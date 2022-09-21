/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_plcipher_reg.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_PLCIPHER_REG_H__
#define __DRV_PLCIPHER_REG_H__

/* add include here */
#include "hal_plcipher.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef union
{
    struct
    {
        HI_U32 reserved0                        : 3;    // [2:0]
        HI_U32 int_sta_timeout_err              : 1;    // [3]
        HI_U32 int_sta_logic_timeout            : 1;    // [4]
        HI_U32 reserved1                        : 4;    // [8:5]
        HI_U32 int_ista_desc_empty              : 1;    // [9]
        HI_U32 int_ista_desc_out                : 1;    // [10]
        HI_U32 reserved2                        : 6;    // [16:11]
        HI_U32 int_osta_desc_empty              : 1;   // [17]
        HI_U32 reserved3                        : 1;   // [18]
        HI_U32 int_osta_wrbuffer_done           : 1;   // [19]
        HI_U32 reserved4                        : 4;   // [23:20]
        HI_U32 int_ena_all                      : 1;   // [24]
        HI_U32 reserved5                        : 7;   // [31:25]
    } bits;
    HI_U32 u32;
} PLCIPHER_INT_STATUS_U;  //Offset:0x108

typedef PLCIPHER_INT_STATUS_U PLCIPHER_INT_ENABLE_U;
typedef PLCIPHER_INT_STATUS_U PLCIPHER_INT_ORG_STATUS_U;

typedef union
{
    struct
    {
        HI_U32  rsv1:8;
        HI_U32  sw_cw_odd_even: 1;
        HI_U32  sw_cw_channel_id: 4;
        HI_U32  rsv2:3;
        HI_U32  sw_cw_type: 8;
        HI_U32  sw_iv_sel: 1;
        HI_U32  rsv3:   3;
        HI_U32  case_sw_algo_type_ok:1;
        HI_U32  rsv4: 3;

    }bits;
    HI_U32 u32;
}PLCIPHER_CW_SET_U;

#define PLCIPHER_REG_BASE_ADDR_PHY          (0xF9A40000)
extern  HI_VOID * g_u32PLCipherRegBase;

#define PLCIPHER_REG_BASE_ADDR                   g_u32PLCipherRegBase //ioremap_nocache(0xF9A40000)
#define PL_GLB_CFG   (PLCIPHER_REG_BASE_ADDR + 0x0000)
#define BUS_GLB_CFG (PLCIPHER_REG_BASE_ADDR + 0x0004)
#define RAM_CKGT (PLCIPHER_REG_BASE_ADDR + 0x0008)
#define BUS_STATUS (PLCIPHER_REG_BASE_ADDR + 0x000C)
#define IN_DESC_SADDR (PLCIPHER_REG_BASE_ADDR + 0x0010)
#define IN_DESC_SIZE (PLCIPHER_REG_BASE_ADDR + 0x0014)
#define IN_DESC_PTR (PLCIPHER_REG_BASE_ADDR + 0x0018)
#define IN_DESC_ADD (PLCIPHER_REG_BASE_ADDR + 0x001C)
#define IN_VLDDESC_CNT (PLCIPHER_REG_BASE_ADDR + 0x0020) //RO

#define IN_DESC_INT_CFG (PLCIPHER_REG_BASE_ADDR + 0x0028)
#define IN_DESC_INT_POST_NUM (PLCIPHER_REG_BASE_ADDR + 0x002C)
#define OUT_DESC_SADDR (PLCIPHER_REG_BASE_ADDR + 0x0080)
#define OUT_DESC_SIZE (PLCIPHER_REG_BASE_ADDR + 0x0084)
#define OUT_DESC_PTR (PLCIPHER_REG_BASE_ADDR + 0x0088) //RO
#define OUT_DESC_ADD (PLCIPHER_REG_BASE_ADDR + 0x008C)
#define OUT_VLDDESC_CNT (PLCIPHER_REG_BASE_ADDR + 0x0090)

#define OUT_DESC_INT_CFG (PLCIPHER_REG_BASE_ADDR + 0x0098)
#define OUT_DESC_INT_POST_NUM (PLCIPHER_REG_BASE_ADDR + 0x009C)  //RO
#define TIMEOUT_THRSH (PLCIPHER_REG_BASE_ADDR + 0x00A0)
#define TIMEOUT_REG (PLCIPHER_REG_BASE_ADDR + 0x00A4)
#define RAW_INT (PLCIPHER_REG_BASE_ADDR + 0x0100)
#define ENA_INT (PLCIPHER_REG_BASE_ADDR + 0x0104)
#define STA_INT (PLCIPHER_REG_BASE_ADDR + 0x0108)
#define PL_INT_ENA (PLCIPHER_REG_BASE_ADDR + 0x010C)
#define KEY_SEC_EN_CFG (PLCIPHER_REG_BASE_ADDR + 0x120)
#define CW_SET (PLCIPHER_REG_BASE_ADDR + 0x0200)
#define CW_WORD0 (PLCIPHER_REG_BASE_ADDR + 0x0204)
#define CW_WORD1 (PLCIPHER_REG_BASE_ADDR + 0x0208)
#define CW_WORD2 (PLCIPHER_REG_BASE_ADDR + 0x020c)
#define CW_WORD3 (PLCIPHER_REG_BASE_ADDR + 0x0210)
#define CA_INFO (PLCIPHER_REG_BASE_ADDR + 0x0214)
#define CA_FIFO (PLCIPHER_REG_BASE_ADDR + 0x0220)
#define OTP_CTRL (PLCIPHER_REG_BASE_ADDR + 0x0300)
#define ERROR_REG (PLCIPHER_REG_BASE_ADDR + 0x0400)
#define DBG (PLCIPHER_REG_BASE_ADDR + 0x0500)
#define DBG_INCTRL (PLCIPHER_REG_BASE_ADDR + 0x0504)
#define DBG_OUTCTRL (PLCIPHER_REG_BASE_ADDR + 0x0508)


#define PID_CH_CFG0 (PLCIPHER_REG_BASE_ADDR + 0x1000)
#define PID_CH_CFG1 (PLCIPHER_REG_BASE_ADDR + 0x1100)
#define PID_CH_CFG2 (PLCIPHER_REG_BASE_ADDR + 0x1200)
#define PID_CH_CFG3 (PLCIPHER_REG_BASE_ADDR + 0x1300)
#define PID_CH_CFG4 (PLCIPHER_REG_BASE_ADDR + 0x1400)
#define PID_CH_CFG5 (PLCIPHER_REG_BASE_ADDR + 0x1500)
#define PID_CH_CFG6 (PLCIPHER_REG_BASE_ADDR + 0x1600)
#define PID_CH_CFG7 (PLCIPHER_REG_BASE_ADDR + 0x1700)
#define PID_CH_CFG8 (PLCIPHER_REG_BASE_ADDR + 0x1800)
#define PID_CH_CFG9 (PLCIPHER_REG_BASE_ADDR + 0x1900)
#define PID_CH_CFG10 (PLCIPHER_REG_BASE_ADDR + 0x1a00)
#define PID_CH_CFG11 (PLCIPHER_REG_BASE_ADDR + 0x1b00)


#ifdef __cplusplus
}
#endif
#endif /* end #ifndef __DRV_PLCIPHER_REG_H__ */

