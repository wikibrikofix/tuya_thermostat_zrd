#include "tl_common.h"

#include "app_main.h"

static uint8_t      pkt_buff[DATA_MAX_LEN*2];
static uint8_t      answer_count = 0;
static uint16_t     seq_num = 0;
static status_net_t status_net = STATUS_NET_UNKNOWN;
static uint8_t      no_answer = false;

cmd_queue_t cmd_queue = {0};

uint8_t checksum(uint8_t *data, uint16_t length) {

    uint8_t crc8 = 0;

    for(uint8_t i = 0; i < length; i++) {
        crc8 += data[i];
    }

    return crc8;
}

void add_cmd_queue(pkt_tuya_t *pkt, uint8_t confirm_need) {

    memset(&cmd_queue.cmd_queue[cmd_queue.cmd_num], 0, sizeof(cmd_queue_cell_t));

    cmd_queue.cmd_queue[cmd_queue.cmd_num].confirm_need = confirm_need;
    memcpy(&(cmd_queue.cmd_queue[cmd_queue.cmd_num].pkt), pkt, sizeof(pkt_tuya_t));
    cmd_queue.cmd_num++;

}

static void move_cmd_queue() {

    uint8_t i = 0;

    if (cmd_queue.cmd_num) {
        if (cmd_queue.cmd_queue[0].confirm_rec) {
            if (cmd_queue.cmd_num == 1) {
                cmd_queue.cmd_num = 0;
            } else {
                for (i = 0; i < cmd_queue.cmd_num; i++) {
                    memcpy(&cmd_queue.cmd_queue[i], &cmd_queue.cmd_queue[i+1], sizeof(cmd_queue_cell_t));
                }
                cmd_queue.cmd_num--;
            }
        }
    }
}

static void send_command(pkt_tuya_t *pkt) {

    while(1) {
        if (app_uart_txMsg((uint8_t*)pkt, pkt->pkt_len) == UART_TX_SUCCESS) break;
        sleep_ms(30);
    }
}

uint16_t get_seq_num() {

    return seq_num;
}

void set_seq_num(uint16_t f_seq_num) {

    seq_num = f_seq_num;
}

void set_header_pkt(uint8_t *f_pkt_buff, uint8_t len, uint16_t f_seq_num, uint8_t command) {

    memset(f_pkt_buff, 0, len);
    pkt_tuya_t *out_pkt = (pkt_tuya_t*)f_pkt_buff;
    out_pkt->pkt_len = 0;
    out_pkt->f_start1 = FLAG_START1;
    out_pkt->pkt_len++;
    out_pkt->f_start2 = FLAG_START2;
    out_pkt->pkt_len++;
    out_pkt->pkt_vesion = SP_VERSION;
    out_pkt->pkt_len++;
    out_pkt->seq_num = reverse16(f_seq_num);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    out_pkt->command = command;
    out_pkt->pkt_len++;
}

static void set_command(command_t command, uint16_t f_seq_num, bool inc_seq_num) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    uint16_t len;
    uint32_t utc_time, local_time;

    if (inc_seq_num) {
        f_seq_num++;
        if (f_seq_num > 0xFFF0) f_seq_num = 0;
        seq_num = f_seq_num;
    }

    set_header_pkt(pkt_buff, sizeof(pkt_buff), f_seq_num, command);

    switch(command) {
        case COMMAND00:
            break;
        case COMMAND01:
            out_pkt->len = 0;
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_cmd_queue(out_pkt, true);
            break;
        case COMMAND02:
            out_pkt->len = reverse16(1);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = status_net;
            out_pkt->pkt_len++;
            out_pkt->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_cmd_queue(out_pkt, true);
            break;
        case COMMAND03:
            out_pkt->len = 0;
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_cmd_queue(out_pkt, false);
            break;
        case COMMAND04:
            break;
        case COMMAND05:
            break;
        case COMMAND06:
            break;
        case COMMAND24:
            out_pkt->len = reverse16(8);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;

            zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_TIME, &len, (uint8_t*)&utc_time);
            zcl_getAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_GEN_TIME, ZCL_ATTRID_LOCAL_TIME, &len, (uint8_t*)&local_time);

            utc_time   += UNIX_TIME_CONST;
            local_time += UNIX_TIME_CONST;

            out_pkt->data[0] = (utc_time >> 24) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[1] = (utc_time >> 16) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[2] = (utc_time >> 8) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[3] = utc_time & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[4] = (local_time >> 24) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[5] = (local_time >> 16) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[6] = (local_time >> 8) & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[7] = local_time & 0xFF;
            out_pkt->pkt_len++;
            out_pkt->data[8] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_cmd_queue(out_pkt, false);

            break;
        case COMMAND28:
            out_pkt->len = 0;
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_cmd_queue(out_pkt, true);
            break;
        case COMMANDXX:
