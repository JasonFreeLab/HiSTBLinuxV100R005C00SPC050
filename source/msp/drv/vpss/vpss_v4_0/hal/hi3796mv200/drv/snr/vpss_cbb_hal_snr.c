//#include <linux/io.h>
//#include <linux/delay.h>

#include "vpss_cbb_common.h"
//#include "vpss_reg.h"


#if 1

HI_VOID VPSS_Snr_SetDbmOutMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbm_out_mode)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.dbm_out_mode = dbm_out_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMadMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 mad_mode)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.mad_mode = mad_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDetHyEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 det_hy_en)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.det_hy_en = det_hy_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbmDemoMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbm_demo_mode)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.dbm_demo_mode = dbm_demo_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbmDemoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbm_demo_en)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.dbm_demo_en = dbm_demo_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}

HI_VOID VPSS_Snr_SetDbLumHorEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_en)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.db_lum_hor_en = db_lum_hor_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetSnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 snr_en)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.snr_nr_en = snr_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_en)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.dm_en = dm_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_en)
{
    U_VPSS_SNR_CTRL VPSS_SNR_CTRL;

    VPSS_SNR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32));
    VPSS_SNR_CTRL.bits.db_en = db_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CTRL.u32), VPSS_SNR_CTRL.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbmDemoPosX(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbm_demo_pos_x)
{
    U_VPSS_DBM_DEMO VPSS_DBM_DEMO;

    VPSS_DBM_DEMO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBM_DEMO.u32));
    VPSS_DBM_DEMO.bits.dbm_demo_pos_x = dbm_demo_pos_x;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBM_DEMO.u32), VPSS_DBM_DEMO.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbCtrstThresh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_ctrst_thresh)
{
    U_VPSS_DB_DIR VPSS_DB_DIR;

    VPSS_DB_DIR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_DIR.u32));
    VPSS_DB_DIR.bits.db_ctrst_thresh = db_ctrst_thresh;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_DIR.u32), VPSS_DB_DIR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbGradSubRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_grad_sub_ratio)
{
    U_VPSS_DB_DIR VPSS_DB_DIR;

    VPSS_DB_DIR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_DIR.u32));
    VPSS_DB_DIR.bits.db_grad_sub_ratio = db_grad_sub_ratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_DIR.u32), VPSS_DB_DIR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHBlkSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_blk_size)
{
    U_VPSS_DB_BLK VPSS_DB_BLK;

    VPSS_DB_BLK.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BLK.u32));
    VPSS_DB_BLK.bits.db_lum_h_blk_size = db_lum_h_blk_size;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BLK.u32), VPSS_DB_BLK.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHorTxtWinSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_txt_win_size)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32));
    VPSS_DB_RATIO.bits.db_lum_hor_txt_win_size = db_lum_hor_txt_win_size;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32), VPSS_DB_RATIO.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbGlobalDbStrenthLum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_global_db_strenth_lum)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32));
    VPSS_DB_RATIO.bits.db_global_db_strenth_lum = db_global_db_strenth_lum;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32), VPSS_DB_RATIO.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorFilterSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_filter_sel)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32));
    VPSS_DB_RATIO.bits.db_lum_hor_filter_sel = db_lum_hor_filter_sel;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32), VPSS_DB_RATIO.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorScaleRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_scale_ratio)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32));
    VPSS_DB_RATIO.bits.db_lum_hor_scale_ratio = db_lum_hor_scale_ratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_RATIO.u32), VPSS_DB_RATIO.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHorHfVarGain2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_hf_var_gain2)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_var_gain2 = db_lum_hor_hf_var_gain2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorHfVarGain1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_hf_var_gain1)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_var_gain1 = db_lum_hor_hf_var_gain1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorHfVarCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_hf_var_core)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_var_core = db_lum_hor_hf_var_core;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorHfDiffGain2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_hf_diff_gain2)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_diff_gain2 = db_lum_hor_hf_diff_gain2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorHfDiffGain1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_hf_diff_gain1)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_diff_gain1 = db_lum_hor_hf_diff_gain1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorHfDiffCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_hf_diff_core)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_diff_core = db_lum_hor_hf_diff_core;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LHHF.u32), VPSS_DB_LHHF.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHorBordAdjGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_bord_adj_gain)
{
    U_VPSS_DB_LVHF VPSS_DB_LVHF;

    VPSS_DB_LVHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LVHF.u32));
    VPSS_DB_LVHF.bits.db_lum_hor_bord_adj_gain = db_lum_hor_bord_adj_gain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LVHF.u32), VPSS_DB_LVHF.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorAdjGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_adj_gain)
{
    U_VPSS_DB_LVHF VPSS_DB_LVHF;

    VPSS_DB_LVHF.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LVHF.u32));
    VPSS_DB_LVHF.bits.db_lum_hor_adj_gain = db_lum_hor_adj_gain;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LVHF.u32), VPSS_DB_LVHF.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbMaxLumHorDbDist(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_max_lum_hor_db_dist)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32));
    VPSS_DB_CTRS.bits.db_max_lum_hor_db_dist = db_max_lum_hor_db_dist;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbCtrstAdjGain2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_ctrst_adj_gain2)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32));
    VPSS_DB_CTRS.bits.db_ctrst_adj_gain2 = db_ctrst_adj_gain2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbCtrstAdjGain1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_ctrst_adj_gain1)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32));
    VPSS_DB_CTRS.bits.db_ctrst_adj_gain1 = db_ctrst_adj_gain1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirSmoothMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_smooth_mode)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32));
    VPSS_DB_CTRS.bits.db_dir_smooth_mode = db_dir_smooth_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbCtrstAdjCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_ctrst_adj_core)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32));
    VPSS_DB_CTRS.bits.db_ctrst_adj_core = db_ctrst_adj_core;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_CTRS.u32), VPSS_DB_CTRS.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p7)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p7 = db_lum_hor_delta_lut_p7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p6)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p6 = db_lum_hor_delta_lut_p6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p5)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p5 = db_lum_hor_delta_lut_p5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p4)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p4 = db_lum_hor_delta_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p3)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p3 = db_lum_hor_delta_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p2)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p2 = db_lum_hor_delta_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p1)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p1 = db_lum_hor_delta_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p0)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p0 = db_lum_hor_delta_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT0.u32), VPSS_DB_LUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p15)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p15 = db_lum_hor_delta_lut_p15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p14)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p14 = db_lum_hor_delta_lut_p14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p13)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p13 = db_lum_hor_delta_lut_p13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p12)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p12 = db_lum_hor_delta_lut_p12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p11)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p11 = db_lum_hor_delta_lut_p11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p10)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p10 = db_lum_hor_delta_lut_p10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p9)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p9 = db_lum_hor_delta_lut_p9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHorDeltaLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_hor_delta_lut_p8)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p8 = db_lum_hor_delta_lut_p8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT1.u32), VPSS_DB_LUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p9)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p9 = db_lum_h_str_fade_lut_p9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p8)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p8 = db_lum_h_str_fade_lut_p8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p7)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p7 = db_lum_h_str_fade_lut_p7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p6)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p6 = db_lum_h_str_fade_lut_p6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p5)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p5 = db_lum_h_str_fade_lut_p5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p4)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p4 = db_lum_h_str_fade_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p3)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p3 = db_lum_h_str_fade_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p2)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p2 = db_lum_h_str_fade_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p1)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p1 = db_lum_h_str_fade_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p0)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p0 = db_lum_h_str_fade_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT2.u32), VPSS_DB_LUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p11)
{
    U_VPSS_DB_LUT3 VPSS_DB_LUT3;

    VPSS_DB_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT3.u32));
    VPSS_DB_LUT3.bits.db_lum_h_str_fade_lut_p11 = db_lum_h_str_fade_lut_p11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT3.u32), VPSS_DB_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbLumHStrFadeLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_lum_h_str_fade_lut_p10)
{
    U_VPSS_DB_LUT3 VPSS_DB_LUT3;

    VPSS_DB_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT3.u32));
    VPSS_DB_LUT3.bits.db_lum_h_str_fade_lut_p10 = db_lum_h_str_fade_lut_p10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT3.u32), VPSS_DB_LUT3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbDirStrGainLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p7)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p7 = db_dir_str_gain_lut_p7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrGainLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p6)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p6 = db_dir_str_gain_lut_p6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrGainLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p5)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p5 = db_dir_str_gain_lut_p5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrGainLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p4)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p4 = db_dir_str_gain_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrGainLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p3)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p3 = db_dir_str_gain_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrGainLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p2)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p2 = db_dir_str_gain_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrGainLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p1)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p1 = db_dir_str_gain_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrGainLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_gain_lut_p0)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p0 = db_dir_str_gain_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT4.u32), VPSS_DB_LUT4.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbDirStrLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p7)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p7 = db_dir_str_lut_p7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p6)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p6 = db_dir_str_lut_p6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p5)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p5 = db_dir_str_lut_p5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p4)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p4 = db_dir_str_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p3)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p3 = db_dir_str_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p2)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p2 = db_dir_str_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p1)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p1 = db_dir_str_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p0)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p0 = db_dir_str_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT5.u32), VPSS_DB_LUT5.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbDirStrLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p15)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p15 = db_dir_str_lut_p15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p14)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p14 = db_dir_str_lut_p14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p13)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p13 = db_dir_str_lut_p13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p12)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p12 = db_dir_str_lut_p12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p11)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p11 = db_dir_str_lut_p11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p10)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p10 = db_dir_str_lut_p10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p9)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p9 = db_dir_str_lut_p9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbDirStrLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_dir_str_lut_p8)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p8 = db_dir_str_lut_p8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_LUT6.u32), VPSS_DB_LUT6.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbAdptDeltaScl(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_adpt_delta_scl)
{
    U_VPSS_DB_ADPT VPSS_DB_ADPT;

    VPSS_DB_ADPT.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_ADPT.u32));
    VPSS_DB_ADPT.bits.db_adpt_delta_scl = db_adpt_delta_scl;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_ADPT.u32), VPSS_DB_ADPT.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbAdptDeltaAdj0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_adpt_delta_adj0)
{
    U_VPSS_DB_ADPT VPSS_DB_ADPT;

    VPSS_DB_ADPT.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_ADPT.u32));
    VPSS_DB_ADPT.bits.db_adpt_delta_adj0 = db_adpt_delta_adj0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_ADPT.u32), VPSS_DB_ADPT.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbAdptFltMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 db_adpt_flt_mode)
{
    U_VPSS_DB_ADPT VPSS_DB_ADPT;

    VPSS_DB_ADPT.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_ADPT.u32));
    VPSS_DB_ADPT.bits.db_adpt_flt_mode = db_adpt_flt_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_ADPT.u32), VPSS_DB_ADPT.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyThdEdge(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_thd_edge)
{
    U_VPSS_DBD_THDEDGE VPSS_DBD_THDEDGE;

    VPSS_DBD_THDEDGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_THDEDGE.u32));
    VPSS_DBD_THDEDGE.bits.dbd_hy_thd_edge = dbd_hy_thd_edge;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_THDEDGE.u32), VPSS_DBD_THDEDGE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyThdTxt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_thd_txt)
{
    U_VPSS_DBD_THDTXT VPSS_DBD_THDTXT;

    VPSS_DBD_THDTXT.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_THDTXT.u32));
    VPSS_DBD_THDTXT.bits.dbd_hy_thd_txt = dbd_hy_thd_txt;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_THDTXT.u32), VPSS_DBD_THDTXT.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdDetLutWgt7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt7)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt7 = dbd_det_lut_wgt7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt6)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt6 = dbd_det_lut_wgt6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt5)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt5 = dbd_det_lut_wgt5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt4)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt4 = dbd_det_lut_wgt4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt3)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt3 = dbd_det_lut_wgt3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt2)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt2 = dbd_det_lut_wgt2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt1)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt1 = dbd_det_lut_wgt1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt0)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt0 = dbd_det_lut_wgt0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT0.u32), VPSS_DBD_LUTWGT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdDetLutWgt15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt15)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt15 = dbd_det_lut_wgt15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt14)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt14 = dbd_det_lut_wgt14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt13)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt13 = dbd_det_lut_wgt13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt12)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt12 = dbd_det_lut_wgt12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt11)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt11 = dbd_det_lut_wgt11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt10)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt10 = dbd_det_lut_wgt10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt9)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt9 = dbd_det_lut_wgt9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdDetLutWgt8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_det_lut_wgt8)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt8 = dbd_det_lut_wgt8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_LUTWGT1.u32), VPSS_DBD_LUTWGT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyRtnBdTxt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rtn_bd_txt)
{
    U_VPSS_DBD_RTNBDTXT VPSS_DBD_RTNBDTXT;

    VPSS_DBD_RTNBDTXT.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_RTNBDTXT.u32));
    VPSS_DBD_RTNBDTXT.bits.dbd_hy_rtn_bd_txt = dbd_hy_rtn_bd_txt;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_RTNBDTXT.u32), VPSS_DBD_RTNBDTXT.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyTstBlkNum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_tst_blk_num)
{
    U_VPSS_DBD_TSTBLKNUM VPSS_DBD_TSTBLKNUM;

    VPSS_DBD_TSTBLKNUM.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_TSTBLKNUM.u32));
    VPSS_DBD_TSTBLKNUM.bits.dbd_hy_tst_blk_num = dbd_hy_tst_blk_num;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_TSTBLKNUM.u32), VPSS_DBD_TSTBLKNUM.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyRdx8binLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rdx8bin_lut1)
{
    U_VPSS_DBD_HYRDX8BINLUT0 VPSS_DBD_HYRDX8BINLUT0;

    VPSS_DBD_HYRDX8BINLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32));
    VPSS_DBD_HYRDX8BINLUT0.bits.dbd_hy_rdx8bin_lut1 = dbd_hy_rdx8bin_lut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32), VPSS_DBD_HYRDX8BINLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdHyRdx8binLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rdx8bin_lut0)
{
    U_VPSS_DBD_HYRDX8BINLUT0 VPSS_DBD_HYRDX8BINLUT0;

    VPSS_DBD_HYRDX8BINLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32));
    VPSS_DBD_HYRDX8BINLUT0.bits.dbd_hy_rdx8bin_lut0 = dbd_hy_rdx8bin_lut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32), VPSS_DBD_HYRDX8BINLUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyRdx8binLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rdx8bin_lut3)
{
    U_VPSS_DBD_HYRDX8BINLUT1 VPSS_DBD_HYRDX8BINLUT1;

    VPSS_DBD_HYRDX8BINLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32));
    VPSS_DBD_HYRDX8BINLUT1.bits.dbd_hy_rdx8bin_lut3 = dbd_hy_rdx8bin_lut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32), VPSS_DBD_HYRDX8BINLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdHyRdx8binLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rdx8bin_lut2)
{
    U_VPSS_DBD_HYRDX8BINLUT1 VPSS_DBD_HYRDX8BINLUT1;

    VPSS_DBD_HYRDX8BINLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32));
    VPSS_DBD_HYRDX8BINLUT1.bits.dbd_hy_rdx8bin_lut2 = dbd_hy_rdx8bin_lut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32), VPSS_DBD_HYRDX8BINLUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyRdx8binLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rdx8bin_lut5)
{
    U_VPSS_DBD_HYRDX8BINLUT2 VPSS_DBD_HYRDX8BINLUT2;

    VPSS_DBD_HYRDX8BINLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32));
    VPSS_DBD_HYRDX8BINLUT2.bits.dbd_hy_rdx8bin_lut5 = dbd_hy_rdx8bin_lut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32), VPSS_DBD_HYRDX8BINLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdHyRdx8binLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rdx8bin_lut4)
{
    U_VPSS_DBD_HYRDX8BINLUT2 VPSS_DBD_HYRDX8BINLUT2;

    VPSS_DBD_HYRDX8BINLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32));
    VPSS_DBD_HYRDX8BINLUT2.bits.dbd_hy_rdx8bin_lut4 = dbd_hy_rdx8bin_lut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32), VPSS_DBD_HYRDX8BINLUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyRdx8binLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_rdx8bin_lut6)
{
    U_VPSS_DBD_HYRDX8BINLUT3 VPSS_DBD_HYRDX8BINLUT3;

    VPSS_DBD_HYRDX8BINLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT3.u32));
    VPSS_DBD_HYRDX8BINLUT3.bits.dbd_hy_rdx8bin_lut6 = dbd_hy_rdx8bin_lut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_HYRDX8BINLUT3.u32), VPSS_DBD_HYRDX8BINLUT3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdHyMaxBlkSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_hy_max_blk_size)
{
    U_VPSS_DBD_BLKSIZE VPSS_DBD_BLKSIZE;

    VPSS_DBD_BLKSIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_BLKSIZE.u32));
    VPSS_DBD_BLKSIZE.bits.dbd_hy_max_blk_size = dbd_hy_max_blk_size;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_BLKSIZE.u32), VPSS_DBD_BLKSIZE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDbdMinBlkSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_min_blk_size)
{
    U_VPSS_DBD_BLKSIZE VPSS_DBD_BLKSIZE;

    VPSS_DBD_BLKSIZE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_BLKSIZE.u32));
    VPSS_DBD_BLKSIZE.bits.dbd_min_blk_size = dbd_min_blk_size;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_BLKSIZE.u32), VPSS_DBD_BLKSIZE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDbdThrFlat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dbd_thr_flat)
{
    U_VPSS_DBD_FLAT VPSS_DBD_FLAT;

    VPSS_DBD_FLAT.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DBD_FLAT.u32));
    VPSS_DBD_FLAT.bits.dbd_thr_flat = dbd_thr_flat;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DBD_FLAT.u32), VPSS_DBD_FLAT.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmCtrstThresh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ctrst_thresh)
{
    U_VPSS_DM_DIR VPSS_DM_DIR;

    VPSS_DM_DIR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_DIR.u32));
    VPSS_DM_DIR.bits.dm_ctrst_thresh = dm_ctrst_thresh;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_DIR.u32), VPSS_DM_DIR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmGlobalStr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_global_str)
{
    U_VPSS_DM_EDGE VPSS_DM_EDGE;

    VPSS_DM_EDGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_EDGE.u32));
    VPSS_DM_EDGE.bits.dm_global_str = dm_global_str;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_EDGE.u32), VPSS_DM_EDGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmInitValStep(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_init_val_step)
{
    U_VPSS_DM_EDGE VPSS_DM_EDGE;

    VPSS_DM_EDGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_EDGE.u32));
    VPSS_DM_EDGE.bits.dm_init_val_step = dm_init_val_step;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_EDGE.u32), VPSS_DM_EDGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmMmfSet(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_mmf_set)
{
    U_VPSS_DM_EDGE VPSS_DM_EDGE;

    VPSS_DM_EDGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_EDGE.u32));
    VPSS_DM_EDGE.bits.dm_mmf_set = dm_mmf_set;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_EDGE.u32), VPSS_DM_EDGE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmSwWhtLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_sw_wht_lut_p3)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p3 = dm_sw_wht_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32), VPSS_DM_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmSwWhtLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_sw_wht_lut_p2)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p2 = dm_sw_wht_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32), VPSS_DM_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmSwWhtLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_sw_wht_lut_p1)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p1 = dm_sw_wht_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32), VPSS_DM_LUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmSwWhtLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_sw_wht_lut_p0)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p0 = dm_sw_wht_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT0.u32), VPSS_DM_LUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmLimitT10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_limit_t_10)
{
    U_VPSS_DM_LUT1 VPSS_DM_LUT1;

    VPSS_DM_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT1.u32));
    VPSS_DM_LUT1.bits.dm_limit_t_10 = dm_limit_t_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT1.u32), VPSS_DM_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmLimitT(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_limit_t)
{
    U_VPSS_DM_LUT1 VPSS_DM_LUT1;

    VPSS_DM_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT1.u32));
    VPSS_DM_LUT1.bits.dm_limit_t = dm_limit_t;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT1.u32), VPSS_DM_LUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmSwWhtLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_sw_wht_lut_p4)
{
    U_VPSS_DM_LUT1 VPSS_DM_LUT1;

    VPSS_DM_LUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT1.u32));
    VPSS_DM_LUT1.bits.dm_sw_wht_lut_p4 = dm_sw_wht_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT1.u32), VPSS_DM_LUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmDirStrGainLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p7)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p7 = dm_dir_str_gain_lut_p7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrGainLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p6)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p6 = dm_dir_str_gain_lut_p6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrGainLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p5)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p5 = dm_dir_str_gain_lut_p5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrGainLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p4)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p4 = dm_dir_str_gain_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrGainLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p3)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p3 = dm_dir_str_gain_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrGainLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p2)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p2 = dm_dir_str_gain_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrGainLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p1)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p1 = dm_dir_str_gain_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrGainLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_gain_lut_p0)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p0 = dm_dir_str_gain_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT2.u32), VPSS_DM_LUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmDirStrLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p7)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p7 = dm_dir_str_lut_p7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p6)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p6 = dm_dir_str_lut_p6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p5)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p5 = dm_dir_str_lut_p5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p4)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p4 = dm_dir_str_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p3)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p3 = dm_dir_str_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p2)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p2 = dm_dir_str_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p1)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p1 = dm_dir_str_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p0)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p0 = dm_dir_str_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT3.u32), VPSS_DM_LUT3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmDirStrLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p15)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p15 = dm_dir_str_lut_p15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p14)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p14 = dm_dir_str_lut_p14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p13)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p13 = dm_dir_str_lut_p13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p12)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p12 = dm_dir_str_lut_p12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p11)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p11 = dm_dir_str_lut_p11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p10)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p10 = dm_dir_str_lut_p10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p9)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p9 = dm_dir_str_lut_p9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p8)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p8 = dm_dir_str_lut_p8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT4.u32), VPSS_DM_LUT4.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmMmfLimitEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_mmf_limit_en)
{
    U_VPSS_DM_DIRC VPSS_DM_DIRC;

    VPSS_DM_DIRC.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_DIRC.u32));
    VPSS_DM_DIRC.bits.dm_mmf_limit_en = dm_mmf_limit_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_DIRC.u32), VPSS_DM_DIRC.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmCswTrsntSt10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_csw_trsnt_st_10)
{
    U_VPSS_DM_DIRO VPSS_DM_DIRO;

    VPSS_DM_DIRO.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_DIRO.u32));
    VPSS_DM_DIRO.bits.dm_csw_trsnt_st_10 = dm_csw_trsnt_st_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_DIRO.u32), VPSS_DM_DIRO.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmLswRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_lsw_ratio)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32));
    VPSS_DM_LSW.bits.dm_lsw_ratio = dm_lsw_ratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32), VPSS_DM_LSW.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmCswTrsntSt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_csw_trsnt_st)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32));
    VPSS_DM_LSW.bits.dm_csw_trsnt_st = dm_csw_trsnt_st;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32), VPSS_DM_LSW.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmLwCtrstT10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_lw_ctrst_t_10)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32));
    VPSS_DM_LSW.bits.dm_lw_ctrst_t_10 = dm_lw_ctrst_t_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32), VPSS_DM_LSW.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmLwCtrstT(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_lw_ctrst_t)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32));
    VPSS_DM_LSW.bits.dm_lw_ctrst_t = dm_lw_ctrst_t;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LSW.u32), VPSS_DM_LSW.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmCswTrsntLt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_csw_trsnt_lt)
{
    U_VPSS_DM_MMFLR VPSS_DM_MMFLR;

    VPSS_DM_MMFLR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFLR.u32));
    VPSS_DM_MMFLR.bits.dm_csw_trsnt_lt = dm_csw_trsnt_lt;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFLR.u32), VPSS_DM_MMFLR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmMmfLr10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_mmf_lr_10)
{
    U_VPSS_DM_MMFLR VPSS_DM_MMFLR;

    VPSS_DM_MMFLR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFLR.u32));
    VPSS_DM_MMFLR.bits.dm_mmf_lr_10 = dm_mmf_lr_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFLR.u32), VPSS_DM_MMFLR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmMmfLr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_mmf_lr)
{
    U_VPSS_DM_MMFLR VPSS_DM_MMFLR;

    VPSS_DM_MMFLR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFLR.u32));
    VPSS_DM_MMFLR.bits.dm_mmf_lr = dm_mmf_lr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFLR.u32), VPSS_DM_MMFLR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmCswTrsntLt10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_csw_trsnt_lt_10)
{
    U_VPSS_DM_MMFSR VPSS_DM_MMFSR;

    VPSS_DM_MMFSR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFSR.u32));
    VPSS_DM_MMFSR.bits.dm_csw_trsnt_lt_10 = dm_csw_trsnt_lt_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFSR.u32), VPSS_DM_MMFSR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmMmfSr10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_mmf_sr_10)
{
    U_VPSS_DM_MMFSR VPSS_DM_MMFSR;

    VPSS_DM_MMFSR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFSR.u32));
    VPSS_DM_MMFSR.bits.dm_mmf_sr_10 = dm_mmf_sr_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFSR.u32), VPSS_DM_MMFSR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmMmfSr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_mmf_sr)
{
    U_VPSS_DM_MMFSR VPSS_DM_MMFSR;

    VPSS_DM_MMFSR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFSR.u32));
    VPSS_DM_MMFSR.bits.dm_mmf_sr = dm_mmf_sr;


    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_MMFSR.u32), VPSS_DM_MMFSR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmDirBlendStr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_blend_str)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32));
    VPSS_DM_THR0.bits.dm_dir_blend_str = dm_dir_blend_str;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32), VPSS_DM_THR0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmLimResBlendStr2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_lim_res_blend_str2)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32));
    VPSS_DM_THR0.bits.dm_lim_res_blend_str2 = dm_lim_res_blend_str2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32), VPSS_DM_THR0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmLimResBlendStr1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_lim_res_blend_str1)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32));
    VPSS_DM_THR0.bits.dm_lim_res_blend_str1 = dm_lim_res_blend_str1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32), VPSS_DM_THR0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmLimitLswRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_limit_lsw_ratio)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32));
    VPSS_DM_THR0.bits.dm_limit_lsw_ratio = dm_limit_lsw_ratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_THR0.u32), VPSS_DM_THR0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransBandLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p4)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p4 = dm_trans_band_lut_p4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p3)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p3 = dm_trans_band_lut_p3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p2)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p2 = dm_trans_band_lut_p2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p1)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p1 = dm_trans_band_lut_p1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p0)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p0 = dm_trans_band_lut_p0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT5.u32), VPSS_DM_LUT5.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransBandLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p9)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p9 = dm_trans_band_lut_p9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p8)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p8 = dm_trans_band_lut_p8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p7)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p7 = dm_trans_band_lut_p7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p6)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p6 = dm_trans_band_lut_p6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p5)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p5 = dm_trans_band_lut_p5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT6.u32), VPSS_DM_LUT6.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransBandLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p14)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p14 = dm_trans_band_lut_p14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p13)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p13 = dm_trans_band_lut_p13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p12)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p12 = dm_trans_band_lut_p12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p11)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p11 = dm_trans_band_lut_p11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p10)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p10 = dm_trans_band_lut_p10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT7.u32), VPSS_DM_LUT7.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransBandLutP19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p19)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p19 = dm_trans_band_lut_p19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p18)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p18 = dm_trans_band_lut_p18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p17)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p17 = dm_trans_band_lut_p17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p16)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p16 = dm_trans_band_lut_p16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p15)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p15 = dm_trans_band_lut_p15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT8.u32), VPSS_DM_LUT8.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransBandLutP24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p24)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p24 = dm_trans_band_lut_p24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p23)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p23 = dm_trans_band_lut_p23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p22)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p22 = dm_trans_band_lut_p22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p21)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p21 = dm_trans_band_lut_p21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p20)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p20 = dm_trans_band_lut_p20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT9.u32), VPSS_DM_LUT9.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransBandLutP29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p29)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p29 = dm_trans_band_lut_p29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p28)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p28 = dm_trans_band_lut_p28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p27)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p27 = dm_trans_band_lut_p27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p26)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p26 = dm_trans_band_lut_p26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransBandLutP25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p25)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p25 = dm_trans_band_lut_p25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT10.u32), VPSS_DM_LUT10.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransBandLutP30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_band_lut_p30)
{
    U_VPSS_DM_LUT11 VPSS_DM_LUT11;

    VPSS_DM_LUT11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT11.u32));
    VPSS_DM_LUT11.bits.dm_trans_band_lut_p30 = dm_trans_band_lut_p30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT11.u32), VPSS_DM_LUT11.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmDirStrLutP20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p20)
{
    U_VPSS_DM_LUT12 VPSS_DM_LUT12;

    VPSS_DM_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32));
    VPSS_DM_LUT12.bits.dm_dir_str_lut_p20 = dm_dir_str_lut_p20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32), VPSS_DM_LUT12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p19)
{
    U_VPSS_DM_LUT12 VPSS_DM_LUT12;

    VPSS_DM_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32));
    VPSS_DM_LUT12.bits.dm_dir_str_lut_p19 = dm_dir_str_lut_p19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32), VPSS_DM_LUT12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p18)
{
    U_VPSS_DM_LUT12 VPSS_DM_LUT12;

    VPSS_DM_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32));
    VPSS_DM_LUT12.bits.dm_dir_str_lut_p18 = dm_dir_str_lut_p18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32), VPSS_DM_LUT12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p17)
{
    U_VPSS_DM_LUT12 VPSS_DM_LUT12;

    VPSS_DM_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32));
    VPSS_DM_LUT12.bits.dm_dir_str_lut_p17 = dm_dir_str_lut_p17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32), VPSS_DM_LUT12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmDirStrLutP16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_dir_str_lut_p16)
{
    U_VPSS_DM_LUT12 VPSS_DM_LUT12;

    VPSS_DM_LUT12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32));
    VPSS_DM_LUT12.bits.dm_dir_str_lut_p16 = dm_dir_str_lut_p16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT12.u32), VPSS_DM_LUT12.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp5)
{
    U_VPSS_DM_LUT13 VPSS_DM_LUT13;

    VPSS_DM_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32));
    VPSS_DM_LUT13.bits.dm_ang_ctrst_pun_lutp5 = dm_ang_ctrst_pun_lutp5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32), VPSS_DM_LUT13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp4)
{
    U_VPSS_DM_LUT13 VPSS_DM_LUT13;

    VPSS_DM_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32));
    VPSS_DM_LUT13.bits.dm_ang_ctrst_pun_lutp4 = dm_ang_ctrst_pun_lutp4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32), VPSS_DM_LUT13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp3)
{
    U_VPSS_DM_LUT13 VPSS_DM_LUT13;

    VPSS_DM_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32));
    VPSS_DM_LUT13.bits.dm_ang_ctrst_pun_lutp3 = dm_ang_ctrst_pun_lutp3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32), VPSS_DM_LUT13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp2)
{
    U_VPSS_DM_LUT13 VPSS_DM_LUT13;

    VPSS_DM_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32));
    VPSS_DM_LUT13.bits.dm_ang_ctrst_pun_lutp2 = dm_ang_ctrst_pun_lutp2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32), VPSS_DM_LUT13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp1)
{
    U_VPSS_DM_LUT13 VPSS_DM_LUT13;

    VPSS_DM_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32));
    VPSS_DM_LUT13.bits.dm_ang_ctrst_pun_lutp1 = dm_ang_ctrst_pun_lutp1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32), VPSS_DM_LUT13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp0)
{
    U_VPSS_DM_LUT13 VPSS_DM_LUT13;

    VPSS_DM_LUT13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32));
    VPSS_DM_LUT13.bits.dm_ang_ctrst_pun_lutp0 = dm_ang_ctrst_pun_lutp0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT13.u32), VPSS_DM_LUT13.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp11)
{
    U_VPSS_DM_LUT14 VPSS_DM_LUT14;

    VPSS_DM_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32));
    VPSS_DM_LUT14.bits.dm_ang_ctrst_pun_lutp11 = dm_ang_ctrst_pun_lutp11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32), VPSS_DM_LUT14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp10)
{
    U_VPSS_DM_LUT14 VPSS_DM_LUT14;

    VPSS_DM_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32));
    VPSS_DM_LUT14.bits.dm_ang_ctrst_pun_lutp10 = dm_ang_ctrst_pun_lutp10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32), VPSS_DM_LUT14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp9)
{
    U_VPSS_DM_LUT14 VPSS_DM_LUT14;

    VPSS_DM_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32));
    VPSS_DM_LUT14.bits.dm_ang_ctrst_pun_lutp9 = dm_ang_ctrst_pun_lutp9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32), VPSS_DM_LUT14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp8)
{
    U_VPSS_DM_LUT14 VPSS_DM_LUT14;

    VPSS_DM_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32));
    VPSS_DM_LUT14.bits.dm_ang_ctrst_pun_lutp8 = dm_ang_ctrst_pun_lutp8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32), VPSS_DM_LUT14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp7)
{
    U_VPSS_DM_LUT14 VPSS_DM_LUT14;

    VPSS_DM_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32));
    VPSS_DM_LUT14.bits.dm_ang_ctrst_pun_lutp7 = dm_ang_ctrst_pun_lutp7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32), VPSS_DM_LUT14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp6)
{
    U_VPSS_DM_LUT14 VPSS_DM_LUT14;

    VPSS_DM_LUT14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32));
    VPSS_DM_LUT14.bits.dm_ang_ctrst_pun_lutp6 = dm_ang_ctrst_pun_lutp6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT14.u32), VPSS_DM_LUT14.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp17)
{
    U_VPSS_DM_LUT15 VPSS_DM_LUT15;

    VPSS_DM_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32));
    VPSS_DM_LUT15.bits.dm_ang_ctrst_pun_lutp17 = dm_ang_ctrst_pun_lutp17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32), VPSS_DM_LUT15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp16)
{
    U_VPSS_DM_LUT15 VPSS_DM_LUT15;

    VPSS_DM_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32));
    VPSS_DM_LUT15.bits.dm_ang_ctrst_pun_lutp16 = dm_ang_ctrst_pun_lutp16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32), VPSS_DM_LUT15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp15)
{
    U_VPSS_DM_LUT15 VPSS_DM_LUT15;

    VPSS_DM_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32));
    VPSS_DM_LUT15.bits.dm_ang_ctrst_pun_lutp15 = dm_ang_ctrst_pun_lutp15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32), VPSS_DM_LUT15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp14)
{
    U_VPSS_DM_LUT15 VPSS_DM_LUT15;

    VPSS_DM_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32));
    VPSS_DM_LUT15.bits.dm_ang_ctrst_pun_lutp14 = dm_ang_ctrst_pun_lutp14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32), VPSS_DM_LUT15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp13)
{
    U_VPSS_DM_LUT15 VPSS_DM_LUT15;

    VPSS_DM_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32));
    VPSS_DM_LUT15.bits.dm_ang_ctrst_pun_lutp13 = dm_ang_ctrst_pun_lutp13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32), VPSS_DM_LUT15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp12)
{
    U_VPSS_DM_LUT15 VPSS_DM_LUT15;

    VPSS_DM_LUT15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32));
    VPSS_DM_LUT15.bits.dm_ang_ctrst_pun_lutp12 = dm_ang_ctrst_pun_lutp12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT15.u32), VPSS_DM_LUT15.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp23)
{
    U_VPSS_DM_LUT16 VPSS_DM_LUT16;

    VPSS_DM_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32));
    VPSS_DM_LUT16.bits.dm_ang_ctrst_pun_lutp23 = dm_ang_ctrst_pun_lutp23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32), VPSS_DM_LUT16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp22)
{
    U_VPSS_DM_LUT16 VPSS_DM_LUT16;

    VPSS_DM_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32));
    VPSS_DM_LUT16.bits.dm_ang_ctrst_pun_lutp22 = dm_ang_ctrst_pun_lutp22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32), VPSS_DM_LUT16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp21)
{
    U_VPSS_DM_LUT16 VPSS_DM_LUT16;

    VPSS_DM_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32));
    VPSS_DM_LUT16.bits.dm_ang_ctrst_pun_lutp21 = dm_ang_ctrst_pun_lutp21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32), VPSS_DM_LUT16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp20)
{
    U_VPSS_DM_LUT16 VPSS_DM_LUT16;

    VPSS_DM_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32));
    VPSS_DM_LUT16.bits.dm_ang_ctrst_pun_lutp20 = dm_ang_ctrst_pun_lutp20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32), VPSS_DM_LUT16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp19)
{
    U_VPSS_DM_LUT16 VPSS_DM_LUT16;

    VPSS_DM_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32));
    VPSS_DM_LUT16.bits.dm_ang_ctrst_pun_lutp19 = dm_ang_ctrst_pun_lutp19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32), VPSS_DM_LUT16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp18)
{
    U_VPSS_DM_LUT16 VPSS_DM_LUT16;

    VPSS_DM_LUT16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32));
    VPSS_DM_LUT16.bits.dm_ang_ctrst_pun_lutp18 = dm_ang_ctrst_pun_lutp18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT16.u32), VPSS_DM_LUT16.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp25)
{
    U_VPSS_DM_LUT17 VPSS_DM_LUT17;

    VPSS_DM_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT17.u32));
    VPSS_DM_LUT17.bits.dm_ang_ctrst_pun_lutp25 = dm_ang_ctrst_pun_lutp25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT17.u32), VPSS_DM_LUT17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmAngCtrstPunLutp24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_ang_ctrst_pun_lutp24)
{
    U_VPSS_DM_LUT17 VPSS_DM_LUT17;

    VPSS_DM_LUT17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT17.u32));
    VPSS_DM_LUT17.bits.dm_ang_ctrst_pun_lutp24 = dm_ang_ctrst_pun_lutp24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_LUT17.u32), VPSS_DM_LUT17.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDmTransWid10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_wid_10)
{
    U_VPSS_DM_TRANS_WID VPSS_DM_TRANS_WID;

    VPSS_DM_TRANS_WID.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_TRANS_WID.u32));
    VPSS_DM_TRANS_WID.bits.dm_trans_wid_10 = dm_trans_wid_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_TRANS_WID.u32), VPSS_DM_TRANS_WID.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmTransWid(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dm_trans_wid)
{
    U_VPSS_DM_TRANS_WID VPSS_DM_TRANS_WID;

    VPSS_DM_TRANS_WID.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_TRANS_WID.u32));
    VPSS_DM_TRANS_WID.bits.dm_trans_wid = dm_trans_wid;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_TRANS_WID.u32), VPSS_DM_TRANS_WID.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_0)
{
    U_VPSS_DB_BORD_FLAG0 VPSS_DB_BORD_FLAG0;

    VPSS_DB_BORD_FLAG0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG0.u32));
    VPSS_DB_BORD_FLAG0.bits.vpss_db_bord_flag_0 = vpss_db_bord_flag_0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG0.u32), VPSS_DB_BORD_FLAG0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_1)
{
    U_VPSS_DB_BORD_FLAG1 VPSS_DB_BORD_FLAG1;

    VPSS_DB_BORD_FLAG1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG1.u32));
    VPSS_DB_BORD_FLAG1.bits.vpss_db_bord_flag_1 = vpss_db_bord_flag_1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG1.u32), VPSS_DB_BORD_FLAG1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_2)
{
    U_VPSS_DB_BORD_FLAG2 VPSS_DB_BORD_FLAG2;

    VPSS_DB_BORD_FLAG2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG2.u32));
    VPSS_DB_BORD_FLAG2.bits.vpss_db_bord_flag_2 = vpss_db_bord_flag_2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG2.u32), VPSS_DB_BORD_FLAG2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_3)
{
    U_VPSS_DB_BORD_FLAG3 VPSS_DB_BORD_FLAG3;

    VPSS_DB_BORD_FLAG3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG3.u32));
    VPSS_DB_BORD_FLAG3.bits.vpss_db_bord_flag_3 = vpss_db_bord_flag_3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG3.u32), VPSS_DB_BORD_FLAG3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_4)
{
    U_VPSS_DB_BORD_FLAG4 VPSS_DB_BORD_FLAG4;

    VPSS_DB_BORD_FLAG4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG4.u32));
    VPSS_DB_BORD_FLAG4.bits.vpss_db_bord_flag_4 = vpss_db_bord_flag_4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG4.u32), VPSS_DB_BORD_FLAG4.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_5)
{
    U_VPSS_DB_BORD_FLAG5 VPSS_DB_BORD_FLAG5;

    VPSS_DB_BORD_FLAG5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG5.u32));
    VPSS_DB_BORD_FLAG5.bits.vpss_db_bord_flag_5 = vpss_db_bord_flag_5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG5.u32), VPSS_DB_BORD_FLAG5.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_6)
{
    U_VPSS_DB_BORD_FLAG6 VPSS_DB_BORD_FLAG6;

    VPSS_DB_BORD_FLAG6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG6.u32));
    VPSS_DB_BORD_FLAG6.bits.vpss_db_bord_flag_6 = vpss_db_bord_flag_6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG6.u32), VPSS_DB_BORD_FLAG6.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_7)
{
    U_VPSS_DB_BORD_FLAG7 VPSS_DB_BORD_FLAG7;

    VPSS_DB_BORD_FLAG7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG7.u32));
    VPSS_DB_BORD_FLAG7.bits.vpss_db_bord_flag_7 = vpss_db_bord_flag_7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG7.u32), VPSS_DB_BORD_FLAG7.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_8)
{
    U_VPSS_DB_BORD_FLAG8 VPSS_DB_BORD_FLAG8;

    VPSS_DB_BORD_FLAG8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG8.u32));
    VPSS_DB_BORD_FLAG8.bits.vpss_db_bord_flag_8 = vpss_db_bord_flag_8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG8.u32), VPSS_DB_BORD_FLAG8.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_9)
{
    U_VPSS_DB_BORD_FLAG9 VPSS_DB_BORD_FLAG9;

    VPSS_DB_BORD_FLAG9.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG9.u32));
    VPSS_DB_BORD_FLAG9.bits.vpss_db_bord_flag_9 = vpss_db_bord_flag_9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG9.u32), VPSS_DB_BORD_FLAG9.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_10)
{
    U_VPSS_DB_BORD_FLAG10 VPSS_DB_BORD_FLAG10;

    VPSS_DB_BORD_FLAG10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG10.u32));
    VPSS_DB_BORD_FLAG10.bits.vpss_db_bord_flag_10 = vpss_db_bord_flag_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG10.u32), VPSS_DB_BORD_FLAG10.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_11)
{
    U_VPSS_DB_BORD_FLAG11 VPSS_DB_BORD_FLAG11;

    VPSS_DB_BORD_FLAG11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG11.u32));
    VPSS_DB_BORD_FLAG11.bits.vpss_db_bord_flag_11 = vpss_db_bord_flag_11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG11.u32), VPSS_DB_BORD_FLAG11.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_12)
{
    U_VPSS_DB_BORD_FLAG12 VPSS_DB_BORD_FLAG12;

    VPSS_DB_BORD_FLAG12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG12.u32));
    VPSS_DB_BORD_FLAG12.bits.vpss_db_bord_flag_12 = vpss_db_bord_flag_12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG12.u32), VPSS_DB_BORD_FLAG12.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_13)
{
    U_VPSS_DB_BORD_FLAG13 VPSS_DB_BORD_FLAG13;

    VPSS_DB_BORD_FLAG13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG13.u32));
    VPSS_DB_BORD_FLAG13.bits.vpss_db_bord_flag_13 = vpss_db_bord_flag_13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG13.u32), VPSS_DB_BORD_FLAG13.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_14)
{
    U_VPSS_DB_BORD_FLAG14 VPSS_DB_BORD_FLAG14;

    VPSS_DB_BORD_FLAG14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG14.u32));
    VPSS_DB_BORD_FLAG14.bits.vpss_db_bord_flag_14 = vpss_db_bord_flag_14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG14.u32), VPSS_DB_BORD_FLAG14.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_15)
{
    U_VPSS_DB_BORD_FLAG15 VPSS_DB_BORD_FLAG15;

    VPSS_DB_BORD_FLAG15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG15.u32));
    VPSS_DB_BORD_FLAG15.bits.vpss_db_bord_flag_15 = vpss_db_bord_flag_15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG15.u32), VPSS_DB_BORD_FLAG15.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_16)
{
    U_VPSS_DB_BORD_FLAG16 VPSS_DB_BORD_FLAG16;

    VPSS_DB_BORD_FLAG16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG16.u32));
    VPSS_DB_BORD_FLAG16.bits.vpss_db_bord_flag_16 = vpss_db_bord_flag_16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG16.u32), VPSS_DB_BORD_FLAG16.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_17)
{
    U_VPSS_DB_BORD_FLAG17 VPSS_DB_BORD_FLAG17;

    VPSS_DB_BORD_FLAG17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG17.u32));
    VPSS_DB_BORD_FLAG17.bits.vpss_db_bord_flag_17 = vpss_db_bord_flag_17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG17.u32), VPSS_DB_BORD_FLAG17.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_18)
{
    U_VPSS_DB_BORD_FLAG18 VPSS_DB_BORD_FLAG18;

    VPSS_DB_BORD_FLAG18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG18.u32));
    VPSS_DB_BORD_FLAG18.bits.vpss_db_bord_flag_18 = vpss_db_bord_flag_18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG18.u32), VPSS_DB_BORD_FLAG18.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_19)
{
    U_VPSS_DB_BORD_FLAG19 VPSS_DB_BORD_FLAG19;

    VPSS_DB_BORD_FLAG19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG19.u32));
    VPSS_DB_BORD_FLAG19.bits.vpss_db_bord_flag_19 = vpss_db_bord_flag_19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG19.u32), VPSS_DB_BORD_FLAG19.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_20)
{
    U_VPSS_DB_BORD_FLAG20 VPSS_DB_BORD_FLAG20;

    VPSS_DB_BORD_FLAG20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG20.u32));
    VPSS_DB_BORD_FLAG20.bits.vpss_db_bord_flag_20 = vpss_db_bord_flag_20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG20.u32), VPSS_DB_BORD_FLAG20.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_21)
{
    U_VPSS_DB_BORD_FLAG21 VPSS_DB_BORD_FLAG21;

    VPSS_DB_BORD_FLAG21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG21.u32));
    VPSS_DB_BORD_FLAG21.bits.vpss_db_bord_flag_21 = vpss_db_bord_flag_21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG21.u32), VPSS_DB_BORD_FLAG21.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_22)
{
    U_VPSS_DB_BORD_FLAG22 VPSS_DB_BORD_FLAG22;

    VPSS_DB_BORD_FLAG22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG22.u32));
    VPSS_DB_BORD_FLAG22.bits.vpss_db_bord_flag_22 = vpss_db_bord_flag_22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG22.u32), VPSS_DB_BORD_FLAG22.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_23)
{
    U_VPSS_DB_BORD_FLAG23 VPSS_DB_BORD_FLAG23;

    VPSS_DB_BORD_FLAG23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG23.u32));
    VPSS_DB_BORD_FLAG23.bits.vpss_db_bord_flag_23 = vpss_db_bord_flag_23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG23.u32), VPSS_DB_BORD_FLAG23.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_24)
{
    U_VPSS_DB_BORD_FLAG24 VPSS_DB_BORD_FLAG24;

    VPSS_DB_BORD_FLAG24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG24.u32));
    VPSS_DB_BORD_FLAG24.bits.vpss_db_bord_flag_24 = vpss_db_bord_flag_24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG24.u32), VPSS_DB_BORD_FLAG24.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_25)
{
    U_VPSS_DB_BORD_FLAG25 VPSS_DB_BORD_FLAG25;

    VPSS_DB_BORD_FLAG25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG25.u32));
    VPSS_DB_BORD_FLAG25.bits.vpss_db_bord_flag_25 = vpss_db_bord_flag_25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG25.u32), VPSS_DB_BORD_FLAG25.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_26)
{
    U_VPSS_DB_BORD_FLAG26 VPSS_DB_BORD_FLAG26;

    VPSS_DB_BORD_FLAG26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG26.u32));
    VPSS_DB_BORD_FLAG26.bits.vpss_db_bord_flag_26 = vpss_db_bord_flag_26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG26.u32), VPSS_DB_BORD_FLAG26.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_27)
{
    U_VPSS_DB_BORD_FLAG27 VPSS_DB_BORD_FLAG27;

    VPSS_DB_BORD_FLAG27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG27.u32));
    VPSS_DB_BORD_FLAG27.bits.vpss_db_bord_flag_27 = vpss_db_bord_flag_27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG27.u32), VPSS_DB_BORD_FLAG27.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_28)
{
    U_VPSS_DB_BORD_FLAG28 VPSS_DB_BORD_FLAG28;

    VPSS_DB_BORD_FLAG28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG28.u32));
    VPSS_DB_BORD_FLAG28.bits.vpss_db_bord_flag_28 = vpss_db_bord_flag_28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG28.u32), VPSS_DB_BORD_FLAG28.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_29)
{
    U_VPSS_DB_BORD_FLAG29 VPSS_DB_BORD_FLAG29;

    VPSS_DB_BORD_FLAG29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG29.u32));
    VPSS_DB_BORD_FLAG29.bits.vpss_db_bord_flag_29 = vpss_db_bord_flag_29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG29.u32), VPSS_DB_BORD_FLAG29.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_30)
{
    U_VPSS_DB_BORD_FLAG30 VPSS_DB_BORD_FLAG30;

    VPSS_DB_BORD_FLAG30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG30.u32));
    VPSS_DB_BORD_FLAG30.bits.vpss_db_bord_flag_30 = vpss_db_bord_flag_30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG30.u32), VPSS_DB_BORD_FLAG30.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_31)
{
    U_VPSS_DB_BORD_FLAG31 VPSS_DB_BORD_FLAG31;

    VPSS_DB_BORD_FLAG31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG31.u32));
    VPSS_DB_BORD_FLAG31.bits.vpss_db_bord_flag_31 = vpss_db_bord_flag_31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG31.u32), VPSS_DB_BORD_FLAG31.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_32)
{
    U_VPSS_DB_BORD_FLAG32 VPSS_DB_BORD_FLAG32;

    VPSS_DB_BORD_FLAG32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG32.u32));
    VPSS_DB_BORD_FLAG32.bits.vpss_db_bord_flag_32 = vpss_db_bord_flag_32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG32.u32), VPSS_DB_BORD_FLAG32.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_33)
{
    U_VPSS_DB_BORD_FLAG33 VPSS_DB_BORD_FLAG33;

    VPSS_DB_BORD_FLAG33.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG33.u32));
    VPSS_DB_BORD_FLAG33.bits.vpss_db_bord_flag_33 = vpss_db_bord_flag_33;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG33.u32), VPSS_DB_BORD_FLAG33.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_34)
{
    U_VPSS_DB_BORD_FLAG34 VPSS_DB_BORD_FLAG34;

    VPSS_DB_BORD_FLAG34.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG34.u32));
    VPSS_DB_BORD_FLAG34.bits.vpss_db_bord_flag_34 = vpss_db_bord_flag_34;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG34.u32), VPSS_DB_BORD_FLAG34.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_35)
{
    U_VPSS_DB_BORD_FLAG35 VPSS_DB_BORD_FLAG35;

    VPSS_DB_BORD_FLAG35.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG35.u32));
    VPSS_DB_BORD_FLAG35.bits.vpss_db_bord_flag_35 = vpss_db_bord_flag_35;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG35.u32), VPSS_DB_BORD_FLAG35.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_36)
{
    U_VPSS_DB_BORD_FLAG36 VPSS_DB_BORD_FLAG36;

    VPSS_DB_BORD_FLAG36.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG36.u32));
    VPSS_DB_BORD_FLAG36.bits.vpss_db_bord_flag_36 = vpss_db_bord_flag_36;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG36.u32), VPSS_DB_BORD_FLAG36.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_37)
{
    U_VPSS_DB_BORD_FLAG37 VPSS_DB_BORD_FLAG37;

    VPSS_DB_BORD_FLAG37.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG37.u32));
    VPSS_DB_BORD_FLAG37.bits.vpss_db_bord_flag_37 = vpss_db_bord_flag_37;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG37.u32), VPSS_DB_BORD_FLAG37.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_38)
{
    U_VPSS_DB_BORD_FLAG38 VPSS_DB_BORD_FLAG38;

    VPSS_DB_BORD_FLAG38.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG38.u32));
    VPSS_DB_BORD_FLAG38.bits.vpss_db_bord_flag_38 = vpss_db_bord_flag_38;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG38.u32), VPSS_DB_BORD_FLAG38.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_39)
{
    U_VPSS_DB_BORD_FLAG39 VPSS_DB_BORD_FLAG39;

    VPSS_DB_BORD_FLAG39.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG39.u32));
    VPSS_DB_BORD_FLAG39.bits.vpss_db_bord_flag_39 = vpss_db_bord_flag_39;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG39.u32), VPSS_DB_BORD_FLAG39.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_40)
{
    U_VPSS_DB_BORD_FLAG40 VPSS_DB_BORD_FLAG40;

    VPSS_DB_BORD_FLAG40.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG40.u32));
    VPSS_DB_BORD_FLAG40.bits.vpss_db_bord_flag_40 = vpss_db_bord_flag_40;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG40.u32), VPSS_DB_BORD_FLAG40.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_41)
{
    U_VPSS_DB_BORD_FLAG41 VPSS_DB_BORD_FLAG41;

    VPSS_DB_BORD_FLAG41.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG41.u32));
    VPSS_DB_BORD_FLAG41.bits.vpss_db_bord_flag_41 = vpss_db_bord_flag_41;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG41.u32), VPSS_DB_BORD_FLAG41.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_42)
{
    U_VPSS_DB_BORD_FLAG42 VPSS_DB_BORD_FLAG42;

    VPSS_DB_BORD_FLAG42.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG42.u32));
    VPSS_DB_BORD_FLAG42.bits.vpss_db_bord_flag_42 = vpss_db_bord_flag_42;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG42.u32), VPSS_DB_BORD_FLAG42.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_43)
{
    U_VPSS_DB_BORD_FLAG43 VPSS_DB_BORD_FLAG43;

    VPSS_DB_BORD_FLAG43.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG43.u32));
    VPSS_DB_BORD_FLAG43.bits.vpss_db_bord_flag_43 = vpss_db_bord_flag_43;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG43.u32), VPSS_DB_BORD_FLAG43.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_44)
{
    U_VPSS_DB_BORD_FLAG44 VPSS_DB_BORD_FLAG44;

    VPSS_DB_BORD_FLAG44.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG44.u32));
    VPSS_DB_BORD_FLAG44.bits.vpss_db_bord_flag_44 = vpss_db_bord_flag_44;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG44.u32), VPSS_DB_BORD_FLAG44.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_45)
{
    U_VPSS_DB_BORD_FLAG45 VPSS_DB_BORD_FLAG45;

    VPSS_DB_BORD_FLAG45.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG45.u32));
    VPSS_DB_BORD_FLAG45.bits.vpss_db_bord_flag_45 = vpss_db_bord_flag_45;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG45.u32), VPSS_DB_BORD_FLAG45.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_46)
{
    U_VPSS_DB_BORD_FLAG46 VPSS_DB_BORD_FLAG46;

    VPSS_DB_BORD_FLAG46.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG46.u32));
    VPSS_DB_BORD_FLAG46.bits.vpss_db_bord_flag_46 = vpss_db_bord_flag_46;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG46.u32), VPSS_DB_BORD_FLAG46.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_47)
{
    U_VPSS_DB_BORD_FLAG47 VPSS_DB_BORD_FLAG47;

    VPSS_DB_BORD_FLAG47.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG47.u32));
    VPSS_DB_BORD_FLAG47.bits.vpss_db_bord_flag_47 = vpss_db_bord_flag_47;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG47.u32), VPSS_DB_BORD_FLAG47.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_48)
{
    U_VPSS_DB_BORD_FLAG48 VPSS_DB_BORD_FLAG48;

    VPSS_DB_BORD_FLAG48.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG48.u32));
    VPSS_DB_BORD_FLAG48.bits.vpss_db_bord_flag_48 = vpss_db_bord_flag_48;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG48.u32), VPSS_DB_BORD_FLAG48.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag49(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_49)
{
    U_VPSS_DB_BORD_FLAG49 VPSS_DB_BORD_FLAG49;

    VPSS_DB_BORD_FLAG49.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG49.u32));
    VPSS_DB_BORD_FLAG49.bits.vpss_db_bord_flag_49 = vpss_db_bord_flag_49;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG49.u32), VPSS_DB_BORD_FLAG49.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_50)
{
    U_VPSS_DB_BORD_FLAG50 VPSS_DB_BORD_FLAG50;

    VPSS_DB_BORD_FLAG50.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG50.u32));
    VPSS_DB_BORD_FLAG50.bits.vpss_db_bord_flag_50 = vpss_db_bord_flag_50;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG50.u32), VPSS_DB_BORD_FLAG50.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_51)
{
    U_VPSS_DB_BORD_FLAG51 VPSS_DB_BORD_FLAG51;

    VPSS_DB_BORD_FLAG51.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG51.u32));
    VPSS_DB_BORD_FLAG51.bits.vpss_db_bord_flag_51 = vpss_db_bord_flag_51;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG51.u32), VPSS_DB_BORD_FLAG51.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_52)
{
    U_VPSS_DB_BORD_FLAG52 VPSS_DB_BORD_FLAG52;

    VPSS_DB_BORD_FLAG52.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG52.u32));
    VPSS_DB_BORD_FLAG52.bits.vpss_db_bord_flag_52 = vpss_db_bord_flag_52;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG52.u32), VPSS_DB_BORD_FLAG52.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_53)
{
    U_VPSS_DB_BORD_FLAG53 VPSS_DB_BORD_FLAG53;

    VPSS_DB_BORD_FLAG53.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG53.u32));
    VPSS_DB_BORD_FLAG53.bits.vpss_db_bord_flag_53 = vpss_db_bord_flag_53;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG53.u32), VPSS_DB_BORD_FLAG53.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_54)
{
    U_VPSS_DB_BORD_FLAG54 VPSS_DB_BORD_FLAG54;

    VPSS_DB_BORD_FLAG54.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG54.u32));
    VPSS_DB_BORD_FLAG54.bits.vpss_db_bord_flag_54 = vpss_db_bord_flag_54;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG54.u32), VPSS_DB_BORD_FLAG54.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_55)
{
    U_VPSS_DB_BORD_FLAG55 VPSS_DB_BORD_FLAG55;

    VPSS_DB_BORD_FLAG55.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG55.u32));
    VPSS_DB_BORD_FLAG55.bits.vpss_db_bord_flag_55 = vpss_db_bord_flag_55;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG55.u32), VPSS_DB_BORD_FLAG55.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_56)
{
    U_VPSS_DB_BORD_FLAG56 VPSS_DB_BORD_FLAG56;

    VPSS_DB_BORD_FLAG56.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG56.u32));
    VPSS_DB_BORD_FLAG56.bits.vpss_db_bord_flag_56 = vpss_db_bord_flag_56;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG56.u32), VPSS_DB_BORD_FLAG56.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_57)
{
    U_VPSS_DB_BORD_FLAG57 VPSS_DB_BORD_FLAG57;

    VPSS_DB_BORD_FLAG57.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG57.u32));
    VPSS_DB_BORD_FLAG57.bits.vpss_db_bord_flag_57 = vpss_db_bord_flag_57;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG57.u32), VPSS_DB_BORD_FLAG57.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_58)
{
    U_VPSS_DB_BORD_FLAG58 VPSS_DB_BORD_FLAG58;

    VPSS_DB_BORD_FLAG58.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG58.u32));
    VPSS_DB_BORD_FLAG58.bits.vpss_db_bord_flag_58 = vpss_db_bord_flag_58;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG58.u32), VPSS_DB_BORD_FLAG58.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag59(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_59)
{
    U_VPSS_DB_BORD_FLAG59 VPSS_DB_BORD_FLAG59;

    VPSS_DB_BORD_FLAG59.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG59.u32));
    VPSS_DB_BORD_FLAG59.bits.vpss_db_bord_flag_59 = vpss_db_bord_flag_59;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG59.u32), VPSS_DB_BORD_FLAG59.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag60(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_60)
{
    U_VPSS_DB_BORD_FLAG60 VPSS_DB_BORD_FLAG60;

    VPSS_DB_BORD_FLAG60.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG60.u32));
    VPSS_DB_BORD_FLAG60.bits.vpss_db_bord_flag_60 = vpss_db_bord_flag_60;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG60.u32), VPSS_DB_BORD_FLAG60.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag61(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_61)
{
    U_VPSS_DB_BORD_FLAG61 VPSS_DB_BORD_FLAG61;

    VPSS_DB_BORD_FLAG61.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG61.u32));
    VPSS_DB_BORD_FLAG61.bits.vpss_db_bord_flag_61 = vpss_db_bord_flag_61;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG61.u32), VPSS_DB_BORD_FLAG61.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag62(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_62)
{
    U_VPSS_DB_BORD_FLAG62 VPSS_DB_BORD_FLAG62;

    VPSS_DB_BORD_FLAG62.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG62.u32));
    VPSS_DB_BORD_FLAG62.bits.vpss_db_bord_flag_62 = vpss_db_bord_flag_62;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG62.u32), VPSS_DB_BORD_FLAG62.u32);

    return ;
}



