/**
 * @file can_tx_task.c
 * @brief CAN transmit task implementation.
 * @details This file contains the implementation of the CAN transmit task.
 */

#include "can_tx_task.h"
#include "app_freertos.h"

/**
* @brief Function implementing the sendCANTask thread.
* @param argument: Not used
* @retval None
*/
void StartSendCANTask(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
}