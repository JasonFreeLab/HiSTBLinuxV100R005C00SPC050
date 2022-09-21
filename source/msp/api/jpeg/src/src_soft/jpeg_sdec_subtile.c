/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_subtile.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : sub tile decode
                        区域解码
Function List   :

History           :
Date                          Author                    Modification
2017/03/16           sdk              Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jpeglib.h"
#include "jerror.h"

#include "hi_jpeg_config.h"

#include "jpeg_hdec_api.h"

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/

#ifdef CFG_JPEG_SDEC_SET_CROP
static inline HI_VOID JPEG_SDEC_SetCropXW(j_decompress_ptr cinfo,HI_U32 Crop_X, HI_U32 Crop_Width)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    pJpegHandle->bCrop = HI_TRUE;
    pJpegHandle->stCropRect.x = Crop_X;
    pJpegHandle->stCropRect.w = Crop_Width;

    return;
}

static inline HI_VOID JPEG_SDEC_SetCropYH(j_decompress_ptr cinfo, HI_U32 Crop_Y, HI_U32 Crop_H)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (HI_TRUE != pJpegHandle->SupportHardDec)
    {
       return;
    }

    /**<-- if not support crop, should not set crop_rect >**/
    /**<-- 如果不是区域解码，不需要设置裁剪区域 >**/
    if (HI_TRUE != pJpegHandle->bCrop)
    {
       return;
    }

    /**<-- if decode to user buffer, but not set crop rect, not support >**/
    /**<-- 如果没有设置区域使用解码输出到用户buffer 不支持，因为用户内存不够用 >**/
    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_FALSE == pJpegHandle->bSetCropRect))
    {
       ERREXIT(cinfo, JERR_CROP_CANNOT_SUPPORT);
    }

    if (HI_TRUE == pJpegHandle->bSetCropRect)
    {
       return;
    }

    /**<-- if has been set crop_y, should not set again,  call HI_JPEG_SetCropRect for example >**/
    /**<-- 如果设置了区域大小就不需要重新再设置了 >**/
    if (0 == pJpegHandle->stCropRect.y)
    {
        pJpegHandle->stCropRect.y = Crop_Y;
    }

    if (0 == pJpegHandle->stCropRect.h)
    {
        pJpegHandle->stCropRect.h = Crop_H;
    }

    pJpegHandle->bSetCropRect = HI_TRUE;

    return;
}

#endif


#ifdef CFG_JPEG_SDEC_SET_SKIP
/*****************************************************************************
* func           : JPEG_SDEC_SetSkipLines
* description : set skip lines
                       CNcomment: 设置要忽略的行数
* param[in]  : cinfo              CNcomment: 解码对象   CNend\n
* param[in]  : SkipLines       CNcomment:忽略的行数CNend\n
* others:     : NA
*****************************************************************************/
static inline HI_VOID JPEG_SDEC_SetSkipLines(j_decompress_ptr cinfo, HI_U32 SkipLines)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_FALSE == pJpegHandle->bCrop))
    {/**<-- hard decode support skip decode >**/
       ERREXIT(cinfo, JERR_SKIP_CANNOT_SUPPORT);
    }

    pJpegHandle->SkipLines += SkipLines;

    return;
}

static inline HI_VOID JPEG_SDEC_SetDisScanMark(j_decompress_ptr cinfo, HI_BOOL bDiscardScanlines)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    pJpegHandle->bDiscardScanlines = bDiscardScanlines;

}
#endif
