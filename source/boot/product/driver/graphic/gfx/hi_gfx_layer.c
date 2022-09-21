/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_layer.c
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : show
                          CNcomment:显示处理CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                     sdk                         Created file
******************************************************************************/


/************************** add include here**************************************/
#include "hi_gfx_show.h"
#include "hi_gfx_layer.h"
#include "hi_gfx_surface.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_blit.h"
#include "hi_gfx_decode.h"
#include "hi_gfx_mem.h"
#include "hi_gfx_sys.h"

#ifdef CONFIG_GFX_SUPPORT_VO_4K
#include "drv_com_logo.h"
#endif

#include "drv_hifb_adp.h"
#include "drv_hifb_wbc.h"

#include "hi_drv_disp.h"
#include "drv_disp_ext.h"
/************************** Macro Definition     *********************************/

#define WBC_TC_WIDTH 720

/************************** Structure Definition *********************************/

typedef enum hiFB_COLOR_FMT_E
{
    HI_FB_FMT_RGB565 = 0,
    HI_FB_FMT_RGB888,        /**<  RGB888 24bpp */

    HI_FB_FMT_KRGB444,       /**<  RGB444 16bpp */
    HI_FB_FMT_KRGB555,       /**<  RGB555 16bpp */
    HI_FB_FMT_KRGB888,       /**<  RGB888 32bpp */

    HI_FB_FMT_ARGB4444,      /**< ARGB4444      */
    HI_FB_FMT_ARGB1555,      /**< ARGB1555      */
    HI_FB_FMT_ARGB8888,      /**< ARGB8888      */
    HI_FB_FMT_ARGB8565,      /**< ARGB8565      */

    HI_FB_FMT_RGBA4444,      /**< ARGB4444      */
    HI_FB_FMT_RGBA5551,      /**< RGBA5551      */
    HI_FB_FMT_RGBA5658,      /**< RGBA5658      */
    HI_FB_FMT_RGBA8888,      /**< RGBA8888      */

    HI_FB_FMT_BGR565,        /**< BGR565        */
    HI_FB_FMT_BGR888,        /**< BGR888        */
    HI_FB_FMT_ABGR4444,      /**< ABGR4444      */
    HI_FB_FMT_ABGR1555,      /**< ABGR1555      */
    HI_FB_FMT_ABGR8888,      /**< ABGR8888      */
    HI_FB_FMT_ABGR8565,      /**< ABGR8565      */
    HI_FB_FMT_KBGR444,       /**< BGR444 16bpp  */
    HI_FB_FMT_KBGR555,       /**< BGR555 16bpp  */
    HI_FB_FMT_KBGR888,       /**< BGR888 32bpp  */

    HI_FB_FMT_1BPP,          /**<  clut1        */
    HI_FB_FMT_2BPP,          /**<  clut2        */
    HI_FB_FMT_4BPP,          /**<  clut4        */
    HI_FB_FMT_8BPP,          /**< clut8         */
    HI_FB_FMT_ACLUT44,       /**< AClUT44       */
    HI_FB_FMT_ACLUT88,       /**< ACLUT88       */
    HI_FB_FMT_PUYVY,         /**< UYVY          */
    HI_FB_FMT_PYUYV,         /**< YUYV          */
    HI_FB_FMT_PYVYU,         /**< YVYU          */
    HI_FB_FMT_YUV888,        /**< YUV888        */
    HI_FB_FMT_AYUV8888,      /**< AYUV8888      */
    HI_FB_FMT_YUVA8888,      /**< YUVA8888      */
    HI_FB_FMT_BUTT
}HI_FB_COLOR_FMT_E;


/************************** Global Variable declaration **************************/
static HI_GFX_DISPLAY_INFO_S gs_stDisplayInfo[HI_GFX_LAYER_MAXCOUNT];


/************************** Api declaration **************************************/
#ifdef CONFIG_GFX_SUPPORT_VO_4K
static HI_S32 BOOT_GFX_DisplayLogoWithVo(HI_BOOL bDispSd, HI_HANDLE DecSurface);
#endif

static HI_S32 BOOT_GFX_DisplayLogoWithLayer(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_U32 LayerId, HI_HANDLE DecSurface);


