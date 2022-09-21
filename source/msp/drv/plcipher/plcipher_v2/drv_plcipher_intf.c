/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_plcipher_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#if 0
#include <linux/proc_fs.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <linux/spinlock.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/kallsyms.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/seq_file.h>
#include <linux/version.h>
//#include <linux/himedia.h>

#include <asm/atomic.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/traps.h>

#include <linux/miscdevice.h>
#endif
#include "linux/compat.h"
#include "linux/fs.h"

#include "hi_type.h"
//#include "hi_debug.h"
//#include "hi_common.h"
//#include "hi_kernel_adapt.h"
#include "hi_drv_dev.h"
#include "hi_drv_mem.h"
//#include "hal_plcipher.h"
#include "drv_plcipher_ioctl.h"
#include "drv_plcipher_ext.h"
#include "drv_plcipher.h"
#include "drv_advca_ext.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/***************************** Macro Definition ******************************/

#define PLCIPHER_NAME "HI_PLCIPHER"
#define PLCIPHER_REG_BASE_ADDR_PHY          (0xF9A40000)

/**************************** global variables ****************************/

static PLCIPHER_EXPORT_FUNC_S s_PlcipherExportFuncs =
{
    .pfnPlcipherSetKey  = HI_DRV_PLCIPHER_SetKey,
    .pfnPlcipherSetIV   = HI_DRV_PLCIPHER_SetIV,
};

static UMAP_DEVICE_S  g_PLCipherDevice;
HI_VOID * g_u32PLCipherRegBase;

/******* proc function begin ********/

#if (1 ==  HI_PROC_SUPPORT)

HI_S32 PLCIPHER_ProcRead(struct seq_file *p, HI_VOID *v)
{

    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;
    PLCIPHER_CHN_STATUS_S stPLCipherChanInfo ;
    PLCIPHER_CHN_STATUS_S* pstPLCipherChanInfo = NULL;
    memset(&stPLCipherChanInfo, 0, sizeof(stPLCipherChanInfo));

    PROC_PRINT(p, "\n------------------CIPHER STATUS------------\n");
    PROC_PRINT(p, "Chnid   Status   Encrypt   Alg      EvenOdd   PacketNum    Addr(in/out)    DataLen    \n");
    for(i = 0; i < PLCIPHER_CHAN_NUM; i++)
    {
        HI_CHAR Status[16] = "";
        HI_CHAR Alg[16]  = "";
        HI_CHAR EvenOdd[16] = "";

        memset(&stPLCipherChanInfo, 0, sizeof(stPLCipherChanInfo));
        stPLCipherChanInfo.ChanID = i;
        pstPLCipherChanInfo = &stPLCipherChanInfo;

        ret = DRV_PLCIPHER_GetChanStatus(pstPLCipherChanInfo);
        if (ret != HI_SUCCESS)
        {
            break;
        }

        if (!pstPLCipherChanInfo->bOpen)
        {
            continue;
        }

        if (pstPLCipherChanInfo->bDataDone)
        {
            strncpy(Status, "Done", sizeof(Status));
        }
        else
        {
            strncpy(Status, "Processing", sizeof(Status));
        }

        if (HI_UNF_PLCIPHER_KEY_EVEN == pstPLCipherChanInfo->enKeyEvenOdd)
        {
            strncpy(EvenOdd, "Even", sizeof(EvenOdd));
        }
        else
        {
            strncpy(EvenOdd, "Odd", sizeof(EvenOdd));
        }

        if (HI_UNF_PLCIPHER_ALG_AES_IPTV == pstPLCipherChanInfo->enAlg)
        {
            strncpy(Alg, "AES_IPTV",sizeof(Alg));
        }
        else if (HI_UNF_PLCIPHER_ALG_AES_ECB == pstPLCipherChanInfo->enAlg)
        {
            strncpy(Alg, "AES_ECB",sizeof(Alg));
        }
        else if (HI_UNF_PLCIPHER_ALG_AES_CBC == pstPLCipherChanInfo->enAlg)
        {
            strncpy(Alg, "AES_CBC",sizeof(Alg));
        }
        else
        {
            strncpy(Alg, "UnKnown",sizeof(Alg));
        }

        PROC_PRINT( p, " %2d       %s      %d   %8s     %s  %8d      %08x/%08x   %d       \n",
                    i,
                    Status,
                    pstPLCipherChanInfo->bEncryptOrDecrypt,
                    Alg,
                    EvenOdd,
                    pstPLCipherChanInfo->DataLen/188,
                    pstPLCipherChanInfo->InPhyAddr,
                    pstPLCipherChanInfo->OutPhyAddr,
                    pstPLCipherChanInfo->DataLen
                   );

        PROC_PRINT(p, "\n---------------Current Used Key Information-------------\n");
        PROC_PRINT(p, "CurChan: %d\n",stPLCipherChanInfo.ChanID);
        PROC_PRINT(p, "EvenCW:  %08x %08x %08x %08x\n",pstPLCipherChanInfo->EvenCW[0],pstPLCipherChanInfo->EvenCW[1],pstPLCipherChanInfo->EvenCW[2],pstPLCipherChanInfo->EvenCW[3]);
        PROC_PRINT(p, "OddCW:   %08x %08x %08x %08x\n",pstPLCipherChanInfo->OddCW[0],pstPLCipherChanInfo->OddCW[1],pstPLCipherChanInfo->OddCW[2],pstPLCipherChanInfo->OddCW[3]);
        PROC_PRINT(p, "IV:      %08x %08x %08x %08x\n",pstPLCipherChanInfo->IV[0],pstPLCipherChanInfo->IV[1],pstPLCipherChanInfo->IV[2],pstPLCipherChanInfo->IV[3]);
    }

    return ret;
}

