
#include "usart.h"

extern UART_HandleTypeDef huart1;
extern osMessageQueueId_t Queue_USART1_RxHandle;

/* semaphore to protect UART TX access */
osSemaphoreId_t uartTxSem;

/* RX DMA buffer */
uint8_t rx_dma_buf[RX_DMA_BUF_SIZE];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        /* notify processing task to copy buffer outside ISR context */
        osThreadFlagsSet(TaskProcessingHandle, USART_RX_DONE_FLAG);
        /* restart reception */
        HAL_UART_Receive_DMA(&huart1, rx_dma_buf, RX_DMA_BUF_SIZE);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
                /* release semaphore to signal TX completion to task */
                if (uartTxSem != NULL)
                {
                    osSemaphoreRelease(uartTxSem);
                }
    }
}