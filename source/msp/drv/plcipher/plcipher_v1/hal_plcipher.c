/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_plcipher.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#include <linux/jiffies.h>
#include <asm/barrier.h>    /* mb() */
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_common.h"
#include "hi_error_mpi.h"
#include "drv_plcipher_ioctl.h"
#include "drv_plcipher_reg.h"
#include "hal_plcipher.h"
#include "drv_advca_ext.h"
#include "hi_drv_mmz.h"
#include "hi_drv_plcipher.h"
#include "hi_drv_reg.h"
#include "hi_reg_common.h"
#include "hi_drv_module.h"


/***************************** Macro Definition ******************************/
/*process of bit*/
#define HAL_SET_BIT(src, bit)        ((src) |= (1<<bit))
#define HAL_CLEAR_BIT(src,bit)       ((src) &= ~(1<<bit))



/******************************* API declaration *****************************/
HI_VOID HAL_PLCIPHER_ReadReg(HI_U32* addr, HI_U32 *pu32Val)
{
    HI_REG_READ32(addr, *pu32Val);
    return;
}

HI_VOID HAL_PLCIPHER_WriteReg(HI_U32* addr, HI_U32 u32Val)
{
    HI_REG_WRITE32(addr, u32Val);
    return;
}

HI_VOID HAL_PLCIPHER_GetDescReadPtr(HI_U32* pInDescReadPrt,HI_U32* pOutDescReadPrt)
{
    HAL_PLCIPHER_ReadReg(IN_DESC_PTR, pInDescReadPrt);
    *pInDescReadPrt &= 0xffff;
    HAL_PLCIPHER_ReadReg(OUT_DESC_PTR, pOutDescReadPrt);
    *pOutDescReadPrt &= 0xffff;
    return;
}

HI_VOID HAL_PLCIPHER_GetDescWritePtr(HI_U32* pInDescWritePrt,HI_U32* pOutDescWritePrt)
{

    HI_U32 InDescWritePrt = 0;
    HI_U32 OutDescWritePrt = 0;
    HAL_PLCIPHER_ReadReg(IN_DESC_PTR, &InDescWritePrt);
    InDescWritePrt = (InDescWritePrt >> 16) & 0xffff;
    *pInDescWritePrt = InDescWritePrt;
    HAL_PLCIPHER_ReadReg(OUT_DESC_PTR, &OutDescWritePrt);
    OutDescWritePrt = (OutDescWritePrt >> 16) & 0xffff;
    *pOutDescWritePrt = OutDescWritePrt;

}

HI_VOID HAL_PLCIPHER_GetInDescInvalidNum(HI_U32* pInDescvalidNum )
{
    HAL_PLCIPHER_ReadReg(IN_VLDDESC_CNT, pInDescvalidNum);
    *pInDescvalidNum &= 0xffff;
    return;
}

HI_VOID HAL_PLCIPHER_GetOutDescInvalidNum(HI_U32* pOutDescvalidNum )
{
    HAL_PLCIPHER_ReadReg(OUT_VLDDESC_CNT, pOutDescvalidNum);
    *pOutDescvalidNum &= 0xffff;
    return;
}
#if 1
HI_VOID HAL_PLCipher_HardWareInit(HI_VOID)
{
    U_PERI_CRG48 unCrg;

    /* enable hash hardware clock */
    unCrg.u32 = g_pstRegCrg->PERI_CRG48.u32;
    unCrg.bits.pl_ci_cken = 1;
    unCrg.bits.pl_ci_srst_req = 1;
    g_pstRegCrg->PERI_CRG48.u32 = unCrg.u32;

    unCrg.u32 = g_pstRegCrg->PERI_CRG48.u32;
    unCrg.bits.pl_ci_srst_req = 0;
    g_pstRegCrg->PERI_CRG48.u32 = unCrg.u32;

    return;
}

