/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for sensorSampleTask */
osThreadId_t sensorSampleTaskHandle;
const osThreadAttr_t sensorSampleTask_attributes = {
  .name = "sensorSampleTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for buzzerTask */
osThreadId_t buzzerTaskHandle;
const osThreadAttr_t buzzerTask_attributes = {
  .name = "buzzerTask",
  .priority = (osPriority_t) osPriorityBelowNormal,
  .stack_size = 128 * 4
};
/* Definitions for storageTask */
osThreadId_t storageTaskHandle;
const osThreadAttr_t storageTask_attributes = {
  .name = "storageTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for flightStateMessageTask */
osThreadId_t flightStateMessageTaskHandle;
const osThreadAttr_t flightStateMessageTask_attributes = {
  .name = "flightStateMessageTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for sendCANTask */
osThreadId_t sendCANTaskHandle;
const osThreadAttr_t sendCANTask_attributes = {
  .name = "sendCANTask",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 128 * 4
};
/* Definitions for receiveCANTask */
osThreadId_t receiveCANTaskHandle;
const osThreadAttr_t receiveCANTask_attributes = {
  .name = "receiveCANTask",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of sensorSampleTask */
  sensorSampleTaskHandle = osThreadNew(StartSensorSampleTask, NULL, &sensorSampleTask_attributes);

  /* creation of buzzerTask */
  buzzerTaskHandle = osThreadNew(StartBuzzerTask, NULL, &buzzerTask_attributes);

  /* creation of storageTask */
  storageTaskHandle = osThreadNew(StartStorageTask, NULL, &storageTask_attributes);

  /* creation of flightStateMessageTask */
  flightStateMessageTaskHandle = osThreadNew(StartFlightStateMessageTask, NULL, &flightStateMessageTask_attributes);

  /* creation of sendCANTask */
  sendCANTaskHandle = osThreadNew(StartSendCANTask, NULL, &sendCANTask_attributes);

  /* creation of receiveCANTask */
  receiveCANTaskHandle = osThreadNew(StartReceiveCANTask, NULL, &receiveCANTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartSensorSampleTask */
/**
* @brief Function implementing the sensorSampleTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSensorSampleTask */
void StartSensorSampleTask(void *argument)
{
  /* USER CODE BEGIN sensorSampleTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END sensorSampleTask */
}

/* USER CODE BEGIN Header_StartBuzzerTask */
/**
* @brief Function implementing the buzzerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBuzzerTask */
void StartBuzzerTask(void *argument)
{
  /* USER CODE BEGIN buzzerTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END buzzerTask */
}

/* USER CODE BEGIN Header_StartStorageTask */
/**
* @brief Function implementing the storageTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartStorageTask */
void StartStorageTask(void *argument)
{
  /* USER CODE BEGIN storageTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END storageTask */
}

/* USER CODE BEGIN Header_StartFlightStateMessageTask */
/**
* @brief Function implementing the flightStateMessageTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartFlightStateMessageTask */
void StartFlightStateMessageTask(void *argument)
{
  /* USER CODE BEGIN flightStateMessageTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END flightStateMessageTask */
}

/* USER CODE BEGIN Header_StartSendCANTask */
/**
* @brief Function implementing the sendCANTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSendCANTask */
void StartSendCANTask(void *argument)
{
  /* USER CODE BEGIN sendCANTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END sendCANTask */
}

/* USER CODE BEGIN Header_StartReceiveCANTask */
/**
* @brief Function implementing the receiveCANTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReceiveCANTask */
void StartReceiveCANTask(void *argument)
{
  /* USER CODE BEGIN receiveCANTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END receiveCANTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

