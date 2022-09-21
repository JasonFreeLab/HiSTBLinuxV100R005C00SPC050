/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : jpge_osr.c
Version             : Initial Draft
Author              :
Created             : 2016/03/03
Description         :
                      CNcomment:  CNend\n
Function List       :


History             :
Date                        Author                  Modification
2016/03/03                  sdk               Created file
******************************************************************************/


/*********************************add include here******************************/
#include <linux/version.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/poll.h>
#include <linux/workqueue.h>
#include <asm/io.h>

#include "hi_jpge_type.h"
#include "drv_jpge_ioctl.h"
#include "drv_jpge_ext.h"
#include "jpge_hal.h"
#include "hi_drv_dev.h"
#include "hi_reg_common.h"
#include "hi_drv_mem.h"
#include "hi_drv_module.h"
#include "hi_gfx_comm_k.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition ******************************/
#define JPGENAME     "HI_JPGE"


static HI_S32  JPGE_DRV_Open(struct inode *finode, struct file *pfile);
static HI_S32  JPGE_DRV_Close(struct inode *finode, struct file  *pfile);
static HI_S32  JPGE_DRV_Suspend(PM_BASEDEV_S *pdev,   pm_message_t state);
static HI_S32  JPGE_DRV_Resume(PM_BASEDEV_S *pdev);


long  jpge_ioctl        (struct file *pFile, unsigned int cmd, unsigned long arg);
#ifdef CONFIG_COMPAT
long  jpge_compat_ioctl (struct file *pFile, unsigned int cmd, unsigned long arg);
#endif

/*************************** Structure Definition ****************************/

static JPGE_EXPORT_FUNC_S s_JpgeExportFuncs =
{
    .pfnJpgeModInit         = JPGE_DRV_ModInit,
    .pfnJpgeModExit         = JPGE_DRV_ModExit,
    .pfnJpgeSuspend         = JPGE_DRV_Suspend,
    .pfnJpgeResume          = JPGE_DRV_Resume,
    .pfnJpgeInit            = JPEG_ENC_OpenDevForVenc,
    .pfnJpgeDeInit          = JPEG_ENC_CloseForVenc,
    .pfnJpgeCreateChn       = JPEG_ENC_CtreateForVenc,
    .pfnJpgeEncodeFrame     = JPEG_ENC_StartForVenc,
    .pfnJpgeDestroyChn      = JPEG_ENC_DestoryForVenc,
};

/********************** Global Variable declaration **************************/
static atomic_t g_JPGECount    = ATOMIC_INIT(0);
static HI_BOOL gs_bClockOpen   = HI_FALSE;
static HI_BOOL gs_bJpgeModInit = HI_FALSE;

static struct file_operations jpge_fops =
{
    .owner          = THIS_MODULE,
    .unlocked_ioctl = jpge_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = jpge_compat_ioctl,
#endif
    .open     = JPGE_DRV_Open,
    .release  = JPGE_DRV_Close,
    .mmap     = NULL,
};

static PM_BASEOPS_S jpge_drvops =
{
    .suspend  = JPGE_DRV_Suspend,
    .resume   = JPGE_DRV_Resume,
};

static PM_DEVICE_S jpge_dev =
{
    .name     = "hi_jpge",
    .minor    = HIMEDIA_DYNAMIC_MINOR,
    .owner    = THIS_MODULE,
    .app_ops  = &jpge_fops,
    .base_ops = &jpge_drvops,
};

/********************** API forward declarations     **************************/


/********************** API forward release          **************************/

/***************************************************************************
* func           : JPGE_DRV_Open
* description : api open jpge dev call this function
                        CNcomment: 打开设备文件       CNend\n
* param[in]  : finode     CNcomment: 文件节点       CNend\n
* param[in]  : pFile      CNcomment: 文件描述符   CNend\n
* retval        : NA
* others:     : NA
****************************************************************************/
static HI_S32 JPGE_DRV_Open(struct inode *finode, struct file *pfile)
{
    if (1 == atomic_inc_return(&g_JPGECount))
    {
        JPEG_ENC_OpenClock();;
    }

    return HI_SUCCESS;
}

