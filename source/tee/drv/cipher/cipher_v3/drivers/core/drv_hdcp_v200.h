/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_hdcp_v200.h
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef _DRV_HDCP_V200_H_
#define _DRV_HDCP_V200_H_

#include "drv_osal_lib.h"

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/*! \Define the offset of reg */
#define CHAN0_CIPHER_IV            (0x0000)
#define CHAN0_CIPHER_DOUT          (0x0080)
#define HDCP_MODE_CTRL             (0x0300)
#define CPU_HDCP_ROOTKEY           (0x0280)
#define CALC_ST0                   (0x0318)
#define CHAN0_CIPHER_CTRL          (0x0400)
#define CHAN0_CIPHER_DIN           (0x0420)

/* Define the union U_HDCP_MODE_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        u32    hdcp_mode_en          : 1   ; /* [0]  */
        u32    hdcp_rootkey_sel      : 2   ; /* [2..1]  */
        u32    reserved_0            : 1   ; /* [3]  */
        u32    hdmi_tx_hdcp14_wr_en  : 1   ; /* [4]  */
        u32    hdmi_rx_hdcp14_wr_en  : 1   ; /* [5]  */
        u32    hdmi_rx_hdcp22_wr_en  : 1   ; /* [6]  */
        u32    reserved_1            : 1   ; /* [7]  */
        u32    hdcp_wr_sel           : 2   ; /* [9..8]  */
        u32    reserved_2            : 22  ; /* [31..10]  */
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
        u32    sym_ch0_start         : 1   ; /* [0]  */
        u32    sym_ch0_alg_mode      : 3   ; /* [3..1]  */
        u32    sym_ch0_alg_sel       : 3   ; /* [6..4]  */
        u32    sym_ch0_decrypt       : 1   ; /* [7]  */
        u32    sym_ch0_dat_width     : 2   ; /* [9..8]  */
        u32    sym_ch0_key_length    : 2   ; /* [11..10]  */
        u32    sym_ch0_ccm_gcm_input_flag : 2   ; /* [13..12]  */
        u32    sym_ch0_key_sel       : 1   ; /* [14]  */
        u32    sym_ch0_ivin_sel      : 1   ; /* [15]  */
        u32    reserved_0            : 2   ; /* [17..16]  */
        u32    sym_ch0_sm1_round_num : 2   ; /* [19..18]  */
        u32    sym_ch0_gcm_iv_len    : 4   ; /* [23..20]  */
        u32    sym_ch0_ccm_gcm_pc_last : 1   ; /* [24]  */
        u32    sym_ccm_gcm_last_block  : 4   ;/* [28..25]  */
        u32    reserved_1            : 3   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    u32    u32;

} U_CHAN0_CIPHER_CTRL;

/** @}*/  /** <!-- ==== Structure Definition end ====*/
#endif
