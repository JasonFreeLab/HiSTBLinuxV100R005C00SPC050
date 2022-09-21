/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hi_jpeg_api.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : The user will use this api to realize some function
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                sdk                        Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "jerror.h"

#include "hi_jpeg_config.h"
#include "hi_jpeg_api.h"
#include "hi_gfx_sys.h"
#include "hi_jpeg_checkpara.h"

#include "jpeg_hdec_api.h"
#include "jpeg_hdec_mem.h"

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/

/********************** Global Variable declaration ********************************/

/********************** API forward declarations    ********************************/

extern HI_VOID JPEG_SDEC_SetInputBufferInfo(const struct jpeg_decompress_struct *cinfo,HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,HI_CHAR* pSecondStreamVirBuf, HI_U32 SecondStreamBufSize);
extern HI_VOID JPEG_HDEC_GetImagInfo(j_decompress_ptr cinfo);

/**********************       API realization       ***********************************/

HI_VOID HI_JPEG_GetInputDataBufInfo(const struct jpeg_decompress_struct *cinfo, HI_JPEG_INPUT_DATA_BUF_INFO_S *pInputDataBufInfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;

    CHECK_JPEG_EQUAL_UNRETURN(cinfo, NULL);
    CHECK_JPEG_EQUAL_UNRETURN(pInputDataBufInfo, NULL);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(pJpegHandle, NULL);

    /**<-- get hard decode save stream buffer information >**/
    /**<-- 获取硬件解码存储码流buffer  信息>**/
    pInputDataBufInfo->BeginReadToInputDataBuf = pJpegHandle->stInputDataBufInfo.BeginReadToInputDataBuf;
    pInputDataBufInfo->pInputDataVirBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[pJpegHandle->stInputDataBufInfo.SaveStreamBufIndex].pSaveStreamVirBuf;
    pInputDataBufInfo->InputDataPhyBuf  = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[pJpegHandle->stInputDataBufInfo.SaveStreamBufIndex].SaveStreamPhyBuf;
    pInputDataBufInfo->InputDataBufSize = pJpegHandle->stInputDataBufInfo.SaveStreamBufSize;

    return;
}


HI_VOID HI_JPEG_EnReadDataToInputDataBuf(const struct jpeg_decompress_struct *cinfo, HI_BOOL EnReadToInputDataBuf)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_UNRETURN(cinfo, NULL);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(pJpegHandle, NULL);

    /**<-- tell jpeg decoder enable read data to save stream buffer >**/
    /**<-- 通知解码器使能往码流buffer 写数据了，解码可以不用自己再拷贝了>**/
    pJpegHandle->stInputDataBufInfo.EnReadToInputDataBuf = EnReadToInputDataBuf;

    return;
}


HI_VOID HI_JPEG_StopDec(const struct jpeg_decompress_struct *cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_UNRETURN(cinfo, NULL);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(pJpegHandle, NULL);

    /**<-- stop decode >**/
    /**<-- 停止解码，解码退出>**/
    pJpegHandle->EnStopDecode = HI_TRUE;

    return;
}


HI_VOID HI_JPEG_SetStreamBufInfo(const struct jpeg_decompress_struct *cinfo,HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,HI_CHAR* pSecondStreamVirBuf, HI_U32 SecondStreamBufSize)
{
    /**<-- set input stream buffer information >**/
    /**<-- 设置码流输入信息，包括内存回绕信息>**/
    CHECK_JPEG_EQUAL_UNRETURN(cinfo, NULL);
    JPEG_SDEC_SetInputBufferInfo(cinfo, StreamPhyAddr, TotalStremBufSize, pSecondStreamVirBuf, SecondStreamBufSize);
    return;
}

HI_VOID HI_JPEG_SetCropRect(const struct jpeg_decompress_struct *cinfo, const HI_JPEG_RECT_S *pstCropRect)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_UNRETURN(cinfo, NULL);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(pJpegHandle, NULL);

    CHECK_JPEG_EQUAL_UNRETURN(pstCropRect, NULL);

    pJpegHandle->bSetCropRect = HI_TRUE;
    pJpegHandle->stCropRect.x = pstCropRect->x;
    pJpegHandle->stCropRect.y = pstCropRect->y;
    pJpegHandle->stCropRect.w = pstCropRect->w;
    pJpegHandle->stCropRect.h = pstCropRect->h;

    return;
}

HI_S32  HI_JPEG_SetOutDesc(const struct jpeg_decompress_struct *cinfo,const HI_JPEG_SURFACE_S *pstSurfaceDesc)
{
    HI_S32 s32Cnt = 0;
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,HI_FAILURE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,HI_FAILURE);

    CHECK_JPEG_EQUAL_RETURN(pstSurfaceDesc, NULL,HI_FAILURE);

    /**<--decode out to usr buffer >**/
    /**<-- 输出到用户分配的buffer 中>**/
    pJpegHandle->bOutUsrBuf = HI_TRUE;

    for (s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++)
    {
        pJpegHandle->stOutSurface.u32OutPhy[s32Cnt]   = pstSurfaceDesc->u32OutPhy[s32Cnt];
        pJpegHandle->stOutSurface.pOutVir[s32Cnt]     = pstSurfaceDesc->pOutVir[s32Cnt];
        pJpegHandle->stOutSurface.u32OutStride[s32Cnt]= pstSurfaceDesc->u32OutStride[s32Cnt];
    }

    return HI_SUCCESS;
}


HI_S32  HI_JPEG_GetJpegInfo(j_decompress_ptr cinfo, HI_JPEG_INFO_S *pJpegInfo)
{
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
     CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,HI_FAILURE);

     pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
     CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,HI_FAILURE);

     CHECK_JPEG_EQUAL_RETURN(pJpegInfo, NULL,HI_FAILURE);

     /**<--get input picture information >**/
     /**<-- 获取原始图片的大小和像素格式等信息>**/
     if (HI_FALSE == pJpegInfo->bOutInfo)
     {
         HI_GFX_Memset(pJpegInfo, 0, sizeof(HI_JPEG_INFO_S));
         pJpegInfo->u32Width[0]  = cinfo->image_width;
         pJpegInfo->u32Height[0] = cinfo->image_height;
         pJpegInfo->enFmt = pJpegHandle->enImageFmt;
         return HI_SUCCESS;
     }

     JPEG_HDEC_GetImagInfo(cinfo);

     /**<--get output information >**/
     /**<-- 获取输出信息>**/
     switch (cinfo->out_color_space)
     {
         case JCS_YUV400_SP:
         case JCS_YUV444_SP:
         case JCS_YUV420_SP:
         case JCS_YUV422_SP_12:
         case JCS_YUV422_SP_21:
             pJpegInfo->u32Width[0]     = pJpegHandle->stJpegSofInfo.u32YWidth;
             pJpegInfo->u32Width[1]     = pJpegHandle->stJpegSofInfo.u32CWidth;
             pJpegInfo->u32Height[0]    = pJpegHandle->stJpegSofInfo.u32YHeight;
             pJpegInfo->u32Height[1]    = pJpegHandle->stJpegSofInfo.u32CHeight;
             pJpegInfo->u32McuHeight[0] = pJpegHandle->stJpegSofInfo.u32YMcuHeight;
             pJpegInfo->u32McuHeight[1] = pJpegHandle->stJpegSofInfo.u32CMcuHeight;
             pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.u32YStride;
             pJpegInfo->u32OutStride[1] = pJpegHandle->stJpegSofInfo.u32CbCrStride;
             pJpegInfo->u32OutSize[0]   = pJpegHandle->stJpegSofInfo.u32YSize;
             pJpegInfo->u32OutSize[1]   = pJpegHandle->stJpegSofInfo.u32CSize;
             break;
          default:
             pJpegInfo->u32Width[0]     = cinfo->output_width;
             pJpegInfo->u32Height[0]    = cinfo->output_height;
             pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.DecOutStride;
             pJpegInfo->u32OutSize[0]   = pJpegInfo->u32OutStride[0] * pJpegInfo->u32Height[0];
             break;
     }

     /**<--used by decode >**/
     /**<--  暂时做为解码分辨率用>**/
     pJpegInfo->u32Width[2]     = pJpegHandle->stJpegSofInfo.DecOutWidth;
     pJpegInfo->u32Height[2]    = pJpegHandle->stJpegSofInfo.DecOutHeight;
     pJpegInfo->u32OutStride[2] = pJpegHandle->stJpegSofInfo.DecOutStride;
     pJpegInfo->u32OutSize[2]   = pJpegInfo->u32OutStride[2] * pJpegInfo->u32Height[2];

     return HI_SUCCESS;
}

