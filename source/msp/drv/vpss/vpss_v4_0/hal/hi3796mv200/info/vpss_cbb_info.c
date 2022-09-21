#include "vpss_cbb_info.h"
#include "vpss_cbb_reg.h"

HI_VOID VPSS_InfoCfg_Dei_ST(CBB_INFO_S *pstInfoDeiCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetStRaddr(pstVpssNode, pstInfoDeiCfg->u32RPhyAddr);
    VPSS_Mac_SetStWaddr(pstVpssNode, pstInfoDeiCfg->u32WPhyAddr);
    VPSS_Mac_SetStStride(pstVpssNode, pstInfoDeiCfg->u32Stride);

    VPSS_Mac_SetRchRstBypass(pstVpssNode, pstInfoDeiCfg->bSmmu_R);
    VPSS_Mac_SetWchWstBypass(pstVpssNode, pstInfoDeiCfg->bSmmu_W);
}

HI_VOID VPSS_InfoCfg_Di_CNT(CBB_INFO_S *pstInfoDiCntCfg, CBB_REG_ADDR_S stRegAddr)
{

    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetDiWcntAddr(pstVpssNode, pstInfoDiCntCfg->u32WPhyAddr);
    VPSS_Mac_SetDiRcntAddr(pstVpssNode, pstInfoDiCntCfg->u32RPhyAddr);
    VPSS_Mac_SetDiCntStride(pstVpssNode, pstInfoDiCntCfg->u32Stride, pstInfoDiCntCfg->u32Stride);
    VPSS_Mac_SetDiCntSize(pstVpssNode, pstInfoDiCntCfg->u32Width, pstInfoDiCntCfg->u32Height);
    VPSS_Mac_SetRchDiCntBypass(pstVpssNode, pstInfoDiCntCfg->bSmmu_R);
    VPSS_Mac_SetWchDiCntBypass(pstVpssNode, pstInfoDiCntCfg->bSmmu_W);
}

HI_VOID VPSS_InfoGet_All(S_STT_REGS_TYPE *pstSttReg, CBB_INFO_S *pstInfoStt)
{
    VPSS_SAFE_MEMCPY(pstSttReg, pstInfoStt->pu8RVirAddr, sizeof(S_STT_REGS_TYPE));
}

HI_VOID VPSS_InfoCfg_Prjv(CBB_INFO_PRJV_S *pstInfoPrjvCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetPrjvNx2Addr(pstVpssNode, pstInfoPrjvCfg->u32Nx2WriteAddr);
    VPSS_Mac_SetPrjvNx2Stride(pstVpssNode, pstInfoPrjvCfg->u32Stride);
    VPSS_Mac_SetPrjvCurAddr(pstVpssNode, pstInfoPrjvCfg->u32CurReadAddr);
    VPSS_Mac_SetPrjvCurStride(pstVpssNode, pstInfoPrjvCfg->u32Stride);

    VPSS_Mac_SetRchPrjvCurBypass(pstVpssNode, pstInfoPrjvCfg->bSmmu_Cur);
    VPSS_Mac_SetWchPrjvNx2Bypass(pstVpssNode, pstInfoPrjvCfg->bSmmu_Nx2);
}

HI_VOID VPSS_InfoCfg_Prjh(CBB_INFO_PRJH_S *pstInfoPrjhCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;
    VPSS_Mac_SetPrjhNx2Addr(pstVpssNode, pstInfoPrjhCfg->u32Nx2WriteAddr);
    VPSS_Mac_SetPrjhNx2Stride(pstVpssNode, pstInfoPrjhCfg->u32Stride);
    VPSS_Mac_SetPrjhCurAddr(pstVpssNode, pstInfoPrjhCfg->u32CurReadAddr);
    VPSS_Mac_SetPrjhCurStride(pstVpssNode, pstInfoPrjhCfg->u32Stride);

    VPSS_Mac_SetRchPrjhCurBypass(pstVpssNode, pstInfoPrjhCfg->bSmmu_Cur);
    VPSS_Mac_SetWchPrjhNx2Bypass(pstVpssNode, pstInfoPrjhCfg->bSmmu_Nx2);
}

