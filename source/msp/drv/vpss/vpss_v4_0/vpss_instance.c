#include "vpss_instance.h"
#include "vpss_common.h"
#include "hi_drv_stat.h"
#include "vpss_ctrl.h"
#include "vpss_alg_ratio.h"
#include "hi_reg_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define SAVEYUV 0
#define IMAGEINFO 0


HI_S32 VPSS_INST_UserGetImage(VPSS_HANDLE hVPSS, HI_DRV_VIDEO_FRAME_S *pstImage)
{
    VPSS_INSTANCE_S *pstInstance;

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);

    if (!pstInstance)
    {
        return HI_FAILURE;
    }

    return VPSS_SRCIN_GetImage(&pstInstance->stSrcIn, pstImage);
}

HI_S32 VPSS_INST_UserRelImage(VPSS_HANDLE hVPSS, HI_DRV_VIDEO_FRAME_S *pstImage)
{
    VPSS_INSTANCE_S *pstInstance;

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);

    if (!pstInstance)
    {
        return HI_FAILURE;
    }

    return VPSS_SRCIN_RelImage(&pstInstance->stSrcIn, pstImage);
}

HI_S32 VPSS_INST_SetUserActiveMode(VPSS_INSTANCE_S *pstInstance)
{
    VPSS_INFO("VPSS_INST_SetUserActiveMode.\n");

    pstInstance->eSrcImgMode = VPSS_SOURCE_MODE_USERACTIVE;
    pstInstance->stSrcFuncs.VPSS_GET_SRCIMAGE = VPSS_INST_UserGetImage;
    pstInstance->stSrcFuncs.VPSS_REL_SRCIMAGE = VPSS_INST_UserRelImage;

    (HI_VOID)VPSS_SRCIN_Init(&pstInstance->stSrcIn);

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_RevisePortRect(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;

    VPSS_PORT_S *pstPort;

    HI_CHIP_TYPE_E enChipType;
    HI_CHIP_VERSION_E enChipVersion;


    HI_U32 u32LevelH = 0;
    HI_U32 u32LevelW = 0;

    VPSS_IN_STREAM_INFO_S *pstStreamInfo;

    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);

    if (pstInstance->u32UhdLevelW == VPSS_UHD_HIGH_W
        && pstInstance->u32UhdLevelH == VPSS_UHD_HIGH_H)
    {
        if (atomic_read(&pstInstance->atmUhdFmt) == 0)
        {
            u32LevelW = VPSS_UHD_MIDDLE_W;
            u32LevelH = VPSS_UHD_MIDDLE_H;
        }
        else
        {
            u32LevelW = VPSS_UHD_HIGH_W;
            u32LevelH = VPSS_UHD_HIGH_H;

            HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

            if (enChipType == HI_CHIP_TYPE_HI3798M || enChipType == HI_CHIP_TYPE_HI3796M)
            {
                if (pstStreamInfo->u32InRate >= 25
                    && pstStreamInfo->u32StreamProg == 0)
                {
                    u32LevelW = VPSS_UHD_MIDDLE_W;
                    u32LevelH = VPSS_UHD_MIDDLE_H;
                }
            }
        }
    }
    else
    {
        u32LevelW = VPSS_UHD_LOW_W;
        u32LevelH = VPSS_UHD_LOW_H;
    }

    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            HI_RECT_S stLevelRect = {0};

            {
                HI_S32 s32OriWidth = 0;
                HI_S32 s32OriHeight = 0;
                HI_S32 s32OriARw = 0;
                HI_S32 s32OriARh = 0;
                HI_RECT_S stOriLevel = {0};

                stOriLevel.s32Width = u32LevelW;
                stOriLevel.s32Height = u32LevelH;
                VPSS_INST_LevelRectGetOriRect(pstPort->stLevelOutRect,
                                              stOriLevel,
                                              &s32OriWidth,
                                              &s32OriHeight,
                                              &s32OriARw,
                                              &s32OriARh);

                if (s32OriWidth != 0xffffffff
                    && s32OriHeight != 0xffffffff)
                {
                    pstPort->s32OutputWidth = s32OriWidth;
                    pstPort->s32OutputHeight = s32OriHeight;
                    pstPort->stDispPixAR.u32ARw = s32OriARw;
                    pstPort->stDispPixAR.u32ARh = s32OriARh;
                }
            }

            if ((pstPort->s32OutputWidth > u32LevelW
                 || pstPort->s32OutputHeight > u32LevelH)
#if 0
                && (pstStreamInfo->u32StreamW <= 1920
                    && pstStreamInfo->u32StreamH <= 1080)
#endif
               )
            {
                HI_U32 u32RatioW = 0;
                HI_U32 u32RatioH = 0;
                HI_U32 u32TmpH = 0;
                HI_U32 u32TmpW = 0;

                if (pstPort->s32OutputHeight > u32LevelH)
                {
                    u32RatioW = pstPort->s32OutputWidth * 2048 / u32LevelW;
                    u32RatioH = pstPort->s32OutputHeight * 2048 / u32LevelH;

                    if (u32RatioW > u32RatioH)
                    {
                        u32TmpW = pstPort->s32OutputWidth * 2048 / u32RatioW;
                        u32TmpH = pstPort->s32OutputHeight * 2048 / u32RatioW;
                    }
                    else
                    {
                        u32TmpW = pstPort->s32OutputWidth * 2048 / u32RatioH;
                        u32TmpH = pstPort->s32OutputHeight * 2048 / u32RatioH;
                    }
                }
                else
                {
                    u32TmpW = 1920;
                    u32TmpH = pstPort->s32OutputHeight;
                }

                VPSS_PIXLE_DOWNALIGN_W(u32TmpW, HI_FALSE);
                VPSS_PIXLE_DOWNALIGN_H(u32TmpH, HI_FALSE);

                pstPort->stDispPixAR.u32ARw =
                    (((pstPort->stDispPixAR.u32ARw
                       * pstPort->s32OutputWidth) / u32TmpW )
                     * u32TmpH) / pstPort->s32OutputHeight;


                pstPort->s32OutputWidth = u32TmpW;
                pstPort->s32OutputHeight = u32TmpH;

            }

            {
                stLevelRect.s32Width = u32LevelW;
                stLevelRect.s32Height = u32LevelH;

                VPSS_INST_LevelRectSetReviseRect(pstPort->stLevelOutRect,
                                                 stLevelRect,
                                                 pstPort->s32OutputWidth,
                                                 pstPort->s32OutputHeight,
                                                 pstPort->stDispPixAR.u32ARw,
                                                 pstPort->stDispPixAR.u32ARh);
            }

            if (pstInstance->u32UhdLevelW == VPSS_UHD_HIGH_W
                && pstInstance->u32UhdLevelH == VPSS_UHD_HIGH_H)
            {
                if (atomic_read(&pstInstance->atmUhdFmt) == 0)
                {
                    stLevelRect.s32Width = VPSS_UHD_MIDDLE_W;
                    stLevelRect.s32Height = VPSS_UHD_MIDDLE_H;
                }
                else
                {
                    stLevelRect.s32Width = VPSS_UHD_HIGH_W;
                    stLevelRect.s32Height = VPSS_UHD_HIGH_H;
                }
            }
            else
            {
                stLevelRect.s32Width = VPSS_UHD_LOW_W;
                stLevelRect.s32Height = VPSS_UHD_LOW_H;
            }

            {
                HI_S32 s32ReviseWidth = 0;
                HI_S32 s32ReviseHeight = 0;
                HI_S32 s32ReviseARw = 0;
                HI_S32 s32ReviseARh = 0;

                VPSS_INST_LevelRectGetReviseRect(pstPort->stLevelOutRect,
                                                 stLevelRect,
                                                 &s32ReviseWidth,
                                                 &s32ReviseHeight,
                                                 &s32ReviseARw,
                                                 &s32ReviseARh);

                if (s32ReviseWidth != 0xffffffff
                    && s32ReviseHeight != 0xffffffff)
                {
                    pstPort->s32OutputWidth = s32ReviseWidth;
                    pstPort->s32OutputHeight = s32ReviseHeight;
                    pstPort->stDispPixAR.u32ARw = s32ReviseARw;
                    pstPort->stDispPixAR.u32ARh = s32ReviseARh;
                }
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_RevisePortCmpCfg(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;
    HI_DRV_VPSS_PORT_CFG_S *pstPortCfg;

    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);

    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        pstPortCfg = &(pstInstance->stUsrPortCfg[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            if ( HI_DRV_PIX_FMT_NV21_CMP == pstPortCfg->eFormat)
            {
                pstPort->eFormat = HI_DRV_PIX_FMT_NV21;
            }
            else if ( HI_DRV_PIX_FMT_NV12_CMP == pstPortCfg->eFormat )
            {
                pstPort->eFormat = HI_DRV_PIX_FMT_NV12;
            }
            else if ( HI_DRV_PIX_FMT_NV16_2X1_CMP == pstPortCfg->eFormat)
            {
                pstPort->eFormat = HI_DRV_PIX_FMT_NV16_2X1;
            }
            else if ( HI_DRV_PIX_FMT_NV61_2X1_CMP == pstPortCfg->eFormat)
            {
                pstPort->eFormat = HI_DRV_PIX_FMT_NV61_2X1;
            }
            else if ( HI_DRV_PIX_FMT_NV61_2X1 == pstPortCfg->eFormat
                      || HI_DRV_PIX_FMT_NV16_2X1 == pstPortCfg->eFormat
                      || HI_DRV_PIX_FMT_NV21 == pstPortCfg->eFormat
                      || HI_DRV_PIX_FMT_NV12 == pstPortCfg->eFormat)
            {
                //pstPort->eFormat = HI_DRV_PIX_FMT_NV21;
            }
            else
            {
                VPSS_ERROR("Invalid Port Out Fmt %d\n", pstPortCfg->eFormat);
            }

        }
    }

    return HI_SUCCESS;
}

HI_VOID VPSS_INST_RevisePortOutRect(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;
    HI_DRV_VPSS_PORT_CFG_S *pstPortCfg;
    HI_S32 s32OutRectH;
    HI_S32 s32OutRectW;
    HI_S32 s32OutRectW_new;
    HI_S32 s32OutRectH_new;

    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        pstPortCfg = &(pstInstance->stUsrPortCfg[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            if ((HI_DRV_VPSS_ROTATION_90 == pstPort->enRotation)
                || (HI_DRV_VPSS_ROTATION_270 == pstPort->enRotation)
               )
            {
                s32OutRectW = pstPortCfg->s32OutputWidth;
                s32OutRectH = pstPortCfg->s32OutputHeight;
                VPSS_DBG_INFO("Out cfg W H %d %d Stream W H %d %d \n",
                              s32OutRectW, s32OutRectH, pstStreamInfo->u32StreamW, pstStreamInfo->u32StreamH);
                if (s32OutRectH > VPSS_FHD_WIDTH)
                {
                    s32OutRectH_new = VPSS_FHD_WIDTH;
                    s32OutRectW_new = s32OutRectW * s32OutRectH_new / s32OutRectH;
                    pstPort->s32OutputWidth  = s32OutRectW_new;
                    pstPort->s32OutputHeight = s32OutRectH_new;
                }
                else if ((s32OutRectH == 0) && (pstStreamInfo->u32StreamH > VPSS_FHD_WIDTH))
                {
                    pstPort->s32OutputHeight  = VPSS_FHD_WIDTH;
                    pstPort->s32OutputWidth = pstStreamInfo->u32StreamW * VPSS_FHD_WIDTH / pstStreamInfo->u32StreamH;
                }

                VPSS_PIXLE_DOWNALIGN_W(pstPort->s32OutputWidth, HI_FALSE);
                VPSS_PIXLE_DOWNALIGN_H(pstPort->s32OutputHeight, HI_FALSE);

                VPSS_DBG_INFO("Revise out w h %d %d\n", pstPort->s32OutputWidth, pstPort->s32OutputHeight);
            }
            else if ((HI_DRV_VPSS_ROTATION_180 == pstPort->enRotation)
                     || (HI_TRUE == pstPort->bHoriFlip)
                     || (HI_TRUE == pstPort->bVertFlip)
                    )
            {
                if (pstPort->s32OutputWidth > VPSS_FHD_WIDTH)
                {
                    pstPort->s32OutputWidth  = pstStreamInfo->u32StreamW;
                    pstPort->s32OutputHeight = pstStreamInfo->u32StreamH;
                }
            }
        }
    }

    return;
}

HI_S32 VPSS_INST_RevisePortFormat(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;

    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);

    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            if ((pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV12
                 || pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1
                 || pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE
                 || pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
                && pstPort->eFormat == HI_DRV_PIX_FMT_NV21)
            {
                pstPort->bUVInver = HI_TRUE;
            }
            else if ((pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV21
                      || pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1
                      || pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE
                      || pstStreamInfo->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP)
                     && pstPort->eFormat == HI_DRV_PIX_FMT_NV12)
            {
                pstPort->bUVInver = HI_TRUE;
            }
            else
            {
                pstPort->bUVInver = HI_FALSE;
            }
        }
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_INST_RevisePortOutBitWidth(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_IN_ENTITY_S *pstEntity;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;
    HI_DRV_VPSS_PORT_CFG_S *pstPortCfg;

    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);
    pstEntity = &pstInstance->stInEntity;

    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            pstPortCfg = &(pstInstance->stUsrPortCfg[u32Count]);
            {
                //fix to 8bit output width

                /*
                   only input is 10bit and VO has 10bit processing capacity
                   can vpss output 10bit data!!
                 */
                if (!VPSS_HDR_TYPE_NEED_DETILE_NOALG(pstStreamInfo->eStreamType))
                {
                    if ( pstStreamInfo->enBitWidth >= HI_DRV_PIXEL_BITWIDTH_10BIT &&
                         pstPortCfg->enOutBitWidth >= HI_DRV_PIXEL_BITWIDTH_10BIT)
                    {
                        pstPort->enOutBitWidth = HI_DRV_PIXEL_BITWIDTH_10BIT;
                    }
                    else
                    {
                        pstPort->enOutBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                    }

#if !defined(CHIP_TYPE_hi3798cv200_a) && !defined(CHIP_TYPE_hi3798cv200)
                    if (pstPortCfg->enOutBitWidth == HI_DRV_PIXEL_BITWIDTH_10BIT_CTS)
                    {
                        pstPort->enOutBitWidth = HI_DRV_PIXEL_BITWIDTH_10BIT_CTS;
                    }
#endif
                }
                else
                {
                    pstPort->enOutBitWidth = pstStreamInfo->enBitWidth;
#ifndef VPSS_ZME_SUPPORT_10BIT
                    if ((pstPort->s32OutputWidth != 0)
                        || (pstPort->s32OutputHeight != 0))
                    {
                        pstPort->enOutBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                    }
#endif
                }
                //2D node must output 8bit when rotation is enabled.
                if ((HI_DRV_VPSS_ROTATION_90 == pstPort->enRotation)
                    || (HI_DRV_VPSS_ROTATION_270 == pstPort->enRotation))

                {
                    pstPort->enOutBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                }
            }
        }
    }

    return HI_SUCCESS;
}

#ifdef VPSS_ZME_WIDTH_MAX_FHD
HI_S32 VPSS_INST_RevisePortOutImageWidth(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;
    HI_S32 s32Ret;
    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_IN_INTF_S stInIntf;

    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);
    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }
    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);
    s32Ret = stInIntf.pfnGetProcessImage(&pstInstance->stInEntity, &pstCur);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
        return HI_FAILURE;
    }
    if ((HI_DRV_FT_SBS == pstCur->eFrmType)
        || (HI_DRV_FT_TAB == pstCur->eFrmType))
    {
        for (u32Count = 0;
             u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
             u32Count ++)
        {
            pstPort = &(pstInstance->stPort[u32Count]);
            if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
            {
                if (HI_DRV_FT_SBS == pstCur->eFrmType)
                {
                    if (0 == pstPort->s32OutputWidth)
                    {
                        pstPort->s32OutputWidth = pstCur->u32Width / 2;
                        pstPort->s32OutputHeight = pstCur->u32Height;
                    }
                }
                else
                {
                    if (0 == pstPort->s32OutputHeight)
                    {
                        pstPort->s32OutputHeight = pstCur->u32Height / 2;
                        pstPort->s32OutputWidth = pstCur->u32Width;
                    }
                }
            }
        }
    }
    return HI_SUCCESS;
}
#endif
HI_S32 VPSS_INST_DebugCfg(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_DRV_VPSS_PORT_CFG_S *pstPortCfg;
    HI_U32 u32SrcWH = 0;
#if DEF_VPSS_DEBUG
    {
        VPSS_HANDLE hDbgPart;
        hDbgPart = DEF_DBG_SRC_ID;

        VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                             DBG_SET_I2P,
                             &hDbgPart,
                             &(pstInstance->stInEntity.stDbginfo.bDeiDisable));

        VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                             DBG_SET_FRMRATE,
                             &(pstInstance->stInEntity.stDbginfo.frameEn),
                             &(pstInstance->stInEntity.stDbginfo.framerate));

        VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                             DBG_REVISE_SRC_WH,
                             &(pstInstance->stInEntity.stDbginfo.bImageRevise),
                             &u32SrcWH);

        if (pstInstance->stInEntity.stDbginfo.bImageRevise)
        {
            pstInstance->stInEntity.stDbginfo.u32InputWidth = (u32SrcWH >> 16) & 0xFFFF;
            pstInstance->stInEntity.stDbginfo.u32InputHeight = u32SrcWH & 0xFFFF;
        }
        VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                             DBG_INFO_FRM,
                             &hDbgPart,
                             &(pstInstance->stInEntity.stDbginfo));
    }
#endif

    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        pstPortCfg = &(pstInstance->stUsrPortCfg[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
#if DEF_VPSS_DEBUG
            {
                VPSS_HANDLE hDbgPart;
                switch (((HI_U32)pstPort->s32PortId) & 0x000000ff)
                {
                    case 0:
                        hDbgPart = DEF_DBG_PORT0_ID;
                        break;
                    case 1:
                        hDbgPart = DEF_DBG_PORT1_ID;
                        break;
                    case 2:
                        hDbgPart = DEF_DBG_PORT2_ID;
                        break;
                    default:
                        VPSS_FATAL("Invalid Port ID %#x\n", pstPort->s32PortId);
                        hDbgPart = DEF_DBG_PORT0_ID;
                        break;
                }

                VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                DBG_SET_UV_INVERT,
                &hDbgPart,
                &(pstPort->bUVInver));
                VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                DBG_SET_CMP_ON,
                &hDbgPart,
                &(pstPort->u32cmpflag));
                VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                DBG_SET_CMP_OFF,
                &hDbgPart,
                &(pstPort->u32cmpflag));

                VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                DBG_SET_OUTBITWIDTH,
                &hDbgPart,
                &(pstPort->enOutBitWidth));

                VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                DBG_SET_RATATION,
                &hDbgPart,
                &(pstPort->enRotation));

                VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                DBG_SET_LBX_COLOR,
                &hDbgPart,
                &(pstPort->eLetterBoxColor));

            }
