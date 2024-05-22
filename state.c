#include "state.h"

State current_State = IDLE;

void state_update(State new_state)
{
    State tmp = current_State;
    current_State = new_state;

    printf("State Updated : %d => %d", tmp, current_State);
}