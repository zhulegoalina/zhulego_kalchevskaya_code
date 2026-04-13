#include <stdio.h>
#include <assert.h>
#include <sqlite3.h>
#include "database.h"

void test_db_open() {
    sqlite3 *db;
    int rc = db_open("data/autopark.db", &db);
    assert(rc == SQLITE_OK);
    db_close(db);
    printf("test_db_open passed\n");
}

void test_db_close() {
    sqlite3 *db;
    db_open("data/autopark.db", &db);
    db_close(db);
    printf("test_db_close passed\n");
}

void test_execute_query() {
    sqlite3 *db;
    db_open("data/autopark.db", &db);
    int rc = execute_query(db, "SELECT 1;");
    assert(rc == SQLITE_OK);
    db_close(db);
    printf("test_execute_query passed\n");
}

int main() {
    test_db_open();
    test_db_close();
    test_execute_query();
    printf("\nAll database tests passed!\n");
    return 0;
}
