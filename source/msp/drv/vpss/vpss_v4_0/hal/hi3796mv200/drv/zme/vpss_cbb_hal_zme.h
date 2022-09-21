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
#ifndef __VPSS_CBB_HAL_ZME_H__
#define __VPSS_CBB_HAL_ZME_H__
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
//addr=0x2000
HI_VOID VPSS_Zme_Set_VPSS_VHD0_HSP(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 hlmsc_en , HI_U32 hchmsc_en , HI_U32 hlmid_en , HI_U32 hchmid_en , HI_U32 hlfir_en , HI_U32 hchfir_en , HI_U32 hfir_order , HI_U32 hratio );
//addr=0x2004
HI_VOID VPSS_Zme_Set_VPSS_VHD0_HLOFFSET(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 hor_loffset );
//addr=0x2008
HI_VOID VPSS_Zme_Set_VPSS_VHD0_HCOFFSET(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 hor_coffset );
//addr=0x200c
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VSP(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vlmsc_en , HI_U32 vchmsc_en , HI_U32 vlmid_en , HI_U32 vchmid_en , HI_U32 vlfir_en , HI_U32 vchfir_en , HI_U32 zme_out_fmt );
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VSP_OutFmt(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 zme_out_fmt );

//addr=0x2010
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VSR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vratio );
//addr=0x2014
HI_VOID VPSS_Zme_Set_VPSS_VHD0_VOFFSET(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 vluma_offset , HI_U32 vchroma_offset );

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZMEORESO(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 oh, HI_U32 ow);

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_LHADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 scl_lh );

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_LVADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 scl_lv );

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_CHADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 scl_ch );

HI_VOID VPSS_Zme_Set_VPSS_VHD0_ZME_CVADDR(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 scl_cv );

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

