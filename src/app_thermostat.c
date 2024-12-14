#include "app_main.h"



/*
 *
 *  common remote_cmd functions
 *
 */

void remote_cmd_sys_mode(void *args) {

    uint8_t *mode = (uint8_t*)args;

    if(data_point_model[DP_IDX_ONOFF].id == 0) return;

    if (*mode != SYS_MODE_OFF && *mode != SYS_MODE_HEAT) {
        return;
    }

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

    if (*mode == SYS_MODE_OFF) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    } else if (*mode == SYS_MODE_HEAT) {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    }
}

void remote_cmd_heating_set(void *args) {

    int16_t *arg = (int16_t*)args;
    int32_t temp = *arg;

    uint16_t len;
    int16_t  minHeatSet;
    int16_t  maxHeatSet;

    if(data_point_model[DP_IDX_SETPOINT].id == 0) return;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&minHeatSet);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&maxHeatSet);

//    printf("1.temp: %d, minHeatSet: %d, maxHeatSet: %d\r\n", temp, minHeatSet, maxHeatSet);

    if (temp < minHeatSet || temp > maxHeatSet) {
        return;
    }

//    printf("2. temp: %d, minHeatSet: %d, maxHeatSet: %d\r\n", temp, minHeatSet, maxHeatSet);


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

void remote_cmd_temp_calibration(void *args) {

    int8_t *arg = (int8_t*)args;
    int8_t temp = *arg;

    if(data_point_model[DP_IDX_CALIBRATION].id == 0) return;

    if (temp < CLIENT_TEMP_CALIBRATION_MIN || temp > CLIENT_TEMP_CALIBRATION_MAX) {
        return;
    }

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

void remote_cmd_keylock(void *args) {

    uint8_t *keylock = (uint8_t*)args;

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
    data_point->data[0] = *keylock;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_sensor_used(void *args) {

    uint8_t *sensor_used = (uint8_t*)args;

    if (data_point_model[DP_IDX_SENSOR].id == 0) return;

    if (*sensor_used != SENSOR_IN && *sensor_used != SENSOR_AL && *sensor_used != SENSOR_OU) {
        return;
    }

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
    data_point->data[0] = *sensor_used;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_deadband(void *args) {

    uint8_t *arg = (uint8_t*)args;
    uint32_t hysteresis = *arg;

    if (data_point_model[DP_IDX_DEADZONE].id == 0) return;

    if (hysteresis < HYSTERESIS_MIN || hysteresis > HYSTERESIS_MAX) {
        return;
    }

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

void remote_cmd_min_setpoint(void *args) {

    uint16_t *arg = (uint16_t*)args;
    uint32_t min_temp = *arg;

    printf("min_temp: %d\r\n", min_temp);

    if (data_point_model[DP_IDX_MIN].id == 0) return;

    if (min_temp < SET_POINT_MIN_MIN * 100 || min_temp > SET_POINT_MIN_MAX * 100) {
        return;
    }

    min_temp /= 100; // 1500 -> 15°C

    if (data_point_model[DP_IDX_MAX].divisor == 10) {
        min_temp *= 10;
    } else if (data_point_model[DP_IDX_MAX].divisor == 100) {
        min_temp *= 100;
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
    data_point->dp_id = data_point_model[DP_IDX_MIN].id;
    out_pkt->pkt_len++;
    data_point->dp_type = data_point_model[DP_IDX_MIN].type;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = (min_temp >> 24) & 0xFF;
    data_point->data[1] = (min_temp >> 16) & 0xFF;
    data_point->data[2] = (min_temp >> 8)  & 0xFF;
    data_point->data[3] = min_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

    thermostat_settings_save();
}

void remote_cmd_max_setpoint(void *args) {

    uint16_t *arg = (uint16_t*)args;
    uint32_t max_temp = *arg;

    if (data_point_model[DP_IDX_MAX].id == 0) return;

    if (max_temp < SET_POINT_MAX_MIN * 100 || max_temp > SET_POINT_MAX_MAX * 100) {
        return;
    }

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

/*
 *
 *  common local_cmd functions
 *
 */

void local_cmd_inner_sensor(void *args) {

    int16_t *temp = (int16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_TEMP].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_TEMP].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMPERATURE, (uint8_t*)temp);

#if UART_PRINTF_MODE && DEBUG_CMD
            printf("Local Temperature: %d\r\n", temp);
#endif


}
void local_cmd_heating_set(void *args) {

    uint16_t *temp = (uint16_t*)args;
    uint16_t divisor = 1;

    if (data_point_model[DP_IDX_SETPOINT].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_SETPOINT].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, (uint8_t*)temp);

    thermostat_settings_save();


}

void local_cmd_min_setpoint(void *args) {

    int16_t *temp = (int16_t*)args;

    uint16_t divisor = 1;
    int16_t  old_min;
    uint16_t len;

    if (data_point_model[DP_IDX_MIN].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_MIN].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&old_min);

//                            printf("temp: %d, old_min: %d", temp, old_min);

    if (old_min != *temp) {

        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, (uint8_t*)temp);

        thermostat_settings_save();
    }


}

void local_cmd_max_setpoint(void *args) {

    int16_t *temp = (int16_t*)args;

    uint16_t divisor = 1;
    int16_t  absMinHeatSet;
    int16_t  absMaxHeatSet;
    int16_t  old_max;
    uint16_t len;
    bool set_attr = false;


    if (data_point_model[DP_IDX_MAX].divisor == 1) {
        divisor = 100;
    } else if (data_point_model[DP_IDX_MAX].divisor == 10) {
        divisor = 10;
    }

    *temp *= divisor;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&absMinHeatSet);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&absMaxHeatSet);

