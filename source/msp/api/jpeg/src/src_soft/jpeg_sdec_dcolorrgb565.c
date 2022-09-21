/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dcolorrgb565.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : output rgb565
                        解码输出RGB565。
Function List   :

History           :
Date                          Author                    Modification
2017/03/16           sdk              Created file
******************************************************************************/



/****************************  add include here     *********************************/
#include "jpeg_sdec_color.h"


/***************************** Macro Definition     ********************************/
#define CONVERT_PACK_SHORT_565(r,g,b)    ((((r) >> 3) << 11)|(((g)>> 2) << 5)|(((b)>>3)))

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
static inline HI_VOID RGB565_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    if (NULL == OutBuf)
    {
       return;
    }

    if ((JCS_RGB565 == cinfo->out_color_space) || (JCS_RGB_565 == cinfo->out_color_space))
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_565(Red,Green,Blue);
       return;
    }

    *(INT16*)OutBuf = CONVERT_PACK_SHORT_565(Blue,Green,Red);

    return;
}

static HI_VOID JPEG_SDEC_YCC_RGB565_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB565_Convert(cinfo,OutBuf,Red,Green,Blue);
    return;
}

static HI_VOID JPEG_SDEC_GRAY_RGB565_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB565_Convert(cinfo,OutBuf,Red,Green,Blue);
    return;
}

static HI_VOID JPEG_SDEC_YCCK_RGB565_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB565_Convert(cinfo,OutBuf,Red,Green,Blue);
    return;
}

static HI_VOID JPEG_SDEC_CMYK_RGB565_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    register HI_U32 R = 0, G = 0, B = 0;

    R  =  MulDiv255Round(Red,Alpha);
    G  =  MulDiv255Round(Green,Alpha);
    B  =  MulDiv255Round(Blue,Alpha);
    RGB565_Convert(cinfo,OutBuf,R,G,B);
    return;
}


/*****************************************************************************
* func              : JPEG_SDEC_SupportRGB565
* description    : decode output rgb565
                          CNcomment:解码输出格式为rgb565CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_SupportRGB565(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if ((JCS_RGB565 != cinfo->out_color_space) && (JCS_BGR565 != cinfo->out_color_space) && (JCS_RGB_565 != cinfo->out_color_space))
    {
        return HI_FAILURE;
    }

    cinfo->out_color_components = 3;

    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCC_ConVert  = JPEG_SDEC_YCC_RGB565_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_GRAY_ConVert = JPEG_SDEC_GRAY_RGB565_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCCK_ConVert = JPEG_SDEC_YCCK_RGB565_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_CMYK_ConVert = JPEG_SDEC_CMYK_RGB565_Convert;

    return HI_SUCCESS;
}
