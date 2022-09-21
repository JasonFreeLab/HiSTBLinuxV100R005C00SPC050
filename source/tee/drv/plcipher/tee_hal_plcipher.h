/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_hal_plcipher.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __TEE_HAL_PLCIPHER_H__
#define __TEE_HAL_PLCIPHER_H__

#include "hi_tee_plcipher.h"

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/
/******* proc function begin ********/

HI_VOID HAL_PLCipher_HardWareInit(HI_VOID);
HI_VOID HAL_PLCipher_HardWareDeInit(HI_VOID);
HI_VOID HAL_PLCipher_EnMMU(HI_U32 u32MmuTlbBase);
HI_VOID HAL_PLCipher_DisMMU(HI_VOID);
HI_VOID HAL_PLCipher_EnAllInt(HI_VOID);
HI_VOID HAL_PLCipher_DisAllInt(HI_VOID);
HI_VOID HAL_PLCipher_ClrSecChn(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_SetSecChn(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_EnDmaChn(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_DisDmaChn(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_SetDmaChanBase(HI_U32 u32ChnId,HI_U32 u32Addr);
HI_VOID HAL_PLCipher_SetDmaChanDepth(HI_U32 u32ChnId,HI_U32 u32Depth);
HI_VOID HAL_PLCipher_DmaChanAddDesc(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_ResetDmaChanDescPW(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_SetDmaObufAddr(HI_U32 u32ChnId,HI_U32 u32Addr);
HI_VOID HAL_PLCipher_EnDmaObuf(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_DisDmaObuf(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_SetDmaObufLen(HI_U32 u32ChnId,HI_U32 u32Len);
HI_VOID HAL_PLCipher_ResetDmaObufPR(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_GetDmaObufPW(HI_U32 u32ChnId,HI_U32* pu32ObufPw);
HI_VOID HAL_PLCipher_GetDmaObufPR(HI_U32 u32ChnId,HI_U32* pu32ObufPw);
HI_VOID HAL_PLCipher_GetDMAGlBStatus(HI_U32 *GlBStatus);
HI_VOID HAL_PLCipher_GetDMAObufIntStatus(HI_U32 *OufIntStatus );
HI_VOID HAL_PLCipher_ClrDMAObufIntStatus(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_CfgDMACoal(HI_U32 u32Packets);
HI_VOID HAL_PLCipher_ClrDMAObufMMU(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_ClrDMAChanMMU(HI_U32 u32ChnId);
HI_VOID HAL_PLCipher_CfgChanPIDFilter(HI_U32 u32ChnId,HI_BOOL bFilterEn);
HI_VOID HAL_PLCipher_SetChnPID(HI_U32 u32ChnId,HI_U8 PIDNo, HI_U16 PID);
HI_VOID HAL_PLCipher_SetCWAttr(HI_U32 Chan, HI_TEE_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, HI_TEE_PLCIPHER_ALG_E enAlg, HI_BOOL bIsCWOrIV );
HI_VOID HAL_PLCipher_GetCWAttr(HI_U32 Chan, HI_TEE_PLCIPHER_KEY_EVENODD_E* penKeyEvenOdd, HI_TEE_PLCIPHER_ALG_E* penAlg );
HI_VOID HAL_PLCipher_SetCWWord(HI_U32 CW, HI_U32 WordNo);
//HI_S32 HAL_PLCIPHER_ProcGetStatus(PLCIPHER_CHN_STATUS_S *pstCipherStatus);
/******* proc function end ********/

#ifdef __cplusplus
}
#endif
#endif /* __HAL_PLCIPHER_H__ */


