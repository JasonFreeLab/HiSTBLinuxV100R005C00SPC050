/******************************************************************************

          Copyright (C), 2001-2011, Hisilicon technology limited company

 ******************************************************************************
  Filename   : user_ctrl.c
  Version    : first draft
  Author     : 
  Create date: 2012-10-11
  Modify     :
  Func descr : bfgx sys file inode user ctrl
  Func list  :
  Modi histoy:
  1.Data     : 2015-04-11
    Author   : 
    Modify
    content  : Create File

******************************************************************************/

/*****************************************************************************
  1 Include Head file
*****************************************************************************/
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include "plat_debug.h"
#include "plat_pm.h"
#include "exception_rst.h"
#include "oneimage.h"
#include "oal_kernel_file.h"
#include "oal_sdio_host_if.h"
#include "plat_pm_wlan.h"
#include "hisi_ini.h"
#include "heartbeat_host.h"
#include "user_ctrl.h"


/*****************************************************************************
  2 Define global variable
*****************************************************************************/
#define CMD_NUM_HEAD            (0x5A << 8)
#define GET_CMD_NUM(cmd)        (cmd & 0xFF)
#define GET_CMD_HEAD(cmd)       (cmd & (~0xFF))

struct kobject *g_sysfs_hi110x_bfgx    = NULL;
struct kobject *g_sysfs_hisi_pmdbg     = NULL;
struct platform_device *hw_ps_device = NULL;

#ifdef PLATFORM_DEBUG_ENABLE
struct kobject *g_sysfs_hi110x_debug   = NULL;
int32 g_uart_rx_dump  = UART_DUMP_CLOSE;
#endif


int32 g_plat_loglevel = PLAT_LOG_DEBUG;
int32 g_bug_on_enable = BUG_ON_DISABLE;
module_param(g_plat_loglevel,int,S_IRUGO | S_IWUSR);

#define DTS_COMP_HI1101_PS_NAME     "hisilicon,hisi_bfgx"


extern int isAsic(void);

/*****************************************************************************
  3 Function implement
*****************************************************************************/

STATIC ssize_t show_wifi_pmdbg(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
   struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();
   oal_int32         ret = 0;

   if (NULL == buf)
   {
      PS_PRINT_ERR("buf is NULL\n");
      return -FAILURE;
   }

#ifdef PLATFORM_DEBUG_ENABLE
   ret += snprintf(buf + ret , PAGE_SIZE - ret, "wifi_pm_debug usage: \n"
                       " 1:dump host info 2:dump device info\n"
                       " 3:open wifi      4:close wifi \n"
                       " 5:enable pm      6:disable pm \n");
#else
  ret += snprintf(buf + ret , PAGE_SIZE - ret, "wifi_pm_debug usage: \n"
                       " 1:dump host info 2:dump device info\n");
#endif

   ret += wlan_pm_host_info_print(pst_wlan_pm, buf + ret, PAGE_SIZE - ret);

   return ret;
}

#ifdef PLATFORM_DEBUG_ENABLE
extern oal_uint wlan_pm_suspend_test(void);
extern oal_uint wlan_pm_resume_test(void);
oal_uint ul_test_count = 0;
OAL_STATIC oal_void pm_gpio_wkup_deepsleep_test(oal_void)
{
    oal_uint32 ul_loop = 0xffffffff;
    while (ul_loop--)
    {
        ul_test_count++;
        printk("test count::%lu\r\n", ul_test_count);
        printk("<<<<<<<<<<<<step1>>>>>>>>>>>>\r\n");
        wlan_pm_suspend_test();

        //msleep(1);
        printk("<<<<<<<<<<<<step2>>>>>>>>>>>>\r\n");
        wlan_pm_resume_test();

        msleep(100);
    }
}


