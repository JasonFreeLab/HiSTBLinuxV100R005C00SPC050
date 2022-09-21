/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_api.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : control hard decode dispose
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                sdk                         Created file
******************************************************************************/

/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "jpeglib.h"
#include "jpegint.h"
#include "jerror.h"

#include "hi_jpeg_config.h"
#include "hi_jpeg_reg.h"
#include "hi_jpeg_checkpara.h"
#include "hi_gfx_sys.h"

#include "jpeg_hdec_api.h"
#include "jpeg_hdec_mem.h"
#include "jpeg_hdec_rwreg.h"

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/
  typedef struct tagJPEG_DECOMPRESS_RES
  {
      HI_S32 CscDev;
      HI_S32 MMZDev;
      HI_CHAR*   pStreamPhyBuf;
      HI_CHAR*   pStreamVirBuf;
  }JPEG_DECOMPRESS_RES;
/********************** Global Variable declaration ********************************/
JPEG_DECOMPRESS_RES gs_stJpegDecompressRes = {-1, -1, NULL, NULL};

/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
static inline HI_VOID JPEG_HDEC_CloseDev(const struct jpeg_common_struct *cinfo);
static inline HI_VOID JPEG_HDEC_ReleaseRes   (const struct jpeg_common_struct *cinfo);
static inline HI_S32  JPEG_HDEC_SendStream(j_decompress_ptr cinfo);
static inline HI_S32 JPEG_HDEC_OutUserBuf(j_decompress_ptr cinfo, HI_CHAR* ScanlineBuf, HI_U32 MaxLines);


extern HI_VOID JPEG_HDEC_IfSupport(j_decompress_ptr cinfo);
extern HI_VOID JPEG_HDEC_FreeDecodeMemory(j_decompress_ptr cinfo);
extern  HI_S32 JPEG_HDEC_SetPara(const struct jpeg_decompress_struct *cinfo);
extern HI_VOID JPEG_SDEC_GetTimeStamp(HI_U32 *pu32TimeMs, HI_U32 *pu32TimeUs);


#ifdef CONFIG_GFX_MEM_ION
extern HI_S32 JPEG_HDEC_OpenMemDev(HI_VOID);
extern HI_VOID JPEG_HDEC_CloseMemDev(HI_S32 Device);
#endif

/******************************* API realization *****************************/

/*****************************************************************************
* func           : define open and close tde device
* others:     : NA
*****************************************************************************/
#define JPEG_HDEC_OPEN_CLOSE_DEV
#include "jpeg_hdec_csc.c"
#undef JPEG_HDEC_OPEN_CLOSE_DEV

void __attribute__ ((constructor)) jpeg_lib_creat(void)
{
     return;
}


void __attribute__ ((destructor)) jpeg_lib_destroy(void)
{
    return;
}

