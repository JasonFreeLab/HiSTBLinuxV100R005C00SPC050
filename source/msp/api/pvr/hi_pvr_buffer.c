#include <stdlib.h>
#include <malloc.h>
#include "hi_type.h"
#include "hi_mpi_mem.h"
#include "pvr_debug.h"
#include "hi_pvr_debug.h"
#include "hi_pvr_priv.h"
#include "hi_pvr_fifo.h"
#include "hi_pvr_buffer.h"

#ifdef HI_PVR_EXTRA_BUF_SUPPORT

#define TS_CACHE_BUFFER_MAGIC_NUM   (0x54537473)/*"TSts"*/

#define PVR_CACHE_BUFFER_SET_STATE(enCurState, enNewState)\
    do{\
        (enCurState) |= (enNewState);\
    }while(0)
#define PVR_CACHE_BUFFER_CLEAR_STATE(enCurState, enNewState)\
    do{\
        (enCurState) &= ~(enNewState);\
    }while(0)
#define PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, ret)\
    do{\
        if (TS_CACHE_BUFFER_MAGIC_NUM != (pstTsCacheBuffer)->u32CheckCode)\
        {\
            HI_ERR_PVR("Invalid pointer(checkCode:0x%x)\n", (pstTsCacheBuffer)->u32CheckCode);\
            return ret;\
        }\
    }while(0)

/*write and flush can be done at the same time; wrte and read can  be done at the same time; read and flush can't be done at the same time*/
#define PVR_CACHE_BUFFER_WRITE_INVALID (PVR_CACHE_BUFFER_STATE_BUTT|PVR_CACHE_BUFFER_STATE_WRITE)
#define PVR_CACHE_BUFFER_READ_INVALID  (PVR_CACHE_BUFFER_STATE_BUTT|PVR_CACHE_BUFFER_STATE_FLUSH)
#define PVR_CACHE_BUFFER_FLUSH_INVALID (PVR_CACHE_BUFFER_STATE_BUTT|PVR_CACHE_BUFFER_STATE_READ|PVR_CACHE_BUFFER_STATE_FLUSH)


/*if including the state, continue waiting*/
static HI_S32 PVRTsCacheBufferChechAndWait(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer,
        PVR_CACHE_BUFFER_STATE_E enStateList)
{
    HI_U32 u32TimeOut = 10 * 1000; /*total timeout is 10*1000*1000us=10s*/

    /*the loop will unlock and lock the mutex*/
    do
    {
        if (0 == (pstTsCacheBuffer->enState & enStateList))
        {
            break;
        }

        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        PVR_USLEEP(1000);
        PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
        u32TimeOut--;
    }while (0 != u32TimeOut);

    if (0 == (pstTsCacheBuffer->enState & enStateList))
    {
        return HI_SUCCESS;
    }
    else
    {
        HI_ERR_PVR("wait 10s for the buffer state change failed(cur/invalid:%u/%u)\n", pstTsCacheBuffer->enState, enStateList);
        return  HI_FAILURE;
    }
}


