/** @file timer_events.h
 *  @brief Timer events header file.
 *  @details This file contains the declarations for timer interrupt handlers
 */

#ifndef TIMER_EVENTS_H
#define TIMER_EVENTS_H

#include <stdint.h>

void TIM_SYNC_Elapsed_IRQHandler(void);
void TIM_SYNC_Capture_IRQHandler(uint32_t capture_value);

void TIM_PPS_WDG_Elapsed_IRQHandler(void);

#endif // TIMER_EVENTS_H