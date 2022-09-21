/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : spacc_reg.h
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#ifndef _SPACC_REG_H_
#define _SPACC_REG_H_

#define CHAN0_CIPHER_IV                  (s_spacc_reg_base + 0x0000)
#define CHANn_CIPHER_IVOUT(id)           (s_spacc_reg_base + 0x0000 + (id)*0x10)
#define CHAN0_CIPHER_DOUT                (s_spacc_reg_base + 0x0080)
#define CIPHER_KEY(id)                   (s_spacc_reg_base + 0x0100 + (id)*0x20)
#define SM1_SK(id)                       (s_spacc_reg_base + 0x0200 + (id)*0x10)
#define ODD_EVEN_KEY_SEL                 (s_spacc_reg_base + 0x0290)
#define HDCP_MODE_CTRL                   (s_spacc_reg_base + 0x0300)
#define SEC_CHN_CFG                      (s_spacc_reg_base + 0x0304)
#define CALC_ERR                         (s_spacc_reg_base + 0x0320)
#define CHAN0_CIPHER_CTRL                (s_spacc_reg_base + 0x0400)
#define CIPHER_INT_STATUS                (s_spacc_reg_base + 0x0404)
#define CIPHER_INT_EN                    (s_spacc_reg_base + 0x0408)
#define CIPHER_INT_RAW                   (s_spacc_reg_base + 0x040c)
#define CIPHER_IN_SMMU_EN                (s_spacc_reg_base + 0x0410)
#define OUT_SMMU_EN                      (s_spacc_reg_base + 0x0414)
#define CHAN0_CIPHER_DIN                 (s_spacc_reg_base + 0x0420)
#define NORM_SMMU_START_ADDR             (s_spacc_reg_base + 0x0440)
#define SEC_SMMU_START_ADDR              (s_spacc_reg_base + 0x0444)
#define CHANn_CIPHER_CTRL(id)            (s_spacc_reg_base + 0x0400 + (id)*0x80)
#define CHANn_CIPHER_IN_NODE_CFG(id)     (s_spacc_reg_base + 0x0404 + (id)*0x80)
#define CHANn_CIPHER_IN_NODE_START_ADDR(id) (s_spacc_reg_base+0x0408+(id)*0x80)
#define CHANn_CIPHER_IN_BUF_RPTR(id)     (s_spacc_reg_base+0x040C+(id)*0x80)
#define CHANn_CIPHER_OUT_NODE_CFG(id)    (s_spacc_reg_base + 0x0430 + (id)*0x80)
#define CHANn_CIPHER_OUT_NODE_START_ADDR(id) (s_spacc_reg_base+0x0434+(id)*0x80)
#define CHANn_CIPHER_OUT_BUF_RPTR(id)     (s_spacc_reg_base+0x0438+(id)*0x80)

#define CHAN0_HASH_CTRL                  (s_spacc_reg_base + 0x0800)
#define HASH_INT_STATUS                  (s_spacc_reg_base + 0x0804)
#define HASH_INT_EN                      (s_spacc_reg_base + 0x0808)
#define HASH_INT_RAW                     (s_spacc_reg_base + 0x080C)
#define HASH_IN_SMMU_EN                  (s_spacc_reg_base + 0x0810)
#define CHAN0_HASH_DAT_IN                (s_spacc_reg_base + 0x0818)
#define CHAN0_HASH_TOTAL_DAT_LEN         (s_spacc_reg_base + 0x081C)
#define CHANn_HASH_CTRL(id)              (s_spacc_reg_base + 0x0800 + (id)*0x80)
#define CHANn_HASH_IN_NODE_CFG(id)       (s_spacc_reg_base + 0x0804 + (id)*0x80)
#define CHANn_HASH_IN_NODE_START_ADDR(id)(s_spacc_reg_base + 0x0808 + (id)*0x80)
#define CHANn_HASH_IN_BUF_RPTR(id)       (s_spacc_reg_base + 0x080C + (id)*0x80)
#define CHANn_HASH_STATE_VAL(id)         (s_spacc_reg_base + 0x0340 + (id)*0x08)
#define CHANn_HASH_STATE_VAL_ADDR(id)    (s_spacc_reg_base + 0x0344 + (id)*0x08)


#define SPACC_READ(addr)        *(volatile unsigned int *)(addr)
#define SPACC_WRITE(addr, val)  *(volatile unsigned int *)(addr) = (val)

#endif

