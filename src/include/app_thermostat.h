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

/* Display brightness */
#define DEV_DYSPLAY_LEVEL0          0x00
#define DEV_DYSPLAY_LEVEL1          0x01
#define DEV_DYSPLAY_LEVEL2          0x02
#define DEV_DYSPLAY_LEVEL3          0x03
#define DEV_DYSPLAY_LEVEL4          0x04
#define DEV_DYSPLAY_LEVEL5          0x05
#define DEV_DYSPLAY_LEVEL6          0x06
#define DEV_DYSPLAY_LEVEL7          0x07
#define DEV_DYSPLAY_LEVEL8          0x08
#define DEV_DYSPLAY_LEVEL9          0x09

/* Local Temperature Calibration */
#define DEV_TEMP_CALIBRATION_N9     0xFFFFFFF7  // -9°C
#define DEV_TEMP_CALIBRATION_N8     0xFFFFFFF8  // -8°C
#define DEV_TEMP_CALIBRATION_N7     0xFFFFFFF9  // -7°C
#define DEV_TEMP_CALIBRATION_N6     0xFFFFFFFA  // -6°C
#define DEV_TEMP_CALIBRATION_N5     0xFFFFFFFB  // -5°C
#define DEV_TEMP_CALIBRATION_N4     0xFFFFFFFC  // -4°C
#define DEV_TEMP_CALIBRATION_N3     0xFFFFFFFD  // -3°C
#define DEV_TEMP_CALIBRATION_N2     0xFFFFFFFE  // -3°C
#define DEV_TEMP_CALIBRATION_N1     0xFFFFFFFF  // -2°C
#define DEV_TEMP_CALIBRATION_0      0x00000000  //  0°C
#define DEV_TEMP_CALIBRATION_P1     0x00000001  //  1°C
#define DEV_TEMP_CALIBRATION_P2     0x00000002  //  2°C
#define DEV_TEMP_CALIBRATION_P3     0x00000003  //  3°C
#define DEV_TEMP_CALIBRATION_P4     0x00000004  //  4°C
#define DEV_TEMP_CALIBRATION_P5     0x00000005  //  5°C
#define DEV_TEMP_CALIBRATION_P6     0x00000006  //  6°C
#define DEV_TEMP_CALIBRATION_P7     0x00000007  //  7°C
#define DEV_TEMP_CALIBRATION_P8     0x00000008  //  8°C
#define DEV_TEMP_CALIBRATION_P9     0x00000009  //  9°C

#define CLIENT_TEMP_CALIBRATION_MIN -90
#define CLIENT_TEMP_CALIBRATION_MAX  90

extern uint8_t thermostat_mode;

void remote_smd_sys_mode(uint8_t mode);
void remote_smd_heating_set(int16_t temp);
void remote_smd_temp_calibration(int8_t temp);
void set_run_state_bit(uint8_t bit_num, bool set);
void thermostat_onoff_state(int8_t onoff);
void thermostat_heatset_state(int32_t tempF);
void remote_smd_display_mode(uint8_t mode);
void remote_smd_keylock(uint8_t keylock);


#endif /* SRC_INCLUDE_APP_THERMOSTAT_H_ */
