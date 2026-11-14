/**
 * @file    flight_fsm.h
 * @brief   Flight state machine header file
 * @details This file contains:
 *           - The definition of the flight state machine structure
 *           - Flight state definitions
 *           - Function prototypes for initializing and updating the flight state machine
 */

#ifndef FLIGHT_FSM_H
#define FLIGHT_FSM_H

typedef enum {
    FLIGHT_STATE_INIT,
    FLIGHT_STATE_GROUND_HANDLING,
    FLIGHT_STATE_PRE_LAUNCH,
    FLIGHT_STATE_POWERED_ASCENT,
    FLIGHT_STATE_UNPOWERED_ASCENT,
    FLIGHT_STATE_BALLISTIC_DESCENT,
    FLIGHT_STATE_DESCENT_DROGUE,
    FLIGHT_STATE_DESCENT_MAIN,
    FLIGHT_STATE_RECOVERY
} flight_state_t;

typedef enum {
    FLIGHT_EVENT_BOOT,
    FLIGHT_EVENT_ARM,
    FLIGHT_EVENT_LAUNCH,
    FLIGHT_EVENT_BURNOUT,
    FLIGHT_EVENT_APOGEE,
    FLIGHT_EVENT_DROGUE,
    FLIGHT_EVENT_MAIN,
    FLIGHT_EVENT_TOUCHDOWN
} flight_event_t;

typedef struct {
    flight_state_t previous_state;
    flight_state_t current_state;
} flight_fsm_t;

flight_state_t flight_fsm_transition(flight_event_t event);
flight_state_t flight_fsm_get_current_state(void);
flight_state_t flight_fsm_get_previous_state(void);

#endif /* FLIGHT_FSM_H */