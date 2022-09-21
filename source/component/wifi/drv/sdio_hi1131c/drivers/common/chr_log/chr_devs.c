/*
 * =====================================================================================
 *
 *       Filename:  chr_devs.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  09/28/2014 04:43:10 PM
 *       Revision:  none
 *       Compiler:
 *
 *         Author:  
 *   Organization:
 *
 * =====================================================================================
 */
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*
 * 1 Head Files Includeing
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/workqueue.h>
#include <asm/atomic.h>
#include <stdarg.h>     /*sprintf() etc.*/
#include <linux/slab.h> /* for kmalloc/kfree */
#include <linux/unistd.h>
#include <linux/un.h>
#include <linux/socket.h>
#include <net/sock.h>

#ifdef CONFIG_HWCONNECTIVITY
#include <linux/huawei/hw_connectivity.h>
#endif
#include "chr_devs.h"
#include "oneimage.h"
//#define CONFIG_CHR_OTHER_DEVS

/*
 * 2 Global Variable Definition
 */
static CHR_DEV   g_log_devs[];
static CHR_EVENT   g_chr_event;
static int32     g_buffer_size[];
static int32     g_log_enable = CHR_LOG_DISABLE;

static char     *g_chr_logprio_str[] = {
    "D",
    "I",
    "W",
    "E",
};
static char    *g_subsystem_str[] = {
    "kmsgplat",
    "kmsgwifi",
    "appwifi",
    "appgnss",
    "appbt",
    "appfm",
    "appnfc",
    "appir",
};
/*
 * 3 Function Definition
 */

#ifdef CHR_LOG_STAT
#define log_info_total_inc(_dev_index) do{ \
        g_log_devs[_dev_index].log_stat.total++;           \
        if (0 == g_log_devs[_dev_index].log_stat.total)    \
        { \
            g_log_devs[_dev_index].log_stat.user_dropped = 0;  \
        } \
    }while(0)

#define log_info_user_dropped_inc(_dev_index) do{ \
        g_log_devs[_dev_index].log_stat.user_dropped++;\
    }while(0)

#define log_info_user_errlog_inc(_dev_index) do{ \
        g_log_devs[_dev_index].log_stat.errlog_cnt++;\
    }while(0)

#else
#define log_info_total_inc(_dev_index)
#define log_info_user_dropped_inc(_dev_index)
#define log_info_user_errlog_inc(_dev_index)
#endif

#define PTR_BUFINFO(dev_idx)  do{ \
        CHR_DBG("Log_Info.name = %s,r_off = %d,w_off = %d\n",\
        g_log_devs[dev_idx].miscdev->name, \
        atomic_read(&g_log_devs[dev_idx].user.r_off), \
        atomic_read(&g_log_devs[dev_idx].user.w_off)); \
    }while(0)
/*
 * Prototype    : chr_buf_alloc
 * Description  : malloc memory for log buf and initialize buf_info data
 * Input        : void
 * Output       :
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static int32 chr_buf_alloc(CHR_DEV_INDEX dev_index)
{
    uint32 buf_len = 0;
    down(&g_log_devs[dev_index].user.buf_sema);
    if(0 == atomic_read(&g_log_devs[dev_index].ref_count))
    {
        buf_len = g_log_devs[dev_index].user.size;
        g_log_devs[dev_index].user.buffer = kmalloc(buf_len, GFP_KERNEL);
        if(NULL == g_log_devs[dev_index].user.buffer)
        {
            CHR_ERR("has no enough space for %s user bufer\n", g_log_devs[dev_index].miscdev->name);
            up(&g_log_devs[dev_index].user.buf_sema);
            return -ENOMEM;
        }
        CHR_DBG("--------->>>>finish init user buffer:size=%d\n", g_log_devs[dev_index].user.size);
    }
    PTR_BUFINFO(dev_index);
    atomic_inc(&g_log_devs[dev_index].ref_count);
    CHR_DBG("red_count = %d ", atomic_read(&g_log_devs[dev_index].ref_count));
    up(&g_log_devs[dev_index].user.buf_sema);

    return CHR_SUCC;
}

/*
 * Prototype    : chr_buf_free
 * Description  : free memory for log buf and clear buf_info data
 * Input        : void
 * Output       :
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static int32 chr_buf_free(CHR_DEV_INDEX dev_index)
{
    down(&g_log_devs[dev_index].user.buf_sema);
    if(atomic_dec_and_test(&g_log_devs[dev_index].ref_count))
    {
        if (NULL != g_log_devs[dev_index].user.buffer)
        {
            kfree(g_log_devs[dev_index].user.buffer);
        }
    }
    PTR_BUFINFO(dev_index);
    up(&g_log_devs[dev_index].user.buf_sema);

    return CHR_SUCC;
}

/*
 * Prototype    : logger_offset
 * Description  : give a number n, calc new index of write/read
 * Input        :
 * Output       :
 * Return Value : size_t
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
 static size_t logger_offset(CHR_DEV_INDEX dev_index, size_t n)
 {
    return n & (g_log_devs[dev_index].user.size - 1);
 }

 /*
 * Prototype    : is_between
 * Description  : is a < c < b, accounting for wrapping of a, b, and c positions.
 *                that is, if a < b, check for c between a and b
 *                and if a> b, check for c outside (not between) a and b
 *                |------- a xxxxxxx b -------|
 *                              c^
 *                |xxxxxxx b ------- a xxxxxxx|
 *                   c^                    c^
 *                return 1: c is between a and b
 *                       0: c is not between a and b
 * Input        :
 * Output       :
 * Return Value : int
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
 static inline int is_between(size_t a, size_t b, size_t c)
 {
    if (a > b)
    {
        /*is c outside of b through a?*/
        if (c <= b || a <= c)
        {
            return 1;
        }
    }
    else
    {
        /*is c between a and b?*/
        if (a <= c && c <= b)
        {
            return 1;
        }
    }

    return 0;
 }

