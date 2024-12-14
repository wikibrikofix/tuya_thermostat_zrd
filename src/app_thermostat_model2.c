#include "app_main.h"

/* data point for manufacturer id -
 * "edl8pz1k"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */
data_point_st_t data_point_model1[DP_IDX_MAXNUM] = {
        {DP_TYPE1_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_1, local_cmd_onoff_state_1},                // onoff
        {DP_TYPE1_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_1},                                // local temperature
        {DP_TYPE1_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_1, local_cmd_heating_set_1},             // heat setpoint
        {DP_TYPE1_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_1, local_cmd_min_setpoint_1},           // min heat setpoint
        {DP_TYPE1_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_1, local_cmd_max_setpoint_1},           // max heat setpoint
        {DP_TYPE1_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_1, local_cmd_deadband_1},                   // hysteresis
        {DP_TYPE1_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_1, local_cmd_temp_calibration_1},   // local temperature calibration
        {DP_TYPE1_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_1},                       // 0x00 - heat, 0x01 - idle
        {DP_TYPE1_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_1, local_cmd_sensor_used_1},     // sensor IN/AL/OU
        {DP_TYPE1_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_1, local_cmd_oper_mode_1},         // manual (setpoint) / programming (schedule)
        {DP_TYPE1_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_1, local_cmd_keylock_1},             // lock / unlock keys (child lock)
        {DP_TYPE1_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_1, NULL},                       // schedule
        {DP_TYPE1_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
        {DP_TYPE1_ID_66, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_1},                      // temperature of outer sensor
        {DP_TYPE1_ID_6F, DP_VAL,  4,    10, remote_cmd_frost_protect_1, local_cmd_frost_protect_1}, // frost protected
        {DP_TYPE1_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_1, local_cmd_heat_protect_1},   // heat protected
        {DP_TYPE1_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_1},                            // schedule mon
        {DP_TYPE1_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_1},                            // schedule tue
        {DP_TYPE1_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_1},                            // schedule wed
        {DP_TYPE1_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_1},                            // schedule thu
        {DP_TYPE1_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_1},                            // schedule fri
        {DP_TYPE1_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_1},                            // schedule sat
        {DP_TYPE1_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_1},                            // schedule sun
        {DP_TYPE1_ID_00, DP_RAW,  0,    0,  NULL, NULL},
        {DP_TYPE1_ID_00, DP_RAW,  0,    0,  NULL, NULL},
};



/*
 *
 * For models   "edl8pz1k"
 *
 * Funstions for local commands. MCU -> ZT3L -> Zegbee
 */

void local_cmd_oper_mode_1(void *args) {

    uint8_t *mode = (uint8_t*)args;

    if (*mode) {
        *mode = 0;
    } else {
        *mode = 1;
    }
#if UART_PRINTF_MODE && DEBUG_CMD
            printf("Thermostat in %s mode\r\n", *mode?"programming":"manual");
#endif



    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE, mode);

}

void local_cmd_frost_protect_1(void *args) {

    int16_t *temp = (int16_t*)args;
    uint16_t divisor = 1;
    int16_t  old_temp;
    uint16_t len;

    if (data_point_model[DP_IDX_FROST_PROTECT].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_FROST_PROTECT].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT, &len, (uint8_t*)&old_temp);

    printf("frost prottect. temp: %d, old_temp: %d", *temp, old_temp);

    if (old_temp != *temp) {

        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT, (uint8_t*)temp);

        thermostat_settings_save();
    }




}

void local_cmd_heat_protect_1(void *args) {

    int16_t *temp = (int16_t*)args;
    uint16_t divisor = 1;
    int16_t  old_temp;
    uint16_t len;

    if (data_point_model[DP_IDX_HEAT_PROTECT].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_HEAT_PROTECT].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_HEAT_PROTECT, &len, (uint8_t*)&old_temp);

    printf("heat prottect. temp: %d, old_temp: %d", *temp, old_temp);

    if (old_temp != *temp) {

        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_HEAT_PROTECT, (uint8_t*)temp);

        thermostat_settings_save();
    }
}

void local_cmd_outdoor_sensor_1(void *args) {

    int16_t *temp = (int16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_TEMP_OUT].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_TEMP_OUT].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_OUTDOOR_TEMPERATURE, (uint8_t*)temp);

#if UART_PRINTF_MODE && DEBUG_CMD
            printf("OutDoor Temperature: %d\r\n", *temp);
#endif

}

void local_cmd_set_schedule_1(void *args) {

    schedule_args_model2_t *schedule_args = (schedule_args_model2_t*)args;
    uint8_t *ptr = schedule_args->data_point->data;
    ptr++;
    dp_schedule_model2_t *schedule = (dp_schedule_model2_t*)ptr;

    printf("Schedule mon\r\n");

    for (uint8_t i = 0; i < 4; i++) {
        schedule_args->heatMode[i].transTime = schedule->hour * 60;
        schedule_args->heatMode[i].transTime += schedule->minute;
        schedule_args->heatMode[i].heatSetpoint = reverse16(schedule->temperature)/data_point_model[schedule_args->idx].divisor * 100;
        schedule++;
        printf("idx: %d, i: %d, time: %d, temp: %d\r\n", schedule_args->idx, i, schedule_args->heatMode[i].transTime, schedule_args->heatMode[i].heatSetpoint);
    }

    thermostat_settings_save();
}

