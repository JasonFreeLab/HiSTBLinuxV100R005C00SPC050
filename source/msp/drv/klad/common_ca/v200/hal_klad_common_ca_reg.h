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

#include "hi_type.h"
#include "hal_klad_reg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KL_C5_CSA2_KLAD_CTRL            (KL_BASE_ADDR + 0xD0)    //C5 CSA2 Key ladder control register.
#define KL_C5_CSA3_KLAD_CTRL            (KL_BASE_ADDR + 0xD4)    //C5 CSA3 Key ladder control register.
#define KL_C5_SP_KLAD_CTRL              (KL_BASE_ADDR + 0xD8)    //C5 SP key ladder control register.
#define KL_C5_R2R_KLAD_CTRL             (KL_BASE_ADDR + 0xDC)    //C5 R2R key ladder control register.
#define KL_C5_MISC_KLAD_CTRL            (KL_BASE_ADDR + 0xE0)    //C5 misc key ladder control register.
#define KL_C5_KLAD_STATE                (KL_BASE_ADDR + 0xE4)    //C5 key ladder state.

#define KL_C5_OTP_LV_SEL                (KL_OTP_SHADOW_BASE_ADDR + 0x20)


typedef union
{
    struct
    {
        HI_U32 c5_csa2_calc_start    : 1; //[0]
        HI_U32 c5_csa2_level_sel     : 4; //[1~4]
        HI_U32 c5_csa2_tdes_aes_sel  : 1; //[5]
        HI_U32 reserved0             : 2; //[6~7]
        HI_U32 c5_csa2_key_addr      : 8; //[8~15]
        HI_U32 reserved1             : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_C5_CSA2_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c5_csa3_calc_start    : 1; //[0]
        HI_U32 c5_csa3_level_sel     : 4; //[1~4]
        HI_U32 c5_csa3_tdes_aes_sel  : 1; //[5]
        HI_U32 reserved0             : 2; //[6~7]
        HI_U32 c5_csa3_key_addr      : 8; //[8~15]
        HI_U32 reserved1             : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_C5_CSA3_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c5_sp_calc_start     : 1; //[0]
        HI_U32 c5_sp_level_sel      : 4; //[1~4]
        HI_U32 c5_sp_tdes_aes_sel   : 1; //[5]
        HI_U32 reserved0            : 2; //[6~7]
        HI_U32 c5_sp_key_addr       : 8; //[8~15]
        HI_U32 c5_sp_dsc_mode       : 8; //[16~23]
        HI_U32 c5_sp_port_sel       : 2; //[24~25]
        HI_U32 reserved1            : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_C5_SP_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c5_r2r_calc_start   : 1; //[0]
        HI_U32 c5_r2r_level_sel    : 4; //[1~4]
        HI_U32 c5_r2r_tdes_aes_sel : 1; //[5]
        HI_U32 reserved0           : 2; //[6~7]
        HI_U32 c5_r2r_key_addr     : 8; //[8~15]
        HI_U32 c5_r2r_dsc_mode     : 8; //[16~23]
        HI_U32 c5_r2r_port_sel     : 2; //[24~25]
        HI_U32 reserved1           : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_C5_R2R_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c5_misc_calc_start   : 1; //[0]
        HI_U32 c5_misc_level_sel    : 4; //[1~4]
        HI_U32 c5_misc_tdes_aes_sel : 1; //[5]
        HI_U32 reserved0            : 2; //[6~7]
        HI_U32 c5_misc_key_addr     : 8; //[8~15]
        HI_U32 c5_misc_dsc_mode     : 8; //[16~23]
        HI_U32 c5_misc_port_sel     : 2; //[24~25]
        HI_U32 reserved1            : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_C5_MISC_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c5_csa2_klad0_rdy    : 1; //[0]
        HI_U32 c5_csa2_klad1_rdy    : 1; //[1]
        HI_U32 c5_csa2_klad2_rdy    : 1; //[2]
        HI_U32 c5_csa3_klad0_rdy    : 1; //[3]
        HI_U32 c5_csa3_klad1_rdy    : 1; //[4]
        HI_U32 c5_csa3_klad2_rdy    : 1; //[5]
        HI_U32 c5_sp_klad0_rdy      : 1; //[6]
        HI_U32 c5_sp_klad1_rdy      : 1; //[7]
        HI_U32 c5_sp_klad2_rdy      : 1; //[8]
        HI_U32 c5_sp_klad3_rdy      : 1; //[9]
        HI_U32 c5_sp_klad4_rdy      : 1; //[10]
        HI_U32 c5_r2r_klad0_rdy     : 1; //[11]
        HI_U32 c5_r2r_klad1_rdy     : 1; //[12]
        HI_U32 c5_r2r_klad2_rdy     : 1; //[13]
        HI_U32 c5_misc_klad0_rdy    : 1; //[14]
        HI_U32 c5_misc_klad1_rdy    : 1; //[15]
        HI_U32 c5_misc_klad2_rdy    : 1; //[16]
        HI_U32 c5_misc_klad3_rdy    : 1; //[17]
        HI_U32 c5_misc_klad4_rdy    : 1; //[18]
        HI_U32 reserved             : 13; //[19~31]
    } bits;
    HI_U32 u32;
} KL_C5_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U8 cm0_deob_enable       : 1; //[0]
        HI_U8 cm0_csa2_lv_sel       : 1; //[1]
        HI_U8 cm0_csa3_lv_sel       : 1; //[2]
        HI_U8 cm0_sp_lv_sel         : 2; //[3-4]
        HI_U8 cm0_r2r_lv_sel        : 1; //[5]
        HI_U8 cm0_misc_lv_sel       : 2; //[6-7]
    } bits;
    HI_U8 u8;
} KL_C5_OTP_LV_SEL_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_COMMON_CA_REG_H__ */
