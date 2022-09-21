/******************************************************************************

  Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sys_ext_k.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2006/02/09
  Description   :
******************************************************************************/
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/version.h> 
#include <asm/io.h>
#include <linux/sched.h>
#include <linux/math64.h>
#include <linux/hikapi.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_reg_common.h"
#include "hi_drv_dev.h"
#include "hi_drv_sys.h"
#include "hi_drv_reg.h"


#define DIV_NS_TO_MS  1000000

/* for irq request, define the CPU num macro  */
#define MEDIA_CPU_INDEX              1
#define GENERAL_DEV_CPU_INDEX        2

DEFINE_SEMAPHORE(g_KSysMutex);

#define kSys_lock()                                       \
do{                                                       \
    HI_S32 s32LockRet = down_interruptible(&g_KSysMutex); \
    if (s32LockRet != 0)                                  \
    {                                                     \
        return s32LockRet;                                \
    }                                                     \
}while(0)

#define kSys_unlock() up(&g_KSysMutex)

/* common module use these two macro itself */
#ifndef HI_REG_WriteBits
#define HI_REG_WriteBits(virAddr, value, mask) do{ \
            HI_U32 __reg; \
            HI_REG_READ(virAddr, __reg); \
            __reg = (__reg & ~(mask)) | ((value) & (mask)); \
            HI_REG_WRITE(virAddr, __reg); \
        }while(0)
#endif

#ifndef HI_REG_ReadBits
#define HI_REG_ReadBits(virAddr, mask)  ({\
            HI_U32 __value;\
            HI_U32 __reg; \
            HI_REG_READ(virAddr, __reg); \
            __value = ((__reg) & (mask)); \
            __value;\
        })
#endif

HI_VOID HI_DRV_SYS_GetChipVersion(HI_CHIP_TYPE_E *penChipType, HI_CHIP_VERSION_E *penChipVersion)
{
    HI_CHIP_TYPE_E      ChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E   ChipVersion = HI_CHIP_VERSION_BUTT;

    /* penChipType or penChipVersion maybe NULL, but not both */
    if (HI_NULL == penChipType && HI_NULL == penChipVersion)
    {
        HI_ERR_SYS("invalid input parameter\n");
        return;
    }

#if defined(CHIP_TYPE_hi3798mv100)  \
 || defined(CHIP_TYPE_hi3796mv100)  \
 || defined(CHIP_TYPE_hi3716dv100)
    if (0x37980100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                ChipType    = HI_CHIP_TYPE_HI3796M;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
            case 0x10:
                ChipType    = HI_CHIP_TYPE_HI3716D;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3798M;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
        }
    }
#elif defined(CHIP_TYPE_hi3798cv200)   \
   || defined(CHIP_TYPE_hi3798mv200)   \
   || defined(CHIP_TYPE_hi3798mv300)   \
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
    if ((0x37160410 == g_pstRegSysCtrl->SC_SYSID) || (0x37160450 == g_pstRegSysCtrl->SC_SYSID) || (0x37160460 == g_pstRegSysCtrl->SC_SYSID))
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
        HI_ERR_SYS("invalid input parameter\n");
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
            case 0x10:
                 *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_21_21;
                 return HI_SUCCESS;
            default:
                HI_ERR_SYS("get package type error!\n");
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
    if ((0x37986200 == g_pstRegSysCtrl->SC_SYSID) || (0x37980210 == g_pstRegSysCtrl->SC_SYSID) || (0x37988200 == g_pstRegSysCtrl->SC_SYSID))
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

HI_S32 HI_DRV_SYS_GetTimeStampMs(HI_U32 *pu32TimeMs)
{
    HI_U64 u64TimeNow;

    if (HI_NULL == pu32TimeMs)
    {
        HI_ERR_SYS("null pointer error\n");
        return HI_FAILURE;
    }

    u64TimeNow = sched_clock();

    do_div(u64TimeNow, DIV_NS_TO_MS);

    *pu32TimeMs = (HI_U32)u64TimeNow;

    return HI_SUCCESS;
}

