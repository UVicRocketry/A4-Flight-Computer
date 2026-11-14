/**
 * @file storage_task.c
 * @brief Storage task implementation.
 * @details This file contains the implementation of the storage task.
 */

#include "storage_task.h"
#include "app_freertos.h"

/**
* @brief Function implementing the storageTask thread.
* @param argument: Not used
* @retval None
*/
void StartStorageTask(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
}