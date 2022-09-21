#ifndef __INIT_EXT_H
#define __INIT_EXT_H

#include "stdint.h"
typedef int32_t (*tc_drv_init_t)(void);

typedef uint64_t (*tc_drv_handle_t)(uint32_t x0,
				    uint32_t x1,
				    uint32_t x2,
				    uint32_t x3,
				    uint32_t x4,
				    void *y1,
				    void *y2,
				    uint32_t z1);


typedef struct tc_drv_desc {
	uint8_t reserve1;
	uint8_t reserve2;
	uint8_t reserve3;
	uint8_t reserve4;
	const char *name;
	tc_drv_init_t init;
	tc_drv_handle_t handle;
} tc_drv_desc_t;

#if (TRUSTEDCORE_PLATFORM_CHOOSE == WITH_DEVCHIP_PLATFORM)
#define PRIORITY_CORE_INIT             5
#define PRIORITY_CORE_INIT_LATE        4
#define PRIORITY_SERVICE_INIT          3
#define PRIORITY_SERVICE_INIT_LATE     2
#define PRIORITY_DRIVER_INIT           1
#define PRIORITY_DRIVER_INIT_LATE      0
#define PRIORITY_HIGHEST               (PRIORITY_CORE_INIT)
#define PRIORITY_LOWEST                (PRIORITY_DRIVER_INIT_LATE)
#endif

#define DECLARE_TC_DRV(_name, _reserve1, _reserve2, _reserve3, _reserve4, _setup, _smch) \
	static const tc_drv_desc_t __drv_desc_ ## _name \
		__attribute__ ((section(".tc_drv_descs"), used)) = { \
			_reserve1, \
			_reserve2, \
			_reserve3, \
			_reserve4, \
			#_name, \
			_setup, \
			_smch }

#endif
