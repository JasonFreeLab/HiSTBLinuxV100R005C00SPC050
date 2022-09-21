/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dcoloryuvsp.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : output yuv semi-planer
                        解码输出yuv semi-planer 格式，这个文件变量的定义
                        要和开源保准保持一致，否则无法正常使用。
Function List   :

History           :
Date                          Author                    Modification
2017/03/16           sdk              Created file
******************************************************************************/


/****************************  add include here     *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "hi_jpeg_checkpara.h"
#include "hi_jpeg_config.h"
#include "hi_gfx_sys.h"

#include "jpeg_hdec_api.h"

/***************************** Macro Definition     ********************************/
#define JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS()   \
        JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;  \
        pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);\
        if (NULL == pJpegHandle)\
        {\
           ERREXIT(cinfo, JERR_NULL_POINT);\
        }

#define JPEG_CHECK_WHETHER_SUPPORT_OUT_YUV400(jpeg_color_space) \
        if (JCS_GRAYSCALE != jpeg_color_space)\
        {\
            ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);\
        }

#define JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(jpeg_color_space) \
        if (JCS_YCbCr != jpeg_color_space)\
        {\
            ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);\
        }

#define JPEG_CHECK_BUFFER_NULL_POINT_EXIT(Buffer) \
        if (NULL == Buffer)\
        {\
            ERREXIT(cinfo, JERR_NULL_POINT);\
        }

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/
static inline HI_VOID JPEG_SDEC_OutY (j_decompress_ptr cinfo, JSAMPROW InputYBuf);
static inline HI_VOID JPEG_SDEC_OutWholeCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_OutHalfRowCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_OutHalfColCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_OutHalfRowColCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_CheckYUVSPBuf(j_decompress_ptr cinfo);