static HI_S32 GFX_CreateLayer(HI_GFX_LAYER_ID_E enLayerID, HI_BOOL Support4KLogo, HI_GFX_PF_E enPixelFormat, HI_HANDLE *pLayerSurface);
static HI_S32 GfxOpenLayer(HI_LOGO_SURFACE_S *pstGfxSurface, HI_BOOL Support4KLogo);
static HI_S32 GfxLayerIdToGfxId(HI_GFX_LAYER_ID_E eLayerID);
static HI_S32 GfxLayerIdToGpId(HI_GFX_LAYER_ID_E eLayerID);
static HI_S32 GfxGetDisplayInfo(HI_LOGO_SURFACE_S *pstSurface,HI_GFX_DISPLAY_INFO_S *pDisplayInfo, HI_BOOL Support4KLogo);
static HI_U32 GfxParaAlign(HI_U32 x, HI_U32 a);
static HI_VOID GfxLayerToHifbFmt(HI_GFX_PF_E SrcFmt,HI_FB_COLOR_FMT_E *DstFmt);

static HI_VOID GfxGetLayerInfo(HI_LOGO_SURFACE_S *pstGfxSurface);
static HI_S32 GFX_DestroyLayer(HI_HANDLE hLayerSurface);
static HI_S32 GFX_RefreshLayer(HI_HANDLE hLayerSurface, HI_BOOL Support4KLogo);


HI_VOID GfxWinReviseOutRect(const HI_RECT_S *tmp_virtscreen,             \
                                     const HI_DRV_DISP_OFFSET_S *stOffsetInfo,    \
                                     const HI_RECT_S *stFmtResolution,            \
                                     const HI_RECT_S *stPixelFmtResolution,       \
                                     HI_RECT_S *stToBeRevisedRect,                \
                                     HI_RECT_S *stRevisedRect);

/************************** API realization **************************************/

/*****************************************************************************
* func	       :  HI_BOOT_GFX_DisplayWithLayerOrVo
* description	:  CNcomment: 使用图形层或者视频层显示CNend\n
*para[in]        : pInputBaseLogoInfo
*para[in]        : DecSurface
* retval		:  HI_SUCCESS
                         HI_FAILURE
* others:		:  NA
*****************************************************************************/
HI_S32 HI_BOOT_GFX_DisplayWithLayerOrVo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_HANDLE DecSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 LayerId = 0;
#ifdef CONFIG_GFX_SUPPORT_VO_4K
    HI_LOGO_SURFACE_S *pstSrcSurface = (HI_LOGO_SURFACE_S *)DecSurface;
#endif

    CHECK_POINT_NULL(pInputBaseLogoInfo);

#ifdef CONFIG_GFX_SUPPORT_VO_4K
    CHECK_POINT_NULL(pstSrcSurface);
    if (HI_TRUE == pstSrcSurface->bVoDispSupport)
    {
        return BOOT_GFX_DisplayLogoWithVo(pInputBaseLogoInfo->DispToSD, DecSurface);
    }
#endif

    LayerId = HI_GFX_LAYER_HD_0;
    Ret = BOOT_GFX_DisplayLogoWithLayer(pInputBaseLogoInfo, LayerId, DecSurface);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_Log();
       return HI_FAILURE;
    }

    if (HI_TRUE != pInputBaseLogoInfo->DispToSD)
    {
        return HI_SUCCESS;
    }

    LayerId = HI_GFX_LAYER_SD_0;
    return BOOT_GFX_DisplayLogoWithLayer(pInputBaseLogoInfo, LayerId, DecSurface);
}


#ifdef CONFIG_GFX_SUPPORT_VO_4K
static HI_S32 BOOT_GFX_DisplayLogoWithVo(HI_BOOL bDispSd, HI_HANDLE DecSurface)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_VIDEO_LOGO_INFO LocalLogoInfo;
     HI_LOGO_SURFACE_S *pstSrcSurface = (HI_LOGO_SURFACE_S *)DecSurface;
     CHECK_POINT_NULL(pstSrcSurface);

     HI_GFX_Memset(&LocalLogoInfo,0x0,sizeof(LocalLogoInfo));
     LocalLogoInfo.eDispChannelId  = HI_UNF_DISPLAY1;
     LocalLogoInfo.bWbcIso         = (HI_TRUE == bDispSd) ? (HI_FALSE) : (HI_TRUE);
     LocalLogoInfo.ePixelFmt       = HI_DRV_PIX_FMT_NV21;

     LocalLogoInfo.u32LogoWidth    = pstSrcSurface->u32Width[0];
     LocalLogoInfo.u32LogoHeight   = pstSrcSurface->u32Height[0];

     LocalLogoInfo.u32LogoYStride  = pstSrcSurface->u32Stride[0];
     LocalLogoInfo.u32LogoCbStride = pstSrcSurface->u32Stride[1];
     LocalLogoInfo.u32LogoCrStride = pstSrcSurface->u32Stride[2];

     LocalLogoInfo.u32LogoYAddr    = (HI_U32)pstSrcSurface->pPhyAddr[0];
     LocalLogoInfo.u32LogoCbAddr   = (HI_U32)pstSrcSurface->pPhyAddr[1];
     LocalLogoInfo.u32LogoCrAddr   = (HI_U32)pstSrcSurface->pPhyAddr[2];

     Ret = HI_UBOOT_LOGO_CreateLayer(&LocalLogoInfo);
     if (HI_SUCCESS != Ret)
     {
        HI_GFX_Log();
        return HI_FAILURE;
     }

