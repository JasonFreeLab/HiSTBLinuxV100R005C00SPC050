/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_otp_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include <linux/uaccess.h>
#include "hi_kernel_adapt.h"
#include "hi_drv_module.h"
#include "hi_drv_dev.h"
#include "hal_otp.h"
#include "hi_error_mpi.h"
#include "drv_otp_ioctl.h"
#include "hi_drv_proc.h"
#include "hi_drv_mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define DRV_OTP_PROC_SEPARATE         "===============================================\n"
#define DRV_OTP_PROC_PRINT(fmt...)    PROC_PRINT(p, fmt)

static UMAP_DEVICE_S   g_otp_umap_dev;

HI_DECLARE_MUTEX(g_otp_mutex);

typedef struct
{
    HI_U32 cmd;
    HI_S32 (*fun_ioctl)(HI_VOID *arg);
} DRV_OTP_IOCTL_FUNC_MAP_S;

HI_S32 DRV_OTP_Read(HI_VOID *arg)
{
    OTP_ENTRY_S *otp_entry = NULL;
    
    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S *)arg;
    return HAL_OTP_Read(otp_entry->addr, &(otp_entry->value));
}

HI_S32 DRV_OTP_ReadByte(HI_VOID *arg)
{
    OTP_ENTRY_S *otp_entry = NULL;
    HI_U8 value = 0;
    HI_S32 ret;
    CHECK_NULL_PTR(arg);

    otp_entry = (OTP_ENTRY_S *)arg;
    ret = HAL_OTP_ReadByte(otp_entry->addr, &value);
    otp_entry->value = value;
    return ret;
}

HI_S32 DRV_OTP_ReadBitsOneByte(HI_VOID *arg)
{
    OTP_ENTRY_S *otp_entry = NULL;
    HI_U8 start_bit = 0;
    HI_U8 bit_width = 0;
    HI_U8 value = 0;
    HI_S32 ret;

    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S *)arg;
    start_bit = OTP_START_BIT(otp_entry->value);
    bit_width = OTP_BIT_WIDTH(otp_entry->value);
    value = OTP_VALUE_BYTE(otp_entry->value);

    if (start_bit > 7)
    {
        HI_ERR_OTP("start_bit check failed. [%d]\n", start_bit);
        return HI_ERR_OTP_INVALID_PARA;
    }
    if (bit_width + start_bit > 8)
    {
        HI_ERR_OTP("bit_width check failed. [%d-%d]\n", start_bit, bit_width);
        return HI_ERR_OTP_INVALID_PARA;
    }
    ret = HAL_OTP_ReadBitsOnebyte(otp_entry->addr, start_bit, bit_width, &value);
    otp_entry->value = OTP_GET_PARA(start_bit, bit_width, value);
    return ret;
}

HI_S32 DRV_OTP_Write(HI_VOID *arg)
{
    OTP_ENTRY_S *otp_entry = NULL;
    
    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S *)arg;
    return HAL_OTP_Write(otp_entry->addr, otp_entry->value);
}

HI_S32 DRV_OTP_WriteByte(HI_VOID *arg)
{
    OTP_ENTRY_S *otp_entry = NULL;
    
    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S *)arg;
    return HAL_OTP_WriteByte(otp_entry->addr, (HI_U8)otp_entry->value);
}

HI_S32 DRV_OTP_WriteBit(HI_VOID *arg)
{

    OTP_ENTRY_S *otp_entry = NULL;
    HI_U8 bit_pos = 0;
    HI_U8 value = 0;
    
    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S *)arg;
    bit_pos = OTP_START_BIT(otp_entry->value);
    value = OTP_VALUE_BYTE(otp_entry->value);
    
    if (bit_pos > 7)
    {
        HI_ERR_OTP("bit_pos check failed. [%d]\n", bit_pos);
        return HI_ERR_OTP_INVALID_PARA;
    }
    if (value != 0 && value != 1)
    {
        HI_ERR_OTP("value check failed. [%d]\n", value);
        return HI_ERR_OTP_INVALID_PARA;
    }
    return HAL_OTP_WriteBit(otp_entry->addr, bit_pos, (HI_BOOL)value);
}

HI_S32 DRV_OTP_WriteBitsOneByte(HI_VOID *arg)
{
    OTP_ENTRY_S *otp_entry = NULL;
    HI_U8 start_bit = 0;
    HI_U8 bit_width = 0;
    HI_U8 value = 0;
    
    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S *)arg;
    start_bit = OTP_START_BIT(otp_entry->value);
    bit_width = OTP_BIT_WIDTH(otp_entry->value);
    value = OTP_VALUE_BYTE(otp_entry->value);
    
    if (start_bit > 7)
    {
        HI_ERR_OTP("start_bit check failed. [%d]\n", start_bit);
        return HI_ERR_OTP_INVALID_PARA;
    }
    if (bit_width + start_bit > 8)
    {
        HI_ERR_OTP("bit_width check failed. [%d-%d]\n", start_bit, bit_width);
        return HI_ERR_OTP_INVALID_PARA;
    }
    return HAL_OTP_WriteBitsOnebyte(otp_entry->addr, start_bit, bit_width, value);
}

