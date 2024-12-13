#ifndef SRC_INCLUDE_APP_ENDPOINT_CFG_H_
#define SRC_INCLUDE_APP_ENDPOINT_CFG_H_

#define APP_ENDPOINT1 0x01
#define APP_ENDPOINT2 0x02
#define APP_ENDPOINT3 0x03
#define APP_ENDPOINT4 0x04
#define APP_ENDPOINT5 0x05

/**
 *  @brief Defined for basic cluster attributes
 */
typedef struct{
    uint8_t  zclVersion;
    uint8_t  appVersion;
    uint8_t  stackVersion;
    uint8_t  hwVersion;
    uint8_t  manuName[ZCL_BASIC_MAX_LENGTH];
    uint8_t  modelId[ZCL_BASIC_MAX_LENGTH];
    uint8_t  dateCode[ZCL_BASIC_MAX_LENGTH];
    uint8_t  powerSource;
    uint8_t  genDevClass;                        //attr 8
    uint8_t  genDevType;                         //attr 9
    uint8_t  deviceEnable;
    uint8_t  swBuildId[ZCL_BASIC_MAX_LENGTH];    //attr 4000
} zcl_basicAttr_t;

/**
 *  @brief Defined for identify cluster attributes
 */
typedef struct{
    uint16_t identifyTime;
}zcl_identifyAttr_t;

/**
 *  @brief Defined for group cluster attributes
 */
typedef struct{
    u8  nameSupport;
}zcl_groupAttr_t;

/**
 *  @brief Defined for scene cluster attributes
 */
typedef struct{
    u8   sceneCount;
    u8   currentScene;
    u8   nameSupport;
    bool sceneValid;
    u16  currentGroup;
}zcl_sceneAttr_t;

/**
 *  @brief Defined for time cluster attributes
 */
typedef struct {
    uint32_t time_utc;
    uint32_t time_local;
} zcl_timeAttr_t;

/**
 *  @brief Defined for level cluster attributes
 */
typedef struct {
    uint8_t     currentLevel;
    uint8_t     minLevel;
    uint8_t     maxLevel;
} zcl_levelAttr_t;

/**
 *  @brief Defined for Thermostat and HVAC UI CFG clusters attributes
 */
typedef struct {
    int16_t     localTemperature;               // 22°C * 100
    int16_t     outDoorTemperature;             // 24°C * 100
    int16_t     absMinHeatSetpointLimit;        // min 5°C * 100
    int16_t     absMaxHeatSetpointLimit;        // max 45°C * 100
    int16_t     minHeatSetpointLimit;           // min 5°C * 100
    int16_t     maxHeatSetpointLimit;           // max 45°C * 100
    int8_t      localTemperatureCalibration;    // in device -9°C...+9°C
    int16_t     occupiedHeatingSetpoint;        // 0°C ... 50°C * 100
    uint8_t     controlSequenceOfOperation;     // 0x02 Heating
    uint8_t     systemMode;                     // see /src/zcl/zcl_app_thermostat.h
    uint16_t    runningState;                   // 0x0000 - off, 0x0001 - heat
    uint8_t     startOfWeek;                    // see day_of_week_t in /src/zcl/zcl_app_thermostat.h
    uint8_t     weeklyTransNum;
    uint8_t     dailyTransNum;
    uint8_t     manual_progMode;                // 0x00 - manual mode, 0x01 - programming mode or invert :))
    uint8_t     sensor_used;                    // IN, ALL, OU - castom attribute
    int16_t     frostProtect;
    int16_t     heatProtect;
    uint8_t     dead_band;                      // 1 ... 5 °C
    uint8_t     temperatureDisplayMode;         // 0x00 - °C, 0x01 - °F. Always °C (Not support)
    uint8_t     keypadLockout;                  // on off
} zcl_thermostatAttr_t;

extern uint8_t APP_EP1_CB_CLUSTER_NUM;

/* Attributes */
extern zcl_basicAttr_t g_zcl_basicAttrs;
extern zcl_identifyAttr_t g_zcl_identifyAttrs;
extern zcl_groupAttr_t g_zcl_group1Attrs;
extern zcl_sceneAttr_t g_zcl_scene1Attrs;
extern zcl_thermostatAttr_t g_zcl_thermostatAttrs;
extern zcl_levelAttr_t g_zcl_levelAttrs;

#endif /* SRC_INCLUDE_APP_ENDPOINT_CFG_H_ */
