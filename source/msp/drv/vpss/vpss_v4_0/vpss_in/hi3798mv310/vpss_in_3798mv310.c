#include "vpss_in_3798mv310.h"
#ifdef VPSS_HAL_WITH_CBB
#include "vpss_cbb_alg.h"
#endif
#include "vpss_info.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_BOOL VPSS_IN_CheckImage_V3(HI_DRV_VIDEO_FRAME_S *pstImage)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;
    HI_BOOL bSupported = HI_TRUE;
    HI_S32  s32Index;
    HI_DRV_PIX_FORMAT_E aeSupportFormatTbl[] =
    {
        HI_DRV_PIX_FMT_NV12,
        HI_DRV_PIX_FMT_NV21,
        HI_DRV_PIX_FMT_NV12_CMP,
        HI_DRV_PIX_FMT_NV21_CMP,
        HI_DRV_PIX_FMT_NV12_TILE,
        HI_DRV_PIX_FMT_NV21_TILE,
        HI_DRV_PIX_FMT_NV12_TILE_CMP,
        HI_DRV_PIX_FMT_NV21_TILE_CMP,
        HI_DRV_PIX_FMT_NV16,
        HI_DRV_PIX_FMT_NV61,
        HI_DRV_PIX_FMT_NV16_2X1,
        HI_DRV_PIX_FMT_NV61_2X1,
        HI_DRV_PIX_FMT_YUV400,
        HI_DRV_PIX_FMT_YUV_444,
        HI_DRV_PIX_FMT_YUV422_2X1,
        HI_DRV_PIX_FMT_YUV422_1X2,
        HI_DRV_PIX_FMT_YUV420p,
        HI_DRV_PIX_FMT_YUV411,
        HI_DRV_PIX_FMT_YUV410p,
        HI_DRV_PIX_FMT_YUYV,
        HI_DRV_PIX_FMT_YVYU,
        HI_DRV_PIX_FMT_UYVY,
        HI_DRV_PIX_FMT_ARGB8888,
        HI_DRV_PIX_FMT_ABGR8888,
        HI_DRV_PIX_FMT_ARGB1555,
        HI_DRV_PIX_FMT_ABGR1555,
        HI_DRV_PIX_FMT_RGB565
    };

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstPriv->u32Reserve[0]);

    if (pstPriv->u32LastFlag == DEF_HI_DRV_VPSS_LAST_ERROR_FLAG)
    {
        return HI_FALSE;
    }

    for (s32Index = 0; s32Index < VPSS_GET_ARRAY_CNT(aeSupportFormatTbl); s32Index++)
    {
        if (pstImage->ePixFormat == aeSupportFormatTbl[s32Index])
        {
            break;
        }
    }

    if (s32Index == VPSS_GET_ARRAY_CNT(aeSupportFormatTbl))
    {
        VPSS_FATAL("In image can't be processed Pixformat %d\n", pstImage->ePixFormat);
        bSupported = HI_FALSE;
    }

    if (pstImage->eFrmType >= HI_DRV_FT_BUTT)
    {
        VPSS_FATAL("In image can't be processed FrmType %d\n", pstImage->eFrmType);
        bSupported = HI_FALSE;
    }
    if (pstImage->eFrmType == HI_DRV_FT_FPK
        && pstImage->u32Width > VPSS_FHD_WIDTH)
    {
        VPSS_FATAL("4K FS not support!!\n");
        bSupported = HI_FALSE;
    }

    if ((pstImage->u32Height < VPSS_FRAME_MIN_HEIGHT) || (pstImage->u32Width < VPSS_FRAME_MIN_WIDTH)
        || (pstImage->u32Width > VPSS_FRAME_MAX_WIDTH) || (pstImage->u32Height > VPSS_FRAME_MAX_HEIGHT))
    {
        VPSS_FATAL("In image can't be processed H %d W %d\n",
                   pstImage->u32Height,
                   pstImage->u32Width);
        bSupported = HI_FALSE;
    }

    if ((HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL == pstImage->enSrcFrameType)
        || (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL == pstImage->enSrcFrameType))
    {
        VPSS_FATAL("Not support Dobly frame! type:%d\n", pstImage->enSrcFrameType);
        bSupported = HI_FALSE;
    }


    return bSupported;
}

HI_S32 VPSS_IN_CorrectFieldOrder(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pImage)
{
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;

    pstStreamInfo = &(pstEntity->stStreamInfo);

    /*
      * when get first image ,believe its topfirst info
      */
    if (pstStreamInfo->u32RealTopFirst == DEF_TOPFIRST_BUTT)
    {
        if (pImage->bProgressive == HI_TRUE)
        {
            pstStreamInfo->u32RealTopFirst = DEF_TOPFIRST_PROG;
        }
        else
        {
            pstStreamInfo->u32RealTopFirst =
                pImage->bTopFieldFirst;
        }
    }
    else
    {
        /*
           * detect progressive
           */
        if (pstStreamInfo->u32RealTopFirst == DEF_TOPFIRST_PROG)
        {
            if (pImage->bProgressive == HI_TRUE)
            {

            }
            else
            {
                pstStreamInfo->u32RealTopFirst =
                    pImage->bTopFieldFirst;
            }
        }
        /*
           * detect interlace
           */
        else
        {
            if (pImage->bProgressive == HI_TRUE)
            {
                pstStreamInfo->u32RealTopFirst =
                    DEF_TOPFIRST_PROG;
            }
            else
            {
                pImage->bTopFieldFirst =
                    pstStreamInfo->u32RealTopFirst;
            }
        }

    }

    return HI_SUCCESS;
}

HI_VOID VPSS_IN_CorrectProgByCfg(HI_DRV_VPSS_PRODETECT_E enProgInfo, HI_DRV_VIDEO_FRAME_S *pImage)
{
    HI_DRV_VIDEO_PRIVATE_S *pstFrmPriv;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;

    pstFrmPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pImage->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstFrmPriv->u32Reserve[0]);

    if (enProgInfo == HI_DRV_VPSS_PRODETECT_AUTO)
    {
        if (  (HI_UNF_VCODEC_TYPE_REAL8 == pstVdecPriv->entype)
              || (HI_UNF_VCODEC_TYPE_REAL9 == pstVdecPriv->entype)
              || (HI_UNF_VCODEC_TYPE_MPEG4 == pstVdecPriv->entype)
              || (HI_UNF_VCODEC_TYPE_VP9 == pstVdecPriv->entype))
        {
            return;
        }

        if (pImage->u32Height == 720)
        {
            pImage->bProgressive = HI_TRUE;
        }
        // un-trust bit-stream information
        else if (pImage->u32Height <= 576)
        {
            if ( (240 >= pImage->u32Height) && (320 >= pImage->u32Width) )
            {
                pImage->bProgressive = HI_TRUE;
            }
            else if (pImage->u32Height <= (pImage->u32Width * 9 / 14 ) )
            {
                // Rule: wide aspect ratio stream is normal progressive, we think that progressive info is correct.
            }
            else
            {
                pImage->bProgressive = HI_FALSE;
            }
        }
        else
        {

        }
    }

    else if (enProgInfo == HI_DRV_VPSS_PRODETECT_INTERLACE)
    {
        pImage->bProgressive = HI_FALSE;
    }
    else if (enProgInfo == HI_DRV_VPSS_PRODETECT_PROGRESSIVE)
    {
        if (pImage->bProgressive == HI_FALSE)
        {
            if (pImage->bTopFieldFirst == HI_TRUE)
            {
                pImage->bProgressive = HI_TRUE;
                pImage->enFieldMode = HI_DRV_FIELD_BOTTOM;
            }
            else
            {
                pImage->bProgressive = HI_TRUE;
                pImage->enFieldMode = HI_DRV_FIELD_TOP;
            }
        }
    }
    else
    {
        VPSS_FATAL("Invalid ProgInfo %d\n", enProgInfo);
    }

    return;
}

HI_S32 VPSS_IN_CorrectProgInfo(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pImage)
{
    HI_DRV_VIDEO_PRIVATE_S *pstFrmPriv;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;

    pstFrmPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pImage->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstFrmPriv->u32Reserve[0]);

#if defined(HI_NVR_SUPPORT)
    pImage->bProgressive = HI_TRUE;
    return  HI_SUCCESS;
#endif
    //all streams except SDR fix to prog
    if (HI_DRV_VIDEO_FRAME_TYPE_SDR != pImage->enSrcFrameType)
    {
        pImage->bProgressive = HI_TRUE;
        return  HI_SUCCESS;
    }
    if (pstFrmPriv->u32LastFlag == DEF_HI_DRV_VPSS_LAST_ERROR_FLAG)
    {
        return HI_SUCCESS;
    }

    if (pstEntity->bAlwaysFlushSrc == HI_TRUE)
    {
        pImage->bProgressive = HI_TRUE;
        return  HI_SUCCESS;
    }
#if 0 //LastFrame in 3D mode or > FHD shoule be corrected to Prog frame
    if (pstFrmPriv->u32LastFlag == DEF_HI_DRV_VPSS_LAST_FRAME_FLAG)
    {
        if ( pImage->u32Height > 1088 || pImage->u32Width > 1920)
        {
            pImage->bProgressive = HI_TRUE;
        }

        return HI_SUCCESS;
    }
