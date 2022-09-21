/*
 *
 * Copyright (C), 2015-2025, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : oal_softwdt.c
 * Version       : Initial Draft
 * Author        : 
 * Created       : 2015/09/30
 * hisi connectity dft c file
 */
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define  HISI_LOG_TAG "[DFT]"
#include "oal_util.h"
#include "oal_net.h"

#include "oal_schedule.h"
#include "oal_workqueue.h"

#include "oal_kernel_file.h"

#ifdef _PRE_OAL_FEATURE_KEY_PROCESS_TRACE
OAL_DEFINE_SPINLOCK(g_dft_head_lock);
OAL_LIST_CREATE_HEAD(g_dft_head);
oal_module_symbol(g_dft_head_lock);
oal_module_symbol(g_dft_head);

#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
#define KERN_PRINT  (BIT0)
#define BUFF_PRINT  (BIT1)

OAL_STATIC oal_uint32 dft_print_mask = (KERN_PRINT | BUFF_PRINT);
module_param(dft_print_mask, uint, S_IRUGO | S_IWUSR);
OAL_STATIC oal_int32 oal_dft_dump_key_info(char* buf,oal_int32 key_type, oal_uint32 print_tag)
{
    oal_int32 ret = 0;
    oal_ulong flags;

    oal_int32 last_time_flag;

    struct timeval  first_tv;
    struct timeval  last_tv;
    struct rtc_time first_tm;
    struct rtc_time last_tm;

    oal_list_entry_stru *pst_pos;
    oal_dft_trace_item  *pst_dft_item;

    oal_spin_lock_irq_save(&g_dft_head_lock, &flags);
    OAL_LIST_SEARCH_FOR_EACH(pst_pos, &g_dft_head)
    {
        oal_spin_unlock_irq_restore(&g_dft_head_lock, &flags);
        last_time_flag = 0;
        pst_dft_item = OAL_LIST_GET_ENTRY(pst_pos,oal_dft_trace_item,list);

        if(key_type != pst_dft_item->dft_type)
        {
            oal_spin_lock_irq_save(&g_dft_head_lock, &flags);
            continue;
        }

        oal_memset(&first_tm,0,OAL_SIZEOF(first_tm));
        oal_memcopy(&first_tv,&pst_dft_item->first_timestamp, OAL_SIZEOF(first_tv));
        first_tv.tv_sec -= sys_tz.tz_minuteswest * 60;
        oal_rtc_time_to_tm(first_tv.tv_sec, &first_tm);

        oal_memset(&last_tm,0,OAL_SIZEOF(last_tm));
        oal_memcopy(&last_tv,&pst_dft_item->last_timestamp, OAL_SIZEOF(last_tv));
        if(last_tv.tv_sec)
        {
            last_tv.tv_sec -= sys_tz.tz_minuteswest * 60;
            oal_rtc_time_to_tm(last_tv.tv_sec, &last_tm);
            last_time_flag = 1;
        }

        if(!last_time_flag)
        {
            if(print_tag & KERN_PRINT)
                printk(KERN_DEBUG"%s,1st at %02d:%02d:%02d:%02d:%02d,total:%u\n",
                        pst_dft_item->name,
                        first_tm.tm_mon+1,
                        first_tm.tm_mday,
                        first_tm.tm_hour, first_tm.tm_min, first_tm.tm_sec,
                        pst_dft_item->trace_count);
            if(print_tag & BUFF_PRINT)
            {
                if (NULL != buf)
                {
                    ret +=  snprintf(buf + ret , PAGE_SIZE - ret, "%s,1st at %02d:%02d:%02d:%02d:%02d,total:%u\n",
                            pst_dft_item->name,
                            first_tm.tm_mon+1,
                            first_tm.tm_mday,
                            first_tm.tm_hour, first_tm.tm_min, first_tm.tm_sec,
                            pst_dft_item->trace_count);
                }
            }
        }
        else
        {
            if(print_tag & KERN_PRINT)
                printk(KERN_DEBUG"%s,1st at %02d:%02d:%02d:%02d:%02d,last at %02d:%02d:%02d:%02d:%02d,total:%u\n",
                        pst_dft_item->name,
                        first_tm.tm_mon+1,
                        first_tm.tm_mday,
                        first_tm.tm_hour, first_tm.tm_min, first_tm.tm_sec,
                        last_tm.tm_mon+1,
                        last_tm.tm_mday,
                        last_tm.tm_hour, last_tm.tm_min, last_tm.tm_sec,
                        pst_dft_item->trace_count);
            if(print_tag & BUFF_PRINT)
            {
                if (NULL != buf)
                {
                    ret +=  snprintf(buf + ret , PAGE_SIZE - ret, "%s,1st at %02d:%02d:%02d:%02d:%02d,last at %02d:%02d:%02d:%02d:%02d,total:%u\n",
                            pst_dft_item->name,
                            first_tm.tm_mon+1,
                            first_tm.tm_mday,
                            first_tm.tm_hour, first_tm.tm_min, first_tm.tm_sec,
                            last_tm.tm_mon+1,
                            last_tm.tm_mday,
                            last_tm.tm_hour, last_tm.tm_min, last_tm.tm_sec,
                            pst_dft_item->trace_count);
                }
            }
        }

        oal_spin_lock_irq_save(&g_dft_head_lock, &flags);
    }
    oal_spin_unlock_irq_restore(&g_dft_head_lock, &flags);

    return ret;
}

