/******************************************************************************

          Copyright (C), 2001-2017, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : taload_osal.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2017-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2017-07-29  sdk        N/A               Create this file.
 ******************************************************************************/

#ifndef __TALOAD_OSAL_H__
#define __TALOAD_OSAL_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup      TALOAD_OSAL */
/** @{ */  /** <!-- [TALOAD_OSAL] */

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup      TALOAD_OSAL */
/** @{ */  /** <!-- [TALOAD_OSAL] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @} */  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup      TALOAD_OSAL */
/** @{ */  /** <!-- [TALOAD_OSAL] */

HI_VOID* TALOAD_MemCpy(HI_VOID* pDest, const HI_VOID* pSrc, HI_U32 u32Count);

HI_VOID* TALOAD_MemSet(HI_VOID* pToSet, HI_S32 s32SetChar, HI_U32 u32Count);

HI_S32 TALOAD_MemCmp(HI_VOID* pBuf1, HI_VOID* pBuf2, HI_U32 u32Count);

HI_S32  TALOAD_StrNCmp(HI_CHAR* pcStr1, HI_CHAR* pcStr2, HI_U32 u32Count);

HI_U32 TALOAD_StrLen(HI_CHAR* pcStr);

/** @} */  /** <!-- ==== API Declaration End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif /*__TALOAD_OSAL_H__*/
