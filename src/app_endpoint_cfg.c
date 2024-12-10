#include "tl_common.h"
#include "zcl_include.h"

#include "app_main.h"

#ifndef ZCL_BASIC_MFG_NAME
#define ZCL_BASIC_MFG_NAME          {6,'T','E','L','I','N','K'}
#endif
#ifndef ZCL_BASIC_MODEL_ID
#define ZCL_BASIC_MODEL_ID          {8,'T','L','S','R','8','2','x','x'}
#endif
#ifndef ZCL_BASIC_SW_BUILD_ID
#define ZCL_BASIC_SW_BUILD_ID       {10,'0','1','2','2','0','5','2','0','1','7'}
#endif

#define R               ACCESS_CONTROL_READ
#define RW              ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE
#define RR              ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE
#define RRW             ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE | ACCESS_CONTROL_REPORTABLE

#define ZCL_UINT8       ZCL_DATA_TYPE_UINT8
#define ZCL_INT8        ZCL_DATA_TYPE_INT8
#define ZCL_UINT16      ZCL_DATA_TYPE_UINT16
#define ZCL_INT16       ZCL_DATA_TYPE_INT16
#define ZCL_UINT32      ZCL_DATA_TYPE_UINT32
#define ZCL_ENUM8       ZCL_DATA_TYPE_ENUM8
#define ZCL_BOOLEAN     ZCL_DATA_TYPE_BOOLEAN
#define ZCL_BITMAP8     ZCL_DATA_TYPE_BITMAP8
#define ZCL_BITMAP16    ZCL_DATA_TYPE_BITMAP16
#define ZCL_CHAR_STR    ZCL_DATA_TYPE_CHAR_STR
#define ZCL_UTC         ZCL_DATA_TYPE_UTC

/**
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
const uint16_t app_ep1_inClusterList[] = {
    ZCL_CLUSTER_GEN_BASIC,
    ZCL_CLUSTER_GEN_IDENTIFY,
#ifdef ZCL_GROUP
    ZCL_CLUSTER_GEN_GROUPS,
#endif
#ifdef ZCL_SCENE
    ZCL_CLUSTER_GEN_SCENES,
#endif
#ifdef ZCL_ON_OFF
    ZCL_CLUSTER_GEN_ON_OFF,
#endif
#ifdef ZCL_ZLL_COMMISSIONING
    ZCL_CLUSTER_TOUCHLINK_COMMISSIONING,
#endif
#ifdef ZCL_LEVEL_CTRL
    ZCL_CLUSTER_GEN_LEVEL_CONTROL,
#endif
#ifdef ZCL_THERMOSTAT
    ZCL_CLUSTER_HAVC_THERMOSTAT,
    ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG,
#endif
};

/**
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
const uint16_t app_ep1_outClusterList[] = {
#ifdef ZCL_OTA
    ZCL_CLUSTER_OTA,
    ZCL_CLUSTER_GEN_TIME,
#endif
};

/**
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define APP_EP1_IN_CLUSTER_NUM   (sizeof(app_ep1_inClusterList)/sizeof(app_ep1_inClusterList[0]))
#define APP_EP1_OUT_CLUSTER_NUM  (sizeof(app_ep1_outClusterList)/sizeof(app_ep1_outClusterList[0]))

/**
 *  @brief Definition for simple description for HA profile
 */
const af_simple_descriptor_t app_ep1Desc = {
    HA_PROFILE_ID,                          /* Application profile identifier */
    HA_DEV_THERMOSTAT,                      /* Application device identifier */
    APP_ENDPOINT1,                          /* Endpoint */
    2,                                      /* Application device version */
    0,                                      /* Reserved */
    APP_EP1_IN_CLUSTER_NUM,                 /* Application input cluster count */
    APP_EP1_OUT_CLUSTER_NUM,                /* Application output cluster count */
    (uint16_t *)app_ep1_inClusterList,      /* Application input cluster list */
    (uint16_t *)app_ep1_outClusterList,     /* Application output cluster list */
};



