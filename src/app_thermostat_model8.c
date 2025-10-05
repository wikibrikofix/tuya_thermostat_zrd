#include "app_main.h"

/* data point for manufacturer id -
 * "7rghpoxo"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */

#define R08_ABS_HEAT_MIN            500
#define R08_ABS_HEAT_MAX            6000
#define R08_HEAT_MIN_MIN            500         // * 100
#define R08_HEAT_MIN_MAX            3500        // * 100
#define R08_HEAT_MAX_MIN            3500        // * 100
#define R08_HEAT_MAX_MAX            6000        // * 100
#define R08_CALIBRATION_MIN        -90          // * 10
#define R08_CALIBRATION_MAX         90          // * 10

#define DP_IDX_SCHEDULE_MODE    DP_IDX_SCHEDULE_MON
#define DP_IDX_SCHEDULE_HOUR    DP_IDX_SCHEDULE_TUE
#define DP_IDX_SCHEDULE_MINUTE  DP_IDX_SCHEDULE_WED
#define DP_IDX_SCHEDULE_TEMP    DP_IDX_SCHEDULE_THU
#define DP_IDX_SCHEDULE_PERIOD  DP_IDX_SCHEDULE_FRI


data_point_st_t data_point_model8[DP_IDX_MAXNUM];

