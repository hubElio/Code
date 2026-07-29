#include "flash_layout.h"
#include "bl_jump.h"
#include "main.h"
#include "app_header.h"
#include "crc.h"

#define APP_MAGIC 0xABCDEFAB
#define APP_HEADER_ADDR 0x08008000
#define APP_START_ADDR  0x0800C000
#define APP_MAX_SIZE    0xABCDEFAB


typedef void (*pFunction)(void);

void JumpToApplication(void)
{

    uint32_t appStack = *(uint32_t*)0x0800C000;
    uint32_t appReset = *(uint32_t*)0x0800C004;

    HAL_DeInit();

    __disable_irq();

    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;

    for (int i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    }

    SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk | SCB_ICSR_PENDSTCLR_Msk;

    SCB->VTOR = 0x0800C000;

    __set_CONTROL(0);
    __set_PSP(0);
    __set_MSP(appStack);

    __DSB();
    __ISB();
    ((void (*)(void))appReset)();

}

int bootloader_is_app_valid(void) {
    uint32_t HDR_ADDR = APP_HEADER_ADDR;
    const app_header_t *app_hdr = (const app_header_t *)HDR_ADDR;

    // 1 Magic number
    if(app_hdr->magic_number != APP_MAGIC) {
        return 1;
    }

    // 2 reset handler sanity
    uint32_t reset_handler = *(uint32_t *)(APP_START_ADDR + 4);
    if((reset_handler & 0xFF000000) != 0x08000000) {
        return 2;
    }

    // 3 Size sanity
    if(app_hdr->app_size == 0 || app_hdr->app_size > APP_MAX_SIZE) {
    	return 3;
    }

    // 4 CRC check
    uint32_t calc_crc = calculate_crc32((const uint8_t *)APP_START_ADDR, app_hdr->app_size);

    if(calc_crc != app_hdr->app_crc) { 
    	return 4;
    }

    return 0; // valid
}
 
