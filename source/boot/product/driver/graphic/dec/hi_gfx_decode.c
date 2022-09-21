/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_decode.c
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : decode images
                          CNcomment: 解码图片 CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                      sdk                        Created file
******************************************************************************/


/***************************** add include here*********************************/
#include "jpeg_decode.h"
#include "bmp_decode.h"

#include "hi_gfx_comm.h"
#include "hi_gfx_mem.h"
#include "hi_gfx_decode.h"
#include "hi_gfx_surface.h"
#include "hi_gfx_layer.h"
#include "hi_gfx_sys.h"

#include "hi_drv_disp.h"
#include "drv_disp_ext.h"

/***************************** Macro Definition ********************************/


/***************************** Structure Definition ****************************/
typedef enum tagGFX_IMGTYPE_E
{
    DEC_IMGTYPE_JPEG = 0,
    DEC_IMGTYPE_BMP,
    DEC_IMGTPYE_BUTT
}GFX_IMGTYPE_E;

typedef struct tagGFX_DEC_INSTANCE_S
{
    HI_U32  DecHandle;
    HI_S32 (*CreateDecode)  (HI_U32 *puDecHandle,HI_CHAR* pSrcBuf,HI_U32 u32SrcLen);
    HI_S32 (*DestroyDecode) (HI_U32 DecHandle);
    HI_S32 (*GetImageInfo)  (HI_U32 DecHandle, HI_HANDLE hSurface);
    HI_S32 (*StartDecode)   (HI_U32 DecHandle, HI_HANDLE hSurface);
}GFX_DEC_INSTANCE_S;

/***************************** Global Variable declaration *********************/

/***************************** API forward declarations ************************/

static GFX_IMGTYPE_E GetImageType(HI_CHAR* pSrcAddr);
static HI_S32 GFX_CreateDecode(HI_HANDLE *pDecHandle,HI_CHAR* pSrcAddr,HI_U32 u32SrcLen);
static HI_S32 GFX_StartDecode(HI_HANDLE DecHandle,HI_HANDLE *pSurface);
static HI_S32 GFX_DestroyDecode(HI_HANDLE DecHandle);

/***************************** API realization *********************************/

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
HI_S32 HI_BOOT_GFX_DecImg(HI_U32 SrcBuf, HI_U32 SrcLen, HI_HANDLE *DecSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_HANDLE hDecHandle = HI_GFX_INVALID_HANDLE;

    if ((0 == SrcBuf) || (SrcLen <= 4) || (NULL == DecSurface))
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    Ret = GFX_CreateDecode(&hDecHandle,(HI_CHAR*)SrcBuf,SrcLen);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    Ret = GFX_StartDecode(hDecHandle, DecSurface);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        (HI_VOID)GFX_DestroyDecode(hDecHandle);
        return HI_FAILURE;
    }

    Ret = GFX_DestroyDecode(hDecHandle);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static HI_S32 GFX_CreateDecode(HI_HANDLE *pDecHandle,HI_CHAR* pSrcAddr,HI_U32 u32SrcLen)
{

    HI_S32 Ret = HI_SUCCESS;
    GFX_IMGTYPE_E ImgType = DEC_IMGTYPE_JPEG;
    GFX_DEC_INSTANCE_S *pstDecInstance = NULL;

    pstDecInstance = (GFX_DEC_INSTANCE_S*)HI_GFX_Malloc(sizeof(GFX_DEC_INSTANCE_S),"decode-handle");
    CHECK_POINT_NULL(pstDecInstance);

    *pDecHandle = (HI_HANDLE)pstDecInstance;
    HI_GFX_Memset((HI_VOID*)pstDecInstance,0x0,sizeof(GFX_DEC_INSTANCE_S));

    ImgType = GetImageType(pSrcAddr);
    if (DEC_IMGTYPE_JPEG == ImgType)
    {
        pstDecInstance->CreateDecode   = JPEG_ADP_CreateDecode;
        pstDecInstance->DestroyDecode  = JPEG_ADP_DestroyDecode;
        pstDecInstance->GetImageInfo   = JPEG_ADP_GetImgInfo;
        pstDecInstance->StartDecode    = JPEG_ADP_StartDecode;
    }
    else if (DEC_IMGTYPE_BMP == ImgType)
    {
        pstDecInstance->CreateDecode   = BMP_ADP_CreateDecode;
        pstDecInstance->DestroyDecode  = BMP_ADP_DestroyDecode;
        pstDecInstance->GetImageInfo   = BMP_ADP_GetImgInfo;
        pstDecInstance->StartDecode    = BMP_ADP_StartDecode;
    }
    else
    {
        HI_GFX_Log();
        goto ERROR_EXIT;
    }

    Ret = pstDecInstance->CreateDecode(&(pstDecInstance->DecHandle),pSrcAddr,u32SrcLen);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        goto ERROR_EXIT;
    }

    return HI_SUCCESS;

