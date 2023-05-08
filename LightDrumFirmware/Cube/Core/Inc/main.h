/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MainWrapper.h"
#include "Utils.h"
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
#define GRAPH_CLK_Pin GPIO_PIN_2
#define GRAPH_CLK_GPIO_Port GPIOE
#define GRAPH_SDI_Pin GPIO_PIN_6
#define GRAPH_SDI_GPIO_Port GPIOE
#define STRIP_ESHDN_Pin GPIO_PIN_0
#define STRIP_ESHDN_GPIO_Port GPIOC
#define VDD_PG_Pin GPIO_PIN_1
#define VDD_PG_GPIO_Port GPIOC
#define VDDA_PG_Pin GPIO_PIN_2
#define VDDA_PG_GPIO_Port GPIOC
#define STRIP_PG_Pin GPIO_PIN_3
#define STRIP_PG_GPIO_Port GPIOC
#define SOLID_LGT_MON_Pin GPIO_PIN_0
#define SOLID_LGT_MON_GPIO_Port GPIOA
#define MIDI_OUT_Pin GPIO_PIN_2
#define MIDI_OUT_GPIO_Port GPIOA
#define MIDI_IN_Pin GPIO_PIN_3
#define MIDI_IN_GPIO_Port GPIOA
#define STRIP1_MON_Pin GPIO_PIN_4
#define STRIP1_MON_GPIO_Port GPIOA
#define STRIP5_MON_Pin GPIO_PIN_5
#define STRIP5_MON_GPIO_Port GPIOA
#define STRIP2_MON_Pin GPIO_PIN_6
#define STRIP2_MON_GPIO_Port GPIOA
#define STRIP6_MON_Pin GPIO_PIN_7
#define STRIP6_MON_GPIO_Port GPIOA
#define STRIP7_MON_Pin GPIO_PIN_4
#define STRIP7_MON_GPIO_Port GPIOC
#define STRIP3_MON_Pin GPIO_PIN_5
#define STRIP3_MON_GPIO_Port GPIOC
#define STRIP4_MON_Pin GPIO_PIN_0
#define STRIP4_MON_GPIO_Port GPIOB
#define STRIP8_MON_Pin GPIO_PIN_1
#define STRIP8_MON_GPIO_Port GPIOB
#define XLR_SEL_IND_Pin GPIO_PIN_9
#define XLR_SEL_IND_GPIO_Port GPIOE
#define HP_SEL_IND_Pin GPIO_PIN_13
#define HP_SEL_IND_GPIO_Port GPIOE
#define MENU_LEFT_Pin GPIO_PIN_15
#define MENU_LEFT_GPIO_Port GPIOE
#define MENU_LEFT_EXTI_IRQn EXTI15_10_IRQn
#define DMX_TX_Pin GPIO_PIN_10
#define DMX_TX_GPIO_Port GPIOB
#define ENC2_B_Pin GPIO_PIN_12
#define ENC2_B_GPIO_Port GPIOB
#define ENC2_A_Pin GPIO_PIN_13
#define ENC2_A_GPIO_Port GPIOB
#define ENC2_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC1_A_Pin GPIO_PIN_14
#define ENC1_A_GPIO_Port GPIOB
#define ENC1_A_EXTI_IRQn EXTI15_10_IRQn
#define ENC2_SW_Pin GPIO_PIN_8
#define ENC2_SW_GPIO_Port GPIOD
#define ENC2_SW_EXTI_IRQn EXTI9_5_IRQn
#define MENU_RIGHT_Pin GPIO_PIN_9
#define MENU_RIGHT_GPIO_Port GPIOD
#define MENU_RIGHT_EXTI_IRQn EXTI9_5_IRQn
#define MENU_ACT_Pin GPIO_PIN_10
#define MENU_ACT_GPIO_Port GPIOD
#define MENU_ACT_EXTI_IRQn EXTI15_10_IRQn
#define MENU_BACK_Pin GPIO_PIN_11
#define MENU_BACK_GPIO_Port GPIOD
#define MENU_BACK_EXTI_IRQn EXTI15_10_IRQn
#define MENU_UP_Pin GPIO_PIN_12
#define MENU_UP_GPIO_Port GPIOD
#define MENU_UP_EXTI_IRQn EXTI15_10_IRQn
#define ENC1_B_Pin GPIO_PIN_13
#define ENC1_B_GPIO_Port GPIOD
#define GRAPH_LE_Pin GPIO_PIN_14
#define GRAPH_LE_GPIO_Port GPIOD
#define GRAPH_OE_Pin GPIO_PIN_15
#define GRAPH_OE_GPIO_Port GPIOD
#define PWM_OE_Pin GPIO_PIN_6
#define PWM_OE_GPIO_Port GPIOC
#define DIAG_DEBUG_Pin GPIO_PIN_8
#define DIAG_DEBUG_GPIO_Port GPIOC
#define DIAG_STATUS_Pin GPIO_PIN_9
#define DIAG_STATUS_GPIO_Port GPIOC
#define SCREEN_TX_Pin GPIO_PIN_9
#define SCREEN_TX_GPIO_Port GPIOA
#define SCREEN_RX_Pin GPIO_PIN_10
#define SCREEN_RX_GPIO_Port GPIOA
#define DMX_RX_Pin GPIO_PIN_11
#define DMX_RX_GPIO_Port GPIOC
#define STRIP_PWR_Pin GPIO_PIN_0
#define STRIP_PWR_GPIO_Port GPIOD
#define SDIO_CD_Pin GPIO_PIN_1
#define SDIO_CD_GPIO_Port GPIOD
#define SDIO_CD_EXTI_IRQn EXTI1_IRQn
#define MENU_DOWN_Pin GPIO_PIN_3
#define MENU_DOWN_GPIO_Port GPIOD
#define MENU_DOWN_EXTI_IRQn EXTI3_IRQn
#define ENC1_SW_Pin GPIO_PIN_5
#define ENC1_SW_GPIO_Port GPIOD
#define ENC1_SW_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
