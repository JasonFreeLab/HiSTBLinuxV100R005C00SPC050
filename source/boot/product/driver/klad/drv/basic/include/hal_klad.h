/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HAL_KLAD_H__
#define __HAL_KLAD_H__

#include "hi_type.h"
#include "hi_debug.h"
#ifndef HI_MINIBOOT_SUPPORT
#include "exports.h"
#else
#include "delay.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define msleep(ms) udelay(ms * 1000)

#ifndef HI_REG_READ32
#define HI_REG_READ32(addr,result)  ((result) = *(volatile unsigned int *)(addr))
#endif

#ifndef HI_REG_WRITE32
#define HI_REG_WRITE32(addr,result)  (*(volatile unsigned int *)(addr) = (result))
#endif

HI_VOID HAL_KLAD_WriteReg(HI_U32 addr, HI_U32 val);

HI_U32 HAL_KLAD_ReadReg(HI_U32 addr);

HI_S32 HAL_KLAD_CheckState(HI_VOID);

HI_VOID HAL_KLAD_SetDataIn(HI_U8 *data);

HI_VOID HAL_KLAD_SetComDataIn(HI_U8 *data);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_H__ */
