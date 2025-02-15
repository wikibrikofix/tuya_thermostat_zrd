#include "app_main.h"

/* data point for manufacturer id -
 * "mpbki2zm"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */
data_point_st_t data_point_model7[DP_IDX_MAXNUM] = {
        {DP_TYPE7_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_7, local_cmd_sys_mode_7},                   // onoff
        {DP_TYPE7_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_7},                                // local temperature
        {DP_TYPE7_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_7, local_cmd_heating_set_7},             // heat setpoint
        {DP_TYPE7_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_7, local_cmd_min_setpoint_7},           // min heat setpoint
        {DP_TYPE7_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_7, local_cmd_max_setpoint_7},           // max heat setpoint
        {DP_TYPE7_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_7, local_cmd_deadband_7},                   // hysteresis
        {DP_TYPE7_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_7, local_cmd_temp_calibration_7},   // local temperature calibration
        {DP_TYPE7_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_7},                       // valve 0x00 - open, 0x01 - close
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_65, DP_BOOL, 1,    1,  remote_cmd_oper_mode_7, local_cmd_oper_mode_7},         // manual (setpoint) / programming (schedule)
        {DP_TYPE7_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_7, local_cmd_keylock_7},             // lock / unlock keys (child lock)
        {DP_TYPE7_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_7, NULL},                       // schedule
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_70, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_7},                        // schedule mon
        {DP_TYPE7_ID_6F, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_7},                        // schedule tue
        {DP_TYPE7_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_7},                        // schedule wed
        {DP_TYPE7_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_7},                        // schedule thu
        {DP_TYPE7_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_7},                        // schedule fri
        {DP_TYPE7_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_7},                        // schedule sat
        {DP_TYPE7_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_7},                        // schedule sun
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_04, DP_BOOL, 1,    1,  remote_cmd_eco_mode_7, local_cmd_eco_mode_7},           // eco mode
        {DP_TYPE7_ID_69, DP_VAL,  4,    10, remote_cmd_eco_mode_heat_temp_7, local_cmd_eco_mode_heat_temp_7},   // eco mode's heat temperature
        {DP_TYPE7_ID_68, DP_VAL,  4,    10, remote_cmd_eco_mode_cool_temp_7, local_cmd_eco_mode_cool_temp_7},   // eco mode's cool temperature
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            //
        {DP_TYPE7_ID_02, DP_ENUM, 1,    1,  NULL, local_cmd_therm_mode_7},                          // thermostat local mode (cold, heat, fan)
};

/*
 *
 * For models   "mpbki2zm"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_set_run_state_7(void *args) {

    run_state_bit_t *run_state_bit = (run_state_bit_t*)args;

    uint16_t runState = 0;
    uint16_t len;
    uint8_t sys_mode;
    uint8_t bit_num = RUN_STATE_FAN_BIT;

    printf("local_cmd_set_run_state_7(). dev_therm_mode: 0x%x\r\n", dev_therm_mode);

    switch (dev_therm_mode) {
        case DEV_THERM_MODE_COLD:
            bit_num = RUN_STATE_COOL_BIT;
            break;
        case DEV_THERM_MODE_HEAT:
            bit_num = RUN_STATE_HEAT_BIT;
            break;
        case DEV_THERM_MODE_FAN:
            bit_num = RUN_STATE_FAN_BIT;
            break;
        default:
            return;
            break;
    }


    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE, &len, (uint8_t*)&sys_mode);

    if (run_state_bit->set || (!run_state_bit->set && bit_num == RUN_STATE_FAN_BIT && sys_mode)) {
        runState |= (1 << bit_num);
    }

    zcl_setAttrVal(APP_ENDPOINT1,
                   ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE,
                   (uint8_t*)&runState);

}



void local_cmd_sys_mode_7(void *args) {

    uint8_t *onoff = (uint8_t*)args;
    run_state_bit_t run_state_bit;
    uint8_t sys_mode;

    if (*onoff == DEV_POWER_OFF) {
#if UART_PRINTF_MODE /* && DEBUG_CMD*/
        printf("Power OFF model7\r\n");
