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


#include <asm/barrier.h>    /* mb() */
#include <linux/delay.h>
#include <linux/spinlock.h>
#include "linux/io.h" /*ioread32*/
#include "hi_type.h"

#include "drv_plcipher_reg.h"
#include "hal_plcipher.h"
#include "drv_advca_ext.h"

#include "hi_drv_plcipher.h"
#include "hi_reg_common.h"
#include "drv_plcipher_define.h"


/***************************** Macro Definition ******************************/
/*process of bit*/
#define HAL_SET_BIT(src, bit)        ((src) |= (1<<bit))
#define HAL_CLEAR_BIT(src,bit)       ((src) &= ~(1<<bit))

#define PLCIPHER_READ_REG(offset)  ioread32((void *)(PLCIPHER_REG_BASE_ADDR  + offset))
#define PLCIPHER_WRITE_REG(offset, value) iowrite32(value, (void*)(PLCIPHER_REG_BASE_ADDR  + offset))

/******************************* API declaration *****************************/

HI_VOID HAL_PLCipher_HardWareInit(HI_VOID)
{
    U_PERI_CRG264 unCrg;

    /* enable hash hardware clock */
    unCrg.u32 = g_pstRegCrg->PERI_CRG264.u32;
    unCrg.bits.plcipher_cken = 1;
    unCrg.bits.plcipher_srst_req = 1;
    g_pstRegCrg->PERI_CRG264.u32 = unCrg.u32;

    unCrg.u32 = g_pstRegCrg->PERI_CRG264.u32;
    unCrg.bits.plcipher_srst_req = 0;
    g_pstRegCrg->PERI_CRG264.u32 = unCrg.u32;
    mb();
    udelay(100);


}

HI_VOID HAL_PLCipher_HardWareDeInit(HI_VOID)
{
    U_PERI_CRG264 unCrg;
    /* enable hash hardware clock */
    unCrg.u32 = g_pstRegCrg->PERI_CRG264.u32;
    unCrg.bits.plcipher_cken = 0;
    g_pstRegCrg->PERI_CRG264.u32 = unCrg.u32;
    mb();
}

#ifndef PLCIPHER_TEE_SUPPORT
HI_VOID HAL_PLCipher_EnMMU(HI_U32 u32MmuTlbBase)
{
    HI_U32 baseAddr = 0;
    U_DMA_S_TLB_BASE base;
    U_DMA_S_CTRL Val;
    base.u32 =  u32MmuTlbBase;
    PLCIPHER_WRITE_REG(DMA_S_TLB_BASE, base.u32);
    wmb();/*sync the DDR*/

    PLCIPHER_WRITE_REG(DMA_S_TLB_BASE, base.u32);
    baseAddr = PLCIPHER_READ_REG(DMA_S_TLB_BASE);
    BUG_ON(baseAddr != u32MmuTlbBase );

    Val.u32 = PLCIPHER_READ_REG(DMA_S_CTRL);
    Val.bits.dma_s_mmu_en = 1;
    PLCIPHER_WRITE_REG(DMA_S_CTRL, Val.u32);
}

HI_VOID HAL_PLCipher_DisMMU(HI_VOID)
{
    U_DMA_S_CTRL Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_S_CTRL);
    Val.bits.dma_s_mmu_en = 0;
    PLCIPHER_WRITE_REG(DMA_S_CTRL, Val.u32);
}

HI_VOID HAL_PLCipher_EnAllInt(HI_VOID)
{
    U_DMA_S_CTRL Val;
    U_DMA_S_GLB_STAT stat;

    Val.u32 = PLCIPHER_READ_REG(DMA_S_CTRL);
    Val.bits.s_obuf_pack_int_en = 1;
    PLCIPHER_WRITE_REG(DMA_S_CTRL, Val.u32);
    stat.u32= PLCIPHER_READ_REG(DMA_S_GLB_STAT);
    stat.bits.dma_s_int_msk = 1;
    PLCIPHER_WRITE_REG(DMA_S_GLB_STAT, Val.u32);
}
HI_VOID HAL_PLCipher_DisAllInt(HI_VOID)
{
    U_DMA_S_CTRL Val;
    U_DMA_S_GLB_STAT stat;

    Val.u32 = PLCIPHER_READ_REG(DMA_S_CTRL);
    Val.bits.s_obuf_pack_int_en = 0;
    PLCIPHER_WRITE_REG(DMA_S_CTRL, Val.u32);
    stat.u32 = PLCIPHER_READ_REG(DMA_S_GLB_STAT);
    stat.bits.dma_s_int_msk = 0;
    PLCIPHER_WRITE_REG(DMA_S_GLB_STAT, Val.u32);
}

