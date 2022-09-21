/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hi_drv_jpeg.h
Version           : Initial Draft
Author            : sdk
Created          : 2017/07/05
Description     :
Function List   :


History          :
Date                   Author                Modification
2017/07/05          sdk                   Created file
******************************************************************************/

#ifndef __HI_DRV_JPEG_H__
#define __HI_DRV_JPEG_H__


/***************************** add include here*********************************/
#include "hi_type.h"


/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ********************************/
    #define VID_CMD_MAGIC     'j'



    #define CMD_JPG_GETDEVICE                  _IO(VID_CMD_MAGIC,   0)
    #define CMD_JPG_GETSUSPEND                 _IO(VID_CMD_MAGIC,   1)
    #define CMD_JPG_GETRESUME                  _IO(VID_CMD_MAGIC,   2)

    #define CMD_JPG_RESET                      _IO(VID_CMD_MAGIC,   3)
    #define CMD_JPG_CANCEL_RESET               _IO(VID_CMD_MAGIC,   4)

#ifdef CHIP_TYPE_X5HD_hi3716m
    #define CMD_JPG_GETINTSTATUS               _IOWR(VID_CMD_MAGIC, 5,  JPEG_GETINTTYPE_S*)
#else
    #define CMD_JPG_GETINTSTATUS               _IOWR(VID_CMD_MAGIC, 5,  JPEG_GETINTTYPE_S)