/*
 * Prototype    : format_prefixstr
 * Description  : format log str with time and prio info
 * Input        :
 * Output       :
 * Return Value : void
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static void format_prefixstr( int8 * prefix_str, CHR_LOGPRIORITY prio)
{
    struct tm      p_tm;
    struct timeval tv;

    do_gettimeofday(&tv);
    time_to_tm(tv.tv_sec, 0, &p_tm);
    snprintf(prefix_str, CHR_MSG_MAX_LEN, "%04d.%02d.%02d:%02d.%02d.%02d:%03d]%s]", (int)(p_tm.tm_year+1900),\
                    (p_tm.tm_mon+1), p_tm.tm_mday, p_tm.tm_hour,\
                    p_tm.tm_min, p_tm.tm_sec, (int)(tv.tv_usec/1000), g_chr_logprio_str[prio]);
}

  /*
 * Prototype    : get_entry_header
 * Description  :
 * Input        :
 * Output       :
 * Return Value : struct chr_logger_entry *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
 static struct chr_logger_entry *get_entry_header(CHR_DEV_INDEX dev_index, struct chr_logger_entry *scratch, size_t r_Index)
 {
    size_t len = min(sizeof(struct chr_logger_entry), (g_log_devs[dev_index].user.size - r_Index));
    char *dest = &g_log_devs[dev_index].user.buffer[r_Index];
    if (len != sizeof(struct chr_logger_entry))
    {
        memcpy(((void *)scratch), dest, len);
        memcpy(((void *)scratch) + len, g_log_devs[dev_index].user.buffer, sizeof(struct chr_logger_entry) - len);
        return scratch;
    }

    return (struct chr_logger_entry *)dest;
 }

/*
 * Prototype    : do_write_logger_entry
 * Description  :
 * Input        :
 * Output       :
 * Return Value : void
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
 static void do_write_logger_entry(CHR_DEV_INDEX dev_index, const void *buf, size_t index, size_t count)
 {
    size_t len = 0;

    len = min(count, g_log_devs[dev_index].user.size - index);
    memcpy(&g_log_devs[dev_index].user.buffer[index], buf, len);
    if (count != len)
    {
        memcpy(g_log_devs[dev_index].user.buffer, buf + len, count - len);
    }
 }

 /*
 * Prototype    : do_write_log_from_user
 * Description  :
 * Input        :
 * Output       :
 * Return Value : ssize_t
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
 static ssize_t do_write_log_from_user(CHR_DEV_INDEX dev_index, const void __user *buf, size_t index, size_t count)
 {
    size_t len;
    uint8 __user  *puser = (uint8 __user *)buf;
    uint8 value = 0;
    if((E_FLAG_OFFSET < count))
    {
        get_user(value, (puser + E_FLAG_OFFSET));
        if ('E' == value)
        {
            log_info_user_errlog_inc(dev_index);
        }
    }
    len = min(count, g_log_devs[dev_index].user.size - index);
    if (len && copy_from_user(&g_log_devs[dev_index].user.buffer[index], buf, len))
    {
        return -CHR_EFAIL;
    }

    if (count != len)
    {
        if(copy_from_user(g_log_devs[dev_index].user.buffer, buf + len, count - len))
        {
            return -CHR_EFAIL;
        }
    }

    return count;
 }

   /*
 * Prototype    : do_read_log_to_user
 * Description  :
 * Input        :
 * Output       :
 * Return Value : ssize_t
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
 static ssize_t do_read_log_to_user(CHR_DEV_INDEX dev_index, void __user *buf, size_t index, size_t count)
 {
    size_t len;

    len = min(count, g_log_devs[dev_index].user.size - index);
    if (copy_to_user(buf, &g_log_devs[dev_index].user.buffer[index], len))
    {
        return -CHR_EFAIL;
    }

    if (count != len)
    {
        if(copy_to_user(buf + len, g_log_devs[dev_index].user.buffer, count - len))
        {
            return -CHR_EFAIL;
        }
    }

    return count;
 }

 /*
 * Prototype    : do_write_log_from_kernel
 * Description  :
 * Input        :
 * Output       :
 * Return Value : ssize_t
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
 static ssize_t do_write_log_from_kernel(CHR_DEV_INDEX dev_index, const void *buf, size_t index, size_t count)
 {
    size_t len;

    len = min(count, g_log_devs[dev_index].user.size - index);
    memcpy(&g_log_devs[dev_index].user.buffer[index], buf, len);
    if (count != len)
    {
        memcpy(g_log_devs[dev_index].user.buffer, buf + len, count - len);
    }

    return count;
 }

/*
 * Prototype    : chr_buf_write
 * Description  : copy user buf to driver's log buf
 * Input        :
 * Output       :
 * Return Value : ssize_t
 * Calls        :
 * Called By    : chr_misc_write
 *
 *   History        :
 *   1.Date         : 2014/10/15
 *     Author       : 
 *     Modification : Created function
 *
 */
