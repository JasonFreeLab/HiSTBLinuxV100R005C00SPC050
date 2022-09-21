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

#include <hi_tee_module_id.h>
#include <hi_tee_ta_al.h>
#include "hi_type.h"
#include "hi_tee_cipher.h"
#include "tee_mpi_cipher.h"
#include "tee_cipher_ioctl.h"

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

#define UMAP_DEVNAME_CIPHER       "cipher"

/**************************** debug api ***********************/
#define HI_PRINT                uart_printf_func
#define HI_ERR_CIPHER(fmt...)   uart_printf_func(fmt)
#define HI_INFO_CIPHER(fmt...)  uart_printf_func(fmt)

#if 1
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


/**************************** system api ***********************/
#define malloc(x)                           TEE_Malloc((x), 0)
#define free(x)                             TEE_Free(x)

#define cipher_mutex                               HI_VOID *
#define cipher_mutex_init(x)                       (HI_VOID)x
#define cipher_mutex_lock(x)                       (HI_VOID)x
#define cipher_mutex_unlock(x)                     (HI_VOID)x
#define cipher_mutex_destroy(x)                    (HI_VOID)x

#define cipher_open(a, b, c)                __TEE_CIPHER_Ioctl(CMD_CIPHER_INIT, HI_NULL);
#define cipher_close(x)                     __TEE_CIPHER_Ioctl(CMD_CIPHER_DEINIT, HI_NULL);
#define cipher_ioctl(dev, cmd, argp)        __TEE_CIPHER_Ioctl(cmd, argp)

#define cipher_malloc(x) TEE_Malloc((x), 0)
#define cipher_free(x)   TEE_Free(x)

#define cipher_memcpy_s         memcpy_s
#define cipher_memset_s         memset_s
#define cipher_memcmp           TEE_MemCompare

HI_S32 __TEE_CIPHER_Ioctl(HI_U32 u32Cmd, HI_VOID *args);

#endif

