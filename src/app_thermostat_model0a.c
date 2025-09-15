#include "app_main.h"

/* data point for manufacturer id -
 * "_TZE284_xalsoe3m"
 *
 * id, type, len, divisor, remote_commands_functionCb, local_commands_functionCb
*/

data_point_st_t data_point_model9[DP_IDX_MAXNUM] = {
/*00*/  {DP_TYPE0A_ID_01, DP_BOOL, 1,    1,  remote_cmd_sys_mode_0A, local_cmd_onoff_state_0A},             // onoff
/*01*/  {DP_TYPE0A_ID_18, DP_VAL,  4,    10, NULL, local_cmd_inner_sensor_0A},                              // local temperature
/*02*/  {DP_TYPE0A_ID_10, DP_VAL,  4,    10, remote_cmd_heating_set_0A, local_cmd_heating_set_0A},          // heat setpoint
/*03*/  {DP_TYPE0A_ID_1A, DP_VAL,  4,    10, remote_cmd_min_setpoint_0A, local_cmd_min_setpoint_0A},        // min heat setpoint
/*04*/  {DP_TYPE0A_ID_13, DP_VAL,  4,    10, remote_cmd_max_setpoint_0A, local_cmd_max_setpoint_0A},        // max heat setpoint
/*05*/  {DP_TYPE0A_ID_67, DP_VAL,  4,    1,  remote_cmd_deadband_0A, local_cmd_deadband_0A},                // hysteresis
/*06*/  {DP_TYPE0A_ID_1B, DP_VAL,  4,    1,  remote_cmd_temp_calibration_0A, local_cmd_temp_calibration_0A},// local temperature calibration
/*07*/  {DP_TYPE0A_ID_24, DP_ENUM, 1,    1,  NULL, local_cmd_set_run_state_0A},                     // 0x00 - heat, 0x01 - idle
/*08*/  {DP_TYPE0A_ID_2B, DP_ENUM, 1,    1,  remote_cmd_sensor_used_0A, local_cmd_sensor_used_0A},  // sensor IN/OU/AL
/*09*/  {DP_TYPE0A_ID_02, DP_ENUM, 1,    1,  remote_cmd_oper_mode_0A, local_cmd_oper_mode_0A},      // manual (setpoint) / programming (schedule)
/*10*/  {DP_TYPE0A_ID_27, DP_BOOL, 1,    1,  remote_cmd_keylock_0A, local_cmd_keylock_0A},          // lock / unlock keys (child lock)
/*11*/  {DP_TYPE0A_ID_44, DP_RAW,  0x30, 1,  remote_cmd_set_schedule_1, local_cmd_set_schedule_1},  // schedule
/*12*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // unknown
/*13*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // temperature of outer sensor
/*14*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // frost protected
/*15*/  {DP_TYPE0A_ID_68, DP_VAL,  4,    10, remote_cmd_heat_protect_0A, local_cmd_heat_protect_0A},// heat protected
/*16*/  {DP_TYPE0A_ID_6E, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_0A},                      // schedule mon
/*17*/  {DP_TYPE0A_ID_6D, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_0A},                      // schedule tue
/*18*/  {DP_TYPE0A_ID_6C, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_0A},                      // schedule wed
/*19*/  {DP_TYPE0A_ID_6B, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_0A},                      // schedule thu
/*20*/  {DP_TYPE0A_ID_6A, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_0A},                      // schedule fri
/*21*/  {DP_TYPE0A_ID_69, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_0A},                      // schedule sat
/*22*/  {DP_TYPE0A_ID_65, DP_RAW,  0x11, 10, NULL, local_cmd_set_schedule_0A},                      // schedule sun
/*23*/  {DP_TYPE0A_ID_71, DP_VAL,  4,    1,  NULL, NULL},                                           // level brightness 06:00-22:00
/*24*/  {DP_TYPE0A_ID_72, DP_VAL,  4,    1,  NULL, NULL},                                           // level brightness 22:00-06:00
/*25*/  {DP_TYPE0A_ID_28, DP_BOOL, 1,    1,  remote_cmd_eco_mode_0A, local_cmd_eco_mode_0A},        // eco mode
/*26*/  {DP_TYPE0A_ID_00, DP_VAL,  0,    0,  NULL, NULL},                                           // eco mode's heat temperature
/*27*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // eco mode's cool temperature
/*28*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // sound
/*29*/  {DP_TYPE0A_ID_00, DP_BOOL, 0,    0,  NULL, NULL},                                           // default setting
/*30*/  {DP_TYPE0A_ID_00, DP_ENUM, 0,    0,  NULL, NULL},                                           // type relay NC or NO (inversion)
/*31*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // thermostat mode ext.
/*32*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // fan mode
/*33*/  {DP_TYPE0A_ID_00, DP_RAW,  0,    0,  NULL, NULL},                                           // fan control
/*34*/  {DP_TYPE0A_ID_00, DP_VAL,  0,    0,  NULL, NULL},                                           // external sensor calibration
/*35*/  {DP_TYPE0A_ID_00, DP_ENUM, 0,    0,  NULL, NULL},                                           // mode key lock
};
