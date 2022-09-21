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

#ifndef  __ENGINE_SYNC_H__
#define  __ENGINE_SYNC_H__

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_VOID Sync_SetCodecHandle(ENGINE_CODEC_S* pstCodec);

HI_BOOL Sync_CheckIsSourceNeedDecode(SOURCE_S* pstSource);

HI_VOID Sync_Prepare(SOURCE_MANAGER_S* pstSourceManager);

HI_S32  Sync_DropStream(SOURCE_S* pstSource, HI_U32 u32SeekPts);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