/*
 * from datasheet, the value of dolby_flag meaning: 0: support; 1: not_support .
 * but we change its meaning for return parameter : 0:not support; 1:support.
 */
HI_S32 HI_DRV_SYS_GetDolbySupport(HI_U32 *pu32Support)
{
    *pu32Support = !(g_pstRegPeri->CHIPSET_INFO.bits.dolby_flag);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_SYS_GetHdrSupport(HI_U32 *pu32Support)
{
#if defined(CHIP_TYPE_hi3798cv200)
    switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.otp_hdr_ctrl)
    {
        case 0x0:
        case 0x1:
            *pu32Support = 0x1;
            break;
        default:
            *pu32Support = 0x0;
            break;
    }
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
    switch(g_pstRegPeri->PERI_SOC_FUSE_0.bits.otp_hdr_ctrl)
    {
        case 0x0:
        case 0x2:
            *pu32Support = 0x1;
            break;
        default:
            *pu32Support = 0x0;
            break;
    }
#else
    *pu32Support = 0x0;
#endif

    return HI_SUCCESS;
}

HI_S32 HI_DRV_SYS_GetDolbyvisionSupport(HI_U32 *pu32Support)
{
#if defined(CHIP_TYPE_hi3798cv200)
    switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.otp_hdr_ctrl)
    {
        case 0x0:
            *pu32Support = 0x1;
            break;
        default:
            *pu32Support = 0x0;
            break;
    }
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
    switch(g_pstRegPeri->PERI_SOC_FUSE_0.bits.otp_hdr_ctrl)
    {
        case 0x0:
        case 0x1:
            *pu32Support = 0x1;
            break;
        default:
            *pu32Support = 0x0;
            break;
    }
#else
    *pu32Support = 0x0;
#endif
    return HI_SUCCESS;
}

/*
 * 1:support; 0:not_support
 */
HI_S32 HI_DRV_SYS_GetDtsSupport(HI_U32 *pu32Support)
{
    *pu32Support = g_pstRegPeri->CHIPSET_INFO.bits.dts_flag;

    return HI_SUCCESS;
}

/*
 * 1:support; 0:not_support
 */
HI_S32 HI_DRV_SYS_GetRoviSupport(HI_U32 *pu32Support)
{
    *pu32Support = g_pstRegPeri->PERI_SOC_FUSE_0.bits.mven;

    return HI_SUCCESS;
}

/*
 * 0: not_advca_support; 1: advca_support
 */
HI_S32 HI_DRV_SYS_GetAdvcaSupport(HI_U32 *pu32Support)
{
#define HI_CHIP_NON_ADVCA   (0x2a13c812)
#define HI_CHIP_ADVCA       (0x6edbe953)

#if    defined(CHIP_TYPE_hi3716dv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || ((defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)) \
         && !defined(HI_ADVCA_TYPE_NAGRA))
