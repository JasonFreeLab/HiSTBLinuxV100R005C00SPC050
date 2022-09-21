/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name       : drv_hifb_adp.c
Version          : Initial Draft
Author           : sdk
Created          : 2017/07/12
Description     :
Function List   :


History          :
Date                     Author                Modification
2017/07/12          sdk                    Created file
******************************************************************************/


/***************************** add include here*********************************/
#ifndef HI_BUILD_IN_BOOT
    #include <linux/string.h>
    #include <linux/fb.h>
    #include <linux/time.h>
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
    #include <linux/init.h>
    #include <linux/delay.h>
    #include <asm/uaccess.h>
    #include <asm/io.h>
    #include <linux/interrupt.h>
    #include <linux/ioport.h>
    #include <linux/string.h>
    #include <linux/workqueue.h>
    #include "hi_module.h"
    #include "hi_drv_module.h"
#else
    #include "hifb_debug.h"
    #include "hi_drv_pq.h"
    #include "hi_gfx_mem.h"
#endif


#include "drv_disp_ext.h"
#include "drv_hifb_hal.h"
#include "drv_hifb_adp.h"
#include "hi_drv_disp.h"
#include "drv_hifb_wbc.h"
#include "drv_pq_ext.h"

#ifdef CFG_HIFB_PROC_SUPPORT
#include "drv_hifb_proc.h"
#endif

#include "drv_hifb_paracheck.h"
#include "drv_hifb_config.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition ********************************/
#ifndef HI_BUILD_IN_BOOT
static DISP_EXPORT_FUNC_S *ps_DispExportFuncs = HI_NULL;
#endif

#ifndef HI_BUILD_IN_BOOT
#define OPTM_HIFB_WVM_ENABLE                       1
#define OPTM_HIFB_GFXRR_ENABLE                     1
#define CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH     4096
#define CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH           3840
#define CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT          2160
#endif


#define DispWidth_HD                     1280
#define DispHeight_HD                    720
#define DispWidth_SD                     720
#define DispHeight_SD                    576
#define OPTM_COLOR_DEFVALUE              50
#define OPTM_EXTRACTLINE_RATIO           4
#define OPTM_EXTRACTLINE_WIDTH           1080


/**
 ** G3(中间空掉G2，这里HD_2 -> G3)一直是做为鼠标层，
 ** CV200绑定到FB5中，所以CV200用的是SD1
 **/
#define OPTM_CURSOR_LAYERID                    HIFB_LAYER_HD_2

#define OPTM_GP_SUPPORT_MAXLAYERNUM            5
#define OPTM_GP0_GFX_COUNT                     CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT
#define OPTM_GP1_GFX_COUNT                     CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT
#define OPTM_GFXCLUT_LENGTH                    256


#define HIFB_CHECK_GFX_OPEN(enLayerId)  \
        do{ if (enLayerId >= HIFB_LAYER_ID_BUTT){\
              HIFB_ERROR("no suppout Gfx%d!\n",enLayerId);       \
              return HI_FAILURE;}\
            if (g_stGfxDevice[enLayerId].bOpened != HI_TRUE){    \
              HIFB_ERROR("Error! Gfx%d not open!\n",enLayerId);  \
              return HI_FAILURE;}\
        }while(0)


/***************************** Structure Definition ****************************/
typedef enum tagOPTM_VDP_CONNECT_E
{
    OPTM_VDP_CONNECT_G3_DHD0 = 0,
    OPTM_VDP_CONNECT_G3_DHD1,
    OPTM_VDP_CONNECT_BUTT,
}OPTM_VDP_CONNECT_E;

typedef enum tagOPTM_WBC_BUFFER_STATUS_E
{
    OPTM_WBC_BUFFER_RELEASED = 0,
    OPTM_WBC_BUFFER_ACQUIRED
}OPTM_WBC_BUFFER_STATUS_E;


typedef struct tagOPTM_GFX_IRQ_S
{
    HI_VOID* pParam0;   /** layer id      **/
    HI_U32   u32Param1;
    IntCallBack pFunc;  /** irq function **/
}OPTM_GFX_IRQ_S;

typedef struct tagOPTM_GFX_CALLBACK_S
{
    HI_U32 u32CTypeFlag;
    OPTM_GFX_IRQ_S stGfxIrq[HIFB_CALLBACK_TYPE_BUTT];
}OPTM_GFX_CALLBACK_S;

typedef struct tagOPTM_GP_IRQ_S
{
    HI_BOOL bRegistered[HI_DRV_DISP_C_TYPE_BUTT];
    OPTM_GFX_CALLBACK_S stGfxCallBack[OPTM_GP_SUPPORT_MAXLAYERNUM];
}OPTM_GP_IRQ_S;

/***************************** Global Variable declaration *********************/
static volatile HI_U32 *gs_Phyaddr = HI_NULL;
static HI_U32 gs_GFXInitFlag = OPTM_DISABLE;

#ifndef CONFIG_GFX_PQ
static OPTM_ALG_GZME_MEM_S  gs_stGPZme;
#endif

HIFB_GFX_MODE_EN g_enOptmGfxWorkMode = HIFB_GFX_MODE_NORMAL;

OPTM_GFX_LAYER_S g_stGfxDevice[OPTM_MAX_LOGIC_HIFB_LAYER];

OPTM_GFX_GP_S g_stGfxGPDevice[OPTM_GFX_GP_BUTT];

static OPTM_GP_IRQ_S g_stGfxGPIrq[OPTM_GFX_GP_BUTT];
extern OPTM_GFX_WBC_S g_stGfxWbc2;

#ifndef HI_BUILD_IN_BOOT
   static PQ_EXPORT_FUNC_S*  gs_pstPqFuncs = HI_NULL;
   static HIFB_LAYER_ID_E gs_CallBackLayerId[HIFB_LAYER_ID_BUTT];
#endif

const HIFB_CAPABILITY_S g_stGfxCap[OPTM_MAX_LOGIC_HIFB_LAYER] =
{
    /* HD0 */
    {
        .bKeyAlpha       = 1,
        .bGlobalAlpha    = 1,
        .bCmap           = 1,
        .bHasCmapReg     = 1,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale        = HI_TRUE,
        .bLayerSupported = CONFIG_HIFB_HD0_LAYER_SUPPORT,
        .bCompression    = CONFIG_HIFB_HD0_COMPRESSION_SUPPORT,
        .bStereo         = 1,
        .u32MaxWidth     = CONFIG_HIFB_HD_LAYER_MAXWIDTH,
        .u32MaxHeight    = CONFIG_HIFB_HD_LAYER_MAXHEIGHT,
        .u32MinWidth     = 0,
        .u32MinHeight    = 0,
        .u32VDefLevel    = 0,  /* not surpport */
        .u32HDefLevel    = 0,  /* not surpport */
    },

    /* HD1 */
    {
        .bKeyAlpha       = 1,
        .bGlobalAlpha    = 1,
        .bCmap           = 1,
        .bHasCmapReg     = 1,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale        = HI_TRUE,
        .bLayerSupported = CONFIG_HIFB_HD1_LAYER_SUPPORT,
        .bCompression    = CONFIG_HIFB_HD1_COMPRESSION_SUPPORT,
        .bStereo         = 0,
        .u32MaxWidth     = CONFIG_HIFB_HD_LAYER_MAXWIDTH,
        .u32MaxHeight    = CONFIG_HIFB_HD_LAYER_MAXHEIGHT,
        .u32MinWidth     = 0,
        .u32MinHeight    = 0,
        .u32VDefLevel    = 0,  /* not surpport */
        .u32HDefLevel   = 0,  /* not surpport */
    },
    /* HD2 */
    {
        .bKeyAlpha       = 1,
        .bGlobalAlpha    = 1,
        .bCmap           = 1,
        .bHasCmapReg     = 1,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale        = HI_TRUE,
        .bLayerSupported = CONFIG_HIFB_HD2_LAYER_SUPPORT,
        .bCompression    = CONFIG_HIFB_HD2_COMPRESSION_SUPPORT,
        .bStereo         = 0,
        .u32MaxWidth     = CONFIG_HIFB_HD_LAYER_MAXWIDTH,
        .u32MaxHeight    = CONFIG_HIFB_HD_LAYER_MAXHEIGHT,
        .u32MinWidth     = 0,
        .u32MinHeight    = 0,
        .u32VDefLevel    = 0,  /* not surpport */
        .u32HDefLevel    = 0,  /* not surpport */
    },

    /* HD3 */
    {
        .bKeyAlpha        = 1,
        .bGlobalAlpha     = 1,
        .bCmap            = 1,
        .bHasCmapReg      = 1,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale         = HI_TRUE,
        .bLayerSupported  = CONFIG_HIFB_HD3_LAYER_SUPPORT,
        .bCompression     = CONFIG_HIFB_HD3_COMPRESSION_SUPPORT,
        .bStereo          = 0,
        .u32MaxWidth      = CONFIG_HIFB_HD_LAYER_MAXWIDTH,
        .u32MaxHeight     = CONFIG_HIFB_HD_LAYER_MAXHEIGHT,
        .u32MinWidth      = 0,
        .u32MinHeight     = 0,
        .u32VDefLevel     = 0,  /* not surpport */
        .u32HDefLevel     = 0,  /* not surpport */
    },

    /* SD0 */
    {
        .bKeyAlpha        = 1,
        .bGlobalAlpha     = 1,
        .bCmap            = 1,
        .bHasCmapReg      = 1,
        .bColFmt          = {1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,0,0,  0,1,0,0,  0,0,0,0,  0,0}, /** 36 **/
        .bVoScale         = HI_TRUE,
        .bLayerSupported  = CONFIG_HIFB_SD0_LAYER_SUPPORT,
        .bCompression     = CONFIG_HIFB_SD0_COMPRESSION_SUPPORT,
        .bStereo          = 1,
        .u32MaxWidth      = CONFIG_HIFB_SD_LAYER_MAXWIDTH,
        .u32MaxHeight     = CONFIG_HIFB_SD_LAYER_MAXHEIGHT,
        .u32MinWidth      = 0,
        .u32MinHeight     = 0,
        .u32VDefLevel     = 0,  /* not surpport */
        .u32HDefLevel     = 0,  /* not surpport */
    },

    /* SD1 */
    {
        .bKeyAlpha        = 1,
        .bGlobalAlpha     = 1,
        .bCmap            = 1,
        .bHasCmapReg      = 1,
        .bColFmt          = {1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,0,0,  0,1,0,0,  0,0,0,0,  0,0}, /** 36 **/
        .bVoScale         = HI_FALSE,
        .bLayerSupported  = CONFIG_HIFB_SD1_LAYER_SUPPORT,
        .bCompression     = CONFIG_HIFB_SD1_COMPRESSION_SUPPORT,
        .bStereo          = 1,
        .u32MaxWidth      = CONFIG_HIFB_SD_LAYER_MAXWIDTH,
        .u32MaxHeight     = CONFIG_HIFB_SD_LAYER_MAXHEIGHT,
        .u32MinWidth      = 0,
        .u32MinHeight     = 0,
        .u32VDefLevel     = 0,  /* not surpport */
        .u32HDefLevel     = 0,  /* not surpport */
    },

    /* SD2 */
    {
        .bKeyAlpha         = 1,
        .bGlobalAlpha      = 1,
        .bCmap             = 0,
        .bHasCmapReg       = 0,
        .bColFmt           = {1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,1,1,  1,1,0,0,  0,0,0,0,  0,0,0,0,  0,0}, /** 36 **/
        .bVoScale          = HI_FALSE,
        .bLayerSupported   = CONFIG_HIFB_SD2_LAYER_SUPPORT,
        .bCompression      = CONFIG_HIFB_SD2_COMPRESSION_SUPPORT,
        .bStereo           = 0,
        .u32MaxWidth       = CONFIG_HIFB_SD_LAYER_MAXWIDTH,
        .u32MaxHeight      = CONFIG_HIFB_SD_LAYER_MAXHEIGHT,
        .u32MinWidth       = 0,
        .u32MinHeight      = 0,
        .u32VDefLevel      = 0,  /* not surpport */
        .u32HDefLevel      = 0,  /* not surpport */
    },

    /* SD3 */
    {
        .bKeyAlpha         = 1,
        .bGlobalAlpha      = 1,
        .bCmap             = 0,
        .bHasCmapReg       = 0,
        .bColFmt           = {1,1,1,1,  1,1,1,1,  1,1,1,1,   1,1,1,1,   1,1,1,1,   1,1,0,0,  0,0,0,0,  0,0,0,0,  0,0}, /** 36 **/
        .bVoScale          = HI_FALSE,
        .bLayerSupported = CONFIG_HIFB_SD3_LAYER_SUPPORT,
        .bCompression      = CONFIG_HIFB_SD3_COMPRESSION_SUPPORT,
        .bStereo           = 0,
        .u32MaxWidth       = CONFIG_HIFB_SD_LAYER_MAXWIDTH,
        .u32MaxHeight      = CONFIG_HIFB_SD_LAYER_MAXHEIGHT,
        .u32MinWidth       = 0,
        .u32MinHeight      = 0,
        .u32VDefLevel      = 0,  /* not surpport */
        .u32HDefLevel      = 0,  /* not surpport */
    },
#ifndef HI_BUILD_IN_BOOT
    /* AD0 */
    {
        .bKeyAlpha         = 1,
        .bGlobalAlpha      = 1,
        .bCmap             = 0,
        .bHasCmapReg       = 0,
        .bColFmt           = {1,1,0,0,     \
                              0,0,1,1,     \
                              0,0,0,0,     \
                              0,1,1,0,     \
                              1,1,0,0,     \
                              0,0,1,1,     \
                              1,1,1,1,     \
                              0,0,0,0,     \
                              0,0}, /** 36 **/
        .bVoScale          = HI_TRUE,
        .bLayerSupported   = CONFIG_HIFB_AD0_LAYER_SUPPORT,
        .bCompression      = CONFIG_HIFB_AD0_COMPRESSION_SUPPORT,
        .bStereo           = 1,
        .u32MaxWidth       = CONFIG_HIFB_AD_LAYER_MAXWIDTH,
        .u32MaxHeight      = CONFIG_HIFB_AD_LAYER_MAXHEIGHT,
        .u32MinWidth       = 0,
        .u32MinHeight      = 0,
        .u32VDefLevel      = 0,  /* not surpport */
        .u32HDefLevel      = 0,  /* not surpport */
    },

    /* AD1 */
    {
        .bKeyAlpha         = 1,
        .bGlobalAlpha      = 1,
        .bCmap             = 0,
        .bHasCmapReg       = 0,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale          = HI_TRUE,
        .bLayerSupported   = CONFIG_HIFB_AD1_LAYER_SUPPORT,
        .bCompression      = CONFIG_HIFB_AD1_COMPRESSION_SUPPORT,
        .bStereo           = 1,
        .u32MaxWidth       = CONFIG_HIFB_AD_LAYER_MAXWIDTH,
        .u32MaxHeight      = CONFIG_HIFB_AD_LAYER_MAXHEIGHT,
        .u32MinWidth       = 0,
        .u32MinHeight      = 0,
        .u32VDefLevel      = 0,  /* not surpport */
        .u32HDefLevel      = 0,  /* not surpport */
    },

    /* AD2 */
    {
        .bKeyAlpha         = 1,
        .bGlobalAlpha      = 1,
        .bCmap             = 0,
        .bHasCmapReg       = 0,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale          = HI_TRUE,
        .bLayerSupported   = CONFIG_HIFB_AD2_LAYER_SUPPORT,
        .bCompression      = CONFIG_HIFB_AD2_COMPRESSION_SUPPORT,
        .bStereo           = 1,
        .u32MaxWidth       = CONFIG_HIFB_AD_LAYER_MAXWIDTH,
        .u32MaxHeight      = CONFIG_HIFB_AD_LAYER_MAXHEIGHT,
        .u32MinWidth       = 0,
        .u32MinHeight      = 0,
        .u32VDefLevel      = 0,  /* not surpport */
        .u32HDefLevel      = 0,  /* not surpport */
    },

    /* AD3 */
    {
        .bKeyAlpha         = 1,
        .bGlobalAlpha      = 1,
        .bCmap             = 0,
        .bHasCmapReg       = 0,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale          = HI_TRUE,
        .bLayerSupported   = CONFIG_HIFB_AD3_LAYER_SUPPORT,
        .bCompression      = CONFIG_HIFB_AD3_COMPRESSION_SUPPORT,
        .bStereo           = 1,
        .u32MaxWidth       = CONFIG_HIFB_AD_LAYER_MAXWIDTH,
        .u32MaxHeight      = CONFIG_HIFB_AD_LAYER_MAXHEIGHT,
        .u32MinWidth       = 0,
        .u32MinHeight      = 0,
        .u32VDefLevel      = 0,  /* not surpport */
        .u32HDefLevel      = 0,  /* not surpport */
    },

    /* CURSOR */
    {
        .bKeyAlpha         = 1,
        .bGlobalAlpha      = 1,
        .bCmap             = 0,
        .bHasCmapReg       = 0,
        .bColFmt         = {1,1,0,0,     \
                            0,0,1,1,     \
                            0,0,0,0,     \
                            0,1,1,0,     \
                            1,1,0,0,     \
                            0,0,1,1,     \
                            1,1,1,1,     \
                            0,0,0,0,     \
                            0,0}, /** 36 **/
        .bVoScale          = HI_TRUE,
        .bLayerSupported   = CONFIG_HIFB_CURSOR_LAYER_SUPPORT,
        .bCompression      = CONFIG_HIFB_CURSOR_COMPRESSION_SUPPORT,
        .bStereo           = 1,
        .u32MaxWidth       = CONFIG_HIFB_CURSOR_LAYER_MAXWIDTH,
        .u32MaxHeight      = CONFIG_HIFB_CURSOR_LAYER_MAXHEIGHT,
        .u32MinWidth       = 0,
        .u32MinHeight      = 0,
        .u32VDefLevel      = 0,  /* not surpport */
        .u32HDefLevel      = 0,  /* not surpport */
    },
#endif
};

/***************************** API forward declarations ************************/
#ifdef OPTM_HIFB_WVM_ENABLE
static HI_VOID OPTM_GfxWVBCallBack(HI_U32 enLayerId);
#endif

#ifndef HI_BUILD_IN_BOOT
static HI_S32 OPTM_DispInfoUpdate(OPTM_VDP_LAYER_GP_E enGPId);
static HI_S32  OPTM_Distribute_Callback(HI_VOID* u32Param0, HI_VOID* u32Param1);
static HI_VOID DRV_HIFB_ADP_FrameEndCallBack (HI_VOID* u32Param0, HI_VOID* u32Param1);
#endif

#if !defined(HI_BUILD_IN_BOOT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
static HI_S32  OPTM_GFX_SetStereoDepth(HIFB_LAYER_ID_E enLayerId, HI_S32 s32Depth);
#endif

static HI_S32 OPTM_GPRecovery(OPTM_GFX_GP_E enGPId);
static HI_S32 OPTM_GPSetCsc(OPTM_GFX_GP_E enGfxGpId, OPTM_GFX_CSC_PARA_S *pstCscPara, HI_BOOL bIsBGRIn);

#ifndef CONFIG_GFX_PQ
static OPTM_COLOR_SPACE_E OPTM_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc);
#else
static HI_PQ_GFX_COLOR_SPACE_E PQ_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc);
#endif

static inline OPTM_VDP_GFX_IFMT_E OPTM_ClutPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline OPTM_VDP_GFX_IFMT_E OPTM_RGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline OPTM_VDP_GFX_IFMT_E OPTM_XRGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline OPTM_VDP_GFX_IFMT_E OPTM_XYCbCrPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);

#ifndef HI_BUILD_IN_BOOT
static inline HIFB_COLOR_FMT_E OPTM_ClutHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HIFB_COLOR_FMT_E OPTM_RGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HIFB_COLOR_FMT_E OPTM_XRGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HIFB_COLOR_FMT_E OPTM_XYCbCrHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HI_VOID HIFB_ADP_ReOpen(OPTM_GFX_GP_E enGpId);
static inline HI_VOID HIFB_ADP_ReClose(OPTM_GFX_GP_E enGpId);
static inline HI_VOID HIFB_ADP_DispSetting(OPTM_GFX_GP_E enGpId, HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo);
static inline HI_VOID HIFB_ADP_UpdataLayerInfo(HI_VOID* u32Param0, HI_VOID* u32Param1);
#endif

static inline HI_VOID HIFB_ADP_ResetLayerInRect(OPTM_GFX_GP_E enGpId);
static inline HI_S32 HIFB_ADP_SetLayerDataBigEndianFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt);
static inline HI_S32 HIFB_ADP_SetLayerDataLittleEndianFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt);


/***************************** API realization *********************************/
#if defined(CONFIG_HIFB_LOWPOWER_SUPPORT) && !defined(HI_BUILD_IN_BOOT)
static OPTM_GFX_GP_E HIFB_ADP_ConvertLayerIdToGpId(HIFB_LAYER_ID_E enLayerId)
{
    if (enLayerId <= HIFB_LAYER_HD_3)
    {
        return OPTM_GFX_GP_0;
    }
    else if(enLayerId >= HIFB_LAYER_SD_0 && enLayerId <= HIFB_LAYER_SD_1)
    {
        return OPTM_GFX_GP_1;
    }

    return OPTM_GFX_GP_BUTT;
}
#endif


#ifndef HI_BUILD_IN_BOOT
static HI_U32 OPTM_AlignUp(HI_U32 x, HI_U32 a)
{
    if (0 == a)
    {
       return x;
    }

    return ( (( x + (a - 1) ) / a ) * a);
}

#else

#define IO_ADDRESS(addr) (addr)

extern HI_S32 GfxWinReviseOutRect(const HI_RECT_S *tmp_virtscreen,
                                         const HI_DRV_DISP_OFFSET_S *stOffsetInfo,
                                         const HI_RECT_S *stFmtResolution,
                                         const HI_RECT_S *stPixelFmtResolution,
                                         HI_RECT_S *stToBeRevisedRect,
                                         HI_RECT_S *stRevisedRect);

