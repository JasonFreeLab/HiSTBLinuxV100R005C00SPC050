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

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
/*****************************************************************************
  1 Header File Including
*****************************************************************************/
//#include <linux/module.h>   /* kernel module definitions */
//#include <linux/init.h>
#include <linux/interrupt.h>

#include <linux/platform_device.h>
#include <linux/kobject.h>
#include <linux/irq.h>
//#include <linux/wakelock.h>

#include <linux/mmc/sdio.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/host.h>
#include <linux/gpio.h>
#include <linux/tty.h>
#include <linux/notifier.h>
#include <linux/suspend.h>

#include "board.h"
#include "plat_type.h"
#include "plat_debug.h"
#include "plat_sdio.h"
#include "plat_firmware.h"
#include "plat_pm.h"
#include "exception_rst.h"

#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"
#include "oal_hcc_host_if.h"
#include "oal_schedule.h"
#include "heartbeat_host.h"


/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
/*
  * Function: suspend_notify
  * Description: suspend notify call back
  * Ruturn: 0 -- success
 **/
static int pf_suspend_notify(struct notifier_block *notify_block,
                unsigned long mode, void *unused)
{

    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return IRQ_NONE;
    }

    switch (mode) {
        case PM_POST_SUSPEND:
            PS_PRINT_INFO("host resume OK!\n");
            break;
        case PM_SUSPEND_PREPARE:
            PS_PRINT_INFO("host suspend now!\n");
            break;
        default:
            break;
    }
    return 0;
}

static struct notifier_block pf_suspend_notifier = {
        .notifier_call = pf_suspend_notify,
        .priority = INT_MIN,
    };

struct pm_drv_data * pm_drv_data_t = NULL;

struct pm_drv_data * pm_get_drvdata(void)
{
	return pm_drv_data_t;
}

static void pm_set_drvdata(struct pm_drv_data * data)
{
	pm_drv_data_t = data;
}


/*****************************************************************************
  3 Function Definition
*****************************************************************************/

/* sensorbub?￡?éμ?oˉêy￡??ˉ????D?ê±ó?à′2é?ˉsensorhubμ?×′ì? */
extern int getSensorMcuMode(void);
extern int get_iomcu_power_state(void);

/*****************************************************************************
 * Prototype    : firmware_download_function
 * Description  : download wlan patch
 * Input        : which_cfg
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : 
 *     Modification : Created function

*****************************************************************************/
int firmware_download_function(uint32 which_cfg)
{
    int32 ret = 0;
    unsigned long long total_time = 0;
    oal_time_t_stru start_time, end_time, trans_time;
    static unsigned long long max_time = 0;
    static unsigned long long count = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    start_time = oal_ktime_get();

    if (which_cfg >= CFG_FILE_TOTAL)
    {
        PS_PRINT_ERR("cfg file index [%d] outof range\n", which_cfg);
        return -FAILURE;
    }

    PS_PRINT_INFO("enter firmware_download_function\n");
    oal_sdio_wake_lock(pm_data->pst_wlan_pm_info->pst_sdio);
    oal_sdio_claim_host(pm_data->pst_wlan_pm_info->pst_sdio);

    wlan_pm_init_dev();

    ret = sdio_reinit();
    if (ret < 0)
    {
        oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
        oal_sdio_wake_unlock(pm_data->pst_wlan_pm_info->pst_sdio);
        PS_PRINT_ERR("sdio reinit failed, ret:%d!\n", ret);
        return -FAILURE;
    }
    PS_PRINT_INFO("firmware_download begin\n");

    ret = firmware_download(which_cfg);
    if (ret < 0)
    {
        oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
        oal_sdio_wake_unlock(pm_data->pst_wlan_pm_info->pst_sdio);
        PS_PRINT_ERR("firmware download fail!\n");
        DECLARE_DFT_TRACE_KEY_INFO("patch_download_fail",OAL_DFT_TRACE_FAIL);
        CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_FIRMWARE_DOWN));
        return -FAILURE;
    }
    DECLARE_DFT_TRACE_KEY_INFO("patch_download_ok",OAL_DFT_TRACE_SUCC);

    oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
    oal_sdio_wake_unlock(pm_data->pst_wlan_pm_info->pst_sdio);

    PS_PRINT_INFO("firmware_download success\n");

    end_time = oal_ktime_get();

    trans_time = oal_ktime_sub(end_time, start_time);
    total_time = (unsigned long long)oal_ktime_to_us(trans_time);

    if (total_time > max_time)
    {
        max_time = total_time;
    }

    count++;
    PS_PRINT_WARNING("download firmware, count [%llu], current time [%llu]us, max time [%llu]us\n", count, total_time, max_time);

    return SUCCESS;
}

