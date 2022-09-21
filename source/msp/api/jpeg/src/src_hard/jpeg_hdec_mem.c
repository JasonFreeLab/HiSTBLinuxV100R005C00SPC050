/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_mem.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : memory alloc
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                 sdk                       Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jerror.h"

#include  "hi_gfx_sys.h"
#include  "hi_jpeg_config.h"
#include  "hi_jpeg_checkpara.h"

#include  "jpeg_hdec_mem.h"
#include  "jpeg_hdec_api.h"

#include  "hi_gfx_comm.h"

/***************************** Macro Definition ***********************************/
#ifdef CONFIG_GFX_MMU_SUPPORT
#define MMZ_TAG          "iommu"
#else
#define MMZ_TAG          "mmz"
#endif

#define INPUT_DATA_MODULE       "JPEG_INPUT_DATA_BUF"
#define DEC_YUVSP_MODULE        "JPEG_DECODE_YUVSP_BUF"
#define DEC_XRGB_MODULE         "JPEG_DECODE_XRGB_BUF"
#define DEC_XRGB_MIN_MODULE     "JPEG_DECODE_XRGB_MIN_BUF"

/***************************** Structure Definition *********************************/

/***************************** Global Variable declaration ***************************/

/***************************** API forward declarations *****************************/
static HI_S32 JPEG_HDEC_AllocInputDataBuf(j_decompress_ptr cinfo, const HI_U32 InputDataSize);
static HI_VOID JPEG_HDEC_FreeInputDataBuf(j_decompress_ptr cinfo);
static HI_S32 JPEG_HDEC_AllocYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_VOID JPEG_HDEC_FreeYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_S32 JPEG_HDEC_AllocXRGBMem(const struct jpeg_decompress_struct *cinfo);
static HI_VOID JPEG_HDEC_FreeXRGBMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);

#ifdef CONFIG_JPEG_HARDDEC2ARGB
static HI_S32 JPEG_HDEC_GetMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_VOID JPEG_HDEC_FreeMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
#endif

extern HI_BOOL JPEG_SDEC_InputBufferIsPhyMem(j_decompress_ptr cinfo);

/***************************** API realization *************************************/
HI_BOOL JPEG_HDEC_AllocDecodeMemory(j_decompress_ptr cinfo)
{
    HI_S32 Ret = HI_SUCCESS;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FALSE);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(NULL, pJpegHandle, HI_FALSE);

    Ret = JPEG_HDEC_AllocInputDataBuf(cinfo,(CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE) * CONFIG_JPED_INPUT_DATA_BUFFER_NUM);
    CHECK_JPEG_UNEQUAL_RETURN(HI_SUCCESS, Ret, HI_FALSE);

    Ret = JPEG_HDEC_AllocYUVMem(pJpegHandle);
    CHECK_JPEG_UNEQUAL_RETURN(HI_SUCCESS, Ret, HI_FALSE);

#ifdef CONFIG_JPEG_HARDDEC2ARGB
    Ret = JPEG_HDEC_GetMinMem(pJpegHandle);
    CHECK_JPEG_UNEQUAL_RETURN(HI_SUCCESS, Ret, HI_FALSE);
#endif

    Ret = JPEG_HDEC_AllocXRGBMem(cinfo);
    CHECK_JPEG_UNEQUAL_RETURN(HI_SUCCESS, Ret, HI_FALSE);

    return HI_TRUE;
}


HI_VOID JPEG_HDEC_FreeDecodeMemory(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);

    JPEG_HDEC_FreeInputDataBuf(cinfo);

    JPEG_HDEC_FreeYUVMem(pJpegHandle);

#ifdef CONFIG_JPEG_HARDDEC2ARGB
    JPEG_HDEC_FreeMinMem(pJpegHandle);
#endif

    JPEG_HDEC_FreeXRGBMem(pJpegHandle);

    return;
}


