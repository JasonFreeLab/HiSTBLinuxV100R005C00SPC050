/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_trng.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_TRNG_H__
#define __DRV_TRNG_H__

/*************************** Structure Definition ****************************/
/** \addtogroup     rsa */
/** @{ */  /** <!-- [rsa] */

/*! \rsa capacity, 0-nonsupport, 1-support */
typedef struct
{
    u32 trng         : 1 ;    /*!<  Support TRNG */
}trng_capacity;

/*! \trng error code */
enum trng_error_code
{
    HI_TRNG_ERR_NO_AVAILABLE = HI_BASE_ERR_BASE_TRNG, /*!< random number invalid */
    HI_TRNG_ERR_TIME_OUT,                             /*!<  timeout */
    HI_TRNG_ERR_NONSUPPORT,                           /*!<  non-support */
};

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      trng */
/** @{ */  /** <!--[trng]*/


/**
\brief get rand number.
\param[out]  randnum rand number.
\param[in]   timeout time out.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 drv_trng_randnum(u32 *randnum, u32 timeout);

/**
\brief  get the trng capacity.
\param[out] capacity The hash capacity.
\retval     NA.
*/
void drv_trng_get_capacity(trng_capacity *capacity);

/** @} */  /** <!-- ==== API declaration end ==== */

#endif
