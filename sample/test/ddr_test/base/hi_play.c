
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "hi_type.h"

#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_unf_avplay.h"

#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DOLBYPLUS.decode.h"

#include "hi_psi_si.h"
#include "hi_demux.h"
#include "hi_play.h"

typedef enum
{
    HI_PLAY_MODE_NONE = 0,
    HI_PLAY_MODE_DVB,
    HI_PLAY_MODE_TS,
    HI_PLAY_MODE_IP,
    HI_PLAY_MODE_ES,
    HI_PLAY_MODE_PVR
} HI_PLAY_MODE_E;

typedef struct
{
    HI_HANDLE   Avplay;
    HI_CHAR     AudFileName[MAX_FILENAME_LEN];
    HI_CHAR     VidFileName[MAX_FILENAME_LEN];
    HI_S32      RunFlag;
} EsFileInfo;

typedef struct
{
    HI_U32  IP;
    HI_U32  Port;
    HI_U32  PortId;
    HI_U32  TsBufSize;
    HI_S32  RunFlag;
} IpPlayInfo;

typedef struct
{
    HI_U32          PlayId;
    HI_PLAY_MODE_E  PlayMode;
    HI_U32          TunerId;
    HiPmtInfo       Pmt;
    HI_HANDLE       Avplay;
    HI_HANDLE       Window;
    HI_HANDLE       Sound;
    TsFileInfo      TsFile;
    IpPlayInfo      IpInfo;
    EsFileInfo      EsFile;
    pthread_t       ThreadId;
} HiPlayInfo;

static HiPlayInfo   PlayInfo[HI_PLAY_COUNT];

