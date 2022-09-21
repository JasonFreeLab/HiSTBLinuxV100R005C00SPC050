/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_verimatrix_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __HAL_KLAD_VERIMATRIX_REG_H__
#define __HAL_KLAD_VERIMATRIX_REG_H__

#include "hi_type.h"
#include "hal_klad_reg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#define KL_C6_SP_KLAD_CTRL                (KL_BASE_ADDR + 0x0C)//SP¿ØÖÆ¼Ä´æÆ÷
#define KL_C6_MISC_KLAD_CTRL              (KL_BASE_ADDR + 0xC0)//misc¿ØÖÆ¼Ä´æÆ÷
#define KL_C6_SP_KWMCWC                   (KL_BASE_ADDR + 0x280)
#define KL_C6_MISC_KWMCWC                 (KL_BASE_ADDR + 0x290)

typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 tdes_aes_sel   : 1; //[2]
        HI_U32 raw_mode       : 1; //[3]
        HI_U32 level_sel_5    : 1; //[4]
        HI_U32 ta_kl_flag     : 1; //[5]
        HI_U32 reserved1      : 2; //[7:6]
        HI_U32 key_addr       : 8; //[15:8]
        HI_U32 dsc_mode       : 8; //[23:16]
        HI_U32 reserved       : 8; //[31:24]
    } bits;
    HI_U32 u32;
} KL_C6_SP_KLAD_CTRL_U;


typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 tdes_aes_sel   : 1; //[2]
        HI_U32 target_sel     : 1; //[3]
        HI_U32 level_sel_5    : 1; //[4]
        HI_U32 reserved_0     : 3; //[7:5]
        HI_U32 key_addr       : 8; //[15:8]
        HI_U32 dsc_mode       : 8; //[23:16]
        HI_U32 reserved       : 8; //[31:24]
    } bits;
    HI_U32 u32;
} KL_C6_MISC_KLAD_CTRL_U;

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
} KL_C6_KLAD_STATE_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_VERIMATRIX_REG_H__ */