/* Basic */
zcl_basicAttr_t g_zcl_basicAttrs =
{
    .zclVersion     = 0x03,
    .appVersion     = APP_RELEASE,
    .stackVersion   = (STACK_RELEASE|STACK_BUILD),
    .hwVersion      = HW_VERSION,
    .manuName       = ZCL_BASIC_MFG_NAME,
    .modelId        = ZCL_BASIC_MODEL_ID,
    .dateCode       = ZCL_BASIC_DATE_CODE,
    .powerSource    = POWER_SOURCE_MAINS_1_PHASE,
    .swBuildId      = ZCL_BASIC_SW_BUILD_ID,
    .deviceEnable   = TRUE,
};

const zclAttrInfo_t basic_attrTbl[] =
{
    { ZCL_ATTRID_BASIC_ZCL_VER,             ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.zclVersion  },
    { ZCL_ATTRID_BASIC_APP_VER,             ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.appVersion  },
    { ZCL_ATTRID_BASIC_STACK_VER,           ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.stackVersion},
    { ZCL_ATTRID_BASIC_HW_VER,              ZCL_UINT8,      R,  (uint8_t*)&g_zcl_basicAttrs.hwVersion   },
    { ZCL_ATTRID_BASIC_MFR_NAME,            ZCL_CHAR_STR,   R,  (uint8_t*)g_zcl_basicAttrs.manuName     },
    { ZCL_ATTRID_BASIC_MODEL_ID,            ZCL_CHAR_STR,   R,  (uint8_t*)g_zcl_basicAttrs.modelId      },
    { ZCL_ATTRID_BASIC_DATE_CODE,           ZCL_CHAR_STR,   R,  (uint8_t*)g_zcl_basicAttrs.dateCode     },
    { ZCL_ATTRID_BASIC_POWER_SOURCE,        ZCL_ENUM8,      R,  (uint8_t*)&g_zcl_basicAttrs.powerSource },
    { ZCL_ATTRID_BASIC_DEV_ENABLED,         ZCL_BOOLEAN,    RW, (uint8_t*)&g_zcl_basicAttrs.deviceEnable},
    { ZCL_ATTRID_BASIC_SW_BUILD_ID,         ZCL_CHAR_STR,   R,  (uint8_t*)&g_zcl_basicAttrs.swBuildId   },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},

};

#define ZCL_BASIC_ATTR_NUM       sizeof(basic_attrTbl) / sizeof(zclAttrInfo_t)


/* Identify */
zcl_identifyAttr_t g_zcl_identifyAttrs =
{
    .identifyTime   = 0x0000,
};

const zclAttrInfo_t identify_attrTbl[] =
{
    { ZCL_ATTRID_IDENTIFY_TIME,             ZCL_UINT16,     RW, (uint8_t*)&g_zcl_identifyAttrs.identifyTime},

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},
};

#define ZCL_IDENTIFY_ATTR_NUM           sizeof(identify_attrTbl) / sizeof(zclAttrInfo_t)

#ifdef ZCL_GROUP
/* Group */
zcl_groupAttr_t g_zcl_group1Attrs =
{
    .nameSupport    = 0,
};

const zclAttrInfo_t group_attr1Tbl[] =
{
    { ZCL_ATTRID_GROUP_NAME_SUPPORT,        ZCL_BITMAP8,    R,  (uint8_t*)&g_zcl_group1Attrs.nameSupport},

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},
};

#define ZCL_GROUP_1ATTR_NUM    sizeof(group_attr1Tbl) / sizeof(zclAttrInfo_t)

#endif

#ifdef ZCL_SCENE
/* Scene */
zcl_sceneAttr_t g_zcl_scene1Attrs = {
    .sceneCount     = 0,
    .currentScene   = 0,
    .currentGroup   = 0x0000,
    .sceneValid     = FALSE,
    .nameSupport    = 0,
};

