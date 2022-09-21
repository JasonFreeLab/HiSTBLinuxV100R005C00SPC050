// ****************************************************************************** 
// Copyright     :  Copyright (C) 2016, Hisilicon Technologies Co. Ltd.
// File name     :  hdmi_reg_crg.c
// Project line  :  Platform And Key Technologies Development
// Department    :  CAD Development Department
// Author        :  xxx
// Version       :  1
// Date          :  2016/7/18
// Description   :  The description of xxx project
// Others        :   
// History       :  xxx 2016/07/18 10:40:30 Create file
// ******************************************************************************

#include "hi_type.h"
#include "hdmi_reg_crg.h"
#include "hdmi_product_define.h"
#include "hdmi_platform.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "drv_hdmi_platform.h"
#endif


#define  HDMI_ADDR_CRG  0xf8a22000
#define  HDMI_ADDR_CLKGATESRST  0xf8000048
#define  HDMI_ADDR_SYSCTRL      0xf8000210

/* Define the struct pointor of the module hdmi2tx_dphy_reg */
volatile HDMI_REG_CRG_S *s_pstRegCrg = NULL;
volatile HDMI_SC_CLKGATE_SRST_CTRL *s_pstRegClkGateSrst = NULL;
volatile HDMI_REG_SYSCTRL_S *s_pstRegSysCtrl = NULL;

static int REG_HDMI_SYSCTRL_reg_Init(void);
static int REG_HDMI_SYSCTRL_reg_DeInit(void);

int REG_HDMI_CRG_reg_Init(void)
{
    if (NULL != s_pstRegCrg)
    {
        return HI_SUCCESS;
    }
    
    s_pstRegCrg  = (HDMI_REG_CRG_S*)HDMI_IO_MAP(HDMI_ADDR_CRG, sizeof(HDMI_REG_CRG_S));

    if(NULL == s_pstRegCrg)
    {
        HDMI_ERR("ioremap_nocache gophdmi2tx_crg_regAllReg failed!!!!!!!\n");
        return HI_FAILURE;
    }

    if( HDMI_CHIP_HI3798MV300 == DRV_HDMI_ProdChipGet() )
    {
        REG_HDMI_SYSCTRL_reg_Init();
    }

    return HI_SUCCESS;
}

int REG_HDMI_CRG_reg_DeInit(void)
{
    if(HI_NULL != s_pstRegCrg)
    {
        HDMI_IO_UNMAP(s_pstRegCrg);    
        s_pstRegCrg = HI_NULL;
    }

    if( HDMI_CHIP_HI3798MV300 == DRV_HDMI_ProdChipGet() )
    {
        REG_HDMI_SYSCTRL_reg_DeInit();
    }

    return HI_SUCCESS;

}

int REG_HDMI_CRG_hpll_frac_Set(unsigned int uhpll_frac)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL10 o_peri_crg_pll10;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL10.u32);

    o_peri_crg_pll10.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg_pll10.bits.hpll_frac = uhpll_frac;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg_pll10.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_frac_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL10 o_peri_crg_pll10;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL10.u32);
    o_peri_crg_pll10.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg_pll10.bits.hpll_frac;
}

int REG_HDMI_CRG_hpll_postdiv1_Set(unsigned int uhpll_postdiv1)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL10 o_peri_crg_pll10;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL10.u32);

    o_peri_crg_pll10.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg_pll10.bits.hpll_postdiv1 = uhpll_postdiv1;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg_pll10.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_postdiv1_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL10 o_peri_crg_pll10;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL10.u32);
    o_peri_crg_pll10.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg_pll10.bits.hpll_postdiv1;
}


int REG_HDMI_CRG_hpll_postdiv2_Set(unsigned int uhpll_postdiv2)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL10 o_peri_crg_pll10;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL10.u32);

    o_peri_crg_pll10.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg_pll10.bits.hpll_postdiv2 = uhpll_postdiv2;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg_pll10.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_postdiv2_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL10 o_peri_crg_pll10;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL10.u32);
    o_peri_crg_pll10.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg_pll10.bits.hpll_postdiv2;
}

int REG_HDMI_CRG_hpll_fbdiv_Set(unsigned int uhpll_fbdiv)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_fbdiv = uhpll_fbdiv;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_fbdiv_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_fbdiv;
}