/***************************************************************************************
* func          : OPTM_GpInitFromDisp
* description   : CNcomment: 初始化参数，参数来源于display  CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GpInitFromDisp(OPTM_GFX_GP_E enGPId, HI_BOOL Support4KLogo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_DRV_DISPLAY_E enDisp = HI_DRV_DISPLAY_0;
    HI_DISP_DISPLAY_INFO_S pstInfo;

#ifndef CONFIG_GFX_PQ
    OPTM_COLOR_SPACE_E enGpCsc = OPTM_CS_BT709_YUV_LIMITED;
#else
    HI_PQ_GFX_COLOR_SPACE_E  enGpCsc;
#endif

    HIFB_CHECK_ARRAY_OVER_RETURN(enGPId,OPTM_GFX_GP_BUTT,HI_FAILURE);

    if (HI_FALSE == g_stGfxGPDevice[enGPId].bOpen)
    {
        return HI_FAILURE;
    }

    enDisp = (enGPId == OPTM_GFX_GP_0) ? (HI_DRV_DISPLAY_1) : (HI_DRV_DISPLAY_0);

    HI_GFX_Memset(&pstInfo, 0, sizeof(HI_DISP_DISPLAY_INFO_S));

    Ret = HI_DISP_GetDisplayInfo(enDisp, &pstInfo);
    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    g_stGfxGPDevice[enGPId].bInterface = pstInfo.bInterlace;

    GfxWinReviseOutRect(&pstInfo.stVirtaulScreen,
                        &pstInfo.stOffsetInfo,
                        &pstInfo.stFmtResolution,
                        &pstInfo.stPixelFmtResolution,
                        &pstInfo.stVirtaulScreen,
                        &g_stGfxGPDevice[enGPId].stOutRect);

    if ((OPTM_GFX_GP_0 == enGPId) && (HI_TRUE == Support4KLogo))
    {
        g_stGfxGPDevice[enGPId].stOutRect.s32X      = 0;
        g_stGfxGPDevice[enGPId].stOutRect.s32Y      = 0;
        g_stGfxGPDevice[enGPId].stOutRect.s32Width  = pstInfo.stFmtResolution.s32Width;
        g_stGfxGPDevice[enGPId].stOutRect.s32Height = pstInfo.stFmtResolution.s32Height;
    }


    if ((HI_TRUE == pstInfo.bIsMaster) && (enGPId == OPTM_GFX_GP_0))
    {
        g_enOptmGfxWorkMode = HIFB_GFX_MODE_HD_WBC;
    }

    OPTM_GPRecovery(enGPId);

#ifndef CONFIG_GFX_PQ
    enGpCsc = OPTM_AdaptCscTypeFromDisp(pstInfo.eColorSpace);
#else
    enGpCsc = PQ_AdaptCscTypeFromDisp(pstInfo.eColorSpace);
#endif

    g_stGfxGPDevice[enGPId].enOutputCsc = enGpCsc;
    OPTM_GPSetCsc(enGPId, &g_stGfxGPDevice[enGPId].stCscPara, g_stGfxGPDevice[enGPId].bBGRState);

    return HI_SUCCESS;
}
#endif


/***************************************************************************************
* func          : OPTM_GFX_GetDevCap
* description   : CNcomment: 获取图层能力级 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static inline HI_VOID  OPTM_GFX_GetDevCap(const HIFB_CAPABILITY_S **pstCap)
{
    *pstCap = &g_stGfxCap[0];
}

/***************************************************************************************
* func          : OPTM_GetGfxHalId
* description   : CNcomment: hifb ID 转换成 图层ID，配寄存器使用 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static OPTM_VDP_LAYER_GFX_E OPTM_GetGfxHalId(HIFB_LAYER_ID_E enLayerId)
{
    if (enLayerId < HIFB_LAYER_HD_2)
    {
        return (OPTM_VDP_LAYER_GFX_E)enLayerId;
    }
    else if(enLayerId == HIFB_LAYER_HD_2)
    {
        return OPTM_VDP_LAYER_GFX3;
    }
    else if(enLayerId == HIFB_LAYER_SD_0)
    {
        return (OPTM_VDP_LAYER_GFX_E)enLayerId;
    }
    else
    {
        return OPTM_VDP_LAYER_GFX_BUTT;
    }
}


/***************************************************************************************
* func          : OPTM_AdaptCscTypeFromDisp
* description   : CNcomment: 从disp中获取CSC类型 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
#ifndef CONFIG_GFX_PQ
static OPTM_COLOR_SPACE_E OPTM_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc)
{
    switch (enHiDrvCsc)
    {
        case HI_DRV_CS_BT601_YUV_LIMITED:
            return OPTM_CS_BT601_YUV_LIMITED;
        case HI_DRV_CS_BT601_YUV_FULL:
            return OPTM_CS_BT601_YUV_FULL;
        case HI_DRV_CS_BT601_RGB_FULL:
            return OPTM_CS_BT601_RGB_FULL;
        case HI_DRV_CS_BT709_YUV_LIMITED:
            return OPTM_CS_BT709_YUV_LIMITED;
        case HI_DRV_CS_BT709_YUV_FULL:
            return OPTM_CS_BT709_YUV_FULL;
        case HI_DRV_CS_BT709_RGB_FULL:
            return OPTM_CS_BT709_RGB_FULL;
        default:
            return OPTM_CS_BUTT;
    }
}
#else
static HI_PQ_GFX_COLOR_SPACE_E PQ_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc)
{
    switch (enHiDrvCsc)
    {
        case HI_DRV_CS_BT601_YUV_LIMITED:
            return PQ_GFX_CS_BT601_YUV_LIMITED;
        case HI_DRV_CS_BT601_YUV_FULL:
            return PQ_GFX_CS_BT601_YUV_FULL;
        case HI_DRV_CS_BT601_RGB_FULL:
            return PQ_GFX_CS_BT601_RGB_FULL;
        case HI_DRV_CS_BT709_YUV_LIMITED:
            return PQ_GFX_CS_BT709_YUV_LIMITED;
        case HI_DRV_CS_BT709_YUV_FULL:
            return PQ_GFX_CS_BT709_YUV_FULL;
        case HI_DRV_CS_BT709_RGB_FULL:
            return PQ_GFX_CS_BT709_RGB_FULL;
#ifdef CONFIG_HIFB_BI2020_SUPPORT
        case  HI_DRV_CS_BT2020_YUV_LIMITED:
            return PQ_GFX_CS_BT2020_YUV_LIMITED;
        case HI_DRV_CS_BT2020_YUV_FULL:
            return PQ_GFX_CS_BT2020_YUV_LIMITED;
        case HI_DRV_CS_BT2020_RGB_LIMITED:
            return PQ_GFX_CS_BT2020_RGB_FULL;
        case HI_DRV_CS_BT2020_RGB_FULL:
            return PQ_GFX_CS_BT2020_RGB_FULL;
#endif
        default:
            return PQ_GFX_CS_BUTT;
    }
}
#endif


#if !defined(HI_BUILD_IN_BOOT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
/***************************************************************************************
* func           : OPTM_AdaptTriDimModeFromDisp
* description : CNcomment: 从disp中获取3D模式 CNend\n
* param[in]  : HI_VOID
* retval        : NA
* others:      : NA
***************************************************************************************/
static HIFB_STEREO_MODE_E OPTM_AdaptTriDimModeFromDisp(OPTM_VDP_DISP_MODE_E enDispStereo)
{
    switch (enDispStereo)
    {
        case VDP_DISP_MODE_2D:
            return HIFB_STEREO_MONO;
        case VDP_DISP_MODE_SBS:
            return HIFB_STEREO_SIDEBYSIDE_HALF;
        case VDP_DISP_MODE_TAB:
            return HIFB_STEREO_TOPANDBOTTOM;
        case VDP_DISP_MODE_FP:
            return HIFB_STEREO_FRMPACKING;
        default:
            return HIFB_STEREO_BUTT;
    }

    return HIFB_STEREO_BUTT;
}
#endif