static ssize_t chr_buf_write(CHR_DEV_INDEX dev_index, const int8 __user * buf, size_t count)
{
    int ret = -CHR_EFAIL;
    size_t tmp_wIndex = 0;
    size_t tmp_rIndex = 0;
    size_t new_wIndex = 0;
    struct chr_logger_entry header;

    if (unlikely(NULL == buf))
    {
        return -EFAULT;
    }
    memset(&header,0,sizeof(header));

    if (count > CHR_MSG_MAX_LEN)
    {
        /* count must not big than CHR_MSG_MAX_LEN, or count=CHR_MSG_MAX_LEN */
        count = CHR_MSG_MAX_LEN;
    }
    header.len = count;
    log_info_total_inc(dev_index);

    tmp_wIndex = atomic_read(&g_log_devs[dev_index].user.w_off);
    tmp_rIndex = atomic_read(&g_log_devs[dev_index].user.r_off);
    new_wIndex = logger_offset(dev_index, (tmp_wIndex + sizeof(struct chr_logger_entry) + count));
    if(is_between(tmp_rIndex, tmp_wIndex, new_wIndex))
    {
        CHR_DBG("buffer is full! rIndex=%d, wIndex=%d, new_wIndex=%d\n", tmp_rIndex, tmp_wIndex, new_wIndex);
        log_info_user_dropped_inc(dev_index);
        wake_up_interruptible(&g_log_devs[dev_index].read_waitqueue);
        return 0;
    }
    atomic_set(&g_log_devs[dev_index].user.w_off, new_wIndex);
    do_write_logger_entry(dev_index, &header, tmp_wIndex, sizeof(struct chr_logger_entry));
    tmp_wIndex = logger_offset(dev_index, tmp_wIndex + sizeof(struct chr_logger_entry));
    ret = do_write_log_from_user(dev_index, buf, tmp_wIndex, count);
    if (unlikely(ret < 0))
    {
        return ret;
    }

    if(new_wIndex > tmp_rIndex)
    {
        if (new_wIndex - tmp_rIndex > g_log_devs[dev_index].user.size / 10)
        {
            wake_up_interruptible(&g_log_devs[dev_index].read_waitqueue);
        }
    }
    else
    {
        if (g_log_devs[dev_index].user.size - tmp_rIndex + new_wIndex > g_log_devs[dev_index].user.size / 10)
        {
            wake_up_interruptible(&g_log_devs[dev_index].read_waitqueue);
        }
    }

    return count;
}

/*
 * Prototype    : chr_buf_read
 * Description  : copy driver's log buf to user buf
 * Input        :
 * Output       :
 * Return Value : void
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       : 
 *     Modification : Created function
 *
 */
static ssize_t chr_buf_read(CHR_DEV_INDEX dev_index, int8 __user * buf, size_t count)
{
    struct chr_logger_entry scrath;
    struct chr_logger_entry *entry;
    int64  ret         = 0;
    size_t len        = 0;
    uint64 msg_len    = 0;
    size_t msg_start  = 0;
    uint64 tmp_rIndex = 0;
    uint64 tmp_wIndex = 0;

    CHR_DBG("-----------------------enter chr_buf_read(),logd read size:count=%lu\n",count);
    PTR_BUFINFO(dev_index);
    while (len < count)
    {
        tmp_rIndex = atomic_read(&g_log_devs[dev_index].user.r_off);
        tmp_wIndex = atomic_read(&g_log_devs[dev_index].user.w_off);
        CHR_DBG("--------tmp_rIndex=%lu,tmp_wIndex=%lu\n", tmp_rIndex, tmp_wIndex);
        /*There is nothing to read, buffer is empty.*/
        if (tmp_rIndex == tmp_wIndex)
        {
            break;
        }

        entry   = get_entry_header(dev_index, &scrath, tmp_rIndex);
        msg_len = entry->len;
        if (msg_len > CHR_MSG_MAX_LEN)
        {
            CHR_WARNING("msg length wrong,reset buffer! msg_len=%lu,tmp_rIndex=%lu,tmp_wIndex=%lu\n", msg_len, tmp_rIndex, tmp_wIndex);
            atomic_set(&g_log_devs[dev_index].user.r_off, tmp_wIndex);
            break;
        }
        /*There is no enough space in __user buffer to contain next msg*/
        CHR_DBG("--------msg_len=%lu,len=%lu\n", msg_len, len);
        if (len + msg_len > count)
        {
            break;
        }

        msg_start  = logger_offset(dev_index, tmp_rIndex + sizeof(struct chr_logger_entry));
        ret        = do_read_log_to_user(dev_index, buf + len, msg_start, msg_len);
        /*copy_to _user() failed*/
        if (unlikely(ret != msg_len))
        {
            return ret;
        }

        len += ret;
        atomic_set(&g_log_devs[dev_index].user.r_off, logger_offset(dev_index, msg_start + msg_len));
        CHR_DBG("--------one msg copy to user success:msg_start=%lu,len=%lu\n", msg_start, ret);
    }

    CHR_DBG("-----------------------leave chr_buf_read(),total read count=%lu\n", len);
    PTR_BUFINFO(dev_index);

    return len;
}
/*
 * Prototype    : combine_cmd
 * Description  : combine errcatch msg
 * Input        :
 * Output       : int32
 * Return Value : msg size
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015-4-22
 *     Author       : 
 *     Modification : Created function
 *
 */

