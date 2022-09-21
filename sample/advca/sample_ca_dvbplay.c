/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_dvbplay.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
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
#include "hi_unf_hdmi.h"
#include "hi_unf_descrambler.h"
#include "hi_unf_advca.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "hi_adp.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "parse_config_file.h"


#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;
HI_S32             g_CwType = 0;

KEYLADDER_TYPE_E g_KladType;
HI_UNF_ADVCA_ALG_TYPE_E       g_kladAlg  = HI_UNF_ADVCA_ALG_TYPE_BUTT;

HI_U8 g_u8SessionKey1[16] = {0};
HI_U8 g_u8SessionKey2[16] = {0};
HI_U8 g_u8SessionKey3[16] = {0};
HI_U8 g_u8EncrytedOddKey[16] = {0};
HI_U8 g_u8EncrytedEvenKey[16] = {0};
HI_U8 g_u8ClearOddKey[8] = {0};
HI_U8 g_u8ClearEvenKey[8] = {0};


static HI_VOID printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{    
    HI_U32 i = 0;    

    if (NULL != string)    
    {        
        printf("%s\n", string);    
    }    

    for (i = 0 ; i < u32Length; i++)
    {
        if((i % 16 == 0) && (i != 0))
            printf("\n");

        printf("0x%02x ", pu8Input[i]);
    }

    printf("\n");

    return;
}

static HI_S32 get_cw_type()
{
    HI_CHAR *value = HI_NULL;

    value = get_config_var("ENCRYPTCW");
    if (HI_NULL == value)
    {
        return -1;
    }

    if (0 == strncmp(value, "NO", sizeof ("NO")))
    {
        g_CwType = 0;
        printf("clear cw selected\n");
        return 0;
    }

    if (0 == strncmp(value, "YES", sizeof ("YES")))
    {
        g_CwType = 1;
        printf("encrypt cw selected\n");
        return 0;
    }

    g_CwType = 0;
    printf("not set cw type, clear cw selected\n");

    return 0;
}

