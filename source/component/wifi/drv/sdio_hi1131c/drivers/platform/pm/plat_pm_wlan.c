/*
 *
 * Copyright (C), 2001-2021, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : plat_pm.c
 * Version       : Hi1101
 * Author        : 
 * Created       : 2012/12/10
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * 1.Date        : 2015/04/10
 *   Author      : 
 *   Modification: Created file
 *
 */

#if (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include <linux/module.h>   /* kernel module definitions */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
//#include <linux/kobject.h>
#include <linux/irq.h>
#include <linux/wakelock.h>
#if 0
#include <linux/mmc/sdio.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/host.h>

#include <linux/gpio.h>
#endif
#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"

#include "plat_type.h"
//#include "plat_debug.h"
#include "plat_pm_wlan.h"
#include "plat_pm.h"

#include "oal_hcc_host_if.h"
#include "oam_ext_if.h"
#include "oal_usb_if.h"
#include "plat_debug.h"
#include "exception_rst.h"
#ifdef _PRE_WLAN_FEATURE_WOW
#include "hmac_wow.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_PLAT_PM_WLAN_C

#define EXPORT_SYMBOL_GPL(x)

oal_int32 g_set_usb =0;
oal_uint8 g_usb_rx_task_flag = 0;
extern volatile  int  intr_initial_flag;
/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
struct wlan_pm_s* gpst_wlan_pm_info = OAL_PTR_NULL;

wlan_pm_callback_stru     gst_wlan_pm_callback =
{
    .wlan_pm_wakeup_dev  = wlan_pm_wakeup_dev,
    .wlan_pm_state_get   = wlan_pm_state_get,
    .wlan_pm_wakeup_host = wlan_pm_wakeup_host,
    .wlan_pm_feed_wdg    = wlan_pm_feed_wdg,
    .wlan_pm_wakeup_dev_ack    = wlan_pm_wakeup_dev_ack,

};
oal_bool_enum g_wlan_pm_switch = 0; /* 1131C-debug */

EXPORT_SYMBOL_GPL(g_wlan_pm_switch);

oal_uint32 auto_freq_enable = 1; /* 1131C-debug */
module_param(auto_freq_enable, uint, S_IRUGO | S_IWUSR);

extern  int32 wlan_power_on(void);
extern  int32 wlan_power_off(void);
void wlan_pm_wakeup_work(oal_work_stru *pst_worker);
void wlan_pm_sleep_work(oal_work_stru *pst_worker);
void wlan_pm_freq_adjust_work(oal_work_stru *pst_worker);

void wlan_pm_wdg_timeout(struct wlan_pm_s *pm_data);



int32 wlan_pm_wakeup_done_callback(void *data);
int32 wlan_pm_close_done_callback(void *data);
int32 wlan_pm_open_bcpu_done_callback(void *data);
int32 wlan_pm_close_bcpu_done_callback(void *data);

int32 wlan_pm_stop_wdg(struct wlan_pm_s *pst_wlan_pm_info);
oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker);
void wlan_pm_info_clean(void);

#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
void wlan_pm_forslp_work(oal_work_stru *pst_worker);
oal_uint wlan_pm_resume(void);
#endif

extern oal_atomic g_pm_spinlock_get;
extern  unsigned int g_ul_wlan_resume_state;
extern  unsigned int g_ul_wlan_resume_wifi_init_flag;
extern  unsigned int g_ul_wlan_reusme_wifi_mode;
/*****************************************************************************
 函 数 名  : wlan_pm_get_drv
 功能描述  : 获取全局wlan结构
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
struct wlan_pm_s*  wlan_pm_get_drv(oal_void)
{
    return gpst_wlan_pm_info;
}

EXPORT_SYMBOL_GPL(wlan_pm_get_drv);

/*****************************************************************************
 函 数 名  : wlan_pm_set_device_ready
 功能描述  : 接受到deviceready的信号，设置host侧 device ready状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  wlan_pm_set_device_ready(oal_void* data)
{
    struct wlan_pm_s    *pst_wlan_pm = (struct wlan_pm_s*)data;
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "#### wlan_pm_set_device_ready\n");

    OAL_COMPLETE(&pst_wlan_pm->st_device_ready);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : wlan_pm_init_device_ready
 功能描述  : 初始化host侧 device ready状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_init_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_device_ready);
}
/*****************************************************************************
 函 数 名  : wlan_pm_wait_device_ready
 功能描述  : 等待host侧 device ready状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_wait_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    int rv;
    /* 等待host下半部初始化完成 */
    rv = oal_wait_for_completion_timeout(&pst_wlan_pm->st_device_ready, (oal_uint32)OAL_MSECS_TO_JIFFIES(HOST_WAIT_BOTTOM_INIT_TIMEOUT));
    if(0 != rv)
    {
        start_heartbeat();
    }
    return rv;
}

/*****************************************************************************
 函 数 名  : wlan_pm_heartbeat_callback
 功能描述  : 心跳包处理接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wlan_pm_heartbeat_callback(void *data)
{
    return SUCCESS;
}



/*****************************************************************************
 函 数 名  : wlan_pm_exit
 功能描述  : WLAN pm退出接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint  wlan_pm_exit(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_SUCC;
    }

    wlan_pm_stop_wdg(pst_wlan_pm);
#ifndef _PRE_FEATURE_USB
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WAKEUP_SUCC);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WLAN_READY);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_ALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_DISALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_POWEROFF_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_OPEN_BCPU_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_CLOSE_BCPU_ACK);
#ifdef _PRE_WLAN_FEATURE_WOW
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WOW_WIFI_REDAY);
#endif
#endif
    kfree(pst_wlan_pm);

    gpst_wlan_pm_info = OAL_PTR_NULL;

    OAL_IO_PRINT("[plat_pm]wlan_pm_exit ok!");

    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : wlan_pm_is_poweron
 功能描述  : wifi是否上电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_is_poweron(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    //struct pm_drv_data  *pm_data = pm_get_drvdata();

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FALSE;
    }
    //mutex_lock(&pm_data->host_mutex);

    if (POWER_STATE_OPEN == pst_wlan_pm->ul_wlan_power_state)
    {
        //mutex_unlock(&pm_data->host_mutex);
        return OAL_TRUE;
    }
    else
    {
        //mutex_unlock(&pm_data->host_mutex);
        return OAL_FALSE;
    }
}
EXPORT_SYMBOL_GPL(wlan_pm_is_poweron);

/*****************************************************************************
 函 数 名  : wlan_pm_open

 功能描述  : open wifi,如果bfgx没有开启,上电,否则，下命令开WCPU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wlan_pm_open(oal_void)
{

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();
#ifdef _PRE_FEATURE_USB
    struct oal_usb     *pst_usb;
    oal_int32           ret;
    pst_usb = oal_get_usb_default_handler();
#endif

    OAL_IO_PRINT("wlan_pm_open caller\r\n");

    if ((NULL == pm_data)||(OAL_PTR_NULL == pst_wlan_pm))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PWR, "wlan_pm_open::pm_data[%p] or pst_wlan_pm[%p] is NULL!", pm_data, pst_wlan_pm);
        return OAL_FAIL;
    }
    mutex_lock(&pm_data->host_mutex);
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
    /*若host是睡眠下电后wkup 不判断dev开关状态*/
    extern unsigned int g_ul_wlan_resume_state;
    if (!g_ul_wlan_resume_state)
    {
        if (POWER_STATE_OPEN == pst_wlan_pm->ul_wlan_power_state)
        {
            mutex_unlock(&pm_data->host_mutex);
            OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open::aleady opened");
            return OAL_ERR_CODE_ALREADY_OPEN;
        }
    }
#else
    if (POWER_STATE_OPEN == pst_wlan_pm->ul_wlan_power_state)
    {
        mutex_unlock(&pm_data->host_mutex);
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open::aleady opened");
        return OAL_ERR_CODE_ALREADY_OPEN;
    }
#endif
#ifdef _PRE_FEATURE_USB
    if (!pst_wlan_pm->pst_usb->st_sdio_wakelock.lock_count)
    {
        /*make sure open only lock once*/
        oal_sdio_wake_lock(pst_wlan_pm->pst_usb);
    }
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_open::get wakelock %lu!",pst_wlan_pm->pst_usb->st_sdio_wakelock.lock_count);
#else
    if (!pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count)
    {
        /*make sure open only lock once*/
        oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    }
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_open::get wakelock %lu!",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
#endif

    pst_wlan_pm->ul_open_cnt++;

    if (OAL_SUCC != wlan_power_on())
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_open::wlan_power_on fail!");
        pst_wlan_pm->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
#ifdef _PRE_FEATURE_USB
        oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
#else
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
#endif
        mutex_unlock(&pm_data->host_mutex);
        DECLARE_DFT_TRACE_KEY_INFO("wlan_power_on_fail",OAL_DFT_TRACE_FAIL);
        return OAL_FAIL;
    }

#ifdef _PRE_FEATURE_USB
    /* 再上电场景，重新启动usb rx data线程 */
    if (1 == g_usb_rx_task_flag)
    {
        g_usb_rx_task_flag = 0;

        if (OAL_SUCC != oal_register_usb_intr(hcc_get_default_handler()->hi_usb))
        {
            OAL_IO_PRINT("failed to start usb rx task\n");
            oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
            return -OAL_EFAIL;
        }

    }

    OAM_WARNING_LOG0(0, OAM_SF_PWR, "usb_set_intr_buffer begin\r\n");
    msleep(500);
    ret = usb_set_intr_buffer(pst_usb->usb_drv_rx_message);
    if (ret < 0)
    {
      OAM_WARNING_LOG0(0, OAM_SF_PWR, "failed to usb_set_intr_buffer\n");
      return -OAL_EFAIL;
    }
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "usb_set_intr_buffer end\r\n");

#endif



#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#if 0 /* 1131C-debug */
        wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);

        if (OAL_PTR_NULL != g_pst_custom_process_func.p_custom_cali_func)
        {
            g_pst_custom_process_func.p_custom_cali_func();
        }
        else
        {
            OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_open::NO g_pst_custom_process_func registered");
            mutex_unlock(&pm_data->host_mutex);

            return OAL_FAIL;
        }

        if (0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
        {
            DECLARE_DFT_TRACE_KEY_INFO("wlan_wait_custom_cali_fail", OAL_DFT_TRACE_FAIL);

            OAM_ERROR_LOG1(0,OAM_SF_PWR, "wlan_pm_open::wlan_pm_wait_custom_cali timeout %d !!!!!!", HOST_WAIT_BOTTOM_INIT_TIMEOUT);

            mutex_unlock(&pm_data->host_mutex);
            return OAL_FAIL;
        }
#endif /* 0 */
#endif

    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_open::wlan_pm_open SUCC!! g_wlan_pm_switch = %d", g_wlan_pm_switch);
    DECLARE_DFT_TRACE_KEY_INFO("wlan_open_succ",OAL_DFT_TRACE_SUCC);
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
    /*若host是睡眠下电后wkup 不等待device ready*/

    if (!g_ul_wlan_resume_state)
    {
        if (!wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
        {

            OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_wait_device_ready timeout %d !!!!!!\n", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
            return -OAL_EFAIL;;
        }
    }
#else
    if (!wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
    {

        OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_wait_device_ready timeout %d !!!!!!\n", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
        return -OAL_EFAIL;;
    }
#endif
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "device ready message is coming\r\n");

#if 1
    //OAM_WARNING_LOG0(0, OAM_SF_PWR, "oal_set2usb_recv_buffer\n");
    //if (g_set_usb == 0)
    //{
#ifdef _PRE_FEATURE_USB
       if (oal_set2usb_recv_buffer(oal_get_usb_default_handler()))
       {
           OAL_IO_PRINT("failed to oal_set2usb_recv_buffer\n");
           mutex_unlock(&pm_data->host_mutex);
           return -OAL_EFAIL;
       }
#endif
       //g_set_usb ++;
    //}
   //OAM_WARNING_LOG0(0, OAM_SF_PWR, "oal_set2usb_recv_buffer\n");
#endif
#ifdef _PRE_FEATURE_USB
    pst_usb->hcc_rx_active_flag = OAL_TRUE;
    wake_up_interruptible(&pst_usb->hcc_rx_thread_active_wq);
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "wake up usb rx!!\n");
#endif

    OAM_WARNING_LOG0(0, OAM_SF_PWR, "hcc_enable\n");
    hcc_enable(hcc_get_default_handler(), OAL_TRUE);


    OAL_IO_PRINT("wlan_pm_open SUCC!!\n");

    wlan_pm_enable();

    /*将timeout值恢复为默认值，并启动定时器*/
    wlan_pm_set_timeout(WLAN_SLEEP_DEFAULT_CHECK_CNT);

    mutex_unlock(&pm_data->host_mutex);
    return OAL_SUCC;

}
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
oal_int32           ram_reg_test_result = OAL_SUCC;
unsigned long long  ram_reg_test_time = 0;

