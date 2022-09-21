/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : patch_for_jdmaster.c
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
#define JPEG_SDEC_CALC_OUT_COLOR_COMPONENTS
#include "jpeg_sdec_color.c"
#undef JPEG_SDEC_CALC_OUT_COLOR_COMPONENTS
//HISILICON add end

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
//HISILICON add begin
//ADP_HARD_DEC: set mark information

#define adp_for_calc_out_color_components          JPEG_SDEC_CalcOutColorComponents(cinfo);

//HISILICON add end
