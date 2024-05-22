// main.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wiringPi.h>
#include "input.h"
#include "user_db.h"
#include "state.h"

int main(void) {
    // Database initialization
    sqlite3 *db;
    if (open_database("users.db", &db) != SQLITE_OK) {
        return 1;
    }

    if (create_user_table(db) != SQLITE_OK) {
        close_database(db);
        return 1;
    }

    printf("Program Start\n");
    // Module initialization
    if (wiringPiSetupGpio() == -1) {
        printf("WiringPi setup failed.\n");
        return 1;
    }
    input_init();

    // Variable initialization
    unsigned int fail_count = 0;

    unsigned int user_id, password;

    // Main loop
    while (1) {
    // user id check
        current_State = INPUT_ID;
        input_with_button(&user_id);
        char user_id_str[6];
        sprintf(user_id_str, "%d", user_id);

    if (user_exists(db, user_id_str) == false) {
        printf("User with ID %d not exists. Try again.\n", user_id);
        input_clear();
        continue;
    } else {
        printf("User with ID %d exists.\n", user_id);
    }
    input_clear();

    // password check
    current_State = INPUT_PASSWORD;
    input_with_button(&password);
    char password_str[6];
    sprintf(password_str, "%d", password);
    char *password_db = get_password(db, user_id_str);

    if (password_db == NULL) {
        printf("Failed to retrieve password from database.\n");
        fail_count++;
        printf("Fail Count: %d\n", fail_count);
    } else {
        printf("password_str: %s\n", password_str);
        printf("password_db: %s\n", password_db);

        if (strcmp(password_str, password_db) == 0) {
            printf("Password check successful.\n");
        } else {
            printf("Password check failed.\n");
            fail_count++;
            printf("Fail Count: %d\n", fail_count);
        }
        free(password_db);
    }
    input_clear();
}

    // Program end
    close_database(db);
    return 0;
}
