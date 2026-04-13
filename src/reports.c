#include <stdio.h>
#include <sqlite3.h>
#include "database.h"
#include "reports.h"

void reports_menu() {
    int choice;
    printf("\n=== Reports ===\n");
    printf("1. Car mileage report\n");
    printf("2. Driver earnings report\n");
    printf("Choose: ");
    scanf("%d", &choice);
    
    if (choice == 1) report_car_mileage();
    else if (choice == 2) report_driver_earnings();
}

void report_car_mileage() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    execute_query(db, "SELECT car_number, SUM(distance) as total_mileage FROM orders JOIN cars ON orders.car_id = cars.id GROUP BY car_number;");
    db_close(db);
}

void report_driver_earnings() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    execute_query(db, "SELECT full_name, SUM(driver_earnings) as total_earnings FROM orders JOIN drivers ON orders.driver_id = drivers.id GROUP BY full_name;");
    db_close(db);
}
