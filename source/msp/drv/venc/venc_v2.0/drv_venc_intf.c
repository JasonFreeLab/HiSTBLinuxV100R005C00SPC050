
/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : viu.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       :
  Description   :
  History       :
  1.Date        : 2010/03/17
    Author      : sdk
    Modification: Created file
******************************************************************************/

#include <asm/uaccess.h>
#include <linux/delay.h>

#include "hi_unf_common.h"
#include "hi_drv_dev.h"
#include "drv_venc_ext.h"
#include "hi_drv_file.h"
#include "hi_drv_proc.h"
#include "hi_drv_module.h"
#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_ioctl.h"
#include "drv_venc.h"
#include "drv_omxvenc.h"
#include "hi_kernel_adapt.h"

#ifdef VENC_SUPPORT_JPGE
#include "drv_jpge_ext.h"
#endif

static UMAP_DEVICE_S g_VencRegisterData;

#define HI_VENC_LOCK() (void)pthread_mutex_lock(&g_VencMutex);
#define HI_VENC_UNLOCK() (void)pthread_mutex_unlock(&g_VencMutex);

#ifdef VENC_SUPPORT_JPGE
JPGE_EXPORT_FUNC_S *pJpgeFunc = HI_NULL;
#endif

extern int vedu_init( void );
extern OPTM_VENC_CHN_S g_stVencChn[HI_VENC_MAX_CHN];

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define Smooth_printk printk
#else
#define Smooth_printk(format, arg...)
#endif


#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        if (hVencChn == NULL)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_CHN_BY_UHND(u32VeChn, hVencUsrChn) \
    do {\
        if (hVencUsrChn == HI_INVALID_HANDLE)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hUsrHandle == hVencUsrChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_UPDATE_2(data,curdata) \
    do{\
          *(data + 1) = *data;\
          *data = curdata;\
        }while(0)

HI_BOOL gb_IsVencChanAlive[HI_VENC_MAX_CHN] = {HI_FALSE};
//HI_HANDLE gh_AttachedSrc[HI_VENC_MAX_CHN] = {HI_INVALID_HANDLE};

/*============Deviece===============*/

//VENC device open times
atomic_t g_VencCount = ATOMIC_INIT(0);


HI_CHAR g_szYUVType[][8] = {"YUV_420", "YUV_422", "YUV_444", "UNKNOW"};
HI_CHAR g_szStoreType[][12] = {"SEMIPLANNAR", "PLANNAR", "PACKAGE", "UNKNOW"};

//static HI_S32  VENC_ProcRead(struct seq_file *p, HI_VOID *v);
//static HI_S32  VENC_ProcWrite(struct file * file, const char __user * buf, size_t count, loff_t *ppos);
HI_VOID VENC_TimerFunc(HI_LENGTH_T value);

/*static VENC_EXPORT_FUNC_S s_VencExportFuncs =
{
    .pfnVencEncodeFrame = VENC_DRV_EflEncodeFrame,
};*/

HI_S32 VENC_DRV_Resume(HI_VOID);
HI_S32 VENC_DRV_Suspend(HI_VOID);

VENC_EXPORT_FUNC_S s_VencExportFuncs =
{
    /*.pfnVencEncodeFrame = VENC_DRV_EflEncodeFrame,*/
    .pfnVencQueueFrame   = VENC_DRV_EflQFrameByAttach,
    .pfnVencWakeUpThread = VENC_DRV_EflWakeUpThread,
    .pfnVencResume       = VENC_DRV_Resume,
    .pfnVencSuspend      = VENC_DRV_Suspend,
    //.pfnSetSrcInfo       = VENC_DRV_SetSrcInfo,  //fix me
};

/*typedef enum
{
    VENC_PROC_TIMEMODE = 0,
    VENC_PROC_FRAMEMODE,
    VENC_PROC_BUTT
} VENC_PROC_COMMAND_E;*/

struct timer_list vencTimer;

HI_DECLARE_MUTEX(g_VencMutex);

HI_U32 g_u32VencOpenFlag = 0;

static HI_S32 VENC_DRV_Open(struct inode *finode, struct file  *ffile)
{
    HI_S32 Ret, i;
    //HI_CHAR ProcName[12];
    //DRV_PROC_ITEM_S  *pProcItem;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    if (1 == atomic_inc_return(&g_VencCount))
    {
        //VENC_DRV_BoardInit();

        VENC_DRV_InitEvent();
        Ret = VENC_DRV_EflOpenVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("VeduEfl_OpenVedu failed, ret=%d\n", Ret);
            atomic_dec(&g_VencCount);
            up(&g_VencMutex);
            return HI_FAILURE;
        }


        for (i = 0; i < HI_VENC_MAX_CHN; i++)
        {
            memset(&(g_stVencChn[i]), 0, sizeof(OPTM_VENC_CHN_S));
            g_stVencChn[i].hVEncHandle = NULL;
            g_stVencChn[i].hUsrHandle = HI_INVALID_HANDLE;
        }

        init_timer(&vencTimer);
        vencTimer.expires  = jiffies + (HZ);
        vencTimer.function = VENC_TimerFunc;
        add_timer(&vencTimer);
    }

    g_u32VencOpenFlag = 1;
    up(&g_VencMutex);

#ifdef VENC_SUPPORT_JPGE
    Ret = HI_DRV_MODULE_GetFunction(HI_ID_JPGENC, (HI_VOID**)&pJpgeFunc);
    if(HI_SUCCESS != Ret)
    {
         HI_ERR_VENC("GetFunction from JPGE  failed.\n");
         goto error_0;
    }
    pJpgeFunc->pfnJpgeInit();
#endif
    return HI_SUCCESS;

#ifdef VENC_SUPPORT_JPGE
error_0:
    del_timer_sync(&vencTimer);
    VENC_DRV_EflCloseVedu();

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    atomic_dec(&g_VencCount);
    up(&g_VencMutex);

    return HI_FAILURE;
#endif
}