/***************************************************************************************
* func          : OPTM_GPDATA_Init
* description : CNcomment: GP data inital  CNend\n
* param[in]  : HI_VOID
* retval        : NA
* others:      : NA
***************************************************************************************/
static HI_VOID OPTM_GPDATA_Init(HI_VOID)
{
    HI_GFX_Memset(&(g_stGfxDevice[0])   , 0, sizeof(g_stGfxDevice));
    HI_GFX_Memset(&(g_stGfxGPDevice[0]) , 0, sizeof(g_stGfxGPDevice));
    HI_GFX_Memset(&(g_stGfxGPIrq[0])    , 0, sizeof(g_stGfxGPIrq));
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func            : OPTM_Aapt_Module_GetFunction
* description   : CNcomment: 获取函数指针 CNend\n
* param[in]    : HI_VOID
* retval          : NA
* others:        : NA
***************************************************************************************/
static HI_S32 OPTM_Aapt_Module_GetFunction(HI_U32 u32ModuleID, HI_VOID** ppFunc)
{
    if (HI_NULL == ppFunc)
    {
        return HI_FAILURE;
    }

    if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(u32ModuleID, ppFunc))
    {
        return HI_FAILURE;
    }

    if (HI_NULL == *ppFunc)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
#endif


/***************************************************************************************
* func          : OPTM_GfxInit
* description   : CNcomment: 驱动初始化 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxInit(HI_VOID)
{
#if !defined(CONFIG_GFX_PQ) || defined(HI_BUILD_IN_BOOT)
    HI_S32 s32Ret = HI_SUCCESS;
#endif

    if (OPTM_ENABLE == gs_GFXInitFlag)
    {
        return HI_SUCCESS;
    }

#ifdef HI_BUILD_IN_BOOT
    gs_Phyaddr = (volatile HI_U32*)IO_ADDRESS(CONFIG_VDP_REG_BASEADDR);
#else
    gs_Phyaddr = (volatile HI_U32*)HI_GFX_REG_MAP(CONFIG_VDP_REG_BASEADDR, CONFIG_VDP_SIZE);
#endif
    if (NULL == gs_Phyaddr)
    {
        HIFB_ERROR("map vdp register failed\n");
        return HI_FAILURE;
    }

    OPTM_VDP_DRIVER_Initial(gs_Phyaddr);

    OPTM_GPDATA_Init();
    HIFB_WBC2_Init();

#ifndef CONFIG_GFX_PQ
    s32Ret = OPTM_ALG_GZmeVdpComnInit(&gs_stGPZme);
    if (HI_SUCCESS != s32Ret)
    {
        HIFB_ERROR("Malloc Gfxzme coeff buffer failed\n");
        return s32Ret;
    }
#endif

#ifdef HI_BUILD_IN_BOOT
    s32Ret = DRV_PQ_InitGfxZme();
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }
#endif

    gs_GFXInitFlag = OPTM_ENABLE;

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_GfxDeInit
* description   : CNcomment: 图形设备去初始化 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GfxDeInit(HI_VOID)
{
#ifndef HI_BUILD_IN_BOOT
    HI_U32 u32LayerId = HIFB_LAYER_HD_0;

    if (OPTM_DISABLE == gs_GFXInitFlag)
    {
        return HI_SUCCESS;
    }

    for (u32LayerId = HIFB_LAYER_HD_0; u32LayerId < HIFB_LAYER_ID_BUTT; u32LayerId++)
    {
        if (HI_FALSE != g_stGfxDevice[u32LayerId].bOpened)
        {
            (HI_VOID)OPTM_GfxCloseLayer(u32LayerId);
        }
    }

    #ifndef CONFIG_GFX_PQ
        OPTM_ALG_GZmeVdpComnDeInit(&gs_stGPZme);
    #endif

    HIFB_WBC2_Dinit();
    HIFB_WBC2_SetTcFlag(HI_FALSE);

    gs_GFXInitFlag   = OPTM_DISABLE;
    ps_DispExportFuncs = HI_NULL;

    if (NULL != gs_Phyaddr)
    {
        HI_GFX_REG_UNMAP((HI_VOID*)gs_Phyaddr);
    }
#endif

    return HI_SUCCESS;
}


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : OPTM_3DMode_Callback
* description   : CNcomment: 执行3D工作对列函数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID OPTM_3DMode_Callback(struct work_struct *data)
{
    HI_U32 i;
    HI_U32 u32CTypeFlag;
    HI_U32 u32LayerCount;
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;
    OPTM_GFX_WORK_S *pst3DModeWork = HI_NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(data);
    pst3DModeWork = container_of(data, OPTM_GFX_WORK_S, work);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pst3DModeWork);

    enGpId = (OPTM_GFX_GP_E)(pst3DModeWork->u32Data);
    HIFB_CHECK_ARRAY_OVER_UNRETURN(enGpId,OPTM_GFX_GP_BUTT);

    u32LayerCount = (OPTM_GFX_GP_0 == enGpId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    HIFB_CHECK_ARRAY_OVER_UNRETURN(u32LayerCount,OPTM_GP_SUPPORT_MAXLAYERNUM);

    for (i = 0; i < u32LayerCount;i++)
    {
        u32CTypeFlag = g_stGfxGPIrq[enGpId].stGfxCallBack[i].u32CTypeFlag;
        if (0 == u32CTypeFlag)
        {
            continue;
        }

        if (u32CTypeFlag & HIFB_CALLBACK_TYPE_3DMode_CHG)
        {
            if (g_stGfxGPIrq[enGpId].stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].pFunc)
            {
                g_stGfxGPIrq[enGpId].stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].pFunc(
                    g_stGfxGPIrq[enGpId].stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].pParam0,
                    (HI_VOID*)&g_stGfxGPDevice[enGpId].enTriDimMode);
            }
        }
    }
}
#endif


/***************************************************************************************
* func          : OPTM_ALG_Init
* description   : CNcomment: 算法初始化 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID OPTM_ALG_Init(OPTM_GFX_GP_E enGPId)
{
#ifndef CONFIG_GFX_PQ
    OPTM_ALG_GDTI_RTL_PARA_S stDtiRtlPara;
    HI_GFX_Memset(&stDtiRtlPara, 0, sizeof(stDtiRtlPara));

    OPTM_ALG_GDtiInit(HI_NULL, &stDtiRtlPara);

    OPTM_VDP_GP_SetTiHpCoef(enGPId, VDP_TI_MODE_CHM, (HI_S32 *)stDtiRtlPara.s32CTIHPTmp);
    OPTM_VDP_GP_SetTiHpCoef(enGPId, VDP_TI_MODE_LUM, (HI_S32 *)stDtiRtlPara.s32LTIHPTmp);

    OPTM_VDP_GP_SetTiGainRatio(enGPId, VDP_TI_MODE_CHM, (HI_S32)stDtiRtlPara.s16CTICompsatRatio);
    OPTM_VDP_GP_SetTiGainRatio(enGPId, VDP_TI_MODE_LUM, (HI_S32)stDtiRtlPara.s16LTICompsatRatio);

    OPTM_VDP_GP_SetTiCoringThd(enGPId, VDP_TI_MODE_CHM, (HI_U32)stDtiRtlPara.u16CTICoringThrsh);
    OPTM_VDP_GP_SetTiCoringThd(enGPId, VDP_TI_MODE_LUM, (HI_U32)stDtiRtlPara.u16LTICoringThrsh);

    OPTM_VDP_GP_SetTiSwingThd(enGPId, VDP_TI_MODE_CHM, (HI_U32)stDtiRtlPara.u16CTIOverSwingThrsh, (HI_U32)stDtiRtlPara.u16CTIUnderSwingThrsh);
    OPTM_VDP_GP_SetTiSwingThd(enGPId, VDP_TI_MODE_LUM, (HI_U32)stDtiRtlPara.u16LTIOverSwingThrsh, (HI_U32)stDtiRtlPara.u16LTIUnderSwingThrsh);

    OPTM_VDP_GP_SetTiMixRatio(enGPId, VDP_TI_MODE_CHM, (HI_U32)stDtiRtlPara.u8CTIMixingRatio);
    OPTM_VDP_GP_SetTiMixRatio(enGPId, VDP_TI_MODE_LUM, (HI_U32)stDtiRtlPara.u8LTIMixingRatio);

    OPTM_VDP_GP_SetTiHfThd(enGPId, VDP_TI_MODE_LUM, (HI_U32 *)stDtiRtlPara.u32LTIHFreqThrsh);
    OPTM_VDP_GP_SetTiGainCoef(enGPId, VDP_TI_MODE_LUM, (HI_U32 *)stDtiRtlPara.u32LTICompsatMuti);
#endif
    return;
}


/***************************************************************************************
* func          : OPTM_GPOpen
* description   : CNcomment: 打开GP设备并设置ZME系数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GPOpen(OPTM_GFX_GP_E enGPId)
{
    HI_U32 i = 0;
    OPTM_VDP_BKG_S  stBkg = {0};
    HI_U32 u32InitLayerID = 0;
    HI_U32 u32MaxLayerCount = 0;


    HIFB_CHECK_ARRAY_OVER_RETURN(enGPId,OPTM_GFX_GP_BUTT, HI_FAILURE);

    if (HI_TRUE == g_stGfxGPDevice[enGPId].bOpen)
    {
        return HI_SUCCESS;
    }

#ifndef HI_BUILD_IN_BOOT
    if (HI_NULL == ps_DispExportFuncs)
    {
        if (HI_SUCCESS != OPTM_Aapt_Module_GetFunction(HI_ID_DISP, (HI_VOID**)&ps_DispExportFuncs))
        {
            HIFB_ERROR("Fail to get disp export functions!\n");
            return HI_FAILURE;
        }

        HIFB_CHECK_NULLPOINTER_RETURN(ps_DispExportFuncs, HI_FAILURE);
    }

    if (OPTM_GFX_GP_0 == enGPId)
    {
        init_waitqueue_head(&g_stGfxWbc2.WaiteWbcWorkqueueMutex);

        g_stGfxGPDevice[enGPId].queue = create_workqueue(HIFB_WORK_QUEUE);

        if (HI_NULL != g_stGfxGPDevice[enGPId].queue)
        {
            INIT_WORK(&g_stGfxGPDevice[enGPId].stOpenSlvWork.work,   HIFB_WBC_StartWorkQueue);
            INIT_WORK(&g_stGfxGPDevice[enGPId].st3DModeChgWork.work, OPTM_3DMode_Callback);
            HIFB_INFO("create_workqueue success.\n");
        }
    }
#endif

    HI_GFX_Memset(&g_stGfxGPIrq[enGPId], 0, sizeof(OPTM_GP_IRQ_S));

   g_stGfxGPDevice[enGPId].u32ZmeDeflicker = (OPTM_GFX_GP_0 == enGPId)?0:1;

    g_stGfxGPDevice[enGPId].u32Alpha          = 0xff;
    g_stGfxGPDevice[enGPId].enReadMode        = VDP_RMODE_PROGRESSIVE;
    g_stGfxGPDevice[enGPId].stBkg             = stBkg;
#ifndef CONFIG_GFX_PQ
    g_stGfxGPDevice[enGPId].enInputCsc        = OPTM_CS_BT709_RGB_FULL;
    g_stGfxGPDevice[enGPId].enOutputCsc       = OPTM_CS_UNKNOWN;
#else
    g_stGfxGPDevice[enGPId].enInputCsc        = PQ_GFX_CS_BT709_RGB_FULL;
    g_stGfxGPDevice[enGPId].enOutputCsc       = PQ_GFX_CS_BUTT;
#endif
    g_stGfxGPDevice[enGPId].bBGRState         = HI_FALSE;
    g_stGfxGPDevice[enGPId].bGpClose          = HI_FALSE;
    g_stGfxGPDevice[enGPId].bRecoveryInNextVT = HI_TRUE;
    g_stGfxGPDevice[enGPId].bDispInitial      = HI_FALSE;

    if (OPTM_GFX_GP_0 == enGPId)
    {
        g_stGfxGPDevice[enGPId].enMixg       = VDP_CBM_MIXG0;
        g_stGfxGPDevice[enGPId].enGpHalId    = OPTM_VDP_LAYER_GP0;
        g_stGfxGPDevice[enGPId].enDispCh     = OPTM_DISPCHANNEL_1;
        u32InitLayerID                       = (HI_U32)HIFB_LAYER_HD_0;
        u32MaxLayerCount                     = (HI_U32)(OPTM_GP0_GFX_COUNT + u32InitLayerID - 1);
    }
    else
    {
        g_stGfxGPDevice[enGPId].enMixg       = VDP_CBM_MIXG1;
        g_stGfxGPDevice[enGPId].enGpHalId    = OPTM_VDP_LAYER_GP1;
        g_stGfxGPDevice[enGPId].enDispCh     = OPTM_DISPCHANNEL_0;
        u32InitLayerID                       = (HI_U32)HIFB_LAYER_SD_0;
        u32MaxLayerCount                     = (HI_U32)(OPTM_GP1_GFX_COUNT + u32InitLayerID - 1);
    }

    OPTM_VDP_GP_SetLayerGalpha(enGPId, g_stGfxGPDevice[enGPId].u32Alpha);
    OPTM_VDP_GP_SetReadMode   (enGPId, g_stGfxGPDevice[enGPId].enReadMode);
    OPTM_VDP_CBM_SetMixerBkg  (g_stGfxGPDevice[enGPId].enMixg, g_stGfxGPDevice[enGPId].stBkg);

    g_stGfxGPDevice[enGPId].u32Prior = 0x0;

    HIFB_CHECK_ARRAY_OVER_RETURN(u32MaxLayerCount,OPTM_MAX_LOGIC_HIFB_LAYER, HI_FAILURE);

    for (i = u32InitLayerID; i <= u32MaxLayerCount; i++)
    {
        g_stGfxDevice[i].u32ZOrder = i;
        OPTM_VDP_CBM_SetMixerPrio(g_stGfxGPDevice[enGPId].enMixg, i, g_stGfxDevice[i].u32ZOrder);
        g_stGfxDevice[i].enGfxHalId = OPTM_GetGfxHalId(i);
        g_stGfxGPDevice[enGPId].u32Prior |= (i < 2) ? ((i+1)<<(i*4)) : (((i+1)+1)<<(i*4));
    }

    OPTM_ALG_Init(enGPId);

    g_stGfxGPDevice[enGPId].bOpen = HI_TRUE;

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GPClose
* description   : CNcomment: 关闭GP设备 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GPClose(OPTM_GFX_GP_E enGPId)
{
    HIFB_CHECK_ARRAY_OVER_RETURN(enGPId,OPTM_GFX_GP_BUTT, HI_FAILURE);

    if (HI_FALSE == g_stGfxGPDevice[enGPId].bOpen)
    {
        return HI_SUCCESS;
    }

    g_enOptmGfxWorkMode = HIFB_GFX_MODE_NORMAL;

#ifndef HI_BUILD_IN_BOOT
    OPTM_SetCallbackToDisp(enGPId, (IntCallBack)DRV_HIFB_ADP_UpDataCallBack,   HI_DRV_DISP_C_INTPOS_90_PERCENT,  HI_FALSE);
    OPTM_SetCallbackToDisp(enGPId, (IntCallBack)DRV_HIFB_ADP_FrameEndCallBack, HI_DRV_DISP_C_INTPOS_100_PERCENT, HI_FALSE);

    if (g_stGfxGPDevice[enGPId].queue)
    {
        destroy_workqueue(g_stGfxGPDevice[enGPId].queue);
        g_stGfxGPDevice[enGPId].queue = HI_NULL;
    }
#endif

    g_stGfxGPDevice[enGPId].bOpen            = HI_FALSE;
    g_stGfxGPDevice[enGPId].bDispInitial     = HI_FALSE;
    g_stGfxGPDevice[enGPId].bNeedExtractLine = HI_FALSE;
    g_stGfxGPDevice[enGPId].bMaskFlag        = HI_FALSE;

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_GfxSetLayerReadMode
* description   : CNcomment: 设置读取数据模式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerReadMode(HIFB_LAYER_ID_E enLayerId, OPTM_VDP_DATA_RMODE_E enReadMode)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_ARRAY_OVER_RETURN(enLayerId,OPTM_MAX_LOGIC_HIFB_LAYER, HI_FAILURE);
    enGPId = g_stGfxDevice[enLayerId].enGPId;

    OPTM_VDP_GFX_SetReadMode(g_stGfxDevice[enLayerId].enGfxHalId, enReadMode);
    OPTM_VDP_GP_SetReadMode(g_stGfxGPDevice[enGPId].enGpHalId,   enReadMode);

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GfxInitLayer
* description   : CNcomment: 初始化图层信息 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_GfxInitLayer(HIFB_LAYER_ID_E enLayerId)
{
    OPTM_VDP_BKG_S stBkg = {0};

    HIFB_CHECK_ARRAY_OVER_UNRETURN(enLayerId,OPTM_MAX_LOGIC_HIFB_LAYER);
    init_waitqueue_head(&(g_stGfxDevice[enLayerId].vblEvent));

    g_stGfxDevice[enLayerId].stBkg        = stBkg;
    g_stGfxDevice[enLayerId].enGfxHalId   = OPTM_GetGfxHalId(enLayerId);
    g_stGfxDevice[enLayerId].CscState     = OPTM_CSC_SET_PARA_RGB;
    g_stGfxDevice[enLayerId].enBitExtend  = VDP_GFX_BITEXTEND_3RD;
    g_stGfxDevice[enLayerId].enReadMode   = VDP_RMODE_PROGRESSIVE;
    g_stGfxDevice[enLayerId].enUpDateMode = VDP_RMODE_PROGRESSIVE;
#ifdef CONFIG_HIFB_GFX3_TO_GFX5
    g_stGfxDevice[enLayerId].enGPId       = (g_stGfxDevice[enLayerId].enGfxHalId > OPTM_VDP_LAYER_GFX2) ? OPTM_GFX_GP_1 : OPTM_GFX_GP_0;
#else
    g_stGfxDevice[enLayerId].enGPId       = (g_stGfxDevice[enLayerId].enGfxHalId > OPTM_VDP_LAYER_GFX3) ? OPTM_GFX_GP_1 : OPTM_GFX_GP_0;
#endif

    OPTM_VDP_GFX_SetNoSecFlag  (g_stGfxDevice[enLayerId].enGfxHalId, HI_TRUE);
    OPTM_VDP_GFX_SetDcmpEnable (g_stGfxDevice[enLayerId].enGfxHalId, HI_FALSE);
    OPTM_VDP_GFX_SetLayerBkg   (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].stBkg);
    OPTM_VDP_GFX_SetBitExtend  (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].enBitExtend);
    OPTM_VDP_GFX_SetReadMode   (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].enReadMode);
    OPTM_VDP_GFX_SetUpdMode    (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].enUpDateMode);

#ifdef CONFIG_HIFB_GFX3_TO_GFX5
    if (OPTM_VDP_LAYER_GFX3 == g_stGfxDevice[enLayerId].enGfxHalId)
    {
        OPTM_VDP_SetLayerConnect(OPTM_VDP_CONNECT_G3_DHD1);
        OPTM_VDP_OpenGFX3(HI_TRUE);
    }
#endif

    return;
}


/***************************************************************************************
* func          : OPTM_GFX_ReleaseClutBuf
* description   : CNcomment: 释放调色板内存 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_ReleaseClutBuf(HIFB_LAYER_ID_E enLayerId)
{
#ifndef HI_BUILD_IN_BOOT
    HIFB_CHECK_ARRAY_OVER_RETURN(enLayerId,OPTM_MAX_LOGIC_HIFB_LAYER,HI_FAILURE);

    if (HI_FALSE == g_stGfxCap[enLayerId].bHasCmapReg)
    {
       return HI_SUCCESS;
    }

    if (0 == g_stGfxDevice[enLayerId].stCluptTable.pu8StartVirAddr)
    {
        return HI_SUCCESS;
    }

    OPTM_UnmapAndRelease(&(g_stGfxDevice[enLayerId].stCluptTable));
    g_stGfxDevice[enLayerId].stCluptTable.pu8StartVirAddr  = NULL;
    g_stGfxDevice[enLayerId].stCluptTable.u32StartPhyAddr  = 0;
    g_stGfxDevice[enLayerId].stCluptTable.u32StartSmmuAddr = 0;
    g_stGfxDevice[enLayerId].stCluptTable.u32Size          = 0;
    g_stGfxDevice[enLayerId].stCluptTable.bSmmu            = HI_FALSE;
#endif

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_GPSetCsc
* description   : CNcomment: 设置GP CSC系数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GPSetCsc(OPTM_GFX_GP_E enGfxGpId, OPTM_GFX_CSC_PARA_S *pstCscPara, HI_BOOL bIsBGRIn)
{
    HI_PQ_GFX_CSC_PARA_S stGfxCscPara;

    HI_UNUSED(pstCscPara);
    HIFB_CHECK_ARRAY_OVER_RETURN(enGfxGpId,OPTM_GFX_GP_BUTT,HI_FAILURE);

    g_stGfxGPDevice[enGfxGpId].enInputCsc = PQ_GFX_CS_BT709_RGB_FULL;

    OPTM_CheckGPMask_BYGPID(enGfxGpId);

    stGfxCscPara.sGfxCscMode.eInputCS   = g_stGfxGPDevice[enGfxGpId].enInputCsc;
    stGfxCscPara.sGfxCscMode.eOutputCS  = g_stGfxGPDevice[enGfxGpId].enOutputCsc;
    stGfxCscPara.bIsBGRIn   = bIsBGRIn;

#ifndef HI_BUILD_IN_BOOT
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs,HI_FAILURE);
    if (enGfxGpId == OPTM_GFX_GP_0)
    {
        gs_pstPqFuncs->pfnPQ_SetGfxCscCoef(PQ_GFX_GP0,&stGfxCscPara);
    }
    else
    {
        gs_pstPqFuncs->pfnPQ_SetGfxCscCoef(PQ_GFX_GP1,&stGfxCscPara);
    }
#else
    if (enGfxGpId == OPTM_GFX_GP_0)
    {
        DRV_PQ_SetGfxCscCoef(PQ_GFX_GP0, &stGfxCscPara);
    }
    else
    {
        DRV_PQ_SetGfxCscCoef(PQ_GFX_GP1, &stGfxCscPara);
    }
#endif

    OPTM_VDP_GP_SetCscEnable(g_stGfxGPDevice[enGfxGpId].enGpHalId, HI_TRUE);
    OPTM_VDP_GP_SetRegUp(g_stGfxGPDevice[enGfxGpId].enGpHalId);

    return HI_SUCCESS;
}


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : OPTM_GfxSetCallback
* description   : CNcomment: set call back function
                             设置中断响应函数,在对应的中断中调用该对应的赋值函数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GfxSetCallback(HIFB_LAYER_ID_E enLayerId, IntCallBack pCallBack, HIFB_CALLBACK_TPYE_E eCallbackType)
{
    HI_U32 u32GfxIndex = 0;
    OPTM_GFX_GP_E  enGPId = OPTM_GFX_GP_0;

    if (eCallbackType >= HIFB_CALLBACK_TYPE_BUTT)
    {
        HIFB_ERROR("Fail to set callback func!\n");
        return HI_FAILURE;
    }

    HIFB_CHECK_ARRAY_OVER_RETURN(enLayerId,OPTM_MAX_LOGIC_HIFB_LAYER,HI_FAILURE);
    enGPId = g_stGfxDevice[enLayerId].enGPId;
    HIFB_CHECK_ARRAY_OVER_RETURN(enGPId,OPTM_GFX_GP_BUTT,HI_FAILURE);

    u32GfxIndex = (enLayerId > HIFB_LAYER_HD_3) ? (enLayerId - HIFB_LAYER_HD_3 - 1) : enLayerId;
    if (u32GfxIndex >= OPTM_GP_SUPPORT_MAXLAYERNUM)
    {
        HIFB_ERROR("Fail to set callback func!\n");
        return HI_FAILURE;
    }

    gs_CallBackLayerId[enLayerId] = enLayerId;
    if (HI_NULL != pCallBack)
    {
        g_stGfxGPIrq[enGPId].stGfxCallBack[u32GfxIndex].stGfxIrq[eCallbackType].pFunc     = pCallBack;
        g_stGfxGPIrq[enGPId].stGfxCallBack[u32GfxIndex].stGfxIrq[eCallbackType].pParam0   = (HI_VOID*)&gs_CallBackLayerId[enLayerId];
        g_stGfxGPIrq[enGPId].stGfxCallBack[u32GfxIndex].u32CTypeFlag |= eCallbackType;

        return HI_SUCCESS;
    }

    g_stGfxGPIrq[enGPId].stGfxCallBack[u32GfxIndex].u32CTypeFlag &= ~((HI_U32)eCallbackType);
    g_stGfxGPIrq[enGPId].stGfxCallBack[u32GfxIndex].stGfxIrq[eCallbackType].pFunc = HI_NULL;

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_CheckGfxCallbackReg
* description   : CNcomment: check whether call back function have register
                             判断相应的回调函数是否被注册 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_CheckGfxCallbackReg(OPTM_GFX_GP_E enGPId, HIFB_CALLBACK_TPYE_E eCallbackType)
{
    HI_U32 u32LayerCount = (enGPId == OPTM_GFX_GP_0) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    HI_U32 u32LayerId = 0;

    HIFB_CHECK_ARRAY_OVER_RETURN(enGPId,OPTM_GFX_GP_BUTT,HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN(u32LayerCount,OPTM_GP_SUPPORT_MAXLAYERNUM,HI_FAILURE);

    for (u32LayerId = 0; u32LayerId < u32LayerCount; u32LayerId++)
    {
        if (g_stGfxGPIrq[enGPId].stGfxCallBack[u32LayerId].u32CTypeFlag & eCallbackType)
        {
            if (g_stGfxGPIrq[enGPId].stGfxCallBack[u32LayerId].stGfxIrq[eCallbackType].pFunc)
            {
                return HI_SUCCESS;
            }
        }
    }

    return HI_FAILURE;
}
#endif


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : OPTM_GetScreenRectFromDispInfo
* description   : CNcomment: 从disp中获取screen rect CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GetScreenRectFromDispInfo(const HI_RECT_S *tmp_virtscreen,      \
                                                          const OPTM_GFX_OFFSET_S *stOffsetInfo,\
                                                          const HI_RECT_S *stFmtResolution,     \
                                                          const HI_RECT_S *stPixelFmtResolution,\
                                                          HI_RECT_S *stScreenRect)
{
    OPTM_GFX_OFFSET_S tmp_offsetInfo = *stOffsetInfo;

    HIFB_CHECK_NULLPOINTER_RETURN(tmp_virtscreen,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stOffsetInfo,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stFmtResolution,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stPixelFmtResolution,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stScreenRect,HI_FAILURE);

    if (tmp_virtscreen->s32Width == 0 || tmp_virtscreen->s32Height == 0)
    {
        return HI_FAILURE;
    }

    if ( (stFmtResolution->s32Width * 2) == stPixelFmtResolution->s32Width)
    {
        tmp_offsetInfo.u32Left  *= 2;
        tmp_offsetInfo.u32Right *= 2;
    }

    stScreenRect->s32X      = tmp_offsetInfo.u32Left;
    stScreenRect->s32Y      = tmp_offsetInfo.u32Top;
    stScreenRect->s32Width  = (stPixelFmtResolution->s32Width - tmp_offsetInfo.u32Left - tmp_offsetInfo.u32Right);
    stScreenRect->s32Height = (stPixelFmtResolution->s32Height - tmp_offsetInfo.u32Top - tmp_offsetInfo.u32Bottom);
    stScreenRect->s32X      = OPTM_AlignUp(stScreenRect->s32X, 2);
    stScreenRect->s32Y      = OPTM_AlignUp(stScreenRect->s32Y, 2);
    stScreenRect->s32Width  = OPTM_AlignUp(stScreenRect->s32Width, 2);
    stScreenRect->s32Height = OPTM_AlignUp(stScreenRect->s32Height, 2);

    return HI_SUCCESS;
}
#endif


#ifndef HI_BUILD_IN_BOOT
static HI_VOID DRV_HIFB_ADP_FrameEndCallBack(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
#ifdef CFG_HIFB_FENCE_SUPPORT
    HI_U32 u32CTypeFlag = 0;
    HI_VOID* pLayerId   = NULL;
    HI_U32 WorkedLayerDdr = 0;
    HI_U32 WillWorkLayerDdr = 0;
#endif
    HIFB_LAYER_ID_E enLayerId = HIFB_LAYER_HD_0;
    OPTM_GFX_GP_E  *pEnGpId   = (OPTM_GFX_GP_E *)u32Param0;

    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param1);
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(*pEnGpId);

    if (OPTM_GFX_GP_0 != *pEnGpId)
    {
        return;
    }

    if (HI_FALSE == g_stGfxGPDevice[*pEnGpId].bOpen)
    {
        return;
    }

    (HI_VOID)HIFB_WBC_FrameEndProcess(*pEnGpId);

    for (enLayerId = HIFB_LAYER_HD_0; enLayerId <= HIFB_LAYER_HD_3; enLayerId++)
    {
 #ifdef CFG_HIFB_FENCE_SUPPORT
        pLayerId = g_stGfxGPIrq[*pEnGpId].stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].pParam0;

        HIFB_HAL_GetWorkedLayerAddr(enLayerId,&WorkedLayerDdr);
        HIFB_HAL_GetWillWorkLayerAddr(enLayerId,&WillWorkLayerDdr);
        if (WorkedLayerDdr != WillWorkLayerDdr)
        {
           return;
        }

        u32CTypeFlag = g_stGfxGPIrq[*pEnGpId].stGfxCallBack[enLayerId].u32CTypeFlag;
        if ((u32CTypeFlag & HIFB_CALLBACK_TYPE_FRAME_END) && (NULL != g_stGfxGPIrq[*pEnGpId].stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].pFunc))
        {
           g_stGfxGPIrq[*pEnGpId].stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].pFunc(pLayerId,HI_NULL);
        }
#endif

#ifdef OPTM_HIFB_WVM_ENABLE
        OPTM_GfxWVBCallBack(enLayerId);
#endif

    }

    return;
}

/***************************************************************************************
* func          : OPTM_DispInfoProcess
* description   : CNcomment: display信息处理 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_BOOL OPTM_DispInfoProcess(OPTM_VDP_LAYER_GP_E eGpId, HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo)
{
    HI_BOOL bDispInfoChange = HI_FALSE;
    HI_RECT_S stOutRect;

    HIFB_CHECK_GPID_SUPPORT_RETURN(eGpId, HI_FALSE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstDispInfo,HI_FALSE);

    if (   g_stGfxGPDevice[eGpId].stInRect.s32Width  != pstDispInfo->stDispInfo.stVirtaulScreen.s32Width ||
           g_stGfxGPDevice[eGpId].stInRect.s32Height != pstDispInfo->stDispInfo.stVirtaulScreen.s32Height)
    {
        bDispInfoChange = HI_TRUE;
    }

    HI_GFX_Memcpy(&g_stGfxGPDevice[eGpId].stInRect, &pstDispInfo->stDispInfo.stVirtaulScreen, sizeof(HI_RECT_S));

    OPTM_GetScreenRectFromDispInfo(&pstDispInfo->stDispInfo.stVirtaulScreen,
                                   (OPTM_GFX_OFFSET_S *)&pstDispInfo->stDispInfo.stOffsetInfo,
                                   &pstDispInfo->stDispInfo.stFmtResolution,
                                   &pstDispInfo->stDispInfo.stPixelFmtResolution,
                                   &stOutRect);

    if (g_stGfxGPDevice[eGpId].stOutRect.s32Width  != stOutRect.s32Width  ||
        g_stGfxGPDevice[eGpId].stOutRect.s32Height != stOutRect.s32Height ||
        g_stGfxGPDevice[eGpId].stOutRect.s32X != stOutRect.s32X           ||
        g_stGfxGPDevice[eGpId].stOutRect.s32Y != stOutRect.s32Y)
    {
        bDispInfoChange = HI_TRUE;
    }

    HI_GFX_Memcpy(&g_stGfxGPDevice[eGpId].stOutRect, &stOutRect, sizeof(HI_RECT_S));

    return bDispInfoChange;
}


/***************************************************************************************
* func          : OPTM_SET_GPMask
* description   : CNcomment: 在90%中断处理中调用,设置GP掩码 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_SET_GPMask(OPTM_GFX_GP_E enGPId, HI_BOOL bFlag)
{
    HI_U32           i             = 0;
    HI_BOOL          bEnable       = HI_FALSE;
    HI_U32           u32LayerCount = 0;
    HIFB_LAYER_ID_E  enLayerId     = HIFB_LAYER_HD_0;
    OPTM_GFX_WBC_S   *pstWbc2      = &g_stGfxWbc2;

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    if (HI_FALSE == g_stGfxGPDevice[enGPId].bOpen)
    {
        return HI_SUCCESS;
    }

    u32LayerCount = (OPTM_GFX_GP_0 == enGPId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enLayerId     = (OPTM_GFX_GP_0 == enGPId) ? HIFB_LAYER_HD_0    : HIFB_LAYER_SD_0;
    HIFB_CHECK_LAYERID_SUPPORT_RETURN((enLayerId + u32LayerCount), HI_FAILURE);

    g_stGfxGPDevice[enGPId].bMaskFlag = bFlag;

    if (IS_MASTER_GP((OPTM_GFX_GP_E)enGPId))
    {
        g_stGfxGPDevice[OPTM_SLAVER_GPID].bMaskFlag = bFlag;
    }

    if (IS_SLAVER_GP(enGPId))
    {
        bEnable = bFlag ? HI_FALSE : g_stGfxDevice[HIFB_LAYER_SD_0].bEnable;
        OPTM_VDP_GFX_SetLayerEnable (g_stGfxDevice[HIFB_LAYER_SD_0].enGfxHalId, bEnable);
        OPTM_VDP_WBC_SetEnable      (pstWbc2->enWbcHalId, bEnable);

        return HI_SUCCESS;
    }

    for (i = 0; i < u32LayerCount;i++)
    {
        if (HI_FALSE == g_stGfxDevice[enLayerId + i].bOpened)
        {
            continue;
        }

        bEnable = bFlag ? HI_FALSE : g_stGfxDevice[enLayerId+i].bEnable;
        OPTM_VDP_GFX_SetLayerEnable(g_stGfxDevice[enLayerId+i].enGfxHalId, bEnable);
        g_stGfxDevice[HIFB_LAYER_SD_0].bEnable = bEnable;
    }

    if (IS_MASTER_GP((OPTM_GFX_GP_E)enGPId))
    {
        g_stGfxDevice[HIFB_LAYER_SD_0].bEnable = bFlag ? HI_FALSE : g_stGfxDevice[HIFB_LAYER_SD_0].bEnable;
        g_stGfxGPDevice[OPTM_SLAVER_GPID].unUpFlag.bits.IsEnable = 1;
    }

    return HI_SUCCESS;
}


#ifndef HI_BUILD_IN_BOOT
static HI_VOID HIFB_ADP_GetResumeStatus(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbResume)
{
    if (enLayerId >= HIFB_LAYER_SD_0)
    {
       return;
    }

    *pbResume = g_stGfxGPDevice[0].bResume;
    g_stGfxGPDevice[0].bResume = HI_FALSE;

    return;
}

HI_VOID HIFB_ADP_SetLowPowerInfo(HIFB_LAYER_ID_E enLayerId,HIFB_ADP_LOWPOWER_INFO_S *pstLowPowerInfo)
{
   #ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
     HIFB_CHECK_NULLPOINTER_UNRETURN(pstLowPowerInfo);
     HIFB_HAL_EnableLayerLowPower(enLayerId, pstLowPowerInfo->LowPowerEn);
     HIFB_HAL_EnableGpLowPower(HIFB_ADP_ConvertLayerIdToGpId(enLayerId), pstLowPowerInfo->LowPowerEn);
     HIFB_HAL_SetLowPowerInfo(enLayerId,pstLowPowerInfo->LpInfo);
   #else
     HI_UNUSED(enLayerId);
     HI_UNUSED(pstLowPowerInfo);
   #endif
}
#endif


#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(HI_BUILD_IN_BOOT)
static HI_VOID HIFB_ADP_SetDeCmpDdrInfo(HIFB_LAYER_ID_E enLayerId, HI_U32 ARHeadDdr,HI_U32 ARDataDdr,HI_U32 GBHeadDdr,HI_U32 GBDataDdr,HI_U32 DeCmpStride)
{
    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(enLayerId);
    g_stGfxDevice[enLayerId].ARHeadDdr = ARHeadDdr;
    g_stGfxDevice[enLayerId].ARDataDdr = ARDataDdr;
    g_stGfxDevice[enLayerId].GBHeadDdr = GBHeadDdr;
    g_stGfxDevice[enLayerId].GBDataDdr = GBDataDdr;
    g_stGfxDevice[enLayerId].CmpStride = (HI_U16)DeCmpStride;
    DRV_HAL_SetDeCmpDdrInfo(enLayerId,ARHeadDdr,ARDataDdr,GBHeadDdr,GBDataDdr,DeCmpStride);
    return;
}

static HI_VOID HIFB_ADP_GetDeCmpStatus(HIFB_LAYER_ID_E enLayerId, DRV_HIFB_DECMPSTATUS_S *pstDeCmpStatus, HI_BOOL bDebug)
{
    DRV_HAL_GetDeCmpStatus(enLayerId, pstDeCmpStatus, bDebug);
    return;
}

static HI_VOID HIFB_ADP_SetVdpIntMask(HI_U32 IntMask)
{
    DRV_HAL_SetVdpIntMask(IntMask);
}

static HI_VOID HIFB_ADP_GetVdpIntMask(HI_U32 *pIntMask)
{
    DRV_HAL_GetVdpIntMask(pIntMask);
}

static HI_VOID OPTM_GFX_DECMP_Open(HIFB_LAYER_ID_E enLayerId)
{
    OPTM_VDP_GFX_SetDcmpEnable(enLayerId,HI_TRUE);
}

static HI_VOID OPTM_GFX_DECMP_Close(HIFB_LAYER_ID_E enLayerId)
{
    OPTM_VDP_GFX_SetDcmpEnable(enLayerId,HI_FALSE);
}
#endif


/***************************************************************************************
* func          : OPTM_GFX_GET_DECMP_Status
* description   : CNcomment: 获取G0的解压使能状态 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID OPTM_GFX_GET_DECMP_Status(HIFB_LAYER_ID_E enLayerId)
{
    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(enLayerId);
    OPTM_VDP_GFX_GetDcmpStatus(enLayerId,&(g_stGfxDevice[enLayerId].bDmpOpened));
}


HI_VOID DRV_HIFB_ADP_UpDataCallBack(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
#ifdef CFG_HIFB_PROC_SUPPORT
    HI_U32 CurScanline = 0;
    HI_U32 UpScanline  = 0;
    HI_U32 StartScanline = 0;
    HI_BOOL bScanLineAbnormal = HI_FALSE;
#endif
    OPTM_GFX_GP_E *pEnGpId = (OPTM_GFX_GP_E *)u32Param0;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param1);
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(*pEnGpId);

    if (HI_FALSE == g_stGfxGPDevice[*pEnGpId].bOpen)
    {
        return;
    }

#ifdef CHIP_TYPE_hi3798cv200/** bugfix hdmi cts **/
    g_stGfxGPDevice[*pEnGpId].enDispFmt = pstDispInfo->stDispInfo.eFmt;
#endif

    if ((g_enOptmGfxWorkMode == HIFB_GFX_MODE_NORMAL) && (HI_TRUE == pstDispInfo->stDispInfo.bIsMaster) && (OPTM_GFX_GP_0 == *pEnGpId))
    {
        g_enOptmGfxWorkMode = HIFB_GFX_MODE_HD_WBC;
        if (NULL != g_stGfxGPDevice[*pEnGpId].queue)
        {
            g_stGfxGPDevice[*pEnGpId].stOpenSlvWork.u32Data = HIFB_LAYER_SD_0;
            queue_work(g_stGfxGPDevice[*pEnGpId].queue, &g_stGfxGPDevice[*pEnGpId].stOpenSlvWork.work);
        }
    }

    if ((HI_DRV_DISP_C_PREPARE_TO_PEND == pstDispInfo->eEventType) || (HI_DRV_DISP_C_PREPARE_CLOSE == pstDispInfo->eEventType))
    {
        return HIFB_ADP_ReClose(*pEnGpId);
    }

    if ((HI_DRV_DISP_C_RESUME == pstDispInfo->eEventType) || (HI_DRV_DISP_C_OPEN == pstDispInfo->eEventType))
    {
        g_stGfxGPDevice[*pEnGpId].bResume = HI_TRUE;
        return HIFB_ADP_ReOpen(*pEnGpId);
    }

    if (HI_DRV_DISP_C_DISPLAY_SETTING_CHANGE == pstDispInfo->eEventType)
    {
        return HIFB_ADP_DispSetting(*pEnGpId,pstDispInfo);
    }

#ifdef CFG_HIFB_PROC_SUPPORT
    if (OPTM_GFX_GP_0 == *pEnGpId)
    {
       HIFB_HAL_GetVoCallBackCurScanLine(&CurScanline);
       HIFB_HAL_GetVoCallBackStartPointScanLine(&StartScanline);
       HIFB_HAL_GetVoCallBackUpPointScanLine(&UpScanline);

       HIFB_PROC_SetVoCallBackInOutScanLine(0,CurScanline,HI_TRUE);
       HIFB_PROC_SetStartAndUpScanLine(StartScanline,UpScanline);

       HIFB_PROC_CheckScanLineAbnormal(0,&bScanLineAbnormal);
    }
    if (HI_TRUE == bScanLineAbnormal)
    {
       //return;
    }
#endif

    if (HI_DRV_DISP_C_VT_INT == pstDispInfo->eEventType)
    {
         return HIFB_ADP_UpdataLayerInfo(u32Param0,u32Param1);
    }

    return;
}


