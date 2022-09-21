/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     :hi_drv_cipher.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __HI_TEE_DRV_CIPHER_H__
#define __HI_TEE_DRV_CIPHER_H__

#include "hi_type.h"
#include "hi_tee_cipher.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#define CIPHER_SOFT_CHAN_NUM       CIPHER_CHAN_NUM
#define CIPHER_INVALID_CHN        (0xffffffff)
#define CIPHER_MAX_NODE_BUF_SIZE  (0xFFFF0)   //1M-16
#define CIPHER_MAX_RSA_KEY_LEN    (512)
#define HASH_OUTPUT_SIZE_WORD     (1600/8/4)    //sha3 state

#define  HDCP_KEY_RAM_SIZE                      320
#define  HDCP_KEY_PRIME_SIZE                    320
#define  HDCP_KEY_TOOL_FILE_SIZE                384
#define  HDCP_KEY_CHIP_FILE_SIZE               (HDCP_KEY_RAM_SIZE + 12)

#define HASH_ALG_SHA2                           0x01
#define HASH_ALG_SHA3                           0x02
#define HASH_ALG_SM3                            0x03

#define HASH_MODE_RAW                           0x01
#define HASH_MODE_MAC                           0x02
#define HASH_MODE_SHAKE                         0x03

typedef struct hiCIPHER_DATA_INFO_S
{
    HI_U32  u32src;
    HI_U32  u32dest;
    HI_U32  u32length;
    HI_BOOL bDecrypt;
    HI_U32  u32DataPkg[4];
}HI_DRV_CIPHER_DATA_INFO_S;

typedef enum hiHI_DRV_HASH_STEP
{
    HI_DRV_HASH_STEP_UPDATE = 0x0,
    HI_DRV_HASH_STEP_INIT = 0x01,
    HI_DRV_HASH_STEP_FINAL = 0x02,
}HI_DRV_HASH_STEP_E;

typedef struct  hiCIPHER_HANDLE_S
{
    HI_HANDLE hCIHandle;
    HI_TEE_CIPHER_ATTS_S stCipherAtts;
}CIPHER_HANDLE_S;

typedef struct  hiCIPHER_DATA_S
{
    HI_HANDLE CIHandle;
    HI_U32 ScrPhyAddr;
    HI_U32 DestPhyAddr;
    HI_U32 u32DataLength;
}CIPHER_DATA_S;

typedef struct  hiCIPHER_PKG_S
{
    HI_HANDLE CIHandle;
    HI_U32 u32PkgNum;
    HI_TEE_CIPHER_DATA_S* pu8Pkg;
}CIPHER_PKG_S;

typedef struct hiCIPHER_Config_CTRL
{
    HI_HANDLE CIHandle;
    HI_TEE_CIPHER_CTRL_S CIpstCtrl;
}CIPHER_Config_CTRL;

typedef struct hiCIPHER_WAIT_DONE
{
    HI_HANDLE CIHandle;
    HI_U32    u32TimeOut;;
}CIPHER_WAIT_DONE_S;

typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 u32Key[12];                              /**< Key input, EK||AK||SK for SM1 */ /**< CNcomment:????, ???SM1,????AK||EK||SK*/
    HI_U32 u32OddKey[8];                            /**< Key input, Old Key */            /**< CNcomment:????, ???*/
    HI_U32 u32IV[4];                                /**< Initialization vector (IV) */                                                                                    /**< CNcomment:???? */
    HI_BOOL bKeyByCA;                               /**< Encryption using advanced conditional access (CA) or decryption using keys */                                    /**< CNcomment:???????CA?????Key */
    HI_TEE_CIPHER_CA_TYPE_E enCaType;               /**< Select keyladder type when using advanced CA */                                                                  /**< CNcomment:?????CA?,???????keyladder */
    HI_TEE_CIPHER_ALG_E enAlg;                      /**< Cipher algorithm */                                                                                              /**< CNcomment:???? */
    HI_TEE_CIPHER_BIT_WIDTH_E enBitWidth;           /**< Bit width for encryption or decryption */                                                                        /**< CNcomment:???????? */
    HI_TEE_CIPHER_WORK_MODE_E enWorkMode;           /**< Operating mode */                                                                                                /**< CNcomment:???? */
    HI_TEE_CIPHER_KEY_LENGTH_E enKeyLen;            /**< Key length */                                                                                                    /**< CNcomment:???? */
    HI_TEE_CIPHER_CTRL_CHANGE_FLAG_S stChangeFlags; /**< control information exchange choices, we default all woulde be change except they have been in the choices */    /**< CNcomment:????????,??????????????? */
    HI_TEE_CIPHER_SM1_ROUND_E enSm1Round;           /**< SM1 round number, should be 8, 10, 12 or 14*/                                                                                                    /**< CNcomment:sm1??????? */
    HI_U32 u32IVLen;                                /**< IV lenght for CCM/GCM, which is an element of {4,6,8,10,12,14,16} for CCM, and is an element of [1-16] for GCM*/  /**< CNcomment: CCM/GCM?IV??,CCM?????{7, 8, 9, 10, 11, 12, 13}, GCM?????[1-16]*/
    HI_U32 u32TagLen;                               /**< Tag lenght for CCM which is an element of {4,6,8,10,12,14,16}*/          /**< CNcomment: CCM?TAG??,????{4,6,8,10,12,14,16}*/
    HI_U32 u32ALen;                                 /**< Associated data for CCM and GCM*/                                        /**< CNcomment: CCM/GCM???????*/
    HI_U32 u32APhyAddr;                             /**< Physical address of Associated data for CCM and GCM*/                                        /**< CNcomment: CCM/GCM???????*/
}CIPHER_CONFIG_CTRL_EX;

typedef struct
{
    HI_U32 hCIHandle;
    HI_TEE_CIPHER_UR_S stCipherUR;
}CIPHER_USAGE_RULE;

typedef struct
{
    HI_TEE_CIPHER_HASH_TYPE_E enShaType;
    HI_U32  u32HardChn;
    HI_U32  u32ShaVal[16];
    HI_U32  u32DataPhy;
    HI_U32  u32DataLen;
}CIPHER_HASH_DATA_S;

typedef struct hiCIPHER_HASH_INIT_S
{
    HI_TEE_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle;
}CIPHER_HASH_INIT_S;

typedef struct hiCIPHER_HASH_UPDATE_S
{
    HI_HANDLE HashHandle;
    HI_U8 *pu8InputData;
    HI_U32 u32InputDataLen;
}CIPHER_HASH_UPDATE_S;

typedef struct hiCIPHER_HASH_FINISH_S
{
    HI_HANDLE HashHandle;
    HI_U8 *pu8OutputHash;
}CIPHER_HASH_FINISH_S;

typedef struct
{
    HI_U32 u32TimeOutUs;
	HI_U32 u32RNG;
}CIPHER_RNG_S;

typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 u32TagLen;
    HI_U32 u32Tag[4];
}CIPHER_TAG_S;

typedef struct  hiCIPHER_INFO_S
{
    HI_HANDLE CIHandle;
    HI_TEE_CIPHER_INFO_S stInfo;
}CIPHER_INFO_S;

typedef struct hiCIPHER_RSA_DATA_S
{
    HI_U8  *pu8Input;
    HI_U8  *pu8Output;
    HI_U32  u32DataLen;
    HI_U8  *pu8N;
	HI_U8  *pu8K;
    HI_U8  *pu8P;                      /*!<  1st prime factor  */ /**< CNcomment: 指向RSA私钥P的指针*/
    HI_U8  *pu8Q;                      /*!<  2nd prime factor  */ /**< CNcomment: 指向RSA私钥Q的指针*/
    HI_U8  *pu8DP;                     /*!<  D % (P - 1)       */ /**< CNcomment: 指向RSA私钥DP的指针*/
    HI_U8  *pu8DQ;                     /*!<  D % (Q - 1)       */ /**< CNcomment: 指向RSA私钥DQ的指针*/
    HI_U8  *pu8QP;                     /*!<  1 / (Q % P)       */ /**< CNcomment: 指向RSA私钥QP的指针*/
    HI_U16 u16NLen;
    HI_U16 u16KLen;
    HI_U16 u16DLen;                   /**< length of private exponent */ /**< CNcomment: RSA私钥D的长度*/
    HI_U16 u16PLen;                   /**< length of 1st prime factor */ /**< CNcomment: RSA私钥P的长度*/
    HI_U16 u16QLen;                   /**< length of 2nd prime factor */ /**< CNcomment: RSA私钥Q的长度*/
    HI_U16 u16DPLen;                  /**< length of D % (P - 1) */      /**< CNcomment: RSA私钥DP的长度*/
    HI_U16 u16DQLen;                  /**< length of D % (Q - 1) */      /**< CNcomment: RSA私钥DQ的长度*/
    HI_U16 u16QPLen;                  /**< length of 1 / (Q % P) */      /**< CNcomment: RSA私钥QP的长度*/
}CIPHER_RSA_DATA_S;

