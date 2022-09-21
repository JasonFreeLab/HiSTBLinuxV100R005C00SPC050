#ifndef HI_MINIBOOT_SUPPORT
#include "common.h"
#endif

#include "hi_common.h"
#include "hi_reg_common.h"

#define readl(_a)        (*(volatile HI_U32 *)(_a))
#define HI_OTP_BASE_ADDR  0xf8ab0000

HI_VOID HI_DRV_SYS_GetChipVersion(HI_CHIP_TYPE_E *penChipType, HI_CHIP_VERSION_E *penChipVersion)
{
    HI_CHIP_TYPE_E      ChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E   ChipVersion = HI_CHIP_VERSION_BUTT;

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)
    if (0x37980100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                ChipType    = HI_CHIP_TYPE_HI3796M;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3798M;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
        }
    }
#elif defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200_b)
    if (0x20281000 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                ChipType    = HI_CHIP_TYPE_HI3798C_A;
                ChipVersion = HI_CHIP_VERSION_V200;
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3798C_B;
                ChipVersion = HI_CHIP_VERSION_V200;
                break;
        }
    }
#elif defined(CHIP_TYPE_hi3798cv200)   \
   || defined(CHIP_TYPE_hi3798mv200)   \
   || defined(CHIP_TYPE_hi3798mv300)	\
   || defined(CHIP_TYPE_hi3798mv200_a) \
   || defined(CHIP_TYPE_hi3796mv200)
    switch (g_pstRegSysCtrl->SC_SYSID)
    {
        case 0x37980200:
            ChipType    = HI_CHIP_TYPE_HI3798C;
            ChipVersion = HI_CHIP_VERSION_V200;
            break;
        case 0x37986200:
            ChipType    = HI_CHIP_TYPE_HI3798M;
            ChipVersion = HI_CHIP_VERSION_V200;
            break;
        case 0x37980210:
            ChipType    = HI_CHIP_TYPE_HI3798M;
            ChipVersion = HI_CHIP_VERSION_V300;
            break;
        case 0x37988200:
            ChipType    = HI_CHIP_TYPE_HI3798M_A;
            ChipVersion = HI_CHIP_VERSION_V200;
            break;
        case 0x37960200:
            ChipType    = HI_CHIP_TYPE_HI3796M;
            ChipVersion = HI_CHIP_VERSION_V200;
            break;
        default:
            ChipType    = HI_CHIP_TYPE_HI3798C;
            ChipVersion = HI_CHIP_VERSION_V200;
            break;
    }
#elif defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    if ((0x37160410 == g_pstRegSysCtrl->SC_SYSID) || (0x37160450 == g_pstRegSysCtrl->SC_SYSID))
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                ChipType    = HI_CHIP_TYPE_HI3716M;
                ChipVersion = HI_CHIP_VERSION_V420;
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3716M;
                ChipVersion = HI_CHIP_VERSION_V410;
                break;
        }
    }
#endif

    if (penChipType)
    {
        *penChipType = ChipType;
    }

    if (penChipVersion)
    {
        *penChipVersion = ChipVersion;
    }
}

HI_S32 HI_DRV_SYS_GetChipPackageType(HI_CHIP_PACKAGE_TYPE_E *penPackageType)
{
    if (HI_NULL == penPackageType)
    {
        return HI_FAILURE;
    }

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)
    if (0x37980100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_23_23;
                return HI_SUCCESS;
            case 0x1:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_19_19;
                return HI_SUCCESS;
            case 0x3:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_15_15;
                return HI_SUCCESS;
            case 0x7:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_QFP_216;
                return HI_SUCCESS;
            default:
                return HI_FAILURE;
        }
    }
#elif defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200_b)
    if (0x20281000 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_31_31;
                break;
            case 0x1:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_19_19;
                break;
            default :
                return HI_FAILURE;
        }
    }
#elif defined(CHIP_TYPE_hi3798cv200)
    if (0x37980200 == g_pstRegSysCtrl->SC_SYSID)
    {
        *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_19_19;
        return HI_SUCCESS;
    }
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
    if ((0x37988200 == g_pstRegSysCtrl->SC_SYSID) || (0x37980210 == g_pstRegSysCtrl->SC_SYSID) || (0x37986200 == g_pstRegSysCtrl->SC_SYSID))
    {
        *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_14_14;
        return HI_SUCCESS;
    }
#elif defined(CHIP_TYPE_hi3796mv200)
   if (0x37960200 == g_pstRegSysCtrl->SC_SYSID)
   {
       switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
       {
            case 0x0:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_21_21;
                break;
            case 0x1:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_15_15;
                break;
            default:
                return HI_FAILURE;
       }
       return HI_SUCCESS;
   }
#elif defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    if ((0x37160410 == g_pstRegSysCtrl->SC_SYSID) || (0x37160450 == g_pstRegSysCtrl->SC_SYSID))
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_19_19;
                break;
            case 0x1:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_16_16;
                break;
            default :
                return HI_FAILURE;
        }
        return HI_SUCCESS;
    }
#else
    #error "Unkown chip type and package type!"
#endif
    return HI_FAILURE;
}

HI_S32 HI_DRV_SYS_GetCPUSecureMode(HI_BOOL *bSecure)
{
    HI_U32 u32RegValue = 0;

    if (HI_NULL == bSecure)
    {
        return HI_FAILURE;
    }

#if defined(CHIP_TYPE_hi3796mv200)
    u32RegValue = readl(HI_OTP_BASE_ADDR + 4);
    if (0x42 == ((u32RegValue >> 8) & 0xff))
    {
        *bSecure = HI_TRUE;
    }
    else
    {
        *bSecure = HI_FALSE;
    }
#else
    HI_UNUSED(u32RegValue);
#ifdef CONFIG_SBL
    *bSecure = HI_FALSE;
#else
    *bSecure = HI_TRUE;
#endif
#endif

    return HI_SUCCESS;
}


