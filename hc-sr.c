#include "hc-sr.h" //센싱 관련 헤더 파일 포함

float getDistance(int nTrigPin, int nEchoPin) // 거리 감지 함수
{
    float fDistance; // 측정 거리 변수

    int nStartTime, nEndTime; // 시간 변수

    digitalWrite(nTrigPin, LOW); // 초음파 신호 10us 발생

    delayMicroseconds(2);
    digitalWrite(nTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(nTrigPin, LOW);

    while (digitalRead(nEchoPin) == LOW)
        ; // 초음파 입력 신호 대기

    nStartTime = micros();

    while (digitalRead(nEchoPin) == HIGH)
        ; // 초음파 신호 수신시 시간 저장

    nEndTime = micros();
    fDistance = (nEndTime - nStartTime) / 29. / 2.; // 거리 계산

    return fDistance; // 거리 반환
}
void initUltra(int nTrigPin, int nEchoPin) // 센서 초기화 함수
{
    pinMode(nTrigPin, OUTPUT);
    pinMode(nEchoPin, INPUT);
}