static HI_S32 readConfigFile(HI_CHAR *pFileName)
{
    HI_S32 s32ValueNum = 0;
    HI_S32 s32Ret = 0;

    s32ValueNum = parse_config_file(pFileName);
    if (0 == s32ValueNum || MAX_VAR_NUM < s32ValueNum)
    {
        return HI_FAILURE;
    }

    get_cw_type();

    s32Ret |= get_keyladder_type(&g_KladType);
    s32Ret |= get_keyladder_alg(&g_kladAlg);    

    if (s32Ret != 0)
    {
        printf("read config key failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 setCsa2Cw(HI_HANDLE hKey)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;

    printf("use csa2 keyladder\n");

    if (HI_UNF_ADVCA_ALG_TYPE_TDES == g_kladAlg)
    {
        HI_UNF_ADVCA_SetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_TDES);
        printf("Keyladder Alg  is TDES\n");

    }
    else
    {
        HI_UNF_ADVCA_SetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_AES);
        printf("Keyladder Alg  is AES\n");        
    }

    HI_UNF_ADVCA_GetDVBKeyLadderStage(&enStage);
    if (enStage >= HI_UNF_ADVCA_KEYLADDER_LEV2)
    {
        get_key_value("SESSIONKEY1", g_u8SessionKey1, 16);
        printBuffer("Sessionkey1:", g_u8SessionKey1, 16);
        
        Ret |= HI_UNF_ADVCA_SetDVBSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV1, g_u8SessionKey1);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_ADVCA_SetDVBSessionKey failed\n");            
            return HI_FAILURE;
        }
    }

    if (enStage >= HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        get_key_value("SESSIONKEY2", g_u8SessionKey2, 16);
        printBuffer("Sessionkey2:", g_u8SessionKey2, 16);
        
        Ret |= HI_UNF_ADVCA_SetDVBSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV2, g_u8SessionKey2);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_ADVCA_SetDVBSessionKey failed\n");            
            return HI_FAILURE;
        }
    }

    get_key_value("ENCRYPTEDODDKEY", g_u8EncrytedOddKey, 16);
    get_key_value("ENCRYPTEDEVENKEY", g_u8EncrytedEvenKey, 16);

    printBuffer("Encrypted Odd key :", g_u8EncrytedOddKey, 16);
    printBuffer("Encrypted enen key:", g_u8EncrytedEvenKey, 16);

    Ret = HI_UNF_DMX_SetDescramblerOddKey(hKey,g_u8EncrytedOddKey);
    Ret |= HI_UNF_DMX_SetDescramblerEvenKey(hKey,g_u8EncrytedEvenKey);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_SetDescramblerEvenKey failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 setCsa3Cw(HI_HANDLE hKey)
{
    HI_S32 Ret;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;

    printf("use csa3 keyladder\n");

    if (HI_UNF_ADVCA_ALG_TYPE_TDES == g_kladAlg)
    {
        Ret = HI_UNF_ADVCA_SetCSA3Alg(HI_UNF_ADVCA_ALG_TYPE_TDES);
        printf("Keyladder Alg  is TDES\n");
    }
    else
    {
        Ret = HI_UNF_ADVCA_SetCSA3Alg(HI_UNF_ADVCA_ALG_TYPE_AES);
        printf("Keyladder Alg  is AES\n");
    }

    HI_UNF_ADVCA_GetCSA3KeyLadderStage(&enStage);
    if (enStage >= HI_UNF_ADVCA_KEYLADDER_LEV2)
    {
        get_key_value("SESSIONKEY1", g_u8SessionKey1, 16);
        printBuffer("Sessionkey1:", g_u8SessionKey1, 16);

        Ret = HI_UNF_ADVCA_SetCSA3SessionKey(HI_UNF_ADVCA_KEYLADDER_LEV1, g_u8SessionKey1);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_ADVCA_SetCSA3SessionKey failed\n");            
            return HI_FAILURE;
        }
    }
    
    if (enStage >= HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        get_key_value("SESSIONKEY2", g_u8SessionKey2, 16);
        printBuffer("Sessionkey2:", g_u8SessionKey2, 16);
        
        Ret = HI_UNF_ADVCA_SetCSA3SessionKey(HI_UNF_ADVCA_KEYLADDER_LEV2, g_u8SessionKey2);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_ADVCA_SetCSA3SessionKey failed\n");            
            return HI_FAILURE;
        }
    }

    get_key_value("ENCRYPTEDODDKEY", g_u8EncrytedOddKey, 16);
    get_key_value("ENCRYPTEDEVENKEY", g_u8EncrytedEvenKey, 16);

    printBuffer("Encrypted Odd key :", g_u8EncrytedOddKey, 16);
    printBuffer("Encrypted enen key:", g_u8EncrytedEvenKey, 16);

    Ret = HI_UNF_DMX_SetDescramblerOddKey(hKey, g_u8EncrytedOddKey);
    Ret |= HI_UNF_DMX_SetDescramblerEvenKey(hKey, g_u8EncrytedEvenKey);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_SetDescramblerEvenKey failed\n");
        return HI_FAILURE;
    }    

    return HI_SUCCESS;
}

HI_S32 AVPLAY_SetCW(HI_HANDLE hKey)
{
    HI_S32 Ret = HI_SUCCESS;

    if (0 == g_CwType)
    {
        get_key_value("CLEARODDKEY", g_u8ClearOddKey, 8);
        get_key_value("CLEAREVENKEY", g_u8ClearEvenKey, 8);

        printBuffer("Clear Odd key :", g_u8ClearOddKey, 8);
        printBuffer("Clear Even key:", g_u8ClearEvenKey, 8);

        Ret = HI_UNF_DMX_SetDescramblerOddKey(hKey,g_u8ClearOddKey);
        Ret |= HI_UNF_DMX_SetDescramblerEvenKey(hKey,g_u8ClearEvenKey);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DMX_SetDescramblerKey failed\n");
            return Ret;
        }
    }
    else
    {
        if (KEYLADDER_TYPE_CSA2 == g_KladType)
        {
            Ret = setCsa2Cw(hKey);
        }
        else if (KEYLADDER_TYPE_CSA3 == g_KladType)
        {
            Ret = setCsa3Cw(hKey);
        }
        else
        {
            printf("keyladdertype:%x is not supported\n", g_KladType);
        }
    }
    
    return Ret;
}