int32 wlan_is_shutdown(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return ((POWER_STATE_SHUTDOWN == pm_data->pst_wlan_pm_info->ul_wlan_power_state) ? true : false);
}

int32 wifi_power_fail_process(int32 error)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return WIFI_POWER_FAIL;
    }

    if (error >= WIFI_POWER_ENUM_BUTT)
    {
         PS_PRINT_ERR("error is undefined, error=[%d]\n", error);
         return WIFI_POWER_FAIL;
    }

    PS_PRINT_INFO("wifi power fail, error=[%d]\n", error);

    switch (error)
    {
    case WIFI_POWER_SUCCESS:
        break;

    /*BFGX off，wifi firmware download fail和wait boot up fail，直接返回失败，上层重试，不走DFR*/
    case WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL:
        if(OAL_TRUE == oal_trigger_exception(OAL_TRUE))
        {
            /*exception is processing, can't power off*/
            PS_PRINT_INFO("sdio exception is working\n");
            break;
        }
        PS_PRINT_INFO("set wlan_power_state to shutdown\n");
        oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
        pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
    case WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL:
        PS_PRINT_INFO("wifi power fail: pull down power on gpio\n");
        board_power_off();
        break;
    default:
        PS_PRINT_ERR("error is undefined, error=[%d]\n", error);
        break;
    }

    return WIFI_POWER_FAIL;
}

int32 wlan_power_on(void)
{
    int32  ret;
    int32  error = WIFI_POWER_SUCCESS;
    unsigned long long total_time = 0;
    oal_time_t_stru start_time, end_time, trans_time;
    static unsigned long long max_download_time = 0;
    static unsigned long long num = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    start_time = oal_ktime_get();

    PS_PRINT_INFO("wlan power on!\n");

    if(OAL_TRUE == oal_exception_is_busy())
    {
        DECLARE_DFT_TRACE_KEY_INFO("open_fail_sdio_is_busy", OAL_DFT_TRACE_FAIL);
        return -FAILURE;
    }
#if 1
/* 1131C-debug */
    //if (bfgx_is_shutdown())
    {
        PS_PRINT_SUC("wifi pull up power_on_enable gpio!\n");
        board_power_on();
        DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_by_gpio_ok",OAL_DFT_TRACE_SUCC);

        wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);

        if(WIFI_POWER_SUCCESS == firmware_download_function(WIFI_CFG))
        {
            pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_OPEN;
            oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);
        }
        else
        {
            PS_PRINT_ERR("firmware download fail\n");
            error = WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL;
            goto wifi_power_fail;
        }

        if(!wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
        {
            DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_dev_ready_by_gpio_fail", OAL_DFT_TRACE_FAIL);
            PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!\n", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
            error = WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL;
            CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_WCPU_BOOTUP));
            goto wifi_power_fail;
        }
    }
#else
    oal_enable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);
#endif /* 0 */
    hcc_enable(hcc_get_default_handler(), OAL_TRUE);

    end_time = oal_ktime_get();

    trans_time = oal_ktime_sub(end_time, start_time);
    total_time = (unsigned long long)oal_ktime_to_us(trans_time);

    if (total_time > max_download_time)
    {
        max_download_time = total_time;
    }

    num++;
    PS_PRINT_WARNING("power on, count [%llu], current time [%llu]us, max time [%llu]us\n", num, total_time, max_download_time);

    ret = WIFI_POWER_SUCCESS;
    goto wifi_power_over;