#endif
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_RevisePortRotationDbg(VPSS_INSTANCE_S *pstInstance)
{
    VPSS_HANDLE hDbgPart;
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;

    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            //set rotation before RevisePortOutBitWidth
            switch (((HI_U32)pstPort->s32PortId) & 0x000000ff)
            {
                case 0:
                    hDbgPart = DEF_DBG_PORT0_ID;
                    break;
                case 1:
                    hDbgPart = DEF_DBG_PORT1_ID;
                    break;
                case 2:
                    hDbgPart = DEF_DBG_PORT2_ID;
                    break;
                default:
                    VPSS_FATAL("Invalid Port ID %#x\n", pstPort->s32PortId);
                    return HI_FAILURE;
                    break;
            }

            VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                                 DBG_SET_RATATION,
                                 &hDbgPart,
                                 &(pstPort->enRotation));

        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_SyncUsrCfg(VPSS_INSTANCE_S *pstInstance)
{
    unsigned long flags;
    HI_DRV_VPSS_CFG_S *pstInstUsrcCfg;
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_DRV_VPSS_PORT_CFG_S *pstPortCfg;
    VPSS_IN_ATTR_S stInAttr;

    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    if (pstInstance->bCfgNew)
    {
        pstInstUsrcCfg = &(pstInstance->stUsrInstCfg);

        memset(&stInAttr, 0, sizeof(VPSS_IN_ATTR_S));
        stInAttr.bAlwaysFlushSrc = pstInstUsrcCfg->bAlwaysFlushSrc;
        stInAttr.enProgInfo = pstInstUsrcCfg->enProgInfo;
        stInAttr.bProgRevise = pstInstUsrcCfg->bProgRevise;
        stInAttr.enSrcCS = pstInstUsrcCfg->enSrcCS;
        VPSS_IN_SetAttr(&(pstInstance->stInEntity), stInAttr);

        pstInstance->stProcCtrl = pstInstUsrcCfg->stProcCtrl;

        pstInstance->u32UhdLevelW = pstInstance->u32UhdUsrLevelW;
        pstInstance->u32UhdLevelH = pstInstance->u32UhdUsrLevelH;

        VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
                             DBG_SET_UHD,
                             &pstInstance->u32UhdUsrLevelW,
                             &pstInstance->u32UhdUsrLevelH);

        for (u32Count = 0;
             u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
             u32Count ++)
        {
            pstPort = &(pstInstance->stPort[u32Count]);

            if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
            {
                pstPortCfg = &(pstInstance->stUsrPortCfg[u32Count]);

                pstPort->eFormat = pstPortCfg->eFormat;
                pstPort->s32OutputWidth = pstPortCfg->s32OutputWidth;
                pstPort->s32OutputHeight = pstPortCfg->s32OutputHeight;

                pstPort->eDstCS = pstPortCfg->eDstCS;
                pstPort->stDispPixAR = pstPortCfg->stDispPixAR;
                pstPort->eAspMode = pstPortCfg->eAspMode;
                pstPort->stCustmAR = pstPortCfg->stCustmAR;
                pstPort->stScreen = pstPortCfg->stScreen;
                pstPort->bInterlaced = pstPortCfg->bInterlaced;

                pstPort->bOnlyKeyFrame = pstPortCfg->bOnlyKeyFrame;
                pstPort->bLBDCropEn = pstPortCfg->bLBDCropEn;

                VPSS_INST_LevelRectSetOriRect(pstPort->stLevelOutRect,
                                              pstPort->s32OutputWidth,
                                              pstPort->s32OutputHeight,
                                              pstPort->stDispPixAR.u32ARw,
                                              pstPort->stDispPixAR.u32ARh);

                VPSS_SAFE_MEMCPY(&pstPort->stVideoRect, &pstPortCfg->stVideoRect, sizeof(HI_RECT_S));

                pstPort->bUseCropRect = pstPortCfg->bUseCropRect;
                VPSS_SAFE_MEMCPY(&pstPort->stInRect, &pstPortCfg->stInRect, sizeof(HI_RECT_S));
                VPSS_SAFE_MEMCPY(&pstPort->stCropRect, &pstPortCfg->stCropRect, sizeof(HI_DRV_CROP_RECT_S));

                pstPort->bTunnelEnable = pstPortCfg->bTunnelEnable;
                pstPort->s32SafeThr = pstPortCfg->s32SafeThr;
                pstPort->u32MaxFrameRate = pstPortCfg->u32MaxFrameRate;

                pstPort->b3Dsupport = pstPortCfg->b3Dsupport;
                pstPort->stFrmInfo.stBufListCfg = pstPortCfg->stBufListCfg;
                pstPort->stProcCtrl = pstPortCfg->stProcCtrl;
                pstPort->enRotation = pstPortCfg->enRotation;
                pstPort->bHoriFlip = pstPortCfg->bHoriFlip;
                pstPort->bVertFlip = pstPortCfg->bVertFlip;
                pstPort->bPassThrough = pstPortCfg->bPassThrough;
                pstPort->enOutBitWidth  = pstPortCfg->enOutBitWidth;
            }
        }

        pstInstance->bCfgNew = HI_FALSE;

    }

    //in 3798cv200 ,vpss bypass 4k frame
    //(HI_VOID)VPSS_INST_RevisePortRect(pstInstance);

    //must call this func before VPSS_INST_RevisePortOutBitWidth
    (HI_VOID)VPSS_INST_RevisePortRotationDbg(pstInstance);

    (HI_VOID)VPSS_INST_RevisePortCmpCfg(pstInstance);
    (HI_VOID)VPSS_INST_DebugCfg(pstInstance);

    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);

    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            if (pstPort->stFrmInfo.stBufListCfg.eBufType
                == HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE)
            {
                if (pstPort->b3Dsupport == HI_TRUE)
                {
                    VPSS_FB_AllocExtBuffer(&(pstPort->stFrmInfo),
                                           pstPort->stFrmInfo.stBufListCfg.u32BufNumber);
                }
                else
                {
                    VPSS_FB_AllocExtBuffer(&(pstPort->stFrmInfo), 0);
                }

                VPSS_FB_RlsExtBuffer(&(pstPort->stFrmInfo));
            }
        }
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_INST_SyncUsrCfg_q(VPSS_INSTANCE_S *pstInstance)
{
    unsigned long flags;
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_DRV_VPSS_PORT_CFG_S *pstPortCfg;
    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    for (u32Count = 0;
         u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER;
         u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            pstPortCfg = &(pstInstance->stUsrPortCfg[u32Count]);
            pstPort->bPassThrough = pstPortCfg->bPassThrough;
        }
    }
    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);
    return HI_SUCCESS;
}
VPSS_PORT_S *VPSS_INST_GetPort(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort)
{

    HI_U32 u32PortID;
    VPSS_PORT_S *pstPort;
    u32PortID = PORTHANDLE_TO_PORTID(hPort);

    if (u32PortID >= DEF_HI_DRV_VPSS_PORT_MAX_NUMBER)
    {
        VPSS_FATAL("Invalid PortID %#x.", u32PortID);
        return HI_NULL;
    }

    pstPort = &(pstInstance->stPort[u32PortID]);

    if (pstPort->s32PortId == VPSS_INVALID_HANDLE)
    {
        VPSS_FATAL("Port doesn't Exit.\n");

        pstPort = HI_NULL;
    }

    return pstPort;
}

HI_S32 VPSS_INST_ResetPort(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort)
{
    VPSS_PORT_S *pstPort;
    HI_U32 u32PortID;

    u32PortID = PORTHANDLE_TO_PORTID(hPort);

    pstPort = HI_NULL;

    pstPort = VPSS_INST_GetPort(pstInstance, hPort);
    if (!pstPort)
    {
        return HI_FAILURE;
    }
    pstPort->u32OutCount = 0;
    VPSS_FB_Reset(&(pstPort->stFrmInfo));

    return HI_SUCCESS;

}

HI_S32 VPSS_INST_Reset(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    HI_S32 s32Ret = HI_SUCCESS;
    VPSS_IN_ENTITY_S *pstInEntity;
    VPSS_IN_INTF_S stInIntf;

    VPSS_PORT_S *pstPort;

    VPSS_CHECK_NULL(pstInstance);

    VPSS_CTRL_Pause(pstInstance->ID);

    pstInEntity = &pstInstance->stInEntity;

    s32Ret = VPSS_IN_GetIntf(pstInEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get In Intf Failed\n");
        return HI_FAILURE;
    }

    s32Ret = stInIntf.pfnReset(pstInEntity);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Reset Failed\n");
        return HI_FAILURE;
    }

    /*reset port*/
    VPSS_TRANS_FB_Reset(&(pstInstance->stInEntity.stTransFbInfo));
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            VPSS_INST_ResetPort(pstInstance, pstPort->s32PortId);
        }
    }

    pstInstance->u32CheckRate = 0;
    pstInstance->u32CheckSucRate = 0;
    pstInstance->u32CheckCnt = 0;
    pstInstance->u32CheckSucCnt = 0;
    pstInstance->ulLastCheckTime = 0;

    pstInstance->u32ImgRate = 0;
    pstInstance->u32ImgSucRate = 0;
    pstInstance->u32ImgCnt = 0;
    pstInstance->u32ImgSucCnt = 0;
    pstInstance->u32ImgLastCnt = 0;
    pstInstance->u32ImgLastSucCnt = 0;

    pstInstance->u32BufRate = 0;
    pstInstance->u32BufSucRate = 0;
    pstInstance->u32BufCnt = 0;
    pstInstance->u32BufSucCnt = 0;

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->u32BufLastSucCnt = 0;
    pstInstance->u32LastBufCnt = 0;
    pstInstance->u32LogicTimeoutCnt = 0;
    pstInstance->u32TimeStampIndex = 0;
    pstInstance->u32LogicClock = 0xFFFFFFFF;
    for (u32Count = 0; u32Count < VPSS_PROC_TIMESTAMP_MAXCNT; u32Count++)
    {
        pstInstance->aulCreatTime[u32Count] = 0;
        pstInstance->aulLogicStartTime[u32Count] = 0;
        pstInstance->aulTunnelOutTime[u32Count] = 0;
        pstInstance->aulLogicEndTime[u32Count] = 0;
        pstInstance->aulThreadWakeUpTunnel[u32Count] = 0;
        pstInstance->aulThreadWakeUpAll[u32Count] = 0;
        pstInstance->aulPQAlgStartTime[u32Count] = 0;
        pstInstance->aulPQAlgEndTime[u32Count] = 0;
        pstInstance->aulFinishTime[u32Count] = 0;
        pstInstance->u32LogicTick[u32Count] = 0;
    }
#endif

    pstInstance->u32ScenceChgCnt = 0;
    VPSS_CTRL_Resume(pstInstance->ID);

    return HI_SUCCESS;
}

HI_BOOL VPSS_INST_CheckAllDone(VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s2Ret = HI_FAILURE;
    VPSS_PORT_S *pstPort;
    VPSS_FB_INFO_S *pstFrmListInfo;
    VPSS_SRC_DATA_S *pstData = HI_NULL;
    HI_U32 u32Count;
    HI_BOOL bDone;
    unsigned long flags;
    VPSS_IN_ENTITY_S *pstInEntity;
    VPSS_IN_INTF_S stInIntf = {0};

    pstInEntity = &pstInstance->stInEntity;

    s2Ret = VPSS_IN_GetIntf(pstInEntity, &stInIntf);
    if (HI_SUCCESS != s2Ret)
    {
        VPSS_ERROR("Get In Intf Failed\n");
        return HI_FALSE;
    }

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);
    // TODO:�˴�����ֵ������
    /*
     *check image all done
     */
    s2Ret = stInIntf.pfnGetProcessImage(pstInEntity, &pstData);
    if (HI_SUCCESS == s2Ret)
    {
        return HI_FALSE;
    }

    /*
     *check all outframe acquired
     */
    bDone = HI_TRUE;
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            pstFrmListInfo = &(pstPort->stFrmInfo);
            VPSS_OSAL_DownSpin(&(pstFrmListInfo->stFulBufSpin), &flags);
            if (pstFrmListInfo->pstTarget_1 != pstFrmListInfo->stFulFrmList.prev)
            {
                bDone = HI_FALSE;
            }
            VPSS_OSAL_UpSpin(&(pstFrmListInfo->stFulBufSpin), &flags);
        }
    }

    return bDone;
}

HI_BOOL VPSS_INST_CheckPortBuffer(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort)
{
    VPSS_PORT_S *pstPort;
    VPSS_FB_INFO_S *pstFrmListInfo;
    HI_BOOL bAvailable = HI_FALSE;
    VPSS_FB_NODE_S *pstFrmNode;
    HI_DRV_VIDEO_FRAME_S *pstFrm;
    LIST *pstNextNode;
    unsigned long flags;
    pstPort = HI_NULL;

    pstPort = VPSS_INST_GetPort(pstInstance, hPort);

    if (!pstPort)
    {
        return HI_FALSE;
    }
    pstFrmListInfo = &(pstPort->stFrmInfo);
    VPSS_OSAL_DownSpin(&(pstFrmListInfo->stFulBufSpin), &flags);

    pstNextNode = (pstFrmListInfo->pstTarget_1)->next;
    if (pstNextNode != &(pstFrmListInfo->stFulFrmList))
    {
        pstFrmNode = list_entry(pstNextNode,
                                VPSS_FB_NODE_S, node);
        pstFrm = &(pstFrmNode->stOutFrame);

        if (pstFrm->eFrmType == HI_DRV_FT_NOT_STEREO)
        {
            bAvailable = HI_TRUE;
        }
        else
        {
            if (pstNextNode->next != &(pstFrmListInfo->stFulFrmList))
            {
                bAvailable = HI_TRUE;
            }
            else
            {
                bAvailable = HI_FALSE;
            }
        }
    }
    else
    {
        bAvailable = HI_FALSE;
    }
    VPSS_OSAL_UpSpin(&(pstFrmListInfo->stFulBufSpin), &flags);

    return bAvailable;
}

HI_S32 VPSS_INST_SetState(VPSS_INSTANCE_S *pstInstance, VPSS_INSTANCE_STATE_E enState)
{
    //VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
    pstInstance->enState = enState;
    //VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
    return HI_SUCCESS;
}

HI_S32 VPSS_INST_Init(VPSS_INSTANCE_S *pstInstance, HI_DRV_VPSS_CFG_S *pstVpssCfg)
{
    HI_DRV_VPSS_CFG_S stTmpCfg;
    VPSS_IN_ENV_S stInEnv;
    HI_U32 u32Count;
    HI_S32 s32Ret;
    HI_U32 u32MemSize = 0;

    memset(pstInstance, 0, sizeof(VPSS_INSTANCE_S));

    VPSS_OSAL_InitLOCK(&(pstInstance->stInstLock), 1);
    VPSS_OSAL_InitSpin(&(pstInstance->stUsrSetSpin));

    pstInstance->ID = 0;
    pstInstance->hDst = 0;
    pstInstance->pfUserCallBack = HI_NULL;
    pstInstance->eSrcImgMode = VPSS_SOURCE_MODE_BUTT;
    pstInstance->stSrcFuncs.VPSS_GET_SRCIMAGE = HI_NULL;
    pstInstance->stSrcFuncs.VPSS_REL_SRCIMAGE = HI_NULL;
    pstInstance->u32ScenceChgCnt = 0;

    atomic_set(&(pstInstance->atmUhdFmt), 1);
    s32Ret = VPSS_OSAL_GetSysMemSize(&u32MemSize);
    if (HI_SUCCESS == s32Ret)
    {
        if (u32MemSize == VPSS_SYS_MEM_MIN)
        {
            pstInstance->u32UhdLevelW = VPSS_UHD_LOW_W;
            pstInstance->u32UhdLevelH = VPSS_UHD_LOW_H;
        }
        else
        {
            pstInstance->u32UhdLevelW = VPSS_UHD_HIGH_W;
            pstInstance->u32UhdLevelH = VPSS_UHD_HIGH_H;
        }
    }
    else
    {
        pstInstance->u32UhdLevelW = VPSS_UHD_MIDDLE_W;
        pstInstance->u32UhdLevelH = VPSS_UHD_MIDDLE_H;
    }

    pstInstance->u32UhdUsrLevelW = pstInstance->u32UhdLevelW;
    pstInstance->u32UhdUsrLevelH = pstInstance->u32UhdLevelH;

    memset(&stInEnv, 0, sizeof(VPSS_IN_ENV_S));
    memset(&(pstInstance->enCapability), 0, sizeof(VPSS_CAPABILITY_U));

    (HI_VOID)VPSS_OSAL_GetVpssVersion(&(stInEnv.enVersion), &(stInEnv.enCapability));

    stInEnv.enVersion = VPSS_VERSION_V4_0;
    stInEnv.enCapability.u32 = 0x0;
    pstInstance->enCapability = stInEnv.enCapability;

    VPSS_RWZB_Init(&(pstInstance->stRwzbInfo));


    VPSS_DBG_DbgInit(&(pstInstance->stDbgCtrl));

    if (HI_NULL == pstVpssCfg)
    {
        VPSS_INST_GetDefInstCfg(&stTmpCfg);
        pstInstance->bSecure = stTmpCfg.bSecure;
    }
    else
    {
        pstInstance->bSecure = pstVpssCfg->bSecure;
    }

    stInEnv.bSecure = pstInstance->bSecure;

    s32Ret = VPSS_IN_Init(&(pstInstance->stInEntity), stInEnv);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Vpss Init Error\n");
        return HI_FAILURE;
    }


    memset(&(pstInstance->stPort), 0,
           sizeof(VPSS_PORT_S)*DEF_HI_DRV_VPSS_PORT_MAX_NUMBER);
    u32Count = 0;
    while (u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER)
    {
        pstInstance->stPort[u32Count].s32PortId = VPSS_INVALID_HANDLE;
        pstInstance->stPort[u32Count].bEnble = HI_FALSE;
        u32Count++;
    }

    if (HI_NULL == pstVpssCfg)
    {
        VPSS_INST_GetDefInstCfg(&stTmpCfg);
        VPSS_INST_SetInstCfg(pstInstance, &stTmpCfg);
    }
    else
    {
        VPSS_INST_SetInstCfg(pstInstance, pstVpssCfg);
    }

    VPSS_TRANS_FB_Init(&(pstInstance->stInEntity.stTransFbInfo), pstInstance);
    return HI_SUCCESS;
}

HI_S32 VPSS_INST_CompleteImage(VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32Ret;
    VPSS_IN_INTF_S stInIntf;

    VPSS_IN_ENTITY_S *pstEntity;

    pstEntity = &pstInstance->stInEntity;

    s32Ret = VPSS_IN_GetIntf(pstEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get In Intf Failed\n");
        return HI_FAILURE;
    }

    stInIntf.pfnCompleteImage(pstEntity);


    return HI_SUCCESS;
}

