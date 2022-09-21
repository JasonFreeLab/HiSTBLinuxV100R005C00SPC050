/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : patch_for_jdapistd.c
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
//HISILICON add begin
//ADP_HARD_DECODE:
#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"
#include "jpeg_hdec_support.c"

#define CFG_JPEG_SDEC_SET_CROP
#include "jpeg_sdec_subtile.c"
#undef CFG_JPEG_SDEC_SET_CROP


#define CFG_JPEG_SDEC_SET_SKIP
#include "jpeg_sdec_subtile.c"
#undef CFG_JPEG_SDEC_SET_SKIP

//HISILICON add end

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/
extern HI_VOID JPEG_HDEC_SetOutFmt(const struct jpeg_decompress_struct *cinfo);
extern HI_U32 JPEG_HDEC_StartDec(j_decompress_ptr cinfo, HI_CHAR* ScanlineBuf, HI_U32 MaxLines);

/**********************       API realization       ***********************************/
//HISILICON add begin
//ADP_HARD_DEC: crop skia and hard decode
#define adp_for_set_out_fmt                 JPEG_HDEC_SetOutFmt(cinfo);
#define adp_for_check_support_crop          JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);\
                                            JPEG_HDEC_IfSupport(cinfo);\
                                            JPEG_HDEC_SupportCrop(cinfo);

#define adp_for_set_cropxw                  JPEG_SDEC_SetCropXW(cinfo, *xoffset, *width);\
                                            if (HI_TRUE == pJpegHandle->SupportHardDec)\
                                            {\
                                               return;\
                                            }

#define adp_for_hard_decode                 JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);\
                                            row_ctr = (NULL != scanlines) ? JPEG_HDEC_StartDec(cinfo,(HI_CHAR*)scanlines[0],1) : JPEG_HDEC_StartDec(cinfo,NULL,1);\
                                            if (HI_TRUE == pJpegHandle->bHdecEnd)\
                                            {\
                                               return row_ctr;\
                                            }\
                                            pJpegHandle->SupportHardDec = HI_FALSE;


#define adp_for_set_skip_info               JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data); \
                                            JPEG_SDEC_SetCropYH(cinfo,num_lines,cinfo->output_height - num_lines);\
                                            JPEG_SDEC_SetSkipLines(cinfo, num_lines);

#define adp_for_enable_discard_scanlines    {\
                                              JPEG_SDEC_SetDisScanMark(cinfo,HI_TRUE);
#define adp_for_disable_discard_scanlines     JPEG_SDEC_SetDisScanMark(cinfo,HI_FALSE);\
                                            }


#define adp_for_begin_check_hdec_support    JPEG_HDEC_IfSupport(cinfo);\
                                            if (HI_TRUE != pJpegHandle->SupportHardDec)\
                                            {
#define adp_for_end_check_hdec_support      }

#define adp_for_check_hdec_support          if (HI_TRUE == pJpegHandle->SupportHardDec)\
                                            {\
                                                 cinfo->output_scanline += num_lines;\
                                                 return num_lines;\
                                            }
//HISILICON add end
