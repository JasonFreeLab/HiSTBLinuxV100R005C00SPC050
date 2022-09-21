/************************************************************************************\
\*              Copyright 2004 - 2050, Hisilicon Tech. Co., Ltd.                    *\
\*                           ALL RIGHTS RESERVED                                    *\
\************************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_unf_demux.h"

#include "hi_demux.h"

#define HI_INVALID_DEMUX_ID         (0xFFFF)
#define HI_INVALID_PORT_ID          (0xFFFF)

typedef struct
{
    HI_U32      DmxId;
    HI_HANDLE   Chan;
    HI_U32      ChanPid;
} HiDmxChanInfo;

typedef struct
{
    HI_HANDLE           Chan;
    HI_HANDLE           Filter;
    HI_U32              Depth;
    HI_U8               Match[DMX_FILTER_MAX_DEPTH];
    HI_U8               Mask[DMX_FILTER_MAX_DEPTH];
    HI_U8               Negate[DMX_FILTER_MAX_DEPTH];
    DemuxDataProcess    Func;
    HI_VOID            *Param;
} HiDmxFilterInfo;

typedef struct
{
    HI_U32              DmxNum;
    HI_U32              RamPortNum;
    HI_U32             *RamPort;
    HI_U32              ChanNum;
    HiDmxChanInfo      *ChanInfo;
    HI_U32              FilterNum;
    HiDmxFilterInfo    *FilterInfo;
    pthread_mutex_t     DmxMutex;
} HiDmxInfo;

static HiDmxInfo    DmxInfo             = {0};
static HI_S32       DmxThreadRunFlag    = HI_THREAD_SLEEP;
static pthread_t    DmxThreadId         = 0;

static HI_VOID ResetChannel(HiDmxChanInfo *ChanInfo)
{
    pthread_mutex_lock(&DmxInfo.DmxMutex);
    ChanInfo->DmxId     = HI_INVALID_DEMUX_ID;
    ChanInfo->Chan      = HI_INVALID_HANDLE;
    ChanInfo->ChanPid   = HI_INVALID_PID;
    pthread_mutex_unlock(&DmxInfo.DmxMutex);
}

static HI_VOID ResetFilter(HiDmxFilterInfo *FilterInfo)
{
    pthread_mutex_lock(&DmxInfo.DmxMutex);
    FilterInfo->Filter  = HI_INVALID_HANDLE;
    FilterInfo->Chan    = HI_INVALID_HANDLE;
    pthread_mutex_unlock(&DmxInfo.DmxMutex);
}

static HI_BOOL HiDemuxDataMatchFilter(HiDmxFilterInfo *FilterInfo, HI_U8 *buf, HI_U32 len)
{
    HI_BOOL     ret = HI_TRUE;
    HI_U8      *ptr = buf;
    HI_U8      *end = buf + len;
    HI_U32      i   = 0;

    while ((i < FilterInfo->Depth) && (ptr < end))
    {
        if (FilterInfo->Negate[i])
        {
            if (FilterInfo->Match[i] == (*ptr & ~FilterInfo->Mask[i]))
            {
                ret = HI_FALSE;

                break;
            }
        }
        else
        {
            if (FilterInfo->Match[i] != (*ptr & ~FilterInfo->Mask[i]))
            {
                ret = HI_FALSE;

                break;
            }
        }

        if (0 != i)
        {
            ++ptr;
        }
        else
        {
            ptr += 3;
        }

        ++i;
    }

    return ret;
}

static HI_VOID *HiDemuxDataTask(HI_VOID *Para)
{
    while (HI_THREAD_EXIT != DmxThreadRunFlag)
    {
        HI_S32      ret;
        HI_HANDLE   Chan[64];
        HI_U32      ChanCnt = sizeof(Chan) / sizeof(Chan[0]);
        HI_U32      i;

        if (HI_THREAD_SLEEP == DmxThreadRunFlag)
        {
            usleep(10 * 1000);

            continue;
        }

        ret = HI_UNF_DMX_GetDataHandle(Chan, &ChanCnt, 100);
        if (HI_SUCCESS != ret)
        {
            continue;
        }

        for (i = 0; i < ChanCnt; i++)
        {
            HI_U32              j;
            HI_UNF_DMX_DATA_S   DmxData[8];
            HI_U32              AcquireNum  = sizeof(DmxData) / sizeof(DmxData[0]);
            HI_U32              DataNum     = 0;

            pthread_mutex_lock(&DmxInfo.DmxMutex);

            ret = HI_UNF_DMX_AcquireBuf(Chan[i], AcquireNum, &DataNum, DmxData, 0);
            if (HI_SUCCESS != ret)
            {
                printf("[%s] HI_UNF_DMX_AcquireBuf failed 0x%x\n", __FUNCTION__, ret);

                pthread_mutex_unlock(&DmxInfo.DmxMutex);

                continue;
            }

            for (j = 0; j < DataNum; j++)
            {
                HI_U8  *buf = DmxData[j].pu8Data;
                HI_U32  len = DmxData[j].u32Size;
                HI_U32  k;

                for (k = 0; k < DmxInfo.FilterNum; k++)
                {
                    HiDmxFilterInfo *FilterInfo = &DmxInfo.FilterInfo[k];

                    if (FilterInfo->Chan != Chan[i])
                    {
                        continue;
                    }

                    if (HiDemuxDataMatchFilter(FilterInfo, buf, len))
                    {
                        if (FilterInfo->Func)
                        {
                            (FilterInfo->Func)(buf, len, FilterInfo->Param);
                        }
                    }
                }
            }

            ret = HI_UNF_DMX_ReleaseBuf(Chan[i], DataNum, DmxData);
            if (HI_SUCCESS != ret)
            {
                printf("[%s] HI_UNF_DMX_ReleaseBuf failed 0x%x\n", __FUNCTION__, ret);
            }

            pthread_mutex_unlock(&DmxInfo.DmxMutex);
        }
    }

    return HI_NULL;
}

HI_S32 HiDemuxInit(HI_VOID)
{
    HI_S32                  ret;
    HI_UNF_DMX_CAPABILITY_S DmxCap;
    HI_U32                  size;
    HI_U32                  *pMem;
    HI_U32                  i;

    ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_Init failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_DMX_GetCapability(&DmxCap);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_GetCapability failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    pthread_mutex_init(&DmxInfo.DmxMutex, HI_NULL);

    size = DmxCap.u32RamPortNum * sizeof(HI_U32);
    size += DmxCap.u32ChannelNum * sizeof(HiDmxChanInfo);
    size += DmxCap.u32FilterNum * sizeof(HiDmxFilterInfo);

    pMem = (HI_U32 *)malloc(size);
    if (HI_NULL == pMem)
    {
        printf("[%s] allocate memory 0x%x bytes failed\n", __FUNCTION__, size);

        return HI_FAILURE;
    }

    memset(pMem, 0, size);

    DmxInfo.DmxNum      = DmxCap.u32DmxNum;
    DmxInfo.RamPortNum  = DmxCap.u32RamPortNum;
    DmxInfo.ChanNum     = DmxCap.u32ChannelNum;
    DmxInfo.FilterNum   = DmxCap.u32FilterNum;
    DmxInfo.RamPort     = pMem;
    DmxInfo.ChanInfo    = (HiDmxChanInfo*)(DmxInfo.RamPort + DmxInfo.RamPortNum);
    DmxInfo.FilterInfo  = (HiDmxFilterInfo*)(DmxInfo.ChanInfo + DmxInfo.ChanNum);

    for (i = 0; i < DmxInfo.RamPortNum; i++)
    {
        DmxInfo.RamPort[i] = 0;
    }

    for (i = 0; i < DmxInfo.ChanNum; i++)
    {
        DmxInfo.ChanInfo[i].DmxId   = HI_INVALID_DEMUX_ID;
        DmxInfo.ChanInfo[i].Chan    = HI_INVALID_HANDLE;
        DmxInfo.ChanInfo[i].ChanPid = HI_INVALID_PID;
    }

    for (i = 0; i < DmxInfo.FilterNum; i++)
    {
        DmxInfo.FilterInfo[i].Filter    = HI_INVALID_HANDLE;
        DmxInfo.FilterInfo[i].Chan      = HI_INVALID_HANDLE;
    }

    DmxThreadRunFlag = HI_THREAD_RUNNING;

    ret = pthread_create(&DmxThreadId, HI_NULL, HiDemuxDataTask, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] pthread_create error\n", __FUNCTION__);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HiDemuxDeInit(HI_VOID)
{
    HI_S32 ret;

    DmxThreadRunFlag = HI_THREAD_EXIT;

    pthread_join(DmxThreadId, HI_NULL);

    free((HI_VOID*)DmxInfo.RamPort);

    ret = HI_UNF_DMX_DeInit();
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_DeInit failed 0x%x\n", __FUNCTION__, ret);
    }

    return ret;
}

HI_VOID* TsFileSendThread(HI_VOID *arg)
{
    HI_S32      ret;
    HI_HANDLE   TsBuffer;
    FILE       *TsFp    = HI_NULL;
    TsFileInfo *Ts      = (TsFileInfo*)arg;
    HI_U32      Size    = 256 * 188;

    if (!Ts)
    {
        goto exit;
    }

    printf("[%s] open %s\n", __FUNCTION__, Ts->FileName);

    TsFp = fopen(Ts->FileName, "rb");
    if (!TsFp)
    {
        perror("[TsFileSendThread] fopen error");

        goto exit;
    }

    ret = HI_UNF_DMX_CreateTSBuffer(Ts->PortId, Ts->TsBufferSize, &TsBuffer);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_CreateTSBuffer failed 0x%x\n", __FUNCTION__, ret);

        goto exit;
    }

    usleep(10 * 1000);

    while (HI_THREAD_EXIT != Ts->RunFlag)
    {
        HI_UNF_STREAM_BUF_S StreamBuf = {HI_NULL, 0};

        if (HI_THREAD_SLEEP == Ts->RunFlag)
        {
            rewind(TsFp);

            ret = HI_UNF_DMX_ResetTSBuffer(TsBuffer);
            if (HI_SUCCESS != ret)
            {
                printf("[%s] HI_UNF_DMX_ResetTSBuffer failed 0x%x\n", __FUNCTION__, ret);
            }

            usleep(50 * 1000);

            continue;
        }

        ret = HI_UNF_DMX_GetTSBuffer(TsBuffer, Size, &StreamBuf, 100);
        if (HI_SUCCESS != ret)
        {
            if ((HI_ERR_DMX_TIMEOUT == ret) || (HI_ERR_DMX_NOAVAILABLE_BUF == ret))
            {
                continue;
            }

            printf("[%s] HI_UNF_DMX_GetTSBuffer failed 0x%x\n", __FUNCTION__, ret);

            continue;
        }

        if ((HI_NULL == StreamBuf.pu8Data) || (StreamBuf.u32Size != Size))
        {
            continue;
        }

        ret = fread(StreamBuf.pu8Data, 1, StreamBuf.u32Size, TsFp);
        if (0 == ret)
        {
            if (Ts->Rewind)
            {
                rewind(TsFp);

                continue;
            }

            break;
        }

        if (ret < 0)
        {
            perror("[TsFileSendThread] fread error");

            break;
        }

        ret = HI_UNF_DMX_PutTSBuffer(TsBuffer, ret);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DMX_PutTSBuffer failed 0x%x\n", __FUNCTION__, ret);
        }

        if (Ts->SleepMs)
        {
            usleep(Ts->SleepMs * 1000);
        }
    }

    ret = HI_UNF_DMX_DestroyTSBuffer(TsBuffer);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_DestroyTSBuffer failed 0x%x\n", __FUNCTION__, ret);
    }

exit :
    if (TsFp)
    {
        fclose(TsFp);
    }

    Ts->RunFlag = HI_THREAD_EXIT;

    return HI_NULL;
}

HI_S32 HiDemuxMallocRamPortId(HI_U32 *PortId)
{
    HI_S32  ret = HI_FAILURE;
    HI_U32  i;

    if (HI_NULL == PortId)
    {
        return HI_FAILURE;
    }

    pthread_mutex_lock(&DmxInfo.DmxMutex);

    for (i = 0; i < DmxInfo.RamPortNum; i++)
    {
        if (0 == DmxInfo.RamPort[i])
        {
            DmxInfo.RamPort[i] = 1;

            *PortId = HI_UNF_DMX_PORT_RAM_0 + i;

            ret = HI_SUCCESS;

            break;
        }
    }

    pthread_mutex_unlock(&DmxInfo.DmxMutex);

    return ret;
}

HI_S32 HiDemuxFreeRamPortId(HI_U32 PortId)
{
    HI_S32  ret     = HI_FAILURE;
    HI_U32  RamId   = PortId - HI_UNF_DMX_PORT_RAM_0;

    pthread_mutex_lock(&DmxInfo.DmxMutex);

    if (RamId < DmxInfo.RamPortNum)
    {
        DmxInfo.RamPort[RamId] = 0;

        ret = HI_SUCCESS;
    }

    pthread_mutex_unlock(&DmxInfo.DmxMutex);

    return ret;
}

HI_S32 HiDemuxAddFilter(HI_U32 DmxId, HiDemuxFilterInfo *DmxFltInfo)
{
    HI_S32                      ret;
    HiDmxChanInfo              *ChanInfo    = HI_NULL;
    HiDmxFilterInfo            *FilterInfo  = HI_NULL;
    HI_UNF_DMX_CHAN_ATTR_S      ChanAttr;
    HI_UNF_DMX_FILTER_ATTR_S    FilterAttr;
    HI_HANDLE                   Channel     = HI_INVALID_HANDLE;
    HI_HANDLE                   Filter      = HI_INVALID_HANDLE;
    HI_U32                      NewChanFlag = 0;
    HI_U32                      i;

    pthread_mutex_lock(&DmxInfo.DmxMutex);

    for (i = 0; i < DmxInfo.ChanNum; i++)
    {
        if ((DmxInfo.ChanInfo[i].DmxId == DmxId) && (DmxInfo.ChanInfo[i].ChanPid == DmxFltInfo->Pid))
        {
            ChanInfo = &DmxInfo.ChanInfo[i];

            break;
        }
    }

    if (HI_NULL == ChanInfo)
    {
        for (i = 0; i < DmxInfo.ChanNum; i++)
        {
            if (HI_INVALID_DEMUX_ID == DmxInfo.ChanInfo[i].DmxId)
            {
                ChanInfo = &DmxInfo.ChanInfo[i];

                ChanInfo->DmxId     = DmxId;
                ChanInfo->ChanPid   = DmxFltInfo->Pid;

                NewChanFlag = 1;

                break;
            }
        }
    }

    pthread_mutex_unlock(&DmxInfo.DmxMutex);

    if (HI_NULL == ChanInfo)
    {
        printf("[%s] error: no free channel\n", __FUNCTION__);

        return HI_FAILURE;
    }

    if (NewChanFlag)
    {
        HI_UNF_DMX_GetChannelDefaultAttr(&ChanAttr);

        ret = HI_UNF_DMX_CreateChannel(DmxId, &ChanAttr, &Channel);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DMX_CreateChannel failed 0x%x\n", __FUNCTION__, ret);

            ResetChannel(ChanInfo);

            return -1;
        }

        ret = HI_UNF_DMX_SetChannelPID(Channel, DmxFltInfo->Pid);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DMX_SetChannelPID failed 0x%x\n", __FUNCTION__, ret);

            HI_UNF_DMX_DestroyChannel(Channel);
            ResetChannel(ChanInfo);

            return -1;
        }

        ret = HI_UNF_DMX_OpenChannel(Channel);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DMX_OpenChannel failed 0x%x\n", __FUNCTION__, ret);

            HI_UNF_DMX_DestroyChannel(Channel);
            ResetChannel(ChanInfo);

            return -1;
        }


        pthread_mutex_lock(&DmxInfo.DmxMutex);
        ChanInfo->Chan = Channel;
        pthread_mutex_unlock(&DmxInfo.DmxMutex);
    }

    pthread_mutex_lock(&DmxInfo.DmxMutex);
    for (i = 0; i < DmxInfo.FilterNum; i++)
    {
        if (HI_INVALID_HANDLE == DmxInfo.FilterInfo[i].Chan)
        {
            FilterInfo = &DmxInfo.FilterInfo[i];

            FilterInfo->Chan = Channel;

            break;
        }
    }
    pthread_mutex_unlock(&DmxInfo.DmxMutex);

    if (HI_NULL == FilterInfo)
    {
        if (NewChanFlag)
        {
            HI_UNF_DMX_CloseChannel(Channel);
            HI_UNF_DMX_DestroyChannel(Channel);
            ResetChannel(ChanInfo);
        }

        return -1;
    }

    FilterAttr.u32FilterDepth = (DmxFltInfo->Depth < DMX_FILTER_MAX_DEPTH) ? DmxFltInfo->Depth : DMX_FILTER_MAX_DEPTH;

    for (i = 0; i < FilterAttr.u32FilterDepth; i++)
    {
        FilterAttr.au8Match[i]  = DmxFltInfo->Match[i];
        FilterAttr.au8Mask[i]   = DmxFltInfo->Mask[i];
        FilterAttr.au8Negate[i] = DmxFltInfo->Negate[i];
    }


    ret = HI_UNF_DMX_CreateFilter(DmxId, &FilterAttr, &Filter);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_CreateFilter failed 0x%x\n", __FUNCTION__, ret);

        ResetFilter(FilterInfo);

        if (NewChanFlag)
        {
            HI_UNF_DMX_CloseChannel(Channel);
            HI_UNF_DMX_DestroyChannel(Channel);
            ResetChannel(ChanInfo);
        }

        return -1;
    }

    ret = HI_UNF_DMX_AttachFilter(Filter, Channel);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_AttachFilter failed 0x%x\n", __FUNCTION__, ret);

        HI_UNF_DMX_DestroyFilter(Filter);
        ResetFilter(FilterInfo);

        if (NewChanFlag)
        {
            HI_UNF_DMX_CloseChannel(Channel);
            HI_UNF_DMX_DestroyChannel(Channel);
            ResetChannel(ChanInfo);
        }

        return -1;
    }

    pthread_mutex_lock(&DmxInfo.DmxMutex);
    FilterInfo->Chan    = Channel;
    FilterInfo->Filter  = Filter;
    FilterInfo->Depth   = FilterAttr.u32FilterDepth;
    FilterInfo->Func    = DmxFltInfo->Func;
    FilterInfo->Param   = DmxFltInfo->Param;
    memcpy(FilterInfo->Match,   FilterAttr.au8Match, FilterAttr.u32FilterDepth);
    memcpy(FilterInfo->Mask,    FilterAttr.au8Mask, FilterAttr.u32FilterDepth);
    memcpy(FilterInfo->Negate,  FilterAttr.au8Negate, FilterAttr.u32FilterDepth);
    pthread_mutex_unlock(&DmxInfo.DmxMutex);

    return Filter;
}

HI_S32 HiDemuxRemoveFilter(HI_U32 Filter)
{
    HI_S32              ret;
    HiDmxChanInfo      *ChanInfo    = HI_NULL;
    HiDmxFilterInfo    *FilterInfo  = HI_NULL;
    HI_HANDLE           Channel;
    HI_U32              i;

    pthread_mutex_lock(&DmxInfo.DmxMutex);
    for (i = 0; i < DmxInfo.FilterNum; i++)
    {
        if (Filter == DmxInfo.FilterInfo[i].Filter)
        {
            FilterInfo = &DmxInfo.FilterInfo[i];

            break;
        }
    }
    pthread_mutex_unlock(&DmxInfo.DmxMutex);

    if (HI_NULL == FilterInfo)
    {
        return -1;
    }

    Channel = FilterInfo->Chan;

    ret = HI_UNF_DMX_DetachFilter(Filter, Channel);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_DetachFilter failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ret = HI_UNF_DMX_DestroyFilter(Filter);
    if (HI_SUCCESS != ret)
    {
        printf("[%s] HI_UNF_DMX_DestroyFilter failed 0x%x\n", __FUNCTION__, ret);

        return HI_FAILURE;
    }

    ResetFilter(FilterInfo);

    pthread_mutex_lock(&DmxInfo.DmxMutex);
    for (i = 0; i < DmxInfo.FilterNum; i++) // 查找有没有其他过滤器使用此通道
    {
        if (Channel == DmxInfo.FilterInfo[i].Chan)
        {
            break;
        }
    }

    if (i == DmxInfo.FilterNum) // 没有其他过滤器使用此通道时将通道删除
    {
        for (i = 0; i < DmxInfo.ChanNum; i++)
        {
            if (Channel == DmxInfo.ChanInfo[i].Chan)
            {
                ChanInfo = &DmxInfo.ChanInfo[i];

                break;
            }
        }

        if (i == DmxInfo.ChanNum)
        {
            printf("[%s] error: chan 0x%x not found\n", __FUNCTION__, Channel);
        }
    }
    pthread_mutex_unlock(&DmxInfo.DmxMutex);

    if (ChanInfo)
    {
        ResetChannel(ChanInfo);

        ret = HI_UNF_DMX_CloseChannel(Channel);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DMX_CloseChannel failed 0x%x\n", __FUNCTION__, ret);

            return HI_FAILURE;
        }

        ret = HI_UNF_DMX_DestroyChannel(Channel);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DMX_DestroyChannel failed 0x%x\n", __FUNCTION__, ret);

            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

