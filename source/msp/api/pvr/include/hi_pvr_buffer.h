#ifndef __HI_PVR_BUFFER_H__
#define __HI_PVR_BUFFER_H__
#include <sys/ioctl.h>
#include <pthread.h>
#include "hi_type.h"

#ifdef HI_PVR_EXTRA_BUF_SUPPORT

#define PVR_REC_TS_QUEUE_BLOCK (0x2F000)/* write 188K one time */

/*one bit is a state, so it support two states at the same time*/
typedef enum tagPVR_CACHE_BUFFER_STATE_E
{
    PVR_CACHE_BUFFER_STATE_IDLE =   1,  /*support all action*/
    PVR_CACHE_BUFFER_STATE_READ =   2,  /*1 << 0 can't be flushed*/
    PVR_CACHE_BUFFER_STATE_WRITE =  4,  /*1 << 1 can't be flushed*/
    PVR_CACHE_BUFFER_STATE_FLUSH =  8,  /*1 << 2 can't be readed, written, flushed*/
    PVR_CACHE_BUFFER_STATE_BUTT =   16  /*1 << 3 invalid state*/
} PVR_CACHE_BUFFER_STATE_E;

typedef struct tagPVR_TS_CACHE_BUFF_INFO_S
{
    HI_U32 u32CheckCode;                /*magic num, used to check the buffer*/
    PVR_CACHE_BUFFER_STATE_E enState;   /*buffer state,*/
    HI_U8* pu8Addr;                     /*buffer address*/
    HI_U32 u32Size;                     /*total buffer size*/
    HI_U32 u32UsedSize;                 /*used buffer size*/
    HI_U32 u32Head;                     /*head offset in the buffer*/
    HI_U64 u64HeadGlobalOffset;         /*head globaloffset of the ts data, used for play*/
    pthread_mutex_t stCacheMutex;       /*mutex, used to support atomic of read, write and flush*/
} PVR_TS_CACHE_BUFF_INFO_S;

HI_S32 PVR_TS_CACHE_BUFFER_Init(HI_U32 u32RecBufSize, PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer);
HI_S32 PVR_TS_CACHE_BUFFER_DeInit(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer);
HI_U32 PVR_TS_CACHE_BUFFER_GetFreeSize(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer);
HI_U32 PVR_TS_CACHE_BUFFER_GetUsedSize(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer);
HI_S32 PVR_TS_CACHE_BUFFER_WriteToBuffer(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U8* pu8RecData, HI_U32 u32Len);
#ifdef HI_PVR_FIFO_DIO
HI_S32 PVR_TS_CACHE_BUFFER_FlushBegin(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer,
                                      HI_U8** pTsBuffData, HI_U32* pu32DataLen, HI_BOOL bForceWrite);
#else
HI_S32 PVR_TS_CACHE_BUFFER_FlushBegin(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U8** pTsBuffData, HI_U32* pu32DataLen);
#endif
HI_S32 PVR_TS_CACHE_BUFFER_FlushEnd(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U32 u32Len);
HI_U32 PVR_TS_CACHE_BUFFER_CheckCached(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U64 u64GlobalOffset);
HI_S32 PVR_TS_CACHE_BUFFER_ReadFromBuffer(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U64 u64GlobalOffset, HI_U32 u32DataLen, HI_U8* pu8Buf);
HI_S32 PVR_TS_CACHE_BUFFER_Reset(PVR_TS_CACHE_BUFF_INFO_S* pstTsCacheBuffer, HI_U64 u64HeadGlobalOffset);

#endif /*endif for HI_PVR_EXTRA_BUF_SUPPORT*/

#endif /*endif for __HI_PVR_BUFFER_H__*/