int REG_HDMI_CRG_hpll_refdiv_Set(unsigned int uhpll_refdiv)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_refdiv = uhpll_refdiv;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_refdiv_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_refdiv;
}

int REG_HDMI_CRG_hpll_pd_Set(unsigned int uhpll_pd)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_pd = uhpll_pd;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_pd_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_pd;
}


int REG_HDMI_CRG_hpll_foutvcopd_Set(unsigned int uhpll_foutvcopd)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_foutvcopd = uhpll_foutvcopd;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_foutvcopd_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_foutvcopd;
}


int REG_HDMI_CRG_hpll_fout4phasepdPLL_Set(unsigned int uhpll_fout4phasepdPLL)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_fout4phasepdPLL = uhpll_fout4phasepdPLL;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_fout4phasepdPLL_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_fout4phasepdPLL;
}


int REG_HDMI_CRG_hpll_foutpostdivpd_Set(unsigned int uhpll_foutpostdivpd)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_foutpostdivpd = uhpll_foutpostdivpd;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_foutpostdivpd_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_foutpostdivpd;
}


int REG_HDMI_CRG_hpll_dacpd_Set(unsigned int uhpll_dacpd)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_dacpd = uhpll_dacpd;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_dacpd_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_dacpd;
}


int REG_HDMI_CRG_hpll_dsmpd_Set(unsigned int uhpll_dsmpd)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_dsmpd = uhpll_dsmpd;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_dsmpd_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_dsmpd;
}


int REG_HDMI_CRG_hpll_bypass_Set(unsigned int uhpll_bypass)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);

    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crgpll11.bits.hpll_bypass = uhpll_bypass;
    HDMITXRegWrite(pu32RegAddr, o_peri_crgpll11.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hpll_bypass_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG_PLL11 o_peri_crgpll11;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG_PLL11.u32);
    o_peri_crgpll11.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crgpll11.bits.hpll_bypass;
}

int REG_HDMI_CRG_vo_bus_cken_Set(unsigned int uvo_bus_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_bus_cken = uvo_bus_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_bus_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_bus_cken;
}

int REG_HDMI_CRG_vo_sd_cken_Set(unsigned int uvo_sd_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_sd_cken = uvo_sd_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_sd_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_sd_cken;
}

int REG_HDMI_CRG_vo_sdate_cken_Set(unsigned int uvo_sdate_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_sdate_cken = uvo_sdate_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_sdate_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_sdate_cken;
}

int REG_HDMI_CRG_vo_hd_cken_Set(unsigned int uvo_hd_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_hd_cken = uvo_hd_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_hd_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_hd_cken;
}

int REG_HDMI_CRG_vdac_ch0_cken_Set(unsigned int uvdac_ch0_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vdac_ch0_cken = uvdac_ch0_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vdac_ch0_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vdac_ch0_cken;
}

int REG_HDMI_CRG_vo_sd_clk_sel_Set(unsigned int uvo_sd_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_sd_clk_sel = uvo_sd_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_sd_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_sd_clk_sel;
}

int REG_HDMI_CRG_vo_sd_clk_div_Set(unsigned int uvo_sd_clk_div)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_sd_clk_div = uvo_sd_clk_div;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_sd_clk_div_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_sd_clk_div;
}

int REG_HDMI_CRG_vo_hd_clk_sel_Set(unsigned int uvo_hd_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_hd_clk_sel = uvo_hd_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_hd_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_hd_clk_sel;
}

int REG_HDMI_CRG_vo_hd_clk_div_Set(unsigned int uvo_hd_clk_div)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_hd_clk_div = uvo_hd_clk_div;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_hd_clk_div_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_hd_clk_div;
}

int REG_HDMI_CRG_vdac_ch0_clk_sel_Set(unsigned int uvdac_ch0_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vdac_ch0_clk_sel = uvdac_ch0_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vdac_ch0_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vdac_ch0_clk_sel;
}

int REG_HDMI_CRG_hdmi_clk_sel_Set(unsigned int uhdmi_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.hdmi_clk_sel = uhdmi_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmi_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.hdmi_clk_sel;
}

int REG_HDMI_CRG_vo_sd_hdmi_clk_sel_Set(unsigned int uvo_sd_hdmi_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_sd_hdmi_clk_sel = uvo_sd_hdmi_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_sd_hdmi_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_sd_hdmi_clk_sel;
}

