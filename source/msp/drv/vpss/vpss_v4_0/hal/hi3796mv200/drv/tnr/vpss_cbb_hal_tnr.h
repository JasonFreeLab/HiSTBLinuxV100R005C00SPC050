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
#ifndef __VPSS_CBB_HAL_TNR_H__
#define __VPSS_CBB_HAL_TNR_H__
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

HI_VOID VPSS_Tnr_SetMcnrMotionMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcnr_motion_mode);
HI_VOID VPSS_Tnr_SetMarketcoor(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 marketcoor);
HI_VOID VPSS_Tnr_SetMarketmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 marketmode);
HI_VOID VPSS_Tnr_SetMarketmodeen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 marketmodeen);
HI_VOID VPSS_Tnr_SetMcnrMedsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcnr_meds_en);
HI_VOID VPSS_Tnr_SetMcnrRgmeMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcnr_rgme_mode);
HI_VOID VPSS_Tnr_SetMcnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mcnr_en);
HI_VOID VPSS_Tnr_SetCnren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cnren);
HI_VOID VPSS_Tnr_SetYnren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ynren);
HI_VOID VPSS_Tnr_SetNren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 nren);
HI_VOID VPSS_Tnr_SetAlpha2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 alpha2);
HI_VOID VPSS_Tnr_SetAlpha1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 alpha1);
HI_VOID VPSS_Tnr_SetCmotionlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionlpfmode);
HI_VOID VPSS_Tnr_SetYmotionlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionlpfmode);
HI_VOID VPSS_Tnr_SetCmotioncalcmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotioncalcmode);
HI_VOID VPSS_Tnr_SetYmotioncalcmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotioncalcmode);
HI_VOID VPSS_Tnr_SetMeancadjshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 meancadjshift);
HI_VOID VPSS_Tnr_SetMeanyadjshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 meanyadjshift);
HI_VOID VPSS_Tnr_SetMeanCmotionAdjEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_cmotion_adj_en);
HI_VOID VPSS_Tnr_SetMeanYmotionAdjEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_ymotion_adj_en);
HI_VOID VPSS_Tnr_SetMdprelpfen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mdprelpfen);
HI_VOID VPSS_Tnr_SetCmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmdcore);
HI_VOID VPSS_Tnr_SetCmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmdgain);
HI_VOID VPSS_Tnr_SetYmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymdcore);
HI_VOID VPSS_Tnr_SetYmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymdgain);
HI_VOID VPSS_Tnr_SetRandomctrlmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 randomctrlmode);
HI_VOID VPSS_Tnr_SetBlkdiffthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 blkdiffthd);
HI_VOID VPSS_Tnr_SetNoisedetecten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noisedetecten);
HI_VOID VPSS_Tnr_SetFlatthdmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 flatthdmax);
HI_VOID VPSS_Tnr_SetFlatthdmed(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 flatthdmed);
HI_VOID VPSS_Tnr_SetFlatthdmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 flatthdmin);
HI_VOID VPSS_Tnr_SetSmvythd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 smvythd);
HI_VOID VPSS_Tnr_SetSmvxthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 smvxthd);
HI_VOID VPSS_Tnr_SetDiscardsmvyen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 discardsmvyen);
HI_VOID VPSS_Tnr_SetDiscardsmvxen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 discardsmvxen);
HI_VOID VPSS_Tnr_SetGmAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 gm_adj);
HI_VOID VPSS_Tnr_SetMvlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mvlpfmode);
HI_VOID VPSS_Tnr_SetMvrefmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mvrefmode);
HI_VOID VPSS_Tnr_SetMotionestimateen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motionestimateen);
HI_VOID VPSS_Tnr_SetMagPnlCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mag_pnl_core_xmv);
HI_VOID VPSS_Tnr_SetMagPnlGainXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mag_pnl_gain_xmv);
HI_VOID VPSS_Tnr_SetMagPnlCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mag_pnl_core_0mv);
HI_VOID VPSS_Tnr_SetMagPnlGain0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mag_pnl_gain_0mv);
HI_VOID VPSS_Tnr_SetStdPnlCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_pnl_core_xmv);
HI_VOID VPSS_Tnr_SetStdPnlGainXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_pnl_gain_xmv);
HI_VOID VPSS_Tnr_SetStdPnlCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_pnl_core_0mv);
HI_VOID VPSS_Tnr_SetStdPnlGain0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_pnl_gain_0mv);
HI_VOID VPSS_Tnr_SetStdCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_core_xmv);
HI_VOID VPSS_Tnr_SetStdCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_core_0mv);
HI_VOID VPSS_Tnr_SetStdPnlCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_pnl_core);
HI_VOID VPSS_Tnr_SetStdPnlGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_pnl_gain);
HI_VOID VPSS_Tnr_SetAdjXmvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 adj_xmv_max);
HI_VOID VPSS_Tnr_SetAdj0mvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 adj_0mv_max);
HI_VOID VPSS_Tnr_SetAdjXmvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 adj_xmv_min);
HI_VOID VPSS_Tnr_SetAdj0mvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 adj_0mv_min);
HI_VOID VPSS_Tnr_SetAdjMvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 adj_mv_min);
HI_VOID VPSS_Tnr_SetAdjMvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 adj_mv_max);
HI_VOID VPSS_Tnr_SetCbcrweight2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbcrweight2);
HI_VOID VPSS_Tnr_SetCbcrweight1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbcrweight1);
HI_VOID VPSS_Tnr_SetCbcrupdateen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbcrupdateen);
HI_VOID VPSS_Tnr_SetCrend1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 crend1);
HI_VOID VPSS_Tnr_SetCbend1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbend1);
HI_VOID VPSS_Tnr_SetCrbegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 crbegin1);
HI_VOID VPSS_Tnr_SetCbbegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbbegin1);
HI_VOID VPSS_Tnr_SetCrend2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 crend2);
HI_VOID VPSS_Tnr_SetCbend2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbend2);
HI_VOID VPSS_Tnr_SetCrbegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 crbegin2);
HI_VOID VPSS_Tnr_SetCbbegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbbegin2);
HI_VOID VPSS_Tnr_SetMotionmergeratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motionmergeratio);
HI_VOID VPSS_Tnr_SetPremotionalpha(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 premotionalpha);
HI_VOID VPSS_Tnr_SetPremotionmergemode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 premotionmergemode);
HI_VOID VPSS_Tnr_SetCmotioncore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotioncore);
HI_VOID VPSS_Tnr_SetCmotiongain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotiongain);
HI_VOID VPSS_Tnr_SetYmotioncore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotioncore);
HI_VOID VPSS_Tnr_SetYmotiongain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotiongain);
HI_VOID VPSS_Tnr_SetMotionmappingen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motionmappingen);
HI_VOID VPSS_Tnr_SetSaltuslevel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 saltuslevel);
HI_VOID VPSS_Tnr_SetSaltusdecten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 saltusdecten);
HI_VOID VPSS_Tnr_SetCmclpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmclpfmode);
HI_VOID VPSS_Tnr_SetYmclpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymclpfmode);
HI_VOID VPSS_Tnr_SetCmcadjen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmcadjen);
HI_VOID VPSS_Tnr_SetYmcadjen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymcadjen);
HI_VOID VPSS_Tnr_SetCnonrrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cnonrrange);
HI_VOID VPSS_Tnr_SetYnonrrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ynonrrange);
HI_VOID VPSS_Tnr_SetCmotionmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionmode);
HI_VOID VPSS_Tnr_SetYmotionmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionmode);
HI_VOID VPSS_Tnr_SetScenechangeinfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechangeinfo);
HI_VOID VPSS_Tnr_SetScenechangeen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechangeen);
HI_VOID VPSS_Tnr_SetCfgCmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cfg_cmdcore);
HI_VOID VPSS_Tnr_SetCfgCmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cfg_cmdgain);
HI_VOID VPSS_Tnr_SetCfgYmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cfg_ymdcore);
HI_VOID VPSS_Tnr_SetCfgYmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cfg_ymdgain);
HI_VOID VPSS_Tnr_SetFlatinfoymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 flatinfoymax);
HI_VOID VPSS_Tnr_SetFlatinfoxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 flatinfoxmax);
HI_VOID VPSS_Tnr_SetFlatinfoymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 flatinfoymin);
HI_VOID VPSS_Tnr_SetFlatinfoxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 flatinfoxmin);
HI_VOID VPSS_Tnr_SetYblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingymax);
HI_VOID VPSS_Tnr_SetYblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingxmax);
HI_VOID VPSS_Tnr_SetYblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingymin);
HI_VOID VPSS_Tnr_SetYblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingxmin);
HI_VOID VPSS_Tnr_SetCblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingymax);
HI_VOID VPSS_Tnr_SetCblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingxmax);
HI_VOID VPSS_Tnr_SetCblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingymin);
HI_VOID VPSS_Tnr_SetCblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingxmin);
HI_VOID VPSS_Tnr_SetDtblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dtblendingymax);
HI_VOID VPSS_Tnr_SetDtblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dtblendingxmax);
HI_VOID VPSS_Tnr_SetDtblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dtblendingymin);
HI_VOID VPSS_Tnr_SetDtblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dtblendingxmin);
HI_VOID VPSS_Tnr_SetKRgdifycore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_rgdifycore);
HI_VOID VPSS_Tnr_SetGRgdifycore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_rgdifycore);
HI_VOID VPSS_Tnr_SetCoreRgdify(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_rgdify);
HI_VOID VPSS_Tnr_SetLmtRgdify(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lmt_rgdify);
HI_VOID VPSS_Tnr_SetCoefSadlpf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 coef_sadlpf);
HI_VOID VPSS_Tnr_SetK1TpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k1_tpdif_rgsad);
HI_VOID VPSS_Tnr_SetKmvRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 kmv_rgsad);
HI_VOID VPSS_Tnr_SetKTpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_tpdif_rgsad);
HI_VOID VPSS_Tnr_SetGTpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 g_tpdif_rgsad);
HI_VOID VPSS_Tnr_SetThmagRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 thmag_rgmv);
HI_VOID VPSS_Tnr_SetThSaddifRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_saddif_rgmv);
HI_VOID VPSS_Tnr_SetTh0mvsadRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_0mvsad_rgmv);
HI_VOID VPSS_Tnr_SetCoreMagRg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mag_rg);
HI_VOID VPSS_Tnr_SetLmtMagRg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lmt_mag_rg);
HI_VOID VPSS_Tnr_SetCoreMvRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mv_rgmvls);
HI_VOID VPSS_Tnr_SetKMvRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_mv_rgmvls);
HI_VOID VPSS_Tnr_SetCoreMagRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 core_mag_rgmvls);
HI_VOID VPSS_Tnr_SetKMagRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_mag_rgmvls);
HI_VOID VPSS_Tnr_SetThMvadjRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_mvadj_rgmvls);
HI_VOID VPSS_Tnr_SetEnMvadjRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 en_mvadj_rgmvls);
HI_VOID VPSS_Tnr_SetKSadRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_sad_rgls);
HI_VOID VPSS_Tnr_SetThMagRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_mag_rgls);
HI_VOID VPSS_Tnr_SetThSadRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 th_sad_rgls);
HI_VOID VPSS_Tnr_SetKSadcoreRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_sadcore_rgmv);
HI_VOID VPSS_Tnr_SetRpMagthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_magth_rgmv);
HI_VOID VPSS_Tnr_SetRpSadthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_sadth_rgmv);
HI_VOID VPSS_Tnr_SetRpMvxthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_mvxth_rgmv);
HI_VOID VPSS_Tnr_SetRpcounterth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rpcounterth);
HI_VOID VPSS_Tnr_SetKRpcounter(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 k_rpcounter);
HI_VOID VPSS_Tnr_SetRpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_en);
HI_VOID VPSS_Tnr_SetRpDifsadthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difsadth_rgmv);
HI_VOID VPSS_Tnr_SetRpDifmvxthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difmvxth_rgmv);
HI_VOID VPSS_Tnr_SetRpDifsadthTb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difsadth_tb);
HI_VOID VPSS_Tnr_SetRpDifmvxthSp(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 rp_difmvxth_sp);
HI_VOID VPSS_Tnr_SetMeanMotionRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio3);
HI_VOID VPSS_Tnr_SetMeanMotionRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio2);
HI_VOID VPSS_Tnr_SetMeanMotionRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio1);
HI_VOID VPSS_Tnr_SetMeanMotionRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio0);
HI_VOID VPSS_Tnr_SetMeanMotionRatio7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio7);
HI_VOID VPSS_Tnr_SetMeanMotionRatio6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio6);
HI_VOID VPSS_Tnr_SetMeanMotionRatio5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio5);
HI_VOID VPSS_Tnr_SetMeanMotionRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio4);
HI_VOID VPSS_Tnr_SetMeanMotionRatio11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio11);
HI_VOID VPSS_Tnr_SetMeanMotionRatio10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio10);
HI_VOID VPSS_Tnr_SetMeanMotionRatio9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio9);
HI_VOID VPSS_Tnr_SetMeanMotionRatio8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio8);
HI_VOID VPSS_Tnr_SetMeanMotionRatio15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio15);
HI_VOID VPSS_Tnr_SetMeanMotionRatio14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio14);
HI_VOID VPSS_Tnr_SetMeanMotionRatio13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio13);
HI_VOID VPSS_Tnr_SetMeanMotionRatio12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mean_motion_ratio12);
HI_VOID VPSS_Tnr_SetYblendingalphalut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut3);
HI_VOID VPSS_Tnr_SetYblendingalphalut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut2);
HI_VOID VPSS_Tnr_SetYblendingalphalut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut1);
HI_VOID VPSS_Tnr_SetYblendingalphalut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut0);
HI_VOID VPSS_Tnr_SetYblendingalphalut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut7);
HI_VOID VPSS_Tnr_SetYblendingalphalut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut6);
HI_VOID VPSS_Tnr_SetYblendingalphalut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut5);
HI_VOID VPSS_Tnr_SetYblendingalphalut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut4);
HI_VOID VPSS_Tnr_SetYblendingalphalut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut11);
HI_VOID VPSS_Tnr_SetYblendingalphalut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut10);
HI_VOID VPSS_Tnr_SetYblendingalphalut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut9);
HI_VOID VPSS_Tnr_SetYblendingalphalut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut8);
HI_VOID VPSS_Tnr_SetYblendingalphalut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut15);
HI_VOID VPSS_Tnr_SetYblendingalphalut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut14);
HI_VOID VPSS_Tnr_SetYblendingalphalut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut13);
HI_VOID VPSS_Tnr_SetYblendingalphalut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut12);
HI_VOID VPSS_Tnr_SetYblendingalphalut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut19);
HI_VOID VPSS_Tnr_SetYblendingalphalut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut18);
HI_VOID VPSS_Tnr_SetYblendingalphalut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut17);
HI_VOID VPSS_Tnr_SetYblendingalphalut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut16);
HI_VOID VPSS_Tnr_SetYblendingalphalut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut23);
HI_VOID VPSS_Tnr_SetYblendingalphalut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut22);
HI_VOID VPSS_Tnr_SetYblendingalphalut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut21);
HI_VOID VPSS_Tnr_SetYblendingalphalut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut20);
HI_VOID VPSS_Tnr_SetYblendingalphalut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut27);
HI_VOID VPSS_Tnr_SetYblendingalphalut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut26);
HI_VOID VPSS_Tnr_SetYblendingalphalut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut25);
HI_VOID VPSS_Tnr_SetYblendingalphalut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut24);
HI_VOID VPSS_Tnr_SetYblendingalphalut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut31);
HI_VOID VPSS_Tnr_SetYblendingalphalut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut30);
HI_VOID VPSS_Tnr_SetYblendingalphalut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut29);
HI_VOID VPSS_Tnr_SetYblendingalphalut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 yblendingalphalut28);
HI_VOID VPSS_Tnr_SetCblendingalphalut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut3);
HI_VOID VPSS_Tnr_SetCblendingalphalut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut2);
HI_VOID VPSS_Tnr_SetCblendingalphalut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut1);
HI_VOID VPSS_Tnr_SetCblendingalphalut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut0);
HI_VOID VPSS_Tnr_SetCblendingalphalut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut7);
HI_VOID VPSS_Tnr_SetCblendingalphalut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut6);
HI_VOID VPSS_Tnr_SetCblendingalphalut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut5);
HI_VOID VPSS_Tnr_SetCblendingalphalut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut4);
HI_VOID VPSS_Tnr_SetCblendingalphalut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut11);
HI_VOID VPSS_Tnr_SetCblendingalphalut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut10);
HI_VOID VPSS_Tnr_SetCblendingalphalut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut9);
HI_VOID VPSS_Tnr_SetCblendingalphalut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut8);
HI_VOID VPSS_Tnr_SetCblendingalphalut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut15);
HI_VOID VPSS_Tnr_SetCblendingalphalut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut14);
HI_VOID VPSS_Tnr_SetCblendingalphalut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut13);
HI_VOID VPSS_Tnr_SetCblendingalphalut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut12);
HI_VOID VPSS_Tnr_SetCblendingalphalut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut19);
HI_VOID VPSS_Tnr_SetCblendingalphalut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut18);
HI_VOID VPSS_Tnr_SetCblendingalphalut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut17);
HI_VOID VPSS_Tnr_SetCblendingalphalut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut16);
HI_VOID VPSS_Tnr_SetCblendingalphalut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut23);
HI_VOID VPSS_Tnr_SetCblendingalphalut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut22);
HI_VOID VPSS_Tnr_SetCblendingalphalut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut21);
HI_VOID VPSS_Tnr_SetCblendingalphalut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut20);
HI_VOID VPSS_Tnr_SetCblendingalphalut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut27);
HI_VOID VPSS_Tnr_SetCblendingalphalut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut26);
HI_VOID VPSS_Tnr_SetCblendingalphalut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut25);
HI_VOID VPSS_Tnr_SetCblendingalphalut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut24);
HI_VOID VPSS_Tnr_SetCblendingalphalut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut31);
HI_VOID VPSS_Tnr_SetCblendingalphalut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut30);
HI_VOID VPSS_Tnr_SetCblendingalphalut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut29);
HI_VOID VPSS_Tnr_SetCblendingalphalut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cblendingalphalut28);
HI_VOID VPSS_Tnr_SetYmotionstrlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut3);
HI_VOID VPSS_Tnr_SetYmotionstrlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut2);
HI_VOID VPSS_Tnr_SetYmotionstrlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut1);
HI_VOID VPSS_Tnr_SetYmotionstrlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut0);
HI_VOID VPSS_Tnr_SetYmotionstrlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut7);
HI_VOID VPSS_Tnr_SetYmotionstrlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut6);
HI_VOID VPSS_Tnr_SetYmotionstrlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut5);
HI_VOID VPSS_Tnr_SetYmotionstrlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut4);
HI_VOID VPSS_Tnr_SetYmotionstrlut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut11);
HI_VOID VPSS_Tnr_SetYmotionstrlut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut10);
HI_VOID VPSS_Tnr_SetYmotionstrlut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut9);
HI_VOID VPSS_Tnr_SetYmotionstrlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut8);
HI_VOID VPSS_Tnr_SetYmotionstrlut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut15);
HI_VOID VPSS_Tnr_SetYmotionstrlut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut14);
HI_VOID VPSS_Tnr_SetYmotionstrlut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut13);
HI_VOID VPSS_Tnr_SetYmotionstrlut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut12);
HI_VOID VPSS_Tnr_SetYmotionstrlut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut19);
HI_VOID VPSS_Tnr_SetYmotionstrlut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut18);
HI_VOID VPSS_Tnr_SetYmotionstrlut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut17);
HI_VOID VPSS_Tnr_SetYmotionstrlut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut16);
HI_VOID VPSS_Tnr_SetYmotionstrlut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut23);
HI_VOID VPSS_Tnr_SetYmotionstrlut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut22);
HI_VOID VPSS_Tnr_SetYmotionstrlut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut21);
HI_VOID VPSS_Tnr_SetYmotionstrlut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut20);
HI_VOID VPSS_Tnr_SetYmotionstrlut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut27);
HI_VOID VPSS_Tnr_SetYmotionstrlut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut26);
HI_VOID VPSS_Tnr_SetYmotionstrlut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut25);
HI_VOID VPSS_Tnr_SetYmotionstrlut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut24);
HI_VOID VPSS_Tnr_SetYmotionstrlut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut31);
HI_VOID VPSS_Tnr_SetYmotionstrlut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut30);
HI_VOID VPSS_Tnr_SetYmotionstrlut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut29);
HI_VOID VPSS_Tnr_SetYmotionstrlut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut28);
HI_VOID VPSS_Tnr_SetYmotionstrlut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut35);
HI_VOID VPSS_Tnr_SetYmotionstrlut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut34);
HI_VOID VPSS_Tnr_SetYmotionstrlut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut33);
HI_VOID VPSS_Tnr_SetYmotionstrlut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut32);
HI_VOID VPSS_Tnr_SetYmotionstrlut39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut39);
HI_VOID VPSS_Tnr_SetYmotionstrlut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut38);
HI_VOID VPSS_Tnr_SetYmotionstrlut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut37);
HI_VOID VPSS_Tnr_SetYmotionstrlut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut36);
HI_VOID VPSS_Tnr_SetYmotionstrlut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut43);
HI_VOID VPSS_Tnr_SetYmotionstrlut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut42);
HI_VOID VPSS_Tnr_SetYmotionstrlut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut41);
HI_VOID VPSS_Tnr_SetYmotionstrlut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut40);
HI_VOID VPSS_Tnr_SetYmotionstrlut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut47);
HI_VOID VPSS_Tnr_SetYmotionstrlut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut46);
HI_VOID VPSS_Tnr_SetYmotionstrlut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut45);
HI_VOID VPSS_Tnr_SetYmotionstrlut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut44);
HI_VOID VPSS_Tnr_SetYmotionstrlut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut51);
HI_VOID VPSS_Tnr_SetYmotionstrlut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut50);
HI_VOID VPSS_Tnr_SetYmotionstrlut49(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut49);
HI_VOID VPSS_Tnr_SetYmotionstrlut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut48);
HI_VOID VPSS_Tnr_SetYmotionstrlut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut55);
HI_VOID VPSS_Tnr_SetYmotionstrlut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut54);
HI_VOID VPSS_Tnr_SetYmotionstrlut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut53);
HI_VOID VPSS_Tnr_SetYmotionstrlut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut52);
HI_VOID VPSS_Tnr_SetYmotionstrlut59(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut59);
HI_VOID VPSS_Tnr_SetYmotionstrlut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut58);
HI_VOID VPSS_Tnr_SetYmotionstrlut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut57);
HI_VOID VPSS_Tnr_SetYmotionstrlut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut56);
HI_VOID VPSS_Tnr_SetYmotionstrlut63(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut63);
HI_VOID VPSS_Tnr_SetYmotionstrlut62(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut62);
HI_VOID VPSS_Tnr_SetYmotionstrlut61(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut61);
HI_VOID VPSS_Tnr_SetYmotionstrlut60(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut60);
HI_VOID VPSS_Tnr_SetYmotionstrlut67(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut67);
HI_VOID VPSS_Tnr_SetYmotionstrlut66(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut66);
HI_VOID VPSS_Tnr_SetYmotionstrlut65(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut65);
HI_VOID VPSS_Tnr_SetYmotionstrlut64(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut64);
HI_VOID VPSS_Tnr_SetYmotionstrlut71(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut71);
HI_VOID VPSS_Tnr_SetYmotionstrlut70(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut70);
HI_VOID VPSS_Tnr_SetYmotionstrlut69(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut69);
HI_VOID VPSS_Tnr_SetYmotionstrlut68(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut68);
HI_VOID VPSS_Tnr_SetYmotionstrlut75(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut75);
HI_VOID VPSS_Tnr_SetYmotionstrlut74(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut74);
HI_VOID VPSS_Tnr_SetYmotionstrlut73(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut73);
HI_VOID VPSS_Tnr_SetYmotionstrlut72(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut72);
HI_VOID VPSS_Tnr_SetYmotionstrlut79(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut79);
HI_VOID VPSS_Tnr_SetYmotionstrlut78(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut78);
HI_VOID VPSS_Tnr_SetYmotionstrlut77(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut77);
HI_VOID VPSS_Tnr_SetYmotionstrlut76(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut76);
HI_VOID VPSS_Tnr_SetYmotionstrlut83(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut83);
HI_VOID VPSS_Tnr_SetYmotionstrlut82(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut82);
HI_VOID VPSS_Tnr_SetYmotionstrlut81(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut81);
HI_VOID VPSS_Tnr_SetYmotionstrlut80(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut80);
HI_VOID VPSS_Tnr_SetYmotionstrlut87(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut87);
HI_VOID VPSS_Tnr_SetYmotionstrlut86(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut86);
HI_VOID VPSS_Tnr_SetYmotionstrlut85(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut85);
HI_VOID VPSS_Tnr_SetYmotionstrlut84(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut84);
HI_VOID VPSS_Tnr_SetYmotionstrlut91(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut91);
HI_VOID VPSS_Tnr_SetYmotionstrlut90(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut90);
HI_VOID VPSS_Tnr_SetYmotionstrlut89(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut89);
HI_VOID VPSS_Tnr_SetYmotionstrlut88(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut88);
HI_VOID VPSS_Tnr_SetYmotionstrlut95(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut95);
HI_VOID VPSS_Tnr_SetYmotionstrlut94(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut94);
HI_VOID VPSS_Tnr_SetYmotionstrlut93(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut93);
HI_VOID VPSS_Tnr_SetYmotionstrlut92(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut92);
HI_VOID VPSS_Tnr_SetYmotionstrlut99(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut99);
HI_VOID VPSS_Tnr_SetYmotionstrlut98(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut98);
HI_VOID VPSS_Tnr_SetYmotionstrlut97(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut97);
HI_VOID VPSS_Tnr_SetYmotionstrlut96(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut96);
HI_VOID VPSS_Tnr_SetYmotionstrlut103(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut103);
HI_VOID VPSS_Tnr_SetYmotionstrlut102(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut102);
HI_VOID VPSS_Tnr_SetYmotionstrlut101(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut101);
HI_VOID VPSS_Tnr_SetYmotionstrlut100(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut100);
HI_VOID VPSS_Tnr_SetYmotionstrlut107(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut107);
HI_VOID VPSS_Tnr_SetYmotionstrlut106(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut106);
HI_VOID VPSS_Tnr_SetYmotionstrlut105(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut105);
HI_VOID VPSS_Tnr_SetYmotionstrlut104(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut104);
HI_VOID VPSS_Tnr_SetYmotionstrlut111(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut111);
HI_VOID VPSS_Tnr_SetYmotionstrlut110(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut110);
HI_VOID VPSS_Tnr_SetYmotionstrlut109(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut109);
HI_VOID VPSS_Tnr_SetYmotionstrlut108(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut108);
HI_VOID VPSS_Tnr_SetYmotionstrlut115(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut115);
HI_VOID VPSS_Tnr_SetYmotionstrlut114(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut114);
HI_VOID VPSS_Tnr_SetYmotionstrlut113(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut113);
HI_VOID VPSS_Tnr_SetYmotionstrlut112(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut112);
HI_VOID VPSS_Tnr_SetYmotionstrlut119(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut119);
HI_VOID VPSS_Tnr_SetYmotionstrlut118(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut118);
HI_VOID VPSS_Tnr_SetYmotionstrlut117(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut117);
HI_VOID VPSS_Tnr_SetYmotionstrlut116(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut116);
HI_VOID VPSS_Tnr_SetYmotionstrlut123(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut123);
HI_VOID VPSS_Tnr_SetYmotionstrlut122(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut122);
HI_VOID VPSS_Tnr_SetYmotionstrlut121(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut121);
HI_VOID VPSS_Tnr_SetYmotionstrlut120(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut120);
HI_VOID VPSS_Tnr_SetYmotionstrlut127(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut127);
HI_VOID VPSS_Tnr_SetYmotionstrlut126(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut126);
HI_VOID VPSS_Tnr_SetYmotionstrlut125(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut125);
HI_VOID VPSS_Tnr_SetYmotionstrlut124(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymotionstrlut124);
HI_VOID VPSS_Tnr_SetCmotionstrlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut3);
HI_VOID VPSS_Tnr_SetCmotionstrlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut2);
HI_VOID VPSS_Tnr_SetCmotionstrlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut1);
HI_VOID VPSS_Tnr_SetCmotionstrlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut0);
HI_VOID VPSS_Tnr_SetCmotionstrlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut7);
HI_VOID VPSS_Tnr_SetCmotionstrlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut6);
HI_VOID VPSS_Tnr_SetCmotionstrlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut5);
HI_VOID VPSS_Tnr_SetCmotionstrlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut4);
HI_VOID VPSS_Tnr_SetCmotionstrlut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut11);
HI_VOID VPSS_Tnr_SetCmotionstrlut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut10);
HI_VOID VPSS_Tnr_SetCmotionstrlut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut9);
HI_VOID VPSS_Tnr_SetCmotionstrlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut8);
HI_VOID VPSS_Tnr_SetCmotionstrlut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut15);
HI_VOID VPSS_Tnr_SetCmotionstrlut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut14);
HI_VOID VPSS_Tnr_SetCmotionstrlut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut13);
HI_VOID VPSS_Tnr_SetCmotionstrlut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut12);
HI_VOID VPSS_Tnr_SetCmotionstrlut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut19);
HI_VOID VPSS_Tnr_SetCmotionstrlut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut18);
HI_VOID VPSS_Tnr_SetCmotionstrlut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut17);
HI_VOID VPSS_Tnr_SetCmotionstrlut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut16);
HI_VOID VPSS_Tnr_SetCmotionstrlut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut23);
HI_VOID VPSS_Tnr_SetCmotionstrlut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut22);
HI_VOID VPSS_Tnr_SetCmotionstrlut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut21);
HI_VOID VPSS_Tnr_SetCmotionstrlut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut20);
HI_VOID VPSS_Tnr_SetCmotionstrlut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut27);
HI_VOID VPSS_Tnr_SetCmotionstrlut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut26);
HI_VOID VPSS_Tnr_SetCmotionstrlut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut25);
HI_VOID VPSS_Tnr_SetCmotionstrlut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut24);
HI_VOID VPSS_Tnr_SetCmotionstrlut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut31);
HI_VOID VPSS_Tnr_SetCmotionstrlut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut30);
HI_VOID VPSS_Tnr_SetCmotionstrlut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut29);
HI_VOID VPSS_Tnr_SetCmotionstrlut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut28);
HI_VOID VPSS_Tnr_SetCmotionstrlut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut35);
HI_VOID VPSS_Tnr_SetCmotionstrlut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut34);
HI_VOID VPSS_Tnr_SetCmotionstrlut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut33);
HI_VOID VPSS_Tnr_SetCmotionstrlut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut32);
HI_VOID VPSS_Tnr_SetCmotionstrlut39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut39);
HI_VOID VPSS_Tnr_SetCmotionstrlut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut38);
HI_VOID VPSS_Tnr_SetCmotionstrlut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut37);
HI_VOID VPSS_Tnr_SetCmotionstrlut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut36);
HI_VOID VPSS_Tnr_SetCmotionstrlut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut43);
HI_VOID VPSS_Tnr_SetCmotionstrlut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut42);
HI_VOID VPSS_Tnr_SetCmotionstrlut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut41);
HI_VOID VPSS_Tnr_SetCmotionstrlut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut40);
HI_VOID VPSS_Tnr_SetCmotionstrlut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut47);
HI_VOID VPSS_Tnr_SetCmotionstrlut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut46);
HI_VOID VPSS_Tnr_SetCmotionstrlut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut45);
HI_VOID VPSS_Tnr_SetCmotionstrlut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut44);
HI_VOID VPSS_Tnr_SetCmotionstrlut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut51);
HI_VOID VPSS_Tnr_SetCmotionstrlut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut50);
HI_VOID VPSS_Tnr_SetCmotionstrlut49(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut49);
HI_VOID VPSS_Tnr_SetCmotionstrlut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut48);
HI_VOID VPSS_Tnr_SetCmotionstrlut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut55);
HI_VOID VPSS_Tnr_SetCmotionstrlut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut54);
HI_VOID VPSS_Tnr_SetCmotionstrlut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut53);
HI_VOID VPSS_Tnr_SetCmotionstrlut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut52);
HI_VOID VPSS_Tnr_SetCmotionstrlut59(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut59);
HI_VOID VPSS_Tnr_SetCmotionstrlut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut58);
HI_VOID VPSS_Tnr_SetCmotionstrlut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut57);
HI_VOID VPSS_Tnr_SetCmotionstrlut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut56);
HI_VOID VPSS_Tnr_SetCmotionstrlut63(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut63);
HI_VOID VPSS_Tnr_SetCmotionstrlut62(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut62);
HI_VOID VPSS_Tnr_SetCmotionstrlut61(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut61);
HI_VOID VPSS_Tnr_SetCmotionstrlut60(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut60);
HI_VOID VPSS_Tnr_SetCmotionstrlut67(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut67);
HI_VOID VPSS_Tnr_SetCmotionstrlut66(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut66);
HI_VOID VPSS_Tnr_SetCmotionstrlut65(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut65);
HI_VOID VPSS_Tnr_SetCmotionstrlut64(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut64);
HI_VOID VPSS_Tnr_SetCmotionstrlut71(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut71);
HI_VOID VPSS_Tnr_SetCmotionstrlut70(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut70);
HI_VOID VPSS_Tnr_SetCmotionstrlut69(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut69);
HI_VOID VPSS_Tnr_SetCmotionstrlut68(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut68);
HI_VOID VPSS_Tnr_SetCmotionstrlut75(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut75);
HI_VOID VPSS_Tnr_SetCmotionstrlut74(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut74);
HI_VOID VPSS_Tnr_SetCmotionstrlut73(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut73);
HI_VOID VPSS_Tnr_SetCmotionstrlut72(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut72);
HI_VOID VPSS_Tnr_SetCmotionstrlut79(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut79);
HI_VOID VPSS_Tnr_SetCmotionstrlut78(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut78);
HI_VOID VPSS_Tnr_SetCmotionstrlut77(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut77);
HI_VOID VPSS_Tnr_SetCmotionstrlut76(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut76);
HI_VOID VPSS_Tnr_SetCmotionstrlut83(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut83);
HI_VOID VPSS_Tnr_SetCmotionstrlut82(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut82);
HI_VOID VPSS_Tnr_SetCmotionstrlut81(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut81);
HI_VOID VPSS_Tnr_SetCmotionstrlut80(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut80);
HI_VOID VPSS_Tnr_SetCmotionstrlut87(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut87);
HI_VOID VPSS_Tnr_SetCmotionstrlut86(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut86);
HI_VOID VPSS_Tnr_SetCmotionstrlut85(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut85);
HI_VOID VPSS_Tnr_SetCmotionstrlut84(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut84);
HI_VOID VPSS_Tnr_SetCmotionstrlut91(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut91);
HI_VOID VPSS_Tnr_SetCmotionstrlut90(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut90);
HI_VOID VPSS_Tnr_SetCmotionstrlut89(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut89);
HI_VOID VPSS_Tnr_SetCmotionstrlut88(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut88);
HI_VOID VPSS_Tnr_SetCmotionstrlut95(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut95);
HI_VOID VPSS_Tnr_SetCmotionstrlut94(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut94);
HI_VOID VPSS_Tnr_SetCmotionstrlut93(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut93);
HI_VOID VPSS_Tnr_SetCmotionstrlut92(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut92);
HI_VOID VPSS_Tnr_SetCmotionstrlut99(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut99);
HI_VOID VPSS_Tnr_SetCmotionstrlut98(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut98);
HI_VOID VPSS_Tnr_SetCmotionstrlut97(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut97);
HI_VOID VPSS_Tnr_SetCmotionstrlut96(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut96);
HI_VOID VPSS_Tnr_SetCmotionstrlut103(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut103);
HI_VOID VPSS_Tnr_SetCmotionstrlut102(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut102);
HI_VOID VPSS_Tnr_SetCmotionstrlut101(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut101);
HI_VOID VPSS_Tnr_SetCmotionstrlut100(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut100);
HI_VOID VPSS_Tnr_SetCmotionstrlut107(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut107);
HI_VOID VPSS_Tnr_SetCmotionstrlut106(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut106);
HI_VOID VPSS_Tnr_SetCmotionstrlut105(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut105);
HI_VOID VPSS_Tnr_SetCmotionstrlut104(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut104);
HI_VOID VPSS_Tnr_SetCmotionstrlut111(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut111);
HI_VOID VPSS_Tnr_SetCmotionstrlut110(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut110);
HI_VOID VPSS_Tnr_SetCmotionstrlut109(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut109);
HI_VOID VPSS_Tnr_SetCmotionstrlut108(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut108);
HI_VOID VPSS_Tnr_SetCmotionstrlut115(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut115);
HI_VOID VPSS_Tnr_SetCmotionstrlut114(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut114);
HI_VOID VPSS_Tnr_SetCmotionstrlut113(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut113);
HI_VOID VPSS_Tnr_SetCmotionstrlut112(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut112);
HI_VOID VPSS_Tnr_SetCmotionstrlut119(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut119);
HI_VOID VPSS_Tnr_SetCmotionstrlut118(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut118);
HI_VOID VPSS_Tnr_SetCmotionstrlut117(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut117);
HI_VOID VPSS_Tnr_SetCmotionstrlut116(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut116);
HI_VOID VPSS_Tnr_SetCmotionstrlut123(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut123);
HI_VOID VPSS_Tnr_SetCmotionstrlut122(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut122);
HI_VOID VPSS_Tnr_SetCmotionstrlut121(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut121);
HI_VOID VPSS_Tnr_SetCmotionstrlut120(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut120);
HI_VOID VPSS_Tnr_SetCmotionstrlut127(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut127);
HI_VOID VPSS_Tnr_SetCmotionstrlut126(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut126);
HI_VOID VPSS_Tnr_SetCmotionstrlut125(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut125);
HI_VOID VPSS_Tnr_SetCmotionstrlut124(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cmotionstrlut124);
HI_VOID VPSS_Tnr_SetLgdifyLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_3);
HI_VOID VPSS_Tnr_SetLgdifyLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_2);
HI_VOID VPSS_Tnr_SetLgdifyLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_1);
HI_VOID VPSS_Tnr_SetLgdifyLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_0);
HI_VOID VPSS_Tnr_SetLgdifyLut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_7);
HI_VOID VPSS_Tnr_SetLgdifyLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_6);
HI_VOID VPSS_Tnr_SetLgdifyLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_5);
HI_VOID VPSS_Tnr_SetLgdifyLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_4);
HI_VOID VPSS_Tnr_SetLgdifyLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_11);
HI_VOID VPSS_Tnr_SetLgdifyLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_10);
HI_VOID VPSS_Tnr_SetLgdifyLut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_9);
HI_VOID VPSS_Tnr_SetLgdifyLut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lgdify_lut_8);
HI_VOID VPSS_Tnr_SetPmvLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_3);
HI_VOID VPSS_Tnr_SetPmvLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_2);
HI_VOID VPSS_Tnr_SetPmvLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_1);
HI_VOID VPSS_Tnr_SetPmvLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_0);
HI_VOID VPSS_Tnr_SetPmvLut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_7);
HI_VOID VPSS_Tnr_SetPmvLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_6);
HI_VOID VPSS_Tnr_SetPmvLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_5);
HI_VOID VPSS_Tnr_SetPmvLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_4);
HI_VOID VPSS_Tnr_SetPmvLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_11);
HI_VOID VPSS_Tnr_SetPmvLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_10);
HI_VOID VPSS_Tnr_SetPmvLut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_9);
HI_VOID VPSS_Tnr_SetPmvLut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_8);
HI_VOID VPSS_Tnr_SetPmvLut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_15);
HI_VOID VPSS_Tnr_SetPmvLut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_14);
HI_VOID VPSS_Tnr_SetPmvLut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_13);
HI_VOID VPSS_Tnr_SetPmvLut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 pmv_lut_12);
HI_VOID VPSS_Tnr_SetNoiseLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_3);
HI_VOID VPSS_Tnr_SetNoiseLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_2);
HI_VOID VPSS_Tnr_SetNoiseLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_1);
HI_VOID VPSS_Tnr_SetNoiseLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_0);
HI_VOID VPSS_Tnr_SetNoiseLut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_7);
HI_VOID VPSS_Tnr_SetNoiseLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_6);
HI_VOID VPSS_Tnr_SetNoiseLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_5);
HI_VOID VPSS_Tnr_SetNoiseLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_4);
HI_VOID VPSS_Tnr_SetNoiseLut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_9);
HI_VOID VPSS_Tnr_SetNoiseLut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 noise_lut_8);
HI_VOID VPSS_Tnr_SetCchgLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_3);
HI_VOID VPSS_Tnr_SetCchgLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_2);
HI_VOID VPSS_Tnr_SetCchgLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_1);
HI_VOID VPSS_Tnr_SetCchgLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_0);
HI_VOID VPSS_Tnr_SetCchgLut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_7);
HI_VOID VPSS_Tnr_SetCchgLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_6);
HI_VOID VPSS_Tnr_SetCchgLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_5);
HI_VOID VPSS_Tnr_SetCchgLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_4);
HI_VOID VPSS_Tnr_SetCchgLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_11);
HI_VOID VPSS_Tnr_SetCchgLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_10);
HI_VOID VPSS_Tnr_SetCchgLut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_9);
HI_VOID VPSS_Tnr_SetCchgLut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cchg_lut_8);
HI_VOID VPSS_Tnr_SetDirLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_3);
HI_VOID VPSS_Tnr_SetDirLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_2);
HI_VOID VPSS_Tnr_SetDirLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_1);
HI_VOID VPSS_Tnr_SetDirLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_0);
HI_VOID VPSS_Tnr_SetDirLut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_7);
HI_VOID VPSS_Tnr_SetDirLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_6);
HI_VOID VPSS_Tnr_SetDirLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_5);
HI_VOID VPSS_Tnr_SetDirLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dir_lut_4);
HI_VOID VPSS_Tnr_SetYmdLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_3);
HI_VOID VPSS_Tnr_SetYmdLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_2);
HI_VOID VPSS_Tnr_SetYmdLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_1);
HI_VOID VPSS_Tnr_SetYmdLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_0);
HI_VOID VPSS_Tnr_SetYmdLut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_7);
HI_VOID VPSS_Tnr_SetYmdLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_6);
HI_VOID VPSS_Tnr_SetYmdLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_5);
HI_VOID VPSS_Tnr_SetYmdLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_4);
HI_VOID VPSS_Tnr_SetYmdLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_11);
HI_VOID VPSS_Tnr_SetYmdLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_10);
HI_VOID VPSS_Tnr_SetYmdLut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_9);
HI_VOID VPSS_Tnr_SetYmdLut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_8);
HI_VOID VPSS_Tnr_SetYmdLut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_15);
HI_VOID VPSS_Tnr_SetYmdLut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_14);
HI_VOID VPSS_Tnr_SetYmdLut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_13);
HI_VOID VPSS_Tnr_SetYmdLut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ymd_lut_12);
HI_VOID VPSS_Tnr_SetStdLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_3);
HI_VOID VPSS_Tnr_SetStdLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_2);
HI_VOID VPSS_Tnr_SetStdLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_1);
HI_VOID VPSS_Tnr_SetStdLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_0);
HI_VOID VPSS_Tnr_SetStdLut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_7);
HI_VOID VPSS_Tnr_SetStdLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_6);
HI_VOID VPSS_Tnr_SetStdLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_5);
HI_VOID VPSS_Tnr_SetStdLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_4);
HI_VOID VPSS_Tnr_SetStdLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_11);
HI_VOID VPSS_Tnr_SetStdLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_10);
HI_VOID VPSS_Tnr_SetStdLut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_9);
HI_VOID VPSS_Tnr_SetStdLut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_8);
HI_VOID VPSS_Tnr_SetStdLut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_15);
HI_VOID VPSS_Tnr_SetStdLut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_14);
HI_VOID VPSS_Tnr_SetStdLut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_13);
HI_VOID VPSS_Tnr_SetStdLut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 std_lut_12);
HI_VOID VPSS_Tnr_SetFigLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fig_lut_2);
HI_VOID VPSS_Tnr_SetFigLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fig_lut_1);
HI_VOID VPSS_Tnr_SetFigLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fig_lut_0);
HI_VOID VPSS_Tnr_SetFigLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fig_lut_5);
HI_VOID VPSS_Tnr_SetFigLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fig_lut_4);
HI_VOID VPSS_Tnr_SetFigLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 fig_lut_3);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

