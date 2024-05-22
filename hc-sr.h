#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h> // wiringPi GPIO 라이브러리 포함

#define TP_PIN 23 // 센서핀 정의
#define EP_PIN 24

void initUltra(int nTrigPin, int nEchoPin); // 센서 관련 함수 프로토타입 선언
float getDistance(int nTrigPin, int nEchoPin);