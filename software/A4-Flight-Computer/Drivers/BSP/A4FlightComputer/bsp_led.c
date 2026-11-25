/**
 * @file bsp_led.c
 * @brief LED board support package implementation.
 * @details This file contains the implementation of the LED board support package.
 */

#include "main.h"
#include "stm32h5xx_hal.h"
#include "a4_flightcomputer_bsp.h"

void BSP_LED_1_ON()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
}

void BSP_LED_1_OFF()
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
}

void BSP_LED_1_TOGGLE()
{
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}

void BSP_LED_2_ON()
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
}

void BSP_LED_2_OFF()
{
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
}

void BSP_LED_2_TOGGLE()
{
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
}
