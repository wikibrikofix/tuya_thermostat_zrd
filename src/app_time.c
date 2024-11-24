#include "app_main.h"

static bool time_sent = false;

void get_time(uint32_t *utc_time, uint32_t *local_time) {

    uint16_t attr_len;
    uint32_t attr_data;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_TIME, &attr_len, (uint8_t*)&attr_data);

    if (attr_data != 0xFFFFFFFF) {
        *utc_time = attr_data;
    } else {
        utc_time = NULL;
    }

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_LOCAL_TIME, &attr_len, (uint8_t*)&attr_data);

    if (attr_data != 0xFFFFFFFF) {
        *local_time = attr_data;
    } else {
        local_time = NULL;
    }
}

static int32_t app_clockCb(void *arg) {

    uint32_t utc_time, local_time;
    uint32_t *p_utc_time = &utc_time;
    uint32_t *p_local_time = &local_time;

    if (time_sent) {
        get_time(p_utc_time, p_local_time);

        if (p_utc_time && p_local_time) {
            utc_time++;
            local_time++;
            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_TIME, (uint8_t*)p_utc_time);
            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_LOCAL_TIME, (uint8_t*)p_local_time);

#if UART_PRINTF_MODE && DEBUG_TIME
            printf("UTC time  : %d\r\n", (utc_time+UNIX_TIME_CONST));
            printf("Local time: %d\r\n", (local_time+UNIX_TIME_CONST));
#endif
        }
    }

    return 0;
}

int32_t app_time_cmdCb(void *arg) {

    if(zb_isDeviceJoinedNwk()) {
        epInfo_t dstEpInfo;
        TL_SETSTRUCTCONTENT(dstEpInfo, 0);

        dstEpInfo.profileId = HA_PROFILE_ID;
#if FIND_AND_BIND_SUPPORT
        dstEpInfo.dstAddrMode = APS_DSTADDR_EP_NOTPRESETNT;
#else
        dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
        dstEpInfo.dstEp = APP_ENDPOINT1;
        dstEpInfo.dstAddr.shortAddr = 0x0;
#endif
        zclAttrInfo_t *pAttrEntry;
        pAttrEntry = zcl_findAttribute(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_TIME);

        zclReadCmd_t *pReadCmd = (zclReadCmd_t *)ev_buf_allocate(sizeof(zclReadCmd_t) + (sizeof(uint16_t)*2));
        if(pReadCmd){
            pReadCmd->numAttr = 2;
            pReadCmd->attrID[0] = ZCL_ATTRID_TIME;
            pReadCmd->attrID[1] = ZCL_ATTRID_LOCAL_TIME;

            zcl_read(APP_ENDPOINT1, &dstEpInfo, ZCL_CLUSTER_GEN_TIME, MANUFACTURER_CODE_NONE, 0, 0, 0, pReadCmd);

            ev_buf_free((uint8_t *)pReadCmd);

            return TIMEOUT_60MIN;
        }

    }

    return 0;
}

void set_time_sent() {

    if (!time_sent) {
        TL_ZB_TIMER_SCHEDULE(app_clockCb, NULL, TIMEOUT_1SEC);
    }

    time_sent = true;
}

bool get_time_sent() {

    return time_sent;
}