int32 combine_cmd(int8 * buf, int32 maxlen, int32 idx)
{
    return snprintf(buf, maxlen, "%s;%s;%s;", ERRCATCH_VENDOR_STR, g_subsystem_str[idx],
            ERRCATCH_CMD_STR);
}
/*
 * Prototype    : __chr_printLog
 * Description  : copy print buf to driver's log buf
 * Input        :
 * Output       :
 * Return Value : void
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
int32 __chr_printLog(CHR_LOGPRIORITY prio, CHR_DEV_INDEX dev_index, const int8 *fmt,...)
{
    int32   prefix_len;
    int32   fmt_strlen;
    size_t  tmp_wIndex = 0;
    size_t  tmp_rIndex = 0;
    size_t  new_wIndex = 0;
    va_list argptr;
    int8    tmpbuf_str[CHR_MSG_MAX_LEN];
    struct chr_logger_entry header;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        return 0;
    }

    if (NULL == g_log_devs[dev_index].user.buffer)
    {
        CHR_DBG("buffer not init, abandon logs\n");
        log_info_user_dropped_inc(dev_index);
        return 0;
    }
    memset(&header,0,sizeof(header));

    format_prefixstr(tmpbuf_str, prio);
    prefix_len = strlen(tmpbuf_str);
    va_start(argptr, fmt);
    fmt_strlen = vsnprintf(tmpbuf_str + prefix_len, CHR_MSG_MAX_LEN - prefix_len - 2, fmt, argptr);
    va_end(argptr);
    //strcat(tmpbuf_str,"\n");
    fmt_strlen = strlen(tmpbuf_str);

    if (fmt_strlen > CHR_MSG_MAX_LEN)
    {
        /* count must not big than CHR_MSG_MAX_LEN, or count=CHR_MSG_MAX_LEN */
        fmt_strlen = CHR_MSG_MAX_LEN;
    }
    header.len = fmt_strlen;
    log_info_total_inc(dev_index);

    tmp_wIndex = atomic_read(&g_log_devs[dev_index].user.w_off);
    tmp_rIndex = atomic_read(&g_log_devs[dev_index].user.r_off);
    new_wIndex = logger_offset(dev_index, (tmp_wIndex + sizeof(struct chr_logger_entry) + fmt_strlen));
    if(is_between(tmp_rIndex, tmp_wIndex, new_wIndex))
    {
        CHR_DBG("buffer is full! rIndex=%d, wIndex=%d, new_wIndex=%d \n", tmp_rIndex, tmp_wIndex, new_wIndex);
        log_info_user_dropped_inc(dev_index);
        wake_up_interruptible(&g_log_devs[dev_index].read_waitqueue);
        return 0;
    }
    atomic_set(&g_log_devs[dev_index].user.w_off, new_wIndex);

    do_write_logger_entry(dev_index, &header, tmp_wIndex, sizeof(struct chr_logger_entry));
    tmp_wIndex = logger_offset(dev_index, tmp_wIndex + sizeof(struct chr_logger_entry));
    do_write_log_from_kernel(dev_index, tmpbuf_str, tmp_wIndex, fmt_strlen);

    PTR_BUFINFO(dev_index);
    if(new_wIndex > tmp_rIndex)
    {
        if (new_wIndex - tmp_rIndex > g_log_devs[dev_index].user.size / 10)
        {
            wake_up_interruptible(&g_log_devs[dev_index].read_waitqueue);
        }
    }
    else
    {
        if (g_log_devs[dev_index].user.size - tmp_rIndex + new_wIndex > g_log_devs[dev_index].user.size / 10)
        {
            wake_up_interruptible(&g_log_devs[dev_index].read_waitqueue);
        }
    }

    if(CHR_LOG_ERROR == prio)
    {
        log_info_user_errlog_inc(dev_index);
    }
    return fmt_strlen;
}
EXPORT_SYMBOL(__chr_printLog);