/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_Init
 Description        : initialize the ts cache buffer
 Input                :
 Output              :
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_S32 PVR_TS_CACHE_BUFFER_Init(HI_U32 u32RecBufSize, PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer)
{
    HI_PVR_DEBUG_ENTER();

    if ((0 == u32RecBufSize) || (HI_NULL == pstTsCacheBuffer))
    {
        HI_ERR_PVR("zero length(%u) or null pointer(%p)\n", u32RecBufSize, pstTsCacheBuffer);
        return HI_FAILURE;
    }

    memset(pstTsCacheBuffer, 0x00, sizeof(PVR_TS_CACHE_BUFF_INFO_S));

    /*ts cache buffer is 2 times of record buffer*/
    pstTsCacheBuffer->u32Size = 2 * u32RecBufSize;

    /*DIO require that the addr must align by PVR_DIO_ALIGN_SIZE*/
#ifndef HI_PVR_FIFO_DIO
    pstTsCacheBuffer->pu8Addr = (HI_U8*)HI_MALLOC(HI_ID_PVR, pstTsCacheBuffer->u32Size);
#else
    pstTsCacheBuffer->pu8Addr = (HI_U8*)memalign((size_t)PVR_DIO_ALIGN_SIZE, (size_t)pstTsCacheBuffer->u32Size);
#endif
    if (HI_NULL == pstTsCacheBuffer->pu8Addr)
    {
        HI_ERR_PVR("Malloc ts cache buffer(%u) failed\n", pstTsCacheBuffer->u32Size);
        pstTsCacheBuffer->u32Size = 0;
        return HI_ERR_PVR_NO_MEM;
    }

    memset(pstTsCacheBuffer->pu8Addr, 0x00, pstTsCacheBuffer->u32Size);

    /*add mutex, for timeshift, play will read data from the buffer while record is flushing data to the files.*/
    if (-1 == pthread_mutex_init(&(pstTsCacheBuffer->stCacheMutex), NULL))
    {
        HI_ERR_PVR("Init the cache mutex failed\n");
#ifndef HI_PVR_FIFO_DIO
        HI_FREE(HI_ID_PVR, pstTsCacheBuffer->pu8Addr);
#else
        free(pstTsCacheBuffer->pu8Addr);
#endif
        memset(pstTsCacheBuffer, 0x00, sizeof(PVR_TS_CACHE_BUFF_INFO_S));
        return HI_FAILURE;
    }

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
    pstTsCacheBuffer->enState = PVR_CACHE_BUFFER_STATE_IDLE;
    pstTsCacheBuffer->u64HeadGlobalOffset = 0;
    pstTsCacheBuffer->u32Head = 0;
    pstTsCacheBuffer->u32UsedSize = 0;
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    /*u32CheckCode is not needed to be saved by the mutex.*/
    pstTsCacheBuffer->u32CheckCode = TS_CACHE_BUFFER_MAGIC_NUM;

    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}


/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_DeInit
 Description        : DeInitialize the ts cache buffer
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_S32 PVR_TS_CACHE_BUFFER_DeInit(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer)
{
    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstTsCacheBuffer)
    {
        HI_WARN_PVR("Null pointer! no need to deinit\n");
        return HI_SUCCESS;
    }

    /*invalid param check: pstTsCacheBuffer is not initialized by PVR_TS_CACHE_BUFFER_Init*/
    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, HI_FAILURE);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));

    if (PVR_CACHE_BUFFER_STATE_IDLE != pstTsCacheBuffer->enState)
    {
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        HI_ERR_PVR("invalid  state(%d)\n", pstTsCacheBuffer->enState);
        return HI_FAILURE;
    }

    pstTsCacheBuffer->enState = PVR_CACHE_BUFFER_STATE_BUTT;
    pstTsCacheBuffer->u64HeadGlobalOffset = 0;
    pstTsCacheBuffer->u32Head = 0;
    pstTsCacheBuffer->u32UsedSize = 0;

    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    pstTsCacheBuffer->u32CheckCode = 0;

    if (HI_NULL != pstTsCacheBuffer->pu8Addr)
    {
        memset(pstTsCacheBuffer->pu8Addr, 0x00, pstTsCacheBuffer->u32Size);

#ifndef HI_PVR_FIFO_DIO
        HI_FREE(HI_ID_PVR, pstTsCacheBuffer->pu8Addr);
#else
        free(pstTsCacheBuffer->pu8Addr);
#endif
        pstTsCacheBuffer->pu8Addr = HI_NULL;
    }

    (HI_VOID)pthread_mutex_destroy(&(pstTsCacheBuffer->stCacheMutex));

    memset(pstTsCacheBuffer, 0x00, sizeof(PVR_TS_CACHE_BUFF_INFO_S));

    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_GetUsedSize
 Description        : get the used size of the ts cache buffer
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_U32 PVR_TS_CACHE_BUFFER_GetUsedSize(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer)
{
    /*default return 0 mean that no valided data*/
    HI_U32 u32UsedSize = 0;

    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pstTsCacheBuffer) || (0 == pstTsCacheBuffer->u32Size))
    {
        HI_ERR_PVR("Null pointer(%p) or zero length!\n", pstTsCacheBuffer);
        return u32UsedSize;
    }

    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, u32UsedSize);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
    u32UsedSize = pstTsCacheBuffer->u32UsedSize;
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    HI_PVR_DEBUG_EXIT();

    return u32UsedSize;
}

