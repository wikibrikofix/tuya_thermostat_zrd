#ifndef SRC_INCLUDE_APP_THERMOSTAT_H_
#define SRC_INCLUDE_APP_THERMOSTAT_H_

#define HYSTERESIS_MIN              1
#define HYSTERESIS_MAX              5
#define SET_POINT_MIN_MIN           5
#define SET_POINT_MIN_MAX           15
#define SET_POINT_MAX_MIN           15
#define SET_POINT_MAX_MAX           45
#define FROST_PROTECT_MIN           0
#define FROST_PROTECT_MAX           10
#define HEAT_PROTECT_MIN            25
#define HEAT_PROTECT_MAX            70

/* command on or off */
#define DEV_POWER_OFF               0x00
#define DEV_POWER_ON                0x01

/* Power-on behavior */
#define DEV_PWR_ON_BEHAVIOR_PREV    0x01
#define DEV_PWR_ON_BEHAVIOR_OFF     0x02
#define DEV_PWR_ON_BEHAVIOR_ON      0x03

/* Thermostat mode - setpoint or schedule */
#define DEV_THERM_MODE_MANUAL       0x01
#define DEV_THERM_MODE_PROGRAMMING  0x02

/* Mode Celsius or Fahrenheit */
#define DEV_DISPLAY_MODE_CELSIUS    0x01
#define DEV_DISPLAY_MODE_FAHRENHEIT 0x02

#define CLIENT_TEMP_CALIBRATION_MIN -90
#define CLIENT_TEMP_CALIBRATION_MAX  90

#define DEV_THERM_MODE_COLD         0x00
#define DEV_THERM_MODE_HEAT         0x01
#define DEV_THERM_MODE_FAN          0x02

#define ZB_MODELID_ARR_NUM          16
#define ZB_MODELID_SIZE             19
#define ZB_MODELID_FULL_SIZE        ZB_MODELID_SIZE+2

typedef struct __attribute__((packed)) {
    zcl_scheduleData_t schedule_data;
    int16_t     localTemperature;               // 22°C * 100
    uint8_t     systemMode;                     // see /src/zcl/zcl_app_thermostat.h
    int16_t     minHeatSetpointLimit;           // min 5°C * 100
    int16_t     maxHeatSetpointLimit;           // max 45°C * 100
    int8_t      localTemperatureCalibration;    // in device -9°C...+9°C
    int16_t     occupiedHeatingSetpoint;        // 0°C ... 50°C * 100
    uint8_t     manual_progMode;
    uint8_t     sensor_used;                    // IN, ALL, OU - castom attribute
    int16_t     frostProtect;
    int16_t     heatProtect;
    uint8_t     dead_band;                      // 1 ... 5 °C
    uint8_t     temperatureDisplayMode;         // 0x00 - °C, 0x01 - °F. Always °C (Not support)
    uint8_t     keypadLockout;                  // on off
    uint8_t     currentLevelA;
    uint8_t     currentLevelB;
    uint8_t     ecoMode;                        // 1 - ecoMode on, 0 - ecoMode off
    int16_t     ecoModeHeatTemperature;         // 20°C * 100
    int16_t     ecoModeCoolTemperature;         // 20°C * 100
    uint8_t     sound;                          // 0 - off, 1 - on
    uint8_t     schedule_mode;                  // enum off, 5+2, 6+1, 7
    uint8_t     level;                          // enum off, low, medium, high
    uint8_t     inversion;                      // 0 - off, 1 - on
    uint8_t     frost_protect_onoff;            // 0 - off, 1 - on
    uint8_t     dev_therm_mode;                 // 0 - cool, 1 - heat, 2 - fan
    uint8_t     crc;
} thermostat_settings_t;

typedef struct {
    uint8_t bit_num;
    uint8_t set;
} run_state_bit_t;

typedef struct {
    data_point_t    *data_point;
    uint16_t        idx;
    heatMode_t      *heatMode;
    uint8_t         w_day;
} schedule_args_model2_t;

extern uint8_t w_mon;
extern uint8_t w_tue;
extern uint8_t w_wed;
extern uint8_t w_thu;
extern uint8_t w_fri;
extern uint8_t w_sat;
extern uint8_t w_sun;
extern uint8_t w_day;

