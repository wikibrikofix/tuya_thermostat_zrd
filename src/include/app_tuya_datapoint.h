#ifndef SRC_INCLUDE_APP_TUYA_DATAPOINT_H_
#define SRC_INCLUDE_APP_TUYA_DATAPOINT_H_

typedef enum {
    MANUF_NAME_0 = 0,
    MANUF_NAME_1,
    MANUF_NAME_MAX
} manuf_name_t;

typedef struct {
    uint8_t     id;
    uint8_t     type;
    uint16_t    len;
    uint16_t    divisor;
} data_point_st_t;

typedef enum {
    DP_IDX_ONOFF    = 0,
    DP_IDX_TEMP,
    DP_IDX_SETPOINT,
    DP_IDX_MIN,
    DP_IDX_MAX,
    DP_IDX_HYSTERESIS,
    DP_IDX_CALIBRATION,
    DP_IDX_RUNSTATE,
    DP_IDX_SENSOR,
    DP_IDX_PROG,
    DP_IDX_LOCKUNLOCK,
    DP_IDX_SCHEDULE,
    DP_IDX_UNKNOWN,
    DP_IDX_MAXNUM
} data_point_idx_t;

typedef enum {
    DP_TYPE0_ID_00    = 0x00,     // heat min ?
    DP_TYPE0_ID_01    = 0x01,     // on off
    DP_TYPE0_ID_02    = 0x02,     // manual / programming
    DP_TYPE0_ID_03    = 0x03,     // unknown
    DP_TYPE0_ID_10    = 0x10,     // heat setpoint
    DP_TYPE0_ID_13    = 0x13,     // max heat
    DP_TYPE0_ID_18    = 0x18,     // local temperature
    DP_TYPE0_ID_1A    = 0x1A,     // hysteresis
    DP_TYPE0_ID_1B    = 0x1B,     // calibration
    DP_TYPE0_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE0_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE0_ID_2B    = 0x2B,     // Sensor IN/AL/OU
    DP_TYPE0_ID_65    = 0x65,     // schedule
} data_point_id_type0_t;

/* Data Point
 *  Type    Data type   Data length     Description
    0x00    Raw         Custom          Raw data type in hex format, with customizable bytes.
    0x01    Boolean     1               Boolean data type. Valid values include 0x00 and 0x01.
    0x02    Value       4               Value data type, for example, 1, 23, and 104.
    0x03    String      Custom          Custom string.
    0x04    Enum        1               Enum data type, ranging from 0 to 255.
    0x05    Bitmap      1/2/4           Bitmap data type, used to report error codes.
 */

typedef enum {
    DP_RAW = 0,
    DP_BOOL,
    DP_VAL,
    DP_STR,
    DP_ENUM,
    DP_BITMAP
} dp_type_t;

extern uint8_t manuf_name;
extern data_point_st_t *data_point_type;
extern const char8_t **tuya_manuf_names[];
extern data_point_st_t data_point_type0[DP_IDX_MAXNUM];
extern data_point_st_t data_point_type1[DP_IDX_MAXNUM];



#endif /* SRC_INCLUDE_APP_TUYA_DATAPOINT_H_ */
