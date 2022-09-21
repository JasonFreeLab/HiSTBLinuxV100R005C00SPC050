
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_window.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_WINDOW_H__
#define __DRV_WINDOW_H__

#include "hi_type.h"
#include "hi_common.h"
#include "hi_drv_video.h"
#include "hi_drv_stat.h"
#include "hi_drv_win.h"
#include "drv_win_hal.h"
#include "drv_win_prc.h"


#ifdef HI_VO_WIN_SYNC_SUPPORT
#include "drv_sync.h"
#endif

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

typedef enum hiDRV_STILL_FRAME_TYPE_E
{
    HI_DRV_FRAME_NORMAL = 0,
    HI_DRV_FRAME_VDP_ALLOCATE_STILL,
    HI_DRV_FRAME_SWITCH_PROGRAM_STILL,
    HI_DRV_FRAME_BUTT
}HI_DRV_STILL_FRAME_TYPE_E;


/******************************************************************************
    local function and macro
******************************************************************************/

#define FIDELITY_033            1
#define FIDELITY_18             2
#define FIDELITY_576I_YPBPR     3
#define FIDELITY_576P_YPBPR     3
#define FIDELITY_480I_YPBPR     4
#define FIDELITY_480P_YPBPR     4
#define FIDELITY_720P_YPBPR     5
#define FIDELITY_1080I_P_YPBPR  7
#define FIDELITY_CBAR_75        8
#define FIDELITY_MX625          10
#define FIDELITY_BOWTIE         18
#define FIDELITY_SKN            20
#define FIDELITY_ZDN            22
#define FIDELITY_MATRIX525      23
#define FIDELITY_MOTO_CVBS      25
#define FIDELITY_MOTO_75_COLORBARS      32
#define FIDELITY_MOTO_COMBINATION       33
#define FIDELITY_MOTO_CVBS_MATRIX       36

#define VIDEO_TEST_SATURATION_OFFSET   (3)
#define VIDEO_TEST_SATURATION_OFFSET_DEC   (2)


#define WinGetType(pstWin)    (pstWin->enType)
#define WinGetLayerID(pstWin) (pstWin->eLayer)
#define WinGetDispID(pstWin)  (pstWin->enDisp)
#define WinCheckDeviceOpen()    \
{                                \
    if (WIN_DEVICE_STATE_OPEN != s_s32WindowGlobalFlag)  \
    {                            \
        WIN_ERROR("WIN is not inited or suspended in %s!\n", __FUNCTION__); \
        return HI_ERR_VO_NO_INIT;  \
    }                             \
}

#define WinCheckNullPointer(ptr) \
{                                \
    if (!ptr)                    \
    {                            \
        WIN_ERROR("WIN Input null pointer in %s!\n", __FUNCTION__); \
        return HI_ERR_VO_NULL_PTR;  \
    }                             \
}

#define WinCheckWindow(hWin, pstWin) \
{                                    \
    pstWin = WinGetWindow(hWin);     \
    if (!pstWin)                      \
    {                                \
        WIN_WARN("WIN is not exist! %#x\n", hWin); \
        return HI_ERR_VO_WIN_NOT_EXIST; \
    }  \
}

#define WinCheckSlaveWindow(pstWin) \
{                                   \
    if (HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE == WinGetType(pstWin)) \
    {                               \
        if (!pstWin->hSlvWin)        \
        {                           \
            WIN_ERROR("WIN Slave window is lost in %s\n", __FUNCTION__); \
            return HI_ERR_VO_SLAVE_WIN_LOST;    \
        }                           \
    }                               \
}

typedef enum {
    VDP_MCE_STAGE = 0, /*mce stage*/
    VDP_NORMAL_STAGE,  /*kernel has boot already.*/
}VDP_MCE_STAGE_E;
HI_S32 DRV_WIN_GetSftwareStage(HI_VOID);

#define WINDOW_INVALID_ID 0xFFFFFFFFul

#define WINDOW_INDEX_MASK        0x00000FFFl
#define WINDOW_INDEX_NUMBER_MASK 0x000000FFl

HI_S32 WIN_Init(HI_VOID);
HI_S32 WIN_DeInit(HI_VOID);
HI_S32 WIN_Suspend(HI_VOID);
HI_S32 WIN_Resume(HI_VOID);

