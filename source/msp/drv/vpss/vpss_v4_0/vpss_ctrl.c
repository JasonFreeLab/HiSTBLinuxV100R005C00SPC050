#include "hi_kernel_adapt.h"
#include "vpss_ctrl.h"
#include "vpss_common.h"
#include "hi_drv_proc.h"

#ifdef VPSS_HAL_WITH_CBB
#include "vpss_cbb_common.h"
#include "vpss_cbb_component.h"
#include "vpss_cbb_intf.h"
#include "vpss_cbb_hal.h"
#include "vpss_cbb_alg.h"
#include "vpss_cbb_reg.h"
#include "vpss_cbb_common.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static VPSS_CTRL_S g_stVpssCtrl[VPSS_IP_BUTT] =
{
    {
        .bIPVaild = HI_FALSE,
        .enIP     = VPSS_IP_0,
        .u32VpssIrqNum = VPSS0_IRQ_NUM,
        .pVpssIntService = VPSS0_CTRL_IntService,
        .isr_name = "vpss0",
        .s32IsVPSSOpen = 0,
    },

    {
        .bIPVaild = HI_TRUE,
        .enIP     = VPSS_IP_1,
        .u32VpssIrqNum = VPSS1_IRQ_NUM,
        .pVpssIntService = VPSS1_CTRL_IntService,
        .isr_name = "vpss1",
        .s32IsVPSSOpen = 0,
    }
};

HI_VOID VPSS_CTRL_InitInstList(VPSS_IP_E enIp)
{
    HI_U32 u32Count;
    VPSS_INST_CTRL_S *pstInsList;

    pstInsList = &(g_stVpssCtrl[enIp].stInstCtrlInfo);
    rwlock_init(&(pstInsList->stListLock));
    pstInsList->u32Target = 0;
    pstInsList->u32InstanceNum = 0;

    for (u32Count = 0; u32Count < VPSS_INSTANCE_MAX_NUMB; u32Count ++)
    {
        pstInsList->pstInstPool[u32Count] = HI_NULL;
    }

}

HI_S32 VPSS_CTRL_RegistISR(VPSS_IP_E enIp)
{
    if (osal_request_irq(g_stVpssCtrl[enIp].u32VpssIrqNum, g_stVpssCtrl[enIp].pVpssIntService,
                         IRQF_SHARED, g_stVpssCtrl[enIp].isr_name, &(g_stVpssCtrl[enIp].hVpssIRQ)))
    {
        VPSS_FATAL("VPSS%d registe IRQ failed!\n", (HI_U32)enIp);
        return HI_FAILURE;
    }
    else
    {
        if (HI_SUCCESS != HI_DRV_SYS_SetIrqAffinity(HI_ID_VPSS, g_stVpssCtrl[enIp].u32VpssIrqNum, g_stVpssCtrl[enIp].isr_name))
        {
            VPSS_ERROR("Set Vpss Irq Affinity Failed.\n");
        }

        return HI_SUCCESS;
    }
}

HI_S32 VPSS_CTRL_UnRegistISR(VPSS_IP_E enIp)
{
    osal_free_irq(g_stVpssCtrl[enIp].u32VpssIrqNum, g_stVpssCtrl[enIp].isr_name, &(g_stVpssCtrl[enIp].hVpssIRQ));
    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_GetDistributeIP(VPSS_IP_E *penVpssIp)
{
    HI_U32 u32MinInstCount = VPSS_INSTANCE_MAX_NUMB;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i;

    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        if ((HI_TRUE == g_stVpssCtrl[i].bIPVaild) && (u32MinInstCount > g_stVpssCtrl[i].stInstCtrlInfo.u32InstanceNum))
        {
            u32MinInstCount = g_stVpssCtrl[i].stInstCtrlInfo.u32InstanceNum;
            *penVpssIp = i;
            s32Ret = HI_SUCCESS;
        }
    }

    return s32Ret;
}


HI_S32 VPSS_CTRL_SyncDistributeIP(VPSS_INSTANCE_S *pstInstance, HI_DRV_VPSS_IPMODE_E enIpmode)
{
    HI_U32 i;
    VPSS_IP_E enDstVpssIp;
    VPSS_IP_E enSrcVpssIp;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    unsigned long u32LockFlag;
    VPSS_INSTANCE_S *pstChgInst = HI_NULL;

    //step1:get instance real ip
    //step2:change instance to new ip
    //step2.1:if the new ip has instance ,change it together
    if (HI_DRV_VPSS_IPMODE_BUTT <= enIpmode)
    {
        VPSS_FATAL("Invalid Ipmode %d.", enIpmode);
        return HI_FAILURE;
    }

    if ((HI_FALSE == g_stVpssCtrl[VPSS_IP_0].bIPVaild)
        || (HI_FALSE == g_stVpssCtrl[VPSS_IP_1].bIPVaild))
    {
        VPSS_ERROR("Can not change IP %d,single ctrl", enIpmode);
        return HI_FAILURE;
    }

    if (HI_DRV_VPSS_IPMODE_IP0 == enIpmode)
    {
        enDstVpssIp = VPSS_IP_0;
    }
    else
    {
        enDstVpssIp = VPSS_IP_1;
    }

    pstInstCtrlInfo = &(g_stVpssCtrl[enDstVpssIp].stInstCtrlInfo);
    if (enDstVpssIp == pstInstance->CtrlID)
    {
        return HI_SUCCESS;
    }

    enSrcVpssIp = pstInstance->CtrlID;

    //we need exchange instance to keep balance
    if (0 < pstInstCtrlInfo->u32InstanceNum)
    {
        pstInstCtrlInfo = &(g_stVpssCtrl[enDstVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (HI_NULL != pstInstCtrlInfo->pstInstPool[i])
            {
                pstChgInst = pstInstCtrlInfo->pstInstPool[i];
                pstInstCtrlInfo->pstInstPool[i] = pstInstance;
                pstInstance->CtrlID = enDstVpssIp;
                break;
            }
        }

        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        if (HI_NULL == pstChgInst)
        {
            VPSS_ERROR("Can't get DstInst\n");
            return HI_FAILURE;
        }

        pstInstCtrlInfo = &(g_stVpssCtrl[enSrcVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (pstInstance == pstInstCtrlInfo->pstInstPool[i])
            {
                pstInstCtrlInfo->pstInstPool[i] = pstChgInst;
                pstChgInst->CtrlID = enSrcVpssIp;
                break;
            }
        }
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    }
    else
    {
        pstInstCtrlInfo = &(g_stVpssCtrl[enSrcVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (pstInstance == pstInstCtrlInfo->pstInstPool[i])
            {
                pstInstCtrlInfo->pstInstPool[i] = HI_NULL;
                pstInstCtrlInfo->u32InstanceNum--;
                break;
            }
        }

        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        pstInstCtrlInfo = &(g_stVpssCtrl[enDstVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (HI_NULL == pstInstCtrlInfo->pstInstPool[i])
            {
                pstInstCtrlInfo->pstInstPool[i] = pstInstance;
                pstInstance->CtrlID = enDstVpssIp;
                pstInstCtrlInfo->u32InstanceNum++;
                break;
            }
        }

        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    }

    return HI_SUCCESS;
}

VPSS_INSTANCE_S *VPSS_CTRL_GetServiceInstance(VPSS_IP_E enIp)
{
    HI_S32 s32LockRet;
    HI_S32 s32CheckRet;
    HI_U32 u32CycleTime;
    HI_U32 u32CurPos;
    unsigned long  u32LockFlag;
    VPSS_INST_CTRL_S  *pstInstCtrlInfo;
    VPSS_INSTANCE_S *pstInstance;

    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);
    u32CycleTime = 0;
    u32CurPos = pstInstCtrlInfo->u32Target;

    while (u32CycleTime < VPSS_INSTANCE_MAX_NUMB)
    {
        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        pstInstance = pstInstCtrlInfo->pstInstPool[u32CurPos];
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        if (pstInstance == HI_NULL)
        {
            u32CurPos = (u32CurPos + 1) % VPSS_INSTANCE_MAX_NUMB;
            u32CycleTime++;
            continue;
        }

        s32LockRet = HI_SUCCESS;//VPSS_OSAL_TryLock(&(pstInstance->stInstLock));
        //s32LockRet = VPSS_OSAL_TryLock(&(pstInstance->stInstLock));
        if (s32LockRet == HI_SUCCESS)
        {
            pstInstance->u32CheckCnt++;
            if (jiffies - pstInstance->ulLastCheckTime > HZ)
            {
                pstInstance->u32CheckRate = pstInstance->u32CheckCnt;
                pstInstance->u32CheckSucRate = pstInstance->u32CheckSucCnt;
#ifdef VPSS_SUPPORT_PROC_V2
                pstInstance->u32BufRate =  pstInstance->u32BufCnt - pstInstance->u32LastBufCnt;
                pstInstance->u32BufSucRate = pstInstance->u32BufSucCnt - pstInstance->u32BufLastSucCnt;
#else
                pstInstance->u32BufRate = pstInstance->u32BufCnt;
                pstInstance->u32BufSucRate = pstInstance->u32BufSucCnt;
#endif
                pstInstance->u32CheckCnt = 0;
                pstInstance->u32CheckSucCnt = 0;
#ifdef VPSS_SUPPORT_PROC_V2
                pstInstance->u32LastBufCnt = pstInstance->u32BufCnt;
                pstInstance->u32BufLastSucCnt = pstInstance->u32BufSucCnt;
#else
                pstInstance->u32BufCnt = 0;
                pstInstance->u32BufSucCnt = 0;
#endif
                pstInstance->u32ImgRate
                    = pstInstance->u32ImgCnt - pstInstance->u32ImgLastCnt;
                pstInstance->u32ImgSucRate
                    = pstInstance->u32ImgSucCnt - pstInstance->u32ImgLastSucCnt;
                pstInstance->u32ImgLastCnt = pstInstance->u32ImgCnt;
                pstInstance->u32ImgLastSucCnt = pstInstance->u32ImgSucCnt;
                pstInstance->ulLastCheckTime = jiffies;
            }

            if (pstInstance->enState == INSTANCE_STATE_WORING)
            {
                (HI_VOID)VPSS_INST_SyncUsrCfg(pstInstance);

                VPSS_INST_SyncTvpCfg(pstInstance);

                s32CheckRet = VPSS_INST_CheckInstAvailable(pstInstance);
                if (s32CheckRet == HI_SUCCESS)
                {
                    (HI_VOID)VPSS_INST_RevisePortOutBitWidth(pstInstance);
#ifdef VPSS_ZME_WIDTH_MAX_FHD
                    (HI_VOID)VPSS_INST_RevisePortOutImageWidth(pstInstance);
                    VPSS_INST_RevisePortOutRect(pstInstance);
#endif
                    pstInstCtrlInfo->u32Target = (u32CurPos + 1) % VPSS_INSTANCE_MAX_NUMB;
                    pstInstance->u32CheckSucCnt++;
#ifdef VPSS_SUPPORT_PROC_V2
                    pstInstance->aulCreatTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
                    //VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
                    return pstInstance;
                }
                else
                {
                    //VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
                }
            }
        }

        u32CurPos = (u32CurPos + 1) % VPSS_INSTANCE_MAX_NUMB;
        u32CycleTime++;
    }

    return HI_NULL;
}

HI_S32 VPSS_CTRL_FixTask(VPSS_IP_E enIp, HI_DRV_BUF_ADDR_E enLR, VPSS_TASK_S *pstTask)
{
    HI_S32 i;
#ifndef VPSS_ZME_SUPPORT_10BIT
    HI_S32 j;
#endif
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;
    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_FB_NODE_S *pstFrmNode = HI_NULL;
    VPSS_IN_INTF_S stInIntf;

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

    pstHalInfo->pstPqCfg = &pstInst->stPqRegData;
#ifdef VPSS_HAL_WITH_CBB
    pstHalInfo->enSceneMode = pstInst->stUsrInstCfg.enSceneMode;
    pstHalInfo->s32InstanceID = pstInst->ID;
#endif
    s32Ret = VPSS_IN_GetIntf(&(pstInst->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    if (HI_DRV_BUF_ADDR_MAX <= enLR)
    {
        VPSS_ERROR("Invalid Para enLR %d\n", enLR);
        return HI_FAILURE;
    }

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

    /* INInfo */
    s32Ret = stInIntf.pfnGetProcessImage(&pstInst->stInEntity, &pstCur);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
        return HI_FAILURE;
    }
#if !defined(HI_NVR_SUPPORT)

#ifdef VPSS_HAL_WITH_CBB
    if ((pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_SD_FIRST)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_SD_SECOND)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP2_DEI))
#else
    if ((pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_5Field)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DETILE_STEP1)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP2_DEI))
#endif
    {
        HI_DRV_VIDEO_PRIVATE_S *pstPriv;
        HI_PQ_WBC_INFO_S stVpssWbcInfo;
        HI_PQ_CFG_INFO_S stVpssCfgInfo;

        stVpssWbcInfo.u32HandleNo = pstInst->ID;
        stVpssWbcInfo.u32Width = pstCur->u32Width;
        stVpssWbcInfo.u32Height = pstCur->u32Height;
        stVpssWbcInfo.bProgressive = pstCur->bProgressive;
        stVpssWbcInfo.pstVPSSWbcReg = &(pstInst->stPqWbcReg);

        stVpssWbcInfo.s32FieldOrder = !pstCur->bTopFieldFirst;

        stVpssWbcInfo.stOriCoordinate.s32X = 0;
        stVpssWbcInfo.stOriCoordinate.s32Y = 0;
        stVpssWbcInfo.stOriCoordinate.s32Width = 0;
        stVpssWbcInfo.stOriCoordinate.s32Height = 0;
        stVpssWbcInfo.stCropCoordinate = stVpssWbcInfo.stOriCoordinate;

        if (pstCur->enFieldMode == HI_DRV_FIELD_TOP)
        {
            stVpssWbcInfo.s32FieldMode = 0;
        }
        else if (pstCur->enFieldMode == HI_DRV_FIELD_BOTTOM)
        {
            stVpssWbcInfo.s32FieldMode = 1;
        }
        else
        {
            VPSS_ERROR("Dei Error.\n");
            stVpssWbcInfo.s32FieldMode = 0;
        }
        pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstCur->u32Priv;

        stVpssWbcInfo.u32FrameRate = pstCur->u32FrameRate;
        stVpssWbcInfo.bPreInfo = HI_FALSE;

        stVpssWbcInfo.stVdecInfo.IsProgressiveFrm = pstPriv->ePictureMode;
        stVpssWbcInfo.stVdecInfo.IsProgressiveSeq = pstPriv->eSampleType;
        stVpssWbcInfo.stVdecInfo.RealFrmRate = 2500;
        {
            HI_DRV_VIDEO_PRIVATE_S *pstPriv;
            HI_DRV_DNR_INFO_S *pstDnrInfo;

            pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstCur->u32Priv;
            pstDnrInfo = &pstPriv->stDNRInfo;
            stVpssWbcInfo.bCropBeforeDB = HI_FALSE;
            stVpssWbcInfo.u32SingleModeFlag = 1;
            stVpssWbcInfo.u32Protocol = 1;
            stVpssWbcInfo.u32ImageAvgQP = pstDnrInfo->u32ImageAvgQP;
            stVpssWbcInfo.u32VdhInfoAddr = pstDnrInfo->u32VdhInfoAddr;
            stVpssWbcInfo.u32VdhInfoStride = pstDnrInfo->u32VdhInfoStride;
            stVpssWbcInfo.u32ImageStruct = 0; //pstDnrInfo->u32Size;
        }
        DRV_PQ_SetAlgCalcCfg(&stVpssWbcInfo, &stVpssCfgInfo);

        /* open set filed order of alg detection sdk */
        if (stVpssCfgInfo.s32FieldOrder != 2)
        {
            if (pstInst->stInEntity.stStreamInfo.u32RealTopFirst == HI_FALSE)
            {
                if (pstCur->enFieldMode == HI_DRV_FIELD_TOP
                    && pstCur->enBufValidMode != HI_DRV_FIELD_ALL)
                {
                    HI_BOOL bTopFirst;
                    bTopFirst = !stVpssCfgInfo.s32FieldOrder;
                    stInIntf.pfnGetInfo(&pstInst->stInEntity,
                                        VPSS_IN_INFO_CORRECT_FIELD,
                                        HI_DRV_BUF_ADDR_MAX,
                                        &bTopFirst);
                }
            }
            else if (pstInst->stInEntity.stStreamInfo.u32RealTopFirst == HI_TRUE)
            {
                if (pstCur->enFieldMode == HI_DRV_FIELD_BOTTOM
                    && pstCur->enBufValidMode != HI_DRV_FIELD_ALL)

                {
                    HI_BOOL bTopFirst;
                    bTopFirst = !stVpssCfgInfo.s32FieldOrder;
                    stInIntf.pfnGetInfo(&pstInst->stInEntity,
                                        VPSS_IN_INFO_CORRECT_FIELD,
                                        HI_DRV_BUF_ADDR_MAX,
                                        &bTopFirst);
                }
            }
            else
            {

            }
        }
    }
    else
    {
        HI_PQ_WBC_INFO_S stVpssWbcInfo;
        HI_PQ_CFG_INFO_S stVpssCfgInfo;

        memset(&stVpssWbcInfo, 0, sizeof(HI_PQ_WBC_INFO_S));
        memset(&stVpssCfgInfo, 0, sizeof(HI_PQ_CFG_INFO_S));

        stVpssWbcInfo.u32HandleNo = pstInst->ID;
        stVpssWbcInfo.u32Width = pstCur->u32Width;
        stVpssWbcInfo.u32Height = pstCur->u32Height;
        stVpssWbcInfo.bProgressive = pstCur->bProgressive;
        stVpssWbcInfo.pstVPSSWbcReg = &(pstInst->stPqWbcReg);

        DRV_PQ_SetAlgCalcCfg(&stVpssWbcInfo, &stVpssCfgInfo);
    }

#endif


#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
    if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_R
        || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L)
    {
        VPSS_INST_SetHalFrameInfo(pstCur,
                                  &pstHalInfo->stInInfo,
                                  HI_DRV_BUF_ADDR_LEFT);
    }
    else
#endif
    {
        VPSS_INST_SetHalFrameInfo(pstCur,
                                  &pstHalInfo->stInInfo,
                                  enLR);

        pstHalInfo->stInInfo.u32TunnelAddr = pstCur->u32TunnelPhyAddr;
    }

#if !defined(HI_NVR_SUPPORT)
    {
        HI_S32          s32SrcId;
        s32SrcId = (pstInst->hDst & 0x00ff0000) >> 16;
        //vi donot need rwzb, vi cannot give viraddr which rwzb needs.
        if ((s32SrcId != HI_ID_VI) && (pstHalInfo->stInInfo.u32Width <= VPSS_FHD_WIDTH)
            && (!pstHalInfo->stInInfo.bSecure))
        {
            VPSS_RWZB_IMG_S stRwzbImage;

            /*RWZB*/
            if (pstHalInfo->stInInfo.enFieldMode == HI_DRV_FIELD_BOTTOM
                || pstHalInfo->stInInfo.bProgressive == HI_TRUE)
            {
                VPSS_RWZB_GetRwzbData(&(pstInst->stRwzbInfo), &pstHalInfo->stRwzbInfo);
            }

            stRwzbImage.bProgressive = pstHalInfo->stInInfo.bProgressive;
            stRwzbImage.enFieldMode = pstHalInfo->stInInfo.enFieldMode;
            stRwzbImage.u32Height = pstHalInfo->stInInfo.u32Height;
            stRwzbImage.u32Width = pstHalInfo->stInInfo.u32Width;

            VPSS_RWZB_GetRwzbInfo(&(pstInst->stRwzbInfo), &pstHalInfo->stRwzbInfo, &stRwzbImage);
        }
        else
        {
            pstHalInfo->stRwzbInfo.u32EnRwzb = HI_FALSE;
        }
    }
#endif

    /*****************************DEI or TNR cfg*******************************/
    VPSS_CHECK_NULL(stInIntf.pfnSetInfo);

    stInIntf.pfnSetInfo(&(pstInst->stInEntity), VPSS_SET_INFO_INPUT_CFG, enLR, pstHalInfo);

    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
        if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L
            || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_R)
        {
            pstFrmNode = pstTask->pstFrmNode[i * 2];
        }
        else
#endif
        {
            pstFrmNode = pstTask->pstFrmNode[i * 2 + enLR];
        }

#ifdef ZME_2L_TEST
#ifndef VPSS_HAL_WITH_CBB
        if ( HI_TRUE == pstTask->pstInstance->stPort[i].bNeedRotate)
        {
            pstFrmNode = pstTask->pstFrmNodeRoBuf[i];
        }
        else if ( HI_TRUE == pstTask->pstInstance->stPort[i].bNeedZME2L)
#else
        if ( HI_TRUE == pstTask->pstInstance->stPort[i].bNeedZME2L)
#endif
        {
            pstFrmNode = pstTask->pstFrmNodeZME1L;
        }
#endif

#ifdef VPSS_HAL_WITH_CBB
        VPSS_INST_GetRotate(pstInst, i, &pstHalInfo->astPortInfo[i], pstCur);
#endif
        if (pstFrmNode != HI_NULL)
        {
            pstHalInfo->astPortInfo[i].bEnable = HI_TRUE;
            pstHalInfo->astPortInfo[i].bConfig = HI_FALSE;
#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
            pstHalInfo->astPortInfo[i].bCmpLoss = VPSS_ISLOSS_CMP;
#endif
            pstHalInfo->astPortInfo[i].eLetterBoxColor = pstTask->pstInstance->stPort[i].eLetterBoxColor;

#ifdef VPSS_SUPPORT_OUT_TUNNEL
            pstHalInfo->astPortInfo[i].bOutLowDelay = pstTask->bOutLowDelay;
#endif
            if ((pstCur->ePixFormat == HI_DRV_PIX_FMT_NV12
                 || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1
                 || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE
                 || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
                && (pstInst->stPort[i].eFormat == HI_DRV_PIX_FMT_NV21_CMP
                    || pstInst->stPort[i].eFormat == HI_DRV_PIX_FMT_NV21
                    || pstInst->stPort[i].eFormat == HI_DRV_PIX_FMT_NV61_2X1))
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_TRUE;
            }
            else if ((pstCur->ePixFormat == HI_DRV_PIX_FMT_NV21
                      || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1
                      || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE
                      || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP)
                     && (pstInst->stPort[i].eFormat == HI_DRV_PIX_FMT_NV12
                         || pstInst->stPort[i].eFormat == HI_DRV_PIX_FMT_NV12_CMP
                         || pstInst->stPort[i].eFormat == HI_DRV_PIX_FMT_NV16_2X1))
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_TRUE;
            }
            else if (pstInst->stPort[i].bUVInver) //dbg cmd
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_TRUE;
            }
            else
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_FALSE;
            }

#ifdef ZME_2L_TEST
            VPSS_INST_SetOutFrameInfo(pstInst, i,
                                      &pstFrmNode->stBuffer, &pstFrmNode->stOutFrame, enLR);
#ifdef VPSS_SUPPORT_OUT_TUNNEL
            if (pstHalInfo->astPortInfo[i].bOutLowDelay)
            {
                pstFrmNode->stOutFrame.u32TunnelPhyAddr = VPSS_HAL_TunnelOut_GetBufAddr(enIp, pstHalInfo, i);
            }
            else
            {
                pstFrmNode->stOutFrame.u32TunnelPhyAddr = HI_NULL;
            }
#endif
#else
            //如果开启了旋转，使用旋转BUFFER
#ifndef VPSS_HAL_WITH_CBB
            if ((HI_DRV_VPSS_ROTATION_90 == pstInst->stPort[i].enRotation)
                || (HI_DRV_VPSS_ROTATION_270 == pstInst->stPort[i].enRotation))
#else
            if (0)
#endif
            {
                VPSS_INST_SetOutFrameInfo(pstInst, i,
                                          &g_stVpssCtrl[enIp].stRoBuf[i], &pstFrmNode->stOutFrame, enLR);
            }
            else
            {
                VPSS_INST_SetOutFrameInfo(pstInst, i,
                                          &pstFrmNode->stBuffer, &pstFrmNode->stOutFrame, enLR);
            }
#endif

            VPSS_INST_SetHalFrameInfo(&pstFrmNode->stOutFrame,
                                      &pstHalInfo->astPortInfo[i].stOutInfo, enLR);

#ifndef VPSS_ZME_SUPPORT_10BIT
            /* when vpss is working at :10bit src input , 8bit output with ZME,CROP eanble.
              Cfg the input src as 8bit, because ZME,CROP do not support 10bit */
            if ((HI_DRV_PIXEL_BITWIDTH_10BIT == pstCur->enBitWidth)
                && (HI_DRV_PIXEL_BITWIDTH_8BIT == pstHalInfo->astPortInfo[i].stOutInfo.enBitWidth))
            {
                pstHalInfo->stInInfo.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                for (j = 0; j < i; j++)
                {
                    pstHalInfo->astPortInfo[j].stOutInfo.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                    pstTask->pstFrmNode[j * 2]->stOutFrame.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                }
            }
#endif
            VPSS_INST_GetInCrop(pstInst, i, &pstHalInfo->astPortInfo[i].stInCropRect);
            if (HI_DRV_FT_TAB == pstCur->eFrmType)
            {
                if (VPSS_HAL_NODE_3D_FRAME_R == pstHalInfo->enNodeType)
                {
                    pstHalInfo->astPortInfo[i].stInCropRect.s32Y
                    += (pstCur->u32Height / 2);
                    pstHalInfo->astPortInfo[i].stInCropRect.s32Y
                    &= VPSS_HEIGHT_ALIGN;
                }
                pstHalInfo->astPortInfo[i].stInCropRect.s32Height
                -= (pstCur->u32Height / 2);
                pstHalInfo->astPortInfo[i].stInCropRect.s32Height
                &= VPSS_HEIGHT_ALIGN;
            }
            else if (HI_DRV_FT_SBS == pstCur->eFrmType)
            {
                if (VPSS_HAL_NODE_3D_FRAME_R == pstHalInfo->enNodeType)
                {
                    pstHalInfo->astPortInfo[i].stInCropRect.s32X
                    += (pstCur->u32Width / 2);
                    pstHalInfo->astPortInfo[i].stInCropRect.s32X
                    &= VPSS_WIDTH_ALIGN;
                }
                pstHalInfo->astPortInfo[i].stInCropRect.s32Width
                -= (pstCur->u32Width / 2);
                pstHalInfo->astPortInfo[i].stInCropRect.s32Width
                &= VPSS_WIDTH_ALIGN;
            }
            else
            {
                /*do nothing!!*/
            }

            VPSS_INST_GetVideoRect(pstInst, i, &pstHalInfo->astPortInfo[i].stInCropRect,
                                   &pstHalInfo->astPortInfo[i].stVideoRect,
                                   &pstHalInfo->astPortInfo[i].stOutCropRect);

            VPSS_DBG_INFO("Incrop W H %d %d\n",
                          pstHalInfo->astPortInfo[i].stInCropRect.s32Width,
                          pstHalInfo->astPortInfo[i].stInCropRect.s32Height);
            VPSS_DBG_INFO("VRect W H %d %d\n",
                          pstHalInfo->astPortInfo[i].stVideoRect.s32Width,
                          pstHalInfo->astPortInfo[i].stVideoRect.s32Height);
            VPSS_DBG_INFO("ORect W H %d %d\n",
                          pstHalInfo->astPortInfo[i].stOutCropRect.s32Width,
                          pstHalInfo->astPortInfo[i].stOutCropRect.s32Height);

            VPSS_SAFE_MEMCPY(&(pstFrmNode->stOutFrame.stLbxInfo),
                             &(pstHalInfo->astPortInfo[i].stVideoRect),
                             sizeof(HI_RECT_S));
#ifndef VPSS_HAL_WITH_CBB
            VPSS_INST_GetRotate(pstInst, i, &pstHalInfo->astPortInfo[i], pstCur);
#endif
        }
        else
        {
            pstHalInfo->astPortInfo[i].bEnable = HI_FALSE;
        }
    }

    return HI_SUCCESS;

}

HI_BOOL VPSS_CTRL_VirtualPortLowQulity(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_BOOL bStart = HI_FALSE;
    HI_U32 u32Cnt;
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;
    VPSS_HAL_PORT_INFO_S *pstPortInfo;
    VPSS_PORT_S         *pstPortCfg;
    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;
    for (u32Cnt = 0 ; u32Cnt < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Cnt ++)
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[u32Cnt]);
        pstPortCfg  = &(pstInst->stPort[u32Cnt]);
        if (pstPortInfo->bEnable == HI_TRUE
            && pstPortInfo->bConfig == HI_FALSE)
        {
            if ((pstPortCfg->u32MaxFrameRate < 50)
                && (HI_FALSE == pstHalInfo->stInInfo.bProgressive))
            {
                bStart = HI_TRUE;
            }
        }
    }
    return bStart;
}


#ifndef VPSS_HAL_WITH_CBB
HI_BOOL VPSS_CTRL_CheckVirtualStart(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_BOOL bStart = HI_FALSE;

    HI_U32 u32Cnt;

    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;
    VPSS_HAL_PORT_INFO_S *pstPortInfo;

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

    for (u32Cnt = 0 ; u32Cnt < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Cnt ++)
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[u32Cnt]);

        if (pstPortInfo->bEnable == HI_TRUE
            && pstPortInfo->bConfig == HI_FALSE)
        {
            bStart = HI_TRUE;
        }
    }

    return bStart;
}
#endif

HI_S32 VPSS_CTRL_Start2DTask_First3Field(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{

#ifdef VPSS_HAL_WITH_CBB
#if defined(CHIP_TYPE_hi3796mv200)
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

    pstHalInfo->enNodeType = VPSS_HAL_TASK_DETILE_FIRST3FIELD;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstTask);
    HI_ASSERT(s32Ret != HI_FAILURE);

    VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_DETILE_FIRST3FIELD, pstInst->abNodeVaild);
#endif
#else
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_DETILE_STEP1;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstTask);
    HI_ASSERT(s32Ret != HI_FAILURE);
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_DETILE_STEP1] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_DETILE_STEP1);

    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_DETILE_STEP2;
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_DETILE_STEP2] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_DETILE_STEP2);
#endif
    return HI_SUCCESS;
}


