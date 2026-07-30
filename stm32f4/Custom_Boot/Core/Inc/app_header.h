/*
 * app_header.h
 *
 *  Created on: 20-Dec-2025
 *      Author: arunrawat
 */

#ifndef INC_APP_HEADER_H_
#define INC_APP_HEADER_H_

#include "flash_layout.h"

#define APP_MAGIC        0xDEADBEEF
#define APP_HEADER_ADDR  0x08008000
#define APP_START_ADDR   0x08008000//0x0800C000
#define APP_MAX_SIZE     (256 * 1024)

typedef struct
{
	uint32_t ota_flag;
    uint32_t magic;
    uint32_t size;      // application size in bytes
    uint32_t crc;       // CRC32 of application
    uint32_t version;
} app_header_t;

#endif /* INC_APP_HEADER_H_ */