/**********************       API realization       ***********************************/
/*****************************************************************************
* func              : JPEG_SDEC_OutYuv400Sp
* description    :  decode output yuv400 semi-planer
                          CNcomment:解码输出yuv400 semi-planer，
                          这里变量的定义要和开源保准保持一致CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* param[in]     : input_buf      CNcomment: yuv  数据               CNend\n
* param[ou]    : output_buf   CNcomment:输出buffer               CNend\n
* param[in]     : num_rows    CNcomment: 一次性输入的码流行数CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static HI_VOID JPEG_SDEC_YUV400_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    register JSAMPROW Inptr = NULL;

    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr = input_buf[0][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr);
    }

    return;
}

static HI_VOID JPEG_SDEC_YUV444_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;

    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);

       if (HI_TRUE == pJpegHandle->bOutYUV420SP)
       {
          JPEG_SDEC_OutHalfRowColCbCr(cinfo, Inptr2, Inptr1);
          continue;
       }

       JPEG_SDEC_OutWholeCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}


static HI_VOID JPEG_SDEC_YUV420_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;

    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);
       JPEG_SDEC_OutHalfRowCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}


static HI_VOID JPEG_SDEC_YUV42212_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();
    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);

       if (HI_TRUE == pJpegHandle->bOutYUV420SP)
       {
          JPEG_SDEC_OutHalfRowColCbCr(cinfo, Inptr2, Inptr1);
          return;
       }
       JPEG_SDEC_OutHalfColCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}


static HI_VOID JPEG_SDEC_YUV42221_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;

    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);
       JPEG_SDEC_OutHalfRowCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}

static inline HI_VOID JPEG_SDEC_OutY (j_decompress_ptr cinfo, JSAMPROW InputYBuf)
{
    register HI_CHAR* OutYBuf = NULL;
    register HI_U32 OutYBufOffset = 0;
    register HI_U32 Col = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();
    JPEG_CHECK_BUFFER_NULL_POINT_EXIT(pJpegHandle->stOutSurface.pOutVir[0]);

    OutYBuf = pJpegHandle->stOutSurface.pOutVir[0];
    OutYBufOffset = (pJpegHandle->stOutSurface.u32OutStride[0]) * cinfo->output_scanline;

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
       OutYBuf[OutYBufOffset + Col] = GETJSAMPLE(InputYBuf[Col]);
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
       pJpegHandle->u64LuPixValue += OutYBuf[OutYBufOffset + Col];
#endif
    }

    return;
}

static inline HI_VOID JPEG_SDEC_OutWholeCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    register HI_CHAR* OutCbCrBuf = NULL;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();
    JPEG_CHECK_BUFFER_NULL_POINT_EXIT(pJpegHandle->stOutSurface.pOutVir[1]);

    OutCbCrBuf = pJpegHandle->stOutSurface.pOutVir[1];
    OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * cinfo->output_scanline;

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col]   = GETJSAMPLE(InputCbBuf[Col]);
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col + 1] = GETJSAMPLE(InputCrBuf[Col]);
    }

     return;
}

static inline HI_VOID JPEG_SDEC_OutHalfRowColCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    register HI_CHAR* OutCbCrBuf = NULL;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;
    register HI_U32 HasBeenReadSize = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();
    JPEG_CHECK_BUFFER_NULL_POINT_EXIT(pJpegHandle->stOutSurface.pOutVir[1]);

    OutCbCrBuf = pJpegHandle->stOutSurface.pOutVir[1];
    OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * (cinfo->output_scanline / 2);

    if (0 != cinfo->output_scanline % 2)
	{
       return;
	}

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
        if (0 != Col % 2)
        {
           continue;
        }

        OutCbCrBuf[OutCbCrBufOffset + 2 * HasBeenReadSize]   = GETJSAMPLE(InputCbBuf[Col]);
        OutCbCrBuf[OutCbCrBufOffset + 2 * HasBeenReadSize + 1] = GETJSAMPLE(InputCrBuf[Col]);
        HasBeenReadSize++;
    }


    return;
}


static inline HI_VOID JPEG_SDEC_OutHalfRowCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    register HI_CHAR* OutCbCrBuf = NULL;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();
    JPEG_CHECK_BUFFER_NULL_POINT_EXIT(pJpegHandle->stOutSurface.pOutVir[1]);

    OutCbCrBuf = pJpegHandle->stOutSurface.pOutVir[1];

    if ((HI_TRUE == pJpegHandle->bOutYUV420SP) || (JPEG_FMT_YUV420 == pJpegHandle->enImageFmt))
    {
        OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * (cinfo->output_scanline / 2);
    }
    else
    {
         OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * cinfo->output_scanline;
    }

    if ((0 != cinfo->output_scanline % 2) && ((HI_TRUE == pJpegHandle->bOutYUV420SP) || (JPEG_FMT_YUV420 == pJpegHandle->enImageFmt)))
	{
       return;
	}

    for (Col = 0; Col < cinfo->output_width; Col += 2)
    {
       OutCbCrBuf[OutCbCrBufOffset + Col] = GETJSAMPLE(InputCbBuf[Col]);
    }

    for (Col = 1; Col < cinfo->output_width; Col += 2)
    {
       OutCbCrBuf[OutCbCrBufOffset + Col] = GETJSAMPLE(InputCrBuf[Col]);
    }

    return;
}


static inline HI_VOID JPEG_SDEC_OutHalfColCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    register HI_CHAR* OutCbCrBuf = NULL;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();
    JPEG_CHECK_BUFFER_NULL_POINT_EXIT(pJpegHandle->stOutSurface.pOutVir[1]);

    OutCbCrBuf = pJpegHandle->stOutSurface.pOutVir[1];
    OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * (cinfo->output_scanline / 2);

    if (0 != cinfo->output_scanline % 2)
	{
	    return;
	}

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col] = GETJSAMPLE(InputCbBuf[Col]);
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col + 1] = GETJSAMPLE(InputCrBuf[Col]);
    }

     return;
}


/*****************************************************************************
* func              : JPEG_SDEC_InitOutToYuv420Sp
* description    : decode output yuv420 semi-planer
                          CNcomment:解码输出格式统一为yuv420 semi-planer CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : HI_SUCCESS 解码输出yuv420sp
* retval           : HI_FAILURE   不支持解码输出yuv420sp
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitOutToYuv420Sp (j_decompress_ptr cinfo)
{
    my_cconvert_ptr cconvert;
    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FAILURE);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    cinfo->out_color_components = cinfo->num_components;
    cinfo->output_components = (TRUE == cinfo->quantize_colors) ? (1) : (cinfo->out_color_components);
    cconvert = (my_cconvert_ptr)cinfo->cconvert;

    if (HI_TRUE != pJpegHandle->bOutYUV420SP)
    {
       return HI_FAILURE;
    }

    if (JPEG_FMT_YUV400 == pJpegHandle->enImageFmt)
    {
       JPEG_CHECK_WHETHER_SUPPORT_OUT_YUV400(cinfo->jpeg_color_space);
       cconvert->pub.color_convert = JPEG_SDEC_YUV400_TO_YUVSp;
       return HI_SUCCESS;
    }

    switch (pJpegHandle->enImageFmt)
    {
      case JPEG_FMT_YUV444:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV444_TO_YUVSp;
           break;

      case JPEG_FMT_YUV420:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV420_TO_YUVSp;
           break;

      case JPEG_FMT_YUV422_21:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42221_TO_YUVSp;
           break;

      case JPEG_FMT_YUV422_12:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42212_TO_YUVSp;
           break;

      default:
           if (HI_TRUE == pJpegHandle->bOutYUV420SP)
           {
              ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
           }
           break;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* func              : JPEG_SDEC_InitOutToYuvSp
* description    : decode output yuv semi-planer
                          CNcomment:解码输出格式为yuv semi-planer CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitOutToYuvSp (j_decompress_ptr cinfo)
{
    my_cconvert_ptr cconvert;

    CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FAILURE);
    JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    cinfo->out_color_components = cinfo->num_components;
    cinfo->output_components = (TRUE == cinfo->quantize_colors) ? (1) : (cinfo->out_color_components);
    cconvert = (my_cconvert_ptr)cinfo->cconvert;

    if (JCS_YUV400_SP == cinfo->out_color_space)
    {
       JPEG_SDEC_CheckYUVSPBuf(cinfo);
       JPEG_CHECK_WHETHER_SUPPORT_OUT_YUV400(cinfo->jpeg_color_space);
       cconvert->pub.color_convert = JPEG_SDEC_YUV400_TO_YUVSp;
       return HI_SUCCESS;
    }

    switch (cinfo->out_color_space)
    {
      case JCS_YUV444_SP:
            JPEG_SDEC_CheckYUVSPBuf(cinfo);
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV444_TO_YUVSp;
           break;

      case JCS_YUV420_SP:
           JPEG_SDEC_CheckYUVSPBuf(cinfo);
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV420_TO_YUVSp;
           break;

      case JCS_YUV422_SP_21:
           JPEG_SDEC_CheckYUVSPBuf(cinfo);
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42221_TO_YUVSp;
           break;

      case JCS_YUV422_SP_12:
           JPEG_SDEC_CheckYUVSPBuf(cinfo);
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42212_TO_YUVSp;
           break;

      default:
           return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static inline HI_VOID JPEG_SDEC_CheckYUVSPBuf(j_decompress_ptr cinfo)
{
   CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
   JPEG_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

   if (HI_TRUE != pJpegHandle->bOutYCbCrSP)
   {
      return;
   }

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