/*
 *
 * Functions for remote commands. Zegbee -> ZT3L -> MCU
 *
 */

void remote_cmd_oper_mode_1(void *args) {

    uint8_t oper_mode;
    uint8_t *arg = (uint8_t*)args;

    if (*arg) {
        oper_mode = 0;
    } else {
        oper_mode = 1;
    }

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

void remote_cmd_frost_protect_1(void *args) {

    int16_t *arg = (int16_t*)args;
    uint32_t frost_protect = *arg;

    printf("1. frost protect: %d\r\n", frost_protect);

    if (data_point_model[DP_IDX_FROST_PROTECT].id == 0) return;

    if (frost_protect < FROST_PROTECT_MIN * 100 || frost_protect > FROST_PROTECT_MAX * 100) {
        return;
    }

    printf("2. frost protect: %d\r\n", frost_protect);


    frost_protect /= 100; // 1500 -> 15°C

    if (data_point_model[DP_IDX_FROST_PROTECT].divisor == 10) {
        frost_protect *= 10;
    } else if (data_point_model[DP_IDX_FROST_PROTECT].divisor == 100) {
        frost_protect *= 100;
    }

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_FROST_PROTECT].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_FROST_PROTECT].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (frost_protect >> 24) & 0xFF;
    data_point->data[1] = (frost_protect >> 16) & 0xFF;
    data_point->data[2] = (frost_protect >> 8)  & 0xFF;
    data_point->data[3] = frost_protect & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

}

void remote_cmd_heat_protect_1(void *args) {

    int16_t *arg = (int16_t*)args;
    uint32_t heat_protect = *arg;

    printf("1. heat protect: %d\r\n", heat_protect);

    if (data_point_model[DP_IDX_HEAT_PROTECT].id == 0) return;

    if (heat_protect < HEAT_PROTECT_MIN * 100 || heat_protect > HEAT_PROTECT_MAX * 100) {
        return;
    }

    printf("2. heat protect: %d\r\n", heat_protect);


    heat_protect /= 100; // 1500 -> 15°C

    if (data_point_model[DP_IDX_HEAT_PROTECT].divisor == 10) {
        heat_protect *= 10;
    } else if (data_point_model[DP_IDX_HEAT_PROTECT].divisor == 100) {
        heat_protect *= 100;
    }

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_HEAT_PROTECT].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_HEAT_PROTECT].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (heat_protect >> 24) & 0xFF;
    data_point->data[1] = (heat_protect >> 16) & 0xFF;
    data_point->data[2] = (heat_protect >> 8)  & 0xFF;
    data_point->data[3] = heat_protect & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();

}

static void remote_cmd_set_schedule_mon() {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(21);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_MON].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_MON].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE_MON].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_mon;
    uint16_t temp;

    *pstrd++ = 1;
    out_pkt->pkt_len++;

    for (uint8_t i = 0; i < 4; i++) {
        *pstrd++ = heat_mode[i].transTime / 60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime % 60;
        out_pkt->pkt_len++;
        temp = (heat_mode[i].heatSetpoint / 100) * data_point_model[DP_IDX_SCHEDULE_MON].divisor;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

    set_seq_num(seq_num);
}

static void remote_cmd_set_schedule_tue() {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(21);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_TUE].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_TUE].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE_TUE].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_tue;
    uint16_t temp;

    *pstrd++ = 1;
    out_pkt->pkt_len++;

    for (uint8_t i = 0; i < 4; i++) {
        *pstrd++ = heat_mode[i].transTime / 60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime % 60;
        out_pkt->pkt_len++;
        temp = (heat_mode[i].heatSetpoint / 100) * data_point_model[DP_IDX_SCHEDULE_TUE].divisor;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

    set_seq_num(seq_num);
}

static void remote_cmd_set_schedule_wed() {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(21);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_WED].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_WED].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE_WED].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_wed;
    uint16_t temp;

    *pstrd++ = 1;
    out_pkt->pkt_len++;

    for (uint8_t i = 0; i < 4; i++) {
        *pstrd++ = heat_mode[i].transTime / 60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime % 60;
        out_pkt->pkt_len++;
        temp = (heat_mode[i].heatSetpoint / 100) * data_point_model[DP_IDX_SCHEDULE_WED].divisor;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

    set_seq_num(seq_num);
}