oal_int32 wlan_device_mem_check(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAL_BUG_ON(!pst_wlan_pm);
    ram_reg_test_result = OAL_SUCC;
    ram_reg_test_time = 0;
#ifdef _PRE_FEATURE_USB
    oal_sdio_wake_lock(pst_wlan_pm->pst_usb);
#else
    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
#endif
    if (0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_ram_reg_test_work))
    {
#ifdef _PRE_FEATURE_USB
        oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
#else
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
#endif
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"st_ram_reg_test_work submit work fail !\n");
    }

    return OAL_SUCC;

}
oal_int32 wlan_device_mem_check_result(unsigned long long *time)
{
    *time = ram_reg_test_time;
    return ram_reg_test_result;
}
oal_void wlan_device_mem_check_work(oal_work_stru *pst_worker)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    mutex_lock(&pm_data->host_mutex);

    ram_reg_test_result = device_mem_check(&ram_reg_test_time);

#ifdef _PRE_FEATURE_USB
    oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
#else
    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
#endif

    mutex_unlock(&pm_data->host_mutex);
}
EXPORT_SYMBOL_GPL(wlan_device_mem_check);
EXPORT_SYMBOL_GPL(wlan_device_mem_check_result);


#endif

EXPORT_SYMBOL_GPL(wlan_pm_open);

/*****************************************************************************
 函 数 名  : wlan_pm_close
 功能描述  : close wifi,如果bfgx没有开,下电，否则下命令关WCPU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
extern int isAsic(void);
oal_uint32 wlan_pm_close(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();

    //OAL_IO_PRINT("wlan_pm_close caller[%pF]\n",(void*)_RET_IP_);

    if (NULL == pm_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_close,pm_data is NULL!");
        return OAL_FAIL;
    }

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    if (!pst_wlan_pm->ul_apmode_allow_pm_flag)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_close,AP mode,do not shutdown power.");
        return OAL_SUCC;
    }

    OAL_IO_PRINT("[plat_pm]wlan_pm_close start!!\n");

    mutex_lock(&pm_data->host_mutex);
#if 0
    if (!isAsic())
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close is FPGA,do not close wifi!\n");
        mutex_unlock(&pm_data->host_mutex);
        return OAL_SUCC;
    }
#endif
    pst_wlan_pm->ul_close_cnt++;

    if (POWER_STATE_SHUTDOWN == pst_wlan_pm->ul_wlan_power_state)
    {
        mutex_unlock(&pm_data->host_mutex);
        return OAL_ERR_CODE_ALREADY_CLOSE;
    }

    wlan_pm_disable();

    wlan_pm_stop_wdg(pst_wlan_pm);
#ifndef _PRE_FEATURE_USB
    wlan_pm_info_clean();

    /*mask rx sdio data interrupt*/

    oal_sdio_func1_int_mask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);

    if (OAL_SUCC!=wlan_power_off())
    {
        OAL_IO_PRINT("wlan_power_off FAIL!\n");

        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_power_off FAIL!\n");
        mutex_unlock(&pm_data->host_mutex);
        DECLARE_DFT_TRACE_KEY_INFO("wlan_power_off_fail",OAL_DFT_TRACE_FAIL);
        return OAL_FAIL;
    }

    pst_wlan_pm->ul_wlan_power_state = POWER_STATE_SHUTDOWN;

    /*unmask rx sdio data interrupt*/
    oal_sdio_func1_int_unmask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

    OAM_WARNING_LOG1(0,OAM_SF_PWR,"wlan_pm_close release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
    oal_sdio_wakelocks_release_detect(pst_wlan_pm->pst_sdio);
#else
    wlan_pm_info_clean();
    intr_initial_flag = 0;
    if (OAL_SUCC!=wlan_power_off())
    {
        OAL_IO_PRINT("wlan_power_off FAIL!\n");

        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_power_off FAIL!\n");
        mutex_unlock(&pm_data->host_mutex);
        DECLARE_DFT_TRACE_KEY_INFO("wlan_power_off_fail",OAL_DFT_TRACE_FAIL);
        return OAL_FAIL;
    }
    pst_wlan_pm->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
    oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
    OAL_IO_PRINT("wlan_pm_close pst_wlan_pm->ul_wlan_power_state =  %d!\n",pst_wlan_pm->ul_wlan_power_state);

    /* 下电时删除usb rx data线程，待再次上电时，重新开启 */
    if (0 == g_usb_rx_task_flag)
    {
        g_usb_rx_task_flag = 1;

        if (OAL_SUCC != oal_unregister_usb_intr(hcc_get_default_handler()->hi_usb))
        {
            OAL_IO_PRINT("failed to stop usb rx task\n");
            mutex_unlock(&pm_data->host_mutex);
            return -OAL_EFAIL;
        }
    }
#endif
    mutex_unlock(&pm_data->host_mutex);

    hcc_dev_flowctrl_on(hcc_get_default_handler(), 0);

    OAM_WARNING_LOG0(0,OAM_SF_PWR,"wlan_pm_close succ!\n");
    DECLARE_DFT_TRACE_KEY_INFO("wlan_close_succ",OAL_DFT_TRACE_SUCC);
    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_close);

/*****************************************************************************
 函 数 名  : wlan_pm_enable
 功能描述  : 使能wlan平台低功耗
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_enable(oal_void)
{

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if (!g_wlan_pm_switch)
    {
        return OAL_SUCC;
    }

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if (OAL_TRUE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable already enabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    pst_wlan_pm->ul_wlan_pm_enable = OAL_TRUE;

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable SUCC!");

    return OAL_SUCC;
}
EXPORT_SYMBOL_GPL(wlan_pm_enable);

/*****************************************************************************
 函 数 名  : wlan_pm_disable
 功能描述  : 去使能wlan平台低功耗
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_disable_check_wakeup(oal_int32 flag)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if (OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable already disabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    if (OAL_TRUE == flag)
    {
         if (OAL_SUCC != wlan_pm_wakeup_dev())
         {
             OAM_WARNING_LOG0(0, OAM_SF_PWR,"pm wake up dev fail!");
         }
    }

    pst_wlan_pm->ul_wlan_pm_enable = OAL_FALSE;


#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
     if (OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_set_lock_mod_func)
     {
           g_pst_alg_process_func.p_auto_freq_set_lock_mod_func(OAL_FALSE);
     }
     else
     {
         OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_wdg_timeout:NO p_auto_freq_set_lock_mod_func registered");

     }
#endif

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    oal_cancel_work_sync(&pst_wlan_pm->st_wakeup_work);
    oal_cancel_work_sync(&pst_wlan_pm->st_sleep_work);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable SUCC!");

    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_disable_check_wakeup);

oal_uint32 wlan_pm_disable(oal_void)
{
    return wlan_pm_disable_check_wakeup(OAL_TRUE);
}
EXPORT_SYMBOL_GPL(wlan_pm_disable);

/*****************************************************************************
 函 数 名  : wlan_pm_work_submit
 功能描述  : 提交一个kernel work
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker)
{
    oal_int  i_ret    = 0;

    if (work_busy(pst_worker))
    {
        /*If comm worker is processing,
          we need't submit again*/
        i_ret = -OAL_EBUSY;
        goto done;
    }
    else
    {
        OAM_INFO_LOG1(0, OAM_SF_PWR,"WiFi %pF Worker Submit\n",(void*)pst_worker->func);
        queue_work(pst_wlan_pm->pst_pm_wq, pst_worker);
    }
done:
    return i_ret;
}

void wlan_pm_freq_adjust_work(oal_work_stru *pst_worker)
{
    hcc_tx_transfer_lock(hcc_get_default_handler());

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    if (OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_adjust_to_level_func)
    {
       g_pst_alg_process_func.p_auto_freq_adjust_to_level_func();
    }
    else
    {
      OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_freq_adjust_work:NO p_auto_freq_adjust_to_level_func registered");
    }
#endif

    hcc_tx_transfer_unlock(hcc_get_default_handler());
}

struct wifi_srv_callback_handler* wlan_pm_get_wifi_srv_handler(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FALSE;
    }

    return &pst_wlan_pm->st_wifi_srv_handler;
}

oal_uint wlan_pm_adjust_feq(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if (!auto_freq_enable)
    {
        return OAL_SUCC;
    }

    OAL_BUG_ON(!pst_wlan_pm);

    if (0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_freq_adjust_work))
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_adjust_feq submit work fail !\n");
    }

    return OAL_SUCC;

}

#elif (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include <linux/module.h>   /* kernel module definitions */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
#include <linux/kobject.h>
#include <linux/irq.h>
#include <linux/wakelock.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/host.h>
#include <linux/gpio.h>

#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"

#include "plat_type.h"
#include "heartbeat_host.h"
#include "plat_pm_wlan.h"
#include "plat_pm.h"


#include "oal_hcc_host_if.h"
#include "oam_ext_if.h"
#include "plat_debug.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_PLAT_PM_WLAN_C


/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
struct wlan_pm_s* gpst_wlan_pm_info = OAL_PTR_NULL;

wlan_pm_callback_stru     gst_wlan_pm_callback =
{
    .wlan_pm_wakeup_dev  = wlan_pm_wakeup_dev,
    .wlan_pm_state_get   = wlan_pm_state_get,
    .wlan_pm_wakeup_host = wlan_pm_wakeup_host,
    .wlan_pm_feed_wdg    = wlan_pm_feed_wdg,
    .wlan_pm_wakeup_dev_ack    = wlan_pm_wakeup_dev_ack,

};
oal_bool_enum g_wlan_pm_switch = 0; /* 1131C-debug */

EXPORT_SYMBOL_GPL(g_wlan_pm_switch);

oal_uint32 auto_freq_enable = 1; /* 1131C-debug */
module_param(auto_freq_enable, uint, S_IRUGO | S_IWUSR);

extern  int32 wlan_power_on(void);
extern  int32 wlan_power_off(void);
void wlan_pm_wakeup_work(oal_work_stru *pst_worker);
void wlan_pm_sleep_work(oal_work_stru *pst_worker);
void wlan_pm_freq_adjust_work(oal_work_stru *pst_worker);

void wlan_pm_wdg_timeout(struct wlan_pm_s *pm_data);

int32 wlan_pm_wakeup_done_callback(void *data);
int32 wlan_pm_close_done_callback(void *data);
int32 wlan_pm_open_bcpu_done_callback(void *data);
int32 wlan_pm_close_bcpu_done_callback(void *data);
int32 wlan_pm_halt_bcpu_done_callback(void *data);


int32 wlan_pm_stop_wdg(struct wlan_pm_s *pst_wlan_pm_info);
oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker);
void wlan_pm_info_clean(void);

#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
void wlan_pm_forslp_work(oal_work_stru *pst_worker);
#endif

extern oal_atomic g_wakeup_dev_wait_ack;
/*****************************************************************************
 函 数 名  : wlan_pm_get_drv
 功能描述  : 获取全局wlan结构
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
struct wlan_pm_s*  wlan_pm_get_drv(oal_void)
{
    return gpst_wlan_pm_info;
}

EXPORT_SYMBOL_GPL(wlan_pm_get_drv);

/*****************************************************************************
 函 数 名  : wlan_pm_set_device_ready
 功能描述  : 接受到deviceready的信号，设置host侧 device ready状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32  wlan_pm_set_device_ready(oal_void* data)
{
    struct wlan_pm_s    *pst_wlan_pm = (struct wlan_pm_s*)data;
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "#### wlan_pm_set_device_ready\n");

    OAL_COMPLETE(&pst_wlan_pm->st_device_ready);
    return OAL_SUCC;
}
/*****************************************************************************
 函 数 名  : wlan_pm_init_device_ready
 功能描述  : 初始化host侧 device ready状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_init_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_device_ready);
}
/*****************************************************************************
 函 数 名  : wlan_pm_wait_device_ready
 功能描述  : 等待host侧 device ready状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : oal_void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_wait_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    int rv;
    /* 等待host下半部初始化完成 */
    rv = oal_wait_for_completion_timeout(&pst_wlan_pm->st_device_ready, (oal_uint32)OAL_MSECS_TO_JIFFIES(HOST_WAIT_BOTTOM_INIT_TIMEOUT));
    if(0 != rv)
    {
        start_heartbeat();
    }
    return rv;
}

