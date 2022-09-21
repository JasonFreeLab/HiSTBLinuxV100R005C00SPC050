/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : loader_flash.c
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

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/


#if defined(HI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT)
#include <stdio.h>
#include <string.h>
#elif defined(HI_LOADER_RUNNING_ENVIRONMENT_UBOOT)
#include "common.h"
#else
#include <stdio.h>
#include <string.h>
#endif

#include "hi_flash.h"
#include "loader_osal.h"
#include "loader_debug.h"
#include "loader_flash.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


HI_HANDLE LOADER_FLASH_OpenByName(HI_CHAR* pPartitionName)
{
    HI_HANDLE hHandle = HI_INVALID_HANDLE;

    LOADER_CHECK_PARAM_RETERR(HI_NULL_PTR == pPartitionName, HI_INVALID_HANDLE);

    hHandle = HI_Flash_OpenByName(pPartitionName);
    if (HI_INVALID_HANDLE == hHandle)
    {
        LOADER_PrintFuncErr(HI_Flash_OpenByName, LOADER_ERR_FLASH);
        return HI_INVALID_HANDLE;
    }

    LOADER_FuncExit();
    return hHandle;
}

HI_HANDLE LOADER_FLASH_Open(LOADER_FLASH_OPENPARAM_S* pstOpenParam)
{
    HI_HANDLE hHandle = HI_INVALID_HANDLE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM_RETERR(HI_NULL_PTR == pstOpenParam, HI_INVALID_HANDLE);

    hHandle = HI_Flash_Open(pstOpenParam->enFlashType,
                            pstOpenParam->pcPartitionName,
                            pstOpenParam->u64Address,
                            pstOpenParam->u64Length);
    if (HI_INVALID_HANDLE == hHandle)
    {
        LOADER_PrintFuncErr(HI_Flash_Open, LOADER_ERR_FLASH);
        return HI_INVALID_HANDLE;
    }

    LOADER_FuncExit();
    return hHandle;
}

HI_S32 LOADER_FLASH_Close(HI_HANDLE hHandle)
{
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_INVALID_HANDLE == hHandle);

    s32Ret = HI_Flash_Close(hHandle);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_Flash_Close, s32Ret);
        return HI_FAILURE;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_U32 LOADER_FLASH_Read(HI_HANDLE hHandle, HI_U64 u64Address, HI_U8* pu8Buffer, HI_U32 u32BufferSize, HI_U32 u32ReadSize)
{
    HI_U32 u32DataSize = 0;
    HI_U32 u32PageSize = 0;
    HI_Flash_InterInfo_S stFlashInfo;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM_RETERR(HI_INVALID_HANDLE == hHandle, 0);
    LOADER_CHECK_PARAM_RETERR(HI_NULL_PTR == pu8Buffer, 0);
    LOADER_CHECK_PARAM_RETERR(0 == u32BufferSize, 0);
    LOADER_CHECK_PARAM_RETERR(0 == u32ReadSize, 0);

    LOADER_MemSet(&stFlashInfo, 0x00, sizeof(stFlashInfo));
    s32Ret = HI_Flash_GetInfo(hHandle, &stFlashInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_Flash_GetInfo, s32Ret);
        return 0;
    }

    u32PageSize = (HI_FLASH_TYPE_EMMC_0 == stFlashInfo.FlashType) ? stFlashInfo.BlockSize : stFlashInfo.PageSize;
    u32DataSize = LOADER_BYTEALIGN(u32ReadSize, u32PageSize);

    if (u32BufferSize < u32DataSize)
    {
        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return 0;
    }

    s32Ret = HI_Flash_Read(hHandle, u64Address, pu8Buffer, u32DataSize, HI_FLASH_RW_FLAG_RAW);
    if (0 >= s32Ret)
    {
        LOADER_PrintFuncErr(HI_Flash_Read, s32Ret);
        return 0;
    }

    LOADER_FuncExit();
    return (HI_U32)s32Ret;
}

HI_S32 LOADER_FLASH_Write(HI_HANDLE hHandle, HI_U64 u64Address, HI_U8* pu8Data, HI_U32 u32Size)
{
    HI_U32 u32WriteSize = 0;
    HI_U32 u32EraseSize = 0;
    HI_Flash_InterInfo_S stFlashInfo;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_INVALID_HANDLE == hHandle);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8Data);
    LOADER_CHECK_PARAM(0 == u32Size);

    LOADER_MemSet(&stFlashInfo, 0x00, sizeof(stFlashInfo));

    s32Ret = HI_Flash_GetInfo(hHandle, &stFlashInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_Flash_GetInfo, s32Ret);
        return LOADER_ERR_FLASH;
    }

    if (HI_FLASH_TYPE_EMMC_0 != stFlashInfo.FlashType)
    {
        u32EraseSize = LOADER_BYTEALIGN(u32Size, stFlashInfo.BlockSize);
        u32WriteSize = LOADER_BYTEALIGN(u32Size, stFlashInfo.PageSize);

        s32Ret = HI_Flash_Erase(hHandle, u64Address, (HI_U64)u32EraseSize);
        if ((HI_S32)u32EraseSize != s32Ret)
        {
            LOADER_PrintFuncErr(HI_Flash_Erase, s32Ret);
            return LOADER_ERR_FLASH;
        }
    }
    else
    {
        u32WriteSize = LOADER_BYTEALIGN(u32Size, stFlashInfo.BlockSize);
    }

    s32Ret = HI_Flash_Write(hHandle, u64Address, pu8Data, u32WriteSize, HI_FLASH_RW_FLAG_RAW);
    if ((HI_S32)u32WriteSize != s32Ret)
    {
        LOADER_PrintFuncErr(HI_Flash_Write, s32Ret);
        return LOADER_ERR_FLASH;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 LOADER_FLASH_GetInfo(HI_HANDLE hHandle, LOADER_FLASH_INFO_S* pstInfo)
{
    HI_Flash_InterInfo_S stFlashInfo;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_INVALID_HANDLE == hHandle);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pstInfo);

    LOADER_MemSet(&stFlashInfo, 0x00, sizeof(stFlashInfo));

    s32Ret = HI_Flash_GetInfo(hHandle, &stFlashInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_Flash_GetInfo, s32Ret);
        return LOADER_ERR_FLASH;
    }

    if (HI_FLASH_TYPE_EMMC_0 == stFlashInfo.FlashType)
    {
        pstInfo->u32RBlockSize = stFlashInfo.BlockSize;
        pstInfo->u32WBlockSize = stFlashInfo.BlockSize;
    }
    else
    {
        pstInfo->u32RBlockSize = stFlashInfo.PageSize;
        pstInfo->u32WBlockSize = stFlashInfo.PageSize;
    }

    pstInfo->u32EBlockSize = stFlashInfo.BlockSize;
    pstInfo->u64PartSize = stFlashInfo.PartSize;

    LOADER_FuncExit();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

