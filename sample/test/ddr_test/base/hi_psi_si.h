
#ifndef __HI_PSI_SI_H__
#define __HI_PSI_SI_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STREAM_TYPE_11172_VIDEO     0x01    // MPEG1
#define STREAM_TYPE_13818_VIDEO     0x02    // MPEG2
#define STREAM_TYPE_14496_2_VIDEO   0x10    // MPEG4
#define STREAM_TYPE_14496_10_VIDEO  0x1B    // H264
#define STREAM_TYPE_AVS_VIDEO       0x42    // AVS
#define STREAM_TYPE_HEVC_VIDEO      0x24    // H265

#define STREAM_TYPE_11172_AUDIO     0x03    // MPEG1
#define STREAM_TYPE_13818_AUDIO     0x04    // MPEG2
#define STREAM_TYPE_13818_7_AUDIO   0x0F    // AAC
#define STREAM_TYPE_14496_3_AUDIO   0x11    // AAC
#define STREAM_TYPE_AC3_AUDIO       0x81    // AC3

#define STREAM_TYPE_PRIVATE         0x06    // PES packets containing private data

#define HI_PMT_COUNT        (256)
#define HI_PROGRAM_COUNT    (32)

typedef struct
{
    HI_U32 Type;
    HI_U32 Pid;
} HiStreamInfo;

typedef struct
{
    HI_U32          PmtPid;
    HI_U32          ProgNum;
    HI_U32          VerNum;
    HI_U32          PcrPid;
    HI_U32          Programs;
    HiStreamInfo    ProgInfo[HI_PMT_COUNT];
} HiPmtData;

typedef struct
{
    HI_U32      PmtCount;               // PMT表的个数
    HiPmtData   PmtInfo[HI_PMT_COUNT];  // PMT表数据
} HiPmtInfo;

HI_S32  HiPsiGetProgramInfo(HI_U32 DmxId, HiPmtInfo *PmtInfo);
HI_S32  HiPsiInit(HI_VOID);
HI_S32  HiPsiDeInit(HI_VOID);

#ifdef __cplusplus
}
#endif

#endif