//            printf("COMMMANDXX\r\n");
            out_pkt->command = 0x06;
            out_pkt->len = reverse16(4);
            out_pkt->pkt_len++;
            out_pkt->pkt_len++;
            out_pkt->data[0] = 0x65;
            out_pkt->pkt_len++;
            out_pkt->data[1] = 0x00;
            out_pkt->pkt_len++;
            out_pkt->data[2] = 0x00;
            out_pkt->pkt_len++;
            out_pkt->data[3] = 0x00;
            out_pkt->pkt_len++;
            out_pkt->data[4] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
            add_cmd_queue(out_pkt, true);
            break;
        default:
            break;
    }
}

static void set_default_answer(command_t command, uint16_t f_seq_num) {

    pkt_tuya_t *out_pkt = (pkt_tuya_t*)pkt_buff;
    set_header_pkt(pkt_buff, sizeof(pkt_buff), f_seq_num, command);
    out_pkt->len = reverse16(1);
    out_pkt->pkt_len++;
    out_pkt->pkt_len++;
    out_pkt->data[0] = 0x01;
    out_pkt->pkt_len++;
    out_pkt->data[1] = checksum((uint8_t*)out_pkt, out_pkt->pkt_len++);
    add_cmd_queue(out_pkt, false);

}

static int32_t check_answerCb(void *arg) {

    if (no_answer) {
#if UART_PRINTF_MODE
        printf("no answer, reboot\r\n");
#endif
        TL_ZB_TIMER_SCHEDULE(delayedMcuResetCb, NULL, TIMEOUT_1SEC);
    }
    return 0;
}

