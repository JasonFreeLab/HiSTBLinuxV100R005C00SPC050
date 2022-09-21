/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tsplay.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "hi_unf_common.h"
#include "hi_unf_ecs.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"

#define ROUTE_MS12_METHOD_B  (0)
#define PLAY_DMX_ID  0
#define TTS_INDEX      0
#define UIAUDIO_INDEX  1

static FILE             *g_pTsFile = HI_NULL;
static FILE             *g_pcmFile[UIAUDIO_INDEX + 1];

static HI_HANDLE        g_hSysTrack = HI_NULL;
static HI_HANDLE        g_hTtsTrack = HI_NULL;

static pthread_t        g_TsThd;
static HI_BOOL          g_bStopTsThread = HI_FALSE;

static HI_BOOL          g_bStopFlag[UIAUDIO_INDEX + 1];
static pthread_t        g_hPcmThread[UIAUDIO_INDEX + 1];

static pthread_mutex_t g_TsMutex;
HI_HANDLE              g_TsBuf;
PMT_COMPACT_TBL        *g_pProgTbl = HI_NULL;
static HI_BOOL         g_bUseMS12 = HI_FALSE;;

HI_HANDLE              g_hWin;
HI_HANDLE              g_hTrack;
HI_HANDLE              g_hAvplay;

static HI_S32 HIADP_AVPlay_PlayProg_MS12(HI_HANDLE hAvplay,PMT_COMPACT_TBL *pProgTbl,HI_U32 ProgNum,HI_BOOL bAudPlay)
{
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_U32                  VidPid;
    HI_U32                  AudPid;
    HI_U32                  PcrPid;
    HI_UNF_VCODEC_TYPE_E    enVidType;
    HI_U32                  u32AudType;
    HI_S32                  Ret;

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    Ret = HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HI_UNF_AVPLAY_Stop failed.\n");
        return Ret;
    }

    ProgNum = ProgNum % pProgTbl->prog_num;
    if (pProgTbl->proginfo[ProgNum].VElementNum > 0 )
    {
        VidPid = pProgTbl->proginfo[ProgNum].VElementPid;
        enVidType = pProgTbl->proginfo[ProgNum].VideoType;
    }
    else
    {
        VidPid = INVALID_TSPID;
        enVidType = HI_UNF_VCODEC_TYPE_BUTT;
    }

    if (pProgTbl->proginfo[ProgNum].AElementNum > 0)
    {
        AudPid  = pProgTbl->proginfo[ProgNum].AElementPid;
        u32AudType = pProgTbl->proginfo[ProgNum].AudioType;
    }
    else
    {
        AudPid = INVALID_TSPID;
        u32AudType = 0xffffffff;
    }

    //Method A. AudioFormat being identified, Change FORMAT_AAC to FORMAT_MS12_AAC.
    //Method B. AudioCodec being identified, Change HA_AUDIO_ID_AAC to HA_AUDIO_ID_MS12_AAC.
#ifdef ROUTE_MS12_METHOD_B  //Method B. How to route MS12
    if ((HA_AUDIO_ID_AAC == u32AudType) || (HA_AUDIO_ID_DOLBY_PLUS == u32AudType) || (HA_AUDIO_ID_AC3PASSTHROUGH == u32AudType))
    {
        if (HI_TRUE == g_bUseMS12)
        {
            HI_BOOL bMS12Support;
            if (HA_AUDIO_ID_AAC == u32AudType)
            {
                Ret = HI_UNF_AVPLAY_IsAudioFormatSupport(FORMAT_MS12_AAC, &bMS12Support);
                printf(" func:%s line:%d ret:0x%x bsupport: %d\n", __func__, __LINE__, Ret, bMS12Support);
                if ((HI_SUCCESS == Ret) && (HI_TRUE == bMS12Support))
                {
                    printf("\n\nMethod B to route [MS12 AAC] \n\n");
                    u32AudType = HA_AUDIO_ID_MS12_AAC;
                }
            }
            else
            {
                Ret = HI_UNF_AVPLAY_IsAudioFormatSupport(FORMAT_MS12_DDP, &bMS12Support);
                printf(" func:%s line:%d ret:0x%x bsupport: %d\n", __func__, __LINE__, Ret, bMS12Support);
                if ((HI_SUCCESS == Ret) && (HI_TRUE == bMS12Support))
                {
                    printf("\n\nMethod B to route [MS12 DDP] \n\n");
                    u32AudType = HA_AUDIO_ID_MS12_DDP;
                }
            }
        }
    }