static inline HI_VOID HIFB_ADP_ReOpen(OPTM_GFX_GP_E enGpId)
{
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(enGpId);

    if (HI_FALSE == g_stGfxGPDevice[enGpId].bDispInitial)
    {
        return;
    }

    if (HI_TRUE == g_stGfxGPDevice[enGpId].bGpClose)
    {
        g_stGfxGPDevice[enGpId].bGpClose = HI_FALSE;
        g_stGfxGPDevice[enGpId].bRecoveryInNextVT = HI_TRUE;
    }

    HIFB_WBC2_Reset(HI_FALSE);

    OPTM_SET_GPMask(enGpId, HI_FALSE);

    return;
}

static inline HI_VOID HIFB_ADP_ReClose(OPTM_GFX_GP_E enGpId)
{
     HIFB_CHECK_GPID_SUPPORT_UNRETURN(enGpId);

     if (HI_FALSE == g_stGfxGPDevice[enGpId].bDispInitial)
     {
         return;
     }

     g_stGfxGPDevice[enGpId].bGpClose = HI_TRUE;

     OPTM_GFX_GET_DECMP_Status(HIFB_LAYER_HD_0);

     OPTM_SET_GPMask(enGpId, HI_TRUE);

     return;
}

static inline HI_VOID HIFB_ADP_DispSetting(OPTM_GFX_GP_E enGpId, HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo)
{
     HI_BOOL bDispInfoChange = HI_FALSE;

     bDispInfoChange = OPTM_DispInfoProcess(enGpId, pstDispInfo);
     if (HI_FALSE == bDispInfoChange)
     {
         return;
     }

     OPTM_DispInfoUpdate(enGpId);

     if ((enGpId == OPTM_GFX_GP_1) || IS_MASTER_GP(enGpId))
     {
         HIFB_WBC2_Reset(HI_TRUE);
         g_stGfxGPDevice[OPTM_GFX_GP_1].unUpFlag.bits.IsNeedUpInRect = 1;
         g_stGfxWbc2.s32WbcCnt = 2;
     }

     return;
}


static inline HI_VOID HIFB_ADP_UpdataLayerInfo(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
#ifndef CONFIG_GFX_PQ
    OPTM_COLOR_SPACE_E       enGpCsc = OPTM_CS_BUTT;
#else
    HI_PQ_GFX_COLOR_SPACE_E  enGpCsc  = PQ_GFX_CS_BUTT;
#endif
    HI_BOOL bHDR = HI_FALSE;
    OPTM_GFX_GP_E *enGpId = (OPTM_GFX_GP_E *)u32Param0;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param1);
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(*enGpId);

    if ((HI_TRUE == g_stGfxGPDevice[*enGpId].bGpClose) && (HI_TRUE == g_stGfxGPDevice[*enGpId].bDispInitial))
    {
        g_stGfxGPDevice[*enGpId].bRecoveryInNextVT = HI_TRUE;
        g_stGfxGPDevice[*enGpId].bGpClose          = HI_FALSE;
        OPTM_SET_GPMask(*enGpId, HI_FALSE);
    }

    if (HI_TRUE == g_stGfxGPDevice[*enGpId].bRecoveryInNextVT)
    {
        g_stGfxGPDevice[*enGpId].bInterface = pstDispInfo->stDispInfo.bInterlace;

        HI_GFX_Memcpy(&g_stGfxGPDevice[*enGpId].stInRect, &pstDispInfo->stDispInfo.stVirtaulScreen, sizeof(HI_RECT_S));

        OPTM_GetScreenRectFromDispInfo(&pstDispInfo->stDispInfo.stVirtaulScreen,                   \
                                       (OPTM_GFX_OFFSET_S *)&pstDispInfo->stDispInfo.stOffsetInfo, \
                                       &pstDispInfo->stDispInfo.stFmtResolution,                   \
                                       &pstDispInfo->stDispInfo.stPixelFmtResolution,              \
                                       &g_stGfxGPDevice[*enGpId].stOutRect);

        OPTM_GPRecovery(*enGpId);

        g_stGfxGPDevice[*enGpId].bRecoveryInNextVT = HI_FALSE;
        g_stGfxGPDevice[*enGpId].bDispInitial      = HI_TRUE;

    }

#ifndef CONFIG_GFX_PQ
    enGpCsc = OPTM_AdaptCscTypeFromDisp(pstDispInfo->stDispInfo.eColorSpace);
#else
    enGpCsc = PQ_AdaptCscTypeFromDisp(pstDispInfo->stDispInfo.eColorSpace);
#endif

    g_stGfxGPDevice[*enGpId].enOutputCsc = enGpCsc;

    bHDR = (HI_DRV_DISP_PROCESS_MODE_HDR == pstDispInfo->stDispInfo.enDispProcessMode)? (HI_TRUE) : (HI_FALSE);
    g_stGfxGPDevice[*enGpId].bHdr = bHDR;

    if ((HI_FALSE == bHDR) || (OPTM_GFX_GP_1 == *enGpId))
    {
        OPTM_GPSetCsc(*enGpId, &g_stGfxGPDevice[*enGpId].stCscPara, g_stGfxGPDevice[*enGpId].bBGRState);
    }

    if (IS_SLAVER_GP(*enGpId))
    {
        HIFB_WBC_Process(*enGpId);
    }
    else
    {
        OPTM_Distribute_Callback(u32Param0, u32Param1);
    }

    return;
}


/***************************************************************************************
* func          : OPTM_GfxChn2DispChn
* description   : CNcomment: 获取display通道 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_DRV_DISPLAY_E OPTM_GfxChn2DispChn(OPTM_DISPCHANNEL_E enDispCh)
{
    if (OPTM_DISPCHANNEL_0 == enDispCh)
    {
        return HI_DRV_DISPLAY_0;
    }

    if (OPTM_DISPCHANNEL_1 == enDispCh)
    {
        return HI_DRV_DISPLAY_1;
    }

    return HI_DRV_DISPLAY_BUTT;
}
/***************************************************************************************
* func          : OPTM_SetCallbackToDisp
* description   : CNcomment: 向Display注册中断 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_SetCallbackToDisp(OPTM_GFX_GP_E enGPId, IntCallBack pCallBack, HI_DRV_DISP_CALLBACK_TYPE_E eType, HI_BOOL bFlag)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_DISPLAY_E            enDisp;
    HI_DRV_DISP_CALLBACK_S      stCallback;

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN(eType,HI_DRV_DISP_C_TYPE_BUTT,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pCallBack, HI_FAILURE);

    if (bFlag == g_stGfxGPIrq[enGPId].bRegistered[eType])
    {
        return HI_SUCCESS;
    }

    enDisp = OPTM_GfxChn2DispChn(g_stGfxGPDevice[enGPId].enDispCh);
    stCallback.hDst = (HI_VOID*)(&g_stGfxGPDevice[enGPId].enGpHalId);
    stCallback.pfDISP_Callback = (HI_VOID*)pCallBack;

    if (bFlag)
    {
        s32Ret = ps_DispExportFuncs->pfnDispRegCallback(enDisp,eType,&stCallback);
    }
    else
    {
        s32Ret = ps_DispExportFuncs->pfnDispUnRegCallback(enDisp,eType,&stCallback);
    }

    if (HI_SUCCESS == s32Ret)
    {
        g_stGfxGPIrq[enGPId].bRegistered[eType] = bFlag;
    }

    return s32Ret;
}
#endif


/***************************************************************************************
* func          : OPTM_GfxOpenLayer
* description   : CNcomment: 打开图层 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxOpenLayer(HIFB_LAYER_ID_E enLayerId)
{
#ifndef HI_BUILD_IN_BOOT
    HI_S32 s32Ret = HI_SUCCESS;
#endif

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    if (HI_TRUE != g_stGfxCap[enLayerId].bLayerSupported)
    {
        HIFB_ERROR("Gfx%d was not supported!\n",enLayerId);
        return HI_FAILURE;
    }

    if (HI_TRUE == g_stGfxDevice[enLayerId].bOpened)
    {
        HIFB_WARNING("info:Gfx%d was opened!\n",enLayerId);
        return HI_SUCCESS;
    }

    if ((HIFB_GFX_MODE_HD_WBC == g_enOptmGfxWorkMode) && (HIFB_LAYER_SD_0 == enLayerId))
    {
        HIFB_WARNING("GFX work at wbc mode, gfx%d is working!\n", enLayerId);
        return HI_FAILURE;
    }

#ifndef HI_BUILD_IN_BOOT
    if (HI_NULL == gs_pstPqFuncs)
    {
        if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(HI_ID_PQ, (HI_VOID**)&gs_pstPqFuncs))
        {
            HIFB_WARNING("Get PQ_EXPORT_FUNC_S failed\r\n");
        }
    }

    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs, HI_FAILURE);
#endif

    OPTM_GfxInitLayer(enLayerId);

#ifndef HI_BUILD_IN_BOOT
    s32Ret = OPTM_GPOpen(g_stGfxDevice[enLayerId].enGPId);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
#else
    (HI_VOID)OPTM_GPOpen(g_stGfxDevice[enLayerId].enGPId);
#endif

#ifndef HI_BUILD_IN_BOOT
    s32Ret = OPTM_SetCallbackToDisp(g_stGfxDevice[enLayerId].enGPId, (IntCallBack)DRV_HIFB_ADP_UpDataCallBack, HI_DRV_DISP_C_INTPOS_90_PERCENT, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HIFB_ERROR("Disp was not ready, open gfx%d failure!\n", enLayerId);
        return HI_FAILURE;
    }

    s32Ret = OPTM_SetCallbackToDisp(g_stGfxDevice[enLayerId].enGPId, (IntCallBack)DRV_HIFB_ADP_FrameEndCallBack, HI_DRV_DISP_C_INTPOS_100_PERCENT, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HIFB_ERROR("fail to register FrameEndCallBack\n");
        return HI_FAILURE;
    }
#endif

    if (g_stGfxCap[enLayerId].bHasCmapReg != HI_FALSE)
    {
        HI_CHAR name[32] = {'\0'};
        snprintf(name, sizeof(name), "HIFB_Fb%d_Clut", enLayerId);
        if (OPTM_Adapt_AllocAndMap(name, NULL, OPTM_CMAP_SIZE, 0, &g_stGfxDevice[enLayerId].stCluptTable) != HI_SUCCESS)
        {
            HIFB_ERROR("GFX Get clut buffer failed!\n");
            return HI_FAILURE;
        }
        OPTM_VDP_GFX_SetLutAddr(g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].stCluptTable.u32StartPhyAddr);
    }

    g_stGfxDevice[enLayerId].bOpened = HI_TRUE;

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_CheckGpState
* description   : CNcomment: 判断GP状态 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_CheckGpState(OPTM_GFX_GP_E enGPId)
{
    HI_U32 i = 0;
    HI_U32 u32LayerIdSta = 0;
    HI_U32 u32LayerIdEnd = 0;

    if (OPTM_GFX_GP_0 == enGPId)
    {
        u32LayerIdSta = HIFB_LAYER_HD_0;
        u32LayerIdEnd = HIFB_LAYER_HD_3;
    }
    else if (OPTM_GFX_GP_1 == enGPId)
    {
        u32LayerIdSta = HIFB_LAYER_SD_0;
        u32LayerIdEnd = HIFB_LAYER_SD_1;
    }
    else
    {
        return OPTM_DISABLE;
    }

    for (i = u32LayerIdSta; i <= u32LayerIdEnd; i++)
    {
        if (HI_TRUE == g_stGfxDevice[i].bOpened)
        {
            return OPTM_ENABLE;
        }
    }

    return OPTM_DISABLE;
}


/***************************************************************************************
* func           : OPTM_GfxCloseLayer
* description : CNcomment: 关闭打开的图层 CNend\n
* param[in]  : HI_VOID
* retval        : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxCloseLayer(HIFB_LAYER_ID_E enLayerId)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_stGfxDevice[enLayerId].enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    if (HI_FALSE == g_stGfxDevice[enLayerId].bOpened)
    {
        return HI_SUCCESS;
    }

#ifdef CONFIG_HIFB_GFX3_TO_GFX5
    if (OPTM_VDP_LAYER_GFX3 == g_stGfxDevice[enLayerId].enGfxHalId)
    {
        OPTM_VDP_OpenGFX3(HI_FALSE);
        OPTM_VDP_SetLayerConnect(OPTM_VDP_CONNECT_G3_DHD0);
    }
#endif

    OPTM_GfxSetEnable(enLayerId, HI_FALSE);
    OPTM_VDP_GFX_SetNoSecFlag(g_stGfxDevice[enLayerId].enGfxHalId, HI_TRUE);
    OPTM_VDP_GFX_SetRegUp(g_stGfxDevice[enLayerId].enGfxHalId);
    OPTM_GFX_ReleaseClutBuf(enLayerId);

    g_stGfxDevice[enLayerId].bExtractLine = HI_FALSE;
    g_stGfxDevice[enLayerId].bOpened      = HI_FALSE;

    if(!OPTM_CheckGpState(enGPId))
    {
        if (g_enOptmGfxWorkMode == HIFB_GFX_MODE_HD_WBC)
        {
            HIFB_WBC_DinitLayer(OPTM_SLAVER_LAYERID);
            OPTM_GPClose(OPTM_SLAVER_GPID);
        }
        OPTM_GPClose(enGPId);
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GfxSetEnable
* description   : CNcomment: 设置图层使能 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetEnable(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_stGfxDevice[enLayerId].enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    g_stGfxDevice[enLayerId].bEnable = bEnable;
    OPTM_CheckGPMask_BYGPID(enGPId);

    OPTM_VDP_GFX_SetLayerEnable(g_stGfxDevice[enLayerId].enGfxHalId, bEnable);
    OPTM_VDP_GFX_SetRegUp(g_stGfxDevice[enLayerId].enGfxHalId);

    if (IS_MASTER_GP(enGPId))
    {
        HIFB_WBC2_SetEnable(bEnable);
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func            : OPTM_GfxSetLayerAddr
* description    : CNcomment: 设置显示地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:        : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Addr)
{
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    HIFB_CHECK_EQUAL_RETURN(0, u32Addr, HI_FAILURE);

    g_stGfxDevice[enLayerId].NoCmpBufAddr = u32Addr;

    OPTM_CheckGPMask_BYLayerID(enLayerId);

    OPTM_VDP_GFX_SetLayerAddrEX(g_stGfxDevice[enLayerId].enGfxHalId, u32Addr);

    return HI_SUCCESS;
}

/***************************************************************************************
* func            : OPTM_GfxGetLayerAddr
* description    : CNcomment: 获取显示地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:        : NA
***************************************************************************************/
HI_S32 OPTM_GfxGetLayerAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 *pu32Addr)
{
#ifndef HI_BUILD_IN_BOOT
    OPTM_VDP_GFX_GetLayerAddr(enLayerId,pu32Addr);
#endif
    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_GfxSetLayerStride
* description   : CNcomment: 设置图层stride CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerStride(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Stride)
{
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    g_stGfxDevice[enLayerId].Stride = (HI_U16)u32Stride;

    OPTM_CheckGPMask_BYLayerID(enLayerId);

    if (g_stGfxGPDevice[g_stGfxDevice[enLayerId].enGPId].bNeedExtractLine && (OPTM_CURSOR_LAYERID != enLayerId))
    {
        OPTM_VDP_GFX_SetLayerStride(g_stGfxDevice[enLayerId].enGfxHalId, u32Stride*2);
    }
    else
    {
        OPTM_VDP_GFX_SetLayerStride(g_stGfxDevice[enLayerId].enGfxHalId, u32Stride);
    }

    return HI_SUCCESS;
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : OPTM_HalFmtTransferToPixerFmt
* description   : CNcomment: 由VDP像素格式转换成hifb像素格式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HIFB_COLOR_FMT_E OPTM_HalFmtTransferToPixerFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
    HIFB_COLOR_FMT_E ePixFmt = HIFB_FMT_BUTT;

    if (enDataFmt >= VDP_GFX_IFMT_BUTT)
    {
        return HIFB_FMT_BUTT;
    }

    ePixFmt = OPTM_ClutHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    ePixFmt = OPTM_XYCbCrHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    ePixFmt = OPTM_RGBHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    ePixFmt = OPTM_XRGBHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    return HIFB_FMT_BUTT;
}

static inline HIFB_COLOR_FMT_E OPTM_ClutHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch (enDataFmt)
     {
         case VDP_GFX_IFMT_CLUT_1BPP:
            return HIFB_FMT_1BPP;
         case VDP_GFX_IFMT_CLUT_2BPP:
            return HIFB_FMT_2BPP;
         case VDP_GFX_IFMT_CLUT_4BPP:
            return HIFB_FMT_4BPP;
         case VDP_GFX_IFMT_CLUT_8BPP:
            return HIFB_FMT_8BPP;
         case VDP_GFX_IFMT_ACLUT_44:
            return HIFB_FMT_ACLUT44;
         case VDP_GFX_IFMT_ACLUT_88:
            return HIFB_FMT_ACLUT88;
         default:
            return HIFB_FMT_BUTT;
     }
}

