#include "app_main.h"

uint8_t thermostat_mode = DEV_THERM_MODE_TEMP;

void remote_smd_sys_mode(uint8_t mode) {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = DP_ID_01;
    out_pkt->pkt_len++;
    data_point->dp_type = DP_BOOL;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    if (mode == SYS_MODE_OFF) {
        data_point->data[0] = 0x00;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    } else if (mode == SYS_MODE_HEAT) {
        data_point->data[0] = 0x01;
        out_pkt->pkt_len ++;
        data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
        add_cmd_queue(out_pkt, true);
        set_seq_num(seq_num);
    }
}

void remote_smd_heating_set(int16_t temp) {

    temp /= 100;

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = DP_ID_10;
    out_pkt->pkt_len++;
    data_point->dp_type = DP_VAL;
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
}

void remote_smd_temp_calibration(int8_t temp) {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(8);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = DP_ID_1B;
    out_pkt->pkt_len++;
    data_point->dp_type = DP_VAL;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(4));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    temp /= 10; // 90 -> 9, -90 -> -9
    int32_t dev_temp = temp;
    data_point->data[0] = (dev_temp >> 24) & 0xFF;
    data_point->data[1] = (dev_temp >> 16) & 0xFF;
    data_point->data[2] = (dev_temp >> 8)  & 0xFF;
    data_point->data[3] = dev_temp & 0xFF;
    out_pkt->pkt_len += 4;
    data_point->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);
}

void remote_smd_display_mode(uint8_t mode) {

//    pkt_output_t *pkt = (pkt_output_t*)cmdTx[CMD_DISPLAY];
//    pkt->cnt++;
//
//    if (mode == ZCL_DISPLAY_MODE_CELSIUS) {
//        pkt->cmd_value = DEV_DISPLAY_MODE_CELSIUS;
//        add_cmd_queue(CMD_DISPLAY, true, cmdTx[CMD_DISPLAY]);
//    } else if (mode == ZCL_DISPLAY_MODE_FAHRENHEIT) {
//        pkt->cmd_value = DEV_DISPLAY_MODE_FAHRENHEIT;
//        add_cmd_queue(CMD_DISPLAY, true, cmdTx[CMD_DISPLAY]);
//    }
}

void remote_smd_keylock(uint8_t keylock) {

    uint8_t pkt_buff[DATA_MAX_LEN+12];
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t seq_num = get_seq_num();
    seq_num++;

    set_header_pkt(pkt_buff, sizeof(pkt_buff), seq_num, COMMAND04);

    out_pkt->len = reverse16(5);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;

    data_point_t *data_point = (data_point_t*)out_pkt->data;
    data_point->dp_id = DP_ID_28;
    out_pkt->pkt_len++;
    data_point->dp_type = DP_BOOL;
    out_pkt->pkt_len++;
    data_point->dp_len = (reverse16(1));
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    data_point->data[0] = keylock;
    out_pkt->pkt_len ++;
    data_point->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, true);

    set_seq_num(seq_num);

}

void set_run_state_bit(uint8_t bit_num, bool set) {

    zcl_thermostatAttr_t *tempAttrs = zcl_thermostatAttrGet();

    if (set) {
        tempAttrs->runningState |= (1 << bit_num);
    } else {
        tempAttrs->runningState &= ~( 1 << bit_num);
    }
}

void thermostat_onoff_state(int32_t onoff) {
    zcl_thermostatAttr_t *tempAttrs = zcl_thermostatAttrGet();

    if (onoff == DEV_POWER_OFF) {
#if UART_PRINTF_MODE && DEBUG_CMD
        printf("Power OFF\r\n");
#endif
        tempAttrs->systemMode = SYS_MODE_OFF;
        set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
    } else {
#if UART_PRINTF_MODE && DEBUG_CMD
        printf("Power ON\r\n");
#endif
        tempAttrs->systemMode = SYS_MODE_HEAT;
//        if (thermostat_mode == DEV_THERM_MODE_TEMP) {
//
//        }
        if (tempAttrs->occupiedHeatingSetpoint > tempAttrs->localTemperature && thermostat_mode == DEV_THERM_MODE_TEMP) {
            set_run_state_bit(RUN_STATE_HEAT_BIT, ON);
        } else {
            set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
        }
    }

}

void thermostat_heatset_state(int32_t tempF) {

    zcl_thermostatAttr_t *tempAttrs = zcl_thermostatAttrGet();

    int16_t tempC = zcl_convert_temperature_fromFtoC(tempF/10);

#if UART_PRINTF_MODE && DEBUG_CMD
    printf("Heat set temperature: %d F, %d C, localTemperature: %d C\r\n", tempF, tempC, tempAttrs->localTemperature);
#endif
    tempAttrs->occupiedHeatingSetpoint = tempC;
    if (tempAttrs->systemMode == SYS_MODE_HEAT && thermostat_mode == DEV_THERM_MODE_TEMP) {
        if (tempAttrs->occupiedHeatingSetpoint > tempAttrs->localTemperature) {
            set_run_state_bit(RUN_STATE_HEAT_BIT, ON);
        } else {
            set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
        }
    } else if (tempAttrs->systemMode == SYS_MODE_OFF) {
        set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
    }

}
