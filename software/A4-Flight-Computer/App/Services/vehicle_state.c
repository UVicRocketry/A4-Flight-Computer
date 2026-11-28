/**
 * @file vehicle_state.c
 * @brief Vehicle state implementation.
 * @details This file contains the implementation of the vehicle state management.
 */

#include <stddef.h>
#include "vehicle_state.h"

static vehicle_state_t current_vehicle_state = {
    .psu_state_valid = false,
    .psu_state = {0},
    .self_test_completed = false, // TODO: if self-tests happen across multiple tasks, how to track if all self tests are done?
    .self_test_error_bits = 0xFF,    // TODO: all self-test error bits should be set initially, each one should be cleared as the corresponding self-test passes.
    .flight_state_fsm = {0},
};

bool VehicleState_GetCurrentState(vehicle_state_t *state)
{
    if (state == NULL)
    {
        return false;
    }
    *state = current_vehicle_state;
    return true;
}

void VehicleState_SetPSUState(psu_state_t *psu_state)
{
    if (psu_state == NULL)
    {
        return;
    }
    current_vehicle_state.psu_state = *psu_state;
    current_vehicle_state.psu_state_valid = true;
}

bool VehicleState_GetSelfTestResult(self_test_result_t *result)
{
    if (result == NULL)
    {
        return false;
    }

    if (!current_vehicle_state.self_test_completed)
    {
        return false;
    }

    *result = current_vehicle_state.self_test_error_bits;
    return true;
}

void VehicleState_SetSelfTestBit(self_test_result_t mask)
{
    current_vehicle_state.self_test_error_bits |= mask;
}

void VehicleState_ClearSelfTestBit(self_test_result_t mask)
{
    current_vehicle_state.self_test_error_bits &= ~mask;
}
