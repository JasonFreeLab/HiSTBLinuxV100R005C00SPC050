/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cipher_adapt.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __CIPHER_ADAPT_H_
#define __CIPHER_ADAPT_H_

#include <tee_os_hal.h>
#include "hi_type.h"
#include "hi_tee_debug.h"
#include "crys_hmac.h"
#include "uuid_chip.h"
#include "hi_tee_cipher.h"
#include "tee_cipher_ioctl.h"
#include "hi_tee_drv_cipher.h"
#include "cipher_config.h"
#include "drv_tee_mem.h"
#include "drv_cipher_common.h"
#include "spacc_intf.h"
#include "drv_rng.h"
#include "drv_rsa.h"
#include "drv_sm2.h"
#include "tee_drv_common.h"

/**************************** M A C R O ****************************/
#define  TEE_ERR_CIPHER_NOT_INIT                     (HI_S32)(0x804D0001)
#define  TEE_ERR_CIPHER_INVALID_HANDLE               (HI_S32)(0x804D0002)
#define  TEE_ERR_CIPHER_INVALID_POINT                (HI_S32)(0x804D0003)
#define  TEE_ERR_CIPHER_INVALID_PARA                 (HI_S32)(0x804D0004)
#define  TEE_ERR_CIPHER_FAILED_INIT                  (HI_S32)(0x804D0005)
#define  TEE_ERR_CIPHER_FAILED_GETHANDLE             (HI_S32)(0x804D0006)
#define  TEE_ERR_CIPHER_FAILED_RELEASEHANDLE         (HI_S32)(0x804D0007)
#define  TEE_ERR_CIPHER_FAILED_CONFIGAES             (HI_S32)(0x804D0008)
#define  TEE_ERR_CIPHER_FAILED_CONFIGDES             (HI_S32)(0x804D0009)
#define  TEE_ERR_CIPHER_FAILED_ENCRYPT               (HI_S32)(0x804D000A)
#define  TEE_ERR_CIPHER_FAILED_DECRYPT               (HI_S32)(0x804D000B)
#define  TEE_ERR_CIPHER_BUSY                         (HI_S32)(0x804D000C)
#define  TEE_ERR_CIPHER_NO_AVAILABLE_RNG             (HI_S32)(0x804D000D)

#define HI_ID_CIPHER            0x4D

#ifdef  CFG_HI_TEE_SMMU_SUPPORT
#define CIPHER_MMU_SUPPORT
#endif

#define TEE_CIPHER_IOC_NA       0U
#define TEE_CIPHER_IOC_W        1U
#define TEE_CIPHER_IOC_R        2U
#define TEE_CIPHER_IOC_RW       3U

#define TEE_CIPHER_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define CIPHER_IOR(nr,size)     TEE_CIPHER_IOC(TEE_CIPHER_IOC_R, HI_ID_CIPHER,(nr), sizeof(size))
#define CIPHER_IOW(nr,size)     TEE_CIPHER_IOC(TEE_CIPHER_IOC_W, HI_ID_CIPHER,(nr), sizeof(size))
#define CIPHER_IOWR(nr,size)    TEE_CIPHER_IOC(TEE_CIPHER_IOC_RW,HI_ID_CIPHER,(nr),sizeof(size))

#define CIPHER_IOC_DIR(nr)       (((nr) >> 30) & 0x03)
#define CIPHER_IOC_TYPE(nr)      (((nr) >> 8) & 0xFF)
#define CIPHER_IOC_NR(nr)        (((nr) >> 0) & 0xFF)
#define CIPHER_IOC_SIZE(nr)      (((nr) >> 16) & 0x3FFF)

#define U32_TO_POINT(addr)  ((HI_VOID*)((HI_SIZE_T)(addr)))
#define POINT_TO_U32(addr)  ((HI_U32)((HI_SIZE_T)(addr)))

