/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_nagra.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HAL_KLAD_NAGRA_H__
#define __HAL_KLAD_NAGRA_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


HI_VOID HAL_KLAD_NAGRA_CSA2Start(HI_U8 level, HI_U8 addr, HI_U8 odd);

HI_U8 HAL_KLAD_NAGRA_CSA2GetLevel(HI_VOID);

HI_VOID HAL_KLAD_NAGRA_CSA3Start(HI_U8 level, HI_U8 addr, HI_U8 odd);

HI_U8 HAL_KLAD_NAGRA_CSA3GetLevel(HI_VOID);

HI_VOID HAL_KLAD_NAGRA_AESStart(HI_U8 level, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target);

HI_U8 HAL_KLAD_NAGRA_AESGetLevel(HI_VOID);

HI_VOID HAL_KLAD_NAGRA_TDESStart(HI_U8 level, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target);

HI_U8 HAL_KLAD_NAGRA_TDESGetLevel(HI_VOID);

HI_VOID HAL_KLAD_NAGRA_BOOTStart(HI_U8 level, HI_U8 decrypt, HI_U8 addr, HI_U8 target);

HI_U8 HAL_KLAD_NAGRA_BOOTGetLevel(HI_VOID);

HI_VOID HAL_KLAD_NAGRA_BOOTGetEncRslt(HI_U8* data);

HI_VOID HAL_KLAD_NAGRA_BOOTGetDecRslt(HI_U8* data);

HI_U32 HAL_KLAD_NAGRA_GetState(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif	/* __HAL_KLAD_NAGRA_H__ */
