/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_keyladder_dcas.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-03-20
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_KEYLADDER_DCAS_H__
#define __HI_TEE_KEYLADDER_DCAS_H__

#include "hi_tee_keyladder.h"
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup       */
/** @{ */  /** <!-- [DCAS] */

/*
Level: 1
Algorithm: AES
Target Engine: NA
*/
#define HI_TEE_KLAD_DCAS_TYPE_RKD    0x0c00

/*
Level: 3
Algorithm: TDES/AES
Target Engine: Demux - CSA2/CSA3/AES/NOVEL/SM4/TDES; Payload cipher - AES; Multicipher - fixed
*/
#define HI_TEE_KLAD_DCAS_TYPE_K30    0x0c01


/**Vendor ID*/
typedef struct hiTEE_KLAD_VENDOR_ID_S
{
    HI_U8 au8VendorID[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_VENDOR_ID_S;

/**da nonce*/
typedef struct hiTEE_KLAD_DCAS_DA_NONCE_S
{
    HI_U8 au8Nonce[HI_TEE_KLAD_MAX_KEY_LEN];
    HI_U8 au8DaNonce[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_DCAS_DA_NONCE_S;


/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      DCAS */
/** @{ */  /** <!-- [DCAS] */

/**
\brief Generate K30 DA nonce
\param[in] hKlad    Handle of key ladder
\param[in/out] pstDaNonce    pointer to the DA nonce
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_TEE_KLAD_DCAS_K30GenDaNonce(HI_HANDLE hKlad, HI_TEE_KLAD_DCAS_DA_NONCE_S *pstDaNonce);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TEE_KEYLADDER_DCAS_H__ */


