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
    .flight_state_fsm = {0}};

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
