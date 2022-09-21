/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_basic_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __HAL_KLAD_BASIC_REG_H__
#define __HAL_KLAD_BASIC_REG_H__

#include "hi_type.h"
#include "hal_klad_reg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KL_SECSTORE_KLAD_CTRL              (KL_BASE_ADDR + 0x198)
#define KL_SECSTORE_KLAD_STATE             (KL_BASE_ADDR + 0x38)
#define KL_SECSTORE_ENC_RSLT0              (KL_BASE_ADDR + 0x1D0)
#define KL_SECSTORE_ENC_RSLT1              (KL_BASE_ADDR + 0x1D4)
#define KL_SECSTORE_ENC_RSLT2              (KL_BASE_ADDR + 0x1D8)
#define KL_SECSTORE_ENC_RSLT3              (KL_BASE_ADDR + 0x1DC)

#define KL_CATA_KLAD_CTRL                  (KL_BASE_ADDR + 0x190)
#define KL_STBTA_KLAD_CTRL                 (KL_BASE_ADDR + 0x194)

#define KL_SEC_EN                          (KL_BASE_ADDR + 0x200) // secure keyladder enable
#define KL_SEC_EN_LOCK                     (KL_BASE_ADDR + 0x204)

typedef union
{
    struct
    {
        HI_U32 key_addr              : 8; //[0~7]
        HI_U32 tdes_aes_sel          : 1; //[8]
        HI_U32 dec_enc_sel           : 1; //[9]
        HI_U32 reserved1             : 22;//[10~32]
    } bits;
    HI_U32 u32;
} KL_SECSTORE_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 key_addr              : 8; //[0~7]
        HI_U32 tdes_aes_sel          : 1; //[8]
        HI_U32 dec_enc_sel           : 1; //[9]
        HI_U32 reserved1             : 22;//[10~32]
    } bits;
    HI_U32 u32;
} KL_STBTA_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 key_addr              : 8; //[0~7]
        HI_U32 tdes_aes_sel          : 1; //[8]
        HI_U32 dec_enc_sel           : 1; //[9]
        HI_U32 reserved1             : 22;//[10~32]
    } bits;
    HI_U32 u32;
} KL_CATA_KLAD_CTRL_U;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif	/* __HAL_KLAD_BASIC_REG_H__ */
