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
#ifndef __VPSS_CBB_HAL_MAC_H__
#define __VPSS_CBB_HAL_MAC_H__
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
HI_VOID VPSS_Mac_SetImgheight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 imgheight);
HI_VOID VPSS_Mac_SetImgwidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 imgwidth);
HI_VOID VPSS_Mac_SetRefWidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refwidth);
HI_VOID VPSS_Mac_SetRefHeight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refheight);
HI_VOID VPSS_Mac_SetNx2yLbAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2y_lb_addr);
HI_VOID VPSS_Mac_SetNx2cLbAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2c_lb_addr);
HI_VOID VPSS_Mac_SetNx2LbStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_lb_stride);
HI_VOID VPSS_Mac_SetTransSrcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_src_addr);
HI_VOID VPSS_Mac_SetTransDesAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_des_addr);
HI_VOID VPSS_Mac_SetTransEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_en);
HI_VOID VPSS_Mac_SetTransSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 trans_size);
HI_VOID VPSS_Mac_SetNx2yTopHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2y_top_head_addr);
HI_VOID VPSS_Mac_SetNx2yBotHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2y_bot_head_addr);
HI_VOID VPSS_Mac_SetNx2cTopHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2c_top_head_addr);
HI_VOID VPSS_Mac_SetNx2cBotHeadAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2c_bot_head_addr);
HI_VOID VPSS_Mac_SetNx2HeadStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_head_stride);
HI_VOID VPSS_Mac_SetNodeid(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nodeid);
HI_VOID VPSS_Mac_SetCurVerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_ver_offset);
HI_VOID VPSS_Mac_SetCurHorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_hor_offset);
HI_VOID VPSS_Mac_SetCurTileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cur_tile_format);
HI_VOID VPSS_Mac_SetCuryAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cury_addr);
HI_VOID VPSS_Mac_SetCurcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 curc_addr);
HI_VOID VPSS_Mac_SetCurcStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 curc_stride);
HI_VOID VPSS_Mac_SetCuryStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cury_stride);
HI_VOID VPSS_Mac_SetRefVerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_ver_offset);
HI_VOID VPSS_Mac_SetRefHorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_hor_offset);
HI_VOID VPSS_Mac_SetRefTileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ref_tile_format);
HI_VOID VPSS_Mac_SetRefyAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refy_addr);
HI_VOID VPSS_Mac_SetRefcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refc_addr);
HI_VOID VPSS_Mac_SetRefcStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refc_stride);
HI_VOID VPSS_Mac_SetRefyStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 refy_stride);
HI_VOID VPSS_Mac_SetNxt1VerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1_ver_offset);
HI_VOID VPSS_Mac_SetNxt1HorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1_hor_offset);
HI_VOID VPSS_Mac_SetNxt1TileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1_tile_format);
HI_VOID VPSS_Mac_SetNxt1yAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1y_addr);
HI_VOID VPSS_Mac_SetNxt1cAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1c_addr);
HI_VOID VPSS_Mac_SetNxt1cStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1c_stride);
HI_VOID VPSS_Mac_SetNxt1yStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt1y_stride);
HI_VOID VPSS_Mac_SetNxt2DcmpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_dcmp_en);
HI_VOID VPSS_Mac_SetNxt2VerOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_ver_offset);
HI_VOID VPSS_Mac_SetNxt2HorOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_hor_offset);
HI_VOID VPSS_Mac_SetNxt2TileFormat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_tile_format);
HI_VOID VPSS_Mac_SetNxt2TileSpecField(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2_tile_spec_field);
HI_VOID VPSS_Mac_SetNxt2yAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2y_addr);
HI_VOID VPSS_Mac_SetNxt2cAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2c_addr);
HI_VOID VPSS_Mac_SetNxt2cStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2c_stride);
HI_VOID VPSS_Mac_SetNxt2yStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nxt2y_stride);
HI_VOID VPSS_Mac_SetRfrDitherMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_dither_mode);
HI_VOID VPSS_Mac_SetRfrDitherEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfr_dither_en);
HI_VOID VPSS_Mac_SetRfryAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfry_addr);
HI_VOID VPSS_Mac_SetRfrcAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfrc_addr);
HI_VOID VPSS_Mac_SetRfrcStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfrc_stride);
HI_VOID VPSS_Mac_SetRfryStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rfry_stride);
HI_VOID VPSS_Mac_SetVhd0DitherMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_dither_mode);
HI_VOID VPSS_Mac_SetVhd0LcmpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_lcmp_en);
HI_VOID VPSS_Mac_SetVhd0UvInvert(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_uv_invert);
HI_VOID VPSS_Mac_SetVhd0DitherEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_dither_en);
HI_VOID VPSS_Mac_SetVhd0PixBitw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_pix_bitw);
HI_VOID VPSS_Mac_SetVhd0Flip(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_flip);
HI_VOID VPSS_Mac_SetVhd0Mirror(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_mirror);
HI_VOID VPSS_Mac_SetVhd0Height(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_height);
HI_VOID VPSS_Mac_SetVhd0Width(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_width);
HI_VOID VPSS_Mac_SetVhd0yAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0y_addr);
HI_VOID VPSS_Mac_SetVhd0cAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0c_addr);
HI_VOID VPSS_Mac_SetVhd0cStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0c_stride);
HI_VOID VPSS_Mac_SetVhd0yStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0y_stride);
HI_VOID VPSS_Mac_SetStRaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 st_raddr);
HI_VOID VPSS_Mac_SetStWaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 st_waddr);
HI_VOID VPSS_Mac_SetStStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 st_stride);
HI_VOID VPSS_Mac_SetSttWAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 stt_w_addr);
HI_VOID VPSS_Mac_SetNx2TunlEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_tunl_en);
HI_VOID VPSS_Mac_SetNx2TunlRdInterval(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_tunl_rd_interval);
HI_VOID VPSS_Mac_SetNx2TunlAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nx2_tunl_addr);
HI_VOID VPSS_Mac_SetDiCntSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_cnt_width, HI_U32 di_cnt_height);
HI_VOID VPSS_Mac_SetDiRcntAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_rcnt_addr);
HI_VOID VPSS_Mac_SetDiWcntAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_wcnt_addr);
HI_VOID VPSS_Mac_SetDiCntStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 di_rcnt_stride , HI_U32 di_wcnt_stride);
HI_VOID VPSS_Mac_SetReeyAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reey_addr);
HI_VOID VPSS_Mac_SetReecAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reec_addr);
HI_VOID VPSS_Mac_SetReecStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reec_stride);
HI_VOID VPSS_Mac_SetReeyStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 reey_stride);
HI_VOID VPSS_Mac_SetRgmvCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_cur_addr);
HI_VOID VPSS_Mac_SetRgmvCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_cur_stride);
HI_VOID VPSS_Mac_SetBlkmvRefAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_ref_addr);
HI_VOID VPSS_Mac_SetBlkmvRefStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_ref_stride);
HI_VOID VPSS_Mac_SetPrjvCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_cur_addr);
HI_VOID VPSS_Mac_SetPrjvCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_cur_stride);
HI_VOID VPSS_Mac_SetPrjvNx2Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_nx2_addr);
HI_VOID VPSS_Mac_SetPrjvNx2Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_nx2_stride);
HI_VOID VPSS_Mac_SetPrjhCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjv_cur_addr);
HI_VOID VPSS_Mac_SetPrjhCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjh_cur_stride);
HI_VOID VPSS_Mac_SetPrjhNx2Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjh_nx2_addr);
HI_VOID VPSS_Mac_SetPrjhNx2Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 prjh_nx2_stride);

