#ifndef APP_HEADER_H
#define APP_HEADER_H

#include <stdint.h>

#define APP_MAGIC        0xDEADBEEF
#define APP_HEADER_ADDR  0x08008000
#define APP_START_ADDR   0x0800C000
#define APP_MAX_SIZE     (256 * 1024)

typedef struct {
	uint32_t ota_flag;
    uint32_t magic_number;
    uint32_t app_size;
    uint32_t app_crc;
    uint32_t app_version;
} app_header_t;

#endif