const zclAttrInfo_t scene_attr1Tbl[] = {
    { ZCL_ATTRID_SCENE_SCENE_COUNT,         ZCL_UINT8,      R,  (uint8_t*)&g_zcl_scene1Attrs.sceneCount   },
    { ZCL_ATTRID_SCENE_CURRENT_SCENE,       ZCL_UINT8,      R,  (uint8_t*)&g_zcl_scene1Attrs.currentScene },
    { ZCL_ATTRID_SCENE_CURRENT_GROUP,       ZCL_UINT16,     R,  (uint8_t*)&g_zcl_scene1Attrs.currentGroup },
    { ZCL_ATTRID_SCENE_SCENE_VALID,         ZCL_BOOLEAN,    R,  (uint8_t*)&g_zcl_scene1Attrs.sceneValid   },
    { ZCL_ATTRID_SCENE_NAME_SUPPORT,        ZCL_BITMAP8,    R,  (uint8_t*)&g_zcl_scene1Attrs.nameSupport  },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16,     R,  (uint8_t*)&zcl_attr_global_clusterRevision},
};

#define ZCL_SCENE_1ATTR_NUM   sizeof(scene_attr1Tbl) / sizeof(zclAttrInfo_t)

#endif

#ifdef ZCL_LEVEL_CTRL
/* Level */
zcl_levelAttr_t g_zcl_levelAttrs = {
    .currentLevel = 9,
    .minLevel = 1,
    .maxLevel = 9,
};