/*****************************************************************************
* func           : JPEG_HDEC_SetLowDelayBufferDate
* description : set low delay buffer data
                       CNcomment: 填充低延迟buffer 数据，保证后级处理得于完成
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* retval        : NA
* others:     : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_SetLowDelayBufferDate(j_decompress_ptr cinfo)
{
#ifndef CONFIG_JPEG_LOW_DELAY_SUPPORT
     HI_UNUSED(cinfo);
#else
     HI_U32* pu32VirLineBuf = NULL;

     CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
     JPEG_API_MODULE_DEFINE_HANDLE();

     CHECK_JPEG_UNEQUAL_UNRETURN(pJpegHandle->bLowDelayEn, HI_TRUE);

     pu32VirLineBuf = (HI_U32*)pJpegHandle->pVirLineBuf;
     CHECK_JPEG_EQUAL_UNRETURN(NULL, pu32VirLineBuf);

     *pu32VirLineBuf = pJpegHandle->stJpegSofInfo.u32YMcuHeight;
     *(pu32VirLineBuf + 4) = pJpegHandle->stJpegSofInfo.u32CMcuHeight;
#endif
     return;
}


/*****************************************************************************
* func           : JPEG_HDEC_Init
* description : initial hard decode resouce
                       CNcomment:初始化硬件解码资源
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:     : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_Init(j_common_ptr cinfo)
{
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

     CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);

     pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)calloc(1, sizeof(JPEG_HDEC_HANDLE_S) * 8);
     if (NULL == pJpegHandle)
     {
         ERREXIT(cinfo, JERR_NULL_POINT);
         return;
     }

     JPEG_SDEC_GetTimeStamp(&pJpegHandle->DecCostTimes, NULL);

     pJpegHandle->JpegDev = -1;
     pJpegHandle->CscDev  = -1;
     pJpegHandle->MemDev  = -1;
     pJpegHandle->SkipLines = 0;
     pJpegHandle->bHasHufTable = HI_TRUE;
     pJpegHandle->enImageFmt = JPEG_FMT_BUTT;

#ifdef CONFIG_JPEG_EXIF_SUPPORT
     pJpegHandle->u8ImageCount = 1;
#endif

     cinfo->client_data = (HI_VOID*)pJpegHandle;

     return;
}


/*****************************************************************************
* func           : JPEG_HDEC_DeInit
* description : destory decode call this function
                       CNcomment:销毁解码器的时候调用该接口释放资源
* param[in]  : cinfo   CNcomment: 解码对象  CNend\n
* retval        : NA
* others:     : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_DeInit(const struct jpeg_common_struct *cinfo)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_API_MODULE_DEFINE_HANDLE();

    if (HI_FALSE == pJpegHandle->bReleaseRes)
    {
        JPEG_HDEC_ReleaseRes(cinfo);
    }

    free(pJpegHandle);

    return;
}


/*****************************************************************************
* func           : JPEG_HDEC_Reset
* description : finish decode call this function to reset hard decode
                       CNcomment:解码完成调用该接口复位硬件解码器状态
* param[in]  : cinfo      CNcomment: 解码对象  CNend\n
* retval        : NA
* others:     : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_Reset(const struct jpeg_common_struct *cinfo)
{
    HI_U32 PreTime = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_API_MODULE_DEFINE_HANDLE();

    if (HI_FALSE == pJpegHandle->bReleaseRes)
    {
       JPEG_HDEC_ReleaseRes(cinfo);
    }

    HI_GFX_Memset(pJpegHandle,0,sizeof(JPEG_HDEC_HANDLE_S));

    pJpegHandle->bReleaseRes =  HI_TRUE;
    pJpegHandle->JpegDev = -1;
    pJpegHandle->CscDev  = -1;
    pJpegHandle->MemDev  = -1;
    pJpegHandle->SkipLines = 0;
    pJpegHandle->bHasHufTable = HI_TRUE;
    pJpegHandle->enImageFmt = JPEG_FMT_BUTT;

#ifdef CONFIG_JPEG_EXIF_SUPPORT
    pJpegHandle->u8ImageCount = 1;
#endif

    PreTime = pJpegHandle->DecCostTimes;
    JPEG_SDEC_GetTimeStamp(&pJpegHandle->DecCostTimes,NULL);
    pJpegHandle->DecCostTimes = pJpegHandle->DecCostTimes - PreTime;

    return;
}


/*****************************************************************************
* func           : define set proc information function
* others:     : NA
*****************************************************************************/
#define JPEG_HDEC_DEBUG_CHECK_SAVE_DATA
#define JPEG_HDEC_DEBUG_PROC
#define JPEG_HDEC_DEBUG_SAVE_YUVSP
#define JPEG_HDEC_DEBUG_SAVE_BMP
#define JPEG_HDEC_DEBUG_SAVE_SCEN
#include "jpeg_hdec_debug.c"
#undef JPEG_HDEC_DEBUG_SAVE_SCEN
#undef JPEG_HDEC_DEBUG_SAVE_YUVSP
#undef JPEG_HDEC_DEBUG_SAVE_BMP
#undef JPEG_HDEC_DEBUG_PROC
#undef JPEG_HDEC_DEBUG_CHECK_SAVE_DATA

