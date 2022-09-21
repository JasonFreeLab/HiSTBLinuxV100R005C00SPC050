/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_engine.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/

#ifndef  __ENGINE_CODEC_H__
#define  __ENGINE_CODEC_H__

#include "render_common.h"
#include "HA.AUDIO.DOLBYMS12.decode.h"
#include "HA.AUDIO.DOLBYMS12EXT.decode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_BOOL HACodec_CheckIsRenderLibLoaded(ENGINE_CODEC_S* pstCodec);

HI_S32  HACodec_Init(ENGINE_CODEC_S** ppstCodec);

HI_VOID HACodec_DeInit(ENGINE_CODEC_S* pstCodec);

HI_S32  HACodec_LoadRenderLib_Default(ENGINE_CODEC_S* pstCodec);

HI_S32  HACodec_LoadRenderLib(ENGINE_CODEC_S* pstCodec, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr);

HI_VOID HACodec_UnLoadRenderLib(ENGINE_CODEC_S* pstCodec);

HI_S32  HACodec_InitDecodeInfo(ENGINE_CODEC_S* pstCodec, HA_MS12_DECODE_STREAM_S* pstDecodeStream);

HI_VOID HACodec_DeInitDecodeInfo(ENGINE_CODEC_S* pstCodec);

HI_S32  HACodec_Render(ENGINE_CODEC_S* pstCodec, HI_VOID* pstConfigStructure);

HI_S32  HACodec_CtlCommand(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_VOID* pCmdData);

HI_S32  HACodec_EnableDecoder(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_BOOL bEnable);

HI_S32  HACodec_EnableMixer(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_BOOL bEnable);

HI_S32  HACodec_DropPts(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_S32 s32DropPts);

HI_S32  HACodec_DropFrame(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID, HI_U32 u32FrameCnt);

HI_VOID HACodec_UpdateDataStatus(ENGINE_CODEC_S* pstCodec, HI_BOOL* pbStreamDataEnough);

HI_BOOL HACodec_CheckIsDataAvailable(ENGINE_CODEC_S* pstCodec, SOURCE_ID_E enSourceID);

HI_S32  HACodec_SetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData);

HI_S32  HACodec_GetCmd(ENGINE_CODEC_S* pstCodec, HI_VOID* pCmdData);

HI_S32  HACodec_GetRenderLibCapability(HI_U32* pu32Capability);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