data_point_st_t *init_datapoint_model8() {

    memset(data_point_model8, 0, sizeof(data_point_model8));

    g_zcl_thermostatAttrs.absMinHeatSetpointLimit = R08_ABS_HEAT_MIN;       // min +5°C
    g_zcl_thermostatAttrs.absMaxHeatSetpointLimit = R08_ABS_HEAT_MIN;       // max +45°C

    data_point_model8[DP_IDX_ONOFF].id = DP_TYPE8_ID_01;
    data_point_model8[DP_IDX_ONOFF].type = DP_BOOL;
    data_point_model8[DP_IDX_ONOFF].len = 1;
    data_point_model8[DP_IDX_ONOFF].divisor = 1;
    data_point_model8[DP_IDX_ONOFF].remote_cmd = remote_cmd_sys_mode_8;
    data_point_model8[DP_IDX_ONOFF].local_cmd = local_cmd_onoff_state_8;

    data_point_model8[DP_IDX_TEMP].id = DP_TYPE8_ID_03;
    data_point_model8[DP_IDX_TEMP].type = DP_VAL;
    data_point_model8[DP_IDX_TEMP].len = 4;
    data_point_model8[DP_IDX_TEMP].divisor = 10;
    data_point_model8[DP_IDX_TEMP].local_cmd = local_cmd_inner_sensor_8;

    data_point_model8[DP_IDX_SETPOINT].id = DP_TYPE8_ID_02;
    data_point_model8[DP_IDX_SETPOINT].type = DP_VAL;
    data_point_model8[DP_IDX_SETPOINT].len = 4;
    data_point_model8[DP_IDX_SETPOINT].divisor = 10;
    data_point_model8[DP_IDX_SETPOINT].remote_cmd = remote_cmd_heating_set_8;
    data_point_model8[DP_IDX_SETPOINT].local_cmd = local_cmd_heating_set_8;

    data_point_model8[DP_IDX_MIN].id = DP_TYPE8_ID_10;
    data_point_model8[DP_IDX_MIN].type = DP_VAL;
    data_point_model8[DP_IDX_MIN].len = 4;
    data_point_model8[DP_IDX_MIN].divisor = 10;
    data_point_model8[DP_IDX_MIN].remote_cmd = remote_cmd_min_setpoint_8;
    data_point_model8[DP_IDX_MIN].local_cmd = local_cmd_min_setpoint_8;
    data_point_model8[DP_IDX_MIN].arg1 = R08_HEAT_MIN_MIN;
    data_point_model8[DP_IDX_MIN].arg2 = R08_HEAT_MIN_MAX;

    data_point_model8[DP_IDX_MAX].id = DP_TYPE8_ID_0F;
    data_point_model8[DP_IDX_MAX].type = DP_VAL;
    data_point_model8[DP_IDX_MAX].len = 4;
    data_point_model8[DP_IDX_MAX].divisor = 10;
    data_point_model8[DP_IDX_MAX].remote_cmd = remote_cmd_max_setpoint_8;
    data_point_model8[DP_IDX_MAX].local_cmd = local_cmd_max_setpoint_8;
    data_point_model8[DP_IDX_MAX].arg1 = R08_HEAT_MAX_MIN;
    data_point_model8[DP_IDX_MAX].arg2 = R08_HEAT_MAX_MAX;

    data_point_model8[DP_IDX_CALIBRATION].id = DP_TYPE8_ID_13;
    data_point_model8[DP_IDX_CALIBRATION].type = DP_VAL;
    data_point_model8[DP_IDX_CALIBRATION].len = 4;
    data_point_model8[DP_IDX_CALIBRATION].divisor = 1;
    data_point_model8[DP_IDX_CALIBRATION].remote_cmd = remote_cmd_temp_calibration_8;
    data_point_model8[DP_IDX_CALIBRATION].local_cmd = local_cmd_temp_calibration_8;
    data_point_model8[DP_IDX_CALIBRATION].arg1 = R08_CALIBRATION_MIN;
    data_point_model8[DP_IDX_CALIBRATION].arg2 = R08_CALIBRATION_MAX;

    data_point_model8[DP_IDX_RUNSTATE].id = DP_TYPE8_ID_66;
    data_point_model8[DP_IDX_RUNSTATE].type = DP_ENUM;
    data_point_model8[DP_IDX_RUNSTATE].len = 1;
    data_point_model8[DP_IDX_RUNSTATE].divisor = 1;
    data_point_model8[DP_IDX_RUNSTATE].local_cmd = local_cmd_set_run_state_8;

    data_point_model8[DP_IDX_PROG].id = DP_TYPE8_ID_68;
    data_point_model8[DP_IDX_PROG].type = DP_ENUM;
    data_point_model8[DP_IDX_PROG].len = 1;
    data_point_model8[DP_IDX_PROG].divisor = 1;
    data_point_model8[DP_IDX_PROG].remote_cmd = remote_cmd_oper_mode_8;
    data_point_model8[DP_IDX_PROG].local_cmd = local_cmd_oper_mode_8;

    data_point_model8[DP_IDX_LOCKUNLOCK].id = DP_TYPE8_ID_09;
    data_point_model8[DP_IDX_LOCKUNLOCK].type = DP_BOOL;
    data_point_model8[DP_IDX_LOCKUNLOCK].len = 1;
    data_point_model8[DP_IDX_LOCKUNLOCK].divisor = 1;
    data_point_model8[DP_IDX_LOCKUNLOCK].remote_cmd = remote_cmd_keylock_8;
    data_point_model8[DP_IDX_LOCKUNLOCK].local_cmd = local_cmd_keylock_8;

    data_point_model8[DP_IDX_SCHEDULE].id = DP_TYPE8_ID_6D;
    data_point_model8[DP_IDX_SCHEDULE].type = DP_RAW;
    data_point_model8[DP_IDX_SCHEDULE].len = 0x20;
    data_point_model8[DP_IDX_SCHEDULE].remote_cmd = remote_cmd_set_schedule_8;

    // Mode
    data_point_model8[DP_IDX_SCHEDULE_MODE].id = DP_TYPE8_ID_69;
    data_point_model8[DP_IDX_SCHEDULE_MODE].type = DP_ENUM;
    data_point_model8[DP_IDX_SCHEDULE_MODE].len = 1;

    // Hour
    data_point_model8[DP_IDX_SCHEDULE_HOUR].id = DP_TYPE8_ID_6A;
    data_point_model8[DP_IDX_SCHEDULE_HOUR].type = DP_VAL;
    data_point_model8[DP_IDX_SCHEDULE_HOUR].len = 4;
    data_point_model8[DP_IDX_SCHEDULE_HOUR].divisor = 1;

    // Minute
    data_point_model8[DP_IDX_SCHEDULE_MINUTE].id = DP_TYPE8_ID_6B;
    data_point_model8[DP_IDX_SCHEDULE_MINUTE].type = DP_VAL;
    data_point_model8[DP_IDX_SCHEDULE_MINUTE].len = 4;
    data_point_model8[DP_IDX_SCHEDULE_MINUTE].divisor = 1;

    // Temperature
    data_point_model8[DP_IDX_SCHEDULE_TEMP].id = DP_TYPE8_ID_6C;
    data_point_model8[DP_IDX_SCHEDULE_TEMP].type = DP_VAL;
    data_point_model8[DP_IDX_SCHEDULE_TEMP].len = 4;
    data_point_model8[DP_IDX_SCHEDULE_TEMP].divisor = 1;

    // Period
    data_point_model8[DP_IDX_SCHEDULE_PERIOD].id = DP_TYPE8_ID_6D;
    data_point_model8[DP_IDX_SCHEDULE_PERIOD].type = DP_ENUM;
    data_point_model8[DP_IDX_SCHEDULE_PERIOD].len = 1;
    data_point_model8[DP_IDX_SCHEDULE_PERIOD].local_cmd = local_cmd_set_period_8;

    data_point_model8[DP_IDX_ECO_MODE].id = DP_TYPE8_ID_67;
    data_point_model8[DP_IDX_ECO_MODE].type = DP_BOOL;
    data_point_model8[DP_IDX_ECO_MODE].len = 1;
    data_point_model8[DP_IDX_ECO_MODE].remote_cmd = remote_cmd_eco_mode_8;
    data_point_model8[DP_IDX_ECO_MODE].local_cmd = local_cmd_eco_mode_8;

    data_point_model8[DP_IDX_EXT_CALIBRATION].id = DP_TYPE8_ID_65;
    data_point_model8[DP_IDX_EXT_CALIBRATION].type = DP_VAL;
    data_point_model8[DP_IDX_EXT_CALIBRATION].len = 4;
    data_point_model8[DP_IDX_EXT_CALIBRATION].divisor = 1;
    data_point_model8[DP_IDX_EXT_CALIBRATION].remote_cmd = remote_cmd_ext_temp_calibration_8;
    data_point_model8[DP_IDX_EXT_CALIBRATION].local_cmd = local_cmd_ext_temp_calibration_8;
    data_point_model8[DP_IDX_EXT_CALIBRATION].arg1 = R08_CALIBRATION_MIN;
    data_point_model8[DP_IDX_EXT_CALIBRATION].arg2 = R08_CALIBRATION_MAX;

    return data_point_model8;
}

