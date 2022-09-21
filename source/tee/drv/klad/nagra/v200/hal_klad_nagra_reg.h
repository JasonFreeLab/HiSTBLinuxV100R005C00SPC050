/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_nagra_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HAL_KLAD_NAGRA_REG_H__
#define __HAL_KLAD_NAGRA_REG_H__

#include "hal_klad_reg.h"
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KL_C1_CSA2_KLAD_CTRL            (KL_BASE_ADDR + 0x24 )    //CSA2 Key ladder control register.
#define KL_C1_CSA3_KLAD_CTRL            (KL_BASE_ADDR + 0x28 )    //CSA3 Key ladder control register.
#define KL_C1_AES_KLAD_CTRL             (KL_BASE_ADDR + 0x2C )    //AES key ladder control register.
#define KL_C1_TDES_KLAD_CTRL            (KL_BASE_ADDR + 0x30 )    //TDES key ladder control register.
#define KL_C1_BOOT_KLAD_CTRL            (KL_BASE_ADDR + 0x34 )    //C1 BOOT   key ladder start register
#define KL_C1_KLAD_STATE                (KL_BASE_ADDR + 0x38 )    //C1 key ladder state.
#define KL_C1_BOOT_ENC_RSLT0            (KL_BASE_ADDR + 0x40 )    //BOOT key encypt regiter1.
#define KL_C1_BOOT_ENC_RSLT1            (KL_BASE_ADDR + 0x44 )    //BOOT key encypt regiter2.
#define KL_C1_BOOT_ENC_RSLT2            (KL_BASE_ADDR + 0x48 )    //BOOT key encypt regiter3.
#define KL_C1_BOOT_ENC_RSLT3            (KL_BASE_ADDR + 0x4C )    //BOOT key encypt regiter4.
#define KL_C1_BOOT_DEC_RSLT0            (KL_BASE_ADDR + 0x50 )    //clear Flash protection key regiter.
#define KL_C1_BOOT_DEC_RSLT1            (KL_BASE_ADDR + 0x54 )    //clear Flash protection key regiter.
#define KL_C1_BOOT_DEC_RSLT2            (KL_BASE_ADDR + 0x58 )    //clear Flash protection key regiter.
#define KL_C1_BOOT_DEC_RSLT3            (KL_BASE_ADDR + 0x5C )    //clear Flash protection key regiter.
#define KL_C1_SEC_EN                    (KL_BASE_ADDR + 0x330)    //C1 key ladder  secure attribute.
#define KL_C1_BOOT_SEC_EN               (KL_BASE_ADDR + 0x364)    //C1 BOOT key ladder  secure attribute.
#define KL_C1_CPU_ACCESS_CTRL           (KL_BASE_ADDR + 0x380)    //C1 boot key ladder CPU access right control.
#define KL_C1_KLAD_VERSION              (KL_BASE_ADDR + 0x404)    //HKL version Register.

typedef union
{
    struct
    {
        HI_U32 c1_csa2_calc_start : 1; //[0]
        HI_U32 c1_csa2_level_sel  : 4; //[1~4]
        HI_U32 reserved0          : 3; //[5~7]
        HI_U32 c1_csa2_key_addr   : 8; //[8~15]
        HI_U32 reserved1          : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_C1_CSA2_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c1_csa3_calc_start : 1; //[0]
        HI_U32 c1_csa3_level_sel  : 4; //[1~4]
        HI_U32 reserved0          : 3; //[5~7]
        HI_U32 c1_csa3_key_addr   : 8; //[8~15]
        HI_U32 reserved1          : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_C1_CSA3_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c1_aes_calc_start  : 1; //[0]
        HI_U32 c1_aes_level_sel   : 4; //[1~4]
        HI_U32 reserved0          : 3; //[5~7]
        HI_U32 c1_aes_key_addr    : 8; //[8~15]
        HI_U32 c1_aes_dsc_mode    : 8; //[16~23]
        HI_U32 c1_aes_port_sel    : 2; //[24~25]
        HI_U32 reserved1          : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_C1_AES_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c1_tdes_calc_start : 1; //[0]
        HI_U32 c1_tdes_level_sel  : 4; //[1~4]
        HI_U32 reserved0          : 3; //[5~7]
        HI_U32 c1_tdes_key_addr   : 8; //[8~15]
        HI_U32 c1_tdes_dsc_mode   : 8; //[16~23]
        HI_U32 c1_tdes_port_sel   : 2; //[24~25]
        HI_U32 reserved1          : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_C1_TDES_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c1_boot_calc_start  : 1; //[0]
        HI_U32 c1_boot_level_sel   : 4; //[1~4]
        HI_U32 reserved0           : 2; //[5~6]
        HI_U32 c1_boot_decrypt     : 1; //[7]
        HI_U32 c1_boot_key_addr    : 8; //[8~15]
        HI_U32 reserved1           : 8; //[16~23]
        HI_U32 boot_port_sel       : 2; //[24~25]
        HI_U32 dec_rslt_rd_disable : 4; //[26~29]
        HI_U32 reserved2           : 2; //[30~31]
    } bits;
    HI_U32 u32;
} KL_C1_BOOT_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c1_csa2_klad0_rdy  : 1; //[0]
        HI_U32 c1_csa2_klad1_rdy  : 1; //[1]
        HI_U32 c1_csa2_klad2_rdy  : 1; //[2]
        HI_U32 c1_csa3_klad0_rdy  : 1; //[3]
        HI_U32 c1_csa3_klad1_rdy  : 1; //[4]
        HI_U32 c1_csa3_klad2_rdy  : 1; //[5]
        HI_U32 c1_aes_klad0_rdy   : 1; //[6]
        HI_U32 c1_aes_klad1_rdy   : 1; //[7]
        HI_U32 c1_aes_klad2_rdy   : 1; //[8]
        HI_U32 c1_tdes_klad0_rdy  : 1; //[9]
        HI_U32 c1_tdes_klad1_rdy  : 1; //[10]
        HI_U32 c1_tdes_klad2_rdy  : 1; //[11]
        HI_U32 c1_bt_klad0_rdy    : 1; //[12]
        HI_U32 c1_bt_klad1_rdy    : 1; //[13]
        HI_U32 c1_bt_klad2_rdy    : 1; //[14]
        HI_U32 c1_bt_klad3_rdy    : 1; //[15]
        HI_U32 reserved           : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_C1_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 c1_csa2_sec_en      : 1; //[0]
        HI_U32 c1_csa3_sec_en      : 1; //[1]
        HI_U32 c1_aes_sec_en       : 1; //[2]
        HI_U32 c1_tdes_sec_en      : 1; //[3]
        HI_U32 reserved            : 28;//[4~31]
    } bits;
    HI_U32 u32;
} KL_C1_SEC_EN_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif    /* __HAL_KLAD_NAGRA_REG_H__ */
