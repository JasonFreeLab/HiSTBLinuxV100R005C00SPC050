/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_product_define.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/

#include "hdmi_platform.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "drv_hdmi_platform.h"
#include "drv_hdmi_compatibility.h"
#include "hi_drv_sys.h"
#else
#include "hi_common.h"
#endif
#include "hdmi_product_define.h"
#include "hdmi_reg_crg.h"

#define PRODUCT_NULL_CHK(p) do{\
	if(HI_NULL == p)\
	{HDMI_ERR("%s is null pointer!return fail.\n",#p);\
	return HI_FAILURE;}\
}while(0)

#define PRODUCT_NULL_CHK_NORET(p) do{\
    if(HI_NULL == p)\
    {HDMI_ERR("%s is null pointer!return fail.\n",#p);\
    return ;}\
}while(0)

/* HDMITX IO CONFIG,see Hi3798MV200T SI RFQ.xlsm */
#define HDMI_ADDR_BASE_IO_CFG       0xf8000044
/* IO Config bit24:21  func0: CEC/SCL/SDA/HPD func1:GPIO5_1/3/0/5 */
#define HDMI_IO_CFG_MASK            0x01e00000
/* cec io trim */
#define HDMI_ADDR_OTP_CECIOTRIM     0xf8ab0320  // mapping otp addr 0x323
#define HDMI_MASK_OTP_CECIOTRIM     (0xf<<24)   // SW bit27:24
#define HDMI_ADDR_CEC_IOTRIM        0xf8000104  // SC_IO_REUSE3_SEL refer to <Hi3796mv200 SYSCTRL Register>
#define HDMI_MASK_CEC_IOTRIM        (0xf<<12)   // bit15:12

#define HDMI_ADDR_CEC_TX_CTRL		0xf8ce4808
#define cec_reg_i2c_cec_passthru	18
#define cec_reg_nack_hdr			9
HI_S32 HDMITXRegWrite  (HI_U32 *pu32RegAddr, HI_U32 u32Value)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    *(volatile HI_U32*)pu32RegAddr = u32Value;
    return HI_SUCCESS;
}

HI_U32 HDMITXRegRead(HI_U32 *pu32RegAddr)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    return *(volatile HI_U32*)(pu32RegAddr);
}

HI_S32 HDMITXVerifyRegWrite(HI_U32 *pu32RegAddr, HI_U32 u32RegValue, HI_CHAR *pRegName)
{
#if 0
    HI_BOOL bWriteSuccess = HI_FALSE;

    PRODUCT_NULL_CHK(pu32RegAddr);
    bWriteSuccess = (*pu32RegAddr == u32RegValue);
    if (!bWriteSuccess)
    {
        HDMI_ERR("virsual addr=0x%p,re=0x%08x,value=0x%08x,name= %s , error!\n",  pu32RegAddr,*pu32RegAddr,u32RegValue,pRegName);
    }

    return !bWriteSuccess;
#endif
    return 0;
}

HI_S32 HDMIRegWriteU32(HI_U32 u32RegAddr, HI_U32 u32Value)
{
    volatile HI_U32 *pu32RegAddr = HI_NULL;

    pu32RegAddr = (volatile HI_U32 *)HDMI_IO_MAP(u32RegAddr,4) ;

    if (pu32RegAddr)
    {
        *pu32RegAddr = u32Value ;
        HDMI_IO_UNMAP(pu32RegAddr);
        return HI_SUCCESS;
    }
    else
    {
        HDMI_ERR("HDMI_IO_MAP addr=0x%x err!\n",u32RegAddr);
        return HI_FAILURE;
    }


}


HI_U32 HDMIRegReadU32 (HI_U32 u32RegAddr)
{
    volatile HI_U32 *pu32RegAddr = HI_NULL;
	HI_U32  u32Value = 0;

    pu32RegAddr = (volatile HI_U32 *)HDMI_IO_MAP(u32RegAddr,4);

    if (pu32RegAddr)
    {
        u32Value = *pu32RegAddr ;
        HDMI_IO_UNMAP(pu32RegAddr);
    }
    else
    {
        HDMI_ERR("HDMI_IO_MAP addr=0x%x\n err!\n",u32RegAddr);
    }

	return  u32Value;
}


//==========================================================================