//data_point_st_t data_point_model8[DP_IDX_MAXNUM] = {
//        {DP_TYPE8_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_8, local_cmd_onoff_state_8},        // onoff
//        {DP_TYPE8_ID_03, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_8},                        // local temperature
//        {DP_TYPE8_ID_02, DP_VAL,  4,    10, remote_cmd_heating_set_8, local_cmd_heating_set_8},     // heat setpoint
//        {DP_TYPE8_ID_10, DP_VAL,  4,    10, remote_cmd_min_setpoint_8, local_cmd_min_setpoint_8},   // min heat setpoint
//        {DP_TYPE8_ID_0F, DP_VAL,  4,    10, remote_cmd_max_setpoint_8, local_cmd_max_setpoint_8},   // max heat setpoint
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // hysteresis
//        {DP_TYPE8_ID_13, DP_VAL,  4,    1,  remote_cmd_temp_calibration_8, local_cmd_temp_calibration_8}, // local temperature calibration
//        {DP_TYPE8_ID_66, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_8},                       // 0x00 - heat, 0x01 - idle
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // sensor IN/AL/OU
//        {DP_TYPE8_ID_68, DP_ENUM, 1,    1,  remote_cmd_oper_mode_8, local_cmd_oper_mode_8},         // manual (setpoint) / programming (schedule)
//        {DP_TYPE8_ID_09, DP_BOOL, 1,    1,  remote_cmd_keylock_8, local_cmd_keylock_8},             // lock / unlock keys (child lock)
//        {DP_TYPE8_ID_6D, DP_RAW,  0x20, 1,  remote_cmd_set_schedule_8, NULL},                       // schedule
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // temperature of outer sensor
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // frost protected
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // heat protected
//        {DP_TYPE8_ID_69, DP_ENUM, 1,    1,  NULL,NULL},                                             // schedule mon (mode)
//        {DP_TYPE8_ID_6A, DP_VAL,  4,    1,  NULL, NULL},                                            // schedule tue (hour)
//        {DP_TYPE8_ID_6B, DP_VAL,  4,    1,  NULL, NULL},                                            // schedule wed (minute)
//        {DP_TYPE8_ID_6C, DP_VAL,  4,    1,  NULL, NULL},                                            // schedule thu (temperature)
//        {DP_TYPE8_ID_6D, DP_ENUM, 1,    1,  NULL, local_cmd_set_period_8},                          // schedule fri (period)
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule sat
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // schedule sun
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // level brightness of screen
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE8_ID_67, DP_BOOL, 1,    1,  remote_cmd_eco_mode_8, local_cmd_eco_mode_8},           // sleep (eco) mode
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // sound on-off
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // settings reset
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // inversion of output
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE8_ID_00, DP_RAW,  0,    0,  NULL, NULL},
//        {DP_TYPE8_ID_65, DP_VAL,  4,    1,  remote_cmd_ext_temp_calibration_8, local_cmd_ext_temp_calibration_8}, // external calibration
//};


