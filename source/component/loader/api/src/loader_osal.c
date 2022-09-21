/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : loader_osal.c
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

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include <malloc.h>
#if defined(HI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#elif defined(HI_LOADER_RUNNING_ENVIRONMENT_UBOOT)
#include "common.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_common.h"
#endif

#include "loader_osal.h"
#include "loader_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/

/*************************** Structure Definition *****************************/

/*************************** API Declaration **********************************/

HI_U32 LOADER_StrLen(const HI_CHAR* pcStr)
{
    if (HI_NULL_PTR == pcStr)
    {
        LOADER_PrintErrCode(LOADER_ERR_PARAM);
        return 0;
    }

    return strlen(pcStr);
}

HI_U64 LOADER_Strtoul(const HI_CHAR* nptr, HI_CHAR** endptr, int base)
{
    if ((HI_NULL_PTR == nptr))
    {
        LOADER_PrintErrCode(LOADER_ERR_PARAM);
        return 0;
    }

#if defined(HI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT)
    return strtoul(nptr, endptr, base);
#elif defined(HI_LOADER_RUNNING_ENVIRONMENT_UBOOT)
    return simple_strtoul(nptr, endptr, base);
#else
    return strtoul(nptr, endptr, base);
#endif
}

HI_CHAR* LOADER_StrStr(const HI_CHAR* pcStr1, const HI_CHAR* pcStr2)
{
    if ((HI_NULL_PTR == pcStr1)
        || (HI_NULL_PTR == pcStr2))
    {
        LOADER_PrintErrCode(LOADER_ERR_PARAM);
        return HI_NULL_PTR;
    }

    return (HI_CHAR*)strstr(pcStr1, pcStr2);
}

HI_CHAR* LOADER_StrNCpy(HI_CHAR* pcDestination, const HI_CHAR* pcSource , HI_U32 u32Count)
{
    if ((HI_NULL_PTR == pcDestination)
        || (HI_NULL_PTR == pcSource)
        || (0 == u32Count))
    {
        LOADER_PrintErrCode(LOADER_ERR_PARAM);
        return pcDestination;
    }

    return (HI_CHAR*)strncpy(pcDestination, pcSource, u32Count);
}

HI_S32 LOADER_StrNCmp(const HI_CHAR* pcStr1, const HI_CHAR* pcStr2, HI_U32 u32Count)
{
    if ((HI_NULL_PTR == pcStr1)
        || (HI_NULL_PTR == pcStr2)
        || (0 == u32Count))
    {
        LOADER_PrintErrCode(LOADER_ERR_PARAM);
        return -1;
    }

    return strncmp(pcStr1, pcStr2, u32Count);
}

HI_VOID* LOADER_MemCpy(HI_VOID* pDest, const HI_VOID* pSrc, HI_U32 u32Count)
{
    if ((HI_NULL_PTR == pDest)
        || (HI_NULL_PTR == pSrc)
        || (0 == u32Count))
    {
        LOADER_PrintErrCode(LOADER_ERR_MEM);
        return pDest;
    }

    return memcpy(pDest, pSrc, (size_t)u32Count);
}

HI_VOID* LOADER_MemSet(HI_VOID* pToSet, HI_S32 s32SetChar, HI_U32 u32Count)
{
    if ((HI_NULL_PTR == pToSet)
        || (0 == u32Count))
    {
        LOADER_PrintErrCode(LOADER_ERR_MEM);
        return pToSet;
    }

    return memset(pToSet, s32SetChar, (size_t)u32Count);
}

HI_S32 LOADER_MemCmp(HI_VOID* pBuf1, HI_VOID* pBuf2, HI_U32 u32Count)
{
    if ((HI_NULL_PTR == pBuf1)
        || (HI_NULL_PTR == pBuf2)
        || (0 == u32Count))
    {
        LOADER_PrintErrCode(LOADER_ERR_PARAM);
        return -1;
    }

    return memcmp(pBuf1, pBuf2, (size_t)u32Count);
}

HI_VOID* LOADER_MemMalloc(HI_U32 u32Size)
{
    if (0 == u32Size)
    {
        LOADER_PrintErrCode(LOADER_ERR_MEM);
        return HI_NULL_PTR;
    }

    return malloc((size_t)u32Size);
}

HI_VOID LOADER_MemFree(HI_VOID* pBuf)
{
    if (HI_NULL_PTR == pBuf)
    {
        LOADER_PrintErrCode(LOADER_ERR_MEM);
        return;
    }

    free(pBuf);
    pBuf = HI_NULL_PTR;

    return;
}

HI_S32 LOADER_MmzMalloc(HI_U32 u32Size, HI_U32* pu32PhyAddr, HI_U8** ppu8VirAddr)
{
    HI_U32 u32PhyAddr = 0;
    HI_U8* pu8VirAddr = HI_NULL_PTR;

    LOADER_CHECK_PARAM(0 == u32Size);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu32PhyAddr);
    LOADER_CHECK_PARAM(HI_NULL_PTR == ppu8VirAddr);

#ifdef HI_LOADER_RUNNING_ENVIRONMENT_BOOT
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = HI_MEM_Alloc(&u32PhyAddr, u32Size);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_MEM_Alloc, s32Ret);
        return s32Ret;
    }

    pu8VirAddr = (HI_U8*)u32PhyAddr;
#else
    u32PhyAddr = (HI_U32)(HI_SIZE_T)HI_MMZ_New(u32Size, 0, HI_NULL_PTR, "LOADER_API");
    if (0 == u32PhyAddr)
    {
        LOADER_PrintFuncErr(HI_MMZ_New, LOADER_ERR_MEM);
        return LOADER_ERR_MEM;
    }

    pu8VirAddr = (HI_U8*)HI_MMZ_Map(u32PhyAddr, 0);
    if (HI_NULL_PTR == pu8VirAddr)
    {
        LOADER_CHECK(HI_MMZ_Delete(u32PhyAddr));
        LOADER_PrintFuncErr(HI_MMZ_Map, LOADER_ERR_MEM);
        return LOADER_ERR_MEM;
    }
#endif

    *pu32PhyAddr = u32PhyAddr;
    *ppu8VirAddr = pu8VirAddr;

    return HI_SUCCESS;
}

HI_S32 LOADER_MmzFree(HI_U32 u32PhyAddr)
{
#ifdef HI_LOADER_RUNNING_ENVIRONMENT_BOOT
#else
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = HI_MMZ_Unmap(u32PhyAddr);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_MMZ_Unmap, s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MMZ_Delete(u32PhyAddr);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(HI_MMZ_Delete, s32Ret);
        return s32Ret;
    }
#endif

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

