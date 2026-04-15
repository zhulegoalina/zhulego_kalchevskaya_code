#include <stdio.h>
#include <sqlite3.h>
#include "database.h"
#include "cars.h"

void list_cars() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    execute_query(db, "SELECT id, car_number, brand, mileage, load_capacity FROM cars;");
    db_close(db);
}

void add_car() {
    char number[20], brand[50];
    int mileage;
    float capacity;
    printf("Enter car number: ");
    scanf("%s", number);
    printf("Enter brand: ");
    scanf("%s", brand);
    printf("Enter mileage: ");
    scanf("%d", &mileage);
    printf("Enter load capacity: ");
    scanf("%f", &capacity);
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    char sql[512];
    snprintf(sql, sizeof(sql),
             "INSERT INTO cars (car_number, brand, mileage, load_capacity) VALUES ('%s', '%s', %d, %.2f);",
             number, brand, mileage, capacity);
    execute_query(db, sql);
    db_close(db);
    printf("Car added successfully!\n");
}

void update_car() {
    int id;
    char number[20], brand[50];
    int mileage;
    float capacity;
    printf("Enter car ID to update: ");
    scanf("%d", &id);
    printf("Enter new car number: ");
    scanf("%s", number);
    printf("Enter new brand: ");
    scanf("%s", brand);
    printf("Enter new mileage: ");
    scanf("%d", &mileage);
    printf("Enter new load capacity: ");
    scanf("%f", &capacity);
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    char sql[512];
    snprintf(sql, sizeof(sql),
             "UPDATE cars SET car_number='%s', brand='%s', mileage=%d, load_capacity=%.2f WHERE id=%d;",
             number, brand, mileage, capacity, id);
    execute_query(db, sql);
    db_close(db);
    printf("Car updated successfully!\n");
}

void delete_car() {
    int id;
    printf("Enter car ID to delete: ");
    scanf("%d", &id);
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM cars WHERE id = %d;", id);
    execute_query(db, sql);
    db_close(db);
    printf("Car deleted (if existed).\n");
}
