/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_startdec.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : start hard decode
Function List   :


History           :
Date                          Author                    Modification
2017/03/16           sdk              Created file
******************************************************************************/


/****************************  add include here     *********************************/

#include "hi_drv_jpeg.h"
#include "hi_jpeg_checkpara.h"

#ifdef CONFIG_GFX_ANDROID_SDK
#include "utils/Log.h"
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG   "libjpeg"
#endif

/***************************** Macro Definition     ********************************/
#define JPEG_DEC_RESUME_VALUE           0x01
#define JPEG_DEC_EOF_VALUE              0x02
/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/
static inline HI_VOID JPEG_HDEC_SetInputStreamBuffer(j_decompress_ptr cinfo);
static inline HI_VOID JPEG_HDEC_SetSaveStreamBuffer(j_decompress_ptr cinfo);
static inline HI_S32  JPEG_HDEC_OnDecInputPhyMemData(j_decompress_ptr cinfo);
static inline HI_VOID JPEG_HDEC_OnDecInputUnPhyMemData(j_decompress_ptr cinfo, HI_BOOL HasBeenStartDec, JPEG_INTTYPE_E *pIntStatus);
static inline HI_VOID JPEG_HDEC_CopyDataFromPhyBufToSysBuf(j_decompress_ptr cinfo);
static inline HI_VOID JPEG_HDEC_SetDecStatus(j_decompress_ptr cinfo);
static inline HI_S32 JPEG_HDEC_GetDecStatus(const JPEG_HDEC_HANDLE_S *pJpegHandle, JPEG_INTTYPE_E *pIntType, HI_U32 u32TimeOut);

static inline HI_S32 JPEG_HDEC_CheckWhetherShouldOutToUserBuf(const JPEG_HDEC_HANDLE_S *pJpegHandle);

extern HI_VOID JPEG_SDEC_ReadDataToSaveStreamBuffer(j_decompress_ptr cinfo);
extern HI_VOID JPEG_SDEC_GetInputBufferOffset(j_decompress_ptr cinfo);
extern HI_VOID JPEG_SDEC_SeekBufferOffset(j_decompress_ptr cinfo);
extern HI_BOOL JPEG_SDEC_InputBufferIsPhyMem(j_decompress_ptr cinfo);
extern HI_VOID JPEG_SDEC_GetInputStreamBuffer(j_decompress_ptr cinfo, HI_U32 *pStartPhyBuf, HI_U32 *pEndPhyBuf);

/**********************       API realization       ***********************************/

/*****************************************************************************
* func              : JPEG_HDEC_OnDecode
* description    : start decode
                          CNcomment:启动解码CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄                   CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功       CNend\n
* retval           : HI_FAILURE  CNcomment:  失败         CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_HDEC_OnDecode(j_decompress_ptr cinfo)
{
    HI_BOOL HasBeenStartDec = HI_FALSE;
    HI_S32 Ret = HI_SUCCESS;
    JPEG_INTTYPE_E IntStatus = JPG_INTTYPE_NONE;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    /**<-- remember the input data current position >**/
    /**<-- 启动硬件解码之前记录当前输入码流的位置 >**/
    JPEG_SDEC_GetInputBufferOffset(cinfo);

    /**<-- enable read data to input data buffer >**/
    /**<-- 使能直接将码流读到码流buffer 中>**/
    pJpegHandle->stInputDataBufInfo.BeginReadToInputDataBuf = HI_TRUE;

    /**<-- set stream buffer register >**/
    /**<-- 设置码流buffer 寄存器>**/
    JPEG_HDEC_SetInputStreamBuffer(cinfo);

    /**<--dispose the data save physical memory >**/
    /**<-- 处理码流数据放在连续物理内存方式 >**/
    if (HI_TRUE == JPEG_SDEC_InputBufferIsPhyMem(cinfo))
    {
       Ret = JPEG_HDEC_OnDecInputPhyMemData(cinfo);
       goto DEC_FINISH;
    }

    /**<--dispose the data save virtual memory >**/
    /**<-- 处理码流数据放在虚拟内存或文件方式 >**/
    do
    {
        JPEG_HDEC_OnDecInputUnPhyMemData(cinfo,HasBeenStartDec,&IntStatus);
        HasBeenStartDec = HI_TRUE;

        if ((JPG_INTTYPE_CONTINUE == IntStatus) || (JPG_INTTYPE_NONE == IntStatus))
        {
           continue;
        }

        #ifdef CONFIG_JPEG_SEEK_SUPPORT
        if (JPG_INTTYPE_FINISH == IntStatus)
        #else
        if ( (JPG_INTTYPE_ERROR == IntStatus) || (JPG_INTTYPE_FINISH == IntStatus))
        #endif
        {
            break;
        }

        /**<-- disenable read data to input data buffer >**/
        pJpegHandle->stInputDataBufInfo.BeginReadToInputDataBuf = HI_FALSE;

        goto DEC_FAILURE;

    }while (JPG_INTTYPE_FINISH != IntStatus);

