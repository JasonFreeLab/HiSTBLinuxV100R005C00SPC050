/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_hdr.c
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/03/19
  Description  :

******************************************************************************/
#include <linux/string.h>

#include "pq_mng_hdr_alg.h"
#include "pq_mng_hdr.h"
#include "pq_hal_comm.h"
#include "pq_hal_hdr.h"

static HI_BOOL sg_bHdrInitFlag      = HI_FALSE;

HI_S32 PQ_MNG_InitHDR(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_TRUE == sg_bHdrInitFlag)
    {
        return HI_SUCCESS;
    }

    sg_bHdrInitFlag = HI_TRUE;

    PQ_CHECK_NULL_PTR(pstPqParam);

    s32Ret = PQ_HAL_InitHDR(pstPqParam, bDefault);

    return s32Ret;
}

HI_S32 PQ_MNG_DeInitHDR(HI_VOID)
{
    if (HI_FALSE == sg_bHdrInitFlag)
    {
        return HI_SUCCESS;
    }

    sg_bHdrInitFlag   = HI_FALSE;

    return HI_SUCCESS;
}

static HI_S32 PQ_MNG_GetSdrColorMatrixTypeFromSource(HI_BOOL bFullRange, PQ_SOURCE_MODE_E enSourceMode,
        HI_PQ_HDR_MATRIX_COEFF_E *penMatrixType)
{
    if ((SOURCE_MODE_ALL <= enSourceMode) && (SOURCE_MODE_NO == enSourceMode))
    {
        HI_ERR_PQ("[%d]Switch : Hdr Sdr Source Enhance Mode Set error!\n", enSourceMode);
        return HI_FAILURE;
    }

    switch (enSourceMode)
    {
            /* 2020 CL or NCL ???? */
        case SOURCE_MODE_UHD:
        {
            *penMatrixType = HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL ;
        }
        break;
        case SOURCE_MODE_HD:
        {
            *penMatrixType = (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT709_F : HI_PQ_HDR_MATRIX_COEFF_BT709_L;
        }
        break;
        case SOURCE_MODE_SD:
        {
            *penMatrixType = (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT601_F : HI_PQ_HDR_MATRIX_COEFF_BT601_L;
        }
        break;
        default:
        {
            HI_ERR_PQ("Hdr Sdr Source Enhance Source error!\n");
        }
        break;
    }

    return HI_SUCCESS;
}


static HI_S32 PQ_MNG_GetSdrColorPrimatiFromSource(HI_BOOL bFullRange, PQ_SOURCE_MODE_E enSourceMode,
        HI_DRV_COLOR_SPACE_E *penColorPrimaties)
{
    if ((SOURCE_MODE_ALL <= enSourceMode) && (SOURCE_MODE_NO == enSourceMode))
    {
        HI_ERR_PQ("[%d]Switch : Hdr Sdr Source Enhance Mode Set error!\n", enSourceMode);
        return HI_FAILURE;
    }

    switch (enSourceMode)
    {
        case SOURCE_MODE_UHD:
        {
            *penColorPrimaties = (HI_TRUE == bFullRange) ? HI_DRV_CS_BT2020_YUV_FULL : HI_DRV_CS_BT2020_YUV_LIMITED;
        }
        break;
        case SOURCE_MODE_HD:
        {
            *penColorPrimaties = (HI_TRUE == bFullRange) ? HI_DRV_CS_BT709_YUV_FULL : HI_DRV_CS_BT709_YUV_LIMITED;
        }
        break;
        case SOURCE_MODE_SD:
        {
            *penColorPrimaties = (HI_TRUE == bFullRange) ? HI_DRV_CS_BT601_YUV_FULL : HI_DRV_CS_BT601_YUV_LIMITED;
        }
        break;
        default:
        {
            HI_ERR_PQ("Hdr Sdr Source Enhance Source error!\n");
        }
        break;
    }

    return HI_SUCCESS;
}


static HI_S32 pq_mng_hdr_GetHDRInfoOutColorSpace(HI_U8 u8ColourPrimaries, HI_BOOL bFullRange, PQ_SOURCE_MODE_E enSourceMode,
        HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType, HI_DRV_COLOR_SPACE_E *pEnColorSpace)
{
    HI_S32 s32Ret = HI_FAILURE;

    switch (u8ColourPrimaries)
    {
        case 1:
            *pEnColorSpace =
                (HI_TRUE == bFullRange) ? HI_DRV_CS_BT709_YUV_FULL : HI_DRV_CS_BT709_YUV_LIMITED;
            break;
        case 9:
            *pEnColorSpace =
                (HI_TRUE == bFullRange) ? HI_DRV_CS_BT2020_YUV_FULL : HI_DRV_CS_BT2020_YUV_LIMITED;
            break;
        default:
            /* unknow : HDR10/HLG 2020; 2020F, 709L */
            if ((HI_DRV_VIDEO_FRAME_TYPE_HDR10 == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_HLG == enSrcFrameType))
            {
                *pEnColorSpace =
                    (HI_TRUE == bFullRange) ? HI_DRV_CS_BT2020_YUV_FULL : HI_DRV_CS_BT2020_YUV_LIMITED;
            }
            else //sdr
            {
                s32Ret = PQ_MNG_GetSdrColorPrimatiFromSource(bFullRange, enSourceMode, pEnColorSpace);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_PQ("PQ_MNG_GetSdrColorPrimatiFromSource error\n");
                    return HI_FAILURE;
                }
            }

            break;
    }


    return HI_SUCCESS;
}

static HI_S32 pq_mng_hdr_GetHDRInfoEnMarixHevcType(HI_U8 u8MatrixCoeffs, HI_BOOL bFullRange,
        PQ_SOURCE_MODE_E enSourceMode, HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType, HI_PQ_HDR_MATRIX_COEFF_E *pEnMatrixType)
{
    HI_S32 s32Ret           = HI_FAILURE;

    switch (u8MatrixCoeffs)
    {
        case 1:
            *pEnMatrixType =
                (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT709_F : HI_PQ_HDR_MATRIX_COEFF_BT709_L;
            break;
        case 9:
            *pEnMatrixType =
                (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL : HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL;
            break;
        case 10:
            *pEnMatrixType =
                (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT2020_CL : HI_PQ_HDR_MATRIX_COEFF_BT2020_CL;
            break;
        default:
            /* unknow : HDR10/HLG 2020; 2020F, 709L */
            if ((HI_DRV_VIDEO_FRAME_TYPE_HDR10 == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_HLG == enSrcFrameType))
            {
                *pEnMatrixType = HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL;
            }
            else //sdr
            {
                s32Ret = PQ_MNG_GetSdrColorMatrixTypeFromSource(bFullRange, enSourceMode, pEnMatrixType);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_PQ("PQ_MNG_GetSdrColorMatrixTypeFromSource error\n");
                    return HI_FAILURE;
                }
            }

            break;
    }


    return HI_SUCCESS;
}

static HI_S32 pq_mng_hdr_GetHDRInfoEnMarixAvs2Type(HI_U8 u8MatrixCoeffs, HI_BOOL bFullRange,
        PQ_SOURCE_MODE_E enSourceMode, HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType, HI_PQ_HDR_MATRIX_COEFF_E *pEnMatrixType)
{
    HI_S32 s32Ret           = HI_FAILURE;

    switch (u8MatrixCoeffs)
    {
        case 1:
            *pEnMatrixType =
                (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT709_F : HI_PQ_HDR_MATRIX_COEFF_BT709_L;
            break;
        case 8:
            *pEnMatrixType =
                (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL : HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL;
            break;
        case 9:
            *pEnMatrixType =
                (HI_TRUE == bFullRange) ? HI_PQ_HDR_MATRIX_COEFF_BT2020_CL : HI_PQ_HDR_MATRIX_COEFF_BT2020_CL;
            break;
        default:
            /* unknow : HDR10/HLG 2020; 2020F, 709L */
            if ((HI_DRV_VIDEO_FRAME_TYPE_HDR10 == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_HLG == enSrcFrameType))
            {
                *pEnMatrixType = HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL;
            }
            else //sdr
            {
                s32Ret = PQ_MNG_GetSdrColorMatrixTypeFromSource(bFullRange, enSourceMode, pEnMatrixType);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_PQ("PQ_MNG_GetSdrColorMatrixTypeFromSource error\n");
                    return HI_FAILURE;
                }
            }

            break;
    }

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_GetHDRCfg(HI_PQ_WIN_HDR_INFO *pstWinHdrInfo, HI_PQ_HDR_CFG *pstPqHdrCfg)
{
    PQ_CHECK_NULL_PTR(pstWinHdrInfo);
    PQ_CHECK_NULL_PTR(pstPqHdrCfg);

    return PQ_HAL_GetHDRCfg(pstWinHdrInfo, pstPqHdrCfg);
}

HI_S32 PQ_MNG_SetHDRDefaultCfg(HI_BOOL bDefault)
{
    return PQ_HAL_SetHDRDefaultCfg(bDefault);
}

HI_S32 PQ_MNG_GetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstHdrParaMode)
{
    PQ_CHECK_NULL_PTR(pstHdrParaMode);

    return PQ_HAL_GetHDRParaMode(pstHdrParaMode);
}

HI_S32 PQ_MNG_SetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstSetSoftPara)
{
    PQ_CHECK_NULL_PTR(pstSetSoftPara);

    return PQ_HAL_SetHDRParaMode(pstSetSoftPara);
}

HI_S32 PQ_MNG_SetHDRTmLut(HI_PQ_HDR_TM_LUT_S *pstTMSetLut)
{
    PQ_CHECK_NULL_PTR(pstTMSetLut);

    return PQ_HAL_SetHDRTmLut(pstTMSetLut);
}

HI_S32 PQ_MNG_GetHDRTmLut(HI_PQ_HDR_TM_LUT_S *pstTMSetLut)
{
    PQ_CHECK_NULL_PTR(pstTMSetLut);

    return PQ_HAL_GetHDRTmLut(pstTMSetLut);
}

HI_S32 PQ_MNG_SetHDRTmXpos(HI_U8 *pstTMSetXpos)
{
    PQ_CHECK_NULL_PTR(pstTMSetXpos);

    return PQ_HAL_SetHDRTmXpos(pstTMSetXpos);
}

HI_S32 PQ_MNG_GetHDRTmXpos(HI_U8 *pstTMGetXpos)
{
    PQ_CHECK_NULL_PTR(pstTMGetXpos);

    return PQ_HAL_GetHDRTmXpos(pstTMGetXpos);
}

HI_S32 PQ_MNG_SetHDRTYMap(HI_U8 *pstTYmapSet)
{
    PQ_CHECK_NULL_PTR(pstTYmapSet);

    return PQ_HAL_SetHDRTYMap(pstTYmapSet);
}

HI_S32 PQ_MNG_GetHDRTYMap(HI_U8 *pstTYmapGet)
{
    PQ_CHECK_NULL_PTR(pstTYmapGet);

    return PQ_HAL_GetHDRTYMap(pstTYmapGet);
}

HI_S32 PQ_MNG_GetHDRSrcLum(HI_PQ_HDR_SRC_LUM_S *pstGetSoftPara)
{
    PQ_CHECK_NULL_PTR(pstGetSoftPara);

    return PQ_HAL_GetHDRSrcLum(pstGetSoftPara);
}

HI_S32 PQ_MNG_SetHDRSoftPara(HI_PQ_HDR_SOFT_PARA_S *pstSetSoftPara)
{
    PQ_CHECK_NULL_PTR(pstSetSoftPara);

    return PQ_HAL_SetHDRSoftPara(pstSetSoftPara);
}

HI_S32 PQ_MNG_GetHDRSoftPara(HI_PQ_HDR_SOFT_PARA_S *pstGetSoftPara)
{
    PQ_CHECK_NULL_PTR(pstGetSoftPara);

    return PQ_HAL_GetHDRSoftPara(pstGetSoftPara);
}

HI_S32 PQ_MNG_SetHDRToneMap(HI_U8 *pstSetToneMap)
{
    PQ_CHECK_NULL_PTR(pstSetToneMap);

    return PQ_HAL_SetHDRToneMap(pstSetToneMap);
}

HI_S32 PQ_MNG_GetHDRToneMap(HI_U8 *pstGetToneMap)
{
    PQ_CHECK_NULL_PTR(pstGetToneMap);

    return PQ_HAL_GetHDRToneMap(pstGetToneMap);
}

HI_S32 PQ_MNG_SetHDRSatMap(HI_U8 *pstSetSatMap)
{
    PQ_CHECK_NULL_PTR(pstSetSatMap);

    return PQ_HAL_SetHDRSatMap(pstSetSatMap);
}

HI_S32 PQ_MNG_GetHDRSatMap(HI_U8 *pstSetSatMap)
{
    PQ_CHECK_NULL_PTR(pstSetSatMap);

    return PQ_HAL_GetHDRSatMap(pstSetSatMap);
}

#define TRANSFER_CHARACTERISSTICS_HEVC_ST2084  16
#define TRANSFER_CHARACTERISSTICS_AVS2_ST2084  12

static HI_S32 pq_mng_UnifyHDRHevcType(HI_PQ_HDR_UNIFIED_METADATA_IN_S *pstHDRInfoIn,
                                      HI_PQ_HDR_UNIFIED_METADATA_OUT_S *pstHDRInfoOut)
{
    HI_BOOL bFullRange      = pstHDRInfoIn->stColorDescriptionInfo.u8FullRangeFlag;
    HI_U8 u8ColourPrimaries = pstHDRInfoIn->stColorDescriptionInfo.u8ColourPrimaries;
    HI_U8 u8MatrixCoeffs    = pstHDRInfoIn->stColorDescriptionInfo.u8MatrixCoeffs;

    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();

    if (HI_DRV_VIDEO_FRAME_TYPE_HDR10 == pstHDRInfoIn->enSrcFrameType)
    {
        pstHDRInfoOut->enEotfType = HI_PQ_HDR_EOTF_2084;
    }

    pq_mng_hdr_GetHDRInfoOutColorSpace(u8ColourPrimaries, bFullRange, enSourceMode,
                                       pstHDRInfoIn->enSrcFrameType, &(pstHDRInfoOut->enOutCS));

    pq_mng_hdr_GetHDRInfoEnMarixHevcType(u8MatrixCoeffs, bFullRange, enSourceMode,
                                         pstHDRInfoIn->enSrcFrameType, &(pstHDRInfoOut->enMatrixType));

    return HI_SUCCESS;
}

static HI_S32 pq_mng_UnifyHDRAvs2Type(HI_PQ_HDR_UNIFIED_METADATA_IN_S *pstHDRInfoIn,
                                      HI_PQ_HDR_UNIFIED_METADATA_OUT_S *pstHDRInfoOut)
{
    HI_BOOL bFullRange      = pstHDRInfoIn->stColorDescriptionInfo.u8FullRangeFlag;
    HI_U8 u8ColourPrimaries = pstHDRInfoIn->stColorDescriptionInfo.u8ColourPrimaries;
    HI_U8 u8MatrixCoeffs    = pstHDRInfoIn->stColorDescriptionInfo.u8MatrixCoeffs;

    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();

    if (HI_DRV_VIDEO_FRAME_TYPE_HDR10 == pstHDRInfoIn->enSrcFrameType)
    {
        pstHDRInfoOut->enEotfType = HI_PQ_HDR_EOTF_2084;
    }

    pq_mng_hdr_GetHDRInfoOutColorSpace(u8ColourPrimaries, bFullRange, enSourceMode,
                                       pstHDRInfoIn->enSrcFrameType, &(pstHDRInfoOut->enOutCS));

    pq_mng_hdr_GetHDRInfoEnMarixAvs2Type(u8MatrixCoeffs, bFullRange, enSourceMode,
                                         pstHDRInfoIn->enSrcFrameType, &(pstHDRInfoOut->enMatrixType));

    return HI_SUCCESS;

}

static HI_VOID pq_mng_UnifyHDRType(HI_PQ_HDR_UNIFIED_METADATA_IN_S *pstHDRInfoIn,
                                   HI_DRV_VIDEO_STD_E  enVideoStd,
                                   HI_PQ_HDR_UNIFIED_METADATA_OUT_S *pstHDRInfoOut)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_DRV_STD_AVS2 == enVideoStd)
    {
        s32Ret = pq_mng_UnifyHDRAvs2Type(pstHDRInfoIn, pstHDRInfoOut);
    }
    else
    {
        s32Ret = pq_mng_UnifyHDRHevcType(pstHDRInfoIn, pstHDRInfoOut);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("pq_mng_UnifyHDRType error\n");
    }

    return;
}

static HI_VOID pq_mng_UnifyHDRValueHDR10Hevc(HI_PQ_HDR_UNIFIED_METADATA_IN_S *pstHDRInfoIn,
        HI_PQ_HDR_UNIFIED_METADATA_OUT_S *pstHDRInfoOut)
{
    HI_U32 i;

    /* Mastering Info */
    pstHDRInfoOut->bMasteringAvailable = pstHDRInfoIn->bMasteringAvailable;
    pstHDRInfoOut->stMasteringInfo.u16WhitePoint_x = pstHDRInfoIn->stMasteringInfo.u16WhitePoint_x;
    pstHDRInfoOut->stMasteringInfo.u16WhitePoint_y = pstHDRInfoIn->stMasteringInfo.u16WhitePoint_y;
    pstHDRInfoOut->stMasteringInfo.u32MaxDisplayMasteringLuminance
        = pstHDRInfoIn->stMasteringInfo.u32MaxDisplayMasteringLuminance;
    pstHDRInfoOut->stMasteringInfo.u32MinDisplayMasteringLuminance
        = pstHDRInfoIn->stMasteringInfo.u32MinDisplayMasteringLuminance;
    for (i = 0; i < 3; i++)
    {
        pstHDRInfoOut->stMasteringInfo.u16DisplayPrimaries_x[i]
            = pstHDRInfoIn->stMasteringInfo.u16DisplayPrimaries_x[i];
        pstHDRInfoOut->stMasteringInfo.u16DisplayPrimaries_y[i]
            = pstHDRInfoIn->stMasteringInfo.u16DisplayPrimaries_y[i];
    }

    /* Content Info */
    pstHDRInfoOut->bContentAvailable  = pstHDRInfoIn->bContentAvailable;
    pstHDRInfoOut->stContentInfo.u32MaxContentLightLevel
        = pstHDRInfoIn->stContentInfo.u32MaxContentLightLevel;
    pstHDRInfoOut->stContentInfo.u32MaxPicAverageLightLevel
        = pstHDRInfoIn->stContentInfo.u32MaxPicAverageLightLevel;

    return;
}

static HI_VOID pq_mng_UnifyHDRValue(HI_PQ_HDR_UNIFIED_METADATA_IN_S *pstHDRInfoIn,
                                    HI_DRV_VIDEO_STD_E  enVideoStd,
                                    HI_PQ_HDR_UNIFIED_METADATA_OUT_S *pstHDRInfoOut)
{
    if (HI_DRV_VIDEO_FRAME_TYPE_HDR10 == pstHDRInfoIn->enSrcFrameType)
    {
        pq_mng_UnifyHDRValueHDR10Hevc(pstHDRInfoIn, pstHDRInfoOut);
    }

    return;
}

/**
\metadata in, metadata out;
\vdp charge metadata from pq to set color out
 \retval ::HI_SUCCESS

 */
static HI_S32 PQ_MNG_GetHDRUnifiedMetadata(HI_PQ_HDR_UNIFIED_METADATA_IN_S *pstHDRInfoIn,
                                    HI_DRV_VIDEO_STD_E  enVideoStd,
                                    HI_PQ_HDR_UNIFIED_METADATA_OUT_S *pstHDRInfoOut)
{
    PQ_CHECK_NULL_PTR(pstHDRInfoIn);
    PQ_CHECK_NULL_PTR(pstHDRInfoOut);

    pstHDRInfoOut->enSrcFrameType = pstHDRInfoIn->enSrcFrameType;

    pq_mng_UnifyHDRType(pstHDRInfoIn, enVideoStd, pstHDRInfoOut);
    pq_mng_UnifyHDRValue(pstHDRInfoIn, enVideoStd, pstHDRInfoOut);

    return HI_SUCCESS;
}

static HI_S32 PQ_MNG_SetHDRTMCurve(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    PQ_CHECK_NULL_PTR(pstHdrOffsetPara);

    return PQ_HAL_SetHDRTMCurve(pstHdrOffsetPara);
}

static HI_S32 PQ_MNG_GetHDRPqTm(HI_U32 u32TmType)
{
    return PQ_HAL_GetHDRPqTm(u32TmType);
}

static HI_S32 PQ_MNG_SetHdrCSCSetting(HI_PQ_PICTURE_SETTING_S *pstPicSetting)
{
    PQ_CHECK_NULL_PTR(pstPicSetting);

    return PQ_HAL_SetHdrCscSetting(pstPicSetting);
}

static HI_S32 PQ_MNG_SetHdrOffset(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    PQ_CHECK_NULL_PTR(pstHdrOffsetPara);

    return PQ_HAL_SetHdrOffset(pstHdrOffsetPara);
}

static HI_S32 PQ_MNG_SetHdrACCHistGram(HI_U32 u32ACCOutWidth, HI_U32 u32ACCOutHeight, HI_PQ_ACC_HISTGRAM_S *pstACCHistGram)
{
    PQ_CHECK_NULL_PTR(pstACCHistGram);

    return PQ_HAL_SetHDRACCHistGram(u32ACCOutWidth, u32ACCOutHeight, pstACCHistGram);
}

static stPQAlgFuncs stHDRFuncs =
{
    .Init                  = PQ_MNG_InitHDR,
    .DeInit                = PQ_MNG_DeInitHDR,
    .GetHdrCfg             = PQ_MNG_GetHDRCfg,
    .SetHdrDefaultCfg      = PQ_MNG_SetHDRDefaultCfg,
    .GetHdrUnifiedMetadata = PQ_MNG_GetHDRUnifiedMetadata,
    .SetHdrACCHistGram     = PQ_MNG_SetHdrACCHistGram,
    .SetHdrCSCVideoSetting = PQ_MNG_SetHdrCSCSetting,
    .SetHdrOffset          = PQ_MNG_SetHdrOffset,
    .SetHdrTMCurve         = PQ_MNG_SetHDRTMCurve,
    .GetHdrPqTm            = PQ_MNG_GetHDRPqTm
};

HI_S32 PQ_MNG_RegisterHDR(PQ_REG_TYPE_E  enType)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_HDR, enType, PQ_BIN_ADAPT_SINGLE, "hdr", HI_NULL, &stHDRFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterHDR(HI_VOID)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_HDR);

    return s32Ret;
}

