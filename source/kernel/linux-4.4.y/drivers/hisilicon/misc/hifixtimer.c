/*
 *  linux/drivers/clocksource/timer-sp.c
 *
 *  Copyright (C) 1999 - 2003 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/clk.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/sched_clock.h>

#include <clocksource/timer-sp804.h>

#define TIMER_1_BASE	0x00
#define TIMER_2_BASE	0x20

#define TIMER_LOAD	0x00			/* ACVR rw */
#define TIMER_VALUE	0x04			/* ACVR ro */
#define TIMER_CTRL	0x08			/* ACVR rw */
#define TIMER_CTRL_ONESHOT	(1 << 0)	/*  CVR */
#define TIMER_CTRL_32BIT	(1 << 1)	/*  CVR */
#define TIMER_CTRL_DIV1		(0 << 2)	/* ACVR */
#define TIMER_CTRL_DIV16	(1 << 2)	/* ACVR */
#define TIMER_CTRL_DIV256	(2 << 2)	/* ACVR */
#define TIMER_CTRL_IE		(1 << 5)	/*   VR */
#define TIMER_CTRL_PERIODIC	(1 << 6)	/* ACVR */
#define TIMER_CTRL_ENABLE	(1 << 7)	/* ACVR */

#define TIMER_INTCLR	0x0c			/* ACVR wo */
#define TIMER_RIS	0x10			/*  CVR ro */
#define TIMER_MIS	0x14			/*  CVR ro */
#define TIMER_BGLOAD	0x18			/*  CVR rw */

struct hitimer {
	void __iomem *base;
	void __iomem *fix_base;
};

static struct hitimer host = {0};
/******************************************************************************/

static irqreturn_t hi_fixtimer_irq(int irq, void *dev_id)
{
	struct hitimer *host = dev_id;
	unsigned int timer_load, timer_value;

	/* clear the interrupt */
	writel(1, host->base + TIMER_INTCLR);

	timer_load = readl(host->fix_base + TIMER_LOAD);
	timer_value = readl(host->fix_base + TIMER_VALUE);

	if (timer_value > timer_load) {
		printk("LOAD: 0x%08x, VALUE: 0x%08x\n", timer_load, timer_value);

		writel(timer_load, host->fix_base + TIMER_LOAD);

		printk("LOAD: 0x%08x, VALUE: 0x%08x\n", 
			readl(host->fix_base + TIMER_LOAD), 
			readl(host->fix_base + TIMER_VALUE));
	}

	return IRQ_HANDLED;
}
/******************************************************************************/

static struct irqaction hi_fixtimer_irqaction = {
	.name		= "fixtimer",
	.flags		= IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= hi_fixtimer_irq,
	.dev_id		= &host,
};
/******************************************************************************/

static void __init hi_fixtimer_of_init(struct device_node *np)
{
	static bool initialized = false;
	int ret;
	void __iomem *base;
	unsigned long ctrl;
	int irq;
	int val;

	base = of_iomap(np, 0);
	if (WARN_ON(!base))
		return;

	/* Ensure timers are disabled */
	writel(0, base + TIMER_CTRL);
	writel(0, base + TIMER_2_BASE + TIMER_CTRL);

	if (initialized || !of_device_is_available(np))
		goto err;

	irq = irq_of_parse_and_map(np, 0);
	if (irq <= 0)
		goto err;

	ret = of_property_read_u32(np, "timer", &val);
	if (ret) {
		pr_err("no found timer.\n");
		goto err;
	}
	host.fix_base = (void __iomem *)(IO_ADDRESS(val));

	host.base = base;

	writel(0, base + TIMER_CTRL);

	setup_irq(irq, &hi_fixtimer_irqaction);

	writel(0x000750B6, base + TIMER_BGLOAD);
	writel(0x000750B6, base + TIMER_LOAD);

	ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE |
	       TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;

	writel(ctrl, base + TIMER_CTRL);

	initialized = true;

	return;
err:
	iounmap(base);
}
CLOCKSOURCE_OF_DECLARE(hifixtimer, "hisilicon,fixtimer", hi_fixtimer_of_init);
