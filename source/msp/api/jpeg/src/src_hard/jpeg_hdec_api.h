/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_mem.h
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     :
Function List   :


History           :
Date                      Author           Modification
2017/07/05            sdk              Created file
******************************************************************************/
#ifndef __JPEG_HDEC_API_H__
#define __JPEG_HDEC_API_H__


/*********************************add include here********************************/
#include  "jpeglib.h"

#include  "hi_jpeg_config.h"
#include  "hi_jpeg_api.h"

#include  "hi_drv_jpeg.h"
#include  "jpeg_hdec_rwreg.h"

#ifdef CONFIG_JPEG_EXIF_SUPPORT
#include "jpeg_sdec_exif.h"
#endif

#include "jpeg_sdec_color.h"


#ifdef CONFIG_JPEG_SAVE_SCEN
#include "hi_jpeg_reg.h"
#endif

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ******************************/
     #define CONFIG_JPEG_SCALE_MULTIPLE_8                           (3)
     #define CONFIG_JPED_INPUT_DATA_BUFFER_NUM                      (2)

     #define CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN                    (128)
     #define CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE         (128)
     #define CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE                 (256 * 1024)

     #define JPEG_API_MODULE_DEFINE_HANDLE()\
              JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;\
              pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);\
              if (NULL == pJpegHandle)\
              {\
                 ERREXIT(cinfo, JERR_NULL_POINT);\
              }
     /*************************** Enum Definition ****************************/


    /*************************** Structure Definition ****************************/
     typedef struct tatINPUT_STREAM_BUF_S
     {
         HI_BOOL UseSecondInputBuf;           /**<-- use second input buffer     >**//**<-- 是否使用第二块码流buffer >**/
         HI_BOOL SupportUserPhyInputDataBuf;  /**<-- whether user input data buffer is physical      >**//**<-- 使用用户输入的物理内存buffer 数据处理>**/
         HI_BOOL SupportUserInputBufReturn;   /**<-- check whether stream save with two buffer  >**//**<-- 支持内存回绕方式的处理 >**/
         HI_BOOL UserInputDataEof;            /**<-- check the input data whether has been read empty, file or vir mem used  >**//**<-- 是否已经读到最后码流数据>**/
         HI_CHAR *pUserSecondInputDataVirBuf; /**<-- this is second input data virtual buffer  >**//**<-- 内存回绕方式第二块码流虚拟内存>**/
         HI_CHAR *pUserFirstInputDataVirBuf;  /**<-- this is first input data virtual buffer or input data start virtual buffer   >**//**<-- 第一块码流虚拟内存>**/
         HI_U32 UserInputDataPhyBuf;          /**<-- input one or pool physical buffer start address  >**//**<-- 用户输入的码流连续物理地址 >**/
         HI_ULONG UserTotalInputBufSize;      /**<-- input one or pool buffer size   >**//**<-- 用户输入的码流数据大小 >**/
         HI_ULONG UserFirstInputBufSize;      /**<-- first input data buffer size       >**//**<-- 用户输入的第一块码流数据大小>**/
         HI_ULONG UserSecondInputBufSize;     /**<-- second input data buffer size  >**//**<-- 用户输入的第二块码流数据大小 >**/
         HI_ULONG UserInputCurPos;            /**<-- the input data current position, file or vir mem used  >**//**<-- 进入硬件解码之前码流读取的位置>**/
         HI_ULONG UserDataHasBeenReadSize;    /**<-- the input data has been read size, memory return used  >**//**<-- 码流已经被读取的大小，仅在内存回绕方式使用>**/
     }INPUT_STREAM_BUF_S;

     typedef struct tagINPUT_DATA_BUF_S
     {
         HI_BOOL DecDataEof;          /**<-- check whether decode buffer is empty                  >**//**<-- 判断是否已经解码到最后一段码流 >**/
         HI_BOOL SaveStreamBufBusy;   /**<-- check whether current save stream buffer is busy  >**//**<-- 当块存储码流buffer 是否已经存有码流数据>**/
         HI_CHAR *pSaveStreamVirBuf;  /**<-- input data virtual buffer that be use to decode        >**//**<-- 存储码流buffer  虚拟地址 >**/
         HI_U32 SaveStreamPhyBuf;     /**<-- input data physical buffer that be use to decode     >**//**<-- 存储码流buffer 连续物理地址 >**/
     }INPUT_DEC_DATA_BUF_S;

     typedef struct tagJPEG_INPUT_DATA_BUF_INFO_S
     {
         HI_BOOL bUseInsideData;               /**<-- dispose stream with inside or callback  >**//**<-- 是使用回调方式还是内存数据处理方式>**/
         HI_BOOL EnReadToInputDataBuf;         /**<-- enable read input data to save stream buffer with callback used  >**//**<-- 是否需要读到存储码流buffer 中>**/
         HI_BOOL BeginReadToInputDataBuf;      /**<-- begin read input data to save stream buffer  >**//**<-- 开始读到存储码流buffer  中 >**/
         HI_U32 SaveStreamBufSize;             /**<-- input data buffer size that be use to decode  >**//**<-- 存储码流buffer  大小 >**/
         HI_U32 DecDataBufIndex;               /**<-- decode use which buffer    >**//**<-- 解码到第几块码流buffer  >**/
         HI_U32 SaveStreamBufIndex;            /**<-- save data to which buffer  >**//**<-- 已经填写到第几块存储码流buffer >**/
         INPUT_STREAM_BUF_S stInputStreamBuf;  /**<-- input data buffer infomation >**//**<-- 输入码流buffer 信息 >**/
         INPUT_DEC_DATA_BUF_S stSaveStreamBuf[CONFIG_JPED_INPUT_DATA_BUFFER_NUM]; /**<-- hard decode data buffer >**//**<-- 解码使用的存储码流buffer 信息 >**/
     }JPEG_INPUT_DATA_BUF_INFO_S;

    /** the jpeg sof information，the hard decode is only use dec para */
    /** CNcomment:jpeg大小相关信息，硬件解码只有解码分辨率的概念 */
    typedef struct tagJPEG_HDEC_SOFINFO_S
    {
         HI_BOOL bCalcSize;        /**< the jpeg size has  calculated >**//**<CNcomment:jpeg大小已经计算完了，不需要重新计算了  >**/
         HI_U32  u32YWidth;        /**< the lu width                 >**//**<CNcomment:亮度宽宽度        >**/
         HI_U32  u32YHeight;       /**< the lu height                >**//**<CNcomment:亮度高度              >**/
         HI_U32  u32YMcuHeight;    /**< the lu height,mcu align >**//**<CNcomment:亮度高度，MCU对齐>**/
         HI_U32  u32YSize;         /**< the lu size                   >**//**<CNcomment:亮度大小          >**/
         HI_U32  u32CWidth;        /**< the ch width                >**//**<CNcomment:色度宽度          >**/
         HI_U32  u32CHeight;       /**< the ch height               >**//**<CNcomment:色度高度          */
         HI_U32  u32CMcuHeight;    /**< the ch height,mcu align >**//**<CNcomment:色度高度，MCU对齐 >**/
         HI_U32  u32CSize;         /**< the ch size                   >**//**<CNcomment:色度大小          >**/
         HI_U32  u32YStride;       /**< the lu stride                 >**//**<CNcomment:亮度行间距     >**/
         HI_U32  u32CbCrStride;    /**< the ch stride                >**//**<CNcomment:色度行间距     >**/
         HI_U32  DecOutWidth;      /**< the dec width               >**//**<CNcomment:解码宽度          >**/
         HI_U32  DecOutHeight;     /**< the dec height              >**//**<CNcomment:解码高度          >**/
         HI_U32  DecOutStride;     /**< the display stride          >**//**<CNcomment:显示行间距    >**/
         HI_U32  u32InWandH;       /**< set to register size       >**//**<CNcomment:配给硬件的分辨率  >**/
         #ifdef CONFIG_JPEG_HARDDEC2ARGB
         HI_U32  u32McuWidth;      /**< the mcu width        >**/
         HI_U32  u32MINSize;       /**< the min size           >**/
         HI_U32  u32MIN1Size;      /**< the min1 size         >**/
         HI_U32  u32RGBSizeReg;    /**< set to register size >**//**<CNcomment:配给硬件寄存器的值  >**/
         #endif
    }JPEG_HDEC_SOFINFO_S;

    typedef struct tagJPEG_MIDDLE_SURFACE_S
    {
         HI_CHAR* pOutVir; /**<  csc output virtual buffer  >**//**<CNcomment:颜色空间转换输出虚拟地址   */
         HI_CHAR* DecOutVir[MAX_PIXEL_COMPONENT_NUM];  /**< jpeg hard dec output vitual  buffer   >**//**<CNcomment:jpeg 硬件解码输出虚拟地址  */
         HI_U32 DecOutPhy[MAX_PIXEL_COMPONENT_NUM];    /**< jpeg hard dec output physics buffer >**//**<CNcomment:jpeg 硬件解码输出物理地址  */
         HI_U32   OutPhy; /**<  csc output physics buffer    >**//**<CNcomment:颜色空间转换输出物理地址   */
    }JPEG_MIDDLE_SURFACE_S;

    typedef struct tagJPEG_HDEC_HANDLE_S
    {
          volatile HI_CHAR *pJpegRegVirAddr;  /**<-- mmap the jpeg virtual address  >**//**<CNcomment:jpeg映射上来的虚拟地址         >**/
          HI_BOOL bHasHufTable;
          HI_BOOL bDiscardScanlines;          /**<-- skip scan lines  >**//**<CNcomment: 丢行处理>**/
          HI_BOOL bSeekToSoftDec;             /**<-- seek to soft decode  >**//**<CNcomment: 回退到软件解码>**/
          HI_BOOL bOutUsrBuf;                 /**<-- whether out to usr buffer  >**//**<CNcomment: 是否需要解码输出用户buffer 中>**/
          HI_BOOL SupportHardDec;             /**<-- whether support hard decode  >**//**<CNcomment: 是否支持硬件解码>**/
          HI_BOOL EnStopDecode;               /**<-- whether support stop decode in decoding  >**//**<CNcomment: 是否支持解码过程中终止解码>**/
          HI_BOOL bHdecEnd;                   /**<-- hard decode success  >**//**<CNcomment:硬件解码成功>**/
          HI_BOOL bCSCEnd;                    /**<--color space convert success  >**//**<CNcomment:颜色空间转换成功 >**/
          HI_BOOL bOutYCbCrSP;                /**<--if output yuvsp  >**//**<CNcomment:是否解码输出yuv semi_planer    >**/
          HI_BOOL bDecOutColorSpaecXRGB;      /**<--the jpeg support dec to argb  >**//**<CNcomment:jpeg硬件支持解码输出ARGB        >**/
          HI_BOOL bCheckedSupportHardDec;     /**<-- has been check whether support hard decode  >**//**<CNcomment:已经判断了是否支持硬件解码>**/
          HI_BOOL bCrop;                      /**<--  if crop  >**//**<CNcomment:是否裁剪 CNend*/
          HI_BOOL bSetCropRect;               /**< -- if has been set crop rect >**//**<CNcomment: 是否配置了裁剪区域>**/
          HI_U32  u32MinPhyBuf;               /**<-- dec to argb need row buffer  >**//**<CNcomment:解码输出ARGB需要的行buffer      >**/
          HI_U32  SkipLines;                  /**<-- skip output lines >**//**<CNcomment:输出忽略的行数>**/
          #ifdef CONFIG_JPEG_SAVE_SCEN
          HI_S32  s32RegData[JPGD_REG_LENGTH];/**<--save scen>**//**<CNcomment:保存现场信息>**/
          FILE* pScenFile;
          #endif
          HI_S32  s32LuDcLen[6];              /**<-- huffman lu dc codelenght  >**//**<CNcomment:亮度DC的最长CodeLength >**/
          HI_BOOL  bOutYUV420SP;              /**<--all dec output yuv420sp     >**//**<CNcomment:统一输出yuv420sp格式 >**/
          #ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
          HI_U64   u64LuPixValue;             /**<--the lu pixle value  >**//**<CNcomment:亮度值和>**/
          #endif
          HI_U32   HardDecTimes;              /**<--hard decode cost times  >**//**<CNcomment:硬件解码花费的时间>**/
          HI_U32   DecCostTimes;              /**<--calc the decode time  >**//**<CNcomment:计算解码时间>**/
          #ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
          HI_BOOL  bLowDelayEn;
          HI_U32   u32PhyLineBuf;
          HI_CHAR* pVirLineBuf;
          #endif
          HI_S32   s32QuantTab[DCTSIZE2];
          HI_U32   u32HuffDcTab[12];
          HI_U32   u32HufAcMinTab[DCTSIZE];
          HI_U32   u32HufAcBaseTab[DCTSIZE];
          HI_U32   u32HufAcSymbolTab[256];
          HI_S32   s32ClientData; /**<--the client pointer of private structure   >***//**<CNcomment:私有结构体指针>***/
          HI_S32   JpegDev;       /**<--the jpeg device  >**//**<CNcomment:jpeg设备 >**/
          HI_S32   CscDev;
          HI_S32   MemDev;
          HI_U32   ScalRation;    /**<--the dec scale   >**//**<CNcomment:缩放比例  >**/
          HI_BOOL  bReleaseRes;   /**<--the resouce has release   >**//**<CNcomment:资源已经释放掉了>**/
          #ifdef CONFIG_GFX_MEM_ION
          HI_VOID *pSaveStreamMemHandle;
          HI_VOID *pMiddleMemHandle;
          HI_VOID *pMinMemHandle;
          HI_VOID *pOutMemHandle;
          #endif
          HI_U32 ResByteConsum; /**<--consume byte after suspend  >**//**<CNcomment:待机消耗的码流数   >**/
          HI_U8 u8Fac[MAX_PIXEL_COMPONENT_NUM][2];/**< save the sample factor   >**//**<CNcomment:保存采样因子大小 >**/
          HI_JPEG_RECT_S stCropRect; /**<-- output crop size >**//**<--输出裁剪区域 >**/
          JPEG_HDEC_SOFINFO_S  stJpegSofInfo;     /**< the jpeg sof information               >**//**<CNcomment:jpeg图片大小信息           >**/
          JPEG_INPUT_DATA_BUF_INFO_S  stInputDataBufInfo; /**< the hard decode data buffer message    >**/
          HI_JPEG_FMT_E enImageFmt; /**< jpeg picture type   >**//**<CNcomment:jpeg图片格式>**/
          HI_JPEG_SURFACE_S  stOutSurface; /**< the user output message description    >**//**<CNcomment:用户设置的输出信息描述     */
          JPEG_MIDDLE_SURFACE_S  stDecSurface;
          JPEG_SDEC_COLOR_CONVERT_S stSdecColorConvert;
          #ifdef CONFIG_JPEG_EXIF_SUPPORT
	      HI_BOOL  bExifSupport; /**<-- exif para define begine,  support exif mark >**//**<-- 开始定义exif  参数，是否支持exif >**/
	      HI_BOOL  bIsHDR;
	      HI_U8    u8ImageCount;
	      HI_CHAR* pThumbnailAddr;
	      HI_U32   u32ThumbnailSize;
          JPEG_EXIF_INFO_S  stExifInfo;
          #endif
    }JPEG_HDEC_HANDLE_S,*JPEG_HDEC_HANDLE_S_PTR;

    /********************** Global Variable declaration *****************************/

    /******************************* API declaration *****************************/

    /************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __JPEG_HDEC_API_H__*/
