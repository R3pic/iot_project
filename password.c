// password.c

#include <stdio.h>
#include <stdlib.h>
#include "password.h"

bool isHuman = false;          // 전역 변수 초기화
int passwordNum[6] = {0};      // 6자리 비밀번호 배열 초기화
int currentDigit = 0;          // 현재 자릿수 초기화

unsigned int FndData1 = 0;     // 전역 변수로 FND 데이터 초기화
unsigned int FndData2 = 0;

void password_clear();
// 사용자 확인 함수
void checkhuman() {
    printf("Are you human? (if you are, press A then Enter)\n");
    char input;
    scanf(" %c", &input);
    if (input == 'A')
        isHuman = true;
}

// 비밀번호 입력 함수
void input_password(unsigned int *password) {
    bool isDone = false;
    password_clear();
    while (!isDone) {
        printf("Options: 1 = Increment, 2 = Next Digit, 3 = Clear, 4 = OK\n");
        char oper;
        scanf(" %c", &oper);

        switch (oper) {
            case '1':
                passwordNum[currentDigit] = (passwordNum[currentDigit] + 1) % 10;
                printf("Incremented current digit to %d\n", passwordNum[currentDigit]);
                getFndData(&FndData1, &FndData2);
                printf("Retrieved FND Data: FND1 = %08X, FND2 = %08X\n", FndData1, FndData2);
                break;
            case '2':
                currentDigit = (currentDigit + 1) % 6; // 6자리로 변경
                printf("Moved to digit %d\n", currentDigit);
                break;
            case '3':
                password_clear();
                printf("Password cleared\n");
                break;
            case '4':
                *password = passwordNum[5] * 100000 + passwordNum[4] * 10000 + passwordNum[3] * 1000 + passwordNum[2] * 100 + passwordNum[1] * 10 + passwordNum[0];
                printf("Password OK: %06d\n", *password);
                isDone = true;
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

// FND 데이터 변환 함수
void parseToFnd() {
    // FndData1: 우측부터 1번째 자리 ~ 4번째 자리
    FndData1 = (passwordNum[3] << 24) | (passwordNum[2] << 16) | (passwordNum[1] << 8) | passwordNum[0];

    // FndData2: 우측부터 5번째 자리 ~ 6번째 자리 (상위 16비트는 0)
    FndData2 = (passwordNum[5] << 8) | passwordNum[4];
}

// 외부에서 FND 데이터를 가져올 수 있는 함수
void getFndData(unsigned int *data1, unsigned int *data2) {
    parseToFnd();
    *data1 = FndData1;
    *data2 = FndData2;
}

void password_clear(){
    for (int i = 0; i < 6; i++) {
        passwordNum[i] = 0;
    }
    currentDigit = 0;
}