/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_otp_common_ca.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include "hi_debug.h"
#include "hi_type.h"
#include "hi_error_mpi.h"
#include "hi_unf_otp_common_ca.h"
#include "otp_enum.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define HI_ERR_OTP(fmt...)      HI_ERR_PRINT(HI_ID_OTP, fmt)

#define CHECK_NULL_PTR(ptr)\
do{\
    if(NULL == ptr )\
    {\
        HI_ERR_OTP("point is null\n");\
        return HI_ERR_OTP_PTR_NULL;\
    }\
}while(0)

#define CHECK_OTP_PARAM(val) \
do{\
    if(val) \
    {\
        HI_ERR_OTP("otp param is invalid\n");\
        return HI_ERR_OTP_INVALID_PARA;\
    }\
}while(0)

extern HI_S32 OTP_DRV_PVItem(HI_OTP_DATA_E field_id, HI_BOOL is_write,
                             HI_U8 *value, HI_U32 *value_len, HI_BOOL is_lock);

extern HI_S32 OTP_PVItemWrite(HI_OTP_DATA_E field_id, HI_U8 *value, HI_U32 *value_len);

extern HI_S32 OTP_PVItemRead(HI_OTP_DATA_E field_id, HI_U8 *value, HI_U32 *value_len);


HI_S32 HI_UNF_OTP_COMMON_CA_SetChipID(HI_U8 *pu8ChipID, HI_U32 u32Len)
{
    HI_U32 value_len = 8;

    CHECK_NULL_PTR(pu8ChipID);
    CHECK_OTP_PARAM(u32Len != 8);

    return OTP_PVItemWrite(HI_OTP_CM0_CHIPID, pu8ChipID, &value_len);
}

HI_S32 HI_UNF_OTP_COMMON_CA_GetChipID(HI_U8 *pu8ChipID, HI_U32 *pu32Len)
{
    CHECK_NULL_PTR(pu8ChipID);
    CHECK_NULL_PTR(pu32Len);
    CHECK_OTP_PARAM(*pu32Len != 8);

    return OTP_PVItemRead(HI_OTP_CM0_CHIPID, pu8ChipID, pu32Len);
}

HI_S32 HI_UNF_OTP_COMMON_CA_SetKladLevel(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_LEV_E enLevel)
{
    HI_OTP_DATA_E id;
    HI_U32 value_len = 1;
    HI_U8 value      = 0;

    CHECK_OTP_PARAM(enType >= HI_UNF_OTP_COMMON_CA_KLAD_BUTT);
    CHECK_OTP_PARAM(enLevel >= HI_UNF_OTP_COMMON_CA_KLAD_LEV_BUTT);

    switch (enType)
    {
    case HI_UNF_OTP_COMMON_CA_KLAD_CSA2:
        id = HI_OTP_CM0_CSA2_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_CSA3:
        id = HI_OTP_CM0_CSA3_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_R2R:
        id = HI_OTP_CM0_R2R_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_MISC:
        id = HI_OTP_CM0_MISC_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_SP:
        id = HI_OTP_CM0_SP_LV_SEL;
        break;
    default:
        HI_ERR_OTP("Keyladder type(%x) is invalid\n", enType);
        return HI_ERR_OTP_INVALID_PARA;
    }

    if ( (enType == HI_UNF_OTP_COMMON_CA_KLAD_CSA2)
      || (enType == HI_UNF_OTP_COMMON_CA_KLAD_CSA3)
      || (enType == HI_UNF_OTP_COMMON_CA_KLAD_R2R))
    {
        if ((enLevel < HI_UNF_OTP_COMMON_CA_KLAD_LEV2) || (enLevel > HI_UNF_OTP_COMMON_CA_KLAD_LEV3))
        {
            HI_ERR_OTP("level(%x) is invalid\n", enLevel);
            return HI_ERR_OTP_INVALID_PARA;
        }
    }
    else
    {
        if ((enLevel < HI_UNF_OTP_COMMON_CA_KLAD_LEV2) || (enLevel > HI_UNF_OTP_COMMON_CA_KLAD_LEV5))
        {
            HI_ERR_OTP("level(%x) is invalid\n", enLevel);
            return HI_ERR_OTP_INVALID_PARA;
        }
    }

    value = enLevel - 1;

    return OTP_PVItemWrite(id, &value, &value_len);
}


