/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MCP4725.h"
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
CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
CAN_RxHeaderTypeDef rxHeader; 			//CAN Bus Receive Header
CAN_TxHeaderTypeDef txHeader; 			//CAN Bus Transmit Header
uint8_t canRX[8] = {0,0,0,0,0,0,0,0};  	//CAN Bus Receive Buffer
CAN_FilterTypeDef canfil; 				//CAN Bus Filter
uint32_t canMailbox; 					//CAN Bus Mail box variable
HAL_StatusTypeDef status_value;
struct Toggle_Object{
	uint8_t GND_SW;
	uint8_t BAT_SW;
	uint8_t PRE_CH_SW;
};

struct Toggle_Object toggle_switch;

struct Status_SW_Object{
	uint8_t status_BAT_SW;
	uint8_t status_GND_SW;
	uint8_t status_PRE_CH_SW;
};

struct Status_SW_Object status_switch;

struct Set_SW_Object{
	uint8_t set_BAT_SW;
	uint8_t set_GND_SW;
	uint8_t set_PRE_CH_SW;
};

struct Set_SW_Object set_switch;

uint8_t Set_ISO_Meter_Status;

int16_t sensor_voltage_in_100uV;
uint16_t DAC_digits;
uint16_t DAC_Address = 0xC4;
uint16_t DAC_Cmd = 0x00;
uint8_t DAC_Data[2];
uint8_t count=0;
MCP4725_t mcp4725;
uint8_t csend[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
int16_t OP_offset=150;// Offset of OPA2123 (entspricht 12mV)

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Analyse_CANMsg_Reaction(void);
/*void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	count++;
}*/
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  //GPIO-Inititialization
  status_switch.status_BAT_SW=HAL_GPIO_ReadPin (GPIOB, BAT_SW_in_Pin);
  status_switch.status_GND_SW=HAL_GPIO_ReadPin (GPIOB, GND_SW_IN_Pin);
  status_switch.status_PRE_CH_SW=HAL_GPIO_ReadPin (GPIOB, PreCh_SW_in_Pin);

  set_switch.set_BAT_SW=status_switch.status_BAT_SW;
  set_switch.set_GND_SW=status_switch.status_GND_SW;
  set_switch.set_PRE_CH_SW=status_switch.status_PRE_CH_SW;

  HAL_GPIO_WritePin(GPIOB,Avtivate_Bat_Plus_Pin,set_switch.set_BAT_SW);
  HAL_GPIO_WritePin(GPIOB,Activate_GND_BAT_Pin,set_switch.set_GND_SW);
  HAL_GPIO_WritePin(GPIOB,Acivate_Precharche_Pin,set_switch.set_PRE_CH_SW);
  // ISO-Pin is with no error during initialization.
  HAL_GPIO_WritePin(GPIOB,Activate_ISO_Pin,GPIO_PIN_RESET);


  //DAC-Inititialization Currentsigna at 0A
  // Write 1,5V+OP_Offest at the DAC-Output with V_ref=3.3V
  status_value=MCP4725_Initialize(&mcp4725, &hi2c1, 0x60);
  DAC_digits=(uint16_t)( ( (double)(OP_offset)/10000.0 + 1.5)/3.3 *4095 );
  status_value=MCP4725_SetVoltage(&mcp4725, DAC_digits, MCP4725_DAC_ONLY);

  // Start CAN-Bus
  HAL_CAN_Start(&hcan);
  // CAN-Receive Interrupt
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

  // Start Timer 2
  HAL_TIM_Base_Start_IT(&htim2);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	// Prepare the output of the switch manipulation
	set_switch.set_BAT_SW=HAL_GPIO_ReadPin (GPIOB, BAT_SW_in_Pin);
	set_switch.set_GND_SW=HAL_GPIO_ReadPin (GPIOB, GND_SW_IN_Pin);
	set_switch.set_PRE_CH_SW=HAL_GPIO_ReadPin (GPIOB, PreCh_SW_in_Pin);
	// Find out, if Error is provoked
	if (toggle_switch.BAT_SW)
		set_switch.set_BAT_SW=(status_switch.status_BAT_SW > 0x00) ? 0x00 : 0x01;
	if (toggle_switch.GND_SW)
		set_switch.set_GND_SW=(status_switch.status_GND_SW > 0x00) ? 0x00 : 0x01;
	if (toggle_switch.PRE_CH_SW)
		set_switch.set_PRE_CH_SW=(status_switch.status_PRE_CH_SW > 0x00) ? 0x00 :0x01;
	// Update Status of Supp
	HAL_GPIO_WritePin(GPIOB,Avtivate_Bat_Plus_Pin,set_switch.set_BAT_SW);
	HAL_GPIO_WritePin(GPIOB,Activate_GND_BAT_Pin,set_switch.set_GND_SW);
	HAL_GPIO_WritePin(GPIOB,Acivate_Precharche_Pin,set_switch.set_PRE_CH_SW);

	csend[0]=set_switch.set_PRE_CH_SW<<5|set_switch.set_GND_SW<<4|set_switch.set_BAT_SW<<3|toggle_switch.PRE_CH_SW<<2|toggle_switch.GND_SW<<1|toggle_switch.BAT_SW;
	csend[1]=canRX[1];
	csend[2]=canRX[2];
	csend[3]=canRX[3];
	//HAL_GPIO_TogglePin(GPIOB, Avtivate_Bat_Plus_Pin);
	//HAL_CAN_AddTxMessage(&hcan,&txHeader,csend,&canMailbox);
	HAL_Delay(1);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 4;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
  // Organize CAN-Bus
  canfil.FilterBank = 0;
  canfil.FilterMode = CAN_FILTERMODE_IDMASK;
  canfil.FilterFIFOAssignment = CAN_RX_FIFO0;
  canfil.FilterIdHigh = 0x699<<5;
  canfil.FilterIdLow = 0;
  canfil.FilterMaskIdHigh = 0x7FF<<5;
  canfil.FilterMaskIdLow = 0;
  canfil.FilterScale = CAN_FILTERSCALE_32BIT;
  canfil.FilterActivation = CAN_FILTER_ENABLE;
  canfil.SlaveStartFilterBank = 13;

  txHeader.DLC = 8;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.StdId = 0x69A;
  //txHeader.ExtId = 0x00;
  txHeader.TransmitGlobalTime = DISABLE;

  HAL_CAN_ConfigFilter(&hcan,&canfil);
  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 200;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Activate_ISO_Pin|Activate_GND_BAT_Pin|Avtivate_Bat_Plus_Pin|Acivate_Precharche_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : GND_SW_IN_Pin BAT_SW_in_Pin PreCh_SW_in_Pin */
  GPIO_InitStruct.Pin = GND_SW_IN_Pin|BAT_SW_in_Pin|PreCh_SW_in_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Activate_ISO_Pin Activate_GND_BAT_Pin Avtivate_Bat_Plus_Pin Acivate_Precharche_Pin */
  GPIO_InitStruct.Pin = Activate_ISO_Pin|Activate_GND_BAT_Pin|Avtivate_Bat_Plus_Pin|Acivate_Precharche_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void Analyse_CANMsg_Reaction(void)
{
  // canRX[0]=0b0000 0XYZ X: Toggle Main_Switch, Y: Toggle Bat_Plus_Switch Z: Toggle Precharge_Switch
  // canRX[1]=0x0X : X=1 (OK), X=0 (NOK)
  // canRX[2],[3]: Voltage in 100µV (-15.000..15.000)*100µV
  toggle_switch.BAT_SW=canRX[0]&0x01;
  toggle_switch.GND_SW=(canRX[0]&0x02)>>1;
  toggle_switch.PRE_CH_SW=(canRX[0]&0x04)>>2;
  Set_ISO_Meter_Status=canRX[1];
  // Detect actual status of the switches
  status_switch.status_BAT_SW=HAL_GPIO_ReadPin (GPIOB, BAT_SW_in_Pin);
  status_switch.status_GND_SW=HAL_GPIO_ReadPin (GPIOB, GND_SW_IN_Pin);
  status_switch.status_PRE_CH_SW=HAL_GPIO_ReadPin (GPIOB, PreCh_SW_in_Pin);
  // Prepare the output of the switch manipulation
  set_switch.set_BAT_SW=status_switch.status_BAT_SW;
  set_switch.set_GND_SW=status_switch.status_GND_SW;
  set_switch.set_PRE_CH_SW=status_switch.status_PRE_CH_SW;
  // Check if a toggle-manipulation is necessary
  if (toggle_switch.BAT_SW)
	  set_switch.set_BAT_SW=(status_switch.status_BAT_SW > 0x00) ? 0x00 : 0x01;
  if (toggle_switch.GND_SW)
	  set_switch.set_GND_SW=(status_switch.status_GND_SW > 0x00) ? 0x00 : 0x01;
  if (toggle_switch.PRE_CH_SW)
  	  set_switch.set_PRE_CH_SW=(status_switch.status_PRE_CH_SW > 0x00) ? 0x00 :0x01;
  // Update the output signals of the bluepill
  HAL_GPIO_WritePin(GPIOB,Avtivate_Bat_Plus_Pin,set_switch.set_BAT_SW);
  HAL_GPIO_WritePin(GPIOB,Activate_GND_BAT_Pin,set_switch.set_GND_SW);
  HAL_GPIO_WritePin(GPIOB,Acivate_Precharche_Pin,set_switch.set_PRE_CH_SW);
  HAL_GPIO_WritePin(GPIOB,Activate_ISO_Pin,Set_ISO_Meter_Status);
  // Calculate the DAC digits of the DAC zwischen -10.000[*100µ])...+10.000[*100µV]->-100mV..100mV
  sensor_voltage_in_100uV =(int16_t)(canRX[2]<<8 | canRX[3]);
  // Sensor voltage 1.000->+100mV liegt als Sensorsignal vor.
  // Sensor voltage: -1.000->-100mV liegt als Sensorsignal vor.
  // Sensor voltage: 0 ->0mV

  DAC_digits=(uint16_t)( ( (double)(sensor_voltage_in_100uV+OP_offset)/10000.0 +1.5)/3.3 *4095 );
  status_value=MCP4725_SetVoltage(&mcp4725, DAC_digits, MCP4725_DAC_ONLY);
   //HAL_I2C_Mem_Write(&hi2c1,DAC_Address,DAC_Cmd,1,DAC_LowByte,1,20);
  //HAL_I2C_Master_Transmit(&hi2c1, DAC_Address, &DAC_Data, 2, HAL_MAX_DELAY);
}

void HAL_TIM_PerioElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance ==TIM2)
		HAL_CAN_AddTxMessage(&hcan,&txHeader,csend,&canMailbox);

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