HI_S32 VPSS_INST_DelInit(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_IN_ENTITY_S *pstInEntity;
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_IN_INTF_S stInIntf;

    VPSS_CHECK_NULL(pstInstance);

    if (pstInstance->eSrcImgMode == VPSS_SOURCE_MODE_USERACTIVE)
    {
        VPSS_SRCIN_DeInit(&pstInstance->stSrcIn);
    }

    pstInEntity = &pstInstance->stInEntity;

    s32Ret = VPSS_IN_GetIntf(pstInEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get In Intf Failed\n");
        return HI_FAILURE;
    }

    s32Ret = stInIntf.pfnReset(pstInEntity);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Reset Failed\n");
        return HI_FAILURE;
    }
    VPSS_RWZB_DeInit(&(pstInstance->stRwzbInfo));

    s32Ret = VPSS_IN_DeInit(&(pstInstance->stInEntity));
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Vpss In DeInit Error");
        return HI_FAILURE;
    }

    VPSS_TRANS_FB_Reset(&(pstInstance->stInEntity.stTransFbInfo));

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            VPSS_INST_DestoryPort(pstInstance, pstPort->s32PortId);

            pstPort->s32PortId = VPSS_INVALID_HANDLE;
        }
    }

    VPSS_DBG_DbgDeInit(&(pstInstance->stDbgCtrl));

    VPSS_TRANS_FB_DeInit(&(pstInstance->stInEntity.stTransFbInfo));

    (HI_VOID)DRV_PQ_UpdateVpssPQ(pstInstance->ID, HI_NULL, HI_NULL, HI_NULL, HI_NULL);

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_GetDefInstCfg(HI_DRV_VPSS_CFG_S *pstVpssCfg)
{
    HI_DRV_VPSS_PROCESS_S *pstProcCtrl;

    pstVpssCfg->s32Priority = 0;

    pstVpssCfg->bAlwaysFlushSrc = HI_FALSE;

    pstVpssCfg->enProgInfo = HI_DRV_VPSS_PRODETECT_AUTO;
    pstVpssCfg->bProgRevise = HI_TRUE;
    pstVpssCfg->bSecure = HI_FALSE;
    pstVpssCfg->enSceneMode = HI_DRV_VPSS_SCENE_MODE_NORMAL;
    pstVpssCfg->enSrcCS = HI_DRV_CS_UNKNOWN;

    pstProcCtrl = &(pstVpssCfg->stProcCtrl);
    pstProcCtrl->eACC = HI_DRV_VPSS_ACC_DISABLE;
    pstProcCtrl->eACM = HI_DRV_VPSS_ACM_DISABLE;
    pstProcCtrl->eDR = HI_DRV_VPSS_DR_AUTO;
    pstProcCtrl->eDB = HI_DRV_VPSS_DB_AUTO;
    pstProcCtrl->eHFlip = HI_DRV_VPSS_HFLIP_DISABLE;
    pstProcCtrl->eVFlip = HI_DRV_VPSS_VFLIP_DISABLE;
    pstProcCtrl->eCC = HI_DRV_VPSS_CC_AUTO;
    pstProcCtrl->eDEI = HI_DRV_VPSS_DIE_5FIELD;
    pstProcCtrl->eRotation = HI_DRV_VPSS_ROTATION_DISABLE;
    pstProcCtrl->eSharpness = HI_DRV_VPSS_SHARPNESS_AUTO;
    pstProcCtrl->eStereo = HI_DRV_VPSS_STEREO_DISABLE;
    pstProcCtrl->bIFMD = HI_TRUE;

    pstProcCtrl->stInRect.s32X  = 0;
    pstProcCtrl->stInRect.s32Y  = 0;
    pstProcCtrl->stInRect.s32Height = 0;
    pstProcCtrl->stInRect.s32Width = 0;

    pstProcCtrl->bUseCropRect = HI_FALSE;
    pstProcCtrl->stCropRect.u32LeftOffset = 0;
    pstProcCtrl->stCropRect.u32RightOffset = 0;
    pstProcCtrl->stCropRect.u32TopOffset  = 0;
    pstProcCtrl->stCropRect.u32BottomOffset = 0;

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_SetInstCfg(VPSS_INSTANCE_S *pstInstance,
                            HI_DRV_VPSS_CFG_S *pstVpssCfg)
{
    unsigned long flags;
    HI_DRV_VPSS_CFG_S *pstInstUsrcCfg;

    pstInstUsrcCfg = &(pstInstance->stUsrInstCfg);

    //VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    pstInstance->bCfgNew = HI_TRUE;
    if (pstInstance->enState == INSTANCE_STATE_STOP)
    {
        pstInstance->bTvpFirstCfg = HI_TRUE;
    }
    VPSS_SAFE_MEMCPY(pstInstUsrcCfg, pstVpssCfg, sizeof(HI_DRV_VPSS_CFG_S));
    //VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);

    return HI_SUCCESS;
}

HI_U32 VPSS_INST_GetInstCfg(VPSS_INSTANCE_S *pstInstance,
                            HI_DRV_VPSS_CFG_S *pstVpssCfg)
{
    unsigned long flags;
    HI_DRV_VPSS_CFG_S *pstInstUsrcCfg;
    pstInstUsrcCfg = &(pstInstance->stUsrInstCfg);

    //VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    pstVpssCfg->s32Priority = pstInstUsrcCfg->s32Priority;
    pstVpssCfg->bAlwaysFlushSrc = pstInstUsrcCfg->bAlwaysFlushSrc;
    pstVpssCfg->enProgInfo = pstInstUsrcCfg->enProgInfo;
    pstVpssCfg->bProgRevise = pstInstUsrcCfg->bProgRevise;
    pstVpssCfg->enSrcCS = pstInstUsrcCfg->enSrcCS;
    pstVpssCfg->bSecure = pstInstUsrcCfg->bSecure;
    pstVpssCfg->enSceneMode = pstInstUsrcCfg->enSceneMode;
    VPSS_SAFE_MEMCPY(&(pstVpssCfg->stProcCtrl), &(pstInstUsrcCfg->stProcCtrl),
                     sizeof(HI_DRV_VPSS_PROCESS_S));
    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);
    //VPSS_OSAL_UpLock(&(pstInstance->stInstLock));

    return HI_SUCCESS;
}

