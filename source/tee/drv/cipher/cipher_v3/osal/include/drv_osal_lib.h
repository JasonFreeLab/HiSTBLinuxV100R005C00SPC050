/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_osal_lib.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_OSAL_LIB_H__
#define __DRV_OSAL_LIB_H__

#define HI_LOG_D_MODULE_ID     HI_MODULE_ID_CIPHER
#define LOG_D_FUNCTRACE        (0)
#define LOG_D_UNFTRACE         (0)

#include <hi_tee_module_id.h>
#include <tee_os_hal.h>
#include <hi_tee_errcode.h>
#include "sre_pm.h"
#include "uuid_chip.h"
#include "drv_tee_mem.h"
#include "hi_tee_cipher.h"
#include "tee_drv_cipher_kapi.h"
#include "drv_osal_chip.h"
#include "tee_drv_common.h"
#include "hi_tee_log.h"

#define HI_LOG_CHECK_PARAM     HI_TEE_CHECK_PARAM
#define HI_LOG_CHECK_INITED    HI_TEE_CHECK_INITED

#define HI_PRINT            tee_hal_printf

/*! \return uuid */
#define CHECK_OWNER(local) \
    do { \
        crypto_owner owner;\
        crypto_get_owner(&owner); \
        if (0 != memcmp(&owner, local, sizeof(owner))) { \
            HI_LOG_ERROR("return user uuid failed\n"); \
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_ILLEGAL_UUID);\
            return HI_ERR_CIPHER_ILLEGAL_UUID; \
        } \
    } while (0)

/*! \max length module name */
#define CRYPTO_MODULE_NAME_LEN          (16)

/*the max cipher hard channel count*/
#define CRYPTO_HARD_CHANNEL_MAX         (0x08)

/*! \struct channel
 * the context of hardware channel.
*/
typedef struct
{
    /*the state of instance, open or closed.*/
    u32 open;

    /*the context of channel, which is defined by specific module*/
    void *ctx;
}channel_context;

/*! \struct of crypto_mem*/
typedef struct
{
    compat_addr dma_addr;    /*!<  dam addr, may be mmz or smmu */
    compat_addr mmz_addr;    /*!<  mmz addr, sometimes the smmu must maped from mmz */
    void *dma_virt;         /*!<  cpu virtual addr maped from dam addr */
    u32 dma_size;           /*!<  dma memory size */
    void *user_buf;         /*!<  buffer of user */
}crypto_mem;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/*! \****************************** API Declaration *****************************/
/*! \addtogroup    osal lib */
/** @{ */  /** <!--[osal]*/

/**
\brief  init dma memory.
*/
void crypto_mem_init(void);

/**
\brief  deinit dma memory.
*/
void crypto_mem_deinit(void);

/**
\brief  allocate and map a dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] size The size of mem.
\param[in] name The name of mem.
\return         HI_SUCCESS if successful, or HI_BASE_ERR_MALLOC_FAILED.
*/
s32 crypto_mem_create(crypto_mem *mem, u32 type, const char *name, u32 size);

/**
\brief  destory and unmap a dma memory.
\param[in] mem  The struct of crypto_mem.
\return         0 if successful, or HI_BASE_ERR_UNMAP_FAILED.
*/
s32 crypto_mem_destory(crypto_mem *mem);

/**
\brief  map a dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] dma_ddr The address of dma mem.
\param[in] dma_size The size of dma mem.
\return         HI_SUCCESS if successful, or HI_BASE_ERR_MAP_FAILED.
*/
s32 crypto_mem_open(crypto_mem *mem, compat_addr dma_ddr, u32 dma_size);

/**
\brief  unmap a dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] dma_ddr The address of dma mem.
\return         HI_SUCCESS if successful, or HI_BASE_ERR_UNMAP_FAILED.
*/
s32 crypto_mem_close(crypto_mem *mem);

