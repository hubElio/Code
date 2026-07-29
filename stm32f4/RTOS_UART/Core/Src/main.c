/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"

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
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* Definitions for Task_Usart1Rx */
osThreadId_t Task_Usart1RxHandle;
const osThreadAttr_t Task_Usart1Rx_attributes = {
  .name = "Task_Usart1Rx",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_Usart1Tx */
osThreadId_t Task_Usart1TxHandle;
const osThreadAttr_t Task_Usart1Tx_attributes = {
  .name = "Task_Usart1Tx",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskProcessing */
osThreadId_t TaskProcessingHandle;
const osThreadAttr_t TaskProcessing_attributes = {
  .name = "TaskProcessing",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Queue_USART1_Rx */
osMessageQueueId_t Queue_USART1_RxHandle;
const osMessageQueueAttr_t Queue_USART1_Rx_attributes = {
  .name = "Queue_USART1_Rx"
};
/* Definitions for Queue_USART1_Tx */
osMessageQueueId_t Queue_USART1_TxHandle;
const osMessageQueueAttr_t Queue_USART1_Tx_attributes = {
  .name = "Queue_USART1_Tx"
};
/* Definitions for uartTxSem */
osMutexId_t uartTxSemHandle;
const osMutexAttr_t uartTxSem_attributes = {
  .name = "uartTxSem"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_USART1_UART_Init(void);
void StartTask_Usart1Rx(void *argument);
void StartTask_Usart1Tx(void *argument);
void StartTaskProcessing(void *argument);

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
  MX_DMA_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of uartTxSem */
  uartTxSemHandle = osMutexNew(&uartTxSem_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* create UART TX completion semaphore (initial count 1 so the first acquire succeeds) */
  {
    const osSemaphoreAttr_t uartTxSemAttr = { .name = "uartTxSem" };
    uartTxSemHandle = osSemaphoreNew(1, 1, &uartTxSemAttr);
    /* make the global uartTxSem (declared in usart.h) point to this handle */
    uartTxSem = (osSemaphoreId_t)uartTxSemHandle;
  }
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Queue_USART1_Rx */
  Queue_USART1_RxHandle = osMessageQueueNew (16, sizeof(UartFrame_t), &Queue_USART1_Rx_attributes);

  /* creation of Queue_USART1_Tx */
  Queue_USART1_TxHandle = osMessageQueueNew (16, sizeof(UartFrame_t), &Queue_USART1_Tx_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_Usart1Rx */
  Task_Usart1RxHandle = osThreadNew(StartTask_Usart1Rx, NULL, &Task_Usart1Rx_attributes);

  /* creation of Task_Usart1Tx */
  Task_Usart1TxHandle = osThreadNew(StartTask_Usart1Tx, NULL, &Task_Usart1Tx_attributes);

  /* creation of TaskProcessing */
  TaskProcessingHandle = osThreadNew(StartTaskProcessing, NULL, &TaskProcessing_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PD13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTask_Usart1Rx */
/**
  * @brief  Function implementing the Task_Usart1Rx thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask_Usart1Rx */
void StartTask_Usart1Rx(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* debug */
  //HAL_UART_Transmit(&huart1, "RX Start", 13, 1000);
  /* end debug */
  HAL_StatusTypeDef status;
  osDelay(50); // wait for UART to be ready
  status = HAL_UART_Receive_DMA(&huart1, rx_dma_buf, RX_DMA_BUF_SIZE);

  if (status != HAL_OK)
  {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
  }
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask_Usart1Tx */
/**
* @brief Function implementing the Task_Usart1Tx thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask_Usart1Tx */
void StartTask_Usart1Tx(void *argument)
{
  /* USER CODE BEGIN StartTask_Usart1Tx */
  UartFrame_t msg;
  /* Infinite loop */
  for(;;)
  {
    if (osMessageQueueGet(Queue_USART1_TxHandle, &msg, NULL, osWaitForever) == osOK)
    {
      /* acquire semaphore to ensure single TX at a time */
      osSemaphoreAcquire(uartTxSem, osWaitForever);

      if (HAL_UART_Transmit_DMA(&huart1, msg.data, msg.len) != HAL_OK)
      {
        /* if DMA start failed, release semaphore and requeue message */
        osSemaphoreRelease(uartTxSem);
        osMessageQueuePut(Queue_USART1_TxHandle, &msg, 0, 0);
        osDelay(1);
        continue;
      }

      /* wait for TX complete signalled by semaphore release in ISR */
      osSemaphoreAcquire(uartTxSem, osWaitForever);

      /* release semaphore for next user */
      osSemaphoreRelease(uartTxSem);
    }
  }
  /* USER CODE END StartTask_Usart1Tx */
}

/* USER CODE BEGIN Header_StartTaskProcessing */
/**
* @brief Function implementing the TaskProcessing thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskProcessing */
void StartTaskProcessing(void *argument)
{
  /* USER CODE BEGIN StartTaskProcessing */
  UartFrame_t msg;
  /* Infinite loop */
  for(;;)
  {
    /* wait until ISR signals an IDLE-line frame is ready */
    osThreadFlagsWait(USART_RX_DONE_FLAG, osFlagsWaitAny, osWaitForever);

    if (msg.len > RX_DMA_BUF_SIZE)
    {
      msg.len = RX_DMA_BUF_SIZE;
    }

    for (uint16_t i = 0; i < msg.len; i++)
    {
      msg.data[i] = rx_dma_buf[i];
    }

    if (msg.len > 0)
    {
      switch (msg.data[0])
      {
      case '1':
          if (msg.data[1] == '1')
          {
              HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
              osDelay(1000);
          }
          break;

      case '2':
          HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
          osDelay(1000);
          break;

      case '3':
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
        osDelay(100);
        break;
      default:
        break;
      }
    }

    if (HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rx_dma_buf, RX_DMA_BUF_SIZE) != HAL_OK)
    {
      HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    }

    /* forward to TX queue */
    osMessageQueuePut(Queue_USART1_TxHandle, &msg, 0, osWaitForever);
  }
  /* USER CODE END StartTaskProcessing */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
#ifdef USE_FULL_ASSERT
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