/*****************************************************************************
 函 数 名  : wlan_pm_heartbeat_callback
 功能描述  : 心跳包处理接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wlan_pm_heartbeat_callback(void *data)
{
    return SUCCESS;
}

/*****************************************************************************
 函 数 名  : wlan_pm_exit
 功能描述  : WLAN pm退出接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint  wlan_pm_exit(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_SUCC;
    }

    wlan_pm_stop_wdg(pst_wlan_pm);
#ifndef _PRE_FEATURE_USB
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WAKEUP_SUCC);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WLAN_READY);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_ALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_DISALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_POWEROFF_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_OPEN_BCPU_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_CLOSE_BCPU_ACK);
#ifdef _PRE_WLAN_FEATURE_WOW
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WOW_WIFI_REDAY);
#endif
#endif

    oal_destroy_workqueue(pst_wlan_pm->pst_pm_wq);

    kfree(pst_wlan_pm);

    gpst_wlan_pm_info = OAL_PTR_NULL;

    OAL_IO_PRINT("[plat_pm]wlan_pm_exit ok!");


    return OAL_SUCC;

}

/*****************************************************************************
 函 数 名  : wlan_pm_is_poweron
 功能描述  : wifi是否上电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_is_poweron(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    //struct pm_drv_data  *pm_data = pm_get_drvdata();

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FALSE;
    }
    //oal_mutex_unlock(&pm_data->host_mutex);

    if (POWER_STATE_OPEN == pst_wlan_pm->ul_wlan_power_state)
    {
        //oal_mutex_unlock(&pm_data->host_mutex);
        return OAL_TRUE;
    }
    else
    {
        //oal_mutex_unlock(&pm_data->host_mutex);
        return OAL_FALSE;
    }
}
EXPORT_SYMBOL_GPL(wlan_pm_is_poweron);

/*****************************************************************************
 函 数 名  : wlan_pm_get_wifi_srv_handler
 功能描述  : 获取回调handler指针
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
struct wifi_srv_callback_handler* wlan_pm_get_wifi_srv_handler(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FALSE;
    }

    return &pst_wlan_pm->st_wifi_srv_handler;
}
EXPORT_SYMBOL_GPL(wlan_pm_get_wifi_srv_handler);

/*****************************************************************************
 函 数 名  : wlan_pm_open
 功能描述  : open wifi,如果bfgx没有开启,上电,否则，下命令开WCPU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wlan_pm_open(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();

    //OAL_IO_PRINT("wlan_pm_open caller[%pF]\n",(void*)_RET_IP_);

    if ((NULL == pm_data)||(OAL_PTR_NULL == pst_wlan_pm))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PWR, "wlan_pm_open::pm_data[%p] or pst_wlan_pm[%p] is NULL!", pm_data, pst_wlan_pm);
        return OAL_FAIL;
    }

    oal_mutex_lock(&pm_data->host_mutex);

    if(POWER_STATE_OPEN == pst_wlan_pm->ul_wlan_power_state)
    {
        oal_mutex_unlock(&pm_data->host_mutex);
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open::aleady opened");
        return OAL_ERR_CODE_ALREADY_OPEN;
    }

    if(!pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count)
    {
        /*make sure open only lock once*/
        oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_open::get wakelock %lu!",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    pst_wlan_pm->ul_open_cnt++;

    if(OAL_SUCC != wlan_power_on())
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_open::wlan_power_on fail!");
        pst_wlan_pm->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        oal_mutex_unlock(&pm_data->host_mutex);
        DECLARE_DFT_TRACE_KEY_INFO("wlan_power_on_fail",OAL_DFT_TRACE_FAIL);
        return OAL_FAIL;
    }

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#if 0 /* 1131C-debug */
        wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);

        if(OAL_PTR_NULL == g_pst_custom_process_func.p_custom_cali_func)
        {
            OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_open::NO g_pst_custom_process_func registered");
            oal_mutex_unlock(&pm_data->host_mutex);

            return OAL_FAIL;
        }

        /* 如果校准下发成功则等待device ready；否则继续打开wifi */
        if (OAL_SUCC == g_pst_custom_process_func.p_custom_cali_func())
        {
            if(0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
            {
                DECLARE_DFT_TRACE_KEY_INFO("wlan_wait_custom_cali_fail", OAL_DFT_TRACE_FAIL);

                OAM_ERROR_LOG1(0,OAM_SF_PWR, "wlan_pm_open::wlan_pm_wait_custom_cali timeout %d !!!!!!", HOST_WAIT_BOTTOM_INIT_TIMEOUT);

                oal_mutex_unlock(&pm_data->host_mutex);
                if(OAL_TRUE == oal_trigger_sdio_exception(oal_get_sdio_default_handler(), OAL_TRUE))
                {
                    OAL_IO_PRINT("dump device mem when cali custom failed!\n");
                }
                return OAL_FAIL;
            }
        }
#endif /* 0 */
#endif
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_open::wlan_pm_open SUCC!! g_wlan_pm_switch = %d", g_wlan_pm_switch);
    DECLARE_DFT_TRACE_KEY_INFO("wlan_open_succ",OAL_DFT_TRACE_SUCC);

    wlan_pm_enable();

    /*将timeout值恢复为默认值，并启动定时器*/
    wlan_pm_set_timeout(WLAN_SLEEP_DEFAULT_CHECK_CNT);

    oal_mutex_unlock(&pm_data->host_mutex);

    return OAL_SUCC;

}
#if ((_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1131C_HOST))
oal_int32           ram_reg_test_result = OAL_SUCC;
unsigned long long  ram_reg_test_time = 0;

oal_int32 wlan_device_mem_check(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAL_BUG_ON(!pst_wlan_pm);
    ram_reg_test_result = OAL_SUCC;
    ram_reg_test_time = 0;
    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);

    if(0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_ram_reg_test_work))
    {
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"st_ram_reg_test_work submit work fail !\n");
    }

    return OAL_SUCC;

}
oal_int32 wlan_device_mem_check_result(unsigned long long *time)
{
    *time = ram_reg_test_time;
    return ram_reg_test_result;
}
oal_void wlan_device_mem_check_work(oal_work_stru *pst_worker)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    oal_mutex_lock(&pm_data->host_mutex);

    ram_reg_test_result = device_mem_check(&ram_reg_test_time);

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

    oal_mutex_unlock(&pm_data->host_mutex);
}

EXPORT_SYMBOL_GPL(wlan_device_mem_check);
EXPORT_SYMBOL_GPL(wlan_device_mem_check_result);


#endif

EXPORT_SYMBOL_GPL(wlan_pm_open);

/*****************************************************************************
 函 数 名  : wlan_pm_close
 功能描述  : close wifi,如果bfgx没有开,下电，否则下命令关WCPU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
extern int isAsic(void);
oal_uint32 wlan_pm_close(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();

    //OAL_IO_PRINT("wlan_pm_close caller[%pF]\n",(void*)_RET_IP_);

    if (NULL == pm_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_close,pm_data is NULL!");
        return OAL_FAIL;
    }

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    if (!pst_wlan_pm->ul_apmode_allow_pm_flag)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_close,AP mode,do not shutdown power.");
        return OAL_SUCC;
    }

    OAL_IO_PRINT("[plat_pm]wlan_pm_close start!!\n");

    oal_mutex_lock(&pm_data->host_mutex);
#if 0
    if (!isAsic())
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close is FPGA,do not close wifi!\n");
        oal_mutex_unlock(&pm_data->host_mutex);
        return OAL_SUCC;
    }
#endif
    pst_wlan_pm->ul_close_cnt++;

    if(POWER_STATE_SHUTDOWN == pst_wlan_pm->ul_wlan_power_state)
    {
        oal_mutex_unlock(&pm_data->host_mutex);
        return OAL_ERR_CODE_ALREADY_CLOSE;
    }

    wlan_pm_disable();

    wlan_pm_stop_wdg(pst_wlan_pm);

    wlan_pm_info_clean();

    /*mask rx sdio data interrupt*/
    oal_sdio_func1_int_mask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);

    if(OAL_SUCC!=wlan_power_off())
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_power_off FAIL!\n");
        oal_mutex_unlock(&pm_data->host_mutex);
        DECLARE_DFT_TRACE_KEY_INFO("wlan_power_off_fail",OAL_DFT_TRACE_FAIL);
        return OAL_FAIL;
    }

    pst_wlan_pm->ul_wlan_power_state = POWER_STATE_SHUTDOWN;

    /*unmask rx sdio data interrupt*/
    oal_sdio_func1_int_unmask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

    OAM_WARNING_LOG1(0,OAM_SF_PWR,"wlan_pm_close release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    oal_sdio_wakelocks_release_detect(pst_wlan_pm->pst_sdio);

    oal_mutex_unlock(&pm_data->host_mutex);

    hcc_dev_flowctrl_on(hcc_get_default_handler(), 0);

    OAM_WARNING_LOG0(0,OAM_SF_PWR,"wlan_pm_close succ!\n");
    DECLARE_DFT_TRACE_KEY_INFO("wlan_close_succ",OAL_DFT_TRACE_SUCC);
    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_close);

/*****************************************************************************
 函 数 名  : wlan_pm_enable
 功能描述  : 使能wlan平台低功耗
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_enable(oal_void)
{

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if (!g_wlan_pm_switch)
    {
        return OAL_SUCC;
    }

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if (OAL_TRUE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable already enabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    pst_wlan_pm->ul_wlan_pm_enable = OAL_TRUE;

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable SUCC!");

    return OAL_SUCC;
}
EXPORT_SYMBOL_GPL(wlan_pm_enable);

/*****************************************************************************
 函 数 名  : wlan_pm_disable
 功能描述  : 去使能wlan平台低功耗
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint32 wlan_pm_disable_check_wakeup(oal_int32 flag)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if (OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable already disabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    if (OAL_TRUE == flag)
    {
         if (OAL_SUCC != wlan_pm_wakeup_dev())
         {
             OAM_WARNING_LOG0(0, OAM_SF_PWR,"pm wake up dev fail!");
         }
    }

    pst_wlan_pm->ul_wlan_pm_enable = OAL_FALSE;


#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
     if (OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_set_lock_mod_func)
     {
           g_pst_alg_process_func.p_auto_freq_set_lock_mod_func(OAL_FALSE);
     }
     else
     {
         OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_wdg_timeout:NO p_auto_freq_set_lock_mod_func registered");

     }
#endif

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    oal_cancel_work_sync(&pst_wlan_pm->st_wakeup_work);
    oal_cancel_work_sync(&pst_wlan_pm->st_sleep_work);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable SUCC!");

    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_disable_check_wakeup);

oal_uint32 wlan_pm_disable(oal_void)
{
    return wlan_pm_disable_check_wakeup(OAL_TRUE);
}
EXPORT_SYMBOL_GPL(wlan_pm_disable);

/*****************************************************************************
 函 数 名  : wlan_pm_open_bcpu
 功能描述  : 唤醒BCPU
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint  wlan_pm_open_bcpu(oal_void)
{
#define RETRY_TIMES (3)
    oal_uint32           i;
    oal_int32            ret = OAL_FAIL;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint32           ul_ret;

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

     /*通过sdio配置命令，解复位BCPU*/
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"sdio open BCPU");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    for (i = 0; i < RETRY_TIMES; i++)
    {
        ret = wlan_pm_wakeup_dev();
        if (OAL_SUCC == ret)
        {
            break;
        }
    }

    if(OAL_SUCC != ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_dev fail!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_dev succ, retry times [%d]", i);

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_open_bcpu_done);

    ul_ret = oal_sdio_send_msg(pst_wlan_pm->pst_sdio, H2D_MSG_RESET_BCPU);
    if(OAL_SUCC == ul_ret)
    {
        /*等待device执行命令*/
        oal_up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);
        ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_open_bcpu_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_OPEN_BCPU_WAIT_TIMEOUT));
        if(0 == ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_open_bcpu wait device ACK timeout !");
            hcc_tx_transfer_unlock(hcc_get_default_handler());
            return OAL_FAIL;
        }

        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_SUCC;
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"fail to send H2D_MSG_RESET_BCPU");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_FAIL;
    }
}