wifi_power_fail: /* 1131C-debug */
    ret = wifi_power_fail_process(error);
wifi_power_over:
    board_set_host_to_dev_gpio_val_high();
    return ret;
}

int32 wlan_power_off(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("wlan power off!\n");
    stop_heartbeat();
	hcc_disable(hcc_get_default_handler(), OAL_TRUE);

    PS_PRINT_INFO("wifi pull down power_on_enable!\n");
    oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_ALL);
    board_power_off();
    DECLARE_DFT_TRACE_KEY_INFO("wlan_poweroff_by_gpio",OAL_DFT_TRACE_SUCC);

    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);

    pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;

    return SUCCESS;
}

extern uint32 g_ulJumpCmdResult;
int32 device_mem_check(unsigned long long *time)
{
    int32 ret = -FAILURE;
    unsigned long long total_time = 0;
    oal_time_t_stru start_time, end_time, trans_time;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    if (NULL == time)
    {
        PS_PRINT_ERR("param time is  NULL!\n");
        return -FAILURE;
    }

    start_time = oal_ktime_get();

    PS_PRINT_INFO("device ram reg test!\n");

    PS_PRINT_SUC("factory ram reg test pull up power_on_enable gpio!\n");
    board_power_on();

    ret = firmware_download_function(RAM_REG_TEST_CFG);
    if (SUCCESS == ret)
    {
        PS_PRINT_INFO("device ram reg test success!\n");
    }
    else
    {
        PS_PRINT_INFO("device ram reg test failed!\n");
    }

    oal_disable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);

    board_power_off();

    end_time = oal_ktime_get();

    trans_time = oal_ktime_sub(end_time, start_time);
    total_time = (unsigned long long)oal_ktime_to_us(trans_time);

    *time = total_time;

    PS_PRINT_SUC("device mem reg test time [%llu]us\n", total_time);

    ret = g_ulJumpCmdResult;
    g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;

    return ret;
}

EXPORT_SYMBOL(device_mem_check);

/*return 1 for wifi power on,0 for off.*/
oal_int32 hi110x_get_wifi_power_stat(oal_void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    return (pm_data->pst_wlan_pm_info->ul_wlan_power_state != POWER_STATE_SHUTDOWN);
}
EXPORT_SYMBOL(hi110x_get_wifi_power_stat);

STATIC int low_power_remove(void)
{
    int ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    unregister_pm_notifier(&pf_suspend_notifier);
    
    wlan_pm_exit();

    /*free platform driver data struct*/
    oal_free(pm_data);

    pm_data = NULL;

    pm_set_drvdata(NULL);

    return ret;
}

STATIC int low_power_probe(void)
{
    int ret = 0;
    struct pm_drv_data  *pm_data = NULL;

    pm_data = oal_memalloc(sizeof(struct pm_drv_data));
    //pm_data = kzalloc(sizeof(struct pm_drv_data), GFP_KERNEL);


    if (NULL == pm_data)
    {
        PS_PRINT_ERR("no mem to allocate pm_data\n");
        goto PMDATA_MALLOC_FAIL;
    }

    pm_data->pst_wlan_pm_info = wlan_pm_init();
    if(0 == pm_data->pst_wlan_pm_info)
    {
        PS_PRINT_ERR("no mem to allocate wlan_pm_info\n");
        goto WLAN_INIT_FAIL;
    }

	pm_data->board					= get_board_info();

    /*init mutex*/
    OAL_MUTEX_INIT(&pm_data->host_mutex);

    /*set driver data*/
    pm_set_drvdata(pm_data);

    /* register host pm */
    ret = register_pm_notifier(&pf_suspend_notifier);
	if (ret < 0)
    {
		PS_PRINT_ERR("%s : register_pm_notifier failed!\n", __func__);
	}

    return OAL_SUCC;


WLAN_INIT_FAIL:
    oal_free(pm_data);
PMDATA_MALLOC_FAIL:
    return -ENOMEM;
}

int low_power_init(void)
{
    int ret = -FAILURE;

	ret = low_power_probe();
    if (SUCCESS != ret)
    {
        PS_PRINT_ERR("low_power_init: low_power_probe fail\n");
    }

     PS_PRINT_INFO("low_power_init: success\n");
    return ret;
}

