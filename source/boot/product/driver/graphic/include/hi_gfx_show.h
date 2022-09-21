/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_show.h
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : show input data from base through vo or gfx layer
                          CNcomment: 通过图形层或者视频层将输入的数据显示出来 CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                     sdk                          Created file
******************************************************************************/

#ifndef  __HI_GFX_SHOW_H__
#define  __HI_GFX_SHOW_H__


/*********************************add include here******************************/

#include "hi_type.h"

/***************************** Macro Definition ******************************/

#define CONFIG_GFX_DISP_LOGO_SD        0
#define CONFIG_GFX_DISP_LOGO_HD        1
#define CONFIG_GFX_DISP_LOGO_CHANNEL   2

/*************************** Structure Definition ****************************/
typedef enum hiGfxPixelFormatE
{
    HI_GFX_PF_4444       = 3,
    HI_GFX_PF_0444       = 4,
    HI_GFX_PF_1555       = 5,
    HI_GFX_PF_0555       = 6,
    HI_GFX_PF_565        = 7,
    HI_GFX_PF_8565       = 8,
    HI_GFX_PF_8888       = 9,
    HI_GFX_PF_0888       = 10,
    HI_GFX_PF_YUV400     = 11,
    HI_GFX_PF_YUV420     = 12,
    HI_GFX_PF_YUV444     = 13,
    HI_GFX_PF_YUV422_12  = 14,
    HI_GFX_PF_YUV422_21  = 15,
    HI_GFX_PF_AYCbCr8888 = 16,
    HI_GFX_PF_BUTT
}HI_GFX_PF_E;

typedef struct hiBaseGfxLogoInfoS
{
    HI_BOOL DispToSD;
    HI_U32 LogoDataLen;
    HI_U32 LogoDataBuf;
    HI_U32 DispVirtScreenWidth[CONFIG_GFX_DISP_LOGO_CHANNEL];
    HI_U32 DispVirtScreenHeight[CONFIG_GFX_DISP_LOGO_CHANNEL];
    HI_GFX_PF_E DispColorFmt[CONFIG_GFX_DISP_LOGO_CHANNEL];
}HI_BASE_GFX_LOGO_INFO;

/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

/***************************************************************************************
* func             :  HI_GFX_ShowLogo
* description   :  display the input logo by graphic or vo
                         CNcomment: 通过图形层或者视屏层将输入的logo的数据显示处理CNend\n
* param[in]    : pInputBaseLogoInfo
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32  HI_GFX_ShowLogo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo);


#endif /*__HI_GFX_SHOW_H__ */
