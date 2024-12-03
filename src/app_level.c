#include "app_main.h"


static void remote_cmd_level(uint8_t level) {

//    printf("remote_cmd_level(). new level: %d\r\n", level);

//    pkt_output_t *pkt = (pkt_output_t*)cmdTx[CMD_BRIGHTNESS];
//    pkt->cnt++;
//
//    pkt->cmd_value = level;
//    add_cmd_queue(CMD_BRIGHTNESS, true, cmdTx[CMD_BRIGHTNESS]);
}


/*********************************************************************
 * @fn      app_displayMoveToLevelProcess
 *
 * @brief
 *
 * @param   cmdId
 * @param   cmd
 *
 * @return  None
 */

static void app_displayMoveToLevelProcess(u8 cmdId, moveToLvl_t *cmd) {

    if (cmd->level > 9) cmd->level = 9;

    remote_cmd_level(cmd->level);
}


/*********************************************************************
 * @fn      app_displaylevelCb
 *
 * @brief   Handler for ZCL LEVEL command. This function will set LEVEL attribute first.
 *
 * @param   pAddrInfo
 * @param   cmd - level cluster command id
 * @param   cmdPayload
 *
 * @return  status_t
 */

status_t app_displayLevelCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload) {
    if(pAddrInfo->dstEp == APP_ENDPOINT1){
        switch(cmdId){
            case ZCL_CMD_LEVEL_MOVE_TO_LEVEL:
                app_displayMoveToLevelProcess(cmdId, (moveToLvl_t *)cmdPayload);
                break;
            default:
                break;
        }
    }

    return ZCL_STA_SUCCESS;
}

