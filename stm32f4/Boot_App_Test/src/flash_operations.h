#ifndef __FLASH_OPERATIONS_H
#define __FLASH_OPERATIONS_H

#include <stdint.h>

#include "stm32f4xx.h"

#define OTA_FLAG_ADDRESS 0x08008000 // Address of the OTA flag in flash memory

typedef struct {
    uint32_t base;
    uint32_t size;
} FlashSectorInfo;

//To be changed
int Flash_EraseSector(uint8_t sector);
void Flash_Lock(void);
void Flash_Unlock(void);
int Flash_EraseSector(uint8_t sector);
int Flash_WriteWord(uint32_t address, uint32_t data);
uint32_t Flash_ReadWord(uint32_t address, uint32_t *data);
void Flash_WriteBuffer(uint32_t address, const uint32_t *buf, uint32_t len);

//endTo be changed

#endif /* __FLASH_OPERATIONS_H */
