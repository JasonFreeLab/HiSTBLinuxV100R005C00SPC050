/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_sm2_v100.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef _DRV_SYMC_V100_H_
#define _DRV_SYMC_V100_H_

#include "drv_osal_lib.h"

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/*! \Size of entry node */
#define ENTRY_NODE_SIZE     (16)

/*! \symmetric cipher max iv size*/
#define SYMC_IV_MAX_SIZE        (SYMC_IV_MAX_SIZE_IN_WORD * 4)

/*! \Size of nodes list */
#define CHN_LIST_SIZE     \
    ((ENTRY_NODE_SIZE  *2 + SYMC_IV_MAX_SIZE) * SYMC_MAX_LIST_NUM)

/*! \Size of symc nodes list */
#define SYMC_NODE_LIST_SIZE  (CHN_LIST_SIZE * CIPHER_HARD_CHANNEL_CNT)

/*! \Dump flag of node buffer, if set to 1, the SMMU will dump the page cache*/
#define SYMC_BUF_LIST_FLAG_DUMM   (0x01 << 20)

/*! \IV set flag of node buffer, if set to 1, the IV will update to hardware*/
#define SYMC_BUF_LIST_FLAG_IVSET  (0x01 << 21)

/*! \EOL flag of node buffer, set to 1 at the last node*/
#define SYMC_BUF_LIST_FLAG_EOL    (0x01 << 22)

/*! \Define the offset of reg */
#define  REG_CHAN0_CIPHER_DOUT           (0x0000)
#define  REG_CHAN_CIPHER_IVOUT(id)       (0x0010 + (id)*16)
#define  REG_CIPHER_KEY(id)              (0x0090 + (id)*32)
#define  REG_SEC_CHN_CFG                 (0x0824)
#define  REG_CHAN0_CIPHER_CTRL           (0x1000)
#define  REG_CHAN0_CIPHER_DIN            (0x1014)
#define  REG_CHANn_IBUF_NUM(id)          (0x1000 + (id)*128)
#define  REG_CHANn_IBUF_CNT(id)          (0x1000 + (id)*128 + 0x4)
#define  REG_CHANn_IEMPTY_CNT(id)        (0x1000 + (id)*128 + 0x8)
#define  REG_CHANn_CIPHER_CTRL(id)       (0x1000 + (id)*128 + 0x10)
#define  REG_CHANn_SRC_LST_SADDR(id)     (0x1000 + (id)*128 + 0x14)
#define  REG_CHANn_IAGE_CNT(id)          (0x1000 + (id)*128 + 0x1C)
#define  REG_CHANn_SRC_LST_RADDR(id)     (0x1000 + (id)*128 + 0x20)
#define  REG_CHANn_OBUF_NUM(id)          (0x1000 + (id)*128 + 0x3C)
#define  REG_CHANn_OBUF_CNT(id)          (0x1000 + (id)*128 + 0x40)
#define  REG_CHANn_OFULL_CNT(id)         (0x1000 + (id)*128 + 0x44)
#define  REG_CHANn_INT_OCNTCFG(id)       (0x1000 + (id)*128 + 0x48)
#define  REG_CHANn_DEST_LST_SADDR(id)    (0x1000 + (id)*128 + 0x4C)
#define  REG_CHANn_OAGE_CNT(id)          (0x1000 + (id)*128 + 0x54)
#define  REG_CHANn_DEST_LST_RADDR(id)    (0x1000 + (id)*128 + 0x58)
#define  REG_CHANn_DEST_ADDR(id)         (0x1000 + (id)*128 + 0x5C)
#define  REG_INT_STATUS                  (0x1400)
#define  REG_INT_EN                      (0x1404)
#define  REG_INT_RAW                     (0x1408)
#define  CHANn_RD_DAT_ADDR_SMMU_BYPASS   (0x1418)
#define  CHANn_WR_DAT_ADDR_SMMU_BYPASS   (0x141C)

