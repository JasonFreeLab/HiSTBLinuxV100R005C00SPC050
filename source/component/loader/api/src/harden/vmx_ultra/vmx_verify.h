/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : vmx_verify.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2016-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2016-07-29  sdk  N/A               Create this file.
 ******************************************************************************/

#ifndef __VMX_VERIFY_H__
#define __VMX_VERIFY_H__

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
/** \addtogroup     VMX_VERIFY */
/** @{ */  /** <!-- [VMX_VERIFY] */

#define BLSH_IMG_HEADER_BLOCK_NUM           (5)
#define BLSH_IMG_HEADER_MAGINNUMBER_SIZE    (32)
#define BLSH_IMG_HEADER_HEADERVERSION_SIZE  (8)
#define BLSH_IMG_HEADER_RESERVE_SIZE        (31)

#define BLSH_LEN_IMG_HEADER                 (0x2000)
#define BLSH_LEN_IMG_HEADER_SIGN            (0x100)
#define BLSH_POS_IMG_HEADER_SIGN            (BLSH_LEN_IMG_HEADER - BLSH_LEN_IMG_HEADER_SIGN)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     VMX_VERIFY */
/** @{ */  /** <!-- [VMX_VERIFY] */

/****** Enumeration definition ************/

typedef struct tagBLSH_IMAGE_HEAD_S
{
    HI_U8  u8MagicNumber[BLSH_IMG_HEADER_MAGINNUMBER_SIZE];      /**< Magic Number: "Hisilicon_ADVCA_ImgHead_MagicNum" */
    HI_U8  u8HeaderVersion[BLSH_IMG_HEADER_HEADERVERSION_SIZE];  /**< Version: "V000 0003" */
    HI_U32 u32TotalLen;                                          /**< Total length */
    HI_U32 u32CodeOffset;                                        /**< Image offset */
    HI_U32 u32SignedImageLen;                                    /**< Signed Image file size */
    HI_U32 u32SignatureOffset;                                   /**< Signed Image offset */
    HI_U32 u32SignatureLen;                                      /**< Signature length */
    HI_U32 u32BlockNum;                                          /**< Image block number */
    HI_U32 u32BlockOffset[BLSH_IMG_HEADER_BLOCK_NUM];            /**< Each Block offset */
    HI_U32 u32BlockLength[BLSH_IMG_HEADER_BLOCK_NUM];            /**< Each Block length */
    HI_U32 u32SoftwareVerion;                                    /**< Software version */
    HI_U32 u32Reserverd[BLSH_IMG_HEADER_RESERVE_SIZE];
    HI_U32 u32CRC32;                                             /**< CRC32 value */

} BLSH_IMAGE_HEAD_S;

typedef struct tagBLSH_RSA_PUBKEY_S
{
    HI_U8*  pu8N;               /**< point to public modulus  */   /**< CNcomment: 指向RSA公钥N的指针*/
    HI_U8*  pu8E;			    /**< point to public exponent */   /**< CNcomment: 指向RSA公钥E的指针*/
    HI_U16  u16NLen;            /**< length of public modulus, max value is 512Byte*/  /**< CNcomment: RSA公钥N的长度, 最大为512Byte*/
    HI_U16  u16ELen;            /**< length of public exponent, max value is 512Byte*/  /**< CNcomment: RSA公钥E的长度, 最大为512Byte*/
} BLSH_RSA_PUBKEY_S;


/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/*nand and SPI max flash block size*/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     VMX_VERIFY */
/** @{ */  /** <!-- [VMX_VERIFY] */

HI_S32 BLSH_ConfigExternKey(BLSH_RSA_PUBKEY_S* pstPubKey);

HI_S32 BLSH_ClearExternKey(HI_VOID);

HI_S32 BLSH_VerifySignature(HI_U8* pu8Data, HI_U32 u32Size, HI_U8* pu8Signature, HI_U32 u32SignatureSize);

HI_S32 BLSH_VerifyImageHeader(HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize);

HI_S32 BLSH_VerifyImageData(BLSH_IMAGE_HEAD_S* pstImageHeader, HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize);

HI_S32 BLSH_VerifyWholeImage(HI_U8* pu8Data, HI_U32 u32Size);


/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__VMX_VERIFY_H__*/