/*****************************************************************************  701
 函 数 名  : __chr_exception
 功能描述  : 驱动层抛异常接口
 输入参数  : 异常错误类型
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年1月19日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32  __chr_exception(uint32 errno)
{
    struct sk_buff  *skb = NULL;

    if (CHR_LOG_DISABLE == g_log_enable)
    {
        return -EAGAIN;
    }

    if(skb_queue_len(&g_chr_event.errno_queue) > CHR_ERRNO_QUEUE_MAX_LEN)
    {
        CHR_WARNING("too many errno in queue, dispose it, errno=%x\n", errno);
        return -EAGAIN;
    }

    skb = alloc_skb(sizeof(errno), GFP_KERNEL);
    if(NULL == skb)
    {
        CHR_ERR("alloc errno skbuff failed! len=%d, errno=%x\n", (int32)sizeof(errno), errno);
        return -ENOMEM;
    }

    skb_put(skb, sizeof(errno));
    *(uint32*)skb->data = errno;
    skb_queue_tail(&g_chr_event.errno_queue, skb);
    wake_up_interruptible(&g_chr_event.errno_wait);

    return 0;
}
EXPORT_SYMBOL(__chr_exception);

/*
 * Prototype    : chr_misc_read
 * Description  : miscdevice read function
 * Input        :
 * Output       : None
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static ssize_t chr_misc_read(struct file* fp, int8 __user * buf, size_t count, CHR_DEV_INDEX dev_index)
{
    int32 ret;
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        return 0;
    }
    CHR_DBG("g_log_devs[%d].miscdev->name=%s\n", dev_index, g_log_devs[dev_index].miscdev->name);
    ret = chr_buf_read(dev_index, buf, count);
    return ret;

}

/*
 * Prototype    : chr_misc_write
 * Description  : miscdevice write function
 * Input        :
 * Output       : None
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static ssize_t chr_misc_write(struct file *fp,const int8 __user *buf, size_t count, CHR_DEV_INDEX dev_index)
{
    int32 ret;
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        return 0;
    }
    CHR_DBG("g_log_devs[%d].miscdev->name=%s\n", dev_index, g_log_devs[dev_index].miscdev->name);
    ret = chr_buf_write(dev_index, buf, count);
    return ret;
}

/*
 * Prototype    : chr_misc_open
 * Description  : miscdevice open function
 * Input        :
 * Output       : None
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static int32 chr_misc_open(struct inode *nd, struct file* fp, CHR_DEV_INDEX dev_index)
{
    int32 ret = -CHR_EFAIL;
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        return 0;
    }
    CHR_DBG("g_log_devs[%d].miscdev->name=%s\n", dev_index, g_log_devs[dev_index].miscdev->name);
    ret = chr_buf_alloc(dev_index);
    return ret;
}


static int64 chr_misc_ioctl(struct file* fp, uint32 cmd, uint64 arg, CHR_DEV_INDEX i)
{
    uint32 __user  *puser = (uint32 __user *)arg;
    struct sk_buff  *skb =NULL;
    uint32 value = 0;
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        return 0;
    }
    switch (cmd)
    {
        case CHR_CMD_SET_ERRNO:
            get_user(value, puser);
            if(skb_queue_len(&g_chr_event.errno_queue) > CHR_ERRNO_QUEUE_MAX_LEN)
            {
                CHR_WARNING("too many errno in queue, dispose it, errno=%x\n", value);
                break;
            }
            skb = alloc_skb(sizeof(value), GFP_KERNEL);
            if( NULL == skb)
            {
                CHR_ERR("alloc errno skbuff failed! len=%d, errno=%x\n", (int32)sizeof(value), value);
                return -ENOMEM;
            }
            skb_put(skb, sizeof(value));
            *(uint32*)skb->data = value;
            skb_queue_tail(&g_chr_event.errno_queue, skb);
            wake_up_interruptible(&g_chr_event.errno_wait);
            break;
        case CHR_CMD_GET_ERRNO:
            wait_event_interruptible(g_chr_event.errno_wait,  (skb_queue_len(&g_chr_event.errno_queue) > 0));
            skb = skb_dequeue(&g_chr_event.errno_queue);
            if (NULL == skb)
            {
                CHR_WARNING("skb is NULL\n");
                return -ENOMEM;
            }
            if (copy_to_user(puser, skb->data, sizeof(uint32)))
            {
                CHR_WARNING("copy_to_user err!restore it, len=%d\n", (int32)sizeof(uint32));
                skb_queue_head(&g_chr_event.errno_queue, skb);
                return -EFAULT;
            }
            skb_pull(skb, skb->len);
            kfree_skb(skb);
            break;
        default:
            CHR_WARNING("not support cmd=0x%x\n", cmd);
            break;
    }
    return 0;
}

/*
 * Prototype    : chr_misc_release
 * Description  : miscdevice release function
 * Input        :
 * Output       : None
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static int32 chr_misc_release(struct inode *nd, struct file* fp, CHR_DEV_INDEX dev_index)
{
    int32 ret = -CHR_EFAIL;
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        return 0;
    }
    ret = chr_buf_free(dev_index);

    return ret;
}

/*
 * Prototype    : chr_misc_poll
 * Description  : miscdevice poll function
 * Input        :
 * Output       : None
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */
static uint32 chr_misc_poll(struct file *fp, struct poll_table_struct * pts, CHR_DEV_INDEX dev_index)
{
    uint32 mask = 0;
    size_t tmp_rIndex = 0;
    size_t tmp_wIndex = 0;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        return 0;
    }

    PTR_BUFINFO(dev_index);
    tmp_rIndex = atomic_read(&g_log_devs[dev_index].user.r_off);
    tmp_wIndex = atomic_read(&g_log_devs[dev_index].user.w_off);
    CHR_DBG("chr_misc_poll----->r_off=%d,w_off=%d\n", tmp_rIndex, tmp_wIndex);
    poll_wait(fp,&g_log_devs[dev_index].read_waitqueue, pts);
    if(tmp_rIndex != tmp_wIndex)
    {
        mask |= (POLLIN | POLLRDNORM);
    }

    return mask;
}

