/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_datasrc.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : The user will use this api to realize some function
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                sdk                        Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jinclude.h"
#include "jpeglib.h"
#include "jerror.h"

#include "hi_jpeg_checkpara.h"
#include "hi_jpeg_config.h"
#include "hi_gfx_sys.h"

#include "jpeg_hdec_api.h"
#include "jpeg_hdec_mem.h"


#define JPEG_HDEC_DEBUG_SAVE_INPUT_STREAM
#define JPEG_HDEC_DEBUG_CHECK_SAVE_DATA
#include "jpeg_hdec_debug.c"
#undef JPEG_HDEC_DEBUG_CHECK_SAVE_DATA
#undef JPEG_HDEC_DEBUG_SAVE_INPUT_STREAM

/***************************** Macro Definition     ********************************/
#define JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS() \
        my_src_ptr src = NULL;                      \
        JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;  \
        pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);\
        if (NULL == pJpegHandle)\
        {\
           ERREXIT(cinfo, JERR_NULL_POINT);\
        }\
        src = (my_src_ptr)cinfo->src;\
        if (NULL == src)\
        {\
           ERREXIT(cinfo, JERR_NULL_POINT);\
        }

#define JPEG_DATASRC_CHECK_AND_DEFINE_HANDLE_PARAMETERS() \
        JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;  \
        pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);\
        if (NULL == pJpegHandle)\
        {\
           ERREXIT(cinfo, JERR_NULL_POINT);\
        }

/***************************** Structure Definition *******************************/

typedef struct {
  struct jpeg_source_mgr pub;
  FILE *infile;
  JOCTET *buffer;
  boolean start_of_file;
} my_source_mgr;
typedef my_source_mgr *my_src_ptr;

#define INPUT_BUF_SIZE  4096

/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/
#ifdef CONFIG_JPEG_SEEK_SUPPORT
static boolean JPEG_SDEC_SeekInputBuffer(j_decompress_ptr cinfo, long byte_offset);
#endif
static inline HI_S32 JPEG_SDEC_FillPhyMemInputBuffer(j_decompress_ptr cinfo);
static inline HI_S32 JPEG_SDEC_FillUnPhyMemInputBuffer(j_decompress_ptr cinfo, HI_BOOL bInputFile);

extern HI_VOID JPEG_HDEC_FlushBuf(j_decompress_ptr cinfo, HI_U32 PhyAddr);

/**********************       API realization       ***********************************/

static inline HI_S32 JPEG_SDEC_ReadDataToStreamBufCallBackSrc(j_decompress_ptr cinfo, HI_CHAR* pStreamBuf)
{
    HI_S32 EveryTimeReadBytes = 0;
    HI_S32 TotalReadTotalBytes = 0;
    HI_BOOL bFillRet = HI_TRUE;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, 0);
    JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

    do
    {
       if (0 != src->pub.bytes_in_buffer)
       {
          /**<-- shoul consider browser and skia>**/
          /**<--同时考虑浏览器和skia 的使用方式，浏览器的数据已经全部在buffer  中>**/
          EveryTimeReadBytes = (src->pub.bytes_in_buffer > pJpegHandle->stInputDataBufInfo.SaveStreamBufSize) ? (pJpegHandle->stInputDataBufInfo.SaveStreamBufSize) : (src->pub.bytes_in_buffer);
          /**<-- shoul consider save stream buffer size>**/
          /**<--需要考虑存储码流buffer 的大小>**/
          EveryTimeReadBytes = ((HI_S32)(pJpegHandle->stInputDataBufInfo.SaveStreamBufSize - TotalReadTotalBytes) > EveryTimeReadBytes) ?
                                (EveryTimeReadBytes) : (HI_S32)(pJpegHandle->stInputDataBufInfo.SaveStreamBufSize - TotalReadTotalBytes);

          HI_GFX_Memcpy((pStreamBuf + TotalReadTotalBytes), (HI_CHAR*)src->pub.next_input_byte, EveryTimeReadBytes);
          src->pub.next_input_byte += EveryTimeReadBytes;
          src->pub.bytes_in_buffer -= EveryTimeReadBytes;
          TotalReadTotalBytes += EveryTimeReadBytes;
       }
       else
       {
          bFillRet = cinfo->src->fill_input_buffer(cinfo);
       }

       if (HI_FALSE == bFillRet)
       {
          break;
       }

       if ((2 == cinfo->src->bytes_in_buffer) && (0xFF == (*(cinfo->src->next_input_byte))) && (0xD9 == (*(cinfo->src->next_input_byte + 1))))
       {
          break;
       }
    }while(TotalReadTotalBytes < (HI_S32)(pJpegHandle->stInputDataBufInfo.SaveStreamBufSize));

    return TotalReadTotalBytes;
}


