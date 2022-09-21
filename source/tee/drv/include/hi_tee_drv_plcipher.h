/***********************************************************************************
*              Copyright 2004 - 2017, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  hi_tee_drv_plcipher.h
* Description:  Define implement of payloadcipher function.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20170228    NA                 NULL      Create this file.
***********************************************************************************/


#ifndef __HI_TEE_DRV_PLCIPHER_H__
#define __HI_TEE_DRV_PLCIPHER_H__

#include "hi_type.h"
#include "hi_tee_plcipher.h"


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define PLCIPHER_KEY_SIZE    16

typedef struct hiPLCIPHER_SetKey
{
    HI_HANDLE CIHandle;
    HI_BOOL bIsCWOrIV;
    HI_TEE_PLCIPHER_KEY_EVENODD_E enEvenOdd;
    HI_U8   Key[PLCIPHER_KEY_SIZE];
}PLCIPHER_SetKey;

typedef struct  hiPLCIPHER_DATA_S
{
    HI_HANDLE CIHandle;
    HI_U32 ScrPhyAddr;
    HI_U32 DestPhyAddr;
    HI_U32 u32DataLength;
}PLCIPHER_DATA_S;

typedef struct  hiPLCIPHER_HANDLE_S
{
    HI_HANDLE Handle;
    HI_TEE_PLCIPHER_ATTR_S stPlCipherAtts;
}PLCIPHER_CONFIG_S;

HI_S32  HI_DRV_PLCIPHER_Init(HI_VOID);
HI_S32  HI_DRV_PLCIPHER_DeInit(HI_VOID);
HI_S32  HI_DRV_PLCIPHER_CreateHandle(HI_HANDLE* phPLCipher);
HI_S32  HI_DRV_PLCIPHER_DestroyHandle(HI_HANDLE hPLCipher);
HI_S32  HI_DRV_PLCIPHER_GetAttr(HI_HANDLE hPLCipher, HI_TEE_PLCIPHER_ATTR_S* pstAttr);
HI_S32  HI_DRV_PLCIPHER_SetAttr(HI_HANDLE hPLCipher, HI_TEE_PLCIPHER_ATTR_S* pstAttr);
HI_S32  HI_DRV_PLCIPHER_SetKeyIV(PLCIPHER_SetKey* pstKey);
HI_S32  HI_DRV_PLCIPHER_Encrypt(PLCIPHER_DATA_S *pstCIData);
HI_S32  HI_DRV_PLCIPHER_Decrypt(PLCIPHER_DATA_S *pstCIData);

/* extern for keyaddder */
HI_S32 HI_DRV_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_TEE_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_DRV_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_TEE_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8IV, HI_U32 u32IVLen);

/* suspend and resume */
HI_S32  HI_DRV_PLCIPHER_Suspend(HI_VOID);
HI_S32  HI_DRV_PLCIPHER_Resume(HI_VOID);

/* ModInit and ModExit */
HI_S32 PLCIPHER_DRV_ModInit(HI_VOID);
HI_VOID PLCIPHER_DRV_ModExit(HI_VOID);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* End of #ifndef __HI_TEE_DRV_PLCIPHER_H__*/

