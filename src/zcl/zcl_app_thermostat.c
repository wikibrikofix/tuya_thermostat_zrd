#include "zcl_include.h"
#include "zcl_app_thermostat.h"

uint8_t zcl_convert_temperature_fromCtoF(int16_t tempC) {

    return (((tempC*18 + 250)/500 + 64)/2);
}

int16_t zcl_convert_temperature_fromFtoC(int16_t tempF) {

    return (((tempF*2 - 64)*5000 + 90)/180);
}

