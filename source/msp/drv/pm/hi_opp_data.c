/*
 * HI OPP table definitions.
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
 */
#include <linux/module.h>
#include "hi_opp_data.h"
#include "hi_drv_pmoc.h"

/*
 * Structures containing HI voltage supported and various
 * voltage dependent data for each VDD.
 */
static struct hi_opp_def __initdata hi_opp_def_list[] = {

#if   (!defined(CHIP_TYPE_hi3798mv100)) \
   && (!defined(CHIP_TYPE_hi3796mv100)) \
   && (!defined(CHIP_TYPE_hi3716dv100))
    OPP_INITIALIZER(true,  400000, HI_VDD_MPU_OPP1_UV),
#endif
    OPP_INITIALIZER(true,  600000, HI_VDD_MPU_OPP2_UV),
#if    defined(CHIP_TYPE_hi3716mv410)    \
    || defined(CHIP_TYPE_hi3716mv420)    \
    || defined(CHIP_TYPE_hi3798cv200)    \
    || defined(CHIP_TYPE_hi3798mv200_a)  \
    || defined(CHIP_TYPE_hi3798mv200)    \
    || defined(CHIP_TYPE_hi3798mv300) 	 \
    || defined(CHIP_TYPE_hi3798mv310) 	 \
    || defined(CHIP_TYPE_hi3796mv200)
    OPP_INITIALIZER(true,  800000, HI_VDD_MPU_OPP3_UV),
#endif
#if    (!defined(CHIP_TYPE_hi3798cv200))  \
    && (!defined(CHIP_TYPE_hi3798mv200_a))\
    && (!defined(CHIP_TYPE_hi3798mv200))  \
    && (!defined(CHIP_TYPE_hi3798mv300))  \
    && (!defined(CHIP_TYPE_hi3798mv310))  \
    && (!defined(CHIP_TYPE_hi3796mv200))
    OPP_INITIALIZER(true, 1000000, HI_VDD_MPU_OPP4_UV),
#endif
#if !defined(CHIP_TYPE_hi3716mv410)
    OPP_INITIALIZER(true, 1200000, HI_VDD_MPU_OPP5_UV),
#endif
#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3716dv100)
    OPP_INITIALIZER(true, 1500000, HI_VDD_MPU_OPP6_UV),
#endif
#if    defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200_a) \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3796mv200)
    OPP_INITIALIZER(true, 1600000, HI_VDD_MPU_OPP7_UV),
#endif
};

extern HI_CHIP_TYPE_E g_enChipType;
extern HI_CHIP_VERSION_E g_enChipID;
#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
static struct hi_opp_def __initdata hi_opp_def_list_mv300[] = {
    OPP_INITIALIZER(true,  400000, HI_VDD_MPU_OPP1_UV_300),
    OPP_INITIALIZER(true,  600000, HI_VDD_MPU_OPP2_UV_300),
    OPP_INITIALIZER(true,  800000, HI_VDD_MPU_OPP3_UV_300),
    OPP_INITIALIZER(true, 1200000, HI_VDD_MPU_OPP5_UV_300),
    OPP_INITIALIZER(true, 1600000, HI_VDD_MPU_OPP7_UV_300),
};
#endif

/**
 * hi_opp_init() - initialize hi opp table
 */
int __init hi_opp_init(void)
{
    int r = -ENODEV;

    HI_INFO_PM("enter %s\n", __FUNCTION__);

    if ((HI_CHIP_TYPE_HI3798M == g_enChipType) && ((HI_CHIP_VERSION_V300 == g_enChipID) || (HI_CHIP_VERSION_V310 == g_enChipID)))
    {
#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
        r = hi_init_opp_table(hi_opp_def_list_mv300, ARRAY_SIZE(hi_opp_def_list_mv300));
#endif
    }
    else
    {
        r = hi_init_opp_table(hi_opp_def_list, ARRAY_SIZE(hi_opp_def_list));
    }

    return r;
}

#if 0
#ifndef MODULE
device_initcall(hi_opp_init);
#endif
#endif
