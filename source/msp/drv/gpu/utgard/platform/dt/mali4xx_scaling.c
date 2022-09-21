/*
 * Copyright (C) 2013 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained from Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @file arm_core_scaling.c
 * Example core scaling policy.
 */

#include <linux/mali/mali_utgard.h>
#include <linux/workqueue.h>
#include <linux/module.h>

#include "mali_kernel_common.h"

#include "mali4xx_scaling.h"
#include "mali4xx_cfg.h"

static int num_cores_total;
static int num_cores_enabled;

static struct work_struct wq_work;

static unsigned int utilization_gp_value;
static unsigned int utilization_pp_value;

#ifdef GPU_PP_SCALING_ENABLE
unsigned int mali_pp_scale_cores = 0;
module_param(mali_pp_scale_cores, int, S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(mali_pp_scale_cores, "pp scaling");
#endif

static void set_num_cores(struct work_struct *work)
{
    int err = mali_perf_set_num_pp_cores(num_cores_enabled);

    MALI_DEBUG_ASSERT(0 == err);
    MALI_IGNORE(err);
}

static void enable_fix_num_cores(unsigned int num)
{
	if(num > 0 && num <= num_cores_total)
	{
		num_cores_enabled = num ;
		schedule_work(&wq_work);
		MALI_DEBUG_PRINT(3, ("Core scaling: Enabling %d cores\n", num_cores_enabled));
	}
}

unsigned int gpu_get_pp_scale_cores(void)
{
	return num_cores_enabled ;
}

unsigned int gpu_set_pp_scale_cores(unsigned int num)
{
	if(num > num_cores_total)
	{
		num = num_cores_total ;
	}
	else if(num < 1)
	{
		num = 1;
	}

	enable_fix_num_cores(num);

    return num ;
}

void mali_core_scaling_init(int num_pp_cores)
{
    INIT_WORK(&wq_work, set_num_cores);

    num_cores_total   = num_pp_cores;
    num_cores_enabled = num_pp_cores;
}

void mali_core_scaling_term(void)
{
    flush_scheduled_work();
}

void mali_init_pp_scale_cores(unsigned int num)
{
#ifdef GPU_PP_SCALING_ENABLE
	mali_pp_scale_cores = num ;
#endif
}

void mali_core_scaling_update(struct mali_gpu_utilization_data *data)
{
#ifdef GPU_PP_SCALING_ENABLE
	if( mali_pp_scale_cores != gpu_get_pp_scale_cores() )
	{
		mali_pp_scale_cores = gpu_set_pp_scale_cores(mali_pp_scale_cores);
		if( mali_pp_scale_cores == gpu_get_pp_scale_cores() )
		{
			MALI_DEBUG_PRINT(2, ("pp scale success, cores = %d\n", mali_pp_scale_cores));
		}
		else
		{
			MALI_DEBUG_PRINT(2, ("pp scale failed\n"));
		}
	}
#endif

    utilization_gp_value = data->utilization_gp;
    utilization_pp_value = data->utilization_pp;
}