#endif
        sys_mode = SYS_MODE_OFF;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
        run_state_bit.bit_num = RUN_STATE_HEAT_BIT;
        run_state_bit.set = OFF;
        local_cmd_set_run_state_7(&run_state_bit);
    } else {
#if UART_PRINTF_MODE /*&& DEBUG_CMD*/
        printf("Power ON model7\r\n");
#endif
        switch (dev_therm_mode) {
            case DEV_THERM_MODE_COLD:
                sys_mode = SYS_MODE_COOL;
                break;
            case DEV_THERM_MODE_HEAT:
                sys_mode = SYS_MODE_HEAT;
                break;
            case DEV_THERM_MODE_FAN:
                sys_mode = SYS_MODE_FAN;
                break;
            default:
                return;
                break;
        }

        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
    }

    thermostat_settings_save();
}

void local_cmd_therm_mode_7(void* args) {

    uint8_t *mode = (uint8_t*)args;
    uint8_t sys_mode = SYS_MODE_OFF;

    switch (*mode) {
        case DEV_THERM_MODE_COLD:
            dev_therm_mode = DEV_THERM_MODE_COLD;
            sys_mode = SYS_MODE_COOL;
            break;
        case DEV_THERM_MODE_HEAT:
            dev_therm_mode = DEV_THERM_MODE_HEAT;
            sys_mode = SYS_MODE_HEAT;
            break;
        case DEV_THERM_MODE_FAN:
            dev_therm_mode = DEV_THERM_MODE_FAN;
            sys_mode = SYS_MODE_FAN;
            break;
        default:
            break;
    }

    zcl_setAttrVal(APP_ENDPOINT1,
                   ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                   (uint8_t*)&sys_mode);

    thermostat_settings_save();
}

void local_cmd_eco_mode_cool_temp_7(void *args) {

    uint16_t *eco_temp = (uint16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_ECO_COOL_TEMP].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_ECO_COOL_TEMP].divisor == 10) {
        divisor = 10;
    }

    *eco_temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_ECO_MODE_COOL_TEMPERATURE, (uint8_t*)eco_temp);

    thermostat_settings_save();
}

/*
 *
 * For models   "mpbki2zm"
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

static void remote_cmd_therm_mode_7(void* args) {

    uint8_t *mode = (uint8_t*)args;

    if (*mode != SYS_MODE_HEAT && *mode != SYS_MODE_COOL && *mode != SYS_MODE_FAN) {
        return;
    }

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num += 2;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_THERM_MODE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_THERM_MODE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    switch (*mode) {
        case SYS_MODE_COOL:
            data_point->data[0] = DEV_THERM_MODE_COLD;
            dev_therm_mode = DEV_THERM_MODE_COLD;
            break;
        case SYS_MODE_HEAT:
            data_point->data[0] = DEV_THERM_MODE_HEAT;
            dev_therm_mode = DEV_THERM_MODE_HEAT;
            break;
        case SYS_MODE_FAN:
            data_point->data[0] = DEV_THERM_MODE_FAN;
            dev_therm_mode = DEV_THERM_MODE_FAN;
            break;
        default:
            return;
            break;
    }

    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);
    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_sys_mode_7(void *args) {

    uint8_t *mode = (uint8_t*)args;

    if (*mode != SYS_MODE_OFF && *mode != SYS_MODE_HEAT && *mode != SYS_MODE_COOL && *mode != SYS_MODE_FAN) {
        return;
    }

    printf("remote_cmd_sys_mode_7(). mode: 0x%x\r\n", *mode);

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)remote_cmd_pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(remote_cmd_pkt_buff, sizeof(remote_cmd_pkt_buff), seq_num, COMMAND04);

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

    if (*mode == SYS_MODE_OFF) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
        thermostat_settings_save();
    } else {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
        remote_cmd_therm_mode_7(mode);
    }
}

void remote_cmd_eco_mode_cool_temp_7(void *args) {

    int16_t *arg = (int16_t*)args;
    uint32_t eco_temp = *arg;
    uint16_t len;
    int16_t min_temp, max_temp;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_COOL_SETPOINT_LIMIT, &len, (uint8_t*)&min_temp);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_COOL_SETPOINT_LIMIT, &len, (uint8_t*)&max_temp);

    if (eco_temp < min_temp) eco_temp = min_temp;
    if (eco_temp > max_temp) eco_temp = max_temp;

    if (data_point_model[DP_IDX_ECO_COOL_TEMP].divisor == 1) {
        eco_temp /= 100;
    } else if (data_point_model[DP_IDX_ECO_COOL_TEMP].divisor == 10) {
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
    data_point->dp_id = data_point_model[DP_IDX_ECO_COOL_TEMP].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_ECO_COOL_TEMP].type;
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


