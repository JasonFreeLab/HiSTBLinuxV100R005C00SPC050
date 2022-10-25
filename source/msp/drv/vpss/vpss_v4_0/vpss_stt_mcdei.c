#include "vpss_stt_mcdei.h"
#include "vpss_osal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
HI_VOID VPSS_ST_RGME_CalBufSize(HI_U32 *pSize, HI_U32 *pStride, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 u32Stride;
    HI_U32 u32Width;
    HI_U32 u32Height;

    u32Width = pstAttr->u32Width;
    u32Height = pstAttr->u32Height;

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    u32Stride = ((u32Width + 33) / 64 * 8 + 15) & 0xfffffff0;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 5) / 8;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
#else
    u32Stride = (u32Width + 33) / 64 * 16;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 5) / 8;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
#endif

}

HI_S32 VPSS_ST_RGME_Init(VPSS_ST_RGME_S *pstStRgme, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 i = 0;
    LIST *pListHead = HI_NULL;
    HI_U32 u32NodeBuffSize = 0;
    HI_U32 u32TotalBuffSize = 0;
    HI_U32 u32PhyAddr = 0;
    HI_U8 *pu8VirAddr = 0;
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pstStRgme)
    {
        VPSS_ERROR("Vpss StrgmeInit error(null pointer).\n");
        return HI_FAILURE;
    }
    if (HI_TRUE == pstStRgme->bInit)
    {
        (HI_VOID)VPSS_ST_RGME_DeInit(pstStRgme);
    }

    memset(pstStRgme, 0, sizeof(VPSS_ST_RGME_S));
    pstStRgme->u32Width = pstAttr->u32Width;
    pstStRgme->u32Height = pstAttr->u32Height;

    VPSS_ST_RGME_CalBufSize(&u32NodeBuffSize, &(pstStRgme->u32stride), pstAttr);
    u32TotalBuffSize = u32NodeBuffSize * VPSS_RGME_MAX_NODE;
#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstAttr->bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_SttRgmeBuf", u32TotalBuffSize, 0, &pstStRgme->stTEEBuf);
#else
        s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_SttRgmeBuf", u32TotalBuffSize, 0, &(pstStRgme->stTEEBuf));
#endif
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS Strgme Alloc memory failed.\n");
            return HI_FAILURE;
        }

        u32PhyAddr = pstStRgme->stTEEBuf.u32StartSmmuAddr;
        pu8VirAddr = pstStRgme->stTEEBuf.pu8StartVirAddr;
    }
    else
    {
        s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_SttRgmeBuf", u32TotalBuffSize, 0, &(pstStRgme->stMMUBuf));

        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS Strgme Alloc memory failed.\n");
            return HI_FAILURE;
        }

        memset((HI_U8 *)pstStRgme->stMMUBuf.pu8StartVirAddr, 0, pstStRgme->stMMUBuf.u32Size);
        u32PhyAddr = pstStRgme->stMMUBuf.u32StartSmmuAddr;
        pu8VirAddr = pstStRgme->stMMUBuf.pu8StartVirAddr;
    }
#else
    s32Ret = HI_DRV_MMZ_AllocAndMap( "VPSS_SttRgmeBuf", HI_NULL, u32TotalBuffSize, 0, &(pstStRgme->stMMZBuf));
    if (HI_FAILURE == s32Ret)
    {
        VPSS_FATAL("VPSS Strgme Alloc memory failed.\n");
        return HI_FAILURE;
    }
    memset((HI_U8 *)pstStRgme->stMMZBuf.pu8StartVirAddr, 0, pstStRgme->stMMZBuf.u32Size);
    u32PhyAddr = pstStRgme->stMMZBuf.u32StartPhyAddr;
    pu8VirAddr = pstStRgme->stMMZBuf.pu8StartVirAddr;
#endif


    pListHead = &(pstStRgme->stDataList[0].node);
    INIT_LIST_HEAD(pListHead);
    pstStRgme->pstFirstRef = pListHead;

    for (i = 1 ; i < VPSS_RGME_MAX_NODE; i++)
    {
        list_add_tail(&(pstStRgme->stDataList[i].node), pListHead);
    }

    for (i = 0 ; i < VPSS_RGME_MAX_NODE; i++)
    {
        pstStRgme->stDataList[i].u32PhyAddr = u32PhyAddr;
        pstStRgme->stDataList[i].pu8VirAddr = pu8VirAddr;
        u32PhyAddr += u32NodeBuffSize;
        pu8VirAddr += u32NodeBuffSize;
    }

    pstStRgme->bInit = HI_TRUE;

    return HI_SUCCESS;

}
HI_S32 VPSS_ST_RGME_DeInit(VPSS_ST_RGME_S *pstStRgme)
{
    if (HI_NULL == pstStRgme)
    {
        VPSS_ERROR("Vpss Strgme DeInit error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStRgme->bInit)
    {
        VPSS_WARN("Vpss Strgme DeInit error(not init).\n");
        //return HI_FAILURE;
    }
    if (0 != pstStRgme->stTEEBuf.u32StartSmmuAddr)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(&pstStRgme->stTEEBuf);
#else
        HI_DRV_SMMU_UnmapAndRelease(&(pstStRgme->stTEEBuf));
#endif
    }
#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStRgme->stMMUBuf.u32StartSmmuAddr)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstStRgme->stMMUBuf));
    }
#else
    if (0 != pstStRgme->stMMZBuf.u32StartPhyAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstStRgme->stMMZBuf));
    }
#endif
    memset(pstStRgme, 0, sizeof(VPSS_ST_RGME_S));


    return HI_SUCCESS;

}