static void remote_cmd_set_schedule_thu() {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(21);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_THU].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_THU].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE_THU].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_thu;
    uint16_t temp;

    *pstrd++ = 1;
    out_pkt->pkt_len++;

    for (uint8_t i = 0; i < 4; i++) {
        *pstrd++ = heat_mode[i].transTime / 60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime % 60;
        out_pkt->pkt_len++;
        temp = (heat_mode[i].heatSetpoint / 100) * data_point_model[DP_IDX_SCHEDULE_THU].divisor;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

    set_seq_num(seq_num);
}

static void remote_cmd_set_schedule_fri() {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(21);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_FRI].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_FRI].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE_FRI].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_fri;
    uint16_t temp;

    *pstrd++ = 1;
    out_pkt->pkt_len++;

    for (uint8_t i = 0; i < 4; i++) {
        *pstrd++ = heat_mode[i].transTime / 60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime % 60;
        out_pkt->pkt_len++;
        temp = (heat_mode[i].heatSetpoint / 100) * data_point_model[DP_IDX_SCHEDULE_FRI].divisor;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

    set_seq_num(seq_num);
}

static void remote_cmd_set_schedule_sat() {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(21);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_SAT].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_SAT].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE_SAT].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_sat;
    uint16_t temp;

    *pstrd++ = 1;
    out_pkt->pkt_len++;

    for (uint8_t i = 0; i < 4; i++) {
        *pstrd++ = heat_mode[i].transTime / 60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime % 60;
        out_pkt->pkt_len++;
        temp = (heat_mode[i].heatSetpoint / 100) * data_point_model[DP_IDX_SCHEDULE_SAT].divisor;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

    set_seq_num(seq_num);
}

static void remote_cmd_set_schedule_sun() {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;

    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(21);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = data_point_model[DP_IDX_SCHEDULE_SUN].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_SCHEDULE_SUN].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(data_point_model[DP_IDX_SCHEDULE_SUN].len));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    uint8_t *pstrd = data_point->data;
    heatMode_t *heat_mode = g_zcl_scheduleData.schedule_sun;
    uint16_t temp;

    *pstrd++ = 7;
    out_pkt->pkt_len++;

    for (uint8_t i = 0; i < 4; i++) {
        *pstrd++ = heat_mode[i].transTime / 60;
        out_pkt->pkt_len++;
        *pstrd++ = heat_mode[i].transTime % 60;
        out_pkt->pkt_len++;
        temp = (heat_mode[i].heatSetpoint / 100) * data_point_model[DP_IDX_SCHEDULE_SUN].divisor;
        *pstrd++ = (temp >> 8)  & 0xFF;
        *pstrd++ = temp & 0xFF;
        out_pkt->pkt_len += 2;
    }

    *pstrd = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

    set_seq_num(seq_num);
}

void remote_cmd_set_schedule_1(void *args) {

    if (data_point_model[DP_IDX_SCHEDULE].remote_cmd == NULL) return;

    uint8_t *dayOfWeek = (uint8_t*)args;

    if (*dayOfWeek & DAY_SUN) {
        remote_cmd_set_schedule_sun();
    }

    if (*dayOfWeek & DAY_MON) {
        remote_cmd_set_schedule_mon();
    }

    if (*dayOfWeek & DAY_TUE) {
        remote_cmd_set_schedule_tue();
    }

    if (*dayOfWeek & DAY_WED) {
        remote_cmd_set_schedule_wed();
    }

    if (*dayOfWeek & DAY_THU) {
        remote_cmd_set_schedule_thu();
    }

    if (*dayOfWeek & DAY_FRI) {
        remote_cmd_set_schedule_fri();
    }

    if (*dayOfWeek & DAY_SAT) {
        remote_cmd_set_schedule_sat();
    }

    thermostat_settings_save();
}

void remote_cmd_get_schedule_1(uint8_t day) {

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

        if (day == 0) {
            //mon
            heat_mode =  g_zcl_scheduleData.schedule_mon;
            cmd.dayOfWeekForSequence = DAY_MON;
        } else if (day == 1) {
            //tue
            heat_mode =  g_zcl_scheduleData.schedule_tue;
            cmd.dayOfWeekForSequence = DAY_TUE;
        } else if (day == 2) {
            //wed
            heat_mode =  g_zcl_scheduleData.schedule_wed;
            cmd.dayOfWeekForSequence = DAY_WED;
        } else if (day == 3) {
            //thu
            heat_mode =  g_zcl_scheduleData.schedule_thu;
            cmd.dayOfWeekForSequence = DAY_THU;
        } else if (day == 4) {
            //fri
            heat_mode =  g_zcl_scheduleData.schedule_fri;
            cmd.dayOfWeekForSequence = DAY_FRI;
        } else if (day == 5) {
            //sat
            heat_mode =  g_zcl_scheduleData.schedule_sat;
            cmd.dayOfWeekForSequence = DAY_SAT;
        } else if (day == 6) {
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

    zcl_thermostat_setWeeklyScheduleCmdSend(APP_ENDPOINT1, &dstEpInfo, 0, &cmd);

}

