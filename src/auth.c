#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "database.h"
#include "auth.h"

static int current_role = -1;

int register_user(const char *username, const char *password, const char *role) {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return -1;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, password, role) VALUES ('%s', '%s', '%s')",
             username, password, role);
    
    int rc = execute_query(db, sql);
    db_close(db);
    return rc;
}

int login(const char *username, const char *password) {
    sqlite3 *db;
    if (db_open("data/autopark.db", &db) != SQLITE_OK) return 0;
    
    char sql[512];
    snprintf(sql, sizeof(sql),
             "SELECT role FROM users WHERE username='%s' AND password='%s'",
             username, password);
    
    int found = 0;
    if (sqlite3_exec(db, sql, 0, 0, 0) == SQLITE_OK) {
        found = 1;
        current_role = 2;
    }
    
    db_close(db);
    return found;
}

int get_current_user_role() {
    return current_role;
}
