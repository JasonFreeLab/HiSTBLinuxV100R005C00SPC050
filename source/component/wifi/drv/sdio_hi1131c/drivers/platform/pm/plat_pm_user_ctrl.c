/*
 *
 * Copyright (C), 2001-2021, Hisilicon Tech. Co., Ltd.
 *
 *
 * File Name     : plat_pm_user_ctrl.c
 * Version       : Hi1102
 * Author        : 
 * Created       : 2015/04/10
 * Last Modified :
 * Description   : platform pm sys file user control interface
 * Function List :
 * History       :
 * 1.Date        : 2015/04/10
 *   Author      : 
 *   Modification: Created file
 *
 */

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include "plat_debug.h"
#include "plat_pm.h"


/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
STATIC struct kobject *g_sysfs_hi110x_power = NULL;

/*****************************************************************************
  3 Function Definition
*****************************************************************************/

STATIC ssize_t bt_power_state_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
   return 0;
}

STATIC struct kobj_attribute bt_power_attr = {
    .attr = {
        .name = "bt_power_state",
        .mode = S_IRUGO | S_IWUSR,
    },
    .show   = bt_power_state_show,
};

STATIC ssize_t fm_power_state_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
    return 0;
}

STATIC struct kobj_attribute fm_power_attr = {
    .attr = {
        .name = "fm_power_state",
        .mode = S_IRUGO | S_IWUSR,
    },
    .show   = fm_power_state_show,
};

STATIC ssize_t gnss_power_state_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
    return 0;
}

STATIC struct kobj_attribute gnss_power_attr = {
    .attr = {
        .name = "gnss_power_state",
        .mode = S_IRUGO | S_IWUSR,
    },
    .show   = gnss_power_state_show,
};

STATIC ssize_t nfc_power_state_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
    return 0;

}

STATIC struct kobj_attribute nfc_power_attr = {
    .attr = {
        .name = "nfc_power_state",
        .mode = S_IRUGO | S_IWUSR,
    },
    .show   = nfc_power_state_show,
};

STATIC ssize_t ir_power_state_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
    return 0;
}

STATIC struct kobj_attribute ir_power_attr = {
    .attr = {
        .name = "ir_power_state",
        .mode = S_IRUGO | S_IWUSR,
    },
    .show   = ir_power_state_show,
};

STATIC ssize_t bfg_sleep_state_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return sprintf(buf, "%d\n", pm_data->bfgx_dev_state);

}

STATIC struct kobj_attribute bfg_sleep_attr = {
    .attr = {
        .name = "bfg_sleep_state",
        .mode = S_IRUGO | S_IWUSR,
    },
    .show = bfg_sleep_state_show,
};

STATIC ssize_t bfg_wakeup_host_show(struct kobject *kobj,
        struct kobj_attribute *attr, char *buf)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return sprintf(buf, "%d\n", pm_data->bfg_wakeup_host);

}
STATIC struct kobj_attribute bfg_wakeup_host_attr= {
    .attr = {
        .name = "bfg_wakeup_host",
        .mode = S_IRUGO | S_IWUSR,
    },
    .show = bfg_wakeup_host_show,
};
STATIC struct attribute *bfg_power_attrs[] = {
    &bt_power_attr.attr,
    &fm_power_attr.attr,
    &gnss_power_attr.attr,
    &nfc_power_attr.attr,
    &ir_power_attr.attr,
    &bfg_sleep_attr.attr,
    &bfg_wakeup_host_attr.attr,
    NULL
};

STATIC struct attribute_group pm_state_group = {
    .attrs = bfg_power_attrs,
};

int32 pm_user_ctrl_init(void)
{
    int32 ret;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    g_sysfs_hi110x_power = kobject_create_and_add("hi110x_power", NULL);
    if (NULL == g_sysfs_hi110x_power)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hi110x_power !!!\n ");
        return -ENOMEM;
    }

    ret = sysfs_create_group(g_sysfs_hi110x_power , &pm_state_group);
    if (ret)
    {
        PS_PRINT_ERR("failed to create pm properties!\n");
    }
#endif
    return ret;
}


void pm_user_ctrl_exit(void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    sysfs_remove_group(g_sysfs_hi110x_power , &pm_state_group);
    kobject_put(g_sysfs_hi110x_power);
    g_sysfs_hi110x_power = NULL;
    return;
#endif
}