#if 0
     HI_GFX_Print("\n======================================================\n");
     switch (pstSrcSurface->enPixelFormat)
     {
         case HI_GFX_PF_YUV400:
            HI_GFX_Print("output jpeg pix format        = yuv400\n");
            break;
         case HI_GFX_PF_YUV420:
            HI_GFX_Print("output jpeg pix format        = yuv420\n");
            break;
         case HI_GFX_PF_YUV422_12:
            HI_GFX_Print("output jpeg pix format        = yuv422_12\n");
            break;
         case HI_GFX_PF_YUV422_21:
            HI_GFX_Print("output jpeg pix format        = yuv422_21\n");
            break;
         default:
            HI_GFX_Print("output jpeg pix format        = yuv444\n");
            break;
     }
     HI_GFX_Print("LocalLogoInfo.eDispChannelId  = %d\n",   LocalLogoInfo.eDispChannelId);
     HI_GFX_Print("LocalLogoInfo.bWbcIso         = %d\n",   LocalLogoInfo.bWbcIso);
     HI_GFX_Print("LocalLogoInfo.ePixelFmt       = %d\n",   LocalLogoInfo.ePixelFmt);
     HI_GFX_Print("LocalLogoInfo.u32LogoWidth    = %d\n",   LocalLogoInfo.u32LogoWidth);
     HI_GFX_Print("LocalLogoInfo.u32LogoHeight   = %d\n",   LocalLogoInfo.u32LogoHeight);
     HI_GFX_Print("LocalLogoInfo.u32LogoYStride  = %d\n",   LocalLogoInfo.u32LogoYStride);
     HI_GFX_Print("LocalLogoInfo.u32LogoCbStride = %d\n",   LocalLogoInfo.u32LogoCbStride);
     HI_GFX_Print("LocalLogoInfo.u32LogoCrStride = %d\n",   LocalLogoInfo.u32LogoCrStride);
     HI_GFX_Print("LocalLogoInfo.u32LogoYAddr    = 0x%x\n", LocalLogoInfo.u32LogoYAddr);
     HI_GFX_Print("LocalLogoInfo.u32LogoCbAddr   = 0x%x\n", LocalLogoInfo.u32LogoCbAddr);
     HI_GFX_Print("LocalLogoInfo.u32LogoCrAddr   = 0x%x\n", LocalLogoInfo.u32LogoCrAddr);
     HI_GFX_Print("======================================================\n");
#endif

     return HI_SUCCESS;
}
#endif