static HI_S32 VENC_DRV_Close(struct inode *finode, struct file  *ffile)
{
    HI_U32 i = 0;
    HI_S32 Ret = 0;

   // HI_CHAR ProcName[12];

   Ret = down_interruptible(&g_VencMutex);
   if (Ret != HI_SUCCESS)
   {
       HI_WARN_VENC("call down_interruptible err!\n");
   }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if ((g_stVencChn[i].pWhichFile == ffile)
            && (g_stVencChn[i].hVEncHandle != NULL))
        {
            HI_INFO_VENC("Try VENC_DestroyChn %d/%#p.\n", i, g_stVencChn[i].hVEncHandle);
            Ret |= VENC_DRV_DestroyChn(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_WARN_VENC("force DestroyChn %d failed, Ret=%#x.\n", i, Ret);
            }
            g_stVencChn[i].pWhichFile = HI_NULL;
        }
    }

    if (atomic_dec_and_test(&g_VencCount))
    {

        del_timer_sync(&vencTimer);
        VENC_DRV_EflCloseVedu();

#ifdef VENC_SUPPORT_JPGE
        if (pJpgeFunc)
        {
            pJpgeFunc->pfnJpgeDeInit();
        }
#endif

        //VENC_DRV_BoardDeinit();   //change to destroy channel
    }
    g_u32VencOpenFlag = 0;
    up(&g_VencMutex);


    return HI_SUCCESS;
}

