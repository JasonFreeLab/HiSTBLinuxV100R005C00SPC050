/******************************************************************************

 Copyright @ Hisilicon Technologies Co., Ltd. 1998-2015. All rights reserved.

 ******************************************************************************
  File Name     : vpss_cfgreg.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/1/25
  Last Modified :
  Description   : vpss_cfgreg.c header file
  Function List :
  History       :
  1.Date        : 2016/1/25
    Author      : sdk
    Modification: Created file

******************************************************************************/
#ifndef __VPSS_CFGREG_H__
#define __VPSS_CFGREG_H__
#include "hi_type.h"
#include "hi_reg_common.h"

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/
#define VPSS_RegRead(addr) VPSS_REG_RegRead(addr)
#define VPSS_RegWrite(addr, value) VPSS_REG_RegWrite((addr), (value))



/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern HI_S32 VPSS_DRV_SetClockEn(HI_BOOL bClkEn);
extern HI_S32 VPSS_DRV_SetClockEn(HI_BOOL bClkEn);
extern HI_S32 VPSS_DRV_SetTimeOut(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Data);
extern HI_U32 VPSS_REG_RegRead(volatile HI_U32 *a);
extern HI_S32 VPSS_REG_RegWrite(volatile HI_U32 *a, HI_U32 b);
extern HI_S32 VPSS_REG_ResetAppReg(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_REG_S *pstPqReg);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