extern data_point_st_t data_point_model1[DP_IDX_MAXNUM];
extern data_point_st_t data_point_model2[DP_IDX_MAXNUM];
extern data_point_st_t data_point_model3[DP_IDX_MAXNUM];
extern data_point_st_t data_point_model4[DP_IDX_MAXNUM];
extern data_point_st_t data_point_model5[DP_IDX_MAXNUM];
extern data_point_st_t data_point_model6[DP_IDX_MAXNUM];
extern data_point_st_t data_point_model7[DP_IDX_MAXNUM];
extern uint8_t remote_cmd_pkt_buff[DATA_MAX_LEN+12];
extern uint8_t zb_modelId_arr[ZB_MODELID_ARR_NUM][ZB_MODELID_FULL_SIZE];

extern uint8_t dev_therm_mode;

extern void (*answer_weekly_schedule[MANUF_NAME_MAX])(void);

/*
 * common functions remote_cmd
 */
void remote_cmd_sys_mode(void *args);
void remote_cmd_heating_set(void *args);
void remote_cmd_temp_calibration(void *args);
void remote_cmd_keylock(void *args);
void remote_cmd_sensor_used(void *args);
void remote_cmd_deadband(void *args);
void remote_cmd_min_setpoint(void *args);
void remote_cmd_max_setpoint(void *args);

/*
 *  remote_cmd for signarure
 *  "u9bfwha0"
 *  "aoclfnxz"
 *
 *  model1 - name_1
 */

#define remote_cmd_sys_mode_1           remote_cmd_sys_mode
#define remote_cmd_heating_set_1        remote_cmd_heating_set
#define remote_cmd_temp_calibration_1   remote_cmd_temp_calibration
#define remote_cmd_sensor_used_1        remote_cmd_sensor_used
#define remote_cmd_keylock_1            remote_cmd_keylock
#define remote_cmd_deadband_1           remote_cmd_deadband
#define remote_cmd_max_setpoint_1       remote_cmd_max_setpoint

void remote_cmd_oper_mode_1(void *args);
void remote_cmd_set_schedule_1(void *args);
void remote_cmd_get_schedule_1();


/*
 *  remote_cmd for signarure
 *  "edl8pz1k"
 *
 *  model2 - name_2
 */
#define remote_cmd_sys_mode_2           remote_cmd_sys_mode
#define remote_cmd_heating_set_2        remote_cmd_heating_set
#define remote_cmd_temp_calibration_2   remote_cmd_temp_calibration
#define remote_cmd_sensor_used_2        remote_cmd_sensor_used
#define remote_cmd_keylock_2            remote_cmd_keylock
#define remote_cmd_deadband_2           remote_cmd_deadband
#define remote_cmd_min_setpoint_2       remote_cmd_min_setpoint
#define remote_cmd_max_setpoint_2       remote_cmd_max_setpoint

void remote_cmd_oper_mode_2(void *args);
void remote_cmd_frost_protect_2(void *args);
void remote_cmd_heat_protect_2(void *args);
void remote_cmd_set_schedule_2(void *args);
void remote_cmd_get_schedule_2();

/*
 *  remote_cmd for signarure
 *  "tagezcph"
 *
 *  model3 - name_3
 */
#define remote_cmd_sys_mode_3           remote_cmd_sys_mode
#define remote_cmd_heating_set_3        remote_cmd_heating_set
#define remote_cmd_temp_calibration_3   remote_cmd_temp_calibration
#define remote_cmd_sensor_used_3        remote_cmd_sensor_used
#define remote_cmd_keylock_3            remote_cmd_keylock
#define remote_cmd_deadband_3           remote_cmd_deadband
#define remote_cmd_min_setpoint_3       remote_cmd_min_setpoint
#define remote_cmd_max_setpoint_3       remote_cmd_max_setpoint
#define remote_cmd_oper_mode_3          remote_cmd_oper_mode_2
#define remote_cmd_frost_protect_3      remote_cmd_frost_protect_2
#define remote_cmd_heat_protect_3       remote_cmd_heat_protect_2
#define remote_cmd_set_schedule_3       remote_cmd_set_schedule_2
#define remote_cmd_get_schedule_3       remote_cmd_get_schedule_2

void remote_cmd_eco_mode_3(void *args);
void remote_cmd_eco_mode_temp_3(void *args);
void remote_cmd_level_day_3(void *args);
void remote_cmd_level_night_3(void *args);

/*
 *  remote_cmd for signarure
 *  "xyugziqv"
 *
 *  model4 - name_4
 */
