/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_parse.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : jpeg  文件解析
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                 sdk                        Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jerror.h"
#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"
#include "jpeg_hdec_mem.h"
#include "hi_jpeg_checkpara.h"

/***************************** Macro Definition ***********************************/
#define JPEG_ALIGNED_SCALE(x, i)    ( ( (x) + (1 << (i)) - 1 ) >> (i) )
#define JPEG_ROUND_UP(a,b)          ( ((a) + (b) - (1L)) / (b) )

/***************************** Structure Definition ********************************/
typedef enum tagJPEG_HDEC_SCALE_E
{
    JPEG_SCALEDOWN_1 = 0,      /**< scanle down 1 >**//**<CNcomment:不缩放   >**/
    JPEG_SCALEDOWN_2 = 1,      /**< scanle down 2 >**//**<CNcomment:缩小2倍 >**/
    JPEG_SCALEDOWN_4 = 2,      /**< scanle down 4 >**//**<CNcomment:缩小4倍 >**/
    JPEG_SCALEDOWN_8 = 3,      /**< scanle down 8 >**//**<CNcomment:缩小8倍 >**/
    JPEG_SCALEDOWN_BUTT
}JPEG_HDEC_SCALE_E;
/***************************** Global Variable declaration **************************/

/***************************** API forward declarations ****************************/

static inline HI_BOOL JPEG_HDEC_CheckDecXRGBSupport    (const struct jpeg_decompress_struct *cinfo);
static inline HI_VOID JPEG_HDEC_SetOutColorSapceMarker (const struct jpeg_decompress_struct *cinfo);
static inline HI_VOID JPEG_HDEC_GetOutSize(const HI_U32 u32Ration,const HI_U32 u32InWidth, const HI_U32 u32InHeight,HI_U32 *pu32OutWidth,HI_U32 *pu32OutHeight);
static HI_VOID JPEG_HDEC_CalcScale(j_decompress_ptr cinfo);
static HI_VOID JPEG_HDEC_CalcOutComponents(j_decompress_ptr cinfo);
static HI_VOID JPEG_HDEC_CalcOutStride(j_decompress_ptr cinfo,HI_U32 Width);
static inline HI_VOID JPEG_HDEC_InitCropRect(const struct jpeg_decompress_struct *cinfo);
static inline HI_VOID JPEG_HDEC_GetCalcOutXRGBSize(const struct jpeg_decompress_struct *cinfo, HI_U32 *pYSize, HI_U32 *pCSize);
static inline HI_VOID JPEG_HDEC_GetUVResolutionForYuv420sp(const struct jpeg_decompress_struct *cinfo, HI_U32 YHeightTmp, HI_U32 YStride, HI_U32 *pUVHeightTmp, HI_U32 *pUVStride);


extern HI_VOID JPEG_SDEC_GetStride(HI_U32 u32SrcW, HI_U32 *pu32Stride,HI_U32 u32Align);

/***************************** API realization *********************************/