/*****************************************************************************
 函 数 名  : wlan_pm_work_submit
 功能描述  : 提交一个kernel work
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker)
{
    oal_int  i_ret    = 0;

    if(oal_work_is_busy(pst_worker))
    {
        /*If comm worker is processing,
          we need't submit again*/
        i_ret = -OAL_EBUSY;
        goto done;
    }
    else
    {
        OAM_INFO_LOG1(0, OAM_SF_PWR,"WiFi %pF Worker Submit\n",(void*)pst_worker->func);
        if(false==oal_queue_work(pst_wlan_pm->pst_pm_wq, pst_worker))
        {
           i_ret = -OAL_EFAIL;
        }
    }
done:
    return i_ret;
}

/*****************************************************************************
 函 数 名  : wlan_pm_close_done_callback
 功能描述  : device应答poweroff ack消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
int32 wlan_pm_close_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close_done_callback !");

    /*关闭RX通道，防止SDIO RX thread继续访问SDIO*/
    oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_RX);

    pst_wlan_pm->ul_close_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_close_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete H2D_MSG_PM_WLAN_OFF done!");

    return SUCCESS;

}

/*****************************************************************************
 函 数 名  : wlan_pm_open_bcpu_done_callback
 功能描述  : device应答open bcpu ack消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

int32 wlan_pm_open_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_open_bcpu_done_callback !");

    pst_wlan_pm->ul_open_bcpu_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_open_bcpu_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete H2D_MSG_RESET_BCPU done!");

    return SUCCESS;
}

/*****************************************************************************
 函 数 名  : wlan_pm_close_bcpu_done_callback
 功能描述  : device应答open bcpu ack消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

int32 wlan_pm_close_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close_bcpu_done_callback !");

    pst_wlan_pm->ul_close_bcpu_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_close_bcpu_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete H2D_MSG_PM_BCPU_OFF done!");

    return SUCCESS;
}

/*****************************************************************************
 函 数 名  : wlan_pm_halt_bcpu_done_callback
 功能描述  : device应答open bcpu ack消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

int32 wlan_pm_halt_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_halt_bcpu_done_callback !");

    OAL_COMPLETE(&pst_wlan_pm->st_halt_bcpu_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete wlan_pm_halt_bcpu_done_callback done!");

    return SUCCESS;
}

void wlan_pm_freq_adjust_work(oal_work_stru *pst_worker)
{
    hcc_tx_transfer_lock(hcc_get_default_handler());

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    if (OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_adjust_to_level_func)
    {
        g_pst_alg_process_func.p_auto_freq_adjust_to_level_func();
    }
    else
    {
      OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_freq_adjust_work:NO p_auto_freq_adjust_to_level_func registered");
    }
#endif

    hcc_tx_transfer_unlock(hcc_get_default_handler());
}

/*****************************************************************************
 函 数 名  : wlan_pm_adjust_feq
 功能描述  : 提交一个work，调整host和device的CPU和DDR频率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint wlan_pm_adjust_feq(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(!auto_freq_enable)
    {
        return OAL_SUCC;
    }

    OAL_BUG_ON(!pst_wlan_pm);

    if(0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_freq_adjust_work))
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_adjust_feq submit work fail !\n");
    }

    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_adjust_feq);

/*****************************************************************************
 函 数 名  : wlan_pm_poweroff_cmd
 功能描述  : 发消息到device，wifi device关闭wifi系统资源，等待bcpu给它下电
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wlan_pm_poweroff_cmd(oal_void)
{
    oal_int32            ret;
    oal_int32           l_val = 0;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"Send H2D_MSG_PM_WLAN_OFF cmd");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_SUCC != wlan_pm_wakeup_dev())
    {
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }


    ret =  oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_WLAN_OFF);
    if(OAL_SUCC == ret)
    {
        /*等待device执行命令*/
        msleep(20);
        l_val = board_get_wlan_wkup_gpio_val();
        if (0 == l_val)
        {
            OAM_ERROR_LOG1(0, OAM_SF_PWR,"wlan_pm_poweroff_cmd  wait device ACK timeout && GPIO_LEVEL[%d] !", l_val);

            hcc_tx_transfer_unlock(hcc_get_default_handler());

            return OAL_FAIL;
        }

    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"fail to send H2D_MSG_PM_WLAN_OFF");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_FAIL;
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    return OAL_SUCC;


}

/*****************************************************************************
 函 数 名  : wlan_pm_shutdown_bcpu_cmd
 功能描述  : 发消息到device，wifi device关闭BCPU
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wlan_pm_shutdown_bcpu_cmd(oal_void)
{
#define RETRY_TIMES (3)
    oal_uint32           i;
    oal_int32            ret = OAL_FAIL;
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"Send H2D_MSG_PM_BCPU_OFF cmd");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    for (i = 0; i < RETRY_TIMES; i++)
    {
        ret = wlan_pm_wakeup_dev();
        if (OAL_SUCC == ret)
        {
            break;
        }
    }

    if(OAL_SUCC != ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_dev fail!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_dev succ, retry times [%d]", i);

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_bcpu_done);

    ret =  oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_BCPU_OFF);
    if(OAL_SUCC == ret)
    {
        /*等待device执行命令*/
        ul_ret = oal_wait_for_completion_timeout(&pst_wlan_pm->st_close_bcpu_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_POWEROFF_ACK_WAIT_TIMEOUT));
        if(0 == ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_shutdown_bcpu_cmd wait device ACK timeout !");
            hcc_tx_transfer_unlock(hcc_get_default_handler());
            return OAL_FAIL;
        }
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"fail to send H2D_MSG_PM_BCPU_OFF");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_FAIL;
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wlan_pm_dump_info
 功能描述  : debug, 发消息到device，串口输出维测信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

