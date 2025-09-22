#include "app_main.h"

/* data point for manufacturer id -
 * "_TZE204_8byfmxdv"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb, arg1, arg2
*/

data_point_st_t data_point_model0B[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model0B() {

    memset(data_point_model0B, 0, sizeof(data_point_model0B));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = 100;            // min +1°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = 5000;           // max +50°C

    data_point_model0B[DP_IDX_ONOFF].id = DP_TYPE0B_ID_01;
    data_point_model0B[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model0B[DP_IDX_ONOFF].len = 1;
    data_point_model0B[DP_IDX_ONOFF].divisor = 1;
    data_point_model0B[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_0B;
    data_point_model0B[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_0B;

    data_point_model0B[DP_IDX_TEMP].id = DP_TYPE0B_ID_18;
    data_point_model0B[DP_IDX_TEMP].type = DP_VAL;
    data_point_model0B[DP_IDX_TEMP].len = 4;
    data_point_model0B[DP_IDX_TEMP].divisor = 10;
    data_point_model0B[DP_IDX_TEMP].remote_cmd = NULL;
    data_point_model0B[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_0B;

    data_point_model0B[DP_IDX_SETPOINT].id = DP_TYPE0B_ID_10;
    data_point_model0B[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model0B[DP_IDX_SETPOINT].len = 4;
    data_point_model0B[DP_IDX_SETPOINT].divisor = 10;
    data_point_model0B[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_0B;
    data_point_model0B[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_0B;
    data_point_model0B[DP_IDX_SETPOINT].arg1 = g_zcl_thermostatAttrs.minHeatSetpointLimit;
    data_point_model0B[DP_IDX_SETPOINT].arg2 = g_zcl_thermostatAttrs.maxHeatSetpointLimit;

    data_point_model0B[DP_IDX_MIN].id = DP_TYPE0B_ID_1A;
    data_point_model0B[DP_IDX_MIN].type = DP_VAL;
    data_point_model0B[DP_IDX_MIN].len = 4;
    data_point_model0B[DP_IDX_MIN].divisor = 10;
    data_point_model0B[DP_IDX_MIN].remote_cmd = remote_cmd_min_setpoint_0B;
    data_point_model0B[DP_IDX_MIN].local_cmd = local_cmd_min_setpoint_0B;
    data_point_model0B[DP_IDX_MIN].arg1 = 10;                                   // 1°C
    data_point_model0B[DP_IDX_MIN].arg2 = 50;                                   // 5°C

    data_point_model0B[DP_IDX_MAX].id = DP_TYPE0B_ID_13;
    data_point_model0B[DP_IDX_MAX].type = DP_VAL;
    data_point_model0B[DP_IDX_MAX].len = 4;
    data_point_model0B[DP_IDX_MAX].divisor = 10;
    data_point_model0B[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_0B;
    data_point_model0B[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_0B;
    data_point_model0B[DP_IDX_MAX].arg1 = 350;                                  // 35°C
    data_point_model0B[DP_IDX_MAX].arg2 = 500;                                  // 50°C

    data_point_model0B[DP_IDX_DEADZONE].id = DP_TYPE0B_ID_65;
    data_point_model0B[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model0B[DP_IDX_DEADZONE].len = 4;
    data_point_model0B[DP_IDX_DEADZONE].divisor = 1;
    data_point_model0B[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_0B;
    data_point_model0B[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_0B;
    data_point_model0B[DP_IDX_DEADZONE].arg1 = 5;                               // 0.5°C
    data_point_model0B[DP_IDX_DEADZONE].arg2 = 50;                              // 5°C

    data_point_model0B[DP_IDX_CALIBRATION].id = DP_TYPE0B_ID_1B;
    data_point_model0B[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model0B[DP_IDX_CALIBRATION].len = 4;
    data_point_model0B[DP_IDX_CALIBRATION].divisor = 1;
    data_point_model0B[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_0B;
    data_point_model0B[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_0B;
    data_point_model0B[DP_IDX_CALIBRATION].arg1 = -9;
    data_point_model0B[DP_IDX_CALIBRATION].arg2 = 9;

    data_point_model0B[DP_IDX_RUNSTATE].id = DP_TYPE0B_ID_24;
    data_point_model0B[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model0B[DP_IDX_RUNSTATE].len = 1;
    data_point_model0B[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model0B[DP_IDX_RUNSTATE].remote_cmd = NULL;
    data_point_model0B[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_0B;

    data_point_model0B[DP_IDX_SENSOR].id = DP_TYPE0B_ID_2B;
    data_point_model0B[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model0B[DP_IDX_SENSOR].len = 1;
    data_point_model0B[DP_IDX_SENSOR].divisor = 1;
    data_point_model0B[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_0B;
    data_point_model0B[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_0B;

    data_point_model0B[DP_IDX_PROG].id = DP_TYPE0B_ID_02;
    data_point_model0B[DP_IDX_PROG].type = DP_ENUM;
    data_point_model0B[DP_IDX_PROG].len = 1;
    data_point_model0B[DP_IDX_PROG].divisor = 1;
    data_point_model0B[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_0B;
    data_point_model0B[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_0B;

    data_point_model0B[DP_IDX_LOCKUNLOCK].id = DP_TYPE0B_ID_28;
    data_point_model0B[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model0B[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model0B[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model0B[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_0B;
    data_point_model0B[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_0B;

    data_point_model0B[DP_IDX_SCHEDULE].id = DP_TYPE0A_ID_30;
    data_point_model0B[DP_IDX_SCHEDULE].type = DP_RAW;
    data_point_model0B[DP_IDX_SCHEDULE].len = 48;
    data_point_model0B[DP_IDX_SCHEDULE].divisor = 1;
    data_point_model0B[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_0B;
    data_point_model0B[DP_IDX_SCHEDULE].local_cmd = local_cmd_set_schedule_0B;

    data_point_model0B[DP_IDX_LEVEL_A].id = DP_TYPE0B_ID_34;
    data_point_model0B[DP_IDX_LEVEL_A].type = DP_ENUM;
    data_point_model0B[DP_IDX_LEVEL_A].len = 1;
    data_point_model0B[DP_IDX_LEVEL_A].divisor = 1;
    data_point_model0B[DP_IDX_LEVEL_A].remote_cmd = remote_cmd_level_0B;
    data_point_model0B[DP_IDX_LEVEL_A].local_cmd = local_cmd_level_0B;

    return data_point_model0B;
}

/*
 *
 * Local variables and functions
 *
 */

static void get_schedule(void *args) {

    if(!zb_isDeviceJoinedNwk()) return;

    args_get_schedule_t *args_get_schedule = (args_get_schedule_t*)args;

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

    if (args_get_schedule->day & DAY_MON) {
        //mon
        heat_mode =  g_zcl_scheduleData.schedule_mon;
        cmd.dayOfWeekForSequence = DAY_MON;
    } else if (args_get_schedule->day & DAY_SAT) {
        //sat
        heat_mode =  g_zcl_scheduleData.schedule_sat;
        cmd.dayOfWeekForSequence = DAY_SAT;
    } else  if (args_get_schedule->day & DAY_SUN){
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

    if (args_get_schedule->rsp) {
        zcl_thermostat_getWeeklyScheduleRspCmdSend(APP_ENDPOINT1, &dstEpInfo, 0, args_get_schedule->seqNum, &cmd);
    } else {
        zcl_thermostat_setWeeklyScheduleCmdSend(APP_ENDPOINT1, &dstEpInfo, 0, &cmd);
    }
    args_get_schedule->rsp = false;
}

/*
 *
 *  Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_set_schedule_0B(void *args) {

    data_point_t *data_point = (data_point_t*)args;

    uint8_t *ptr = data_point->data, lo, hi;
    uint16_t temp;

    for (uint8_t i = 0; i < 4; i++) {
        g_zcl_scheduleData.schedule_mon[i].transTime = *ptr++ * 60;
        g_zcl_scheduleData.schedule_mon[i].transTime += *ptr++;
        hi = *ptr++;
        lo = *ptr++;
        temp = BUILD_U16(lo, hi) * 10;
        g_zcl_scheduleData.schedule_mon[i].heatSetpoint = temp;
//                printf("mon. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_mon[i].transTime,
//                        g_zcl_scheduleData.schedule_mon[i].heatSetpoint);
    }

    for (uint8_t i = 0; i < 4; i++) {
        g_zcl_scheduleData.schedule_sat[i].transTime = *ptr++ * 60;
        g_zcl_scheduleData.schedule_sat[i].transTime += *ptr++;
        hi = *ptr++;
        lo = *ptr++;
        temp = BUILD_U16(lo, hi) * 10;
        g_zcl_scheduleData.schedule_sat[i].heatSetpoint = temp;
//                printf("sat. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_sat[i].transTime,
//                        g_zcl_scheduleData.schedule_sat[i].heatSetpoint);
    }

    for (uint8_t i = 0; i < 4; i++) {
        g_zcl_scheduleData.schedule_sun[i].transTime = *ptr++ * 60;
        g_zcl_scheduleData.schedule_sun[i].transTime += *ptr++;
        hi = *ptr++;
        lo = *ptr++;
        temp = BUILD_U16(lo, hi) * 10;
        g_zcl_scheduleData.schedule_sun[i].heatSetpoint = temp;
//        printf("sun. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_sun[i].transTime,
//                g_zcl_scheduleData.schedule_sun[i].heatSetpoint);
    }

    thermostat_settings_save();

    args_get_schedule_mon.day = DAY_MON;
    args_get_schedule_mon.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_mon);

    args_get_schedule_sat.day = DAY_SAT;
    args_get_schedule_sat.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_sat);

    args_get_schedule_sun.day = DAY_SUN;
    args_get_schedule_sun.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_sun);

}
/*
 *
 *  Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_level_0B(void *args) {


    uint8_t *level = (uint8_t*)args;

    printf("level: %d\r\n", *level);

    if (data_point_model[DP_IDX_LEVEL_A].id == 0) return;

    if (*level > 2) {
        return;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LEVEL_A].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LEVEL_A].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *level;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_set_schedule_0B(void *args) {

    args_get_schedule_any.day = *(uint8_t*)args;
    args_get_schedule_any.rsp = false;

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(52);
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
            *pstrd++ = ((heat_mode[ii].heatSetpoint/10) >> 8) & 0xFF;
            out_pkt->pkt_len++;
            *pstrd++ = (heat_mode[ii].heatSetpoint/10) & 0xFF;
            out_pkt->pkt_len++;
        }
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_any);
}