/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_GetFreeSize
 Description        : get the free size of the ts cache buffer
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_U32 PVR_TS_CACHE_BUFFER_GetFreeSize(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer)
{
    /*default return 0 mean that no free buffer*/
    HI_U32 u32FreeSize = 0;

    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pstTsCacheBuffer) || (0 == pstTsCacheBuffer->u32Size))
    {
        HI_ERR_PVR("Null pointer(%p) or zero length!\n", pstTsCacheBuffer);
        return u32FreeSize;
    }

    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, u32FreeSize);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
    u32FreeSize = pstTsCacheBuffer->u32Size - pstTsCacheBuffer->u32UsedSize;
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    HI_PVR_DEBUG_EXIT();

    return u32FreeSize;
}

/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_WriteToBuffer
 Description        : write the data to ts cache buffer
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_S32 PVR_TS_CACHE_BUFFER_WriteToBuffer(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U8* pu8RecData, HI_U32 u32Len)
{
    /*need two address info because the rewind of the ts cache buffer*/
    HI_U8* pu8Addr1 = HI_NULL;
    HI_U8* pu8Addr2 = HI_NULL;
    HI_U32 u32Len1 = 0;
    HI_U32 u32Len2 = 0;
    HI_U32 u32Tail = 0;

    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pstTsCacheBuffer) || (0 == pstTsCacheBuffer->u32Size))
    {
        HI_ERR_PVR("Null pointer(%p) or zero length!\n", pstTsCacheBuffer);
        return HI_FAILURE;
    }

    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, HI_FAILURE);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));

    if (PVR_CACHE_BUFFER_STATE_BUTT == pstTsCacheBuffer->enState)
    {
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        HI_ERR_PVR("invalid state(0x%x)\n", pstTsCacheBuffer->enState);
        return HI_FAILURE;
    }

    /*check  current state*/
    (HI_VOID)PVRTsCacheBufferChechAndWait(pstTsCacheBuffer, PVR_CACHE_BUFFER_WRITE_INVALID);

    /*set current state*/
    PVR_CACHE_BUFFER_SET_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_WRITE);

    /*no enough buffer for write*/
    if (u32Len + pstTsCacheBuffer->u32UsedSize > pstTsCacheBuffer->u32Size)
    {
        PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_WRITE);
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        HI_ERR_PVR("no enought buffer to save the data:total/used/need:%u/%u/%u\n",
                   pstTsCacheBuffer->u32Size, pstTsCacheBuffer->u32UsedSize, u32Len);
        return HI_FAILURE;
    }

    u32Tail = (pstTsCacheBuffer->u32Head + pstTsCacheBuffer->u32UsedSize) % pstTsCacheBuffer->u32Size;

    /*need to save two times: one is on the tail; other is on the head*/
    if (u32Tail + u32Len > pstTsCacheBuffer->u32Size)
    {
        pu8Addr1 = pstTsCacheBuffer->pu8Addr + u32Tail;
        u32Len1 = pstTsCacheBuffer->u32Size - u32Tail;
        pu8Addr2 = pstTsCacheBuffer->pu8Addr;
        u32Len2 = u32Len - u32Len1;
    }
    else
    {
        pu8Addr1 = pstTsCacheBuffer->pu8Addr + u32Tail;
        u32Len1 = u32Len;
    }

    /*memcpy don't need the mutex, so we could unlock the mutex in case blocking the read*/
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    memcpy(pu8Addr1, pu8RecData, u32Len1);
    if ((HI_NULL != pu8Addr2) && (0 != u32Len2))
    {
        memcpy(pu8Addr2, pu8RecData + u32Len1, u32Len2);
    }

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
    pstTsCacheBuffer->u32UsedSize += u32Len;
    PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_WRITE);
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_FlushBegin
 Description        : flush the data from ts cache buffer to the files.
                           because the write is done by other function, so support begin and end two function.
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
#ifdef HI_PVR_FIFO_DIO
HI_S32 PVR_TS_CACHE_BUFFER_FlushBegin(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer,
                                      HI_U8** pTsBuffData, HI_U32* pu32DataLen, HI_BOOL bForceWrite)
