/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_product_define.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/

#ifndef __TEE_HDMI_PRODUCT_DEFINE_H__
#define __TEE_HDMI_PRODUCT_DEFINE_H__





#include "hi_type.h"
#include "tee_hdmi_reg_com.h"
#include "tee_hdmi_reg_crg.h"



HI_VOID TEE_DRV_HDMI_ProdIoCfgSet(HI_VOID);
HI_VOID TEE_DRV_HDMI_ProdCrgInit(HI_VOID);
HI_VOID TEE_DRV_HDMI_ProdCrgDeInit(HI_VOID);


#endif  /* __TEE_HDMI_PRODUCT_DEFINE_H__ */


