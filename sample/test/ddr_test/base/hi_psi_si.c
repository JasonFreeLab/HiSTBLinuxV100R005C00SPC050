
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "hi_type.h"
#include "hi_unf_video.h"

#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DOLBYPLUS.decode.h"

#include "hi_psi_si.h"
#include "hi_demux.h"

#define PAT_PID                             0

#define PAT_TABLE_ID                        0x00
#define PMT_TABLE_ID                        0x02

#define AC3_EXT_DESCRIPTOR                  0x52
#define AC3_DESCRIPTOR                      0x6A
#define AC3_PLUS_DESCRIPTOR                 0x7A

#define PACKET_IDENTIFIER(a, b)             ((HI_U32)((((a) & 0x1f) << 8) | ((b) & 0xff)))
#define PROGRAM_NUMBER(a, b)                ((HI_U32)((((a) & 0xff) << 8) | ((b) & 0xff)))
#define VERSION_NUMBER(a)                   (((a) >> 1) & 0x1f)

#define INVALID_VERSION_NUMBER              (-1)

#define HI_DEMUX_INVALID_PROGRAM_NUMBER     (-1)
#define PROGRAM_INFO_LENGTH(a, b)           ((((a) & 0xf) << 8) | (b))
#define ES_INFO_LENGTH(a, b)                ((((a) & 0xf) << 8) | (b))

typedef struct
{
    HI_U32 ProgNum;
    HI_U32 PmtPid;
} HiPatData;

typedef struct
{
    HI_U32      VerNum;
    HI_U32      Pmts;
    HiPatData   Pmt[HI_PMT_COUNT];
} HiPatInfo;

static HI_VOID PsiParsePat(HI_U8 *buf, HI_U32 len, HI_VOID *param)
{
    HI_U32      i       = 0;
    HI_U8      *ptr     = buf;
    HI_U8      *end     = buf + len - 4;
    HI_U32      ver     = VERSION_NUMBER(ptr[5]);
    HiPatInfo  *PatInfo = (HiPatInfo*)param;

    if ((PatInfo->VerNum == ver) || (PAT_TABLE_ID != buf[0]))
    {
        return;
    }

    PatInfo->VerNum = ver;

    ptr += 8;

    while ((ptr + 4) <= end)
    {
        HI_U32 ProgNum;

        ProgNum = PROGRAM_NUMBER(ptr[0], ptr[1]);
        if (ProgNum)
        {
            PatInfo->Pmt[i].ProgNum = ProgNum;
            PatInfo->Pmt[i].PmtPid  = PACKET_IDENTIFIER(ptr[2], ptr[3]);

            if (PatInfo->Pmt[i].PmtPid)
            {
                ++i;
            }
        }

        ptr += 4;
    }

    PatInfo->Pmts = i;
}

static HI_BOOL Is265Stream(const HI_U8 *pu8Data, HI_S32 s32Length)
{
    HI_BOOL bRet = HI_FALSE;

    int nLen = s32Length;
    HI_U8 *pData = (HI_U8*)pu8Data;
    HI_U8 u8Tag = 0;
    HI_U8 u8Length = 0;

    while (nLen > 0)
    {
        u8Tag = *pData++;
        u8Length = *pData++;

        if (u8Tag == 0x05)
        {
            HI_U32 Identify = htonl(*((HI_U32*)pData));

            if (0x48455643 == Identify)
            {
                bRet = HI_TRUE;
                break;
            }
        }

        pData += u8Length;

        nLen -= (u8Length+2);
    }

    return bRet;
}