OAL_STATIC oal_void pm_dev_wkup_host_test(oal_void)
{
    oal_uint32 ul_loop = 0xffffffff;
    while (ul_loop--)
    {
        ul_test_count++;
        printk("test count::%lu\r\n", ul_test_count);
        printk("<<<<<<<<<<<<step1>>>>>>>>>>>>\r\n");
        wlan_pm_suspend_test();
        msleep(10);
    }
}
#endif
STATIC ssize_t store_wifi_pmdbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();
    int input = 0;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    input = oal_atoi(buf);

    if (NULL == pst_wlan_pm)
    {
        OAL_IO_PRINT("pm_data is NULL!\n");
        return -FAILURE;
    }

    switch(input)
    {
       case 1:
        wlan_pm_dump_host_info();
       break;
       case 2:
        wlan_pm_dump_device_info();
       break;
#ifdef PLATFORM_DEBUG_ENABLE
       case 3:
        wlan_pm_open();
       break;
       case 4:
        wlan_pm_close();
       break;
       case 5:
        wlan_pm_enable();
       break;
       case 6:
        wlan_pm_disable();
       break;
       case 7:
        wlan_pm_suspend_test();
       break;
       case 8:
        wlan_pm_resume_test();
       break;
       case 9:
       {
           OAL_IO_PRINT("ctrl pm wkdptest!\n");
           pm_gpio_wkup_deepsleep_test();
       }
       case 10:
       {
           OAL_IO_PRINT("ctrl pm dwkuphtest!\n");
           pm_dev_wkup_host_test();
       }
#endif
       default:
       break;
    }

    return count;
}

STATIC struct kobj_attribute wifi_pmdbg =
__ATTR(wifi_pm, 0644, (void *)show_wifi_pmdbg, (void *)store_wifi_pmdbg);


STATIC struct attribute *pmdbg_attrs[] = {
        &wifi_pmdbg.attr,
        NULL,
};

STATIC struct attribute_group pmdbg_attr_grp = {
    .attrs = pmdbg_attrs,
};

/* functions called from subsystems */
/* called by octty from hal to decide open or close uart */
STATIC ssize_t show_install(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
#if 0
    struct ps_plat_s *pm_data = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return sprintf(buf, "%d\n", pm_data->ldisc_install);
#endif
    return 0;
}
#if 0