//��ȡRGME�˶���Ϣ
HI_S32 VPSS_ST_RGME_GetCfg(VPSS_ST_RGME_S *pstStRgme,
                           VPSS_ST_RGME_CFG_S *pstStRgmeCfg)
{
    VPSS_MC_DATA_S *pstRefNodeData = HI_NULL;
    LIST *pstRefNode = HI_NULL;

    if ((HI_NULL == pstStRgme) || (HI_NULL == pstStRgmeCfg))
    {
        VPSS_ERROR("Vpss Strgme GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStRgme->bInit)
    {
        VPSS_ERROR("Vpss Strgme GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    pstRefNode = pstStRgme->pstFirstRef;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStRgmeCfg->u32CurReadAddr = pstRefNodeData->u32PhyAddr;
    pstStRgmeCfg->pu8CurReadAddr = pstRefNodeData->pu8VirAddr;
    pstRefNode = pstRefNode->next;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStRgmeCfg->u32Nx1ReadAddr = pstRefNodeData->u32PhyAddr;
    pstStRgmeCfg->pu8Nx1ReadAddr = pstRefNodeData->pu8VirAddr;
    pstRefNode = pstRefNode->next;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStRgmeCfg->u32Nx2WriteAddr = pstRefNodeData->u32PhyAddr;
    pstStRgmeCfg->pu8Nx2WriteAddr = pstRefNodeData->pu8VirAddr;
    pstStRgmeCfg->u32Stride = pstStRgme->u32stride;

    return HI_SUCCESS;

}

//RGME�˶���Ϣ������ת
HI_S32 VPSS_ST_RGME_Complete(VPSS_ST_RGME_S *pstStRgme)
{
    if (HI_NULL == pstStRgme)
    {
        VPSS_ERROR("Vpss Strgme complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStRgme->bInit)
    {
        VPSS_ERROR("Vpss Strgme complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStRgme->u32Cnt++;
    pstStRgme->pstFirstRef = pstStRgme->pstFirstRef->next;

    return HI_SUCCESS;
}

//RGME�˶���Ϣ����reset
HI_S32 VPSS_ST_RGME_Reset(VPSS_ST_RGME_S *pstStRgme)
{
    if (HI_NULL == pstStRgme)
    {
        VPSS_WARN("Vpss Strgme complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStRgme->bInit)
    {
        VPSS_WARN("Vpss Strgme complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStRgme->u32Cnt = 0;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStRgme->stMMUBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStRgme->stMMUBuf.pu8StartVirAddr, 0, pstStRgme->stMMUBuf.u32Size);
    }
#else
    if (0 != pstStRgme->stMMZBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStRgme->stMMZBuf.pu8StartVirAddr, 0, pstStRgme->stMMZBuf.u32Size);
    }
#endif

    return HI_SUCCESS;

}

///////////////////////////////////////////////////////////////////
HI_VOID VPSS_ST_BLKMV_CalBufSize(HI_U32 *pSize, HI_U32 *pStride, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 u32Stride;
    HI_U32 u32Width;
    HI_U32 u32Height;

    u32Width = pstAttr->u32Width;
    u32Height = pstAttr->u32Height;

    u32Stride = ((u32Width + 7) / 8 * 4 + 15) / 16 * 16;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 3) / 4;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
}

HI_S32 VPSS_ST_BLKMV_Init(VPSS_ST_BLKMV_S *pstStBlkmv, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 i = 0;
    LIST *pListHead = HI_NULL;
    HI_U32 u32NodeBuffSize = 0;
    HI_U32 u32TotalBuffSize = 0;
    HI_U32 u32PhyAddr = 0;
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pstStBlkmv)
    {
        VPSS_ERROR("Vpss StblkmvInit error(null pointer).\n");
        return HI_FAILURE;
    }
    if (HI_TRUE == pstStBlkmv->bInit)
    {
        (HI_VOID)VPSS_ST_BLKMV_DeInit(pstStBlkmv);
    }

    memset(pstStBlkmv, 0, sizeof(VPSS_ST_BLKMV_S));
    pstStBlkmv->u32Width = pstAttr->u32Width;
    pstStBlkmv->u32Height = pstAttr->u32Height;

    VPSS_ST_BLKMV_CalBufSize(&u32NodeBuffSize, &(pstStBlkmv->u32stride), pstAttr);
    u32TotalBuffSize = u32NodeBuffSize * VPSS_BLKMV_MAX_NODE;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstAttr->bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_SttBlkmvBuf", u32TotalBuffSize, 0, &pstStBlkmv->stTEEBuf);
#else
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttBlkmvBuf", u32TotalBuffSize, 0, &(pstStBlkmv->stTEEBuf));
#endif
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS Stblkmv Alloc memory failed.\n");
            return HI_FAILURE;
        }
        u32PhyAddr = pstStBlkmv->stTEEBuf.u32StartSmmuAddr;
    }
    else
    {
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttBlkmvBuf", u32TotalBuffSize, 0, &(pstStBlkmv->stMMUBuf));
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS Stblkmv Alloc memory failed.\n");
            return HI_FAILURE;
        }
        memset((HI_U8 *)pstStBlkmv->stMMUBuf.pu8StartVirAddr, 0, pstStBlkmv->stMMUBuf.u32Size);
        u32PhyAddr = pstStBlkmv->stMMUBuf.u32StartSmmuAddr;
    }
#else
    s32Ret = HI_DRV_MMZ_AllocAndMap( "VPSS_SttBlkmvBuf", HI_NULL, u32TotalBuffSize, 0, &(pstStBlkmv->stMMZBuf));
    if (HI_FAILURE == s32Ret)
    {
        VPSS_FATAL("VPSS Stblkmv Alloc memory failed.\n");
        return HI_FAILURE;
    }
    memset((HI_U8 *)pstStBlkmv->stMMZBuf.pu8StartVirAddr, 0, pstStBlkmv->stMMZBuf.u32Size);
    u32PhyAddr = pstStBlkmv->stMMZBuf.u32StartPhyAddr;
#endif

    pListHead = &(pstStBlkmv->stDataList[0].node);
    INIT_LIST_HEAD(pListHead);
    pstStBlkmv->pstFirstRef = pListHead;

    for (i = 1 ; i < VPSS_BLKMV_MAX_NODE; i++)
    {
        list_add_tail(&(pstStBlkmv->stDataList[i].node), pListHead);
    }

    for (i = 0 ; i < VPSS_BLKMV_MAX_NODE; i++)
    {
        pstStBlkmv->stDataList[i].u32PhyAddr = u32PhyAddr;
        u32PhyAddr += u32NodeBuffSize;
    }

    pstStBlkmv->bInit = HI_TRUE;

    return HI_SUCCESS;

}



HI_S32 VPSS_ST_BLKMV_DeInit(VPSS_ST_BLKMV_S *pstStBlkmv)
{
    if (HI_NULL == pstStBlkmv)
    {
        VPSS_ERROR("Vpss Stblkmv DeInit error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBlkmv->bInit)
    {
        VPSS_WARN("Vpss Stblkmv DeInit error(not init).\n");
        //return HI_FAILURE;
    }

    if (0 != pstStBlkmv->stTEEBuf.u32StartSmmuAddr)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(&pstStBlkmv->stTEEBuf);
#else
        HI_DRV_SMMU_UnmapAndRelease(&(pstStBlkmv->stTEEBuf));
#endif
    }

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStBlkmv->stMMUBuf.u32StartSmmuAddr)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstStBlkmv->stMMUBuf));
    }
#else
    if (0 != pstStBlkmv->stMMZBuf.u32StartPhyAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstStBlkmv->stMMZBuf));
    }
#endif
    memset(pstStBlkmv, 0, sizeof(VPSS_ST_BLKMV_S));


    return HI_SUCCESS;
}