void  low_power_exit(void)
{
	low_power_remove();
}

#elif (_PRE_OS_VERSION_LITEOS == _PRE_OS_VERSION)
/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include <linux/module.h>   /* kernel module definitions */
#include <linux/init.h>
#include <linux/interrupt.h>
//#include <linux/ktime.h>
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
#endif
//#include <linux/gpio.h>
#include <linux/tty.h>
#include <linux/notifier.h>
//#include <linux/suspend.h>

#include "board.h"
#include "plat_type.h"
#include "plat_debug.h"
#include "plat_sdio.h"
#include "plat_firmware.h"
#include "plat_pm.h"
#include "plat_pm_user_ctrl.h"

#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"
#include "oal_hcc_host_if.h"
#include "oal_schedule.h"

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
#define BIT_1                   (1 << 1)
#define BIT_0                   (1 << 0)

#define MUXCTRL_REG56           (0x0E0)
#define MUXCTRL_REG57           (0x0E4)
#define MUXCTRL_REG56_GPIO7_0   (0)
#define MUXCTRL_REG57_GPIO7_1   (0)


#define GPIO_PIN_0              (BIT_0<<2)
#define GPIO_PIN_1              (BIT_1<<2)
#define MCU_GPIO1               (GPIO7_REG_BASE + GPIO_PIN_0)
#define MCU_GPIO2               (GPIO7_REG_BASE + GPIO_PIN_1)
#define GPIO_DIR                (0x400)

#define WL_EN_GPIO_GROUP        (7)
#define WL_EN_GPIO_PIN          (0)
#define POWER_EN_GPIO_GROUP     (7)
#define POWER_EN_GPIO_PIN       (1)


unsigned int g_ul_wlan_resume_state = 0;
unsigned int g_ul_wlan_resume_wifi_init_flag = 0;
unsigned int g_ul_wlan_reusme_wifi_mode = 0; //0:不启动wifi，1:启动AP，2: 启动 STA

/*
  * Function: suspend_notify
  * Description: suspend notify call back
  * Ruturn: 0 -- success
 **/
struct pm_drv_data * pm_drv_data_t = NULL;

struct pm_drv_data * pm_get_drvdata(void)
{
    return pm_drv_data_t;
}

int32 wlan_is_shutdown(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return ((POWER_STATE_SHUTDOWN == pm_data->pst_wlan_pm_info->ul_wlan_power_state) ? true : false);
}


