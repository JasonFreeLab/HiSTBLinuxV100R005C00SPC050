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
#include "drv_trng.h"

/******************************* API Declaration *****************************/
/** \addtogroup      trng */
/** @{ */  /** <!--[trng]*/

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      trng drivers*/
/** @{*/  /** <!-- [trng]*/

/**
\brief get rand number.
\param[out]  randnum rand number.
\param[in]   timeout time out.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 cryp_trng_get_random( u32 *randnum, u32 timeout );

/** @} */  /** <!-- ==== API declaration end ==== */
#endif
