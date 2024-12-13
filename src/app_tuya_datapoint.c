#include "tl_common.h"

#include "app_main.h"

static const char8_t *tuya_manuf_name0[] = {
                                           "u9bfwha0",
                                           "aoclfnxz",
//                                           "ztvwu4nk",
//                                           "5toc8efa",
//                                           "ye5jkfsb",
                                            NULL};

static const char8_t *tuya_manuf_name1[] = {
                                           "edl8pz1k",
                                            NULL};


/* data point for manufacturer id -
 * "u9bfwha0"
 * "aoclfnxz"
 *
 *  id, type, len, divisor, remote_functionCb
*/

data_point_st_t data_point_model0[DP_IDX_MAXNUM] = {
        {DP_TYPE0_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_0},             // on off
        {DP_TYPE0_ID_18, DP_VAL,  4,    10, NULL},                              // local temperature
        {DP_TYPE0_ID_10, DP_VAL,  4,    1,  remote_cmd_heating_set_0},          // heat setpoint
        {DP_TYPE0_ID_00, DP_VAL,  0,    0,  remote_cmd_min_setpoint_0},         // heat min - not support
        {DP_TYPE0_ID_13, DP_VAL,  4,    1, remote_cmd_max_setpoint_0},         // max heat setpoint
        {DP_TYPE0_ID_1A, DP_VAL,  4,    1,  remote_cmd_deadband_0},             // hysteresis
        {DP_TYPE0_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_0},     // local temperature calibration
        {DP_TYPE0_ID_24, DP_ENUM, 1,    1,  NULL},                              // 0x00 - heat, 0x01 - idle
        {DP_TYPE0_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_0},          // sensor IN/AL/OU
        {DP_TYPE0_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_0},            // manual (setpoint) / programming (schedule)
        {DP_TYPE0_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_0},              // lock / unlock keys (child lock)
        {DP_TYPE0_ID_65, DP_RAW,  0x24, 1,  remote_cmd_set_weekly_schedule_0},  // schedule
        {DP_TYPE0_ID_03, DP_BOOL, 1,    1,  NULL},                              // unknown
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE0_ID_00, DP_RAW,  0,    0,  NULL},
};

/* data point for manufacturer id -
 * "edl8pz1k"
 *
 */
data_point_st_t data_point_model1[DP_IDX_MAXNUM] = {
        {DP_TYPE1_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_1},
        {DP_TYPE1_ID_18, DP_VAL,  4,    10, NULL},                              // local temperature
        {DP_TYPE1_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_1},          // heat setpoint
        {DP_TYPE1_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_1},         // min heat setpoint
        {DP_TYPE1_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_1},         // max heat setpoint
        {DP_TYPE1_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_1},             // hysteresis
        {DP_TYPE1_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_1},     // local temperature calibration
        {DP_TYPE1_ID_24, DP_ENUM, 1,    1,  NULL},                              // 0x00 - heat, 0x01 - idle
        {DP_TYPE1_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_1},          // sensor IN/AL/OU
        {DP_TYPE1_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_1},            // manual (setpoint) / programming (schedule)
        {DP_TYPE1_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_1},              // lock / unlock keys (child lock)
        {DP_TYPE1_ID_00, DP_RAW,  0,    1,  remote_cmd_set_weekly_schedule_1},  // schedule
        {DP_TYPE1_ID_00, DP_BOOL, 1,    1,  NULL},                              // unknown
        {DP_TYPE1_ID_66, DP_VAL,  4,    10, NULL},                              // temperature of outer sensor
        {DP_TYPE1_ID_6F, DP_VAL,  4,    10, remote_cmd_frost_protect_1},        // frost protected
        {DP_TYPE1_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_1},         // heat protected
        {DP_TYPE1_ID_6E, DP_RAW,  0x11, 10, NULL/*remote_cmd_set_schedule_mon_1*/},     // schedule mon
        {DP_TYPE1_ID_6D, DP_RAW,  0x11, 10, NULL/*remote_cmd_set_schedule_tue_1*/},     // schedule tue
        {DP_TYPE1_ID_6C, DP_RAW,  0x11, 10, NULL/*remote_cmd_set_schedule_wed_1*/},     // schedule wed
        {DP_TYPE1_ID_6B, DP_RAW,  0x11, 10, NULL/*remote_cmd_set_schedule_thu_1*/},     // schedule thu
        {DP_TYPE1_ID_6A, DP_RAW,  0x11, 10, NULL/*remote_cmd_set_schedule_fri_1*/},     // schedule fri
        {DP_TYPE1_ID_69, DP_RAW,  0x11, 10, NULL/*remote_cmd_set_schedule_sat_1*/},     // schedule sat
        {DP_TYPE1_ID_65, DP_RAW,  0x11, 10, NULL/*remote_cmd_set_schedule_sun_1*/},     // schedule sun
        {DP_TYPE1_ID_00, DP_RAW,  0,    0,  NULL},
        {DP_TYPE1_ID_00, DP_RAW,  0,    0,  NULL},
};


const char8_t **tuya_manuf_names[] = {tuya_manuf_name0, tuya_manuf_name1};
uint8_t manuf_name = MANUF_NAME_0;

data_point_st_t *data_point_model_arr[] = {data_point_model0, data_point_model1};

// Not worked in gcc 4.5.1
//data_point_st_t *data_point_model = data_point_model_arr[MANUF_NAME_0];
data_point_st_t *data_point_model = data_point_model0;

void data_point_model_init() {

    data_point_model = data_point_model_arr[MANUF_NAME_0];

//    for(uint16_t i = 0; i < DP_IDX_MAXNUM; i++) {
//        printf("i: %d, id: 0x%x, type: %d, len: %d, divisor: %d\r\n",
//                i, data_point_model[i].id, data_point_model[i].type, data_point_model[i].len, data_point_model[i].divisor);
//    }
}
