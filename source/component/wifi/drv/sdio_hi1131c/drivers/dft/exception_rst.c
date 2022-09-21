/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : exception_rst.c
  Version    : first draft
  Author     : 
  Create date: 2012-10-11
  Modify     :
  Func descr : except reset control
  Func list  :
  Modi histoy:
  1.Data     : 2015-04-11
    Author   : 
    Modify
    content  : Create File

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/delay.h>
#include <linux/rtc.h>

#include "plat_type.h"
#include "plat_debug.h"
#include "plat_pm.h"
#include "plat_pm_wlan.h"
#include "exception_rst.h"
#include "plat_firmware.h"
#include "oal_file.h"

#include "oal_sdio.h"
#include "oal_sdio_host_if.h"
#include "oal_hcc_host_if.h"
#include "heartbeat_host.h"
#include "stack.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_EXCEPTION_RST_C


/*****************************************************************************
  3 全局变量定义
*****************************************************************************/
struct st_exception_info *g_pst_exception_info = NULL;
EXPORT_SYMBOL(g_pst_exception_info);
//struct sdio_dump_bcpu_buff st_bcpu_dump_buff = {NULL, 0, 0};
//oal_netbuf_stru*       st_bcpu_dump_netbuf = NULL;

struct st_wifi_dump_mem_info g_st_pkt_b_ram =
{
    .mem_addr = PKT_B_RAM_BASEADDR,
    .size     = PKT_B_RAM_LEN,
    .file_name= "pkt_b_ram",
};

struct st_wifi_dump_mem_info g_st_ram_mem =
{
    .mem_addr = RAM_BASEADDR,
    .size     = RAM_LEN,
    .file_name= "ram",
};

struct st_wifi_dump_mem_info g_st_pkt_h_ram =
{
    .mem_addr = PKT_H_RAM_BASEADDR,
    .size     = PKT_H_RAM_LEN,
    .file_name= "pkt_h_ram",
};


p_st_wifi_demp_mem_info g_apst_panic_dump_mem[] =
{
    &g_st_pkt_b_ram,
    &g_st_ram_mem,
    &g_st_pkt_h_ram,
    NULL,
};

p_st_wifi_demp_mem_info g_apst_trans_fail_dump_mem[] =
{
    &g_st_pkt_b_ram,
    &g_st_ram_mem,
    &g_st_pkt_h_ram,
    NULL,
};


uint32 g_recvd_block_count = 0;

/*****************************************************************************
  2 函数实现
*****************************************************************************/
int32 get_exception_info_reference(struct st_exception_info **exception_data);
void  plat_exception_reset_work(struct work_struct *work);

void channel_disable(void)
{
#ifndef _PRE_FEATURE_USB
    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
#endif
}

