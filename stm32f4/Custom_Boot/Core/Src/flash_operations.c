#include "stm32f4xx.h"
#include "flash_operations.h"

/* ===========================
   DEFINES MANQUANTS POUR CMSIS
   =========================== */

#define OTA_FLAG_ADDRESS      0x08008000
#define APP_START_ADDR        0x0800C000
#define APP_HEADER_ADDR       0x08008000
#define APP_HEADER_SECTOR     2
#define APP_START_SECTOR      3
#define APP_END_SECTOR        11
#define APP_MAGIC             0xDEADBEEF
#define APP_MAX_SIZE          (256 * 1024)

uint32_t flash_read_ota_flag(void) {
    uint32_t data;
    Flash_ReadWord(OTA_FLAG_ADDRESS, &data);
    return data;
}

uint32_t flash_erase_app(void) {
        FLASH_EraseInitTypeDef erase;
    uint32_t error;

    erase.TypeErase    = FLASH_TYPEERASE_SECTORS;
    erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    erase.Sector       = APP_START_SECTOR;
    erase.NbSectors    = (APP_END_SECTOR - APP_START_SECTOR) + 1;

    HAL_FLASHEx_Erase(&erase, &error);
    return error;
}

uint32_t flash_erase_header (void)
{
    FLASH_EraseInitTypeDef erase;
    uint32_t error;

    erase.TypeErase    = FLASH_TYPEERASE_SECTORS;
    erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    erase.Sector       = APP_HEADER_SECTOR;
    erase.NbSectors    = 1;

    HAL_FLASHEx_Erase(&erase, &error);
    return error;
}

void flash_write_word(uint32_t addr, uint32_t data)
{
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, data);
}

void Flash_Unlock(void)
{
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

void Flash_Lock(void)
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

uint32_t Flash_ReadWord(uint32_t address, uint32_t *data)
{
    *data = *(volatile uint32_t*)address;
    return 0;
}

void Flash_WriteBuffer(uint32_t address, const uint32_t *buf, uint32_t len_words)
{
    for (uint32_t i = 0; i < len_words; i++) {
        Flash_WriteWord(address + (i * 4), buf[i]);
    }
}