//HI_S32 WIN_SetMode(HI_DRV_VO_MODE_E enDevMode);
//HI_S32 WIN_GetMode(HI_DRV_VO_MODE_E *enDevMode);

HI_S32 WIN_Create_MCE(HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWin,HI_BOOL bVirtScreen);
HI_S32 WIN_Create(HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWin,HI_BOOL bVirtScreen);
HI_S32 WIN_Destroy(HI_HANDLE hWin);
HI_S32 WIN_CheckAttachState(HI_HANDLE hWin,HI_BOOL *pbSrcAttached,HI_BOOL *pbSinkAttached);

HI_S32 WIN_SetAttr(HI_HANDLE hWin, HI_DRV_WIN_ATTR_S *pWinAttr);
HI_S32 WIN_GetAttr(HI_HANDLE hWin, HI_DRV_WIN_ATTR_S *pWinAttr);

//get info for source
HI_S32 WIN_GetInfo(HI_HANDLE hWin, HI_DRV_WIN_INFO_S * pstInfo);

HI_S32 WIN_SetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc);
HI_S32 WIN_GetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc);

HI_S32 WIN_SetEnable(HI_HANDLE hWin, HI_BOOL bEnable);
HI_S32 WIN_GetEnable(HI_HANDLE hWin, HI_BOOL *pbEnable);

HI_S32 WIN_QueueFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo, HI_DRV_DOLBY_META_INFO_S *pstDolbyMdInfo);
HI_S32 WIN_QueueSyncFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo, HI_U32 *pu32FenceFd);
HI_S32 WIN_QueueUselessFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo);
HI_S32 WIN_DequeueFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo);


HI_S32 WIN_GetPlayInfo(HI_HANDLE hWin, HI_DRV_WIN_PLAY_INFO_S *pstInfo);

HI_S32 WIN_SetZorder(HI_HANDLE hWin, HI_DRV_DISP_ZORDER_E enZFlag);
HI_S32 WIN_GetZorder(HI_HANDLE hWin, HI_U32 *pu32Zorder);

HI_S32 WIN_Freeze(HI_HANDLE hWin, HI_BOOL bEnable,  HI_DRV_WIN_SWITCH_E eRst);
HI_S32 WIN_GetFreezeStatus(HI_HANDLE hWin, HI_BOOL *pbEnable, HI_DRV_WIN_SWITCH_E *penFrz);

HI_S32 WIN_Reset(HI_HANDLE hWin, HI_DRV_WIN_SWITCH_E eRst);

HI_S32 WIN_Pause(HI_HANDLE hWin, HI_BOOL bEnable);

HI_S32 WIN_SetStepMode(HI_HANDLE hWin, HI_BOOL bStepMode);
HI_S32 WIN_SetStepPlay(HI_HANDLE hWin);

/* only for virtual window */
HI_S32 WIN_SetExtBuffer(HI_HANDLE hWin, HI_DRV_VIDEO_BUFFER_POOL_S* pstBuf);
HI_S32 WIN_AcquireFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo);
HI_S32 WIN_ReleaseFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo);
HI_S32 WIN_AttachSink(HI_HANDLE hWin, HI_HANDLE hSink);
HI_S32 WIN_DetachSink(HI_HANDLE hWin, HI_HANDLE hSink);
HI_S32 WIN_SetVirtualAttr(HI_HANDLE hWin, HI_U32 u32Width,HI_U32 u32Height,HI_U32 u32FrmRate);

HI_S32 WIN_SetQuick(HI_HANDLE hWin, HI_BOOL bEnable);
HI_S32 WIN_GetQuick(HI_HANDLE hWin, HI_BOOL *pbEnable);

HI_S32 WIN_CapturePicture(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstPic);
HI_S32 WIN_CapturePictureRelease(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstPic);

HI_S32 WIN_SetRotation(HI_HANDLE hWin, HI_DRV_ROT_ANGLE_E enRotation);
HI_S32 WIN_GetRotation(HI_HANDLE hWin, HI_DRV_ROT_ANGLE_E *penRotation);