#endif
    // belive VI, VI will give the right info
    if (((pImage->hTunnelSrc >> 16) & 0xff) == HI_ID_VI)
    {
        return HI_SUCCESS;
    }

    if (pstFrmPriv->stVideoOriginalInfo.enSource != HI_DRV_SOURCE_DTV)
    {
        return HI_SUCCESS;
    }

    if ( 0x2 == (pstVdecPriv->u8Marker &= 0x2))
    {
        pImage->bProgressive = HI_TRUE;
        return  HI_SUCCESS;
    }

    if ( pImage->u32Height > 1088 || pImage->u32Width > 1920)
    {
        pImage->bProgressive = HI_TRUE;
        return  HI_SUCCESS;
    }

    if ( (pImage->u32Height == 1080 || pImage->u32Height == 1088)
         && pImage->u32Width == 1920)
    {
        if (pImage->u32FrameRate > 50000)
        {
            pImage->bProgressive = HI_TRUE;
            return  HI_SUCCESS;
        }
    }

    if ((pImage->eFrmType == HI_DRV_FT_SBS) ||
        (pImage->eFrmType == HI_DRV_FT_TAB) ||
        (pImage->eFrmType == HI_DRV_FT_FPK))
    {
        pImage->bProgressive = HI_TRUE;
        return HI_SUCCESS;
    }


    if (pImage->ePixFormat == HI_DRV_PIX_FMT_YUYV
        || pImage->ePixFormat == HI_DRV_PIX_FMT_YVYU
        || pImage->ePixFormat == HI_DRV_PIX_FMT_UYVY)
    {
        pImage->bProgressive = HI_TRUE;
        return HI_SUCCESS;
    }

    if (pstEntity->bProgRevise == HI_FALSE)
    {
        pImage->bProgressive = HI_TRUE;
        return HI_SUCCESS;
    }

    /* HEVC do not use resolution to justic P/I type, only use FieldMode */
    if (HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype)
    {
        if (pImage->enFieldMode != HI_DRV_FIELD_ALL
            && pImage->enBufValidMode == HI_DRV_FIELD_ALL)
        {
            pImage->bProgressive = HI_FALSE;
            return HI_SUCCESS;
        }
    }

    VPSS_IN_CorrectProgByCfg(pstEntity->enProgInfo, pImage);

    return HI_SUCCESS;
}

