#ifndef __USART_H
#define __USART_H

#include "main.h"
#include "cmsis_os.h"

#define RX_DMA_BUF_SIZE 2U
#define TX_DMA_BUF_SIZE 256U

typedef struct
{
  uint16_t len;
  uint8_t data[RX_DMA_BUF_SIZE];
} UartFrame_t;

/* flag set by HAL UART TX complete callback */
#define USART_TX_DONE_FLAG (1U << 0)

/* flag set by RX complete callback to wake processing task */
#define USART_RX_DONE_FLAG (1U << 1)

/* processing task handle (used to notify from ISR) */
extern osThreadId_t TaskProcessingHandle;

extern uint8_t rx_dma_buf[RX_DMA_BUF_SIZE];

extern osMessageQueueId_t Queue_USART1_RxHandle;
extern osMessageQueueId_t Queue_USART1_TxHandle;
extern osThreadId_t Task_Usart1TxHandle;
/* semaphore to protect UART TX access */
extern osSemaphoreId_t uartTxSem;

HAL_StatusTypeDef UART_Send_IT(UART_HandleTypeDef *huart, uint8_t *data, uint16_t len);

#endif /* __USART_H */