/*****************************************************************************
 函 数 名  : plat_dfr_cfg_set
 功能描述  : dfr全局配置
 输入参数  : uint64 arg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void plat_dfr_cfg_set(uint64 arg)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return;
    }

    pst_exception_data->exception_reset_enable = arg ? (PLAT_EXCEPTION_ENABLE) : (PLAT_EXCEPTION_DISABLE);

    PS_PRINT_INFO("plat dfr cfg set value = %ld\n", arg);
}

/*****************************************************************************
 函 数 名  : get_exception_info_reference
 功能描述  : 获得保存异常信息的全局变量
 输入参数  : st_exception_info **exception结构体指针，保存全局变量地址的指针
 输出参数  : 无
 返 回 值  : 成功返回0，否则返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32 get_exception_info_reference(struct st_exception_info **exception_data)
{
    if (NULL == exception_data)
    {
        PS_PRINT_ERR("%s parm exception_data is NULL\n", __func__);
        return -EXCEPTION_FAIL;
    }

    if (NULL == g_pst_exception_info)
    {
        *exception_data = NULL;
        PS_PRINT_ERR("%s g_pst_exception_info is NULL\n", __func__);
        return -EXCEPTION_FAIL;
    }

    *exception_data = g_pst_exception_info;

    return EXCEPTION_SUCCESS;
}
EXPORT_SYMBOL(get_exception_info_reference);

/*****************************************************************************
 函 数 名  : plat_exception_handler
 功能描述  : 平台host异常处理总入口函数，填充异常信息，并触发异常处理work
 输入参数  : exception_type:异常的类型
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_exception_handler(uint32 exception_type)
{
	int32  ret = -EXCEPTION_FAIL;
    struct st_exception_info *pst_exception_data = NULL;
	struct pm_drv_data *pm_data = pm_get_drvdata();

    stop_heartbeat();

    if (exception_type >= EXCEPTION_TYPE_BUTT)
    {
        PS_PRINT_ERR("para exception_type %u is error!\n", exception_type);
        return -EXCEPTION_FAIL;
    }
    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
       return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }

    if (PLAT_EXCEPTION_ENABLE != pst_exception_data->exception_reset_enable)
    {
        PS_PRINT_INFO("plat exception reset not enable!");
        return EXCEPTION_SUCCESS;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_exception_data->wifi_exception_cnt += 1;
	ret = wifi_system_reset();
	if (ret != EXCEPTION_SUCCESS)
	{
		PS_PRINT_ERR("plat execption recovery fail! exception_type = [%u]\n",
		                               pst_exception_data->excetion_type);
	}
	else
	{
        PS_PRINT_SUC("plat execption recovery success!\n");
	}
	mutex_unlock(&pm_data->host_mutex);

    return ret;
}

EXPORT_SYMBOL(plat_exception_handler);

/*****************************************************************************
 函 数 名  : wifi_system_reset
 功能描述  : wifi全系统复位，对device重新上电，bfgn和wifi firmware重新加载，
 			 恢复全系统复位前bfgn的业务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_system_reset(void)
{
#ifdef _PRE_FEATURE_USB
        OAL_IO_PRINT("wifi_system_reset is not supported in usb, to be do in feature\n");
        return EXCEPTION_SUCCESS;
#else 

    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EXCEPTION_FAIL;
    }
    /* 打印host侧pm统计信息 */
    wlan_pm_dump_host_info();
    /* 清除pm相关变量 */
    wlan_pm_info_clean();
    /*重新上电，firmware重新加载*/
    hcc_disable(hcc_get_default_handler(), OAL_TRUE);
    
    wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);
    
    //oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);

    PS_PRINT_INFO("wifi system reset, board power on\n");
    board_power_on();

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (EXCEPTION_SUCCESS != firmware_download_function(WIFI_CFG))
    {
        PS_PRINT_ERR("hi110x system power reset failed!\n");
        return -EXCEPTION_FAIL;
    }
#else
    PS_PRINT_ERR("firmware_download_function is not supported, to be do\n");
#endif
    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);

    if (0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
    {
        PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
        CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_WCPU_BOOTUP));
        return -EXCEPTION_FAIL;
    }

    hcc_enable(hcc_get_default_handler(), OAL_TRUE);

    return EXCEPTION_SUCCESS;
#endif
}