DEC_FINISH:

    /**<-- disenable read data to input data buffer >**/
    pJpegHandle->stInputDataBufInfo.BeginReadToInputDataBuf = HI_FALSE;

    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    JPEG_HDEC_SetDecStatus(cinfo);

    Ret = JPEG_HDEC_CheckWhetherShouldOutToUserBuf(pJpegHandle);
    if (HI_SUCCESS != Ret)
    {
       return HI_SUCCESS;
    }

    JPEG_HDEC_CopyDataFromPhyBufToSysBuf(cinfo);

    return Ret;

DEC_FAILURE:

    #ifdef CONFIG_JPEG_SEEK_SUPPORT
    JPEG_SDEC_SeekBufferOffset(cinfo);
    #endif

    return HI_FAILURE;
}


/*****************************************************************************
* func              : JPEG_HDEC_OnDecInputPhyMemData
* description    : start decode that input data from physical memory
                          CNcomment:解码数据使用用户输入的连续码流buffer CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄                   CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功       CNend\n
* retval           : HI_FAILURE  CNcomment:  失败         CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_HDEC_OnDecInputPhyMemData(j_decompress_ptr cinfo)
{
    HI_U32 LowDelayValue = 0;
    HI_S32 Ret = HI_SUCCESS;
    JPEG_INTTYPE_E IntStatus = JPG_INTTYPE_NONE;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_RETURN(NULL, pJpegHandle, HI_FAILURE);

    /**<--read data >**/
    /**<-- 读取码流数据>**/
    JPEG_SDEC_ReadDataToSaveStreamBuffer(cinfo);

    /**<-- set save stream buffer register >**/
    /**<-- 设置存储码流buffer 寄存器>**/
    JPEG_HDEC_SetSaveStreamBuffer(cinfo);

#ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
    if (HI_TRUE == pJpegHandle->bLowDelayEn)
    {
       LowDelayValue = 0x8;
    }
#endif

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME, 0x2);
#ifdef CONFIG_JPEG_4KDDR_DISABLE
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, (0x5 | LowDelayValue));
#else
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, (0x1 | LowDelayValue));
#endif

    Ret = JPEG_HDEC_GetDecStatus(pJpegHandle, &IntStatus, JPEG_INTTYPE_DELAY_TIME);
    if (HI_SUCCESS != Ret)
    {
        JPEG_HDEC_SetLowDelayBufferDate(cinfo);
        return HI_FAILURE;
    }

#ifdef CONFIG_JPEG_SEEK_SUPPORT
    if ((JPG_INTTYPE_CONTINUE == IntStatus) || (JPG_INTTYPE_ERROR == IntStatus))
#else
    if (JPG_INTTYPE_CONTINUE == IntStatus)
#endif
    {
        JPEG_HDEC_SetLowDelayBufferDate(cinfo);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}



