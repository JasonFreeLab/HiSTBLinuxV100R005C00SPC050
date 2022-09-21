#include "vpss_cbb_frame.h"
#include "vpss_cbb_func.h"
#include "vpss_cbb_component.h"
#include "vpss_cbb_debug.h"
#include "vpss_cbb_intf.h"
#include "vpss_reg_struct.h"
//#include "vpss_reg.h"
//#include "vpss_module.h"

HI_S32 CBB_CfgFrm_ReadCur(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    HI_BOOL             bEnTile;
    HI_U32              u32BitWth;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enPixelFmt\n");
        return HI_FAILURE;
    }

    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }

    VPSS_Mac_SetRchCuryBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchCurcBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);


    VPSS_Sys_SetRefDitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
    VPSS_Sys_SetRefDitherEn(pstVpssNode, HI_TRUE);
#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_CUR;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif
    VPSS_Mac_SetRefWidth(pstVpssNode, pstFrmCfg->u32Width);
    VPSS_Mac_SetRefHeight(pstVpssNode, pstFrmCfg->u32Height);
    VPSS_Mac_SetCurHorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetCurVerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetCurTileFormat(pstVpssNode, bEnTile);
    VPSS_Mac_SetCuryAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetCurcAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetCuryStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetCurcStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);
    VPSS_Sys_SetRefPixBitw(pstVpssNode, u32BitWth);
    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_ReadNx1(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    HI_BOOL             bEnTile;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:

            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }

    VPSS_Mac_SetRchNx1yBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchNx1cBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_NX1;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif

    VPSS_Mac_SetNxt1HorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetNxt1VerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetNxt1TileFormat(pstVpssNode, bEnTile);
    VPSS_Mac_SetNxt1yAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetNxt1cAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetNxt1yStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetNxt1cStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    return HI_SUCCESS;
}


HI_U32 CBB_FrameFmtTrans( HI_DRV_PIX_FORMAT_E   enPixelFmt )
{
    HI_U32 u32Fmt = 0;

    switch (enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
            u32Fmt = 0x0;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1_CMP:
        case HI_DRV_PIX_FMT_NV61_CMP:
        case HI_DRV_PIX_FMT_NV16_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16:
        case HI_DRV_PIX_FMT_NV61:
            u32Fmt = 0x1;
            break;
        case HI_DRV_PIX_FMT_YUV400:
            u32Fmt = 0x4;
            break;
        case HI_DRV_PIX_FMT_YUV_444:
            u32Fmt = 0x5;
            break;
        case HI_DRV_PIX_FMT_YUV422_2X1:
            u32Fmt = 0x6;
            break;
        case HI_DRV_PIX_FMT_YUV420p:
            u32Fmt = 0x8;
            break;
        case HI_DRV_PIX_FMT_YUV411:
            u32Fmt = 0x9;
            break;
        case HI_DRV_PIX_FMT_YUV410p:
            u32Fmt = 0xa;
            break;
        case HI_DRV_PIX_FMT_YUYV:
            u32Fmt = 0xb;
            break;
        case HI_DRV_PIX_FMT_YVYU:
            u32Fmt = 0xc;
            break;
        case HI_DRV_PIX_FMT_UYVY:
            u32Fmt = 0xd;
            break;
        default:
            CBB_ERRMSG("REG ERROR");
    }

    return u32Fmt;
}

HI_S32 CBB_CfgFrm_ReadNx2(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    HI_U32 u32Format = 0;
    HI_BOOL bEnTile = HI_FALSE;
    HI_BOOL bDeCmp;
    HI_U32 u32Field;
    HI_U32 u32FieldFirst;
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enBitWth\n");
        return HI_FAILURE;
    }
#if (!CBB_TEST)
    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:

            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }
    u32Format = CBB_FrameFmtTrans(pstFrmCfg->enPixelFmt);
#else
    switch (pstFrmCfg->enPixelFmt)
    {
        case INPUTFMT_TILE_SP420 :
        case INPUTFMT_TILE_400 :
            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }
    u32Format = VPSS_FrameFmtTrans(pstFrmCfg->enPixelFmt);
