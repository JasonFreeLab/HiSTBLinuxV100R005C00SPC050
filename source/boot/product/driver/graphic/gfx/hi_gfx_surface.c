/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_surface.c
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       :
                          CNcomment:surface管理CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                     sdk                          Created file
******************************************************************************/


/*********************************add include here******************************/
#include "hi_gfx_surface.h"
#include "hi_gfx_mem.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_sys.h"

/************************** Macro Definition     *********************************/

/************************** Structure Definition *********************************/

/************************** Global Variable declaration **************************/

/************************** Api declaration **************************************/

/************************** API realization **************************************/

/*****************************************************************************
* func            : HI_BOOT_GFX_CreateDecSurface
* description  : 创建解码surface
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_S32 HI_BOOT_GFX_CreateDecSurface(HI_HANDLE hSurface)
{

    HI_U32 u32YMemSize  = 0;
    HI_U32 u32UMemSize  = 0;
    HI_U32 u32VMemSize  = 0;
    HI_U32 u32TotalSize = 0;

    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);

    u32YMemSize  = pstSurface->u32Size[0];
    u32UMemSize  = pstSurface->u32Size[1];
    u32VMemSize  = pstSurface->u32Size[2];
    u32TotalSize = u32YMemSize + u32UMemSize + u32VMemSize;
    if (0 == u32TotalSize)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    pstSurface->pPhyAddr[0] = (HI_CHAR*)HI_GFX_MMZ_Malloc(u32TotalSize, "decode-out-buf");
    CHECK_POINT_NULL(pstSurface->pPhyAddr[0]);

    pstSurface->pVirAddr[0] = pstSurface->pPhyAddr[0];

    pstSurface->pPhyAddr[1] = pstSurface->pPhyAddr[0] + u32YMemSize;
    pstSurface->pVirAddr[1] = pstSurface->pVirAddr[0] + u32YMemSize;

    pstSurface->pPhyAddr[2] = pstSurface->pPhyAddr[1] + u32UMemSize;
    pstSurface->pVirAddr[2] = pstSurface->pVirAddr[1] + u32UMemSize;

#if 0
    HI_GFX_Print("\n=============================================\n");
    HI_GFX_Print("pstSurface->pPhyAddr[0]   = 0x%lx\n",(unsigned long)pstSurface->pPhyAddr[0]);
    HI_GFX_Print("pstSurface->u32Width[0]   = %d\n",pstSurface->u32Width[0]);
    HI_GFX_Print("pstSurface->u32Height[0]  = %d\n",pstSurface->u32Height[0]);
    HI_GFX_Print("pstSurface->u32Stride[0]  = %d\n",pstSurface->u32Stride[0]);
    HI_GFX_Print("pstSurface->enPixelFormat = %d\n",pstSurface->enPixelFormat);
    HI_GFX_Print("u32YMemSize               = %d\n",u32YMemSize);
    HI_GFX_Print("u32TotalSize              = %d\n",u32TotalSize);
    HI_GFX_Print("=============================================\n");
#endif
    return HI_SUCCESS;
}


/*****************************************************************************
* func             : HI_BOOT_GFX_FreeDecSurface
* description   : 释放surface
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_S32 HI_BOOT_GFX_FreeDecSurface(HI_HANDLE hSurface)
{
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);

    if (NULL != pstSurface->pPhyAddr[0])
    {
        HI_GFX_MMZ_Free(pstSurface->pPhyAddr[0]);
        pstSurface->pPhyAddr[0] = NULL;
    }

    if (NULL != pstSurface->pPhyAddr[1])
    {
        HI_GFX_MMZ_Free(pstSurface->pPhyAddr[1]);
        pstSurface->pPhyAddr[1] = NULL;
    }

    if (NULL != pstSurface->pPhyAddr[2])
    {
        HI_GFX_MMZ_Free(pstSurface->pPhyAddr[2]);
        pstSurface->pPhyAddr[2] = NULL;
    }

    HI_GFX_Free((HI_CHAR*)pstSurface);

    return HI_SUCCESS;
}



HI_S32 HI_BOOT_GFX_CreateSurface(HI_U32 Width, HI_U32 Height, HI_GFX_PF_E PixelFormat,HI_HANDLE *pSurface)
{
#ifdef HI_LOADER_BOOTLOADER
    HI_HANDLE hSurface = 0;
    HI_U32 Stride = 0;
    HI_LOGO_SURFACE_S *pstSurface = NULL;
    CHECK_POINT_NULL(pSurface);

    hSurface = (HI_HANDLE)HI_GFX_Malloc(sizeof(HI_LOGO_SURFACE_S),"memory-surface-handle");
    if (0 == hSurface)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    HI_GFX_Memset((HI_VOID*)hSurface,0x0,sizeof(HI_LOGO_SURFACE_S));
    *pSurface = hSurface;

    switch (PixelFormat)
    {
        case HI_GFX_PF_8888:
            Stride = (Width * 4 + 16 - 1) & (~(16 - 1));
            break;
        case HI_GFX_PF_0888:
            Stride = (Width * 3 + 16 - 1) & (~(16 - 1));
            break;
        case HI_GFX_PF_1555:
        case HI_GFX_PF_565:
            Stride = (Width * 2 + 16 - 1) & (~(16 - 1));
            break;
        default:
            HI_GFX_Log();
            HI_GFX_Free((HI_CHAR*)hSurface);
            return HI_FAILURE;
    }

    pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    pstSurface->enPixelFormat = PixelFormat;
    pstSurface->u32Width[0]   = Width;
    pstSurface->u32Height[0]  = Height;
    pstSurface->u32Stride[0]  = Stride;
    pstSurface->u32Size[0]    = Stride * Height;

    if (0 == pstSurface->u32Size[0])
    {
        HI_GFX_Log();
        HI_GFX_Free((HI_CHAR*)hSurface);
        return HI_FAILURE;
    }

    pstSurface->pPhyAddr[0] = (HI_CHAR*)HI_GFX_Malloc(pstSurface->u32Size[0],"surface-buf");
    if (NULL == pstSurface->pPhyAddr[0])
    {
        HI_GFX_Log();
        HI_GFX_Free((HI_CHAR*)hSurface);
        return HI_FAILURE;
    }
    pstSurface->pVirAddr[0] = pstSurface->pPhyAddr[0];
#else
    HI_UNUSED(Width);
    HI_UNUSED(Height);
    HI_UNUSED(PixelFormat);
    HI_UNUSED(pSurface);
#endif

    return HI_SUCCESS;
}


HI_S32 HI_BOOT_GFX_FreeSurface(HI_HANDLE hSurface)
{
#ifdef HI_LOADER_BOOTLOADER
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);

    if (NULL != pstSurface->pPhyAddr[0])
    {
        HI_GFX_Free(pstSurface->pPhyAddr[0]);
        pstSurface->pPhyAddr[0] = NULL;
    }

    if (NULL != pstSurface->pPhyAddr[1])
    {
        HI_GFX_Free(pstSurface->pPhyAddr[1]);
        pstSurface->pPhyAddr[1] = NULL;
    }

    if (NULL != pstSurface->pPhyAddr[2])
    {
        HI_GFX_Free(pstSurface->pPhyAddr[2]);
        pstSurface->pPhyAddr[2] = NULL;
    }

    HI_GFX_Free((HI_CHAR*)pstSurface);
#else
    HI_UNUSED(hSurface);
#endif
    return HI_SUCCESS;
}


HI_S32 HI_BOOT_GFX_GetSurfaceSize(HI_HANDLE hSurface, HI_U32* pWidth, HI_U32* pHeight)
{
#ifdef HI_LOADER_BOOTLOADER
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);

    if (NULL != pWidth)
    {
        *pWidth = pstSurface->u32Width[0];
    }

    if (NULL != pHeight)
    {
        *pHeight = pstSurface->u32Height[0];
    }
#else
    HI_UNUSED(hSurface);
    HI_UNUSED(pWidth);
    HI_UNUSED(pHeight);
#endif
    return HI_SUCCESS;
}


HI_S32 HI_BOOT_GFX_LockSurface(HI_HANDLE hSurface, HI_PIXELDATA pData, HI_BOOL bSync)
{
#ifdef HI_LOADER_BOOTLOADER
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);

    pData[0].Pitch = pstSurface->u32Stride[0];
    pData[0].pPhyData = pstSurface->pPhyAddr[0];

    switch (pstSurface->enPixelFormat)
    {
        case HI_GFX_PF_8888:
            pData[0].Bpp = 4;
            break;
        case HI_GFX_PF_0888:
            pData[0].Bpp = 3;
            break;
        case HI_GFX_PF_1555:
        case HI_GFX_PF_565:
            pData[0].Bpp = 2;
            break;
        default:
            pData[0].Bpp = 4;
            break;
    }

    HI_UNUSED(bSync);
#else
    HI_UNUSED(hSurface);
    HI_UNUSED(pData);
    HI_UNUSED(bSync);
#endif
    return HI_SUCCESS;
}

HI_S32 HI_BOOT_GFX_UnlockSurface(HI_HANDLE hSurface)
{
    HI_UNUSED(hSurface);
    return HI_SUCCESS;
}
