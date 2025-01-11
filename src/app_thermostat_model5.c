#include "app_main.h"

/* data point for manufacturer id -
 * "5toc8efa"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */
data_point_st_t data_point_model5[DP_IDX_MAXNUM] = {
        {DP_TYPE5_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_5, local_cmd_onoff_state_5},                // onoff
        {DP_TYPE5_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_5},                                // local temperature
        {DP_TYPE5_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_5, local_cmd_heating_set_5},             // heat setpoint
        {DP_TYPE5_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_5, local_cmd_min_setpoint_5},           // min heat setpoint
        {DP_TYPE5_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_5, local_cmd_max_setpoint_5},           // max heat setpoint
        {DP_TYPE5_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_5, local_cmd_deadband_5},                   // hysteresis
        {DP_TYPE5_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_5, local_cmd_temp_calibration_5},   // local temperature calibration
        {DP_TYPE5_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_5},                       // 0x00 - heat, 0x01 - idle
        {DP_TYPE5_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_5, local_cmd_sensor_used_5},     // sensor IN/AL/OU
        {DP_TYPE5_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_5, local_cmd_oper_mode_5},         // manual (setpoint) / programming (schedule)
        {DP_TYPE5_ID_28, DP_BOOL, 1,    1,  remote_cmd_keylock_5, local_cmd_keylock_5},             // lock / unlock keys (child lock)
        {DP_TYPE5_ID_00, DP_RAW,  0,    1,  remote_cmd_set_schedule_5, NULL},                       // schedule
        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
        {DP_TYPE5_ID_66, DP_VAL,  4,    10, NULL, local_cmd_outdoor_sensor_5},                      // temperature of outer sensor
        {DP_TYPE5_ID_00, DP_RAW,  4,    0,  NULL, NULL},                                            // frost protected
        {DP_TYPE5_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_5, local_cmd_heat_protect_5},   // heat protected
        {DP_TYPE5_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule mon
        {DP_TYPE5_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule tue
        {DP_TYPE5_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule wed
        {DP_TYPE5_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule thu
        {DP_TYPE5_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule fri
        {DP_TYPE5_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule sat
        {DP_TYPE5_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_5},                        // schedule sun
        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},
        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},
        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},
        {DP_TYPE5_ID_00, DP_RAW,  0,    0,  NULL, NULL},
};
