#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

int db_open(const char *filename, sqlite3 **db);
void db_close(sqlite3 *db);
int execute_query(sqlite3 *db, const char *sql);
int callback(void *data, int argc, char **argv, char **azColName);

#endif