static HI_VOID PLCIPHER_DRV_ProcInit(HI_VOID)
{
    DRV_PROC_EX_S stProc = {0};

    stProc.fnRead   = PLCIPHER_ProcRead;
    stProc.fnWrite  = HI_NULL;

    HI_DRV_PROC_AddModule(HI_MOD_PLCIPHER, &stProc, NULL);
}

static HI_VOID PLCIPHER_DRV_ProcDeInit(HI_VOID)
{
    HI_DRV_PROC_RemoveModule(HI_MOD_PLCIPHER);
}

#endif
/******* proc function end ********/

HI_S32 DRV_PLCIPHER_Open(struct inode * inode, struct file * file)
{
    return HI_DRV_PLCIPHER_Open();
}

HI_S32 DRV_PLCIPHER_Release(struct inode * inode, struct file * file)
{
    return HI_DRV_PLCIPHER_Close();
}

HI_S32 PLCIPHER_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *argp)
{
    HI_S32 ret = HI_SUCCESS;

    switch(cmd)
    {
        case CMD_PLCIPHER_CREATEHANDLE:
        {
            HI_HANDLE *PLCipher  = (HI_HANDLE *)argp;
            ret = HI_DRV_PLCIPHER_CreateHandle(PLCipher);
            break;
        }

        case CMD_PLCIPHER_DESTROYHANDLE:
        {
            HI_HANDLE hPLCipherChn = *(HI_HANDLE *)argp;
            ret = HI_DRV_PLCIPHER_DestroyHandle(hPLCipherChn);
            break;
        }

        case CMD_PLCIPHER_GETATTR:
        {
            PLCIPHER_CONFIG_S *pstAttr = (PLCIPHER_CONFIG_S *)argp;
            ret = HI_DRV_PLCIPHER_GetAttr(pstAttr->Handle, &pstAttr->stPlCipherAtts);
            break;
        }

        case CMD_PLCIPHER_SETATTR:
        {
            PLCIPHER_CONFIG_S stAttr = *(PLCIPHER_CONFIG_S *)argp;
            ret = HI_DRV_PLCIPHER_SetAttr(stAttr.Handle, &stAttr.stPlCipherAtts);
            break;
        }

        case CMD_PLCIPHER_SETKEY:
        {
            PLCIPHER_SetKey *pstCIData = (PLCIPHER_SetKey *)argp;
            ret = HI_DRV_PLCIPHER_SetKeyIV(pstCIData);
            break;
        }
        case CMD_PLCIPHER_ENCRYPT:
        {
            PLCIPHER_DATA_S *pstCIData = (PLCIPHER_DATA_S *)argp;

            ret = HI_DRV_PLCIPHER_Encrypt(pstCIData);
            break;
        }
        case CMD_PLCIPHER_DECRYPT:
        {
            PLCIPHER_DATA_S *pstCIData = (PLCIPHER_DATA_S *)argp;

            ret = HI_DRV_PLCIPHER_Decrypt(pstCIData);
            break;
        }
        default:
        {
            HI_ERR_PLCIPHER("Unsupport cmd, MOD_ID=0x%02X, NR=0x%02x, SIZE=0x%02x!\n", _IOC_TYPE (cmd), _IOC_NR (cmd), _IOC_SIZE(cmd));
            ret = HI_FAILURE;
            break;
        }
    }

    return ret;
}

