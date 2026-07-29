#ifndef __FLASH_OPERATIONS_H
#define __FLASH_OPERATIONS_H

#include <stdint.h>

#include "stm32f4xx.h"


typedef struct {
    uint32_t base;
    uint32_t size;
} FlashSectorInfo;

static const FlashSectorInfo flashSectors[] = {
    {0x08000000, 16 * 1024},  // Sector 0
    {0x08004000, 16 * 1024},  // Sector 1
    {0x08008000, 16 * 1024},  // Sector 2
    {0x0800C000, 16 * 1024},  // Sector 3
    {0x08010000, 64 * 1024},  // Sector 4
    {0x08020000, 128 * 1024}, // Sector 5
    {0x08040000, 128 * 1024}, // Sector 6
    {0x08060000, 128 * 1024}, // Sector 7
    {0x08080000, 128 * 1024}, // Sector 8
    {0x080A0000, 128 * 1024}, // Sector 9
    {0x080C0000, 128 * 1024}, // Sector 10
    {0x080E0000, 128 * 1024}, // Sector 11
};


int Flash_EraseSector(uint8_t sector);
void Flash_Lock(void);
void Flash_Unlock(void);
int Flash_EraseSector(uint8_t sector);
int Flash_WriteWord(uint32_t address, uint32_t data);
uint32_t Flash_ReadWord(uint32_t address, uint32_t *data);
void Flash_WriteBuffer(uint32_t address, const uint32_t *buf, uint32_t len);

#endif /* __FLASH_OPERATIONS_H */