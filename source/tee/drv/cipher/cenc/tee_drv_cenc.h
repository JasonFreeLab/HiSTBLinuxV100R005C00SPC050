/******************************************************************************
 *
 * Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_cenc.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-03-25
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_CENC_H__
#define __TEE_CENC_H__

#include "hi_tee_drv_cipher.h"

HI_S32 Cipher_CencDecrypt(CIPHER_CENC_DECRYPT_S *pstCencDecrypt);

HI_S32 cenc_decrypt(HI_HANDLE hCipher,
                    HI_U8 u8Key[32],
                    HI_U8 u8IV[16],
                    HI_U32 u32NonSecInputPhyAddr,
                    HI_U32 u32SecOutputPhyAddr,
                    HI_U32 u32ByteLength,
                    HI_U32 u32FirstEncryptOffset,
                    HI_TEE_CIPHER_SUBSAMPLE_S *pstSubSample,
                    HI_U32 u32SubsampleNum);

#endif /* __DRV_CIPHER_INTF_H__ */
