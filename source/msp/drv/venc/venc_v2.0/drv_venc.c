/*****************************************************************************
  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_venc.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/04/07
  Last Modified :
  Description   :
  Function List :
  History       :
  1.Date        :
  Author        : sdk
  Modification  : Created file
 ******************************************************************************/

#include "public.h"

#include "drv_win_ext.h"
#include "drv_venc_ext.h"
#include "drv_disp_ext.h"
#include "hi_drv_proc.h"
#include "hi_drv_module.h"
#include "hi_drv_file.h"
#include "hi_drv_reg.h"
#include "drv_venc_efl.h"
#include "drv_venc_buf_mng.h"
#include "drv_venc.h"
#include "hi_mpi_venc.h"
#include "hi_drv_video.h"
#include "hi_kernel_adapt.h"
#include "hi_reg_common.h"
#include "hi_osal.h"
#include "venc_hal_ext.h"
#ifdef VENC_SUPPORT_ATTACH_VI
#include "drv_vi_ext.h"
#endif
#ifdef VENC_SUPPORT_JPGE
#include "drv_jpge_ext.h"
#endif

#include <linux/delay.h>
#include <linux/kernel.h>

//#include "drv_vi_ext.h"
//#include "drv_ndpt_ext.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

//Check null pointer
//#define VDEC_APPENDIX_LEN 16
#define VENC_MAX_FRAME_LEN 200000
#define VENC_MB_NUM_QCIF   (99)
#define VENC_MB_NUM_CIF    (396)
#define VENC_MB_NUM_D1     (1620)
#define VENC_MB_NUM_720P   (3600)
#define VENC_MB_NUM_FULLHD (8160)

OPTM_VENC_CHN_S g_stVencChn[HI_VENC_MAX_CHN];
VEDU_OSAL_EVENT g_VencWait_Stream[HI_VENC_MAX_CHN];
extern VEDU_OSAL_EVENT g_VENC_Event_stream;

spinlock_t g_SendFrame_Lock[HI_VENC_MAX_CHN];     /*lock the destroy and send frame*/
//HI_DECLARE_MUTEX(g_VencStreamMutex[HI_VENC_MAX_CHN]);

volatile HI_U32 g_VENCCrgCtrl = 0;
//HI_S32 VencThreadGetIFrame(HI_VOID * arg);

HI_U32 g_vedu_chip_id = 0;
//static HI_U32 g_venc_curent_chn_num = 0;
extern VENC_BUFFER_S g_stKernelOmxmmz[HI_VENC_MAX_CHN][OMX_OUTPUT_PORT_BUFFER_MAX];

