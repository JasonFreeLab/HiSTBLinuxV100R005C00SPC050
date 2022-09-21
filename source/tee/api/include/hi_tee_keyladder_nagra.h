/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_keyladder_nagra.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-04-13
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_KEYLADDER_NAGRA_H__
#define __HI_TEE_KEYLADDER_NAGRA_H__

#include "hi_tee_keyladder.h"
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      NAGRA */
/** @{ */  /** <!-- [NAGRA] */

/*
Level: 3
Algorithm: TDES
Target Engine: Demux - CSA2
*/
#define HI_TEE_KLAD_NAGRA_TYPE_CSA2   0x0100

/*
Level: 3
Algorithm: TDES
Target Engine: Demux - CSA3
*/
#define HI_TEE_KLAD_NAGRA_TYPE_CSA3   0x0101

/*
Level: 3
Algorithm: TDES
Target Engine: Demux - AES; Payload cipher - AES; Multicipher - fixed
*/
#define HI_TEE_KLAD_NAGRA_TYPE_AES    0x0102

/*
Level: 3
Algorithm: TDES
Target Engine: Demux - TDES; Multicipher - fixed
*/
#define HI_TEE_KLAD_NAGRA_TYPE_TDES   0x0103

/*
Level: 4 (only need send key to cipher, all keys are already set by bootrom)
Algorithm: TDES
Target Engine: Multicipher - fixed; encrypted register - NA
*/
#define HI_TEE_KLAD_NAGRA_TYPE_FPK    0x0104

/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      NAGRA */
/** @{ */  /** <!-- [NAGRA] */

/**
\brief Send output key of boot key ladder to cipher
\param[in] hKlad    Handle of key ladder
\retval HI_SUCCESS  Success
\retval HI_FAILURE  Failure
*/
HI_S32 HI_TEE_KLAD_NAGRA_SendFPKToCipher(HI_HANDLE hKlad);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TEE_KEYLADDER_NAGRA_H__ */