#define remote_cmd_sys_mode_4           remote_cmd_sys_mode
#define remote_cmd_heating_set_4        remote_cmd_heating_set
#define remote_cmd_temp_calibration_4   remote_cmd_temp_calibration
#define remote_cmd_sensor_used_4        remote_cmd_sensor_used
#define remote_cmd_keylock_4            remote_cmd_keylock
#define remote_cmd_deadband_4           remote_cmd_deadband
#define remote_cmd_min_setpoint_4       remote_cmd_min_setpoint
#define remote_cmd_max_setpoint_4       remote_cmd_max_setpoint
#define remote_cmd_oper_mode_4          remote_cmd_oper_mode_2
#define remote_cmd_frost_protect_4      remote_cmd_frost_protect_2
#define remote_cmd_heat_protect_4       remote_cmd_heat_protect_2
#define remote_cmd_set_schedule_4       remote_cmd_set_schedule_2
#define remote_cmd_get_schedule_4       remote_cmd_get_schedule_2
#define remote_cmd_eco_mode_4           remote_cmd_eco_mode_3
#define remote_cmd_eco_mode_temp_4      remote_cmd_eco_mode_temp_3

void remote_cmd_level_4(void *args);

/*
 *  remote_cmd for signarure
 *  "5toc8efa"
 *
 *  model5 - name_5
 */
#define remote_cmd_sys_mode_5           remote_cmd_sys_mode_2
#define remote_cmd_heating_set_5        remote_cmd_heating_set_2
#define remote_cmd_temp_calibration_5   remote_cmd_temp_calibration_2
#define remote_cmd_sensor_used_5        remote_cmd_sensor_used_2
#define remote_cmd_keylock_5            remote_cmd_keylock_2
#define remote_cmd_deadband_5           remote_cmd_deadband_2
#define remote_cmd_min_setpoint_5       remote_cmd_min_setpoint_2
#define remote_cmd_max_setpoint_5       remote_cmd_max_setpoint_2
#define remote_cmd_oper_mode_5          remote_cmd_oper_mode_2
#define remote_cmd_frost_protect_5      remote_cmd_frost_protect_2
#define remote_cmd_heat_protect_5       remote_cmd_heat_protect_2
#define remote_cmd_set_schedule_5       remote_cmd_set_schedule_2
#define remote_cmd_get_schedule_5       remote_cmd_get_schedule_2

/*
 *  remote_cmd for signarure
 *  "lzriup1j"
 *
 *  model6 - name_6
 */
#define remote_cmd_sys_mode_6           remote_cmd_sys_mode
#define remote_cmd_heating_set_6        remote_cmd_heating_set
#define remote_cmd_keylock_6            remote_cmd_keylock
#define remote_cmd_oper_mode_6          remote_cmd_oper_mode_1

void remote_cmd_sensor_used_6(void *args);
void remote_cmd_temp_calibration_6(void *args);
void remote_cmd_deadband_6(void *args);
void remote_cmd_max_setpoint_6(void *args);
void remote_cmd_frost_protect_6(void *args);
void remote_cmd_heat_protect_6(void *args);
void remote_cmd_set_schedule_6(void *args);
void remote_cmd_get_schedule_6();
void remote_cmd_schedule_mode_6(void *args);
void remote_cmd_inversion_6(void *args);
void remote_cmd_level_6(void *args);
void remote_cmd_sound_6(void *args);
void remote_cmd_setting_reset_6(void *args);

/*
 *  remote_cmd for signarure
 *  "mpbki2zm"
 *
 *  model7 - name_7
 */
//#define remote_cmd_sys_mode_7           remote_cmd_sys_mode
#define remote_cmd_heating_set_7        remote_cmd_heating_set
#define remote_cmd_temp_calibration_7   remote_cmd_temp_calibration
#define remote_cmd_keylock_7            remote_cmd_keylock
#define remote_cmd_deadband_7           remote_cmd_deadband
#define remote_cmd_min_setpoint_7       remote_cmd_min_setpoint
#define remote_cmd_max_setpoint_7       remote_cmd_max_setpoint
#define remote_cmd_oper_mode_7          remote_cmd_oper_mode_2
#define remote_cmd_set_schedule_7       remote_cmd_set_schedule_2
#define remote_cmd_get_schedule_7       remote_cmd_get_schedule_2
#define remote_cmd_eco_mode_7           remote_cmd_eco_mode_3
#define remote_cmd_eco_mode_heat_temp_7 remote_cmd_eco_mode_temp_3

void remote_cmd_sys_mode_7(void *args);
void remote_cmd_eco_mode_cool_temp_7(void *args);

/*
 * common functions local_cmd
 */
