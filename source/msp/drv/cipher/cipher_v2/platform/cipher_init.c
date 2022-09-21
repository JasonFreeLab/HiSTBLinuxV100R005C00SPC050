/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : cipher_init.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"
#include "spacc_body.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

extern HI_S32 DRV_CIPHER_ProcGetStatus(CIPHER_CHN_STATUS_S *pstCipherStatus);
extern HI_S32 CIPHER_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *argp);
extern HI_S32 DRV_CIPHER_Open(struct inode * inode, struct file * file);
extern HI_S32 DRV_CIPHER_Release(struct inode * inode, struct file * file);
extern HI_S32 CIPHER_MODULE_Init(HI_VOID);
extern HI_VOID CIPHER_MODULE_Exit(HI_VOID);
extern CIPHER_EXPORT_FUNC_S s_CipherExportFuncs;

CIPHER_EXPORT_FUNC_S s_CipherExportFuncs =
{
    .pfnCipherCreateHandle      = HI_DRV_CIPHER_CreateHandle,
//    .pfnCipherConfigChn         = HI_DRV_CIPHER_ConfigChnEx,
    .pfnCipherDestroyHandle     = HI_DRV_CIPHER_DestroyHandle,
    .pfnCipherEncrypt           = HI_DRV_CIPHER_Encrypt,
    .pfnCipherDecrypt           = HI_DRV_CIPHER_Decrypt,
    .pfnCipherEncryptMulti      = HI_DRV_CIPHER_EncryptMulti,
    .pfnCipherDecryptMulti      = HI_DRV_CIPHER_DecryptMulti,
    .pfnCipherGetRandomNumber   = HI_DRV_CIPHER_GetRandomNumber,
//    .pfnCipherGetHandleConfig   = HI_DRV_CIPHER_GetHandleConfigEx,
    .pfnCipherLoadHdcpKey       = HI_DRV_CIPHER_LoadHdcpKey,
    .pfnCipherSoftReset         = HI_DRV_CIPHER_SoftReset,
    .pfnCipherCalcHashInit      = HI_DRV_CIPHER_CalcHashInit,
    .pfnCipherCalcHashUpdate    = HI_DRV_CIPHER_CalcHashUpdate,
    .pfnCipherCalcHashFinal     = HI_DRV_CIPHER_CalcHashFinal,
    .pfnCipherResume            = HI_DRV_CIPHER_Resume,
    .pfnCipherSuspend           = HI_DRV_CIPHER_Suspend,
    .pfnCipherEncryptHDCPKey    = HI_DRV_CIPHER_EncryptHDCPKey,
    .pfnCipherSetHdmiReadClk    = HI_DRV_CIPHER_SetHdmiReadClk,
    .pfnCipherSetIV             = HI_DRV_CIPHER_SetIV,
};

#define CIPHER_NAME     "HI_CIPHER"

HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S g_stFlashHdcpKey;
HI_BOOL g_bHDCPKeyLoadFlag = HI_FALSE;
static UMAP_DEVICE_S    g_CipherDevice;

HI_VOID HI_DRV_CIPHER_Suspend(HI_VOID)
{
    DRV_CIPHER_Suspend();
}

HI_S32 HI_DRV_CIPHER_Resume(HI_VOID)
{
    HI_S32 ret;

    ret = DRV_CIPHER_Resume();
    if(HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    if(HI_TRUE == g_bHDCPKeyLoadFlag)
    {
        ret = DRV_CIPHER_LoadHdcpKey(&g_stFlashHdcpKey);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("Load hdcp key failed!\n");
        }
        else
        {
            HI_INFO_CIPHER("Load hdcp key success!\n");
        }
    }

    return  ret;
}

static HI_S32  cipher_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    HI_DRV_CIPHER_Suspend();
    HI_PRINT("CIPHER suspend OK\n");
    return 0;
}

static HI_S32 cipher_pm_resume(PM_BASEDEV_S *pdev)
{
    HI_S32 ret = HI_SUCCESS;

    ret = HI_DRV_CIPHER_Resume();
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CIPHER resume failed!\n");
        return HI_FAILURE;
    }

    HI_PRINT("CIPHER resume OK\n");
    return HI_SUCCESS;
}

