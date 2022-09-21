/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_hash_v100.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef _DRV_HASH_V1_H_
#define _DRV_HASH_V1_H_

#include "drv_osal_lib.h"

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      hash drivers*/
/** @{*/  /** <!-- [hash]*/

/*! \Define the offset of reg */
#define  REG_TOTALLEN_LOW           (0x00)
#define  REG_TOTALLEN_HIGH          (0x04)
#define  REG_STATUS                 (0x08)
#define  REG_CTRL                   (0x0C)
#define  REG_START                  (0x10)
#define  REG_DMA_START_ADDR         (0x14)
#define  REG_DMA_LEN                (0x18)
#define  REG_DATA_IN                (0x1C)
#define  REG_REC_LEN1               (0x20)
#define  REG_REC_LEN2               (0x24)
#define  REG_SHA_OUT1               (0x30)
#define  REG_SHA_OUT2               (0x34)
#define  REG_SHA_OUT3               (0x38)
#define  REG_SHA_OUT4               (0x3C)
#define  REG_SHA_OUT5               (0x40)
#define  REG_SHA_OUT6               (0x44)
#define  REG_SHA_OUT7               (0x48)
#define  REG_SHA_OUT8               (0x4C)
#define  REG_MCU_KEY0               (0x70)
#define  REG_MCU_KEY1               (0x74)
#define  REG_MCU_KEY2               (0x78)
#define  REG_MCU_KEY3               (0x7C)
#define  REG_KL_KEY0                (0x80)
#define  REG_KL_KEY1                (0x84)
#define  REG_KL_KEY2                (0x88)
#define  REG_KL_KEY3                (0x8C)
#define  REG_INIT1_UPDATE           (0x90)

/*! \Define the union U_HASH_STATUS */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    hash_rdy        : 1   ; /* [0]  */
        u32    dma_rdy         : 1   ; /* [1]  */
        u32    msg_rdy         : 1   ; /* [2]  */
        u32    rec_rdy         : 1   ; /* [3]  */
        u32    error_state     : 2   ; /* [5..4]  */
        u32    len_err         : 1   ; /* [6]  */
        u32    reserved_1      : 2   ; /* [31..7]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_HASH_STATUS;

/*! \Define the union U_HASH_CTRL */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    read_ctrl     : 1  ; /* [0]  */
        u32    sha_sel       : 2  ; /* [2..1]  */
        u32    hmac_flag     : 1  ; /* [3]  */
        u32    hardkey_sel   : 1  ; /* [4]  */
        u32    small_end_en  : 1  ; /* [5]  */
        u32    sha_init_update_en  : 1  ; /* [7]  */
        u32    reserved_1      : 25  ; /* [31..7]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_HASH_CTRL;

/*! \Define the union U_SHA_START */
typedef union
{
    /*! \Define the struct bits */
    struct
    {
        u32    sha_start     : 1   ; /* [0]  */
        u32    reserved_1    : 30  ; /* [31..1]  */
    } bits;

    /*! \Define an unsigned member */
    u32    u32;

} U_SHA_START;

/** @}*/  /** <!-- ==== Structure Definition end ====*/
#endif