oal_int32 hi110x_get_wifi_power_stat(oal_void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    return (pm_data->pst_wlan_pm_info->ul_wlan_power_state != POWER_STATE_SHUTDOWN);
}
/*****************************************************************************
 * Prototype    : firmware_download_function
 * Description  : download wlan patch
 * Input        : which_cfg
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : 
 *     Modification : Created function

*****************************************************************************/
int firmware_download_function(uint32 which_cfg)
{
    int32 ret = 0;
    unsigned long long total_time = 0;
    ktime_t start_time, end_time, trans_time;
    static unsigned long long max_time = 0;
    static unsigned long long count = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    start_time = oal_ktime_get();

    if (which_cfg >= CFG_FILE_TOTAL)
    {
        PS_PRINT_ERR("cfg file index [%d] outof range\n", which_cfg);
        return -FAILURE;
    }

    PS_PRINT_INFO("enter firmware_download_function\n");
#if 0
    /*firmware_cfg_init(sdio) function should just be called once*/
    if (!test_bit(FIRMWARE_CFG_INIT_OK, &pm_data->firmware_cfg_init_flag))
    {
        PS_PRINT_ERR("firmware_cfg_init begin\n");
        ret = firmware_cfg_init();
        if (ret)
        {
            PS_PRINT_ERR("firmware_cfg_init failed, ret:%d!\n", ret);
            return ret;
        }

        PS_PRINT_INFO("firmware_cfg_init OK\n");
        set_bit(FIRMWARE_CFG_INIT_OK, &pm_data->firmware_cfg_init_flag);
    }

    oal_sdio_claim_host(pm_data->pst_wlan_pm_info->pst_sdio);

    ret = sdio_reinit();
    if (ret < 0)
    {
        oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
        PS_PRINT_ERR("sdio reinit failed, ret:%d!\n", ret);
        return -FAILURE;
    }
#endif
    wlan_pm_init_dev();

    PS_PRINT_INFO("firmware_download begin\n");

    ret = firmware_download(which_cfg);
    if (ret < 0)
    {
#ifndef _PRE_FEATURE_USB
     oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
#endif
        PS_PRINT_ERR("firmware download fail!\n");
        DECLARE_DFT_TRACE_KEY_INFO("patch_download_fail",OAL_DFT_TRACE_FAIL);
        return -FAILURE;
    }
    DECLARE_DFT_TRACE_KEY_INFO("patch_download_ok",OAL_DFT_TRACE_SUCC);
#ifndef _PRE_FEATURE_USB
     oal_sdio_release_host(pm_data->pst_wlan_pm_info->pst_sdio);
#endif

    PS_PRINT_INFO("firmware_download success\n");

    end_time = oal_ktime_get();

    trans_time = oal_ktime_sub(end_time, start_time);
    total_time = (unsigned long long)oal_ktime_to_us(trans_time);

    if (total_time > max_time)
    {
        max_time = total_time;
    }

    count++;
    PS_PRINT_WARNING("download firmware, count [%llu], current time [%llu]us, max time [%llu]us\n", count, total_time, max_time);

    return SUCCESS;
}
int32 bfgx_is_shutdown(void)
{
#if 0
    struct ps_core_s *ps_core_d = NULL;

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    return ps_chk_bfg_active(ps_core_d) ? false : true;
#else
    return 1;
#endif
}

