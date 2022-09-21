/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_hal_ddc_edid.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/
#ifndef __HDMI_MCU_DDC_EDID_H__
#define __HDMI_MCU_DDC_EDID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hdmi_mcu_com.h"

//#define DDC_DEFAULT_TIMEOUT_ACCESS      100
//#define DDC_DEFAULT_TIMEOUT_HPD         100
#define DDC_DEFAULT_TIMEOUT_IN_PROG     20
#define DDC_DEFAULT_TIMEOUT_SCL         1
#define DDC_DEFAULT_TIMEOUT_SDA         30
#define DDC_DEFAULT_TIMEOUT_ISSUE       20

#if 0
typedef enum
{
    DDC_FUNC_TYPE_EDID, //NO ACK
    DDC_FUNC_TYPE_HDCP, //NO ACK
    DDC_FUNC_TYPE_SCDC, //ACK
    DDC_FUNC_TYPE_BUTT,
}DDC_FUNC_TYPE_E;

typedef enum
{
	DDC_MASTER_MODE_PWD  = 0x0,
    DDC_MASTER_MODE_AON  = 0x1,
} DDC_MASTER_MODE_E;
#endif

typedef enum
{
    //DDC_MODE_READ_SINGLE_NO_ACK,    //0b0000
    //DDC_MODE_READ_SINGLE_ACK,       //0b0001
    DDC_MODE_READ_MUTIL_NO_ACK   = 0x02,     //0b0010
    //DDC_MODE_READ_MUTIL_ACK,        //0b0011
    DDC_MODE_READ_SEGMENT_NO_ACK = 0x04,   //0b0100
    //DDC_MODE_READ_SEGMENT_ACK,      //0b0101
    //DDC_MODE_WRITE_MUTIL_NO_ACK,    //0b0110
    //DDC_MODE_WRITE_MUTIL_ACK,       //0b0111
    DDC_MODE_BUTT
}DDC_ISSUE_MODE_E;

typedef union
{
    struct {
        //HI_U16          bzAccessWaitTimeOut : 1 ;
        HI_U16          bzBusLowScl         : 1 ;
        HI_U16          bzBusLowSda         : 1 ;
        //HI_U16          bzErrIsseuMode      : 1 ;
        HI_U16          bzIssueTimeOut      : 1 ;
        //HI_U16          bzBusNoAck          : 1 ;
        HI_U16          bzInProgTimeOut     : 1 ;
        HI_U16          bzHpdNoExist        : 1 ;
        HI_U16          bzClrErrFail        : 1 ;
        HI_U16          bzReserved          : 10;
    } bits;

    HI_U16  u16;
}DDC_ERR_U;

typedef struct
{
    HI_U8               u8Segment;
    HI_U8               u8Offset;
    DDC_ISSUE_MODE_E    enIssueMode;
    //DDC_FUNC_TYPE_E     enFuncType;
    //DDC_MASTER_MODE_E   enMasterMode;       /* AON MODE ONLY FOR DEBUG */
    //HI_U16              u16Speed;           //TO DO

    //HI_U16              u16AccessTimeOut;
    //HI_U16              u16HpdTimeOut;
    HI_U16              u16InProgTimeOut;
    HI_U16              u16SclTimeOut;
    HI_U16              u16SdaTimeOut;
    HI_U16              u16IssueTimeOut;

    HI_U8               u8DataSize;
    HI_U8               *pu8Data;
}DDC_CFG_S;

#if 0
typedef struct
{
	HI_BOOL				bInit;				/* is the DDC init */

}DDC_RUN_S;
#endif

typedef struct
{
    HI_BOOL				bInit;
    DDC_ERR_U           unErr;
    DDC_CFG_S           stCfg;
    //HI_U8               u8DataSize;
    //HI_U8               *pu8Data;
    HI_U8               u8ExtEdidCnt;
    HI_U8               u8EdidRdStatus;
}DDC_INFO_S;

#if 0
typedef struct
{
    DDC_RUN_S           stDdcRun;                   /* DDC running control info */
    DDC_RECORD_ELEM_S   stDdcElem;
}DDC_INFO_S;
#endif

/**
\brief	  DDC init
\param    none
\retval   none
*/
HI_S16 MCU_HDMI_DdcInit(HI_VOID);

/**
\brief	  DDC deinit
\param    none
\retval   none
*/
HI_S16 MCU_HDMI_DdcDeInit(HI_VOID);

/**
\brief	  DDC error clear
\param    none
\retval   none
*/
HI_S16 MCU_HDMI_DdcErrClear(HI_VOID);

/**
\brief	  DDC issue (read & write)
\param[in]    @pstCfg       Issue config
\retval   HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_DdcIssue(DDC_CFG_S *pstCfg);

/**
\brief	  DDC default issue config get
\param[out]    @pstCfg       default issue config
\retval   HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_DdcDefaultCfgGet(DDC_CFG_S *pstCfg);

/**
\brief	  Get edid & parse cec_phy_addr
\param[out]	@pu8CecPhyAddr          pointer to the cec_phy_addr memery
\param[in]	@u8Size 			    cec_phy_addr size,in Bytes
\retval  HI_SUCCESS;HI_FAILURE
*/
HI_S16 MCU_HDMI_DdcEdidCecAddrGet(HI_U8 *pu8CecPhyAddr, HI_U8 u8Size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __HDMI_MCU_DDC_EDID_H__ */

