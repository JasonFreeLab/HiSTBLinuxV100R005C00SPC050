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

#ifndef __HI_DRV_CIPHER_H__
#define __HI_DRV_CIPHER_H__

#include "hi_type.h"
#include "hi_debug.h"
#include "drv_rsa.h"
#include "hi_unf_cipher.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define CIPHER_SOFT_CHAN_NUM       8
#define CIPHER_INVALID_CHN        (0xffffffff)
#define CIPHER_MAX_NODE_BUF_SIZE  (0xFFFF0)   //1M-16
#define CIPHER_MAX_RSA_KEY_LEN    (512)

#undef HI_PRINT
#define HI_PRINT                           printf
#define HI_FATAL_CIPHER(fmt...)             
#define HI_ERR_CIPHER(fmt...)               HI_PRINT(fmt)
#define HI_WARN_CIPHER(fmt...)              
#define HI_INFO_CIPHER(fmt...)              
#define HI_DEBUG_CIPHER(fmt...)             

typedef struct
{
    HI_U32  u32src;
    HI_U32  u32dest;
    HI_U32  u32length;
    HI_BOOL bDecrypt;
    HI_U32  u32DataPkg[4];
}HI_DRV_CIPHER_DATA_INFO_S;

typedef struct
{
    HI_DRV_CIPHER_DATA_INFO_S stData2Process;
    HI_U32 u32CallBackArg;
}HI_DRV_CIPHER_TASK_S;

typedef struct
{
    HI_HANDLE hCIHandle;
    HI_UNF_CIPHER_ATTS_S stCipherAtts;
}CIPHER_HANDLE_S;

typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 ScrPhyAddr;
    HI_U32 DestPhyAddr;
    HI_U32 u32DataLength;
}CIPHER_DATA_S;

typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 u32PkgNum;
    HI_UNF_CIPHER_DATA_S* pu8Pkg;
}CIPHER_PKG_S;

typedef struct
{    
    HI_HANDLE CIHandle;    
    HI_UNF_CIPHER_CTRL_S CIpstCtrl;
}CIPHER_Config_CTRL;

typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 u32Key[12];                              /**< Key input, EK||AK||SK for SM1 */ /**< CNcomment:输入密钥, 如果是SM1，依次存放AK||EK||SK*/
    HI_U32 u32OddKey[8];                            /**< Key input, Old Key */            /**< CNcomment:输入密钥, 奇密钥*/
    HI_U32 u32IV[4];                                /**< Initialization vector (IV) */                                                                                    /**< CNcomment:初始向量 */
    HI_BOOL bKeyByCA;                               /**< Encryption using advanced conditional access (CA) or decryption using keys */                                    /**< CNcomment:是否使用高安全CA加密或解密Key */
    HI_UNF_CIPHER_CA_TYPE_E enCaType;               /**< Select keyladder type when using advanced CA */                                                                  /**< CNcomment:使用高安全CA时,选择何种类型的keyladder */
    HI_UNF_CIPHER_ALG_E enAlg;                      /**< Cipher algorithm */                                                                                              /**< CNcomment:加密算法 */
    HI_UNF_CIPHER_BIT_WIDTH_E enBitWidth;           /**< Bit width for encryption or decryption */                                                                        /**< CNcomment:加密或解密的位宽 */
    HI_UNF_CIPHER_WORK_MODE_E enWorkMode;           /**< Operating mode */                                                                                                /**< CNcomment:工作模式 */
    HI_UNF_CIPHER_KEY_LENGTH_E enKeyLen;            /**< Key length */                                                                                                    /**< CNcomment:密钥长度 */
    HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S stChangeFlags; /**< control information exchange choices, we default all woulde be change except they have been in the choices */    /**< CNcomment:控制信息变更选项，选项中没有标识的项默认全部变更 */
    HI_UNF_CIPHER_SM1_ROUND_E enSm1Round;           /**< SM1 round number, should be 8, 10, 12 or 14*/                                                                                                    /**< CNcomment:sm1计算的轮数配置 */
    HI_U32 u32IVLen;                                /**< IV lenght for CCM/GCM, which is an element of {4,6,8,10,12,14,16} for CCM, and is an element of [1-16] for GCM*/  /**< CNcomment: CCM/GCM的IV长度，CCM的取值范围{7, 8, 9, 10, 11, 12, 13}， GCM的取值范围[1-16]*/
    HI_U32 u32TagLen;                               /**< Tag lenght for CCM which is an element of {4,6,8,10,12,14,16}*/          /**< CNcomment: CCM的TAG长度，取值范围{4,6,8,10,12,14,16}*/
    HI_U32 u32ALen;                                 /**< Associated data for CCM and GCM*/                                        /**< CNcomment: CCM/GCM的关联数据长度*/
    HI_U32 u32APhyAddr;                             /**< Physical address of Associated data for CCM and GCM*/                                        /**< CNcomment: CCM/GCM的关联数据长度*/
}CIPHER_CONFIG_CTRL_EX;

typedef struct
{
    HI_U8  u8RefCbcMac[16];
    HI_U32 u32AppLen;
}CIPHER_CBCMAC_DATA_S;

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

HI_S32 HI_DRV_CIPHER_GetTag(CIPHER_TAG_S *pstTag);

typedef enum
{
    HI_CIPHER_HMAC_KEY_FROM_CA  = 0,
    HI_CIPHER_HMAC_KEY_FROM_CPU = 1,
}CIPHER_HMAC_KEY_FROM_E;

typedef struct
{
    HI_UNF_CIPHER_HASH_TYPE_E enShaType;
    HI_U32  u32HardChn;
    CIPHER_HMAC_KEY_FROM_E enHMACKeyFrom;
    HI_U32  u32ShaVal[16];
    HI_U32  u32DataPhy;
    HI_U32  u32DataLen;
}CIPHER_HASH_DATA_S;

HI_S32 HI_DRV_CIPHER_CreateHandle(CIPHER_HANDLE_S *pstCIHandle, HI_VOID *file);
HI_S32 HI_DRV_CIPHER_ConfigChn(HI_U32 softChnId, HI_UNF_CIPHER_CTRL_S *pConfig);
HI_S32 HI_DRV_CIPHER_ConfigChnEx(HI_U32 softChnId, CIPHER_CONFIG_CTRL_EX *pConfig);
HI_S32 HI_DRV_CIPHER_GetHandleConfig(CIPHER_Config_CTRL *pstCipherConfig);
HI_S32 HI_DRV_CIPHER_GetHandleConfigEx(CIPHER_CONFIG_CTRL_EX *pstCipherConfig);
HI_S32 HI_DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn);
HI_S32 HI_DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData);
HI_S32 HI_DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData);
HI_S32 HI_DRV_CIPHER_EncryptMulti(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_DecryptMulti(CIPHER_PKG_S *psPkg);
HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG);
HI_S32 HI_DRV_CIPHER_SoftReset(HI_VOID);

HI_S32 HI_DRV_CIPHER_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData);

HI_S32 HI_DRV_CIPHER_CbcMacAuth(CIPHER_CBCMAC_DATA_S *pstParam);

HI_S32 HI_DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* End of #ifndef __HI_DRV_CIPHER_H__*/

