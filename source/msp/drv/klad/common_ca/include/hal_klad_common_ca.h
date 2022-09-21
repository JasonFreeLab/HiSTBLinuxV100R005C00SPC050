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



HI_VOID HAL_KLAD_COMMON_CA_CSA2Start(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd);

HI_U8 HAL_KLAD_COMMON_CA_CSA2GetLevel(HI_VOID);

HI_VOID HAL_KLAD_COMMON_CA_CSA3Start(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd);

HI_U8 HAL_KLAD_COMMON_CA_CSA3GetLevel(HI_VOID);

HI_VOID HAL_KLAD_COMMON_CA_SPStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target);

HI_U8 HAL_KLAD_COMMON_CA_SPGetLevel(HI_VOID);

HI_VOID HAL_KLAD_COMMON_CA_R2RStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target);

HI_U8 HAL_KLAD_COMMON_CA_R2RGetLevel(HI_VOID);

HI_VOID HAL_KLAD_COMMON_CA_MISCStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target);

HI_U8 HAL_KLAD_COMMON_CA_MISCGetLevel(HI_VOID);

HI_U32 HAL_KLAD_COMMON_CA_GetState(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_COMMON_CA_H__ */