/***************************************************************************
* func             : JPGE_DRV_Close
* description   : api close jpge dev call this function
                          CNcomment: 关闭设备文件       CNend\n
* param[in]    : finode     CNcomment: 文件节点       CNend\n
* param[in]    : pFile      CNcomment: 文件描述符   CNend\n
* retval          : NA
* others:       : NA
****************************************************************************/
static HI_S32 JPGE_DRV_Close(struct inode *finode, struct file  *pfile)
{

    JPEG_ENC_Reset();

    if (atomic_dec_and_test(&g_JPGECount))
    {
        JPEG_ENC_CloseClock();
    }

    if (atomic_read(&g_JPGECount) < 0)
    {
        atomic_set(&g_JPGECount, 0);
    }

    return HI_SUCCESS;
}


/***************************************************************************
* func             : JPGE_DRV_Suspend
* description   : suspend will call this function
                         CNcomment: 待机功能 CNend\n
* param[in]    : pdev
* param[in]    : state
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static HI_S32 JPGE_DRV_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{

    U_PERI_CRG36 unTempValue;

    unTempValue.u32 = g_pstRegCrg->PERI_CRG36.u32;

    if (0x1 == unTempValue.bits.jpge_cken)
    {
        gs_bClockOpen = HI_TRUE;
    }
    else
    {
        gs_bClockOpen = HI_FALSE;
    }

    HI_PRINT("JPGE suspend OK\n");

    return HI_SUCCESS;
}


/***************************************************************************
* func           : JPGE_DRV_Resume
* description : resume will call this function
                       CNcomment: 待机唤醒功能 CNend\n
* param[in]  : pdev
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:     : NA
****************************************************************************/
static HI_S32 JPGE_DRV_Resume(PM_BASEDEV_S *pdev)
{
    if (HI_TRUE == gs_bClockOpen)
    {
        JPEG_ENC_OpenClock();
    }

    HI_PRINT("JPGE resume OK\n");

    return HI_SUCCESS;
}

