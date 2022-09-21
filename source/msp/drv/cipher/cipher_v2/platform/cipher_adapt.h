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

#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/spinlock.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/kallsyms.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/seq_file.h>
#include <linux/version.h>
#include <asm/atomic.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/traps.h>
#include <linux/miscdevice.h>
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_common.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_dev.h"
#include "hi_drv_mem.h"
#include "hi_osal.h"
#include "drv_sm2.h"
#include "drv_cipher_ioctl.h"
#include "drv_cipher_ext.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "cipher_config.h"
#include "spacc_intf.h"
#include "drv_rng.h"
#include "drv_rsa.h"
#include "drv_sm2.h"
#include "drv_cenc.h"

/**************************** M A C R O ****************************/
#ifdef  WITH_HISI_SMMU
#define CIPHER_MMU_SUPPORT
#endif

#define CIPHER_IOC_NA	    0U
#define CIPHER_IOC_W	    1U
#define CIPHER_IOC_R	    2U
#define CIPHER_IOC_RW	    3U

#define CIPHER_IOR(nr,size) 	            _IOR(HI_ID_CIPHER,(nr), sizeof(size))
#define CIPHER_IOW(nr,size)	                _IOW(HI_ID_CIPHER,(nr), sizeof(size))
#define CIPHER_IOWR(nr,size)                _IOWR(HI_ID_CIPHER,(nr),sizeof(size))

#define CIPHER_IOC_DIR(nr)		            _IOC_DIR(nr)
#define CIPHER_IOC_TYPE(nr)		            _IOC_TYPE(nr)
#define CIPHER_IOC_NR(nr)		            _IOC_NR(nr)
#define CIPHER_IOC_SIZE(nr)		            _IOC_SIZE(nr)

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



/**************************** S T D L I B ****************************/
#define cipher_ioremap_nocache(addr, size)  ioremap_nocache(addr, size)
#define cipher_iounmap(x)                   iounmap(x)

void *cipher_memset_s(void *dst, unsigned int dlen, unsigned val, unsigned int len);
int  cipher_memcmp_s(const void *a, const void *b, unsigned len);
void *cipher_memcpy_s(void *dst, unsigned dstlen, const void *src, unsigned len);

#define cipher_mutex                        struct semaphore
#define cipher_mutex_init(x)                sema_init(x, 1)
#define cipher_mutex_lock(x)                down_interruptible(x)
#define cipher_mutex_unlock(x)              up(x)

#define cipher_queue_head                   wait_queue_head_t
#define cipher_queue_init(x)                init_waitqueue_head(x)
#define cipher_queue_wait_up(x)             wake_up_interruptible(x)
#define cipher_queue_wait_timeout(head, con, time)  wait_event_interruptible_timeout(head, con, time)

#define cipher_request_irq(irq, func, name)  osal_request_irq(irq, func, IRQF_SHARED, name, name)
#define cipher_free_irq(irq, name)           osal_free_irq(irq, name, name)

#ifdef CONFIG_ARCH_LP64_MODE
#define flush_cache()                        flush_cache_all(); mb(); isb(); dsb(sy)
#else
#define flush_cache()                        flush_cache_all(); mb(); isb(); dsb()
#endif

#define cipher_copy_from_user(s, d, l)       copy_from_user(s, d, l)
#define cipher_copy_to_user(s, d, l)         copy_to_user(s, d, l)

#define cipher_malloc(x)                     HI_KMALLOC(HI_ID_CIPHER, x, GFP_KERNEL)
#define cipher_free(x)                       HI_KFREE(HI_ID_CIPHER, x)

#define cipher_msleep(msec)                  msleep(msec)

#define HI_ERR_CIPHER(fmt...)                HI_ERR_PRINT(HI_ID_CIPHER, fmt)
#define HI_INFO_CIPHER(fmt...)               HI_INFO_PRINT(HI_ID_CIPHER, fmt)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) MIN(MIN((a), (b)), (c))

void HEX2STR(char buf[2], HI_U8 val);

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