HI_U32 VPSS_INST_GetDefPortCfg(HI_DRV_VPSS_PORT_CFG_S *pstPortCfg)
{
    memset(pstPortCfg, 0, sizeof(HI_DRV_VPSS_PORT_CFG_S));

    pstPortCfg->bTunnelEnable = HI_FALSE;
    pstPortCfg->s32SafeThr = 100;

    pstPortCfg->bOnlyKeyFrame = HI_FALSE;
    pstPortCfg->bLBDCropEn = HI_FALSE;
    pstPortCfg->stVideoRect.s32X = 0;
    pstPortCfg->stVideoRect.s32Y = 0;
    pstPortCfg->stVideoRect.s32Width  = 0;
    pstPortCfg->stVideoRect.s32Height = 0;

    pstPortCfg->stInRect.s32X  = 0;
    pstPortCfg->stInRect.s32Y  = 0;
    pstPortCfg->stInRect.s32Height = 0;
    pstPortCfg->stInRect.s32Width = 0;

    pstPortCfg->bUseCropRect = HI_FALSE;
    pstPortCfg->stCropRect.u32LeftOffset = 0;
    pstPortCfg->stCropRect.u32RightOffset = 0;
    pstPortCfg->stCropRect.u32TopOffset  = 0;
    pstPortCfg->stCropRect.u32BottomOffset = 0;

    pstPortCfg->s32OutputWidth = 0;
    pstPortCfg->s32OutputHeight = 0;

    pstPortCfg->stScreen.s32Height = 576;
    pstPortCfg->stScreen.s32Width = 720;
    pstPortCfg->stScreen.s32X = 0;
    pstPortCfg->stScreen.s32Y = 0;
    pstPortCfg->stDispPixAR.u32ARh = 0;
    pstPortCfg->stDispPixAR.u32ARw = 0;
    pstPortCfg->stCustmAR.u32ARh = 0;
    pstPortCfg->stCustmAR.u32ARw = 0;

    pstPortCfg->eDstCS = HI_DRV_CS_BUTT;
    pstPortCfg->eAspMode  = HI_DRV_ASP_RAT_MODE_FULL;
    pstPortCfg->stProcCtrl.eCSC = HI_DRV_VPSS_CSC_AUTO;
    pstPortCfg->stProcCtrl.eFidelity = HI_DRV_VPSS_FIDELITY_DISABLE;

    pstPortCfg->eFormat = HI_DRV_PIX_FMT_NV21;
    pstPortCfg->u32MaxFrameRate = 60;

    pstPortCfg->stBufListCfg.eBufType = HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE;
    pstPortCfg->stBufListCfg.u32BufNumber = HI_VPSS_MAX_BUFFER_NUMB;
    //pstPortCfg->stBufListCfg.u32BufSize = 720*576*2;
    //pstPortCfg->stBufListCfg.u32BufStride = 720;

    pstPortCfg->stBufListCfg.u32BufSize = 1920 * 1080 * 2;
    pstPortCfg->stBufListCfg.u32BufStride = 1920;

    pstPortCfg->b3Dsupport = HI_FALSE;
    pstPortCfg->enRotation = HI_DRV_VPSS_ROTATION_DISABLE;
    pstPortCfg->bHoriFlip = HI_FALSE;
    pstPortCfg->bVertFlip = HI_FALSE;
    pstPortCfg->bPassThrough = HI_FALSE;
    //  pstPortCfg->bPassThrough = HI_TRUE;

    pstPortCfg->enOutBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_CreatePort(VPSS_INSTANCE_S *pstInstance,
                            HI_DRV_VPSS_PORT_CFG_S *pstPortCfg,
                            VPSS_HANDLE *phPort)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_S32 s32Ret;

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count ++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId == VPSS_INVALID_HANDLE)
        {
            break;
        }
    }

    if (u32Count == DEF_HI_DRV_VPSS_PORT_MAX_NUMBER)
    {
        VPSS_FATAL("Port Number is MAX.\n");

        *phPort = 0;
        return HI_FAILURE;
    }
    else
    {
        HI_DRV_VPSS_PORT_CFG_S stPortDefCfg;
        HI_DRV_VPSS_PORT_CFG_S *pstPortSetCfg;
        memset(pstPort, 0, sizeof(VPSS_PORT_S));

        if (pstPortCfg == HI_NULL)
        {
            VPSS_INST_GetDefPortCfg(&(stPortDefCfg));
            pstPortSetCfg = &(stPortDefCfg);
        }
        else
        {
            pstPortSetCfg = pstPortCfg;
        }

        s32Ret = VPSS_FB_Init(&(pstPort->stFrmInfo), &(pstPortSetCfg->stBufListCfg));
        if (s32Ret == HI_FAILURE)
        {
            return HI_FAILURE;
        }
        pstPort->bEnble = HI_FALSE;
        pstPort->s32PortId = (pstInstance->ID * 256) + u32Count;
        pstPort->u32OutCount = 0;

        VPSS_INST_LevelRectInit(pstPort->stLevelOutRect);

        VPSS_INST_SetPortCfg(pstInstance, pstPort->s32PortId, pstPortSetCfg);

        *phPort = pstPort->s32PortId;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_DestoryPort(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort)
{
    VPSS_PORT_S *pstPort;
    HI_U32 u32PortID;

    u32PortID = PORTHANDLE_TO_PORTID(hPort);

    pstPort = HI_NULL;

    pstPort = VPSS_INST_GetPort(pstInstance, hPort);
    if (!pstPort)
    {
        VPSS_FATAL("Invalid PortID %#x.", hPort);
        return HI_FAILURE;
    }

    //    msleep(100);/*��ʱ����ͷ�buffer���жϴ�ϵ����*/
    VPSS_TRANS_FB_Reset(&(pstInstance->stInEntity.stTransFbInfo));

    VPSS_FB_DelInit(&(pstPort->stFrmInfo));

    memset(pstPort, 0, sizeof(VPSS_PORT_S));

    pstPort->s32PortId = VPSS_INVALID_HANDLE;

    return HI_SUCCESS;

}

HI_S32 VPSS_INST_CheckPortCfg(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort,
                              HI_DRV_VPSS_PORT_CFG_S *pstVpssPortCfg)
{
    VPSS_PORT_S *pstPort;
    HI_DRV_VPSS_PORT_PROCESS_S *pstProcCtrl;
    pstPort = HI_NULL;

    pstPort = VPSS_INST_GetPort(pstInstance, hPort);

    if (!pstPort)
    {
        return HI_FAILURE;
    }

    pstProcCtrl = &(pstVpssPortCfg->stProcCtrl);

    if (pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV12
        || pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV16_2X1
        || pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV21
        || pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV61_2X1
        || pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV16_2X1_CMP
        || pstVpssPortCfg->eFormat == HI_DRV_PIX_FMT_NV61_2X1_CMP)
    {

    }
    else
    {
        VPSS_FATAL("Invalid Port eFormat %d\n", pstVpssPortCfg->eFormat);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_INST_GetPortCfg(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort,
                            HI_DRV_VPSS_PORT_CFG_S *pstPortCfg)
{
    unsigned long flags;
    VPSS_PORT_S *pstPort;
    HI_U32 u32PortID;
    HI_DRV_VPSS_PORT_CFG_S *pstUsrPortCfg;
    pstPort = HI_NULL;
    pstPort = VPSS_INST_GetPort(pstInstance, hPort);
    if (!pstPort)
    {
        return HI_FAILURE;
    }

    u32PortID = PORTHANDLE_TO_PORTID(hPort);
    if (u32PortID >= DEF_HI_DRV_VPSS_PORT_MAX_NUMBER)
    {
        VPSS_FATAL("Invalid PortID %#x.", u32PortID);
        return HI_FAILURE;
    }

    //VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    pstUsrPortCfg = &(pstInstance->stUsrPortCfg[u32PortID]);
    VPSS_SAFE_MEMCPY(pstPortCfg, pstUsrPortCfg, sizeof(HI_DRV_VPSS_PORT_CFG_S));
    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);
    //VPSS_OSAL_UpLock(&(pstInstance->stInstLock));

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_SetPortCfg(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort,
                            HI_DRV_VPSS_PORT_CFG_S *pstPortCfg)
{
    unsigned long flags;
    VPSS_PORT_S *pstPort;
    HI_U32 u32PortID;
    HI_DRV_VPSS_PORT_CFG_S *pstUsrPortCfg;
    pstPort = HI_NULL;
    pstPort = VPSS_INST_GetPort(pstInstance, hPort);
    if (!pstPort)
    {
        return HI_FAILURE;
    }

    u32PortID = PORTHANDLE_TO_PORTID(hPort);
    if (u32PortID >= DEF_HI_DRV_VPSS_PORT_MAX_NUMBER)
    {
        VPSS_FATAL("Invalid PortID %#x.", u32PortID);
        return HI_FAILURE;
    }

    //VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    pstInstance->bCfgNew = HI_TRUE;
    pstUsrPortCfg = &(pstInstance->stUsrPortCfg[u32PortID]);
    VPSS_SAFE_MEMCPY(pstUsrPortCfg, pstPortCfg, sizeof(HI_DRV_VPSS_PORT_CFG_S));
    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);
    VPSS_INST_SyncUsrCfg_q(pstInstance);
    if (VPSS_INST_CheckPassThroughForOMX(pstInstance, HI_NULL))
    {
        pstInstance->stInEntity.stTransFbInfo.bNeedTrans = HI_TRUE;
    }
    else
    {
        pstInstance->stInEntity.stTransFbInfo.bNeedTrans = HI_FALSE;
    }
    //VPSS_OSAL_UpLock(&(pstInstance->stInstLock));

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_EnablePort(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort, HI_BOOL bEnPort)
{
    VPSS_PORT_S *pstPort;

    pstPort = HI_NULL;

    pstPort = VPSS_INST_GetPort(pstInstance, hPort);

    if (!pstPort)
    {
        return HI_FAILURE;
    }

    pstPort->bEnble = bEnPort;

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_ReplyUserCommand(VPSS_INSTANCE_S *pstInstance,
                                  HI_DRV_VPSS_USER_COMMAND_E eCommand,
                                  HI_VOID *pArgs)
{
    HI_BOOL *pbAllDone;
    HI_BOOL *pbStorePriv;
    HI_BOOL bVpu;
    HI_DRV_VPSS_PORT_AVAILABLE_S *pstAvailable;
    HI_DRV_VPSS_IPMODE_E enIpmode = HI_DRV_VPSS_IPMODE_AUTO;
    HI_DRV_VPSS_BYPASSATTR_S *pstBypassInfo;
    VPSS_CHECK_NULL(pstInstance);
    switch ( eCommand )
    {
        case HI_DRV_VPSS_USER_COMMAND_RESET:
            VPSS_INST_Reset(pstInstance);
            break;
        case HI_DRV_VPSS_USER_COMMAND_CHECKALLDONE:
            VPSS_CHECK_NULL(pArgs);
            pbAllDone = (HI_BOOL *)pArgs;
            *pbAllDone = VPSS_INST_CheckAllDone(pstInstance);
            break;
        case HI_DRV_VPSS_USER_COMMAND_CHECKBYPASS:
            VPSS_CHECK_NULL(pArgs);
            pstBypassInfo = (HI_DRV_VPSS_BYPASSATTR_S *)pArgs;
#if DEF_VPSS_ANDROID_BYPASS
            if (HI_TRUE == pstInstance->stInEntity.stTransFbInfo.bNeedTrans)
            {
                if (pstBypassInfo->u32InputWidth > 1920)
                {
                    pstBypassInfo->bVpssBypass =  HI_TRUE;
                }
                else
                {
                    pstBypassInfo->bVpssBypass =  HI_FALSE;
                }
            }
            else
            {
                pstBypassInfo->bVpssBypass =  HI_FALSE;
            }
#else
            pstBypassInfo->bVpssBypass = HI_FALSE;
#endif
            break;
        case HI_DRV_VPSS_USER_COMMAND_CHECKAVAILABLE:
            VPSS_CHECK_NULL(pArgs);
            pstAvailable = (HI_DRV_VPSS_PORT_AVAILABLE_S *)pArgs;
            pstAvailable->bAvailable
                = VPSS_INST_CheckPortBuffer(pstInstance, pstAvailable->hPort);
            break;
        case HI_DRV_VPSS_USER_COMMAND_START:
            (HI_VOID)VPSS_INST_SetState(pstInstance, INSTANCE_STATE_WORING);
            break;
        case HI_DRV_VPSS_USER_COMMAND_STOP:
            (HI_VOID)VPSS_INST_SetState(pstInstance, INSTANCE_STATE_STOP);
            break;
        case HI_DRV_VPSS_USER_COMMAND_CHANGEIP:
            VPSS_CHECK_NULL(pArgs);
            bVpu = *(HI_BOOL *)pArgs;
            enIpmode = (bVpu == HI_TRUE) ? HI_DRV_VPSS_IPMODE_IP0 : HI_DRV_VPSS_IPMODE_IP1;
            VPSS_CTRL_SyncDistributeIP(pstInstance, enIpmode);
            break;
        case HI_DRV_VPSS_USER_COMMAND_STOREPRIV:
            VPSS_CHECK_NULL(pArgs);
            pbStorePriv = (HI_BOOL *)pArgs;
            (HI_VOID)VPSS_INST_EnableStorePriv(pstInstance, *pbStorePriv);
            break;
#if 0
        case HI_DRV_VPSS_USER_COMMAND_UHD_LOW:

            VPSS_INST_SetUhdLevel(pstInstance, VPSS_UHD_LOW_W, VPSS_UHD_LOW_H);
            break;
        case HI_DRV_VPSS_USER_COMMAND_UHD_MIDDLE:
            VPSS_INST_SetUhdLevel(pstInstance, VPSS_UHD_MIDDLE_W, VPSS_UHD_MIDDLE_H);
            break;
        case HI_DRV_VPSS_USER_COMMAND_UHD_HIGH:
            VPSS_INST_SetUhdLevel(pstInstance, VPSS_UHD_HIGH_W, VPSS_UHD_HIGH_H);
            break;
#endif
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_GetPortFrame(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    VPSS_PORT_S *pstPort;
    VPSS_FB_INFO_S *pstFrameList;
    HI_U32 u32PortID;
    HI_S32 s32Ret;
    HI_CHAR *pchFile = HI_NULL;

    u32PortID = PORTHANDLE_TO_PORTID(hPort);

    if (u32PortID >= DEF_HI_DRV_VPSS_PORT_MAX_NUMBER)
    {
        VPSS_FATAL("Invalid PortID %#x.", u32PortID);
        return HI_FAILURE;
    }

    pstPort = HI_NULL;
    pstPort = VPSS_INST_GetPort(pstInstance, hPort);

    if (!pstPort)
    {
        return HI_FAILURE;
    }


    pstFrameList = &(pstPort->stFrmInfo);

    s32Ret = VPSS_FB_GetFulFrmBuf(pstFrameList, pstFrame, pchFile);

    if (s32Ret == HI_SUCCESS)
    {
#if DEF_VPSS_DEBUG
        {
            VPSS_HANDLE hDbgPart;
            switch (((HI_U32)pstPort->s32PortId) & 0x000000ff)
            {
                case 0:
                    hDbgPart = DEF_DBG_PORT0_ID;
                    break;
                case 1:
                    hDbgPart = DEF_DBG_PORT1_ID;
                    break;
                case 2:
                    hDbgPart = DEF_DBG_PORT2_ID;
                    break;
                default:
                    VPSS_FATAL("Invalid Port ID %#x\n", pstPort->s32PortId);
                    hDbgPart = DEF_DBG_PORT0_ID;
                    break;
            }
            VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
            DBG_INFO_FRM,
            &hDbgPart,
            pstFrame);

            VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
            DBG_W_YUV,
            &hDbgPart,
            pstFrame);
            VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
            DBG_W_YUV_IDX,
            &hDbgPart,
            pstFrame);
            VPSS_DBG_ReplyDbgCmd(&(pstInstance->stDbgCtrl),
            DBG_W_YUV_FILE,
            &hDbgPart,
            pstFrame);
        }
#endif
    }
    return s32Ret;
}

HI_S32 VPSS_INST_RelPortFrame(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    VPSS_PORT_S *pstPort;
    VPSS_FB_INFO_S *pstFrameList;
#if (defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200))
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
#endif
    HI_S32 s32Ret;

    pstPort = HI_NULL;
    pstPort = VPSS_INST_GetPort(pstInstance, hPort);

    if (!pstPort)
    {
        return HI_FAILURE;
    }
    pstFrameList = &(pstPort->stFrmInfo);

    if (pstFrameList->stBufListCfg.eBufType == HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE
        || pstFrameList->stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_VPSS_MANAGE)
    {

    }
    else
    {
        VPSS_FATAL("Buffer type don't support RelPortFrame\n");
        return HI_FAILURE;
    }


    //4K@60 DTV
    //if(VPSS_TRANS_FB_NeedTrans(&(pstInstance->stInEntity.stTransFbInfo),pstFrame))
#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a) || defined(CHIP_TYPE_hi3796mv200)
    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstFrame->u32Priv;
    if (pstPriv->bByPassVpss == HI_TRUE)
    {
        if (0)
        {
            HI_U8 chFile[256] = "vpss_trans_frm_out.yuv";
            VPSS_OSAL_WRITEYUV(pstFrame, chFile);
        }

        s32Ret = VPSS_FB_RelFulFrmBufNoMmz(pstFrameList, pstFrame);
        s32Ret |= VPSS_TRANS_FB_RelImage(&(pstInstance->stInEntity.stTransFbInfo), pstFrame);
    }
    else
    {
        s32Ret = VPSS_FB_RelFulFrmBuf(pstFrameList, pstFrame);
    }
#else
    s32Ret = VPSS_FB_RelFulFrmBuf(pstFrameList, pstFrame);
#endif

    return s32Ret;
}

HI_S32 VPSS_INST_SetCallBack(VPSS_INSTANCE_S *pstInstance,
                             HI_HANDLE hDst, PFN_VPSS_CALLBACK pfVpssCallback)
{
    pstInstance->hDst = hDst;
    if (pfVpssCallback != HI_NULL)
    {
        pstInstance->pfUserCallBack = pfVpssCallback;

        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }

}

HI_S32 VPSS_INST_GetPortListState(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort, HI_DRV_VPSS_PORT_BUFLIST_STATE_S *pstListState)
{
    VPSS_PORT_S *pstPort;
    VPSS_FB_INFO_S *pstFrameList;
    VPSS_FB_STATE_S stFbState;
    HI_S32 s32Ret;

    pstPort = HI_NULL;
    pstPort = VPSS_INST_GetPort(pstInstance, hPort);

    if (!pstPort)
    {
        return HI_FAILURE;
    }
    pstFrameList = &(pstPort->stFrmInfo);

    s32Ret = VPSS_FB_GetState(pstFrameList, &(stFbState));

    if (HI_SUCCESS == s32Ret)
    {
        pstListState->u32TotalBufNumber = stFbState.u32TotalNumb;
        pstListState->u32FulBufNumber = stFbState.u32FulListNumb;
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_GetUserImage(VPSS_INSTANCE_S *pstInstance,
                              HI_DRV_VIDEO_FRAME_S *pstSrcImage)
{
    HI_S32 s32Ret = HI_FAILURE;
    PFN_VPSS_SRC_FUNC  pfUsrCallBack;

    pfUsrCallBack = pstInstance->stSrcFuncs.VPSS_GET_SRCIMAGE;
    if (HI_NULL == pfUsrCallBack)
    {
        VPSS_FATAL("VPSS_GET_SRCIMAGE doesn't Exit.\n");
        return HI_FAILURE;
    }

    s32Ret = pfUsrCallBack(pstInstance->ID, pstSrcImage);
    return s32Ret;
}

#if DEF_VPSS_ANDROID_BYPASS
HI_S32 VPSS_INST_CheckByPass(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_FB_INFO_S *pstFrameList;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;
    VPSS_PORT_S *pstPort;
    VPSS_BUFFER_S stBuffer;
    HI_S32 s32Ret;
    HI_DRV_VIDEO_FRAME_S *pstPrivFrame;
    HI_U32 u32TmpAddr;
    HI_BOOL bAvailable = HI_FALSE;
    HI_BOOL bFrmListAvailable = HI_FALSE;

    if (pstInstance->stInEntity.stStreamInfo.bStreamByPass != HI_TRUE)
    {
        return HI_SUCCESS;
    }

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId != VPSS_INVALID_HANDLE
            && pstPort->bEnble == HI_TRUE)
        {
            pstFrameList = &(pstPort->stFrmInfo);
            if (pstFrameList->stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                (HI_VOID)VPSS_INST_CheckFrmBuffer(pstInstance,
                                                  pstPort->s32PortId, &bAvailable);
                (HI_VOID)VPSS_FB_CheckFulListAvailable(pstFrameList,
                                                       &bFrmListAvailable);
                if (bAvailable && bFrmListAvailable)
                {
                    pstFrameList->stBufListCfg.u32BufSize = 0;
                    pstFrameList->stBufListCfg.u32BufStride = 0;
                    s32Ret = VPSS_INST_GetFrmBuffer(pstInstance,
                                                    pstPort->s32PortId,
                                                    &(pstFrameList->stBufListCfg),
                                                    &stBuffer,
                                                    pstInstance->stInEntity.stStreamInfo.u32StreamH,
                                                    pstInstance->stInEntity.stStreamInfo.u32StreamW);

                    if (s32Ret == HI_SUCCESS)
                    {
                        if (HI_NULL == pstFrame)
                        {
                            pstFrame = VPSS_VMALLOC(sizeof(HI_DRV_VIDEO_FRAME_S));
                            VPSS_CHECK_NULL(pstFrame);
                        }
                        s32Ret = VPSS_FB_GetFulFrmBuf(pstFrameList, pstFrame, HI_NULL);

                        if (s32Ret == HI_SUCCESS)
                        {
                            pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstFrame->u32Priv;
                            pstPrivFrame = (HI_DRV_VIDEO_FRAME_S *)
                                           stBuffer.stPrivDataBuf.pu8StartVirAddr;
                            if ((pstInstance->bStorePrivData) && (HI_NULL != pstPrivFrame))
                            {
                                VPSS_SAFE_MEMCPY(pstPrivFrame, pstFrame, sizeof(HI_DRV_VIDEO_FRAME_S));
                            }
                            u32TmpAddr = pstFrame->stBufAddr[0].u32PhyAddr_Y;

                            pstFrame->stBufAddr[0].u32PhyAddr_Y = stBuffer.stMemBuf.u32StartPhyAddr;

                            VPSS_INST_ReportNewFrm(pstInstance, pstPort->s32PortId, pstFrame);

                            pstFrame->stBufAddr[0].u32PhyAddr_Y = u32TmpAddr;

                            VPSS_FB_RelFulFrmBufNoMmz(pstFrameList, pstFrame);
                        }
                        else
                        {
                            VPSS_INST_RelFrmBuffer(pstInstance,
                                                   pstPort->s32PortId,
                                                   &(pstFrameList->stBufListCfg),
                                                   &stBuffer.stMemBuf);
                        }
                    }
                }
            }
        }
    }

    if (HI_NULL != pstFrame)
    {
        VPSS_VFREE(pstFrame);
        pstFrame = HI_NULL;
    }
    return HI_SUCCESS;
}
#endif

HI_S32 VPSS_INST_CheckUndoImage(VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VPSS_IN_ENTITY_S *pstEntity;
    HI_VPSS_PQ_INFO_S stVpssPqInfo;
    VPSS_IN_INTF_S stInIntf;

    pstEntity = &pstInstance->stInEntity;

    s32Ret = VPSS_IN_GetIntf(pstEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Intf Failed\n");
        return HI_FAILURE;
    }

    /*
        When working in bypassmode,
        Maybe there are already some frames in fulllist waiting to be readout.
    */
    if (pstInstance->stInEntity.stStreamInfo.bStreamByPass == HI_TRUE)
    {
        HI_BOOL bFrmListAvailable = HI_FALSE;
        VPSS_FB_INFO_S *pstFrameList;

        pstFrameList = &(pstInstance->stPort[0].stFrmInfo);
        (HI_VOID)VPSS_FB_CheckFulListAvailable(pstFrameList, &bFrmListAvailable);
        if (HI_TRUE != bFrmListAvailable)
        {
            s32Ret = stInIntf.pfnRefresh(pstEntity);
        }
        else
        {
            //Do not start logic process, wait sink to readout frames in fulllist
            //Or report the bypassfrmae immediately(omxpath).
            return HI_FAILURE;
        }
    }
    else
    {
        s32Ret = stInIntf.pfnRefresh(pstEntity);
    }

    if (pstEntity->stStreamInfo.u32IsNewImage == HI_TRUE)
    {
        stVpssPqInfo.u32Width = pstEntity->stOriInfo.u32Width;
        stVpssPqInfo.u32Height = pstEntity->stOriInfo.u32Height;
        stVpssPqInfo.u32FrameRate = pstEntity->stOriInfo.u32FrmRate;
        stVpssPqInfo.bInterlace = pstEntity->stOriInfo.bInterlace;
        pstInstance->stPQModule.enSceneMode = pstInstance->stUsrInstCfg.enSceneMode;

        (HI_VOID)DRV_PQ_UpdateVpssPQ(pstInstance->ID, &stVpssPqInfo, &pstInstance->stPqRegData, &pstInstance->stPqWbcReg, &pstInstance->stPQModule);
    }

    return s32Ret;
}

HI_S32 VPSS_INST_CheckInstAvailable(VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 hDst;
    HI_U32 u32Count;
    HI_S32 s32BufIsEnough;
    HI_U32 u32EnablePort ;
    PFN_VPSS_CALLBACK pfUserCallBack;
    HI_S32 s32Ret;
    HI_DRV_VPSS_BUFFUL_STRATAGY_E eBufStratagy;
    VPSS_FB_INFO_S *pstFrameList;
    HI_BOOL bPortBufEnough = HI_FALSE;

    //check if at least one port enabled

    u32EnablePort = 0;
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        if (pstInstance->stPort[u32Count].s32PortId != VPSS_INVALID_HANDLE
            && pstInstance->stPort[u32Count].bEnble == HI_TRUE)
        {
            u32EnablePort++;
        }
    }

    if (u32EnablePort == 0)
    {
        return HI_FAILURE;
    }

    s32BufIsEnough = 0;
    //check if all enabled port has write space
    pstInstance->u32BufCnt ++;

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        if (pstInstance->stPort[u32Count].s32PortId != VPSS_INVALID_HANDLE
            && pstInstance->stPort[u32Count].bEnble == HI_TRUE)
        {
            s32BufIsEnough = s32BufIsEnough - 1;
            pstFrameList = &((pstInstance->stPort[u32Count]).stFrmInfo);
            if (pstFrameList->stBufListCfg.eBufType == HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE)
            {
                if (HI_DRV_FT_NOT_STEREO == pstInstance->stInEntity.stStreamInfo.eStreamFrmType)
                {
                    bPortBufEnough = VPSS_FB_CheckIsAvailable(pstFrameList, DEF_VPSS_2D_BUFFER_DEPEND_NUM);
                }
                else
                {
                    bPortBufEnough = VPSS_FB_CheckIsAvailable(pstFrameList, DEF_VPSS_3D_BUFFER_DEPEND_NUM);
                }
            }
            else
            {
                VPSS_INST_CheckFrmBuffer(pstInstance, pstInstance->stPort[u32Count].s32PortId, &bPortBufEnough);
            }
            if (bPortBufEnough)
            {
                s32BufIsEnough = s32BufIsEnough + 1;
            }
            else
            {

            }
        }

    }

    if (s32BufIsEnough != 0)
    {
        if (u32EnablePort == 1)
        {
            return HI_FAILURE;
        }

        if (pstInstance->pfUserCallBack == HI_NULL)
        {
            VPSS_FATAL("Inst %d UserCallBack is NULL.\n", pstInstance->ID);
            return HI_FAILURE;
        }

        pfUserCallBack = pstInstance->pfUserCallBack;
        hDst = pstInstance->hDst;
        eBufStratagy = HI_DRV_VPSS_BUFFUL_BUTT;
        pfUserCallBack(hDst, VPSS_EVENT_BUFLIST_FULL, &eBufStratagy);

        if (eBufStratagy == HI_DRV_VPSS_BUFFUL_PAUSE
            || eBufStratagy == HI_DRV_VPSS_BUFFUL_BUTT)
        {
            VPSS_INFO("Inst %d OUT Buf Is FULL.\n", pstInstance->ID);
            return HI_FAILURE;
        }
    }
    else
    {
        if (u32EnablePort == 1)
        {
            HI_BOOL bDropped;
            VPSS_PORT_S *pstPort = HI_NULL;
            VPSS_IN_INTF_S stInIntf;
            VPSS_INSTANCE_S *pstInst;
            HI_S32 s32Ret = HI_FAILURE;
            pstInst = pstInstance;
            for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
            {
                if (pstInstance->stPort[u32Count].s32PortId != VPSS_INVALID_HANDLE
                    && pstInstance->stPort[u32Count].bEnble == HI_TRUE)
                {
                    pstPort = &(pstInstance->stPort[u32Count]);
                    break;
                }
            }

            if (pstPort == HI_NULL)
            {
                VPSS_ERROR("Can't get valid port\n");
                return HI_FAILURE;
            }
            pstPort->u32OutCount++;
            bDropped = VPSS_INST_CheckIsDropped(pstInstance,
                                                pstPort->u32MaxFrameRate,
                                                pstPort->u32OutCount);
            if (bDropped == HI_TRUE)
            {
                s32Ret = VPSS_IN_GetIntf(&(pstInst->stInEntity), &stInIntf);
                if (HI_SUCCESS != s32Ret)
                {
                    VPSS_ERROR("Get Interface Failed\n");
                    return HI_FAILURE;
                }
                s32Ret = stInIntf.pfnCompleteImage(&(pstInst->stInEntity));
                if (HI_SUCCESS != s32Ret)
                {
                    VPSS_FATAL("pfnCompleteImage failed!\n");
                    return HI_FAILURE;
                }
                return HI_FAILURE;
            }
        }
    }
    pstInstance->u32BufSucCnt ++;

    //check undo image
    s32Ret = VPSS_INST_CheckUndoImage(pstInstance);
    pstInstance->u32ImgCnt = pstInstance->stInEntity.stListState.u32GetUsrTotal;
    pstInstance->u32ImgSucCnt = pstInstance->stInEntity.stListState.u32GetUsrSuccess;

#if DEF_VPSS_ANDROID_BYPASS
    (HI_VOID)VPSS_INST_CheckByPass(pstInstance);
#endif

    return s32Ret;
}

HI_S32 VPSS_INST_RelFrmBuffer(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE  hPort,
                              HI_DRV_VPSS_BUFLIST_CFG_S   *pstBufCfg,
                              VPSS_MEM_S *pstMemBuf)
{
    HI_S32 s32Ret;
    HI_DRV_VPSS_FRMBUF_S stFrmBuf;

    if (pstInstance == HI_NULL)
    {
        VPSS_FATAL("pstInstance is NULL\n");
        return HI_FAILURE;
    }

    if (pstInstance->pfUserCallBack == HI_NULL)
    {
        VPSS_FATAL("pfUserCallBack is NULL\n");
        return HI_FAILURE;
    }
    stFrmBuf.hPort = hPort;
    stFrmBuf.u32Size = pstBufCfg->u32BufSize;
    stFrmBuf.u32Stride = pstBufCfg->u32BufStride;

    stFrmBuf.u32Size = pstMemBuf->u32Size;
    stFrmBuf.u32StartPhyAddr = pstMemBuf->u32StartPhyAddr;
    stFrmBuf.pu8StartVirAddr = pstMemBuf->pu8StartVirAddr;

    s32Ret = pstInstance->pfUserCallBack(pstInstance->hDst, VPSS_EVENT_REL_FRMBUFFER, &stFrmBuf);

    if (s32Ret == HI_SUCCESS)
    {
        memset(pstMemBuf, 0, sizeof(VPSS_MEM_S));
    }

    return s32Ret;
}
HI_S32 VPSS_INST_GetFrmBuffer(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort,
                              HI_DRV_VPSS_BUFLIST_CFG_S *pstBufCfg, VPSS_BUFFER_S *pstBuffer,
                              HI_U32 u32StoreH, HI_U32 u32StoreW)
{
    VPSS_MEM_S *pstMemBuf;
    VPSS_MEM_S *pstPrivDataBuf;
    HI_S32 s32Ret;
    HI_DRV_VPSS_BUFFER_TYPE_E eBufferType;
    HI_DRV_VPSS_FRMBUF_S stFrmBuf;
    HI_U32 u32BufSize;

    if (pstInstance == HI_NULL)
    {
        VPSS_FATAL("pstInstance is NULL\n");
        return HI_FAILURE;
    }
    eBufferType = pstBufCfg->eBufType;
    u32BufSize = pstBufCfg->u32BufSize;

    pstMemBuf = &(pstBuffer->stMemBuf);
    pstPrivDataBuf = &(pstBuffer->stPrivDataBuf);

    if (pstInstance->pfUserCallBack == HI_NULL)
    {
        VPSS_FATAL("pfUserCallBack is NULL\n");
        return HI_FAILURE;
    }
    stFrmBuf.hPort = hPort;
    stFrmBuf.u32Size = pstBufCfg->u32BufSize;
    stFrmBuf.u32Stride = pstBufCfg->u32BufStride;
    stFrmBuf.u32FrmH = u32StoreH;
    stFrmBuf.u32FrmW = u32StoreW;
    s32Ret = pstInstance->pfUserCallBack(pstInstance->hDst, VPSS_EVENT_GET_FRMBUFFER, &stFrmBuf);

    if (s32Ret == HI_SUCCESS)
    {
        pstMemBuf->u32Size = stFrmBuf.u32Size;
        pstMemBuf->u32StartPhyAddr = stFrmBuf.u32StartPhyAddr;
        pstMemBuf->pu8StartVirAddr = stFrmBuf.pu8StartVirAddr;
        pstBuffer->u32Stride = stFrmBuf.u32Stride;

        pstPrivDataBuf->u32Size = stFrmBuf.u32PrivDataSize;
        pstPrivDataBuf->u32StartPhyAddr = stFrmBuf.u32PrivDataPhyAddr;
        pstPrivDataBuf->pu8StartVirAddr = stFrmBuf.pu8PrivDataVirAddr;
    }

    return s32Ret;
}

HI_S32 VPSS_INST_CheckFrmBuffer(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE  hPort,
                                HI_BOOL *bAvailable)
{
    HI_S32 s32Ret;
    HI_DRV_VPSS_BUFINFO_S stBufInfo;

    if (pstInstance == HI_NULL)
    {
        VPSS_FATAL("pstInstance is NULL\n");
        return HI_FAILURE;
    }
    if (pstInstance->pfUserCallBack == HI_NULL)
    {
        VPSS_FATAL("pfUserCallBack is NULL\n");
        return HI_FAILURE;
    }
    stBufInfo.hPort = hPort;
    stBufInfo.bAvailable = HI_FALSE;
    s32Ret = pstInstance->pfUserCallBack(pstInstance->hDst, VPSS_EVENT_CHECK_FRAMEBUFFER, &stBufInfo);
    if (s32Ret == HI_SUCCESS)
    {
        *bAvailable = stBufInfo.bAvailable;
    }
    else
    {
        *bAvailable = HI_FALSE;
    }
    return s32Ret;
}


HI_S32 VPSS_INST_ReportNewFrm(VPSS_INSTANCE_S *pstInstance,
                              VPSS_HANDLE  hPort, HI_DRV_VIDEO_FRAME_S *pstFrm)
{
    HI_S32 s32Ret;
    HI_DRV_VPSS_FRMINFO_S stFrmInfo;

    if (pstInstance == HI_NULL)
    {
        VPSS_FATAL("pstInstance is NULL\n");
        return HI_FAILURE;
    }

    if (pstInstance->pfUserCallBack == HI_NULL)
    {
        VPSS_FATAL("pfUserCallBack is NULL\n");
        return HI_FAILURE;
    }
    stFrmInfo.hPort = hPort;
    VPSS_SAFE_MEMCPY(&(stFrmInfo.stFrame), pstFrm, sizeof(HI_DRV_VIDEO_FRAME_S));

    s32Ret = pstInstance->pfUserCallBack(pstInstance->hDst, VPSS_EVENT_NEW_FRAME, &stFrmInfo);

    return s32Ret;
}

HI_BOOL VPSS_INST_CheckIsDropped(VPSS_INSTANCE_S *pstInstance, HI_U32 u32OutRate, HI_U32 u32OutCount)
{
    HI_U32 u32Multiple;
    HI_U32 u32Quote;
    HI_BOOL bDropped;
    VPSS_IN_INTF_S stInIntf;
    VPSS_IN_STREAM_INFO_S stInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    bDropped = HI_FALSE;

    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get intf Failed\n");
        return HI_FALSE;
    }

    (HI_VOID)stInIntf.pfnGetInfo(&(pstInstance->stInEntity),
                                 VPSS_IN_INFO_STREAM,
                                 HI_DRV_BUF_ADDR_MAX,
                                 &stInfo);


    if (stInfo.u32InRate < u32OutRate || u32OutRate == 0)
    {
        bDropped = HI_FALSE;
    }
    else
    {
        u32Multiple = stInfo.u32InRate * 10 / u32OutRate;

        u32Quote = (u32Multiple + 5) / 10;

        if (u32OutCount % u32Quote == 1)
        {
            bDropped = HI_TRUE;
        }
        else
        {
            bDropped = HI_FALSE;
        }
    }

    return bDropped;
}

