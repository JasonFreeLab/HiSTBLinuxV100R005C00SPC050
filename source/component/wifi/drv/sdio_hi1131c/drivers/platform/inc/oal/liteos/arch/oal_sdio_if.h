/******************************************************************************

                  版权所有 (C), 2001-2011, 海思半导体有限公司

 ******************************************************************************
  文 件 名   : oal_sdio.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2016年2月29日
  最近修改   :
  功能描述   : oal_sdio.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年2月29日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

#ifndef __OAL_LITEOS_SDIO_IF_H__
#define __OAL_LITEOS_SDIO_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef CONFIG_MMC

#include <mmc/host.h>
#include <mmc/sdio_func.h>
#include <mmc/sdio.h>
#include <mmc/card.h>
#include <gpio.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/err.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/delay.h>

#define SDIO_GET_MAX_BLOCK_COUNT(func)     (func->card->host->max_blk_num)
#define SDIO_GET_MAX_REQ_SIZE(func)        (func->card->host->max_request_size)
#define SDIO_GET_MAX_BLK_SIZE(func)        (func->card->host->max_blk_size)
#define SDIO_EN_TIMEOUT(func)        (func->en_timeout_ms)

#define SDIO_FUNC_NUM(func)             (func->func_num)


/**
 *  oal_sdio_writesb - write to a FIFO of a SDIO function
 *  @func: SDIO function to access
 *  @addr: address of (single byte) FIFO
 *  @src: buffer that contains the data to write
 *  @count: number of bytes to write
 *
 *  Writes to the specified FIFO of a given SDIO function. Return
 *  value indicates if the transfer succeeded or not.
 */
OAL_STATIC OAL_INLINE  oal_int32 oal_sdio_writesb(struct sdio_func *func, oal_uint32 addr, oal_void *src,
    int count)
{
    oal_int32 ret;
#ifdef CONFIG_HISI_SDIO_TIME_DEBUG
    oal_time_t_stru time_start;
    time_start = oal_ktime_get();
#endif

    ret = sdio_write_fifo_block(func, addr, src, count);
    
#ifdef CONFIG_HISI_SDIO_TIME_DEBUG
    if(OAL_UNLIKELY(ret))
    {
        /*If sdio transfer failed, dump the sdio info*/
        oal_uint64  trans_us;
        oal_time_t_stru time_stop = oal_ktime_get();
        trans_us = (oal_uint64)oal_ktime_to_us(oal_ktime_sub(time_stop, time_start));
        printk(KERN_WARNING"[E]oal_sdio_writesb fail=%d, time cost:%llu us,[src:%p,addr:%u,count:%d]\n", 
                            ret, trans_us, src, addr, count);
    }
#endif
    return ret;
}


/**
 *  oal_sdio_readsb - read from a FIFO on a SDIO function
 *  @func: SDIO function to access
 *  @dst: buffer to store the data
 *  @addr: address of (single byte) FIFO
 *  @count: number of bytes to read
 *
 *  Reads from the specified FIFO of a given SDIO function. Return
 *  value indicates if the transfer succeeded or not.
 */
OAL_STATIC OAL_INLINE  oal_int32 oal_sdio_readsb(struct sdio_func *func, oal_void *dst, oal_uint32 addr,
    oal_int32 count)
{
    oal_int32 ret;
#ifdef CONFIG_HISI_SDIO_TIME_DEBUG
    oal_time_t_stru time_start;
    time_start = oal_ktime_get();
#endif

    ret = sdio_read_fifo_block(func, dst, addr, count);
    
#ifdef CONFIG_HISI_SDIO_TIME_DEBUG
    if(OAL_UNLIKELY(ret))
    {
        /*If sdio transfer failed, dump the sdio info*/
        oal_uint64  trans_us;
        oal_time_t_stru time_stop = oal_ktime_get();
        trans_us = (oal_uint64)oal_ktime_to_us(oal_ktime_sub(time_stop, time_start));
        printk(KERN_WARNING"[E]sdio_readsb fail=%d, time cost:%llu us,[dst:%p,addr:%u,count:%d]\n", 
                            ret, trans_us, dst, addr, count);
    }
#endif
    return ret;
}