#endif

    PcrPid = pProgTbl->proginfo[ProgNum].PcrPid;
    if (INVALID_TSPID != PcrPid)
    {
        HI_UNF_SYNC_ATTR_S  SyncAttr;

        Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
        if (HI_SUCCESS != Ret)
        {
            sample_common_printf("HI_UNF_AVPLAY_GetAttr Sync failed 0x%x\n", Ret);
            return Ret;
        }

        if (HI_UNF_SYNC_REF_PCR == SyncAttr.enSyncRef)
        {
            Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_PCR_PID, &PcrPid);
            if (HI_SUCCESS != Ret)
            {
                sample_common_printf("HI_UNF_AVPLAY_SetAttr Sync failed 0x%x\n", Ret);
                return Ret;
            }
        }
    }

    if (VidPid != INVALID_TSPID)
    {
        Ret = HIADP_AVPlay_SetVdecAttr(hAvplay,enVidType,HI_UNF_VCODEC_MODE_NORMAL);
        Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID,&VidPid);
        if (Ret != HI_SUCCESS)
        {
            sample_common_printf("call HIADP_AVPlay_SetVdecAttr failed.\n");
            return Ret;
        }

        Ret = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
        if (Ret != HI_SUCCESS)
        {
            sample_common_printf("call HI_UNF_AVPLAY_Start failed.\n");
            return Ret;
        }
    }

    if (HI_TRUE == bAudPlay && AudPid != INVALID_TSPID)
    {
        Ret  = HIADP_AVPlay_SetAdecAttr(hAvplay, u32AudType, HD_DEC_MODE_RAWPCM, 1);
        Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &AudPid);
        if (HI_SUCCESS != Ret)
        {
            sample_common_printf("HIADP_AVPlay_SetAdecAttr failed:%#x\n",Ret);
            return Ret;
        }

        Ret = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
        if (Ret != HI_SUCCESS)
        {
            printf("call HI_UNF_AVPLAY_Start to start audio failed.\n");
        }
    }
    return HI_SUCCESS;
}

HI_VOID TsTthread(HI_VOID *args)
{
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                Readlen;
    HI_S32                Ret;

    while (!g_bStopTsThread)
    {
        pthread_mutex_lock(&g_TsMutex);
        Ret = HI_UNF_DMX_GetTSBuffer(g_TsBuf, 188*50, &StreamBuf, 1000);
        if (Ret != HI_SUCCESS )
        {
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 188*50, g_pTsFile);
        if(Readlen <= 0)
        {
            printf("read ts file end and rewind!\n");
            rewind(g_pTsFile);
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Ret = HI_UNF_DMX_PutTSBuffer(g_TsBuf, Readlen);
        if (Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
        }
        pthread_mutex_unlock(&g_TsMutex);
    }

    Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }

    return;
}

