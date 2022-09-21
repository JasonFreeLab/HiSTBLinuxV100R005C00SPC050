/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : loader_harden.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2015-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2015-07-29  sdk  N/A               Create this file.
 ******************************************************************************/

#ifndef __LOADER_HARDEN_H__
#define __LOADER_HARDEN_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"
#include "loader_dbinfo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


/*************************** Macro Definition *********************************/
/** \addtogroup      LOADER_DBHARDEN */
/** @{ */  /** <!-- [LOADER_DBHARDEN] */

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup      LOADER_DBHARDEN */
/** @{ */  /** <!-- [LOADER_DBHARDEN] */

/****** Enumeration definition ************/

#ifdef HI_ADVCA_SUPPORT
#define LDDB_D_HARDEN_BYTEWIDTH     (16)
#else
#define LDDB_D_HARDEN_BYTEWIDTH     (1)
#endif


/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @} */  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup      LOADER_DBHARDEN */
/** @{ */  /** <!-- [LOADER_DBHARDEN] */
HI_S32 BLSH_Init(HI_VOID);

HI_S32 BLSH_DeInit(HI_VOID);

HI_S32 BLSH_BlockDataVerify(HI_U8* pu8Data, HI_U32 u32Size, HI_U8* pu8ValueBuffer, HI_U32 u32BufferSize);

HI_S32 BLSH_BlockDataSignature(HI_U8* pu8Data, HI_U32 u32Size, HI_U8* pu8ValueBuffer, HI_U32 u32BufferSize);

HI_S32 BLSH_BlockDataEncrypt(HI_U8* pu8Data, HI_U32 u32Size);

HI_S32 BLSH_BlockDataDecrypt(HI_U8* pu8Data, HI_U32 u32Size);

/** @} */  /** <!-- ==== API Declaration End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__LOADER_HARDEN_H__*/

