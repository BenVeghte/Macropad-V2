/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Flash_Hold_Pin GPIO_PIN_1
#define Flash_Hold_GPIO_Port GPIOF
#define Flash_WP_Pin GPIO_PIN_0
#define Flash_WP_GPIO_Port GPIOC
#define Flash_CS_Pin GPIO_PIN_1
#define Flash_CS_GPIO_Port GPIOC
#define E_Ch_A_Pin GPIO_PIN_0
#define E_Ch_A_GPIO_Port GPIOA
#define E_Ch_B_Pin GPIO_PIN_1
#define E_Ch_B_GPIO_Port GPIOA
#define E_Switch_Pin GPIO_PIN_2
#define E_Switch_GPIO_Port GPIOA
#define OLED_DC_Pin GPIO_PIN_6
#define OLED_DC_GPIO_Port GPIOA
#define OLED_CS_Pin GPIO_PIN_4
#define OLED_CS_GPIO_Port GPIOC
#define C1_Pin GPIO_PIN_5
#define C1_GPIO_Port GPIOC
#define C2_Pin GPIO_PIN_0
#define C2_GPIO_Port GPIOB
#define C3_Pin GPIO_PIN_1
#define C3_GPIO_Port GPIOB
#define C4_Pin GPIO_PIN_2
#define C4_GPIO_Port GPIOB
#define C5_Pin GPIO_PIN_11
#define C5_GPIO_Port GPIOB
#define R6_Pin GPIO_PIN_12
#define R6_GPIO_Port GPIOB
#define R5_Pin GPIO_PIN_13
#define R5_GPIO_Port GPIOB
#define R4_Pin GPIO_PIN_14
#define R4_GPIO_Port GPIOB
#define R3_Pin GPIO_PIN_15
#define R3_GPIO_Port GPIOB
#define R2_Pin GPIO_PIN_6
#define R2_GPIO_Port GPIOC
#define R1_Pin GPIO_PIN_7
#define R1_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
