/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : patch_for_jcomapi.c
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
#include "hi_type.h"
//HISILICON add end
/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/
extern HI_VOID JPEG_HDEC_Reset(const struct jpeg_common_struct *cinfo);

/**********************       API realization       ***********************************/
//HISILICON add begin
//ADP_HARD_DEC: reset hard decode resource
#define adp_for_reset_hdec_resource      JPEG_HDEC_Reset(cinfo);
//HISILICON add end