HI_S32 VPSS_ST_BLKMV_GetCfg(VPSS_ST_BLKMV_S *pstStBlkmv,
                            VPSS_ST_BLKMV_CFG_S *pstStBlkmvCfg)
{
    VPSS_MC_DATA_S *pstRefNodeData = HI_NULL;
    LIST *pstRefNode = HI_NULL;

    if ((HI_NULL == pstStBlkmv) || (HI_NULL == pstStBlkmvCfg))
    {
        VPSS_ERROR("Vpss Stblkmv GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBlkmv->bInit)
    {
        VPSS_ERROR("Vpss Stblkmv GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    pstRefNode = pstStBlkmv->pstFirstRef;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStBlkmvCfg->u32RefReadAddr = pstRefNodeData->u32PhyAddr;
    pstRefNode = pstRefNode->next;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
#if defined(CHIP_TYPE_hi3796mv200)
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStBlkmvCfg->u32CurReadAddr = pstRefNodeData->u32PhyAddr;
    pstRefNode = pstRefNode->next;

    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStBlkmvCfg->u32Nx1WriteAddr = pstRefNodeData->u32PhyAddr;
#else
    pstStBlkmvCfg->u32CurReadAddr = pstRefNodeData->u32PhyAddr;
    pstRefNode = pstRefNode->next;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStBlkmvCfg->u32Nx1ReadAddr = pstRefNodeData->u32PhyAddr;

    pstRefNode = pstRefNode->next;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStBlkmvCfg->u32Nx2WriteAddr = pstRefNodeData->u32PhyAddr;
#endif
    pstStBlkmvCfg->u32Stride = pstStBlkmv->u32stride;


    return HI_SUCCESS;

}


//BLKMV�˶���Ϣ������ת
HI_S32 VPSS_ST_BLKMV_Complete(VPSS_ST_BLKMV_S *pstStBlkmv)
{
    if (HI_NULL == pstStBlkmv)
    {
        VPSS_ERROR("Vpss Stblkmv complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBlkmv->bInit)
    {
        VPSS_ERROR("Vpss Stblkmv complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStBlkmv->u32Cnt++;
    pstStBlkmv->pstFirstRef = pstStBlkmv->pstFirstRef->next;

    return HI_SUCCESS;
}

//BLKMV�˶���Ϣ����reset
HI_S32 VPSS_ST_BLKMV_Reset(VPSS_ST_BLKMV_S *pstStBlkmv)
{
    if (HI_NULL == pstStBlkmv)
    {
        VPSS_WARN("Vpss Stblkmv complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBlkmv->bInit)
    {
        VPSS_WARN("Vpss Stblkmv complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStBlkmv->u32Cnt = 0;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStBlkmv->stMMUBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStBlkmv->stMMUBuf.pu8StartVirAddr, 0, pstStBlkmv->stMMUBuf.u32Size);
    }
#else
    if (0 != pstStBlkmv->stMMZBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStBlkmv->stMMZBuf.pu8StartVirAddr, 0, pstStBlkmv->stMMZBuf.u32Size);
    }
#endif
    return HI_SUCCESS;
}

#ifdef VPSS_SUPPORT_BLKMT
///////////////////////////////////////////////////////////////////
HI_VOID VPSS_ST_BLKMT_CalBufSize(HI_U32 *pSize, HI_U32 *pStride, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 u32Stride;
    HI_U32 u32Width;
    HI_U32 u32Height;

    u32Width = pstAttr->u32Width;
    u32Height = pstAttr->u32Height;

    u32Stride = ((u32Width + 7) / 8 * 4 + 15) / 16 * 16;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 3) / 4;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
}

HI_S32 VPSS_ST_BLKMT_Init(VPSS_ST_BLKMT_S *pstStBLKMT, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 i = 0;
    LIST *pListHead = HI_NULL;
    HI_U32 u32NodeBuffSize = 0;
    HI_U32 u32TotalBuffSize = 0;
    HI_U32 u32PhyAddr = 0;
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pstStBLKMT)
    {
        VPSS_ERROR("Vpss StBLKMTInit error(null pointer).\n");
        return HI_FAILURE;
    }
    if (HI_TRUE == pstStBLKMT->bInit)
    {
        (HI_VOID)VPSS_ST_BLKMT_DeInit(pstStBLKMT);
    }

    memset(pstStBLKMT, 0, sizeof(VPSS_ST_BLKMT_S));
    pstStBLKMT->u32Width = pstAttr->u32Width;
    pstStBLKMT->u32Height = pstAttr->u32Height;

    VPSS_ST_BLKMT_CalBufSize(&u32NodeBuffSize, &(pstStBLKMT->u32stride), pstAttr);
    u32TotalBuffSize = u32NodeBuffSize * VPSS_BLKMT_MAX_NODE;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstAttr->bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_SttBLKMTBuf", u32TotalBuffSize, 0, &pstStBLKMT->stTEEBuf);
#else
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttBLKMTBuf", u32TotalBuffSize, 0, &(pstStBLKMT->stTEEBuf));
#endif
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS StBLKMT Alloc memory failed.\n");
            return HI_FAILURE;
        }
        u32PhyAddr = pstStBLKMT->stTEEBuf.u32StartSmmuAddr;
    }
    else
    {
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttBLKMTBuf", u32TotalBuffSize, 0, &(pstStBLKMT->stMMUBuf));
        if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStBLKMT->stMMUBuf.pu8StartVirAddr))
        {
            VPSS_FATAL("VPSS StBLKMT Alloc memory failed.\n");
            return HI_FAILURE;
        }
        memset((HI_U8 *)pstStBLKMT->stMMUBuf.pu8StartVirAddr, 0, pstStBLKMT->stMMUBuf.u32Size);
        u32PhyAddr = pstStBLKMT->stMMUBuf.u32StartSmmuAddr;
    }
#else
    s32Ret = HI_DRV_MMZ_AllocAndMap( "VPSS_SttBLKMTBuf", HI_NULL, u32TotalBuffSize, 0, &(pstStBLKMT->stMMZBuf));
    if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStBLKMT->stMMZBuf.pu8StartVirAddr))
    {
        VPSS_FATAL("VPSS StBLKMT Alloc memory failed.\n");
        return HI_FAILURE;
    }
    memset((HI_U8 *)pstStBLKMT->stMMZBuf.pu8StartVirAddr, 0, pstStBLKMT->stMMZBuf.u32Size);
    u32PhyAddr = pstStBLKMT->stMMZBuf.u32StartPhyAddr;
#endif

    pListHead = &(pstStBLKMT->stDataList[0].node);
    INIT_LIST_HEAD(pListHead);
    pstStBLKMT->pstFirstRef = pListHead;

    for (i = 1 ; i < VPSS_BLKMT_MAX_NODE; i++)
    {
        list_add_tail(&(pstStBLKMT->stDataList[i].node), pListHead);
    }

    for (i = 0 ; i < VPSS_BLKMT_MAX_NODE; i++)
    {
        pstStBLKMT->stDataList[i].u32PhyAddr = u32PhyAddr;
        u32PhyAddr += u32NodeBuffSize;
    }

    pstStBLKMT->bInit = HI_TRUE;

    return HI_SUCCESS;

}

HI_S32 VPSS_ST_BLKMT_DeInit(VPSS_ST_BLKMT_S *pstStBLKMT)
{
    if (HI_NULL == pstStBLKMT)
    {
        VPSS_ERROR("Vpss StBLKMT DeInit error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBLKMT->bInit)
    {
        VPSS_WARN("Vpss StBLKMT DeInit error(not init).\n");
        //return HI_FAILURE;
    }

    if (0 != pstStBLKMT->stTEEBuf.u32StartSmmuAddr)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(&pstStBLKMT->stTEEBuf);
#else
        HI_DRV_SMMU_UnmapAndRelease(&(pstStBLKMT->stTEEBuf));
#endif
    }

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStBLKMT->stMMUBuf.u32StartSmmuAddr)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstStBLKMT->stMMUBuf));
    }
