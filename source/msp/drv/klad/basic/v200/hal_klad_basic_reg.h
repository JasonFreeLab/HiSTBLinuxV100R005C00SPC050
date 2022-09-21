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


#define KL_BOOT_KLAD_CTRL              (KL_BASE_ADDR + 0x144)    //BOOT   key ladder start register
#define KL_BOOT_KLAD_STATE             (KL_BASE_ADDR + 0x148)    //key ladder state.
#define KL_BOOT_ENC_RSLT0              (KL_BASE_ADDR + 0x150)    //BOOT key encypt regiter1.
#define KL_BOOT_ENC_RSLT1              (KL_BASE_ADDR + 0x154)    //BOOT key encypt regiter2.
#define KL_BOOT_ENC_RSLT2              (KL_BASE_ADDR + 0x158)    //BOOT key encypt regiter3.
#define KL_BOOT_ENC_RSLT3              (KL_BASE_ADDR + 0x15C)    //BOOT key encypt regiter4.

#define KL_SW_KLAD_CTRL                (KL_BASE_ADDR + 0x164)    //SW  key ladder start register
#define KL_STB_ROOTKEY_CTRL            (KL_BASE_ADDR + 0x168)    //STB root   key ladder start register
#define KL_SW_KLAD_STATE               (KL_BASE_ADDR + 0x16C)    //SW key ladder state.
#define KL_SW_ENC_RSLT0                (KL_BASE_ADDR + 0x170)    //SW key encypt regiter1.
#define KL_SW_ENC_RSLT1                (KL_BASE_ADDR + 0x174)    //SW key encypt regiter2.
#define KL_SW_ENC_RSLT2                (KL_BASE_ADDR + 0x178)    //SW key encypt regiter3.
#define KL_SW_ENC_RSLT3                (KL_BASE_ADDR + 0x17C)    //SW key encypt regiter4.

#define KL_WIDEVINE_KLAD_CTRL          (KL_BASE_ADDR + 0x180)    //widevine Key ladder control register.
#define KL_WIDEVINE_KLAD_STATE         (KL_BASE_ADDR + 0x184)    //key ladder state.
#define KL_WIDEVINE_CW_CRC             (KL_BASE_ADDR + 0x188)    //widevine cw crc result
#define KL_WIDEVINE_DEC_FLAG           (KL_BASE_ADDR + 0x18C)    //widevine decrypt flag
#define KL_WIDEVINE_ENC_RSLT0          (KL_BASE_ADDR + 0x190)    //widevine key encypt regiter1.
#define KL_WIDEVINE_ENC_RSLT1          (KL_BASE_ADDR + 0x194)    //widevine key encypt regiter2.
#define KL_WIDEVINE_ENC_RSLT2          (KL_BASE_ADDR + 0x198)    //widevine key encypt regiter3.
#define KL_WIDEVINE_ENC_RSLT3          (KL_BASE_ADDR + 0x19C)    //widevine key encypt regiter4.

#define KL_CA_TA_KLAD_CTRL             (KL_BASE_ADDR + 0x1A4)    //CA_TA  key ladder start register
#define KL_CA_TA_KLAD_STATE            (KL_BASE_ADDR + 0x1A8)    //CA_TA key ladder state.
#define KL_STB_TA_KLAD_CTRL            (KL_BASE_ADDR + 0x1AC)    //
#define KL_STB_TA_KLAD_STATE           (KL_BASE_ADDR + 0x1B0)    //STB_TA key ladder state.
#define KL_SEC_STORE_KLAD_CTRL         (KL_BASE_ADDR + 0x1B4)    //SEC_STORE key ladder start register
#define KL_SEC_STORE_KLAD_STATE        (KL_BASE_ADDR + 0x1B8)    //SEC_STORE key ladder state.

#define KL_SEC_STORE_ENC_RSLT0         (KL_BASE_ADDR + 0x1E0)    //SEC_STORE TA keyladder encrypt result register 0
#define KL_SEC_STORE_ENC_RSLT1         (KL_BASE_ADDR + 0x1E4)    //SEC_STORE TA keyladder encrypt result register 1
#define KL_SEC_STORE_ENC_RSLT2         (KL_BASE_ADDR + 0x1E8)    //SEC_STORE TA keyladder encrypt result register 2
#define KL_SEC_STORE_ENC_RSLT3         (KL_BASE_ADDR + 0x1EC)    //SEC_STORE TA keyladder encrypt result register 3
#define KL_STB_IMAGE_KLAD_CTRL         (KL_BASE_ADDR + 0x1F0)    //STB IMAGE   key ladder start register
#define KL_STB_IMAGE_KLAD_STATE        (KL_BASE_ADDR + 0x1F4)    //key ladder state.

