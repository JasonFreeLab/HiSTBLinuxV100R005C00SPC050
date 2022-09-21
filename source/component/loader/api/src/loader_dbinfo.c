/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : loader_dbinfo.c
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

#include "hi_flash.h"


#if defined(HI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT)
#include "string.h"
#include "hi_drv_pdm.h"
extern char* getenv(const char* key);
#elif defined(HI_LOADER_RUNNING_ENVIRONMENT_UBOOT)
#include "common.h"
#include "hi_drv_pdm.h"
#else
#include <stdio.h>
#include "hi_unf_pdm.h"
#endif

#include "loader_debug.h"
#include "loader_osal.h"
#include "loader_flash.h"
#include "loader_harden.h"
#include "loader_dbinfo.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define LDDB_D_LEN_COMMAND              (1024)                  /**< Command line size according to arch/arm/include/asm/setup.h COMMAND_LINE_SIZE */
#define LDDB_D_LEN_VERIFYVALUE          (256)                   /**< Max length of Mac verify value */
#define LDDB_D_LEN_DEVICEITEM           (128)                   /**< Max length of device information items name */
#define LDDB_D_BOOTARGS_FILENAME        "/proc/cmdline"         /**< Path of cmdline file  */
#define LDDB_D_FLASHMAP_LOADERDB        "loaderdb"
#define LDDB_D_FLASHMAP_SOFTWAREINFO    "softwareinfo"

typedef struct tagLDDB_DATABLOCK_INFO_S
{
    HI_CHAR acPartitionName[LDDB_D_LEN_PARTNAME];       /**< The name of the partition data */
    HI_U32  u32Offset;                                  /**< The offset size in the partition */
    HI_U32  u32Size;                                    /**< The data size allocated in the partition */

} LDDB_DATABLOCK_INFO_S;

typedef struct tagLDDB_PARTITON_HEADER_S
{
    HI_U8  au8VerifyValue[LDDB_D_LEN_VERIFYVALUE];      /**< u32Crc, Hmac value   */
    HI_U32 u32EncryptedSize;                            /**< Encrypted data size */
    HI_U32 u32DataSize;                                 /**< Data size */

} LDDB_PARTITON_HEADER_S;

#ifdef HI_LOADER_RUNNING_ENVIRONMENT_BOOT

#define lddbGetDeviceInfo(pstrCfgName, pstrCfgValue, u32Size) HI_DRV_PDM_GetDeviceInfo(pstrCfgName, pstrCfgValue, u32Size)

static HI_S32 lddbGetBootargs(HI_CHAR* pcBuffer, HI_U32 u32BufferSize)
{
    HI_CHAR* pcBootargs = HI_NULL_PTR;

    LOADER_FuncEnter();

    pcBootargs = (HI_CHAR*)getenv("bootargs");
    if (HI_NULL_PTR == pcBootargs)
    {
        LOADER_PrintFuncErr(getenv, LOADER_ERR_DEVICE);
        return LOADER_ERR_DEVICE;
    }

    LOADER_MemCpy(pcBuffer, pcBootargs, u32BufferSize);

    LOADER_FuncExit();
    return HI_SUCCESS;
}
#else

#define lddbGetDeviceInfo(pstrCfgName, pstrCfgValue, u32Size) HI_UNF_PDM_GetDeviceInfo(pstrCfgName, pstrCfgValue, u32Size)

static HI_S32 lddbGetBootargs(HI_CHAR* pcBuffer, HI_U32 u32BufferSize)
{
    FILE* pFile = HI_NULL_PTR;
    HI_CHAR* pcRet = HI_NULL_PTR;

    LOADER_FuncEnter();

    pFile = fopen(LDDB_D_BOOTARGS_FILENAME, "r");
    if (HI_NULL_PTR == pFile)
    {
        LOADER_PrintFuncErr(fopen, LOADER_ERR_FILE);
        return LOADER_ERR_FILE;
    }

    pcRet = fgets(pcBuffer, (HI_S32)u32BufferSize, pFile);
    if (HI_NULL_PTR == pcRet)
    {
        LOADER_PrintFuncErr(fgets, LOADER_ERR_FILE);
        fclose(pFile);
        return LOADER_ERR_FILE;
    }

    fclose(pFile);

    LOADER_FuncExit();
    return HI_SUCCESS;
}
#endif

