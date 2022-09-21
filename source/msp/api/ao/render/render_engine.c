/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_engine.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dlfcn.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "render_common.h"
#include "render_buffer.h"
#include "render_proc.h"
#include "engine_sink.h"
#include "engine_codec.h"
#include "engine_sync.h"
#include "engine_codec_private.h"
#include "pts_queue.h"
#include "engine_customer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)
#define line()   HI_INFO_AO("%s line:%d\n", __func__, __LINE__)

#define SOURCE_INPUT_ACQUIRE_LEN       (0xFFFFFFFF)
#define RENDER_THREAD_SLEEP_TIME       (5 * 1000)
#define MAX_PTS_FILE_PATH_LEN          (40)

#define RENDER_CODEC_VOLUME_DB_MIN     (-96)
#define RENDER_CODEC_VOLUME_DB_MAX     (0)
#define RENDER_CODEC_MUTE_FADE_MS      (10)

static RENDER_MANAGER_S* g_pstEngineRenderManager = HI_NULL;
static ENGINE_MANAGER_S* g_pstEngineManager = HI_NULL;

static HI_VOID EngineLock(HI_VOID)
{
    SOURCE_ID_E enSourceID;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        SOURCE_INST_LOCK(enSourceID);
    }
}

static HI_VOID EngineUnLock(HI_VOID)
{
    SOURCE_ID_E enSourceID;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        SOURCE_INST_UNLOCK(enSourceID);
    }
}

static HI_VOID CodecLock(HI_VOID)
{
    HACODEC_INST_LOCK();
}

static HI_VOID CodecUnlock(HI_VOID)
{
    HACODEC_INST_UNLOCK();
}

static HI_VOID BufferLock(HI_VOID)
{
    BUF_ACQUIRE_LOCK();
}

static HI_VOID BufferUnlock(HI_VOID)
{
    BUF_ACQUIRE_UNLOCK();
}

#ifdef RENDER_DEBUG_SUPPORT
static HI_VOID SaveOutputPtsFile(SOURCE_S* pstSource)
{
    HI_CHAR cPts[MAX_PTS_FILE_PATH_LEN];
    FILE_DUMP_S* pstFileDump = &g_pstEngineRenderManager->stDumpManager.stPtsDump[pstSource->enSourceID];

    if (HI_FALSE == pstFileDump->bSaved)
    {
        if (HI_NULL != pstFileDump->pDumpFile)
        {
            fclose(pstFileDump->pDumpFile);
            pstFileDump->pDumpFile = HI_NULL;
        }

        return;
    }

    if (HI_NULL == pstFileDump->pDumpFile)
    {
        const HI_CHAR* aprefix = "/mnt/source_out_";
        const HI_CHAR* asuffix = ".pts";
        HI_CHAR cSoureId[2];
        HI_CHAR cFile[MAX_PTS_FILE_PATH_LEN];

        memset(cFile, 0, MAX_PTS_FILE_PATH_LEN);
        memset(cSoureId, 0, 2);

        strncpy(cFile, aprefix, strlen(aprefix));
        cSoureId[0] = pstSource->enSourceID + '0';
        strncat(cFile, cSoureId, strlen(cSoureId));
        strncat(cFile, asuffix, strlen(asuffix));
        HI_INFO_AO("fopen source in pts %s\n", cFile);

        pstFileDump->pDumpFile = fopen(cFile, "w");
        if (HI_NULL == pstFileDump->pDumpFile)
        {
            HI_ERR_AO("fopen pts debug %s failed\n", cFile);
            return;
        }

        HI_ERR_AO("[DEBUG INFO] Dump Out Pts File: SourceID(%d) %s\n", pstSource->enSourceID, cFile);
    }

    snprintf(cPts, MAX_PTS_FILE_PATH_LEN, "%08d, %10d\r", pstSource->u32CurStreamPts, pstSource->u32StreamConsumedBytes);

    HI_INFO_AO("fputs %s\n", cPts);
    fputs(cPts, pstFileDump->pDumpFile);
}
#endif

static HI_BOOL EngineIsSystemTrackAlone(HI_VOID)
{
    HI_BOOL bSystemTrackAlone = HI_TRUE;
    SOURCE_ID_E enSourceCntID;
    SOURCE_S* pstSource;

    trace();

    EngineLock();

    for (enSourceCntID = SOURCE_ID_MAIN; enSourceCntID < SOURCE_ID_BUTT; enSourceCntID++)
    {
        if (SOURCE_ID_SYSTEM == enSourceCntID)
        {
            continue;
        }

        pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceCntID];
        if ((HI_NULL != pstSource) && ((SOURCE_STATE_RUNNING == pstSource->enState) || (SOURCE_STATE_PAUSE == pstSource->enState)))
        {
            if (HI_TRUE == pstSource->bDataValid)
            {
                bSystemTrackAlone = HI_FALSE;
                break;
            }
        }
    }

    EngineUnLock();

    return bSystemTrackAlone;
}

