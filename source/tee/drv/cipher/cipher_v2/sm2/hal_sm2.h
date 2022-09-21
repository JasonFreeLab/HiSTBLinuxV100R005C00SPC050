/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_sm2.h
  Version       : Initial Draft
  Author        :
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
******************************************************************************/

#ifndef __HAL_SM2_H__
#define __HAL_SM2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hi_type.h"
#include "hi_drv_cipher.h"

#define CPU_TO_BE16(v) (((v)<< 8) | ((v)>>8))
#define CPU_TO_BE32(v) (((v)>>24) | (((v)>>8)&0xff00) | (((v)<<8)&0xff0000) | ((v)<<24))

typedef enum hiSM2_MODEA_S
{
    SM2_MODEA_CLR_MRAM = 0x01,
    SM2_MODEA_CLR_KRAM = 0x02,
    SM2_MODEA_CLR_NRAM = 0x04,
    SM2_MODEA_CLR_RRAM = 0x08,
    SM2_MODEA_CLR_PKA  = 0x10,
    SM2_MODEA_CLR_ALLRAM = 0x1F,
    SM2_MODEA_SIZE = 0xFF,
}SM2_MODEA_S;

typedef enum hiSM2_RAM_TYPE_S
{
    SM2_RAM_TYPE_MRAM = 0,
    SM2_RAM_TYPE_NRAM,
    SM2_RAM_TYPE_KRAM,
    SM2_RAM_TYPE_RRAM,
}SM2_RAM_TYPE_S;

typedef enum hiSM2_OPCODE_S
{
    SM2_OPCODE_ADD_MOD = 3,
    SM2_OPCODE_SUB_MOD = 5,
    SM2_OPCODE_MUL_MOD = 6,
    SM2_OPCODE_INV_MOD = 7,
    SM2_OPCODE_MOD = 8,
    SM2_OPCODE_MUL = 9,
    SM2_OPCODE_MUL_DOT = 12,
    SM2_OPCODE_ADD_DOT = 13,
    SM2_OPCODE_CLR_RAM = 15,
}SM2_OPCODE_S;

HI_S32 HAL_SM2_WaitReady(HI_BOOL bIsFast);
HI_VOID HAL_SM2_SetMode(SM2_MODEA_S enModea, SM2_OPCODE_S enOpcode);
HI_VOID HAL_SM2_Start(HI_VOID);
HI_U32 HAL_SM2_GetResultFlag(HI_VOID);
HI_U32 HAL_SM2_GetFailureFlag(HI_VOID);
HI_U16 HAL_SM2_GetCrc16(HI_VOID);
HI_VOID HAL_SM2_ClrInt(HI_VOID);
HI_U32 HAL_SM2_GetRawInt(HI_VOID);
HI_U32 HAL_SM2_GetInt(HI_VOID);
HI_U32 HAL_SM2_GetIntEn(HI_VOID);
HI_U32 HAL_SM2_GetBusy(HI_VOID);
HI_VOID HAL_SM2_EnableInt(HI_VOID);
HI_VOID HAL_SM2_DisableInt(HI_VOID);
HI_VOID HAL_SM2_SetRAM(SM2_RAM_TYPE_S enRamType, HI_U32 u32Section, const HI_U32 u32Ram[SM2_LEN_IN_WROD], HI_BOOL bIsExpandZero);
HI_VOID HAL_SM2_GetRAM(SM2_RAM_TYPE_S enRamType, HI_U32 u32Section, HI_U32 u32Ram[SM2_LEN_IN_WROD]);
HI_VOID HAL_SM2_SetWP(HI_U32 u32WPH, HI_U32 u32WPL);
HI_VOID HAL_SM2_SetRngOption(HI_U32 u32Option);
HI_VOID HAL_SM2_OTPKeyEnable(HI_BOOL bIsEnable);
HI_VOID HAL_SM2_SetKeyRandom(HI_U32 u32Random[2]);
HI_VOID HAL_SM2_SetKeyCrc(HI_U16 u16Crc);
HI_VOID HAL_SM2_PrivateKeyEnable(HI_BOOL bIsEnable);
HI_S32 HAL_SM2_SoftReset(HI_VOID);
HI_S32 HAL_SM2_Enable(HI_VOID);
HI_S32 HAL_SM2_Disable(HI_VOID);

#ifdef __cplusplus
}
#endif

#endif /* sha2.h */