static inline HIFB_COLOR_FMT_E OPTM_RGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch (enDataFmt)
     {
         case VDP_GFX_IFMT_RGB_565:
            return HIFB_FMT_RGB565;
         case VDP_GFX_IFMT_RGB_888:
            return HIFB_FMT_RGB888;
         default:
            return HIFB_FMT_BUTT;
     }
}

static inline HIFB_COLOR_FMT_E OPTM_XRGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch(enDataFmt)
     {
        case VDP_GFX_IFMT_RGB_444:
           return HIFB_FMT_KRGB444;
        case VDP_GFX_IFMT_RGB_555:
           return HIFB_FMT_KRGB555;
        case VDP_GFX_IFMT_ARGB_8565:
           return HIFB_FMT_ARGB8565;
        case VDP_GFX_IFMT_KRGB_888:
           return HIFB_FMT_KRGB888;
        case VDP_GFX_IFMT_ARGB_8888:
            return HIFB_FMT_ARGB8888;
        case VDP_GFX_IFMT_ARGB_4444:
            return HIFB_FMT_ARGB4444;
        case VDP_GFX_IFMT_ARGB_1555:
            return HIFB_FMT_ARGB1555;
        case VDP_GFX_IFMT_RGBA_4444:
            return HIFB_FMT_RGBA4444;
        case VDP_GFX_IFMT_RGBA_5551:
            return HIFB_FMT_RGBA5551;
        case VDP_GFX_IFMT_RGBA_5658:
            return HIFB_FMT_RGBA5658;
        case VDP_GFX_IFMT_RGBA_8888:
            return HIFB_FMT_RGBA8888;
        default:
            return HIFB_FMT_BUTT;
     }
}

static inline HIFB_COLOR_FMT_E OPTM_XYCbCrHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch(enDataFmt)
     {
         case VDP_GFX_IFMT_PKG_UYVY:
            return HIFB_FMT_PUYVY;
         case VDP_GFX_IFMT_PKG_YUYV:
            return HIFB_FMT_PYUYV;
         case VDP_GFX_IFMT_PKG_YVYU:
            return HIFB_FMT_PYVYU;
         case VDP_GFX_IFMT_YCBCR_888:
            return HIFB_FMT_YUV888;
         case VDP_GFX_IFMT_AYCBCR_8888:
            return HIFB_FMT_AYUV8888;
         case VDP_GFX_IFMT_YCBCRA_8888:
            return HIFB_FMT_YUVA8888;
         default:
            return HIFB_FMT_BUTT;
     }
}
#endif


/***************************************************************************************
* func          : OPTM_PixerFmtTransferToHalFmt
* description   : CNcomment: 由hifb像素格式转换成图形层像素格式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
OPTM_VDP_GFX_IFMT_E OPTM_PixerFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
    OPTM_VDP_GFX_IFMT_E eHalFmt = VDP_GFX_IFMT_BUTT;

    if (enDataFmt >= HIFB_FMT_BUTT)
    {
        return VDP_GFX_IFMT_BUTT;
    }

    eHalFmt = OPTM_ClutPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    eHalFmt = OPTM_XRGBPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    eHalFmt = OPTM_RGBPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    eHalFmt = OPTM_XYCbCrPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    return VDP_GFX_IFMT_BUTT;
}

static inline OPTM_VDP_GFX_IFMT_E OPTM_ClutPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch(enDataFmt)
     {
        case HIFB_FMT_1BPP:
            return VDP_GFX_IFMT_CLUT_1BPP;
        case HIFB_FMT_2BPP:
            return VDP_GFX_IFMT_CLUT_2BPP;
        case HIFB_FMT_4BPP:
            return VDP_GFX_IFMT_CLUT_4BPP;
        case HIFB_FMT_8BPP:
            return VDP_GFX_IFMT_CLUT_8BPP;
        case HIFB_FMT_ACLUT44:
            return VDP_GFX_IFMT_ACLUT_44;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}


static inline OPTM_VDP_GFX_IFMT_E OPTM_RGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch(enDataFmt)
     {
        case HIFB_FMT_KRGB444:
           return VDP_GFX_IFMT_RGB_444;
        case HIFB_FMT_KRGB555:
           return VDP_GFX_IFMT_RGB_555;
        case HIFB_FMT_RGB565:
            return VDP_GFX_IFMT_RGB_565;
        case HIFB_FMT_RGB888:
           return VDP_GFX_IFMT_RGB_888;
        case HIFB_FMT_YUV888:
           return VDP_GFX_IFMT_YCBCR_888;
        case HIFB_FMT_KRGB888:
           return VDP_GFX_IFMT_KRGB_888;
        case HIFB_FMT_BGR565:
            return VDP_GFX_IFMT_RGB_565;
        case HIFB_FMT_BGR888:
            return VDP_GFX_IFMT_RGB_888;
        case HIFB_FMT_KBGR444:
            return VDP_GFX_IFMT_RGB_444;
        case HIFB_FMT_KBGR555:
            return VDP_GFX_IFMT_RGB_555;
        case HIFB_FMT_KBGR888:
            return VDP_GFX_IFMT_KRGB_888;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}

static inline OPTM_VDP_GFX_IFMT_E OPTM_XRGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch(enDataFmt)
     {
        case HIFB_FMT_ARGB8888:
            return VDP_GFX_IFMT_ARGB_8888;
        case HIFB_FMT_ARGB4444:
            return VDP_GFX_IFMT_ARGB_4444;
        case HIFB_FMT_ARGB1555:
            return VDP_GFX_IFMT_ARGB_1555;
        case HIFB_FMT_RGBA4444:
            return VDP_GFX_IFMT_RGBA_4444;
        case HIFB_FMT_RGBA5551:
            return VDP_GFX_IFMT_RGBA_5551;
        case HIFB_FMT_RGBA5658:
            return VDP_GFX_IFMT_RGBA_5658;
        case HIFB_FMT_RGBA8888:
            return VDP_GFX_IFMT_RGBA_8888;
        case HIFB_FMT_ABGR4444:
            return VDP_GFX_IFMT_ARGB_4444;
        case HIFB_FMT_ABGR1555:
            return VDP_GFX_IFMT_ARGB_1555;
        case HIFB_FMT_ABGR8888:
            return VDP_GFX_IFMT_ABGR_8888;
        case HIFB_FMT_ABGR8565:
            return VDP_GFX_IFMT_ARGB_8565;
        case HIFB_FMT_ARGB8565:
            return VDP_GFX_IFMT_ARGB_8565;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}

static inline OPTM_VDP_GFX_IFMT_E OPTM_XYCbCrPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch(enDataFmt)
     {
        case HIFB_FMT_PUYVY:
            return VDP_GFX_IFMT_PKG_UYVY;
        case HIFB_FMT_PYUYV:
            return VDP_GFX_IFMT_PKG_YUYV;
        case HIFB_FMT_PYVYU:
            return VDP_GFX_IFMT_PKG_YVYU;
        case HIFB_FMT_ACLUT88:
           return VDP_GFX_IFMT_ACLUT_88;
        case HIFB_FMT_YUVA8888:
            return VDP_GFX_IFMT_YCBCRA_8888;
        case HIFB_FMT_AYUV8888:
            return VDP_GFX_IFMT_AYCBCR_8888;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}


/***************************************************************************************
* func          : OPTM_GfxSetLayerDataFmt
* description   : CNcomment: 设置图层格式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerDataFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt)
{
    HI_S32 Ret = HI_SUCCESS;
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_stGfxDevice[enLayerId].enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    HIFB_CHECK_ARRAY_OVER_RETURN(enDataFmt, HIFB_FMT_BUTT, HI_FAILURE);
    if (HI_FALSE == g_stGfxCap[enLayerId].bColFmt[enDataFmt])
    {
        HIFB_ERROR("unSupport color format.\n");
        return HI_FAILURE;
    }

    g_stGfxDevice[enLayerId].enDataFmt = enDataFmt;

    OPTM_CheckGPMask_BYGPID(enGPId);

    if (   (HIFB_FMT_ABGR8888 != enDataFmt)
        && ((enDataFmt >= HIFB_FMT_BGR565) && (HIFB_FMT_KBGR888 >= enDataFmt))
        && (g_stGfxDevice[enLayerId].CscState == OPTM_CSC_SET_PARA_RGB))
    {
        Ret = HIFB_ADP_SetLayerDataBigEndianFmt(enLayerId,enDataFmt);
    }
    else if (  ((HIFB_FMT_ABGR8888 == enDataFmt) || (HIFB_FMT_BGR565 > enDataFmt || enDataFmt > HIFB_FMT_KBGR888))
            && (g_stGfxDevice[enLayerId].CscState == OPTM_CSC_SET_PARA_BGR))
    {
        Ret = HIFB_ADP_SetLayerDataLittleEndianFmt(enLayerId,enDataFmt);
    }

    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    OPTM_VDP_GFX_SetInDataFmt(g_stGfxDevice[enLayerId].enGfxHalId,OPTM_PixerFmtTransferToHalFmt(enDataFmt));

    return HI_SUCCESS;
}


static inline HI_S32 HIFB_ADP_SetLayerDataBigEndianFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt)
{
     HI_S32 s32Cnt = 0;
     HI_U32 u32LayerCount = 0;
     OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

     HI_UNUSED(enDataFmt);
     HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
     enGPId = g_stGfxDevice[enLayerId].enGPId;
     HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

     u32LayerCount = (HIFB_LAYER_HD_3 >= enLayerId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;

     for (s32Cnt = 0; s32Cnt < u32LayerCount; s32Cnt++)
     {
         if ((s32Cnt != enLayerId) && (g_stGfxDevice[s32Cnt].bEnable) && (g_stGfxDevice[s32Cnt].CscState != OPTM_CSC_SET_PARA_BGR))
         {
             HIFB_ERROR("fail to set color format.\n");
             return HI_FAILURE;
         }
     }

     g_stGfxDevice[enLayerId].CscState = OPTM_CSC_SET_PARA_BGR;
     g_stGfxGPDevice[enGPId].bBGRState = HI_TRUE;

     OPTM_GPSetCsc(enGPId,  &g_stGfxGPDevice[enGPId].stCscPara, HI_TRUE);

     if (IS_MASTER_GP(enGPId))
     {
         OPTM_GPSetCsc(OPTM_SLAVER_GPID,  &g_stGfxGPDevice[OPTM_SLAVER_GPID].stCscPara, HI_TRUE);
         g_stGfxGPDevice[OPTM_SLAVER_GPID].bBGRState = HI_TRUE;
     }

     return HI_SUCCESS;
}

static inline HI_S32 HIFB_ADP_SetLayerDataLittleEndianFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt)
{
     HI_S32 s32Cnt = 0;
     HI_U32 u32LayerCount = 0;
     OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

     HI_UNUSED(enDataFmt);
     HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
     enGPId = g_stGfxDevice[enLayerId].enGPId;
     HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

     u32LayerCount = (HIFB_LAYER_HD_3 >= enLayerId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;

     for (s32Cnt = 0; s32Cnt < u32LayerCount; s32Cnt++)
     {
         if ( (s32Cnt != enLayerId) && (g_stGfxDevice[s32Cnt].bEnable) && (g_stGfxDevice[s32Cnt].CscState != OPTM_CSC_SET_PARA_RGB))
         {
             HIFB_ERROR("fail to set color format.\n");
             return HI_FAILURE;
         }
     }

     g_stGfxDevice[enLayerId].CscState = OPTM_CSC_SET_PARA_RGB;
     g_stGfxGPDevice[enGPId].bBGRState = HI_FALSE;

     OPTM_GPSetCsc(enGPId,  &g_stGfxGPDevice[enGPId].stCscPara, HI_FALSE);

     if(IS_MASTER_GP(enGPId))
     {
         OPTM_GPSetCsc(OPTM_SLAVER_GPID,  &g_stGfxGPDevice[OPTM_SLAVER_GPID].stCscPara, HI_FALSE);
         g_stGfxGPDevice[OPTM_SLAVER_GPID].bBGRState = HI_FALSE;
     }

     return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_GFX_SetClutColorReg
* description   : CNcomment: 设置调色板颜色寄存器 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_SetClutColorReg(HIFB_LAYER_ID_E enLayerId, HI_U32 u32OffSet, HI_U32 u32Color, HI_S32 UpFlag)
{
    HI_U32 *pCTab = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    pCTab = (HI_U32 *)(g_stGfxDevice[enLayerId].stCluptTable.pu8StartVirAddr);
    HIFB_CHECK_NULLPOINTER_RETURN(pCTab, HI_FAILURE);

    pCTab[u32OffSet] = u32Color;
    if (UpFlag != 0)
    {
        OPTM_VDP_GFX_SetParaUpd(g_stGfxDevice[enLayerId].enGfxHalId,VDP_DISP_COEFMODE_LUT);
    }

    return HI_SUCCESS;
}


#ifdef OPTM_HIFB_WVM_ENABLE
/***************************************************************************************
* func          : OPTM_GfxWVBCallBack
* description   : CNcomment: 等中断完成 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID OPTM_GfxWVBCallBack(HI_U32 enLayerId)
{
    HIFB_CHECK_ARRAY_OVER_UNRETURN(enLayerId, OPTM_MAX_LOGIC_HIFB_LAYER);

    if (HI_FALSE == g_stGfxDevice[enLayerId].bOpened)
    {
        return;
    }

    g_stGfxDevice[enLayerId].vblflag = 1;
    wake_up_interruptible(&(g_stGfxDevice[enLayerId].vblEvent));

    return;
}

/***************************************************************************************
* func          : OPTM_GfxWaitVBlank
* description   : CNcomment: 等中断 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxWaitVBlank(HIFB_LAYER_ID_E enLayerId)
{
    HI_U32 u32TimeOutMs = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    HIFB_CHECK_ARRAY_OVER_RETURN(enLayerId, OPTM_MAX_LOGIC_HIFB_LAYER,HI_FAILURE);
    HIFB_CHECK_GFX_OPEN(enLayerId);

    u32TimeOutMs = (200 * HZ)/1000;

    g_stGfxDevice[enLayerId].vblflag = 0;
    s32Ret = wait_event_interruptible_timeout(g_stGfxDevice[enLayerId].vblEvent, g_stGfxDevice[enLayerId].vblflag, u32TimeOutMs);
    if(s32Ret <= 0)
    {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

#else

HI_S32 OPTM_GfxWaitVBlank(HIFB_LAYER_ID_E enLayerId)
{
    HIFB_ERROR("GFX ERROR! NOT enable wait v blank\n");
    HI_UNUSED(enLayerId);
    return HI_FAILURE;
}

#endif

/***************************************************************************************
* func          : OPTM_GfxSetLayerDeFlicker
* description   : CNcomment: 设置图层抗闪，不支持 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerDeFlicker(HIFB_LAYER_ID_E enLayerId, HIFB_DEFLICKER_S *pstDeFlicker)
{
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GfxSetLayerAlpha
* description   : CNcomment: 设置图层alpha CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerAlpha(HIFB_LAYER_ID_E enLayerId, HIFB_ALPHA_S *pstAlpha)
{
    HI_GFX_Memcpy(&g_stGfxDevice[enLayerId].stAlpha, pstAlpha, sizeof(HIFB_ALPHA_S));

    /** 是否已经开机过渡完 **/
    OPTM_CheckGPMask_BYLayerID(enLayerId);

    OPTM_VDP_GFX_SetPalpha(g_stGfxDevice[enLayerId].enGfxHalId,pstAlpha->bAlphaEnable,HI_TRUE,pstAlpha->u8Alpha0,pstAlpha->u8Alpha1);
    OPTM_VDP_GFX_SetLayerGalpha(g_stGfxDevice[enLayerId].enGfxHalId, pstAlpha->u8GlobalAlpha);

    return HI_SUCCESS;

}

/***************************************************************************************
* func          : OPTM_GfxGetLayerRect
* description   : CNcomment: 获取图层输入分辨率 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxGetLayerRect(HIFB_LAYER_ID_E enLayerId, HIFB_RECT *pstRect)
{
    HI_GFX_Memcpy(pstRect, &g_stGfxDevice[enLayerId].stInRect, sizeof(HIFB_RECT));
    return HI_SUCCESS;
}

/***************************************************************************************
* func            : OPTM_GfxSetLayerRect
* description    : CNcomment: 设置图层输入矩形 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:        : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerRect(HIFB_LAYER_ID_E enLayerId, const HIFB_RECT *pstRect)
{
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;
    OPTM_VDP_DISP_RECT_S stGfxRect;

    if (enLayerId >= OPTM_MAX_LOGIC_HIFB_LAYER)
    {
        return HI_FAILURE;
    }

    enGpId = g_stGfxDevice[enLayerId].enGPId;
    if (enGpId >= OPTM_GFX_GP_BUTT)
    {
        return HI_FAILURE;
    }

    g_stGfxDevice[enLayerId].stInRect.x = pstRect->x;
    g_stGfxDevice[enLayerId].stInRect.y = pstRect->y;
    g_stGfxDevice[enLayerId].stInRect.w = pstRect->w;
    g_stGfxDevice[enLayerId].stInRect.h = pstRect->h;


    OPTM_CheckGPMask_BYLayerID(enLayerId);

    HI_GFX_Memset(&stGfxRect, 0, sizeof(OPTM_VDP_DISP_RECT_S));

    stGfxRect.u32VX  = g_stGfxDevice[enLayerId].stInRect.x;
    stGfxRect.u32DXS = g_stGfxDevice[enLayerId].stInRect.x;
    stGfxRect.u32VY  = g_stGfxDevice[enLayerId].stInRect.y;
    stGfxRect.u32DYS = g_stGfxDevice[enLayerId].stInRect.y;
    stGfxRect.u32IWth= g_stGfxDevice[enLayerId].stInRect.w;
    stGfxRect.u32IHgt= g_stGfxDevice[enLayerId].stInRect.h;

    if (g_stGfxDevice[enLayerId].stInRect.x > g_stGfxGPDevice[enGpId].stInRect.s32Width - g_stGfxCap[enLayerId].u32MinWidth)
    {
        g_stGfxDevice[enLayerId].stInRect.x = g_stGfxGPDevice[enGpId].stInRect.s32Width - g_stGfxCap[enLayerId].u32MinWidth;
    }

    if (g_stGfxDevice[enLayerId].stInRect.y > g_stGfxGPDevice[enGpId].stInRect.s32Height - g_stGfxCap[enLayerId].u32MinHeight)
    {
        g_stGfxDevice[enLayerId].stInRect.y = g_stGfxGPDevice[enGpId].stInRect.s32Height - g_stGfxCap[enLayerId].u32MinHeight;
    }

    if (!IS_SLAVER_GP(enGpId))
    {
        if ((g_stGfxDevice[enLayerId].stInRect.x + g_stGfxDevice[enLayerId].stInRect.w) > g_stGfxGPDevice[enGpId].stInRect.s32Width)
        {
            stGfxRect.u32IWth = g_stGfxGPDevice[enGpId].stInRect.s32Width - g_stGfxDevice[enLayerId].stInRect.x;
        }

        if ((g_stGfxDevice[enLayerId].stInRect.y + g_stGfxDevice[enLayerId].stInRect.h) > g_stGfxGPDevice[enGpId].stInRect.s32Height)
        {
            stGfxRect.u32IHgt = g_stGfxGPDevice[enGpId].stInRect.s32Height - g_stGfxDevice[enLayerId].stInRect.y;
        }
    }

    if (g_stGfxGPDevice[enGpId].bNeedExtractLine)
    {/** 是否抽行处理 **/
        stGfxRect.u32IHgt /= 2;
        stGfxRect.u32VY   /= 2;
        stGfxRect.u32DYS  /= 2;
        g_stGfxDevice[enLayerId].bExtractLine = HI_TRUE;
        OPTM_VDP_GFX_SetLayerStride(g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].Stride * 2);
    }
    else if (HI_TRUE == g_stGfxDevice[enLayerId].bExtractLine)
    {
        OPTM_GfxSetLayerStride(enLayerId, g_stGfxDevice[enLayerId].Stride);
        g_stGfxDevice[enLayerId].bExtractLine = HI_FALSE;
    }


    stGfxRect.u32OWth = stGfxRect.u32IWth;
    stGfxRect.u32OHgt = stGfxRect.u32IHgt;
    stGfxRect.u32DXL  = g_stGfxDevice[enLayerId].stInRect.x + stGfxRect.u32OWth;
    stGfxRect.u32DYL  = g_stGfxDevice[enLayerId].stInRect.y + stGfxRect.u32OHgt;

    /*************************************/
    if ( (g_enOptmGfxWorkMode == HIFB_GFX_MODE_NORMAL) && (enGpId == OPTM_GFX_GP_1))
    {
        stGfxRect.u32DXS = 0;
        stGfxRect.u32DYS = 0;
        stGfxRect.u32DXL = g_stGfxGPDevice[enGpId].stInRect.s32Width;
        stGfxRect.u32DYL = g_stGfxGPDevice[enGpId].stInRect.s32Height;

        if (g_stGfxGPDevice[enGpId].bNeedExtractLine)
        {
            stGfxRect.u32DYL /= 2;
        }
    }
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if ((HIFB_STEREO_SIDEBYSIDE_HALF == g_stGfxDevice[enLayerId].enTriDimMode) || (HIFB_STEREO_TOPANDBOTTOM == g_stGfxDevice[enLayerId].enTriDimMode))
    {
        stGfxRect.u32DXS = 0;
        stGfxRect.u32DYS = 0;
        stGfxRect.u32DXL = g_stGfxGPDevice[enGpId].stInRect.s32Width;
        stGfxRect.u32DYL = g_stGfxGPDevice[enGpId].stInRect.s32Height;
    }

    if (HIFB_STEREO_SIDEBYSIDE_HALF == g_stGfxDevice[enLayerId].enTriDimMode)
    {
        stGfxRect.u32IWth = stGfxRect.u32IWth/2;
        stGfxRect.u32IWth &= 0xfffffffe;
        stGfxRect.u32OWth = (stGfxRect.u32IWth)*2;
    }
    else if (HIFB_STEREO_TOPANDBOTTOM == g_stGfxDevice[enLayerId].enTriDimMode)
    {
        stGfxRect.u32IHgt = stGfxRect.u32IHgt/2;
        stGfxRect.u32IHgt &= 0xfffffffe;
        stGfxRect.u32OHgt = (stGfxRect.u32IHgt)*2;
    }
