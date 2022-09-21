/***********************************************************************************
*              Copyright 2004 - 2017, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  mpi_plcipher.c
* Description:  Define function implement.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20161012    NA                 NULL      Create this file.
***********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "hi_mpi_plcipher.h"
#include "hi_unf_hdcp.h"
#include "mpi_mmz.h"
#include "hi_mpi_mem.h"

#include "drv_plcipher_ioctl.h"
#include "hi_drv_struct.h"


static HI_S32 g_PLCipherDevFd = -1;
static HI_S32 g_PLCipherInitCounter = -1;
static pthread_mutex_t   g_PLCipherMutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_PLCIPHER_LOCK()           (void)pthread_mutex_lock(&g_PLCipherMutex)
#define HI_PLCIPHER_UNLOCK()     (void)pthread_mutex_unlock(&g_PLCipherMutex)

#define CHECK_PLCIPHER_OPEN()\
do{\
    HI_PLCIPHER_LOCK();\
    if (g_PLCipherInitCounter < 0)\
    {\
        HI_ERR_PLCIPHER("PLCIPHER is not open.\n");\
        HI_PLCIPHER_UNLOCK();\
        return HI_ERR_PLCIPHER_NOT_INIT;\
    }\
    HI_PLCIPHER_UNLOCK();\
}while(0)

#define CHECK_PLCIPHER_POINTER(p)           \
        do                                  \
        {                                   \
            if (HI_NULL == p)               \
            {                               \
                HI_ERR_PLCIPHER("Null Pointer!\n"); \
                return HI_ERR_PLCIPHER_INVALID_PTR; \
            }                               \
        } while (0)


#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_PRINT("[%s]:\n", name);\
    for ( _i = 0 ; _i < (len); _i++ )\
    {\
        if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
        HI_PRINT("%02x ", *((str)+_i));\
    }\
    HI_PRINT("\n");\
}

HI_S32 HI_MPI_PLCIPHER_Init(HI_VOID)
{
    HI_PLCIPHER_LOCK();

    if (g_PLCipherInitCounter > 0)
    {
        g_PLCipherInitCounter++;
        HI_PLCIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    g_PLCipherDevFd = open("/dev/"UMAP_DEVNAME_PLCIPHER, O_RDWR, 0);
    if (g_PLCipherDevFd < 0)
    {
        HI_FATAL_PLCIPHER("Open PLCIPHER err.\n");
        HI_PLCIPHER_UNLOCK();
        return HI_ERR_PLCIPHER_FAILED_INIT;
    }

    g_PLCipherInitCounter = 1;
    HI_PLCIPHER_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_DeInit(HI_VOID)
{
    HI_S32 Ret = HI_FAILURE;

    HI_PLCIPHER_LOCK();

    if(g_PLCipherInitCounter > 0)
    {
        g_PLCipherInitCounter--;
    }

    if(g_PLCipherInitCounter != 0)
    {
        HI_PLCIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    Ret = close(g_PLCipherDevFd);

    if(HI_SUCCESS != Ret)
    {
        HI_FATAL_PLCIPHER("Close plcipher err.\n");
        g_PLCipherInitCounter++;
        HI_PLCIPHER_UNLOCK();
        return HI_ERR_PLCIPHER_NOT_INIT;
    }

    g_PLCipherInitCounter = -1;

    HI_PLCIPHER_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_Create(HI_HANDLE* phPLCipher)
{
    HI_S32 Ret = HI_FAILURE;
    HI_HANDLE hPLCipher = HI_INVALID_HANDLE;

    CHECK_PLCIPHER_OPEN();
    CHECK_PLCIPHER_POINTER(phPLCipher);
    Ret = ioctl(g_PLCipherDevFd, CMD_PLCIPHER_CREATEHANDLE, &hPLCipher);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *phPLCipher = hPLCipher;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_Destroy(HI_HANDLE hPLCipher)
{
    HI_S32 Ret = HI_FAILURE;

    CHECK_PLCIPHER_OPEN();

    Ret = ioctl(g_PLCipherDevFd, CMD_PLCIPHER_DESTROYHANDLE, &hPLCipher);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_GetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{
    HI_S32 Ret = HI_FAILURE;
    PLCIPHER_CONFIG_S stCIHandle = {0};

    CHECK_PLCIPHER_OPEN();
    CHECK_PLCIPHER_POINTER(pstAttr);

    stCIHandle.Handle = hPLCipher;
    Ret = ioctl(g_PLCipherDevFd, CMD_PLCIPHER_GETATTR, &stCIHandle);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    memcpy(pstAttr, &stCIHandle.stPlCipherAtts, sizeof(HI_UNF_PLCIPHER_ATTR_S));

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_SetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S* pstAttr)
{

    HI_S32 Ret = HI_FAILURE;
    PLCIPHER_CONFIG_S stCIHandle = {0};

    CHECK_PLCIPHER_OPEN();
    CHECK_PLCIPHER_POINTER(pstAttr);

    if(pstAttr->enAlg < HI_UNF_PLCIPHER_ALG_AES_IPTV || pstAttr->enAlg > HI_UNF_PLCIPHER_ALG_AES_CBC)
    {
        HI_ERR_PLCIPHER("para set PLCIPHER alg 0x%x is invalid.\n", pstAttr->enAlg);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }
    stCIHandle.Handle = hPLCipher;
    memcpy(&stCIHandle.stPlCipherAtts, pstAttr, sizeof(HI_UNF_PLCIPHER_ATTR_S));

    Ret = ioctl(g_PLCipherDevFd, CMD_PLCIPHER_SETATTR, &stCIHandle);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, const HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
    HI_S32 Ret = HI_FAILURE;
    PLCIPHER_SetKey stSetKey;

    CHECK_PLCIPHER_OPEN();
    CHECK_PLCIPHER_POINTER(pu8Key);
    if (enKeyEvenOdd >= HI_UNF_PLCIPHER_KEY_BUTT)
    {
        HI_ERR_PLCIPHER("para enKeyEvenOdd 0x%x is invalid.\n", enKeyEvenOdd);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }

    if (u32KeyLen > sizeof(stSetKey.Key))
    {
        HI_ERR_PLCIPHER("para u32KeyLen 0x%x is invalid.\n", u32KeyLen);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }

    memset(&stSetKey, 0x0, sizeof(stSetKey));

    stSetKey.CIHandle = hPLCipher;
    stSetKey.bIsCWOrIV = HI_TRUE;
    stSetKey.enEvenOdd = enKeyEvenOdd;
    memcpy(stSetKey.Key, pu8Key, u32KeyLen);

    Ret=ioctl(g_PLCipherDevFd, CMD_PLCIPHER_SETKEY, &stSetKey);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enIVEvenOdd,const HI_U8 *pu8IV, HI_U32 u32IVLen)
{
    HI_S32 Ret = HI_FAILURE;
    PLCIPHER_SetKey stSetIV;

    CHECK_PLCIPHER_OPEN();
    CHECK_PLCIPHER_POINTER(pu8IV);

    if (enIVEvenOdd >= HI_UNF_PLCIPHER_KEY_BUTT)
    {
        HI_ERR_PLCIPHER("para enKeyEvenOdd 0x%x is invalid.\n", enIVEvenOdd);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }

    if (u32IVLen > sizeof(stSetIV.Key))
    {
        HI_ERR_PLCIPHER("para u32IVLen 0x%x is invalid.\n", u32IVLen);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }

    memset(&stSetIV,0x0,sizeof(stSetIV));

    stSetIV.CIHandle =  hPLCipher;
    stSetIV.bIsCWOrIV = HI_FALSE;
    stSetIV.enEvenOdd =  enIVEvenOdd;
    memcpy(stSetIV.Key, pu8IV, u32IVLen);

    Ret=ioctl(g_PLCipherDevFd, CMD_PLCIPHER_SETKEY, &stSetIV);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_Encrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length)
{
    HI_S32 Ret = HI_FAILURE;
    PLCIPHER_DATA_S CIdata;

    CHECK_PLCIPHER_OPEN();

    if (u32Length < PLCIPHER_MIN_SIZE_PRE_DESC || u32Length > PLCIPHER_MAX_SIZE_PRE_DESC)
    {
        HI_ERR_PLCIPHER("data len = 0x%x is invalid, correct rang is (0x%x ~ 0x%x )\n",
                        u32Length, PLCIPHER_MIN_SIZE_PRE_DESC, PLCIPHER_MAX_SIZE_PRE_DESC);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }
    if ( u32Length%(188) != 0)
    {
        HI_ERR_PLCIPHER("data len = 0x%x is invalid, must be times of (188*16) \n", u32Length);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }

    /* adapt 32 bit and 64 bit compile toolchain */
    CIdata.ScrPhyAddr = (HI_U32)((HI_ULONG)pSrcBuf);
    CIdata.DestPhyAddr = (HI_U32)((HI_ULONG)pDestBuf);
    CIdata.u32DataLength = u32Length;
    CIdata.CIHandle = hPLCipher;

    Ret = ioctl(g_PLCipherDevFd, CMD_PLCIPHER_ENCRYPT, &CIdata);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PLCIPHER_Decrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length)
{
    HI_S32 Ret = HI_FAILURE;
    PLCIPHER_DATA_S CIdata;

    CHECK_PLCIPHER_OPEN();

    if (u32Length < PLCIPHER_MIN_SIZE_PRE_DESC || u32Length > PLCIPHER_MAX_SIZE_PRE_DESC)
    {
        HI_ERR_PLCIPHER("data len = 0x%x is invalid, correct rang is (0x%x ~ 0x%x )\n",
                         u32Length, PLCIPHER_MIN_SIZE_PRE_DESC, PLCIPHER_MAX_SIZE_PRE_DESC);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }
    if (u32Length%(188) != 0)
    {
        HI_ERR_PLCIPHER("data len = 0x%x is invalid, must be times of (188*16) \n", u32Length);
        return HI_ERR_PLCIPHER_INVALID_PARA;
    }

    /* adapt 32 bit and 64 bit compile toolchain */
    CIdata.ScrPhyAddr = (HI_U32)((HI_ULONG)pSrcBuf);
    CIdata.DestPhyAddr = (HI_U32)((HI_ULONG)pDestBuf);
    CIdata.u32DataLength = u32Length;
    CIdata.CIHandle = hPLCipher;

    Ret = ioctl(g_PLCipherDevFd, CMD_PLCIPHER_DECRYPT, &CIdata);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