HI_S32 HI_DRV_CIPHER_SoftReset()
{
    HI_S32 ret = HI_SUCCESS;

    (HI_VOID)HI_DRV_CIPHER_Suspend();

    ret = HI_DRV_CIPHER_Resume();
    if( HI_SUCCESS != ret )
    {
        HI_ERR_CIPHER("Cipher Soft Reset failed in cipher resume!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/******* proc function begin ********/
#if (1 == HI_PROC_SUPPORT)
static HI_S32 CIPHER_ProcGetStatus(CIPHER_CHN_STATUS_S *pstCipherStatus)
{
    return DRV_CIPHER_ProcGetStatus(pstCipherStatus);
}

HI_S32 CIPHER_ProcRead(struct seq_file *p, HI_VOID *v)
{
    CIPHER_CHN_STATUS_S stCipherStatus[8];
    int i = 0;
    HI_S32 ret = HI_SUCCESS;

    PROC_PRINT(p, "\n------------------------------------------CIPHER STATUS-----------------------------------------------------------------------------------------------\n");
    PROC_PRINT(p, "Chnid   Status   Decrypt   Alg   Mode   KeyLen    Addr in/out      KeyFrom  INT-RAW in/out  INT-EN in/out INT_OCNTCFG    IVOUT\n");

    memset(&stCipherStatus, 0, sizeof(stCipherStatus));
    for(i = 0; i < 8; i++)
    {
        stCipherStatus[i].u32ChnId = i;
    }

    ret = CIPHER_ProcGetStatus((CIPHER_CHN_STATUS_S *)&stCipherStatus);
    if(HI_FAILURE == ret)
    {
        PROC_PRINT(p, "CIPHER_ProcGetStatus failed!\n");
        return HI_FAILURE;
    }

    for(i = CIPHER_PKGx1_CHAN; i <= CIPHER_PKGxN_CHAN_MAX; i++)
    {
        PROC_PRINT(p, " %d       %s      %d      %s  %s    %03d    %08x/%08x    %s           %d/%d            %d/%d        %08x     %s\n",
                        i,
                        stCipherStatus[i].ps8Openstatus,
                        stCipherStatus[i].bIsDecrypt,
                        stCipherStatus[i].ps8Alg,
                        stCipherStatus[i].ps8Mode,
                        stCipherStatus[i].u32KeyLen,
                        stCipherStatus[i].u32DataInAddr,
                        stCipherStatus[i].u32DataOutAddr,
                        stCipherStatus[i].ps8KeyFrom,
                        stCipherStatus[i].bInINTRaw,
                        stCipherStatus[i].bOutINTRaw,
                        stCipherStatus[i].bInINTEn,
                        stCipherStatus[i].bOutINTEn,
                        stCipherStatus[i].u32OutINTCount,
                        stCipherStatus[i].u8IVString);
    }

    return HI_SUCCESS;
}

HI_S32 CIPHER_ProcWrite(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
{
    return count;
}

static HI_VOID CIPHER_DRV_ProcInit(HI_VOID)
{
    DRV_PROC_EX_S stProc = {0};

    stProc.fnRead   = CIPHER_ProcRead;
    stProc.fnWrite  = CIPHER_ProcWrite;

    HI_DRV_PROC_AddModule(HI_MOD_CIPHER, &stProc, NULL);
}

static HI_VOID CIPHER_DRV_ProcDeInit(HI_VOID)
{
    HI_DRV_PROC_RemoveModule(HI_MOD_CIPHER);
}
#endif
/******* proc function end ********/

static long DRV_CIPHER_Ioctl(struct file *ffile, unsigned int cmd, unsigned long arg)
{
    long ret;

    ret = (long)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, CIPHER_Ioctl);

    return ret;
}

static struct file_operations DRV_CIPHER_Fops=
{
    .owner            = THIS_MODULE,
    .open             = DRV_CIPHER_Open,
    .unlocked_ioctl   = DRV_CIPHER_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl     = DRV_CIPHER_Ioctl,
#endif
    .release          = DRV_CIPHER_Release,
};

static PM_BASEOPS_S cipher_drvops = {
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = cipher_pm_suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = cipher_pm_resume,
};

HI_S32 CIPHER_DRV_ModInit(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    snprintf(g_CipherDevice.devfs_name, sizeof(UMAP_DEVNAME_CIPHER), UMAP_DEVNAME_CIPHER);
    g_CipherDevice.fops = &DRV_CIPHER_Fops;
    g_CipherDevice.minor = UMAP_MIN_MINOR_CIPHER;
    g_CipherDevice.owner  = THIS_MODULE;
    g_CipherDevice.drvops = &cipher_drvops;

    if (HI_DRV_DEV_Register(&g_CipherDevice) < 0)
    {
        HI_ERR_CIPHER("register CIPHER failed.\n");
        return HI_FAILURE;
    }

    ret = HI_DRV_MODULE_Register(HI_ID_CIPHER, CIPHER_NAME, (HI_VOID*)&s_CipherExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("HI_DRV_MODULE_Register failed\n");
        return ret;
    }

    ret = CIPHER_MODULE_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

/******* proc function begin ********/
#if (1 == HI_PROC_SUPPORT)
    CIPHER_DRV_ProcInit();
#endif
/******* proc function end ********/

#ifdef MODULE
    HI_PRINT("Load hi_cipher.ko success.\t(%s)\n", VERSION_STRING);
#endif
    return HI_SUCCESS;
}

HI_VOID CIPHER_DRV_ModExit(HI_VOID)
{

/******* proc function begin ********/
#if (1 == HI_PROC_SUPPORT)
    CIPHER_DRV_ProcDeInit();
#endif
/******* proc function end ********/

    HI_DRV_DEV_UnRegister(&g_CipherDevice);

    (HI_VOID)CIPHER_MODULE_Exit();

    HI_DRV_MODULE_UnRegister(HI_ID_CIPHER);

    return ;
}

#ifdef MODULE
module_init(CIPHER_DRV_ModInit);
module_exit(CIPHER_DRV_ModExit);
#endif

MODULE_AUTHOR("Hi3720 MPP GRP");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


