/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_color.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     :
Function List   :

History           :
Date                          Author                    Modification
2017/07/05                 sdk                        Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jpeglib.h"
#include "hi_jpeg_config.h"

#include "jpeg_hdec_api.h"

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/

#ifdef JPEG_SDEC_CALC_OUT_COLOR_COMPONENTS
/*****************************************************************************
* func              : JPEG_SDEC_CalcOutColorComponents
* description    : calc output color components
                          CNcomment: 计算输出色彩空间的组件数CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_VOID JPEG_SDEC_CalcOutColorComponents(j_decompress_ptr cinfo)
{
    switch (cinfo->out_color_space)
    {
        case JCS_RGBA_8888:
          cinfo->out_color_components = 4;
          break;
        case JCS_CrCbY:
        case JCS_BGR:
        case JCS_BGR565:
          cinfo->out_color_components = 3;
          break;
        case JCS_ARGB_1555:
        case JCS_ABGR_1555:
        case JCS_RGBA_5551:
        case JCS_BGRA_5551:
          cinfo->out_color_components = 2;
          break;
        default:
          break;
    }

    return;
}
#endif



#ifdef JPEG_SDEC_SET_IMG_COLOR_SPACE
/*****************************************************************************
* func              : JPEG_SDEC_SetImgColorSpace
* description    : set image color space
                          CNcomment: 设置图片的色彩空间CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_VOID JPEG_SDEC_SetImgColorSpace(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (cinfo->num_components == 1)
    {
       if (cinfo->comp_info[0].h_samp_factor==cinfo->comp_info[0].v_samp_factor)
       {/**不管采样因子是多少都按照(1*1)配置，T81协议36页**/
             pJpegHandle->enImageFmt = JPEG_FMT_YUV400;
             pJpegHandle->u8Fac[0][0] = 1;
             pJpegHandle->u8Fac[0][1] = 1;
             pJpegHandle->u8Fac[1][0] = 0;
             pJpegHandle->u8Fac[1][1] = 0;
             pJpegHandle->u8Fac[2][0] = 0;
             pJpegHandle->u8Fac[2][1] = 0;
       }
    }
    else if ((cinfo->num_components == 3) && (cinfo->comp_info[1].h_samp_factor == cinfo->comp_info[2].h_samp_factor) && (cinfo->comp_info[1].v_samp_factor == cinfo->comp_info[2].v_samp_factor))
    {
        if (cinfo->comp_info[0].h_samp_factor == ((cinfo->comp_info[1].h_samp_factor)<<1))
        {
             if (cinfo->comp_info[0].v_samp_factor == ((cinfo->comp_info[1].v_samp_factor)<<1))
             {
                pJpegHandle->enImageFmt = JPEG_FMT_YUV420;
             }
             else if (cinfo->comp_info[0].v_samp_factor == cinfo->comp_info[1].v_samp_factor)
             {
                  pJpegHandle->enImageFmt = JPEG_FMT_YUV422_21;
             }

         }
         else if (cinfo->comp_info[0].h_samp_factor == cinfo->comp_info[1].h_samp_factor)
         {
               if (cinfo->comp_info[0].v_samp_factor == ((cinfo->comp_info[1].v_samp_factor)<<1))
               {
                    pJpegHandle->enImageFmt = JPEG_FMT_YUV422_12;
               }
               else if (cinfo->comp_info[0].v_samp_factor == cinfo->comp_info[1].v_samp_factor)
               {
                    pJpegHandle->enImageFmt = JPEG_FMT_YUV444;
               }
          }
          pJpegHandle->u8Fac[0][0] = cinfo->comp_info[0].h_samp_factor;
          pJpegHandle->u8Fac[0][1] = cinfo->comp_info[0].v_samp_factor;
          pJpegHandle->u8Fac[1][0] = cinfo->comp_info[1].h_samp_factor;
          pJpegHandle->u8Fac[1][1] = cinfo->comp_info[1].v_samp_factor;
          pJpegHandle->u8Fac[2][0] = cinfo->comp_info[2].h_samp_factor;
          pJpegHandle->u8Fac[2][1] = cinfo->comp_info[2].v_samp_factor;
    }
    else
    {
        pJpegHandle->enImageFmt = JPEG_FMT_BUTT;
    }

    return;
}
#endif


#ifdef JPEG_SDEC_SET_LU_DC_CODE_LENGTH
/*****************************************************************************
* func              : JPEG_SDEC_SetLuDcCodeLen
* description    : set lu dc code length
                          CNcomment: 设置lu 的编码长度CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_VOID JPEG_SDEC_SetLuDcCodeLen(j_decompress_ptr cinfo, UINT8 bits[])
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    pJpegHandle->s32LuDcLen[0] = bits[11];
    pJpegHandle->s32LuDcLen[1] = bits[12];
    pJpegHandle->s32LuDcLen[2] = bits[13];
    pJpegHandle->s32LuDcLen[3] = bits[14];
    pJpegHandle->s32LuDcLen[4] = bits[15];
    pJpegHandle->s32LuDcLen[5] = bits[16];
    return;
}
#endif
