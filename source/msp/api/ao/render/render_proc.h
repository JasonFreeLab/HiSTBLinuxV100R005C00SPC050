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

#ifndef  __RENDER_PROC_H__
#define  __RENDER_PROC_H__

#include "render_common.h"

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

#ifdef RENDER_DEBUG_SUPPORT

HI_S32  Proc_Init(RENDER_MANAGER_S* pstRender);

HI_VOID Proc_DeInit(RENDER_MANAGER_S* pstRender);

HI_VOID Proc_Source(SOURCE_S* pstSource);

HI_VOID Proc_Engine(ENGINE_MANAGER_S* pstEngine, STATISTICS_CMD_E enCmd);

HI_VOID Proc_Sink(ENGINE_MANAGER_S* pstEngine, STATISTICS_CMD_E enCmd);

#else

#define Proc_Init(Param)

#define Proc_DeInit(Param)

#define Proc_Source(Param)

#define Proc_Engine(Param, cmd)

#define Proc_Sink(Param, cmd)

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
