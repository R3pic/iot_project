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
#include "uart.h"
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
    init_uart();
    input_init();
    initFnd();
    initUltra(TP_PIN, EP_PIN);
    initPir(PIR_PIN);

    // Variable initialization
    unsigned int fail_count = 0;
    float distance = 0.0;
    unsigned int fndData[2];
    int Pir_val;
    state_update(IDLE);
    // Main loop
    while (1)
    {
        switch (current_State)
        {
        case IDLE:
            Pir_val = readPir(PIR_PIN);
            if (Pir_val == HIGH)
            {
                printf("main() motion detected. distance is close?\n");
                delay(1000);
                distance = getDistance(TP_PIN, EP_PIN);
                if (distance <= 500 && distance <= 40)
                {
                    printf("Distance : %.2f(cm)\n", distance);
                    state_update(INPUT_ID);
                }
            }
            break;
        case INPUT_ID:
            check_buttons();
            parseToFnd(fndData);
            break;
        case INPUT_PASSWORD:
            check_buttons();
            parseToFnd(fndData);
            break;
        case LOGGED_IN:
            uart_send("LCD 1\n"); // 로그인하면 lcd에 텍스트 띄우기.
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