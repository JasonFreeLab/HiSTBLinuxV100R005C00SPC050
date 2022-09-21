/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_win_share.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017-05-12
  Description   : this file keeps win and disp shared structures and functions.
  History       :
  1.Date        : 2017-05-12
    Author      : q00293180
    Modification: Created file
*******************************************************************************/

#include "drv_win_share.h"
#include "drv_win_priv.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

static WIN_SHARE_INFO_S stWinShareInfo = {0};


/*****************************************************************************
***                                                Internal functions
******************************************************************************/
static HI_VOID WIN_SHARE_INNER_SetValidWinNum(WIN_SHARE_INFO_S *pstWinShareInfo)
{
    HI_U32 u32Index = 0;
    HI_U32 u32ValidWinNum = 0;

    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        if (WIN_SHARE_HandleValid(pstWinShareInfo->stWinInfo[u32Index].hWinHandle))
        {
            u32ValidWinNum++;
        }
    }

    pstWinShareInfo->u32HdWinNum = u32ValidWinNum;

    return;
}

/*****************************************************************************/




/*****************************************************************************
***                                                External functions
******************************************************************************/
HI_BOOL WIN_SHARE_HandleValid(HI_HANDLE hWinHandle)
{
    if ((WIN_INDEX_PREFIX == WinGetPrefix(hWinHandle))
        && (HI_DRV_DISPLAY_1 == WinGetDispId(hWinHandle)))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_BOOL WIN_SHARE_FindTheValidWin(WIN_INFO_S *pstWinInfo,
                                            HI_U32      *pu32Index)
{
    HI_U32 u32Index = INVALID_WIN_INDEX, u32Count = 0;
    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        if (WIN_SHARE_HandleValid(pstWinInfo[u32Index].hWinHandle))
        {
            u32Count++;
            *pu32Index = u32Index;
        }
    }

    //CANNOT find the valid win,just return.
    if (1 != u32Count)
    {
        return HI_FALSE;
    }

    return HI_TRUE;

}


/*****************************************************************************/

HI_VOID WIN_SHARE_ResetShareInfo(HI_VOID)
{
    HI_U32 u32Index = 0;

    memset(&stWinShareInfo,0x0,sizeof(WIN_SHARE_INFO_S));
    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        stWinShareInfo.stWinInfo[u32Index].hWinHandle = HI_INVALID_HANDLE;
    }

    return;
}

HI_VOID WIN_SHARE_SetWinInfo(WIN_INFO_S *pstWinInfo)
{
    HI_U32 u32WinIndex = 0;

    u32WinIndex = pstWinInfo->hWinHandle & 0xFF;
    stWinShareInfo.stWinInfo[u32WinIndex] = *pstWinInfo;

    return;
}

HI_VOID WIN_SHARE_GetShareInfo(WIN_SHARE_INFO_S *pstWinShareInfo)
{

    WIN_SHARE_INNER_SetValidWinNum(&stWinShareInfo);
    *pstWinShareInfo = stWinShareInfo;
    return;
}

static HI_VOID WIN_SHARE_GetColorSpaceFromHdrMetadata(HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType,
                                                     HI_U8 u8ColourPrimaries,
                                                     HI_BOOL bFullRange,
                                                     HI_DRV_COLOR_SPACE_E *penColorSpace)
{
    switch (u8ColourPrimaries)
    {
        case 1:
            *penColorSpace =
                (HI_TRUE == bFullRange) ? HI_DRV_CS_BT709_YUV_FULL : HI_DRV_CS_BT709_YUV_LIMITED;
            break;
        case 9:
            *penColorSpace =
                (HI_TRUE == bFullRange) ? HI_DRV_CS_BT2020_YUV_FULL : HI_DRV_CS_BT2020_YUV_LIMITED;
            break;
        default:
            /* unknow : HDR10/HLG/SLF 2020; 2020F, 709L */
            if ((HI_DRV_VIDEO_FRAME_TYPE_HDR10 == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_HLG == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_SLF == enSrcFrameType))
            {
                *penColorSpace =
                    (HI_TRUE == bFullRange) ? HI_DRV_CS_BT2020_YUV_FULL : HI_DRV_CS_BT2020_YUV_LIMITED;
            }
            else //other  hdr frame.
            {
                *penColorSpace = HI_DRV_CS_BT709_YUV_LIMITED;
            }

            break;
    }

    return;
}


//get color space from frame.
HI_VOID WIN_SHARE_GetFrameColorSpace(HI_DRV_VIDEO_FRAME_S *pstFrame, HI_DRV_COLOR_SPACE_E *penColorSpace)
{
    if (HI_NULL == pstFrame)
    {
        *penColorSpace = HI_DRV_CS_BT709_YUV_LIMITED;
        return;
    }

    if (HI_DRV_VIDEO_FRAME_TYPE_SDR == pstFrame->enSrcFrameType)
    {
        *penColorSpace = ((HI_DRV_VIDEO_PRIVATE_S *)&pstFrame->u32Priv[0])->eColorSpace;
    }
    else
    {
        WIN_SHARE_GetColorSpaceFromHdrMetadata(pstFrame->enSrcFrameType,
                                               pstFrame->stColourInfo.u8ColourPrimaries,
                                               ((1 == pstFrame->stColourInfo.u8FullRangeFlag) ? HI_TRUE : HI_FALSE),
                                               penColorSpace);
    }

    return;
}

static HI_VOID WIN_SHARE_GetMarixTypeByAvs2(HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType,
                                            HI_U8 u8MatrixCoeffs,
                                            HI_BOOL bFullRange,
                                            WIN_FRAME_MATRIX_COEFF_E *penMatrixType)
{
    switch (u8MatrixCoeffs)
    {
        case 1:
            *penMatrixType =
                (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT709_F : WIN_FRAME_MATRIX_COEFF_BT709_L;
            break;
        case 8:
            *penMatrixType =
                (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT2020_NCL : WIN_FRAME_MATRIX_COEFF_BT2020_NCL;
            break;
        case 9:
            *penMatrixType =
                (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT2020_CL : WIN_FRAME_MATRIX_COEFF_BT2020_CL;
            break;
        default:
            /* unknow : HDR10/HLG/SLF 2020; 2020F, 709L */
            if ((HI_DRV_VIDEO_FRAME_TYPE_HDR10 == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_HLG == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_SLF == enSrcFrameType))
            {
                *penMatrixType = WIN_FRAME_MATRIX_COEFF_BT2020_NCL;
            }
            else //other hdr frame.
            {
                *penMatrixType = (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT709_F : WIN_FRAME_MATRIX_COEFF_BT709_L;
            }

            break;
    }

    return ;
}

static HI_VOID WIN_SHARE_GetMarixTypeByHevc(HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType,
                                            HI_U8 u8MatrixCoeffs,
                                            HI_BOOL bFullRange,
                                            WIN_FRAME_MATRIX_COEFF_E *penMatrixType)
{
    switch (u8MatrixCoeffs)
    {
        case 1:
            *penMatrixType =
                (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT709_F : WIN_FRAME_MATRIX_COEFF_BT709_L;
            break;
        case 9:
            *penMatrixType =
                (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT2020_NCL : WIN_FRAME_MATRIX_COEFF_BT2020_NCL;
            break;
        case 10:
            *penMatrixType =
                (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT2020_CL : WIN_FRAME_MATRIX_COEFF_BT2020_CL;
            break;
        default:
            /* unknow : HDR10/HLG/SLF 2020; 2020F, 709L */
            if ((HI_DRV_VIDEO_FRAME_TYPE_HDR10 == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_HLG == enSrcFrameType) ||
                (HI_DRV_VIDEO_FRAME_TYPE_SLF == enSrcFrameType))
            {
                *penMatrixType = WIN_FRAME_MATRIX_COEFF_BT2020_NCL;
            }
            else //other hdr frame.
            {
                *penMatrixType = (HI_TRUE == bFullRange) ? WIN_FRAME_MATRIX_COEFF_BT709_F : WIN_FRAME_MATRIX_COEFF_BT709_L;
            }

            break;
    }

    return ;
}

static HI_VOID WIN_SHARE_UnifyMdAvs2Type(WIN_SHARE_UNIFIED_METADATA_IN_S *pstMdInfoIn,
                                                    WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut)
{
    HI_BOOL bFullRange      = (1 == pstMdInfoIn->stColorDescriptionInfo.u8FullRangeFlag) ? HI_TRUE : HI_FALSE;
    HI_U8 u8ColourPrimaries = pstMdInfoIn->stColorDescriptionInfo.u8ColourPrimaries;
    HI_U8 u8MatrixCoeffs    = pstMdInfoIn->stColorDescriptionInfo.u8MatrixCoeffs;

    WIN_SHARE_GetColorSpaceFromHdrMetadata(pstMdInfoIn->enSrcFrameType,
                                           u8ColourPrimaries,
                                           bFullRange,
                                           &(pstMdInfoOut->enFrmCS));

    WIN_SHARE_GetMarixTypeByAvs2(pstMdInfoIn->enSrcFrameType,
                                 u8MatrixCoeffs,
                                 bFullRange,
                                 &(pstMdInfoOut->enMatrixType));
    return;
}

static HI_VOID WIN_SHARE_UnifyMdHevcType(WIN_SHARE_UNIFIED_METADATA_IN_S *pstMdInfoIn,
                                                    WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut)
{
    HI_BOOL bFullRange      = (1 == pstMdInfoIn->stColorDescriptionInfo.u8FullRangeFlag) ? HI_TRUE : HI_FALSE;
    HI_U8 u8ColourPrimaries = pstMdInfoIn->stColorDescriptionInfo.u8ColourPrimaries;
    HI_U8 u8MatrixCoeffs    = pstMdInfoIn->stColorDescriptionInfo.u8MatrixCoeffs;

    WIN_SHARE_GetColorSpaceFromHdrMetadata(pstMdInfoIn->enSrcFrameType,
                                           u8ColourPrimaries,
                                           bFullRange,
                                           &(pstMdInfoOut->enFrmCS));

    WIN_SHARE_GetMarixTypeByHevc(pstMdInfoIn->enSrcFrameType,
                                 u8MatrixCoeffs,
                                 bFullRange,
                                 &(pstMdInfoOut->enMatrixType));
    return;
}


static HI_VOID WIN_SHARE_UnifyMdType(WIN_SHARE_UNIFIED_METADATA_IN_S *pstMdInfoIn,
                                               HI_DRV_VIDEO_STD_E  enVideoStd,
                                               WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut)
{
    switch(pstMdInfoIn->enSrcFrameType)
    {
        case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
            pstMdInfoOut->enEotfType = WIN_FRAME_EOTF_2084;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HLG:
            pstMdInfoOut->enEotfType = WIN_FRAME_EOTF_HLG;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_SLF:
            pstMdInfoOut->enEotfType = WIN_FRAME_EOTF_SLF;
            break;
        default:
            pstMdInfoOut->enEotfType = WIN_FRAME_EOTF_1886;
            break;
    }

    if (HI_DRV_STD_AVS2 == enVideoStd)
    {
        WIN_SHARE_UnifyMdAvs2Type(pstMdInfoIn, pstMdInfoOut);
    }
    else
    {
        WIN_SHARE_UnifyMdHevcType(pstMdInfoIn, pstMdInfoOut);
    }

    return;
}

static HI_VOID WIN_SHARE_UnifyMdValueHdr10ByHevc(WIN_SHARE_UNIFIED_METADATA_IN_S *pstMdInfoIn,
                                               WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut)
{
    HI_U32 i;

    /* Mastering Info */
    pstMdInfoOut->bMasteringAvailable = pstMdInfoIn->bMasteringAvailable;
    pstMdInfoOut->stMasteringInfo.u16WhitePoint_x = pstMdInfoIn->stMasteringInfo.u16WhitePoint_x;
    pstMdInfoOut->stMasteringInfo.u16WhitePoint_y = pstMdInfoIn->stMasteringInfo.u16WhitePoint_y;
    pstMdInfoOut->stMasteringInfo.u32MaxDisplayMasteringLuminance
        = pstMdInfoIn->stMasteringInfo.u32MaxDisplayMasteringLuminance;
    pstMdInfoOut->stMasteringInfo.u32MinDisplayMasteringLuminance
        = pstMdInfoIn->stMasteringInfo.u32MinDisplayMasteringLuminance;
    for (i = 0; i < 3; i++)
    {
        pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_x[i]
            = pstMdInfoIn->stMasteringInfo.u16DisplayPrimaries_x[i];
        pstMdInfoOut->stMasteringInfo.u16DisplayPrimaries_y[i]
            = pstMdInfoIn->stMasteringInfo.u16DisplayPrimaries_y[i];
    }

    /* Content Info */
    pstMdInfoOut->bContentAvailable  = pstMdInfoIn->bContentAvailable;
    pstMdInfoOut->stContentInfo.u32MaxContentLightLevel
        = pstMdInfoIn->stContentInfo.u32MaxContentLightLevel;
    pstMdInfoOut->stContentInfo.u32MaxPicAverageLightLevel
        = pstMdInfoIn->stContentInfo.u32MaxPicAverageLightLevel;

    return;

}

static HI_VOID WIN_SHARE_UnifyMdValue(WIN_SHARE_UNIFIED_METADATA_IN_S *pstMdInfoIn,
                                               WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut)
{
    if ((HI_DRV_VIDEO_FRAME_TYPE_HDR10 == pstMdInfoIn->enSrcFrameType)
        || (HI_DRV_VIDEO_FRAME_TYPE_HLG == pstMdInfoIn->enSrcFrameType)
        || (HI_DRV_VIDEO_FRAME_TYPE_SLF == pstMdInfoIn->enSrcFrameType))
    {
        WIN_SHARE_UnifyMdValueHdr10ByHevc(pstMdInfoIn, pstMdInfoOut);
    }

    return;
}


HI_S32  WIN_SHARE_GetUnifiedMetadata(WIN_SHARE_UNIFIED_METADATA_IN_S *pstMdInfoIn,
                                               HI_DRV_VIDEO_STD_E  enVideoStd,
                                               WIN_SHARE_UNIFIED_METADATA_OUT_S *pstMdInfoOut)
{
    if ((HI_NULL == pstMdInfoIn) ||
        (HI_NULL == pstMdInfoOut))
    {
        HI_ERR_WIN("pstMdInfoIn or pstMdInfoOut is NULL\n");
        return HI_ERR_VO_NULL_PTR;
    }

    pstMdInfoOut->enSrcFrameType = pstMdInfoIn->enSrcFrameType;
    if (HI_DRV_VIDEO_FRAME_TYPE_SDR == pstMdInfoIn->enSrcFrameType)
    {
        return HI_SUCCESS;
    }

    WIN_SHARE_UnifyMdType(pstMdInfoIn, enVideoStd, pstMdInfoOut);
    WIN_SHARE_UnifyMdValue(pstMdInfoIn, pstMdInfoOut);

    return HI_SUCCESS;
}


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */


