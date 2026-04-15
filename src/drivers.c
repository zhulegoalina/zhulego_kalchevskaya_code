#include <stdio.h>
#include <sqlite3.h>
#include "database.h"
#include "drivers.h"

void list_drivers() {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    execute_query(db, "SELECT id, full_name, category, experience FROM drivers;");
    db_close(db);
}

void add_driver() {
    char name[100], category[20], address[100];
    int experience, birth_year;
    
    printf("Enter full name: ");
    scanf(" %[^\n]", name);
    printf("Enter category: ");
    scanf("%s", category);
    printf("Enter experience (years): ");
    scanf("%d", &experience);
    printf("Enter address: ");
    scanf(" %[^\n]", address);
    printf("Enter birth year: ");
    scanf("%d", &birth_year);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO drivers (full_name, category, experience, address, birth_year) VALUES ('%s', '%s', %d, '%s', %d);",
             name, category, experience, address, birth_year);
    
    execute_query(db, sql);
    db_close(db);
    printf("Driver added successfully!\n");
}

void update_driver() {
    int id;
    char name[100], category[20], address[100];
    int experience, birth_year;
    
    printf("Enter driver ID to update: ");
    scanf("%d", &id);
    printf("Enter new full name: ");
    scanf(" %[^\n]", name);
    printf("Enter new category: ");
    scanf("%s", category);
    printf("Enter new experience: ");
    scanf("%d", &experience);
    printf("Enter new address: ");
    scanf(" %[^\n]", address);
    printf("Enter new birth year: ");
    scanf("%d", &birth_year);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "UPDATE drivers SET full_name='%s', category='%s', experience=%d, address='%s', birth_year=%d WHERE id=%d;",
             name, category, experience, address, birth_year, id);
    
    execute_query(db, sql);
    db_close(db);
    printf("Driver updated successfully!\n");
}

void delete_driver() {
    int id;
    printf("Enter driver ID to delete: ");
    scanf("%d", &id);
    
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return;
    
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM drivers WHERE id = %d;", id);
    execute_query(db, sql);
    db_close(db);
    printf("Driver deleted (if existed).\n");
}
