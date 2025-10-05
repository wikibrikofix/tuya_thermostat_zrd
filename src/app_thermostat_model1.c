#include "app_main.h"

/* data point for manufacturer id -
 * "u9bfwha0"
 * "aoclfnxz"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
*/

#define R01_ABS_HEAT_MIN            500
#define R01_ABS_HEAT_MAX            4500
#define R01_HEAT_MIN_MIN            500         // * 100
#define R01_HEAT_MAX_MAX            4500        // * 100
#define R01_HEAT_PROTECT_MIN        4500        // * 100
#define R01_HEAT_PROTECT_MAX        7000        // * 100
#define R01_DEADZONE_MIN            1
#define R01_DEADZONE_MAX            5
#define R01_CALIBRATION_MIN        -90          // * 10
#define R01_CALIBRATION_MAX         90          // * 10

//data_point_st_t data_point_model1[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model1() {

    memset(data_point_model_common, 0, sizeof(data_point_model_common));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R01_ABS_HEAT_MIN;       // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R01_ABS_HEAT_MIN;       // max +45°C

    data_point_model_common[DP_IDX_ONOFF].id = DP_TYPE1_ID_01;
    data_point_model_common[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model_common[DP_IDX_ONOFF].len = 1;
    data_point_model_common[DP_IDX_ONOFF].divisor = 1;
    data_point_model_common[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_1;
    data_point_model_common[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_1;

    data_point_model_common[DP_IDX_TEMP].id = DP_TYPE1_ID_18;
    data_point_model_common[DP_IDX_TEMP].type = DP_VAL;
    data_point_model_common[DP_IDX_TEMP].len = 4;
    data_point_model_common[DP_IDX_TEMP].divisor = 10;
    data_point_model_common[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_1;

    data_point_model_common[DP_IDX_SETPOINT].id = DP_TYPE1_ID_10;
    data_point_model_common[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model_common[DP_IDX_SETPOINT].len = 4;
    data_point_model_common[DP_IDX_SETPOINT].divisor = 1;
    data_point_model_common[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_1;
    data_point_model_common[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_1;

    data_point_model_common[DP_IDX_MAX].id = DP_TYPE1_ID_13;
    data_point_model_common[DP_IDX_MAX].type = DP_VAL;
    data_point_model_common[DP_IDX_MAX].len = 4;
    data_point_model_common[DP_IDX_MAX].divisor = 1;
    data_point_model_common[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_1;
    data_point_model_common[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_1;
    data_point_model_common[DP_IDX_MAX].arg1 = R01_HEAT_MIN_MIN;
    data_point_model_common[DP_IDX_MAX].arg2 = R01_HEAT_MAX_MAX;

    data_point_model_common[DP_IDX_DEADZONE].id = DP_TYPE1_ID_1A;
    data_point_model_common[DP_IDX_DEADZONE].type = DP_VAL;
    data_point_model_common[DP_IDX_DEADZONE].len = 4;
    data_point_model_common[DP_IDX_DEADZONE].divisor = 1;
    data_point_model_common[DP_IDX_DEADZONE].remote_cmd = remote_cmd_deadband_1;
    data_point_model_common[DP_IDX_DEADZONE].local_cmd = local_cmd_deadband_1;
    data_point_model_common[DP_IDX_DEADZONE].arg1 = R01_DEADZONE_MIN;
    data_point_model_common[DP_IDX_DEADZONE].arg2 = R01_DEADZONE_MAX;

    data_point_model_common[DP_IDX_CALIBRATION].id = DP_TYPE1_ID_1B;
    data_point_model_common[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model_common[DP_IDX_CALIBRATION].len = 4;
    data_point_model_common[DP_IDX_CALIBRATION].divisor = 1;
    data_point_model_common[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_1;
    data_point_model_common[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_1;
    data_point_model_common[DP_IDX_CALIBRATION].arg1 = R01_CALIBRATION_MIN;
    data_point_model_common[DP_IDX_CALIBRATION].arg2 = R01_CALIBRATION_MAX;

    data_point_model_common[DP_IDX_RUNSTATE].id = DP_TYPE1_ID_24;
    data_point_model_common[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model_common[DP_IDX_RUNSTATE].len = 1;
    data_point_model_common[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model_common[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_1;

    data_point_model_common[DP_IDX_SENSOR].id = DP_TYPE1_ID_2B;
    data_point_model_common[DP_IDX_SENSOR].type = DP_ENUM;
    data_point_model_common[DP_IDX_SENSOR].len = 1;
    data_point_model_common[DP_IDX_SENSOR].divisor = 1;
    data_point_model_common[DP_IDX_SENSOR].remote_cmd = remote_cmd_sensor_used_1;
    data_point_model_common[DP_IDX_SENSOR].local_cmd = local_cmd_sensor_used_1;

    data_point_model_common[DP_IDX_PROG].id = DP_TYPE1_ID_02;
    data_point_model_common[DP_IDX_PROG].type = DP_ENUM;
    data_point_model_common[DP_IDX_PROG].len = 1;
    data_point_model_common[DP_IDX_PROG].divisor = 1;
    data_point_model_common[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_1;
    data_point_model_common[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_1;

    data_point_model_common[DP_IDX_LOCKUNLOCK].id = DP_TYPE1_ID_28;
    data_point_model_common[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model_common[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_1;
    data_point_model_common[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_1;

    data_point_model_common[DP_IDX_SCHEDULE].id = DP_TYPE1_ID_65;
    data_point_model_common[DP_IDX_SCHEDULE].type = DP_RAW;
    data_point_model_common[DP_IDX_SCHEDULE].len = 0x24;
    data_point_model_common[DP_IDX_SCHEDULE].divisor = 1;
    data_point_model_common[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_1;
    data_point_model_common[DP_IDX_SCHEDULE].local_cmd = local_cmd_set_schedule_1;

    return data_point_model_common;
}

//data_point_st_t data_point_model1[DP_IDX_MAXNUM] = {
//        {DP_TYPE1_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_1, local_cmd_onoff_state_1},                // on off
//        {DP_TYPE1_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_1},                                // local temperature
//        {DP_TYPE1_ID_10, DP_VAL,  4,    1,  remote_cmd_heating_set_1, local_cmd_heating_set_1},             // heat setpoint
//        {DP_TYPE1_ID_00, DP_VAL,  0,    0,  NULL, NULL},                                                    // heat min - not support
//        {DP_TYPE1_ID_13, DP_VAL,  4,    1,  remote_cmd_max_setpoint_1, local_cmd_max_setpoint_1},           // max heat setpoint
//        {DP_TYPE1_ID_1A, DP_VAL,  4,    1,  remote_cmd_deadband_1, local_cmd_deadband_1},                   // hysteresis
//        {DP_TYPE1_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_1, local_cmd_temp_calibration_1},   // local temperature calibration
//        {DP_TYPE1_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_1},                               // 0x00 - heat, 0x01 - idle
//        {DP_TYPE1_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_1, local_cmd_sensor_used_1},             // sensor IN/AL/OU
//        {DP_TYPE1_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_1, local_cmd_oper_mode_1},                 // manual (setpoint) / programming (schedule)
//        {DP_TYPE1_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_1, local_cmd_keylock_1},                     // lock / unlock keys (child lock)
//        {DP_TYPE1_ID_65, DP_RAW,  0x24, 1,  remote_cmd_set_schedule_1, local_cmd_set_schedule_1},           // schedule
//};

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
}


/*
 *
 * For models   "u9bfwha0"
 *              "aoclfnxz"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_oper_mode_1(void *args) {

    uint8_t *mode = (uint8_t*)args;

#if UART_PRINTF_MODE && DEBUG_CMD
            printf("Thermostat mode %s\r\n", *mode?"programming":"manual");
#endif

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE, mode);

    thermostat_settings_save();
}

void local_cmd_set_schedule_1(void *args) {

    data_point_t *data_point = (data_point_t*)args;

    uint16_t len = data_point->dp_len / 3;
    uint8_t *ptr = data_point->data;

    for (uint8_t i = 0; i < len;) {
        for (uint8_t ii = 0; ii < 4; ii++) {
            if (i < 4) {
                g_zcl_scheduleData.schedule_mon[ii].transTime = *ptr++ * 60;
                g_zcl_scheduleData.schedule_mon[ii].transTime += *ptr++;
                g_zcl_scheduleData.schedule_mon[ii].heatSetpoint = *ptr++ / 2 * 100;
//                printf("mon. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_mon[ii].transTime,
//                        g_zcl_scheduleData.schedule_mon[ii].heatSetpoint);
                i++;
            } else if (i < 8) {
                g_zcl_scheduleData.schedule_sat[ii].transTime = *ptr++ * 60;
                g_zcl_scheduleData.schedule_sat[ii].transTime += *ptr++;
                g_zcl_scheduleData.schedule_sat[ii].heatSetpoint = *ptr++ / 2 * 100;
//                printf("sat. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_sat[ii].transTime,
//                        g_zcl_scheduleData.schedule_sat[ii].heatSetpoint);
                i++;
            } else {
                g_zcl_scheduleData.schedule_sun[ii].transTime = *ptr++ * 60;
                g_zcl_scheduleData.schedule_sun[ii].transTime += *ptr++;
                g_zcl_scheduleData.schedule_sun[ii].heatSetpoint = *ptr++ / 2 * 100;
//                printf("sun. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_sun[ii].transTime,
//                        g_zcl_scheduleData.schedule_sun[ii].heatSetpoint);
                i++;
            }
        }
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
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_oper_mode_1(void *args) {

    uint8_t *oper_mode = (uint8_t*)args;

    if (data_point_model[DP_IDX_PROG].id == 0) return;

    if (*oper_mode > 1) return;


    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    data_point->data[0] = *oper_mode;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_set_schedule_1(void *args) {

    args_get_schedule_any.day = *(uint8_t*)args;
    args_get_schedule_any.rsp = false;

    printf("day: %d\r\n", args_get_schedule_any.day);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_any);
}

void remote_cmd_get_schedule_1(void *args) {

    uint8_t *seqNum = (uint8_t*)args;

    args_get_schedule_mon.day = DAY_MON;
    args_get_schedule_mon.seqNum = *seqNum;
    args_get_schedule_mon.rsp = true;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_mon);

    args_get_schedule_sat.day = DAY_SAT;
    args_get_schedule_sat.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_sat);

    args_get_schedule_sun.day = DAY_SUN;
    args_get_schedule_sun.rsp = false;
    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_sun);
}
