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
#include "exports.h"
#include "hi_drv_klad.h"
#include "hal_klad_reg.h"
#include "hal_klad.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


HI_VOID HAL_KLAD_WriteReg(HI_U32 addr, HI_U32 val)
{
    HI_REG_WRITE32(addr, val);
    return;
}

HI_U32 HAL_KLAD_ReadReg(HI_U32 addr)
{
    HI_U32 val = 0;

    HI_REG_READ32(addr, val);
    return val;
}

HI_U32 HAL_KLAD_ReadOtpShadowReg(HI_U32 addr)
{
    HI_U32 val = 0;

    HI_REG_READ32((addr + KL_OTP_SHADOW_BASE_ADDR), val);
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
    HI_BOOL bSecure;
    HI_S32 ret;
    
    ret = HI_DRV_SYS_GetCPUSecureMode(&bSecure);

    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("HI_DRV_SYS_GetCPUSecureMode failed. [%#x]\n", ret);
        return;
    }

    if(bSecure)
    {
        for (i = 0; i < 16; i += 4)
        {
            din = (data[i + 3] << 24) | (data[i + 2] << 16) | (data[i + 1] << 8) | data[i];
            HAL_KLAD_WriteReg(KL_SEC_KLAD_DIN0 + i, din);
        }
    }
    else
    {
        for (i = 0; i < 16; i += 4)
        {
            din = (data[i + 3] << 24) | (data[i + 2] << 16) | (data[i + 1] << 8) | data[i];
            HAL_KLAD_WriteReg(KL_REG_DIN0 + i, din);
        }
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
