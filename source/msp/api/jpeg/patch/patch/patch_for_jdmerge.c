/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : patch_for_jdmerge.c
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
#include "jpeg_sdec_dupsampleryuvsp.c"
//HISILICON add end


/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
//HISILICON add begin
//ADP_HARD_DECODE: init upsample for yuv semi-planer

#define adp_for_init_upsampler_yuvsp     CHECK_JPEG_EQUAL_UNRETURN(HI_SUCCESS,JPEG_SDEC_InitUpsamplerForYuvsp(cinfo));

//HISILICON add end
