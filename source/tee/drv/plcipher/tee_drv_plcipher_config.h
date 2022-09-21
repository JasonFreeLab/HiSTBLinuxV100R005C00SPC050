/******************************************************************************

  Copyright (C), 2004-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_drv_plcipher_config.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __TEE_DRV_PLCIPHER_CONFIG_H__
#define __TEE_DRV_PLCIPHER_CONFIG_H__

#define HI_CRG_BASE_ADDR                     (0xF8A22000)
#if defined(CHIP_TYPE_hi3796mv200)

#define  PLCIPHER_REG_BASE_ADDR_PHY          (0xF9A40000)
#define  PLCIPHER_CHAN_NUM                   8
#define  PLCIPHER_SEC_CHAN_OFFSET            0
#define  PLCIPHER_DSC_NUM                    512     //512*47k = 24M
#define  PLCIPHER_IRQ_NUMBER                 (176 + 32)
#define  PLCIPHER_IRQ_NAME                   "plcipher_safe"

#endif

#endif      /* __TEE_DRV_PLCIPHER_CONFIG_H__ */
