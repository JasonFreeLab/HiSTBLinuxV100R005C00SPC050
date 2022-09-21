/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : omx_audio_common.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __OMX_AUDIO_COMMON_H__
#define __OMX_AUDIO_COMMON_H__

#include "omx_audio_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


OMX_ERRORTYPE OMX_AUDIO_COMMON_Init(OMX_HANDLETYPE Handle, HI_AUDDATATYPE** ppAudioData);

HI_VOID       OMX_AUDIO_COMMON_DeInit(HI_AUDDATATYPE* pAudioData);

OMX_ERRORTYPE OMX_AUDIO_COMMON_StartDecode(HI_AUDDATATYPE* pAudioData);

OMX_ERRORTYPE OMX_AUDIO_COMMON_StopDecode(HI_AUDDATATYPE* pAudioData);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

