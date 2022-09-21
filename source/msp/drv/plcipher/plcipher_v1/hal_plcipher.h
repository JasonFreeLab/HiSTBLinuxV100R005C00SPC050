/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_plcipher.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :
******************************************************************************/

#ifndef __HAL_PLCIPHER_H__
#define __HAL_PLCIPHER_H__

/* add include here */
//#include <asm/arch/hardware.h> /* for IO_ADDRESS */
//#include <./arch/arm/mach-x5hd/include/mach/hardware.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/clk.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/io.h>

//#include <mach/hardware.h>

#include "drv_plcipher_ext.h"
#include "drv_plcipher_reg.h"
#include "drv_plcipher_ioctl.h"
//#include "drv_plcipher_define.h"
#include "hi_unf_payloadcipher.h"

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/
#define  PLCIPHER_IRQ_NUMBER            (107 + 32)
/*************************** Structure Definition ****************************/ 
/******* proc function begin ********/
HI_VOID HAL_PLCIPHER_GetDescReadPtr(HI_U32* pInDescReadPrt,HI_U32* pOutDescReadPrt);
HI_VOID HAL_PLCIPHER_GetDescWritePtr(HI_U32* pInDescWritePrt,HI_U32* pOutDescWritePrt);
HI_VOID HAL_PLCIPHER_GetInDescInvalidNum(HI_U32* pInDescvalidNum );
HI_VOID HAL_PLCIPHER_GetOutDescInvalidNum(HI_U32* pOutDescvalidNum );
HI_VOID HAL_PLCipher_HardWareInit(HI_VOID);
HI_VOID HAL_PLCipher_HardWareDeInit(HI_VOID);
HI_VOID HAL_PLCipher_EnableGloableInt(HI_VOID);
HI_VOID HAL_PLCipher_DisableGloableInt(HI_VOID);
HI_VOID HAL_PLCipher_EnableAllInt(HI_VOID);
HI_VOID HAL_PLCipher_DisableAllInt(HI_VOID);
HI_VOID HAL_PLCipher_GetIntState(HI_U32* pu32IntState);
HI_VOID HAL_PLCipher_ClrIntState(HI_VOID);
HI_VOID HAL_PLCipher_EnableOutDescDataDoneInt(HI_VOID);
HI_VOID HAL_PLCipher_DisableOutDescDataDoneInt(HI_VOID);
HI_VOID HAL_PLCipher_SetKeySecureAttr(HI_BOOL bKeyOnlySecure);
HI_VOID HAL_PLCipher_ResetDescQueue(HI_VOID);
HI_VOID HAL_PLCipher_ConfigDescQueue(HI_U32 InQStartAddr, HI_U32 InQSize,HI_U32 OutQStartAddr, HI_U32 OutQSize );
HI_VOID HAL_PLCipher_InDescAdd(HI_VOID);
HI_VOID HAL_PLCipher_OutDescAdd(HI_VOID);
HI_VOID HAL_PLCipher_ConfigCWSetAllAttr(HI_BOOL bOdd,HI_U32 Chan,HI_U32 Algo,HI_BOOL ConfigAsCW);
HI_VOID HAL_PLCipher_ConfigCWOddEven(HI_BOOL bOdd);
HI_VOID HAL_PLCipher_ConfigCWAlgo(HI_U32 Algo);
HI_VOID HAL_PLCipher_ConfigCWIV(HI_BOOL ConfigAsCW);
HI_VOID HAL_PLCipher_ConfigCWChan(HI_U32 Chan);
HI_VOID HAL_PLCipher_SetCWAttr(HI_U32 Chan, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, HI_UNF_PLCIPHER_ALG_E enAlg, HI_BOOL bIsCWOrIV );
HI_VOID HAL_PLCipher_GetCWAttr(HI_U32 Chan, HI_UNF_PLCIPHER_KEY_EVENODD_E* penKeyEvenOdd, HI_UNF_PLCIPHER_ALG_E* penAlg );
HI_VOID HAL_PLCipher_SetCWWord(HI_U32 CW, HI_U32 WordNo);
HI_U32 HAL_PLCipher_GetTimeOutIntStatus(HI_VOID);
HI_U32 HAL_PLCipher_GetInerTimeOutIntStatus(HI_VOID);
HI_U32 HAL_PLCipher_GetInDescEmptyIntStatus(HI_VOID);
HI_U32 HAL_PLCipher_GetInDescMoveIntStatus(HI_VOID);
HI_U32 HAL_PLCipher_GetOutDescEmptyIntStatus(HI_VOID);
HI_U32 HAL_PLCipher_GetOutDescDataDoneIntStatus(HI_VOID);
HI_VOID HAL_PLCipher_ClrOutDescDataDoneIntStatus(HI_VOID);
HI_VOID HAL_PLCipher_ClrGlobalIntStatus(HI_VOID);
//HI_S32 HAL_PLCIPHER_ProcGetStatus(PLCIPHER_CHN_STATUS_S *pstCipherStatus);
/******* proc function end ********/

#ifdef __cplusplus
}
#endif
#endif /* __HAL_PLCIPHER_H__ */


