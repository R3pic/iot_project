#include "state.h"
#include "uart.h"
#include <stdio.h>
#include <wiringPi.h>

State current_State = IDLE;

void state_update(State new_state)
{
    current_State = new_state;
    switch (new_state)
    {
    case IDLE:
        printf("IDLE MODE\n");
        uart_send("LCD 1 IDLE MODE\n");
        break;
    case INPUT_ID:
        printf("Input ID MODE\n");
        uart_send("LCD 1 Input ID MODE\n");
        delay(1000);
        uart_send("MOTOR 1\n");
        break;
    case INPUT_PASSWORD:
        printf("Input Password MODE\n");
        uart_send("LCD 1 Input PW MODE\n");
        break;
    case LOGGED_IN:
        printf("Succesfully Login\n");
        uart_send("LCD 1 Login\n");
        delay(1000);
        uart_send("MOTOR 0\n");
        break;
    case LOGGED_IN_WITH_ADMIN:
        printf("Login with Admin\n");
        uart_send("LCD 1 Login with Admin\n");
        break;
    default:
        break;
    }
}