HI_VOID VPSS_Snr_SetVpssDbBordFlag63(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 vpss_db_bord_flag_63)
{
    U_VPSS_DB_BORD_FLAG63 VPSS_DB_BORD_FLAG63;

    VPSS_DB_BORD_FLAG63.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG63.u32));
    VPSS_DB_BORD_FLAG63.bits.vpss_db_bord_flag_63 = vpss_db_bord_flag_63;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DB_BORD_FLAG63.u32), VPSS_DB_BORD_FLAG63.u32);

    return ;
}



HI_VOID VPSS_Snr_SetTestEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 test_en)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32));
    VPSS_SNR_ENABLE.bits.test_en = test_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgeprefilteren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgeprefilteren)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32));
    VPSS_SNR_ENABLE.bits.edgeprefilteren = edgeprefilteren;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetColorweighten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 colorweighten)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32));
    VPSS_SNR_ENABLE.bits.colorweighten = colorweighten;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionedgeweighten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motionedgeweighten)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32));
    VPSS_SNR_ENABLE.bits.motionedgeweighten = motionedgeweighten;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCnr2den(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cnr2den)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32));
    VPSS_SNR_ENABLE.bits.cnr2den = cnr2den;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetYnr2den(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ynr2den)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32));
    VPSS_SNR_ENABLE.bits.ynr2den = ynr2den;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_ENABLE.u32), VPSS_SNR_ENABLE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgeoriratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgeoriratio)
{
    U_VPSS_SNR_EDGE_RATIORANGE VPSS_SNR_EDGE_RATIORANGE;

    VPSS_SNR_EDGE_RATIORANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32));
    VPSS_SNR_EDGE_RATIORANGE.bits.edgeoriratio = edgeoriratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32), VPSS_SNR_EDGE_RATIORANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgeminratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgeminratio)
{
    U_VPSS_SNR_EDGE_RATIORANGE VPSS_SNR_EDGE_RATIORANGE;

    VPSS_SNR_EDGE_RATIORANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32));
    VPSS_SNR_EDGE_RATIORANGE.bits.edgeminratio = edgeminratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32), VPSS_SNR_EDGE_RATIORANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemaxratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemaxratio)
{
    U_VPSS_SNR_EDGE_RATIORANGE VPSS_SNR_EDGE_RATIORANGE;

    VPSS_SNR_EDGE_RATIORANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32));
    VPSS_SNR_EDGE_RATIORANGE.bits.edgemaxratio = edgemaxratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32), VPSS_SNR_EDGE_RATIORANGE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgeoristrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgeoristrength)
{
    U_VPSS_SNR_EDGE_STRRANGE VPSS_SNR_EDGE_STRRANGE;

    VPSS_SNR_EDGE_STRRANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32));
    VPSS_SNR_EDGE_STRRANGE.bits.edgeoristrength = edgeoristrength;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32), VPSS_SNR_EDGE_STRRANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgeminstrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgeminstrength)
{
    U_VPSS_SNR_EDGE_STRRANGE VPSS_SNR_EDGE_STRRANGE;

    VPSS_SNR_EDGE_STRRANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32));
    VPSS_SNR_EDGE_STRRANGE.bits.edgeminstrength = edgeminstrength;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32), VPSS_SNR_EDGE_STRRANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemaxstrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemaxstrength)
{
    U_VPSS_SNR_EDGE_STRRANGE VPSS_SNR_EDGE_STRRANGE;

    VPSS_SNR_EDGE_STRRANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32));
    VPSS_SNR_EDGE_STRRANGE.bits.edgemaxstrength = edgemaxstrength;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32), VPSS_SNR_EDGE_STRRANGE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgestrth3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgestrth3)
{
    U_VPSS_SNR_EDGE_STRTH VPSS_SNR_EDGE_STRTH;

    VPSS_SNR_EDGE_STRTH.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32));
    VPSS_SNR_EDGE_STRTH.bits.edgestrth3 = edgestrth3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32), VPSS_SNR_EDGE_STRTH.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgestrth2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgestrth2)
{
    U_VPSS_SNR_EDGE_STRTH VPSS_SNR_EDGE_STRTH;

    VPSS_SNR_EDGE_STRTH.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32));
    VPSS_SNR_EDGE_STRTH.bits.edgestrth2 = edgestrth2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32), VPSS_SNR_EDGE_STRTH.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgestrth1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgestrth1)
{
    U_VPSS_SNR_EDGE_STRTH VPSS_SNR_EDGE_STRTH;

    VPSS_SNR_EDGE_STRTH.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32));
    VPSS_SNR_EDGE_STRTH.bits.edgestrth1 = edgestrth1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32), VPSS_SNR_EDGE_STRTH.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgestrk3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgestrk3)
{
    U_VPSS_SNR_EDGE_STRK VPSS_SNR_EDGE_STRK;

    VPSS_SNR_EDGE_STRK.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRK.u32));
    VPSS_SNR_EDGE_STRK.bits.edgestrk3 = edgestrk3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRK.u32), VPSS_SNR_EDGE_STRK.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgestrk2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgestrk2)
{
    U_VPSS_SNR_EDGE_STRK VPSS_SNR_EDGE_STRK;

    VPSS_SNR_EDGE_STRK.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRK.u32));
    VPSS_SNR_EDGE_STRK.bits.edgestrk2 = edgestrk2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRK.u32), VPSS_SNR_EDGE_STRK.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgestrk1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgestrk1)
{
    U_VPSS_SNR_EDGE_STRK VPSS_SNR_EDGE_STRK;

    VPSS_SNR_EDGE_STRK.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRK.u32));
    VPSS_SNR_EDGE_STRK.bits.edgestrk1 = edgestrk1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STRK.u32), VPSS_SNR_EDGE_STRK.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgemeanth3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth3)
{
    U_VPSS_SNR_EDGE_MEANTH1 VPSS_SNR_EDGE_MEANTH1;

    VPSS_SNR_EDGE_MEANTH1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32));
    VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth3 = edgemeanth3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32), VPSS_SNR_EDGE_MEANTH1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeanth2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth2)
{
    U_VPSS_SNR_EDGE_MEANTH1 VPSS_SNR_EDGE_MEANTH1;

    VPSS_SNR_EDGE_MEANTH1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32));
    VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth2 = edgemeanth2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32), VPSS_SNR_EDGE_MEANTH1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeanth1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth1)
{
    U_VPSS_SNR_EDGE_MEANTH1 VPSS_SNR_EDGE_MEANTH1;

    VPSS_SNR_EDGE_MEANTH1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32));
    VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth1 = edgemeanth1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32), VPSS_SNR_EDGE_MEANTH1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgemeanth6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth6)
{
    U_VPSS_SNR_EDGE_MEANTH2 VPSS_SNR_EDGE_MEANTH2;

    VPSS_SNR_EDGE_MEANTH2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32));
    VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth6 = edgemeanth6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32), VPSS_SNR_EDGE_MEANTH2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeanth5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth5)
{
    U_VPSS_SNR_EDGE_MEANTH2 VPSS_SNR_EDGE_MEANTH2;

    VPSS_SNR_EDGE_MEANTH2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32));
    VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth5 = edgemeanth5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32), VPSS_SNR_EDGE_MEANTH2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeanth4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth4)
{
    U_VPSS_SNR_EDGE_MEANTH2 VPSS_SNR_EDGE_MEANTH2;

    VPSS_SNR_EDGE_MEANTH2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32));
    VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth4 = edgemeanth4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32), VPSS_SNR_EDGE_MEANTH2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgemeanth8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth8)
{
    U_VPSS_SNR_EDGE_MEANTH3 VPSS_SNR_EDGE_MEANTH3;

    VPSS_SNR_EDGE_MEANTH3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32));
    VPSS_SNR_EDGE_MEANTH3.bits.edgemeanth8 = edgemeanth8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32), VPSS_SNR_EDGE_MEANTH3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeanth7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeanth7)
{
    U_VPSS_SNR_EDGE_MEANTH3 VPSS_SNR_EDGE_MEANTH3;

    VPSS_SNR_EDGE_MEANTH3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32));
    VPSS_SNR_EDGE_MEANTH3.bits.edgemeanth7 = edgemeanth7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32), VPSS_SNR_EDGE_MEANTH3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgemeank4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank4)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank4 = edgemeank4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeank3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank3)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank3 = edgemeank3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeank2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank2)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank2 = edgemeank2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeank1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank1)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank1 = edgemeank1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdgemeank8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank8)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank8 = edgemeank8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeank7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank7)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank7 = edgemeank7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeank6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank6)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank6 = edgemeank6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdgemeank5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edgemeank5)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank5 = edgemeank5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetC2dwinheight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 c2dwinheight)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32));
    VPSS_SNR_WIN.bits.c2dwinheight = c2dwinheight;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32), VPSS_SNR_WIN.u32);

    return ;
}