HI_VOID DRV_HDMI_ProdCecHwDisable(HI_VOID)
{
    /* 20170304 Importan NOTE: when disable cec ,must set 1 in bit cec_reg_nack_hdr,
    or it will  disturb other device cec communication,such as ONKYU TX-RZ800 & Samsung UA55HU6000JXXZ;
    when enable cec ,set 0 in bit cec_reg_nack_hdr, and it must clear cec rx-fifo whenever recieve an message.*/

    HI_U32  u32TmpRegValue = 0;

    u32TmpRegValue  = HDMIRegReadU32(HDMI_ADDR_CEC_TX_CTRL);
    u32TmpRegValue |= 0x1 << cec_reg_i2c_cec_passthru;
    u32TmpRegValue |= 0x1 << cec_reg_nack_hdr;
    HDMIRegWriteU32(HDMI_ADDR_CEC_TX_CTRL, u32TmpRegValue);

    return ;
}

HI_VOID DRV_HDMI_ProdCecCpuInfoSet(HDMI_MCU_INFO_S *pstCecCpuInfo)
{
    PRODUCT_NULL_CHK_NORET(pstCecCpuInfo);

    REG_HDMI_SYSCTRL_cpu_cec_info_0_Set(pstCecCpuInfo->u32PhyAddr);
    REG_HDMI_SYSCTRL_cpu_cec_info_1_Set(pstCecCpuInfo->u32LogicAddr);
    REG_HDMI_SYSCTRL_cpu_mcu_switch_info_Set(pstCecCpuInfo->u32SwitchInfo);
    REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_0_Set(pstCecCpuInfo->u32Rsv0);
    REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_1_Set(pstCecCpuInfo->u32Rsv1);
    REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_2_Set(pstCecCpuInfo->u32Rsv2);
    REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_3_Set(pstCecCpuInfo->u32Rsv3);
    REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_4_Set(pstCecCpuInfo->u32Rsv4);

    return ;
}

HI_VOID DRV_HDMI_ProdCecCpuInfoGet(HDMI_MCU_INFO_S *pstCecCpuInfo)
{
    PRODUCT_NULL_CHK_NORET(pstCecCpuInfo);

    pstCecCpuInfo->u32PhyAddr     = REG_HDMI_SYSCTRL_cpu_cec_info_0_Get();
    pstCecCpuInfo->u32LogicAddr   = REG_HDMI_SYSCTRL_cpu_cec_info_1_Get();
    pstCecCpuInfo->u32SwitchInfo  = REG_HDMI_SYSCTRL_cpu_mcu_switch_info_Get();
    pstCecCpuInfo->u32Rsv0        = REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_0_Get();
    pstCecCpuInfo->u32Rsv1        = REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_1_Get();
    pstCecCpuInfo->u32Rsv2        = REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_2_Get();
    pstCecCpuInfo->u32Rsv3        = REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_3_Get();
    pstCecCpuInfo->u32Rsv4        = REG_HDMI_SYSCTRL_cpu_hdmitx_rsv_4_Get();

    return ;
}

HI_VOID DRV_HDMI_ProdCecMcuInfoGet(HDMI_MCU_INFO_S *pstCecMcuInfo)
{
    PRODUCT_NULL_CHK_NORET(pstCecMcuInfo);

    pstCecMcuInfo->u32PhyAddr     = REG_HDMI_SYSCTRL_mcu_cec_info_0_Get();
    pstCecMcuInfo->u32LogicAddr   = REG_HDMI_SYSCTRL_mcu_cec_info_1_Get();
    pstCecMcuInfo->u32SwitchInfo  = REG_HDMI_SYSCTRL_mcu_cpu_switch_info_Get();
    pstCecMcuInfo->u32Rsv0        = REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_0_Get();
    pstCecMcuInfo->u32Rsv1        = REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_1_Get();
    pstCecMcuInfo->u32Rsv2        = REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_2_Get();
    pstCecMcuInfo->u32Rsv3        = REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_3_Get();
    pstCecMcuInfo->u32Rsv4        = REG_HDMI_SYSCTRL_mcu_hdmitx_rsv_4_Get();

    return ;
}