/* read by octty from hal to decide open which uart */
STATIC ssize_t show_dev_name(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{

    struct ps_plat_s *pm_data = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return sprintf(buf, "%s\n", pm_data->dev_name);

}
#endif
#if 0

/* read by octty from hal to decide whether or not use flow cntrl */
STATIC ssize_t show_flow_cntrl(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{

    struct ps_plat_s *pm_data = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    pm_data = dev_get_drvdata(&hw_ps_device->dev);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return sprintf(buf, "%d\n", pm_data->flow_cntrl);

}
#endif

STATIC ssize_t show_ini_file_name(struct device *dev, struct kobj_attribute *attr, char *buf)
{
    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return snprintf(buf, INI_FILE_PATH_LEN, "%s", g_ini_file_name);
}

STATIC ssize_t show_country_code(struct device *dev, struct kobj_attribute *attr, char *buf)
{
    int8 *country_code = NULL;
    int ret;
    int8 ibuf[COUNTRY_CODE_LEN];

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    country_code = hwifi_get_country_code();
    if (strncmp(country_code, "99", strlen("99")) == 0)
    {
        ret = get_cust_conf_string(CUST_MODU_WIFI, "country_code", ibuf, sizeof(ibuf));
        if (ret == INI_SUCC)
        {
            strncpy(buf, ibuf, COUNTRY_CODE_LEN);
            buf[COUNTRY_CODE_LEN-1] = '\0';
            return strlen(buf);
        }
        else
        {
            PS_PRINT_ERR("get dts country_code error\n");
            return 0;
        }
    }
    else
    {
        return snprintf(buf, COUNTRY_CODE_LEN, "%s", country_code);
    }
}

STATIC ssize_t show_wifi_exception_count(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: wifi rst count is %d\n", pst_exception_data->wifi_exception_cnt);
    return sprintf(buf, "%d\n", pst_exception_data->wifi_exception_cnt);
}

STATIC ssize_t show_loglevel(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return sprintf(buf, "curr loglevel=%d, curr bug_on=%d\nalert:0\nerr:1\nwarning:2\nfunc|succ|info:3\ndebug:4\nbug_on enable:b\nbug_on disable:B\n", g_plat_loglevel, g_bug_on_enable);
}

STATIC ssize_t store_loglevel(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 loglevel = PLAT_LOG_INFO;

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    /*bug on set*/
    if ('b' == *buf)
    {
        g_bug_on_enable = BUG_ON_ENABLE;
        PS_PRINT_INFO("BUG_ON enable sucess, g_bug_on_enable = %d\n", g_bug_on_enable);
        return count;
    }
    else if ('B' == *buf)
    {
        g_bug_on_enable = BUG_ON_DISABLE;
        PS_PRINT_INFO("BUG_ON disable sucess, g_bug_on_enable = %d\n", g_bug_on_enable);
        return count;
    }

    loglevel = simple_strtol(buf, NULL, 10);
    if(PLAT_LOG_ALERT > loglevel)
    {
        g_plat_loglevel = PLAT_LOG_ALERT;
    }
    else if(PLAT_LOG_DEBUG < loglevel)
    {
        g_plat_loglevel = PLAT_LOG_DEBUG;
    }
    else
    {
        g_plat_loglevel = loglevel;
    }

    return count;
}


/* structures specific for sysfs entries */
STATIC struct kobj_attribute ldisc_install =
__ATTR(install, 0444, (void *)show_install, NULL);

STATIC struct kobj_attribute ini_file_name =
__ATTR(ini_file_name, 0444, (void *)show_ini_file_name, NULL);

STATIC struct kobj_attribute country_code =
__ATTR(country_code, 0444, (void *)show_country_code, NULL);

STATIC struct kobj_attribute wifi_rst_count =
__ATTR(wifi_rst_count, 0444, (void *)show_wifi_exception_count, NULL);


STATIC struct kobj_attribute loglevel =
__ATTR(loglevel, 0664, (void *)show_loglevel, (void *)store_loglevel);

#ifdef CONFIG_HI1102_PLAT_HW_CHR
extern ssize_t show_chr_log_switch(struct device *dev, struct kobj_attribute *attr, int8 *buf);
extern ssize_t store_chr_log_switch(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count);
static struct kobj_attribute chr_log_switch =
    __ATTR(chr_log_switch, 0644, (void *)show_chr_log_switch, (void *)store_chr_log_switch);

extern ssize_t show_chr_log_stat_info(struct device *dev, struct kobj_attribute *attr, int8 *buf);
static struct kobj_attribute chr_log_stat =
    __ATTR(chr_log_stat, 0444, (void *)show_chr_log_stat_info, (void *)0);
#endif

STATIC struct attribute *bfgx_attrs[] = {
        &ldisc_install.attr,
        &ini_file_name.attr,
        &country_code.attr,
        &wifi_rst_count.attr,
        &loglevel.attr,
#ifdef CONFIG_HI1102_PLAT_HW_CHR
        &chr_log_switch.attr,
        &chr_log_stat.attr,
#endif
        NULL,
};

STATIC struct attribute_group bfgx_attr_grp = {
    .attrs = bfgx_attrs,
};

#ifdef PLATFORM_DEBUG_ENABLE
STATIC ssize_t show_exception_dbg(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return sprintf(buf, "cmd  func             \n"
                        " 1  close bt          \n"
                        " 2  set beat flat to 0\n");
}

STATIC ssize_t store_exception_dbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
#if 0
    int32  cmd = 0;
    int32  ret = 0;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return 0;
    }

    cmd = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("cmd:%d\n", cmd);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    switch (cmd)
    {
        case 1:
            PS_PRINT_INFO("exception debug test: close BT\n");
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_BT);
            break;

        case 2:
            PS_PRINT_INFO("exception: set debug beat flag to 0\n");
            pst_exception_data->debug_beat_flag = 0;
            break;

        default:
            PS_PRINT_ERR("unknown cmd %d\n", cmd);
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
#endif
    return 0;
}

STATIC ssize_t show_uart_rx_dump(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return sprintf(buf, "curr uart dump status =%d\n no:0\n yes:1\n", g_uart_rx_dump);
}

STATIC ssize_t store_uart_rx_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    g_uart_rx_dump = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("g_uart_rx_dump aft %d\n", g_uart_rx_dump);
    return count;
}

STATIC ssize_t show_dev_test(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return sprintf(buf, "cmd  func\n  1  cause bfgx into panic\n  2  enable exception recovery\n  3  enable wifi open bcpu\n"
                                   "  4  pull up power gpio   \n  5  pull down power gpio     \n  6  uart loop test       \n");
}