HI_VOID VPSS_Snr_SetC2dwinwidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 c2dwinwidth)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32));
    VPSS_SNR_WIN.bits.c2dwinwidth = c2dwinwidth;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32), VPSS_SNR_WIN.u32);

    return ;
}


HI_VOID VPSS_Snr_SetY2dwinheight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 y2dwinheight)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32));
    VPSS_SNR_WIN.bits.y2dwinheight = y2dwinheight;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32), VPSS_SNR_WIN.u32);

    return ;
}


HI_VOID VPSS_Snr_SetY2dwinwidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 y2dwinwidth)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32));
    VPSS_SNR_WIN.bits.y2dwinwidth = y2dwinwidth;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_WIN.u32), VPSS_SNR_WIN.u32);

    return ;
}



HI_VOID VPSS_Snr_SetCsnrstr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 csnrstr)
{
    U_VPSS_SNR_STR VPSS_SNR_STR;

    VPSS_SNR_STR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR.u32));
    VPSS_SNR_STR.bits.csnrstr = csnrstr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR.u32), VPSS_SNR_STR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetYsnrstr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ysnrstr)
{
    U_VPSS_SNR_STR VPSS_SNR_STR;

    VPSS_SNR_STR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR.u32));
    VPSS_SNR_STR.bits.ysnrstr = ysnrstr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR.u32), VPSS_SNR_STR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetStroffset3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 stroffset3)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32));
    VPSS_SNR_STR_OFFSET.bits.stroffset3 = stroffset3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32), VPSS_SNR_STR_OFFSET.u32);

    return ;
}