#define KL_CLEAR_CW_KLAD_CTRL          (KL_BASE_ADDR + 0x204)    //Clear CW control register
#define KL_AUX_KLAD_CTRL               (KL_BASE_ADDR + 0x208)    //AUX Keyladder control register
#define KL_SOS_KLAD_CTRL               (KL_BASE_ADDR + 0x20C)    //SOS Keyladder control register
#define KL_SMCU_KLAD_CTRL              (KL_BASE_ADDR + 0x210)    //SMCU Keyladder control register
#define KL_HISI_TA_KLAD_CTRL           (KL_BASE_ADDR + 0x214)    //HISI_TA Keyladder control register
#define KL_TEE_KLAD_STATE              (KL_BASE_ADDR + 0x218)    //TEE key ladder state.
#define KL_HSL_KLAD_CTRL               (KL_BASE_ADDR + 0x21C)    //HSL Keyladder control register
#define KL_HSL_KLAD_DISABLE            (KL_BASE_ADDR + 0x220)    //HSL Keyladder disable control register

#define KL_SEC_KLAD_DIN0               (KL_BASE_ADDR + 0x300)    //secure CPU config data in register 0
#define KL_SEC_KLAD_DIN1               (KL_BASE_ADDR + 0x304)    //secure CPU  data in register 1
#define KL_SEC_KLAD_DIN2               (KL_BASE_ADDR + 0x308)    //secure CPU  data in register 2
#define KL_SEC_KLAD_DIN3               (KL_BASE_ADDR + 0x30C)    //secure CPU  data in register 3

#define KL_SP_KWMCWC_DIN0              (KL_BASE_ADDR + 0x310)    //secure CPU config KWMCWC register 0
#define KL_SP_KWMCWC_DIN1              (KL_BASE_ADDR + 0x314)    //secure CPU  KWMCWC register 1
#define KL_SP_KWMCWC_DIN2              (KL_BASE_ADDR + 0x318)    //secure CPU  KWMCWC register 2
#define KL_SP_KWMCWC_DIN3              (KL_BASE_ADDR + 0x31C)    //secure CPU  KWMCWC register 3

#define KL_MISC_KWMCWC_DIN0            (KL_BASE_ADDR + 0x320)    //secure CPU config KWMCWC register 0
#define KL_MISC_KWMCWC_DIN1            (KL_BASE_ADDR + 0x324)    //secure CPU  KWMCWC register 1
#define KL_MISC_KWMCWC_DIN2            (KL_BASE_ADDR + 0x328)    //secure CPU  KWMCWC register 2
#define KL_MISC_KWMCWC_DIN3            (KL_BASE_ADDR + 0x32C)    //secure CPU  KWMCWC register 3

#define KL_C2_SEC_EN                   (KL_BASE_ADDR + 0x334)    //C2 key ladder  secure attribute.
#define KL_C3_SEC_EN                   (KL_BASE_ADDR + 0x338)    //C3 key ladder  secure attribute.
#define KL_C5_SEC_EN                   (KL_BASE_ADDR + 0x33C)    //C5 key ladder  secure attribute.
#define KL_C6_SEC_EN                   (KL_BASE_ADDR + 0x340)    //C6 key ladder  secure attribute.
#define KL_WIDEVINE_SEC_EN             (KL_BASE_ADDR + 0x348)    //secure enable lock register
#define KL_SW_SEC_EN                   (KL_BASE_ADDR + 0x34C)    //SW key ladder  secure attribute enable.
#define KL_STB_ROOTKEY_SEC_EN          (KL_BASE_ADDR + 0x350)    //STB_ROOTKEY key ladder  secure attribute enable.
#define KL_STB_IMAGE_SEC_EN            (KL_BASE_ADDR + 0x354)    //STB_IMAGE key ladder  secure attribute enable.
#define KL_BOOT_SEC_EN                 (KL_BASE_ADDR + 0x358)    //BOOT key ladder  secure attribute enable.
#define KL_SEC_EN_LOCK                 (KL_BASE_ADDR + 0x35C)    //secure enable lock register
#define KL_CLEAR_CW_SEC_EN             (KL_BASE_ADDR + 0x360)    //Clear CW   secure attribute enable.


