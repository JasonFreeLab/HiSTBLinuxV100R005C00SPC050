/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_win.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2012/09/20
  Description   :
  History       :
  1.Date        :
  Author        :
  Modification  : Created file

*******************************************************************************/

#include <linux/vmalloc.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/slab.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
#include <linux/smp_lock.h>
#endif
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0))
#include <asm/system.h>
#endif
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>

#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_kernel_adapt.h"

#include "hi_drv_module.h"

#include "hi_drv_disp.h"
#include "drv_disp.h"
#include "drv_display.h"
#include "drv_disp_debug.h"
#include "drv_disp_ext.h"
#include "drv_disp_osal.h"
#include "drv_disp_debug.h"

#include "hi_drv_win.h"
#include "drv_win_ext.h"
#include "drv_vdec_ext.h"
#include "drv_vi_ext.h"
#include "drv_win_ioctl.h"
#include "drv_window.h"
#include "hi_osal.h"
#include "drv_win_hal.h"

#include "drv_win_hdr.h"
#include "drv_win_priv.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static atomic_t    g_VoCount = ATOMIC_INIT(0);
//WIN_GLOBAL_STATE_S   g_VoGlobalState;
WIN_STATE_S          g_VoModState;
HI_BOOL     g_VoSuspend = HI_FALSE;
HI_U32  g_bWinPrivateInformation = HI_FALSE;

typedef struct tagWIN_PROC_COMMAND
{
    const HI_CHAR *command_name;
    HI_S32 (*PF_DebugFun)(HI_HANDLE hWin, HI_CHAR *pArg2);
} WIN_PROC_COMMAND;

HI_DECLARE_MUTEX(g_VoMutex);

HI_U8 *g_pWinDataFlowPath[HI_DATA_FLOW_BUTT] =
{
    "queue+dequeue",
    "queue+isr_release",
    "queue+fence",
};

HI_U8 *g_pWinModeString[HI_DRV_WINDOW_MODE_BUTT] =
{
    "NormalMode",
    "DolbyMode",
    "HdrMode",
};

HI_U8 *g_pWinFrmBitWidthString[HI_DRV_PIXEL_BITWIDTH_BUTT] =
{
    "8-bit",
    "10-bit",
    "12-bit",
};

HI_U8 *g_pAlgLocation[2] =
{
    "In V0",
    "In VP",
};

HI_U8 *g_pWinTrueString[2] =
{
    "False",
    "True ",
};

HI_U8 *g_pWinYNString[2] =
{
    "N",
    "Y",
};

HI_U8 *g_pWinEnableString[2] =
{
    "Disable",
    "Enable ",
};
HI_U8 *g_pWinRotateString[5] =
{
    "Rotation_00",
    "Rotation_90 ",
    "Rotation_180 ",
    "Rotation_270 ",
    "Rotation_butt ",
};
//WIN_PROC_INFO_S s_stProcInfo;
//static HI_U32 s_WinProcId[HI_DRV_DISPLAY_BUTT][WINDOW_MAX_NUMBER]={WINDOW_INVALID_ID};
HI_U8 *g_pWinStateString[6] =
{
    "Run        ",
    "Pause      ",
    "Resume     ",
    "FreezeLast ",
    "FreezeBlack",
};

HI_U8 *g_pWinDispModeString[DISP_STEREO_BUTT] =
{
    "2D",
    "FPK",
    "SBS_HALF",
    "TAB",
    "FILED_ALTE",
    "LINE_ALTE",
    "SBS_FULL",
    "L_DEPTH",
    "LDEP_GDEP",
};

HI_U8 *g_pWinQucikString[2] =
{
    " ",
    "+QuickMode",
};

HI_U8 *g_pWinStepString[2] =
{
    " ",
    "+StepMode",
};


HI_U8 *g_pWinFreezeString[2] = {"LAST", "BLACK"};

HI_U8 *g_pWinTpyeString[HI_DRV_WIN_BUTT] =
{
    "Display",
    "Virtual",
    "Main   ",
    "Slave  ",
};

HI_U8 *g_pWinAspectCvrsString[HI_DRV_ASP_RAT_MODE_BUTT] =
{
    "Full      ",
    "LetterBox ",
    "PanAndScan",
    "Combined  ",
    "FullHori  ",
    "FullVert  ",
    "Customer  "
};

HI_U8 *g_pWinFrameTypetring[HI_DRV_FT_BUTT] =
{
    "2D",
    "SideBySid",
    "TopAndBottom",
    "MVC",
};

HI_U8 *g_pWinFieldModeString[HI_DRV_FIELD_BUTT] =
{
    "Top",
    "Bottom",
    "All",
};

HI_U8 *g_pWinMemTypeString[] =
{
    "WinSupply",
    "UserSupply",
};

HI_U8 *g_pWinFieldTypeString[HI_DRV_FIELD_BUTT + 1] =
{
    "Top",
    "Bottom",
    "Frame",
    "BUTT",
};

HI_U8 *g_pPixFmtString[] =
{
    "NV12       ",
    "NV21       ",
    "NV12CMP    ",
    "NV21CMP    ",
    "NV12TILE   ",
    "NV21TILE   ",
    "NV12TILECMP",
    "NV21TILECMP",
    "YUYV       ",
    "YYUV       ",
    "YVYU       ",
    "UYVY       ",
    "VYUY       ",
    "           ",
};

HI_U8 *g_pColorSpaceString[HI_DRV_CS_BUTT] =
{
    "HI_DRV_CS_UNKNOWN",
    "HI_DRV_CS_DEFAULT",

    "HI_DRV_CS_BT601_YUV_LIMITED",/* BT.601 */
    "HI_DRV_CS_BT601_YUV_FULL",
    "HI_DRV_CS_BT601_RGB_LIMITED",
    "HI_DRV_CS_BT601_RGB_FULL",

    "HI_DRV_CS_NTSC1953",

    /* These should be useful.  Assume 601 extents. */
    "HI_DRV_CS_BT470_SYSTEM_M",
    "HI_DRV_CS_BT470_SYSTEM_BG",

    "HI_DRV_CS_BT709_YUV_LIMITED",/* BT.709 */
    "HI_DRV_CS_BT709_YUV_FULL",
    "HI_DRV_CS_BT709_RGB_LIMITED",
    "HI_DRV_CS_BT709_RGB_FULL",
    "HI_DRV_CS_BT2020_YUV_LIMITED",/* ::::Current Used:::: BT.2020 */
    "HI_DRV_CS_BT2020_YUV_FULL",
    "HI_DRV_CS_BT2020_RGB_LIMITED",
    "HI_DRV_CS_BT2020_RGB_FULL",   /* ::::Current Used:::: */

    "HI_DRV_CS_REC709",      /* HD and modern captures. */

    "HI_DRV_CS_SMPT170M", /* ITU-R 601 -- broadcast NTSC/PAL */
    "HI_DRV_CS_SMPT240M", /* 1125-Line (US) HDTV */

    "HI_DRV_CS_BT878",    /* broken BT878 extents
                           (601, luma range 16-253 instead of 16-235) */

    "HI_DRV_CS_XVYCC",

    "HI_DRV_CS_JPEG",
};

HI_U8 *g_pGammaTypeString[HI_DRV_GAMMA_TYPE_BUTT] =
{
    "HI_DRV_GAMMA_TYPE_1886",
    "HI_DRV_GAMMA_TYPE_2084",
};

HI_U8 g_pPixFmtUnknown[20] = {0};


HI_U8 *g_pSourceString[] =
{
    "Unknown",
    "AVPlay ",
    "VI     ",
};