//    printf("temp: %d, absMinHeatSet: %d, absMaxHeatSet: %d\r\n", temp, absMinHeatSet, absMaxHeatSet);

    if (*temp > absMaxHeatSet) {
        *temp = absMaxHeatSet;
        set_attr = true;
    }
    if (*temp < absMinHeatSet) {
        *temp = absMinHeatSet;
        set_attr = true;
    }

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&old_max);

    if (old_max != *temp) {
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, (uint8_t*)temp);

        thermostat_settings_save();
    }

    if (set_attr) {
        data_point_model[DP_IDX_MAX].remote_cmd(temp);
    }

}

void local_cmd_deadband(void *args) {

    int16_t *temp = (int16_t*)args;

    if (data_point_model[DP_IDX_DEADZONE].divisor == 10) {
        *temp /= 10;
    } else if (data_point_model[DP_IDX_DEADZONE].divisor == 100) {
        *temp /= 100;
    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND, (uint8_t*)temp);

    thermostat_settings_save();
}

void local_cmd_temp_calibration(void *args) {

    int8_t *temp = (int8_t*)args;

    if (data_point_model[DP_IDX_CALIBRATION].divisor == 1) {
        *temp *= 10;
    } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 100) {
        *temp /= 10;
    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, (uint8_t*)temp);

    thermostat_settings_save();


}

void local_cmd_keylock(void *args) {

    uint8_t *lock = (uint8_t*)args;

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT, (uint8_t*)lock);

    thermostat_settings_save();


}

void local_cmd_sensor_used(void *args) {

    uint8_t *sensor_used = (uint8_t*)args;

//    if (sensor_used == SENSOR_IN) {
////                                printf("sensor IN\r\n");
//    } else if (sensor_used == SENSOR_AL) {
////                                printf("sensor AL\r\n");
//    } else {
////                                printf("sensor OU\r\n");
//    }

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, (uint8_t*)sensor_used);
}

void local_cmd_set_run_state(void *args) {

    run_state_bit_t *run_state_bit = (run_state_bit_t*)args;

    uint16_t runState;
    uint16_t len;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE, &len, (uint8_t*)&runState);

    if (run_state_bit->set) {
        runState |= (1 << run_state_bit->bit_num);
    } else {
        runState &= ~( 1 << run_state_bit->bit_num);
    }

    zcl_setAttrVal(APP_ENDPOINT1,
                   ZCL_CLUSTER_HAVC_THERMOSTAT,
                   ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE,
                   (uint8_t*)&runState);

}

