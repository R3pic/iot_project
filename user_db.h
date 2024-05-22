// user_db.h
#ifndef USER_DB_H
#define USER_DB_H

#include <sqlite3.h>
#include <stdbool.h>

int open_database(const char *filename, sqlite3 **db);
int create_user_table(sqlite3 *db);
int insert_user(sqlite3 *db, int user_id, int password);
bool user_exists(sqlite3 *db, int user_id);
int get_password(sqlite3 *db, int user_id);
int close_database(sqlite3 *db);

#endif // USER_DB_H