HI_S32 VPSS_IN_ReviseImage(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pImage)
{
    HI_DRV_VIDEO_PRIVATE_S *pstFrmPriv;

    if (pstEntity->stDbginfo.bImageRevise)
    {
        pImage->u32Width = pstEntity->stDbginfo.u32InputWidth;
        pImage->u32Height = pstEntity->stDbginfo.u32InputHeight;
    }

    /*1.Revise image width ,height align to 2 or 4 */
    VPSS_PIXLE_DOWNALIGN_W(pImage->u32Width, HI_FALSE);

    if (pImage->u32Width <= 1920)
    {
        if (HI_TRUE == pImage->bProgressive)
        {
            VPSS_PIXLE_DOWNALIGN_H(pImage->u32Height, HI_FALSE);  //align 2
        }
        else
        {
            VPSS_PIXLE_DOWNALIGN_H(pImage->u32Height, HI_TRUE); //align 4
        }
    }
    else //need enable 4p/c
    {
        VPSS_PIXLE_DOWNALIGN_H(pImage->u32Height, HI_TRUE);  //align 4
    }

    if (HI_TRUE == pstEntity->stDbginfo.bDeiDisable)
    {
        pImage->enFieldMode = HI_DRV_FIELD_ALL;
        pImage->bProgressive = HI_TRUE;
    }

    if ( HI_TRUE == pstEntity->stDbginfo.frameEn )
    {
        pImage->u32FrameRate = pstEntity->stDbginfo.framerate * 1000;
    }

    pstFrmPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pImage->u32Priv[0]);
    if (pstFrmPriv->stVideoOriginalInfo.enSource == HI_DRV_SOURCE_DTV)
    {
        pstFrmPriv->stVideoOriginalInfo.bInterlace = (pImage->bProgressive == HI_TRUE) ? HI_FALSE : HI_TRUE;
        pstFrmPriv->stVideoOriginalInfo.u32FrmRate = pstEntity->stStreamInfo.u32InRate * 1000;

        if (pstEntity->enSrcCS == HI_DRV_CS_UNKNOWN)
        {
            if (pstFrmPriv->eColorSpace == HI_DRV_CS_UNKNOWN)
            {
                if (pImage->u32Width >= 1280 || pImage->u32Height >= 720)
                {
                    pstFrmPriv->eColorSpace  = HI_DRV_CS_BT709_YUV_LIMITED;
                }
                else
                {
                    pstFrmPriv->eColorSpace  = HI_DRV_CS_BT601_YUV_LIMITED;
                }
            }
        }
        else
        {
            pstFrmPriv->eColorSpace = pstEntity->enSrcCS;
        }
    }

    if (pstEntity->stStreamInfo.u32RealTopFirst != DEF_TOPFIRST_BUTT
        && pstEntity->stStreamInfo.u32StreamProg == pImage->bProgressive)
    {
        pImage->bTopFieldFirst = pstEntity->stStreamInfo.u32RealTopFirst;
    }

    /*
      * 2. 3d addr revise
      * SBS TAB read half image
      * MVC read two addr
      */
    if ((pImage->eFrmType == HI_DRV_FT_SBS) || (pImage->eFrmType == HI_DRV_FT_TAB))
    {
        VPSS_SAFE_MEMCPY(&(pImage->stBufAddr[1]), &(pImage->stBufAddr[0]),
                         sizeof(HI_DRV_VID_FRAME_ADDR_S));
    }

    /*
     *revise frame rate
     */
    if (pImage->u32FrameRate == 0)
    {
        pImage->u32FrameRate = 25000;
    }

    /*
     * if not top/bottom Interleaved,force Prog
     */
    if ((pImage->enFieldMode != HI_DRV_FIELD_ALL) && (pImage->enBufValidMode != HI_DRV_FIELD_ALL))
    {
        pImage->bProgressive = HI_TRUE;
    }

    //98mv200 donot support 10bit_i
    if ((HI_DRV_PIXEL_BITWIDTH_10BIT == pImage->enBitWidth)
        && (HI_TRUE != pImage->bProgressive))
    {
        pImage->enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_IN_ChangeInRate(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pstSrcImage)
{
    HI_U32 u32HzRate; /*0 -- 100*/
    HI_U32 u32InRate;

    if (pstSrcImage->bProgressive == HI_FALSE
        && pstSrcImage->enFieldMode == HI_DRV_FIELD_ALL)
    {
        u32InRate = pstSrcImage->u32FrameRate * 2;
    }
    else
    {
        u32InRate = pstSrcImage->u32FrameRate;
    }

    u32HzRate = u32InRate / 1000;

    if (u32HzRate < 10)
    {
        u32HzRate = 1;
    }
    else if (u32HzRate < 20)
    {
        u32HzRate = 10;
    }
    else if (u32HzRate < 30)
    {
        u32HzRate = 25;
    }
    else if (u32HzRate < 40)
    {
        u32HzRate = 30;
    }
    else if (u32HzRate < 60)
    {
        u32HzRate = 50;
    }
    else
    {
        u32HzRate = u32HzRate / 10 * 10;
    }

    pstEntity->stStreamInfo.u32InRate = u32HzRate;

    return HI_SUCCESS;
}

HI_S32 VPSS_IN_UpdateStreamInfo(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pstSrcImage)
{
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstSrcImage->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstPriv->u32Reserve[0]);
    pstStreamInfo = &(pstEntity->stStreamInfo);

    if (pstStreamInfo->u32StreamProg != pstSrcImage->bProgressive)
    {
        pstStreamInfo->u32IsNewImage = HI_TRUE;
    }
    else if (pstStreamInfo->u32StreamH != pstSrcImage->u32Height)
    {
        pstStreamInfo->u32IsNewImage = HI_TRUE;
    }
    else if (pstStreamInfo->u32StreamW != pstSrcImage->u32Width)
    {
        pstStreamInfo->u32IsNewImage = HI_TRUE;
    }
    else if (pstStreamInfo->eStreamFrmType != pstSrcImage->eFrmType)
    {
        pstStreamInfo->u32IsNewImage = HI_TRUE;
    }
    else if (pstStreamInfo->enFieldMode != pstSrcImage->enFieldMode)
    {
        pstStreamInfo->u32IsNewImage = HI_TRUE;
    }
    else if (pstStreamInfo->bStreamByPass == HI_TRUE)
    {
        pstStreamInfo->u32IsNewImage = HI_TRUE;
        pstStreamInfo->bStreamByPass = HI_FALSE;
    }
    else
    {
        pstStreamInfo->u32IsNewImage = HI_FALSE;
    }

    if (HI_TRUE == pstEntity->stTransFbInfo.bNeedTrans)
    {
        pstStreamInfo->u32IsNewImage = HI_TRUE;
    }

    if (HI_TRUE == pstStreamInfo->u32IsNewImage)
    {
        pstEntity->u32ScenceChgCnt++;
    }

    pstStreamInfo->u32StreamInRate = pstSrcImage->u32FrameRate;
    pstStreamInfo->u32StreamTopFirst = pstSrcImage->bTopFieldFirst;
    pstStreamInfo->u32StreamProg = pstSrcImage->bProgressive;
    pstStreamInfo->u32StreamH = pstSrcImage->u32Height;
    pstStreamInfo->u32StreamW = pstSrcImage->u32Width;
    pstStreamInfo->eStreamFrmType = pstSrcImage->eFrmType;
    pstStreamInfo->ePixFormat = pstSrcImage->ePixFormat;
    pstStreamInfo->enBitWidth = pstSrcImage->enBitWidth;
    pstStreamInfo->u32FrameIndex = pstSrcImage->u32FrameIndex;
    pstStreamInfo->u32Pts = pstSrcImage->u32Pts;
    pstStreamInfo->s64OmxPts = pstSrcImage->s64OmxPts;
    pstStreamInfo->eStreamType = pstSrcImage->enSrcFrameType;
    pstStreamInfo->enFieldMode = pstSrcImage->enFieldMode;

#ifdef VPSS_SUPPORT_PROC_V2

    pstStreamInfo->enBufValidMode = pstSrcImage->enBufValidMode;
    pstStreamInfo->bTopFieldFirst = pstSrcImage->bTopFieldFirst;
    pstStreamInfo->bSecure = pstSrcImage->bSecure;
    pstStreamInfo->enSrcFrameType = pstSrcImage->enSrcFrameType;
    pstStreamInfo->eFrmType = pstSrcImage->eFrmType;
    pstStreamInfo->u32StreamAspW = pstSrcImage->u32AspectWidth;
    pstStreamInfo->u32StreamAspH = pstSrcImage->u32AspectHeight;
#endif
    if (pstSrcImage->bProgressive != HI_TRUE
        && pstSrcImage->enFieldMode != HI_DRV_FIELD_ALL
        && pstSrcImage->enBufValidMode == HI_DRV_FIELD_ALL
        && HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype)
    {
        pstStreamInfo->bH265Interlace = HI_TRUE;
    }
    else
    {
        pstStreamInfo->bH265Interlace = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_BOOL VPSS_IN_CheckNeedNr(VPSS_IN_ENTITY_S *pstInEntity)
{
#if !defined(HI_NVR_SUPPORT)
    if ((pstInEntity->stStreamInfo.u32StreamW <= 1920))
    {
        return HI_TRUE;
    }
#endif
    return HI_FALSE;
}

HI_VOID VPSS_IN_CopyHalFrameInfo(HI_DRV_VIDEO_FRAME_S *pstFrame,
                                 VPSS_HAL_FRAME_S *pstHalFrm, HI_DRV_BUF_ADDR_E enBufLR)
{
    if (pstFrame == HI_NULL || pstHalFrm == HI_NULL || (enBufLR >= HI_DRV_BUF_ADDR_MAX))
    {
        VPSS_FATAL("func=%s,pstFrame(%p), pstHalFrm(%p) enBufLR:%d\n", __func__, pstFrame, pstHalFrm, enBufLR);
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

    return ;
}

HI_VOID VPSS_IN_ClearAllAlgBuffer(VPSS_IN_ENTITY_S *pstEntity)
{
    VPSS_WBC_S *pstWbcInfo;
    VPSS_STTWBC_S *psttWbc;
    VPSS_DIESTINFO_S *pstDieStInfo;
    VPSS_NRMADINFO_S *pstNrMadInfo;
    VPSS_MCDEI_INFO_S *pstMcdeiInfo;

    pstWbcInfo = &pstEntity->stWbcInfo[0];
    psttWbc = &pstEntity->stSttWbc[0];
    pstDieStInfo = &pstEntity->stDieStInfo[0];
    pstNrMadInfo = &pstEntity->stNrMadInfo[0];
    pstMcdeiInfo = &pstEntity->stMcdeiInfo[0];

    (HI_VOID)VPSS_WBC_DeInit(pstWbcInfo);
    (HI_VOID)VPSS_STTINFO_DieDeInit(pstDieStInfo);
    (HI_VOID)VPSS_STTINFO_NrDeInit(pstNrMadInfo);
    (HI_VOID)VPSS_STTINFO_SttWbcDeInit(psttWbc);
    (HI_VOID)VPSS_INST_McDeiDeInit(pstMcdeiInfo);

    (HI_VOID)VPSS_WBC_DeInit(&pstEntity->stWbcInfo[1]);
    (HI_VOID)VPSS_STTINFO_DieDeInit(&pstEntity->stDieStInfo[1]);
    (HI_VOID)VPSS_STTINFO_NrDeInit(&pstEntity->stNrMadInfo[1]);
    (HI_VOID)VPSS_STTINFO_SttWbcDeInit(&pstEntity->stSttWbc[1]);
    (HI_VOID)VPSS_INST_McDeiDeInit(&pstEntity->stMcdeiInfo[1]);

    return ;
}


HI_S32 VPSS_IN_GetSrcInitMode_V3(VPSS_IN_ENTITY_S *pstEntity)
{
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;

    VPSS_CHECK_NULL(pstEntity);

    VPSS_CHECK_VERSION(pstEntity->enVersion, VPSS_VERSION_V4_0);

    pstStreamInfo = &(pstEntity->stStreamInfo);

    if (HI_TRUE == pstStreamInfo->u32StreamProg)
    {
        return SRC_MODE_FRAME;
    }
#if 0
    else if ((720 == pstStreamInfo->u32StreamW) && (480 == pstStreamInfo->u32StreamH))
    {
        return SRC_MODE_NTSC;
    }
    else if ((720 == pstStreamInfo->u32StreamW) && (576 == pstStreamInfo->u32StreamH))
    {
        return SRC_MODE_PAL;
    }
#endif
    else
    {
        return SRC_MODE_NTSC;
    }

}

HI_S32 VPSS_IN_NewImgInit(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S *pstImage)
{
    VPSS_SRC_ATTR_S stSrcAttr;
    VPSS_WBC_ATTR_S stWbcAttr;
    VPSS_NR_ATTR_S stNrAttr;
    VPSS_SRC_S *pstSrcInfo;
    VPSS_WBC_S *pstWbcInfo;
    VPSS_STTWBC_S *psttWbc;
    VPSS_DIESTINFO_S *pstDieStInfo;
    VPSS_NRMADINFO_S *pstNrMadInfo;
    VPSS_MCDEI_INFO_S *pstMcdeiInfo;
    unsigned long flags;
    HI_BOOL     bDEISecure;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;
    HI_S32 s32InitListRet = HI_FAILURE;
    HI_S32 s32Ret;

    pstSrcInfo = &pstEntity->stSrc;
    pstWbcInfo = &pstEntity->stWbcInfo[0];
    psttWbc = &pstEntity->stSttWbc[0];
    pstDieStInfo = &pstEntity->stDieStInfo[0];
    pstNrMadInfo = &pstEntity->stNrMadInfo[0];
    pstMcdeiInfo = &pstEntity->stMcdeiInfo[0];
#if !defined(HI_NVR_SUPPORT)
    VPSS_IN_ClearAllAlgBuffer(pstEntity);
#endif

    if (HI_TRUE == pstEntity->stDbginfo.bPrintSrcInfo)
    {
        VPSS_DBG_PrintFrameInfo(pstImage, HI_TRUE, 0, 0xFFFFFFFF);
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);
    pstEntity->stOriInfo.enSource = pstPriv->stVideoOriginalInfo.enSource;
    pstEntity->stOriInfo.u32Width = pstPriv->stVideoOriginalInfo.u32Width;
    pstEntity->stOriInfo.u32Height = pstPriv->stVideoOriginalInfo.u32Height;
    pstEntity->stOriInfo.u32FrmRate = pstPriv->stVideoOriginalInfo.u32FrmRate;
    pstEntity->stOriInfo.bInterlace = (pstImage->bProgressive == HI_TRUE) ? HI_FALSE : HI_TRUE;
    pstEntity->stOriInfo.enColorSys = pstPriv->stVideoOriginalInfo.enColorSys;

    //if first image , take its fieldorder
    pstEntity->stStreamInfo.u32RealTopFirst = pstImage->bTopFieldFirst;

    stSrcAttr.hSrcModule = pstEntity->hSource;
    stSrcAttr.pfnRlsImage = (PFN_SRC_FUNC)pstEntity->pfnRlsCallback;
    stWbcAttr.enBitWidth = HI_DRV_PIXEL_BITWIDTH_10BIT; //MV200, wbc fix to 10bit.
    stWbcAttr.enRefMode = VPSS_WBC_REF_MODE_NULL;
    if (HI_DRV_PIX_FMT_NV12_TILE_CMP == pstImage->ePixFormat)
    {
        stWbcAttr.ePixFormat = HI_DRV_PIX_FMT_NV12_TILE;
    }
    else if (HI_DRV_PIX_FMT_NV21_TILE_CMP == pstImage->ePixFormat)
    {
        stWbcAttr.ePixFormat = HI_DRV_PIX_FMT_NV21_TILE;
    }
    else
    {
        stWbcAttr.ePixFormat = pstImage->ePixFormat;
    }
    stWbcAttr.u32Height = pstImage->u32Height;
    stWbcAttr.u32Width = pstImage->u32Width;
    stWbcAttr.u32FrameIndex = pstImage->u32FrameIndex;
    stWbcAttr.u32Pts = pstImage->u32Pts;
    stWbcAttr.s64OmxPts = pstImage->s64OmxPts;
    stWbcAttr.bSecure = pstImage->bSecure;
    stNrAttr.u32Height = pstImage->u32Height;
    stNrAttr.u32Width = pstImage->u32Width;
    stNrAttr.bSecure    = HI_FALSE;
    bDEISecure          = HI_FALSE;
    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstPriv->u32Reserve[0]);

    if (pstImage->bProgressive != HI_TRUE
        && pstImage->enFieldMode != HI_DRV_FIELD_ALL
        && pstImage->enBufValidMode == HI_DRV_FIELD_ALL
        && HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype)
    {
        stWbcAttr.u32Height *= 2;
        stNrAttr.u32Height  *= 2;
    }

    stSrcAttr.enMode = VPSS_IN_GetSrcInitMode_V3(pstEntity);

    //���е�FieldMode!=ALLʱ ҲҪ��3Field��֧, ȷ��mv200�Ľڵ�VPSS_HAL_NODE_2D_FIELD, ����NRʱ����ȡ��u32Snrmad_raddr

    if ((HI_TRUE == pstEntity->stStreamInfo.u32StreamProg)
        && (pstImage->enFieldMode == HI_DRV_FIELD_ALL))
    {
        stWbcAttr.enMode = VPSS_WBC_MODE_NORMAL;
        stNrAttr.enMode = NR_MODE_FRAME;
    }
    else
    {
        stWbcAttr.enMode = VPSS_WBC_MODE_4FIELD;
        stNrAttr.enMode = NR_MODE_3FIELD;
    }

    if (pstImage->u32Width > 1920)
    {
        VPSS_OSAL_DownSpin(&(pstEntity->stSrcSpin), &flags);
        s32InitListRet = VPSS_SRC_Init(pstSrcInfo, stSrcAttr);
        VPSS_OSAL_UpSpin(&(pstEntity->stSrcSpin), &flags);
#if !defined(HI_NVR_SUPPORT)
        s32InitListRet |= VPSS_STTINFO_SttWbcInit(psttWbc);
#endif
    }
    else
    {
        if (HI_DRV_FT_NOT_STEREO == pstImage->eFrmType)
        {
            VPSS_OSAL_DownSpin(&(pstEntity->stSrcSpin), &flags);
            s32InitListRet = VPSS_SRC_Init(pstSrcInfo, stSrcAttr);
            VPSS_OSAL_UpSpin(&(pstEntity->stSrcSpin), &flags);
#if !defined(HI_NVR_SUPPORT)
            s32InitListRet |= VPSS_WBC_Init(pstWbcInfo, &stWbcAttr);
            s32InitListRet |= VPSS_INST_McDeiInit(pstMcdeiInfo, pstImage);
            s32InitListRet |= VPSS_STTINFO_DieInit(pstDieStInfo,
                                                   stWbcAttr.u32Width,
                                                   stWbcAttr.u32Height,
                                                   bDEISecure);

            s32InitListRet |= VPSS_STTINFO_NrInit(pstNrMadInfo, &stNrAttr);
            s32InitListRet |= VPSS_STTINFO_SttWbcInit(psttWbc);
#endif
        }
        else
        {
            VPSS_OSAL_DownSpin(&(pstEntity->stSrcSpin), &flags);
            s32InitListRet = VPSS_SRC_Init(pstSrcInfo, stSrcAttr);
            VPSS_OSAL_UpSpin(&(pstEntity->stSrcSpin), &flags);
#if !defined(HI_NVR_SUPPORT)
            s32InitListRet |= VPSS_WBC_Init(pstWbcInfo, &stWbcAttr);
            pstWbcInfo = &pstEntity->stWbcInfo[1];
            s32InitListRet |= VPSS_WBC_Init(pstWbcInfo, &stWbcAttr);
            s32InitListRet |= VPSS_STTINFO_DieInit(pstDieStInfo,
                                                   stWbcAttr.u32Width,
                                                   stWbcAttr.u32Height,
                                                   pstImage->bSecure);
            pstDieStInfo = &pstEntity->stDieStInfo[1];
            s32InitListRet |= VPSS_STTINFO_DieInit(pstDieStInfo,
                                                   stWbcAttr.u32Width,
                                                   stWbcAttr.u32Height,
                                                   pstImage->bSecure);
            s32InitListRet |= VPSS_STTINFO_NrInit(pstNrMadInfo, &stNrAttr);
            pstNrMadInfo = &pstEntity->stNrMadInfo[1];
            s32InitListRet |= VPSS_STTINFO_NrInit(pstNrMadInfo , &stNrAttr);
            s32InitListRet |= VPSS_STTINFO_SttWbcInit(psttWbc);
            psttWbc = &pstEntity->stSttWbc[1];
            s32InitListRet |= VPSS_STTINFO_SttWbcInit(psttWbc );
            s32InitListRet |= VPSS_INST_McDeiInit(pstMcdeiInfo, pstImage);
            //3D right eye addr must be pstEntity->pstMcdeiInfo[1]
            s32InitListRet |= VPSS_INST_McDeiInit((&pstEntity->stMcdeiInfo[1]), pstImage);
#endif
        }
    }

    if (HI_SUCCESS != s32InitListRet)
    {
        return HI_FAILURE;
    }

    s32Ret = VPSS_SRC_PutImage(pstSrcInfo, (VPSS_SRC_DATA_S *)pstImage);
    pstEntity->stListState.u32PutSrcCount = pstSrcInfo->u32PutSrcCount;

    return s32Ret;
}


HI_S32 VPSS_IN_Refresh_V3(VPSS_IN_ENTITY_S *pstEntity)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bSupport = HI_TRUE;
    unsigned long flags;
    HI_DRV_VIDEO_FRAME_S *pstImage;
    HI_DRV_VIDEO_FRAME_S *pstData;

    VPSS_CHECK_NULL(pstEntity);
    VPSS_CHECK_VERSION(pstEntity->enVersion, VPSS_VERSION_V4_0);
    VPSS_CHECK_NULL(pstEntity->pfnAcqCallback);
    VPSS_CHECK_NULL(pstEntity->pfnRlsCallback);

    pstImage = &pstEntity->stSrcImage;

    /*
    if there are pictures not complete, do not receive picture again!!@sdk
    */
    if (pstEntity->stSrc.bInit)
    {
        if (pstEntity->stSrc.bEnding != HI_TRUE)
        {
            VPSS_OSAL_DownSpin(&(pstEntity->stSrcSpin), &flags);
            s32Ret = VPSS_SRC_GetProcessImage(&pstEntity->stSrc, &pstData);
            VPSS_OSAL_UpSpin(&(pstEntity->stSrcSpin), &flags);
            if (HI_SUCCESS == s32Ret)
            {
                return HI_SUCCESS;
            }
        }
        else
        {
            if (!VPSS_SRC_CheckIsEmpty(&pstEntity->stSrc))
            {
                return HI_SUCCESS;
            }
            else
            {
                pstEntity->stSrc.bEnding = HI_FALSE;
                pstEntity->stSrc.bEndingCompleteCnt = 0;
            }
        }
    }

    pstEntity->stListState.u32GetUsrTotal++;
    s32Ret = pstEntity->pfnAcqCallback(pstEntity->hSource, pstImage);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    pstEntity->stListState.u32GetUsrSuccess++;

    //(HI_VOID)HI_DRV_SYS_GetTimeStampMs(&(pstImage->stLowdelayStat.u32VPSS_IN));
    {
        HI_LD_Event_S evt;
        HI_U32 TmpTime = 0;
        HI_DRV_SYS_GetTimeStampMs(&TmpTime);
        evt.evt_id = EVENT_VPSS_FRM_IN;
        evt.frame = pstImage->u32FrameIndex;
        evt.handle = pstImage->hTunnelSrc;
        evt.time = TmpTime;
        HI_DRV_LD_Notify_Event(&evt);
    }

    if (HI_TRUE == pstEntity->stDbginfo.bPrintSrcInfo)
    {
        VPSS_DBG_PrintFrameInfo(pstImage, HI_TRUE,
                                pstEntity->stDbginfo.u32PrintStartIndex,
                                pstEntity->stDbginfo.u32PrintEndIndex);
    }


    bSupport = VPSS_IN_CheckImage_V3(pstImage);
    if (HI_TRUE != bSupport)
    {
        HI_DRV_VIDEO_PRIVATE_S *pstLastPriv;
        pstLastPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);

        if (pstLastPriv->u32LastFlag != DEF_HI_DRV_VPSS_LAST_ERROR_FLAG)
        {
            pstEntity->pfnRlsCallback(pstEntity->hSource, pstImage);
        }
        else if (pstLastPriv->u32LastFlag == DEF_HI_DRV_VPSS_LAST_ERROR_FLAG)
        {
            VPSS_SRC_S *pstSrcInfo = &pstEntity->stSrc;

            if (pstEntity->stWbcInfo[0].bInit == HI_TRUE)
            {
                VPSS_SRC_Flush(pstSrcInfo, pstEntity->stStreamInfo.u32StreamProg);
            }
        }
        else
        {

        }

        pstEntity->stListState.u32RelUsrTotal++;
        pstEntity->stListState.u32RelUsrSuccess++;
        return HI_FAILURE;
    }
    /*
        if (pstFrame->u32FrameIndex == 0)
        {
            HI_U8 chFile[DEF_FILE_NAMELENGTH];

            HI_OSAL_Snprintf(chFile, DEF_FILE_NAMELENGTH, "vpss_in_%dx%d_idx%d.yuv",
                             pstImage->u32Width, pstImage->u32Height, pstImage->u32FrameIndex);
            VPSS_OSAL_WRITEYUV(pstImage, chFile);
        }
    */

    (HI_VOID)VPSS_IN_CorrectProgInfo(pstEntity, pstImage);

    (HI_VOID)VPSS_IN_ReviseImage(pstEntity, pstImage);

    (HI_VOID)VPSS_IN_ChangeInRate(pstEntity, pstImage);

    if (VPSS_TRANS_FB_NeedTrans(&(pstEntity->stTransFbInfo), pstImage))
    {
        HI_DRV_VIDEO_PRIVATE_S *pstPriv;

        pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstImage->u32Priv;

        pstPriv->bByPassVpss = HI_TRUE;
        /*
                if (0)
                {
                    HI_U8 chFile[256] = "vpss_trans_frm_in.yuv";
                    VPSS_OSAL_WRITEYUV(pstImage, chFile);
                }
        */
        if (HI_TRUE == pstEntity->stDbginfo.bPrintSrcInfo)
        {
            VPSS_DBG_PrintFrameInfo(pstImage, HI_TRUE, 0, 0x1);
        }

        if (HI_SUCCESS == VPSS_TRANS_FB_PutImage(&(pstEntity->stTransFbInfo), pstImage))
        {
            VPSS_INFO("\n-------%d------Trans Image success,frameindex=%d",
                      pstEntity->hSource, pstImage->u32FrameIndex);
        }
        else
        {
            pstEntity->pfnRlsCallback(pstEntity->hSource, pstImage);
            VPSS_ERROR("\n-------%d------Trans Image failed,frameindex=%d",
                       pstEntity->hSource, pstImage->u32FrameIndex);
        }

        //return failuer,because vpss logic can't work
        return HI_FAILURE;
    }
    else
    {
        HI_DRV_VIDEO_PRIVATE_S *pstPriv;

        pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstImage->u32Priv;

        pstPriv->bByPassVpss = HI_FALSE;
    }

    (HI_VOID)VPSS_IN_UpdateStreamInfo(pstEntity, pstImage);
    pstEntity->stTransFbInfo.bNeedTrans = HI_FALSE;

    if (HI_TRUE == pstEntity->stStreamInfo.u32IsNewImage)
    {
        s32Ret = VPSS_IN_NewImgInit(pstEntity, pstImage);
    }
    else
    {
        VPSS_SRC_S *pstSrcInfo;

        pstSrcInfo = &pstEntity->stSrc;
        VPSS_CHECK_NULL(pstSrcInfo);
        s32Ret = VPSS_SRC_PutImage(pstSrcInfo, (VPSS_SRC_DATA_S *)pstImage);
        pstEntity->stListState.u32PutSrcCount = pstSrcInfo->u32PutSrcCount;
    }

    return s32Ret;
}