HI_S32 HI_JPEG_GetLuPixSum(const struct jpeg_decompress_struct *cinfo, HI_U64 *u64LuPixSum)
{
    CHECK_JPEG_EQUAL_RETURN(u64LuPixSum, NULL,HI_FAILURE);

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,HI_FAILURE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,HI_FAILURE);

    *u64LuPixSum = pJpegHandle->u64LuPixValue;

    return HI_SUCCESS;

#else
    HI_UNUSED(cinfo);
    *u64LuPixSum = 0;
    return HI_FAILURE;
#endif
}


HI_S32 HI_JPEG_SetLowDelayInf(const struct jpeg_decompress_struct *cinfo, HI_U32 u32PhyLineBuf, HI_CHAR* pVirLineBuf)
{
#ifndef CONFIG_JPEG_LOW_DELAY_SUPPORT
    HI_UNUSED(cinfo);
    HI_UNUSED(u32PhyLineBuf);
    HI_UNUSED(pVirLineBuf);
    return HI_FAILURE;
#else
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,HI_FAILURE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,HI_FAILURE);

    if (NULL == pVirLineBuf || 0 == u32PhyLineBuf)
    {
        pJpegHandle->bLowDelayEn   = HI_FALSE;
        pJpegHandle->u32PhyLineBuf = 0;
        pJpegHandle->pVirLineBuf   = NULL;
        return HI_FAILURE;
    }

    /**<-- only support yuv sp that output color space >**/
    /**<-- 低延迟只支持输出yuv semi-planer 格式>**/
    pJpegHandle->bLowDelayEn   = HI_TRUE;
    pJpegHandle->u32PhyLineBuf = u32PhyLineBuf;
    pJpegHandle->pVirLineBuf   = pVirLineBuf;
    return HI_SUCCESS;
#endif
}



#ifdef CONFIG_JPEG_EXIF_SUPPORT
HI_S32 HI_JPEG_SetExifMark(j_decompress_ptr cinfo, HI_BOOL bExifSupport)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,HI_FAILURE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,HI_FAILURE);

    pJpegHandle->bExifSupport = bExifSupport;

    return HI_SUCCESS;
}

HI_U8 HI_JPEG_GetImageCount(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,0);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,0);

    return pJpegHandle->u8ImageCount;
}

HI_U32 HI_JPEG_GetThumbnailSize(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,0);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,0);

    return pJpegHandle->u32ThumbnailSize;
}

HI_S32 HI_JPEG_GetThumbnail(j_decompress_ptr cinfo, HI_CHAR* pThumbnailAddr)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,HI_FAILURE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,HI_FAILURE);

    CHECK_JPEG_EQUAL_RETURN(pThumbnailAddr, NULL,HI_FAILURE);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle->pThumbnailAddr, NULL,HI_FAILURE);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle->u32ThumbnailSize, 0,HI_FAILURE);

    HI_GFX_Memcpy(pThumbnailAddr, pJpegHandle->pThumbnailAddr, pJpegHandle->u32ThumbnailSize);

    return HI_SUCCESS;
}

HI_BOOL HI_JPEG_IsHdr(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_RETURN(cinfo, NULL,HI_FALSE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(pJpegHandle, NULL,HI_FALSE);

    return pJpegHandle->bIsHDR;
}
#endif


HI_VOID HI_JPEG_IfHardDec(const struct jpeg_decompress_struct *cinfo,HI_BOOL *pHardDec)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_UNRETURN(cinfo, NULL);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(pJpegHandle, NULL);

    *pHardDec = pJpegHandle->bHdecEnd;

    return;
}