static HI_S32 EngineCreateRenderOutBuf(HI_VOID)
{
    HI_U8* pMem;

    trace();

    pMem = (HI_U8*)malloc(RENDER_BUFFER_SIZE * SOURCE_ID_BUTT);
    if (HI_NULL == pMem)
    {
        HI_ERR_AO("Source render buf malloc failed\n");
        return HI_FAILURE;
    }

    g_pstEngineManager->pROutBuffer[SOURCE_ID_MAIN]   = pMem;
    g_pstEngineManager->pROutBuffer[SOURCE_ID_ASSOC]  = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_ASSOC;
    g_pstEngineManager->pROutBuffer[SOURCE_ID_SYSTEM] = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_SYSTEM;
    g_pstEngineManager->pROutBuffer[SOURCE_ID_TTS]    = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_TTS;

    return HI_SUCCESS;
}

static HI_VOID EngineDestoryRenderOutBuf(HI_VOID)
{
    trace();

    free(g_pstEngineManager->pROutBuffer[SOURCE_ID_MAIN]);
    g_pstEngineManager->pROutBuffer[SOURCE_ID_MAIN] = HI_NULL;
}

static HI_VOID EngineGetOutFrameMs(HA_MS12_STREAM_S* pstMS12DecodeStream, SOURCE_ID_E enSourceID, HI_U32* pu32OutFrameMs)
{
    *pu32OutFrameMs = pstMS12DecodeStream->stOutput.u32OutFrameMs[enSourceID];
}

static HI_VOID EngineFindPts(SOURCE_MANAGER_S* pstSourceManager)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource) || (SOURCE_STATE_RUNNING != pstSource->enState))
        {
            continue;
        }

        s32Ret = PTSQUEUE_Find(pstSource->pPtsQueue, pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes, &pstSource->u32CurStreamPts);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("PTSQUEUE_Find source %d CurPos:%d failed(0x%x)\n", enSourceID, pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes, s32Ret);
        }
        else
        {
            PTS_PRINTF("PTSQUEUE_Find source %d StreamConsumedBytes:%d DecodeLeftBytes:%d CurPos:%d CurPts:%d\n", enSourceID,
                       pstSource->u32StreamConsumedBytes, pstSource->u32DecodeLeftBytes, pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes, pstSource->u32CurStreamPts);
        }
    }
}

static HI_VOID EngineUpdatePts(RENDER_MANAGER_S* pstRenderManager, HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_U32 u32OutFrameMs;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;
    HI_U32 u32UpdatePts;
    HA_CODEC_ID_E enCodecId = pstRenderManager->pstEngineManger->pstCodec->enCodecID;
    SOURCE_MANAGER_S* pstSourceManager = pstRenderManager->pstSourceManager;

    CHANNEL_TRACE();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource) || (SOURCE_STATE_RUNNING != pstSource->enState))
        {
            continue;
        }

        EngineGetOutFrameMs(pstMS12DecodeStream, enSourceID, &u32OutFrameMs);
        if (0 != u32OutFrameMs)
        {
            PTS_PRINTF("UpdatePts source %d PrePcmDelayMs:%d CurPcmDelayMs:%d\n",
                        enSourceID, pstSource->u32DecoderPcmDelay, pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID]);

            u32UpdatePts = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID] + u32OutFrameMs - pstSource->u32DecoderPcmDelay;

            PTSQUEUE_Update(pstSource->pPtsQueue, u32UpdatePts);

            pstSource->u32CurStreamPts = PTSQUEUE_GetReadPts(pstSource->pPtsQueue);

            PTS_PRINTF("UpdatePts source %d NewCurPts:%d (added %d)\n", enSourceID, pstSource->u32CurStreamPts, u32UpdatePts);

            if (SOURCE_ID_MAIN == enSourceID)
            {
                pstSource->bWorking = HI_TRUE;
            }

            if (HA_AUDIO_ID_MS12_AAC == enCodecId)
            {
                pstSource->u32DecoderStaticDelay = MS12_AAC_STATIC_DELAY;
            }
            else if (HA_AUDIO_ID_MS12_DDP == enCodecId)
            {
                pstSource->u32DecoderStaticDelay = MS12_DOLBY_STATIC_DELAY;
            }

