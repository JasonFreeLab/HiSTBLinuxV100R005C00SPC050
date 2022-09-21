#ifndef _TEE_DRV_TZASC_HAL_H_
#define _TEE_DRV_TZASC_HAL_H_

#include "tee_drv_tzasc.h"

void tzasc_hal_init(void);
void tzasc_hal_enable(void);
void tzasc_hal_config_res_region(unsigned int sp, unsigned int mid);
void tzasc_hal_add_region(st_tzasc_region *region);
void tzasc_hal_add_share_region(st_tzasc_share_region *region);
void tzasc_hal_config_tzpc(void);
void tzasc_hal_security_check(void);
void tzasc_hal_get_share_region_end(unsigned long long *addr);

#endif /* _TEE_DRV_TZASC_HAL_H_ */