HI_VOID VPSS_Snr_SetStroffset2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 stroffset2)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32));
    VPSS_SNR_STR_OFFSET.bits.stroffset2 = stroffset2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32), VPSS_SNR_STR_OFFSET.u32);

    return ;
}


HI_VOID VPSS_Snr_SetStroffset1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 stroffset1)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32));
    VPSS_SNR_STR_OFFSET.bits.stroffset1 = stroffset1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32), VPSS_SNR_STR_OFFSET.u32);

    return ;
}


HI_VOID VPSS_Snr_SetStroffset0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 stroffset0)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32));
    VPSS_SNR_STR_OFFSET.bits.stroffset0 = stroffset0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_OFFSET.u32), VPSS_SNR_STR_OFFSET.u32);

    return ;
}



HI_VOID VPSS_Snr_SetCstradjust(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cstradjust)
{
    U_VPSS_SNR_STR_ADJUST VPSS_SNR_STR_ADJUST;

    VPSS_SNR_STR_ADJUST.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_ADJUST.u32));
    VPSS_SNR_STR_ADJUST.bits.cstradjust = cstradjust;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_ADJUST.u32), VPSS_SNR_STR_ADJUST.u32);

    return ;
}


HI_VOID VPSS_Snr_SetYstradjust(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ystradjust)
{
    U_VPSS_SNR_STR_ADJUST VPSS_SNR_STR_ADJUST;

    VPSS_SNR_STR_ADJUST.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_ADJUST.u32));
    VPSS_SNR_STR_ADJUST.bits.ystradjust = ystradjust;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_STR_ADJUST.u32), VPSS_SNR_STR_ADJUST.u32);

    return ;
}



HI_VOID VPSS_Snr_SetScenechangeth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechangeth)
{
    U_VPSS_SNR_SCHANGE_TH VPSS_SNR_SCHANGE_TH;

    VPSS_SNR_SCHANGE_TH.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE_TH.u32));
    VPSS_SNR_SCHANGE_TH.bits.scenechangeth = scenechangeth;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE_TH.u32), VPSS_SNR_SCHANGE_TH.u32);

    return ;
}



HI_VOID VPSS_Snr_SetRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio3)
{
    U_VPSS_SNR_EDGE_RATIO_1 VPSS_SNR_EDGE_RATIO_1;

    VPSS_SNR_EDGE_RATIO_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32));
    VPSS_SNR_EDGE_RATIO_1.bits.ratio3 = ratio3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32), VPSS_SNR_EDGE_RATIO_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio2)
{
    U_VPSS_SNR_EDGE_RATIO_1 VPSS_SNR_EDGE_RATIO_1;

    VPSS_SNR_EDGE_RATIO_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32));
    VPSS_SNR_EDGE_RATIO_1.bits.ratio2 = ratio2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32), VPSS_SNR_EDGE_RATIO_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio1)
{
    U_VPSS_SNR_EDGE_RATIO_1 VPSS_SNR_EDGE_RATIO_1;

    VPSS_SNR_EDGE_RATIO_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32));
    VPSS_SNR_EDGE_RATIO_1.bits.ratio1 = ratio1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32), VPSS_SNR_EDGE_RATIO_1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetRatio6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio6)
{
    U_VPSS_SNR_EDGE_RATIO_2 VPSS_SNR_EDGE_RATIO_2;

    VPSS_SNR_EDGE_RATIO_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32));
    VPSS_SNR_EDGE_RATIO_2.bits.ratio6 = ratio6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32), VPSS_SNR_EDGE_RATIO_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetRatio5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio5)
{
    U_VPSS_SNR_EDGE_RATIO_2 VPSS_SNR_EDGE_RATIO_2;

    VPSS_SNR_EDGE_RATIO_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32));
    VPSS_SNR_EDGE_RATIO_2.bits.ratio5 = ratio5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32), VPSS_SNR_EDGE_RATIO_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio4)
{
    U_VPSS_SNR_EDGE_RATIO_2 VPSS_SNR_EDGE_RATIO_2;

    VPSS_SNR_EDGE_RATIO_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32));
    VPSS_SNR_EDGE_RATIO_2.bits.ratio4 = ratio4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32), VPSS_SNR_EDGE_RATIO_2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetRatio8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio8)
{
    U_VPSS_SNR_EDGE_RATIO_3 VPSS_SNR_EDGE_RATIO_3;

    VPSS_SNR_EDGE_RATIO_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32));
    VPSS_SNR_EDGE_RATIO_3.bits.ratio8 = ratio8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32), VPSS_SNR_EDGE_RATIO_3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetRatio7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 ratio7)
{
    U_VPSS_SNR_EDGE_RATIO_3 VPSS_SNR_EDGE_RATIO_3;

    VPSS_SNR_EDGE_RATIO_3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32));
    VPSS_SNR_EDGE_RATIO_3.bits.ratio7 = ratio7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32), VPSS_SNR_EDGE_RATIO_3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetEdge3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge3)
{
    U_VPSS_SNR_EDGE_STR VPSS_SNR_EDGE_STR;

    VPSS_SNR_EDGE_STR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STR.u32));
    VPSS_SNR_EDGE_STR.bits.edge3 = edge3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STR.u32), VPSS_SNR_EDGE_STR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdge2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge2)
{
    U_VPSS_SNR_EDGE_STR VPSS_SNR_EDGE_STR;

    VPSS_SNR_EDGE_STR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STR.u32));
    VPSS_SNR_EDGE_STR.bits.edge2 = edge2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STR.u32), VPSS_SNR_EDGE_STR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEdge1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 edge1)
{
    U_VPSS_SNR_EDGE_STR VPSS_SNR_EDGE_STR;

    VPSS_SNR_EDGE_STR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STR.u32));
    VPSS_SNR_EDGE_STR.bits.edge1 = edge1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_EDGE_STR.u32), VPSS_SNR_EDGE_STR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetTestColorCr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 test_color_cr)
{
    U_VPSS_SNR_TEST_COLOR VPSS_SNR_TEST_COLOR;

    VPSS_SNR_TEST_COLOR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_TEST_COLOR.u32));
    VPSS_SNR_TEST_COLOR.bits.test_color_cr = test_color_cr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_TEST_COLOR.u32), VPSS_SNR_TEST_COLOR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetTestColorCb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 test_color_cb)
{
    U_VPSS_SNR_TEST_COLOR VPSS_SNR_TEST_COLOR;

    VPSS_SNR_TEST_COLOR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_TEST_COLOR.u32));
    VPSS_SNR_TEST_COLOR.bits.test_color_cb = test_color_cb;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_TEST_COLOR.u32), VPSS_SNR_TEST_COLOR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetScenechangeMode2En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechange_mode2_en)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32));
    VPSS_SNR_SCHANGE.bits.scenechange_mode2_en = scenechange_mode2_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetScenechangeBldcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechange_bldcore)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32));
    VPSS_SNR_SCHANGE.bits.scenechange_bldcore = scenechange_bldcore;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetScenechangeBldk(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechange_bldk)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32));
    VPSS_SNR_SCHANGE.bits.scenechange_bldk = scenechange_bldk;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetScenechangeMode1En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechange_mode1_en)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32));
    VPSS_SNR_SCHANGE.bits.scenechange_mode1_en = scenechange_mode1_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetScenechangeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechange_en)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32));
    VPSS_SNR_SCHANGE.bits.scenechange_en = scenechange_en;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetScenechangeInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 scenechange_info)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32));
    VPSS_SNR_SCHANGE.bits.scenechange_info = scenechange_info;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_SCHANGE.u32), VPSS_SNR_SCHANGE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionalpha(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motionalpha)
{
    U_VPSS_SNR_MT VPSS_SNR_MT;

    VPSS_SNR_MT.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_MT.u32));
    VPSS_SNR_MT.bits.motionalpha = motionalpha;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_MT.u32), VPSS_SNR_MT.u32);

    return ;
}



