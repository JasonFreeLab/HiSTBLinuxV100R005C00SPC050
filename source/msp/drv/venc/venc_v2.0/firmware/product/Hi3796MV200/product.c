#include "venc_hal_ext.h"
#include "hi_reg_common.h"
#include "drv_venc_osal.h"

enum
{
    VENC_CLK_SEL_250 = 0,
    VENC_CLK_SEL_24 = 1
};

static VOID DRV_VENC_PDT_OpenHardware(VOID)
{
    U_PERI_CRG35 unTmpValue;
#ifdef HI_SMMU_SUPPORT
    U_PERI_CRG203 unTmpSmmuCfg;

    /*if support SMMU should open the smmu clock*/
    unTmpSmmuCfg.bits.venc_smmu_cken      = 1;
    g_pstRegCrg->PERI_CRG203.u32 = unTmpSmmuCfg.u32;
#endif

    memset(&unTmpValue,0,sizeof(U_PERI_CRG35));
    /* reset */
    g_pstRegCrg->PERI_CRG35.u32 = unTmpValue.u32;

    /* open vedu clock */
    unTmpValue.bits.venc_core_cken = 1;
    unTmpValue.bits.venc_axi_cken  = 1;
    unTmpValue.bits.venc_clk_sel  = VENC_CLK_SEL_250;
    g_pstRegCrg->PERI_CRG35.u32 = unTmpValue.u32;
}

static VOID DRV_VENC_PDT_CloseHardware(VOID)
{
    U_PERI_CRG35 unTmpValue;
#ifdef HI_SMMU_SUPPORT
    U_PERI_CRG203 unTmpSmmuCfg;
    unTmpSmmuCfg.bits.venc_smmu_cken      = 0;
    g_pstRegCrg->PERI_CRG203.u32 = unTmpSmmuCfg.u32;
#endif

    /* close vedu clock */
    unTmpValue.bits.venc_core_cken = 0;
    unTmpValue.bits.venc_axi_cken  = 0;
    g_pstRegCrg->PERI_CRG35.u32 = unTmpValue.u32;
}

static VOID DRV_VENC_PDT_ResetHardware(VOID)
{
    U_PERI_CRG35 unTmpValue;
#ifdef HI_SMMU_SUPPORT
    U_PERI_CRG203 unTmpSmmuCfg;
    unTmpSmmuCfg.u32 = g_pstRegCrg->PERI_CRG203.u32;

    unTmpSmmuCfg.bits.venc_smmu_srst_req  = 1;
    g_pstRegCrg->PERI_CRG203.u32 = unTmpSmmuCfg.u32;
    udelay(5);

    unTmpSmmuCfg.bits.venc_smmu_srst_req  = 0;
    g_pstRegCrg->PERI_CRG203.u32 = unTmpSmmuCfg.u32;

    udelay(10);
#endif
    unTmpValue.u32 = g_pstRegCrg->PERI_CRG35.u32;

    unTmpValue.bits.venc_srst_req = 1;
    g_pstRegCrg->PERI_CRG35.u32 = unTmpValue.u32;
    udelay(5);

    unTmpValue.bits.venc_srst_req = 0;
    g_pstRegCrg->PERI_CRG35.u32 = unTmpValue.u32;
    udelay(10);
}

static VOID DRV_VENC_PDT_InitHalInterface(VOID)
{
    g_venc_hal_fun_ptr.pfun_HAL_ClearInt      = DRV_VENC_HAL_V500R001_ClrInt;
    g_venc_hal_fun_ptr.pfun_HAL_DisableInt    = DRV_VENC_HAL_V500R001_DisableInt;
    g_venc_hal_fun_ptr.pfun_HAL_ReadReg       = DRV_VENC_HAL_V500R001_ReadReg;
    g_venc_hal_fun_ptr.pfun_HAL_ReadSmmuReg   = DRV_VENC_HAL_V500R001_ReadReg_Smmu;
    g_venc_hal_fun_ptr.pfun_HAL_CfgReg        = DRV_VENC_HAL_V500R001_CfgReg;

    g_venc_hal_fun_ptr.pfun_HAL_Init          = DRV_VENC_HAL_V500R001_Init;
    g_venc_hal_fun_ptr.pfun_HAL_Deinit        = DRV_VENC_HAL_V500R001_Deinit;

    g_venc_hal_fun_ptr.pfun_HAL_OpenHardware  = DRV_VENC_PDT_OpenHardware;
    g_venc_hal_fun_ptr.pfun_HAL_CloseHardware = DRV_VENC_PDT_CloseHardware;
    g_venc_hal_fun_ptr.pfun_HAL_ResetHardware = DRV_VENC_PDT_ResetHardware;
}

//VOID PDT_InitRcInterface()
//{

//}


SINT32 DRV_VENC_PDT_V500R001_Init(VOID)
{
    DRV_VENC_PDT_InitHalInterface();

    //PDT_InitRcInterface();

    return 0;
}