HI_S32 WIN_SetFlip(HI_HANDLE hWin, HI_BOOL bHoriFlip, HI_BOOL bVertFlip);
HI_S32 WIN_GetFlip(HI_HANDLE hWin, HI_BOOL *pbHoriFlip, HI_BOOL *pbVertFlip);

HI_S32 WIN_GetUnload(HI_HANDLE hWin, HI_U32 *pu32Times);
HI_S32 WIN_SetWindowAlpha(HI_HANDLE hWin, HI_U32 u32Alpha);
HI_S32 WIN_GetWindowAlpha(HI_HANDLE hWin, HI_U32 *pu32Alpha);

HI_S32 WIN_SendFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo);
HI_S32 WIN_DestroyStillFrame(HI_DRV_VIDEO_FRAME_S *pStillFrameinfo);
HI_U32 WinGetIndex(HI_HANDLE hWin, HI_DRV_DISPLAY_E *enDisp, HI_U32 *u32WinIndex);
HI_S32 WinForceClearCapture(HI_HANDLE hWin);
HI_S32 WIN_Test(HI_HANDLE hWin);
HI_BOOL WinCheckWhetherCanToCreate(HI_HANDLE hWin);
HI_BOOL WinCheckWhetherCanToDestroy(HI_HANDLE hWin);
HI_BOOL WinCheckProcCanBeRemoved(HI_HANDLE hWin);

HI_S32 WIN_SetFrostMode(HI_HANDLE hWin, HI_DRV_WINDOW_FROST_E eWinFrostMode);
HI_S32 WIN_GetFrostMode(HI_HANDLE hWin, HI_DRV_WINDOW_FROST_E *peWinFrostMode);

HI_VOID Win_UpdateVideoLayerSetting(HI_DRV_DISPLAY_E enDstDisp,
                                    const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo);

typedef struct tagWIN_HANDLE_ARRAY_S
{
    HI_U32 u32WinNumber;
    HI_HANDLE ahWinHandle[DEF_MAX_WIN_NUM_ON_SINGLE_DISP];
}WIN_HANDLE_ARRAY_S;

HI_S32 Win_DebugGetHandle(HI_DRV_DISPLAY_E enDisp, WIN_HANDLE_ARRAY_S *pstWin);


HI_U32 WinGetPrefix(HI_U32 u32WinIndex);
HI_U32 WinGetDispId(HI_U32 u32WinIndex);
HI_U32 WinGetId(HI_U32 u32WinIndex);


#define WIN_PROC_BUFFER_MAX_NUMBER 32
#define WIN_PROC_DEBUG_FRAME_RECORD_NUMBER 32

typedef struct tagWIN_DEBUG_USER_INFO_S
{
    HI_RECT_S stVirInRect;
    HI_RECT_S stVirOutRect;


   // HI_DRV_DISP_OFFSET_S stDispOffset;
    HI_U32 u32OffsetLeft;
   HI_U32 u32OffsetRight;
   HI_U32 u32OffsetTop;
   HI_U32 u32OffsetButtom;
    HI_RECT_S stRevisedAttrOutRect;

    HI_RECT_S stPhyInRect;
    HI_RECT_S stPhyOutRect;

}WIN_DEBUG_USER_INFO_S;

typedef struct tagWIN_DEBUG_HAL_INFO_S
{
    HI_RECT_S stSrcRect;
    HI_RECT_S stIn;
    HI_RECT_S stVideo;
    HI_RECT_S stDisp;
}WIN_DEBUG_HAL_INFO_S;

typedef struct tagWIN_DEBUG_LOGIC_INFO_S
{
    HI_RECT_S stInRect;
    HI_RECT_S stOutRect;
}WIN_DEBUG_LOGIC_INFO_S;

typedef struct tagWIN_DEBUG_FRC_INFO_S
{
    HI_BOOL  bDisable;
    HI_U32 u32InRota;
    HI_U32 u32OutRota;
    HI_U32 u32Count;
} WIN_DEBUG_FRC_INFO_S;

typedef struct tagWIN_DEBUG_INFO_S
{
    WIN_DEBUG_FRC_INFO_S stFRC;
    WIN_DEBUG_USER_INFO_S stWinUseInfo;
    WIN_DEBUG_HAL_INFO_S stWinHalInfo;
    WIN_DEBUG_LOGIC_INFO_S stWinLogicInfo;
} WIN_DEBUG_INFO_S;


