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
    
    sqlite3_stmt *stmt;
    int found = 0;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *role = (const char *)sqlite3_column_text(stmt, 0);
            found = 1;
            
            if (strcmp(role, "admin") == 0)
                current_role = 3;
            else if (strcmp(role, "dispatcher") == 0)
                current_role = 2;
            else
                current_role = 1;
        }
        sqlite3_finalize(stmt);
    }
    
    db_close(db);
    return found;
}

int get_current_user_role() {
    return current_role;
}