/*****************************************************************************
* func              : JPEG_SDEC_FillInputBuffer
* description    : read data to save buffer
                          CNcomment:将码流写到解码器的buffer 中，作为解码器的输入CNend\n
* param[in]     : cinfo          CNcomment: 解码器句柄                   CNend\n
* param[in]     : bInputFile   CNcomment: 是不是读文件形式 CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功       CNend\n
* retval           : HI_FAILURE  CNcomment:  失败         CNend\n
* others:        : NA
*****************************************************************************/
HI_S32 JPEG_SDEC_FillInputBuffer(j_decompress_ptr cinfo, HI_BOOL bInputFile)
{
    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo,HI_FAILURE);
    JPEG_DATASRC_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    /**<-- stop decode >**/
    /**<--停止解码直接退出 >**/
    if (HI_TRUE == pJpegHandle->EnStopDecode)
    {
        ERREXIT(cinfo, JERR_STOP_DECODE);
    }

    /**<-- no need read to input data buffer >**/
    /**<-- 判断是否需要直接将码流写到输入buffer 中 >**/
    CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, pJpegHandle->stInputDataBufInfo.BeginReadToInputDataBuf, HI_FAILURE);

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf)
    {
        return JPEG_SDEC_FillPhyMemInputBuffer(cinfo);
    }

    return JPEG_SDEC_FillUnPhyMemInputBuffer(cinfo,bInputFile);
}


/*****************************************************************************
* func              : JPEG_SDEC_FillInputBufferFromMemReturn
* description    : fill data that from return buffer
                          CNcomment:内存回绕码流处理方式CNend\n
* param[in]     : cinfo          CNcomment: 解码器句柄             CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功       CNend\n
* retval           : HI_FAILURE  CNcomment:  失败         CNend\n
* others:        : NA
*****************************************************************************/
static boolean JPEG_SDEC_FillInputBufferFromMemReturn(j_decompress_ptr cinfo)
{
    HI_S32 Ret = HI_SUCCESS;
    size_t nbytes;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo,HI_FALSE);
    JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

    Ret = JPEG_SDEC_FillInputBuffer(cinfo, HI_FALSE);
    CHECK_JPEG_EQUAL_RETURN(Ret, HI_SUCCESS, TRUE);

    if (HI_FALSE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf)
    {
       pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf = (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize >= pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize) ? (HI_TRUE) : (HI_FALSE);
       pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize = (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf) ? (0) : (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize);
    }

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf)
    {/**<-- read data from second input data buffer >**/
     /**<-- 从第二块输入buffer  读取码流 >**/
        nbytes = ((pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize + INPUT_BUF_SIZE) > pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize) ?
                  (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize) : (INPUT_BUF_SIZE);

        src->buffer = (JOCTET *)(pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserSecondInputDataVirBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize);
        pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize += nbytes;
    }
    else
    {/**<-- read data from first input data buffer >**/
     /**<-- 从第一块输入buffer  读取码流 >**/
        nbytes = ((pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize + INPUT_BUF_SIZE) > pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize) ?
                  (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize) : (INPUT_BUF_SIZE);

        src->buffer = (JOCTET *)(pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize);
        pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize += nbytes;
    }

    if ((HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf) && (nbytes <= 0))
    {
       src->buffer[0] = (JOCTET) 0xFF;
       src->buffer[1] = (JOCTET) JPEG_EOI;
       nbytes = 2;
    }

    src->pub.next_input_byte = src->buffer;
    src->pub.bytes_in_buffer = nbytes;

    return TRUE;
}

