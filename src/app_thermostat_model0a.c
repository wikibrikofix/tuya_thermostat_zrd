#include "app_main.h"

/* data point for manufacturer id -
 * "_TZE284_xalsoe3m"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
*/

data_point_st_t data_point_model0A[DP_IDX_MAXNUM] = {
/*00*/  {DP_TYPE0A_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_0A, local_cmd_onoff_state_0A},             // onoff
/*01*/  {DP_TYPE0A_ID_10, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_0A},                              // local temperature
/*02*/  {DP_TYPE0A_ID_32, DP_VAL,  4,    1,  remote_cmd_heating_set_0A, local_cmd_heating_set_0A},          // heat setpoint
/*03*/  {DP_TYPE0A_ID_12, DP_VAL,  4,    1,  remote_cmd_min_setpoint_0A, local_cmd_min_setpoint_0A},        // min heat setpoint
/*04*/  {DP_TYPE0A_ID_22, DP_VAL,  4,    1,  remote_cmd_max_setpoint_0A, local_cmd_max_setpoint_0A},        // max heat setpoint
/*05*/  {DP_TYPE0A_ID_66, DP_VAL,  4,    1,  remote_cmd_deadband_0A, local_cmd_deadband_0A},                // hysteresis
/*06*/  {DP_TYPE0A_ID_13, DP_VAL,  4,    1,  remote_cmd_temp_calibration_0A, local_cmd_temp_calibration_0A},// local temperature calibration
/*07*/  {DP_TYPE0A_ID_2F, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_0A},                     // 0x00 - heat, 0x01 - idle
/*08*/  {DP_TYPE0A_ID_20, DP_ENUM, 1,    1,  remote_cmd_sensor_used_0A, local_cmd_sensor_used_0A},  // sensor IN/OU/AL
/*09*/  {DP_TYPE0A_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_0A, local_cmd_oper_mode_0A},      // manual (setpoint) / programming (schedule)
/*10*/  {DP_TYPE0A_ID_27, DP_BOOL, 1,    1,  remote_cmd_keylock_0A, local_cmd_keylock_0A},          // lock / unlock keys (child lock)
/*11*/  {DP_TYPE0A_ID_44, DP_RAW,  0x30, 1,  remote_cmd_set_schedule_0A, local_cmd_set_schedule_0A},// schedule
/*12*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // unknown
/*13*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // temperature of outer sensor
/*14*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // frost protected
/*15*/  {DP_TYPE0A_ID_65, DP_VAL,  4,    1,  remote_cmd_heat_protect_0A, local_cmd_heat_protect_0A},// heat protected
/*16*/  {DP_TYPE0A_ID_00, DP_RAW,  0x0,  10, NULL, NULL},                      // schedule mon
/*17*/  {DP_TYPE0A_ID_00, DP_RAW,  0x0,  10, NULL, NULL},                      // schedule tue
/*18*/  {DP_TYPE0A_ID_00, DP_RAW,  0x0,  10, NULL, NULL},                      // schedule wed
/*19*/  {DP_TYPE0A_ID_00, DP_RAW,  0x0,  10, NULL, NULL},                      // schedule thu
/*20*/  {DP_TYPE0A_ID_00, DP_RAW,  0x0,  10, NULL, NULL},                      // schedule fri
/*21*/  {DP_TYPE0A_ID_00, DP_RAW,  0x0,  10, NULL, NULL},                      // schedule sat
/*22*/  {DP_TYPE0A_ID_00, DP_RAW,  0x0,  10, NULL, NULL},                      // schedule sun
/*23*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    1,  NULL, NULL},                                           // level brightness 06:00-22:00
/*24*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    1,  NULL, NULL},                                           // level brightness 22:00-06:00
/*25*/  {DP_TYPE0A_ID_28, DP_BOOL, 1,    1,  remote_cmd_eco_mode_0A, local_cmd_eco_mode_0A},        // eco mode
/*26*/  {DP_TYPE0A_ID_00, DP_VAL,  0,    0,  NULL, NULL},                                           // eco mode's heat temperature
/*27*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // eco mode's cool temperature
/*28*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // sound
/*29*/  {DP_TYPE0A_ID_00, DP_BOOL, 0,    0,  NULL, NULL},                                           // default setting
/*30*/  {DP_TYPE0A_ID_00, DP_ENUM, 0,    0,  NULL, NULL},                                           // type relay NC or NO (inversion)
/*31*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // thermostat mode ext.
/*32*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // fan mode
/*33*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // fan control
/*34*/  {DP_TYPE0A_ID_00, DP_VAL,  0,    0,  NULL, NULL},                                           // external sensor calibration
/*35*/  {DP_TYPE0A_ID_00, DP_ENUM, 0,    0,  NULL, NULL},                                           // mode key lock
};

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
 *  Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_set_schedule_0A(void *args) {

    data_point_t *data_point = (data_point_t*)args;

    uint8_t *ptr = data_point->data, lo, hi;
    uint16_t temp;

    for (uint8_t i = 0; i < 4; i++) {
        g_zcl_scheduleData.schedule_mon[i].transTime = *ptr++ * 60;
        g_zcl_scheduleData.schedule_mon[i].transTime += *ptr++;
        hi = *ptr++;
        lo = *ptr++;
        temp = BUILD_U16(lo, hi) * 100;
        g_zcl_scheduleData.schedule_mon[i].heatSetpoint = temp;
//                printf("mon. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_mon[i].transTime,
//                        g_zcl_scheduleData.schedule_mon[i].heatSetpoint);
    }

    for (uint8_t i = 0; i < 4; i++) {
        g_zcl_scheduleData.schedule_sat[i].transTime = *ptr++ * 60;
        g_zcl_scheduleData.schedule_sat[i].transTime += *ptr++;
        hi = *ptr++;
        lo = *ptr++;
        temp = BUILD_U16(lo, hi) * 100;
        g_zcl_scheduleData.schedule_sat[i].heatSetpoint = temp;
//                printf("sat. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_sat[i].transTime,
//                        g_zcl_scheduleData.schedule_sat[i].heatSetpoint);
    }

    for (uint8_t i = 0; i < 4; i++) {
        g_zcl_scheduleData.schedule_sun[i].transTime = *ptr++ * 60;
        g_zcl_scheduleData.schedule_sun[i].transTime += *ptr++;
        hi = *ptr++;
        lo = *ptr++;
        temp = BUILD_U16(lo, hi) * 100;
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

void remote_cmd_set_schedule_0A(void *args) {

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
            *pstrd++ = ((heat_mode[ii].heatSetpoint/100) >> 8) & 0xFF;
            out_pkt->pkt_len++;
            *pstrd++ = (heat_mode[ii].heatSetpoint/100) & 0xFF;
            out_pkt->pkt_len++;
        }
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

    TL_SCHEDULE_TASK(get_schedule, &args_get_schedule_any);
}
