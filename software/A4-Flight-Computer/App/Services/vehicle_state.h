/**
 * @file vehicle_state.h
 * @brief Vehicle state management.
 * @details This file contains the interface for managing or checking the state of the vehicle.
 */

#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

#include <stdbool.h>
#include <stdint.h>
#include "flight_fsm.h"

typedef struct
{
    uint8_t channel_states;
    uint16_t temp_psu;
    uint16_t temp_cell_1;
    uint16_t temp_cell_2;
    uint16_t v_bat_mV;
} psu_state_t;

#define SELF_TEST_ERROR_NONE 0b00000000
#define SELF_TEST_ERROR_SD_CARD 0b00000001         // SD card test failed (unable to read/write to SD card or card not present)
#define SELF_TEST_ERROR_CAN_BUS 0b00000010         // CAN bus test failed (no ACKs received to test messages, or failed to send test messages)
#define SELF_TEST_ERROR_BREAKAWAY 0b00000100       // no continuity on breakaway sense connector
#define SELF_TEST_ERROR_ONBOARD_SENSORS 0b00001000 // One or more on-board sensors test failed (unable to read from sensor, or sensor reading out of range)
#define SELF_TEST_ERROR_PSU 0b00010000             // no status message received from PSU module
#define SELF_TEST_ERROR_BATTERY 0b00100000         // battery voltage out of range (too low or too high)
#define SELF_TEST_ERROR_TELEMETRY 0b01000000       // no status messagee received from telemetry module
#define SELF_TEST_ERROR_OTHER 0b10000000           // other self-test error (not specified)

typedef uint8_t self_test_result_t;

typedef struct
{
    bool psu_state_valid;
    psu_state_t psu_state;
    bool self_test_completed;                // indicates if the self-test has been completed.
    self_test_result_t self_test_error_bits; // bitfield representing different self-test errors.
    flight_fsm_t flight_state_fsm;
    bool breakaway_continuity; // indicates if the breakaway sense connector has continuity (true) or not (false).
} vehicle_state_t;

bool VehicleState_GetCurrentState(vehicle_state_t *state);
void VehicleState_SetPSUState(psu_state_t *psu_state);
bool VehicleState_GetSelfTestResult(self_test_result_t *result);
void VehicleState_SetSelfTestBit(self_test_result_t mask);
void VehicleState_ClearSelfTestBit(self_test_result_t mask);

#endif /* VEHICLE_STATE_H */