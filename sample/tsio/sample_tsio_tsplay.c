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
#include "hi_unf_tsio.h"

#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"


FILE               *g_pTsFile = HI_NULL;
static pthread_t   g_DmxInjThd, g_TsioInjThd;
static pthread_mutex_t g_TsMutex = PTHREAD_MUTEX_INITIALIZER;
static HI_BOOL     g_bStopDmxInjThread = HI_FALSE, g_bStopTsioInjThread = HI_FALSE;
HI_HANDLE          g_TsioInjHandle;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

#define  PLAY_DMX_ID  0

HI_VOID TsioInjThread(HI_VOID *args)
{
    HI_UNF_TSIO_BUFFER_S  Buf = {0};
    HI_U32                Readlen;
    HI_S32                Ret;

    while (!g_bStopTsioInjThread)
    {
		pthread_mutex_lock(&g_TsMutex);
        Ret = HI_UNF_TSIO_GetBuffer(g_TsioInjHandle, 188 * 50, &Buf, 1000);
        if (Ret != HI_SUCCESS )
        {
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

loop:
        Readlen = fread(Buf.pu8Data, sizeof(HI_S8), 188*50, g_pTsFile);
        if(Readlen <= 0 || Readlen != 188 * 50)
        {
            printf("read ts file end and rewind!\n");
            rewind(g_pTsFile);
            goto loop;
        }

        Ret = HI_UNF_TSIO_PutBuffer(g_TsioInjHandle, &Buf);
        if (Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_TSIO_PutBuffer failed.\n");
        }

        pthread_mutex_unlock(&g_TsMutex);
    }

    return;
}

HI_VOID DmxInjThread(HI_VOID *args)
{
    HI_HANDLE TsBufHandle = (HI_HANDLE)(unsigned long)args;
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                Readlen;
    HI_S32                Ret;

    while (!g_bStopDmxInjThread)
    {
        Ret = HI_UNF_DMX_GetTSBuffer(TsBufHandle, 188*50, &StreamBuf, 1000);
        if (Ret != HI_SUCCESS )
        {
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 188*50, g_pTsFile);
        if(Readlen <= 0)
        {
            printf("read ts file end and rewind!\n");
            rewind(g_pTsFile);
            continue;
        }

        Ret = HI_UNF_DMX_PutTSBuffer(TsBufHandle, Readlen);
        if (Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
        }
    }

    Ret = HI_UNF_DMX_ResetTSBuffer(TsBufHandle);
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }

    rewind(g_pTsFile);

    return;
}

HI_S32 HIADP_PROG_Init(HI_U32 *ProgNum)
{
    HI_S32 Ret = HI_FAILURE;
    HI_HANDLE DmxTsHandle;

    Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID, HI_UNF_DMX_PORT_RAM_0);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        goto out0;
    }

    Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &DmxTsHandle);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        goto out1;
    }

    g_bStopDmxInjThread = HI_FALSE;
    pthread_create(&g_DmxInjThd, HI_NULL, (HI_VOID *)DmxInjThread, (HI_VOID *)(unsigned long)DmxTsHandle);

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(PLAY_DMX_ID, &g_pProgTbl);
    if (Ret != HI_SUCCESS)
    {
        printf("call HIADP_Search_GetAllPmt failed.\n");
        goto out2;
    }

    g_bStopDmxInjThread = HI_TRUE;
    pthread_join(g_DmxInjThd, HI_NULL);

    *ProgNum = 0;

out2:
    HI_UNF_DMX_DestroyTSBuffer(DmxTsHandle);
out1:
    HI_UNF_DMX_DetachTSPort(PLAY_DMX_ID);
out0:
    return Ret;
}

HI_S32 HIADP_TSIO_Init(HI_U32 ProgNum)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_TSIO_BUFFER_ATTR_S   RamAttrs = {
        .enStreamType   = HI_UNF_TSIO_RAM_TS,
        .u32BufSize     = 2 * 1024 * 1024,
        .u32MaxDataRate = 0,
    };
    HI_UNF_TSIO_ATTR_S          SrvAttrs = {
        .stOutput       = {
            .enOutputType = HI_UNF_TSIO_OUTPUT_DMX,
            .unParam = {
                .stDMX = {
                    .enPort = HI_UNF_DMX_PORT_TSIO_0,
                }
            }
        },
        .u32SID         = 0xffffffff,
    };
    HI_HANDLE                   hTsio;

    Ret = HI_UNF_TSIO_Init(HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_TSIO_Init failed.\n");
        goto out0;
    }

    Ret = HI_UNF_TSIO_CreateBuffer(HI_UNF_TSIO_RAM_PORT_1, &RamAttrs, &g_TsioInjHandle);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_TSIO_CreateBuffer failed.\n");
        goto out1;
    }

    Ret = HI_UNF_TSIO_Create(&SrvAttrs, &hTsio);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_Create failed.\n");
        goto out2;
    }

    Ret = HI_UNF_TSIO_AttachRAMInput(hTsio, g_TsioInjHandle);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_AttachRAMInput failed.\n");
        goto out3;
    }

    /* video */
    Ret = HI_UNF_TSIO_AddPID(hTsio, g_pProgTbl->proginfo[ProgNum].VElementPid);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_AddPID video failed.\n");
        goto out4;
    }

    /* audio */
    Ret = HI_UNF_TSIO_AddPID(hTsio, g_pProgTbl->proginfo[ProgNum].AElementPid);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_AddPID audio failed.\n");
        goto out5;
    }

    Ret = HI_UNF_TSIO_Start(hTsio);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_TSIO_Start failed.\n");
        goto out6;
    }

    g_bStopTsioInjThread = HI_FALSE;
    pthread_create(&g_TsioInjThd, HI_NULL, (HI_VOID *)TsioInjThread, HI_NULL);

    return Ret;