/*****************************************************************************
* func              : JPEG_HDEC_AllocInputDataBuf
* description    : alloc input data buffer memory
                          CNcomment:  分配输入码流buffer CNend\n
* param[in]     : cinfo    CNcomment: 解码器句柄 CNend\n
* param[in]     : InputDataSize   CNcomment: 分配输入码流总大小 CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功           CNend\n
* retval           : HI_FAILURE  CNcomment:  失败             CNend\n
* others:        : NA
*****************************************************************************/
static HI_S32 JPEG_HDEC_AllocInputDataBuf(j_decompress_ptr cinfo, const HI_U32 InputDataSize)
{
    HI_U32 SaveStreamPhyBuf = 0;
    HI_U32 SaveStreamBufIndex = 0;
    HI_CHAR* pSaveStreamVirBuf = NULL;
    HI_BOOL bMemMMUType  = HI_TRUE;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    CHECK_JPEG_EQUAL_RETURN(0, InputDataSize, HI_FAILURE);
    CHECK_JPEG_EQUAL_RETURN(HI_TRUE, JPEG_SDEC_InputBufferIsPhyMem(cinfo), HI_SUCCESS);

#ifdef CONFIG_GFX_MEM_ION
    SaveStreamPhyBuf = HI_GFX_AllocMem(pJpegHandle->MemDev,InputDataSize, CONFIG_JPEG_INPUT_DATA_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)INPUT_DATA_MODULE, &(pJpegHandle->pSaveStreamMemHandle),&bMemMMUType);
#else
    SaveStreamPhyBuf = HI_GFX_AllocMem(InputDataSize, CONFIG_JPEG_INPUT_DATA_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)INPUT_DATA_MODULE, &bMemMMUType);
#endif
    CHECK_JPEG_EQUAL_RETURN(0, SaveStreamPhyBuf, HI_FAILURE);

    for (SaveStreamBufIndex = 0; SaveStreamBufIndex < CONFIG_JPED_INPUT_DATA_BUFFER_NUM; SaveStreamBufIndex++)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].SaveStreamPhyBuf = SaveStreamPhyBuf + SaveStreamBufIndex * (CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE);
    }

#ifdef CONFIG_GFX_MEM_ION
    pSaveStreamVirBuf = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->MemDev,SaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
#else
    pSaveStreamVirBuf = (HI_CHAR*)HI_GFX_MapCached(SaveStreamPhyBuf, bMemMMUType);
#endif
    CHECK_JPEG_EQUAL_RETURN(NULL, pSaveStreamVirBuf, HI_FAILURE);

    pJpegHandle->stInputDataBufInfo.SaveStreamBufSize = CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE;

    for (SaveStreamBufIndex = 0; SaveStreamBufIndex < CONFIG_JPED_INPUT_DATA_BUFFER_NUM; SaveStreamBufIndex++)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].pSaveStreamVirBuf = (HI_CHAR*)(pSaveStreamVirBuf + SaveStreamBufIndex * (CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE));
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, bMemMMUType, HI_FAILURE);
#endif

    return HI_SUCCESS;
}


static HI_VOID JPEG_HDEC_FreeInputDataBuf(j_decompress_ptr cinfo)
{
    HI_U32 SaveStreamBufIndex = 0;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    CHECK_JPEG_EQUAL_UNRETURN(HI_TRUE, JPEG_SDEC_InputBufferIsPhyMem(cinfo));
    CHECK_JPEG_EQUAL_UNRETURN(0, pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf);

#ifdef CONFIG_GFX_MEM_ION
    if (NULL != pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf)
    {
       (HI_VOID)HI_GFX_Unmap(pJpegHandle->MemDev,pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
    }
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle,HI_TRUE);
#else
    if (NULL != pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf)
    {
       (HI_VOID)HI_GFX_Unmap(pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, HI_TRUE);
    }
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, HI_TRUE);
#endif

    pJpegHandle->stInputDataBufInfo.SaveStreamBufSize = 0;
    for (SaveStreamBufIndex = 0; SaveStreamBufIndex < CONFIG_JPED_INPUT_DATA_BUFFER_NUM; SaveStreamBufIndex++)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].SaveStreamPhyBuf = 0;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].pSaveStreamVirBuf = NULL;
    }

    return;
}