extern int32 uart_loop_test(void);
STATIC ssize_t store_dev_test(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    //int32 ret;
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    cmd = simple_strtol(buf, NULL, 10);
    switch (cmd)
    {
        case 2:
            PS_PRINT_INFO("cmd %d,enable platform dfr\n", cmd);
            pst_exception_data->exception_reset_enable = PLAT_EXCEPTION_ENABLE;
            break;
        case 4:
            PS_PRINT_INFO("cmd %d,test pull up power gpio\n", cmd);
            board_power_on();
            break;
        case 5:
            PS_PRINT_INFO("cmd %d,test pull down power gpio\n", cmd);
            board_power_off();
            break;

        default:
            PS_PRINT_ERR("unknown cmd %d\n", cmd);
            break;
    }

    return count;
}

STATIC ssize_t show_wifi_mem_dump(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return sprintf(buf, "cmd         func             \n"
                        " 1    uart halt wcpu         \n"
                        " 2    uart read wifi pub reg \n"
                        " 3    uart read wifi priv reg\n"
                        " 4    uart read wifi mem     \n"
                        " 5    equal cmd 1+2+3+4      \n");
}

STATIC ssize_t store_wifi_mem_dump(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
#if 0
    int32 cmd;
    int32 ret;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        return ret;
    }

    cmd = simple_strtol(buf, NULL, 10);
    switch (cmd)
    {
#if 0
        case 1:
            PS_PRINT_INFO("wifi mem dump cmd %d, halt wcpu\n", cmd);
            uart_halt_wcpu();
            break;
        case 2:
            PS_PRINT_INFO("wifi mem dump cmd %d, read wifi public register\n", cmd);
            uart_read_wifi_mem(WIFI_PUB_REG);
            break;
        case 3:
            PS_PRINT_INFO("wifi mem dump cmd %d, read wifi priv register\n", cmd);
            uart_read_wifi_mem(WIFI_PRIV_REG);
            break;
        case 4:
            PS_PRINT_INFO("wifi mem dump cmd %d, read wifi mem\n", cmd);
            uart_read_wifi_mem(WIFI_MEM);
            break;
        case 5:
            PS_PRINT_INFO("wifi mem dump cmd %d\n", cmd);
            debug_uart_read_wifi_mem(1);
            break;
#endif
        default:
            PS_PRINT_ERR("error cmd:[%d]\n", cmd);
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
    #endif
    return 0;
}
#if 0
/*****************************************************************************
 函 数 名  : show_dump
 功能描述  : 显示SDIO上报BFGX的reg
 输入参数  :
 输出参数  :
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年12月2日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
STATIC ssize_t show_dump(struct device *dev, struct kobj_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s\n", __func__);

    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -FAILURE;
    }

    return sprintf(buf, "cmd           func            \n"
                        " 1    sdio read bcpu pub reg  \n"
                        " 2    sdio read bcpu priv reg \n"
                        " 3    sdio read bcpu mem      \n"
                        " 4    equal cmd 1+2+3         \n");
}
#endif
STATIC struct kobj_attribute plat_exception_dbg =
__ATTR(exception_dbg, 0644, (void *)show_exception_dbg, (void *)store_exception_dbg);

STATIC struct kobj_attribute uart_dumpctrl =
__ATTR(uart_rx_dump, 0664, (void *)show_uart_rx_dump, (void *)store_uart_rx_dump);

STATIC struct kobj_attribute wifi_dev_test =
__ATTR(wifi_test, 0664, (void *)show_dev_test, (void *)store_dev_test);

STATIC struct kobj_attribute wifi_mem_dump =
__ATTR(wifi_mem, 0664, (void *)show_wifi_mem_dump, (void *)store_wifi_mem_dump);


STATIC struct attribute *hi110x_debug_attrs[] = {
        &plat_exception_dbg.attr,
        &uart_dumpctrl.attr,
        &wifi_dev_test.attr,
        &wifi_mem_dump.attr,
        NULL,
};

STATIC struct attribute_group hi110x_debug_attr_grp = {
    .attrs = hi110x_debug_attrs,
};
#endif


int32 user_ctrl_init(void)
{
    int status;
    struct kobject *pst_root_object = NULL;

    pst_root_object = oal_get_sysfs_root_object();
    if(NULL == pst_root_object)
    {
        PS_PRINT_ERR("[E]get root sysfs object failed!\n");
        return -EFAULT;
    }

    g_sysfs_hisi_pmdbg = kobject_create_and_add("pmdbg", pst_root_object);
    if (NULL == g_sysfs_hisi_pmdbg)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hisi_pmdbg !!!\n ");
        goto fail;
    }

    status = sysfs_create_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
    if (status)
    {
        PS_PRINT_ERR("failed to create g_sysfs_hisi_pmdbg sysfs entries\n");
        goto fail;
    }

    g_sysfs_hi110x_bfgx = kobject_create_and_add("hi110x_ps", NULL);
    if (NULL == g_sysfs_hi110x_bfgx)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hi110x_ps !!!\n ");
        goto fail;
    }

    status = sysfs_create_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
    if (status)
    {
        PS_PRINT_ERR("failed to create g_sysfs_hi110x_bfgx sysfs entries\n");
        goto fail;
    }

#ifdef PLATFORM_DEBUG_ENABLE
    g_sysfs_hi110x_debug = kobject_create_and_add("hi110x_debug", NULL);
    if (NULL == g_sysfs_hi110x_debug)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hi110x_debug !!!\n ");
        goto fail;
    }

    status = sysfs_create_group(g_sysfs_hi110x_debug, &hi110x_debug_attr_grp);
    if (status)
    {
        PS_PRINT_ERR("failed to create g_sysfs_hi110x_debug sysfs entries\n");
        goto fail;
    }
#endif


    return 0;

fail:
    user_ctrl_exit();
    return -EFAULT;
}

void user_ctrl_exit(void)
{

#ifdef PLATFORM_DEBUG_ENABLE
    if(NULL != g_sysfs_hi110x_debug)
    {
        sysfs_remove_group(g_sysfs_hi110x_debug, &hi110x_debug_attr_grp);
        kobject_put(g_sysfs_hi110x_debug);
        g_sysfs_hi110x_debug = NULL;
    }
#endif

    if(NULL != g_sysfs_hi110x_bfgx)
    {
        sysfs_remove_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
        kobject_put(g_sysfs_hi110x_bfgx);
        g_sysfs_hi110x_bfgx = NULL;
    }

    if(NULL != g_sysfs_hisi_pmdbg)
    {
        sysfs_remove_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
        kobject_put(g_sysfs_hisi_pmdbg);
        g_sysfs_hisi_pmdbg = NULL;
    }

    //oal_conn_sysfs_root_obj_exit();
}

/**
 * Prototype    : ps_get_core_reference
 * Description  : reference the core's data,This references the per-PS
 *                  platform device in the arch/xx/board-xx.c file..
 * input        : use *hw_ps_device
 * output       : the have registered ps_core_d struct
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
int32 ps_get_core_reference(struct ps_plat_s **core_data)
{
    struct platform_device *pdev = NULL;

    pdev = hw_ps_device;
    if (!pdev)
    {
        *core_data = NULL;
        PS_PRINT_ERR("%s pdev is NULL\n", __func__);
        return FAILURE;
    }

    *core_data  = dev_get_drvdata(&pdev->dev);
    if (NULL == (*core_data))
    {
        PS_PRINT_ERR("ps_plat_d is NULL\n");
        return FAILURE;
    }

    return SUCCESS;
}


static uint32 hw_debug_data_parse(const int8 __user *buf)
{
    unsigned int temp;

    if( 0 > kstrtouint(buf, 16, &temp) )
    {
        return -EINVAL;
    }

    if( CMD_NUM_HEAD != GET_CMD_HEAD(temp))
    {
        return -EINVAL;
    }

    return _IO(PLAT_CFG_IOC_MAGIC, GET_CMD_NUM(temp));
}

/**
 * Prototype    : hw_debug_ioctl
 * Description  : called by ini_plat_dfr_set
 * input        : file handle, cmd, arg
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/11/24
 *     Author       : 
 *     Modification : Created function
 *
 */

