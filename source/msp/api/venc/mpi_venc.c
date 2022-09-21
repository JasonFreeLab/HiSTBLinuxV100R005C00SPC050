/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : mpi_venc.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/03/31
  Description   :
  History       :
  1.Date        : 2010/03/31
    Author      : sdk
    Modification: Created file

******************************************************************************/

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>

#include "hi_mpi_venc.h"
#include "hi_error_mpi.h"
#include "hi_type.h"
#include "hi_mpi_mem.h"
#include "drv_venc_ioctl.h"
#include "hi_drv_struct.h"

#include "hi_mpi_vi.h"
#include "hi_mpi_win.h"
#include "hi_mpi_disp.h"
#include "mpi_mmz.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


#ifdef VENC_DPT_ONLY
#define VEDU_MMZ_ALIGN       (256)
#else
#define VEDU_MMZ_ALIGN       (64)
#endif

enum
{
    VEDU_H264  = 0,
    VEDU_JPGE  = 1,
    VEDU_H265  = 2,
};

static HI_S32 g_VEncDevFd = -1;
static const HI_CHAR g_VEncDevName[] = "/dev/" UMAP_DEVNAME_VENC;
static pthread_mutex_t g_VEncMutex = PTHREAD_MUTEX_INITIALIZER;
static VENC_CHN_INFO_S s_asrVeChnInfo[VENC_MAX_CHN_NUM];
static VENC_CHN_VirAddr_S s_asrVeChnVirAddr[VENC_MAX_CHN_NUM];

#define HI_VENC_LOCK() (void)pthread_mutex_lock(&g_VEncMutex);
#define HI_VENC_UNLOCK() (void)pthread_mutex_unlock(&g_VEncMutex);

#define CHECK_VENC_INIT() \
    do {\
        HI_VENC_LOCK(); \
        if (g_VEncDevFd < 0)\
        {\
            HI_VENC_UNLOCK(); \
            return HI_ERR_VENC_NO_INIT; \
        } \
        HI_VENC_UNLOCK(); \
    } while (0)

#define CHECK_CHANNEL_EXIST(i,max,ChnHandle) \
    do {\
        for(i = 0; i < max; i++ )\
        {\
            if (s_asrVeChnInfo[i].handle == ChnHandle)\
                break;\
        }\
        if (max == i)\
            return HI_ERR_VENC_CHN_NOT_EXIST;\
    } while (0)

HI_S32 HI_MPI_VENC_Init(HI_VOID)
{
    struct stat st;
    HI_S32 i = 0;

    HI_VENC_LOCK();

    /* Already Opened in the process*/
    if (g_VEncDevFd > 0)
    {
        HI_VENC_UNLOCK();
        return HI_SUCCESS;
    }

    g_VEncDevFd = open(g_VEncDevName, O_RDWR | O_NONBLOCK, 0);

    if (g_VEncDevFd < 0)
    {
        HI_FATAL_VENC("open VEDU err.\n");
        HI_VENC_UNLOCK();
        return HI_FAILURE;
    }


    if (HI_FAILURE == fstat(g_VEncDevFd, &st))
    {
        HI_FATAL_VENC("VEDU is not exist.\n");
        HI_VENC_UNLOCK();
        return HI_ERR_VENC_DEV_NOT_EXIST;
    }

    if (!S_ISCHR (st.st_mode))
    {
        HI_FATAL_VENC("VEDU is not device.\n");
        HI_VENC_UNLOCK();
        return HI_ERR_VENC_NOT_DEV_FILE;
    }


    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        s_asrVeChnInfo[i].handle = HI_INVALID_HANDLE;
        s_asrVeChnVirAddr[i].pStrmBufVirAddr = HI_NULL;
#ifdef HI_VENC_96mv200_SUPPORT
        s_asrVeChnVirAddr[i].pSliceBufVirAddr = HI_NULL;
#endif
        s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg  = HI_NULL;
        s_asrVeChnInfo[i].u32StrmBufPhyAddr    = HI_NULL;
        s_asrVeChnInfo[i].u32StrmBufPhyAddrJpeg = HI_NULL;
        s_asrVeChnInfo[i].u32BufSize           = 0;
        s_asrVeChnInfo[i].u32BufSizeJpeg       = 0;
    }

    HI_VENC_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VENC_DeInit(HI_VOID)
{
    HI_U32 i;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32PhyAddrBase = 0;

    HI_VENC_LOCK();

    if (g_VEncDevFd < 0)
    {
        HI_VENC_UNLOCK();

        return HI_SUCCESS;
    }

    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        if (s_asrVeChnInfo[i].handle != HI_INVALID_HANDLE)
        {
            u32PhyAddrBase = s_asrVeChnInfo[i].u32StrmBufPhyAddr - VEDU_MMZ_ALIGN;
            s32Ret = HI_MMZ_Unmap(u32PhyAddrBase);

            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_VENC("venc unmap failed!(PhyAddr = 0x%x)\n", u32PhyAddrBase);
            }
#ifdef HI_VENC_96mv200_SUPPORT
            u32PhyAddrBase = s_asrVeChnInfo[i].u32SliceBufPhyAddr;
            s32Ret = HI_MPI_MMZ_Unmap(u32PhyAddrBase);

            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_VENC("venc unmap failed!(PhyAddr = 0x%x)\n", u32PhyAddrBase);
            }
            s_asrVeChnVirAddr[i].pSliceBufVirAddr = HI_NULL;