#endif

    if(OPTM_CURSOR_LAYERID != enLayerId){
        /** cursor support odd size **/
        stGfxRect.u32VX   &= 0xfffffffe;
        stGfxRect.u32VY   &= 0xfffffffe;
        stGfxRect.u32DXS  &= 0xfffffffe;
        stGfxRect.u32DYS  &= 0xfffffffe;
        stGfxRect.u32DXL  &= 0xfffffffe;
        stGfxRect.u32DYL  &= 0xfffffffe;
        stGfxRect.u32IWth &= 0xfffffffe;
        stGfxRect.u32IHgt &= 0xfffffffe;
        stGfxRect.u32OWth &= 0xfffffffe;
        stGfxRect.u32OHgt &= 0xfffffffe;
    }

    OPTM_VDP_GFX_SetLayerReso(g_stGfxDevice[enLayerId].enGfxHalId, stGfxRect);

    return HI_SUCCESS;

}


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func            : OPTM_GfxSetGpInPutSize
* description    : CNcomment: 设置GP输入大小 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:        : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetGpInPutSize(OPTM_GFX_GP_E enGpId, HI_U32 u32Width, HI_U32 u32Height)
{
    g_stGfxGPDevice[enGpId].stInRect.s32Width  = u32Width;
    g_stGfxGPDevice[enGpId].stInRect.s32Height = u32Height;
    return HI_SUCCESS;
}

/***************************************************************************************
* func            : OPTM_GfxGetDispFMTSize
* description    : CNcomment: 获取disp大小 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:        : NA
***************************************************************************************/
HI_S32 OPTM_GfxGetDispFMTSize(OPTM_GFX_GP_E enGpId, HIFB_RECT *pstOutRect)
{
    pstOutRect->x = g_stGfxGPDevice[enGpId].stOutRect.s32X;
    pstOutRect->y = g_stGfxGPDevice[enGpId].stOutRect.s32Y;
    pstOutRect->w = g_stGfxGPDevice[enGpId].stOutRect.s32Width;
    pstOutRect->h = g_stGfxGPDevice[enGpId].stOutRect.s32Height;

    if(pstOutRect->w == 0 || pstOutRect->h == 0){
        pstOutRect->x = 0;
        pstOutRect->y = 0;
        pstOutRect->w = 1280;
        pstOutRect->h = 720;
    }

    if(pstOutRect->w == 1440 && (pstOutRect->h == 576 || pstOutRect->h == 480)){
        pstOutRect->w /= 2;
    }

    return HI_SUCCESS;
}
#endif


/***************************************************************************************
* func          : OPTM_GfxSetDispFMTSize
* description   : CNcomment: 设置display像素格式和大小 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetDispFMTSize(OPTM_GFX_GP_E enGpId, const HI_RECT_S *pstOutRect)
{
#ifndef CONFIG_HIFB_EXTRACE_DISABLE
    HI_U32    u32Ratio    = 0;
#endif
    HIFB_RECT stInputRect = {0};

    if(pstOutRect->s32X < 0 || pstOutRect->s32Y < 0){
        return HI_FAILURE;
    }

    if(pstOutRect->s32Width <= 0 || pstOutRect->s32Height <= 0){
        return HI_FAILURE;
    }

    g_stGfxGPDevice[enGpId].stOutRect.s32X      = pstOutRect->s32X;
    g_stGfxGPDevice[enGpId].stOutRect.s32Y      = pstOutRect->s32Y;
    g_stGfxGPDevice[enGpId].stOutRect.s32Width  = pstOutRect->s32Width;
    g_stGfxGPDevice[enGpId].stOutRect.s32Height = pstOutRect->s32Height;

    OPTM_CheckGPMask_BYGPID(enGpId);

    stInputRect.x = g_stGfxGPDevice[enGpId].stInRect.s32X;
    stInputRect.y = g_stGfxGPDevice[enGpId].stInRect.s32Y;
    stInputRect.w = g_stGfxGPDevice[enGpId].stInRect.s32Width;
    stInputRect.h = g_stGfxGPDevice[enGpId].stInRect.s32Height;

#ifndef CONFIG_HIFB_EXTRACE_DISABLE
    /*judge wether need to extract line for layer or not*/
    u32Ratio =  g_stGfxGPDevice[enGpId].stInRect.s32Height*2;
    u32Ratio /= g_stGfxGPDevice[enGpId].stOutRect.s32Height;

    if(g_stGfxGPDevice[enGpId].bInterface)
    {
        //u32Ratio *= 2;
    }
    /**
     ** 是否需要抽行处理只和性能有关
     ** 比如3840 * 2560(IN) 1280 * 720(OUT) 2560 / 720 > 3
     **/
    if(u32Ratio >= OPTM_EXTRACTLINE_RATIO && !IS_SLAVER_GP(enGpId)){
        g_stGfxGPDevice[enGpId].bNeedExtractLine = HI_TRUE;
    }else{
        g_stGfxGPDevice[enGpId].bNeedExtractLine = HI_FALSE;
    }
#endif

    if(stInputRect.w && stInputRect.h)
    {
        OPTM_GfxSetGpRect(enGpId, &stInputRect);
    }

    return HI_SUCCESS;

}

/***************************************************************************************
* func             : OPTM_GfxSetGpRect
* description   : CNcomment: 设置GP RECT CNend\n
*                 (1)回写更新需要设置GP寄存器
                  (2)显示制式发生变化的时候
                  (3)输入分辨率发生变化的时候
                  (4)待机打开图层需要重新配置GP
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID OPTM_GfxGetPqGpFromDispChannel(const OPTM_DISPCHANNEL_E enChannel, HI_PQ_GFX_LAYER_E *pPqGp)
{
    if (OPTM_DISPCHANNEL_1 == enChannel)
    {
       *pPqGp = PQ_GFX_GP0;
    }
    else if (OPTM_DISPCHANNEL_0 == enChannel)
    {
       *pPqGp = PQ_GFX_GP1;
    }
    else
    {
        *pPqGp = PQ_GFX_LAYER_BUTT;
    }

    return;
}

HI_S32 OPTM_GfxSetGpRect(OPTM_GFX_GP_E enGpId, const HIFB_RECT * pstInputRect)
{
    OPTM_VDP_DISP_RECT_S stGfxRect    = {0};
    HI_PQ_GFX_ZME_PARA_S stGfxZmePara = {0};
    HI_RECT_S stOutRect               = {0};
    HI_PQ_GFX_LAYER_E enPqGfxGp = PQ_GFX_LAYER_BUTT;

#ifdef CHIP_TYPE_hi3798cv200/** hdmi cts bug, revise gp0 out width and xoffset and zme out width **/
    HI_DRV_DISP_FMT_E  enDispFmt  = HI_DRV_DISP_FMT_1080P_50;
    #ifdef HI_BUILD_IN_BOOT
        HI_DISP_DISPLAY_INFO_S pstInfo;
        HI_GFX_Memset(&pstInfo,0,sizeof(HI_DISP_DISPLAY_INFO_S));
        if(enGpId == OPTM_GFX_GP_0){
            HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_1, &pstInfo);
        }else{
            HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &pstInfo);
        }
        g_stGfxGPDevice[enGpId].enDispFmt = pstInfo.eFmt;
    #endif
    enDispFmt = g_stGfxGPDevice[enGpId].enDispFmt;
#endif


    g_stGfxGPDevice[enGpId].stInRect.s32Width  = pstInputRect->w;
    g_stGfxGPDevice[enGpId].stInRect.s32Height = pstInputRect->h;

    stOutRect.s32X      = g_stGfxGPDevice[enGpId].stOutRect.s32X;
    stOutRect.s32Y      = g_stGfxGPDevice[enGpId].stOutRect.s32Y;
    stOutRect.s32Width  = g_stGfxGPDevice[enGpId].stOutRect.s32Width;
    stOutRect.s32Height = g_stGfxGPDevice[enGpId].stOutRect.s32Height;

    OPTM_CheckGPMask_BYGPID(enGpId);

#ifdef CHIP_TYPE_hi3798cv200
    if ( (OPTM_GFX_GP_0 == enGpId) && (HI_DRV_DISP_FMT_1440x576i_50 == enDispFmt || HI_DRV_DISP_FMT_1440x480i_60 == enDispFmt))
    {
        stOutRect.s32X      = g_stGfxGPDevice[enGpId].stOutRect.s32X * 2;
        stOutRect.s32Width  = g_stGfxGPDevice[enGpId].stOutRect.s32Width * 2;
        stOutRect.s32Y      = g_stGfxGPDevice[enGpId].stOutRect.s32Y;
        stOutRect.s32Height = g_stGfxGPDevice[enGpId].stOutRect.s32Height;
    }
#endif

    stGfxRect.u32IWth = g_stGfxGPDevice[enGpId].stInRect.s32Width   & 0xfffffffe;
    stGfxRect.u32IHgt = g_stGfxGPDevice[enGpId].stInRect.s32Height  & 0xfffffffe;
    stGfxRect.u32OWth = stOutRect.s32Width  & 0xfffffffe;
    stGfxRect.u32OHgt = stOutRect.s32Height & 0xfffffffe;

    stGfxRect.u32DXS  = stOutRect.s32X & 0xfffffffe;
    stGfxRect.u32DYS  = stOutRect.s32Y & 0xfffffffe;
    stGfxRect.u32DXL  = stGfxRect.u32OWth + stGfxRect.u32DXS;
    stGfxRect.u32DYL  = stGfxRect.u32OHgt + stGfxRect.u32DYS;
    stGfxRect.u32VX   = stGfxRect.u32DXS;
    stGfxRect.u32VY   = stGfxRect.u32DYS;
    stGfxRect.u32VXL  = stGfxRect.u32OWth + stGfxRect.u32VX;
    stGfxRect.u32VYL  = stGfxRect.u32OHgt + stGfxRect.u32VY;

    if (g_stGfxGPDevice[enGpId].bNeedExtractLine == HI_TRUE)
    {
        stGfxRect.u32IHgt /= 2;
    }

    if ( (0 == stGfxRect.u32IWth) || (0 == stGfxRect.u32IHgt) || (0 == stGfxRect.u32OWth) || (0 == stGfxRect.u32OHgt))
    {
        return HI_SUCCESS;
    }

    OPTM_VDP_GP_SetLayerReso(enGpId, stGfxRect);

    if (IS_SLAVER_GP(enGpId))
    {
        stGfxRect.u32IWth  = g_stGfxWbc2.stInRect.w & 0xfffffffe;
        stGfxRect.u32IHgt  = g_stGfxWbc2.stInRect.h & 0xfffffffe;
        if ((0 == stGfxRect.u32IWth) || (0 == stGfxRect.u32IHgt))
        {
            return HI_SUCCESS;
        }

        if (HIFB_STEREO_SIDEBYSIDE_HALF    == g_stGfxGPDevice[OPTM_SLAVER_GPID].enTriDimMode)
        {
            stGfxRect.u32IWth /= 2;
        }
        else if (HIFB_STEREO_TOPANDBOTTOM == g_stGfxGPDevice[OPTM_SLAVER_GPID].enTriDimMode)
        {
            stGfxRect.u32IHgt /= 2;
        }

        if ( HI_TRUE == g_stGfxGPDevice[OPTM_MASTER_GPID].bNeedExtractLine)
        {
            stGfxRect.u32IHgt /= 2;
        }

        HIFB_WBC2_SetCropReso(stGfxRect);
    }

    /**here set layer rect  that been opened by usered **/
    HIFB_ADP_ResetLayerInRect(enGpId);

    /**set zme, if wbc mode, should not set gp1 zme **/
    stGfxZmePara.u32ZmeFrmWIn  = stGfxRect.u32IWth;
    stGfxZmePara.u32ZmeFrmHIn  = stGfxRect.u32IHgt;
    stGfxZmePara.u32ZmeFrmWOut = stOutRect.s32Width;
    stGfxZmePara.u32ZmeFrmHOut = stOutRect.s32Height;
    stGfxZmePara.bDeFlicker    = g_stGfxGPDevice[enGpId].u32ZmeDeflicker ? HI_FALSE : HI_TRUE;
    stGfxZmePara.bZmeFrmFmtIn  = HI_TRUE;
    stGfxZmePara.bZmeFrmFmtOut = g_stGfxGPDevice[enGpId].bInterface ? HI_FALSE : HI_TRUE;

    OPTM_GfxGetPqGpFromDispChannel(g_stGfxGPDevice[enGpId].enDispCh,&enPqGfxGp);
    if (PQ_GFX_LAYER_BUTT == enPqGfxGp)
    {
       return HI_FAILURE;
    }

    OPTM_VDP_GP_SetParaUpd(enGpId,VDP_ZME_MODE_HOR);
    OPTM_VDP_GP_SetParaUpd(enGpId,VDP_ZME_MODE_VER);

#ifndef HI_BUILD_IN_BOOT
    if (IS_SLAVER_GP(enGpId))
    {/** 如果是同源的，这里不处理GP1**/
       return HI_SUCCESS;
    }
    gs_pstPqFuncs->pfnPQ_SetGfxZme(enPqGfxGp, &stGfxZmePara);
#endif

#ifdef HI_BUILD_IN_BOOT
    DRV_PQ_SetGfxZme(enPqGfxGp, &stGfxZmePara);
#endif

    return HI_SUCCESS;
}