#ifdef VENC_SUPPORT_JPGE
extern JPGE_EXPORT_FUNC_S *pJpgeFunc;
#endif

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        if (hVencChn == NULL)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_CHN_BY_UHND(u32VeChn, hVencUsrChn) \
    do {\
        if (hVencUsrChn == HI_INVALID_HANDLE)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hUsrHandle == hVencUsrChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_PRIORITY_ID(s32VeChn, sPriorityID) \
    do {\
        sPriorityID = 0; \
        while (sPriorityID < HI_VENC_MAX_CHN)\
        {   \
            if (PriorityTab[0][sPriorityID] == s32VeChn)\
            { \
                break; \
            } \
            sPriorityID++; \
        } \
    } while (0)

//extern HI_U32 gVpNethandle;
wait_queue_head_t gEncodeFrame;
volatile HI_U32 gencodeframe = 0;
extern HI_S32 gMax, gBMAX;
//HI_U8 gSendbuf[VENC_MAX_FRAME_LEN + VDEC_APPENDIX_LEN + 4];
HI_U8 ZeroDelaySuffix[] = {0x00, 0x00, 0x01, 0x1e, 0x48, 0x53, 0x50, 0x49, 0x43, 0x45, 0x4E, 0x44, 0x00, 0x00, 0x01,
                           0x1e
                          };
HI_U32 gVencVppayload = 0;
//extern wait_queue_head_t stSendTimeQue;
//volatile HI_U32 gSendStart = 0;


HI_S8 PriorityTab[2][16] = {{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, {}};
///////////////////////////////////////////////////////////////
extern VENC_EXPORT_FUNC_S s_VencExportFuncs;

static HI_VOID GetPixFormat(HI_UNF_VIDEO_FORMAT_E VideoFormat, HI_DRV_PIX_FORMAT_E *pPixFormat)
{
    switch (VideoFormat)
    {
        case HI_UNF_FORMAT_YUV_SEMIPLANAR_422:
            *pPixFormat = HI_DRV_PIX_FMT_NV61_2X1;
            break;

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_420:
            *pPixFormat = HI_DRV_PIX_FMT_NV21;
            break;

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_420_UV:
            *pPixFormat = HI_DRV_PIX_FMT_NV12;
            break;

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_400:
            *pPixFormat = HI_DRV_PIX_FMT_NV80;
            break;

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_411:
            *pPixFormat = HI_DRV_PIX_FMT_NV12_411;
            break;

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_422_1X2:
            *pPixFormat = HI_DRV_PIX_FMT_NV61;
            break;

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_444:
            *pPixFormat = HI_DRV_PIX_FMT_NV42;
            break;

        case HI_UNF_FORMAT_YUV_PACKAGE_UYVY:
            *pPixFormat = HI_DRV_PIX_FMT_UYVY;
            break;

        case HI_UNF_FORMAT_YUV_PACKAGE_YUYV:
            *pPixFormat = HI_DRV_PIX_FMT_YUYV;
            break;

        case HI_UNF_FORMAT_YUV_PACKAGE_YVYU:
            *pPixFormat = HI_DRV_PIX_FMT_YVYU;
            break;

        case HI_UNF_FORMAT_YUV_PLANAR_400:
            *pPixFormat = HI_DRV_PIX_FMT_YUV400;
            break;

        case HI_UNF_FORMAT_YUV_PLANAR_411:
            *pPixFormat = HI_DRV_PIX_FMT_YUV411;
            break;

        case HI_UNF_FORMAT_YUV_PLANAR_420:
            *pPixFormat = HI_DRV_PIX_FMT_YUV420p;
            break;

        case HI_UNF_FORMAT_YUV_PLANAR_422_1X2:
            *pPixFormat = HI_DRV_PIX_FMT_YUV422_1X2;
            break;

        case HI_UNF_FORMAT_YUV_PLANAR_422_2X1:
            *pPixFormat = HI_DRV_PIX_FMT_YUV422_2X1;
            break;

        case HI_UNF_FORMAT_YUV_PLANAR_444:
            *pPixFormat = HI_DRV_PIX_FMT_YUV_444;
            break;

        case HI_UNF_FORMAT_YUV_PLANAR_410:
            *pPixFormat = HI_DRV_PIX_FMT_YUV410p;
            break;

        default:
            *pPixFormat = HI_DRV_PIX_BUTT;
            break;
    }
}

static HI_VOID GetFrameType(HI_UNF_VIDEO_FRAME_PACKING_TYPE_E FramePackingType, HI_DRV_FRAME_TYPE_E *pFrmType)
{
    switch (FramePackingType)
    {
        case HI_UNF_FRAME_PACKING_TYPE_NONE:
            *pFrmType = HI_DRV_FT_NOT_STEREO;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE:
            *pFrmType = HI_DRV_FT_SBS;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM:
            *pFrmType = HI_DRV_FT_TAB;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED:
            *pFrmType = HI_DRV_FT_NOT_STEREO;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING:
            *pFrmType = HI_DRV_FT_FPK;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_3D_TILE:
            *pFrmType = (HI_DRV_FT_FPK + 1);  //HI_DRV_FT_FS;  fix me!
            break;

        default:
            *pFrmType = HI_DRV_FT_BUTT;
            break;
    }
}
static HI_S32 Convert_FrameStructure(HI_UNF_VIDEO_FRAME_INFO_S* pstUnfImage, HI_DRV_VIDEO_FRAME_S* pstDrvImage)
{
    D_VENC_CHECK_PTR(pstUnfImage);
    D_VENC_CHECK_PTR(pstDrvImage);
    memset(pstDrvImage,0,sizeof(HI_DRV_VIDEO_FRAME_S));

    pstDrvImage->u32FrameIndex  = pstUnfImage->u32FrameIndex;
    pstDrvImage->stBufAddr[0].u32PhyAddr_Y = pstUnfImage->stVideoFrameAddr[0].u32YAddr;
    pstDrvImage->stBufAddr[0].u32Stride_Y  = pstUnfImage->stVideoFrameAddr[0].u32YStride;
    pstDrvImage->stBufAddr[0].u32PhyAddr_C = pstUnfImage->stVideoFrameAddr[0].u32CAddr;
    pstDrvImage->stBufAddr[0].u32Stride_C  = pstUnfImage->stVideoFrameAddr[0].u32CStride;
    pstDrvImage->stBufAddr[0].u32PhyAddr_Cr = pstUnfImage->stVideoFrameAddr[0].u32CrAddr;
    pstDrvImage->stBufAddr[0].u32Stride_Cr = pstUnfImage->stVideoFrameAddr[0].u32CrStride;

    pstDrvImage->stBufAddr[1].u32PhyAddr_Y = pstUnfImage->stVideoFrameAddr[1].u32YAddr;
    pstDrvImage->stBufAddr[1].u32Stride_Y  = pstUnfImage->stVideoFrameAddr[1].u32YStride;
    pstDrvImage->stBufAddr[1].u32PhyAddr_C = pstUnfImage->stVideoFrameAddr[1].u32CAddr;
    pstDrvImage->stBufAddr[1].u32Stride_C  = pstUnfImage->stVideoFrameAddr[1].u32CStride;
    pstDrvImage->stBufAddr[1].u32PhyAddr_Cr = pstUnfImage->stVideoFrameAddr[1].u32CrAddr;
    pstDrvImage->stBufAddr[1].u32Stride_Cr = pstUnfImage->stVideoFrameAddr[1].u32CrStride;
    pstDrvImage->u32Width = pstUnfImage->u32Width;
    pstDrvImage->u32Height = pstUnfImage->u32Height;
    pstDrvImage->u32SrcPts = pstUnfImage->u32SrcPts;
    pstDrvImage->u32Pts   = pstUnfImage->u32Pts;
    pstDrvImage->u32AspectWidth       = pstUnfImage->u32AspectWidth;
    pstDrvImage->u32AspectHeight      = pstUnfImage->u32AspectHeight;
    pstDrvImage->u32FrameRate = pstUnfImage->stFrameRate.u32fpsInteger;

    GetPixFormat(pstUnfImage->enVideoFormat, &pstDrvImage->ePixFormat);

    pstDrvImage->bProgressive    = pstUnfImage->bProgressive;

    switch (pstUnfImage->enFieldMode)
    {
        case HI_UNF_VIDEO_FIELD_ALL:
            pstDrvImage->enFieldMode = HI_DRV_FIELD_ALL;
            break;
        case HI_UNF_VIDEO_FIELD_TOP:
            pstDrvImage->enFieldMode = HI_DRV_FIELD_TOP;
            break;
        case HI_UNF_VIDEO_FIELD_BOTTOM:
            pstDrvImage->enFieldMode = HI_DRV_FIELD_BOTTOM;
            break;
        default:
            pstDrvImage->enFieldMode = HI_DRV_FIELD_BUTT;
            break;
    }
    pstDrvImage->bTopFieldFirst = pstUnfImage->bTopFieldFirst;
    pstDrvImage->stDispRect.s32Height = pstUnfImage->u32DisplayHeight;
    pstDrvImage->stDispRect.s32Width  = pstUnfImage->u32DisplayWidth;
    pstDrvImage->stDispRect.s32X      = pstUnfImage->u32DisplayCenterX;
    pstDrvImage->stDispRect.s32Y      = pstUnfImage->u32DisplayCenterY;

    GetFrameType(pstUnfImage->enFramePackingType, &pstDrvImage->eFrmType);

    pstDrvImage->u32Circumrotate = pstUnfImage->u32Circumrotate;
#ifndef VENC_DPT_ONLY
    pstDrvImage->bToFlip_H = pstUnfImage->bHorizontalMirror;
#endif
    pstDrvImage->bToFlip_V = pstUnfImage->bVerticalMirror;
    pstDrvImage->u32ErrorLevel = pstUnfImage->u32ErrorLevel;

    return HI_SUCCESS;
}

static HI_S32 CheckPicSize(HI_U32 Width, HI_U32 Height, HI_BOOL bOMXChn)
{
    HI_U32 MinHeight;
    HI_U32 MaxHeight;
    HI_U32 MinWidth;
    HI_U32 MaxWidth;

    if (bOMXChn)
    {
        MinHeight = HI_OMXVENC_MIN_HEIGTH;
        MinWidth  = HI_OMXVENC_MIN_WIDTH;
        MaxHeight = HI_VENC_MAX_HEIGTH;
        MaxWidth  = HI_VENC_MAX_WIDTH;
    }
    else
    {
        MinHeight = HI_VENC_MIN_HEIGTH;
        MinWidth  = HI_VENC_MIN_WIDTH;
        MaxHeight = HI_VENC_MAX_HEIGTH;
        MaxWidth  = HI_VENC_MAX_WIDTH;
    }

    if ((Height < MinHeight) || (Width < MinWidth))
    {
        HI_ERR_VENC("Picture Width(%u) or Heigth(%u) too small.\n", Width, Height);

        return HI_ERR_VENC_INVALID_PARA;
    }

    if ((Height > MaxHeight) || (Width > MaxWidth))
    {
        HI_ERR_VENC("Picture Width(%u) or Heigth(%u) too large.\n", Width, Height);

        return HI_ERR_VENC_INVALID_PARA;
    }

    if ((Height % HI_VENC_PIC_SZIE_ALIGN) || (Width % HI_VENC_PIC_SZIE_ALIGN))
    {
        HI_ERR_VENC("Picture Width(%u) or Heigth(%u) invalid, should N*%d.\n", Width, Height,
                    HI_VENC_PIC_SZIE_ALIGN);

        return HI_ERR_VENC_INVALID_PARA;
    }

    return HI_SUCCESS;
}
static HI_S32 CheckVencType(HI_UNF_VCODEC_TYPE_E VencType)
{
    HI_BOOL flag = HI_FALSE;

    if (VencType == HI_UNF_VCODEC_TYPE_H264)
    {
        flag = HI_TRUE;
    }
#ifdef VENC_SUPPORT_JPGE
    if (VencType == HI_UNF_VCODEC_TYPE_JPEG)
    {
        flag = HI_TRUE;
    }
#endif
#ifdef VENC_SUPPORT_H265
    if (VencType == HI_UNF_VCODEC_TYPE_HEVC)
    {
        flag = HI_TRUE;
    }
#endif

    return (flag == HI_TRUE) ? HI_SUCCESS : HI_FAILURE;
}

static HI_UNF_VCODEC_CAP_LEVEL_E GetMaxCapLevel(HI_VOID)
{
    HI_UNF_VCODEC_CAP_LEVEL_E MaxCapLevel;
    HI_U32 MaxTotalMB;

    MaxTotalMB = (D_VENC_ALIGN_UP(HI_VENC_MAX_WIDTH, 16) >> 4) * (D_VENC_ALIGN_UP(HI_VENC_MAX_HEIGTH, 16) >> 4);

    if (MaxTotalMB > VENC_MB_NUM_720P)
    {
        MaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    }
    else if (MaxTotalMB > VENC_MB_NUM_D1)
    {
        MaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_720P;
    }
    else if (MaxTotalMB > VENC_MB_NUM_CIF)
    {
        MaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
    }
    else
    {
        MaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_QCIF;
    }

    switch (g_vedu_chip_id)
    {
        case 0:
            MaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
            break;

        case 1:
            MaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_720P;
            break;

        default:
            break;
    }

    return MaxCapLevel;
}

static HI_UNF_VCODEC_CAP_LEVEL_E GetMinCapLevel(HI_BOOL bOMXChn)
{
    HI_UNF_VCODEC_CAP_LEVEL_E MinCapLevel;
    HI_U32 MinTotalMB;
    HI_U32 MinWidth;
    HI_U32 MinHeigth;

    if (bOMXChn)
    {
        MinWidth = HI_OMXVENC_MIN_WIDTH;
        MinHeigth = HI_OMXVENC_MIN_HEIGTH;
    }
    else
    {
        MinWidth = HI_VENC_MIN_WIDTH;
        MinHeigth = HI_VENC_MIN_HEIGTH;
    }

    MinTotalMB = (D_VENC_ALIGN_UP(MinWidth, 16) >> 4) * (D_VENC_ALIGN_UP(MinHeigth, 16) >> 4);

    if (MinTotalMB > VENC_MB_NUM_720P)
    {
        MinCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    }
    else if (MinTotalMB > VENC_MB_NUM_D1)
    {
        MinCapLevel = HI_UNF_VCODEC_CAP_LEVEL_720P;
    }
    else if (MinTotalMB > VENC_MB_NUM_CIF)
    {
        MinCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
    }
    else
    {
        MinCapLevel = HI_UNF_VCODEC_CAP_LEVEL_QCIF;
    }

    return MinCapLevel;
}

static HI_S32 GetBufMinSize(HI_UNF_VCODEC_CAP_LEVEL_E enCapLevel, HI_U32 *BufMinSize)
{
    switch (enCapLevel)
    {
        case HI_UNF_VCODEC_CAP_LEVEL_QCIF:
            *BufMinSize = 176 * 144 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_CIF:
            *BufMinSize = 352 * 288 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_D1:
            *BufMinSize = 720 * 576 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_720P:
            *BufMinSize = 1280 * 720 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_FULLHD:
            *BufMinSize = 1920 * 1080 * 2;
            break;

        default:
            HI_ERR_VENC("enCapLevel(%d) invalid.\n", enCapLevel);

            return HI_ERR_VENC_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static HI_S32 CheckCaplevel(const HI_UNF_VENC_CHN_ATTR_S *pstAttr, HI_U32 *BufMinSize, HI_BOOL bOMXChn)
{
    HI_U32 TotalMB;
    HI_UNF_VCODEC_CAP_LEVEL_E MinCapLevel,MaxCapLevel;

    TotalMB = (D_VENC_ALIGN_UP(pstAttr->u32Height, 16) >> 4) * (D_VENC_ALIGN_UP(pstAttr->u32Width, 16) >> 4);
    MinCapLevel = GetMinCapLevel(bOMXChn);
    MaxCapLevel = GetMaxCapLevel();

    if ((pstAttr->enCapLevel > MaxCapLevel) || (pstAttr->enCapLevel < MinCapLevel))
    {
        HI_ERR_VENC("enCapLevel(%d) invalid,MaxCapLevel = %d,MinCapLevel = %d\n", pstAttr->enCapLevel,MaxCapLevel,MinCapLevel);

        return HI_ERR_VENC_NOT_SUPPORT;
    }

    switch (pstAttr->enCapLevel)
    {
        case HI_UNF_VCODEC_CAP_LEVEL_QCIF:
            if (TotalMB > VENC_MB_NUM_QCIF)
            {
                HI_ERR_VENC("Picture Width(%u) or Heigth(%u) too large for enCapLevel(%d) .\n",
                            pstAttr->u32Width, pstAttr->u32Height, pstAttr->enCapLevel);

                return HI_ERR_VENC_INVALID_PARA;
            }

            *BufMinSize = 176 * 144 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_CIF:
            if (TotalMB > VENC_MB_NUM_CIF)
            {
                HI_ERR_VENC("Picture Width(%u) or Heigth(%u) too large for enCapLevel(%d) .\n",
                            pstAttr->u32Width, pstAttr->u32Height, pstAttr->enCapLevel);

                return HI_ERR_VENC_INVALID_PARA;
            }

            *BufMinSize = 352 * 288 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_D1:
            if (TotalMB > VENC_MB_NUM_D1)
            {
                HI_ERR_VENC("Picture Width(%u) or Heigth(%u) too large for enCapLevel(%d) .\n",
                            pstAttr->u32Width, pstAttr->u32Height, pstAttr->enCapLevel);

                return HI_ERR_VENC_INVALID_PARA;
            }

            *BufMinSize = 720 * 576 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_720P:
            if (TotalMB > VENC_MB_NUM_720P)
            {
                HI_ERR_VENC("Picture Width(%u) or Heigth(%u) too large for enCapLevel(%d) .\n",
                            pstAttr->u32Width, pstAttr->u32Height, pstAttr->enCapLevel);

                return HI_ERR_VENC_INVALID_PARA;
            }

            *BufMinSize = 1280 * 720 * 2;
            break;

        case HI_UNF_VCODEC_CAP_LEVEL_FULLHD:
            if (TotalMB > VENC_MB_NUM_FULLHD)
            {
                HI_ERR_VENC("Picture Width(%u) or Heigth(%u) too large for enCapLevel(%d) .\n",
                            pstAttr->u32Width, pstAttr->u32Height, pstAttr->enCapLevel);

                return HI_ERR_VENC_INVALID_PARA;
            }

            *BufMinSize = 1920 * 1080 * 2;
            break;

        default:
            HI_ERR_VENC("enCapLevel(%d) invalid.\n", pstAttr->enCapLevel);

            return HI_ERR_VENC_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static HI_S32 CheckCommonAttr(const HI_UNF_VENC_CHN_ATTR_S* pstAttr, HI_U32 u32BufMinSize)
{
    if ((pstAttr->u32StrmBufSize < u32BufMinSize)
        || (pstAttr->u32StrmBufSize > HI_VENC_MAX_BUF_SIZE))
    {
        HI_ERR_VENC("u32StrmBufSize(%u) invalid.u32StrmBufSize should larger than %d and smaller than %d\n",
                     pstAttr->u32StrmBufSize, u32BufMinSize, HI_VENC_MAX_BUF_SIZE);

        return HI_ERR_VENC_INVALID_PARA;
    }

    if ((pstAttr->u32InputFrmRate < HI_VENC_MIN_fps)
        || (pstAttr->u32InputFrmRate > HI_VENC_MAX_fps))
    {
        HI_ERR_VENC("u32InputFrmRate(%u) is invalid.\n", pstAttr->u32InputFrmRate);

        return HI_ERR_VENC_INVALID_PARA;
    }

    if ((pstAttr->u32TargetFrmRate < HI_VENC_MIN_fps)
        || (pstAttr->u32TargetFrmRate > pstAttr->u32InputFrmRate))
    {
        HI_ERR_VENC("u32TargetFrmRate(%u) is invalid, should 1~inputFrameRate.\n", pstAttr->u32TargetFrmRate);

        return HI_ERR_VENC_INVALID_PARA;
    }

    if (pstAttr->u8Priority >= HI_VENC_MAX_PRIORITY )
    {
        HI_ERR_VENC("u8Priority(%u) is invalid, should < u8MaxPriority(%u).\n", pstAttr->u8Priority , HI_VENC_MAX_PRIORITY);

        return HI_ERR_VENC_INVALID_PARA;
    }

    if (!((HI_TRUE == pstAttr->bQuickEncode) || (HI_FALSE == pstAttr->bQuickEncode)))
    {
        HI_ERR_VENC("bQuickEncode(%u) is invalid.\n", pstAttr->bQuickEncode);

        return HI_ERR_VENC_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static HI_S32 CheckPrivateAttr(const HI_UNF_VENC_CHN_ATTR_S *pstAttr)
{
#ifdef VENC_SUPPORT_JPGE
    if (HI_UNF_VCODEC_TYPE_JPEG == pstAttr->enVencType)
    {
        if (pstAttr->u32RotationAngle != 0)
        {
            HI_ERR_VENC("u32RotationAngle(%u)of JPEG Encoder only support 0 now.\n", pstAttr->u32RotationAngle);

            return HI_ERR_VENC_INVALID_PARA;
        }

        if ((pstAttr->u32Qlevel < HI_VENC_MIN_Q_VALUE) || (pstAttr->u32Qlevel > HI_VENC_MAX_Q_VALUE))
        {
            HI_ERR_VENC("u32Qlevel(%u) is invalid.\n", pstAttr->u32Qlevel);

            return HI_ERR_VENC_INVALID_PARA;
        }
    }
    else
#endif
    {
        if (pstAttr->u32RotationAngle != 0)
        {
            HI_ERR_VENC("u32RotationAngle(%u)of H264 Encoder only support 0 now.\n", pstAttr->u32RotationAngle);

            return HI_ERR_VENC_NOT_SUPPORT;
        }

        if (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264)
        {
            if (pstAttr->enVencProfile >= HI_UNF_H264_PROFILE_BUTT)
            {
                HI_ERR_VENC("enVencProfile(%d) invalid.\n", pstAttr->enVencProfile);

                return HI_ERR_VENC_INVALID_PARA;
            }

            if (pstAttr->enVencProfile == HI_UNF_H264_PROFILE_EXTENDED)
            {
                HI_ERR_VENC("enVencProfile(%d) not support.\n", pstAttr->enVencProfile);

                return HI_ERR_VENC_NOT_SUPPORT;
            }
        }

        if ((pstAttr->u32TargetBitRate < HI_VENC_MIN_bps) || (pstAttr->u32TargetBitRate > HI_VENC_MAX_bps))
        {
            HI_ERR_VENC("u32TargetBitRate(%u) is invalid.\n", pstAttr->u32TargetBitRate);

            return HI_ERR_VENC_INVALID_PARA;
        }

        if (pstAttr->u32Gop < HI_VENC_MIN_GOP)
        {
            HI_ERR_VENC("u32Gop(%u) is invalid, should > %u.\n", pstAttr->u32Gop, HI_VENC_MIN_GOP);

            return HI_ERR_VENC_INVALID_PARA;
        }

        if (pstAttr->u32MinQp > HI_VENC_MAX_QP)
        {
            HI_ERR_VENC("u32MinQp(%u) is invalid, should < %u.\n", pstAttr->u32MinQp, HI_VENC_MAX_QP);

            return HI_ERR_VENC_INVALID_PARA;
        }

        if (pstAttr->u32MaxQp > HI_VENC_MAX_QP)
        {
            HI_ERR_VENC("u32MaxQp(%u) is invalid, should < %u.\n", pstAttr->u32MaxQp, HI_VENC_MAX_QP);

            return HI_ERR_VENC_INVALID_PARA;
        }

        if (pstAttr->u32MinQp >= pstAttr->u32MaxQp)
        {
            HI_ERR_VENC("u32MinQp(%u) is invalid, should < u32MaxQp(%u).\n", pstAttr->u32MinQp , pstAttr->u32MaxQp);

            return HI_ERR_VENC_INVALID_PARA;
        }

        if (!((HI_TRUE == pstAttr->bSlcSplitEn) || (HI_FALSE == pstAttr->bSlcSplitEn)))
        {
            HI_ERR_VENC("bSlcSplitEn(%u) is invalid.\n", pstAttr->bSlcSplitEn);

            return HI_ERR_VENC_INVALID_PARA;
        }

        if (pstAttr->u32DriftRateThr != (-1))
        {
            if (pstAttr->u32DriftRateThr > HI_VENC_MAX_RcThr)
            {
                HI_ERR_VENC("u32DriftRateThr(%u) is invalid,should smaller than %d\n", pstAttr->u32DriftRateThr, HI_VENC_MAX_RcThr);

                return HI_ERR_VENC_INVALID_PARA;
            }
        }
    }

    return HI_SUCCESS;
}

static HI_S32 CheckConfig(const HI_UNF_VENC_CHN_ATTR_S *pstAttr, HI_BOOL bOMXChn)
{
    HI_U32 u32BufMinSize = 0;
    HI_S32 Ret;

    if (CheckVencType(pstAttr->enVencType) != HI_SUCCESS)
    {
        HI_ERR_VENC("NOT support Type(%d) VENC channel.\n", pstAttr->enVencType);
        return HI_ERR_VENC_NOT_SUPPORT;
    }

    Ret = CheckPicSize(pstAttr->u32Width, pstAttr->u32Height, bOMXChn);
    if(Ret != HI_SUCCESS)
    {
        return Ret;
    }

    Ret = CheckCaplevel(pstAttr, &u32BufMinSize, bOMXChn);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    Ret = CheckCommonAttr(pstAttr, u32BufMinSize);
    if(Ret != HI_SUCCESS)
    {
        return Ret;
    }

    Ret = CheckPrivateAttr(pstAttr);
    if(Ret != HI_SUCCESS)
    {
        return Ret;
    }

    if (pstAttr->bSlcSplitEn)
    {
        if ((pstAttr->u32SplitSize > HI_VENC_MAX_SPLIT_BYTE_SIZE) || (pstAttr->u32SplitSize < HI_VENC_MIN_SPLIT_BYTE_SIZE))
        {
            HI_ERR_VENC("u32SplitSize(%u) is invalid.Should < %u && > %u .\n", pstAttr->u32SplitSize,
                        HI_VENC_MAX_SPLIT_BYTE_SIZE,HI_VENC_MIN_SPLIT_BYTE_SIZE);

            return HI_ERR_VENC_INVALID_PARA;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 checkAttachModule(HI_MOD_ID_E enModId)
{
    HI_BOOL flag = HI_FALSE;

#ifdef VENC_SUPPORT_ATTACH_VI
    if (enModId == HI_ID_VI)
    {
        flag = HI_TRUE;
    }
#endif
#ifdef VENC_SUPPORT_ATTACH_VO
    if (enModId == HI_ID_VO)
    {
        flag = HI_TRUE;
    }
#endif
#ifdef VENC_SUPPORT_ATTACH_CAST
    if (enModId == HI_ID_DISP)
    {
        flag = HI_TRUE;
    }
#endif

    return (flag == HI_TRUE) ? HI_SUCCESS : HI_FAILURE;
}

static HI_VOID GetVideoFormat(HI_DRV_PIX_FORMAT_E PixFormat, HI_UNF_VIDEO_FORMAT_E *pVideoFormat)
{
    switch (PixFormat)
    {
        case HI_DRV_PIX_FMT_NV61_2X1:
            *pVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_422 ;
            break;

        case HI_DRV_PIX_FMT_NV12:
            *pVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_420_UV;
            break;

        case HI_DRV_PIX_FMT_NV21:
            *pVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_420 ;
            break;

        case HI_DRV_PIX_FMT_NV80:
            *pVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_400;
            break;

        case HI_DRV_PIX_FMT_NV12_411:
            *pVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_411;
            break;

        case HI_DRV_PIX_FMT_NV61:
            *pVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_422_1X2;
            break;

        case HI_DRV_PIX_FMT_NV42:
            *pVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_444;
            break;

        case HI_DRV_PIX_FMT_UYVY:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PACKAGE_UYVY;
            break;

        case HI_DRV_PIX_FMT_YUYV:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PACKAGE_YUYV;
            break;

        case HI_DRV_PIX_FMT_YVYU:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PACKAGE_YVYU;
            break;

        case HI_DRV_PIX_FMT_YUV400:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_400;
            break;

        case HI_DRV_PIX_FMT_YUV411:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_411;
            break;

        case HI_DRV_PIX_FMT_YUV420p:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_420;
            break;

        case HI_DRV_PIX_FMT_YUV422_1X2:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_422_1X2;
            break;

        case HI_DRV_PIX_FMT_YUV422_2X1:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_422_2X1;
            break;

        case HI_DRV_PIX_FMT_YUV_444:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_444;
            break;

        case HI_DRV_PIX_FMT_YUV410p:
            *pVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_410;
            break;

        default:
            *pVideoFormat = HI_UNF_FORMAT_YUV_BUTT;
            break;
    }
}
static HI_S32 Convert_DrvFrameStructure(HI_DRV_VIDEO_FRAME_S* pstDrvImage, HI_UNF_VIDEO_FRAME_INFO_S* pstUnfImage)
{
    D_VENC_CHECK_PTR(pstUnfImage);
    D_VENC_CHECK_PTR(pstDrvImage);
   memset(pstUnfImage, 0, sizeof(HI_UNF_VIDEO_FRAME_INFO_S));

    pstUnfImage->u32FrameIndex  = pstDrvImage->u32FrameIndex;
    pstUnfImage->stVideoFrameAddr[0].u32YAddr = pstDrvImage->stBufAddr[0].u32PhyAddr_Y ;
    pstUnfImage->stVideoFrameAddr[0].u32YStride = pstDrvImage->stBufAddr[0].u32Stride_Y ;
    pstUnfImage->stVideoFrameAddr[0].u32CAddr = pstDrvImage->stBufAddr[0].u32PhyAddr_C ;
    pstUnfImage->stVideoFrameAddr[0].u32CStride = pstDrvImage->stBufAddr[0].u32Stride_C ;
    pstUnfImage->stVideoFrameAddr[0].u32CrAddr = pstDrvImage->stBufAddr[0].u32PhyAddr_Cr;
    pstUnfImage->stVideoFrameAddr[0].u32CrStride = pstDrvImage->stBufAddr[0].u32Stride_Cr ;

    pstUnfImage->stVideoFrameAddr[1].u32YAddr = pstDrvImage->stBufAddr[1].u32PhyAddr_Y ;
    pstUnfImage->stVideoFrameAddr[1].u32YStride = pstDrvImage->stBufAddr[1].u32Stride_Y ;
    pstUnfImage->stVideoFrameAddr[1].u32CAddr = pstDrvImage->stBufAddr[1].u32PhyAddr_C ;
    pstUnfImage->stVideoFrameAddr[1].u32CStride = pstDrvImage->stBufAddr[1].u32Stride_C ;
    pstUnfImage->stVideoFrameAddr[1].u32CrAddr = pstDrvImage->stBufAddr[1].u32PhyAddr_Cr;
    pstUnfImage->stVideoFrameAddr[1].u32CrStride = pstDrvImage->stBufAddr[1].u32Stride_Cr ;

    pstUnfImage->u32Width = pstDrvImage->u32Width;
    pstUnfImage->u32Height = pstDrvImage->u32Height;
    pstUnfImage->u32SrcPts = pstDrvImage->u32SrcPts;
    pstUnfImage->u32Pts = pstDrvImage->u32Pts ;
    pstUnfImage->u32AspectWidth = pstDrvImage->u32AspectWidth;
    pstUnfImage->u32AspectHeight = pstDrvImage->u32AspectHeight;
    pstUnfImage->stFrameRate.u32fpsInteger = pstDrvImage->u32FrameRate;

    GetVideoFormat(pstDrvImage->ePixFormat, &pstUnfImage->enVideoFormat);

    pstUnfImage->bProgressive = pstDrvImage->bProgressive;

    switch (pstDrvImage->enFieldMode)
    {
        case HI_DRV_FIELD_ALL:
            pstUnfImage->enFieldMode = HI_UNF_VIDEO_FIELD_ALL;
            break;
        case HI_DRV_FIELD_TOP:
            pstUnfImage->enFieldMode = HI_UNF_VIDEO_FIELD_TOP;
            break;
        case HI_DRV_FIELD_BOTTOM:
            pstUnfImage->enFieldMode = HI_UNF_VIDEO_FIELD_BOTTOM;
            break;
        default:
            pstUnfImage->enFieldMode = HI_UNF_VIDEO_FIELD_BUTT;
            break;
    }
    pstUnfImage->bTopFieldFirst = pstDrvImage->bTopFieldFirst;
    pstUnfImage->u32DisplayHeight = pstDrvImage->stDispRect.s32Height;
    pstUnfImage->u32DisplayWidth = pstDrvImage->stDispRect.s32Width;
    pstUnfImage->u32DisplayCenterX = pstDrvImage->stDispRect.s32X;
    pstUnfImage->u32DisplayCenterY = pstDrvImage->stDispRect.s32Y;

    switch (pstDrvImage->eFrmType)
    {
        case HI_DRV_FT_NOT_STEREO:
            pstUnfImage->enFramePackingType = HI_UNF_FRAME_PACKING_TYPE_NONE;
            break;

        case HI_DRV_FT_SBS:
            pstUnfImage->enFramePackingType = HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE;
            break;

        case HI_DRV_FT_TAB:
            pstUnfImage->enFramePackingType = HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM;
            break;

        case HI_DRV_FT_FPK:
            pstUnfImage->enFramePackingType = HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING;
            break;

        case (HI_DRV_FRAME_TYPE_E)(HI_DRV_FT_FPK+1):
            pstUnfImage->enFramePackingType = HI_UNF_FRAME_PACKING_TYPE_3D_TILE;
            break;

        default:
            pstUnfImage->enFramePackingType = HI_UNF_FRAME_PACKING_TYPE_BUTT;  //QS
            break;
    }

    pstUnfImage->u32Circumrotate = pstDrvImage->u32Circumrotate;
#ifdef VENC_DPT_ONLY
    pstUnfImage->bHorizontalMirror = 0;//pstDrvImage->bToFlip_H;
#else
    pstUnfImage->bHorizontalMirror = pstDrvImage->bToFlip_H;
#endif
    pstUnfImage->bVerticalMirror = pstDrvImage->bToFlip_V;
    pstUnfImage->u32ErrorLevel = pstDrvImage->u32ErrorLevel;

    return HI_SUCCESS;
}

HI_VOID VENC_DRV_InitEvent(HI_VOID)
{
    HI_U32 i;

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        //init_waitqueue_head(&g_astVencWait[i]);
        VENC_DRV_OsalInitEvent(&g_VencWait_Stream[i], 0);
        spin_lock_init(&g_SendFrame_Lock[i]);
    }

    init_waitqueue_head(&gEncodeFrame);
    VENC_DRV_OsalInitEvent(&g_VENC_Event_stream, 0);

    gencodeframe = 0;
    g_vedu_chip_id = 2;
}

HI_VOID VENC_DRV_BoardInit(HI_VOID)
{
    /* open vedu clock  && set clock freq*/
    VENC_PDT_OpenHardware();
    /* cancel reset */
    VENC_PDT_ResetHardware();
}

HI_VOID VENC_DRV_BoardDeinit(HI_VOID)
{
    /* close vedu clock */
    VENC_PDT_CloseHardware();
    /* reset */
    VENC_PDT_ResetHardware();
}

static HI_VOID VENC_DRV_SetCfgInfo(HI_UNF_VENC_CHN_ATTR_S *pVencUnfAttrs, VeduEfl_EncCfg_S *pstEncCfg)
{
    switch (pVencUnfAttrs->enVencType)
    {
#ifdef VENC_SUPPORT_H265
        case HI_UNF_VCODEC_TYPE_HEVC:
            pstEncCfg->Protocol = VEDU_H265;
            pstEncCfg->Profile  = (HI_U32)pVencUnfAttrs->enVencProfile;
            pstEncCfg->Gop      = pVencUnfAttrs->u32Gop;
            pstEncCfg->QLevel   = 0;
            break;
#endif
        case HI_UNF_VCODEC_TYPE_H264:
            pstEncCfg->Protocol = VEDU_H264;
            pstEncCfg->Profile  = (HI_U32)pVencUnfAttrs->enVencProfile;
            pstEncCfg->Gop      = pVencUnfAttrs->u32Gop;
            pstEncCfg->QLevel   = 0;
            break;
     #ifdef VENC_SUPPORT_JPGE
        case HI_UNF_VCODEC_TYPE_JPEG:
            pstEncCfg->Protocol = VEDU_JPGE;
            pstEncCfg->Profile  = VEDU_H264_PROFILE_BUTT;
            pstEncCfg->QLevel   = pVencUnfAttrs->u32Qlevel;
            pstEncCfg->Gop      = 0;
            break;
     #endif
        default:
            pstEncCfg->Protocol = VEDU_H264;
            break;
    }

}

static HI_VOID VENC_DRV_GetRCSkipFrmEn(VeduEfl_EncCfg_S *pstEncCfg)
{
    pstEncCfg->bRCSkipFrmEn = (pstEncCfg->DriftRCThr <= 100) ? HI_TRUE : HI_FALSE;
}

static HI_VOID VENC_DRV_GetSplitSize(VeduEfl_EncCfg_S *pstEncCfg, HI_U32 SplitSize)
{
    pstEncCfg->SplitSize = (pstEncCfg->SlcSplitEn) ? SplitSize : 0;
}

HI_S32 VENC_DRV_CreateChn(VeduEfl_EncPara_S** phVencChn, venc_chan_cfg *pstAttr,
                      VENC_CHN_INFO_S *pstVeInfo,HI_BOOL bOMXChn, struct file  *pfile)
{
    HI_S32 s32Ret = 0, i = 0;
    VeduEfl_EncCfg_S EncCfg;
    HI_HANDLE hJpgeChn = HI_INVALID_HANDLE;
    HI_UNF_VENC_CHN_ATTR_S* pVencUnfAttrs;

    VeduEfl_EncPara_S *pstEncChnPara = HI_NULL;
    VeduEfl_RcAttr_S RcAttrCfg;
    HI_CHAR YUVFileName[64] = {""};
    HI_CHAR StreamFileName[64] = {""};
    HI_U32 SlcSize = 0;

#ifdef VENC_SUPPORT_JPGE
    Jpge_EncCfg_S    JpgeEncCfg;
    memset(&JpgeEncCfg, 0, sizeof(Jpge_EncCfg_S));
#endif

    D_VENC_CHECK_PTR(phVencChn);
    D_VENC_CHECK_PTR(pstAttr);
    D_VENC_CHECK_PTR(pstVeInfo);

    pVencUnfAttrs = &pstAttr->VencUnfAttr;
    s32Ret = CheckConfig(pVencUnfAttrs, bOMXChn);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (g_stVencChn[i].hVEncHandle == NULL)
        {
            break;
        }
    }

    if (i == HI_VENC_MAX_CHN)
    {
        HI_ERR_VENC("channal create err! \n");
        return HI_ERR_VENC_CREATE_ERR;
    }

    VENC_DRV_SetCfgInfo(pVencUnfAttrs, &EncCfg);

    EncCfg.bAutoRequestIfrm = pstAttr->bAutoRequestIFrm;
    EncCfg.bPrependSpsPps = pstAttr->bPrependSpsPps;
    EncCfg.CapLevel      = pVencUnfAttrs->enCapLevel;
    EncCfg.FrameWidth    = pVencUnfAttrs->u32Width;
    EncCfg.FrameHeight   = pVencUnfAttrs->u32Height;
    EncCfg.RotationAngle = pVencUnfAttrs->u32RotationAngle;
    EncCfg.Priority      = pVencUnfAttrs->u8Priority;
    EncCfg.streamBufSize = pVencUnfAttrs->u32StrmBufSize;
    EncCfg.QuickEncode   = pVencUnfAttrs->bQuickEncode;
    EncCfg.SlcSplitEn    = (HI_TRUE == pVencUnfAttrs->bSlcSplitEn) ? 1 : 0;
    EncCfg.DriftRCThr    = pVencUnfAttrs->u32DriftRateThr;

    VENC_DRV_GetRCSkipFrmEn(&EncCfg);

    EncCfg.bOMXChn  = bOMXChn;
    s32Ret = VENC_DRV_EflCreateVenc(phVencChn, &EncCfg);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    pstEncChnPara = (VeduEfl_EncPara_S*)(*phVencChn);

    SlcSize = STRM_CalSlcSize(pstEncChnPara->hStrmMng, EncCfg.Protocol, EncCfg.FrameHeight, pVencUnfAttrs->u32SplitSize);

    if ((EncCfg.SlcSplitEn) && (SlcSize == 0xffffffff))
    {
        HI_ERR_VENC("Get slice size fail!");
        goto create_error_1;
    }

    VENC_DRV_GetSplitSize(&EncCfg, SlcSize);

#ifdef VENC_SUPPORT_JPGE
    if (EncCfg.Protocol == VEDU_JPGE)
    {
        if (pJpgeFunc == HI_NULL)
        {
            HI_ERR_VENC("pJpgeFunc is NULL!\n");
            goto create_error_1;
        }
        JpgeEncCfg.FrameWidth  = pVencUnfAttrs->u32Width;
        JpgeEncCfg.FrameHeight = pVencUnfAttrs->u32Height;
        JpgeEncCfg.SlcSplitEn  = 0;                         //EncCfg.SlcSplitEn;
        JpgeEncCfg.SplitSize   = EncCfg.SplitSize;
        JpgeEncCfg.Qlevel      = pVencUnfAttrs->u32Qlevel;

        s32Ret = pJpgeFunc->pfnJpgeCreateChn(&hJpgeChn, &JpgeEncCfg);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_VENC("pfnJpgeCreateChn Failed!\n");
            s32Ret = HI_ERR_VENC_CREATE_ERR;
            goto create_error_1;
        }

        s32Ret = VENC_DRV_EflAllocBuf2Jpge(pstEncChnPara, EncCfg.CapLevel);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_VENC("pfnJpgeCreateChn Failed!\n");
            s32Ret = HI_ERR_VENC_CREATE_ERR;
            goto create_error_2;
        }
    }
#endif

    RcAttrCfg.BitRate    = pVencUnfAttrs->u32TargetBitRate;
    RcAttrCfg.InFrmRate  = pVencUnfAttrs->u32InputFrmRate;
    RcAttrCfg.OutFrmRate = pVencUnfAttrs->u32TargetFrmRate;
    RcAttrCfg.MaxQp      = pVencUnfAttrs->u32MaxQp;
    RcAttrCfg.MinQp      = pVencUnfAttrs->u32MinQp;

    pstEncChnPara->CurStrmBufSize = RcAttrCfg.BitRate / RcAttrCfg.OutFrmRate * BUF_SIZE_MULT_CHECK_INIT;
    if (pstEncChnPara->CurStrmBufSize > (pVencUnfAttrs->u32StrmBufSize - 64) * 8)
    {
         pstEncChnPara->CurStrmBufSize = (pVencUnfAttrs->u32StrmBufSize - 64) * 8;
    }
    pstEncChnPara->CurStrmBufSize = D_VENC_ALIGN_UP(pstEncChnPara->CurStrmBufSize / 8, VEDU_MMZ_ALIGN);
    pstEncChnPara->stHal.SplitSize  = EncCfg.SplitSize;

    s32Ret = VENC_DRV_EflRcAttrInit(pstEncChnPara, &RcAttrCfg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("config venc err:%#x.\n", s32Ret);
        s32Ret = HI_ERR_VENC_INVALID_PARA;
        goto create_error_3;
    }

    /*creat one proc file*/
    s32Ret = VENC_DRV_ProcAdd(pstEncChnPara, i);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("venc_ProcAdd failed, ret = 0x%08x\n", s32Ret);
        s32Ret = HI_ERR_VENC_CREATE_ERR;
        goto create_error_3;
    }

    pstVeInfo->handle            = g_stVencChn[i].hUsrHandle;//*phVencChn;
    pstVeInfo->u32StrmBufPhyAddr = pstEncChnPara->stHal.StrmBufAddr;
    pstVeInfo->u32BufSize        = pstEncChnPara->stHal.StrmBufSize;
    pstVeInfo->u32SliceBufPhyAddr = pstEncChnPara->stHal.SliceBuf.u32StartPhyAddr;
    pstVeInfo->u32StrmBufPhyAddrJpeg = pstEncChnPara->JpgMMZBuf.u32StartPhyAddr;

    pstVeInfo->u32BufSizeJpeg    = pstEncChnPara->JpgMMZBuf.u32Size;
    pstVeInfo->u32Protocol       = pstEncChnPara->Protocol;
    g_stVencChn[i].StrmBufAddr   = pstEncChnPara->stHal.StrmBufAddr;
    g_stVencChn[i].StrmBufSize   = pstEncChnPara->stHal.StrmBufSize;
    g_stVencChn[i].hVEncHandle   = pstEncChnPara;
    g_stVencChn[i].hSource       = HI_INVALID_HANDLE;
    g_stVencChn[i].pWhichFile    = pfile;
    g_stVencChn[i].u32SliceSize            = EncCfg.SplitSize;
    g_stVencChn[i].u32FrameNumLastInput    = 0;
    g_stVencChn[i].u32FrameNumLastEncoded  = 0;
    g_stVencChn[i].u32TotalByteLastEncoded = 0;
    g_stVencChn[i].u32LastSecInputFps      = 0;
    g_stVencChn[i].u32LastSecEncodedFps    = 0;
    g_stVencChn[i].u32LastSecKbps          = 0;
    g_stVencChn[i].u32LastSecTryNum        = 0;
    g_stVencChn[i].u32LastTryNumTotal      = 0;
    g_stVencChn[i].u32LastSecOKNum         = 0;
    g_stVencChn[i].u32LastOKNumTotal       = 0;
    g_stVencChn[i].u32LastSecPutNum        = 0;
    g_stVencChn[i].u32LastPutNumTotal      = 0;
    g_stVencChn[i].bFrameBufMng            = HI_TRUE;
    g_stVencChn[i].bEnable                 = HI_FALSE;
    g_stVencChn[i].enSrcModId              = HI_ID_BUTT;
    g_stVencChn[i].bOMXChn                 = bOMXChn;
    g_stVencChn[i].stProcWrite.bFrameModeRun     = HI_FALSE;
    g_stVencChn[i].stProcWrite.bTimeModeRun      = HI_FALSE;
    g_stVencChn[i].stProcWrite.bSaveYUVFileRun   = HI_FALSE;
    g_stVencChn[i].stProcWrite.u32FrameModeCount = 0;
    g_stVencChn[i].stProcWrite.fpSaveFile        = HI_NULL;
    g_stVencChn[i].hJPGE                         = hJpgeChn;

    g_stVencChn[i].stChnUserCfg  = *pVencUnfAttrs;
#ifdef VENC_SUPPORT_JPGE
    if (EncCfg.Protocol == VEDU_JPGE)
    {
        g_stVencChn[i].stChnUserCfg.u32Gop = 0;
        g_stVencChn[i].stChnUserCfg.u32TargetBitRate = 0;
        g_stVencChn[i].stChnUserCfg.u32MaxQp = 0;
        g_stVencChn[i].stChnUserCfg.u32MinQp = 0;
        g_stVencChn[i].stChnUserCfg.enVencProfile = HI_UNF_H264_PROFILE_BUTT;
    }
    else
#endif
    {
        g_stVencChn[i].stChnUserCfg.u32Qlevel = 0;
    }

    memset(&g_stKernelOmxmmz[i],0,sizeof(VENC_BUFFER_S)*OMX_OUTPUT_PORT_BUFFER_MAX);

    s32Ret = HI_OSAL_Snprintf(YUVFileName, sizeof(YUVFileName), "venc_proc_chn%02d.yuv", i);
    if (0 == s32Ret)
    {
        HI_ERR_VENC("HI_OSAL_Snprintf failed!\n");
    }
    memcpy(g_stVencChn[i].stProcWrite.YUVFileName, YUVFileName, 64);
    s32Ret = HI_OSAL_Snprintf(StreamFileName, sizeof(StreamFileName), "venc_proc_chn%02d.h264", i);
    if (0 == s32Ret)
    {
        HI_ERR_VENC("HI_OSAL_Snprintf failed!\n");
    }
    memcpy(g_stVencChn[i].stProcWrite.StreamFileName, StreamFileName, 64);
    HI_INFO_VENC("create OK, Chn:%d/%#x.\n", i, g_stVencChn[i].hVEncHandle);

#ifdef __VENC_RC_DBG__

    g_stVencChn[i].stProcWrite.fpSaveFile = VENC_DRV_OsalFopen("/mnt/yuv_stream/venc_rc_dbg.h264",  O_RDWR | O_CREAT | O_APPEND, 0);
    if (HI_NULL == g_stVencChn[i].stProcWrite.fpSaveFile)
    {
        HI_ERR_VENC("Can not create file.\n");
        g_stVencChn[i].stProcWrite.bTimeModeRun = HI_FALSE;
        return HI_FAILURE;
    }
    g_stVencChn[i].stProcWrite.bTimeModeRun = HI_TRUE;
#endif

    return HI_SUCCESS;

create_error_3:
#ifdef VENC_SUPPORT_JPGE
    if (EncCfg.Protocol == VEDU_JPGE)
    {
        VENC_DRV_EflFreeBuf2Jpge(pstEncChnPara);
    }

create_error_2:
    if (EncCfg.Protocol == VEDU_JPGE)
    {
        if (pJpgeFunc != HI_NULL)
        {
            pJpgeFunc->pfnJpgeDestroyChn(hJpgeChn);
        }
    }
#endif
create_error_1:
    VENC_DRV_EflDestroyVenc(pstEncChnPara);

    return s32Ret;

}

HI_S32 VENC_DRV_DestroyChn( VeduEfl_EncPara_S* hVencChn)
{
    HI_S32 s32Ret   = 0;
    HI_U32 u32VeChn = 0;
    OPTM_VENC_CHN_S* pstVenc;
    unsigned long flags;
    //VI_EXPORT_FUNC_S *pViFunc = HI_NULL;
    VeduEfl_EncPara_S*  pstEncChnPara;
    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);

    spin_lock_irqsave(&g_SendFrame_Lock[u32VeChn], flags);
    pstVenc = &g_stVencChn[u32VeChn];
    pstEncChnPara = g_stVencChn[u32VeChn].hVEncHandle;
    spin_unlock_irqrestore(&g_SendFrame_Lock[u32VeChn], flags);
    //VENC must be stop working
    if (pstVenc->bEnable)
    {
        HI_WARN_VENC("Error:Destroy channel when VENC is run.\n");
        VENC_DRV_EflStopVenc(pstEncChnPara);
        VENC_DRV_OsalGiveEvent(&g_VencWait_Stream[u32VeChn]);
    }

#ifdef __VENC_RC_DBG__
    g_stVencChn[u32VeChn].stProcWrite.bTimeModeRun = HI_FALSE;
    VENC_DRV_OsalFclose(g_stVencChn[u32VeChn].stProcWrite.fpSaveFile);

#endif

    switch (pstVenc->enSrcModId)
    {
        case HI_ID_DISP:
        {
            pstEncChnPara->stSrcInfo.pfDetachFunc(pstVenc->hSource, pstVenc->hUsrHandle);
        }
        break;
        default:
            break;
    }
    /**/
    VENC_DRV_ProcDel(pstEncChnPara, u32VeChn);

#ifdef VENC_SUPPORT_JPGE
    if ((HI_INVALID_HANDLE != g_stVencChn[u32VeChn].hJPGE) && (pJpgeFunc != HI_NULL))
    {
        s32Ret = pJpgeFunc->pfnJpgeDestroyChn(g_stVencChn[u32VeChn].hJPGE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_VENC("Error:Destroy JGPE ERR.\n");
        }

        VENC_DRV_EflFreeBuf2Jpge(pstEncChnPara);
    }
#endif

    s32Ret = VENC_DRV_EflDestroyVenc(pstEncChnPara);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

#if 0
    if (g_stVencChn[s32VeChn].hSource != HI_INVALID_HANDLE)
    {

        if (HI_ID_VI == g_stVencChn[s32VeChn].enSrcModId)
        {
            HI_DRV_MODULE_GetFunction(HI_ID_VI, (HI_VOID**)&pViFunc);
            if (HI_NULL != pViFunc)
            {
                s32Ret = pViFunc->pfnViPutUsrID(pstVenc->hSource & 0xff, pstVenc->u32SrcUser);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_VENC("ViuPutUsrID failed, Ret=%#x.\n", s32Ret);
                    return s32Ret;
                }
            }
        }
    }
#endif

    spin_lock_irqsave(&g_SendFrame_Lock[u32VeChn], flags);
    g_stVencChn[u32VeChn].hSource     = HI_INVALID_HANDLE;
    g_stVencChn[u32VeChn].hVEncHandle = NULL;;
    g_stVencChn[u32VeChn].bFrameBufMng = HI_TRUE;
    g_stVencChn[u32VeChn].bOMXChn     = HI_FALSE;
    g_stVencChn[u32VeChn].bEnable     = HI_FALSE;

    spin_unlock_irqrestore(&g_SendFrame_Lock[u32VeChn], flags);
    HI_INFO_VENC("VENC_DestroyChn %d OK\n", u32VeChn);

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_AttachInput(VeduEfl_EncPara_S* hVencChn, HI_HANDLE hSrc, HI_MOD_ID_E enModId )
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32VeChn = 0;
    OPTM_VENC_CHN_S* pstVenc;
    VeduEfl_SrcInfo_S stSrcInfo;
    VeduEfl_EncPara_S*  pstEncChnPara = hVencChn;

#ifdef VENC_SUPPORT_ATTACH_VI
    //VI_EXPORT_FUNC_S *pViFunc = HI_NULL;
#endif
#ifdef VENC_SUPPORT_ATTACH_VO
    WIN_EXPORT_FUNC_S *pVoFunc = HI_NULL;
#endif
#ifdef VENC_SUPPORT_ATTACH_CAST
    DISP_EXPORT_FUNC_S* pDispFunc = HI_NULL; //to be continued with vdp
#endif

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);

    memset(&stSrcInfo,0,sizeof(VeduEfl_SrcInfo_S));
    pstVenc = &g_stVencChn[u32VeChn];

    if (HI_TRUE == pstVenc->bEnable)
    {
        HI_ERR_VENC("VENC has already start! please attach before start!\n");
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    if (checkAttachModule(enModId) != HI_SUCCESS)
    {
        HI_ERR_VENC("ModId not surpport now, enModId=%x!\n", enModId);
        return HI_ERR_VENC_INVALID_PARA;
    }

    if (pstVenc->hSource != HI_INVALID_HANDLE)
    {
        HI_ERR_VENC("Venc%d already attached to %#x!\n", u32VeChn, pstVenc->hSource);
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }


    if ( HI_ID_DISP == enModId )
    {
        ret = HI_DRV_MODULE_GetFunction(HI_ID_DISP, (HI_VOID**)&pDispFunc);
        if (ret)
        {
            HI_ERR_VENC("GetFunction for Module(%d),failed!\n", HI_ID_DISP);
            return HI_FAILURE;
        }
        if (HI_NULL != pDispFunc)
        {
            stSrcInfo.handle     = hSrc;
            stSrcInfo.pfGetImage = VENC_DRV_EflGetImage;
            stSrcInfo.pfPutImage = (VE_IMAGE_FUNC)(pDispFunc->pfnDispRlsCastFrm);
            stSrcInfo.pfDetachFunc = (VE_DETACH_FUNC)(pDispFunc->pfnDispExtDeAttach);
            stSrcInfo.pfChangeInfo = (VE_CHANGE_INFO_FUNC)(pDispFunc->pfnDispSetCastAttr);
        }
        D_VENC_CHECK_PTR(stSrcInfo.pfChangeInfo);
        ret = (stSrcInfo.pfChangeInfo)(hSrc,
                            pstVenc->stChnUserCfg.u32Width,
                            pstVenc->stChnUserCfg.u32Height,
                            HI_VENC_MAX_fps);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_VENC("stSrcInfo.pfChangeInfo failed!\n");

            return HI_FAILURE;
        }

        ret = VENC_DRV_EflAttachInput(pstEncChnPara, &stSrcInfo);
    }
    else if ( HI_ID_VO == enModId )
    {
        ret = HI_DRV_MODULE_GetFunction(HI_ID_VO, (HI_VOID**)&pVoFunc);
        if (ret)
        {
            HI_ERR_VENC("GetFunction for Module(%d),failed!\n", HI_ID_VO);

            return HI_FAILURE;
        }

        if (HI_NULL != pVoFunc)
        {
            stSrcInfo.handle     = hSrc;
            stSrcInfo.pfGetImage = VENC_DRV_EflGetImage;
            stSrcInfo.pfPutImage = (VE_IMAGE_FUNC)(pVoFunc->pfnWinRlsFrm);
            stSrcInfo.pfDetachFunc = NULL;
            stSrcInfo.pfChangeInfo = (VE_CHANGE_INFO_FUNC)(pVoFunc->pfnWinSetVirAttr);

        }
        D_VENC_CHECK_PTR(stSrcInfo.pfChangeInfo);
        ret = (stSrcInfo.pfChangeInfo)(hSrc,
                            pstVenc->stChnUserCfg.u32Width,
                            pstVenc->stChnUserCfg.u32Height,
                            HI_VENC_MAX_fps);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_VENC("stSrcInfo.pfChangeInfo failed!\n");

            return HI_FAILURE;
        }
        ret = VENC_DRV_EflAttachInput(pstEncChnPara, &stSrcInfo);
    }

    if (HI_SUCCESS == ret)
    {
        pstVenc->enSrcModId   = enModId;
        pstVenc->hSource      = hSrc;
        pstVenc->bFrameBufMng = HI_TRUE;
        HI_INFO_VENC("VENC%d attchInputOK, srcHdl:%#x, UserHdl:%#x.\n", u32VeChn, pstVenc->hSource, pstVenc->u32SrcUser);
    }

    return ret;
}

HI_S32 VENC_DRV_SetSrcInfo(VeduEfl_EncPara_S* hVencChn, HI_DRV_VENC_SRC_HANDLE_S* pstSrc)
{
    HI_S32 s32Ret = 0;
#ifdef VENC_SUPPORT_ATTACH_VI
    HI_U32 u32VeChn = 0;
    VeduEfl_SrcInfo_S stSrcInfo;
    OPTM_VENC_CHN_S* pstVenc;
    VI_EXPORT_FUNC_S* pViFunc = HI_NULL;
    VeduEfl_EncPara_S*  pstEncChnPara;

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);
    D_VENC_CHECK_PTR(pstSrc);

    pstVenc = &g_stVencChn[u32VeChn];
    pstEncChnPara = (VeduEfl_EncPara_S*)g_stVencChn[u32VeChn].hVEncHandle;

    memset(&stSrcInfo,0,sizeof(VeduEfl_SrcInfo_S));

    if (pstVenc->hSource == HI_INVALID_HANDLE)
    {
        HI_ERR_VENC("Venc%d haven't attach any src!\n", u32VeChn);
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    switch (pstSrc->enSrcMode)
    {
        case HI_ID_VI:
        {
            s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_VI, (HI_VOID**)&pViFunc);
            if ((HI_SUCCESS != s32Ret)||(HI_NULL == pViFunc))
            {
                HI_ERR_VENC("GetFunction for Module(%d),failed!\n", HI_ID_VI);
                return HI_FAILURE;
            }

            stSrcInfo.handle     = pstSrc->hSrc;
            stSrcInfo.pfGetImage = VENC_DRV_EflGetImage;
            stSrcInfo.pfPutImage = (VE_IMAGE_FUNC)(pViFunc->pfnVencRlsFrame);
            stSrcInfo.pfDetachFunc = NULL;
            stSrcInfo.pfChangeInfo = (VE_CHANGE_INFO_FUNC)(pViFunc->pfnDispSetCastAttr);
            pstVenc->bFrameBufMng = HI_TRUE;

            D_VENC_CHECK_PTR(stSrcInfo.pfChangeInfo);

            s32Ret = (stSrcInfo.pfChangeInfo)(pstSrc->hSrc,
                                    pstVenc->stChnUserCfg.u32Width,
                                    pstVenc->stChnUserCfg.u32Height,
                                    HI_VENC_MAX_fps);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_VENC("The first time SetInfo to VI failed!ret = %x\n", s32Ret);
                pstVenc->hSource      = HI_INVALID_HANDLE;
                pstVenc->enSrcModId   = HI_ID_BUTT;
                pstVenc->bFrameBufMng = HI_TRUE;
                return HI_FAILURE;
            }
            break;
        }
    default:
        HI_ERR_VENC("VENC not support set Src to Mod(%d)\n", pstVenc->enSrcModId);
        return HI_ERR_VENC_INVALID_PARA;
}
    s32Ret = VENC_DRV_EflAttachInput(pstEncChnPara, &stSrcInfo);
#else
    HI_ERR_VENC("Venc not support this API\n");
    s32Ret = HI_ERR_VENC_NOT_SUPPORT;
#endif
    return s32Ret;
}

