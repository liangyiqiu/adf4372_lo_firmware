/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "softspi.h"
#include "adf4372.h"
#include "stdio.h"
#include "string.h"
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
SoftSPI_TypeDef soft_spi_1;
adf4372_type_def adf4372_1;

uint8_t gui8_adf4372_reg_type[ADF4372_REG_NUMBER];
uint8_t gui8_adf4372_reg_value[ADF4372_REG_NUMBER];

uint8_t send_str[100];
uint8_t receive_str[4];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  soft_spi_1.SCLK_GPIO=GPIOB;
  soft_spi_1.SCLK_Pin=GPIO_PIN_4;

  soft_spi_1.SDIO_GPIO=GPIOB;
  soft_spi_1.SDIO_Pin=GPIO_PIN_5;

  soft_spi_1.SS_GPIO=GPIOB;
  soft_spi_1.SS_Pin=GPIO_PIN_6;

  soft_spi_1.Delay_Time=5;

  SoftSPI_Init(&soft_spi_1);

  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);

  adf4372_1.adf4372_reg_type=gui8_adf4372_reg_type;
  adf4372_1.adf4372_reg_value=gui8_adf4372_reg_value;
  adf4372_1.f_rfout=11e9;
  adf4372_1.n_frac_1=0;
  adf4372_1.n_frac_2=0;
  adf4372_1.n_int=0;
  adf4372_1.n_mod_1=0;
  adf4372_1.n_mod_2=0;
  adf4372_1.SoftSPIx=&soft_spi_1;

  HAL_Delay(1000);

  //adf4372_init(&adf4372_1);
  adf4372_ace_init(&adf4372_1);

//   HAL_Delay(2000);

//   adf4372_ace_init(&adf4372_1);
    
  sprintf(send_str,"adf4372 init finished.\r\n");
  HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);

  HAL_Delay(100);

 uint32_t rf_int_default=*(__IO uint32_t *)FLASH_USER_START_ADDR;
 uint32_t rf_frac_default=*(__IO uint32_t *)(FLASH_USER_START_ADDR+4);

 if(rf_int_default==0x00||rf_int_default==0xff)
   rf_int_default=10;
 if(rf_frac_default==0x00||rf_frac_default==0xff)
   rf_frac_default=50;

 adf4372_update_freq(&adf4372_1,rf_int_default,rf_frac_default);
 sprintf(send_str,"load default freq: %d.%d GHz\r\n",rf_int_default,rf_frac_default);
 HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);

  while (1)
  {
    /* USER CODE END WHILE */
		
    /* USER CODE BEGIN 3 */
    HAL_UART_Receive(&huart2,receive_str,3,1000);
    if(receive_str[0]!=0)
    {
      switch (receive_str[0])
      {
        case 0x0a:
        {
          sprintf(send_str,"mcu ok\r\n");
          HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
          break;
        }      
        case 0x0b:
        {
          SoftSPI_ClrSS(&soft_spi_1);
          SoftSPI_Write_Word(&soft_spi_1,receive_str[1]|0x8000);
          uint8_t read_byte=SoftSPI_Read_Byte(&soft_spi_1);
          SoftSPI_SetSS(&soft_spi_1);

          sprintf(send_str,"read byte is %x\r\n",read_byte);
          HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
          break;
        }
        case 0x0c:
        {
          SoftSPI_ClrSS(&soft_spi_1);
          SoftSPI_Write_Word(&soft_spi_1,receive_str[1]);
          SoftSPI_Write_Byte(&soft_spi_1,receive_str[2]);
          SoftSPI_SetSS(&soft_spi_1);

          sprintf(send_str,"write byte %x, at reg %x\r\n",receive_str[2],receive_str[1]);
          HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
          break;
        }
        case 0x0d:
        {
          uint8_t read_pin = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
          sprintf(send_str,"read pin is %d\r\n",read_pin);
          HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
          break;
        }
        case 0x0e:
        {
          //adf4372_update_freq(&adf4372_1);
          adf4372_ace_update_freq(&adf4372_1);
          sprintf(send_str,"update freq finish.\r\n");
          HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
          break;
        }
        case 0x0f:
        {
          adf4372_ace_init(&adf4372_1);
  
          sprintf(send_str,"adf4372 init finished.\r\n");
          HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
          break;
        }
        case 0xaa:
				{
					if(receive_str[1]<100&&receive_str[2]<100)
					{
						adf4372_update_freq(&adf4372_1,receive_str[1],receive_str[2]);
						sprintf(send_str,"update freq: %d.%02d GHz\r\n",receive_str[1],receive_str[2]);
						HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
					}
					else
					{
						sprintf(send_str,"invalid input.\r\n");
						HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
					}
					break;
				}
        case 0xab:
				{
					if(receive_str[1]<100&&receive_str[2]<100)
					{
						adf4372_update_freq(&adf4372_1,receive_str[1],receive_str[2]);
						sprintf(send_str,"update freq: %d.%02d GHz\r\n",receive_str[1],receive_str[2]);
						HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);

            freq_write_flash(receive_str[1],receive_str[2]);
            sprintf(send_str,"default freq stored: %d.%02d GHz\r\n",receive_str[1],receive_str[2]);
						HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
					}
					else
					{
						sprintf(send_str,"invalid input.\r\n");
						HAL_UART_Transmit(&huart2,send_str,strlen(send_str),1000);
					}
					break;
				}
      }
      receive_str[0]=0;
    }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
