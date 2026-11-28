/*
 * @file bsp_sd.c
 * @brief SD card board support package implementation.
 * @details This file contains the implementation of the SD card board support package.
 */

#include "main.h"
#include "a4_flightcomputer_bsp.h"
#include "stm32h5xx_hal_sd.h"

extern SD_HandleTypeDef hsd1;

static void BSP_SD_ResetController(void)
{
    __HAL_RCC_SDMMC1_FORCE_RESET();
    __HAL_RCC_SDMMC1_RELEASE_RESET();
}

uint32_t BSP_SD_Init(void)
{
    if (hsd1.State != HAL_SD_STATE_RESET)
    {
        if (HAL_SD_DeInit(&hsd1) != HAL_OK)
        {
            return 1;
        }
    }

    BSP_SD_ResetController();

    // Initialize the SD card using the HAL library
    if (HAL_SD_Init(&hsd1) != HAL_OK)
    {
        // Initialization failed
        HAL_SD_DeInit(&hsd1);
        return 1;
    }

    // SD card initialized successfully
    return 0; // Return success code
}

bool BSP_SD_Ready(void)
{
    // Check the status of the SD card using the HAL library
    if (HAL_SD_GetCardState(&hsd1) == HAL_SD_CARD_TRANSFER)
    {
        // SD card is ready for data transfer
        return true; // Return success code
    }
    else
    {
        // SD card is not ready or an error occurred
        return false; // Return an error code or handle the error as needed
    }
}