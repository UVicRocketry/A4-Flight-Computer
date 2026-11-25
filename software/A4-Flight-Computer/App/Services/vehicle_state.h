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

typedef struct
{
    bool psu_state_valid;
    psu_state_t psu_state;
    flight_fsm_t flight_state_fsm;
} vehicle_state_t;

bool VehicleState_GetCurrentState(vehicle_state_t *state);
void VehicleState_SetPSUState(psu_state_t *psu_state);

#endif /* VEHICLE_STATE_H */