HI_VOID VPSS_Mac_SetCueyAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuey_addr);
HI_VOID VPSS_Mac_SetCuecAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuec_addr);
HI_VOID VPSS_Mac_SetCuecStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuec_stride);
HI_VOID VPSS_Mac_SetCueyStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cuey_stride);
HI_VOID VPSS_Mac_SetRgmvNx1Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx1_addr);
HI_VOID VPSS_Mac_SetRgmvNx1Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx1_stride);
HI_VOID VPSS_Mac_SetRgmvNx2Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx2_addr);
HI_VOID VPSS_Mac_SetRgmvNx2Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rgmv_nx2_stride);

HI_VOID VPSS_Mac_SetMadRaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mad_raddr);
HI_VOID VPSS_Mac_SetMadWaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mad_waddr);
HI_VOID VPSS_Mac_SetSnrMadRaddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 snr_mad_raddr);
HI_VOID VPSS_Mac_SetMadStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mad_stride);
HI_VOID VPSS_Mac_SetBlkmvCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_cur_addr);
HI_VOID VPSS_Mac_SetBlkmvCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_cur_stride);
HI_VOID VPSS_Mac_SetBlkmvNx1Addr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_nx1_addr);
HI_VOID VPSS_Mac_SetBlkmvNx1Stride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmv_nx1_stride);

HI_VOID VPSS_Mac_SetBlkmtCurAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_cur_addr);
HI_VOID VPSS_Mac_SetBlkmtCurStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_cur_stride);

HI_VOID VPSS_Mac_SetBlkmtRefAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_ref_addr);
HI_VOID VPSS_Mac_SetBlkmtRefStride(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkmt_ref_stride);


HI_VOID VPSS_Mac_SetTnrCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 tnr_cfg_addr);
HI_VOID VPSS_Mac_SetSnrCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 snr_cfg_addr);
HI_VOID VPSS_Mac_SetDeiCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dei_cfg_addr);
HI_VOID VPSS_Mac_SetZmeCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 zme_cfg_addr);
HI_VOID VPSS_Mac_SetFmtcCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fmtc_cfg_addr);