static inline HI_VOID HIFB_ADP_ResetLayerInRect(OPTM_GFX_GP_E enGpId)
{
    HI_S32 s32Cnt = 0;
    HI_U32 u32LayerCount  = 0;
    HIFB_LAYER_ID_E enLayerId      = HIFB_LAYER_ID_BUTT;
    HIFB_LAYER_ID_E enInitLayerId  = HIFB_LAYER_ID_BUTT;

    u32LayerCount = (OPTM_GFX_GP_0 == enGpId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enInitLayerId = (OPTM_GFX_GP_0 == enGpId) ? HIFB_LAYER_HD_0 : HIFB_LAYER_SD_0;

    for (s32Cnt = 0; s32Cnt < u32LayerCount; s32Cnt++)
    {
        enLayerId = enInitLayerId + s32Cnt;
        if (!g_stGfxDevice[enLayerId].bOpened)
        {
            continue;
        }
        OPTM_GfxSetLayerRect(enLayerId, &g_stGfxDevice[enLayerId].stInRect);
    }

    return;
}


HI_S32 OPTM_GfxGetGpRect(OPTM_GFX_GP_E enGpId, HIFB_RECT * pstInputRect)
{
    OPTM_VDP_DISP_RECT_S stGfxRect = {0};
    OPTM_VDP_GP_GetLayerReso(enGpId, &stGfxRect);
    pstInputRect->w = stGfxRect.u32IWth;
    pstInputRect->h = stGfxRect.u32IHgt;
    pstInputRect->x = stGfxRect.u32VX;
    pstInputRect->y = stGfxRect.u32VY;
    return HI_SUCCESS;
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : OPTM_GfxSetGpDeflicker
* description   : CNcomment: 设置GP抗闪 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetGpDeflicker(OPTM_GFX_GP_E enGpId, HI_BOOL bDeflicker)
{
    HIFB_RECT stInputRect = {0};

    stInputRect.x = g_stGfxGPDevice[enGpId].stInRect.s32X;
    stInputRect.y = g_stGfxGPDevice[enGpId].stInRect.s32Y;
    stInputRect.w = g_stGfxGPDevice[enGpId].stInRect.s32Width;
    stInputRect.h = g_stGfxGPDevice[enGpId].stInRect.s32Height;

    g_stGfxGPDevice[enGpId].u32ZmeDeflicker = (HI_U32)bDeflicker;

    OPTM_GfxSetGpRect(enGpId, &stInputRect);

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GfxGetOutRect
* description   : CNcomment: 获取输出分辨率 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxGetOutRect(HIFB_LAYER_ID_E enLayerId, HIFB_RECT * pstOutputRect)
{
    OPTM_GFX_GP_E enGpId = g_stGfxDevice[enLayerId].enGPId;

    pstOutputRect->x = 0;
    pstOutputRect->y = 0;
    pstOutputRect->w = g_stGfxGPDevice[enGpId].stInRect.s32Width;
    pstOutputRect->h = g_stGfxGPDevice[enGpId].stInRect.s32Height;

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func          : OPTM_GfxSetLayKeyMask
* description   : CNcomment:设置图层color key 信息CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayKeyMask(HIFB_LAYER_ID_E enLayerId, const HIFB_COLORKEYEX_S *pstColorkey)
{
    OPTM_VDP_GFX_CKEY_S ckey_info;
    OPTM_VDP_GFX_MASK_S ckey_mask;

    /** 判断该图层是否打开 **/
    HIFB_CHECK_GFX_OPEN(enLayerId);

    HI_GFX_Memset(&ckey_info, 0, sizeof(ckey_info));
    HI_GFX_Memset(&ckey_mask, 0, sizeof(ckey_mask));

    HI_GFX_Memcpy(&g_stGfxDevice[enLayerId].stColorkey, pstColorkey, sizeof(HIFB_COLORKEYEX_S));

    /** 是否已经开机logo过渡完 **/
    OPTM_CheckGPMask_BYLayerID(enLayerId);

    ckey_info.bKeyMode  = pstColorkey->u32KeyMode;

    if (g_stGfxDevice[enLayerId].CscState == OPTM_CSC_SET_PARA_BGR)
    {
        ckey_info.u32Key_r_min = pstColorkey->u8BlueMin;
        ckey_info.u32Key_g_min = pstColorkey->u8GreenMin;
        ckey_info.u32Key_b_min = pstColorkey->u8RedMin;

        ckey_info.u32Key_r_max = pstColorkey->u8BlueMax;
        ckey_info.u32Key_g_max = pstColorkey->u8GreenMax;
        ckey_info.u32Key_b_max = pstColorkey->u8RedMax;

        ckey_mask.u32Mask_r = pstColorkey->u8BlueMask;
        ckey_mask.u32Mask_g = pstColorkey->u8GreenMask;
        ckey_mask.u32Mask_b = pstColorkey->u8RedMask;
    }
    else
    {
        ckey_info.u32Key_r_min = pstColorkey->u8RedMin;
        ckey_info.u32Key_g_min = pstColorkey->u8GreenMin;
        ckey_info.u32Key_b_min = pstColorkey->u8BlueMin;

        ckey_info.u32Key_r_max = pstColorkey->u8RedMax;
        ckey_info.u32Key_g_max = pstColorkey->u8GreenMax;
        ckey_info.u32Key_b_max = pstColorkey->u8BlueMax;

        ckey_mask.u32Mask_r = pstColorkey->u8RedMask;
        ckey_mask.u32Mask_g = pstColorkey->u8GreenMask;
        ckey_mask.u32Mask_b = pstColorkey->u8BlueMask;
    }

  /**
     ** set key threshold / mode / enable of graphic layer
     **/
    OPTM_VDP_GFX_SetKeyMask(g_stGfxDevice[enLayerId].enGfxHalId, ckey_mask);
    OPTM_VDP_GFX_SetColorKey(g_stGfxDevice[enLayerId].enGfxHalId, pstColorkey->bKeyEnable, ckey_info);
    /** 配置完要更新寄存器 **/
    OPTM_VDP_GFX_SetRegUp(g_stGfxDevice[enLayerId].enGfxHalId);

    return HI_SUCCESS;

}


/***************************************************************************************
* func          : OPTM_GfxSetLayerPreMult
* description   : CNcomment: 设置图层预乘 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerPreMult(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable)
{
    OPTM_GFX_GP_E enGpId  = g_stGfxDevice[enLayerId].enGPId;

    g_stGfxDevice[enLayerId].bPreMute = bEnable;

    OPTM_CheckGPMask_BYGPID(enGpId);

    OPTM_VDP_GFX_SetPreMultEnable(g_stGfxDevice[enLayerId].enGfxHalId, bEnable);

    return HI_SUCCESS;
}

HI_VOID OPTM_GfxGetClosePreMultState(OPTM_GFX_GP_E enGpId, HI_BOOL *pbShouldClosePreMult)
{
#ifdef CHIP_TYPE_hi3798cv200
    *pbShouldClosePreMult = g_stGfxGPDevice[enGpId].bHdr;
#else
    *pbShouldClosePreMult = HI_FALSE;
#endif
}



#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_GfxWhetherDiscardFrame(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pNoDiscardFrame)
{
    HI_S32 Ret = HI_SUCCESS;
    DISP_EXPORT_FUNC_S *DispExportFuncs = NULL;
    HI_DISP_DISPLAY_INFO_S stDispInfo;
    HI_DRV_DISPLAY_E enDisp;

    if (enLayerId < HIFB_LAYER_SD_0)
    {
       enDisp = HI_DRV_DISPLAY_1;
    }
    else
    {
       enDisp = HI_DRV_DISPLAY_0;
    }

    HI_GFX_Memset(&stDispInfo,0x0,sizeof(HI_DISP_DISPLAY_INFO_S));
    Ret = HI_DRV_MODULE_GetFunction(HI_ID_DISP, (HI_VOID**)&DispExportFuncs);
    if ( (HI_SUCCESS != Ret) || (NULL == DispExportFuncs))
    {
        HIFB_ERROR("disp export funcs get failure\n");
        return;
    }

    Ret = DispExportFuncs->pfnDispGetDispInfo(enDisp,&stDispInfo);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("pfnDispGetDispInfo get failure\n");
        return;
    }

    if (  (HI_DRV_DISP_FMT_1080P_24 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_1080P_25 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_1080P_30 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_1080P_23_976 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_1080P_29_97 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_3840X2160_24 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_3840X2160_25 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_3840X2160_30 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_3840X2160_23_976 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_3840X2160_29_97 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_4096X2160_24 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_4096X2160_25 == stDispInfo.eFmt) || (HI_DRV_DISP_FMT_4096X2160_30 == stDispInfo.eFmt))
    {
       *pNoDiscardFrame = HI_FALSE;
    }
    else
    {
       *pNoDiscardFrame = HI_TRUE;
    }
    return;
}

/***************************************************************************************
* func          : OPTM_GfxGetOSDData
* description   : CNcomment: 获取对应图层得OSD数据 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_GfxGetOSDData(HIFB_LAYER_ID_E enLayerId, HIFB_OSD_DATA_S *pstLayerData)
{
    HI_U32 u32Enable     = HI_FALSE;
    HI_U32 u32KeyEnable  = HI_FALSE;
    HI_U32 alpharange    = 0;
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_BUTT;
    OPTM_VDP_DISP_RECT_S  stRect     = {0};
    OPTM_VDP_DISP_RECT_S stInRect    = {0};
    OPTM_VDP_GFX_MASK_S  stckey_mask = {0};
    OPTM_VDP_GFX_CKEY_S  stKey       = {0};
    OPTM_VDP_GFX_IFMT_E  enDataFmt   = VDP_GFX_IFMT_BUTT;

    if(enLayerId < HIFB_LAYER_SD_0){
        enGPId = OPTM_GFX_GP_0;
    }else{
        enGPId = OPTM_GFX_GP_1;
    }

    OPTM_VDP_GFX_GetLayerEnable(OPTM_GetGfxHalId(enLayerId), &u32Enable);

    if(u32Enable){
        pstLayerData->eState = HIFB_LAYER_STATE_ENABLE;
    }else{
        pstLayerData->eState = HIFB_LAYER_STATE_DISABLE;
    }

    /** 获取surface 帧buffer地址 **/
    OPTM_VDP_GFX_GetLayerAddr(OPTM_GetGfxHalId(enLayerId), &pstLayerData->u32RegPhyAddr);

    OPTM_VDP_GFX_GetLayerStride(OPTM_GetGfxHalId(enLayerId), &pstLayerData->u32Stride);

    OPTM_VDP_GFX_GetLayerInRect(OPTM_GetGfxHalId(enLayerId), &stInRect);
    pstLayerData->stInRect.x = stInRect.u32DXS;
    pstLayerData->stInRect.y = stInRect.u32DYS;
    pstLayerData->stInRect.w = stInRect.u32IWth;
    pstLayerData->stInRect.h = stInRect.u32IHgt;

    OPTM_VDP_GP_GetRect(enGPId, &stRect);

    pstLayerData->stOutRect.x = 0;
    pstLayerData->stOutRect.y = 0;
    pstLayerData->stOutRect.w = stRect.u32IWth;
    pstLayerData->stOutRect.h = stRect.u32IHgt;

    pstLayerData->DisplayWidth = stRect.u32OWth;
    pstLayerData->DisplayHeight= stRect.u32OHgt;

    /** question **/
    OPTM_VDP_WBC_GetEnable(OPTM_VDP_LAYER_WBC_GP0, &u32Enable);
    if (u32Enable){
    /**同源**/
        pstLayerData->eGfxWorkMode = HIFB_GFX_MODE_HD_WBC;
        pstLayerData->enSlaveryLayerID = OPTM_SLAVER_LAYERID;
    }else{/**非同源**/
        pstLayerData->eGfxWorkMode = HIFB_GFX_MODE_NORMAL;
        pstLayerData->enSlaveryLayerID = HIFB_LAYER_ID_BUTT;
    }

    OPTM_VDP_GFX_GetPalpha( OPTM_GetGfxHalId(enLayerId),               \
                           &pstLayerData->stAlpha.bAlphaEnable,        \
                           &alpharange,&pstLayerData->stAlpha.u8Alpha0,\
                           &pstLayerData->stAlpha.u8Alpha1);

    OPTM_VDP_GFX_GetLayerGalpha(OPTM_GetGfxHalId(enLayerId),     \
                                &pstLayerData->stAlpha.u8GlobalAlpha);

    OPTM_VDP_GFX_GetKeyMask (OPTM_GetGfxHalId(enLayerId), &stckey_mask);
    OPTM_VDP_GFX_GetColorKey(OPTM_GetGfxHalId(enLayerId), &u32KeyEnable,&stKey);

    pstLayerData->stColorKey.u8RedMask   = stckey_mask .u32Mask_r;
    pstLayerData->stColorKey.u8GreenMask = stckey_mask .u32Mask_g;
    pstLayerData->stColorKey.u8BlueMask  = stckey_mask .u32Mask_b;

    pstLayerData->stColorKey.bMaskEnable = HI_TRUE;
    pstLayerData->stColorKey.bKeyEnable  = u32KeyEnable;
    pstLayerData->stColorKey.u32KeyMode  = stKey.bKeyMode;

    pstLayerData->stColorKey.u8RedMax    = stKey.u32Key_r_max;
    pstLayerData->stColorKey.u8GreenMax  = stKey.u32Key_g_max;
    pstLayerData->stColorKey.u8BlueMax   = stKey.u32Key_b_max;

    pstLayerData->stColorKey.u8RedMin    = stKey.u32Key_r_min;
    pstLayerData->stColorKey.u8GreenMin  = stKey.u32Key_g_min;
    pstLayerData->stColorKey.u8BlueMin   = stKey.u32Key_b_min;

    OPTM_VDP_GFX_GetPreMultEnable(OPTM_GetGfxHalId(enLayerId), &pstLayerData->bPreMul);

    OPTM_VDP_GFX_GetInDataFmt(OPTM_GetGfxHalId(enLayerId), &enDataFmt);

    pstLayerData->eFmt = OPTM_HalFmtTransferToPixerFmt(enDataFmt);

}


HI_VOID HIFB_ADP_GetLogoData(HIFB_LAYER_ID_E enLayerId, HIFB_LOGO_DATA_S *pstLogoData)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_U32 LayerEnable = 0;
     OPTM_VDP_GFX_IFMT_E  enDataFmt   = VDP_GFX_IFMT_BUTT;
     HIFB_COLOR_FMT_E enFmt = HIFB_FMT_BUTT;
     DISP_EXPORT_FUNC_S *DispExportFuncs = NULL;
     HI_DISP_DISPLAY_INFO_S stDispInfo;
     HI_DRV_DISPLAY_E enDisp;
     HI_RECT_S stOutRect = {0};
     OPTM_VDP_DISP_RECT_S stInRect = {0};

     if (enLayerId < HIFB_LAYER_SD_0)
     {
        enDisp = HI_DRV_DISPLAY_1;
     }
     else
     {
        enDisp = HI_DRV_DISPLAY_0;
     }

     HI_GFX_Memset(&stDispInfo,0x0,sizeof(HI_DISP_DISPLAY_INFO_S));
     Ret = HI_DRV_MODULE_GetFunction(HI_ID_DISP, (HI_VOID**)&DispExportFuncs);
     if ( (HI_SUCCESS != Ret) || (NULL == DispExportFuncs))
     {
         HIFB_ERROR("disp export funcs get failure\n");
         return;
     }

     Ret = DispExportFuncs->pfnDispGetDispInfo(enDisp,&stDispInfo);
     if (HI_SUCCESS != Ret)
     {
         HIFB_ERROR("pfnDispGetDispInfo get failure\n");
         return;
     }
     OPTM_GetScreenRectFromDispInfo(&stDispInfo.stVirtaulScreen, (OPTM_GFX_OFFSET_S *)&stDispInfo.stOffsetInfo,
                                    &stDispInfo.stFmtResolution,&stDispInfo.stPixelFmtResolution,
                                    &stOutRect);

     OPTM_VDP_GFX_GetLayerInRect (OPTM_GetGfxHalId(enLayerId), &stInRect);
     OPTM_VDP_GFX_GetLayerEnable (OPTM_GetGfxHalId(enLayerId), &LayerEnable);
     OPTM_VDP_GFX_GetLayerAddr   (OPTM_GetGfxHalId(enLayerId), &pstLogoData->LogoYAddr);
     OPTM_VDP_GFX_GetInDataFmt   (OPTM_GetGfxHalId(enLayerId), &enDataFmt);
     enFmt = OPTM_HalFmtTransferToPixerFmt(enDataFmt);

     if (   (CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH == stInRect.u32IWth || CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH == stInRect.u32IWth)
         && (CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH == stDispInfo.stFmtResolution.s32Width || CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH == stDispInfo.stFmtResolution.s32Width)
         && (CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT == stInRect.u32IHgt)
         && (CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT == stDispInfo.stFmtResolution.s32Height))
     {
         pstLogoData->Support4KLogo = HI_TRUE;
     }

     pstLogoData->LogoEnable     = (1 == LayerEnable) ? (HI_TRUE) : (HI_FALSE);
     pstLogoData->LogoCbCrAddr   = 0x0;

     if ((enLayerId < HIFB_LAYER_SD_0) && (HI_FALSE == pstLogoData->Support4KLogo))
     {
        pstLogoData->LogoWidth      = stDispInfo.stVirtaulScreen.s32Width;
        pstLogoData->LogoHeight     = stDispInfo.stVirtaulScreen.s32Height;
     }
     else
     {
        pstLogoData->LogoWidth      = stDispInfo.stFmtResolution.s32Width;
        pstLogoData->LogoHeight     = stDispInfo.stFmtResolution.s32Height;
     }
     pstLogoData->stOutRect.x    = stOutRect.s32X;
     pstLogoData->stOutRect.y    = stOutRect.s32Y;
     pstLogoData->stOutRect.w    = stOutRect.s32Width;
     pstLogoData->stOutRect.h    = stOutRect.s32Height;
     pstLogoData->eLogoPixFmt    = HIFB_LOGO_PIX_FMT_ARGB8888;
     pstLogoData->LogoYStride    = pstLogoData->LogoWidth * 4;
     if (HIFB_FMT_ARGB1555 == enFmt)
     {
        pstLogoData->eLogoPixFmt = HIFB_LOGO_PIX_FMT_ARGB1555;
        pstLogoData->LogoYStride = pstLogoData->LogoWidth * 2;
     }
     return;
}
#endif



/***************************************************************************************
* func          : OPTM_GfxUpLayerReg
* description   : CNcomment: 更新寄存器 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxUpLayerReg(HIFB_LAYER_ID_E enLayerId)
{
    OPTM_GFX_GP_E enGpId = g_stGfxDevice[enLayerId].enGPId;
    /**
         ** if the para has not setted finish,do not updata the register
        ** 如果相关寄存器没有配置完，不更新寄存器使相关配置暂时不生效
        **/
    OPTM_CheckGPMask_BYGPID(enGpId);

#ifdef CFG_HIFB_PROC_SUPPORT
    HIFB_PROC_CountVoCallBackScanLineAbnormalTimes(enLayerId);
#endif

    OPTM_VDP_GFX_SetRegUp(g_stGfxDevice[enLayerId].enGfxHalId);
    OPTM_VDP_GP_SetRegUp (g_stGfxGPDevice[g_stGfxDevice[enLayerId].enGPId].enGpHalId);

    if (IS_MASTER_GP(enGpId))
    {
        HIFB_WBC2_Reset(HI_TRUE);
    }

    return HI_SUCCESS;
}

HI_VOID HIFB_ADP_SetInOutScanLine(HIFB_LAYER_ID_E LayerId, HI_BOOL bInScanLine)
{
#ifdef CFG_HIFB_PROC_SUPPORT
    HI_U32 Scanline = 0;
    HIFB_HAL_GetVoCallBackCurScanLine(&Scanline);
    HIFB_PROC_SetVoCallBackInOutScanLine(LayerId,Scanline,bInScanLine);
#endif
    return;
}


#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
/***************************************************************************************
* func          : OPTM_GfxGetHalTriDimMode
* description   : CNcomment: 获取3D模式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
OPTM_VDP_DISP_MODE_E OPTM_GfxGetHalTriDimMode(HIFB_STEREO_MODE_E enMode)
{
    switch(enMode)
    {
        case HIFB_STEREO_MONO:
            return VDP_DISP_MODE_2D;
        case HIFB_STEREO_SIDEBYSIDE_HALF:
            return VDP_DISP_MODE_SBS;
        case HIFB_STEREO_TOPANDBOTTOM:
            return VDP_DISP_MODE_TAB;
        case HIFB_STEREO_FRMPACKING:
            return VDP_DISP_MODE_FP;
        default:
            return VDP_DISP_MODE_BUTT;
    }

    return VDP_DISP_MODE_BUTT;
}


/***************************************************************************************
* func          : OPTM_GfxSetTriDimMode
* description   : CNcomment: 设置3D模式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetTriDimMode(HIFB_LAYER_ID_E enLayerId, HIFB_STEREO_MODE_E enMode, HIFB_STEREO_MODE_E enWbcSteroMode)
{
    HI_U32 u32GpId = (HI_U32)(g_stGfxDevice[enLayerId].enGPId);

    if(u32GpId >= (HI_U32)OPTM_GFX_GP_BUTT){
        return HI_FAILURE;
    }
    /**
     **保存GP和图层的3D模式
     **/
    g_stGfxDevice[enLayerId].enTriDimMode = enMode;
    g_stGfxGPDevice[u32GpId].enTriDimMode = enMode;

    OPTM_CheckGPMask_BYGPID(u32GpId);

    OPTM_VDP_GP_SetRegUp(g_stGfxDevice[enLayerId].enGPId);
    /**
     ** WBC_GP_INRECT == GP_INRECT
     **/
    if(IS_MASTER_GP(u32GpId)){
        g_stGfxGPDevice[OPTM_SLAVER_GPID].enTriDimMode = enWbcSteroMode;
        g_stGfxGPDevice[OPTM_SLAVER_GPID].stInRect.s32Width  = g_stGfxGPDevice[u32GpId].stInRect.s32Width;
        g_stGfxGPDevice[OPTM_SLAVER_GPID].stInRect.s32Height = g_stGfxGPDevice[u32GpId].stInRect.s32Height;

        if(HIFB_STEREO_MONO == enWbcSteroMode){
            g_stGfxWbc2.enWbcMode = OPTM_WBC_MODE_MONO;
        }else{
            g_stGfxWbc2.enWbcMode = OPTM_WBC_MODE_LFET_EYE;
        }
        /** 3d回写使能 **/
        g_stGfxGPDevice[OPTM_SLAVER_GPID].unUpFlag.bits.WbcMode          = 1;
        g_stGfxGPDevice[OPTM_SLAVER_GPID].unUpFlag.bits.IsNeedUpInRect   = 1;
        HIFB_WBC2_Reset(HI_TRUE);
    }

    return HI_SUCCESS;

}

/***************************************************************************************
* func            : OPTM_GfxSetTriDimAddr
* description    : CNcomment: 设置3D显示地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:        : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetTriDimAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 u32TriDimAddr)
{
    g_stGfxDevice[enLayerId].u32TriDimAddr= u32TriDimAddr;

    OPTM_CheckGPMask_BYLayerID(enLayerId);

    OPTM_VDP_GFX_SetLayerNAddr(enLayerId, u32TriDimAddr);

    return HI_SUCCESS;
}
#endif



#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : OPTM_GfxGetLayerPriority
* description   : CNcomment: 获取图层在GP 中的优先级 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxGetLayerPriority(HIFB_LAYER_ID_E enLayerId, HI_U32 *pU32Priority)
{
    HI_U32 i            = 0;
    HI_U32 u32prio      = 0;
    HI_U32 u32Index     = 0;
    HI_U32 u32LayerPrio = 0;
    HI_U32 u32LayerIdIndex = 0;
    OPTM_VDP_CBM_MIX_E eCbmMixg;

    u32Index = (g_stGfxDevice[enLayerId].enGPId == OPTM_GFX_GP_0) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    eCbmMixg = (g_stGfxDevice[enLayerId].enGPId == OPTM_GFX_GP_0) ? VDP_CBM_MIXG0 : VDP_CBM_MIXG1;
    OPTM_VDP_CBM_GetMixerPrio(eCbmMixg, &u32prio);

    /**
     ** HIFB_LAYER_HD_0 -> 0
     ** HIFB_LAYER_HD_1 -> 1
     ** HIFB_LAYER_SD_0 -> 0
     ** HIFB_LAYER_SD_1 -> 1
     **/
    if(HIFB_LAYER_HD_2 == enLayerId){
        u32LayerIdIndex = 3; /** G3 **/
    }
    else{
        u32LayerIdIndex =  enLayerId - OPTM_GP0_GFX_COUNT * g_stGfxDevice[enLayerId].enGPId;
    }
    for(i = 0; i < u32Index; i++){
        u32LayerPrio = u32prio & 0xf;
        u32prio      = u32prio >> 4;
        if((u32LayerPrio-1) == u32LayerIdIndex){
            *pU32Priority = i+1;
            return HI_SUCCESS;
        }
    }
    HIFB_ERROR("info:fail to get z_order of gfx%d!\n",enLayerId);
    return HI_FAILURE;

}

/***************************************************************************************
* func          : OPTM_GfxSetLayerPriority
* description   : CNcomment: 设置图层在GP 中的优先级 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerPriority(HIFB_LAYER_ID_E enLayerId, HIFB_ZORDER_E enZOrder)
{
    HI_U32  u32Prio        = 0;
    HI_U32  u32LayerPrio   = 0;
    HI_U32  u32MaskUpBit   = 0;
    HI_U32  u32MaskDownBit = 0;
    HI_U32  u32SwitchBit   = 0;
    HI_U32  u32MaskTopBit  = 0;
    HI_U32  u32MaskBit     = 0;
    HI_U32  u32LayerCount  = 0;
    HI_S32  count          = 0;
    OPTM_VDP_CBM_MIX_E eCbmMixg = VDP_CBM_MIX_BUTT;

    if (HI_SUCCESS != OPTM_GfxGetLayerPriority(enLayerId, &u32LayerPrio)){
        HIFB_ERROR("info:fail to set z_order of gfx%d!\n",enLayerId);
        return HI_FAILURE;
    }

    eCbmMixg = (g_stGfxDevice[enLayerId].enGPId == OPTM_GFX_GP_0) ? VDP_CBM_MIXG0 : VDP_CBM_MIXG1;
    OPTM_VDP_CBM_GetMixerPrio(eCbmMixg, &u32Prio);
    u32LayerCount = (g_stGfxDevice[enLayerId].enGPId == OPTM_GFX_GP_0) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;

    u32SwitchBit = (u32Prio >> (4*(u32LayerPrio-1))) & 0xf;

    for(count = u32LayerPrio; count > 0; count--)
    {
        u32MaskUpBit = 0xf | (u32MaskUpBit << 4);
    }

    for(count = u32LayerPrio; count <= u32LayerCount; count++)
    {
        u32MaskDownBit = 0xf | (u32MaskDownBit << 4);
    }
    u32MaskDownBit <<= 4*(u32LayerPrio-1);

    u32MaskBit = 0xf;
    u32MaskTopBit = 0xf;
    for(count = 1; count < u32LayerCount; count++)
    {
        u32MaskBit = 0xf | (u32MaskBit << 4);
        u32MaskTopBit = u32MaskTopBit << 4;
    }

    u32Prio &= u32MaskBit;
    switch (enZOrder)
    {
        case HIFB_ZORDER_MOVEBOTTOM:
        {
            if (u32LayerPrio == 1)
            {
               return HI_SUCCESS;
            }
            /*当前layer之上的Z序值保持不变|当前layer之下的Z序值上移|当前layer Z序值*/
            u32Prio = (u32Prio&(~u32MaskUpBit)) | \
                      ((u32MaskUpBit&((u32Prio&u32MaskUpBit)<<4))&(~0xf)) |
                      u32SwitchBit;
            break;
        }
        case HIFB_ZORDER_MOVEDOWN:
        {
            if (u32LayerPrio == 1)
            {
               return HI_SUCCESS;
            }

            u32Prio = ((u32Prio&(0xf<<4*(u32LayerPrio-1)))>>4) | \
                      ((u32Prio&(0xf<<4*(u32LayerPrio-2)))<<4) | \
                       (~((0xf<<4*(u32LayerPrio-1))|(0xf<<4*(u32LayerPrio-2)))&u32Prio);
            break;
        }
        case HIFB_ZORDER_MOVETOP:
        {
            if (u32LayerPrio == u32LayerCount)
            {
               return HI_SUCCESS;
            }
            /*当前layer之下的Z序值保持不变|当前layer之上的Z序值下移|当前layer Z序值*/
            u32Prio = (u32Prio&(~u32MaskDownBit)) | \
                      ((u32MaskDownBit&((u32Prio&u32MaskDownBit)>>4))&(~u32MaskTopBit)) | \
                      (u32SwitchBit<<(4*(u32LayerCount-1)));
            break;
        }
        case HIFB_ZORDER_MOVEUP:
        {

            if (u32LayerPrio == u32LayerCount)
            {
               return HI_SUCCESS;
            }
            u32Prio = ((u32Prio&(0xf<<4*(u32LayerPrio-1)))<<4) | \
                      ((u32Prio&(0xf<<4*u32LayerPrio))>>4) | \
                       (~((0xf<<4*(u32LayerPrio-1))|(0xf<<4*u32LayerPrio))&u32Prio);
            break;
        }
        default:
        {
            return HI_FAILURE;
        }
    }

    u32Prio &= u32MaskBit;

    OPTM_VDP_SetMixgPrio(eCbmMixg, u32Prio);

    g_stGfxGPDevice[g_stGfxDevice[enLayerId].enGPId].u32Prior = u32Prio;


    return HI_SUCCESS;

}


