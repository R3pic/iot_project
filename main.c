// main.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

#include "fnd.h"
#include "input.h"
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

    // Variable initialization
    unsigned int fail_count = 0;

    unsigned int fndData[2];

    current_State = INPUT_ID;
    // Main loop
    while (1)
    {
        switch (current_State)
        {
        case IDLE:
            printf("Idle\n");
        case INPUT_ID:
        case INPUT_PASSWORD:
            check_buttons();
            parseToFnd(fndData);
            for (int i = 0; i < 6; i++)
            {
                FndData(i, fndData);
            }
            break;
        case LOGGED_IN:
            printf("Logged in\n");
            delay(50);
            break;
        default:
            break;
        }
        delay(50);
    }
    return 0;
}