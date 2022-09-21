/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dupsampleryuvsp.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : output yuv semi-planer
                        上采样输出yuv semi-planer
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
#define UPSAMPLER_CHECK_AND_DEFINE_HANDLE_PARAMETERS()   \
        JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;  \
        pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);\
        if (NULL == pJpegHandle)\
        {\
           ERREXIT(cinfo, JERR_NULL_POINT);\
        }

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
 static HI_VOID JPEG_SDEC_YUV400_UPLANER_TO_YUVSp (j_decompress_ptr cinfo,
                                                                         JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                                         JDIMENSION in_row_groups_avail,
                                                                         JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                                         JDIMENSION out_rows_avail)
{
    register HI_CHAR* OutYBuf = NULL;
    register HI_U32 OutYBufOffset = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    UPSAMPLER_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);

    *out_row_ctr = 1;

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = pJpegHandle->stOutSurface.u32OutStride[0] * cinfo->output_scanline;
    OutYBuf = pJpegHandle->stOutSurface.pOutVir[0] + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][*in_row_group_ctr], sizeof(char) * pJpegHandle->stOutSurface.u32OutStride[0]);

    (*in_row_group_ctr)++;

    return;
}


static HI_VOID JPEG_SDEC_YUV400_H2V2_UPLANER_TO_YUVSp (j_decompress_ptr cinfo,
                                                                                JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                                                JDIMENSION in_row_groups_avail,
                                                                                JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                                                JDIMENSION out_rows_avail)
{
    my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;

    register HI_CHAR* OutYBuf = NULL;
    register HI_U32 OutYBufOffset = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    UPSAMPLER_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);

    *out_row_ctr = 1;

    if (TRUE == upsample->spare_full)
    {
       upsample->spare_full = FALSE;
       return;
    }
    upsample->spare_full = TRUE;

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = pJpegHandle->stOutSurface.u32OutStride[0] * cinfo->output_scanline;
    OutYBuf = pJpegHandle->stOutSurface.pOutVir[0] + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2], sizeof(char) * pJpegHandle->stOutSurface.u32OutStride[0]);

    OutYBuf += pJpegHandle->stOutSurface.u32OutStride[0];
    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2 + 1], sizeof(char) * pJpegHandle->stOutSurface.u32OutStride[0]);

    (*in_row_group_ctr)++;

    return;
}


static HI_VOID JPEG_SDEC_YUV444_UPLANER_TO_YUVSp (j_decompress_ptr cinfo,
                                                            		     JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                            		     JDIMENSION in_row_groups_avail,
                                                            		     JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                            		     JDIMENSION out_rows_avail)
{
    HI_U32 Col = 0;

    register HI_CHAR* OutYBuf = NULL;
    register HI_U32 OutYBufOffset = 0;
    register HI_CHAR* OutCbCrBuf = NULL;
    register HI_U32 OutCbCrBufOffset = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    UPSAMPLER_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);

    *out_row_ctr = 1;

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = pJpegHandle->stOutSurface.u32OutStride[0] * cinfo->output_scanline;
    OutYBuf = pJpegHandle->stOutSurface.pOutVir[0] + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][*in_row_group_ctr], sizeof(char) * pJpegHandle->stOutSurface.u32OutStride[0]);

    /**<--out Cb Cr data >**/
    /**<-- 输出 Cb Cr  数据>**/
    OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * cinfo->output_scanline;
    OutCbCrBuf = pJpegHandle->stOutSurface.pOutVir[1] + OutCbCrBufOffset;

    for (Col = 0; Col < pJpegHandle->stOutSurface.u32OutStride[1] / 2; Col++)
    {
       OutCbCrBuf[2 * Col]   = input_buf[2][*in_row_group_ctr][Col];
       OutCbCrBuf[2 * Col + 1] = input_buf[1][*in_row_group_ctr][Col];
    }

    (*in_row_group_ctr)++;

    return;
}



static HI_VOID JPEG_SDEC_YUV420_UPLANER_TO_YUVSp (j_decompress_ptr cinfo,
                                                          		     JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                          		     JDIMENSION in_row_groups_avail,
                                                          		     JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                          		     JDIMENSION out_rows_avail)
{
    HI_U32 Col = 0;
    my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;

    register HI_CHAR* OutYBuf = NULL;
    register HI_U32 OutYBufOffset = 0;
    register HI_CHAR* OutCbCrBuf = NULL;
    register HI_U32 OutCbCrBufOffset = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    UPSAMPLER_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);

    *out_row_ctr = 1;

    if (TRUE == upsample->spare_full)
    {
       upsample->spare_full = FALSE;
       return;
    }
    upsample->spare_full = TRUE;

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = pJpegHandle->stOutSurface.u32OutStride[0] * cinfo->output_scanline;
    OutYBuf = pJpegHandle->stOutSurface.pOutVir[0] + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2], sizeof(char)  *pJpegHandle->stOutSurface.u32OutStride[0]);

    OutYBuf += pJpegHandle->stOutSurface.u32OutStride[0];
    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2 + 1], sizeof(char) * pJpegHandle->stOutSurface.u32OutStride[0]);

    /**<--out Cb Cr data >**/
    /**<-- 输出 Cb Cr  数据>**/
	if (0 != cinfo->output_scanline % 2)
	{
       (*in_row_group_ctr)++;
       return;
	}


    OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * (cinfo->output_scanline / 2);
    OutCbCrBuf = pJpegHandle->stOutSurface.pOutVir[1] + OutCbCrBufOffset;

    for (Col = 0; Col < pJpegHandle->stOutSurface.u32OutStride[1] / 2; Col++)
    {
       OutCbCrBuf[2 * Col]   = input_buf[2][*in_row_group_ctr][Col];
       OutCbCrBuf[2 * Col + 1] = input_buf[1][*in_row_group_ctr][Col];
    }

	(*in_row_group_ctr)++;

    return;
}