const zclAttrInfo_t level_attrTbl[] =
{
    { ZCL_ATTRID_LEVEL_CURRENT_LEVEL,       ZCL_UINT8,  RR, (uint8_t*)&g_zcl_levelAttrs.currentLevel },
    { ZCL_ATTRID_LEVEL_MIN_LEVEL,           ZCL_UINT8,  R,  (uint8_t*)&g_zcl_levelAttrs.minLevel },
    { ZCL_ATTRID_LEVEL_MAX_LEVEL,           ZCL_UINT8,  R,  (uint8_t*)&g_zcl_levelAttrs.maxLevel },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16, R,  (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_LEVEL_ATTR_NUM   sizeof(level_attrTbl) / sizeof(zclAttrInfo_t)
#endif

zcl_timeAttr_t g_zcl_timeAttrs = {
    .time_utc   = 0xffffffff,
    .time_local = 0xffffffff,
};

const zclAttrInfo_t time_attrTbl[] =
{
    { ZCL_ATTRID_TIME,                      ZCL_UTC,    RW, (uint8_t*)&g_zcl_timeAttrs.time_utc         },
    { ZCL_ATTRID_LOCAL_TIME,                ZCL_UINT32, R,  (uint8_t*)&g_zcl_timeAttrs.time_local       },

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,   ZCL_UINT16, R,  (uint8_t*)&zcl_attr_global_clusterRevision  },
};

#define ZCL_TIME_ATTR_NUM    sizeof(time_attrTbl) / sizeof(zclAttrInfo_t)


#ifdef ZCL_THERMOSTAT

zcl_thermostatAttr_t g_zcl_thermostatAttrs = {
    .localTemperature = 2200,               // 22°C * 100
    .absMinHeatSetpointLimit = 500,         // min  5°C * 100 ( +5°C ... +15°C)
    .absMaxHeatSetpointLimit = 4500,        // max 45°C * 100 (+15°C ... +45°C)
    .minHeatSetpointLimit = 500,            // min  5°C * 100 ( +5°C ... +15°C)
    .maxHeatSetpointLimit = 4500,           // max 45°C * 100 (+15°C ... +45°C)
    .localTemperatureCalibration = 0,       // in device -9°C...+9°C
    .occupiedHeatingSetpoint = 2200,        // set 22°C * 100
    .controlSequenceOfOperation = 0x02,     // 0x02 Heating
    .systemMode = SYS_MODE_OFF,             // see /src/zcl/zcl_app_thermostat.h
    .runningState = 0x0000,                 // 0x0000 - off, 0x0001 - heat
    .manual_progMode = 0x00,                // 0x00 - manual mode, 0x01 - programming mode
    .sensor_used = SENSOR_IN,               // IN, ALL, OU
    .dead_band = HYSTERESIS_MIN,            // 1 ... 5 °C
    .temperatureDisplayMode = 0x00,         // 0x00 - °C, 0x01 - °F (Not support)
    .keypadLockout = 0x00,                  // on off
    .startOfWeek = DAY_MON,                 // 1 - Monday
    .weeklyTransNum = 3,                    // 1 - Mon-Fri, 2 - Sat, 3 - Sun
    .dailyTransNum = 4,
};


const zclAttrInfo_t thermostat_attrTbl[] = {
        { ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMPERATURE,             ZCL_INT16,      RR,     (uint8_t*)&g_zcl_thermostatAttrs.localTemperature           },
        { ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MIN_HEAT_SETPOINT_LIMIT,   ZCL_INT16,      R,      (uint8_t*)&g_zcl_thermostatAttrs.absMinHeatSetpointLimit    },
        { ZCL_ATTRID_HVAC_THERMOSTAT_ABS_MAX_HEAT_SETPOINT_LIMIT,   ZCL_INT16,      R,      (uint8_t*)&g_zcl_thermostatAttrs.absMaxHeatSetpointLimit    },
        { ZCL_ATTRID_HVAC_THERMOSTAT_MIN_HEAT_SETPOINT_LIMIT,       ZCL_INT16,      RRW,    (uint8_t*)&g_zcl_thermostatAttrs.minHeatSetpointLimit       },
        { ZCL_ATTRID_HVAC_THERMOSTAT_MAX_HEAT_SETPOINT_LIMIT,       ZCL_INT16,      RRW,    (uint8_t*)&g_zcl_thermostatAttrs.maxHeatSetpointLimit       },
        { ZCL_ATTRID_HVAC_THERMOSTAT_LOCAL_TEMP_CALIBRATION,        ZCL_INT8,       RRW,    (uint8_t*)&g_zcl_thermostatAttrs.localTemperatureCalibration},
        { ZCL_ATTRID_HVAC_THERMOSTAT_OCCUPIED_HEATING_SETPOINT,     ZCL_INT16,      RRW,    (uint8_t*)&g_zcl_thermostatAttrs.occupiedHeatingSetpoint    },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CTRL_SEQUENCE_OF_OPERATION,    ZCL_ENUM8,      R,      (uint8_t*)&g_zcl_thermostatAttrs.controlSequenceOfOperation },
        { ZCL_ATTRID_HVAC_THERMOSTAT_SYS_MODE,                      ZCL_ENUM8,      RRW,    (uint8_t*)&g_zcl_thermostatAttrs.systemMode                 },
        {ZCL_ATTRID_HVAC_THERMOSTAT_PROGRAMMING_OPERATION_MODE,     ZCL_BITMAP8,    RRW,    (uint8_t*)&g_zcl_thermostatAttrs.manual_progMode            },
        { ZCL_ATTRID_HVAC_THERMOSTAT_RUNNING_STATE,                 ZCL_BITMAP16,   RR,     (uint8_t*)&g_zcl_thermostatAttrs.runningState               },
        { ZCL_ATTRID_HVAC_THERMOSTAT_MIN_SETPOINT_DEAD_BAND,        ZCL_INT8,       RRW,    (uint8_t*)&g_zcl_thermostatAttrs.dead_band                  },
        { ZCL_ATTRID_HVAC_THERMOSTAT_START_OF_WEEK,                 ZCL_ENUM8,      R,      (uint8_t*)&g_zcl_thermostatAttrs.startOfWeek                },
        { ZCL_ATTRID_HVAC_THERMOSTAT_NUM_OF_WEEKLY_TRANSITIONS,     ZCL_INT8,       R,      (uint8_t*)&g_zcl_thermostatAttrs.weeklyTransNum             },
        { ZCL_ATTRID_HVAC_THERMOSTAT_NUM_OF_DAILY_TRANSITIONS,      ZCL_INT8,       R,      (uint8_t*)&g_zcl_thermostatAttrs.dailyTransNum              },
        { ZCL_ATTRID_HVAC_THERMOSTAT_CUSTOM_SENSOR_USED,            ZCL_ENUM8,      RRW,    (uint8_t*)&g_zcl_thermostatAttrs.sensor_used                },

        { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,                       ZCL_UINT16,     R,      (uint8_t*)&zcl_attr_global_clusterRevision                  },
};

#define ZCL_THERMOSTAT_ATTR_NUM   sizeof(thermostat_attrTbl) / sizeof(zclAttrInfo_t)

const zclAttrInfo_t thermostat_ui_cfg_attrTbl[] = {
        { ZCL_ATTRID_HVAC_TEMPERATURE_DISPLAY_MODE, ZCL_ENUM8,  RRW,    (uint8_t*)&g_zcl_thermostatAttrs.temperatureDisplayMode },
        { ZCL_ATTRID_HVAC_KEYPAD_LOCKOUT,           ZCL_ENUM8,  RRW,    (uint8_t*)&g_zcl_thermostatAttrs.keypadLockout          },

        { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION,       ZCL_UINT16, R,      (uint8_t*)&zcl_attr_global_clusterRevision              },
};

#define ZCL_THERMOSTAT_UIC_ATTR_NUM   sizeof(thermostat_ui_cfg_attrTbl) / sizeof(zclAttrInfo_t)
#endif


/**
 *  @brief Definition for simple switch ZCL specific cluster
 */
const zcl_specClusterInfo_t g_appEp1ClusterList[] = {
    {ZCL_CLUSTER_GEN_BASIC,     MANUFACTURER_CODE_NONE, ZCL_BASIC_ATTR_NUM,     basic_attrTbl,      zcl_basic_register,     app_basicCb},
    {ZCL_CLUSTER_GEN_IDENTIFY,  MANUFACTURER_CODE_NONE, ZCL_IDENTIFY_ATTR_NUM,  identify_attrTbl,   zcl_identify_register,  app_identifyCb},
#ifdef ZCL_GROUP
    {ZCL_CLUSTER_GEN_GROUPS,    MANUFACTURER_CODE_NONE, ZCL_GROUP_1ATTR_NUM,    group_attr1Tbl,     zcl_group_register,     NULL},
#endif
#ifdef ZCL_SCENE
    {ZCL_CLUSTER_GEN_SCENES,    MANUFACTURER_CODE_NONE, ZCL_SCENE_1ATTR_NUM,    scene_attr1Tbl,     zcl_scene_register,     app_sceneCb},
#endif
#ifdef ZCL_LEVEL_CTRL
    {ZCL_CLUSTER_GEN_LEVEL_CONTROL, MANUFACTURER_CODE_NONE, ZCL_LEVEL_ATTR_NUM, level_attrTbl,      zcl_level_register,     app_displayLevelCb},
#endif
    {ZCL_CLUSTER_GEN_TIME,      MANUFACTURER_CODE_NONE, ZCL_TIME_ATTR_NUM,      time_attrTbl,       zcl_time_register,      app_timeCb},
#ifdef ZCL_THERMOSTAT
    {ZCL_CLUSTER_HAVC_THERMOSTAT, MANUFACTURER_CODE_NONE, ZCL_THERMOSTAT_ATTR_NUM, thermostat_attrTbl, zcl_thermostat_register, app_thermostatCb},
    {ZCL_CLUSTER_HAVC_USER_INTERFACE_CONFIG, MANUFACTURER_CODE_NONE, ZCL_THERMOSTAT_UIC_ATTR_NUM, thermostat_ui_cfg_attrTbl, zcl_thermostat_ui_cfg_register, app_thermostat_uicCb},
#endif
};

uint8_t APP_EP1_CB_CLUSTER_NUM = (sizeof(g_appEp1ClusterList)/sizeof(g_appEp1ClusterList[0]));

