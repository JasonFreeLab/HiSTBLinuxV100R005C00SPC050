/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: mpi_render.c
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
#include "hi_mpi_ao.h"

#include "render.h"
#include "render_source.h"
#include "render_engine.h"
#include "render_common.h"
#include "render_buffer.h"
#include "render_proc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

#define RENDERNAME        "DolbyMS12Decoder"
#define RENDERCODECID     (0x20351012)

static HI_U32 g_u32InstantiatedCnt = 0;
static RENDER_MANAGER_S g_stRenderManager;

#define CHECK_FORMAT_AND_RETURN_VALUE(format, capability, psupport) \
    do { \
        if(((FORMAT_MS12_DDP == format) && (0 != (capability & MS12_SUPPORT_FORMAT_DDP))) || \
           ((FORMAT_MS12_AAC == format) && (0 != (capability & MS12_SUPPORT_FORMAT_AAC))) || \
           ((FORMAT_MS12_AC4 == format) && (0 != (capability & FORMAT_MS12_AC4)))) \
        { \
            *psupport = HI_TRUE; \
        } \
        else \
        { \
            *psupport = HI_FALSE; \
        } \
    } while(0)

HI_S32 RENDERGetStreamInfo(HI_HANDLE hTrack, HI_MPI_AO_RENDER_STREAMINFO_S* pstStreaminfo)
{
    CHECK_AO_NULL_PTR(pstStreaminfo);

    pstStreaminfo->u32CodecID = RENDERCODECID;
    pstStreaminfo->enSampleRate = RENDER_OUT_FRAME_SAMPLERATE;

    return HI_SUCCESS;
}

HI_S32 RENDERGetHaSzNameInfo(HI_HANDLE hTrack, HI_MPI_AO_RENDER_SZNAMEINFO_S* pstAdecName)
{
    CHECK_AO_NULL_PTR(pstAdecName);

    strncpy(pstAdecName->szHaCodecName, RENDERNAME, sizeof(pstAdecName->szHaCodecName));

    return HI_SUCCESS;
}

HI_BOOL RENDER_IsRenderFormat(const HA_FORMAT_E enFormat)
{
    return (HI_BOOL)((FORMAT_MS12_DDP == enFormat) || (FORMAT_MS12_AAC == enFormat) || (FORMAT_MS12_AC4 == enFormat));
}

HI_S32 RENDER_FoundSupportDecoder(const HA_FORMAT_E enFormat, HI_U32* pu32DstCodecID)
{
    switch (enFormat)
    {
        case FORMAT_MS12_DDP:
            *pu32DstCodecID = HA_AUDIO_ID_MS12_DDP;
            break;
        case FORMAT_MS12_AAC:
            *pu32DstCodecID = HA_AUDIO_ID_MS12_AAC;
            break;
        case FORMAT_MS12_AC4:
            *pu32DstCodecID = HA_AUDIO_ID_MS12_AC4;
            break;
        default:
            HI_ERR_AO("Invalid format(0x%x)\n", enFormat);
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 RENDER_CheckIsFormatSupport(const HA_FORMAT_E enFormat, HI_BOOL* pbSupport)
{
    HI_S32 s32Ret;
    HI_U32 u32Capability;

    trace();

    if ((FORMAT_MS12_DDP != enFormat) && (FORMAT_MS12_AAC != enFormat) && (FORMAT_MS12_AC4 != enFormat))
    {
        *pbSupport = HI_FALSE;
        return HI_SUCCESS;
    }

    RENDER_LOCK();

    if ((0 == g_u32InstantiatedCnt) ||
        ((0 != g_u32InstantiatedCnt) && (HI_FALSE == g_stRenderManager.pstEngineManger->pstCodec->bLibInited)))
    { //CodecLock is needed
        s32Ret = Engine_GetCapability(&u32Capability);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Engine_GetCapability failed(0x%x)\n", s32Ret);
            *pbSupport = HI_FALSE;
            RENDER_UNLOCK();
            return HI_FAILURE;
        }
    }
    else
    {
        HA_MS12_GET_CAPABILITY_S stCapability;
        stCapability.enCmd = HA_CODEC_MS12_GET_CAPABILITY_CMD;
        stCapability.u32Capability = 0;

        s32Ret = Engine_GetCmd(&stCapability);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Engine_GetCmd failed(0x%x)\n", s32Ret);
            RENDER_UNLOCK();
            return HI_FAILURE;
        }
        u32Capability = stCapability.u32Capability;
    }

    HI_WARN_AO("Render support format:0x%x", u32Capability);
    CHECK_FORMAT_AND_RETURN_VALUE(enFormat, u32Capability, pbSupport);

    RENDER_UNLOCK();
    return HI_SUCCESS;
}