static HI_VOID PsiParsePmt(HI_U8 *buf, HI_U32 len, HI_VOID *param)
{
    HI_U8      *ptr         = buf;
    HI_U8      *end         = buf + len - 4;
    HI_U32      prog_num    = PROGRAM_NUMBER(ptr[3], ptr[4]);
    HI_U32      ver         = VERSION_NUMBER(ptr[5]);
    HiPmtData  *pmt         = (HiPmtData*)param;

    if (PMT_TABLE_ID != buf[0])
    {
        return;
    }

    if ((prog_num == pmt->ProgNum) && (ver == pmt->VerNum)) // 若有相同的PMT表则直接返回
    {
        return;
    }

    pmt->VerNum     = ver;
    pmt->ProgNum    = prog_num;

    ptr += 8;

    pmt->PcrPid = PACKET_IDENTIFIER(ptr[0], ptr[1]);

    ptr += (4 + PROGRAM_INFO_LENGTH(ptr[2], ptr[3]));

    while ((ptr + 5) <= end)
    {
        HI_U32  StreamType  = ptr[0];
        HI_U32  Pid         = PACKET_IDENTIFIER(ptr[1], ptr[2]);
        HI_U32  EsInfoLen   = ES_INFO_LENGTH(ptr[3], ptr[4]);
        HI_S32  Type        = -1;

        ptr += 5;

        switch (StreamType)
        {
            case STREAM_TYPE_11172_AUDIO :
            case STREAM_TYPE_13818_AUDIO :
                Type = HA_AUDIO_ID_MP3;
                break;

            case STREAM_TYPE_13818_7_AUDIO :
                Type = HA_AUDIO_ID_AAC;
                break;

            case STREAM_TYPE_AC3_AUDIO :
                Type = HA_AUDIO_ID_DOLBY_PLUS;
                break;

            case STREAM_TYPE_11172_VIDEO :
            case STREAM_TYPE_13818_VIDEO :
                Type = HI_UNF_VCODEC_TYPE_MPEG2;
                break;

            case STREAM_TYPE_14496_2_VIDEO :
                Type = HI_UNF_VCODEC_TYPE_MPEG4;
                break;

            case STREAM_TYPE_14496_10_VIDEO :
                Type = HI_UNF_VCODEC_TYPE_H264;
                break;

            case STREAM_TYPE_AVS_VIDEO :
                Type = HI_UNF_VCODEC_TYPE_AVS;
                break;

            case STREAM_TYPE_HEVC_VIDEO :
                Type = HI_UNF_VCODEC_TYPE_HEVC;
                break;

            case STREAM_TYPE_PRIVATE :
                if ((AC3_EXT_DESCRIPTOR == ptr[0]) || (AC3_DESCRIPTOR == ptr[0]) || (AC3_PLUS_DESCRIPTOR == ptr[0]))
                {
                    Type = HA_AUDIO_ID_DOLBY_PLUS;
                }
                else if (Is265Stream(ptr, end-ptr))
                {
                    Type = HI_UNF_VCODEC_TYPE_HEVC;
                }
                break;

            default :
                printf("[%s] Pid = 0x%xStreamType=0x%x, EsInfoLen=0x%x, Tag=0x%x\n", __FUNCTION__, Pid, StreamType, EsInfoLen, ptr[0]);
                break;
        }
        
        if (-1 != Type)
        {
            pmt->ProgInfo[pmt->Programs].Type   = Type;
            pmt->ProgInfo[pmt->Programs].Pid    = Pid;

            if (++pmt->Programs >= HI_PROGRAM_COUNT)
            {
                break;
            }
        }

        ptr += EsInfoLen;
    }
}

static HI_VOID ShowProgram(HiPatInfo *PatInfo, HiPmtInfo *PmtData)
{
    HI_U32 i;

    for (i = 0; i < PmtData->PmtCount; i++)
    {
        HI_U32 j;

        printf("PmtPid=0x%x, Program Number=%d\n",
            PatInfo->Pmt[i].PmtPid, PmtData->PmtInfo[i].ProgNum);

        for (j = 0; j < PmtData->PmtInfo[i].Programs; j++)
        {
            switch (PmtData->PmtInfo[i].ProgInfo[j].Type)
            {
                case HI_UNF_VCODEC_TYPE_MPEG2 :
                    printf("\tPID=%u(0x%x) - MPEG2 Video Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                    break;

                case HI_UNF_VCODEC_TYPE_MPEG4 :
                    printf("\tPID=%u(0x%x) - MPEG4 Video Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                    break;

                case HI_UNF_VCODEC_TYPE_H264 :
                    printf("\tPID=%u(0x%x) - H264 Video Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                    break;

                case HI_UNF_VCODEC_TYPE_AVS :
                    printf("\tPID=%u(0x%x) - AVS Video Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                case HI_UNF_VCODEC_TYPE_HEVC:
                    printf("\tPID=%u(0x%x) - HEVC Video Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                    break;

                case HA_AUDIO_ID_MP3 :
                    printf("\tPID=%u(0x%x) - MP3 Audio Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                    break;

                case HA_AUDIO_ID_AAC :
                    printf("\tPID=%u(0x%x) - AAC Audio Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                    break;

                case HA_AUDIO_ID_DOLBY_PLUS :
                    printf("\tPID=%u(0x%x) - AC3 Audio Stream\n",
                        PmtData->PmtInfo[i].ProgInfo[j].Pid, PmtData->PmtInfo[i].ProgInfo[j].Pid);

                    break;

                default :
                    printf("\tStream Type error\n");
            }
        }

        printf("\n");
    }

    printf("\n");
}

HI_S32 HiPsiGetProgramInfo(HI_U32 DmxId, HiPmtInfo *PmtData)
{
    HiPatInfo           PatInfo;
    HiDemuxFilterInfo   DmxFltInfo;
    HI_S32              Filter;
    HI_U32              i;

    PmtData->PmtCount = 0;

    for (i = 0; i < HI_PMT_COUNT; i++)
    {
        PmtData->PmtInfo[i].PmtPid      = HI_INVALID_PID;
        PmtData->PmtInfo[i].ProgNum     = HI_DEMUX_INVALID_PROGRAM_NUMBER;
        PmtData->PmtInfo[i].VerNum      = INVALID_VERSION_NUMBER;
        PmtData->PmtInfo[i].PcrPid      = HI_INVALID_PID;
        PmtData->PmtInfo[i].Programs    = 0;
    }

    PatInfo.VerNum  = INVALID_VERSION_NUMBER;
    PatInfo.Pmts    = 0;

    DmxFltInfo.Pid          = PAT_PID;
    DmxFltInfo.Depth        = 1;
    DmxFltInfo.Match[0]     = PAT_TABLE_ID;
    DmxFltInfo.Mask[0]      = 0x00;
    DmxFltInfo.Negate[0]    = 0x00;
    DmxFltInfo.Func         = PsiParsePat;
    DmxFltInfo.Param        = (HI_VOID*)&PatInfo;

    Filter = HiDemuxAddFilter(DmxId, &DmxFltInfo);
    if (HI_FAILURE == Filter)
    {
        return HI_FAILURE;
    }

    for (i = 0; i < 100; i++)
    {
        usleep(100 * 1000);

        if (INVALID_VERSION_NUMBER != PatInfo.VerNum)
        {
            break;
        }
    }

    HiDemuxRemoveFilter(Filter);

    if (0 == PatInfo.Pmts)
    {
        printf("[%s] not PAT\n", __FUNCTION__);

        return HI_FAILURE;
    }

    for (i = 0; i < PatInfo.Pmts; i++)
    {
        HI_U32      pid     = PatInfo.Pmt[i].PmtPid;
        HI_U32      ProgNum = PatInfo.Pmt[i].ProgNum;
        HiPmtData  *pmt     = &PmtData->PmtInfo[PmtData->PmtCount];
        HI_U32      j;

        if (HI_INVALID_PID == pid)
        {
            break;
        }

        pmt->PmtPid = pid;

        DmxFltInfo.Pid          = pid;
        DmxFltInfo.Depth        = 3;
        DmxFltInfo.Match[0]     = PMT_TABLE_ID;
        DmxFltInfo.Mask[0]      = 0x00;
        DmxFltInfo.Negate[0]    = 0x00;
        DmxFltInfo.Match[1]     = (ProgNum >> 8) & 0xff;
        DmxFltInfo.Mask[1]      = 0x00;
        DmxFltInfo.Negate[1]    = 0x00;
        DmxFltInfo.Match[2]     = ProgNum & 0xff;
        DmxFltInfo.Mask[2]      = 0x00;
        DmxFltInfo.Negate[2]    = 0x00;
        DmxFltInfo.Func         = PsiParsePmt;
        DmxFltInfo.Param        = (HI_VOID*)pmt;

        Filter = HiDemuxAddFilter(DmxId, &DmxFltInfo);
        if (HI_FAILURE != Filter)
        {
            for (j = 0; j < 100; j++)
            {
                usleep(100 * 1000);

                if (INVALID_VERSION_NUMBER != pmt->VerNum)
                {
                    ++PmtData->PmtCount;

                    break;
                }
            }

            HiDemuxRemoveFilter(Filter);
        }
    }

    if (0 == PmtData->PmtCount)
    {
        printf("[%s] not program\n", __FUNCTION__);

        return HI_FAILURE;
    }

    ShowProgram(&PatInfo, PmtData);

    return HI_SUCCESS;
}

HI_S32 HiPsiInit(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 HiPsiDeInit(HI_VOID)
{
    return HI_SUCCESS;
}