#ifdef RENDER_DEBUG_SUPPORT
            SaveOutputPtsFile(pstSource);
#endif
        }
        else
        {
            pstSource->u32DecoderPcmDelay = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID];
            PTS_PRINTF("No Frame out, source %d current decoder pcm delay : %d\n", enSourceID, pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID]);
        }
    }
}

static HI_VOID EngineSetSinkFifoBufAvalid(HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_BOOL bValid = (0 == pstMS12DecodeStream->stOutput.pstOutput->u32PcmOutSamplesPerFrame ? HI_FALSE: HI_TRUE);

    Sink_SetFifoBufValid(bValid);
}

static HI_VOID EngineUpdateStreamInfo(SOURCE_MANAGER_S* pstSourceManager, HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    CHANNEL_TRACE();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource) || (SOURCE_STATE_RUNNING != pstSource->enState))
        {
            continue;
        }

        if ((HI_TRUE == pstSource->bEosFlag) &&
            (HI_FALSE == pstMS12DecodeStream->stOutput.bStreamEnough[enSourceID]))
        {
            pstSource->bEosState = HI_TRUE;
        }
    }
}

static HI_VOID EngineAcquireStreamData(SOURCE_MANAGER_S* pstSourceManager, HA_MS12_STREAM_S* pstMS12DecodeStream, HI_U32* pu32StreamBufBytes)
{
    SOURCE_ID_E enSourceID = 0;
    SOURCE_S* pstSource;
    HI_U8* u8InputBuf[SOURCE_ID_BUTT] = {0};

    memset(pu32StreamBufBytes, 0, sizeof(HI_U32) * SOURCE_ID_BUTT);
    memset(pstMS12DecodeStream->stInput.pstInPack[SOURCE_ID_MAIN], 0, sizeof(HI_HADECODE_INPACKET_S) * SOURCE_ID_BUTT);

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource))
        {
            pstMS12DecodeStream->stInput.enStreamState[enSourceID] = MS12_STREAM_IDLE;
            continue;
        }

        pstMS12DecodeStream->stInput.enStreamState[enSourceID] = (HI_U32)pstSource->enState;
        if ((SOURCE_STATE_RUNNING != pstSource->enState))
        {
            CHANNEL_PRINTF("Source: %d stream is not available\n", enSourceID);
            continue;
        }

        if ((SOURCE_ID_SYSTEM == enSourceID) && (HI_TRUE == pstSource->bActivate))
        {
            PTS_PRINTF("Source: %d status is activate\n", enSourceID);
            pstMS12DecodeStream->stInput.enStreamState[enSourceID] = MS12_STREAM_ACTIVATE;
            pstSource->bActivate = HI_FALSE;
        }

        if (HI_FALSE == Sync_CheckIsSourceNeedDecode(pstSource))
        {
            continue;
        }

        pu32StreamBufBytes[enSourceID] = RENDER_Buffer_Acquire(pstSource->pRBuffer, SOURCE_INPUT_ACQUIRE_LEN, &u8InputBuf[enSourceID]);
        PTS_PRINTF("Source: %d acquire InBufSize:%d\n", enSourceID, pu32StreamBufBytes[enSourceID]);

        Proc_Source(pstSource);

        if (0 < pu32StreamBufBytes[enSourceID])
        {
            pstMS12DecodeStream->stInput.pstInPack[enSourceID]->pu8Data = u8InputBuf[enSourceID];
            pstMS12DecodeStream->stInput.pstInPack[enSourceID]->s32Size = pu32StreamBufBytes[enSourceID];
        }
    }
}

static HI_VOID EngineReleaseStreamData(SOURCE_MANAGER_S* pstSourceManager, HA_MS12_STREAM_S* pstMS12DecodeStream, HI_U32* pu32StreamBufBytes)
{
    HI_U32 u32ConsumedByte;
    HI_U32 u32DecoderLeftedByte;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource) ||
           ((SOURCE_STATE_RUNNING != pstSource->enState) && (SOURCE_STATE_PAUSE != pstSource->enState)))
        {
            CHANNEL_PRINTF("Source: %d stream is not available\n", enSourceID);
            continue;
        }

        u32ConsumedByte = pu32StreamBufBytes[enSourceID] -
                          pstMS12DecodeStream->stInput.pstInPack[enSourceID]->s32Size;

        u32DecoderLeftedByte = pstMS12DecodeStream->stOutput.u32DecodeLeftBytes[enSourceID];
        pstSource->u32StreamConsumedBytes += u32ConsumedByte;
        pstSource->u32DecodeLeftBytes = u32DecoderLeftedByte;

        if (u32ConsumedByte > 0)
        {
            RENDER_Buffer_Release(pstSource->pRBuffer, u32ConsumedByte);
            pstSource->bDecoderHadbeenStarted = HI_TRUE;
        }

        PTS_PRINTF("Source: %d [%d] release InBufSize:%d  pstInPack.size:%d Total_ConsumedByte:%d DecodeLeftBytes:%d, cur ConsumedByte:%d\n",
                   enSourceID, pstSource->enState, pu32StreamBufBytes[enSourceID], pstMS12DecodeStream->stInput.pstInPack[enSourceID]->s32Size,
                   pstSource->u32StreamConsumedBytes, pstSource->u32DecodeLeftBytes, u32ConsumedByte);
    }
}