HI_VOID HAL_PLCipher_HardWareDeInit(HI_VOID)
{
    U_PERI_CRG48 unCrg;
    /* enable hash hardware clock */
    unCrg.u32 = g_pstRegCrg->PERI_CRG48.u32;
    unCrg.bits.pl_ci_cken = 0;
    g_pstRegCrg->PERI_CRG48.u32 = unCrg.u32;

    return;
}
#endif
HI_VOID HAL_PLCipher_EnableGloableInt(HI_VOID)
{
    HI_U32 Int = 0;
    PLCIPHER_INT_ENABLE_U IntEnable;
    HAL_PLCIPHER_ReadReg(PL_INT_ENA, &Int);
    Int |= 0x1;
    HAL_PLCIPHER_WriteReg(PL_INT_ENA, Int);// enable gloable int
    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    IntEnable.bits.int_ena_all = 1;
    HAL_PLCIPHER_WriteReg(ENA_INT, IntEnable.u32);
    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    return;
}

HI_VOID HAL_PLCipher_DisableGloableInt(HI_VOID)
{
    HI_U32 Int = 0;
    PLCIPHER_INT_ENABLE_U IntEnable;
    HAL_PLCIPHER_ReadReg(PL_INT_ENA, &Int);
    Int &= 0xfffffffe;
    HAL_PLCIPHER_WriteReg(PL_INT_ENA, Int);// enable gloable int

    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    IntEnable.bits.int_ena_all = 0;
    HAL_PLCIPHER_WriteReg(ENA_INT, IntEnable.u32);
    return;

}

HI_VOID HAL_PLCipher_EnableAllInt(HI_VOID)
{

    PLCIPHER_INT_ENABLE_U IntEnable;
    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    IntEnable.bits.int_ena_all = 1;
    HAL_PLCIPHER_WriteReg(ENA_INT, IntEnable.u32);
    mb();
    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    return;
}

HI_VOID HAL_PLCipher_DisableAllInt(HI_VOID)
{


    PLCIPHER_INT_ENABLE_U IntEnable;
    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    IntEnable.bits.int_ena_all = 0;
    HAL_PLCIPHER_WriteReg(ENA_INT, IntEnable.u32);
    return;
}

HI_VOID HAL_PLCipher_GetIntState(HI_U32* pu32IntState)
{
    HAL_PLCIPHER_ReadReg(STA_INT, pu32IntState);
    return;
}

HI_VOID HAL_PLCipher_ClrIntState(HI_VOID)
{
    HI_U32 RawInt = 0;
    HAL_PLCIPHER_WriteReg(RAW_INT, 0xffffffff);
    HAL_PLCIPHER_ReadReg(RAW_INT, &RawInt);
    if ( RawInt != 0 )
    {
        HI_FATAL_PLCIPHER("clr raw int ,the it value 0x%x is not 0\n",RawInt);
    }
    return;
}

HI_VOID HAL_PLCipher_EnableOutDescDataDoneInt(HI_VOID)
{

    PLCIPHER_INT_ENABLE_U IntEnable;
    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    IntEnable.bits.int_osta_wrbuffer_done = 1;
    HAL_PLCIPHER_WriteReg(ENA_INT, IntEnable.u32);
    return;
}

HI_VOID HAL_PLCipher_DisableOutDescDataDoneInt(HI_VOID)
{

    PLCIPHER_INT_ENABLE_U IntEnable;
    HAL_PLCIPHER_ReadReg(ENA_INT, &IntEnable.u32);
    IntEnable.bits.int_osta_wrbuffer_done = 0;
    HAL_PLCIPHER_WriteReg(ENA_INT, IntEnable.u32);
    return;
}

HI_VOID HAL_PLCipher_SetKeySecureAttr(HI_BOOL bKeyOnlySecure)
{
    HI_U32 RegValue = 0;
    HAL_PLCIPHER_ReadReg(KEY_SEC_EN_CFG, &RegValue);
    if ( bKeyOnlySecure )
    {
        RegValue |= 0x1;
    }
    else
    {
        RegValue &= 0xffffffffe;
    }
    HAL_PLCIPHER_WriteReg(KEY_SEC_EN_CFG, RegValue);
    return;
}

