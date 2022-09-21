/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_hdmi_tsplay.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;


extern HI_U32 HDMI_Test_CMD(HI_CHAR * u8String);

HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                      s32Ret = HI_SUCCESS;
    HI_CHAR                     szInputCmd[128];
    HI_U32                      u32ProgNum = 0;
    HI_U32                      u32Tuner = 0;
    HI_U32                      u32TunerFreq;
    HI_U32                      u32TunerSrate;
    HI_U32                      u32ThirdParam;
    HI_HANDLE                   hWin = HI_INVALID_HANDLE;
    HI_HANDLE                   hAvplay = HI_INVALID_HANDLE;
    HI_UNF_AVPLAY_ATTR_S        stAvplayAttr;
    HI_UNF_SYNC_ATTR_S          stSyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    stStop;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;
    HI_SYS_VERSION_S            stSysVersion;
    HI_UNF_ENC_FMT_E            enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_HANDLE                   hTrack = HI_INVALID_HANDLE;
    HI_CHIP_TYPE_E              enChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E           enChipVersion = HI_CHIP_VERSION_BUTT;
    

    if (argc < 2)
    {
        printf("Usage: %s [freq] [srate] [qamtype or polarization] [vo_format] [tuner]\n"
                "       qamtype or polarization: \n"
                "           For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64] \n"
                "           For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0] \n"
                "       vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50  default HI_UNF_ENC_FMT_1080i_50\n"
                "       Tuner: value can be 0, 1, 2, 3\n",
                argv[0]);

        printf("Example: %s 618 6875 64 1080i_50 0\n", argv[0]);
        return HI_FAILURE;
    }

    
    u32TunerFreq  = strtol(argv[1], NULL, 0);
    u32TunerSrate = (u32TunerFreq > 1000) ? 27500 : 6875;
    u32ThirdParam = (u32TunerFreq > 1000) ? 0 : 64;

    if (argc >= 3)
    {
        u32TunerSrate = strtol(argv[2], NULL, 0);
    }

    if (argc >= 4)
    {
        u32ThirdParam = strtol(argv[3], NULL, 0);
    }

    if (argc >= 5)
    {
        enFormat = HIADP_Disp_StrToFmt(argv[4]);
    }

    if (argc >= 6)
    {
        u32Tuner = strtol(argv[5], NULL, 0);
    }

    HI_SYS_Init();

    s32Ret = HI_SYS_GetVersion(&stSysVersion);
    if (HI_SUCCESS == s32Ret)
    {
        enChipType    = stSysVersion.enChipTypeHardWare;
        enChipVersion = stSysVersion.enChipVersion;

        if (   ((HI_CHIP_TYPE_HI3798M == enChipType) && (HI_CHIP_VERSION_V100 == enChipVersion))
            || ((HI_CHIP_TYPE_HI3796M == enChipType) && (HI_CHIP_VERSION_V100 == enChipVersion)) )
        {
            system("echo volt=1140 > /proc/msp/pm_core");
        }
    }

    HIADP_MCE_Exit();

    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_Snd_Init failed. ret = 0x%x\n", s32Ret);
        goto SYS_DEINIT;
    }

    s32Ret = HIADP_Disp_Init(enFormat);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_Disp_Init failed. ret = 0x%x\n", s32Ret);
        goto SND_DEINIT;
    }

    s32Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    s32Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_VO_Init/HIADP_VO_CreatWin failed. ret = 0x%x\n", s32Ret);
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }

    s32Ret = HI_UNF_DMX_Init();
    s32Ret |= HIADP_DMX_AttachTSPort(0, u32Tuner);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_DMX_Init/HIADP_DMX_AttachTSPort failed. ret = 0x%x\n", s32Ret);
        goto VO_DEINIT;
    }

    s32Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_Tuner_Init failed. ret = 0x%x\n", s32Ret);
        goto DMX_DEINIT;
    }

    s32Ret = HIADP_Tuner_Connect(u32Tuner, u32TunerFreq, u32TunerSrate, u32ThirdParam);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_Tuner_Connect failed. ret = 0x%x\n", s32Ret);
        goto TUNER_DEINIT;
    }

    HIADP_Search_Init();
    s32Ret = HIADP_Search_GetAllPmt(0,&g_pProgTbl);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_Search_GetAllPmt failed. ret = 0x%x\n", s32Ret);
        goto PSISI_FREE;
    }

    s32Ret = HIADP_AVPlay_RegADecLib();
    s32Ret |= HI_UNF_AVPLAY_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_AVPLAY_Init failed. ret = 0x%x\n", s32Ret);
        goto PSISI_FREE;
    }

    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    stAvplayAttr.u32DemuxId = 0;
    s32Ret |= HI_UNF_AVPLAY_Create(&stAvplayAttr, &hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_AVPLAY_Create failed. ret = 0x%x\n", s32Ret);
        goto AVPLAY_DEINIT;
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    s32Ret |= HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_AVPLAY_ChnOpen failed. ret = 0x%x\n", s32Ret);
        goto CHN_CLOSE;
    }

    s32Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_VO_AttachWindow failed. ret = 0x%x\n", s32Ret);
        goto CHN_CLOSE;
    }
    s32Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_VO_SetWindowEnable failed. ret = 0x%x\n", s32Ret);
        goto WIN_DETACH;
    }

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed. ret = 0x%x\n", s32Ret);
        goto WIN_DETACH;
    }

    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_SND_CreateTrack failed. ret = 0x%x\n", s32Ret);
        goto WIN_DETACH;
    }

    s32Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_SND_Attach failed. ret = 0x%x\n", s32Ret);
        goto TRACK_DESTROY;
    }

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);
    stSyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    stSyncAttr.stSyncStartRegion.s32VidPlusTime = 100;
    stSyncAttr.stSyncStartRegion.s32VidNegativeTime = -100;
    stSyncAttr.bQuickOutput = HI_FALSE;
    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_AVPLAY_SetAttr failed. ret = 0x%x\n", s32Ret);
        goto SND_DETACH;
    }

    u32ProgNum = 0;


    s32Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl, u32ProgNum,HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HIADP_AVPlay_PlayProg failed. ret = 0x%x\n", s32Ret);
        goto AVPLAY_STOP;
    }

    while(1)
    {

        //SAMPLE_GET_INPUTCMD(InputCmd);
        sample_printf("please input 'h' to get help or 'q' to quit!\n");
        sample_printf("hdmi_cmd >");
        memset(szInputCmd, 0, 128);
        SAMPLE_GET_INPUTCMD(szInputCmd);
        if ('q' == szInputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
        if (('d' == szInputCmd[0])
            && ('v' == szInputCmd[1])
            &&('b' == szInputCmd[2]))
        {
            u32ProgNum = atoi(&szInputCmd[4]);
            if (u32ProgNum == 0)
                u32ProgNum = 1;
            s32Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl, u32ProgNum-1,HI_TRUE);
            if (HI_SUCCESS != s32Ret)
            {
                sample_printf("call HIADP_AVPlay_PlayProg! ret = 0x%x\n", s32Ret);
                break;
            }
            continue;
        }
        
        HDMI_Test_CMD(szInputCmd);
        if ( (0 == strcmp("help", (char *)szInputCmd)) || (0 == strcmp("h", (char *)szInputCmd)) )
        {
             printf("\t dvb num             change to play program num\n");
        }
    }

AVPLAY_STOP:
    stStop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    stStop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &stStop);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);

CHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    HIADP_Search_DeInit();

TUNER_DEINIT:
    HIADP_Tuner_DeInit();

DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

SYS_DEINIT:
    if (((HI_CHIP_TYPE_HI3798M == enChipType) && (HI_CHIP_VERSION_V100 == enChipVersion))
        || ((HI_CHIP_TYPE_HI3796M == enChipType) && (HI_CHIP_VERSION_V100 == enChipVersion)) )
    {
        system("echo volt=0 > /proc/msp/pm_core");
    }

    HI_SYS_DeInit();

    return s32Ret;
}


