#include "pir.h" //센싱 관련 헤더 파일 포함

int gnPirState = LOW;  // 동작 센서 상태 변수 정의
void initPir(int nPin) // 센서 초기화 함수
{
    pinMode(nPin, INPUT); // 센서핀 입력 설정
}
int readPir(int nPin) // 센서값 read 함수
{
    int nPirVal = 0; // 센서값 변수 정의

    nPirVal = digitalRead(nPin); // 센서값 read
    if (nPirVal == HIGH)
    {
        if (gnPirState == LOW)
        { // 모션 감지시 동작
            printf("Motion detected!\n");
            gnPirState = HIGH;
        }
    }
    else
    {
        if (gnPirState == HIGH)
        {
            printf("Motion ended!\n");
            gnPirState = LOW;
        }
    }
    return nPirVal;
}