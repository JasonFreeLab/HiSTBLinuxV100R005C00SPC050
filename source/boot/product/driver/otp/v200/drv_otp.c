/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
    File Name   : mpi_otp_v200.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "string.h"
#include "hal_otp.h"
#include "drv_otp.h"
#include "otp_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define OTP_CUSTOMER_KEY_LEN            (16)
#define OTP_STB_PRIV_DATA_ADDR          (0x220)
#define OTP_CUSTOMER_KEY_ADDR           (0x230)
#define OTP_SOC_TEE_ENABLE  (0x05)
#define OTP_SEC_WORD     (0x60)
#define OTP_NORMAL_CHIP_VALUE     (0x2A13C812)
#define OTP_SECURE_CHIP_VALUE     (0x6EDBE953)

HI_S32 DRV_OTP_Init(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_DeInit(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data)
{
    OTP_CHECK_PARAM(u32Offset >= 16);

    return HAL_OTP_WriteByte(OTP_STB_PRIV_DATA_ADDR + u32Offset, u8Data);
}

HI_S32 DRV_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data)
{
    HI_U8 value = 0;
    HI_S32 ret  = HI_FAILURE;

    OTP_CHECK_PARAM(u32Offset >= 16);
    OTP_CHECK_PARAM(HI_NULL == pu8Data);

    ret = HAL_OTP_ReadByte(OTP_STB_PRIV_DATA_ADDR + u32Offset, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get stb priv data, return:%x\n", ret);
        return HI_FAILURE;
    }

    *pu8Data = value;

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen)
{
    HI_U8 customerkey[OTP_CUSTOMER_KEY_LEN] = {0};
    HI_S32 ret            = HI_FAILURE;
    HI_S32 i              = 0;

    OTP_CHECK_PARAM(HI_NULL == pKey);
    OTP_CHECK_PARAM(u32KeyLen != 16);

    for (i = 0; i < 16; i++)
    {
        ret = HAL_OTP_ReadByte(OTP_CUSTOMER_KEY_ADDR + i, &customerkey[i]);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_OTP("failed to get customer key, return:%x\n", ret);
            return HI_FAILURE;
        }
    }

    memcpy(pKey, customerkey, OTP_CUSTOMER_KEY_LEN);

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag)
{
    return HI_FAILURE;
}

HI_S32 DRV_OTP_LockIDWord(HI_VOID)
{
    return HI_FAILURE;
}

HI_S32 DRV_OTP_BurnToNormalChipset(HI_VOID)
{
    HI_U32 value = OTP_NORMAL_CHIP_VALUE;
    HI_S32 ret  = HI_FAILURE;
    ret = HAL_OTP_Write(OTP_SEC_WORD, value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Write Normal Chip otp failed, return:%x\n", ret);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_BurnToSecureChipset(HI_VOID)
{
    HI_U32 value = OTP_SECURE_CHIP_VALUE;
    HI_S32 ret  = HI_FAILURE;
    ret = HAL_OTP_Write(OTP_SEC_WORD, value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Write Secure Chip otp failed, return:%x\n", ret);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_U32 DRV_OTP_Read(HI_U32 addr)
{
    HI_U32 value = 0;
    HI_S32 ret   = HI_FAILURE;

    ret = HAL_OTP_Read(addr, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read otp, return:%x\n", ret);
        return 0;
    }

    return value;
}

HI_U8 DRV_OTP_ReadByte(HI_U32 addr)
{
    HI_U8  value = 0;
    HI_S32 ret   = HI_FAILURE;

    ret = HAL_OTP_ReadByte(addr, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read otp, return:%x\n", ret);
        return 0;
    }

    return value;
}

HI_S32 DRV_OTP_WriteByte(HI_U32 addr, HI_U8 u8data)
{
    HI_S32 ret = HI_FAILURE;

    ret = HAL_OTP_WriteByte(addr, u8data);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to write otp, return:%x\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetTrustZoneStat(HI_BOOL *pbEnable)
{
    HI_U8 value = 0;
    HI_S32 ret  = HI_FAILURE;

    ret = HAL_OTP_ReadByte(OTP_SOC_TEE_ENABLE, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get tee status, return:%x\n", ret);
        return HI_FAILURE;
    }

    *pbEnable = (value == 0x42) ? HI_FALSE : HI_TRUE;
    
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
