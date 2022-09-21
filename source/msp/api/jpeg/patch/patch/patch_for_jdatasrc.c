/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : patch_for_jdatasrc.c
Version           : Initial Draft
Author            :
Created          : 2017/03/16
Description     : sdk
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
#include "hi_type.h"

/***************************** Macro Definition     ********************************/

#define JPEG_SDEC_InitStdioSrc(cinfo)               JPEG_SDEC_InitSrc(cinfo, NULL, 0, HI_TRUE)
#define JPEG_SDEC_InitMemSrc(cinfo, InBuf, InSize)  JPEG_SDEC_InitSrc(cinfo, InBuf, InSize, HI_FALSE)
#define JPEG_SDEC_FillFileInputBuffer(cinfo)        JPEG_SDEC_FillInputBuffer(cinfo, HI_TRUE)
#define JPEG_SDEC_FillMemInputBuffer(cinfo)         JPEG_SDEC_FillInputBuffer(cinfo, HI_FALSE)

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/
METHODDEF (void) init_source (j_decompress_ptr cinfo);
METHODDEF (void) init_mem_source (j_decompress_ptr cinfo);
METHODDEF (boolean) fill_input_buffer (j_decompress_ptr cinfo);
METHODDEF (boolean) fill_mem_input_buffer (j_decompress_ptr cinfo);
METHODDEF (void) skip_input_data (j_decompress_ptr cinfo, long num_bytes);
METHODDEF (void) term_source (j_decompress_ptr cinfo);

extern HI_VOID JPEG_SDEC_InitSrc(j_decompress_ptr cinfo, const HI_UCHAR* InBuf, HI_ULONG InSize, HI_BOOL bInputFile);
extern HI_S32 JPEG_SDEC_FillInputBuffer(j_decompress_ptr cinfo, HI_BOOL bInputFile);

/**********************       API realization       ***********************************/
//HISILICON add begin
//ADP_HARD_DEC: fill data dispose
static inline void jpeg_init_file (j_decompress_ptr cinfo, FILE *infile)
{
    my_src_ptr src;
    if (cinfo->src == NULL)
    {
      cinfo->src = (struct jpeg_source_mgr *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,sizeof(my_source_mgr));
      src = (my_src_ptr) cinfo->src;
      src->buffer = (JOCTET *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,INPUT_BUF_SIZE * sizeof(JOCTET));
    }

    src = (my_src_ptr) cinfo->src;
    src->pub.init_source       = init_source;
    src->pub.fill_input_buffer = fill_input_buffer;
    src->pub.skip_input_data   = skip_input_data;
    src->pub.resync_to_restart = jpeg_resync_to_restart;
    src->pub.term_source       = term_source;
    src->infile                = infile;
    src->pub.bytes_in_buffer   = 0;
    src->pub.next_input_byte   = NULL;

    JPEG_SDEC_InitStdioSrc(cinfo);
}


static inline void jpeg_init_mem (j_decompress_ptr cinfo,const unsigned char *inbuffer, unsigned long insize)
{
  my_src_ptr src;
  if (inbuffer == NULL || insize == 0)
  {
    ERREXIT(cinfo, JERR_INPUT_EMPTY);
  }

  if (cinfo->src == NULL)
  {
    cinfo->src = (struct jpeg_source_mgr *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,sizeof(my_source_mgr));
    src = (my_src_ptr) cinfo->src;
    src->buffer = (JOCTET *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,INPUT_BUF_SIZE * sizeof(JOCTET));
  }

  src = (my_src_ptr)cinfo->src;
  src->pub.init_source       = init_mem_source;
  src->pub.fill_input_buffer = fill_mem_input_buffer;
  src->pub.skip_input_data   = skip_input_data;
  src->pub.resync_to_restart = jpeg_resync_to_restart;
  src->pub.term_source       = term_source;
  src->pub.bytes_in_buffer   = (size_t) insize;
  src->pub.next_input_byte   = (const JOCTET *) inbuffer;

  JPEG_SDEC_InitMemSrc(cinfo, inbuffer, insize);
}


#define adp_for_fill_from_file                HI_S32 Ret = HI_SUCCESS;\
                                              Ret = JPEG_SDEC_FillFileInputBuffer(cinfo);\
                                              CHECK_JPEG_EQUAL_RETURN(Ret, HI_SUCCESS, TRUE);

#define adp_for_fill_from_mem                 HI_S32 Ret = HI_SUCCESS;\
                                              Ret = JPEG_SDEC_FillMemInputBuffer(cinfo);\
                                              CHECK_JPEG_EQUAL_RETURN(Ret, HI_SUCCESS, TRUE);

#define adp_for_init_from_file                return jpeg_init_file(cinfo,infile);

#define adp_for_init_from_mem                 return jpeg_init_mem(cinfo,inbuffer,insize);

#define adp_for_not_warn_eof                  if (0)

//HISILICON add end