#define KL_C2_CPU_ACCESS_CTRL          (KL_BASE_ADDR + 0x384)    //C2 key ladder CPU access right control.
#define KL_C3_CPU_ACCESS_CTRL          (KL_BASE_ADDR + 0x388)    //C3 key ladder CPU access right control.
#define KL_C5_CPU_ACCESS_CTRL          (KL_BASE_ADDR + 0x38C)    //C5 key ladder CPU access right control.
#define KL_C6_CPU_ACCESS_CTRL          (KL_BASE_ADDR + 0x390)    //C6 key ladder CPU access right control.
#define KL_BOOT_CPU_ACCESS_CTRL        (KL_BASE_ADDR + 0x394)    //BOOT key ladder CPU access right control.
#define KL_DCAS_CPU_ACCESS_CTRL        (KL_BASE_ADDR + 0x398)    //DCAS key ladder CPU access right control.
#define KL_CLEAR_CW_CPU_ACCESS_CTRL    (KL_BASE_ADDR + 0x39C)    //CLEAR_CW key ladder CPU access right control.
#define KL_SW_CPU_ACCESS_CTRL          (KL_BASE_ADDR + 0x3A0)    //SW key ladder CPU access right control.
#define KL_STB_RK_CPU_ACCESS_CTRL      (KL_BASE_ADDR + 0x3A4)    //STB_rootkey CPU access right control.
#define KL_STB_IMAGE_ACCESS_CTRL       (KL_BASE_ADDR + 0x3A8)    //STB_IMAGE key ladder CPU access right control.
#define KL_CPU_ACCESS_LOCK             (KL_BASE_ADDR + 0x3F0)    //keyladder access right lock register

#define KL_HIS_KLAD_VERSION            (KL_BASE_ADDR + 0x400)    //HKL version Register.
#define KL_C2_KLAD_VERSION             (KL_BASE_ADDR + 0x408)    //HKL version Register.
#define KL_C3_KLAD_VERSION             (KL_BASE_ADDR + 0x40C)    //HKL version Register.
#define KL_C5_KLAD_VERSION             (KL_BASE_ADDR + 0x410)    //HKL version Register.
#define KL_C6_KLAD_VERSION             (KL_BASE_ADDR + 0x414)    //HKL version Register.
#define KL_DCAS_KLAD_VERSION           (KL_BASE_ADDR + 0x418)    //HKL version Register.
#define KL_WIDEVINE_KLAD_VERSION       (KL_BASE_ADDR + 0x41C)    //HKL version Register.
#define KL_CA_HKL_ACPU_INT_RAW         (KL_BASE_ADDR + 0x420)    //hkl module raise acpu calculation finish raw interup
#define KL_CA_HKL_ACPU_INT_EN          (KL_BASE_ADDR + 0x424)    //raise acpu calculation finish interup enable
#define KL_CA_HKL_ACPU_INT             (KL_BASE_ADDR + 0x428)    //hkl module raise acpu calculation finish interup state
#define KL_CA_HKL_TZCPU_INT_RAW        (KL_BASE_ADDR + 0x42C)    //hkl module raise tzcpu calculation finish raw interup
#define KL_CA_HKL_TZCPU_INT_EN         (KL_BASE_ADDR + 0x430)    //raise tzcpu calculation finish interup enable
#define KL_CA_HKL_TZCPU_INT            (KL_BASE_ADDR + 0x434)    //hkl module raise tzcpu calculation finish interup state
#define KL_CA_HKL_SCPU_INT_RAW         (KL_BASE_ADDR + 0x438)    //hkl module raise scpu calculation finish raw interup
#define KL_CA_HKL_SCPU_INT_EN          (KL_BASE_ADDR + 0x43C)    //raise scpu calculation finish interup enable
#define KL_CA_HKL_SCPU_INT             (KL_BASE_ADDR + 0x440)    //hkl module raise scpu calculation finish interup state
#define KL_CA_HKL_SMCU_INT_RAW         (KL_BASE_ADDR + 0x444)    //hkl module raise smcu calculation finish raw interup
#define KL_CA_HKL_SMCU_INT_EN          (KL_BASE_ADDR + 0x448)    //raise smcu calculation finish interup enable
#define KL_CA_HKL_SMCU_INT             (KL_BASE_ADDR + 0x44C)    //hkl module raise smcu calculation finish interup state

