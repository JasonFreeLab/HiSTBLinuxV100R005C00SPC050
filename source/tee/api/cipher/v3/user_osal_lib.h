/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : user_osal_lib.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __USER_OSAL_LIB_H__
#define __USER_OSAL_LIB_H__
#include <hi_tee_module_id.h>
#include <hi_tee_ta_al.h>
#include "hi_tee_debug.h"
#include "hi_tee_cipher.h"
#include "tee_drv_cipher_kapi.h"
#include "mpi_cipher.h"

#define LOG_D_MODULE_ID        HI_ID_CIPHER
#define LOG_D_FUNCTRACE        (0)
#define LOG_D_UNFTRACE         (0)
#include "hi_tee_debug.h"

#define HI_LOG_CHECK_PARAM     HI_TEE_CHECK_PARAM

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/*! \****************************** API Declaration *****************************/
/*! \addtogroup    osal lib */
/** @{ */  /** <!--[osal]*/

void print_string(const char*name, u8 *string, u32 size);

#define HI_PRINT                            ta_printf

#define crypto_malloc(x)                    (0 < (x) ? tee_hal_malloc(x) : HI_NULL)
#define crypto_free(x)                      {if(HI_NULL != (x) ) tee_hal_free(x);}

#define PTHREAD_MUTEX_INITIALIZER            HI_NULL
#define crypto_mutex                         void *
#define crypto_mutex_init(x)                 0
#define crypto_mutex_lock(x)                 0
#define crypto_mutex_unlock(x)               0
#define crypto_mutex_destroy(x)              0

#define crypto_open(a, b, c)                 0
#define crypto_close(x)                      0

#define CRYPTO_IOCTL(cmd, argp)    \
        __tee_hisilicon_ioctl(HI_MODULE_ID_CIPHER, cmd, argp, 0)

#endif  /* End of #ifndef __HI_DRV_CIPHER_H__*/