static HI_S32 BOOT_GFX_DisplayLogoWithLayer(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_U32 LayerId, HI_HANDLE DecSurface)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_U32 DispChanel = 0;
     HI_BOOL GfxSupport4k = HI_FALSE;
     HI_HANDLE LayerSurface = HI_GFX_INVALID_HANDLE;
     HI_GFX_BLTOPT_S stBltOpt;

     if (HI_GFX_LAYER_HD_0 == LayerId)
     {
         DispChanel = CONFIG_GFX_DISP_LOGO_HD;
     }
     else
     {
         DispChanel = CONFIG_GFX_DISP_LOGO_SD;
     }

     HI_BOOT_GFX_IsSupport4KLOGO(DecSurface, &GfxSupport4k);

     Ret = GFX_CreateLayer(LayerId, GfxSupport4k, pInputBaseLogoInfo->DispColorFmt[DispChanel], &LayerSurface);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_Log();
         return HI_FAILURE;
     }

     Ret = HI_BOOT_GFX2D_Init();
     if (HI_SUCCESS != Ret)
     {
        HI_GFX_Log();
        goto ERR_EXIT_ONE;
     }

     Ret = HI_BOOT_GFX2D_FillRect(LayerSurface, NULL, 0xffaabbcc, HI_GFX_COMPOPT_NONE);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_Log();
         goto ERR_EXIT_ONE;
     }

     HI_GFX_Memset(&stBltOpt, 0, sizeof(HI_GFX_BLTOPT_S));
     stBltOpt.EnableScale = HI_TRUE;
     Ret = HI_BOOT_GFX2D_Blit(DecSurface, NULL, LayerSurface, NULL, &stBltOpt);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_Log();
         goto ERR_EXIT_ONE;
     }

     Ret = GFX_RefreshLayer(LayerSurface, GfxSupport4k);
     if (HI_SUCCESS != Ret){
         HI_GFX_Log();
         goto ERR_EXIT_ONE;
     }

     if (HI_GFX_INVALID_HANDLE != LayerSurface)
     {
        HI_GFX_Free((HI_CHAR*)LayerSurface);
     }

     return HI_SUCCESS;

ERR_EXIT_ONE:

     if (HI_GFX_INVALID_HANDLE != LayerSurface)
     {
        GFX_DestroyLayer(LayerSurface);
        HI_GFX_Free((HI_CHAR*)LayerSurface);
     }

     HI_GFX_Log();

     return HI_FAILURE;
}



static HI_S32 GFX_CreateLayer(HI_GFX_LAYER_ID_E enLayerID, HI_BOOL Support4KLogo, HI_GFX_PF_E enPixelFormat, HI_HANDLE *pLayerSurface)
{

    HI_S32 Ret = HI_SUCCESS;
    HI_HANDLE hSurface = 0;
    HI_LOGO_SURFACE_S *pstSurface = NULL;

    if (HI_GFX_LAYER_HD_0 == enLayerID)
    {
        hSurface = (HI_HANDLE)HI_GFX_Malloc(sizeof(HI_LOGO_SURFACE_S),"hd-surface-handle");
    }
    else
    {
        hSurface = (HI_HANDLE)HI_GFX_Malloc(sizeof(HI_LOGO_SURFACE_S),"sd-surface-handle");
    }

    if (0 == hSurface)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }
    HI_GFX_Memset((HI_VOID*)hSurface,0x0,sizeof(HI_LOGO_SURFACE_S));

    *pLayerSurface = hSurface;

    pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    pstSurface->enLayerID = enLayerID;
    pstSurface->enPixelFormat = enPixelFormat;

    if (HI_GFX_LAYER_HD_0 == enLayerID)
    {
         Ret = GfxOpenLayer(pstSurface,Support4KLogo);
    }
    else
    {
         GfxGetLayerInfo(pstSurface);
    }

    if (HI_SUCCESS != Ret)
    {
         HI_GFX_Free((HI_CHAR*)pstSurface);
         return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static HI_S32 GfxOpenLayer(HI_LOGO_SURFACE_S *pstGfxSurface, HI_BOOL Support4KLogo)
{

    HI_S32 Ret = HI_SUCCESS;
    HI_S32 s32DataId = 0;
    HI_S32 s32GPId   = 0;
    HI_FB_COLOR_FMT_E enLayerFmt;
    HI_DISP_DISPLAY_INFO_S stInfo = {0};
    HI_GFX_DISPLAY_INFO_S *pDisplayInfo = NULL;

    CHECK_POINT_NULL(pstGfxSurface);

    s32DataId = GfxLayerIdToGfxId(pstGfxSurface->enLayerID);
    if (HI_FAILURE == s32DataId)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    s32GPId  = GfxLayerIdToGpId(pstGfxSurface->enLayerID);
    if (HI_FAILURE == s32GPId)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    if (s32DataId >= HI_GFX_LAYER_MAXCOUNT)
    {
       HI_GFX_Log();
       return HI_FAILURE;
    }
    pDisplayInfo = gs_stDisplayInfo + s32DataId;

    Ret = GfxGetDisplayInfo(pstGfxSurface,pDisplayInfo, Support4KLogo);
    if (Ret != HI_SUCCESS)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    GfxLayerToHifbFmt(pstGfxSurface->enPixelFormat, &enLayerFmt);

    OPTM_GfxInit            ();
    OPTM_GfxOpenLayer       (s32DataId);
    OPTM_GfxSetLayerDataFmt (s32DataId,  (enLayerFmt));
    OPTM_GfxSetLayerStride  (s32DataId,  (pDisplayInfo->u32Stride));
    OPTM_GfxSetLayerAddr    (s32DataId,  (pDisplayInfo->u32ScreenAddr));
    OPTM_GfxSetLayerAlpha   (s32DataId,  (HIFB_ALPHA_S*)(&(pDisplayInfo->stAlpha)));
    OPTM_GfxSetLayerRect    (s32DataId,  (const HIFB_RECT*)(&(pDisplayInfo->stInRect)));
    OPTM_GfxSetGpRect       (s32GPId,    (const HIFB_RECT*)(&(pDisplayInfo->stInRect)));
    OPTM_GfxSetDispFMTSize  (s32GPId,    (const HI_RECT_S*)(&(pDisplayInfo->stOutRect)));
    OPTM_GpInitFromDisp     (s32GPId, Support4KLogo);

    if (HI_FALSE == HIFB_ADP_GetIsGfxWorkAtWbc())
    {
       return HI_SUCCESS;
    }

    HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &stInfo);
    if (stInfo.stFmtResolution.s32Width > WBC_TC_WIDTH)
    {
        OPTM_GFX_SetTCFlag(HI_TRUE);
    }
    HIFB_WBC_InitLayer     (HI_GFX_LAYER_SD_0);
    OPTM_GpInitFromDisp    (OPTM_GFX_GP_1, Support4KLogo);

    return HI_SUCCESS;
}