#endif

    if (pstFrmCfg->bProgressive)
    {
        VPSS_Sys_SetBfield(pstVpssNode, HI_FALSE);
    }
    else
    {
        VPSS_Sys_SetBfield(pstVpssNode, HI_TRUE);
    }

    if (pstFrmCfg->bTop)
    {
        u32Field = 0x0;
    }
    else
    {
        u32Field = 0x1;
    }

    if (pstFrmCfg->bTopFirst)
    {
        u32FieldFirst = 0x0;
    }
    else
    {
        u32FieldFirst = 0x1;
    }

    //VPSS_MEM_CLEAR(stFuncVC1Cfg);
    VPSS_Mac_SetRchNx2yBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchNx2cBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);
    VPSS_Mac_SetRchNx2ylbBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_Y);
    VPSS_Mac_SetRchNx2clbBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].bSmmu_C);

    VPSS_Sys_SetBfieldMode(pstVpssNode, u32Field);
    VPSS_Sys_SetBfieldFirst(pstVpssNode, u32FieldFirst);
#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_NX2;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif
    VPSS_Sys_SetProt(pstVpssNode, pstFrmCfg->bSecure);

    if (pstFrmCfg->bCompress)
    {
        VPSS_Mac_SetNx2yTopHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead);
        VPSS_Mac_SetNx2yBotHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_YHead
                                    + (pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size / 2));

        VPSS_Mac_SetNx2cTopHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead);
        VPSS_Mac_SetNx2cBotHeadAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_CHead
                                    + (pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Head_Size / 4));

        VPSS_Mac_SetNx2HeadStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Head_Stride);

        VPSS_Mac_SetRchNx2yHeadBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_YHead);
        VPSS_Mac_SetRchNx2cHeadBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_CHead);


        bDeCmp = HI_TRUE;
    }
    else
    {
        bDeCmp = HI_FALSE;
    }

    VPSS_Sys_SetInPixBitw(pstVpssNode, u32BitWth);
    VPSS_Sys_SetInFormat(pstVpssNode, u32Format);
    VPSS_Mac_SetImgwidth(pstVpssNode, pstFrmCfg->u32Width);
    VPSS_Mac_SetImgheight(pstVpssNode, pstFrmCfg->u32Height);


    VPSS_Mac_SetNxt2yAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetNxt2cAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetNxt2yStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetNxt2cStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_Mac_SetNxt2DcmpEn(pstVpssNode, bDeCmp);
    VPSS_Mac_SetNxt2HorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetNxt2VerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetNxt2TileFormat(pstVpssNode, bEnTile);

    if ( CBB_BITWIDTH_10BIT == pstFrmCfg->enBitWidth && bEnTile == HI_TRUE)
    {
        VPSS_Mac_SetNx2yLbAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_Y);
        VPSS_Mac_SetNx2cLbAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32PhyAddr_C);
        VPSS_Mac_SetNx2LbStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_2BIT_LB].u32Stride_Y);
    }

    return HI_SUCCESS;
}


HI_S32 CBB_CfgFrm_ReadRef(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    //CBB_FUNC_VC1_S        stFuncVC1Cfg;
    //CBB_FRAME_CHANNEL_E enChan;
    HI_BOOL             bEnTile;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;


    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enPixelFmt\n");
        return HI_FAILURE;
    }

    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12_TILE: /* 12 tile  */
        case HI_DRV_PIX_FMT_NV21_TILE: /* 21 tile  */
        case HI_DRV_PIX_FMT_YUV400_TILE: /* 21 tile  */
            bEnTile = HI_TRUE;
            break;
        default:
            bEnTile = HI_FALSE;
            break;
    }

    VPSS_Mac_SetRchRefyBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchRefcBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

#if 0
    stFuncVC1Cfg.bEnable = HI_FALSE;
    enChan = CBB_FRAME_READ_REF;
    VPSS_CBB_FUNC_SetConfig(stRegAddr, CBB_FUNC_VC1, (HI_VOID *)&stFuncVC1Cfg, (HI_VOID *)&enChan);
#endif
    //VPSS_Mac_SetRefWidth(pstVpssNode, pstFrmCfg->u32Width);
    //VPSS_Mac_SetRefHeight(pstVpssNode, pstFrmCfg->u32Height);

    VPSS_Mac_SetRefHorOffset(pstVpssNode, pstFrmCfg->stOffset.s32X);
    VPSS_Mac_SetRefVerOffset(pstVpssNode, pstFrmCfg->stOffset.s32Y);
    VPSS_Mac_SetRefTileFormat(pstVpssNode, bEnTile);

    VPSS_Mac_SetRefyAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetRefcAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetRefyStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetRefcStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);


    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_ReadRee(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    CBB_FRAME_ADDR_S    *pstAddr;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    pstAddr = &(pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT]);
    VPSS_Mac_SetReeyAddr(pstVpssNode, pstAddr->u32PhyAddr_Y);
    VPSS_Mac_SetReecAddr(pstVpssNode, pstAddr->u32PhyAddr_C);
    VPSS_Mac_SetReeyStride(pstVpssNode, pstAddr->u32Stride_Y);
    VPSS_Mac_SetReecStride(pstVpssNode, pstAddr->u32Stride_C);

    VPSS_Mac_SetRchReeyBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetRchReecBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    return HI_SUCCESS;
}


