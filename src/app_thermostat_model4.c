#include "app_main.h"

/* data point for manufacturer id -
 * "xyugziqv"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */
data_point_st_t data_point_model4[DP_IDX_MAXNUM] = {
        {DP_TYPE4_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_4, local_cmd_onoff_state_4},                // onoff
        {DP_TYPE4_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_4},                                // local temperature
        {DP_TYPE4_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_4, local_cmd_heating_set_4},             // heat setpoint
        {DP_TYPE4_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_4, local_cmd_min_setpoint_4},           // min heat setpoint
        {DP_TYPE4_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_4, local_cmd_max_setpoint_4},           // max heat setpoint
        {DP_TYPE4_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_4, local_cmd_deadband_4},                   // hysteresis
        {DP_TYPE4_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_4, local_cmd_temp_calibration_4},   // local temperature calibration
        {DP_TYPE4_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_4},                       // 0x00 - heat, 0x01 - idle
        {DP_TYPE4_ID_66, DP_ENUM, 1,    1,  remote_cmd_sensor_used_4, local_cmd_sensor_used_4},     // sensor IN/AL/OU
        {DP_TYPE4_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_4, local_cmd_oper_mode_4},         // manual (setpoint) / programming (schedule)
        {DP_TYPE4_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_4, local_cmd_keylock_4},             // lock / unlock keys (child lock)
        {DP_TYPE4_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_4, NULL},                       // schedule
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
        {DP_TYPE4_ID_71, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_4},                      // temperature of outer sensor
        {DP_TYPE4_ID_75, DP_VAL,  4,    10, remote_cmd_frost_protect_4, local_cmd_frost_protect_4}, // frost protected
        {DP_TYPE4_ID_74, DP_VAL,  4,    10, remote_cmd_heat_protect_4, local_cmd_heat_protect_4},   // heat protected
        {DP_TYPE4_ID_70, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule mon
        {DP_TYPE4_ID_6F, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule tue
        {DP_TYPE4_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule wed
        {DP_TYPE4_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule thu
        {DP_TYPE4_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule fri
        {DP_TYPE4_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule sat
        {DP_TYPE4_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_4},                        // schedule sun
        {DP_TYPE4_ID_73, DP_VAL,  4,    1,  remote_cmd_level_4, local_cmd_level_4},                 // level brightness of screen
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE4_ID_04, DP_BOOL, 1,    1,  remote_cmd_eco_mode_4, local_cmd_eco_mode_4},           // eco mode
        {DP_TYPE4_ID_69, DP_VAL,  4,    10, remote_cmd_eco_mode_temp_4, local_cmd_eco_mode_temp_4}, // eco mode's temperature
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE4_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
};

/*
 *
 * For models   "xyugziqv"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */


/*
 *
 * For models   "xyugziqv"
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_level_4(void *args) {

    uint8_t *level = (uint8_t*)args;

//    printf("remote_cmd_level_day_3(). level: %d\r\n", *level);

    if (*level < 0 || *level > 9) return;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);


    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LEVEL_A].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LEVEL_A].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (*level >> 24) & 0xFF;
    data_point->data[1] = (*level >> 16) & 0xFF;
    data_point->data[2] = (*level >> 8)  & 0xFF;
    data_point->data[3] = *level & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}


