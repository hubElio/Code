#include "stm32f4xx.h"

static void Flash_Unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

static void Flash_Lock(void)
{
    FLASH->CR |= FLASH_CR_LOCK;
}

int Flash_EraseSector(uint8_t sector)
{
    if (sector > 11) return -1;

    Flash_Unlock();

    while (FLASH->SR & FLASH_SR_BSY);

    FLASH->CR &= ~FLASH_CR_SNB_Msk;
    FLASH->CR |= FLASH_CR_SER | (sector << FLASH_CR_SNB_Pos);

    FLASH->CR |= FLASH_CR_STRT;

    while (FLASH->SR & FLASH_SR_BSY);

    FLASH->CR &= ~FLASH_CR_SER;

    if (FLASH->SR & (FLASH_SR_PGAERR | FLASH_SR_PGPERR | FLASH_SR_WRPERR)) {
        Flash_Lock();
        return -1;
    }

    Flash_Lock();
    return 0;
}

int Flash_WriteWord(uint32_t address, uint32_t data)
{
    Flash_Unlock();

    while (FLASH->SR & FLASH_SR_BSY);

    FLASH->CR &= ~FLASH_CR_PSIZE;
    FLASH->CR |= FLASH_CR_PSIZE_1; // 32 bits
    FLASH->CR |= FLASH_CR_PG;

    *(volatile uint32_t*)address = data;

    while (FLASH->SR & FLASH_SR_BSY);

    FLASH->CR &= ~FLASH_CR_PG;

    if (FLASH->SR & (FLASH_SR_PGAERR | FLASH_SR_PGPERR | FLASH_SR_WRPERR)) {
        Flash_Lock();
        return -1;
    }

    Flash_Lock();
    return 0;
}

uint32_t Flash_ReadWord(uint32_t address)
{
    return *(volatile uint32_t*)address;
}

void Flash_WriteBuffer(uint32_t address, const uint8_t *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i += 4) {
        uint32_t word =
            buf[i] |
            (buf[i+1] << 8) |
            (buf[i+2] << 16) |
            (buf[i+3] << 24);

        Flash_WriteWord(address + i, word);
    }
}

