#include <stdio.h>
#include <sqlite3.h>
#include "database.h"
#include "orders.h"

void list_orders() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    execute_query(db, "SELECT id, order_date, driver_id, car_id, cargo_weight, cost FROM orders;");
    db_close(db);
}

void add_order() {
    char date[11];
    int driver_id, car_id, distance;
    float cargo_weight, cost;
    
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter driver ID: ");
    scanf("%d", &driver_id);
    printf("Enter car ID: ");
    scanf("%d", &car_id);
    printf("Enter distance: ");
    scanf("%d", &distance);
    printf("Enter cargo weight: ");
    scanf("%f", &cargo_weight);
    printf("Enter cost: ");
    scanf("%f", &cost);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    // Проверка грузоподъёмности
    char check_sql[256];
    snprintf(check_sql, sizeof(check_sql), "SELECT load_capacity FROM cars WHERE id = %d;", car_id);
    float load_capacity = 0;
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, check_sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            load_capacity = (float)sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    
    if (cargo_weight > load_capacity) {
        printf("Error: Cargo weight %.2f exceeds car load capacity %.2f\n", cargo_weight, load_capacity);
        db_close(db);
        return;
    }
    
    float driver_earnings = cost * 0.20;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO orders (order_date, driver_id, car_id, distance, cargo_weight, cost, driver_earnings) VALUES ('%s', %d, %d, %d, %.2f, %.2f, %.2f);",
             date, driver_id, car_id, distance, cargo_weight, cost, driver_earnings);
    
    execute_query(db, sql);
    db_close(db);
    printf("Order added! Driver earnings: %.2f\n", driver_earnings);
}

void delete_order() {
    int id;
    printf("Enter order ID to delete: ");
    scanf("%d", &id);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM orders WHERE id = %d;", id);
    execute_query(db, sql);
    db_close(db);
    printf("Order deleted (if existed).\n");
}
