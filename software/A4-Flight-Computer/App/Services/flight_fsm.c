/** @file    flight_fsm.c
 *  @brief   Flight state machine implementation
 *  @details This file contains the implementation of the flight state machine.
 */

#include "flight_fsm.h"

static flight_fsm_t flight_fsm = {
    .previous_state = FLIGHT_STATE_INIT,
    .current_state = FLIGHT_STATE_INIT
};

flight_state_t flight_fsm_transition(flight_event_t event) {
    flight_state_t last_state = flight_fsm.current_state;

    switch (flight_fsm.current_state) {
        case FLIGHT_STATE_INIT:
            if (event == FLIGHT_EVENT_BOOT) {
                flight_fsm.current_state = FLIGHT_STATE_GROUND_HANDLING;
            }
            break;

        case FLIGHT_STATE_GROUND_HANDLING:
            if (event == FLIGHT_EVENT_ARM) {
                flight_fsm.current_state = FLIGHT_STATE_PRE_LAUNCH;
            }
            break;

        case FLIGHT_STATE_PRE_LAUNCH:
            if (event == FLIGHT_EVENT_LAUNCH) {
                flight_fsm.current_state = FLIGHT_STATE_POWERED_ASCENT;
            }
            break;

        case FLIGHT_STATE_POWERED_ASCENT:
            if (event == FLIGHT_EVENT_BURNOUT) {
                flight_fsm.current_state = FLIGHT_STATE_UNPOWERED_ASCENT;
            } else if (event == FLIGHT_EVENT_DROGUE) {
                flight_fsm.current_state = FLIGHT_STATE_DESCENT_DROGUE;
            } else if (event == FLIGHT_EVENT_MAIN) {
                flight_fsm.current_state = FLIGHT_STATE_DESCENT_MAIN;
            }
            break;

        case FLIGHT_STATE_UNPOWERED_ASCENT:
            if (event == FLIGHT_EVENT_APOGEE) {
                flight_fsm.current_state = FLIGHT_STATE_BALLISTIC_DESCENT;
            } else if (event == FLIGHT_EVENT_DROGUE) {
                flight_fsm.current_state = FLIGHT_STATE_DESCENT_DROGUE;
            } else if (event == FLIGHT_EVENT_MAIN) {
                flight_fsm.current_state = FLIGHT_STATE_DESCENT_MAIN;
            }
            break;

        case FLIGHT_STATE_BALLISTIC_DESCENT:
            if (event == FLIGHT_EVENT_DROGUE) {
                flight_fsm.current_state = FLIGHT_STATE_DESCENT_DROGUE;
            } else if (event == FLIGHT_EVENT_MAIN) {
                flight_fsm.current_state = FLIGHT_STATE_DESCENT_MAIN;
            } else if (event == FLIGHT_EVENT_TOUCHDOWN) {
                flight_fsm.current_state = FLIGHT_STATE_RECOVERY;
            }
            break;

        case FLIGHT_STATE_DESCENT_DROGUE:
            if (event == FLIGHT_EVENT_MAIN) {
                flight_fsm.current_state = FLIGHT_STATE_DESCENT_MAIN;
            } else if (event == FLIGHT_EVENT_TOUCHDOWN) {
                flight_fsm.current_state = FLIGHT_STATE_RECOVERY;
            }
            break;

        case FLIGHT_STATE_DESCENT_MAIN:
            if (event == FLIGHT_EVENT_TOUCHDOWN) {
                flight_fsm.current_state = FLIGHT_STATE_RECOVERY;
            }
            break;

        default:
            // Handle unexpected states or events
            break;
    }

    if (flight_fsm.current_state != last_state) {
        flight_fsm.previous_state = last_state;
    }

    return flight_fsm.current_state;
}

flight_state_t flight_fsm_get_current_state() {
    return flight_fsm.current_state;
}

flight_state_t flight_fsm_get_previous_state() {
    return flight_fsm.previous_state;
}