static HI_VOID JPEG_SDEC_YUV42212_UPLANER_TO_YUVSp (j_decompress_ptr cinfo,
                                                  		     JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                  		     JDIMENSION in_row_groups_avail,
                                                  		     JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                  		     JDIMENSION out_rows_avail)
{
    JPEG_SDEC_YUV420_UPLANER_TO_YUVSp(cinfo,input_buf,in_row_group_ctr,in_row_groups_avail,output_buf,out_row_ctr,out_rows_avail);
    return;
}



static HI_VOID JPEG_SDEC_YUV42221_UPLANER_TO_YUVSp (j_decompress_ptr cinfo,
                                                          		     JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                          		     JDIMENSION in_row_groups_avail,
                                                          		     JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                          		     JDIMENSION out_rows_avail)
{
    HI_U32 Col = 0;
    my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;

    register HI_CHAR* OutYBuf = NULL;
    register HI_U32 OutYBufOffset = 0;
    register HI_CHAR* OutCbCrBuf = NULL;
    register HI_U32 OutCbCrBufOffset = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    UPSAMPLER_CHECK_AND_DEFINE_HANDLE_PARAMETERS();

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);

    *out_row_ctr = 1;

    if (TRUE == upsample->spare_full)
    {
       upsample->spare_full = FALSE;
       return;
    }
    upsample->spare_full = TRUE;

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = pJpegHandle->stOutSurface.u32OutStride[0] * cinfo->output_scanline;
    OutYBuf = pJpegHandle->stOutSurface.pOutVir[0] + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][*in_row_group_ctr], sizeof(char)*pJpegHandle->stOutSurface.u32OutStride[0]);

    /**<--out Cb Cr data >**/
    /**<-- 输出 Cb Cr  数据>**/
    OutCbCrBufOffset = pJpegHandle->stOutSurface.u32OutStride[1] * (cinfo->output_scanline / 2);
    OutCbCrBuf = pJpegHandle->stOutSurface.pOutVir[1] + OutCbCrBufOffset;

    for (Col = 0; Col < pJpegHandle->stOutSurface.u32OutStride[1] / 2; Col++)
    {
       OutCbCrBuf[2 * Col]   = input_buf[2][*in_row_group_ctr][Col];
       OutCbCrBuf[2 * Col + 1] = input_buf[1][*in_row_group_ctr][Col];
    }

    (*in_row_group_ctr)++;

    return;
}



/*****************************************************************************
* func              : JPEG_SDEC_InitUpsamplerForYuvsp
* description    : 上采样输出yuv semi-planer
* param[in]     : cinfo   CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitUpsamplerForYuvsp(j_decompress_ptr cinfo)
{
    my_upsample_ptr upsample;

    upsample = (my_upsample_ptr)cinfo->upsample;

    if (   (JCS_YUV400_SP != cinfo->out_color_space) && (JCS_YUV420_SP != cinfo->out_color_space)
        && (JCS_YUV422_SP_12 != cinfo->out_color_space) && (JCS_YUV422_SP_21 != cinfo->out_color_space)
        && (JCS_YUV444_SP  != cinfo->out_color_space))
    {
        return HI_FAILURE;
    }

    if (JCS_GRAYSCALE == cinfo->jpeg_color_space)
    {/** 400 **/
       if(cinfo->max_h_samp_factor == 2)
       {
           upsample->pub.upsample = JPEG_SDEC_YUV400_H2V2_UPLANER_TO_YUVSp;
       }
       else
       {
           upsample->pub.upsample = JPEG_SDEC_YUV400_UPLANER_TO_YUVSp;
       }
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 2) && (cinfo->max_v_samp_factor == 2))
    {/** 420 **/
       upsample->pub.upsample = JPEG_SDEC_YUV420_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 2) && (cinfo->max_v_samp_factor == 1))
    {/** 422 2*1 **/
       upsample->pub.upsample = JPEG_SDEC_YUV42221_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 1) && (cinfo->max_v_samp_factor == 2))
    {/** 422 1*2 **/
       upsample->pub.upsample = JPEG_SDEC_YUV42212_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 1) && (cinfo->max_v_samp_factor == 1))
    {/** 444 **/
       upsample->pub.upsample = JPEG_SDEC_YUV444_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    return HI_FAILURE;
}