ERROR_EXIT:

    if (NULL != pstDecInstance)
    {
        HI_GFX_Free((HI_CHAR*)pstDecInstance);
        pstDecInstance = NULL;
    }

    *pDecHandle = HI_GFX_INVALID_HANDLE;

    return HI_FAILURE;
}


static GFX_IMGTYPE_E GetImageType(HI_CHAR* pSrcAddr)
{
    HI_CHAR HeadInfo[4] = {0};

    HI_GFX_Memcpy(HeadInfo,pSrcAddr,4);

    if ((0xFF == *((HI_U8*)HeadInfo)) && (0xD8 == *((HI_U8*)(HeadInfo + 1))))
    {
        return DEC_IMGTYPE_JPEG;
    }

    if ((0x42 == *((HI_U8*)HeadInfo)) && (0x4d == *((HI_U8*)(HeadInfo + 1))))
    {
        return DEC_IMGTYPE_BMP;
    }

    return DEC_IMGTPYE_BUTT;
};


static HI_S32 GFX_StartDecode(HI_HANDLE DecHandle,HI_HANDLE *pSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_HANDLE hSurface = HI_GFX_INVALID_HANDLE;
    GFX_DEC_INSTANCE_S *pstDecInstance = (GFX_DEC_INSTANCE_S*)DecHandle;
    CHECK_POINT_NULL(pstDecInstance);

    hSurface = (HI_HANDLE)HI_GFX_Malloc(sizeof(HI_LOGO_SURFACE_S),"decode-surface-handle");
    if (NULL == (HI_VOID*)hSurface)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    *pSurface  = hSurface;
    HI_GFX_Memset((HI_VOID*)hSurface,0x0,sizeof(HI_LOGO_SURFACE_S));

    Ret = pstDecInstance->GetImageInfo(pstDecInstance->DecHandle,hSurface);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        goto ERROR_EXIT;
    }

    Ret = HI_BOOT_GFX_CreateDecSurface(hSurface);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        goto ERROR_EXIT;
    }

    Ret = pstDecInstance->StartDecode(pstDecInstance->DecHandle,hSurface);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        goto ERROR_EXIT;
    }

    return HI_SUCCESS;

ERROR_EXIT:

    if (HI_GFX_INVALID_HANDLE != hSurface)
    {
        HI_BOOT_GFX_FreeDecSurface(hSurface);
        HI_GFX_Free((HI_CHAR*)hSurface);
    }

    *pSurface = HI_GFX_INVALID_HANDLE;

    return HI_FAILURE;
}


static HI_S32 GFX_DestroyDecode(HI_HANDLE DecHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    GFX_DEC_INSTANCE_S *pstDecInstance = (GFX_DEC_INSTANCE_S*)DecHandle;
    CHECK_POINT_NULL(pstDecInstance);

    Ret = pstDecInstance->DestroyDecode(pstDecInstance->DecHandle);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_Log();
        return HI_FAILURE;
    }

    HI_GFX_Free((HI_CHAR*)pstDecInstance);

    return HI_SUCCESS;
}


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
HI_VOID HI_BOOT_GFX_IsSupport4KLOGO(HI_HANDLE DecSurface, HI_BOOL *pSupport4k)
{
     HI_DISP_DISPLAY_INFO_S stInfo = {0};
     HI_LOGO_SURFACE_S *pstSrcSurface = (HI_LOGO_SURFACE_S *)DecSurface;
     CHECK_POINT_NULL_UNRETURN(pstSrcSurface);

     HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_1, &stInfo);

     if (   (CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH == pstSrcSurface->u32Width[0] || CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH == pstSrcSurface->u32Width[0])
         && (CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH == stInfo.stFmtResolution.s32Width || CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH == stInfo.stFmtResolution.s32Width)
         && (CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT == pstSrcSurface->u32Height[0])
         && (CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT == stInfo.stFmtResolution.s32Height))
     {
          *pSupport4k = HI_TRUE;
     }
     else
     {
          *pSupport4k = HI_FALSE;
     }

#if 0
     HI_GFX_Print("\n===========================================================\n");
     HI_GFX_Print("========%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
     HI_GFX_Print("the gfx 4k logo support %d\n",*pSupport4k);
     HI_GFX_Print("img size [%d %d], fmt size [%d %d]\n",pstSrcSurface->u32Width[0],pstSrcSurface->u32Height[0],stInfo.stFmtResolution.s32Width,stInfo.stFmtResolution.s32Height);
     HI_GFX_Print("===========================================================\n");
#endif
     return;
}
