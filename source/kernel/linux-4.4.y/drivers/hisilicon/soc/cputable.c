/******************************************************************************
 *  Copyright (C) 2015 Hisilicon Technologies CO.,LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiyong 2015.6.25
 *
******************************************************************************/

#include <linux/kernel.h>
#include <linux/hisilicon/cputable.h>

struct cpu_table {
	u64 id;
	u64 mask;
	const char *name;
};

#define _CPU(_id, _mask, _name) \
{.id = _id, .mask = _mask, .name = _name }

static struct cpu_table cpus_table[] = {
	_CPU(_HI3716MV410, _HI3716MV410_MASK, "hi3716mv410"),
	_CPU(_HI3716MV420, _HI3716MV410_MASK, "hi3716mv420"),
	_CPU(_HI3716MV420N, _HI3716MV410_MASK, "hi3716mv420_n"),
	_CPU(_HI3716MV410N, _HI3716MV410_MASK, "hi3716mv410_n"),
	_CPU(_HI3798MV100, _HI3798MV100_MASK, "hi3798mv100"),
	_CPU(_HI3796MV100, _HI3798MV100_MASK, "hi3796mv100"),
	_CPU(_HI3798CV200, _HI3798CV200_MASK, "hi3798cv200"),
	_CPU(_HI3798MV200, _HI3798MV200_MASK, "hi3798mv200"),
	_CPU(_HI3798MV300, _HI3798MV200_MASK, "hi3798mv300"),
	_CPU(_HI3796MV200_21X21, _HI3796MV200_MASK, "hi3796mv200(21x21)"),
	_CPU(_HI3796MV200_15X15, _HI3796MV200_MASK, "hi3796mv200(15x15)"),
	_CPU(_HI3716MV450, _HI3796MV200_MASK, "hi3716mv450"),
	_CPU(_HI3798MV310, _HI3798MV310_MASK, "hi3798mv310"),
	_CPU(_HI3798MV300_H, _HI3798MV310_MASK, "hi3798mv310h"),
	_CPU(0, 0, "Unknown CPU"),
};

static struct cpu_table *cpu_table = NULL;
/******************************************************************************/

const char *get_cpuname(void)
{
	if (!cpu_table) {
		int ix;

		get_chipid(0);

		for (ix = 0; ; ix++) {
			cpu_table = &cpus_table[ix];
			if (!cpu_table->id)
				break;
			if ((cpu_chipid & cpu_table->mask) == cpu_table->id)
				break;
		}
	}

	return cpu_table->name;
}
/******************************************************************************/

static int __init show_cpuname(void)
{
	printk("CPU: %s\n", get_cpuname());
	return 0;
}
early_initcall(show_cpuname);