#define  REG_MMU_GLOBAL_CTR_ADDR         (0x00)
#define  REG_MMU_INTMAS_S                (0x10)
#define  REG_MMU_INTRAW_S                (0x14)
#define  REG_MMU_INTSTAT_S               (0x18)
#define  REG_MMU_INTCLR_S                (0x1c)
#define  REG_MMU_INTMASK_NS              (0x20)
#define  REG_MMU_INTRAW_NS               (0x24)
#define  REG_MMU_INTSTAT_NS              (0x28)
#define  REG_MMU_INTCLR_NS               (0x2C)
#define  REG_MMU_SCB_TTBR                (0x208)
#define  REG_MMU_CB_TTBR                 (0x20C)
#define  REG_MMU_ERR_RDADDR_S            (0x2f0)
#define  REG_MMU_ERR_WRADDR_S            (0x2f4)
#define  REG_MMU_ERR_RDADDR_NS           (0x304)
#define  REG_MMU_ERR_WRADDR_NS           (0x308)

/*! \Define the union U_CHANn_CIPHER_CTRL */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    decrypt         : 1   ; /* [0]  */
        u32    mode            : 3   ; /* [3..1]  */
        u32    alg_sel         : 2   ; /* [5..4]  */
        u32    width           : 2   ; /* [7..6]  */
        u32    reserved_1      : 1   ; /* [8]  */
        u32    key_length      : 2   ; /* [10..9]  */
        u32    reserved_2      : 2   ; /* [12..11]  */
        u32    key_sel         : 1   ; /* [13]  */
        u32    key_adder       : 3   ; /* [16..14]  */
        u32    reserved_3      : 5   ; /* [21..17]  */
        u32    weight          : 10  ; /* [31..22]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_CHANn_CIPHER_CTRL;

/*! \Define the union U_SEC_CHN_CFG */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    sec_chn_cfg     : 8   ; /* [7..0]  */
        u32    sec_chn_cfg_lock : 1  ; /* [8]  */
        u32    reserved_1      : 23  ; /* [31..9]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_SEC_CHN_CFG;

/*! \Define the union U_CHANn_RD_DAT_ADDR_SMMU_BYPASS */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    chann_rd_dat_addr_smmu_bypass     : 7   ; /* [6..0]  */
        u32    reserved_1                        : 25  ; /* [31..7]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_CHANn_RD_DAT_ADDR_SMMU_BYPASS;

/*! \Define the union U_CHANn_WR_DAT_ADDR_SMMU_BYPASS */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    chann_wr_dat_addr_smmu_bypass     : 7  ; /* [6..0]  */
        u32    reserved_1                        : 25 ; /* [31..7]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_CHANn_WR_DAT_ADDR_SMMU_BYPASS;

/*! \Define the union U_INT_STATUS */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    chn_ibuf_int           : 8 ; /* [7..0]  */
        u32    chn_obuf_int           : 8 ; /* [15..8]  */
        u32    tdes_key_error_int     : 1 ; /* [16]  */
        u32    reserved_1             : 15; /* [31..17]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_INT_STATUS;

/*! \Define the union U_INT_EN */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    chn_ibuf_en           : 8 ; /* [7..0]  */
        u32    chn_obuf_en           : 8 ; /* [15..8]  */
        u32    tdes_key_error_en     : 1 ; /* [16]  */
        u32    reserved_1            : 13; /* [31..17]  */
        u32    sec_int_en            : 1 ; /* [30]  */
        u32    int_en                : 1 ; /* [31]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_INT_EN;

/*! \Define the union U_INT_RAW */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    chn_ibuf_raw           : 8 ; /* [7..0]  */
        u32    chn_obuf_raw           : 8 ; /* [15..8]  */
        u32    tdes_key_error_raw     : 1 ; /* [16]  */
        u32    reserved_1             : 15; /* [31..17]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_INT_RAW;

/*! \Define the union U_SMMU_SCR */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    glb_bypass           : 1 ; /* [0]  */
        u32    reserved_1           : 2; /* [2..1]  */
        u32    int_en               : 1 ; /* [3]  */
        u32    reserved_2           : 28; /* [31..4]  */

    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_SMMU_SCR;

/*! \Define the union U_SMMU_INT */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    ints_tlbmiss         : 1 ; /* [0]  */
        u32    ints_ptw_trans       : 1;  /* [1]  */
        u32    ints_tlbinvalid      : 1 ; /* [2]  */
        u32    reserved_2           : 29; /* [31..3]  */

    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_SMMU_INT;

/** @}*/  /** <!-- ==== Structure Definition end ====*/
#endif