HI_S32 VPSS_IN_GetProcessImage_V3(VPSS_IN_ENTITY_S *pstEntity, HI_DRV_VIDEO_FRAME_S **ppstFrame)
{
    VPSS_SRC_S *pstSrc;
    VPSS_WBC_S *pstWbc;
    HI_S32 s32Ret = HI_SUCCESS;
    unsigned long flags;

    VPSS_CHECK_NULL(pstEntity);

    VPSS_CHECK_VERSION(pstEntity->enVersion, VPSS_VERSION_V4_0);

    pstSrc = &pstEntity->stSrc;

    if (pstSrc->bEnding != HI_TRUE)
    {
        VPSS_OSAL_DownSpin(&(pstEntity->stSrcSpin), &flags);
        s32Ret = VPSS_SRC_GetProcessImage(pstSrc, ppstFrame);
        VPSS_OSAL_UpSpin(&(pstEntity->stSrcSpin), &flags);
    }
    else
    {
        pstWbc = &pstEntity->stWbcInfo[0];

        s32Ret = VPSS_WBC_GetCurInfo(pstWbc, ppstFrame);
        if (s32Ret == HI_SUCCESS)
        {
            (*ppstFrame)->bProgressive = HI_TRUE;
        }

    }

    return s32Ret;
}

