/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_dispctrl.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2016-11-2
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_DRV_DISPCTRL_H__
#define __TEE_DRV_DISPCTRL_H__

#define HI_LOG_D_MODULE_ID     HI_MODULE_ID_DISPCTRL
#define HI_LOG_D_FUNCTRACE     (0)

#include "hi_tee_debug.h"
#include "tee_os_hal.h"
#include "tee_drv_dispctrl_ext.h"
#include "uuid_chip.h"

#define DISPCTRL_MAX_INSTANCE                 16     /* DISPCTRL 最大实例数*/

#define DISPCTRL_MAX_HDCP_NUMBER              3
#define DISPCTRL_MAX_FMAT_NUMBER              4

#define HI_TEE_DISPCTRL_ID                    0x1f   /* 自定义DISPCTRL句柄头用于校验句柄*/


/* stream info*/
typedef struct
{
    HI_HANDLE                       VfmwHandle;
    TEE_DRV_DISPCTRL_FRAME_INFO_S   FrameInfo;

}DISPCTRL_STREAM_INFO_S;

/* HDCP Digital Config */
typedef struct
{
    HI_HANDLE                      StreamHandle;
    HI_U32                         u32HdcpLevelMax;
    HI_U32                         u32ResolutionMax;
    HI_TEE_DISPCTRL_HDCP_LEVEL_E      enHdcpReq;
    HI_TEE_DISPCTRL_DIGITAL_ACTION_E  enDigOutAction[DISPCTRL_MAX_HDCP_NUMBER][DISPCTRL_MAX_FMAT_NUMBER];

}DISPCTRL_HDCP_DIGITAL_CONFIG_S;

/*analogoutput Config*/
typedef struct
{
    HI_TEE_DISPCTRL_CGMS_CFG_S                CgmsState;
    HI_TEE_DISPCTRL_MACROVISION_MODE_E        MacroVisionState;
    HI_TEE_DISPCTRL_ANALOGOUTPUT_PARAMETER_S  AnalogoutMute;
}DISPCTRL_ANALOGOUT_CONFIG_S;

typedef struct
{
    HI_HANDLE                       DispctrlHandle;
    TEE_UUID                        UserUUID;
    DISPCTRL_HDCP_DIGITAL_CONFIG_S  HdcpDigitalConfig;
    DISPCTRL_STREAM_INFO_S          StreamInfo;
    DISPCTRL_ANALOGOUT_CONFIG_S     AnalogoutConfig;
}DISPCTRL_S;

typedef struct
{
    HI_U32                          ContentStreamType;     /*used for repeater*/
    HI_U32                          DownScalWidth;
    HI_U32                          DownScalHight;
}DISPCTRL_MONITOR_S;

/*Define video resolution type*/
typedef enum
{
    DISPCTRL_RES_SD = 0,          /*SD(480 or 576)*/
    DISPCTRL_RES_HD,              /*HD (720)*/
    DISPCTRL_RES_FHD,             /*FHD (1080)*/
    DISPCTRL_RES_UHD,             /*UHD (4K)*/
    DISPCTRL_RES_BUTT,
}DISPCTRL_RES_E;

#endif