#endif
    #define CMD_JPG_GETRESUMEVALUE             _IOWR(VID_CMD_MAGIC, 6,  HI_JPG_SAVEINFO_S)

    #define CMD_JPG_READPROC                   _IOWR(VID_CMD_MAGIC, 7,  HI_JPEG_PROC_INFO_S)

    #define CMD_JPG_LOWDELAY_LINEINFO          _IOWR(VID_CMD_MAGIC, 8, HI_JPEG_OUTPUTINFO_S)
    #define CMD_JPG_COMPAT_LOWDELAY_LINEINFO   _IOWR(VID_CMD_MAGIC, 8, HI_JPEG_COMPAT_OUTPUTINFO_S)

    #define CMD_JPG_GETINFLEXION               _IOWR(VID_CMD_MAGIC, 9, HI_U32)

    #define MAX_COMPONENT_NUM                 3
    #define JPEG_INTTYPE_DELAY_TIME           10000 /** 10s **/

    /***************************** Structure Definition ****************************/
    typedef enum hiJPEG_INTTYPE_E{
        JPG_INTTYPE_NONE       = 0,
        JPG_INTTYPE_CONTINUE,
        JPG_INTTYPE_LOWDEALY,
        JPG_INTTYPE_FINISH,
        JPG_INTTYPE_ERROR,
        JPG_INTTYPE_STREAM_ERROR,
        JPG_INTTYPE_BUTT
    }JPEG_INTTYPE_E;

    typedef enum hiJPEG_FMT_E{
        JPG_FMT_YUV400         = 0,
        JPG_FMT_YUV420         = 1,
        JPG_FMT_YUV422_21      = 2,
        JPG_FMT_YUV422_12      = 3,
        JPG_FMT_YUV444         = 4,
        JPG_FMT_YCCK           = 5,
        JPG_FMT_CMYK           = 6,
        JPG_FMT_BUTT
    }JPEG_FMT_E;

    typedef struct tagJPEG_RECT_S
    {
        HI_U32 x, y;
        HI_U32 w, h;
    }JPEG_RECT_S;

    typedef struct hiJPEG_GETINTTYPE_S
    {
        HI_U32 TimeOut;
        JPEG_INTTYPE_E IntType;
    }JPEG_GETINTTYPE_S;

    typedef struct hiJPG_SAVEINFO_S{
        HI_U32  u32ResumeData0;
        HI_U32  u32ResumeData1;
        HI_U32  u32ResBitRemain;
        HI_U32  u32ResByteConsu;
        HI_U32  u32ResMcuy;
        HI_U32  u32Pdy;
        HI_U32  u32Pdcbcr;
        HI_U32  u32DriCnt;
    }HI_JPG_SAVEINFO_S;

    typedef struct hiJPEG_PROC_INFO_S{
         HI_BOOL bSeekToSoftDec;   /**<-- seek to soft decode   >**//**<-- 回退到软件解码>**/
         HI_BOOL bHardDec;         /**<-- whether hard decode    >**//**<-- 是否为硬件解码 >**/
         HI_U32 CurOffset;         /**<-- current offset that will seek >**//**<-- 要回退的当前位置>**/
         HI_U32 SkipScanLines;     /**<-- skip scan lines >**//**<-- 丢弃了多少行 >**/
         HI_U32 HardDecTimes;      /**<-- hard decode cost times >**//**<-- 硬件解码所花费的时间 >**/
         HI_U32 DecCostTimes;      /**<-- decode cost times       >**//**<-- 解码当前帧所花费的时间 >**/
         HI_U32 DecInflexion;      /**<-- hard or soft decode inflexion  >**//**<-- 软件硬件解码的拐点  >**/
         HI_U32 u32YWidth;         /**<-- the lu width       >**//**<-- 亮度宽宽度 >**/
         HI_U32 u32YHeight;        /**<-- the lu height      >**//**<-- 亮度高度       >**/
         HI_U32 u32YSize;          /**<-- the lu size         >**//**<-- :亮度大小      >**/
         HI_U32 u32CWidth;         /**<-- the ch width      >**//**<-- 色度宽度       >**/
         HI_U32 u32CHeight;        /**<--  the ch height    >**//**<-- 色度高度       >**/
         HI_U32 u32CSize;          /**<-- the ch size        >**//**<-- 色度大小        >**/
         HI_U32 u32YStride;        /**<-- the lu stride      >**//**<-- :亮度行间距 >**/
         HI_U32 u32CbCrStride;     /**<-- the ch stride     >**//**<-- 色度行间距  > **/
         HI_U32 StartStreamBuf;    /**<-- the stream start address     >**//**<-- 码流buffer起始地址，要64字节对齐      >**/
         HI_U32 EndStreamBuf;      /**<-- the stream end address       >**//**<-- 码流buffer结束地址，要64字节对齐      >**/
         HI_U32 StartSaveDataBuf;  /**<-- the save data start address  >**//**<-- 存储码流的起始地址(在码流地址区域内)  >**/
         HI_U32 EndSaveDataBuf;    /**<-- the save data end address    >**//**<-- 存储码流的结束地址(在码流地址区域内)  >**/
         HI_U32 ImageWidth;        /**<-- the input widht             >**//**<-- 输入宽度           >**/
         HI_U32 ImageHeight;       /**<-- the input height            >**//**<-- 输入高度           >**/
         HI_U32 OutputWidth;       /**<-- decode output width    >**//**<-- 解码输出宽度>**/
         HI_U32 OutputHeight;      /**<--decode output height    >**//**<-- 解码输出高度>**/
         HI_U32 OutputStride;      /**<--decode output stride     >**//**<-- 输出行间距      >**/
         HI_U32 ImageFmt;          /**<-- the input format           >**//**<-- 输入像素格式>**/
         HI_U32 OutputFmt;         /**<-- the output format        >**//**<-- 输出像素格式>**/
         HI_U32 OutputLuPhyBuf;    /**<-- output lu physics address  >**//**<-- 亮度输出物理地址 >**/
         HI_U32 OutputChPhyBuf;    /**<-- output ch physics address  >**//**<-- 色度输出物理地址 >**/
         HI_U32 ScaleTimes;        /**<-- decode scale times            >**//**<-- 解码缩放倍数 >**/
         HI_U32 DecPthreadNums;    /**<-- decode pthread numbers   >**//**<-- 当前解码线程数>**/
         HI_S32 DecLockTimes;      /**<-- decode has been lock times  >**//**<-- 当前解码被锁的次数>**/
         HI_S32 OpenDevConTimes;   /**<-- open dev continue times       >**//**<-- 设备已经被连续打开的次数>**/
         JPEG_RECT_S stCropRect;   /**<-- crop rect       >**//**<-- 裁剪区域>**/
    }HI_JPEG_PROC_INFO_S;


    typedef struct tagJPEG_INMSG_S{
         HI_U32     u32AllPhy;         /**<--  整块码流buffer的起始物理地址>**/
         HI_U32     u32SavePhy;        /**<--  第一块存码流的物理地址         >**/
         HI_U64     u64SaveVir[2];     /**<--  存码流的虚拟地址，第二块虚拟地址和整块码流buffer的物理地址对应 >**/
         HI_U32     u32AllLen;         /**<--  整块码流buffer的长度            > **/
         HI_U32     u32SaveLen[2];     /**<--  存码流的两个buffer的大小>**/
         HI_U32     s32InWidth;        /**<--  输入图像宽           >**/
         HI_U32     s32InHeight;       /**<--  输入图像高           >**/
         HI_U32     DecHandle;         /**<--  解码器                       >**/
         HI_BOOL    bUserPhyMem;       /**<--  是否传入的为物理地址  >**/
         JPEG_FMT_E  enInFmt;          /**<--  输入图像像素格式             >**/
    }HI_DRV_JPEG_INMSG_S;

    typedef struct tagJPEG_OUTMSG_S{
         HI_U32      u32OutPhy[MAX_COMPONENT_NUM];
         HI_U32      u32OutVir[MAX_COMPONENT_NUM];
         HI_U32      u32OutWidth[MAX_COMPONENT_NUM];
         HI_U32      u32OutHeight[MAX_COMPONENT_NUM];
         HI_U32      u32OutStride[MAX_COMPONENT_NUM];
         HI_U32      u32OutSize[MAX_COMPONENT_NUM];
         HI_S32      s32Scale;
         HI_U32      DecHandle;
         HI_U64      u64LuPixValue;
         HI_BOOL     bOutYuvSp420;
         HI_BOOL     bLuPixSum;
         JPEG_FMT_E  enOutFmt;
    }HI_DRV_JPEG_OUTMSG_S;

    typedef struct hiJPEG_DECINFO_S{
         HI_DRV_JPEG_INMSG_S  stInMsg;
         HI_DRV_JPEG_OUTMSG_S stOutMsg;
    }HI_JPEG_DECINFO_S;


    typedef struct hiJPEG_OUTPUTINFO_S{
         HI_CHAR* pVirLineBuf;
         HI_U32 u32OutHeight[MAX_COMPONENT_NUM];
    }HI_JPEG_OUTPUTINFO_S;

    typedef struct hiJPEG_COMPAT_OUTPUTINFO_S{
         HI_U32 u32VirLineBuf;
         HI_U32 u32OutHeight[MAX_COMPONENT_NUM];
    }HI_JPEG_COMPAT_OUTPUTINFO_S;

    /***************************** Global Variable declaration *********************/

    /***************************** API forward declarations ************************/

    /***************************** API realization *********************************/
    HI_S32 HI_DRV_JPEG_CreateDec(HI_U32 *pDecHandle);

    HI_S32 HI_DRV_JPEG_DecInfo(HI_U32 DecHandle,HI_DRV_JPEG_INMSG_S *stInMsg);

    HI_S32 HI_DRV_JPEG_DecOutInfo(HI_U32 DecHandle,HI_DRV_JPEG_OUTMSG_S *stOutMsg);

    HI_S32 HI_DRV_JPEG_DecFrame(HI_U32 DecHandle,HI_JPEG_DECINFO_S *pstDecInfo);

    HI_VOID HI_DRV_JPEG_DestoryDec(HI_U32 DecHandle);

    HI_VOID HI_DRV_JPEG_GetLuPixSum(HI_U32 DecHandle,HI_U64* pu64LuPixValue);

    /****************************************************************************/


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __HI_DRV_JPEG_H__*/