HI_BOOL VPSS_IN_CheckEyeValid(HI_DRV_BUF_ADDR_E enLR, VPSS_IN_INFO_TYPE_E enType)
{
    if ((HI_DRV_BUF_ADDR_LEFT != enLR) && (HI_DRV_BUF_ADDR_RIGHT != enLR))
    {
        if ((HI_DRV_BUF_ADDR_MAX == enLR)
            && ((VPSS_IN_INFO_STREAM == enType) || (VPSS_IN_INFO_CORRECT_FIELD == enType)))
        {
            return HI_TRUE;
        }

        VPSS_ERROR("Invalid L/R Type %d\n", enLR);
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_S32 VPSS_IN_GetInfo_V3(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_INFO_TYPE_E enType,
                          HI_DRV_BUF_ADDR_E enLR,
                          HI_VOID *pstInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_CHECK_NULL(pstEntity);

    if (HI_TRUE != VPSS_IN_CheckEyeValid(enLR, enType))
    {
        return HI_FAILURE;
    }

    VPSS_CHECK_VERSION(pstEntity->enVersion, VPSS_VERSION_V4_0);

    switch (enType)
    {
        case VPSS_IN_INFO_WBC:
        {
            HI_DRV_VIDEO_FRAME_S **ppstData;
            VPSS_WBC_S *pstWbc;

            ppstData = (HI_DRV_VIDEO_FRAME_S **)pstInfo;
            pstWbc = &pstEntity->stWbcInfo[enLR];
            s32Ret = VPSS_WBC_GetWbcInfo(pstWbc, ppstData);
            break;
        }
        case VPSS_IN_INFO_REF:
        {
            HI_DRV_VIDEO_FRAME_S **ppstRef;
            VPSS_WBC_S *pstWbc;

            ppstRef = (HI_DRV_VIDEO_FRAME_S **)pstInfo;
            pstWbc = &pstEntity->stWbcInfo[enLR];
            s32Ret = VPSS_WBC_GetRefInfo(pstWbc, ppstRef);
            break;
        }
        case VPSS_IN_INFO_SRC:
            VPSS_ERROR("Not support\n");
            break;
        case VPSS_IN_INFO_WBCREG_VA:
        {
            VPSS_STTWBC_S *pstStWbc;
            HI_U32 **ppu32VirAddr;

            pstStWbc = &pstEntity->stSttWbc[enLR];

            ppu32VirAddr = (HI_U32 **)pstInfo;

#ifdef HI_VPSS_SMMU_SUPPORT
            *ppu32VirAddr = (HI_U32 *)pstStWbc->stMMUBuf.pu8StartVirAddr;
#else
            *ppu32VirAddr = (HI_U32 *)pstStWbc->stMMZBuf.pu8StartVirAddr;
#endif
            s32Ret = HI_SUCCESS;
            break;
        }
        case VPSS_IN_INFO_WBCREG_PA:
        {
            VPSS_STTWBC_S *pstStWbc;
            HI_U32 *pu32VirAddr;

            pstStWbc = &pstEntity->stSttWbc[enLR];

            pu32VirAddr = (HI_U32 *)pstInfo;

#ifdef HI_VPSS_SMMU_SUPPORT
            *pu32VirAddr = pstStWbc->stMMUBuf.u32StartSmmuAddr;
#else
            *pu32VirAddr = pstStWbc->stMMZBuf.u32StartPhyAddr;
#endif
            s32Ret = HI_SUCCESS;
            break;
        }
        case VPSS_IN_INFO_STREAM:
        {
            VPSS_IN_STREAM_INFO_S *pstStreamInfo;
            pstStreamInfo = (VPSS_IN_STREAM_INFO_S *)pstInfo;
            VPSS_SAFE_MEMCPY(pstStreamInfo, &(pstEntity->stStreamInfo),
                             sizeof(VPSS_IN_STREAM_INFO_S));
            break;
        }
        case VPSS_IN_INFO_NR:
        {
            VPSS_NRMADCFG_S *pstNrCfg;
            VPSS_NRMADINFO_S *pstNrMadInfo;

            pstNrCfg = (VPSS_NRMADCFG_S *)pstInfo;
            pstNrMadInfo = &pstEntity->stNrMadInfo[enLR];
            if (pstEntity->stStreamInfo.u32StreamW <= VPSS_FHD_WIDTH)
            {
                s32Ret = VPSS_STTINFO_NrGetInfo(pstNrMadInfo, pstNrCfg);
            }
            break;
        }
        case VPSS_IN_INFO_DIE:
        {
            VPSS_DIESTINFO_S *pstDieStInfo;
            VPSS_DIESTCFG_S *pstDieStCfg;

            pstDieStCfg = (VPSS_DIESTCFG_S *)pstInfo;
            pstDieStInfo = &pstEntity->stDieStInfo[enLR];
            s32Ret = VPSS_STTINFO_DieGetInfo(pstDieStInfo, pstDieStCfg);
            break;
        }
        case VPSS_IN_INFO_BLEND_REF:
        {
            VPSS_BLEND_S *pstBlend;
            HI_DRV_VIDEO_FRAME_S **ppstRef;

            ppstRef = (HI_DRV_VIDEO_FRAME_S **)pstInfo;
            pstBlend = &pstEntity->stMcdeiInfo[enLR].stBlendWbcInfo;
            s32Ret = VPSS_BLEND_GetRefInfo(pstBlend, ppstRef);
            break;
        }
        case VPSS_IN_INFO_BLEND_WBC:
        {
            VPSS_BLEND_S *pstBlend;
            HI_DRV_VIDEO_FRAME_S * * ppstWbc;

            ppstWbc = (HI_DRV_VIDEO_FRAME_S **)pstInfo;
            pstBlend = &pstEntity->stMcdeiInfo[enLR].stBlendWbcInfo;
            s32Ret = VPSS_BLEND_GetWbcInfo(pstBlend, ppstWbc);
            break;
        }
        case VPSS_IN_INFO_RGME:
        {
            VPSS_ST_RGME_S *pstStRgme;
            VPSS_ST_RGME_CFG_S *pstStRgmeCfg;

            pstStRgmeCfg = (VPSS_ST_RGME_CFG_S *)pstInfo;
            pstStRgme = &pstEntity->stMcdeiInfo[enLR].stRgmeInfo;
            s32Ret = VPSS_ST_RGME_GetCfg(pstStRgme, pstStRgmeCfg);
            break;
        }
        case VPSS_IN_INFO_BLKMV:
        {
            VPSS_ST_BLKMV_S *pstStBlkmv;
            VPSS_ST_BLKMV_CFG_S *pstStBlkmvCfg;

            pstStBlkmvCfg = (VPSS_ST_BLKMV_CFG_S *)pstInfo;
            pstStBlkmv = &pstEntity->stMcdeiInfo[enLR].stBlkmvInfo;
            s32Ret = VPSS_ST_BLKMV_GetCfg(pstStBlkmv, pstStBlkmvCfg);
            break;
        }
        case VPSS_IN_INFO_PRJH:
        {
            VPSS_ST_PRJH_S *pstStPrjh;
            VPSS_ST_PRJH_CFG_S *pstStPrjhCfg;

            pstStPrjhCfg = (VPSS_ST_PRJH_CFG_S *)pstInfo;
            pstStPrjh = &pstEntity->stMcdeiInfo[enLR].stPrjhInfo;
            s32Ret = VPSS_ST_PRJH_GetCfg(pstStPrjh, pstStPrjhCfg);
            break;
        }
        case VPSS_IN_INFO_PRJV:
        {
            VPSS_ST_PRJV_S *pstStPrjv;
            VPSS_ST_PRJV_CFG_S *pstStPrjvCfg;

            pstStPrjvCfg = (VPSS_ST_PRJV_CFG_S *)pstInfo;
            pstStPrjv = &pstEntity->stMcdeiInfo[enLR].stPrjvInfo;
            s32Ret = VPSS_ST_PRJV_GetCfg(pstStPrjv, pstStPrjvCfg);
            break;
        }
        case VPSS_IN_INFO_CORRECT_FIELD:
        {
            HI_BOOL bTopFirst;
            bTopFirst = *(HI_BOOL *)pstInfo;
            if (bTopFirst == pstEntity->stStreamInfo.u32RealTopFirst)
            {
                s32Ret = HI_SUCCESS;
                return s32Ret;
            }

            if (pstEntity->stStreamInfo.u32RealTopFirst == DEF_TOPFIRST_BUTT)
            {
                pstEntity->stStreamInfo.u32RealTopFirst = bTopFirst;
                s32Ret = HI_SUCCESS;
                return s32Ret;
            }

            if (pstEntity->stSrc.bEnding != HI_TRUE)
            {
                s32Ret = VPSS_SRC_CorrectListOrder(&pstEntity->stSrc, bTopFirst);
            }

            pstEntity->stStreamInfo.u32RealTopFirst = bTopFirst;
            break;
        }
        default:
            VPSS_ERROR("Invalid Info Type %d\n", enType);
            s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 VPSS_IN_SetInputConfigProc( VPSS_IN_ENTITY_S *pstEntity,
                                   HI_DRV_VIDEO_FRAME_S *pstCur,
                                   HI_DRV_BUF_ADDR_E enLR,
                                   VPSS_HAL_INFO_S *pstHalInfo,
                                   HI_DRV_VIDEO_FRAME_S *pstWbc,
                                   VPSS_MCDEI_INFO_S *pstMcdeiInfo,
                                   HI_DRV_VIDEO_FRAME_S *pstSrcImage,
                                   HI_DRV_VIDEO_FRAME_S *pstRef[]
                                 )

{
    HI_S32 i;
    HI_U32 u32RefCount;
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret;

    s32Ret = VPSS_IN_GetIntf(pstEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    s32Ret = stInIntf.pfnGetInfo( pstEntity,
                                  VPSS_IN_INFO_WBC,
                                  enLR,
                                  (HI_VOID *)&pstWbc);

    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("GetInfo VPSS_IN_INFO_WBC fail! Errcode:0x%x\n", s32Ret);
        return s32Ret;
    }

    /*keep ref frame pts equal cur pts*/
    pstWbc->u32FrameIndex = pstCur->u32FrameIndex;
    pstWbc->u32Pts = pstCur->u32Pts;
    pstWbc->s64OmxPts = pstCur->s64OmxPts;
    VPSS_SAFE_MEMCPY(pstWbc->u32Priv, pstCur->u32Priv, sizeof(HI_U32)*DEF_HI_DRV_FRAME_INFO_SIZE);
    VPSS_IN_CopyHalFrameInfo(pstWbc, &pstHalInfo->stInWbcInfo, enLR);

    s32Ret = stInIntf.pfnGetInfo( pstEntity,
                                  VPSS_IN_INFO_REF,
                                  enLR,
                                  (HI_VOID *)pstRef);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("GetInfo VPSS_IN_INFO_WBC fail! Errcode:0x%x\n", s32Ret);
        return s32Ret;
    }

    u32RefCount = pstEntity->stWbcInfo[enLR].stWbcAttr.enMode - 2;

    if (u32RefCount < (VPSS_WBC_MODE_BUTT - 2))
    {
        if (pstRef[u32RefCount] != HI_NULL)
        {
            //VPSS_ERROR("pstRef[i]  %d %#x\n",u32RefCount,pstRef[u32RefCount]->stBufAddr[0].u32PhyAddr_Y);
            VPSS_IN_CopyHalFrameInfo(pstRef[u32RefCount], &pstHalInfo->stInRefInfo[u32RefCount], enLR);

            for (i = (u32RefCount - 1); i >= 0; i--)
            {
                if (pstRef[i] != HI_NULL)
                {

                    //VPSS_ERROR("pstRef[i]  %d %#x\n",i,pstRef[i]->stBufAddr[0].u32PhyAddr_Y);
                    VPSS_IN_CopyHalFrameInfo(pstRef[i], &pstHalInfo->stInRefInfo[i], enLR);
                }
                else
                {
                    pstRef[i] = pstRef[i + 1];

                    //VPSS_ERROR("pstRef[i]  %d %#x\n",i,pstRef[i]->stBufAddr[0].u32PhyAddr_Y);
                    VPSS_IN_CopyHalFrameInfo(pstRef[i], &pstHalInfo->stInRefInfo[i], enLR);
                }
            }
        }
        else
        {
            for (i = 0; i <= u32RefCount; i++)
            {
                VPSS_IN_CopyHalFrameInfo(pstCur, &pstHalInfo->stInRefInfo[i], enLR);
            }
        }
    }

    return s32Ret;
}

HI_S32 VPSS_IN_SetInputConfig( VPSS_IN_ENTITY_S *pstEntity,
                               VPSS_SET_INFO_TYPE_E enType,
                               HI_DRV_BUF_ADDR_E enLR,
                               HI_VOID *pstInfo)
{
    VPSS_HAL_INFO_S *pstHalInfo;
    HI_DRV_VIDEO_FRAME_S *pstCur;
    HI_DRV_VIDEO_FRAME_S *pstRef[4] = {HI_NULL, HI_NULL, HI_NULL, HI_NULL};
    HI_DRV_VIDEO_FRAME_S *pstWbc = HI_NULL;
    VPSS_MCDEI_INFO_S *pstMcdeiInfo = HI_NULL;
    HI_DRV_VIDEO_FRAME_S *pstSrcImage = HI_NULL;
    HI_S32 s32Ret;

    VPSS_IN_INTF_S stInIntf;
    s32Ret = VPSS_IN_GetIntf(pstEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    pstHalInfo = (VPSS_HAL_INFO_S *)pstInfo;
    VPSS_CHECK_NULL(stInIntf.pfnGetInfo);
    stInIntf.pfnGetInfo(pstEntity, VPSS_IN_INFO_WBCREG_PA, enLR, &pstHalInfo->stSttAddr.u32stt_w_phy_addr);
    stInIntf.pfnGetInfo(pstEntity, VPSS_IN_INFO_WBCREG_VA, enLR, &pstHalInfo->stSttAddr.pu8stt_w_vir_addr);

    s32Ret = stInIntf.pfnGetProcessImage(pstEntity, &pstCur);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
        return HI_FAILURE;
    }

    switch (pstHalInfo->enNodeType)
    {
        case VPSS_HAL_NODE_2D_FRAME:
        case VPSS_HAL_NODE_2D_FIELD:
        case VPSS_HAL_NODE_3D_FRAME_R:
        case VPSS_HAL_NODE_2D_FIELD_VIRTUAL:
        case VPSS_HAL_NODE_2D_DEI_LAST_2FIELD:
        case VPSS_HAL_NODE_2D_DEI_LAST_2FIELD_VIRTUAL:
            if (VPSS_IN_CheckNeedNr(pstEntity))
            {
                pstHalInfo->stNrInfo.bNrEn = HI_TRUE;
                stInIntf.pfnGetInfo( pstEntity,
                                     VPSS_IN_INFO_NR,
                                     enLR,
                                     (HI_VOID *) & (pstHalInfo->stNrInfo.stNrMadCfg));
            }
#ifdef VPSS_SUPPORT_ALG_MCNR
            pstSrcImage = &pstEntity->stSrcImage;
            pstHalInfo = (VPSS_HAL_INFO_S *)pstInfo;
            pstMcdeiInfo = &pstEntity->stMcdeiInfo[enLR];
            if (HI_TRUE == pstMcdeiInfo->bMcNrEnable)
            {
                VPSS_INST_SetHalMcNrInfo(pstMcdeiInfo, pstHalInfo, enLR, pstSrcImage);
            }
#endif
            break;
        case VPSS_HAL_NODE_2D_DEI:
        case VPSS_HAL_NODE_2D_DEI_VIRTUAL:  //2D����, hd����˿�,ת��ʹ��
        case VPSS_HAL_NODE_2D_SD_FIRST:     //sd, ����
        case VPSS_HAL_NODE_2D_SD_SECOND:    //sd, ����
        case VPSS_HAL_NODE_2D_SD_VIRTUAL:   //sd, ��������˿�,ת��ʹ��
        case VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE:
        case VPSS_HAL_NODE_2D_H265_STEP2_DEI:
            pstHalInfo->stDieInfo.bBottom_first = pstEntity->stStreamInfo.u32RealTopFirst;
            stInIntf.pfnGetInfo(pstEntity,
                                VPSS_IN_INFO_DIE,
                                enLR,
                                (HI_VOID *) & (pstHalInfo->stDieInfo.stDieStCfg));

            if (VPSS_IN_CheckNeedNr(pstEntity))
            {
                pstHalInfo->stNrInfo.bNrEn = HI_TRUE;
                stInIntf.pfnGetInfo(pstEntity,
                                    VPSS_IN_INFO_NR,
                                    enLR,
                                    (HI_VOID *) & (pstHalInfo->stNrInfo.stNrMadCfg));
            }
            pstSrcImage = &pstEntity->stSrcImage;
            pstHalInfo = (VPSS_HAL_INFO_S *)pstInfo;
            pstMcdeiInfo = &pstEntity->stMcdeiInfo[enLR];
            VPSS_INST_SetHalMcdeiInfo(pstMcdeiInfo, pstHalInfo, enLR, pstSrcImage);
            break;
        case VPSS_HAL_NODE_2D_UHD:
        case VPSS_HAL_NODE_2D_UHD_VIRTUAL:
        case VPSS_HAL_NODE_2D_CTS10:        //ֻ��2Dʱ��
        case VPSS_HAL_NODE_2D_CTS10_VIRTUAL: //CTS10,����˿�
        case VPSS_HAL_NODE_3D_FRAME_L:      //3D����
        case VPSS_HAL_NODE_ROTATION_Y:      //Y,C��ת
        case VPSS_HAL_NODE_ROTATION_C:      //Y,C��ת
        case VPSS_HAL_NODE_HDR_DETILE_NOALG:

            /* Do Nothing */
            break;
        default:
            VPSS_FATAL("Node Type(%x) is Not Surport,\n", pstHalInfo->enNodeType);
            return HI_FAILURE;
    }

    if (VPSS_IN_CheckNeedNr(pstEntity))
    {
        s32Ret = VPSS_IN_SetInputConfigProc(pstEntity,
                                            pstCur,
                                            enLR,
                                            pstHalInfo,
                                            pstWbc,
                                            pstMcdeiInfo,
                                            pstSrcImage,
                                            pstRef
                                           );
    }

    return s32Ret;
}


HI_S32 VPSS_IN_SetInfo_V3 ( VPSS_IN_ENTITY_S *pstEntity,
                            VPSS_SET_INFO_TYPE_E enType,
                            HI_DRV_BUF_ADDR_E enLR,
                            HI_VOID *pstInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_CHECK_NULL(pstEntity);

    VPSS_CHECK_VERSION(pstEntity->enVersion, VPSS_VERSION_V4_0);

    if (pstEntity->stWbcInfo[enLR].stWbcAttr.enMode >= VPSS_WBC_MODE_BUTT)
    {
        VPSS_FATAL("Invalid stWbcAttr.enMode:%d\n", pstEntity->stWbcInfo[enLR].stWbcAttr.enMode);
        return HI_FAILURE;
    }


    switch (enType)
    {
        case VPSS_SET_INFO_INPUT_CFG:
            s32Ret = VPSS_IN_SetInputConfig(pstEntity, enType, enLR, pstInfo);
            break;
        case VPSS_SET_INFO_PTS:
        {
            HI_DRV_VIDEO_FRAME_S *pstFrm ;
            HI_DRV_VIDEO_FRAME_S *pstRef[3] = {HI_NULL, HI_NULL, HI_NULL};
            VPSS_IN_INTF_S stInIntf;
            s32Ret = VPSS_IN_GetIntf(pstEntity, &stInIntf);
            if (HI_SUCCESS != s32Ret)
            {
                VPSS_ERROR("Get Interface Failed\n");
                return HI_FAILURE;
            }

            pstFrm = (HI_DRV_VIDEO_FRAME_S *)pstInfo;
            /* keep pts equal src frame*/
            if (HI_FALSE == pstEntity->stStreamInfo.u32StreamProg)
            {
                s32Ret = stInIntf.pfnGetInfo( pstEntity,
                                              VPSS_IN_INFO_REF,
                                              enLR,
                                              (HI_VOID *)pstRef);

                if (HI_FAILURE == s32Ret)
                {
                    VPSS_FATAL("VPSS_WBC_GetWbcInfo failed!\n");
                    return HI_FAILURE;
                }

                if (HI_NULL == pstRef[1])
                {
                    pstFrm->u32FrameIndex = pstEntity->stStreamInfo.u32FrameIndex;
                    pstFrm->u32Pts = pstEntity->stStreamInfo.u32Pts;
                    pstFrm->s64OmxPts = pstEntity->stStreamInfo.s64OmxPts;
                }
                else
                {
                    pstFrm->u32FrameIndex = pstRef[1]->u32FrameIndex;
                    pstFrm->u32Pts = pstRef[1]->u32Pts;
                    pstFrm->s64OmxPts = pstRef[1]->s64OmxPts;
                    VPSS_SAFE_MEMCPY(pstFrm->u32Priv, pstRef[1]->u32Priv, sizeof(HI_U32)*DEF_HI_DRV_FRAME_INFO_SIZE);
                }
            }
        }
        break;
        /*
                case VPSS_SET_INFO_MCDEI:
                {
                    VPSS_MCDEI_INFO_S *pstMcdeiInfo;
                    VPSS_HAL_INFO_S    *pstHalInfo;
                    HI_DRV_VIDEO_FRAME_S *pstSrcImage;

                    pstSrcImage = &pstEntity->stSrcImage;
                    pstHalInfo = (VPSS_HAL_INFO_S *)pstInfo;
                    pstMcdeiInfo = &pstEntity->stMcdeiInfo[enLR];
                    s32Ret = VPSS_INST_SetHalMcdeiInfo(pstMcdeiInfo, pstHalInfo, enLR, pstSrcImage);
                }
                break;
        */
        default:
            VPSS_ERROR("Invalid set Info Type %d\n", enType);
            s32Ret = HI_FAILURE;
    }

    return s32Ret;
}



HI_S32 VPSS_IN_CompleteImage_V3(VPSS_IN_ENTITY_S *pstEntity)
{
    VPSS_SRC_S *pstSrcInfo;
    VPSS_WBC_S *pstWbcInfo;
    VPSS_STTWBC_S *psttWbc;
    VPSS_DIESTINFO_S *pstDieStInfo;
    VPSS_NRMADINFO_S *pstNrMadInfo;
    VPSS_MCDEI_INFO_S *pstMcdeiInfo;

    VPSS_CHECK_NULL(pstEntity);

    pstSrcInfo = &pstEntity->stSrc;
    pstWbcInfo = &pstEntity->stWbcInfo[0];

    psttWbc = &pstEntity->stSttWbc[0];
    pstDieStInfo = &pstEntity->stDieStInfo[0];
    pstNrMadInfo = &pstEntity->stNrMadInfo[0];
    pstMcdeiInfo = &pstEntity->stMcdeiInfo[0];

    VPSS_SRC_CompleteImage(pstSrcInfo, HI_NULL);
    pstEntity->stListState.u32CompleteSrcCount = pstSrcInfo->u32CompleteSrcCount;
    pstEntity->stListState.u32ReleaseSrcCount = pstSrcInfo->u32ReleaseSrcCount;

#if !defined(HI_NVR_SUPPORT)
    if (pstEntity->stStreamInfo.u32StreamW <= 1920)
    {
        VPSS_WBC_Complete(pstWbcInfo);
        VPSS_STTINFO_DieComplete(pstDieStInfo);
        VPSS_STTINFO_NrComplete(pstNrMadInfo);
        VPSS_STTINFO_SttWbcComplete(psttWbc);
        VPSS_INST_McDeiComplete(pstMcdeiInfo);

        if (pstEntity->stStreamInfo.eStreamFrmType != HI_DRV_FT_NOT_STEREO)
        {
            VPSS_WBC_Complete(&pstEntity->stWbcInfo[1]);
            VPSS_STTINFO_DieComplete(&pstEntity->stDieStInfo[1]);
            VPSS_STTINFO_NrComplete(&pstEntity->stNrMadInfo[1]);
            VPSS_STTINFO_SttWbcComplete(&pstEntity->stSttWbc[1]);
            VPSS_INST_McDeiComplete(&pstEntity->stMcdeiInfo[1]);
        }
    }
    else
    {
        VPSS_STTINFO_SttWbcComplete(psttWbc);
    }
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_IN_Reset_V3(VPSS_IN_ENTITY_S *pstEntity)
{
    VPSS_SRC_S *pstSrcInfo;
    VPSS_WBC_S *pstWbcInfo;

    VPSS_STTWBC_S *psttWbc;
    VPSS_DIESTINFO_S *pstDieStInfo;
    VPSS_NRMADINFO_S *pstNrMadInfo;
    VPSS_MCDEI_INFO_S *pstMcdeiInfo;

    VPSS_CHECK_NULL(pstEntity);

    pstSrcInfo = &pstEntity->stSrc;
    pstWbcInfo = &pstEntity->stWbcInfo[0];
    psttWbc = &pstEntity->stSttWbc[0];
    pstDieStInfo = &pstEntity->stDieStInfo[0];
    pstNrMadInfo = &pstEntity->stNrMadInfo[0];
    pstMcdeiInfo = &pstEntity->stMcdeiInfo[0];

    /*reset image list*/
    //:TODO:?���̡¨�?��??��?��������?VPSS?y?����|������y?Y��?��?o?����?�訪?2?,?����???2???
    VPSS_SRC_Reset(pstSrcInfo);

    if (pstEntity->enMode == VPSS_IN_MODE_USRACTIVE)
    {
        //:TODO:��-?�꨺???��?2?��?��??���̡¨�?RESET
    }

#if !defined(HI_NVR_SUPPORT)
    if (pstEntity->stStreamInfo.u32StreamW <= 1920)
    {
        VPSS_WBC_Reset(pstWbcInfo);
        VPSS_STTINFO_DieReset(pstDieStInfo);
        VPSS_STTINFO_NrReset(pstNrMadInfo);
        VPSS_STTINFO_SttWbcReset(psttWbc);
        VPSS_INST_McDeiReset(pstMcdeiInfo);

        if (pstEntity->stStreamInfo.eStreamFrmType != HI_DRV_FT_NOT_STEREO)
        {
            VPSS_WBC_Reset(&pstEntity->stWbcInfo[1]);
            VPSS_STTINFO_DieReset(&pstEntity->stDieStInfo[1]);
            VPSS_STTINFO_NrReset(&pstEntity->stNrMadInfo[1]);
            VPSS_STTINFO_SttWbcReset(&pstEntity->stSttWbc[1]);
            VPSS_INST_McDeiReset(&pstEntity->stMcdeiInfo[1]);
        }
    }
    else
    {
        VPSS_STTINFO_SttWbcReset(&pstEntity->stSttWbc[0]);
    }

#if 0
    if (pstEntity->enMode == VPSS_IN_MODE_USRACTIVE)
    {
        VPSS_SRCIN_DeInit(&pstEntity->stSrcIn);
    }
#endif

    if (pstEntity->stStreamInfo.u32StreamW <= 1920)
    {
        VPSS_WBC_DeInit(pstWbcInfo);
        VPSS_STTINFO_DieDeInit(pstDieStInfo);
        VPSS_STTINFO_NrDeInit(pstNrMadInfo);
        VPSS_STTINFO_SttWbcDeInit(psttWbc);
        VPSS_INST_McDeiDeInit(pstMcdeiInfo);

        if (pstEntity->stStreamInfo.eStreamFrmType != HI_DRV_FT_NOT_STEREO)
        {
            VPSS_WBC_DeInit(&pstEntity->stWbcInfo[1]);
            VPSS_STTINFO_DieDeInit(&pstEntity->stDieStInfo[1]);
            VPSS_STTINFO_NrDeInit(&pstEntity->stNrMadInfo[1]);
            VPSS_STTINFO_SttWbcDeInit(&pstEntity->stSttWbc[1]);
            VPSS_INST_McDeiDeInit(&pstEntity->stMcdeiInfo[1]);
        }
    }
    else
    {
        VPSS_STTINFO_SttWbcDeInit(&pstEntity->stSttWbc[0]);
    }
#endif
    memset(&(pstEntity->stStreamInfo), 0, sizeof(VPSS_IN_STREAM_INFO_S));

    pstEntity->stStreamInfo.u32RealTopFirst = DEF_TOPFIRST_BUTT;

    memset(&(pstEntity->stListState), 0, sizeof(VPSS_IN_IMAGELIST_STATE_S));


    return HI_SUCCESS;
}

HI_S32 VPSS_IN_GetIntf(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_INTF_S *pstIntf)
{
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_CHECK_NULL(pstEntity);

    if (pstEntity->enVersion == VPSS_VERSION_V4_0)
    {
        pstIntf->pfnRefresh         = VPSS_IN_Refresh_V3;
        pstIntf->pfnCompleteImage   = VPSS_IN_CompleteImage_V3;
        pstIntf->pfnGetProcessImage = VPSS_IN_GetProcessImage_V3;
        pstIntf->pfnReset           = VPSS_IN_Reset_V3;
        pstIntf->pfnGetInfo         = VPSS_IN_GetInfo_V3;
        pstIntf->pfnSetInfo         = VPSS_IN_SetInfo_V3;
    }
    else
    {
        VPSS_ERROR("Version %d can't support\n", pstEntity->enVersion);
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 VPSS_IN_Init(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_ENV_S stEnv)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VPSS_CHECK_NULL(pstEntity);

    pstEntity->stStreamInfo.u32RealTopFirst = DEF_TOPFIRST_BUTT;

    if (stEnv.enVersion == VPSS_VERSION_V4_0)
    {
        pstEntity->enVersion = VPSS_VERSION_V4_0;

        VPSS_OSAL_InitSpin(&(pstEntity->stSrcSpin));
    }
    else
    {
        VPSS_ERROR("Version %d can't support\n", stEnv.enVersion);
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 VPSS_IN_DeInit(VPSS_IN_ENTITY_S *pstEntity)
{
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_CHECK_NULL(pstEntity);

    if (pstEntity->enVersion == VPSS_VERSION_V4_0)
    {
        VPSS_SRC_S *pstSrcInfo;
        VPSS_WBC_S *pstWbcInfo;
        VPSS_STTWBC_S *psttWbc;
        VPSS_DIESTINFO_S *pstDieStInfo;
        VPSS_NRMADINFO_S *pstNrMadInfo;
        VPSS_MCDEI_INFO_S *pstMcdeiInfo;
        unsigned long flags;

        VPSS_CHECK_NULL(pstEntity);

        pstSrcInfo = &pstEntity->stSrc;
        pstWbcInfo = &pstEntity->stWbcInfo[0];
        psttWbc = &pstEntity->stSttWbc[0];
        pstDieStInfo = &pstEntity->stDieStInfo[0];
        pstNrMadInfo = &pstEntity->stNrMadInfo[0];
        pstMcdeiInfo = &pstEntity->stMcdeiInfo[0];

        VPSS_OSAL_DownSpin(&(pstEntity->stSrcSpin), &flags);
        VPSS_SRC_DeInit(pstSrcInfo);
        VPSS_OSAL_UpSpin(&(pstEntity->stSrcSpin), &flags);

        // TODO: ��??��?�꨺?
        if (pstEntity->enMode == VPSS_IN_MODE_USRACTIVE)
        {
            //VPSS_SRCIN_DeInit(&pstInstance->stSrcIn);
        }
#if !defined(HI_NVR_SUPPORT)

        VPSS_IN_ClearAllAlgBuffer(pstEntity);

        if (pstEntity->stStreamInfo.u32StreamW <= 1920)
        {
            VPSS_WBC_DeInit(pstWbcInfo);
            VPSS_STTINFO_DieDeInit(pstDieStInfo);
            VPSS_STTINFO_NrDeInit(pstNrMadInfo);
            VPSS_STTINFO_SttWbcDeInit(psttWbc);
            VPSS_INST_McDeiDeInit(pstMcdeiInfo);

            if (pstEntity->stStreamInfo.eStreamFrmType != HI_DRV_FT_NOT_STEREO)
            {
                VPSS_WBC_DeInit(&pstEntity->stWbcInfo[1]);
                VPSS_STTINFO_DieDeInit(&pstEntity->stDieStInfo[1]);
                VPSS_STTINFO_NrDeInit(&pstEntity->stNrMadInfo[1]);
                VPSS_STTINFO_SttWbcDeInit(&pstEntity->stSttWbc[1]);
                VPSS_INST_McDeiDeInit(&pstEntity->stMcdeiInfo[1]);
            }
        }
        else
        {
            VPSS_STTINFO_SttWbcDeInit(psttWbc);
        }
#endif
    }
    else
    {
        VPSS_ERROR("VpssVersion %d can't support\n", pstEntity->enVersion);
        s32Ret = HI_FAILURE;
        goto DEINIT_OUT;

    }
DEINIT_OUT:
    return s32Ret;
}

HI_S32 VPSS_IN_SetAttr(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_ATTR_S stAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_CHECK_NULL(pstEntity);

    pstEntity->enProgInfo = stAttr.enProgInfo;
    pstEntity->bProgRevise = stAttr.bProgRevise;
    pstEntity->bAlwaysFlushSrc = stAttr.bAlwaysFlushSrc;
    pstEntity->enSrcCS = stAttr.enSrcCS;
    return s32Ret;

}

HI_S32 VPSS_IN_GetAttr(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_ATTR_S *pstAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_CHECK_NULL(pstEntity);

    pstAttr->enProgInfo = pstEntity->enProgInfo;
    pstAttr->bProgRevise = pstEntity->bProgRevise;
    pstAttr->bAlwaysFlushSrc = pstEntity->bAlwaysFlushSrc;

    return s32Ret;
}

HI_S32 VPSS_IN_SetSrcMode(VPSS_IN_ENTITY_S *pstEntity, VPSS_IN_SOURCE_S stMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    VPSS_CHECK_NULL(pstEntity);

    pstEntity->hSource = stMode.hSource;
    pstEntity->enMode = stMode.enMode;
    pstEntity->pfnAcqCallback = stMode.pfnAcqCallback;
    pstEntity->pfnRlsCallback = stMode.pfnRlsCallback;

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */
