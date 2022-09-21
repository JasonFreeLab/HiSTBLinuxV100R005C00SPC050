/******************************************************************************

 Copyright @ Hisilicon Technologies Co., Ltd. 1998-2015. All rights reserved.

 ******************************************************************************
  File Name     : vpss_cfgreg.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/1/25
  Last Modified :
  Description   : vpss_cfgreg.c header file
  Function List :
  History       :
  1.Date        : 2016/1/25
    Author      : sdk
    Modification: Created file

******************************************************************************/
#ifndef __VPSS_CBB_HAL_CROP_H__
#define __VPSS_CBB_HAL_CROP_H__
#include "hi_type.h"
//#include "vpss_reg.h"
#include "vpss_cbb_common.h"



/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if 1
HI_VOID VPSS_DRV_Set_VPSS_VHD0CROP_SIZE(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 height , HI_U32 width );
HI_VOID VPSS_DRV_Set_VPSS_VHD0CROP_POS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 y , HI_U32 x );

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

