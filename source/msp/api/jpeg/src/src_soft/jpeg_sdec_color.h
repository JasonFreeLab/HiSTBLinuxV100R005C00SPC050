/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_color.h
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     :
Function List   :


History           :
Date                      Author                   Modification
2017/07/05            sdk                        Created file
******************************************************************************/

#ifndef __JPEG_SDEC_COLORSPACE_H__
#define __JPEG_SDEC_COLORSPACE_H__

/*********************************add include here********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jpeglib.h"
#include "hi_jpeg_config.h"


/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition *******************************/

    #define SkMulS16(x, y)  ((x) * (y))

    /*************************** Structure Definition *******************************/
    typedef struct tagJPEG_SDEC_COLOR_CONVERT_S
    {
      HI_VOID (*JPEG_SDEC_YCC_ConVert)(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue);
      HI_VOID (*JPEG_SDEC_GRAY_ConVert)(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue);
      HI_VOID (*JPEG_SDEC_YCCK_ConVert)(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue);
      HI_VOID (*JPEG_SDEC_CMYK_ConVert)(j_decompress_ptr cinfo, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha);
    }JPEG_SDEC_COLOR_CONVERT_S;

    /***************************  The enum of Jpeg image format  ********************/


    /********************** Global Variable declaration ******************************/


    /******************************* API declaration ******************************/
    static inline HI_U8 MulDiv255Round(HI_U16 a, HI_U16 b)
    {
    	if ((a > 32767) || (b > 32767))
    	{
    		return 0;
    	}

    	unsigned prod = SkMulS16(a, b) + 128;

    	return (prod + (prod >> 8)) >> 8;
    }

    /**************************************************************************/

    #ifdef __cplusplus
        #if __cplusplus
}
        #endif
   #endif /* __cplusplus */
#endif /* __JPEG_SDEC_COLORSPACE_H__*/
