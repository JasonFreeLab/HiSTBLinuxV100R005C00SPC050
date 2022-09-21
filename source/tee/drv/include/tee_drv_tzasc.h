#ifndef _TEE_DRV_TZASC_H_
#define _TEE_DRV_TZASC_H_

typedef struct tzasc_region {
	int en;
	unsigned long long base;
	unsigned long long size;
	unsigned int sp;
	unsigned int mid_en;
	unsigned int mid_w;
	unsigned int mid_r;
} st_tzasc_region;

typedef struct tzasc_share_region {
	int en;
	unsigned long long base;
	unsigned long long size;
	unsigned int master_type0;
} st_tzasc_share_region;

#define TZASC_RIGHT_NONE          (0x5a)
#define TZASC_RIGHT_NON_SEC       (0xa5)
#define TZASC_RIGHT_SEC           (0x8a)
#define TZASC_RIGHT_FULL          (0xa8)

void tee_drv_tzasc_init(void);
void tee_drv_tzasc_enable(void);
void tee_drv_tzasc_config_res_region(unsigned int sp, unsigned int mid);
void tee_drv_tzasc_add_region(st_tzasc_region *region);
void tee_drv_tzasc_add_share_region(st_tzasc_share_region *region);
void tee_drv_tzasc_config_tzpc(void);
void tee_drv_tzasc_security_check(void);
void tee_drv_tzasc_get_share_region_end(unsigned long long *addr);
#endif /* _TEE_DRV_TZASC_H_ */