HI_BOOL RENDER_CheckIsRenderType(HI_UNF_SND_TRACK_TYPE_E enType)
{
    if (enType >= HI_UNF_SND_TRACK_TYPE_SYS && enType <= HI_UNF_SND_TRACK_TYPE_TTS)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_BOOL RENDER_CheckTrack(HI_HANDLE hTrack)
{
    return Source_CheckTrack(hTrack);
}

HI_BOOL RENDER_CheckIsMediaTrack(HI_HANDLE hTrack)
{
    return Source_CheckIsMediaTrack(hTrack);
}

HI_BOOL RENDER_CheckIsMediaTrackCreated(HI_HANDLE hTrack)
{
    return Source_CheckIsMediaTrackCreated(hTrack);
}

HI_S32 RENDER_ApplyTrackID(const HI_MPI_AO_RENDER_ATTR_S* pstRenderTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret;

    trace();

    CHECK_AO_NULL_PTR(pstRenderTrackAttr);
    CHECK_AO_NULL_PTR(phTrack);

    RENDER_LOCK();

    s32Ret = Source_ApllyID(pstRenderTrackAttr, phTrack);

    RENDER_UNLOCK();

    return s32Ret;
}

HI_S32 RENDER_DeApplyTrackID(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;

    trace();

    if ((HI_TRUE != Source_CheckIsMediaTrack(hTrack)) ||
        (HI_TRUE != Source_CheckIsMediaTrackAlloced(hTrack)))
    {
        HI_ERR_AO("Track(0x%x) Invalid parameter failed\n", hTrack);
        return HI_ERR_AO_INVALID_PARA;
    }

    RENDER_LOCK();

    s32Ret = Source_DeApllyID(hTrack);

    RENDER_UNLOCK();

    return s32Ret;
}

HI_S32 RENDER_CreateTrack(HI_UNF_SND_E enSound, const HI_MPI_AO_RENDER_ATTR_S* pstRenderTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret;

    trace();

    CHECK_AO_NULL_PTR(pstRenderTrackAttr);
    CHECK_AO_NULL_PTR(phTrack);

    PROC_LOCK();
    RENDER_LOCK();

    HI_WARN_AO("In render track InstantiatedCnt:(0x%x)\n", g_u32InstantiatedCnt);

    if (0 == g_u32InstantiatedCnt)
    {
        Source_Init(&g_stRenderManager);
        Engine_Init(&g_stRenderManager);
        Proc_Init(&g_stRenderManager);

        s32Ret = Engine_Create();
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Engine_Create failed(0x%x)\n", s32Ret);
            goto Err_CreateEngine;
        }
    }

    s32Ret = Source_Create(enSound, pstRenderTrackAttr, phTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Create failed(0x%x)\n", s32Ret);
        goto Err_CreateSource;
    }

    if (HI_TRUE == Source_CheckIsNeedLoadRenderLib(*phTrack))
    {
        s32Ret = Engine_LoadRenderLib();
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Engine_LoadRenderLib failed(0x%x)\n", s32Ret);
            goto Err_LoadLib;
        }
    }

    g_u32InstantiatedCnt++;

    RENDER_UNLOCK();
    PROC_UNLOCK();

    HI_WARN_AO("Out1 render track InstantiatedCnt:(0x%x)\n", g_u32InstantiatedCnt);

    return s32Ret;