#define HAL_CIPHER_ReadReg(addr, result)  (*(result) = *(volatile unsigned int *)(tee_hal_phys_to_virt((unsigned long)addr)))
#define HAL_CIPHER_WriteReg(addr,result)  (*(volatile unsigned int *)(tee_hal_phys_to_virt((unsigned long)addr)) = (result))

#define HAL_SET_BIT(src, bit)        ((src) |= (1<<bit))
#define HAL_CLEAR_BIT(src,bit)       ((src) &= ~(1<<bit))

#define CPU_TO_BE16(v) (((v)<< 8) | ((v)>>8))
#define CPU_TO_BE32(v) (((v)>>24) | (((v)>>8)&0xff00) | (((v)<<8)&0xff0000) | ((v)<<24))
#define CPU_TO_BE64(x) ((HI_U64)(                         \
        (((HI_U64)(x) & (HI_U64)0x00000000000000ffULL) << 56) |   \
        (((HI_U64)(x) & (HI_U64)0x000000000000ff00ULL) << 40) |   \
        (((HI_U64)(x) & (HI_U64)0x0000000000ff0000ULL) << 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00000000ff000000ULL) <<  8) |   \
        (((HI_U64)(x) & (HI_U64)0x000000ff00000000ULL) >>  8) |   \
        (((HI_U64)(x) & (HI_U64)0x0000ff0000000000ULL) >> 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00ff000000000000ULL) >> 40) |   \
        (((HI_U64)(x) & (HI_U64)0xff00000000000000ULL) >> 56)))

#if defined(TESTSUITE_RTOSck_UT) || defined(TESTSUITE_RTOSck_PT) || defined(TESTSUITE_RTOSck_IT)
#define CIPHER_ACCESS_CHECK(addr, size)

#define CIPHER_ACCESS_READ_RIGHT_CHECK(addr, size)

#define CIPHER_ACCESS_WRITE_RIGHT_CHECK(addr, size)
#else
#define CIPHER_ACCESS_CHECK(addr, size)     if(false == tee_hal_access_check(addr, size)) {\
                    tee_hal_printf("ERROR!!!!, it seems the input buffer is not valid line is %d\n", __LINE__);\
                    return TEE_ERROR_ACCESS_DENIED;\
                    }

#define CIPHER_ACCESS_READ_RIGHT_CHECK(addr, size)  if(false == tee_hal_read_right_check(addr, size)) {\
                    tee_hal_printf("ERROR!!!!, it seems the input buffer READ denied line is %d\n", __LINE__);\
                    return TEE_ERROR_ACCESS_DENIED;\
                    }

#define CIPHER_ACCESS_WRITE_RIGHT_CHECK(addr, size)   if(false == tee_hal_write_right_check(addr, size)) {\
                    tee_hal_printf("ERROR!!!!, it seems the input buffer write denied line is %d\n", __LINE__);\
                    return TEE_ERROR_ACCESS_DENIED;\
                    }
#endif

/**************************** S T D L I B ****************************/
#define cipher_ioremap_nocache(addr, size)  (HI_VOID*)(addr)
#define cipher_iounmap(x)                   (HI_VOID)x

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len);
int  cipher_memcmp_s(const void *a, const void *b, unsigned len);
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len);

#define cipher_mutex                               HI_VOID *

static inline HI_S32 cipher_mutex_lock_fuction(cipher_mutex* x)
{
    return 0;
}

static inline HI_S32 cipher_mutex_unlock_fuction(cipher_mutex* x)
{
    return 0;
}

#define cipher_mutex_init(x)                       (HI_VOID)x
#define cipher_mutex_lock(x)                       cipher_mutex_lock_fuction(x)
#define cipher_mutex_unlock(x)                     cipher_mutex_unlock_fuction(x)

#define cipher_queue_head                          HI_VOID *
#define cipher_queue_init(x)                       (HI_VOID)x
#define cipher_queue_wait_up(x)                    (HI_VOID)x
#define cipher_queue_wait_timeout(head, con, time)  0