void wlan_pm_dump_host_info(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(NULL == pst_wlan_pm)
    {
        return;
    }

    OAL_IO_PRINT("----------wlan_pm_dump_host_info begin-----------\n");
    OAL_IO_PRINT("power on:%ld, enable:%ld,g_wlan_pm_switch:%d\n",pst_wlan_pm->ul_wlan_power_state,pst_wlan_pm->ul_wlan_pm_enable,g_wlan_pm_switch);
    OAL_IO_PRINT("dev state:%ld, sleep stage:%d\n",pst_wlan_pm->ul_wlan_dev_state,pst_wlan_pm->ul_slpack);
    OAL_IO_PRINT("open:%d,close:%d\n",pst_wlan_pm->ul_open_cnt,pst_wlan_pm->ul_close_cnt);
    OAL_IO_PRINT("sdio suspend:%d,sdio resume:%d\n",pst_wlan_pm->pst_sdio->ul_sdio_suspend,pst_wlan_pm->pst_sdio->ul_sdio_resume);
    OAL_IO_PRINT("gpio_intr[no.%lu]:%llu\n",pst_wlan_pm->pst_sdio->ul_wlan_irq,pst_wlan_pm->pst_sdio->gpio_int_count);
    OAL_IO_PRINT("data_intr:%llu\n",pst_wlan_pm->pst_sdio->data_int_count);
    OAL_IO_PRINT("wakeup_intr:%llu\n",pst_wlan_pm->pst_sdio->wakeup_int_count);
    OAL_IO_PRINT("D2H_MSG_WAKEUP_SUCC:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count);
    OAL_IO_PRINT("D2H_MSG_ALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count);
    OAL_IO_PRINT("D2H_MSG_DISALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count);


    OAL_IO_PRINT("wakeup_dev_wait_ack:%d\n",oal_atomic_read(&g_wakeup_dev_wait_ack));
    OAL_IO_PRINT("wakeup_succ:%d\n",pst_wlan_pm->ul_wakeup_succ);
    OAL_IO_PRINT("wakeup_dev_ack:%d\n",pst_wlan_pm->ul_wakeup_dev_ack);
    OAL_IO_PRINT("wakeup_done_callback:%d\n",pst_wlan_pm->ul_wakeup_done_callback);
    OAL_IO_PRINT("wakeup_succ_work_submit:%d\n",pst_wlan_pm->ul_wakeup_succ_work_submit);
    OAL_IO_PRINT("wakeup_fail_wait_sdio:%d\n",pst_wlan_pm->ul_wakeup_fail_wait_sdio);
    OAL_IO_PRINT("wakeup_fail_timeout:%d\n",pst_wlan_pm->ul_wakeup_fail_timeout);
    OAL_IO_PRINT("wakeup_fail_set_reg:%d\n",pst_wlan_pm->ul_wakeup_fail_set_reg);
    OAL_IO_PRINT("wakeup_fail_submit_work:%d\n",pst_wlan_pm->ul_wakeup_fail_submit_work);
    OAL_IO_PRINT("sleep_succ:%d\n",pst_wlan_pm->ul_sleep_succ);
    OAL_IO_PRINT("sleep feed wdg:%d\n",pst_wlan_pm->ul_sleep_feed_wdg_cnt);
    OAL_IO_PRINT("sleep_fail_request:%d\n",pst_wlan_pm->ul_sleep_fail_request);
    OAL_IO_PRINT("sleep_fail_set_reg:%d\n",pst_wlan_pm->ul_sleep_fail_set_reg);
    OAL_IO_PRINT("sleep_fail_wait_timeout:%d\n",pst_wlan_pm->ul_sleep_fail_wait_timeout);
    OAL_IO_PRINT("sleep_fail_forbid:%d\n",pst_wlan_pm->ul_sleep_fail_forbid);
    OAL_IO_PRINT("sleep_work_submit:%d\n",pst_wlan_pm->ul_sleep_work_submit);
    OAL_IO_PRINT("wklock_cnt:%lu\n \n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
    OAL_IO_PRINT("----------wlan_pm_dump_host_info end-----------\n");

}

/*****************************************************************************
 函 数 名  : wlan_pm_host_info_print
 功能描述  : cat维测节点输出host低功耗统计
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_int32 wlan_pm_host_info_print(struct wlan_pm_s *pst_wlan_pm,char* buf,oal_int32 buf_len)
{
    oal_int32 ret = 0;

    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"----------wlan_pm_host_info_print begin-----------\n");
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"power on:%ld, enable:%ld,g_wlan_pm_switch:%d\n",pst_wlan_pm->ul_wlan_power_state,pst_wlan_pm->ul_wlan_pm_enable,g_wlan_pm_switch);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"dev state:%ld, sleep stage:%d\n",pst_wlan_pm->ul_wlan_dev_state,pst_wlan_pm->ul_slpack);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"open:%d,close:%d\n",pst_wlan_pm->ul_open_cnt,pst_wlan_pm->ul_close_cnt);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sdio suspend:%d,sdio resume:%d\n",pst_wlan_pm->pst_sdio->ul_sdio_suspend,pst_wlan_pm->pst_sdio->ul_sdio_resume);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"gpio_intr[no.%lu]:%llu\n",pst_wlan_pm->pst_sdio->ul_wlan_irq,pst_wlan_pm->pst_sdio->gpio_int_count);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"data_intr:%llu\n",pst_wlan_pm->pst_sdio->data_int_count);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_intr:%llu\n",pst_wlan_pm->pst_sdio->wakeup_int_count);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"D2H_MSG_WAKEUP_SUCC:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"D2H_MSG_ALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"D2H_MSG_DISALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count);


    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_dev_wait_ack:%d\n",oal_atomic_read(&g_wakeup_dev_wait_ack));
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_succ:%d\n",pst_wlan_pm->ul_wakeup_succ);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_dev_ack:%d\n",pst_wlan_pm->ul_wakeup_dev_ack);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_done_callback:%d\n",pst_wlan_pm->ul_wakeup_done_callback);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_succ_work_submit:%d\n",pst_wlan_pm->ul_wakeup_succ_work_submit);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_fail_wait_sdio:%d\n",pst_wlan_pm->ul_wakeup_fail_wait_sdio);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_fail_timeout:%d\n",pst_wlan_pm->ul_wakeup_fail_timeout);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_fail_set_reg:%d\n",pst_wlan_pm->ul_wakeup_fail_set_reg);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wakeup_fail_submit_work:%d\n",pst_wlan_pm->ul_wakeup_fail_submit_work);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sleep_succ:%d\n",pst_wlan_pm->ul_sleep_succ);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sleep feed wdg:%d\n",pst_wlan_pm->ul_sleep_feed_wdg_cnt);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sleep_fail_request:%d\n",pst_wlan_pm->ul_sleep_fail_request);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sleep_fail_set_reg:%d\n",pst_wlan_pm->ul_sleep_fail_set_reg);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sleep_fail_wait_timeout:%d\n",pst_wlan_pm->ul_sleep_fail_wait_timeout);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sleep_fail_forbid:%d\n",pst_wlan_pm->ul_sleep_fail_forbid);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"sleep_work_submit:%d\n",pst_wlan_pm->ul_sleep_work_submit);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"wklock_cnt:%lu\n \n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
    ret += OAL_SPRINTF(buf + ret , buf_len - ret,"----------wlan_pm_host_info_print end-----------\n");

    return ret;
}

void wlan_pm_dump_device_info(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_DEBUG);
}

oal_void wlan_pm_debug_sleep(void)
{
   struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);

    pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

    return  ;
}

oal_void wlan_pm_debug_wakeup(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;

    return  ;
}

oal_void wlan_pm_debug_wake_lock(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    OAL_IO_PRINT("wlan_pm_debug_wake_lock:wklock_cnt = %lu\r\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    return  ;
}

oal_void wlan_pm_debug_wake_unlock(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
    OAL_IO_PRINT("wlan_pm_debug_wake_unlock:wklock_cnt = %lu\r\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    return  ;
}

#endif


/*****************************************************************************
 函 数 名  : wlan_pm_init_dev
 功能描述  : 初始化device的状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint wlan_pm_init_dev(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint             ul_flag;
    oal_int              ret;


    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }
    PS_PRINT_DBG("init_dev!\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_init_dev!\n");


    board_set_wlan_h2d_pm_state(WLAN_PM_WKUPDEV_LEVEL);
#ifdef _PRE_FEATURE_USB
    oal_spin_lock_irq_save(&pst_wlan_pm->pst_usb->st_pm_state_lock,&ul_flag);

    pst_wlan_pm->ul_wlan_dev_state              = HOST_DISALLOW_TO_SLEEP;
    pst_wlan_pm->ul_slpack                      = SLPACK_DEV_DISALLOW;

    oal_spin_unlock_irq_restore(&pst_wlan_pm->pst_usb->st_pm_state_lock,&ul_flag);
#else
    oal_spin_lock_irq_save(&pst_wlan_pm->pst_sdio->st_pm_state_lock,&ul_flag);

    pst_wlan_pm->ul_wlan_dev_state              = HOST_DISALLOW_TO_SLEEP;
    pst_wlan_pm->ul_slpack                      = SLPACK_DEV_DISALLOW;

    oal_spin_unlock_irq_restore(&pst_wlan_pm->pst_sdio->st_pm_state_lock,&ul_flag);
#endif

    /* wait for sdio wakeup */
    ret = oal_down_timeout(&chan_wake_sema, 6*OAL_TIME_HZ);
    if (-ETIME == ret)
    {
        //PS_PRINT_ERR("sdio controller is not ready!");
#ifdef _PRE_FEATURE_USB
        oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
#else
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
#endif
        return OAL_FAIL;
    }
    oal_up(&chan_wake_sema);

    return OAL_SUCC;
}

/*****************************************************************************
 函 数 名  : wlan_pm_chan_reinit
 功能描述  : 唤醒流程reinit chan
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年8月17日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint wlan_pm_chan_reinit(void)
{
    oal_int32              ret;
#ifdef _PRE_FEATURE_USB
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    OAL_IO_PRINT("waiting for enum done");
    wait_usb_enum_done();
    usb_set_intr_buffer(pst_wlan_pm->pst_usb->usb_drv_rx_message);
    if(oal_set2usb_recv_buffer(pst_wlan_pm->pst_usb))
    {
       OAL_IO_PRINT("failed to oal_set2usb_recv_buffer\n");
       return -OAL_EFAIL;
    }
    pst_wlan_pm->pst_usb->hcc_rx_active_flag = OAL_TRUE;
    wake_up_interruptible(&pst_wlan_pm->pst_usb->hcc_rx_thread_active_wq);
    OAL_IO_PRINT("wake up usb rx!!\n");
    return OAL_SUCC;
#else
    struct pm_drv_data  *pm_data = pm_get_drvdata();

    oal_sdio_claim_host(pm_data->pst_wlan_pm_info->pst_sdio);

#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
    if(!g_ul_wlan_resume_state)
    {
        ret = oal_sdio_dev_reinit();
    }
    else
    {
        ret = oal_sdio_func_probe_resume();
    }
#else
    ret = sdio_reinit();
#endif
    oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
    return ret;
#endif
}

/*****************************************************************************
 函 数 名  : wlan_pm_wakeup_dev
 功能描述  : 唤醒device
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint wlan_pm_wakeup_dev(oal_void)
{
#define WKUP_RETRY_TIMES (1)
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    //oal_uint             flags;
    oal_int32              ret;
    oal_uint8              uc_wakeup_retry = 0;
    static oal_uint8       uc_wakeup_err_count = 0;
#if 0 //1131 debug
    if (OAL_TRUE == g_wlan_pm_switch
    &&  0        == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "wlan_pm_wakeup_dev, pm_switch[%d],t[%d]\n", pst_wlan_pm->ul_wlan_pm_enable,hmac_wow_get_time());
    }
#endif
    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        PS_PRINT_ERR("OAL_PTR_NULL!\n");
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"[pm]OAL_PTR_NULL!!");
        return OAL_FAIL;
    }

    if (HOST_DISALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
    {
        return OAL_SUCC;
    }

#ifdef _PRE_FEATURE_USB
    oal_sdio_wake_lock(pst_wlan_pm->pst_usb);
#else
    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
#endif

wakeup_again:

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_wakeup_done);
    PS_PRINT_DBG("wkupdev!\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]wake up device!");

    /* wait for sdio wakeup */
    ret = oal_down_timeout(&chan_wake_sema, 6*OAL_TIME_HZ);
    if (-ETIME == ret)
    {
        pst_wlan_pm->ul_wakeup_fail_wait_sdio++;
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"[pm]sdio controller is not ready!");
#ifdef _PRE_FEATURE_USB
        oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
#else
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
#endif
        goto wakeup_fail;
    }
    oal_up(&chan_wake_sema);

#ifndef _PRE_FEATURE_USB
    oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_FALSE);
   // oal_spin_lock_irq_save(&pst_wlan_pm->pst_sdio->st_irq_lock, &flags);
#endif
    pst_wlan_pm ->ul_wakeup_gpio_up_cnt ++;
    PS_PRINT_DBG("gpio high\n");
    OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]gpio high level cnt::%u!", pst_wlan_pm ->ul_wakeup_gpio_up_cnt);
    board_set_wlan_h2d_pm_state(WLAN_PM_WKUPDEV_LEVEL);

    oal_atomic_set(&g_wakeup_dev_wait_ack,1);

#ifndef _PRE_FEATURE_USB
    oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);
    // oal_spin_lock_irq_save(&pst_wlan_pm->pst_sdio->st_irq_lock, &flags);
#endif

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;

    //chan reinit
    PS_PRINT_DBG("wakeup chan reinit\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]channel reinit!");
    ret = wlan_pm_chan_reinit();
    if (ret < 0)
    {
        pst_wlan_pm->ul_wakeup_fail_wait_sdio++;
        pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        if(0==uc_wakeup_retry)
        {
            PS_PRINT_WARNING("sdio reinit failed,try again,  ret:%d!\n", ret);
            OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]sdio reinit failed,try again!,  ret:%d!\n", ret);
            board_set_wlan_h2d_pm_state(WLAN_PM_SLPREQ_LEVEL);
            uc_wakeup_retry++;
            goto wakeup_again;
        }
        else
        {
            PS_PRINT_ERR("sdio reinit failed, ret:%d!\n", ret);
            OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]sdio reinit failed!,  ret:%d!\n", ret);
            goto wakeup_fail;
        }
    }

    PS_PRINT_DBG("chan reinit done, waitting for dev ack\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]chan reinit done, waitting for dev ack!");
    //oal_up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);

    ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_wakeup_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_WAKUP_MSG_WAIT_TIMEOUT));
    if (0 == ul_ret)
    {
        pst_wlan_pm->ul_wakeup_fail_timeout++;

        if (uc_wakeup_retry++ < WKUP_RETRY_TIMES)
        {
            PS_PRINT_WARNING("wkup fail,try again\n");
            OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]wlan_pm_wakeup_dev wait device complete fail,wait time %d ms!,try again",WLAN_WAKUP_MSG_WAIT_TIMEOUT);
            board_set_wlan_h2d_pm_state(WLAN_PM_SLPREQ_LEVEL);
            goto wakeup_again;
        }
        else
        {
            PS_PRINT_ERR("wkup fail\n");
            OAM_ERROR_LOG2(0, OAM_SF_PWR,"[pm]wlan_pm_wakeup_dev [%d]wait device complete fail,wait time %d ms!",uc_wakeup_err_count,WLAN_WAKUP_MSG_WAIT_TIMEOUT);
            goto wakeup_fail;
        }
    }

    pst_wlan_pm->ul_wakeup_succ++;
    DECLARE_DFT_TRACE_KEY_INFO("wlan_wakeup_succ",OAL_DFT_TRACE_SUCC);
    //PS_PRINT_INFO("wlan_pm_wakeup_dev succ, wakelock cnt %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    pst_wlan_pm->ul_wdg_timeout_curr_cnt = 0;
    pst_wlan_pm->ul_packet_cnt           = 0;
    PS_PRINT_DBG("wkup ok\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]host wakeup device succ");

    wlan_pm_feed_wdg();
    uc_wakeup_err_count = 0;

    //usleep_range(500,510);

    start_heartbeat();

    return OAL_SUCC;
wakeup_fail:

    pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

#ifdef _PRE_FEATURE_USB
    oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
#else
    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
#endif
    DECLARE_DFT_TRACE_KEY_INFO("wlan_wakeup_fail",OAL_DFT_TRACE_FAIL);
    uc_wakeup_err_count++;

    /* pm唤醒失败超出门限，启动dfr流程 */
    if (WLAN_WAKEUP_FAIL_MAX_TIMES < uc_wakeup_err_count)
    {
        OAM_ERROR_LOG1(0, OAM_SF_PWR,"[pm]Now ready to enter DFR process after [%d]times wlan_wakeup_fail!", uc_wakeup_err_count);
        uc_wakeup_err_count = 0;
#ifndef _PRE_FEATURE_USB
        //oal_exception_submit(oal_get_sdio_default_handler(), TRANS_FAIL);
        //oal_exception_submit(oal_get_sdio_default_handler(), WIFI_WAKEUP_FAIL);
#endif
        //wifi_exception_work_submit(TIMER_TIMEOUT);
    }
    CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_WAKEUP_DEV));

    return OAL_FAIL;

}