/*****************************************************************************
 函 数 名  : wifi_exception_mem_dump
 功能描述  : 全系统复位，firmware重新加载的时候，导出device指定地址的内存
 输入参数  : pst_mem_dump_info  : 需要读取的内存信息
             count              : 需要读取的内存块个数
 输出参数  : 无
 返 回 值  : 异常处理成功返回0，否则返回1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32 wifi_exception_mem_dump(p_st_wifi_demp_mem_info * pst_mem_dump_info)
{
    int32 ret;
    struct st_exception_info *pst_exception_data = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return -EXCEPTION_FAIL;
    }
#ifndef _PRE_FEATURE_USB

    mutex_lock(&pm_data->host_mutex);

    oal_sdio_claim_host(oal_get_sdio_default_handler());
    ret = sdio_reinit();
    if (ret < 0)
    {
        oal_sdio_release_host(oal_get_sdio_default_handler());
        PS_PRINT_ERR("wifi mem dump:sdio reinit failed, ret=[%d]\n", ret);
        mutex_unlock(&pm_data->host_mutex);
        return -EXCEPTION_FAIL;
    }
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    ret = device_mem_dump(pst_mem_dump_info);
#else
    PS_PRINT_ERR("device_mem_dump add in later\n");
#endif
    oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_ALL);
    oal_sdio_release_host(oal_get_sdio_default_handler());
    if (ret < 0)
    {
        PS_PRINT_ERR("sdio_device_mem_dump failed, ret=[%d]\n", ret);
        mutex_unlock(&pm_data->host_mutex);
        return -EXCEPTION_FAIL;
    }

    mutex_unlock(&pm_data->host_mutex);
#endif
    return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL(wifi_exception_mem_dump);


void oal_exception_submit(int32 excep_type)
{
    oal_ulong flags;
    
#ifdef _PRE_FEATURE_USB
        OAL_IO_PRINT(" not supported in usb, to be do in feature\n");
        return;
#else 

    struct oal_sdio *hi_sdio = oal_get_sdio_default_handler();
    
    DECLARE_DFT_TRACE_KEY_INFO("sdio_exception", OAL_DFT_TRACE_EXCEP);
    if ((NULL == g_pst_exception_info) || (NULL == g_pst_exception_info->plat_exception_rst_workqueue) )
    {
        OAL_IO_PRINT("[E]%s, hi_sdio is null\n", __FUNCTION__);
        return;
    }
    if (OAL_UNLIKELY(NULL == hi_sdio))
    {
        OAL_IO_PRINT("[E]%s, hi_sdio is null\n", __FUNCTION__);
        return;
    }

    oal_spin_lock_irq_save(&(g_pst_exception_info->excp_lock), &flags);
    if (work_busy( &(g_pst_exception_info->excp_worker) ))
    {
        OAL_IO_PRINT("excep %d block, exception %d is working\n",excep_type, g_pst_exception_info->excetion_type);
        oal_spin_unlock_irq_restore(&g_pst_exception_info->excp_lock, &flags);
        return;
    }

    /*disable sdio*/
    oal_disable_sdio_state(hi_sdio, OAL_SDIO_ALL);
    hcc_change_state_exception();
    g_pst_exception_info->excetion_type = excep_type;
    queue_work(g_pst_exception_info->plat_exception_rst_workqueue, &(g_pst_exception_info->excp_worker));
    oal_spin_unlock_irq_restore( &(g_pst_exception_info->excp_lock), &flags);
#endif
}
EXPORT_SYMBOL(oal_exception_submit);