/*
 * get loader config parameter from bootargs in secondary style: loaderdb=part_name,offset,size.
 */
static HI_S32 lddbGetBlockInfo(HI_CHAR* pcDataName, LDDB_DATABLOCK_INFO_S* pstDataInfo)
{
    HI_CHAR* pstr  = HI_NULL_PTR;
    HI_CHAR* pstr2 = HI_NULL_PTR;
    HI_CHAR  acBootArgs[LDDB_D_LEN_COMMAND] = {0};
    HI_S32   s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    s32Ret = lddbGetBootargs(acBootArgs, LDDB_D_LEN_COMMAND);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbGetBootargs, s32Ret);
        return s32Ret;
    }

    pstr = LOADER_StrStr(acBootArgs, pcDataName);
    if (HI_NULL_PTR == pstr)
    {
        LOADER_PrintFuncErr(LOADER_StrStr, LOADER_ERR_DEVICE);
        return LOADER_ERR_DEVICE;
    }

    pstr += LOADER_StrLen(pcDataName);
    if ('=' != pstr[0])
    {
        LOADER_PrintFuncErr(LOADER_StrLen, LOADER_ERR_DEVICE);
        return LOADER_ERR_DEVICE;
    }

    pstr += 1;
    pstr2 = LOADER_StrStr(pstr, ",");
    if (HI_NULL_PTR == pstr2)
    {
        LOADER_PrintFuncErr(LOADER_StrStr, LOADER_ERR_DEVICE);
        return LOADER_ERR_DEVICE;
    }

    if (LDDB_D_LEN_PARTNAME < (pstr2 - pstr))
    {
        LOADER_PrintFuncErr(LOADER_StrStr, LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    LOADER_MemCpy(pstDataInfo->acPartitionName, pstr, (HI_U32)(pstr2 - pstr));

    pstr  = pstr2 + 1;
    pstDataInfo->u32Offset = (HI_U32)LOADER_Strtoul(pstr, HI_NULL_PTR, 16);

    pstr = LOADER_StrStr(pstr, ",");
    if (HI_NULL_PTR == pstr)
    {
        LOADER_PrintFuncErr(LOADER_StrStr, LOADER_ERR_DEVICE);
        return LOADER_ERR_DEVICE;
    }

    pstr = pstr + 1;
    pstDataInfo->u32Size = (HI_U32)LOADER_Strtoul(pstr, HI_NULL_PTR, 16);

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 lddbFlashDataHarden(HI_U8* pu8DataAddr, HI_U32 u32DataSize)
{
    HI_U32 u32SignDataLen = 0;
    HI_U8* pucSignDataPos = HI_NULL_PTR;
    HI_U8* pu8EncryptedData = HI_NULL_PTR;
    LDDB_PARTITON_HEADER_S* pstHeader = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    pstHeader = (LDDB_PARTITON_HEADER_S*)pu8DataAddr;
    pu8EncryptedData  = pu8DataAddr + sizeof(LDDB_PARTITON_HEADER_S);

    s32Ret = BLSH_BlockDataEncrypt(pu8EncryptedData, pstHeader->u32EncryptedSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_BlockDataEncrypt, s32Ret);
        return s32Ret;
    }

    pucSignDataPos = pu8DataAddr + sizeof(pstHeader->au8VerifyValue);
    u32SignDataLen = u32DataSize - sizeof(pstHeader->au8VerifyValue);

    s32Ret = BLSH_BlockDataSignature(pucSignDataPos, u32SignDataLen, pstHeader->au8VerifyValue, sizeof(pstHeader->au8VerifyValue));
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_BlockDataSignature, s32Ret);
        return s32Ret;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 lddbFlashDataVerify(HI_U8* pu8FlashData, HI_U32 u32FlashSize)
{
    HI_U32 u32VerifyDataLen = 0;
    HI_U8* pucVerifyDataPos = HI_NULL_PTR;
    HI_U8* pucEncryptedData = HI_NULL_PTR;
    LDDB_PARTITON_HEADER_S* pstHeader = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    pstHeader = (LDDB_PARTITON_HEADER_S*)(HI_VOID*)pu8FlashData;

    pucVerifyDataPos = pu8FlashData + sizeof(pstHeader->au8VerifyValue);
    u32VerifyDataLen = u32FlashSize - sizeof(pstHeader->au8VerifyValue);
    s32Ret = BLSH_BlockDataVerify(pucVerifyDataPos, u32VerifyDataLen, pstHeader->au8VerifyValue, sizeof(pstHeader->au8VerifyValue));
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_BlockDataVerify, s32Ret);
        return s32Ret;
    }

    pucEncryptedData = pu8FlashData + sizeof(LDDB_PARTITON_HEADER_S);
    s32Ret = BLSH_BlockDataDecrypt(pucEncryptedData, pstHeader->u32EncryptedSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_BlockDataDecrypt, s32Ret);
        return s32Ret;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 lddbPartitionOpen(HI_CHAR* pcPartitionName, HI_HANDLE* phHandle, HI_U32* pu32Offset, HI_U32* pu32Size)
{
    HI_U32 u32Size = 0;
    HI_U32 u32Offset = 0;
    LOADER_FLASH_INFO_S stFlashInfo;
    LDDB_DATABLOCK_INFO_S stBlockInfo;
    HI_HANDLE hFlashHandle = HI_INVALID_HANDLE;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    hFlashHandle = LOADER_FLASH_OpenByName(pcPartitionName);
    if (HI_INVALID_HANDLE == hFlashHandle)
    {
        LOADER_MemSet(&stBlockInfo, 0x00, sizeof(stBlockInfo));
        s32Ret = lddbGetBlockInfo(pcPartitionName, &stBlockInfo);
        if (HI_SUCCESS != s32Ret)
        {
            LOADER_PrintFuncErr(lddbGetBlockInfo, s32Ret);
            return s32Ret;
        }

        hFlashHandle = LOADER_FLASH_OpenByName(stBlockInfo.acPartitionName);
        if (HI_INVALID_HANDLE == hFlashHandle)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_OpenByName, LOADER_ERR_DEVICE);
            return LOADER_ERR_DEVICE;
        }

        LOADER_MemSet(&stFlashInfo, 0x00, sizeof(stFlashInfo));
        s32Ret = LOADER_FLASH_GetInfo(hFlashHandle, &stFlashInfo);
        if (HI_SUCCESS != s32Ret)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_GetInfo, s32Ret);
            LOADER_CHECK(LOADER_FLASH_Close(hFlashHandle));
            return LOADER_ERR_DEVICE;
        }

        if (stFlashInfo.u64PartSize < ((HI_U64)stBlockInfo.u32Offset + (HI_U64)stBlockInfo.u32Size))
        {
            LOADER_CHECK(LOADER_FLASH_Close(hFlashHandle));
            LOADER_PrintErrCode(LOADER_ERR_DEVICE);
            return LOADER_ERR_DEVICE;
        }

        u32Offset = stBlockInfo.u32Offset;
        u32Size   = stBlockInfo.u32Size;
    }
    else
    {
        LOADER_MemSet(&stFlashInfo, 0x00, sizeof(stFlashInfo));
        s32Ret = LOADER_FLASH_GetInfo(hFlashHandle, &stFlashInfo);
        if (HI_SUCCESS != s32Ret)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_GetInfo, s32Ret);
            LOADER_CHECK(LOADER_FLASH_Close(hFlashHandle));
            return LOADER_ERR_DEVICE;
        }

        u32Offset = 0;
        u32Size   = stFlashInfo.u64PartSize;
    }

    s32Ret = BLSH_Init();
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_Init, s32Ret);

        LOADER_CHECK(LOADER_FLASH_Close(hFlashHandle));
        return s32Ret;
    }

    *pu32Offset = u32Offset;
    *pu32Size   = u32Size;
    *phHandle   = hFlashHandle;

    LOADER_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 lddbPartitionClose(HI_HANDLE hHandle)
{
    LOADER_FuncEnter();

    LOADER_CHECK(BLSH_DeInit());

    LOADER_CHECK(LOADER_FLASH_Close(hHandle));

    LOADER_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 lddbPartitionDataRead(HI_HANDLE hHandle, HI_U8* pu8DataBuffer, HI_U32 u32DataSize, HI_U32 u32Offset, HI_U32 u32Size)
{
    HI_U32 u32TotalSize = 0;
    HI_U32 u32BufferSize = 0;
    HI_U32 u32ReturnSize = 0;
    LOADER_FLASH_INFO_S stFlashInfo;
    LDDB_PARTITON_HEADER_S* pstHeader = HI_NULL_PTR;
    HI_U8* pu8PartitionBuff = HI_NULL_PTR;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    s32Ret = LOADER_FLASH_GetInfo(hHandle, &stFlashInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_GetInfo, s32Ret);
        return s32Ret;
    }

    u32BufferSize = LOADER_BYTEALIGN(sizeof(LDDB_PARTITON_HEADER_S), stFlashInfo.u32RBlockSize);
    if (u32BufferSize > u32Size)
    {
        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    pu8PartitionBuff = LOADER_MemMalloc(u32BufferSize);
    if (HI_NULL_PTR == pu8PartitionBuff)
    {
        LOADER_PrintErrCode(LOADER_ERR_MEM);
        return LOADER_ERR_MEM;
    }

    LOADER_MemSet(pu8PartitionBuff, 0x00, u32BufferSize);

    u32ReturnSize = LOADER_FLASH_Read(hHandle, u32Offset, pu8PartitionBuff, u32BufferSize, u32BufferSize);
    if (u32BufferSize != u32ReturnSize)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Read, s32Ret);
        LOADER_MemFreeSetNull(pu8PartitionBuff);
        return s32Ret;
    }

    pstHeader = (LDDB_PARTITON_HEADER_S*)pu8PartitionBuff;
    if (pstHeader->u32DataSize > u32DataSize)
    {
        LOADER_MemFreeSetNull(pu8PartitionBuff);

        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    if ((0 == pstHeader->u32DataSize)
        || (pstHeader->u32EncryptedSize != LOADER_BYTEALIGN(pstHeader->u32DataSize, LDDB_D_HARDEN_BYTEWIDTH)))
    {
        LOADER_MemFreeSetNull(pu8PartitionBuff);

        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    u32TotalSize = pstHeader->u32EncryptedSize + sizeof(LDDB_PARTITON_HEADER_S);
    if (u32TotalSize > stFlashInfo.u64PartSize)
    {
        LOADER_MemFreeSetNull(pu8PartitionBuff);

        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    if (u32BufferSize < u32TotalSize)
    {
        LOADER_MemFreeSetNull(pu8PartitionBuff);

        u32BufferSize = LOADER_BYTEALIGN(u32TotalSize, stFlashInfo.u32RBlockSize);
        if (u32BufferSize > u32Size)
        {
            LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
            return LOADER_ERR_OVERFLOW;
        }

        pu8PartitionBuff = LOADER_MemMalloc(u32BufferSize);
        if (HI_NULL_PTR == pu8PartitionBuff)
        {
            LOADER_PrintErrCode(LOADER_ERR_MEM);
            return LOADER_ERR_MEM;
        }

        LOADER_MemSet(pu8PartitionBuff, 0x00, u32BufferSize);
        u32ReturnSize = LOADER_FLASH_Read(hHandle, u32Offset, pu8PartitionBuff, u32BufferSize, u32BufferSize);
        if (u32BufferSize != u32ReturnSize)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_Read, s32Ret);
            LOADER_MemFreeSetNull(pu8PartitionBuff);
            return s32Ret;
        }

        pstHeader = (LDDB_PARTITON_HEADER_S*)pu8PartitionBuff;
    }

    s32Ret = lddbFlashDataVerify(pu8PartitionBuff, u32TotalSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbFlashDataVerify, s32Ret);
        LOADER_MemFreeSetNull(pu8PartitionBuff);
        return s32Ret;
    }

    LOADER_MemCpy(pu8DataBuffer, pu8PartitionBuff + sizeof(LDDB_PARTITON_HEADER_S), pstHeader->u32DataSize);
    LOADER_MemFreeSetNull(pu8PartitionBuff);

    LOADER_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 lddbPartitionDataWrite(HI_HANDLE hHandle, HI_U8* pu8Data, HI_U32 u32DataSize, HI_U32 u32Offset, HI_U32 u32Size)
{
    HI_U32 u32TotalDataSize = 0;
    HI_U32 u32EncryptedSize = 0;
    HI_U8* pu8TotalDataBuff = HI_NULL_PTR;
    LDDB_PARTITON_HEADER_S* pstHeader = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    u32EncryptedSize = LOADER_BYTEALIGN(u32DataSize, LDDB_D_HARDEN_BYTEWIDTH);
    u32TotalDataSize = sizeof(LDDB_PARTITON_HEADER_S) + u32EncryptedSize;
    if (u32TotalDataSize > u32Size)
    {
        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    pu8TotalDataBuff = LOADER_MemMalloc(u32TotalDataSize);
    if (HI_NULL_PTR == pu8TotalDataBuff)
    {
        LOADER_PrintErrCode(LOADER_ERR_MEM);
        return LOADER_ERR_MEM;
    }

    LOADER_MemSet(pu8TotalDataBuff, 0x00, u32TotalDataSize);
    LOADER_MemCpy(pu8TotalDataBuff + sizeof(LDDB_PARTITON_HEADER_S), pu8Data, u32DataSize);

    pstHeader = (LDDB_PARTITON_HEADER_S*)pu8TotalDataBuff;
    pstHeader->u32DataSize = u32DataSize;
    pstHeader->u32EncryptedSize = u32EncryptedSize;

    s32Ret = lddbFlashDataHarden(pu8TotalDataBuff, u32TotalDataSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbFlashDataHarden, s32Ret);
        LOADER_MemFreeSetNull(pu8TotalDataBuff);
        return s32Ret;
    }

    s32Ret = LOADER_FLASH_Write(hHandle, u32Offset, pu8TotalDataBuff, u32TotalDataSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Write, s32Ret);
        LOADER_MemFreeSetNull(pu8TotalDataBuff);
        return s32Ret;
    }

    LOADER_MemFreeSetNull(pu8TotalDataBuff);

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 LDDB_GetLoaderInfo(LDDB_LOADER_INFO_S* pstLoaderInfo)
{
    HI_U32 u32OffsetSize = 0;
    HI_U32 u32PartitionSize = 0;
    HI_HANDLE hPartitionHandle = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstLoaderInfo);

    s32Ret = lddbPartitionOpen(LDDB_D_FLASHMAP_LOADERDB, &hPartitionHandle, &u32OffsetSize, &u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionOpen, s32Ret);
        return s32Ret;
    }

    if (u32PartitionSize < sizeof(LDDB_LOADER_INFO_S))
    {
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    s32Ret = lddbPartitionDataRead(hPartitionHandle, (HI_U8*)pstLoaderInfo, sizeof(LDDB_LOADER_INFO_S), u32OffsetSize, u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionDataRead, s32Ret);
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));
        return s32Ret;
    }

    LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

    LOADER_FuncExit();
    return HI_SUCCESS;

}