oal_void wlan_pm_wakeup_dev_ack(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm;

    if(oal_atomic_read(&g_wakeup_dev_wait_ack))
    {
        pst_wlan_pm = wlan_pm_get_drv();

        if (OAL_PTR_NULL == pst_wlan_pm)
        {
            return ;
        }

        pst_wlan_pm->ul_wakeup_dev_ack++;

        OAL_COMPLETE(&pst_wlan_pm->st_wakeup_done);


        oal_atomic_set(&g_wakeup_dev_wait_ack,0);
    }

    return;

}
/*****************************************************************************
 函 数 名  : wlan_pm_wakeup_host
 功能描述  : device唤醒host
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_uint wlan_pm_wakeup_host(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    PS_PRINT_DBG("wkuphost!\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]dev wake up host!");

    OAL_BUG_ON(!pst_wlan_pm);
#ifdef _PRE_FEATURE_USB
    oal_sdio_wake_lock(pst_wlan_pm->pst_usb);
#else
    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
#endif
    OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_host get wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    if (0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_wakeup_work))
    {
        pst_wlan_pm->ul_wakeup_fail_submit_work++;
#ifdef _PRE_FEATURE_USB
        oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
        OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_host submit work fail, release wakelock %lu!\n",pst_wlan_pm->pst_usb->st_sdio_wakelock.lock_count);
#else
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_host submit work fail, release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
#endif

    }
    else
    {
        pst_wlan_pm->ul_wakeup_succ_work_submit++;
    }

    return OAL_SUCC;

}
/*****************************************************************************
 函 数 名  : wlan_pm_ack_handle
 功能描述  : device ack处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_ack_handle(oal_int32 ack,void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;
    if(0 == pst_wlan_pm->ul_waitting_for_dev_ack)
    {
      OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]not waitting for dev ack !\n");
      return;
    }
    if(0 == (--pst_wlan_pm->ul_waitting_for_dev_ack))
    {
      pst_wlan_pm->ul_slpack = ack;

      OAL_COMPLETE(&pst_wlan_pm->st_sleep_request_ack);
    }
    else
    {
      OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]not pairing ack :: %d !\n", pst_wlan_pm->ul_waitting_for_dev_ack);
    }
}
/*****************************************************************************
 函 数 名  : wlan_pm_allow_sleep_callback
 功能描述  : device应答allow_sleep消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_int32 wlan_pm_allow_sleep_callback(void *data)
{

    PS_PRINT_DBG("wlan_pm_allow_sleep !\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]wlan pm device allow sleep !\n");

    wlan_pm_ack_handle(SLPACK_DEV_ALLOW, data);

    return SUCCESS;

}
/*****************************************************************************
 函 数 名  : wlan_pm_disallow_sleep_callback
 功能描述  : device应答allow_sleep消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_int32 wlan_pm_disallow_sleep_callback(void *data)
{
    //PS_PRINT_INFO("wlan_pm_disallow_sleep_callback !\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "[pm]wlan pm device ack disallow sleep!\n");
    PS_PRINT_INFO("wlan_pm_disallow_sleep !\n");

    wlan_pm_ack_handle(SLPACK_DEV_DISALLOW, data);

    return SUCCESS;
}

/*****************************************************************************
 函 数 名  : wlan_pm_wakeup_work
 功能描述  : device唤醒host work
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
void wlan_pm_wakeup_work(oal_work_stru *pst_worker)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint l_ret;

    PS_PRINT_DBG("wkupwork!\n");
    OAM_INFO_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_work start!\n");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    l_ret = wlan_pm_wakeup_dev();

#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "<<<< OAL_COMPLETE >>>>t[%d]\n",hmac_wow_get_time());
    OAL_COMPLETE(&pst_wlan_pm->st_resume_done_event);
#endif
    if (OAL_UNLIKELY(OAL_SUCC!=l_ret))
    {
        DECLARE_DFT_TRACE_KEY_INFO("wlan_wakeup_fail",OAL_DFT_TRACE_FAIL);
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

#ifdef _PRE_FEATURE_USB
    /*match for the work submit*/
    oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);
    DECLARE_DFT_TRACE_KEY_INFO("wlan_d2h_wakeup_succ",OAL_DFT_TRACE_SUCC);
    OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_work release wakelock %lu!\n",pst_wlan_pm->pst_usb->st_sdio_wakelock.lock_count);
#else
    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
    DECLARE_DFT_TRACE_KEY_INFO("wlan_d2h_wakeup_succ",OAL_DFT_TRACE_SUCC);
    OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_work release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
#endif
    return;

}

/*****************************************************************************
 函 数 名  : wlan_pm_wakeup_done_callback
 功能描述  : device应答wakeup succ消息处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

int32 wlan_pm_wakeup_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    pst_wlan_pm->ul_wakeup_done_callback++;
    //OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_done_callback cnt:: %u!", g_ul_wkup_ack_cnt);

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]dev ack wakeup success cnt:: %u!", pst_wlan_pm->ul_wakeup_done_callback);

    wlan_pm_wakeup_dev_ack();

    return SUCCESS;

}

/*****************************************************************************
 函 数 名  : wlan_pm_sleep_request
 功能描述  : 发送sleep 请求给device
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SUCC/FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_int32 wlan_pm_sleep_request(struct wlan_pm_s    *pst_wlan_pm)
{
#ifdef _PRE_FEATURE_USB
    return oal_usb_send_msg(pst_wlan_pm->pst_usb, H2D_MSG_SLEEP_REQ);
#else
    return oal_sdio_send_msg(pst_wlan_pm->pst_sdio, H2D_MSG_SLEEP_REQ);
#endif

}

/*****************************************************************************
 函 数 名  : wlan_pm_sleep_work
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef _PRE_FEATURE_USB
    extern volatile int enum_flag_cdce;
#endif
void wlan_pm_sleep_work(oal_work_stru *pst_worker)
{
   struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
   //oal_uint             flags;
   oal_int32           l_ret;
   oal_uint32           ul_ret;
   oal_uint32           ul_wifi_pause_pm = OAL_FALSE;
   oal_spin_lock_stru           pm_spin_lock;
   oal_uint           ul_pm_flags;
#if 0 //1131 debug
   PS_PRINT_DBG("slpwk!\n");
   OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]host sleep work");
    if (OAL_TRUE == g_wlan_pm_switch
    &&  0        == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "wlan_pm_sleep_work, pm_switch[%d],t[%d]\n", pst_wlan_pm->ul_wlan_pm_enable,hmac_wow_get_time());
    }
#endif
    pst_wlan_pm->ul_wdg_timeout_curr_cnt = 0;
    pst_wlan_pm->ul_packet_cnt           = 0;

   hcc_tx_transfer_lock(hcc_get_default_handler());
   PS_PRINT_DBG("slpwk!\n");
   OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]host sleep work");

   if (OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
   {
        PS_PRINT_DBG("pmdisable!\n");
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]pm disable");
        wlan_pm_feed_wdg();
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return ;
   }

   /*协议栈回调获取是否pause低功耗*/
   if (pst_wlan_pm->st_wifi_srv_handler.p_wifi_srv_get_pm_pause_func)
   {
       ul_wifi_pause_pm = pst_wlan_pm->st_wifi_srv_handler.p_wifi_srv_get_pm_pause_func();
   }

   if (OAL_TRUE == ul_wifi_pause_pm)
   {
        wlan_pm_feed_wdg();
        PS_PRINT_DBG("pmpause!\n");
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]scanning, pause pm");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return ;
   }

   if (HOST_ALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
   {
     PS_PRINT_INFO("sleeping,need not do again!\n");
     OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]sleeping,need not do again!");
     wlan_pm_feed_wdg();
     hcc_tx_transfer_unlock(hcc_get_default_handler());
     return ;
   }

#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
   if (FORCE_SLP_STATUS == pst_wlan_pm->ul_slpreq_flag)
   {
        PS_PRINT_INFO("someone force to sleep request, do not need to do this again!\n");
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]someone force to sleep request, do not need to do this again!");
        goto fail_sleep;
   }
#endif
   pst_wlan_pm->ul_slpack = SLPACK_DEV_ALLOW;

   // we may not need this anymore
   OAL_INIT_COMPLETION(&pst_wlan_pm->st_sleep_request_ack);
   pst_wlan_pm->ul_sleep_msg_send_cnt++;
   PS_PRINT_DBG("sendslpmsg!\n");
   OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]send sleep msg!cnt::%u", pst_wlan_pm->ul_sleep_msg_send_cnt);

   pst_wlan_pm->ul_waitting_for_dev_ack++;
   l_ret = wlan_pm_sleep_request(pst_wlan_pm);
   if (OAL_SUCC != l_ret)
   {
      pst_wlan_pm->ul_sleep_fail_request++;
      pst_wlan_pm->ul_waitting_for_dev_ack--;
      OAM_ERROR_LOG0(0, OAM_SF_PWR,"[pm]wlan_pm_sleep_request fail !\n");
      goto fail_sleep;
   }

   ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_sleep_request_ack, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_SLEEP_MSG_WAIT_TIMEOUT));
   if(0 == ul_ret)
   {
       /* 超时处理，拉低gpio通知dev流程完成，再拉高gpio告知dev睡眠失败 */
       oal_spin_lock_init(&pm_spin_lock);
       oal_spin_lock_irq_save(&pm_spin_lock, &ul_pm_flags);
       board_set_wlan_h2d_pm_state(WLAN_PM_SLPREQ_LEVEL);
       board_set_wlan_h2d_pm_state(WLAN_PM_WKUPDEV_LEVEL);
       oal_spin_unlock_irq_restore(&pm_spin_lock, &ul_pm_flags);

       pst_wlan_pm->ul_slpreq_flag = NO_SLPREQ_STATUS;
       pst_wlan_pm->ul_sleep_fail_wait_timeout++;
       PS_PRINT_ERR("wlan_pm_sleep_work wait completion fail \n");
       OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]wlan_pm_sleep_work wait completion fail cnt::%u !\n", pst_wlan_pm->ul_sleep_fail_wait_timeout);
       goto fail_sleep;
   }

       //dev ack allow_slp normally, but ...
   if (SLPACK_DEV_DISALLOW == pst_wlan_pm->ul_slpack) // SLPACK_DEV_ALLOW
   {
       pst_wlan_pm->ul_sleep_fail_forbid++;
       OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]wlan_pm_sleep_work device forbid sleep %ld\n",pst_wlan_pm->ul_slpack);
       DECLARE_DFT_TRACE_KEY_INFO("wlan_forbid_sleep",OAL_DFT_TRACE_SUCC);
       goto fail_sleep;
   }
#ifndef _PRE_FEATURE_USB
   oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_FALSE);
#endif

   pst_wlan_pm->ul_sleep_gpio_low_cnt++;
   PS_PRINT_DBG("gpio low!\n");
   OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]gpio low!cnt::%u", pst_wlan_pm->ul_sleep_gpio_low_cnt);

   pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

   /* 拉低gpio告知dev流程结束并等待dev去读状态 */
   /* when allow_slp ok, make h2d gpio low */
    board_set_wlan_h2d_pm_state(WLAN_PM_SLPREQ_LEVEL);



   wlan_pm_stop_wdg(pst_wlan_pm);
#ifdef _PRE_FEATURE_USB
    oal_uint32           ul_loop = HOST_WAIT_FOR_DEV_DETACH;
    while (ul_loop--)
    {
        if (enum_flag_cdce == 0)
        {
            break;
        }
    }
    if (ul_loop == 0)
    {
        PS_PRINT_INFO("waiting for dev detach failed");
    }
#else
    /* 等待dev读取gpio状态完毕 */
    udelay(65);
#endif

#ifdef _PRE_FEATURE_USB

   oal_sdio_wake_unlock(pst_wlan_pm->pst_usb);

   if(0!=pst_wlan_pm->pst_usb->st_sdio_wakelock.lock_count)
   {
      OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]wlan_pm_sleep_work release wakelock %lu!\n",pst_wlan_pm->pst_usb->st_sdio_wakelock.lock_count);
   }

#else
   oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_ALL);//psm

   oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);

   oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

   if(0!=pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count)
   {
      OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]wlan_pm_sleep_work release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
   }
#endif

   stop_heartbeat();

   hcc_tx_transfer_unlock(hcc_get_default_handler());

   DECLARE_DFT_TRACE_KEY_INFO("wlan_sleep_ok",OAL_DFT_TRACE_SUCC);

   PS_PRINT_DBG("slpok!\n");
   OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]wlan sleep work succ !\n");

   pst_wlan_pm->ul_sleep_succ++;

    return;

fail_sleep:
    wlan_pm_feed_wdg();
    hcc_tx_transfer_unlock(hcc_get_default_handler());
    return ;

}





#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME

/*****************************************************************************
 函 数 名  : wlan_pm_forslp_request
 功能描述  : 发送forcesleep 请求给device
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SUCC/FAIL
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年10月31日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/

oal_int32 wlan_pm_forslp_request(struct wlan_pm_s    *pst_wlan_pm)
{
#ifdef _PRE_FEATURE_USB
    return oal_usb_send_msg(pst_wlan_pm->pst_usb, H2D_MSG_FORCESLP_REQ);
#else
    return oal_sdio_send_msg(pst_wlan_pm->pst_sdio, H2D_MSG_FORCESLP_REQ);
#endif

}

/*****************************************************************************
 函 数 名  : wlan_pm_set_forceslp
 功能描述  : 设置强制睡标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_set_forceslp(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    /* set force slp flag */
    pst_wlan_pm->ul_slpreq_flag = FORCE_SLP_STATUS;
}

