-- Created by Redgate Data Modeler (https://datamodeler.redgate-platform.com)
-- Last modification date: 2026-04-13 15:56:32.107

-- tables
-- Table: cars
CREATE TABLE cars (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    car_number TEXT NOT NULL UNIQUE,
    brand TEXT NOT NULL,
    mileage INTEGER NOT NULL,
    load_capacity REAL NOT NULL
);

-- Table: drivers
CREATE TABLE drivers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    full_name TEXT NOT NULL,
    category TEXT NOT NULL,
    experience INTEGER NOT NULL,
    address TEXT NOT NULL,
    birth_year INTEGER NOT NULL
);

-- Table: orders
CREATE TABLE orders (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    order_date TEXT NOT NULL,
    driver_id INTEGER NOT NULL,
    car_id INTEGER NOT NULL,
    distance INTEGER NOT NULL,
    cargo_weight REAL NOT NULL,
    cost REAL NOT NULL,
    driver_earnings REAL,
    FOREIGN KEY (driver_id) REFERENCES drivers(id),
    FOREIGN KEY (car_id) REFERENCES cars(id)
);

-- Table: users
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    role TEXT NOT NULL
);

-- Тестовые данные
INSERT INTO users VALUES (1, 'admin', 'admin123', 'admin');
INSERT INTO users VALUES (2, 'dispatcher1', 'pass123', 'dispatcher');
INSERT INTO users VALUES (3, 'driver1', 'pass123', 'driver');

INSERT INTO cars VALUES (1, 'A001AA', 'Volvo', 120000, 5.5);
INSERT INTO cars VALUES (2, 'B002BB', 'Scania', 85000, 8.0);
INSERT INTO cars VALUES (3, 'C003CC', 'MAN', 45000, 6.0);

INSERT INTO drivers VALUES (1, 'Иванов Иван', 'C', 15, 'ул. Ленина 1', 1980);
INSERT INTO drivers VALUES (2, 'Петров Пётр', 'C', 8, 'ул. Гагарина 2', 1990);
INSERT INTO drivers VALUES (3, 'Сидоров Сидор', 'B', 3, 'ул. Пушкина 3', 1995);

INSERT INTO orders VALUES (1, '2025-04-01', 1, 1, 200, 4.5, 500, 100);
INSERT INTO orders VALUES (2, '2025-04-02', 2, 2, 350, 7.0, 800, 160);
INSERT INTO orders VALUES (3, '2025-04-03', 1, 3, 150, 3.0, 350, 70);