/*****************************************************************************
* func              : JPEG_HDEC_OnDecInputUnPhyMemData
* description    : start decode that input data from file or virtual buffer
                          CNcomment:解码数据使用用户输入文件或者非连续buffer 数据CNend\n
* param[in]     : cinfo                      CNcomment: 解码器句柄                               CNend\n
* param[in]     : HasBeenStartDec   CNcomment: 是否为第一次启动解码 CNend\n
* param[ou]    : pIntStatus             CNcomment: 获取解码状态                         CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功       CNend\n
* retval           : HI_FAILURE  CNcomment:  失败         CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_VOID JPEG_HDEC_OnDecInputUnPhyMemData(j_decompress_ptr cinfo, HI_BOOL HasBeenStartDec, JPEG_INTTYPE_E *pIntStatus)
{
    HI_BOOL DecDataEof = HI_FALSE;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);

    /**<--read data >**/
    /**<-- 读取码流数据>**/
    JPEG_SDEC_ReadDataToSaveStreamBuffer(cinfo);

    if (HI_TRUE == HasBeenStartDec)
    {
       (HI_VOID)JPEG_HDEC_GetDecStatus(pJpegHandle, pIntStatus, JPEG_INTTYPE_DELAY_TIME);
    }

    if ( (JPG_INTTYPE_ERROR == *pIntStatus) || (JPG_INTTYPE_FINISH == *pIntStatus))
    {
        return;
    }

    DecDataEof = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[pJpegHandle->stInputDataBufInfo.DecDataBufIndex].DecDataEof;

    CHECK_JPEG_EQUAL_UNRETURN(HI_FALSE,pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[pJpegHandle->stInputDataBufInfo.DecDataBufIndex].SaveStreamBufBusy);

    /**<-- set save stream buffer register >**/
    /**<-- 设置存储码流buffer 寄存器>**/
    JPEG_HDEC_SetSaveStreamBuffer(cinfo);

    if (HI_FALSE == HasBeenStartDec)
    {
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(DecDataEof ? JPEG_DEC_EOF_VALUE : 0x0));
      #ifdef CONFIG_JPEG_4KDDR_DISABLE
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
      #else
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
      #endif
    }
    else
    {
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(DecDataEof ? (JPEG_DEC_EOF_VALUE | JPEG_DEC_RESUME_VALUE) : JPEG_DEC_RESUME_VALUE));
    }

    return;
}

static inline HI_S32 JPEG_HDEC_GetDecStatus(const JPEG_HDEC_HANDLE_S *pJpegHandle, JPEG_INTTYPE_E *pIntType, HI_U32 u32TimeOut)
{
   HI_S32 Ret = HI_SUCCESS;
   JPEG_GETINTTYPE_S GetIntType;

   GetIntType.IntType = JPG_INTTYPE_NONE;
   GetIntType.TimeOut = u32TimeOut;

   Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETINTSTATUS, &GetIntType);
   if (HI_SUCCESS != Ret)
   {
       return Ret;
   }

   *pIntType = GetIntType.IntType;

   return HI_SUCCESS;
}