/*****************************************************************************
* func              : JPEG_SDEC_FillPhyMemInputBuffer
* description    : read data from user input data buffer
                          CNcomment: 从用户输入的内存读码流CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄 CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功       CNend\n
* retval           : HI_FAILURE  CNcomment:  失败         CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_FillPhyMemInputBuffer(j_decompress_ptr cinfo)
{
    HI_U32 FirstStartPhyBuf = 0;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo,HI_FAILURE);
    JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataEof = HI_TRUE;

    /**<-- use physical buffer, and memory buffer is not return >**/
    /**<--连续物理内存方式，没有使用码流回绕方式>**/
    if (HI_FALSE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn)
    {
       pJpegHandle->stInputDataBufInfo.SaveStreamBufSize = src->pub.bytes_in_buffer;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf = (HI_CHAR*)src->pub.next_input_byte;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize - src->pub.bytes_in_buffer);
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize;
       return HI_SUCCESS;
    }

    /**<-- save data buffer that will hard decode from second buffer >**/
    /**<--硬件解码使用的存储码流buffer 使用第二块buffer >**/
    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf)
    {
       pJpegHandle->stInputDataBufInfo.SaveStreamBufSize = (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize) + src->pub.bytes_in_buffer;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf = (HI_CHAR*)src->pub.next_input_byte;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize - src->pub.bytes_in_buffer);
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize;
       return HI_SUCCESS;
    }

    /**<-- save data buffer that will hard decode from first buffer >**/
    /**<--硬件解码使用的存储码流buffer 起始地址使用第一块buffer >**/
    FirstStartPhyBuf = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserSecondInputDataVirBuf);
    pJpegHandle->stInputDataBufInfo.SaveStreamBufSize = (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize) + src->pub.bytes_in_buffer;
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf = (HI_CHAR*)src->pub.next_input_byte;
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf  = FirstStartPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize - src->pub.bytes_in_buffer);
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize;

    return HI_SUCCESS;
}


/*****************************************************************************
* func              : JPEG_SDEC_FillUnPhyMemInputBuffer
* description    : read data to input data buffer that decoder alloc
                          CNcomment: 将码流数据读到解码器分配的码流buffer CNend\n
* param[in]     : cinfo          CNcomment: 解码器句柄                   CNend\n
* param[in]     : bInputFile   CNcomment: 是不是读文件形式 CNend\n
* retval           : HI_SUCCESS  CNcomment:  成功       CNend\n
* retval           : HI_FAILURE  CNcomment:  失败         CNend\n
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_FillUnPhyMemInputBuffer(j_decompress_ptr cinfo, HI_BOOL bInputFile)
{
    size_t nbytes;
    HI_U32 ReadDataBufIndex = 0;
    HI_CHAR* pInputDataBuf  = NULL;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo,HI_FAILURE);
    JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

    ReadDataBufIndex = pJpegHandle->stInputDataBufInfo.SaveStreamBufIndex;
    CHECK_JPEG_EQUAL_RETURN(HI_TRUE, pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[ReadDataBufIndex].SaveStreamBufBusy, HI_SUCCESS);

    CHECK_JPEG_EQUAL_RETURN(HI_TRUE, pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataEof, HI_SUCCESS);

    pInputDataBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[ReadDataBufIndex].pSaveStreamVirBuf;

    if (HI_FALSE == pJpegHandle->stInputDataBufInfo.bUseInsideData)
    {
        nbytes = JPEG_SDEC_ReadDataToStreamBufCallBackSrc(cinfo, pInputDataBuf);
    }
    else if (HI_TRUE == bInputFile)
    {
       if (0 != src->pub.bytes_in_buffer)
       {
          HI_GFX_Memcpy(pInputDataBuf, (HI_CHAR*)src->pub.next_input_byte, src->pub.bytes_in_buffer);
          nbytes = JFREAD(src->infile,(HI_CHAR*)(pInputDataBuf + src->pub.bytes_in_buffer),pJpegHandle->stInputDataBufInfo.SaveStreamBufSize - src->pub.bytes_in_buffer);
          nbytes += src->pub.bytes_in_buffer;

          src->pub.next_input_byte = NULL;
          src->pub.bytes_in_buffer = 0;
       }
       else
       {
           nbytes = JFREAD(src->infile,pInputDataBuf,pJpegHandle->stInputDataBufInfo.SaveStreamBufSize);
       }
    }
    else
    {
       nbytes = (src->pub.bytes_in_buffer > pJpegHandle->stInputDataBufInfo.SaveStreamBufSize) ? pJpegHandle->stInputDataBufInfo.SaveStreamBufSize : src->pub.bytes_in_buffer;
       HI_GFX_Memcpy(pInputDataBuf, (HI_CHAR*)src->pub.next_input_byte, nbytes);
       src->pub.next_input_byte += nbytes;
       src->pub.bytes_in_buffer -= nbytes;
    }

    JPEG_HDEC_FlushBuf(cinfo,pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf);

    if (nbytes < pJpegHandle->stInputDataBufInfo.SaveStreamBufSize)
    {
       pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataEof = HI_TRUE;
    }
    else
    {
       pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataEof = HI_FALSE;
    }

    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[ReadDataBufIndex].SaveStreamBufBusy = HI_TRUE;
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[ReadDataBufIndex].DecDataEof = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataEof;

    pJpegHandle->stInputDataBufInfo.SaveStreamBufIndex++;
    if (pJpegHandle->stInputDataBufInfo.SaveStreamBufIndex >= CONFIG_JPED_INPUT_DATA_BUFFER_NUM)
    {
       pJpegHandle->stInputDataBufInfo.SaveStreamBufIndex = 0;
    }

    return HI_SUCCESS;
}


/*****************************************************************************
* func              : JPEG_SDEC_InitSrc
* description    : init input data buffer information
                          CNcomment:初始化输入码流信息CNend\n
* param[in]     : *cinfo   CNcomment: 解码器句柄 CNend\n
* param[in]     : InBuf    CNcomment: 输入码流的虚拟地址，或者是码流回绕模式的第一块码流虚拟地址CNend\n
* param[in]     : InSize    CNcomment: 输入码流的大小，或者是码流回绕模式的第一块码流大小CNend\n
* param[in]     : bInputFile    CNcomment: 是否为输入文件形式CNend\n
* others:         : NA
*****************************************************************************/
HI_VOID JPEG_SDEC_InitSrc(j_decompress_ptr cinfo, const HI_UCHAR* InBuf, HI_ULONG InSize, HI_BOOL bInputFile)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

    pJpegHandle->stInputDataBufInfo.bUseInsideData = HI_TRUE;

