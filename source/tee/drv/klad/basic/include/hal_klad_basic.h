/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_basic.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HAL_KLAD_BASIC_H__
#define __HAL_KLAD_BASIC_H__

#include "hi_type.h"
#include "boot.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern HI_VOID HAL_KLAD_WriteReg(HI_U32 addr, HI_U32 val);
extern HI_U32 HAL_KLAD_ReadReg(HI_U32 addr);
HI_VOID HAL_KLAD_BASIC_CATA_Start(HI_U8 alg, HI_U8 addr, HI_BOOL decrypt);
HI_VOID HAL_KLAD_BASIC_SECSTORE_GetEncRslt(HI_U8* data);
HI_VOID HAL_KLAD_BASIC_SECSTORE_Start(HI_U8 alg, HI_U8 addr, HI_BOOL decrypt);
HI_VOID HAL_KLAD_BASIC_HISITA_Start(HI_U8 addr);
HI_VOID HAL_KLAD_BASIC_STBTA_Start(HI_U8 alg, HI_U8 addr, HI_BOOL decrypt);
HI_VOID HAL_KLAD_BASIC_CLEARCW_Start(HI_U8 addr, HI_U8 dsc, HI_U8 port);
HI_U32 HAL_KLAD_LockClearCw(HI_VOID);
HI_U32 HAL_KLAD_UnLockClearCw(HI_VOID);

#if defined(CHIP_TYPE_hi3796mv200)
HI_VOID HAL_KLAD_SetClearCwKeyIn(HI_U8* data);
#endif
HI_VOID HAL_KLAD_BASIC_SetBasicKladSecen();
HI_VOID HAL_KLAD_BASIC_SetBasicKladSecenLock();
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __HAL_KLAD_BASIC_H__ */