/*****************************************************************************
* func            : JPEG_HDEC_GetImagInfo
* description  : get jpeg picture information
                                   CNcomment:  获取图片信息 CNend\n
* param[in]   : cinfo       CNcomment: 解码对象    CNend\n
* retval         : NA
* others:       : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_GetImagInfo(j_decompress_ptr cinfo)
{
      HI_U32 InputMcuWidth  = 0;
      HI_U32 InputMcuHeight = 0;
      HI_U32 DecWidth = 0;
      HI_U32 DecHeight = 0;
      /**<-- mcu data >**/
      /**<-- 宏块大小 >**/
      HI_U32 YWidthTmp = 0;
      HI_U32 YHeightTmp = 0;
      HI_U32 CHeightTmp = 0;
      /**<-- useful data >**/
      /**<-- 实际有用的大小 >**/
      HI_U32 u32YStride = 0;
      HI_U32 u32UVStride = 0;
      HI_U32 u32YWidth = 0;
      HI_U32 u32YHeight = 0;
      HI_U32 u32UVWidth = 0;
      HI_U32 u32UVHeight = 0;
      HI_U32 u32YSize = 0;
      HI_U32 u32CSize = 0;

      CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
      JPEG_API_MODULE_DEFINE_HANDLE();

      if (HI_TRUE == pJpegHandle->stJpegSofInfo.bCalcSize)
      {
          JPEG_HDEC_CalcOutComponents(cinfo);
          return;
      }

      JPEG_HDEC_CalcScale(cinfo);

      JPEG_HDEC_GetOutSize(pJpegHandle->ScalRation,cinfo->image_width,cinfo->image_height,&(cinfo->output_width),&(cinfo->output_height));

      JPEG_HDEC_SetOutColorSapceMarker(cinfo);

      JPEG_SDEC_GetStride(cinfo->output_width,&u32YStride,JPGD_HDEC_MMZ_YUVSP_STRIDE_ALIGN);

      u32YWidth  = (cinfo->output_width <= 1)  ? (2) : (cinfo->output_width);
      u32YHeight = (cinfo->output_height <= 1) ? (2) : (cinfo->output_height);

      if (1 == pJpegHandle->u8Fac[0][0])
      {
           InputMcuWidth  = (cinfo->image_width  + JPEG_MCU_8ALIGN - 1) >> 3;
           DecWidth = (cinfo->image_width   + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
           YWidthTmp = (cinfo->output_width  + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
      }
      else
      {
           InputMcuWidth  = (cinfo->image_width  + JPEG_MCU_16ALIGN - 1) >> 4;
           DecWidth  = (cinfo->image_width + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
           YWidthTmp = (cinfo->output_width + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
      }

      if (1 == pJpegHandle->u8Fac[0][1])
      {
           InputMcuHeight = (cinfo->image_height + JPEG_MCU_8ALIGN - 1) >> 3;
           DecHeight  = (cinfo->image_height  + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
           YHeightTmp = (cinfo->output_height + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
      }
      else
      {
           InputMcuHeight = (cinfo->image_height + JPEG_MCU_16ALIGN - 1) >> 4;
           DecHeight  = (cinfo->image_height  + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
           YHeightTmp = (cinfo->output_height + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
      }

      switch (pJpegHandle->enImageFmt)
      {
          case JPEG_FMT_YUV420:
              CHeightTmp  = YHeightTmp >> 1;
              u32UVStride = u32YStride;
              u32YWidth   = (u32YWidth  >> 1) << 1;
              u32YHeight  = (u32YHeight >> 1) << 1;
              u32UVWidth  = u32YWidth  >> 1;
              u32UVHeight = u32YHeight >> 1;
              break;
          case JPEG_FMT_YUV422_21:
              CHeightTmp  = YHeightTmp;
              u32UVStride = u32YStride;
              JPEG_HDEC_GetUVResolutionForYuv420sp(cinfo,YHeightTmp,u32YStride,&CHeightTmp,&u32UVStride);
              u32YWidth    = (u32YWidth  >> 1) << 1;
              u32UVWidth   = u32YWidth >> 1;
              u32UVHeight  = u32YHeight;
              break;
          case JPEG_FMT_YUV422_12:
              CHeightTmp  = YHeightTmp >> 1;
              u32UVStride = u32YStride << 1;
              JPEG_HDEC_GetUVResolutionForYuv420sp(cinfo,YHeightTmp,u32YStride,&CHeightTmp,&u32UVStride);
              u32YHeight   = (u32YHeight >> 1) << 1;
              u32UVWidth   = u32YWidth;
              u32UVHeight  = u32YHeight >> 1;
              break;
          case JPEG_FMT_YUV444:
              CHeightTmp  = YHeightTmp;
              u32UVStride = u32YStride << 1;
              JPEG_HDEC_GetUVResolutionForYuv420sp(cinfo,YHeightTmp,u32YStride,&CHeightTmp,&u32UVStride);
              u32UVWidth   = u32YWidth;
              u32UVHeight  = u32YHeight;
              break;
          default:
              break;
      }

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
      if ((HI_TRUE == pJpegHandle->bOutYUV420SP) && (JPEG_FMT_YUV400 != pJpegHandle->enImageFmt))
      {
          u32YWidth  = (0 == (u32YWidth  % 2)) ? (u32YWidth)  : (u32YWidth  - 1);
          u32YHeight = (0 == (u32YHeight % 2)) ? (u32YHeight) : (u32YHeight - 1);
          u32UVWidth = u32YWidth >> 1;
          u32UVHeight = u32YHeight >> 1;
      }
#endif

      JPEG_HDEC_InitCropRect(cinfo);

      JPEG_HDEC_CalcOutComponents(cinfo);

      JPEG_HDEC_CalcOutStride(cinfo,YWidthTmp);
      pJpegHandle->stJpegSofInfo.DecOutStride = (HI_TRUE == pJpegHandle->bOutYCbCrSP) ? (u32YStride) : (pJpegHandle->stJpegSofInfo.DecOutStride);

      u32YSize = YHeightTmp * u32YStride;
      u32CSize = CHeightTmp * u32UVStride;
      JPEG_HDEC_GetCalcOutXRGBSize(cinfo, &u32YSize, &u32CSize);

      /**<-- jpeg decode use mcu align  >**/
      /**<-- jpeg 解码使用的参数为MCU 对齐的 >**/
      pJpegHandle->stJpegSofInfo.bCalcSize =  HI_TRUE;

      pJpegHandle->stJpegSofInfo.u32InWandH =  (InputMcuWidth | (InputMcuHeight << 16));

      pJpegHandle->stJpegSofInfo.u32YWidth  =  u32YWidth;
      pJpegHandle->stJpegSofInfo.u32YHeight =  u32YHeight;
      pJpegHandle->stJpegSofInfo.u32YStride =  u32YStride;
      pJpegHandle->stJpegSofInfo.u32YSize   =  u32YSize;
      pJpegHandle->stJpegSofInfo.u32CWidth  =  u32UVWidth;
      pJpegHandle->stJpegSofInfo.u32CHeight =  u32UVHeight;
      pJpegHandle->stJpegSofInfo.u32CbCrStride = u32UVStride;
      pJpegHandle->stJpegSofInfo.u32CSize =  u32CSize;

      pJpegHandle->stJpegSofInfo.u32YMcuHeight = YHeightTmp;
      pJpegHandle->stJpegSofInfo.u32CMcuHeight = CHeightTmp;

      /**<-- get lu  pixel sum >**/
      /**<-- 统计亮度和使用>**/
      pJpegHandle->stJpegSofInfo.DecOutWidth = DecWidth  >> pJpegHandle->ScalRation;
      pJpegHandle->stJpegSofInfo.DecOutHeight = DecHeight >> pJpegHandle->ScalRation;

#ifdef CONFIG_JPEG_HARDDEC2ARGB
      pJpegHandle->stJpegSofInfo.u32McuWidth  =  InputMcuWidth;
      pJpegHandle->stJpegSofInfo.u32MINSize   =  InputMcuWidth * 128;
      pJpegHandle->stJpegSofInfo.u32MIN1Size  =  pJpegHandle->stJpegSofInfo.u32MINSize;
      pJpegHandle->stJpegSofInfo.u32RGBSizeReg =  2 * pJpegHandle->stJpegSofInfo.u32MINSize;
#endif

      return;
}

static inline HI_VOID JPEG_HDEC_GetUVResolutionForYuv420sp(const struct jpeg_decompress_struct *cinfo, HI_U32 YHeightTmp, HI_U32 YStride, HI_U32 *pUVHeightTmp, HI_U32 *pUVStride)
{
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     if (HI_TRUE != pJpegHandle->bOutYUV420SP)
     {
         return;
     }

     if (JPEG_FMT_YUV422_21 == pJpegHandle->enImageFmt)
     {
         *pUVHeightTmp  = YHeightTmp >> 1;
         return;
     }

     if (JPEG_FMT_YUV422_12 == pJpegHandle->enImageFmt)
     {
         *pUVStride = (YStride << 1) >> 1;
         return;
     }

     if (JPEG_FMT_YUV444 == pJpegHandle->enImageFmt)
     {
         *pUVHeightTmp  = YHeightTmp >> 1;
         *pUVStride = (YStride << 1) >> 1;
         return;
     }
#else
    HI_UNUSED(cinfo);
    HI_UNUSED(YHeightTmp);
    HI_UNUSED(YStride);
    HI_UNUSED(pUVHeightTmp);
    HI_UNUSED(pUVStride);
#endif
    return;
}

static inline HI_VOID JPEG_HDEC_InitCropRect(const struct jpeg_decompress_struct *cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (HI_TRUE == pJpegHandle->bSetCropRect)
    {
         return;
    }

    pJpegHandle->stCropRect.x = 0;
    pJpegHandle->stCropRect.y = 0;
    pJpegHandle->stCropRect.w = (HI_S32)cinfo->output_width;
    pJpegHandle->stCropRect.h = (HI_S32)cinfo->output_height;

    return;
}

static inline HI_VOID JPEG_HDEC_GetCalcOutXRGBSize(const struct jpeg_decompress_struct *cinfo, HI_U32 *pYSize, HI_U32 *pCSize)
{
#ifdef CONFIG_JPEG_HARDDEC2ARGB
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if (HI_TRUE != pJpegHandle->bDecOutColorSpaecXRGB)
    {
        return;
    }

    *pYSize = pJpegHandle->stJpegSofInfo.DecOutStride * pJpegHandle->stCropRect.h;
    *pCSize = 0;
#else
    HI_UNUSED(cinfo);
    HI_UNUSED(pYSize);
    HI_UNUSED(pCSize);
#endif
    return;
}

static HI_VOID JPEG_HDEC_CalcScale(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_8;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 2)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_4;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 3)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 4)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_2;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 5)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 6)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 7)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 8)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_1;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 9)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 10)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 11)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 12)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 13)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 14)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (cinfo->scale_num * DCTSIZE <= cinfo->scale_denom * 15)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }

    return;
}


