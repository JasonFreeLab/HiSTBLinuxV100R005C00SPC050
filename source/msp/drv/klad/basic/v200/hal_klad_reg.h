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
#endif /* End of #ifdef __cplusplus */


#define KL_BASE_ADDR                (0xF8ABA000)
#define KL_OTP_SHADOW_BASE_ADDR     (0xF8AB0000)

#define KL_COM_KLAD_DIN0            (KL_BASE_ADDR + 0x0)      //data in register 0
#define KL_COM_KLAD_DIN1            (KL_BASE_ADDR + 0x4)      //data in register 1
#define KL_COM_KLAD_DIN2            (KL_BASE_ADDR + 0x8)      //data in register 2
#define KL_COM_KLAD_DIN3            (KL_BASE_ADDR + 0xC)      //data in register 3

#define KL_KLAD_STATE               (KL_BASE_ADDR + 0x10)     //HKL work state.
#define KL_KLAD_CHECK_ERROR         (KL_BASE_ADDR + 0x14)     //Hisec key ladder error code value.
#define KL_KLAD_CRC                 (KL_BASE_ADDR + 0x18)     //The curr level key crc.
#define KL_CA_VENDOR                (KL_BASE_ADDR + 0x1C)     //HKL CA verdor Register.
#define KL_ROB_ALARM                (KL_BASE_ADDR + 0x20)     //Hisec key ladder ROB alarm value.

#define KL_SEC_KLAD_DIN0            (KL_BASE_ADDR + 0x300)    //secure CPU config data in register 0
#define KL_SEC_KLAD_DIN1            (KL_BASE_ADDR + 0x304)    //secure CPU  data in register 1
#define KL_SEC_KLAD_DIN2            (KL_BASE_ADDR + 0x308)    //secure CPU  data in register 2
#define KL_SEC_KLAD_DIN3            (KL_BASE_ADDR + 0x30C)    //secure CPU  data in register 3

#if (defined(CHIP_TYPE_hi3796mv200) && !defined(HI_TEE_SUPPORT))   \
    || (defined(CHIP_TYPE_hi3716mv420) && !defined(HI_TEE_SUPPORT)) \
    || (defined(CHIP_TYPE_hi3716mv410) && !defined(HI_TEE_SUPPORT))
#define KL_REG_DIN0                  KL_SEC_KLAD_DIN0
#define KL_REG_DIN1                  KL_SEC_KLAD_DIN1
#define KL_REG_DIN2                  KL_SEC_KLAD_DIN2
#define KL_REG_DIN3                  KL_SEC_KLAD_DIN3
#else
#define KL_REG_DIN0                  KL_COM_KLAD_DIN0
#define KL_REG_DIN1                  KL_COM_KLAD_DIN1
#define KL_REG_DIN2                  KL_COM_KLAD_DIN2
#define KL_REG_DIN3                  KL_COM_KLAD_DIN3
#endif

#if defined(CHIP_TYPE_hi3716mv420) ||defined(CHIP_TYPE_hi3716mv410)
typedef union
{
    struct
    {
        HI_U32 hkl_busy    : 1; //[0~1]
        HI_U32 reserved    : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_KLAD_STATE_U;
#else
typedef union
{
    struct
    {
        HI_U32 hkl_busy    : 2; //[0~1]
        HI_U32 reserved    : 30; //[1~31]
    } bits;
    HI_U32 u32;
} KL_KLAD_STATE_U;
#endif

typedef union
{
    struct
    {
        HI_U32 kl_err       : 1; //[0]
        HI_U32 reserved0    : 3; //[1~3]
        HI_U32 kl_check_err : 8; //[4~11]
        HI_U32 reserved1    : 20; //[12~31]
    } bits;
    HI_U32 u32;
} KL_KLAD_CHECK_ERROR_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  /* __HAL_KLAD_REG_H__ */
