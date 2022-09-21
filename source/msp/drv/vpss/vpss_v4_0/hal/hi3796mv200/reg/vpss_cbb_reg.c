#include <linux/io.h>
#include <linux/delay.h>
#include "vpss_cbb_reg.h"
#include "vpss_common.h"
#include "vpss_reg_struct.h"
#include "vpss_cbb_hal.h"

#if 1


#define VPSS_WRITE_REG_SAFE(reg, val, errlog) \
    { \
        HI_S32 s32Timeout = 0; \
        reg = val; \
        while (val != reg) \
        { \
            if (s32Timeout++ > 10) \
            { \
                VPSS_FATAL(errlog); \
                return HI_FAILURE; \
            } \
            else \
            { \
                udelay(1); \
            } \
        } \
    }

HI_S32 VPSS_REG_RegWrite(volatile HI_U32 *a, HI_U32 b)
{
    volatile HI_U32 *addr = a;

    //printk("W [0x%08x] = 0x%08x(%u,%u).\n", (unsigned int)addr, b, ((b&0xFFFF0000)>>16), (b&0xFFFF));
    *addr = b;
    return HI_SUCCESS;
}

HI_U32 VPSS_REG_RegRead(volatile HI_U32 *a)
{
    volatile HI_U32 *addr = a;

    //printk("R [0x%08x] = 0x%08x(%u,%u).\n", (unsigned int)addr, (*(addr)), (*(addr))>>16, (*(addr))&0xFFFF);
    return (*(addr));
}

HI_S32 VPSS_REG_ResetAppReg(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_REG_S *pstPqReg)
{
    memset((HI_U8 *)pstVpssRegs, 0, sizeof(S_VPSS_REGS_TYPE));

    if (pstPqReg)
    {
        VPSS_SAFE_MEMCPY((HI_U8 *)pstVpssRegs, (HI_U8 *)pstPqReg, sizeof(S_VPSS_REGS_TYPE));
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DRV_SetClockEn(HI_BOOL bClkEn)
{
    if (bClkEn)
    {
        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG60.bits.vpss_srst_req, 1, "VPSS reset timeout!\n");

        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG93.bits.vpss_rst_ok, 1, "VPSS unreset timeout!\n");

        //0x00:345.6MHz; 0x01:24M;  0x02:375M, Must Be same with VPSS_LOGIC_CLOCK_SEL
        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG60.bits.vpss_clk_sel, VPSS_LOGIC_CLOCK_SEL, "VPSS clock select fail!\n");

        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG60.bits.vpss_cken, 1, "VPSS clock enable timeout!\n");

        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG60.bits.vpss_srst_req, 0, "VPSS unreset fail!\n");

        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG93.bits.vpss_rst_ok, 0, "VPSS unreset timeout!\n");
    }
    else
    {
        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG60.bits.vpss_srst_req, 1, "VPSS reset timeout!\n");
        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG93.bits.vpss_rst_ok, 1, "VPSS unreset timeout!\n");
        VPSS_WRITE_REG_SAFE(g_pstRegCrg->PERI_CRG60.bits.vpss_cken, 0, "VPSS disable clock timeout!\n");
    }

    return HI_SUCCESS;
}

#endif