#define KL_CLEAR_CW_LOCK               (KL_BASE_ADDR + 0x680)    //CLEAR_CW key ladder lock
#define KL_CLEAR_CW_DIN0               (KL_BASE_ADDR + 0x690)    //CLEAR_CW key ladder data0 in
#define KL_CLEAR_CW_DIN1               (KL_BASE_ADDR + 0x694)    //CLEAR_CW key ladder data1 in
#define KL_CLEAR_CW_DIN2               (KL_BASE_ADDR + 0x698)    //CLEAR_CW key ladder data2 in
#define KL_CLEAR_CW_DIN3               (KL_BASE_ADDR + 0x69c)    //CLEAR_CW key ladder data3 in

typedef union
{
    struct
    {
        HI_U32 boot_calc_start       : 1; //[0]
        HI_U32 reserved0             : 4; //[1~4]
        HI_U32 boot_tdes_aes_sel     : 1; //[5]
        HI_U32 reserved1             : 1; //[6]
        HI_U32 boot_decrypt          : 1; //[7]
        HI_U32 boot_key_addr         : 8; //[8~15]
        HI_U32 reserved2             : 8; //[16~23]
        HI_U32 boot_port_sel         : 2; //[24~25]
        HI_U32 reserved3             : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_BOOT_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 boot_klad0_rdy        : 1; //[0]
        HI_U32 reserved              : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_BOOT_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 sw_calc_start         : 1; //[0]
        HI_U32 reserved0             : 6; //[1~6]
        HI_U32 sw_decrypt            : 1; //[7]
        HI_U32 sw_key_addr           : 8; //[8~15]
        HI_U32 reserved1             : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_SW_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 stb_calc_start       : 1; //[0]
        HI_U32 reserved0            : 7; //[1~7]
        HI_U32 stb_key_addr         : 8; //[8~15]
        HI_U32 reserved1            : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_STB_ROOTKEY_CTRL_U;

// logic starts 2 level inside
typedef union
{
    struct
    {
        HI_U32 sw_klad0_rdy         : 1; //[0]
        HI_U32 sw_klad1_rdy         : 1; //[1]
        HI_U32 reserved             : 30; //[2~31]
    } bits;
    HI_U32 u32;
} KL_SW_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 widevine_calc_start   : 1; //[0]
        HI_U32 widevine_level_sel    : 4; //[1~4]
        HI_U32 reserved0             : 2; //[5~6]
        HI_U32 widevine_decrypt      : 1; //[7]
        HI_U32 widevine_key_addr     : 8; //[8~15]
        HI_U32 reserved1             : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_WIDEVINE_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 widevine_klad0_rdy    : 1; //[0]
        HI_U32 widevine_klad1_rdy    : 1; //[1]
        HI_U32 widevine_klad2_rdy    : 1; //[2]
        HI_U32 widevine_klad3_rdy    : 1; //[3]
        HI_U32 reserved              : 28; //[4~31]
    } bits;
    HI_U32 u32;
} KL_WIDEVINE_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 widevine_cw_crc      : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_WIDEVINE_CW_CRC_U;

