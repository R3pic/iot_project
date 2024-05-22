#include "buzzer.h" //Buzzer 제어 헤더파일 포함

int melodySize = 8;                                                                  // 멜로디 크기
int melody[] = { NOTE_C7, NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, 0, NOTE_B6, NOTE_C7 }; // 멜로디 계이름
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };                                    // 음표 길이

void initBuzzer()
{
    softToneCreate(BUZZER_PIN);
    stopBuzzer();
}

void playBuzzer(unsigned int unFreq, int nPlayTime)
{
    int noteDuration = 1000 / nPlayTime; // 음표 설정

    softToneWrite(BUZZER_PIN, unFreq);           // Buzzer PWM 신호 생성
    int pauseBetweenNotes = noteDuration * 1.30; // 음표 지연 시간
    delay(pauseBetweenNotes);
}

void stopBuzzer()
{
    softToneWrite(BUZZER_PIN, 0);
}
void controlBuzzer(int buzzerStatus)
{
    switch (buzzerStatus)
    {
    case ON:
        for (int thisNote = 0; thisNote < melodySize; thisNote++)
        {
            playBuzzer(melody[thisNote], noteDurations[thisNote]); // 멜로디 길이만큼 재생
            stopBuzzer();                                          // 멜로디 정지
        }
        break;
    case OFF:
        stopBuzzer();
        break;
    default:
        break;
    }
}