static HI_S32 WINProcessCmdCreate( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdDestroy( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetEnable( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetEnable( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdVirAcquire( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdVirRelease( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetAttr( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetAttr( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetZorder( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetOrder( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetSource( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetSource( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdFreeze( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetFreezeStatus( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSendFrame( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdQuFrame( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdQuDolbyFrame( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdQuSyncFrame( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdQuULSFrame( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdDqFrame( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdReset( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdPause( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetPlayInfo( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetInfo( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdStepMode( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdStepPlay( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdVirExternBuf( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetQuick( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetQuick( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSuspend( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdResum( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetHandle( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdAttach( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdDetach( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetLatestFrameInfo( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdCaptureStart( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdCaptureRelease( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdCaptureFree( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetRotation( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetRotation( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetFlip( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetFlip( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetFrostMode( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetFrostMode( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetMode( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetDispOutType( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetDispOutTypeAndGFXState( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetUnload( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdCloseHDRPath( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetDolbyLibStatus( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdDebug( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdSetAlpha( HI_VOID *arg, WIN_STATE_S *pstWinState);
static HI_S32 WINProcessCmdGetAlpha( HI_VOID *arg, WIN_STATE_S *pstWinState);

typedef struct WINProcessCmdFunc
{
    unsigned int cmd;
    HI_S32(*pWIN_ProcessCmdFunc)(HI_VOID *arg, WIN_STATE_S *pstWinState);
} stWINProcessCmdFunc;

static const stWINProcessCmdFunc s_aWINCmdFuncTab[] =
{
    {CMD_WIN_CREATE, WINProcessCmdCreate},
    {CMD_WIN_DESTROY, WINProcessCmdDestroy},
    {CMD_WIN_SET_ENABLE, WINProcessCmdSetEnable},
    {CMD_WIN_GET_ENABLE, WINProcessCmdGetEnable},
    {CMD_WIN_VIR_ACQUIRE, WINProcessCmdVirAcquire},
    {CMD_WIN_VIR_RELEASE, WINProcessCmdVirRelease},
    {CMD_WIN_SET_ATTR, WINProcessCmdSetAttr},
    {CMD_WIN_GET_ATTR, WINProcessCmdGetAttr},
    {CMD_WIN_SET_ZORDER, WINProcessCmdSetZorder},
    {CMD_WIN_GET_ORDER, WINProcessCmdGetOrder},
    {CMD_WIN_SET_SOURCE, WINProcessCmdSetSource},
    {CMD_WIN_GET_SOURCE, WINProcessCmdGetSource},
    {CMD_WIN_FREEZE, WINProcessCmdFreeze},
    {CMD_WIN_GET_FREEZE_STATUS, WINProcessCmdGetFreezeStatus},
    {CMD_WIN_SEND_FRAME, WINProcessCmdSendFrame},
    {CMD_WIN_QU_FRAME, WINProcessCmdQuFrame},
    {CMD_WIN_QUDOLBY_FRAME, WINProcessCmdQuDolbyFrame},
    {CMD_WIN_QUSYNC_FRAME, WINProcessCmdQuSyncFrame},
    {CMD_WIN_QU_ULSFRAME, WINProcessCmdQuULSFrame},
    {CMD_WIN_DQ_FRAME, WINProcessCmdDqFrame},
    {CMD_WIN_RESET, WINProcessCmdReset},
    {CMD_WIN_PAUSE, WINProcessCmdPause},
    {CMD_WIN_GET_PLAY_INFO, WINProcessCmdGetPlayInfo},
    {CMD_WIN_GET_INFO, WINProcessCmdGetInfo},
    {CMD_WIN_STEP_MODE, WINProcessCmdStepMode},
    {CMD_WIN_STEP_PLAY, WINProcessCmdStepPlay},
    {CMD_WIN_VIR_EXTERNBUF, WINProcessCmdVirExternBuf},
    {CMD_WIN_SET_QUICK, WINProcessCmdSetQuick},
    {CMD_WIN_GET_QUICK, WINProcessCmdGetQuick},
    {CMD_WIN_SUSPEND, WINProcessCmdSuspend},
    {CMD_WIN_RESUM, WINProcessCmdResum},
    {CMD_WIN_GET_HANDLE, WINProcessCmdGetHandle},
    {CMD_WIN_ATTACH, WINProcessCmdAttach},
    {CMD_WIN_DETACH, WINProcessCmdDetach},
    {CMD_WIN_GET_LATESTFRAME_INFO, WINProcessCmdGetLatestFrameInfo},
    {CMD_VO_WIN_CAPTURE_START, WINProcessCmdCaptureStart},
    {CMD_VO_WIN_CAPTURE_RELEASE, WINProcessCmdCaptureRelease},
    {CMD_VO_WIN_CAPTURE_FREE, WINProcessCmdCaptureFree},
    {CMD_WIN_SET_ROTATION, WINProcessCmdSetRotation},
    {CMD_WIN_GET_ROTATION, WINProcessCmdGetRotation},
    {CMD_WIN_SET_FLIP, WINProcessCmdSetFlip},
    {CMD_WIN_GET_FLIP, WINProcessCmdGetFlip},
    {CMD_WIN_SET_FROST_MODE, WINProcessCmdSetFrostMode},
    {CMD_WIN_GET_FROST_MODE, WINProcessCmdGetFrostMode},
    {CMD_WIN_SET_MODE, WINProcessCmdSetMode},
    {CMD_WIN_GET_DISP_OUT_TYPE, WINProcessCmdGetDispOutType},
    {CMD_WIN_GET_DISP_OUT_TYPE_AND_GFX_STATE, WINProcessCmdGetDispOutTypeAndGFXState},
    {CMD_WIN_GET_UNLOAD, WINProcessCmdGetUnload},
    {CMD_WIN_CLOSE_HDR_PATH, WINProcessCmdCloseHDRPath},
    {CMD_WIN_SET_DOLBY_LIB_STATUS, WINProcessCmdSetDolbyLibStatus},
    {CMD_WIN_DEBUG, WINProcessCmdDebug},
	{CMD_WIN_SET_ALPHA, WINProcessCmdSetAlpha},
	{CMD_WIN_GET_ALPHA, WINProcessCmdGetAlpha},
};

HI_U8 *DrvWinGetPixfmtString(HI_DRV_PIX_FORMAT_E enPixfmt)
{
    switch (enPixfmt)
    {
        case HI_DRV_PIX_FMT_NV12:
            return g_pPixFmtString[0];
        case HI_DRV_PIX_FMT_NV21:
            return g_pPixFmtString[1];
        case HI_DRV_PIX_FMT_NV12_CMP:
            return g_pPixFmtString[2];
        case HI_DRV_PIX_FMT_NV21_CMP:
            return g_pPixFmtString[3];
        case HI_DRV_PIX_FMT_NV12_TILE:
            return g_pPixFmtString[4];
        case HI_DRV_PIX_FMT_NV21_TILE:
            return g_pPixFmtString[5];
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
            return g_pPixFmtString[6];
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            return g_pPixFmtString[7];
        case HI_DRV_PIX_FMT_YUYV:
            return g_pPixFmtString[8];
        case HI_DRV_PIX_FMT_YYUV:
            return g_pPixFmtString[9];
        case HI_DRV_PIX_FMT_YVYU:
            return g_pPixFmtString[10];
        case HI_DRV_PIX_FMT_UYVY:
            return g_pPixFmtString[11];
        case HI_DRV_PIX_FMT_VYUY:
            return g_pPixFmtString[12];
        default:
            HI_OSAL_Snprintf(g_pPixFmtUnknown, 10, "%d", enPixfmt);
            return g_pPixFmtUnknown;
    }

}

HI_S32 WIN_ProcParsePara(HI_CHAR *pProcPara, HI_CHAR **ppItem, HI_CHAR **ppValue)
{
    HI_CHAR *pChar = HI_NULL;
    HI_CHAR *pItem, *pValue;

    pChar = strchr(pProcPara, '=');
    if (HI_NULL == pChar)
    {
        return HI_FAILURE; /* Not Found '=' */
    }

    pItem = pProcPara;
    pValue = pChar + 1;
    *pChar = '\0';

    /* remove blank bytes from item tail */
    pChar = pItem;
    while (*pChar != ' ' && *pChar != '\0')
    {
        pChar++;
    }
    *pChar = '\0';

    /* remove blank bytes from value head */
    while (*pValue == ' ')
    {
        pValue++;
    }

    *ppItem = pItem;
    *ppValue = pValue;

    return HI_SUCCESS;
}

extern HI_U8 *g_pVDPColorSpaceString[HI_DRV_CS_BUTT];

#define WIN_PROC_BASE               0
#define WIN_PROC_EXTREN_WIN_POSI    1
HI_U32 g_pWinProcLevel = WIN_PROC_BASE;

static HI_VOID Win_GetProcBufStatus(struct seq_file *p, WIN_PROC_INFO_S *pstProcInfo)
{
    HI_U32 i = 0;
    WB_STATE_S *pstBuffer = &pstProcInfo->stBufState;

    PROC_PRINT(p,
               "-----------------------Buffer State---------------------------------\n"
               "Queue(Try/OK)       :%d/%d\n"
               "Release(Try/OK)     :%d/%d\n"
               "Config              :%d\n"
               "Underload           :%d\n"
               "Discard             :%d\n"
               "UndispFrame(Q/DQ)   :%d/%d\n"
               "MemRefCnt(Inc/Dec)  :%d/%d\n"
               "*FieldUnmatchCnt    :%d\n"
			   "*Alpha              :%d\n",
               pstBuffer->stRecord.u32TryQueueFrame, pstBuffer->stRecord.u32QueueFrame,
               pstBuffer->stRecord.u32Release, pstBuffer->stRecord.u32Release,
               pstBuffer->stRecord.u32Config,
               pstProcInfo->u32UnderLoad,
               pstBuffer->stRecord.u32Disacard,
               pstProcInfo->u32ULSIn, pstProcInfo->u32ULSOut,
               pstBuffer->stRecord.u32IncreaseMemRefCnt, pstBuffer->stRecord.u32DecreaseMemRefCnt,
               pstProcInfo->u32TBNotMatchCount,
			   pstProcInfo->u32Alpha
              );

    {
        HI_S32 EmpNum, WrtNum, ToDispNum, DispNum, DispedNum;

        EmpNum    = 0;
        WrtNum    = 0;
        ToDispNum = 0;
        DispNum   = 0;
        DispedNum = 0;

        for (i = 0; i < pstProcInfo->stBufState.u32Number; i++)
        {
            switch (pstProcInfo->stBufState.stNode[i].u32State)
            {
                case 0:
                case 1:
                    EmpNum++;
                    break;
                case 2:
                    WrtNum++;
                    break;
                case 3:
                    ToDispNum++;
                    break;
                case 4:
                    DispNum++;
                    break;
                case 5:
                    DispedNum++;
                    break;
            }
        }

        PROC_PRINT(p,
                   "--------------------------------------------------------------------\n"
                   "BufferQueue[state, FrameID]\n"
                   "(State: 1,Empty[%d]; 2,Write[%d]; 3,ToDisp[%d]; 4,Disp[%d]; 5,Disped[%d])\n",
                   EmpNum, WrtNum, ToDispNum, DispNum, DispedNum
                  );
    }

    for (i = 0; i < pstBuffer->u32Number;)
    {
        PROC_PRINT(p, "[%d,0x%x] ",
                   pstBuffer->stNode[i].u32State,
                   pstBuffer->stNode[i].u32FrameIndex
                  );

        i++;
        if ( (i % 4) == 0)
        {
            PROC_PRINT(p, "\n");
        }
    }

}

static HI_S32 DRV_WIN_Calc_Frame_Time(HI_U32 *pu32FrameTime, HI_U32 *pu32FrameConfigToDispTime,
                                      HI_U32 *pu32ThousandFrameAveDelayTime, HIDRV_DISP_NODE_DELAYTIME *pstDispNodeDelayTime)

{
    if ((HI_NULL == pstDispNodeDelayTime))
    {
        return HI_FAILURE;
    }

    if (pstDispNodeDelayTime->bNodeCalcSwitchFlag)
    {
        *pu32FrameConfigToDispTime = pstDispNodeDelayTime->u32NodeConfigLeftTime * 1000;

        if (pstDispNodeDelayTime->astDispNodeTime[0].u32NodeTimeus > 0)
        {
            *pu32FrameTime = pstDispNodeDelayTime->u32CurrentNodeTimeus + pstDispNodeDelayTime->u32NodeConfigLeftTime * 1000;
        }

        if (pstDispNodeDelayTime->u32ThousandNodeAveDelayTime > 0)
        {
            *pu32ThousandFrameAveDelayTime  = pstDispNodeDelayTime->u32ThousandNodeAveDelayTime + pstDispNodeDelayTime->u32NodeConfigLeftTime * 1000;
        }
    }
    else
    {
        *pu32FrameTime                  = 0;
        *pu32FrameConfigToDispTime      = 0;
        *pu32ThousandFrameAveDelayTime  = 0;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_WIN_ProcRead(struct seq_file *p, HI_VOID *v)
{
    DRV_PROC_ITEM_S *pProcItem;
    HI_DRV_VIDEO_FRAME_S *pstNewFrame;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    WIN_PROC_INFO_S *pstProcInfo;
    HI_HANDLE hWin;
    HI_S32 nRet;
    HI_U32 i;
    HI_U8 *pu8WinSate;

    WINDOW_S *pstWin = HI_NULL;
    HIDRV_DISP_NODE_DELAYTIME   *pstDispNodeDelayTime = HI_NULL;

    HI_U32  u32FrameTime = 0;
    HI_U32  u32FrameConfigToDispTime = 0;
    HI_U32  u32ThousandFrameAveDelayTime = 0;

    nRet = down_interruptible(&g_VoMutex);
    pProcItem = p->private;

    hWin = (HI_HANDLE)(unsigned long)pProcItem->data;

    pstProcInfo = (WIN_PROC_INFO_S *)DISP_MALLOC(sizeof(WIN_PROC_INFO_S));
    if (!pstProcInfo)
    {
        PROC_PRINT(p, "-------- Malloc Proc Buffer Failed!--------\n");
        goto _ERR_EXIT_;
    }

    nRet = WinGetProcInfo(hWin, pstProcInfo);
    if (nRet)
    {
        HI_ERR_WIN("WinGetProcInfo FAILED!\n");
        goto _ERR_EXIT_;
    }

    WinCheckWindow(hWin, pstWin);

    PROC_PRINT(p, "------------------------------Win%04x[Z=%d]------------------------------------\n"
               "------------Win Info-------------------|-------------Frame Info-------------------\n",
               (HI_U32)(pstProcInfo->u32Index & 0xffffUL),
               pstProcInfo->u32Zorder);

    switch (pstProcInfo->u32WinState)
    {
        case 1:
            pu8WinSate = g_pWinStateString[1];
            break;
        case 2:
            pu8WinSate = g_pWinStateString[2];
            break;
        case 3:
            if (pstProcInfo->enFreezeMode == HI_DRV_WIN_SWITCH_LAST)
            {
                pu8WinSate = g_pWinStateString[3];
            }
            else
            {
                pu8WinSate = g_pWinStateString[4];
            }
            break;
        default:
            pu8WinSate = g_pWinStateString[0];
            break;
    }


    /*
    ------------------------------Win0100 [Z=1]-------------------------------------
    ------------Win Info-----------------|-------------Frame Info-------------------
    Enable              :TRUE            |Type/PixFmt         :NotStereo/NV12
    State               :Working         |Circurotate         :FALSE
    Type                :Main            |W/H(WvsH)           :1920/1080(16:9)
    LayerID             :0               |Disp(X/Y/W/H)       :0/0/1920/1080
    AspectRatioConvert  :Full            |FrameRate           :50
    CustAspectRatio     :HI_FALSE        |ColorSpace          :BT709_YUV_LIMITED
    Crop                :Enable          |Fieldmode(Origin)   :Frame(Bottom)
    Crop(L/T/R/B)       :0/0/0/0         |OriRect(X/Y/W/H)    :0/0/720/576
    In  (X/Y/W/H)       :0/0/0/0         |FrameIndex          :0x15eb5
    Out (X/Y/W/H)       :0/0/1280/720    |SrcPTS/PTS          :0x31a7345/0x31a7359
    DispMode/RightFirst :2D/HI_FALSE     |PlayTime            :1
    Masked              :FALSE           |FieldMode           :All
    AttachSource        :AVPLAY0         |Fidelity            :0
    CallBack            :Acquire(N)      |Y/CAddr             :0x23719000/0x23913400
                        :Release(Y)      |Y/CStride           :0x780/0x780
                        :SetAttr(Y)      |
    SlaveID             :win0000         |
    ----VirtualWindowInfo-----           |
    MemoryType          :NA              |
    BufferNum           :0               |
    PixelFormat         :NA              |
    */
    if ( (pstProcInfo->enType == HI_DRV_WIN_ACTIVE_SLAVE))
    {
        pstNewFrame = pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveCfgFrame;

        if (pstNewFrame)
        {
            pstPriv     = (HI_DRV_VIDEO_PRIVATE_S *)(&pstNewFrame->u32Priv[0]);
            PROC_PRINT(p, "%-19s:%-20s", "Enable", g_pWinTrueString[pstProcInfo->bEnable]);
            PROC_PRINT(p, "%-19s:%-10s/%-9s\n", "|Type/PixFmt", g_pWinFrameTypetring[pstNewFrame->eFrmType],
                       DrvWinGetPixfmtString(pstNewFrame->ePixFormat));
            PROC_PRINT(p, "%-19s:%-20s", "State", pu8WinSate);
            PROC_PRINT(p, "%-19s:%-20s\n", "|Rotation", g_pWinRotateString[pstNewFrame->u32Circumrotate > 0]);
            PROC_PRINT(p, "%-19s:%-20s", "Type", g_pWinTpyeString[pstProcInfo->enType]);
            PROC_PRINT(p, "%-19s:%4d/%4d(%4d:%4d)\n", "|W/H(Aspect W:H)", pstNewFrame->u32Width, pstNewFrame->u32Height,
                       (HI_U32)pstNewFrame->u32AspectWidth,
                       (HI_U32)pstNewFrame->u32AspectHeight);
            PROC_PRINT(p, "%-19s:%-20X", "*LayerID", pstProcInfo->u32LayerId);

            PROC_PRINT(p, "%-19s:%4d/%4d/%4d/%4d \n", "|Disp(X/Y/W/H)",
                       pstNewFrame->stDispRect.s32X,
                       pstNewFrame->stDispRect.s32Y,
                       pstNewFrame->stDispRect.s32Width,
                       pstNewFrame->stDispRect.s32Height);
            PROC_PRINT(p, "%-19s:%-20s", "AspectRatioConvert", g_pWinAspectCvrsString[pstProcInfo->stAttr.enARCvrs]);
            PROC_PRINT(p, "%-19s:%d.%d\n", "|FrameRate", pstNewFrame->u32FrameRate / 100,
                       pstNewFrame->u32FrameRate - (pstNewFrame->u32FrameRate - (pstNewFrame->u32FrameRate / 100 * 100))
                      );

            PROC_PRINT(p, "%-19s:%-4d:%-15d", "CustAspectRatio", (HI_U32)pstProcInfo->stAttr.stCustmAR.u32ARw,
                       (HI_U32)pstProcInfo->stAttr.stCustmAR.u32ARh);
            PROC_PRINT(p, "%-19s:%-20s\n", "|ColorSpace", g_pVDPColorSpaceString[pstPriv->eColorSpace]);

            PROC_PRINT(p, "%-19s:%-20s", "Crop", g_pWinTrueString[pstProcInfo->stAttr.bUseCropRect]);
            PROC_PRINT(p, "%-19s:%s(%s)\n", "|Fieldmode(Origin)", g_pWinFieldTypeString[pstNewFrame->enFieldMode],
                       g_pWinFieldTypeString[pstPriv->eOriginField]);
            PROC_PRINT(p, "%-19s:%4x/%4x/%4x/%4x ", "Crop(L/T/R/B) ",  pstProcInfo->stAttr.stCropRect.u32LeftOffset,
                       pstProcInfo->stAttr.stCropRect.u32TopOffset,
                       pstProcInfo->stAttr.stCropRect.u32RightOffset,
                       pstProcInfo->stAttr.stCropRect.u32BottomOffset);
            PROC_PRINT(p, "%-19s:%d/%d/%d/%d\n", "|OriRect(X/Y/W/H)",  0,
                       0,
                       pstPriv->stVideoOriginalInfo.u32Width,
                       pstPriv->stVideoOriginalInfo.u32Height);
            PROC_PRINT(p, "%-19s:%4d/%4d/%4d/%4d ", "In  (X/Y/W/H)", pstProcInfo->stAttr.stInRect.s32X,
                       pstProcInfo->stAttr.stInRect.s32Y,
                       pstProcInfo->stAttr.stInRect.s32Width,
                       pstProcInfo->stAttr.stInRect.s32Height);
            PROC_PRINT(p, "%-19s:0x%x\n", "|FrameIndex",  pstNewFrame->u32FrameIndex);
            PROC_PRINT(p, "%-19s:%4d/%4d/%4d/%4d ", "Out(X/Y/W/H)", pstProcInfo->stAttr.stOutRect.s32X,
                       pstProcInfo->stAttr.stOutRect.s32Y,
                       pstProcInfo->stAttr.stOutRect.s32Width,
                       pstProcInfo->stAttr.stOutRect.s32Height);
            PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|SrcPTS/PTS",  pstNewFrame->u32SrcPts, pstNewFrame->u32Pts);

            PROC_PRINT(p, "%-19s:%d\n", "|PlayTime", pstPriv->u32PlayTime);
            PROC_PRINT(p, "%-19s:%-20s", "*Masked", g_pWinTrueString[pstProcInfo->bMasked]);
            PROC_PRINT(p, "%-19s:%-20s\n", "|FieldMode", g_pWinFieldModeString[pstNewFrame->enFieldMode]);
            PROC_PRINT(p, "%-19s:%-20s", "AttachSource", g_pWinTrueString[pstProcInfo->hSrc != HI_INVALID_HANDLE]);
            PROC_PRINT(p, "%-19s:%d\n", "|Fidelity", pstPriv->u32Fidelity);
            PROC_PRINT(p, "%-19s:%-20s", "*CallBack(Acquire)", g_pWinYNString[pstProcInfo->pfAcqFrame    != HI_NULL]);
            PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|H8:YAddr/YStride", pstNewFrame->stBufAddr[0].u32PhyAddr_Y, pstNewFrame->stBufAddr[0].u32Stride_Y);
            PROC_PRINT(p, "%-19s:%-20s", "*CallBack(Release)", g_pWinYNString[pstProcInfo->pfRlsFrame    != HI_NULL]);
            PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|H8:CAddr/CStride", pstNewFrame->stBufAddr[0].u32PhyAddr_C, pstNewFrame->stBufAddr[0].u32Stride_C);
            PROC_PRINT(p, "%-19s:%-20s", "*CallBack(SetAttr)", g_pWinYNString[pstProcInfo->pfSendWinInfo != HI_NULL]);
            PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|L2:YAddr/YStride", pstNewFrame->stBufAddr_LB[0].u32PhyAddr_Y, pstNewFrame->stBufAddr_LB[0].u32Stride_Y);
            PROC_PRINT(p, "%-19s:%-20s", "hSecondSrc", g_pWinYNString[pstProcInfo->hSecondSrc != HI_INVALID_HANDLE]);
            PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|L2:CAddr/CStride", pstNewFrame->stBufAddr_LB[0].u32PhyAddr_C, pstNewFrame->stBufAddr_LB[0].u32Stride_C);
            PROC_PRINT(p, "%-19s:%-20s", "WinMode", g_pWinModeString[pstProcInfo->enWinMode]);
            PROC_PRINT(p, "%-19s:%-20d", "Secure", pstNewFrame->bSecure);
            PROC_PRINT(p, "\n");
        }

        PROC_PRINT(p, "-----------------Isogeny  infor--------------------------------|\n");
        PROC_PRINT(p, "%-19s:%-20d\n",  "wbc point", pstProcInfo->stIsogenyProcInfo.enWBCForcePoint);
        PROC_PRINT(p, "%-19s:%-20d\n",  "enIsogenyBuffMode:", pstProcInfo->stIsogenyProcInfo.enIsogenyBuffMode);
        PROC_PRINT(p, "%-19s:%-20d\n",  "enIsogenyBuffStatus:", pstProcInfo->stIsogenyProcInfo.enIsogenyBuffStatus);
        PROC_PRINT(p, "%-19s:%-20d\n",  "enWBCForcePoint:", pstProcInfo->stIsogenyProcInfo.enWBCForcePoint);
        PROC_PRINT(p, "%-19s:%-20d\n",  "enWBForceField:", pstProcInfo->stIsogenyProcInfo.enWBForceField);
        PROC_PRINT(p, "%-19s:%-20d\n",  "enWBForceField:", pstProcInfo->stIsogenyProcInfo.enWBForceField);
        PROC_PRINT(p, "%-19s:%-20d\n",  "u32WBCFinishCount:", pstProcInfo->stIsogenyProcInfo.stWBC0ProcInfo.u32WBCFinishCount);
        PROC_PRINT(p, "%-19s:%-20d\n",  "u32WBCDisardCount:", pstProcInfo->stIsogenyProcInfo.stWBC0ProcInfo.u32WBCDisardCount);
        if (HI_NULL != pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveNextNode)
        {
            PROC_PRINT(p, "%-19s:0x%-20x\n",    "SalveNextNode:ID",  pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveNextNode->u32ID);
        }
        else
        {
            PROC_PRINT(p, "%-19s:%-20s\n",  "SalveNextNode:", "Nothing");
        }

        if (HI_NULL != pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveCurrentNode)
        {
            PROC_PRINT(p, "%-19s:0x%-20x\n",    "SalveCurrentNode:ID",  pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveCurrentNode->u32ID);
            PROC_PRINT(p, "%-19s:%-20d\n",  "Config FrameIndx",  pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveCfgFrame->u32FrameIndex);
        }
        else
        {
            PROC_PRINT(p, "%-19s:%-20s\n",  "SalveCurrentNode:", "Nothing");
        }

        if (HI_NULL != pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveDispNode)
        {
            PROC_PRINT(p, "%-19s:0x%-20x\n",    "SalveDispNode:ID",  pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.pstSalveDispNode->u32ID);
        }
        else
        {
            PROC_PRINT(p, "%-19s:%-20s\n",  "SalveDispNode:", "Nothing");
        }

        PROC_PRINT(p, "%-19s:%-20d\n",  "u32SalveCfgCount:", pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.u32SalveCfgCount);
        PROC_PRINT(p, "%-19s:%-20d\n",  "u32SalveRecCount:", pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.u32SalveRecCount);
        PROC_PRINT(p, "%-19s:%-20d\n",  "u32SalveDisardCount:", pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.u32SalveDisardCount);
        PROC_PRINT(p, "%-19s:%-20d\n",  "u32SalveRepeatCount:", pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.u32SalveRepeatCount);
        PROC_PRINT(p, "%-19s:%-20d\n",  "u32SalveReleaseCount:", pstProcInfo->stIsogenyProcInfo.stSlaveProcInfo.u32SalveReleaseCount);

        for (i = 0; i < pstProcInfo->stIsogenyProcInfo.pstBuffer->u32Number;)
        {
            pstNewFrame = (HI_DRV_VIDEO_FRAME_S *) & (pstProcInfo->stIsogenyProcInfo.pstBuffer->pstBufArray[i]->u32Data);
            PROC_PRINT(p, "[%d,0x%x,%d,0x%x] ",
                       pstProcInfo->stIsogenyProcInfo.pstBuffer->pstBufArray[i]->u32ID,
                       pstProcInfo->stIsogenyProcInfo.pstBuffer->pstBufArray[i]->u32State,
                       pstNewFrame->u32FrameIndex,
                       pstNewFrame->stBufAddr[0].u32PhyAddr_Y
                      );

            i++;
            if ( (i % 4) == 0)
            {
                PROC_PRINT(p, "\n");
            }
        }

        PROC_PRINT(p, "\n");

        PROC_PRINT(p, "Empty:read->%d,Write->%d \n", pstProcInfo->stIsogenyProcInfo.pstBuffer->u32EmptyReadPos, pstProcInfo->stIsogenyProcInfo.pstBuffer->u32EmptyWritePos);

        for (i = 0; i < pstProcInfo->stIsogenyProcInfo.pstBuffer->u32Number; i++)
        {
            PROC_PRINT(p, "[%d],", pstProcInfo->stIsogenyProcInfo.pstBuffer->u32EmptyArray[i]);

        }
        PROC_PRINT(p, "\n");


        PROC_PRINT(p, "Full:read->%d,Write->%d \n", pstProcInfo->stIsogenyProcInfo.pstBuffer->u32FullReaddPos, pstProcInfo->stIsogenyProcInfo.pstBuffer->u32FullWritePos);

        for (i = 0; i < pstProcInfo->stIsogenyProcInfo.pstBuffer->u32Number; i++)
        {
            PROC_PRINT(p, "[%d],", pstProcInfo->stIsogenyProcInfo.pstBuffer->u32FullArray[i]);

        }

        PROC_PRINT(p, "\n");
        if (pstProcInfo)
        {
            DISP_FREE(pstProcInfo);
        }

        up(&g_VoMutex);
        return nRet;

    }

    if ( (pstProcInfo->enType != HI_DRV_WIN_ACTIVE_SLAVE))
    {
        pstNewFrame = &pstProcInfo->stBufState.stCurrentFrame;
        pstPriv     = (HI_DRV_VIDEO_PRIVATE_S *)(&pstNewFrame->u32Priv[0]);
        PROC_PRINT(p, "%-19s:%-20s", "Enable", g_pWinTrueString[pstProcInfo->bEnable]);
        PROC_PRINT(p, "%-19s:%-10s/%-9s\n", "|Type/PixFmt", g_pWinFrameTypetring[pstNewFrame->eFrmType],
                   DrvWinGetPixfmtString(pstNewFrame->ePixFormat));
        PROC_PRINT(p, "%-19s:%-20s", "State", pu8WinSate);
        PROC_PRINT(p, "%-19s:%-20s\n", "|Rotation", g_pWinRotateString[pstNewFrame->u32Circumrotate > 0]);
        PROC_PRINT(p, "%-19s:%-20s", "Type", g_pWinTpyeString[pstProcInfo->enType]);
        PROC_PRINT(p, "%-19s:%4d/%4d(%4d:%4d)\n", "|W/H(Aspect W:H)", pstNewFrame->u32Width, pstNewFrame->u32Height,
                   (HI_U32)pstNewFrame->u32AspectWidth,
                   (HI_U32)pstNewFrame->u32AspectHeight);
        PROC_PRINT(p, "%-19s:%-20X", "*LayerID", pstProcInfo->u32LayerId);

        PROC_PRINT(p, "%-19s:%4d/%4d/%4d/%4d \n", "|Disp(X/Y/W/H)",
                   pstNewFrame->stDispRect.s32X,
                   pstNewFrame->stDispRect.s32Y,
                   pstNewFrame->stDispRect.s32Width,
                   pstNewFrame->stDispRect.s32Height);
        PROC_PRINT(p, "%-19s:%-20s", "AspectRatioConvert", g_pWinAspectCvrsString[pstProcInfo->stAttr.enARCvrs]);
        PROC_PRINT(p, "%-19s:%d.%d\n", "|FrameRate", pstNewFrame->u32FrameRate / 100,
                   pstNewFrame->u32FrameRate - (pstNewFrame->u32FrameRate - (pstNewFrame->u32FrameRate / 100 * 100))
                  );

        PROC_PRINT(p, "%-19s:%-4d:%-15d", "CustAspectRatio", (HI_U32)pstProcInfo->stAttr.stCustmAR.u32ARw,
                   (HI_U32)pstProcInfo->stAttr.stCustmAR.u32ARh);
        PROC_PRINT(p, "%-19s:%-20s\n", "|ColorSpace", g_pVDPColorSpaceString[pstPriv->eColorSpace]);

        PROC_PRINT(p, "%-19s:%-20s", "Crop", g_pWinTrueString[pstProcInfo->stAttr.bUseCropRect]);
        PROC_PRINT(p, "%-19s:%s(%s)\n", "|Fieldmode(Origin)", g_pWinFieldTypeString[pstNewFrame->enFieldMode],
                   g_pWinFieldTypeString[pstPriv->eOriginField]);
        PROC_PRINT(p, "%-19s:%4x/%4x/%4x/%4x ", "Crop(L/T/R/B) ",  pstProcInfo->stAttr.stCropRect.u32LeftOffset,
                   pstProcInfo->stAttr.stCropRect.u32TopOffset,
                   pstProcInfo->stAttr.stCropRect.u32RightOffset,
                   pstProcInfo->stAttr.stCropRect.u32BottomOffset);
        PROC_PRINT(p, "%-19s:%d/%d/%d/%d\n", "|OriRect(X/Y/W/H)",  0,
                   0,
                   pstPriv->stVideoOriginalInfo.u32Width,
                   pstPriv->stVideoOriginalInfo.u32Height);
        PROC_PRINT(p, "%-19s:%4d/%4d/%4d/%4d ", "In  (X/Y/W/H)", pstProcInfo->stAttr.stInRect.s32X,
                   pstProcInfo->stAttr.stInRect.s32Y,
                   pstProcInfo->stAttr.stInRect.s32Width,
                   pstProcInfo->stAttr.stInRect.s32Height);
        PROC_PRINT(p, "%-19s:0x%x\n", "|FrameIndex",  pstNewFrame->u32FrameIndex);
        PROC_PRINT(p, "%-19s:%4d/%4d/%4d/%4d ", "Out(X/Y/W/H)", pstProcInfo->stAttr.stOutRect.s32X,
                   pstProcInfo->stAttr.stOutRect.s32Y,
                   pstProcInfo->stAttr.stOutRect.s32Width,
                   pstProcInfo->stAttr.stOutRect.s32Height);
        PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|SrcPTS/PTS",  pstNewFrame->u32SrcPts, pstNewFrame->u32Pts);
        PROC_PRINT(p, "%-19s:%-10s/%-9s", "DispMode/RightFirst", g_pWinDispModeString[pstProcInfo->eDispMode],
                   g_pWinTrueString[pstProcInfo->bRightEyeFirst]);
        PROC_PRINT(p, "%-19s:%d\n", "|PlayTime", pstPriv->u32PlayTime);
        PROC_PRINT(p, "%-19s:%-20s", "*Masked", g_pWinTrueString[pstProcInfo->bMasked]);
        PROC_PRINT(p, "%-19s:%-20s\n", "|FieldMode", g_pWinFieldModeString[pstNewFrame->enFieldMode]);
        PROC_PRINT(p, "%-19s:%-20s", "AttachSource", g_pWinTrueString[pstProcInfo->hSrc != HI_INVALID_HANDLE]);
        PROC_PRINT(p, "%-19s:%d\n", "|Fidelity", pstPriv->u32Fidelity);
        PROC_PRINT(p, "%-19s:%-20s", "*CallBack(Acquire)", g_pWinYNString[pstProcInfo->pfAcqFrame    != HI_NULL]);
        PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|H8:YAddr/YStride", pstNewFrame->stBufAddr[0].u32PhyAddr_Y, pstNewFrame->stBufAddr[0].u32Stride_Y);
        PROC_PRINT(p, "%-19s:%-20s", "*CallBack(Release)", g_pWinYNString[pstProcInfo->pfRlsFrame    != HI_NULL]);
        PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|H8:CAddr/CStride", pstNewFrame->stBufAddr[0].u32PhyAddr_C, pstNewFrame->stBufAddr[0].u32Stride_C);
        PROC_PRINT(p, "%-19s:%-20s", "*CallBack(SetAttr)", g_pWinYNString[pstProcInfo->pfSendWinInfo != HI_NULL]);
        PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|L2:YAddr/YStride", pstNewFrame->stBufAddr_LB[0].u32PhyAddr_Y, pstNewFrame->stBufAddr_LB[0].u32Stride_Y);
        PROC_PRINT(p, "%-19s:%-20s", "hSecondSrc", g_pWinYNString[pstProcInfo->hSecondSrc != HI_INVALID_HANDLE]);
        PROC_PRINT(p, "%-19s:0x%x/0x%x\n", "|L2:CAddr/CStride", pstNewFrame->stBufAddr_LB[0].u32PhyAddr_C, pstNewFrame->stBufAddr_LB[0].u32Stride_C);
        PROC_PRINT(p, "%-19s:%-20s", "WinMode", g_pWinModeString[pstProcInfo->enWinMode]);
        PROC_PRINT(p, "%-19s:%-20s\n", "|Frame BitWidth", g_pWinFrmBitWidthString[pstNewFrame->enBitWidth]);
        PROC_PRINT(p, "%-19s:%-20s|\n", "OpenHdr", g_pWinYNString[!pstProcInfo->stAttr.bCloseHdrPath]);
        PROC_PRINT(p, "%-19s:%-20s|\n", "HisiHdr", g_pWinYNString[pstProcInfo->stAttr.bHisiHdr]);

        if (pstProcInfo->hSlvWin)
        {
            PROC_PRINT(p, "%-19s:%04X                |\n", "SlaveWinID", (HI_U32)(pstProcInfo->hSlvWin & 0xFFFFul));
        }
        else
        {
            PROC_PRINT(p, "%-19s:%04X                |\n", "SlaveWinID", (HI_U32)0xFFFFul);
        }

        PROC_PRINT(p, "%-19s:%-4d                |\n", "bQuickoutMode", pstProcInfo->bQuickMode);
        PROC_PRINT(p, "%-19s:%-4d                |\n", "bVirtualCoordinate", pstProcInfo->bVirtualCoordinate);
        PROC_PRINT(p, "%-19s:%-20X \n", "*LayerRegionNum", pstProcInfo->u32LayerRegionNo);
        PROC_PRINT(p, "%-19s:%-20X \n", "*Zorder", pstProcInfo->u32Zorder);
    }

    if (pstProcInfo->stAttr.bVirtual)
    {
        PROC_PRINT(p, "----VirtualWindowInfo-----           |\n");
        PROC_PRINT(p, "%-19s:%-20s\n", "MemoryType", g_pWinMemTypeString[pstProcInfo->stAttr.bUserAllocBuffer == HI_TRUE]);
        PROC_PRINT(p, "%-19s:%-20d\n", "BufferNum", pstProcInfo->stAttr.u32BufNumber);
        PROC_PRINT(p, "%-19s:%-20s\n", "PixelFormat", DrvWinGetPixfmtString(pstProcInfo->stAttr.enDataFormat));
    }

    /*
    -----------------------HDR10 frame info-----------------------------
    */
    if (g_pWinProcLevel >= WIN_PROC_EXTREN_WIN_POSI )
    {
        switch (pstNewFrame->enSrcFrameType)
        {
            case HI_DRV_VIDEO_FRAME_TYPE_SDR:
                PROC_PRINT(p,
                           "-----------------------SDR frame info-----------------------------\n"
                           "ColourPrimaries     :%d\n"
                           "MatrixCoeffs        :%d\n"
                           "bFullRange          :%d\n",
                           pstNewFrame->stColourInfo.u8ColourPrimaries,
                           pstNewFrame->stColourInfo.u8MatrixCoeffs,
                           pstNewFrame->stColourInfo.u8FullRangeFlag
                          );
                break;

            case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
                PROC_PRINT(p,
                           "-----------------------HDR10 frame info-----------------------------\n"
                           "ColourPrimaries     :%d\n"
                           "MatrixCoeffs        :%d\n"
                           "bFullRange          :%d\n"
                           "TransferCharac      :%d\n"
                           "bMasteringAvailable :%d\n"
                           "MaxMasterLum        :%d\n"
                           "MinMasterLum        :%d\n"
                           "bContentAvailable   :%d\n",
                           pstNewFrame->stColourInfo.u8ColourPrimaries,
                           pstNewFrame->stColourInfo.u8MatrixCoeffs,
                           pstNewFrame->stColourInfo.u8FullRangeFlag,
                           pstNewFrame->unHDRInfo.stHDR10Info.u8TransferCharacteristics,
                           pstNewFrame->unHDRInfo.stHDR10Info.u8MasteringAvailable,
                           pstNewFrame->unHDRInfo.stHDR10Info.stMasteringInfo.u32MaxDisplayMasteringLuminance,
                           pstNewFrame->unHDRInfo.stHDR10Info.stMasteringInfo.u32MinDisplayMasteringLuminance,
                           pstNewFrame->unHDRInfo.stHDR10Info.u8ContentAvailable
                          );
                break;

            case HI_DRV_VIDEO_FRAME_TYPE_HLG:
                PROC_PRINT(p,
                           "-----------------------HLG frame info-----------------------------\n"
                           "ColourPrimaries     :%d\n"
                           "MatrixCoeffs        :%d\n"
                           "bFullRange          :%d\n",
                           pstNewFrame->stColourInfo.u8ColourPrimaries,
                           pstNewFrame->stColourInfo.u8MatrixCoeffs,
                           pstNewFrame->stColourInfo.u8FullRangeFlag
                          );
                break;

            case HI_DRV_VIDEO_FRAME_TYPE_SLF:
                PROC_PRINT(p,
                           "-----------------------SLF frame info-----------------------------\n"
                           "ColourPrimaries     :%d\n"
                           "MatrixCoeffs        :%d\n"
                           "bFullRange          :%d\n",
                           pstNewFrame->stColourInfo.u8ColourPrimaries,
                           pstNewFrame->stColourInfo.u8MatrixCoeffs,
                           pstNewFrame->stColourInfo.u8FullRangeFlag
                          );

            default:
                break;
        }
    }
    Win_GetProcBufStatus(p, pstProcInfo);
    PROC_PRINT(p, "DataFlow Path:%s\n", g_pWinDataFlowPath[pstProcInfo->stWinInfoForDeveloper.eWinDataFlow]);

    PROC_PRINT(p, "Overlay Lowdelay stat: OmxDone %u, OverlayQueue %u, WinGet %u, WinConfig %u, Total %u\n",
               pstProcInfo->stLowdelayStat.u32OmxReportDoneTime,
               pstProcInfo->stLowdelayStat.u32OverlayQueueTime,
               pstProcInfo->stLowdelayStat.u32WinGetFrameTime,
               pstProcInfo->stLowdelayStat.u32WinConfigTime,
               pstProcInfo->stLowdelayStat.u32WinConfigTime - pstProcInfo->stLowdelayStat.u32OmxReportDoneTime);
	
	pstDispNodeDelayTime = &(pstWin->stBuffer.stWinBP.stBuffer.stDispNodeDelayTime);
    if (HI_NULL != pstDispNodeDelayTime)
    {
        if (pstDispNodeDelayTime->bNodeCalcSwitchFlag)
        {
            DRV_WIN_Calc_Frame_Time(&u32FrameTime, &u32FrameConfigToDispTime, &u32ThousandFrameAveDelayTime, pstDispNodeDelayTime);

            PROC_PRINT(p, "----------------------win frame delay time info----------------------\n");
            PROC_PRINT(p, "AVE frame delay time of %d :%d us  |  frame delay time:%d us\n",
                       CALC_AVE_TIME_FRAME_NUM, u32ThousandFrameAveDelayTime, u32FrameTime);

            PROC_PRINT(p, "the time from frame config to display : %d us\n", u32FrameConfigToDispTime);

            if (g_pWinProcLevel >= WIN_PROC_EXTREN_WIN_POSI )
            {
                PROC_PRINT(p, "--------------------win node add to del time info---------------------\n");
                PROC_PRINT(p, "[NodeID, time(us)]");

                for (i = 0 ; i < DISP_BUF_NODE_MAX_NUMBER ; i++)
                {
                    if (!(i % 4))
                    {
                        PROC_PRINT(p, "\n");
                    }

                    PROC_PRINT(p, "[0x%x, %d us]\t", pstDispNodeDelayTime->astDispNodeTime[i].u32NodeID,
                               pstDispNodeDelayTime->astDispNodeTime[i].u32NodeTimeus);
                }
                PROC_PRINT(p, "\n");
                PROC_PRINT(p, "AVE node delay time of %d :%d us\n", CALC_AVE_TIME_FRAME_NUM,
                           pstDispNodeDelayTime->u32ThousandNodeAveDelayTime);
            }
        }

    }

    if (g_pWinProcLevel >= WIN_PROC_EXTREN_WIN_POSI)
    {
        PROC_PRINT(p,
                   "--------------------------win posi debug info----------------------------\n"
                   "user info:\n"
                   "           vir_inrect: 			(%d,%d,%d,%d)\n"
                   "           vir_outrect:			(%d,%d,%d,%d)\n"
                   "           DispOffset/L/R/T/B/:		(%d,%d,%d,%d)\n"
                   "           ReAttrOutRect:		(%d,%d,%d,%d)\n"
                   "           phy_inrect:			(%d,%d,%d,%d)\n"
                   "           phy_outrect:			(%d,%d,%d,%d)\n"
                   "hal info:\n"
                   "           inrect:			(%d,%d,%d,%d)\n"
                   "           videorect:			(%d,%d,%d,%d)\n"
                   "           disprect:			(%d,%d,%d,%d)\n"
                   "--------------------------win frc debug info----------------------------\n"
                   "frc info:\n"
                   "           status:         %s \n"
                   "           inrota/outrota: (%d/%d)\n"
                   "           count:          %d\n",

                   pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirInRect.s32X, pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirInRect.s32Y, pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirInRect.s32Width, pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirInRect.s32Height,
                   pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirOutRect.s32X, pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirOutRect.s32Y, pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirOutRect.s32Width, pstProcInfo->stWinDebugInfo.stWinUseInfo.stVirOutRect.s32Height,
                   pstProcInfo->stWinDebugInfo.stWinUseInfo.u32OffsetLeft, pstProcInfo->stWinDebugInfo.stWinUseInfo.u32OffsetRight, pstProcInfo->stWinDebugInfo.stWinUseInfo.u32OffsetTop, pstProcInfo->stWinDebugInfo.stWinUseInfo.u32OffsetButtom,
                   pstProcInfo->stWinDebugInfo.stWinUseInfo.stRevisedAttrOutRect.s32X, pstProcInfo->stWinDebugInfo.stWinUseInfo.stRevisedAttrOutRect.s32Y, pstProcInfo->stWinDebugInfo.stWinUseInfo.stRevisedAttrOutRect.s32Width, pstProcInfo->stWinDebugInfo.stWinUseInfo.stRevisedAttrOutRect.s32Height,
                   pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyInRect.s32X, pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyInRect.s32Y, pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyInRect.s32Width, pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyInRect.s32Height,
                   pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyOutRect.s32X, pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyOutRect.s32Y, pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyOutRect.s32Width, pstProcInfo->stWinDebugInfo.stWinUseInfo.stPhyOutRect.s32Height,

                   pstProcInfo->stWinDebugInfo.stWinHalInfo.stSrcRect.s32X, pstProcInfo->stWinDebugInfo.stWinHalInfo.stSrcRect.s32Y, pstProcInfo->stWinDebugInfo.stWinHalInfo.stSrcRect.s32Width, pstProcInfo->stWinDebugInfo.stWinHalInfo.stSrcRect.s32Height,
                   pstProcInfo->stWinDebugInfo.stWinHalInfo.stVideo.s32X, pstProcInfo->stWinDebugInfo.stWinHalInfo.stVideo.s32Y, pstProcInfo->stWinDebugInfo.stWinHalInfo.stVideo.s32Width, pstProcInfo->stWinDebugInfo.stWinHalInfo.stVideo.s32Height,
                   pstProcInfo->stWinDebugInfo.stWinHalInfo.stDisp.s32X, pstProcInfo->stWinDebugInfo.stWinHalInfo.stDisp.s32Y, pstProcInfo->stWinDebugInfo.stWinHalInfo.stDisp.s32Width, pstProcInfo->stWinDebugInfo.stWinHalInfo.stDisp.s32Height,
                   pstProcInfo->stWinDebugInfo.stFRC.bDisable?g_pWinEnableString[0]:g_pWinEnableString[1],
                   pstProcInfo->stWinDebugInfo.stFRC.u32InRota, pstProcInfo->stWinDebugInfo.stFRC.u32OutRota,
                   pstProcInfo->stWinDebugInfo.stFRC.u32Count

                  );
    }

    PROC_PRINT(p, "\n");

_ERR_EXIT_:
    if (pstProcInfo)
    {
        DISP_FREE(pstProcInfo);
    }
    up(&g_VoMutex);
    return nRet;
}

static HI_S32 WinProcParsePara(HI_CHAR *pProcPara, HI_CHAR **ppArg1, HI_CHAR **ppArg2)
{
    HI_CHAR *pChar = HI_NULL;

    if (strlen(pProcPara) == 0)
    {
        /* not fined arg1 and arg2, return failed */
        *ppArg1  = HI_NULL;
        *ppArg2  = HI_NULL;
        return HI_FAILURE;
    }

    /* find arg1 */
    pChar = pProcPara;
    while ( (*pChar == ' ') && (*pChar != '\0') )
    {
        pChar++;
    }

    if (*pChar != '\0')
    {
        *ppArg1 = pChar;
    }
    else
    {
        *ppArg1  = HI_NULL;

        return HI_FAILURE;
    }

    /* ignor arg1 */
    while ( (*pChar != ' ') && (*pChar != '\0') )
    {
        pChar++;
    }

    /* Not find arg2, return */
    if (*pChar == '\0')
    {
        *ppArg2 = HI_NULL;

        return HI_SUCCESS;
    }

    /* add '\0' for arg1 */
    *pChar = '\0';

    /* start to find arg2 */
    pChar = pChar + 1;
    while ( (*pChar == ' ') && (*pChar != '\0') )
    {
        pChar++;
    }

    if (*pChar != '\0')
    {
        *ppArg2 = pChar;
    }
    else
    {
        *ppArg2 = HI_NULL;
    }

    return HI_SUCCESS;
}
HI_VOID WIN_ProcWriteHelp(HI_VOID)
{
    HI_DRV_PROC_EchoHelper("------------------Win Debug Option----------------\n");
    HI_DRV_PROC_EchoHelper("echo help                    > /proc/msp/winXXXX  \n");
	HI_DRV_PROC_EchoHelper("echo asp (0/1/2/3)full/let/pan/cmb   > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo pause   on/off          > /proc/msp/winXXXX  \n");
	HI_DRV_PROC_EchoHelper("echo frc   on/off          > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo reset   black/still     > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo freeze  black/still/off > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo order   up/down         > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo quick   on/off          > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo rota    0/90/180/270    > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo flip    hori/vert       > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo depth   X               > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo capture path            > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo step    on/off          > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo next    1               > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo hdr     on/off          > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo hisi    on/off          > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo outrect x,y,w,h         > /proc/msp/winXXXX  \n");
    HI_DRV_PROC_EchoHelper("echo frm_node_time on/off    > /proc/msp/winXXXX  \n");

}

#ifndef HI_ADVCA_FUNCTION_RELEASE
HI_S32 WinProcHelp(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;
    WIN_ProcWriteHelp();

    return s32Ret;
}

HI_S32 WinProcPause(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        s32Ret = WIN_Pause(hWin, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        s32Ret = WIN_Pause(hWin, HI_FALSE);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcReset(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "black", strlen("black")))
    {
        s32Ret = WIN_Reset(hWin, HI_DRV_WIN_SWITCH_BLACK);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "still", strlen("still")))
    {
        s32Ret = WIN_Reset(hWin, HI_DRV_WIN_SWITCH_LAST);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcFreeze(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "black", strlen("black")))
    {
        s32Ret = WIN_Freeze(hWin, HI_TRUE, HI_DRV_WIN_SWITCH_BLACK);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "still", strlen("still")))
    {
        s32Ret = WIN_Freeze(hWin, HI_TRUE, HI_DRV_WIN_SWITCH_LAST);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        s32Ret = WIN_Freeze(hWin, HI_FALSE, HI_DRV_WIN_SWITCH_BLACK);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcOrder(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "up", strlen("up")))
    {
        s32Ret = WIN_SetZorder(hWin, HI_DRV_DISP_ZORDER_MOVEUP);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "down", strlen("down")))
    {
        s32Ret = WIN_SetZorder(hWin, HI_DRV_DISP_ZORDER_MOVEDOWN);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcQuick(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        s32Ret = WIN_SetQuick(hWin, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        s32Ret = WIN_SetQuick(hWin, HI_FALSE);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcRota(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    HI_ERR_WIN("Not support set rotation now\n");

    return s32Ret;
}

HI_S32 WinProcFlip(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    HI_ERR_WIN("Not support set flip now\n");

    return s32Ret;
}

HI_S32 WinProcDepth(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    HI_ERR_WIN("Not support set 3d-depth now\n");

    return s32Ret;
}

HI_S32 WinProcCapture(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_UCHAR *pChar = pArg2;
    HI_DRV_VIDEO_FRAME_S *pstCurFrame = HI_NULL;
    HI_U32 pathlength = 0;

    pstCurFrame = (HI_DRV_VIDEO_FRAME_S *)DISP_MALLOC(sizeof(HI_DRV_VIDEO_FRAME_S));
    if (!pstCurFrame)
    {
        HI_ERR_WIN("alloc frame info memory failed\n");
        return HI_FAILURE;
    }

    /* get currently displayed frame  */
    s32Ret = WinGetCurrentImg(hWin, pstCurFrame);
    if (s32Ret != HI_SUCCESS)
    {
        DISP_FREE(pstCurFrame);
        HI_ERR_WIN("call WinGetCurrentImg failed\n");
        return s32Ret;
    }

    /* calculate char nubmer of path string */
    while ( (*pChar != ' ') && (*pChar != '\0') )
    {
        pChar++;
        pathlength++;
    }
    pathlength++;

    /* save yuv frame */
    s32Ret = vdp_DebugSaveYUVImg(pstCurFrame, pArg2, pathlength);

    DISP_FREE(pstCurFrame);

    return s32Ret;
}

HI_S32 WinProcStepPlay(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        s32Ret = WIN_SetStepMode(hWin, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        s32Ret = WIN_SetStepMode(hWin, HI_FALSE);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcNextFrm(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    s32Ret = WIN_SetStepPlay(hWin);

    return s32Ret;
}

HI_S32 WinProcHdrSwitch(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        s32Ret = WIN_CloseHdrPath(hWin, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        s32Ret = WIN_CloseHdrPath(hWin, HI_TRUE);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcForceHisiHdr(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        s32Ret = WIN_SetHisiPath(hWin, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        s32Ret = WIN_SetHisiPath(hWin, HI_FALSE);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 WinProcSetOutRect(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_DRV_WIN_ATTR_S stWinAttr = {0};
    HI_CHAR chX[5] = {0}, chY[5] = {0}, chW[5] = {0}, chH[5] = {0};
    HI_U32 u32X = 0, u32Y = 0, u32W = 0, u32H = 0;
    HI_U32 u32Index = 0, u32XIndex = 0, u32YIndex = 0, u32WIndex = 0, u32HIndex = 0;
    HI_CHAR *pTmpCh = HI_NULL;

    /* parse arg2 into x,y,w,h. */
    pTmpCh = pArg2;
    while ((*pTmpCh != ' ') && (*pTmpCh != '\0'))
    {
        if (*pTmpCh != ',')
        {
            switch (u32Index)
            {
                case 0:
                    chX[u32XIndex++] = *pTmpCh;
                    break;
                case 1:
                    chY[u32YIndex++] = *pTmpCh;
                    break;
                case 2:
                    chW[u32WIndex++] = *pTmpCh;
                    break;
                case 3:
                    chH[u32HIndex++] = *pTmpCh;
                    break;
                default:
                    break;
            }
        }
        else
        {
            u32Index++;
        }

        pTmpCh++;
    }

    /* add end symbol to each array. */
    chX[u32XIndex] = '\0';
    chY[u32YIndex] = '\0';
    chW[u32WIndex] = '\0';
    chH[u32HIndex] = '\0';

    /* transfer to integer. */
    u32X = simple_strtol(chX, NULL, 10);
    u32Y = simple_strtol(chY, NULL, 10);
    u32W = simple_strtol(chW, NULL, 10);
    u32H = simple_strtol(chH, NULL, 10);

    s32Ret = WIN_GetAttr(hWin, &stWinAttr);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }
    stWinAttr.stOutRect.s32X = u32X;
    stWinAttr.stOutRect.s32Y = u32Y;
    stWinAttr.stOutRect.s32Width = u32W;
    stWinAttr.stOutRect.s32Height = u32H;

    s32Ret = WIN_SetAttr(hWin, &stWinAttr);

    return s32Ret;
}


HI_S32 WinProcSetASP(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;
	HI_DRV_WIN_ATTR_S stWinAttr = {0};

	s32Ret = WIN_GetAttr(hWin, &stWinAttr);
	if (HI_SUCCESS != s32Ret)
	{
		return s32Ret;
	}

	stWinAttr.enARCvrs = (HI_DRV_ASP_RAT_MODE_E)simple_strtol(pArg2, NULL, 10);
	
	if( (stWinAttr.enARCvrs <= HI_DRV_ASP_RAT_MODE_COMBINED) && (stWinAttr.enARCvrs >= HI_DRV_ASP_RAT_MODE_FULL))
	{
		HI_DRV_PROC_EchoHelper("set asp mode: %d",*g_pWinAspectCvrsString[stWinAttr.enARCvrs]);
		s32Ret = WIN_SetAttr(hWin, &stWinAttr);
	}

    return s32Ret;
}


HI_S32 WinProcRdDoor(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "start", strlen("start")))
    {
        g_bWinPrivateInformation = HI_TRUE;
    }
    else
    {
        g_bWinPrivateInformation = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S32 WinProcShowDolbyLibInfo(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    WIN_ShowDolbyLibInfo();

    return HI_SUCCESS;
}

HI_S32 WinProcSetProcLevel(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    g_pWinProcLevel = (HI_U32)simple_strtol(pArg2, NULL, 10);

    return HI_SUCCESS;
}

HI_S32 WinProcSrPostDci(HI_HANDLE hWin, HI_CHAR *pArg2)
{
    WIN_Test(hWin);

    return HI_SUCCESS;
}

HI_S32 WinProcSetDelayTime( HI_HANDLE hWin, HI_CHAR *pArg2)
{
    WINDOW_S *pstWin = HI_NULL;

    HIDRV_DISP_NODE_DELAYTIME   *pstDispNodeDelayTime   = HI_NULL;

    WinCheckWindow(hWin, pstWin);

    pstDispNodeDelayTime = &(pstWin->stBuffer.stWinBP.stBuffer.stDispNodeDelayTime);

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
    	HI_DRV_PROC_EchoHelper("set delay time: on\n");
        pstDispNodeDelayTime->bNodeCalcSwitchFlag = HI_TRUE;
    }
    else
    {
    	HI_DRV_PROC_EchoHelper("set delay time: off\n");
        pstDispNodeDelayTime->bNodeCalcSwitchFlag = HI_FALSE;
        memset(pstDispNodeDelayTime, 0, sizeof(HIDRV_DISP_NODE_DELAYTIME));
    }
    return HI_SUCCESS;
}

HI_S32 WinProcSetFRC( HI_HANDLE hWin, HI_CHAR *pArg2)
{
    WINDOW_S *pstWin = HI_NULL;

    WinCheckWindow(hWin, pstWin);

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
    	HI_DRV_PROC_EchoHelper("set frc: on\n");
        pstWin->stWinDebugInfo.stFRC.bDisable = HI_FALSE;
    }
    else
    {
    	HI_DRV_PROC_EchoHelper("set frc: off\n");
        pstWin->stWinDebugInfo.stFRC.bDisable = HI_TRUE;
    }
    return HI_SUCCESS;
}


HI_S32 WinProcSetAlpha(HI_HANDLE hWin, HI_CHAR *pArg2)
{
	WIN_SetWindowAlpha(hWin,(HI_U32)simple_strtol(pArg2, NULL, 10));
    return HI_SUCCESS;
}

static const WIN_PROC_COMMAND WinProcCmds[] =
{
    {"help",     WinProcHelp},
    {"pause",    WinProcPause},
    {"reset",    WinProcReset},
    {"freeze",   WinProcFreeze},
    {"order",    WinProcOrder},
    {"quick",    WinProcQuick},
    {"rota",     WinProcRota},
    {"flip",     WinProcFlip},
    {"depth",    WinProcDepth},
    {"capture",  WinProcCapture},
    {"step",     WinProcStepPlay},
    {"next",     WinProcNextFrm},
    {"hdr",      WinProcHdrSwitch},
    {"hisi",     WinProcForceHisiHdr},
    {"outrect",  WinProcSetOutRect},
    {"rd_door",  WinProcRdDoor},
    {"dolbylib", WinProcShowDolbyLibInfo},
    {"proc",     WinProcSetProcLevel},
    {"sr_post_dci_test", WinProcSrPostDci},
    {"frm_node_time",  WinProcSetDelayTime},
    {"alpha",  WinProcSetAlpha},
    {"asp",  WinProcSetASP},
    {"frc",  WinProcSetFRC},
    
};


HI_S32 WinProcCmdProcess(HI_HANDLE hWin, HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_S32 nRet = HI_SUCCESS;

    HI_U32 u32CmdNum = 0;

    for (u32CmdNum = 0; u32CmdNum < sizeof(WinProcCmds) / sizeof(WIN_PROC_COMMAND); u32CmdNum++)
    {
        if (0 == HI_OSAL_Strncmp(pArg1, WinProcCmds[u32CmdNum].command_name, strlen(WinProcCmds[u32CmdNum].command_name)))
        {
            nRet = WinProcCmds[u32CmdNum].PF_DebugFun(hWin, pArg2);
            break;
        }
    }

    return nRet;
}
#endif

HI_S32 DRV_WIN_ProcWrite(struct file *file,
                         const char __user *buf, size_t count, loff_t *ppos)
{
    struct seq_file *p = file->private_data;
    DRV_PROC_ITEM_S *pProcItem = p->private;
    HI_CHAR *pArg1, *pArg2;
    HI_HANDLE hWin;
    HI_S32 nRet;

    HI_CHAR u8WinProcBuffer[256];

    hWin = (HI_HANDLE)(unsigned long)(pProcItem->data);

    if (count >= sizeof(u8WinProcBuffer))
    {
        HI_ERR_WIN("your parameter string is too long!\n");
        return -EFAULT;
    }

    nRet = down_interruptible(&g_VoMutex);

    memset(u8WinProcBuffer, 0, sizeof(u8WinProcBuffer));
    if (copy_from_user(u8WinProcBuffer, buf, count))
    {
        up(&g_VoMutex);
        HI_ERR_WIN("MMZ: copy_from_user failed!\n");
        return -EFAULT;
    }
    u8WinProcBuffer[count] = 0;

    nRet = WinProcParsePara(u8WinProcBuffer, &pArg1, &pArg2);
    if (  (nRet != HI_SUCCESS)
          || (0 == HI_OSAL_Strncmp(pArg1, "help", strlen("help")))
          || (pArg2 == HI_NULL) )
    {
        up(&g_VoMutex);
        WIN_ProcWriteHelp();
        return count;
    }

#ifndef HI_ADVCA_FUNCTION_RELEASE
    nRet = WinProcCmdProcess(hWin, pArg1, pArg2);
    if (nRet != HI_SUCCESS)
    {
        WIN_ProcWriteHelp();
    }
#endif

    up(&g_VoMutex);

    return count;
}



/***************************************************************/
HI_S32 WIN_AddToProc(HI_HANDLE hWindow)
{
    DRV_PROC_ITEM_S  *pProcItem;
    HI_CHAR           ProcName[12];
    HI_U32 u32Index;
    HI_S32 Ret;

    if (HI_FALSE == WinCheckWhetherCanToCreate(hWindow))
    {
        HI_WARN_WIN("WinCheckWhetherCanToCreate failed!\n");
        return HI_SUCCESS;
    }

    Ret = WinGetProcIndex(hWindow, &u32Index);
    if (Ret)
    {
        HI_ERR_WIN("WinGetProcIndex failed!\n");
        return HI_ERR_VO_ADD_PROC_ERR;
    }

    HI_OSAL_Snprintf(ProcName, 12, "win%04x", (HI_U32)(u32Index & WINDOW_INDEX_MASK));

    pProcItem = HI_DRV_PROC_AddModule(ProcName, HI_NULL, HI_NULL);
    if (!pProcItem)
    {
        HI_ERR_WIN("Window add proc failed!\n");
        return HI_ERR_VO_ADD_PROC_ERR;
    }

    pProcItem->data  = (HI_VOID *)(unsigned long)hWindow;
    pProcItem->read  = DRV_WIN_ProcRead;
    pProcItem->write = DRV_WIN_ProcWrite;

    return HI_SUCCESS;
}

HI_S32 WIN_RemFromProc(HI_HANDLE hWindow)
{
    HI_CHAR           ProcName[12];
    HI_U32 u32Index;
    HI_S32 Ret;

    if (HI_FALSE == WinCheckProcCanBeRemoved(hWindow))
    {
        HI_WARN_WIN(" Win Proc Should Not Removed.!\n");
        return HI_SUCCESS;
    }

    Ret = WinGetProcIndex(hWindow, &u32Index);
    if (!Ret)
    {
        HI_OSAL_Snprintf(ProcName, 12 , "win%04x", (HI_U32)(u32Index & WINDOW_INDEX_MASK));
        HI_DRV_PROC_RemoveModule(ProcName);
    }
    else
    {
        HI_FATAL_WIN("WinGetProcInfo failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_AddToState(WIN_STATE_S *pst2WinState, HI_BOOL bVirtual, HI_DRV_DISPLAY_E enDisp, HI_HANDLE hWin)
{
    HI_S32 i;

    if (bVirtual == HI_TRUE)
    {
        for (i = 0; i < DEF_MAX_WIN_NUM_ON_VIRTUAL_DISP; i++)
        {
            if (pst2WinState->hVirtualWin[i] == HI_NULL)
            {
                pst2WinState->hVirtualWin[i] = hWin;
                return HI_SUCCESS;
            }
        }
    }
    else
    {
        if (enDisp >= HI_DRV_DISPLAY_BUTT)
        {
            return HI_SUCCESS;
        }

        for (i = 0; i < DEF_MAX_WIN_NUM_ON_SINGLE_DISP; i++)
        {
            if (pst2WinState->hWin[enDisp][i] == HI_NULL)
            {
                pst2WinState->hWin[enDisp][i] = hWin;
                return HI_SUCCESS;
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 WIN_RemFromState(WIN_STATE_S *pst2WinState, HI_BOOL bVirtual, HI_HANDLE hWin)
{
    HI_DRV_DISPLAY_E enDisp;
    HI_S32 i;

    if (bVirtual)
    {
        for (i = 0; i < DEF_MAX_WIN_NUM_ON_VIRTUAL_DISP; i++)
        {
            if (pst2WinState->hVirtualWin[i] == hWin)
            {
                pst2WinState->hVirtualWin[i] = HI_NULL;
                return HI_SUCCESS;
            }
        }
    }
    else
    {
        for (enDisp = 0; enDisp < HI_DRV_DISPLAY_BUTT; enDisp++)
        {
            for (i = 0; i < DEF_MAX_WIN_NUM_ON_SINGLE_DISP; i++)
            {
                if (pst2WinState->hWin[enDisp][i] == hWin)
                {
                    pst2WinState->hWin[enDisp][i] = HI_NULL;
                    return HI_SUCCESS;
                }
            }
        }
    }

    return HI_SUCCESS;
}


VDP_MCE_STAGE_E sftware_stage = 0;

HI_S32 DRV_WIN_SetSftwareStage(HI_VOID)
{
    sftware_stage = VDP_NORMAL_STAGE;
    return HI_SUCCESS;
}

HI_S32 DRV_WIN_GetSftwareStage(HI_VOID)
{
    return sftware_stage;
}

HI_S32 WIN_CreateExt(WIN_CREATE_S *pVoWinCreate, WIN_STATE_S *pst2WinState)
{
    HI_DRV_WIN_INFO_S stWinInfo;
    HI_S32 Ret ;

    if (pVoWinCreate->bMCE)
    {
        Ret = WIN_Create_MCE(&pVoWinCreate->WinAttr, &pVoWinCreate->hWindow, pVoWinCreate->bVirtScreen);
    }
    else
    {
        Ret = WIN_Create(&pVoWinCreate->WinAttr, &pVoWinCreate->hWindow, pVoWinCreate->bVirtScreen);
    }

    if ( HI_SUCCESS != Ret)
    {
        goto __ERR_EXIT__;
    }

    if (DRV_WIN_GetSftwareStage())
    {
        // add proc
        Ret = WIN_AddToProc(pVoWinCreate->hWindow);
        if ( HI_SUCCESS != Ret)
        {
            goto __ERR_EXIT_DESTROY__;
        }

        if (pVoWinCreate->WinAttr.bVirtual != HI_TRUE)
        {
            if ( HI_SUCCESS == WIN_GetInfo(pVoWinCreate->hWindow, &stWinInfo))
            {
                if (stWinInfo.hSec)
                {
                    Ret = WIN_AddToProc(stWinInfo.hSec);
                    if ( HI_SUCCESS != Ret)
                    {
                        goto __ERR_EXIT_REM_PORC__;
                    }
                }
            }
        }
    }

    WIN_AddToState(pst2WinState, pVoWinCreate->WinAttr.bVirtual, pVoWinCreate->WinAttr.enDisp, pVoWinCreate->hWindow);
    return HI_SUCCESS;

__ERR_EXIT_REM_PORC__:
    (HI_VOID) WIN_RemFromProc(pVoWinCreate->hWindow);

__ERR_EXIT_DESTROY__:
    (HI_VOID) WIN_Destroy(pVoWinCreate->hWindow);

__ERR_EXIT__:
    return HI_FAILURE;
}

HI_S32 WIN_DestroyExt(HI_HANDLE hWindow, WIN_STATE_S *pstWinState)
{
    HI_DRV_WIN_INFO_S stWinInfo;
    HI_S32 Ret;

    if (HI_SUCCESS != WIN_GetInfo(hWindow, &stWinInfo))
    {
        HI_ERR_WIN("Window dose not exist!\n");
        return HI_ERR_VO_WIN_NOT_EXIST;
    }

    if (stWinInfo.eType == HI_DRV_WIN_VITUAL_SINGLE)
    {
        // if virtual window, remove proc and destory.
        Ret = WIN_RemFromProc(hWindow);
        if (Ret)
        {
            HI_ERR_WIN("WIN_RemFromProc failed!\n");
        }

        Ret = WIN_Destroy(hWindow);
        if (Ret != HI_SUCCESS)
        {
            HI_FATAL_WIN("call WIN_Destroy failed.\n");
        }

        WIN_RemFromState(pstWinState, HI_TRUE, hWindow);
    }
    else
    {
        if (stWinInfo.hSec)
        {
            // if have slave window, remove slave window proc firstly
            Ret = WIN_RemFromProc(stWinInfo.hSec);
            if (Ret)
            {
                HI_ERR_WIN("WIN_RemFromProc slave failed!\n");
            }
        }

        // remove proc and destory window
        Ret = WIN_RemFromProc(hWindow);
        if (Ret)
        {
            HI_ERR_WIN("WIN_RemFromProc failed!\n");
        }

        Ret = WIN_Destroy(hWindow);
        if (Ret != HI_SUCCESS)
        {
            HI_FATAL_WIN("call WIN_Destroy failed.\n");
        }

        WIN_RemFromState(pstWinState, HI_FALSE, hWindow);
    }

    return Ret;
}

HI_S32 WIN_CheckHanlde(HI_HANDLE hWindow, WIN_STATE_S *pstWinState)
{
    if (HI_NULL == pstWinState)
    {
        HI_ERR_WIN("pstWinState is NULL\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_S32 WIN_GetAttachFunc(HI_DRV_WIN_SRC_INFO_S *pstWinSrc, HI_MOD_ID_E enModID)
{
    VDEC_EXPORT_FUNC_S *pstVdecFunc = HI_NULL;
    VI_EXPORT_FUNC_S *pstViFunc = HI_NULL;
    HI_S32 s32Ret;
    HI_HANDLE hSrc;

    hSrc = pstWinSrc->hSrc;

    if (hSrc == HI_INVALID_HANDLE)
    {
        pstWinSrc->pfAcqFrame = HI_NULL;
        pstWinSrc->pfRlsFrame = HI_NULL;
        pstWinSrc->pfSendWinInfo = HI_NULL;

        return HI_SUCCESS;
    }

    if ( HI_ID_VDEC == enModID)
    {
        s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_VDEC, (HI_VOID **) & (pstVdecFunc));
        if (HI_SUCCESS != s32Ret || pstVdecFunc == HI_NULL)
        {
            WIN_ERROR("get vdec func error.\n");
            return HI_FAILURE;
        }

        pstWinSrc->pfAcqFrame = HI_NULL;
        pstWinSrc->pfRlsFrame = pstVdecFunc->pfnVORlsFrame;
        pstWinSrc->pfSendWinInfo = pstVdecFunc->pfnVOSendWinInfo;

        s32Ret = HI_SUCCESS;
    }
    else if ( HI_ID_VI == enModID )
    {
        s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_VI, (HI_VOID **) & (pstViFunc));
        if (HI_SUCCESS != s32Ret || pstViFunc == HI_NULL)
        {
            WIN_ERROR("get vi func error,s32Ret:%x,pstViFunc:%p\n", s32Ret, pstViFunc);
            return HI_FAILURE;
        }

        pstWinSrc->pfAcqFrame = pstViFunc->pfnVOAcqFrame;
        pstWinSrc->pfRlsFrame = pstViFunc->pfnVORlsFrame;
        pstWinSrc->pfSendWinInfo = pstViFunc->pfnVOSendWinInfo;

        s32Ret = HI_SUCCESS;
    }
    else
    {
        WIN_ERROR("enModID %#x is invalid.\n", enModID);
        s32Ret = HI_FAILURE;
    }

    return s32Ret;

}

static HI_S32 WINProcessCmdCreate( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_CREATE_S  *pVoWinCreate;

    pVoWinCreate = (WIN_CREATE_S *)arg;

    Ret = WIN_CreateExt(pVoWinCreate, pstWinState);
    WIN_WARN("creat win0x%x,v(%d) out->(%d,%d,%d,%d)\n", \
             pVoWinCreate->hWindow, \
             pVoWinCreate->bVirtScreen, \
             pVoWinCreate->WinAttr.stOutRect.s32X, \
             pVoWinCreate->WinAttr.stOutRect.s32Y, \
             pVoWinCreate->WinAttr.stOutRect.s32Width, \
             pVoWinCreate->WinAttr.stOutRect.s32Height);

    return Ret;
}

static HI_S32 WINProcessCmdDestroy( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;

    Ret = WIN_CheckHanlde(*((HI_HANDLE *)arg), pstWinState);

    if (HI_SUCCESS == Ret)
    {
        HI_BOOL bSinkAttached = HI_TRUE;
        HI_BOOL bSrcAttached = HI_TRUE;
        HI_HANDLE hWindow = HI_INVALID_HANDLE;
        hWindow = *((HI_HANDLE *)arg);
        Ret = WIN_CheckAttachState(hWindow, &bSrcAttached, &bSinkAttached);

        if (HI_SUCCESS != Ret)
        {
            WIN_ERROR("Can't Get window's attachState\n");
            return HI_ERR_VO_INVALID_OPT;
        }

        if (bSrcAttached == HI_TRUE || bSinkAttached == HI_TRUE)
        {
            WIN_ERROR("Window is still attached,Can't be destoryed."
                      "bSrcAttached %d,bSinkAttached %d\n", bSrcAttached, bSinkAttached);
            return HI_ERR_VO_INVALID_OPT;
        }

        Ret = WIN_DestroyExt(*((HI_HANDLE *)arg), pstWinState);
        WIN_WARN("destroy win0x%xd--ret %d.\n", hWindow, Ret);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetEnable( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ENABLE_S   *pWinEnable;

    pWinEnable = (WIN_ENABLE_S *)arg;

    Ret = WIN_CheckHanlde(pWinEnable->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {

        Ret = WIN_SetEnable(pWinEnable->hWindow, pWinEnable->bEnable);
        WIN_WARN("set win0x%x, enable->%d\n", pWinEnable->hWindow, pWinEnable->bEnable);
    }

    return Ret;
}

static HI_S32 WINProcessCmdGetEnable( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ENABLE_S   *pVoWinEnable;

    pVoWinEnable = (WIN_ENABLE_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinEnable->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetEnable(pVoWinEnable->hWindow, &pVoWinEnable->bEnable);
    }

    return Ret;
}

static HI_S32 WINProcessCmdVirAcquire( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FRAME_S   *pVoWinFrame;
    pVoWinFrame = (WIN_FRAME_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFrame->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_AcquireFrame(pVoWinFrame->hWindow, &pVoWinFrame->stFrame);
    }

    return Ret;
}

static HI_S32 WINProcessCmdVirRelease( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FRAME_S   *pVoWinFrame;
    pVoWinFrame = (WIN_FRAME_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFrame->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_ReleaseFrame(pVoWinFrame->hWindow, &pVoWinFrame->stFrame);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetAttr( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_CREATE_S *pVoWinAttr;

    pVoWinAttr = (WIN_CREATE_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinAttr->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetAttr(pVoWinAttr->hWindow, &pVoWinAttr->WinAttr);
    }
    WIN_WARN("set attr win0x%x, out->(%d,%d,%d,%d)\n", pVoWinAttr->hWindow, \
             pVoWinAttr->WinAttr.stOutRect.s32X, \
             pVoWinAttr->WinAttr.stOutRect.s32Y, \
             pVoWinAttr->WinAttr.stOutRect.s32Width, \
             pVoWinAttr->WinAttr.stOutRect.s32Height);

    return Ret;
}

static HI_S32 WINProcessCmdGetAttr( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_CREATE_S   *pVoWinAttr;

    pVoWinAttr = (WIN_CREATE_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinAttr->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetAttr(pVoWinAttr->hWindow, &pVoWinAttr->WinAttr);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetZorder( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ZORDER_S *pVoWinZorder;

    pVoWinZorder = (WIN_ZORDER_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinZorder->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetZorder(pVoWinZorder->hWindow, pVoWinZorder->eZFlag);
    }
    WIN_WARN("set zorder win0x%x, ZFlag->%d\n", pVoWinZorder->hWindow, pVoWinZorder->eZFlag);

    return Ret;
}

static HI_S32 WINProcessCmdGetOrder( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ORDER_S *pVoWinOrder;

    pVoWinOrder = (WIN_ORDER_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinOrder->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetZorder(pVoWinOrder->hWindow, &pVoWinOrder->Order);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetSource( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_SOURCE_S *pVoWinAttach;
    HI_DRV_WIN_SRC_INFO_S stWinSrc = {0};
    HI_MOD_ID_E enSrcModID;
    pVoWinAttach = (WIN_SOURCE_S *)arg;

    stWinSrc.hSrc = pVoWinAttach->stSrc.hSrc;
    stWinSrc.hSecondSrc = pVoWinAttach->stSrc.hSecondSrc;
    enSrcModID = pVoWinAttach->stSrc.enSrcMode;

    Ret = WIN_GetAttachFunc(&stWinSrc, enSrcModID);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetSource(pVoWinAttach->hWindow,
                            &stWinSrc);
    }

    WIN_WARN("set source win0x%x, hSrc->%d\n", pVoWinAttach->hWindow, stWinSrc.hSrc);

    return Ret;
}

static HI_S32 WINProcessCmdGetSource( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_SOURCE_S *pVoWinAttach;
    HI_DRV_WIN_SRC_INFO_S stSrcInfo;
    pVoWinAttach = (WIN_SOURCE_S *)arg;

    Ret = WIN_GetSource(pVoWinAttach->hWindow, &stSrcInfo);
    if (HI_SUCCESS == Ret)
    {
        pVoWinAttach->stSrc.hSrc = stSrcInfo.hSrc;
        pVoWinAttach->stSrc.hSecondSrc = stSrcInfo.hSecondSrc;
    }

    return Ret;
}

static HI_S32 WINProcessCmdFreeze( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FREEZE_S  *pVoWinFreeze;

    pVoWinFreeze = (WIN_FREEZE_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFreeze->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_Freeze(pVoWinFreeze->hWindow, pVoWinFreeze->bEnable, pVoWinFreeze->eMode);
    }

    return Ret;
}

static HI_S32 WINProcessCmdGetFreezeStatus( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FREEZE_S  *pVoWinFreeze;

    pVoWinFreeze = (WIN_FREEZE_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFreeze->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetFreezeStatus(pVoWinFreeze->hWindow, &pVoWinFreeze->bEnable, &pVoWinFreeze->eMode);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSendFrame( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FRAME_S   *pVoWinFrame;

    pVoWinFrame = (WIN_FRAME_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFrame->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SendFrame(pVoWinFrame->hWindow, &pVoWinFrame->stFrame);
    }

    return Ret;
}

static HI_S32 WINProcessCmdQuFrame( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FRAME_S   *pVoWinFrame;
    pVoWinFrame = (WIN_FRAME_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinFrame->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_QueueFrame(pVoWinFrame->hWindow, &pVoWinFrame->stFrame, &pVoWinFrame->stDolbyHdrCfg);
    }

    return Ret;
}

static HI_S32 WINProcessCmdQuDolbyFrame( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_DOLBYFRAME_S    *pVoWinDoviFrm;
    pVoWinDoviFrm = (WIN_DOLBYFRAME_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinDoviFrm->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WinQueueDolbyFrame(pVoWinDoviFrm->hWindow,
                                 &pVoWinDoviFrm->stBLFrm,
                                 &pVoWinDoviFrm->stELFrm,
                                 pVoWinDoviFrm->bELValid,
                                 &pVoWinDoviFrm->stDolbyInfo);
    }

    return Ret;
}

static HI_S32 WINProcessCmdQuSyncFrame( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_SYNCFRAME_S  *pVoWinFrame;

    pVoWinFrame = (WIN_SYNCFRAME_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFrame->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_QueueSyncFrame(pVoWinFrame->hWindow, &pVoWinFrame->stFrame, &pVoWinFrame->u32FenceFd);
    }

    return Ret;
}

static HI_S32 WINProcessCmdQuULSFrame( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FRAME_S   *pVoWinFrame;
    pVoWinFrame = (WIN_FRAME_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFrame->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_QueueUselessFrame(pVoWinFrame->hWindow, &pVoWinFrame->stFrame);
    }

    return Ret;
}

static HI_S32 WINProcessCmdDqFrame( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FRAME_S     *pVoWinFrame;

    pVoWinFrame = (WIN_FRAME_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinFrame->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_DequeueFrame(pVoWinFrame->hWindow, &pVoWinFrame->stFrame);
    }

    return Ret;
}

static HI_S32 WINProcessCmdReset( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_RESET_S  *pVoWinReset;

    pVoWinReset = (WIN_RESET_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinReset->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_Reset(pVoWinReset->hWindow, pVoWinReset->eMode);
    }

    WIN_WARN("win reset win0x%x, %s\n", pVoWinReset->hWindow, HI_DRV_WIN_SWITCH_LAST == pVoWinReset->eMode ? "last" : "black");

    return Ret;
}

static HI_S32 WINProcessCmdPause( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_PAUSE_S  *pVoWinPause;

    pVoWinPause = (WIN_PAUSE_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinPause->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_Pause(pVoWinPause->hWindow, pVoWinPause->bEnable);
    }

    WIN_WARN("win pause win0x%x, bEnable->%d\n", pVoWinPause->hWindow, pVoWinPause->bEnable);

    return Ret;
}

static HI_S32 WINProcessCmdGetPlayInfo( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_PLAY_INFO_S  *pVoWinDelay;

    pVoWinDelay = (WIN_PLAY_INFO_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinDelay->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetPlayInfo(pVoWinDelay->hWindow, &pVoWinDelay->stPlayInfo);
    }

    return Ret;
}

static HI_S32 WINProcessCmdGetInfo( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_PRIV_INFO_S  *pVoWinDelay;

    pVoWinDelay = (WIN_PRIV_INFO_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinDelay->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetInfo(pVoWinDelay->hWindow, &pVoWinDelay->stPrivInfo);
    }

    return Ret;
}

static HI_S32 WINProcessCmdStepMode( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_STEP_MODE_S  *pVoWinStepMode;

    pVoWinStepMode = (WIN_STEP_MODE_S *)arg;

    Ret = WIN_CheckHanlde(pVoWinStepMode->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetStepMode(pVoWinStepMode->hWindow, pVoWinStepMode->bStep);
    }

    WIN_WARN("win step mode win0x%x, bStep->%d\n", pVoWinStepMode->hWindow, pVoWinStepMode->bStep);

    return Ret;
}

static HI_S32 WINProcessCmdStepPlay( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;

    Ret = WIN_CheckHanlde(*((HI_HANDLE *)arg), pstWinState);

    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetStepPlay(*((HI_HANDLE *)arg));
    }

    WIN_WARN("win step play win0x%x,ret %d\n", *((HI_HANDLE *)arg), Ret);

    return Ret;
}

static HI_S32 WINProcessCmdVirExternBuf( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_BUF_POOL_S      *winBufAttr = (WIN_BUF_POOL_S *)arg;

    Ret = WIN_CheckHanlde(winBufAttr->hwin, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetExtBuffer(winBufAttr->hwin, &winBufAttr->stBufPool);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetQuick( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_SET_QUICK_S *pstQuickOutputAttr = (WIN_SET_QUICK_S *)arg;
    Ret = WIN_CheckHanlde(pstQuickOutputAttr->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetQuick(pstQuickOutputAttr->hWindow, pstQuickOutputAttr->bQuickEnable);
    }

    WIN_WARN("win quit win0x%x, bEnable->%d\n", pstQuickOutputAttr->hWindow, pstQuickOutputAttr->bQuickEnable);

    return Ret;
}

static HI_S32 WINProcessCmdGetQuick( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_SET_QUICK_S *pstQuickOutputAttr = (WIN_SET_QUICK_S *)arg;
    Ret = WIN_CheckHanlde(pstQuickOutputAttr->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetQuick(pstQuickOutputAttr->hWindow, &pstQuickOutputAttr->bQuickEnable);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSuspend( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    Ret = WIN_Suspend();

    WIN_WARN("win suspend!\n");

    return Ret;
}

static HI_S32 WINProcessCmdResum( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    Ret = WIN_Resume();

    WIN_WARN("win resum!\n");

    return Ret;
}

static HI_S32 WINProcessCmdGetHandle( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_HANDLE_ARRAY_S stWinArray;
    WIN_GET_HANDLE_S *pWin = (WIN_GET_HANDLE_S *)arg;

    Ret = Win_DebugGetHandle(pWin->enDisp, &stWinArray);
    if (Ret == HI_SUCCESS)
    {
        HI_S32 i;

        pWin->u32WinNumber = stWinArray.u32WinNumber;

        for (i = 0; (i < pWin->u32WinNumber) && (i < DEF_MAX_WIN_NUM_ON_SINGLE_DISP); i++)
        {
            pWin->ahWinHandle[i] = stWinArray.ahWinHandle[i];
        }
    }

    return Ret;

}

static HI_S32 WINProcessCmdAttach( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ATTACH_S *pstAttach;
    pstAttach = (WIN_ATTACH_S *)arg;

    if (pstAttach->enType == ATTACH_TYPE_SINK)
    {
        Ret = WIN_AttachSink(pstAttach->hWindow, pstAttach->hMutual);
    }
    else
    {
        Ret = HI_FAILURE;
    }

    WIN_WARN("win attach win0x%x, sink->%d\n", pstAttach->hWindow, pstAttach->hMutual);

    return Ret;
}

static HI_S32 WINProcessCmdDetach( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ATTACH_S *pstAttach;
    pstAttach = (WIN_ATTACH_S *)arg;

    if (pstAttach->enType == ATTACH_TYPE_SINK)
    {
        Ret = WIN_DetachSink(pstAttach->hWindow, pstAttach->hMutual);
    }
    else
    {
        Ret = HI_FAILURE;
    }

    WIN_WARN("win detach win0x%x, sink->%d\n", pstAttach->hWindow, pstAttach->hMutual);

    return Ret;
}

static HI_S32 WINProcessCmdGetLatestFrameInfo( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FRAME_S *frame_info;
    frame_info = (WIN_FRAME_S *)arg;
    Ret = WinGetCurrentImg(frame_info->hWindow, &frame_info->stFrame);

    return Ret;
}

static HI_S32 WINProcessCmdCaptureStart( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_CAPTURE_S *capture_info = HI_NULL;
    HI_DRV_DISPLAY_E enDisp;
    HI_U32 u32WinIndex;

    capture_info = (WIN_CAPTURE_S *)arg;

    (HI_VOID)WinGetIndex(capture_info->hWindow, &enDisp, &u32WinIndex);

    if (enDisp >= HI_DRV_DISPLAY_BUTT || u32WinIndex >= DEF_MAX_WIN_NUM_ON_SINGLE_DISP)
    {
        WIN_ERROR("enDisp or u32WinIndex out of range\n");
        return HI_FAILURE;
    }

    pstWinState->hCapture[enDisp][u32WinIndex] = capture_info->hWindow;

    Ret = WinCapturePause(capture_info->hWindow, 1);
    if (HI_SUCCESS != Ret)
    {
        pstWinState->hCapture[enDisp][u32WinIndex] = 0;
        return Ret;
    }

    Ret = WinCaptureFrame(capture_info->hWindow,
                          &capture_info->CapPicture,
                          &capture_info->driver_supply_addr.startPhyAddr,
                          &capture_info->driver_supply_addr.length);

    if (HI_SUCCESS != Ret)
    {
        pstWinState->hCapture[enDisp][u32WinIndex] = 0;
        WinCapturePause(capture_info->hWindow, 0);
    }

    WIN_WARN("win capture start win0x%x,addr->0x%x,ret %d\n", capture_info->hWindow, capture_info->CapPicture.stBufAddr[0].u32PhyAddr_Y, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdCaptureRelease( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_CAPTURE_S *capture_info = HI_NULL;
    HI_DRV_DISPLAY_E enDisp;
    HI_U32 u32WinIndex;

    capture_info = (WIN_CAPTURE_S *)arg;
    (HI_VOID)WinGetIndex(capture_info->hWindow, &enDisp, &u32WinIndex);

    Ret = WinReleaseCaptureFrame(capture_info->hWindow, &capture_info->CapPicture);

    if ( enDisp >= HI_DRV_DISPLAY_BUTT || u32WinIndex >= DEF_MAX_WIN_NUM_ON_SINGLE_DISP)
    {
        WIN_ERROR("enDisp or u32WinIndex out of range\n");
        return HI_FAILURE;
    }

    if (HI_SUCCESS != Ret)
    {
        pstWinState->hCapture[enDisp][u32WinIndex] = 0;
    }

    Ret = WinCapturePause(capture_info->hWindow, 0);
    if (HI_SUCCESS != Ret)
    {
        pstWinState->hCapture[enDisp][u32WinIndex] = 0;
    }

    WIN_WARN("win capture release win0x%x,addr->0x%x,ret %d\n", capture_info->hWindow, capture_info->CapPicture.stBufAddr[0].u32PhyAddr_Y, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdCaptureFree( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_CAPTURE_S *capture_info = HI_NULL;
    HI_DRV_DISPLAY_E enDisp;
    HI_U32 u32WinIndex;

    capture_info = (WIN_CAPTURE_S *)arg;

    (HI_VOID)WinGetIndex(capture_info->hWindow, &enDisp, &u32WinIndex);

    if (enDisp >= HI_DRV_DISPLAY_BUTT || u32WinIndex >= DEF_MAX_WIN_NUM_ON_SINGLE_DISP)
    {
        WIN_ERROR("enDisp or WinIndex out of range\n");
        return HI_FAILURE;
    }

    pstWinState->hCapture[enDisp][u32WinIndex] = 0;

    Ret = WinFreeCaptureMMZBuf(capture_info->hWindow, &capture_info->CapPicture);

    WIN_WARN("win capture free win0x%x,addr->0x%x,ret %d\n", capture_info->hWindow, capture_info->CapPicture.stBufAddr[0].u32PhyAddr_Y, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdSetRotation( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ROTATION_S *pVoWinRotation;
    pVoWinRotation = (WIN_ROTATION_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinRotation->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetRotation(pVoWinRotation->hWindow, pVoWinRotation->enRotation);
    }

    WIN_WARN("win set rotation win0x%x,rotation->0x%x,ret %d\n", pVoWinRotation->hWindow, pVoWinRotation->enRotation, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdGetRotation( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ROTATION_S *pVoWinRotation;
    pVoWinRotation = (WIN_ROTATION_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinRotation->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetRotation(pVoWinRotation->hWindow, &(pVoWinRotation->enRotation));
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetFlip( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FLIP_S *pVoWinFlip;

    pVoWinFlip = (WIN_FLIP_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinFlip->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetFlip(pVoWinFlip->hWindow, pVoWinFlip->bHoriFlip, pVoWinFlip->bVertFlip);
    }

    WIN_WARN("win set flip win0x%x,rotation->0x%x,ret %d\n", pVoWinFlip->hWindow, pVoWinFlip->bHoriFlip, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdGetFlip( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FLIP_S *pVoWinFlip;
    pVoWinFlip = (WIN_FLIP_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinFlip->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetFlip(pVoWinFlip->hWindow,
                          &(pVoWinFlip->bHoriFlip),
                          &(pVoWinFlip->bVertFlip));
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetFrostMode( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FROST_MODE_S *pWinFrostMode;
    pWinFrostMode = (WIN_FROST_MODE_S *)arg;

    Ret = WIN_CheckHanlde(pWinFrostMode->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetFrostMode(pWinFrostMode->hWindow, pWinFrostMode->eFrostMode);
    }

    WIN_WARN("win set frostmode win0x%x,eFrostMode->0x%x,ret %d\n", pWinFrostMode->hWindow, pWinFrostMode->eFrostMode, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdGetFrostMode( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_FROST_MODE_S *pWinFrostMode;
    pWinFrostMode = (WIN_FROST_MODE_S *)arg;

    Ret = WIN_CheckHanlde(pWinFrostMode->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetFrostMode(pWinFrostMode->hWindow, &pWinFrostMode->eFrostMode);
    }

    return Ret;
}

static HI_S32 WINProcessCmdSetMode( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_MODE_S *pVoWinMode;
    pVoWinMode = (WIN_MODE_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinMode->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetMode(pVoWinMode->hWindow, pVoWinMode->enWinMode);
    }

    WIN_INFO("win set mode win0x%x,eFrostMode->0x%x,ret %d\n", pVoWinMode->hWindow, pVoWinMode->enWinMode, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdGetDispOutType( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_DISP_OUT_TYPE_S *pVoWinDispOutType;
    pVoWinDispOutType = (WIN_DISP_OUT_TYPE_S *)arg;
    Ret = WIN_CheckHanlde(pVoWinDispOutType->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetDispOutput(pVoWinDispOutType->hWindow, &pVoWinDispOutType->enDispOutType);
    }

    return Ret;
}

static HI_S32 WINProcessCmdGetDispOutTypeAndGFXState( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_DISP_OUT_TYPE_AND_GFX_STATE_S *pstWinDispTypeGfxState;
    pstWinDispTypeGfxState = (WIN_DISP_OUT_TYPE_AND_GFX_STATE_S *)arg;
    Ret = WIN_CheckHanlde(pstWinDispTypeGfxState->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetDispOutputAndGfxState(pstWinDispTypeGfxState->hWindow,
                                           &pstWinDispTypeGfxState->enDispOutType,
                                           &pstWinDispTypeGfxState->bNeedProcessGfx);
    }

    return Ret;
}

static HI_S32 WINProcessCmdGetUnload( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_UNLOAD_S *pWinUnload;
    pWinUnload = (WIN_UNLOAD_S *)arg;
    Ret = WIN_CheckHanlde(pWinUnload->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetUnload(pWinUnload->hWindow,
                            &(pWinUnload->u32Times));
    }

    return Ret;
}

static HI_S32 WINProcessCmdCloseHDRPath( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_ENABLE_S *pstWinHdrEnable;
    pstWinHdrEnable = (WIN_ENABLE_S *)arg;
    Ret = WIN_CheckHanlde(pstWinHdrEnable->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_CloseHdrPath(pstWinHdrEnable->hWindow, pstWinHdrEnable->bEnable);
    }

    WIN_WARN("win set mode win0x%x,bEnable->0x%x,ret %d\n", pstWinHdrEnable->hWindow, pstWinHdrEnable->bEnable, Ret);

    return Ret;
}

static HI_S32 WINProcessCmdSetDolbyLibStatus( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_DOLBY_LIB_INFO_S *pstWinDolbyLibInfo;
    pstWinDolbyLibInfo = (WIN_DOLBY_LIB_INFO_S *)arg;
    Ret = WIN_SetDolbyLibInfo(pstWinDolbyLibInfo);

    return Ret;
}

static HI_S32 WINProcessCmdSetAlpha( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
	HI_S32 Ret = HI_SUCCESS;

    WIN_ALPHA_S *pstWinAlpha = HI_NULL ;
     
    pstWinAlpha = (WIN_ALPHA_S *)arg;
    Ret = WIN_CheckHanlde(pstWinAlpha->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_SetWindowAlpha(pstWinAlpha->hWindow,pstWinAlpha->u32Alpha);
    }

    return Ret;
}
static HI_S32 WINProcessCmdGetAlpha( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
	HI_S32 Ret = HI_SUCCESS;

    WIN_ALPHA_S *pstWinAlpha = HI_NULL ;
     
    pstWinAlpha = (WIN_ALPHA_S *)arg;
    Ret = WIN_CheckHanlde(pstWinAlpha->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WIN_GetWindowAlpha(pstWinAlpha->hWindow,&pstWinAlpha->u32Alpha);
    }

    return Ret;
}

static HI_S32 WINProcessCmdDebug( HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = HI_SUCCESS;
    WIN_DEBUG_CMD_AND_ARGS_S *pstWinDebugCmd;
    pstWinDebugCmd = (WIN_DEBUG_CMD_AND_ARGS_S *)arg;
    Ret = WIN_CheckHanlde(pstWinDebugCmd->hWindow, pstWinState);
    if (HI_SUCCESS == Ret)
    {
        Ret = WinDebugCmdProcess(pstWinDebugCmd);
    }

    return Ret;
}

HI_S32 WIN_ProcessCmd(unsigned int cmd, HI_VOID *arg, WIN_STATE_S *pstWinState)
{
    HI_S32 Ret = -ENOIOCTLCMD;
    HI_S8 s8Index = 0;

    if ((HI_NULL == arg) || (HI_NULL == pstWinState))
    {
        HI_FATAL_WIN("pass null ptr.\n");
        Ret = HI_ERR_DISP_NULL_PTR;
        return Ret;
    }

    for (s8Index = 0; (s8Index < sizeof(s_aWINCmdFuncTab) / sizeof(stWINProcessCmdFunc)); s8Index++)
    {
        if ((s_aWINCmdFuncTab[s8Index].cmd) == cmd &&
            (HI_NULL != s_aWINCmdFuncTab[s8Index].pWIN_ProcessCmdFunc))
        {
            Ret = s_aWINCmdFuncTab[s8Index].pWIN_ProcessCmdFunc(arg, pstWinState);

            break;
        }
    }

    return Ret;
}

extern HI_U32 DISP_Get_CountStatus(HI_VOID);

HI_S32 DRV_WIN_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    HI_S32  Ret;

    Ret = down_interruptible(&g_VoMutex);
    if (Ret)
    {
        HI_FATAL_WIN("down g_VoMutex failed.\n");
        return -1;
    }

    /* just return if no task opened the vo device.*/
#if 0
    if ( !atomic_read(&g_VoCount) )
    {
        up(&g_VoMutex);
        return 0;
    }
#endif

    g_VoSuspend = HI_TRUE;
    WIN_Suspend();

    msleep(50);

    HI_PRINT("VO suspend OK\n");

    up(&g_VoMutex);
    return 0;
}

HI_S32 DRV_WIN_Resume(PM_BASEDEV_S *pdev)
{
    HI_S32  Ret;

    Ret = down_interruptible(&g_VoMutex);
    if (Ret)
    {
        HI_FATAL_WIN("down g_VoMutex failed.\n");
        return -1;
    }

#if 0
    if (!atomic_read(&g_VoCount))
    {
        up(&g_VoMutex);
        return 0;
    }
#endif

    WIN_Resume();
    g_VoSuspend = HI_FALSE;

    HI_PRINT("VO resume OK\n");

    up(&g_VoMutex);
    return 0;
}

HI_S32 DRV_WIN_Process(HI_U32 cmd, HI_VOID *arg)
{
    WIN_STATE_S   *pstWinState;
    HI_S32        Ret;

    Ret = down_interruptible(&g_VoMutex);

    pstWinState = &g_VoModState;

    Ret = WIN_ProcessCmd(cmd, arg, pstWinState);

    up(&g_VoMutex);
    return Ret;
}

/*add for mce interface*/
HI_S32  HI_DRV_WIN_Create(HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWindow)
{
    HI_S32 Ret;
    WIN_CREATE_S voWinCreate = {0};

    WinCheckNullPointer(pWinAttr);
    WinCheckNullPointer(phWindow);

    voWinCreate.hWindow = *phWindow;
    voWinCreate.WinAttr = *pWinAttr;
    voWinCreate.bMCE = HI_TRUE;
    voWinCreate.bVirtScreen = HI_TRUE;

    Ret = DRV_WIN_Process(CMD_WIN_CREATE, &voWinCreate);
    *phWindow = voWinCreate.hWindow;
    return Ret;
}


HI_S32 HI_DRV_WIN_Destroy(HI_HANDLE hWindow)
{
    HI_S32 Ret;

    Ret = DRV_WIN_Process(CMD_WIN_DESTROY, &hWindow);
    return Ret;
}

HI_S32 HI_DRV_WIN_SetEnable(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    HI_S32 Ret;
    WIN_ENABLE_S   stVoWinEnable;

    stVoWinEnable.bEnable = bEnable;
    stVoWinEnable.hWindow = hWindow;

    Ret = DRV_WIN_Process(CMD_WIN_SET_ENABLE, &stVoWinEnable);
    return Ret;
}

HI_S32 HI_DRV_WIN_GetEnable(HI_HANDLE hWindow, HI_BOOL *pbEnable)
{
    HI_S32 Ret;
    WIN_ENABLE_S   stVoWinEnable = {0};
    memset(&stVoWinEnable, 0, sizeof(WIN_ENABLE_S));

    WinCheckNullPointer(pbEnable);

    stVoWinEnable.hWindow = hWindow;

    Ret = DRV_WIN_Process(CMD_WIN_GET_ENABLE, &stVoWinEnable);
    if (!Ret)
    {
        *pbEnable = stVoWinEnable.bEnable;
    }
    return Ret;
}


HI_S32 HI_DRV_WIN_SetSource(HI_HANDLE hWindow, HI_DRV_WIN_SRC_HANDLE_S *pstSrc)
{
    HI_S32 Ret;
    WIN_SOURCE_S VoWinAttach;

    WinCheckNullPointer(pstSrc);

    VoWinAttach.hWindow = hWindow;
    VoWinAttach.stSrc.hSrc   = pstSrc->hSrc;
    VoWinAttach.stSrc.hSecondSrc = pstSrc->hSecondSrc;
    VoWinAttach.stSrc.enSrcMode = pstSrc->enSrcMode;
    //  printk("------HI_DRV_WIN_SetSource-win->0x%x----handle-0x%x\n",hWindow,pstSrc->hSrc);
    Ret = DRV_WIN_Process(CMD_WIN_SET_SOURCE, &VoWinAttach);
    return Ret;
}

HI_S32 HI_DRV_WIN_GetSource(HI_HANDLE hWindow, HI_DRV_WIN_SRC_HANDLE_S *pstSrc)
{
    return HI_ERR_VO_WIN_UNSUPPORT;
}


HI_S32 HI_DRV_WIN_Reset(HI_HANDLE hWindow, HI_DRV_WIN_SWITCH_E enSwitch)
{
    HI_S32 Ret;
    WIN_RESET_S   VoWinReset;

    VoWinReset.hWindow = hWindow;
    VoWinReset.eMode   = enSwitch;
    Ret = DRV_WIN_Process(CMD_WIN_RESET, &VoWinReset);
    return Ret;
}

HI_S32 HI_DRV_WIN_Pause(HI_HANDLE hWin, HI_BOOL bEnable)
{
    HI_S32 Ret;
    WIN_PAUSE_S   stWinPause;

    stWinPause.hWindow = hWin;
    stWinPause.bEnable = bEnable;
    Ret = DRV_WIN_Process(CMD_WIN_PAUSE, &stWinPause);
    return Ret;
}

HI_S32 HI_DRV_WIN_SetStepMode(HI_HANDLE hWin, HI_BOOL bStepMode)
{
    HI_S32 Ret;
    WIN_STEP_MODE_S   stMode;

    stMode.hWindow = hWin;
    stMode.bStep = bStepMode;
    Ret = DRV_WIN_Process(CMD_WIN_STEP_MODE, &bStepMode);
    return Ret;
}

HI_S32 HI_DRV_WIN_SetStepPlay(HI_HANDLE hWin)
{

    return DRV_WIN_Process(CMD_WIN_STEP_PLAY, &hWin);

}

HI_S32 HI_DRV_WIN_SetExtBuffer(HI_HANDLE hWin, HI_DRV_VIDEO_BUFFER_POOL_S *pstBuf)
{
    HI_S32 Ret;

    WinCheckNullPointer(pstBuf);

    Ret  = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        HI_FATAL_WIN("down g_VoMutex failed.\n");
        return Ret;
    }

    Ret  = WIN_SetExtBuffer(hWin, pstBuf);

    up(&g_VoMutex);
    return Ret;
}

HI_S32 HI_DRV_WIN_AcquireFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    HI_S32 Ret;

    WinCheckNullPointer(pFrameinfo);

    Ret  = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        HI_FATAL_WIN("down g_VoMutex failed.\n");
        return Ret;
    }

    Ret  = WIN_AcquireFrame(hWin, pFrameinfo);

    up(&g_VoMutex);
    return Ret;
}

HI_S32 HI_DRV_WIN_ReleaseFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    HI_S32 Ret;
    WinCheckNullPointer(pFrameinfo);

    Ret = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        HI_FATAL_WIN("down g_VoMutex failed.\n");
        return Ret;
    }

    Ret  = WIN_ReleaseFrame(hWin, pFrameinfo);

    up(&g_VoMutex);
    return Ret;
}

HI_S32 HI_DRV_WIN_SetQuick(HI_HANDLE hWin, HI_BOOL bEnable)
{
    HI_S32 Ret;
    WIN_SET_QUICK_S   stQuik;

    stQuik.hWindow = hWin;
    stQuik.bQuickEnable = bEnable;
    Ret = DRV_WIN_Process(CMD_WIN_SET_QUICK, &stQuik);
    return Ret;
}

HI_S32 Make_CaptureFrame(HI_DRV_VIDEO_FRAME_S *pFrameinfo, HI_DRV_VIDEO_FRAME_S *pCapFrameinfo)
{
    HI_U32 datalen = 0, y_stride = 0, height = 0 ;
    HI_U32 u32StillFrameStartPhyAddr, u32FrameStartPhyAddr;
    HI_U8  *pu8StillFrameStartVirAddr = HI_NULL, *pu8FrameStartVirAddr = HI_NULL;
    HI_S32 nRet = 0;
    DISP_MMZ_BUF_S  stMMZ_Frame;

    if (!pCapFrameinfo)
    {
        HI_ERR_WIN("para null!\n");
        return HI_FAILURE;
    }
    if (!pFrameinfo)
    {
        HI_ERR_WIN("para null!\n");
        return HI_FAILURE;
    }

    /*1:calculate data long*/
    y_stride = pFrameinfo->stBufAddr[0].u32Stride_Y;
    height   = pFrameinfo->u32Height;

    if ( HI_DRV_PIX_FMT_NV21 == pFrameinfo->ePixFormat)
    {
        datalen = height * y_stride * 3 / 2 ;
    }
    else if (HI_DRV_PIX_FMT_NV21_CMP == pFrameinfo->ePixFormat)
    {
        datalen = height * y_stride * 3 / 2 + 16 * height * 3 / 2;
    }
    else if (HI_DRV_PIX_FMT_NV61_2X1 == pFrameinfo->ePixFormat)
    {
        datalen = height * y_stride * 2 + height * 4;
    }
    else
    {
        HI_ERR_WIN("Invalid Format %d!\n", pFrameinfo->ePixFormat);
        return HI_FAILURE;
    }
    //printk("make --str-%d,h--%d --long %d--\n",y_stride,height,datalen);
    /*2: creat still frame*/
    u32StillFrameStartPhyAddr = pCapFrameinfo->stBufAddr[0].u32PhyAddr_Y;
    u32FrameStartPhyAddr = pFrameinfo->stBufAddr[0].u32PhyAddr_Y;

    memset(&stMMZ_Frame, 0, sizeof(DISP_MMZ_BUF_S));

    stMMZ_Frame.u32StartPhyAddr = pCapFrameinfo->stBufAddr[0].u32PhyAddr_Y;
    stMMZ_Frame.u32Size = datalen;
    stMMZ_Frame.bSmmu = HI_TRUE;

    nRet = DISP_OS_MMZ_Map(&stMMZ_Frame);
    if (HI_SUCCESS != nRet)
    {
        return HI_ERR_VO_MALLOC_FAILED;
    }

    pu8StillFrameStartVirAddr = stMMZ_Frame.pu8StartVirAddr;

#ifdef  CFG_VDP_MMU_SUPPORT
    memset(&stMMZ_Frame, 0, sizeof(DISP_MMZ_BUF_S));
    stMMZ_Frame.u32StartPhyAddr = u32FrameStartPhyAddr;
    stMMZ_Frame.u32Size = datalen;
    stMMZ_Frame.bSmmu = HI_TRUE;

    nRet = DISP_OS_MMZ_Map(&stMMZ_Frame);
    if (HI_SUCCESS != nRet)
    {
        return HI_ERR_VO_MALLOC_FAILED;
    }
    pu8FrameStartVirAddr = stMMZ_Frame.pu8StartVirAddr;
#else
    pu8FrameStartVirAddr = (HI_U8 *) phys_to_virt (u32FrameStartPhyAddr);
#endif

    //printk("copy --dist-0x%x,h--0x%x --start-\n",(HI_U32 )pu8StillFrameStartVirAddr,(HI_U32 )pu8FrameStartVirAddr);

    memcpy(pCapFrameinfo, pFrameinfo, sizeof(HI_DRV_VIDEO_FRAME_S));
    //printk("copy --dist-0x%x,h--0x%x --end-\n",(HI_U32 )pu8StillFrameStartVirAddr,(HI_U32 )pu8FrameStartVirAddr);

    memcpy((void *)pu8StillFrameStartVirAddr, (void *)pu8FrameStartVirAddr, datalen);


    //printk("copy --dist-0x%x,h--0x%x --end-\n",(HI_U32 )pu8StillFrameStartVirAddr,(HI_U32 )pu8FrameStartVirAddr);


    /*3: calculate  frame addr*/
    pCapFrameinfo->stBufAddr[0].u32PhyAddr_YHead = u32StillFrameStartPhyAddr + (pFrameinfo->stBufAddr[0].u32PhyAddr_YHead - u32FrameStartPhyAddr);
    pCapFrameinfo->stBufAddr[0].u32Stride_Y =  pFrameinfo->stBufAddr[0].u32Stride_Y;

    pCapFrameinfo->stBufAddr[0].u32PhyAddr_Y = u32StillFrameStartPhyAddr + (pFrameinfo->stBufAddr[0].u32PhyAddr_Y - u32FrameStartPhyAddr);


    pCapFrameinfo->stBufAddr[0].u32PhyAddr_C = u32StillFrameStartPhyAddr + (pCapFrameinfo->u32Height * pCapFrameinfo->stBufAddr[0].u32Stride_Y);

    pCapFrameinfo->stBufAddr[0].u32PhyAddr_CrHead = u32StillFrameStartPhyAddr + ( pFrameinfo->stBufAddr[0].u32PhyAddr_CrHead - u32FrameStartPhyAddr);
    pCapFrameinfo->stBufAddr[0].u32PhyAddr_Cr = u32StillFrameStartPhyAddr + ( pFrameinfo->stBufAddr[0].u32PhyAddr_Cr - u32FrameStartPhyAddr );
    pCapFrameinfo->stBufAddr[0].u32Stride_Cr = pFrameinfo->stBufAddr[0].u32Stride_Cr;

#ifdef  CFG_VDP_MMU_SUPPORT
    memset(&stMMZ_Frame, 0, sizeof(DISP_MMZ_BUF_S));
    stMMZ_Frame.u32Size = datalen;
    stMMZ_Frame.bSmmu = HI_TRUE;

    stMMZ_Frame.pu8StartVirAddr = pu8FrameStartVirAddr;
    DISP_OS_MMZ_UnMap(&stMMZ_Frame);

    stMMZ_Frame.pu8StartVirAddr = pu8StillFrameStartVirAddr;
    DISP_OS_MMZ_UnMap(&stMMZ_Frame);
#else
    DISP_OS_MMZ_UnMap(&stMMZ_Frame);
#endif
    //  printk("make -end-str-%d,h--%d ----\n",pCapFrameinfo->stBufAddr[0].u32Stride_Y,pCapFrameinfo->u32Height);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_WIN_CapturePicture(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstPic)
{
    HI_S32 Ret;
    WIN_CAPTURE_S   stCapture;

    if (!pstPic)
    {
        HI_ERR_WIN("para null!\n");
        return HI_FAILURE;
    }

    stCapture.hWindow = hWin;

    Ret = DRV_WIN_Process(CMD_VO_WIN_CAPTURE_START, &stCapture);
    if (HI_SUCCESS != Ret)
    {
        WIN_ERROR("capture err!\n");
        return Ret;
    }

    stCapture.hWindow = hWin;
    pstPic->stBufAddr[0].u32PhyAddr_Y = stCapture.driver_supply_addr.startPhyAddr;

    (HI_VOID)Make_CaptureFrame(&(stCapture.CapPicture), pstPic);

    stCapture.hWindow = hWin;
    Ret = DRV_WIN_Process(CMD_VO_WIN_CAPTURE_RELEASE, &stCapture);
    if (HI_SUCCESS != Ret)
    {
        WIN_ERROR("capture RELEASE err!\n");
    }
    return Ret;
}

HI_S32 HI_DRV_WIN_CapturePictureRelease(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstPic)
{
    HI_S32 Ret;
    WIN_CAPTURE_S  stCapture;

    if (!pstPic)
    {
        HI_ERR_WIN("para null!\n");
        return HI_FAILURE;
    }

    stCapture.hWindow = hWin;
    stCapture.CapPicture = *pstPic;

    Ret = DRV_WIN_Process(CMD_VO_WIN_CAPTURE_FREE, &stCapture);

    return Ret;
}

HI_S32 HI_DRV_WIN_SetRotation(HI_HANDLE hWin, HI_DRV_ROT_ANGLE_E enRotation)
{
    return HI_ERR_VO_WIN_UNSUPPORT;
}

HI_S32 HI_DRV_WIN_GetRotation(HI_HANDLE hWin, HI_DRV_ROT_ANGLE_E *penRotation)
{
    return HI_ERR_VO_WIN_UNSUPPORT;
}

HI_S32 HI_DRV_WIN_SetFlip(HI_HANDLE hWin, HI_BOOL bHoriFlip, HI_BOOL bVertFlip)
{
    return HI_ERR_VO_WIN_UNSUPPORT;
}

HI_S32 HI_DRV_WIN_GetFlip(HI_HANDLE hWin, HI_BOOL *pbHoriFlip, HI_BOOL *pbVertFlip)
{
    return HI_ERR_VO_WIN_UNSUPPORT;
}

HI_S32 HI_DRV_WIN_SendFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    HI_S32 Ret;
    WinCheckNullPointer(pFrameinfo);
    Ret = WIN_SendFrame(hWin, pFrameinfo);
    return Ret;
}

HI_S32 HI_DRV_WIN_SetAttr(HI_HANDLE hWin, HI_DRV_WIN_ATTR_S *pWinAttr)
{
    HI_S32 Ret;
    WIN_CREATE_S   stWinAttr;

    WinCheckNullPointer(pWinAttr);

    stWinAttr.hWindow = hWin;
    stWinAttr.WinAttr = *pWinAttr;
    Ret = DRV_WIN_Process(CMD_WIN_SET_ATTR, &stWinAttr);
    return Ret;
}

HI_S32 HI_DRV_WIN_GetAttr(HI_HANDLE hWin, HI_DRV_WIN_ATTR_S *pWinAttr)
{
    HI_S32 Ret;
    WIN_CREATE_S   stWinAttr = {0};

    WinCheckNullPointer(pWinAttr);

    memset(&stWinAttr, 0, sizeof(WIN_CREATE_S));
    stWinAttr.hWindow = hWin;
    // stWinAttr.WinAttr = *pWinAttr;
    Ret = DRV_WIN_Process(CMD_WIN_GET_ATTR, &stWinAttr);
    if (!Ret)
    {
        *pWinAttr = stWinAttr.WinAttr;
    }
    return Ret;
}

HI_S32 HI_DRV_WIN_GetDelayMs(HI_HANDLE hWindow, HI_U32 *pu32DelayTime)
{
    HI_S32 Ret;
    HI_DRV_WIN_PLAY_INFO_S      WinPlayInfo;

    WinCheckNullPointer(pu32DelayTime);

    Ret = HI_DRV_WIN_GetPlayInfo(hWindow, &WinPlayInfo);
    if (HI_SUCCESS == Ret)
    {
        *pu32DelayTime =  WinPlayInfo.u32DelayTime;
    }

    return Ret;
}

HI_S32 HI_DRV_WIN_GetPlayInfo(HI_HANDLE hWindow, HI_DRV_WIN_PLAY_INFO_S *pInfo)
{
    HI_S32 Ret;
    WIN_PLAY_INFO_S WinPlayInfo = {0};

    memset(&WinPlayInfo, 0, sizeof(WIN_PLAY_INFO_S));
    WinCheckNullPointer(pInfo);
    WinPlayInfo.hWindow = hWindow;

    Ret = DRV_WIN_Process(CMD_WIN_GET_PLAY_INFO, &WinPlayInfo);
    *pInfo = WinPlayInfo.stPlayInfo;
    return Ret;
}

HI_S32 HI_DRV_WIN_GetInfo(HI_HANDLE hWindow, HI_DRV_WIN_INFO_S *pInfo)
{
    HI_S32 Ret;
    WIN_PRIV_INFO_S WinPrivInfo = {0};

    memset(&WinPrivInfo, 0, sizeof(WIN_PRIV_INFO_S));
    WinCheckNullPointer(pInfo);
    WinPrivInfo.hWindow = hWindow;

    Ret = DRV_WIN_Process(CMD_WIN_GET_INFO, &WinPrivInfo);
    *pInfo = WinPrivInfo.stPrivInfo;

    return Ret;
}

HI_S32 DRV_WIN_SendFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32     Ret = 0;
    WIN_FRAME_S *pstWinFrame = HI_NULL;

    if (!pFrame)
    {
        HI_ERR_WIN("para null!\n");
        return HI_FAILURE;
    }

    pstWinFrame = HI_KMALLOC(HI_ID_VO, sizeof(WIN_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pstWinFrame)
    {
        HI_ERR_WIN("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstWinFrame, 0, sizeof(WIN_FRAME_S));
    pstWinFrame->hWindow = hWindow;
    pstWinFrame->stFrame = *pFrame;

    Ret = DRV_WIN_Process(CMD_WIN_SEND_FRAME, pstWinFrame);

    HI_KFREE(HI_ID_VO, pstWinFrame);
    pstWinFrame = HI_NULL;

    return Ret;
}


HI_S32 HI_DRV_WIN_QFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32     Ret = 0;
    WIN_FRAME_S *pstWinFrame = HI_NULL;

    WinCheckNullPointer(pFrame);

    pstWinFrame = HI_KMALLOC(HI_ID_VO, sizeof(WIN_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pstWinFrame)
    {
        HI_ERR_WIN("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstWinFrame, 0, sizeof(WIN_FRAME_S));
    pstWinFrame->hWindow = hWindow;
    pstWinFrame->stFrame = *pFrame;

    Ret = DRV_WIN_Process(CMD_WIN_QU_FRAME, pstWinFrame);

    HI_KFREE(HI_ID_VO, pstWinFrame);
    pstWinFrame = HI_NULL;

    return Ret;
}

HI_S32 HI_DRV_WIN_QULSFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32     Ret = 0;
    WIN_FRAME_S *pstWinFrame = HI_NULL;

    WinCheckNullPointer(pFrame);

    pstWinFrame = HI_KMALLOC(HI_ID_VO, sizeof(WIN_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pstWinFrame)
    {
        HI_ERR_WIN("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstWinFrame, 0, sizeof(WIN_FRAME_S));
    pstWinFrame->hWindow = hWindow;
    pstWinFrame->stFrame = *pFrame;

    Ret = DRV_WIN_Process(CMD_WIN_QU_ULSFRAME, pstWinFrame);

    HI_KFREE(HI_ID_VO, pstWinFrame);
    pstWinFrame = HI_NULL;

    return Ret;
}

HI_S32 HI_DRV_WIN_DQFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32     Ret = 0;
    WIN_FRAME_S *pstWinFrame = HI_NULL;
    WinCheckNullPointer(pFrame);

    pstWinFrame = HI_KMALLOC(HI_ID_VO, sizeof(WIN_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pstWinFrame)
    {
        HI_ERR_WIN("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstWinFrame, 0, sizeof(WIN_FRAME_S));
    pstWinFrame->hWindow = hWindow;

    Ret = DRV_WIN_Process(CMD_WIN_DQ_FRAME, pstWinFrame);
    if (HI_SUCCESS == Ret)
    {
        *pFrame = pstWinFrame->stFrame;
    }

    HI_KFREE(HI_ID_VO, pstWinFrame);
    pstWinFrame = HI_NULL;

    return Ret;
}

HI_S32 DRV_WIN_AcquireFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32     Ret = 0;
    WIN_FRAME_S *pstWinFrame = HI_NULL;

    pstWinFrame = HI_KMALLOC(HI_ID_VO, sizeof(WIN_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pstWinFrame)
    {
        HI_ERR_WIN("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstWinFrame, 0, sizeof(WIN_FRAME_S));
    pstWinFrame->hWindow = hWindow;

    Ret = DRV_WIN_Process(CMD_WIN_VIR_ACQUIRE, pstWinFrame);
    if (HI_SUCCESS == Ret)
    {
        *pFrame = pstWinFrame->stFrame;
    }

    HI_KFREE(HI_ID_VO, pstWinFrame);
    pstWinFrame = HI_NULL;

    return Ret;
}

HI_S32 DRV_WIN_ReleaseFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32     Ret = 0;
    WIN_FRAME_S *pstWinFrame = HI_NULL;

    pstWinFrame = HI_KMALLOC(HI_ID_VO, sizeof(WIN_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pstWinFrame)
    {
        HI_ERR_WIN("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstWinFrame, 0, sizeof(WIN_FRAME_S));

    pstWinFrame->hWindow = hWindow;
    pstWinFrame->stFrame = *pFrame;

    Ret = DRV_WIN_Process(CMD_WIN_VIR_RELEASE, pstWinFrame);

    HI_KFREE(HI_ID_VO, pstWinFrame);
    pstWinFrame = HI_NULL;

    return Ret;
}


HI_S32 HI_DRV_WIN_SetZorder(HI_HANDLE hWin, HI_DRV_DISP_ZORDER_E ZFlag)
{
    HI_S32     Ret;
    WIN_ZORDER_S stWinZorder;

    stWinZorder.hWindow = hWin;
    stWinZorder.eZFlag = ZFlag;
    Ret = DRV_WIN_Process(CMD_WIN_SET_ZORDER, &stWinZorder);
    return Ret;
}

HI_S32 HI_DRV_WIN_GetZorder(HI_HANDLE hWin, HI_U32 *pu32Zorder)
{
    HI_S32     Ret;
    WIN_ORDER_S stWinOrder = {0};

    WinCheckNullPointer(pu32Zorder);

    memset(&stWinOrder, 0, sizeof(WIN_ORDER_S));
    stWinOrder.hWindow = hWin;

    Ret = DRV_WIN_Process(CMD_WIN_SET_ZORDER, &stWinOrder);
    if (!Ret)
    {
        *pu32Zorder = stWinOrder.Order ;
    }
    return Ret;
}

HI_S32 HI_DRV_WIN_Freeze(HI_HANDLE hWin, HI_BOOL bEnable,  HI_DRV_WIN_SWITCH_E eRst)
{
    HI_S32     Ret;
    WIN_FREEZE_S stWinFreeze;

    stWinFreeze.hWindow = hWin;
    stWinFreeze.bEnable = bEnable;
    stWinFreeze.eMode = eRst;

    Ret = DRV_WIN_Process(CMD_WIN_FREEZE, &stWinFreeze);

    return Ret;
}

HI_S32 HI_DRV_WIN_GetLatestFrameInfo(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *frame_info)
{
    HI_S32     Ret = 0;
    WIN_FRAME_S  *pframe_info_ioctl = HI_NULL;

    WinCheckNullPointer(frame_info);

    pframe_info_ioctl = HI_KMALLOC(HI_ID_VO, sizeof(WIN_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pframe_info_ioctl)
    {
        HI_ERR_WIN("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pframe_info_ioctl, 0, sizeof(WIN_FRAME_S));

    pframe_info_ioctl->hWindow = hWin;

    Ret = DRV_WIN_Process(CMD_WIN_GET_LATESTFRAME_INFO, pframe_info_ioctl);
    if (HI_SUCCESS == Ret)
    {
        *frame_info = pframe_info_ioctl->stFrame;
    }

    HI_KFREE(HI_ID_VO, pframe_info_ioctl);
    pframe_info_ioctl = HI_NULL;

    return Ret;
}


HI_S32 WIN_DRV_DestroyAll(WIN_STATE_S *pst2WinState)
{
    HI_DRV_DISPLAY_E enDisp;
    HI_S32 i;

    for (enDisp = 0; enDisp < HI_DRV_DISPLAY_BUTT; enDisp++)
    {
        for (i = 0; i < DEF_MAX_WIN_NUM_ON_SINGLE_DISP; i++)
        {
            if (pst2WinState->hWin[enDisp][i] != HI_NULL)
            {
                WIN_DestroyExt(pst2WinState->hWin[enDisp][i], pst2WinState);
            }
        }
    }

    for (i = 0; i < DEF_MAX_WIN_NUM_ON_VIRTUAL_DISP; i++)
    {
        if (pst2WinState->hVirtualWin[i] != HI_NULL)
        {
            WIN_DestroyExt(pst2WinState->hVirtualWin[i], pst2WinState);
        }
    }

    return HI_SUCCESS;
}



HI_S32 HI_DRV_WIN_Init(HI_VOID)
{
    HI_S32 i, j, Ret;

    Ret = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        WIN_FATAL(" get mutex error.\n");
        return HI_FAILURE;
    }

    for (i = HI_DRV_DISPLAY_0; i < HI_DRV_DISPLAY_BUTT; i++)
    {
        for (j = 0; j < DEF_MAX_WIN_NUM_ON_SINGLE_DISP; j++)
        {
            g_VoModState.hWin[i][j] = HI_NULL;
        }
    }

    for (j = 0; j < DEF_MAX_WIN_NUM_ON_VIRTUAL_DISP; j++)
    {
        g_VoModState.hVirtualWin[j] = HI_NULL;
    }

    if (1 == atomic_inc_return(&g_VoCount))
    {
        Ret = WIN_Init();
        if (Ret != HI_SUCCESS)
        {
            HI_FATAL_WIN("call VO_Init failed.\n");
            atomic_dec(&g_VoCount);
            up(&g_VoMutex);
            return -1;
        }
    }

    up(&g_VoMutex);

    Ret = DRV_WIN_Register();
    if (Ret != HI_SUCCESS)
    {
        HI_FATAL_WIN("call DRV_WIN_Register failed.\n");
        return -1;
    }

    return 0;
}



HI_S32 HI_DRV_WIN_DeInit(HI_VOID)
{
    HI_S32        Ret;

    Ret = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        WIN_FATAL(" get mutex error.\n");
        return HI_FAILURE;
    }

    WIN_DRV_DestroyAll(&g_VoModState);
    if (atomic_dec_and_test(&g_VoCount))
    {
        WIN_DeInit();
    }

    up(&g_VoMutex);
    return 0;
}



static WIN_EXPORT_FUNC_S s_stWinExportFuncs =
{
    .pfnWinInit      = HI_DRV_WIN_Init,
    .pfnWinDeInit    = HI_DRV_WIN_DeInit,
    .pfnWinCreate    = HI_DRV_WIN_Create,
    .pfnWinDestory   = HI_DRV_WIN_Destroy,
    .pfnWinSetAttr   = HI_DRV_WIN_SetAttr,
    .pfnWinGetAttr   = HI_DRV_WIN_GetAttr,
    .pfnWinGetInfo   = HI_DRV_WIN_GetInfo,
    .pfnWinSetSrc    = HI_DRV_WIN_SetSource,
    .pfnWinGetSrc    = HI_DRV_WIN_GetSource,
    .pfnWinSetEnable = HI_DRV_WIN_SetEnable,
    .pfnWinGetEnable = HI_DRV_WIN_GetEnable,
    .pfnWinQueueFrm  = HI_DRV_WIN_QFrame,
    .pWinQueueUselessFrm = HI_DRV_WIN_QULSFrame,
    .pfnWinDequeueFrm  = HI_DRV_WIN_DQFrame,
    .pfnWinGetPlayInfo = HI_DRV_WIN_GetPlayInfo,
    .pfnWinSetZorder = HI_DRV_WIN_SetZorder,
    .pfnWinGetZorder = HI_DRV_WIN_GetZorder,
    .pfnWinFreeze    = HI_DRV_WIN_Freeze,
    .pfnWinGetLatestFrameInfo = HI_DRV_WIN_GetLatestFrameInfo,
    .pfnWinReset     = HI_DRV_WIN_Reset,
    .pfnWinPause     = HI_DRV_WIN_Pause,
    .pfnWinSetStepMode = HI_DRV_WIN_SetStepMode,
    .pfnWinSetStepPlay = HI_DRV_WIN_SetStepPlay,
    .pfnWinSetExtBuffer = HI_DRV_WIN_SetExtBuffer,
    .pfnWinAcquireFrm  = HI_DRV_WIN_AcquireFrame,
    .pfnWinRlsFrm      = WIN_ReleaseFrame,
    //    .pfnWin3DMode      = HI_DRV_WIN_Set3DMode,
    .pfnWinSetQuik   = HI_DRV_WIN_SetQuick,
    .pfnWinCapturePic  = HI_DRV_WIN_CapturePicture,
    .pfnWinCapturePicRls = HI_DRV_WIN_CapturePictureRelease,
    .pfnWinSetRotation = HI_DRV_WIN_SetRotation,
    .pfnWinGetRotation = HI_DRV_WIN_GetRotation,
    .pfnWinSetFlip   = HI_DRV_WIN_SetFlip,
    .pfnWinGetFlip   = HI_DRV_WIN_GetFlip,
    .pfnWinSendFrm   = HI_DRV_WIN_SendFrame,
    .pfnWinResume = DRV_WIN_Resume,
    .pfnWinSuspend = DRV_WIN_Suspend,
    .pfnWinSetVirAttr = WIN_SetVirtualAttr,
};

HI_S32 DRV_WIN_Register(HI_VOID)
{
    HI_S32  Ret;

    Ret = HI_DRV_MODULE_Register((HI_U32)HI_ID_VO, "HI_VO", (HI_VOID *)(&s_stWinExportFuncs));
    if (HI_SUCCESS != Ret)
    {
        HI_FATAL_WIN("HI_DRV_MODULE_Register VO failed\n");
        return Ret;
    }

    g_VoSuspend = HI_FALSE;

    return  0;
}

HI_VOID DRV_WIN_UnRegister(HI_VOID)
{

    HI_DRV_WIN_DeInit();

    HI_DRV_MODULE_UnRegister(HI_ID_VO);

    return;
}



HI_S32 WIN_DRV_Open(struct inode *finode, struct file  *ffile)
{
    WIN_STATE_S *pWinState = HI_NULL;
    HI_S32     Ret;

    Ret = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        WIN_FATAL(" get mutex error.\n");
        return HI_FAILURE;
    }

    pWinState = HI_KMALLOC(HI_ID_VO, sizeof(WIN_STATE_S), GFP_KERNEL);
    if (!pWinState)
    {
        WIN_FATAL("malloc pWinState failed.\n");
        up(&g_VoMutex);
        return -1;
    }

    memset(pWinState, 0, sizeof(WIN_STATE_S));

    if (1 == atomic_inc_return(&g_VoCount))
    {
        Ret = WIN_Init();
        if (Ret != HI_SUCCESS)
        {
            HI_KFREE(HI_ID_VO, pWinState);
            WIN_FATAL("call VO_Init failed.\n");
            atomic_dec(&g_VoCount);
            up(&g_VoMutex);
            return -1;
        }
    }

    ffile->private_data = pWinState;

    up(&g_VoMutex);
    return 0;
}

HI_S32 WIN_DRV_Close(struct inode *finode, struct file  *ffile)
{
    WIN_STATE_S    *pVoState;
    HI_S32        Ret = HI_FAILURE;
    HI_U32        i = 0, j = 0;

    Ret = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        WIN_FATAL(" get mutex error.\n");
        return HI_FAILURE;
    }

    pVoState = ffile->private_data;
    if (HI_NULL == pVoState)
    {
        up(&g_VoMutex);
        WIN_FATAL(" pVoState is null.\n");
        return HI_FAILURE;
    }

    for (i = 0; i < HI_DRV_DISPLAY_BUTT; i++)
    {
        for (j = 0; j < DEF_MAX_WIN_NUM_ON_SINGLE_DISP; j++)
        {
            if (pVoState->hCapture[i][j] != 0)
            {
                WinForceClearCapture(pVoState->hCapture[i][j]);
            }
        }
    }

    WIN_DRV_DestroyAll(pVoState);

    if (atomic_dec_and_test(&g_VoCount))
    {
        WIN_DeInit();
    }

    HI_KFREE(HI_ID_VO, pVoState);

    up(&g_VoMutex);
    return HI_SUCCESS;
}

HI_S32 DRV_WIN_Ioctl(struct inode *inode, struct file  *file, unsigned int cmd, HI_VOID *arg)
{
    WIN_STATE_S   *pstWinState;
    HI_S32        Ret = HI_FAILURE;

    Ret = down_interruptible(&g_VoMutex);
    if (HI_SUCCESS != Ret)
    {
        WIN_FATAL(" get mutex error.\n");
        return HI_FAILURE;
    }

    pstWinState = file->private_data;
    Ret = WIN_ProcessCmd(cmd, arg, pstWinState);

    up(&g_VoMutex);
    return Ret;
}

//#ifndef MODULE
EXPORT_SYMBOL(g_VoMutex);

EXPORT_SYMBOL(DRV_WIN_Ioctl);
EXPORT_SYMBOL(WIN_DRV_Open);
EXPORT_SYMBOL(WIN_DRV_Close);
EXPORT_SYMBOL(DRV_WIN_Suspend);
EXPORT_SYMBOL(DRV_WIN_Resume);
//EXPORT_SYMBOL(DRV_WIN_ProcRegister);
//EXPORT_SYMBOL(DRV_WIN_ProcfUnRegister);
EXPORT_SYMBOL(WIN_AcquireFrame);
EXPORT_SYMBOL(WIN_ReleaseFrame);

EXPORT_SYMBOL(HI_DRV_WIN_SetEnable);
EXPORT_SYMBOL(DRV_WIN_Register);
EXPORT_SYMBOL(DRV_WIN_UnRegister);

EXPORT_SYMBOL(HI_DRV_WIN_Init);
EXPORT_SYMBOL(HI_DRV_WIN_DeInit);
EXPORT_SYMBOL(HI_DRV_WIN_QFrame);
EXPORT_SYMBOL(HI_DRV_WIN_CapturePicture);
EXPORT_SYMBOL(HI_DRV_WIN_QULSFrame);
EXPORT_SYMBOL(DRV_WIN_Process);
EXPORT_SYMBOL(HI_DRV_WIN_Create);
EXPORT_SYMBOL(HI_DRV_WIN_Destroy);
EXPORT_SYMBOL(HI_DRV_WIN_Freeze);
EXPORT_SYMBOL(HI_DRV_WIN_Pause);

EXPORT_SYMBOL(HI_DRV_WIN_SetSource);
EXPORT_SYMBOL(HI_DRV_WIN_Reset);
EXPORT_SYMBOL(HI_DRV_WIN_GetPlayInfo);
EXPORT_SYMBOL(DRV_WIN_SendFrame);
EXPORT_SYMBOL(HI_DRV_WIN_SetZorder);
EXPORT_SYMBOL(DRV_WIN_SetSftwareStage);
//#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
