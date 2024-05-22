#include <softTone.h> // wiringPi 버저 PWM 라이브러리 포함
#include <stdio.h>
#include <wiringPi.h> // wiringPi 라이브러리 포함

#define NOTE_C6 1047 // 도

#define NOTE_CS6 1109
#define NOTE_D6 1175 // 레

#define NOTE_DS6 1245
#define NOTE_E6 1319 // 미
#define NOTE_F6 1397 // 파

#define NOTE_FS6 1480
#define NOTE_G6 1568 // 솔

#define NOTE_GS6 1661
#define NOTE_A6 1760 // 라

#define NOTE_AS6 1865
#define NOTE_B6 1976 // 시

#define NOTE_C7 2093 // 도

#define NOTE_CS7 2217
#define NOTE_D7 2349 // 레

#define NOTE_DS7 2489
#define NOTE_E7 2637 // 미
#define NOTE_F7 2794 // 파

#define NOTE_FS7 2960
#define NOTE_G7 3136 // 솔

#define NOTE_GS7 3322
#define NOTE_A7 3520 // 라

#define NOTE_AS7 3729
#define NOTE_B7 3951 // 시
#define NOTE_C8 4186 // 도

#define CS_MCP3208 8 // SPI 통신핀 정의
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000
#define BUZZER_PIN 17 // 센서핀 정의

#define ON 1
#define OFF 0
void initBuzzer(); // 센서 관련 함수 프로토타입 선언
void playBuzzer(unsigned int unFreq, int nPlayTime);
void stopBuzzer();
void controlBuzzer(int buzzerStatus);