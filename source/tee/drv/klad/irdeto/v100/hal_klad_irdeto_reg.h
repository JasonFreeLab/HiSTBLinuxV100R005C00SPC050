/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_irdeto_reg.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __HAL_KLAD_IRDETO_REG_H__
#define __HAL_KLAD_IRDETO_REG_H__

#include "hal_klad_reg.h"
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define KL_C2_CSA2_KLAD_CTRL              (KL_BASE_ADDR + 0x04)
#define KL_C2_R2R_KLAD_CTRL               (KL_BASE_ADDR + 0x08)
#define KL_C2_SP_KLAD_CTRL                (KL_BASE_ADDR + 0x0C)
#define KL_C2_CSA3_KLAD_CTRL              (KL_BASE_ADDR + 0x10)
#define KL_C2_SSUK_KLAD_CTRL              (KL_BASE_ADDR + 0xC8)
#define KL_C2_CCC_KLAD_CTRL               (KL_BASE_ADDR + 0xCC)
#define KL_C2_CCC_RSLT0                   (KL_BASE_ADDR + 0xF0)
#define KL_C2_CCC_RSLT1                   (KL_BASE_ADDR + 0xF4)
#define KL_C2_CCC_RSLT2                   (KL_BASE_ADDR + 0xF8)
#define KL_C2_CCC_RSLT3                   (KL_BASE_ADDR + 0xFC)
#define KL_C2_TA_KLAD_CTRL                (KL_BASE_ADDR + 0x100)

#define KL_C2_SEC_EN                      (KL_BASE_ADDR + 0x200)

typedef union
{
    struct
    {
        HI_U32 level_sel             : 2; //[0~1]
        HI_U32 tdes_aes_sel          : 1; //[2]
        HI_U32 ta_kl_flag            : 1; //[3]
        HI_U32 reserved1             : 4; //[4~7]
        HI_U32 key_addr              : 8; //[8~15]
        HI_U32 dsc_mode              : 8;//[16~23]
        HI_U32 reserved              : 8; //[31:24]
    } bits;
    HI_U32 u32;
} KL_C2_CSA2_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel             : 2; //[0~1]
        HI_U32 tdes_aes_sel          : 1; //[2]
        HI_U32 ta_kl_flag            : 1; //[3]
        HI_U32 reserved1             : 4; //[4~7]
        HI_U32 key_addr              : 8; //[8~15]
        HI_U32 dsc_mode              : 8; //[16~23]
        HI_U32 reserved              : 8; //[31:24]
    } bits;
    HI_U32 u32;
} KL_C2_CSA3_KLAD_CTRL_U;

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
} KL_C2_SP_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel             : 2; //[0~1]
        HI_U32 tdes_aes_sel          : 1; //[2]
        HI_U32 payload_mode          : 1; //[3]
        HI_U32 reserved1             : 5; //[4~7]
        HI_U32 key_addr              : 8; //[8~15]
        HI_U32 dsc_mode              : 8;//[16~23]
        HI_U32 reserved              : 8; //[31:24]
    } bits;
    HI_U32 u32;
} KL_C2_R2R_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel             : 2; //[0~1]
        HI_U32 cur_128bit_cnt        : 6; //[2~7]
        HI_U32 last_time             : 1; //[8]
        HI_U32 lut_alg_sel           : 1; //[9]
        HI_U32 dec_lut_alg_sel       : 1; //[10]
        HI_U32 reserved              : 21; //[11:31]
    } bits;
    HI_U32 u32;
} KL_C2_TA_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c2_ccc_calc_start     : 1; //[0]
        HI_U32 reserved              : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_C2_CCC_KLAD_CALC_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c2_ssuk_key_addr      : 8; //[0~7]
        HI_U32 reserved1             : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_C2_SSUK_CTRL_U;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_KLAD_IRDETO_REG_H__ */