static HI_VOID EngineSendOutFrame(ENGINE_MANAGER_S* pstEngineManager, HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_S32 s32Ret;

    CHANNEL_TRACE();

    s32Ret = Sink_SendData(pstMS12DecodeStream);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_AO("Sink_SendData failed(0x%x)\n", s32Ret);
    }
}

static HI_BOOL EngineCheckIsStreamEnough(HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_U32 u32StreamCnt;

    CHANNEL_TRACE();

    for (u32StreamCnt = 0; u32StreamCnt < MS12_MAX_STREAM_NUM; u32StreamCnt++)
    {
        if (HI_TRUE == pstMS12DecodeStream->stOutput.bStreamEnough[u32StreamCnt])
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}

static HI_VOID EnginePtsMute(HI_BOOL bMute)
{
    HA_MS12_VOLUME_S stMs12Volume;

    HI_WARN_AO("EnginePtsMute bMute = %d\n", bMute);

    stMs12Volume.enCmd = HA_CODEC_MS12_SET_MIXER1_VOLUME_CMD;
    stMs12Volume.enVolumeCurve = MS12_VOLCURVE_LINEAR;
    stMs12Volume.s32VolumedB = (HI_TRUE == bMute) ? RENDER_CODEC_VOLUME_DB_MIN : RENDER_CODEC_VOLUME_DB_MAX;
    stMs12Volume.u32FadeMs = RENDER_CODEC_MUTE_FADE_MS;

    HACodec_CtlCommand(g_pstEngineManager->pstCodec, SOURCE_ID_MAIN, (HI_VOID*)&stMs12Volume);
}

static HI_VOID EngineProcessPtsMute(ENGINE_MANAGER_S* pstEngineManager)
{
    PTSMUTEQUEUE_POLICY enPtsMutePolicy;
    SOURCE_S* pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[SOURCE_ID_MAIN];

    if (HI_NULL == pstSource)
    {
        return;
    }

    enPtsMutePolicy = PTSMUTEQUEUE_Find(pstEngineManager->pPtsMuteQueue, pstSource->u32CurStreamPts);
    switch(enPtsMutePolicy)
    {
        case PTSMUTE_MUTE_NONE:
            break;
        case PTSMUTE_MUTE_START:
            EnginePtsMute(HI_TRUE);
            break;
        case PTSMUTE_MUTE_STOP:
            EnginePtsMute(HI_FALSE);
            break;
        default:
            break;
    }
}

static HI_VOID* EngineDecThread(HI_VOID* arg)
{
    HI_S32 s32Ret;
    HA_MS12_DECODE_STREAM_S stMS12DecodeStream;
    HI_U32 aInStreamSize[SOURCE_ID_BUTT] = {0};

    trace();

    while(HI_FALSE == HACodec_CheckIsRenderLibLoaded(g_pstEngineManager->pstCodec))
    {
        usleep(RENDER_THREAD_SLEEP_TIME);
        if (HI_TRUE == g_pstEngineManager->bThreadExit)
        {
            return (HI_VOID*)0;
        }
    }

    s32Ret = HACodec_InitDecodeInfo(g_pstEngineManager->pstCodec, &stMS12DecodeStream);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HADecInitDecodeInfo failed(0x%x)\n", s32Ret);
        return (HI_VOID*)0;
    }

    stMS12DecodeStream.enCmd = HA_CODEC_MS12_DECODE_FRAME_CMD;

    while (HI_TRUE != g_pstEngineManager->bThreadExit)
    {
        BufferLock();

        EngineLock();

        EngineFindPts(g_pstEngineRenderManager->pstSourceManager);

        Sync_Prepare(g_pstEngineRenderManager->pstSourceManager);

        EngineAcquireStreamData(g_pstEngineRenderManager->pstSourceManager, &stMS12DecodeStream.stStream, aInStreamSize);

        EngineProcessPtsMute(g_pstEngineManager);

        EngineUnLock();

        Proc_Engine(g_pstEngineManager, STATISTICS_START);

        CodecLock();

        s32Ret = HACodec_Render(g_pstEngineManager->pstCodec, &stMS12DecodeStream);
        if (HI_SUCCESS != s32Ret)
        {
            CHANNEL_PRINTF("EngineRenderSource not success(0x%x)!\n", s32Ret);
        }
        else
        {
            CHANNEL_PRINTF("EngineRenderSource success pcm sample:%d\n", stMS12DecodeStream.stStream.stOutput.pstOutput->u32PcmOutSamplesPerFrame);
        }

        HACodec_UpdateDataStatus(g_pstEngineManager->pstCodec, stMS12DecodeStream.stStream.stOutput.bStreamEnough);

        CodecUnlock();

        Proc_Engine(g_pstEngineManager, STATISTICS_STOP);

        EngineLock();

        EngineReleaseStreamData(g_pstEngineRenderManager->pstSourceManager, &stMS12DecodeStream.stStream, aInStreamSize);

        EngineUpdatePts(g_pstEngineRenderManager, &stMS12DecodeStream.stStream);

        EngineSetSinkFifoBufAvalid(&stMS12DecodeStream.stStream);

        EngineUnLock();

        BufferUnlock();

        Proc_Sink(g_pstEngineManager, STATISTICS_START);

        EngineSendOutFrame(g_pstEngineManager, &stMS12DecodeStream.stStream);   //output

        Proc_Sink(g_pstEngineManager, STATISTICS_STOP);

        EngineUpdateStreamInfo(g_pstEngineRenderManager->pstSourceManager, &stMS12DecodeStream.stStream);

        if (HI_FALSE == EngineCheckIsStreamEnough(&stMS12DecodeStream.stStream))
        {
            usleep(RENDER_THREAD_SLEEP_TIME);
        }
    }

    return (HI_VOID*)0;
}


