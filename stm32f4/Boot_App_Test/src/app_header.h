/*
 * app_header.h
 *
 *  Created on: Jul 18, 2026
 *      Author: eerva
 */

#ifndef INC_APP_HEADER_H_
#define INC_APP_HEADER_H_

#include "flash_layout.h"

typedef struct {
	uint32_t ota_flag; // if a over-the-air update is available, this flag will be set to 1
	uint32_t magic_number; // used as an identifier for the application header
	uint32_t app_version;
	uint32_t app_size;
	uint32_t app_crc;
} app_header_t;



#endif /* INC_APP_HEADER_H_ */
