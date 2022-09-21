#include "av_play.h"

#define AVPLAY_AUDIO_BUFF_SIZE (2 * 1024 * 1024)
#define AVPLAY_VIDEO_BUFF_SIZE (9 * 1024 * 1024)
#define ADTS_HEAD_LEN          (7)

static HI_S32 TsPlayerEventHandler(HI_HANDLE handle, HI_UNF_AVPLAY_EVENT_E enEvent, HI_U32 para)
{
    return HI_SUCCESS;
}

AvPlay::AvPlay()
{
}

AvPlay::~AvPlay()
{
}

HI_S32 AvPlay::HIADP_MCE_Exit(HI_VOID)
{
#ifndef ANDROID
    HI_S32 ret;
    HI_UNF_MCE_STOPPARM_S stStop;

    ret = HI_UNF_MCE_Init(HI_NULL);

    if (HI_SUCCESS != ret)
    {
        WVLOGE("call HI_UNF_MCE_Init failed, ret=%#x!\n", ret);
        return ret;
    }

    ret = HI_UNF_MCE_ClearLogo();

    if (HI_SUCCESS != ret)
    {
        WVLOGE("call HI_UNF_MCE_ClearLogo failed, ret=%#x!\n", ret);
        return ret;
    }

    stStop.enStopMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    stStop.enCtrlMode = HI_UNF_MCE_PLAYCTRL_BY_TIME;
    stStop.u32PlayTimeMs = 0;
    ret = HI_UNF_MCE_Stop(&stStop);

    if (HI_SUCCESS != ret)
    {
        WVLOGE("call HI_UNF_MCE_Stop failed, ret=%#x!\n", ret);
        return ret;
    }

    ret = HI_UNF_MCE_Exit(HI_NULL);

    if (HI_SUCCESS != ret)
    {
        WVLOGE("call HI_UNF_MCE_Exit failed, ret=%#x!\n", ret);
        return ret;
    }

    HI_UNF_MCE_DeInit();
#endif
    return HI_SUCCESS;
}

HI_S32 AvPlay::AvPlayOpen(HI_HANDLE* ohAVHandle, HI_HANDLE* ohWin)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_AVPLAY_ATTR_S      stAttr;
    HI_UNF_SYNC_ATTR_S        SyncAttr;
    HI_HANDLE                 hTrack;
    HI_U32                    AdecType = 0;
    HI_HA_DECODEMODE_E        enAudioDecMode = HD_DEC_MODE_RAWPCM;
    HI_S32                    s32DtsDtsCoreOnly = 0;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;
    HI_UNF_AVPLAY_TVP_ATTR_S  stAvTVPAttr;
    HI_UNF_AVPLAY_STOP_OPT_S  Stop;
    HI_HANDLE                 AVPlayHandle;
    HI_HANDLE                 hWin;

    WVLOGD("Enter AvPlayOpen\n");
    // 2. Create AVPlayer
    ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_GetDefaultConfig failed.\n");
        return HI_FAILURE;
    }

    //Get Param from Hiplayer
    stAttr.stStreamAttr.u32AudBufSize = AVPLAY_AUDIO_BUFF_SIZE;
    stAttr.stStreamAttr.u32VidBufSize = AVPLAY_VIDEO_BUFF_SIZE;

    ret = HI_UNF_AVPLAY_Create(&stAttr, &AVPlayHandle);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_Create failed.\n");
        return HI_FAILURE;
    }

    // 3. Register Callback Func
    ret |= HI_UNF_AVPLAY_RegisterEvent(AVPlayHandle, HI_UNF_AVPLAY_EVENT_STOP, TsPlayerEventHandler);
    ret |= HI_UNF_AVPLAY_RegisterEvent(AVPlayHandle, HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME, TsPlayerEventHandler);
    ret |= HI_UNF_AVPLAY_RegisterEvent(AVPlayHandle, HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME, TsPlayerEventHandler);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_RegisterEvent failed.\n");
        HI_UNF_AVPLAY_Destroy(AVPlayHandle);
        return HI_FAILURE;
    }

    // 4. Set Sync mode
    ret = HI_UNF_AVPLAY_GetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_GetAttr failed.\n");
        HI_UNF_AVPLAY_Destroy(AVPlayHandle);
        return HI_FAILURE;
    }

    //SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    ret = HI_UNF_AVPLAY_SetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_SetAttr failed.\n");
        HI_UNF_AVPLAY_Destroy(AVPlayHandle);
        return HI_FAILURE;
    }

    // 5. Start Audio Play
    ret = HI_UNF_AVPLAY_ChnOpen(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call audio HI_UNF_AVPLAY_ChnOpen failed.\n");
        Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
        Stop.u32TimeoutMs = 0;
        HI_UNF_AVPLAY_Stop(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &Stop);
        return HI_FAILURE;
    }

    ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        HI_UNF_AVPLAY_ChnClose(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        return HI_FAILURE;
    }

    ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_SND_CreateTrack failed.\n");
        HI_UNF_AVPLAY_ChnClose(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        return HI_FAILURE;
    }

    ret = HI_UNF_SND_Attach(hTrack, AVPlayHandle);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_SND_Attach failed.\n");
        HI_UNF_SND_DestroyTrack(hTrack);
        return HI_FAILURE;
    }

    ret = HI_UNF_SND_SetTrackMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, HI_UNF_TRACK_MODE_DOUBLE_MONO);

    if (ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_SetTrackMode failed.\n");
        HI_UNF_SND_DestroyTrack(hTrack);
        HI_UNF_AVPLAY_ChnClose(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        return HI_FAILURE;
    }

    ret = HIADP_AVPlay_SetAdecAttr(AVPlayHandle, HA_AUDIO_ID_AAC, HD_DEC_MODE_RAWPCM, s32DtsDtsCoreOnly);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_SetAttr failed.\n");
        HI_UNF_SND_Detach(hTrack, AVPlayHandle);
        return HI_FAILURE;
    }

    ret = HI_UNF_AVPLAY_Start(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_Start failed.\n");
        return HI_FAILURE;
    }
