#ifndef FND_H // FND_H가 정의되어 있지 않다면
#define FND_H // FND_H 정의

#include <wiringPi.h> //wiringPi 라이브러리 포함

#define FND_A 2 // FND 데이터핀 정의
#define FND_B 3
#define FND_C 4
#define FND_D 17
#define FND_E 27
#define FND_F 22
#define FND_G 10
#define FND_DP 9
// FND 세그먼트 핀 정의
#define FND_SEL0 11
#define FND_SEL1 5
#define FND_SEL2 6
#define FND_SEL3 13
#define FND_SEL4 19
#define FND_SEL5 26

#define A_BIT 0x01 // 세그먼트 비트값 정의
#define B_BIT 0x02
#define C_BIT 0x04
#define D_BIT 0x08
#define E_BIT 0x10
#define F_BIT 0x20
#define G_BIT 0x40
#define DP_BIT 0x80
#define MAX_FND_POSITION 6 // 세그먼트 개수
#define MAX_FND_LED 8      // 세그먼트 LED 개수
#define FND_0_SEL 0x01     // 세그먼트 위치 비트값 정의
#define FND_1_SEL 0x02
#define FND_2_SEL 0x04
#define FND_3_SEL 0x08
#define FND_4_SEL 0x10
#define FND_5_SEL 0x20

void initFnd(); // FND 관련 함수 프로토타입 선언
void selectFnd(int Position);
void offFnd();
void FndData(int position, unsigned int data);

#endif // FND_H 종료