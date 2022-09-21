/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dcolorxrgbx888.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : output argb8888 and rgb888
                        解码输出ARGB8888 和RGB888
Function List   :

History           :
Date                          Author                    Modification
2017/03/16           sdk              Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include "jpeg_sdec_color.h"

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
static inline HI_VOID RGB888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    if (NULL == OutBuf)
    {
       return;
    }

    if ((JCS_BGR == cinfo->out_color_space) || (JCS_EXT_BGR == cinfo->out_color_space))
    {
       OutBuf[2] =  Red;
       OutBuf[1] =  Green;
       OutBuf[0] =  Blue;
       return;
    }

    OutBuf[0] =  Red;
    OutBuf[1] =  Green;
    OutBuf[2] =  Blue;

    return;
}

static HI_VOID JPEG_SDEC_YCC_RGB888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB888_Convert(cinfo,OutBuf,Red,Green,Blue);
    return;
}

static HI_VOID JPEG_SDEC_GRAY_RGB888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB888_Convert(cinfo,OutBuf,Red,Green,Blue);
    return;
}

static HI_VOID JPEG_SDEC_YCCK_RGB888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB888_Convert(cinfo,OutBuf,Red,Green,Blue);
    return;
}

static HI_VOID JPEG_SDEC_CMYK_RGB888_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    register HI_U32 R = 0, G = 0, B = 0;

    R =  MulDiv255Round(Red,Alpha);
    G =  MulDiv255Round(Green,Alpha);
    B =  MulDiv255Round(Blue,Alpha);
    RGB888_Convert(cinfo,OutBuf,R,G,B);
    return;
}

/*****************************************************************************
* func              : JPEG_SDEC_SupportRGB888
* description    : decode output rgb888
                          CNcomment:解码输出格式为rgb888CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_SupportRGB888(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (  (JCS_BGR != cinfo->out_color_space) && (JCS_RGB != cinfo->out_color_space)
        &&(JCS_EXT_BGR != cinfo->out_color_space) && (JCS_EXT_RGB != cinfo->out_color_space))
    {
        return HI_FAILURE;
    }

    cinfo->out_color_components = 3;

    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCC_ConVert  = JPEG_SDEC_YCC_RGB888_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_GRAY_ConVert = JPEG_SDEC_GRAY_RGB888_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCCK_ConVert = JPEG_SDEC_YCCK_RGB888_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_CMYK_ConVert = JPEG_SDEC_CMYK_RGB888_Convert;

    return HI_SUCCESS;
}
