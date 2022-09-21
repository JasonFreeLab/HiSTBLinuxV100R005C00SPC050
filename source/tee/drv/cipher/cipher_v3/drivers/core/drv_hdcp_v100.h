/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_hdcp_v100.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef _DRV_HDCP_V100_H_
#define _DRV_HDCP_V100_H_

#include "drv_osal_lib.h"

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/*! \Define the offset of reg */
#define CHAN0_CIPHER_DOUT          (0x0000)
#define CPU_HDCP_ROOTKEY           (0x0810)
#define HDCP_MODE_CTRL             (0x0820)
#define SEC_CHN_CFG                (0x0824)
#define CHAN0_CIPHER_CTRL          (0x1000)
#define CHAN0_CIPHER_IV            (0x1004)
#define CHAN0_CIPHER_DIN           (0x1014)
#define CIPHER_REG_CHAN0_CFG       (0x1410)

/* Define the union U_HDCP_MODE_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    hdcp_mode_en          : 1   ; /* [0]  */
        u32    tx_read               : 1   ; /* [1]  */
        u32    hdcp_rootkey_sel      : 2   ; /* [3..2]  */
        u32    rx_read               : 1   ; /* [4]  */
        u32    rx_sel                : 2   ; /* [6..5]  */
        u32    hdcp22_rx_read        : 1   ; /* [7]  */
        u32    reserved_1            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_HDCP_MODE_CTRL;

/* Define the union U_CHAN0_CIPHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    decrypt               : 1   ; /* [0]  */
        u32    mode                  : 3   ; /* [3..1]  */
        u32    alg_sel               : 2   ; /* [5..4]  */
        u32    width                 : 2   ; /* [7..6]  */
        u32    ivin_sel              : 1   ; /* [8]  */
        u32    key_length            : 2   ; /* [10..9]  */
        u32    reserved_0            : 2   ; /* [12..11]  */
        u32    key_sel               : 2   ; /* [13]  */
        u32    key_adder             : 3   ; /* [16..14]  */
        u32    reserved_1            : 15   ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CHAN0_CIPHER_CTRL;

/* Define the union U_CIPHER_REG_CHAN0_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    ch0_start             : 1   ;  /* [0]  */
        u32    ch0_busy              : 1   ;  /* [1]  */
        u32    reserved_0            : 30   ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CIPHER_REG_CHAN0_CFG;

/** @}*/  /** <!-- ==== Structure Definition end ====*/
#endif
