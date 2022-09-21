/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_decode.h
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : decode images
                          CNcomment: 解码图片 CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                     sdk                        Created file
******************************************************************************/

#ifndef  __HI_GFX_DECODE_H__
#define  __HI_GFX_DECODE_H__


/*********************************add include here******************************/

#include "hi_type.h"

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

/*****************************************************************************
* func	       :  HI_BOOT_GFX_DecImg
* description	:  graphic decode, only support bmp and jpeg decode
                         if want to display for vo, input image should be jpeg, and decode format with yuv420sp.
                         CNcomment:只能支持bmp  和jpeg  两种格式的图片解码，要是使用VO
                         输出，只能使用jpeg 图片，且解码输出的像素格式为yuv420sp。
                         其他情况，jpeg 输出yuv格式，bmp 输出rgb格式。CNend\n
*para[in]        : SrcBuf
*para[in]        : SrcLen
*para[ou]       : DecSurface
* retval		:  HI_SUCCESS
                         HI_FAILURE
* others:		:  NA
*****************************************************************************/
HI_S32 HI_BOOT_GFX_DecImg(HI_U32 SrcBuf, HI_U32 SrcLen, HI_HANDLE *DecSurface);


/*****************************************************************************
* func	       :  HI_BOOT_GFX_IsSupport4KLOGO
* description	:  check whether this decode surface can support 4k output
                         CNcomment:判断这个解码surface是否支持4K输出CNend\n
*para[in]        : DecSurface
*para[ou]       : pSupport4k
* retval		:  HI_SUCCESS
                         HI_FAILURE
* others:		:  NA
*****************************************************************************/
HI_VOID HI_BOOT_GFX_IsSupport4KLOGO(HI_HANDLE DecSurface, HI_BOOL *pSupport4k);

#endif /*__HI_GFX_DECODE_H__ */
