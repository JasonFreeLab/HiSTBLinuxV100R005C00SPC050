/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_csc.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : csc yuv to xrgb
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                 sdk                       Created file
******************************************************************************/

/****************************  add include here     *********************************/
#ifndef CONFIG_JPEG_CSC_DISABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hi_jpeg_config.h"
#include "hi_gfx_sys.h"

#if defined(CHIP_TYPE_hi3712) || defined(CHIP_TYPE_hi3716m)
#include  "hi_tde_ioctl.h"
#else
#include  "hi_drv_tde.h"
#endif

/***************************** Macro Definition ***********************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE
#define DEC_TINIT()   struct timeval tv_start, tv_end; unsigned int time_cost,line_start
#define DEC_TSTART()  gettimeofday(&tv_start, NULL);line_start = __LINE__
#define DEC_TEND()    gettimeofday(&tv_end, NULL); \
                      time_cost = ((tv_end.tv_usec - tv_start.tv_usec) + (tv_end.tv_sec - tv_start.tv_sec)*1000000); \
                      GFX_Printf("=============================================================================\n"); \
                      GFX_Printf("FROM LINE: %d TO LINE: %d COST: %d us\n",line_start, __LINE__, time_cost);  \
                      GFX_Printf("=============================================================================\n")
#endif
/***************************** Structure Definition ********************************/

/***************************** Global Variable declaration ***************************/

/***************************** API forward declarations ****************************/

