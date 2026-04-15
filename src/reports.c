#include <stdio.h>
#include <sqlite3.h>
#include "database.h"
#include "reports.h"

void reports_menu() {
    int choice;
    printf("\n=== Reports ===\n");
    printf("1. Orders by driver for period\n");
    printf("2. Car total mileage and cargo\n");
    printf("3. Driver statistics (trips, cargo, earnings)\n");
    printf("4. Driver with fewest trips\n");
    printf("5. Car with highest mileage\n");
    printf("6. Earnings for all drivers for period\n");
    printf("7. Earnings for specific driver for period\n");
    printf("Choose: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1: orders_by_driver_period(); break;
        case 2: car_total_stats(); break;
        case 3: driver_statistics(); break;
        case 4: driver_fewest_trips(); break;
        case 5: car_highest_mileage(); break;
        case 6: earnings_all_drivers_period(); break;
        case 7: earnings_driver_period(); break;
        default: printf("Invalid choice\n");
    }
}

void orders_by_driver_period() {
    char driver_name[100], start_date[11], end_date[11];
    printf("Enter driver full name: ");
    scanf(" %[^\n]", driver_name);
    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%s", start_date);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", end_date);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT o.order_date, c.car_number, o.distance, o.cargo_weight, o.cost "
             "FROM orders o "
             "JOIN drivers d ON o.driver_id = d.id "
             "JOIN cars c ON o.car_id = c.id "
             "WHERE d.full_name = '%s' AND o.order_date BETWEEN '%s' AND '%s';",
             driver_name, start_date, end_date);
    
    printf("\n=== Orders for %s from %s to %s ===\n", driver_name, start_date, end_date);
    execute_query(db, sql);
    db_close(db);
}

void car_total_stats() {
    char car_number[20];
    printf("Enter car number: ");
    scanf("%s", car_number);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT SUM(o.distance) as total_mileage, SUM(o.cargo_weight) as total_cargo "
             "FROM orders o JOIN cars c ON o.car_id = c.id "
             "WHERE c.car_number = '%s';",
             car_number);
    
    printf("\n=== Statistics for car %s ===\n", car_number);
    execute_query(db, sql);
    db_close(db);
}

void driver_statistics() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    const char *sql = "SELECT d.full_name, COUNT(o.id) as trips, SUM(o.cargo_weight) as total_cargo, SUM(o.driver_earnings) as total_earnings "
                      "FROM drivers d LEFT JOIN orders o ON d.id = o.driver_id "
                      "GROUP BY d.id;";
    
    printf("\n=== Driver Statistics ===\n");
    execute_query(db, sql);
    db_close(db);
}

void driver_fewest_trips() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    const char *sql = "SELECT d.full_name, d.category, d.experience, COUNT(o.id) as trips, SUM(o.driver_earnings) as earnings "
                      "FROM drivers d LEFT JOIN orders o ON d.id = o.driver_id "
                      "GROUP BY d.id ORDER BY trips ASC LIMIT 1;";
    
    printf("\n=== Driver with Fewest Trips ===\n");
    execute_query(db, sql);
    db_close(db);
}

void car_highest_mileage() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    const char *sql = "SELECT c.car_number, c.brand, c.mileage, SUM(o.distance) as total_distance "
                      "FROM cars c LEFT JOIN orders o ON c.id = o.car_id "
                      "GROUP BY c.id ORDER BY total_distance DESC LIMIT 1;";
    
    printf("\n=== Car with Highest Total Mileage ===\n");
    execute_query(db, sql);
    db_close(db);
}

void earnings_all_drivers_period() {
    char start_date[11], end_date[11];
    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%s", start_date);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", end_date);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT d.full_name, SUM(o.driver_earnings) as earnings "
             "FROM drivers d JOIN orders o ON d.id = o.driver_id "
             "WHERE o.order_date BETWEEN '%s' AND '%s' "
             "GROUP BY d.id;",
             start_date, end_date);
    
    printf("\n=== Earnings for period %s to %s ===\n", start_date, end_date);
    execute_query(db, sql);
    db_close(db);
}

void earnings_driver_period() {
    char driver_name[100], start_date[11], end_date[11];
    printf("Enter driver full name: ");
    scanf(" %[^\n]", driver_name);
    printf("Enter start date (YYYY-MM-DD): ");
    scanf("%s", start_date);
    printf("Enter end date (YYYY-MM-DD): ");
    scanf("%s", end_date);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT d.full_name, SUM(o.driver_earnings) as earnings "
             "FROM drivers d JOIN orders o ON d.id = o.driver_id "
             "WHERE d.full_name = '%s' AND o.order_date BETWEEN '%s' AND '%s';",
             driver_name, start_date, end_date);
    
    printf("\n=== Earnings for %s from %s to %s ===\n", driver_name, start_date, end_date);
    execute_query(db, sql);
    db_close(db);
}
