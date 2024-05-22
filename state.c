#include "state.h"
#include <stdio.h>

State current_State = IDLE;

void state_update(State new_state)
{
    current_State = new_state;
    switch (current_State)
    {
    case IDLE:
        printf("IDLE MODE");
        break;
    case INPUT_ID:
        printf("Input ID MODE");
        break;
    case INPUT_PASSWORD:
        printf("Input Password MODE");
        break;
    case LOGGED_IN:
        printf("Succesfully Login");
        break;
    case LOGGED_IN_WITH_ADMIN:
        printf("Login with Admin");
        break;
    default:
        break;
    }
}