HI_VOID VPSS_Snr_SetCbcrWeight1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbcr_weight1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32));
    VPSS_SNR_CBCR_W1.bits.cbcr_weight1 = cbcr_weight1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCrEnd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cr_end1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32));
    VPSS_SNR_CBCR_W1.bits.cr_end1 = cr_end1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCbEnd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cb_end1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32));
    VPSS_SNR_CBCR_W1.bits.cb_end1 = cb_end1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCrBegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cr_begin1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32));
    VPSS_SNR_CBCR_W1.bits.cr_begin1 = cr_begin1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCbBegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cb_begin1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32));
    VPSS_SNR_CBCR_W1.bits.cb_begin1 = cb_begin1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W1.u32), VPSS_SNR_CBCR_W1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetCbcrWeight2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cbcr_weight2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32));
    VPSS_SNR_CBCR_W2.bits.cbcr_weight2 = cbcr_weight2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCrEnd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cr_end2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32));
    VPSS_SNR_CBCR_W2.bits.cr_end2 = cr_end2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCbEnd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cb_end2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32));
    VPSS_SNR_CBCR_W2.bits.cb_end2 = cb_end2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCrBegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cr_begin2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32));
    VPSS_SNR_CBCR_W2.bits.cr_begin2 = cr_begin2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetCbBegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 cb_begin2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32));
    VPSS_SNR_CBCR_W2.bits.cb_begin2 = cb_begin2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_SNR_CBCR_W2.u32), VPSS_SNR_CBCR_W2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut07(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut07)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut07 = motion_edge_lut07;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut06(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut06)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut06 = motion_edge_lut06;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut05(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut05)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut05 = motion_edge_lut05;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut04(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut04)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut04 = motion_edge_lut04;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut03(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut03)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut03 = motion_edge_lut03;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut02)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut02 = motion_edge_lut02;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut01)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut01 = motion_edge_lut01;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut00)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut00 = motion_edge_lut00;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_01.u32), MOTION_EDGE_LUT_01.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut0f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut0f)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0f = motion_edge_lut0f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut0e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut0e)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0e = motion_edge_lut0e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut0d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut0d)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0d = motion_edge_lut0d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut0c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut0c)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0c = motion_edge_lut0c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut0b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut0b)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0b = motion_edge_lut0b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut0a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut0a)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0a = motion_edge_lut0a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut09(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut09)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut09 = motion_edge_lut09;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut08(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut08)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut08 = motion_edge_lut08;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_02.u32), MOTION_EDGE_LUT_02.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut17)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut17 = motion_edge_lut17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut16)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut16 = motion_edge_lut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut15)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut15 = motion_edge_lut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut14)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut14 = motion_edge_lut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut13)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut13 = motion_edge_lut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut12)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut12 = motion_edge_lut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut11)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut11 = motion_edge_lut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut10)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut10 = motion_edge_lut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_03.u32), MOTION_EDGE_LUT_03.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut1f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut1f)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1f = motion_edge_lut1f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut1e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut1e)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1e = motion_edge_lut1e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut1d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut1d)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1d = motion_edge_lut1d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut1c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut1c)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1c = motion_edge_lut1c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut1b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut1b)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1b = motion_edge_lut1b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut1a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut1a)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1a = motion_edge_lut1a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut19)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut19 = motion_edge_lut19;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut18)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut18 = motion_edge_lut18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_04.u32), MOTION_EDGE_LUT_04.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut27)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut27 = motion_edge_lut27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut26)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut26 = motion_edge_lut26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut25)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut25 = motion_edge_lut25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut24)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut24 = motion_edge_lut24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut23)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut23 = motion_edge_lut23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut22)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut22 = motion_edge_lut22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut21)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut21 = motion_edge_lut21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut20)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut20 = motion_edge_lut20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_05.u32), MOTION_EDGE_LUT_05.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut2f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut2f)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2f = motion_edge_lut2f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut2e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut2e)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2e = motion_edge_lut2e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut2d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut2d)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2d = motion_edge_lut2d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut2c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut2c)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2c = motion_edge_lut2c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut2b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut2b)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2b = motion_edge_lut2b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut2a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut2a)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2a = motion_edge_lut2a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut29)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut29 = motion_edge_lut29;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut28)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut28 = motion_edge_lut28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_06.u32), MOTION_EDGE_LUT_06.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut37)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut37 = motion_edge_lut37;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut36)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut36 = motion_edge_lut36;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut35)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut35 = motion_edge_lut35;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut34)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut34 = motion_edge_lut34;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut33)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut33 = motion_edge_lut33;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut32)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut32 = motion_edge_lut32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut31)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut31 = motion_edge_lut31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut30)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut30 = motion_edge_lut30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_07.u32), MOTION_EDGE_LUT_07.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut3f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut3f)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3f = motion_edge_lut3f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut3e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut3e)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3e = motion_edge_lut3e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut3d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut3d)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3d = motion_edge_lut3d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut3c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut3c)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3c = motion_edge_lut3c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut3b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut3b)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3b = motion_edge_lut3b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut3a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut3a)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3a = motion_edge_lut3a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut39)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut39 = motion_edge_lut39;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut38)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut38 = motion_edge_lut38;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_08.u32), MOTION_EDGE_LUT_08.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut47)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut47 = motion_edge_lut47;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut46)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut46 = motion_edge_lut46;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut45)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut45 = motion_edge_lut45;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut44)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut44 = motion_edge_lut44;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut43)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut43 = motion_edge_lut43;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut42)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut42 = motion_edge_lut42;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut41)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut41 = motion_edge_lut41;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut40)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut40 = motion_edge_lut40;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_09.u32), MOTION_EDGE_LUT_09.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut4f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut4f)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4f = motion_edge_lut4f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut4e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut4e)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4e = motion_edge_lut4e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut4d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut4d)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4d = motion_edge_lut4d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut4c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut4c)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4c = motion_edge_lut4c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut4b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut4b)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4b = motion_edge_lut4b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut4a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut4a)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4a = motion_edge_lut4a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut49(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut49)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut49 = motion_edge_lut49;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut48)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut48 = motion_edge_lut48;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_10.u32), MOTION_EDGE_LUT_10.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut57)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut57 = motion_edge_lut57;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut56)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut56 = motion_edge_lut56;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut55)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut55 = motion_edge_lut55;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut54)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut54 = motion_edge_lut54;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut53)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut53 = motion_edge_lut53;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut52)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut52 = motion_edge_lut52;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut51)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut51 = motion_edge_lut51;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut50)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut50 = motion_edge_lut50;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_11.u32), MOTION_EDGE_LUT_11.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut5f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut5f)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5f = motion_edge_lut5f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut5e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut5e)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5e = motion_edge_lut5e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut5d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut5d)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5d = motion_edge_lut5d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut5c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut5c)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5c = motion_edge_lut5c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut5b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut5b)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5b = motion_edge_lut5b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut5a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut5a)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5a = motion_edge_lut5a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut59(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut59)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut59 = motion_edge_lut59;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut58)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut58 = motion_edge_lut58;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_12.u32), MOTION_EDGE_LUT_12.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut67(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut67)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut67 = motion_edge_lut67;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut66(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut66)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut66 = motion_edge_lut66;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut65(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut65)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut65 = motion_edge_lut65;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut64(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut64)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut64 = motion_edge_lut64;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut63(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut63)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut63 = motion_edge_lut63;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut62(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut62)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut62 = motion_edge_lut62;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut61(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut61)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut61 = motion_edge_lut61;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut60(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut60)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut60 = motion_edge_lut60;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_13.u32), MOTION_EDGE_LUT_13.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut6f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut6f)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6f = motion_edge_lut6f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut6e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut6e)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6e = motion_edge_lut6e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut6d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut6d)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6d = motion_edge_lut6d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut6c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut6c)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6c = motion_edge_lut6c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut6b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut6b)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6b = motion_edge_lut6b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut6a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut6a)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6a = motion_edge_lut6a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut69(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut69)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut69 = motion_edge_lut69;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut68(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut68)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut68 = motion_edge_lut68;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_14.u32), MOTION_EDGE_LUT_14.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut77(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut77)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut77 = motion_edge_lut77;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut76(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut76)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut76 = motion_edge_lut76;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut75(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut75)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut75 = motion_edge_lut75;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut74(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut74)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut74 = motion_edge_lut74;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut73(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut73)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut73 = motion_edge_lut73;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut72(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut72)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut72 = motion_edge_lut72;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut71(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut71)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut71 = motion_edge_lut71;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut70(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut70)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut70 = motion_edge_lut70;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_15.u32), MOTION_EDGE_LUT_15.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut7f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut7f)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7f = motion_edge_lut7f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut7e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut7e)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7e = motion_edge_lut7e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut7d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut7d)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7d = motion_edge_lut7d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut7c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut7c)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7c = motion_edge_lut7c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut7b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut7b)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7b = motion_edge_lut7b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut7a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut7a)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7a = motion_edge_lut7a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut79(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut79)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut79 = motion_edge_lut79;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut78(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut78)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut78 = motion_edge_lut78;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_16.u32), MOTION_EDGE_LUT_16.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut87(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut87)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut87 = motion_edge_lut87;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut86(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut86)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut86 = motion_edge_lut86;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut85(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut85)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut85 = motion_edge_lut85;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut84(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut84)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut84 = motion_edge_lut84;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut83(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut83)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut83 = motion_edge_lut83;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut82(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut82)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut82 = motion_edge_lut82;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut81(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut81)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut81 = motion_edge_lut81;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut80(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut80)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut80 = motion_edge_lut80;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_17.u32), MOTION_EDGE_LUT_17.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut8f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut8f)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8f = motion_edge_lut8f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut8e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut8e)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8e = motion_edge_lut8e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut8d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut8d)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8d = motion_edge_lut8d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut8c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut8c)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8c = motion_edge_lut8c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut8b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut8b)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8b = motion_edge_lut8b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut8a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut8a)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8a = motion_edge_lut8a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut89(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut89)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut89 = motion_edge_lut89;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut88(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut88)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut88 = motion_edge_lut88;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_18.u32), MOTION_EDGE_LUT_18.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut97(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut97)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut97 = motion_edge_lut97;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut96(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut96)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut96 = motion_edge_lut96;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut95(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut95)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut95 = motion_edge_lut95;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut94(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut94)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut94 = motion_edge_lut94;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut93(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut93)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut93 = motion_edge_lut93;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut92(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut92)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut92 = motion_edge_lut92;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut91(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut91)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut91 = motion_edge_lut91;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut90(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut90)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut90 = motion_edge_lut90;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_19.u32), MOTION_EDGE_LUT_19.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLut9f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut9f)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9f = motion_edge_lut9f;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut9e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut9e)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9e = motion_edge_lut9e;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut9d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut9d)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9d = motion_edge_lut9d;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut9c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut9c)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9c = motion_edge_lut9c;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut9b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut9b)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9b = motion_edge_lut9b;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut9a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut9a)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9a = motion_edge_lut9a;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut99(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut99)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut99 = motion_edge_lut99;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLut98(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lut98)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut98 = motion_edge_lut98;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_20.u32), MOTION_EDGE_LUT_20.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLuta7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta7)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta7 = motion_edge_luta7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta6)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta6 = motion_edge_luta6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta5)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta5 = motion_edge_luta5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta4)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta4 = motion_edge_luta4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta3)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta3 = motion_edge_luta3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta2)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta2 = motion_edge_luta2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta1)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta1 = motion_edge_luta1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta0)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta0 = motion_edge_luta0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_21.u32), MOTION_EDGE_LUT_21.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutaf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutaf)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutaf = motion_edge_lutaf;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutae(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutae)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutae = motion_edge_lutae;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutad)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutad = motion_edge_lutad;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutac(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutac)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutac = motion_edge_lutac;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutab(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutab)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutab = motion_edge_lutab;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutaa(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutaa)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutaa = motion_edge_lutaa;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta9)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_luta9 = motion_edge_luta9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuta8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luta8)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32));
    MOTION_EDGE_LUT_22.bits.motion_edge_luta8 = motion_edge_luta8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_22.u32), MOTION_EDGE_LUT_22.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutb7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb7)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb7 = motion_edge_lutb7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb6)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb6 = motion_edge_lutb6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb5)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb5 = motion_edge_lutb5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb4)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb4 = motion_edge_lutb4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb3)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb3 = motion_edge_lutb3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb2)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb2 = motion_edge_lutb2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb1)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb1 = motion_edge_lutb1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb0)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb0 = motion_edge_lutb0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_23.u32), MOTION_EDGE_LUT_23.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutbf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutbf)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbf = motion_edge_lutbf;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutbe(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutbe)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbe = motion_edge_lutbe;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutbd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutbd)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbd = motion_edge_lutbd;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutbc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutbc)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbc = motion_edge_lutbc;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutbb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutbb)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbb = motion_edge_lutbb;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutba(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutba)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutba = motion_edge_lutba;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb9)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutb9 = motion_edge_lutb9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutb8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutb8)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutb8 = motion_edge_lutb8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_24.u32), MOTION_EDGE_LUT_24.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutc7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc7)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc7 = motion_edge_lutc7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc6)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc6 = motion_edge_lutc6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc5)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc5 = motion_edge_lutc5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc4)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc4 = motion_edge_lutc4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc3)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc3 = motion_edge_lutc3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc2)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc2 = motion_edge_lutc2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc1)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc1 = motion_edge_lutc1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc0)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc0 = motion_edge_lutc0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_25.u32), MOTION_EDGE_LUT_25.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutcf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutcf)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcf = motion_edge_lutcf;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutce(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutce)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutce = motion_edge_lutce;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutcd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutcd)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcd = motion_edge_lutcd;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutcc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutcc)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcc = motion_edge_lutcc;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutcb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutcb)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcb = motion_edge_lutcb;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutca(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutca)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutca = motion_edge_lutca;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc9)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutc9 = motion_edge_lutc9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutc8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutc8)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutc8 = motion_edge_lutc8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_26.u32), MOTION_EDGE_LUT_26.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutd7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd7)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd7 = motion_edge_lutd7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd6)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd6 = motion_edge_lutd6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd5)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd5 = motion_edge_lutd5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd4)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd4 = motion_edge_lutd4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd3)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd3 = motion_edge_lutd3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd2)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd2 = motion_edge_lutd2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd1)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd1 = motion_edge_lutd1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd0)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd0 = motion_edge_lutd0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_27.u32), MOTION_EDGE_LUT_27.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutdf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutdf)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdf = motion_edge_lutdf;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutde(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutde)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutde = motion_edge_lutde;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutdd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutdd)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdd = motion_edge_lutdd;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutdc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutdc)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdc = motion_edge_lutdc;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutdb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutdb)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdb = motion_edge_lutdb;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutda(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutda)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutda = motion_edge_lutda;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd9)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutd9 = motion_edge_lutd9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutd8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutd8)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutd8 = motion_edge_lutd8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_28.u32), MOTION_EDGE_LUT_28.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLute7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute7)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute7 = motion_edge_lute7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute6)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute6 = motion_edge_lute6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute5)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute5 = motion_edge_lute5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute4)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute4 = motion_edge_lute4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute3)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute3 = motion_edge_lute3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute2)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute2 = motion_edge_lute2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute1)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute1 = motion_edge_lute1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute0)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute0 = motion_edge_lute0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_29.u32), MOTION_EDGE_LUT_29.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutef(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutef)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutef = motion_edge_lutef;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutee(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutee)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutee = motion_edge_lutee;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuted(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luted)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_luted = motion_edge_luted;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutec(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutec)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutec = motion_edge_lutec;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLuteb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_luteb)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_luteb = motion_edge_luteb;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutea(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutea)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutea = motion_edge_lutea;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute9)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_lute9 = motion_edge_lute9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLute8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lute8)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32));
    MOTION_EDGE_LUT_30.bits.motion_edge_lute8 = motion_edge_lute8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_30.u32), MOTION_EDGE_LUT_30.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutf7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf7)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf7 = motion_edge_lutf7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf6)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf6 = motion_edge_lutf6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf5)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf5 = motion_edge_lutf5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf4)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf4 = motion_edge_lutf4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf3)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf3 = motion_edge_lutf3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf2)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf2 = motion_edge_lutf2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf1)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf1 = motion_edge_lutf1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf0)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf0 = motion_edge_lutf0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_31.u32), MOTION_EDGE_LUT_31.u32);

    return ;
}



HI_VOID VPSS_Snr_SetMotionEdgeLutff(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutff)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutff = motion_edge_lutff;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutfe(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutfe)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfe = motion_edge_lutfe;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutfd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutfd)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfd = motion_edge_lutfd;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutfc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutfc)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfc = motion_edge_lutfc;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutfb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutfb)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfb = motion_edge_lutfb;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutfa(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutfa)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfa = motion_edge_lutfa;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf9)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutf9 = motion_edge_lutf9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Snr_SetMotionEdgeLutf8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 motion_edge_lutf8)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutf8 = motion_edge_lutf8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->MOTION_EDGE_LUT_32.u32), MOTION_EDGE_LUT_32.u32);

    return ;
}