typedef struct hiSM2_SIGN_DATA_S
{
    HI_U32 u32e[SM2_LEN_IN_WROD];
    HI_U32 u32d[SM2_LEN_IN_WROD];
    HI_U32 u32r[SM2_LEN_IN_WROD];
    HI_U32 u32s[SM2_LEN_IN_WROD];
}SM2_SIGN_DATA_S;

typedef struct hiSM2_VERIFY_DATA_S
{
    HI_U32 u32e[SM2_LEN_IN_WROD];
    HI_U32 u32Px[SM2_LEN_IN_WROD];
    HI_U32 u32Py[SM2_LEN_IN_WROD];
    HI_U32 u32r[SM2_LEN_IN_WROD];
    HI_U32 u32s[SM2_LEN_IN_WROD];
}SM2_VERIFY_DATA_S;

typedef struct hiSM2_ENC_DATA_S
{
    HI_U32 u32Px[SM2_LEN_IN_WROD];
    HI_U32 u32Py[SM2_LEN_IN_WROD];
    HI_U32 u32C1x[SM2_LEN_IN_WROD];
    HI_U32 u32C1y[SM2_LEN_IN_WROD];
    HI_U32 u32X2[SM2_LEN_IN_WROD];
    HI_U32 u32Y2[SM2_LEN_IN_WROD];
}SM2_ENC_DATA_S;

typedef struct hiSM2_DEC_DATA_S
{
    HI_U32 u32d[SM2_LEN_IN_WROD];
    HI_U32 u32C1x[SM2_LEN_IN_WROD];
    HI_U32 u32C1y[SM2_LEN_IN_WROD];
    HI_U32 u32X2[SM2_LEN_IN_WROD];
    HI_U32 u32Y2[SM2_LEN_IN_WROD];
}SM2_DEC_DATA_S;

typedef struct hiSM2_KEY_DATA_S
{
    HI_U32 u32d[SM2_LEN_IN_WROD];
    HI_U32 u32Px[SM2_LEN_IN_WROD];
    HI_U32 u32Py[SM2_LEN_IN_WROD];
}SM2_KEY_DATA_S;

/** RSA private key struct */
/** CNcomment:RSA私钥结构体 */
typedef struct
{
    HI_U8 *pu8N;                      /*!<  public modulus    */ /**< CNcomment: 指向RSA公钥N的指针*/
    HI_U8 *pu8E;                      /*!<  public exponent   */ /**< CNcomment: 指向RSA公钥E的指针*/
    HI_U8 *pu8D;                      /*!<  private exponent  */ /**< CNcomment: 指向RSA私钥D的指针*/
    HI_U8 *pu8P;                      /*!<  1st prime factor  */ /**< CNcomment: 指向RSA私钥P的指针*/
    HI_U8 *pu8Q;                      /*!<  2nd prime factor  */ /**< CNcomment: 指向RSA私钥Q的指针*/
    HI_U8 *pu8DP;                     /*!<  D % (P - 1)       */ /**< CNcomment: 指向RSA私钥DP的指针*/
    HI_U8 *pu8DQ;                     /*!<  D % (Q - 1)       */ /**< CNcomment: 指向RSA私钥DQ的指针*/
    HI_U8 *pu8QP;                     /*!<  1 / (Q % P)       */ /**< CNcomment: 指向RSA私钥QP的指针*/
    HI_U16 u16NLen;                   /**< length of public modulus */   /**< CNcomment: RSA公钥N的长度*/
    HI_U16 u16ELen;                   /**< length of public exponent */  /**< CNcomment: RSA公钥E的长度*/
    HI_U16 u16DLen;                   /**< length of private exponent */ /**< CNcomment: RSA私钥D的长度*/
    HI_U16 u16PLen;                   /**< length of 1st prime factor */ /**< CNcomment: RSA私钥P的长度*/
    HI_U16 u16QLen;                   /**< length of 2nd prime factor */ /**< CNcomment: RSA私钥Q的长度*/
    HI_U16 u16DPLen;                  /**< length of D % (P - 1) */      /**< CNcomment: RSA私钥DP的长度*/
    HI_U16 u16DQLen;                  /**< length of D % (Q - 1) */      /**< CNcomment: RSA私钥DQ的长度*/
    HI_U16 u16QPLen;                  /**< length of 1 / (Q % P) */      /**< CNcomment: RSA私钥QP的长度*/
}CIPHER_RSA_PRI_KEY_S;