out6:
    HI_UNF_TSIO_AddPID(hTsio, g_pProgTbl->proginfo[ProgNum].AElementPid);
out5:
    HI_UNF_TSIO_AddPID(hTsio, g_pProgTbl->proginfo[ProgNum].VElementPid);
out4:
    HI_UNF_TSIO_DetachInput(hTsio);
out3:
    HI_UNF_TSIO_Destroy(hTsio);
out2:
    HI_UNF_TSIO_DestroyBuffer(g_TsioInjHandle);
out1:
    HI_UNF_TSIO_DeInit();
out0:
    return Ret;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32                      Ret;
    HI_HANDLE                   hWin = HI_INVALID_HANDLE;
    HI_HANDLE                   hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                     InputCmd[32];
    HI_UNF_ENC_FMT_E            enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_U32                      ProgNum;
    HI_HANDLE                   hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;

    if (argc < 2)
    {
        printf("Usage: %s file [vo_format]\n", argv[0]);
        printf("\tvo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50\n");
        printf("Example:\n\t%s ./test.ts 1080i_50\n", argv[0]);
        return 0;
    }

    if (3 == argc)
    {
        enFormat = HIADP_Disp_StrToFmt(argv[2]);
    }

    g_pTsFile = fopen(argv[1], "rb");
    if (!g_pTsFile)
    {
        printf("open file %s error!\n", argv[1]);
        return -1;
    }

    HI_SYS_Init();

    HIADP_MCE_Exit();

    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Disp_Init(enFormat);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Disp_Init failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_VO_Init failed.\n");
        goto DISP_DEINIT;
    }

    Ret = HIADP_VO_CreatWin(HI_NULL, &hWin);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_VO_CreatWin failed.\n");
        goto VO_DEINIT;
    }

    Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_Init failed.\n");
        goto VO_DEINIT;
    }

    Ret = HIADP_PROG_Init(&ProgNum);
    if (HI_SUCCESS != Ret)
    {
        printf("Detect program failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID, HI_UNF_DMX_PORT_TSIO_0);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HIADP_TSIO_Init(ProgNum);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_TSIO_Init failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    if (HI_SUCCESS != Ret)
    {
        printf("call RegADecLib failed.\n");
        goto TSIO_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto TSIO_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = PLAY_DMX_ID;
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto AVPLAY_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto VCHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_VO_AttachWindow failed:%#x.\n",Ret);
        goto ACHN_CLOSE;
    }

    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    pthread_mutex_lock(&g_TsMutex);
    rewind(g_pTsFile);
    HI_UNF_TSIO_ResetBuffer(g_TsioInjHandle);

    Ret = HIADP_AVPlay_PlayProg(hAvplay, g_pProgTbl, ProgNum, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call HIADP_AVPlay_PlayProg failed.\n");
        goto AVPLAY_STOP;
    }

    pthread_mutex_unlock(&g_TsMutex);

    while (1)
    {
        static HI_U32 u32TplaySpeed = 2;
        printf("please input 'q' to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if ('t' == InputCmd[0])
        {
            HI_UNF_AVPLAY_TPLAY_OPT_S stTplayOpt;
            printf("%dx tplay\n",u32TplaySpeed);

            stTplayOpt.enTplayDirect = HI_UNF_AVPLAY_TPLAY_DIRECT_FORWARD;
            stTplayOpt.u32SpeedInteger = u32TplaySpeed;
            stTplayOpt.u32SpeedDecimal = 0;

            HI_UNF_AVPLAY_SetDecodeMode(hAvplay, HI_UNF_VCODEC_MODE_I);
            HI_UNF_AVPLAY_Tplay(hAvplay,&stTplayOpt);
            u32TplaySpeed = (32 == u32TplaySpeed * 2) ? (2) : (u32TplaySpeed * 2) ;
            continue;
        }

        if ('r' == InputCmd[0])
        {
            printf("resume\n");
            HI_UNF_AVPLAY_SetDecodeMode(hAvplay, HI_UNF_VCODEC_MODE_NORMAL);
            HI_UNF_AVPLAY_Resume(hAvplay,HI_NULL);
            u32TplaySpeed = 2;
            continue;
        }

        if ('g' == InputCmd[0])
        {
            HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;
            HI_UNF_AVPLAY_GetStatusInfo(hAvplay,&stStatusInfo);
            printf("localtime %u playtime %u\n",stStatusInfo.stSyncStatus.u32LocalTime,stStatusInfo.stSyncStatus.u32PlayTime);
            continue;
        }

        ProgNum = atoi(InputCmd);
        if (ProgNum == 0)
            ProgNum = 1;

        pthread_mutex_lock(&g_TsMutex);
        rewind(g_pTsFile);
        HI_UNF_TSIO_ResetBuffer(g_TsioInjHandle);

        Ret = HIADP_AVPlay_PlayProg(hAvplay, g_pProgTbl, ProgNum - 1, HI_TRUE);
        if (Ret != HI_SUCCESS)
        {
            printf("call HIADP_AVPlay_PlayProg failed!\n");
            break;
        }

        pthread_mutex_unlock(&g_TsMutex);
    }

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);

ACHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

VCHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

TSIO_DEINIT:
    g_bStopTsioInjThread = HI_TRUE;
    pthread_join(g_TsioInjThd, HI_NULL);
    HI_UNF_TSIO_DestroyBuffer(g_TsioInjHandle);
    HI_UNF_TSIO_DeInit();

DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    if (HI_INVALID_HANDLE != hWin)
    {
        HI_UNF_VO_DestroyWindow(hWin);
    }
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();

    fclose(g_pTsFile);
    g_pTsFile = HI_NULL;

    return Ret;
}


