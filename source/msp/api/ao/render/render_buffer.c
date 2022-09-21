/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_buffer.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "hi_drv_ao.h"
#include "hi_error_mpi.h"

#include "render_buffer.h"
#include "kfifo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define RENDER_BUF_CNT 2

typedef struct RENDER_BUFFER
{
    kfifo_s  fifo;
    HI_VOID* pBuf;
    HI_U32   u32BufferSize;

    HI_VOID* pInputTmpBuf;
    HI_BOOL  bInputTmpBufUsed;

    HI_VOID* pOutBuf;
    HI_U32   u32OutBufDataSize;
} RENDER_BUFFER_S;

HI_S32 RENDER_Buffer_Init(HI_VOID** phHandle, HI_U32 u32BufferSize, HI_VOID* pExtOutBuf)
{
    HI_S32 s32Ret;

    CHECK_AO_NULL_PTR(phHandle);
    CHECK_AO_NULL_PTR(pExtOutBuf);

    if (0 == u32BufferSize)
    {
        HI_ERR_AO("Invalid arg %d \n", u32BufferSize);
        return HI_ERR_AO_INVALID_PARA;
    }

    RENDER_BUFFER_S* pstBuffer = (RENDER_BUFFER_S*)malloc(sizeof(RENDER_BUFFER_S));
    if (HI_NULL == pstBuffer)
    {
        HI_ERR_AO("malloc render buffer failed!\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }

    memset(pstBuffer, 0, sizeof(RENDER_BUFFER_S));
    pstBuffer->u32BufferSize = u32BufferSize;

    pstBuffer->pBuf = (HI_VOID*)malloc(u32BufferSize * RENDER_BUF_CNT);
    if (HI_NULL == pstBuffer->pBuf)
    {
        HI_ERR_AO("malloc Buf failed!\n");
        goto ERR_MALLOC_BUFFER;
    }

    pstBuffer->pInputTmpBuf = pstBuffer->pBuf + u32BufferSize;
    pstBuffer->pOutBuf = pExtOutBuf;

    s32Ret = kfifo_init(&pstBuffer->fifo, pstBuffer->pBuf, pstBuffer->u32BufferSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("kfifo init failed!\n");
        goto ERR_OUTBUF_INIT;
    }

    *phHandle = (HI_VOID*)pstBuffer;

    return HI_SUCCESS;

ERR_OUTBUF_INIT:
    free(pstBuffer->pBuf);
    pstBuffer->pBuf = HI_NULL;

ERR_MALLOC_BUFFER:
    free(pstBuffer);

    return HI_ERR_AO_MALLOC_FAILED;
}

HI_S32 RENDER_Buffer_DeInit(HI_VOID* handle)
{
    RENDER_BUFFER_S* pstBuffer;

    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_BUFFER_S*)handle;
    kfifo_deinit(&pstBuffer->fifo);

    free(pstBuffer->pBuf);
    pstBuffer->pBuf = HI_NULL;

    free(pstBuffer);

    return HI_SUCCESS;
}

HI_S32 RENDER_Buffer_Get(HI_VOID* handle, HI_U32 u32RequestSize, HI_U8** ppu8Data)
{
    RENDER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(ppu8Data);

    pstBuffer = (RENDER_BUFFER_S*)handle;
    if (kfifo_availabe(&pstBuffer->fifo) < pstBuffer->u32OutBufDataSize)
    {
        return RBUFFER_ERR_BUFFER_FULL;
    }

    if (u32RequestSize >= (kfifo_availabe(&pstBuffer->fifo) - pstBuffer->u32OutBufDataSize))
    {
        return RBUFFER_ERR_BUFFER_FULL;
    }

    if (u32RequestSize <= kfifo_linear_availabe(&pstBuffer->fifo))
    {
        kfifo_get_write_ptr(&pstBuffer->fifo, (HI_VOID**)ppu8Data);
        return HI_SUCCESS;
    }

    pstBuffer->bInputTmpBufUsed = HI_TRUE;
    *ppu8Data = pstBuffer->pInputTmpBuf;

    return HI_SUCCESS;
}

HI_S32 RENDER_Buffer_Put(HI_VOID* handle, HI_U32 u32DataSize, HI_U8* pu8Data)
{
    HI_S32  s32Ret;
    RENDER_BUFFER_S* pstBuffer;

    CHECK_AO_NULL_PTR(pu8Data);
    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_BUFFER_S*)handle;
    if (HI_TRUE == pstBuffer->bInputTmpBufUsed)
    {
        pstBuffer->bInputTmpBufUsed = HI_FALSE;
        s32Ret = kfifo_write(&pstBuffer->fifo, pu8Data, u32DataSize);
        if (HI_SUCCESS != s32Ret)
        {
            HI_INFO_AO("kfifo_write write %d failed(0x%x)\n", u32DataSize, s32Ret);
            return RBUFFER_ERR_BUFFER_FULL;
        }

        return HI_SUCCESS;
    }

    kfifo_update_write_ptr(&pstBuffer->fifo, u32DataSize);

    return HI_SUCCESS;
}

