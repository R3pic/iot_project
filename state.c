#include "state.h"
#include <stdio.h>

State current_State = IDLE;

void state_update(State new_state)
{
    current_State = new_state;
    switch (new_state)
    {
    case IDLE:
        printf("IDLE MODE\n");
        break;
    case INPUT_ID:
        printf("Input ID MODE\n");
        break;
    case INPUT_PASSWORD:
        printf("Input Password MODE\n");
        break;
    case LOGGED_IN:
        printf("Succesfully Login\n");
        break;
    case LOGGED_IN_WITH_ADMIN:
        printf("Login with Admin\n");
        break;
    default:
        break;
    }
}