void uart_cmd_handler() {

    size_t load_size = 0;
    uint8_t ch, complete = false;
    uint8_t answer_buff[DATA_MAX_LEN+24];
    pkt_tuya_t *pkt  = (pkt_tuya_t*)answer_buff;
    data_point_t *data_point = (data_point_t*)pkt->data;

    if (first_start == 1) {
        set_command(COMMAND01, seq_num, true);
        first_start = 0;
        data_point_model_init();
        TL_ZB_TIMER_SCHEDULE(check_answerCb, NULL, TIMEOUT_15SEC);

        //only for test!!!
//        set_command(COMMANDXX, seq_num, true);
    }

    if (cmd_queue.cmd_num) {

        send_command(&cmd_queue.cmd_queue[0].pkt);

        if (cmd_queue.cmd_queue[0].confirm_need) {
            /* trying to read for 1 seconds */
            for(uint8_t i = 0; i < 100; i++ ) {
                if (available_ring_buff() && get_queue_len_ring_buff() >= 8) {
                    while (available_ring_buff() && load_size < (DATA_MAX_LEN + 8)) {
                        ch = read_byte_from_ring_buff();

                        if (load_size == 0) {
                            if (ch != FLAG_START1) {
                                continue;
                            }
                        } else if (load_size == 1) {
                            if (ch != FLAG_START2) {
                                load_size = 0;
                                continue;
                            }
                        }

                        answer_buff[load_size++] = ch;

                        if (load_size == 2) {

                            load_size += read_bytes_from_buff(answer_buff+load_size, 6);

                            if (load_size == 8) {
                                pkt->len = reverse16(pkt->len);
                                load_size += read_bytes_from_buff(answer_buff+load_size, pkt->len);
                            } else {
                                load_size = 0;
                                continue;
                            }

                        }

                        if (load_size == pkt->len + 9) {
                            i = 100;
                            complete = true;
                            break;
                        }
                    }
                }
                sleep_ms(10);
            }

            if (complete) {
                no_answer = false;
                pkt->pkt_len = load_size;
                pkt_tuya_t *send_pkt = &cmd_queue.cmd_queue[0].pkt;
                uint8_t crc = checksum((uint8_t*)pkt, pkt->pkt_len-1);

//                printf("complete.inCRC: 0x%x, outCRC: 0x%x\r\n", crc, answer_buff[pkt->pkt_len-1]);

                if (crc == answer_buff[pkt->pkt_len-1]) {
                    if (send_pkt->command == COMMAND04 && pkt->command == COMMAND06 && pkt->seq_num == send_pkt->seq_num) {
                        cmd_queue.cmd_queue[0].confirm_rec = true;
                        if (data_point->dp_id == data_point_model[DP_IDX_SETPOINT].id ||
                            data_point->dp_id == data_point_model[DP_IDX_ONOFF].id) {
                            set_default_answer(COMMAND06, reverse16(pkt->seq_num));
                        }
                    } else if (pkt->command == send_pkt->command && pkt->seq_num == send_pkt->seq_num) {
                        switch(pkt->command) {
                            case COMMAND00:
                                break;
                            case COMMAND01:

                                cmd_queue.cmd_queue[0].confirm_rec = true;

                                uint8_t *p = pkt->data;
                                uint16_t len = pkt->len;

                                while(*p != ':' && len != 0) {
                                    p++;
                                    len--;
                                }
                                p++;
                                p++;

                                uint8_t *ptr = p;
                                while(*p != '"' && len != 0) {
                                    p++;
                                    len--;
                                }

                                *p = 0;

                                for (uint8_t ii = 0; ii < MANUF_NAME_MAX; ii++) {
                                    for (uint8_t i = 0; i < 255; i++) {
                                        if (tuya_manuf_names[ii][i] == NULL) break;
                                        if (strcmp(tuya_manuf_names[ii][i], (char8_t*)ptr) == 0) {
                                            manuf_name = ii;
                                            ii = MANUF_NAME_MAX;
                                            break;
                                        }
                                    }
                                }

//                                printf("manuf_name: %d, %s is find\r\n", manuf_name, ptr);

                                if (manuf_name == MANUF_NAME_MAX) {
                                    manuf_name = MANUF_NAME_0;
                                }

                                data_point_model = data_point_model_arr[manuf_name];

                                break;
                            case COMMAND02:
                                cmd_queue.cmd_queue[0].confirm_rec = true;
                                break;
                            case COMMAND03:
                                break;
                            case COMMAND04:
                                break;
                            case COMMAND05:
                                break;
                            case COMMAND06:
                                break;
                            case COMMAND28:
                                cmd_queue.cmd_queue[0].confirm_rec = true;
                                break;
                            default:
                                break;
                        }
                    }

                } else {
#if UART_PRINTF_MODE
                    printf("Error CRC. inCRC: 0x%x, outCRC: 0x%x\r\n", crc, answer_buff[pkt->pkt_len-1]);
#endif
                }

            } else {
#if UART_PRINTF_MODE
                printf("no complete\r\n");
#endif
                cmd_queue.cmd_queue[0].confirm_rec = false;
                if (answer_count++ == 5) {
                    answer_count = 0;
                    cmd_queue.cmd_queue[0].confirm_rec = true;
                }

                no_answer = true;
            }
        } else {
            cmd_queue.cmd_queue[0].confirm_rec = true;
        }

    }

    move_cmd_queue();

    if (available_ring_buff() && get_queue_len_ring_buff() >= 8) {
        while (available_ring_buff() && load_size < (DATA_MAX_LEN + 8)) {
            ch = read_byte_from_ring_buff();

            if (load_size == 0) {
                if (ch != FLAG_START1) {
                    continue;
                }
            } else if (load_size == 1) {
                if (ch != FLAG_START2) {
                    load_size = 0;
                    continue;
                }
            }

            answer_buff[load_size++] = ch;

            if (load_size == 2) {

                load_size += read_bytes_from_buff(answer_buff+load_size, 6);

                if (load_size == 8) {
                    pkt->len = reverse16(pkt->len);
                    load_size += read_bytes_from_buff(answer_buff+load_size, pkt->len);
                } else {
                    load_size = 0;
                    continue;
                }

            }

            if (load_size == pkt->len + 9) {
                break;
            }
        }

        if (load_size == pkt->len + 9) {

            pkt->pkt_len = load_size;
            uint8_t crc = checksum((uint8_t*)pkt, pkt->pkt_len-1);
            if (crc == answer_buff[pkt->pkt_len-1]) {
                pkt->seq_num = reverse16(pkt->seq_num);

                if (pkt->command == COMMAND03) {
                    /* Reset Factory */
#if UART_PRINTF_MODE && DEBUG_CMD
                    printf("command 0x03. Factory Reset\r\n");
#endif
                    set_command(pkt->command, pkt->seq_num, false);
                    zb_factoryReset();
                    TL_ZB_TIMER_SCHEDULE(delayedMcuResetCb, NULL, TIMEOUT_3SEC);
                } else if (pkt->command == COMMAND24) {
#if UART_PRINTF_MODE && DEBUG_CMD
                    printf("command 0x24. Sync Time\r\n");
#endif
                    if (get_time_sent()) {
                        set_command(pkt->command, pkt->seq_num, false);
                    } else {
                        set_default_answer(COMMAND06, pkt->seq_num);
                    }

                } else if (pkt->command == COMMAND06) {
#if UART_PRINTF_MODE && DEBUG_CMD
                    printf("command 0x06. Report DP data\r\n");
#endif
                    if (pkt->len >= 5) {
                        /* data point used */
                        data_point->dp_len = reverse16(data_point->dp_len);

                        if (data_point->dp_id == data_point_model[DP_IDX_ONOFF].id &&
                                data_point->dp_type == data_point_model[DP_IDX_ONOFF].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x01\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);
                            thermostat_onoff_state(data_point->data[0]);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_PROG].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_PROG].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x02\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            uint8_t mode = data_point->data[0];
#if UART_PRINTF_MODE && DEBUG_CMD
                                    printf("Thermostat mode %s\r\n", mode?"programming":"manual");
#endif

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                                           ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE, (uint8_t*) &mode);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_UNKNOWN].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_UNKNOWN].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x03\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SETPOINT].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SETPOINT].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x10\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            uint16_t divisor = 1;

                            if (data_point_model[DP_IDX_SETPOINT].divisor == 1) {
                                divisor = 100;
                            } else if (data_point_model[DP_IDX_SETPOINT].divisor == 10) {
                                divisor = 10;
                            }

                            uint16_t temp = (int32_from_str(data_point->data) & 0xFFFF) * divisor;

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                                           ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT, (uint8_t*) &temp);


                        } else if (data_point->dp_id == data_point_model[DP_IDX_MAX].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_MAX].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x13\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            uint16_t divisor = 1;

                            if (data_point_model[DP_IDX_MAX].divisor == 1) {
                                divisor = 100;
                            } else if (data_point_model[DP_IDX_MAX].divisor == 10) {
                                divisor = 10;
                            }

                            uint32_t temp = (int32_from_str(data_point->data) & 0xFFFF) * divisor;

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                                           ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT, (uint8_t*) &temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_TEMP].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_TEMP].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x18\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            uint16_t divisor = 1;

                            if (data_point_model[DP_IDX_TEMP].divisor == 1) {
                                divisor = 100;
                            } else if (data_point_model[DP_IDX_TEMP].divisor
                                    == 10) {
                                divisor = 10;
                            }

                            uint16_t temp = (int32_from_str(data_point->data) & 0xFFFF) * divisor;

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                                           ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMPERATURE, (uint8_t*) &temp);