typedef union
{
    struct
    {
        HI_U32 ca_ta_calc_start    : 1; //[0]
        HI_U32 reserved0           : 7; //[1~7]
        HI_U32 ca_ta_key_addr      : 8; //[8~15]
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
        HI_U32 stb_ta_calc_start    : 1; //[0]
        HI_U32 reserved0            : 7; //[1~7]
        HI_U32 stb_ta_key_addr      : 8; //[8~15]
        HI_U32 reserved1            : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_STB_TA_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 stb_ta_klad0_rdy   : 1; //[0]
        HI_U32 reserved           : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_STB_TA_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 sec_store_calc_start    : 1; //[0]
        HI_U32 reserved0               : 6; //[1~6]
        HI_U32 se_store_decrypt        : 1; //[7]
        HI_U32 sec_store_key_addr      : 8; //[8~15]
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
        HI_U32 stb_image_calc_start   : 1; //[0]
        HI_U32 reserved0              : 7; //[1~7]
        HI_U32 stb_image_key_addr     : 8; //[8~15]
        HI_U32 reserved1              : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_STB_IMAGE_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 stb_image_klad0_rdy   : 1; //[0]
        HI_U32 reserved              : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_STB_IMAGE_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 clear_cw_calc_start    : 1; //[0]
        HI_U32 reserved0              : 7; //[1~7]
        HI_U32 clear_cw_key_addr      : 8; //[8~15]
        HI_U32 clear_cw_dsc_mode      : 8; //[16~23]
        HI_U32 clear_cw_port_sel      : 2; //[14~25]
        HI_U32 reserved1              : 6; //[26~31]
    } bits;
    HI_U32 u32;
} KL_CLEAR_CW_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 aux_calc_start           : 1; //[0]
        HI_U32 reserved0                : 7; //[1~7]
        HI_U32 aux_key_addr             : 8; //[8~15]
        HI_U32 reserved1                : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_AUX_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 sos_calc_start           : 1; //[0]
        HI_U32 reserved0                : 7; //[1~7]
        HI_U32 sos_key_addr             : 8; //[8~15]
        HI_U32 reserved1                : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_SOS_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 smcu_calc_start           : 1; //[0]
        HI_U32 reserved0                : 7; //[1~7]
        HI_U32 smcu_key_addr             : 8; //[8~15]
        HI_U32 reserved1                : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_SMCU_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 hisi_ta_calc_start           : 1; //[0]
        HI_U32 reserved0                    : 7; //[1~7]
        HI_U32 hisi_ta_key_addr             : 8; //[8~15]
        HI_U32 reserved1                    : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_HISI_TA_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 aux_klad0_rdy                : 1; //[0]
        HI_U32 sos_klad0_rdy                : 1; //[1]
        HI_U32 smcu_klad0_rdy               : 1; //[2]
        HI_U32 hisi_ta_klad0_rdy            : 1; //[3]
        HI_U32 hsl_klad0_rdy                : 1; //[4]
        HI_U32 reserved1                    : 27; //[5~31]
    } bits;
    HI_U32 u32;
} KL_TEE_KLAD_STATE_U;

typedef union
{
    struct
    {
        HI_U32 hsl_calc_start               : 1; //[0]
        HI_U32 reserved0                    : 7; //[1~7]
        HI_U32 hsl_key_addr                 : 8; //[8~15]
        HI_U32 reserved1                    : 16; //[16~31]
    } bits;
    HI_U32 u32;
} KL_HSL_KLAD_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 hsl_kl_disable               : 1; //[0]
        HI_U32 hsl_rk_clr                   : 1; //[1]
        HI_U32 reserved1                    : 30; //[2~31]
    } bits;
    HI_U32 u32;
} KL_HSL_KLAD_DISABLE_U;

