

#ifndef __MALI4XX_DT__
#define __MALI4XX_DT__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mali_config{
    int dvfs_enable;
    unsigned long max_frequency;
    unsigned long min_frequency;
    unsigned int max_utilization;
    unsigned int min_utilization;

    unsigned int temp_ctrl;

    unsigned long long time_busy_gp;
    unsigned long long time_idle_gp;
    unsigned long long time_busy_pp;
    unsigned long long time_idle_pp;
}mali_config;

struct device * mali_adp_get_device(void);

int mali_adp_get_powerstatus(void);

int mali_adp_get_dvfsstatus(void);

void* mali_adp_get_configuration(struct mali_device *mdev);

int mali_ext_set_freq_and_volt(int freq, int volt, int dvfs_enable);

int mali_ext_set_max_freq(int freq);

#ifdef __cplusplus
}
#endif
#endif

