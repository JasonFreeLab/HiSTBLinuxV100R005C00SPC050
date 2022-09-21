/*
 *  Generic watchdog defines. Derived from..
 *
 * Berkshire PC Watchdog Defines
 * by Ken Hollis <khollis@bitgate.com>
 *
 */

#ifndef _HI_DRV_WDG_H
#define _HI_DRV_WDG_H

#include "hi_debug.h"

#define HI_FATAL_WDG(fmt...)    HI_FATAL_PRINT(HI_ID_WDG, fmt)
#define HI_ERR_WDG(fmt...)      HI_ERR_PRINT(HI_ID_WDG, fmt)
#define HI_WARN_WDG(fmt...)     HI_WARN_PRINT(HI_ID_WDG, fmt)
#define HI_INFO_WDG(fmt...)     HI_INFO_PRINT(HI_ID_WDG, fmt)

#define HI_WDG_NUM  (1)

#endif  /* ifndef _HI_DRV_WDG_H */