HI_S32 VPSS_CTRL_GetFieldIdx(VPSS_TASK_S *pstTask)
{
    VPSS_IN_ENTITY_S *pstEntity = &(pstTask->pstInstance->stInEntity);
    HI_DRV_BUF_ADDR_E enLR = HI_DRV_BUF_ADDR_LEFT;
    HI_S32 idx;
    HI_U32 u32FieldIdx;
    HI_DRV_VIDEO_FRAME_S *pstRef[4] = {HI_NULL, HI_NULL, HI_NULL, HI_NULL};
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret;

    s32Ret = VPSS_IN_GetIntf(pstEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    stInIntf.pfnGetInfo( pstEntity,
                         VPSS_IN_INFO_REF,
                         enLR,
                         (HI_VOID *)pstRef);

    u32FieldIdx = 0;
    for (idx = 2; idx >= 0; idx--) //field 0,1,2
    {
        if (pstRef[idx] != HI_NULL)
        {
            u32FieldIdx++;
        }
    }

    return u32FieldIdx;
}

HI_BOOL VPSS_CTRL_Check2DDetileStart(VPSS_TASK_S *pstTask)
{
    VPSS_IN_ENTITY_S *pstEntity = &(pstTask->pstInstance->stInEntity);
    HI_S32 s32FieldIdx;
    if (pstEntity->stStreamInfo.u32StreamProg)
    {
        return HI_FALSE;
    }

    s32FieldIdx = VPSS_CTRL_GetFieldIdx(pstTask);
    if ((0 <= s32FieldIdx) && (s32FieldIdx < 3))//field 0,1,2
    {
        pstTask->stVpssHalInfo.u32DetileFieldIdx = s32FieldIdx;
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_VOID VPSS_CTRL_CopyWBCStatistic(VPSS_TASK_S *pstTask)
{
#ifdef VPSS_HAL_WITH_CBB
    if (HI_NULL != pstTask->stVpssHalInfo.stSttAddr.pu8stt_w_vir_addr)
    {
        VPSS_SAFE_MEMCPY(&(pstTask->pstInstance->stPqWbcReg),
                         (PQ_VPSS_WBC_REG_S *)pstTask->stVpssHalInfo.stSttAddr.pu8stt_w_vir_addr,
                         sizeof(PQ_VPSS_WBC_REG_S));
    }
#else
    if (HI_NULL != pstTask->stVpssHalInfo.pu8stt_w_vir_addr)
    {
        VPSS_SAFE_MEMCPY(&(pstTask->pstInstance->stPqWbcReg),
                         (PQ_VPSS_WBC_REG_S *)pstTask->stVpssHalInfo.pu8stt_w_vir_addr,
                         sizeof(PQ_VPSS_WBC_REG_S));
    }
#endif

    return;
}

HI_S32 VPSS_CTRL_Start2DTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;
#ifdef VPSS_HAL_WITH_CBB
    VPSS_FB_NODE_S *pstOutputInfo;
    HI_U32 PortId;
#endif

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

    pstHalInfo->enNodeType = VPSS_INST_Check2DNodeType(pstInst);

    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstTask);
    HI_ASSERT(s32Ret != HI_FAILURE);

#ifdef VPSS_HAL_WITH_CBB
    for (PortId = 0; PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; PortId++)
    {
        pstOutputInfo = pstTask->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT];

        if (pstInst->stPort[PortId].bNeedRotate)
        {
            //set rotation output frame info
            if (HI_NULL != pstOutputInfo)
            {
                VPSS_INST_SetRotationOutFrameInfo(pstInst, PortId,
                                                  &pstOutputInfo->stBuffer, &pstOutputInfo->stOutFrame, HI_DRV_BUF_ADDR_LEFT);
            }
            else
            {
                VPSS_FATAL("pstOutputInfo is NULL! PortId:%d\n", PortId);
                // return HI_FAILURE;
            }
        }
    }

    if (VPSS_CTRL_VirtualPortLowQulity(enIp, pstTask))
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_LOWQUALITY, pstInst->abNodeVaild);
    }
    else if ((VPSS_HAL_NODE_2D_FRAME == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_UHD == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_UHD_VIRTUAL == pstHalInfo->enNodeType))
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FRAME, pstInst->abNodeVaild);
    }
    else if ((VPSS_HAL_NODE_2D_DEI == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_SD_FIRST == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_FIELD == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_SD_SECOND == pstHalInfo->enNodeType))
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD, pstInst->abNodeVaild);
    }
    else if (VPSS_HAL_NODE_2D_DEI_LAST_2FIELD == pstHalInfo->enNodeType)
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_LAST2FIELD, pstInst->abNodeVaild);
    }
    else if (VPSS_HAL_NODE_HDR_DETILE_NOALG == pstHalInfo->enNodeType)
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_HDR, pstInst->abNodeVaild);
    }
#else
    if (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_Field)
    {
        pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_FIELD] = HI_TRUE;
        VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD);

        if (VPSS_CTRL_CheckVirtualStart(enIp, pstTask))
        {
            pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL]
                = HI_TRUE;
            VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL);
        }
    }
    else if (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_5Field
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_FRAME
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_HIGH_SPEED
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_HDR_DETILE_NOALG)
    {
        pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D] = HI_TRUE;

        VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D);

        if (VPSS_CTRL_CheckVirtualStart(enIp, pstTask))
        {
            if ((VPSS_CTRL_VirtualPortLowQulity(enIp, pstTask))
                && (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_5Field))
            {
                pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_Field;
                pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL] = HI_TRUE;
                VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL);
            }
            else
            {
                pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_VIRTUAL] = HI_TRUE;
                VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_VIRTUAL);
            }
        }
    }
    else if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L)
    {
        pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_SPLIT_L] = HI_TRUE;

        VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_SPLIT_L);

        if (VPSS_CTRL_CheckVirtualStart(enIp, pstTask))
        {
            pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_FRAME;

            pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_VIRTUAL]
                = HI_TRUE;

            VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_VIRTUAL);
        }
    }

    else
    {
        VPSS_ERROR("Invalid Node Type %d\n", pstHalInfo->enNodeType);
    }
#endif

    return HI_SUCCESS;
}

HI_BOOL VPSS_CTRL_Check2DStart(VPSS_TASK_S *pstTask)
{
    HI_U32 i;

    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if (pstTask->pstFrmNode[i * 2] != HI_NULL)
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}
#ifndef VPSS_HAL_WITH_CBB
HI_BOOL VPSS_CTRL_CheckRotateStart(VPSS_TASK_S *pstTask, HI_U32 PortId)
{
    VPSS_PORT_S *pstPort;
    pstPort = &(pstTask->pstInstance->stPort[PortId]);

    if ((HI_DRV_VPSS_ROTATION_DISABLE == pstPort->enRotation)
        || (HI_DRV_VPSS_ROTATION_180 == pstPort->enRotation)
        || (HI_FALSE == pstPort->bEnble))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_BOOL VPSS_CTRL_CheckZME1LStart(VPSS_TASK_S *pstTask, HI_U32 PortId)
{
    VPSS_PORT_S *pstPort;
    pstPort = &(pstTask->pstInstance->stPort[PortId]);

    if (( HI_TRUE == pstTask->bZME2lTaskNeed[PortId]) && (HI_TRUE == pstPort->bEnble))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

#ifdef ZME_2L_TEST
/******************************************************************************
brief      : CNcomment :  check rotate and ZME_2L task
           :  本函数功能:
              1  根据输入图像信息(解码图像)检测与判定是否需要做二级缩放及旋转操作。并记录每个port相关标志。
              2  如果需要做二级缩放(旋转)，则分配所需要的缓存图像buffer。
attention  :
param[in]  : enIp      :  vpss ID
             pstTask   :
retval     : HI_S32
see        :
author     :sdk
******************************************************************************/

HI_U32 VPSS_CTRL_Zme2lAndRotateCfg(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_U32  i = 0, u32DstW = 0, u32DstH = 0 , u32RotateNeed = 0;

    HI_S32 s32Ret                = HI_FAILURE;
    VPSS_INSTANCE_S     *pstInst = HI_NULL;
    HI_DRV_VIDEO_FRAME_S *pstCur = HI_NULL;
    VPSS_IN_INTF_S stInIntf;

    HI_U32 u32BufSize            = 0;
    HI_U32 u32BufStride          = 0;
    HI_DRV_VIDEO_FRAME_S *pstFrm = HI_NULL;
    VPSS_BUFFER_S        *pstBuf = HI_NULL;

    VPSS_PORT_S          *pstPort[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER] = {HI_NULL, HI_NULL, HI_NULL};
    HI_PQ_ZME_WIN_S      stZmeWin;

    HI_DRV_VIDEO_PRIVATE_S *pPriInfo;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;


    pstInst = pstTask->pstInstance;
    memset(pstTask->bZME2lTaskNeed, 0, sizeof(HI_BOOL)*DEF_HI_DRV_VPSS_PORT_MAX_NUMBER);

    s32Ret = VPSS_IN_GetIntf(&(pstInst->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);
    s32Ret = stInIntf.pfnGetProcessImage(&pstInst->stInEntity, &pstCur);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
        return HI_FAILURE;
    }

    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        pstPort[i]  = &pstInst->stPort[i];

        if ( HI_TRUE == pstPort[i]->bEnble && VPSS_INVALID_HANDLE != pstPort[i]->s32PortId )
        {
            /*  如果需要做旋转操作，则记录当前port旋转标志 并 申请相应的缓存buffer*/
            if (VPSS_CTRL_CheckRotateStart(pstTask, i))
            {
                pstPort[i]->bNeedRotate = HI_TRUE;
                u32RotateNeed++;
                if ( HI_NULL == pstTask->pstFrmNodeRoBuf[i])  //只分配一次缓存帧存
                {
                    pstTask->pstFrmNodeRoBuf[i] = (VPSS_FB_NODE_S *)VPSS_VMALLOC(sizeof(VPSS_FB_NODE_S));
                    memset((VPSS_FB_NODE_S *)(pstTask->pstFrmNodeRoBuf[i]), 0x0, (sizeof(VPSS_FB_NODE_S)));
                }

                if ( HI_NULL != pstTask->pstFrmNodeRoBuf[i])
                {
                    pstFrm = &pstTask->pstFrmNodeRoBuf[i]->stOutFrame;
                    pstBuf = &pstTask->pstFrmNodeRoBuf[i]->stBuffer;

                    if (pstPort[i]->s32OutputWidth != 0 && pstPort[i]->s32OutputHeight != 0)
                    {
                        pstFrm->u32Width  = pstPort[i]->s32OutputHeight;
                        pstFrm->u32Height = pstPort[i]->s32OutputWidth;
                    }
                    else
                    {
                        pPriInfo = (HI_DRV_VIDEO_PRIVATE_S *) &pstCur->u32Priv[0];
                        pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pPriInfo->u32Reserve[0]);
                        if ((HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype)
                            && (pstCur->enFieldMode != HI_DRV_FIELD_ALL)
                            && (pstCur->enBufValidMode == HI_DRV_FIELD_ALL))
                        {
                            pstFrm->u32Width = pstCur->u32Height * 2;
                            pstFrm->u32Height = pstCur->u32Width;
                        }
                        else
                        {
                            pstFrm->u32Width = pstCur->u32Height;
                            pstFrm->u32Height = pstCur->u32Width;
                        }
                    }

                    VPSS_OSAL_CalBufSize(&u32BufSize,
                                         &u32BufStride,
                                         pstFrm->u32Height,
                                         pstFrm->u32Width,
                                         pstPort[i]->eFormat,
                                         pstPort[i]->enOutBitWidth);

                    if ((pstBuf->stMemBuf.u32Size != u32BufSize)
                        || (pstBuf->u32Stride != u32BufStride))
                    {
                        if (pstBuf->stMemBuf.u32Size != 0)
                        {
                            VPSS_OSAL_FreeMem(&(pstBuf->stMemBuf));
                        }

                        if (!pstInst->bSecure)
                        {
                            s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_NORMAL, u32BufSize,
                                                           HI_NULL,
                                                           "VPSS_RoBuf",
                                                           &(pstBuf->stMemBuf));
                        }
                        else
                        {
                            s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_SECURE, u32BufSize,
                                                           HI_NULL,
                                                           "VPSS_RoBuf",
                                                           &(pstBuf->stMemBuf));
                        }
                        if (s32Ret != HI_SUCCESS)
                        {
                            VPSS_FATAL("Alloc RoBuf Failed\n");
                        }

                        pstBuf->u32Stride = u32BufStride;
                    }
                }
            }

            else
            {
                if (HI_NULL != pstTask->pstFrmNodeRoBuf[i])
                {
                    //释放旋转内存，节省SDK空间占用
                    if (0 != pstTask->pstFrmNodeRoBuf[i]->stBuffer.stMemBuf.u32Size)
                    {
                        VPSS_OSAL_FreeMem(&(pstTask->pstFrmNodeRoBuf[i]->stBuffer.stMemBuf));
                        pstTask->pstFrmNodeRoBuf[i]->stBuffer.stMemBuf.u32Size = 0;
                        pstTask->pstFrmNodeRoBuf[i]->stBuffer.u32Stride = 0;
                    }

                    VPSS_VFREE(pstTask->pstFrmNodeRoBuf[i]);
                    pstTask->pstFrmNodeRoBuf[i] = HI_NULL;
                }
            }
        }
    }

    if ( u32RotateNeed > 0) //如果有旋转任务，则不再做二级缩放
    {
        return HI_SUCCESS;
    }

    stZmeWin.stPort0Win.u32Width = pstPort[0]->s32OutputWidth;
    stZmeWin.stPort0Win.u32Height = pstPort[0]->s32OutputHeight;

    stZmeWin.stPort1Win.u32Width = pstPort[1]->s32OutputWidth;
    stZmeWin.stPort1Win.u32Height = pstPort[1]->s32OutputHeight;

    if (  0 != u32DstW && 0 != u32DstH) //只分配一次缓存帧存

    {
        if (HI_NULL == pstTask->pstFrmNodeZME1L) //只分配一次缓存帧存
        {
            pstTask->pstFrmNodeZME1L = (VPSS_FB_NODE_S *)VPSS_VMALLOC(sizeof(VPSS_FB_NODE_S));
        }

        if ( HI_NULL != pstTask->pstFrmNodeZME1L)
        {
            pstFrm = &pstTask->pstFrmNodeZME1L->stOutFrame;
            pstBuf = &pstTask->pstFrmNodeZME1L->stBuffer;

            pstFrm->u32Width    = u32DstW;
            pstFrm->u32Height   = u32DstH;

            VPSS_OSAL_CalBufSize(&u32BufSize,
                                 &u32BufStride,
                                 pstFrm->u32Height,
                                 pstFrm->u32Width,
                                 HI_DRV_PIX_FMT_NV21,
                                 HI_DRV_PIXEL_BITWIDTH_10BIT);

            if ((pstBuf->stMemBuf.u32Size != u32BufSize)
                || (pstBuf->u32Stride != u32BufStride))
            {
                if (pstBuf->stMemBuf.u32Size != 0)
                {
                    VPSS_OSAL_FreeMem(&(pstBuf->stMemBuf));
                }
                if (!pstInst->bSecure)
                {
                    s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_NORMAL, u32BufSize,
                                                   "VPSS_ZME1LBuf",
                                                   HI_NULL,
                                                   &(pstBuf->stMemBuf));
                }
                else
                {
                    s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_SECURE, u32BufSize,
                                                   "VPSS_ZME1LBuf",
                                                   HI_NULL,
                                                   &(pstBuf->stMemBuf));
                }
                if (s32Ret != HI_SUCCESS)
                {
                    VPSS_FATAL("Alloc ZME1LBuf Failed\n");
                }

                pstBuf->u32Stride = u32BufStride;
            }
        }
    }
    else
    {
        if ( HI_NULL != pstTask->pstFrmNodeZME1L)
        {
            //释放二级缩放内存，节省SDK空间占用
            if (0 != pstTask->pstFrmNodeZME1L->stBuffer.stMemBuf.u32Size)
            {
                VPSS_OSAL_FreeMem(&(pstTask->pstFrmNodeZME1L->stBuffer.stMemBuf));
                pstTask->pstFrmNodeZME1L->stBuffer.stMemBuf.u32Size = 0;
                pstTask->pstFrmNodeZME1L->stBuffer.u32Stride = 0;

                VPSS_VFREE(pstTask->pstFrmNodeZME1L);
                pstTask->pstFrmNodeZME1L = HI_NULL;
            }
        }
    }

    return s32Ret;
}


HI_S32 VPSS_CTRL_StartZME2LTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask, HI_U32 PortId)
{
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;
    HI_DRV_VIDEO_FRAME_S *pstInputFrame;
    VPSS_FB_NODE_S *pstOutputInfo;

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

    //set ZME_2L input frame info
    pstInputFrame = &(pstTask->pstFrmNodeZME1L->stOutFrame);
    VPSS_INST_SetHalFrameInfo(pstInputFrame, &pstHalInfo->stInInfo, HI_DRV_BUF_ADDR_LEFT);

    //set ZME_2L output frame info
    pstOutputInfo = pstTask->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT];
    VPSS_INST_SetOutFrameInfo(pstInst, PortId, &pstOutputInfo->stBuffer, &pstOutputInfo->stOutFrame, HI_DRV_BUF_ADDR_LEFT);
    VPSS_INST_SetHalFrameInfo(&pstOutputInfo->stOutFrame, &pstHalInfo->astPortInfo[PortId].stOutInfo, HI_DRV_BUF_ADDR_LEFT);

    VPSS_INST_GetInCrop(pstInst, PortId, &pstHalInfo->astPortInfo[PortId].stInCropRect);

    VPSS_INST_GetVideoRect(pstInst, PortId, &pstHalInfo->astPortInfo[PortId].stInCropRect,
                           &pstHalInfo->astPortInfo[PortId].stVideoRect,
                           &pstHalInfo->astPortInfo[PortId].stOutCropRect);

    pstHalInfo->enNodeType = VPSS_HAL_NODE_ZME_2L;
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_P0_ZME_L2 + PortId] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_P0_ZME_L2 + PortId );
    return HI_SUCCESS;
}
#endif

HI_S32 VPSS_CTRL_StartRotateTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask, HI_U32 PortId)
{
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;
    HI_DRV_VIDEO_FRAME_S *pstInputFrame;
    VPSS_FB_NODE_S *pstOutputInfo;

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

#ifdef ZME_2L_TEST
    //set rotation input frame info
    pstInputFrame = &(pstTask->pstFrmNodeRoBuf[PortId]->stOutFrame);
    VPSS_INST_SetHalFrameInfo(pstInputFrame, &pstHalInfo->stInInfo, HI_DRV_BUF_ADDR_LEFT);
#else
    //set rotation input frame info
    pstInputFrame = &(pstTask->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT]->stOutFrame);
    VPSS_INST_SetHalFrameInfo(pstInputFrame, &pstHalInfo->stInInfo, HI_DRV_BUF_ADDR_LEFT);

#endif

    //set rotation output frame info
    pstOutputInfo = pstTask->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT];
    VPSS_INST_SetRotationOutFrameInfo(pstInst, PortId,
                                      &pstOutputInfo->stBuffer, &pstOutputInfo->stOutFrame, HI_DRV_BUF_ADDR_LEFT);

    if ((HI_DRV_VPSS_ROTATION_90 == pstInst->stPort[PortId].enRotation)
        || (HI_DRV_VPSS_ROTATION_270 == pstInst->stPort[PortId].enRotation))
    {
        pstOutputInfo->stOutFrame.stLbxInfo.s32X =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32Y;
        pstOutputInfo->stOutFrame.stLbxInfo.s32Y =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32X;
        pstOutputInfo->stOutFrame.stLbxInfo.s32Width =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32Height;
        pstOutputInfo->stOutFrame.stLbxInfo.s32Height =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32Width;
    }
    else
    {
        memcpy(&(pstOutputInfo->stOutFrame.stLbxInfo),
               &(pstHalInfo->astPortInfo[PortId].stVideoRect),
               sizeof(HI_RECT_S));
    }

    VPSS_INST_SetHalFrameInfo(&pstOutputInfo->stOutFrame,
                              &pstHalInfo->astPortInfo[PortId].stOutInfo, HI_DRV_BUF_ADDR_LEFT);

    //rotation Y
    pstHalInfo->enNodeType = VPSS_HAL_NODE_ROTATION_Y;
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_P0_RO_Y + PortId * 2] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_P0_RO_Y + PortId * 2);

    //rotation C
    pstHalInfo->enNodeType = VPSS_HAL_NODE_ROTATION_C;
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_P0_RO_C + PortId * 2] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_P0_RO_C + PortId * 2);

    return HI_SUCCESS;
}

#endif
HI_S32 VPSS_CTRL_Start3DTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;

    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;

    pstHalInfo->enNodeType = VPSS_INST_Check3DNodeType(pstInst);

    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_RIGHT, pstTask);
    HI_ASSERT(s32Ret != HI_FAILURE);

#ifndef VPSS_HAL_WITH_CBB
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_3D_R] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_3D_R);
#else
    VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_3D, pstInst->abNodeVaild);
#endif
    return HI_SUCCESS;
}

HI_BOOL VPSS_CTRL_Check3DStart(VPSS_TASK_S *pstTask)
{
    HI_U32 i;

    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if (pstTask->pstFrmNode[i * 2 + 1] != HI_NULL)
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}

HI_S32 VPSS_CTRL_GetOutBufferRect(HI_RECT_S stOriRect, HI_RECT_S *pstRevisedRect)
{
    HI_U32 u32OriW = 0, u32OriH = 0;
    HI_U32 u32DstW = 0, u32DstH = 0;
    HI_U32 u32RatioW;
    HI_U32 u32RatioH;
    HI_U32 u32TmpH;
    HI_U32 u32TmpW;
    HI_U32 u32WidthLevel;
    HI_U32 u32HeightLevel;

    u32WidthLevel = 3840;
    u32HeightLevel = 2160;

    u32OriW = stOriRect.s32Width;
    u32OriH = stOriRect.s32Height;

    if (u32OriW < u32WidthLevel && u32OriH < u32HeightLevel)
    {
        u32DstW = u32OriW;
        u32DstH = u32OriH;
    }
    else if (u32OriW >= u32WidthLevel && u32OriH >= u32HeightLevel)
    {
        u32DstW = u32WidthLevel;
        u32DstH = u32HeightLevel;
    }
    else
    {
        u32RatioW = u32OriW * 2048 / u32WidthLevel;
        u32RatioH = u32OriH * 2048 / u32HeightLevel;

        if (u32RatioW > u32RatioH)
        {
            u32TmpW = u32OriW * 2048 / u32RatioW;
            u32TmpH = u32OriH * 2048 / u32RatioW;
        }
        else
        {
            u32TmpW = u32OriW * 2048 / u32RatioH;
            u32TmpH = u32OriH * 2048 / u32RatioH;
        }

        VPSS_PIXLE_DOWNALIGN_W(u32TmpW, HI_FALSE);
        VPSS_PIXLE_DOWNALIGN_H(u32TmpH, HI_FALSE);

        u32DstW = u32TmpW;
        u32DstH = u32TmpH;
    }

    pstRevisedRect->s32Width = u32DstW;
    pstRevisedRect->s32Height = u32DstH;

    return HI_SUCCESS;
}

#ifdef VPSS_SUPPORT_OUT_TUNNEL
HI_BOOL VPSS_CTRL_CheckLowDelay(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_BOOL bLowDelayTask = HI_FALSE;
    VPSS_INSTANCE_S *pstInstance;
    VPSS_IN_INTF_S stInIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage;
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_U32 u32EnablePort = 0;
    HI_BOOL bRotation = HI_FALSE;

    if (pstTask->pstInstance)
    {
        pstInstance = pstTask->pstInstance;

        (HI_VOID)VPSS_IN_GetIntf(&(pstTask->pstInstance->stInEntity), &stInIntf);

        VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

        (HI_VOID)stInIntf.pfnGetProcessImage(&(pstTask->pstInstance->stInEntity),
                                             &pstImage);

        for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
        {
            pstPort = &((pstTask->pstInstance)->stPort[u32Count]);
            if (pstPort->bEnble)
            {
                u32EnablePort++;

                if ((pstPort->enRotation != HI_DRV_VPSS_ROTATION_DISABLE)
                    || (pstPort->bHoriFlip == HI_TRUE)
                    || (pstPort->bVertFlip == HI_TRUE))
                {
                    bRotation = HI_TRUE;
                }

                if (pstPort->bTunnelEnable)
                {
                    bLowDelayTask = HI_TRUE;
                }
            }
        }

        if (pstImage->u32Width > 1920)
        {
            bLowDelayTask = HI_FALSE;
        }

        if (pstImage->bSecure)
        {
            bLowDelayTask = HI_FALSE;
        }

        if (pstImage->eFrmType != HI_DRV_FT_NOT_STEREO)
        {
            bLowDelayTask = HI_FALSE;
        }

        if (pstImage->u32Circumrotate != 0)
        {
            bLowDelayTask = HI_FALSE;
        }

        if (u32EnablePort > 1 || bRotation == HI_TRUE)
        {
            bLowDelayTask = HI_FALSE;
        }
    }
    else
    {
        bLowDelayTask = HI_FALSE;
    }

    return bLowDelayTask;
}
#endif

HI_S32 VPSS_CTRL_CreateTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32StoreH;
    HI_U32 u32StoreW;
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_DRV_VPSS_BUFLIST_CFG_S  *pstBufListCfg;
    VPSS_IN_INTF_S stInIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage = HI_NULL;
    HI_U32 u32ExtBufSize;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    /*
        Traversal instance list to find a Available inst
        available means two requirement:
        1.one undo image
        2.at least two writting space
     */
    pstTask->pstInstance = VPSS_CTRL_GetServiceInstance(enIp);

    if (HI_NULL == pstTask->pstInstance)
    {
        return HI_FAILURE;
    }

    /*
        get the image info to  inform user out buffer size
    */
    (HI_VOID)VPSS_IN_GetIntf(&(pstTask->pstInstance->stInEntity), &stInIntf);

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

    (HI_VOID)stInIntf.pfnGetProcessImage(&(pstTask->pstInstance->stInEntity),
                                         &pstImage);
    if (HI_NULL == pstImage)
    {
        VPSS_FATAL("Get image fail!!!\n");
        return HI_FAILURE;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);
    /***********config out buffer************************/
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &((pstTask->pstInstance)->stPort[u32Count]);
        pstBufListCfg = &(pstPort->stFrmInfo.stBufListCfg);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE &&
            pstPort->bEnble == HI_TRUE)
        {
            if (pstPort->s32OutputHeight == 0 && pstPort->s32OutputWidth == 0)
            {
                HI_RECT_S stInRect;
                VPSS_INST_GetInCrop(pstTask->pstInstance, u32Count, &stInRect);
                u32StoreW = (HI_U32)stInRect.s32Width;
                u32StoreH = (HI_U32)stInRect.s32Height;

                //u32StoreH = pstStreamInfo->u32StreamH;
                //u32StoreW = pstStreamInfo->u32StreamW;
            }
            else
            {
                if (pstBufListCfg->eBufType != HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
                {
                    u32StoreH = pstPort->s32OutputHeight;
                    u32StoreW = pstPort->s32OutputWidth;
                }
                else
                {
                    HI_RECT_S stInRect;
                    HI_RECT_S stBufferRect;
                    VPSS_INST_GetInCrop(pstTask->pstInstance, u32Count, &stInRect);

                    VPSS_CTRL_GetOutBufferRect(stInRect, &stBufferRect);

                    u32StoreW = (HI_U32)stBufferRect.s32Width;
                    u32StoreH = (HI_U32)stBufferRect.s32Height;
                }
            }

            if (VPSS_HDR_TYPE_NEED_TRANS_METADATA(pstImage->enSrcFrameType))
            {
                u32ExtBufSize = 4096;//pstImage->unHDRInfo.stDolbyInfo.stMetadata.u32Length;
            }
            else
            {
                u32ExtBufSize = 0;
            }

            if (pstPriv->u32LastFlag == DEF_HI_DRV_VPSS_LAST_FRAME_FLAG)
            {
                pstPort->bCurDropped = HI_FALSE;
            }
            else
            {
                pstPort->bCurDropped = VPSS_INST_CheckIsDropped(pstTask->pstInstance,
                                       pstPort->u32MaxFrameRate,
                                       pstPort->u32OutCount);
            }
            if (pstPort->bCurDropped == HI_FALSE)
            {
                /*2D image -> 1 outFrame 1 buffer*/
                if (pstImage->eFrmType == HI_DRV_FT_NOT_STEREO
                    || pstPort->b3Dsupport == HI_FALSE)
                {
                    pstTask->pstFrmNode[u32Count * 2] =
                        VPSS_FB_GetEmptyFrmBuf(&(pstPort->stFrmInfo),
                                               u32StoreH, u32StoreW,
                                               pstPort->eFormat,
                                               pstPort->enOutBitWidth,
                                               pstTask->pstInstance->bSecure,
                                               u32ExtBufSize);
                    pstTask->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
                }
                /*3D image -> 1 outFrame 2 buffer*/
                else
                {
                    pstTask->pstFrmNode[u32Count * 2] =
                        VPSS_FB_GetEmptyFrmBuf(&(pstPort->stFrmInfo),
                                               u32StoreH, u32StoreW,
                                               pstPort->eFormat,
                                               pstPort->enOutBitWidth,
                                               pstTask->pstInstance->bSecure,
                                               u32ExtBufSize);
                    pstTask->pstFrmNode[u32Count * 2 + 1] =
                        VPSS_FB_GetEmptyFrmBuf(&(pstPort->stFrmInfo),
                                               u32StoreH, u32StoreW,
                                               pstPort->eFormat,
                                               pstPort->enOutBitWidth,
                                               pstTask->pstInstance->bSecure,
                                               u32ExtBufSize);
                    if (pstTask->pstFrmNode[u32Count * 2] == HI_NULL
                        || pstTask->pstFrmNode[u32Count * 2 + 1] == HI_NULL)
                    {

                        if (pstTask->pstFrmNode[u32Count * 2] != HI_NULL)
                        {
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstTask->pstFrmNode[u32Count * 2],
                                                   VPSS_FB_TYPE_NORMAL);
                        }

                        if (pstTask->pstFrmNode[u32Count * 2 + 1] != HI_NULL)
                        {
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstTask->pstFrmNode[u32Count * 2 + 1],
                                                   VPSS_FB_TYPE_NORMAL);
                        }
                        pstTask->pstFrmNode[u32Count * 2] = HI_NULL;
                        pstTask->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
                    }
                }


#if 1
                if (pstBufListCfg->eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
                {
                    /*************************/

                    if (pstPort->eFormat == HI_DRV_PIX_FMT_NV12
                        || pstPort->eFormat == HI_DRV_PIX_FMT_NV21)
                    {
                        pstBufListCfg->u32BufStride = (u32StoreW + 0xf) & 0xfffffff0 ;
                        pstBufListCfg->u32BufSize =
                            pstBufListCfg->u32BufStride * u32StoreH * 3 / 2;
                    }
                    else if (pstPort->eFormat == HI_DRV_PIX_FMT_NV16_2X1
                             || pstPort->eFormat == HI_DRV_PIX_FMT_NV61_2X1)
                    {
                        pstBufListCfg->u32BufStride =  (u32StoreW + 0xf) & 0xfffffff0 ;
                        pstBufListCfg->u32BufSize =
                            pstBufListCfg->u32BufStride * u32StoreH * 2;
                    }
                    else
                    {
                        VPSS_FATAL("Port %x OutFormat%d isn't supported.\n",
                                   pstPort->s32PortId, pstPort->eFormat);
                    }
                    /*************************/
                    if (pstTask->pstFrmNode[u32Count * 2] != HI_NULL)
                    {
                        s32Ret = VPSS_INST_GetFrmBuffer(pstTask->pstInstance, pstPort->s32PortId, pstBufListCfg,
                                                        &(pstTask->pstFrmNode[u32Count * 2]->stBuffer), u32StoreH, u32StoreW);
                        if (s32Ret != HI_SUCCESS)
                        {
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstTask->pstFrmNode[u32Count * 2],
                                                   VPSS_FB_TYPE_NORMAL);
                            if (pstTask->pstFrmNode[u32Count * 2 + 1] != HI_NULL)
                            {
                                VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                       pstTask->pstFrmNode[u32Count * 2 + 1],
                                                       VPSS_FB_TYPE_NORMAL);
                            }
                            VPSS_OSAL_UpLock(&(pstTask->pstInstance->stInstLock));
                            return HI_FAILURE;
                        }
                    }

                    if (pstTask->pstFrmNode[u32Count * 2 + 1] != HI_NULL)
                    {
                        s32Ret = VPSS_INST_GetFrmBuffer(pstTask->pstInstance, pstPort->s32PortId, pstBufListCfg,
                                                        &(pstTask->pstFrmNode[u32Count * 2 + 1]->stBuffer), u32StoreH, u32StoreW);
                        if (s32Ret != HI_SUCCESS)
                        {
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstTask->pstFrmNode[u32Count * 2],
                                                   VPSS_FB_TYPE_NORMAL);
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstTask->pstFrmNode[u32Count * 2 + 1],
                                                   VPSS_FB_TYPE_NORMAL);
                            VPSS_OSAL_UpLock(&(pstTask->pstInstance->stInstLock));
                            return HI_FAILURE;
                        }
                    }
                }
                else
                {

                }
#endif
            }
            else
            {
                pstTask->pstFrmNode[u32Count * 2] = HI_NULL;
                pstTask->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
            }
        }
        else
        {
            pstTask->pstFrmNode[u32Count * 2] = HI_NULL;
            pstTask->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
        }
    }

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER * 2; u32Count++)
    {
        if (pstTask->pstFrmNode[u32Count] != HI_NULL)
        {
            s32Ret = HI_SUCCESS;
            break;
        }
    }

#if 0
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &((pstTask->pstInstance)->stPort[u32Count]);

        if (pstPort->bEnble == HI_TRUE
            && pstPort->bCurDropped == HI_FALSE
            && pstTask->pstFrmNode[u32Count * 2] == HI_NULL)
        {
            s32Ret = HI_FAILURE;
            break;
        }
    }
#endif

    if (s32Ret == HI_SUCCESS)
    {
        for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
        {
            pstPort = &((pstTask->pstInstance)->stPort[u32Count]);
            if (pstPort->bEnble == HI_TRUE)
            {
                pstPort->u32OutCount++;
            }
        }
    }

    return s32Ret;

}


