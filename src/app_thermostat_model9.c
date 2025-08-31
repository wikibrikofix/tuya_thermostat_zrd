#include "app_main.h"

/* data point for manufacturer id -
 * "6a4vxfnv"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */
data_point_st_t data_point_model9[DP_IDX_MAXNUM] = {
/*00*/  {DP_TYPE9_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_9, local_cmd_onoff_state_9},                // onoff
/*01*/  {DP_TYPE9_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_9},                                // local temperature
/*02*/  {DP_TYPE9_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_9, local_cmd_heating_set_9},             // heat setpoint
/*03*/  {DP_TYPE9_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_9, local_cmd_min_setpoint_9},           // min heat setpoint
/*04*/  {DP_TYPE9_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_9, local_cmd_max_setpoint_9},           // max heat setpoint
/*05*/  {DP_TYPE9_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_9, local_cmd_deadband_9},                   // hysteresis
/*06*/  {DP_TYPE9_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_9, local_cmd_temp_calibration_9},   // local temperature calibration
/*07*/  {DP_TYPE9_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_9},                       // 0x00 - heat, 0x01 - idle
/*08*/  {DP_TYPE9_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_9, local_cmd_sensor_used_9},     // sensor IN/AL/OU
/*09*/  {DP_TYPE9_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_9, local_cmd_oper_mode_9},         // manual (setpoint) / programming (schedule)
/*10*/  {DP_TYPE9_ID_27, DP_BOOL, 1,    1,  remote_cmd_keylock_9, local_cmd_keylock_9},             // lock / unlock keys (child lock)
/*11*/  {DP_TYPE9_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_9, NULL},                       // schedule
/*12*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
/*13*/  {DP_TYPE9_ID_66, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_9},                      // temperature of outer sensor
/*14*/  {DP_TYPE9_ID_6F, DP_VAL,  4,    10, remote_cmd_frost_protect_9, local_cmd_frost_protect_9}, // frost protected
/*15*/  {DP_TYPE9_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_9, local_cmd_heat_protect_9},   // heat protected
/*16*/  {DP_TYPE9_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule mon
/*17*/  {DP_TYPE9_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule tue
/*18*/  {DP_TYPE9_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule wed
/*19*/  {DP_TYPE9_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule thu
/*20*/  {DP_TYPE9_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule fri
/*21*/  {DP_TYPE9_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule sat
/*22*/  {DP_TYPE9_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_9},                        // schedule sun
/*23*/  {DP_TYPE9_ID_71, DP_VAL,  4,    1,  remote_cmd_level_day_9, local_cmd_level_day_9},         // level brightness 06:00-22:00
/*24*/  {DP_TYPE9_ID_72, DP_VAL,  4,    1,  remote_cmd_level_night_9, local_cmd_level_night_9},     // level brightness 22:00-06:00
/*25*/  {DP_TYPE9_ID_28, DP_BOOL, 1,    1,  remote_cmd_eco_mode_9, local_cmd_eco_mode_9},           // eco mode
/*26*/  {DP_TYPE9_ID_70, DP_VAL,  4,    10, remote_cmd_eco_mode_temp_9, local_cmd_eco_mode_temp_9}, // eco mode's temperature
/*27*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
/*28*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
/*29*/  {DP_TYPE9_ID_1C, DP_BOOL, 1,    1,  remote_cmd_setting_reset_9, local_cmd_setting_reset_9}, // default setting
/*30*/  {DP_TYPE9_ID_74, DP_ENUM, 4,    1,  remote_cmd_inversion_9, local_cmd_inversion_9},         // type relay NC or NO (inversion)
/*31*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
/*32*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
/*33*/  {DP_TYPE9_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
/*34*/  {DP_TYPE9_ID_73, DP_VAL,  4,    1,  remote_cmd_ext_temp_calibration_9, local_cmd_ext_temp_calibration_9}, // external sensor calibration
/*35*/  {DP_TYPE9_ID_75, DP_ENUM, 1,    1,  remote_cmd_mode_keylock_9, local_cmd_mode_keylock_9},   // mode key lock
};


void remote_cmd_mode_keylock_9(void *args) {

    uint8_t *mode = (uint8_t*)args;

    if (*mode != 0x00 && *mode != 0x01) {
        return;
    }

    printf("remote_cmd_mode_keylock_9: %d\r\n", *mode);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_MODE_LOCK].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_MODE_LOCK].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    if (*mode == 0x00) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_to_ring_cmd(out_pkt, true);
        set_seq_num(seq_num);
    } else if (*mode == 0x01) {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_to_ring_cmd(out_pkt, true);
        set_seq_num(seq_num);
    }

    thermostat_settings_save();
}

void remote_cmd_deadband_9(void *args) {

    uint8_t *arg = (uint8_t*)args;
    uint32_t hysteresis = *arg;

    if (data_point_model[DP_IDX_DEADZONE].id == 0) return;

    /* 5 -> 0.5°C ... 50 -> 5°C */
    if (hysteresis < 5 || hysteresis > 50) {
        return;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;


    if (data_point_model[DP_IDX_DEADZONE].divisor == 10) {
        hysteresis *= 10;
    } else if (data_point_model[DP_IDX_DEADZONE].divisor == 100) {
        hysteresis *= 100;
    }

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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
    add_to_ring_cmd(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}


void local_cmd_mode_keylock_9(void *args) {

    uint8_t *mode = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_MODE_KEYLOCK, (uint8_t*)mode);

    thermostat_settings_save();
}