int32 oal_exception_is_busy(void)
{
    if(OAL_UNLIKELY(NULL == g_pst_exception_info))
    {
        return OAL_FALSE;
    }

    if(work_busy( &(g_pst_exception_info->excp_worker) ))
    {
        /*sdio mem dump is processing,
          can't power off or submit repeat*/
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
EXPORT_SYMBOL(oal_exception_is_busy);

int32 oal_trigger_exception(int32 is_sync)
{
    oal_ulong timeout_jiffies;
    
#ifdef _PRE_FEATURE_USB
    OAL_IO_PRINT(" not supported in usb, to be do in feature\n");
    return OAL_TRUE;
#else 

    if(OAL_TRUE == oal_exception_is_busy())
    {
        return OAL_TRUE;
    }

    /*trigger device panic*/
    if(oal_sdio_send_msg(oal_get_sdio_default_handler(), H2D_MSG_TEST))
    {
        OAL_IO_PRINT("send sdio panic message failed!\n");
        return OAL_FALSE;
    }

    if(OAL_TRUE != is_sync)
    {
        OAL_IO_PRINT("sdio exception is doing...\n");
        return OAL_TRUE;
    }

    /*wait device panic*/
    timeout_jiffies = OAL_TIME_JIFFY + OAL_MSECS_TO_JIFFIES(2000);
    for(;;)
    {
        if(OAL_TRUE == oal_exception_is_busy())
        {
            break;
        }

        if(oal_time_after(OAL_TIME_JIFFY, timeout_jiffies))
        {
            OAL_IO_PRINT("wait panic message timeout!\n");
            return OAL_FALSE;
        }

        oal_msleep(OAL_JIFFIES_TO_MSECS(1));
    }

    OAL_IO_PRINT("trigger sdio exception manually sucuess\n");
    return OAL_TRUE;
#endif
}
EXPORT_SYMBOL(oal_trigger_exception);


/*Try to dump device mem, controlled by flag sdio_dump_mem_flag*/
void oal_try_to_dump_device_mem(int32 is_sync)
{
    if(NOT_DUMP_MEM == (g_pst_exception_info->dump_mem_flag) )
    {
        OAL_IO_PRINT("sdio_dump_mem_flag is NOT_DUMP_MEM\r\n");
        return;
    }

    OAL_IO_PRINT("Try to dump device mem!\n");
    oal_trigger_exception(is_sync);
}
EXPORT_SYMBOL(oal_try_to_dump_device_mem);



oal_int32 oal_device_panic_callback(void *data)
{
    oal_exception_submit(DEVICE_PANIC);
    return OAL_SUCC;
}

/**********************************************************************************
//检查DEVICE WAKEUP HOST gpio 是否拉高。
//this func is not check whether the device is panic,
//it is give a long time for device reset CPU
**********************************************************************************/
oal_int32 oal_dev2host_gpio_hold_time_check(oal_uint32 switch_timeout, oal_uint32 hold_time)
{
    oal_ulong timeout;
    oal_uint32 gpio_value;
    oal_int32 state = 0;/*0 init, 1 gpio to high*/
    oal_time_t_stru time_start;
    oal_time_t_stru time_stop;
    oal_uint64  trans_us;

    if(!switch_timeout)
    {
        switch_timeout = 200;
    }

    timeout = OAL_TIME_JIFFY + OAL_MSECS_TO_JIFFIES(switch_timeout);
    time_start = oal_ktime_get();
    for(;;)
    {
        gpio_value = board_get_wlan_wkup_gpio_val();
        if(0 == state)
        {
            if(0 == gpio_value)
            {
                if(oal_time_after(OAL_TIME_JIFFY, timeout))
                {
                    OAL_IO_PRINT("[E]wait wakeup gpio to high timeout [%u] ms\n", switch_timeout);
                    return OAL_FALSE;
                }
                else
                {
                
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
                    usleep(20);
#else
                    usleep_range(10, 20);
#endif
                    continue;
                }
            }
            else
            {
                time_stop = oal_ktime_get();
                trans_us = (oal_uint64)oal_ktime_to_us(oal_ktime_sub(time_stop, time_start));
                OAL_IO_PRINT("device reset sdio ip cost %llu us\n", trans_us);
                timeout = OAL_TIME_JIFFY + OAL_MSECS_TO_JIFFIES(hold_time);
                state = 1;
                continue;
            }
        }
        else if(1 == state)
        {
            if(0 == gpio_value)
            {
                OAL_IO_PRINT("[E]gpio pull down again!\n");
                return OAL_FALSE;
            }
            else
            {
                if(oal_time_after(OAL_TIME_JIFFY, timeout))
                {
                    /*gpio high and hold enough time.*/
                    return OAL_TRUE;
                }
                else
                {
#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
                    usleep(20);
#else
                    usleep_range(10, 20);
#endif
                    continue;
                }
            }
        }
        else
        {
            OAL_IO_PRINT("[E]error state=%d\n", state);
            return OAL_FALSE;
        }
    }
}

oal_int32 check_except_type(oal_int32  excp_type)
{
    if(DEVICE_PANIC == excp_type)
    {
        DECLARE_DFT_TRACE_KEY_INFO("wifi_device_panic",OAL_DFT_TRACE_EXCEP);
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"[E]WiFi Device Panic");
        return SUCC;
    }
    else if(TRANS_FAIL == excp_type)
    {
        DECLARE_DFT_TRACE_KEY_INFO("sdio_trans_fail",OAL_DFT_TRACE_EXCEP);
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"[E]sdio_trans_fail");
        return SUCC;
    }
    else
    {
        PS_PRINT_ERR("excp_type error, excp_type = %d\r\n", excp_type);
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"[E]excp_type error");
        return -EINVAL;
    }
}

