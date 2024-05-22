#ifndef PIR_H
#define PIR_H

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h> // wiringPi GPIO 라이브러리 포함

#define PIR_PIN 18 // 센서핀 정의

void initPir(int nPin); // 센서 관련 함수 프로토타입 선언
int readPir(int nPin);

#endif // PIR_H