#define HI_CHIP_ID_WORD_ADDR_OFFSET       (0x0128)
#else
#define HI_CHIP_ID_WORD_ADDR_OFFSET       (0x0060)
#endif

    HI_U32 AdvcaFlag;
    HI_U32 * pu32AdvcaVirAddr = HI_NULL;

    pu32AdvcaVirAddr = (HI_U32 *)(g_pOtpBaseVirAddr + HI_CHIP_ID_WORD_ADDR_OFFSET);
    if (HI_NULL == pu32AdvcaVirAddr)
    {
        HI_ERR_SYS("pu32AdvcaVirAddr invalid!\n");
        return HI_FAILURE;
    }
    HI_REG_READ(pu32AdvcaVirAddr, AdvcaFlag);

    if (HI_CHIP_ADVCA == AdvcaFlag)
    {
        *pu32Support = 1;
    }
    else if (HI_CHIP_NON_ADVCA == AdvcaFlag)
    {
        *pu32Support = 0;
    }
    else
    {
        HI_ERR_SYS("invalid advca flag\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_SYS_GetMemConfig(HI_SYS_MEM_CONFIG_S *pstConfig)
{
    HI_S32 ret;

    if (HI_NULL == pstConfig)
    {
        return HI_FAILURE;
    }

    ret = get_mem_size(&pstConfig->u32TotalSize, HIKAPI_GET_RAM_SIZE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("get TotalSize failed\n");
        return HI_FAILURE;
    }

    ret = get_mem_size(&pstConfig->u32MMZSize, HIKAPI_GET_CMA_SIZE);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("get CmaSize failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* define otp map offset */
#define SC_SYSID_OFFSET 0xee0
#if defined(CHIP_TYPE_hi3798mv200)    \
 || defined(CHIP_TYPE_hi3798mv300)    \
 || defined(CHIP_TYPE_hi3798mv200_a)
#define OTP_MAP_LOTID0    0x170
#define OTP_MAP_LOTID4    0x174
#define OTP_MAP_LOTID8    0x178
#elif defined(CHIP_TYPE_hi3796mv200)  \
  || (defined(CHIP_TYPE_hi3716mv410) && defined(NOCS3_0_SUPPORT)) \
  || (defined(CHIP_TYPE_hi3716mv420) && defined(NOCS3_0_SUPPORT))
#define OTP_MAP_LOTID0    0x300
#define OTP_MAP_LOTID4    0x304
#define OTP_MAP_LOTID8    0x308
#define SITE_NUM_OFFSET   0x310
#endif

#if defined(CHIP_TYPE_hi3798mv200)    \
 || defined(CHIP_TYPE_hi3798mv300)    \
 || defined(CHIP_TYPE_hi3798mv200_a)  \
 || defined(CHIP_TYPE_hi3796mv200)    \
 || (defined(CHIP_TYPE_hi3716mv410) && defined(NOCS3_0_SUPPORT)) \
 || (defined(CHIP_TYPE_hi3716mv420) && defined(NOCS3_0_SUPPORT))
HI_S32 HI_DRV_SYS_Get64DieID(HI_U64 *pu64dieid)
{
    /* for 57 low bits */
    HI_U64 u64LotIDSum = 0;
    HI_U64 u64LotIDSum_0 = 0, u64LotIDSum_1 = 0;
    HI_U64 u64WaferID = 0;
    HI_U64 u64DieXY = 0;
    HI_U64 u64Low57bits = 0;
    /* for 7 high bits */
    HI_U64 u64TmpSC_Sysid = 0;
    HI_U64 u64High7bits = 0;
    HI_U64 u64High1_0bits = 0;
    HI_U64 u64High4_2bits = 0;
    HI_U64 u64High5bit = 0;
    HI_U64 u64High6bit = 0;

    if (HI_NULL == pu64dieid)
    {
        HI_ERR_SYS("invalid die ID ptr\n");
        return HI_FAILURE;
    }

    kSys_lock();

    u64LotIDSum_0 = HI_REG_ReadBits(g_pOtpBaseVirAddr + OTP_MAP_LOTID0, 0xfffffff0) >> 4;
    u64LotIDSum_1 = HI_REG_ReadBits(g_pOtpBaseVirAddr + OTP_MAP_LOTID4, 0xff);
    u64LotIDSum_1 = u64LotIDSum_1 << 28;
    u64LotIDSum = u64LotIDSum_0 |u64LotIDSum_1;                           /**u64LotIDSum is 36 bit */
    u64WaferID = (HI_REG_ReadBits(g_pOtpBaseVirAddr + OTP_MAP_LOTID4, 0x1f00) >> 8);    /**u64WaferID is 5bit */
    u64DieXY = (HI_REG_ReadBits(g_pOtpBaseVirAddr + OTP_MAP_LOTID4, 0x1fffe000) >> 13);   /**u64DieXY is 16bit*/
    /** put u64LotIDSum u64WaferID and u64DieXY together*/
    u64Low57bits = u64LotIDSum | (u64WaferID << 36) | (u64DieXY << 41);

    /* get the high 7 bits */
    u64TmpSC_Sysid = HI_REG_ReadBits((HI_U8 *)g_pstRegSysCtrl + SC_SYSID_OFFSET, 0xffffffff);
    u64High1_0bits = (u64TmpSC_Sysid & 0x30) >> 4;
    u64High4_2bits = (u64TmpSC_Sysid & 0x700) >> 8;
    u64High5bit = (u64TmpSC_Sysid & 0x80000) >> 19;
    u64High6bit = (u64TmpSC_Sysid & 0x800000) >> 23;
    u64High7bits = (u64High6bit << 6) | (u64High5bit << 5)
                 | (u64High4_2bits << 2) | u64High1_0bits;

    /* get the 64bits chip dieID */
     *pu64dieid = (u64High7bits << 57) | u64Low57bits;

    kSys_unlock();

    return HI_SUCCESS;
}
#else
HI_S32 HI_DRV_SYS_Get64DieID(HI_U64 *pu64dieid)
{
    HI_U64 u64LotIDSum = 0;
    HI_U64 u64LotIDSum_0 = 0, u64LotIDSum_1 = 0;
    HI_U64 u64WaferID = 0;
    HI_U64 u64DieXY = 0;

    if (HI_NULL == pu64dieid)
    {
        HI_ERR_SYS("invalid die ID ptr\n");
        return HI_FAILURE;
    }

    kSys_lock();

    u64LotIDSum_0 = HI_REG_ReadBits(g_pOtpBaseVirAddr + 0x0170, 0xfffffff0) >> 4;
    u64LotIDSum_1 = HI_REG_ReadBits(g_pOtpBaseVirAddr + 0x0174, 0xff);
    u64LotIDSum_1 = u64LotIDSum_1 << 28;
    u64LotIDSum = u64LotIDSum_0 |u64LotIDSum_1;                            /**u64LotIDSum is 36 bit */
    u64WaferID = (HI_REG_ReadBits(g_pOtpBaseVirAddr + 0x0174, 0x1f00) >> 8);     /**u64WaferID is 5bit */
    u64DieXY = (HI_REG_ReadBits(g_pOtpBaseVirAddr + 0x0174, 0x1fffe000) >> 13);  /**u64DieXY is 16bit*/
    /** put u64LotIDSum u64WaferID and u64DieXY together*/
    *pu64dieid = u64LotIDSum | (u64WaferID << 36) | (u64DieXY << 41);

    kSys_unlock();

    return HI_SUCCESS;
}
#endif

/* get the register value on address 0x253(bit[31~30]) of otp */
extern char *get_chiptrim_value(char *buf, unsigned int buflen, unsigned int offset);
extern int get_chiptrim_size(void);

HI_S32 HI_DRV_SYS_Get32DieID(HI_U32 *pu32dieid)
{
#if defined(CHIP_TYPE_hi3798mv200)    \
 || defined(CHIP_TYPE_hi3798mv300)    \
 || defined(CHIP_TYPE_hi3798mv200_a)  \
 || defined(CHIP_TYPE_hi3796mv200)

    HI_U32 u32WaferID = 0;
    HI_U32 u32DieXY = 0;
    HI_U32 u32DieX7Bits = 0;
    HI_U32 u32DieY7Bits = 0;

    HI_U32 u32ShadowTmp = 0;
    HI_U32 u32Hour = 0;
    HI_U32 u32Min = 0;
    HI_U32 u32SiteNum = 0;

    if (HI_NULL == pu32dieid)
    {
        HI_ERR_SYS("invalid die ID ptr\n");
        return HI_FAILURE;
    }

    kSys_lock();

    /* get waferID and dieXY register value */
    u32WaferID = (HI_REG_ReadBits(g_pOtpBaseVirAddr + OTP_MAP_LOTID4, 0x1f00) >> 8);   /**u32WaferID is 5bit */
    u32DieXY = (HI_REG_ReadBits(g_pOtpBaseVirAddr + OTP_MAP_LOTID4, 0x1fffe000) >> 13);  /**u32DieXY is 16bit*/
    u32DieX7Bits = u32DieXY & 0x7f;
    u32DieY7Bits = (u32DieXY & 0x7f00) >> 8;

    /* get hour and min register value */
    u32ShadowTmp = HI_REG_ReadBits(g_pOtpBaseVirAddr + OTP_MAP_LOTID8, 0x03ff8000) >> 15;
    u32Hour = u32ShadowTmp & 0x1f;
    u32Min = (u32ShadowTmp & 0x7e0) >> 5;
#ifndef CHIP_TYPE_hi3796mv200
    /* get SiteNum, the u32SiteNum is bit30 and bit31 in offset 4, and the data length is 4 */
    if(unlikely(get_chiptrim_size() < 8))
    {
        kSys_unlock();
        HI_ERR_SYS("no enough data size for SiteNum\n");
        return HI_FAILURE;
    }

    if(unlikely(!get_chiptrim_value((char *)(&u32SiteNum), 4, 4)))
    {
        kSys_unlock();
        HI_ERR_SYS("get SiteNum error\n");
        return HI_FAILURE;
    }
#else
    u32SiteNum = HI_REG_ReadBits((HI_U8 *)g_pOtpBaseVirAddr + SITE_NUM_OFFSET, 0xFFFFFFFF);
#endif
    u32SiteNum = (u32SiteNum & 0xc0000000) >> 30;
    /** put u32SiteNum ... u32WaferID and u32DieXY together*/
    *pu32dieid = (u32SiteNum << 30) | (u32Hour << 25) | (u32Min << 19) | (u32WaferID << 14)
                | (u32DieX7Bits << 7) | u32DieY7Bits;

    kSys_unlock();

#else
    *pu32dieid = 0x0;
#endif
    return HI_SUCCESS;
}


extern int hi_get_irq_byname(char *name);

HI_S32 HI_DRV_SYS_SetIrqAffinity(HI_MOD_ID_E eModuleId, HI_U32 u32irqNum, const HI_CHAR *name)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_S32 s32CpuIndex = 0;
    HI_U32 __u32irqNum = u32irqNum;

    if (eModuleId < HI_ID_STB || eModuleId > HI_ID_BUTT)
    {
        HI_ERR_SYS("Invalid module id!\n");
        return HI_FAILURE;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 4, 0))
    __u32irqNum = hi_get_irq_byname((char *)name);
    if(-1 == __u32irqNum)
    {
        HI_ERR_SYS("hi_get_irq_byname:%s failed.\n",name);
        return -1;
    }
#endif

    /* only SMP cores and core numbers must be more than 2 */
    if (num_online_cpus() > 2)
    {
        switch (eModuleId)
        {
            case HI_ID_IR:
            case HI_ID_RTC:
            case HI_ID_I2C:
            case HI_ID_SCI:
            case HI_ID_WDG:
            case HI_ID_GPIO:
            case HI_ID_GPIO_I2C:
            case HI_ID_KEYLED:
                s32CpuIndex = GENERAL_DEV_CPU_INDEX;
                HI_INFO_SYS("Gereral device interrupts use CPU %d!\n", GENERAL_DEV_CPU_INDEX);
                break;

#ifdef HI_FPGA_SUPPORT
#ifdef HI_TEE_SUPPORT
            /* TO avoid VPSS's reg r/w operation collision with VDH. (they are both on FPGA4) */
            case HI_ID_VFMW:
            case HI_ID_VPSS:
                s32CpuIndex = 0;
                break;
#endif
#endif
            default:
                s32CpuIndex = MEDIA_CPU_INDEX;
                HI_INFO_SYS("Media interrupts use CPU %d!\n", MEDIA_CPU_INDEX);
                break;
        }

        if (cpu_online(s32CpuIndex))
        {
            s32Ret = irq_set_affinity(__u32irqNum, cpumask_of(s32CpuIndex));
            if(HI_SUCCESS != s32Ret)
            {
                HI_ERR_SYS("cpumask error, cpu num is %d, irq num is %u, name is %s!\n", s32CpuIndex, __u32irqNum);
                return HI_FAILURE;
            }
        }
        else
        {
            HI_ERR_SYS("cpu num %d is offline, irq num is %u,name is %s!\n", s32CpuIndex, __u32irqNum, name);
        }
    }
    else
    {
        HI_INFO_SYS("No need to set irq affinity!\n");
        s32Ret = HI_SUCCESS;
    }
    return s32Ret;
}

HI_S32 HI_DRV_SYS_GetCPUSecureMode(HI_BOOL *bSecure)
{
    HI_U32 u32RegValue = 0;

    if (HI_NULL == bSecure)
    {
        return HI_FAILURE;
    }

#if defined(CHIP_TYPE_hi3796mv200)
    HI_REG_READ(g_pOtpBaseVirAddr + 4, u32RegValue);
    /*TEE disable ,boot kernel all run in secure mode*/
    if (0x42 == ((u32RegValue >> 8) & 0xff))
    {
        *bSecure = HI_TRUE;
    }
    /*TEE enable, boot kernel all run in Non-secure mode ,only secure os run in secure mode*/
    else
    {
        *bSecure = HI_FALSE;
    }
    return HI_SUCCESS;
#else
    HI_UNUSED(u32RegValue);
    HI_ERR_SYS("only 96mv200 support get cpu secure mode!\n");
    return HI_FAILURE;
#endif
}

/*pu32Value: 0普通模式，非0特殊模式；*/
/*EPLL0 地址是0xF8A22030  0x12560418表示特殊模式，其他表示普通模式*/
HI_S32 HI_DRV_SYS_GetFlag(HI_U32 *pu32Value)
{
    HI_U32 u32RegValue = 0;

    if (HI_NULL == pu32Value)
    {
        return HI_FAILURE;
    }

#if defined(CHIP_TYPE_hi3798mv200)   \
   || defined(CHIP_TYPE_hi3798mv300)
    HI_REG_READ((HI_VOID *)g_pstRegCrg + 0x30, u32RegValue);

    if (0x12560418 == (u32RegValue & 0xffffffff))
    {
        *pu32Value = 1;
    }
    else
    {
        *pu32Value = 0;
    }
    return HI_SUCCESS;
#else
    HI_UNUSED(u32RegValue);
    HI_ERR_SYS("only 98mv200 support getflag mode!\n");
    return HI_FAILURE;
#endif
}

EXPORT_SYMBOL(HI_DRV_SYS_GetChipVersion);
EXPORT_SYMBOL(HI_DRV_SYS_GetChipPackageType);
EXPORT_SYMBOL(HI_DRV_SYS_GetTimeStampMs);
EXPORT_SYMBOL(HI_DRV_SYS_GetDolbySupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetHdrSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetDolbyvisionSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetDtsSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetAdvcaSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetRoviSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetMemConfig);
EXPORT_SYMBOL(HI_DRV_SYS_Get64DieID);
EXPORT_SYMBOL(HI_DRV_SYS_Get32DieID);
EXPORT_SYMBOL(HI_DRV_SYS_SetIrqAffinity);
EXPORT_SYMBOL(HI_DRV_SYS_GetCPUSecureMode);
EXPORT_SYMBOL(HI_DRV_SYS_GetFlag);
