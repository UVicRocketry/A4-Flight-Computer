/** @file exti_events.c
 *  @brief EXTI interrupt event handling
 *  @details This file contains the implementations for EXTI interrupt handlers.
 */

#include "exti_events.h"

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    switch (pin)
    {
        case ADXL_INT1_Pin:
            //GpioEvents_OnAdxlInt1();
            break;

        case ADXL_INT2_Pin:
            //GpioEvents_OnAdxlInt2();
            break;

        case LSM6_INT1_Pin:
            //GpioEvents_OnLsm6Int1();
            break;
        
        case LSM6_INT2_Pin:
            //GpioEvents_OnLsm6Int2();
            break;

        case BMP_INT_Pin:
            //GpioEvents_OnBmpInt();
            break;

        case BRKWAY_SENSE_Pin:
            //GpioEvents_OnBrkwaySense();
            break;

        default:
            break;
    }
}