HI_S32 DRV_OTP_Reset(HI_VOID *arg)
{
    return HAL_OTP_Reset();
}


static DRV_OTP_IOCTL_FUNC_MAP_S g_ioctl_func_map[] =
{
    {CMD_OTP_READ,               DRV_OTP_Read},
    {CMD_OTP_READ_BYTE,          DRV_OTP_ReadByte},
    {CMD_OTP_READ_BITS_ONEBYTE,  DRV_OTP_ReadBitsOneByte},
    {CMD_OTP_WRITE,              DRV_OTP_Write},
    {CMD_OTP_WRITE_BYTE,         DRV_OTP_WriteByte},
    {CMD_OTP_WRITE_BIT,          DRV_OTP_WriteBit},
    {CMD_OTP_WRITE_BITS_ONEBYTE, DRV_OTP_WriteBitsOneByte},
    {CMD_OTP_RESET,              DRV_OTP_Reset},
};

HI_S32 OTP_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *arg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 i = 0;
    HI_S32 size = 0;

    size = sizeof(g_ioctl_func_map) / sizeof(g_ioctl_func_map[0]);
    for (i = 0; i < size; i++)
    {
        if (cmd == g_ioctl_func_map[i].cmd)
        {
            if (down_interruptible(&g_otp_mutex))
            {
                return -1;
            }
            ret = g_ioctl_func_map[i].fun_ioctl(arg);
            if (ret != HI_SUCCESS)
            {
                HI_ERR_OTP("cmd ID: 0x%x failed, ret: 0x%x\n", cmd, ret);
            }
            up(&g_otp_mutex);
            return ret;
        }
    }

    HI_ERR_OTP("not support cmd ID: 0x%x\n", cmd);
    return HI_ERR_OTP_INVALID_PARA;
}

static HI_S32 OTP_DRV_Open(struct inode *inode, struct file *filp)
{
    return 0;
}

static HI_S32 OTP_DRV_Close(struct inode *inode, struct file *filp)
{
    return 0;
}

#define OTP_NAME "HI_OTP"
HI_S32 OTP_DRV_Init(void)
{
    HI_S32 ret = HI_SUCCESS;

    ret = HI_DRV_MODULE_Register(HI_ID_OTP, OTP_NAME, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_OTP("HI_DRV_MODULE_Register otp failed\n");
        return ret;
    }
    ret = HAL_OTP_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_OTP("HAL_OTP_Init otp failed\n");
        return ret;
    }
    return HI_SUCCESS;
}

HI_S32 OTP_DRV_DeInit(void)
{
    HI_DRV_MODULE_UnRegister(HI_ID_OTP);
    return HI_SUCCESS;
}

static HI_SLONG OTP_DRV_Ioctl(struct file *ffile, HI_U32 cmd, HI_ULONG arg)
{
    HI_SLONG ret;
    ret = (HI_SLONG)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, OTP_Ioctl);
    return ret;
}

static struct file_operations otp_fops =
{
    .owner          = THIS_MODULE,
    .open           = OTP_DRV_Open,
    .unlocked_ioctl = OTP_DRV_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = OTP_DRV_Ioctl,
#endif
    .release        = OTP_DRV_Close,
};

int OTP_PM_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    return HI_SUCCESS;
}

int OTP_PM_Resume(PM_BASEDEV_S *pdev)
{
    //return HAL_OTP_Reset();
    return HI_SUCCESS;
}

static PM_BASEOPS_S  otp_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = OTP_PM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = OTP_PM_Resume,
};


HI_S32 OTP_DRV_ModInit(HI_VOID)
{
    snprintf(g_otp_umap_dev.devfs_name, sizeof(UMAP_DEVNAME_OTP), UMAP_DEVNAME_OTP);
    g_otp_umap_dev.minor = UMAP_MIN_MINOR_OTP;
    g_otp_umap_dev.owner  = THIS_MODULE;
    g_otp_umap_dev.drvops = &otp_drvops;
    g_otp_umap_dev.fops = &otp_fops;

    if (HI_DRV_DEV_Register(&g_otp_umap_dev) < 0)
    {
        HI_FATAL_OTP("register otp failed.\n");
        return HI_FAILURE;
    }
    OTP_DRV_Init();
#ifdef MODULE
    HI_PRINT("Load hi_otp.ko success.  \t(%s)\n", VERSION_STRING);
#endif
    return 0;
}

HI_VOID OTP_DRV_ModExit(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&g_otp_umap_dev);
    OTP_DRV_DeInit();
    return;
}

#ifdef MODULE
module_init(OTP_DRV_ModInit);
module_exit(OTP_DRV_ModExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

