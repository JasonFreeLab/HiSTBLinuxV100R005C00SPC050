
/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : hi_tee_log.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2017-07-29
 Last Modified by: Linux Integration Group
 Description     : All functions and macros, not begin with HI_, prohibited to use
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2017-07-29  STB_Linux  N/A               Create this file.
 ******************************************************************************/

#ifndef __HI_TEE_LOG_H__
#define __HI_TEE_LOG_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"
#include "hi_tee_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     HI_TEE_LOG */
/** @{ */  /** <!-- [HI_TEE_LOG] */

/****** Macro switch definition ***********/

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     HI_TEE_LOG */
/** @{ */  /** <!-- [HI_TEE_LOG] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     HI_TEE_LOG */
/** @{ */  /** <!-- [HI_TEE_LOG] */

extern HI_S32 HI_TEE_Set_LogLevel(HI_MODULE_ID_E ModId, HI_TEE_LOG_LEVEL_E LogLevel);
extern HI_S32 HI_TEE_Get_LogLevel(HI_MODULE_ID_E ModId, HI_TEE_LOG_LEVEL_E *pLogLevel);
extern HI_VOID HI_TEE_LogOut(HI_TEE_LOG_LEVEL_E LogLevel, HI_MODULE_ID_E ModId, HI_U8 *pFuncName, HI_U32 LineNum, const HI_CHAR *format, ...);

/** @}*/  /** <!-- ==== API Declaration End ====*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif  /* __HI_TEE_LOG_H__ */


