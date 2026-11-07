/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TIM_SYNC htim3
#define TIM_PPS_WDG htim6
#define TIM_BUZZ htim2
#define ADXL_INT1_Pin GPIO_PIN_4
#define ADXL_INT1_GPIO_Port GPIOA
#define ADXL_INT2_Pin GPIO_PIN_5
#define ADXL_INT2_GPIO_Port GPIOA
#define LSM6_INT1_Pin GPIO_PIN_6
#define LSM6_INT1_GPIO_Port GPIOA
#define LSM6_INT2_Pin GPIO_PIN_7
#define LSM6_INT2_GPIO_Port GPIOA
#define BUZZ_OUT_Pin GPIO_PIN_4
#define BUZZ_OUT_GPIO_Port GPIOC
#define BMP_INT_Pin GPIO_PIN_0
#define BMP_INT_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_2
#define LED2_GPIO_Port GPIOB
#define CAN_SHDN_Pin GPIO_PIN_14
#define CAN_SHDN_GPIO_Port GPIOB
#define CAN_STB_Pin GPIO_PIN_15
#define CAN_STB_GPIO_Port GPIOB
#define PPS_IN_Pin GPIO_PIN_6
#define PPS_IN_GPIO_Port GPIOC
#define SYNC_OUT_Pin GPIO_PIN_7
#define SYNC_OUT_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
