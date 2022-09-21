/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <asm/io.h>
#include <linux/delay.h>
#include "hi_drv_reg.h"
#include "hi_error_mpi.h"
#include "hal_klad_reg.h"
#include "hal_klad.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


static HI_U8* g_klad_vir_addr = 0;
static HI_U8* g_otp_shadow_vir_addr = 0;

HI_VOID HAL_KLAD_RegisterMap(void)
{
    HI_VOID *ptr = HI_NULL;

    ptr = ioremap_nocache(KL_BASE_ADDR, 0x1000);
    if (HI_NULL == ptr)
    {
        HI_ERR_KLAD("ca_ioremap_nocache err!\n");
        return;
    }
    g_klad_vir_addr = ptr;

    ptr = ioremap_nocache(KL_OTP_SHADOW_BASE_ADDR, 0x1000);
    if (HI_NULL == ptr)
    {
        HI_ERR_KLAD("ca_ioremap_nocache err!\n");
        return;
    }
    g_otp_shadow_vir_addr = ptr;

    return;
}

HI_VOID HAL_KLAD_RegisterUnMap(void)
{
    if (g_klad_vir_addr != 0)
    {
        iounmap((HI_VOID*)g_klad_vir_addr);
        g_klad_vir_addr = 0;
    }

    if (g_otp_shadow_vir_addr != 0)
    {
        iounmap((HI_VOID*)g_otp_shadow_vir_addr);
        g_otp_shadow_vir_addr = 0;
    }

    return;
}

HI_VOID HAL_KLAD_WriteReg(HI_U32 addr, HI_U32 val)
{
    HI_REG_WRITE32((g_klad_vir_addr + (addr - KL_BASE_ADDR)), val);
    return;
}

HI_U32 HAL_KLAD_ReadReg(HI_U32 addr)
{
    HI_U32 val = 0;

    HI_REG_READ32((g_klad_vir_addr + (addr - KL_BASE_ADDR)), val);
    return val;
}

HI_U32 HAL_KLAD_ReadOtpShadowReg(HI_U32 addr)
{
    HI_U32 val = 0;

    HI_REG_READ32((g_otp_shadow_vir_addr + (addr - KL_OTP_SHADOW_BASE_ADDR)), val);
    return val;
}

HI_S32 HAL_KLAD_CheckState(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    KL_KLAD_STATE_U state;
    KL_KLAD_CHECK_ERROR_U check_error;
    HI_U32 cnt = 0;

    while (1)
    {
        state.u32 = 0;
        state.u32 = HAL_KLAD_ReadReg(KL_KLAD_STATE);
#if defined(CHIP_TYPE_hi3716mv420) ||defined(CHIP_TYPE_hi3716mv410)
        if (0x0 == state.bits.hkl_busy)
        {
            break;
        }
#else
        if (0x2 == state.bits.hkl_busy)
        {
            break;
        }
#endif

        msleep(1);
        cnt++;

        // TODO:
        if (cnt >= 100)
        {
            HI_ERR_KLAD("hkl is busy\n");
            return HI_ERR_KLAD_WAIT_TIMEOUT;
        }
    }

    check_error.u32 = HAL_KLAD_ReadReg(KL_KLAD_CHECK_ERROR);
    if (check_error.bits.kl_check_err != 0x0)
    {
        HI_ERR_KLAD("kl_check_err %#x\n", check_error.bits.kl_check_err);
        ret = HI_ERR_KLAD_CHECK_BASE + check_error.bits.kl_check_err;
    }

    return ret;
}

HI_VOID HAL_KLAD_SetDataIn(HI_U8 *data)
{
    HI_U32 i = 0;
    HI_U32 din = 0;

    for (i = 0; i < 16; i += 4)
    {
        din = (data[i + 3] << 24) | (data[i + 2] << 16) | (data[i + 1] << 8) | data[i];
        HAL_KLAD_WriteReg(KL_REG_DIN0 + i, din);
    }

    return;
}

HI_VOID HAL_KLAD_SetComDataIn(HI_U8 *data)
{
    HI_U32 i = 0;
    HI_U32 din = 0;

    for (i = 0; i < 16; i += 4)
    {
        din = (data[i + 3] << 24) | (data[i + 2] << 16) | (data[i + 1] << 8) | data[i];
        HAL_KLAD_WriteReg(KL_COM_KLAD_DIN0 + i, din);
    }

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
