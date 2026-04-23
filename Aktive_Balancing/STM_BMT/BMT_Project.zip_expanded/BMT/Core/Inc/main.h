/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MCP4725.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

extern CAN_RxHeaderTypeDef rxHeader; 			//CAN Bus Receive Header
extern CAN_TxHeaderTypeDef txHeader; 			//CAN Bus Transmit Header
extern uint8_t canRX[8];						// = {0,0,0,0,0,0,0,0};  	//CAN Bus Receive Buffer
extern CAN_FilterTypeDef canfil; 				//CAN Bus Filter
extern uint32_t canMailbox; 					//CAN Bus Mail box variable
extern HAL_StatusTypeDef status_value;

/*extern struct Toggle_Object{
	uint8_t GND_SW;
	uint8_t BAT_SW;
	uint8_t PRE_CH_SW;
};*/

extern struct Toggle_Object toggle_switch;
/*
extern struct Status_SW_Object{
	uint8_t status_BAT_SW;
	uint8_t status_GND_SW;
	uint8_t status_PRE_CH_SW;
};*/

extern struct Status_SW_Object status_switch;
/*
extern struct Set_SW_Object{
	uint8_t set_BAT_SW;
	uint8_t set_GND_SW;
	uint8_t set_PRE_CH_SW;
};
*/
extern struct Set_SW_Object set_switch;

extern uint8_t Set_ISO_Meter_Status;

extern int16_t sensor_voltage_in_100uV;
extern uint16_t DAC_digits;
extern uint16_t DAC_Address;
extern uint16_t DAC_Cmd ;
extern uint8_t DAC_Data[2];
extern MCP4725_t mcp4725;
extern uint8_t csend[8];
extern int16_t OP_offset;
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
extern void Analyse_CANMsg_Reaction(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GND_SW_IN_Pin GPIO_PIN_12
#define GND_SW_IN_GPIO_Port GPIOB
#define BAT_SW_in_Pin GPIO_PIN_13
#define BAT_SW_in_GPIO_Port GPIOB
#define PreCh_SW_in_Pin GPIO_PIN_14
#define PreCh_SW_in_GPIO_Port GPIOB
#define Activate_ISO_Pin GPIO_PIN_3
#define Activate_ISO_GPIO_Port GPIOB
#define Activate_GND_BAT_Pin GPIO_PIN_4
#define Activate_GND_BAT_GPIO_Port GPIOB
#define Avtivate_Bat_Plus_Pin GPIO_PIN_5
#define Avtivate_Bat_Plus_GPIO_Port GPIOB
#define Acivate_Precharche_Pin GPIO_PIN_9
#define Acivate_Precharche_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
