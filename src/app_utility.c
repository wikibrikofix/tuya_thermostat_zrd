#include "tl_common.h"
#include "zcl_include.h"

#include "app_main.h"

uint8_t mcuBootAddrGet(void);
//uint32_t mcuBootAddrGet(void);

void start_message() {
    const uint8_t version[] = ZCL_BASIC_SW_BUILD_ID;
#ifdef ZCL_OTA
    if (mcuBootAddrGet()) {
#if UART_PRINTF_MODE
        printf("OTA mode enabled. MCU boot from address: 0x%x\r\n", FLASH_ADDR_OF_OTA_IMAGE);
#endif /* UART_PRINTF_MODE */
    } else {
#if UART_PRINTF_MODE
        printf("OTA mode enabled. MCU boot from address: 0x%x\r\n", FLASH_ADDR_OF_APP_FW);
#endif /* UART_PRINTF_MODE */
    }
#else
#if UART_PRINTF_MODE
    printf("OTA mode desabled. MCU boot from address: 0x%x\r\n", FLASH_ADDR_OF_APP_FW);
#endif /* UART_PRINTF_MODE */
#endif

    printf("Firmware version: %s\r\n", version+1);
}


int32_t poll_rateAppCb(void *arg) {

    uint32_t poll_rate = zb_getPollRate();

    if (poll_rate == g_appCtx.long_poll) {
        zb_setPollRate(g_appCtx.short_poll);
        return TIMEOUT_30SEC;
    }

    zb_setPollRate(g_appCtx.long_poll);

    return g_appCtx.long_poll;
}

int32_t delayedMcuResetCb(void *arg) {

    //printf("mcu reset\r\n");
    zb_resetDevice();
    return -1;
}

int32_t delayedFactoryResetCb(void *arg) {

    //printf("factory reset\r\n");
    zb_resetDevice2FN();
//    sleep_ms(500);
//    rf_setTxPower(MY_RF_POWER_INDEX);
//    zb_factoryReset();
//    sleep_ms(100);

//    TL_ZB_TIMER_SCHEDULE(delayedMcuResetCb, NULL, TIMEOUT_3SEC);

//    zb_resetDevice();
    return -1;
}

int32_t delayedFullResetCb(void *arg) {

    //printf("full reset\r\n");
    return -1;
}

int32_t fakeTimer500msCb(void *arg) {

    return 0;
}

uint32_t reverse32(uint32_t in) {
    uint32_t out;
    uint8_t *source = (uint8_t*)&in;
    uint8_t *destination = (uint8_t*)&out;

    destination[3] = source[0];
    destination[2] = source[1];
    destination[1] = source[2];
    destination[0] = source[3];

    return out;
}

uint16_t reverse16(uint16_t in) {
    uint16_t out;
    uint8_t *source = (uint8_t*)&in;
    uint8_t *destination = (uint8_t*)&out;

    destination[1] = source[0];
    destination[0] = source[1];

    return out;
}

int32_t int32_from_str(uint8_t *data) {

    int32_t val;

    val = data[0] << 24;
    val |= data[1] << 16;
    val |= data[2] << 8;
    val |= data[3];

    return val;
}

//char * mystrstr(char * mainStr, char * subStr) {
//    char *s1, *s2;
//
//    // Iterate over the main string
//    while( *mainStr != NULL)
//    {
//        // search for the first character in substring
//        if(*mainStr == *subStr)
//        {
//            // The first character of substring is matched.
//            // Check if all characters of substring.
//            s1 = mainStr;
//            s2 = subStr;
//
//            while (*s1 && *s2 )
//            {
//                if(*s1 != *s2)
//                    break;      // not matched
//
//                s1++;
//                s2++;
//            }
//
//            // we reached end of subStr
//            if(*s2 == NULL)
//                return mainStr;
//        }
//
//        // go to next element
//        mainStr++;
//    }
//
//    return NULL;
//}
