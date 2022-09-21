/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_keyladder_suma.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-03-27
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_KEYLADDER_SUMA_H__
#define __HI_TEE_KEYLADDER_SUMA_H__

#include "hi_type.h"
#include "hi_tee_keyladder.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup       */
/** @{ */  /** <!-- [SUMA] */

/*
Level: 2
Algorithm: TDES
Target Engine: NA
*/
#define HI_TEE_KLAD_SUMA_TYPE_LP      0x0500

/**Data key*/
typedef struct hiTEE_KLAD_SUMA_DATA_KEY_S
{
    HI_U8 au8EncKey[HI_TEE_KLAD_MAX_KEY_LEN];
    HI_U8 au8DataKey[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_SUMA_DATA_KEY_S;


/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      SUMA */
/** @{ */  /** <!-- [SUMA] */

/**
\brief Generate Datakey(lp keyladder)
\param[in] hKlad    Handle of key ladder
\param[in/out] pstKey    pointer to the DataKey
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_TEE_KLAD_SUMA_GenerateDataKey(const HI_HANDLE hKlad, HI_TEE_KLAD_SUMA_DATA_KEY_S* pstKey);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TEE_KEYLADDER_SUMA_H__ */


