/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_source.c
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
#include "hi_mpi_ao.h"

#include "render_common.h"
#include "render_buffer.h"
#include "pts_queue.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

#define MS12_TRACK_MASK          (0x88)
#define RENDER_TRACK_MASK        (0xff)
#define RENDER_TRACK_MAXNUM      (0x0f)
#define RENDER_TRACK_IDOFFSET    (0x08)
#define MAX_PTS_FILE_PATH_LEN    (40)
#define VALIDATE_PTS_WRITE_LEN   (22)
#define INVALIDATE_PTS_WRITE_LEN (11)

typedef struct
{
    HI_BOOL bInited;
    HI_BOOL bIDAlloced[RENDER_TRACK_MAXNUM];
    HI_BOOL bTrackCreated[RENDER_TRACK_MAXNUM];
} SOURCE_IDM_S;

static SOURCE_MANAGER_S* g_pstSourceManager = HI_NULL;
static RENDER_MANAGER_S* g_pstSourceRenderManager = HI_NULL;

static SOURCE_IDM_S g_stMediaTrackIDM =
{
    .bInited = HI_FALSE,
};

#define CHECK_AND_GET_SOURCEIDFROMTRACKID(u32TrackID, enSourceID) \
    do { \
        if (((u32TrackID & 0xf000) != (HI_ID_RENDER_TRACK << 12)) || \
            (SOURCE_ID_BUTT <= (u32TrackID & RENDER_TRACK_MASK))) \
        { \
            HI_ERR_AO("Invalid track id(0x%x) failed\n", u32TrackID); \
            return HI_ERR_AO_INVALID_PARA; \
        } \
        enSourceID = (SOURCE_ID_E)(u32TrackID & RENDER_TRACK_MASK); \
    } while(0)

#define CHECK_TRACK_SYNCMODE(enSyncMode) \
    do { \
        if (HI_MPI_AO_TRACK_SYNCMODE_BUTT == enSyncMode) \
        { \
            HI_ERR_AO("Invalid Sync Mode(%d)\n", enSyncMode); \
            return HI_ERR_AO_INVALID_PARA; \
        } \
    } while(0)

static HI_BOOL CheckIsNeedDuplicate(SOURCE_ID_E enSourceID)
{
    return (SOURCE_ID_MAIN == enSourceID);
}

static HI_BOOL CheckIsNeedLoadRenderLib(SOURCE_ID_E enSourceID)
{
    return (HI_BOOL)((SOURCE_ID_SYSTEM == enSourceID) || (SOURCE_ID_TTS == enSourceID));
}

static HI_BOOL CheckIsSourceDuplicate(SOURCE_ID_E enSourceID)
{
    return g_pstSourceManager->pstSource[enSourceID]->bDual;
}

static HI_BOOL CheckIsMediaTrack(HI_HANDLE hTrack)
{
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    return (HI_BOOL)((SOURCE_ID_MAIN == enSourceID) || (SOURCE_ID_ASSOC == enSourceID));
}