#define cipher_request_irq(irq, func, name)         0
#define cipher_free_irq(x)                          (HI_VOID)x

extern void v7_flush_kern_cache_all(void);
#define flush_cache()                   v7_flush_kern_cache_all(); //flush_cache_all(); mb(); isb(); dsb();

#define cipher_copy_from_user(s, d, l)     (cipher_memcpy_s(s, l, d, l), 0)
#define cipher_copy_to_user(s, d, l)       (cipher_memcpy_s(s, l, d, l), 0)

#define cipher_malloc(x)                   tee_hal_malloc((x))
#define cipher_free(x)                     tee_hal_free((x))
#define Cipher_Malloc                      cipher_malloc
#define Cipher_Free                        cipher_free

#define cipher_msleep(msec) TEE_DRV_DelayUs(msec * 10) //10us

#define HI_PRINT tee_hal_printf
#define HI_ERR_CIPHER(fmt...)               HI_TEE_ERR_PRINT(HI_MODULE_ID_CIPHER, fmt)
#define HI_INFO_CIPHER(fmt...)              HI_TEE_INFO_PRINT(HI_MODULE_ID_CIPHER, fmt)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) MIN(MIN((a), (b)), (c))

#define SERURE_WRITE_TIMES         (3)

extern void PrintData(const char*pbName, HI_U8 *pbData, HI_U32 u32Size);

#if 1
#define HI_PRINT_HEX(name, str, len) PrintData(name, str, len)
#else
#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_U8 *_str; \
    _str = (HI_U8*)str; \
    HI_PRINT("[%s]:\n", name);\
    for ( _i = 0 ; _i < (len); _i++ )\
    {\
        if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
        HI_PRINT("\\x%02x", *((_str)+_i));\
    }\
    HI_PRINT("\n");\
}
#endif

/**************************** P R I V A T E ****************************/
#define CHECK_CIPHER_UUID(uuid)\
do{\
    if (Cipher_CheckUserUUID(uuid) != HI_SUCCESS)\
    {\
        return HI_FAILURE;\
    }\
}while(0)

