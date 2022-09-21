/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_win_share.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017-05-12
  Description   : this file keeps win and disp shared structures and functions.
  History       :
  1.Date        : 2017-05-12
    Author      : q00293180
    Modification: Created file
*******************************************************************************/
#ifndef __DRV_WIN_SHARE_H__
#define __DRV_WIN_SHARE_H__

#include "drv_win_common.h"
#include "hi_type.h"
#include "hi_drv_video.h"
#include "hi_drv_disp.h"
#include "drv_disp_osal.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

#define INVALID_WIN_INDEX  0xFFFF


/****************************************************************************
Structures
*****************************************************************************/
/* NOTE: struct belowed amid to fix boot compile issue. */
typedef enum hiWINDOW_FROST_E
{
    WINDOW_FROST_CLOSE = 0x0 ,       /**<Close  */ /**<CNcomment:¹Ø±Õ CNend*/
    WINDOW_FROST_LOW         ,       /**<Low    */ /**<CNcomment:Èõ   CNend*/
    WINDOW_FROST_MIDDLE      ,       /**<Middle */ /**<CNcomment:ÖÐ   CNend*/
    WINDOW_FROST_HIGH        ,       /**<High   */ /**<CNcomment:Ç¿   CNend*/

    WINDOW_FROST_BUTT
}WINDOW_FROST_E;


typedef struct tagWIN_INFO_S
{
    //=========window=================
    HI_HANDLE              hWinHandle;         /* handle of window  */
    HI_BOOL                bWinEnable;         /* window status.    */
    HI_BOOL                bCloseHdr;         /* whether to close win's hdr function,just for show. */
    HI_U32                 u32Alpha;
	HI_U32                 u32AllAlpha;

    //=========layer ==================
    HI_U32                 u32LayerId;         /* window layer id.  */
    HI_U32                 u32RegionNo;
    HI_BOOL                bRegionEnable;
    HI_BOOL                bRegionMute;
    HI_BOOL                bFlipEn;
    HI_BOOL                bTnrOnVdp;
    DISP_MMZ_BUF_S         stLayerAlgMmz;
    HI_RECT_S              stIn;

    //=========buffer==================
    HI_DRV_COLOR_SPACE_E   enInCsc;            /* input color space*/
    HI_DRV_VIDEO_FRAME_S   *pCurrentFrame;
    HI_DRV_VIDEO_FRAME_S   *pNextFrame;

    //=========display=================
    HI_DRV_COLOR_SPACE_E   enOutCsc;           /* output color space */
    HI_DRV_DISP_OUT_TYPE_E enOutType;
    HI_DISP_DISPLAY_INFO_S *pstDispInfo;
    HI_RECT_S              stDisp;
    HI_RECT_S              stVideo;

    //=========extern use. such as pq=======
    HI_BOOL                bHdcpDegradePQ;
    HI_RECT_S              stHdcpIntermediateRect;
    WINDOW_FROST_E         enLayerFrostMode;

}WIN_INFO_S;


typedef struct tagWIN_SHARE_INFO_S
{
    HI_U32       u32HdWinNum;                  /* record all HD win num. */
    WIN_INFO_S   stWinInfo[WINDOW_MAX_NUMBER];

}WIN_SHARE_INFO_S;

//--------unify metadata---------
typedef enum tagWIN_FRAME_EOTF_E
{
    WIN_FRAME_EOTF_1886 = 0x0,
    WIN_FRAME_EOTF_2084 ,
    WIN_FRAME_EOTF_HLG ,
    WIN_FRAME_EOTF_SLF ,

    WIN_FRAME_EOTF_BUTT
}WIN_FRAME_EOTF_E;

typedef enum hiWIN_FRAME_MATRIX_COEFF_E
{
    WIN_FRAME_MATRIX_COEFF_BT601_L = 0x0,
    WIN_FRAME_MATRIX_COEFF_BT601_F,
    WIN_FRAME_MATRIX_COEFF_BT709_L,
    WIN_FRAME_MATRIX_COEFF_BT709_F,
    WIN_FRAME_MATRIX_COEFF_BT2020_NCL,
    WIN_FRAME_MATRIX_COEFF_BT2020_CL,
    WIN_FRAME_MATRIX_COEFF_UNKNOW,

    WIN_FRAME_MATRIX_COEFF_BT2020_BUTT

}WIN_FRAME_MATRIX_COEFF_E;

#ifndef __DISP_PLATFORM_BOOT__
typedef struct tagWIN_SHARE_UNIFIED_METADATA_IN_S
{
    HI_DRV_VIDEO_FRAME_TYPE_E        enSrcFrameType;
    HI_DRV_COLOUR_DESCRIPTION_INFO_S stColorDescriptionInfo;
    HI_U8 u8TransferCharacteristics;

    HI_BOOL  bMasteringAvailable;
    HI_BOOL  bContentAvailable;
    HI_DRV_MASTERING_DISPLAY_COLOUR_VOLUME_S stMasteringInfo;
    HI_DRV_CONTENT_LIGHT_LEVEL_INFO_S        stContentInfo;
}WIN_SHARE_UNIFIED_METADATA_IN_S;

typedef struct tagWIN_SHARE_UNIFIED_METADATA_OUT_S
{
    HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType;
    HI_DRV_COLOR_SPACE_E      enFrmCS;       /* frame colorspace */

    WIN_FRAME_EOTF_E          enEotfType;
    WIN_FRAME_MATRIX_COEFF_E  enMatrixType;

    HI_BOOL  bMasteringAvailable;
    HI_BOOL  bContentAvailable;
    HI_DRV_MASTERING_DISPLAY_COLOUR_VOLUME_S stMasteringInfo;
    HI_DRV_CONTENT_LIGHT_LEVEL_INFO_S        stContentInfo;
}WIN_SHARE_UNIFIED_METADATA_OUT_S;
#endif

/****************************************************************************
Functions
*****************************************************************************/
HI_BOOL WIN_SHARE_HandleValid(HI_HANDLE hWinHandle);
HI_BOOL WIN_SHARE_FindTheValidWin(WIN_INFO_S *pstWinInfo,
                                            HI_U32      *pu32Index);

HI_VOID WIN_SHARE_ResetShareInfo(HI_VOID);
HI_VOID WIN_SHARE_SetWinInfo(WIN_INFO_S *pstWinInfo);


HI_VOID WIN_SHARE_GetShareInfo(WIN_SHARE_INFO_S *pstWinShareInfo);
HI_VOID WIN_SHARE_GetFrameColorSpace(HI_DRV_VIDEO_FRAME_S *pstFrame, HI_DRV_COLOR_SPACE_E *penColorSpace);

#ifndef __DISP_PLATFORM_BOOT__
HI_S32  WIN_SHARE_GetUnifiedMetadata(WIN_SHARE_UNIFIED_METADATA_IN_S *pstMdInfoIn,
                                               HI_DRV_VIDEO_STD_E  enVideoStd,
                                               WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut);
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /*  __DRV_WIN_SHARE_H__  */


