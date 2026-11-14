/** @file timer_events.c
 *  @brief Timer events implementation file.
 *  @details This file contains the implementations for timer interrupt handlers.
 */

#include "timer_events.h"

void TIM_SYNC_Elapsed_IRQHandler(void)
{
    // Implementation for TIM_SYNC elapsed interrupt
}

void TIM_SYNC_Capture_IRQHandler(uint32_t capture_value)
{
    // Implementation for TIM_SYNC capture interrupt
}

void TIM_PPS_WDG_Elapsed_IRQHandler(void)
{
    // Implementation for TIM_PPS_WDG elapsed interrupt
}