/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_tee_cipher.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __CRYP_TRNG_H_
#define __CRYP_TRNG_H_

#include "drv_osal_lib.h"
#include "drv_hdcp.h"

/******************************* API Declaration *****************************/
/** \addtogroup      hdcp */
/** @{ */  /** <!--[hdcp]*/

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      hdcp drivers*/
/** @{*/  /** <!-- [hdcp]*/

/**
\brief  HDCP encrypt/decrypt use AES-CBC, IV is all zero.
\param[in]  keysel Hdcp root key sel.
\param[in]  ramsel hdmi ram sel.
\param[in]  in The input data.
\param[out] out The input data.
\param[out] len The input data length, must align with 16.
\param[in]  operation encrypt or decrypt.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 cryp_hdcp_crypto(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u32 *hostkey,
                 u32 *in, u32 *out, u32 len, u32 operation);

/** @} */  /** <!-- ==== API declaration end ==== */
#endif