/*****************************************************************************
* func           : JPEG_HDEC_ReleaseRes
* description : release resource
                       CNcomment:释放资源
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* retval        : NA
* others:     : NA
*****************************************************************************/
static inline HI_VOID JPEG_HDEC_ReleaseRes(const struct jpeg_common_struct *cinfo)
{
    /**<-- set proc information >**/
    /**<--设置proc 信息>**/
#ifdef CONFIG_JPEG_PROC_ENABLE
    JPEG_HDEC_SetProcInfo((j_decompress_ptr)cinfo);
#endif

    JPEG_HDEC_SetLowDelayBufferDate((j_decompress_ptr)cinfo);

    /**<-- free decode memory >**/
    /**<-- 释放解码所需要的内存>**/
    JPEG_HDEC_FreeDecodeMemory((j_decompress_ptr)cinfo);

    JPEG_HDEC_CloseDev(cinfo);

    return;
}

/*****************************************************************************
* func           : define csc function for yuv convert to xrgb
* others:     : NA
*****************************************************************************/
#define JPEG_HDEC_START_CSC
#include "jpeg_hdec_csc.c"
#undef JPEG_HDEC_START_CSC

/*****************************************************************************
* func           : JPEG_HDEC_StartDec
* description : start jpeg hard decode
                       CNcomment: 开始硬件解码
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* param[in]  : ScanlineBuf     CNcomment: 行buffer           CNend\n
* param[in]  : MaxLines        CNcomment: 最大行数  CNend\n
* retval        : row line          CNcomment:  返回读取行数CNend\n
* others:     : NA
*****************************************************************************/
HI_U32 JPEG_HDEC_StartDec(j_decompress_ptr cinfo, HI_CHAR* ScanlineBuf, HI_U32 MaxLines)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 RowLineNums = 0;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, MaxLines);
    JPEG_API_MODULE_DEFINE_HANDLE();

    JPEG_HDEC_IfSupport(cinfo);
    if (HI_FALSE == pJpegHandle->SupportHardDec)
    {
       return MaxLines;
    }

    /**<-- stop decode >**/
    /**<--停止解码直接退出 >**/
    if (HI_TRUE == pJpegHandle->EnStopDecode)
    {
        ERREXIT(cinfo, JERR_STOP_DECODE);
    }

    Ret = JPEG_HDEC_SendStream(cinfo);
    if (HI_SUCCESS != Ret)
    {
     #ifdef CONFIG_JPEG_SEEK_SUPPORT
       JPEG_HDEC_FreeDecodeMemory(cinfo);
       pJpegHandle->bHdecEnd = HI_FALSE;
       return 0;
     #else
       ERREXIT(cinfo, JERR_HARDDEC_FAILURE);
     #endif
    }

#ifndef CONFIG_JPEG_CSC_DISABLE
    RowLineNums = (HI_U32)JPEG_HDEC_HardCSC(cinfo);
    if (HI_SUCCESS != RowLineNums)
    {
      ERREXIT(cinfo, JERR_HARD_CSC_FAILURE);
    }
#endif

    if (HI_TRUE == pJpegHandle->bDiscardScanlines)
    {
       /**<-- if skip scanlines, should not copy data to user buffer >**/
       /**<--如果是丢行处理则不需要拷贝码流>**/
       return MaxLines;
    }

    RowLineNums = (HI_U32)JPEG_HDEC_OutUserBuf(cinfo, ScanlineBuf, MaxLines);

    return RowLineNums;
}


HI_BOOL JPEG_HDEC_OpenDev(const struct jpeg_decompress_struct *cinfo)
{
     CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FALSE);
     JPEG_API_MODULE_DEFINE_HANDLE();

     pJpegHandle->JpegDev = open("/dev/jpeg", O_RDWR | O_SYNC, S_IRUSR);
     if (pJpegHandle->JpegDev < 0)
     {
         return HI_FALSE;
     }

     pJpegHandle->pJpegRegVirAddr = (volatile char*)mmap(NULL,JPGD_REG_LENGTH,PROT_READ | PROT_WRITE,MAP_SHARED,pJpegHandle->JpegDev,(off_t)0);
     if (MAP_FAILED == pJpegHandle->pJpegRegVirAddr)
     {
         JPEG_HDEC_CloseDev((const struct jpeg_common_struct*)cinfo);
         return HI_FALSE;
     }