/**
\brief  attach a cpu buffer with dma memory.
\param[in] mem  The struct of crypto_mem.
\param[in] buffer The user's buffer.
\return         HI_SUCCESS if successful, or HI_FAILURE.
*/
s32 crypto_mem_attach(crypto_mem *mem, void *buffer);

/**
\brief  flush dma memory,
*\param[in] mem The struct of crypto_mem.
*\param[in] dma2user 1-data from dma to user, 0-data from user to dma.
*\param[in] offset The offset of data to be flush.
*\param[in] data_size The size of data to be flush.
\return         HI_SUCCESS if successful, or HI_FAILURE.
*/
s32 crypto_mem_flush(crypto_mem *mem, u32 dma2user, u32 offset, u32 data_size);

/**
\brief  get dma memory physical address
*\param[in] mem The struct of crypto_mem.
\return         dma_addr if successful, or zero.
*/
s32 crypto_mem_phys(crypto_mem *mem, compat_addr *dma_addr);

/**
\brief  get dma memory virtual address
*\param[in] mem The struct of crypto_mem.
\return         dma_addr if successful, or zero.
*/
void * crypto_mem_virt(crypto_mem *mem);

/**
\brief  print the map info of local dma
*\param[in] mem The struct of crypto_mem.
\return         dma_addr if successful, or zero.
*/
void crypto_mem_map_info(void);

/**
\brief  check whether cpu is secure or not.
\retval secure cpu, HI_TRUE is returned otherwise HI_FALSE is returned.
*/
u32 crypto_is_sec_cpu(void);

/**
\brief  map the physics addr to cpu within the base table, contains the base addr and crg addr.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.*/
s32 module_addr_map(void);

/**
\brief  unmap the physics addr to cpu within the base table, contains the base addr and crg addr.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.*/
s32 module_addr_unmap(void);

/**
\brief  enable a module, open clock  and remove reset signal.
\param[in]  id The module id.
\retval    NA */
void module_enable(module_id id);

/**
\brief  disable a module, close clock and set reset signal.
\param[in] id The module id.
\retval    NA */
void module_disable(module_id id);

/**
\brief  get attribute of module.
\param[in]  id The module id.
\param[out] int_valid enable interrupt or not.
\param[out] int_num interrupt number of module.
\param[out] name name of module.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.*/
void module_get_attr(module_id id, u32 *int_valid, u32 *int_num, const char **name);

/**
\brief  get base address of module.
\param[in]  id The module id.
\param[out] phyaddr module base addr.
\param[out] address cpu address of module register.
*/
void module_get_base_address(module_id id, u32 *phyaddr, void **address);

/**
\brief  read a register.
\param[in]  id The module id.
\param[in]  offset The module id.
\retval    the value of register*/
u32 module_reg_read(module_id id, u32 offset);

/**
\brief  hex to string.
\param[in]  buf The string buffer.
\param[in]  val The value of hex.
\retval    NA */
void HEX2STR(char buf[2], HI_U8 val);

/**
\brief  print a string.
\param[in]  name The name of string.
\param[in]  string The string buffer.
\param[in]  size The size of string.
\retval    the value of register*/
void print_string(const char*name, u8 *string, u32 size);

/**
\brief  write a register.
\param[in]  id The module id.
\retval    NA */
void module_reg_write(module_id id, u32 offset, u32 val);

/* cipher module read and write a register */
#define SYMC_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_SYMC, offset)
#define SYMC_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_SYMC, offset, val)

/* hash module read and write a register */
#define HASH_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_HASH, offset)
#define HASH_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_HASH, offset, val)

/* rsa module read and write a register */
#define IFEP_RSA_READ(offset)       module_reg_read(CRYPTO_MODULE_ID_IFEP_RSA, offset)
#define IFEP_RSA_WRITE(offset, val) module_reg_write(CRYPTO_MODULE_ID_IFEP_RSA, offset, val)

/* trng module read and write a register */
#define TRNG_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_TRNG, offset)
#define TRNG_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_TRNG, offset, val)

