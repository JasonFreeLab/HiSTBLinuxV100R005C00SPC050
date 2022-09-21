/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_suma_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __HAL_KLAD_SUMA_REG_H__
#define __HAL_KLAD_SUMA_REG_H__

#include "hi_type.h"
#include "hal_klad_reg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KL_SUMA_LP_KLAD_CTRL               (KL_BASE_ADDR + 0x14)
#define KL_SUMA_LP_PARAMETER_BASE          (KL_BASE_ADDR + 0x50)
typedef union
{
    struct
    {
        HI_U32 level_sel             : 2; //[0~1]
        HI_U32 tdes_aes_sel          : 1; //[2]
        HI_U32 reserved1             : 29;//[3~31]
    } bits;
    HI_U32 u32;
} KL_SUMA_LP_KLAD_CTRL_U;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_SUMA_REG_H__ */
