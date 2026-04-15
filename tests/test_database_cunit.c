#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <sqlite3.h>
#include "database.h"

void test_db_open_close() {
    sqlite3 *db;
    CU_ASSERT(db_open("data/autopark.db", &db) == SQLITE_OK);
    db_close(db);
}

void test_execute_query() {
    sqlite3 *db;
    db_open("data/autopark.db", &db);
    CU_ASSERT(execute_query(db, "SELECT 1;") == SQLITE_OK);
    db_close(db);
}

void test_cars_table_exists() {
    sqlite3 *db;
    db_open("data/autopark.db", &db);
    const char *sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='cars';";
    CU_ASSERT(execute_query(db, sql) == SQLITE_OK);
    db_close(db);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Database Tests", 0, 0);
    CU_add_test(suite, "test_db_open_close", test_db_open_close);
    CU_add_test(suite, "test_execute_query", test_execute_query);
    CU_add_test(suite, "test_cars_table_exists", test_cars_table_exists);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
