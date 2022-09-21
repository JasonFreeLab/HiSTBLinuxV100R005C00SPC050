/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_rng.c
  Version       : Initial Draft
  Author        :
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"

HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber, HI_U32 u32TimeOutUs)
{
    HI_S32 Ret = HI_FAILURE;
    CIPHER_RNG_S stRNG;

    INLET_PARAM_CHECK_POINT_NULL(pu32RandomNumber);

    stRNG.u32RNG = 0;
    stRNG.u32TimeOutUs = u32TimeOutUs;
    Ret = cipher_ioctl(g_CipherDevFd, CMD_CIPHER_GETRANDOMNUMBER, &stRNG);

    if (Ret == HI_SUCCESS)
    {
        *pu32RandomNumber = stRNG.u32RNG;
    }

    return Ret;
}

