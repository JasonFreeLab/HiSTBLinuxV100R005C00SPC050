/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_klad_dcas.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-03-21
Last Modified :
Description   : Key ladder API declaration for DCAS
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_KLAD_DCAS_H__
#define __HI_UNF_KLAD_DCAS_H__

#include "hi_type.h"
#include "hi_unf_klad.h"

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
#define HI_UNF_KLAD_DCAS_TYPE_RKD    0x0c00

/*
Level: 3
Algorithm: TDES/AES
Target Engine: Demux - CSA2/CSA3/AES/NOVEL/SM4/TDES; Payload cipher - AES; Multicipher - fixed
*/
#define HI_UNF_KLAD_DCAS_TYPE_K30    0x0c01


/**da nonce*/
typedef struct hiUNF_KLAD_DCAS_DA_NONCE_S
{
    HI_U8 au8Nonce[HI_UNF_KLAD_MAX_KEY_LEN];
    HI_U8 au8DaNonce[HI_UNF_KLAD_MAX_KEY_LEN];
} HI_UNF_KLAD_DCAS_DA_NONCE_S;


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
HI_S32 HI_UNF_KLAD_DCAS_K30GenDaNonce(HI_HANDLE hKlad, HI_UNF_KLAD_DCAS_DA_NONCE_S *pstDaNonce);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_KLAD_DCAS_H__ */