/***************************** API realization ***********************************/
#ifdef JPEG_HDEC_START_CSC
static TDE2_COLOR_FMT_E JPEG_HDEC_GetXRGB8888(j_decompress_ptr cinfo)
{
    switch (cinfo->out_color_space)
    {
        case JCS_EXT_XBGR:
        case JCS_EXT_ABGR:
            return TDE2_COLOR_FMT_RGBA8888;
        case JCS_EXT_XRGB:
        case JCS_EXT_ARGB:
            return TDE2_COLOR_FMT_BGRA8888;
        case JCS_RGBA_8888:
        case JCS_EXT_RGBX:
        case JCS_EXT_RGBA:
            return TDE2_COLOR_FMT_ABGR8888;
        case JCS_EXT_BGRX:
        case JCS_EXT_BGRA:
            return TDE2_COLOR_FMT_ARGB8888;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static TDE2_COLOR_FMT_E JPEG_HDEC_GetXRGB1555(j_decompress_ptr cinfo)
{
    switch (cinfo->out_color_space)
    {
        case JCS_ARGB_1555:
            return TDE2_COLOR_FMT_BGRA1555;
        case JCS_ABGR_1555:
            return TDE2_COLOR_FMT_RGBA1555;
        case JCS_BGRA_5551:
            return TDE2_COLOR_FMT_ARGB1555;
        case JCS_RGBA_5551:
            return TDE2_COLOR_FMT_ABGR1555;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static TDE2_COLOR_FMT_E JPEG_HDEC_GetRGB888(j_decompress_ptr cinfo)
{
    switch (cinfo->out_color_space)
    {
        case JCS_RGB:
        case JCS_EXT_RGB:
            return TDE2_COLOR_FMT_BGR888;
        case JCS_BGR:
        case JCS_EXT_BGR:
            return TDE2_COLOR_FMT_RGB888;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static TDE2_COLOR_FMT_E JPEG_HDEC_GetRGB565(j_decompress_ptr cinfo)
{
    switch (cinfo->out_color_space)
    {
        case JCS_RGB565:
        case JCS_RGB_565:
            return TDE2_COLOR_FMT_RGB565;
        case JCS_BGR565:
            return TDE2_COLOR_FMT_BGR565;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static TDE2_COLOR_FMT_E JPEG_HDEC_ConvertJpegFmtToTdeFmt(j_decompress_ptr cinfo)
{
    TDE2_COLOR_FMT_E eCSCFmt = TDE2_COLOR_FMT_BUTT;

    eCSCFmt = JPEG_HDEC_GetXRGB8888(cinfo);
    if (TDE2_COLOR_FMT_BUTT != eCSCFmt)
    {
       return eCSCFmt;
    }

    eCSCFmt = JPEG_HDEC_GetXRGB1555(cinfo);
    if (TDE2_COLOR_FMT_BUTT != eCSCFmt)
    {
       return eCSCFmt;
    }

    eCSCFmt = JPEG_HDEC_GetRGB888(cinfo);
    if (TDE2_COLOR_FMT_BUTT != eCSCFmt)
    {
       return eCSCFmt;
    }

    eCSCFmt = JPEG_HDEC_GetRGB565(cinfo);
    return eCSCFmt;
}

static HI_S32 JPEG_HDEC_CSC_MbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE2_SURFACE_S* pstDst,TDE2_RECT_S  *pstDstRect,TDE2_MBOPT_S* pstMbOpt,HI_S32 CscDev)
{
    TDE_MBBITBLT_CMD_S stMbBlit;

    HI_GFX_Memset(&stMbBlit,0,sizeof(TDE_MBBITBLT_CMD_S));
    stMbBlit.s32Handle = s32Handle;
    HI_GFX_Memcpy(&stMbBlit.stMB, pstMB, sizeof(TDE2_MB_S));
    HI_GFX_Memcpy(&stMbBlit.stMbRect, pstMbRect, sizeof(TDE2_RECT_S));
    HI_GFX_Memcpy(&stMbBlit.stDstRect, pstDstRect, sizeof(TDE2_RECT_S));
    HI_GFX_Memcpy(&stMbBlit.stMbOpt, pstMbOpt, sizeof(TDE2_MBOPT_S));

    stMbBlit.stDst.bAlphaExt1555  = pstDst->bAlphaExt1555;
    stMbBlit.stDst.bAlphaMax255   = pstDst->bAlphaMax255;
    stMbBlit.stDst.bYCbCrClut     = pstDst->bYCbCrClut;
    stMbBlit.stDst.enColorFmt     = pstDst->enColorFmt;
    stMbBlit.stDst.u32ClutPhyAddr = 0;
    stMbBlit.stDst.u32CbCrPhyAddr = pstDst->u32CbCrPhyAddr;
    stMbBlit.stDst.u32CbCrStride  = pstDst->u32CbCrStride;
    stMbBlit.stDst.u32Height      = pstDst->u32Height;
    stMbBlit.stDst.u32PhyAddr     = pstDst->u32PhyAddr;
    stMbBlit.stDst.u32Stride      = pstDst->u32Stride;
    stMbBlit.stDst.u32Width       = pstDst->u32Width;
    stMbBlit.stDst.u8Alpha0       = pstDst->u8Alpha0;
    stMbBlit.stDst.u8Alpha1       = pstDst->u8Alpha1;

    return ioctl(CscDev, TDE_MB_BITBLT, &stMbBlit);
}

static HI_S32 JPEG_HDEC_CSC_BeginJob(HI_S32 CscDev)
{
    TDE_HANDLE Handle = HI_ERR_TDE_INVALID_HANDLE;

    if (ioctl(CscDev, TDE_BEGIN_JOB, &Handle) < 0)
    {
        return HI_ERR_TDE_INVALID_HANDLE;
    }

    return Handle;
}

static HI_S32 JPEG_HDEC_CSC_EndJob(TDE_HANDLE s32Handle, HI_BOOL bBlock, HI_U32 u32TimeOut,HI_S32 CscDev)
{
    HI_S32 Ret = HI_FAILURE;
    TDE_ENDJOB_CMD_S stEndJob;

    stEndJob.s32Handle  = s32Handle;
    stEndJob.bSync      = HI_FALSE;
    stEndJob.bBlock     = bBlock;
    stEndJob.u32TimeOut = u32TimeOut;

    Ret = ioctl(CscDev, TDE_END_JOB, &stEndJob);
    if (HI_ERR_TDE_INTERRUPT == Ret)
    {
       Ret = ioctl(CscDev, TDE_WAITFORDONE, &s32Handle);
    }

    return Ret;
}

static HI_S32 JPEG_HDEC_HardCSC(j_decompress_ptr cinfo)
{
    HI_S32 Ret =  HI_SUCCESS;
    TDE2_MB_S SrcSurface;
    TDE2_SURFACE_S DstSurface;
    TDE2_RECT_S SrcRect,DstRect;
    TDE2_MBOPT_S stMbOpt;
    TDE_HANDLE s32Handle;
//   HI_U32 Row = 0;

    JPEG_API_MODULE_DEFINE_HANDLE();
#ifndef HI_ADVCA_FUNCTION_RELEASE
     //DEC_TINIT();
#endif

    TDE2_MB_COLOR_FMT_E enMbFmt[6] = {
                                       TDE2_MB_COLOR_FMT_JPG_YCbCr400MBP,
                                       TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP,
                                       TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP,
                                       TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP,
                                       TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP,
                                       TDE2_MB_COLOR_FMT_BUTT,
                                     };

    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {
       pJpegHandle->bCSCEnd = HI_TRUE;
       return HI_SUCCESS;
    }

    if ( (HI_TRUE == pJpegHandle->bOutYCbCrSP) || (HI_TRUE == pJpegHandle->bCSCEnd))
    {
       return HI_SUCCESS;
    }

    SrcSurface.u32YPhyAddr    = pJpegHandle->stDecSurface.DecOutPhy[0];
    SrcSurface.u32CbCrPhyAddr = pJpegHandle->stDecSurface.DecOutPhy[1];
    SrcSurface.u32YWidth      = pJpegHandle->stJpegSofInfo.u32YWidth;
    SrcSurface.u32YHeight     = pJpegHandle->stJpegSofInfo.u32YHeight;
    SrcSurface.u32YStride     = pJpegHandle->stJpegSofInfo.u32YStride;
    SrcSurface.u32CbCrStride  = pJpegHandle->stJpegSofInfo.u32CbCrStride;

    if (pJpegHandle->enImageFmt >= (sizeof(enMbFmt) / sizeof(TDE2_MB_COLOR_FMT_E)))
    {
        return HI_FAILURE;
    }
    SrcSurface.enMbFmt = enMbFmt[pJpegHandle->enImageFmt];
#if 0
    JPEG_TRACE("============================================================================\n");
    JPEG_TRACE("SrcSurface.u32YWidth      = %d\n",SrcSurface.u32YWidth);
    JPEG_TRACE("SrcSurface.u32YHeight     = %d\n",SrcSurface.u32YHeight);
    JPEG_TRACE("SrcSurface.u32YStride     = %d\n",SrcSurface.u32YStride);
    JPEG_TRACE("SrcSurface.u32CbCrStride  = %d\n",SrcSurface.u32CbCrStride);
    JPEG_TRACE("============================================================================\n");
#endif

    DstSurface.enColorFmt = JPEG_HDEC_ConvertJpegFmtToTdeFmt(cinfo);
    DstSurface.u32PhyAddr = pJpegHandle->stDecSurface.OutPhy;

    if (HI_TRUE == pJpegHandle->bOutUsrBuf)
    {
       DstSurface.u32Stride = pJpegHandle->stOutSurface.u32OutStride[0];
    }
    else
    {
       DstSurface.u32Stride = pJpegHandle->stJpegSofInfo.DecOutStride;
    }

    DstSurface.u32Width       = (HI_U32)pJpegHandle->stCropRect.w;
    DstSurface.u32Height      = (HI_U32)pJpegHandle->stCropRect.h;
    DstSurface.pu8ClutPhyAddr = NULL;
    DstSurface.bYCbCrClut     = HI_FALSE;
    DstSurface.bAlphaMax255   = HI_TRUE;
    DstSurface.bAlphaExt1555  = HI_TRUE;
    DstSurface.u8Alpha0       = 0;
    DstSurface.u8Alpha1       = 255;
    DstSurface.u32CbCrPhyAddr = 0;
    DstSurface.u32CbCrStride  = 0;

    SrcRect.s32Xpos   = pJpegHandle->stCropRect.x;
    SrcRect.s32Ypos   = pJpegHandle->stCropRect.y;
    SrcRect.u32Width  = (HI_U32)pJpegHandle->stCropRect.w;
    SrcRect.u32Height = (HI_U32)pJpegHandle->stCropRect.h;
    DstRect.s32Xpos   = 0;
    DstRect.s32Ypos   = 0;
    DstRect.u32Width  = (HI_U32)pJpegHandle->stCropRect.w;
    DstRect.u32Height = (HI_U32)pJpegHandle->stCropRect.h;

#if 0
    JPEG_TRACE("============================================================================\n");
    JPEG_TRACE("DstSurface.u32Width  = %d\n",DstSurface.u32Width);
    JPEG_TRACE("DstSurface.u32Height = %d\n",DstSurface.u32Height);
    JPEG_TRACE("DstSurface.u32Stride = %d\n",DstSurface.u32Stride);
    JPEG_TRACE("SrcRect.s32Xpos      = %d\n",SrcRect.s32Xpos);
    JPEG_TRACE("SrcRect.s32Ypos      = %d\n",SrcRect.s32Ypos);
    JPEG_TRACE("SrcRect.u32Width     = %d\n",SrcRect.u32Width);
    JPEG_TRACE("SrcRect.u32Height    = %d\n",SrcRect.u32Height);
    JPEG_TRACE("DstRect.s32Xpos      = %d\n",DstRect.s32Xpos);
    JPEG_TRACE("DstRect.s32Ypos      = %d\n",DstRect.s32Ypos);
    JPEG_TRACE("DstRect.u32Width     = %d\n",DstRect.u32Width);
    JPEG_TRACE("DstRect.u32Height    = %d\n",DstRect.u32Height);
    JPEG_TRACE("============================================================================\n");
#endif

    HI_GFX_Memset(&stMbOpt,0,sizeof(TDE2_MBOPT_S));
    stMbOpt.enResize = TDE2_MBRESIZE_NONE;

#ifndef HI_ADVCA_FUNCTION_RELEASE
    //DEC_TSTART();
#endif

#if 0/**<-- csc by scanlines **/
    while (Row < pJpegHandle->stCropRect.h)
    {
        SrcRect.s32Xpos   = pJpegHandle->stCropRect.x;
        SrcRect.s32Ypos   = Row;
        SrcRect.u32Width  = (HI_U32)pJpegHandle->stCropRect.w;
        SrcRect.u32Height = 1;
        DstRect.s32Xpos   = 0;
        DstRect.s32Ypos   = Row;
        DstRect.u32Width  = (HI_U32)pJpegHandle->stCropRect.w;
        DstRect.u32Height = 1;
#endif
        if ((s32Handle = JPEG_HDEC_CSC_BeginJob(pJpegHandle->CscDev)) != HI_ERR_TDE_INVALID_HANDLE)
        {
          Ret = JPEG_HDEC_CSC_MbBlit(s32Handle, &SrcSurface, &SrcRect, &DstSurface, &DstRect, &stMbOpt,pJpegHandle->CscDev);
          if (HI_SUCCESS != Ret)
          {
              JPEG_TRACE("==== JPEG_HDEC_CSC_MbBlit Failure,s32Ret = 0x%x!\n",Ret);
              return HI_FAILURE;
          }

          Ret = JPEG_HDEC_CSC_EndJob(s32Handle, HI_TRUE, 10000,pJpegHandle->CscDev);
          if (HI_SUCCESS != Ret)
          {
              JPEG_TRACE("==== JPEG_HDEC_CSC_EndJob Failure,s32Ret = 0x%x!\n",Ret);
              return HI_FAILURE;
          }
        }
#if 0
        Row++;
    }
#endif
#ifndef HI_ADVCA_FUNCTION_RELEASE
    //DEC_TEND();
#endif

    pJpegHandle->bCSCEnd = HI_TRUE;

#ifndef HI_ADVCA_FUNCTION_RELEASE
    JPEG_HDEC_SaveBmp(cinfo,pJpegHandle->stDecSurface.pOutVir,DstRect.u32Width,DstRect.u32Height, DstSurface.u32Stride);
#endif

    return HI_SUCCESS;
}
#endif



#ifdef JPEG_HDEC_OPEN_CLOSE_DEV
static inline HI_S32 JPEG_HDEC_CSC_Open()
{
    HI_S32 s32CscDev = -1;
    s32CscDev = open("/dev/hi_tde", O_RDWR, S_IRUSR);
    if (s32CscDev < 0)
    {
        return -1;
    }

    return s32CscDev;
}

static inline HI_VOID JPEG_HDEC_CSC_Close(HI_S32 CscDev)
{
    if (CscDev < 0)
    {
       return;
    }

    close(CscDev);

    return;
}
#endif
#endif
