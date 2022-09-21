/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_disp_dolby.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017-06-08
  Description   :structures define and functions declaration for processing Dolby HDR.
  History       :
  1.Date        : 2017-06-08
    Author      : sdk
    Modification: Created file
*******************************************************************************/

#ifndef __DRV_DISP_DOLBY_H__
#define __DRV_DISP_DOLBY_H__

#include "hi_type.h"

#ifndef __DISP_PLATFORM_BOOT__
#include "hi_drv_hdmi.h"
#include "drv_pq_ext.h"

#include "drv_win_share.h"

#include "vdp_define.h"
#include "vdp_ip_define.h"
#include "vdp_fpga_define.h"
#include "vdp_hal_intf.h"
#include "KdmTypeFxp.h"

#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

//switcher composer mode define
#define DISABLE_EL_FLAG_OFF  0
#define DISABLE_EL_FLAG_ON   1

//update metadata buffer length
#define MAX_MD_BUF_LEN  255 //255 Bytes.

//metadata info send over HDMI
#define HEADER_MD_VER   0b000
#define HEADER_MD_TYPE  0b00

//DolbyVision source in HDR10 out infoFrame metadata
#define HDR10_METADATA_R_X                  0x8A48              //0.708/0.00002 = 35400
#define HDR10_METADATA_R_Y                  0x3908              //0.292/0.00002 = 14600
#define HDR10_METADATA_G_X                  0x2134              //0.170/0.00002 = 8500
#define HDR10_METADATA_G_Y                  0x9BAA              //0.797/0.00002 = 39850
#define HDR10_METADATA_B_X                  0x1996              //0.131/0.00002 = 6550
#define HDR10_METADATA_B_Y                  0x8FC               //0.046/0.00002 = 2300
#define HDR10_METADATA_WP_X                 0x3D13              //0.3127/0.00002 = 15635
#define HDR10_METADATA_WP_Y                 0x4042              //0.3290/0.00002 = 16450
#define HDR10_METADATA_DISP_MASTER_MAX      0x3E8               //1000nits
#define HDR10_METADATA_DISP_MASTER_MIN      0x5                 //0.005nits
#define HDR10_METADATA_CLL_MAX              0x0
#define HDR10_METADATA_FALL_MAX             0x0


//******************************NEW STUCTURE CODE******************************
typedef struct hiDOLBY_MD_HEADER_S
{
    HI_BOOL     bNoMd;      /* indicates that no Dolby Vision metadata is contained in the current Dolby Vision video frame transmission */
    HI_BOOL     bEos;       /* indicates that the immediate next video frame contains a signal that is not a Dolby Vision signal */
    HI_U8       u8MdVer;    /* metadata_version = 0b000: Current version */
    HI_U8       u8MdType;   /* metadata_type = 0b00: Dolby Vision metadata */
    HI_U32      u32MdId;    /* first byte of dm_metadata_base_t,indicates the ID number of the Dolby Vision video frame */
}DOLBY_MD_HEADER_S;

typedef struct hiDRV_DISP_DOLBY_COEFF_S
{
    rpu_ext_config_fixpt_main_t   stCompCfg;
    dm_metadata_t                 stDmCfg;
    DmKsFxp_t                     stDmKs;
    hdr_10_infoframe_t            stHdr10InfoFrm;
    HI_U8                         u8MdBuf[MAX_MD_BUF_LEN];    /* store update metadata that config in this interrupt.*/
    HI_U32                        u32UpMdLen;                 /* the length of update metadata */
}DRV_DISP_DOLBY_COEFF_S;

typedef struct hiDRV_DISP_DOLBY_PLAY_INFO_S
{
    HI_BOOL                       bELVaild;
    DRV_DISP_DOLBY_COEFF_S        stDolbyCoeff;
}DRV_DISP_DOLBY_PLAY_INFO_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

