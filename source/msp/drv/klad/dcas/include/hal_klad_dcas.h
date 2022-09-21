/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_dcas.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HAL_KLAD_DCAS_H__
#define __HAL_KLAD_DCAS_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


HI_VOID HAL_KLAD_DCAS_RKDStart(HI_VOID);

HI_VOID HAL_KLAD_DCAS_K30Start(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target);

HI_U8 HAL_KLAD_DCAS_K30GetLevel(HI_VOID);

HI_U32 HAL_KLAD_DCAS_K30GetDaNonceState(HI_VOID);

HI_VOID HAL_KLAD_DCAS_K30GetDaNonce(HI_U8 *data);

HI_U32 HAL_KLAD_DCAS_GetState(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_DCAS_H__ */
