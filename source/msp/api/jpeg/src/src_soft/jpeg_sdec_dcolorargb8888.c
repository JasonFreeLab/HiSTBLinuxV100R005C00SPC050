/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dcolorargb8888.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : output argb8888
                        解码输出ARGB8888
Function List   :

History           :
Date                          Author                    Modification
2017/07/05                sdk                         Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include "jpeg_sdec_color.h"

/***************************** Macro Definition     ********************************/


/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/

static inline HI_VOID ARGB8888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    if (NULL == OutBuf)
    {
       return;
    }

    if ((JCS_EXT_BGRX == cinfo->out_color_space) || (JCS_EXT_BGRA == cinfo->out_color_space))
    {
       OutBuf[2] =  Red;
       OutBuf[1] =  Green;
       OutBuf[0] =  Blue;
       OutBuf[3] =  Alpha;
       return;
    }

    if ((JCS_EXT_XBGR == cinfo->out_color_space) || (JCS_EXT_ABGR == cinfo->out_color_space))
    {
       OutBuf[3] =  Red;
       OutBuf[2] =  Green;
       OutBuf[1] =  Blue;
       OutBuf[0] =  Alpha;
       return;
    }

    if ((JCS_EXT_XRGB == cinfo->out_color_space) || (JCS_EXT_ARGB == cinfo->out_color_space))
    {
       OutBuf[1] =  Red;
       OutBuf[2] =  Green;
       OutBuf[3] =  Blue;
       OutBuf[0] =  Alpha;
       return;
    }

    /**<-- JCS_EXT_RGBX / JCS_EXT_RGBA / JCS_RGBA_8888>**/
    OutBuf[0] =  Red;
    OutBuf[1] =  Green;
    OutBuf[2] =  Blue;
    OutBuf[3] =  Alpha;

    return;
}

static HI_VOID JPEG_SDEC_YCC_ARGB8888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB8888_Convert(cinfo,OutBuf,Red,Green,Blue,0XFF);
    return;
}

static HI_VOID JPEG_SDEC_GRAY_ARGB8888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB8888_Convert(cinfo,OutBuf,Red,Green,Blue,0XFF);
    return;
}

static HI_VOID JPEG_SDEC_YCCK_ARGB8888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB8888_Convert(cinfo,OutBuf,Red,Green,Blue,0XFF);
    return;
}

static HI_VOID JPEG_SDEC_CMYK_ARGB8888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    ARGB8888_Convert(cinfo,OutBuf,Red,Green,Blue,Alpha);
    return;
}


/*****************************************************************************
* func              : JPEG_SDEC_SupportARGB8888
* description    : decode output argb8888
                          CNcomment:解码输出格式为argb8888 CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_SupportARGB8888(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (  (JCS_RGBA_8888 != cinfo->out_color_space)
        &&(JCS_EXT_RGBX != cinfo->out_color_space) && (JCS_EXT_BGRX != cinfo->out_color_space) && (JCS_EXT_XBGR != cinfo->out_color_space) && (JCS_EXT_XRGB != cinfo->out_color_space)
        &&(JCS_EXT_RGBA != cinfo->out_color_space) && (JCS_EXT_BGRA != cinfo->out_color_space) && (JCS_EXT_ABGR != cinfo->out_color_space) && (JCS_EXT_ARGB != cinfo->out_color_space))
    {
       return HI_FAILURE;
    }

    cinfo->out_color_components = 4;

    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCC_ConVert  = JPEG_SDEC_YCC_ARGB8888_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_GRAY_ConVert = JPEG_SDEC_GRAY_ARGB8888_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCCK_ConVert = JPEG_SDEC_YCCK_ARGB8888_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_CMYK_ConVert = JPEG_SDEC_CMYK_ARGB8888_Convert;

    return HI_SUCCESS;
}
