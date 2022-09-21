/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hi_jpeg_api.h
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : The user will use this api to realize some function
Function List   :


History           :
Date                            Author                    Modification
2017/07/05                   sdk                       Created file
******************************************************************************/

#ifndef __HI_JPEG_API_H__
#define __HI_JPEG_API_H__


/*********************************add include here******************************/

#include "jpeglib.h"
#include "hi_type.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

     /***************************** Macro Definition ******************************/
     /** \addtogroup      JPEG */
     /** @{ */    /** <!--[JPEG]*/

     /** Maximum number of data components */
     /** CNcomment:最大数据分量数 CNend */
     #define MAX_PIXEL_COMPONENT_NUM            3

     /** @} */  /** <!-- ==== Macro Definition end ==== */

     /*************************** Enum Definition ****************************/
     /****************************************************************************/
     /*                               jpeg enum                                    */
     /****************************************************************************/

    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /** enum of the input jpeg color space */
    /** CNcomment:输入的jpeg图片格式 CNend */
    typedef enum hiHI_JPEG_FMT_E
    {
        JPEG_FMT_YUV400 = 0,
        JPEG_FMT_YUV420,
        JPEG_FMT_YUV422_21,
        JPEG_FMT_YUV422_12,
        JPEG_FMT_YUV444,
        JPEG_FMT_BUTT
    }HI_JPEG_FMT_E;

    /** @} */  /** <!-- ==== enum Definition end ==== */

    /*************************** Structure Definition ****************************/
    /****************************************************************************/
    /*                               jpeg api structure                            */
    /****************************************************************************/

    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /** Structure of Rectangle */
    /** CNcomment:矩形 CNend */
    typedef struct hiJPEG_RECT_S
    {
        HI_U32 x, y;
        HI_U32 w, h;
    }HI_JPEG_RECT_S;

    /** Structure of the output yuvsp/rgb/yuv package message, only support 1/2/4/8/ scale */
    /** CNcomment:设置输出yuvsp/rgb/yuv pacekage 的相关信息，只支持1/2/4/8缩放 CNend */
    typedef struct hiJPEG_SURFACE_S
    {
         HI_U32   u32OutPhy[MAX_PIXEL_COMPONENT_NUM];    /**< output physic address,0 is luminance or rgb buf, 1 is chroma buf    *//**<CNcomment:输出物理地址，0分量输出y或者rgb地址，1分量为色度地址 CNend     */
         HI_CHAR* pOutVir[MAX_PIXEL_COMPONENT_NUM];      /**< output virtual address,0 is luminance or rgb buf, 1 is chroma buf   *//**<CNcomment:输出虚拟地址，0分量输出y或者rgb地址，1分量为色度地址 CNend     */
         HI_U32   u32OutStride[MAX_PIXEL_COMPONENT_NUM]; /**< output stride                     *//**<CNcomment:输出行间距 CNend      */
    }HI_JPEG_SURFACE_S;

    /** Structure of the input and output jpeg width and height,input jpeg format */
    /** CNcomment:jpeg文件的原始大小以及解码输出大小，原始图片格式 CNend */
    typedef struct hiJPEG_INFO_S
    {
         HI_BOOL bOutInfo; /**< false is get input information and the other get output information   *//**<CNcomment:FALSE获取输入信息，TRUE获取输出信息 CNend */
         HI_U32  u32Width[MAX_PIXEL_COMPONENT_NUM];     /**< 0 input and output rgb width and lu width,1 is ch width               *//**<CNcomment:0输入和解码输出rgb图片宽度或者解码yuvsp亮度宽度，1为色度宽度 CNend          */
         HI_U32  u32Height[MAX_PIXEL_COMPONENT_NUM];    /**< 0 input and output rgb height and lu height,1 is ch height            *//**<CNcomment:0输入和解码输出rgb图片高度或者解码yuvsp亮度高度，1为色度高度 CNend          */
         HI_U32  u32McuHeight[MAX_PIXEL_COMPONENT_NUM]; /**< 0 input and output rgb height and lu height mcu align,1 is ch height  *//**<CNcomment:0输入和解码输出rgb图片高度或者解码yuvsp亮度高度，MCU对齐，1为色度高度 CNend */
         HI_U32  u32OutStride[MAX_PIXEL_COMPONENT_NUM]; /**< 0 output rgb stride and lu stride,1 is ch stride                      *//**<CNcomment:0解码输出rgb或yubsp的亮度行间距，1为色度行间距离 CNend                      */
         HI_U32  u32OutSize[MAX_PIXEL_COMPONENT_NUM];   /**< 0 output rgb size and lu size,1 is ch size                               *//**<CNcomment:0解码输出rgb或yubsp的大小，1为色度大小 CNend                                   */
         HI_JPEG_FMT_E enFmt;  /**< the input format  *//**<CNcomment:输入的图片格式 CNend      */
    }HI_JPEG_INFO_S;

    typedef struct hiJPEG_INPUT_DATA_BUF_INFO_S
    {
       HI_BOOL BeginReadToInputDataBuf ;  /**<-- check whether can read input data to data buffer >**/
       HI_VOID *pInputDataVirBuf;         /**<-- input data virtual buffer   >**/
       HI_U32 InputDataPhyBuf;            /**<-- input data physical buffer >**/
       HI_U32 InputDataBufSize;           /**<-- input data buffer size       >**/
    }HI_JPEG_INPUT_DATA_BUF_INFO_S;

    /** @} */  /** <!-- ==== Structure Definition End ==== */

    /********************** Global Variable declaration **************************/

    /******************************* API declaration *****************************/


    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /**
       \brief get input data buffer information. CNcomment:获取输入码流buffer 信息 CNend
       \attention \n
        at fill input buffer function, before read data to which buffer, can call this function\n
       CNcomment:在填充码流的时候，可以通过该函数判断可以往哪里写输入码流CNend\n

       \param[in]    cinfo. CNcomment:解码对象 CNend
       \param[in]    *pInputDataBufInfo. CNcomment:输入码流buffer 信息CNend

       \retval ::NA

       \see \n
       ::HI_JPEG_GetInputDataBufInfo
       */
    HI_VOID HI_JPEG_GetInputDataBufInfo(const struct jpeg_decompress_struct *cinfo, HI_JPEG_INPUT_DATA_BUF_INFO_S *pInputDataBufInfo);


    /**
       \brief enable read data to input data buffer, that decode no need cpy data again. CNcomment:使能往码流buffer 读数据，解码的时候不需要再拷贝CNend
       \attention \n
        after fill input buffer function, can call this function\n
       CNcomment:在填充完码流的时候，使能是否往码流buffer 读数据CNend\n

       \param[in]    cinfo. CNcomment:解码对象 CNend
       \param[in]    BeginReadDataToInputDataBuf. CNcomment:是否往码流buffer 读数据CNend

       \retval ::NA

       \see \n
       ::HI_JPEG_EnReadDataToInputDataBuf
       */
    HI_VOID HI_JPEG_EnReadDataToInputDataBuf(const struct jpeg_decompress_struct *cinfo, HI_BOOL EnReadToInputDataBuf);


    /**
       \brief exit jpeg decode. CNcomment:退出jpeg 解码CNend
       \attention \n
        when you want not to decode, call this function\n
       CNcomment:设置是否退出解码CNend\n

       \param[in]    cinfo. CNcomment:解码对象 CNend

       \retval ::NA

       \see \n
       ::HI_JPEG_StopDec
       */
    HI_VOID HI_JPEG_StopDec(const struct jpeg_decompress_struct *cinfo);

     /**
        \brief set stream mem information. CNcomment:设置码流内存信息 CNend
        \attention \n
         if want to use this function,should call after jpeg_stdio_src or jpeg_mem_src\n
        CNcomment:如果要调用，必须在关联码流之后调 CNend\n

        \param[in]    cinfo. CNcomment:解码对象 CNend
        \param[in]    StreamPhyAddr.    CNcomment:码流buffer 内存池起始物理地址 CNend
        \param[in]    StremBufSize.       CNcomment:码流buffer 内存池大小                         CNend
        \param[in]    pStreamVirBuf.      CNcomment:码流buffer 内存池起始虚拟地址，也是码流回绕的第二块地址CNend
        \param[in]    SecondStreamBufSize.    CNcomment: 第二块码流buffer 大小 CNend

        \retval ::NA

        \see \n
        ::HI_JPEG_SetStreamBufInfo
        */
     HI_VOID HI_JPEG_SetStreamBufInfo(const struct jpeg_decompress_struct *cinfo,HI_U32 StreamPhyAddr,HI_U32 StremBufSize,HI_CHAR* pStreamVirBuf, HI_U32 SecondStreamBufSize);


     /**
        \brief set decode crop rect. CNcomment:设置裁剪区域 CNend
        \attention \n
        HI_JPEG_SetCropRect should have called after jpeg_crop_scanline\n
        CNcomment:在调用jpeg_crop_scanline  之后调用 CNend\n

        \param[in]    cinfo. CNcomment:解码对象 CNend
        \param[in]    *pstCropRect. CNcomment:解码输出区域 CNend

        \retval ::NA

        \see \n
        ::HI_JPEG_SetOutDesc
        */
     HI_VOID HI_JPEG_SetCropRect(const struct jpeg_decompress_struct *cinfo, const HI_JPEG_RECT_S *pstCropRect);

    /**
    \brief Sets dec output message. CNcomment:设置解码输出的信息上下文 CNend
    \attention \n
    HI_JPEG_SetOutDesc should have called create jpeg decoder.set the output address \n
    and output stride,set whether crop, set crop rect \n
    CNcomment:必须在创建解码器之后，启动解码之前调用该接口，主要设置解码输出地址和输出 \n
              行间距，设置是否裁剪以及对应的裁剪区域 CNend\n

    \param[in]    cinfo. CNcomment:解码对象 CNend
    \param[in]    *pstSurfaceDesc. CNcomment:解码输出描述信息 CNend

    \retval ::HI_SUCCESS
    \retval ::HI_FAILURE

    \see \n
    ::HI_JPEG_SetOutDesc
    */
    HI_S32    HI_JPEG_SetOutDesc(const struct jpeg_decompress_struct *cinfo, const HI_JPEG_SURFACE_S *pstSurfaceDesc);

    /**
    \brief Get Jpeg information. CNcomment:获取jpeg图片信息 CNend
    \attention \n
    if you want to get input format and input width and input height,you should set bOutInfo false.\n
    others you can get the information as follows: output rgb widht/height/stride/size or output \n
    yuvsp lu width/height/stride/size and ch width/height/stride/size.\n
    you call this function should after read header and set the ouput parameter.\n
    CNcomment:当bOutInfo设置成FALSE的时候，可以获取到图片输入的宽度和高度以及像素格式，当设置成TRUE的 \n
              时候则可以获取到如下信息，要是解码RGB则获取到宽度/高度/行间距/大小,要是解码输出yuvsp，\n
              则可以获取的亮度和色度的宽度/高度/行间距/大小的信息。 CNend\n

    \param[in]    cinfo. CNcomment:解码对象 CNend
    \param[out]    pJpegInfo.  CNcomment:解码jpeg的相关信息  CNend

    \retval ::HI_SUCCESS
    \retval ::HI_FAILURE

    \see \n
    ::HI_JPEG_GetJpegInfo
    */
    HI_S32  HI_JPEG_GetJpegInfo(j_decompress_ptr cinfo, HI_JPEG_INFO_S *pJpegInfo);

    /**
    \brief get lu pixle sum value. CNcomment:获取亮度值 CNend
    \attention \n
    If you want to get the luminance value, you can call this function, \n
    but you should call it after jpeg_start_decompress and have call HI_JPEG_SetLuPixSumFlag.\n
    CNcomment:要是想得到亮度值，可以调用该函数，但必须在jpeg_start_decompress之后调用而且解码 \n
              之前要调用HI_JPEG_SetLuPixSumFlag CNend\n

    \param[in]    cinfo. CNcomment:解码对象 CNend
    \param[out]    u64LuPixSum. CNcomment:输出亮度值 CNend

    \retval ::HI_SUCCESS
    \retval ::HI_FAILURE

    \see \n
    ::HI_JPEG_GetLuPixSum
    */
    HI_S32 HI_JPEG_GetLuPixSum(const struct jpeg_decompress_struct *cinfo,HI_U64 *u64LuPixSum);

    /**
        \brief set low delay information. CNcomment:设置低延迟信息 CNend
        \attention the s32LineNum value should in [1 ~ output height]\n
        NA.\n
        CNcomment:CNend\n

        \param[in]    cinfo.         CNcomment:解码对象                     CNend
        \param[in]    u32PhyLineBuf. CNcomment:保存行号连续地址             CNend
        \param[in]    pVirLineBuf.   CNcomment:保存行号虚拟地址             CNend

        \retval ::HI_SUCCESS
        \retval ::HI_FAILURE

        \see \n
        ::HI_JPEG_SetLowDelayInf
        */
    HI_S32 HI_JPEG_SetLowDelayInf(const struct jpeg_decompress_struct *cinfo, HI_U32 u32PhyLineBuf, HI_CHAR* pVirLineBuf);


    /** @} */  /** <!-- ==== API Declaration End ==== */

    /****************************************************************************/


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __HI_JPEG_API_H__*/
