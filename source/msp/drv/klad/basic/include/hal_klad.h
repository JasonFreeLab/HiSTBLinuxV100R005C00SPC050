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

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#define HI_FATAL_KLAD(fmt...)    HI_FATAL_PRINT(HI_ID_CA, fmt)
#define HI_ERR_KLAD(fmt...)      HI_ERR_PRINT(HI_ID_CA, fmt)
#define HI_WARN_KLAD(fmt...)     HI_WARN_PRINT(HI_ID_CA, fmt)
#define HI_INFO_KLAD(fmt...)     HI_INFO_PRINT(HI_ID_CA, fmt)


HI_VOID HAL_KLAD_RegisterMap(void);

HI_VOID HAL_KLAD_RegisterUnMap(void);

HI_VOID HAL_KLAD_WriteReg(HI_U32 addr, HI_U32 val);

HI_U32 HAL_KLAD_ReadReg(HI_U32 addr);

HI_U32 HAL_KLAD_ReadOtpShadowReg(HI_U32 addr);

HI_S32 HAL_KLAD_CheckState(HI_VOID);

HI_VOID HAL_KLAD_SetDataIn(HI_U8 *data);

HI_VOID HAL_KLAD_SetComDataIn(HI_U8 *data);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_H__ */
