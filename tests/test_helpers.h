#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

static void setup_test_db() {
    // Удаляем старую тестовую БД
    remove("data/test.db");
    
    // Создаём новую
    sqlite3 *db;
    sqlite3_open("data/test.db", &db);
    
    // Создаём таблицы (упрощённо, без внешних ключей для простоты)
    sqlite3_exec(db, "CREATE TABLE cars (id INTEGER PRIMARY KEY AUTOINCREMENT, car_number TEXT, brand TEXT, mileage INTEGER, load_capacity REAL);", 0, 0, 0);
    sqlite3_exec(db, "CREATE TABLE drivers (id INTEGER PRIMARY KEY AUTOINCREMENT, full_name TEXT, category TEXT, experience INTEGER, address TEXT, birth_year INTEGER);", 0, 0, 0);
    sqlite3_exec(db, "CREATE TABLE orders (id INTEGER PRIMARY KEY AUTOINCREMENT, order_date TEXT, driver_id INTEGER, car_id INTEGER, distance INTEGER, cargo_weight REAL, cost REAL, driver_earnings REAL);", 0, 0, 0);
    
    // Добавляем тестовые данные
    sqlite3_exec(db, "INSERT INTO cars (car_number, brand, mileage, load_capacity) VALUES ('T001', 'TestCar', 0, 10.0);", 0, 0, 0);
    sqlite3_exec(db, "INSERT INTO drivers (full_name, category, experience, address, birth_year) VALUES ('Test Driver', 'C', 5, 'Test Address', 1990);", 0, 0, 0);
    
    sqlite3_close(db);
}

static void teardown_test_db() {
    remove("data/test.db");
}

#endif