#else
HI_S32 PVR_TS_CACHE_BUFFER_FlushBegin(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U8** pTsBuffData, HI_U32* pu32DataLen)
#endif
{
    HI_U32 u32FlushSize = 0;

    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pTsBuffData) || (HI_NULL == pu32DataLen))
    {
        HI_ERR_PVR("Null pointer for pTsBuffData(%p) or pu32DataLen(%p)\n", pTsBuffData, pu32DataLen);
        return HI_FAILURE;
    }

    if ((HI_NULL == pstTsCacheBuffer) || (0 == pstTsCacheBuffer->u32Size))
    {
        HI_ERR_PVR("Null pointer(%p) or zero length!\n", pstTsCacheBuffer);
        return HI_FAILURE;
    }

    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, HI_FAILURE);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
    if (PVR_CACHE_BUFFER_STATE_BUTT == pstTsCacheBuffer->enState)
    {
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        HI_ERR_PVR("invalid state(0x%x)\n", pstTsCacheBuffer->enState);
        return HI_FAILURE;
    }

    /*check and set current state*/
    (HI_VOID)PVRTsCacheBufferChechAndWait(pstTsCacheBuffer, PVR_CACHE_BUFFER_FLUSH_INVALID);
    PVR_CACHE_BUFFER_SET_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_FLUSH);

    /*if rewind, flush by two times because only one output address is inputed*/
    *pTsBuffData = pstTsCacheBuffer->pu8Addr + pstTsCacheBuffer->u32Head;
    u32FlushSize = PVR_REC_TS_QUEUE_BLOCK;/*max size one time*/

    if (u32FlushSize > pstTsCacheBuffer->u32UsedSize)
    {
#ifdef HI_PVR_FIFO_DIO
        if (HI_TRUE == bForceWrite)
        {
#endif
            if (pstTsCacheBuffer->u32Head + pstTsCacheBuffer->u32UsedSize > pstTsCacheBuffer->u32Size)
            {
                u32FlushSize = pstTsCacheBuffer->u32Size - pstTsCacheBuffer->u32Head;
            }
            else
            {
                u32FlushSize = pstTsCacheBuffer->u32UsedSize;
            }
#ifdef HI_PVR_FIFO_DIO
        }
        else
        {
            if (pstTsCacheBuffer->u32Head + pstTsCacheBuffer->u32UsedSize > pstTsCacheBuffer->u32Size)
            {
                u32FlushSize = pstTsCacheBuffer->u32Size - pstTsCacheBuffer->u32Head;
            }
            else
            {
                HI_WARN_PVR("current data is not enough, so flush next!head/used/total:%u/%u/%u\n",
                            pstTsCacheBuffer->u32Head, pstTsCacheBuffer->u32UsedSize, pstTsCacheBuffer->u32Size);
                PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_FLUSH);
                PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
                return HI_FAILURE;
            }
        }
