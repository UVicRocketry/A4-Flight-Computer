/**
 * @file buzzer_task.c
 * @brief Buzzer task implementation.
 * @details This file contains the implementation of the buzzer task.
 */

 #include "buzzer_task.h"
 #include "app_freertos.h"
#include "main.h"

/**
* @brief Function implementing the buzzerTask thread.
* @param argument: Not used
* @retval None
*/
void StartBuzzerTask(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(500);
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
  }
}