HI_BOOL VPSS_CTRL_Check2DH265InterlaceStart(VPSS_TASK_S *pstTask)
{
    VPSS_IN_INTF_S stInIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage;
    HI_DRV_VIDEO_PRIVATE_S *pPriInfo;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;
    VPSS_CHECK_NULL(pstTask->pstInstance);

    (HI_VOID)VPSS_IN_GetIntf(&(pstTask->pstInstance->stInEntity), &stInIntf);

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

    (HI_VOID)stInIntf.pfnGetProcessImage(&(pstTask->pstInstance->stInEntity),
                                         &pstImage);

    pPriInfo = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pPriInfo->u32Reserve[0]);
    if ((HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype)
        && (!pstImage->bProgressive)
        && pstImage->enBufValidMode == HI_DRV_FIELD_ALL)
    {
        VPSS_DBG_INFO("Start H265Interlace task...\n");
        return HI_TRUE;
    }
    else
    {
        pstTask->stVpssHalInfo.pstH265RefList = HI_NULL;
        VPSS_HAL_H265RefListDeInit(&pstTask->pstInstance->stH265RefList);
        return HI_FALSE;
    }
}
HI_S32 VPSS_CTRL_Start2DTask_H265(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;
    VPSS_INSTANCE_S *pstInst;
    pstHalInfo = &pstTask->stVpssHalInfo;
    pstInst = pstTask->pstInstance;
    pstHalInfo->pstH265RefList = &pstInst->stH265RefList;
    if ((pstInst->stInEntity.stStreamInfo.u32IsNewImage) || (!pstHalInfo->pstH265RefList->bRefListValid))
    {
        pstHalInfo->pstH265RefList = &pstInst->stH265RefList;
        VPSS_HAL_H265RefListInit(pstHalInfo->pstH265RefList,
                                 pstInst->stInEntity.stStreamInfo.u32StreamW,
                                 pstInst->stInEntity.stStreamInfo.u32StreamH,
                                 pstInst->stPort[0].eFormat,
                                 pstInst->bSecure);
    }
#ifdef VPSS_HAL_WITH_CBB
    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstTask);
    HI_ASSERT(s32Ret != HI_FAILURE);

    VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_H265_DEI, pstInst->abNodeVaild);

#else
    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstTask);
    HI_ASSERT(s32Ret != HI_FAILURE);
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_H265_STEP1_INTERLACE] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_H265_STEP1_INTERLACE);
    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_H265_STEP2_DEI;
    pstInst->abNodeVaild[VPSS_HAL_TASK_NODE_2D_H265_STEP2_DEI] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_H265_STEP2_DEI);
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_StartTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_U32 i;
    HI_BOOL bStart2D = HI_TRUE;
    HI_BOOL bStart3D = HI_FALSE;
    HI_S32 s32Ret;

    /* 所有节点都置为HI_FALSE */
#ifdef VPSS_HAL_WITH_CBB
    for (i = 0; i < VPSS_HAL_NODE_BUTT; i++)
    {
        pstTask->pstInstance->abNodeVaild[i] = HI_FALSE;
    }
#else
    for (i = 0; i < VPSS_HAL_TASK_NODE_BUTT; i++)
    {
        pstTask->pstInstance->abNodeVaild[i] = HI_FALSE;
    }
#endif

#ifdef VPSS_SUPPORT_PROC_V2
    pstTask->pstInstance->u32LogicTimeoutCnt++;
#endif
#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
#ifdef ZME_2L_TEST
    s32Ret = VPSS_CTRL_Zme2lAndRotateCfg(enIp, pstTask);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Check ZME_2L Failed\n");
        return s32Ret;
    }
#endif
#endif

    if (VPSS_CTRL_Check2DH265InterlaceStart(pstTask))
    {
        s32Ret = VPSS_CTRL_Start2DTask_H265(enIp, pstTask);
        if (HI_SUCCESS != s32Ret)
        {
            VPSS_ERROR("Start VPSS_CTRL_Start2DTask_H265 Task Failed\n");
            return s32Ret;
        }
    }
#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3796mv200)
    else if (VPSS_CTRL_Check2DDetileStart(pstTask))
    {
        s32Ret = VPSS_CTRL_Start2DTask_First3Field(enIp, pstTask);
        if (HI_SUCCESS != s32Ret)
        {
            VPSS_ERROR("Start VPSS_CTRL_Start2DTask_First3Field Task Failed\n");
            return s32Ret;
        }
    }
#endif
    else
    {
        bStart2D = VPSS_CTRL_Check2DStart(pstTask);
        if (bStart2D)
        {
            s32Ret = VPSS_CTRL_Start2DTask(enIp, pstTask);
            if (HI_SUCCESS != s32Ret)
            {
                VPSS_ERROR("Start 2D Task Failed\n");
                return s32Ret;
            }
        }
    }
#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
#ifdef ZME_2L_TEST
    //ZME_2L
    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if ( VPSS_CTRL_CheckRotateStart(pstTask, i) )
        {
            VPSS_CTRL_StartRotateTask(enIp, pstTask, i);
        }
        else  if ( VPSS_CTRL_CheckZME1LStart(pstTask, i) )
        {
            VPSS_CTRL_StartZME2LTask(enIp, pstTask, i);
        }
        else
        {
        }
    }
#else
    //rotate
    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if (VPSS_CTRL_CheckRotateStart(pstTask, i))
        {
            VPSS_CTRL_StartRotateTask(enIp, pstTask, i);
        }
        else
        {
            //释放旋转内存，节省SDK空间占用
            if (0 != g_stVpssCtrl[enIp].stRoBuf[i].stMemBuf.u32Size)
            {
                VPSS_OSAL_FreeMem(&(g_stVpssCtrl[enIp].stRoBuf[i].stMemBuf));
                g_stVpssCtrl[enIp].stRoBuf[i].stMemBuf.u32Size = 0;
            }
        }
    }
#endif
#endif
    bStart3D = VPSS_CTRL_Check3DStart(pstTask);
    if (bStart3D)
    {
        (HI_VOID)VPSS_CTRL_Start3DTask(enIp, pstTask);
    }

#if DEF_VPSS_LOGIC_WORK
    s32Ret = VPSS_HAL_StartLogic(enIp, pstTask->pstInstance->abNodeVaild);
#else
    s32Ret = HI_SUCCESS;
#endif

#ifdef VPSS_SUPPORT_PROC_V2
    pstTask->pstInstance->aulLogicStartTime[pstTask->pstInstance->u32TimeStampIndex] = jiffies;
#endif

    return s32Ret;
}


HI_S32 VPSS_CTRL_GetRwzbData(VPSS_IP_E enIP, VPSS_TASK_S *pstTask)
{
    VPSS_INSTANCE_S *pstInstance;
    HI_U32 u32Count;
    VPSS_RWZB_S *pstRwzb;

    pstInstance = pstTask->pstInstance;
    pstRwzb = &(pstInstance->stRwzbInfo);

    for (u32Count = 0; u32Count < 6 ; u32Count ++)
    {
#ifndef VPSS_HAL_WITH_CBB
        /*pu8stt_w_vir_addr not malloc when 4K*/
        if (pstTask->stVpssHalInfo.stInInfo.u32Width <= VPSS_FHD_WIDTH)
        {
            VPSS_HAL_GetDetPixel((HI_U32 *)pstTask->stVpssHalInfo.pu8stt_w_vir_addr, u32Count, &(pstRwzb->u8RwzbData[u32Count][0]));
        }
#else
        VPSS_HAL_GetDetPixel(&(pstRwzb->u8RwzbData[u32Count][0]), &(pstTask->stVpssHalInfo.stRwzbInfo.u8Data[u32Count][0]));
#endif
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_CTRL_UpdatePqWbcData(VPSS_INSTANCE_S *pstInstance, PQ_VPSS_WBC_REG_S *pstLocalWbcReg)
{
    HI_PQ_WBC_INFO_S stPqWbcInfo;

    HI_DRV_VIDEO_FRAME_S *pstCur;

    VPSS_IN_INTF_S stInIntf;
#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798cv200_a)
    HI_U32 u32BaseRegPhyAddr;
    HI_U8 *pu8BaseRegVirAddr;
#endif
    HI_S32 s32Ret;

    if ( HI_NULL == pstLocalWbcReg)
    {
        //    VPSS_ERROR("Get pstLocalWbcReg is null!!!\n");
        return HI_FAILURE;
    }
#if 0 //when out-lowdelay is enabled, lasi statistic data has not been created util now.
    VPSS_SAFE_MEMCPY(&pstInstance->stPqWbcReg,
                     pstLocalWbcReg,
                     sizeof(PQ_VPSS_WBC_REG_S));
#endif
    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    (HI_VOID)stInIntf.pfnGetProcessImage(&pstInstance->stInEntity, &pstCur);

    stPqWbcInfo.u32Width = pstCur->u32Width;
    stPqWbcInfo.u32Height = pstCur->u32Height;
    stPqWbcInfo.bProgressive = pstCur->bProgressive;
    stPqWbcInfo.u32HandleNo = pstInstance->ID ;
    stPqWbcInfo.pstVPSSWbcReg = &pstInstance->stPqWbcReg;
    stPqWbcInfo.stOriCoordinate.s32X = 0;
    stPqWbcInfo.stOriCoordinate.s32Y = 0;
    stPqWbcInfo.stOriCoordinate.s32Width = 0;
    stPqWbcInfo.stOriCoordinate.s32Height = 0;
    stPqWbcInfo.stCropCoordinate = stPqWbcInfo.stOriCoordinate;
#ifdef VPSS_SUPPORT_ALG_MCNR
    if (VPSS_ALG_IS_MCNR_ENABLE(pstCur->u32Width, pstCur->u32Height))
    {
        stPqWbcInfo.bMcnrEnableFlag = HI_TRUE;
    }
    else
    {
        stPqWbcInfo.bMcnrEnableFlag = HI_FALSE;
    }

    if ((pstInstance->stRwzbInfo.stDetInfo.isRWZB > 0)
        || VPSS_NOT_SUPPORT_MCNR_FMT(pstCur->ePixFormat))
    {
        stPqWbcInfo.bMcnrEnableFlag = HI_FALSE;
    }
#endif
    if (pstCur->bProgressive == HI_FALSE)
    {
        VPSS_ST_RGME_CFG_S stStRgmeCfg;
        stInIntf.pfnGetInfo(&(pstInstance->stInEntity), VPSS_IN_INFO_RGME, HI_DRV_BUF_ADDR_LEFT, &stStRgmeCfg);

        stPqWbcInfo.pRGMV = (HI_VOID *)(stStRgmeCfg.pu8Nx2WriteAddr);

        stPqWbcInfo.stride = stStRgmeCfg.u32Stride;
        stPqWbcInfo.u32DeiEnFlag = HI_TRUE;
    }
    else
    {
#ifdef VPSS_SUPPORT_ALG_MCNR
        //逐行 mctnr 开的时候，也要配置 pRGMV
        if (HI_TRUE == stPqWbcInfo.bMcnrEnableFlag)
        {
            VPSS_ST_RGME_CFG_S stStRgmeCfg;
            stInIntf.pfnGetInfo(&(pstInstance->stInEntity), VPSS_IN_INFO_RGME, HI_DRV_BUF_ADDR_LEFT, &stStRgmeCfg);
            stPqWbcInfo.pRGMV = (HI_VOID *)(stStRgmeCfg.pu8Nx2WriteAddr);
            stPqWbcInfo.stride = stStRgmeCfg.u32Stride;
        }
        else
        {
            stPqWbcInfo.pRGMV = HI_NULL;
            stPqWbcInfo.stride = 0;
        }
#endif
        stPqWbcInfo.u32DeiEnFlag = HI_FALSE;
    }

    {
        HI_DRV_VIDEO_PRIVATE_S *pstPriv;
        HI_DRV_DNR_INFO_S *pstDnrInfo;

        pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstCur->u32Priv;
        pstDnrInfo = &pstPriv->stDNRInfo;
        stPqWbcInfo.bCropBeforeDB = HI_FALSE;
        stPqWbcInfo.u32SingleModeFlag = 1;
        stPqWbcInfo.u32Protocol = 1;
        stPqWbcInfo.u32ImageAvgQP = pstDnrInfo->u32ImageAvgQP;
        stPqWbcInfo.u32VdhInfoAddr = pstDnrInfo->u32VdhInfoAddr;
        stPqWbcInfo.u32VdhInfoStride = pstDnrInfo->u32VdhInfoStride;
        stPqWbcInfo.u32ImageStruct = 0; //pstDnrInfo->u32Size;
    }
#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798cv200_a)
    (HI_VOID)VPSS_HAL_GetBaseRegAddr(VPSS_IP_0,
                                     &u32BaseRegPhyAddr,
                                     &pu8BaseRegVirAddr);
#endif

    DRV_PQ_GetWbcInfo(&stPqWbcInfo);

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_StorePrivData(VPSS_BUFFER_S *pstVpssBuf, HI_DRV_VIDEO_FRAME_S *pstPrivFrmData)
{
    HI_DRV_VIDEO_FRAME_S *pstPrivFrame;
    VPSS_MEM_S *pstPrivDataBuf;

#ifdef HI_VPSS_SMMU_SUPPORT
#else
    HI_S32 s32Ret;
    MMZ_BUFFER_S stMMZBuf;
#endif

    pstPrivDataBuf = &(pstVpssBuf->stPrivDataBuf);

#ifdef HI_VPSS_SMMU_SUPPORT
    pstPrivFrame = (HI_DRV_VIDEO_FRAME_S *)pstPrivDataBuf->pu8StartVirAddr;
    if (HI_NULL != pstPrivFrame)
    {
        VPSS_SAFE_MEMCPY(pstPrivFrame, pstPrivFrmData, sizeof(HI_DRV_VIDEO_FRAME_S));
    }
#else
    stMMZBuf.u32StartPhyAddr = pstPrivDataBuf->u32StartPhyAddr;
    stMMZBuf.u32Size = pstPrivDataBuf->u32Size;
    s32Ret = HI_DRV_MMZ_Map(&stMMZBuf);
    if (HI_SUCCESS == s32Ret)
    {
        pstPrivFrame = (HI_DRV_VIDEO_FRAME_S *)stMMZBuf.pu8StartVirAddr;

        VPSS_SAFE_MEMCPY(pstPrivFrame, pstPrivFrmData, sizeof(HI_DRV_VIDEO_FRAME_S));
    }
    else
    {
        VPSS_ERROR("Get PrivDataBuf Failed,PhyAddr=%#x\n",
                   pstPrivDataBuf->u32StartPhyAddr);
    }
#endif

    return HI_SUCCESS;
}



HI_S32 VPSS_CTRL_CompleteTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_INSTANCE_S *pstInstance;

    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret = HI_FAILURE;

    pstInstance = pstTask->pstInstance;

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulThreadWakeUpAll[pstInstance->u32TimeStampIndex] = jiffies;
    VPSS_HAL_GetSystemTickCounter(enIp,
                                  &(pstInstance->u32LogicTick[pstInstance->u32TimeStampIndex]),
                                  &(pstInstance->u32LogicClock));
    pstInstance->u32LogicTimeoutCnt--;
#endif
    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    //correct src info ,because rotation change it

    /*step 0.0:get  info from pq module*/
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
#ifdef VPSS_HAL_WITH_CBB
        if ((HI_TRUE == pstPort->bEnble) && pstPort->bNeedRotate)
#else
        if ((HI_TRUE == pstPort->bEnble) &&
            ((HI_DRV_VPSS_ROTATION_90 == pstPort->enRotation)
             || (HI_DRV_VPSS_ROTATION_270 == pstPort->enRotation)))
#endif
        {
            VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);
            s32Ret = stInIntf.pfnGetProcessImage(&pstInstance->stInEntity, &pstCur);
            if (HI_SUCCESS != s32Ret)
            {
                VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
                return HI_FAILURE;
            }

            pstTask->stVpssHalInfo.stInInfo.u32Width = pstCur->u32Width;
            pstTask->stVpssHalInfo.stInInfo.u32Height = pstCur->u32Height;
            pstTask->stVpssHalInfo.stInInfo.bProgressive = pstCur->bProgressive;
            pstTask->stVpssHalInfo.stInInfo.enFieldMode = pstCur->enFieldMode;
            break;
        }
    }
#if !defined(HI_NVR_SUPPORT)
    //Get lasi statistic data here, to Ensure lasi data has been truely created(after tunnel interrupt and complete Interrupt).
    VPSS_CTRL_CopyWBCStatistic(pstTask);
    VPSS_CTRL_GetRwzbData(enIp, pstTask);
#endif


#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulPQAlgStartTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif

#if !defined(HI_NVR_SUPPORT)
#ifdef VPSS_HAL_WITH_CBB
    VPSS_CTRL_UpdatePqWbcData(pstInstance, (PQ_VPSS_WBC_REG_S *)pstTask->stVpssHalInfo.stSttAddr.pu8stt_w_vir_addr);
#else
    VPSS_CTRL_UpdatePqWbcData(pstInstance, (PQ_VPSS_WBC_REG_S *)pstTask->stVpssHalInfo.pu8stt_w_vir_addr);
#endif
#endif


#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulPQAlgEndTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif


    /*step 1.0 :release done image*/
    VPSS_INST_CompleteImage(pstInstance);

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulFinishTime[pstInstance->u32TimeStampIndex] = jiffies;
    pstInstance->u32TimeStampIndex = (pstInstance->u32TimeStampIndex + 1) % VPSS_PROC_TIMESTAMP_MAXCNT;
#endif
    return HI_SUCCESS;
}


HI_S32 VPSS_CTRL_SendOutFrame(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_INSTANCE_S *pstInstance;
    VPSS_FB_NODE_S *pstLeftFbNode;
    VPSS_FB_NODE_S *pstRightFbNode;
    HI_BOOL bDropped;
    HI_DRV_VIDEO_FRAME_S *pstTmpFrame = HI_NULL;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_DRV_VPSS_BUFFER_TYPE_E ePortType = HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE;
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret = HI_FAILURE;


    pstInstance = pstTask->pstInstance;

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulThreadWakeUpTunnel[pstInstance->u32TimeStampIndex] = jiffies;
    if (HI_FALSE == pstTask->bOutLowDelay)
    {
        pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = 0xFFFFFFFE;
    }
#endif

    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    pstTmpFrame = VPSS_VMALLOC(sizeof(HI_DRV_VIDEO_FRAME_S));
    if (HI_NULL == pstTmpFrame)
    {
        return HI_FAILURE;
    }

    /*step 2:add outframe to outPort list*/
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId == VPSS_INVALID_HANDLE)
        {
            continue;
        }
        pstLeftFbNode = pstTask->pstFrmNode[u32Count * 2];
        pstRightFbNode = pstTask->pstFrmNode[u32Count * 2 + 1];

        bDropped = HI_FALSE;
        if (pstLeftFbNode != HI_NULL || pstRightFbNode != HI_NULL)
        {
            //Drop 2first frame for interlace stream
            if (HI_FALSE == pstInstance->stInEntity.stStreamInfo.u32StreamProg)
            {
                if ((2 == pstInstance->stInEntity.stWbcInfo[0].u32CompleteCount)
                    || (3 == pstInstance->stInEntity.stWbcInfo[0].u32CompleteCount))
                {
                    bDropped = HI_TRUE;
                }
            }
        }

        if (pstLeftFbNode != HI_NULL )
        {
            VPSS_SAFE_MEMCPY(pstTmpFrame,
                             &(pstLeftFbNode->stOutFrame),
                             sizeof(HI_DRV_VIDEO_FRAME_S));

#if 0
#ifdef VPSS_SUPPORT_OUT_TUNNEL
            (HI_VOID)HI_DRV_SYS_GetTimeStampMs(&(pstLeftFbNode->stOutFrame.stLowdelayStat.u32VPSS_OUT));

            if (pstLeftFbNode->stOutFrame.stLowdelayStat.u32VPSS_IN + 20 <
                pstLeftFbNode->stOutFrame.stLowdelayStat.u32VPSS_OUT)
            {
                VPSS_FATAL("time: %d !!!!!!!!!!!!\n",
                           (pstLeftFbNode->stOutFrame.stLowdelayStat.u32VPSS_OUT -
                            pstLeftFbNode->stOutFrame.stLowdelayStat.u32VPSS_IN));
            }
            else
            {
                VPSS_FATAL("time: %d\n",
                           (pstLeftFbNode->stOutFrame.stLowdelayStat.u32VPSS_OUT -
                            pstLeftFbNode->stOutFrame.stLowdelayStat.u32VPSS_IN));
            }
#endif
#endif
            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                /*Revise the Port Type to HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE
                    *in order to decide whether report newframe
                    */
                ePortType = HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE;

                if (pstInstance->bStorePrivData)
                {
#ifdef VPSS_SUPPORT_OUT_TUNNEL
                    memset(&(pstLeftFbNode->stOutFrame.stLowdelayStat), 0x0, sizeof(HI_DRV_LOWDELAY_STAT_INFO_S));
                    // record report done time for overlay lowdelay
                    (HI_VOID)HI_DRV_SYS_GetTimeStampMs(&(pstLeftFbNode->stOutFrame.stLowdelayStat.u32OmxReportDoneTime));
#endif
                    (HI_VOID)VPSS_CTRL_StorePrivData(&(pstLeftFbNode->stBuffer),
                                                     &(pstLeftFbNode->stOutFrame));
                }

                if (HI_FALSE == bDropped)
                {
                    if (u32Count == 0)
                    {
                        HI_LD_Event_S evt;
                        HI_U32 TmpTime = 0;
                        HI_DRV_SYS_GetTimeStampMs(&TmpTime);
                        evt.evt_id = EVENT_VPSS_FRM_OUT;
                        evt.frame = pstLeftFbNode->stOutFrame.u32FrameIndex;
                        evt.handle = pstLeftFbNode->stOutFrame.hTunnelSrc;
                        evt.time = TmpTime;
                        HI_DRV_LD_Notify_Event(&evt);
                    }

                    VPSS_INST_ReportNewFrm(pstTask->pstInstance,
                                           pstPort->s32PortId,
                                           &(pstLeftFbNode->stOutFrame));
                }
                else
                {
                    VPSS_INST_RelFrmBuffer(pstTask->pstInstance, pstPort->s32PortId,
                                           &(pstPort->stFrmInfo.stBufListCfg),
                                           &(pstLeftFbNode->stBuffer.stMemBuf));
                }


                memset(&(pstTask->pstFrmNode[u32Count]->stBuffer), 0x0,
                       sizeof(pstTask->pstFrmNode[u32Count]->stBuffer));

                VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                       pstTask->pstFrmNode[u32Count],
                                       VPSS_FB_TYPE_NORMAL);
            }
            else
            {
                if (HI_FALSE == bDropped)
                {
                    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstLeftFbNode->stOutFrame.u32Priv[0]);
                    pstPriv->u32FrmCnt = pstPort->u32OutCount;
                    if ((pstInstance->stInEntity.stStreamInfo.u32InRate > pstPort->u32MaxFrameRate)
                        && (pstPort->u32MaxFrameRate != 0))
                    {
                        pstLeftFbNode->stOutFrame.u32FrameRate
                            = pstInstance->stInEntity.stStreamInfo.u32InRate / 2 * 1000;
                    }

                    if (u32Count == 0)
                    {
                        HI_LD_Event_S evt;
                        HI_U32 TmpTime = 0;
                        HI_DRV_SYS_GetTimeStampMs(&TmpTime);
                        evt.evt_id = EVENT_VPSS_FRM_OUT;
                        evt.frame = pstLeftFbNode->stOutFrame.u32FrameIndex;
                        evt.handle = pstLeftFbNode->stOutFrame.hTunnelSrc;
                        evt.time = TmpTime;
                        HI_DRV_LD_Notify_Event(&evt);
                    }
                    VPSS_FB_AddFulFrmBuf(&(pstPort->stFrmInfo), pstLeftFbNode);
                }
                else
                {

                    VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                           pstLeftFbNode,
                                           VPSS_FB_TYPE_NORMAL);
                }
            }
        }

        if (pstRightFbNode != HI_NULL)
        {
            VPSS_SAFE_MEMCPY(&(pstRightFbNode->stOutFrame.stBufAddr[0]),
                             &(pstTmpFrame->stBufAddr[0]),
                             sizeof(HI_DRV_VID_FRAME_ADDR_S));
            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                if (HI_FALSE == bDropped)
                {
                    VPSS_INST_ReportNewFrm(pstTask->pstInstance,
                                           pstPort->s32PortId,
                                           &(pstRightFbNode->stOutFrame));
                }
                else
                {
                    VPSS_INST_RelFrmBuffer(pstTask->pstInstance, pstPort->s32PortId,
                                           &(pstPort->stFrmInfo.stBufListCfg),
                                           &(pstRightFbNode->stBuffer.stMemBuf));
                }

                VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                       pstTask->pstFrmNode[u32Count],
                                       VPSS_FB_TYPE_NORMAL);
            }
            else
            {

                if (HI_FALSE == bDropped)
                {
                    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstRightFbNode->stOutFrame.u32Priv[0]);
                    pstPriv->u32FrmCnt = pstPort->u32OutCount;
                    VPSS_FB_AddFulFrmBuf(&(pstPort->stFrmInfo), pstRightFbNode);
                }
                else
                {
                    VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                           pstRightFbNode,
                                           VPSS_FB_TYPE_NORMAL);
                }
            }
        }
    }
    if (ePortType == HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE)
    {
        if (pstInstance->pfUserCallBack != HI_NULL)
        {
            pstInstance->pfUserCallBack(pstInstance->hDst, VPSS_EVENT_NEW_FRAME, HI_NULL);
        }
        else
        {
            VPSS_FATAL("Can't report VPSS_EVENT_NEW_FRAME,pfUserCallBack is NULL");
        }

        VPSS_INST_ReportCompleteEvent(pstInstance);
    }

    VPSS_VFREE(pstTmpFrame);

    return HI_SUCCESS;
}



HI_S32 VPSS_CTRL_ClearTask(VPSS_IP_E enIp, VPSS_TASK_S *pstTask)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_FB_NODE_S *pstFbNode;
    VPSS_IN_INTF_S stInIntf;
    VPSS_INSTANCE_S *pstInst;

    HI_S32 s32Ret = HI_FAILURE;

    pstInst = pstTask->pstInstance;

#ifdef VPSS_SUPPORT_PROC_V2
    pstInst->aulTunnelOutTime[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->aulLogicEndTime[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->aulThreadWakeUpTunnel[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->aulThreadWakeUpAll[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->aulPQAlgStartTime[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->aulPQAlgEndTime[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->aulFinishTime[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->u32LogicTick[pstInst->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInst->u32TimeStampIndex = (pstInst->u32TimeStampIndex + 1) % VPSS_PROC_TIMESTAMP_MAXCNT;
#endif

    s32Ret = VPSS_IN_GetIntf(&(pstInst->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    //step1:release src buffer
    s32Ret = stInIntf.pfnCompleteImage(&(pstInst->stInEntity));
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("pfnCompleteImage failed!\n");
        return HI_FAILURE;
    }

    //step2:release port buffer
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &((pstTask->pstInstance)->stPort[u32Count]);
        pstFbNode = pstTask->pstFrmNode[u32Count * 2];
        if (pstFbNode != HI_NULL)
        {
            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                VPSS_INST_RelFrmBuffer(pstTask->pstInstance, pstPort->s32PortId,
                                       &(pstPort->stFrmInfo.stBufListCfg),
                                       &(pstTask->pstFrmNode[u32Count]->stBuffer.stMemBuf));
            }
            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                   pstFbNode,
                                   VPSS_FB_TYPE_NORMAL);
        }

        pstFbNode = pstTask->pstFrmNode[u32Count * 2 + 1];
        if (pstFbNode != HI_NULL)
        {

            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                VPSS_INST_RelFrmBuffer(pstTask->pstInstance, pstPort->s32PortId,
                                       &(pstPort->stFrmInfo.stBufListCfg),
                                       &(pstTask->pstFrmNode[u32Count]->stBuffer.stMemBuf));
            }
            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                   pstFbNode,
                                   VPSS_FB_TYPE_NORMAL);
        }
    }

#ifndef VPSS_HAL_WITH_CBB
    //step3:reset vpss logic
    VPSS_REG_ReSetCRG(pstTask->pstInstance->CtrlID);
#endif
    return HI_SUCCESS;

}

HI_S32 VPSS_CTRL_ThreadProc(HI_VOID *pArg)
{
    VPSS_IP_E enIp;
    HI_S32 s32CreateRet   = HI_FAILURE;
    HI_S32 s32StartRet    = HI_FAILURE;
    HI_S32 s32WaitRet     = HI_FAILURE;
    HI_BOOL bResetEveryFrame = HI_TRUE;
    HI_U32 u32NowTime = 0;
    VPSS_CTRL_S *pstVpssCtrl = HI_NULL;

    enIp = (VPSS_IP_E)pArg;
    pstVpssCtrl = &(g_stVpssCtrl[enIp]);

    pstVpssCtrl->s32ThreadPos = 0;

    VPSS_OSAL_InitEvent(&(pstVpssCtrl->stTaskNext), EVENT_UNDO, EVENT_UNDO);
    VPSS_OSAL_InitEvent(&(pstVpssCtrl->stNewTask), EVENT_UNDO, EVENT_UNDO);
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    VPSS_OSAL_InitEvent(&(pstVpssCtrl->stTaskLowDelay), EVENT_UNDO, EVENT_UNDO);
#endif
    pstVpssCtrl->stTask.u32LastTotal = 0;
    pstVpssCtrl->stTask.u32SuccessTotal = 0;
    pstVpssCtrl->stTask.u32Create = 0;
    pstVpssCtrl->stTask.u32Fail = 0;
    pstVpssCtrl->stTask.u32TimeOut = 0;

    while (!kthread_should_stop())
    {
        HI_S32 s32Ret = HI_FAILURE;
        pstVpssCtrl->stTask.stState = TASK_STATE_READY;

        if (pstVpssCtrl->u32ThreadSleep == 1)
        {
            goto VpssThreadIdle;
        }

        pstVpssCtrl->s32ThreadPos = 1;

        pstVpssCtrl->stTask.u32Create++;

        s32CreateRet =  VPSS_CTRL_CreateTask(enIp, &(pstVpssCtrl->stTask));
        /* create success  running -> waitting */
        if (s32CreateRet == HI_SUCCESS)
        {
            VPSS_INFO("...............CreateTask\n");
            pstVpssCtrl->s32ThreadPos = 2;
            /* pstInstance is not null when creat success */
            bResetEveryFrame = pstVpssCtrl->stTask.pstInstance->stDbgCtrl.stInstDbg.bResetPerFrame;
            VPSS_HAL_SetClockEn(enIp, HI_TRUE);
#ifdef VPSS_SUPPORT_OUT_TUNNEL
            if (VPSS_CTRL_CheckLowDelay(enIp, &(pstVpssCtrl->stTask)))
            {
                pstVpssCtrl->stTask.bOutLowDelay = HI_TRUE;
            }
            else
            {
                pstVpssCtrl->stTask.bOutLowDelay = HI_FALSE;
            }
            VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stTaskLowDelay), EVENT_UNDO, EVENT_UNDO);
#endif
            VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stTaskNext), EVENT_UNDO, EVENT_UNDO);

            s32StartRet = VPSS_CTRL_StartTask(enIp, &(pstVpssCtrl->stTask));
            if (s32StartRet == HI_SUCCESS)
            {
                VPSS_INFO("...............StartTask\n");
                /*
                   start logic running, waitting for irq to wakeup thread
                   */
                pstVpssCtrl->stTask.stState = TASK_STATE_WAIT;
#if DEF_VPSS_LOGIC_WORK
#ifdef VPSS_SUPPORT_OUT_TUNNEL
                if (pstVpssCtrl->stTask.bOutLowDelay)
                {
                    s32WaitRet = VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stTaskLowDelay), HZ);
                }
                else
                {
                    s32WaitRet = VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stTaskNext), HZ);
                }
#else
                s32WaitRet = VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stTaskNext), HZ);
#endif
#else
                msleep(10);
                s32WaitRet = HI_SUCCESS;