int32 wifi_power_fail_process(int32 error)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return WIFI_POWER_FAIL;
    }

    if (error >= WIFI_POWER_ENUM_BUTT)
    {
         PS_PRINT_ERR("error is undefined, error=[%d]\n", error);
         return WIFI_POWER_FAIL;
    }

    PS_PRINT_INFO("wifi power fail, error=[%d]\n", error);

    switch (error)
    {
    case WIFI_POWER_SUCCESS:
    case WIFI_POWER_PULL_POWER_GPIO_FAIL:
        break;

    /*BFGX off，wifi firmware download fail和wait boot up fail，直接返回失败，上层重试，不走DFR*/
    case WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL:
        PS_PRINT_INFO("bfgx off,set wlan_power_state to shutdown\n");
#if 0
        oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
#endif
        pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
    case WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL:
        PS_PRINT_INFO("wifi power fail: pull down power on gpio\n");
#if 0
        board_power_off();
#endif
        break;

    /*BFGX on，wifi上电失败，进行全系统复位，wifi本次返回失败，上层重试*/
    case WIFI_POWER_BFGX_ON_BOOT_UP_FAIL:
        PS_PRINT_INFO("bfgx on,set wlan_power_state to shutdown\n");
#if 0
        oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
#endif
        pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
    case WIFI_POWER_BFGX_DERESET_WCPU_FAIL:
    case WIFI_POWER_BFGX_ON_FIRMWARE_DOWNLOAD_FAIL:
#if 0
        if (WIFI_POWER_SUCCESS == plat_power_fail_exception_info_set(SUBSYS_WIFI, THREAD_WIFI, WIFI_POWER_ON_FAIL))
        {
            bfgx_system_reset();
            plat_power_fail_process_done();
        }
        else
        {
            PS_PRINT_ERR("wifi power fail, set exception info fail\n");
        }
#else
        PS_PRINT_ERR("wifi power fail, set exception info fail\n");
#endif
        break;

    default:
        PS_PRINT_ERR("error is undefined, error=[%d]\n", error);
        break;
    }

    return WIFI_POWER_FAIL;
}
int32 wlan_power_on(void)
{
    int32  error = WIFI_POWER_SUCCESS;
    unsigned long long total_time = 0;
    ktime_t start_time, end_time, trans_time;
    static unsigned long long max_download_time = 0;
    static unsigned long long num = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    start_time = oal_ktime_get();

    PS_PRINT_INFO("wlan power on!\n");
#ifdef _PRE_WLAN_FEATURE_DATA_BACKUP
/*无镜像备份host下电唤醒后不给dev上下电*/
dprintf("g_ul_wlan_resume_state_ 2 = %d", g_ul_wlan_resume_state);
    if (!g_ul_wlan_resume_state)
    {
        wlan_pm_init_dev();
#ifdef _PRE_FEATURE_USB
        wlan_power_on_usb();
        printf("power on wlan in usb platform\r\n");
#else
        if (SUCC != wlan_power_on_sdio())
        {
            printf("wlan_power_on_sdio failed\r\n");
            return -FAILURE;
        }
#endif
    }
#else
/*正常host上电流程，给device上下电走firmware download*/
#ifdef _PRE_FEATURE_USB
        wlan_power_on_usb();
        printf("power on wlan in usb platform\r\n");
#else
        if (SUCC != wlan_power_on_sdio())
        {
            printf("wlan_power_on_sdio failed\r\n");
            return -FAILURE;
        }
#endif
#endif

#if 0
    if (bfgx_is_shutdown())
    {
        PS_PRINT_SUC("wifi pull up power_on_enable gpio!\n");
#if 0
        board_power_on();
#endif
        DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_by_gpio_ok",OAL_DFT_TRACE_SUCC);

        wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);

        if (WIFI_POWER_SUCCESS == firmware_download_function(BFGX_AND_WIFI_CFG))
        {
            pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_OPEN;
#if 0
            oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);
#endif
        }
        else
        {
            PS_PRINT_ERR("firmware download fail\n");
            error = WIFI_POWER_BFGX_OFF_FIRMWARE_DOWNLOAD_FAIL;
            goto wifi_power_fail;
        }

        if (!wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
        {
            DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_dev_ready_by_gpio_fail", OAL_DFT_TRACE_FAIL);
            PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!\n", HOST_WAIT_BOTTOM_INIT_TIMEOUT);
            error = WIFI_POWER_BFGX_OFF_BOOT_UP_FAIL;
            goto wifi_power_fail;
        }
    }
    else
    {
#if 0
        if (WIFI_POWER_SUCCESS != uart_wifi_open())
        {
            DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_by_uart_fail", OAL_DFT_TRACE_FAIL);
            error = WIFI_POWER_BFGX_DERESET_WCPU_FAIL;
            goto wifi_power_fail;
        }
        else
        {
            wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);
            if (WIFI_POWER_SUCCESS == firmware_download_function(WIFI_CFG))
            {
                pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_OPEN;
                oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_TRUE);
            }
            else
            {
                PS_PRINT_ERR("firmware download fail\n");
                error = WIFI_POWER_BFGX_ON_FIRMWARE_DOWNLOAD_FAIL;
                goto wifi_power_fail;
            }

            if (!wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
            {
                DECLARE_DFT_TRACE_KEY_INFO("wlan_poweron_dev_ready_by_uart_fail",OAL_DFT_TRACE_FAIL);
                PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!",HOST_WAIT_BOTTOM_INIT_TIMEOUT);
                error = WIFI_POWER_BFGX_ON_BOOT_UP_FAIL;
                goto wifi_power_fail;
            }
        }
#endif
    }
#if 0/* 1131C-debug */
    oal_enable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);
#endif /* 0 */
#endif
    pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_OPEN;


    end_time = oal_ktime_get();

    trans_time = oal_ktime_sub(end_time, start_time);
    total_time = (unsigned long long)oal_ktime_to_us(trans_time);

    if (total_time > max_download_time)
    {
        max_download_time = total_time;
    }

    num++;
    PS_PRINT_WARNING("power on, count [%llu], current time [%llu]us, max time [%llu]us\n", num, total_time, max_download_time);

    return WIFI_POWER_SUCCESS;

wifi_power_fail: /* 1131C-debug */
    return wifi_power_fail_process(error);
}

