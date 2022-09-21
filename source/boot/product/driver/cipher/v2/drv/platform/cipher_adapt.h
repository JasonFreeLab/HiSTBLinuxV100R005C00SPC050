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

#ifndef HI_MINIBOOT_SUPPORT
#include <common.h>
#else
#include "delay.h"
#include "malloc.h"
#include "string.h"
#include "stdio.h"
#endif
#include "hi_common.h"
#include "malloc.h"

#include "hi_type.h"
#include "hi_debug.h"
#include "drv_cipher_ioctl.h"
#include "cipher_config.h"
#include "spacc_intf.h"
#include "drv_rng.h"
#include "drv_rsa.h"
#include "hi_error_mpi.h"

/**************************** M A C R O ****************************/
#ifdef  WITH_HISI_SMMU
#define CIPHER_MMU_SUPPORT
#endif

#define CIPHER_IOC_NA        0U
#define CIPHER_IOC_W        1U
#define CIPHER_IOC_R        2U
#define CIPHER_IOC_RW        3U

#define CIPHER_IOR(nr,size)                 _IOR(HI_ID_CIPHER,(nr), sizeof(size))
#define CIPHER_IOW(nr,size)                 _IOW(HI_ID_CIPHER,(nr), sizeof(size))
#define CIPHER_IOWR(nr,size)                _IOWR(HI_ID_CIPHER,(nr),sizeof(size))

#define CIPHER_IOC_DIR(nr)                  _IOC_DIR(nr)
#define CIPHER_IOC_TYPE(nr)                 _IOC_TYPE(nr)
#define CIPHER_IOC_NR(nr)                   _IOC_NR(nr)
#define CIPHER_IOC_SIZE(nr)                 _IOC_SIZE(nr)

#define U32_TO_POINT(addr)                  ((HI_VOID*)((HI_SIZE_T)(addr)))
#define POINT_TO_U32(addr)                  ((HI_U32)((HI_SIZE_T)(addr)))

#define HAL_CIPHER_ReadReg(addr, result)    (*(result) = *(volatile unsigned int *)(addr))
#define HAL_CIPHER_WriteReg(addr,result)    (*(volatile unsigned int *)(addr) = (result))

#define HAL_SET_BIT(src, bit)               ((src) |= (1<<bit))
#define HAL_CLEAR_BIT(src,bit)              ((src) &= ~(1<<bit))

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

#ifndef MIN
#define MIN(a,b) (a) < (b) ? (a) : (b)
#endif

/**************************** S T D L I B ****************************/
#define cipher_ioremap_nocache(addr, size)  (HI_VOID*)(addr)
#define cipher_iounmap(x)

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len);
int  cipher_memcmp_s(const void *a, const void *b, unsigned len);
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len);

#define cipher_mutex                        HI_VOID *
#define cipher_mutex_init(x)
#define cipher_mutex_lock(x)                0
#define cipher_mutex_unlock(x)

#define cipher_queue_head                   HI_VOID *
#define cipher_queue_init(x)
#define cipher_queue_wait_up(x)
#define cipher_queue_wait_timeout(head, con, time)

#define cipher_request_irq(irq, func, name)
#define cipher_free_irq(irq, name)

#define flush_cache()

#define cipher_copy_from_user(s, d, l)       (memcpy(s, d, l), 0)
#define cipher_copy_to_user(s, d, l)         (memcpy(s, d, l), 0)

#define cipher_malloc(x)                     malloc(x)
#define cipher_free(x)                       free(x)

#define cipher_msleep(msec)                  udelay(1000)

#define EXPORT_SYMBOL(x)

void HEX2STR(HI_U8 buf[2], HI_U8 val);

#if 0
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
typedef struct
{
    HI_VOID *pu8StartVirAddr;
    HI_U32 u32StartPhyAddr;
    HI_U32 u32MMZAddr;
    HI_U32 u32Size;
}cipher_mmz_buf_t;

HI_U32  cipher_mmu_table_addr(HI_VOID);
HI_S32  cipher_mmz_alloc_remap(HI_CHAR *name, cipher_mmz_buf_t *pstMmz);
HI_VOID cipher_mmz_release_unmap(cipher_mmz_buf_t *pstMmz);
HI_S32  cipher_mmz_map(cipher_mmz_buf_t *pstMmz);
HI_VOID cipher_mmz_unmap(cipher_mmz_buf_t *pstMmz);

#endif