VPSS_HAL_NODE_TYPE_E VPSS_INST_Check2DNodeType(VPSS_INSTANCE_S *pstInst)
{
    VPSS_IN_INTF_S stIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage;
    HI_S32 s32Ret = HI_SUCCESS;

    (HI_VOID)VPSS_IN_GetIntf(&(pstInst->stInEntity), &stIntf);

    VPSS_CHECK_NULL(stIntf.pfnGetProcessImage);

    s32Ret = stIntf.pfnGetProcessImage(&(pstInst->stInEntity), &pstImage);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Process Image Failed\n");
        return HI_FAILURE;
    }

#ifndef VPSS_HAL_WITH_CBB
    if (VPSS_HDR_TYPE_NEED_DETILE_NOALG(pstImage->enSrcFrameType))
    {
        return VPSS_HAL_NODE_HDR_DETILE_NOALG;
    }
    if (pstImage->u32Width > 1920)
    {
        return VPSS_HAL_NODE_UHD;
    }
    else
    {
        if (pstImage->bProgressive)
        {
            if (pstImage->enFieldMode == HI_DRV_FIELD_ALL)
            {
                return VPSS_HAL_NODE_2D_FRAME;
            }
            else
            {
                return VPSS_HAL_NODE_2D_Field;
            }
        }
        else
        {
            return VPSS_HAL_NODE_2D_5Field;
        }
    }
    return VPSS_HAL_NODE_2D_FRAME;
#else

    if (VPSS_HDR_TYPE_NEED_DETILE_NOALG(pstImage->enSrcFrameType))
    {
        return VPSS_HAL_NODE_HDR_DETILE_NOALG;
    }

    if (pstImage->u32Width > 1920)
    {
        return VPSS_HAL_NODE_2D_UHD;
    }

    if (pstImage->bProgressive)
    {
        if (pstImage->enFieldMode == HI_DRV_FIELD_ALL)
        {
            return VPSS_HAL_NODE_2D_FRAME;
        }
        else
        {
            if (HI_TRUE == pstInst->stInEntity.stSrc.bEnding)
            {
                return VPSS_HAL_NODE_2D_DEI_LAST_2FIELD;
            }
            else
            {
                return VPSS_HAL_NODE_2D_FIELD;
            }
        }
    }
    else
    {
        return VPSS_HAL_NODE_2D_DEI;
    }
    return VPSS_HAL_NODE_2D_FRAME;
#endif
}

VPSS_HAL_NODE_TYPE_E VPSS_INST_Check3DNodeType(VPSS_INSTANCE_S *pstInst)
{
    VPSS_IN_INTF_S stIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage;
    HI_S32 s32Ret;

    (HI_VOID)VPSS_IN_GetIntf(&(pstInst->stInEntity), &stIntf);

    if (HI_NULL == stIntf.pfnGetInfo)
    {
        return VPSS_HAL_NODE_BUTT;
    }

    VPSS_CHECK_NULL(stIntf.pfnGetProcessImage);

    s32Ret = stIntf.pfnGetProcessImage(&(pstInst->stInEntity), &pstImage);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Process Image Failed\n");
        return HI_FAILURE;
    }
    //HI_ASSERT(pstInst->stStreamInfo.eStreamFrmType < HI_DRV_FT_BUTT);
    //HI_ASSERT(pstInst->stStreamInfo.eStreamFrmType != HI_DRV_FT_NOT_STEREO);

    if (pstImage->eFrmType == HI_DRV_FT_FPK)
    {
        return VPSS_HAL_NODE_2D_FRAME;
    }
    else if (pstImage->eFrmType == HI_DRV_FT_TAB
             || pstImage->eFrmType == HI_DRV_FT_SBS)
    {
        return VPSS_HAL_NODE_3D_FRAME_R;
    }
    else
    {
        VPSS_ERROR("Invalid frame type %d\n", pstImage->eFrmType);
    }

    return VPSS_HAL_NODE_2D_FRAME;
}


HI_VOID VPSS_INST_SetHalFrameInfo(HI_DRV_VIDEO_FRAME_S *pstFrame,
                                  VPSS_HAL_FRAME_S *pstHalFrm, HI_DRV_BUF_ADDR_E enBufLR)
{
    if (pstFrame == HI_NULL || pstHalFrm == HI_NULL || (enBufLR >= HI_DRV_BUF_ADDR_MAX))
    {
        VPSS_FATAL("pstFrame(%p), pstHalFrm(%p) enBufLR:%d\n", pstFrame, pstHalFrm, enBufLR);
        return;
    }
    pstHalFrm->eFrmType = pstFrame->eFrmType;
    pstHalFrm->u32Width = pstFrame->u32Width;
    pstHalFrm->u32Height = pstFrame->u32Height;

    pstHalFrm->enFormat = pstFrame->ePixFormat;
    pstHalFrm->enFieldMode = pstFrame->enFieldMode;
    pstHalFrm->bProgressive = pstFrame->bProgressive;
    VPSS_SAFE_MEMCPY(&pstHalFrm->stAddr, &(pstFrame->stBufAddr[enBufLR]), sizeof(HI_DRV_VID_FRAME_ADDR_S));
    pstHalFrm->bCompressd = pstFrame->bCompressd;
    pstHalFrm->enBitWidth = pstFrame->enBitWidth;
    pstHalFrm->bTopFirst = pstFrame->bTopFieldFirst;
    pstHalFrm->bSecure = pstFrame->bSecure;
    if (VPSS_HAS_LBADDR(pstFrame->enBitWidth))
    {
        VPSS_SAFE_MEMCPY(&pstHalFrm->stAddr_LB, &pstFrame->stBufAddr_LB[enBufLR], sizeof(HI_DRV_VID_FRAME_ADDR_S));
    }

    if (VPSS_HDR_TYPE_NEED_TRANS_METADATA(pstFrame->enSrcFrameType))
    {
        if (pstFrame->unHDRInfo.stDolbyInfo.bMetadataValid)
        {
            pstHalFrm->stAddr_META.u32PhyAddr_Y = pstFrame->unHDRInfo.stDolbyInfo.stMetadata.u32Addr;
            pstHalFrm->u32MetaSize = pstFrame->unHDRInfo.stDolbyInfo.stMetadata.u32Length;

            //VPSS_ERROR("meta size %d\n",pstHalFrm->u32MetaSize);
        }
        else
        {
            //VPSS_ERROR("meta invalid\n");
            pstHalFrm->stAddr_META.u32PhyAddr_Y = 0;
            pstHalFrm->u32MetaSize = 0; //EL carries no Metadata, DONOT need to trans Metadata
        }
    }
}

HI_VOID VPSS_INST_SetOutFrameInfo(VPSS_INSTANCE_S *pstInst, HI_U32 PortId, VPSS_BUFFER_S *pstBuf,
                                  HI_DRV_VIDEO_FRAME_S *pstFrm, HI_DRV_BUF_ADDR_E enBufLR)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32DstW, u32SrcW;
    HI_U32 u32DstH, u32SrcH;

    HI_DRV_VIDEO_FRAME_S *pstCur;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;
    VPSS_PORT_S *pstPort;
    HI_U32 u32PhyAddr, u32Stride;
    VPSS_IN_INTF_S stIntf = {0};

    (HI_VOID)VPSS_IN_GetIntf(&(pstInst->stInEntity), &stIntf);
    if (HI_NULL == stIntf.pfnGetProcessImage)
    {
        return;
    }

    /* INInfo */
    s32Ret = stIntf.pfnGetProcessImage(&(pstInst->stInEntity), &pstCur);
    if (HI_FAILURE == s32Ret)
    {
        VPSS_FATAL("GetProcessImage failed!\n");
        return;
    }

    u32SrcW = pstFrm->u32Width;
    u32SrcH = pstFrm->u32Height;
    VPSS_SAFE_MEMCPY(pstFrm, pstCur, sizeof(HI_DRV_VIDEO_FRAME_S));

    pstFrm->u32TunnelPhyAddr = 0;

    pstPort = &pstInst->stPort[PortId];

    u32DstW = pstPort->s32OutputWidth;
    u32DstH = pstPort->s32OutputHeight;

    if ((u32DstW == 0) || (u32DstH == 0))
    {
        HI_RECT_S stInRect;
        VPSS_INST_GetInCrop(pstInst, PortId, &stInRect);
        u32DstW = (HI_U32)stInRect.s32Width;
        u32DstH = (HI_U32)stInRect.s32Height;
        //u32DstW = pstInst->stStreamInfo.u32StreamW;
        //u32DstH = pstInst->stStreamInfo.u32StreamH;
    }

#ifdef ZME_2L_TEST
    if (HI_TRUE == pstPort->bNeedZME2L) //�����Ҫ�������ţ���Ҫ��������port�������
    {
        pstFrm->u32Width  = u32SrcW;
        pstFrm->u32Height = u32SrcH;
    }
#ifndef VPSS_HAL_WITH_CBB
    else if (HI_TRUE == pstPort->bNeedRotate) //�����Ҫ��ת����Ҫ��������port�������
    {
        pstFrm->u32Width  = u32SrcW;
        pstFrm->u32Height = u32SrcH;
    }
#endif
    else
    {
        pstFrm->u32Width  = u32DstW;
        pstFrm->u32Height = u32DstH;
    }
#else
#ifndef VPSS_HAL_WITH_CBB
    if ((HI_DRV_VPSS_ROTATION_90 == pstPort->enRotation)
        || (HI_DRV_VPSS_ROTATION_270 == pstPort->enRotation))
    {
        HI_U32 u32BufSize = 0;
        HI_U32 u32BufStride = 0;

        pstFrm->u32Width  = u32DstH;
        pstFrm->u32Height = u32DstW;
        VPSS_OSAL_CalBufSize(&u32BufSize, &u32BufStride, pstFrm->u32Height
                             , pstFrm->u32Width, pstPort->eFormat, pstPort->enOutBitWidth);
        if ((pstBuf->stMemBuf.u32Size != u32BufSize)
            || (pstBuf->u32Stride != u32BufStride))
        {
            if (pstBuf->stMemBuf.u32Size != 0)
            {
                VPSS_OSAL_FreeMem(&(pstBuf->stMemBuf));
            }

            s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_NORMAL,
                                           u32BufSize,
                                           "VPSS_RoBuf",
                                           HI_NULL,
                                           &(pstBuf->stMemBuf));
            if (s32Ret != HI_SUCCESS)
            {
                VPSS_FATAL("Alloc RoBuf Failed\n");
            }

            pstBuf->u32Stride = u32BufStride;
        }


    }
    else
#endif
    {
        pstFrm->u32Width  = u32DstW;
        pstFrm->u32Height = u32DstH;
    }
#endif
    /* keep pts equal src frame*/
    s32Ret = stIntf.pfnSetInfo(&(pstInst->stInEntity), VPSS_SET_INFO_PTS, enBufLR, pstFrm);
    if (HI_FAILURE == s32Ret)
    {
        VPSS_FATAL("set PTS failed!\n");
        return;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrm->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstPriv->u32Reserve[0]);

    if (pstPort->eAspMode == HI_DRV_ASP_RAT_MODE_FULL)
    {
        if (pstCur->u32AspectWidth != 0 && pstCur->u32AspectHeight != 0)
        {

            pstFrm->u32AspectWidth = pstCur->u32AspectWidth;
            pstFrm->u32AspectHeight = pstCur->u32AspectHeight;
        }
        else if (pstCur->u32AspectWidth == 0 && pstCur->u32AspectHeight == 1)
        {
            pstFrm->u32AspectWidth = pstCur->u32Width;
            pstFrm->u32AspectHeight = pstCur->u32Height;
        }
        else if (pstCur->u32AspectWidth == 0 && pstCur->u32AspectHeight == 2)
        {
            pstFrm->u32AspectWidth = pstCur->u32Width;
            pstFrm->u32AspectHeight = pstCur->u32Height;
        }
        else
        {

        }
#ifndef VPSS_HAL_WITH_CBB
        if (pstPort->enRotation == HI_DRV_VPSS_ROTATION_90
            || pstPort->enRotation == HI_DRV_VPSS_ROTATION_270)
#else
        if (pstPort->bNeedRotate)
#endif
        {
            HI_U32 u32Tmp;

            u32Tmp = pstFrm->u32AspectWidth;

            pstFrm->u32AspectWidth = pstFrm->u32AspectHeight;
            pstFrm->u32AspectHeight = u32Tmp;
        }

        pstPriv->bAspectProcessed = HI_FALSE;
    }
    else
    {
        pstFrm->u32AspectWidth = pstPort->stDispPixAR.u32ARw;
        pstFrm->u32AspectHeight = pstPort->stDispPixAR.u32ARh;

        pstPriv->bAspectProcessed = HI_TRUE;
    }

    pstFrm->ePixFormat = pstPort->eFormat;
    pstFrm->bProgressive = HI_TRUE;
    pstFrm->enFieldMode = HI_DRV_FIELD_ALL;
    pstFrm->enBitWidth = pstPort->enOutBitWidth;

    if (pstCur->bProgressive == HI_TRUE)
    {
        pstPriv->eOriginField = HI_DRV_FIELD_ALL;
    }
    else
    {
        pstPriv->eOriginField = pstCur->enFieldMode;
    }

    VPSS_RWZB_GetRwzbType(&(pstInst->stRwzbInfo), &(pstPriv->u32Fidelity));

    if (pstPort->b3Dsupport && (pstCur->eFrmType != HI_DRV_FT_NOT_STEREO))
    {
        pstFrm->eFrmType = HI_DRV_FT_FPK;
    }
    else
    {
        pstFrm->eFrmType = HI_DRV_FT_NOT_STEREO;
    }

    pstFrm->u32Circumrotate = 0;
    pstFrm->bToFlip_V = 0;

    //:TODO:�ȼ�ʵ��stLbxInfo
    pstFrm->stLbxInfo.s32X = 0;
    pstFrm->stLbxInfo.s32Y = 0;
    pstFrm->stLbxInfo.s32Width  = u32DstW;
    pstFrm->stLbxInfo.s32Height = u32DstH;

    if (VPSS_HDR_TYPE_NEED_TRANS_METADATA(pstFrm->enSrcFrameType))
    {
        pstFrm->unHDRInfo.stDolbyInfo.stMetadata.u32Addr = pstBuf->stExtBuf.u32StartPhyAddr;
        //VPSS_ERROR("size %d\n",pstFrm->unHDRInfo.stDolbyInfo.stMetadata.u32Length);
    }

    if ((HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype)
        && (pstPriv->eOriginField != HI_DRV_FIELD_ALL)
        && (pstFrm->enBufValidMode == HI_DRV_FIELD_ALL))
    {
        if (pstPort->enRotation == HI_DRV_VPSS_ROTATION_90
            || pstPort->enRotation == HI_DRV_VPSS_ROTATION_270)
        {
            pstFrm->u32AspectWidth *= 2;
            pstFrm->stDispRect.s32Width *= 2;
            pstPriv->stOriginImageRect.s32Width *= 2;
            pstPriv->stVideoOriginalInfo.u32Width *= 2;
        }
        else
        {
            pstFrm->u32AspectHeight *= 2;
            pstFrm->stDispRect.s32Height *= 2;
            pstPriv->stOriginImageRect.s32Height *= 2;
            pstPriv->stVideoOriginalInfo.u32Height *= 2;
        }

        VPSS_DBG_INFO("H aspH dispH %d %d %d\n", pstFrm->u32Height,
                      pstFrm->u32AspectHeight, pstFrm->stDispRect.s32Height);
        VPSS_DBG_INFO("OriginRect.H  OriginalInfo.H %d %d\n",
                      pstFrm->u32AspectHeight, pstFrm->stDispRect.s32Height);
    }

    /* ����ַ��Ϣ */
    u32PhyAddr = pstBuf->stMemBuf.u32StartPhyAddr;
    u32Stride  = pstBuf->u32Stride;

    pstFrm->stBufAddr[enBufLR].u32Stride_Y  =  u32Stride;
    pstFrm->stBufAddr[enBufLR].u32Stride_C  =  u32Stride;

    if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1_CMP
        || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1_CMP
       )
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_YHead = u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_YHead + pstFrm->u32Height * 16;

        pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead =
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y + u32Stride * pstFrm->u32Height;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead + pstFrm->u32Height * 16;
    }
    else if ( pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21_CMP
              || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12_CMP)
    {
        if ( HI_TRUE == pstInst->enCapability.bits.hi3716mv410 ||
             HI_TRUE == pstInst->enCapability.bits.hi3798cv200_a )
        {
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =  u32PhyAddr + u32Stride * pstFrm->u32Height;
        }
    }
    else if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1)
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].vir_addr_y = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr);
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =  u32PhyAddr + u32Stride * pstFrm->u32Height;
        pstFrm->stBufAddr[enBufLR].vir_addr_c = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr + u32Stride * pstFrm->u32Height);
    }
    else if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_ARGB8888
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_ABGR8888)
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
    }

    else
    {
        VPSS_FATAL("Invalid Out pixFormat %d, Use default format:%d\n",
                   pstFrm->ePixFormat, HI_DRV_PIX_FMT_NV21);

        pstFrm->ePixFormat = HI_DRV_PIX_FMT_NV21;
        pstPort->eFormat = HI_DRV_PIX_FMT_NV21;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].vir_addr_y = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr);
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =  u32PhyAddr + u32Stride * pstFrm->u32Height;
        pstFrm->stBufAddr[enBufLR].vir_addr_c = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr + u32Stride * pstFrm->u32Height);

        return;
    }


    return;
}

