/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_tee_advca.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :

******************************************************************************/
#ifndef __DRV_TEE_ADVCA_H__
#define __DRV_TEE_ADVCA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_unf_advca.h"


#define KLAD_MAX_KEY_LEN     (16)

/**Target engine of key ladder*/
typedef enum
{
    KLAD_TARGET_ENGINE_PAYLOAD_CSA2             = 0x0000,   /**<Demux PAYLOAD CSA2 */
    KLAD_TARGET_ENGINE_PAYLOAD_CSA3             = 0x0010,   /**<Demux PAYLOAD CSA3 */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_CBC_IDSA     = 0x0020,   /**<Demux PAYLOAD AES  IPTV Mode */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_ECB          = 0x0021,   /**<Demux PAYLOAD AES  ECB Mode */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_CBC_CI       = 0x0022,   /**<Demux PAYLOAD AES  CIPLUS */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_CLRSTART_ECB = 0x0024,   /**<Demux PAYLOAD AES  CLRSTART ECB */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_CLRSTART_CBC = 0x0025,   /**<Demux PAYLOAD AES  CLRSTART CBC */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_CTR          = 0x0026,   /**<Demux PAYLOAD AES  CTR */
    KLAD_TARGET_ENGINE_PAYLOAD_DES_IPTV         = 0x0030,   /**<Demux PAYLOAD DES  CIPLUS */
    KLAD_TARGET_ENGINE_PAYLOAD_DES_CIPLUS       = 0x0032,   /**<Demux PAYLOAD DES  CIPLUS */
    KLAD_TARGET_ENGINE_PAYLOAD_DES_CBC          = 0x0033,   /**<Demux PAYLOAD DES  CBC */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_NOVEL        = 0x0040,   /**<Demux PAYLOAD AES  NOVEL */
    KLAD_TARGET_ENGINE_PAYLOAD_SMS4_NOVEL       = 0x0041,   /**<Demux PAYLOAD SMS4 NOVEL */
    KLAD_TARGET_ENGINE_PAYLOAD_SMS4_IPTV        = 0x0050,   /**<Demux PAYLOAD SMS4 IPTV */
    KLAD_TARGET_ENGINE_PAYLOAD_SMS4_ECB         = 0x0051,   /**<Demux PAYLOAD SMS4 ECB */
    KLAD_TARGET_ENGINE_PAYLOAD_SMS4_CBC         = 0x0053,   /**<Demux PAYLOAD SMS4 CBC */
    KLAD_TARGET_ENGINE_PAYLOAD_AES_CBC          = 0x0063,   /**<Demux PAYLOAD AES  CBC */
    KLAD_TARGET_ENGINE_PAYLOAD_TDES_IPTV        = 0x0070,   /**<Demux PAYLOAD TDES IPTV */
    KLAD_TARGET_ENGINE_PAYLOAD_TDES_ECB         = 0x0071,   /**<Demux PAYLOAD TDES ECB */
    KLAD_TARGET_ENGINE_PAYLOAD_TDES_CBC         = 0x0073,   /**<Demux PAYLOAD TDES CBC */
    KLAD_TARGET_ENGINE_RAW_AES_CBC              = 0x4020,   /**<Cipher AES CBC */
    KLAD_TARGET_ENGINE_RAW_AES_ECB              = 0x4021,   /**<Cipher AES ECB */
    KLAD_TARGET_ENGINE_RAW_AES_CBC_PIFF         = 0x4022,   /**<Cipher AES CBC PIFF */
    KLAD_TARGET_ENGINE_RAW_AES_CBC_APPLE        = 0x4023,   /**<Cipher AES CBC APPLE */
    KLAD_TARGET_ENGINE_RAW_AES_CTR              = 0x4024,   /**<Cipher AES CTR */
    KLAD_TARGET_ENGINE_RAW_TDES_CBC             = 0x4040,   /**<Cipher AES CBC */
    KLAD_TARGET_ENGINE_RAW_TDES_ECB             = 0x4041,   /**<Cipher AES ECB */
    KLAD_TARGET_ENGINE_FIXED,                               /**<Can't config by software */
    KLAD_TARGET_ENGINE_BUTT
} KLAD_TARGET_ENGINE_E;

/**Encryption algorithm of key ladder*/
typedef enum
{
    KLAD_ALG_TYPE_TDES = 0,      /**<Encryption algorithm : TDES*/
    KLAD_ALG_TYPE_AES,           /**<Encryption algorithm : AES*/
    KLAD_ALG_TYPE_BUTT
} KLAD_ALG_TYPE_E;

/**Level of key ladder*/
typedef enum
{
    KLAD_LEVEL1 = 0,
    KLAD_LEVEL2,
    KLAD_LEVEL3,
    KLAD_LEVEL4,
    KLAD_LEVEL5,
    KLAD_LEVEL6,
    KLAD_LEVEL_BUTT
} KLAD_LEVEL_E;

/**Session key*/
typedef struct
{
    KLAD_LEVEL_E enLevel;
    HI_U8 au8Key[KLAD_MAX_KEY_LEN];
} KLAD_SESSION_KEY_S;

/**Content key*/
typedef struct
{
    HI_BOOL bOdd;
    HI_U8 au8Key[KLAD_MAX_KEY_LEN];
} KLAD_CONTENT_KEY_S;

typedef struct
{
    HI_BOOL bOdd;
    HI_U32 u32IVLength;
    HI_U8 au8IV[KLAD_MAX_KEY_LEN];
} KLAD_CONTENT_IV_S;

typedef struct
{
    KLAD_ALG_TYPE_E enAlg;
    KLAD_TARGET_ENGINE_E enEngine;
} KLAD_ATTR_S;

typedef struct
{
    HI_U32 klad_type;
    HI_U32 handle;
    KLAD_ATTR_S attr;
    HI_U32 session_level;
    KLAD_SESSION_KEY_S session_key[KLAD_LEVEL_BUTT];
    KLAD_CONTENT_KEY_S content_key;
    HI_BOOL iv_flag;
    KLAD_CONTENT_IV_S content_iv;
}klad_session_para_s;


HI_S32 DEV_ADVCA_TeecSetKey(klad_session_para_s * parameter);
HI_S32 DEV_ADVCA_InitTeec(HI_VOID);
HI_S32 DEV_ADVCA_DeInitTeec(HI_VOID);
#ifdef __cplusplus
#if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_TEE_ADVCA_H__ */

