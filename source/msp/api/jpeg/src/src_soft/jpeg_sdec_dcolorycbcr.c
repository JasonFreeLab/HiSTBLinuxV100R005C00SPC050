/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dcolorycbcr.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : output YCbCr
                        解码输出YCbCr。
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

/***************************** Macro Definition     ********************************/


/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/

static HI_VOID JPEG_SDEC_OutYCbCr(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    register JSAMPROW inptr0, inptr1, inptr2;

    register HI_CHAR* OutPutBuf = NULL;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
        inptr1 = input_buf[1][input_row];
        inptr2 = input_buf[2][input_row];
        input_row++;

        if (NULL == pJpegHandle->stOutSurface.pOutVir[0])
        {
           OutPutBuf = (HI_CHAR*)(*output_buf++);
        }
        else
        {
            RowNum  = pJpegHandle->stOutSurface.u32OutStride[0] * ((cinfo->output_scanline - pJpegHandle->SkipLines) + HasBeenReadRowNum);
            OutPutBuf = (HI_CHAR*)(pJpegHandle->stOutSurface.pOutVir[0] + RowNum);
            HasBeenReadRowNum++;
        }

        for (Col = 0; Col < cinfo->output_width; Col++)
        {
          OutPutBuf[0] = GETJSAMPLE(inptr0[Col]);
		  OutPutBuf[1] = GETJSAMPLE(inptr1[Col]);
		  OutPutBuf[2] = GETJSAMPLE(inptr2[Col]);
          OutPutBuf += 3;
        }
    }

    return;
}

static HI_VOID JPEG_SDEC_OutCrCbY(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    register JSAMPROW inptr0, inptr1, inptr2;

    register HI_CHAR* OutPutBuf = NULL;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
        inptr1 = input_buf[1][input_row];
        inptr2 = input_buf[2][input_row];
        input_row++;


        if (NULL == pJpegHandle->stOutSurface.pOutVir[0])
        {
           OutPutBuf = (HI_CHAR*)(*output_buf++);
        }
        else
        {
            RowNum  = pJpegHandle->stOutSurface.u32OutStride[0] * ((cinfo->output_scanline - pJpegHandle->SkipLines) + HasBeenReadRowNum);
            OutPutBuf = (HI_CHAR*)(pJpegHandle->stOutSurface.pOutVir[0] + RowNum);
            HasBeenReadRowNum++;
        }

        for (Col = 0; Col < cinfo->output_width; Col++)
        {
           OutPutBuf[0] = GETJSAMPLE(inptr2[Col]);
           OutPutBuf[1] = GETJSAMPLE(inptr1[Col]);
           OutPutBuf[2] = GETJSAMPLE(inptr0[Col]);
           OutPutBuf += 3;
        }
    }

    return;
}

/*****************************************************************************
* func              : JPEG_SDEC_InitOutToYCbCr
* description    : decode output ycbcr
                          CNcomment:解码输出格式为ycbcr CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitOutToYCbCr(j_decompress_ptr cinfo)
{
    my_cconvert_ptr cconvert = (my_cconvert_ptr)cinfo->cconvert;

    if ((JCS_CrCbY != cinfo->out_color_space) && (JCS_YCbCr != cinfo->out_color_space))
    {
        return HI_FAILURE;
    }

    cinfo->out_color_components = cinfo->num_components;
    cinfo->output_components = (TRUE == cinfo->quantize_colors) ? (1) : (cinfo->out_color_components);

    if (cinfo->out_color_space == cinfo->jpeg_color_space)
    {
 		cconvert->pub.color_convert = JPEG_SDEC_OutYCbCr;
        return HI_SUCCESS;
    }

    if ((JCS_CrCbY == cinfo->out_color_space) && (JCS_YCbCr == cinfo->jpeg_color_space))
    {
 	   cconvert->pub.color_convert = JPEG_SDEC_OutCrCbY;
       return HI_SUCCESS;
    }

    ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);

    return HI_SUCCESS;
}
