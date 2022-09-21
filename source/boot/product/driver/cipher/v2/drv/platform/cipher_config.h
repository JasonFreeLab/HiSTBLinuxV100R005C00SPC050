/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cipher_config.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __CIPHER_CONFIG_H_
#define __CIPHER_CONFIG_H_

//#define HDCP_ENABLE
//#define SHA3_ENABLE
#define IFEP_RSA_ENABLE
//#define SIC_RSA

//#define SMMU_ENABLE


#define REE_SECURE_ENABLE //REE without TEE
//#define SM2_ENABLE

//#define STANDBY_ENABLE

//#define INT_ENABLE

#define  CIPHER_IRQ_NUMBER                      (126 + 32)

#define  CIPHER_RNG_REG_BASE_ADDR_PHY           (0xF8ABC000)
#define  CIPHER_KLAD_REG_BASE_ADDR_PHY          (0xF8A90000)
#define  CIPHER_MMU_REG_BASE_ADDR_PHY           (0xF99F0000)
#define  CIPHER_CIPHER_REG_BASE_ADDR_PHY        (0xF9A00000)
#define  CIPHER_RSA_REG_BASE_ADDR_PHY           (0xF9A30000)
#define  CIPHER_HDMI_REG_BASE_ADDR_PHY          (0XF8A208B0)
#define  CIPHER_SHA3_REG_BASE_ADDR_PHY          (0xF9A10000)
#define  CIPHER_SM2_REG_BASE_ADDR_PHY           (0xF9A38000)

#define  CIPHER_RSA_CRG_ADDR_PHY                (0xF8A80060)
#define  CIPHER_SHA3_CRG_ADDR_PHY               (0xF8A80060)
#define  CIPHER_SPACC_CRG_ADDR_PHY              (0XF8A22410)

#endif