/**
 *  oal_sdio_readb - read a single byte from a SDIO function
 *  @func: SDIO function to access
 *  @addr: address to read
 *  @err_ret: optional status value from transfer
 *
 *  Reads a single byte from the address space of a given SDIO
 *  function. If there is a problem reading the address, 0xff
 *  is returned and @err_ret will contain the error code.
 */
OAL_STATIC OAL_INLINE oal_uint8 oal_sdio_readb(struct sdio_func *func, oal_uint32 addr, oal_int32 *err_ret)
{
    return sdio_read_byte(func, addr , err_ret);    
}

/**
 *  oal_sdio_writeb - write a single byte to a SDIO function
 *  @func: SDIO function to access
 *  @b: byte to write
 *  @addr: address to write to
 *  @err_ret: optional status value from transfer
 *
 *  Writes a single byte to the address space of a given SDIO
 *  function. @err_ret will contain the status of the actual
 *  transfer.
 */
OAL_STATIC OAL_INLINE void oal_sdio_writeb(struct sdio_func *func, oal_uint8 b, oal_uint32 addr, oal_int32 *err_ret)
{
    sdio_write_byte(func, b, addr, err_ret);
}

/**
 *  oal_sdio_readl - read a 32 bit integer from a SDIO function
 *  @func: SDIO function to access
 *  @addr: address to read
 *  @err_ret: optional status value from transfer
 *
 *  Reads a 32 bit integer from the address space of a given SDIO
 *  function. If there is a problem reading the address,
 *  0xffffffff is returned and @err_ret will contain the error
 *  code.
 */
OAL_STATIC OAL_INLINE oal_uint32 oal_sdio_readl(struct sdio_func *func, oal_uint32 addr, oal_int32 *err_ret)
{
    return sdio_readl(func , addr, err_ret);
}

/**
 *  oal_sdio_writel - write a 32 bit integer to a SDIO function
 *  @func: SDIO function to access
 *  @b: integer to write
 *  @addr: address to write to
 *  @err_ret: optional status value from transfer
 *
 *  Writes a 32 bit integer to the address space of a given SDIO
 *  function. @err_ret will contain the status of the actual
 *  transfer.
 */
OAL_STATIC OAL_INLINE oal_void oal_sdio_writel(struct sdio_func *func, oal_uint32 b, oal_uint32 addr, oal_int32 *err_ret)
{
    sdio_writel(func, b, addr, err_ret);
}

/**
 *  sdio_memcpy_fromio - read a chunk of memory from a SDIO function
 *  @func: SDIO function to access
 *  @dst: buffer to store the data
 *  @addr: address to begin reading from
 *  @count: number of bytes to read
 *
 *  Reads from the address space of a given SDIO function. Return
 *  value indicates if the transfer succeeded or not.
 */
OAL_STATIC OAL_INLINE oal_int32 oal_sdio_memcpy_fromio(struct sdio_func *func, oal_void *dst,
    oal_uint32 addr, oal_int32 count)
{
    oal_int32 ret;
#ifdef CONFIG_HISI_SDIO_TIME_DEBUG
    oal_time_t_stru time_start;
    time_start = oal_ktime_get();
#endif
    ret = sdio_memcpy_fromio(func, dst, addr, count);
#ifdef CONFIG_HISI_SDIO_TIME_DEBUG
    if(OAL_UNLIKELY(ret))
    {
        /*If sdio transfer failed, dump the sdio info*/
        oal_uint64  trans_us;
        oal_time_t_stru time_stop = oal_ktime_get();
        trans_us = (oal_uint64)oal_ktime_to_us(oal_ktime_sub(time_stop, time_start));
        printk(KERN_WARNING"[E]sdio_memcpy_fromio fail=%d, time cost:%llu us,[dst:%p,addr:%u,count:%d]\n", 
                            ret, trans_us, dst, addr, count);
    }
#endif
    return ret;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_sdio_if.h */

