#ifndef __VPSS_IN_INTF_H__
#define __VPSS_IN_INTF_H__
#include "vpss_common.h"
#include "drv_vdec_ext.h"

#include "vpss_in_common.h"

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
#include "vpss_in_3716mv410.h"
#endif

#if defined(CHIP_TYPE_hi3798cv200_a)
#include "vpss_in_hifoneb02.h"
#endif

#if defined(CHIP_TYPE_hi3798mv100_a) || defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)
#include "vpss_in_3798mv100.h"
#endif

#if defined(CHIP_TYPE_hi3798cv200)
#include "vpss_in_3798cv200.h"
#endif

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
#include "vpss_in_3798mv200.h"
#endif

#if defined(CHIP_TYPE_hi3798mv310)
#include "vpss_in_3798mv310.h"
#endif

#if defined(CHIP_TYPE_hi3796mv200)
#include "vpss_in_3796mv200.h"
#endif

#endif