typedef struct hiCIPHER_RSA_KEY_S
{
    CIPHER_RSA_PRI_KEY_S stPriKey;
    HI_U32 u32NumBits;
    HI_U32 u32Exponent;
}CIPHER_RSA_KEY_S;

typedef struct  hiCIPHER_TEST_DATA_S
{
    HI_U32 u32Cmd;
    HI_VOID *pu8Param;
    HI_U32  u32ParamSize;
}CIPHER_TEST_DATA_S;

typedef struct  hiCIPHER_PBKDF2_DATA_S
{
    HI_TEE_CIPHER_PBKDF2_S stInfo;
    HI_U8 *pu8Output;
}CIPHER_PBKDF2_DATA_S;

typedef struct  hiCIPHER_CENC_DECRYPT_S
{
    HI_HANDLE hCipher;
    HI_U8 u8Key[32];
    HI_U8 u8IV[16];
    HI_U32 u32NonSecInputPhyAddr;
    HI_U32 u32SecOutputPhyAddr;
    HI_U32 u32ByteLength;
    HI_U32 u32FirstEncryptOffset;
    HI_TEE_CIPHER_SUBSAMPLE_S *pstSubSample;
    HI_U32 u32SubsampleNum;
}CIPHER_CENC_DECRYPT_S;

typedef enum
{
    CIPHER_TEST_PRINT_PHY = 0x01,
    CIPHER_TEST_PRINT_VIA,
    CIPHER_TEST_MEMSET,
    CIPHER_TEST_MEMCMP,
    CIPHER_TEST_MEMCPY,
    CIPHER_TEST_MEMCMP_PHY,
    CIPHER_TEST_READ_REG,
    CIPHER_TEST_WRITE_REG,
    CIPHER_TEST_AES  = 0x10,
    CIPHER_TEST_HMAC,
    CIPHER_TEST_RSA,
    CIPHER_TEST_HASH,
    CIPHER_TEST_DES,
    CIPHER_TEST_RSA_PRIM,
    CIPHER_TEST_RSA_KG,
    CIPHER_TEST_RND,
    CIPHER_TEST_SM2,
    CIPHER_TEST_CBC_CTS,
    CIPHER_TEST_ACCESS_SEC_MEM,
    CIPHER_TEST_BUTT,
}CIPHER_TEST;

