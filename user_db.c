// user_db.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_db.h"

int open_database(const char *filename, sqlite3 **db) {
    int rc = sqlite3_open(filename, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        return rc;
    }
    return SQLITE_OK;
}

int create_user_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS Users("
                      "ID INTEGER PRIMARY KEY, "
                      "Password VARCHAR(6) NOT NULL)";
    char *errmsg = NULL;
    int rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return rc;
    }
    return SQLITE_OK;
}

int insert_user(sqlite3 *db, int user_id, const int password) {
    char password_str[7];
    sprintf(password_str, "%06d", password);

    const char *sql = "INSERT INTO Users (ID, Password) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, password_str, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return rc;
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

bool check_password(sqlite3 *db, int user_id, const int password) {
    char password_str[7];
    sprintf(password_str, "%06u", password);

    const char *sql = "SELECT Password FROM Users WHERE ID = ?";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_bind_int(stmt, 1, user_id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *stored_password = (const char *)sqlite3_column_text(stmt, 0);
        printf("%s, %s", password_str, stored_password);
        sqlite3_finalize(stmt);
        return !(strcmp(stored_password, password_str) == 0);
    }

    sqlite3_finalize(stmt);
    return false;
}

bool user_exists(sqlite3 *db, int user_id) {
    const char *sql = "SELECT 1 FROM Users WHERE ID = ?";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_bind_int(stmt, 1, user_id);

    rc = sqlite3_step(stmt);
    bool exists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return exists;
}

int close_database(sqlite3 *db) {
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot close database: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    return SQLITE_OK;
}