#else
    if (0 != pstStBLKMT->stMMZBuf.u32StartPhyAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstStBLKMT->stMMZBuf));
    }
#endif
    memset(pstStBLKMT, 0, sizeof(VPSS_ST_BLKMT_S));


    return HI_SUCCESS;
}

HI_S32 VPSS_ST_BLKMT_GetCfg(VPSS_ST_BLKMT_S *pstStBLKMT,
                            VPSS_ST_BLKMT_CFG_S *pstStBLKMTCfg)
{
    VPSS_MC_DATA_S *pstRefNodeData = HI_NULL;
    LIST *pstRefNode = HI_NULL;

    if ((HI_NULL == pstStBLKMT) || (HI_NULL == pstStBLKMTCfg))
    {
        VPSS_ERROR("Vpss StBLKMT GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBLKMT->bInit)
    {
        VPSS_ERROR("Vpss StBLKMT GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    pstRefNode = pstStBLKMT->pstFirstRef;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStBLKMTCfg->u32CurWriteAddr = pstRefNodeData->u32PhyAddr;
    pstRefNode = pstRefNode->next;

    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStBLKMTCfg->u32RefReadAddr = pstRefNodeData->u32PhyAddr;

    pstStBLKMTCfg->u32Stride = pstStBLKMT->u32stride;

    return HI_SUCCESS;
}


//BLKMT�˶���Ϣ������ת
HI_S32 VPSS_ST_BLKMT_Complete(VPSS_ST_BLKMT_S *pstStBLKMT)
{
    if (HI_NULL == pstStBLKMT)
    {
        VPSS_ERROR("Vpss StBLKMT complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBLKMT->bInit)
    {
        VPSS_ERROR("Vpss StBLKMT complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStBLKMT->u32Cnt++;
    pstStBLKMT->pstFirstRef = pstStBLKMT->pstFirstRef->next;

    return HI_SUCCESS;
}

//BLKMT�˶���Ϣ����reset
HI_S32 VPSS_ST_BLKMT_Reset(VPSS_ST_BLKMT_S *pstStBLKMT)
{
    if (HI_NULL == pstStBLKMT)
    {
        VPSS_WARN("Vpss StBLKMT complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStBLKMT->bInit)
    {
        VPSS_WARN("Vpss StBLKMT complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStBLKMT->u32Cnt = 0;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStBLKMT->stMMUBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStBLKMT->stMMUBuf.pu8StartVirAddr, 0, pstStBLKMT->stMMUBuf.u32Size);
    }
#else
    if (0 != pstStBLKMT->stMMZBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStBLKMT->stMMZBuf.pu8StartVirAddr, 0, pstStBLKMT->stMMZBuf.u32Size);
    }
#endif
    return HI_SUCCESS;
}


#endif //#ifdef VPSS_SUPPORT_BLKMT

#ifdef VPSS_SUPPORT_DICNT
///////////////////////////////////////////////////////////////////
HI_VOID VPSS_ST_DICNT_CalBufSize(HI_U32 *pSize, HI_U32 *pStride, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 u32Stride;
    HI_U32 u32Width;
    HI_U32 u32Height;

    u32Width = pstAttr->u32Width;
    u32Height = pstAttr->u32Height;

    u32Stride = (((u32Width + 3) / 4 * 4 + 7) / 8 + 15) / 16 * 16;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * u32Height / 2;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
}

HI_S32 VPSS_ST_DICNT_Init(VPSS_ST_DICNT_S *pstStDICNT, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 i = 0;
    LIST *pListHead = HI_NULL;
    HI_U32 u32NodeBuffSize = 0;
    HI_U32 u32TotalBuffSize = 0;
    HI_U32 u32PhyAddr = 0;
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pstStDICNT)
    {
        VPSS_ERROR("Vpss StDICNTInit error(null pointer).\n");
        return HI_FAILURE;
    }
    if (HI_TRUE == pstStDICNT->bInit)
    {
        (HI_VOID)VPSS_ST_DICNT_DeInit(pstStDICNT);
    }

    memset(pstStDICNT, 0, sizeof(VPSS_ST_DICNT_S));
    pstStDICNT->u32Width = (pstAttr->u32Width + 3) / 4;
    pstStDICNT->u32Height = pstAttr->u32Height / 2;

    VPSS_ST_DICNT_CalBufSize(&u32NodeBuffSize, &(pstStDICNT->u32stride), pstAttr);
    u32TotalBuffSize = u32NodeBuffSize * VPSS_DICNT_MAX_NODE;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstAttr->bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_SttDICNTBuf", u32TotalBuffSize, 0, &pstStDICNT->stTEEBuf);
#else
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttDICNTBuf", u32TotalBuffSize, 0, &(pstStDICNT->stTEEBuf));
#endif
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS StDICNT Alloc memory failed.\n");
            return HI_FAILURE;
        }
        u32PhyAddr = pstStDICNT->stTEEBuf.u32StartSmmuAddr;
    }
    else
    {
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttDICNTBuf", u32TotalBuffSize, 0, &(pstStDICNT->stMMUBuf));
        if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStDICNT->stMMUBuf.pu8StartVirAddr))
        {
            VPSS_FATAL("VPSS StDICNT Alloc memory failed.\n");
            return HI_FAILURE;
        }
        memset((HI_U8 *)pstStDICNT->stMMUBuf.pu8StartVirAddr, 0, pstStDICNT->stMMUBuf.u32Size);
        u32PhyAddr = pstStDICNT->stMMUBuf.u32StartSmmuAddr;
    }
#else
    s32Ret = HI_DRV_MMZ_AllocAndMap( "VPSS_SttDICNTBuf", HI_NULL, u32TotalBuffSize, 0, &(pstStDICNT->stMMZBuf));
    if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStDICNT->stMMZBuf.pu8StartVirAddr))
    {
        VPSS_FATAL("VPSS StDICNT Alloc memory failed.\n");
        return HI_FAILURE;
    }
    memset((HI_U8 *)pstStDICNT->stMMZBuf.pu8StartVirAddr, 0, pstStDICNT->stMMZBuf.u32Size);
    u32PhyAddr = pstStDICNT->stMMZBuf.u32StartPhyAddr;
#endif

    pListHead = &(pstStDICNT->stDataList[0].node);
    INIT_LIST_HEAD(pListHead);
    pstStDICNT->pstFirstRef = pListHead;

    for (i = 1 ; i < VPSS_DICNT_MAX_NODE; i++)
    {
        list_add_tail(&(pstStDICNT->stDataList[i].node), pListHead);
    }

    for (i = 0 ; i < VPSS_DICNT_MAX_NODE; i++)
    {
        pstStDICNT->stDataList[i].u32PhyAddr = u32PhyAddr;
        u32PhyAddr += u32NodeBuffSize;
    }

    pstStDICNT->bInit = HI_TRUE;

    return HI_SUCCESS;

}

HI_S32 VPSS_ST_DICNT_DeInit(VPSS_ST_DICNT_S *pstStDICNT)
{
    if (HI_NULL == pstStDICNT)
    {
        VPSS_ERROR("Vpss StDICNT DeInit error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStDICNT->bInit)
    {
        VPSS_WARN("Vpss StDICNT DeInit error(not init).\n");
        //return HI_FAILURE;
    }

    if (0 != pstStDICNT->stTEEBuf.u32StartSmmuAddr)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(&pstStDICNT->stTEEBuf);
#else
        HI_DRV_SMMU_UnmapAndRelease(&(pstStDICNT->stTEEBuf));
#endif
    }

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStDICNT->stMMUBuf.u32StartSmmuAddr)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstStDICNT->stMMUBuf));
    }
#else
    if (0 != pstStDICNT->stMMZBuf.u32StartPhyAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstStDICNT->stMMZBuf));
    }
