#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#define BUTTON1 12
#define BUTTON2 16
#define BUTTON3 20
#define BUTTON4 21
#define BOUNCE_TIME 200 // Bouncing time in milliseconds

typedef uint8_t u8;

u8 keyState1 = HIGH;
u8 keyState2 = HIGH;
u8 keyState3 = HIGH;
u8 keyState4 = HIGH;

unsigned long lastInterruptTime1 = 0;
unsigned long lastInterruptTime2 = 0;
unsigned long lastInterruptTime3 = 0;
unsigned long lastInterruptTime4 = 0;

unsigned long getmillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

void handleButtonPress1() {
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime1 > BOUNCE_TIME) {
        if (keyState1 == HIGH) {
            printf("Button 1 Push\n");
            keyState1 = LOW;
        } else {
            printf("Button 1 Pull\n");
            keyState1 = HIGH;
        }
        lastInterruptTime1 = interruptTime;
    }
}

void handleButtonPress2() {
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime2 > BOUNCE_TIME) {
        if (keyState2 == HIGH) {
            printf("Button 2 Push\n");
            keyState2 = LOW;
        } else {
            printf("Button 2 Pull\n");
            keyState2 = HIGH;
        }
        lastInterruptTime2 = interruptTime;
    }
}

void handleButtonPress3() {
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime3 > BOUNCE_TIME) {
        if (keyState3 == HIGH) {
            printf("Button 3 Push\n");
            keyState3 = LOW;
        } else {
            printf("Button 3 Pull\n");
            keyState3 = HIGH;
        }
        lastInterruptTime3 = interruptTime;
    }
}

void handleButtonPress4() {
    unsigned long interruptTime = getmillis();
    if (interruptTime - lastInterruptTime4 > BOUNCE_TIME) {
        if (keyState4 == HIGH) {
            printf("Button 4 Push\n");
            keyState4 = LOW;
        } else {
            printf("Button 4 Pull\n");
            keyState4 = HIGH;
        }
        lastInterruptTime4 = interruptTime;
    }
}

void setup() {
    wiringPiSetupGpio();

    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    pinMode(BUTTON4, INPUT);

    pullUpDnControl(BUTTON1, PUD_UP);
    pullUpDnControl(BUTTON2, PUD_UP);
    pullUpDnControl(BUTTON3, PUD_UP);
    pullUpDnControl(BUTTON4, PUD_UP);

    wiringPiISR(BUTTON1, INT_EDGE_BOTH, &handleButtonPress1);
    wiringPiISR(BUTTON2, INT_EDGE_BOTH, &handleButtonPress2);
    wiringPiISR(BUTTON3, INT_EDGE_BOTH, &handleButtonPress3);
    wiringPiISR(BUTTON4, INT_EDGE_BOTH, &handleButtonPress4);

    printf("Setup complete\n");
}

int main() {
    setup();
    while (1) {
        // Main loop can be used for other tasks
        delay(100); // Adding a small delay to reduce CPU usage
    }
    return 0;
}
