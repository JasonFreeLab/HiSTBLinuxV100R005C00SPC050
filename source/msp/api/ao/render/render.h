/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __MPI_RENDER_H__
#define  __MPI_RENDER_H__

#include "hi_unf_sound.h"
#include "hi_mpi_ao.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define RBUFFER_ERR_BUFFER_FULL (0x80000001)

HI_BOOL RENDER_IsRenderFormat(const HA_FORMAT_E enFormat);

HI_S32  RENDER_CheckIsFormatSupport(const HA_FORMAT_E enFormat, HI_BOOL* pbSupport);

HI_S32  RENDER_FoundSupportDecoder(const HA_FORMAT_E enFormat, HI_U32* pu32DstCodecID);

HI_BOOL RENDER_CheckIsRenderType(HI_UNF_SND_TRACK_TYPE_E enType);

HI_BOOL RENDER_CheckTrack(HI_HANDLE hTrack);

HI_BOOL RENDER_CheckIsMediaTrack(HI_HANDLE hTrack);

HI_BOOL RENDER_CheckIsMediaTrackCreated(HI_HANDLE hTrack);

HI_S32  RENDER_ApplyTrackID(const HI_MPI_AO_RENDER_ATTR_S* pstRenderTrackAttr, HI_HANDLE* phTrack);

HI_S32  RENDER_DeApplyTrackID(HI_HANDLE hTrack);

HI_S32  RENDER_CreateTrackWithID(HI_HANDLE hTrack);

HI_S32  RENDER_DestroyTrackWithID(HI_HANDLE hTrack);

HI_S32  RENDER_CreateTrack(HI_UNF_SND_E enSound, const HI_MPI_AO_RENDER_ATTR_S* pstRenderTrackAttr, HI_HANDLE* phTrack);

HI_S32  RENDER_DestroyTrack(HI_HANDLE hTrack);

HI_S32  RENDER_SetTrackAttr(HI_HANDLE hTrack, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr);

HI_S32  RENDER_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr);

HI_S32  RENDER_SetTrackCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd);

HI_S32  RENDER_SetTrackConfig(HI_HANDLE hTrack, HI_VOID* pConfig);

HI_S32  RENDER_GetTrackConfig(HI_HANDLE hTrack, HI_VOID* pConfig);

HI_S32  RENDER_AttachTrack(HI_HANDLE hTrack, HI_HANDLE hSrcTrack);

HI_S32  RENDER_DeAttachTrack(HI_HANDLE hTrack, HI_HANDLE hSrcTrack);

HI_S32  RENDER_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr);

HI_S32  RENDER_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame);

HI_S32  RENDER_SendStream(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs);

HI_S32  RENDER_GetBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream);

HI_S32  RENDER_PutBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs);

HI_S32  RENDER_StartTrack(HI_HANDLE hTrack);

HI_S32  RENDER_StopTrack(HI_HANDLE hTrack);

HI_S32  RENDER_PauseTrack(HI_HANDLE hTrack);

HI_S32  RENDER_FlushTrack(HI_HANDLE hTrack);

HI_S32  RENDER_GetTrackPts(HI_HANDLE hTrack, HI_U32* pu32Pts);

HI_S32  RENDER_DropTrackStream(const HI_HANDLE hTrack, HI_U32 u32SeekPts);

HI_S32  RENDER_SetTargetPts(const HI_HANDLE hTrack, HI_U32 u32TargetPts);

HI_S32  RENDER_GetTargetPts(const HI_HANDLE hTrack, HI_U32* pu32TargetPts);

HI_S32  RENDER_DropFrame(const HI_HANDLE hTrack, HI_U32 u32FrameCnt);

HI_S32  RENDER_SetSyncMode(const HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode);

HI_S32  RENDER_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs);

HI_S32  RENDER_GetInfo(const HI_HANDLE hTrack, HI_MPI_TRACK_INFO_E enInfoCmd, HI_VOID* pTrackInfo);

HI_S32  RENDER_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag);

HI_S32  RENDER_CheckNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