void local_cmd_onoff_state(void *args) {

    uint8_t *onoff = (uint8_t*)args;
    run_state_bit_t run_state_bit;
    uint8_t sys_mode;

    if (*onoff == DEV_POWER_OFF) {
#if UART_PRINTF_MODE && DEBUG_CMD
        printf("Power OFF\r\n");
#endif
        sys_mode = SYS_MODE_OFF;
        zcl_setAttrVal(APP_ENDPOINT1,
                       ZCL_CLUSTER_HAVC_THERMOSTAT,
                       ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,
                       (uint8_t*)&sys_mode);
        run_state_bit.bit_num = RUN_STATE_HEAT_BIT;
        run_state_bit.set = OFF;
        local_cmd_set_run_state(&run_state_bit);
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


/*****************************************************************************************************/

void set_zcl_modelId(uint8_t *signature) {
    uint8_t modelId[ZCL_BASIC_MAX_LENGTH] = {0};
    uint8_t name[ZCL_BASIC_MAX_LENGTH-1] = {0};

    strncpy((char*)name, STR_MODEL_ID_BEGIN, STR_MODEL_ID_BEGIN_LEN);
    strncpy((char*)name+STR_MODEL_ID_BEGIN_LEN, (char*)signature, 8);

    set_zcl_str(name, modelId, ZCL_BASIC_MAX_LENGTH);

    zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_BASIC, ZCL_ATTRID_BASIC_MODEL_ID, modelId);
}

/*****************************************************************************************************/

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
    int16_t     frostProtect;
    int16_t     heatProtect;
    uint8_t     keypadLockout;
    uint8_t     crc;
    bool        save = false;

    st = nv_flashReadNew(1, NV_MODULE_APP, NV_ITEM_APP_USER_CFG, sizeof(thermostat_settings_t), (uint8_t*)&thermostat_settings);

    crc = thermostat_settings.crc;

    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&minHeatSetpointLimit);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, &len, (uint8_t*)&maxHeatSetpointLimit);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, &len, (uint8_t*)&localTemperatureCalibration);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, &len, (uint8_t*)&occupiedHeatingSetpoint);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE, &len, (uint8_t*)&manual_progMode);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, &len, (uint8_t*)&sensor_used);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND, &len, (uint8_t*)&dead_band);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT, &len, (uint8_t*)&frostProtect);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_HEAT_PROTECT, &len, (uint8_t*)&heatProtect);
    zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT, &len, (uint8_t*)&keypadLockout);


    if(st == NV_SUCC && crc == checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1)) {
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

        if (thermostat_settings.frostProtect != frostProtect) {
            thermostat_settings.frostProtect = frostProtect;
            save = true;
        }

        if (thermostat_settings.heatProtect != heatProtect) {
            thermostat_settings.heatProtect = heatProtect;
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
        thermostat_settings.crc = checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1);
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
        thermostat_settings.frostProtect = frostProtect;
        thermostat_settings.heatProtect = heatProtect;
        thermostat_settings.keypadLockout = keypadLockout;
        thermostat_settings.crc = checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1);

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

    if (st == NV_SUCC && thermostat_settings.crc == checksum((uint8_t*)&thermostat_settings, sizeof(thermostat_settings_t)-1)) {
        memcpy(&g_zcl_scheduleData, &thermostat_settings.schedule_data, sizeof(zcl_scheduleData_t));
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT, (uint8_t*)&thermostat_settings.minHeatSetpointLimit);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, (uint8_t*)&thermostat_settings.maxHeatSetpointLimit);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, (uint8_t*)&thermostat_settings.localTemperatureCalibration);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, (uint8_t*)&thermostat_settings.occupiedHeatingSetpoint);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, (uint8_t*)&thermostat_settings.sensor_used);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND, (uint8_t*)&thermostat_settings.dead_band);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_FROST_PROTECT, (uint8_t*)&thermostat_settings.frostProtect);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT, ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_HEAT_PROTECT, (uint8_t*)&thermostat_settings.heatProtect);
        zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT, (uint8_t*)&thermostat_settings.keypadLockout);
    }

#else
    st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

    return st;
}