HI_S32 VENC_DRV_Suspend(HI_VOID)
{
    HI_U32 i = 0;
    HI_S32 Ret;

    if (!g_u32VencOpenFlag)
    {
        HI_PRINT("VENC suspend OK\n");
        return 0;
    }

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        HI_INFO_VENC("suspend venc channel %d handle %p, invalid = %x\n", i, g_stVencChn[i].hVEncHandle,
                      HI_INVALID_HANDLE );
        if (g_stVencChn[i].hVEncHandle != NULL && g_stVencChn[i].bEnable == 1)
        {

            Ret = VENC_DRV_StopReceivePic(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_WARN_VENC("VENC_StopReceivePic %d failed, Ret=%#x.\n", i, Ret);
            }

            gb_IsVencChanAlive[i] = HI_TRUE;
        }
        else
        {
            gb_IsVencChanAlive[i] = HI_FALSE;
        }
    }

    if (atomic_dec_and_test(&g_VencCount))
    {
        VENC_DRV_EflSuspendVedu();

        //VENC_DRV_BoardDeinit();  //change to destroy channel
    }

    HI_PRINT("VENC suspend OK\n");
    up(&g_VencMutex);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_Resume(HI_VOID)
{
   HI_S32 Ret, i;
    //HI_MOD_ID_E enModId;

    if (!g_u32VencOpenFlag)
    {
        HI_PRINT("VENC resume OK\n");
        return 0;
    }

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    if (1 == atomic_inc_return(&g_VencCount))
    {
        //VENC_DRV_BoardInit();   ==>rmove to the
        VENC_DRV_InitEvent();
        Ret = VENC_DRV_EflResumeVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("VeduEfl_OpenVedu failed, ret=%d\n", Ret);
            atomic_dec(&g_VencCount);
            up(&g_VencMutex);
            return HI_FAILURE;
        }
    }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (gb_IsVencChanAlive[i])
        {
#ifdef HI_SMMU_SUPPORT
            {
                HI_U32 u32ptaddr,u32err_rdaddr,u32err_wraddr;
                HI_DRV_SMMU_GetPageTableAddr(&u32ptaddr,&u32err_rdaddr, &u32err_wraddr);
                g_stVencChn[i].hVEncHandle->stHal.u32SmmuPageBaseAddr = u32ptaddr;
                g_stVencChn[i].hVEncHandle->stHal.u32SmmuErrReadAddr  = u32err_rdaddr;
                g_stVencChn[i].hVEncHandle->stHal.u32SmmuErrWriteAddr = u32err_wraddr;
            }
#endif
            HI_INFO_VENC(" h %d, fr %d. gop %d\n ",
                          g_stVencChn[i].stChnUserCfg.u32Height,
                          g_stVencChn[i].stChnUserCfg.u32TargetFrmRate,
                          g_stVencChn[i].stChnUserCfg.u32Gop);
            Ret = VENC_DRV_StartReceivePic(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_FATAL_VENC(KERN_ERR "Resume VENC_StartReceivePic %d failed.\n", i);
                continue;
            }
        }
    }

    HI_PRINT("VENC resume OK\n");
    up(&g_VencMutex);
    return HI_SUCCESS;
}