Err_LoadLib:
    Source_DestroyTrack(*phTrack);

Err_CreateSource:
    if (0 == g_u32InstantiatedCnt)
    {
        Engine_Destroy();
    }

Err_CreateEngine:
    if (0 == g_u32InstantiatedCnt)
    {
        Proc_DeInit(&g_stRenderManager);
        Source_Deinit();
        Engine_Deinit();
    }

    RENDER_UNLOCK();
    PROC_UNLOCK();

    HI_WARN_AO("Out2 render track InstantiatedCnt:(0x%x)\n", g_u32InstantiatedCnt);

    return s32Ret;
}

HI_S32 RENDER_CreateTrackWithID(HI_HANDLE hTrack) //TO optimize
{
    HI_S32 s32Ret;

    trace();

    PROC_LOCK();
    RENDER_LOCK();

    if (0 == g_u32InstantiatedCnt) //TO optimize
    {
        Source_Init(&g_stRenderManager);
        Engine_Init(&g_stRenderManager);
        Proc_Init(&g_stRenderManager);

        s32Ret = Engine_Create();
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Engine_Create failed(0x%x)\n", s32Ret);
            goto Err_CreateEngine;
        }
    }

    s32Ret = Source_CreateWithID(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_Create failed(0x%x)\n", s32Ret);
        goto Err_CreateSource;
    }

    if (HI_TRUE == Source_CheckIsNeedLoadRenderLib(hTrack))
    {
        s32Ret = Engine_LoadRenderLib();
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Engine_LoadRenderLib failed(0x%x)\n", s32Ret);
            goto Err_LoadLib;
        }
    }

    g_u32InstantiatedCnt++;

    RENDER_UNLOCK();
    PROC_UNLOCK();

    return s32Ret;

Err_LoadLib:
    Source_DestroyTrack(hTrack);

Err_CreateSource:
    if (0 == g_u32InstantiatedCnt)
    {
        Engine_Destroy();
    }

Err_CreateEngine:
    if (0 == g_u32InstantiatedCnt)
    {
        Proc_DeInit(&g_stRenderManager);
        Source_Deinit();
        Engine_Deinit();
    }

    RENDER_UNLOCK();
    PROC_UNLOCK();

    return s32Ret;
}

HI_S32 RENDER_DestroyTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;

    HI_WARN_AO("In render track InstantiatedCnt:(0x%x)\n", g_u32InstantiatedCnt);
    PROC_LOCK();

    s32Ret = Source_DestroyTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_DestroyTrack failed(0x%x)\n", s32Ret);
        PROC_UNLOCK();
        return s32Ret;
    }

    RENDER_LOCK();

    if (0 == (--g_u32InstantiatedCnt))
    {
        Engine_Destroy();
        Proc_DeInit(&g_stRenderManager);
        Source_Deinit();
        Engine_Deinit();
    }

    RENDER_UNLOCK();
    PROC_UNLOCK();

    HI_WARN_AO("Out render track InstantiatedCnt:(0x%x)\n", g_u32InstantiatedCnt);

    return s32Ret;
}

HI_S32 RENDER_DestroyTrackWithID(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    HI_BOOL bMediaTrackCreatedSource = HI_TRUE;

    HI_WARN_AO("In render track InstantiatedCnt:(0x%x)\n", g_u32InstantiatedCnt);
    PROC_LOCK();

    if ((HI_TRUE != Source_CheckIsMediaTrack(hTrack)) ||
        (HI_TRUE != Source_CheckIsMediaTrackAlloced(hTrack)))
    {
        HI_ERR_AO("Track(0x%x) Invalid parameter failed\n", hTrack);
        PROC_UNLOCK();
        return HI_ERR_AO_INVALID_PARA;
    }

    bMediaTrackCreatedSource = Source_CheckIsMediaTrackCreated(hTrack);

    s32Ret = Source_DestroyTrackWithID(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_DestroyTrack failed(0x%x)\n", s32Ret);
        PROC_UNLOCK();
        return s32Ret;
    }

    if (HI_FALSE == bMediaTrackCreatedSource)
    {
        HI_WARN_AO("MediaTrack is created but not create source\n");
        PROC_UNLOCK();
        return s32Ret;
    }

    RENDER_LOCK();

    if (0 == (--g_u32InstantiatedCnt))
    {
        Engine_Destroy();
        Proc_DeInit(&g_stRenderManager);
        Source_Deinit();
        Engine_Deinit();
    }

    RENDER_UNLOCK();
    PROC_UNLOCK();

    HI_WARN_AO("Out render track InstantiatedCnt:(0x%x)\n", g_u32InstantiatedCnt);

    return s32Ret;
}