HI_VOID VPSS_Snr_SetClipmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 clipmode)
{
    U_VPSS_DM_DR_CTRL VPSS_DM_DR_CTRL;

    VPSS_DM_DR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32));
    VPSS_DM_DR_CTRL.bits.clipmode = clipmode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32), VPSS_DM_DR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEnangadjstbylm(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 enangadjstbylm)
{
    U_VPSS_DM_DR_CTRL VPSS_DM_DR_CTRL;

    VPSS_DM_DR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32));
    VPSS_DM_DR_CTRL.bits.enangadjstbylm = enangadjstbylm;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32), VPSS_DM_DR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEnstradjstbylm(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 enstradjstbylm)
{
    U_VPSS_DM_DR_CTRL VPSS_DM_DR_CTRL;

    VPSS_DM_DR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32));
    VPSS_DM_DR_CTRL.bits.enstradjstbylm = enstradjstbylm;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32), VPSS_DM_DR_CTRL.u32);

    return ;
}


HI_VOID VPSS_Snr_SetEnep(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 enep)
{
    U_VPSS_DM_DR_CTRL VPSS_DM_DR_CTRL;

    VPSS_DM_DR_CTRL.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32));
    VPSS_DM_DR_CTRL.bits.enep = enep;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DM_DR_CTRL.u32), VPSS_DM_DR_CTRL.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLradjpixrange10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lradjpixrange_10)
{
    U_VPSS_DR_THR VPSS_DR_THR;

    VPSS_DR_THR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32));
    VPSS_DR_THR.bits.lradjpixrange_10 = lradjpixrange_10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32), VPSS_DR_THR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLradjpixrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lradjpixrange)
{
    U_VPSS_DR_THR VPSS_DR_THR;

    VPSS_DR_THR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32));
    VPSS_DR_THR.bits.lradjpixrange = lradjpixrange;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32), VPSS_DR_THR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetRegdrstrenth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 regdrstrenth)
{
    U_VPSS_DR_THR VPSS_DR_THR;

    VPSS_DR_THR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32));
    VPSS_DR_THR.bits.regdrstrenth = regdrstrenth;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32), VPSS_DR_THR.u32);

    return ;
}


HI_VOID VPSS_Snr_SetRegthrmdfangctrst(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 regthrmdfangctrst)
{
    U_VPSS_DR_THR VPSS_DR_THR;

    VPSS_DR_THR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32));
    VPSS_DR_THR.bits.regthrmdfangctrst = regthrmdfangctrst;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DR_THR.u32), VPSS_DR_THR.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut50)
{
    U_VPSS_DRLSWSTRLUT0 VPSS_DRLSWSTRLUT0;

    VPSS_DRLSWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32));
    VPSS_DRLSWSTRLUT0.bits.lswstrlut50 = lswstrlut50;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32), VPSS_DRLSWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut40)
{
    U_VPSS_DRLSWSTRLUT0 VPSS_DRLSWSTRLUT0;

    VPSS_DRLSWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32));
    VPSS_DRLSWSTRLUT0.bits.lswstrlut40 = lswstrlut40;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32), VPSS_DRLSWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut30)
{
    U_VPSS_DRLSWSTRLUT0 VPSS_DRLSWSTRLUT0;

    VPSS_DRLSWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32));
    VPSS_DRLSWSTRLUT0.bits.lswstrlut30 = lswstrlut30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32), VPSS_DRLSWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut20)
{
    U_VPSS_DRLSWSTRLUT0 VPSS_DRLSWSTRLUT0;

    VPSS_DRLSWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32));
    VPSS_DRLSWSTRLUT0.bits.lswstrlut20 = lswstrlut20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32), VPSS_DRLSWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut10)
{
    U_VPSS_DRLSWSTRLUT0 VPSS_DRLSWSTRLUT0;

    VPSS_DRLSWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32));
    VPSS_DRLSWSTRLUT0.bits.lswstrlut10 = lswstrlut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32), VPSS_DRLSWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut00)
{
    U_VPSS_DRLSWSTRLUT0 VPSS_DRLSWSTRLUT0;

    VPSS_DRLSWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32));
    VPSS_DRLSWSTRLUT0.bits.lswstrlut00 = lswstrlut00;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT0.u32), VPSS_DRLSWSTRLUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut51)
{
    U_VPSS_DRLSWSTRLUT1 VPSS_DRLSWSTRLUT1;

    VPSS_DRLSWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32));
    VPSS_DRLSWSTRLUT1.bits.lswstrlut51 = lswstrlut51;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32), VPSS_DRLSWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut41)
{
    U_VPSS_DRLSWSTRLUT1 VPSS_DRLSWSTRLUT1;

    VPSS_DRLSWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32));
    VPSS_DRLSWSTRLUT1.bits.lswstrlut41 = lswstrlut41;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32), VPSS_DRLSWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut31)
{
    U_VPSS_DRLSWSTRLUT1 VPSS_DRLSWSTRLUT1;

    VPSS_DRLSWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32));
    VPSS_DRLSWSTRLUT1.bits.lswstrlut31 = lswstrlut31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32), VPSS_DRLSWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut21)
{
    U_VPSS_DRLSWSTRLUT1 VPSS_DRLSWSTRLUT1;

    VPSS_DRLSWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32));
    VPSS_DRLSWSTRLUT1.bits.lswstrlut21 = lswstrlut21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32), VPSS_DRLSWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut11)
{
    U_VPSS_DRLSWSTRLUT1 VPSS_DRLSWSTRLUT1;

    VPSS_DRLSWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32));
    VPSS_DRLSWSTRLUT1.bits.lswstrlut11 = lswstrlut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32), VPSS_DRLSWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut01)
{
    U_VPSS_DRLSWSTRLUT1 VPSS_DRLSWSTRLUT1;

    VPSS_DRLSWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32));
    VPSS_DRLSWSTRLUT1.bits.lswstrlut01 = lswstrlut01;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT1.u32), VPSS_DRLSWSTRLUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut52)
{
    U_VPSS_DRLSWSTRLUT2 VPSS_DRLSWSTRLUT2;

    VPSS_DRLSWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32));
    VPSS_DRLSWSTRLUT2.bits.lswstrlut52 = lswstrlut52;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32), VPSS_DRLSWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut42)
{
    U_VPSS_DRLSWSTRLUT2 VPSS_DRLSWSTRLUT2;

    VPSS_DRLSWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32));
    VPSS_DRLSWSTRLUT2.bits.lswstrlut42 = lswstrlut42;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32), VPSS_DRLSWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut32)
{
    U_VPSS_DRLSWSTRLUT2 VPSS_DRLSWSTRLUT2;

    VPSS_DRLSWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32));
    VPSS_DRLSWSTRLUT2.bits.lswstrlut32 = lswstrlut32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32), VPSS_DRLSWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut22)
{
    U_VPSS_DRLSWSTRLUT2 VPSS_DRLSWSTRLUT2;

    VPSS_DRLSWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32));
    VPSS_DRLSWSTRLUT2.bits.lswstrlut22 = lswstrlut22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32), VPSS_DRLSWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut12)
{
    U_VPSS_DRLSWSTRLUT2 VPSS_DRLSWSTRLUT2;

    VPSS_DRLSWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32));
    VPSS_DRLSWSTRLUT2.bits.lswstrlut12 = lswstrlut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32), VPSS_DRLSWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut02)
{
    U_VPSS_DRLSWSTRLUT2 VPSS_DRLSWSTRLUT2;

    VPSS_DRLSWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32));
    VPSS_DRLSWSTRLUT2.bits.lswstrlut02 = lswstrlut02;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT2.u32), VPSS_DRLSWSTRLUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut53)
{
    U_VPSS_DRLSWSTRLUT3 VPSS_DRLSWSTRLUT3;

    VPSS_DRLSWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32));
    VPSS_DRLSWSTRLUT3.bits.lswstrlut53 = lswstrlut53;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32), VPSS_DRLSWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut43)
{
    U_VPSS_DRLSWSTRLUT3 VPSS_DRLSWSTRLUT3;

    VPSS_DRLSWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32));
    VPSS_DRLSWSTRLUT3.bits.lswstrlut43 = lswstrlut43;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32), VPSS_DRLSWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut33)
{
    U_VPSS_DRLSWSTRLUT3 VPSS_DRLSWSTRLUT3;

    VPSS_DRLSWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32));
    VPSS_DRLSWSTRLUT3.bits.lswstrlut33 = lswstrlut33;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32), VPSS_DRLSWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut23)
{
    U_VPSS_DRLSWSTRLUT3 VPSS_DRLSWSTRLUT3;

    VPSS_DRLSWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32));
    VPSS_DRLSWSTRLUT3.bits.lswstrlut23 = lswstrlut23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32), VPSS_DRLSWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut13)
{
    U_VPSS_DRLSWSTRLUT3 VPSS_DRLSWSTRLUT3;

    VPSS_DRLSWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32));
    VPSS_DRLSWSTRLUT3.bits.lswstrlut13 = lswstrlut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32), VPSS_DRLSWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut03(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut03)
{
    U_VPSS_DRLSWSTRLUT3 VPSS_DRLSWSTRLUT3;

    VPSS_DRLSWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32));
    VPSS_DRLSWSTRLUT3.bits.lswstrlut03 = lswstrlut03;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT3.u32), VPSS_DRLSWSTRLUT3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut54)
{
    U_VPSS_DRLSWSTRLUT4 VPSS_DRLSWSTRLUT4;

    VPSS_DRLSWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32));
    VPSS_DRLSWSTRLUT4.bits.lswstrlut54 = lswstrlut54;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32), VPSS_DRLSWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut44)
{
    U_VPSS_DRLSWSTRLUT4 VPSS_DRLSWSTRLUT4;

    VPSS_DRLSWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32));
    VPSS_DRLSWSTRLUT4.bits.lswstrlut44 = lswstrlut44;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32), VPSS_DRLSWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut34)
{
    U_VPSS_DRLSWSTRLUT4 VPSS_DRLSWSTRLUT4;

    VPSS_DRLSWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32));
    VPSS_DRLSWSTRLUT4.bits.lswstrlut34 = lswstrlut34;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32), VPSS_DRLSWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut24)
{
    U_VPSS_DRLSWSTRLUT4 VPSS_DRLSWSTRLUT4;

    VPSS_DRLSWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32));
    VPSS_DRLSWSTRLUT4.bits.lswstrlut24 = lswstrlut24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32), VPSS_DRLSWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut14)
{
    U_VPSS_DRLSWSTRLUT4 VPSS_DRLSWSTRLUT4;

    VPSS_DRLSWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32));
    VPSS_DRLSWSTRLUT4.bits.lswstrlut14 = lswstrlut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32), VPSS_DRLSWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut04(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut04)
{
    U_VPSS_DRLSWSTRLUT4 VPSS_DRLSWSTRLUT4;

    VPSS_DRLSWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32));
    VPSS_DRLSWSTRLUT4.bits.lswstrlut04 = lswstrlut04;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT4.u32), VPSS_DRLSWSTRLUT4.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut55)
{
    U_VPSS_DRLSWSTRLUT5 VPSS_DRLSWSTRLUT5;

    VPSS_DRLSWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32));
    VPSS_DRLSWSTRLUT5.bits.lswstrlut55 = lswstrlut55;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32), VPSS_DRLSWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut45)
{
    U_VPSS_DRLSWSTRLUT5 VPSS_DRLSWSTRLUT5;

    VPSS_DRLSWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32));
    VPSS_DRLSWSTRLUT5.bits.lswstrlut45 = lswstrlut45;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32), VPSS_DRLSWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut35)
{
    U_VPSS_DRLSWSTRLUT5 VPSS_DRLSWSTRLUT5;

    VPSS_DRLSWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32));
    VPSS_DRLSWSTRLUT5.bits.lswstrlut35 = lswstrlut35;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32), VPSS_DRLSWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut25)
{
    U_VPSS_DRLSWSTRLUT5 VPSS_DRLSWSTRLUT5;

    VPSS_DRLSWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32));
    VPSS_DRLSWSTRLUT5.bits.lswstrlut25 = lswstrlut25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32), VPSS_DRLSWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut15)
{
    U_VPSS_DRLSWSTRLUT5 VPSS_DRLSWSTRLUT5;

    VPSS_DRLSWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32));
    VPSS_DRLSWSTRLUT5.bits.lswstrlut15 = lswstrlut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32), VPSS_DRLSWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut05(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut05)
{
    U_VPSS_DRLSWSTRLUT5 VPSS_DRLSWSTRLUT5;

    VPSS_DRLSWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32));
    VPSS_DRLSWSTRLUT5.bits.lswstrlut05 = lswstrlut05;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT5.u32), VPSS_DRLSWSTRLUT5.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut56)
{
    U_VPSS_DRLSWSTRLUT6 VPSS_DRLSWSTRLUT6;

    VPSS_DRLSWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32));
    VPSS_DRLSWSTRLUT6.bits.lswstrlut56 = lswstrlut56;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32), VPSS_DRLSWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut46)
{
    U_VPSS_DRLSWSTRLUT6 VPSS_DRLSWSTRLUT6;

    VPSS_DRLSWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32));
    VPSS_DRLSWSTRLUT6.bits.lswstrlut46 = lswstrlut46;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32), VPSS_DRLSWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut36)
{
    U_VPSS_DRLSWSTRLUT6 VPSS_DRLSWSTRLUT6;

    VPSS_DRLSWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32));
    VPSS_DRLSWSTRLUT6.bits.lswstrlut36 = lswstrlut36;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32), VPSS_DRLSWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut26)
{
    U_VPSS_DRLSWSTRLUT6 VPSS_DRLSWSTRLUT6;

    VPSS_DRLSWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32));
    VPSS_DRLSWSTRLUT6.bits.lswstrlut26 = lswstrlut26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32), VPSS_DRLSWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut16)
{
    U_VPSS_DRLSWSTRLUT6 VPSS_DRLSWSTRLUT6;

    VPSS_DRLSWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32));
    VPSS_DRLSWSTRLUT6.bits.lswstrlut16 = lswstrlut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32), VPSS_DRLSWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut06(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut06)
{
    U_VPSS_DRLSWSTRLUT6 VPSS_DRLSWSTRLUT6;

    VPSS_DRLSWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32));
    VPSS_DRLSWSTRLUT6.bits.lswstrlut06 = lswstrlut06;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT6.u32), VPSS_DRLSWSTRLUT6.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut57)
{
    U_VPSS_DRLSWSTRLUT7 VPSS_DRLSWSTRLUT7;

    VPSS_DRLSWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32));
    VPSS_DRLSWSTRLUT7.bits.lswstrlut57 = lswstrlut57;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32), VPSS_DRLSWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut47)
{
    U_VPSS_DRLSWSTRLUT7 VPSS_DRLSWSTRLUT7;

    VPSS_DRLSWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32));
    VPSS_DRLSWSTRLUT7.bits.lswstrlut47 = lswstrlut47;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32), VPSS_DRLSWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut37)
{
    U_VPSS_DRLSWSTRLUT7 VPSS_DRLSWSTRLUT7;

    VPSS_DRLSWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32));
    VPSS_DRLSWSTRLUT7.bits.lswstrlut37 = lswstrlut37;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32), VPSS_DRLSWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut27)
{
    U_VPSS_DRLSWSTRLUT7 VPSS_DRLSWSTRLUT7;

    VPSS_DRLSWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32));
    VPSS_DRLSWSTRLUT7.bits.lswstrlut27 = lswstrlut27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32), VPSS_DRLSWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut17)
{
    U_VPSS_DRLSWSTRLUT7 VPSS_DRLSWSTRLUT7;

    VPSS_DRLSWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32));
    VPSS_DRLSWSTRLUT7.bits.lswstrlut17 = lswstrlut17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32), VPSS_DRLSWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut07(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut07)
{
    U_VPSS_DRLSWSTRLUT7 VPSS_DRLSWSTRLUT7;

    VPSS_DRLSWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32));
    VPSS_DRLSWSTRLUT7.bits.lswstrlut07 = lswstrlut07;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT7.u32), VPSS_DRLSWSTRLUT7.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLswstrlut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut58)
{
    U_VPSS_DRLSWSTRLUT8 VPSS_DRLSWSTRLUT8;

    VPSS_DRLSWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32));
    VPSS_DRLSWSTRLUT8.bits.lswstrlut58 = lswstrlut58;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32), VPSS_DRLSWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut48)
{
    U_VPSS_DRLSWSTRLUT8 VPSS_DRLSWSTRLUT8;

    VPSS_DRLSWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32));
    VPSS_DRLSWSTRLUT8.bits.lswstrlut48 = lswstrlut48;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32), VPSS_DRLSWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut38)
{
    U_VPSS_DRLSWSTRLUT8 VPSS_DRLSWSTRLUT8;

    VPSS_DRLSWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32));
    VPSS_DRLSWSTRLUT8.bits.lswstrlut38 = lswstrlut38;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32), VPSS_DRLSWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut28)
{
    U_VPSS_DRLSWSTRLUT8 VPSS_DRLSWSTRLUT8;

    VPSS_DRLSWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32));
    VPSS_DRLSWSTRLUT8.bits.lswstrlut28 = lswstrlut28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32), VPSS_DRLSWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut18)
{
    U_VPSS_DRLSWSTRLUT8 VPSS_DRLSWSTRLUT8;

    VPSS_DRLSWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32));
    VPSS_DRLSWSTRLUT8.bits.lswstrlut18 = lswstrlut18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32), VPSS_DRLSWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLswstrlut08(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lswstrlut08)
{
    U_VPSS_DRLSWSTRLUT8 VPSS_DRLSWSTRLUT8;

    VPSS_DRLSWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32));
    VPSS_DRLSWSTRLUT8.bits.lswstrlut08 = lswstrlut08;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRLUT8.u32), VPSS_DRLSWSTRLUT8.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut50)
{
    U_VPSS_DRLRWSTRLUT0 VPSS_DRLRWSTRLUT0;

    VPSS_DRLRWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32));
    VPSS_DRLRWSTRLUT0.bits.lrwstrlut50 = lrwstrlut50;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32), VPSS_DRLRWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut40)
{
    U_VPSS_DRLRWSTRLUT0 VPSS_DRLRWSTRLUT0;

    VPSS_DRLRWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32));
    VPSS_DRLRWSTRLUT0.bits.lrwstrlut40 = lrwstrlut40;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32), VPSS_DRLRWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut30)
{
    U_VPSS_DRLRWSTRLUT0 VPSS_DRLRWSTRLUT0;

    VPSS_DRLRWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32));
    VPSS_DRLRWSTRLUT0.bits.lrwstrlut30 = lrwstrlut30;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32), VPSS_DRLRWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut20)
{
    U_VPSS_DRLRWSTRLUT0 VPSS_DRLRWSTRLUT0;

    VPSS_DRLRWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32));
    VPSS_DRLRWSTRLUT0.bits.lrwstrlut20 = lrwstrlut20;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32), VPSS_DRLRWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut10)
{
    U_VPSS_DRLRWSTRLUT0 VPSS_DRLRWSTRLUT0;

    VPSS_DRLRWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32));
    VPSS_DRLRWSTRLUT0.bits.lrwstrlut10 = lrwstrlut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32), VPSS_DRLRWSTRLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut00)
{
    U_VPSS_DRLRWSTRLUT0 VPSS_DRLRWSTRLUT0;

    VPSS_DRLRWSTRLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32));
    VPSS_DRLRWSTRLUT0.bits.lrwstrlut00 = lrwstrlut00;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT0.u32), VPSS_DRLRWSTRLUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut51)
{
    U_VPSS_DRLRWSTRLUT1 VPSS_DRLRWSTRLUT1;

    VPSS_DRLRWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32));
    VPSS_DRLRWSTRLUT1.bits.lrwstrlut51 = lrwstrlut51;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32), VPSS_DRLRWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut41)
{
    U_VPSS_DRLRWSTRLUT1 VPSS_DRLRWSTRLUT1;

    VPSS_DRLRWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32));
    VPSS_DRLRWSTRLUT1.bits.lrwstrlut41 = lrwstrlut41;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32), VPSS_DRLRWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut31)
{
    U_VPSS_DRLRWSTRLUT1 VPSS_DRLRWSTRLUT1;

    VPSS_DRLRWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32));
    VPSS_DRLRWSTRLUT1.bits.lrwstrlut31 = lrwstrlut31;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32), VPSS_DRLRWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut21)
{
    U_VPSS_DRLRWSTRLUT1 VPSS_DRLRWSTRLUT1;

    VPSS_DRLRWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32));
    VPSS_DRLRWSTRLUT1.bits.lrwstrlut21 = lrwstrlut21;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32), VPSS_DRLRWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut11)
{
    U_VPSS_DRLRWSTRLUT1 VPSS_DRLRWSTRLUT1;

    VPSS_DRLRWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32));
    VPSS_DRLRWSTRLUT1.bits.lrwstrlut11 = lrwstrlut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32), VPSS_DRLRWSTRLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut01)
{
    U_VPSS_DRLRWSTRLUT1 VPSS_DRLRWSTRLUT1;

    VPSS_DRLRWSTRLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32));
    VPSS_DRLRWSTRLUT1.bits.lrwstrlut01 = lrwstrlut01;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT1.u32), VPSS_DRLRWSTRLUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut52)
{
    U_VPSS_DRLRWSTRLUT2 VPSS_DRLRWSTRLUT2;

    VPSS_DRLRWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32));
    VPSS_DRLRWSTRLUT2.bits.lrwstrlut52 = lrwstrlut52;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32), VPSS_DRLRWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut42)
{
    U_VPSS_DRLRWSTRLUT2 VPSS_DRLRWSTRLUT2;

    VPSS_DRLRWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32));
    VPSS_DRLRWSTRLUT2.bits.lrwstrlut42 = lrwstrlut42;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32), VPSS_DRLRWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut32)
{
    U_VPSS_DRLRWSTRLUT2 VPSS_DRLRWSTRLUT2;

    VPSS_DRLRWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32));
    VPSS_DRLRWSTRLUT2.bits.lrwstrlut32 = lrwstrlut32;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32), VPSS_DRLRWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut22)
{
    U_VPSS_DRLRWSTRLUT2 VPSS_DRLRWSTRLUT2;

    VPSS_DRLRWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32));
    VPSS_DRLRWSTRLUT2.bits.lrwstrlut22 = lrwstrlut22;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32), VPSS_DRLRWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut12)
{
    U_VPSS_DRLRWSTRLUT2 VPSS_DRLRWSTRLUT2;

    VPSS_DRLRWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32));
    VPSS_DRLRWSTRLUT2.bits.lrwstrlut12 = lrwstrlut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32), VPSS_DRLRWSTRLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut02)
{
    U_VPSS_DRLRWSTRLUT2 VPSS_DRLRWSTRLUT2;

    VPSS_DRLRWSTRLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32));
    VPSS_DRLRWSTRLUT2.bits.lrwstrlut02 = lrwstrlut02;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT2.u32), VPSS_DRLRWSTRLUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut53)
{
    U_VPSS_DRLRWSTRLUT3 VPSS_DRLRWSTRLUT3;

    VPSS_DRLRWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32));
    VPSS_DRLRWSTRLUT3.bits.lrwstrlut53 = lrwstrlut53;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32), VPSS_DRLRWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut43)
{
    U_VPSS_DRLRWSTRLUT3 VPSS_DRLRWSTRLUT3;

    VPSS_DRLRWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32));
    VPSS_DRLRWSTRLUT3.bits.lrwstrlut43 = lrwstrlut43;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32), VPSS_DRLRWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut33)
{
    U_VPSS_DRLRWSTRLUT3 VPSS_DRLRWSTRLUT3;

    VPSS_DRLRWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32));
    VPSS_DRLRWSTRLUT3.bits.lrwstrlut33 = lrwstrlut33;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32), VPSS_DRLRWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut23)
{
    U_VPSS_DRLRWSTRLUT3 VPSS_DRLRWSTRLUT3;

    VPSS_DRLRWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32));
    VPSS_DRLRWSTRLUT3.bits.lrwstrlut23 = lrwstrlut23;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32), VPSS_DRLRWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut13)
{
    U_VPSS_DRLRWSTRLUT3 VPSS_DRLRWSTRLUT3;

    VPSS_DRLRWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32));
    VPSS_DRLRWSTRLUT3.bits.lrwstrlut13 = lrwstrlut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32), VPSS_DRLRWSTRLUT3.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut03(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut03)
{
    U_VPSS_DRLRWSTRLUT3 VPSS_DRLRWSTRLUT3;

    VPSS_DRLRWSTRLUT3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32));
    VPSS_DRLRWSTRLUT3.bits.lrwstrlut03 = lrwstrlut03;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT3.u32), VPSS_DRLRWSTRLUT3.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut54)
{
    U_VPSS_DRLRWSTRLUT4 VPSS_DRLRWSTRLUT4;

    VPSS_DRLRWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32));
    VPSS_DRLRWSTRLUT4.bits.lrwstrlut54 = lrwstrlut54;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32), VPSS_DRLRWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut44)
{
    U_VPSS_DRLRWSTRLUT4 VPSS_DRLRWSTRLUT4;

    VPSS_DRLRWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32));
    VPSS_DRLRWSTRLUT4.bits.lrwstrlut44 = lrwstrlut44;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32), VPSS_DRLRWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut34)
{
    U_VPSS_DRLRWSTRLUT4 VPSS_DRLRWSTRLUT4;

    VPSS_DRLRWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32));
    VPSS_DRLRWSTRLUT4.bits.lrwstrlut34 = lrwstrlut34;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32), VPSS_DRLRWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut24)
{
    U_VPSS_DRLRWSTRLUT4 VPSS_DRLRWSTRLUT4;

    VPSS_DRLRWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32));
    VPSS_DRLRWSTRLUT4.bits.lrwstrlut24 = lrwstrlut24;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32), VPSS_DRLRWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut14)
{
    U_VPSS_DRLRWSTRLUT4 VPSS_DRLRWSTRLUT4;

    VPSS_DRLRWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32));
    VPSS_DRLRWSTRLUT4.bits.lrwstrlut14 = lrwstrlut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32), VPSS_DRLRWSTRLUT4.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut04(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut04)
{
    U_VPSS_DRLRWSTRLUT4 VPSS_DRLRWSTRLUT4;

    VPSS_DRLRWSTRLUT4.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32));
    VPSS_DRLRWSTRLUT4.bits.lrwstrlut04 = lrwstrlut04;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT4.u32), VPSS_DRLRWSTRLUT4.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut55)
{
    U_VPSS_DRLRWSTRLUT5 VPSS_DRLRWSTRLUT5;

    VPSS_DRLRWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32));
    VPSS_DRLRWSTRLUT5.bits.lrwstrlut55 = lrwstrlut55;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32), VPSS_DRLRWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut45)
{
    U_VPSS_DRLRWSTRLUT5 VPSS_DRLRWSTRLUT5;

    VPSS_DRLRWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32));
    VPSS_DRLRWSTRLUT5.bits.lrwstrlut45 = lrwstrlut45;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32), VPSS_DRLRWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut35)
{
    U_VPSS_DRLRWSTRLUT5 VPSS_DRLRWSTRLUT5;

    VPSS_DRLRWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32));
    VPSS_DRLRWSTRLUT5.bits.lrwstrlut35 = lrwstrlut35;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32), VPSS_DRLRWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut25)
{
    U_VPSS_DRLRWSTRLUT5 VPSS_DRLRWSTRLUT5;

    VPSS_DRLRWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32));
    VPSS_DRLRWSTRLUT5.bits.lrwstrlut25 = lrwstrlut25;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32), VPSS_DRLRWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut15)
{
    U_VPSS_DRLRWSTRLUT5 VPSS_DRLRWSTRLUT5;

    VPSS_DRLRWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32));
    VPSS_DRLRWSTRLUT5.bits.lrwstrlut15 = lrwstrlut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32), VPSS_DRLRWSTRLUT5.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut05(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut05)
{
    U_VPSS_DRLRWSTRLUT5 VPSS_DRLRWSTRLUT5;

    VPSS_DRLRWSTRLUT5.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32));
    VPSS_DRLRWSTRLUT5.bits.lrwstrlut05 = lrwstrlut05;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT5.u32), VPSS_DRLRWSTRLUT5.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut56)
{
    U_VPSS_DRLRWSTRLUT6 VPSS_DRLRWSTRLUT6;

    VPSS_DRLRWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32));
    VPSS_DRLRWSTRLUT6.bits.lrwstrlut56 = lrwstrlut56;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32), VPSS_DRLRWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut46)
{
    U_VPSS_DRLRWSTRLUT6 VPSS_DRLRWSTRLUT6;

    VPSS_DRLRWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32));
    VPSS_DRLRWSTRLUT6.bits.lrwstrlut46 = lrwstrlut46;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32), VPSS_DRLRWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut36)
{
    U_VPSS_DRLRWSTRLUT6 VPSS_DRLRWSTRLUT6;

    VPSS_DRLRWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32));
    VPSS_DRLRWSTRLUT6.bits.lrwstrlut36 = lrwstrlut36;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32), VPSS_DRLRWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut26)
{
    U_VPSS_DRLRWSTRLUT6 VPSS_DRLRWSTRLUT6;

    VPSS_DRLRWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32));
    VPSS_DRLRWSTRLUT6.bits.lrwstrlut26 = lrwstrlut26;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32), VPSS_DRLRWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut16)
{
    U_VPSS_DRLRWSTRLUT6 VPSS_DRLRWSTRLUT6;

    VPSS_DRLRWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32));
    VPSS_DRLRWSTRLUT6.bits.lrwstrlut16 = lrwstrlut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32), VPSS_DRLRWSTRLUT6.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut06(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut06)
{
    U_VPSS_DRLRWSTRLUT6 VPSS_DRLRWSTRLUT6;

    VPSS_DRLRWSTRLUT6.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32));
    VPSS_DRLRWSTRLUT6.bits.lrwstrlut06 = lrwstrlut06;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT6.u32), VPSS_DRLRWSTRLUT6.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut57)
{
    U_VPSS_DRLRWSTRLUT7 VPSS_DRLRWSTRLUT7;

    VPSS_DRLRWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32));
    VPSS_DRLRWSTRLUT7.bits.lrwstrlut57 = lrwstrlut57;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32), VPSS_DRLRWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut47)
{
    U_VPSS_DRLRWSTRLUT7 VPSS_DRLRWSTRLUT7;

    VPSS_DRLRWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32));
    VPSS_DRLRWSTRLUT7.bits.lrwstrlut47 = lrwstrlut47;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32), VPSS_DRLRWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut37)
{
    U_VPSS_DRLRWSTRLUT7 VPSS_DRLRWSTRLUT7;

    VPSS_DRLRWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32));
    VPSS_DRLRWSTRLUT7.bits.lrwstrlut37 = lrwstrlut37;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32), VPSS_DRLRWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut27)
{
    U_VPSS_DRLRWSTRLUT7 VPSS_DRLRWSTRLUT7;

    VPSS_DRLRWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32));
    VPSS_DRLRWSTRLUT7.bits.lrwstrlut27 = lrwstrlut27;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32), VPSS_DRLRWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut17)
{
    U_VPSS_DRLRWSTRLUT7 VPSS_DRLRWSTRLUT7;

    VPSS_DRLRWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32));
    VPSS_DRLRWSTRLUT7.bits.lrwstrlut17 = lrwstrlut17;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32), VPSS_DRLRWSTRLUT7.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut07(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut07)
{
    U_VPSS_DRLRWSTRLUT7 VPSS_DRLRWSTRLUT7;

    VPSS_DRLRWSTRLUT7.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32));
    VPSS_DRLRWSTRLUT7.bits.lrwstrlut07 = lrwstrlut07;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT7.u32), VPSS_DRLRWSTRLUT7.u32);

    return ;
}