/***************************************************************************
* func          : JPEG_ENC_OpenDevForVenc
* description   : venc jpeg encode initial will call this function
                  CNcomment: venc编码调用 CNend\n
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
HI_VOID JPEG_ENC_OpenDevForVenc(HI_VOID)
{
     JPGE_DRV_Open(NULL, NULL);
}

/***************************************************************************
* func          : JPEG_ENC_CloseForVenc
* description   : venc jpeg encode dinitial will call this function
                  CNcomment: venc编码调用 CNend\n
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
HI_VOID JPEG_ENC_CloseForVenc(HI_VOID)
{
    JPGE_DRV_Close(NULL, NULL);
}



/***************************************************************************
* func          : jpge_ioctl
* description   : kernel 64bit and api 32bit or kernel 32bit also call this function
                  CNcomment: 内核态和用户态都是64位或者内核态32位调用该函数 CNend\n
* param[in]     : pFile      CNcomment: 文件描述符     CNend\n
* param[in]     : cmd        CNcomment: 传入的调用命令 CNend\n
* param[in]     : arg        CNcomment: 传入参数 CNend\n
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
long jpge_ioctl(struct file *pFile, unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    long s32Ret = 0;
    JPGE_HANDLE  s32Handle = -1;
    Jpge_EncCfg_S  stEncCfg;
    Jpge_EncInfo_S EncInfo;

    if (NULL == argp)
    {
       return -EFAULT;
    }

    switch (cmd)
    {
        case JPGE_CREATEHANDLE_CMD:
        {
            s32Ret = JPEG_ENC_CreateHandle(&s32Handle);
            if (HI_SUCCESS != s32Ret)
            {
                return HI_FAILURE;
            }

            if (copy_to_user(argp, (HI_VOID *)(&s32Handle),sizeof(JPGE_HANDLE)))
            {
                return -EFAULT;
            }

            return HI_SUCCESS;
        }
        case JPGE_CREATE_CMD:
        {
            HI_GFX_Memset(&stEncCfg,0,sizeof(Jpge_EncCfg_S));

            if (copy_from_user(&stEncCfg, argp, sizeof(Jpge_EncCfg_S)))
            {
                return -EFAULT;
            }
            s32Ret = JPEG_ENC_Create(&stEncCfg);
            if (0 != s32Ret)
            {
                return s32Ret;
            }

            if (copy_to_user(argp, &stEncCfg, sizeof(Jpge_EncCfg_S)))
            {
                return -EFAULT;
            }

            return HI_SUCCESS;
        }
        case JPGE_ENCODE_CMD:
        {
            HI_GFX_Memset(&EncInfo,0,sizeof(Jpge_EncInfo_S));

            if (copy_from_user(&EncInfo, argp, sizeof(Jpge_EncInfo_S)))
            {
                return -EFAULT;
            }
            if (0 == EncInfo.EncIn.BusOutBuf)
            {
                return HI_FAILURE;
            }

            CHECK_JPGE_HANDLE_SUPPORT(EncInfo.EncHandle);

            s32Ret =  JPEG_ENC_Start(EncInfo.EncHandle, &EncInfo.EncIn, &EncInfo.EncOut);
            if (0 != s32Ret)
            {
                return s32Ret;
            }

            if (copy_to_user(argp, &EncInfo, sizeof(Jpge_EncInfo_S)))
            {
                return -EFAULT;
            }

            return HI_SUCCESS;
        }
        case JPGE_DESTROY_CMD:
        {
            if (copy_from_user(&s32Handle, argp, sizeof(JPGE_HANDLE)))
            {
                return -EFAULT;
            }

            CHECK_JPGE_HANDLE_SUPPORT(s32Handle);

            return JPEG_ENC_Destory(s32Handle);
        }
        default:
            break;
    }

    return -ENOIOCTLCMD;

}


#ifdef CONFIG_COMPAT

/***************************************************************************
* func          : jpge_compat_ioctl
* description   : kernel 64bit and api 64bit call this function
                  CNcomment: 内核态和用户态都是64位调用该函数 CNend\n
* param[in]     : pFile      CNcomment: 文件描述符     CNend\n
* param[in]     : cmd        CNcomment: 传入的调用命令 CNend\n
* param[in]     : arg        CNcomment: 传入参数 CNend\n
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
long jpge_compat_ioctl(struct file *pFile, unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    long s32Ret = 0;
    Jpge_EncInfo_S           stEncInfo;
    Jpge_Compat_EncInfo_S    CompatEncInfo;

    if (NULL == argp)
    {
       return -EFAULT;
    }

    switch (cmd)
    {
        case JPGE_CREATEHANDLE_CMD:
        {
            return jpge_ioctl(pFile,JPGE_CREATEHANDLE_CMD,arg);
        }
        case JPGE_CREATE_CMD:
        {
            return jpge_ioctl(pFile,JPGE_CREATE_CMD,arg);
        }
        case JPGE_COMPAT_ENCODE_CMD:
        {
            HI_GFX_Memset(&stEncInfo,0,sizeof(Jpge_EncInfo_S));
            HI_GFX_Memset(&CompatEncInfo,0,sizeof(Jpge_Compat_EncInfo_S));

            if (copy_from_user(&CompatEncInfo, argp, sizeof(Jpge_Compat_EncInfo_S)))
            {
                return -EFAULT;
            }
            if (0 == CompatEncInfo.EncIn.BusOutBuf)
            {
                return HI_FAILURE;
            }
            stEncInfo.EncIn.BusViY     = CompatEncInfo.EncIn.BusViY;
            stEncInfo.EncIn.BusViC     = CompatEncInfo.EncIn.BusViC;
            stEncInfo.EncIn.BusViV     = CompatEncInfo.EncIn.BusViV;
            stEncInfo.EncIn.ViYStride  = CompatEncInfo.EncIn.ViYStride;
            stEncInfo.EncIn.ViCStride  = CompatEncInfo.EncIn.ViCStride;
            stEncInfo.EncIn.BusOutBuf  = CompatEncInfo.EncIn.BusOutBuf;
            stEncInfo.EncIn.pOutBuf    = (HI_U8*)(unsigned long)(CompatEncInfo.EncIn.pOutBuf);
            stEncInfo.EncIn.OutBufSize = CompatEncInfo.EncIn.OutBufSize;

            stEncInfo.EncOut.BusStream = CompatEncInfo.EncOut.BusStream;
            stEncInfo.EncOut.pStream   = (HI_U8*)(unsigned long)(CompatEncInfo.EncOut.pStream);
            stEncInfo.EncOut.StrmSize  = CompatEncInfo.EncOut.StrmSize;

            s32Ret =  JPEG_ENC_Start(CompatEncInfo.EncHandle, &stEncInfo.EncIn, &stEncInfo.EncOut);
            if (0 != s32Ret)
            {
                return s32Ret;
            }

            CompatEncInfo.EncIn.BusViY     = stEncInfo.EncIn.BusViY;
            CompatEncInfo.EncIn.BusViC     = stEncInfo.EncIn.BusViC;
            CompatEncInfo.EncIn.BusViV     = stEncInfo.EncIn.BusViV;
            CompatEncInfo.EncIn.ViYStride  = stEncInfo.EncIn.ViYStride;
            CompatEncInfo.EncIn.ViCStride  = stEncInfo.EncIn.ViCStride;
            CompatEncInfo.EncIn.BusOutBuf  = stEncInfo.EncIn.BusOutBuf;
            CompatEncInfo.EncIn.pOutBuf    = (unsigned long)stEncInfo.EncIn.pOutBuf;
            CompatEncInfo.EncIn.OutBufSize = stEncInfo.EncIn.OutBufSize;

            CompatEncInfo.EncOut.BusStream = stEncInfo.EncOut.BusStream;
            CompatEncInfo.EncOut.pStream   = (unsigned long)stEncInfo.EncOut.pStream;
            CompatEncInfo.EncOut.StrmSize  = stEncInfo.EncOut.StrmSize;

            if (copy_to_user(argp, &CompatEncInfo, sizeof(Jpge_Compat_EncInfo_S)))
            {
                return -EFAULT;
            }

            return HI_SUCCESS;
        }
        case JPGE_DESTROY_CMD:
        {
            return jpge_ioctl(pFile,JPGE_DESTROY_CMD,arg);
        }
        default:
            break;
    }

    return -ENOIOCTLCMD;

}
#endif


/***************************************************************************
* func          : jpge_showversion
* description   : insmod jpge dev success call this function to display info
                  CNcomment: 驱动加载成功打印 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
static HI_VOID jpge_showversion(HI_VOID)
{
#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE) && defined(MODULE)
    GFX_Printk("Load hi_jpegenc.ko success.\t(%s)\n", VERSION_STRING);
#endif
    return;
}


/***************************************************************************
* func          : JPGE_DRV_ModExit
* description   : insmod jpge dinital
                  CNcomment: 驱动加载去初始化 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_VOID JPGE_DRV_ModExit(HI_VOID)
{
    if (HI_FALSE == gs_bJpgeModInit)
    {
        return;
    }

    HI_GFX_MODULE_UnRegister(HIGFX_JPGENC_ID);

    JPEG_ENC_Close();

    HI_DRV_PM_UnRegister(&jpge_dev);

    gs_bJpgeModInit = HI_FALSE;

    return;
}

/***************************************************************************
* func          : JPGE_DRV_ModInit
* description   : insmod jpge inital
                  CNcomment: 驱动加载初始化 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JPGE_DRV_ModInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == gs_bJpgeModInit)
    {
        return HI_SUCCESS;
    }

    s32Ret = JPEG_ENC_Open();
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("JPGE open failure!\n");
        return -1;
    }

    s32Ret = HI_DRV_PM_Register(&jpge_dev);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("register dev failed!\n");
        JPEG_ENC_Close();
        return HI_FAILURE;
    }

    s32Ret = HI_GFX_MODULE_Register(HIGFX_JPGENC_ID, JPGENAME, &s_JpgeExportFuncs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PRINT("HI_DRV_MODULE_Register JPGE failed\n");
        JPGE_DRV_ModExit();
        return HI_FAILURE;
    }

    jpge_showversion();

    gs_bJpgeModInit = HI_TRUE;

    return HI_SUCCESS;
}

#ifdef MODULE
module_init(JPGE_DRV_ModInit);
module_exit(JPGE_DRV_ModExit);
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
MODULE_DESCRIPTION("driver for the all jpge");
MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0.0.0");
#else
MODULE_DESCRIPTION("");
MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
MODULE_VERSION("");
#endif