#ifdef CONFIG_JPEG_SEEK_SUPPORT
    cinfo->src->seek_input_data = JPEG_SDEC_SeekInputBuffer;
#endif

    if (HI_TRUE == bInputFile)
    {
        return;
    }

    if (NULL == InBuf)
    {
        ERREXIT(cinfo, JERR_NULL_POINT);
    }

    src->infile = NULL;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf = (HI_CHAR*)InBuf;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize = InSize;
    /**<-- should  consider turbo mem src initial for _tjInitDecompress function >**/
    /**<-- 需要考虑_tjInitDecompress 函数会先初始化码流处理函数>**/
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize = (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize <= 1) ? (InSize) : (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize);

    return;
}

#ifdef CONFIG_JPEG_SEEK_SUPPORT
static boolean JPEG_SDEC_SeekInputBuffer(j_decompress_ptr cinfo, HI_SLONG ByteOffset)
{
    HI_S32 Ret = HI_SUCCESS;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo,HI_FALSE);
    JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

    /**<-- the data save physical buffer, need not seek >**/
    /**<--码流存放在连续物理内存中，不需要回退>**/
    CHECK_JPEG_EQUAL_RETURN(HI_TRUE, pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf,TRUE);

    /**<-- seek stream, next to soft decode, so should not read data to save stream buffer >**/
    /**<--码流回退启动软件解码，不能再往存储码流buffer 里面写数据了>**/
    pJpegHandle->stInputDataBufInfo.BeginReadToInputDataBuf = HI_FALSE;

    if (NULL != src->infile)
    {
       Ret = fseek(src->infile,ByteOffset,SEEK_SET);
       src->pub.next_input_byte = NULL;
       src->pub.bytes_in_buffer = 0;
    }
    else
    {
       src->pub.next_input_byte = (JOCTET*)pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf + ByteOffset;
       src->pub.bytes_in_buffer = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize - ByteOffset;
    }

    if (HI_SUCCESS != Ret)
    {
        ERREXIT(cinfo, JERR_STREAM_BACK_FAILURE);
    }

    return TRUE;
}
#endif