HI_S32 VENC_DRV_DetachInput(VeduEfl_EncPara_S* hVencChn, HI_HANDLE hSrc, HI_MOD_ID_E enModId )
{
    HI_U32 u32VeChn = 0;
    OPTM_VENC_CHN_S* pstVenc;
    VeduEfl_SrcInfo_S stSrcInfo = {0};
    VeduEfl_EncPara_S* pstEncChnPara;

    if (enModId >= HI_ID_BUTT)
    {
        return HI_ERR_VENC_CHN_NO_ATTACH;
    }

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);

    pstVenc = &g_stVencChn[u32VeChn];
    pstEncChnPara = (VeduEfl_EncPara_S*)g_stVencChn[u32VeChn].hVEncHandle;

    if (pstVenc->hSource == HI_INVALID_HANDLE)
    {
        HI_WARN_VENC("Venc%d NOT attached.\n", u32VeChn);
        return HI_ERR_VENC_CHN_NO_ATTACH;
    }

    if (pstVenc->hSource != hSrc)
    {
        HI_ERR_VENC("Venc%d NOT attached to %#x, but attached to %#x.\n", u32VeChn, hSrc, pstVenc->hSource);
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    if (checkAttachModule(enModId) != HI_SUCCESS)
    {
        HI_ERR_VENC("ModId not surpport now, enModId=%x!\n", enModId);
        return HI_ERR_VENC_INVALID_PARA;
    }

    //VENC must be stop working
    if (pstVenc->bEnable)
    {
        VENC_DRV_StopReceivePic(pstEncChnPara);
    }

    stSrcInfo.handle      = HI_INVALID_HANDLE;
    stSrcInfo.pfGetImage  = HI_NULL;
    stSrcInfo.pfPutImage  = HI_NULL;
    stSrcInfo.pfChangeInfo = HI_NULL;
    stSrcInfo.pfDetachFunc = HI_NULL;

    VENC_DRV_EflDetachInput(pstEncChnPara, &stSrcInfo);
    HI_INFO_VENC("VENC%d dettchInputOK, srcHdl:%#x, UserHdl:%#x.\n", u32VeChn, pstVenc->hSource, pstVenc->u32SrcUser);

    g_stVencChn[u32VeChn].enSrcModId = HI_ID_BUTT;
    g_stVencChn[u32VeChn].hSource = HI_INVALID_HANDLE;
    g_stVencChn[u32VeChn].bFrameBufMng = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 WaitForStream(VeduEfl_EncPara_S *hVencChn, HI_U32 u32TimeoutMs)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_S32 u32VeChn = 0;
    VeduEfl_EncPara_S* pstEncChnPara;

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);
    pstEncChnPara = (VeduEfl_EncPara_S*)g_stVencChn[u32VeChn].hVEncHandle;

    if (STRM_GetWrittenLength(pstEncChnPara->hStrmMng) <= 0)
    {
        if (u32TimeoutMs == 0)
        {
            return HI_ERR_VENC_BUF_EMPTY;
        }
        else
        {
            s32Ret = VENC_DRV_OsalWaitEvent(&g_VencWait_Stream[u32VeChn], u32TimeoutMs);
            if (s32Ret == HI_FAILURE)
            {
                return HI_ERR_VENC_BUF_EMPTY;
            }

            s32Ret = STRM_GetWrittenLength(pstEncChnPara->hStrmMng);
            if (s32Ret <= 0)
            {
                return HI_ERR_VENC_BUF_EMPTY;
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 AcqReadBuffer(VeduEfl_EncPara_S *pstEncChnPara, VeduEfl_NALU_S *pstVeduPacket)
{
    HI_S32 s32Ret = HI_FAILURE;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStreamInfo(pstEncChnPara, &stStreamInfo);
    s32Ret = STRM_AcqReadBuffer(pstEncChnPara->hStrmMng, &stStreamInfo, pstVeduPacket);

    pstEncChnPara->stStat.StreamTotalByte = stStreamInfo.StreamTotalByte;

    return s32Ret;
}

HI_S32 RlsReadBuffer(VeduEfl_EncPara_S *pstEncChnPara, VeduEfl_NALU_S *pstVeduPacket)
{
    HI_S32 s32Ret = HI_FAILURE;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStreamInfo(pstEncChnPara, &stStreamInfo);
    s32Ret = STRM_RlsReadBuffer(pstEncChnPara->hStrmMng, &stStreamInfo, pstVeduPacket);

    return s32Ret;
}

static HI_S32 AcquireVencStream(VeduEfl_EncPara_S *hVencChn, HI_U32 u32TimeoutMs, VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S *pstBufOffSet)
{
    HI_S32 s32Ret = HI_FAILURE;
    VeduEfl_NALU_S stVeduPacket;
    VeduEfl_EncPara_S *pstEncChnPara = hVencChn;

    s32Ret = WaitForStream(pstEncChnPara, u32TimeoutMs);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    s32Ret = AcqReadBuffer(pstEncChnPara, &stVeduPacket);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    STRM_GetAcquireStreamInfo(pstEncChnPara->hStrmMng, pstEncChnPara->Protocol, pstEncChnPara->StreamMMZBuf.pu8StartVirAddr,
                              &stVeduPacket, pstStream, pstBufOffSet);

    return HI_SUCCESS;
}


#ifdef VENC_SUPPORT_JPGE
static HI_S32 GetJpgeStream(VeduEfl_NALU_S *pstVeduPacket, VENC_STREAM_S *pstStream, VeduEfl_EncPara_S *hVencChn, VENC_BUF_OFFSET_S *pstBufOffSet)
{
    HI_S32 s32Ret = HI_FAILURE;
    VeduEfl_EncPara_S *pstEncChnPara = hVencChn;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStreamInfo(pstEncChnPara, &stStreamInfo);
    s32Ret = STRM_GetJpgeStream(pstEncChnPara->hStrmMng, &stStreamInfo, pstVeduPacket, pstStream, pstBufOffSet);

    pstEncChnPara->stStat.StreamTotalByte = stStreamInfo.StreamTotalByte;

    return s32Ret;
}

static HI_S32 AcquireJpgeStream(VeduEfl_EncPara_S *hVencChn, HI_U32 u32TimeoutMs, VENC_STREAM_S* pstStream, VENC_BUF_OFFSET_S *pstBufOffSet)
{
    HI_S32 s32Ret = HI_FAILURE;
    VeduEfl_NALU_S stVeduPacket;
    VeduEfl_EncPara_S* pstEncChnPara = hVencChn;

    s32Ret = WaitForStream(pstEncChnPara, u32TimeoutMs);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    if (pstEncChnPara->stStat.GetStreamNumOK != pstEncChnPara->stStat.PutStreamNumOK)
    {
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    s32Ret = AcqReadBuffer(pstEncChnPara, &stVeduPacket);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_ERR_VENC_BUF_EMPTY;
    }

    s32Ret = GetJpgeStream(&stVeduPacket, pstStream, pstEncChnPara, pstBufOffSet);

    return s32Ret;
}
#endif

static HI_S32 VENC_DRV_SaveStream(VENC_STREAM_S* pstStream, VeduEfl_EncPara_S* phVencChn)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32VeChn;
    VeduEfl_StatInfo_S StatInfo;
    static HI_BOOL bTagFirstTimeSave = HI_TRUE;
    static HI_U32 u32SaveFrameStartCount = 0;
    HI_U32 u32SkipFrmNum = 0;

    D_VENC_GET_CHN(u32VeChn, phVencChn);
    D_VENC_CHECK_CHN(u32VeChn);

    if ((g_stVencChn[u32VeChn].stProcWrite.bTimeModeRun == HI_TRUE) || (g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun == HI_TRUE))
    {
        s32Ret = VENC_DRV_EflQueryStatInfo(g_stVencChn[u32VeChn].hVEncHandle, &StatInfo);

        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_VENC("VeduEfl_QueryStatInfo failed.\n");

            return HI_FAILURE;
        }

        u32SkipFrmNum = StatInfo.QuickEncodeSkip + StatInfo.SamePTSSkip + StatInfo.ErrCfgSkip
                        + StatInfo.FrmRcCtrlSkip + StatInfo.TooFewBufferSkip;
#ifndef __VENC_RC_DBG__
        /* request one I frame and record u32SaveFrameStartCount to compare with g_VencSaveFrameCount when save file firstly */
        if (bTagFirstTimeSave == HI_TRUE)
        {
            VENC_DRV_EflRequestIframe(phVencChn);
            bTagFirstTimeSave = HI_FALSE;
            u32SaveFrameStartCount = StatInfo.GetFrameNumOK - u32SkipFrmNum;

            return HI_SUCCESS;
        }
#endif
        /* compare with u32FrameModeCount each time */
        if ((g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun == HI_TRUE)
            && (StatInfo.GetFrameNumOK - u32SkipFrmNum - u32SaveFrameStartCount) > g_stVencChn[u32VeChn].stProcWrite.u32FrameModeCount)
        {
            /* time to stop save file */
            g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun = HI_FALSE;

            return HI_SUCCESS;
        }

        if (pstStream->u32SlcLen > 0)
        {
            s32Ret = HI_DRV_FILE_Write(g_stVencChn[u32VeChn].stProcWrite.fpSaveFile, (char*)pstStream->VirAddr, pstStream->u32SlcLen);

            if (s32Ret != pstStream->u32SlcLen)
            {
                HI_ERR_VENC("VeduOsal_Fwrite failed.\n");
                g_stVencChn[u32VeChn].stProcWrite.bTimeModeRun  = HI_FALSE;
                g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun = HI_FALSE;
            }
        }
    }
    else
    {
        bTagFirstTimeSave = HI_TRUE;
    }

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_AcquireStream(VeduEfl_EncPara_S* hVencChn, VENC_STREAM_S* pstStream, HI_U32 u32TimeoutMs,
                              VENC_BUF_OFFSET_S* pstBufOffSet)
{
    HI_S32 s32Ret   = -1;
    HI_S32 u32VeChn = 0;
    unsigned long flags;
    VeduEfl_EncPara_S* pstEncChnPara = HI_NULL;
    D_VENC_CHECK_PTR(pstStream);
    D_VENC_CHECK_PTR(pstBufOffSet);

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);

    spin_lock_irqsave(&g_SendFrame_Lock[u32VeChn], flags);

    pstEncChnPara = g_stVencChn[u32VeChn].hVEncHandle;
    if (!pstEncChnPara || (g_stVencChn[u32VeChn].hVEncHandle == NULL))
    {
        spin_unlock_irqrestore(&g_SendFrame_Lock[u32VeChn], flags);
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    else
    {
        pstEncChnPara->stStat.GetStreamNumTry++;
    }
    spin_unlock_irqrestore(&g_SendFrame_Lock[u32VeChn], flags);

#ifdef VENC_SUPPORT_JPGE
    if (g_stVencChn[u32VeChn].hJPGE != HI_INVALID_HANDLE) /*JPEG*/
    {
        s32Ret = AcquireJpgeStream(pstEncChnPara, u32TimeoutMs, pstStream, pstBufOffSet);
    }
    else
#endif
    {
        s32Ret = AcquireVencStream(pstEncChnPara, u32TimeoutMs, pstStream, pstBufOffSet);
    }

    if (s32Ret != HI_SUCCESS)
    {
       return s32Ret;
    }

    pstEncChnPara->stStat.GetStreamNumOK++;

    HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_VSYNC, "PTS=%u.\n", pstStream->u32PtsMs);

    s32Ret = VENC_DRV_SaveStream(pstStream, pstEncChnPara);

    return s32Ret;
}

#ifdef VENC_SUPPORT_JPGE
static HI_S32 ReleaseJpgeStream(VeduEfl_EncPara_S* hVencChn, VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm)
{
    VeduEfl_EncPara_S  *pstEncChnPara = hVencChn;

    if ((pstAcqStrm->Jpeg_Phy_Addr != pstEncChnPara->JpgMMZBuf.u32StartPhyAddr)
        || (pstEncChnPara->stStat.GetStreamNumOK <= pstEncChnPara->stStat.PutStreamNumOK))
    {
        HI_ERR_VENC("Release stream failed, GetStreamNumOK=%d,PutStreamNumOK=%d,pstStream->VirAddr = %x,JpegOutBufPhyAddr= %x.\n",
                    pstEncChnPara->stStat.GetStreamNumOK, pstEncChnPara->stStat.PutStreamNumOK, pstAcqStrm->Jpeg_Phy_Addr,
                    pstEncChnPara->JpgMMZBuf.u32StartPhyAddr);
        return HI_ERR_VENC_CHN_RELEASE_ERR;
    }

    return HI_SUCCESS;
}
#endif

static HI_VOID GetRleaseStreamInfo(VeduEfl_EncPara_S *pstEncChnPara, VENC_INFO_ACQUIRE_STREAM_S *pstAcqStrm, VeduEfl_NALU_S *pstVeduPacket)
{
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStreamInfo(pstEncChnPara, &stStreamInfo);
    STRM_GetRleaseStreamInfo(pstEncChnPara->hStrmMng, pstEncChnPara->Protocol, &stStreamInfo, pstAcqStrm, pstVeduPacket);
}

static HI_S32 ReleaseVencStream(VeduEfl_EncPara_S *hVencChn, VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm)
{
    HI_S32 s32Ret = 0;
    VeduEfl_NALU_S stVeduPacket;
    VeduEfl_EncPara_S  *pstEncChnPara = hVencChn;

    memset(&stVeduPacket, 0, sizeof(VeduEfl_NALU_S));

    GetRleaseStreamInfo(pstEncChnPara, pstAcqStrm, &stVeduPacket);
    s32Ret = RlsReadBuffer(pstEncChnPara, &stVeduPacket);

    return s32Ret;
}

HI_S32 VENC_DRV_ReleaseStream(VeduEfl_EncPara_S* hVencChn, VENC_INFO_ACQUIRE_STREAM_S* pstAcqStrm)
{
    HI_U32 u32VeChn = 0;
    HI_S32 s32Ret = 0;
    VeduEfl_EncPara_S  *pstEncChnPara;

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);

    pstEncChnPara = (VeduEfl_EncPara_S*)hVencChn;

    pstEncChnPara->stStat.PutStreamNumTry++;

#ifdef VENC_SUPPORT_JPGE
    if (pstEncChnPara->Protocol == VEDU_JPGE)
    {
        s32Ret = ReleaseJpgeStream(pstEncChnPara, pstAcqStrm);
    }
    else
#endif
    {
        s32Ret = ReleaseVencStream(pstEncChnPara, pstAcqStrm);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("Release stream failed, ret= %#x.\n", s32Ret);

        return HI_ERR_VENC_CHN_RELEASE_ERR;
    }
    pstEncChnPara->stStat.PutStreamNumOK++;

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_ReleaseStreamIntar(VeduEfl_EncPara_S* hVencChn, VENC_STREAM_S* pstStream)
{
    HI_U32 u32VeChn = 0;
    HI_S32 s32Ret = 0;
    VeduEfl_NALU_S stVeduPacket;
    VeduEfl_EncPara_S*  pstEncChnPara;

    D_VENC_CHECK_PTR(pstStream);
    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);

    memset(&stVeduPacket, 0, sizeof(stVeduPacket));
    pstEncChnPara = (VeduEfl_EncPara_S*)hVencChn;

    if (g_stVencChn[u32VeChn].hJPGE != HI_INVALID_HANDLE)
    {
        pstEncChnPara->stStat.PutStreamNumTry++;

        if ((pstStream->VirAddr != (HI_VIRT_ADDR_T)pstEncChnPara->JpgMMZBuf.pu8StartVirAddr)
            || (pstEncChnPara->stStat.GetStreamNumOK <= pstEncChnPara->stStat.PutStreamNumOK))
        {
            HI_ERR_VENC("Release stream failed, GetStreamNumOK=%d,PutStreamNumOK=%d,pstStream->pu8Addr = %x,JpegOutBufPhyAddr= %x.\n",
                        pstEncChnPara->stStat.GetStreamNumOK, pstEncChnPara->stStat.PutStreamNumOK, pstStream->VirAddr,
                        pstEncChnPara->JpgMMZBuf.u32StartPhyAddr);

            return HI_ERR_VENC_CHN_RELEASE_ERR;
        }
        pstEncChnPara->stStat.PutStreamNumOK++;

        return HI_SUCCESS;
    }


    if (STRM_GetRleaseStreamInfoIntar(pstEncChnPara->hStrmMng, pstStream, &stVeduPacket) != HI_SUCCESS)
    {
        return HI_ERR_VENC_CHN_RELEASE_ERR;
    }

    pstEncChnPara->stStat.PutStreamNumTry++;

    s32Ret = RlsReadBuffer(pstEncChnPara, &stVeduPacket);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("Release stream failed, ret= %#x.\n", s32Ret);

        return HI_ERR_VENC_CHN_RELEASE_ERR;
    }

    pstEncChnPara->stStat.PutStreamNumOK++;

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_StartReceivePic(VeduEfl_EncPara_S* EncHandle)
{
    HI_S32 s32Ret   = HI_FAILURE;
    HI_U32 u32VeChn = 0;
    VeduEfl_EncPara_S*  pstEncChnPara;
    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);

    pstEncChnPara = (VeduEfl_EncPara_S*)EncHandle;

    if (HI_TRUE == g_stVencChn[u32VeChn].bEnable)
    {
        return HI_SUCCESS;
    }

    s32Ret = VENC_DRV_EflStartVenc(EncHandle);
    if (HI_SUCCESS == s32Ret)
    {
        g_stVencChn[u32VeChn].bEnable = HI_TRUE;

        if ( g_stVencChn[u32VeChn].enSrcModId >= HI_ID_BUTT)  /*non attach mode*/
        {
            pstEncChnPara->stSrcInfo.pfGetImage = VENC_DRV_EflGetImage;
            pstEncChnPara->stSrcInfo.pfGetImage_OMX = VENC_DRV_EflGetImage_OMX;
            pstEncChnPara->stSrcInfo.pfPutImage = VENC_DRV_EflPutImage;
            g_stVencChn[u32VeChn].stSrcInfo = pstEncChnPara->stSrcInfo;
        }
        do_gettimeofday(&(g_stVencChn[u32VeChn].stTimeStart));
        HI_INFO_VENC("start Chn %d/%#x. OK\n", u32VeChn, EncHandle);
        pstEncChnPara->InterFrmCnt = pstEncChnPara->stRc.Gop - 1;
        pstEncChnPara->stRc.RcStart = 1;
    }
    else
    {
        s32Ret = HI_ERR_VENC_INVALID_CHNID;
    }
    return s32Ret;
}