static HI_S32 EngineGetPts(SOURCE_MANAGER_S* pstSourceManager, SOURCE_ID_E enSourceID, HI_U32* pu32Pts)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource = pstSourceManager->pstSource[enSourceID];
    static HI_U32 s_pts = 0;

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Source(%d) is not insted\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if ((HI_FALSE == pstSource->bWorking) || (HI_INVALID_PTS == pstSource->u32CurStreamPts))
    {
        PTS_PRINTF("Source(%d) not working state(bworking: %d curpts:%d)\n", enSourceID, pstSource->bWorking, pstSource->u32CurStreamPts);
        return HI_ERR_AO_NOT_INIT;
    }

    //when no data sent,just use PreDecodePts(same as stream pts)
    if (HI_FALSE == pstSource->bSinkStarted)
    {
        *pu32Pts = pstSource->u32PreDecodePts;
        PTS_PRINTF("Source(%d) PreDecode Pts:%d\n", enSourceID, *pu32Pts);
        return HI_SUCCESS;
    }

    s32Ret = Sink_GetSyncDelayMs(pstSource, pu32Pts);
    if (HI_SUCCESS != s32Ret)
    {
        PTS_PRINTF("Source(%d) have no valid pts\n", enSourceID);
        return HI_ERR_AO_NOT_INIT;
    }

    if (*pu32Pts < s_pts) //for pts trace
    {
        HI_WARN_AO("seems error pts %d -> %d\n", s_pts, *pu32Pts);
    }

    s_pts = *pu32Pts;

    return HI_SUCCESS;
}

static HI_S32 EngineGetSinkDelayMs(ENGINE_MANAGER_S* pstEngineManager, HI_U32* pu32DelayMs)
{
    return Sink_GetDelayMs(pu32DelayMs);
}

static HI_VOID EngineAttachExtSinkTrack(ENGINE_MANAGER_S* pstEngineManager, HI_HANDLE hExtSinkTrack)
{
    pstEngineManager->hExtTrack = hExtSinkTrack;
}

static HI_S32 EngineDeAttachExtSinkTrack(ENGINE_MANAGER_S* pstEngineManager, HI_HANDLE hSrcTrack)
{
    HI_S32 s32Ret;

    if (pstEngineManager->hExtTrack != hSrcTrack)
    {
        HI_ERR_AO("Invalid srctrack id(0x%x)\n", hSrcTrack);
        return HI_ERR_AO_INVALID_PARA;
    }

    s32Ret = Sink_DeattchExtTrack();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Sink_DeattchExtTrack failed(0x%x)\n", s32Ret);
    }

    pstEngineManager->hExtTrack = HI_NULL;

    return s32Ret;
}

