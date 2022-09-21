/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_engine.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dlfcn.h>

#include "omx_audio_proc.h"
#include "omx_audio_base.h"
#include "hi_common.h"


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#define PROC_OMXAUDIO_NAME_LENGTH     (8)   // The leng can not change, depend on the leng of PROC_OMXAUDIO_NODE_NAME
#define PROC_OMXAUDIO_MAXNUM          (3)

#define PROC_OMXAUDIO_DIR_NAME        "msp"
#define PROC_OMXAUDIO_NODE_NAME       "audomx0"
#define PROC_OMXAUDIO_LONG_DIR_NAME   "/proc/hisi/msp"
#define PROC_OMXAUDIO_ABSOLUTE_PATH   "/proc/msp/audomx0"


static HI_S32 ProcShowInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    HI_AUDDATATYPE* pHAData = (HI_AUDDATATYPE*)pPrivData;

    HI_PROC_Printf(pstBuf, "\n----------------------  OMX Audio  --------------------\n");
    HI_PROC_Printf(pstBuf, "    Passthrough:                   :%d\n", pHAData->stAdec.bPassThrough);
    HI_PROC_Printf(pstBuf, "    UseInnerBuf:                   :%d\n", pHAData->bInnerBufFlag);
    HI_PROC_Printf(pstBuf, "    SamplesPerFrame:               :%d\n", pHAData->sPcm.nSize);
    HI_PROC_Printf(pstBuf, "    Channels:                      :%d\n", pHAData->sPcm.nChannels);
    HI_PROC_Printf(pstBuf, "    SampleRate:                    :%d\n", pHAData->sPcm.nSamplingRate);
    HI_PROC_Printf(pstBuf, "    AnchorTimeMs:                  :%lld\n", pHAData->mAnchorTimeUs / 1000);

    return HI_SUCCESS;
}

static HI_S32 ProcSetCmd(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_U32 u32Argc, HI_U8* pu8Argv[], HI_VOID* pPrivData)
{
    HA_UNUSED_PARAMETER(pstBuf);
    HA_UNUSED_PARAMETER(u32Argc);
    HA_UNUSED_PARAMETER(pu8Argv);
    HA_UNUSED_PARAMETER(pPrivData);

    return HI_SUCCESS;
}

static HI_S32 ProcFindAvalidDirIndex(HI_U8* pu8Index)
{
    HI_U8 u8Index = 0;
    HI_CHAR aPathName[20];

    memset(aPathName, 0, sizeof(aPathName));
    strncpy(aPathName, PROC_OMXAUDIO_ABSOLUTE_PATH, strlen(PROC_OMXAUDIO_ABSOLUTE_PATH));

    for (u8Index = 0; u8Index < PROC_OMXAUDIO_MAXNUM; u8Index++)
    {
        aPathName[16] += u8Index;  //16 mean audomx(X)
        if (0 != access(aPathName, F_OK))
        {
            *pu8Index = u8Index;
            return HI_SUCCESS;
        }
    }

    return HI_FAILURE;
}

HI_S32 OMX_HA_PROC_Init(HI_AUDDATATYPE* pHAData)
{
    HI_S32 s32Ret;
    HI_U8  u8DirIndex = 0;
    HI_CHAR* aProcOmxName = HI_NULL;

    s32Ret = ProcFindAvalidDirIndex(&u8DirIndex);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    aProcOmxName = (HI_CHAR*)malloc(PROC_OMXAUDIO_NAME_LENGTH);
    if (HI_NULL == aProcOmxName)
    {
        return HI_FAILURE;
    }

    memset(aProcOmxName, 0, PROC_OMXAUDIO_NAME_LENGTH);
    strncpy(aProcOmxName, PROC_OMXAUDIO_NODE_NAME, strlen(PROC_OMXAUDIO_NODE_NAME));
    aProcOmxName[6] += u8DirIndex;  // 6 mean audomx(X)

    HI_SYS_Init();

    pHAData->stProcEntry.pszDirectory = PROC_OMXAUDIO_DIR_NAME;
    pHAData->stProcEntry.pszEntryName = aProcOmxName;
    pHAData->stProcEntry.pfnShowProc  = ProcShowInfo;
    pHAData->stProcEntry.pfnCmdProc   = ProcSetCmd;
    pHAData->stProcEntry.pPrivData    = pHAData;

    s32Ret = HI_PROC_AddEntry(HI_ID_AO, &pHAData->stProcEntry);
    if (HI_SUCCESS != s32Ret)
    {
        free(pHAData->stProcEntry.pszEntryName);
        pHAData->stProcEntry.pszEntryName = HI_NULL;
    }

    return s32Ret;
}

HI_VOID OMX_HA_PROC_DeInit(HI_AUDDATATYPE* pHAData)
{
    if (pHAData->stProcEntry.pszEntryName)
    {
        HI_PROC_RemoveEntry(HI_ID_AO, &pHAData->stProcEntry);

        HI_SYS_DeInit();

        free(pHAData->stProcEntry.pszEntryName);
        pHAData->stProcEntry.pszEntryName = HI_NULL;
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