HI_S32 VENC_DRV_StopReceivePic(VeduEfl_EncPara_S* EncHandle)
{
    HI_S32 s32Ret   = HI_FAILURE;
    HI_U32 u32VeChn = 0;
    VeduEfl_EncPara_S* pstEncChnPara;

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
    pstEncChnPara = EncHandle;

    if (HI_FALSE == g_stVencChn[u32VeChn].bEnable)
    {
        return HI_SUCCESS;
    }

    s32Ret = VENC_DRV_EflStopVenc(pstEncChnPara);
    if (HI_SUCCESS == s32Ret)
    {
        g_stVencChn[u32VeChn].bEnable = HI_FALSE;
        HI_INFO_VENC("stop Chn %d/%#x. OK\n", u32VeChn, pstEncChnPara);
    }

    return s32Ret;
}

static HI_VOID VENC_DRV_SetAttr_Dbg(HI_UNF_VENC_CHN_ATTR_S *pstChnUserCfg, HI_UNF_VENC_CHN_ATTR_S* pstAttr, HI_BOOL Enable)
{
    if (pstChnUserCfg->enCapLevel != pstAttr->enCapLevel)
    {
        HI_ERR_VENC("VENC not support this active change enCapLevel:(%d -> %d)!\n",
                    pstChnUserCfg->enCapLevel, pstAttr->enCapLevel);
    }

    if (pstChnUserCfg->bSlcSplitEn != pstAttr->bSlcSplitEn)
    {
        HI_ERR_VENC("VENC not support this active change bSlcSplitEn:(%d -> %d)!\n",
                    pstChnUserCfg->bSlcSplitEn, pstAttr->bSlcSplitEn);
    }

    if (pstChnUserCfg->u32RotationAngle != pstAttr->u32RotationAngle)
    {
        HI_ERR_VENC("VENC not support this active change u32RotationAngle:(%d -> %d)!\n",
                    pstChnUserCfg->u32RotationAngle, pstAttr->u32RotationAngle);
    }

    if (pstChnUserCfg->u32StrmBufSize != pstAttr->u32StrmBufSize)
    {
        HI_ERR_VENC("VENC not support this active change u32StrmBufSize:(%d -> %d)!\n",
                    pstChnUserCfg->u32StrmBufSize, pstAttr->u32StrmBufSize);
    }

    if (pstChnUserCfg->enVencType != pstAttr->enVencType)
    {
        HI_ERR_VENC("VENC not support this active change encode type:(%d -> %d)!\n",
                    pstChnUserCfg->enVencType, pstAttr->enVencType);
    }

    if (Enable)
    {
        if ((pstChnUserCfg->enVencProfile != pstAttr->enVencProfile)
            && (pstChnUserCfg->enVencType == HI_UNF_VCODEC_TYPE_H264))
        {
            HI_ERR_VENC("VENC not support this active change enVencProfile:(%d -> %d)! enVencType(%d,%d)\n",
                        pstChnUserCfg->enVencProfile, pstAttr->enVencProfile, pstChnUserCfg->enVencType, HI_UNF_VCODEC_TYPE_H264);
        }
    }

    return;
}

