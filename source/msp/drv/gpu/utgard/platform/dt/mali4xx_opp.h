
#ifndef __MALI4XX_OPP__
#define __MALI4XX_OPP__

#ifdef __cplusplus
extern "C" {
#endif

unsigned long opps_get_default_freq(void);

unsigned long opps_get_default_volt(void);

unsigned long opps_get_max_freq(void);

unsigned long opps_get_min_freq(void);

unsigned int opps_get_max_utilization(void);

unsigned int opps_get_min_utilization(void);

int setup_opps(struct device *dev);

int term_opps(struct device *dev);

#ifdef __cplusplus
}
#endif
#endif

