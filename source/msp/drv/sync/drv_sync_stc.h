/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sync_stc.h
  Version       : Initial Draft
  Author        : l00370809
  Created       : 20016/9/28
  Description   :
******************************************************************************/
#ifndef __SYNC_DRV_STC_H__
#define __SYNC_DRV_STC_H__

#include "drv_sync_ioctl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

HI_VOID SYNC_StcAdjust(SYNC_S *pSync, HI_U64 PCRValue ,HI_U64 STCValue);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