/* sm2 module read and write a register */
#define SM2_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_SM2, offset)
#define SM2_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_SM2, offset, val)

/* smmu module read and write a register */
#define SMMU_READ(offset)         module_reg_read(CRYPTO_MODULE_ID_SMMU, offset)
#define SMMU_WRITE(offset, val)   module_reg_write(CRYPTO_MODULE_ID_SMMU, offset, val)

/**
\brief  Initialize the channel list.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\param[in]  ctx_size The size of context.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 crypto_channel_init(channel_context *ctx, u32 num, u32 ctx_size);

/**
\brief  Deinitialize the channel list.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 crypto_channel_deinit(channel_context *ctx, u32 num);

/**
\brief  allocate a channel.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\param[in]  mask Mask whick channel allowed be alloc, max is 32.
\param[out] id The id of channel.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 crypto_channel_alloc(channel_context *ctx, u32 num, u32 mask, u32 *id);

/**
\brief  free a channel.
\param[in]  ctx The context of channel.
\param[in]  num The channel numbers, max is 32.
\param[in] id The id of channel.
\retval    on success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
void crypto_channel_free(channel_context *ctx, u32 num, u32 id);

/**
\brief  get the private data of hard channel.
\param[in] ctx The context of channel.
\param[in] num The channel numbers, max is 32.
\param[in] id The id of channel.
\retval    on success, the address of context is returned.  On error, NULL is returned..
*/
void *crypto_channel_get_context(channel_context *ctx, u32 num, u32 id);

s32 crypto_copy_from_user(void *to, const void *from, unsigned long n);
s32 crypto_copy_to_user(void  *to, const void *from, unsigned long n);
u32 get_rand(void);

#define crypto_ioremap_nocache(addr, size)  (void*)addr
#define crypto_iounmap(addr, size)

#define crypto_read(addr)         (*(volatile unsigned int *)(tee_hal_phys_to_virt(((long unsigned int)(addr)))))
#define crypto_write(addr, val)   (*(volatile unsigned int *)(tee_hal_phys_to_virt(((long unsigned int)(addr)))) = (val))

#define crypto_msleep(msec)         tee_hal_msleep(msec)
#define crypto_udelay(msec)         tee_hal_udelay(msec)

void *crypto_calloc(u32 n, u32 size);
#define crypto_malloc(x)            (0 < (x) ? tee_hal_malloc(x) : HI_NULL)
#define crypto_free(x)              {if(HI_NULL != (x) ) tee_hal_free(x);}

#define crypto_request_irq(irq, func, name) tee_hal_request_irq(irq, (void *)func, 0, (void*)name)
#define crypto_free_irq(irq, name)          tee_hal_delete_irq(irq)

typedef struct tee_hal_mutex                      crypto_mutex;
#define crypto_mutex_init(x)                      tee_hal_mutex_init("crypto", x)
#define crypto_mutex_lock(x)                      (tee_hal_mutex_lock(x), 0)
#define crypto_mutex_unlock(x)                    tee_hal_mutex_unlock(x)
#define crypto_mutex_destroy(x)                   tee_hal_mutex_destroy(x)
#define DEFINE_SEMAPHORE(x)                       static struct tee_hal_mutex x

#define irqreturn_t                                s32
#define crypto_queue_head                          void *
#define crypto_queue_init(x)                       (void)0
#define crypto_queue_wait_up(x)                    (void)0
#define crypto_queue_wait_timeout(head, con, time) (con)

extern void v7_flush_kern_cache_all(void);
#define flush_cache()                             tee_hal_dcache_flush_all();

#define crypto_owner                              TEE_UUID
#define crypto_get_owner(x)                       tee_hal_current_uuid(x)

void smmu_get_table_addr(u64 *rdaddr, u64 *wraddr, u64 *table);

#define IRQ_HANDLED                               0
#define IRQ_NONE                                  1

#endif  /* End of #ifndef __HI_DRV_CIPHER_H__*/