#if 1
    // Enable TVP attribute
    stAvTVPAttr.bEnable = HI_TRUE;
    ret = HI_UNF_AVPLAY_SetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_TVP, &stAvTVPAttr);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("set tvp error\n");
        HI_UNF_AVPLAY_Destroy(AVPlayHandle);
        return HI_FAILURE;
    }
#endif
    // 6. VO window create
    ret = HIADP_VO_CreatWin(HI_NULL, &hWin);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HIADP_VO_CreatWin failed.\n");
        HI_UNF_AVPLAY_Destroy(AVPlayHandle);
        return HI_FAILURE;
    }

    // 8. Start Video Play
    ret = HI_UNF_AVPLAY_ChnOpen(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        HI_UNF_VO_DestroyWindow(hWin);
        return HI_FAILURE;
    }

    HI_UNF_VCODEC_ATTR_S VcodecAttr;
    ret = HI_UNF_AVPLAY_GetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VcodecAttr);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_SetAttr failed.\n");
        HI_UNF_AVPLAY_Destroy(AVPlayHandle);
        return HI_FAILURE;
    }

    VcodecAttr.enType = HI_UNF_VCODEC_TYPE_H264;

    ret = HI_UNF_AVPLAY_SetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VcodecAttr);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_SetAttr failed.\n");
        HI_UNF_AVPLAY_Destroy(AVPlayHandle);
        return HI_FAILURE;
    }

    ret = HI_UNF_VO_AttachWindow(hWin, AVPlayHandle);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_VO_AttachWindow failed.\n");
        HI_UNF_AVPLAY_ChnClose(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        return HI_FAILURE;
    }

    ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_VO_SetWindowEnable failed.\n");
        HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(hWin, AVPlayHandle);
        return HI_FAILURE;
    }

    ret = HI_UNF_AVPLAY_Start(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_Start failed.\n");
        HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(hWin, AVPlayHandle);
        return HI_FAILURE;
    }

    *ohAVHandle = AVPlayHandle;
    *ohWin = hWin;

    WVLOGD("AVPlayHandle IN AvPlayOpen:0x%x\n", AVPlayHandle);
    return HI_SUCCESS;
}

HI_S32 AvPlay::StartAvPlay()
{
    HI_S32 ret;
    HI_UNF_ENC_FMT_E enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_UNF_DISP_BG_COLOR_S BgColor;

    WVLOGD("Enter StartAvPlay.\n");
    HI_SYS_Init();

    if (HIADP_MCE_Exit() != HI_SUCCESS)
    {
        WVLOGE("hide hisilicon image fail");
    }

    ret = HI_UNF_AVPLAY_Init();

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_Init failed.\n");
        HI_SYS_DeInit();
        return HI_FAILURE;
    }

    ret = HIADP_Disp_Init(enFormat);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call DispInit failed.\n");
        HI_UNF_AVPLAY_DeInit();
        return HI_FAILURE;
    }

    BgColor.u8Red   = 0;
    BgColor.u8Green = 200;
    BgColor.u8Blue  = 200;
    HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY0, &BgColor);
    ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        HIADP_Disp_DeInit();
        HI_UNF_AVPLAY_DeInit();
        return HI_FAILURE;
    }

    ret = HIADP_Snd_Init();

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call SndInit failed.\n");
        HIADP_VO_DeInit();
        return HI_FAILURE;
    }

    ret = HIADP_AVPlay_RegADecLib();

    if (ret != HI_SUCCESS)
    {
        WVLOGE("call HI_UNF_AVPLAY_RegisterAcodecLib failed.\n");
        HIADP_Snd_DeInit();
        return HI_FAILURE;
    }

    return AvPlayOpen(&hAVPlay, &hWin);
}

