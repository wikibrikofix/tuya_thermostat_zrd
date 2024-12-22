#ifndef SRC_INCLUDE_APP_TUYA_DATAPOINT_H_
#define SRC_INCLUDE_APP_TUYA_DATAPOINT_H_

/* data point for manufacturer id -
 * "u9bfwha0"
 * "aoclfnxz"
 *
 * type1 (model1)
*/
typedef enum {
    DP_TYPE1_ID_00    = 0x00,     // heat min  - if 0 - not support
    DP_TYPE1_ID_01    = 0x01,     // on off
    DP_TYPE1_ID_02    = 0x02,     // manual / programming
    DP_TYPE1_ID_03    = 0x03,     // unknown
    DP_TYPE1_ID_10    = 0x10,     // heat setpoint
    DP_TYPE1_ID_13    = 0x13,     // max heat
    DP_TYPE1_ID_18    = 0x18,     // local temperature
    DP_TYPE1_ID_1A    = 0x1A,     // hysteresis
    DP_TYPE1_ID_1B    = 0x1B,     // calibration
    DP_TYPE1_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE1_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE1_ID_2B    = 0x2B,     // Sensor IN/AL/OU
    DP_TYPE1_ID_65    = 0x65,     // schedule
} data_point_id_type0_t;


/* data point for manufacturer id -
 * "edl8pz1k"
 *
 * type2 (model2)
 */
typedef enum {
    DP_TYPE2_ID_00    = 0x00,     // 0 - not support
    DP_TYPE2_ID_01    = 0x01,     // on off
    DP_TYPE2_ID_02    = 0x02,     // manual / programming
    DP_TYPE2_ID_10    = 0x10,     // heat setpoint
    DP_TYPE2_ID_13    = 0x13,     // max heat
    DP_TYPE2_ID_18    = 0x18,     // local temperature
    DP_TYPE2_ID_1A    = 0x1A,     // min heat
    DP_TYPE2_ID_1B    = 0x1B,     // calibration
    DP_TYPE2_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE2_ID_28    = 0x28,     // lock / unlock keys
    DP_TYPE2_ID_2B    = 0x2B,     // Sensor IN/AL/OU
    DP_TYPE2_ID_67    = 0x67,     // hysteresis
    DP_TYPE2_ID_68    = 0x68,     // protection max temperature
    DP_TYPE2_ID_6F    = 0x6F,     // protection min temperature
    DP_TYPE2_ID_65    = 0x65,     // schedule sun
    DP_TYPE2_ID_66    = 0x66,     // temperature of outer sensor (if AL or OU)
    DP_TYPE2_ID_69    = 0x69,     // schedule sat
    DP_TYPE2_ID_6A    = 0x6A,     // schedule fri
    DP_TYPE2_ID_6B    = 0x6B,     // schedule thu
    DP_TYPE2_ID_6C    = 0x6C,     // schedule wed
    DP_TYPE2_ID_6D    = 0x6D,     // schedule tue
    DP_TYPE2_ID_6E    = 0x6E,     // schedule mon
} data_point_id_type1_t;