HI_S32 RENDER_SetTrackConfig(HI_HANDLE hTrack, HI_VOID* pConfig)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_SetTrackConfig(enSourceID, pConfig);
}

HI_S32 RENDER_GetTrackConfig(HI_HANDLE hTrack, HI_VOID* pConfig)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_GetTrackConfig(enSourceID, pConfig);
}

HI_S32 RENDER_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr)
{
    return Source_GetTrackAttr(hTrack, pstAttr);
}

HI_S32 RENDER_SetTrackAttr(HI_HANDLE hTrack, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    PROC_LOCK();

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        PROC_UNLOCK();
        return s32Ret;
    }

    s32Ret = Engine_SetAttr(enSourceID, pstRenderAttr);

    PROC_UNLOCK();

    return s32Ret;
}

HI_S32 RENDER_SetTrackCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_SetCmd(enSourceID, pstRenderCmd);
}

HI_S32 RENDER_AttachTrack(HI_HANDLE hTrack, HI_HANDLE hSrcTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_AttachExtSinkTrack(enSourceID, hSrcTrack);
}

HI_S32 RENDER_DeAttachTrack(HI_HANDLE hTrack, HI_HANDLE hSrcTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_DeAttachExtSinkTrack(enSourceID, hSrcTrack);
}

HI_S32 RENDER_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    return Source_SendTrackData(hTrack, pstAOFrame);
}

HI_S32 RENDER_SendStream(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    return Source_SendStream(hTrack, enBufId, pstStream, u32PtsMs);
}

HI_S32 RENDER_GetBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream)
{
    return Source_GetBuffer(hTrack, enBufId, u32RequestSize, pstStream);
}

HI_S32 RENDER_PutBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    return Source_PutBuffer(hTrack, enBufId, pstStream, u32PtsMs);;
}

HI_S32 RENDER_StartTrack(HI_HANDLE hTrack)
{
    return Source_StartTrack(hTrack);
}

HI_S32 RENDER_StopTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    trace();

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = Source_StopTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_StopTrack failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_ResetDecoder(enSourceID);
}

HI_S32 RENDER_PauseTrack(HI_HANDLE hTrack)
{
    return Source_PauseTrack(hTrack);
}

HI_S32 RENDER_FlushTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = Source_FlushTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_FlushTrack failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_ResetDecoder(enSourceID);
}

HI_S32  RENDER_GetTrackPts(HI_HANDLE hTrack, HI_U32* pu32Pts)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_GetTrackPts(enSourceID, pu32Pts);
}

HI_S32 RENDER_DropTrackStream(const HI_HANDLE hTrack, HI_U32 u32SeekPts)
{
    HI_BOOL bMediaTrack;
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    bMediaTrack = Source_CheckIsMediaTrack(hTrack);
    if (HI_FALSE == bMediaTrack)
    {
        HI_ERR_AO("Failed only support MediaTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NOTSUPPORT;
    }

    return Engine_DropTrackStream(enSourceID, u32SeekPts);
}

HI_S32 RENDER_SetTargetPts(const HI_HANDLE hTrack, HI_U32 u32TargetPts)
{
    HI_BOOL bMediaTrack;

    bMediaTrack = Source_CheckIsMediaTrack(hTrack);
    if (HI_FALSE == bMediaTrack)
    {
        HI_ERR_AO("Failed only support MediaTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NOTSUPPORT;
    }

    return Source_SetTargetPts(hTrack, u32TargetPts);
}

HI_S32 RENDER_DropFrame(const HI_HANDLE hTrack, HI_U32 u32FrameCnt)
{
    HI_BOOL bMediaTrack;

    bMediaTrack = Source_CheckIsMediaTrack(hTrack);
    if (HI_FALSE == bMediaTrack)
    {
        HI_ERR_AO("Failed only support MediaTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NOTSUPPORT;
    }

    return Source_DropFrame(hTrack, u32FrameCnt);
}

HI_S32 RENDER_SetSyncMode(const HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    HI_BOOL bMediaTrack;

    bMediaTrack = Source_CheckIsMediaTrack(hTrack);
    if (HI_FALSE == bMediaTrack)
    {
        HI_ERR_AO("Failed only support MediaTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NOTSUPPORT;
    }

    return Source_SetSyncMode(hTrack, enSyncMode);
}

HI_S32 RENDER_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    s32Ret = Source_GetSourceID(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_GetSourceID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = Source_SetEosFlag(hTrack, bEosFlag);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Source_SetEosFlag failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    return Engine_SetEosFlag(enSourceID, bEosFlag);
}

HI_S32 RENDER_GetInfo(const HI_HANDLE hTrack, HI_MPI_TRACK_INFO_E enInfoCmd, HI_VOID* pTrackInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    CHECK_AO_NULL_PTR(pTrackInfo);

    switch (enInfoCmd)
    {
        case TRACK_INFO_WORKSTATE:
            break;
        case TRACK_INFO_INBUFSIZE:
            break;
        case TRACK_INFO_OUTBUFNUM:
            break;
        case TRACK_INFO_EOSSTATEFLAG:
            return Source_GetEosState(hTrack, (HI_BOOL*)pTrackInfo);
        case TRACK_INFO_STREAM:
            return RENDERGetStreamInfo(hTrack, (HI_MPI_AO_RENDER_STREAMINFO_S*)pTrackInfo);
        case TRACK_INFO_BUFFERSTATUS:
            return Source_GetBufferStatus(hTrack, (HI_MPI_AO_RENDER_BUFSTATUS_S*)pTrackInfo);
        case TRACK_INFO_HASZNAME:
            return RENDERGetHaSzNameInfo(hTrack, (HI_MPI_AO_RENDER_SZNAMEINFO_S*)pTrackInfo);
        default:
            HI_ERR_AO("Unknown info cmd(0x%x)\n", enInfoCmd);
            return HI_ERR_AO_INVALID_PARA;
    }

    return s32Ret;
}

HI_S32 RENDER_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret;
    HI_U32 u32SinkDelayMs = 0;
    HI_U32 u32SourceDelayMs = 0;

    s32Ret = Engine_GetSinkDelayMs(&u32SinkDelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Engine_GetSinkDelayMs failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = Source_GetDelayMs(hTrack, &u32SourceDelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Engine_GetSinkDelayMs failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    *pu32DelayMs = u32SinkDelayMs + u32SourceDelayMs;

    HI_INFO_AO("DelayMs:%d(Source:%d Sink:%d)\n", *pu32DelayMs, u32SourceDelayMs, u32SinkDelayMs);

    return s32Ret;
}

HI_S32 RENDER_CheckNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent)
{
    CHECK_AO_NULL_PTR(pstNewEvent);

    pstNewEvent->bFrameInfoChange = HI_FALSE;
    pstNewEvent->bStreamCorrupt = HI_FALSE;
    pstNewEvent->bUnSupportFormat = HI_FALSE;
    pstNewEvent->stStreamInfo.u32Channel = 2;
    pstNewEvent->stStreamInfo.enSampleRate = HI_UNF_SAMPLE_RATE_48K;
    pstNewEvent->stStreamInfo.enBitDepth = HI_UNF_BIT_DEPTH_16;
    pstNewEvent->stStreamInfo.enACodecType = 0;

    return HI_ERR_AO_NOTSUPPORT;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
