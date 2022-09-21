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

#include "hi_unf_cipher.h"
#include "hi_unf_hdcp.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

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

#define HI_FATAL_CIPHER(fmt...)             HI_FATAL_PRINT(HI_ID_CIPHER, fmt)
#define HI_ERR_CIPHER(fmt...)               HI_ERR_PRINT(HI_ID_CIPHER, fmt)
#define HI_WARN_CIPHER(fmt...)              HI_WARN_PRINT(HI_ID_CIPHER, fmt)
#define HI_INFO_CIPHER(fmt...)              HI_INFO_PRINT(HI_ID_CIPHER, fmt)
#define HI_DEBUG_CIPHER(fmt...)             HI_DBG_PRINT(HI_ID_CIPHER, fmt)

typedef struct
{
    HI_BOOL bIsUseOTPRootKey;
    HI_UNF_HDCP_HDCPKEY_S stHdcpKey;
    HI_U8 u8FlashEncryptedHdcpKey[HDCP_KEY_CHIP_FILE_SIZE];
}CIPHER_HDCP_KEY_TRANSFER_S;

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

typedef enum
{
    CIPHER_HDCP_MODE_NO_HDCP_KEY                = 0x0,
    CIPHER_HDCP_MODE_HDCP_KEY,
    CIPHER_HDCP_MODE_BUTT,
}HI_DRV_CIPHER_HDCP_KEY_MODE_E;

typedef enum
{
    CIPHER_HDCP_KEY_RAM_MODE_READ               = 0x0,
    CIPHER_HDCP_KEY_RAM_MODE_WRITE,
    CIPHER_HDCP_KEY_RAM_MODE_BUTT,
}HI_DRV_CIPHER_HDCP_KEY_RAM_MODE_E;

typedef enum
{
    CIPHER_HDCP_KEY_SELECT_TX               = 0x0,
    CIPHER_HDCP_KEY_SELECT_RX,
    CIPHER_HDCP_KEY_SELECT_BUTT,
}HI_DRV_CIPHER_HDCP_KEY_RX_SELECT_E;

typedef enum
{
    CIPHER_HDCP_KEY_WR_RX_RAM               = 0x0,
    CIPHER_HDCP_KEY_RD_RX_RAM,
    CIPHER_HDCP_KEY_RX_READ_BUTT,
}HI_DRV_CIPHER_HDCP_KEY_RX_READ_E;

typedef enum
{
    CIPHER_HDCP_KEY_TYPE_OTP_ROOT_KEY           = 0x0,
    CIPHER_HDCP_KEY_TYPE_HISI_DEFINED,
    CIPHER_HDCP_KEY_TYPE_HOST_ROOT_KEY,
    CIPHER_HDCP_KEY_TYPE_BUTT,
}HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E;

typedef enum
{
    HI_DRV_HDCPKEY_TX0,
    HI_DRV_HDCPKEY_TX1,
    HI_DRV_HDCPKEY_RX0,
    HI_DRV_HDCPKEY_RX1,
    HI_DRV_HDCPKEY_RX0V22,
    HI_DRV_HDCPKEY_BUTT
}HI_DRV_HDCPKEY_TYPE_E;

typedef enum
{
    HI_DRV_HDCP_VERIOSN_1x = 0x0,
    HI_DRV_HDCP_VERIOSN_2x,

    HI_DRV_HDCP_VERSON_BUTT
}HI_DRV_HDCP_VERSION_E;

typedef struct
{
    HI_U8 u8Key[HDCP_KEY_CHIP_FILE_SIZE];   // 332bytes for HDCP1.X, unknown for other.
    HI_U32 u32KeyLen;
    HI_DRV_HDCP_VERSION_E enHDCPVersion;
    HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType;
}HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S;

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
    HI_U8  *pu8Input;
    HI_U8  *pu8Output;
    HI_U32  u32DataLen;
    HI_U8  *pu8N;
    HI_U8  *pu8K;
    HI_U16 u16NLen;
    HI_U16 u16KLen;
}CIPHER_RSA_DATA_S;

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

typedef struct
{
    HI_U32 u32e[SM2_LEN_IN_WROD];
    HI_U32 u32d[SM2_LEN_IN_WROD];
    HI_U32 u32r[SM2_LEN_IN_WROD];
    HI_U32 u32s[SM2_LEN_IN_WROD];
}SM2_SIGN_DATA_S;

typedef struct
{
    HI_U32 u32e[SM2_LEN_IN_WROD];
    HI_U32 u32Px[SM2_LEN_IN_WROD];
    HI_U32 u32Py[SM2_LEN_IN_WROD];
    HI_U32 u32r[SM2_LEN_IN_WROD];
    HI_U32 u32s[SM2_LEN_IN_WROD];
}SM2_VERIFY_DATA_S;

typedef struct
{
    HI_U32 u32Px[SM2_LEN_IN_WROD];
    HI_U32 u32Py[SM2_LEN_IN_WROD];
    HI_U32 u32C1x[SM2_LEN_IN_WROD];
    HI_U32 u32C1y[SM2_LEN_IN_WROD];
    HI_U32 u32X2[SM2_LEN_IN_WROD];
    HI_U32 u32Y2[SM2_LEN_IN_WROD];
}SM2_ENC_DATA_S;

typedef struct
{
    HI_U32 u32d[SM2_LEN_IN_WROD];
    HI_U32 u32C1x[SM2_LEN_IN_WROD];
    HI_U32 u32C1y[SM2_LEN_IN_WROD];
    HI_U32 u32X2[SM2_LEN_IN_WROD];
    HI_U32 u32Y2[SM2_LEN_IN_WROD];
}SM2_DEC_DATA_S;