static HI_S32 GfxLayerIdToGfxId(HI_GFX_LAYER_ID_E eLayerID)
{
    if (HI_GFX_LAYER_HD_0 == eLayerID)
    {
        return 0;
    }
    else if(HI_GFX_LAYER_HD_1 == eLayerID)
    {
        return 1;
    }
    else if(HI_GFX_LAYER_HD_2 == eLayerID)
    {
        return 2;
    }
    else if(HI_GFX_LAYER_HD_3 == eLayerID)
    {
        return 3;
    }
    else if(HI_GFX_LAYER_SD_0 == eLayerID)
    {
        return 4;
    }
    else if(HI_GFX_LAYER_SD_1 == eLayerID)
    {
        return 5;
    }
    else
    {
        return HI_FAILURE;
    }
}


static HI_S32 GfxLayerIdToGpId(HI_GFX_LAYER_ID_E eLayerID)
{
    if (eLayerID <= HI_GFX_LAYER_HD_3)
    {
        return 0;
    }
    else if (eLayerID <= HI_GFX_LAYER_SD_1)
    {
        return 1;
    }
    else
    {
        return HI_FAILURE;
    }
}


static HI_S32 GfxGetDisplayInfo(HI_LOGO_SURFACE_S *pstSurface,HI_GFX_DISPLAY_INFO_S *pDisplayInfo, HI_BOOL Support4KLogo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32BufferSize = 0;
    HI_DISP_DISPLAY_INFO_S pstInfo = {0};
    MMZ_BUFFER_S stDisplayBuf;
    HI_RECT stOutRect = {0};

    if (pstSurface->enLayerID <= HI_GFX_LAYER_HD_3)
    {
        HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_1, &pstInfo);
    }
    else
    {
        HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &pstInfo);
    }

    GfxWinReviseOutRect(&pstInfo.stVirtaulScreen,      \
                        &pstInfo.stOffsetInfo,         \
                        &pstInfo.stFmtResolution,      \
                        &pstInfo.stPixelFmtResolution, \
                        &pstInfo.stVirtaulScreen,      \
                        (HI_RECT_S*)(&stOutRect));

    HI_GFX_Memset(pDisplayInfo, 0, sizeof(HI_GFX_DISPLAY_INFO_S));

    pDisplayInfo->stAlpha.bAlphaEnable  = HI_TRUE;
    pDisplayInfo->stAlpha.bAlphaChannel = HI_FALSE;
    pDisplayInfo->stAlpha.u8Alpha0      = 0x00;
    pDisplayInfo->stAlpha.u8Alpha1      = 0xff;
    pDisplayInfo->stAlpha.u8GlobalAlpha = 0xff;

    pDisplayInfo->stInRect.x  = pstInfo.stVirtaulScreen.s32X;
    pDisplayInfo->stInRect.y  = pstInfo.stVirtaulScreen.s32Y;
    pDisplayInfo->stInRect.w  = pstInfo.stVirtaulScreen.s32Width;
    pDisplayInfo->stInRect.h  = pstInfo.stVirtaulScreen.s32Height;
    pDisplayInfo->stOutRect.x  = stOutRect.x;
    pDisplayInfo->stOutRect.y  = stOutRect.y;
    pDisplayInfo->stOutRect.w  = stOutRect.w;
    pDisplayInfo->stOutRect.h  = stOutRect.h;
    pstSurface->stRect.x  = pDisplayInfo->stInRect.x;
    pstSurface->stRect.y  = pDisplayInfo->stInRect.y;
    pstSurface->stRect.w  = pDisplayInfo->stInRect.w;
    pstSurface->stRect.h  = pDisplayInfo->stInRect.h;