STATIC int64 hw_debug_ioctl(struct file *file, uint32 cmd, uint64 arg)
{

    if (NULL == file)
    {
        PS_PRINT_ERR("file is null\n");
        return -EINVAL;
    }

    switch (cmd)
    {
        case PLAT_DFR_CFG_CMD:
            plat_dfr_cfg_set(arg);
            break;
        case PLAT_BEATTIMER_TIMEOUT_RESET_CFG_CMD:
            set_heartbeat_cfg(arg);
            break;
        case _IO(PLAT_CFG_IOC_MAGIC, PLAT_TRIGGER_EXCEPTION):
            PS_PRINT_WARNING("PLAT_TRIGGER_EXCEPTION\r\n");
            oal_trigger_exception(OAL_TRUE);
            // when panic msg come up, the function oal_sdio_device_panic_callback will be called
            break;
        case _IO(PLAT_CFG_IOC_MAGIC, PLAT_POWER_RESET):
            PS_PRINT_WARNING("PLAT_POWER_RESET\r\n");
            wifi_system_reset();
            break;
       case _IO(PLAT_CFG_IOC_MAGIC, PLAT_CHANNEL_DISABLE):
            PS_PRINT_WARNING("PLAT_CHANNEL_DISABLE\r\n");
            oal_wlan_gpio_intr_enable(oal_get_sdio_default_handler(), OAL_FALSE);
            break;

        default:
            PS_PRINT_WARNING("hw_debug_ioctl cmd = %d not find\n", cmd);
            return -EINVAL;
    }

    return 0;
}


