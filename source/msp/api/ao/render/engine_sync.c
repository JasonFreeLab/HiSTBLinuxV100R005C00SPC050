/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: engine_codec.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "render_common.h"
#include "render_buffer.h"
#include "engine_codec.h"
#include "engine_codec_private.h"
#include "pts_queue.h"

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

ENGINE_CODEC_S* g_pstSyncCodec;

const char* aSeekResult[PTS_SEEK_BUTT] =
{
    "PTS_SEEK_NONE",
    "PTS_SEEK_ALIGN",
    "PTS_SEEK_PACKAGE",
    "PTS_SEEK_FRAME",
};

static HI_VOID EnableDecode(SOURCE_S* pstSource, HI_BOOL bEnable)
{
    trace();

    if ((HI_TRUE == bEnable) && (HI_FALSE == pstSource->bDecoding))
    {
        pstSource->bDecoding = HI_TRUE;
    }
    else if ((HI_FALSE == bEnable) && (HI_TRUE == pstSource->bDecoding) &&
             (HI_FALSE == pstSource->bEnableDecoder))
    {
        pstSource->bDecoding = HI_FALSE;
    }

    HACodec_EnableDecoder(g_pstSyncCodec, pstSource->enSourceID, pstSource->bDecoding);
}

static HI_VOID DropStream(HI_VOID* handle, HI_U32 u32DataSize)
{
    HI_U32 u32ReleaseSize = u32DataSize;
    HI_U32 u32Size;
    HI_S32 s32Ret;
    HI_U8* pTempBuf;

    trace();

    for (; u32ReleaseSize > 0; )
    {
        u32Size = RENDER_Buffer_Acquire(handle, u32ReleaseSize, &pTempBuf);

        SYNC_PRINTF("RENDER_Buffer_Release wantedsize:%d realsize:%d\n", u32ReleaseSize, u32Size);

        s32Ret = RENDER_Buffer_Release(handle, u32Size);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Release buf failed(0x%x)\n", s32Ret);
        }

        u32ReleaseSize -= u32Size;
    }
}

