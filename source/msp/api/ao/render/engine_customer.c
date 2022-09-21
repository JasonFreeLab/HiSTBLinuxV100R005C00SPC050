#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_drv_ao.h"
#include "engine_customer.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define ENGINE_MAX_PTS_MUTE_NUM          (64)
#define ENGINE_MAX_PTS_MUTE_START_DELTA  (64) //ms
#define ENGINE_MAX_PTS_MUTE_STOP_DELTA   (64) //ms

#define trace()  HI_INFO_AO("%s called\n", __func__)

static pthread_mutex_t g_PtsMuteQueueMutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    HI_U32 u32StartPts;
    HI_U32 u32StopPts;
    HI_BOOL bActivate;
} PTSMUTEQUEUE_ATTR_S;

static HI_VOID PTSMUTEQUEUE_LOCK()
{
    (void)pthread_mutex_lock(&g_PtsMuteQueueMutex);
}

static HI_VOID PTSMUTEQUEUE_UNLOCK()
{
    (void)pthread_mutex_unlock(&g_PtsMuteQueueMutex);
}

typedef struct
{
    PTSMUTEQUEUE_ATTR_S stPtsMuteAttr[ENGINE_MAX_PTS_MUTE_NUM];
    HI_U32 u32Index;
    HI_U32 u32Count;
} PTSMUTEQUEUE_S;

HI_S32 PTSMUTEQUEUE_Create(HI_VOID** phHandle)
{
    PTSMUTEQUEUE_S* pstPtsMute = HI_NULL;

    trace();
    CHECK_AO_NULL_PTR(phHandle);

    pstPtsMute = (PTSMUTEQUEUE_S*)malloc(sizeof(PTSMUTEQUEUE_S));
    if (HI_NULL == pstPtsMute)
    {
        HI_ERR_AO("malloc PTSMUTEQUEUE_S failed\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }

    memset(pstPtsMute, 0, sizeof(PTSMUTEQUEUE_S));
    *phHandle = (HI_VOID*)pstPtsMute;

    return HI_SUCCESS;
}

HI_VOID PTSMUTEQUEUE_Destroy(HI_VOID* pHandle)
{
    trace();

    PTSMUTEQUEUE_LOCK();

    free(pHandle);

    PTSMUTEQUEUE_UNLOCK();
}

HI_S32 PTSMUTEQUEUE_Add(HI_VOID* pHandle, HI_U32 u32StartPts, HI_U32 u32StopPts)
{
    HI_U32 u32WriteIndex;
    PTSMUTEQUEUE_S* pstPtsMute = (PTSMUTEQUEUE_S*)pHandle;

    trace();

    CHECK_AO_NULL_PTR(pHandle);
    PTSMUTEQUEUE_LOCK();

    if (pstPtsMute->u32Count >= (ENGINE_MAX_PTS_MUTE_NUM - 1))
    {
        HI_ERR_AO("PTSMUTEQUEUE is full\n");
        PTSMUTEQUEUE_UNLOCK();
        return HI_FAILURE;
    }

    u32WriteIndex = (pstPtsMute->u32Count + pstPtsMute->u32Index) & (ENGINE_MAX_PTS_MUTE_NUM - 1);

    pstPtsMute->stPtsMuteAttr[u32WriteIndex].u32StartPts = u32StartPts;
    pstPtsMute->stPtsMuteAttr[u32WriteIndex].u32StopPts = u32StopPts;
    pstPtsMute->stPtsMuteAttr[u32WriteIndex].bActivate = HI_FALSE;

    pstPtsMute->u32Count++;

    PTSMUTEQUEUE_UNLOCK();

    return HI_SUCCESS;
}

PTSMUTEQUEUE_POLICY PTSMUTEQUEUE_Find(HI_VOID* pHandle, HI_U32 u32Pts)
{
    HI_U32 u32Index;
    PTSMUTEQUEUE_S* pstPtsMute = (PTSMUTEQUEUE_S*)pHandle;

    CHECK_AO_NULL_PTR(pHandle);
    PTSMUTEQUEUE_LOCK();

    u32Index = pstPtsMute->u32Index;
    if (0 == pstPtsMute->u32Count)
    {
        PTSMUTEQUEUE_UNLOCK();
        return PTSMUTE_MUTE_NONE;
    }

    if ((HI_FALSE == pstPtsMute->stPtsMuteAttr[u32Index].bActivate) &&
        ((u32Pts + ENGINE_MAX_PTS_MUTE_START_DELTA) >= pstPtsMute->stPtsMuteAttr[u32Index].u32StartPts))
    {
        HI_INFO_AO("Pts Mute start, find Pts %d, start pts %d\n", u32Pts,  pstPtsMute->stPtsMuteAttr[u32Index].u32StartPts);
        pstPtsMute->stPtsMuteAttr[u32Index].bActivate = HI_TRUE;

        PTSMUTEQUEUE_UNLOCK();
        return PTSMUTE_MUTE_START;
    }

    if ((HI_TRUE == pstPtsMute->stPtsMuteAttr[u32Index].bActivate) &&
        (u32Pts >= (pstPtsMute->stPtsMuteAttr[u32Index].u32StopPts + ENGINE_MAX_PTS_MUTE_STOP_DELTA)))
    {
        HI_INFO_AO("Pts Mute stop, find Pts %d, stop pts %d\n", u32Pts,  pstPtsMute->stPtsMuteAttr[u32Index].u32StopPts);
        pstPtsMute->stPtsMuteAttr[u32Index].bActivate = HI_FALSE;
        pstPtsMute->u32Index = (pstPtsMute->u32Index + 1) & (ENGINE_MAX_PTS_MUTE_NUM - 1);
        pstPtsMute->u32Count--;

        PTSMUTEQUEUE_UNLOCK();
        return PTSMUTE_MUTE_STOP;
    }
    PTSMUTEQUEUE_UNLOCK();

    return PTSMUTE_MUTE_NONE;
}

HI_S32 PTSMUTEQUEUE_Reset(HI_VOID* pHandle)
{
    PTSMUTEQUEUE_S* pstPtsMute = (PTSMUTEQUEUE_S*)pHandle;

    trace();

    CHECK_AO_NULL_PTR(pHandle);
    PTSMUTEQUEUE_LOCK();

    pstPtsMute->u32Index = 0;
    pstPtsMute->u32Count = 0;

    PTSMUTEQUEUE_UNLOCK();

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

