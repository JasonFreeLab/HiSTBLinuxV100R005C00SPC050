/************************************************************************************\
\*              Copyright 2004 - 2050, Hisilicon Tech. Co., Ltd.                    *\
\*                           ALL RIGHTS RESERVED                                    *\
\************************************************************************************/

#ifndef __HI_DEMUX_H__
#define __HI_DEMUX_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HI_THREAD_EXIT              -1
#define HI_THREAD_SLEEP             0
#define HI_THREAD_RUNNING           1

#define HI_DEMUX_ID_0               0   // DEMUX 0 能接收数据和播放音视频, 不能录制
#define HI_DEMUX_ID_1               1   // DEMUX 1 能接收数据和录制, 不能播放音视频
#define HI_DEMUX_ID_2               2   // DEMUX 2 能接收数据和录制, 不能播放音视频

#define HI_DEMUX_PORT_QAM           0
#define HI_DEMUX_PORT_PAD           1
#define HI_DEMUX_PORT_RAM           2

#define HI_INVALID_PID        (0x1FFF)

#define SECTION_LENGTH(a, b)        (((((a) & 0xf) << 8) | (b)) + 3)

#define HI_FILTER_MAX_DEPTH         16

typedef enum
{
    HI_DMX_MODE_NONE = 0,
    HI_DMX_MODE_PLAY,
    HI_DMX_MODE_REC
} HI_DMX_MODE_E;

typedef HI_VOID (*DemuxDataProcess)(HI_U8 *buf, HI_U32 len, HI_VOID *param);

typedef struct
{
    HI_U32              Pid;
    HI_U32              Depth;
    HI_U8               Match[HI_FILTER_MAX_DEPTH];
    HI_U8               Mask[HI_FILTER_MAX_DEPTH];
    HI_U8               Negate[HI_FILTER_MAX_DEPTH];
    DemuxDataProcess    Func;
    HI_VOID            *Param;
} HiDemuxFilterInfo;

#define MAX_FILENAME_LEN        256

typedef struct
{
    HI_U32      PortId;
    HI_U32      TsBufferSize;
    HI_CHAR     FileName[MAX_FILENAME_LEN];
    HI_BOOL     Rewind;         // 是否循环发送
    HI_U32      SleepMs;        // 每次put后延时多少毫秒
    HI_S32      RunFlag;
} TsFileInfo;

HI_S32  HiDemuxInit(HI_VOID);
HI_S32  HiDemuxDeInit(HI_VOID);

HI_VOID* TsFileSendThread(HI_VOID *arg);

HI_S32  HiDemuxMallocRamPortId(HI_U32 *PortId);
HI_S32  HiDemuxFreeRamPortId(HI_U32 PortId);

HI_S32  HiDemuxAddFilter(HI_U32 DmxId, HiDemuxFilterInfo *DmxFltInfo);
HI_S32  HiDemuxRemoveFilter(HI_U32 Filter);

#ifdef __cplusplus
}
#endif

#endif  // __HI_DEMUX_H__

