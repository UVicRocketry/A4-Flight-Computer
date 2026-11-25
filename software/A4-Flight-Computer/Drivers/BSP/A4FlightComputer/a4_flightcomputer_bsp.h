/**
 * @file a4_flightcomputer_bsp.h
 * @brief A4 Flight Computer Board Support Package header.
 * @details This file contains the interface declarations for the A4 Flight Computer Board Support Package.
 */

#ifndef A4_FLIGHTCOMPUTER_BSP_H
#define A4_FLIGHTCOMPUTER_BSP_H

#include <stdint.h>

/* --- Buzzer --- */
void BSP_Buzzer_On();
void BSP_Buzzer_Start(uint32_t frequency_hz);
void BSP_Buzzer_Stop(void);
void BSP_Buzzer_Off(void);

/* --- LED --- */
void BSP_LED_1_ON();
void BSP_LED_1_OFF();
void BSP_LED_1_TOGGLE();
void BSP_LED_2_ON();
void BSP_LED_2_OFF();
void BSP_LED_2_TOGGLE();

#endif /* A4_FLIGHTCOMPUTER_BSP_H */