typedef struct
{
    HI_U32 u32d[SM2_LEN_IN_WROD];
    HI_U32 u32Px[SM2_LEN_IN_WROD];
    HI_U32 u32Py[SM2_LEN_IN_WROD];
}SM2_KEY_DATA_S;


typedef struct  hiCIPHER_CENC_DECRYPT_S
{
    HI_HANDLE hCipher;
    HI_U8 u8Key[32];
    HI_U8 u8IV[16];
    HI_U32 u32NonSecInputPhyAddr;
    HI_U32 u32SecOutputPhyAddr;
    HI_U32 u32ByteLength;
    HI_U32 u32FirstEncryptOffset;
    HI_U32 u32SubsampleNum;
    HI_UNF_CIPHER_SUBSAMPLE_S *pstSubSample;
}CIPHER_CENC_DECRYPT_S;

HI_S32 HI_DRV_CIPHER_GetTag(CIPHER_TAG_S *pstTag);

HI_S32 HI_DRV_CIPHER_CPU_Encrypt(HI_U8 *pu8Input,
                              HI_U32 u32InputLen,
                              HI_U8 *pu8Output,
                              HI_DRV_CIPHER_HDCP_KEY_MODE_E enHdcpEnMode,
                              HI_DRV_CIPHER_HDCP_ROOT_KEY_TYPE_E enRootKeyType,
                              HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType,
                              CIPHER_Config_CTRL *pConfig,
                              HI_BOOL bIsDecrypt);

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
static const HI_U32 s_u32P[SM2_LEN_IN_WROD] =  {0x04000000, 0x02000000, 0x01000000, 0x01000000, 0x02000000, 0xFFFFFFFF, 0x02000000, 0x03000000};
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
static const HI_U32 s_u32P[SM2_LEN_IN_WROD] =  {0x2952E50A, 0x6AD93C28, 0xDA874DEE, 0x6CC6D890, 0xA82D37EB, 0x36C6C93F, 0x469C573D, 0xF218DEF6};
static const HI_U32 s_u32wp[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0C38A0A2, 0x1577F750};
static const HI_U32 s_u32N[SM2_LEN_IN_WROD] =  {0x3AD33C62, 0x7FF548F6, 0xDB0BC0BC, 0xC3DCD0E3, 0x2AF545D5, 0x840BDC3A, 0x942B21CE, 0x53D02711};
static const HI_U32 s_u32wn[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3E06E30D, 0xF94BF562};
static const HI_U32 s_u321[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01000000};
static const HI_U32 s_u320[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
static const HI_U32 s_u32ma[SM2_LEN_IN_WROD] = {0xDC7F6B83, 0xAFCB99B2, 0x8F526642, 0x62D2CE10, 0xF7FA815B, 0x8B1ABE9B, 0x7E404156, 0x975E23D7};
static const HI_U32 s_u32mb[SM2_LEN_IN_WROD] = {0x2C57396F, 0x1E3A0D79, 0xE6E38AC3, 0x7B8C4C77, 0x887656E0, 0x4F557657, 0x206FAEF2, 0x925DCBFD};
static const HI_U32 s_u32m1[SM2_LEN_IN_WROD] = {0x6129BD7A, 0xE7B0FBB3, 0xCADB4617, 0x22089040, 0x9CDF88D6, 0x729D7AFB, 0x18B118A5, 0x4986D13C};
#endif


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

#ifdef CONFIG_COMPAT
typedef struct
{
    HI_HANDLE CIHandle;
    HI_U32 u32PkgNum;
    HI_U32 u32PkgVia;
}CIPHER_COMPAT_PKG_S;

typedef struct
{
    HI_U32  u32InputVia;
    HI_U32  u328OutputVia;
    HI_U32  u32DataLen;
    HI_U32  u328NVia;
    HI_U32  u328KVia;
    HI_U16  u16NLen;
    HI_U16  u16KLen;
}CIPHER_COMPAT_RSA_DATA_S;

typedef struct  hiCIPHER_COMPAT_CENC_DECRYPT_S
{
    HI_HANDLE hCipher;
    HI_U8 u8Key[32];
    HI_U8 u8IV[16];
    HI_U32 u32NonSecInputPhyAddr;
    HI_U32 u32SecOutputPhyAddr;
    HI_U32 u32ByteLength;
    HI_U32 u32FirstEncryptOffset;
    HI_U32 u32SubsampleNum;
    HI_U32 u32SubSampleVia;
}CIPHER_COMPAT_CENC_DECRYPT_S;
#endif

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
HI_S32 HI_DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey);
HI_S32 HI_DRV_CIPHER_CencDecrypt(CIPHER_CENC_DECRYPT_S *pstCencDecrypt);
HI_S32 HI_DRV_CIPHER_CalcHashInit(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_CalcHashUpdate(CIPHER_HASH_DATA_S *pCipherHashData);
HI_S32 HI_DRV_CIPHER_CalcHashFinal(CIPHER_HASH_DATA_S *pCipherHashData);

HI_S32 HI_DRV_CIPHER_EncryptHDCPKey(CIPHER_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer);
HI_S32 HI_DRV_CIPHER_CbcMacAuth(CIPHER_CBCMAC_DATA_S *pstParam);

HI_S32 HI_DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData);

HI_VOID HI_DRV_CIPHER_Suspend(HI_VOID);
HI_S32 HI_DRV_CIPHER_Resume(HI_VOID);
HI_VOID HI_DRV_CIPHER_SetHdmiReadClk(HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType);
HI_S32 HI_DRV_CIPHER_SetIV(HI_HANDLE hCIHandle,  HI_U8 *pu8IV, HI_U32 u32IVLen);
HI_S32 DRV_CIPHER_EncryptHDCPKey(CIPHER_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer);
HI_S32 DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* End of #ifndef __HI_DRV_CIPHER_H__*/

