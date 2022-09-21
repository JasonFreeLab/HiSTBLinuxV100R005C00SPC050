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
#ifndef __VPSS_CBB_HAL_LBA_H__
#define __VPSS_CBB_HAL_LBA_H__
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
HI_VOID VPSS_DRV_Set_VPSS_VHD0LBA_DSIZE(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 Hgt, HI_U32 Wth);

HI_VOID VPSS_DRV_Set_VPSS_VHD0LBA_VFPOS(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Y, HI_U32 u32X);

HI_VOID VPSS_DRV_Set_VPSS_VHD0LBA_BK(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32YColor, HI_U32 u32CbColor, HI_U32 u32CrColor);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