static HI_S32 EngineSetTrackConfig(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    HI_UNF_AUDIOTRACK_CONFIG_S* pstConfig = pConfig;
    HI_VOID* pCmd = HI_NULL;
    HA_MS12_VOLUME_S stVolume;
    HA_MS12_SET_EOSFLAG_S stEosFlag;
    HA_MS12_SET_MEDIAVOLATTENUATE_S stAttenuate;

    HI_WARN_AO("Cmd:0x%x\n",pstConfig->u32ConfigType);

    switch (pstConfig->u32ConfigType)
    {
        case CONFIG_VOLUME:
        {
            VOLUME_CONFIG_S* pstVolume = pstConfig->pConfigData;
            stVolume.enCmd = HA_CODEC_MS12_SET_VOLUME_CMD;
            stVolume.enVolumeCurve = pstVolume->enVolumeCurve;
            stVolume.s32VolumedB = pstVolume->s32VolumedB;
            stVolume.u32FadeMs = pstVolume->u32FadeMs;
            pCmd = (HI_VOID *)&stVolume;
            break;
        }
        case CONFIG_SETEOSFLAG:
        {
            SOURCE_S* pstSource;
            SETEOSFLAG_CONFIG_S* pstEosFlag = pstConfig->pConfigData;

            SOURCE_INST_LOCK(enSourceID);

            pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID];
            if (HI_NULL == pstSource)
            {
                HI_ERR_AO("Source(%d) is not insted\n", enSourceID);
                SOURCE_INST_UNLOCK(enSourceID);
                return HI_ERR_AO_INVALID_PARA;
            }

            stEosFlag.enCmd = HA_CODEC_MS12_SET_EOSFLAG_CMD;
            stEosFlag.bEosFlag = pstEosFlag->bEosFlag;
            pCmd = (HI_VOID *)&stEosFlag;
            pstSource->bDataValid = HI_FALSE;

            SOURCE_INST_UNLOCK(enSourceID);
            break;
        }
        case CONFIG_SETMEDIAVOLUMEATTENUATION:
        {
            SETMEDIAVOLUMEATTENUATION_CONFIG_S* pstAttenuate = pstConfig->pConfigData;
            stAttenuate.enCmd = HA_CODEC_MS12_SET_MEDIAVOLATTENUATE_CMD;
            stAttenuate.bEnable = pstAttenuate->bAttenuate;
            pCmd = (HI_VOID *)&stAttenuate;
            break;
        }
        case CONFIG_SETCONTINUOUSOUTPUTSTATUS:
        {
            SETCONTINUOUSOUTPUT_CONFIG_S* pstContinuousOutput = pstConfig->pConfigData;
            return Sink_EnableContinuousOutput(pstContinuousOutput->bEnable);
        }
        default:
        {
            HI_ERR_AO("Unknown cmd:0x%x \n",pstConfig->u32ConfigType);
            return HI_ERR_AO_INVALID_PARA;
        }
    }

    return HACodec_CtlCommand(pstEngineManager->pstCodec, enSourceID, pCmd);
}