#endif
    }

    /*if including end of the buffer, only flush the end*/
    if (u32FlushSize + pstTsCacheBuffer->u32Head > pstTsCacheBuffer->u32Size)
    {
        u32FlushSize = pstTsCacheBuffer->u32Size - pstTsCacheBuffer->u32Head;
    }

    if (0 == u32FlushSize)
    {
        HI_WARN_PVR("current data is not enough, so flush next!head/used/total:%u/%u/%u\n",
                    pstTsCacheBuffer->u32Head, pstTsCacheBuffer->u32UsedSize, pstTsCacheBuffer->u32Size);
        PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_FLUSH);
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        return HI_FAILURE;
    }

    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    *pu32DataLen = u32FlushSize;

    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_FlushEnd
 Description        : update the head, usedsize and state.
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_S32 PVR_TS_CACHE_BUFFER_FlushEnd(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U32 u32Len)
{
    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pstTsCacheBuffer) || (0 == pstTsCacheBuffer->u32Size))
    {
        HI_ERR_PVR("Null pointer(%p) or zero length!\n", pstTsCacheBuffer);
        return HI_FAILURE;
    }

    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, HI_FAILURE);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));

    /*only flush state  support the flushend operation*/
    if (0 == (PVR_CACHE_BUFFER_STATE_FLUSH & pstTsCacheBuffer->enState))
    {
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        HI_ERR_PVR("invalid state(%d)\n", pstTsCacheBuffer->enState);
        return HI_FAILURE;
    }

    /*update the head, usedsize, globaloffset and state*/
    pstTsCacheBuffer->u32Head = (pstTsCacheBuffer->u32Head + u32Len) % pstTsCacheBuffer->u32Size;
    pstTsCacheBuffer->u32UsedSize = (pstTsCacheBuffer->u32UsedSize >= u32Len) ? (pstTsCacheBuffer->u32UsedSize - u32Len) : 0;
    pstTsCacheBuffer->u64HeadGlobalOffset += u32Len;
    PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_FLUSH);

    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_CheckCached
 Description        : check if buffer is cached the needed data.
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_U32 PVR_TS_CACHE_BUFFER_CheckCached(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U64 u64GlobalOffset)
{
    /*default is zero means that none needed data is cached*/
    HI_U32 u32CachedSize = 0;

    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pstTsCacheBuffer) || (0 == pstTsCacheBuffer->u32Size) || (0 == pstTsCacheBuffer->u32UsedSize))
    {
        /*pstTsCacheBuffer->u32UsedSize may be zero, so don't use err-level log*/
        HI_WARN_PVR("Null pointer(%p) or zero length(%u) or zero usedLen(%u)!\n",
                    pstTsCacheBuffer, pstTsCacheBuffer->u32Size, pstTsCacheBuffer->u32UsedSize);
        return u32CachedSize;
    }

    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, u32CachedSize);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));

    if (u64GlobalOffset < pstTsCacheBuffer->u64HeadGlobalOffset + pstTsCacheBuffer->u32UsedSize)
    {
        u32CachedSize = (HI_U32)(pstTsCacheBuffer->u64HeadGlobalOffset + pstTsCacheBuffer->u32UsedSize - u64GlobalOffset);
    }

    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    HI_PVR_DEBUG_EXIT();

    return u32CachedSize;
}

