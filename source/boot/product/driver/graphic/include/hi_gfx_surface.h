/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_surface.h
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       :
                          CNcomment:surfaceπ‹¿ÌCNend\n
Function List     :
History             :
Date                               Author                     Modification
2017/06/08                     sdk                         Created file
******************************************************************************/

#ifndef  __HI_GFX_SURFACE_H__
#define  __HI_GFX_SURFACE_H__


/*********************************add include here******************************/

#include "hi_gfx_show.h"
#include "hi_gfx_comm.h"

/***************************** Macro Definition ******************************/

#define  CONFIG_GFX_PIXELDATA_NUM         3

/*************************** Structure Definition ****************************/

typedef struct hiLOGOSURFACE_S
{
    HI_BOOL bVoDispSupport;
    HI_U32  u32Width[CONFIG_GFX_PIXELDATA_NUM];
    HI_U32  u32Height[CONFIG_GFX_PIXELDATA_NUM];
    HI_U32  u32Stride[CONFIG_GFX_PIXELDATA_NUM];
    HI_U32  u32Size[CONFIG_GFX_PIXELDATA_NUM];
    HI_CHAR* pPhyAddr[CONFIG_GFX_PIXELDATA_NUM];
    HI_CHAR* pVirAddr[CONFIG_GFX_PIXELDATA_NUM];
    HI_GFX_RECT_S stRect;
    HI_GFX_LAYER_ID_E enLayerID;
    HI_GFX_PF_E  enPixelFormat;
}HI_LOGO_SURFACE_S;


typedef struct tagGFX_PIXELDATA_S
{
    HI_VOID* pPhyData;
    HI_U32   Pitch;
    HI_U32 Bpp;
} GFX_PIXELDATA_S;


/********************** Global Variable declaration **************************/
typedef GFX_PIXELDATA_S   HI_PIXELDATA[CONFIG_GFX_PIXELDATA_NUM];

/******************************* API declaration *****************************/
HI_S32 HI_BOOT_GFX_CreateDecSurface(HI_HANDLE hSurface);
HI_S32 HI_BOOT_GFX_FreeDecSurface(HI_HANDLE hSurface);
HI_S32 HI_BOOT_GFX_CreateSurface(HI_U32 Width, HI_U32 Height, HI_GFX_PF_E PixelFormat,HI_HANDLE *pSurface);
HI_S32 HI_BOOT_GFX_FreeSurface(HI_HANDLE hSurface);
HI_S32 HI_BOOT_GFX_GetSurfaceSize(HI_HANDLE hSurface, HI_U32* pWidth, HI_U32* pHeight);
HI_S32 HI_BOOT_GFX_LockSurface(HI_HANDLE hSurface, HI_PIXELDATA pData, HI_BOOL bSync);
HI_S32 HI_BOOT_GFX_UnlockSurface(HI_HANDLE hSurface);


#endif /*__HI_GFX_SURFACE_H__ */