static HI_S32 VENC_DRV_SetAttr_RCAndFrmRatePara(HI_UNF_VENC_CHN_ATTR_S* pstAttr, VeduEfl_RcAttr_S *pstRcAttrCfg,
                                       VeduEfl_EncPara_S* EncHandle, OPTM_VENC_CHN_S* pstVenc)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_BOOL RcFlag  = HI_FALSE;

    if ((pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264) || (pstAttr->enVencType == HI_UNF_VCODEC_TYPE_HEVC))
    {
        RcFlag |= (pstVenc->stChnUserCfg.u32TargetBitRate != pstAttr->u32TargetBitRate);
        RcFlag |= (pstVenc->stChnUserCfg.u32InputFrmRate  != pstAttr->u32InputFrmRate);
        RcFlag |= (pstVenc->stChnUserCfg.u32TargetFrmRate != pstAttr->u32TargetFrmRate);
        RcFlag |= (pstVenc->stChnUserCfg.u32Gop           != pstAttr->u32Gop);

        if (RcFlag == HI_TRUE)
        {
            pstRcAttrCfg->BitRate    = pstAttr->u32TargetBitRate;
            pstRcAttrCfg->InFrmRate  = pstAttr->u32InputFrmRate;
            pstRcAttrCfg->OutFrmRate = pstAttr->u32TargetFrmRate;
            pstRcAttrCfg->Gop        = pstAttr->u32Gop;

            s32Ret = VENC_DRV_EflRcSetAttr(pstVenc->hVEncHandle, pstRcAttrCfg);

            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_VENC("config venc Rate Control Attribute err:%#x.\n", s32Ret);

                return HI_FAILURE;
            }
        }
    }
#ifdef VENC_SUPPORT_JPGE
    else  /* jpeg*/
    {
        VeduEfl_EncPara_S* pstEncChnPara = EncHandle;

        if ((pstAttr->u32InputFrmRate > 60) || (pstAttr->u32InputFrmRate < pstAttr->u32TargetFrmRate))
        {
            return HI_ERR_VENC_INVALID_PARA;
        }

        /*initialize  parameter*/
        pstEncChnPara->stRc.VoFrmRate = pstAttr->u32TargetFrmRate;
        pstEncChnPara->stRc.ViFrmRate = pstAttr->u32InputFrmRate;
    }
#endif

    return HI_SUCCESS;
}
static HI_S32 VENC_DRV_SetAttr_Resolution(VeduEfl_EncPara_S* EncHandle, OPTM_VENC_CHN_S* pstVenc, HI_UNF_VENC_CHN_ATTR_S* pstAttr)
{
    VeduEfl_EncPara_S*  pstEncChnPara = EncHandle;

    if ((pstVenc->stChnUserCfg.u32Height  != pstAttr->u32Height)                //should be change
        || (pstVenc->stChnUserCfg.u32Width != pstAttr->u32Width))
    {
        if (pstVenc->enSrcModId != HI_ID_BUTT)     //attach mode
        {
            if ((pstEncChnPara->stSrcInfo.pfChangeInfo)(pstEncChnPara->stSrcInfo.handle,
                                                        pstAttr->u32Width,
                                                        pstAttr->u32Height,
                                                        HI_VENC_MAX_fps) != HI_SUCCESS)
            {
                HI_ERR_VENC("Src Handle(%x) change Info failed!.\n", pstEncChnPara->stSrcInfo.handle);

                return HI_FAILURE;
            }

            if (pstVenc->bEnable == HI_FALSE)   /*if not start encode release all frame*/
            {
                VENC_DRV_EflRlsAllFrame(pstEncChnPara);
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_SetAttr(VeduEfl_EncPara_S* EncHandle, HI_UNF_VENC_CHN_ATTR_S* pstAttr, VENC_CHN_INFO_S* pstVeInfo)
{
    HI_S32 s32Ret   = -1;
    HI_U32 u32VeChn = 0;
    HI_BOOL ErrCfg  = HI_FALSE;

    OPTM_VENC_CHN_S* pstVenc;
    VeduEfl_RcAttr_S RcAttrCfg;
    VeduEfl_EncPara_S* pstEncChnPara = (VeduEfl_EncPara_S*)EncHandle;

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
    D_VENC_CHECK_PTR(pstAttr);
    pstVenc = &g_stVencChn[u32VeChn];

    s32Ret = CheckConfig(pstAttr, pstVenc->bOMXChn);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    /* check the new attr whether legal */
    ErrCfg |= (pstVenc->stChnUserCfg.enCapLevel != pstAttr->enCapLevel);
    ErrCfg |= (pstVenc->stChnUserCfg.bSlcSplitEn != pstAttr->bSlcSplitEn);
    ErrCfg |= (pstVenc->stChnUserCfg.u32RotationAngle != pstAttr->u32RotationAngle);
    ErrCfg |= (pstVenc->stChnUserCfg.u32StrmBufSize != pstAttr->u32StrmBufSize);
    ErrCfg |= (pstVenc->stChnUserCfg.enVencType != pstAttr->enVencType);

    if (pstVenc->bEnable)
    {
        if ( pstVenc->stChnUserCfg.enVencType == HI_UNF_VCODEC_TYPE_H264 )
        {
            ErrCfg |= (pstVenc->stChnUserCfg.enVencProfile != pstAttr->enVencProfile);
        }
    }

    if (ErrCfg == HI_TRUE)
    {
        VENC_DRV_SetAttr_Dbg(&pstVenc->stChnUserCfg, pstAttr, pstVenc->bEnable);

        return HI_ERR_VENC_NOT_SUPPORT;
    }

    /* this case to change the resolution */
    s32Ret = VENC_DRV_SetAttr_Resolution(pstEncChnPara, pstVenc, pstAttr);

    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    /* this case to change the profile of H264 Encoder  */
    if ((pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264) && (pstVenc->stChnUserCfg.enVencProfile != pstAttr->enVencProfile))
    {

        pstEncChnPara->H264HpEn    = (HI_U32)pstAttr->enVencProfile;
        pstEncChnPara->H264CabacEn = (pstEncChnPara->H264HpEn == VEDU_H264_BASELINE_PROFILE) ? 0 : 1;

        /* make sps & pps & VOL stream */
        VENC_DRV_EflFlushStrmHeader(pstEncChnPara);
        pstEncChnPara->stRc.RcStart = 1;
    }

    /* this case to change the RC & FrmRate Control parameter */

    s32Ret = VENC_DRV_SetAttr_RCAndFrmRatePara(pstAttr, &RcAttrCfg, pstEncChnPara, pstVenc);
    if (s32Ret != HI_SUCCESS)
    {
        /*initialize  parameter*/


    /*this case to change the RotationAngle*/
        return s32Ret;
    }

    /* this case to change the Priority */
    if (pstVenc->stChnUserCfg.u8Priority != pstAttr->u8Priority)
    {
        HI_U32 PriorityID;
        D_VENC_GET_PRIORITY_ID(u32VeChn, PriorityID);
        D_VENC_CHECK_CHN(PriorityID);
        PriorityTab[1][PriorityID] = pstAttr->u8Priority;
        VENC_DRV_EflSortPriority();
    }

    /* update the new user attr */
    if ((pstAttr->enVencType == HI_UNF_VCODEC_TYPE_H264)||(pstAttr->enVencType == HI_UNF_VCODEC_TYPE_HEVC))
    {
        pstVenc->stChnUserCfg.u32Gop           = pstAttr->u32Gop;
        pstVenc->stChnUserCfg.u8Priority       = pstAttr->u8Priority;
        pstVenc->stChnUserCfg.u32TargetBitRate = pstAttr->u32TargetBitRate;
        pstVenc->stChnUserCfg.u32InputFrmRate  = pstAttr->u32InputFrmRate;
        pstVenc->stChnUserCfg.u32TargetFrmRate = pstAttr->u32TargetFrmRate;
        pstVenc->stChnUserCfg.u32MaxQp         = pstAttr->u32MaxQp;
        pstVenc->stChnUserCfg.u32MinQp         = pstAttr->u32MinQp;
        pstVenc->stChnUserCfg.bQuickEncode     = pstAttr->bQuickEncode;
        pstVenc->stChnUserCfg.u32DriftRateThr  = pstAttr->u32DriftRateThr;
        pstVenc->stChnUserCfg.enVencProfile    = pstAttr->enVencProfile;
        pstVenc->stChnUserCfg.enVencType       = pstAttr->enVencType;
        pstVenc->stChnUserCfg.u32RotationAngle = pstAttr->u32RotationAngle;
        pstVenc->stChnUserCfg.u32Height        = pstAttr->u32Height;
        pstVenc->stChnUserCfg.u32Width         = pstAttr->u32Width;

        pstEncChnPara->stRc.MinQp                   = pstAttr->u32MinQp;
        pstEncChnPara->stRc.MaxQp                   = pstAttr->u32MaxQp;
        pstEncChnPara->AutoSkipFrameEn         = (pstAttr->u32DriftRateThr<=100)?1:0;
        pstEncChnPara->DriftRcSkipThr          = pstAttr->u32DriftRateThr;
    }
#ifdef VENC_SUPPORT_JPGE
    else   /*JPEG*/
    {
        pstVenc->stChnUserCfg.u8Priority       = pstAttr->u8Priority;
        pstVenc->stChnUserCfg.u32InputFrmRate  = pstAttr->u32InputFrmRate;
        pstVenc->stChnUserCfg.u32TargetFrmRate = pstAttr->u32TargetFrmRate;
        pstVenc->stChnUserCfg.bQuickEncode     = pstAttr->bQuickEncode;
        pstVenc->stChnUserCfg.enVencType       = pstAttr->enVencType;
        pstVenc->stChnUserCfg.u32RotationAngle = pstAttr->u32RotationAngle;
        pstVenc->stChnUserCfg.u32Height        = pstAttr->u32Height;
        pstVenc->stChnUserCfg.u32Width         = pstAttr->u32Width;
        pstVenc->stChnUserCfg.u32Qlevel        = pstAttr->u32Qlevel;

        pstEncChnPara->QLevel                  = pstAttr->u32Qlevel;
    }
#endif
    pstEncChnPara->QuickEncode                 = pstAttr->bQuickEncode;

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_GetAttr(VeduEfl_EncPara_S* EncHandle, HI_UNF_VENC_CHN_ATTR_S* pstAttr)
{
    HI_U32 u32VeChn = 0;
    OPTM_VENC_CHN_S* pstVenc;

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
    D_VENC_CHECK_PTR(pstAttr);
    pstVenc = &g_stVencChn[u32VeChn];

    *pstAttr = pstVenc->stChnUserCfg;

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_RequestIFrame(VeduEfl_EncPara_S* EncHandle)
{
    HI_S32 u32VeChn = 0;
    OPTM_VENC_CHN_S* pstVenc;

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
    pstVenc = &g_stVencChn[u32VeChn];

    VENC_DRV_EflRequestIframe(pstVenc->hVEncHandle);

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_QueueFrame(VeduEfl_EncPara_S* hVencChn, HI_UNF_VIDEO_FRAME_INFO_S* pstFrameInfo )
{
    HI_S32 s32Ret;
    HI_U32 u32VeChn = 0;
    HI_DRV_VIDEO_FRAME_S stFrame;
    VeduEfl_EncPara_S* pstEncChnPara;

    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);
    D_VENC_CHECK_PTR(pstFrameInfo);

    pstEncChnPara = hVencChn;
    if (g_stVencChn[u32VeChn].bEnable != HI_TRUE)
    {
        HI_ERR_VENC("Please start the VENC before QueueFrame!\n");
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    if (HI_TRUE == pstEncChnPara->bNeverEnc)
    {
        if (HI_ID_BUTT == g_stVencChn[u32VeChn].enSrcModId)   //如果未绑定则设置
        {
            pstEncChnPara->stSrcInfo.pfGetImage = VENC_DRV_EflGetImage;
            pstEncChnPara->stSrcInfo.pfPutImage = VENC_DRV_EflPutImage;
        }
        else
        {
            HI_ERR_VENC("the venc had already attach another sourse!QueueFrame is  invalid!! \n");
            return HI_ERR_VENC_CHN_INVALID_STAT;
        }
    }
    s32Ret = Convert_FrameStructure(pstFrameInfo, &stFrame);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("Convert_FrameStructure error! \n");

        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    if (HI_TRUE == pstEncChnPara->bNeverEnc)
    {
        pstEncChnPara->bNeverEnc = HI_FALSE;
    }

    if (g_stVencChn[u32VeChn].stProcWrite.bSaveYUVFileRun)     //save the yuv before send to vpss
    {
        VENC_DRV_DbgWriteYUV(&stFrame, g_stVencChn[u32VeChn].stProcWrite.YUVFileName);
    }

    stFrame.u32TunnelPhyAddr = 0;
    s32Ret = VENC_DRV_EflQueueFrame(pstEncChnPara, &stFrame);

    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_DequeueFrame(VeduEfl_EncPara_S* hVencChn, HI_UNF_VIDEO_FRAME_INFO_S* pstFrameInfo )
{
    HI_S32 s32Ret;
    HI_S32 u32VeChn = 0;
    HI_DRV_VIDEO_FRAME_S stFrame;
    VeduEfl_EncPara_S* pstEncChnPara;
    D_VENC_GET_CHN(u32VeChn, hVencChn);
    D_VENC_CHECK_CHN(u32VeChn);
    D_VENC_CHECK_PTR(pstFrameInfo);

    memset(&stFrame, 0 ,sizeof(HI_DRV_VIDEO_FRAME_S));
    pstEncChnPara = hVencChn;
    if (g_stVencChn[u32VeChn].enSrcModId < HI_ID_BUTT)
    {
        HI_ERR_VENC("the venc had already attach another sourse!DequeueFrame is  invalid!! \n");
        return HI_ERR_VENC_CHN_INVALID_STAT;
    }

    s32Ret = VENC_DRV_EflDequeueFrame(pstEncChnPara, &stFrame);

    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    s32Ret = Convert_DrvFrameStructure(&stFrame, pstFrameInfo);
    return s32Ret;
}

#ifdef VENC_SUPPORT_H265
static HI_S32 GetCapInfoH265(HI_UNF_VENC_CAP_INFO_S *pstCapInfo)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 MaxResoBufMinSize = 0;
    HI_U32 MinResoBufMinSize = 0;
    HI_UNF_VCODEC_CAP_LEVEL_E enMaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_BUTT;
    HI_UNF_VCODEC_CAP_LEVEL_E enMinCapLevel = HI_UNF_VCODEC_CAP_LEVEL_BUTT;

    D_VENC_CHECK_PTR(pstCapInfo);

    pstCapInfo->enCodecType = HI_UNF_VCODEC_TYPE_HEVC;
    pstCapInfo->u32MaxChnNum = HI_VENC_MAX_CHN;

    enMaxCapLevel = GetMaxCapLevel();
    s32Ret = GetBufMinSize(enMaxCapLevel, &MaxResoBufMinSize);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    pstCapInfo->stMaxReso.enCapLevel = enMaxCapLevel;
    pstCapInfo->stMaxReso.u32Height  = HI_VENC_MAX_HEIGTH;
    pstCapInfo->stMaxReso.u32Width   = HI_VENC_MAX_WIDTH;
    pstCapInfo->stMaxReso.u32MaxBitRate = HI_VENC_MAX_bps;
    pstCapInfo->stMaxReso.u32MinBitRate = HI_VENC_MIN_bps;
    pstCapInfo->stMaxReso.u32MaxFrmRate = HI_VENC_MAX_fps;
    pstCapInfo->stMaxReso.u32MinBufSize = MaxResoBufMinSize;

    enMinCapLevel = GetMinCapLevel(0);
    s32Ret = GetBufMinSize(enMinCapLevel, &MinResoBufMinSize);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    pstCapInfo->stMinReso.enCapLevel = enMinCapLevel;
    pstCapInfo->stMinReso.u32Height  = HI_VENC_MIN_HEIGTH;
    pstCapInfo->stMinReso.u32Width   = HI_VENC_MIN_WIDTH;
    pstCapInfo->stMinReso.u32MaxBitRate = HI_VENC_MAX_bps;
    pstCapInfo->stMinReso.u32MinBitRate = HI_VENC_MIN_bps;
    pstCapInfo->stMinReso.u32MaxFrmRate = HI_VENC_MAX_fps;
    pstCapInfo->stMinReso.u32MinBufSize = MinResoBufMinSize;

    return HI_SUCCESS;
}
#endif

#ifdef VENC_SUPPORT_H264
static HI_S32 GetCapInfoH264(HI_UNF_VENC_CAP_INFO_S *pstCapInfo)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 MaxResoBufMinSize = 0;
    HI_U32 MinResoBufMinSize = 0;
    HI_UNF_VCODEC_CAP_LEVEL_E enMaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_BUTT;
    HI_UNF_VCODEC_CAP_LEVEL_E enMinCapLevel = HI_UNF_VCODEC_CAP_LEVEL_BUTT;

    D_VENC_CHECK_PTR(pstCapInfo);

    pstCapInfo->enCodecType  = HI_UNF_VCODEC_TYPE_H264;
    pstCapInfo->u32MaxChnNum = HI_VENC_MAX_CHN;

    enMaxCapLevel = GetMaxCapLevel();
    s32Ret = GetBufMinSize(enMaxCapLevel, &MaxResoBufMinSize);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    pstCapInfo->stMaxReso.enCapLevel = enMaxCapLevel;
    pstCapInfo->stMaxReso.u32Height  = HI_VENC_MAX_HEIGTH;
    pstCapInfo->stMaxReso.u32Width   = HI_VENC_MAX_WIDTH;
    pstCapInfo->stMaxReso.u32MaxBitRate = HI_VENC_MAX_bps;
    pstCapInfo->stMaxReso.u32MinBitRate = HI_VENC_MIN_bps;
    pstCapInfo->stMaxReso.u32MaxFrmRate = HI_VENC_MAX_fps;
    pstCapInfo->stMaxReso.u32MinBufSize = MaxResoBufMinSize;

    enMinCapLevel = GetMinCapLevel(0);
    s32Ret = GetBufMinSize(enMinCapLevel, &MinResoBufMinSize);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    pstCapInfo->stMinReso.enCapLevel = enMinCapLevel;
    pstCapInfo->stMinReso.u32Height  = HI_VENC_MIN_HEIGTH;
    pstCapInfo->stMinReso.u32Width   = HI_VENC_MIN_WIDTH;
    pstCapInfo->stMinReso.u32MaxBitRate = HI_VENC_MAX_bps;
    pstCapInfo->stMinReso.u32MinBitRate = HI_VENC_MIN_bps;
    pstCapInfo->stMinReso.u32MaxFrmRate = HI_VENC_MAX_fps;
    pstCapInfo->stMinReso.u32MinBufSize = MinResoBufMinSize;

    return HI_SUCCESS;
}
#endif

#ifdef VENC_SUPPORT_JPGE
static HI_S32 GetCapInfoJPGE(HI_UNF_VENC_CAP_INFO_S *pstCapInfo)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 MaxResoBufMinSize = 0;
    HI_U32 MinResoBufMinSize = 0;
    HI_UNF_VCODEC_CAP_LEVEL_E enMaxCapLevel = HI_UNF_VCODEC_CAP_LEVEL_BUTT;
    HI_UNF_VCODEC_CAP_LEVEL_E enMinCapLevel = HI_UNF_VCODEC_CAP_LEVEL_BUTT;

    D_VENC_CHECK_PTR(pstCapInfo);

    pstCapInfo->enCodecType  = HI_UNF_VCODEC_TYPE_JPEG;
    pstCapInfo->u32MaxChnNum = HI_JPGE_MAX_CHN;

    enMaxCapLevel = GetMaxCapLevel();
    s32Ret = GetBufMinSize(enMaxCapLevel, &MaxResoBufMinSize);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    pstCapInfo->stMaxReso.enCapLevel = enMaxCapLevel;
    pstCapInfo->stMaxReso.u32Height  = HI_VENC_MAX_HEIGTH;
    pstCapInfo->stMaxReso.u32Width   = HI_VENC_MAX_WIDTH;
    pstCapInfo->stMaxReso.u32MaxBitRate = HI_VENC_MAX_bps;
    pstCapInfo->stMaxReso.u32MinBitRate = HI_VENC_MIN_bps;
    pstCapInfo->stMaxReso.u32MaxFrmRate = HI_VENC_MAX_fps;
    pstCapInfo->stMaxReso.u32MinBufSize = MaxResoBufMinSize;

    enMinCapLevel = GetMinCapLevel(0);
    s32Ret = GetBufMinSize(enMinCapLevel, &MinResoBufMinSize);
    if (s32Ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    pstCapInfo->stMinReso.enCapLevel = enMinCapLevel;
    pstCapInfo->stMinReso.u32Height  = HI_VENC_MIN_HEIGTH;
    pstCapInfo->stMinReso.u32Width   = HI_VENC_MIN_WIDTH;
    pstCapInfo->stMinReso.u32MaxBitRate = HI_VENC_MAX_bps;
    pstCapInfo->stMinReso.u32MinBitRate = HI_VENC_MIN_bps;
    pstCapInfo->stMinReso.u32MaxFrmRate = HI_VENC_MAX_fps;
    pstCapInfo->stMinReso.u32MinBufSize = MinResoBufMinSize;

    return HI_SUCCESS;
}
#endif

HI_S32 VENC_DRV_GetCapability(HI_UNF_VENC_CAP_S *pstCapability)
{
    HI_U32 TypeNum = 0;

    D_VENC_CHECK_PTR(pstCapability);
    memset(pstCapability, 0, sizeof(HI_UNF_VENC_CAP_S));

#ifdef VENC_SUPPORT_H265
    if (GetCapInfoH265(&pstCapability->stCapInfo[TypeNum]) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    TypeNum++;
#endif

#ifdef VENC_SUPPORT_H264
    if (GetCapInfoH264(&pstCapability->stCapInfo[TypeNum]) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    TypeNum++;
#endif

#ifdef VENC_SUPPORT_JPGE
    if (GetCapInfoJPGE(&pstCapability->stCapInfo[TypeNum]) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
    TypeNum++;
#endif
    pstCapability->u32SupportTypeNum = TypeNum;

    if (TypeNum == 0)
    {
        HI_ERR_VENC("Get Encode Type of Capability Failure!");

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

////////////////////////////////////////////////////////////////
/*new function interface  for openTV 5*/
////////////////////////////////////////////////////////////////
HI_DECLARE_MUTEX(g_VencDrvMutex);
extern atomic_t g_VencCount;
extern struct timer_list vencTimer;
extern HI_U32 g_u32VencOpenFlag;
extern HI_VOID VENC_TimerFunc(HI_LENGTH_T value);

HI_S32 VENC_DRV_Init(HI_VOID)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_VENC, "HI_VENC", (HI_VOID*)&s_VencExportFuncs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("HI_DRV_MODULE_Register failed, mode ID = 0x%08X\n", HI_ID_VENC);
        return HI_FAILURE;
    }

    InitVencInterface();

    return HI_SUCCESS;
}

HI_VOID VENC_DRV_Exit(HI_VOID)
{
    HI_DRV_MODULE_UnRegister(HI_ID_VENC);
    return;
}

#ifndef VENC_DPT_ONLY
HI_S32 HI_DRV_VENC_GetUserHndByKerHnd(VeduEfl_EncPara_S* hVencHandle, HI_HANDLE* hVencUsrHandle)
{
    HI_S32 i = 0;

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (g_stVencChn[i].hVEncHandle == hVencHandle)
        { break; }
    }

    if (i >= HI_VENC_MAX_CHN)
    {
        HI_ERR_VENC("unknown venchandle!\n");
        return HI_FAILURE;
    }

    *hVencUsrHandle = GET_VENC_CHHANDLE(i);
    return HI_SUCCESS;
}


HI_S32 HI_DRV_VENC_Init(HI_VOID)
{
    HI_S32 s32Ret = 0;

#if 0
    /*Init the VENC device*/
    s32Ret = VENC_DRV_Init();
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("Init VENC drv fail!\n");
        return HI_FAILURE;
    }
#endif

    /*just init the wait_event*/
    //VENC_DRV_BoardInit();  ==> after create the channel

    VENC_DRV_InitEvent();

    /*creat thread to manage channel*/
    s32Ret = VENC_DRV_EflOpenVedu();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_VENC("VeduEfl_OpenVedu failed, ret=%d\n", s32Ret);
        return HI_FAILURE;
    }
    return s32Ret;
}

HI_S32 HI_DRV_VENC_DeInit(HI_VOID)
{

    HI_S32 s32Ret = 0;
    HI_U32 i = 0;

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (g_stVencChn[i].hVEncHandle == NULL)
        {
            break;
        }
    }
    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (/*(g_stVencChn[i].pWhichFile == ffile)&& */(g_stVencChn[i].hVEncHandle != NULL))
        {
            HI_INFO_VENC("Try VENC_DestroyChn %d/%#p.\n", i, g_stVencChn[i].hVEncHandle);
            s32Ret = VENC_DRV_DestroyChn(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != s32Ret)
            {
                HI_WARN_VENC("force DestroyChn %d failed, Ret=%#x.\n", i, s32Ret);
            }
            g_stVencChn[i].pWhichFile = HI_NULL;
        }
    }

    VENC_DRV_EflCloseVedu();

    /*close the venc lock*/
    VENC_DRV_BoardDeinit();

#if 0
    VENC_DRV_Exit();
#endif

    return HI_SUCCESS;
}

HI_S32 HI_DRV_VENC_GetDefaultAttr(HI_UNF_VENC_CHN_ATTR_S* pstAttr)
{
    if (NULL == pstAttr)
    {
        return HI_ERR_VENC_NULL_PTR;
    }

    pstAttr->enVencType       = HI_UNF_VCODEC_TYPE_H264;
    pstAttr->enCapLevel       = HI_UNF_VCODEC_CAP_LEVEL_720P;
    pstAttr->enVencProfile    = HI_UNF_H264_PROFILE_HIGH;
    pstAttr->u32RotationAngle = 0;
    pstAttr->bSlcSplitEn      = HI_FALSE;
    pstAttr->u32StrmBufSize   = 1280 * 720 * 2;
    pstAttr->u32Width         = 1280;
    pstAttr->u32Height        = 720;

    pstAttr->u32TargetBitRate = 4 * 1024 * 1024;
    pstAttr->u32InputFrmRate  = 25;
    pstAttr->u32TargetFrmRate = 25;
    pstAttr->u32Gop           = 100;
    pstAttr->u32MaxQp = 48;
    pstAttr->u32MinQp = 16;
    pstAttr->bQuickEncode     = HI_FALSE;
    pstAttr->u32DriftRateThr  = (-1);
    pstAttr->u8Priority       = 0;
    pstAttr->u32Qlevel        = 0;
    return HI_SUCCESS;
}

HI_S32 HI_DRV_VENC_Create(HI_HANDLE* phVencChn, HI_UNF_VENC_CHN_ATTR_S* pstAttr, HI_BOOL bOMXChn, struct file*  pfile)
{
    VENC_CHN_INFO_S stVeInfo;   //no use output in the mode
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VeduEfl_EncPara_S* hKernVencChn = NULL;
    venc_chan_cfg stVencCfg ;

    stVencCfg.bAutoRequestIFrm = HI_FALSE;
    stVencCfg.bPrependSpsPps   = HI_TRUE;
    stVencCfg.bOmxChn          = HI_FALSE;
    stVencCfg.ControlRateType  = VENC_DRV_ControlRateConstant;
    stVencCfg.h264Level        = 0;   //no use
    memcpy(&stVencCfg.VencUnfAttr, pstAttr, sizeof(HI_UNF_VENC_CHN_ATTR_S));

    Ret = down_interruptible(&g_VencDrvMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_CreateChn(&hKernVencChn, &stVencCfg, &stVeInfo, bOMXChn, pfile);
    D_VENC_GET_CHN(u32Index, hKernVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
        up(&g_VencDrvMutex);
        return HI_ERR_VENC_CREATE_ERR;
    }

    g_stVencChn[u32Index].hUsrHandle = GET_VENC_CHHANDLE(u32Index);
    *phVencChn = g_stVencChn[u32Index].hUsrHandle;
    up(&g_VencDrvMutex);

#ifdef __VENC_RC_DBG__

    g_stVencChn[u32Index].stProcWrite.fpSaveFile = VENC_DRV_OsalFopen("/mnt/venc_rc_dbg.h264",  O_RDWR | O_CREAT | O_APPEND, 0);
    if (HI_NULL == g_stVencChn[u32Index].stProcWrite.fpSaveFile)
    {
        HI_ERR_VENC("Can not create file.\n");
        g_stVencChn[u32Index].stProcWrite.bTimeModeRun = HI_FALSE;
        return HI_FAILURE;
    }
    g_stVencChn[u32Index].stProcWrite.bTimeModeRun = HI_TRUE;
#endif
    return Ret;
}

HI_S32 HI_DRV_VENC_Destroy(HI_HANDLE hVenc)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;

    // VENC
    Ret = down_interruptible(&g_VencDrvMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, hVenc);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
        up(&g_VencDrvMutex);
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }


#ifdef __VENC_RC_DBG__
    g_stVencChn[u32Index].stProcWrite.bTimeModeRun = HI_FALSE;
    VENC_DRV_OsalFclose(g_stVencChn[u32Index].stProcWrite.fpSaveFile);

#endif

    Ret  |= VENC_DRV_DestroyChn(g_stVencChn[u32Index].hVEncHandle);

    up(&g_VencDrvMutex);

    return Ret;
}

HI_S32 HI_DRV_VENC_AttachInput(HI_HANDLE hVenc, HI_HANDLE hSrc)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    s32Ret = VENC_DRV_AttachInput(hVencChn, hSrc, ((hSrc & 0xff0000) >> 16));
    up(&g_VencDrvMutex);
    return s32Ret;

}

HI_S32 HI_DRV_VENC_DetachInput(HI_HANDLE hVenc)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_HANDLE hSrc = 0;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;

    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    hSrc = hVencChn->stSrcInfo.handle;
    s32Ret =  VENC_DRV_DetachInput(hVencChn,hSrc, ((hSrc & 0xff0000) >> 16));
    up(&g_VencDrvMutex);

    return s32Ret;
}

HI_S32 HI_DRV_VENC_Start(HI_HANDLE hVenc)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_StartReceivePic(hVencChn);
    up(&g_VencDrvMutex);
    return s32Ret;
}

HI_S32 HI_DRV_VENC_Stop(HI_HANDLE hVenc)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_StopReceivePic(hVencChn);
    up(&g_VencDrvMutex);
    return s32Ret;
}

HI_S32 HI_DRV_VENC_AcquireStream(HI_HANDLE hVenc,VENC_STREAM_S *pstStream, HI_U32 u32TimeoutMs)
{
   VENC_BUF_OFFSET_S stBufOffSet;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    return VENC_DRV_AcquireStream(hVencChn, pstStream, u32TimeoutMs, &stBufOffSet);
}

HI_S32 HI_DRV_VENC_ReleaseStream(HI_HANDLE hVenc, VENC_STREAM_S *pstStream)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_ReleaseStreamIntar(hVencChn, pstStream);
    up(&g_VencDrvMutex);
    return s32Ret;
}

HI_S32 HI_DRV_VENC_SetAttr(HI_HANDLE hVenc,HI_UNF_VENC_CHN_ATTR_S *pstAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_SetAttr(hVencChn, pstAttr, HI_NULL);
    up(&g_VencDrvMutex);
    return s32Ret;
}

HI_S32 HI_DRV_VENC_GetAttr(HI_HANDLE hVenc, HI_UNF_VENC_CHN_ATTR_S *pstAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_GetAttr(hVencChn, pstAttr);
    up(&g_VencDrvMutex);
    return s32Ret;
}

HI_S32 HI_DRV_VENC_RequestIFrame(HI_HANDLE hVenc)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_RequestIFrame(hVencChn);
    up(&g_VencDrvMutex);
    return s32Ret;
}

HI_S32 HI_DRV_VENC_QueueFrame(HI_HANDLE hVenc, HI_UNF_VIDEO_FRAME_INFO_S *pstFrameinfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_QueueFrame(hVencChn, pstFrameinfo );
    up(&g_VencDrvMutex);
    return s32Ret;
}

HI_S32 HI_DRV_VENC_DequeueFrame(HI_HANDLE hVenc, HI_UNF_VIDEO_FRAME_INFO_S *pstFrameinfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ChnID;
    VeduEfl_EncPara_S* hVencChn;
    s32Ret = down_interruptible(&g_VencDrvMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);
    hVencChn = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_DequeueFrame(hVencChn, pstFrameinfo);
    up(&g_VencDrvMutex);
    return s32Ret;
}


HI_S32 HI_DRV_VENC_Open_By_OPENTV(HI_VOID)
{
    HI_S32 Ret, i;

    Ret = down_interruptible(&g_VencDrvMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    if (1 == atomic_inc_return(&g_VencCount))
    {
        VENC_DRV_InitEvent();

        Ret = VENC_DRV_EflOpenVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("VeduEfl_OpenVedu failed, ret=%d\n", Ret);
            atomic_dec(&g_VencCount);
            up(&g_VencDrvMutex);
            return HI_FAILURE;
        }


        for (i = 0; i < HI_VENC_MAX_CHN; i++)
        {
            memset(&(g_stVencChn[i]), 0, sizeof(OPTM_VENC_CHN_S));
            g_stVencChn[i].hVEncHandle = NULL;
        }

        init_timer(&vencTimer);
        vencTimer.expires  = jiffies + (HZ);
        vencTimer.function = VENC_TimerFunc;
        add_timer(&vencTimer);
    }

    g_u32VencOpenFlag = 1;
    up(&g_VencDrvMutex);

#ifdef VENC_SUPPORT_JPGE
    Ret = HI_DRV_MODULE_GetFunction(HI_ID_JPGENC, (HI_VOID**)&pJpgeFunc);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("Get jpge function failed!\n");
        pJpgeFunc = HI_NULL;
    }
#endif


    return HI_SUCCESS;
}


HI_S32 HI_DRV_VENC_Close_By_OPENTV(struct file*  ffile)
{
    HI_U32 i = 0;
    HI_S32 Ret = 0;

    Ret = down_interruptible(&g_VencDrvMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    del_timer_sync(&vencTimer);

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if ((g_stVencChn[i].pWhichFile == ffile)
            && (g_stVencChn[i].hVEncHandle != NULL))
        {

            HI_INFO_VENC("Try VENC_DestroyChn %d/%#x.\n", i, g_stVencChn[i].hVEncHandle);
            Ret |= VENC_DRV_DestroyChn(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_WARN_VENC("force DestroyChn %d failed, Ret=%#x.\n", i, Ret);
            }

            g_stVencChn[i].pWhichFile = HI_NULL;
        }
    }

    if (atomic_dec_and_test(&g_VencCount))
    {
        VENC_DRV_EflCloseVedu();
        VENC_DRV_BoardDeinit();
    }

    g_u32VencOpenFlag = 0;
    up(&g_VencDrvMutex);

    return HI_SUCCESS;
}

EXPORT_SYMBOL(HI_DRV_VENC_Init);
EXPORT_SYMBOL(HI_DRV_VENC_DeInit);
EXPORT_SYMBOL(HI_DRV_VENC_GetDefaultAttr);
EXPORT_SYMBOL(HI_DRV_VENC_Create);
EXPORT_SYMBOL(HI_DRV_VENC_Destroy);
EXPORT_SYMBOL(HI_DRV_VENC_AttachInput);
EXPORT_SYMBOL(HI_DRV_VENC_DetachInput);
EXPORT_SYMBOL(HI_DRV_VENC_Start);
EXPORT_SYMBOL(HI_DRV_VENC_Stop);
EXPORT_SYMBOL(HI_DRV_VENC_AcquireStream);
EXPORT_SYMBOL(HI_DRV_VENC_ReleaseStream);
EXPORT_SYMBOL(HI_DRV_VENC_SetAttr);
EXPORT_SYMBOL(HI_DRV_VENC_GetAttr);
EXPORT_SYMBOL(HI_DRV_VENC_RequestIFrame);
EXPORT_SYMBOL(HI_DRV_VENC_QueueFrame);
EXPORT_SYMBOL(HI_DRV_VENC_DequeueFrame);
EXPORT_SYMBOL(HI_DRV_VENC_GetUserHndByKerHnd);

EXPORT_SYMBOL(HI_DRV_VENC_Open_By_OPENTV);
EXPORT_SYMBOL(HI_DRV_VENC_Close_By_OPENTV);
#endif

EXPORT_SYMBOL(VEDU_DRV_EflRcInitQp);
EXPORT_SYMBOL(VEDU_DRV_RCGetTargetFrameBits);
EXPORT_SYMBOL(ModifyInfoForBitRatesChange);
EXPORT_SYMBOL(ModifyInfoForGopChange);
EXPORT_SYMBOL(VEDU_DRV_EflRCGetCurTimeOfP);
EXPORT_SYMBOL(VEDU_DRV_EflRCCalcTargetFrameBits);
EXPORT_SYMBOL(VEDU_DRV_RCofFirstFrame);
EXPORT_SYMBOL(VEDU_DRV_RcModifyQPForLargeFrmBits);
EXPORT_SYMBOL(VEDU_DRV_RCCalcQPDeltaByFrameBits);
EXPORT_SYMBOL(VEDU_DRV_RCCalcQPDeltaByInstantBits);
EXPORT_SYMBOL(VEDU_DRV_RCCalcQPDeltaByBitRate);
EXPORT_SYMBOL(VEDU_DRV_RCCalcQPDeltaByWaterline);
EXPORT_SYMBOL(VEDU_DRV_RCCalculateCurQP);
EXPORT_SYMBOL(VEDU_DRV_RCUpdateFrameBits);
EXPORT_SYMBOL(VEDU_DRV_RCCalcTimeOfP);
EXPORT_SYMBOL(VEDU_DRV_RCUpdateInstantBits);
EXPORT_SYMBOL(ModifyInfoForFrmRateChange);
EXPORT_SYMBOL(VEDU_DRV_RCIsNeedRecoding);
EXPORT_SYMBOL(VEDU_DRV_RCStartQPChange);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