HI_S32 HI_UNF_OTP_COMMON_CA_GetKladLevel(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_LEV_E *penLevel)
{
    HI_U8 value = 0;
    HI_U32 value_len = 1;
    HI_OTP_DATA_E id;
    HI_S32 ret = HI_FAILURE;

    CHECK_OTP_PARAM(enType >= HI_UNF_OTP_COMMON_CA_KLAD_BUTT);
    CHECK_NULL_PTR(penLevel);

    switch (enType)
    {
    case HI_UNF_OTP_COMMON_CA_KLAD_CSA2:
        id = HI_OTP_CM0_CSA2_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_CSA3:
        id = HI_OTP_CM0_CSA3_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_R2R:
        id = HI_OTP_CM0_R2R_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_MISC:
        id = HI_OTP_CM0_MISC_LV_SEL;
        break;
    case HI_UNF_OTP_COMMON_CA_KLAD_SP:
        id = HI_OTP_CM0_SP_LV_SEL;
        break;
    default:
        HI_ERR_OTP("Keyladder type(%x) is invalid\n", enType);
        return HI_ERR_OTP_INVALID_PARA;
    }

    ret = OTP_PVItemRead(id, &value, &value_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to get keyladder level, return:%x\n", ret);
        return ret;
    }

    *penLevel = (HI_UNF_OTP_COMMON_CA_KLAD_LEV_E)(value + 1);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_OTP_COMMON_CA_SetKladTarget(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_TARGET_E enTarget)
{
    HI_OTP_DATA_E id;
    HI_U8 value = 0;
    HI_U32 value_len = 1;

    CHECK_OTP_PARAM(enTarget >= HI_UNF_OTP_COMMON_CA_KLAD_TARGET_BUTT);
    CHECK_OTP_PARAM(enType != HI_UNF_OTP_COMMON_CA_KLAD_MISC && enType != HI_UNF_OTP_COMMON_CA_KLAD_SP);

    if (enType == HI_UNF_OTP_COMMON_CA_KLAD_MISC)
    {
        id = HI_OTP_CM0_MISC_CTRL;
    }
    else
    {
        id = HI_OTP_CM0_SP_CTRL;
    }

    value = enTarget;

    return OTP_PVItemWrite(id, &value, &value_len);
}


HI_S32 HI_UNF_OTP_COMMON_CA_GetKladTarget(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_UNF_OTP_COMMON_CA_KLAD_TARGET_E *penTarget)
{
    HI_OTP_DATA_E id;
    HI_U8 value = 0;
    HI_U32 value_len = 1;
    HI_S32 ret = HI_FAILURE;

    CHECK_OTP_PARAM(enType != HI_UNF_OTP_COMMON_CA_KLAD_MISC && enType != HI_UNF_OTP_COMMON_CA_KLAD_SP);
    CHECK_NULL_PTR(penTarget);

    if (enType == HI_UNF_OTP_COMMON_CA_KLAD_MISC)
    {
        id = HI_OTP_CM0_MISC_CTRL;
    }
    else
    {
        id = HI_OTP_CM0_SP_CTRL;
    }

    ret = OTP_PVItemRead(id, &value, &value_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get keyladder target, return:%x\n", ret);
        return ret;
    }

    *penTarget = value;
    return HI_SUCCESS;
}

HI_S32 HI_UNF_OTP_COMMON_CA_DisableKlad(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType)
{
    HI_U8 value = 1;
    HI_U32 value_len = 1;
    HI_OTP_DATA_E id;

    switch (enType)
    {
    case HI_UNF_OTP_COMMON_CA_CSA2:
        id = HI_OTP_CM0_CSA2_KL_DISABLE;
        break;
    case HI_UNF_OTP_COMMON_CA_CSA3:
        id = HI_OTP_CM0_CSA3_KL_DISABLE;
        break;
    case HI_UNF_OTP_COMMON_CA_R2R:
        id = HI_OTP_CM0_R2R_KL_DISABLE;
        break;
    default:
        HI_ERR_OTP("keyladder type(%x) is invalid\n", enType);
        return HI_ERR_OTP_INVALID_PARA;
    }


    return OTP_PVItemWrite(id, &value, &value_len);
}

HI_S32 HI_UNF_OTP_COMMON_CA_GetKladStat(HI_UNF_OTP_COMMON_CA_KLAD_TYPE_E enType, HI_BOOL *pbEnable)
{
    HI_U8 value = 0;
    HI_U32 value_len = 1;
    HI_S32 ret = HI_FAILURE;
    HI_OTP_DATA_E id;

    CHECK_NULL_PTR(pbEnable);

    switch (enType)
    {
    case HI_UNF_OTP_COMMON_CA_CSA2:
        id = HI_OTP_CM0_CSA2_KL_DISABLE;
        break;
    case HI_UNF_OTP_COMMON_CA_CSA3:
        id = HI_OTP_CM0_CSA3_KL_DISABLE;
        break;
    case HI_UNF_OTP_COMMON_CA_R2R:
        id = HI_OTP_CM0_R2R_KL_DISABLE;
        break;
    default:
        HI_ERR_OTP("keyladder type(%x) is invalid\n", enType);
        return HI_ERR_OTP_INVALID_PARA;
    }

    ret = OTP_PVItemRead(id, &value, &value_len);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get keyladder status, return:%x\n", ret);
        return ret;
    }

    *pbEnable = (value == 1) ? HI_FALSE : HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_OTP_COMMON_CA_SetRootKey(HI_UNF_OTP_COMMON_CA_ROOTKEY_E enType, HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
    HI_OTP_DATA_E id;
    HI_U32 value_len = 16;

    CHECK_OTP_PARAM(enType >= HI_UNF_OTP_COMMON_CA_BUTT);
    CHECK_NULL_PTR(pu8Key);
    CHECK_OTP_PARAM(u32KeyLen != 16);

    switch (enType)
    {
    case HI_UNF_OTP_COMMON_CA_CSA2:
        id = HI_OTP_CM0_CSA2_ROOTKEY;
        break;
    case HI_UNF_OTP_COMMON_CA_CSA3:
        id = HI_OTP_CM0_CSA3_ROOTKEY;
        break;
    case HI_UNF_OTP_COMMON_CA_R2R:
        id = HI_OTP_CM0_R2R_ROOTKEY;
        break;
    case HI_UNF_OTP_COMMON_CA_MISC:
        id = HI_OTP_CM0_MISC_ROOTKEY;
        break;
    case HI_UNF_OTP_COMMON_CA_SP:
        id = HI_OTP_CM0_SP_ROOTKEY;
        break;
    case HI_UNF_OTP_COMMON_CA_BOOT:
        id = HI_OTP_BOOT_ROOTKEY;
        break;
    default:
        HI_ERR_OTP("rootkey type(%x) is invalid\n", enType);
        return HI_ERR_OTP_INVALID_PARA;
    }

    return OTP_PVItemWrite(id, pu8Key, &value_len);
}


HI_S32 HI_UNF_OTP_COMMON_CA_SetJTAGKey(HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
    HI_U32 value_len = 16;
    CHECK_NULL_PTR(pu8Key);
    CHECK_OTP_PARAM(u32KeyLen != 16);

    return OTP_PVItemWrite(HI_OTP_CM0_JTAG_KEY, pu8Key, &value_len);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