int32 wlan_power_off(void)
{
#ifdef _PRE_FEATURE_USB
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("wlan power off!\n");

    hcc_disable(hcc_get_default_handler(), OAL_TRUE);

    board_power_off();

    DECLARE_DFT_TRACE_KEY_INFO("wlan_poweroff_by_bcpu_ok",OAL_DFT_TRACE_SUCC);

    //oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);

    pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;

    return SUCCESS;
#else

    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("wlan power off!\n");

    hcc_disable(hcc_get_default_handler(), OAL_TRUE);

    /*先关闭SDIO TX通道*/
    oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_TX);

    board_power_off();
    oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_ALL);

    DECLARE_DFT_TRACE_KEY_INFO("wlan_poweroff_by_bcpu_ok",OAL_DFT_TRACE_SUCC);

    oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);

    pm_data->pst_wlan_pm_info->ul_wlan_power_state = POWER_STATE_SHUTDOWN;

    return SUCCESS;

#endif

}
extern uint32 g_ulJumpCmdResult;
int32 device_mem_check(unsigned long long *time)
{
    int32 ret = -FAILURE;
    unsigned long long total_time = 0;
    ktime_t start_time, end_time, trans_time;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    if (NULL == time)
    {
        PS_PRINT_ERR("param time is  NULL!\n");
        return -FAILURE;
    }

    start_time = oal_ktime_get();

    PS_PRINT_INFO("device ram reg test!\n");

    if (bfgx_is_shutdown())
    {
        PS_PRINT_SUC("factory ram reg test pull up power_on_enable gpio!\n");
#if 0
        board_power_on();
#endif
    }
    else
    {
        PS_PRINT_ERR("device mem check:bfgx must be shutdown!\n");
        return ret;
    }
#if 0
    ret = firmware_download_function(RAM_REG_TEST_CFG);
    if (SUCCESS == ret)
    {
        PS_PRINT_INFO("device ram reg test success!\n");
    }
    else
    {
        PS_PRINT_INFO("device ram reg test failed!\n");
    }
#endif
#ifndef _PRE_FEATURE_USB
    oal_disable_sdio_state(pm_data->pst_wlan_pm_info->pst_sdio, OAL_SDIO_ALL);
#endif

#if 0
    board_power_off();
#endif
    end_time = oal_ktime_get();

    trans_time = oal_ktime_sub(end_time, start_time);
    total_time = (unsigned long long)oal_ktime_to_us(trans_time);

    *time = total_time;

    PS_PRINT_SUC("device mem reg test time [%llu]us\n", total_time);

    ret = g_ulJumpCmdResult;
    g_ulJumpCmdResult = CMD_JUMP_EXEC_RESULT_SUCC;

    return ret;
}
STATIC int low_power_remove(void)
{
    int ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    wlan_pm_exit();

    /*remove kobject*/
    pm_user_ctrl_exit();

    /*delete timer*/
    del_timer_sync(&pm_data->bfg_timer);
    del_timer_sync(&pm_data->dev_ack_timer);

    /*destory wake lock*/
    wake_lock_destroy(&pm_data->bfg_wake_lock);

    /*free platform driver data struct*/
    kfree(pm_data);

    pm_data = NULL;

    pm_set_drvdata(NULL);

    return ret;
}

static void pm_set_drvdata(struct pm_drv_data * data)
{
    pm_drv_data_t = data;
}

STATIC int low_power_probe(void)
{

    int ret = 0;
    struct pm_drv_data  *pm_data = NULL;
    struct workqueue_struct * host_wkup_dev_workq = NULL;

    pm_data = zalloc(sizeof(struct pm_drv_data));
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("no mem to allocate pm_data\n");
        goto PMDATA_MALLOC_FAIL;
    }

    pm_data->pst_wlan_pm_info = wlan_pm_init();
    if (0 == pm_data->pst_wlan_pm_info)
    {
        PS_PRINT_ERR("no mem to allocate wlan_pm_info\n");
        goto WLAN_INIT_FAIL;
    }
    pm_set_drvdata(pm_data);