static HI_S32 EngineGetTrackConfig(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    HI_UNF_AUDIOTRACK_CONFIG_S* pstConfig = pConfig;

    switch (pstConfig->u32ConfigType)
    {
        case CONFIG_GETSYSTEMTRACKALONEFLAG:
        {
            GETSYSTRACKALONE_CONFIG_S* pstIsConfig = pstConfig->pConfigData;
            pstIsConfig->bAlone = EngineIsSystemTrackAlone();
            return HI_SUCCESS;
        }
        case CONFIG_VOLUME:
        {
            return HI_ERR_AO_NOTSUPPORT;
        }
        default:
        {
            HI_ERR_AO("Unknown cmd:0x%x \n",pstConfig->u32ConfigType);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 EngineResetDecoder(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID)
{
    HI_S32 s32Cmd = HA_CODEC_MS12_RESET_CMD;

    if (enSourceID >= SOURCE_ID_BUTT)
    {
        return HI_FAILURE;
    }

    return HACodec_CtlCommand(pstEngineManager->pstCodec, enSourceID, (HI_VOID*)&s32Cmd);
}

static HI_S32 EngineSetEosFlag(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID, HI_BOOL bEosFlag)
{
    HA_MS12_SET_EOSFLAG_S stEosFlag;

    stEosFlag.enCmd = HA_CODEC_MS12_SET_EOSFLAG_CMD;
    stEosFlag.bEosFlag = bEosFlag;

    return HACodec_CtlCommand(pstEngineManager->pstCodec, enSourceID, (HI_VOID*)&stEosFlag);
}

HI_S32 Engine_Init(RENDER_MANAGER_S* pstRenderManager)
{
    HI_S32 s32Ret;

    trace();

    g_pstEngineManager = (ENGINE_MANAGER_S*)malloc(sizeof(ENGINE_MANAGER_S));
    if (HI_NULL == g_pstEngineManager)
    {
        HI_ERR_AO("Source manager malloc failed!\n");
        return HI_FAILURE;
    }

    memset(g_pstEngineManager, 0, sizeof(ENGINE_MANAGER_S));

    s32Ret = HACodec_Init(&g_pstEngineManager->pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodec_Init failed(0x%x)\n", s32Ret);
        goto ERR_INITHACODEC;
    }

    s32Ret = PTSMUTEQUEUE_Create(&g_pstEngineManager->pPtsMuteQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("PTSMUTE_Create failed(0x%x)\n", s32Ret);
        goto ERR_CREATE_PTSMUTE;
    }

    pstRenderManager->pstEngineManger = g_pstEngineManager;
    g_pstEngineRenderManager = pstRenderManager;

    return HI_SUCCESS;

ERR_CREATE_PTSMUTE:
    HACodec_DeInit(g_pstEngineManager->pstCodec);

ERR_INITHACODEC:
    free(g_pstEngineManager);
    g_pstEngineManager = HI_NULL;

    return HI_FAILURE;
}

HI_S32 Engine_Deinit(HI_VOID)
{
    trace();

    if (g_pstEngineManager)
    {
        PTSMUTEQUEUE_Destroy(g_pstEngineManager->pPtsMuteQueue);
        HACodec_DeInit(g_pstEngineManager->pstCodec);

        free(g_pstEngineManager);
        g_pstEngineManager = HI_NULL;
    }

    g_pstEngineRenderManager->pstEngineManger = HI_NULL;

    return HI_SUCCESS;
}

HI_S32 Engine_Create(HI_VOID)
{
    HI_S32 s32Ret;

    trace();

    s32Ret = EngineCreateRenderOutBuf();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("EngineCreateRenderOutBuf failed(0x%x)\n", s32Ret);
        goto ERR_RENDER_OUTBUF_CREATE;
    }

    s32Ret = Sink_Init(g_pstEngineRenderManager);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Sink_Create failed(0x%x)\n", s32Ret);
        goto ERR_INITHADEC;
    }

    g_pstEngineManager->bThreadExit = HI_FALSE;

    s32Ret = pthread_create(&g_pstEngineManager->Thread, HI_NULL, EngineDecThread, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("pthread_create failied\n");
        goto ERR_SINK_CREATE;
    }

    return s32Ret;

ERR_SINK_CREATE:
    s32Ret = Sink_Deinit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Sink_Destroy failed(0x%x)\n", s32Ret);
    }

ERR_INITHADEC:
    EngineDestoryRenderOutBuf();

ERR_RENDER_OUTBUF_CREATE:
    return s32Ret;
}

HI_VOID Engine_Destroy(HI_VOID)
{
    HI_S32 s32Ret;

    trace();

    g_pstEngineManager->bThreadExit = HI_TRUE;
    pthread_join(g_pstEngineManager->Thread, HI_NULL);

    s32Ret = Sink_Deinit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Sink_Destroy failed(0x%x)\n", s32Ret);
    }

    EngineDestoryRenderOutBuf();

    HACodec_DeInitDecodeInfo(g_pstEngineManager->pstCodec);
    HACodec_UnLoadRenderLib(g_pstEngineManager->pstCodec);
}

HI_S32 Engine_LoadRenderLib(HI_VOID)
{
    HI_S32 s32Ret;

    trace();

    CodecLock();

    s32Ret = HACodec_LoadRenderLib_Default(g_pstEngineManager->pstCodec);

    Sync_SetCodecHandle(g_pstEngineManager->pstCodec);

    CodecUnlock();

    return s32Ret;
}