HI_VOID VPSS_Mac_SetChkSumWAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 chk_sum_w_addr);
HI_VOID VPSS_Mac_SetWinfoSumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 winfo_sum_sel);
HI_VOID VPSS_Mac_SetRinfoSumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rinfo_sum_sel);
HI_VOID VPSS_Mac_SetRch3SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch3_sum_sel);
HI_VOID VPSS_Mac_SetRch2SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch2_sum_sel);
HI_VOID VPSS_Mac_SetRch1SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch1_sum_sel);
HI_VOID VPSS_Mac_SetRch0SumSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch0_sum_sel);

HI_VOID VPSS_Mac_SetRchNx2clbBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2clb_bypass);
HI_VOID VPSS_Mac_SetRchNx2ylbBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2ylb_bypass);
HI_VOID VPSS_Mac_SetRchTunlBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_tunl_bypass);
HI_VOID VPSS_Mac_SetRchReecBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_reec_bypass);
HI_VOID VPSS_Mac_SetRchReeyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_reey_bypass);
HI_VOID VPSS_Mac_SetRchRgmvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_rgmv_cur_bypass);
HI_VOID VPSS_Mac_SetRchRgmvNx1Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_rgmv_nx1_bypass);

HI_VOID VPSS_Mac_SetRchBlkmtRefBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_blkmt_ref_bypass);

HI_VOID VPSS_Mac_SetRchBlkmvRefBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_blkmv_ref_bypass);
HI_VOID VPSS_Mac_SetRchBlkmvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_blkmv_cur_bypass);
HI_VOID VPSS_Mac_SetRchPrjvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_prjv_cur_bypass);
HI_VOID VPSS_Mac_SetRchPrjhCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_prjh_cur_bypass);

HI_VOID VPSS_Mac_SetRchDiCntBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_di_rcnt_bypass);

HI_VOID VPSS_Mac_SetRchRstBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_rst_bypass);
HI_VOID VPSS_Mac_SetRchSrmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_srmd_bypass);
HI_VOID VPSS_Mac_SetRchTrmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_trmd_bypass);
HI_VOID VPSS_Mac_SetRchNx2cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2c_bypass);
HI_VOID VPSS_Mac_SetRchNx2yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2y_bypass);
HI_VOID VPSS_Mac_SetRchNx1cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx1c_bypass);
HI_VOID VPSS_Mac_SetRchNx1yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx1y_bypass);
HI_VOID VPSS_Mac_SetRchRefcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_refc_bypass);
HI_VOID VPSS_Mac_SetRchRefyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_refy_bypass);
HI_VOID VPSS_Mac_SetRchCurcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_curc_bypass);
HI_VOID VPSS_Mac_SetRchCuryBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_cury_bypass);
HI_VOID VPSS_Mac_SetRchTransrBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_transr_bypass);
HI_VOID VPSS_Mac_SetRchNx2cHeadBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2c_head_bypass);
HI_VOID VPSS_Mac_SetRchNx2yHeadBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_nx2y_head_bypass);

HI_VOID VPSS_Mac_SetWchDiCntBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_di_wcnt_bypass);

HI_VOID VPSS_Mac_SetWchCuecBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_cuec_bypass);
HI_VOID VPSS_Mac_SetWchCueyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_cuey_bypass);
HI_VOID VPSS_Mac_SetWchRgmvNx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_rgmvnx2_bypass);
HI_VOID VPSS_Mac_SetWchRgmvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_rgmvcur_bypass);

HI_VOID VPSS_Mac_SetWchBlkmtCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_blkmtcur_bypass);
HI_VOID VPSS_Mac_SetWchBlkmvNx1Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_blkmvnx1_bypass);
HI_VOID VPSS_Mac_SetWchPrjvNx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_prjvnx2_bypass);
HI_VOID VPSS_Mac_SetWchPrjhNx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_prjhnx2_bypass);
HI_VOID VPSS_Mac_SetWchTunlBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_tunl_bypass);

HI_VOID VPSS_Mac_SetWchSttBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_stt_bypass);

HI_VOID VPSS_Mac_SetWchTwmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_twmd_bypass);
HI_VOID VPSS_Mac_SetWchWstBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_wst_bypass);
HI_VOID VPSS_Mac_SetWchTranswBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_transw_bypass);
HI_VOID VPSS_Mac_SetWchRfrcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_rfrc_bypass);
HI_VOID VPSS_Mac_SetWchRfryBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_rfry_bypass);
HI_VOID VPSS_Mac_SetWchVhd0cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_vhd0c_bypass);
HI_VOID VPSS_Mac_SetWchVhd0yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_vhd0y_bypass);
HI_VOID VPSS_Mac_SetVhd0TunlEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_en);
HI_VOID VPSS_Mac_SetVhd0TunlMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_mode);
HI_VOID VPSS_Mac_SetVhd0TunlFinishLine(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_finish_line);
HI_VOID VPSS_Mac_SetVhd0TunlAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vhd0_tunl_addr);

HI_VOID VPSS_Mac_SetWchBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 wch_bypass);


HI_VOID VPSS_Mac_SetRchBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rch_bypass);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



#endif /* __VPSS_CFGREG_H__ */

