/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : patch_for_jdmarker.c
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
#include "jpeg_hdec_api.h"

#define JPEG_SDEC_SET_IMG_COLOR_SPACE
#define JPEG_SDEC_SET_LU_DC_CODE_LENGTH
#include "jpeg_sdec_color.c"
#undef JPEG_SDEC_SET_IMG_COLOR_SPACE
#undef JPEG_SDEC_SET_LU_DC_CODE_LENGTH

#include "jpeg_sdec_exif.c"
//HISILICON add end


/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
//HISILICON add begin
//ADP_HARD_DEC: set mark information

#define adp_for_set_image_color_sapce             JPEG_SDEC_SetImgColorSpace(cinfo);

#define adp_for_set_dri_info                      if (0 == index){\
                                                      JPEG_SDEC_SetLuDcCodeLen(cinfo,bits);\
                                                  }
#ifdef CONFIG_JPEG_EXIF_SUPPORT
#define adp_for_set_exif                          marker->process_APPn[1] = JPEG_SDEC_GetExif;
#else
#define adp_for_set_exif                          do{}while(0);
#endif
//HISILICON add end