/* --------------- /dev/chrKmsgWifi ops and dev define  ---------------*/
OPS_OPEN(chrKmsgWifi,   CHR_INDEX_KMSG_WIFI, nd, fp);
OPS_RELEASE(chrKmsgWifi,CHR_INDEX_KMSG_WIFI, nd, fp);
OPS_READ(chrKmsgWifi,   CHR_INDEX_KMSG_WIFI, fp, buf, count, pos);
OPS_WRITE(chrKmsgWifi,  CHR_INDEX_KMSG_WIFI, fp, buf, count, pos);
OPS_IOCTL(chrKmsgWifi,  CHR_INDEX_KMSG_WIFI, fp, cmd, arg);
OPS_POLL(chrKmsgWifi,   CHR_INDEX_KMSG_WIFI, fp, pts);
FILE_OPS(chrKmsgWifi);
MISC_DEV(chrKmsgWifi,   CHR_DEV_KMSG_WIFI);

/* --------------- /dev/chrKmsgPlat ops and dev define  ---------------*/
OPS_OPEN(chrKmsgPlat,    CHR_INDEX_KMSG_PLAT, nd, fp);
OPS_RELEASE(chrKmsgPlat, CHR_INDEX_KMSG_PLAT, nd, fp);
OPS_READ(chrKmsgPlat,    CHR_INDEX_KMSG_PLAT, fp, buf, count, pos);
OPS_WRITE(chrKmsgPlat,   CHR_INDEX_KMSG_PLAT, fp, buf, count, pos);
OPS_IOCTL(chrKmsgPlat,  CHR_INDEX_KMSG_PLAT, fp, cmd, arg);
OPS_POLL(chrKmsgPlat,    CHR_INDEX_KMSG_PLAT, fp, pts);
FILE_OPS(chrKmsgPlat);
MISC_DEV(chrKmsgPlat,    CHR_DEV_KMSG_PLAT);

/* --------------- /dev/chrAppWifi ops and dev define  ---------------*/
OPS_OPEN(chrAppWifi,    CHR_INDEX_APP_WIFI, nd, fp);
OPS_RELEASE(chrAppWifi, CHR_INDEX_APP_WIFI, nd, fp);
OPS_READ(chrAppWifi,    CHR_INDEX_APP_WIFI, fp, buf, count, pos);
OPS_WRITE(chrAppWifi,   CHR_INDEX_APP_WIFI, fp, buf, count, pos);
OPS_IOCTL(chrAppWifi,  CHR_INDEX_APP_WIFI, fp, cmd, arg);
OPS_POLL(chrAppWifi,    CHR_INDEX_APP_WIFI, fp, pts);
FILE_OPS(chrAppWifi);
MISC_DEV(chrAppWifi,    CHR_DEV_APP_WIFI);

/* --------------- /dev/chrAppBt ops and dev define ---------------*/
OPS_OPEN(chrAppBt,      CHR_INDEX_APP_BT, nd, fp);
OPS_RELEASE(chrAppBt,   CHR_INDEX_APP_BT, nd, fp);
OPS_READ(chrAppBt,      CHR_INDEX_APP_BT, fp, buf, count, pos);
OPS_WRITE(chrAppBt,     CHR_INDEX_APP_BT, fp, buf, count, pos);
OPS_IOCTL(chrAppBt,  CHR_INDEX_APP_BT, fp, cmd, arg);
OPS_POLL(chrAppBt,      CHR_INDEX_APP_BT, fp, pts);
FILE_OPS(chrAppBt);
MISC_DEV(chrAppBt,      CHR_DEV_APP_BT);