/***************************************************************************************
* func          : OPTM_DispInfoUpdate
* description   : CNcomment: 更新display信息 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_DispInfoUpdate(OPTM_VDP_LAYER_GP_E enGPId)
{
    HI_U32           i;
    HI_U32           u32LayerCount;
    HI_RECT_S        *pstDispRect;
    HIFB_LAYER_ID_E  enInitLayerId;
    HIFB_LAYER_ID_E  enLayerId;

    if(!g_stGfxGPDevice[enGPId].bOpen){
        return HI_SUCCESS;
    }

    OPTM_CheckGPMask_BYGPID(enGPId);

    u32LayerCount = (OPTM_VDP_LAYER_GP0 == enGPId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enInitLayerId = (OPTM_VDP_LAYER_GP0 == enGPId) ? HIFB_LAYER_HD_0 : HIFB_LAYER_SD_0;

    pstDispRect = &g_stGfxGPDevice[enGPId].stOutRect;

    if (IS_SLAVER_GP((OPTM_GFX_GP_E)enGPId))
    {
        OPTM_GPSetCsc(enGPId, &g_stGfxGPDevice[enGPId].stCscPara,g_stGfxGPDevice[enGPId].bBGRState);
    }
    else
    {
        /*when recovery gp , set disp size to hardware first*/
        OPTM_GfxSetDispFMTSize((OPTM_GFX_GP_E)enGPId, pstDispRect);
        /**
                ** recover all gfx in the gp
                **/
        for (i = 0; i < u32LayerCount;i++)
        {
            enLayerId = enInitLayerId + i;

            if(!g_stGfxDevice[enLayerId].bOpened){
                continue;
            }

            OPTM_GfxSetLayerRect(enLayerId, &g_stGfxDevice[enLayerId].stInRect);
            OPTM_VDP_GFX_SetUpdMode (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].enUpDateMode);
            OPTM_VDP_GFX_SetRegUp(enLayerId);
        }
        OPTM_VDP_GP_SetRegUp   (enGPId);

    }

    return HI_SUCCESS;
}
#endif


/***************************************************************************************
* func          : OPTM_GPRecovery
* description   : CNcomment: 重新设置GP属性 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GPRecovery(OPTM_GFX_GP_E enGPId)
{
    HI_U32           i             = 0;
    HI_U32           u32LayerCount = 0;
    HI_RECT_S        *pstDispRect  = &g_stGfxGPDevice[enGPId].stOutRect;
    HIFB_LAYER_ID_E  enInitLayerId = HIFB_LAYER_HD_0;
    HIFB_LAYER_ID_E  enLayerId     = HIFB_LAYER_HD_0;

    if (!g_stGfxGPDevice[enGPId].bOpen)
    {
        return HI_SUCCESS;
    }

    /**
     ** check whether should reset the gp property,false should reset
     **/
    OPTM_CheckGPMask_BYGPID(enGPId);

    /**
     **check reset which layer
     **/
    u32LayerCount   = (OPTM_GFX_GP_0 == enGPId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enInitLayerId   = (OPTM_GFX_GP_0 == enGPId) ? HIFB_LAYER_HD_0    : HIFB_LAYER_SD_0;

    /**
     **GP0 1920 * 1080
     **GP1 720  * 576
     **/
    OPTM_VDP_CBM_SetMixerBkg    (g_stGfxGPDevice[enGPId].enMixg, g_stGfxGPDevice[enGPId].stBkg);
    OPTM_VDP_SetMixgPrio        (g_stGfxGPDevice[enGPId].enMixg, g_stGfxGPDevice[enGPId].u32Prior);
    OPTM_VDP_GP_SetLayerGalpha  (enGPId, g_stGfxGPDevice[enGPId].u32Alpha);

    if (IS_SLAVER_GP(enGPId))
    {
        HIFB_WBC2_Recovery(enGPId);
        return HI_SUCCESS;
    }

    OPTM_GfxSetDispFMTSize (enGPId, pstDispRect);
    OPTM_VDP_GP_SetRegUp   (enGPId);
    /**
     **recover all gfx in the gp
     **/
    for (i = 0; i < u32LayerCount;i++)
    {
        enLayerId = enInitLayerId + i;
        if (!g_stGfxDevice[enLayerId].bOpened)
        {
            /**
             ** Close graphics layer if the state record is not the same with hardware.
             ** scene:quickboot,close logo here if logo exist!
             **/
            OPTM_VDP_GFX_SetLayerEnable (g_stGfxDevice[enLayerId].enGfxHalId, HI_FALSE);
            OPTM_VDP_GFX_SetRegUp       (g_stGfxDevice[enLayerId].enGfxHalId);
            continue;
        }

        OPTM_GfxSetEnable         (enLayerId, g_stGfxDevice[enLayerId].bEnable);
        OPTM_GfxSetLayerAlpha     (enLayerId, &g_stGfxDevice[enLayerId].stAlpha);
        OPTM_GfxSetLayKeyMask     (enLayerId, &g_stGfxDevice[enLayerId].stColorkey);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
        OPTM_GfxSetTriDimMode     (enLayerId, g_stGfxDevice[enLayerId].enTriDimMode, g_stGfxGPDevice[OPTM_SLAVER_GPID].enTriDimMode);
        OPTM_GfxSetTriDimAddr     (enLayerId, g_stGfxDevice[enLayerId].u32TriDimAddr);
        OPTM_GFX_SetStereoDepth   (enLayerId, g_stGfxDevice[enLayerId].s32Depth);
#endif

        OPTM_GfxSetLayerPreMult   (enLayerId, g_stGfxDevice[enLayerId].bPreMute);
        OPTM_GfxSetLayerDataFmt   (enLayerId, g_stGfxDevice[enLayerId].enDataFmt);
        OPTM_GfxSetLayerRect      (enLayerId, &g_stGfxDevice[enLayerId].stInRect);

        OPTM_VDP_GFX_SetLutAddr   (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].stCluptTable.u32StartPhyAddr);
        OPTM_VDP_GFX_SetParaUpd   (g_stGfxDevice[enLayerId].enGfxHalId, VDP_DISP_COEFMODE_LUT);
        OPTM_VDP_GFX_SetLayerBkg  (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].stBkg);
        OPTM_VDP_GFX_SetBitExtend (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].enBitExtend);

#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(HI_BUILD_IN_BOOT)
        if ((HIFB_LAYER_HD_0 == enLayerId) && (HI_TRUE == g_stGfxDevice[enLayerId].bDmpOpened))
        {
            OPTM_GFX_DECMP_Open(enLayerId);
        }
#endif

#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE)
        if (HI_TRUE == g_stGfxDevice[enLayerId].bDmpOpened)
        {
           DRV_HAL_SetDeCmpDdrInfo(enLayerId,g_stGfxDevice[enLayerId].ARHeadDdr,g_stGfxDevice[enLayerId].ARDataDdr,g_stGfxDevice[enLayerId].GBHeadDdr,g_stGfxDevice[enLayerId].GBDataDdr,g_stGfxDevice[enLayerId].CmpStride);
        }
        else
#endif
        {
            OPTM_GfxSetLayerStride    (enLayerId, g_stGfxDevice[enLayerId].Stride);
            OPTM_GfxSetLayerAddr      (enLayerId, g_stGfxDevice[enLayerId].NoCmpBufAddr);
        }

#ifdef CONFIG_HIFB_GFX3_TO_GFX5
        /*gfx3 have no zme*/
        if (OPTM_VDP_LAYER_GFX3 == g_stGfxDevice[enLayerId].enGfxHalId)
        {
            g_stGfxDevice[enLayerId].enReadMode = VDP_RMODE_PROGRESSIVE;//g_stGfxGPDevice[enGPId].bInterface ? VDP_RMODE_SELF_ADAPTION : VDP_RMODE_PROGRESSIVE;
        }
#endif
        OPTM_GfxSetLayerReadMode(enLayerId, g_stGfxDevice[enLayerId].enReadMode);
        OPTM_VDP_GFX_SetUpdMode (g_stGfxDevice[enLayerId].enGfxHalId, g_stGfxDevice[enLayerId].enUpDateMode);
   }

   return HI_SUCCESS;
}

#ifndef HI_BUILD_IN_BOOT

/***************************************************************************************
* func          : OPTM_VO_Callback
* description   : CNcomment: VO CALLBACK CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_VO_Callback(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
    HI_U32                      i;
    HI_U32                      u32CTypeFlag;
    HI_U32                      u32LayerCount;
    HIFB_LAYER_ID_E             enInitLayerId;
    OPTM_VDP_LAYER_GP_E         *pEnGpHalId  = (OPTM_VDP_LAYER_GP_E *)u32Param0;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    if ((NULL == pEnGpHalId) || (NULL == pstDispInfo))
    {
        return HI_FAILURE;
    }

    u32LayerCount = (OPTM_VDP_LAYER_GP0 == *pEnGpHalId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enInitLayerId = (OPTM_VDP_LAYER_GP0 == *pEnGpHalId) ? HIFB_LAYER_HD_0 : HIFB_LAYER_SD_0;

    for (i = 0; i < u32LayerCount;i++)
    {
        u32CTypeFlag = g_stGfxGPIrq[*pEnGpHalId].stGfxCallBack[i].u32CTypeFlag;
        if (HIFB_CALLBACK_TYPE_VO != (u32CTypeFlag & HIFB_CALLBACK_TYPE_VO))
        {
           continue;
        }

        if (NULL != g_stGfxGPIrq[*pEnGpHalId].stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].pFunc)
        {
            g_stGfxGPIrq[*pEnGpHalId].stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].pFunc(
                g_stGfxGPIrq[*pEnGpHalId].stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].pParam0,HI_NULL);
        }
    }

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_Distribute_Callback
* description   : CNcomment: 分发中断处理类型 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_Distribute_Callback(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    HIFB_STEREO_MODE_E enTriDimMode;
#endif
    OPTM_GFX_GP_E      *penGpId  = (OPTM_GFX_GP_E *)u32Param0;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    if(penGpId == HI_NULL || pstDispInfo == HI_NULL){
        return HI_FAILURE;
    }

    OPTM_VO_Callback(u32Param0, u32Param1);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    enTriDimMode = OPTM_AdaptTriDimModeFromDisp(OPTM_DISP_GetDispMode(g_stGfxGPDevice[*penGpId].enGpHalId));

    if ((enTriDimMode != g_stGfxGPDevice[*penGpId].enTriDimMode) && (HIFB_STEREO_BUTT > enTriDimMode))
    {
        if (OPTM_CheckGfxCallbackReg((OPTM_GFX_GP_E)(*penGpId), HIFB_CALLBACK_TYPE_3DMode_CHG) != HI_SUCCESS)
        {
           return HI_SUCCESS;
        }

        g_stGfxGPDevice[*penGpId].enTriDimMode = enTriDimMode;

        OPTM_VDP_GP_SetRegUp   (*penGpId);

        g_stGfxGPDevice[*penGpId].st3DModeChgWork.u32Data = *penGpId;

        queue_work(g_stGfxGPDevice[*penGpId].queue, &g_stGfxGPDevice[*penGpId].st3DModeChgWork.work);
    }
#endif

    return HI_SUCCESS;
}
#endif


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : OPTM_GFX_SetGPMask
* description   : CNcomment: 这个接口只有开机logo才会用到，主要是用来过渡使用的
                             设置GP0和GP1掩码，并且在logo过渡完之后重新设置GP CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_SetGPMask(OPTM_GFX_GP_E enGpId, HI_BOOL bFlag)
{
    HIFB_OSD_DATA_S stLayerData;

    g_stGfxGPDevice[enGpId].bMaskFlag = bFlag;
    /**
     ** when logo is clear, should updata gp info, use app gp info
     ** 如果logo已经清除，就需要配置用户的信息，否则会一直保留着logo
     ** 的配置，除非状态发生变化才会重新跟新GP
     **/
    if(!bFlag){
        OPTM_GPRecovery(enGpId);
    }

    if(OPTM_MASTER_GPID == enGpId){
        OPTM_GfxGetOSDData(HIFB_LAYER_SD_0, &stLayerData);
        if(IS_MASTER_GP(enGpId) || HIFB_LAYER_STATE_ENABLE == stLayerData.eState){
            g_stGfxGPDevice[OPTM_SLAVER_GPID].bMaskFlag = bFlag;
            if(!bFlag && g_stGfxWbc2.IsOpen){
                OPTM_GPRecovery(OPTM_SLAVER_GPID);
            }
        }
    }
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GFX_GetGfxMask
* description   : CNcomment: 获取GP设置掩码 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_GetGfxMask(OPTM_GFX_GP_E enGpId)
{
    return g_stGfxGPDevice[enGpId].bMaskFlag;
}


/***************************************************************************************
* func          : OPTM_GFX_ClearLogoOsd
* description   : CNcomment: 清logo CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_ClearLogoOsd(HIFB_LAYER_ID_E enLayerId)
{
    HI_UNUSED(enLayerId);
    return HI_SUCCESS;
}

#endif


#if !defined(HI_BUILD_IN_BOOT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
/***************************************************************************************
* func          : OPTM_GFX_SetStereoDepth
* description   : CNcomment: 设置3D景深，与人眼的距离 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GFX_SetStereoDepth(HIFB_LAYER_ID_E enLayerId, HI_S32 s32Depth)
{
    g_stGfxDevice[enLayerId].s32Depth = s32Depth;

    if(g_stGfxDevice[enLayerId].s32Depth != 0){
        OPTM_VDP_GFX_SetThreeDimDofEnable(OPTM_GetGfxHalId(enLayerId), HI_TRUE);
    }

    OPTM_VDP_GFX_SetThreeDimDofStep(OPTM_GetGfxHalId(enLayerId), s32Depth, (0-s32Depth));

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func          : OPTM_GFX_SetTCFlag
* description   : CNcomment: 设置是不是TC使用场景标识 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_SetTCFlag(HI_BOOL bFlag)
{
    HIFB_WBC2_SetTcFlag(bFlag);
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GFX_GetHaltDispStatus
* description   : CNcomment: 获取显示状态 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_GetHaltDispStatus(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbDispInit)
{
    OPTM_GFX_GP_E enGPId = g_stGfxDevice[enLayerId].enGPId;
    *pbDispInit =  g_stGfxGPDevice[enGPId].bGpClose?HI_FALSE:HI_TRUE;
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_AllocAndMap
* description   : CNcomment: alloc and map mem CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, GFX_MMZ_BUFFER_S *psMBuf)
{
    #ifndef HI_BUILD_IN_BOOT
        return HI_GFX_AllocAndMap(bufname, zone_name, size, align, psMBuf);
    #else
        if (HI_SUCCESS == HI_DRV_PDM_AllocReserveMem(bufname, size, &psMBuf->u32StartPhyAddr)){
            psMBuf->pu8StartVirAddr = (HI_U8*)psMBuf->u32StartPhyAddr;
            return HI_SUCCESS;
        }else{
            return HI_FAILURE;
        }
    #endif
}

/***************************************************************************************
* func          : OPTM_UnmapAndRelease
* description   : unmap the ddr and release it\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_UnmapAndRelease(GFX_MMZ_BUFFER_S *psMBuf)
{
    #ifdef HI_BUILD_IN_BOOT
        return;
    #else
        HI_GFX_UnmapAndRelease(psMBuf);
    #endif
}

/***************************************************************************************
* func          : OPTM_Adapt_AllocAndMap
* description   : CNcomment: 分配内存并映射地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_Adapt_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, GFX_MMZ_BUFFER_S *psMBuf)
{
    #ifndef HI_BUILD_IN_BOOT
        return HI_GFX_AllocAndMap(bufname, zone_name, size, align, psMBuf);
    #else
        psMBuf->u32StartPhyAddr = (HI_U32)HI_GFX_Malloc(size,"hifb_wbc_buffer");
        if (HI_NULL == psMBuf->u32StartPhyAddr)
        {
            HIFB_ERROR("fail to alloc buffer.\n");
            return HI_FAILURE;
        }
        return HI_SUCCESS;
    #endif
}


HI_BOOL HIFB_ADP_GetIsGfxWorkAtWbc(HI_VOID)
{
    return (HIFB_GFX_MODE_HD_WBC == g_enOptmGfxWorkMode) ? (HI_TRUE) : (HI_FALSE);
}


/***************************************************************************************
* func          : OPTM_GFX_GetOps
* description   : CNcomment: 获取设备上下文 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_GFX_GetOps(OPTM_GFX_OPS_S *ops)
{

    ops->OPTM_GfxCloseLayer         = OPTM_GfxCloseLayer;
    ops->OPTM_GfxDeInit             = OPTM_GfxDeInit;
#ifndef HI_BUILD_IN_BOOT
    ops->OPTM_GfxGetLayerPriority   = OPTM_GfxGetLayerPriority;
    ops->OPTM_GfxGetOSDData         = OPTM_GfxGetOSDData;
    ops->HIFB_ADP_GetLogoData       = HIFB_ADP_GetLogoData;
#endif
    ops->OPTM_GfxInit               = OPTM_GfxInit;
    ops->OPTM_GfxOpenLayer          = OPTM_GfxOpenLayer;
#ifndef HI_BUILD_IN_BOOT
    ops->OPTM_GfxSetCallback        = OPTM_GfxSetCallback;
#endif
    ops->OPTM_GfxSetColorReg        = OPTM_GFX_SetClutColorReg;
    ops->OPTM_GfxSetEnable          = OPTM_GfxSetEnable;
    ops->OPTM_GfxSetGpRect          = OPTM_GfxSetGpRect;
    ops->OPTM_GfxGetGpRect          = OPTM_GfxGetGpRect;
#ifndef HI_BUILD_IN_BOOT
    ops->OPTM_GfxSetGpInPutSize     = OPTM_GfxSetGpInPutSize;
#endif
    ops->OPTM_GfxSetLayerAddr       = OPTM_GfxSetLayerAddr;
    ops->OPTM_GfxGetLayerAddr       = OPTM_GfxGetLayerAddr;
    ops->OPTM_GfxSetLayerAlpha      = OPTM_GfxSetLayerAlpha;

    ops->OPTM_GfxSetLayerDataFmt    = OPTM_GfxSetLayerDataFmt;
    ops->OPTM_GfxSetLayerDeFlicker  = OPTM_GfxSetLayerDeFlicker;
    ops->OPTM_GfxSetLayerPreMult    = OPTM_GfxSetLayerPreMult;
    ops->OPTM_GfxGetClosePreMultState = OPTM_GfxGetClosePreMultState;
#ifndef HI_BUILD_IN_BOOT
    ops->OPTM_GfxWhetherDiscardFrame  = OPTM_GfxWhetherDiscardFrame;
    ops->OPTM_GfxSetLayerPriority   = OPTM_GfxSetLayerPriority;
#endif
    ops->OPTM_GfxSetLayerRect       = OPTM_GfxSetLayerRect;
    ops->OPTM_GfxSetLayerStride     = OPTM_GfxSetLayerStride;
    ops->OPTM_GfxSetLayKeyMask      = OPTM_GfxSetLayKeyMask;
    ops->OPTM_GfxUpLayerReg         = OPTM_GfxUpLayerReg;
    ops->HIFB_ADP_SetInOutScanLine  = HIFB_ADP_SetInOutScanLine;
    ops->OPTM_GfxWaitVBlank         = OPTM_GfxWaitVBlank;
    ops->OPTM_GFX_GetDevCap         = OPTM_GFX_GetDevCap;
#ifndef HI_BUILD_IN_BOOT
    ops->OPTM_GfxGetOutRect         = OPTM_GfxGetOutRect;
#endif
    ops->OPTM_GfxGetLayerRect       = OPTM_GfxGetLayerRect;
#ifndef HI_BUILD_IN_BOOT
    ops->OPTM_GFX_SetGPMask         = OPTM_GFX_SetGPMask;
    ops->OPTM_GFX_GetGfxMask        = OPTM_GFX_GetGfxMask;
    ops->OPTM_GfxGetDispFMTSize     = OPTM_GfxGetDispFMTSize;
    ops->OPTM_GFX_GetSlvLayerInfo   = HIFB_WBC_GetLayerInfo;
#endif
    ops->OPTM_GFX_SetTCFlag         = OPTM_GFX_SetTCFlag;

#ifndef HI_BUILD_IN_BOOT
    ops->HIFB_ADP_GetResumeStatus   = HIFB_ADP_GetResumeStatus;
    ops->HIFB_ADP_SetLowPowerInfo   = HIFB_ADP_SetLowPowerInfo;
#endif

#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(HI_BUILD_IN_BOOT)
    ops->HIFB_ADP_SetDeCmpDdrInfo   = HIFB_ADP_SetDeCmpDdrInfo;
    ops->HIFB_ADP_GetDeCmpStatus    = HIFB_ADP_GetDeCmpStatus;
    ops->HIFB_ADP_SetVdpIntMask     = HIFB_ADP_SetVdpIntMask;
    ops->HIFB_ADP_GetVdpIntMask     = HIFB_ADP_GetVdpIntMask;
    ops->OPTM_GFX_DECMP_Open        = OPTM_GFX_DECMP_Open;
    ops->OPTM_GFX_DECMP_Close       = OPTM_GFX_DECMP_Close;
#endif

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    ops->OPTM_GfxSetTriDimMode      = OPTM_GfxSetTriDimMode;
    ops->OPTM_GfxSetTriDimAddr      = OPTM_GfxSetTriDimAddr;
    ops->OPTM_GFX_SetStereoDepth    = OPTM_GFX_SetStereoDepth;
#endif
#ifndef HI_BUILD_IN_BOOT
    ops->OPTM_GFX_ClearLogoOsd      = OPTM_GFX_ClearLogoOsd;
    ops->OPTM_GfxSetGpDeflicker     = OPTM_GfxSetGpDeflicker;
#endif
    ops->OPTM_GFX_GetHaltDispStatus = OPTM_GFX_GetHaltDispStatus;
    ops->HIFB_ADP_GetIsGfxWorkAtWbc = HIFB_ADP_GetIsGfxWorkAtWbc;
}
