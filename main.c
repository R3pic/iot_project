// main.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "password.h"
#include "user_db.h"

int main(void) {
    sqlite3 *db;
    if (open_database("users.db", &db) != SQLITE_OK) {
        return 1;
    }

    if (create_user_table(db) != SQLITE_OK) {
        close_database(db);
        return 1;
    }

    printf("Program Start\n");

    unsigned int fail_count = 0;
    while (1) {
        if (isHuman) {
            unsigned int user_id, password;
            unsigned int FndData1 = 0, FndData2 = 0;

            // 사용자 ID 입력
            printf("Enter User ID (up to 6 digits): ");
            scanf("%6d", &user_id);

            if (user_exists(db, user_id) == false) {
                printf("User with ID %d not exists. Try again.\n", user_id);
                continue;
            }

            // 비밀번호 입력
            input_password(&password);

            // 데이터베이스에 삽입
            // if (insert_user(db, user_id, password) == SQLITE_OK) {
            //     printf("User data successfully inserted.\n");
            // }
            // 비밀번호 검증
            if (check_password(db, user_id, password)) {
                printf("Password check successful.\n");
            } else {
                printf("Password check failed.\n");
                fail_count++;
                printf("Fail Count: %d", fail_count);
            }
        } else {
            checkhuman();
        }
    }

    close_database(db);
    return 0;
}
