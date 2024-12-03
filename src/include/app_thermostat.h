#ifndef SRC_INCLUDE_APP_THERMOSTAT_H_
#define SRC_INCLUDE_APP_THERMOSTAT_H_

/* Command type */
#define CMDTYPE_ONOFF               0x2F
#define CMDTYPE_HEATSET             0x2E
#define CMDTYPE_LOCAL_TEMP          0x08
#define CMDTYPE_THERMOSTAT_MODE     0x11
#define CMDTYPE_DISPLAY_MODE        0x13
#define CMDTYPE_DISPLAY_LEVEL       0x03
#define CMDTYPE_TEMP_CALIBRATION    0x2D

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
    uint8_t     dead_band;                      // 1 ... 5 °C
    uint8_t     temperatureDisplayMode;         // 0x00 - °C, 0x01 - °F. Always °C (Not support)
    uint8_t     keypadLockout;                  // on off
} thermostat_settings_t;

extern uint8_t thermostat_mode;

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

#endif /* SRC_INCLUDE_APP_THERMOSTAT_H_ */
