
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_hdmi.h"
#include "hi_unf_aenc.h"
#include "hi_unf_venc.h"
#include "hi_error_mpi.h"

#include "HA.AUDIO.AAC.encode.h"

#include "hi_demux.h"
#include "hi_play.h"
#include "hi_transcode.h"

#define MAX_FILENAME_LEN        256

#define TRANSCODE_VO_WIDTH      1280 //1920
#define TRANSCODE_VO_HEIGHT     720 //1080

#define MAX_VID_FILE_SIZE       (400 * 1024 * 1024)
#define MAX_AUD_FILE_SIZE       (36 * 1024 * 1024)

//#define SAVE_TO_FILE

typedef struct
{
    pthread_t   ThreadId;
    HI_S32      ThreadRunFlag;
    HI_CHAR     FileName[MAX_FILENAME_LEN];
    HI_HANDLE   AencHandle;
    HI_HANDLE   AudHandle;
} AudioAencInfo;

typedef struct
{
    pthread_t   ThreadId;
    HI_S32      ThreadRunFlag;
    HI_CHAR     FileName[MAX_FILENAME_LEN];
    HI_HANDLE   VencHandle;
    HI_HANDLE   VidHandle;
} VideoVencInfo;

typedef struct
{
    HI_U32          PlayId;
    HI_HANDLE       Avplay;
    HI_HANDLE       Window;
    AudioAencInfo   AencInfo;
    VideoVencInfo   VencInfo;
} HiTranscodeInfo;

typedef struct
{
    AudioAencInfo   AencInfo;
    VideoVencInfo   VencInfo;
} HiCastInfo;

static HiTranscodeInfo  TranscodeInfo[HI_TRANSCODE_COUNT];
static HiCastInfo       CastInfo;

static HI_VOID* AudioDataProcess(HI_VOID* arg)
{
    HI_S32          ret;
    AudioAencInfo  *AudInfo = (AudioAencInfo*)arg;
    FILE           *AudFp   = HI_NULL;
#ifdef SAVE_TO_FILE
    HI_U32          Size    = 0;

    AudFp = fopen(AudInfo->FileName, "wb");
    if (!AudFp)
    {
        printf("[%s] can't open %s\n", __FUNCTION__, AudInfo->FileName);

        return HI_NULL;
    }

    printf("[%s] open %s\n", __FUNCTION__, AudInfo->FileName);
#endif
    while (HI_THREAD_EXIT != AudInfo->ThreadRunFlag)
    {
        HI_UNF_ES_BUF_S AudEsBuf;

        if (HI_THREAD_SLEEP == AudInfo->ThreadRunFlag)
        {
            usleep(10 * 1000);

            continue;
        }

        usleep(10 * 1000);

        ret = HI_UNF_AENC_AcquireStream(AudInfo->AencHandle, &AudEsBuf, 0);
        if ((HI_SUCCESS == ret) && (AudEsBuf.u32BufLen > 0))
        {
        #ifdef SAVE_TO_FILE
            ret = fwrite(AudEsBuf.pu8Buf, 1, AudEsBuf.u32BufLen, AudFp);
            if (ret < 0)
            {
                perror("[AudioDataProcess] fwrite error");

                AudInfo->ThreadRunFlag = HI_THREAD_EXIT;
            }
            else if (ret < AudEsBuf.u32BufLen)
            {
                printf("[%s] fwrite failed ret=%d, len=%u\n", __FUNCTION__, ret, AudEsBuf.u32BufLen);
            }
            else
            {
                Size += ret;
                if (Size > MAX_AUD_FILE_SIZE)
                {
                    Size = 0;

                    fseek(AudFp, 0, SEEK_SET);
                }
            }
        #endif
            ret = HI_UNF_AENC_ReleaseStream(AudInfo->AencHandle, &AudEsBuf);
            if (HI_SUCCESS != ret)
            {
                printf("[%s] HI_UNF_AENC_ReleaseStream failed 0x%x\n", __FUNCTION__, ret);
            }
        }
    }

    if (AudFp)
    {
        fclose(AudFp);
    }

    return HI_NULL;
}