HI_S32 AvPlay::GetAvPlayVideoBuffer(IN HI_U8* buffer, IN HI_U32 buffer_len, INOUT HI_U8*& out_buffer)
{
    HI_S32 ret;

    CHK_ARG(buffer != NULL);
    CHK_ARG(buffer_len != 0);

    //Get ES buffer from ES, if we can get it, input!
    ret = HI_UNF_AVPLAY_GetBuf(hAVPlay, HI_UNF_AVPLAY_BUF_ID_ES_VID, buffer_len, &video_stream_buf, 0);

    if (ret != HI_SUCCESS)
    {
        if (HI_ERR_VDEC_BUFFER_FULL == ret)
        {
            WVLOGE("VDec full\n");
        }

        return HI_FAILURE;
    }

    WVLOGD("In GetAvPlayVideoBuffer StreamBuf.pu8Data:0x%x, length:%d\n", video_stream_buf.pu8Data, buffer_len);

    // for test, non TVP
    //memcpy(video_stream_buf.pu8Data, buffer, buffer_len);

    out_buffer = video_stream_buf.pu8Data;

    return HI_SUCCESS;
}

HI_S32 AvPlay::PutDataToAvplayVideobuffer(IN HI_U32 buffer_len)
{
    CHK_ARG(buffer_len != 0);

    WVLOGD("IN PutDataToAvplayVideobuffe,buffer_len:%d\n", buffer_len);
    return HI_UNF_AVPLAY_PutBuf(hAVPlay, HI_UNF_AVPLAY_BUF_ID_ES_VID, buffer_len, 0);
}

HI_S32 AvPlay::GetAvPlayAudioBuffer(IN HI_U8* buffer, IN HI_U32 buffer_len, INOUT HI_U8*& out_buffer)
{
    HI_S32 ret;
    // In the case of MP4 demux, the ADTS head is removed, so we need add it when we want to play es stream.
    HI_U32 audio_buffer_len_with_adts = buffer_len + ADTS_HEAD_LEN;
    uint8_t adtsHead[ADTS_HEAD_LEN] = {0xff,0xf1,0x00,0x00,0x00,0x1f,0xfc};
    int profile = 2; // AAC LC
    int freqIdx = 4; // 44.1KHz
    int chanCfg = 2; // CPE

    CHK_ARG(buffer != NULL);
    CHK_ARG(buffer_len != 0);

    ret = HI_UNF_AVPLAY_GetBuf(hAVPlay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, audio_buffer_len_with_adts, &audio_stream_buf, 0);

    if (ret != HI_SUCCESS)
    {
        if (HI_ERR_VDEC_BUFFER_FULL == ret)
        {
            WVLOGE("ADec full\n");
        }

        return HI_FAILURE;
    }

    // ADTS head value calculation.
    adtsHead[2] = ((profile - 1) << 6) + (freqIdx << 2) +(chanCfg >> 2);
    adtsHead[3] = ((chanCfg & 3) << 6) + (audio_buffer_len_with_adts >> 11);
    adtsHead[4] |= ((audio_buffer_len_with_adts & 0x7FF) >> 3);
    adtsHead[5] |= ((audio_buffer_len_with_adts & 0x7) << 5);

    WVLOGD("In GetAvPlayAudioBuffer audio_stream_buf.pu8Data:0x%x, audio_buffer_len_with_adts:%d\n", audio_stream_buf.pu8Data, audio_buffer_len_with_adts);

    memcpy(audio_stream_buf.pu8Data, adtsHead, ADTS_HEAD_LEN);
    memcpy(audio_stream_buf.pu8Data + ADTS_HEAD_LEN, buffer, buffer_len);

    out_buffer = audio_stream_buf.pu8Data + ADTS_HEAD_LEN;

    return HI_SUCCESS;
}

HI_S32 AvPlay::PutDataToAvplayAudiobuffer(IN HI_U32 buffer_len)
{
    CHK_ARG(buffer_len != 0);

    HI_U32 audio_buffer_len_with_adts = buffer_len + ADTS_HEAD_LEN;
    WVLOGD("IN PutDataToAvplayAudiobuffer, audio_buffer_len_with_adts:%d\n", audio_buffer_len_with_adts);
    return HI_UNF_AVPLAY_PutBuf(hAVPlay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, audio_buffer_len_with_adts, 0);
}

