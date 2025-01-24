#include "stm32f4xx.h"

#define BUFFER_SIZE 256

uint16_t waveformBuffer[BUFFER_SIZE];

void generateTriangularWave() {
    // Fill the buffer with values for a triangular wave
    for (int i = 0; i < BUFFER_SIZE / 2; ++i) {
        waveformBuffer[i] = i * (4095 / (BUFFER_SIZE / 2));
    }

    for (int i = BUFFER_SIZE / 2; i < BUFFER_SIZE; ++i) {
        waveformBuffer[i] = 4095 - (i - BUFFER_SIZE / 2) * (4095 / (BUFFER_SIZE / 2));
    }
}

void initDAC() {
    // Enable the DAC clock
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;

    // Enable the GPIOA clock (assuming DAC is on PA4)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA4 as analog
    GPIOA->MODER |= GPIO_MODER_MODER4;

    // Configure DAC channel 1
    DAC->CR |= DAC_CR_EN1;   // Enable DAC channel 1
    DAC->CR &= ~DAC_CR_BOFF1; // Enable buffer for DAC channel 1
}

void initDMA() {
    // Enable the DMA1 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

    // Configure DMA for DAC
    DMA1_Stream5->CR &= ~DMA_SxCR_EN;  // Disable the DMA stream
    DMA1_Stream5->PAR = (uint32_t)(&DAC->DHR12R1);  // DAC data register address
    DMA1_Stream5->M0AR = (uint32_t)waveformBuffer;  // Memory address
    DMA1_Stream5->NDTR = BUFFER_SIZE;  // Number of data items to transfer
    DMA1_Stream5->CR |= DMA_SxCR_CHSEL_7;  // Channel 7 for DAC
    DMA1_Stream5->CR |= DMA_SxCR_PL_1;  // Priority level (medium)
    DMA1_Stream5->CR |= DMA_SxCR_DIR_0;  // Memory to peripheral
    DMA1_Stream5->CR |= DMA_SxCR_MINC;  // Memory increment mode
    DMA1_Stream5->CR |= DMA_SxCR_MSIZE_0;  // Memory size (16 bits)
    DMA1_Stream5->CR |= DMA_SxCR_PSIZE_0;  // Peripheral size (16 bits)
    DMA1_Stream5->FCR |= DMA_SxFCR_DMDIS;  // Direct mode disabled

    // Enable the DMA stream
    DMA1_Stream5->CR |= DMA_SxCR_EN;
}

int main(void) {
    // Initialize the triangular wave buffer
    generateTriangularWave();

    // Initialize the DAC
    initDAC();

    // Initialize the DMA
    initDMA();

    while (1) {
        // The DAC output is automatically updated by the DMA transfer
    }
}