static long DRV_PLCIPHER_Ioctl(struct file *ffile, unsigned int cmd, unsigned long arg)
{
    long ret;

    ret = (long)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, PLCIPHER_Ioctl);

    return ret;
}

/** <* ref from linux/fs.h @by sdk */
static struct file_operations DRV_PLCIPHER_Fops=
{
    .owner            = THIS_MODULE,
    .open             = DRV_PLCIPHER_Open,
    .unlocked_ioctl   = DRV_PLCIPHER_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl     = DRV_PLCIPHER_Ioctl,
#endif
    .release          = DRV_PLCIPHER_Release,
};

static HI_S32  plcipher_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    HI_DRV_PLCIPHER_Suspend();
    HI_PRINT("PLCIPHER suspend OK\n");
    return 0;
}

static HI_S32 plcipher_pm_resume(PM_BASEDEV_S *pdev)
{
    HI_S32 ret = HI_SUCCESS;

    ret = HI_DRV_PLCIPHER_Resume();
    if(ret != HI_SUCCESS)
    {
        HI_FATAL_PLCIPHER("PLCIPHER resume failed!\n");
        return HI_FAILURE;
    }

    HI_PRINT("PLCIPHER resume OK\n");
    return HI_SUCCESS;
}

static PM_BASEOPS_S plcipher_drvops = {
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = plcipher_pm_suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = plcipher_pm_resume,
};

HI_S32 PLCIPHER_DRV_ModInit(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    strncpy(g_PLCipherDevice.devfs_name, UMAP_DEVNAME_PLCIPHER, strlen(UMAP_DEVNAME_PLCIPHER));
    g_PLCipherDevice.fops = &DRV_PLCIPHER_Fops;
    g_PLCipherDevice.minor = UMAP_MIN_MINOR_PLCIPHER;
    g_PLCipherDevice.owner  = THIS_MODULE;
    g_PLCipherDevice.drvops = &plcipher_drvops;

    ret = HI_DRV_MODULE_Register(HI_ID_PLCIPHER, PLCIPHER_NAME, (HI_VOID *)&s_PlcipherExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_PLCIPHER("HI_DRV_MODULE_Register failed\n");
        return ret;
    }

    if (HI_DRV_DEV_Register(&g_PLCipherDevice) < 0)
    {
        HI_FATAL_PLCIPHER("register PLCIPHER failed.\n");
        return HI_FAILURE;
    }

    g_u32PLCipherRegBase = ioremap_nocache(PLCIPHER_REG_BASE_ADDR_PHY, 0x10000);
    if (g_u32PLCipherRegBase == HI_NULL)
    {
        HI_FATAL_PLCIPHER("ioremap_nocache PLCipher Reg failed\n");
        return ret;
    }

#if(1 ==  HI_PROC_SUPPORT)
    PLCIPHER_DRV_ProcInit();
#endif

    ret = HI_DRV_PLCIPHER_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }
#ifdef MODULE
    HI_PRINT("Load hi_plcipher.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID PLCIPHER_DRV_ModExit(HI_VOID)
{

#if(1 ==  HI_PROC_SUPPORT)
    PLCIPHER_DRV_ProcDeInit();
#endif
    iounmap(g_u32PLCipherRegBase);
    (HI_VOID)HI_DRV_PLCIPHER_DeInit();
    HI_DRV_MODULE_UnRegister(HI_ID_PLCIPHER);
    HI_DRV_DEV_UnRegister(&g_PLCipherDevice);
    return ;
}

#ifdef MODULE
module_init(PLCIPHER_DRV_ModInit);
module_exit(PLCIPHER_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

