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

#ifndef  __RENDER_ENGINE_H__
#define  __RENDER_ENGINE_H__

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_S32  Engine_Init(RENDER_MANAGER_S* pstRenderManager);

HI_S32  Engine_Deinit(HI_VOID);

HI_S32  Engine_Create(HI_VOID);

HI_VOID Engine_Destroy(HI_VOID);

HI_S32  Engine_LoadRenderLib(HI_VOID);

HI_S32  Engine_DropTrackStream(const SOURCE_ID_E enSourceID, HI_U32 u32SeekPts);

HI_S32  Engine_SetAttr(const SOURCE_ID_E enSourceID, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr);

HI_S32  Engine_SetCmd(const SOURCE_ID_E enSourceID, HI_VOID* pstRenderCmd);

HI_S32  Engine_AttachExtSinkTrack(const SOURCE_ID_E enSourceID, HI_HANDLE hExtSinkTrack);

HI_S32  Engine_DeAttachExtSinkTrack(const SOURCE_ID_E enSourceID, HI_HANDLE hSrcTrack);

HI_S32  Engine_SetTrackConfig(const SOURCE_ID_E enSourceID, HI_VOID* pConfig);

HI_S32  Engine_GetTrackConfig(const SOURCE_ID_E enSourceID, HI_VOID* pConfig);

HI_S32  Engine_GetTrackPts(const SOURCE_ID_E enSourceID, HI_U32* pu32Pts);

HI_S32  Engine_GetSinkDelayMs(HI_U32* pu32DelayMs);

HI_S32  Engine_ResetDecoder(const SOURCE_ID_E enSourceID);

HI_S32  Engine_SetEosFlag(const SOURCE_ID_E enSourceID, HI_BOOL bEosFlag);

HI_S32  Engine_GetCapability(HI_U32* pu32Capability);

HI_S32  Engine_GetCmd(HI_VOID* pstRenderCmd);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