HI_VOID VPSS_Snr_SetLrwstrlut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut58)
{
    U_VPSS_DRLRWSTRLUT8 VPSS_DRLRWSTRLUT8;

    VPSS_DRLRWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32));
    VPSS_DRLRWSTRLUT8.bits.lrwstrlut58 = lrwstrlut58;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32), VPSS_DRLRWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut48)
{
    U_VPSS_DRLRWSTRLUT8 VPSS_DRLRWSTRLUT8;

    VPSS_DRLRWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32));
    VPSS_DRLRWSTRLUT8.bits.lrwstrlut48 = lrwstrlut48;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32), VPSS_DRLRWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut38)
{
    U_VPSS_DRLRWSTRLUT8 VPSS_DRLRWSTRLUT8;

    VPSS_DRLRWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32));
    VPSS_DRLRWSTRLUT8.bits.lrwstrlut38 = lrwstrlut38;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32), VPSS_DRLRWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut28)
{
    U_VPSS_DRLRWSTRLUT8 VPSS_DRLRWSTRLUT8;

    VPSS_DRLRWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32));
    VPSS_DRLRWSTRLUT8.bits.lrwstrlut28 = lrwstrlut28;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32), VPSS_DRLRWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut18)
{
    U_VPSS_DRLRWSTRLUT8 VPSS_DRLRWSTRLUT8;

    VPSS_DRLRWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32));
    VPSS_DRLRWSTRLUT8.bits.lrwstrlut18 = lrwstrlut18;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32), VPSS_DRLRWSTRLUT8.u32);

    return ;
}


