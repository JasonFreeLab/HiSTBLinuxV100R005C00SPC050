
/*
 * devfreq governor for utgard GPUs
 *
 * Copyright (c) <2011-2015> HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/errno.h>
#include <linux/module.h>
#include <linux/devfreq.h>
#include <linux/math64.h>
#include "governor.h"

#define GOVERNOR_NAME "gpu_ondemand"

#define DEVFREQ_ERROR_INFO() \
printk("error: func = %s, line = %d\n", __FUNCTION__, __LINE__);

#define DEVFREQ_DEBUG 0
#define DEVFREQ_MAX_VARY 200000000

#define HUNDRED 100

typedef struct para{
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
}para;

static int devfreq_hisilicon_func(struct devfreq *df, unsigned long *freq)
{
	int ret;
	unsigned long busy, total;
	unsigned long next_rate;
	int dvfs_enable;
	unsigned long max_frequency, min_frequency;
	unsigned int max_utilization, min_utilization;
	unsigned int temp_ctrl;

	struct devfreq_dev_status *status;
	struct para *mali_valuable;

	/* (0)Get the info from Mali */
	ret = devfreq_update_stats(df);
	if (ret) {
		DEVFREQ_ERROR_INFO();
		return ret;
	}

	status = &df->last_status;

	mali_valuable = (struct para*)status->private_data;

	dvfs_enable = mali_valuable->dvfs_enable;
	max_frequency = mali_valuable->max_frequency;
	min_frequency = mali_valuable->min_frequency;
	max_utilization = mali_valuable->max_utilization;
	min_utilization = mali_valuable->min_utilization;

	busy = status->busy_time >> 10;
	total = status->total_time >> 10;

	temp_ctrl = mali_valuable->temp_ctrl;

        /* check total, avoid being divided by zero */
	if (total == 0) {
		*freq = status->current_frequency;
		return 0;
	}

        /* (1)Check dvfs enable */
	if (dvfs_enable == 0) {
		*freq = status->current_frequency;
		return 0;
	}

	/* (2)Check the temperature */
	if (temp_ctrl == 1) {
		*freq = (unsigned long)min_frequency;
		return 0;
	}

	/* (3)Compute next rate, base on : Current Freq x Current Utilisation = Next Freq x IdealUtilisation */
	if ((HUNDRED*busy/total < max_utilization) && (HUNDRED*busy/total > min_utilization)) {
		*freq = status->current_frequency;
		return 0;
	}

	next_rate = status->current_frequency;

	next_rate = (next_rate / HUNDRED) * (busy * HUNDRED / total) ;                  /* avoid over precision */

	next_rate = next_rate / (min_utilization + max_utilization) * HUNDRED * 2 ;     /* avoid over precision */

	/* (4)Do not jump large than 200M */
	if (status->current_frequency + DEVFREQ_MAX_VARY < next_rate) {
		next_rate = status->current_frequency + DEVFREQ_MAX_VARY;
	} else if (status->current_frequency - DEVFREQ_MAX_VARY > next_rate) {
		next_rate = status->current_frequency - DEVFREQ_MAX_VARY;
	}

	/* (5)Check the max/min frequency */
	if (next_rate > max_frequency) {
		*freq = max_frequency;
	} else if (next_rate < min_frequency) {
		*freq = min_frequency;
	} else {
		*freq = next_rate;
	}

	if (DEVFREQ_DEBUG & (status->current_frequency != *freq))
		printk("devfreq_hisilicon_func@ CurFreq = %lu, NextFreq = %lu, Utilization = %lu\n",

	status->current_frequency, next_rate, busy*HUNDRED/total);

	return 0;
}

static int devfreq_hisilicon_handler(struct devfreq *devfreq, unsigned int event, void *data)
{
	switch (event)
	{
		case DEVFREQ_GOV_START:
			devfreq_monitor_start(devfreq);
			break;

		case DEVFREQ_GOV_STOP:
			devfreq_monitor_stop(devfreq);
			break;

		case DEVFREQ_GOV_INTERVAL:
			devfreq_interval_update(devfreq, (unsigned int *)data);
			break;

		case DEVFREQ_GOV_SUSPEND:
			devfreq_monitor_suspend(devfreq);
			break;

		case DEVFREQ_GOV_RESUME:
			devfreq_monitor_resume(devfreq);
			break;

		default:
			break;
	}

	if (DEVFREQ_DEBUG)
		printk("devfreq_hisilicon_handler@ event = %d\n", event);

	return 0;
}

static struct devfreq_governor devfreq_hisilicon = {
	.name = GOVERNOR_NAME,
	.get_target_freq = devfreq_hisilicon_func,
	.event_handler = devfreq_hisilicon_handler,
};

static int __init devfreq_hisilicon_init(void)
{
	if (DEVFREQ_DEBUG)
		printk("devfreq_hisilicon_init@\n");

	return devfreq_add_governor(&devfreq_hisilicon);
}
module_init(devfreq_hisilicon_init);

static void __exit devfreq_hisilicon_exit(void)
{
	int ret;

	ret = devfreq_remove_governor(&devfreq_hisilicon);
	if (ret) {
		DEVFREQ_ERROR_INFO();
	}

	if (DEVFREQ_DEBUG)
		printk("devfreq_hisilicon_exit@\n");

	return;
}
module_exit(devfreq_hisilicon_exit);
MODULE_LICENSE("GPL");