HI_VOID VPSS_InfoCfg_Blkmv(CBB_INFO_BLKMV_S *pstInfoBlkmvCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetBlkmvNx1Addr(pstVpssNode, pstInfoBlkmvCfg->u32Nx1WriteAddr);
    VPSS_Mac_SetBlkmvNx1Stride(pstVpssNode, pstInfoBlkmvCfg->u32Stride);
    VPSS_Mac_SetBlkmvRefAddr(pstVpssNode, pstInfoBlkmvCfg->u32RefReadAddr);
    VPSS_Mac_SetBlkmvRefStride(pstVpssNode, pstInfoBlkmvCfg->u32Stride);
    VPSS_Mac_SetBlkmvCurAddr(pstVpssNode, pstInfoBlkmvCfg->u32CurReadAddr);
    VPSS_Mac_SetBlkmvCurStride(pstVpssNode, pstInfoBlkmvCfg->u32Stride);

    VPSS_Mac_SetRchBlkmvRefBypass(pstVpssNode, pstInfoBlkmvCfg->bSmmu_Ref);
    VPSS_Mac_SetRchBlkmvCurBypass(pstVpssNode, pstInfoBlkmvCfg->bSmmu_Cur);
    VPSS_Mac_SetWchBlkmvNx1Bypass(pstVpssNode, pstInfoBlkmvCfg->bSmmu_Nx1);
}

HI_VOID VPSS_InfoCfg_Blkmt(CBB_INFO_BLKMT_S *pstInfoBlkmtCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetBlkmtCurAddr(pstVpssNode, pstInfoBlkmtCfg->u32CurWriteAddr);
    VPSS_Mac_SetBlkmtCurStride(pstVpssNode, pstInfoBlkmtCfg->u32Stride);
    VPSS_Mac_SetBlkmtRefAddr(pstVpssNode, pstInfoBlkmtCfg->u32RefReadAddr);
    VPSS_Mac_SetBlkmtRefStride(pstVpssNode, pstInfoBlkmtCfg->u32Stride);

    VPSS_Mac_SetRchBlkmtRefBypass(pstVpssNode, pstInfoBlkmtCfg->bSmmu_Ref);
    VPSS_Mac_SetWchBlkmtCurBypass(pstVpssNode, pstInfoBlkmtCfg->bSmmu_Cur);
}

HI_VOID VPSS_InfoCfg_Rgmv(CBB_INFO_RGMV_S *pstInfoRgmvCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetRgmvCurAddr(pstVpssNode, pstInfoRgmvCfg->u32CurReadAddr);
    VPSS_Mac_SetRgmvNx1Addr(pstVpssNode, pstInfoRgmvCfg->u32Nx1ReadAddr);
    VPSS_Mac_SetRgmvNx2Addr(pstVpssNode, pstInfoRgmvCfg->u32Nx2WriteAddr);
    VPSS_Mac_SetRgmvCurStride(pstVpssNode, pstInfoRgmvCfg->u32Stride);
    VPSS_Mac_SetRgmvNx1Stride(pstVpssNode, pstInfoRgmvCfg->u32Stride);
    VPSS_Mac_SetRgmvNx2Stride(pstVpssNode, pstInfoRgmvCfg->u32Stride);

    VPSS_Mac_SetRchRgmvCurBypass(pstVpssNode, pstInfoRgmvCfg->bSmmu_Cur);
    VPSS_Mac_SetRchRgmvNx1Bypass(pstVpssNode, pstInfoRgmvCfg->bSmmu_Nx1);
    VPSS_Mac_SetWchRgmvNx2Bypass(pstVpssNode, pstInfoRgmvCfg->bSmmu_Nx2);

    VPSS_Sys_SetRgmeEn(pstVpssNode, HI_TRUE);
}


HI_VOID VPSS_InfoCfg_Snr_Mad(CBB_INFO_S *pstInfoSnrCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetSnrMadRaddr(pstVpssNode, pstInfoSnrCfg->u32RPhyAddr);

}

HI_VOID VPSS_InfoCfg_Tnr_Mad(CBB_INFO_S *pstInfoTnrCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetMadRaddr(pstVpssNode, pstInfoTnrCfg->u32RPhyAddr);
    VPSS_Mac_SetMadWaddr(pstVpssNode, pstInfoTnrCfg->u32WPhyAddr);
    VPSS_Mac_SetMadStride(pstVpssNode, pstInfoTnrCfg->u32Stride);


}

HI_VOID VPSS_INFOCfg_SttInfo(CBB_INFO_S *pstInfoStt, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Mac_SetSttWAddr(pstVpssNode, pstInfoStt->u32WPhyAddr);


}

