/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_source.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __RENDER_SOURCE_H__
#define  __RENDER_SOURCE_H__

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_BOOL Source_CheckTrack(HI_HANDLE hTrack);

HI_BOOL Source_CheckIsNeedLoadRenderLib(HI_HANDLE hTrack);

HI_BOOL Source_CheckIsMediaTrack(HI_HANDLE hTrack);

HI_BOOL Source_CheckIsMediaTrackAlloced(HI_HANDLE hTrack);

HI_BOOL Source_CheckIsMediaTrackCreated(HI_HANDLE hTrack);

HI_S32  Source_Init(RENDER_MANAGER_S* pstRenderManager);

HI_S32  Source_Deinit(HI_VOID);

HI_S32  Source_ApllyID(const HI_MPI_AO_RENDER_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack);

HI_S32 Source_DeApllyID(HI_HANDLE hTrack);

HI_S32  Source_CreateWithID(HI_HANDLE hTrack);

HI_S32  Source_DestroyTrackWithID(HI_HANDLE hTrack);

HI_S32  Source_Create(HI_UNF_SND_E enSound, const HI_MPI_AO_RENDER_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack);

HI_S32  Source_DestroyTrack(HI_HANDLE hTrack);

HI_S32  Source_SetTrackConfig(HI_HANDLE hTrack, HI_U32 u32cfgType, const HI_VOID* pstConfig);

HI_S32  Source_GetTrackConfig(HI_HANDLE hTrack, HI_U32 u32cfgType, HI_VOID* pstConfig);

HI_S32  Source_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr);

HI_S32  Source_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame);

HI_S32  Source_SendStream(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs);

HI_S32  Source_GetBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream);

HI_S32  Source_PutBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs);

HI_S32  Source_StartTrack(HI_HANDLE hTrack);

HI_S32  Source_StopTrack(HI_HANDLE hTrack);

HI_S32  Source_PauseTrack(HI_HANDLE hTrack);

HI_S32  Source_FlushTrack(HI_HANDLE hTrack);

HI_S32  Source_GetSourceID(HI_HANDLE hTrack, SOURCE_ID_E* penSourceID);

HI_S32  Source_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts);

HI_S32  Source_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt);

HI_S32  Source_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode);

HI_S32  Source_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs);

HI_S32  Source_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag);

HI_S32  Source_GetEosState(HI_HANDLE hTrack, HI_BOOL* bEosState);

HI_S32  Source_GetBufferStatus(HI_HANDLE hTrack, HI_MPI_AO_RENDER_BUFSTATUS_S* pstBufStatus);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