HI_VOID HAL_PLCipher_SetSecChn(HI_U32 u32ChnId)
{
    U_DMA_S_CTRL Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_S_CTRL);
    HAL_SET_BIT( Val.bits.dma_s_ci_sel, u32ChnId);
    PLCIPHER_WRITE_REG(DMA_S_CTRL, Val.u32);
}

HI_VOID HAL_PLCipher_CfgDMACoal(HI_U32 u32Packets)
{
    U_DMA_S_COAL_CFG Val;
    Val.bits.s_coal_cnt_nums = u32Packets & 0xffff;
    Val.bits.s_coal_time_cyc    = 0x3ff;/* ever packet wull cost 4us , the max packet num is 0xff = 255 ,it will cost 255*4= 0x3fc*/
    PLCIPHER_WRITE_REG(DMA_S_COAL_CFG, Val.u32);
}


HI_VOID HAL_PLCipher_GetDMAGlBStatus(HI_U32 *GlBStatus)
{
    *GlBStatus = PLCIPHER_READ_REG(DMA_S_GLB_STAT);
}

#else

HI_VOID HAL_PLCipher_EnMMU(HI_U32 u32MmuTlbBase)
{
    HI_U32 baseAddr = 0;
    U_DMA_TLB_BASE base;
    U_DMA_CTRL Val;
    base.u32 =  u32MmuTlbBase;
    PLCIPHER_WRITE_REG(DMA_TLB_BASE, base.u32);
    mb();
    baseAddr = PLCIPHER_READ_REG(DMA_TLB_BASE);
    BUG_ON(baseAddr != u32MmuTlbBase);

    Val.u32 = PLCIPHER_READ_REG(DMA_CTRL);
    Val.bits.dma_mmu_en = 1;
    PLCIPHER_WRITE_REG(DMA_CTRL, Val.u32);
}

HI_VOID HAL_PLCipher_DisMMU(HI_VOID)
{
    U_DMA_CTRL Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_CTRL);
    Val.bits.dma_mmu_en = 0;
    PLCIPHER_WRITE_REG(DMA_CTRL, Val.u32);
    mb();
}

HI_VOID HAL_PLCipher_EnAllInt(HI_VOID)
{
    U_DMA_CTRL Val;
    U_DMA_GLB_STAT stat;

    Val.u32 = PLCIPHER_READ_REG(DMA_CTRL);
    Val.bits.obuf_pack_int_en = 1;
    PLCIPHER_WRITE_REG(DMA_CTRL, Val.u32);
    stat.u32= PLCIPHER_READ_REG(DMA_GLB_STAT);
    stat.bits.dma_int_msk = 1;
    PLCIPHER_WRITE_REG(DMA_GLB_STAT, Val.u32);
}

HI_VOID HAL_PLCipher_DisAllInt(HI_VOID)
{
    U_DMA_CTRL Val;
    U_DMA_GLB_STAT stat;

    Val.u32 = PLCIPHER_READ_REG(DMA_CTRL);
    Val.bits.obuf_pack_int_en = 0;
    PLCIPHER_WRITE_REG(DMA_CTRL, Val.u32);

    stat.u32 = PLCIPHER_READ_REG(DMA_GLB_STAT);
    stat.bits.dma_int_msk = 0;
    PLCIPHER_WRITE_REG(DMA_GLB_STAT, stat.u32);

}
HI_VOID HAL_PLCipher_GetDMAGlBStatus(HI_U32 *GlBStatus)
{
    *GlBStatus = PLCIPHER_READ_REG(DMA_GLB_STAT);
}

HI_VOID HAL_PLCipher_CfgDMACoal(HI_U32 u32Packets)
{
    U_DMA_COAL_CFG Val;
    Val.bits.coal_cnt_nums = u32Packets & 0xffff;
    Val.bits.coal_time_cyc  = 0x3ff;/* ever packet wull cost 4us , the max packet num is 0xff = 255 ,it will cost 255*4= 0x3fc*/
    PLCIPHER_WRITE_REG(DMA_COAL_CFG, Val.u32);
}