#endif
                if (s32WaitRet == HI_SUCCESS)
                {
                    pstVpssCtrl->s32ThreadPos = 3;
                    VPSS_CTRL_SendOutFrame(enIp, &(pstVpssCtrl->stTask));

                    if (jiffies - u32NowTime >= HZ)
                    {
                        u32NowTime = jiffies;
                        pstVpssCtrl->stTask.u32SucRate = pstVpssCtrl->stTask.u32SuccessTotal
                                                         - pstVpssCtrl->stTask.u32LastTotal;
                        pstVpssCtrl->stTask.u32LastTotal = pstVpssCtrl->stTask.u32SuccessTotal;
                    }

                    pstVpssCtrl->stTask.u32SuccessTotal ++;
#ifdef VPSS_SUPPORT_OUT_TUNNEL
                    if (pstVpssCtrl->stTask.bOutLowDelay)
                    {
                        s32WaitRet = VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stTaskNext), HZ);
                        if (s32WaitRet != HI_SUCCESS)
                        {
                            VPSS_FATAL("...............Wait LowDelay Faild\n");
                        }
                    }
#endif
                    VPSS_CTRL_CompleteTask(enIp, &(pstVpssCtrl->stTask));
                }
                else
                {
                    VPSS_FATAL("...............Wait OutTime Faild\n");
                    pstVpssCtrl->s32ThreadPos = 4;
                    pstVpssCtrl->stTask.u32TimeOut++;
#ifdef VPSS_HAL_WITH_CBB
                    VPSS_HAL_DumpReg(enIp, VPSS_HAL_NODE_2D_FRAME, HI_TRUE);
#else
                    VPSS_HAL_DumpReg(enIp, VPSS_HAL_TASK_NODE_2D);
#endif
                    VPSS_CTRL_ClearTask(enIp, &(pstVpssCtrl->stTask));

                    if (HI_TRUE == bResetEveryFrame)
                    {
                        VPSS_HAL_SetClockEn(enIp, HI_FALSE);
                    }
                }
            }
            else
            {
                /* 创建Task成功之后，start必须成功 */
                VPSS_FATAL("...............StartTask Faild\n");

                VPSS_CTRL_ClearTask(enIp, &(pstVpssCtrl->stTask));

                goto  VpssThreadIdle;
            }
        }
        else/*create failed or start failed running -> idle*/
        {
            pstVpssCtrl->stTask.u32Fail++;

        VpssThreadIdle:
            pstVpssCtrl->s32ThreadPos = 5;
            pstVpssCtrl->stTask.stState = TASK_STATE_IDLE;
            if (HI_TRUE == bResetEveryFrame)
            {
                VPSS_HAL_SetClockEn(enIp, HI_FALSE);
            }
            s32Ret = VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stNewTask), HZ / 100);
            if (s32Ret == HI_SUCCESS)
            {
                VPSS_INFO("WakeUpThread Success.\n");
            }

            VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stNewTask), EVENT_UNDO, EVENT_UNDO);
#ifdef ZME_2L_TEST
            /*当上层出现stop操作时，释放缓存的buffer*/
            if ( HI_NULL != pstVpssCtrl->stTask.pstFrmNodeZME1L)
            {
                //释放旋转内存，节省SDK空间占用
                if (0 != pstVpssCtrl->stTask.pstFrmNodeZME1L->stBuffer.stMemBuf.u32Size)
                {
                    VPSS_OSAL_FreeMem(&(pstVpssCtrl->stTask.pstFrmNodeZME1L->stBuffer.stMemBuf));
                    pstVpssCtrl->stTask.pstFrmNodeZME1L->stBuffer.stMemBuf.u32Size = 0;
                    pstVpssCtrl->stTask.pstFrmNodeZME1L->stBuffer.u32Stride = 0;

                    VPSS_VFREE(pstVpssCtrl->stTask.pstFrmNodeZME1L);
                    pstVpssCtrl->stTask.pstFrmNodeZME1L = HI_NULL;
                }
            }
#endif
        }

    }

    pstVpssCtrl->s32ThreadPos = 6;

    VPSS_INFO("s32ThreadPos = %d...\n", pstVpssCtrl->s32ThreadPos);

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_CreateThread(VPSS_IP_E enIp)
{
    struct sched_param param;

    g_stVpssCtrl[enIp].u32ThreadKilled = 0;
    g_stVpssCtrl[enIp].u32ThreadSleep = 0;
    g_stVpssCtrl[enIp].hThread =
        kthread_create(VPSS_CTRL_ThreadProc, (HI_VOID *)enIp, "HI_VPSS_Process");

    if ( IS_ERR(g_stVpssCtrl[enIp].hThread) )
    {
        VPSS_FATAL("Can not create thread.\n");
        return HI_FAILURE;
    }


    param.sched_priority = 99;
    sched_setscheduler(g_stVpssCtrl[enIp].hThread, SCHED_RR, &param);

#ifndef HI_TEE_SUPPORT
    //kthread_bind(g_stVpssCtrl[enIp].hThread, 3);
    //kthread_bind(g_stVpssCtrl[enIp].hThread, 0);
#endif


#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
#ifdef HI_FPGA_SUPPORT
    /* TO avoid VPSS's reg r/w operation collision with VDH. (they are both on FPGA4) */
    if (num_online_cpus() > 2)
    {
        if (cpu_online(VPSS_CPU_INDEX))
        {
            kthread_bind(g_stVpssCtrl[enIp].hThread, VPSS_CPU_INDEX);

            //VPSS_FATAL("bind vpss thread to cpu %d!\n", VPSS_CPU_INDEX);
        }
        else
        {
            VPSS_FATAL("kthread_bind fail, cpu %d is not online!\n", VPSS_CPU_INDEX);
        }
    }
#endif
#endif
    wake_up_process(g_stVpssCtrl[enIp].hThread);

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_DestoryThread(VPSS_IP_E enIp)
{
    HI_S32 s32Ret;

    s32Ret = kthread_stop(g_stVpssCtrl[enIp].hThread);

    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Destory Thread Error.\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_CreateInstProc(VPSS_HANDLE hVPSS)
{
    HI_CHAR           ProcName[20];
    DRV_PROC_ITEM_S  *pProcItem;

    HI_OSAL_Snprintf(ProcName, 20, "vpss%02x", hVPSS);

    pProcItem = HI_DRV_PROC_AddModule(ProcName, HI_NULL, HI_NULL);

    if (!pProcItem)
    {
        VPSS_FATAL("Vpss add proc failed!\n");
        return HI_FAILURE;
    }

    pProcItem->data  = (HI_VOID *)(unsigned long)hVPSS;
    pProcItem->read  = VPSS_CTRL_ProcRead;
    pProcItem->write = VPSS_CTRL_ProcWrite;

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_DestoryInstProc(VPSS_HANDLE hVPSS)
{
    HI_CHAR           ProcName[20];
    HI_OSAL_Snprintf(ProcName, 20, "vpss%02x", (HI_U32)(hVPSS));
    HI_DRV_PROC_RemoveModule(ProcName);
    return HI_SUCCESS;
}

HI_U32 VPSS_CTRL_MallocInstanceId(HI_VOID)
{
    HI_U32 i;
    HI_U32 u32InstCount;
    HI_BOOL bFindVpss;
    HI_U32 u32VpssId;
    VPSS_IP_E enVpssIp;
    unsigned long  u32LockFlag;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;

    u32InstCount = 0;

    for (u32VpssId = 0; u32VpssId < VPSS_IP_BUTT * VPSS_INSTANCE_MAX_NUMB; u32VpssId++)
    {
        bFindVpss = HI_FALSE;

        for (enVpssIp = VPSS_IP_0; enVpssIp < VPSS_IP_BUTT; enVpssIp++)
        {
            pstInstCtrlInfo = &(g_stVpssCtrl[enVpssIp].stInstCtrlInfo);
            read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
            for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
            {
                if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
                {
                    if (u32VpssId == pstInstCtrlInfo->pstInstPool[i]->ID)
                    {
                        bFindVpss = HI_TRUE;
                        u32InstCount++;
                        break;
                    }
                }
            }
            read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        }

        if (!bFindVpss)
        {
            break;
        }
    }

    if (u32InstCount == 0)
    {
        return 0;
    }
    else
    {
        return u32VpssId;
    }
}

VPSS_HANDLE VPSS_CTRL_AddInstance(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32VpssId = 0;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    HI_U32 u32Count;
    unsigned long  u32LockFlag;
    VPSS_IP_E enVpssIp;


    enVpssIp = pstInstance->CtrlID;

    if (enVpssIp >= VPSS_IP_BUTT)
    {
        VPSS_FATAL("Invalid enVpssIp:%d\n", enVpssIp);
        return VPSS_INVALID_HANDLE;
    }

    pstInstCtrlInfo = &(g_stVpssCtrl[enVpssIp].stInstCtrlInfo);
    //u32VpssId = VPSS_CTRL_MallocInstanceId();
    write_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    for (u32Count = 0; u32Count < VPSS_INSTANCE_MAX_NUMB; u32Count++)
    {
        if (pstInstCtrlInfo->pstInstPool[u32Count] == HI_NULL)
        {
            pstInstCtrlInfo->pstInstPool[u32Count] = pstInstance;
            u32VpssId = u32Count;
            break;
        }
    }
    write_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    if (u32Count == VPSS_INSTANCE_MAX_NUMB)
    {
        VPSS_FATAL("Instance Number is Max.\n");

        return VPSS_INVALID_HANDLE;
    }
    else
    {
        pstInstance->ID = u32VpssId;
        pstInstCtrlInfo->u32InstanceNum++;
        return pstInstance->ID;
    }
}

HI_S32 VPSS_CTRL_DelInstance(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 i;
    VPSS_IP_E enVpssIP;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    unsigned long  u32LockFlag;

    VPSS_CHECK_NULL(pstInstance);

    enVpssIP = pstInstance->CtrlID;
    pstInstCtrlInfo = &(g_stVpssCtrl[enVpssIP].stInstCtrlInfo);

    write_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
    for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
    {
        if (pstInstCtrlInfo->pstInstPool[i] == pstInstance)
        {
            pstInstCtrlInfo->pstInstPool[i] = HI_NULL;
            break;
        }
    }
    write_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    return HI_SUCCESS;
}



HI_S32 VPSS_CTRL_Init(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 i, j;

    g_stVpssCtrl[0].bIPVaild = HI_TRUE;
    g_stVpssCtrl[1].bIPVaild = HI_FALSE;


    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        if (HI_TRUE != g_stVpssCtrl[i].bIPVaild)
        {
            continue;
        }

        if (0 == g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            s32Ret = VPSS_CTRL_RegistISR((VPSS_IP_E)i);

            if (HI_SUCCESS != s32Ret)
            {
                goto VPSS_IP_DEL_INT;
            }

            VPSS_CTRL_InitInstList((VPSS_IP_E)i);

            s32Ret = VPSS_HAL_Init((VPSS_IP_E)i);
            if (HI_SUCCESS != s32Ret)
            {
                goto VPSS_IP_UnRegist_IRQ;
            }

            s32Ret = VPSS_CTRL_CreateThread((VPSS_IP_E)i);
            if (s32Ret != HI_SUCCESS)
            {
                VPSS_FATAL("VPSS_CTRL_CreateThread Failed\n");
                goto VPSS_IP_HAL_DEL_INIT;
            }
        }

        g_stVpssCtrl[i].s32IsVPSSOpen++;

    }

    return HI_SUCCESS;
#ifdef VPSS_HAL_WITH_CBB
VPSS_IP_HAL_DEL_INIT:
    (HI_VOID)VPSS_HAL_DeInit((VPSS_IP_E)i);
VPSS_IP_UnRegist_IRQ:
    (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)i);

VPSS_IP_DEL_INT:
    for (j = 0; j < i; j++)
    {
        if (HI_TRUE == g_stVpssCtrl[j].bIPVaild)
        {
            (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)j);
            (HI_VOID)VPSS_HAL_DeInit((VPSS_IP_E)j);
            (HI_VOID)VPSS_CTRL_DestoryThread((VPSS_IP_E)j);
        }
    }
#else

VPSS_IP_HAL_DEL_INIT:
    (HI_VOID)VPSS_HAL_DelInit((VPSS_IP_E)i);
VPSS_IP_UnRegist_IRQ:
    (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)i);

VPSS_IP_DEL_INT:
    for (j = 0; j < i; j++)
    {
        if (HI_TRUE == g_stVpssCtrl[j].bIPVaild)
        {
            (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)j);
            (HI_VOID)VPSS_HAL_DelInit((VPSS_IP_E)j);
            (HI_VOID)VPSS_CTRL_DestoryThread((VPSS_IP_E)j);
        }
    }
#endif
    return HI_FAILURE;
}

HI_S32 VPSS_CTRL_DelInit(HI_VOID)
{
    HI_U32 i;
    HI_U32 u32Count;
    VPSS_BUFFER_S *pstVpssBuf;

    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        if (HI_TRUE != g_stVpssCtrl[i].bIPVaild)
        {
            continue;
        }

        if (1 > g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            VPSS_FATAL("CTRL_DelInit Error,vpss hasn't initted.\n");
            return HI_FAILURE;
        }

        g_stVpssCtrl[i].s32IsVPSSOpen--;
        if (1 == g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            for (u32Count = 0; u32Count < VPSS_INSTANCE_MAX_NUMB; u32Count ++)
            {
                if (HI_NULL != g_stVpssCtrl[i].stInstCtrlInfo.pstInstPool[u32Count])
                {
                    VPSS_FATAL("CTRL_DelInit Error,destroy instance first.\n");
                    g_stVpssCtrl[i].s32IsVPSSOpen++;
                    return HI_FAILURE;
                }
            }
            //add for low power
            VPSS_HAL_SetClockEn(i, HI_FALSE);

            //release rotation buffer

            for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count ++)
            {
#ifdef ZME_2L_TEST
                if ( g_stVpssCtrl[i].stTask.pstFrmNodeRoBuf[u32Count] != HI_NULL)
                {
                    pstVpssBuf = &(g_stVpssCtrl[i].stTask.pstFrmNodeRoBuf[u32Count]->stBuffer);
                    if (pstVpssBuf->stMemBuf.u32Size != 0)
                    {
                        (HI_VOID)VPSS_OSAL_FreeMem(&(pstVpssBuf->stMemBuf));
                        pstVpssBuf->u32Stride = 0;
                        pstVpssBuf->stMemBuf.u32Size = 0;

                        VPSS_VFREE(g_stVpssCtrl[i].stTask.pstFrmNodeRoBuf[u32Count]);
                        g_stVpssCtrl[i].stTask.pstFrmNodeRoBuf[u32Count] = HI_NULL;
                    }

                }

                if ( g_stVpssCtrl[i].stTask.pstFrmNodeZME1L != HI_NULL)
                {
                    pstVpssBuf = &(g_stVpssCtrl[i].stTask.pstFrmNodeZME1L->stBuffer);
                    if (pstVpssBuf->stMemBuf.u32Size != 0)
                    {
                        (HI_VOID)VPSS_OSAL_FreeMem(&(pstVpssBuf->stMemBuf));
                        pstVpssBuf->u32Stride = 0;
                        pstVpssBuf->stMemBuf.u32Size = 0;

                        VPSS_VFREE(g_stVpssCtrl[i].stTask.pstFrmNodeZME1L);
                        g_stVpssCtrl[i].stTask.pstFrmNodeZME1L = HI_NULL;
                    }
                }
#else
                pstVpssBuf = &(g_stVpssCtrl[i].stRoBuf[u32Count]);
                if (pstVpssBuf->stMemBuf.u32Size != 0)
                {
                    VPSS_OSAL_FreeMem(&(pstVpssBuf->stMemBuf));
                    pstVpssBuf->u32Stride = 0;
                    pstVpssBuf->stMemBuf.u32Size = 0;
                }
#endif
            }
        }

        if (0 == g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)i);
            (HI_VOID)VPSS_CTRL_DestoryThread((VPSS_IP_E)i);
#ifdef VPSS_HAL_WITH_CBB
            (HI_VOID)VPSS_HAL_DeInit((VPSS_IP_E)i);
#else
            (HI_VOID)VPSS_HAL_DelInit((VPSS_IP_E)i);
#endif
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_SetMceFlag(HI_BOOL bInMCE)
{
    HI_U32 i;

    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        g_stVpssCtrl[i].bInMCE = bInMCE;
    }

    return HI_SUCCESS;
}