void local_cmd_inner_sensor(void *args);
void local_cmd_heating_set(void *args);
void local_cmd_temp_calibration(void *args);
void local_cmd_min_setpoint(void *args);
void local_cmd_max_setpoint(void *args);
void local_cmd_deadband(void *args);
void local_cmd_keylock(void *args);
void local_cmd_sensor_used(void *args);
void local_cmd_set_run_state(void *args);
void local_cmd_onoff_state(void *args);

/*
 *  local_cmd for signarure
 *  "u9bfwha0"
 *  "aoclfnxz"
 *
 *  model1 - name_1
 */
#define local_cmd_inner_sensor_1        local_cmd_inner_sensor
#define local_cmd_heating_set_1         local_cmd_heating_set
#define local_cmd_temp_calibration_1    local_cmd_temp_calibration
#define local_cmd_min_setpoint_1        local_cmd_min_setpoint
#define local_cmd_max_setpoint_1        local_cmd_max_setpoint
#define local_cmd_deadband_1            local_cmd_deadband
#define local_cmd_keylock_1             local_cmd_keylock
#define local_cmd_sensor_used_1         local_cmd_sensor_used
#define local_cmd_set_run_state_1       local_cmd_set_run_state
#define local_cmd_onoff_state_1         local_cmd_onoff_state

void local_cmd_oper_mode_1(void *args);
void local_cmd_set_schedule_1(void *args);

/*
 *  local_cmd for signarure
 *  "edl8pz1k"
 *
 *  model2 - name_2
 */
#define local_cmd_inner_sensor_2        local_cmd_inner_sensor
#define local_cmd_heating_set_2         local_cmd_heating_set
#define local_cmd_temp_calibration_2    local_cmd_temp_calibration
#define local_cmd_min_setpoint_2        local_cmd_min_setpoint
#define local_cmd_max_setpoint_2        local_cmd_max_setpoint
#define local_cmd_deadband_2            local_cmd_deadband
#define local_cmd_keylock_2             local_cmd_keylock
#define local_cmd_sensor_used_2         local_cmd_sensor_used
#define local_cmd_set_run_state_2       local_cmd_set_run_state
#define local_cmd_onoff_state_2         local_cmd_onoff_state

void local_cmd_oper_mode_2(void *args);
void local_cmd_frost_protect_2(void *args);
void local_cmd_heat_protect_2(void *args);
void local_cmd_outdoor_sensor_2(void *args);
void local_cmd_set_schedule_2(void *args);


/*
 *  local_cmd for signarure
 *  "tagezcph"
 *
 *  model3 - name_3
 */
#define local_cmd_inner_sensor_3        local_cmd_inner_sensor
#define local_cmd_heating_set_3         local_cmd_heating_set
#define local_cmd_temp_calibration_3    local_cmd_temp_calibration
#define local_cmd_min_setpoint_3        local_cmd_min_setpoint
#define local_cmd_max_setpoint_3        local_cmd_max_setpoint
#define local_cmd_deadband_3            local_cmd_deadband
#define local_cmd_keylock_3             local_cmd_keylock
#define local_cmd_sensor_used_3         local_cmd_sensor_used
#define local_cmd_set_run_state_3       local_cmd_set_run_state
#define local_cmd_onoff_state_3         local_cmd_onoff_state
#define local_cmd_oper_mode_3           local_cmd_oper_mode_2
#define local_cmd_frost_protect_3       local_cmd_frost_protect_2
#define local_cmd_heat_protect_3        local_cmd_heat_protect_2
#define local_cmd_outdoor_sensor_3      local_cmd_outdoor_sensor_2
#define local_cmd_set_schedule_3        local_cmd_set_schedule_2

void local_cmd_eco_mode_3(void *args);
void local_cmd_eco_mode_temp_3(void *args);
void local_cmd_level_day_3(void *args);
void local_cmd_level_night_3(void *args);


/*
 *  local_cmd for signarure
 *  "xyugziqv"
 *
 *  model4 - name_4
 */
