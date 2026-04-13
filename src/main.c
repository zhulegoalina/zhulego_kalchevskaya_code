#include <stdio.h>
#include "database.h"

int main() {
    sqlite3 *db;
    
    printf(" Autopark Management System \n");
    
    if (db_open("data/autopark.db", &db) != SQLITE_OK) {
        return 1;
    }
    
    printf("Connected to database\n\n");
    
    // Вывести всех водителей
    printf("Drivers \n");
    const char *sql = "SELECT id, full_name, experience FROM drivers;";
    execute_query(db, sql);
    
    db_close(db);
    return 0;
}
