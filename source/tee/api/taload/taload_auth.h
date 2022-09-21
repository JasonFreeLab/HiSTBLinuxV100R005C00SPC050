/******************************************************************************

          Copyright (C), 2001-2017, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : taload_auth.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2017-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2017-07-29  sdk        N/A               Create this file.
 ******************************************************************************/

#ifndef __TALOAD_AUTH_H__
#define __TALOAD_AUTH_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"
#include "taload_verify.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup     TALOAD_AUTH */
/** @{ */  /** <!-- [TALOAD_AUTH] */

#define TALOAD_TA_NOT_SIGNED_TAG                   (0x2A13C812)
#define TALOAD_TA_NOT_ENCRYPTED_TAG                (0x2A13C812)
#define TALOAD_TA_VERSION_CHECK_DISABLE            (0x2A13C812)
#define TALOAD_TA_MSID_CHECK_DISABLE               (0x2A13C812)
#define TALOAD_TA_UPDATE_TAG                       (0x2A13C812)

#define TALOAD_UINT_MAX 0xFFFFFFFF

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     TALOAD_AUTH */
/** @{ */  /** <!-- [TALOAD_AUTH] */

/****** Enumeration definition ************/

typedef enum tagTALOAD_TA_KLAD_TYPE_E
{
    TALOAD_TA_KLAD_TYPE_CATA      = 0,
    TALOAD_TA_KLAD_TYPE_HISITA,
    TALOAD_TA_KLAD_TYPE_STBTA,
    TALOAD_TA_KLAD_TYPE_BUTT
} TALOAD_TA_KLAD_TYPE_E;

/****** Structure definition **************/

typedef struct tagTALOAD_VERIFY_PARAM_S
{
    HI_U32  u32EncryptFlag;
    HI_U32  u32KeyladderType;
    HI_U32  u32SignFlag;
    HI_U8*  pu8ProtectKey;
    TALOAD_RSA_KEY_S* pstRSAKey;

} TALOAD_VERIFY_PARAM_S;

typedef struct tagTALOAD_TA_CERT_PAYLOAD_S
{
    HI_U32 u32EncryptFlag;
    HI_U32 u32SignFlag;
    HI_U32 u32KeyladderType;                                            /**0 for CA_TA type, 1 for hisi TA type, 2 for stb type */
    HI_U8  au8TAUUID[TALOAD_LEN_UUID];
    HI_U8  au8TaProtectKey[TALOAD_LEN_PROTECTKEY];
    TALOAD_RSA_KEY_S stTaPublicKey;
    HI_U8  au8TAOwner[TALOAD_LEN_IMG_HEADER_TAOWNER];                   /**<TA Owner: such as "Hisilicon" */
    HI_U32 u32TAID;                                                     /**<value is unique for any ta*/
    HI_U32 u32AutoAddNewTaFlag;                                         /**<0x2A13C812:support add this new TA after the product released.*/
    HI_U32 u32TAVersionCheckFlag;                                       /**<0x2A13C812:Don't need TA versioning check.*/
    HI_U32 u32TAMSIDCheckFlag;                                          /**<0x2A13C812:Don't need TA MSID check.*/

} TALOAD_TA_CERT_PAYLOAD_S;

typedef struct tagTALOAD_TA_ROOT_CERT_PAYLOAD_S
{
    TALOAD_RSA_KEY_S stTaRootPubicKey;
    HI_U8  au8TAOwner[TALOAD_LEN_IMG_HEADER_TAOWNER];                   /**<TA Owner: such as "Hisilicon" */

} TALOAD_TA_ROOT_CERT_PAYLOAD_S;

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     TALOAD_AUTH */
/** @{ */  /** <!-- [TALOAD_AUTH] */

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__TALOAD_AUTH_H__*/