#endif
            s_asrVeChnVirAddr[i].pStrmBufVirAddr = NULL;
        }
    }

    close(g_VEncDevFd);

    g_VEncDevFd = -1;
    HI_VENC_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VENC_SetAttr(HI_HANDLE hVencChn, const HI_UNF_VENC_CHN_ATTR_S* pstAttr)
{
    HI_S32 s32Ret, i = 0;
    VENC_INFO_CREATE_S stVencChnCreate;
    memset(&stVencChnCreate, 0, sizeof(VENC_INFO_CREATE_S));

    if (!pstAttr)
    {
        HI_ERR_VENC("para pstAttr is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    stVencChnCreate.hVencChn = hVencChn;
    stVencChnCreate.stAttr.VencUnfAttr = *pstAttr;
    stVencChnCreate.stAttr.bOmxChn = HI_FALSE;
    stVencChnCreate.stAttr.bAutoRequestIFrm = HI_FALSE;
    stVencChnCreate.stAttr.bPrependSpsPps   = HI_TRUE;
    stVencChnCreate.stAttr.ControlRateType  = VENC_DRV_ControlRateConstant;  //CBR;
    memcpy(&stVencChnCreate.stVeInfo, &s_asrVeChnInfo[i], sizeof(VENC_CHN_INFO_S));
    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_SET_CHN_ATTR, &stVencChnCreate);
    if (HI_SUCCESS == s32Ret)
    {
       if ((stVencChnCreate.stVeInfo.u32StrmBufPhyAddrJpeg != HI_NULL) && (s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg == HI_NULL))  /*h264->jpeg*/
       {
            s_asrVeChnInfo[i].u32StrmBufPhyAddrJpeg = stVencChnCreate.stVeInfo.u32StrmBufPhyAddrJpeg;
            s_asrVeChnInfo[i].u32BufSizeJpeg        = stVencChnCreate.stVeInfo.u32BufSizeJpeg;
            s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg = HI_MMAP(s_asrVeChnInfo[i].u32StrmBufPhyAddrJpeg, s_asrVeChnInfo[i].u32BufSizeJpeg);
            if (NULL == s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg)
            {
                HI_ERR_VENC("memmap JPEG's stream buffer failed.\n");
                (void)ioctl(g_VEncDevFd, CMD_VENC_DESTROY_CHN, &(stVencChnCreate.hVencChn));
                return HI_FAILURE;
            }
       }
       else if ((stVencChnCreate.stVeInfo.u32StrmBufPhyAddrJpeg == HI_NULL) && (s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg != HI_NULL)) /*jpeg->h264*/
       {
            s32Ret = HI_MUNMAP(s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg);
            if (HI_SUCCESS != s32Ret)
            {
                return s32Ret;
            }
            s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg = HI_NULL;
            s_asrVeChnInfo[i].u32StrmBufPhyAddrJpeg = HI_NULL;
            s_asrVeChnInfo[i].u32BufSizeJpeg        = 0;
       }
    }

    return s32Ret;
}

HI_S32 HI_MPI_VENC_GetAttr(HI_HANDLE hVencChn, HI_UNF_VENC_CHN_ATTR_S* pstAttr)
{
    HI_S32 s32Ret, i = 0;
    VENC_INFO_CREATE_S stVencChnCreate;

    if (!pstAttr)
    {
        HI_ERR_VENC("para pstAttr is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }
    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);
    stVencChnCreate.hVencChn = hVencChn;
    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_GET_CHN_ATTR, &stVencChnCreate);
    if (HI_SUCCESS == s32Ret)
    {
        *pstAttr = stVencChnCreate.stAttr.VencUnfAttr;
    }

    return s32Ret;
}

static HI_BOOL IsChipIDV500R001(HI_CHIP_TYPE_E enChipType, HI_CHIP_VERSION_E enChipVersion)
{
    if (((enChipType == HI_CHIP_TYPE_HI3798M) && (enChipVersion == HI_CHIP_VERSION_V300)) ||
        ((enChipType == HI_CHIP_TYPE_HI3796M) && (enChipVersion == HI_CHIP_VERSION_V200)))
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

static HI_S32 GetJPGEStreamAddrUser(HI_U32 ChanID, HI_HANDLE* phVencChn)
{
    HI_U32 u32PhyAddrBase = 0;
    HI_VOID *pUsrVirAddr = NULL;

    /*jpeg not support SMMU*/
    u32PhyAddrBase = s_asrVeChnInfo[ChanID].u32StrmBufPhyAddr - VEDU_MMZ_ALIGN;   // 'VEDU_MMZ_ALIGN' is the offset with the base PhyAddr
    pUsrVirAddr = (HI_VOID*)(HI_SIZE_T)HI_MPI_MMZ_Map(u32PhyAddrBase, 0 /*bCache*/ );
    s_asrVeChnVirAddr[ChanID].pStrmBufVirAddr = pUsrVirAddr + VEDU_MMZ_ALIGN;

    if (pUsrVirAddr == HI_NULL)
    {
        HI_ERR_VENC("memmap VENC's stream buffer failed.\n");
        (void)ioctl(g_VEncDevFd, CMD_VENC_DESTROY_CHN, phVencChn);

        return HI_ERR_VENC_CREATE_ERR;
    }

    u32PhyAddrBase = s_asrVeChnInfo[ChanID].u32StrmBufPhyAddrJpeg;
    pUsrVirAddr    = (HI_VOID*)(HI_SIZE_T)HI_MMZ_Map(u32PhyAddrBase, 0);
    s_asrVeChnVirAddr[ChanID].pStrmBufVirAddrJpeg = pUsrVirAddr;

    if (pUsrVirAddr == HI_NULL)
    {
        HI_ERR_VENC("memmap JPEG's stream buffer failed.\n");
        (void)ioctl(g_VEncDevFd, CMD_VENC_DESTROY_CHN, phVencChn);

        return HI_ERR_VENC_CREATE_ERR;
    }

    return HI_SUCCESS;
}

static HI_S32 GetVENCStreamAddrUser(HI_U32 ChanID, HI_HANDLE* phVencChn)
{
    HI_S32 s32Ret = 0;
    HI_U32 u32PhyAddrBase = 0;
    HI_VOID *pUsrVirAddr = NULL;
    HI_SYS_VERSION_S stVersion;

    memset(&stVersion, 0, sizeof(HI_SYS_VERSION_S));
    s32Ret = HI_SYS_GetVersion(&stVersion);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    u32PhyAddrBase = s_asrVeChnInfo[ChanID].u32StrmBufPhyAddr - VEDU_MMZ_ALIGN;   // 'VEDU_MMZ_ALIGN' is the offset with the base PhyAddr
    pUsrVirAddr = (HI_VOID*)(HI_SIZE_T)HI_MMZ_Map(u32PhyAddrBase, 0 /*bCache*/ );
    s_asrVeChnVirAddr[ChanID].pStrmBufVirAddr = pUsrVirAddr + VEDU_MMZ_ALIGN;

    if (pUsrVirAddr == HI_NULL)
    {
        HI_ERR_VENC("memmap VENC's stream buffer failed.Phyaddr = 0x%x\n", u32PhyAddrBase);
        (void)ioctl(g_VEncDevFd, CMD_VENC_DESTROY_CHN, phVencChn);

        return HI_ERR_VENC_CREATE_ERR;
    }

    if (IsChipIDV500R001(stVersion.enChipTypeHardWare, stVersion.enChipVersion))
    {
        HI_U32 u32SlicePhyAddrBase = 0;

        u32SlicePhyAddrBase = s_asrVeChnInfo[ChanID].u32SliceBufPhyAddr;
        pUsrVirAddr = (HI_VOID*)(HI_SIZE_T)HI_MPI_MMZ_Map(u32SlicePhyAddrBase, 0 /*bCache*/ );
        s_asrVeChnVirAddr[ChanID].pSliceBufVirAddr = pUsrVirAddr;

        if (pUsrVirAddr == HI_NULL)
        {
            HI_ERR_VENC("memmap VENC's Slice buffer failed. Phyaddr = 0x%x\n", u32SlicePhyAddrBase);

            (void)ioctl(g_VEncDevFd, CMD_VENC_DESTROY_CHN, phVencChn);

            return HI_ERR_VENC_CREATE_ERR;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VENC_Create(HI_HANDLE* phVencChn, const HI_UNF_VENC_CHN_ATTR_S* pstAttr)
{
    HI_S32 s32Ret = 0;
    HI_S32 i = 0;
    VENC_INFO_CREATE_S stVencChnCreate;

    if (!pstAttr)
    {
        HI_ERR_VENC("para pstAttr is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    if (!phVencChn)
    {
        HI_ERR_VENC("para phVencChn is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    CHECK_VENC_INIT();

    for (i = 0; i < VENC_MAX_CHN_NUM; i++)
    {
        if (s_asrVeChnInfo[i].handle == HI_INVALID_HANDLE)
        {
            break;
        }
    }

    if (i == VENC_MAX_CHN_NUM)
    {
        HI_ERR_VENC("mpi create err, \n");
        return HI_ERR_VENC_CREATE_ERR;
    }

    stVencChnCreate.bOMXChn = HI_FALSE;
    stVencChnCreate.stAttr.bAutoRequestIFrm = HI_FALSE;
    stVencChnCreate.stAttr.bPrependSpsPps   = HI_TRUE;
    stVencChnCreate.stAttr.bOmxChn = HI_FALSE;
    stVencChnCreate.stAttr.ControlRateType = 2;
    memcpy(&(stVencChnCreate.stAttr.VencUnfAttr), pstAttr, sizeof(HI_UNF_VENC_CHN_ATTR_S));

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_CREATE_CHN, &stVencChnCreate);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    memcpy(&(s_asrVeChnInfo[i]), &(stVencChnCreate.stVeInfo), sizeof(VENC_CHN_INFO_S));
    s_asrVeChnInfo[i].hSource = HI_INVALID_HANDLE;

    if (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_JPEG)
    {
        s32Ret = GetJPGEStreamAddrUser(i, &(stVencChnCreate.hVencChn));
    }
    else
    {
        s32Ret = GetVENCStreamAddrUser(i, &(stVencChnCreate.hVencChn));
    }

    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    *phVencChn = stVencChnCreate.hVencChn;
    s_asrVeChnInfo[i].handle = *phVencChn;

    HI_INFO_VENC("createOK, Chn%d, BufAddr: %#x / %p, Len:%#x.\n",
                 i, s_asrVeChnInfo[i].u32StrmBufPhyAddr,
                 s_asrVeChnVirAddr[i].pStrmBufVirAddr, s_asrVeChnInfo[i].u32BufSize);

    return HI_SUCCESS;
}

static HI_S32 DestroyJPGEStreamAddr(HI_U32 ChanID)
{
    HI_U32 u32PhyAddrBase = 0;
    HI_S32 s32Ret = 0;

    u32PhyAddrBase = s_asrVeChnInfo[ChanID].u32StrmBufPhyAddr  - VEDU_MMZ_ALIGN;
    s32Ret = HI_MPI_MMZ_Unmap(u32PhyAddrBase);

    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("venc unmap failed!(PhyAddr = 0x%x)\n", u32PhyAddrBase);

        return s32Ret;
    }

    s_asrVeChnVirAddr[ChanID].pStrmBufVirAddr = NULL;

    u32PhyAddrBase = s_asrVeChnInfo[ChanID].u32StrmBufPhyAddrJpeg;
    s32Ret = HI_MMZ_Unmap(u32PhyAddrBase);

    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("jpge unmap failed!(PhyAddr = 0x%x)\n", u32PhyAddrBase);

        return s32Ret;
    }

    s_asrVeChnVirAddr[ChanID].pStrmBufVirAddrJpeg = NULL;

    return HI_SUCCESS;
}

static HI_S32 DestroyVENCStreamAddr(HI_U32 ChanID)
{
    HI_S32 s32Ret = 0;
    HI_U32 u32PhyAddrBase = 0;
    HI_SYS_VERSION_S stVersion;

    memset(&stVersion, 0, sizeof(HI_SYS_VERSION_S));
    s32Ret = HI_SYS_GetVersion(&stVersion);

    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    u32PhyAddrBase = s_asrVeChnInfo[ChanID].u32StrmBufPhyAddr - VEDU_MMZ_ALIGN;
    s32Ret = HI_MMZ_Unmap(u32PhyAddrBase);

    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("venc unmap failed!(PhyAddr = 0x%x)\n", u32PhyAddrBase);

        return s32Ret;
    }


    if (IsChipIDV500R001(stVersion.enChipTypeHardWare, stVersion.enChipVersion))
    {
        u32PhyAddrBase = s_asrVeChnInfo[ChanID].u32SliceBufPhyAddr;
        s32Ret = HI_MPI_MMZ_Unmap(u32PhyAddrBase);

        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_VENC("venc unmap failed!(PhyAddr = 0x%x)\n", u32PhyAddrBase);

            return s32Ret;
        }

        s_asrVeChnVirAddr[ChanID].pSliceBufVirAddr = NULL;
    }

    s_asrVeChnVirAddr[ChanID].pStrmBufVirAddr = NULL;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VENC_Destroy(HI_HANDLE hVencChn)
{
    HI_S32 s32Ret = 0, i = 0;
    HI_MOD_ID_E enModID = HI_ID_BUTT;

    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    enModID = (HI_MOD_ID_E)((s_asrVeChnInfo[i].hSource & 0xff0000) >> 16);
    switch (enModID)
    {
#ifdef HI_VI_SUPPORT
        case HI_ID_VI:
            s32Ret =  HI_MPI_VI_Detach(s_asrVeChnInfo[i].hSource, hVencChn);
            break;
#endif
        case HI_ID_VO:
            s32Ret =  HI_MPI_WIN_DetachWinSink(s_asrVeChnInfo[i].hSource, hVencChn);
            break;
        case HI_ID_DISP:
            s32Ret =  HI_MPI_DISP_ExtDeAttach(s_asrVeChnInfo[i].hSource, hVencChn);
            break;
        default:
            break;
    }
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("VENC still attach Module(%d),please detach first!\n", enModID);
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    if (s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg != NULL)
    {
        s32Ret = DestroyJPGEStreamAddr(i);
    }
    else
    {
        s32Ret = DestroyVENCStreamAddr(i);
    }
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_DESTROY_CHN, &hVencChn);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }


    s_asrVeChnInfo[i].handle = HI_INVALID_HANDLE;
    s_asrVeChnInfo[i].hSource = HI_INVALID_HANDLE;

    return s32Ret;
}

HI_S32 HI_MPI_VENC_AttachInput(HI_HANDLE hVencChn, HI_HANDLE hSrc)
{
    HI_S32 s32Ret = 0, i = 0;
    VENC_INFO_ATTACH_S stVencAttachInfo;
    HI_MOD_ID_E enModID = HI_ID_BUTT;

    if (HI_INVALID_HANDLE == hSrc)
    {
        HI_ERR_VENC("para hSrc is invalid.\n");
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    enModID = (HI_MOD_ID_E)((hSrc & 0xff0000) >> 16);

    stVencAttachInfo.hSrc = hSrc;
    stVencAttachInfo.hVencChn = hVencChn;
    stVencAttachInfo.enModId = enModID;

    s32Ret  = ioctl(g_VEncDevFd, CMD_VENC_ATTACH_INPUT, &stVencAttachInfo);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    switch (enModID)
    {
        case HI_ID_VI:
#ifdef HI_VI_SUPPORT
        s32Ret = HI_MPI_VI_Attach(hSrc , hVencChn);
#else
        HI_ERR_VENC("venc not support attach VI in this version!\n", enModID);
        s32Ret = HI_ERR_VENC_NOT_SUPPORT;
#endif
        break;

        case HI_ID_VO:
        {
            s32Ret = HI_MPI_WIN_AttachWinSink(hSrc, hVencChn);
        }
        break;

        case HI_ID_DISP:
        {
            s32Ret = HI_MPI_DISP_ExtAttach(hSrc, hVencChn);
        }
        break;

      default:
        HI_ERR_VENC("ModId not surpport now, enModId=%x!\n", enModID);
        s32Ret = HI_ERR_VENC_INVALID_PARA;
        break;
    }

    if (HI_SUCCESS == s32Ret)
    {
        s_asrVeChnInfo[i].hSource = hSrc;
        s32Ret = HI_MPI_VENC_Start(hVencChn);
    }
    else
    {
        if (HI_ID_VO == enModID)
        {
            s32Ret = HI_MPI_WIN_DetachWinSink(hSrc, hVencChn);
        }
        else if (HI_ID_DISP == enModID)
        {
            s32Ret = HI_MPI_DISP_ExtDeAttach(hSrc, hVencChn);
        }
        else if (HI_ID_VI == enModID)
        {
#ifdef HI_VI_SUPPORT
            s32Ret = HI_MPI_VI_Detach(hSrc, hVencChn);
#endif
        }

        if (s32Ret != HI_SUCCESS)
        {
            HI_WARN_VENC("Mode(%d) detach func return failed!", enModID);
        }
        if (HI_SUCCESS != ioctl(g_VEncDevFd, CMD_VENC_DETACH_INPUT, &stVencAttachInfo))
        {
            HI_INFO_VENC("detach input error\n");
        }
    }
    return s32Ret;
}

HI_S32 HI_MPI_VENC_SetSource(HI_HANDLE hVencChn, HI_DRV_VENC_SRC_HANDLE_S* pstSrc)
{
    HI_S32 s32Ret = 0, i = 0;
    VENC_SET_SRC_S stSetSrcInfo;

    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hSrc is invalid.\n");
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (!pstSrc)
    {
        HI_ERR_VENC("para pstStream is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    stSetSrcInfo.hVencChn      = hVencChn;
    memcpy(&stSetSrcInfo.stVencSrc, pstSrc, sizeof(HI_DRV_VENC_SRC_HANDLE_S));
    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_SET_SRC, &stSetSrcInfo);
    if (HI_SUCCESS != s32Ret)
    {
        s_asrVeChnInfo[i].hSource = HI_INVALID_HANDLE;
    }
    return s32Ret;
}


HI_S32 HI_MPI_VENC_DetachInput(HI_HANDLE hVencChn/*, HI_HANDLE hSrc*/)
{
    HI_S32 s32Ret = 0, i = 0;
    VENC_INFO_ATTACH_S stVencAttachInfo;
    HI_MOD_ID_E enModID = HI_ID_BUTT;

    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    stVencAttachInfo.hVencChn = hVencChn;

    enModID = (HI_MOD_ID_E)((s_asrVeChnInfo[i].hSource & 0xff0000) >> 16);

    switch (enModID)
    {
#ifdef HI_VI_SUPPORT
        case HI_ID_VI:
            s32Ret =  HI_MPI_VI_Detach(s_asrVeChnInfo[i].hSource, hVencChn);
            break;
#endif
        case HI_ID_VO:
            s32Ret =  HI_MPI_WIN_DetachWinSink(s_asrVeChnInfo[i].hSource, hVencChn);
            break;
        case HI_ID_DISP:
            s32Ret =  HI_MPI_DISP_ExtDeAttach(s_asrVeChnInfo[i].hSource, hVencChn);
            break;
        case HI_ID_BUTT:
            return HI_ERR_VENC_CHN_NO_ATTACH;
        default:
            HI_ERR_VENC("Venc Detach, ModId not surpport now, enModId=%x!\n", enModID);
            return HI_ERR_VENC_INVALID_PARA;
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("venc can't detach with ModID(%x) now.\n", enModID);
        return HI_FAILURE;
    }

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_DETACH_INPUT, &stVencAttachInfo);

    if (HI_SUCCESS == s32Ret)
    {
        s_asrVeChnInfo[i].hSource = HI_INVALID_HANDLE;
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}

static HI_S32 GetStreamAddr(HI_U32 HandleID, VENC_BUF_OFFSET_S *pstBufOffSet, HI_UNF_VENC_STREAM_S* pstStream)
{
    HI_S32 s32Ret = 0;
    HI_SYS_VERSION_S stVersion;

    memset(&stVersion, 0, sizeof(HI_SYS_VERSION_S));
    s32Ret = HI_SYS_GetVersion(&stVersion);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    if (s_asrVeChnVirAddr[HandleID].pStrmBufVirAddrJpeg != NULL)
    {
        pstStream->pu8Addr = (HI_U8*)s_asrVeChnVirAddr[HandleID].pStrmBufVirAddrJpeg;
    }
    else
    {
        if (IsChipIDV500R001(stVersion.enChipTypeHardWare, stVersion.enChipVersion))
        {
            if (s_asrVeChnInfo[HandleID].u32Protocol == VEDU_H264)
            {
                if (pstStream->enDataType.enH264EType == HI_UNF_H264E_NALU_PPS)
                {
                    pstStream->pu8Addr = (HI_U8*)(s_asrVeChnVirAddr[HandleID].pSliceBufVirAddr) + pstBufOffSet->u32StrmBufOffset[0];
                }
                else
                {
                    pstStream->pu8Addr = (HI_U8*)(s_asrVeChnVirAddr[HandleID].pStrmBufVirAddr) + pstBufOffSet->u32StrmBufOffset[0];
                }
            }
            else
            {
                if (pstStream->enDataType.enHEVCEType == HI_UNF_HEVCE_NALU_PPS)
                {
                    pstStream->pu8Addr = (HI_U8*)(s_asrVeChnVirAddr[HandleID].pSliceBufVirAddr) + pstBufOffSet->u32StrmBufOffset[0];
                }
                else
                {
                    pstStream->pu8Addr = (HI_U8*)(s_asrVeChnVirAddr[HandleID].pStrmBufVirAddr) + pstBufOffSet->u32StrmBufOffset[0];
                }
            }
        }
        else
        {
            pstStream->pu8Addr = (HI_U8*)(s_asrVeChnVirAddr[HandleID].pStrmBufVirAddr) + pstBufOffSet->u32StrmBufOffset[0];
        }
    }

    return HI_SUCCESS;
}

static HI_S32 GetStreamAddrOffset(HI_U32 HandleID, HI_U32 *pStreamAddrOff, const HI_UNF_VENC_STREAM_S* pstStream)
{
    HI_S32 s32Ret = 0;
    HI_SYS_VERSION_S stVersion;

    memset(&stVersion, 0, sizeof(HI_SYS_VERSION_S));
    s32Ret = HI_SYS_GetVersion(&stVersion);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    if (IsChipIDV500R001(stVersion.enChipTypeHardWare, stVersion.enChipVersion))
    {
        if (s_asrVeChnInfo[HandleID].u32Protocol == VEDU_H264)
        {
            if (pstStream->enDataType.enH264EType == HI_UNF_H264E_NALU_PPS)
            {
                *pStreamAddrOff = (pstStream->pu8Addr - (HI_U8*)(s_asrVeChnVirAddr[HandleID].pSliceBufVirAddr));
            }
            else
            {
                *pStreamAddrOff = (pstStream->pu8Addr - (HI_U8*)(s_asrVeChnVirAddr[HandleID].pStrmBufVirAddr));
            }
        }
        else
        {
            if (pstStream->enDataType.enHEVCEType == HI_UNF_HEVCE_NALU_PPS)
            {
                *pStreamAddrOff = (pstStream->pu8Addr - (HI_U8*)(s_asrVeChnVirAddr[HandleID].pSliceBufVirAddr));
            }
            else
            {
                *pStreamAddrOff = (pstStream->pu8Addr - (HI_U8*)(s_asrVeChnVirAddr[HandleID].pStrmBufVirAddr));
            }
        }
    }
    else
    {
        *pStreamAddrOff = (pstStream->pu8Addr - (HI_U8*)(s_asrVeChnVirAddr[HandleID].pStrmBufVirAddr));
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VENC_AcquireStream(HI_HANDLE hVencChn, HI_UNF_VENC_STREAM_S* pstStream, HI_U32 u32TimeoutMs)
{
    HI_S32 s32Ret = 0;
    HI_U32 i = 0;
    VENC_INFO_ACQUIRE_STREAM_S stVencAcquireStream;
    VENC_BUF_OFFSET_S stBufOffSet;

    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (HI_NULL == pstStream)
    {
        HI_ERR_VENC("para pstStream is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    stVencAcquireStream.hVencChn = hVencChn;
    stVencAcquireStream.u32BlockFlag = u32TimeoutMs;
    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_ACQUIRE_STREAM, &stVencAcquireStream);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    memcpy(&stBufOffSet, &(stVencAcquireStream.stBufOffSet), sizeof(stBufOffSet));
    pstStream->u32SlcLen = stVencAcquireStream.stStream.u32SlcLen;
    pstStream->u32PtsMs = stVencAcquireStream.stStream.u32PtsMs;
    pstStream->bFrameEnd = stVencAcquireStream.stStream.bFrameEnd;
    pstStream->enDataType = stVencAcquireStream.stStream.enDataType;

    if (pstStream->u32SlcLen > 0)
    {
        s32Ret = GetStreamAddr(i, &stBufOffSet, pstStream);

        if (s32Ret != HI_SUCCESS)
        {
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VENC_ReleaseStream(HI_HANDLE hVencChn, const HI_UNF_VENC_STREAM_S* pstStream)
{
    HI_S32 s32Ret = 0;
    HI_U32 i = 0;
    VENC_INFO_ACQUIRE_STREAM_S stVencAcquireStream;

    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (HI_NULL == pstStream)
    {
        HI_ERR_VENC("para pstStream is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }
    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    stVencAcquireStream.hVencChn = hVencChn;
    stVencAcquireStream.stStream.u32SlcLen = pstStream->u32SlcLen;
    stVencAcquireStream.stStream.u32PtsMs = pstStream->u32PtsMs;
    stVencAcquireStream.stStream.bFrameEnd = pstStream->bFrameEnd;
    stVencAcquireStream.stStream.enDataType = pstStream->enDataType;

    if (s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg != HI_NULL)
    {
        if (pstStream->pu8Addr != (HI_U8*)s_asrVeChnVirAddr[i].pStrmBufVirAddrJpeg)
        {
            HI_ERR_VENC("Release stream failed.\n");
            return HI_ERR_VENC_CHN_RELEASE_ERR;
        }
        stVencAcquireStream.Jpeg_Phy_Addr = s_asrVeChnInfo[i].u32StrmBufPhyAddrJpeg;
    }
    else
    {
        s32Ret = GetStreamAddrOffset(i, &stVencAcquireStream.H264_stream_off, pstStream);

        if (s32Ret != HI_SUCCESS)
        {
            return s32Ret;
        }
    }

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_RELEASE_STREAM, &stVencAcquireStream);

    return s32Ret;
}

HI_S32 HI_MPI_VENC_Start(HI_HANDLE hVencChn)
{
    HI_S32 s32Ret = 0, i = 0;

    if ((hVencChn & 0xffff0000) != (HI_ID_VENC << 16))
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_INVALID_PARA;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_START_RECV_PIC, &hVencChn);

    return s32Ret;
}

HI_S32 HI_MPI_VENC_Stop(HI_HANDLE hVencChn)
{
    HI_S32 s32Ret = 0, i = 0;
    if ((hVencChn & 0xffff0000) != (HI_ID_VENC << 16))
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_INVALID_PARA;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);
    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_STOP_RECV_PIC, &hVencChn);

    return s32Ret;
}

HI_S32 HI_MPI_VENC_RequestIFrame(HI_HANDLE hVencChn)
{
    HI_S32 s32Ret = 0, i = 0;

    if ((hVencChn & 0xffff0000) != (HI_ID_VENC << 16))
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_INVALID_PARA;
    }

    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_REQUEST_I_FRAME, &hVencChn);

    return s32Ret;
}

HI_S32 HI_MPI_VENC_QueueFrame(HI_HANDLE hVencChn, HI_UNF_VIDEO_FRAME_INFO_S* pstFrameinfo)
{
    HI_S32 s32Ret = 0, i = 0;
    VENC_INFO_QUEUE_FRAME_S stVencQueueFrame;
    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);

    if (HI_NULL == pstFrameinfo)
    {
        HI_ERR_VENC("para pstStream is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    stVencQueueFrame.hVencChn = hVencChn;
    memcpy(&(stVencQueueFrame.stVencFrame), pstFrameinfo, sizeof(HI_UNF_VIDEO_FRAME_INFO_S));
    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_QUEUE_FRAME, &stVencQueueFrame);

    return s32Ret;
}

HI_S32 HI_MPI_VENC_DequeueFrame(HI_HANDLE hVencChn, HI_UNF_VIDEO_FRAME_INFO_S* pstFrameinfo)
{
    HI_S32 s32Ret = 0, i = 0;
    VENC_INFO_QUEUE_FRAME_S stVencQueueFrame;
    if (HI_INVALID_HANDLE == hVencChn)
    {
        HI_ERR_VENC("para hVencChn is invalid.\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    CHECK_VENC_INIT();
    CHECK_CHANNEL_EXIST(i, VENC_MAX_CHN_NUM, hVencChn);
    if (HI_NULL == pstFrameinfo)
    {
        HI_ERR_VENC("para pstStream is NULL.\n");
        return HI_ERR_VENC_NULL_PTR;
    }
    stVencQueueFrame.hVencChn = hVencChn;

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_DEQUEUE_FRAME, &stVencQueueFrame);

    if (!s32Ret)
    {
        memcpy(pstFrameinfo, &(stVencQueueFrame.stVencFrame), sizeof(HI_UNF_VIDEO_FRAME_INFO_S));
    }

    return s32Ret;
}

HI_S32 HI_MPI_VENC_GetCapability(HI_UNF_VENC_CAP_S *pstCapability)
{
    HI_S32 s32Ret = 0;

    if (HI_NULL == pstCapability)
    {
        HI_ERR_VENC("para pstCapability is NULL.\n");

        return HI_ERR_VENC_NULL_PTR;
    }

    CHECK_VENC_INIT();

    s32Ret = ioctl(g_VEncDevFd, CMD_VENC_GET_CAP, pstCapability);

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

