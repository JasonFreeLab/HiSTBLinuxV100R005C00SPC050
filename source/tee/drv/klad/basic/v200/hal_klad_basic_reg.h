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

#define KL_CA_TA_KLAD_CTRL             (KL_BASE_ADDR + 0x1A4)    //CA_TA  key ladder start register
#define KL_CA_TA_KLAD_STATE            (KL_BASE_ADDR + 0x1A8)    //CA_TA key ladder state.
#define KL_STB_TA_KLAD_CTRL            (KL_BASE_ADDR + 0x1AC)    //STB_TA key ladder state.
#define KL_HISI_TA_KLAD_CTRL           (KL_BASE_ADDR + 0x214)    //HISI_TA key start register
#define KL_CLEAR_CW_KLAD_CTRL          (KL_BASE_ADDR + 0x204)    //CLEAR_CW key start register

#define KL_SEC_STORE_KLAD_CTRL         (KL_BASE_ADDR + 0x1B4)    //SEC_STORE key ladder start register
#define KL_SEC_STORE_KLAD_STATE        (KL_BASE_ADDR + 0x1B8)    //SEC_STORE key ladder state.

#define KL_SEC_STORE_ENC_RSLT0         (KL_BASE_ADDR + 0x1E0)    //SEC_STORE TA keyladder encrypt result register 0
#define KL_SEC_STORE_ENC_RSLT1         (KL_BASE_ADDR + 0x1E4)    //SEC_STORE TA keyladder encrypt result register 1
#define KL_SEC_STORE_ENC_RSLT2         (KL_BASE_ADDR + 0x1E8)    //SEC_STORE TA keyladder encrypt result register 2
#define KL_SEC_STORE_ENC_RSLT3         (KL_BASE_ADDR + 0x1EC)    //SEC_STORE TA keyladder encrypt result register 3

#define KL_SEC_EN_LOCK                 (KL_BASE_ADDR + 0x35C)    //secure enable lock register

#define KL_CLEAR_CW_SECURE_EN          (KL_BASE_ADDR + 0x360)
#define KL_CLEAR_CW_LOCK               (KL_BASE_ADDR + 0x680)    //CLEAR_CW key ladder lock
#define KL_CLEAR_CW_LOCK_STATUS        (KL_BASE_ADDR + 0x684)    //CLEAR_CW key ladder lock status
#define KL_REG_CLEAR_CW_DIN0           (KL_BASE_ADDR + 0x690)


typedef enum
{
    KL_CLEAR_CW_LOCK_STATUS_UNLOCK = 0x00,
    KL_CLEAR_CW_LOCK_STATUS_LOCK_TEE,
    KL_CLEAR_CW_LOCK_STATUS_LOCK_REE,
    KL_CLEAR_CW_LOCK_STATUS_LOCK_PANDA,
    KL_CLEAR_CW_LOCK_STATUS_BUTT
} KL_CLEAR_CW_LOCK_STATUS_E;

typedef union
{
    struct
    {
        HI_U32 ca_ta_calc_start    : 1; //[0]
        HI_U32 reserved0           : 7; //[1~7]
        HI_U32 ca_ta_key_odd       : 1; //[8]
        HI_U32 ca_ta_key_addr      : 7; //[9~15]
        HI_U32 reserved1           : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_CA_TA_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 ca_ta_klad0_rdy    : 1; //[0]
        HI_U32 reserved           : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_TA_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 sec_store_calc_start    : 1; //[0]
        HI_U32 reserved0               : 6; //[1~6]
        HI_U32 sec_store_decrypt       : 1; //[7]
        HI_U32 sec_store_odd           : 1; //[8]
        HI_U32 sec_store_key_addr      : 7; //[9~15]
        HI_U32 reserved2               : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_SEC_STORE_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 sec_store_klad0_rdy   : 1; //[0]
        HI_U32 reserved              : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_SEC_STORE_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 stb_ta_calc_start    : 1; //[0]
        HI_U32 reserved0            : 7; //[1~7]
        HI_U32 stb_ta_key_odd       : 1; //[8]
        HI_U32 stb_ta_key_addr      : 7; //[9~15]
        HI_U32 reserved1            : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_STB_TA_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 hisi_ta_calc_start   : 1; //[0]
        HI_U32 reserved0            : 7; //[1~7]
        HI_U32 hisi_ta_key_odd      : 1; //[8]
        HI_U32 hisi_ta_key_addr     : 7; //[9~15]
        HI_U32 reserved1            : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_HISI_TA_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 clear_cw_calc_start   : 1; //[0]
        HI_U32 reserved0             : 7; //[1~7]
        HI_U32 clear_cw_key_odd      : 1; //[8]
        HI_U32 clear_cw_key_addr     : 7; //[9~15]
        HI_U32 clear_cw_dsc_code     : 8; //[16~23]
        HI_U32 clear_cw_port_sel     : 2; //[24~25]
        HI_U32 reserved1             : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_CLEAR_CW_KLAD_CTRL_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif	/* __HAL_KLAD_BASIC_REG_H__ */