typedef union
{
    struct
    {
        HI_U32 c3_csa2_sec_en         : 1; //[0]
        HI_U32 c3_csa3_sec_en         : 1; //[1]
        HI_U32 c3_sp_sec_en           : 1; //[2]
        HI_U32 c3_r2r_sec_en          : 1; //[3]
        HI_U32 c3_drm_sec_en          : 1; //[4]
        HI_U32 c3_lp_sec_en           : 1; //[5]
        HI_U32 reserved               : 26; //[6~31]
    } bits;
    HI_U32 u32;
} KL_C3_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 c5_csa2_sec_en          : 1; //[0]
        HI_U32 c5_csa3_sec_en          : 1; //[1]
        HI_U32 c5_sp_sec_en            : 1; //[2]
        HI_U32 c5_r2r_sec_en           : 1; //[3]
        HI_U32 c5_misc_sec_en          : 1; //[4]
        HI_U32 reserved                : 27; //[5~31]
    } bits;
    HI_U32 u32;
} KL_C5_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 c6_csa2_sec_en          : 1; //[0]
        HI_U32 c6_csa3_sec_en          : 1; //[1]
        HI_U32 c6_sp_sec_en            : 1; //[2]
        HI_U32 c6_r2r_sec_en           : 1; //[3]
        HI_U32 c6_misc_sec_en          : 1; //[4]
        HI_U32 reserved                : 27; //[5~31]
    } bits;
    HI_U32 u32;
} KL_C6_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 dcas_sec_en          : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_DCAS_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 widevine_sec_en      : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_WIDEVINE_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 ca_ta_sec_en         : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_TA_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 sw_sec_en            : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_SW_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 stb_rk_sec_en        : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_STB_ROOTKEY_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 stb_image_sec_en     : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_STB_IMAGE_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 boot_sec_en          : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_BOOT_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 c1_sec_en_lock           : 1; //[0]
        HI_U32 c2_sec_en_lock           : 1; //[1]
        HI_U32 c3_sec_en_lock           : 1; //[2]
        HI_U32 c5_sec_en_lock           : 1; //[3]
        HI_U32 c6_sec_en_lock           : 1; //[4]
        HI_U32 dcas_sec_en_lock         : 1; //[5]
        HI_U32 widevine_sec_en_lock     : 1; //[6]
        HI_U32 sw_sec_en_lock           : 1; //[7]
        HI_U32 stb_rk_sec_en_lock       : 1; //[8]
        HI_U32 stb_image_sec_en_lock    : 1; //[9]
        HI_U32 boot_sec_en_lock         : 1; //[10]
        HI_U32 clear_cw_sec_en_lock     : 1; //[11]
        HI_U32 c1_boot_sec_en_lock      : 1; //[12]
        HI_U32 reserved                 : 19;//[13~31]
    } bits;
    HI_U32 u32;
} KL_SEC_EN_LOCK_U;

