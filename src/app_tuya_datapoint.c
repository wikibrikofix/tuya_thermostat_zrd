#include "tl_common.h"

#include "app_main.h"

/* data point for manufacturer id -
 * "u9bfwha0"
 *
*/
data_point_st_t data_point_type0[DP_IDX_MAXNUM] = {
        {DP_TYPE0_ID_01, DP_BOOL, 1,    1},             // on off
        {DP_TYPE0_ID_18, DP_VAL,  4,    10},            // local temperature
        {DP_TYPE0_ID_10, DP_VAL,  4,    1},             // heat setpoint
        {DP_TYPE0_ID_00, DP_VAL,  0,    0},             // heat min
        {DP_TYPE0_ID_13, DP_VAL,  4,    1},             // max heat setpoint
        {DP_TYPE0_ID_1A, DP_VAL,  4,    1},             // hysteresis
        {DP_TYPE0_ID_1B, DP_VAL,  4,    1},             // local temperature calibration
        {DP_TYPE0_ID_24, DP_BOOL, 1,    1},             // 0x00 - heat, 0x01 - idle
        {DP_TYPE0_ID_2B, DP_ENUM, 1,    1},             // sensor IN/AL/OU
        {DP_TYPE0_ID_02, DP_ENUM, 1,    1},             // manual (setpoint) / programming (schedule)
        {DP_TYPE0_ID_28, DP_BOOL, 1,    1},             // lock / unlock keys (child lock)
        {DP_TYPE0_ID_65, DP_RAW,  0x24, 1},             // schedule
        {DP_TYPE0_ID_03, DP_BOOL, 1,    1},             // unknown
};

data_point_st_t data_point_type1[DP_IDX_MAXNUM] = {{0}};

static const char8_t *tuya_manuf_name0[] = {
//                                           "aoclfnxz",
//                                           "ztvwu4nk",
//                                           "5toc8efa",
//                                           "ye5jkfsb",
                                           "u9bfwha0",
                                            NULL};
/* only test. for future */
static const char8_t *tuya_manuf_name1[] = {
                                           "cjbofhxw",
                                           "wbhaespm",
                                           "mwomyz5n",
                                            NULL};


data_point_st_t *data_point_type = data_point_type0;
const char8_t **tuya_manuf_names[] = {tuya_manuf_name0, tuya_manuf_name1};
uint8_t manuf_name = MANUF_NAME_0;