int REG_HDMI_CRG_vdp_clk_sel_Set(unsigned int uvdp_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vdp_clk_sel = uvdp_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vdp_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vdp_clk_sel;
}

int REG_HDMI_CRG_vo_hd_hdmi_clk_sel_Set(unsigned int uvo_hd_hdmi_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.vo_hd_hdmi_clk_sel = uvo_hd_hdmi_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_vo_hd_hdmi_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.vo_hd_hdmi_clk_sel;
}

int REG_HDMI_CRG_voR_srst_req_Set(unsigned int uvoR_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);

    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg54.bits.voR_srst_req = uvoR_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg54.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_voR_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG54 o_peri_crg54;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG54.u32);
    o_peri_crg54.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg54.bits.voR_srst_req;
}


int REG_HDMI_CRG_ssc_in_cken_Set(unsigned int ussc_in_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.ssc_in_cken = ussc_in_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_ssc_in_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.ssc_in_cken;
}

int REG_HDMI_CRG_ssc_bypass_cken_Set(unsigned int ussc_bypass_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.ssc_bypass_cken = ussc_bypass_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_ssc_bypass_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.ssc_bypass_cken;
}

int REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Set(unsigned int uhdmitx_ctrl_osc_24m_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_osc_24m_cken = uhdmitx_ctrl_osc_24m_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_osc_24m_cken;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_cken_Set(unsigned int uhdmitx_ctrl_cec_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_cec_cken = uhdmitx_ctrl_cec_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_cec_cken;
}

int REG_HDMI_CRG_hdmitx_ctrl_os_cken_Set(unsigned int uhdmitx_ctrl_os_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_os_cken = uhdmitx_ctrl_os_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_os_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_os_cken;
}

int REG_HDMI_CRG_hdmitx_ctrl_as_cken_Set(unsigned int uhdmitx_ctrl_as_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_as_cken = uhdmitx_ctrl_as_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_as_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_as_cken;
}

int REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(unsigned int uhdmitx_ctrl_bus_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_bus_srst_req = uhdmitx_ctrl_bus_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_bus_srst_req;
}

int REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(unsigned int uhdmitx_ctrl_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_srst_req = uhdmitx_ctrl_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_srst_req;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Set(unsigned int uhdmitx_ctrl_cec_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_cec_srst_req = uhdmitx_ctrl_cec_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_cec_srst_req;
}

int REG_HDMI_CRG_hdmitx_ssc_srst_req_Set(unsigned int uhdmitx_ssc_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ssc_srst_req = uhdmitx_ssc_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ssc_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ssc_srst_req;
}

int REG_HDMI_CRG_ssc_clk_div_Set(unsigned int ussc_clk_div)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.ssc_clk_div = ussc_clk_div;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_ssc_clk_div_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.ssc_clk_div;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_clk_sel_Set(unsigned int uhdmitx_ctrl_cec_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_ctrl_cec_clk_sel = uhdmitx_ctrl_cec_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_ctrl_cec_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_ctrl_cec_clk_sel;
}

int REG_HDMI_CRG_hdmitx_pxl_cken_Set(unsigned int uhdmitx_pxl_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.hdmitx_pxl_cken = uhdmitx_pxl_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_pxl_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.hdmitx_pxl_cken;
}

int REG_HDMI_CRG_ssc_bypass_clk_sel_Set(unsigned int ussc_bypass_clk_sel)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);

    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg67.bits.ssc_bypass_clk_sel = ussc_bypass_clk_sel;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg67.u32);

    return HI_SUCCESS;
}

int REG_HDMI_CRG_ssc_bypass_clk_sel_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG67 o_peri_crg67;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG67.u32);
    o_peri_crg67.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg67.bits.ssc_bypass_clk_sel;
}

int REG_HDMI_CRG_phy_tmds_cken_Set(unsigned int uphy_tmds_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.phy_tmds_cken = uphy_tmds_cken;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_phy_tmds_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);
    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg68.bits.phy_tmds_cken;
}

int REG_HDMI_CRG_hdmitx_phy_srst_req_Set(unsigned int uhdmitx_phy_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.hdmitx_phy_srst_req = uhdmitx_phy_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_hdmitx_phy_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);
    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg68.bits.hdmitx_phy_srst_req;
}