HI_VOID HAL_PLCipher_ResetDescQueue(HI_VOID)
{
    HAL_PLCIPHER_WriteReg(IN_DESC_SADDR, 0);
    HAL_PLCIPHER_WriteReg(IN_DESC_SIZE, 0);
    HAL_PLCIPHER_WriteReg(IN_VLDDESC_CNT, 0);
    HAL_PLCIPHER_WriteReg(IN_DESC_INT_CFG, 1);


    HAL_PLCIPHER_WriteReg(OUT_DESC_SADDR, 0);
    HAL_PLCIPHER_WriteReg(OUT_DESC_SIZE, 0);
    HAL_PLCIPHER_WriteReg(OUT_VLDDESC_CNT, 0);
    HAL_PLCIPHER_WriteReg(OUT_DESC_INT_CFG, 1);
}

HI_VOID HAL_PLCipher_ConfigDescQueue(HI_U32 InQStartAddr, HI_U32 InQSize,HI_U32 OutQStartAddr, HI_U32 OutQSize )
{

    HAL_PLCIPHER_WriteReg(IN_DESC_SADDR, InQStartAddr);
    HAL_PLCIPHER_WriteReg(IN_DESC_SIZE, InQSize);

    HAL_PLCIPHER_WriteReg(OUT_DESC_SADDR, OutQStartAddr);
    HAL_PLCIPHER_WriteReg(OUT_DESC_SIZE, OutQSize);
    return;
}

HI_VOID HAL_PLCipher_InDescAdd(HI_VOID)
{
    HAL_PLCIPHER_WriteReg(IN_DESC_ADD, 1);
    return;
}

HI_VOID HAL_PLCipher_OutDescAdd(HI_VOID)
{
    HAL_PLCIPHER_WriteReg(OUT_DESC_ADD, 1);
    return;
}

HI_VOID HAL_PLCipher_ConfigCWSetAllAttr(HI_BOOL bOdd,HI_U32 Chan,HI_U32 Algo,HI_BOOL ConfigAsCW)
{
    return;
}

HI_VOID HAL_PLCipher_ConfigCWOddEven(HI_BOOL bOdd)
{
    HI_U32 RegValue = 0;
    HAL_PLCIPHER_ReadReg(CW_SET, &RegValue) ;
    if ( bOdd )
    {
        RegValue |= 0x1ff;
    }
    else
    {
        RegValue &= 0xfffffeff;
    }
    HAL_PLCIPHER_WriteReg(CW_SET, RegValue);

    return;
}

HI_VOID HAL_PLCipher_ConfigCWAlgo(HI_U32 Algo)
{
    HI_U32 RegValue = 0;
    Algo &= 0xff;
    HAL_PLCIPHER_ReadReg(CW_SET, &RegValue) ;
    RegValue &= 0xfff0ffff;
    RegValue |= (Algo << 16);
    HAL_PLCIPHER_WriteReg(CW_SET, RegValue);
    return;
}

HI_VOID HAL_PLCipher_ConfigCWIV(HI_BOOL ConfigAsCW)
{
    HI_U32 RegValue = 0;
    if ( ConfigAsCW )
    {
        RegValue &= 0xfeffffff;
    }
    else
    {
        RegValue |= 0x01000000;
    }

    HAL_PLCIPHER_WriteReg(CW_SET, RegValue);
    return;
}

HI_VOID HAL_PLCipher_ConfigCWChan(HI_U32 Chan)
{
    HI_U32 RegValue = 0;
    Chan &= 0xf;
    RegValue &= 0xffffe1ff;
    RegValue |= (Chan << 9);
    HAL_PLCIPHER_WriteReg(CW_SET, RegValue);
    return;
}


HI_VOID HAL_PLCipher_SetCWAttr(HI_U32 Chan, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, HI_UNF_PLCIPHER_ALG_E enAlg, HI_BOOL bIsCWOrIV )
{
    PLCIPHER_CW_SET_U CWSet;

    HAL_PLCIPHER_ReadReg(CW_SET, &CWSet.u32);



    if ( enKeyEvenOdd ==  HI_UNF_PLCIPHER_KEY_EVEN)
    {
        CWSet.bits.sw_cw_odd_even = 0;
    }
    else
    {
        CWSet.bits.sw_cw_odd_even = 1;
    }

    CWSet.bits.sw_iv_sel = (bIsCWOrIV)?0:1;
    CWSet.bits.sw_cw_channel_id = Chan & 0xf;
    CWSet.bits.sw_cw_type = enAlg & 0xff;

    HAL_PLCIPHER_WriteReg(CW_SET, CWSet.u32);

    return;
}

