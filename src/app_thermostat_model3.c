#include "app_main.h"

/* data point for manufacturer id -
 * "tagezcph"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */
data_point_st_t data_point_model2[DP_IDX_MAXNUM] = {
        {DP_TYPE3_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_3, local_cmd_onoff_state_3},                // onoff
        {DP_TYPE3_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_3},                                // local temperature
        {DP_TYPE3_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_3, local_cmd_heating_set_3},             // heat setpoint
        {DP_TYPE3_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_3, local_cmd_min_setpoint_3},           // min heat setpoint
        {DP_TYPE3_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_3, local_cmd_max_setpoint_3},           // max heat setpoint
        {DP_TYPE3_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_3, local_cmd_deadband_3},                   // hysteresis
        {DP_TYPE3_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_3, local_cmd_temp_calibration_3},   // local temperature calibration
        {DP_TYPE3_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_3},                       // 0x00 - heat, 0x01 - idle
        {DP_TYPE3_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_3, local_cmd_sensor_used_3},     // sensor IN/AL/OU
        {DP_TYPE3_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_3, local_cmd_oper_mode_3},         // manual (setpoint) / programming (schedule)
        {DP_TYPE3_ID_27, DP_BOOL, 1,    1,  remote_cmd_keylock_3, local_cmd_keylock_3},             // lock / unlock keys (child lock)
        {DP_TYPE3_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_3, NULL},                       // schedule
        {DP_TYPE3_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
        {DP_TYPE3_ID_66, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_3},                      // temperature of outer sensor
        {DP_TYPE3_ID_6F, DP_VAL,  4,    10, remote_cmd_frost_protect_3, local_cmd_frost_protect_3}, // frost protected
        {DP_TYPE3_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_3, local_cmd_heat_protect_3},   // heat protected
        {DP_TYPE3_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule mon
        {DP_TYPE3_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule tue
        {DP_TYPE3_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule wed
        {DP_TYPE3_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule thu
        {DP_TYPE3_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule fri
        {DP_TYPE3_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule sat
        {DP_TYPE3_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_3},                        // schedule sun
        {DP_TYPE3_ID_71, DP_VAL,  4,    1,  remote_cmd_level_day_3, local_cmd_level_day_3},         // level brightness 06:00-22:00
        {DP_TYPE3_ID_72, DP_VAL,  4,    1,  remote_cmd_level_night_3, local_cmd_level_night_3},     // level brightness 22:00-06:00
        {DP_TYPE3_ID_28, DP_BOOL, 1,    1,  remote_cmd_eco_mode_3, local_cmd_eco_mode_3},           // eco mode
        {DP_TYPE3_ID_70, DP_VAL,  4,    10, remote_cmd_eco_mode_temp_3, local_cmd_eco_mode_temp_3}, // eco mode's temperature
};

/*
 *
 * For models   "tagezcph"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_eco_mode_3(void *args) {

    uint8_t *eco_mode = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE, (uint8_t*)eco_mode);

    thermostat_settings_save();
}

void local_cmd_eco_mode_temp_3(void *args) {

    uint16_t *eco_temp = (uint16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_ECO_TEMP].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_ECO_TEMP].divisor == 10) {
        divisor = 10;
    }

    *eco_temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE_TEMPERATURE, (uint8_t*)eco_temp);

    thermostat_settings_save();
}

void local_cmd_level_day_3(void *args) {

    uint16_t *level = (uint16_t*)args;
//    uint16_t divisor = 1;

    printf("local_cmd_level_day_3(). level: %d\r\n", *level);

//    if (data_point_model[DP_IDX_LEVEL_A].divisor == 1) {
//        divisor = 100;
//    } else if (data_point_model[DP_IDX_LEVEL_A].divisor == 10) {
//        divisor = 10;
//    }

//    *level *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);

    thermostat_settings_save();
}

void local_cmd_level_night_3(void *args) {

    uint16_t *level = (uint16_t*)args;
//    uint16_t divisor = 1;

    printf("local_cmd_level_night_3(). level: %d\r\n", *level);

//    if (data_point_model[DP_IDX_LEVEL_B].divisor == 1) {
//        divisor = 100;
//    } else if (data_point_model[DP_IDX_LEVEL_B].divisor == 10) {
//        divisor = 10;
//    }

//    *level *= divisor;

    zcl_setAttrVal(APP_ENDPOINT2, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);

    thermostat_settings_save();
}

/*
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_eco_mode_3(void *args) {

    uint8_t *eco_mode = (uint8_t*)args;

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_ECO_MODE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_ECO_MODE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = *eco_mode;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_eco_mode_temp_3(void *args) {

    int16_t *arg = (int16_t*)args;
    uint32_t eco_temp = *arg;
    uint16_t len;
    int16_t min_temp, max_temp;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&min_temp);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&max_temp);

    if (eco_temp < min_temp) eco_temp = min_temp;
    if (eco_temp > max_temp) eco_temp = max_temp;

//    eco_temp /= 100; // 1500 -> 15°C
//
//    if (data_point_model[DP_IDX_ECO_TEMP].divisor == 10) {
//        eco_temp *= 10;
//    } else if (data_point_model[DP_IDX_ECO_TEMP].divisor == 100) {
//        eco_temp *= 100;
//    }

    if (data_point_model[DP_IDX_ECO_TEMP].divisor == 1) {
        eco_temp /= 100;
    } else if (data_point_model[DP_IDX_ECO_TEMP].divisor == 10) {
        eco_temp /= 10;
    }


    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_ECO_TEMP].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_ECO_TEMP].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (eco_temp >> 24) & 0xFF;
    data_point->data[1] = (eco_temp >> 16) & 0xFF;
    data_point->data[2] = (eco_temp >> 8)  & 0xFF;
    data_point->data[3] = eco_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_level_day_3(void *args) {

    uint8_t *level = (uint8_t*)args;

    printf("remote_cmd_level_day_3(). level: %d\r\n", *level);

    if (*level < 0 || *level > 8) return;

//    if (data_point_model[DP_IDX_LEVEL_A].divisor == 10) {
//        *level *= 10;
//    } else if (data_point_model[DP_IDX_LEVEL_A].divisor == 100) {
//        *level *= 100;
//    }

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
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_level_night_3(void *args) {

    uint8_t *level = (uint8_t*)args;

    printf("remote_cmd_level_night_3(). level: %d\r\n", *level);

    if (*level < 0 || *level > 8) return;

//    if (data_point_model[DP_IDX_LEVEL_B].divisor == 10) {
//        *level *= 10;
//    } else if (data_point_model[DP_IDX_LEVEL_B].divisor == 100) {
//        *level *= 100;
//    }

    zcl_setAttrVal(APP_ENDPOINT2, ZCL_CLUSTER_GEN_LEVEL_CONTROL, ZCL_ATTRID_LEVEL_CURRENT_LEVEL, (uint8_t*)level);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_LEVEL_B].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_LEVEL_B].type;
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
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