int REG_HDMI_CRG_phy_tmds_srst_req_Set(unsigned int uphy_tmds_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.phy_tmds_srst_req = uphy_tmds_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_phy_tmds_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);
    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg68.bits.phy_tmds_srst_req;
}

int REG_HDMI_CRG_tmds_clk_div_Set(unsigned int utmds_clk_div)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);

    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    o_peri_crg68.bits.tmds_clk_div = utmds_clk_div;
    HDMITXRegWrite(pu32RegAddr, o_peri_crg68.u32);
    
    return HI_SUCCESS;
}

int REG_HDMI_CRG_tmds_clk_div_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    R_PERI_CRG68 o_peri_crg68;

    pu32RegAddr = (HI_U32*)&(s_pstRegCrg->PERI_CRG68.u32);
    o_peri_crg68.u32 = HDMITXRegRead(pu32RegAddr);
    return o_peri_crg68.bits.tmds_clk_div;
}

static int REG_HDMI_SYSCTRL_reg_Init(void)
{
    if ( (NULL != s_pstRegClkGateSrst) && (NULL != s_pstRegSysCtrl) )
    {
        return HI_SUCCESS;
    }
    s_pstRegClkGateSrst = (HDMI_SC_CLKGATE_SRST_CTRL *)HDMI_IO_MAP(HDMI_ADDR_CLKGATESRST, sizeof(HDMI_SC_CLKGATE_SRST_CTRL));
    s_pstRegSysCtrl     = (HDMI_REG_SYSCTRL_S *)HDMI_IO_MAP(HDMI_ADDR_SYSCTRL, sizeof(HDMI_REG_SYSCTRL_S));
    if (NULL == s_pstRegClkGateSrst)
    {
        HDMI_ERR("SysCtrl ClkGateSrstReg!\n");
        return HI_FAILURE;
    }
    if (NULL == s_pstRegSysCtrl)
    {
        HDMI_ERR("SysCtrl CEC_MCUInfoReg!\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

static int REG_HDMI_SYSCTRL_reg_DeInit(void)
{
    if (HI_NULL != s_pstRegClkGateSrst)
    {
        HDMI_IO_UNMAP(s_pstRegClkGateSrst);
        s_pstRegClkGateSrst = HI_NULL;
    }
    if (HI_NULL != s_pstRegSysCtrl)
    {
        HDMI_IO_UNMAP(s_pstRegSysCtrl);
        s_pstRegSysCtrl     = HI_NULL;
    }
    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_hdmi_cec_cken_Set(unsigned int uhdmi_cec_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);

    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_cec_cken = uhdmi_cec_cken;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_sc_clkgate_srst_ctrl.u32);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_hdmi_cec_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);
    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_cec_cken;
}

int REG_HDMI_SYSCTRL_hdmi_cec_srst_req_Set(unsigned int uhdmi_cec_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);

    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_cec_srst_req = uhdmi_cec_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_sc_clkgate_srst_ctrl.u32);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_hdmi_cec_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);
    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_cec_srst_req;
}

int REG_HDMI_SYSCTRL_hdmi_osc_cken_Set(unsigned int uhdmi_osc_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);

    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_osc_cken = uhdmi_osc_cken;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_sc_clkgate_srst_ctrl.u32);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_hdmi_osc_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);
    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_osc_cken;
}

int REG_HDMI_SYSCTRL_hdmi_apb_cken_Set(unsigned int uhdmi_apb_cken)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);

    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_apb_cken = uhdmi_apb_cken;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_sc_clkgate_srst_ctrl.u32);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_hdmi_apb_cken_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);
    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_apb_cken;
}

int REG_HDMI_SYSCTRL_hdmi_bus_srst_req_Set(unsigned int uhdmi_bus_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);

    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_bus_srst_req = uhdmi_bus_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_sc_clkgate_srst_ctrl.u32);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_hdmi_bus_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);
    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_bus_srst_req;
}

int REG_HDMI_SYSCTRL_hdmi_srst_req_Set(unsigned int uhdmi_srst_req)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);

    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_srst_req = uhdmi_srst_req;
    HDMITXRegWrite(pu32RegAddr, o_hdmi_sc_clkgate_srst_ctrl.u32);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_hdmi_srst_req_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;
    HDMI_SC_CLKGATE_SRST_CTRL o_hdmi_sc_clkgate_srst_ctrl;

    pu32RegAddr = (HI_U32*)&(s_pstRegClkGateSrst->u32);
    o_hdmi_sc_clkgate_srst_ctrl.u32 = HDMITXRegRead(pu32RegAddr);
    return o_hdmi_sc_clkgate_srst_ctrl.bits.hdmi_srst_req;
}