/*****************************************************************************
* func              : JPEG_SDEC_InputBufferIsPhyMem
* description    : check whether input data buffer is physical memory
                          CNcomment: 判断输入的码流地址是不是连续的物理内存CNend\n
* param[in]     : *cinfo   CNcomment: 解码器句柄 CNend\n
* others:        : NA
*****************************************************************************/
HI_BOOL JPEG_SDEC_InputBufferIsPhyMem(j_decompress_ptr cinfo)
{
    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo,HI_FALSE);
    JPEG_DATASRC_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    return pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf;
}


/*****************************************************************************
* func              : JPEG_SDEC_ReadDataToSaveStreamBuffer
* description    : read data to save stream buffer
                          CNcomment:读取码流到存储码流buffer  中，用来硬件解码使用 CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄 CNend\n
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_SDEC_ReadDataToSaveStreamBuffer(j_decompress_ptr cinfo)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_DATASRC_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    if ( (HI_FALSE == pJpegHandle->stInputDataBufInfo.bUseInsideData) && (HI_FALSE == pJpegHandle->stInputDataBufInfo.EnReadToInputDataBuf))
    {
        JPEG_SDEC_FillUnPhyMemInputBuffer(cinfo, HI_FALSE);
        return;
    }

    (HI_VOID)(*cinfo->src->fill_input_buffer)(cinfo);

    return;
}


/*****************************************************************************
* func              : JPEG_SDEC_GetInputStreamBuffer
* description    : get input stream buffer
                          CNcomment:获取输入码流buffer 的起始和结束地址 CNend\n
* param[in]     : cinfo   CNcomment: 解码器句柄 CNend\n
* param[in]     : pStartPhyBuf   CNcomment: 起始地址 CNend\n
* param[in]     : pEndPhyBuf   CNcomment: 结束地址 CNend\n
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_SDEC_GetInputStreamBuffer(j_decompress_ptr cinfo, HI_U32 *pStartPhyBuf, HI_U32 *pEndPhyBuf)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_DATASRC_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf)
    {
        *pStartPhyBuf = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf;
        *pEndPhyBuf = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize;
        *pStartPhyBuf = (*pStartPhyBuf + CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1) & (~(CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1));
        *pStartPhyBuf = *pStartPhyBuf - CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN;
        *pEndPhyBuf = (*pEndPhyBuf + CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1) & (~(CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1));
        return;
    }

    *pStartPhyBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf;
    *pEndPhyBuf = *pStartPhyBuf + CONFIG_JPED_INPUT_DATA_BUFFER_NUM * (CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE);

    return;
}


/*****************************************************************************
* func              : JPEG_SDEC_GetInputBufferOffset
* description    : get the input data current position
                          CNcomment: 获取输入buffer 的偏移位置，
                          在这里给硬件解码回退软件解码使用CNend\n
* param[in]     : *cinfo   CNcomment: 解码器句柄 CNend\n
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_SDEC_GetInputBufferOffset(j_decompress_ptr cinfo)
{
#ifdef CONFIG_JPEG_SEEK_SUPPORT
   CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
   JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

   /**<-- the data save physical buffer, include memory return type, need not seek >**/
   /**<--码流存放在连续物理内存中，包括内存回退模式，不需要回退，所以不需要获取位置>**/
   CHECK_JPEG_EQUAL_UNRETURN(HI_TRUE, pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf);

   /**<-- use callback type,  fist save stream size, next save data has been read pos >**/
   /**<-- 先保存码流大小，在保存进入硬件解码所在的位置>**/
   if (0 == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize)
   {
     pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf = (HI_CHAR*)src->pub.next_input_byte;
     pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize = src->pub.bytes_in_buffer;
   }

   if (HI_FALSE == pJpegHandle->stInputDataBufInfo.bUseInsideData)
   {
      pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos = (cinfo->src->current_offset > cinfo->src->bytes_in_buffer) ? (cinfo->src->current_offset - cinfo->src->bytes_in_buffer) : (0);
      if (0 == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos)
      {
          pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize - src->pub.bytes_in_buffer;
      }
      return;
   }

   if (NULL != src->infile)
   {
      pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos = (HI_ULONG)ftell(src->infile);
      pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos - src->pub.bytes_in_buffer;
      return;
   }

   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize - src->pub.bytes_in_buffer;