HI_VOID VPSS_INST_SetRotationOutFrameInfo(VPSS_INSTANCE_S *pstInst, HI_U32 PortId, VPSS_BUFFER_S *pstBuf,
        HI_DRV_VIDEO_FRAME_S *pstFrm, HI_DRV_BUF_ADDR_E enBufLR)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32DstW;
    HI_U32 u32DstH;
    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_PORT_S *pstPort;
    HI_U32 u32PhyAddr, u32Stride;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;
    VPSS_IN_INTF_S stIntf = {0};

    /* INInfo */
    (HI_VOID)VPSS_IN_GetIntf(&(pstInst->stInEntity), &stIntf);

    if (HI_NULL == stIntf.pfnGetProcessImage)
    {
        return;
    }

    s32Ret = stIntf.pfnGetProcessImage(&(pstInst->stInEntity), &pstCur);
    if (HI_FAILURE == s32Ret)
    {
        VPSS_FATAL("GetProcessImage failed!\n");
        return;
    }

    VPSS_SAFE_MEMCPY(pstFrm, pstCur, sizeof(HI_DRV_VIDEO_FRAME_S));

    pstPort = &pstInst->stPort[PortId];

    u32DstW = pstPort->s32OutputWidth;
    u32DstH = pstPort->s32OutputHeight;

    if ((u32DstW == 0) || (u32DstH == 0))
    {
        HI_RECT_S stInRect;
        VPSS_INST_GetInCrop(pstInst, PortId, &stInRect);
        u32DstW = (HI_U32)stInRect.s32Width;
        u32DstH = (HI_U32)stInRect.s32Height;
    }

    pstFrm->u32Width  = u32DstW;
    pstFrm->u32Height = u32DstH;

    pstFrm->u32AspectHeight = pstPort->stDispPixAR.u32ARh;
    pstFrm->u32AspectWidth = pstPort->stDispPixAR.u32ARw;

    pstFrm->ePixFormat = pstPort->eFormat;
    pstFrm->bProgressive = HI_TRUE;
    pstFrm->enFieldMode = HI_DRV_FIELD_ALL;

    pstFrm->enBitWidth = pstPort->enOutBitWidth;

    if (pstPort->b3Dsupport && (pstCur->eFrmType != HI_DRV_FT_NOT_STEREO))
    {
        pstFrm->eFrmType = HI_DRV_FT_FPK;
    }
    else
    {
        pstFrm->eFrmType = HI_DRV_FT_NOT_STEREO;
    }

    /* keep pts equal src frame, this will clear pstFrm->u32Priv[]*/
    s32Ret = stIntf.pfnSetInfo(&(pstInst->stInEntity), VPSS_SET_INFO_PTS, enBufLR, pstFrm);
    if (HI_FAILURE == s32Ret)
    {
        VPSS_FATAL("set PTS failed!\n");
        return;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrm->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstPriv->u32Reserve[0]);

    if (pstCur->bProgressive == HI_TRUE)
    {
        pstPriv->eOriginField = HI_DRV_FIELD_ALL;
    }
    else
    {
        pstPriv->eOriginField = pstCur->enFieldMode;
    }

    if (pstPort->eAspMode == HI_DRV_ASP_RAT_MODE_FULL)
    {
        if (pstCur->u32AspectWidth != 0 && pstCur->u32AspectHeight != 0)
        {
            pstFrm->u32AspectWidth = pstCur->u32AspectWidth;
            pstFrm->u32AspectHeight = pstCur->u32AspectHeight;
        }
        else if (pstCur->u32AspectWidth == 0 && pstCur->u32AspectHeight == 1)
        {
            pstFrm->u32AspectWidth = pstCur->u32Width;
            pstFrm->u32AspectHeight = pstCur->u32Height;
        }
        else if (pstCur->u32AspectWidth == 0 && pstCur->u32AspectHeight == 2)
        {
            pstFrm->u32AspectWidth = pstCur->u32Width;
            pstFrm->u32AspectHeight = pstCur->u32Height;
        }
        else
        {

        }
        if (pstPort->enRotation == HI_DRV_VPSS_ROTATION_90
            || pstPort->enRotation == HI_DRV_VPSS_ROTATION_270)
        {
            HI_U32 u32Tmp;

            u32Tmp = pstFrm->u32AspectWidth;

            pstFrm->u32AspectWidth = pstFrm->u32AspectHeight;
            pstFrm->u32AspectHeight = u32Tmp;
        }
        pstPriv->bAspectProcessed = HI_FALSE;
    }
    else
    {
        pstFrm->u32AspectWidth = pstPort->stDispPixAR.u32ARw;
        pstFrm->u32AspectHeight = pstPort->stDispPixAR.u32ARh;

        pstPriv->bAspectProcessed = HI_TRUE;
    }

    pstFrm->u32Circumrotate = 0;
    pstFrm->bToFlip_V = 0;
    pstFrm->stLbxInfo.s32X = 0;
    pstFrm->stLbxInfo.s32Y = 0;
    pstFrm->stLbxInfo.s32Width  = 0;
    pstFrm->stLbxInfo.s32Height = 0;

    if ((HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype)
        && (pstPriv->eOriginField != HI_DRV_FIELD_ALL)
        && (pstFrm->enBufValidMode == HI_DRV_FIELD_ALL))
    {

        if (pstPort->enRotation == HI_DRV_VPSS_ROTATION_90
            || pstPort->enRotation == HI_DRV_VPSS_ROTATION_270)
        {
            pstFrm->u32AspectWidth *= 2;
            pstFrm->stDispRect.s32Width *= 2;
            pstPriv->stOriginImageRect.s32Width *= 2;
            pstPriv->stVideoOriginalInfo.u32Width *= 2;
        }
        else
        {
            pstFrm->u32AspectHeight *= 2;
            pstFrm->stDispRect.s32Height *= 2;
            pstPriv->stOriginImageRect.s32Height *= 2;
            pstPriv->stVideoOriginalInfo.u32Height *= 2;
        }

        VPSS_DBG_INFO("H aspH dispH %d %d %d\n", pstFrm->u32Height,
                      pstFrm->u32AspectHeight, pstFrm->stDispRect.s32Height);
        VPSS_DBG_INFO("OriginRect.H  OriginalInfo.H %d %d\n",
                      pstFrm->u32AspectHeight, pstFrm->stDispRect.s32Height);
    }

    /* ����ַ��Ϣ */
    u32PhyAddr = pstBuf->stMemBuf.u32StartPhyAddr;
    u32Stride  = pstBuf->u32Stride;

    pstFrm->stBufAddr[enBufLR].u32Stride_Y  =  u32Stride;
    pstFrm->stBufAddr[enBufLR].u32Stride_C  =  u32Stride;

    if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12_CMP
        || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21_CMP
        || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1_CMP
        || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1_CMP
       )
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_YHead = u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_YHead + pstFrm->u32Height * 16;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead =
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y + u32Stride * pstFrm->u32Height;

        if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12_CMP
            || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21_CMP)
        {
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =
                pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead + pstFrm->u32Height * 16 / 2;
        }
        else
        {
            pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =
                pstFrm->stBufAddr[enBufLR].u32PhyAddr_CHead + pstFrm->u32Height * 16;
        }
    }
    else if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV12
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV21
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1)
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =  u32PhyAddr + u32Stride * pstFrm->u32Height;

        pstFrm->stBufAddr[enBufLR].vir_addr_y = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr);
        pstFrm->stBufAddr[enBufLR].vir_addr_c = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr + u32Stride * pstFrm->u32Height);
    }
    else if (pstFrm->ePixFormat == HI_DRV_PIX_FMT_ARGB8888
             || pstFrm->ePixFormat == HI_DRV_PIX_FMT_ABGR8888)
    {
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
    }
    else
    {
        VPSS_FATAL("Invalid Out pixFormat %d, Use default format:%d\n",
                   pstFrm->ePixFormat, HI_DRV_PIX_FMT_NV21);

        pstFrm->ePixFormat = HI_DRV_PIX_FMT_NV21;
        pstPort->eFormat = HI_DRV_PIX_FMT_NV21;
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_Y =  u32PhyAddr;
        pstFrm->stBufAddr[enBufLR].vir_addr_y = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr);
        pstFrm->stBufAddr[enBufLR].u32PhyAddr_C =  u32PhyAddr + u32Stride * pstFrm->u32Height;
        pstFrm->stBufAddr[enBufLR].vir_addr_c = (HI_U64)(HI_SIZE_T)(pstBuf->stMemBuf.pu8StartVirAddr + u32Stride * pstFrm->u32Height);
    }

    return;
}
HI_VOID VPSS_INST_GetInCrop(VPSS_INSTANCE_S *pstInst, HI_U32 PortId, HI_RECT_S *pstInCropRect)
{
    HI_U32 u32SrcW;
    HI_U32 u32SrcH;
    VPSS_IN_STREAM_INFO_S stInfo;
    VPSS_IN_INTF_S stIntf = {0};

    (HI_VOID)VPSS_IN_GetIntf(&(pstInst->stInEntity), &stIntf);

    if (HI_NULL == stIntf.pfnGetInfo)
    {
        return;
    }

    (HI_VOID)stIntf.pfnGetInfo(&(pstInst->stInEntity),
                               VPSS_IN_INFO_STREAM,
                               HI_DRV_BUF_ADDR_MAX,
                               &stInfo);

    u32SrcW = stInfo.u32StreamW;
    u32SrcH = stInfo.u32StreamH;

    if (stInfo.bH265Interlace)
    {
        u32SrcH = u32SrcH * 2;
    }

    pstInCropRect->s32X = 0;
    pstInCropRect->s32Y = 0;
    pstInCropRect->s32Width  = u32SrcW;
    pstInCropRect->s32Height = u32SrcH;

#if 0 //�����水��Port Crop�Ĺ��ܷ�֧
    if (pstInst->stProcCtrl.bUseCropRect)
    {
        HI_DRV_CROP_RECT_S *pCrpRct;

        pCrpRct = &pstInst->stProcCtrl.stCropRect;

        if (((pCrpRct->u32LeftOffset + pCrpRct->u32RightOffset) > u32SrcW)
            || ((pCrpRct->u32TopOffset + pCrpRct->u32BottomOffset) > u32SrcH))
        {
            VPSS_INFO("u32LeftOffset(%d) add u32RightOffset(%d) is too large(%d)\n"
                      "Or TopOffset(%d) add u32BottomOffset(%d) is too large(%d)\n",
                      pCrpRct->u32LeftOffset, pCrpRct->u32RightOffset, u32SrcW,
                      pCrpRct->u32TopOffset, pCrpRct->u32BottomOffset, u32SrcH);
            return;
        }

        pstInCropRect->s32X = pCrpRct->u32LeftOffset;
        pstInCropRect->s32Y = pCrpRct->u32TopOffset;
        pstInCropRect->s32Width  = u32SrcW - (pCrpRct->u32LeftOffset + pCrpRct->u32RightOffset);
        pstInCropRect->s32Height = u32SrcH - (pCrpRct->u32TopOffset + pCrpRct->u32BottomOffset);

    }
    else
    {
        HI_RECT_S *pInRct;

        pInRct = &pstInst->stProcCtrl.stInRect;

        if ((pInRct->s32X < 0) || (pInRct->s32Y < 0) || (pInRct->s32Width <= 0) || (pInRct->s32Height <= 0))
        {
            VPSS_INFO("s32X(%d)  s32Y(%d) s32Width(%d) s32Height(%d) is invaild\n",
                      pInRct->s32X, pInRct->s32Y, pInRct->s32Width, pInRct->s32Height);

            return;
        }

        if (((pInRct->s32X + pInRct->s32Width) > u32SrcW)
            || ((pInRct->s32Y + pInRct->s32Height) > u32SrcH))
        {
            VPSS_INFO("s32X(%d) add s32Width(%d) is too large  u32SrcW(%d)n"
                      "Or s32Y(%d) add s32Height(%d) is too large  u32SrcH(%d)n",
                      pInRct->s32X, pInRct->s32Width, u32SrcW,
                      pInRct->s32Y, pInRct->s32Height, u32SrcH);

            return;
        }

        pstInCropRect->s32X = pInRct->s32X;
        pstInCropRect->s32Y = pInRct->s32Y;
        pstInCropRect->s32Width  = pInRct->s32Width;
        pstInCropRect->s32Height = pInRct->s32Height;

    }
#else
    if (pstInst->stPort[PortId].bUseCropRect)
    {
        HI_DRV_CROP_RECT_S *pCrpRct;

        pCrpRct = &pstInst->stPort[PortId].stCropRect;
        if ((HI_DRV_FT_NOT_STEREO != pstInst->stSrcImage.eFrmType)
            && ((0 != pCrpRct->u32LeftOffset)
                || (0 != pCrpRct->u32RightOffset)
                || (0 != pCrpRct->u32TopOffset)
                || (0 != pCrpRct->u32BottomOffset)))
        {
            VPSS_ERROR("3d not support crop,u32LeftOffset(%d), u32RightOffset(%d)\n"
                       "TopOffset(%d),u32BottomOffset(%d)\n",
                       pCrpRct->u32LeftOffset, pCrpRct->u32RightOffset,
                       pCrpRct->u32TopOffset, pCrpRct->u32BottomOffset);
            return;
        }
        if (((pCrpRct->u32LeftOffset + pCrpRct->u32RightOffset) > u32SrcW)
            || ((pCrpRct->u32TopOffset + pCrpRct->u32BottomOffset) > u32SrcH))
        {
            VPSS_INFO("u32LeftOffset(%d) add u32RightOffset(%d) is too large(%d)\n"
                      "Or TopOffset(%d) add u32BottomOffset(%d) is too large(%d)\n",
                      pCrpRct->u32LeftOffset, pCrpRct->u32RightOffset, u32SrcW,
                      pCrpRct->u32TopOffset, pCrpRct->u32BottomOffset, u32SrcH);
            return;
        }

        pstInCropRect->s32X = pCrpRct->u32LeftOffset;
        pstInCropRect->s32Y = pCrpRct->u32TopOffset;
        pstInCropRect->s32Width  = u32SrcW - (pCrpRct->u32LeftOffset + pCrpRct->u32RightOffset);
        pstInCropRect->s32Height = u32SrcH - (pCrpRct->u32TopOffset + pCrpRct->u32BottomOffset);

    }
    else
    {
        HI_RECT_S *pInRct;

        pInRct = &pstInst->stPort[PortId].stInRect;

        if ((pInRct->s32X < 0) || (pInRct->s32Y < 0) || (pInRct->s32Width <= 0) || (pInRct->s32Height <= 0))
        {
            VPSS_INFO("s32X(%d)  s32Y(%d) s32Width(%d) s32Height(%d) is invaild\n",
                      pInRct->s32X, pInRct->s32Y, pInRct->s32Width, pInRct->s32Height);

            return;
        }
        if ((HI_DRV_FT_NOT_STEREO != pstInst->stSrcImage.eFrmType)
            && ((pstInCropRect->s32X != pInRct->s32X)
                || (pstInCropRect->s32Y != pInRct->s32Y)
                || (pstInCropRect->s32Width != pInRct->s32Width)
                || (pstInCropRect->s32Height != pInRct->s32Height)))
        {
            VPSS_INFO("3d not support crop,pInRct s32X(%d), s32Y(%d)\n"
                      "s32Width(%d),s32Height(%d)\n",
                      pInRct->s32X, pInRct->s32Y,
                      pInRct->s32Width, pInRct->s32Height);
            return;
        }
        if (((pInRct->s32X + pInRct->s32Width) > u32SrcW)
            || ((pInRct->s32Y + pInRct->s32Height) > u32SrcH))
        {
            VPSS_INFO("s32X(%d) add s32Width(%d) is too large  u32SrcW(%d)n"
                      "Or s32Y(%d) add s32Height(%d) is too large  u32SrcH(%d)n",
                      pInRct->s32X, pInRct->s32Width, u32SrcW,
                      pInRct->s32Y, pInRct->s32Height, u32SrcH);

            return;
        }

        pstInCropRect->s32X = pInRct->s32X;
        pstInCropRect->s32Y = pInRct->s32Y;
        pstInCropRect->s32Width  = pInRct->s32Width;
        pstInCropRect->s32Height = pInRct->s32Height;

    }
#endif

    return;
}

