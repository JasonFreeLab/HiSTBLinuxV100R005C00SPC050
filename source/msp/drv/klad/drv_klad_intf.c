/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_intf.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <linux/kthread.h>
#include "hi_common.h"
#include "hal_klad.h"
#include "hi_osal.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "hi_drv_klad.h"
#include "drv_klad.h"
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"

#include "drv_klad_basic.h"
#ifdef HI_ADVCA_COMMON_CA_SUPPORT
#include "drv_klad_common_ca.h"
#endif

#ifdef HI_ADVCA_NAGRA_SUPPORT
#include "drv_klad_nagra.h"
#endif

#ifdef HI_ADVCA_VERIMATRIX_SUPPORT
#include "drv_klad_verimatrix.h"
#endif

#ifdef HI_ADVCA_CONAX_SUPPORT
#include "drv_klad_conax.h"
#endif

#if (1 == HI_PROC_SUPPORT)
#include "drv_klad_proc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static UMAP_DEVICE_S g_ca_dev;


static HI_S32 KLAD_Open(struct inode* inode, struct file* filp)
{
    KLAD_FUNC_ENTER();

    mutex_lock(&g_klad_mutex);
    filp->private_data = (void*)(unsigned long)task_tgid_nr(current);
    mutex_unlock(&g_klad_mutex);

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}
#if 1
static HI_S32 KLAD_Release(struct inode* inode, struct file* filp)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    mutex_lock(&g_klad_mutex);
    ret = DRV_KLAD_Release(filp);
    mutex_unlock(&g_klad_mutex);

    KLAD_FUNC_EXIT();
    return ret;
}
#endif
static int KLAD_PM_Resume(PM_BASEDEV_S* pdev)
{
    KLAD_FUNC_ENTER();
    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static int KLAD_PM_Suspend(PM_BASEDEV_S* pdev, pm_message_t state)
{
    HI_ERR_KLAD("klad suspend OK\n");
    return HI_SUCCESS;
}

static long KLAD_Ioctl(struct file* ffile, unsigned int cmd, unsigned long arg)
{
    return (long)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, DRV_KLAD_Ioctl);
}

static struct file_operations ca_fpops =
{
    .owner = THIS_MODULE,
    .open = KLAD_Open,
    .unlocked_ioctl = KLAD_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = KLAD_Ioctl,
#endif
    .release = KLAD_Release,
};

static PM_BASEOPS_S ca_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = KLAD_PM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = KLAD_PM_Resume,
};

/*****************************************************************************
 Prototype    :
 Description  : Keyladder proc function register
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
/******* proc function begin ********/
#if (1 == HI_PROC_SUPPORT)
static HI_S32 KLAD_ProcWrite(struct file* file, const char __user* buf, size_t count, loff_t* ppos)
{
    return DRV_KLAD_ProcWrite(file, buf, count, ppos);
}

static HI_S32 KLAD_ProcRead(struct seq_file* p, HI_VOID* v)
{
    return DRV_KLAD_ProcRead(p, v);
}
#endif
/******* proc function end   ********/

/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode init.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_S32 KLAD_ModInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

#if (1 == HI_PROC_SUPPORT)
    DRV_PROC_EX_S proc_func = {0};
#endif

    KLAD_FUNC_ENTER();

    HAL_KLAD_RegisterMap();

    ret = DRV_KLAD_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("klad module init error\n");
        KLAD_FUNC_EXIT();
        return HI_FAILURE;
    }
    ret = DRV_KLAD_BASIC_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_FuncInit failed\n");
        KLAD_FUNC_EXIT();
        return ret;
    }

#ifdef HI_ADVCA_COMMON_CA_SUPPORT
    ret = DRV_KLAD_COMMON_CA_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_COMMON_CA_Init failed\n");
        KLAD_FUNC_EXIT();
        return ret;
    }
#endif

#ifdef HI_ADVCA_VERIMATRIX_SUPPORT
    ret = DRV_KLAD_VERIMATRIX_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_VERIMATRIX_Init failed\n");
        KLAD_FUNC_EXIT();
        return ret;
    }
#endif

#ifdef HI_ADVCA_NAGRA_SUPPORT
    ret = DRV_KLAD_NAGRA_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_NAGRA_Init failed\n");
        KLAD_FUNC_EXIT();
        return ret;
    }
#endif
#ifdef HI_ADVCA_CONAX_SUPPORT
    ret = DRV_KLAD_CONAX_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_CONAX_Init failed\n");
        KLAD_FUNC_EXIT();
        return ret;
    }
#endif

    HI_OSAL_Snprintf(g_ca_dev.devfs_name, sizeof(g_ca_dev.devfs_name), UMAP_DEVNAME_CA);
    g_ca_dev.minor  = UMAP_MIN_MINOR_CA;
    g_ca_dev.owner  = THIS_MODULE;
    g_ca_dev.fops   = &ca_fpops;
    g_ca_dev.drvops = &ca_drvops;

    if (HI_DRV_DEV_Register(&g_ca_dev) < 0)
    {
        HI_FATAL_KLAD("register CA failed.\n");
        goto err0;
    }

#if (1 == HI_PROC_SUPPORT)
    proc_func.fnRead = KLAD_ProcRead;
    proc_func.fnWrite = KLAD_ProcWrite;
    HI_DRV_PROC_AddModule(HI_MOD_CA, &proc_func, NULL);
#endif

#ifdef MODULE
    HI_PRINT("Load hi_advca.ko success.\t(%s)\n", VERSION_STRING);
#endif

    ret = HI_DRV_MODULE_Register(HI_ID_CA, "HI_KLAD", HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("HI_DRV_MODULE_Register failed\n");
        KLAD_FUNC_EXIT();
        goto err0;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;

err0:
    DRV_KLAD_Exit();
    KLAD_FUNC_EXIT();
    return HI_FAILURE;
}

/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode exit.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_VOID KLAD_ModExit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_BASIC_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_BASIC_Exit failed\n");
    }

#ifdef HI_ADVCA_COMMON_CA_SUPPORT
    ret = DRV_KLAD_COMMON_CA_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_COMMON_CA_Exit failed\n");
    }
#endif

#ifdef HI_ADVCA_VERIMATRIX_SUPPORT
    ret = DRV_KLAD_VERIMATRIX_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_VERIMATRIX_Exit failed\n");
    }
#endif

#ifdef HI_ADVCA_NAGRA_SUPPORT
    ret = DRV_KLAD_NAGRA_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_NAGRA_Exit failed\n");
    }
#endif
#ifdef HI_ADVCA_CONAX_SUPPORT
    ret = DRV_KLAD_CONAX_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_CONAX_Exit failed\n");
    }
#endif

#if (1 == HI_PROC_SUPPORT)
    HI_DRV_PROC_RemoveModule(HI_MOD_CA);
#endif

    HI_DRV_DEV_UnRegister(&g_ca_dev);
    HI_DRV_MODULE_UnRegister(HI_ID_CA);

    HAL_KLAD_RegisterUnMap();

    DRV_KLAD_Exit();

    KLAD_FUNC_EXIT();
    return;
}

#ifdef MODULE
module_init(KLAD_ModInit);
module_exit(KLAD_ModExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
