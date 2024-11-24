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

typedef enum {
    DAY_SUN = 0x00, // Sunday
    DAY_MON = 0x01, // Monday
    DAY_TUE = 0x02, // Tuesday
    DAY_WED = 0x03, // Wednesday
    DAY_THU = 0x04, // Thursday
    DAY_FRI = 0x05, // Friday
    DAY_SAT = 0x06  // Saturday
} day_of_week_t;


uint8_t zcl_convert_temperature_fromCtoF(int16_t tempC);
int16_t zcl_convert_temperature_fromFtoC(int16_t tempF);

#endif /* SRC_ZCL_ZCL_APP_THERMOSTAT_H_ */
