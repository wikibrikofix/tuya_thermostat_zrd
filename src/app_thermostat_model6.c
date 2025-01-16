#include "app_main.h"

/* data point for manufacturer id -
 * "lzriup1j"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
 */
data_point_st_t data_point_model6[DP_IDX_MAXNUM] = {
        {DP_TYPE6_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_6, local_cmd_onoff_state_6},                // onoff
        {DP_TYPE6_ID_03, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_6},                                // local temperature
        {DP_TYPE6_ID_02, DP_VAL,  4,    10, remote_cmd_heating_set_6, local_cmd_heating_set_6},             // heat setpoint
        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},           // min heat setpoint
        {DP_TYPE6_ID_0F, DP_VAL,  4,    10, remote_cmd_max_setpoint_5, local_cmd_max_setpoint_5},           // max heat setpoint
        {DP_TYPE6_ID_6B, DP_VAL,  4,    1,  remote_cmd_deadband_6, local_cmd_deadband_6},                   // hysteresis
        {DP_TYPE6_ID_13, DP_VAL,  4,    1,  remote_cmd_temp_calibration_6, local_cmd_temp_calibration_6},   // local temperature calibration
        {DP_TYPE6_ID_65, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_6},                       // 0x00 - heat, 0x01 - idle
        {DP_TYPE6_ID_6A, DP_ENUM, 1,    1,  remote_cmd_sensor_used_6, local_cmd_sensor_used_6},     // sensor IN/AL/OU
        {DP_TYPE6_ID_04, DP_ENUM, 1,    1,  remote_cmd_oper_mode_6, local_cmd_oper_mode_6},         // manual (setpoint) / programming (schedule)
        {DP_TYPE6_ID_09, DP_BOOL, 1,    1,  remote_cmd_keylock_6, local_cmd_keylock_6},             // lock / unlock keys (child lock)
        {DP_TYPE6_ID_6D, DP_RAW,  0x20, 1,  remote_cmd_set_schedule_6, local_cmd_set_schedule_6},           // schedule
        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                            // unknown
        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},                      // temperature of outer sensor
        {DP_TYPE6_ID_66, DP_BOOL, 1,    1,  remote_cmd_frost_protect_6, local_cmd_frost_protect_6},         // frost protected
        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},   // heat protected
        {DP_TYPE6_ID_68, DP_ENUM, 1,    1,  remote_cmd_set_schedule_mode_6, local_cmd_set_schedule_mode_6}, // schedule mode
        {DP_TYPE6_ID_00, DP_RAW,  0x11, 10, NULL, NULL},                        // schedule tue
        {DP_TYPE6_ID_00, DP_RAW,  0x11, 10, NULL, NULL},                        // schedule wed
        {DP_TYPE6_ID_00, DP_RAW,  0x11, 10, NULL, NULL},                        // schedule thu
        {DP_TYPE6_ID_00, DP_RAW,  0x11, 10, NULL, NULL},                        // schedule fri
        {DP_TYPE6_ID_00, DP_RAW,  0x11, 10, NULL, NULL},                        // schedule sat
        {DP_TYPE6_ID_00, DP_RAW,  0x11, 10, NULL, NULL},                        // schedule sun
        {DP_TYPE6_ID_6E, DP_ENUM, 1,    1,  remote_cmd_level_6, local_cmd_level_6},                 // level brightness of screen
        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
        {DP_TYPE6_ID_00, DP_RAW,  0,    0,  NULL, NULL},
        {DP_TYPE6_ID_69, DP_BOOL, 1,    1,  remote_cmd_sound_6, local_cmd_sound_6},                 // sound on-off
        {DP_TYPE6_ID_67, DP_BOOL, 1,    1,  remote_cmd_setting_reset_6, local_cmd_setting_reset_6}, // settings reset
        {DP_TYPE6_ID_6F, DP_BOOL, 1,    1,  remote_cmd_inversion_6, local_cmd_inversion_6},         // inversion of output
};
