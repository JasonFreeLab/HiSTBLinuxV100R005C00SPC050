/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_disp_xdr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017-05-12
  Description   :process sdr/hdr source
  History       :
  1.Date        : 2017-05-12
    Author      : q00293180
    Modification: Created file
*******************************************************************************/

#ifndef __DRV_DISP_XDR_H__
#define __DRV_DISP_XDR_H__

#include "hi_type.h"
#include "drv_win_share.h"
#ifndef __DISP_PLATFORM_BOOT__
#include "hi_drv_hdmi.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef __DISP_PLATFORM_BOOT__

/*****************************************************************************/
//HLG source in HDR10 out infoFrame metadata
#define HLG_TO_HDR10_PRIMARIES0_X                  13250
#define HLG_TO_HDR10_PRIMARIES0_Y                  34500
#define HLG_TO_HDR10_PRIMARIES1_X                  7500
#define HLG_TO_HDR10_PRIMARIES1_Y                  3000
#define HLG_TO_HDR10_PRIMARIES2_X                  34000
#define HLG_TO_HDR10_PRIMARIES2_Y                  16000
#define HLG_TO_HDR10_WHITE_POINT_X                 15635
#define HLG_TO_HDR10_WHITE_POINT_Y                 16450
#define HLG_TO_HDR10_DISP_MASTER_LUMINANCE_MAX     1000
#define HLG_TO_HDR10_DISP_MASTER_LUMINANCE_MIN     200
#define HLG_TO_HDR10_CONTENT_LIGHT_LEVEL_MAX       1000
#define HLG_TO_HDR10_FRAME_AVERAGE_LIGHT_MAX         250


/*****************************************************************************/
typedef enum tagDISP_XDR_WORK_MODE_E
{
    XDR_WORK_MODE_HISI = 0x0,
    XDR_WORK_MODE_DOLBY,
    XDR_WORK_MODE_BUTT
}DISP_XDR_WORK_MODE_E;

typedef struct tagDISP_XDR_PROC_INFO_S
{
    HI_U32                  u32HdWinNum;
    DISP_XDR_WORK_MODE_E    enWorkMode;
    WIN_INFO_S              stWinInfo[WINDOW_MAX_NUMBER];
}DISP_XDR_PROC_INFO_S;

typedef struct tagDISP_XDR_PLAY_INFO_S
{
    DISP_XDR_WORK_MODE_E          enPreWorkMode;//previous.last
    HI_DRV_HDMI_HDR_ATTR_S        stPreHdmiHdrAttr;//previous.last
}DISP_XDR_PLAY_INFO_S;


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