static HI_S32 AudioTranscodeStart(HiTranscodeInfo *Transcode)
{
    HI_S32                      ret;
    HI_HANDLE                   SndTrackHandle;
    HI_UNF_AUDIOTRACK_ATTR_S    SndTrackAttr;
    HI_HANDLE                   AencHandle;
    AAC_ENC_CONFIG              AacEncCfg;
    HI_UNF_AENC_ATTR_S          AencAttr;

    ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_VIRTUAL, &SndTrackAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_SND_GetDefaultTrackAttr failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    SndTrackAttr.u32OutputBufSize = 256 * 1024;

    ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &SndTrackAttr, &SndTrackHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_SND_CreateTrack failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_SND_Attach(SndTrackHandle, Transcode->Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_SND_Attach failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    AencAttr.enAencType = HA_AUDIO_ID_AAC;

    HA_AAC_GetDefaultConfig(&AacEncCfg);

    HA_AAC_GetEncDefaultOpenParam(&AencAttr.sOpenParam, &AacEncCfg);

    ret = HI_UNF_AENC_Create(&AencAttr, &AencHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_Create failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_AENC_AttachInput(AencHandle, SndTrackHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_AttachInput failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_AENC_Start(AencHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_Start failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    Transcode->AencInfo.ThreadRunFlag   = HI_THREAD_RUNNING;
    Transcode->AencInfo.AencHandle      = AencHandle;
    Transcode->AencInfo.AudHandle       = SndTrackHandle;

    ret = pthread_create(&Transcode->AencInfo.ThreadId, HI_NULL, AudioDataProcess, (HI_VOID*)&Transcode->AencInfo);
    if (0 != ret)
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 AudioTranscodeStop(HiTranscodeInfo *Transcode)
{
    HI_S32 ret;

    if (0 != Transcode->AencInfo.ThreadId)
    {
        Transcode->AencInfo.ThreadRunFlag = HI_THREAD_EXIT;
        pthread_join(Transcode->AencInfo.ThreadId, HI_NULL);

        Transcode->AencInfo.ThreadId = 0;
    }

    if (HI_INVALID_HANDLE != Transcode->AencInfo.AencHandle)
    {
        ret = HI_UNF_AENC_Stop(Transcode->AencInfo.AencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_AENC_Stop failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_AENC_DetachInput(Transcode->AencInfo.AencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_AENC_AttachInput failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_AENC_Destroy(Transcode->AencInfo.AencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_AENC_Destroy failed 0x%x\n", __FUNCTION__, ret);
        }

        Transcode->AencInfo.AencHandle = HI_INVALID_HANDLE;
    }

    if (HI_INVALID_HANDLE != Transcode->AencInfo.AudHandle)
    {
        ret = HI_UNF_SND_Detach(Transcode->AencInfo.AudHandle, Transcode->Avplay);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_SND_Detach failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_SND_DestroyTrack(Transcode->AencInfo.AudHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_SND_DestroyTrack failed 0x%x\n", __FUNCTION__, ret);
        }

        Transcode->AencInfo.AudHandle = HI_INVALID_HANDLE;
    }

    return 0;
}

static HI_VOID* AudioCastProcess(HI_VOID* arg)
{
    HI_S32          ret;
    AudioAencInfo  *AudInfo = (AudioAencInfo*)arg;
    FILE           *AudFp   = HI_NULL;
#ifdef SAVE_TO_FILE
    HI_U32          Size    = 0;

    AudFp = fopen(AudInfo->FileName, "wb");
    if (!AudFp)
    {
        printf("[%s] can't open %s\n", __FUNCTION__, AudInfo->FileName);

        return HI_NULL;
    }

    printf("[%s] open %s\n", __FUNCTION__, AudInfo->FileName);
#endif
    while (HI_THREAD_EXIT != AudInfo->ThreadRunFlag)
    {
        HI_UNF_ES_BUF_S AudEsBuf;

        if (HI_THREAD_SLEEP == AudInfo->ThreadRunFlag)
        {
            usleep(10 * 1000);

            continue;
        }

        usleep(10 * 1000);

        ret = HI_UNF_AENC_AcquireStream(AudInfo->AencHandle, &AudEsBuf, 0);
        if ((HI_SUCCESS == ret) && (AudEsBuf.u32BufLen > 0))
        {
        #ifdef SAVE_TO_FILE
            ret = fwrite(AudEsBuf.pu8Buf, 1, AudEsBuf.u32BufLen, AudFp);
            if (ret < 0)
            {
                perror("[AudioCastProcess] fwrite error");

                AudInfo->ThreadRunFlag = HI_THREAD_EXIT;
            }
            else if (ret < AudEsBuf.u32BufLen)
            {
                printf("[%s] fwrite failed ret=%d, len=%u\n", __FUNCTION__, ret, AudEsBuf.u32BufLen);
            }
            else
            {
                Size += ret;
                if (Size > MAX_AUD_FILE_SIZE)
                {
                    Size = 0;

                    fseek(AudFp, 0, SEEK_SET);
                }
            }
        #endif
            ret = HI_UNF_AENC_ReleaseStream(AudInfo->AencHandle, &AudEsBuf);
            if (HI_SUCCESS != ret)
            {
                printf("[%s] HI_UNF_AENC_ReleaseStream failed 0x%x\n", __FUNCTION__, ret);
            }
        }
    }

    if (AudFp)
    {
        fclose(AudFp);
    }

    return HI_NULL;
}

static HI_S32 AudioCastStart(AudioAencInfo *AencInfo)
{
    HI_S32                  ret;
    HI_UNF_SND_CAST_ATTR_S  CastAttr;
    HI_UNF_AENC_ATTR_S      AencAttr;
    AAC_ENC_CONFIG          AacEncCfg;
    HI_HANDLE               AudCast;
    HI_HANDLE               AencHandle;

    ret = HI_UNF_SND_GetDefaultCastAttr(HI_UNF_SND_0, &CastAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_SND_GetDefaultCastAttr failed 0x%x\n", __FUNCTION__, ret);

        return ret;
    }

    ret = HI_UNF_SND_CreateCast(HI_UNF_SND_0, &CastAttr, &AudCast);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_SND_CreateCast failed 0x%x\n", __FUNCTION__, ret);

        return ret;
    }

    AencAttr.enAencType = HA_AUDIO_ID_AAC;

    HA_AAC_GetDefaultConfig(&AacEncCfg);

    HA_AAC_GetEncDefaultOpenParam(&AencAttr.sOpenParam, &AacEncCfg);

    ret = HI_UNF_AENC_Create(&AencAttr, &AencHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_Create failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_AENC_AttachInput(AencHandle, AudCast);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_AttachInput failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_AENC_Start(AencHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_Start failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_SND_SetCastEnable(AudCast, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_SND_SetCastEnable failed 0x%x\n", __FUNCTION__, ret);

        return ret;
    }

    AencInfo->ThreadRunFlag = HI_THREAD_RUNNING;
    AencInfo->AencHandle    = AencHandle;
    AencInfo->AudHandle     = AudCast;

    ret = pthread_create(&AencInfo->ThreadId, HI_NULL, AudioCastProcess, (HI_VOID*)AencInfo);
    if (0 != ret)
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID AudioCastStop(AudioAencInfo *AencInfo)
{
    HI_S32 ret;

    if (0 != AencInfo->ThreadId)
    {
        AencInfo->ThreadRunFlag = HI_THREAD_EXIT;
        pthread_join(AencInfo->ThreadId, HI_NULL);

        AencInfo->ThreadId = 0;
    }

    if (HI_INVALID_HANDLE != AencInfo->AudHandle)
    {
        ret = HI_UNF_SND_SetCastEnable(AencInfo->AudHandle, HI_FALSE);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_SND_SetCastEnable failed 0x%x\n", __FUNCTION__, ret);
        }
    }

    if (HI_INVALID_HANDLE != AencInfo->AencHandle)
    {
        ret = HI_UNF_AENC_Stop(AencInfo->AencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_AENC_Stop failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_AENC_DetachInput(AencInfo->AencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_AENC_DetachInput failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_AENC_Destroy(AencInfo->AencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_AENC_Destroy failed 0x%x\n", __FUNCTION__, ret);
        }

        AencInfo->AencHandle = HI_INVALID_HANDLE;
    }

    if (HI_INVALID_HANDLE != AencInfo->AudHandle)
    {
        ret = HI_UNF_SND_DestroyCast(AencInfo->AudHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_SND_DestroyCast failed 0x%x\n", __FUNCTION__, ret);
        }

        AencInfo->AudHandle = HI_INVALID_HANDLE;
    }
}

static HI_VOID* VideoDataProcess(HI_VOID* arg)
{
    HI_S32          ret;
    VideoVencInfo  *VidInfo = (VideoVencInfo*)arg;
    FILE           *VidFp   = HI_NULL;
#ifdef SAVE_TO_FILE
    HI_U32          Size    = 0;
    HI_U8          *buf;
    HI_U32          len;

    VidFp = fopen(VidInfo->FileName, "wb");
    if (!VidFp)
    {
        printf("[%s] can't open %s\n", __FUNCTION__, VidInfo->FileName);

        return HI_NULL;
    }

    printf("[%s] open %s\n", __FUNCTION__, VidInfo->FileName);
#endif
    while (HI_THREAD_EXIT != VidInfo->ThreadRunFlag)
    {
        HI_UNF_VENC_STREAM_S    VencStream;

        if (HI_THREAD_SLEEP == VidInfo->ThreadRunFlag)
        {
            usleep(10 * 1000);

            continue;
        }

        usleep(10 * 1000);

        ret = HI_UNF_VENC_AcquireStream(VidInfo->VencHandle, &VencStream, 0);
        if ((HI_SUCCESS != ret) || (0 == VencStream.u32SlcLen))
        {
            if (HI_ERR_VENC_BUF_EMPTY != ret)
            {
                printf("[%s] HI_UNF_VENC_AcquireStream failed 0x%x\n", __FUNCTION__, ret);
            }

            continue;
        }
#ifdef SAVE_TO_FILE
        buf = VencStream.pu8Addr;
        len = VencStream.u32SlcLen;

        do
        {
            ret = fwrite(buf, 1, len, VidFp);
            if (ret <= 0)
            {
                perror("[VideoDataProcess] fwrite error");

                printf("[%s] write failed, buf=%p, len=%u\n", __FUNCTION__, buf, len);

                VidInfo->ThreadRunFlag = HI_THREAD_EXIT;

                break;
            }
            else
            {
                buf += ret;
                len -= ret;

                Size += ret;
                if (Size > MAX_VID_FILE_SIZE)
                {
                    Size = 0;

                    fseek(VidFp, 0, SEEK_SET);
                }
            }
        } while (len);
    #endif
        ret = HI_UNF_VENC_ReleaseStream(VidInfo->VencHandle, &VencStream);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_ReleaseStream failed 0x%x\n", __FUNCTION__, ret);
        }
    }

    if (VidFp)
    {
        fclose(VidFp);
    }

    return HI_NULL;
}

static HI_S32 VideoTranscodeStart(HiTranscodeInfo *Transcode)
{
    HI_S32                  ret;
    HI_HANDLE               Window;
    HI_HANDLE               VencHandle;
    HI_UNF_WINDOW_ATTR_S    WinAttr = {0};
    HI_UNF_VENC_CHN_ATTR_S  VencAttr;

    WinAttr.enDisp          = HI_UNF_DISPLAY0;
    WinAttr.bVirtual        = HI_TRUE;
    WinAttr.enVideoFormat   = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
    WinAttr.bUseCropRect    = HI_FALSE;

    WinAttr.stWinAspectAttr.enAspectCvrs        = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;

    ret = HI_UNF_VO_CreateWindow(&WinAttr, &Window);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_CreateWindow failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    Transcode->Window = Window;

    ret = HI_UNF_VO_AttachWindow(Window, Transcode->Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_AttachWindow failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_VENC_GetDefaultAttr(&VencAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_GetDefaultAttr failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    VencAttr.enVencType         = HI_UNF_VCODEC_TYPE_H264;
    VencAttr.enCapLevel         = HI_UNF_VCODEC_CAP_LEVEL_720P;//HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    VencAttr.u32Width           = TRANSCODE_VO_WIDTH;
    VencAttr.u32Height          = TRANSCODE_VO_HEIGHT;
    VencAttr.u32TargetBitRate   = 5 * 1024 * 1024;  //目标码率要和实际的编码分辨率配套，不然可能会引起一些异常处理，参考目标码率:D1以下:1768*1024或以下,720P:3*1024*1024,1080P:5*1024*1024
    VencAttr.u32InputFrmRate    = 60;
    VencAttr.u32TargetFrmRate   = 60;
    VencAttr.u32StrmBufSize     = TRANSCODE_VO_WIDTH * TRANSCODE_VO_HEIGHT * 4;

    ret = HI_UNF_VENC_Create(&VencHandle, &VencAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_Create failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_VENC_AttachInput(VencHandle, Window);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_AttachInput failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_VO_SetWindowEnable(Window, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_SetWindowEnable failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_VENC_Start(VencHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_Start failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    Transcode->VencInfo.ThreadRunFlag   = HI_THREAD_RUNNING;
    Transcode->VencInfo.VencHandle      = VencHandle;
    Transcode->VencInfo.VidHandle       = HI_INVALID_HANDLE;

    ret = pthread_create(&Transcode->VencInfo.ThreadId, HI_NULL, VideoDataProcess, (HI_VOID*)&Transcode->VencInfo);
    if (0 != ret)
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    return 0;
}

static HI_VOID VideoTranscodeStop(HiTranscodeInfo *Transcode)
{
    HI_S32 ret;

    if (0 != Transcode->VencInfo.ThreadId)
    {
        Transcode->VencInfo.ThreadRunFlag = HI_THREAD_EXIT;
        pthread_join(Transcode->VencInfo.ThreadId, HI_NULL);

        Transcode->VencInfo.ThreadId = 0;
    }

    if (HI_INVALID_HANDLE != Transcode->VencInfo.VencHandle)
    {
        ret = HI_UNF_VENC_Stop(Transcode->VencInfo.VencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_Stop failed 0x%x\n", __FUNCTION__, ret);
        }
        ret = HI_UNF_VO_SetWindowEnable(Transcode->Window, HI_FALSE);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VO_SetWindowEnable failed 0x%x\n", __FUNCTION__, ret);
        }
        ret = HI_UNF_VO_DetachWindow(Transcode->Window, Transcode->Avplay);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VO_SetWindowEnable failed 0x%x\n", __FUNCTION__, ret);
        }
        ret = HI_UNF_VENC_DetachInput(Transcode->VencInfo.VencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_DetachInput failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_VENC_Destroy(Transcode->VencInfo.VencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_Destroy failed 0x%x\n", __FUNCTION__, ret);
        }

        Transcode->VencInfo.VencHandle = HI_INVALID_HANDLE;
    }

    if (HI_INVALID_HANDLE != Transcode->Window)
    {
        ret = HI_UNF_VO_DestroyWindow(Transcode->Window);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_VO_DestroyWindow failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        }

        Transcode->Window = HI_INVALID_HANDLE;
    }
}

static HI_VOID* VideoCastProcess(HI_VOID* arg)
{
    HI_S32          ret;
    VideoVencInfo  *VidInfo = (VideoVencInfo*)arg;
    FILE           *VidFp   = HI_NULL;
#ifdef SAVE_TO_FILE
    HI_U32          Size    = 0;
    HI_U8          *buf;
    HI_U32          len;

    VidFp = fopen(VidInfo->FileName, "wb");
    if (!VidFp)
    {
        printf("[%s] can't open %s\n", __FUNCTION__, VidInfo->FileName);

        return HI_NULL;
    }

    printf("[%s] open %s\n", __FUNCTION__, VidInfo->FileName);
#endif
    while (HI_THREAD_EXIT != VidInfo->ThreadRunFlag)
    {
        HI_UNF_VENC_STREAM_S    VencStream;

        if (HI_THREAD_SLEEP == VidInfo->ThreadRunFlag)
        {
            usleep(10 * 1000);

            continue;
        }

        usleep(20 * 1000);

        ret = HI_UNF_VENC_AcquireStream(VidInfo->VencHandle, &VencStream, 0);
        if ((HI_SUCCESS != ret) || (0 == VencStream.u32SlcLen))
        {
            if (HI_ERR_VENC_BUF_EMPTY != ret)
            {
                printf("[%s] HI_UNF_VENC_AcquireStream failed 0x%x\n", __FUNCTION__, ret);
            }

            continue;
        }
#ifdef SAVE_TO_FILE
        buf = VencStream.pu8Addr;
        len = VencStream.u32SlcLen;

        do
        {
            ret = fwrite(buf, 1, len, VidFp);
            if (ret <= 0)
            {
                perror("[VideoCastProcess] fwrite error");

                printf("[%s] write failed, buf=%p, len=%u\n", __FUNCTION__, buf, len);

                VidInfo->ThreadRunFlag = HI_THREAD_EXIT;

                break;
            }
            else
            {
                buf += ret;
                len -= ret;

                Size += ret;
                if (Size > MAX_VID_FILE_SIZE)
                {
                    Size = 0;

                    fseek(VidFp, 0, SEEK_SET);
                }
            }
        } while (len);
    #endif
        ret = HI_UNF_VENC_ReleaseStream(VidInfo->VencHandle, &VencStream);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_ReleaseStream failed 0x%x\n", __FUNCTION__, ret);
        }
    }

    if (VidFp)
    {
        fclose(VidFp);
    }

    return HI_NULL;
}

static HI_S32 VideoCastStart(VideoVencInfo *VencInfo)
{
    HI_S32                  ret;
    HI_HANDLE               VencHandle;
    HI_UNF_VENC_CHN_ATTR_S  VencAttr;
    HI_HANDLE               VidHandle;
    HI_UNF_DISP_CAST_ATTR_S DispCastCfg = {0};

    ret = HI_UNF_DISP_GetDefaultCastAttr(HI_UNF_DISPLAY1, &DispCastCfg);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DISP_GetDefaultCastAttr failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    DispCastCfg.u32Width    = TRANSCODE_VO_WIDTH;
    DispCastCfg.u32Height   = TRANSCODE_VO_HEIGHT;

    ret = HI_UNF_DISP_CreateCast(HI_UNF_DISPLAY1, &DispCastCfg, &VidHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DISP_CreateCast failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_VENC_GetDefaultAttr(&VencAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_GetDefaultAttr failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    VencAttr.enVencType         = HI_UNF_VCODEC_TYPE_H264;
    VencAttr.enCapLevel         = HI_UNF_VCODEC_CAP_LEVEL_720P;
    VencAttr.u32Width           = TRANSCODE_VO_WIDTH;
    VencAttr.u32Height          = TRANSCODE_VO_HEIGHT;
    VencAttr.u32TargetBitRate   = 4 * 1024 * 1024;
    VencAttr.u32InputFrmRate    = 30;
    VencAttr.u32TargetFrmRate   = 30;
    VencAttr.u32StrmBufSize     = TRANSCODE_VO_WIDTH * TRANSCODE_VO_HEIGHT * 4;

    ret = HI_UNF_VENC_Create(&VencHandle, &VencAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_Create failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_VENC_AttachInput(VencHandle, VidHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_AttachInput failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_DISP_SetCastEnable(VidHandle, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DISP_SetCastEnable failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_VENC_Start(VencHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_Start failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    VencInfo->ThreadRunFlag = HI_THREAD_RUNNING;
    VencInfo->VencHandle    = VencHandle;
    VencInfo->VidHandle     = VidHandle;

    ret = pthread_create(&VencInfo->ThreadId, HI_NULL, VideoCastProcess, (HI_VOID*)VencInfo);
    if (0 != ret)
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    return 0;
}

static HI_VOID VideoCastStop(VideoVencInfo *VencInfo)
{
    HI_S32 ret;

    if (0 != VencInfo->ThreadId)
    {
        VencInfo->ThreadRunFlag = HI_THREAD_EXIT;
        pthread_join(VencInfo->ThreadId, HI_NULL);

        VencInfo->ThreadId = 0;
    }

    if (HI_INVALID_HANDLE != VencInfo->VencHandle)
    {
        ret = HI_UNF_VENC_Stop(VencInfo->VencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_Stop failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_VENC_DetachInput(VencInfo->VencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_DetachInput failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_VENC_Destroy(VencInfo->VencHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_VENC_Destroy failed 0x%x\n", __FUNCTION__, ret);
        }

        VencInfo->VencHandle = HI_INVALID_HANDLE;
    }

    if (HI_INVALID_HANDLE != VencInfo->VidHandle)
    {
        ret = HI_UNF_DISP_SetCastEnable(VencInfo->VidHandle, HI_FALSE);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DISP_SetCastEnable failed 0x%x\n", __FUNCTION__, ret);
        }

        ret = HI_UNF_DISP_DestroyCast(VencInfo->VidHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DISP_DestroyCast failed 0x%x\n", __FUNCTION__, ret);
        }

        VencInfo->VidHandle = HI_INVALID_HANDLE;
    }
}

HI_S32 HiTranscodeStart(HI_U32 PlayId, HI_CHAR *VidFile, HI_CHAR *AudFile)
{
    HI_S32              ret;
    HiTranscodeInfo    *Transcode   = HI_NULL;
    HI_HANDLE           Avplay;
    HI_U32              i;

    ret = HiPlayGetInfo(PlayId, &Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] PlayId=%u\n", __FUNCTION__, PlayId);

        return HI_FAILURE;
    }

    if (!VidFile && !AudFile)
    {
        printf("[%s - %u] VidFile and AudFile is null\n", __FUNCTION__, __LINE__);

        return HI_FAILURE;
    }

    if (VidFile)
    {
        if (strlen(VidFile) >= MAX_FILENAME_LEN)
        {
            printf("[%s - %u] video filename too long\n", __FUNCTION__, __LINE__);

            return HI_FAILURE;
        }
    }

    if (AudFile)
    {
        if (strlen(AudFile) >= MAX_FILENAME_LEN)
        {
            printf("[%s - %u] audio filename too long\n", __FUNCTION__, __LINE__);

            return HI_FAILURE;
        }
    }

    for (i = 0; i < HI_TRANSCODE_COUNT; i++)
    {
        if (HI_INVALID_HANDLE == TranscodeInfo[i].Avplay)
        {
            Transcode = &TranscodeInfo[i];

            Transcode->PlayId   = PlayId;
            Transcode->Avplay   = Avplay;

            break;
        }
    }

    if (HI_NULL == Transcode)
    {
        printf("[%s] no free transcode\n", __FUNCTION__);

        return HI_FAILURE;
    }

    if (VidFile)
    {
        strcpy(Transcode->VencInfo.FileName, VidFile);

        ret = VideoTranscodeStart(Transcode);
        if (HI_SUCCESS != ret)
        {
            VideoTranscodeStop(Transcode);

            return HI_FAILURE;
        }
    }

    if (AudFile)
    {
        strcpy(Transcode->AencInfo.FileName, AudFile);

        ret = AudioTranscodeStart(Transcode);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HiTranscodeStop(HI_U32 PlayId)
{
    HiTranscodeInfo    *Transcode   = HI_NULL;
    HI_U32              i;

    for (i = 0; i < HI_TRANSCODE_COUNT; i++)
    {
        if (PlayId == TranscodeInfo[i].PlayId)
        {
            Transcode = &TranscodeInfo[i];

            break;
        }
    }

    if (HI_NULL == Transcode)
    {
        return HI_SUCCESS;
    }

    VideoTranscodeStop(Transcode);

    AudioTranscodeStop(Transcode);

    Transcode->PlayId = HI_PLAY_COUNT;
    Transcode->Avplay = HI_INVALID_HANDLE;
    Transcode->Window = HI_INVALID_HANDLE;

    return HI_SUCCESS;
}

HI_S32 HiTransCastStart(HI_CHAR *VidFile, HI_CHAR *AudFile)
{
    HI_S32  ret;

    if (!VidFile && !AudFile)
    {
        printf("[%s - %u] VidFile and AudFile is null\n", __FUNCTION__, __LINE__);

        return HI_FAILURE;
    }

    if (VidFile)
    {
        if (strlen(VidFile) >= MAX_FILENAME_LEN)
        {
            printf("[%s - %u] video filename too long\n", __FUNCTION__, __LINE__);

            return HI_FAILURE;
        }
    }

    if (AudFile)
    {
        if (strlen(AudFile) >= MAX_FILENAME_LEN)
        {
            printf("[%s - %u] audio filename too long\n", __FUNCTION__, __LINE__);

            return HI_FAILURE;
        }
    }

    HiTransCastStop();

    if (VidFile)
    {
        strcpy(CastInfo.VencInfo.FileName, VidFile);

        ret = VideoCastStart(&CastInfo.VencInfo);
        if (HI_SUCCESS != ret)
        {
            VideoCastStop(&CastInfo.VencInfo);

            return HI_FAILURE;
        }
    }

    if (AudFile)
    {
        strcpy(CastInfo.AencInfo.FileName, AudFile);

        ret = AudioCastStart(&CastInfo.AencInfo);
        if (HI_SUCCESS != ret)
        {
            AudioCastStop(&CastInfo.AencInfo);

            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HiTransCastStop(HI_VOID)
{
    VideoCastStop(&CastInfo.VencInfo);
    AudioCastStop(&CastInfo.AencInfo);

    return HI_SUCCESS;
}

HI_S32 HiTranscodeInit(HI_VOID)
{
    HI_S32  ret;
    HI_U32  i;

    for (i = 0; i < HI_TRANSCODE_COUNT; i++)
    {
        TranscodeInfo[i].PlayId = HI_PLAY_COUNT;
        TranscodeInfo[i].Avplay = HI_INVALID_HANDLE;
        TranscodeInfo[i].Window = HI_INVALID_HANDLE;

        TranscodeInfo[i].VencInfo.ThreadId      = 0;
        TranscodeInfo[i].VencInfo.VencHandle    = HI_INVALID_HANDLE;
        TranscodeInfo[i].VencInfo.VidHandle     = HI_INVALID_HANDLE;

        TranscodeInfo[i].AencInfo.ThreadId      = 0;
        TranscodeInfo[i].AencInfo.AencHandle    = HI_INVALID_HANDLE;
        TranscodeInfo[i].AencInfo.AudHandle     = HI_INVALID_HANDLE;
    }

    CastInfo.AencInfo.ThreadId      = 0;
    CastInfo.AencInfo.AencHandle    = HI_INVALID_HANDLE;
    CastInfo.AencInfo.AudHandle     = HI_INVALID_HANDLE;
    CastInfo.VencInfo.ThreadId      = 0;
    CastInfo.VencInfo.VencHandle    = HI_INVALID_HANDLE;
    CastInfo.VencInfo.VidHandle     = HI_INVALID_HANDLE;

    ret = HI_UNF_VENC_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_Init failed 0x%x\n", __FUNCTION__, ret);

        return -1;
    }

    ret = HI_UNF_AENC_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_Init failed 0x%x\n", __FUNCTION__, ret);

        return -1;
    }

    ret = HI_UNF_AENC_RegisterEncoder("libHA.AUDIO.AAC.encode.so");
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_RegisterEncoder failed 0x%x\n", __FUNCTION__, ret);

        return -1;
    }

    return 0;
}

HI_S32 HiTranscodeDeInit(HI_VOID)
{
    HI_S32  ret;
    HI_U32  i;

    for (i = 0; i < HI_TRANSCODE_COUNT; i++)
    {
        if (HI_INVALID_HANDLE != TranscodeInfo[i].Avplay)
        {
            HiTranscodeStop(TranscodeInfo[i].PlayId);
        }
    }

    HiTransCastStop();

    ret = HI_UNF_AENC_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_AENC_DeInit failed 0x%x\n", __FUNCTION__, ret);
    }

    ret = HI_UNF_VENC_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VENC_DeInit failed 0x%x\n", __FUNCTION__, ret);
    }

    return HI_SUCCESS;
}

