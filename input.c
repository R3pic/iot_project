#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "input.h"
#include "state.h"

unsigned int inputdata[6] = { 0 };
int currentDigit = 0;
bool isDone = false;
unsigned int *current_data;

void input_init(){
    pullUpDnControl(BTN1_PIN, PUD_UP);
    if(wiringPiISR(BTN1_PIN, INT_EDGE_FALLING, &button1_pressed) < 0){
        printf("ISR setup failed for BTN1\n");
        exit(1);
    }
    pullUpDnControl(BTN2_PIN, PUD_UP);
    if(wiringPiISR(BTN2_PIN, INT_EDGE_FALLING, &button2_pressed) < 0){
        printf("ISR setup failed for BTN2\n");
        exit(1);
    }
    pullUpDnControl(BTN3_PIN, PUD_UP);
    if(wiringPiISR(BTN3_PIN, INT_EDGE_FALLING, &button3_pressed) < 0){
        printf("ISR setup failed for BTN3\n");
        exit(1);
    }
    pullUpDnControl(BTN4_PIN, PUD_UP);
    if(wiringPiISR(BTN4_PIN, INT_EDGE_FALLING, &button4_pressed) < 0){
        printf("ISR setup failed for BTN4\n");
        exit(1);
    }
}

void input_with_button(unsigned int *_current_data) {
    current_data = _current_data;
    isDone = false;
    while (!isDone) {
        printf("Options: 1 = Increment, 2 = Next Digit, 3 = Clear, 4 = OK\n");
        char oper;
        scanf(" %c", &oper);

        switch (oper) {
            case '1':
                button1_pressed();
                break;
            case '2':
                button2_pressed();
                break;
            case '3':
                button3_pressed();
                break;
            case '4':
                button4_pressed();
                break;
            case 'q':
                printf("Program stopped.\n");
                exit(0);
                break;
            default:
                printf("Invalid option, try again.\n");
                break;
        }
    }
}

void button1_pressed() {
    switch (current_State) {
        case IDLE:
            break;
        case INPUT_ID:
            inputdata[currentDigit] = (inputdata[currentDigit] + 1) % 10;
            printf("Incremented ID number: %d\n", inputdata[currentDigit]);
            printf("Current ID input: %d\n", get_plain_int());
            break;
        case INPUT_PASSWORD:
            inputdata[currentDigit] = (inputdata[currentDigit] + 1) % 10;
            printf("Incremented Password number: %d\n", inputdata[currentDigit]);
            printf("Current Password input: %d\n", get_plain_int());
            break;
        case LOGGED_IN:
            break;
        case LOGGED_IN_WITH_ADMIN:
            break;
    }
}

void button2_pressed() {
    switch (current_State) {
        case IDLE:
            break;
        case INPUT_ID:
            currentDigit = (currentDigit + 1) % 6;
            printf("Moved to digit %d\n", currentDigit);
            printf("Current ID input: %d\n", get_plain_int());
            break;
        case INPUT_PASSWORD:
            currentDigit = (currentDigit + 1) % 6;
            printf("Moved to digit %d\n", currentDigit);
            printf("Current Password input: %d\n", get_plain_int());
            break;
        case LOGGED_IN:
            break;
        case LOGGED_IN_WITH_ADMIN:
            break;
    }
}

void button3_pressed() {
    switch (current_State) {
        case IDLE:
            break;
        case INPUT_ID:
            input_clear();
            printf("input cleared\n");
            break;
        case INPUT_PASSWORD:
            input_clear();
            printf("input cleared\n");
            break;
        case LOGGED_IN:
            break;
        case LOGGED_IN_WITH_ADMIN:
            break;
    }
}

void button4_pressed() {
    switch (current_State) {
        case IDLE:
            break;
        case INPUT_ID:
            *current_data = get_plain_int();
            printf("input OK: %d\n", *current_data);
            if (user_exists(db, *current_data) == false) {
                printf("User with ID %d not exists. Try again.\n", *current_data);
            } else {
                printf("User with ID %d exists.\n", *current_data);
                current_State = INPUT_PASSWORD;
            }
            input_clear();
            isDone = true;
            break;
        case INPUT_PASSWORD:
            *current_data = get_plain_int();
            printf("input OK: %d\n", *current_data);
            unsigned int fndData[2];
            parseToFnd(fndData, *current_data);
            printf("FND Data: FND1 = %08X, FND2 = %08X\n", fndData[0], fndData[1]);
            if (strcmp(get_password(db, *current_data), *current_data) == 0) {
                printf("Password check successful.\n");
                current_State = LOGGED_IN;
            } else {
                printf("Password check failed.\n");
                fail_count++;
                printf("Fail Count: %d\n", fail_count);
            }
            isDone = true;
            break;
        case LOGGED_IN:
            break;
        case LOGGED_IN_WITH_ADMIN:
            break;
    }
}

unsigned int get_plain_int() {
    unsigned int result = inputdata[5] * 100000 + inputdata[4] * 10000 + inputdata[3] * 1000 + inputdata[2] * 100 + inputdata[1] * 10 + inputdata[0];
    return result;
}

void parseToFnd(unsigned int *fndData, unsigned int passwordNum) {
    // FndData1: 1~4 digits of passwordNum 
    fndData[0] = ((passwordNum / 1000 % 10) << 24) | ((passwordNum / 100 % 10) << 16) | ((passwordNum / 10 % 10) << 8) | (passwordNum % 10);

    // FndData2: 5~6 digits of passwordNum
    fndData[1] = ((passwordNum / 100000 % 10) << 8) | (passwordNum / 10000 % 10);
}

void input_clear() {
    for (int i = 0; i < 6; i++) {
        inputdata[i] = 0;
    }
    currentDigit = 0;
}