static HI_BOOL CheckIsMediaTrackIDApplied(HI_HANDLE hTrack)
{
    CHANNEL_TRACE();

    return g_stMediaTrackIDM.bIDAlloced[((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1];
}

static HI_BOOL CheckIsMediaTrackCreated(HI_HANDLE hTrack)
{
    CHANNEL_TRACE();

    return g_stMediaTrackIDM.bTrackCreated[((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1];
}

#ifdef RENDER_DEBUG_SUPPORT
static HI_VOID Filewrite(HI_VOID* pData, HI_U32 u32Size, HI_U32 u32Count, FILE* pFile)
{
    HI_U32 u32WroteSize;

    u32WroteSize = fwrite(pData, u32Size, u32Count, pFile);
    if (u32Count != u32WroteSize)
    {
        HI_WARN_AO("Source_fwrite failed to write %d but %d wrote)\n", u32Count, u32WroteSize);
    }
}
#endif

static HI_UNF_SND_TRACK_TYPE_E GetTrackTypeFromSourceID(SOURCE_ID_E enSourceID)
{
    //trace();

    if (SOURCE_ID_SYSTEM == enSourceID)
    {
        return HI_UNF_SND_TRACK_TYPE_SYS;
    }
    else if (SOURCE_ID_TTS == enSourceID)
    {
        return HI_UNF_SND_TRACK_TYPE_TTS;
    }
    else
    {
        HI_ERR_AO("Unknown source id (0x%x)\n", enSourceID);
    }

    return HI_UNF_SND_TRACK_TYPE_BUTT;
}

static SOURCE_ID_E GetSourceIDFromTrackAttr(const HI_MPI_AO_RENDER_ATTR_S* pstTrackAttr)
{
    trace();

    if (HI_MPI_RENDER_TRACK_TYPE_MAIN == pstTrackAttr->enType)
    {
        return SOURCE_ID_MAIN;
    }
    else if (HI_MPI_RENDER_TRACK_TYPE_SYS == pstTrackAttr->enType)
    {
        return SOURCE_ID_SYSTEM;
    }
    else if (HI_MPI_RENDER_TRACK_TYPE_TTS == pstTrackAttr->enType)
    {
        return SOURCE_ID_TTS;
    }
    else
    {
        HI_ERR_AO("Invalid Track Type(0x%x)\n", pstTrackAttr->enType);
    }

    return SOURCE_ID_BUTT;
}

static HI_U32 GetTrackIDFromSourceID(SOURCE_ID_E enSourceID)
{
    //trace();

    /*
      define of Track Handle :
      bit31                                                                    bit0
        |<----   16bit --------->|<--   4bit  -->|<--  4bit  -->|<---  8bit  --->|
        |------------------------------------------------------------------------|
        |      HI_MOD_ID_E       | render defined | idm defined  |     chnID     |
        |------------------------------------------------------------------------|
      */

    return (HI_ID_AO << 16) | (HI_ID_RENDER_TRACK << 12) | enSourceID;
}

static SOURCE_ID_E GetSourceIDFromTrackID(HI_HANDLE hTrack)
{
    //trace();
    return (SOURCE_ID_E)(hTrack & RENDER_TRACK_MASK);
}

static HI_VOID MediaTrackIDMInit(HI_VOID)
{
    CHANNEL_TRACE();

    if (HI_FALSE == g_stMediaTrackIDM.bInited)
    {
        memset(&g_stMediaTrackIDM, 0, sizeof(SOURCE_IDM_S));
        g_stMediaTrackIDM.bInited = HI_TRUE;
    }
}

static HI_S32 MediaTrackIDMAlloc(SOURCE_ID_E enSourceID, HI_HANDLE* phTrack)
{
    HI_U32 u32ID;

    CHANNEL_TRACE();

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM; u32ID++)
    {
        if (HI_FALSE == g_stMediaTrackIDM.bIDAlloced[u32ID])
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_ERR_AO("Too many render track failed(0x%x)!\n", u32ID);
        return HI_FAILURE;
    }

    g_stMediaTrackIDM.bIDAlloced[u32ID] = HI_TRUE;
    g_stMediaTrackIDM.bTrackCreated[u32ID] = HI_FALSE;

    *phTrack = (HI_ID_AO << 16) | (HI_ID_RENDER_TRACK << 12) | ((u32ID + 1) << RENDER_TRACK_IDOFFSET | enSourceID);

    HI_INFO_AO("Alloc id (0x%x)!\n", *phTrack);

    return HI_SUCCESS;
}

static HI_S32 MediaTrackIDMDeAlloc(HI_HANDLE hTrack)
{
    HI_U32 u32ID = ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1;

    CHANNEL_TRACE();

    HI_INFO_AO("DeAlloc id (0x%x)!\n", u32ID);

    g_stMediaTrackIDM.bIDAlloced[u32ID] = HI_FALSE;

    return HI_SUCCESS;
}

static HI_S32 MediaTrackIDMCreate(HI_HANDLE hTrack)
{
    HI_U32 u32ID = ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1;

    CHANNEL_TRACE();

    CHANNEL_PRINTF("Create ID(0x%x)\n", u32ID);

    if ((HI_FALSE != g_stMediaTrackIDM.bTrackCreated[u32ID]) ||
        (HI_TRUE  != g_stMediaTrackIDM.bIDAlloced[u32ID]))
    {
        HI_ERR_AO("Track(0x%x) ID(x%x) is already created or ID is not alloced!\n", hTrack, u32ID);
        return HI_FAILURE;
    }

    g_stMediaTrackIDM.bTrackCreated[u32ID] = HI_TRUE;

    return HI_SUCCESS;
}

static HI_VOID MediaTrackIDMDestory(HI_HANDLE hTrack)
{
    HI_U32 u32ID = ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1;

    CHANNEL_TRACE();

    CHANNEL_PRINTF("Release ID(0x%x)\n", u32ID);

    if (HI_TRUE != g_stMediaTrackIDM.bIDAlloced[u32ID])
    {
        HI_ERR_AO("Track(0x%x) ID is not alloc!\n", hTrack);
    }

    g_stMediaTrackIDM.bTrackCreated[u32ID] = HI_FALSE;
}

#ifdef RENDER_DEBUG_SUPPORT
static HI_VOID SourceEsFileWrite(SOURCE_ID_E enSourceID, HI_U8 *pu8Data, HI_U32 u32Size)
{
    FILE_DUMP_S* pstEsDump = &g_pstSourceRenderManager->stDumpManager.stEsDump[enSourceID];

    if (HI_FALSE == pstEsDump->bSaved)
    {
       if (HI_NULL != pstEsDump->pDumpFile)
       {
            fclose(pstEsDump->pDumpFile);
            pstEsDump->pDumpFile = HI_NULL;
       }

       return;
    }

    if (HI_NULL == pstEsDump->pDumpFile)
    {
        HI_CHAR cSoureId[3];
        HI_CHAR cIndex[2];
        HI_CHAR cDumpFile[MAX_PTS_FILE_PATH_LEN];
        const HI_CHAR* aprefix = "/mnt/source_";
        const HI_CHAR* asuffix = ".es";

        memset(cSoureId, 0, 3);
        memset(cIndex, 0, 2);
        memset(cDumpFile, 0, MAX_PTS_FILE_PATH_LEN);

        strncpy(cDumpFile, aprefix, strlen(aprefix));
        cSoureId[0] = enSourceID + '0';
        cSoureId[1] = '_';
        strncat(cDumpFile, cSoureId, strlen(cSoureId));
        cIndex[0] = pstEsDump->u32CurFileIndex + '0'; //TOCheck
        strncat(cDumpFile, cIndex, strlen(cIndex));
        strncat(cDumpFile, asuffix, strlen(asuffix));

        HI_ERR_AO("[DEBUG INFO] Dump ES File: SourceID(%d) %s\n", enSourceID, cDumpFile);

        pstEsDump->pDumpFile = fopen(cDumpFile, "w");
        if (HI_NULL == pstEsDump->pDumpFile)
        {
            HI_ERR_AO("fopen dump file %s failed\n", cDumpFile);
            return;
        }

        pstEsDump->u32CurFileIndex++;
    }

    Filewrite(pu8Data, 1, u32Size, pstEsDump->pDumpFile);
}

static HI_VOID SourceEsFileClose(SOURCE_ID_E enSourceID)
{
    FILE_DUMP_S* pstEsDump = &g_pstSourceRenderManager->stDumpManager.stEsDump[enSourceID];

    if (HI_NULL != pstEsDump->pDumpFile)
    {
        fclose(pstEsDump->pDumpFile);
        pstEsDump->pDumpFile = HI_NULL;
    }
}

static HI_VOID SourcePtsFileWrite(SOURCE_ID_E enSourceID, HI_U32 u32PtsMs, HI_U32 u32Size)
{
    FILE_DUMP_S* pstPtsDump = &g_pstSourceRenderManager->stDumpManager.stPtsDump[enSourceID];
    HI_CHAR cPts[MAX_PTS_FILE_PATH_LEN] = {0};

    if (HI_FALSE == pstPtsDump->bSaved)
    {
       if (HI_NULL != pstPtsDump->pInPtsFile)
       {
            fclose(pstPtsDump->pInPtsFile);
            pstPtsDump->pInPtsFile = HI_NULL;
       }

       return;
    }

    if (HI_NULL == pstPtsDump->pInPtsFile)
    {
        HI_CHAR cFile[MAX_PTS_FILE_PATH_LEN];
        HI_CHAR cSoureId[2];
        const HI_CHAR* aprefix = "/mnt/source_in_";
        const HI_CHAR* asuffix = ".pts";

        memset(cSoureId, 0, 2);
        memset(cFile, 0, MAX_PTS_FILE_PATH_LEN);

        strncpy(cFile, aprefix, strlen(aprefix));
        cSoureId[0] = enSourceID + '0';
        strncat(cFile, cSoureId, 2);
        strncat(cFile, asuffix, strlen(asuffix));
        HI_INFO_AO("fopen source in pts %s\n", cFile);

        pstPtsDump->pInPtsFile = fopen(cFile, "w");
        if (HI_NULL == pstPtsDump->pInPtsFile)
        {
            HI_ERR_AO("fopen source in pts %s failed\n", cFile);
            return;
        }

        HI_ERR_AO("[DEBUG INFO] Dump In Pts File: SourceID(%d) %s\n", enSourceID, cFile);

        snprintf(cPts, MAX_PTS_FILE_PATH_LEN, "\n%08d,  %-10d", u32PtsMs, u32Size);
        Filewrite(cPts, 1, VALIDATE_PTS_WRITE_LEN, pstPtsDump->pInPtsFile);

        return;
    }

    if (HI_INVALID_PTS != u32PtsMs)
    {
        snprintf(cPts, MAX_PTS_FILE_PATH_LEN, "\n%08d,  %-10d", u32PtsMs, u32Size);
        Filewrite(cPts, 1, VALIDATE_PTS_WRITE_LEN, pstPtsDump->pInPtsFile);
    }
    else
    {
        snprintf(cPts, MAX_PTS_FILE_PATH_LEN, "%-10d", u32Size);
        Filewrite(cPts, 1, INVALIDATE_PTS_WRITE_LEN, pstPtsDump->pInPtsFile);
    }

    HI_INFO_AO("fput %08d, %10d\n", u32PtsMs, u32Size);
}

static HI_VOID SourcePtsFileClose(SOURCE_ID_E enSourceID)
{
    FILE_DUMP_S* pstPtsDump = &g_pstSourceRenderManager->stDumpManager.stPtsDump[enSourceID];

    if (HI_NULL != pstPtsDump->pInPtsFile)
    {
        fclose(pstPtsDump->pInPtsFile);
        pstPtsDump->pInPtsFile = HI_NULL;
    }
}
#endif

static HI_BOOL SourceCheckIsInstantiated(SOURCE_ID_E enSourceID)
{
    return (HI_BOOL)(HI_NULL != g_pstSourceManager->pstSource[enSourceID]);
}

static HI_BOOL SourceCheckIsSourceManagerInited(HI_VOID)
{
    return (HI_BOOL)(HI_NULL != g_pstSourceManager);
}

static HI_S32 SourceSetDuplicateStatus(SOURCE_ID_E enSourceID, HI_BOOL bDuplicate)
{
    SOURCE_S* pstSource;

    HI_INFO_AO("SourceSetDuplicateStatus enSourceID = %d, bDuplicate = %d\n", enSourceID, bDuplicate);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->bDual = bDuplicate;

    return HI_SUCCESS;
}

static HI_S32 SourceCreatePtsQueue(SOURCE_S* pstSource)
{
    trace();

    if ((SOURCE_ID_MAIN != pstSource->enSourceID) && (SOURCE_ID_ASSOC != pstSource->enSourceID))
    {
        return HI_SUCCESS;
    }

    return PTSQUEUE_Create(&pstSource->pPtsQueue);
}

static HI_S32 SourceDestoryPtsQueue(SOURCE_S* pstSource)
{
    trace();

    if ((SOURCE_ID_MAIN != pstSource->enSourceID) && (SOURCE_ID_ASSOC != pstSource->enSourceID))
    {
        return HI_SUCCESS;
    }

    if (HI_NULL != pstSource->pPtsQueue)
    {
        return PTSQUEUE_Detroy(pstSource->pPtsQueue);
    }

    return HI_FAILURE;
}

static HI_S32 SourceGetExtRenderOutBuf(SOURCE_ID_E enSourceID, HI_VOID** ppROutBuffer)
{
    *ppROutBuffer = g_pstSourceRenderManager->pstEngineManger->pROutBuffer[enSourceID];
    if (HI_NULL == *ppROutBuffer)
    {
        HI_ERR_AO("Source manager malloc failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 SourceAllocID(SOURCE_ID_E enSourceID, HI_HANDLE* phTrack)
{
    CHANNEL_TRACE();

    MediaTrackIDMInit();

    return MediaTrackIDMAlloc(enSourceID, phTrack);
}

static HI_S32 SourceDeallocID(HI_HANDLE hTrack)
{
    CHANNEL_TRACE();

    return MediaTrackIDMDeAlloc(hTrack);
}

static HI_S32 SourceCreate(SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;
    HI_VOID* pROutBuffer;
    SOURCE_S* pstSource;

    CHANNEL_TRACE();

    pstSource = (SOURCE_S*)malloc(sizeof(SOURCE_S));
    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Souce malloc failed!\n");
        return HI_FAILURE;
    }

    memset(pstSource, 0, sizeof(SOURCE_S));

    pstSource->enState = SOURCE_STATE_IDLE;
    pstSource->enSourceID = enSourceID;
    pstSource->u32CurStreamPts = HI_INVALID_PTS;
    pstSource->bMixing = HI_TRUE;
    pstSource->bDecoding = HI_TRUE;
    pstSource->bEnableMixer = HI_TRUE;
    pstSource->bEnableDecoder = HI_TRUE;
    pstSource->bWorking = HI_FALSE;
    pstSource->bDecoderHadbeenStarted = HI_FALSE;
    pstSource->u32PreDecodePts = HI_INVALID_PTS;
    pstSource->bDataValid = HI_FALSE;
    pstSource->u32DecoderPcmDelay = 0;
    pstSource->u32DecoderStaticDelay = 0;

    s32Ret = SourceGetExtRenderOutBuf(enSourceID, &pROutBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceGetExtRenderOutBuf failed(0x%x)\n", s32Ret);
        goto ERR_BUFFER_INIT;
    }

    s32Ret = RENDER_Buffer_Init(&pstSource->pRBuffer, RENDER_BUFFER_SIZE, pROutBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("RENDER_Buffer_Init failed(0x%x)\n", s32Ret);
        goto ERR_BUFFER_INIT;
    }

    s32Ret = SourceCreatePtsQueue(pstSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceCreatePtsQueue failed(0x%x)\n", s32Ret);
        goto ERR_PTSQUEUE_CREATE;
    }

    g_pstSourceManager->pstSource[pstSource->enSourceID] = pstSource;

    return HI_SUCCESS;

ERR_PTSQUEUE_CREATE:
    s32Ret = RENDER_Buffer_DeInit(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("RENDER_Buffer_DeInit failed(0x%x)\n", s32Ret);
    }

ERR_BUFFER_INIT:
    if (pstSource)
    {
        free(pstSource);
    }

    return HI_FAILURE;
}

HI_S32 SourceDestroyTrack(SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource;

    trace();

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    s32Ret = SourceDestoryPtsQueue(pstSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestoryPtsQueue failed(0x%x)\n", s32Ret);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = RENDER_Buffer_DeInit(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("RENDER_Buffer_DeInit failed(0x%x)\n", s32Ret);
        return HI_ERR_AO_INVALID_PARA;
    }

    free(pstSource);
    g_pstSourceManager->pstSource[enSourceID] = HI_NULL;

    return s32Ret;
}

HI_S32  SourceSendStream(SOURCE_ID_E enSourceID, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource;

    CHANNEL_TRACE();

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    pstSource->u32SendStreamTryCnt++;

    s32Ret = PTSQUEUE_CheckIsFull(pstSource->pPtsQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("PTSQUEUE[%d] is full(0x%x)\n", enSourceID, s32Ret);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    s32Ret = RENDER_Buffer_Send(pstSource->pRBuffer, pstStream->u32Size, pstStream->pu8Data);
    if (RBUFFER_ERR_BUFFER_FULL == s32Ret)
    {
        CHANNEL_PRINTF("RENDER_Buffer_Send Buf Full(0x%x)\n", s32Ret);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

#ifdef RENDER_DEBUG_SUPPORT
    SourceEsFileWrite(enSourceID, pstStream->pu8Data, pstStream->u32Size);

    SourcePtsFileWrite(enSourceID, u32PtsMs, pstStream->u32Size);
#endif

    s32Ret = PTSQUEUE_Put(pstSource->pPtsQueue, u32PtsMs, pstStream->u32Size);
    if (HI_SUCCESS != s32Ret) //unlikely
    {
        HI_ERR_AO("PTSQUEUE_Put failed(0x%x)\n", s32Ret);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    pstSource->u32SendStreamOkCnt++;
    pstSource->bDataValid = HI_TRUE;

    return s32Ret;
}

HI_S32 SourceGetBuffer(SOURCE_ID_E enSourceID, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource;

    trace();

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    pstSource->u32GetBufTryCnt++;

    s32Ret = PTSQUEUE_CheckIsFull(pstSource->pPtsQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("PTSQUEUE[%d] is full(0x%x)\n", enSourceID, s32Ret);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    s32Ret = RENDER_Buffer_Get(pstSource->pRBuffer, u32RequestSize, &pstStream->pu8Data);
    if (RBUFFER_ERR_BUFFER_FULL == s32Ret)
    {
        s32Ret = HI_ERR_AO_OUT_BUF_FULL;
    }

    pstStream->u32Size = u32RequestSize;
    pstSource->u32GetBufOkCnt++;

    HI_INFO_AO("RENDER_Buffer_Get %d return(0x%x)\n", pstStream->u32Size, s32Ret);

    return s32Ret;
}

HI_S32  SourcePutBuffer(SOURCE_ID_E enSourceID, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource;

    trace();

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    pstSource->u32PutBufTryCnt++;

    s32Ret = PTSQUEUE_CheckIsFull(pstSource->pPtsQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("PTSQUEUE[%d] is full(0x%x)\n", enSourceID, s32Ret);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    s32Ret = RENDER_Buffer_Put(pstSource->pRBuffer, pstStream->u32Size, pstStream->pu8Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("RENDER_Buffer_Put failed(0x%x)\n", s32Ret);
        return s32Ret;
    }
    else
    {
        HI_INFO_AO("RENDER_Buffer_Put %d success\n", pstStream->u32Size);
    }

#ifdef RENDER_DEBUG_SUPPORT
    SourceEsFileWrite(enSourceID, pstStream->pu8Data, pstStream->u32Size);

    SourcePtsFileWrite(enSourceID, u32PtsMs, pstStream->u32Size);
#endif

    s32Ret = PTSQUEUE_Put(pstSource->pPtsQueue, u32PtsMs, pstStream->u32Size);
    if (HI_SUCCESS != s32Ret) //unlikely
    {
        HI_INFO_AO("PTSQUEUE_Put failed(0x%x)\n", s32Ret);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    pstSource->u32PutBufOkCnt++;
    pstSource->bDataValid = HI_TRUE;

    return s32Ret;
}

HI_S32  SourceStartTrack(SOURCE_ID_E enSourceID)
{
    SOURCE_S* pstSource;

    HI_WARN_AO("Start track %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->enState = SOURCE_STATE_RUNNING;

    return HI_SUCCESS;
}

HI_S32  SourceStopTrack(SOURCE_ID_E enSourceID)
{
    SOURCE_S* pstSource;

    HI_WARN_AO("Stop track %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->enState = SOURCE_STATE_STOP;

    pstSource->u32StreamConsumedBytes = 0;
    pstSource->u32DecodeLeftBytes = 0;
    pstSource->u32CurStreamPts = HI_INVALID_PTS;
    pstSource->bMixing = HI_TRUE;
    pstSource->bDecoding = HI_TRUE;
    pstSource->bEnableMixer = HI_TRUE;
    pstSource->bEnableDecoder = HI_TRUE;
    pstSource->bEosFlag = HI_FALSE;
    pstSource->bEosState = HI_FALSE;
    pstSource->bWorking = HI_FALSE;

    pstSource->u32SinkPts = HI_INVALID_PTS;
    pstSource->bSinkStarted = HI_FALSE;
    pstSource->bDecoderHadbeenStarted = HI_FALSE;
    pstSource->u32PreDecodePts = HI_INVALID_PTS;
    pstSource->bDataValid = HI_FALSE;
    pstSource->u32DecoderPcmDelay = 0;
    pstSource->u32GetBufTryCnt = 0;
    pstSource->u32GetBufOkCnt = 0;
    pstSource->u32PutBufTryCnt = 0;
    pstSource->u32PutBufOkCnt = 0;
    pstSource->u32SendStreamTryCnt = 0;
    pstSource->u32SendStreamOkCnt = 0;
    pstSource->u32SendTrackDataTryCnt = 0;
    pstSource->u32SendTrackDataOkCnt = 0;
    pstSource->u32DecoderStaticDelay = 0;

    RENDER_Buffer_Reset(pstSource->pRBuffer);
    PTSQUEUE_Reset(pstSource->pPtsQueue);

    return HI_SUCCESS;
}

HI_S32  SourcePauseTrack(SOURCE_ID_E enSourceID)
{
    SOURCE_S* pstSource;

    HI_WARN_AO("Pause track %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->enState = SOURCE_STATE_PAUSE;

    return HI_SUCCESS;
}

HI_S32 SourceFlushTrack(SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource;

    HI_INFO_AO("Flush track %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    s32Ret = RENDER_Buffer_Reset(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("RENDER_Buffer_Reset failed(0x%x)\n", s32Ret);
    }

    if ((SOURCE_ID_MAIN == enSourceID) || (SOURCE_ID_ASSOC == enSourceID))
    {
        s32Ret |= PTSQUEUE_Reset(pstSource->pPtsQueue);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("PTSQUEUE_Reset failed(0x%x)\n", s32Ret);
            return s32Ret;
        }
    }

#ifdef RENDER_DEBUG_SUPPORT
    SourceEsFileClose(enSourceID);
#endif

    pstSource->bDecoderHadbeenStarted = HI_FALSE;
    pstSource->bDataValid = HI_FALSE;
    pstSource->u32DecodeLeftBytes = 0;
    pstSource->bActivate = HI_FALSE;

    return s32Ret;
}

HI_S32 SourceSetTargetPts(SOURCE_ID_E enSourceID, HI_U32 u32TargetPts)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d TargetPts:%dms\n", enSourceID, u32TargetPts);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    if (!((HI_FALSE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bEnableMixer)))   //syncmode pause
    {
        return HI_FAILURE;
    }

    pstSource->bSeekFrame = HI_TRUE;
    pstSource->enPkGSeekType = PKG_SEEK_MODE_INTER;
    pstSource->u32TargetPts = u32TargetPts;

    return HI_SUCCESS;
}

HI_S32 SourceDropFrame(SOURCE_ID_E enSourceID, HI_U32 u32FrameCnt)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d DropFrame:%d\n", enSourceID, u32FrameCnt);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    if (!((HI_FALSE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bEnableMixer)))   //syncmode pause
    {
        return HI_FAILURE;
    }

    pstSource->bDropFrame = HI_TRUE;
    pstSource->u32DropFrameCnt = u32FrameCnt;

    return HI_SUCCESS;
}

HI_S32 SourceSetSyncMode(SOURCE_ID_E enSourceID, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    SOURCE_S* pstSource;
    HI_BOOL bValue;

    SYNC_PRINTF("Set source:%d SyncMode:%d\n", enSourceID, enSyncMode);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    bValue = (HI_MPI_AO_TRACK_SYNCMODE_STARTOUTPUT == enSyncMode) ? HI_TRUE : HI_FALSE;

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->bEnableDecoder = bValue;
    pstSource->bEnableMixer   = bValue;

    if (HI_MPI_AO_TRACK_SYNCMODE_STARTOUTPUT == enSyncMode)
    {   //force exit presync mode
        pstSource->bDropFrame = HI_FALSE;
        pstSource->bSeekFrame = HI_FALSE;
        pstSource->enPkGSeekType = PKG_SEEK_MODE_NONE;
    }

    return HI_SUCCESS;
}

HI_S32 SourceSetEosFlag(SOURCE_ID_E enSourceID, HI_BOOL bEosFlag)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d EosFlag:%d\n", enSourceID, bEosFlag);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->bEosFlag = bEosFlag;

    return HI_SUCCESS;
}

HI_S32 SourceGetDelayMs(SOURCE_ID_E enSourceID, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_S32 s32OutBufSize = 0;
    SOURCE_S* pstSource;

    HI_INFO_AO("SourceGetDelayMs source %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    s32Ret = RENDER_Buffer_GetDataSize(pstSource->pRBuffer, &s32OutBufSize);
    if (HI_SUCCESS != s32Ret)
    {
        *pu32DelayMs = 0;
        HI_ERR_AO("RENDER_Buffer_GetDataSize failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (SOURCE_ID_SYSTEM == enSourceID)
    {
        pstSource->bActivate = HI_TRUE;
    }

    HI_WARN_AO("Source %d RenderBufSize:%d DecodeLeftBytes %d\n", enSourceID, s32OutBufSize, pstSource->u32DecodeLeftBytes);

    s32OutBufSize += pstSource->u32DecodeLeftBytes; //Notes: add decoder leftbuf

    *pu32DelayMs = (s32OutBufSize * 1000) / (RENDER_OUT_FRAME_SAMPLERATE * RENDER_OUT_FRAME_BYTES);

    return HI_SUCCESS;
}

HI_S32 SourceGetEosState(SOURCE_ID_E enSourceID, HI_BOOL* bEosFlag)
{
    SOURCE_S* pstSource;

    HI_INFO_AO("SourceGetEosState source %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    *bEosFlag = pstSource->bEosState;

    return HI_SUCCESS;
}

HI_S32 SourceGetBufferStatus(SOURCE_ID_E enSourceID, HI_MPI_AO_RENDER_BUFSTATUS_S* pstBufStatus)
{
    SOURCE_S* pstSource;
    HI_U32 u32InBufUsed;
    HI_U32 u32InBufSize;
    HI_S32 s32Ret;

    HI_INFO_AO("SourceGetBufferStatus source %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    s32Ret = RENDER_Buffer_Enquire(pstSource->pRBuffer, &u32InBufUsed, &u32InBufSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("RENDER_Buffer_Enquire failed(0x%x)\n", s32Ret);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstBufStatus->u32BufferSize = u32InBufSize;
    pstBufStatus->u32BufferUsed = u32InBufUsed;
    pstBufStatus->u32BufferAvailable = u32InBufSize - u32InBufUsed;
    pstBufStatus->u32TotDecodeFrame = 0;        //reserved
    pstBufStatus->u32SamplesPerFrame = 1024;    //reserved
    pstBufStatus->bEndOfFrame = pstSource->bEosState;   //reserved

    return s32Ret;
}

HI_BOOL Source_CheckTrack(HI_HANDLE hTrack)
{
    CHANNEL_PRINTF("Track id:0x%x!\n", hTrack);

    if ((hTrack & 0xf000) != (HI_ID_RENDER_TRACK << 12) ||
        (SOURCE_ID_BUTT <= (hTrack & RENDER_TRACK_MASK)))   //lowbit 8: render sub_mod
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_BOOL Source_CheckIsMediaTrack(HI_HANDLE hTrack)
{
    CHANNEL_PRINTF("Track id:0x%x!\n", hTrack);

    return CheckIsMediaTrack(hTrack);
}

HI_BOOL Source_CheckIsMediaTrackAlloced(HI_HANDLE hTrack)
{
    CHANNEL_PRINTF("Track id:0x%x!\n", hTrack);

    return CheckIsMediaTrackIDApplied(hTrack);
}

HI_BOOL Source_CheckIsMediaTrackCreated(HI_HANDLE hTrack)
{
    CHANNEL_PRINTF("Track id:0x%x!\n", hTrack);

    return CheckIsMediaTrackCreated(hTrack);
}

HI_S32 Source_Init(RENDER_MANAGER_S* pstRenderManager)
{
    trace();

    g_pstSourceManager = (SOURCE_MANAGER_S*)malloc(sizeof(SOURCE_MANAGER_S));
    if (HI_NULL == g_pstSourceManager)
    {
        HI_ERR_AO("Source manager malloc failed!\n");
        return HI_FAILURE;
    }

    memset(g_pstSourceManager, 0, sizeof(SOURCE_MANAGER_S));

    pstRenderManager->pstSourceManager = g_pstSourceManager;
    g_pstSourceRenderManager = pstRenderManager;

    return HI_SUCCESS;
}

HI_S32 Source_Deinit(HI_VOID)
{
    trace();

    if (g_pstSourceManager)
    {
        free(g_pstSourceManager);
        g_pstSourceManager = HI_NULL;
    }

    return HI_SUCCESS;
}

HI_S32 Source_ApllyID(const HI_MPI_AO_RENDER_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    enSourceID = GetSourceIDFromTrackAttr(pstTrackAttr);
    if ((SOURCE_ID_MAIN != enSourceID) && (SOURCE_ID_ASSOC != enSourceID))
    {
        HI_ERR_AO("Get invalid sourceID(0x%x) failed or invalid type(0x%x)!\n", enSourceID, pstTrackAttr->enType);
        return HI_FAILURE;
    }

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    s32Ret = SourceAllocID(enSourceID, phTrack);

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_DeApllyID(HI_HANDLE hTrack)
{
    return SourceDeallocID(hTrack);
}

HI_S32 Source_Create(HI_UNF_SND_E enSound, const HI_MPI_AO_RENDER_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    enSourceID = GetSourceIDFromTrackAttr(pstTrackAttr);
    if (SOURCE_ID_BUTT == enSourceID)
    {
        HI_ERR_AO("GetSourceID failed!\n");
        return HI_FAILURE;
    }

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    if (HI_TRUE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is always instantiated\n", enSourceID);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_FAILURE;
    }

    s32Ret = SourceCreate(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceCreate failed(0x%x)\n", s32Ret);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_FAILURE;
    }

    *phTrack = GetTrackIDFromSourceID(enSourceID);

    if (HI_TRUE != CheckIsNeedDuplicate(enSourceID))
    {
        HI_INFO_AO("Source(%d)Do need duplicate source\n", enSourceID);
        goto EXIT;
    }

    s32Ret = SourceCreate(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Duplicate SourceCreate failed(0x%x)\n", s32Ret);
        goto ERR_DUPLICATE;
    }

    (HI_VOID)SourceSetDuplicateStatus(enSourceID, HI_TRUE);

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);
    return s32Ret;

ERR_DUPLICATE:
    s32Ret = SourceDestroyTrack(enSourceID);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ERR_DUPLICATE SourceDestroyTrack failed(0x%x)\n", s32Ret);
    }

EXIT:
    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_CreateWithID(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    enSourceID = GetSourceIDFromTrackID(hTrack);
    if ((SOURCE_ID_MAIN != enSourceID) && (SOURCE_ID_ASSOC != enSourceID))
    {
        HI_ERR_AO("GetSourceID failed(0x%x)!\n", enSourceID);
        return HI_FAILURE;
    }

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    s32Ret = SourceCreate(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceCreate failed(0x%x)\n", s32Ret);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_FAILURE;
    }

    if (HI_TRUE != CheckIsNeedDuplicate(enSourceID))
    {
        HI_INFO_AO("Source(%d)Do need duplicate source\n", enSourceID);
        goto EXIT;
    }

    s32Ret = SourceCreate(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Duplicate SourceCreate failed(0x%x)\n", s32Ret);
        goto ERR_DUPLICATE;
    }

    (HI_VOID)SourceSetDuplicateStatus(enSourceID, HI_TRUE);

    s32Ret = MediaTrackIDMCreate(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("MediaTrackIDMCreate failed(0x%x)\n", s32Ret);
        SourceDestroyTrack(SOURCE_ID_ASSOC);
        goto ERR_DUPLICATE;
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;

ERR_DUPLICATE:
    s32Ret = SourceDestroyTrack(enSourceID);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ERR_DUPLICATE SourceDestroyTrack failed(0x%x)\n", s32Ret);
    }

EXIT:
    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32  Source_DestroyTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

#ifdef RENDER_DEBUG_SUPPORT
    SourceEsFileClose(enSourceID);
    SourcePtsFileClose(enSourceID);
#endif

    if (HI_TRUE == CheckIsSourceDuplicate(enSourceID))
    {
        s32Ret = SourceDestroyTrack(SOURCE_ID_ASSOC);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("SourceDestroy assoc failed(0x%x)\n", s32Ret);
        }
    }

    s32Ret = SourceDestroyTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestroy failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_DestroyTrackWithID(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    if ((HI_TRUE == CheckIsMediaTrack(hTrack)) ||
        (HI_TRUE == CheckIsMediaTrackIDApplied(hTrack)))
    {
        if (HI_FALSE == CheckIsMediaTrackCreated(hTrack))
        {
            //only id applied, do nothing
            SOURCE_IO_UNLOCK(enSourceID);
            SOURCE_INST2_UNLOCK(enSourceID);
            SOURCE_INST_UNLOCK(enSourceID);
            return HI_SUCCESS;
        }

        MediaTrackIDMDestory(hTrack);
    }

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

#ifdef RENDER_DEBUG_SUPPORT
    SourceEsFileClose(enSourceID);
    SourcePtsFileClose(enSourceID);
#endif

    if (HI_TRUE == CheckIsSourceDuplicate(enSourceID))
    {
        s32Ret = SourceDestroyTrack(SOURCE_ID_ASSOC);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("SourceDestroy assoc failed(0x%x)\n", s32Ret);
        }
    }

    s32Ret = SourceDestroyTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestroy failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr)
{
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstAttr->enTrackType = GetTrackTypeFromSourceID(enSourceID);

    SOURCE_INST_UNLOCK(enSourceID);

    return HI_SUCCESS;
}

HI_S32 Source_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_IO_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        SOURCE_IO_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    if (SOURCE_STATE_RUNNING != pstSource->enState)
    {
        pstSource->enState = SOURCE_STATE_RUNNING;
    }

    pstSource->u32SendTrackDataTryCnt++;

    s32Ret = RENDER_Buffer_Send(pstSource->pRBuffer, pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels * 2, (HI_U8*)pstAOFrame->ps32PcmBuffer);
    if (RBUFFER_ERR_BUFFER_FULL == s32Ret)
    {
        s32Ret = HI_ERR_AO_OUT_BUF_FULL;
    }
    else
    {
        pstSource->u32SendTrackDataOkCnt++;
    }

    pstSource->bDataValid = HI_TRUE;

#ifdef RENDER_DEBUG_SUPPORT
    SourceEsFileWrite(enSourceID, (HI_U8*)pstAOFrame->ps32PcmBuffer, pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels * 2);
#endif

    SOURCE_IO_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32  Source_SendStream(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;
    SOURCE_ID_E enDstSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_IO_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_IO_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    enDstSourceID = (HI_MPI_AO_BUF_ID_ES_ASSOC == enBufId) ? SOURCE_ID_ASSOC : enSourceID;

    s32Ret = SourceSendStream(enDstSourceID, pstStream, u32PtsMs);
    if (HI_SUCCESS != s32Ret)
    {
        CHANNEL_PRINTF("SourceSendStream failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_GetBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;
    SOURCE_ID_E enDstSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_IO_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_IO_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    enDstSourceID = (HI_MPI_AO_BUF_ID_ES_ASSOC == enBufId) ? SOURCE_ID_ASSOC : enSourceID;

    s32Ret = SourceGetBuffer(enDstSourceID, u32RequestSize, pstStream);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("SourceGetBuffer failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_PutBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;
    SOURCE_ID_E enDstSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_IO_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_IO_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    enDstSourceID = (HI_MPI_AO_BUF_ID_ES_ASSOC == enBufId) ? SOURCE_ID_ASSOC : enSourceID;

    s32Ret = SourcePutBuffer(enDstSourceID, pstStream, u32PtsMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("SourcePutBuffer failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_StartTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);

    HI_WARN_AO("Source StartTrack %d\n", enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourceStartTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStartTrack failed(0x%x)\n", s32Ret);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceStartTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStartTrack ASSOC failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32  Source_StopTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source StopTrack %d\n", enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

#ifdef RENDER_DEBUG_SUPPORT
    SourceEsFileClose(enSourceID);
    SourcePtsFileClose(enSourceID);
#endif

    s32Ret = SourceStopTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStopTrack failed(0x%x)\n", s32Ret);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceStopTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStopTrack failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32  Source_PauseTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source PauseTrack %d\n", enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourcePauseTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStopTrack failed(0x%x)\n", s32Ret);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourcePauseTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourcePauseTrack failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_FlushTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    HI_WARN_AO("Source FlushTrack %d\n", enSourceID);

    s32Ret = SourceFlushTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceFlushTrack failed(0x%x)\n", s32Ret);
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceFlushTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceFlushTrack Assoc failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_GetSourceID(HI_HANDLE hTrack, SOURCE_ID_E* penSourceID)
{
    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, *penSourceID);

    SOURCE_INST_LOCK(*penSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(*penSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_FALSE == SourceCheckIsInstantiated(*penSourceID))
    {
        SOURCE_INST_UNLOCK(*penSourceID);
        HI_ERR_AO("Source(%d) is not instantiated\n", *penSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    SOURCE_INST_UNLOCK(*penSourceID);

    return HI_SUCCESS;
}

HI_BOOL Source_CheckIsNeedLoadRenderLib(HI_HANDLE hTrack)
{
    SOURCE_ID_E enSourceID = GetSourceIDFromTrackID(hTrack);

    return CheckIsNeedLoadRenderLib(enSourceID);
}

HI_S32 Source_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourceSetTargetPts(enSourceID, u32TargetPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetTargetPts failed(0x%x)\n", s32Ret);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceSetTargetPts(SOURCE_ID_ASSOC, u32TargetPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetTargetPts ASSOC failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourceDropFrame(enSourceID, u32FrameCnt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDropFrame failed(0x%x)\n", s32Ret);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceDropFrame(SOURCE_ID_ASSOC, u32FrameCnt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDropFrame ASSOC failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_TRACK_SYNCMODE(enSyncMode);

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourceSetSyncMode(enSourceID, enSyncMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetSyncMode failed(0x%x)\n", s32Ret);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceSetSyncMode(SOURCE_ID_ASSOC, enSyncMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetSyncMode ASSOC failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source SetEosFlag %d bEosFlag:%d\n", enSourceID, bEosFlag);

    SOURCE_INST_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourceSetEosFlag(enSourceID, bEosFlag);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetEosFlag failed(0x%x)\n", s32Ret);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceSetEosFlag(SOURCE_ID_ASSOC, bEosFlag);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetEosFlag ASSOC failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret;
    HI_U32 u32DelayMs = 0;
    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source GetDelayMs %d\n", enSourceID);

    SOURCE_INST_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourceGetDelayMs(enSourceID, &u32DelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        *pu32DelayMs = 0;
        HI_ERR_AO("SourceGetDelayMs failed(0x%x)\n", s32Ret);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    *pu32DelayMs = u32DelayMs;

    SOURCE_INST_UNLOCK(enSourceID);

    return HI_SUCCESS;
}

HI_S32 Source_GetEosState(HI_HANDLE hTrack, HI_BOOL* bEosState)
{
    HI_S32 s32Ret;

    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);

    if (HI_FALSE == SourceCheckIsSourceManagerInited())
    {
        HI_ERR_AO("SourceManager is not inited\n");
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = SourceGetEosState(enSourceID, bEosState);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceGetEosState failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_GetBufferStatus(HI_HANDLE hTrack, HI_MPI_AO_RENDER_BUFSTATUS_S* pstBufStatus)
{
    HI_S32 s32Ret;

    SOURCE_ID_E enSourceID;

    trace();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);

    s32Ret = SourceGetBufferStatus(enSourceID, pstBufStatus);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceGetBufferStatus failed(0x%x)\n", s32Ret);
    }

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
