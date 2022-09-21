/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : patch_for_jdhuff.c
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
//MPG_SUPPORT:
#include "jpeg_sdec_table.h"
//HISILICON add end

/***************************** Macro Definition     ********************************/

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration ********************************/


/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
//HISILICON add begin
//ADP_HARD_DEC: use default table
#define adp_for_set_default_talbe       htbl = isDC ? (JHUFF_TBL*)&gs_u8DefaultDC[tblno] : (JHUFF_TBL*)&gs_u8DefaultAC[tblno];\
                                        if (0)

#define adp_for_not_warn_hit_mark       if (0)
//HISILICON add end
