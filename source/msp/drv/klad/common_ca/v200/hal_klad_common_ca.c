/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_common_ca.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hal_klad.h"
#include "hal_klad_common_ca_reg.h"
#include "hal_klad_common_ca.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


HI_VOID HAL_KLAD_COMMON_CA_CSA2Start(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd)
{
    KL_C5_CSA2_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.c5_csa2_calc_start   = 0x1;
    ctrl.bits.c5_csa2_level_sel    = level & 0xf;
    ctrl.bits.c5_csa2_tdes_aes_sel = alg & 0x1;
    ctrl.bits.c5_csa2_key_addr     = ((addr & 0x7F) << 1) + (odd & 0x1);
    HAL_KLAD_WriteReg(KL_C5_CSA2_KLAD_CTRL, ctrl.u32);

    return;
}

HI_U8 HAL_KLAD_COMMON_CA_CSA2GetLevel(HI_VOID)
{
    HI_U32 value = 0;
    HI_U32 level[] = {2, 3};
    KL_C5_OTP_LV_SEL_U lv_sel;

    value = HAL_KLAD_ReadOtpShadowReg(KL_C5_OTP_LV_SEL);
    lv_sel.u8 = value & 0xff;

    return level[lv_sel.bits.cm0_csa2_lv_sel];
}

HI_VOID HAL_KLAD_COMMON_CA_CSA3Start(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd)
{
    KL_C5_CSA3_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.c5_csa3_calc_start   = 0x1;
    ctrl.bits.c5_csa3_level_sel    = level & 0xf;
    ctrl.bits.c5_csa3_tdes_aes_sel = alg & 0x1;
    ctrl.bits.c5_csa3_key_addr     = ((addr & 0x7F) << 1) + (odd & 0x1);
    HAL_KLAD_WriteReg(KL_C5_CSA3_KLAD_CTRL, ctrl.u32);

    return;
}

HI_U8 HAL_KLAD_COMMON_CA_CSA3GetLevel(HI_VOID)
{
    HI_U32 value = 0;
    HI_U32 level[] = {2, 3};
    KL_C5_OTP_LV_SEL_U lv_sel;

    value = HAL_KLAD_ReadOtpShadowReg(KL_C5_OTP_LV_SEL);
    lv_sel.u8 = value & 0xff;

    return level[lv_sel.bits.cm0_csa3_lv_sel];
}

HI_VOID HAL_KLAD_COMMON_CA_SPStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target)
{
    KL_C5_SP_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.c5_sp_calc_start   = 0x1;
    ctrl.bits.c5_sp_level_sel    = level & 0xf;
    ctrl.bits.c5_sp_tdes_aes_sel = alg & 0x1;
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    if (0x01 == (target & 0x3))
    {
        ctrl.bits.c5_sp_key_addr   = addr;
    }
    else
    {
        ctrl.bits.c5_sp_key_addr   = ((addr & 0x7F) << 1) + (odd & 0x1);
        ctrl.bits.c5_sp_dsc_mode   = engine;
    }
#else
    ctrl.bits.c5_sp_key_addr       = ((addr & 0x7F) << 1) + (odd & 0x1);
#endif
    ctrl.bits.c5_sp_port_sel       = target & 0x3;
    HAL_KLAD_WriteReg(KL_C5_SP_KLAD_CTRL, ctrl.u32);

    return;
}

HI_U8 HAL_KLAD_COMMON_CA_SPGetLevel(HI_VOID)
{
    HI_U32 value = 0;
    HI_U32 level[] = {2, 3, 4, 5};
    KL_C5_OTP_LV_SEL_U lv_sel;

    value = HAL_KLAD_ReadOtpShadowReg(KL_C5_OTP_LV_SEL);
    lv_sel.u8 = value & 0xff;

    return level[lv_sel.bits.cm0_sp_lv_sel];
}

HI_VOID HAL_KLAD_COMMON_CA_R2RStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target)
{
    KL_C5_R2R_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.c5_r2r_calc_start   = 0x1;
    ctrl.bits.c5_r2r_level_sel    = level & 0xf;
    ctrl.bits.c5_r2r_tdes_aes_sel = alg & 0x1;
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    if (0x01 == (target & 0x3))
    {
        ctrl.bits.c5_r2r_key_addr   = addr;
    }
    else
    {
        ctrl.bits.c5_r2r_key_addr   = ((addr & 0x7F) << 1) + (odd & 0x1);
        ctrl.bits.c5_r2r_dsc_mode   = engine;
    }
#else
    ctrl.bits.c5_r2r_key_addr       = ((addr & 0x7F) << 1) + (odd & 0x1);
#endif
    ctrl.bits.c5_r2r_port_sel       = target & 0x3;
    HAL_KLAD_WriteReg(KL_C5_R2R_KLAD_CTRL, ctrl.u32);

    return;
}

HI_U8 HAL_KLAD_COMMON_CA_R2RGetLevel(HI_VOID)
{
    HI_U32 value = 0;
    HI_U32 level[] = {2, 3};
    KL_C5_OTP_LV_SEL_U lv_sel;

    value = HAL_KLAD_ReadOtpShadowReg(KL_C5_OTP_LV_SEL);
    lv_sel.u8 = value & 0xff;

    return level[lv_sel.bits.cm0_r2r_lv_sel];
}

HI_VOID HAL_KLAD_COMMON_CA_MISCStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target)
{
    KL_C5_MISC_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.c5_misc_calc_start   = 0x1;
    ctrl.bits.c5_misc_level_sel    = level & 0xf;
    ctrl.bits.c5_misc_tdes_aes_sel = alg & 0x1;
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    if (0x01 == (target & 0x3))
    {
        ctrl.bits.c5_misc_key_addr   = addr;
    }
    else
    {
        ctrl.bits.c5_misc_key_addr   = ((addr & 0x7F) << 1) + (odd & 0x1);
        ctrl.bits.c5_misc_dsc_mode   = engine;
    }
#else
    ctrl.bits.c5_misc_key_addr       = ((addr & 0x7F) << 1) + (odd & 0x1);
#endif
    ctrl.bits.c5_misc_port_sel       = target & 0x3;
    HAL_KLAD_WriteReg(KL_C5_MISC_KLAD_CTRL, ctrl.u32);

    return;
}

HI_U8 HAL_KLAD_COMMON_CA_MISCGetLevel(HI_VOID)
{
    HI_U32 value = 0;
    HI_U32 level[] = {2, 3, 4, 5};
    KL_C5_OTP_LV_SEL_U lv_sel;

    value = HAL_KLAD_ReadOtpShadowReg(KL_C5_OTP_LV_SEL);
    lv_sel.u8 = value & 0xff;

    return level[lv_sel.bits.cm0_misc_lv_sel];
}

HI_U32 HAL_KLAD_COMMON_CA_GetState(HI_VOID)
{
    KL_C5_KLAD_STATE_U state;

    state.u32 = HAL_KLAD_ReadReg(KL_C5_KLAD_STATE);

    return state.u32;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
