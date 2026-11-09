/**
 * @file flight_state_message_task.c
 * @brief Flight state message task implementation.
 * @details This file contains the implementation of the flight state message task.
 */

#include "flight_state_message_task.h"
#include "app_freertos.h"

/**
* @brief Function implementing the flightStateMessageTask thread.
* @param argument: Not used
* @retval None
*/
void StartFlightStateMessageTask(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
}