/* --------------- /dev/chrAppGnss ops and dev define ---------------*/
OPS_OPEN(chrAppGnss,    CHR_INDEX_APP_GNSS, nd, fp);
OPS_RELEASE(chrAppGnss, CHR_INDEX_APP_GNSS, nd, fp);
OPS_READ(chrAppGnss,    CHR_INDEX_APP_GNSS, fp, buf, count, pos);
OPS_WRITE(chrAppGnss,   CHR_INDEX_APP_GNSS, fp, buf, count, pos);
OPS_IOCTL(chrAppGnss,  CHR_INDEX_APP_GNSS, fp, cmd, arg);
OPS_POLL(chrAppGnss,    CHR_INDEX_APP_GNSS, fp, pts);
FILE_OPS(chrAppGnss);
MISC_DEV(chrAppGnss,    CHR_DEV_APP_GNSS);
#ifdef CONFIG_CHR_OTHER_DEVS
/*---------------- /dev/chrAppFm ops and dev define -----------------*/
OPS_OPEN(chrAppFm,    CHR_INDEX_APP_FM, nd, fp);
OPS_RELEASE(chrAppFm, CHR_INDEX_APP_FM, nd, fp);
OPS_READ(chrAppFm,    CHR_INDEX_APP_FM, fp, buf, count, pos);
OPS_WRITE(chrAppFm,   CHR_INDEX_APP_FM, fp, buf, count, pos);
OPS_IOCTL(chrAppFm,  CHR_INDEX_APP_FM, fp, cmd, arg);
OPS_POLL(chrAppFm,    CHR_INDEX_APP_FM, fp, pts);
FILE_OPS(chrAppFm);
MISC_DEV(chrAppFm, CHR_DEV_APP_FM);
/*---------------- /dev/chrAppNfc ops and dev define ----------------*/
OPS_OPEN(chrAppNfc,    CHR_INDEX_APP_NFC, nd, fp);
OPS_RELEASE(chrAppNfc, CHR_INDEX_APP_NFC, nd, fp);
OPS_READ(chrAppNfc,    CHR_INDEX_APP_NFC, fp, buf, count, pos);
OPS_WRITE(chrAppNfc,   CHR_INDEX_APP_NFC, fp, buf, count, pos);
OPS_IOCTL(chrAppNfc,  CHR_INDEX_APP_NFC, fp, cmd, arg);
OPS_POLL(chrAppNfc,    CHR_INDEX_APP_NFC, fp, pts);
FILE_OPS(chrAppNfc);
MISC_DEV(chrAppNfc, CHR_DEV_APP_NFC);
/*---------------- /dev/chrAppIr ops and dev define -----------------*/
OPS_OPEN(chrAppIr,    CHR_INDEX_APP_IR, nd, fp);
OPS_RELEASE(chrAppIr, CHR_INDEX_APP_IR, nd, fp);
OPS_READ(chrAppIr,    CHR_INDEX_APP_IR, fp, buf, count, pos);
OPS_WRITE(chrAppIr,   CHR_INDEX_APP_IR, fp, buf, count, pos);
OPS_IOCTL(chrAppIr,  CHR_INDEX_APP_IR, fp, cmd, arg);
OPS_POLL(chrAppIr,    CHR_INDEX_APP_IR, fp, pts);
FILE_OPS(chrAppIr);
MISC_DEV(chrAppIr, CHR_DEV_APP_IR);
#endif

static CHR_DEV g_log_devs[] = {
    { .dev_index = CHR_INDEX_KMSG_PLAT,  .miscdev = &chrKmsgPlat_dev,},
    { .dev_index = CHR_INDEX_KMSG_WIFI, .miscdev = &chrKmsgWifi_dev,},
    { .dev_index = CHR_INDEX_APP_WIFI,  .miscdev = &chrAppWifi_dev,},
    { .dev_index = CHR_INDEX_APP_GNSS,  .miscdev = &chrAppGnss_dev,},
    { .dev_index = CHR_INDEX_APP_BT,    .miscdev = &chrAppBt_dev,},
    #ifdef CONFIG_CHR_OTHER_DEVS
    { .dev_index = CHR_INDEX_APP_FM,    .miscdev = &chrAppFm_dev,},
    { .dev_index = CHR_INDEX_APP_NFC,   .miscdev = &chrAppNfc_dev,},
    { .dev_index = CHR_INDEX_APP_IR,   .miscdev = &chrAppIr_dev,},
    #endif
};

static int32 g_buffer_size[] = {
    __USER_BUFF_LEN_PLAT,
    __USER_BUFF_LEN_WIFI_KMSG,
    __USER_BUFF_LEN_WIFI_APP,
    __USER_BUFF_LEN_GNSS,
    __USER_BUFF_LEN_BT,
    __USER_BUFF_LEN_FM,
    __USER_BUFF_LEN_NFC,
    __USER_BUFF_LEN_IR,
};

ssize_t show_chr_log_stat_info(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    int32 i         = 0;
    int32 devs      = 0;
    int32 len       = 0;
    int32 str_cnt   = 0;

#ifdef CHR_LOG_STAT
    devs = sizeof(g_log_devs) / sizeof(CHR_DEV);

    if (NULL == buf)
    {
        CHR_ERR("buf is NULL\n");
        return -CHR_EFAIL;
    }

    for (i = 0; i < devs; i++)
    {
        len = sprintf(buf + str_cnt, "name:%s totol:%d user_drop:%d errlog:%d\n", \
        g_log_devs[i].miscdev->name, g_log_devs[i].log_stat.total, \
        g_log_devs[i].log_stat.user_dropped, g_log_devs[i].log_stat.errlog_cnt);
        str_cnt += len;
    }
#endif

    return str_cnt;
}

