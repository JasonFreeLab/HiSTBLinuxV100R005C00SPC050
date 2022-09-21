/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_layer.h
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : display through gfx layer or vo
                          CNcomment: 显示输出处理CNend\n
Function List     :
History             :
Date                              Author                     Modification
2017/06/08                    sdk                          Created file
******************************************************************************/

#ifndef  __HI_GFX_LAYER_H__
#define  __HI_GFX_LAYER_H__


/*********************************add include here******************************/

#include "hi_type.h"
#include "hi_gfx_comm.h"

/***************************** Macro Definition ******************************/

#define CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH     4096
#define CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH           3840
#define CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT          2160

/** 这个要和驱动保持一致，否则无法释放 **/
#define DISPLAY_BUFFER_HD           "HIFB_DispBuf_HD"
#define DISPLAY_BUFFER_SD           "HIFB_DispBuf_SD"
#define HI_GFX_LAYER_MAXCOUNT       6
/*************************** Structure Definition ****************************/
typedef struct hiFbAlpha_S
{
    HI_BOOL bAlphaEnable;
    HI_BOOL bAlphaChannel;
    HI_U8 u8Alpha0;
    HI_U8 u8Alpha1;
    HI_U8 u8GlobalAlpha;
    HI_U8 u8Reserved;
}HI_FB_ALPHA_S;

typedef struct hiGfxDisplayInfo_S
{
    HI_U32 u32Stride;
    HI_U32 u32ScreenAddr;
    HI_RECT stInRect;
    HI_RECT stOutRect;
    HI_FB_ALPHA_S stAlpha;
}HI_GFX_DISPLAY_INFO_S;

/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/
/*****************************************************************************
* func	       :  HI_BOOT_GFX_DisplayWithLayerOrVo
* description	:  CNcomment: 使用图形层或者视频层显示CNend\n
*para[in]        : pInputBaseLogoInfo
*para[in]        : DecSurface
* retval		:  HI_SUCCESS
                         HI_FAILURE
* others:		:  NA
*****************************************************************************/
HI_S32 HI_BOOT_GFX_DisplayWithLayerOrVo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_HANDLE DecSurface);



#endif /*__HI_GFX_LAYER_H__ */
