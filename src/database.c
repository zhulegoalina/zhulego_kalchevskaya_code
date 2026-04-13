#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

int db_open(const char *filename, sqlite3 **db) {
    return sqlite3_open(filename, db);
}

void db_close(sqlite3 *db) {
    sqlite3_close(db);
}

int execute_query(sqlite3 *db, const char *sql) {
    char *errmsg = 0;
    int rc = sqlite3_exec(db, sql, callback, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
    return rc;
}

int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