HI_VOID PcmThread(HI_VOID* args)
{
    HI_S32 s32Ret;
    HI_U32 u32Readlen;
    HI_U32 u32WantedSize;
    HI_U32 u32StreamId = (HI_VOID*)args - (HI_VOID*)HI_NULL;
    HI_BOOL bAudBufAvail = HI_FALSE;

    HI_UNF_AO_FRAMEINFO_S stAOFrame;
    HI_VOID* PmcBuf = HI_NULL;
    HI_HANDLE* phTrack;

    if (UIAUDIO_INDEX == u32StreamId)
    {
        phTrack = &g_hSysTrack;
    }
    else if (TTS_INDEX == u32StreamId)
    {
        phTrack = &g_hTtsTrack;
    }
    else
    {
        printf("Error pcm stream id (0x%x)\n", u32StreamId);
        return;
    }

    //for system audio or tts, only support 48K 16bit pcm
    stAOFrame.s32BitPerSample = 16;
    stAOFrame.u32Channels   = 2;
    stAOFrame.bInterleaved  = 1;
    stAOFrame.u32SampleRate = 48000;
    stAOFrame.u32PtsMs = 0xffffffff;
    stAOFrame.ps32BitsBuffer = HI_NULL;
    stAOFrame.u32BitsBytesPerFrame = 0;
    stAOFrame.u32FrameIndex = 0;
    stAOFrame.u32PcmSamplesPerFrame = 1536;

    u32WantedSize = 1536 * 2 * sizeof(HI_S16);
    PmcBuf = (HI_VOID*)malloc(u32WantedSize);
    stAOFrame.ps32PcmBuffer = (HI_S32*)(PmcBuf);

    while (HI_TRUE != g_bStopFlag[u32StreamId])
    {
        if (HI_FALSE == bAudBufAvail)
        {
            u32Readlen = fread(PmcBuf, 1, u32WantedSize,  g_pcmFile[u32StreamId]);
            if (u32Readlen != u32WantedSize)
            {
                rewind(g_pcmFile[u32StreamId]);
            }
        }

        s32Ret = HI_UNF_SND_SendTrackData(*phTrack, &stAOFrame);
        if (HI_SUCCESS == s32Ret)
        {
            bAudBufAvail = HI_FALSE;
            continue;
        }
        else if (HI_FAILURE == s32Ret)
        {
            printf("HI_UNF_SND_SendTrackData failed(0x%x)!\n", s32Ret);
            break;
        }
        else
        {
            usleep(5 * 1000);
            bAudBufAvail = HI_TRUE;
            continue;
        }
    }

    free(PmcBuf);
}

static HI_S32 System_init(HI_VOID)
{
    HI_S32    s32Ret;

    HI_SYS_Init();

    HIADP_MCE_Exit();

    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
    }

    return s32Ret;
}

static HI_VOID System_Deinit(HI_VOID)
{
    HIADP_Snd_DeInit();
    HI_SYS_DeInit();
}

