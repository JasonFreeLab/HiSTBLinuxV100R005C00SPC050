/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : loader_flash.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2016-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2016-07-29  sdk  N/A               Create this file.
 ******************************************************************************/

#ifndef __LOADER_FLASH_H__
#define __LOADER_FLASH_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"
#include "hi_flash.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup     LOADER_FLASH */
/** @{ */  /** <!-- [LOADER_FLASH] */

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     LOADER_FLASH */
/** @{ */  /** <!-- [LOADER_FLASH] */

/****** Enumeration definition ************/

/****** Structure definition **************/

typedef struct tagLOADER_FLASH_OPENPARAM_S
{
    HI_CHAR*        pcPartitionName;
    HI_FLASH_TYPE_E enFlashType;
    HI_U64          u64Address;
    HI_U64          u64Length;

} LOADER_FLASH_OPENPARAM_S;

typedef struct tagLOADER_FLASH_INFO_S
{
    HI_U64          u64Address;
    HI_U64          u64PartSize;
    HI_U32          u32WBlockSize;
    HI_U32          u32RBlockSize;
    HI_U32          u32EBlockSize;

} LOADER_FLASH_INFO_S;

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     LOADER_FLASH */
/** @{ */  /** <!-- [LOADER_FLASH] */

#define LOADER_BYTEALIGN(u32DataSize, u32AlignSize) (((u32DataSize) + (u32AlignSize) - 1) & (~((u32AlignSize) - 1)))

HI_HANDLE LOADER_FLASH_OpenByName(HI_CHAR* pPartitionName);

HI_HANDLE LOADER_FLASH_Open(LOADER_FLASH_OPENPARAM_S* pstOpenParam);

HI_S32 LOADER_FLASH_Close(HI_HANDLE hHandle);

HI_U32 LOADER_FLASH_Read(HI_HANDLE hHandle, HI_U64 u64Address, HI_U8* pu8Buffer, HI_U32 u32BufferSize, HI_U32 u32ReadSize);

HI_S32 LOADER_FLASH_Write(HI_HANDLE hHandle, HI_U64 u64Address, HI_U8* pu8Data, HI_U32 u32Size);

HI_S32 LOADER_FLASH_GetInfo(HI_HANDLE hHandle, LOADER_FLASH_INFO_S* pstInfo);


/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__LOADER_FLASH_H__*/

