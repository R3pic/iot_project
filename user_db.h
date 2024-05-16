#ifndef USER_DB_H
#define USER_DB_H

#include <sqlite3.h>
#include <stdbool.h>

// 데이터베이스 작업
int open_database(const char *filename, sqlite3 **db);
int create_user_table(sqlite3 *db);
int insert_user(sqlite3 *db, int user_id, const int password);
int close_database(sqlite3 *db);
bool check_password(sqlite3 *db, int user_id, const int password);
bool user_exists(sqlite3 *db, int user_id);

#endif // USER_DB_H