static HI_S32 Create_Media(HI_VOID)
{
    HI_S32                      s32Ret;
    HI_HANDLE                   hAvplay;
    HI_HANDLE                   hTrack;
    HI_HANDLE                   hWin;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;

    s32Ret = HIADP_Disp_Init(HI_UNF_ENC_FMT_1080i_50);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_Disp_Init failed.\n");
        return s32Ret;
    }

    s32Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    s32Ret |= HIADP_VO_CreatWin(HI_NULL, &hWin);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }
    g_hWin = hWin;
    s32Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_DMX_Init failed.\n");
        goto VO_DEINIT;
    }

    s32Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID,HI_UNF_DMX_PORT_RAM_0);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_AVPLAY_Init();
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto TSBUF_FREE;
    }

    //step 2 Create avplay
    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = PLAY_DMX_ID;
    s32Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    g_hAvplay = hAvplay;

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto AVPLAY_DESTROY;
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto VCHN_CLOSE;
    }

    s32Ret = HI_UNF_VO_AttachWindow(g_hWin, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_VO_AttachWindow failed:%#x.\n",s32Ret);
        goto ACHN_CLOSE;
    }

    s32Ret = HI_UNF_VO_SetWindowEnable(g_hWin, HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    //step 3 Create Salvetrack
    //In some usecase: SlaveTrack should be created, Because when only TTS/UI Audio Track exists, MS12 would
    //create mastertrack to passthrough, So User do not create mastertrack.
    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }
    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }

    g_hTrack = hTrack;

    s32Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;

    s32Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    s32Ret = HI_UNF_AVPLAY_GetAttr(g_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    s32Ret |= HI_UNF_AVPLAY_SetAttr(g_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    pthread_mutex_init(&g_TsMutex,NULL);
    g_bStopTsThread = HI_FALSE;
    pthread_create(&g_TsThd, HI_NULL, (HI_VOID *)TsTthread, HI_NULL);

    HIADP_Search_Init();
    s32Ret = HIADP_Search_GetAllPmt(PLAY_DMX_ID, &g_pProgTbl);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HIADP_Search_GetAllPmt failed.\n");
        goto PSISI_FREE;
    }

    pthread_mutex_lock(&g_TsMutex);
    rewind(g_pTsFile);
    HI_UNF_DMX_ResetTSBuffer(g_TsBuf);

    s32Ret = HIADP_AVPlay_PlayProg_MS12(g_hAvplay, g_pProgTbl, 0, HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HIADP_AVPlay_PlayProg failed.\n");
        goto AVPLAY_STOP;
    }

    pthread_mutex_unlock(&g_TsMutex);

    return HI_SUCCESS;

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    g_pProgTbl = HI_NULL;
    HIADP_Search_DeInit();
    pthread_mutex_destroy(&g_TsMutex);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(g_hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(g_hWin, hAvplay);

ACHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

VCHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

TSBUF_FREE:
    HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

    return s32Ret;
}

static HI_VOID Destroy_Media(HI_VOID)
{
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;

    g_bStopTsThread = HI_TRUE;
    pthread_join(g_TsThd, HI_NULL);

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

    HIADP_Search_FreeAllPmt(g_pProgTbl);
    HIADP_Search_DeInit();

    HI_UNF_SND_Detach(g_hTrack, g_hAvplay);

    HI_UNF_SND_DestroyTrack(g_hTrack);

    HI_UNF_VO_SetWindowEnable(g_hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(g_hWin, g_hAvplay);

    HI_UNF_AVPLAY_ChnClose(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    HI_UNF_AVPLAY_ChnClose(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

    HI_UNF_AVPLAY_Destroy(g_hAvplay);

    HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);

    HI_UNF_AVPLAY_DeInit();

    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

    HI_UNF_VO_DestroyWindow(g_hWin);
    HIADP_VO_DeInit();

    HIADP_Disp_DeInit();
}


static HI_S32 Create_System_Track(HI_VOID)
{
    HI_S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SYS, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &g_hSysTrack);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_VOID Destroy_System_Track(HI_VOID)
{
    if (HI_NULL != g_hSysTrack)
    {
        HI_UNF_SND_DestroyTrack(g_hSysTrack);
    }
    g_hSysTrack = HI_NULL;
}

static HI_S32 Create_Tts_Track(HI_VOID)
{
    HI_S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_TTS, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &g_hTtsTrack);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_VOID Destroy_Tts_Track(HI_VOID)
{
    if (HI_NULL != g_hTtsTrack)
    {
        HI_UNF_SND_DestroyTrack(g_hTtsTrack);
    }
    g_hTtsTrack = HI_NULL;
}

static void print_usage()
{
    printf("Usage: sample_ms12_mixer ts_file tts tts_file system uiaudio_file\n");
    printf("Example1:./sample_ms12_mixer ./test.ts\n");
    printf("Example2:./sample_ms12_mixer null tts ./tts_48k_2ch.pcm\n");
    printf("Example3:./sample_ms12_mixer null system  ./uiaudio_48_2ch.pcm\n");
    printf("Example4:./sample_ms12_mixer ./test.ts tts ./tts_48k_2ch.pcm system ./uiaudio_48_2ch.pcm\n");
}


HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_BOOL                     bMedia = HI_FALSE;
    HI_BOOL                     bUIAudio = HI_FALSE;
    HI_BOOL                     bTts = HI_FALSE;
    HI_U32                      u32Cnt;
    HI_U32                      u32TtsFileID = -1;
    HI_U32                      u32UIAudioFileID = -1;
    HI_CHAR                     InputCmd[32];

    if (argc < 2)
    {
        print_usage();
        return -1;
    }

    //MUST enable ms12,when mixing with TTS/UI Audio
    g_bUseMS12 = HI_TRUE;

    for (u32Cnt = 2; u32Cnt <= argc - 1; u32Cnt++)
    {
        if (!strcasecmp("tts", argv[u32Cnt]))
        {
            u32TtsFileID = ++u32Cnt;
            if (HI_NULL != argv[u32TtsFileID])
            {
                bTts = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
        }
        else if (!strcasecmp("system", argv[u32Cnt]))
        {
            u32UIAudioFileID = ++u32Cnt;
            if (HI_NULL != argv[u32TtsFileID])
            {
                bUIAudio = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
        }
    }

    printf(" Using MS12: %d\n", g_bUseMS12);

    printf("Open Ts file:%s\n", argv[1]);
    g_pTsFile = fopen(argv[1], "rb");
    if (g_pTsFile)
    {
        bMedia = HI_TRUE;
    }
    else
    {
        printf("open file %s error no media found!\n", argv[1]);
        bMedia = HI_FALSE;
    }

    if (HI_TRUE == bTts)
    {
        printf("Open TTS file:%s\n", argv[u32TtsFileID]);
        g_pcmFile[TTS_INDEX] = fopen(argv[u32TtsFileID], "rb");
        if (!g_pcmFile[TTS_INDEX])
        {
            printf("open TTS file %s error!\n", argv[u32TtsFileID]);
            return -1;
        }
    }

    if (HI_TRUE == bUIAudio)
    {
        printf("open System file %s \n", argv[u32UIAudioFileID]);
        g_pcmFile[UIAUDIO_INDEX] = fopen(argv[u32UIAudioFileID], "rb");
        if (!g_pcmFile[UIAUDIO_INDEX])
        {
            printf("open System file %s error!\n", argv[u32UIAudioFileID]);
            return -1;
        }
    }

    System_init();

    if (HI_TRUE == bMedia)
    {
        printf("Creat Main track & thread\n");
        Create_Media();
    }

    if (HI_TRUE == bTts)
    {
        printf("Creat tts track & thread\n");
        Create_Tts_Track();
        g_bStopFlag[TTS_INDEX] = HI_FALSE;
        pthread_create(&g_hPcmThread[TTS_INDEX], HI_NULL, (HI_VOID*)PcmThread, (HI_VOID*)HI_NULL + TTS_INDEX);
    }

    if (HI_TRUE == bUIAudio)
    {
        printf("Creat ui audio track & thread\n");
        Create_System_Track();
        g_bStopFlag[UIAUDIO_INDEX] = HI_FALSE;
        pthread_create(&g_hPcmThread[UIAUDIO_INDEX], HI_NULL, (HI_VOID*)PcmThread, (HI_VOID*)HI_NULL + UIAUDIO_INDEX);
    }

    while (1)
    {
        printf("please input 'q' to quit!\n");

        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if ('v' == InputCmd[0])
        {
            printf("SetMediaFadeVol here\n");
            continue;
        }
    }

    if (HI_TRUE == bUIAudio)
    {
        printf("Destory ui audio track & thread\n");
        g_bStopFlag[UIAUDIO_INDEX] = HI_TRUE;
        pthread_join(g_hPcmThread[UIAUDIO_INDEX], HI_NULL);
        Destroy_System_Track();
    }

    if (HI_TRUE == bTts)
    {
        printf("Destory tts audio track & thread\n");
        g_bStopFlag[TTS_INDEX] = HI_TRUE;
        pthread_join(g_hPcmThread[TTS_INDEX], HI_NULL);
        Destroy_Tts_Track();
    }

    if (HI_TRUE == bMedia)
    {
        printf("Destory Media & thread\n");
        Destroy_Media();
    }

    System_Deinit();

    if (g_pTsFile)
        fclose(g_pTsFile);

    if (g_pcmFile[TTS_INDEX])
        fclose(g_pcmFile[TTS_INDEX]);

    if (g_pcmFile[UIAUDIO_INDEX])
        fclose(g_pcmFile[UIAUDIO_INDEX]);

    return HI_SUCCESS;
}