/*
 *
 * Local variables and functions
 *
 */

ev_timer_event_t *check_schedule8TimerEvt = NULL;

enum read_schedule_counter_t {
    READ_SCHEDULE_WW = 0,
    READ_SCHEDULE_WW_1,
    READ_SCHEDULE_WW_2,
    READ_SCHEDULE_WW_3,
    READ_SCHEDULE_WW_4,
    READ_SCHEDULE_WW_5,
    READ_SCHEDULE_WW_6,

    READ_SCHEDULE_SAT,
    READ_SCHEDULE_SAT_1,
    READ_SCHEDULE_SAT_2,
    READ_SCHEDULE_SAT_3,
    READ_SCHEDULE_SAT_4,
    READ_SCHEDULE_SAT_5,
    READ_SCHEDULE_SAT_6,

    READ_SCHEDULE_SUN,
    READ_SCHEDULE_SUN_1,
    READ_SCHEDULE_SUN_2,
    READ_SCHEDULE_SUN_3,
    READ_SCHEDULE_SUN_4,
    READ_SCHEDULE_SUN_5,
    READ_SCHEDULE_SUN_6,
};

enum set_schedule_couter_t {
    WRITE_SCHEDULE_WW = 0,
    WRITE_SCHEDULE_WW_1,
    WRITE_SCHEDULE_WW_1_TEMP,
    WRITE_SCHEDULE_WW_1_HOUR,
    WRITE_SCHEDULE_WW_1_MINUTE,
    WRITE_SCHEDULE_WW_2_TEMP,
    WRITE_SCHEDULE_WW_2_HOUR,
    WRITE_SCHEDULE_WW_2_MINUTE,
    WRITE_SCHEDULE_WW_3_TEMP,
    WRITE_SCHEDULE_WW_3_HOUR,
    WRITE_SCHEDULE_WW_3_MINUTE,
    WRITE_SCHEDULE_WW_4_TEMP,
    WRITE_SCHEDULE_WW_4_HOUR,
    WRITE_SCHEDULE_WW_4_MINUTE,
    WRITE_SCHEDULE_WW_5_TEMP,
    WRITE_SCHEDULE_WW_5_HOUR,
    WRITE_SCHEDULE_WW_5_MINUTE,
    WRITE_SCHEDULE_WW_6_TEMP,
    WRITE_SCHEDULE_WW_6_HOUR,
    WRITE_SCHEDULE_WW_6_MINUTE,