HI_VOID VPSS_INST_GetVideoRect(VPSS_INSTANCE_S *pstInst,
                               HI_U32 PortId,
                               HI_RECT_S *pstInCropRect,
                               HI_RECT_S *pstVideoRect,
                               HI_RECT_S *pstOutCropRect)
{
    HI_U32 u32DstW;
    HI_U32 u32DstH;

    HI_S32 s32Ret;
    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_IN_INTF_S stInIntf;
    s32Ret = VPSS_IN_GetIntf(&(pstInst->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return ;
    }
    s32Ret = stInIntf.pfnGetProcessImage(&pstInst->stInEntity, &pstCur);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
        return ;
    }

#ifdef ZME_2L_TEST
    if (HI_TRUE == pstInst->stPort[PortId].bNeedZME2L) //�����Ҫ�������ţ��������������Ϊ�������
    {
        u32DstW = pstInst->stPort[PortId].u32ZME1LWidth;
        u32DstH = pstInst->stPort[PortId].u32ZME1LHeight;
        pstInst->stPort[PortId].bNeedZME2L = HI_FALSE;

        VPSS_DBG_INFO("Dst w h %d %d\n", u32DstW, u32DstH);
    }
    else if (HI_TRUE == pstInst->stPort[PortId].bNeedRotate)
    {
        u32DstW = pstInst->stPort[PortId].s32OutputHeight;
        u32DstH = pstInst->stPort[PortId].s32OutputWidth;
#ifndef VPSS_HAL_WITH_CBB
        pstInst->stPort[PortId].bNeedRotate = HI_FALSE;
#endif
        VPSS_DBG_INFO("Dst w h %d %d\n", u32DstW, u32DstH);
    }
    else
    {
        u32DstW = pstInst->stPort[PortId].s32OutputWidth;
        u32DstH = pstInst->stPort[PortId].s32OutputHeight;

        VPSS_DBG_INFO("Dst w h %d %d\n", u32DstW, u32DstH);
    }
#else
    if ((HI_DRV_VPSS_ROTATION_90 == pstInst->stPort[PortId].enRotation)
        || (HI_DRV_VPSS_ROTATION_270 == pstInst->stPort[PortId].enRotation))
    {
        u32DstW = pstInst->stPort[PortId].s32OutputHeight;
        u32DstH = pstInst->stPort[PortId].s32OutputWidth;
    }
    else
    {
        u32DstW = pstInst->stPort[PortId].s32OutputWidth;
        u32DstH = pstInst->stPort[PortId].s32OutputHeight;
    }
#endif

    if ((u32DstW == 0) || u32DstH == 0)
    {
#ifndef VPSS_HAL_WITH_CBB
        if ((HI_DRV_VPSS_ROTATION_90 == pstInst->stPort[PortId].enRotation)
            || (HI_DRV_VPSS_ROTATION_270 == pstInst->stPort[PortId].enRotation))
#else
        if (pstInst->stPort[PortId].bNeedRotate)
#endif
        {
            u32DstW = pstInCropRect->s32Height;
            u32DstH = pstInCropRect->s32Width;

            VPSS_DBG_INFO("Dst w h %d %d\n", u32DstW, u32DstH);
        }
        else
        {
            u32DstW = pstInCropRect->s32Width;
            u32DstH = pstInCropRect->s32Height;
        }

        if (HI_DRV_FT_TAB == pstCur->eFrmType)
        {
            u32DstH = 2 * u32DstH;
        }
        else if (HI_DRV_FT_SBS == pstCur->eFrmType)
        {
            u32DstW = 2 * u32DstW;
        }


        pstVideoRect->s32X = 0;
        pstVideoRect->s32Y = 0;
        pstVideoRect->s32Width  = u32DstW;
        pstVideoRect->s32Height = u32DstH;


        pstOutCropRect->s32X = pstInCropRect->s32X;
        pstOutCropRect->s32Y = pstInCropRect->s32Y;
        pstOutCropRect->s32Width = pstInCropRect->s32Width;
        pstOutCropRect->s32Height = pstInCropRect->s32Height;


        VPSS_DBG_INFO("pstVideoRect w h %d %d\n", pstVideoRect->s32Width, pstVideoRect->s32Height);

        return;
    }

    pstVideoRect->s32X = 0;
    pstVideoRect->s32Y = 0;
    pstVideoRect->s32Width  = u32DstW;
    pstVideoRect->s32Height = u32DstH;
    VPSS_DBG_INFO("Port ASP:%d \n", pstInst->stPort[PortId].eAspMode);

    if (pstInst->stPort[PortId].eAspMode == HI_DRV_ASP_RAT_MODE_TV)
    {
        HI_RECT_S *pVRct;

        pVRct = &pstInst->stPort[PortId].stVideoRect;

        if ((pVRct->s32X < 0) || (pVRct->s32Y < 0) || (pVRct->s32Width <= 0) || (pVRct->s32Height <= 0))
        {
            VPSS_INFO("s32X(%d)  s32Y(%d) s32Width(%d) s32Height(%d) is invaild\n",
                      pVRct->s32X, pVRct->s32Y, pVRct->s32Width, pVRct->s32Height);

            return;
        }

        if (((pVRct->s32X + pVRct->s32Width) > u32DstW)
            || ((pVRct->s32Y + pVRct->s32Height) > u32DstH))
        {
            VPSS_WARN("s32X(%d) add s32Width(%d) is too large  u32DstW(%d)\n"
                      "Or s32Y(%d) add s32Height(%d) is too large  u32DstH(%d)\n",
                      pVRct->s32X, pVRct->s32Width, u32DstW,
                      pVRct->s32Y, pVRct->s32Height, u32DstH);

            return;
        }

        pstVideoRect->s32X = pVRct->s32X;
        pstVideoRect->s32Y = pVRct->s32Y;
        pstVideoRect->s32Width  = pVRct->s32Width;
        pstVideoRect->s32Height = pVRct->s32Height;
    }
    else if (pstInst->stPort[PortId].eAspMode == HI_DRV_ASP_RAT_MODE_LETTERBOX
             || pstInst->stPort[PortId].eAspMode == HI_DRV_ASP_RAT_MODE_COMBINED
             || pstInst->stPort[PortId].eAspMode == HI_DRV_ASP_RAT_MODE_PANANDSCAN)
    {
        HI_RECT_S stScreen;
        HI_RECT_S stOutWnd;
        HI_S32 s32Ret;
        HI_U32 u32InHeight;
        HI_U32 u32InWidth;

        VPSS_PORT_S *pstPort;

        HI_DRV_VIDEO_FRAME_S *pstImg;

        ALG_RATIO_DRV_PARA_S stAspDrvPara;
        ALG_RATIO_OUT_PARA_S stAspOutPara;
        VPSS_IN_INTF_S stIntf = {0};

        (HI_VOID)VPSS_IN_GetIntf(&(pstInst->stInEntity), &stIntf);

        pstPort = &(pstInst->stPort[PortId]);

        if (HI_NULL == stIntf.pfnGetProcessImage)
        {
            return;
        }

        /* INInfo */
        s32Ret = stIntf.pfnGetProcessImage(&(pstInst->stInEntity), &pstImg);
        if (HI_FAILURE == s32Ret)
        {
            pstVideoRect->s32X = 0;
            pstVideoRect->s32Y = 0;
            pstVideoRect->s32Width  = u32DstW;
            pstVideoRect->s32Height = u32DstH;
            return ;
        }

        stScreen.s32Height = pstPort->stScreen.s32Height;
        stScreen.s32Width = pstPort->stScreen.s32Width;
        stScreen.s32X = pstPort->stScreen.s32X;
        stScreen.s32Y = pstPort->stScreen.s32Y;

        /*To calculate Rotation AspectRatinTransfer, we must use the origin OutRect*/
        if (pstPort->s32OutputHeight != 0
            && pstPort->s32OutputWidth != 0)
        {
            stOutWnd.s32Height = pstPort->s32OutputHeight;
            stOutWnd.s32Width = pstPort->s32OutputWidth;
        }
        else
        {
            stOutWnd.s32Height = pstImg->u32Height;
            stOutWnd.s32Width = pstImg->u32Width;
        }

        stOutWnd.s32X = 0;
        stOutWnd.s32Y = 0;

        stAspDrvPara.AspectHeight = pstImg->u32AspectHeight;
        stAspDrvPara.AspectWidth  = pstImg->u32AspectWidth;

        stAspDrvPara.DeviceHeight = pstPort->stDispPixAR.u32ARh;
        stAspDrvPara.DeviceWidth  = pstPort->stDispPixAR.u32ARw;

        stAspDrvPara.eAspMode = pstPort->eAspMode;

        stAspDrvPara.stInWnd.s32X = 0;
        stAspDrvPara.stInWnd.s32Y = 0;

        u32InHeight = pstInCropRect->s32Height;
        u32InWidth = pstInCropRect->s32Width;

        if (pstImg->eFrmType == HI_DRV_FT_NOT_STEREO
            || pstImg->eFrmType == HI_DRV_FT_FPK)
        {
            stAspDrvPara.stInWnd.s32Height = u32InHeight;
            stAspDrvPara.stInWnd.s32Width = u32InWidth;
        }
        else if (pstImg->eFrmType == HI_DRV_FT_SBS)
        {
            stAspDrvPara.stInWnd.s32Height = u32InHeight;
            stAspDrvPara.stInWnd.s32Width = u32InWidth;
        }
        else if (pstImg->eFrmType == HI_DRV_FT_TAB)
        {
            stAspDrvPara.stInWnd.s32Height = u32InHeight;
            stAspDrvPara.stInWnd.s32Width = u32InWidth;
        }
        else
        {
            stAspDrvPara.stInWnd.s32Height = u32InHeight;
            stAspDrvPara.stInWnd.s32Width = u32InWidth;
        }

        stAspDrvPara.stOutWnd.s32X = 0;
        stAspDrvPara.stOutWnd.s32Y = 0;
        stAspDrvPara.stOutWnd.s32Height = stOutWnd.s32Height;
        stAspDrvPara.stOutWnd.s32Width = stOutWnd.s32Width;

        stAspDrvPara.stScreen.s32X = stScreen.s32X;
        stAspDrvPara.stScreen.s32Y = stScreen.s32Y;
        stAspDrvPara.stScreen.s32Height = stScreen.s32Height;
        stAspDrvPara.stScreen.s32Width = stScreen.s32Width;

        if (pstPort->stCustmAR.u32ARh != 0
            && pstPort->stCustmAR.u32ARw != 0)
        {
            stAspDrvPara.stUsrAsp.bUserDefAspectRatio = HI_TRUE;
        }
        else
        {
            stAspDrvPara.stUsrAsp.bUserDefAspectRatio = HI_FALSE;
        }

        stAspDrvPara.stUsrAsp.u32UserAspectHeight = pstPort->stCustmAR.u32ARh;
        stAspDrvPara.stUsrAsp.u32UserAspectWidth = pstPort->stCustmAR.u32ARw;

#if 1
        switch (pstPort->enRotation)
        {
            case HI_DRV_VPSS_ROTATION_DISABLE:
            case HI_DRV_VPSS_ROTATION_180:
                break;
            case HI_DRV_VPSS_ROTATION_90:
            case HI_DRV_VPSS_ROTATION_270:
                stAspDrvPara.stOutWnd.s32Width = stOutWnd.s32Height;
                stAspDrvPara.stOutWnd.s32Height = stOutWnd.s32Width;
                stAspDrvPara.stScreen.s32X = stScreen.s32Y;
                stAspDrvPara.stScreen.s32Y = stScreen.s32X;
                stAspDrvPara.stScreen.s32Height = stScreen.s32Width;
                stAspDrvPara.stScreen.s32Width = stScreen.s32Height;
                stAspDrvPara.stUsrAsp.u32UserAspectHeight = pstPort->stCustmAR.u32ARw;
                stAspDrvPara.stUsrAsp.u32UserAspectWidth = pstPort->stCustmAR.u32ARh;
                stAspDrvPara.DeviceHeight = pstPort->stDispPixAR.u32ARw;
                stAspDrvPara.DeviceWidth  = pstPort->stDispPixAR.u32ARh;
                break;
            default:
                VPSS_FATAL("Invalid Rotation Type %d\n", pstPort->enRotation);
                break;
        }
#endif
        stAspOutPara.bEnAsp = HI_TRUE;
        ALG_ASP_GetConfig(&stAspDrvPara,
                          pstPort->eAspMode, &stScreen,
                          &stAspOutPara);


        if (pstInst->stPort[PortId].eAspMode == HI_DRV_ASP_RAT_MODE_LETTERBOX)
        {
            /*Get Zme out H/W via AspAlg*/
            pstVideoRect->s32X = stAspOutPara.stOutWnd.s32X;
            pstVideoRect->s32Y = stAspOutPara.stOutWnd.s32Y;
            pstVideoRect->s32Width  = stAspOutPara.stOutWnd.s32Width;
            pstVideoRect->s32Height = stAspOutPara.stOutWnd.s32Height;

            pstOutCropRect->s32X        = pstInCropRect->s32X;
            pstOutCropRect->s32Y        = pstInCropRect->s32Y;
            pstOutCropRect->s32Width    = pstInCropRect->s32Width;
            pstOutCropRect->s32Height   = pstInCropRect->s32Height;
        }
        else
        {
            pstVideoRect->s32X = 0;
            pstVideoRect->s32Y = 0;
            pstVideoRect->s32Width  = stAspOutPara.u32ZmeW;
            pstVideoRect->s32Height = stAspOutPara.u32ZmeH;

            pstOutCropRect->s32X = stAspOutPara.stCropWnd.s32X;
            pstOutCropRect->s32Y = stAspOutPara.stCropWnd.s32Y;
            pstOutCropRect->s32Width = stAspOutPara.stCropWnd.s32Width;
            pstOutCropRect->s32Height = stAspOutPara.stCropWnd.s32Height;
        }
    }
    else if (pstInst->stPort[PortId].eAspMode == HI_DRV_ASP_RAT_MODE_FULL)
    {
        pstVideoRect->s32X = 0;
        pstVideoRect->s32Y = 0;
        pstVideoRect->s32Width  = u32DstW;
        pstVideoRect->s32Height = u32DstH;

        VPSS_DBG_INFO("pstVideoRect w h %d %d\n", pstVideoRect->s32Width, pstVideoRect->s32Height);

        pstOutCropRect->s32X = pstInCropRect->s32X;
        pstOutCropRect->s32Y = pstInCropRect->s32Y;
        pstOutCropRect->s32Width = pstInCropRect->s32Width;
        pstOutCropRect->s32Height = pstInCropRect->s32Height;
        VPSS_DBG_INFO("FULL Vrect W H %d %d\n", pstVideoRect->s32Width, pstVideoRect->s32Height);
        VPSS_DBG_INFO("FULL InCrop W H %d %d\n", pstInCropRect->s32Width, pstInCropRect->s32Height);
    }
    else
    {
        pstVideoRect->s32X = 0;
        pstVideoRect->s32Y = 0;
        pstVideoRect->s32Width  = u32DstW;
        pstVideoRect->s32Height = u32DstH;
        pstOutCropRect->s32X = 0;
        pstOutCropRect->s32Y = 0;
        pstOutCropRect->s32Width = pstVideoRect->s32Width;
        pstOutCropRect->s32Height = pstVideoRect->s32Height;
        VPSS_WARN("Aspect Mode %d can't support\n", pstInst->stPort[PortId].eAspMode);

    }
    VPSS_DBG_INFO("pstVideoRect w h %d %d\n", pstVideoRect->s32Width, pstVideoRect->s32Height);

}
HI_VOID VPSS_INST_GetRotate(VPSS_INSTANCE_S *pstInst, HI_U32 PortId, VPSS_HAL_PORT_INFO_S *pstHalPortInfo, HI_DRV_VIDEO_FRAME_S *pstFrm)
{
    if (pstInst->stPort[PortId].enRotation == HI_DRV_VPSS_ROTATION_180)
    {
        pstHalPortInfo->bNeedFlip = HI_TRUE;
        pstHalPortInfo->bNeedMirror = HI_TRUE;
    }
    else
    {
        pstHalPortInfo->bNeedFlip = HI_FALSE;
        pstHalPortInfo->bNeedMirror = HI_FALSE;
    }

    if (pstFrm->u32Circumrotate != 0)
    {
        pstHalPortInfo->bNeedFlip = !pstHalPortInfo->bNeedFlip;
    }

    pstHalPortInfo->enRotation = pstInst->stPort[PortId].enRotation;

    if (pstInst->stPort[PortId].bHoriFlip == HI_TRUE)
    {
        pstHalPortInfo->bNeedMirror = !pstHalPortInfo->bNeedMirror;
    }

    if (pstInst->stPort[PortId].bVertFlip == HI_TRUE)
    {
        pstHalPortInfo->bNeedFlip = !pstHalPortInfo->bNeedFlip;
    }

#ifdef VPSS_HAL_WITH_CBB
    if ((pstInst->stPort[PortId].enRotation == HI_DRV_VPSS_ROTATION_90)
        || (pstInst->stPort[PortId].enRotation == HI_DRV_VPSS_ROTATION_270))

    {
        pstHalPortInfo->bNeedRota = HI_TRUE;
        pstInst->stPort[PortId].bNeedRotate = HI_TRUE;
    }
    else
    {
        pstHalPortInfo->bNeedRota = HI_FALSE;
        pstInst->stPort[PortId].bNeedRotate = HI_FALSE;
    }
#endif
    return ;
}
#define VPSS_SAVE_SUB(a,b) (((a)<=(b))?0:((a)-(b)))

#define VPSS_PRINT_RECT(name, a) \
    do{\
        break;printk("%s, Top:%d, Bot:%d, Left:%d, Right:%d\n", \
                     name,\
                     a.u32TopOffset,\
                     a.u32BottomOffset,\
                     a.u32LeftOffset,\
                     a.u32RightOffset);\
    }while(0)


HI_VOID VPSS_INST_LBX_DET(VPSS_LBX_DET_S *pstLbxDet, HI_U32 u32sttWbcInfo)
{
#if 0
    HI_U32 i;
    S_VPSSWB_REGS_TYPE *psttwbcInfo;

    /* ��ȡ�Ĵ�����LBX��Ϣ, ֻ�����۵�ͳ����Ϣ */
    psttwbcInfo = (S_VPSSWB_REGS_TYPE *)u32sttWbcInfo;

    pstLbxDet->u32valid_top   = psttwbcInfo->LBD_INFO_0.bits.lbd_fix_top;
    pstLbxDet->u32valid_bot   = psttwbcInfo->LBD_INFO_0.bits.lbd_fix_bot;
    pstLbxDet->u32valid_left  = psttwbcInfo->LBD_INFO_1.bits.lbd_fix_left;
    pstLbxDet->u32valid_right = psttwbcInfo->LBD_INFO_1.bits.lbd_fix_right;

    pstLbxDet->m_top[pstLbxDet->u32NodeIndex]   = pstLbxDet->u32valid_top;
    pstLbxDet->m_bot[pstLbxDet->u32NodeIndex]   = pstLbxDet->u32valid_bot;
    pstLbxDet->m_left[pstLbxDet->u32NodeIndex]  = pstLbxDet->u32valid_left;
    pstLbxDet->m_right[pstLbxDet->u32NodeIndex] = pstLbxDet->u32valid_right;

    for (i = 0; i < VPSS_LBX_DET_NODE_NUM; i++)
    {
        if ( pstLbxDet->m_top[i] < pstLbxDet->u32valid_top)
        {
            pstLbxDet->u32valid_top = pstLbxDet->m_top[i];
        }
        if ( pstLbxDet->m_bot[i] > pstLbxDet->u32valid_bot)
        {
            pstLbxDet->u32valid_bot = pstLbxDet->m_bot[i];
        }
        if ( pstLbxDet->m_left[i] < pstLbxDet->u32valid_left)
        {
            pstLbxDet->u32valid_left = pstLbxDet->m_left[i];
        }
        if ( pstLbxDet->m_right[i] > pstLbxDet->u32valid_right)
        {
            pstLbxDet->u32valid_right = pstLbxDet->m_right[i];
        }
    }

    pstLbxDet->u32NodeIndex = (pstLbxDet->u32NodeIndex + 1) % 32;
#endif
}

HI_VOID VPSS_INST_GetLbxInfo(VPSS_INSTANCE_S *pstInst, HI_U32 PortId, HI_RECT_S *pstLbx)
{
    HI_U32 u32SrcW = 0, u32SrcH = 0;
    HI_U32 u32DstW = 0, u32DstH = 0;
    HI_RECT_S stInRect;
#if 0
    HI_RECT_S stVideoRect;
    HI_DRV_CROP_RECT_S stLdb;  /* Ӳ�����Ľ�� */
    HI_DRV_CROP_RECT_S stCrop; /* �û����õ�CROP */
    HI_DRV_CROP_RECT_S stLeave;/* Ӳ������ȥCROPʣ�µĲ��� */
    HI_DRV_CROP_RECT_S stCalc; /* ��������֮���LBX */
    HI_DRV_CROP_RECT_S stAdd;  /* �û��¼ӵ�LBX */
    HI_DRV_CROP_RECT_S stFinal;/* ���յ�LBX */
#endif
    VPSS_IN_STREAM_INFO_S stInfo;
    VPSS_IN_INTF_S stIntf = {0};
    VPSS_PORT_S *pstPort;

    (HI_VOID)VPSS_IN_GetIntf(&(pstInst->stInEntity), &stIntf);

    if (stIntf.pfnGetInfo == HI_NULL)
    {
        return;
    }

    (HI_VOID)stIntf.pfnGetInfo(&(pstInst->stInEntity),
                               VPSS_IN_INFO_STREAM,
                               HI_DRV_BUF_ADDR_MAX,
                               &stInfo);


    u32SrcW = stInfo.u32StreamW;
    u32SrcH = stInfo.u32StreamH;

    VPSS_INST_GetInCrop(pstInst, PortId, &stInRect);

    pstPort = &pstInst->stPort[PortId];

    u32DstW = pstPort->s32OutputWidth;
    u32DstH = pstPort->s32OutputHeight;

    if ((u32DstW == 0) || (u32DstH == 0))
    {
        u32DstW = (HI_U32)stInRect.s32Width;
        u32DstH = (HI_U32)stInRect.s32Height;
    }
#if 0
    (HI_VOID)stIntf.pfnGetInfo(&(pstInst->stInEntity),
                               VPSS_IN_INFO_WBCREG_VA,
                               HI_DRV_BUF_ADDR_LEFT,
                               &u32WbcRegVirAddr);

    VPSS_INST_LBX_DET(&pstInst->stLbxDet, u32WbcRegVirAddr);

    stLdb.u32TopOffset  = pstInst->stLbxDet.u32valid_top + 1;
    stLdb.u32LeftOffset = pstInst->stLbxDet.u32valid_left + 1;
    stLdb.u32BottomOffset
        = VPSS_SAVE_SUB(u32SrcH, pstInst->stLbxDet.u32valid_bot);
    stLdb.u32RightOffset
        = VPSS_SAVE_SUB(u32SrcW, pstInst->stLbxDet.u32valid_right);

    VPSS_PRINT_RECT("stLdb", stLdb);


    /* ��ȡ�ü�����Ϣ */
    stCrop.u32TopOffset  = (HI_U32)stInRect.s32Y;
    stCrop.u32LeftOffset = (HI_U32)stInRect.s32X;
    stCrop.u32BottomOffset
        = VPSS_SAVE_SUB(u32SrcH, ((HI_U32)stInRect.s32Y + (HI_U32)stInRect.s32Height));
    stCrop.u32RightOffset
        = VPSS_SAVE_SUB(u32SrcW, ((HI_U32)stInRect.s32X + (HI_U32)stInRect.s32Width));

    VPSS_PRINT_RECT("stCrop", stCrop);

    /* ʣ���LBX��Ϣ */
    stLeave.u32TopOffset    = VPSS_SAVE_SUB(stLdb.u32TopOffset, stCrop.u32TopOffset);
    stLeave.u32LeftOffset   = VPSS_SAVE_SUB(stLdb.u32LeftOffset, stCrop.u32LeftOffset);
    stLeave.u32BottomOffset = VPSS_SAVE_SUB(stLdb.u32BottomOffset, stCrop.u32BottomOffset);
    stLeave.u32RightOffset  = VPSS_SAVE_SUB(stLdb.u32RightOffset, stCrop.u32RightOffset);

    VPSS_PRINT_RECT("stLeave", stLeave);

    /* ��������֮���LBX��Ϣ */
    VPSS_INST_GetVideoRect(pstInst, PortId, &stInRect, &stVideoRect);

    stCalc.u32TopOffset    = (stLeave.u32TopOffset * (HI_U32)stVideoRect.s32Height * 1024 + 512)
                             / ((HI_U32)stInRect.s32Height * 1024);
    stCalc.u32LeftOffset   = (stLeave.u32LeftOffset * (HI_U32)stVideoRect.s32Width * 1024 + 512)
                             / ((HI_U32)stInRect.s32Width * 1024);
    stCalc.u32BottomOffset = (stLeave.u32BottomOffset * (HI_U32)stVideoRect.s32Height * 1024 + 512)
                             / ((HI_U32)stInRect.s32Height * 1024);
    stCalc.u32RightOffset  = (stLeave.u32RightOffset * (HI_U32)stVideoRect.s32Width * 1024 + 512)
                             / ((HI_U32)stInRect.s32Width * 1024);

    VPSS_PRINT_RECT("stCalc", stCalc);

    /* �¼ӵ�LBX��Ϣ */
    stAdd.u32TopOffset  = (HI_U32)stVideoRect.s32Y;
    stAdd.u32LeftOffset = (HI_U32)stVideoRect.s32X;
    stAdd.u32BottomOffset
        = VPSS_SAVE_SUB(u32DstH, ((HI_U32)stVideoRect.s32Y + (HI_U32)stVideoRect.s32Height));
    stAdd.u32RightOffset
        = VPSS_SAVE_SUB(u32DstW, ((HI_U32)stVideoRect.s32X + (HI_U32)stVideoRect.s32Width));
    VPSS_PRINT_RECT("stAdd", stAdd);

    /* ���յ�LBX��Ϣ */
    stFinal.u32TopOffset    = stCalc.u32TopOffset + stAdd.u32TopOffset;
    stFinal.u32LeftOffset   = stCalc.u32LeftOffset + stAdd.u32LeftOffset;
    stFinal.u32BottomOffset = stCalc.u32BottomOffset + stAdd.u32BottomOffset;
    stFinal.u32RightOffset  = stCalc.u32RightOffset + stAdd.u32RightOffset;

    VPSS_PRINT_RECT("stFinal", stFinal);

    pstLbx->s32X = (HI_S32)stFinal.u32LeftOffset;
    pstLbx->s32Y = (HI_S32)stFinal.u32TopOffset;
    pstLbx->s32Width  = (HI_S32)(VPSS_SAVE_SUB(u32DstW, (stFinal.u32LeftOffset + stFinal.u32RightOffset)));
    pstLbx->s32Height = (HI_S32)(VPSS_SAVE_SUB(u32DstH, (stFinal.u32TopOffset + stFinal.u32BottomOffset)));
#else
    pstLbx->s32X = 0;
    pstLbx->s32Y = 0;
    pstLbx->s32Width  = u32DstW;
    pstLbx->s32Height = u32DstH;
#endif
}