static inline HI_VOID JPEG_HDEC_GetOutSize(const HI_U32 u32Ration,const HI_U32 u32InWidth, const HI_U32 u32InHeight,HI_U32 *pu32OutWidth,HI_U32 *pu32OutHeight)
{
      switch (u32Ration)
      {
        case 0:
            *pu32OutWidth  = u32InWidth;
            *pu32OutHeight = u32InHeight;
            break;
        case 1:
            *pu32OutWidth  = (JDIMENSION)JPEG_ROUND_UP((long) u32InWidth,  2L);
            *pu32OutHeight = (JDIMENSION)JPEG_ROUND_UP((long) u32InHeight, 2L);
            break;
        case 2:
            *pu32OutWidth  = (JDIMENSION)JPEG_ROUND_UP((long) u32InWidth,  4L);
            *pu32OutHeight = (JDIMENSION)JPEG_ROUND_UP((long) u32InHeight, 4L);
            break;
        case 3:
            *pu32OutWidth  = (JDIMENSION)JPEG_ROUND_UP((long) u32InWidth,  8L);
            *pu32OutHeight = (JDIMENSION)JPEG_ROUND_UP((long) u32InHeight, 8L);
            break;
        default:
            break;
      }
      return;
}


static inline HI_VOID JPEG_HDEC_SetOutColorSapceMarker(const struct jpeg_decompress_struct *cinfo)
{
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     if (  (JCS_YUV400_SP    == cinfo->out_color_space)
         ||(JCS_YUV420_SP    == cinfo->out_color_space)
         ||(JCS_YUV422_SP_12 == cinfo->out_color_space)
         ||(JCS_YUV422_SP_21 == cinfo->out_color_space)
         ||(JCS_YUV444_SP    == cinfo->out_color_space))
      {
          pJpegHandle->bOutYCbCrSP = HI_TRUE;
      }
      else
      {
          pJpegHandle->bOutYCbCrSP = HI_FALSE;
      }

      if (0 == pJpegHandle->ScalRation)
      {
          pJpegHandle->bDecOutColorSpaecXRGB = JPEG_HDEC_CheckDecXRGBSupport(cinfo);
      }
      else
      {
          pJpegHandle->bDecOutColorSpaecXRGB = HI_FALSE;
      }
      return;
}