HI_VOID HAL_PLCipher_SetSecChn(HI_U32 u32ChnId)
{
    return;
}
#endif
//==================================in channel ===================================
HI_VOID HAL_PLCipher_EnDmaChn(HI_U32 u32ChnId)
{
    U_DMA_CHNL_ENB Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_CHNL_ENB);
    HAL_SET_BIT( Val.bits.dma_chanls_enb, u32ChnId);
    PLCIPHER_WRITE_REG(DMA_CHNL_ENB, Val.u32);
}

HI_VOID HAL_PLCipher_DisDmaChn(HI_U32 u32ChnId)
{
    U_DMA_CHNL_DIS Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_CHNL_DIS);
    HAL_SET_BIT( Val.bits.dma_chanls_dis, u32ChnId);
    PLCIPHER_WRITE_REG(DMA_CHNL_DIS, Val.u32);
}

HI_VOID HAL_PLCipher_SetDmaChanBase(HI_U32 u32ChnId,HI_U32 u32Addr)
{
    U_DMA_CHNL_BASE Val;
    Val.u32 = u32Addr;
    PLCIPHER_WRITE_REG(DMA_CHNL_BASE(u32ChnId) , Val.u32);
}

HI_VOID HAL_PLCipher_SetDmaChanDepth(HI_U32 u32ChnId,HI_U32 u32Depth)
{
    U_DMA_CHNL_DEPTH Val;
    Val.u32 = u32Depth - 1;
    PLCIPHER_WRITE_REG(DMA_CHNL_DEPTH(u32ChnId), Val.u32);
}


HI_VOID HAL_PLCipher_DmaChanAddDesc(HI_U32 u32ChnId)
{
    U_DMA_SLOT_PI_W Val;
    Val.bits.sw_pi_w_bid = (u32ChnId & 0x3f);
    Val.bits.sw_pi_wptr = 1;
    PLCIPHER_WRITE_REG(DMA_SLOT_PI_W, Val.u32);
}

HI_VOID HAL_PLCipher_ResetDmaChanDescPW(HI_U32 u32ChnId)
{
    U_DMA_SLOT_PI_W Val;
    Val.bits.sw_pi_w_bid = (u32ChnId & 0x3f);
    Val.bits.sw_pi_wptr = 0;
    PLCIPHER_WRITE_REG(DMA_SLOT_PI_W, Val.u32);
}

//==================================out channel ===================================
HI_VOID HAL_PLCipher_SetDmaObufAddr(HI_U32 u32ChnId,HI_U32 u32Addr)
{
    U_DMA_OBUF_ADDR Val;
    Val.u32 = u32Addr;
    PLCIPHER_WRITE_REG(DMA_OBUF_ADDR(u32ChnId) , Val.u32);
}

HI_VOID HAL_PLCipher_EnDmaObuf(HI_U32 u32ChnId)
{
    U_DMA_OBUF_ENB_L Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_OBUF_ENB_L);
    HAL_SET_BIT( Val.bits.dma_obuf_enb_l, u32ChnId);
    PLCIPHER_WRITE_REG(DMA_OBUF_ENB_L, Val.u32);
}

HI_VOID HAL_PLCipher_DisDmaObuf(HI_U32 u32ChnId)
{
    U_DMA_OBUF_DIS_L Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_OBUF_DIS_L);
    HAL_SET_BIT( Val.bits.dma_obuf_dis_l, u32ChnId);
    PLCIPHER_WRITE_REG(DMA_OBUF_DIS_L, Val.u32);
}

HI_VOID HAL_PLCipher_SetDmaObufLen(HI_U32 u32ChnId,HI_U32 u32Len)
{
    U_DMA_OBUF_LEN Val;
    Val.u32 = u32Len;
    PLCIPHER_WRITE_REG(DMA_OBUF_LEN(u32ChnId), Val.u32);
}

HI_VOID HAL_PLCipher_ResetDmaObufPR(HI_U32 u32ChnId)
{
    PLCIPHER_WRITE_REG(DMA_SLOT_PO_R(u32ChnId), 0x0);
}

HI_VOID HAL_PLCipher_GetDmaObufPW(HI_U32 u32ChnId,HI_U32* pu32ObufPw)
{
    *pu32ObufPw = PLCIPHER_READ_REG(DMA_SLOT_PO_W(u32ChnId));
}