#endif
    memset(pstStDICNT, 0, sizeof(VPSS_ST_DICNT_S));


    return HI_SUCCESS;
}

HI_S32 VPSS_ST_DICNT_GetCfg(VPSS_ST_DICNT_S *pstStDICNT,
                            VPSS_ST_DICNT_CFG_S *pstStDICNTCfg)
{
    VPSS_MC_DATA_S *pstRefNodeData = HI_NULL;
    LIST *pstRefNode = HI_NULL;

    if ((HI_NULL == pstStDICNT) || (HI_NULL == pstStDICNTCfg))
    {
        VPSS_ERROR("Vpss StDICNT GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStDICNT->bInit)
    {
        VPSS_ERROR("Vpss StDICNT GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    pstRefNode = pstStDICNT->pstFirstRef;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStDICNTCfg->u32WriteAddr = pstRefNodeData->u32PhyAddr;
    pstRefNode = pstRefNode->next;

    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStDICNTCfg->u32ReadAddr = pstRefNodeData->u32PhyAddr;

    pstStDICNTCfg->u32Stride = pstStDICNT->u32stride;

    pstStDICNTCfg->u32Height = pstStDICNT->u32Height;
    pstStDICNTCfg->u32Width  = pstStDICNT->u32Width;

    return HI_SUCCESS;
}


//DICNT�˶���Ϣ������ת
HI_S32 VPSS_ST_DICNT_Complete(VPSS_ST_DICNT_S *pstStDICNT)
{
    if (HI_NULL == pstStDICNT)
    {
        VPSS_ERROR("Vpss StDICNT complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStDICNT->bInit)
    {
        VPSS_ERROR("Vpss StDICNT complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStDICNT->u32Cnt++;
    pstStDICNT->pstFirstRef = pstStDICNT->pstFirstRef->next;

    return HI_SUCCESS;
}

//DICNT�˶���Ϣ����reset
HI_S32 VPSS_ST_DICNT_Reset(VPSS_ST_DICNT_S *pstStDICNT)
{
    if (HI_NULL == pstStDICNT)
    {
        VPSS_WARN("Vpss StDICNT complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStDICNT->bInit)
    {
        VPSS_WARN("Vpss StDICNT complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStDICNT->u32Cnt = 0;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStDICNT->stMMUBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStDICNT->stMMUBuf.pu8StartVirAddr, 0, pstStDICNT->stMMUBuf.u32Size);
    }
#else
    if (0 != pstStDICNT->stMMZBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStDICNT->stMMZBuf.pu8StartVirAddr, 0, pstStDICNT->stMMZBuf.u32Size);
    }
#endif
    return HI_SUCCESS;
}


#endif //#ifdef VPSS_SUPPORT_DICNT


///////////////////////////////////////////////////////////////////
HI_VOID VPSS_ST_PRJH_CalBufSize(HI_U32 *pSize, HI_U32 *pStride, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 u32Stride;
    HI_U32 u32Width;
    HI_U32 u32Height;

    u32Width = pstAttr->u32Width;
    u32Height = pstAttr->u32Height;

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    u32Stride = (((u32Width + 33) / 64 * 256) + 15) & 0xFFFFFFF0;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 5) / 8;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
#else
    u32Stride = (u32Width + 33) / 64 * 128 * 2;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 5) / 8;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
#endif
}

HI_S32 VPSS_ST_PRJH_Init(VPSS_ST_PRJH_S *pstStPrjh, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 i = 0;
    LIST *pListHead = HI_NULL;
    HI_U32 u32NodeBuffSize = 0;
    HI_U32 u32TotalBuffSize = 0;
    HI_U32 u32PhyAddr = 0;
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pstStPrjh)
    {
        VPSS_ERROR("Vpss StprjhInit error(null pointer).\n");
        return HI_FAILURE;
    }
    if (HI_TRUE == pstStPrjh->bInit)
    {
        (HI_VOID)VPSS_ST_PRJH_DeInit(pstStPrjh);
    }

    memset(pstStPrjh, 0, sizeof(VPSS_ST_PRJH_S));
    pstStPrjh->u32Width = pstAttr->u32Width;
    pstStPrjh->u32Height = pstAttr->u32Height;

    VPSS_ST_PRJH_CalBufSize(&u32NodeBuffSize, &(pstStPrjh->u32stride), pstAttr);
    u32TotalBuffSize = u32NodeBuffSize * VPSS_PRJH_MAX_NODE;
#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstAttr->bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_SttprjhBuf", u32TotalBuffSize, 0, &pstStPrjh->stTEEBuf);
#else
        s32Ret = HI_DRV_SMMU_AllocAndMap("VPSS_SttprjhBuf", u32TotalBuffSize, 0, &pstStPrjh->stTEEBuf);
#endif
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS Stprjh Alloc memory failed.\n");
            return HI_FAILURE;
        }
        u32PhyAddr = pstStPrjh->stTEEBuf.u32StartSmmuAddr;

    }
    else
    {
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttprjhBuf", u32TotalBuffSize, 0, &(pstStPrjh->stMMUBuf));
        if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStPrjh->stMMUBuf.pu8StartVirAddr))
        {
            VPSS_FATAL("VPSS Stprjh Alloc memory failed.\n");
            return HI_FAILURE;
        }
        memset((HI_U8 *)pstStPrjh->stMMUBuf.pu8StartVirAddr, 0, pstStPrjh->stMMUBuf.u32Size);
        u32PhyAddr = pstStPrjh->stMMUBuf.u32StartSmmuAddr;
    }
#else
    s32Ret = HI_DRV_MMZ_AllocAndMap( "VPSS_SttprjhBuf", HI_NULL, u32TotalBuffSize, 0, &(pstStPrjh->stMMZBuf));
    if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStPrjh->stMMZBuf.pu8StartVirAddr))
    {
        VPSS_FATAL("VPSS Stprjh Alloc memory failed.\n");
        return HI_FAILURE;
    }
    memset((HI_U8 *)pstStPrjh->stMMZBuf.pu8StartVirAddr, 0, pstStPrjh->stMMZBuf.u32Size);
    u32PhyAddr = pstStPrjh->stMMZBuf.u32StartPhyAddr;
#endif

    pListHead = &(pstStPrjh->stDataList[0].node);
    INIT_LIST_HEAD(pListHead);
    pstStPrjh->pstFirstRef = pListHead;

    for (i = 1 ; i < VPSS_RGME_MAX_NODE; i++)
    {
        list_add_tail(&(pstStPrjh->stDataList[i].node), pListHead);
    }

    for (i = 0 ; i < VPSS_RGME_MAX_NODE; i++)
    {
        pstStPrjh->stDataList[i].u32PhyAddr = u32PhyAddr;
        u32PhyAddr += u32NodeBuffSize;
    }

    pstStPrjh->bInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 VPSS_ST_PRJH_DeInit(VPSS_ST_PRJH_S *pstStPrjh)
{
    if (HI_NULL == pstStPrjh)
    {
        VPSS_ERROR("Vpss Stprjh DeInit error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjh->bInit)
    {
        VPSS_WARN("Vpss Stprjh DeInit error(not init).\n");
        //return HI_FAILURE;
    }
    if (0 != pstStPrjh->stTEEBuf.u32StartSmmuAddr)
    {
#ifdef HI_TEE_SUPPORT
        (HI_VOID)HI_DRV_SECSMMU_Release(&pstStPrjh->stTEEBuf);
#else
        HI_DRV_SMMU_UnmapAndRelease(&(pstStPrjh->stTEEBuf));
#endif
    }
#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStPrjh->stMMUBuf.u32StartSmmuAddr)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstStPrjh->stMMUBuf));
    }
#else
    if (0 != pstStPrjh->stMMZBuf.u32StartPhyAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstStPrjh->stMMZBuf));
    }
#endif
    memset(pstStPrjh, 0, sizeof(VPSS_ST_PRJH_S));
    return HI_SUCCESS;

}

//��ȡPRJH�˶���Ϣ
HI_S32 VPSS_ST_PRJH_GetCfg(VPSS_ST_PRJH_S *pstStPrjh,
                           VPSS_ST_PRJH_CFG_S *pstStPrjhCfg)
{
    VPSS_MC_DATA_S *pstRefNodeData = HI_NULL;
    LIST *pstRefNode = HI_NULL;

    if ((HI_NULL == pstStPrjh) || (HI_NULL == pstStPrjhCfg))
    {
        VPSS_ERROR("Vpss Stprjh GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjh->bInit)
    {
        VPSS_ERROR("Vpss Stprjh GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    pstRefNode = pstStPrjh->pstFirstRef;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStPrjhCfg->u32CurReadAddr = pstRefNodeData->u32PhyAddr;
    pstRefNode = pstRefNode->next;
    pstRefNode = pstRefNode->next;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStPrjhCfg->u32Nx2WriteAddr = pstRefNodeData->u32PhyAddr;
    pstStPrjhCfg->u32Stride = pstStPrjh->u32stride;

    return HI_SUCCESS;

}

//PRJH�˶���Ϣ������ת
HI_S32 VPSS_ST_PRJH_Complete(VPSS_ST_PRJH_S *pstStPrjh)
{
    if (HI_NULL == pstStPrjh)
    {
        VPSS_ERROR("Vpss Stprjh complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjh->bInit)
    {
        VPSS_ERROR("Vpss Stprjh complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStPrjh->u32Cnt++;
    pstStPrjh->pstFirstRef = pstStPrjh->pstFirstRef->next;

    return HI_SUCCESS;

}

//PRJH�˶���Ϣ����reset
HI_S32 VPSS_ST_PRJH_Reset(VPSS_ST_PRJH_S *pstStPrjh)
{
    if (HI_NULL == pstStPrjh)
    {
        VPSS_WARN("Vpss Stprjh complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjh->bInit)
    {
        VPSS_WARN("Vpss Stprjh complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStPrjh->u32Cnt = 0;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStPrjh->stMMUBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStPrjh->stMMUBuf.pu8StartVirAddr, 0, pstStPrjh->stMMUBuf.u32Size);
    }
#else
    if (0 != pstStPrjh->stMMZBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStPrjh->stMMZBuf.pu8StartVirAddr, 0, pstStPrjh->stMMZBuf.u32Size);
    }
#endif

    return HI_SUCCESS;

}

///////////////////////////////////////////////////////////////////

HI_VOID VPSS_ST_PRJV_CalBufSize(HI_U32 *pSize, HI_U32 *pStride, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 u32Stride;
    HI_U32 u32Width;
    HI_U32 u32Height;

    u32Width = pstAttr->u32Width;
    u32Height = pstAttr->u32Height;

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    u32Stride = ((u32Width + 33) / 64 * 64 + 15) & 0xFFFFFFF0;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 5) / 8;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
#else
    u32Stride = (u32Width + 33) / 64 * 32 * 2;
    u32Stride = HI_ALIGN_8BIT_YSTRIDE(u32Stride);
    *pSize = u32Stride * (u32Height / 2 + 5) / 8;
    *pSize = HI_ALIGN_8BIT_YSTRIDE(*pSize);
    *pStride = u32Stride;
#endif
}

HI_S32 VPSS_ST_PRJV_Init(VPSS_ST_PRJV_S *pstStPrjv, VPSS_MC_ATTR_S *pstAttr)
{
    HI_U32 i = 0;
    LIST *pListHead = HI_NULL;
    HI_U32 u32NodeBuffSize = 0;
    HI_U32 u32TotalBuffSize = 0;
    HI_U32 u32PhyAddr = 0;
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == pstStPrjv)
    {
        VPSS_ERROR("Vpss StprjvInit error(null pointer).\n");
        return HI_FAILURE;
    }
    if (HI_TRUE == pstStPrjv->bInit)
    {
        (HI_VOID)VPSS_ST_PRJV_DeInit(pstStPrjv);
    }

    memset(pstStPrjv, 0, sizeof(VPSS_ST_PRJV_S));
    pstStPrjv->u32Width = pstAttr->u32Width;
    pstStPrjv->u32Height = pstAttr->u32Height;

    VPSS_ST_PRJV_CalBufSize(&u32NodeBuffSize, &(pstStPrjv->u32stride), pstAttr);
    u32TotalBuffSize = u32NodeBuffSize * VPSS_PRJV_MAX_NODE;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (pstAttr->bSecure)
    {
#ifdef HI_TEE_SUPPORT
        s32Ret = HI_DRV_SECSMMU_Alloc("VPSS_SttprjvBuf", u32TotalBuffSize, 0, &pstStPrjv->stTEEBuf);
#else
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttprjvBuf", u32TotalBuffSize, 0, &(pstStPrjv->stTEEBuf));
#endif
        if (HI_FAILURE == s32Ret)
        {
            VPSS_FATAL("VPSS Stprjv Alloc memory failed.\n");
            return HI_FAILURE;
        }
        u32PhyAddr = pstStPrjv->stTEEBuf.u32StartSmmuAddr;
    }
    else
    {
        s32Ret = HI_DRV_SMMU_AllocAndMap( "VPSS_SttprjvBuf", u32TotalBuffSize, 0, &(pstStPrjv->stMMUBuf));
        if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStPrjv->stMMUBuf.pu8StartVirAddr))
        {
            VPSS_FATAL("VPSS Stprjv Alloc memory failed.\n");
            return HI_FAILURE;
        }
        memset((HI_U8 *)pstStPrjv->stMMUBuf.pu8StartVirAddr, 0, pstStPrjv->stMMUBuf.u32Size);
        u32PhyAddr = pstStPrjv->stMMUBuf.u32StartSmmuAddr;
    }
#else
    s32Ret = HI_DRV_MMZ_AllocAndMap( "VPSS_SttprjvBuf", HI_NULL, u32TotalBuffSize, 0, &(pstStPrjv->stMMZBuf));
    if ((HI_FAILURE == s32Ret) || (HI_NULL == pstStPrjv->stMMZBuf.pu8StartVirAddr))
    {
        VPSS_FATAL("VPSS Stprjv Alloc memory failed.\n");
        return HI_FAILURE;
    }
    memset((HI_U8 *)pstStPrjv->stMMZBuf.pu8StartVirAddr, 0, pstStPrjv->stMMZBuf.u32Size);
    u32PhyAddr = pstStPrjv->stMMZBuf.u32StartPhyAddr;
#endif

    pListHead = &(pstStPrjv->stDataList[0].node);
    INIT_LIST_HEAD(pListHead);
    pstStPrjv->pstFirstRef = pListHead;

    for (i = 1 ; i < VPSS_RGME_MAX_NODE; i++)
    {
        list_add_tail(&(pstStPrjv->stDataList[i].node), pListHead);
    }

    for (i = 0 ; i < VPSS_RGME_MAX_NODE; i++)
    {
        pstStPrjv->stDataList[i].u32PhyAddr = u32PhyAddr;
        u32PhyAddr += u32NodeBuffSize;
    }

    pstStPrjv->bInit = HI_TRUE;

    return HI_SUCCESS;

}

HI_S32 VPSS_ST_PRJV_DeInit(VPSS_ST_PRJV_S *pstStPrjv)
{
    if (HI_NULL == pstStPrjv)
    {
        VPSS_ERROR("Vpss Stprjv DeInit error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjv->bInit)
    {
        VPSS_WARN("Vpss Stprjv DeInit error(not init).\n");
        //return HI_FAILURE;
    }
    if (0 != pstStPrjv->stTEEBuf.u32StartSmmuAddr)
    {
#ifdef HI_TEE_SUPPORT
        HI_DRV_SECSMMU_Release(&(pstStPrjv->stTEEBuf));
#else
        HI_DRV_SMMU_UnmapAndRelease(&(pstStPrjv->stTEEBuf));
#endif
    }
#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStPrjv->stMMUBuf.u32StartSmmuAddr)
    {
        HI_DRV_SMMU_UnmapAndRelease(&(pstStPrjv->stMMUBuf));
    }
#else
    if (0 != pstStPrjv->stMMZBuf.u32StartPhyAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&(pstStPrjv->stMMZBuf));
    }
#endif
    memset(pstStPrjv, 0, sizeof(VPSS_ST_PRJV_S));
    return HI_SUCCESS;

}

//��ȡPRJV�˶���Ϣ
HI_S32 VPSS_ST_PRJV_GetCfg(VPSS_ST_PRJV_S *pstStPrjv,
                           VPSS_ST_PRJV_CFG_S *pstStPrjvCfg)
{
    VPSS_MC_DATA_S *pstRefNodeData = HI_NULL;
    LIST *pstRefNode = HI_NULL;

    if ((HI_NULL == pstStPrjv) || (HI_NULL == pstStPrjvCfg))
    {
        VPSS_ERROR("Vpss Stprjv GetRefInfo error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjv->bInit)
    {
        VPSS_ERROR("Vpss Stprjv GetRefInfo error(not init).\n");
        return HI_FAILURE;
    }

    pstRefNode = pstStPrjv->pstFirstRef;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStPrjvCfg->u32CurReadAddr = pstRefNodeData->u32PhyAddr;
    pstRefNode = pstRefNode->next;
    pstRefNode = pstRefNode->next;
    pstRefNodeData = list_entry(pstRefNode, VPSS_MC_DATA_S, node);
    pstStPrjvCfg->u32Nx2WriteAddr = pstRefNodeData->u32PhyAddr;
    pstStPrjvCfg->u32Stride = pstStPrjv->u32stride;

    return HI_SUCCESS;

}

//PRJV�˶���Ϣ������ת
HI_S32 VPSS_ST_PRJV_Complete(VPSS_ST_PRJV_S *pstStPrjv)
{
    if (HI_NULL == pstStPrjv)
    {
        VPSS_ERROR("Vpss Stprjv complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjv->bInit)
    {
        VPSS_ERROR("Vpss Stprjv complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStPrjv->u32Cnt++;
    pstStPrjv->pstFirstRef = pstStPrjv->pstFirstRef->next;

    return HI_SUCCESS;

}

//PRJV�˶���Ϣ����reset
HI_S32 VPSS_ST_PRJV_Reset(VPSS_ST_PRJV_S *pstStPrjv)
{
    if (HI_NULL == pstStPrjv)
    {
        VPSS_WARN("Vpss Stprjv complete error(null pointer).\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstStPrjv->bInit)
    {
        VPSS_WARN("Vpss Stprjv complete error(not init).\n");
        return HI_FAILURE;
    }

    pstStPrjv->u32Cnt = 0;

#ifdef HI_VPSS_SMMU_SUPPORT
    if (0 != pstStPrjv->stMMUBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStPrjv->stMMUBuf.pu8StartVirAddr, 0, pstStPrjv->stMMUBuf.u32Size);
    }
#else
    if (0 != pstStPrjv->stMMZBuf.pu8StartVirAddr)
    {
        memset((HI_U8 *)pstStPrjv->stMMZBuf.pu8StartVirAddr, 0, pstStPrjv->stMMZBuf.u32Size);
    }

#endif
    return HI_SUCCESS;


}

///////////////////////////////////////////////////////////////////






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

