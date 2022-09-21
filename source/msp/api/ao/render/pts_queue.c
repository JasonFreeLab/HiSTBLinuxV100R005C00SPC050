/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pts_queue.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/06/28
  Description  :
  History       :
  1.Date        : 2016/06/28
    Author      :
    Modification: Created file

*******************************************************************************/
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pts_queue.h"
#include "hi_drv_ao.h"
#include "hi_error_mpi.h"
#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define QUEUE_MAX_CAP (2048)
#define PTS_MASK      (QUEUE_MAX_CAP - 1)

typedef struct
{
    HI_U32   u32Pts;
    HI_U32   u32OrgPts;
    HI_U32   u32BeginPos;
    HI_U32   u32EndPos;
    HI_BOOL  bInjecting;  //cur queue data being injected
} PTS_ATTR_S;

typedef struct
{
    HI_BOOL     bInited;
    HI_U32      u32WriteIndex;
    HI_U32      u32ReadIndex;
    PTS_ATTR_S* pstPtsAttr;
} PTS_QUEUE_S;

HI_S32 PTSQUEUE_Create(HI_VOID** pHandle)
{
    HI_U32 u32Index = 0;
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(pHandle);

    pstPtsQueue = (PTS_QUEUE_S*)malloc(sizeof(PTS_QUEUE_S));
    if (HI_NULL == pstPtsQueue)
    {
        HI_ERR_AO("Pts queue malloc failed\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }
    memset(pstPtsQueue, 0, sizeof(PTS_QUEUE_S));

    pstPtsQueue->pstPtsAttr = (PTS_ATTR_S*)malloc(sizeof(PTS_ATTR_S) * QUEUE_MAX_CAP);
    if (HI_NULL == pstPtsQueue->pstPtsAttr)
    {
        free(pstPtsQueue);
        HI_ERR_AO("Pts attr malloc failed\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }
    memset(pstPtsQueue->pstPtsAttr, 0, sizeof(PTS_ATTR_S)*QUEUE_MAX_CAP);

    for (u32Index = 0; u32Index < QUEUE_MAX_CAP; u32Index++)
    {
        pstPtsQueue->pstPtsAttr[u32Index].u32Pts = HI_INVALID_PTS;
    }

    *pHandle = (HI_VOID*)pstPtsQueue;

    return HI_SUCCESS;
}

HI_S32 PTSQUEUE_Detroy(HI_VOID* handle)
{
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;

    free(pstPtsQueue->pstPtsAttr);
    pstPtsQueue->pstPtsAttr = HI_NULL;

    free(pstPtsQueue);

    return HI_SUCCESS;
}

HI_S32 PTSQUEUE_Put(HI_VOID* handle, HI_U32 u32Pts, HI_U32 u32DataSize)
{
    HI_U32 u32PrevWriteIndex = 0;
    HI_U32 u32CurrentWriteIndex = 0;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->pstPtsAttr;

    if (HI_INVALID_PTS == u32Pts || pstPtsAttr[u32CurrentWriteIndex].u32Pts == u32Pts)
    {
        if (HI_TRUE == pstPtsQueue->bInited)
        {
            u32CurrentWriteIndex = pstPtsQueue->u32WriteIndex & PTS_MASK;
        }
        pstPtsAttr[u32CurrentWriteIndex].u32EndPos += u32DataSize;

        PTS_PRINTF("PutPts add Pts:%d Size:%d -> Queue[%d].Pts:%d, BeginPos:%d EndPos:%d\n", u32Pts, u32DataSize, u32CurrentWriteIndex, pstPtsAttr[u32CurrentWriteIndex].u32Pts,
                   pstPtsAttr[u32CurrentWriteIndex].u32BeginPos, pstPtsAttr[u32CurrentWriteIndex].u32EndPos);
    }
    else
    {
        if (HI_FALSE == pstPtsQueue->bInited)
        {
            u32CurrentWriteIndex = pstPtsQueue->u32WriteIndex & PTS_MASK;
            pstPtsAttr[u32CurrentWriteIndex].u32BeginPos = 0;
        }
        else
        {
            u32PrevWriteIndex = pstPtsQueue->u32WriteIndex & PTS_MASK;
            pstPtsQueue->u32WriteIndex = (pstPtsQueue->u32WriteIndex + 1) & PTS_MASK;
            u32CurrentWriteIndex = pstPtsQueue->u32WriteIndex & PTS_MASK;

            pstPtsAttr[u32CurrentWriteIndex].u32BeginPos = pstPtsAttr[u32PrevWriteIndex].u32EndPos;
            pstPtsAttr[u32PrevWriteIndex].bInjecting = HI_FALSE;
        }
        pstPtsAttr[u32CurrentWriteIndex].u32Pts = u32Pts;
        pstPtsAttr[u32CurrentWriteIndex].u32OrgPts = u32Pts;
        pstPtsAttr[u32CurrentWriteIndex].u32EndPos = (pstPtsAttr[u32CurrentWriteIndex].u32BeginPos + u32DataSize);

        PTS_PRINTF("PutPts new Pts:%d Size:%d-> Queue[%d].Pts:%d, BeginPos:%d EndPos:%d\n", u32Pts, u32DataSize, u32CurrentWriteIndex, pstPtsAttr[u32CurrentWriteIndex].u32Pts,
                   pstPtsAttr[u32CurrentWriteIndex].u32BeginPos, pstPtsAttr[u32CurrentWriteIndex].u32EndPos);

    }

    pstPtsAttr[u32CurrentWriteIndex].bInjecting = HI_TRUE;

    if (HI_FALSE == pstPtsQueue->bInited)
    {
        pstPtsQueue->bInited = HI_TRUE;
    }

    PTS_PRINTF("PutPts ReadIndex:%d WriteIndex:%d \n", pstPtsQueue->u32ReadIndex, pstPtsQueue->u32WriteIndex);

    return HI_SUCCESS;
}

HI_S32 PTSQUEUE_Find(HI_VOID* handle, HI_U32 u32Pos, HI_U32* pu32Pts)
{
    HI_U32 u32Idx;
    HI_U32 u32ReadIndex;
    HI_U32 u32WriteIndex;
    HI_U32 u32QueueSize = 0;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->pstPtsAttr;

    u32ReadIndex = pstPtsQueue->u32ReadIndex;
    u32WriteIndex = pstPtsQueue->u32WriteIndex;

    PTS_PRINTF("FindPts ReadIndex:%d WriteIndex:%d find pos:%d\n", u32ReadIndex, u32WriteIndex, u32Pos);

    if (u32ReadIndex == u32WriteIndex)
    {
        u32QueueSize = (HI_TRUE == pstPtsQueue->pstPtsAttr[u32WriteIndex].bInjecting) ? 1 : 0; //only one package
    }
    else
    {
        u32QueueSize = (u32WriteIndex > u32ReadIndex) ? (u32WriteIndex - u32ReadIndex + 1) : (QUEUE_MAX_CAP - u32ReadIndex + u32WriteIndex);
    }

    for (u32Idx = 0; u32Idx < u32QueueSize; u32Idx++)
    {
        u32ReadIndex = (pstPtsQueue->u32ReadIndex + u32Idx) & PTS_MASK;

        PTS_PRINTF("FindPts Queue[%d] BeginPos:%d EndPos:%d\n", u32ReadIndex, pstPtsAttr[u32ReadIndex].u32BeginPos, pstPtsAttr[u32ReadIndex].u32EndPos);

        if (pstPtsAttr[u32ReadIndex].u32BeginPos < pstPtsAttr[u32ReadIndex].u32EndPos)
        {
            if ((pstPtsAttr[u32ReadIndex].u32BeginPos <= u32Pos) && (pstPtsAttr[u32ReadIndex].u32EndPos > u32Pos))
            {
                *pu32Pts = pstPtsAttr[u32ReadIndex].u32Pts;

                PTS_PRINTF("FindPts Cirtcl Pos:%d Pts:%d BeginPos:%d EndPos:%d\n",
                           u32Pos, pstPtsAttr[u32ReadIndex].u32Pts,
                           pstPtsAttr[u32ReadIndex].u32BeginPos, pstPtsAttr[u32ReadIndex].u32EndPos);
                break;
            }
        }
        else
        {
            if ((pstPtsAttr[u32ReadIndex].u32BeginPos <= u32Pos) || (pstPtsAttr[u32ReadIndex].u32EndPos > u32Pos))
            {
                *pu32Pts = pstPtsAttr[u32ReadIndex].u32Pts;

                PTS_PRINTF("FindPts Pos:%d Pts:%d BeginPos:%d EndPos:%d\n",
                           u32Pos, pstPtsAttr[u32ReadIndex].u32Pts,
                           pstPtsAttr[u32ReadIndex].u32BeginPos, pstPtsAttr[u32ReadIndex].u32EndPos);

                break;
            }
        }
    }

    pstPtsQueue->u32ReadIndex = u32ReadIndex;

    return HI_SUCCESS;
}

HI_S32 PTSQUEUE_Update(HI_VOID* handle, HI_U32 u32Delta)
{
    HI_U32 u32ReadIndex;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->pstPtsAttr;
    u32ReadIndex = pstPtsQueue->u32ReadIndex;

    if (HI_INVALID_PTS != pstPtsAttr[u32ReadIndex].u32Pts)
    {
        pstPtsAttr[u32ReadIndex].u32Pts += u32Delta;
    }

    return HI_SUCCESS;
}

HI_U32 PTSQUEUE_GetReadPts(HI_VOID* handle)
{
    HI_U32 u32ReadIndex;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->pstPtsAttr;
    u32ReadIndex = pstPtsQueue->u32ReadIndex;

    return pstPtsAttr[u32ReadIndex].u32Pts;
}

HI_BOOL PTSQUEUE_CheckIsFull(HI_VOID* handle)
{
    HI_U32 u32PtsCnt = 0;
    HI_U32 u32ReadIndex;
    HI_U32 u32WriteIndex;
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;

    u32ReadIndex = pstPtsQueue->u32ReadIndex;
    u32WriteIndex = pstPtsQueue->u32WriteIndex;

    if (u32ReadIndex == u32WriteIndex)
    {
        u32PtsCnt = (HI_TRUE == pstPtsQueue->pstPtsAttr[u32WriteIndex].bInjecting) ? 1 : 0;
    }
    else
    {
        u32PtsCnt = (u32WriteIndex > u32ReadIndex) ? (u32WriteIndex - u32ReadIndex + 1) : (QUEUE_MAX_CAP - u32ReadIndex + u32WriteIndex);
    }

    if ((QUEUE_MAX_CAP - 1) == u32PtsCnt)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

PTS_SEEK_E PTSQUEUE_Seek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts)
{
    HI_U32 u32Idx;
    HI_U32 u32ReadIndex;
    HI_U32 u32ReadCnt = 0;
    HI_U32 u32WriteIndex;
    HI_U32 u32TotalSize;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    if (HI_NULL == handle)
    {
        return PTS_SEEK_BUTT;
    }

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->pstPtsAttr;

    u32ReadIndex = pstPtsQueue->u32ReadIndex;
    u32WriteIndex = pstPtsQueue->u32WriteIndex;

    if (u32ReadIndex == u32WriteIndex)
    {
        if (HI_TRUE != pstPtsQueue->pstPtsAttr[u32WriteIndex].bInjecting)
        {
            return PTS_SEEK_NONE;
        }
        u32TotalSize = 1;
    }
    else
    {
        u32TotalSize = (u32WriteIndex > u32ReadIndex) ? (u32WriteIndex - u32ReadIndex + 1) : (QUEUE_MAX_CAP - u32ReadIndex + u32WriteIndex + 1);
    }

    u32Idx = (u32ReadIndex & PTS_MASK);

    PTS_PRINTF("SeekPts Cur u32ReadIndex:%d u32WriteIndex:%d totalReadCnt:%d\n", u32ReadIndex, u32WriteIndex, u32TotalSize);

    for (u32ReadCnt = 0; u32ReadCnt < u32TotalSize; u32ReadCnt++)
    {
        if (HI_INVALID_PTS == pstPtsAttr[u32Idx].u32Pts)
        {
            u32Idx =  (u32Idx + 1) & PTS_MASK;
            continue;
        }

        if ((pstPtsAttr[u32Idx].u32Pts + RENDER_PTS_MAX_DIFF) >= u32TargetPts)
        {
            *pu32NearbyPts = pstPtsAttr[u32Idx].u32Pts;
            *pu32NearbyPos = pstPtsAttr[u32Idx].u32BeginPos;
            pstPtsQueue->u32ReadIndex += u32ReadCnt;
            PTS_PRINTF("SeekPts Queue[%d] NearbyPts:%d EndPos:%d\n", pstPtsQueue->u32ReadIndex, *pu32NearbyPts, *pu32NearbyPos);
            return PTS_SEEK_ALIGN;
        }

        /*if ((pstPtsAttr[u32Idx + 1].u32Pts > u32TargetPts) && (u32TotalSize > 1))
        {
            *pu32NearbyPts = pstPtsAttr[u32Idx].u32Pts;
            *pu32NearbyPos = pstPtsAttr[u32Idx].u32BeginPos;
            pstPtsQueue->u32ReadIndex += u32ReadCnt;
            return PTS_SEEK_FRAME;
        }*/

        u32Idx = (u32Idx + 1) & PTS_MASK;
    }
    PTS_PRINTF("SeekPts end u32Idx:%d u32ReadCnt:%d\n", u32Idx, u32ReadCnt);

    if (u32Idx >= 1)
    {
        *pu32NearbyPts = pstPtsAttr[u32Idx - 1].u32Pts;
        *pu32NearbyPos = pstPtsAttr[u32Idx - 1].u32BeginPos;
        PTS_PRINTF("SeekPts find NearbyPos:%d NearbyPts:%d u32Idx:%d\n", *pu32NearbyPos, *pu32NearbyPts, u32Idx);
    }

    if (u32ReadCnt >= 1)    //likely
    {
        pstPtsQueue->u32ReadIndex += (u32ReadCnt - 1);
    }

    return PTS_SEEK_PACKAGE;
}

PTS_SEEK_E PTSQUEUE_Drop_Seek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts)
{
    HI_U32 u32Idx;
    HI_U32 u32ReadIndex;
    HI_U32 u32ReadCnt = 0;
    HI_U32 u32WriteIndex;
    HI_U32 u32TotalSize;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    CHECK_AO_NULL_PTR(handle);
    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->pstPtsAttr;

    u32ReadIndex = pstPtsQueue->u32ReadIndex;
    u32WriteIndex = pstPtsQueue->u32WriteIndex;

    u32TotalSize = u32WriteIndex >= u32ReadIndex ? (u32WriteIndex - u32ReadIndex + 1) : (QUEUE_MAX_CAP - u32ReadIndex + u32WriteIndex + 1);
    if (0 == u32TotalSize)
    {
        return PTS_SEEK_NONE;
    }

    for (u32Idx = (u32ReadIndex & PTS_MASK); u32Idx != (u32WriteIndex & PTS_MASK); u32Idx++)
    {
        if (pstPtsAttr[u32Idx].u32Pts >= u32TargetPts)
        {
            *pu32NearbyPts = pstPtsAttr[u32Idx].u32Pts;
            *pu32NearbyPos = pstPtsAttr[u32Idx].u32BeginPos;
            pstPtsQueue->u32ReadIndex += u32ReadCnt;

            return PTS_SEEK_PACKAGE;
        }

        u32ReadCnt++;
    }

    *pu32NearbyPts = pstPtsAttr[u32Idx - 1].u32Pts;
    *pu32NearbyPos = pstPtsAttr[u32Idx - 1].u32BeginPos;
    pstPtsQueue->u32ReadIndex += u32ReadCnt;

    return PTS_SEEK_PACKAGE;
}

HI_S32 PTSQUEUE_Reset(HI_VOID* handle)
{
    HI_U32 u32Index = 0;
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;

    pstPtsQueue->bInited = HI_FALSE;
    pstPtsQueue->u32ReadIndex = 0;
    pstPtsQueue->u32WriteIndex = 0;

    memset(pstPtsQueue->pstPtsAttr, 0, sizeof(PTS_ATTR_S)*QUEUE_MAX_CAP);
    for (u32Index = 0; u32Index < QUEUE_MAX_CAP; u32Index++)
    {
        pstPtsQueue->pstPtsAttr[u32Index].u32Pts = HI_INVALID_PTS;
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
