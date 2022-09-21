/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_keyladder_irdeto.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_KEYLADDER_IRDETO_H__
#define __HI_TEE_KEYLADDER_IRDETO_H__

#include "hi_tee_keyladder.h"
#include "hi_type.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      IRDETO */
/** @{ */  /** <!-- [IRDETO] */

/*
Level: 2/3
Algorithm: TDES or AES
Target: Demux
Access: TCPU/ACPU
*/
#define HI_TEE_KLAD_IRDETO_TYPE_CSA2    0x0200
#define HI_TEE_KLAD_IRDETO_TYPE_CSA3    0x0201
#define HI_TEE_KLAD_IRDETO_TYPE_SP      0x0202
#define HI_TEE_KLAD_IRDETO_TYPE_R2R     0x0203
#define HI_TEE_KLAD_IRDETO_TYPE_TA      0x0204
#define HI_UNF_KLAD_IRDETO_TYPE_CCC     0x0205
#define HI_UNF_KLAD_IRDETO_TYPE_SSUK    0x0206

/**Flag of TA key ladder*/
typedef enum hiTEE_KLAD_IRDETO_TA_KL_FLAG_E
{
    HI_TEE_KLAD_IRDETO_TA_KL_FLAG_HOST_CPU = 0,      /**<last level cw data is ca_din from host cpu config*/
    HI_TEE_KLAD_IRDETO_TA_KL_FLAG_TA_KLAD  = 1,      /**<last level cW data is cwsk_cw from ta key ladder*/
    HI_TEE_KLAD_IRDETO_TA_KL_FLAG_BUTT
} HI_TEE_KLAD_IRDETO_TA_KL_FLAG_E;

typedef struct hiTEE_KLAD_TA_KEY_S
{
    HI_U8 au8Key[HI_TEE_KLAD_MAX_KEY_LEN];
} HI_TEE_KLAD_TA_KEY_S;

/**Trandata */
typedef struct hiTEE_KLAD_TRAN_DATA_S
{
    HI_U32  u32DataSize;
    HI_U8*  pu8TranData;
} HI_TEE_KLAD_TRAN_DATA_S;

/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      IRDETO */
/** @{ */  /** <!-- [IRDETO] */

/**
\brief Set TA flag
\param[in] hKlad    Handle of key ladder
\param[in] enFlag   flag of TA key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_TEE_KLAD_IRDETO_SetTAFlag(const HI_HANDLE hKlad, const HI_TEE_KLAD_IRDETO_TA_KL_FLAG_E enFlag);

/**
\brief Set TA session key
\param[in] hKlad    Handle of key ladder
\param[in] pstKey   session key(level1) of TA key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/

HI_S32 HI_TEE_KLAD_IRDETO_SetTASessionKey(const HI_HANDLE hKlad,const HI_TEE_KLAD_TA_KEY_S* pstKey);

/**
\brief Set TA transform data
\param[in] hKlad    Handle of key ladder
\param[in] pstTrandata   transform data(level2) of TA key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_TEE_KLAD_IRDETO_SetTATranData(const HI_HANDLE hKlad,const HI_TEE_KLAD_TRAN_DATA_S* pstTrandata);

/**
\brief Set TA content key
\param[in] hKlad    Handle of key ladder
\param[in] pstKey   content key(level3) of TA key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_TEE_KLAD_IRDETO_SetTAContentKey(const HI_HANDLE hKlad,const HI_TEE_KLAD_TA_KEY_S* pstKey);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TEE_KEYLADDER_IRDETO_H__ */