    WRITE_SCHEDULE_SAT,
    WRITE_SCHEDULE_SAT_1,
    WRITE_SCHEDULE_SAT_1_TEMP,
    WRITE_SCHEDULE_SAT_1_HOUR,
    WRITE_SCHEDULE_SAT_1_MINUTE,
    WRITE_SCHEDULE_SAT_2_TEMP,
    WRITE_SCHEDULE_SAT_2_HOUR,
    WRITE_SCHEDULE_SAT_2_MINUTE,
    WRITE_SCHEDULE_SAT_3_TEMP,
    WRITE_SCHEDULE_SAT_3_HOUR,
    WRITE_SCHEDULE_SAT_3_MINUTE,
    WRITE_SCHEDULE_SAT_4_TEMP,
    WRITE_SCHEDULE_SAT_4_HOUR,
    WRITE_SCHEDULE_SAT_4_MINUTE,
    WRITE_SCHEDULE_SAT_5_TEMP,
    WRITE_SCHEDULE_SAT_5_HOUR,
    WRITE_SCHEDULE_SAT_5_MINUTE,
    WRITE_SCHEDULE_SAT_6_TEMP,
    WRITE_SCHEDULE_SAT_6_HOUR,
    WRITE_SCHEDULE_SAT_6_MINUTE,

    WRITE_SCHEDULE_SUN,
    WRITE_SCHEDULE_SUN_1,
    WRITE_SCHEDULE_SUN_1_TEMP,
    WRITE_SCHEDULE_SUN_1_HOUR,
    WRITE_SCHEDULE_SUN_1_MINUTE,
    WRITE_SCHEDULE_SUN_2_TEMP,
    WRITE_SCHEDULE_SUN_2_HOUR,
    WRITE_SCHEDULE_SUN_2_MINUTE,
    WRITE_SCHEDULE_SUN_3_TEMP,
    WRITE_SCHEDULE_SUN_3_HOUR,
    WRITE_SCHEDULE_SUN_3_MINUTE,
    WRITE_SCHEDULE_SUN_4_TEMP,
    WRITE_SCHEDULE_SUN_4_HOUR,
    WRITE_SCHEDULE_SUN_4_MINUTE,
    WRITE_SCHEDULE_SUN_5_TEMP,
    WRITE_SCHEDULE_SUN_5_HOUR,
    WRITE_SCHEDULE_SUN_5_MINUTE,
    WRITE_SCHEDULE_SUN_6_TEMP,
    WRITE_SCHEDULE_SUN_6_HOUR,
    WRITE_SCHEDULE_SUN_6_MINUTE,
};

//static uint8_t day_mon, day_sat, day_sun;
static uint8_t read_schedule = READ_SCHEDULE_WW;

static uint8_t buff_schedule8[128];
static uint8_t *size_schedule = buff_schedule8;
static bool day_sent = false;
static bool period_sent = false;
static bool hour_sent = false;
static bool min_sent = false;
static bool temp_sent = false;

temp_schedule_model8_t *temp_schedule8;


static ev_timer_event_t *set_schedule8TimerEvt = NULL;

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

    cmd.numOfTransForSequence = 6;
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

static void set_week_day(uint8_t day) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_MODE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_MODE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = day;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

//    thermostat_settings_save();
}

static void set_time_period(uint8_t period) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_PERIOD].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_PERIOD].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = period;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

//    thermostat_settings_save();
}

static void set_hour(uint32_t hour) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_HOUR].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_HOUR].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (hour >> 24) & 0xFF;
    data_point->data[1] = (hour >> 16) & 0xFF;
    data_point->data[2] = (hour >> 8)  & 0xFF;
    data_point->data[3] = hour & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);
}

static void set_minute(uint32_t minute) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_MINUTE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_MINUTE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (minute >> 24) & 0xFF;
    data_point->data[1] = (minute >> 16) & 0xFF;
    data_point->data[2] = (minute >> 8)  & 0xFF;
    data_point->data[3] = minute & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);
}

static void set_temperature(uint32_t temperature) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_TEMP].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_TEMP].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (temperature >> 24) & 0xFF;
    data_point->data[1] = (temperature >> 16) & 0xFF;
    data_point->data[2] = (temperature >> 8)  & 0xFF;
    data_point->data[3] = temperature & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);
}

