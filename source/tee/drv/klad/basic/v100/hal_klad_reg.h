/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __HAL_KLAD_REG_H__
#define __HAL_KLAD_REG_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KL_BASE_ADDR                (0xF8A90000)
#define KL_OTP_SHADOW_BASE_ADDR     (0xF8AB0080)

#define KL_COM_KLAD_DIN0           (KL_BASE_ADDR + 0x20 ) //data in register 0
#define KL_COM_KLAD_DIN1           (KL_BASE_ADDR + 0x24 ) //data in register 1
#define KL_COM_KLAD_DIN2           (KL_BASE_ADDR + 0x28 ) //data in register 2
#define KL_COM_KLAD_DIN3           (KL_BASE_ADDR + 0x2C ) //data in register 3

#define KL_KLAD_STATE              (KL_BASE_ADDR + 0x38 ) //HKL work state.
#define KL_KLAD_STATE2             (KL_BASE_ADDR + 0x44 )

#define KL_SEC_KLAD_DIN0           (KL_BASE_ADDR + 0x1A0)   //secure CPU config data in register 0
#define KL_SEC_KLAD_DIN1           (KL_BASE_ADDR + 0x1A4)   //secure CPU  data in register 1
#define KL_SEC_KLAD_DIN2           (KL_BASE_ADDR + 0x1A8)   //secure CPU  data in register 2
#define KL_SEC_KLAD_DIN3           (KL_BASE_ADDR + 0x1AC)   //secure CPU  data in register 3

#define KL_STATE                   (KL_BASE_ADDR + 0x38)

#define KL_EN_MASK                 (0x00007FFF) // all keyladder set to secure keyladder

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
#define KL_REG_DIN0                KL_SEC_KLAD_DIN0
#define KL_REG_DIN1                KL_SEC_KLAD_DIN1
#define KL_REG_DIN2                KL_SEC_KLAD_DIN2
#define KL_REG_DIN3                KL_SEC_KLAD_DIN3
#else
#define KL_REG_DIN0                KL_COM_KLAD_DIN0
#define KL_REG_DIN1                KL_COM_KLAD_DIN1
#define KL_REG_DIN2                KL_COM_KLAD_DIN2
#define KL_REG_DIN3                KL_COM_KLAD_DIN3
#endif

typedef union
{
    struct
    {
        HI_U32 err_state           : 4; //[3:0]
        HI_U32 last_key_not_rdy    : 1; //[4]
        HI_U32 csa2_klad0_rdy      : 1; //[5]
        HI_U32 csa2_klad1_rdy      : 1; //[6]
        HI_U32 csa2_klad2_rdy      : 1; //[7]
        HI_U32 r2r_klad0_rdy       : 1; //[8]
        HI_U32 r2r_klad1_rdy       : 1; //[9]
        HI_U32 r2r_klad2_rdy       : 1; //[10]
        HI_U32 sp_klad0_rdy        : 1; //[11]
        HI_U32 sp_klad1_rdy        : 1; //[12]
        HI_U32 sp_klad2_rdy        : 1; //[13]
        HI_U32 csa3_klad0_rdy      : 1; //[14]
        HI_U32 csa3_klad1_rdy      : 1; //[15]
        HI_U32 csa3_klad2_rdy      : 1; //[16]
        HI_U32 misc_klad0_rdy      : 1; //[17]
        HI_U32 misc_klad1_rdy      : 1; //[18]
        HI_U32 misc_klad2_rdy      : 1; //[19]
        HI_U32 lp_klad0_rdy        : 1; //[20]
        HI_U32 lp_klad1_rdy        : 1; //[21]
        HI_U32 k3_rdy              : 1; //[22]
        HI_U32 k2_rdy              : 1; //[23]
        HI_U32 k1_rdy              : 1; //[24]
        HI_U32 reserved            : 6; //[25:30]
        HI_U32 klad_busy           : 1; //[31]
    } bits;
    HI_U32 u32;
} KL_KLAD_STATE_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_BASIC_REG_H__ */