#if UART_PRINTF_MODE && DEBUG_CMD
                                    printf("Local Temperature %d\r\n", temp);
#endif

                        } else if (data_point->dp_id == data_point_model[DP_IDX_DEADZONE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_DEADZONE].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x1A\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            uint16_t temp = (int32_from_str(data_point->data) & 0xFFFF);

                            if (data_point_model[DP_IDX_DEADZONE].divisor == 10) {
                                temp /= 10;
                            } else if (data_point_model[DP_IDX_DEADZONE].divisor == 100) {
                                temp /= 100;
                            }

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                                           ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND, (uint8_t*) &temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_CALIBRATION].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_CALIBRATION].type) {

                            int32_t temp = int32_from_str(data_point->data);
                            if (data_point_model[DP_IDX_CALIBRATION].divisor == 1) {
                                temp *= 10;
                            } else if (data_point_model[DP_IDX_CALIBRATION].divisor == 100) {
                                temp /= 10;
                            }
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x1B. calibration local temperature: %d\r\n", temp);
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                                           ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION, (uint8_t*) &temp);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_RUNSTATE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_RUNSTATE].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                        printf("data point 0x24\r\n");
    #endif
                            set_default_answer(pkt->command, pkt->seq_num);
                            if (data_point->data[0]) {
                                set_run_state_bit(RUN_STATE_HEAT_BIT, OFF);
                            } else {
                                set_run_state_bit(RUN_STATE_HEAT_BIT, ON);
                            }

                        } else if (data_point->dp_id == data_point_model[DP_IDX_LOCKUNLOCK].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_LOCKUNLOCK].type) {
                            uint8_t lock = data_point->data[0];
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x28. key %s\r\n", lock?"lock":"unlock");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG,
                                           ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT, (uint8_t*) &lock);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SENSOR].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SENSOR].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x2B\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

                            uint8_t sensor_used = data_point->data[0];

                            if (sensor_used == SENSOR_IN) {
//                                printf("sensor IN\r\n");
                            } else if (sensor_used == SENSOR_AL) {
//                                printf("sensor AL\r\n");
                            } else {
//                                printf("sensor OU\r\n");
                            }

                            zcl_setAttrVal(APP_ENDPOINT1, ZCL_CLUSTER_HAVC_THERMOSTAT,
                                           ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED, (uint8_t*)&sensor_used);

                        } else if (data_point->dp_id == data_point_model[DP_IDX_SCHEDULE].id &&
                                   data_point->dp_type == data_point_model[DP_IDX_SCHEDULE].type) {
#if UART_PRINTF_MODE && DEBUG_DP
                                    printf("data point 0x65\r\n");
#endif
                            set_default_answer(pkt->command, pkt->seq_num);

//                            printf("schedule\r\n");

                            if (manuf_name == MANUF_NAME_0) {
                                uint16_t len = data_point->dp_len / 3;
                                uint8_t *ptr = data_point->data;

                                for(uint8_t i = 0; i < len ;) {
                                    for(uint8_t ii = 0; ii < 4; ii++) {
                                        if (i < 4) {
                                            g_zcl_scheduleData.schedule_mon[ii].transTime = *ptr++ * 60;
                                            g_zcl_scheduleData.schedule_mon[ii].transTime += *ptr++;
                                            g_zcl_scheduleData.schedule_mon[ii].heatSetpoint = *ptr++/2*100;
//                                            printf("mon. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_mon[ii].transTime,
//                                                    g_zcl_scheduleData.schedule_mon[ii].heatSetpoint);
                                            i++;
                                        } else if (i < 8) {
                                            g_zcl_scheduleData.schedule_sat[ii].transTime = *ptr++ * 60;
                                            g_zcl_scheduleData.schedule_sat[ii].transTime += *ptr++;
                                            g_zcl_scheduleData.schedule_sat[ii].heatSetpoint = *ptr++/2*100;
//                                            printf("sat. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_sat[ii].transTime,
//                                                    g_zcl_scheduleData.schedule_sat[ii].heatSetpoint);
                                            i++;
                                        } else {
                                            g_zcl_scheduleData.schedule_sun[ii].transTime = *ptr++ * 60;
                                            g_zcl_scheduleData.schedule_sun[ii].transTime += *ptr++;
                                            g_zcl_scheduleData.schedule_sun[ii].heatSetpoint = *ptr++/2*100;
//                                            printf("sun. i: %d, time: %d, temp: %d\r\n", i, g_zcl_scheduleData.schedule_sun[ii].transTime,
//                                                    g_zcl_scheduleData.schedule_sun[ii].heatSetpoint);
                                            i++;
                                        }
                                    }
                                }
                            } else if (manuf_name == MANUF_NAME_1) {
                                // to the future
                            }

                            thermostat_schedule_save();
                        }
                    }
                }
            }
        }
    }
}

void set_status_net(status_net_t new_status) {

    if (new_status != status_net) {
        status_net = new_status;
        set_command(COMMAND02, seq_num, true);
    }

}