/**********************************************************************/
/**
 * Prototype    : hw_debug_open
 * Description  : functions called from above oam hal,when open debug file
 *                  input : "/dev/hwbfgdbg"
 * input        : return 0 --> open is ok
 * output       : return !0--> open is false
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
STATIC int32 hw_debug_open(struct inode *inode, struct file *filp)
{
    struct ps_plat_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    (ps_core_d->g_debug_cnt)++;
    PS_PRINT_INFO("%s g_debug_cnt=%d", __func__, ps_core_d->g_debug_cnt);
    atomic_set(&ps_core_d->dbg_func_has_open, 1);

    ps_core_d->dbg_read_delay = DBG_READ_DEFAULT_TIME;

    return 0;
}

/**
 * Prototype    : hw_debug_read
 * Description  : functions called from above oam hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_debug_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{

    PS_PRINT_DBG("not support yet\n");

    return count;
}

/**
 * Prototype    : hw_debug_write
 * Description  : functions called from above oam hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
#ifdef PLATFORM_DEBUG_ENABLE
STATIC ssize_t hw_debug_write(struct file *filp, const int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    uint32 cmd;

    PS_PRINT_FUNCTION_NAME;

    cmd = hw_debug_data_parse(buf);
    if(cmd > 0)
    {
        hw_debug_ioctl(filp, cmd, 0);
        return count;
    }

    PS_PRINT_ERR("not supported yet\r\n");
    return count;
}
#endif

/**
 * Prototype    : hw_debug_release
 * Description  : called by oam func from hal when close debug inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
STATIC int32 hw_debug_release(struct inode *inode, struct file *filp)
{
    struct ps_plat_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    ps_core_d->g_debug_cnt--;
    PS_PRINT_INFO("%s g_debug_cnt=%d", __func__, ps_core_d->g_debug_cnt);

    return 0;
}

STATIC const struct file_operations hw_debug_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_debug_open,
#ifdef PLATFORM_DEBUG_ENABLE
        .write          = hw_debug_write,
#endif
        .read           = hw_debug_read,
        .unlocked_ioctl = hw_debug_ioctl,
        .release        = hw_debug_release,
};

STATIC struct miscdevice hw_debug_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwdbg",
        .fops   = &hw_debug_fops,
};

/**
 * This references is the per-PS platform device in the arch/arm/
 * board-xx.c file.
 */

