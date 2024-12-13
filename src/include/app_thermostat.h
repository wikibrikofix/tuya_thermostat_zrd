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

typedef struct __attribute__((packed)) {
    zcl_scheduleData_t schedule_data;
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
    uint8_t     crc;
} thermostat_settings_t;

void remote_cmd_sys_mode_0(void *args);
void remote_cmd_heating_set_0(void *args);
void remote_cmd_temp_calibration_0(void *args);
void remote_cmd_display_mode_0(void *args);
void remote_cmd_keylock_0(void *args);
void remote_cmd_sensor_used_0(void *args);
void remote_cmd_deadband_0(void *args);
void remote_cmd_min_setpoint_0(void *args);
void remote_cmd_max_setpoint_0(void *args);
void remote_cmd_oper_mode_0(void *args);
void remote_cmd_set_weekly_schedule_0(void *args);

#define remote_cmd_sys_mode_1           remote_cmd_sys_mode_0
#define remote_cmd_heating_set_1        remote_cmd_heating_set_0
#define remote_cmd_temp_calibration_1   remote_cmd_temp_calibration_0
#define remote_cmd_sensor_used_1        remote_cmd_sensor_used_0
#define remote_cmd_keylock_1            remote_cmd_keylock_0
#define remote_cmd_deadband_1           remote_cmd_deadband_0
#define remote_cmd_max_setpoint_1       remote_cmd_max_setpoint_0
void remote_cmd_min_setpoint_1(void *args);
void remote_cmd_oper_mode_1(void *args);
void remote_cmd_frost_protect_1(void *args);
void remote_cmd_heat_protect_1(void *args);
void remote_cmd_set_weekly_schedule_1(void *args);
//void remote_cmd_set_schedule_mon_1(void *args);
//void remote_cmd_set_schedule_tue_1(void *args);
//void remote_cmd_set_schedule_wed_1(void *args);
//void remote_cmd_set_schedule_thu_1(void *args);
//void remote_cmd_set_schedule_fri_1(void *args);
//void remote_cmd_set_schedule_sat_1(void *args);
//void remote_cmd_set_schedule_sun_1(void *args);


void remote_smd_sys_mode(uint8_t mode);
void remote_smd_heating_set(int32_t temp);
void remote_smd_temp_calibration(int8_t temp);
void remote_smd_display_mode(uint8_t mode);
void remote_smd_keylock(uint8_t keylock);
void remote_cmd_sensor_used(uint8_t sensor_used);
void remote_cmd_deadband(uint32_t hysteresis);
void remote_cmd_min_setpoint(uint32_t min_temp);
void remote_cmd_max_setpoint(uint32_t max_temp);
void remote_cmd_oper_mode(uint8_t oper_mode);
void remote_cmd_set_weekly_schedule();
void set_run_state_bit(uint8_t bit_num, bool set);
void thermostat_onoff_state(int8_t onoff);
void thermostat_get_weekly_schedule(uint8_t day);
nv_sts_t thermostat_settings_save();
nv_sts_t thermostat_settings_restore();
void set_zcl_modelId(uint8_t *signature);

#endif /* SRC_INCLUDE_APP_THERMOSTAT_H_ */
