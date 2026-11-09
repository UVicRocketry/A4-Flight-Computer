/**
 * @file sensor_task.c
 * @brief Sensor task implementation.
 * @details This file contains the implementation of the sensor task.
 */

#include "sensor_task.h"
#include "app_freertos.h"

/**
* @brief Function implementing the sensorSampleTask thread.
* @param argument: Not used
* @retval None
*/
void StartSensorSampleTask(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
}
