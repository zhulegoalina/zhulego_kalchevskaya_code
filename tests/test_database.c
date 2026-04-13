#include <stdio.h>
#include <assert.h>
#include <sqlite3.h>

int test_database_connection() {
    sqlite3 *db;
    int rc = sqlite3_open("data/autopark.db", &db);
    if (rc != SQLITE_OK) {
        printf("Failed to open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    sqlite3_close(db);
    printf("Database connection test passed\n");
    return 0;
}

int main() {
    int result = test_database_connection();
    return result;
}