#define local_cmd_inner_sensor_4        local_cmd_inner_sensor
#define local_cmd_heating_set_4         local_cmd_heating_set
#define local_cmd_temp_calibration_4    local_cmd_temp_calibration
#define local_cmd_min_setpoint_4        local_cmd_min_setpoint
#define local_cmd_max_setpoint_4        local_cmd_max_setpoint
#define local_cmd_deadband_4            local_cmd_deadband
#define local_cmd_keylock_4             local_cmd_keylock
#define local_cmd_sensor_used_4         local_cmd_sensor_used
#define local_cmd_set_run_state_4       local_cmd_set_run_state
#define local_cmd_onoff_state_4         local_cmd_onoff_state
#define local_cmd_oper_mode_4           local_cmd_oper_mode_2
#define local_cmd_frost_protect_4       local_cmd_frost_protect_2
#define local_cmd_heat_protect_4        local_cmd_heat_protect_2
#define local_cmd_outdoor_sensor_4      local_cmd_outdoor_sensor_2
#define local_cmd_set_schedule_4        local_cmd_set_schedule_2
#define local_cmd_eco_mode_4            local_cmd_eco_mode_3
#define local_cmd_eco_mode_temp_4       local_cmd_eco_mode_temp_3
#define local_cmd_level_4               local_cmd_level_day_3


/*
 *  local_cmd for signarure
 *  "5toc8efa"
 *
 *  model5 - name_5
 */
#define local_cmd_inner_sensor_5        local_cmd_inner_sensor_2
#define local_cmd_heating_set_5         local_cmd_heating_set_2
#define local_cmd_temp_calibration_5    local_cmd_temp_calibration_2
#define local_cmd_min_setpoint_5        local_cmd_min_setpoint_2
#define local_cmd_max_setpoint_5        local_cmd_max_setpoint_2
#define local_cmd_deadband_5            local_cmd_deadband_2
#define local_cmd_keylock_5             local_cmd_keylock_2
#define local_cmd_sensor_used_5         local_cmd_sensor_used_2
#define local_cmd_set_run_state_5       local_cmd_set_run_state_2
#define local_cmd_onoff_state_5         local_cmd_onoff_state_2
#define local_cmd_oper_mode_5           local_cmd_oper_mode_2
#define local_cmd_frost_protect_5       local_cmd_frost_protect_2
#define local_cmd_heat_protect_5        local_cmd_heat_protect_2
#define local_cmd_outdoor_sensor_5      local_cmd_outdoor_sensor_2
#define local_cmd_set_schedule_5        local_cmd_set_schedule_2

/*
 *  local_cmd for signarure
 *  "lzriup1j"
 *
 *  model6 - name_6
 */
#define local_cmd_inner_sensor_6        local_cmd_inner_sensor
#define local_cmd_heating_set_6         local_cmd_heating_set
#define local_cmd_max_setpoint_6        local_cmd_max_setpoint
#define local_cmd_deadband_6            local_cmd_deadband
#define local_cmd_keylock_6             local_cmd_keylock
#define local_cmd_set_run_state_6       local_cmd_set_run_state
#define local_cmd_onoff_state_6         local_cmd_onoff_state
#define local_cmd_oper_mode_6           local_cmd_oper_mode_1
#define local_cmd_heat_protect_6        local_cmd_heat_protect_2

void local_cmd_sensor_used_6(void *args);
void local_cmd_temp_calibration_6(void *args);
void local_cmd_frost_protect_6(void *args);
void local_cmd_inversion_6(void *args);
void local_cmd_level_6(void *args);
void local_cmd_sound_6(void *args);
void local_cmd_setting_reset_6(void *args);
void local_cmd_schedule_mode_6(void *args);
void local_cmd_set_schedule_6(void *args);

/*
 *  local_cmd for signarure
 *  "mpbki2zm"
 *
 *  model7 - name_7
 */
#define local_cmd_inner_sensor_7        local_cmd_inner_sensor
#define local_cmd_heating_set_7         local_cmd_heating_set
#define local_cmd_temp_calibration_7    local_cmd_temp_calibration
#define local_cmd_min_setpoint_7        local_cmd_min_setpoint
#define local_cmd_max_setpoint_7        local_cmd_max_setpoint
#define local_cmd_deadband_7            local_cmd_deadband
#define local_cmd_keylock_7             local_cmd_keylock
#define local_cmd_oper_mode_7           local_cmd_oper_mode_2
#define local_cmd_set_schedule_7        local_cmd_set_schedule_2
#define local_cmd_eco_mode_7            local_cmd_eco_mode_3
#define local_cmd_eco_mode_heat_temp_7  local_cmd_eco_mode_temp_3

void local_cmd_sys_mode_7(void *args);
void local_cmd_eco_mode_cool_temp_7(void *args);
void local_cmd_set_run_state_7(void *args);
void local_cmd_therm_mode_7(void* args);
void local_cmd_eco_mode_cool_temp_7(void *args);

#endif /* SRC_INCLUDE_APP_THERMOSTAT_H_ */
