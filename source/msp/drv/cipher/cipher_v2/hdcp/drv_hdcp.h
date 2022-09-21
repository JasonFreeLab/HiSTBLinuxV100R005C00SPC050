/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_hdcp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#define _DRV_HDCP_H_

#include "hi_drv_cipher.h"

HI_S32 DRV_CIPHER_EncryptHDCPKey(CIPHER_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer);
HI_S32 DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey);

#endif