HI_S32 VENC_Ioctl_Create(struct file *file, HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;

    VENC_INFO_CREATE_S *pstCreateInfo = (VENC_INFO_CREATE_S *)arg;
    VeduEfl_EncPara_S* hKernVencChn = NULL;
    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_CreateChn((VeduEfl_EncPara_S**)&hKernVencChn, (venc_chan_cfg*) & (pstCreateInfo->stAttr),
                             (VENC_CHN_INFO_S*) & (pstCreateInfo->stVeInfo), pstCreateInfo->bOMXChn, file);

    if (hKernVencChn == HI_NULL)
    {
        up(&g_VencMutex);

        return Ret;
    }

    D_VENC_GET_CHN(u32Index, hKernVencChn);

    if (u32Index >= HI_VENC_MAX_CHN)
    {
        up(&g_VencMutex);

        return HI_ERR_VENC_CREATE_ERR;
    }
    g_stVencChn[u32Index].hUsrHandle = GET_VENC_CHHANDLE(u32Index);
    pstCreateInfo->hVencChn = g_stVencChn[u32Index].hUsrHandle;
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_Destroy(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *phVencChn = (HI_HANDLE *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *phVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
        up(&g_VencMutex);

        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_DestroyChn(g_stVencChn[u32Index].hVEncHandle);

    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_AttachInput(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ATTACH_S *pAttachInfo = (VENC_INFO_ATTACH_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pAttachInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_AttachInput(g_stVencChn[u32Index].hVEncHandle, pAttachInfo->hSrc, pAttachInfo->enModId);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_DetachInput(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ATTACH_S *pAttachInfo = (VENC_INFO_ATTACH_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pAttachInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    pAttachInfo->enModId = (HI_MOD_ID_E)((g_stVencChn[u32Index].hSource & 0xff0000) >> 16);
    Ret = VENC_DRV_DetachInput(g_stVencChn[u32Index].hVEncHandle,g_stVencChn[u32Index].hSource, pAttachInfo->enModId);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_SetSrc(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_SET_SRC_S *pSetSrc = (VENC_SET_SRC_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pSetSrc->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_SetSrcInfo(g_stVencChn[u32Index].hVEncHandle,&(pSetSrc->stVencSrc));
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_AcquireStream(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ACQUIRE_STREAM_S *pstAcqStrm = (VENC_INFO_ACQUIRE_STREAM_S*)arg;
    VeduEfl_EncPara_S* tempHandle = NULL;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstAcqStrm->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    tempHandle = g_stVencChn[u32Index].hVEncHandle;
    up(&g_VencMutex);

    Ret = VENC_DRV_AcquireStream(tempHandle,
                                 &(pstAcqStrm->stStream),
                                 pstAcqStrm->u32BlockFlag,
                                 &(pstAcqStrm->stBufOffSet));

    return Ret;
}

HI_S32 VENC_Ioctl_ReleaseStream(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ACQUIRE_STREAM_S *pstAcqStrm = (VENC_INFO_ACQUIRE_STREAM_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstAcqStrm->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_ReleaseStream(g_stVencChn[u32Index].hVEncHandle, pstAcqStrm);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_StartRecvPic(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *pHandle = (HI_HANDLE*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *pHandle);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_StartReceivePic(g_stVencChn[u32Index].hVEncHandle);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_StopRecvPic(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *pHandle = (HI_HANDLE*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *pHandle);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_StopReceivePic(g_stVencChn[u32Index].hVEncHandle);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_SetChnAttr(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_CREATE_S *pstCreateInfo = (VENC_INFO_CREATE_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstCreateInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_SetAttr(g_stVencChn[u32Index].hVEncHandle, &(pstCreateInfo->stAttr.VencUnfAttr),&(pstCreateInfo->stVeInfo));
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_GetChnAttr(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_CREATE_S *pstCreateInfo = (VENC_INFO_CREATE_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstCreateInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_GetAttr(g_stVencChn[u32Index].hVEncHandle, &(pstCreateInfo->stAttr.VencUnfAttr));
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_RequestIFrame(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *pHandle = (HI_HANDLE*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *pHandle);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[u32Index].hJPGE == HI_INVALID_HANDLE)
    {
       Ret = VENC_DRV_RequestIFrame(g_stVencChn[u32Index].hVEncHandle);
    }
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_QueueFrame(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_QUEUE_FRAME_S *pQueueFrameInfo = (VENC_INFO_QUEUE_FRAME_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pQueueFrameInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[u32Index].bOMXChn)
    {
       Ret = VENC_DRV_QueueFrame_OMX(g_stVencChn[u32Index].hVEncHandle, &(pQueueFrameInfo->stVencFrame_OMX));
    }
    else
    {
       Ret = VENC_DRV_QueueFrame(g_stVencChn[u32Index].hVEncHandle, &(pQueueFrameInfo->stVencFrame));
    }

    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_DequeueFrame(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_QUEUE_FRAME_S *pQueueFrameInfo = (VENC_INFO_QUEUE_FRAME_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pQueueFrameInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_DequeueFrame(g_stVencChn[u32Index].hVEncHandle,&(pQueueFrameInfo->stVencFrame));
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_GetCapability(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_VENC_CAP_S *pstCapability = (HI_UNF_VENC_CAP_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_GetCapability(pstCapability);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_GetMsg(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_GET_MSG_S *pMessageInfo   = (VENC_INFO_GET_MSG_S *)arg;
    VeduEfl_EncPara_S* tempHandle = NULL;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pMessageInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    tempHandle = g_stVencChn[u32Index].hVEncHandle;
    up(&g_VencMutex);

    Ret = VENC_DRV_GetMessage_OMX(tempHandle,&(pMessageInfo->msg_info_omx));

    return Ret;
}

HI_S32 VENC_Ioctl_MmzMap(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_VENC_MMZ_PHY_S* pMMZPhyInfo = (VENC_INFO_VENC_MMZ_PHY_S*)arg;
    VENC_INFO_MMZ_MAP_S pMMBInfo;

    pMMBInfo.stVencBuf.phyaddr = pMMZPhyInfo->phyaddr;
    pMMBInfo.stVencBuf.bufsize = pMMZPhyInfo->bufsize;
    D_VENC_GET_CHN_BY_UHND(u32Index, pMMZPhyInfo->hVencChn);
    D_VENC_CHECK_CHN(u32Index);

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_MMZ_Map_OMX(u32Index,&(pMMBInfo.stVencBuf) );
    up(&g_VencMutex);
    if (HI_SUCCESS == Ret)
    {
        pMMZPhyInfo->vir2phy_offset = (HI_VIRT_ADDR_T)pMMBInfo.stVencBuf.kernel_viraddr - (HI_VIRT_ADDR_T)pMMBInfo.stVencBuf.phyaddr;
    }

    return Ret;
}

HI_S32 VENC_Ioctl_MmzUmmap(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_VENC_MMZ_PHY_S* pMMZPhyInfo = (VENC_INFO_VENC_MMZ_PHY_S*)arg;
    VENC_INFO_MMZ_MAP_S pMMBInfo;

    pMMBInfo.stVencBuf.phyaddr = pMMZPhyInfo->phyaddr;
    pMMBInfo.stVencBuf.bufsize = pMMZPhyInfo->bufsize;
    D_VENC_GET_CHN_BY_UHND(u32Index, pMMZPhyInfo->hVencChn);
    D_VENC_CHECK_CHN(u32Index);
    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_MMZ_UMMap_OMX(u32Index,&(pMMBInfo.stVencBuf) );
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_QueueStream(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_QUEUE_FRAME_S *pstQueStrm = (VENC_INFO_QUEUE_FRAME_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstQueStrm->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_QueueStream_OMX(g_stVencChn[u32Index].hVEncHandle, &(pstQueStrm->stVencFrame_OMX));
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl_FlushPort(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_FLUSH_PORT_S *pstFlushPort = (VENC_INFO_FLUSH_PORT_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstFlushPort->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_FlushPort_OMX(g_stVencChn[u32Index].hVEncHandle, pstFlushPort->u32PortIndex);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *arg)
{
    HI_S32 Ret = HI_FAILURE;

    switch (cmd)
    {
        case CMD_VENC_CREATE_CHN:
        {
            Ret = VENC_Ioctl_Create(file, arg);
        }
        break;

        case CMD_VENC_DESTROY_CHN:
        {
            Ret = VENC_Ioctl_Destroy(arg);
        }
        break;

        case CMD_VENC_ATTACH_INPUT:
        {
            Ret = VENC_Ioctl_AttachInput(arg);
        }
        break;

        case CMD_VENC_DETACH_INPUT:
        {
            Ret = VENC_Ioctl_DetachInput(arg);
        }
        break;

        case CMD_VENC_SET_SRC:
        {
            Ret = VENC_Ioctl_SetSrc(arg);
        }
        break;

        case CMD_VENC_ACQUIRE_STREAM:
        {
            Ret = VENC_Ioctl_AcquireStream(arg);
        }
        break;

        case CMD_VENC_RELEASE_STREAM:
        {
            Ret = VENC_Ioctl_ReleaseStream(arg);
        }
        break;

        case CMD_VENC_START_RECV_PIC:
        {
            Ret = VENC_Ioctl_StartRecvPic(arg);
        }
        break;

        case CMD_VENC_STOP_RECV_PIC:
        {
            Ret = VENC_Ioctl_StopRecvPic(arg);
        }
        break;

        case CMD_VENC_SET_CHN_ATTR:
        {
            Ret = VENC_Ioctl_SetChnAttr(arg);
        }
        break;

        case CMD_VENC_GET_CHN_ATTR:
        {
            Ret = VENC_Ioctl_GetChnAttr(arg);
        }
        break;

        case CMD_VENC_REQUEST_I_FRAME:
        {
            Ret = VENC_Ioctl_RequestIFrame(arg);
        }
        break;

        case CMD_VENC_QUEUE_FRAME:                 //both omxvenc & venc use!!
        {
            Ret = VENC_Ioctl_QueueFrame(arg);
        }
        break;

        case CMD_VENC_DEQUEUE_FRAME:
        {
            Ret = VENC_Ioctl_DequeueFrame(arg);
        }
        break;

        case CMD_VENC_GET_CAP:
        {
            Ret = VENC_Ioctl_GetCapability(arg);
        }
        break;

        case CMD_VENC_GET_MSG:
        {
            Ret = VENC_Ioctl_GetMsg(arg);
        }
        break;

        case CMD_VENC_MMZ_MAP:
        {
            Ret = VENC_Ioctl_MmzMap(arg);
        }
        break;

        case CMD_VENC_MMZ_UMMAP:
        {
            Ret = VENC_Ioctl_MmzUmmap(arg);
        }
        break;

        case CMD_VENC_QUEUE_STREAM:                    //juse omxvenc use this api
        {
            Ret = VENC_Ioctl_QueueStream(arg);
        }
        break;

        case CMD_VENC_FLUSH_PORT:
        {
            Ret = VENC_Ioctl_FlushPort(arg);
        }
        break;

        default:
        {
            HI_ERR_VENC("venc cmd unknown:%x\n", cmd);
        }
        break;
    }

    return Ret;
}

static long VENC_DRV_Ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    long Ret;

    Ret = (long)HI_DRV_UserCopy(file->f_path.dentry->d_inode, file, cmd, arg, VENC_Ioctl);
    return Ret;
}

static struct file_operations VENC_FOPS =
{
    .owner            = THIS_MODULE,
    .open            = VENC_DRV_Open,
    .unlocked_ioctl = VENC_DRV_Ioctl,
    #ifdef CONFIG_COMPAT
    .compat_ioctl   = VENC_DRV_Ioctl,
    #endif
    .release        = VENC_DRV_Close,
};

/*****************************************************************************
 Prototype    : VENC_DRV_Suspend
 Description  : VENC module standby function
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
static int  venc_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
#if 1
    VENC_DRV_Suspend();
#else
    int i;
    int ret;
    HI_FATAL_VENC("entering venc_pm_suspend\n");

    // 0  now all usr processes are in sleep status, any delay is serious error!
    ret = down_trylock(&g_VencMutex);
    if (ret)
    {
        HI_FATAL_VENC("err0: lock !\n");
        return -1;
    }

    // 1.0
    if (atomic_read(&g_VencCount))
    {
        up(&g_VencMutex);
        HI_FATAL_VENC("err1: not close all file \n");
        return -1;
    }

    // 1.2
    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (g_stVencChn[i].pWhichFile)
        {
            up(&g_VencMutex);
            HI_FATAL_VENC("err2: chan %d not close \n", i);
            return -1;
        }
    }

    HI_FATAL_VENC("ok !\n");
    up(&g_VencMutex);
#endif
    return 0;
}

/*****************************************************************************
 Prototype    : VENC_DRV_Resume
 Description  : VENC module wake-up function
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
static int venc_pm_resume(PM_BASEDEV_S *pdev)
{
#if 1
    VENC_DRV_Resume();
#else
 #if 0
    down_trylock(&g_VencMutex);
    up(&g_VencMutex);
 #endif
    HI_FATAL_VENC("ok !\n");
#endif
    return 0;
}

static PM_BASEOPS_S venc_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = venc_pm_suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = venc_pm_resume,
};

HI_S32 VENC_DRV_ModInit(HI_VOID)
{
    HI_U32 i;
    HI_S32 s32Ret = HI_FAILURE;


    s32Ret = VENC_DRV_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("Init drv fail!\n");
        return HI_FAILURE;
    }

    snprintf(g_VencRegisterData.devfs_name, 64, "%s", UMAP_DEVNAME_VENC);
    g_VencRegisterData.fops   = &VENC_FOPS;
    g_VencRegisterData.minor  = UMAP_MIN_MINOR_VENC;
    g_VencRegisterData.owner  = THIS_MODULE;
    g_VencRegisterData.drvops = &venc_drvops;
    if (HI_DRV_DEV_Register(&g_VencRegisterData) < 0)
    {
        HI_FATAL_VENC("register VENC failed.\n");
        return HI_FAILURE;
    }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        g_stVencChn[i].pWhichFile = NULL;
    }
    //VENC_DRV_BoardDeinit();   //fix me@
    HI_INFO_VENC("register VENC successful.\n");

#ifdef MODULE
    HI_PRINT("Load hi_venc.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return 0;
}

HI_VOID VENC_DRV_ModExit(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&g_VencRegisterData);
    VENC_DRV_Exit();

    return;
}


HI_VOID VENC_TimerFunc(HI_LENGTH_T value)
{
    HI_U32 i = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 LastSecBits = 0;
    HI_U32 BitRate = 0;
    HI_S32 RcRatio = 0;
    VeduEfl_StatInfo_S StatInfo;
    VeduEfl_EncPara_S *pstEncChnPara = NULL;
    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (g_stVencChn[i].hVEncHandle != NULL)
        {
            s32Ret = VENC_DRV_EflQueryStatInfo(g_stVencChn[i].hVEncHandle, &StatInfo);
            if (HI_SUCCESS == s32Ret)
            {
                /* video encoder does frame rate control by this value */
                g_stVencChn[i].u32LastSecEncodedFps = StatInfo.GetFrameNumOK - StatInfo.QuickEncodeSkip
                                                     -StatInfo.ErrCfgSkip - StatInfo.FrmRcCtrlSkip - StatInfo.SamePTSSkip
                                                     -StatInfo.TooFewBufferSkip - StatInfo.TooManyBitsSkip
                                                     -g_stVencChn[i].u32FrameNumLastEncoded;
                g_stVencChn[i].u32LastSecInputFps = StatInfo.GetFrameNumOK - g_stVencChn[i].u32FrameNumLastInput;
                g_stVencChn[i].u32LastSecKbps = StatInfo.StreamTotalByte - g_stVencChn[i].u32TotalByteLastEncoded;
                g_stVencChn[i].u32LastSecTryNum = StatInfo.GetFrameNumTry - g_stVencChn[i].u32LastTryNumTotal;
                g_stVencChn[i].u32LastSecOKNum = StatInfo.GetFrameNumOK - g_stVencChn[i].u32LastOKNumTotal;
                g_stVencChn[i].u32LastSecPutNum = StatInfo.PutFrameNumOK - g_stVencChn[i].u32LastPutNumTotal;
                /* save value for next calculation */
                g_stVencChn[i].u32FrameNumLastInput    = StatInfo.GetFrameNumOK;
                g_stVencChn[i].u32FrameNumLastEncoded  = StatInfo.GetFrameNumOK - StatInfo.QuickEncodeSkip - StatInfo.ErrCfgSkip
                                                       - StatInfo.FrmRcCtrlSkip - StatInfo.SamePTSSkip
                                                       - StatInfo.TooFewBufferSkip - StatInfo.TooManyBitsSkip ;
                g_stVencChn[i].u32TotalByteLastEncoded = StatInfo.StreamTotalByte;
                g_stVencChn[i].u32LastTryNumTotal      = StatInfo.GetFrameNumTry;
                g_stVencChn[i].u32LastOKNumTotal       = StatInfo.GetFrameNumOK;
                g_stVencChn[i].u32LastPutNumTotal      = StatInfo.PutFrameNumOK;

                pstEncChnPara = (VeduEfl_EncPara_S*)g_stVencChn[i].hVEncHandle;
                D_VENC_UPDATE_2(pstEncChnPara->LastSecInputFrmRate, g_stVencChn[i].u32LastSecInputFps);
                pstEncChnPara->stRc.LastSecFrameCnt = 0;
                pstEncChnPara->stRc.bFrmRateSataError = 0;

                if (g_stVencChn[i].enSrcModId != HI_ID_BUTT)
                {
                    pstEncChnPara->stRc.Waterline = pstEncChnPara->stRc.WaterlineInit;
                }

                LastSecBits = g_stVencChn[i].u32LastSecKbps * 8;
                BitRate = pstEncChnPara->stRc.BitRate;

                if (pstEncChnPara->RcDbgPrint == 1)
                {
                    if (BitRate >= LastSecBits)
                    {
                        RcRatio = (BitRate - LastSecBits) * 100 / (BitRate);
                        RcRatio = (-1) * RcRatio;
                    }
                    else
                    {
                        RcRatio = (LastSecBits - BitRate) * 100 / (BitRate);
                    }

                    HI_ERR_VENC("Targetbitrate is %d, CurBitRate is %d, FrameRate is %d, RcRatio is %d%%\n",
                                BitRate, LastSecBits, g_stVencChn[i].u32LastSecEncodedFps, RcRatio);
                }
            }
        }
    }

    vencTimer.expires  = jiffies + (HZ);
    vencTimer.function = VENC_TimerFunc;
    add_timer(&vencTimer);

    return;
}





#ifdef MODULE
module_init(VENC_DRV_ModInit);
module_exit(VENC_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