typedef struct tagWIN_PROC_INFO_S
{
    HI_DRV_WIN_TYPE_E enType;
    HI_U32  u32Index;
    HI_U32  u32Zorder;
    HI_U32  u32LayerId;
    HI_U32  u32LayerRegionNo;

    HI_BOOL bEnable;
    HI_BOOL bMasked;
    HI_U32  u32WinState;

    HI_BOOL bReset;
    HI_DRV_WIN_SWITCH_E enResetMode;
    HI_DRV_WIN_SWITCH_E enFreezeMode;

    HI_BOOL bQuickMode;
    HI_BOOL bStepMode;
    HI_BOOL bVirtualCoordinate;

    /* not change when window lives */
    /* source info */
    HI_U32 hSrc;
    HI_U32 hSecondSrc;//for Dolby dual process.
    HI_VOID* pfAcqFrame;
    HI_VOID* pfRlsFrame;
    HI_VOID* pfSendWinInfo;

    /* attribute */
    //HI_DISP_DISPLAY_INFO_S stRefDispInfo;
    HI_DRV_WIN_ATTR_S stAttr;
    HI_DRV_DISP_STEREO_E eDispMode;
    HI_BOOL bRightEyeFirst;
	HI_U32 u32Alpha;

    /* slave window for HD&SD display the same content at the same time */
    HI_HANDLE hSlvWin;

    /* debug info */
    HI_BOOL bDebugEn;
    HI_U32 u32TBNotMatchCount;

    /* statistic info */
    HI_U32 u32ULSIn;
    HI_U32 u32ULSOut;
    HI_U32 u32UnderLoad;

    /*  buffer state */
    WB_STATE_S stBufState;
    HI_DRV_WIN_DATA_FLOW_E eDataFlowPath;

    HI_DRV_LOWDELAY_STAT_INFO_S stLowdelayStat;
    /*only for developer or mainteiner.*/
    HI_WIN_RROC_FOR_DEVELOPER_S stWinInfoForDeveloper;

	ISOGBNY_PROC_INFO_S stIsogenyProcInfo;

    /* window mode:SDR normal mode or HDR Dolby mode */
    HI_DRV_WINDOW_MODE_E    enWinMode;
    WIN_DEBUG_INFO_S stWinDebugInfo;
}WIN_PROC_INFO_S;

HI_VOID Win_UpWinPosionDebugInfo(HI_VOID *pstWin,WIN_HAL_PARA_S *pstLayerPara);
HI_BOOL WinCheckHDIs3DMode(HI_DRV_DISPLAY_E enDisp);

HI_S32 WinGetProcIndex(HI_HANDLE hWin, HI_U32 *p32Index);
HI_S32 WinGetProcInfo(HI_HANDLE hWin, WIN_PROC_INFO_S *pstInfo);

HI_S32 WinGetCurrentImg(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstFrame);
HI_S32 WinCaptureFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstFrame, HI_U32 *stMMZPhyAddr, HI_U32 *stMMZlen);
HI_S32 WinReleaseCaptureFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstFrame);
HI_S32 WinFreeCaptureMMZBuf(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *cap_frame);
HI_S32 WinCapturePause(HI_HANDLE hWin, HI_BOOL bCaptureStart);
HI_S32 DestroyStillFrame(HI_DRV_VIDEO_FRAME_S *pStillFrameInfo);

HI_S32 WinDebugCmdProcess(WIN_DEBUG_CMD_AND_ARGS_S *pstDebugCmd);

HI_S32 WinParamAlignUp(HI_S32 s32X, HI_U32 u32Align);
HI_S32 WinParamAlignDown(HI_S32 s32X, HI_U32 u32Align);
HI_U32 WinGetHDWinNum(HI_VOID);
HI_S32 WinStatisticLowdelayTimeInfor(HI_HANDLE hWin,
                                     HI_DRV_VIDEO_FRAME_S *pFrameInfo,
                                     HI_LD_Event_ID_E eLDEventId);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /*  __DRV_WINDOW_H__  */