HI_S32 CBB_CfgFrm_WriteVhd0(CBB_FRAME_S *pstFrmCfg, HI_VOID *pArgs, CBB_REG_ADDR_S stRegAddr)
{

    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    HI_U32 u32Format = 0;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if ((pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT) || (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT_CTS))
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enPixelFmt\n");
        return HI_FAILURE;
    }
#if 1
    switch (pstFrmCfg->enPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
            u32Format = 0x0;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV16:
        case HI_DRV_PIX_FMT_NV61:
            u32Format = 0x1;
            break;
        default:
            return HI_FAILURE;
    }
#else
    u32Format = pstFrmCfg->enPixelFmt ;
#endif

    VPSS_Mac_SetVhd0Width(pstVpssNode, pstFrmCfg->u32Width);
    VPSS_Mac_SetVhd0Height(pstVpssNode, pstFrmCfg->u32Height);
    VPSS_Mac_SetVhd0PixBitw(pstVpssNode, u32BitWth);
    VPSS_Sys_SetVhd0Format(pstVpssNode, u32Format);

    if (pstFrmCfg->enBitWidth > CBB_BITWIDTH_8BIT)
    {
        VPSS_Mac_SetVhd0DitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetVhd0DitherEn(pstVpssNode, HI_FALSE);
    }
    else
    {
        VPSS_Mac_SetVhd0DitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetVhd0DitherEn(pstVpssNode, HI_TRUE);
    }

    VPSS_Mac_SetVhd0yAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetVhd0cAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetVhd0yStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetVhd0cStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    VPSS_Mac_SetWchVhd0yBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetWchVhd0cBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    VPSS_Sys_SetVhd0En(pstVpssNode, HI_TRUE);

    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_WriteRfr(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, HI_BOOL bEnable)
{

    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U32 u32BitWth = 0;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_8BIT)
    {
        u32BitWth = 0;
    }
    else if (pstFrmCfg->enBitWidth == CBB_BITWIDTH_10BIT)
    {
        u32BitWth = 1;
    }
    else
    {
        CBB_ERRMSG("invalid enPixelFmt\n");
        return HI_FAILURE;
    }

    //VPSS_Mac_SetRfrWidth(pstVpssNode, pstFrmCfg->u32Width);
    //VPSS_Mac_SetRfrWidth(pstVpssNode, pstFrmCfg->u32Height);
    VPSS_Sys_SetRfrPixBitw(pstVpssNode, u32BitWth);

    VPSS_Mac_SetRfryAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_Y);
    VPSS_Mac_SetRfrcAddr(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32PhyAddr_C);
    VPSS_Mac_SetRfryStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y);
    VPSS_Mac_SetRfrcStride(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C);

    if (pstFrmCfg->enBitWidth > CBB_BITWIDTH_8BIT)
    {
        VPSS_Mac_SetRfrDitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetRfrDitherEn(pstVpssNode, HI_FALSE);
    }
    else
    {
        VPSS_Mac_SetRfrDitherMode(pstVpssNode, REG_DITHER_MODE_DITHER);
        VPSS_Mac_SetRfrDitherEn(pstVpssNode, HI_TRUE);
    }

    VPSS_Mac_SetWchRfryBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetWchRfrcBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    VPSS_Sys_SetRfrEn(pstVpssNode, bEnable);

    return HI_SUCCESS;
}

HI_S32 CBB_CfgFrm_WriteCue(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    CBB_FRAME_ADDR_S    *pstAddr;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    pstAddr = &(pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT]);

    VPSS_Mac_SetCueyAddr(pstVpssNode,  pstAddr->u32PhyAddr_Y);
    VPSS_Mac_SetCuecAddr(pstVpssNode, pstAddr->u32PhyAddr_C);
    VPSS_Mac_SetCueyStride(pstVpssNode, pstAddr->u32Stride_Y);
    VPSS_Mac_SetCuecStride(pstVpssNode, pstAddr->u32Stride_C);

    VPSS_Mac_SetWchCueyBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y);
    VPSS_Mac_SetWchCuecBypass(pstVpssNode, pstFrmCfg->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_C);

    return HI_SUCCESS;
}

