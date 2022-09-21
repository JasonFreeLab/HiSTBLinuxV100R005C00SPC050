/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_rng.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_RNG_H__
#define __DRV_RNG_H__

/* add include here */
#include "drv_cipher_ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

HI_S32 DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG);

HI_U32 DRV_CIPHER_Rand(HI_VOID);

HI_S32 DRV_RNG_Init(HI_VOID);

HI_VOID DRV_RNG_DeInit(HI_VOID);

#ifdef __cplusplus
}
#endif
#endif /* __DRV_CIPHER_H__ */