HI_S32 VPSS_INST_GetPortPrc(VPSS_INSTANCE_S *pstInstance, VPSS_HANDLE hPort, VPSS_PORT_PRC_S *pstPortPrc)
{
    VPSS_PORT_S *pstPort;
    pstPort = HI_NULL;

    if (hPort == VPSS_INVALID_HANDLE)
    {
        memset(pstPortPrc, 0, sizeof(VPSS_PORT_PRC_S));
        pstPortPrc->s32PortId = VPSS_INVALID_HANDLE;
    }
    else
    {
        pstPort = VPSS_INST_GetPort(pstInstance, hPort);
        if (pstPort == HI_NULL)
        {
            VPSS_FATAL("Get Port Proc Error.\n");
            return HI_FAILURE;
        }
        pstPortPrc->s32PortId = pstPort->s32PortId ;
        pstPortPrc->bEnble = pstPort->bEnble ;
        pstPortPrc->eFormat = pstPort->eFormat ;
        pstPortPrc->s32OutputWidth = pstPort->s32OutputWidth ;
        pstPortPrc->s32OutputHeight = pstPort->s32OutputHeight ;
        pstPortPrc->eDstCS = pstPort->eDstCS ;
        pstPortPrc->stDispPixAR = pstPort->stDispPixAR ;
        pstPortPrc->eAspMode = pstPort->eAspMode ;
        pstPortPrc->stCustmAR = pstPort->stCustmAR ;
        pstPortPrc->bInterlaced = pstPort->bInterlaced ;
        pstPortPrc->stScreen = pstPort->stScreen ;
        pstPortPrc->u32MaxFrameRate = pstPort->u32MaxFrameRate ;
        pstPortPrc->u32OutCount = pstPort->u32OutCount ;
        pstPortPrc->stProcCtrl = pstPort->stProcCtrl ;
        pstPortPrc->bTunnelEnable = pstPort->bTunnelEnable ;
        pstPortPrc->s32SafeThr = pstPort->s32SafeThr ;
        pstPortPrc->b3Dsupport = pstPort->b3Dsupport;
        pstPortPrc->stBufListCfg.eBufType = pstPort->stFrmInfo.stBufListCfg.eBufType;
        pstPortPrc->stBufListCfg.u32BufNumber = pstPort->stFrmInfo.stBufListCfg.u32BufNumber;
        pstPortPrc->stBufListCfg.u32BufSize = pstPort->stFrmInfo.stBufListCfg.u32BufSize;
        pstPortPrc->stBufListCfg.u32BufStride = pstPort->stFrmInfo.stBufListCfg.u32BufStride;

        pstPortPrc->bVertFlip = pstPort->bVertFlip;
        pstPortPrc->bHoriFlip = pstPort->bHoriFlip;
        pstPortPrc->enRotation = pstPort->enRotation;
        VPSS_FB_GetState(&(pstPort->stFrmInfo), &(pstPortPrc->stFbPrc));
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_INST_GetSrcListState(VPSS_INSTANCE_S *pstInstance, VPSS_IN_IMAGELIST_STATE_S *pstListState)
{
    VPSS_IN_ENTITY_S *pstInEntity;
    pstInEntity = &pstInstance->stInEntity;

    pstListState->u32GetUsrTotal        = pstInEntity->stListState.u32GetUsrTotal;
    pstListState->u32GetUsrSuccess      = pstInEntity->stListState.u32GetUsrSuccess;
    pstListState->u32RelUsrTotal        = pstInEntity->stListState.u32RelUsrTotal;
    pstListState->u32RelUsrSuccess      = pstInEntity->stListState.u32RelUsrSuccess;

    pstListState->u32PutSrcCount        = pstInEntity->stListState.u32PutSrcCount;
    pstListState->u32CompleteSrcCount   = pstInEntity->stListState.u32CompleteSrcCount;
    pstListState->u32ReleaseSrcCount    = pstInEntity->stListState.u32ReleaseSrcCount;

    return HI_SUCCESS;
}


HI_S32 VPSS_INST_SetUhdLevel(VPSS_INSTANCE_S *pstInstance, HI_U32 u32WidthLevel, HI_U32 u32HeightLevel)
{
    unsigned long flags;

    if ((VPSS_UHD_LOW_W == u32WidthLevel
         || VPSS_UHD_MIDDLE_W == u32WidthLevel
         || VPSS_UHD_HIGH_W == u32WidthLevel)
        && (VPSS_UHD_LOW_H == u32HeightLevel
            || VPSS_UHD_MIDDLE_H == u32HeightLevel
            || VPSS_UHD_HIGH_H == u32HeightLevel)
       )
    {

    }
    else
    {
        VPSS_ERROR("Invalid Level W %d Level H %d");
        return HI_FAILURE;
    }

    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    pstInstance->u32UhdUsrLevelW = u32WidthLevel;
    pstInstance->u32UhdUsrLevelH = u32HeightLevel;
    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_LevelRectInit(HI_RECT_S pMatrixRect[][5])
{
    pMatrixRect[0][0].s32Width = VPSS_UHD_LOW_W;
    pMatrixRect[0][0].s32Height = VPSS_UHD_LOW_H;
    pMatrixRect[0][1].s32Width = 0xffffffff;
    pMatrixRect[0][1].s32Height = 0xffffffff;
    pMatrixRect[0][2].s32Width = 0xffffffff;
    pMatrixRect[0][2].s32Height = 0xffffffff;
    pMatrixRect[0][3].s32Width = 0xffffffff;
    pMatrixRect[0][3].s32Height = 0xffffffff;
    pMatrixRect[0][4].s32Width = 0xffffffff;
    pMatrixRect[0][4].s32Height = 0xffffffff;

    pMatrixRect[1][0].s32Width = VPSS_UHD_MIDDLE_W;
    pMatrixRect[1][0].s32Height = VPSS_UHD_MIDDLE_H;
    pMatrixRect[1][1].s32Width = 0xffffffff;
    pMatrixRect[1][1].s32Height = 0xffffffff;
    pMatrixRect[1][2].s32Width = 0xffffffff;
    pMatrixRect[1][2].s32Height = 0xffffffff;
    pMatrixRect[1][3].s32Width = 0xffffffff;
    pMatrixRect[1][3].s32Height = 0xffffffff;
    pMatrixRect[1][4].s32Width = 0xffffffff;
    pMatrixRect[1][4].s32Height = 0xffffffff;

    pMatrixRect[2][0].s32Width = VPSS_UHD_HIGH_W;
    pMatrixRect[2][0].s32Height = VPSS_UHD_HIGH_H;
    pMatrixRect[2][1].s32Width = 0xffffffff;
    pMatrixRect[2][1].s32Height = 0xffffffff;
    pMatrixRect[2][2].s32Width = 0xffffffff;
    pMatrixRect[2][2].s32Height = 0xffffffff;
    pMatrixRect[2][3].s32Width = 0xffffffff;
    pMatrixRect[2][3].s32Height = 0xffffffff;
    pMatrixRect[2][4].s32Width = 0xffffffff;
    pMatrixRect[2][4].s32Height = 0xffffffff;

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_LevelRectSetOriRect(HI_RECT_S pMatrixRect[][5],
                                     HI_S32 s32OriWidth,
                                     HI_S32 s32OriHeight,
                                     HI_S32 s32OriARw,
                                     HI_S32 s32OriARh)
{
    if (s32OriWidth != pMatrixRect[0][1].s32Width
        || s32OriHeight != pMatrixRect[0][1].s32Height)
    {
        pMatrixRect[0][1].s32Width = s32OriWidth;
        pMatrixRect[0][1].s32Height = s32OriHeight;
        pMatrixRect[0][2].s32Width = 0xffffffff;
        pMatrixRect[0][2].s32Height = 0xffffffff;
        pMatrixRect[0][3].s32Width = s32OriARw;
        pMatrixRect[0][3].s32Height = s32OriARh;
        pMatrixRect[0][4].s32Width = 0xffffffff;
        pMatrixRect[0][4].s32Height = 0xffffffff;
    }

    if (s32OriWidth != pMatrixRect[1][1].s32Width
        || s32OriHeight != pMatrixRect[1][1].s32Height)
    {
        pMatrixRect[1][1].s32Width = s32OriWidth;
        pMatrixRect[1][1].s32Height = s32OriHeight;
        pMatrixRect[1][2].s32Width = 0xffffffff;
        pMatrixRect[1][2].s32Height = 0xffffffff;
        pMatrixRect[1][3].s32Width = s32OriARw;
        pMatrixRect[1][3].s32Height = s32OriARh;
        pMatrixRect[1][4].s32Width = 0xffffffff;
        pMatrixRect[1][4].s32Height = 0xffffffff;
    }

    if (s32OriWidth != pMatrixRect[2][1].s32Width
        || s32OriHeight != pMatrixRect[2][1].s32Height)
    {
        pMatrixRect[2][1].s32Width = s32OriWidth;
        pMatrixRect[2][1].s32Height = s32OriHeight;
        pMatrixRect[2][2].s32Width = 0xffffffff;
        pMatrixRect[2][2].s32Height = 0xffffffff;
        pMatrixRect[2][3].s32Width = s32OriARw;
        pMatrixRect[2][3].s32Height = s32OriARh;
        pMatrixRect[2][4].s32Width = 0xffffffff;
        pMatrixRect[2][4].s32Height = 0xffffffff;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_LevelRectSetReviseRect(HI_RECT_S pMatrixRect[][5],
                                        HI_RECT_S stLevelRect,
                                        HI_S32 s32ReviseWidth,
                                        HI_S32 s32ReviseHeight,
                                        HI_S32 s32ReviseARw,
                                        HI_S32 s32ReviseARh)
{
    if (stLevelRect.s32Width == VPSS_UHD_LOW_W
        && stLevelRect.s32Height == VPSS_UHD_LOW_H)
    {
        pMatrixRect[0][2].s32Width = s32ReviseWidth;
        pMatrixRect[0][2].s32Height = s32ReviseHeight;
        pMatrixRect[0][4].s32Width = s32ReviseARw;
        pMatrixRect[0][4].s32Height = s32ReviseARh;
    }
    else if (stLevelRect.s32Width == VPSS_UHD_MIDDLE_W
             && stLevelRect.s32Height == VPSS_UHD_MIDDLE_H)
    {
        pMatrixRect[1][2].s32Width = s32ReviseWidth;
        pMatrixRect[1][2].s32Height = s32ReviseHeight;
        pMatrixRect[1][4].s32Width = s32ReviseARw;
        pMatrixRect[1][4].s32Height = s32ReviseARh;
    }
    else if (stLevelRect.s32Width == VPSS_UHD_HIGH_W
             && stLevelRect.s32Height == VPSS_UHD_HIGH_H)
    {
        pMatrixRect[2][2].s32Width = s32ReviseWidth;
        pMatrixRect[2][2].s32Height = s32ReviseHeight;
        pMatrixRect[2][4].s32Width = s32ReviseARw;
        pMatrixRect[2][4].s32Height = s32ReviseARh;
    }
    else
    {
        VPSS_ERROR("Invalid Level W %d H %d\n",
                   stLevelRect.s32Width,
                   stLevelRect.s32Height);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_LevelRectGetReviseRect(HI_RECT_S pMatrixRect[][5],
                                        HI_RECT_S stLevelRect,
                                        HI_S32 *ps32ReviseWidth,
                                        HI_S32 *ps32ReviseHeight,
                                        HI_S32 *ps32ReviseARw,
                                        HI_S32 *ps32ReviseARh)
{
    if (stLevelRect.s32Width == VPSS_UHD_LOW_W
        && stLevelRect.s32Height == VPSS_UHD_LOW_H)
    {
        *ps32ReviseWidth = pMatrixRect[0][2].s32Width;
        *ps32ReviseHeight = pMatrixRect[0][2].s32Height;
        *ps32ReviseARw = pMatrixRect[0][4].s32Width;
        *ps32ReviseARh = pMatrixRect[0][4].s32Height;
    }
    else if (stLevelRect.s32Width == VPSS_UHD_MIDDLE_W
             && stLevelRect.s32Height == VPSS_UHD_MIDDLE_H)
    {
        *ps32ReviseWidth = pMatrixRect[1][2].s32Width;
        *ps32ReviseHeight = pMatrixRect[1][2].s32Height;
        *ps32ReviseARw = pMatrixRect[1][4].s32Width;
        *ps32ReviseARh = pMatrixRect[1][4].s32Height;
    }
    else if (stLevelRect.s32Width == VPSS_UHD_HIGH_W
             && stLevelRect.s32Height == VPSS_UHD_HIGH_H)
    {
        *ps32ReviseWidth = pMatrixRect[2][2].s32Width;
        *ps32ReviseHeight = pMatrixRect[2][2].s32Height;
        *ps32ReviseARw = pMatrixRect[2][4].s32Width;
        *ps32ReviseARh = pMatrixRect[2][4].s32Height;
    }
    else
    {
        VPSS_ERROR("Invalid Level W %d H %d\n",
                   stLevelRect.s32Width,
                   stLevelRect.s32Height);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_LevelRectGetOriRect(HI_RECT_S pMatrixRect[][5],
                                     HI_RECT_S stLevelRect,
                                     HI_S32 *ps32OriWidth,
                                     HI_S32 *ps32OriHeight,
                                     HI_S32 *ps32OriARw,
                                     HI_S32 *ps32OriARh)
{
    if (stLevelRect.s32Width == VPSS_UHD_LOW_W
        && stLevelRect.s32Height == VPSS_UHD_LOW_H)
    {
        *ps32OriWidth = pMatrixRect[0][1].s32Width;
        *ps32OriHeight = pMatrixRect[0][1].s32Height;
        *ps32OriARw = pMatrixRect[0][3].s32Width;
        *ps32OriARh = pMatrixRect[0][3].s32Height;
    }
    else if (stLevelRect.s32Width == VPSS_UHD_MIDDLE_W
             && stLevelRect.s32Height == VPSS_UHD_MIDDLE_H)
    {
        *ps32OriWidth = pMatrixRect[1][1].s32Width;
        *ps32OriHeight = pMatrixRect[1][1].s32Height;
        *ps32OriARw = pMatrixRect[1][3].s32Width;
        *ps32OriARh = pMatrixRect[1][3].s32Height;
    }
    else if (stLevelRect.s32Width == VPSS_UHD_HIGH_W
             && stLevelRect.s32Height == VPSS_UHD_HIGH_H)
    {
        *ps32OriWidth = pMatrixRect[2][1].s32Width;
        *ps32OriHeight = pMatrixRect[2][1].s32Height;
        *ps32OriARw = pMatrixRect[2][3].s32Width;
        *ps32OriARh = pMatrixRect[2][3].s32Height;
    }
    else
    {
        VPSS_ERROR("Invalid Level W %d H %d\n",
                   stLevelRect.s32Width,
                   stLevelRect.s32Height);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_INST_EnableStorePriv(VPSS_INSTANCE_S *pstInstance, HI_BOOL bStore)
{
    unsigned long flags;

    if (bStore != HI_TRUE && bStore != HI_FALSE)
    {
        VPSS_ERROR("Invalid para bStore %d\n", bStore);
        return HI_FAILURE;
    }

    VPSS_OSAL_DownSpin(&(pstInstance->stUsrSetSpin), &flags);
    pstInstance->bStorePrivData = bStore;
    VPSS_OSAL_UpSpin(&(pstInstance->stUsrSetSpin), &flags);

    return HI_SUCCESS;
}
HI_S32 VPSS_INST_SyncTvpCfg(VPSS_INSTANCE_S *pstInstance)
{
    HI_BOOL bSecure;

    bSecure = pstInstance->stUsrInstCfg.bSecure;

    if (pstInstance->bSecure != bSecure)
    {
        if (pstInstance->bTvpFirstCfg == HI_TRUE)
        {
            pstInstance->bSecure = bSecure;

            pstInstance->bTvpFirstCfg = HI_FALSE;
        }
        else
        {
            VPSS_ERROR("vpss is working ,can't change secure config from %d to %d\n", pstInstance->bSecure, bSecure);
        }
    }

    return HI_SUCCESS;
}

HI_BOOL VPSS_INST_CheckPassThroughForVO(VPSS_INSTANCE_S *pstInstance, HI_DRV_VIDEO_FRAME_S *pstInImage)
{
    HI_U32 u32Count;
    HI_BOOL bPassThrough = HI_TRUE;
    VPSS_PORT_S *pstPort;

    for (u32Count = 0; u32Count < VPSS_PORT_MAX_NUMB; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->bEnble == HI_TRUE
            && pstPort->s32PortId != HI_INVALID_HANDLE)
        {
#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
            if ((pstPort->s32OutputWidth == 0 && pstPort->s32OutputHeight == 0)
                || (pstPort->s32OutputWidth == pstInImage->u32Width
                    && pstPort->s32OutputHeight == pstInImage->u32Height)
               )
#else
            if ( ( (pstPort->s32OutputWidth == 0 && pstPort->s32OutputHeight == 0)
                   || (pstPort->s32OutputWidth == pstInImage->u32Width
                       && pstPort->s32OutputHeight == pstInImage->u32Height)
                 )
                 && ((pstPort->enRotation == HI_DRV_VPSS_ROTATION_DISABLE)
                     && (pstPort->bHoriFlip == HI_FALSE)
                     && (pstPort->bVertFlip == HI_FALSE))
               )
#endif
            {
                bPassThrough &= HI_TRUE;
            }
            else
            {
                bPassThrough &= HI_FALSE;
            }
        }
    }

    return bPassThrough;
}
HI_BOOL VPSS_INST_CheckPassThroughForOMX(VPSS_INSTANCE_S *pstInstance, HI_DRV_VIDEO_FRAME_S *pstInImage)
{
    HI_U32 u32Count;
    HI_BOOL bPassThrough = HI_TRUE;
    VPSS_PORT_S *pstPort;
    for (u32Count = 0; u32Count < VPSS_PORT_MAX_NUMB; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->bEnble == HI_TRUE
            && pstPort->s32PortId != HI_INVALID_HANDLE)
        {
            if (pstPort->bPassThrough)  //omx do not force vpss to work, vpss can make choose by resolutation etc..
            {
                bPassThrough &= HI_TRUE;
            }
            else //omx need vpss work, for detile ...
            {
                bPassThrough &= HI_FALSE;
            }
        }
    }

    return bPassThrough;
}

HI_VOID VPSS_INST_ReportCompleteEvent(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32                        u32Count;
    VPSS_PORT_S                  *pstPort;
    HI_DRV_VPSS_PORT_AVAILABLE_S  stPortBufState[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE)
        {
            stPortBufState[u32Count].hPort = pstPort->s32PortId;
            stPortBufState[u32Count].bAvailable = VPSS_INST_CheckPortBuffer(pstInstance,
                                                  pstPort->s32PortId);
        }
        else
        {
            stPortBufState[u32Count].hPort = VPSS_INVALID_HANDLE;
            stPortBufState[u32Count].bAvailable = HI_FALSE;
        }
    }

    if (pstInstance->pfUserCallBack != HI_NULL)
    {
        pstInstance->pfUserCallBack(pstInstance->hDst, VPSS_EVENT_TASK_COMPLETE, stPortBufState);
    }
    else
    {
        VPSS_FATAL("Can't report VPSS_EVENT_NEW_FRAME,pfUserCallBack is NULL");
    }

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
