#ifndef STATE_H
#define STATE_H

typedef enum {
    IDLE,
    INPUT_ID,
    INPUT_PASSWORD,
    LOGGED_IN,
    LOGGED_IN_WITH_ADMIN,
} State;

extern State current_State;

#endif