/*****************************************************************************
* func              : JPEG_HDEC_AllocYUVMem
* description    : alloc yuv output memory
                          CNcomment:  分配硬件解码输出码流CNend\n
* param[in]     : pJpegHandle    CNcomment: 解码器句柄 CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功           CNend\n
* retval           : HI_FAILURE  CNcomment:  失败             CNend\n
* others:        : NA
*****************************************************************************/
static HI_S32 JPEG_HDEC_AllocYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 u32MemSize   = 0;
    HI_U32 DecOutPhy    = 0;
    HI_U32 u32Align     = JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN;
    HI_BOOL bMemMMUType = HI_TRUE;

    /**<-- decode xrgb, should not alloc yuvsp buffer >**/
    /**<-- 解码输出XRGB，不需要分配yuv sp buffer >**/
    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {
       return HI_SUCCESS;
    }

    /**<-- output to user buffer >**/
    /**<-- 输出到用户内存>**/
    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_TRUE == pJpegHandle->bOutYCbCrSP))
    {
          pJpegHandle->stDecSurface.DecOutPhy[0] = pJpegHandle->stOutSurface.u32OutPhy[0];
          pJpegHandle->stDecSurface.DecOutPhy[1] = pJpegHandle->stOutSurface.u32OutPhy[1];
          pJpegHandle->stDecSurface.DecOutPhy[2] = pJpegHandle->stOutSurface.u32OutPhy[2];
          pJpegHandle->stDecSurface.DecOutVir[0] = pJpegHandle->stOutSurface.pOutVir[0];
          pJpegHandle->stDecSurface.DecOutVir[1] = pJpegHandle->stOutSurface.pOutVir[1];
          pJpegHandle->stDecSurface.DecOutVir[2] = pJpegHandle->stOutSurface.pOutVir[2];
          return HI_SUCCESS;
    }

    u32MemSize = pJpegHandle->stJpegSofInfo.u32YSize + pJpegHandle->stJpegSofInfo.u32CSize;

#ifdef CONFIG_GFX_MEM_ION
    DecOutPhy = HI_GFX_AllocMem(pJpegHandle->MemDev,u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_YUVSP_MODULE, &(pJpegHandle->pMiddleMemHandle),&bMemMMUType);
#else
    DecOutPhy = HI_GFX_AllocMem(u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_YUVSP_MODULE, &bMemMMUType);
#endif
    CHECK_JPEG_EQUAL_RETURN(0, DecOutPhy, HI_FAILURE);

    pJpegHandle->stDecSurface.DecOutPhy[0] = DecOutPhy;
    pJpegHandle->stDecSurface.DecOutPhy[1] = DecOutPhy + pJpegHandle->stJpegSofInfo.u32YSize;

#ifdef CONFIG_GFX_MMU_SUPPORT
    CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, bMemMMUType, HI_FAILURE);
#endif

    return HI_SUCCESS;
}