/*****************************************************************************
 Prototype          : PVR_TS_CACHE_BUFFER_ReadFromBuffer
 Description        : read data from the cached buffer. return the read size
 Return Value      :
 Global Variable
    Read Only       :
    Read & Write   :
  History
  1.Date             : 2017/01/09
    Author           : sdk
    Modification   : Created function
*****************************************************************************/
HI_S32 PVR_TS_CACHE_BUFFER_ReadFromBuffer(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U64 u64GlobalOffset, HI_U32 u32DataLen, HI_U8* pu8Buf)
{
    HI_U32 u32CachedSize = 0;
    HI_U32 u32OffsetCached = 0;
    HI_U32 u32OffsetOutBuf = 0;
    HI_U32 u32LenTemp = 0;
    HI_U8* pu8StartAddr = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    if ((HI_NULL == pstTsCacheBuffer) || (0 == pstTsCacheBuffer->u32Size) || (0 == pstTsCacheBuffer->u32UsedSize))
    {
        /*pstTsCacheBuffer->u32UsedSize may be zero, so don't use err-level log*/
        HI_WARN_PVR("Null pointer(%p) or zero length(%u) or zero usedLen(%u)!\n",
                    pstTsCacheBuffer, pstTsCacheBuffer->u32Size, pstTsCacheBuffer->u32UsedSize);
        return 0;
    }

    PVR_TS_CACHE_BUFFER_CHECK_INVALID_RETURN(pstTsCacheBuffer, 0);

    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));

    /*check and set current state*/
    (HI_VOID)PVRTsCacheBufferChechAndWait(pstTsCacheBuffer, PVR_CACHE_BUFFER_READ_INVALID);
    PVR_CACHE_BUFFER_SET_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_READ);

    HI_WARN_PVR("Current info:(R_offset/R_len/B_Offset/B_Len:0x%08llx/0x%08x/0x%08llx/0x%08x)\n",
                u64GlobalOffset, u32DataLen, pstTsCacheBuffer->u64HeadGlobalOffset, pstTsCacheBuffer->u32UsedSize);

    /*some ts data hasn't been received*/
    if (u64GlobalOffset + u32DataLen > pstTsCacheBuffer->u64HeadGlobalOffset + pstTsCacheBuffer->u32UsedSize)
    {
        PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_READ);
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        return -1;
    }

    /*none of the needed data is cached*/
    if (u64GlobalOffset + u32DataLen  <= pstTsCacheBuffer->u64HeadGlobalOffset)
    {
        PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_READ);
        PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));
        return 0;
    }

    if (u64GlobalOffset >= pstTsCacheBuffer->u64HeadGlobalOffset) /*all ts data is cached*/
    {
        u32OffsetOutBuf = 0;
        u32CachedSize = u32DataLen;
        u32OffsetCached = u64GlobalOffset - pstTsCacheBuffer->u64HeadGlobalOffset;/*offset from the pstTsCacheBuffer->u32Head*/
    }
    else /*some ts data is cached*/
    {
        u32CachedSize = u32DataLen - (HI_U32)(pstTsCacheBuffer->u64HeadGlobalOffset - u64GlobalOffset);
        u32OffsetOutBuf = u32DataLen - u32CachedSize;
        u32OffsetCached = 0;
    }

    /*unlock the mutex in case blocking the write*/
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    u32OffsetCached = (pstTsCacheBuffer->u32Head + u32OffsetCached) % pstTsCacheBuffer->u32Size;

    HI_WARN_PVR("(u32OffsetCached/u32CachedSize/u32OffsetOutBuf:%u/%u/%u)\n", u32OffsetCached, u32CachedSize, u32OffsetOutBuf);

    /*for some ts data is cached, the cached data is located on the tail, so we use u32OffsetOutBuf to tell the offset*/
    if (u32OffsetCached + u32CachedSize > pstTsCacheBuffer->u32Size)
    {
        pu8StartAddr = pstTsCacheBuffer->pu8Addr + u32OffsetCached;
        u32LenTemp = pstTsCacheBuffer->u32Size - u32OffsetCached;
        memcpy(pu8Buf + u32OffsetOutBuf, pu8StartAddr, u32LenTemp);
        memcpy(pu8Buf + u32OffsetOutBuf + u32LenTemp, pstTsCacheBuffer->pu8Addr, (u32CachedSize - u32LenTemp));
    }
    else
    {
        pu8StartAddr = pstTsCacheBuffer->pu8Addr + u32OffsetCached;
        memcpy(pu8Buf + u32OffsetOutBuf, pu8StartAddr, u32CachedSize);
    }

    /*update the state*/
    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
    PVR_CACHE_BUFFER_CLEAR_STATE(pstTsCacheBuffer->enState, PVR_CACHE_BUFFER_STATE_READ);
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    HI_PVR_DEBUG_EXIT();

    return (HI_S32)u32CachedSize;
}

/*CNcomment: 该函数主要用于在续录或者Pid 变更时做512 对齐处理使用的，reset 就是对extra buffer中涉及变更的变量
    进行归零，但是HeadGlobalOffset 却需要另做处理*/
HI_S32 PVR_TS_CACHE_BUFFER_Reset(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U64 u64HeadGlobalOffset)
{
    HI_PVR_DEBUG_ENTER();

    if (HI_NULL == pstTsCacheBuffer)
    {
        HI_ERR_PVR("Null pointer(%p)!\n", pstTsCacheBuffer);
        return HI_FAILURE;
    }
    
    PVR_LOCK(&(pstTsCacheBuffer->stCacheMutex));
    pstTsCacheBuffer->u32Head = 0;
    pstTsCacheBuffer->u32UsedSize = 0;
    pstTsCacheBuffer->u64HeadGlobalOffset = u64HeadGlobalOffset;
    PVR_UNLOCK(&(pstTsCacheBuffer->stCacheMutex));

    HI_PVR_DEBUG_EXIT();

    return HI_SUCCESS;
}

#endif
