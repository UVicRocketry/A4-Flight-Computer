/**
 * @file can_rx_task.c
 * @brief CAN receive task implementation.
 * @details This file contains the implementation of the CAN receive task.
 */

#include "can_rx_task.h"
#include "app_freertos.h"

/**
* @brief Function implementing the receiveCANTask thread.
* @param argument: Not used
* @retval None
*/
void StartReceiveCANTask(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
}