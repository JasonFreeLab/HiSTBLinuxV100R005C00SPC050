/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_blit.h
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : display through gfx layer or vo
                          CNcomment: 2D加速CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                      sdk                        Created file
******************************************************************************/

#ifndef  __HI_GFX_BLIT_H__
#define  __HI_GFX_BLIT_H__


/*********************************add include here******************************/

#include "hi_type.h"

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/
typedef struct hiGFXBLTOPT_S
{
   HI_BOOL EnableScale;
}HI_GFX_BLTOPT_S;


typedef enum hiGFXCOMPOPT_E
{
    HI_GFX_COMPOPT_NONE = 0,
    HI_GFX_COMPOPT_BUTT
}HI_GFX_COMPOPT_E;

/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/
/*****************************************************************************
* func            : HI_BOOT_GFX2D_Init
* description  : 2d加速初始化
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_S32 HI_BOOT_GFX2D_Init(HI_VOID);


/*****************************************************************************
* func            : HI_BOOT_GFX2D_FillRect
* description  : 填充矩形
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_S32 HI_BOOT_GFX2D_FillRect(HI_HANDLE hSurface, const HI_RECT* pstRect, HI_U32 u32Color, HI_GFX_COMPOPT_E eComPopt);


/*****************************************************************************
* func            : HI_BOOT_GFX2D_Blit
* description  : 2d叠加操作
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_S32 HI_BOOT_GFX2D_Blit(HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,HI_HANDLE DstSurface, const HI_RECT* pDstRect, const HI_GFX_BLTOPT_S* pBlitOpt);


#endif /*__HI_GFX_BLIT_H__ */
