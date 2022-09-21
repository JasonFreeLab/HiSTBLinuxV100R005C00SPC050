/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_sdec_dcolorxrgb.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : output xrgb
                        解码输出XRGB  格式
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


#include "jpeg_sdec_dcolorargb8888.c"
#include "jpeg_sdec_dcolorargb1555.c"
#include "jpeg_sdec_dcolorrgb888.c"
#include "jpeg_sdec_dcolorrgb565.c"

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
static HI_VOID JPEG_SDEC_YCC_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
    register JSAMPROW inptr0, inptr1, inptr2;
    /* copy these pointers into registers if possible */
    register JSAMPLE * range_limit = cinfo->sample_range_limit;
    register int * Crrtab = cconvert->Cr_r_tab;
    register int * Cbbtab = cconvert->Cb_b_tab;
    register long * Crgtab = (long*)cconvert->Cr_g_tab;
    register long * Cbgtab = (long*)cconvert->Cb_g_tab;
    SHIFT_TEMPS

    register HI_CHAR* OutPutBuf = NULL;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_S32 Y = 0, Cb = 0, Cr = 0;
    register HI_U32 Red = 0, Green = 0, Blue = 0;

    register HI_U32 PixOffset = 0;
    PixOffset = ((JCS_RGB565 != cinfo->out_color_space) && (JCS_BGR565 != cinfo->out_color_space) && (JCS_RGB_565 != cinfo->out_color_space)) ? (cinfo->out_color_components) : (2);

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
            Y  = GETJSAMPLE(inptr0[Col]); /**< Green >**/
            Cb = GETJSAMPLE(inptr1[Col]); /**< Blue    >**/
            Cr = GETJSAMPLE(inptr2[Col]); /**< Red     >**/

            Red   = range_limit[Y + Crrtab[Cr]];
            Green = range_limit[Y + ((int)RIGHT_SHIFT(Cbgtab[Cb]+Crgtab[Cr], SCALEBITS))];
            Blue  = range_limit[Y + Cbbtab[Cb]];

            pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCC_ConVert(cinfo,OutPutBuf,Red,Green,Blue);
            OutPutBuf += PixOffset;
        }
    }

    return;
}

static HI_VOID JPEG_SDEC_GRAY_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    register JSAMPROW inptr;

    register HI_CHAR* OutPutBuf = NULL;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_U32 Red = 0;

    register HI_U32 PixOffset = 0;
    PixOffset = ((JCS_RGB565 != cinfo->out_color_space) && (JCS_BGR565 != cinfo->out_color_space) && (JCS_RGB_565 != cinfo->out_color_space)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr = input_buf[0][input_row++];

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
           Red = inptr[Col];
           pJpegHandle->stSdecColorConvert.JPEG_SDEC_GRAY_ConVert(cinfo,OutPutBuf,Red,Red,Red);
           OutPutBuf += PixOffset;
        }
    }

    return;
}


static HI_VOID JPEG_SDEC_YCCK_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
    register JSAMPROW inptr0, inptr1, inptr2, inptr3;
    /* copy these pointers into registers if possible */
    register JSAMPLE * range_limit = cinfo->sample_range_limit;
    register int * Crrtab = cconvert->Cr_r_tab;
    register int * Cbbtab = cconvert->Cb_b_tab;
    register long * Crgtab = (long*)cconvert->Cr_g_tab;
    register long * Cbgtab = (long*)cconvert->Cb_g_tab;
    SHIFT_TEMPS

    register HI_CHAR* OutPutBuf = NULL;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_S32 Y = 0, Cb = 0, Cr = 0;
    register HI_U32 Red = 0, Green = 0, Blue = 0;

    HI_U8 YCCK[4];
	HI_U8 MaxVal = 0;
	register HI_S32 C  = 0;	/** cyan	**/
	register HI_S32 M  = 1;	/** magenta **/
	register HI_S32 YE = 2;	/** yellow	**/
	register HI_S32 K  = 3;	/** black	**/

    register HI_U32 PixOffset = 0;
    PixOffset = ((JCS_RGB565 != cinfo->out_color_space) && (JCS_BGR565 != cinfo->out_color_space) && (JCS_RGB_565 != cinfo->out_color_space)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
		inptr1 = input_buf[1][input_row];
		inptr2 = input_buf[2][input_row];
		inptr3 = input_buf[3][input_row];
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
              Y  = GETJSAMPLE(inptr0[Col]);
              Cb = GETJSAMPLE(inptr1[Col]);
              Cr = GETJSAMPLE(inptr2[Col]);

              YCCK[C]  = range_limit[MAXJSAMPLE - (Y + Crrtab[Cr])];
              YCCK[M]  = range_limit[MAXJSAMPLE - (Y + ((int) RIGHT_SHIFT(Cbgtab[Cb] + Crgtab[Cr],SCALEBITS)))];
              YCCK[YE] = range_limit[MAXJSAMPLE - (Y + Cbbtab[Cb])];
              YCCK[K]  = inptr3[Col];

              MaxVal = (YCCK[C] > YCCK[M])  ? (YCCK[C]) : (YCCK[M]);
              MaxVal = (MaxVal  > YCCK[YE]) ? (MaxVal)  : (YCCK[YE]);
              MaxVal = (MaxVal  > YCCK[K])  ? (MaxVal)  : (YCCK[K]);

              Red   = (YCCK[K] * YCCK[C])  / MaxVal;
              Green = (YCCK[K] * YCCK[M])  / MaxVal;
              Blue  = (YCCK[K] * YCCK[YE]) / MaxVal;

              pJpegHandle->stSdecColorConvert.JPEG_SDEC_YCCK_ConVert(cinfo,OutPutBuf,Red,Green,Blue);
              OutPutBuf += PixOffset;
        }
    }

    return;
}