static inline HI_BOOL JPEG_HDEC_CheckDecXRGBSupport(const struct jpeg_decompress_struct *cinfo)
{
#ifdef CONFIG_JPEG_HARDDEC2ARGB
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
     {
        return HI_FALSE;
     }

     if (   (JCS_EXT_RGBX == cinfo->out_color_space) || (JCS_EXT_RGBA == cinfo->out_color_space) || (JCS_RGBA_8888 == cinfo->out_color_space)
          ||(JCS_EXT_BGRX == cinfo->out_color_space) || (JCS_EXT_BGRA == cinfo->out_color_space) )
     {
        return HI_TRUE;
     }

     if ((JCS_RGBA_5551 == cinfo->out_color_space) || (JCS_BGRA_5551 == cinfo->out_color_space))
     {
        return HI_TRUE;
     }

     if (  (JCS_BGR == cinfo->out_color_space) || (JCS_RGB == cinfo->out_color_space)
        || (JCS_EXT_BGR == cinfo->out_color_space) || (JCS_EXT_RGB == cinfo->out_color_space))
     {
         return HI_TRUE;
     }

     if ((JCS_RGB565 == cinfo->out_color_space) || (JCS_BGR565 == cinfo->out_color_space) || (JCS_RGB_565 == cinfo->out_color_space))
     {
         return HI_TRUE;
     }
#else
     HI_UNUSED(cinfo);
#endif
     return HI_FALSE;
}

