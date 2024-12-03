#include "app_main.h"

uint8_t thermostat_mode = DEV_THERM_MODE_MANUAL;

void remote_smd_sys_mode(uint8_t mode) {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_ONOFF].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_ONOFF].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    if (mode == SYS_MODE_OFF) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    } else if (mode == SYS_MODE_HEAT) {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    }
}

void remote_smd_heating_set(int32_t temp) {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    if (data_point_model[DP_IDX_SETPOINT].divisor == 1) {
        temp /= 100;
    } else if (data_point_model[DP_IDX_SETPOINT].divisor == 10) {
        temp /= 10;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SETPOINT].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SETPOINT].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (temp >> 24) & 0xFF;
    data_point->data[1] = (temp >> 16) & 0xFF;
    data_point->data[2] = (temp >> 8)  & 0xFF;
    data_point->data[3] = temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_smd_temp_calibration(int8_t temp) {

    if(data_point_model[DP_IDX_CALIBRATION].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    temp /= 10; // 90 -> 9, -90 -> -9
    if (data_point_model[DP_IDX_CALIBRATION].divisor == 10) {
        temp *= 10;
    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 100) {
        temp *= 100;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_CALIBRATION].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_CALIBRATION].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    int32_t dev_temp = temp;
    data_point->data[0] = (dev_temp >> 24) & 0xFF;
    data_point->data[1] = (dev_temp >> 16) & 0xFF;
    data_point->data[2] = (dev_temp >> 8)  & 0xFF;
    data_point->data[3] = dev_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_smd_display_mode(uint8_t mode) {

//    pkt_output_t *pkt = (pkt_output_t*)cmdTx[CMD_DISPLAY];
//    pkt->cnt++;
//
//    if (mode == ZCL_DISPLAY_MODE_CELSIUS) {
//        pkt->cmd_value = DEV_DISPLAY_MODE_CELSIUS;
//        add_cmd_queue(CMD_DISPLAY, true, cmdTx[CMD_DISPLAY]);
//    } else if (mode == ZCL_DISPLAY_MODE_FAHRENHEIT) {
//        pkt->cmd_value = DEV_DISPLAY_MODE_FAHRENHEIT;
//        add_cmd_queue(CMD_DISPLAY, true, cmdTx[CMD_DISPLAY]);
//    }
}

void remote_smd_keylock(uint8_t keylock) {

    if(data_point_model[DP_IDX_LOCKUNLOCK].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LOCKUNLOCK].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LOCKUNLOCK].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = keylock;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_sensor_used(uint8_t sensor_used) {

    if (data_point_model[DP_IDX_SENSOR].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SENSOR].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SENSOR].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = sensor_used;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_deadband(uint32_t hysteresis) {

    if (data_point_model[DP_IDX_DEADZONE].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;


    if (data_point_model[DP_IDX_DEADZONE].divisor == 10) {
        hysteresis *= 10;
    } else if (data_point_model[DP_IDX_DEADZONE].divisor == 100) {
        hysteresis *= 100;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_DEADZONE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_DEADZONE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (hysteresis >> 24) & 0xFF;
    data_point->data[1] = (hysteresis >> 16) & 0xFF;
    data_point->data[2] = (hysteresis >> 8)  & 0xFF;
    data_point->data[3] = hysteresis & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_min_setpoint(uint32_t min_temp) {
//    printf("min_temp: %d\r\n", min_temp);

    if (data_point_model[DP_IDX_MIN].id == 0) return;

//    min_temp /= 10;
//    uint8_t pkt_buff[DATA_MAX_LEN+12];
//    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
//    uint16_t seq_num = get_seq_num();
//    seq_num++;
//
//    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);
//
//    out_pkt->len = reverse16(8);
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//
//    data_point_t *data_point = (data_point_t*)out_pkt->data;
//    data_point->dp_id = DP_ID_1A;
//    out_pkt->pkt_len++;
//    data_point->dp_type = DP_VAL;
//    out_pkt->pkt_len++;
//    data_point->dp_len = (reverse16(4));
//    out_pkt->pkt_len++;
//    out_pkt->pkt_len++;
//    data_point->data[0] = (min_temp >> 24) & 0xFF;
//    data_point->data[1] = (min_temp >> 16) & 0xFF;
//    data_point->data[2] = (min_temp >> 8)  & 0xFF;
//    data_point->data[3] = min_temp & 0xFF;
//    out_pkt->pkt_len += 4;
//    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
//    add_cmd_queue(out_pkt, true);
//
//    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_max_setpoint(uint32_t max_temp) {

    if (data_point_model[DP_IDX_MAX].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    max_temp /= 100; // 4400 -> 44°C

    if (data_point_model[DP_IDX_MAX].divisor == 10) {
        max_temp *= 10;
    } else if (data_point_model[DP_IDX_MAX].divisor == 100) {
        max_temp *= 100;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_MAX].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_MAX].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (max_temp >> 24) & 0xFF;
    data_point->data[1] = (max_temp >> 16) & 0xFF;
    data_point->data[2] = (max_temp >> 8)  & 0xFF;
    data_point->data[3] = max_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_oper_mode(uint8_t oper_mode) {

    if (data_point_model[DP_IDX_PROG].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_PROG].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_PROG].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = oper_mode;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_set_weekly_schedule() {

    if (data_point_model[DP_IDX_SCHEDULE].id == 0) return;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    switch(manuf_name) {
        case MANUF_NAME_0:
            set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

            out_pkt->len = reverse16(40);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;

            data_point_t *data_point = (data_point_t*)out_pkt->data;
            data_point->dp_id = data_point_model[DP_IDX_SCHEDULE].id;
            out_pkt->pkt_len++;
            data_point->dp_type = data_point_model[DP_IDX_SCHEDULE].type;
            out_pkt->pkt_len++;
            data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE].len));
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;

            uint8_t *pstrd = data_point->data;
            heatMode_t *heat_mode;

            for (uint8_t i = 0; i < 3; i++) {
                if (i == 0) {
                    heat_mode = g_zcl_scheduleData.schedule_mon;
                } else if (i == 1) {
                    heat_mode = g_zcl_scheduleData.schedule_sat;
                } else {
                    heat_mode = g_zcl_scheduleData.schedule_sun;
                }
                for (uint8_t ii = 0; ii < 4; ii++) {
                    *pstrd++ = heat_mode[ii].transTime/60;
                    out_pkt->pkt_len++;
                    *pstrd++ = heat_mode[ii].transTime%60;
                    out_pkt->pkt_len++;
                    *pstrd++ = heat_mode[ii].heatSetpoint/100*2;
                    out_pkt->pkt_len++;
                }
            }
            *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_cmd_queue(out_pkt, true);
            break;
        case MANUF_NAME_1:
            break;
        default:
            break;
    }

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void set_run_state_bit(uint8_t bit_num, bool set) {

    uint16_t runState;
    uint16_t len;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE, &len, (uint8_t*)&runState);

    if (set) {
        runState |= (1 << bit_num);
    } else {
        runState &= ~( 1 << bit_num);
    }

    zcl_setAttrVal(APP_ENDPOINT1,
                   ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE,
                   (uint8_t*)&runState);

}

void thermostat_onoff_state(int8_t onoff) {

    uint8_t sys_mode;

    if (onoff == DEV_POWER_OFF) {
#if UART_PRINTF_MODE && DEBUG_CMD
        printf("Power OFF\r\n");
#endif
        sys_mode = SYS_MODE_OFF;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
        set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
    } else {
#if UART_PRINTF_MODE && DEBUG_CMD
        printf("Power ON\r\n");
#endif
        sys_mode = SYS_MODE_HEAT;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
    }

}

//void thermostat_heatset_state(int32_t tempF) {
//
//    zcl_thermostatAttr_t *tempAttrs = zcl_thermostatAttrGet();
//
//    int16_t tempC = zcl_convert_temperature_fromFtoC(tempF/10);
//
//#if UART_PRINTF_MODE && DEBUG_CMD
//    printf("Heat set temperature: %d F, %d C, localTemperature: %d C\r\n", tempF, tempC, tempAttrs->localTemperature);
//#endif
//    tempAttrs->occupiedHeatingSetpoint = tempC;
//    if (tempAttrs->systemMode == SYS_MODE_HEAT && thermostat_mode == DEV_THERM_MODE_MANUAL) {
//        if (tempAttrs->occupiedHeatingSetpoint > tempAttrs->localTemperature) {
//            set_run_state_bit(RUN_STATE_HEAT_BIT, ON);
//        } else {
//            set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
//        }
//    } else if (tempAttrs->systemMode == SYS_MODE_OFF) {
//        set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
//    }
//
//}

void thermostat_get_weekly_schedule(uint8_t day) {

    if(!zb_isDeviceJoinedNwk()) return;

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

    zcl_thermostat_setWeeklyScheduleCmd_t cmd;
    heatMode_t *heat_mode;

    cmd.dayOfWeekForSequence = 0;

    if (manuf_name == MANUF_NAME_0) {

        if (day == 0) {
            //mon
            heat_mode =  g_zcl_scheduleData.schedule_mon;
            cmd.dayOfWeekForSequence = DAY_MON;
        } else if (day == 1) {
            //sat
            heat_mode =  g_zcl_scheduleData.schedule_sat;
            cmd.dayOfWeekForSequence = DAY_SAT;
        } else  if (day == 2){
            //sun
            heat_mode =  g_zcl_scheduleData.schedule_sun;
            cmd.dayOfWeekForSequence = DAY_SUN;
        } else {
            return;
        }

        cmd.numOfTransForSequence = 4;
        cmd.sequenceMode.pHeatMode = heat_mode;
        cmd.modeForSequence = HEAT_SERPOINT_FIELD_PRESENT;

//        for (uint8_t i = 0; i < cmd.numOfTransForSequence; i++) {
//            printf("i: %d, time: %d, temp: %d\r\n", i, cmd.sequenceMode.pHeatMode[i].transTime, cmd.sequenceMode.pHeatMode[i].heatSetpoint);
//        }

    } else if (manuf_name == MANUF_NAME_1) {
    } else {
        return;
    }

    zcl_thermostat_setWeeklyScheduleCmdSend(APP_ENDPOINT1, &dstEpInfo, 0, &cmd);

}

nv_sts_t thermostat_settings_save() {
    nv_sts_t st = NV_SUCC;

#ifdef ZCL_THERMOSTAT
#if NV_ENABLE
    thermostat_settings_t thermostat_settings;
    uint16_t len;
    int16_t     minHeatSetpointLimit;
    int16_t     maxHeatSetpointLimit;
    int8_t      localTemperatureCalibration;
    int16_t     occupiedHeatingSetpoint;
    uint8_t     manual_progMode;
    uint8_t     sensor_used;
    uint8_t     dead_band;
    uint8_t     keypadLockout;

    st = nv_flashReadNew(1, NV_MODULE_APP, NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);
    bool save = false;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&minHeatSetpointLimit);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&maxHeatSetpointLimit);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, &len, (uint8_t*)&localTemperatureCalibration);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, &len, (uint8_t*)&occupiedHeatingSetpoint);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE, &len, (uint8_t*)&manual_progMode);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, &len, (uint8_t*)&sensor_used);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND, &len, (uint8_t*)&dead_band);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT, &len, (uint8_t*)&keypadLockout);


    if(st == NV_SUCC) {
        if (memcmp(&thermostat_settings.schedule_data, &g_zcl_scheduleData, sizeof(zcl_scheduleData_t)) != 0) {
            memcpy(&thermostat_settings.schedule_data, &g_zcl_scheduleData, sizeof(zcl_scheduleData_t));
            save = true;
        }

        if (thermostat_settings.minHeatSetpointLimit != minHeatSetpointLimit) {
            thermostat_settings.minHeatSetpointLimit = minHeatSetpointLimit;
            save = true;
        }

        if (thermostat_settings.maxHeatSetpointLimit != maxHeatSetpointLimit) {
            thermostat_settings.maxHeatSetpointLimit = maxHeatSetpointLimit;
            save = true;
        }

        if (thermostat_settings.localTemperatureCalibration != localTemperatureCalibration) {
            thermostat_settings.localTemperatureCalibration = localTemperatureCalibration;
            save = true;
        }

        if (thermostat_settings.occupiedHeatingSetpoint != occupiedHeatingSetpoint) {
            thermostat_settings.occupiedHeatingSetpoint = occupiedHeatingSetpoint;
            save = true;
        }

        if (thermostat_settings.manual_progMode != manual_progMode) {
            thermostat_settings.manual_progMode = manual_progMode;
            save = true;
        }

        if (thermostat_settings.sensor_used != sensor_used) {
            thermostat_settings.sensor_used = sensor_used;
            save = true;
        }

        if (thermostat_settings.dead_band != dead_band) {
            thermostat_settings.dead_band = dead_band;
            save = true;
        }

        if (thermostat_settings.keypadLockout != keypadLockout) {
            thermostat_settings.keypadLockout = keypadLockout;
            save = true;
        }

        if (save) {
#if UART_PRINTF_MODE && DEBUG_SAVE
        printf("Settings saved\r\n");
#endif
        st = nv_flashWriteNew(1, NV_MODULE_APP,  NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);

        }
    } else if (st == NV_ITEM_NOT_FOUND) {

#if UART_PRINTF_MODE && DEBUG_SAVE
        printf("Settings saved\r\n");
#endif

        memcpy(&thermostat_settings.schedule_data, &g_zcl_scheduleData, sizeof(zcl_scheduleData_t));
        thermostat_settings.minHeatSetpointLimit = minHeatSetpointLimit;
        thermostat_settings.maxHeatSetpointLimit = maxHeatSetpointLimit;
        thermostat_settings.localTemperatureCalibration = localTemperatureCalibration;
        thermostat_settings.occupiedHeatingSetpoint = occupiedHeatingSetpoint;
        thermostat_settings.occupiedHeatingSetpoint = occupiedHeatingSetpoint;
        thermostat_settings.sensor_used = sensor_used;
        thermostat_settings.dead_band = dead_band;
        thermostat_settings.keypadLockout = keypadLockout;

        st = nv_flashWriteNew(1, NV_MODULE_APP,  NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);
    }
#else
    st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

    return st;
}

nv_sts_t thermostat_settings_restore() {
    nv_sts_t st = NV_SUCC;

#if UART_PRINTF_MODE && DEBUG_SAVE
        printf("Settings restored\r\n");
#endif

#ifdef ZCL_THERMOSTAT
#if NV_ENABLE

    thermostat_settings_t thermostat_settings;

    st = nv_flashReadNew(1, NV_MODULE_APP,  NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);

    memcpy(&g_zcl_scheduleData, &thermostat_settings.schedule_data, sizeof(zcl_scheduleData_t));
    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, (uint8_t*)&thermostat_settings.minHeatSetpointLimit);
    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, (uint8_t*)&thermostat_settings.maxHeatSetpointLimit);
    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, (uint8_t*)&thermostat_settings.localTemperatureCalibration);
    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, (uint8_t*)&thermostat_settings.occupiedHeatingSetpoint);
    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, (uint8_t*)&thermostat_settings.sensor_used);
    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND, (uint8_t*)&thermostat_settings.dead_band);
    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT, (uint8_t*)&thermostat_settings.keypadLockout);


#else
    st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

    return st;
}


