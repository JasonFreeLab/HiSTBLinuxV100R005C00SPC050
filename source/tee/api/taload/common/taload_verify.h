/******************************************************************************

          Copyright (C), 2001-2017, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : taload_verify.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2017-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2016-07-29  sdk        N/A               Create this file.
 ******************************************************************************/

#ifndef __TALOAD_VERIFY_H__
#define __TALOAD_VERIFY_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup     TALOAD_VERIFY */
/** @{ */  /** <!-- [TALOAD_VERIFY] */
#define HISI_MAGIC_NUMBER   "Hisilicon_ADVCA_ImgHead_MagicNum"

#define TALOAD_NUM_IMG_HEADER_BLOCK            (5)
#define TALOAD_LEN_IMG_HEADER_MAGINNUMBER      (32)
#define TALOAD_LEN_IMG_HEADER_HEADERVERSION    (8)
#define TALOAD_LEN_IMG_HEADER_RESERVE          (31)
#define TALOAD_LEN_IMG_HEADER_TAOWNER          (32)
#define TALOAD_LEN_RESERVE                     (4)
#define TALOAD_LEN_UUID                        (16)

#define TALOAD_LEN_PROTECTKEY                  (16)
#define TALOAD_LEN_CONTENT_IV                  (16)
#define TALOAD_LEN_RSA_PUBLIC_KEY_E            (256)
#define TALOAD_LEN_RSA_PUBLIC_KEY_N            (256)

#define TALOAD_LEN_IMG_HEADER                  (0x2000)
#define TALOAD_LEN_IMG_HEADER_SIGN             (0x100)
#define TALOAD_LEN_IMG_HEADER_SIGNDATA         (TALOAD_LEN_IMG_HEADER - TALOAD_LEN_IMG_HEADER_SIGN)

#define TALOAD_HEADER_CHECK(pstImageHeader)    \
    ((TALOAD_LEN_IMG_HEADER >= pstImageHeader->u32TotalLen) \
     || (TALOAD_LEN_IMG_HEADER != pstImageHeader->u32CodeOffset)    \
     || (TALOAD_LEN_IMG_HEADER_SIGN != pstImageHeader->u32SignatureLen) \
     || (pstImageHeader->u32SignedImageLen + pstImageHeader->u32CodeOffset != pstImageHeader->u32SignatureOffset)    \
     || (pstImageHeader->u32SignatureOffset + pstImageHeader->u32SignatureLen != pstImageHeader->u32TotalLen))

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     TALOAD_VERIFY */
/** @{ */  /** <!-- [TALOAD_VERIFY] */

/****** Enumeration definition ************/

typedef enum tagTALOAD_TA_LOAD_TYPE_E
{
    TALOAD_TA_LOAD_TYPE_ROOTCERT      = 0,
    TALOAD_TA_LOAD_TYPE_CERT,
    TALOAD_TA_LOAD_TYPE_TA,
    TALOAD_TA_LOAD_TYPE_BUTT
} TALOAD_TA_LOAD_TYPE_E;                                             /**< u32ImageType in TALOAD_IMAGE_HEAD_S*/

/****** Structure definition **************/

typedef struct tagTALOAD_RSA_KEY_S
{
    HI_U8 au8RSAKeyN[TALOAD_LEN_RSA_PUBLIC_KEY_N];
    HI_U8 au8RSAKeyE[TALOAD_LEN_RSA_PUBLIC_KEY_E];

} TALOAD_RSA_KEY_S;

typedef struct tagTALOAD_IMAGE_HEAD_S
{
    HI_U8  u8MagicNumber[TALOAD_LEN_IMG_HEADER_MAGINNUMBER];           /**< Magic Number: "Hisilicon_ADVCA_ImgHead_MagicNum" */
    HI_U8  u8HeaderVersion[TALOAD_LEN_IMG_HEADER_HEADERVERSION];       /**< Version: "V000 0003" */
    HI_U32 u32TotalLen;                                                /**< Total length */
    HI_U32 u32CodeOffset;                                              /**< Image offset */
    HI_U32 u32SignedImageLen;                                          /**< Signed Image file size */
    HI_U32 u32SignatureOffset;                                         /**< Signed Image offset */
    HI_U32 u32SignatureLen;                                            /**< Signature length */
    HI_U32 u32BlockNum;                                                /**< Image block number */
    HI_U32 u32BlockOffset[TALOAD_NUM_IMG_HEADER_BLOCK];                /**< Each Block offset */
    HI_U32 u32BlockLength[TALOAD_NUM_IMG_HEADER_BLOCK];                /**< Each Block length */
    HI_U32 u32SecVersion;
    HI_U32 u32Reserverd[TALOAD_LEN_IMG_HEADER_RESERVE];
    HI_U32 u32CRC32;                                                   /**< CRC32 value */
    HI_U32 u32ImageType;
    HI_U32 u32SegmentID;                                               /**< Segment ID */
    HI_U32 u32FuncVersion;                                             /**< Function version */

} TALOAD_IMAGE_HEAD_S;

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     TALOAD_VERIFY */
/** @{ */  /** <!-- [TALOAD_VERIFY] */

HI_S32 TALOAD_Decrypt(HI_U8* pu8Data, HI_U32 u32Size, HI_U8* pu8ProtectKey, HI_U32 u32KeyladderType);

HI_S32 TALOAD_VerifySignature
(
    HI_U8* pu8Data,
    HI_U32 u32Size,
    HI_U8* pu8Signature,
    HI_U32 u32SignatureSize,
    TALOAD_RSA_KEY_S* pstRSAKey
);

HI_S32 TALOAD_VerifyInit(HI_VOID);

HI_S32 TALOAD_VerifyDeInit(HI_VOID);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__TALOAD_VERIFY_H__*/