/* show curr chr log switch enable or disable */
ssize_t show_chr_log_switch(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    if (NULL == buf)
    {
        CHR_ERR("buf is NULL\n");
        return -CHR_EFAIL;
    }

    CHR_INFO("show g_log_enable=%d\n", g_log_enable);

    return sprintf(buf, "1:enable other:disable value=%d\n", g_log_enable);
}

/*  store curr chr log switch enable or disable */
ssize_t store_chr_log_switch(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 log_switch = 0;

    if (NULL == buf)
    {
        CHR_ERR("buf is NULL\n");
        return -CHR_EFAIL;
    }

    if ((sscanf(buf, "%d", &log_switch) != 1))   //vsscanf
    {
        CHR_INFO("set CHR_LOG's switch failed!\n");
        return -CHR_EFAIL;
    }

    if (CHR_LOG_ENABLE == log_switch)
    {
        g_log_enable = log_switch;
    }
    else if (CHR_LOG_DISABLE == log_switch)
    {
        g_log_enable = log_switch;
    }

    CHR_INFO("store g_log_enable=%d\n", g_log_enable);

    return count;
}

/*
 * Prototype    : miscdev_init
 * Description  : initialize struct data and register miscdev
 * Input        :
 * Output       : None
 * Return Value :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2014/9/28
 *     Author       :
 *     Modification : Created function
 *
 */

static int32 chr_miscdev_init(CHR_DEV_INDEX dev_index)
{
    int32 ret = 0;

    sema_init(&g_log_devs[dev_index].user.buf_sema, 1);
    init_waitqueue_head(&g_log_devs[dev_index].read_waitqueue);
    g_log_devs[dev_index].user.size = g_buffer_size[dev_index];
    atomic_set(&g_log_devs[dev_index].user.r_off, 0);
    atomic_set(&g_log_devs[dev_index].user.w_off, 0);
    atomic_set(&g_log_devs[dev_index].ref_count, 0);

    if (CHR_INDEX_KMSG_PLAT == dev_index || CHR_INDEX_KMSG_WIFI == dev_index)
    {
        ret = chr_buf_alloc(dev_index);
        if (CHR_SUCC != ret)
        {
            CHR_ERR("alloc buf memory err\n");
            return ret;
        }
    }

#ifdef CHR_LOG_STAT
    g_log_devs[dev_index].log_stat.total        = 0;
    g_log_devs[dev_index].log_stat.user_dropped = 0;
    g_log_devs[dev_index].log_stat.errlog_cnt   = 0;
#endif

    ret = misc_register(g_log_devs[dev_index].miscdev);
    return ret;
}


static int32 chr_miscdevs_register(void)
{
    int32 i, ret = -CHR_EFAIL;
    int32 devs;

    init_waitqueue_head(&g_chr_event.errno_wait);
    skb_queue_head_init(&g_chr_event.errno_queue);

    devs = sizeof(g_log_devs) / sizeof(CHR_DEV);
    for (i = 0; i < devs; i++)
    {
        ret = chr_miscdev_init(i);
        if (0 != ret)
        {
            for (; i >= 0; i--)
            {
                if(NULL != g_log_devs[i].user.buffer)
                {
                    kfree(g_log_devs[i].user.buffer);
                }
                misc_deregister(g_log_devs[i].miscdev);
            }
            CHR_ERR("chr devs register error!!!\n");
            g_log_enable = CHR_LOG_DISABLE;
            return ret;
        }
        CHR_INFO("chr dev %s register ok\n", g_log_devs[i].miscdev->name);
    }
    g_log_enable = CHR_LOG_ENABLE;
    return ret;
}

static void chr_miscdevs_unregister(void)
{
    int32 i;
    int32 devs = sizeof(g_log_devs) / sizeof(CHR_DEV);

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_INFO("chr log is diabled\n");
        return;
    }
    for(i = 0; i < devs; i++)
    {
        if(NULL != g_log_devs[i].user.buffer)
        {
            kfree(g_log_devs[i].user.buffer);
        }
        misc_deregister(g_log_devs[i].miscdev);
    }
    g_log_enable = CHR_LOG_DISABLE;

    CHR_INFO("chr dev usregister \n");
}

int32 chr_miscdevs_init(void)
{
    int32 ret = -CHR_EFAIL;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (!is_my_chip()) {
        CHR_INFO("cfg chr log chip type is not match, skip driver init");
        g_log_enable = CHR_LOG_DISABLE;
        return -EINVAL;
    } else {
        CHR_INFO("cfg chr log is matched with hi110x, continue");
    }
#endif
    ret = chr_miscdevs_register();
    return ret;
}
void chr_miscdevs_exit(void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (!is_my_chip()) {
        CHR_INFO("cfg chr log chip type is not match, skip driver init");
        return;
    } else {
        CHR_INFO("cfg chr log is matched with hi110x, continue");
    }
#endif
    chr_miscdevs_unregister();
}
//module_init(chr_miscdevs_init);
//module_exit(chr_miscdevs_exit);
MODULE_AUTHOR("Hisilicon platform Driver Group");
MODULE_DESCRIPTION("hi110x chr log driver");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

