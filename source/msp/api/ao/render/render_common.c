/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_common.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <string.h>
#include <stdlib.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

static pthread_mutex_t g_RenderMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_HacodeMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_SinkMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_BufAcquireMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_ProcMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_SourceInstMutex[SOURCE_ID_BUTT] =
    {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};
static pthread_mutex_t g_SourceInstMutex2[SOURCE_ID_BUTT] =
    {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};
static pthread_mutex_t g_SourceIOMutex[SOURCE_ID_BUTT] =
    {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};

HI_VOID RENDER_LOCK(HI_VOID)
{
    //lock debug
    (void)pthread_mutex_lock(&g_RenderMutex);
}

HI_VOID RENDER_UNLOCK(HI_VOID)
{
    (void)pthread_mutex_unlock(&g_RenderMutex);
}

HI_VOID BUF_ACQUIRE_LOCK(HI_VOID)
{
    (void)pthread_mutex_lock(&g_BufAcquireMutex);
}

HI_VOID BUF_ACQUIRE_UNLOCK(HI_VOID)
{
    (void)pthread_mutex_unlock(&g_BufAcquireMutex);
}

HI_VOID SOURCE_INST_LOCK(SOURCE_ID_E enSourceID)
{
    (void)pthread_mutex_lock(&g_SourceInstMutex[enSourceID]);
}

HI_VOID SOURCE_INST_UNLOCK(SOURCE_ID_E enSourceID)
{
    (void)pthread_mutex_unlock(&g_SourceInstMutex[enSourceID]);
}

HI_VOID SOURCE_INST2_LOCK(SOURCE_ID_E enSourceID)
{
    (void)pthread_mutex_lock(&g_SourceInstMutex2[enSourceID]);
}

HI_VOID SOURCE_INST2_UNLOCK(SOURCE_ID_E enSourceID)
{
    (void)pthread_mutex_unlock(&g_SourceInstMutex2[enSourceID]);
}

HI_VOID SOURCE_IO_LOCK(SOURCE_ID_E enSourceID)
{
    (void)pthread_mutex_lock(&g_SourceIOMutex[enSourceID]);
}

HI_VOID SOURCE_IO_UNLOCK(SOURCE_ID_E enSourceID)
{
    (void)pthread_mutex_unlock(&g_SourceIOMutex[enSourceID]);
}

HI_VOID HACODEC_INST_LOCK(HI_VOID)
{
    (void)pthread_mutex_lock(&g_HacodeMutex);
}

HI_VOID HACODEC_INST_UNLOCK(HI_VOID)
{
    (void)pthread_mutex_unlock(&g_HacodeMutex);
}

HI_VOID SINK_LOCK(HI_VOID)
{
    (void)pthread_mutex_lock(&g_SinkMutex);
}

HI_VOID SINK_UNLOCK(HI_VOID)
{
    (void)pthread_mutex_unlock(&g_SinkMutex);
}

HI_VOID PROC_LOCK(HI_VOID)
{
    (void)pthread_mutex_lock(&g_ProcMutex);
}

HI_S32 PROC_TRYLOCK(HI_VOID)
{
     return pthread_mutex_trylock(&g_ProcMutex);
}

HI_VOID PROC_UNLOCK(HI_VOID)
{
    (void)pthread_mutex_unlock(&g_ProcMutex);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
