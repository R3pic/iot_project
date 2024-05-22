#include "fnd.h" //FND 제어 헤더 파일 포함

const int FndSelectTable[MAX_FND_POSITION] = {
    // FND 위치 핀 정의
    FND_SEL0,
    FND_SEL1,
    FND_SEL2,
    FND_SEL3,
    FND_SEL4,
    FND_SEL5,
};
const int FndPinTable[MAX_FND_LED] = {
    // FND 데이터 핀 정의
    FND_A,
    FND_B,
    FND_C,
    FND_D,
    FND_E,
    FND_F,
    FND_G,
    FND_DP,

};

const int FndNumberTable[16] = {
    // FND 숫자 패턴 정의
    A_BIT | B_BIT | C_BIT | D_BIT | E_BIT | F_BIT,         // '0'
    B_BIT | C_BIT,                                         // '1'
    A_BIT | B_BIT | D_BIT | E_BIT | G_BIT,                 // '2'
    A_BIT | B_BIT | C_BIT | D_BIT | G_BIT,                 // '3'
    B_BIT | C_BIT | F_BIT | G_BIT,                         // '4'
    A_BIT | C_BIT | D_BIT | F_BIT | G_BIT,                 // '5'
    C_BIT | D_BIT | E_BIT | F_BIT | G_BIT,                 // '6'
    A_BIT | B_BIT | C_BIT,                                 // '7'
    A_BIT | B_BIT | C_BIT | D_BIT | E_BIT | F_BIT | G_BIT, // '8'
    A_BIT | B_BIT | C_BIT | F_BIT | G_BIT,                 // '9'
    A_BIT | B_BIT | C_BIT | E_BIT | F_BIT | G_BIT,         // 'A'
    C_BIT | D_BIT | E_BIT | F_BIT | G_BIT,                 // 'b'
    A_BIT | D_BIT | E_BIT | F_BIT,                         // 'C'
    B_BIT | C_BIT | D_BIT | E_BIT | G_BIT,                 // 'd'
    A_BIT | D_BIT | E_BIT | F_BIT | G_BIT,                 // 'E'
    A_BIT | E_BIT | F_BIT | G_BIT,                         // 'F'
};

void initFnd()
{ // FND 초기화 함수
    int i;
    for (i = 0; i < MAX_FND_POSITION; i++)
    {
        pinMode(FndSelectTable[i], OUTPUT); // 세그먼트 위치 선택핀 출력 설정
    }
    for (i = 0; i < MAX_FND_LED; i++)
    {

        pinMode(FndPinTable[i], OUTPUT); // 세그먼트 데이터핀 출력 설정
    }
}

void selectFnd(int Position)
{ // FND 선택 함수
    int i;
    for (i = 0; i < MAX_FND_POSITION; i++)
    { // 세그먼트 위치에 출력

        if (Position & (1 << i))
        {
            digitalWrite(FndSelectTable[i], LOW);
        }
        else
        {
            digitalWrite(FndSelectTable[i], HIGH);
        }
    }
}

void offFnd()
{ // fnd off 함수
    int i;
    for (i = 0; i < MAX_FND_POSITION; i++)
    {

        digitalWrite(FndSelectTable[i], HIGH);
    }
}

void FndData(int position, unsigned int fndData[2])
{ // FND 표시 함수
    int i;
    int fndSegmentData = 0; // 변수명 변경: fndData -> fndSegmentData

    switch (position) // 각 세그먼트 위치에 따라
    {
    case 0:
        selectFnd(FND_0_SEL);
        fndSegmentData = (fndData[0] & 0x000000ff);
        break;
    case 1:
        selectFnd(FND_1_SEL);
        fndSegmentData = (fndData[0] & 0x0000ff00) >> 8;
        break;
    case 2:
        selectFnd(FND_2_SEL);
        fndSegmentData = (fndData[0] & 0x00ff0000) >> 16;
        break;
    case 3:
        selectFnd(FND_3_SEL);
        fndSegmentData = (fndData[0] & 0xff000000) >> 24;
        break;
    case 4:
        selectFnd(FND_4_SEL);
        fndSegmentData = (fndData[1] & 0x000000ff);
        break;
    case 5:
        selectFnd(FND_5_SEL);
        fndSegmentData = (fndData[1] & 0x0000ff00) >> 8;
        break;
    default:
        return; // 올바르지 않은 위치일 경우 함수를 종료합니다.
    }

    for (i = 0; i < MAX_FND_LED; i++) // 각 세그먼트에 신호 출력
    {
        if (FndNumberTable[fndSegmentData] & (1 << i))
        {
            digitalWrite(FndPinTable[i], HIGH);
        }
        else
        {
            digitalWrite(FndPinTable[i], LOW);
        }
    }
    delay(3); // 각 자리의 숫자 표시를 명확히 하기 위한 지연
}
