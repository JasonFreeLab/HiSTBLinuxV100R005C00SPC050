/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sm2.h
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/

#ifndef __DRV_SM2_H__
#define __DRV_SM2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hi_type.h"
#include "hi_drv_cipher.h"
#include "hal_sm2.h"

HI_S32 DRV_SM2_Init(HI_VOID);
HI_VOID DRV_SM2_DeInit(HI_VOID);
HI_S32 DRV_SM2_Sign(SM2_SIGN_DATA_S *pSm2SignData);
HI_S32 DRV_SM2_Verify(SM2_VERIFY_DATA_S *pSm2VerifyData);
HI_S32 DRV_SM2_Encrypt(SM2_ENC_DATA_S *pSm2EncData);
HI_S32 DRV_SM2_Decrypt(SM2_DEC_DATA_S *pSm2DecData);
HI_S32 DRV_SM2_Key(SM2_KEY_DATA_S *pSm2KeyData);

HI_U16 DRV_SM2_CRC16Key(HI_U16 u32Initial , HI_U32 u32Key[SM2_LEN_IN_WROD]);

HI_S32 DRV_SM2_AddMod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD]);

HI_S32 DRV_SM2_SubMod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD]);

HI_S32 DRV_SM2_MulModp(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD],
                      HI_BOOL bIsPrivateKey);

HI_S32 DRV_SM2_MulModn(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32b[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD],
                      HI_BOOL bIsPrivateKey);

HI_S32 DRV_SM2_InvMod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD]);

HI_S32 DRV_SM2_Mod(const HI_U32 u32a[SM2_LEN_IN_WROD],
                      const HI_U32 u32p[SM2_LEN_IN_WROD],
                      HI_U32 u32c[SM2_LEN_IN_WROD]);

HI_S32 DRV_SM2_Mul( const HI_U32 u32a[SM2_LEN_IN_WROD],
                    const HI_U32 u32b[SM2_LEN_IN_WROD],
                    HI_U32 u32c[SM2_LEN_IN_WROD*2]);

HI_S32 DRV_SM2_MulDot( const HI_U32 u32k[SM2_LEN_IN_WROD],
                    const HI_U32 u32Px[SM2_LEN_IN_WROD],
                    const HI_U32 u32Py[SM2_LEN_IN_WROD],
                    HI_U32 u32Rx[SM2_LEN_IN_WROD],
                    HI_U32 u32Ry[SM2_LEN_IN_WROD],
                    HI_BOOL bIsPrivateKey);

HI_S32 DRV_SM2_AddDot( const HI_U32 u32Sx[SM2_LEN_IN_WROD],
                    const HI_U32 u32Sy[SM2_LEN_IN_WROD],
                    const HI_U32 u32Rx[SM2_LEN_IN_WROD],
                    const HI_U32 u32Ry[SM2_LEN_IN_WROD],
                    HI_U32 u32Cx[SM2_LEN_IN_WROD],
                    HI_U32 u32Cy[SM2_LEN_IN_WROD]);

HI_S32 DRV_SM2_CleanRam(SM2_MODEA_S enModea);
HI_U16 DRV_SM2_GetCRC16(HI_VOID);


#ifdef __cplusplus
}
#endif

#endif