#if 0
    HI_GFX_Print("\n===========================================================\n");
    HI_GFX_Print("========%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
    HI_GFX_Print("disp in rect  [%d %d %d %d]\n",pDisplayInfo->stInRect.x,pDisplayInfo->stInRect.y,pDisplayInfo->stInRect.w,pDisplayInfo->stInRect.h);
    HI_GFX_Print("disp out rect [%d %d %d %d]\n",pDisplayInfo->stOutRect.x,pDisplayInfo->stOutRect.y,pDisplayInfo->stOutRect.w,pDisplayInfo->stOutRect.h);
    HI_GFX_Print("this outrect should equal to logo to app's src rect\n");
    HI_GFX_Print("logo virtual screen and offset should equal to app's\n");
    HI_GFX_Print("===========================================================\n");
#endif
    if (HI_TRUE == Support4KLogo)
    {
        pDisplayInfo->stInRect.x  = 0;
        pDisplayInfo->stInRect.y  = 0;
        pDisplayInfo->stInRect.w  = pstInfo.stFmtResolution.s32Width;
        pDisplayInfo->stInRect.h  = pstInfo.stFmtResolution.s32Height;
        pDisplayInfo->stOutRect.x = pDisplayInfo->stInRect.x;
        pDisplayInfo->stOutRect.y = pDisplayInfo->stInRect.y;
        pDisplayInfo->stOutRect.w = pDisplayInfo->stInRect.w;
        pDisplayInfo->stOutRect.h = pDisplayInfo->stInRect.h;
        pstSurface->stRect.x  = stOutRect.x;
        pstSurface->stRect.y  = stOutRect.y;
        pstSurface->stRect.w  = stOutRect.w;
        pstSurface->stRect.h  = stOutRect.h;
#if 0
        HI_GFX_Print("\n===========================================================\n");
        HI_GFX_Print("========%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
        HI_GFX_Print("=======let input rect equal to out rect, gp0 and gp1 not need zme\n");
        HI_GFX_Print("disp in rect  [%d %d %d %d]\n",pDisplayInfo->stInRect.x,pDisplayInfo->stInRect.y,pDisplayInfo->stInRect.w,pDisplayInfo->stInRect.h);
        HI_GFX_Print("disp out rect [%d %d %d %d]\n",pDisplayInfo->stOutRect.x,pDisplayInfo->stOutRect.y,pDisplayInfo->stOutRect.w,pDisplayInfo->stOutRect.h);
        HI_GFX_Print("===========================================================\n");
#endif
    }

    pstSurface->u32Width[0]     = pDisplayInfo->stInRect.w;
    pstSurface->u32Height[0]    = pDisplayInfo->stInRect.h;
    switch (pstSurface->enPixelFormat)
    {
        case HI_GFX_PF_8888:
             pstSurface->u32Stride[0] = (pDisplayInfo->stInRect.w * 4 + 0xf) & 0xfffffff0;
             break;
        case HI_GFX_PF_0888:
             pstSurface->u32Stride[0] = (pDisplayInfo->stInRect.w * 3 + 0xf) & 0xfffffff0;
             break;
        case HI_GFX_PF_565:
        case HI_GFX_PF_1555:
             pstSurface->u32Stride[0] = (pDisplayInfo->stInRect.w * 2 + 0xf) & 0xfffffff0;
             break;
        default:
             break;
    }
    u32BufferSize = pstSurface->u32Stride[0] * pDisplayInfo->stInRect.h;

    if (pstSurface->enLayerID <= HI_GFX_LAYER_HD_3)
    {
        Ret = HI_DRV_PDM_AllocReserveMem(DISPLAY_BUFFER_HD, u32BufferSize, &stDisplayBuf.u32StartPhyAddr);
    }
    else
    {
        Ret = HI_DRV_PDM_AllocReserveMem(DISPLAY_BUFFER_SD, u32BufferSize, &stDisplayBuf.u32StartPhyAddr);
    }

    pstSurface->pPhyAddr[0] = (HI_CHAR*)stDisplayBuf.u32StartPhyAddr;
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    pDisplayInfo->u32Stride     = pstSurface->u32Stride[0];
    pDisplayInfo->u32ScreenAddr = stDisplayBuf.u32StartPhyAddr;

    return HI_SUCCESS;
}

HI_VOID GfxWinReviseOutRect(const HI_RECT_S *tmp_virtscreen,          \
                                     const HI_DRV_DISP_OFFSET_S *stOffsetInfo, \
                                     const HI_RECT_S *stFmtResolution,         \
                                     const HI_RECT_S *stPixelFmtResolution,    \
                                     HI_RECT_S *stToBeRevisedRect,             \
                                     HI_RECT_S *stRevisedRect)
{
    HI_U32 width_ratio   = 0;
    HI_U32 height_ratio  = 0;
    HI_U32 zmeDestWidth  = 0;
    HI_U32 zmeDestHeight = 0;
    HI_DRV_DISP_OFFSET_S tmp_offsetInfo;

    CHECK_POINT_NULL_UNRETURN(tmp_virtscreen);
    CHECK_POINT_NULL_UNRETURN(stOffsetInfo);
    CHECK_POINT_NULL_UNRETURN(stFmtResolution);
    CHECK_POINT_NULL_UNRETURN(stPixelFmtResolution);
    CHECK_POINT_NULL_UNRETURN(stToBeRevisedRect);
    CHECK_POINT_NULL_UNRETURN(stRevisedRect);

    tmp_offsetInfo = *stOffsetInfo;

    if ( (stFmtResolution->s32Width * 2) == stPixelFmtResolution->s32Width)
    {
        tmp_offsetInfo.u32Left  *= 2;
        tmp_offsetInfo.u32Right *= 2;
    }

    zmeDestWidth = (stPixelFmtResolution->s32Width - tmp_offsetInfo.u32Left - tmp_offsetInfo.u32Right);
    zmeDestHeight = (stPixelFmtResolution->s32Height - tmp_offsetInfo.u32Top - tmp_offsetInfo.u32Bottom);

    if ((0 == tmp_virtscreen->s32Width) || (0 == tmp_virtscreen->s32Height))
    {
       return;
    }
    width_ratio  = zmeDestWidth  * 100 /(tmp_virtscreen->s32Width);
    height_ratio = zmeDestHeight * 100 /(tmp_virtscreen->s32Height);

    if (tmp_virtscreen->s32Width != stToBeRevisedRect->s32Width)
    {
        stRevisedRect->s32Width = (stToBeRevisedRect->s32Width * width_ratio) / 100;
    }
    else
    {
        stRevisedRect->s32Width = zmeDestWidth;
    }

    if (tmp_virtscreen->s32Height != stToBeRevisedRect->s32Height)
    {
        stRevisedRect->s32Height = (stToBeRevisedRect->s32Height * height_ratio) / 100;
    }
    else
    {
        stRevisedRect->s32Height = zmeDestHeight;
    }


    stRevisedRect->s32X = (stToBeRevisedRect->s32X * width_ratio) /100 + tmp_offsetInfo.u32Left;
    stRevisedRect->s32Y = (stToBeRevisedRect->s32Y  * height_ratio) /100 + tmp_offsetInfo.u32Top;

    stRevisedRect->s32X      = GfxParaAlign(stRevisedRect->s32X, 2);
    stRevisedRect->s32Y      = GfxParaAlign(stRevisedRect->s32Y , 2);
    stRevisedRect->s32Width  = GfxParaAlign(stRevisedRect->s32Width, 2);
    stRevisedRect->s32Height = GfxParaAlign(stRevisedRect->s32Height, 2);

    return;
}


static HI_U32 GfxParaAlign(HI_U32 x, HI_U32 a)
{
    if (!a)
    {
        return x;
    }
    else
    {
        return ( (( x + (a-1) ) / a ) * a);
    }
}

static HI_VOID GfxLayerToHifbFmt(HI_GFX_PF_E SrcFmt,HI_FB_COLOR_FMT_E *DstFmt)
{
    switch(SrcFmt)
    {
        case HI_GFX_PF_1555:
            *DstFmt = HI_FB_FMT_ARGB1555;
            break;
        case HI_GFX_PF_565:
            *DstFmt = HI_FB_FMT_RGB565;
            break;
        case HI_GFX_PF_8888:
            *DstFmt = HI_FB_FMT_ARGB8888;
            break;
        case HI_GFX_PF_0888:
            *DstFmt = HI_FB_FMT_RGB888;
            break;
        default:
            *DstFmt = HI_FB_FMT_ARGB8888;
            break;
    }
    return;
}

static HI_VOID GfxGetLayerInfo(HI_LOGO_SURFACE_S *pstGfxSurface)
{
    HIFB_WBC_DATA_S stWbcInfo;
    HI_DISP_DISPLAY_INFO_S pstInfo;
    HI_RECT stOutRect = {0};

    HI_GFX_Memset(&stWbcInfo, 0x0, sizeof(HIFB_WBC_DATA_S));
    HI_GFX_Memset(&pstInfo, 0x0, sizeof(HI_DISP_DISPLAY_INFO_S));

    HIFB_WBC_BOOT_GetWbcInfo  (&stWbcInfo);

    HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &pstInfo);
    GfxWinReviseOutRect(&pstInfo.stVirtaulScreen,      \
                        &pstInfo.stOffsetInfo,         \
                        &pstInfo.stFmtResolution,      \
                        &pstInfo.stPixelFmtResolution, \
                        &pstInfo.stVirtaulScreen,      \
                        (HI_RECT_S*)(&stOutRect));

    pstGfxSurface->stRect.x     = 0;
    pstGfxSurface->stRect.y     = 0;
    pstGfxSurface->stRect.w     = stOutRect.w;
    pstGfxSurface->stRect.h     = stOutRect.h;
    pstGfxSurface->u32Width[0]  = stOutRect.w;
    pstGfxSurface->u32Height[0] = stOutRect.h;

    pstGfxSurface->u32Stride[0] = stWbcInfo.u32Stride;
    pstGfxSurface->pPhyAddr[0]  = (HI_CHAR*)stWbcInfo.u32ReadBufAddr;
#if 0
    HI_GFX_Print("\n===========================================================\n");
    HI_GFX_Print("========%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
    HI_GFX_Print("sd layer rect [%d %d %d %d]\n",pstGfxSurface->stRect.x,pstGfxSurface->stRect.y,pstGfxSurface->stRect.w,pstGfxSurface->stRect.h);
    HI_GFX_Print("sd layer surface [%d %d]\n",   pstGfxSurface->u32Width[0],pstGfxSurface->u32Height[0]);
    HI_GFX_Print("sd layer surface stride %d\n", pstGfxSurface->u32Stride[0]);
    HI_GFX_Print("sd layer surface ddr 0x%x\n",  stWbcInfo.u32ReadBufAddr);
    HI_GFX_Print("this outrect should equal to logo to app's src rect\n");
    HI_GFX_Print("logo virtual screen and offset should equal to app's\n");
    HI_GFX_Print("===========================================================\n");
#endif
    return;
}

static HI_S32 GFX_DestroyLayer(HI_HANDLE hLayerSurface)
{
    HI_S32 DataId = 0;
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hLayerSurface;

    CHECK_POINT_NULL(pstSurface);

    DataId = GfxLayerIdToGfxId(pstSurface->enLayerID);
    if (HI_FAILURE == DataId)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    OPTM_GfxCloseLayer(DataId);

    return HI_SUCCESS;
}

static HI_S32 GFX_RefreshLayer(HI_HANDLE hLayerSurface, HI_BOOL Support4KLogo)
{
    HI_S32 DataId = 0;
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hLayerSurface;

    CHECK_POINT_NULL(pstSurface);

    DataId = GfxLayerIdToGfxId(pstSurface->enLayerID);
    if (HI_FAILURE == DataId)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    OPTM_GfxSetEnable  (DataId, HI_TRUE);
    OPTM_GfxUpLayerReg (DataId);

    if (HI_FALSE == HIFB_ADP_GetIsGfxWorkAtWbc())
    {
       return HI_SUCCESS;
    }

    HIFB_WBC_BOOT_ReFresh   (Support4KLogo);
    OPTM_GfxUpLayerReg      (HI_GFX_LAYER_SD_0);

    return HI_SUCCESS;
}