HI_VOID HAL_PLCipher_GetCWAttr(HI_U32 Chan, HI_UNF_PLCIPHER_KEY_EVENODD_E* penKeyEvenOdd, HI_UNF_PLCIPHER_ALG_E* penAlg )
{
    PLCIPHER_CW_SET_U CWSet;

    HAL_PLCIPHER_ReadReg(CW_SET, &CWSet.u32);

    if ( 1 == CWSet.bits.sw_cw_odd_even )
    {
        *penKeyEvenOdd = HI_UNF_PLCIPHER_KEY_ODD;
    }
    else
    {
        *penKeyEvenOdd = HI_UNF_PLCIPHER_KEY_EVEN;
    }

    *penAlg = CWSet.bits.sw_cw_type & 0xff;
    return;
}


HI_VOID HAL_PLCipher_SetCWWord(HI_U32 CW, HI_U32 WordNo)
{

    switch ( WordNo )
    {
        case  0:
        {
            HAL_PLCIPHER_WriteReg(CW_WORD0, CW);
            break;
        }
        case  1:
        {
            HAL_PLCIPHER_WriteReg(CW_WORD1, CW);
            break;
        }
        case  2:
        {
            HAL_PLCIPHER_WriteReg(CW_WORD2, CW);
            break;
        }
        case  3:
        {
            HAL_PLCIPHER_WriteReg(CW_WORD3, CW);
            break;
        }
        default:
            break;

    }
    return;
}

HI_U32 HAL_PLCipher_GetTimeOutIntStatus(HI_VOID)
{
    PLCIPHER_INT_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(STA_INT, &unIntSta.u32);
    return unIntSta.bits.int_sta_timeout_err;
}

HI_U32 HAL_PLCipher_GetInerTimeOutIntStatus(HI_VOID)
{
    PLCIPHER_INT_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(STA_INT, &unIntSta.u32);
    return unIntSta.bits.int_sta_logic_timeout;
}

HI_U32 HAL_PLCipher_GetInDescEmptyIntStatus(HI_VOID)
{
    PLCIPHER_INT_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(STA_INT, &unIntSta.u32);
    return unIntSta.bits.int_ista_desc_empty;
}

HI_U32 HAL_PLCipher_GetInDescMoveIntStatus(HI_VOID)
{
    PLCIPHER_INT_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(STA_INT, &unIntSta.u32);
    return unIntSta.bits.int_ista_desc_out;
}

HI_U32 HAL_PLCipher_GetOutDescEmptyIntStatus(HI_VOID)
{
    PLCIPHER_INT_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(STA_INT, &unIntSta.u32);
    return unIntSta.bits.int_osta_desc_empty;
}

HI_U32 HAL_PLCipher_GetOutDescDataDoneIntStatus(HI_VOID)
{
    PLCIPHER_INT_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(STA_INT, &unIntSta.u32);
    return unIntSta.bits.int_osta_wrbuffer_done;
}

HI_VOID HAL_PLCipher_ClrOutDescDataDoneIntStatus(HI_VOID)
{
    PLCIPHER_INT_ORG_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(RAW_INT, &unIntSta.u32);
    unIntSta.bits.int_osta_wrbuffer_done = 1;//write 1 clear the ori int
    HAL_PLCIPHER_WriteReg(RAW_INT, unIntSta.u32);
}

HI_VOID HAL_PLCipher_ClrGlobalIntStatus(HI_VOID)
{
    PLCIPHER_INT_ORG_STATUS_U unIntSta;
    HAL_PLCIPHER_ReadReg(RAW_INT, &unIntSta.u32);
    unIntSta.bits.int_ena_all = 1;//write 1 clear the ori int
    HAL_PLCIPHER_WriteReg(RAW_INT, unIntSta.u32);
}


