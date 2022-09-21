
/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_hal_cec.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/
#ifndef __HDMI_MCU_CEC_REG_H__
#define __HDMI_MCU_CEC_REG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hdmi_mcu_com.h"

#define CEC_MAX_RAW_SIZE            15
#define CEC_MAX_MSG_NUM             10
#define CEC_PHY_ADDR_SIZE           4

#define IRQ_HDMITX_CEC_MASK         0x20        // hdmitx_cec irq 29

typedef enum
{
    CEC_PING_START,
    CEC_PING_WAIT,
    CEC_PING_TIMEOUT,
    CEC_PING_BUTT
}CEC_PING_STATUS_E;

enum OpcodeEnum
{
    CEC_OPCODE_IMAGE_VIEW_ON        = 0x04,
    CEC_OPCODE_TEXT_VIEW_ON         = 0x0d,
    CEC_OPCODE_SET_MENU_LANGUAGE    = 0x32,
    CEC_OPCODE_STANDBY              = 0x36, // standby
    CEC_OPCODE_GIVE_OSD_NAME        = 0x46, // 'his'
    CEC_OPCODE_SET_OSD_NAME         = 0x47,
    CEC_OPCODE_ROUTING_CHANGE       = 0x80,
    CEC_OPCODE_ACTIVE_SOURCE        = 0x82,
    CEC_OPCODE_GIVE_PHYSICAL_ADDRESS= 0x83, // report phyaddr
    CEC_OPCODE_REPORT_PHYADDR       = 0x84,
    CEC_OPCODE_REQUEST_ACTIVE_SOURCE= 0x85, // CEC_OPCODE_ACTIVE_SOURCE response active source
    CEC_OPCODE_SET_STREAM_PATH      = 0x86,
    CEC_OPCODE_DEVICE_VENDOR_ID     = 0x87,
    CEC_OPCODE_GIVE_DEVICE_VENDOR_ID= 0x8c, // 'his'
    CEC_OPCODE_MENU_REQUEST         = 0x8d, // 0X00 active,0x01 deactive
    CEC_OPCODE_MENU_STATUS          = 0x8e,
    CEC_OPCODE_GIVE_DEVICE_POWER_STATUS,
    CEC_OPCODE_REPORT_POWER_STATUS  = 0x90,
    CEC_OPCODE_GET_MENU_LANGUAGE    = 0x91, // 'chi'
    CEC_OPCODE_CEC_VERSION          = 0x9e,
    CEC_OPCODE_GET_CEC_VERSION      = 0x9f, // report cec version 0x04
    CEC_OPCODE_ABORT_MESSAGE        = 0xff  // no response
};

typedef enum
{
    CEC_LOGICALADD_TV               = 0X00,
    CEC_LOGICALADD_RECORDDEV_1      = 0X01,
    CEC_LOGICALADD_RECORDDEV_2      = 0X02,
    CEC_LOGICALADD_TUNER_1          = 0X03,
    CEC_LOGICALADD_PLAYDEV_1        = 0X04,
    CEC_LOGICALADD_AUDIOSYSTEM      = 0X05,
    CEC_LOGICALADD_TUNER_2          = 0X06,
    CEC_LOGICALADD_TUNER_3          = 0X07,
    CEC_LOGICALADD_PLAYDEV_2        = 0X08,
    CEC_LOGICALADD_RECORDDEV_3      = 0X09,
    CEC_LOGICALADD_TUNER_4          = 0X0A,
    CEC_LOGICALADD_PLAYDEV_3        = 0X0B,
    CEC_LOGICALADD_RESERVED_1       = 0X0C,
    CEC_LOGICALADD_RESERVED_2       = 0X0D,
    CEC_LOGICALADD_SPECIALUSE       = 0X0E,
    CEC_LOGICALADD_BROADCAST        = 0X0F,
    CEC_LOGICALADD_BUTT
}CEC_LOGICALADD_E;

#if 0
typedef struct
{
    HI_U8           u8Length;
    HI_U8           u8Data[CEC_MAX_RAW_SIZE];
}CEC_RAWDATA_S;
#endif

typedef struct // union
{
    HI_U8           u8Length;
    HI_U8           u8Data[CEC_MAX_RAW_SIZE];
    //CEC_RAWDATA_S   stRawData;
    //CEC_UICMD_E     enUIOpcode;
}CEC_OPERAND_S;

typedef struct
{
    CEC_LOGICALADD_E enSrcAddr;
    CEC_LOGICALADD_E enDestAddr;
    HI_U8            u8Opcode;
    CEC_OPERAND_S    stOperand;
}CEC_MSG_FRAME_S;

typedef struct
{
    HI_U16          u16WtPtr;
    HI_U16          u16RdPtr;
    HI_U16          u16RdAbleCnt;
    HI_U16          u16InCnt;
    HI_U16          u16OutCnt;
    CEC_MSG_FRAME_S stPool[CEC_MAX_MSG_NUM];
}CEC_POOL_S;

typedef union
{
    struct
    {
        HI_U8       bit1Init        :   1;
        HI_U8       bit1Enable      :   1;  // hw/irq Enable
        HI_U8       bit1PingTimeout :   1;
    }u8;

    HI_U8           u8Byte;
}CEC_STATUS_U;

typedef struct
{
    CEC_STATUS_U      unStat;
    CEC_LOGICALADD_E  enMyLogicAddr;
    //HI_U16          u16SinkMapId;
    //HI_U16          u16MyCaptureId;
    HI_U8             au8MyPhyAddr[CEC_PHY_ADDR_SIZE];
    CEC_POOL_S        stRx;
    CEC_MSG_FRAME_S   stTx;
    CEC_PING_STATUS_E enPingStatus;
    HI_U16            u16PingTimeout;
    //CEC_POOL_S      stTx;
}CEC_INFO_S;

HI_S16 CecRxPoolWrite(CEC_MSG_FRAME_S *pstFrame);
HI_S16 CecRxPoolRead(CEC_MSG_FRAME_S *pstFrame);

//CEC_INFO_S *CecInfoPtrGet(HI_VOID);

/**
\brief	  CEC init
\param      none
\retval  HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_CecInit(HI_VOID);

/**
\brief	  CEC deinit
\param      none
\retval  HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_CecDeInit(HI_VOID);

/**
\brief	  CEC enable
\param[out]     @bEnable      enable/disable cec
\retval  HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_CecEnable(HI_BOOL bEnable);

/**
\brief	  CEC phy_addr set
\param[in]     @pu8PhyAddr      cec phy address
\param[out]    @pu8LogicAddr    pointer to cec logic addr
\retval  HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_CecPhyAddrSet(HI_U8 *pu8PhyAddr, CEC_LOGICALADD_E *penLogicAddr);

/**
\brief	  CEC frame recieve.
\param[out]     @pstFrame      pointer to a cec frame
\retval  HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_CecFrameRx(CEC_MSG_FRAME_S *pstFrame);

/**
\brief	  Cec frame sent
\param[in]     @pstFrame      pointer to a cec frame
\retval  HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_CecFrameTx(CEC_MSG_FRAME_S *pstFrame);

/**
\brief	  CEC irq handle
\param[in]      none
\retval         none
*/
//HI_VOID MCU_HDMI_CecIrqHandle(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  //__HDMI_MCU_CEC_REG_H__