STATIC int32 ps_probe(struct platform_device *pdev)
{
    struct ps_plat_s *ps_plat_d;
    int32  err = SUCCESS;
    struct device_node *np;
    const char * pdev_name;

    PS_PRINT_FUNCTION_NAME;

    np = of_find_compatible_node(NULL, NULL,DTS_COMP_HI1101_PS_NAME);   // should be the same as dts node compatible property
    if (NULL == np)
    {
        PS_PRINT_ERR("Unable to find %s\n",DTS_COMP_HI1101_PS_NAME);
        return -ENOENT;
    }

    if (of_property_read_string(np, "hi1102,uart_port", &pdev_name))
    {
        PS_PRINT_ERR("%s node doesn't have uart-dev property!\n", np->name);
        return -ENOENT;
    }

    ps_plat_d = kzalloc(sizeof(struct ps_plat_s), GFP_KERNEL);
    if (NULL == ps_plat_d)
    {
        PS_PRINT_ERR("no mem to allocate\n");
        return -ENOMEM;
    }
    dev_set_drvdata(&pdev->dev, ps_plat_d);
    /* get reference of pdev */
    ps_plat_d->pm_pdev = pdev;
    hw_ps_device = pdev;

    err = user_ctrl_init();
    if (SUCCESS != err)
    {
        PS_PRINT_ERR("bfgx_user_ctrl_init failed\n");
        goto user_ctrl_init_fail;
    }
    err = misc_register(&hw_debug_device);
    if (SUCCESS != err)
    {
        PS_PRINT_ERR("Failed to register debug inode\n");
        goto misc_register_fail;
    }

    return 0;

    misc_register_fail:
        user_ctrl_exit();
    user_ctrl_init_fail:
        dev_set_drvdata(&pdev->dev, NULL);
        kfree(ps_plat_d);
        return err;
}

/**
 * Prototype    : ps_suspend
 * Description  : called by kernel when kernel goto suspend
 * input        : pdev, state
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
int32 ps_suspend(struct platform_device *pdev, pm_message_t state)
{
#if 0
    struct hw_ps_plat_data  *pdata = pdev->dev.platform_data;
    if (pdata->suspend)
    {
        return pdata->suspend(pdev, state);
    }

    return -EOPNOTSUPP;
#else
    return 0;
#endif
}

/**
 * Prototype    : ps_resume
 * Description  : called by kernel when kernel resume from suspend
 * input        : pdev
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
int32 ps_resume(struct platform_device *pdev)
{
#if 0
    struct hw_ps_plat_data  *pdata = pdev->dev.platform_data;
    if (pdata->resume)
    {
        return pdata->resume(pdev);
    }

    return -EOPNOTSUPP;
#else
    return 0;
#endif
}
/**
 * Prototype    : ps_remove
 * Description  : called when user applation rmmod driver
 * input        : pdev
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : 
 *     Modification : Created function
 *
 */
STATIC int32 ps_remove(struct platform_device *pdev)
{
    struct ps_plat_s *ps_plat_d;


    misc_deregister(&hw_debug_device);
    PS_PRINT_INFO("misc debug device have removed\n");
    user_ctrl_exit();

    ps_plat_d = dev_get_drvdata(&pdev->dev);

    if (NULL != ps_plat_d)
    {
        kfree(ps_plat_d);
        ps_plat_d = NULL;
    }
    else
    {
        PS_PRINT_ERR("ps_plat_d is null\n");
    }

    hw_ps_device = NULL;

    PS_PRINT_INFO("sysfs user ctrl removed\n");

    return 0;
}
#ifdef _PRE_CONFIG_USE_DTS
static struct of_device_id hi1101_ps_match_table[] = {
    {
        .compatible = DTS_COMP_HI1101_PS_NAME,
        .data = NULL,
    },
    { },
};
#endif

/**********************************************************/
/*  platform_driver struct for PS module */
STATIC struct platform_driver ps_platform_driver = {
        .probe      = ps_probe,
        .remove     = ps_remove,
        .suspend    = ps_suspend,
        .resume     = ps_resume,
        .driver     = {
            .name   = "hisi_bfgx",
            .owner  = THIS_MODULE,
#ifdef _PRE_CONFIG_USE_DTS
        .of_match_table = hi1101_ps_match_table,
#endif
        },
};

int32 hw_ps_init(void)
{
    int32 ret;

    PS_PRINT_FUNCTION_NAME;

    ret = platform_driver_register(&ps_platform_driver);
    if (ret)
    {
        PS_PRINT_ERR("Unable to register platform bfgx driver.\n");
    }
    return ret;
}

void hw_ps_exit(void)
{
    platform_driver_unregister(&ps_platform_driver);
}