static HI_S32 AVPLAY_AttachDescramble(HI_HANDLE hAvplay,HI_HANDLE *phKey)
{
    HI_S32 Ret;
    HI_UNF_DMX_DESCRAMBLER_ATTR_S stDesramblerAttr;
    HI_HANDLE hKey;
    HI_HANDLE hDmxVidChn,hDmxAudChn;

	memset(&stDesramblerAttr,0,sizeof(HI_UNF_DMX_DESCRAMBLER_ATTR_S));
    if (0 == g_CwType)
    {
        stDesramblerAttr.enCaType = HI_UNF_DMX_CA_NORMAL;
    }
    else
    {
        stDesramblerAttr.enCaType = HI_UNF_DMX_CA_ADVANCE;
    }

    if (KEYLADDER_TYPE_CSA2 == g_KladType)
    {
        stDesramblerAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2;
    }
    else if (KEYLADDER_TYPE_CSA3 == g_KladType)
    {
        stDesramblerAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3;
    }
    
	stDesramblerAttr.enEntropyReduction = HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE;
    Ret = HI_UNF_DMX_CreateDescramblerExt(0,&stDesramblerAttr,&hKey);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_CreateDescramblerExt failed %#x\n",Ret);
        return HI_FAILURE;
    }

    Ret = HI_UNF_AVPLAY_GetDmxVidChnHandle(hAvplay,&hDmxVidChn);
    Ret |= HI_UNF_AVPLAY_GetDmxAudChnHandle(hAvplay,&hDmxAudChn);
    Ret = HI_UNF_DMX_AttachDescrambler(hKey,hDmxVidChn);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachDescrambler hDmxVidChn failed\n");        
        (HI_VOID)HI_UNF_DMX_DestroyDescrambler(hKey);
        return HI_FAILURE;
    }

    Ret = HI_UNF_DMX_AttachDescrambler(hKey,hDmxAudChn);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachDescrambler hDmxAudChn failed\n");                
        (HI_VOID)HI_UNF_DMX_DetachDescrambler(hKey,hDmxVidChn);
        (HI_VOID)HI_UNF_DMX_DestroyDescrambler(hKey);
        return HI_FAILURE;
    }
    *phKey = hKey;

    return HI_SUCCESS;
}



HI_S32 AVPLAY_DetachDescramble(HI_HANDLE hAvplay,HI_HANDLE hKey)
{
    HI_S32 Ret;
    HI_HANDLE hDmxVidChn,hDmxAudChn;

    Ret = HI_UNF_AVPLAY_GetDmxVidChnHandle(hAvplay,&hDmxVidChn);
    Ret |= HI_UNF_AVPLAY_GetDmxAudChnHandle(hAvplay,&hDmxAudChn);
    Ret |= HI_UNF_DMX_DetachDescrambler(hKey,hDmxVidChn);
    Ret |= HI_UNF_DMX_DetachDescrambler(hKey,hDmxAudChn);
    Ret |= HI_UNF_DMX_DestroyDescrambler(hKey);
    
    return Ret;
}


HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                      Ret;
    HI_HANDLE                   hWin;
    HI_HANDLE                   hAvplay;
    HI_HANDLE                   hDescramber;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                     InputCmd[32];
    HI_U32                      ProgNum;
    HI_HANDLE                   hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S    TrackAttr;
    HI_U32                      Tuner = 0;
    HI_U32                      TunerFreq;
    HI_U32                      TunerSrate;
    HI_U32                      ThirdParam;
    HI_U32                      u32Ber[3];
    HI_UNF_ENC_FMT_E            Format = HI_UNF_ENC_FMT_1080i_50;

    if (argc < 2)
    {
        printf("Usage: %s [keyconfigfile] [freq] [srate] [qamtype or polarization] [vo_format] [tuner]\n"
                "       keyconfigfile name: \n"
                "       qamtype or polarization: \n"
                "           For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64] \n"
                "           For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0] \n"
                "       vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50  default HI_UNF_ENC_FMT_1080i_50\n"
                "       Tuner: value can be 0, 1, 2, 3\n",
                argv[0]);

        printf("Example: %s 618 6875 64 1080i_50 0\n", argv[0]);
        return HI_FAILURE;
    }

	Ret = readConfigFile(argv[1]);
	if (HI_SUCCESS != Ret)
	{
		printf("parse config file failed\n");
		return HI_FAILURE;
	}

    TunerFreq  = strtol(argv[2], NULL, 0);
    TunerSrate = (TunerFreq > 1000) ? 27500 : 6875;
    ThirdParam = (TunerFreq > 1000) ? 0 : 64;

    if (argc >= 4)
    {
        TunerSrate = strtol(argv[3], NULL, 0);
    }

    if (argc >= 5)
    {
        ThirdParam = strtol(argv[4], NULL, 0);
    }

    if (argc >= 6)
    {
        Format = HIADP_Disp_StrToFmt(argv[5]);
    }

    if (argc >= 7)
    {
        Tuner = strtol(argv[6], NULL, 0);
    }

    HI_SYS_Init();

    HIADP_MCE_Exit();

	Ret = HI_UNF_ADVCA_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_ADVCA_Init failed\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Snd_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Disp_Init(Format);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Disp_DeInit failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }

    Ret = HI_UNF_DMX_Init();
    Ret |= HIADP_DMX_AttachTSPort(0, Tuner);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HIADP_Demux_Init failed.\n");
        goto VO_DEINIT;
    }

    Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Demux_Init failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HIADP_Tuner_Connect(Tuner, TunerFreq, TunerSrate, ThirdParam);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Tuner_Connect failed.\n");
        goto TUNER_DEINIT;
    }

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(0,&g_pProgTbl);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Search_GetAllPmt failed\n");
        goto PSISI_FREE;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    Ret |= HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto PSISI_FREE;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = 0;
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    Ret |= HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto CHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HI_UNF_VO_AttachWindow failed.\n");
        goto CHN_CLOSE;
    }

    Ret = AVPLAY_AttachDescramble(hAvplay, &hDescramber);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call AVPLAY_AttachDescramble failed\n");
        goto CHN_CLOSE;
    }

    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &TrackAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &TrackAttr, &hTrack);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    SyncAttr.stSyncStartRegion.s32VidPlusTime = 100;
    SyncAttr.stSyncStartRegion.s32VidNegativeTime = -100;
    SyncAttr.bQuickOutput = HI_FALSE;
    Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    ProgNum = 0;

    AVPLAY_SetCW(hDescramber);

    Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum,HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call SwitchProg failed.\n");
        goto AVPLAY_STOP;
    }

    while(1)
    {
        printf("please input the q to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if ('s' == InputCmd[0])
        {
            static int cnt = 0;
            HI_BOOL bSmartvol;
            if(cnt % 2 == 0)
            {
                bSmartvol = HI_FALSE;
                printf("prepare to set smart volume true!\n");
                HI_UNF_SND_SetTrackSmartVolume(hTrack, HI_TRUE);
                HI_UNF_SND_GetTrackSmartVolume(hTrack, &bSmartvol);
                printf("GetSmartVolume: bSmartvol = %d\n", bSmartvol);
            }
            else
            {
                bSmartvol = HI_TRUE;
                printf("prepare to set smart volume false!\n");
                HI_UNF_SND_SetTrackSmartVolume(hTrack, HI_FALSE);
                HI_UNF_SND_GetTrackSmartVolume(hTrack, &bSmartvol);
                printf("GetSmartVolume: bSmartvol = %d\n", bSmartvol);
            }
            cnt++;
        }

        if ('g' == InputCmd[0])
        {
            HI_UNF_TUNER_GetBER(Tuner, &u32Ber[0]);
            printf("\n-->BER: %dE -%d\n",u32Ber[0],u32Ber[2]);
            HI_UNF_TUNER_GetSNR(Tuner, &ThirdParam);
            printf("-->SNR: %d \n",ThirdParam);
            HI_UNF_TUNER_GetSignalStrength(Tuner, &ThirdParam);
            printf("-->SSI: %d \n",ThirdParam);
            HI_UNF_TUNER_GetSignalQuality(Tuner, &ThirdParam);
            printf("-->SQI: %d \n\n",ThirdParam);
            continue;
        }
        
        ProgNum = atoi(InputCmd);

        if (ProgNum == 0)
            ProgNum = 1;
        AVPLAY_SetCW(hDescramber);
        Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum-1,HI_TRUE);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call SwitchProgfailed!\n");
            break;
        }
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
    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);

    AVPLAY_DetachDescramble(hAvplay, hDescramber);

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
    HI_SYS_DeInit();
    HI_UNF_ADVCA_DeInit();

    return Ret;
}


