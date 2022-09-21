/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_show.c
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


/************************** add include here**************************************/
#include "hi_gfx_show.h"
#include "hi_gfx_comm.h"

#include "hi_gfx_surface.h"
#include "hi_gfx_decode.h"
#include "hi_gfx_layer.h"

/************************** Macro Definition     *********************************/


/************************** Structure Definition *********************************/

/************************** Global Variable declaration **************************/


/************************** Api declaration **************************************/


/************************** API realization **************************************/


/***************************************************************************************
* func             : HI_GFX_ShowLogo
* description   :  display the input logo by graphic or vo
                         CNcomment: 通过图形层或者视屏层将输入的logo的数据显示处理CNend\n
* param[in]    : pInputBaseLogoInfo
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32  HI_GFX_ShowLogo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_HANDLE DecSurface = HI_GFX_INVALID_HANDLE;

     CHECK_POINT_NULL(pInputBaseLogoInfo);

     Ret = HI_BOOT_GFX_DecImg(pInputBaseLogoInfo->LogoDataBuf,pInputBaseLogoInfo->LogoDataLen,&DecSurface);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_Log();
         HI_BOOT_GFX_FreeDecSurface(DecSurface);
         return HI_FAILURE;
     }

     Ret = HI_BOOT_GFX_DisplayWithLayerOrVo(pInputBaseLogoInfo,DecSurface);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_Log();
         goto ERR_EXIT_ONE;
     }

     if (HI_GFX_INVALID_HANDLE != DecSurface)
     {
        HI_BOOT_GFX_FreeDecSurface(DecSurface);
     }

     return HI_SUCCESS;

   ERR_EXIT_ONE:

     if (HI_GFX_INVALID_HANDLE != DecSurface)
     {
        HI_BOOT_GFX_FreeDecSurface(DecSurface);
     }

     return HI_FAILURE;
}