#ifndef CONFIG_JPEG_CSC_DISABLE
     pJpegHandle->CscDev = JPEG_HDEC_CSC_Open();
     if (pJpegHandle->CscDev < 0)
     {
         JPEG_HDEC_CloseDev((const struct jpeg_common_struct*)cinfo);
         return HI_FALSE;
     }
#endif

#ifdef CONFIG_GFX_MEM_ION
     pJpegHandle->MemDev = JPEG_HDEC_OpenMemDev();
     if (pJpegHandle->MemDev < 0)
     {
         JPEG_HDEC_CloseDev((const struct jpeg_common_struct*)cinfo);
         return HI_FALSE;
     }
#endif

     return HI_TRUE;
}


/*****************************************************************************
* func           : JPEG_HDEC_CloseDev
* description : close jpeg decode hard device
                       CNcomment:关闭硬件解码器设备
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* retval        : NA
* others:     : NA
*****************************************************************************/
static inline HI_VOID JPEG_HDEC_CloseDev(const struct jpeg_common_struct *cinfo)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_API_MODULE_DEFINE_HANDLE();

    if (NULL != pJpegHandle->pJpegRegVirAddr)
    {
       (HI_VOID)munmap((void*)pJpegHandle->pJpegRegVirAddr, JPGD_REG_LENGTH);
       pJpegHandle->pJpegRegVirAddr = NULL;
    }

    if (pJpegHandle->JpegDev >= 0)
    {
       close(pJpegHandle->JpegDev);
       pJpegHandle->JpegDev = -1;
    }

    if (pJpegHandle->CscDev >= 0)
    {
        JPEG_HDEC_CSC_Close(pJpegHandle->CscDev);
        pJpegHandle->CscDev = -1;
    }

#ifdef CONFIG_GFX_MEM_ION
    if (pJpegHandle->MemDev >= 0)
    {
        JPEG_HDEC_CloseMemDev(pJpegHandle->MemDev);
        pJpegHandle->MemDev = -1;
    }
#endif

    return;
}


/*****************************************************************************
* func           : define on decode function
* others:     : NA
*****************************************************************************/
#include "jpeg_hdec_startdec.c"

/*****************************************************************************
* func           : JPEG_HDEC_SendStream
* description : send stream and on decode
                       CNcomment: 送码流并启动解码
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* retval        : HI_SUCCESS      CNcomment:  成功CNend\n
* retval        : HI_FAILURE        CNcomment: 失败CNend\n
* others:     : NA
*****************************************************************************/
static inline HI_S32 JPEG_HDEC_SendStream(j_decompress_ptr cinfo)
{
    HI_S32 Ret = HI_FAILURE;
    HI_U32 PreTime = 0;
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    HI_U32 u32RegistLuaPixSum0 = 0;
    HI_U64 u64RegistLuaPixSum1 = 0;
#endif

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(NULL, pJpegHandle, HI_FAILURE);

    /**<-- if hard decode finish, should not start again >**/
    /**<--如果硬件解码完成，就不需要重新启动解码>**/
    CHECK_JPEG_EQUAL_RETURN(HI_TRUE, pJpegHandle->bHdecEnd, HI_SUCCESS);
    pJpegHandle->bHdecEnd = HI_TRUE;

    Ret = JPEG_HDEC_SetPara(cinfo);
    CHECK_JPEG_UNEQUAL_RETURN(HI_SUCCESS, Ret, HI_FAILURE);

    JPEG_SDEC_GetTimeStamp(&pJpegHandle->HardDecTimes, NULL);

    Ret = JPEG_HDEC_OnDecode(cinfo);

    PreTime = pJpegHandle->HardDecTimes;
    JPEG_SDEC_GetTimeStamp(&pJpegHandle->HardDecTimes,NULL);
    pJpegHandle->HardDecTimes = pJpegHandle->HardDecTimes - PreTime;

    CHECK_JPEG_EQUAL_RETURN(HI_FAILURE, Ret, HI_FAILURE);

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
    {
       u32RegistLuaPixSum0 = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_LPIXSUM0);
       u64RegistLuaPixSum1 = (HI_U64)(JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_LPIXSUM1) & 0xf);
       pJpegHandle->u64LuPixValue = (HI_U64)((u64RegistLuaPixSum1 << 32) | u32RegistLuaPixSum0);
    }
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
    JPEG_HDEC_SaveYUVSP(cinfo);
