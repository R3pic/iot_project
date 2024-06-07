#include "input.h"
#include "state.h"
#include "uart.h"
#include "user_db.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <wiringPi.h>

unsigned int inputdata[6] = { 0 };
int currentDigit = 0;
bool isDone = false;
unsigned long lastInterruptTime = 0;
int fail_count = 0;
int id, password;
extern int current_Data;

void log_attempt(int id);

unsigned long getmillis()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

void input_init()
{
    pinMode(BTN1_PIN, INPUT);
    pinMode(BTN2_PIN, INPUT);
    pinMode(BTN3_PIN, INPUT);
    pinMode(BTN4_PIN, INPUT);

    pullUpDnControl(BTN1_PIN, PUD_UP);
    pullUpDnControl(BTN2_PIN, PUD_UP);
    pullUpDnControl(BTN3_PIN, PUD_UP);
    pullUpDnControl(BTN4_PIN, PUD_UP);
}

void check_buttons()
{
    if (digitalRead(BTN1_PIN) == LOW)
    {
        button1_pressed();
    }
    if (digitalRead(BTN2_PIN) == LOW)
    {
        button2_pressed();
    }
    if (digitalRead(BTN3_PIN) == LOW)
    {
        button3_pressed();
    }
    if (digitalRead(BTN4_PIN) == LOW)
    {
        button4_pressed();
    }
}

void button1_pressed()
{
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime > BOUNCE_TIME)
    {
        switch (current_State)
        {
        case IDLE:
            break;
        case INPUT_ID:
            inputdata[currentDigit] = (inputdata[currentDigit] + 1) % 10;
            printf("Incremented number: %d\n", inputdata[currentDigit]);
            printf("Current ID input: %d\n", get_plain_int());
            break;
        case INPUT_PASSWORD:
            inputdata[currentDigit] = (inputdata[currentDigit] + 1) % 10;
            printf("Incremented number: %d\n", inputdata[currentDigit]);
            printf("Current Password input: %d\n", get_plain_int());
            break;
        case LOGGED_IN:
        case LOGGED_IN_WITH_ADMIN:
            break;
        }
        lastInterruptTime = interruptTime;
    }
}

void button2_pressed()
{
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime > BOUNCE_TIME)
    {
        switch (current_State)
        {
        case IDLE:
            break;
        case INPUT_ID:
        case INPUT_PASSWORD:
            currentDigit = (currentDigit + 1) % 6;
            printf("Moved to digit %d\n", currentDigit);
            printf("Current input: %d\n", get_plain_int());
            char buf[100];
            sprintf(buf, "LCD 2 Current digit: %d\n", currentDigit);
            uart_send(buf);
            break;
        case LOGGED_IN:
        case LOGGED_IN_WITH_ADMIN:
            break;
        }
        lastInterruptTime = interruptTime;
    }
}

void button3_pressed()
{
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime > BOUNCE_TIME)
    {
        switch (current_State)
        {
        case IDLE:
            break;
        case INPUT_ID:
        case INPUT_PASSWORD:
            input_clear();
            printf("Input cleared\n");
            break;
        case LOGGED_IN:
        case LOGGED_IN_WITH_ADMIN:
            break;
        }
        lastInterruptTime = interruptTime;
    }
}

void button4_pressed()
{
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime > BOUNCE_TIME)
    {
        sqlite3 *db;
        if (open_database("users.db", &db) != SQLITE_OK)
        {
            return;
        }

        switch (current_State)
        {
        case IDLE:
            break;
        case INPUT_ID:
            id = get_plain_int();
            printf("Input OK: %d\n", id);
            if (!user_exists(db, id))
            {
                printf("User with ID %d not exists. Try again.\n", id);
            }
            else
            {
                printf("User with ID %d exists.\n", id);
                state_update(INPUT_PASSWORD);
            }
            input_clear();
            isDone = true;
            break;
        case INPUT_PASSWORD:
            password = get_plain_int();
            printf("Input OK: %d\n", password);
            unsigned int fndData[2];
            parseToFnd(fndData);
            printf("FND Data: FND1 = %08X, FND2 = %08X\n", fndData[0], fndData[1]);
            int password_db = get_password(db, id);

            if (password_db != -1 && password_db == password)
            {
                printf("Password check successful.\n");
                uart_send("BUZZER 1\n");
                delay(1000);
                uart_send("MOTOR 1\n");
                state_update(LOGGED_IN);
                // 로그인 성공시 10초 기다렸다가 상태 초기화하고 IDLE모드로 돌아가기.
                delay(10000);
                uart_send("MOTOR 0\n");
                state_update(IDLE);
                fail_count = 0;
                uart_send("LED 0\n");
                input_clear();
            }
            else
            {
                printf("Password check failed.\n");
                uart_send("BUZZER 0\n");
                fail_count++;
                printf("Fail Count: %d\n", fail_count);
                char buffer[10];
                sprintf(buffer, "LED %d", fail_count);
                uart_send(buffer);
                delay(1000);
                if (fail_count >= 4)
                {
                    uart_send("BUZZER 2\n");
                    delay(1000);
                    uart_send("LED 0\n");
                    fail_count = 0;
                    // log_attempt(id);
                }
                // current_State = INPUT_ID;
                state_update(INPUT_ID);
            }
            isDone = true;
            input_clear();
            break;
        case LOGGED_IN:
        case LOGGED_IN_WITH_ADMIN:
            break;
        }
        close_database(db);
        lastInterruptTime = interruptTime;
    }
}

void log_attempt(int id)
{
    FILE *fp = fopen("log.txt", "a");
    if (fp == NULL)
    {
        perror("Failed to open log file");
        return;
    }

    // 현재 시간 가져오기
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // 시간 및 날짜 형식 지정
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    // 로그 메시지 만들기
    char log_message[200];
    sprintf(log_message, "[%s] Becareful! Someone tried to access the system with ID: %d\n", timestamp, id);

    // 로그 파일에 기록
    fprintf(fp, "%s", log_message);
    fclose(fp);
}

int get_plain_int()
{
    int result = inputdata[5] * 100000 + inputdata[4] * 10000 + inputdata[3] * 1000 + inputdata[2] * 100 + inputdata[1] * 10 + inputdata[0];
    return result;
}

void parseToFnd(unsigned int *fndData)
{
    int tmp = get_plain_int();
    // FndData1: 1~4 digits of tmp
    fndData[0] = ((tmp / 1000 % 10) << 24) | ((tmp / 100 % 10) << 16) | ((tmp / 10 % 10) << 8) | (tmp % 10);

    // FndData2: 5~6 digits of tmp
    fndData[1] = ((tmp / 100000 % 10) << 8) | (tmp / 10000 % 10);
}

void input_clear()
{
    for (int i = 0; i < 6; i++)
    {
        inputdata[i] = 0;
    }
    currentDigit = 0;
    char buf[200];
    sprintf(buf, "LCD 2 Current digit: %d\n", currentDigit);
    uart_send(buf);
}
