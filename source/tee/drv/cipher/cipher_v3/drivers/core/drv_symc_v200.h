/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_sm2_v200.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef _DRV_SYMC_V200_H_
#define _DRV_SYMC_V200_H_

#include "drv_osal_lib.h"

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/*! hash in entry list size */
#define SYMC_NODE_SIZE             (4096)

/*! hash in entry list size */
#define SYMC_NODE_LIST_SIZE        (SYMC_NODE_SIZE * 2 * CIPHER_HARD_CHANNEL_CNT)

/*! \Define the offset of reg */
#define CHANn_CIPHER_IVOUT(id)                  (0x0000 + (id)*0x10)
#define CHAN0_CIPHER_DOUT                       (0x0080)
#define CIPHER_KEY(id)                          (0x0100 + (id)*0x20)
#define SM1_SK(id)                              (0x0200 + (id)*0x10)
#define ODD_EVEN_KEY_SEL                        (0x0290)
#define HDCP_MODE_CTRL                          (0x0300)
#define SEC_CHN_CFG                             (0x0304)
#define CALC_ERR                                (0x0320)
#define CHAN0_CIPHER_CTRL                       (0x0400)
#define CIPHER_INT_STATUS                       (0x0404)
#define CIPHER_INT_EN                           (0x0408)
#define CIPHER_INT_RAW                          (0x040c)
#define CIPHER_IN_SMMU_EN                       (0x0410)
#define OUT_SMMU_EN                             (0x0414)
#define CHAN0_CIPHER_DIN                        (0x0420)
#define NORM_SMMU_START_ADDR                    (0x0440)
#define SEC_SMMU_START_ADDR                     (0x0444)
#define CHANn_CIPHER_CTRL(id)                   (0x0400 + (id)*0x80)
#define CHANn_CIPHER_IN_NODE_CFG(id)            (0x0404 + (id)*0x80)
#define CHANn_CIPHER_IN_NODE_START_ADDR(id)     (0x0408 + (id)*0x80)
#define CHANn_CIPHER_IN_BUF_RPTR(id)            (0x040C + (id)*0x80)
#define CHANn_CIPHER_OUT_NODE_CFG(id)           (0x0430 + (id)*0x80)
#define CHANn_CIPHER_OUT_NODE_START_ADDR(id)    (0x0434 + (id)*0x80)
#define CHANn_CIPHER_OUT_BUF_RPTR(id)           (0x0438 + (id)*0x80)
#define HASH_INT_STATUS                         (0x0804)
#define CHN_WHO_USED_REE                        (0x0390)
#define CHN_WHO_USED_TEE                        (0x0394)
#define SYMC_CHN_MASK(id)                       (0x01 << (id))

/* Define the union U_SEC_CHN_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    cipher_sec_chn_cfg    : 8   ; /* [7..0]  */
        u32    cipher_sec_chn_cfg_lock : 1   ; /* [8]  */
        u32    reserved_0            : 7   ; /* [15..9]  */
        u32    hash_sec_chn_cfg      : 8   ; /* [23..16]  */
        u32    hash_sec_chn_cfg_lock : 1   ; /* [24]  */
        u32    reserved_1            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_SEC_CHN_CFG;

/* Define the union U_CIPHER_INT_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    reserved_0            : 1   ; /* [0]  */
        u32    cipher_chn_ibuf_int   : 7   ; /* [7..1]  */
        u32    cipher_chn_obuf_int   : 8   ; /* [15..8]  */
        u32    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CIPHER_INT_STATUS;

/* Define the union U_CIPHER_INT_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    reserved_0            : 1   ; /* [0]  */
        u32    cipher_chn_ibuf_en    : 7   ; /* [7..1]  */
        u32    cipher_chn_obuf_en    : 8   ; /* [15..8]  */
        u32    reserved_1            : 14  ; /* [29..16]  */
        u32    cipher_sec_int_en     : 1   ; /* [30]  */
        u32    cipher_nsec_int_en    : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CIPHER_INT_EN;

/* Define the union U_CIPHER_INT_RAW */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    reserved_0            : 1   ; /* [0]  */
        u32    cipher_chn_ibuf_raw   : 7   ; /* [7..1]  */
        u32    cipher_chn_obuf_raw   : 8   ; /* [15..8]  */
        u32    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CIPHER_INT_RAW;

/* Define the union U_HASH_INT_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 18  ; /* [17..0]  */
        unsigned int    hash_chn_oram_int     : 8   ; /* [25..18]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HASH_INT_STATUS;

/* Define the union U_CIPHER_IN_SMMU_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    cipher_in_chan_rd_dat_smmu_en : 7   ; /* [6..0]  */
        u32    reserved_0            : 9   ; /* [15..7]  */
        u32    cipher_in_chan_rd_node_smmu_en : 7   ; /* [22..16]  */
        u32    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CIPHER_IN_SMMU_EN;

/* Define the union U_OUT_SMMU_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    out_chan_wr_dat_smmu_en : 7   ; /* [6..0]  */
        u32    reserved_0            : 9   ; /* [15..7]  */
        u32    out_chan_rd_node_smmu_en : 7   ; /* [22..16]  */
        u32    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_OUT_SMMU_EN;

/* Define the union U_CHANN_CIPHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    reserved_0            : 1   ; /* [0]  */
        u32    sym_chn_alg_mode      : 3   ; /* [3..1]  */
        u32    sym_chn_alg_sel       : 3   ; /* [6..4]  */
        u32    sym_chn_decrypt       : 1   ; /* [7]  */
        u32    sym_chn_dat_width     : 2   ; /* [9..8]  */
        u32    sym_chn_key_length    : 2   ; /* [11..10]  */
        u32    reserved_1            : 2   ; /* [13..12]  */
        u32    sym_chn_key_sel       : 1   ; /* [14]  */
        u32    reserved_2            : 1   ; /* [15]  */
        u32    sym_chn_dout_byte_swap_en : 1   ; /* [16]  */
        u32    sym_chn_din_byte_swap_en : 1   ; /* [17]  */
        u32    sym_chn_sm1_round_num : 2   ; /* [19..18]  */
        u32    reserved_3            : 2   ; /* [21..20]  */
        u32    weight                : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CHANN_CIPHER_CTRL;

/* Define the union U_CHANN_CIPHER_IN_NODE_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    cipher_in_node_mpackage_int_level : 7   ; /* [6..0]  */
        u32    reserved_0            : 1   ; /* [7]  */
        u32    cipher_in_node_rptr   : 7   ; /* [14..8]  */
        u32    reserved_1            : 1   ; /* [15]  */
        u32    cipher_in_node_wptr   : 7   ; /* [22..16]  */
        u32    reserved_2            : 1   ; /* [23]  */
        u32    cipher_in_node_total_num : 7   ; /* [30..24]  */
        u32    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CHANN_CIPHER_IN_NODE_CFG;

/* Define the union U_CHANN_CIPHER_OUT_NODE_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    cipher_out_node_mpackage_int_level : 7   ; /* [6..0]  */
        u32    reserved_0            : 1   ; /* [7]  */
        u32    cipher_out_node_rptr  : 7   ; /* [14..8]  */
        u32    reserved_1            : 1   ; /* [15]  */
        u32    cipher_out_node_wptr  : 7   ; /* [22..16]  */
        u32    reserved_2            : 1   ; /* [23]  */
        u32    cipher_out_node_total_num : 7   ; /* [30..24]  */
        u32    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CHANN_CIPHER_OUT_NODE_CFG;

/** @}*/  /** <!-- ==== Structure Definition end ====*/
#endif
