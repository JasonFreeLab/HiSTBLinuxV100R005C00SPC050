/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cipher_osal.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#ifndef __CIPHER_OSAL_H__
#define __CIPHER_OSAL_H__

#ifndef HI_MINIBOOT_SUPPORT
#include <common.h>
#else
#include "string.h"
#include "stdio.h"
#endif
#include "hi_common.h"
#include "malloc.h"

#include "hi_mpi_cipher.h"
#include "code_error.h"
#include "rsa_private.h"
#include "rsa_public.h"
#include "ree_mpi_cipher.h"
#include "drv_cipher_ioctl.h"

//#define SHA3_SUPPORT

#define COPRO_BASE     0xF9A34000
#define TRNG_BASE      0xF8ABC200

//#define SIC_RSA_LIB_ENABLE

#define HASH_BLOCK_SIZE                  (128)
#define HASH_RESULT_MAX_LEN              (64)
#define HASH_RESULT_MAX_LEN_IN_WORD      (16)
#define HI_INVALID_HANDLE                (0xffffffff)

#define CPU_TO_BE16(v) (((v)<< 8) | ((v)>>8))
#define CPU_TO_BE32(v) ((((HI_U32)(v))>>24) | ((((HI_U32)(v))>>8)&0xff00) | ((((HI_U32)(v))<<8)&0xff0000) | (((HI_U32)(v))<<24))
#define CPU_TO_BE64(x) ((HI_U64)(                         \
        (((HI_U64)(x) & (HI_U64)0x00000000000000ffULL) << 56) |   \
        (((HI_U64)(x) & (HI_U64)0x000000000000ff00ULL) << 40) |   \
        (((HI_U64)(x) & (HI_U64)0x0000000000ff0000ULL) << 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00000000ff000000ULL) <<  8) |   \
        (((HI_U64)(x) & (HI_U64)0x000000ff00000000ULL) >>  8) |   \
        (((HI_U64)(x) & (HI_U64)0x0000ff0000000000ULL) >> 24) |   \
        (((HI_U64)(x) & (HI_U64)0x00ff000000000000ULL) >> 40) |   \
        (((HI_U64)(x) & (HI_U64)0xff00000000000000ULL) >> 56)))

#define U32_TO_POINT(addr)  ((HI_VOID*)((HI_SIZE_T)(addr)))
#define POINT_TO_U32(addr)  ((HI_U32)((HI_SIZE_T)(addr)))

/**************************** debug api ***********************/
#if 1
void PrintData(const char*pbName, HI_U8 *pbData, HI_U32 u32Size);

#define HI_PRINT_HEX(name, str, len) PrintData(name, str, len)
#else
#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_U32 _val; \
    HI_U8 *_str = (HI_U8*)str;\
	if (_str != HI_NULL) \
    {\
		HI_PRINT("[%s]:\n", name);\
		for ( _i = 0 ; _i < (len); _i+=4 )\
		{\
			_val  = *((_str)+_i+3);\
			_val |= *((_str)+_i+2) << 8;\
			_val |= *((_str)+_i+1) << 16;\
			_val |= *((_str)+_i+0) << 24;\
			HI_PRINT("%x\n", _val);\
		}\
		HI_PRINT("\n");\
	}\
}
#endif

/************************** params check api *********************/
#define INLET_PARAM_CHECK_U32_MAX(val, max) \
do{\
    if ((val) > (max))\
    {\
        HI_ERR_CIPHER("inlet param " #val " = 0x%x overflow, must less than" #max "(0x%x).\n", val, max);\
        return HI_ERR_CIPHER_INVALID_PARA;\
    }\
}while(0)

#define INLET_PARAM_CHECK_U32_ZERO(val) \
do{\
    if ((val) == 0)\
    {\
        HI_ERR_CIPHER("inlet param " #val " is zero\n");\
        return HI_ERR_CIPHER_INVALID_PARA;\
    }\
}while(0)

#define INLET_PARAM_CHECK_POINT_NULL(p) \
do{\
    if ((p) == HI_NULL)\
    {\
        HI_ERR_CIPHER("inlet param " #p " is null\n");\
        return HI_ERR_CIPHER_INVALID_POINT;\
    }\
}while(0)

#define cipher_mutex                             HI_VOID *
#define cipher_mutex_init(x)
#define cipher_mutex_lock(x)
#define cipher_mutex_unlock(x)
#define cipher_mutex_destroy(x)

#define cipher_open(a, b, c)			(CIPHER_MODULE_Init(), 1)
#define cipher_close(x)				(CIPHER_MODULE_Exit(), 0)
#define cipher_ioctl(dev, cmd, argp)		CIPHER_Ioctl(NULL, NULL, cmd, argp)

#define cipher_malloc(x) 			malloc(x)
#define cipher_free(x)   			free(x)

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len);
int   cipher_memcmp_s(const void *a, const void *b, unsigned len);
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len);


extern HI_S32 g_CipherDevFd;

typedef struct
{
    HI_VOID *pu8StartVirAddr;
    HI_SIZE_T szStartPhyAddr;
    HI_U32 u32Size;
}cipher_mmz_buf_t;

HI_S32 CIPHER_Maloc(cipher_mmz_buf_t *pstMem, HI_CHAR *name);
HI_S32 CIPHER_Free(cipher_mmz_buf_t *pstMem);

#endif