oal_void oal_dft_print_error_key_info(oal_void)
{
    oal_int32 i;
    printk(KERN_WARNING"[E]dump error key_info:\n");
    for(i = (OAL_DFT_TRACE_BUTT - 1); i >= OAL_DFT_TRACE_FAIL ; i--)
    {
        oal_dft_dump_key_info(NULL, i, (KERN_PRINT));
    }
}
oal_module_symbol(oal_dft_print_error_key_info);

oal_void oal_dft_print_all_key_info(oal_void)
{
    oal_int32 i;
    for(i = 0; i < OAL_DFT_TRACE_BUTT ; i++)
    {
        oal_dft_dump_key_info(NULL, i, (KERN_PRINT));
    }
}
oal_module_symbol(oal_dft_print_all_key_info);

OAL_STATIC ssize_t  oal_dft_get_key_info(struct device *dev, struct device_attribute *attr, char* buf)
{
    oal_int32 i;
    oal_int32 ret = 0;

    oal_uint32 dft_mask;

    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    dft_mask = dft_print_mask & (KERN_PRINT|BUFF_PRINT);
    dft_print_mask = dft_mask;

    if(oal_list_is_empty(&g_dft_head))
    {
        printk(KERN_DEBUG"key info empty\n");
        ret +=  snprintf(buf + ret , PAGE_SIZE - ret, "key info empty\n");
        return ret;
    }

    if(OAL_DFT_TRACE_BUTT == 0)
        return ret;

    for(i = (OAL_DFT_TRACE_BUTT - 1); i >= 0 ; i--)
    {
        ret += oal_dft_dump_key_info(buf + ret, i, dft_mask);
    }
    
    return ret;
}
OAL_STATIC DEVICE_ATTR(key_info, S_IRUGO, oal_dft_get_key_info, NULL);

#ifdef HI110X_DRV_VERSION
OAL_STATIC oal_int32 oal_dft_print_version_info(char* buf)
{
    oal_int32 ret = 0;
    ret +=  snprintf(buf + ret , PAGE_SIZE - ret, "%s\n",HI110X_DRV_VERSION);
    return ret;
}

OAL_STATIC ssize_t  oal_dft_get_version_info(struct device *dev, struct device_attribute *attr, char* buf)
{
    oal_int32 ret = 0;

    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    ret += oal_dft_print_version_info(buf + ret);
    
    return ret;
}
OAL_STATIC DEVICE_ATTR(version, S_IRUGO, oal_dft_get_version_info, NULL);
#endif

OAL_STATIC struct attribute *dft_sysfs_entries[] = {
        &dev_attr_key_info.attr,
#ifdef HI110X_DRV_VERSION
        &dev_attr_version.attr,
#endif
        NULL
};

OAL_STATIC struct attribute_group dft_attribute_group = {
        .name = "dft",
        .attrs = dft_sysfs_entries,
};

OAL_STATIC oal_int32 dft_sysfs_entry_init(oal_void)
{
    oal_int32       ret = OAL_SUCC;
    oal_kobject*     pst_root_object = NULL;
    pst_root_object = oal_get_sysfs_root_object();
    if(NULL == pst_root_object)
    {
        OAL_IO_PRINT("{frw_sysfs_entry_init::get sysfs root object failed!}\n");
        return -OAL_EFAIL;
    }

    ret = sysfs_create_group(pst_root_object, &dft_attribute_group);
    if (ret)
    {
        OAL_IO_PRINT("{frw_sysfs_entry_init::sysfs create group failed!}\n");
        return ret;
    }
    return OAL_SUCC;
}

OAL_STATIC oal_int32 dft_sysfs_entry_exit(oal_void)
{
    oal_kobject*     pst_root_object = NULL;
    pst_root_object = oal_get_sysfs_root_object();
    if(NULL != pst_root_object)
    {
        sysfs_remove_group(pst_root_object, &dft_attribute_group);
    }

    return OAL_SUCC;
}
#endif

oal_int32 oal_dft_init(oal_void)
{
    oal_int32 ret = OAL_SUCC;
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
    ret = dft_sysfs_entry_init();
#endif
    return ret;
}

oal_void oal_dft_exit(oal_void)
{
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
    dft_sysfs_entry_exit();
#endif
}

oal_module_symbol(oal_dft_init);
oal_module_symbol(oal_dft_exit);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