HI_VOID DRV_HDMI_ProdIoCfgSet(HI_VOID)
{
#ifndef HDMI_FPGA_SUPPORT
    HI_U32  u32TmpRegValue = 0;

    u32TmpRegValue  = HDMIRegReadU32(HDMI_ADDR_BASE_IO_CFG);
    u32TmpRegValue &= ~HDMI_IO_CFG_MASK;
    HDMIRegWriteU32(HDMI_ADDR_BASE_IO_CFG, u32TmpRegValue);
#endif

    return ;
}

HI_VOID DRV_HDMI_ProdIoTrimSet(HI_VOID)
{
#ifndef HDMI_FPGA_SUPPORT
    HI_U32  u32OtpRegValue = 0;
    HI_U32  u32IOTrimValue = 0;

    u32OtpRegValue  = HDMIRegReadU32(HDMI_ADDR_OTP_CECIOTRIM);
    u32OtpRegValue &= HDMI_MASK_OTP_CECIOTRIM;

    u32IOTrimValue  = HDMIRegReadU32(HDMI_ADDR_CEC_IOTRIM);
    u32IOTrimValue &= ~HDMI_MASK_CEC_IOTRIM;

    u32IOTrimValue |= u32OtpRegValue >> 12;
    HDMIRegWriteU32(HDMI_ADDR_CEC_IOTRIM, u32IOTrimValue);
#endif
    return ;
}

HI_VOID DRV_HDMI_ProdCrgGateSet(HI_BOOL bEnable)
{
#ifndef HDMI_FPGA_SUPPORT
    /* Gate */
    REG_HDMI_SYSCTRL_hdmi_apb_cken_Set(bEnable);
    REG_HDMI_SYSCTRL_hdmi_osc_cken_Set(bEnable);
    REG_HDMI_SYSCTRL_hdmi_cec_cken_Set(bEnable);
    /* PERI_CRG67  HDMITX_CTRL CRG  0x010C   0x0000043F */
    REG_HDMI_CRG_ssc_in_cken_Set(bEnable);
    REG_HDMI_CRG_ssc_bypass_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_osc_24m_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_os_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_as_cken_Set(bEnable);
    REG_HDMI_CRG_hdmitx_pxl_cken_Set(bEnable);
    /* PERI_CRG68  HDMITX_PHY      0x0110  0x00000001 */
    REG_HDMI_CRG_phy_tmds_cken_Set(bEnable);

    /* CLK Sel */
    /* PERI_CRG67  HDMITX_CTRL CRG  0x010C   0x0000043F */
    REG_HDMI_CRG_ssc_bypass_clk_sel_Set(HI_FALSE);
#endif
    return ;
}

HI_VOID DRV_HDMI_ProdCrgAllResetSet(HI_BOOL bEnable)
{
#ifndef HDMI_FPGA_SUPPORT
    REG_HDMI_SYSCTRL_hdmi_bus_srst_req_Set(bEnable);
    REG_HDMI_SYSCTRL_hdmi_srst_req_Set(bEnable);
    REG_HDMI_SYSCTRL_hdmi_cec_srst_req_Set(bEnable);
    /* PERI_CRG67  HDMITX_CTRL CRG  0x010C   0x0000043F */
    REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ssc_srst_req_Set(bEnable);
    /* PERI_CRG68  HDMITX_PHY      0x0110  0x00000001 */
    REG_HDMI_CRG_hdmitx_phy_srst_req_Set(bEnable);
    REG_HDMI_CRG_phy_tmds_srst_req_Set(bEnable);

    bEnable = !bEnable;

    /* SC_CLKGATE_SRST_CTRL  0xf8000048 */
    REG_HDMI_SYSCTRL_hdmi_bus_srst_req_Set(bEnable);
    REG_HDMI_SYSCTRL_hdmi_srst_req_Set(bEnable);
    REG_HDMI_SYSCTRL_hdmi_cec_srst_req_Set(bEnable);
    /* PERI_CRG67  HDMITX_CTRL CRG  0x010C   0x0000043F */
    REG_HDMI_CRG_hdmitx_ctrl_bus_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ctrl_srst_req_Set(bEnable);
    REG_HDMI_CRG_hdmitx_ssc_srst_req_Set(bEnable);
    /* PERI_CRG68  HDMITX_PHY      0x0110  0x00000001 */
    REG_HDMI_CRG_hdmitx_phy_srst_req_Set(bEnable);
    REG_HDMI_CRG_phy_tmds_srst_req_Set(bEnable);
#endif
    return ;
}