static HI_VOID JPEG_SDEC_CMYK_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    register JSAMPROW inptr0, inptr1, inptr2, inptr3;

    register HI_CHAR* OutPutBuf = NULL;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_S32 Y = 0, Cb = 0, Cr = 0, A = 0;

    register HI_U32 PixOffset = 0;
    PixOffset = ((JCS_RGB565 != cinfo->out_color_space) && (JCS_BGR565 != cinfo->out_color_space) && (JCS_RGB_565 != cinfo->out_color_space)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
        inptr1 = input_buf[1][input_row];
        inptr2 = input_buf[2][input_row];
        inptr3 = input_buf[3][input_row];
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
            Y  = GETJSAMPLE(inptr0[Col]);
            Cb = GETJSAMPLE(inptr1[Col]);
            Cr = GETJSAMPLE(inptr2[Col]);
            A  = GETJSAMPLE(inptr3[Col]);

            pJpegHandle->stSdecColorConvert.JPEG_SDEC_CMYK_ConVert(cinfo,OutPutBuf,Y,Cb,Cr,A);
            OutPutBuf += PixOffset;
        }
    }

    return;
}


/*****************************************************************************
* func              : JPEG_SDEC_InitOutToXRGB
* description    : decode output xrgb
                          CNcomment:解码输出格式为xrgb  格式 CNend\n
* param[in]     : cinfo             CNcomment: 解码器句柄    CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitOutToXRGB(j_decompress_ptr cinfo)
{
    HI_S32 Ret = HI_SUCCESS;
    my_cconvert_ptr cconvert = (my_cconvert_ptr)cinfo->cconvert;

    Ret = JPEG_SDEC_SupportARGB8888(cinfo);
    Ret &= JPEG_SDEC_SupportARGB1555(cinfo);
    Ret &= JPEG_SDEC_SupportRGB888(cinfo);
    Ret &= JPEG_SDEC_SupportRGB565(cinfo);
    CHECK_JPEG_UNEQUAL_RETURN(HI_SUCCESS, Ret, HI_FAILURE);

    cinfo->output_components = (TRUE == cinfo->quantize_colors) ? (1) : (cinfo->out_color_components);

    if (cinfo->jpeg_color_space == JCS_YCbCr)
    {
        cconvert->pub.color_convert = JPEG_SDEC_YCC_XRGB_Convert;
        build_ycc_rgb_table(cinfo);
        return HI_SUCCESS;
    }

    if (cinfo->jpeg_color_space == JCS_GRAYSCALE)
    {
       cconvert->pub.color_convert = JPEG_SDEC_GRAY_XRGB_Convert;
       return HI_SUCCESS;
    }

    if (cinfo->jpeg_color_space == JCS_YCCK)
    {
       cconvert->pub.color_convert = JPEG_SDEC_YCCK_XRGB_Convert;
       build_ycc_rgb_table(cinfo);
       return HI_SUCCESS;
    }

    if (cinfo->jpeg_color_space == JCS_CMYK)
    {
       cconvert->pub.color_convert = JPEG_SDEC_CMYK_XRGB_Convert;
       return HI_SUCCESS;
    }

    ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);

    return HI_SUCCESS;
}