extern oal_int32 hisdio_intr_mode;
/*******************************************************************************
如果是panic类型，则需要确定gpio时间确保device复位成功
*******************************************************************************/
void check_panic_except(oal_int32  *excp_type)
{
    if(DEVICE_PANIC != *excp_type)
    {
        return;
    }

    if(!hisdio_intr_mode)
    {
        /*sdio mode*/
        oal_msleep(200);
        return;
    }

    /*gpio mode*/
    if(OAL_TRUE != oal_dev2host_gpio_hold_time_check(500, 100))
    {
        *excp_type = TRANS_FAIL;
    }
}

void check_trans_fail_except(oal_int32  *excp_type)
{
    if(TRANS_FAIL != *excp_type)
    {
        return;
    }

    oal_msleep(5000);
    *excp_type = DEVICE_PANIC;
}

oal_int32 exception_mem_dump(oal_int32  excp_type)
{
    int32 ret;

    if(TRANS_FAIL == excp_type)
    {
        OAL_IO_PRINT("wifi_exception_mem_dump,excep_type is TRANS_FAIL, line = %d\n", __LINE__);
        wlan_rst();
        ret = wifi_exception_mem_dump(g_apst_trans_fail_dump_mem);
    }
    else if(DEVICE_PANIC == excp_type)
    {
        OAL_IO_PRINT("wifi_exception_mem_dump,excep_type is DEVICE_PANIC, line = %d\n", __LINE__);
        ret = wifi_exception_mem_dump(g_apst_panic_dump_mem);
    }
    else
    {
        ret = -EINVAL;
    }

    return ret;
}

void  oal_exception_handler(oal_work_stru *work)
{
    oal_int32 ret = OAL_SUCC;
    
#ifdef _PRE_FEATURE_USB
    OAL_IO_PRINT("oal_sdio_exception_handler is not supported in usb, to be do in feature\n");
    return;
#else 

    struct oal_sdio* hi_sdio = oal_get_sdio_default_handler();
    
    OAL_IO_PRINT("oal_sdio_exception_handler(), line = %d\n", __LINE__);
    

    
    if((NULL == hi_sdio) || (NULL == g_pst_exception_info))
    {
        OAL_IO_PRINT("[E]hi_sdio is null\n");
        return;
    }

    if(0 > check_except_type(g_pst_exception_info->excetion_type))
    {
        return;
    }
    
    oal_sdio_claim_host(hi_sdio);
    oal_disable_sdio_state(hi_sdio, OAL_SDIO_ALL);
    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
    
#ifdef _PRE_OAL_FEATURE_KEY_PROCESS_TRACE
    oal_dft_print_all_key_info();
#endif
#ifdef CONFIG_PRINTK
    hwifi_panic_log_dump(KERN_DEBUG);
#endif

    wlan_pm_disable_check_wakeup(OAL_FALSE);
    check_panic_except( &(g_pst_exception_info->excetion_type) );
    check_trans_fail_except( &(g_pst_exception_info->excetion_type) );

//first time, try panic
    oal_sdio_wake_lock(hi_sdio);
    ret = exception_mem_dump(g_pst_exception_info->excetion_type);
    oal_sdio_wake_unlock(hi_sdio);
    if( ret < 0)
    {
    //second time, try trans fail
        OAL_IO_PRINT("exception_mem_dump fail, exception trans to TRANS_FAIL, line = %d\n", __LINE__);
        g_pst_exception_info->excetion_type = TRANS_FAIL;
        oal_sdio_wake_lock(hi_sdio);
        ret = exception_mem_dump(g_pst_exception_info->excetion_type);
        oal_sdio_wake_unlock(hi_sdio);
    }

    if ( ret < 0)
    {
        OAL_IO_PRINT("exception_mem_dump fail, line = %d\n", __LINE__);
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"Panic File Save Failed!");
    }
    else
    {
        OAL_IO_PRINT("exception_mem_dump ok,exception is %d, line = %d\n", g_pst_exception_info->excetion_type, __LINE__);
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"Panic File Save OK!");
    }


    oal_disable_sdio_state(hi_sdio, OAL_SDIO_ALL);
    oal_sdio_release_host(hi_sdio);

    if(NULL == g_pst_exception_info->wifi_dfr_func)
    {
        PS_PRINT_ERR("g_pst_exception_info->wifi_dfr_fun is NULL\r\n");
        //oal_sdio_release_host(hi_sdio);
        return;
    }
    (g_pst_exception_info->wifi_dfr_func)();
    //oal_sdio_release_host(hi_sdio);
#endif
}

/*****************************************************************************
 函 数 名  : plat_exception_reset_init
 功能描述  : 平台异常处理模块初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回0，否则返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_exception_reset_init(void)
{
    if(NULL != g_pst_exception_info)
    {
        PS_PRINT_ERR("g_pst_exception_info is not null\r\n");
        return -EXCEPTION_FAIL;
    }

    g_pst_exception_info = (struct st_exception_info *)oal_kzalloc(sizeof(struct st_exception_info),OAL_GFP_KERNEL);
    if (NULL == g_pst_exception_info)
    {
        PS_PRINT_ERR("kzalloc p_exception_data is failed!\n");
        goto fail;
    }

    g_pst_exception_info->excetion_type = EXCEPTION_TYPE_BUTT;

    g_pst_exception_info->exception_reset_enable   = PLAT_EXCEPTION_ENABLE;
    g_pst_exception_info->wifi_exception_cnt       = 0;

    /*初始化异常处理workqueue和work*/
    g_pst_exception_info->plat_exception_rst_workqueue = create_singlethread_workqueue("plat_exception_reset_queue");
    if(NULL == g_pst_exception_info->plat_exception_rst_workqueue)
    {
        PS_PRINT_ERR("create_singlethread_workqueue failed!\r\n");
        goto fail;
    }    
    oal_spin_lock_init(&g_pst_exception_info->excp_lock);
    OAL_INIT_WORK(&g_pst_exception_info->excp_worker, oal_exception_handler);

    g_pst_exception_info->wifi_dfr_func = NULL;

    ///*初始化sdio读取bcpu完成量*/
    //init_completion(&g_pst_exception_info->wait_sdio_d2h_dump_ack);

    if( 0 > heart_beat_init() )
    {
        goto fail;
    }
    
    PS_PRINT_SUC("plat exception reset init success\n");

	return EXCEPTION_SUCCESS;

fail:
    plat_exception_reset_exit();
    return EXCEPTION_FAIL;
}

EXPORT_SYMBOL_GPL(plat_exception_reset_init);

/*****************************************************************************
 函 数 名  : plat_exception_reset_exit
 功能描述  : 平台异常处理模块退出清理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回0，否则返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int32 plat_exception_reset_exit(void)
{

    if (g_pst_exception_info == NULL)
    {
        PS_PRINT_ERR("g_pst_exception_info is NULL!\n");
        return -EXCEPTION_FAIL;
    }

    if(NULL != g_pst_exception_info)
    {
        if(NULL != g_pst_exception_info->plat_exception_rst_workqueue)
        {
            oal_cancel_work_sync(&g_pst_exception_info->excp_worker);
            destroy_workqueue(g_pst_exception_info->plat_exception_rst_workqueue);
            g_pst_exception_info->plat_exception_rst_workqueue = NULL;
        }
        kfree(g_pst_exception_info);
        g_pst_exception_info = NULL;
    }
    
    heart_beat_release();

    PS_PRINT_SUC("plat exception reset exit success\n");

    return EXCEPTION_SUCCESS;
}

EXPORT_SYMBOL_GPL(plat_exception_reset_exit);