VPSS_HANDLE VPSS_CTRL_CreateInstance(HI_DRV_VPSS_CFG_S *pstVpssCfg)
{
    HI_S32 s32Ret;
    HI_S32 s32InstHandle = VPSS_INVALID_HANDLE;
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;

    s32Ret = VPSS_CTRL_GetDistributeIP(&enVpssIp);
    if ((HI_SUCCESS != s32Ret) || (enVpssIp == VPSS_IP_BUTT))
    {
        VPSS_FATAL("vpss ctrl isn't enable\n");
        return s32InstHandle;
    }

    if (1 >= g_stVpssCtrl[enVpssIp].s32IsVPSSOpen)
    {
        VPSS_FATAL("vpss ctrl isn't opened\n");
        return s32InstHandle;
    }

    pstInstance = (VPSS_INSTANCE_S *)VPSS_VMALLOC(sizeof(VPSS_INSTANCE_S));
    if (pstInstance != HI_NULL)
    {
        if (pstVpssCfg)
        {
            s32Ret = VPSS_INST_Init(pstInstance, pstVpssCfg);
        }
        else
        {
            HI_DRV_VPSS_CFG_S stDefCfg;
            VPSS_INST_GetDefInstCfg(&stDefCfg);
            s32Ret = VPSS_INST_Init(pstInstance, &stDefCfg);
        }
        if (HI_SUCCESS != s32Ret)
        {
            VPSS_VFREE(pstInstance);
            return s32InstHandle;
        }

        pstInstance->CtrlID = enVpssIp;
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->u32LogicTimeoutCnt = 0;
#endif
        s32InstHandle = VPSS_CTRL_AddInstance(pstInstance);
        if (s32InstHandle != VPSS_INVALID_HANDLE)
        {
            if (g_stVpssCtrl[enVpssIp].bInMCE == HI_FALSE)
            {
                (HI_VOID)VPSS_CTRL_CreateInstProc(pstInstance->ID);
            }
        }
        else
        {
            VPSS_VFREE(pstInstance);
        }

        return s32InstHandle;
    }
    else
    {
        VPSS_FATAL("vmalloc instance node failed \n");
        return s32InstHandle;
    }

}

HI_S32 VPSS_CTRL_DestoryInstance(VPSS_HANDLE hVPSS)
{
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);
    if (pstInstance == HI_NULL)
    {
        VPSS_FATAL("hVPSS(%d) is Not be Vaild Or Created\n", hVPSS);
        return HI_FAILURE;
    }

    if (pstInstance->enState != INSTANCE_STATE_STOP)
    {
        VPSS_FATAL("Instance %#x is still working, please stop first\n");
        return HI_FAILURE;
    }

    /*
      *  when deletting instance
      *  must get lock first to ensure that it isn't being served
     */
    enVpssIp = pstInstance->CtrlID;
    g_stVpssCtrl[enVpssIp].u32ThreadSleep = 1;

    while (g_stVpssCtrl[enVpssIp].s32ThreadPos != 5)
    {
        msleep(10);
    }

    if (g_stVpssCtrl[enVpssIp].bInMCE == HI_FALSE)
    {
        VPSS_CTRL_DestoryInstProc(hVPSS);
    }

    g_stVpssCtrl[enVpssIp].stInstCtrlInfo.u32InstanceNum--;
    VPSS_HAL_H265RefListDeInit(&pstInstance->stH265RefList);
    VPSS_CTRL_DelInstance(pstInstance);
    (HI_VOID)VPSS_INST_DelInit(pstInstance);
    VPSS_VFREE(pstInstance);

    g_stVpssCtrl[enVpssIp].u32ThreadSleep = 0;
    return HI_SUCCESS;

}
HI_S32 VPSS_CTRL_GetInstanceNumber(VPSS_IP_E enIp, HI_U32 *pu32Number)
{
    HI_U32 i;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    unsigned long u32LockFlag;
    HI_U32 u32Cnt = 0;

    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);
    read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
    for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
    {
        if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
        {
            u32Cnt ++;
        }
    }
    read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    *pu32Number = u32Cnt;

    return HI_SUCCESS;
}

VPSS_INSTANCE_S *VPSS_CTRL_GetOnlyInstance(VPSS_IP_E enIp)
{
    HI_U32 u32InstNumber;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    VPSS_INSTANCE_S *pstRetPtr = HI_NULL;
    unsigned long u32LockFlag;
    HI_U32 i;

    VPSS_CTRL_GetInstanceNumber(VPSS_IP_0, &u32InstNumber);

    if (u32InstNumber != 1)
    {
        return HI_NULL;
    }

    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);

    read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
    {
        if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
        {
            pstRetPtr = pstInstCtrlInfo->pstInstPool[i];
        }
    }

    read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    return pstRetPtr;
}

VPSS_INSTANCE_S *VPSS_CTRL_GetInstance(VPSS_HANDLE hVPSS)
{
    HI_U32 i;
    HI_U32 u32IpPos;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    VPSS_INSTANCE_S *pstRetPtr = HI_NULL;
    unsigned long u32LockFlag;


    if ((hVPSS < 0) || (hVPSS >= VPSS_INSTANCE_MAX_NUMB * VPSS_IP_BUTT))
    {
        VPSS_FATAL("Invalid VPSS HANDLE %x.\n", hVPSS);
        return HI_NULL;
    }

    for (u32IpPos = VPSS_IP_0; u32IpPos < VPSS_IP_BUTT; u32IpPos++)
    {
        pstInstCtrlInfo = &(g_stVpssCtrl[u32IpPos].stInstCtrlInfo);
        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
            {
                if (hVPSS == pstInstCtrlInfo->pstInstPool[i]->ID)
                {
                    pstRetPtr = pstInstCtrlInfo->pstInstPool[i];
                    break;
                }
            }
        }
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    }

    return pstRetPtr;
}

HI_S32 VPSS_CTRL_WakeUpThread(HI_VOID)
{
    if (g_stVpssCtrl[VPSS_IP_0].s32IsVPSSOpen >= 1)
    {
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stNewTask), 1, 0);
    }

    if (g_stVpssCtrl[VPSS_IP_1].s32IsVPSSOpen >= 1)
    {
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stNewTask), 1, 0);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_Pause(VPSS_HANDLE hVPSS)
{
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;
    HI_U32 u32SleepNumb = 0;

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);

    VPSS_CHECK_NULL(pstInstance);

    enVpssIp = pstInstance->CtrlID;

    g_stVpssCtrl[enVpssIp].u32ThreadSleep = 1;

    while (g_stVpssCtrl[enVpssIp].s32ThreadPos != 5 && u32SleepNumb < 200)
    {
        msleep(10);

        u32SleepNumb ++;
    }

    if (u32SleepNumb >= 200)
    {
        VPSS_ERROR("thread sleep failed pos %d\n", g_stVpssCtrl[enVpssIp].s32ThreadPos);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_Resume(VPSS_HANDLE hVPSS)
{
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);

    VPSS_CHECK_NULL(pstInstance);

    enVpssIp = pstInstance->CtrlID;

    g_stVpssCtrl[enVpssIp].u32ThreadSleep = 0;

    VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[enVpssIp].stNewTask), 1, 0);

    return HI_SUCCESS;
}
#ifndef VPSS_HAL_WITH_CBB
irqreturn_t VPSS0_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_U32 u32State = 0;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INSTANCE_S *pstInstance = g_stVpssCtrl[VPSS_IP_0].stTask.pstInstance;
#endif

    (HI_VOID)VPSS_HAL_GetIntState(VPSS_IP_0, &u32State);

    if (u32State & 0x20)
    {
        VPSS_FATAL("IRQ DCMP ERR    state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x20);
    }

    if (u32State & 0x4)
    {
        VPSS_FATAL("IRQ BUS ERR  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x4);
    }

    if (u32State & 0x2)
    {
        VPSS_FATAL("TIMEOUT  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x2);
    }

    if (u32State & 0x60) //   0xf ---> 0xff open tunl mask and dcmp err mask
    {
        VPSS_FATAL(" Tunnel = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x60);
    }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (u32State & 0x10)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x10);
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stTaskLowDelay), EVENT_DONE, EVENT_UNDO);
    }
#endif
    if (u32State & 0x1)
    {
        //VPSS_FATAL("NODE  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x1);
    }

    if (u32State & 0x88)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x88);
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stTaskNext), EVENT_DONE, EVENT_UNDO);
    }
    return IRQ_HANDLED;
}

irqreturn_t VPSS1_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_U32 u32State = 0;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INSTANCE_S *pstInstance = g_stVpssCtrl[VPSS_IP_0].stTask.pstInstance;
#endif

    (HI_VOID)VPSS_HAL_GetIntState(VPSS_IP_1, &u32State);

    if (u32State & 0x20)
    {
        VPSS_FATAL("IRQ DCMP ERR    state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x20);
    }

    if (u32State & 0x4)
    {
        VPSS_FATAL("IRQ BUS ERR  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x4);
    }

    if (u32State & 0x2)
    {
        VPSS_FATAL("TIMEOUT  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x2);
    }

    if (u32State & 0x60) //   0xf ---> 0xff open tunl mask and dcmp err mask
    {
        VPSS_FATAL(" Tunnel = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x70);
    }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (u32State & 0x10)
    {
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stTaskLowDelay), EVENT_DONE, EVENT_UNDO);
    }
#endif

    if (u32State & 0x1)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x1);
    }

    if (u32State & 0x8)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x8);
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stTaskNext), EVENT_DONE, EVENT_UNDO);
    }

    return IRQ_HANDLED;
}
#else  //98mv200
irqreturn_t VPSS0_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_BOOL abISRStat[CBB_ISR_BUTT] = {0};
    HI_BOOL abISRStatMask[CBB_ISR_BUTT] = {0};
    CBB_REG_ADDR_S stRegAddr = {0};
    HI_U32 u32IntState;
    HI_U32 u32IntStateSMMU;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INSTANCE_S *pstInstance = g_stVpssCtrl[VPSS_IP_0].stTask.pstInstance;
#endif
    stRegAddr.pu8BaseVirAddr = stHalCtx[VPSS_IP_0].pu8BaseRegVir;
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_GET_ISR_STAT, abISRStat, HI_NULL);

    VPSS_SAFE_MEMCPY(abISRStatMask, abISRStat, sizeof(abISRStatMask));
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_CLR_ISR_STAT, abISRStatMask, HI_NULL);

    u32IntState = ((abISRStat[CBB_ISR_NODE_COMPLETE]    << CBB_ISR_NODE_COMPLETE)
                   | (abISRStat[CBB_ISR_LIST_COMPLETE] << CBB_ISR_LIST_COMPLETE)
                   | (abISRStat[CBB_ISR_BUS_READ_ERR]  << CBB_ISR_BUS_READ_ERR )
                   | (abISRStat[CBB_ISR_BUS_WRITE_ERR] << CBB_ISR_BUS_WRITE_ERR)
                   | (abISRStat[CBB_ISR_DCMP_ERR]      << CBB_ISR_DCMP_ERR     )
                   | (abISRStat[CBB_ISR_VHD0_TUNNEL]   << CBB_ISR_VHD0_TUNNEL )
                  );

    //VPSS_FATAL("VPSS IP0 int (0x%X) ...\n", u32IntState);

    if (abISRStat[CBB_ISR_SMMU_S_TLBMISS] || abISRStat[CBB_ISR_SMMU_S_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_S_TLBMISS] << (CBB_ISR_SMMU_S_TLBMISS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_PTW_TRANS] << (CBB_ISR_SMMU_S_PTW_TRANS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] << (CBB_ISR_SMMU_S_TLBINVALID_RD - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR] << (CBB_ISR_SMMU_S_TLBINVALID_WR - CBB_ISR_SMMU_S_MIN));

        VPSS_FATAL("IRQ SMMU-S ERR state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] || abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] << (CBB_ISR_SMMU_NS_TLBMISS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS] << (CBB_ISR_SMMU_NS_PTW_TRANS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] << (CBB_ISR_SMMU_NS_TLBINVALID_RD - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR] << (CBB_ISR_SMMU_NS_TLBINVALID_WR - CBB_ISR_SMMU_NS_MIN));

        VPSS_FATAL("IRQ SMMU-NS ERR  state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_BUS_WRITE_ERR] || abISRStat[CBB_ISR_BUS_READ_ERR])
    {
        VPSS_FATAL("IRQ BUS W/R ERR  state = %x \n", u32IntState);
    }

    if (abISRStat[CBB_ISR_TIMEOUT])
    {
        VPSS_FATAL("IRQ TIMEOUT state = %x \n", u32IntState);
    }

    if (abISRStat[CBB_ISR_DCMP_ERR])
    {
        VPSS_FATAL("IRQ  DCMP ERR state = %x \n", u32IntState);
    }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (abISRStat[CBB_ISR_VHD0_TUNNEL])
    {
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stTaskLowDelay), EVENT_DONE, EVENT_UNDO);
    }
#endif

    if (abISRStat[CBB_ISR_LIST_COMPLETE])
    {
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stTaskNext), EVENT_DONE, EVENT_UNDO);
    }

    return IRQ_HANDLED;
}

irqreturn_t VPSS1_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_BOOL abISRStat[CBB_ISR_BUTT] = {0};
    HI_BOOL abISRStatMask[CBB_ISR_BUTT] = {0};
    CBB_REG_ADDR_S stRegAddr = {0};
    HI_U32 u32IntState;
    HI_U32 u32IntStateSMMU;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INSTANCE_S *pstInstance = g_stVpssCtrl[VPSS_IP_1].stTask.pstInstance;
#endif
    stRegAddr.pu8BaseVirAddr = stHalCtx[VPSS_IP_1].pu8BaseRegVir;
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_GET_ISR_STAT, abISRStat, HI_NULL);

    VPSS_SAFE_MEMCPY(abISRStatMask, abISRStat, sizeof(abISRStatMask));
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_CLR_ISR_STAT, abISRStatMask, HI_NULL);

    u32IntState = ((abISRStat[CBB_ISR_NODE_COMPLETE]    << CBB_ISR_NODE_COMPLETE)
                   | (abISRStat[CBB_ISR_LIST_COMPLETE] << CBB_ISR_LIST_COMPLETE)
                   | (abISRStat[CBB_ISR_BUS_READ_ERR]  << CBB_ISR_BUS_READ_ERR )
                   | (abISRStat[CBB_ISR_BUS_WRITE_ERR] << CBB_ISR_BUS_WRITE_ERR)
                   | (abISRStat[CBB_ISR_DCMP_ERR]      << CBB_ISR_DCMP_ERR     )
                   | (abISRStat[CBB_ISR_VHD0_TUNNEL]   << CBB_ISR_VHD0_TUNNEL )
                  );

    //VPSS_FATAL("VPSS IP1 int (0x%X) ...\n", u32IntState);

    if (abISRStat[CBB_ISR_SMMU_S_TLBMISS] || abISRStat[CBB_ISR_SMMU_S_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_S_TLBMISS] << (CBB_ISR_SMMU_S_TLBMISS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_PTW_TRANS] << (CBB_ISR_SMMU_S_PTW_TRANS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] << (CBB_ISR_SMMU_S_TLBINVALID_RD - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR] << (CBB_ISR_SMMU_S_TLBINVALID_WR - CBB_ISR_SMMU_S_MIN));

        VPSS_FATAL("IRQ SMMU-S ERR state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] || abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] << (CBB_ISR_SMMU_NS_TLBMISS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS] << (CBB_ISR_SMMU_NS_PTW_TRANS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] << (CBB_ISR_SMMU_NS_TLBINVALID_RD - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR] << (CBB_ISR_SMMU_NS_TLBINVALID_WR - CBB_ISR_SMMU_NS_MIN));

        VPSS_FATAL("IRQ SMMU-NS ERR  state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_BUS_WRITE_ERR])
    {
        VPSS_FATAL("IRQ BUS ERR  state = %x \n", u32IntState);
    }


    if (abISRStat[CBB_ISR_TIMEOUT])
    {
        VPSS_FATAL("TIMEOUT  state = %x \n", u32IntState);
    }


    if (abISRStat[CBB_ISR_DCMP_ERR] || abISRStat[CBB_ISR_BUS_READ_ERR])
    {
        VPSS_FATAL(" Tunnel = %x \n", u32IntState);
    }

#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (abISRStat[CBB_ISR_VHD0_TUNNEL])
    {
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stTaskLowDelay), EVENT_DONE, EVENT_UNDO);
    }
#endif

    if (abISRStat[CBB_ISR_LIST_COMPLETE])
    {
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stTaskNext), EVENT_DONE, EVENT_UNDO);
    }

    return IRQ_HANDLED;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

