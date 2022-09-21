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

#ifndef  __OMX_AUDIO_PROC_H__
#define  __OMX_AUDIO_PROC_H__


#include "omx_audio_base.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


typedef enum
{
    STATISTICS_START = 0,
    STATISTICS_STOP,
    STATISTICS_BUTT,
} STATISTICS_CMD_E;

HI_S32  OMX_HA_PROC_Init(HI_AUDDATATYPE* pHAData);
HI_VOID OMX_HA_PROC_DeInit(HI_AUDDATATYPE* pHAData);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