static inline HI_S32 JPEG_HDEC_CheckWhetherShouldOutToUserBuf(const JPEG_HDEC_HANDLE_S *pJpegHandle)
{
    if(   (HI_TRUE == pJpegHandle->bOutUsrBuf)
        &&((HI_TRUE == pJpegHandle->bOutYCbCrSP) || (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)))
    {
        return HI_FAILURE;
    }

    if ((HI_TRUE != pJpegHandle->bOutYCbCrSP) && (HI_TRUE != pJpegHandle->bDecOutColorSpaecXRGB))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* func              : JPEG_HDEC_CopyDataFromPhyBufToSysBuf
* description    : copy data from physical buffer to system buffer
                          CNcomment:将解码输出的码流拷贝到系统内存中CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄 CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_VOID JPEG_HDEC_CopyDataFromPhyBufToSysBuf(j_decompress_ptr cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);

    if ( (0 != pJpegHandle->stJpegSofInfo.u32YSize) && (HI_TRUE != pJpegHandle->bDecOutColorSpaecXRGB))
    {
       HI_GFX_Memcpy(pJpegHandle->stOutSurface.pOutVir[0],pJpegHandle->stDecSurface.DecOutVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
    }

    if (0 != pJpegHandle->stJpegSofInfo.u32CSize)
    {
       HI_GFX_Memcpy(pJpegHandle->stOutSurface.pOutVir[1],pJpegHandle->stDecSurface.DecOutVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
    }

    return;
}

static inline HI_VOID JPEG_HDEC_SetDecStatus(j_decompress_ptr cinfo)
{
    cinfo->global_state = DSTATE_STOPPING;
    cinfo->inputctl->eoi_reached  = HI_TRUE;

    return;
}

/*****************************************************************************
* func              : JPEG_HDEC_SetInputStreamBuffer
* description    : set input stream buffer register, this is be used by memory return
                          CNcomment:配置码流寄存器 ，这个是给码流环绕使用的
                          first buffer: 0x28 ~ 0x24 second buffer: 0x20 ~ 0x2c CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄 CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_VOID JPEG_HDEC_SetInputStreamBuffer(j_decompress_ptr cinfo)
{
    HI_U32 StartInputStreamPhyBuf = 0, EndInputStreamPhyBuf = 0;
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle->pJpegRegVirAddr);

    /**##########################################
         **   |<--------stream buffer---------------------->|
         **   |0x20  ~ 0x2c |<-----save stream buffer ->|0x28 ~ 0x24  |
         **   |___________|_______________________|___________|
         **##########################################**/

    JPEG_SDEC_GetInputStreamBuffer(cinfo, &StartInputStreamPhyBuf, &EndInputStreamPhyBuf);

    /**<--write stream buffer register  >**/
    /**<--配置输入码流buffer 寄存器>**/
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADDR, StartInputStreamPhyBuf);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADDR,EndInputStreamPhyBuf);

    return;
}


/*****************************************************************************
* func              : JPEG_HDEC_SetSaveStreamBuffer
* description    : set save stream buffer register
                          CNcomment:配置实际要解码使用的存储码流buffer CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄 CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_VOID JPEG_HDEC_SetSaveStreamBuffer(j_decompress_ptr cinfo)
{
    HI_U32 DecDataBufIndex = 0;
    HI_U32 StartSaveStreamPhyBuf = 0, EndSaveStreamPhyBuf = 0;
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle->pJpegRegVirAddr);
    /**##########################################
         **   |<--------stream buffer---------------------->|
         **   |0x20  ~ 0x2c |<-----save stream buffer ->|0x28 ~ 0x24  |
         **   |___________|_______________________|___________|
         **##########################################**/
    if (HI_TRUE == JPEG_SDEC_InputBufferIsPhyMem(cinfo))
    {
       /**<--dispose the data save physical memory >**/
       /**<-- 处理码流数据放在连续物理内存方式 >**/
       StartSaveStreamPhyBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf;
       EndSaveStreamPhyBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf;
       #ifdef CONFIG_JPEG_SAVE_SCEN
       JPEG_HDEC_SetSaveScen(cinfo,StartSaveStreamPhyBuf,EndSaveStreamPhyBuf,pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf,(HI_U64)(EndSaveStreamPhyBuf - StartSaveStreamPhyBuf));
       #endif
    }
    else
    {
       DecDataBufIndex = pJpegHandle->stInputDataBufInfo.DecDataBufIndex;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataBufIndex].SaveStreamBufBusy = HI_FALSE;

       StartSaveStreamPhyBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataBufIndex].SaveStreamPhyBuf;
       EndSaveStreamPhyBuf = StartSaveStreamPhyBuf + pJpegHandle->stInputDataBufInfo.SaveStreamBufSize;

       pJpegHandle->stInputDataBufInfo.DecDataBufIndex++;
       if (pJpegHandle->stInputDataBufInfo.DecDataBufIndex >= CONFIG_JPED_INPUT_DATA_BUFFER_NUM)
       {
          pJpegHandle->stInputDataBufInfo.DecDataBufIndex = 0;
       }
    }

    /**<--write save stream buffer register  >**/
    /**<--配置存储码流buffer 寄存器>**/
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, StartSaveStreamPhyBuf & 0xffffffff);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,EndSaveStreamPhyBuf & 0xffffffff);

    return;
}
