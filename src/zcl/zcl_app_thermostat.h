#ifndef SRC_ZCL_ZCL_APP_THERMOSTAT_H_
#define SRC_ZCL_ZCL_APP_THERMOSTAT_H_

#define SYS_MODE_OFF            0x00
#define SYS_MODE_AUTO           0x01
#define SYS_MODE_COOL           0x03
#define SYS_MODE_HEAT           0x04
#define SYS_MODE_EMERGENCY      0x05
#define SYS_MODE_PRECOOLING     0x06
#define SYS_MODE_FAN            0x07
#define SYS_MODE_DRY            0x08
#define SYS_MODE_SLEEP          0x09

#define RUN_MODE_OFF            0x00
#define RUN_MODE_COOL           0x03
#define RUN_MODE_HEAT           0x04

#define RUN_STATE_HEAT_BIT      0

#define MANUAL_MODE             0x00
#define PROG_MODE               0x01

#define ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED                   0xF000

//typedef enum {
//    SENSOR_IN   =   0x00,
//    SENSOR_AL,
//    SENSOR_OU
//} sensor_used_t;

typedef struct {
    uint16_t    minute;
    uint16_t    temperature;
} zcl_schedule_t;

typedef struct __attribute__((packed)) {
    heatMode_t schedule_mon[6];
    heatMode_t schedule_tue[6];
    heatMode_t schedule_wed[6];
    heatMode_t schedule_thu[6];
    heatMode_t schedule_fri[6];
    heatMode_t schedule_sat[6];
    heatMode_t schedule_sun[6];
} zcl_scheduleData_t;

typedef enum {
    DAY_SUN = 0x01, // Sunday
    DAY_MON = 0x02, // Monday
    DAY_TUE = 0x04, // Tuesday
    DAY_WED = 0x08, // Wednesday
    DAY_THU = 0x10, // Thursday
    DAY_FRI = 0x20, // Friday
    DAY_SAT = 0x40  // Saturday
} day_of_week_t;

extern zcl_scheduleData_t g_zcl_scheduleData;

uint8_t zcl_convert_temperature_fromCtoF(int16_t tempC);
int16_t zcl_convert_temperature_fromFtoC(int16_t tempF);

#endif /* SRC_ZCL_ZCL_APP_THERMOSTAT_H_ */