static inline HI_VOID JPEG_HDEC_ComponentsForXRGB8888(j_decompress_ptr cinfo)
{
    switch(cinfo->out_color_space)
    {
        case JCS_EXT_XBGR:
        case JCS_EXT_ABGR:
        case JCS_EXT_XRGB:
        case JCS_EXT_ARGB:
        case JCS_RGBA_8888:
        case JCS_EXT_RGBX:
        case JCS_EXT_RGBA:
        case JCS_EXT_BGRX:
        case JCS_EXT_BGRA:
            cinfo->out_color_components = 4;
            cinfo->output_components = 4;
            break;
        default:
            break;
    }
}

static HI_VOID JPEG_HDEC_ComponentsForXRGB1555(j_decompress_ptr cinfo)
{
    switch(cinfo->out_color_space)
    {
        case JCS_ARGB_1555:
        case JCS_ABGR_1555:
        case JCS_BGRA_5551:
        case JCS_RGBA_5551:
            cinfo->out_color_components = 2;
            cinfo->output_components = 2;
            break;
        default:
            break;;
    }
}

static HI_VOID JPEG_HDEC_ComponentsForRGB888(j_decompress_ptr cinfo)
{
    switch(cinfo->out_color_space)
    {
        case JCS_RGB:
        case JCS_EXT_RGB:
        case JCS_BGR:
        case JCS_EXT_BGR:
            cinfo->out_color_components = 3;
            cinfo->output_components = 3;
            break;
        default:
            break;
    }
}

static HI_VOID JPEG_HDEC_ComponentsForRGB565(j_decompress_ptr cinfo)
{
    switch(cinfo->out_color_space)
    {
        case JCS_RGB565:
        case JCS_RGB_565:
        case JCS_BGR565:
            cinfo->out_color_components = 3;
            cinfo->output_components = 2;
            break;
        default:
            break;
    }
}

static HI_VOID JPEG_HDEC_CalcOutComponents(j_decompress_ptr cinfo)
{
    cinfo->out_color_components = 1;
    cinfo->output_components = 1;

    JPEG_HDEC_ComponentsForXRGB8888(cinfo);
    JPEG_HDEC_ComponentsForXRGB1555(cinfo);
    JPEG_HDEC_ComponentsForRGB888(cinfo);
    JPEG_HDEC_ComponentsForRGB565(cinfo);

    return;
}


/*****************************************************************************
* func            : JPEG_HDEC_CalcOutStride
* description    : calculate out stride
                  CNcomment:  计算输出行间距 CNend\n
* param[in]     : cinfo       CNcomment: 解码对象    CNend\n
* retval        : NA
* others:        : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_CalcOutStride(j_decompress_ptr cinfo,HI_U32 Width)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    JPEG_SDEC_GetStride(Width * cinfo->out_color_components,&(pJpegHandle->stJpegSofInfo.DecOutStride),JPGD_HDEC_MMZ_CSCOUT_STRIDE_ALIGN);

    return;
}