HI_VOID VPSS_Snr_SetLrwstrlut08(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 lrwstrlut08)
{
    U_VPSS_DRLRWSTRLUT8 VPSS_DRLRWSTRLUT8;

    VPSS_DRLRWSTRLUT8.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32));
    VPSS_DRLRWSTRLUT8.bits.lrwstrlut08 = lrwstrlut08;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRLUT8.u32), VPSS_DRLRWSTRLUT8.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrLswadjlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut2)
{
    U_VPSS_DRLSWSTRADJUSTLUT0 VPSS_DRLSWSTRADJUSTLUT0;

    VPSS_DRLSWSTRADJUSTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT0.u32));
    VPSS_DRLSWSTRADJUSTLUT0.bits.dr_lswadjlut2 = dr_lswadjlut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT0.u32), VPSS_DRLSWSTRADJUSTLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLswadjlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut1)
{
    U_VPSS_DRLSWSTRADJUSTLUT0 VPSS_DRLSWSTRADJUSTLUT0;

    VPSS_DRLSWSTRADJUSTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT0.u32));
    VPSS_DRLSWSTRADJUSTLUT0.bits.dr_lswadjlut1 = dr_lswadjlut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT0.u32), VPSS_DRLSWSTRADJUSTLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLswadjlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut0)
{
    U_VPSS_DRLSWSTRADJUSTLUT0 VPSS_DRLSWSTRADJUSTLUT0;

    VPSS_DRLSWSTRADJUSTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT0.u32));
    VPSS_DRLSWSTRADJUSTLUT0.bits.dr_lswadjlut0 = dr_lswadjlut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT0.u32), VPSS_DRLSWSTRADJUSTLUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrLswadjlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut5)
{
    U_VPSS_DRLSWSTRADJUSTLUT1 VPSS_DRLSWSTRADJUSTLUT1;

    VPSS_DRLSWSTRADJUSTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT1.u32));
    VPSS_DRLSWSTRADJUSTLUT1.bits.dr_lswadjlut5 = dr_lswadjlut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT1.u32), VPSS_DRLSWSTRADJUSTLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLswadjlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut4)
{
    U_VPSS_DRLSWSTRADJUSTLUT1 VPSS_DRLSWSTRADJUSTLUT1;

    VPSS_DRLSWSTRADJUSTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT1.u32));
    VPSS_DRLSWSTRADJUSTLUT1.bits.dr_lswadjlut4 = dr_lswadjlut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT1.u32), VPSS_DRLSWSTRADJUSTLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLswadjlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut3)
{
    U_VPSS_DRLSWSTRADJUSTLUT1 VPSS_DRLSWSTRADJUSTLUT1;

    VPSS_DRLSWSTRADJUSTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT1.u32));
    VPSS_DRLSWSTRADJUSTLUT1.bits.dr_lswadjlut3 = dr_lswadjlut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT1.u32), VPSS_DRLSWSTRADJUSTLUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrLswadjlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut8)
{
    U_VPSS_DRLSWSTRADJUSTLUT2 VPSS_DRLSWSTRADJUSTLUT2;

    VPSS_DRLSWSTRADJUSTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT2.u32));
    VPSS_DRLSWSTRADJUSTLUT2.bits.dr_lswadjlut8 = dr_lswadjlut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT2.u32), VPSS_DRLSWSTRADJUSTLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLswadjlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut7)
{
    U_VPSS_DRLSWSTRADJUSTLUT2 VPSS_DRLSWSTRADJUSTLUT2;

    VPSS_DRLSWSTRADJUSTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT2.u32));
    VPSS_DRLSWSTRADJUSTLUT2.bits.dr_lswadjlut7 = dr_lswadjlut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT2.u32), VPSS_DRLSWSTRADJUSTLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLswadjlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lswadjlut6)
{
    U_VPSS_DRLSWSTRADJUSTLUT2 VPSS_DRLSWSTRADJUSTLUT2;

    VPSS_DRLSWSTRADJUSTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT2.u32));
    VPSS_DRLSWSTRADJUSTLUT2.bits.dr_lswadjlut6 = dr_lswadjlut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLSWSTRADJUSTLUT2.u32), VPSS_DRLSWSTRADJUSTLUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrLrwadjlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut2)
{
    U_VPSS_DRLRWSTRADJUSTLUT0 VPSS_DRLRWSTRADJUSTLUT0;

    VPSS_DRLRWSTRADJUSTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT0.u32));
    VPSS_DRLRWSTRADJUSTLUT0.bits.dr_lrwadjlut2 = dr_lrwadjlut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT0.u32), VPSS_DRLRWSTRADJUSTLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLrwadjlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut1)
{
    U_VPSS_DRLRWSTRADJUSTLUT0 VPSS_DRLRWSTRADJUSTLUT0;

    VPSS_DRLRWSTRADJUSTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT0.u32));
    VPSS_DRLRWSTRADJUSTLUT0.bits.dr_lrwadjlut1 = dr_lrwadjlut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT0.u32), VPSS_DRLRWSTRADJUSTLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLrwadjlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut0)
{
    U_VPSS_DRLRWSTRADJUSTLUT0 VPSS_DRLRWSTRADJUSTLUT0;

    VPSS_DRLRWSTRADJUSTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT0.u32));
    VPSS_DRLRWSTRADJUSTLUT0.bits.dr_lrwadjlut0 = dr_lrwadjlut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT0.u32), VPSS_DRLRWSTRADJUSTLUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrLrwadjlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut5)
{
    U_VPSS_DRLRWSTRADJUSTLUT1 VPSS_DRLRWSTRADJUSTLUT1;

    VPSS_DRLRWSTRADJUSTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT1.u32));
    VPSS_DRLRWSTRADJUSTLUT1.bits.dr_lrwadjlut5 = dr_lrwadjlut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT1.u32), VPSS_DRLRWSTRADJUSTLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLrwadjlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut4)
{
    U_VPSS_DRLRWSTRADJUSTLUT1 VPSS_DRLRWSTRADJUSTLUT1;

    VPSS_DRLRWSTRADJUSTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT1.u32));
    VPSS_DRLRWSTRADJUSTLUT1.bits.dr_lrwadjlut4 = dr_lrwadjlut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT1.u32), VPSS_DRLRWSTRADJUSTLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLrwadjlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut3)
{
    U_VPSS_DRLRWSTRADJUSTLUT1 VPSS_DRLRWSTRADJUSTLUT1;

    VPSS_DRLRWSTRADJUSTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT1.u32));
    VPSS_DRLRWSTRADJUSTLUT1.bits.dr_lrwadjlut3 = dr_lrwadjlut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT1.u32), VPSS_DRLRWSTRADJUSTLUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrLrwadjlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut8)
{
    U_VPSS_DRLRWSTRADJUSTLUT2 VPSS_DRLRWSTRADJUSTLUT2;

    VPSS_DRLRWSTRADJUSTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT2.u32));
    VPSS_DRLRWSTRADJUSTLUT2.bits.dr_lrwadjlut8 = dr_lrwadjlut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT2.u32), VPSS_DRLRWSTRADJUSTLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLrwadjlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut7)
{
    U_VPSS_DRLRWSTRADJUSTLUT2 VPSS_DRLRWSTRADJUSTLUT2;

    VPSS_DRLRWSTRADJUSTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT2.u32));
    VPSS_DRLRWSTRADJUSTLUT2.bits.dr_lrwadjlut7 = dr_lrwadjlut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT2.u32), VPSS_DRLRWSTRADJUSTLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrLrwadjlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_lrwadjlut6)
{
    U_VPSS_DRLRWSTRADJUSTLUT2 VPSS_DRLRWSTRADJUSTLUT2;

    VPSS_DRLRWSTRADJUSTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT2.u32));
    VPSS_DRLRWSTRADJUSTLUT2.bits.dr_lrwadjlut6 = dr_lrwadjlut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRLRWSTRADJUSTLUT2.u32), VPSS_DRLRWSTRADJUSTLUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngadjlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut2)
{
    U_VPSS_DRANGADJSUTLUT0 VPSS_DRANGADJSUTLUT0;

    VPSS_DRANGADJSUTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT0.u32));
    VPSS_DRANGADJSUTLUT0.bits.dr_angadjlut2 = dr_angadjlut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT0.u32), VPSS_DRANGADJSUTLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngadjlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut1)
{
    U_VPSS_DRANGADJSUTLUT0 VPSS_DRANGADJSUTLUT0;

    VPSS_DRANGADJSUTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT0.u32));
    VPSS_DRANGADJSUTLUT0.bits.dr_angadjlut1 = dr_angadjlut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT0.u32), VPSS_DRANGADJSUTLUT0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngadjlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut0)
{
    U_VPSS_DRANGADJSUTLUT0 VPSS_DRANGADJSUTLUT0;

    VPSS_DRANGADJSUTLUT0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT0.u32));
    VPSS_DRANGADJSUTLUT0.bits.dr_angadjlut0 = dr_angadjlut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT0.u32), VPSS_DRANGADJSUTLUT0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngadjlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut5)
{
    U_VPSS_DRANGADJSUTLUT1 VPSS_DRANGADJSUTLUT1;

    VPSS_DRANGADJSUTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT1.u32));
    VPSS_DRANGADJSUTLUT1.bits.dr_angadjlut5 = dr_angadjlut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT1.u32), VPSS_DRANGADJSUTLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngadjlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut4)
{
    U_VPSS_DRANGADJSUTLUT1 VPSS_DRANGADJSUTLUT1;

    VPSS_DRANGADJSUTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT1.u32));
    VPSS_DRANGADJSUTLUT1.bits.dr_angadjlut4 = dr_angadjlut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT1.u32), VPSS_DRANGADJSUTLUT1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngadjlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut3)
{
    U_VPSS_DRANGADJSUTLUT1 VPSS_DRANGADJSUTLUT1;

    VPSS_DRANGADJSUTLUT1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT1.u32));
    VPSS_DRANGADJSUTLUT1.bits.dr_angadjlut3 = dr_angadjlut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT1.u32), VPSS_DRANGADJSUTLUT1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngadjlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut8)
{
    U_VPSS_DRANGADJSUTLUT2 VPSS_DRANGADJSUTLUT2;

    VPSS_DRANGADJSUTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT2.u32));
    VPSS_DRANGADJSUTLUT2.bits.dr_angadjlut8 = dr_angadjlut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT2.u32), VPSS_DRANGADJSUTLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngadjlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut7)
{
    U_VPSS_DRANGADJSUTLUT2 VPSS_DRANGADJSUTLUT2;

    VPSS_DRANGADJSUTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT2.u32));
    VPSS_DRANGADJSUTLUT2.bits.dr_angadjlut7 = dr_angadjlut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT2.u32), VPSS_DRANGADJSUTLUT2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngadjlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angadjlut6)
{
    U_VPSS_DRANGADJSUTLUT2 VPSS_DRANGADJSUTLUT2;

    VPSS_DRANGADJSUTLUT2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT2.u32));
    VPSS_DRANGADJSUTLUT2.bits.dr_angadjlut6 = dr_angadjlut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGADJSUTLUT2.u32), VPSS_DRANGADJSUTLUT2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngdifflut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut5)
{
    U_VPSS_DRANGLESTRLUT1_0 VPSS_DRANGLESTRLUT1_0;

    VPSS_DRANGLESTRLUT1_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32));
    VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut5 = dr_angdifflut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32), VPSS_DRANGLESTRLUT1_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut4)
{
    U_VPSS_DRANGLESTRLUT1_0 VPSS_DRANGLESTRLUT1_0;

    VPSS_DRANGLESTRLUT1_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32));
    VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut4 = dr_angdifflut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32), VPSS_DRANGLESTRLUT1_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut3)
{
    U_VPSS_DRANGLESTRLUT1_0 VPSS_DRANGLESTRLUT1_0;

    VPSS_DRANGLESTRLUT1_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32));
    VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut3 = dr_angdifflut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32), VPSS_DRANGLESTRLUT1_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut2)
{
    U_VPSS_DRANGLESTRLUT1_0 VPSS_DRANGLESTRLUT1_0;

    VPSS_DRANGLESTRLUT1_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32));
    VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut2 = dr_angdifflut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32), VPSS_DRANGLESTRLUT1_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut1)
{
    U_VPSS_DRANGLESTRLUT1_0 VPSS_DRANGLESTRLUT1_0;

    VPSS_DRANGLESTRLUT1_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32));
    VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut1 = dr_angdifflut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32), VPSS_DRANGLESTRLUT1_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut0)
{
    U_VPSS_DRANGLESTRLUT1_0 VPSS_DRANGLESTRLUT1_0;

    VPSS_DRANGLESTRLUT1_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32));
    VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut0 = dr_angdifflut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_0.u32), VPSS_DRANGLESTRLUT1_0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngdifflut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut11)
{
    U_VPSS_DRANGLESTRLUT1_1 VPSS_DRANGLESTRLUT1_1;

    VPSS_DRANGLESTRLUT1_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32));
    VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut11 = dr_angdifflut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32), VPSS_DRANGLESTRLUT1_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut10)
{
    U_VPSS_DRANGLESTRLUT1_1 VPSS_DRANGLESTRLUT1_1;

    VPSS_DRANGLESTRLUT1_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32));
    VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut10 = dr_angdifflut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32), VPSS_DRANGLESTRLUT1_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut9)
{
    U_VPSS_DRANGLESTRLUT1_1 VPSS_DRANGLESTRLUT1_1;

    VPSS_DRANGLESTRLUT1_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32));
    VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut9 = dr_angdifflut9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32), VPSS_DRANGLESTRLUT1_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut8)
{
    U_VPSS_DRANGLESTRLUT1_1 VPSS_DRANGLESTRLUT1_1;

    VPSS_DRANGLESTRLUT1_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32));
    VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut8 = dr_angdifflut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32), VPSS_DRANGLESTRLUT1_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut7)
{
    U_VPSS_DRANGLESTRLUT1_1 VPSS_DRANGLESTRLUT1_1;

    VPSS_DRANGLESTRLUT1_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32));
    VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut7 = dr_angdifflut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32), VPSS_DRANGLESTRLUT1_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut6)
{
    U_VPSS_DRANGLESTRLUT1_1 VPSS_DRANGLESTRLUT1_1;

    VPSS_DRANGLESTRLUT1_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32));
    VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut6 = dr_angdifflut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_1.u32), VPSS_DRANGLESTRLUT1_1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngdifflut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut16)
{
    U_VPSS_DRANGLESTRLUT1_2 VPSS_DRANGLESTRLUT1_2;

    VPSS_DRANGLESTRLUT1_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32));
    VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut16 = dr_angdifflut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32), VPSS_DRANGLESTRLUT1_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut15)
{
    U_VPSS_DRANGLESTRLUT1_2 VPSS_DRANGLESTRLUT1_2;

    VPSS_DRANGLESTRLUT1_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32));
    VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut15 = dr_angdifflut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32), VPSS_DRANGLESTRLUT1_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut14)
{
    U_VPSS_DRANGLESTRLUT1_2 VPSS_DRANGLESTRLUT1_2;

    VPSS_DRANGLESTRLUT1_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32));
    VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut14 = dr_angdifflut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32), VPSS_DRANGLESTRLUT1_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut13)
{
    U_VPSS_DRANGLESTRLUT1_2 VPSS_DRANGLESTRLUT1_2;

    VPSS_DRANGLESTRLUT1_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32));
    VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut13 = dr_angdifflut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32), VPSS_DRANGLESTRLUT1_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngdifflut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angdifflut12)
{
    U_VPSS_DRANGLESTRLUT1_2 VPSS_DRANGLESTRLUT1_2;

    VPSS_DRANGLESTRLUT1_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32));
    VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut12 = dr_angdifflut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT1_2.u32), VPSS_DRANGLESTRLUT1_2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngminlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut5)
{
    U_VPSS_DRANGLESTRLUT2_0 VPSS_DRANGLESTRLUT2_0;

    VPSS_DRANGLESTRLUT2_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32));
    VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut5 = dr_angminlut5;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32), VPSS_DRANGLESTRLUT2_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut4)
{
    U_VPSS_DRANGLESTRLUT2_0 VPSS_DRANGLESTRLUT2_0;

    VPSS_DRANGLESTRLUT2_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32));
    VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut4 = dr_angminlut4;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32), VPSS_DRANGLESTRLUT2_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut3)
{
    U_VPSS_DRANGLESTRLUT2_0 VPSS_DRANGLESTRLUT2_0;

    VPSS_DRANGLESTRLUT2_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32));
    VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut3 = dr_angminlut3;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32), VPSS_DRANGLESTRLUT2_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut2)
{
    U_VPSS_DRANGLESTRLUT2_0 VPSS_DRANGLESTRLUT2_0;

    VPSS_DRANGLESTRLUT2_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32));
    VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut2 = dr_angminlut2;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32), VPSS_DRANGLESTRLUT2_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut1)
{
    U_VPSS_DRANGLESTRLUT2_0 VPSS_DRANGLESTRLUT2_0;

    VPSS_DRANGLESTRLUT2_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32));
    VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut1 = dr_angminlut1;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32), VPSS_DRANGLESTRLUT2_0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut0)
{
    U_VPSS_DRANGLESTRLUT2_0 VPSS_DRANGLESTRLUT2_0;

    VPSS_DRANGLESTRLUT2_0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32));
    VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut0 = dr_angminlut0;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_0.u32), VPSS_DRANGLESTRLUT2_0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngminlut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut11)
{
    U_VPSS_DRANGLESTRLUT2_1 VPSS_DRANGLESTRLUT2_1;

    VPSS_DRANGLESTRLUT2_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32));
    VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut11 = dr_angminlut11;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32), VPSS_DRANGLESTRLUT2_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut10)
{
    U_VPSS_DRANGLESTRLUT2_1 VPSS_DRANGLESTRLUT2_1;

    VPSS_DRANGLESTRLUT2_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32));
    VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut10 = dr_angminlut10;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32), VPSS_DRANGLESTRLUT2_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut9)
{
    U_VPSS_DRANGLESTRLUT2_1 VPSS_DRANGLESTRLUT2_1;

    VPSS_DRANGLESTRLUT2_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32));
    VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut9 = dr_angminlut9;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32), VPSS_DRANGLESTRLUT2_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut8)
{
    U_VPSS_DRANGLESTRLUT2_1 VPSS_DRANGLESTRLUT2_1;

    VPSS_DRANGLESTRLUT2_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32));
    VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut8 = dr_angminlut8;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32), VPSS_DRANGLESTRLUT2_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut7)
{
    U_VPSS_DRANGLESTRLUT2_1 VPSS_DRANGLESTRLUT2_1;

    VPSS_DRANGLESTRLUT2_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32));
    VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut7 = dr_angminlut7;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32), VPSS_DRANGLESTRLUT2_1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut6)
{
    U_VPSS_DRANGLESTRLUT2_1 VPSS_DRANGLESTRLUT2_1;

    VPSS_DRANGLESTRLUT2_1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32));
    VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut6 = dr_angminlut6;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_1.u32), VPSS_DRANGLESTRLUT2_1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrAngminlut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut16)
{
    U_VPSS_DRANGLESTRLUT2_2 VPSS_DRANGLESTRLUT2_2;

    VPSS_DRANGLESTRLUT2_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32));
    VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut16 = dr_angminlut16;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32), VPSS_DRANGLESTRLUT2_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut15)
{
    U_VPSS_DRANGLESTRLUT2_2 VPSS_DRANGLESTRLUT2_2;

    VPSS_DRANGLESTRLUT2_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32));
    VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut15 = dr_angminlut15;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32), VPSS_DRANGLESTRLUT2_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut14)
{
    U_VPSS_DRANGLESTRLUT2_2 VPSS_DRANGLESTRLUT2_2;

    VPSS_DRANGLESTRLUT2_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32));
    VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut14 = dr_angminlut14;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32), VPSS_DRANGLESTRLUT2_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut13)
{
    U_VPSS_DRANGLESTRLUT2_2 VPSS_DRANGLESTRLUT2_2;

    VPSS_DRANGLESTRLUT2_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32));
    VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut13 = dr_angminlut13;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32), VPSS_DRANGLESTRLUT2_2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDrAngminlut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dr_angminlut12)
{
    U_VPSS_DRANGLESTRLUT2_2 VPSS_DRANGLESTRLUT2_2;

    VPSS_DRANGLESTRLUT2_2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32));
    VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut12 = dr_angminlut12;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DRANGLESTRLUT2_2.u32), VPSS_DRANGLESTRLUT2_2.u32);

    return ;
}



HI_VOID VPSS_Snr_SetDrdirBlendStr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 drdir_blend_str)
{
    U_VPSS_DMDR_MERGE VPSS_DMDR_MERGE;

    VPSS_DMDR_MERGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32));
    VPSS_DMDR_MERGE.bits.drdir_blend_str = drdir_blend_str;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32), VPSS_DMDR_MERGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetDmcondAppDren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 dmcond_app_dren)
{
    U_VPSS_DMDR_MERGE VPSS_DMDR_MERGE;

    VPSS_DMDR_MERGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32));
    VPSS_DMDR_MERGE.bits.dmcond_app_dren = dmcond_app_dren;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32), VPSS_DMDR_MERGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetU8drdmBlendStr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u8drdm_blend_str)
{
    U_VPSS_DMDR_MERGE VPSS_DMDR_MERGE;

    VPSS_DMDR_MERGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32));
    VPSS_DMDR_MERGE.bits.u8drdm_blend_str = u8drdm_blend_str;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32), VPSS_DMDR_MERGE.u32);

    return ;
}


HI_VOID VPSS_Snr_SetU8drdmMergeMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u8drdm_merge_mode)
{
    U_VPSS_DMDR_MERGE VPSS_DMDR_MERGE;

    VPSS_DMDR_MERGE.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32));
    VPSS_DMDR_MERGE.bits.u8drdm_merge_mode = u8drdm_merge_mode;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE.u32), VPSS_DMDR_MERGE.u32);

    return ;
}



HI_VOID VPSS_Snr_SetAlphaActhvrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 alpha_acthvrange)
{
    U_VPSS_DMDR_MERGE_DELTA0 VPSS_DMDR_MERGE_DELTA0;

    VPSS_DMDR_MERGE_DELTA0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA0.u32));
    VPSS_DMDR_MERGE_DELTA0.bits.alpha_acthvrange = alpha_acthvrange;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA0.u32), VPSS_DMDR_MERGE_DELTA0.u32);

    return ;
}


HI_VOID VPSS_Snr_SetAlphaActhvratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 alpha_acthvratio)
{
    U_VPSS_DMDR_MERGE_DELTA0 VPSS_DMDR_MERGE_DELTA0;

    VPSS_DMDR_MERGE_DELTA0.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA0.u32));
    VPSS_DMDR_MERGE_DELTA0.bits.alpha_acthvratio = alpha_acthvratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA0.u32), VPSS_DMDR_MERGE_DELTA0.u32);

    return ;
}



HI_VOID VPSS_Snr_SetWinactLimit(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 winact_limit)
{
    U_VPSS_DMDR_MERGE_DELTA1 VPSS_DMDR_MERGE_DELTA1;

    VPSS_DMDR_MERGE_DELTA1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA1.u32));
    VPSS_DMDR_MERGE_DELTA1.bits.winact_limit = winact_limit;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA1.u32), VPSS_DMDR_MERGE_DELTA1.u32);

    return ;
}


HI_VOID VPSS_Snr_SetWinactCliplimit(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 winact_cliplimit)
{
    U_VPSS_DMDR_MERGE_DELTA1 VPSS_DMDR_MERGE_DELTA1;

    VPSS_DMDR_MERGE_DELTA1.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA1.u32));
    VPSS_DMDR_MERGE_DELTA1.bits.winact_cliplimit = winact_cliplimit;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA1.u32), VPSS_DMDR_MERGE_DELTA1.u32);

    return ;
}



HI_VOID VPSS_Snr_SetAngstr1Minusfac(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 angstr1_minusfac)
{
    U_VPSS_DMDR_MERGE_DELTA2 VPSS_DMDR_MERGE_DELTA2;

    VPSS_DMDR_MERGE_DELTA2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA2.u32));
    VPSS_DMDR_MERGE_DELTA2.bits.angstr1_minusfac = angstr1_minusfac;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA2.u32), VPSS_DMDR_MERGE_DELTA2.u32);

    return ;
}


HI_VOID VPSS_Snr_SetWinactRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 winact_ratio)
{
    U_VPSS_DMDR_MERGE_DELTA2 VPSS_DMDR_MERGE_DELTA2;

    VPSS_DMDR_MERGE_DELTA2.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA2.u32));
    VPSS_DMDR_MERGE_DELTA2.bits.winact_ratio = winact_ratio;
    VPSS_RegWrite((HI_U32 *) & (pstVpssRegs->VPSS_DMDR_MERGE_DELTA2.u32), VPSS_DMDR_MERGE_DELTA2.u32);

    return ;
}
#endif
