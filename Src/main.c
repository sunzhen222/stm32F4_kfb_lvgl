/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

#include "HardwareInit.h"

#include "common.h"

#include "TestTask.h"
#include "lvglTask.h"


osThreadId_t defaultTaskHandle;
osThreadId_t testTaskHandle;
osThreadId_t lvglTaskHandle;

extern UART_HandleTypeDef huart1;
uint8_t uart1_rx_byte;

void StartDefaultTask(void *argument);

int main(void)
{
    HAL_Init();
    
    /* Configure the system clock */
    SystemClock_Config();
    
    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_FMC_Init();
    MX_USART1_UART_Init();
    
    
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart1_rx_byte, 1);
    
    osKernelInitialize();
    
    const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
    };
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
    
    
    const osThreadAttr_t testTaskAttributes = {
    .name = "TestTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128
    };
    testTaskHandle = osThreadNew(TestTask, NULL, &testTaskAttributes);

    const osThreadAttr_t lvglTaskAttributes = {
    .name = "LvglTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 4096
    };
    lvglTaskHandle = osThreadNew(LvglTask, NULL, &lvglTaskAttributes);

    
    
    /* Start scheduler */
    osKernelStart();
    
    /* We should never get here as control is now taken by the scheduler */
    
    /* Infinite loop */
    while (1)
    {
    }
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        //uart3_send_data(&uart1_rx_byte,1);
        //uart1_rx_callback(uart1_rx_byte);
        HAL_UART_Receive_IT(huart, (uint8_t *)&uart1_rx_byte, 1);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        uart1_tx_callback();
    }
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for(;;)
    {
        osDelay(1);
    }
    /* USER CODE END 5 */ 
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
    HAL_IncTick();
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