#if 0
    pm_data->firmware_cfg_init_flag  = 0;
    pm_data->rcvdata_bef_devack_flag = 0;
    pm_data->bfgx_dev_state         = BFGX_SLEEP;
    pm_data->bfgx_pm_ctrl_enable    = BFGX_PM_DISABLE;
    pm_data->bfgx_lowpower_enable   = BFGX_PM_ENABLE;            /* enable host low_power function defaultly */
    pm_data->bfgx_bt_lowpower_enable   = BFGX_PM_ENABLE;
    pm_data->bfgx_gnss_lowpower_enable = BFGX_PM_ENABLE;
    pm_data->bfgx_nfc_lowpower_enable  = BFGX_PM_DISABLE;

    atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    /* create an ordered workqueue with @max_active = 1 & WQ_UNBOUND flag to wake up device */
#if 0

    host_wkup_dev_workq = create_singlethread_workqueue("wkup_dev_workqueue");
    if (!host_wkup_dev_workq)
    {
        PS_PRINT_ERR("create wkup workqueue failed\n");
        goto CREATE_WORKQ_FAIL;
    }
#endif
    pm_data->wkup_dev_workqueue = host_wkup_dev_workq;
#if 0
    INIT_WORK(&pm_data->wkup_dev_work, host_wkup_dev_work);
    INIT_WORK(&pm_data->send_disallow_msg_work, host_send_disallow_msg);

    pm_data->board                  = get_board_info();
#endif
    //printf("#######000000002########\n");

   // pm_data->bfg_irq = pm_data->board->bfgn_irq;

    /*init bfg wake lock */
  //  wake_lock_init(&pm_data->bfg_wake_lock, WAKE_LOCK_SUSPEND, BFG_LOCK_NAME);
    //printf("#######000000003########\n");
#if 0

    /*init mutex*/
    mutex_init(&pm_data->host_mutex);

    //printf("#######000000004########\n");
    /*init spinlock*/
    spin_lock_init(&pm_data->node_timer_spinlock);

    //printf("#######000000005########\n");

    /* init timer */
    init_timer(&pm_data->dev_ack_timer);

    //printf("#######000000006########\n");

    pm_data->dev_ack_timer.function = devack_timer_expire;
    pm_data->dev_ack_timer.data     = (unsigned long)pm_data;
    //printf("#######000000007########!!!\n");
    /* init bfg data timer */
    init_timer(&pm_data->bfg_timer);
    #if 0
    pm_data->bfg_timer.function = bfg_timer_expire;
    #endif
    pm_data->bfg_timer.data     = (unsigned long)pm_data;
 #endif
    //printf("#######000000008########!!!\n");

    /* init completion */
    init_completion(&pm_data->host_wkup_dev_comp);
    init_completion(&pm_data->dev_ack_comp);
    init_completion(&pm_data->dev_bootok_ack_comp);
    //printf("#######000000009########!!!\n");

    /*set driver data*/
    pm_set_drvdata(pm_data);
    //printf("#######0000000010########!!!\n");
#if 0
    ret = pm_user_ctrl_init();
    if (ret)
    {
        PS_PRINT_ERR("failed to create power properties!\n");
        goto PM_USER_CTL_FAIL;
    }

    /* register host pm */
    ret = register_pm_notifier(&pf_suspend_notifier);
    if (ret < 0)
    {
        PS_PRINT_ERR("%s : register_pm_notifier failed!\n", __func__);
    }
#endif
#endif
    return OAL_SUCC;

PM_USER_CTL_FAIL:

CREATE_WORKQ_FAIL:

WLAN_INIT_FAIL:
    kfree(pm_data);
PMDATA_MALLOC_FAIL:
    return -ENOMEM;
}

int low_power_init(void)
{
    int ret = -FAILURE;

    ret = low_power_probe();
    if (SUCCESS != ret)
    {
        PS_PRINT_ERR("low_power_init: low_power_probe fail\n");
    }

     PS_PRINT_INFO("low_power_init: success\n");
    return ret;
}

void  low_power_exit(void)
{
    low_power_remove();
    firmware_cfg_clear();
}

EXPORT_SYMBOL(device_mem_check);

#endif