HI_S32 LDDB_SetLoaderInfo(LDDB_LOADER_INFO_S* pstLoaderInfo)
{
    HI_U32 u32OffsetSize = 0;
    HI_U32 u32PartitionSize = 0;
    HI_HANDLE hPartitionHandle = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstLoaderInfo);

    s32Ret = lddbPartitionOpen(LDDB_D_FLASHMAP_LOADERDB, &hPartitionHandle, &u32OffsetSize, &u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionOpen, s32Ret);
        return s32Ret;
    }

    if (u32PartitionSize < sizeof(LDDB_LOADER_INFO_S))
    {
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    s32Ret = lddbPartitionDataWrite(hPartitionHandle, (HI_U8*)pstLoaderInfo, sizeof(LDDB_LOADER_INFO_S), u32OffsetSize, u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionDataWrite, s32Ret);
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));
        return s32Ret;
    }

    LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 LDDB_GetSoftwareInfo(LDDB_SOFTWARE_INFO_S* pstSoftwareInfo)
{
    HI_U32 u32OffsetSize = 0;
    HI_U32 u32PartitionSize = 0;
    HI_HANDLE hPartitionHandle = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstSoftwareInfo);

    s32Ret = lddbPartitionOpen(LDDB_D_FLASHMAP_SOFTWAREINFO, &hPartitionHandle, &u32OffsetSize, &u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionOpen, s32Ret);
        return s32Ret;
    }

    if (u32PartitionSize < sizeof(LDDB_SOFTWARE_INFO_S))
    {
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    s32Ret = lddbPartitionDataRead(hPartitionHandle, (HI_U8*)pstSoftwareInfo, sizeof(LDDB_SOFTWARE_INFO_S), u32OffsetSize, u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionDataRead, s32Ret);
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));
        return s32Ret;
    }

    LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 LDDB_SetSoftwareInfo(LDDB_SOFTWARE_INFO_S* pstSoftwareInfo)
{
    HI_U32 u32OffsetSize = 0;
    HI_U32 u32PartitionSize = 0;
    HI_HANDLE hPartitionHandle = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    s32Ret = lddbPartitionOpen(LDDB_D_FLASHMAP_SOFTWAREINFO, &hPartitionHandle, &u32OffsetSize, &u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionOpen, s32Ret);
        return s32Ret;
    }

    if (u32PartitionSize < sizeof(LDDB_SOFTWARE_INFO_S))
    {
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

        LOADER_PrintErrCode(LOADER_ERR_OVERFLOW);
        return LOADER_ERR_OVERFLOW;
    }

    s32Ret = lddbPartitionDataWrite(hPartitionHandle, (HI_U8*)pstSoftwareInfo, sizeof(LDDB_SOFTWARE_INFO_S), u32OffsetSize, u32PartitionSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbPartitionDataWrite, s32Ret);
        LOADER_CHECK(lddbPartitionClose(hPartitionHandle));
        return s32Ret;
    }

    LOADER_CHECK(lddbPartitionClose(hPartitionHandle));

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 LDDB_GetDeviceInfo(LDDB_DEVICE_INFO_S* pstDeviceInfo)
{
    HI_CHAR ac8Buf[LDDB_D_LEN_DEVICEITEM] = {0};
    HI_S32  s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstDeviceInfo);

    LOADER_MemSet(ac8Buf, 0x00, sizeof(ac8Buf));
    s32Ret = lddbGetDeviceInfo("OUI", ac8Buf, sizeof(ac8Buf));
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbGetDeviceInfo, s32Ret);
        return s32Ret;
    }

    pstDeviceInfo->u32OUI = (HI_U32)LOADER_Strtoul(ac8Buf, HI_NULL_PTR, 16);

    LOADER_MemSet(ac8Buf, 0x00, sizeof(ac8Buf));
    s32Ret = lddbGetDeviceInfo("HW", ac8Buf, sizeof(ac8Buf));
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbGetDeviceInfo, s32Ret);
        return s32Ret;
    }

    pstDeviceInfo->u32HardwareVersion = (HI_U32)LOADER_Strtoul(ac8Buf, HI_NULL_PTR, 16);

    LOADER_MemSet(ac8Buf, 0x00, sizeof(ac8Buf));
    s32Ret = lddbGetDeviceInfo("SN", ac8Buf, sizeof(ac8Buf));
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(lddbGetDeviceInfo, s32Ret);
        return s32Ret;
    }

    pstDeviceInfo->u32SerialNum = (HI_U32)LOADER_Strtoul(ac8Buf, HI_NULL_PTR, 16);

    LOADER_FuncExit();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

