#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>

#define BUTTON1 12
#define BUTTON2 16
#define BUTTON3 20
#define BUTTON4 21
#define BOUNCE_TIMER 200

typedef uint8_t u8;

u8 keyState1 = HIGH;
u8 keyState2 = HIGH;
u8 keyState3 = HIGH;
u8 keyState4 = HIGH;

u8 bounceCount1 = 0;
u8 bounceCount2 = 0;
u8 bounceCount3 = 0;
u8 bounceCount4 = 0;

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

    printf("Setup complete\n");
}

void loop() {
    u8 key1 = digitalRead(BUTTON1);
    u8 key2 = digitalRead(BUTTON2);
    u8 key3 = digitalRead(BUTTON3);
    u8 key4 = digitalRead(BUTTON4);

    // Button 1
    if (key1 == LOW) {
        if (keyState1 == HIGH) {
            if (bounceCount1 == 0) {
                bounceCount1 = BOUNCE_TIMER;
                printf("Button 1 Push\n");
                keyState1 = key1;
            } else {
                bounceCount1--;
            }
        }
    } else {
        if (keyState1 == LOW) {
            printf("Button 1 Pull\n");
            keyState1 = key1;
        }
    }

    // Button 2
    if (key2 == LOW) {
        if (keyState2 == HIGH) {
            if (bounceCount2 == 0) {
                bounceCount2 = BOUNCE_TIMER;
                printf("Button 2 Push\n");
                keyState2 = key2;
            } else {
                bounceCount2--;
            }
        }
    } else {
        if (keyState2 == LOW) {
            printf("Button 2 Pull\n");
            keyState2 = key2;
        }
    }

    // Button 3
    if (key3 == LOW) {
        if (keyState3 == HIGH) {
            if (bounceCount3 == 0) {
                bounceCount3 = BOUNCE_TIMER;
                printf("Button 3 Push\n");
                keyState3 = key3;
            } else {
                bounceCount3--;
            }
        }
    } else {
        if (keyState3 == LOW) {
            printf("Button 3 Pull\n");
            keyState3 = key3;
        }
    }

    // Button 4
    if (key4 == LOW) {
        if (keyState4 == HIGH) {
            if (bounceCount4 == 0) {
                bounceCount4 = BOUNCE_TIMER;
                printf("Button 4 Push\n");
                keyState4 = key4;
            } else {
                bounceCount4--;
            }
        }
    } else {
        if (keyState4 == LOW) {
            printf("Button 4 Pull\n");
            keyState4 = key4;
        }
    }

    delay(1); // Add a small delay to avoid excessive CPU usage
}

int main() {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