static int32_t set_scheduleCb(void *args) {

    if (*size_schedule) {

        if (!day_sent) {
            set_week_day(temp_schedule8->week_day);
            day_sent = true;
            return 0;
        }

        if (!period_sent) {
            set_time_period(temp_schedule8->time_period);
            period_sent = true;
            return 0;
        }

        if (!hour_sent) {
            set_hour(temp_schedule8->hour);
            hour_sent = true;
            return 0;
        }

        if (!min_sent) {
            set_minute(temp_schedule8->minute);
            min_sent = true;
            return 0;
        }

        if (!temp_sent) {
            set_temperature(temp_schedule8->temperature);
            temp_sent = true;
            return 0;
        }

        set_week_day(temp_schedule8->week_day);

        day_sent = false;
        period_sent = false;
        hour_sent = false;
        min_sent = false;
        temp_sent = false;

        *size_schedule -= 1;
        temp_schedule8++;

        if (!*size_schedule) {
            thermostat_settings_save();
            remote_cmd_get_schedule_8();
        }

        return 0;
    }
//    printf("exit from set_scheduleCb\r\n");

    set_schedule8TimerEvt = NULL;
    return -1;
}



/*
 *
 * Global functions
 *
 */

int32_t check_schedule8Cb(void *arg) {

//    printf("read_schedule: %d\r\n", read_schedule);

    switch(read_schedule) {
        case READ_SCHEDULE_WW:
            read_schedule++;
//            day_mon = SCHEDULE8_MON;
            set_week_day(SCHEDULE8_MON);
            break;
        case READ_SCHEDULE_WW_1:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T1);
            break;
        case READ_SCHEDULE_WW_2:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T2);
            break;
        case READ_SCHEDULE_WW_3:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T3);
            break;
        case READ_SCHEDULE_WW_4:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T4);
            break;
        case READ_SCHEDULE_WW_5:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T5);
            break;
        case READ_SCHEDULE_WW_6:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T6);
            break;
        case READ_SCHEDULE_SAT:
            read_schedule++;
//            day_sat = SCHEDULE8_SAT;
            set_week_day(SCHEDULE8_SAT);
            break;
        case READ_SCHEDULE_SAT_1:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T1);
            break;
        case READ_SCHEDULE_SAT_2:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T2);
            break;
        case READ_SCHEDULE_SAT_3:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T3);
            break;
        case READ_SCHEDULE_SAT_4:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T4);
            break;
        case READ_SCHEDULE_SAT_5:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T5);
            break;
        case READ_SCHEDULE_SAT_6:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T6);
            break;
        case READ_SCHEDULE_SUN:
            read_schedule++;
//            day_sun = SCHEDULE8_SUN;
            set_week_day(SCHEDULE8_SUN);
            break;
        case READ_SCHEDULE_SUN_1:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T1);
            break;
        case READ_SCHEDULE_SUN_2:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T2);
            break;
        case READ_SCHEDULE_SUN_3:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T3);
            break;
        case READ_SCHEDULE_SUN_4:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T4);
            break;
        case READ_SCHEDULE_SUN_5:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T5);
            break;
        case READ_SCHEDULE_SUN_6:
            read_schedule++;
            set_time_period(SCHEDULE_BIT_T6);
            break;
        default:
            for(uint8_t i = 0; i < 6; i++) {
                g_zcl_scheduleData.schedule_mon[i].transTime = schedule_model8[SCHEDULE8_MON].schedule[i].hour * 60;
                g_zcl_scheduleData.schedule_mon[i].transTime += schedule_model8[SCHEDULE8_MON].schedule[i].minute;
                g_zcl_scheduleData.schedule_mon[i].heatSetpoint = schedule_model8[SCHEDULE8_MON].schedule[i].temperature * 10;

                g_zcl_scheduleData.schedule_sat[i].transTime = schedule_model8[SCHEDULE8_SAT].schedule[i].hour * 60;
                g_zcl_scheduleData.schedule_sat[i].transTime += schedule_model8[SCHEDULE8_SAT].schedule[i].minute;
                g_zcl_scheduleData.schedule_sat[i].heatSetpoint = schedule_model8[SCHEDULE8_SAT].schedule[i].temperature * 10;

                g_zcl_scheduleData.schedule_sun[i].transTime = schedule_model8[SCHEDULE8_SUN].schedule[i].hour * 60;
                g_zcl_scheduleData.schedule_sun[i].transTime += schedule_model8[SCHEDULE8_SUN].schedule[i].minute;
                g_zcl_scheduleData.schedule_sun[i].heatSetpoint = schedule_model8[SCHEDULE8_SUN].schedule[i].temperature * 10;
            }
            thermostat_settings_save();
            remote_cmd_get_schedule_8();
            check_schedule8TimerEvt = NULL;
            return -1;
            break;
    }

    return 0;
}

