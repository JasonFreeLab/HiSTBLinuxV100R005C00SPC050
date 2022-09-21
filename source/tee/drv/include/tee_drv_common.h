#include "hi_type.h"

#ifndef __TEE_DRV_COMMON_H__
#define __TEE_DRV_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define USECS_PER_SEC	1000000

/** Define the chip type. */
typedef enum teeCHIP_TYPE_E
{
    TEE_CHIP_TYPE_HI3796C    = 0x20,
    TEE_CHIP_TYPE_HI3798C,
    TEE_CHIP_TYPE_HI3796M,
    TEE_CHIP_TYPE_HI3798M,

    TEE_CHIP_TYPE_HI3796C_A  = 0x40,
    TEE_CHIP_TYPE_HI3798C_A,
    TEE_CHIP_TYPE_HI3798C_B,

    TEE_CHIP_TYPE_HI3798M_A,

    TEE_CHIP_TYPE_BUTT
}TEE_CHIP_TYPE_E;

/** Define the chip version. */
typedef enum teeCHIP_VERSION_E
{
    TEE_CHIP_VERSION_V100 = 0x100,
    TEE_CHIP_VERSION_V101 = 0x101,
    TEE_CHIP_VERSION_V200 = 0x200,
    TEE_CHIP_VERSION_V210 = 0x210,
    TEE_CHIP_VERSION_V300 = 0x300,
    TEE_CHIP_VERSION_V310 = 0x310,
    TEE_CHIP_VERSION_V400 = 0x400,
    TEE_CHIP_VERSION_V410 = 0x410,
    TEE_CHIP_VERSION_V420 = 0x420,
    TEE_CHIP_VERSION_BUTT
}TEE_CHIP_VERSION_E;


#define HI_TEE_RIGHTCHECK_W(pVar, size)                 \
do                                                      \
{                                                       \
    if (!tee_hal_access_check(pVar, size))              \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_NOPERMISSION);   \
        return HI_TEE_ERR_NOPERMISSION;                 \
    }                                                   \
    if (!tee_hal_write_right_check(pVar, size))         \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_NOPERMISSION);   \
        return HI_TEE_ERR_NOPERMISSION;                 \
    }                                                   \
} while (0)

#define HI_TEE_RIGHTCHECK_R(pVar, size)                 \
do                                                      \
{                                                       \
    if (!tee_hal_access_check(pVar, size))              \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_NOPERMISSION);   \
        return HI_TEE_ERR_NOPERMISSION;                 \
    }                                                   \
    if (!tee_hal_read_right_check(pVar, size))          \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_NOPERMISSION);   \
        return HI_TEE_ERR_NOPERMISSION;                 \
    }                                                   \
} while (0)

#define HI_TEE_RIGHTCHECK_RW(pVar, size)                \
do                                                      \
{                                                       \
    if (!tee_hal_access_check(pVar, size))              \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_NOPERMISSION);   \
        return HI_TEE_ERR_NOPERMISSION;                 \
    }                                                   \
    if (!tee_hal_write_right_check(pVar, size))         \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_NOPERMISSION);   \
        return HI_TEE_ERR_NOPERMISSION;                 \
    }                                                   \
    if (!tee_hal_read_right_check(pVar, size))          \
    {                                                   \
        HI_LOG_PrintErrCode(HI_TEE_ERR_NOPERMISSION);   \
        return HI_TEE_ERR_NOPERMISSION;                 \
    }                                                   \
} while (0)



HI_S32 TEE_DRV_DelayUs(HI_U32 us);

HI_S32 TEE_DRV_GetChipVersion(TEE_CHIP_TYPE_E *penChipType, TEE_CHIP_VERSION_E *penChipVersion);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
