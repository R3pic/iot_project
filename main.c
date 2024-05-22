// main.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

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
    input_init();

    // Variable initialization
    unsigned int fail_count = 0;

    int user_id, password;

    // Main loop
    while (1)
    {
        check_buttons();
        delay(50);
    }
    return 0;
}