HI_S32 Engine_DropTrackStream(const SOURCE_ID_E enSourceID, HI_U32 u32SeekPts)
{
    HI_S32 s32Ret;

    trace();

    SOURCE_INST_LOCK(enSourceID);

    s32Ret = Sync_DropStream(g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID], u32SeekPts);

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Engine_SetAttr(const SOURCE_ID_E enSourceID, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret;

    trace();

    SOURCE_INST_LOCK(enSourceID);

    CodecLock();

    s32Ret = HACodec_LoadRenderLib(g_pstEngineManager->pstCodec, pstRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodecLoadRenderLib failed(0x%x)\n", s32Ret);
    }

    Sync_SetCodecHandle(g_pstEngineManager->pstCodec);

    CodecUnlock();

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Engine_SetCmd(const SOURCE_ID_E enSourceID, HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret;
    HI_U32 u32Cmd;

    trace();

    CHECK_AO_NULL_PTR(pstRenderCmd);

    u32Cmd = *((HI_U32*)pstRenderCmd);
    if (HA_CODEC_MS12_SET_PTS_MUTE_CMD == u32Cmd)
    {
        HA_MS12_SET_PTS_MUTE_S* pstPtsMute;
        HI_WARN_AO("Receive SET_PTS_MUTE_CMD\n");

        SOURCE_INST_LOCK(enSourceID);

        pstPtsMute = (HA_MS12_SET_PTS_MUTE_S*)pstRenderCmd;
        s32Ret = PTSMUTEQUEUE_Add(g_pstEngineManager->pPtsMuteQueue, pstPtsMute->u32StartPts, pstPtsMute->u32StopPts);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("PTSMUTEQUEUE_Add failed(0x%x)\n", s32Ret);
        }

        SOURCE_INST_UNLOCK(enSourceID);

        return s32Ret;
    }

    SOURCE_INST_LOCK(enSourceID);

    s32Ret = HACodec_CtlCommand(g_pstEngineManager->pstCodec, enSourceID, pstRenderCmd);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodec_CtlCommand failed(0x%x)\n", s32Ret);
        if (HA_ErrorInvalidParameter == s32Ret)
        {
            s32Ret = HI_ERR_AO_INVALID_PARA;
        }
    }

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Engine_GetCmd(HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret;

    trace();

    s32Ret = HACodec_GetCmd(g_pstEngineManager->pstCodec, pstRenderCmd);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodec_GetCmd failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Engine_AttachExtSinkTrack(const SOURCE_ID_E enSourceID, HI_HANDLE hExtSinkTrack)
{
    trace();

    SOURCE_INST_LOCK(enSourceID);

    EngineAttachExtSinkTrack(g_pstEngineManager, hExtSinkTrack);

    SOURCE_INST_UNLOCK(enSourceID);

    return HI_SUCCESS;
}

HI_S32 Engine_DeAttachExtSinkTrack(const SOURCE_ID_E enSourceID, HI_HANDLE hSrcTrack)
{
    HI_S32 s32Ret;

    trace();

    SOURCE_INST_LOCK(enSourceID);

    s32Ret = EngineDeAttachExtSinkTrack(g_pstEngineManager, hSrcTrack);

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Engine_GetTrackPts(const SOURCE_ID_E enSourceID, HI_U32* pu32Pts)
{
    HI_S32 s32Ret;

    trace();

    SOURCE_INST_LOCK(enSourceID);

    s32Ret = EngineGetPts(g_pstEngineRenderManager->pstSourceManager, enSourceID, pu32Pts);

    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Engine_GetSinkDelayMs(HI_U32* pu32DelayMs)
{
    return EngineGetSinkDelayMs(g_pstEngineManager, pu32DelayMs);
}

HI_S32 Engine_SetTrackConfig(const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    trace();

    return EngineSetTrackConfig(g_pstEngineManager, enSourceID, pConfig);
}

HI_S32 Engine_GetTrackConfig(const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    trace();

    return EngineGetTrackConfig(g_pstEngineManager, enSourceID, pConfig);
}

HI_S32 Engine_ResetDecoder(const SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;

    trace();

    if (SOURCE_ID_MAIN == enSourceID)
    {
        PTSMUTEQUEUE_Reset(g_pstEngineManager->pPtsMuteQueue);
    }

    BufferLock();

    s32Ret = EngineResetDecoder(g_pstEngineManager, enSourceID);

     BufferUnlock();

    return s32Ret;
}

HI_S32 Engine_SetEosFlag(const SOURCE_ID_E enSourceID, HI_BOOL bEosFlag)
{
    trace();

    return EngineSetEosFlag(g_pstEngineManager, enSourceID, bEosFlag);
}

HI_S32 Engine_GetCapability(HI_U32* pu32Capability)
{
    HI_S32 s32Ret;

    trace();

    s32Ret = HACodec_GetRenderLibCapability(pu32Capability);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("HACodec_GetRenderLibCapability failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