int REG_HDMI_SYSCTRL_cpu_cec_info_0_Set(unsigned int ucpu_cec_info_0)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_CEC_INFO_0);
    HDMITXRegWrite(pu32RegAddr, ucpu_cec_info_0);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_cec_info_0_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_CEC_INFO_0);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_cpu_cec_info_1_Set(unsigned int ucpu_cec_info_1)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_CEC_INFO_1);
    HDMITXRegWrite(pu32RegAddr, ucpu_cec_info_1);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_cec_info_1_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_CEC_INFO_1);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_cpu_mcu_switch_info_Set(unsigned int ucpu_mcu_switch_info)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_MCU_SWITCH_INFO);
    HDMITXRegWrite(pu32RegAddr, ucpu_mcu_switch_info);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_mcu_switch_info_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_MCU_SWITCH_INFO);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_0_Set(unsigned int ucpu_hdmitx_rsv_0)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_0);
    HDMITXRegWrite(pu32RegAddr, ucpu_hdmitx_rsv_0);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_0_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_0);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_1_Set(unsigned int ucpu_hdmitx_rsv_1)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_1);
    HDMITXRegWrite(pu32RegAddr, ucpu_hdmitx_rsv_1);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_1_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_1);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_2_Set(unsigned int ucpu_hdmitx_rsv_2)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_2);
    HDMITXRegWrite(pu32RegAddr, ucpu_hdmitx_rsv_2);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_2_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_2);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_3_Set(unsigned int ucpu_hdmitx_rsv_3)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_3);
    HDMITXRegWrite(pu32RegAddr, ucpu_hdmitx_rsv_3);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_3_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_3);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_4_Set(unsigned int ucpu_hdmitx_rsv_4)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_4);
    HDMITXRegWrite(pu32RegAddr, ucpu_hdmitx_rsv_4);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_4_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->CPU_HDMITX_RESERVED_4);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_cec_info_0_Set(unsigned int umcu_cec_info_0)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_CEC_INFO_0);
    HDMITXRegWrite(pu32RegAddr, umcu_cec_info_0);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_cec_info_0_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_CEC_INFO_0);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_cec_info_1_Set(unsigned int umcu_cec_info_1)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_CEC_INFO_1);
    HDMITXRegWrite(pu32RegAddr, umcu_cec_info_1);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_cec_info_1_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_CEC_INFO_1);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_cpu_switch_info_Set(unsigned int umcu_cpu_switch_info)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_CPU_SWITCH_INFO);
    HDMITXRegWrite(pu32RegAddr, umcu_cpu_switch_info);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_cpu_switch_info_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_CPU_SWITCH_INFO);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_0_Set(unsigned int umcu_hdmitx_rsv_0)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_0);
    HDMITXRegWrite(pu32RegAddr, umcu_hdmitx_rsv_0);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_0_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_0);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_1_Set(unsigned int umcu_hdmitx_rsv_1)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_1);
    HDMITXRegWrite(pu32RegAddr, umcu_hdmitx_rsv_1);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_1_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_1);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_2_Set(unsigned int umcu_hdmitx_rsv_2)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_2);
    HDMITXRegWrite(pu32RegAddr, umcu_hdmitx_rsv_2);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_2_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_2);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_3_Set(unsigned int umcu_hdmitx_rsv_3)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_3);
    HDMITXRegWrite(pu32RegAddr, umcu_hdmitx_rsv_3);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_3_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_3);

    return HDMITXRegRead(pu32RegAddr);
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_4_Set(unsigned int umcu_hdmitx_rsv_4)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_4);
    HDMITXRegWrite(pu32RegAddr, umcu_hdmitx_rsv_4);

    return HI_SUCCESS;
}

int REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_4_Get(HI_VOID)
{
    HI_U32 *pu32RegAddr = NULL;

    pu32RegAddr = (HI_U32*)&(s_pstRegSysCtrl->MCU_HDMITX_RESERVED_4);

    return HDMITXRegRead(pu32RegAddr);
}