/************************** params check api *********************/
#define INLET_PARAM_CHECK_U32_MAX(val, max) \
do{\
    if ((val) > (max))\
    {\
        HI_ERR_CIPHER("inlet param " #val " = 0x%x overflow, must less than" #max "(0x%x).\n", val, max);\
        return TEE_ERR_CIPHER_INVALID_PARA;\
    }\
}while(0)

#define INLET_PARAM_CHECK_U32_ZERO(val) \
do{\
    if (0 == (val))\
    {\
        HI_ERR_CIPHER("inlet param " #val " is zero\n", val);\
        return TEE_ERR_CIPHER_INVALID_PARA;\
    }\
}while(0)

#define INLET_PARAM_CHECK_POINT_NULL(p) \
do{\
    if (HI_NULL == (p))\
    {\
        HI_ERR_CIPHER("inlet param " #p " is null\n");\
        return TEE_ERR_CIPHER_INVALID_POINT;\
    }\
}while(0)

HI_S32 Cipher_GetUserUUID(TEE_UUID *pstUUID);
HI_S32 Cipher_CheckUserUUID(TEE_UUID *pstUUID);

HI_U32  cipher_mmu_table_addr(HI_VOID);

HI_S32 Cipher_Init(    HI_VOID);
HI_VOID Cipher_DeInit(HI_VOID);
HI_S32 DRV_CIPHER_Resume(HI_VOID);
HI_VOID DRV_CIPHER_Suspend(HI_VOID);
HI_S32 Cipher_CreateHandle(HI_HANDLE* phCipher, const HI_TEE_CIPHER_ATTS_S *pstCipherAttr);
HI_S32 Cipher_DestroyHandle(HI_HANDLE hCipher);
HI_S32 Cipher_ConfigHandle(HI_HANDLE hCipher, HI_TEE_CIPHER_CTRL_S* pstCtrl);
HI_S32 Cipher_GetHandleConfig(HI_HANDLE hCipher, HI_TEE_CIPHER_CTRL_S* pstCtrl);
HI_S32 Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 Cipher_EncryptMulti(HI_HANDLE hCipher, HI_TEE_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 Cipher_DecryptMulti(HI_HANDLE hCipher, HI_TEE_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 Cipher_Decrypt_AESCBCCTS(HI_HANDLE hCipherHandle, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength, const HI_U8 au8IV[16]);
HI_S32 Cipher_HashInit(HI_TEE_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle);
HI_S32 Cipher_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen);
HI_S32 Cipher_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash);
HI_S32 Cipher_HashHmacInit(HI_HANDLE hHashHandle, HI_U32 u32TotalLen);
HI_S32 Cipher_GetRandomNumber(HI_U32 *pu32Rnd);
HI_S32 Cipher_Rsa(CIPHER_RSA_DATA_S *pCipherRsaData);
HI_S32 Cipher_GetIVOut(HI_HANDLE hCipher, HI_U8 *pu8IVOut);
HI_S32 cipher_drv_modInit(HI_VOID);
HI_S32 Cipher_Test(HI_U32 u32Cmd, HI_VOID *pu8Param, HI_U32 u32Size);
HI_S32 DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData, HI_BOOL bIsDecrypt);
HI_S32 DRV_CIPHER_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData);
HI_S32 DRV_CIPHER_CalcRsa_ex(CIPHER_RSA_DATA_S *pCipherRsaData);
HI_S32 DRV_CIPHER_CalcRsa_SW(CIPHER_RSA_DATA_S *pCipherRsaData);
HI_S32 DRV_CIPHER_GenRsaKey_SW(CIPHER_RSA_KEY_S *pstRsaKey);
HI_S32 DRV_CIPHER_RSA_CallRMul(HI_U8*X, HI_U8* A, HI_U8* B, HI_U32 Xsize, HI_U32 Asize, HI_U32 Bsize);
HI_S32 DRV_CIPHER_CheckRsaData(HI_U8 *N, HI_U8 *E, HI_U8 *MC, HI_U32 u32Len);
HI_VOID * s_Cipher_RemapPhyAddr(HI_U32 u32PhyAddr, HI_U32 u32Size, HI_BOOL bIsSMMu, HI_BOOL bIsSec);
HI_S32 s_Cipher_UnmapPhyAddr(HI_U32 u32PhyAddr, HI_VOID* pu8SrcVirAddr, HI_BOOL bIsSMMu, HI_BOOL bIsSec);

CRYSError_t CRYS_PKCS5_PBKDF2_HMAC1(HI_TEE_CIPHER_PBKDF2_S *pstInfo, DxUint8_t *output);

HI_S32 s_Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength, HI_BOOL bIsBlock);
HI_S32 s_Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength, HI_BOOL bIsBlock);

HI_S32 Cipher_AesCbcCts_Decrypt(HI_HANDLE hCipherHandle,
                                cipher_mmz_buf_t *pstSrcMmz,
                                cipher_mmz_buf_t *pstDesMmz,
                                HI_U32 u32ByteLength);
HI_S32 Cipher_AesCbcCts_Encrypt(HI_HANDLE hCipherHandle,
                                cipher_mmz_buf_t *pstSrcMmz,
                                cipher_mmz_buf_t *pstDesMmz,
                                HI_U32 u32ByteLength);

HI_S32 TEE_CIPHER_Ioctl(HI_U32 cmd, HI_VOID *argp);
HI_S32 CIPHER_Ioctl(unsigned int cmd, HI_VOID *argp, HI_VOID *file);
HI_S32 CIPHER_MODULE_Init(HI_VOID);
#endif

