/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_common_ca_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __HAL_KLAD_COMMON_CA_REG_H__
#define __HAL_KLAD_COMMON_CA_REG_H__

#include "hal_klad_reg.h"
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KL_COM_CA_R2R_KLAD_CTRL              (KL_BASE_ADDR + 0x08)

typedef union
{
    struct
    {
        HI_U32 level_sel             : 2; //[0~1]
        HI_U32 tdes_aes_sel          : 1; //[2]
        HI_U32 reserved              : 5; //[3~7]
        HI_U32 key_addr              : 8; //[8~15]
        HI_U32 reserved1             : 16;//[16~31]
    } bits;
    HI_U32 u32;
} KL_COM_CA_R2R_KLAD_CTRL_U;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_COMMON_CA_REG_H__ */
