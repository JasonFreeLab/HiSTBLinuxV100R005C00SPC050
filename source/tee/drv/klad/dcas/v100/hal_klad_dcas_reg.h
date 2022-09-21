/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_dcas_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-03-21
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HAL_KLAD_DCAS_REG_H__
#define __HAL_KLAD_DCAS_REG_H__

#include "hal_klad_reg.h"
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#define KL_DCAS_K3_0_KLAD_CTRL           (KL_BASE_ADDR + 0x74)    //DCAS K3_0 key ladder start register
#define KL_DCAS_K3_0_DANONCE0            (KL_BASE_ADDR + 0x80)    //K3_0 MODE DCAS NONCE register
#define KL_DCAS_K3_0_DANONCE1            (KL_BASE_ADDR + 0x84)    //K3_0 MODE DCAS NONCE register
#define KL_DCAS_K3_0_DANONCE2            (KL_BASE_ADDR + 0x88)    //K3_0 MODE DCAS NONCE register
#define KL_DCAS_K3_0_DANONCE3            (KL_BASE_ADDR + 0x8C)    //K3_0 MODE DCAS NONCE register


typedef union
{
    struct
    {
        HI_U32 level_sel            : 4; //[0~3]
        HI_U32 tdes_aes_sel         : 1; //[4]
        HI_U32 model_sel            : 1; //[5]
        HI_U32 reserved0            : 10; //[6~15]
        HI_U32 dsc_code_mc_alg_sel  : 8; //[16~23]
        HI_U32 key_addr             : 8; //[24~31]
    } bits;
    HI_U32 u32;
} KL_DCAS_K3_0_KLAD_CTRL_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_DCAS_REG_H__ */