HI_U32 RENDER_Buffer_Acquire(HI_VOID* handle, HI_U32 u32WantedSize, HI_U8** ppu8Data)
{
    HI_S32 s32Ret;
    HI_U32 u32BusySize = 0;
    HI_U32 u32MinSize = 0;
    HI_U32 u32RealSize = 0;
    RENDER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(ppu8Data);
    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_BUFFER_S*)handle;
    u32BusySize = kfifo_busy(&pstBuffer->fifo);
    u32MinSize = ((pstBuffer->u32BufferSize - pstBuffer->u32OutBufDataSize) < u32BusySize) ?
                 (pstBuffer->u32BufferSize - pstBuffer->u32OutBufDataSize) : u32BusySize;

    s32Ret = kfifo_read(&pstBuffer->fifo, pstBuffer->pOutBuf + pstBuffer->u32OutBufDataSize, u32MinSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("kfifo_read failed(0x%x)\n", s32Ret);
    }

    pstBuffer->u32OutBufDataSize += u32MinSize;
    *ppu8Data = pstBuffer->pOutBuf;

    u32RealSize = (u32WantedSize < pstBuffer->u32OutBufDataSize) ? u32WantedSize : pstBuffer->u32OutBufDataSize;

    return u32RealSize;
}

HI_S32 RENDER_Buffer_Release(HI_VOID* handle, HI_U32 u32ConsumedSize)
{
    RENDER_BUFFER_S* pstBuffer = HI_NULL;
    CHECK_AO_NULL_PTR(handle);

    if (0 == u32ConsumedSize)
    {
        return HI_SUCCESS;
    }

    pstBuffer = (RENDER_BUFFER_S*)handle;
    if (u32ConsumedSize > pstBuffer->u32OutBufDataSize)
    {
        HI_ERR_AO("Release size(%d) larger than RingBuffersize(%d)\n", u32ConsumedSize, pstBuffer->u32OutBufDataSize);
        return HI_FAILURE;
    }
    memmove(pstBuffer->pOutBuf, (HI_U8*)pstBuffer->pOutBuf + u32ConsumedSize, pstBuffer->u32OutBufDataSize - u32ConsumedSize);
    pstBuffer->u32OutBufDataSize -= u32ConsumedSize;

    return HI_SUCCESS;
}

HI_S32 RENDER_Buffer_Enquire(HI_VOID* handle, HI_U32 *pu32UsedSize, HI_U32 *pu32TotalSize)
{
    RENDER_BUFFER_S* pstBuffer = (RENDER_BUFFER_S*)handle;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pu32UsedSize);
    CHECK_AO_NULL_PTR(pu32TotalSize);

    *pu32TotalSize = kfifo_size(&pstBuffer->fifo);
    *pu32UsedSize = *pu32TotalSize - kfifo_availabe(&pstBuffer->fifo) + pstBuffer->u32OutBufDataSize;

    return HI_SUCCESS;
}

HI_S32 RENDER_Buffer_Send(HI_VOID* handle, HI_U32 u32DataSize, HI_U8* pu8Data)
{
    HI_S32 s32Ret;
    RENDER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(pu8Data);
    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_BUFFER_S*)handle;

    if (u32DataSize >= (kfifo_availabe(&pstBuffer->fifo) - pstBuffer->u32OutBufDataSize))
    {
        return RBUFFER_ERR_BUFFER_FULL;
    }

    s32Ret = kfifo_write(&pstBuffer->fifo, pu8Data, u32DataSize);
    if (HI_SUCCESS != s32Ret)
    {
        return RBUFFER_ERR_BUFFER_FULL;
    }

    return HI_SUCCESS;
}

HI_S32 RENDER_Buffer_Reset(HI_VOID* handle)
{
    RENDER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_BUFFER_S*)handle;
    kfifo_reset(&pstBuffer->fifo);

    memset(pstBuffer->pOutBuf, 0, pstBuffer->u32BufferSize);
    pstBuffer->u32OutBufDataSize = 0;

    memset(pstBuffer->pInputTmpBuf, 0, pstBuffer->u32BufferSize);
    pstBuffer->bInputTmpBufUsed = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 RENDER_Buffer_GetDataSize(HI_VOID* handle, HI_S32* ps32BufSize)
{
    RENDER_BUFFER_S* pstBuffer = (RENDER_BUFFER_S*)handle;

    CHECK_AO_NULL_PTR(pstBuffer);

    *ps32BufSize = pstBuffer->u32OutBufDataSize + kfifo_busy(&pstBuffer->fifo);

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
