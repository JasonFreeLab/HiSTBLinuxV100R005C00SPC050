/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_xdr_policy.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2017/06/12
Last Modified :
Description   : this file use to adapt hal's structures.
Function List :
History       :
******************************************************************************/

#include "hal_xdr_policy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

HI_BOOL XDR_SPECIFIC_CheckUserSetColorSpaceValid(HI_DRV_DISP_COLOR_SPACE_E enUserSetColorSpace)
{
    if (HI_DRV_DISP_COLOR_SPACE_BUTT <= enUserSetColorSpace)
    {
        HI_ERR_DISP("enUserSetColorSpace is invalid.\n");
        return HI_FALSE;
    }

    /* support BT709/BT2020/Auto. */
    return HI_TRUE;
}


#ifndef __DISP_PLATFORM_BOOT__
static HI_BOOL XDR_SPECIFIC_CheckVdmProcessConflic(HI_BOOL *pbVdmConArray)
{
    HI_U32 u32Index = 0, u32Count = 0;

    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        if (pbVdmConArray[u32Index])
        {
            u32Count++;
        }
    }

    if (1 >= u32Count)
    {
        return HI_FALSE;
    }
    else
    {
        return HI_TRUE;
    }
}

static HI_VOID XDR_SPECIFIC_ResetVdmArray(HI_BOOL *pbVdmArray)
{
    HI_U32 u32Index = 0;

    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        pbVdmArray[u32Index] = HI_FALSE;
    }

    return;
}


HI_VOID XDR_SPECIFIC_AdjustConfig(WIN_SHARE_INFO_S  *pstWinShareInfo,
                                       HI_U32             u32MaxWinIndex,
                                       HI_BOOL            *pbVdmProcess,
                                       HI_DRV_DISP_PROCESS_MODE_E  enLastDispProcessMode,
                                       HI_DRV_DISP_PROCESS_MODE_E  *penDispProcessMode,
                                       HI_DRV_COLOR_SPACE_E   *penOutCs,
                                       HI_DRV_DISP_OUT_TYPE_E *penOutType)
{
    HI_U32 u32Index = 0;
    WIN_INFO_S *pstWinInfo = HI_NULL;
    HI_DRV_DISP_PROCESS_MODE_E enDispMode = enLastDispProcessMode;
    HI_BOOL  bHdrProcess = HI_FALSE;

    //if conflict, choose max win's vdm process.
    if (XDR_SPECIFIC_CheckVdmProcessConflic(pbVdmProcess))
    {
        XDR_SPECIFIC_ResetVdmArray(pbVdmProcess);
        pbVdmProcess[u32MaxWinIndex] = HI_TRUE;
    }

    //more than one win are not sdr in sdr out, it should go through hdr path.
    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        pstWinInfo = &pstWinShareInfo->stWinInfo[u32Index];

        if (HI_NULL != pstWinInfo->pCurrentFrame)
        {
            //if close hdr function. Force to set hdr frame as sdr, output type as sdr.inCs as BT.709.
            if (pstWinInfo->bCloseHdr)
            {
                pstWinInfo->pCurrentFrame->enSrcFrameType = HI_DRV_VIDEO_FRAME_TYPE_SDR;
                pstWinInfo->enOutType = HI_DRV_DISP_TYPE_NORMAL;
                pstWinInfo->enInCsc   = HI_DRV_CS_BT709_YUV_LIMITED;
                enDispMode = HI_DRV_DISP_PROCESS_MODE_SDR;
                pbVdmProcess[u32Index] = HI_FALSE;
            }

            if ((HI_DRV_VIDEO_FRAME_TYPE_SDR != pstWinInfo->pCurrentFrame->enSrcFrameType)
                || (HI_DRV_DISP_TYPE_NORMAL != pstWinInfo->enOutType))
            {
                bHdrProcess = HI_TRUE;
            }

        }
    }

    if (bHdrProcess)
    {
        enDispMode = HI_DRV_DISP_PROCESS_MODE_HDR;
    }

    *penOutCs = pstWinShareInfo->stWinInfo[u32MaxWinIndex].enOutCsc;
    *penOutType = pstWinShareInfo->stWinInfo[u32MaxWinIndex].enOutType;
    *penDispProcessMode = enDispMode;
    return;
}

HI_BOOL XDR_SPECIFIC_CheckOutputSignalValid(HI_DRV_DISP_OUT_TYPE_E enDispType)
{
    HI_BOOL bValid = HI_FALSE;
    switch (enDispType)
    {
        case HI_DRV_DISP_TYPE_NORMAL:
        case HI_DRV_DISP_TYPE_HDR10:
        case HI_DRV_DISP_TYPE_HLG:
        case HI_DRV_DISP_TYPE_DOLBY:
        case HI_DRV_DISP_TYPE_SDR_CERT:
        case HI_DRV_DISP_TYPE_HDR10_CERT:
            bValid = HI_TRUE;
            break;

        /* unsupport belowed output type currently.*/
        case HI_DRV_DISP_TYPE_AUTO:
        case HI_DRV_DISP_TYPE_TECHNICOLOR:
            bValid = HI_FALSE;
            break;
        default:
            bValid = HI_FALSE;
            break;
    }

    return bValid;

}

HI_VOID VDP_DRV_MaskAndBackupGfx(HI_U32 u32GfxLayerId, HI_U32* pu32Alpha, HI_U32* pu32MuteState)
{
    return;
}
HI_VOID VDP_DRV_UnmaskGfx(HI_U32 u32GfxLayerId, HI_U32 u32Alpha, HI_U32 u32MuteState)
{
    return;
}
HI_VOID VDP_DRV_SetGfxMixvBypassState(HI_U32 u32GfxLayerId, HI_BOOL bEnable)
{
    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