static HI_BOOL CheckIsPreSyncModeValid(SOURCE_S* pstSource)
{
    if (HI_NULL == pstSource || HI_FALSE == pstSource->bSeekFrame)
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_BOOL CheckIsTargetRequirementMeeted(SOURCE_S* pstSource)
{
    if ((HI_INVALID_PTS == pstSource->u32CurStreamPts) || ((pstSource->u32CurStreamPts + RENDER_PTS_MAX_DIFF) < pstSource->u32TargetPts))
    {
        SYNC_PRINTF("Source[%d] TargetPts:%d > CurPts:%d\n", pstSource->enSourceID, pstSource->u32TargetPts, pstSource->u32CurStreamPts);
        return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_BOOL CheckIsAdjustStreamNeeded(SOURCE_S* pstSource)
{
    if (PKG_SEEK_MODE_INTER == pstSource->enPkGSeekType)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

/*static HI_BOOL CheckIsDecoderHadbeenStart(SOURCE_S* pstSource)
{
    return pstSource->bDecoderHadbeenStarted;
}

static HI_VOID ForceAdjustFrameMode(SOURCE_S* pstSource)
{
    pstSource->enPkGSeekType = PKG_SEEK_MODE_INTRA;;
}*/

static HI_VOID ExitDropMode(SOURCE_S* pstSource)
{
    SYNC_PRINTF("Source[%d] TargetPts:%d  CurPts:%d EXIT Drop Mode\n", pstSource->enSourceID, pstSource->u32TargetPts, pstSource->u32CurStreamPts);

    EnableDecode(pstSource, HI_FALSE);

    //when target is 0, PredecodePts has to update here
    pstSource->u32PreDecodePts = pstSource->u32CurStreamPts;
    pstSource->bSeekFrame = HI_FALSE;
    pstSource->enPkGSeekType = PKG_SEEK_MODE_NONE;
    pstSource->bWorking = HI_TRUE;
}

static HI_VOID AdjustStream(SOURCE_S* pstSource)
{
    HI_U32 s32DropBytes;
    HI_U32 u32SeekedPos = 0;
    HI_U32 u32SeekedPts = HI_INVALID_PTS;
    PTS_SEEK_E enPtsSeekState;

    trace();

    enPtsSeekState = PTSQUEUE_Seek(pstSource->pPtsQueue, pstSource->u32TargetPts, &u32SeekedPos, &u32SeekedPts);
    if ((PTS_SEEK_NONE == enPtsSeekState) || (PTS_SEEK_BUTT == enPtsSeekState)) //maybe no pts data
    {
        HI_WARN_AO("PTSQUEUE_Seek source(%d) %d no pts data found\n", pstSource->enSourceID, enPtsSeekState);
        return;
    }

    if (PTS_SEEK_ALIGN == enPtsSeekState)
    {
        pstSource->enPkGSeekType = PKG_SEEK_MODE_NONE;
        pstSource->bSeekFrame = HI_FALSE;
    }
    else if (PTS_SEEK_PACKAGE == enPtsSeekState)
    {
        //pstSource->enPkGSeekType = PKG_SEEK_MODE_INTER;
    }
#if 0 // reserved for seek frame
    else if (PTS_SEEK_FRAME == enPtsSeekState)
    {
        pstSource->enPkGSeekType = PKG_SEEK_MODE_INTRA;
    }
#endif

    SYNC_PRINTF("Seek(package->%s) TargetPts:%d  PtsSeekts:%d PtsSeekPos:%d \n",
                aSeekResult[(HI_U32)enPtsSeekState], pstSource->u32TargetPts, u32SeekedPts, u32SeekedPos);

    s32DropBytes = u32SeekedPos - pstSource->u32StreamConsumedBytes;
    if (0 < s32DropBytes)
    {
        DropStream(pstSource->pRBuffer, s32DropBytes);
        pstSource->u32StreamConsumedBytes = u32SeekedPos;
        //PTSQUEUE_Update(pstSource->pPtsQueue, u32SeekedPts - pstSource->u32CurStreamPts);
    }

    if ((PKG_SEEK_MODE_NONE == pstSource->enPkGSeekType) || (0 < s32DropBytes))
    {
        pstSource->bWorking = HI_TRUE;
    }

    pstSource->u32PreDecodePts = u32SeekedPts;
    pstSource->u32CurStreamPts = u32SeekedPts;
    SYNC_PRINTF("Source:%d Drop InBufSize:%d New Pos:%d Pts:%d\n",
                pstSource->enSourceID, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32CurStreamPts);
}

static HI_VOID AdjustFrame(SOURCE_S* pstSource)
{
    HI_U32 u32DropPts = 0;

    trace();

    if (HI_TRUE != pstSource->bSeekFrame)
    {
        return;
    }

    if (PKG_SEEK_MODE_INTRA == pstSource->enPkGSeekType)
    {
        EnableDecode(pstSource, HI_TRUE);

        u32DropPts = pstSource->u32TargetPts - pstSource->u32CurStreamPts;
        SYNC_PRINTF("Source %d Drop pts:%d\n", pstSource->enSourceID, u32DropPts);
        HACodec_DropPts(g_pstSyncCodec, pstSource->enSourceID, u32DropPts);
        pstSource->bDecoderHadbeenStarted = HI_TRUE;
    }
}

static HI_BOOL SyncCheckIsPreModeEnable(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_S* pstMainSource;
    SOURCE_S* pstAssocSource;

    pstMainSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    pstAssocSource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];

    if (((HI_NULL != pstMainSource) && (HI_TRUE == pstMainSource->bSeekFrame)) ||
        ((HI_NULL != pstAssocSource) && (HI_TRUE == pstAssocSource->bSeekFrame)))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL SyncCheckIsDropFrameEnable(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_S* pstMainSource;
    SOURCE_S* pstAssocSource;

    trace();

    pstMainSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    pstAssocSource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];

    if (((HI_NULL != pstMainSource) && (HI_TRUE == pstMainSource->bDropFrame)) ||
        ((HI_NULL != pstAssocSource) && (HI_TRUE == pstAssocSource->bDropFrame)))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_VOID SyncApplySyncMode(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];

        if (HI_NULL == pstSource)
        {
            continue;
        }

        //SYNC_PRINTF("sourceID:%d EnableMixer:%d Mixing:%d EnableDecoder:%d Decoding:%d\n",
        //            enSourceID, pstSource->bEnableMixer, pstSource->bMixing,
        //            pstSource->bEnableDecoder, pstSource->bDecoding);

        if ((HI_TRUE == pstSource->bEnableMixer) && (HI_FALSE == pstSource->bMixing))
        {
            HACodec_EnableMixer(g_pstSyncCodec, pstSource->enSourceID, HI_TRUE);
            pstSource->bMixing = HI_TRUE;
        }
        else if ((HI_FALSE == pstSource->bEnableMixer) && (HI_TRUE == pstSource->bMixing))
        {
            HACodec_EnableMixer(g_pstSyncCodec, pstSource->enSourceID, HI_FALSE);
            pstSource->bMixing = HI_FALSE;
        }

        if ((HI_TRUE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bDecoding))
        {
            HACodec_EnableDecoder(g_pstSyncCodec, pstSource->enSourceID, HI_TRUE);
            pstSource->bDecoding = HI_TRUE;
        }
        else if ((HI_FALSE == pstSource->bEnableDecoder) && (HI_TRUE == pstSource->bDecoding))
        {
            HACodec_EnableDecoder(g_pstSyncCodec, pstSource->enSourceID, HI_FALSE);
            pstSource->bDecoding = HI_FALSE;
        }
    }
}

static HI_VOID SyncDropFrame(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];

        if (HI_NULL == pstSource || HI_FALSE == pstSource->bDropFrame)
        {
            continue;
        }

        HACodec_DropFrame(g_pstSyncCodec, pstSource->enSourceID, pstSource->u32DropFrameCnt);

        pstSource->bDropFrame = HI_FALSE;
        pstSource->bDecoderHadbeenStarted = HI_TRUE;
    }
}

static HI_VOID SyncPreModeAdjustStream(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if (HI_FALSE == CheckIsPreSyncModeValid(pstSource))
        {
            continue;
        }

        SYNC_PRINTF("Source[%d] DropTargetPts:%d  CurPts:%d\n", enSourceID, pstSource->u32TargetPts, pstSource->u32CurStreamPts);

        if (HI_TRUE == CheckIsTargetRequirementMeeted(pstSource))
        {
            ExitDropMode(pstSource);
            continue;
        }

        if (HI_TRUE == CheckIsAdjustStreamNeeded(pstSource))
        {
            /*if (HI_FALSE == CheckIsDecoderHadbeenStart(pstSource))
            {
                AdjustStream(pstSource);
            }
            else
            {
                //if decoder started, only used drop frame to seek target pts
                ForceAdjustFrameMode(pstSource);
            }*/
            AdjustStream(pstSource);
        }

        AdjustFrame(pstSource);
    }
}

HI_VOID Sync_SetCodecHandle(ENGINE_CODEC_S* pstCodec)
{
    trace();
    g_pstSyncCodec = pstCodec;
}

HI_BOOL Sync_CheckIsSourceNeedDecode(SOURCE_S* pstSource)
{
    if ((HI_TRUE == pstSource->bSeekFrame) && (PKG_SEEK_MODE_INTER == pstSource->enPkGSeekType))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_VOID Sync_Prepare(SOURCE_MANAGER_S* pstSourceManager)
{
    trace();

    SyncApplySyncMode(pstSourceManager);

    if (HI_TRUE != SyncCheckIsPreModeEnable(pstSourceManager))
    {
        if (HI_TRUE == SyncCheckIsDropFrameEnable(pstSourceManager))
        {
            SyncDropFrame(pstSourceManager);
        }

        return;
    }

    SyncPreModeAdjustStream(pstSourceManager);
}

HI_S32 Sync_DropStream(SOURCE_S* pstSource, HI_U32 u32SeekPts)
{
    HI_S32 s32DropBytes;
    HI_U32 u32SeekedPos = 0;
    HI_U32 u32SeekedPts = 0;
    PTS_SEEK_E enPtsSeekState;

    trace();

    if ((HI_NULL == pstSource) ||
        !((HI_FALSE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bEnableMixer)))   //syncmode pause
    {
        return HI_FAILURE;
    }

    HI_WARN_AO("Source[%d] enState:%d DropTargetPts:%d  CurPts:%d\n", pstSource->enSourceID, pstSource->enState, pstSource->u32TargetPts, pstSource->u32CurStreamPts);

    if ((pstSource->u32CurStreamPts >= u32SeekPts) && (HI_INVALID_PTS != pstSource->u32CurStreamPts))
    {
        HI_INFO_AO("Source[%d] SeekPts:%d  CurPts:%d EXIT DropStream Mode\n", pstSource->enSourceID, u32SeekPts, pstSource->u32CurStreamPts);
        return HI_SUCCESS;
    }

    enPtsSeekState = PTSQUEUE_Drop_Seek(pstSource->pPtsQueue, u32SeekPts, &u32SeekedPos, &u32SeekedPts);
    if (PTS_SEEK_NONE == enPtsSeekState) //maybe no pts data
    {
        HI_INFO_AO("PTSQUEUE_Drop_Seek source(%d) no pts data found\n", pstSource->enSourceID);
        return HI_SUCCESS;
    }

    HI_INFO_AO("PtsSeekState:%d TargetPts:%d PtsSeekPts:%d PtsSeekPos:%d\n", enPtsSeekState, pstSource->u32TargetPts, u32SeekedPts, u32SeekedPos);

    s32DropBytes = u32SeekedPos - pstSource->u32StreamConsumedBytes;
    if (s32DropBytes >= 0)
    {
        DropStream(pstSource->pRBuffer, (HI_U32)s32DropBytes);
        pstSource->u32StreamConsumedBytes += (HI_U32)s32DropBytes;
        pstSource->u32CurStreamPts = u32SeekedPts;
        pstSource->u32PreDecodePts = u32SeekedPts;
        pstSource->bWorking = HI_TRUE;
        SYNC_PRINTF("Source:%d Drop InBufSize:%d New Pos:%d Pts:%d\n", pstSource->enSourceID, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32CurStreamPts);
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
