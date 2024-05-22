// main.c

// Standard headers
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

// Custom headers
#include "fnd.h"
#include "hc-sr.h"
#include "input.h"
#include "pir.h"
#include "state.h"
#include "user_db.h"

int main(void)
{
    printf("Program Start\n");
    // Module initialization
    if (wiringPiSetupGpio() == -1)
    {
        printf("WiringPi setup failed.\n");
        return 1;
    }
    // Initialize pi modules
    input_init();
    initFnd();
    initUltra(TP_PIN, EP_PIN);
    initPir(PIR_PIN);

    // Variable initialization
    unsigned int fail_count = 0;
    float distance = 0.0;
    unsigned int fndData[2];
    int Pir_val;
    current_State = IDLE;
    // Main loop
    while (1)
    {
        switch (current_State)
        {
        case IDLE:
            Pir_val = readPir(PIR_PIN);
            if (Pir_val == HIGH)
            {
                printf("main() motion detected. distance is close?");
                delay(1000);
                distance = getDistance(TP_PIN, EP_PIN);
                if (distance <= 500 && distance <= 40)
                {
                    printf("Distance : %.2f(cm)\n", distance);
                    current_State = INPUT_ID;
                }
            }
            break;
        case INPUT_ID:
        case INPUT_PASSWORD:
            check_buttons();
            parseToFnd(fndData);
            break;
        case LOGGED_IN:
            printf("Logged in\n");
            break;
        default:
            break;
        }
        for (int i = 0; i < 6; i++)
        {
            FndData(i, fndData);
        }
        delay(10);
    }
    return 0;
}