#else
   HI_UNUSED(cinfo);
#endif

   return;
}


/*****************************************************************************
* func              : JPEG_SDEC_SeekBufferOffset
* description    : seek stream to position
                          CNcomment: 码流回退到解码异常的地方CNend\n
* param[in]     : *cinfo   CNcomment: 解码器句柄 CNend\n
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_SDEC_SeekBufferOffset(j_decompress_ptr cinfo)
{
#ifdef CONFIG_JPEG_SEEK_SUPPORT
   HI_BOOL bSeekSuccess = HI_TRUE;
   HI_ULONG InputCurPos = 0;

   CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
   JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

   pJpegHandle->bSeekToSoftDec = HI_TRUE;

   InputCurPos = (cinfo->src->current_offset > cinfo->src->bytes_in_buffer) ? (cinfo->src->current_offset - cinfo->src->bytes_in_buffer) : (0);

   if ((HI_FALSE == pJpegHandle->stInputDataBufInfo.bUseInsideData) && (0 == InputCurPos))
   {/**<--for callback used, if not use file, maybe current position is zero >**/
    /**<--如果使用内存数据并且使用回调方式就没有当前位置数据>**/
       src->pub.next_input_byte = (JOCTET*)pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos;
       src->pub.bytes_in_buffer = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos;
       pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos = InputCurPos;
       return;
   }

   CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo->src->seek_input_data);

   bSeekSuccess = cinfo->src->seek_input_data(cinfo, pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos);
   if (TRUE != bSeekSuccess)
   {
       ERREXIT(cinfo, JERR_SEEK_ABNORMAL);
   }
#else
   HI_UNUSED(cinfo);
#endif
   return;
}


/*****************************************************************************
* func              : JPEG_SDEC_SetInputBufferInfo
* description    : save input stream buffer information
                          CNcomment: 保存输入码流的内存信息CNend\n
* param[in]     : *cinfo   CNcomment: 解码器句柄 CNend\n
* param[in]     : StreamPhyAddr   CNcomment: 用户输入的单块buffer  或者码流buffer 池的起始物理地址 CNend\n
* param[in]     : StremBufSize      CNcomment: 用户输入的单块buffer  或者码流buffer 池的大小CNend\n
* param[in]     : pStreamVirBuf     CNcomment: 用户输入的码流buffer 池的起始虚拟地址，也是第二块buffer 的起始虚拟地址CNend\n
* param[in]     : pStreamVirBuf     CNcomment: 用户输入的第二块buffer 的大小CNend\n
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_SDEC_SetInputBufferInfo(const struct jpeg_decompress_struct *cinfo,HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,HI_CHAR* pSecondStreamVirBuf, HI_U32 SecondStreamBufSize)
{
   CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
   JPEG_DATASRC_CHECK_AND_DEFINE_SRC_HANDLE_PARAMETERS();

   if (0 == StreamPhyAddr)
   {
      ERREXIT(cinfo, JERR_NULL_POINT);
   }

#ifndef HI_ADVCA_FUNCTION_RELEASE
   JPEG_HDEC_SaveInputStream((HI_UCHAR*)pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf,pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize,(HI_UCHAR*)pSecondStreamVirBuf,SecondStreamBufSize);
#endif

   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf = StreamPhyAddr;
   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf = HI_TRUE;

   if (0 == SecondStreamBufSize)
   {
      pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn = HI_FALSE;
      return;
   }

   /**<--the stream save with two buffer, should set as follows paras >**/
   /**<-- 为了提高buffer 利用率，使用buffer 池，码流存放在两块buffer 中，即支持内存回绕处理>**/
   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn = HI_TRUE;
   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize = TotalStremBufSize;

   if (NULL == pSecondStreamVirBuf)
   {
      ERREXIT(cinfo, JERR_NULL_POINT);
   }
   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserSecondInputDataVirBuf = pSecondStreamVirBuf;
   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize = SecondStreamBufSize;

   /**<--default read first data buffer>**/
   /**<--默认先读取第一块码流数据>**/
   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf = HI_FALSE;
   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize = 0;

   src->pub.fill_input_buffer = JPEG_SDEC_FillInputBufferFromMemReturn;
   src->pub.bytes_in_buffer = 0;
   src->pub.next_input_byte	= NULL;

   return;
}
