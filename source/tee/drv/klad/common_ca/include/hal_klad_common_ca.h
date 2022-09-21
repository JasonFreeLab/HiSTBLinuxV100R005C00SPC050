/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_common_ca.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HAL_KLAD_COMMON_CA_H__
#define __HAL_KLAD_COMMON_CA_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_VOID HAL_KLAD_COMMON_CA_R2RStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target);
HI_U8 HAL_KLAD_COMMON_CA_GetR2RLevel(HI_VOID);
HI_VOID HAL_KLAD_COMMON_CA_SetKladSecen(HI_VOID);
HI_VOID HAL_KLAD_COMMON_CA_SetNonSecDataIn(HI_U8* data);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_COMMON_CA_H__ */