/* data point for manufacturer id -
 * "tagezcph"
 *
 * type3 (model3)
*/
typedef enum {
    DP_TYPE3_ID_00    = 0x00,     // 0 - not support
    DP_TYPE3_ID_01    = 0x01,     // on off
    DP_TYPE3_ID_02    = 0x02,     // manual / programming
    DP_TYPE3_ID_10    = 0x10,     // heat setpoint
    DP_TYPE3_ID_13    = 0x13,     // max heat
    DP_TYPE3_ID_18    = 0x18,     // local temperature
    DP_TYPE3_ID_1A    = 0x1A,     // min heat
    DP_TYPE3_ID_1B    = 0x1B,     // calibration
    DP_TYPE3_ID_1C    = 0x1C,     // default setting
    DP_TYPE3_ID_24    = 0x24,     // 0x00 - heat, 0x01 - idle
    DP_TYPE3_ID_27    = 0x27,     // lock / unlock keys
    DP_TYPE3_ID_28    = 0x28,     // eco mode
    DP_TYPE3_ID_2B    = 0x2B,     // Sensor IN/AL/OU
    DP_TYPE3_ID_67    = 0x67,     // hysteresis
    DP_TYPE3_ID_68    = 0x68,     // protection max temperature
    DP_TYPE3_ID_6F    = 0x6F,     // protection min temperature
    DP_TYPE3_ID_65    = 0x65,     // schedule sun
    DP_TYPE3_ID_66    = 0x66,     // temperature of outer sensor (if AL or OU)
    DP_TYPE3_ID_69    = 0x69,     // schedule sat
    DP_TYPE3_ID_6A    = 0x6A,     // schedule fri
    DP_TYPE3_ID_6B    = 0x6B,     // schedule thu
    DP_TYPE3_ID_6C    = 0x6C,     // schedule wed
    DP_TYPE3_ID_6D    = 0x6D,     // schedule tue
    DP_TYPE3_ID_6E    = 0x6E,     // schedule mon
    DP_TYPE3_ID_70    = 0x70,     // eco mode's temperature
    DP_TYPE3_ID_71    = 0x71,     // level brightness 06:00-22:00
    DP_TYPE3_ID_72    = 0x72,     // level brightness 22:00-06:00
} data_point_id_type2_t;

typedef enum {
    DP_IDX_ONOFF    = 0,
    DP_IDX_TEMP,
    DP_IDX_SETPOINT,
    DP_IDX_MIN,
    DP_IDX_MAX,
    DP_IDX_DEADZONE,
    DP_IDX_CALIBRATION,
    DP_IDX_RUNSTATE,
    DP_IDX_SENSOR,
    DP_IDX_PROG,
    DP_IDX_LOCKUNLOCK,
    DP_IDX_SCHEDULE,
    DP_IDX_UNKNOWN,
    DP_IDX_TEMP_OUT,
    DP_IDX_FROST_PROTECT,
    DP_IDX_HEAT_PROTECT,
    DP_IDX_SCHEDULE_MON,
    DP_IDX_SCHEDULE_TUE,
    DP_IDX_SCHEDULE_WED,
    DP_IDX_SCHEDULE_THU,
    DP_IDX_SCHEDULE_FRI,
    DP_IDX_SCHEDULE_SAT,
    DP_IDX_SCHEDULE_SUN,
    DP_IDX_LEVEL_A,
    DP_IDX_LEVEL_B,
    DP_IDX_ECO_MODE,
    DP_IDX_ECO_TEMP,
    DP_IDX_MAXNUM
} data_point_idx_t;

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

typedef enum {
    MANUF_NAME_1 = 0,
    MANUF_NAME_2,
    MANUF_NAME_3,
    MANUF_NAME_MAX
} manuf_name_t;

typedef struct __attribute__((packed)) {
    uint8_t  dp_id;
    uint8_t  dp_type;
    uint16_t dp_len;
    uint8_t  data[DATA_MAX_LEN-8];
} data_point_t;

typedef void (*remote_cmd_t)(void *args);
typedef void (*local_cmd_t)(void *args);

typedef struct {
    uint8_t         id;
    uint8_t         type;
    uint16_t        len;
    uint16_t        divisor;
    remote_cmd_t    remote_cmd;
    local_cmd_t     local_cmd;
} data_point_st_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t temperature;
} dp_schedule_model1_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint16_t temperature;
} dp_schedule_model2_t;

extern uint8_t manuf_name;
extern data_point_st_t *data_point_model;
extern const char8_t **tuya_manuf_names[];

void data_point_model_init();
data_point_st_t *data_point_model_arr[DP_IDX_MAXNUM];

#endif /* SRC_INCLUDE_APP_TUYA_DATAPOINT_H_ */
