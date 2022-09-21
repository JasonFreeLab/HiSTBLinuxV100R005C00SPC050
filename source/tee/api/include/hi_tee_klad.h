/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_tee_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_TEE_KLAD_H__
#define __HI_TEE_KLAD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef unsigned char            TEE_KLAD_BYTE;
typedef unsigned short           TEE_KLAD_USHORT16;
typedef unsigned long            TEE_KLAD_ULONG32;
typedef unsigned char            TEE_KLAD_BOOLEAN;

#define TEE_KLAD_MAX_KEY_DESC   16
#define TEE_KLAD_MAX_DEMUX      7
#define TEE_KLAD_MAX_CHANNEL    96

typedef enum
{
    TEE_KLAD_OK,
    TEE_KLAD_FAIL,
    TEE_KLAD_UNMATCH_CHAN
}TEE_KLAD_STATUS;

typedef enum {
    CLEAR_CW_DSCR_TAG               = 0x01,
    ENCRYPTED_CW_DSCR_TAG           = 0x02,
    ENCRYPTED_KEY_DSCR_TAG          = 0x03,
    ENCRYPTION_SCHEME_DSCR_TAG      = 0x04,
    VENDOR_ID_DSCR_TAG              = 0x05,
    PROCESSING_MODE_DSCR_TAG        = 0x06,
    DESCRAMBLING_ALGORITHM_DSCR_TAG = 0x07
}TEE_KLAD_TAG;

TEE_KLAD_STATUS TEE_KLAD_Init(void);

TEE_KLAD_STATUS TEE_KLAD_DeInit(void);

TEE_KLAD_STATUS TEE_KLAD_GetChipId
(
    TEE_KLAD_BYTE *chipId
);

TEE_KLAD_STATUS TEE_KLAD_GetResponseToChallenge
(
    TEE_KLAD_BYTE *nonce,
    TEE_KLAD_BYTE nonceLength,
    int           keyDescriptorsLength,
    TEE_KLAD_BYTE *keyDescriptors,
    TEE_KLAD_BYTE *response ,
    TEE_KLAD_BYTE *responseLength
);

/* streamPathLength should be 1, 2, 4 */
TEE_KLAD_STATUS TEE_KLAD_SetDescrambler
(
    int               streamPathLength,
    TEE_KLAD_BYTE     *streamPath,
    int               numberOfStreamPids,
    TEE_KLAD_USHORT16 *streamPids,
    int               OddkeyDescriptorsLength,
    TEE_KLAD_BYTE     *OddkeyDescriptor,
    int               EvenkeyDescriptorsLength,
    TEE_KLAD_BYTE     *EvenkeyDescriptor
);

TEE_KLAD_STATUS TEE_KLAD_StopDescrambler
(
    int               streamPathLength,
    TEE_KLAD_BYTE     *streamPath,
    int               numberOfStreamPids,
    TEE_KLAD_USHORT16 *streamPids
);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_TEE_KLAD_H__ */
