/******************************************************************************
 Copyright (C), 20016-2026, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hdmi_test_cec.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2010/07/08
Last Modified :
Description   : HDMI TEST CEC interface
Function List :
History       :
******************************************************************************/
#ifndef __HDMI_TEST_CEC_H__
#define __HDMI_TEST_CEC_H__

#define MAX_CEC_CMD_LEN     15

typedef enum
{
    HDMI_TEST_CEC_STANDBY,
    HDMI_TEST_CEC_IMAMGE_VIEW_ON,
    HDMI_TEST_CEC_TEXT_VIEW_ON,
    HDMI_TEST_CEC_ACTIVE_SOURCE,
    HDMI_TEST_CEC_GET_CEC_VERSION,
    HDMI_TEST_CEC_GET_MENU_LAN,
    HDMI_TEST_CEC_GET_PHY_ADDR,
    HDMI_TEST_CEC_GET_DEV_VENDOR_ID,
    HDMI_TEST_CEC_GET_OSD_NAME,
    HDMI_TEST_CEC_SET_OSD_STRING,
    HDMI_TEST_CEC_GET_POWER_STATUS,
    HDMI_TEST_CEC_SET_VOLUME_UP,
    HDMI_TEST_CEC_SET_VOLUME_DOWN,
    HDMI_TEST_CEC_SET_VOLUME_MUTE,
    HDMI_TEST_CEC_USER_DEFINE = 0xff,
}HDMI_TEST_CEC_CMD_E;

typedef struct hiHDMI_TEST_CEC_CMD_S
{
    HDMI_TEST_CEC_CMD_E enCmd;
    HI_U8 u8DestAddr;
    HI_U8 u8Opcode;
    HI_U8 u8Len;
    HI_U8 *u8Data;
}HDMI_TEST_CEC_CMD_S;

typedef struct hiHDMI_TEST_CEC_DEBUG_S
{
    HI_BOOL bLogView;
}HDMI_TEST_CEC_S;


HI_S32 hdmi_test_cec_enable(HI_UNF_HDMI_ID_E enHdmi);
HI_S32 hdmi_test_cec_disable(HI_UNF_HDMI_ID_E enHdmi);
HI_U32 hdmi_test_cec_setcmd(HI_UNF_HDMI_ID_E enHdmi, HDMI_TEST_CEC_CMD_S *pstCecCmd);
HI_S32 hdmi_test_cec_autoping(HI_UNF_HDMI_ID_E enHdmi);
HI_VOID HDMI_CEC_LogSet(HI_BOOL bLogView);


#endif