/*
 *
 * For models   "7rghpoxo"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_ext_temp_calibration_8(void *args) {

    int8_t *temp = (int8_t*)args;

    if (data_point_model[DP_IDX_EXT_CALIBRATION].divisor == 1) {
        *temp *= 10;
    } else if (data_point_model[DP_IDX_EXT_CALIBRATION].divisor == 100) {
        *temp /= 10;
    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_EXT_TEMP_CALIBRATION, (uint8_t*)temp);

    thermostat_settings_save();

}

void local_cmd_set_period_8(void *args) {

    temp_schedule_model8_t *temp_schedule = (temp_schedule_model8_t*)args;

    switch(temp_schedule->time_period) {
        case SCHEDULE_BIT_T1:
//            printf("SCHEDULE_BIT_T1\r\n");
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T1].hour = temp_schedule->hour;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T1].minute = temp_schedule->minute;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T1].temperature = temp_schedule->temperature;

//            printf("hour:        %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T1].hour);
//            printf("minute:      %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T1].minute);
//            printf("temperature: %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T1].temperature);
            break;
        case SCHEDULE_BIT_T2:
//            printf("SCHEDULE_BIT_T2\r\n");
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T2].hour = temp_schedule->hour;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T2].minute = temp_schedule->minute;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T2].temperature = temp_schedule->temperature;

//            printf("hour:        %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T2].hour);
//            printf("minute:      %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T2].minute);
//            printf("temperature: %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T2].temperature);
            break;
        case SCHEDULE_BIT_T3:
//            printf("SCHEDULE_BIT_T3\r\n");
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T3].hour = temp_schedule->hour;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T3].minute = temp_schedule->minute;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T3].temperature = temp_schedule->temperature;

//            printf("hour:        %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T3].hour);
//            printf("minute:      %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T3].minute);
//            printf("temperature: %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T3].temperature);
            break;
        case SCHEDULE_BIT_T4:
//            printf("SCHEDULE_BIT_T4\r\n");
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T4].hour = temp_schedule->hour;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T4].minute = temp_schedule->minute;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T4].temperature = temp_schedule->temperature;

//            printf("hour:        %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T4].hour);
//            printf("minute:      %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T4].minute);
//            printf("temperature: %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T4].temperature);
            break;
        case SCHEDULE_BIT_T5:
//            printf("SCHEDULE_BIT_T5\r\n");
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T5].hour = temp_schedule->hour;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T5].minute = temp_schedule->minute;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T5].temperature = temp_schedule->temperature;

//            printf("hour:        %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T5].hour);
//            printf("minute:      %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T5].minute);
//            printf("temperature: %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T5].temperature);
            break;
        case SCHEDULE_BIT_T6:
//            printf("SCHEDULE_BIT_T6\r\n");
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T6].hour = temp_schedule->hour;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T6].minute = temp_schedule->minute;
            schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T6].temperature = temp_schedule->temperature;

//            printf("hour:        %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T6].hour);
//            printf("minute:      %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T6].minute);
//            printf("temperature: %d\r\n", schedule_model8[temp_schedule->week_day].schedule[SCHEDULE_BIT_T6].temperature);
            break;
        default:
            return;
//            break;
    }

//    printf("temp_schedule.week_day:    %d\r\n", temp_schedule->week_day);
//    printf("temp_schedule.hour:        %d\r\n", temp_schedule->hour);
//    printf("temp_schedule.minute:      %d\r\n", temp_schedule->minute);
//    printf("temp_schedule.temperature: %d\r\n", temp_schedule->temperature);
//    printf("temp_schedule.time_period: %d\r\n", temp_schedule->time_period);

}

/*
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_ext_temp_calibration_8(void *args) {

    int8_t *arg = (int8_t*)args;
    int8_t temp = *arg;

    if(data_point_model[DP_IDX_EXT_CALIBRATION].id == 0) return;

    if (temp < CLIENT_TEMP_CALIBRATION_MIN || temp > CLIENT_TEMP_CALIBRATION_MAX) {
        return;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    temp /= 10; // 90 -> 9, -90 -> -9
    if (data_point_model[DP_IDX_EXT_CALIBRATION].divisor == 10) {
        temp *= 10;
    } else if (data_point_model[DP_IDX_EXT_CALIBRATION].divisor == 100) {
        temp *= 100;
    }

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_EXT_CALIBRATION].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_EXT_CALIBRATION].type;
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
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

}

void remote_cmd_set_schedule_8(void *args) {

    temp_schedule8 = (temp_schedule_model8_t*)buff_schedule8+1;

    temp_schedule_model8_t *p_temp_schedule = temp_schedule8;

    if (set_schedule8TimerEvt) {
        TL_ZB_TIMER_CANCEL(&set_schedule8TimerEvt);
    }

    if (check_schedule8TimerEvt) {
        TL_ZB_TIMER_CANCEL(&check_schedule8TimerEvt);
    }

    uint16_t hour, minute, temperature;

    *size_schedule = 0;

    for (uint8_t i = 0; i < 6; i++) {
        hour = g_zcl_scheduleData.schedule_mon[i].transTime / 60;
        minute = g_zcl_scheduleData.schedule_mon[i].transTime % 60;
        temperature = g_zcl_scheduleData.schedule_mon[i].heatSetpoint / 10;

        if (hour != schedule_model8[SCHEDULE8_MON].schedule[i].hour ||
            minute != schedule_model8[SCHEDULE8_MON].schedule[i].minute ||
            temperature != schedule_model8[SCHEDULE8_MON].schedule[i].temperature) {

            p_temp_schedule->hour = hour;
            p_temp_schedule->minute = minute;
            p_temp_schedule->temperature = temperature;
            p_temp_schedule->time_period = i;
            p_temp_schedule->week_day = SCHEDULE8_MON;
            *size_schedule += 1;
            p_temp_schedule++;
        }
    }

    for (uint8_t i = 0; i < 6; i++) {
        hour = g_zcl_scheduleData.schedule_sat[i].transTime / 60;
        minute = g_zcl_scheduleData.schedule_sat[i].transTime % 60;
        temperature = g_zcl_scheduleData.schedule_sat[i].heatSetpoint / 10;

        if (hour != schedule_model8[SCHEDULE8_SAT].schedule[i].hour ||
            minute != schedule_model8[SCHEDULE8_SAT].schedule[i].minute ||
            temperature != schedule_model8[SCHEDULE8_SAT].schedule[i].temperature) {

            p_temp_schedule->hour = hour;
            p_temp_schedule->minute = minute;
            p_temp_schedule->temperature = temperature;
            p_temp_schedule->time_period = i;
            p_temp_schedule->week_day = SCHEDULE8_SAT;
            *size_schedule += 1;
            p_temp_schedule++;
        }
    }

    for (uint8_t i = 0; i < 6; i++) {
        hour = g_zcl_scheduleData.schedule_sun[i].transTime / 60;
        minute = g_zcl_scheduleData.schedule_sun[i].transTime % 60;
        temperature = g_zcl_scheduleData.schedule_sun[i].heatSetpoint / 10;

        if (hour != schedule_model8[SCHEDULE8_SUN].schedule[i].hour ||
            minute != schedule_model8[SCHEDULE8_SUN].schedule[i].minute ||
            temperature != schedule_model8[SCHEDULE8_SUN].schedule[i].temperature) {

            p_temp_schedule->hour = hour;
            p_temp_schedule->minute = minute;
            p_temp_schedule->temperature = temperature;
            p_temp_schedule->time_period = i;
            p_temp_schedule->week_day = SCHEDULE8_SUN;
            *size_schedule += 1;
            p_temp_schedule++;

        }
    }

//    printf("size_schedule: %d\r\n", *size_schedule);

    set_schedule8TimerEvt = TL_ZB_TIMER_SCHEDULE(set_scheduleCb, NULL, TIMEOUT_650MS);

}


void remote_cmd_get_schedule_8(void *args) {

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