typedef union
{
    struct
    {
        HI_U32 clear_cw_sec_en      : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CLEAR_CW_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 c1_boot_sec_en       : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_C1_BOOT_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 c1_hostcpu_ctrl       : 2; //[0~1]
        HI_U32 c1_tzcpu_ctrl         : 2; //[2~3]
        HI_U32 reserved0             : 2; //[4~5]
        HI_U32 c1_scpu_ctrl          : 2; //[6~7]
        HI_U32 reserved1             : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_C1_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c2_hostcpu_ctrl       : 2; //[0~1]
        HI_U32 c2_tzcpu_ctrl         : 2; //[2~3]
        HI_U32 reserved0             : 2; //[4~5]
        HI_U32 c2_scpu_ctrl          : 2; //[6~7]
        HI_U32 reserved1             : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_C2_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c3_hostcpu_ctrl       : 2; //[0~1]
        HI_U32 c3_tzcpu_ctrl         : 2; //[2~3]
        HI_U32 reserved0             : 2; //[4~5]
        HI_U32 c3_scpu_ctrl          : 2; //[6~7]
        HI_U32 reserved1             : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_C3_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c5_hostcpu_ctrl       : 2; //[0~1]
        HI_U32 c5_tzcpu_ctrl         : 2; //[2~3]
        HI_U32 reserved0             : 2; //[4~5]
        HI_U32 c5_scpu_ctrl          : 2; //[6~7]
        HI_U32 reserved1             : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_C5_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c6_hostcpu_ctrl       : 2; //[0~1]
        HI_U32 c6_tzcpu_ctrl         : 2; //[2~3]
        HI_U32 reserved0             : 2; //[4~5]
        HI_U32 c6_scpu_ctrl          : 2; //[6~7]
        HI_U32 reserved1             : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_C6_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 boot_hostcpu_ctrl       : 2; //[0~1]
        HI_U32 boot_tzcpu_ctrl         : 2; //[2~3]
        HI_U32 reserved0               : 2; //[4~5]
        HI_U32 boot_scpu_ctrl          : 2; //[6~7]
        HI_U32 reserved1               : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_BOOT_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 dcas_hostcpu_ctrl       : 2; //[0~1]
        HI_U32 dcas_tzcpu_ctrl         : 2; //[2~3]
        HI_U32 reserved0               : 2; //[4~5]
        HI_U32 dcas_scpu_ctrl          : 2; //[6~7]
        HI_U32 reserved1               : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_DCAS_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 clear_cw_hostcpu_ctrl        : 2; //[0~1]
        HI_U32 clear_cw_tzcpu_ctrl          : 2; //[2~3]
        HI_U32 reserved0                    : 2; //[4~5]
        HI_U32 clear_cw_scpu_ctrl           : 2; //[6~7]
        HI_U32 reserved1                    : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_CLEAR_CW_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 stb_rk_hostcpu_ctrl        : 2; //[0~1]
        HI_U32 stb_rk_tzcpu_ctrl          : 2; //[2~3]
        HI_U32 reserved0                  : 2; //[4~5]
        HI_U32 stb_rk_scpu_ctrl           : 2; //[6~7]
        HI_U32 reserved1                  : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_STB_RK_CPU_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 stb_image_hostcpu_ctrl        : 2; //[0~1]
        HI_U32 stb_image_tzcpu_ctrl          : 2; //[2~3]
        HI_U32 reserved0                     : 2; //[4~5]
        HI_U32 stb_image_scpu_ctrl           : 2; //[6~7]
        HI_U32 reserved1                     : 24; //[8~31]
    } bits;
    HI_U32 u32;
} KL_STB_IMAGE_ACCESS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 c2_cpu_access_lock           : 1; //[0]
        HI_U32 c3_cpu_access_lock           : 1; //[1]
        HI_U32 c5_cpu_access_lock           : 1; //[2]
        HI_U32 c6_cpu_access_lock           : 1; //[3]
        HI_U32 boot_cpu_access_lock         : 1; //[4]
        HI_U32 dcas_cpu_access_lock         : 1; //[5]
        HI_U32 clear_cw_cpu_access_lock     : 1; //[6]
        HI_U32 sw_cpu_access_lock           : 1; //[7]
        HI_U32 stb_rk_cpu_access_lock       : 1; //[8]
        HI_U32 stb_image_cpu_access_lock    : 1; //[9]
        HI_U32 c1_cpu_access_lock           : 1; //[10]
        HI_U32 reserved0                    : 21; //[11~31]

    } bits;
    HI_U32 u32;
} KL_CPU_ACCESS_LOCK_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_acpu_int_raw  : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_ACPU_INT_RAW_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_acpu_int_en   : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_ACPU_INT_EN_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_acpu_int      : 1; //[0]
        HI_U32 reserved             : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_ACPU_INT_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_tzcpu_int_raw   : 1; //[0]
        HI_U32 reserved               : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_TZCPU_INT_RAW_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_tzcpu_int_en    : 1; //[0]
        HI_U32 reserved               : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_TZCPU_INT_EN_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_tzcpu_int       : 1; //[0]
        HI_U32 reserved               : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_TZCPU_INT_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_scpu_int_raw       : 1; //[0]
        HI_U32 reserved                  : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_SCPU_INT_RAW_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_scpu_int_en        : 1; //[0]
        HI_U32 reserved                  : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_SCPU_INT_EN_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_scpu_int           : 1; //[0]
        HI_U32 reserved                  : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_SCPU_INT_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_smcu_int_raw       : 1; //[0]
        HI_U32 reserved                  : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_SMCU_INT_RAW_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_smcu_int_en        : 1; //[0]
        HI_U32 reserved                  : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_SMCU_INT_EN_U;

typedef union
{
    struct
    {
        HI_U32 ca_hkl_smcu_int           : 1; //[0]
        HI_U32 reserved                  : 31; //[1~31]
    } bits;
    HI_U32 u32;
} KL_CA_HKL_SMCU_INT_U;

typedef union
{
    struct
    {
        HI_U32 c3_csa2_cardless_sec_en         : 1; //[0]
        HI_U32 c3_csa2_cardless_sec_en_lock    : 1; //[1]
        HI_U32 reserved                        : 30; //[2~31]
    } bits;
    HI_U32 u32;
} KL_C3_CARDLESS_CSA2_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 c3_csa3_cardless_sec_en         : 1; //[0]
        HI_U32 c3_csa3_cardless_sec_en_lock    : 1; //[1]
        HI_U32 reserved                        : 30; //[2~31]
    } bits;
    HI_U32 u32;
} KL_C3_CARDLESS_CSA3_SEC_EN_U;

typedef union
{
    struct
    {
        HI_U32 c3_sp_cardless_sec_en         : 1; //[0]
        HI_U32 c3_sp_cardless_sec_en_lock    : 1; //[1]
        HI_U32 reserved                      : 30; //[2~31]
    } bits;
    HI_U32 u32;
} KL_C3_CARDLESS_SP_SEC_EN_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif    /* __HAL_KLAD_BASIC_REG_H__ */