/*****************************************************************************
* func             : JPEG_HDEC_FreeYUVMem
* description   : free the hard decode output mem
                         CNcomment: 释放硬件解码输出的地址  CNend\n
* param[in]    : pJpegHandle   CNcomment: 解码器句柄 CNend\n
* retval          : NA
* others:       : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_FreeYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    CHECK_JPEG_EQUAL_UNRETURN(HI_TRUE, pJpegHandle->bDecOutColorSpaecXRGB);
    CHECK_JPEG_EQUAL_UNRETURN(0, pJpegHandle->stDecSurface.DecOutPhy[0]);

    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_TRUE == pJpegHandle->bOutYCbCrSP))
    {
       return;
    }

#ifdef CONFIG_GFX_MEM_ION
   (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->stDecSurface.DecOutPhy[0], pJpegHandle->pMiddleMemHandle,HI_TRUE);
#else
   (HI_VOID)HI_GFX_FreeMem(pJpegHandle->stDecSurface.DecOutPhy[0], HI_TRUE);
#endif

    pJpegHandle->stDecSurface.DecOutPhy[0]  = 0;
    pJpegHandle->stDecSurface.DecOutPhy[1]  = 0;
    pJpegHandle->stDecSurface.DecOutVir[0]  = NULL;
    pJpegHandle->stDecSurface.DecOutVir[1]  = NULL;

    return;
}


/*****************************************************************************
* func              : JPEG_HDEC_GetMinMem
* description    : alloc min buffer
                          CNcomment:  解码输出ARGB 的中间buffer CNend\n
* param[in]     : pJpegHandle    CNcomment: 解码器句柄 CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功           CNend\n
* retval           : HI_FAILURE  CNcomment:  失败             CNend\n
* others:        : NA
*****************************************************************************/
#ifdef CONFIG_JPEG_HARDDEC2ARGB
static HI_S32 JPEG_HDEC_GetMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 u32MemSize   = pJpegHandle->stJpegSofInfo.u32RGBSizeReg;
    HI_BOOL bMemMMUType = HI_TRUE;

    CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, pJpegHandle->bDecOutColorSpaecXRGB,HI_SUCCESS);

    #ifdef CONFIG_GFX_MEM_ION
      pJpegHandle->u32MinPhyBuf = HI_GFX_AllocMem(pJpegHandle->MemDev,u32MemSize,JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_XRGB_MIN_MODULE, &(pJpegHandle->pMinMemHandle),&bMemMMUType);
    #else
      pJpegHandle->u32MinPhyBuf = HI_GFX_AllocMem(u32MemSize,JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_XRGB_MIN_MODULE, &bMemMMUType);
    #endif
    CHECK_JPEG_EQUAL_RETURN(0, pJpegHandle->u32MinPhyBuf, HI_FAILURE);

    #ifdef CONFIG_GFX_MMU_SUPPORT
      CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, bMemMMUType, HI_FAILURE);
    #endif

    return HI_SUCCESS;
}

static HI_VOID JPEG_HDEC_FreeMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);
    CHECK_JPEG_UNEQUAL_UNRETURN(HI_TRUE, pJpegHandle->bDecOutColorSpaecXRGB);
    CHECK_JPEG_EQUAL_UNRETURN(0, pJpegHandle->u32MinPhyBuf);

    #ifdef CONFIG_GFX_MEM_ION
      (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->u32MinPhyBuf, pJpegHandle->pMinMemHandle,HI_TRUE);
    #else
      (HI_VOID)HI_GFX_FreeMem(pJpegHandle->u32MinPhyBuf,HI_TRUE);
    #endif

    pJpegHandle->u32MinPhyBuf  = 0;

    return;
}
#endif


/*****************************************************************************
* func              : JPEG_HDEC_AllocXRGBMem
* description    : alloc xrgb buffer
                          CNcomment: TDE 转换的输出buffer CNend\n
* param[in]     : pJpegHandle    CNcomment: 解码器句柄 CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功           CNend\n
* retval           : HI_FAILURE  CNcomment:  失败             CNend\n
* others:        : NA
*****************************************************************************/
static HI_S32 JPEG_HDEC_AllocXRGBMem(const struct jpeg_decompress_struct *cinfo)
{
    HI_BOOL bMemMMUType = HI_TRUE;
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32OutStride = 0;
    HI_U32 u32MemSize   = 0;
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    CHECK_JPEG_EQUAL_RETURN(HI_TRUE, pJpegHandle->bOutYCbCrSP,HI_SUCCESS);

    if (HI_TRUE == pJpegHandle->bOutUsrBuf)
    {
        pJpegHandle->stDecSurface.OutPhy = pJpegHandle->stOutSurface.u32OutPhy[0];
        pJpegHandle->stDecSurface.pOutVir = pJpegHandle->stOutSurface.pOutVir[0];
        return HI_SUCCESS;
    }

    u32OutStride = pJpegHandle->stJpegSofInfo.DecOutStride;
    u32MemSize = u32OutStride * ((HI_U32)pJpegHandle->stCropRect.h);

#ifdef CONFIG_GFX_MEM_ION
    pJpegHandle->stDecSurface.OutPhy = HI_GFX_AllocMem(pJpegHandle->MemDev,u32MemSize, JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)DEC_XRGB_MODULE, &(pJpegHandle->pOutMemHandle),&bMemMMUType);
