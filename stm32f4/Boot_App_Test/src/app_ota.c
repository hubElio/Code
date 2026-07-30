/*
 * app_ota.c
 *
 *  Created on: 03-Jan-2026
 *      Author: arunrawat
 */


#include <flash_layout.h>
#include "main.h"
#include "app_ota.h"
#include "flash_operations.h"
#include "macros_utiles.h"
#include "app_header.h"

#define OTA_FLAG_START		1
#define OTA_FLAG_CLEAR		0
#define APP_HEADER_SECTOR	2  

uint32_t flash_buffer[5];

void enable_ota_request(void)
{
	for(int i = 0; i < 5; i++) {
		Flash_ReadWord(APP_HEADER_START_ADDRESS + (i * 4), &flash_buffer[i]);
	}

    /* Update only first word */
    flash_buffer[0] = OTA_FLAG_START;

    Flash_EraseSector(APP_HEADER_SECTOR);

    Flash_WriteBuffer(APP_HEADER_START_ADDRESS, flash_buffer, 5);

    // NVIC_SystemReset();
}

void clear_ota_flag(void)
{
    for(int i = 0; i < 5; i++) {
		Flash_ReadWord(APP_HEADER_START_ADDRESS + (i * 4), &flash_buffer[i]);
	}

    /* Update only first word */
    flash_buffer[0] = OTA_FLAG_CLEAR;

    Flash_EraseSector(APP_HEADER_SECTOR);

    Flash_WriteBuffer(APP_HEADER_START_ADDRESS, flash_buffer, 5);
}
