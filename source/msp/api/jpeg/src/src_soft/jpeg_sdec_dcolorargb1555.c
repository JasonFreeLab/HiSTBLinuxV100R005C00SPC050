/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dcolorargb1555.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : output argb1555
                        解码输出ARGB1555。
Function List   :

History           :
Date                          Author                    Modification
2017/07/05                sdk                         Created file
******************************************************************************/



/****************************  add include here     *********************************/
#include "jpeg_sdec_color.h"


/***************************** Macro Definition     ********************************/
#define CONVERT_PACK_SHORT_ARGB1555(a,r,g,b)  (((a) << 15) | (((r) >> 3) << 10) | (((g) >> 3) << 5) | ((b) >> 3))
#define CONVERT_PACK_SHORT_ABGR1555(a,r,g,b)  (((a) << 15) | (((b) >> 3) << 10) | (((g) >> 3) << 5) | ((r) >> 3))
#define CONVERT_PACK_SHORT_RGBA5551(a,r,g,b)  ((((r) >> 3) << 11) | (((g) >> 3) << 6) | (((b) >> 3) << 1) | (a))
#define CONVERT_PACK_SHORT_BGRA5551(a,r,g,b)  ((((b) >> 3) << 11) | (((g) >> 3) << 6) | (((r) >> 3) << 1) | (a))


/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
static inline HI_VOID ARGB1555_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    if (NULL == OutBuf)
    {
       return;
    }

    if (JCS_ABGR_1555 == cinfo->out_color_space)
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_RGBA5551(Alpha,Red,Green,Blue);
       return;
    }

    if (JCS_ARGB_1555 == cinfo->out_color_space)
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_BGRA5551(Alpha,Red,Green,Blue);
       return;
    }

    if (JCS_BGRA_5551 == cinfo->out_color_space)
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_ARGB1555(Alpha,Red,Green,Blue);
       return;
    }

    /**<-- JCS_RGBA_5551 >**/
    *(INT16*)OutBuf = CONVERT_PACK_SHORT_ABGR1555(Alpha,Red,Green,Blue);

    return;
}

static HI_VOID JPEG_SDEC_YCC_ARGB1555_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB1555_Convert(cinfo,OutBuf,Red,Green,Blue,0X1);
    return;
}

static HI_VOID JPEG_SDEC_GRAY_ARGB1555_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB1555_Convert(cinfo,OutBuf,Red,Green,Blue,0X1);
    return;
}

static HI_VOID JPEG_SDEC_YCCK_ARGB1555_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB1555_Convert(cinfo,OutBuf,Red,Green,Blue,0X1);
    return;
}

static HI_VOID JPEG_SDEC_CMYK_ARGB1555_Convert(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    register HI_U32 R = 0, G = 0, B = 0;

    R =  MulDiv255Round(Red,Alpha);
    G =  MulDiv255Round(Green,Alpha);
    B =  MulDiv255Round(Blue,Alpha);
    ARGB1555_Convert(cinfo,OutBuf,R,G,B,0XFF);
    return;
}


/*****************************************************************************
* func              : JPEG_SDEC_SupportARGB1555
* description    : decode output argb1555
                          CNcomment:解码输出格式为argb1555CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_SupportARGB1555(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (  (JCS_ABGR_1555 != cinfo->out_color_space) && (JCS_ARGB_1555 != cinfo->out_color_space)
        &&(JCS_BGRA_5551 != cinfo->out_color_space) && (JCS_RGBA_5551 != cinfo->out_color_space))
    {
        return HI_FAILURE;
    }

    cinfo->out_color_components = 2;

    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCC_ConVert  = JPEG_SDEC_YCC_ARGB1555_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_GRAY_ConVert = JPEG_SDEC_GRAY_ARGB1555_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCCK_ConVert = JPEG_SDEC_YCCK_ARGB1555_Convert;
    pJpegHandle->stSdecColorConvert.JPEG_SDEC_CMYK_ConVert = JPEG_SDEC_CMYK_ARGB1555_Convert;

    return HI_SUCCESS;
}