#else
    pJpegHandle->stDecSurface.OutPhy = HI_GFX_AllocMem(u32MemSize, JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)DEC_XRGB_MODULE, &bMemMMUType);
#endif
    CHECK_JPEG_EQUAL_RETURN(0, pJpegHandle->stDecSurface.OutPhy, HI_FAILURE);

#ifdef CONFIG_GFX_MEM_ION
    pJpegHandle->stDecSurface.pOutVir = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->MemDev,pJpegHandle->stDecSurface.OutPhy, pJpegHandle->pOutMemHandle);
#else
    pJpegHandle->stDecSurface.pOutVir = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->stDecSurface.OutPhy, bMemMMUType);
#endif
    CHECK_JPEG_EQUAL_RETURN(NULL, pJpegHandle->stDecSurface.pOutVir, HI_FAILURE);

#ifdef CONFIG_GFX_MEM_ION
    Ret = HI_GFX_Flush(pJpegHandle->MemDev,pJpegHandle->stDecSurface.OutPhy, pJpegHandle->pOutMemHandle);
#else
    Ret = HI_GFX_Flush(pJpegHandle->stDecSurface.OutPhy, bMemMMUType);
#endif
    CHECK_JPEG_UNEQUAL_RETURN(HI_SUCCESS, Ret, HI_FAILURE);

#ifdef CONFIG_GFX_MMU_SUPPORT
    CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, bMemMMUType, HI_FAILURE);
#endif

    return HI_SUCCESS;
}


static HI_VOID JPEG_HDEC_FreeXRGBMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);
    CHECK_JPEG_EQUAL_UNRETURN(HI_TRUE, pJpegHandle->bOutYCbCrSP);
    CHECK_JPEG_EQUAL_UNRETURN(HI_TRUE, pJpegHandle->bOutUsrBuf);
    CHECK_JPEG_EQUAL_UNRETURN(0, pJpegHandle->stDecSurface.OutPhy);

#ifdef CONFIG_GFX_MEM_ION
    (HI_VOID)HI_GFX_Unmap(pJpegHandle->MemDev,pJpegHandle->stDecSurface.OutPhy, pJpegHandle->pOutMemHandle);
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->stDecSurface.OutPhy, pJpegHandle->pOutMemHandle,HI_TRUE);
#else
    (HI_VOID)HI_GFX_Unmap(pJpegHandle->stDecSurface.OutPhy, HI_TRUE);
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->stDecSurface.OutPhy, HI_TRUE);
#endif

    pJpegHandle->stDecSurface.OutPhy  = 0;
    pJpegHandle->stDecSurface.pOutVir = NULL;

    return;
}

HI_VOID JPEG_HDEC_FlushBuf(j_decompress_ptr cinfo, HI_U32 PhyAddr)
{
#ifdef CONFIG_GFX_MEM_ION
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_API_MODULE_DEFINE_HANDLE();
    (HI_VOID)HI_GFX_Flush(pJpegHandle->MemDev,PhyAddr, pJpegHandle->pSaveStreamMemHandle);
#else
    (HI_VOID)HI_GFX_Flush(PhyAddr, HI_TRUE);
#endif

    return;
}


#ifdef CONFIG_GFX_MEM_ION
HI_S32 JPEG_HDEC_OpenMemDev(HI_VOID)
{
    return gfx_mem_open();
}

HI_VOID JPEG_HDEC_CloseMemDev(HI_S32 Device)
{
    gfx_mem_close(Device);
}
#endif
