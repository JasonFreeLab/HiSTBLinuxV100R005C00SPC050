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
#ifndef __VPSS_CBB_HAL_SYS_H__
#define __VPSS_CBB_HAL_SYS_H__
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

extern HI_VOID VPSS_DRV_ClrInt( S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32ClrInt );
extern HI_S32 VPSS_DRV_GetIntStatus( S_VPSS_REGS_TYPE *pstVpssRegs );
extern HI_S32 VPSS_DRV_GetRawIntStatus( S_VPSS_REGS_TYPE *pstVpssRegs );
extern HI_S32 VPSS_DRV_Get_SMMU_INTSTAT_S(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 *pu32SecureState, HI_U32 *pu32NoSecureState);
extern HI_VOID VPSS_DRV_Set_VPSS_PNEXT(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 *pu32PhyAddr);
extern HI_VOID VPSS_DRV_Set_VPSS_START(S_VPSS_REGS_TYPE *pstVpssRegs);
extern HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_OUTSTANDING(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 woutstanding , HI_U32 routstanding );
extern HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_BUSLEN(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 bus_len );
extern HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_CLKGT(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ck_gt_en_calc, HI_U32 ck_gt_en );
extern HI_VOID VPSS_DRV_Set_VPSS_MISCELLANEOUS_INITTIMER(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 init_timer);
extern HI_VOID VPSS_DRV_Set_VPSS_BUS_CTRL(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 b128_split_en , HI_U32 b256_split_en );

extern HI_VOID VPSS_DRV_SetIntMask( S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Mask );
extern HI_S32 VPSS_DRV_SetTimeOut(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Data);
extern HI_VOID VPSS_DRV_SetCkgtEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32Data);
extern HI_VOID VPSS_DRV_Set_VPSS_MACCFG(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 mac_ch_prio );
extern HI_VOID VPSS_DRV_SetMemCtrl(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 ema, HI_U32 emaw, HI_U32 emasa, HI_U32 emaa, HI_U32 emab);

#if 1
HI_VOID VPSS_Sys_SetBfield(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bfield);
HI_VOID VPSS_Sys_SetBfieldMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bfield_mode);
HI_VOID VPSS_Sys_SetBfieldFirst(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bfield_first);
HI_VOID VPSS_Sys_SetImgProMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 img_pro_mode);
HI_VOID VPSS_Sys_SetIgbmEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 igbm_en);
HI_VOID VPSS_Sys_SetIfmdEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ifmd_en);
HI_VOID VPSS_Sys_SetProt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prot);
HI_VOID VPSS_Sys_SetRotateEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rotate_en);
HI_VOID VPSS_Sys_SetRotateAngle(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rotate_angle);
HI_VOID VPSS_Sys_SetRfrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_en);
HI_VOID VPSS_Sys_SetTnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 tnr_en);
HI_VOID VPSS_Sys_SetSnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 snr_en);
HI_VOID VPSS_Sys_SetFmtcEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fmtc_en);
HI_VOID VPSS_Sys_SetBlkDetEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blk_det_en);
HI_VOID VPSS_Sys_SetVc1En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vc1_en);
HI_VOID VPSS_Sys_SetMedsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 meds_en);
HI_VOID VPSS_Sys_SetMcdiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcdi_en);
HI_VOID VPSS_Sys_SetDeiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dei_en);
HI_VOID VPSS_Sys_SetRgmeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgme_en);

HI_VOID VPSS_Sys_SetChkSumEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 chk_sum_en);

HI_VOID VPSS_Sys_SetVhd0En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_en);

HI_VOID VPSS_Sys_SetRfrPixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_pix_bitw);
HI_VOID VPSS_Sys_SetRefPixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_pix_bitw);
HI_VOID VPSS_Sys_SetInPixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 in_pix_bitw);
HI_VOID VPSS_Sys_SetInFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 in_format);
HI_VOID VPSS_Sys_SetVhd0Format(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_format);

HI_VOID VPSS_Sys_SetFourPixEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 four_pix_en);
HI_VOID VPSS_Sys_SetRamBank(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ram_bank);
HI_VOID VPSS_Sys_SetVhd0ZmeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 zme_en);
HI_VOID VPSS_Sys_SetVhd0CropEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 crop_en);
HI_VOID VPSS_Sys_SetVhd0LbaEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lba_en);

HI_VOID VPSS_Sys_SetVpssNodeId(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 nodeid );
HI_VOID VPSS_Sys_SetCtsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cts_en);

HI_VOID VPSS_Sys_SetCtsBitSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 bit_sel);

HI_VOID VPSS_Sys_SetRefDitherEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_dither_en);
HI_VOID VPSS_Sys_SetRefDitherMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_dither_mode);

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

