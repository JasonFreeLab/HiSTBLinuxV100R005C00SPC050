/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_disp_dolby.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017-06-08
  Description   : Dolby HDR processing functions.
  History       :
  1.Date        : 2017-06-08
    Author      : sdk
    Modification: Created file
*******************************************************************************/
#include "hi_drv_hdmi.h"
#include "hi_drv_module.h"
#include "drv_disp_priv.h"
#include "drv_disp_bufcore.h"
#include "drv_disp_dolby.h"
#include "drv_window.h"
#include "KdmTypeFxp.h"
#include "vdp_hal_chn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif


//*******************************NEW STUCTURE CODE****************************
HI_VOID XDR_DOLBY_GetCoeffByFrm(HI_DRV_VIDEO_FRAME_S      *pstFrm,
                                          DRV_DISP_DOLBY_PLAY_INFO_S *pstDolbyInfo)
{
    DISP_BUF_NODE_S *pstDispBufNode = HI_NULL;
    DRV_DISP_DOLBY_COEFF_S *pstDolbyCoeff = HI_NULL;
    HI_U32           u32CompLen  = 0;
    HI_U32           u32DmCfgLen = 0;
    HI_U32           u32KsDmLen  = 0;
    HI_U32           u32Hdr10InfoFrmLen = 0;

    pstDispBufNode = container_of((HI_U32 *)pstFrm,DISP_BUF_NODE_S,u32Data[0]);//use container_of method to get the node.

    u32CompLen  = pstDispBufNode->stHdrInfo.u32CompLen;
    u32DmCfgLen = pstDispBufNode->stHdrInfo.u32DmCfgLen;
    u32KsDmLen  = pstDispBufNode->stHdrInfo.u32DmRegLen;
    u32Hdr10InfoFrmLen= pstDispBufNode->stHdrInfo.u32Hdr10InfoFrmLen;
    pstDolbyInfo->stDolbyCoeff.u32UpMdLen = pstDispBufNode->stHdrInfo.u32UpMdLen;

    pstDolbyInfo->bELVaild = pstDispBufNode->bValidData2;
    pstDolbyCoeff = &pstDolbyInfo->stDolbyCoeff;
    //get composer cfg and dm reg metadata from buffer Node.
    memcpy(&pstDolbyCoeff->stCompCfg,pstDispBufNode->u8Metadata,u32CompLen);
    memcpy(&pstDolbyCoeff->stDmCfg,pstDispBufNode->u8Metadata + u32CompLen,u32DmCfgLen);
    memcpy(&pstDolbyCoeff->stDmKs,pstDispBufNode->u8Metadata + u32CompLen + u32DmCfgLen,u32KsDmLen);
    memcpy(&pstDolbyCoeff->stHdr10InfoFrm,pstDispBufNode->u8Metadata + u32CompLen + u32DmCfgLen + u32KsDmLen,u32Hdr10InfoFrmLen);
    memcpy(&pstDolbyCoeff->u8MdBuf,pstDispBufNode->u8Metadata + u32CompLen + u32DmCfgLen + u32KsDmLen + u32Hdr10InfoFrmLen,pstDolbyInfo->stDolbyCoeff.u32UpMdLen);

    return;
}

HI_VOID XDR_DOLBY_GetHdr10InfoFrm(hdr_10_infoframe_t *pstHdr10InfoFrm,
                                            const HI_DRV_DISP_OUT_TYPE_E enDispOutType,
                                            HI_DRV_HDMI_HDR_ATTR_S   *pstHdmiHdrAttr)
{
    if(HI_DRV_DISP_TYPE_HDR10_CERT == enDispOutType)
    {
        pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_CEA_861_3_AUTHEN;
    }
    else
    {
        pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_CEA_861_3;
    }

    pstHdmiHdrAttr->enEotfType = HI_DRV_HDMI_EOTF_SMPTE_ST_2084;
    pstHdmiHdrAttr->enMetadataId = HI_DRV_HDMI_HDR_METADATA_ID_0;

    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries0_X = (pstHdr10InfoFrm->display_primaries_x_0_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_x_0_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries0_Y = (pstHdr10InfoFrm->display_primaries_y_0_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_y_0_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries1_X = (pstHdr10InfoFrm->display_primaries_x_1_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_x_1_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries1_Y = (pstHdr10InfoFrm->display_primaries_y_1_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_y_1_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries2_X = (pstHdr10InfoFrm->display_primaries_x_2_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_x_2_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries2_Y = (pstHdr10InfoFrm->display_primaries_y_2_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_y_2_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16WhitePoint_X = (pstHdr10InfoFrm->white_point_x_MSB << 8) |
                                                           (pstHdr10InfoFrm->white_point_x_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16WhitePoint_Y = (pstHdr10InfoFrm->white_point_y_MSB << 8) |
                                                           (pstHdr10InfoFrm->white_point_y_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16MaxLuminance = (pstHdr10InfoFrm->max_display_mastering_luminance_MSB << 8) |
                                                           (pstHdr10InfoFrm->max_display_mastering_luminance_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16MinLuminance = (pstHdr10InfoFrm->min_display_mastering_luminance_MSB << 8) |
                                                           (pstHdr10InfoFrm->min_display_mastering_luminance_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16MaxLightLevel= (pstHdr10InfoFrm->max_content_light_level_MSB << 8) |
                                                           (pstHdr10InfoFrm->max_content_light_level_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16AverageLightLevel= (pstHdr10InfoFrm->max_frame_average_light_level_MSB << 8) |
                                                           (pstHdr10InfoFrm->max_frame_average_light_level_LSB);
    /* !NOTICE! here should use no-const luminous,otherwise may cause display problem on
    * some TVs which not support const luminous. */
    pstHdmiHdrAttr->enColorimetry = HI_DRV_HDMI_COLORIMETRY_2020_NON_CONST_LUMINOUS;
    return ;
}


static DRV_DISP_DOLBY_PLAY_INFO_S g_stDolbyInfo = {0};

HI_VOID XDR_DOLBY_Process(DISP_S                *pstDisp,
                                  WIN_INFO_S            *pstWinInfo,
                                  HI_DRV_COLOR_SPACE_E   *penOutCs,
                                  HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr)
{
    if (HI_NULL == pstWinInfo->pCurrentFrame)
    {
        *pstHdmiHdrAttr = pstDisp->stXdrPlayInfo.stPreHdmiHdrAttr;
        g_stDolbyInfo     = pstDisp->stDolbyInfo;
    }
    else
    {
        XDR_DOLBY_GetCoeffByFrm(pstWinInfo->pCurrentFrame, &g_stDolbyInfo);

        switch(pstWinInfo->enOutType)
        {
            case HI_DRV_DISP_TYPE_HDR10:
            case HI_DRV_DISP_TYPE_HDR10_CERT:
                XDR_DOLBY_GetHdr10InfoFrm(&g_stDolbyInfo.stDolbyCoeff.stHdr10InfoFrm,
                                          pstWinInfo->enOutType,
                                          pstHdmiHdrAttr);
                *penOutCs = HI_DRV_CS_BT2020_YUV_LIMITED;
                break;
            case HI_DRV_DISP_TYPE_NORMAL:
            case HI_DRV_DISP_TYPE_SDR_CERT:
                pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_DISABLE;
                *penOutCs = HI_DRV_CS_BT709_YUV_LIMITED;
                break;
            case HI_DRV_DISP_TYPE_DOLBY:
                pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_DOLBY_TUNNELING;
                *penOutCs = HI_DRV_CS_BT709_YUV_LIMITED;
                break;
            default:
                DISP_ERROR("Invalid Output Type in Dolby process.\n");
                pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_DISABLE;
                *penOutCs = HI_DRV_CS_BT709_YUV_LIMITED;
                break;

        }

    }

    //config dolby path.
    pstDisp->pstIntfOpt->PF_ConfigDolbyPath(pstWinInfo,&g_stDolbyInfo);

    //record dolby coeff.
    pstDisp->stDolbyInfo = g_stDolbyInfo;

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
