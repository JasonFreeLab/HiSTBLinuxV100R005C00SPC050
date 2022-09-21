/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_support.c
Version           : Initial Draft
Author            : sdk
Created          : 2017/03/31
Description      : check whether hard decode support CNend\n
Function List    :


History          :
Date                         Author                Modification
2017/03/31                sdk                    Created file
******************************************************************************/

/***************************** add include here*********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
#include <cutils/properties.h>
#endif

#include "jerror.h"
#include "hi_jpeg_checkpara.h"
/***************************** Macro Definition ********************************/

/***************************** Structure Definition ****************************/

/***************************** Global Variable declaration *********************/

/***************************** API forward declarations ************************/
static inline HI_BOOL JPEG_HDEC_SupportLowDelay(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_ForceToSoftDec(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_SupportCts(HI_VOID);
static inline HI_BOOL JPEG_HDEC_DriSupport(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_HufTableNumSupport(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_ScaleSupport(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_SampleFactorSupport(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_InputImgSizeSupport(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_OutColorSpaceSupport(const struct jpeg_decompress_struct *cinfo);
static inline HI_BOOL JPEG_HDEC_HardDecInflexion(const struct jpeg_decompress_struct *cinfo);
static inline HI_VOID JPEG_HDEC_SupportOutUsrBuf(const struct jpeg_decompress_struct *cinfo);

extern HI_BOOL JPEG_HDEC_OpenDev(const struct jpeg_decompress_struct *cinfo);
extern HI_BOOL JPEG_HDEC_AllocDecodeMemory  (j_decompress_ptr cinfo);
extern HI_VOID JPEG_HDEC_FreeDecodeMemory(j_decompress_ptr cinfo);
extern HI_BOOL JPEG_HDEC_GetTable           (j_decompress_ptr cinfo);
extern HI_VOID JPEG_HDEC_GetImagInfo(j_decompress_ptr cinfo);

/***************************** API realization *********************************/


/*****************************************************************************
* func             : JPEG_HDEC_IfSupport
* description   : check whether the hard decode support
                         CNcomment: 判断是否支持硬件解码   CNend\n
* param[in]    : cinfo       CNcomment: 解码对象   CNend\n
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_IfSupport(j_decompress_ptr cinfo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_BOOL DriSupport = HI_FALSE;
    HI_BOOL SupportCts = HI_FALSE;
    HI_BOOL LowDelaySupport = HI_FALSE;
    HI_BOOL ForceToSoftDec = HI_FALSE;
    HI_BOOL ScaleSupport   = HI_FALSE;
    HI_BOOL InputImgSizeSupport = HI_FALSE;
    HI_BOOL OutColorSpaceSupport = HI_FALSE;
    HI_BOOL HardDecInflexion = HI_FALSE;
    HI_BOOL SampleFactorSupport = HI_FALSE;
    HI_BOOL HufNumSupport = HI_FALSE;
    HI_BOOL OpenDevSuccess = HI_FALSE;
    HI_BOOL TableSupport = HI_FALSE;
    HI_BOOL AllocMemSuccess = HI_FALSE;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_API_MODULE_DEFINE_HANDLE();

    /**<-- has been call start decode>**/
    /**<--已经调用过解码>**/
    if (HI_TRUE == pJpegHandle->bCheckedSupportHardDec)
    {
       return;
    }
    pJpegHandle->bCheckedSupportHardDec = HI_TRUE;

    /**<-- initial hard dec not support >**/
    /**<--初始化硬件解码不支持>**/
    pJpegHandle->SupportHardDec = HI_FALSE;

    /**<-- initial resources has been release >**/
    /**<--初始化资源已经被释放>**/
    pJpegHandle->bReleaseRes =  HI_FALSE;

    OpenDevSuccess = JPEG_HDEC_OpenDev(cinfo);
    if (HI_TRUE != OpenDevSuccess)
    {
        return;
    }

    LowDelaySupport = JPEG_HDEC_SupportLowDelay(cinfo);
    if (HI_TRUE != LowDelaySupport)
    {
       return;
    }

    JPEG_HDEC_GetImagInfo(cinfo);

    /**<-- only support out to phymem  >**/
    /**<-- 只支持解码输出到用户连续的物理内存 >**/
    JPEG_HDEC_SupportOutUsrBuf(cinfo);

    ForceToSoftDec = JPEG_HDEC_ForceToSoftDec(cinfo);
    if (HI_TRUE == ForceToSoftDec)
    {
        return;
    }

    /**<-- only support out to phymem  >**/
    /**<-- 只支持解码输出到用户连续的物理内存 >**/
    SupportCts = JPEG_HDEC_SupportCts();
    if (HI_TRUE == SupportCts)
    {
        return;
    }

    DriSupport = JPEG_HDEC_DriSupport(cinfo);
    if (HI_TRUE != DriSupport)
    {
        return;
    }

    HufNumSupport = JPEG_HDEC_HufTableNumSupport(cinfo);
    if (HI_TRUE != HufNumSupport)
    {
        return;
    }

    ScaleSupport = JPEG_HDEC_ScaleSupport(cinfo);
    if (HI_TRUE != ScaleSupport)
    {
        return;
    }

    SampleFactorSupport = JPEG_HDEC_SampleFactorSupport(cinfo);
    if (HI_TRUE != SampleFactorSupport)
    {
        return;
    }

    InputImgSizeSupport = JPEG_HDEC_InputImgSizeSupport(cinfo);
    if (HI_TRUE != InputImgSizeSupport)
    {
        return;
    }

    OutColorSpaceSupport = JPEG_HDEC_OutColorSpaceSupport(cinfo);
    if (HI_TRUE != OutColorSpaceSupport)
    {
        return;
    }

    HardDecInflexion = JPEG_HDEC_HardDecInflexion(cinfo);
    if (HI_TRUE == HardDecInflexion)
    {
        return;
    }

    TableSupport = JPEG_HDEC_GetTable(cinfo);
    if (HI_TRUE != TableSupport)
    {
        return;
    }

    AllocMemSuccess = JPEG_HDEC_AllocDecodeMemory(cinfo);
    if (HI_TRUE != AllocMemSuccess)
    {
        return;
    }

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETDEVICE);
    if (HI_SUCCESS != Ret)
    {
        return;
    }

    /**<-- initial hard dec support >**/
    /**<--初始化硬件解码支持>**/
    pJpegHandle->SupportHardDec = HI_TRUE;

    return;
}

static inline HI_BOOL JPEG_HDEC_SupportCrop(const struct jpeg_decompress_struct *cinfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
    {
       ERREXIT(cinfo, JERR_CROP_CANNOT_SUPPORT);
    }

    return HI_TRUE;
}

static inline HI_BOOL JPEG_HDEC_SupportLowDelay(const struct jpeg_decompress_struct *cinfo)
{
#ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
    JPEG_API_MODULE_DEFINE_HANDLE();

    if (HI_FALSE == pJpegHandle->bLowDelayEn)
    {
       return HI_TRUE;
    }

    /**<-- only support input data with physical memory >**/
    /**<--只支持输入码流放在连续物理内存，不支持续码流模式>**/
    if (HI_FALSE == pJpegHandle->bOutUsrBuf)
    {
        ERREXIT(cinfo, JERR_BAD_STATE);
    }

    /**<-- only support decode to user physical memory >**/
    /**<--只支持解码输出到用户连续的物理内存，否则无法实现低延迟数据读取>**/
    if (HI_FALSE == pJpegHandle->bOutUsrBuf)
    {
       ERREXIT(cinfo, JERR_BAD_STATE);
    }

    /**<-- not support scale for low delay >**/
    /**<--低延迟不支持缩放>**/
    if (0 != pJpegHandle->ScalRation)
    {
       ERREXIT(cinfo, JERR_BAD_STATE);
    }

    /**<-- not support all output to yuv420sp >**/
    /**<--不支持统一输出到yuv420sp >**/
    if (HI_TRUE == pJpegHandle->bOutYUV420SP)
    {
        ERREXIT(cinfo, JERR_BAD_STATE);
    }

    /**<-- only support decode to yuv semi-planer  >**/
    /**<--只支持输出yuv semi-planer >**/
    if (HI_TRUE != pJpegHandle->bOutYCbCrSP)
    {
        ERREXIT(cinfo, JERR_BAD_STATE);
    }
#else
    HI_UNUSED(cinfo);
#endif
    return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_ForceToSoftDec(const struct jpeg_decompress_struct *cinfo)
{
#ifndef HI_ADVCA_FUNCTION_RELEASE
  #ifdef CONFIG_GFX_PROPERTY_SUPPORT
    HI_CHAR JpegDecMod[256] = {'\0'};
  #else
    HI_CHAR *pJpegDecMod = NULL;
  #endif
#endif
    /**<-- not support progressive >**/
    /**<--不支持progressive 图片>**/
    if (FALSE != cinfo->progressive_mode)
    {
        return HI_TRUE;
    }

    /**<-- not support arith code >**/
    /**<--不支持算术编码>**/
    if (FALSE != cinfo->arith_code)
    {
       return HI_TRUE;
    }

    /**<-- not support data precision is 8 bits >**/
    /**<--不支持精度不为8 的>**/
    if (8 != cinfo->data_precision)
    {
        return HI_TRUE;
    }

#ifndef HI_ADVCA_FUNCTION_RELEASE
    #ifdef CONFIG_GFX_PROPERTY_SUPPORT
      /**<-- setprop persist.sys.jpeg.hard.decode soft >**/
      /**<-- 默认使用硬件解码 >**/
      property_get("persist.sys.jpeg.hard.decode",JpegDecMod,"hard");
      JpegDecMod[sizeof(JpegDecMod) - 1] = '\0';

      if (0 == strncmp("soft", JpegDecMod, strlen("soft") > strlen(JpegDecMod) ? (strlen("soft")) : (strlen(JpegDecMod))))
      {
         return HI_TRUE;
      }
    #else
      /** export HISI_JPEG_DECODE=soft **/
      pJpegDecMod = getenv("HISI_JPEG_DECODE");
      if (NULL == pJpegDecMod)
      {
          return HI_FALSE;
      }

      if (0 == strncmp("soft", pJpegDecMod, strlen("soft") > strlen(pJpegDecMod) ? (strlen("soft")) : (strlen(pJpegDecMod))))
      {
         return HI_TRUE;
      }
    #endif
#endif
    return HI_FALSE;
}


static inline HI_BOOL JPEG_HDEC_HardDecInflexion(const struct jpeg_decompress_struct *cinfo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 InflexionSize = 0;
    HI_U32 ImgSize = cinfo->image_width * cinfo->image_height;

    JPEG_API_MODULE_DEFINE_HANDLE();

    if (pJpegHandle->JpegDev < 0)
    {
       return HI_FALSE;
    }

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETINFLEXION, &InflexionSize);
    if (HI_SUCCESS != Ret)
    {
       return HI_TRUE;
    }

    if (ImgSize <= InflexionSize)
    {
         return HI_TRUE;
    }

    return HI_FALSE;
}

static inline HI_BOOL JPEG_HDEC_SupportCts(HI_VOID)
{
#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
    HI_CHAR Name[256] = {'\0'};
    HI_CHAR ProcName[256] = {'\0'};
    HI_CHAR ProcessStatusPath[256] = {'\0'};
    HI_S32 Pid = 0;
    FILE* pProcessStatus = NULL;
    HI_CHAR acRealPath[PATH_MAX] = {'\0'};

    Pid = getpid();
    snprintf(ProcessStatusPath,256,"%s%d%s","/proc/",Pid,"/status");
    ProcessStatusPath[sizeof(ProcessStatusPath) - 1] = '\0';

    if (NULL == realpath(ProcessStatusPath, acRealPath))
    {
       return HI_FALSE;
    }
    acRealPath[sizeof(acRealPath) - 1] = '\0';

    pProcessStatus = fopen(acRealPath, "r");
    if (NULL != pProcessStatus)
    {
       (HI_VOID)fscanf(pProcessStatus,"%s %s",Name,ProcName);
       fclose(pProcessStatus);
    }

    if (  (0 == strncmp("ndroid.cts.stub", ProcName, strlen("ndroid.cts.stub") > strlen(ProcName) ? strlen("ndroid.cts.stub") : strlen(ProcName)))
        ||(0 == strncmp("id.cts.graphics", ProcName, strlen("id.cts.graphics") > strlen(ProcName) ? strlen("id.cts.graphics") : strlen(ProcName)))
        ||(0 == strncmp("id.graphics.cts", ProcName, strlen("id.graphics.cts") > strlen(ProcName) ? strlen("id.graphics.cts") : strlen(ProcName)))
        ||(0 == strncmp("roid.camera.cts", ProcName, strlen("roid.camera.cts") > strlen(ProcName) ? strlen("roid.camera.cts") : strlen(ProcName))))
    {
        return HI_TRUE;
    }
#endif
    return HI_FALSE;
}

static inline HI_BOOL JPEG_HDEC_DriSupport(const struct jpeg_decompress_struct *cinfo)
{
#ifndef CONFIG_JPEG_DRI_SUPPORT
     JPEG_API_MODULE_DEFINE_HANDLE();

     if (  (0 != pJpegHandle->s32LuDcLen[0]) || (0 != pJpegHandle->s32LuDcLen[1])
         ||(0 != pJpegHandle->s32LuDcLen[2]) || (0 != pJpegHandle->s32LuDcLen[3])
         ||(0 != pJpegHandle->s32LuDcLen[4]) || (0 != pJpegHandle->s32LuDcLen[5]))
     {
         return HI_FALSE;
     }
#else
     HI_UNUSED(cinfo);
#endif
     return HI_TRUE;
}

static inline HI_BOOL JPEG_HDEC_ScaleSupport(const struct jpeg_decompress_struct *cinfo)
{
    JPEG_API_MODULE_DEFINE_HANDLE();

    if (pJpegHandle->ScalRation > CONFIG_JPEG_SCALE_MULTIPLE_8)
    {
        return HI_FALSE;
    }

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
    if ( (HI_TRUE == pJpegHandle->bOutYUV420SP) && (CONFIG_JPEG_SCALE_MULTIPLE_8 == pJpegHandle->ScalRation))
    {
        return HI_FALSE;
    }
 #endif

    return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_SampleFactorSupport(const struct jpeg_decompress_struct *cinfo)
{
#ifdef CONFIG_JPEG_SET_SAMPLEFACTOR
    HI_S32  ComponentCnt = 0;
    HI_BOOL bY22 = HI_FALSE;
    HI_BOOL bU12 = HI_FALSE;
    HI_BOOL bV12 = HI_FALSE;
    jpeg_component_info *compptr = NULL;

    JPEG_API_MODULE_DEFINE_HANDLE();

    for (ComponentCnt = 0; ComponentCnt < cinfo->comps_in_scan; ComponentCnt++)
    {
         compptr = cinfo->cur_comp_info[ComponentCnt];
         if( (0 == ComponentCnt) && (2 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
             bY22 = HI_TRUE;
         if( (1 == ComponentCnt) && (1 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
             bU12 = HI_TRUE;
         if( (2 == ComponentCnt) && (1 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
             bV12 = HI_TRUE;
    }

    if ( (HI_TRUE == bY22) && (HI_TRUE == bU12) && (HI_TRUE == bV12))
    {
         return HI_FALSE;
    }

    if ( (JPEG_FMT_YUV444 == pJpegHandle->enImageFmt) && (HI_TRUE == bU12) && (HI_TRUE == bV12))
    {
        return HI_FALSE;
    }
#endif
    return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_InputImgSizeSupport(const struct jpeg_decompress_struct *cinfo)
{
     if ( (cinfo->image_width  < 1) || (cinfo->image_width  > 8096)
        ||(cinfo->image_height < 1) || (cinfo->image_height > 8096))
     {
         return HI_FALSE;
     }

     return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_OutColorSpaceSupport(const struct jpeg_decompress_struct *cinfo)
{
     if (   (JCS_CMYK  == cinfo->jpeg_color_space) || (JCS_YCCK  == cinfo->jpeg_color_space)
         || (JCS_YCbCr == cinfo->out_color_space)  || (JCS_CrCbY == cinfo->out_color_space)
         || (JCS_GRAYSCALE == cinfo->out_color_space) || (JCS_UNKNOWN == cinfo->out_color_space))
     {
        return HI_FALSE;
     }

     return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_HufTableNumSupport(const struct jpeg_decompress_struct *cinfo)
{
    HI_S32 ComponentNum = 0;

    for (ComponentNum = 0; ComponentNum < cinfo->num_components && ComponentNum < MAX_COMPS_IN_SCAN; ComponentNum++)
    {
       if (cinfo->cur_comp_info[ComponentNum]->dc_tbl_no != cinfo->cur_comp_info[ComponentNum]->ac_tbl_no)
       {
          return HI_FALSE;
       }
    }

     return HI_TRUE;
}

#if 0
static inline HI_VOID JPEG_HDEC_ExistQuantTable(const struct jpeg_decompress_struct *cinfo)
{
     if (NULL == cinfo->quant_tbl_ptrs[0])
     {
         ERREXIT(cinfo, JERR_NO_QUANT_TABLE);
     }
     return;
}


static inline HI_VOID JPEG_HDEC_ExistHuffTable(const struct jpeg_decompress_struct *cinfo)
{
     if (  (NULL == cinfo->dc_huff_tbl_ptrs[0]) || (NULL != cinfo->dc_huff_tbl_ptrs[2])
         ||(NULL == cinfo->ac_huff_tbl_ptrs[0]) || (NULL != cinfo->ac_huff_tbl_ptrs[2]))
     {
         ERREXIT(cinfo, JERR_BAD_HUFF_TABLE);
     }
     return;
}
#endif

static inline HI_VOID JPEG_HDEC_SupportOutUsrBuf(const struct jpeg_decompress_struct *cinfo)
{
   JPEG_API_MODULE_DEFINE_HANDLE();

   /**<-- decode out to yuv semi-planer  >**/
   /**<-- 解码输出yuv semi planer >**/
   if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
   {
       if (HI_TRUE != pJpegHandle->bOutUsrBuf)
       {
         ERREXIT(cinfo, JERR_OUT_MEM_NULL);
       }

       if (0 == pJpegHandle->stOutSurface.u32OutPhy[0])
       {
          ERREXIT(cinfo, JERR_OUT_MEM_NULL);
       }

       if ((JPEG_FMT_YUV400 != pJpegHandle->enImageFmt) && (0 == pJpegHandle->stOutSurface.u32OutPhy[1]))
       {
          ERREXIT(cinfo, JERR_OUT_MEM_NULL);
       }

       return;
   }

   /**<-- decode out to xrgb  >**/
   /**<-- 解码输出xrgb >**/
   if (HI_TRUE != pJpegHandle->bOutUsrBuf)
   {
       return;
   }

   if (0 == pJpegHandle->stOutSurface.u32OutPhy[0])
   {
      ERREXIT(cinfo, JERR_OUT_MEM_NULL);
   }

   return;
}