/*****************************************************************************
 函 数 名  : wlan_pm_set_forceslp_wakeup
 功能描述  : 强制睡眠唤醒后，设置Host上电标记
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_set_forceslp_wakeup(oal_void)
{
#if 0
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    g_wlan_pm_switch = 1;
    pst_wlan_pm->ul_wlan_pm_enable = OAL_TRUE;
#endif
}

/*****************************************************************************
 函 数 名  : wlan_pm_wakeup_channel
 功能描述  : 唤醒数据通道
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_wakeup_channel(oal_void)
{
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_wakeup_channel::enter, t[%d]\n",hmac_wow_get_time());
    wlan_pm_resume();
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_wakeup_channel::exit, t[%d]\n",hmac_wow_get_time());
}

/*****************************************************************************
 函 数 名  : wlan_pm_forslp_work
 功能描述  : 平台强制睡眠接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
void wlan_pm_forslp_work(oal_work_stru *pst_worker)
{
    oal_uint32           ul_ret;
    oal_int32            l_ret;

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_spin_lock_stru       pm_spin_lock;
    oal_uint                 ul_pm_flags;


    hcc_tx_transfer_lock(hcc_get_default_handler());

    PS_PRINT_DBG("forslpwk!\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]host forcesleep work");

#if 0 //当前强制睡眠不与睡眠标记位复用，两个功能单独调试
    if (OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        PS_PRINT_INFO("pm function disabled!\n");
        goto fail_force_sleep;
    }
#endif
    if (HOST_ALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
    {
        PS_PRINT_INFO("sleeping,do not need again!\n");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return;
    }
    /* stop channel_data_monitor timer */
    wlan_pm_stop_wdg(pst_wlan_pm);

    pst_wlan_pm->ul_slpack = SLPACK_DEV_ALLOW;

    /* send force_slp msg to dev */
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_sleep_request_ack);
    pst_wlan_pm->ul_forslp_msg_send_cnt++;
    PS_PRINT_DBG("sendforslpmsg!\n");
    OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]send force sleep msg!cnt::%u", pst_wlan_pm->ul_forslp_msg_send_cnt);

    pst_wlan_pm->ul_waitting_for_dev_ack++;
    l_ret = wlan_pm_forslp_request(pst_wlan_pm);
    if (OAL_SUCC != l_ret)
    {
       pst_wlan_pm->ul_sleep_fail_request++;
       pst_wlan_pm->ul_waitting_for_dev_ack--;
       OAM_ERROR_LOG0(0, OAM_SF_PWR,"[pm]wlan_pm_forslp_request fail !\n");
       goto fail_force_sleep;
    }

    /* wait for dev's allow_slp ack */
    ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_sleep_request_ack, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_SLEEP_MSG_WAIT_TIMEOUT));
    if (0 == ul_ret)
    {
        /* 超时处理，拉低gpio通知dev流程完成，再拉高gpio告知dev睡眠失败 */
        oal_spin_lock_init(&pm_spin_lock);
        oal_spin_lock_irq_save(&pm_spin_lock, &ul_pm_flags);
        board_set_wlan_h2d_pm_state(WLAN_PM_SLPREQ_LEVEL);
        board_set_wlan_h2d_pm_state(WLAN_PM_WKUPDEV_LEVEL);
        oal_spin_unlock_irq_restore(&pm_spin_lock, &ul_pm_flags);

        pst_wlan_pm->ul_slpreq_flag = NO_SLPREQ_STATUS;
        pst_wlan_pm->ul_sleep_fail_wait_timeout++;
        PS_PRINT_ERR("wlan_pm_forslp_work wait completion fail \n");
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]wlan_pm_forslp_work wait completion fail !\n");
        goto fail_force_sleep;

    }


    pst_wlan_pm->ul_sleep_gpio_low_cnt++;
    PS_PRINT_DBG("gpio low!\n");
    OAM_WARNING_LOG1(0, OAM_SF_PWR,"[pm]gpio low!cnt::%u", pst_wlan_pm->ul_sleep_gpio_low_cnt);

    /* set dev status as sleep */
    pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

    /* 拉低gpio告知dev流程结束并等待dev去读状态 */
    /* when allow_slp ok, make h2d gpio low */
    board_set_wlan_h2d_pm_state(WLAN_PM_SLPREQ_LEVEL);

    /* unset force_slp flag */
    pst_wlan_pm->ul_slpreq_flag = NO_SLPREQ_STATUS;
#ifdef _PRE_FEATURE_USB
    oal_uint32           ul_loop = HOST_WAIT_FOR_DEV_DETACH;
    while (ul_loop--)
    {
        if (enum_flag_cdce == 0)
        {
            break;
        }
    }
    if (ul_loop == 0)
    {
        PS_PRINT_INFO("waiting for dev detach failed");
        goto fail_force_sleep;
    }
#endif

    PS_PRINT_DBG("forslpok!\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]wlan force sleep work succ !\n");

    OAL_COMPLETE(&pst_wlan_pm->st_slpwork_done_event);

    pst_wlan_pm->ul_forslp_succ++;

    host_pow_off();

    /* 不再释放锁，以免 device 被唤醒后无法唤醒 host */
    //hcc_tx_transfer_unlock(hcc_get_default_handler());

fail_force_sleep:
    hcc_tx_transfer_unlock(hcc_get_default_handler());
    wlan_pm_feed_wdg();
    return ;

}


oal_uint wlan_pm_timeout_slp(void)
{
    PS_PRINT_INFO("wlan_pm_timeout_slp>>>>>>>>\n");
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    //PS_PRINT_INFO("pst_wlan_pm->ul_wlan_dev_state = %d", (UINT32)pst_wlan_pm->ul_wlan_dev_state);
     //PS_PRINT_INFO("step2\r\n");
    if (HOST_ALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
    {
        PS_PRINT_INFO("dev has been slp!\n");
        return true;
    }

    //check wifi hmac allow_slp_or_not
    //...
         //PS_PRINT_INFO("step3\r\n");
    if (0 != wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_sleep_work))
    {
        PS_PRINT_INFO("<<<<slp submit fail>>>>\n");
        pst_wlan_pm->ul_sleep_fail_request++;
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_timeout_slp submit slp work fail!\n");
    }
    PS_PRINT_INFO("<<<<waitting evt>>>>\n");
             //PS_PRINT_INFO("step4\r\n");
    ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_slpwork_done_event, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_SLP_MSG_WAIT_TIMEOUT));
    PS_PRINT_INFO("<<<<slp done>>>>\n");
    if (0 == ul_ret)
    {
        PS_PRINT_INFO("wait slp timeout\n");
        return false;
    }
    return true;
}

oal_uint wlan_pm_suspend(void)
{
    PS_PRINT_INFO("wlan_pm_suspend>>>>>>>>\n");
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    //PS_PRINT_INFO("pst_wlan_pm->ul_wlan_dev_state = %d", (UINT32)pst_wlan_pm->ul_wlan_dev_state);

    if (HOST_ALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
    {
        PS_PRINT_INFO("dev has been slp, do not suspend!\n");
        return true;
    }

    //check wifi hmac allow_slp_or_not
    //...
    if (0 != wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_forslp_work))
    {
        PS_PRINT_INFO("<<<<force slp submit fail>>>>\n");
        pst_wlan_pm->ul_forslp_fail_request++;
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_suspend submit force_slp work fail!\n");
    }
    PS_PRINT_INFO("<<<<waitting evt>>>>\n");
             //PS_PRINT_INFO("step4\r\n");
    ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_slpwork_done_event, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_FORSLP_MSG_WAIT_TIMEOUT));
    PS_PRINT_INFO("<<<<force slp done>>>>\n");
    if (0 == ul_ret)
    {
        PS_PRINT_INFO("wait force slp timeout\n");
        return false;
    }

    return true;

}

oal_uint wlan_pm_resume(void)
{
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
    /*若host是睡眠下电后wkup wlan状态应该是open*/

    if (g_ul_wlan_resume_state)
    {
        struct pm_drv_data  *pm_data = pm_get_drvdata();
        pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_OPEN;
    }
#endif
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "<<<<<<<<wlan_pm_resume>>>>>>>>,t[%d]\n",hmac_wow_get_time());
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if (HOST_DISALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
    {
        PS_PRINT_INFO("dev waked, do not resume,t[%d]\n",hmac_wow_get_time());
        return true;
    }
    //OAM_WARNING_LOG0(0, OAM_SF_PWR, "first init\n");
    //SD_MMC_Host_init();
    //OAM_WARNING_LOG0(0, OAM_SF_PWR, "first init ok\n");

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_resume_done_event);
    if (0 != wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_wakeup_work))
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_wkup_dev submit  work fail!\n");
    }

#if 1
    OAM_WARNING_LOG1(0, OAM_SF_PWR, "<<<<wait completion>>>>,t[%d]\n",hmac_wow_get_time());
    ul_ret = oal_wait_for_completion_timeout(&pst_wlan_pm->st_resume_done_event, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_RESUME_WAIT_TIMEOUT));

    if (0 == ul_ret)
    {
        PS_PRINT_INFO("wait wkup_dev resume OK timeout\n");
        return false;
    }
#endif
    OAM_WARNING_LOG2(0, OAM_SF_PWR, "<<<<resume ok>>>> ul_ret[%d],t[%d]\n",ul_ret,hmac_wow_get_time());
    return true;
}



oal_void wlan_pm_check_wakeup_reason(oal_void)
{
    /*醒来读文件系统，判断是wakeUp还是bootUp*/
    if (wake_read_flag() == 1)
    {
        g_ul_wlan_resume_state = 1;
        g_ul_wlan_resume_wifi_init_flag = 1;
        g_ul_wlan_reusme_wifi_mode = REUSME_WIFI_AP;
    }
    else if (wake_read_flag() == 2)
    {
        g_ul_wlan_resume_state = 1;
        g_ul_wlan_resume_wifi_init_flag = 1;
        g_ul_wlan_reusme_wifi_mode = REUSME_WIFI_STA;
    }
    wake_write_flag(0);
}

#endif


/*****************************************************************************
 函 数 名  : wlan_pm_state_get
 功能描述  : 获取pm的sleep状态
 输入参数  :
 输出参数  :
 返 回 值  : 1:allow to sleep; 0:disallow to sleep
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_uint wlan_pm_state_get(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    return pst_wlan_pm->ul_wlan_dev_state;
}

/*****************************************************************************
 函 数 名  : wlan_pm_state_set
 功能描述  : 获取pm的sleep状态
 输入参数  :
 输出参数  :
 返 回 值  : 1:allow to sleep; 0:disallow to sleep
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

oal_void wlan_pm_state_set(struct wlan_pm_s  *pst_wlan_pm,oal_uint ul_state)
{

    pst_wlan_pm->ul_wlan_dev_state = ul_state;

}
/*****************************************************************************
 函 数 名  : wlan_pm_set_timeout
 功能描述  : 睡眠定时器超时时间设置
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  wlan_pm_set_timeout(oal_uint32 ul_timeout)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return ;
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_set_timeout[%d]",ul_timeout);

    pst_wlan_pm ->ul_wdg_timeout_cnt = ul_timeout;

    pst_wlan_pm->ul_wdg_timeout_curr_cnt = 0;

    pst_wlan_pm->ul_packet_cnt = 0;

    wlan_pm_feed_wdg();

}
EXPORT_SYMBOL_GPL(wlan_pm_set_timeout);
/*****************************************************************************
 函 数 名  : wlan_pm_feed_wdg
 功能描述  : 启动50ms睡眠定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void  wlan_pm_feed_wdg(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    pst_wlan_pm->ul_sleep_feed_wdg_cnt++;

    oal_timer_start(&pst_wlan_pm->st_watchdog_timer, WLAN_SLEEP_TIMER_PERIOD);
}


/*****************************************************************************
 函 数 名  : wlan_pm_stop_wdg
 功能描述  : 停止50ms睡眠定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

int32 wlan_pm_stop_wdg(struct wlan_pm_s *pst_wlan_pm_info)
{
    OAL_IO_PRINT("wlan_pm_stop_wdg \r\n");

    pst_wlan_pm_info->ul_wdg_timeout_curr_cnt = 0;
    pst_wlan_pm_info->ul_packet_cnt = 0;

    if (in_interrupt())
    {
        return oal_timer_delete(&pst_wlan_pm_info->st_watchdog_timer);
    }
    else
    {
        return oal_timer_delete_sync(&pst_wlan_pm_info->st_watchdog_timer);
    }

}


/*****************************************************************************
 函 数 名  : wlan_pm_wdg_timeout
 功能描述  : 50ms睡眠定时器超时处理，提交一个sleep work
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/

void wlan_pm_wdg_timeout(struct wlan_pm_s *pm_data)
{
    //OAL_IO_PRINT("wlan_pm_wdg_timeout.... \r\n");
    if (NULL == pm_data)
    {
        return;
    }

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    if (OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_process_func)
    {
        pm_data->ul_packet_cnt += g_pst_alg_process_func.p_auto_freq_process_func();
    }
    else
    {
        OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_wdg_timeout:NO p_auto_freq_process_func registered");
        goto restart_timer;
    }
#endif

    /*和调频共用一个timer，低功耗关闭时timer不会停*/
    if (pm_data->ul_wlan_pm_enable)
    {
#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
        if (FORCE_SLP_STATUS == pm_data->ul_slpreq_flag)
        {
            pm_data->ul_packet_cnt = 0;
            pm_data->ul_wdg_timeout_curr_cnt = 0;
            return;
        }
#endif
        if (0 == pm_data->ul_packet_cnt)
        {
            pm_data->ul_wdg_timeout_curr_cnt++;
            if ((pm_data->ul_wdg_timeout_curr_cnt >= pm_data->ul_wdg_timeout_cnt))
            {
                if(0 != wlan_pm_work_submit(pm_data, &pm_data->st_sleep_work))
                {
                    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_sleep_work submit fail,work is running !\n");
                }
                else
                {
                    /*提交了sleep work后，定时器不重启，避免重复提交sleep work*/
                    pm_data->ul_sleep_work_submit++;
                    return;
                }

            }
        }
        else
        {
            //OAL_IO_PRINT("wlan_pm_wdg_timeout %d have packet %d.... \r\n",pm_data->ul_wdg_timeout_curr_cnt,pm_data->ul_packet_cnt);
            pm_data->ul_wdg_timeout_curr_cnt = 0;
            pm_data->ul_packet_cnt           = 0;
        }

    }
    else
    {
        pm_data->ul_packet_cnt = 0;
    }

restart_timer:
    //OAL_IO_PRINT("wlan_pm_feed_wdg.... \r\n");
    wlan_pm_feed_wdg();


    return;

}


/*****************************************************************************
 函 数 名  : wlan_pm_resume_test
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2016年7月20日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_resume_test(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    if(0 != wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_wakeup_work))
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_resume submit wkup work fail!\n");
    }
    return;
}

/*****************************************************************************
 函 数 名  : wlan_pm_suspend_test
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
oal_void wlan_pm_suspend_test(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    if(0 != wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_sleep_work))
    {
        pst_wlan_pm->ul_sleep_fail_request++;
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_suspend submit slp work fail!\n");
    }
    return;
}



/*****************************************************************************
 函 数 名  : wlan_pm_init
 功能描述  : WLAN PM初始化接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化返回值，成功或失败原因
 调用函数  : 无
 被调函数  : 无

 修改历史      :
  1.日    期   : 2015年5月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
struct wlan_pm_s*  wlan_pm_init(oal_void)
{
    struct wlan_pm_s*   pst_wlan_pm;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    BOARD_INFO *        pst_board = get_board_info();

    if (OAL_PTR_NULL == pst_board)
    {
        return OAL_PTR_NULL;
    }
#endif
    pst_wlan_pm = oal_kzalloc(sizeof(struct wlan_pm_s),OAL_GFP_KERNEL);
    if (NULL == pst_wlan_pm)
    {
        OAL_IO_PRINT("[plat_pm]no mem to allocate wlan_pm_data\n");
        return OAL_PTR_NULL;
    }

    oal_memset(pst_wlan_pm, 0, sizeof(struct wlan_pm_s));

#ifdef _PRE_FEATURE_USB
    pst_wlan_pm->pst_usb                  = oal_get_usb_default_handler();
#else
    pst_wlan_pm->pst_sdio                  = oal_get_sdio_default_handler();

    pst_wlan_pm->pst_sdio->pst_pm_callback = &gst_wlan_pm_callback;
#endif

    /* 默认关低功耗 */
    pst_wlan_pm->ul_wlan_pm_enable          = OAL_FALSE;

    pst_wlan_pm->ul_apmode_allow_pm_flag    = OAL_TRUE;  /* 默认允许下电 */

    /*work queue初始化*/
    pst_wlan_pm->pst_pm_wq = oal_create_singlethread_workqueue("wlan_pm_wq");
    if (!pst_wlan_pm->pst_pm_wq)
    {
        OAL_IO_PRINT("[plat_pm]Failed to create wlan_pm_wq!");
        oal_free(pst_wlan_pm);
        return OAL_PTR_NULL;
    }
    /*register wakeup and sleep work*/
    OAL_INIT_WORK(&pst_wlan_pm->st_wakeup_work, wlan_pm_wakeup_work);
    OAL_INIT_WORK(&pst_wlan_pm->st_sleep_work,  wlan_pm_sleep_work);
    OAL_INIT_WORK(&pst_wlan_pm->st_freq_adjust_work,  wlan_pm_freq_adjust_work);

#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
    /*sleep*/
    OAL_INIT_WORK(&pst_wlan_pm->st_forslp_work,  wlan_pm_forslp_work);
#endif

    /*初始化芯片自检work*/
    OAL_INIT_WORK(&pst_wlan_pm->st_ram_reg_test_work,  wlan_device_mem_check_work);

    /*host2dev gpio初始化为低*/
    board_set_wlan_h2d_pm_state(WLAN_PM_SLPREQ_LEVEL);

    /*sleep timer初始化*/
    oal_timer_init(&pst_wlan_pm->st_watchdog_timer,0,(void *)wlan_pm_wdg_timeout,(unsigned long)pst_wlan_pm);

    pst_wlan_pm->ul_wdg_timeout_cnt            = WLAN_SLEEP_DEFAULT_CHECK_CNT;
    pst_wlan_pm->ul_wdg_timeout_curr_cnt       = 0;
    pst_wlan_pm->ul_packet_cnt                 = 0;

    pst_wlan_pm->ul_wlan_power_state           = POWER_STATE_SHUTDOWN;
    pst_wlan_pm->ul_wlan_dev_state             = HOST_ALLOW_TO_SLEEP; /* 1131C-dbug */
    pst_wlan_pm->ul_slpreq_flag                = NO_SLPREQ_STATUS;
    pst_wlan_pm->ul_slpack                     = SLPACK_DEV_ALLOW;

    pst_wlan_pm->st_wifi_srv_handler.p_wifi_srv_get_pm_pause_func = OAL_PTR_NULL;

    gpst_wlan_pm_info = pst_wlan_pm;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_open_bcpu_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_bcpu_done);
#endif
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_device_ready);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_wakeup_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_sleep_request_ack);

#ifdef _PRE_WLAN_PM_FEATURE_FORCESLP_RESUME
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_slpwork_done_event);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_resume_done_event);
#endif

#ifdef _PRE_FEATURE_USB
    oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_WLAN_READY,wlan_pm_set_device_ready,pst_wlan_pm);
    oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_WAKEUP_SUCC,wlan_pm_wakeup_done_callback,pst_wlan_pm);
    oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_ALLOW_SLEEP,wlan_pm_allow_sleep_callback,pst_wlan_pm);
    oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_DISALLOW_SLEEP,wlan_pm_disallow_sleep_callback,pst_wlan_pm);
#ifdef _PRE_WLAN_FEATURE_WOW
    oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_WOW_WIFI_REDAY,hmac_wow_msg_handle,pst_wlan_pm);
#endif
   // oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_POWEROFF_ACK,wlan_pm_close_done_callback,pst_wlan_pm);
   // oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_OPEN_BCPU_ACK,wlan_pm_open_bcpu_done_callback,pst_wlan_pm);
   // oal_usb_message_register(pst_wlan_pm->pst_usb,USB_D2H_MSG_CLOSE_BCPU_ACK,wlan_pm_close_bcpu_done_callback,pst_wlan_pm);

   // pst_wlan_pm->pst_sdio->gpio_int_count = 0;
    pst_wlan_pm->pst_usb->data_bulk_count = 0;
    pst_wlan_pm->pst_usb->wakeup_int_count = 0;
    pst_wlan_pm->pst_usb->gpio_int_count = 0;
    OAL_IO_PRINT("FBS wlan_pm_init pst_wlan_pm->pst_usb = %x!\r\n",pst_wlan_pm->pst_usb);
#else
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_WLAN_READY,wlan_pm_set_device_ready,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_WAKEUP_SUCC,wlan_pm_wakeup_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_ALLOW_SLEEP,wlan_pm_allow_sleep_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_DISALLOW_SLEEP,wlan_pm_disallow_sleep_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_HEARTBEAT,wlan_pm_heartbeat_callback,pst_wlan_pm);
#ifdef _PRE_WLAN_FEATURE_WOW
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_WOW_WIFI_REDAY,hmac_wow_msg_handle,pst_wlan_pm);
#endif
    // oal_usb_message_register(pst_wlan_pm->pst_usb,D2H_MSG_POWEROFF_ACK,wlan_pm_close_done_callback,pst_wlan_pm);
    // oal_usb_message_register(pst_wlan_pm->pst_usb,D2H_MSG_OPEN_BCPU_ACK,wlan_pm_open_bcpu_done_callback,pst_wlan_pm);
    // oal_usb_message_register(pst_wlan_pm->pst_usb,D2H_MSG_CLOSE_BCPU_ACK,wlan_pm_close_bcpu_done_callback,pst_wlan_pm);

    // pst_wlan_pm->pst_sdio->gpio_int_count = 0;
    //pst_wlan_pm->pst_sdio->data_bulk_count = 0;
    pst_wlan_pm->pst_sdio->data_int_count = 0;
    pst_wlan_pm->pst_sdio->wakeup_int_count = 0;
    pst_wlan_pm->pst_sdio->gpio_int_count = 0;
#endif

    PS_PRINT_DBG("wlan_pm_init ok!\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"[pm]wlan_pm_init ok!\n");
    return  pst_wlan_pm;
}

void wlan_pm_info_clean(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

   // pst_wlan_pm->pst_sdio->gpio_int_count   = 0;
#ifndef _PRE_FEATURE_USB
    pst_wlan_pm->pst_sdio->data_int_count   = 0;
    pst_wlan_pm->pst_sdio->wakeup_int_count = 0;

    pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count = 0;
    pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count = 0;
    pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count = 0;
    pst_wlan_pm->pst_sdio->ul_sdio_suspend               = 0;
    pst_wlan_pm->pst_sdio->ul_sdio_resume                = 0;
#endif
    pst_wlan_pm->ul_wakeup_succ = 0;
    pst_wlan_pm->ul_wakeup_dev_ack = 0;
    pst_wlan_pm->ul_wakeup_done_callback = 0;
    pst_wlan_pm->ul_wakeup_succ_work_submit = 0;
    pst_wlan_pm->ul_wakeup_gpio_up_cnt = 0;
    pst_wlan_pm->ul_waitting_for_dev_ack = 0;
    pst_wlan_pm->ul_wakeup_fail_wait_sdio = 0;
    pst_wlan_pm->ul_wakeup_fail_timeout = 0;
    pst_wlan_pm->ul_wakeup_fail_set_reg = 0;
    pst_wlan_pm->ul_wakeup_fail_submit_work = 0;

    pst_wlan_pm->ul_sleep_succ = 0;
    pst_wlan_pm->ul_sleep_feed_wdg_cnt = 0;
    pst_wlan_pm->ul_wakeup_done_callback = 0;
    pst_wlan_pm->ul_sleep_fail_set_reg = 0;
    pst_wlan_pm->ul_sleep_fail_wait_timeout = 0;
    pst_wlan_pm->ul_sleep_fail_forbid = 0;
    pst_wlan_pm->ul_sleep_work_submit = 0;
    pst_wlan_pm->ul_sleep_msg_send_cnt = 0;
    pst_wlan_pm->ul_sleep_gpio_low_cnt = 0;


    return;

}