HI_VOID DRV_HDMI_ProdCrgPhyResetSet(HI_BOOL bEnable)
{
#ifndef HDMI_FPGA_SUPPORT
    /* PERI_CRG68  HDMITX_PHY      0x0110  0x00000001 */
    REG_HDMI_CRG_hdmitx_phy_srst_req_Set(bEnable);
    REG_HDMI_CRG_phy_tmds_srst_req_Set(bEnable);

    bEnable = !bEnable;

    /* PERI_CRG68  HDMITX_PHY      0x0110  0x00000001 */
    REG_HDMI_CRG_hdmitx_phy_srst_req_Set(bEnable);
    REG_HDMI_CRG_phy_tmds_srst_req_Set(bEnable);
#endif
    return ;
}

HI_VOID DRV_HDMI_ProdCrgPhyResetGet(HI_BOOL *pbEnable)
{
#ifndef HDMI_FPGA_SUPPORT
    PRODUCT_NULL_CHK_NORET(pbEnable);

    /* PERI_CRG68  HDMITX_PHY      0x0110  0x00000001 */
    if(REG_HDMI_CRG_hdmitx_phy_srst_req_Get() \
        || REG_HDMI_CRG_phy_tmds_srst_req_Get() )
    {
        *pbEnable = HI_TRUE;
    }
    else
    {
        *pbEnable = HI_FALSE;
    }

#endif
    return ;
}

HI_VOID DRV_HDMI_ProdCrgDivSet(HDMI_CRG_CFG_S *pstCrgCfg)
{
#ifndef HDMI_FPGA_SUPPORT
    HI_U32 u32Tmp   = 0;

#ifndef HDMI_BUILD_IN_BOOT
    HI_U32 u32CrgDivMs  = 1;
    HI_U32 u32PhySrstMs = 1;
#endif

    if(pstCrgCfg)
    {
        u32Tmp      = pstCrgCfg->u32SscBypassDiv - 1;
        REG_HDMI_CRG_ssc_clk_div_Set(u32Tmp);
        u32Tmp      = pstCrgCfg->u32TmdsClkDiv - 1;
        REG_HDMI_CRG_tmds_clk_div_Set(u32Tmp);

#ifndef HDMI_BUILD_IN_BOOT
        DRV_HDMI_CompatCrgMsGet(HDMI_DEVICE_ID0, &u32CrgDivMs, &u32PhySrstMs);
        msleep(u32CrgDivMs);
#endif
    /* 96mv2 phyreset changed compare with 98mv2 */

    }
#endif

    return ;
}

HDMI_CHIP_TYPE_E DRV_HDMI_ProdChipGet(HI_VOID)
{
    static HDMI_CHIP_TYPE_E enHdmiChip = 0;
    HI_CHIP_TYPE_E      enChipType  = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E   enChipVersion = HI_CHIP_VERSION_BUTT;


    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

    if (HI_CHIP_TYPE_HI3798C == enChipType && HI_CHIP_VERSION_V200 == enChipVersion)
    {
        enHdmiChip = HDMI_CHIP_HI3798CV200;
    }
    else if(HI_CHIP_TYPE_HI3798M_A == enChipType && HI_CHIP_VERSION_V200 == enChipVersion)
    {
        enHdmiChip = HDMI_CHIP_HI3798MV200_A;
    }
    else if(HI_CHIP_TYPE_HI3798M == enChipType && HI_CHIP_VERSION_V200 == enChipVersion)
    {
        enHdmiChip = HDMI_CHIP_HI3798MV200;
    }
    else if (HI_CHIP_TYPE_HI3796M == enChipType && HI_CHIP_VERSION_V200 == enChipVersion)
    {
        enHdmiChip =  HDMI_CHIP_HI3796MV200;
    }

    else if(HI_CHIP_TYPE_HI3798M == enChipType && HI_CHIP_VERSION_V300 == enChipVersion)
    {
       enHdmiChip = HDMI_CHIP_HI3798MV300;
    }

    return enHdmiChip;


}

HI_VOID DRV_HDMI_ProdCrgInit(HI_VOID)
{
    DRV_HDMI_ProdIoCfgSet();
    DRV_HDMI_ProdCrgGateSet(HI_TRUE);
    DRV_HDMI_ProdCrgAllResetSet(HI_TRUE);
    DRV_HDMI_ProdCecHwDisable();

    return ;
}