static HI_S32 VidStringToEnum(HI_CHAR* Vid, HI_UNF_VCODEC_TYPE_E *VidType)
{
    HI_S32 ret = HI_SUCCESS;

    if (!strcasecmp("mpeg2", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_MPEG2;
    }
    else if (!strcasecmp("mpeg4", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_MPEG4;
    }
    else if (!strcasecmp("h263", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_H263;
    }
    else if (!strcasecmp("sor", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_SORENSON;
    }
    else if (!strcasecmp("vp6", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_VP6;
    }
    else if (!strcasecmp("vp6f", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_VP6F;
    }
    else if (!strcasecmp("vp6a", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_VP6A;
    }
    else if (!strcasecmp("h264", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_H264;
    }
    else if (!strcasecmp("h265", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_HEVC;
    }
    else if (!strcasecmp("mvc", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_MVC;
    }
    else if (!strcasecmp("avs", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_AVS;
    }
    else if (!strcasecmp("real8", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_REAL8;
    }
    else if (!strcasecmp("real9", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_REAL9;
    }
    else if (!strcasecmp("vp8", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_VP8;
    }
    else if (!strcasecmp("vp9", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_VP9;
    }        
    else if (!strcasecmp("divx3", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_DIVX3;
    }
    else if (!strcasecmp("mjpeg", Vid))
    {
        *VidType = HI_UNF_VCODEC_TYPE_MJPEG;
    }
    else
    {
        *VidType = HI_UNF_VCODEC_TYPE_BUTT;

        ret = HI_FAILURE;
    }

    return ret;
}

static HI_S32 AudStringToEnum(HI_CHAR* Aud, HI_U32 *AudType)
{
    HI_S32 ret = HI_SUCCESS;

    if (!strcasecmp("mp3", Aud))
    {
        *AudType = HA_AUDIO_ID_MP3;
    }
    else if (!strcasecmp("aac", Aud))
    {
        *AudType = HA_AUDIO_ID_AAC;
    }
    else
    {
        ret = HI_FAILURE;
    }

    return ret;
}

static HI_VOID* SocketRecvThread(HI_VOID *arg)
{
    HI_S32              ret;
    IpPlayInfo         *IpInfo  = (IpPlayInfo*)arg;
    HI_HANDLE           TsBuffer;
    HI_S32              SocketFd = -1;
    HI_S32              Flag;
    HI_U32              on;
    struct sockaddr_in  ServerAddr;
    struct ip_mreq      Mreq;

    printf("[%s] IP=0x%x, Port=%u, PortId=0x%x, BufSize=0x%x\n",
        __FUNCTION__, IpInfo->IP, IpInfo->Port, IpInfo->PortId, IpInfo->TsBufSize);

    ret = HI_UNF_DMX_CreateTSBuffer(IpInfo->PortId, IpInfo->TsBufSize, &TsBuffer);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_CreateTSBuffer failed 0x%x\n", __FUNCTION__, ret);

        return HI_NULL;
    }

    SocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (SocketFd < 0)
    {
        perror("[SocketRecvThread] socket error");

        goto exit;
    }

    on = 1;

    ret = setsockopt(SocketFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (HI_SUCCESS != ret)
    {
        printf("[%s] setsockopt SO_REUSEADDR failed\n", __FUNCTION__);

        goto exit;
    }

    Flag = fcntl(SocketFd, F_GETFL, 0);

    ret = fcntl(SocketFd, F_SETFL, Flag | O_NONBLOCK);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] fcntl failed\n", __FUNCTION__);

        goto exit;
    }

    ServerAddr.sin_family       = AF_INET;
    ServerAddr.sin_addr.s_addr  = htonl(INADDR_ANY);
    ServerAddr.sin_port         = htons(IpInfo->Port);

    ret = bind(SocketFd, (struct sockaddr*)&ServerAddr, sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("[SocketRecvThread] bind error");

        goto exit;
    }

    if (IpInfo->IP)
    {
        Mreq.imr_multiaddr.s_addr = IpInfo->IP;
        Mreq.imr_interface.s_addr = htonl(INADDR_ANY);

        ret = setsockopt(SocketFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &Mreq, sizeof(struct ip_mreq));
        if (0 != ret)
        {
            perror("[SocketRecvThread] setsockopt IP_ADD_MEMBERSHIP error");

            goto exit;
        }
    }

    while (HI_THREAD_EXIT != IpInfo->RunFlag)
    {
        HI_U32              buf[1500];
        HI_UNF_STREAM_BUF_S StreamBuf;
        HI_S32              ReadLen;

        ReadLen = recvfrom(SocketFd, buf, sizeof(buf), 0, HI_NULL, HI_NULL);
        if (ReadLen <= 0)
        {
            usleep(10 * 1000);

            continue;
        }

        do
        {
            ret = HI_UNF_DMX_GetTSBuffer(TsBuffer, ReadLen, &StreamBuf, 100);
            if (HI_SUCCESS == ret)
            {
                memcpy(StreamBuf.pu8Data, buf, ReadLen);

                ret = HI_UNF_DMX_PutTSBuffer(TsBuffer, ReadLen);
                if (HI_SUCCESS != ret)
                {
                    printf("[%s] HI_UNF_DMX_PutTSBuffer failed 0x%x\n", __FUNCTION__, ret);
                }

                break;
            }
        } while (HI_THREAD_EXIT != IpInfo->RunFlag);
    }

    if (IpInfo->IP)
    {
        ret = setsockopt(SocketFd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &Mreq, sizeof(struct ip_mreq));
        if (0 != ret)
        {
            perror("[SocketRecvThread] setsockopt IP_DROP_MEMBERSHIP error");

            goto exit;
        }
    }

exit :
    if (SocketFd >= 0)
    {
        close(SocketFd);
    }

    ret = HI_UNF_DMX_DestroyTSBuffer(TsBuffer);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_DestroyTSBuffer failed 0x%x\n", __FUNCTION__, ret);
    }

    return HI_NULL;
}

static HI_VOID* EsFileSendThread(HI_VOID *arg)
{
    HI_S32      ret;
    FILE       *VidEsFp = HI_NULL;
    FILE       *AudEsFp = HI_NULL;
    EsFileInfo *Es      = (EsFileInfo*)arg;

    if (!Es)
    {
        goto exit;
    }

    if (strlen(Es->VidFileName))
    {
        printf("[%s] open %s\n", __FUNCTION__, Es->VidFileName);

        VidEsFp = fopen(Es->VidFileName, "rb");
        if (!VidEsFp)
        {
            perror("[EsFileSendThread] fopen error");

            goto exit;
        }
    }

    if (strlen(Es->AudFileName))
    {
        printf("[%s] open %s\n", __FUNCTION__, Es->AudFileName);

        AudEsFp = fopen(Es->AudFileName, "rb");
        if (!AudEsFp)
        {
            perror("[EsFileSendThread] fopen error");

            goto exit;
        }
    }

    while (HI_THREAD_EXIT != Es->RunFlag)
    {
        HI_UNF_STREAM_BUF_S StreamBuf;
        HI_S32              ReadLen;

        if (VidEsFp)
        {
            ret = HI_UNF_AVPLAY_GetBuf(Es->Avplay, HI_UNF_AVPLAY_BUF_ID_ES_VID, 0x8000, &StreamBuf, 0);
            if (HI_SUCCESS == ret)
            {
                ReadLen = fread(StreamBuf.pu8Data, 1, StreamBuf.u32Size, VidEsFp);
                if (ReadLen < 0)
                {
                    perror("[EsFileSendThread] vid fread error");

                    break;
                }

                if (0 == ReadLen)
                {
                    rewind(VidEsFp);
                }
                else
                {
                    ret = HI_UNF_AVPLAY_PutBuf(Es->Avplay, HI_UNF_AVPLAY_BUF_ID_ES_VID, ReadLen, 0);
                    if (HI_SUCCESS != ret)
                    {
                        printf("[%s - %u] HI_UNF_AVPLAY_PutBuf Vid failed 0x%x\n", __FUNCTION__, __LINE__, ret);
                    }
                }
            }
        }

        if (AudEsFp)
        {
            ret = HI_UNF_AVPLAY_GetBuf(Es->Avplay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, 0x2000, &StreamBuf, 0);
            if (HI_SUCCESS == ret)
            {
                ReadLen = fread(StreamBuf.pu8Data, 1, StreamBuf.u32Size, AudEsFp);
                if (ReadLen < 0)
                {
                    perror("[EsFileSendThread] aud fread error");

                    break;
                }

                if (0 == ReadLen)
                {
                    rewind(AudEsFp);
                }
                else
                {
                    ret = HI_UNF_AVPLAY_PutBuf(Es->Avplay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, ReadLen, 0);
                    if (HI_SUCCESS != ret)
                    {
                        printf("[%s - %u] HI_UNF_AVPLAY_PutBuf Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);
                    }
                }
            }
        }

        usleep(5 * 1000);
    }

exit :
    if (AudEsFp)
    {
        fclose(AudEsFp);
    }

    if (VidEsFp)
    {
        fclose(VidEsFp);
    }

    Es->RunFlag = HI_THREAD_EXIT;

    return HI_NULL;
}

static HI_VOID ResetPlayInfo(HiPlayInfo *Play)
{
    Play->PlayMode  = HI_PLAY_MODE_NONE;
    Play->Avplay    = HI_INVALID_HANDLE;
    Play->Window    = HI_INVALID_HANDLE;
    Play->Sound     = HI_INVALID_HANDLE;
    Play->ThreadId  = 0;

    memset(&Play->TsFile, 0, sizeof(Play->TsFile));
    memset(&Play->EsFile, 0, sizeof(Play->EsFile));
}

static HI_S32 CreateAvplay(HI_U32 DmxId, HI_U32 StreamType, HI_HANDLE *Avplay)
{
    HI_S32                      ret;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;

    ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, StreamType);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_GetDefaultConfig failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    if (HI_UNF_AVPLAY_STREAM_TYPE_TS == StreamType)
    {
        AvplayAttr.u32DemuxId = DmxId;
    }

    ret = HI_UNF_AVPLAY_Create(&AvplayAttr, Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_Create failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_AVPLAY_ChnOpen(*Avplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_ChnOpen Vid failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_AVPLAY_ChnOpen(*Avplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_ChnOpen Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_AVPLAY_GetAttr(*Avplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_GetAttr Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    if (HI_UNF_AVPLAY_STREAM_TYPE_TS == StreamType)
    {
        SyncAttr.enSyncRef      = HI_UNF_SYNC_REF_AUDIO;
        SyncAttr.bQuickOutput   = HI_FALSE;

        SyncAttr.stSyncStartRegion.s32VidPlusTime       = 60;
        SyncAttr.stSyncStartRegion.s32VidNegativeTime   = -20;
    }
    else
    {
        SyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    }

    ret = HI_UNF_AVPLAY_SetAttr(*Avplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_SetAttr sync failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    return ret;
}

static HI_S32 DestroyAvplay(HI_HANDLE Avplay)
{
    HI_S32  ret;

    ret = HI_UNF_AVPLAY_ChnClose(Avplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_ChnClose failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_AVPLAY_Destroy(Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_Destroy failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    return ret;
}

static HI_S32 CreateSound(HI_UNF_SND_TRACK_TYPE_E TrackType, HI_HANDLE Avplay, HI_HANDLE *Sound)
{
    HI_S32                      ret;
    HI_HANDLE                   Snd;
    HI_UNF_AUDIOTRACK_ATTR_S    SndAttr;

    SndAttr.enTrackType = TrackType;

    ret = HI_UNF_SND_GetDefaultTrackAttr(TrackType, &SndAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_GetDefaultTrackAttr failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &SndAttr, &Snd);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_CreateTrack failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_SND_Attach(Snd, Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_Attach failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    *Sound = Snd;

    return ret;
}

static HI_S32 DestroySound(HI_HANDLE Sound, HI_HANDLE Avplay)
{
    HI_S32  ret;

    ret = HI_UNF_SND_Detach(Sound, Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_Detach failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    ret = HI_UNF_SND_DestroyTrack(Sound);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_SND_DestroyTrack failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    return ret;
}

static HI_S32 CreateWindow(HI_RECT_S *Rect, HI_HANDLE Avplay, HI_U32 Order, HI_HANDLE *WinHnd)
{
    HI_S32                  ret;
    HI_HANDLE               Win;
    HI_UNF_WINDOW_ATTR_S    WinAttr = {0};

    WinAttr.enDisp          = HI_UNF_DISPLAY1;
    WinAttr.bVirtual        = HI_FALSE;
    WinAttr.bUseCropRect    = HI_FALSE;

    WinAttr.stWinAspectAttr.enAspectCvrs        = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;

    memcpy(&WinAttr.stOutputRect, Rect, sizeof(HI_RECT_S));

    ret = HI_UNF_VO_CreateWindow(&WinAttr, &Win);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_CreateWindow failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_VO_AttachWindow(Win, Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_AttachWindow failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_VO_SetWindowEnable(Win, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_SetWindowEnable failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_VO_SetWindowZorder(Win, Order);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_VO_SetWindowZorder failed 0x%x\n", __FUNCTION__, ret);
    }

    *WinHnd = Win;

    return ret;
}

static HI_S32 DestroyWindow(HI_HANDLE WinHnd, HI_HANDLE Avplay)
{
    HI_S32  ret;

    ret = HI_UNF_VO_SetWindowEnable(WinHnd, HI_FALSE);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_SetWindowEnable failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_VO_DetachWindow(WinHnd, Avplay);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_DetachWindow failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_VO_DestroyWindow(WinHnd);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_VO_DestroyWindow failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    return ret;
}

static HI_VOID GetVideoPid(HiPmtData *PmtData, HI_U32 *VidPid, HI_U32 *VidType)
{
    HI_U32  i;

    *VidPid     = HI_INVALID_PID;
    *VidType    = HI_UNF_VCODEC_TYPE_BUTT;

    for (i = 0; i < PmtData->Programs; i++)
    {
        HI_BOOL FindFlag = HI_TRUE;

        switch (PmtData->ProgInfo[i].Type)
        {
            case HI_UNF_VCODEC_TYPE_MPEG2 :
                *VidType    = HI_UNF_VCODEC_TYPE_MPEG2;
                *VidPid     = PmtData->ProgInfo[i].Pid;
                break;

            case HI_UNF_VCODEC_TYPE_MPEG4 :
                *VidType    = HI_UNF_VCODEC_TYPE_MPEG4;
                *VidPid     = PmtData->ProgInfo[i].Pid;
                break;

            case HI_UNF_VCODEC_TYPE_H264 :
                *VidType    = HI_UNF_VCODEC_TYPE_H264;
                *VidPid     = PmtData->ProgInfo[i].Pid;
                break;

            case HI_UNF_VCODEC_TYPE_AVS :
                *VidType    = HI_UNF_VCODEC_TYPE_AVS;
                *VidPid     = PmtData->ProgInfo[i].Pid;
                break;

            case HI_UNF_VCODEC_TYPE_HEVC :
                *VidType    = HI_UNF_VCODEC_TYPE_HEVC;
                *VidPid     = PmtData->ProgInfo[i].Pid;
                break;

            default :
                FindFlag = HI_FALSE;
        }

        if (FindFlag)
        {
            break;
        }
    }
}

static HI_VOID GetAudioPid(HiPmtData *PmtData, HI_U32 *AudPid, HI_U32 *AudType)
{
    HI_U32  i;

    *AudPid     = HI_INVALID_PID;
    *AudType    = 0;

    for (i = 0; i < PmtData->Programs; i++)
    {
        HI_BOOL FindFlag = HI_TRUE;

        switch (PmtData->ProgInfo[i].Type)
        {
            case HA_AUDIO_ID_MP3 :
                *AudType    = HA_AUDIO_ID_MP3;
                *AudPid     = PmtData->ProgInfo[i].Pid;
                break;

            case HA_AUDIO_ID_AAC :
                *AudType    = HA_AUDIO_ID_AAC;
                *AudPid     = PmtData->ProgInfo[i].Pid;
                break;

            case HA_AUDIO_ID_DOLBY_PLUS :
                *AudType    = HA_AUDIO_ID_DOLBY_PLUS;
                *AudPid     = PmtData->ProgInfo[i].Pid;
                break;

            default :
                FindFlag = HI_FALSE;
        }

        if (FindFlag)
        {
            break;
        }
    }
}

static HI_S32 AvStart(HI_HANDLE Avplay, HI_U32 VidPid, HI_U32 VidType, HI_U32 AudPid, HI_U32 AudType)
{
    HI_S32                  ret;
    HI_UNF_VCODEC_ATTR_S    VdecAttr;
    HI_UNF_ACODEC_ATTR_S    AdecAttr;
    HI_UNF_SYNC_ATTR_S      SyncAttr;
    HI_BOOL                 VidEnable = HI_FALSE;
    HI_BOOL                 AudEnable = HI_FALSE;

    ret = HI_UNF_AVPLAY_GetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, (HI_VOID*)&SyncAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_GetAttr Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    ret = HI_UNF_AVPLAY_SetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, (HI_VOID*)&SyncAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_SetAttr Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    ret = HI_UNF_AVPLAY_GetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, (HI_VOID*)&VdecAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_GetAttr failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    VdecAttr.enMode         = HI_UNF_VCODEC_MODE_NORMAL;
    VdecAttr.u32ErrCover    = 100;
    VdecAttr.u32Priority    = 3;

    ret = HI_UNF_AVPLAY_GetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, (HI_VOID*)&AdecAttr);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_GetAttr Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    if (HI_INVALID_PID != VidPid)
    {
        ret = HI_UNF_AVPLAY_SetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &VidPid);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_AVPLAY_SetAttr Vid failed 0x%x\n", __FUNCTION__, __LINE__, ret);

            return ret;
        }
    }

    if (HI_INVALID_PID != AudPid)
    {
        ret = HI_UNF_AVPLAY_SetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &AudPid);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_AVPLAY_SetAttr Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

            return ret;
        }
    }

    VdecAttr.enType = VidType;
    VidEnable = HI_TRUE;
    AdecAttr.enType = AudType;

    switch (AudType)
    {
        case HA_AUDIO_ID_MP3 :
            AudEnable = HI_TRUE;
            HA_MP3_DecGetDefalutOpenParam(&AdecAttr.stDecodeParam);
            break;

        case HA_AUDIO_ID_AAC :
            AudEnable = HI_TRUE;
            HA_AAC_DecGetDefalutOpenParam(&AdecAttr.stDecodeParam);
            break;

        case HA_AUDIO_ID_DOLBY_PLUS :
        {
            static DOLBYPLUS_DECODE_OPENCONFIG_S DolbyDecode;

            HA_DOLBYPLUS_DecGetDefalutOpenConfig(&DolbyDecode);

            /* Dolby DVB Broadcast default settings */
            DolbyDecode.enDrcMode = DOLBYPLUS_DRC_RF;
            DolbyDecode.enDmxMode = DOLBYPLUS_DMX_SRND;
            HA_DOLBYPLUS_DecGetDefalutOpenParam(&AdecAttr.stDecodeParam, &DolbyDecode);

            AdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_SIMUL;

            AudEnable = HI_TRUE;
            break;
        }

        default :
            break;
    }

    if (VidEnable)
    {
        ret = HI_UNF_AVPLAY_SetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_AVPLAY_SetAttr failed 0x%x\n", __FUNCTION__, __LINE__, ret);

            return ret;
        }

        ret = HI_UNF_AVPLAY_Start(Avplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_AVPLAY_Start Vid failed 0x%x\n", __FUNCTION__, __LINE__, ret);

            return ret;
        }
    }

    if (AudEnable)
    {
        ret = HI_UNF_AVPLAY_SetAttr(Avplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AdecAttr);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_AVPLAY_SetAttr Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

            return ret;
        }

        ret = HI_UNF_AVPLAY_Start(Avplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_AVPLAY_Start Aud failed 0x%x\n", __FUNCTION__, __LINE__, ret);

            return ret;
        }
    }

    return ret;
}

static HI_S32 AvStop(HI_HANDLE Avplay)
{
    HI_S32                      ret;
    HI_UNF_AVPLAY_STOP_OPT_S    AvplayStop;

    AvplayStop.enMode       = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    AvplayStop.u32TimeoutMs = 0;

    ret = HI_UNF_AVPLAY_Stop(Avplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD | HI_UNF_AVPLAY_MEDIA_CHAN_VID, &AvplayStop);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_AVPLAY_Stop failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    return ret;
}

static HI_S32 CreatePlayer(HI_U32 PlayId, HI_U32 DmxId, HI_U32 PlayMode, HI_BOOL bHDDisplay)
{
    HI_S32                      ret;
    HiPlayInfo                 *Play;
    HI_RECT_S                   Rect;
    HI_U32                      TrackType;
    HI_UNF_AVPLAY_STREAM_TYPE_E StreamType;
    HI_LAYER_ZORDER_E           LayerZorder;
    HI_U32  u32Width = 0;
    HI_U32 u32Height = 0;

    if (HI_TRUE == bHDDisplay)
    {
        u32Width = 1280;
        u32Height = 720;
    }
    else
    {
        u32Width = 640;
        u32Height = 480;
    }
    {
        u32Width = u32Width*1920/3840;
        u32Height = u32Height*1080/2160;
    }
    if (0 == PlayId)
    {
        Rect.s32X       = 0;
        Rect.s32Y       = 0;
        Rect.s32Width   = 0;
        Rect.s32Height  = 0;
        if (HI_FALSE == bHDDisplay)
        {
            //Rect.s32Width   = 3840*2/3;
            //Rect.s32Height  = 2160*2/3;
            Rect.s32Width   = 1920;
            Rect.s32Height  = 1080*2/3;
        }
        TrackType   = HI_UNF_SND_TRACK_TYPE_MASTER;
        LayerZorder = HI_LAYER_ZORDER_MOVEBOTTOM;
    }
    else if (1 == PlayId)
    {
        Rect.s32X       = 0;
        Rect.s32Y       = 1080-u32Height;
        Rect.s32Width   = u32Width;
        Rect.s32Height  = u32Height;

        TrackType   = HI_UNF_SND_TRACK_TYPE_SLAVE;
        LayerZorder = HI_LAYER_ZORDER_MOVETOP;
    }
    else if (2 == PlayId)
    {
        Rect.s32X       = u32Width;
        Rect.s32Y       = 1080-u32Height;
        Rect.s32Width   = u32Width;
        Rect.s32Height  = u32Height;

        TrackType   = HI_UNF_SND_TRACK_TYPE_SLAVE;
        LayerZorder = HI_LAYER_ZORDER_MOVETOP;
    }
    else
    {
        Rect.s32X       = u32Width*2;
        Rect.s32Y       = 1080-u32Height;
        Rect.s32Width   = u32Width;
        Rect.s32Height  = u32Height;

        TrackType   = HI_UNF_SND_TRACK_TYPE_SLAVE;
        LayerZorder = HI_LAYER_ZORDER_MOVETOP;
    }

    if (HI_PLAY_MODE_ES == PlayMode)
    {
        StreamType = HI_UNF_AVPLAY_STREAM_TYPE_ES;
    }
    else
    {
        StreamType = HI_UNF_AVPLAY_STREAM_TYPE_TS;
    }

    Play = &PlayInfo[PlayId];
    if (HI_PLAY_MODE_NONE != Play->PlayMode)
    {
        if (HI_PLAY_MODE_DVB == Play->PlayMode)
        {
            HiPlayDvbStop(PlayId);
        }
        else if (HI_PLAY_MODE_TS == Play->PlayMode)
        {
            HiPlayTsStop(PlayId);
        }
        else if (HI_PLAY_MODE_ES == Play->PlayMode)
        {
            HiPlayEsStop(PlayId);
        }
    }

    Play->PlayMode = PlayMode;

    ret = CreateAvplay(DmxId, StreamType, &Play->Avplay);
    ret = CreateWindow(&Rect, Play->Avplay, LayerZorder, &Play->Window);
    ret = CreateSound(TrackType, Play->Avplay, &Play->Sound);

    return ret;
}

static HI_S32 DestroyPlayer(HI_U32 PlayId)
{
    HI_S32      ret;
    HiPlayInfo *Play = &PlayInfo[PlayId];

    if (HI_INVALID_HANDLE != Play->Sound)
    {
        ret = DestroySound(Play->Sound, Play->Avplay);
    }

    if (HI_INVALID_HANDLE != Play->Window)
    {
        ret = DestroyWindow(Play->Window, Play->Avplay);
    }

    ret = DestroyAvplay(Play->Avplay);

    ResetPlayInfo(Play);

    return ret;
}

HI_S32 HiPlayDvb(HI_U32 PlayId, HI_U32 TunerId, HI_U32 ProgNum)
{
    HI_S32      ret;
    HI_U32      DmxId   = PlayId;
    HiPmtData  *PmtData;
    HiPlayInfo *DvbPlay;
    HI_U32      AudPid;
    HI_U32      AudType;
    HI_U32      VidPid;
    HI_U32      VidType;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    ret = HI_UNF_DMX_AttachTSPort(DmxId, HI_UNF_DMX_PORT_TSI_0 + TunerId);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DMX_AttachTSPort failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;
    }

    CreatePlayer(PlayId, DmxId, HI_PLAY_MODE_DVB, HI_TRUE);

    DvbPlay = &PlayInfo[PlayId];

    DvbPlay->TunerId = TunerId;

    if (0 == DvbPlay->Pmt.PmtCount)
    {
        ret = HiPsiGetProgramInfo(DmxId, &DvbPlay->Pmt);
        if ((HI_SUCCESS != ret) || (0 == DvbPlay->Pmt.PmtCount))
        {
            return HI_FAILURE;
        }
    }

    PmtData = &DvbPlay->Pmt.PmtInfo[ProgNum % DvbPlay->Pmt.PmtCount];

    GetAudioPid(PmtData, &AudPid, &AudType);
    GetVideoPid(PmtData, &VidPid, &VidType);

    AvStart(DvbPlay->Avplay, VidPid, VidType, AudPid, AudType);

    return 0;
}

HI_S32 HiPlayDvbStop(HI_U32 PlayId)
{
    HI_S32      ret;
    HiPlayInfo *Play = HI_NULL;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    Play = &PlayInfo[PlayId];
    if (HI_PLAY_MODE_DVB != Play->PlayMode)
    {
        return HI_FAILURE;
    }

    if (HI_INVALID_HANDLE == Play->Avplay)
    {
        return HI_SUCCESS;
    }

    ret = AvStop(Play->Avplay);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    DestroyPlayer(PlayId);

    return ret;
}

HI_S32 HiPlayTs(HI_U32 PlayId, HI_CHAR *TsFile, HI_U32 VidPid, HI_CHAR *VidFmt, HI_U32 AudPid, HI_CHAR *AudFmt, HI_BOOL bHDDisplay)
{
    HI_S32      ret;
    HI_U32      DmxId   = PlayId;
    HI_U32      PortId;
    HiPmtData  *PmtData;
    HiPlayInfo *TsPlay;
    HI_U32      AudType;
    HI_U32      VidType;
    HI_BOOL     bPlayTwo = HI_FALSE;

    if (2 == PlayId)
    {
        bPlayTwo = HI_TRUE;
    }
    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    if (strlen(TsFile) >= MAX_FILENAME_LEN)
    {
        printf("[%s - %u] filename too long\n", __FUNCTION__, __LINE__);

        return HI_FAILURE;
    }

    if (0 == strcmp(TsFile, "null"))
    {
        printf("[%s - %u] file is null\n", __FUNCTION__, __LINE__);

        return HI_FAILURE;
    }

    ret = HiDemuxMallocRamPortId(&PortId);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] error: no free ram port\n", __FUNCTION__, __LINE__);

        return ret;
    }

    ret = HI_UNF_DMX_AttachTSPort(DmxId, PortId);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DMX_AttachTSPort failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        HiDemuxFreeRamPortId(PortId);

        return ret;
    }
    if (HI_TRUE == bPlayTwo)
    {
        ret = HI_UNF_DMX_AttachTSPort(DmxId + 1, PortId);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_DMX_AttachTSPort failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        }
    }
    CreatePlayer(PlayId, DmxId, HI_PLAY_MODE_TS, bHDDisplay);
    if (HI_TRUE == bPlayTwo)
    {
        CreatePlayer(PlayId + 1, DmxId + 1, HI_PLAY_MODE_TS, bHDDisplay);
    }
    TsPlay = &PlayInfo[PlayId];

    TsPlay->TsFile.PortId       = PortId;
    TsPlay->TsFile.TsBufferSize = 16 * 1024 * 1024;
    TsPlay->TsFile.Rewind       = HI_TRUE;
    TsPlay->TsFile.SleepMs      = 0;
    TsPlay->TsFile.RunFlag      = HI_THREAD_RUNNING;
    strcpy(TsPlay->TsFile.FileName, TsFile);

    ret = pthread_create(&TsPlay->ThreadId, HI_NULL, TsFileSendThread, (HI_VOID*)&TsPlay->TsFile);
    if (0 != ret)
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    if ((HI_INVALID_PID == VidPid) && (HI_INVALID_PID == AudPid))
    {
        ret = HiPsiGetProgramInfo(DmxId, &TsPlay->Pmt);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }

        TsPlay->TsFile.RunFlag = HI_THREAD_SLEEP;
    }
    else
    {
        TsPlay->Pmt.PmtCount = 1;
        TsPlay->Pmt.PmtInfo[0].Programs = 2;
    }
    PmtData = &TsPlay->Pmt.PmtInfo[0];
    GetAudioPid(PmtData, &AudPid, &AudType);
    GetVideoPid(PmtData, &VidPid, &VidType);

    AvStart(TsPlay->Avplay, VidPid, VidType, AudPid, AudType);

    TsPlay->TsFile.RunFlag = HI_THREAD_RUNNING;
    if (HI_TRUE == bPlayTwo)
    {
        TsPlay = &PlayInfo[PlayId + 1];
        memcpy(&(PlayInfo[PlayId + 1].Pmt), &(PlayInfo[PlayId].Pmt), sizeof(HiPmtInfo));
        PmtData = &TsPlay->Pmt.PmtInfo[0];
        GetAudioPid(PmtData, &AudPid, &AudType);
        GetVideoPid(PmtData, &VidPid, &VidType);

        AvStart(TsPlay->Avplay, VidPid, VidType, AudPid, AudType);

        TsPlay->TsFile.RunFlag = HI_THREAD_RUNNING;
    }
    return 0;
}

HI_S32 HiPlayTsStop(HI_U32 PlayId)
{
    HI_S32      ret;
    HiPlayInfo *TsPlay  = HI_NULL;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    TsPlay = &PlayInfo[PlayId];
    if (HI_PLAY_MODE_TS != TsPlay->PlayMode)
    {
        return HI_FAILURE;
    }

    if (HI_INVALID_HANDLE == TsPlay->Avplay)
    {
        return HI_SUCCESS;
    }

    TsPlay->TsFile.RunFlag = HI_THREAD_EXIT;

    ret = AvStop(TsPlay->Avplay);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    pthread_join(TsPlay->ThreadId, HI_NULL);

    HiDemuxFreeRamPortId(TsPlay->TsFile.PortId);

    DestroyPlayer(PlayId);

    ResetPlayInfo(TsPlay);

    return ret;
}

HI_S32 HiPlayIp(HI_U32 PlayId, HI_CHAR *IpAddr)
{
    HI_S32      ret;
    HI_U32      DmxId   = PlayId;
    HI_U32      PortId;
    HiPmtData  *PmtData;
    HiPlayInfo *IpPlay;
    HI_U32      AudPid;
    HI_U32      VidPid;
    HI_U32      AudType;
    HI_U32      VidType;
    HI_U32      Ip;
    HI_U32      Port;
    HI_CHAR    *String;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    String = strchr(IpAddr, ':');
    if (String)
    {
        *String = 0;

        Port = strtoul(String + 1, HI_NULL, 0);
    }
    else
    {
        Port = 1234;
    }

    Ip = inet_addr(IpAddr);

    if (String)
    {
        *String = ':';
    }

    ret = HiDemuxMallocRamPortId(&PortId);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] error: no free ram port\n", __FUNCTION__, __LINE__);

        return ret;
    }

    ret = HI_UNF_DMX_AttachTSPort(DmxId, PortId);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DMX_AttachTSPort failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        HiDemuxFreeRamPortId(PortId);

        return ret;
    }

    CreatePlayer(PlayId, DmxId, HI_PLAY_MODE_IP, HI_TRUE);

    IpPlay = &PlayInfo[PlayId];

    IpPlay->IpInfo.IP       = Ip;
    IpPlay->IpInfo.Port     = Port;
    IpPlay->IpInfo.PortId   = PortId;
    IpPlay->IpInfo.TsBufSize= 0x200000;
    IpPlay->IpInfo.RunFlag  = HI_THREAD_RUNNING;

    ret = pthread_create(&IpPlay->ThreadId, HI_NULL, SocketRecvThread, (HI_VOID*)&IpPlay->IpInfo);
    if (0 != ret)
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    ret = HiPsiGetProgramInfo(DmxId, &IpPlay->Pmt);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    PmtData = &IpPlay->Pmt.PmtInfo[0];

    GetAudioPid(PmtData, &AudPid, &AudType);
    GetVideoPid(PmtData, &VidPid, &VidType);

    AvStart(IpPlay->Avplay, VidPid, VidType, AudPid, AudType);

    return 0;
}

HI_S32 HiPlayIpStop(HI_U32 PlayId)
{
    HI_S32      ret;
    HiPlayInfo *IpPlay  = HI_NULL;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    IpPlay = &PlayInfo[PlayId];
    if (HI_PLAY_MODE_IP != IpPlay->PlayMode)
    {
        return HI_FAILURE;
    }

    if (HI_INVALID_HANDLE == IpPlay->Avplay)
    {
        return HI_SUCCESS;
    }

    IpPlay->IpInfo.RunFlag = HI_THREAD_EXIT;

    ret = AvStop(IpPlay->Avplay);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    pthread_join(IpPlay->ThreadId, HI_NULL);

    HiDemuxFreeRamPortId(IpPlay->IpInfo.PortId);

    DestroyPlayer(PlayId);

    ResetPlayInfo(IpPlay);

    return ret;
}

HI_S32 HiPlayEs(HI_U32 PlayId, HI_CHAR *VidFile, HI_CHAR *VidFmt, HI_CHAR *AudFile, HI_CHAR *AudFmt, HI_U32 u32Fps)
{
    HI_S32      ret;
    HiPlayInfo *EsPlay;
    HI_U32      VidType = 0;
    HI_U32      AudType = 0;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    if (VidFile)
    {
        if (strlen(VidFile) >= MAX_FILENAME_LEN)
        {
            return HI_FAILURE;
        }

        ret = VidStringToEnum(VidFmt, &VidType);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] video format error\n", __FUNCTION__, __LINE__);

            return HI_FAILURE;
        }
    }

    if (AudFile)
    {
        if (strlen(AudFile) >= MAX_FILENAME_LEN)
        {
            return HI_FAILURE;
        }

        ret = AudStringToEnum(AudFmt, &AudType);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] audio format error\n", __FUNCTION__, __LINE__);

            return HI_FAILURE;
        }
    }

    EsPlay = &PlayInfo[PlayId];

    CreatePlayer(PlayId, PlayId, HI_PLAY_MODE_ES, HI_TRUE);
#if 1 //set fps
    if (0 != u32Fps) //¡Á??¡§¨°????¨º
    {        
        printf("[%s - %u] avplay:%d,frame rate:%d fps\n", __FUNCTION__, __LINE__,PlayId,u32Fps);
        HI_UNF_AVPLAY_FRMRATE_PARAM_S stFramerate;
        stFramerate.enFrmRateType = HI_UNF_AVPLAY_FRMRATE_TYPE_USER;
        stFramerate.stSetFrmRate.u32fpsInteger = u32Fps;
        stFramerate.stSetFrmRate.u32fpsDecimal = 0;
        ret = HI_UNF_AVPLAY_SetAttr(EsPlay->Avplay, HI_UNF_AVPLAY_ATTR_ID_FRMRATE_PARAM, &stFramerate);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_AVPLAY_SetAttr FRMRATE error:0x%x\n", __FUNCTION__, __LINE__,ret);
        }
    }
#endif
    AvStart(EsPlay->Avplay, HI_INVALID_PID, VidType, HI_INVALID_PID, AudType);

    EsPlay->EsFile.Avplay   = EsPlay->Avplay;
    EsPlay->EsFile.RunFlag  = HI_THREAD_RUNNING;

    if (VidFile)
    {
        strcpy(EsPlay->EsFile.VidFileName, VidFile);
    }
    else
    {
        memset(EsPlay->EsFile.VidFileName, 0, MAX_FILENAME_LEN);
    }

    if (AudFile)
    {
        strcpy(EsPlay->EsFile.AudFileName, AudFile);
    }
    else
    {
        memset(EsPlay->EsFile.AudFileName, 0, MAX_FILENAME_LEN);
    }

    ret = pthread_create(&EsPlay->ThreadId, HI_NULL, EsFileSendThread, (HI_VOID*)&EsPlay->EsFile);
    if (0 != ret)
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HiPlayEsStop(HI_U32 PlayId)
{
    HI_S32      ret;
    HiPlayInfo *EsPlay  = HI_NULL;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    EsPlay = &PlayInfo[PlayId];
    if (HI_PLAY_MODE_ES != EsPlay->PlayMode)
    {
        return HI_FAILURE;
    }

    EsPlay->EsFile.RunFlag = HI_THREAD_EXIT;
    pthread_join(EsPlay->ThreadId, HI_NULL);

    ret = AvStop(EsPlay->Avplay);

    ret = DestroyPlayer(PlayId);

    return ret;
}

HI_S32 HiPlayPvr(HI_U32 PlayId, HI_U32 DmxId, HiPmtData *PmtData, HI_HANDLE *Avplay)
{
    HiPlayInfo *PvrPlay;
    HI_U32      AudPid;
    HI_U32      AudType;
    HI_U32      VidPid;
    HI_U32      VidType;

    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    CreatePlayer(PlayId, DmxId, HI_PLAY_MODE_PVR, HI_TRUE);

    PvrPlay = &PlayInfo[PlayId];

    GetAudioPid(PmtData, &AudPid, &AudType);
    GetVideoPid(PmtData, &VidPid, &VidType);

    AvStart(PvrPlay->Avplay, VidPid, VidType, AudPid, AudType);

    *Avplay = PvrPlay->Avplay;

    return HI_SUCCESS;
}

HI_S32 HiPlayPvrStop(HI_U32 PlayId)
{
    if (PlayId >= HI_PLAY_COUNT)
    {
        printf("[%s - %u] PlayId %u error\n", __FUNCTION__, __LINE__, PlayId);

        return HI_FAILURE;
    }

    DestroyPlayer(PlayId);

    return HI_SUCCESS;
}

HI_S32 HiPlayGetInfo(HI_U32 PlayId, HI_HANDLE *Avplay)
{
    HI_S32      ret     = HI_FAILURE;
    HiPlayInfo *Play    = HI_NULL;

    if (PlayId >= HI_PLAY_COUNT)
    {
        return HI_FAILURE;
    }

    Play = &PlayInfo[PlayId];
    if ((PlayId == Play->PlayId) && (HI_INVALID_HANDLE != Play->Avplay))
    {
        *Avplay = Play->Avplay;

        ret = HI_SUCCESS;
    }

    return ret;
}

HI_VOID HiPlayCleanPmt(HI_U32 TunerId)
{
    HI_U32  i;

    for (i = 0; i < HI_PLAY_COUNT; i++)
    {
        HiPlayInfo *Play = &PlayInfo[i];

        if ((HI_PLAY_MODE_DVB == Play->PlayMode) && (TunerId == Play->TunerId))
        {
            memset(&Play->Pmt, 0, sizeof(Play->Pmt));
        }
    }
}

HI_S32 HiPlayInit(HI_VOID)
{
    HI_U32  i;

    for (i = 0; i < HI_PLAY_COUNT; i++)
    {
        PlayInfo[i].PlayId = i;

        ResetPlayInfo(&PlayInfo[i]);
    }

    return HI_SUCCESS;
}

HI_S32 HiPlayDeInit(HI_VOID)
{
    HI_U32  i;

    for (i = 0; i < HI_PLAY_COUNT; i++)
    {
        if (HI_PLAY_MODE_DVB == PlayInfo[i].PlayMode)
        {
            HiPlayDvbStop(i);
        }
        else if (HI_PLAY_MODE_TS == PlayInfo[i].PlayMode)
        {
            HiPlayTsStop(i);
        }
        else if (HI_PLAY_MODE_IP == PlayInfo[i].PlayMode)
        {
            HiPlayIpStop(i);
        }
        else if (HI_PLAY_MODE_ES == PlayInfo[i].PlayMode)
        {
            HiPlayEsStop(i);
        }
    }

    return HI_SUCCESS;
}

