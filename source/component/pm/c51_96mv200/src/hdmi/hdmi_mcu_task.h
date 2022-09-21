/******************************************************************************

  Copyright (C), 2016-2026, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_mcu_task.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/06/20
  Description   :
  History       :
  Date          : 2016/06/20
  Author        : sdk
  Modification  :
*******************************************************************************/
#ifndef __HDMI_MCU_TASK_H__
#define __HDMI_MCU_TASK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "hi_type.h"

/**
\brief  mcu hdmi task init
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskInit(HI_VOID);

/**
\brief  mcu hdmi task handle ,such as ddc read,cec Tx & Rx,etc.
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskHandle(HI_VOID);

/**
\brief  mcu hdmi task deinit
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskDeInit(HI_VOID);

/**
\brief	mcu hdmi task interrupt sever function
\param      none
\retval     none
*/
HI_VOID MCU_HDMI_TaskIrqHandle(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __HDMI_MCU_TASK_H__ */