#endif

    return HI_SUCCESS;
}


/*****************************************************************************
* func           : JPEG_HDEC_NeedCpyDataToUserBuffer
* description : check whether cpy dato to user buffer
                       CNcomment: 判断是否需要将数据拷贝到用户buffer  中
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* param[in]  : MaxLines        CNcomment: 最大行数  CNend\n
* retval        : row line          CNcomment:  返回读取行数CNend\n
* others:     : NA
*****************************************************************************/
static inline HI_S32 JPEG_HDEC_NeedCpyDataToUserBuffer(j_decompress_ptr cinfo, HI_U32 MaxLines)
{
    HI_U32 Cnt = 0;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FAILURE);
    JPEG_API_MODULE_DEFINE_HANDLE();

    /**<-- out to usr buffer, should not copy >**/
    /**<--直接输出到用户buffer  中，不需要拷贝>**/
    if ((HI_FALSE == pJpegHandle->bCSCEnd) || (HI_TRUE == pJpegHandle->bOutUsrBuf))
    {
        for (Cnt = 0; Cnt < MaxLines; Cnt++)
        {
            (cinfo->output_scanline)++;
        }

        return (HI_S32)MaxLines;
    }

    return HI_FAILURE;
}


/*****************************************************************************
* func           : JPEG_HDEC_OutUserBuf
* description : out decode data to user buffer
                       CNcomment:将解码之后的数据拷贝到用户buffer 中
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* param[in]  : ScanlineBuf     CNcomment: 行buffer           CNend\n
* param[in]  : MaxLines        CNcomment: 最大行数  CNend\n
* retval        : row line          CNcomment:  返回读取行数CNend\n
* others:     : NA
*****************************************************************************/
static inline HI_S32 JPEG_HDEC_OutUserBuf(j_decompress_ptr cinfo, HI_CHAR* ScanlineBuf, HI_U32 MaxLines)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 Cnt = 0;
    HI_U32 SrcStride = 0;
    HI_S32 BufSrcLength = 0;
    HI_CHAR *pSrcBuf = NULL;

    JPEG_API_MODULE_DEFINE_HANDLE();

    if ((MaxLines + (cinfo->output_scanline)) > (cinfo->output_height))
    {
        MaxLines = (cinfo->output_height) - (cinfo->output_scanline);
    }

    Ret = JPEG_HDEC_NeedCpyDataToUserBuffer(cinfo,MaxLines);
    CHECK_JPEG_UNEQUAL_RETURN(HI_FAILURE, Ret, Ret);

    /**<-- only support copy to scanline buffer >**/
    /**<-- 只支持拷贝到行buffer,  另外一种为直接输出到物理buffer >**/
    if (NULL == ScanlineBuf)
    {
        ERREXIT(cinfo, JERR_OUT_MEM_NULL);
        return (HI_S32)MaxLines;
    }

    SrcStride = pJpegHandle->stJpegSofInfo.DecOutStride;
    pSrcBuf = pJpegHandle->stDecSurface.pOutVir + (HI_S32)((cinfo->output_scanline - pJpegHandle->stCropRect.y) * SrcStride);

    BufSrcLength = (cinfo->output_components) * (pJpegHandle->stCropRect.w);

    for (Cnt = 0; Cnt < MaxLines; Cnt++)
    {
       HI_GFX_Memcpy(ScanlineBuf, pSrcBuf, (size_t)BufSrcLength);
       (cinfo->output_scanline)++;
    }

    return (HI_S32)MaxLines;
}


HI_VOID JPEG_HDEC_SetOutFmt(const struct jpeg_decompress_struct *cinfo)
{
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;
    CHECK_JPEG_EQUAL_UNRETURN(cinfo, NULL);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(pJpegHandle, NULL);

    /**<--want to decode to yuv420 semi-planer >**/
    /**<-- 希望统一输出yuv420 semi-planer  格式>**/
    if (JCS_YUV420_SP == cinfo->out_color_space)
    {
       pJpegHandle->bOutYUV420SP = HI_TRUE;
    }

    return;

#else
    HI_UNUSED(cinfo);
    return;
#endif
}