HI_VOID HAL_PLCipher_GetDmaObufPR(HI_U32 u32ChnId,HI_U32* pu32ObufPw)
{
    *pu32ObufPw = PLCIPHER_READ_REG(DMA_SLOT_PO_R(u32ChnId));
}

//==================================interupt===================================


HI_VOID HAL_PLCipher_GetDMAObufIntStatus(HI_U32 *OufIntStatus )
{
    *OufIntStatus= PLCIPHER_READ_REG(DMA_PACK_INT_L);
}

HI_VOID HAL_PLCipher_ClrDMAObufIntStatus(HI_U32 u32ChnId)
{
    U_DMA_OBUF_STAT_L Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_PACK_INT_L);
    HAL_SET_BIT(Val.bits.dma_obuf_stat_l,u32ChnId);
    PLCIPHER_WRITE_REG(DMA_PACK_INT_L, Val.u32);
}




HI_VOID HAL_PLCipher_ClrDMAObufMMU(HI_U32 u32ChnId)
{
    U_DMA_OBUF_MMU_DIS_L Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_OBUF_MMU_DIS_L);
    HAL_SET_BIT(Val.bits.dma_obuf_mmu_dis_l,u32ChnId);
    PLCIPHER_WRITE_REG(DMA_OBUF_MMU_DIS_L, Val.u32);
}

HI_VOID HAL_PLCipher_ClrDMAChanMMU(HI_U32 u32ChnId)
{
    U_DMA_CHNL_DIS Val;
    Val.u32 = PLCIPHER_READ_REG(DMA_CHNL_DIS);
    HAL_SET_BIT(Val.bits.dma_pi_mmu_dis,u32ChnId);
    PLCIPHER_WRITE_REG(DMA_CHNL_DIS, Val.u32);
}


HI_VOID HAL_PLCipher_CfgChanPIDFilter(HI_U32 u32ChnId,HI_BOOL bFilterEn)
{
    U_PL_CHN_PID_FLT_EN Val;
    Val.u32 = PLCIPHER_READ_REG(PL_CHN_PID_FLT_EN);
    if ( bFilterEn )
    {
        HAL_SET_BIT( Val.bits.sw_pid_mode, u32ChnId);
    }
    else
    {
        HAL_CLEAR_BIT( Val.bits.sw_pid_mode, u32ChnId);
    }
    PLCIPHER_WRITE_REG(PL_CHN_PID_FLT_EN, Val.u32);
}

HI_VOID HAL_PLCipher_SetChnPID(HI_U32 u32ChnId,HI_U8 PIDNo, HI_U16 PID)
{
    HI_U32 value = 0;
    value = (1 << 13 ) | (PID & 0x1fff);
    PLCIPHER_WRITE_REG(PID_CHN_CFG(u32ChnId, PIDNo), value);
}

HI_VOID HAL_PLCipher_DisChnPID(HI_U32 u32ChnId,HI_U8 PIDNo)
{
    HI_U32 value = 0;
    value = (0 << 13);
    PLCIPHER_WRITE_REG(PID_CHN_CFG(u32ChnId, PIDNo), value);
}

HI_VOID HAL_PLCipher_SetCWAttr(HI_U32 Chan, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, HI_UNF_PLCIPHER_ALG_E enAlg, HI_BOOL bIsCWOrIV )
{
    PLCIPHER_CW_SET_U CWSet;

    CWSet.u32 = PLCIPHER_READ_REG(CW_SET);



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

    PLCIPHER_WRITE_REG(CW_SET, CWSet.u32);
}

HI_VOID HAL_PLCipher_GetCWAttr(HI_U32 Chan, HI_UNF_PLCIPHER_KEY_EVENODD_E* penKeyEvenOdd, HI_UNF_PLCIPHER_ALG_E* penAlg )
{
    PLCIPHER_CW_SET_U CWSet;

    CWSet.u32 = PLCIPHER_READ_REG(CW_SET);

    if ( 1 == CWSet.bits.sw_cw_odd_even )
    {
        *penKeyEvenOdd = HI_UNF_PLCIPHER_KEY_ODD;
    }
    else
    {
        *penKeyEvenOdd = HI_UNF_PLCIPHER_KEY_EVEN;
    }

    *penAlg = CWSet.bits.sw_cw_type & 0xff;
}
HI_VOID HAL_PLCipher_SetCWWord(HI_U32 CW, HI_U32 WordNo)
{
    PLCIPHER_WRITE_REG(CW_WORD(WordNo), CW);
}