HI_S32 HI_DRV_CIPHER_CreateHandle(CIPHER_HANDLE_S *pstCIHandle, HI_VOID *file);
HI_S32 HI_DRV_CIPHER_ConfigChn(HI_U32 softChnId, HI_TEE_CIPHER_CTRL_S *pConfig);
HI_S32 HI_DRV_CIPHER_ConfigChnEx(HI_U32 softChnId, CIPHER_CONFIG_CTRL_EX *pConfig);
HI_S32 HI_DRV_CIPHER_GetHandleConfig(CIPHER_Config_CTRL *pstCipherConfig);
HI_S32 HI_DRV_CIPHER_GetHandleConfigEx(CIPHER_CONFIG_CTRL_EX *pstCipherConfig);
HI_S32 HI_DRV_CIPHER_SetUsageRule(CIPHER_USAGE_RULE *pstUsageRule);
HI_S32 HI_DRV_CIPHER_SetIV(HI_HANDLE hCIHandle, HI_U8 *pu8IV, HI_U32 u32IVLen);
HI_S32 HI_DRV_CIPHER_GetIV(HI_U32 ChnId, HI_U32 u32IV[4]);
HI_S32 HI_DRV_CIPHER_SetIV(HI_HANDLE hCIHandle,  HI_U8 *pu8IV, HI_U32 u32IVLen);
HI_S32 HI_DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn);
HI_S32 HI_DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData);
HI_S32 HI_DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData);
HI_S32 HI_DRV_CIPHER_EncryptMulti(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_DecryptMulti(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_EncryptMultiAsyn(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_DecryptMultiAsyn(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_WaitDone(CIPHER_WAIT_DONE_S *pstWaitDone);
HI_S32 HI_DRV_CIPHER_HashWaitDone(HI_HANDLE handle);
HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG);
HI_S32 HI_DRV_CIPHER_SoftReset(HI_VOID);
HI_S32 HI_DRV_SHA2_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_SHA2_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_SHA2_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_SHA3_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_SHA3_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_SHA2_CalcHashMulti(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_SHA3_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_GetTag(CIPHER_TAG_S *pstTag);
HI_S32 HI_DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData);

HI_VOID HI_DRV_CIPHER_Suspend(HI_VOID);
HI_S32 HI_DRV_CIPHER_Resume(HI_VOID);

HI_S32 HI_DRV_SM2_Sign(SM2_SIGN_DATA_S *pstSignData);
HI_S32 HI_DRV_SM2_Verify(SM2_VERIFY_DATA_S *pstVerifyData);
HI_S32 HI_DRV_SM2_Encrypt(SM2_ENC_DATA_S *pstEncData);
HI_S32 HI_DRV_SM2_Decrypt(SM2_DEC_DATA_S *pstDecData);
HI_S32 HI_DRV_SM2_Key(SM2_KEY_DATA_S *pstKeyData);

#if 1
static const HI_U32 s_u32p[SM2_LEN_IN_WROD] =  {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF};
static const HI_U32 s_u32a[SM2_LEN_IN_WROD] =  {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFCFFFFFF};
static const HI_U32 s_u32b[SM2_LEN_IN_WROD] =  {0x9EFAE928, 0x345E9F9D, 0x4B9E5A4D, 0xA70965CF, 0xF58997F3, 0x928FAB15, 0x41BDBCDD, 0x930E944D};
static const HI_U32 s_u32n[SM2_LEN_IN_WROD] =  {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x6BDF0372, 0x2B05C621, 0x09F4BB53, 0x2341D539};
static const HI_U32 s_u32n1[SM2_LEN_IN_WROD] = {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x6BDF0372, 0x2B05C621, 0x09F4BB53, 0x2241D539};
static const HI_U32 s_u32n2[SM2_LEN_IN_WROD] = {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x6BDF0372, 0x2B05C621, 0x09F4BB53, 0x2141D539};
static const HI_U32 s_u32Gx[SM2_LEN_IN_WROD] = {0x2CAEC432, 0x1981191F, 0x4604995F, 0x94C9396A, 0xBF0BE38F, 0xE10B66F2, 0x89455A71, 0xC7744C33};
static const HI_U32 s_u32Gy[SM2_LEN_IN_WROD] = {0xA23637BC, 0x9C77F6F4, 0xE3CEBD59, 0x5321696B, 0x7C87A9D0, 0x40472AC6, 0xE532DF02, 0xA0F03921};
static const HI_U32 s_u32P[SM2_LEN_IN_WROD]	=  {0x04000000, 0x02000000, 0x01000000, 0x01000000, 0x02000000, 0xFFFFFFFF, 0x02000000, 0x03000000};
static const HI_U32 s_u32wp[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01000000};
static const HI_U32 s_u32N[SM2_LEN_IN_WROD] =  {0x12E4B51E, 0x3B3D2BA2, 0x4CC80F62, 0xD4E0FF3A, 0x4A506434, 0xFAA26FDE, 0xAF921190, 0x204F117C};
static const HI_U32 s_u32wn[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x889E7F32, 0x75093572};
static const HI_U32 s_u321[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01000000};
static const HI_U32 s_u320[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
static const HI_U32 s_u32ma[SM2_LEN_IN_WROD] = {0xFBFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFCFFFFFF, 0x03000000, 0xFFFFFFFF, 0xFCFFFFFF};
static const HI_U32 s_u32mb[SM2_LEN_IN_WROD] = {0x88E10F24, 0xC8E220BA, 0x50817952, 0x3C1CA55E, 0x9A37CF71, 0xAB37B5E9, 0x6330D290, 0x42DDC02B};
static const HI_U32 s_u32m1[SM2_LEN_IN_WROD] = {0x01000000, 0x00000000, 0x00000000, 0x00000000, 0x9420fc8d, 0xd4fa39de, 0xf60b44ac, 0xddbe2ac6};
#else
static const HI_U32 s_u32p[SM2_LEN_IN_WROD] =  {0x9ED64285, 0x184F044C, 0x3524B9E8, 0xDEF76FBF, 0x91837245, 0x7D51455C, 0x8BDB2E72, 0xC3DFF108};
static const HI_U32 s_u32a[SM2_LEN_IN_WROD] =  {0xB4687978, 0xFDC332FA, 0x2E841724, 0xFFFEBB73, 0x8B843C2F, 0xE0D73168, 0x8B2265EC, 0x98E43739};
static const HI_U32 s_u32b[SM2_LEN_IN_WROD] =  {0xD3C6E463, 0x840C3BB2, 0x4142F89C, 0x48FE4B48, 0xA5591DF6, 0x6EA06BB1, 0xDAD1126E, 0x9A24C527};
static const HI_U32 s_u32n[SM2_LEN_IN_WROD] =  {0x9ED64285, 0x184F044C, 0x3524B9E8, 0xDDF76FBF, 0x63207729, 0x8D628504, 0xE74EE75A, 0xB7792EC3};
static const HI_U32 s_u32n1[SM2_LEN_IN_WROD] = {0x9ED64285, 0x184F044C, 0x3524B9E8, 0xDDF76FBF, 0x63207729, 0x8D628504, 0xE74EE75A, 0xB6792EC3};
static const HI_U32 s_u32n2[SM2_LEN_IN_WROD] = {0x9ED64285, 0x184F044C, 0x3524B9E8, 0xDDF76FBF, 0x63207729, 0x8D628504, 0xE74EE75A, 0xB5792EC3};
static const HI_U32 s_u32Gx[SM2_LEN_IN_WROD] = {0xD6EB1D42, 0xB6EA621B, 0xEB346474, 0x5E31CCC3, 0x3B0B2232, 0xDC0BD5AD, 0x146C4E4C, 0x3DD4ED7F};
static const HI_U32 s_u32Gy[SM2_LEN_IN_WROD] = {0x2B518006, 0x072CB4CB, 0xD24973D4, 0xC4703B15, 0xFCFDD7E5, 0xA16EA3BF, 0xB94158A8, 0xA2096EE4};
static const HI_U32 s_u32P[SM2_LEN_IN_WROD]	=  {0x2952E50A, 0x6AD93C28, 0xDA874DEE, 0x6CC6D890, 0xA82D37EB, 0x36C6C93F, 0x469C573D, 0xF218DEF6};
static const HI_U32 s_u32wp[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0C38A0A2, 0x1577F750};
static const HI_U32 s_u32N[SM2_LEN_IN_WROD] =  {0x3AD33C62, 0x7FF548F6, 0xDB0BC0BC, 0xC3DCD0E3, 0x2AF545D5, 0x840BDC3A, 0x942B21CE, 0x53D02711};
static const HI_U32 s_u32wn[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3E06E30D, 0xF94BF562};
static const HI_U32 s_u321[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01000000};
static const HI_U32 s_u320[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
static const HI_U32 s_u32ma[SM2_LEN_IN_WROD] = {0xDC7F6B83, 0xAFCB99B2, 0x8F526642, 0x62D2CE10, 0xF7FA815B, 0x8B1ABE9B, 0x7E404156, 0x975E23D7};
static const HI_U32 s_u32mb[SM2_LEN_IN_WROD] = {0x2C57396F, 0x1E3A0D79, 0xE6E38AC3, 0x7B8C4C77, 0x887656E0, 0x4F557657, 0x206FAEF2, 0x925DCBFD};
static const HI_U32 s_u32m1[SM2_LEN_IN_WROD] = {0x6129BD7A, 0xE7B0FBB3, 0xCADB4617, 0x22089040, 0x9CDF88D6, 0x729D7AFB, 0x18B118A5, 0x4986D13C};
#endif

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* End of #ifndef __HI_TEE_DRV_CIPHER_H__*/

