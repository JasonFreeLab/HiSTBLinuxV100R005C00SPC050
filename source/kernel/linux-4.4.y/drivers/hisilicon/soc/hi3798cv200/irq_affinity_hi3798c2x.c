/******************************************************************************
 *  Copyright (C) 2016 Cai Zhiyong
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
 * Create By Cai Zhiying 2016.1.26
 *
******************************************************************************/

#define pr_fmt(fmt) "irq_affinity: " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cpumask.h>
#include <linux/interrupt.h>

struct irq_affinity {
	unsigned int irq; /* peripheral interrupt, the first is 0, DONOT add 32 */
	unsigned int cpuid;
};

static struct irq_affinity irq_affinity_hi3798c2x[] = {
	{66, 2}, /* USB2HOST0_EHCI */
	{67, 2}, /* USB2HOST0_OHCI */
	{68, 2}, /* USB2OTG */
	{69, 2}, /* USB3_0 */
	{72, 2}, /* GSF1 */
};

static int __init init_irq_affinity(void)
{
	int ret;
	int nr_irqaff = ARRAY_SIZE(irq_affinity_hi3798c2x);

	while (nr_irqaff-- > 0) {
		struct irq_affinity *ia = &irq_affinity_hi3798c2x[nr_irqaff];

		if (ia->cpuid > nr_cpu_ids) {
			pr_warn("cpuid out of range. irq:%d cpuid:%d\n", ia->irq, ia->cpuid);
			continue;
		}

		ret = irq_set_affinity(ia->irq + 32, cpumask_of(ia->cpuid));
		if (ret)
			pr_warn("irq_set_affinity failed. irq:%d cpuid:%d\n", ia->irq, ia->cpuid);
	}

	return 0;
}
late_initcall(init_irq_affinity);

