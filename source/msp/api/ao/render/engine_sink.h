/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : engine_sink.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/

#ifndef  __ENGINE_SINK_H__
#define  __ENGINE_SINK_H__

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32  Sink_Init(RENDER_MANAGER_S* pstRender);

HI_S32  Sink_Deinit(HI_VOID);

HI_S32  Sink_Start(HI_VOID);

HI_S32  Sink_Stop(HI_VOID);

HI_S32  Sink_Pause(HI_VOID);

HI_S32  Sink_flush(HI_VOID);

HI_S32  Sink_SendData(HA_MS12_STREAM_S* pstMS12DecodeStream);

HI_S32  Sink_GetDelayMs(HI_U32* pu32DelayMs);

HI_S32  Sink_GetSyncDelayMs(SOURCE_S* pstSource, HI_U32* pu32Pts);

HI_S32  Sink_SetFifoBufValid(HI_BOOL bValid);

HI_S32  Sink_DeattchExtTrack(HI_VOID);

HI_S32  Sink_EnableContinuousOutput(HI_BOOL bEnable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
