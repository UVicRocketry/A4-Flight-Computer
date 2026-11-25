/**
 * @file bsp_buzzer.c
 * @brief Buzzer board support package implementation.
 * @details This file contains the implementation of the buzzer board support package.
 */

#include "main.h"
#include "a4_flightcomputer_bsp.h"

#define TIMER_CLOCK_HZ 3000000 // 3 MHz

extern TIM_HandleTypeDef TIM_BUZZ;

void BSP_Buzzer_On()
{
    HAL_TIM_Base_Start(&TIM_BUZZ);
}

void BSP_Buzzer_Start(uint32_t frequency_hz)
{
    // calculate the correct timer period for the desired frequency
    uint32_t period = (TIMER_CLOCK_HZ / frequency_hz);

    __HAL_TIM_SET_AUTORELOAD(&TIM_BUZZ, period - 1);
    __HAL_TIM_SET_COMPARE(&TIM_BUZZ, TIM_CHANNEL_4, period / 2); // 50% duty cycle
    HAL_TIM_PWM_Start(&TIM_BUZZ, TIM_CHANNEL_4);
}

void BSP_Buzzer_Stop(void)
{
    HAL_TIM_PWM_Stop(&TIM_BUZZ, TIM_CHANNEL_4);
}

void BSP_Buzzer_Off(void)
{
    HAL_TIM_PWM_Stop(&TIM_BUZZ, TIM_CHANNEL_4);
    HAL_TIM_Base_Stop(&TIM_BUZZ);
}
