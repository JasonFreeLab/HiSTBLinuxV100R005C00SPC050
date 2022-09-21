/***********************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName:
* Description: TianLai internal audio dac hal
*
* History:
* Version   Date         Author         DefectNum    Description
* main\1    2012-11-06   AudioGroup     NULL         Create this file.
***********************************************************************************/
#ifndef __HAL_TIANLAI_ADAC_V700_H__
#define __HAL_TIANLAI_ADAC_V700_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_type.h"

#ifdef HI_SND_MUTECTL_SUPPORT
HI_VOID ADAC_TIANLAI_V700_FastPowerEnable(HI_BOOL bEnable);
#endif
HI_VOID ADAC_TIANLAI_V700_Init(HI_U32 u32SampelRate, HI_BOOL bResume);
HI_VOID ADAC_TIANLAI_V700_DeInit(HI_BOOL bSuspend);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_TIANLAI_ADAC_V700_H__ */
