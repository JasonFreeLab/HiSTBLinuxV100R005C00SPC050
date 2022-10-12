/******************************************************************************
 *  Copyright (C) 2017 Hisilicon Technologies CO.,LTD.
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
 * Create By Cai Zhiying 2017.2.4
 *
******************************************************************************/

#define pr_fmt(fmt) "hisp804: " fmt

#include <linux/clk.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/cpu.h>
#include <linux/io.h>
#include <linux/smp.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/sched_clock.h>

#define TIMER_LOAD      0x00             /* ACVR rw */
#define TIMER_VALUE     0x04             /* ACVR ro */
#define TIMER_CTRL      0x08             /* ACVR rw */
#define TIMER_CTRL_ONESHOT      (1 << 0) /*  CVR */
#define TIMER_CTRL_32BIT        (1 << 1) /*  CVR */
#define TIMER_CTRL_DIV1         (0 << 2) /* ACVR */
#define TIMER_CTRL_DIV16        (1 << 2) /* ACVR */
#define TIMER_CTRL_DIV256       (2 << 2) /* ACVR */
#define TIMER_CTRL_IE           (1 << 5) /*   VR */
#define TIMER_CTRL_PERIODIC     (1 << 6) /* ACVR */
#define TIMER_CTRL_ENABLE       (1 << 7) /* ACVR */

#define TIMER_INTCLR    0x0c             /* ACVR wo */
#define TIMER_RIS       0x10             /*  CVR ro */
#define TIMER_MIS       0x14             /*  CVR ro */
#define TIMER_BGLOAD    0x18             /*  CVR rw */

struct hisp804_clocksource {
	void __iomem *base;
	struct clocksource clksrc;
};

#define to_hiclksrc(e) \
	container_of(e, struct hisp804_clocksource, clksrc)

static struct hisp804_clocksource hisp804_clksrc;

static void __iomem *hisp804_sched_clock_base;

struct hisp804_clockevent_device {
	struct clock_event_device clkevt;
	struct irqaction action;
	void __iomem *base;
	unsigned long rate;
	unsigned long reload;
	char name[16];
};

#define to_hiclkevt(e) \
	container_of(e, struct hisp804_clockevent_device, clkevt)

static struct hisp804_clockevent_device __percpu *hisp804_clkevt;

/******************************************************************************/

static void hisp804_clocksource_enable(void __iomem *base)
{
	writel(0, base + TIMER_CTRL);
	writel(0xffffffff, base + TIMER_LOAD);
	writel(0xffffffff, base + TIMER_VALUE);
	writel(TIMER_CTRL_32BIT | TIMER_CTRL_ENABLE | TIMER_CTRL_PERIODIC,
		base + TIMER_CTRL);
}
/******************************************************************************/

static void hisp804_clocksource_resume(struct clocksource *cs)
{
	hisp804_clocksource_enable(to_hiclksrc(cs)->base);
}
/******************************************************************************/

static u64 notrace hisp804_sched_clock_read(void)
{
	return ~readl_relaxed(hisp804_sched_clock_base + TIMER_VALUE);
}
/******************************************************************************/

static cycle_t hisp804_clocksource_read(struct clocksource *cs)
{
	return ~(cycle_t)readl_relaxed(to_hiclksrc(cs)->base + TIMER_VALUE);
}
/******************************************************************************/

static void __init hisp804_clocksource_init(void __iomem *base,
					    unsigned long rate)
{
	hisp804_clksrc.base = base;
	hisp804_clksrc.clksrc.name = "hisp804";
	hisp804_clksrc.clksrc.rating = 499;
	hisp804_clksrc.clksrc.read = hisp804_clocksource_read;
	hisp804_clksrc.clksrc.resume = hisp804_clocksource_resume;
	hisp804_clksrc.clksrc.mask = CLOCKSOURCE_MASK(32);
	hisp804_clksrc.clksrc.flags = CLOCK_SOURCE_IS_CONTINUOUS;

	hisp804_clocksource_enable(base);

	clocksource_register_hz(&hisp804_clksrc.clksrc, rate);

	hisp804_sched_clock_base = base;
	sched_clock_register(hisp804_sched_clock_read, 32, rate);
}
/******************************************************************************/

static int hisp804_clockevent_shutdown(struct clock_event_device *clkevt)
{
	struct hisp804_clockevent_device *hiclkevt = to_hiclkevt(clkevt);

	writel(0, hiclkevt->base + TIMER_CTRL);

	return 0;
}
/******************************************************************************/

static int hisp804_clockevent_set_next_event(unsigned long next,
					     struct clock_event_device *clkevt)
{
	unsigned long ctrl;
	struct hisp804_clockevent_device *hiclkevt = to_hiclkevt(clkevt);

	writel(TIMER_CTRL_32BIT, hiclkevt->base + TIMER_CTRL);

	writel(next, hiclkevt->base + TIMER_LOAD);
	writel(next, hiclkevt->base + TIMER_LOAD);

	ctrl = TIMER_CTRL_32BIT |
	       TIMER_CTRL_IE |
	       TIMER_CTRL_ONESHOT |
	       TIMER_CTRL_ENABLE;
	writel(ctrl, hiclkevt->base + TIMER_CTRL);

	return 0;
}
/******************************************************************************/

static int sp804_clockevent_set_periodic(struct clock_event_device *clkevt)
{
	unsigned long ctrl;
	struct hisp804_clockevent_device *hiclkevt = to_hiclkevt(clkevt);

	writel(TIMER_CTRL_32BIT, hiclkevt->base + TIMER_CTRL);

	writel(hiclkevt->reload, hiclkevt->base + TIMER_LOAD);
	writel(hiclkevt->reload, hiclkevt->base + TIMER_LOAD);

	ctrl = TIMER_CTRL_32BIT |
	       TIMER_CTRL_IE |
	       TIMER_CTRL_PERIODIC |
	       TIMER_CTRL_ENABLE;
	writel(ctrl, hiclkevt->base + TIMER_CTRL);

	return 0;
}
/******************************************************************************/

static irqreturn_t hisp804_clockevent_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *clkevt = dev_id;
	struct hisp804_clockevent_device *hiclkevt = to_hiclkevt(clkevt);

	/* clear the interrupt */
	writel(1, hiclkevt->base + TIMER_INTCLR);

	clkevt->event_handler(clkevt);

	return IRQ_HANDLED;
}
/******************************************************************************/

static int hisp804_clockevent_setup(struct hisp804_clockevent_device *hiclkevt)
{
	struct clock_event_device *clkevt = &hiclkevt->clkevt;

	writel(0, hiclkevt->base + TIMER_CTRL);

	BUG_ON(setup_irq(clkevt->irq, &hiclkevt->action));

	irq_force_affinity(clkevt->irq, clkevt->cpumask);

	clockevents_config_and_register(clkevt, hiclkevt->rate, 0xf,
		0x7fffffff);

	return 0;
}
/*****************************************************************************/

static void hisp804_clockevent_stop(struct hisp804_clockevent_device *hiclkevt)
{
	struct clock_event_device *clkevt = &hiclkevt->clkevt;

	pr_info("disable IRQ%d cpu #%d\n", clkevt->irq, smp_processor_id());

	disable_irq(clkevt->irq);

	remove_irq(clkevt->irq, &hiclkevt->action);

	clkevt->set_state_shutdown(clkevt);
}
/******************************************************************************/

static int hisp804_clockevent_cpu_notify(struct notifier_block *self,
					 unsigned long action, void *hcpu)
{
	/*
	 * Grab cpu pointer in each case to avoid spurious
	 * preemptible warnings
	 */
	switch (action & ~CPU_TASKS_FROZEN) {
	case CPU_STARTING:
		hisp804_clockevent_setup(this_cpu_ptr(hisp804_clkevt));
		break;
	case CPU_DYING:
		hisp804_clockevent_stop(this_cpu_ptr(hisp804_clkevt));
		break;
	}

	return NOTIFY_OK;
}
/*****************************************************************************/

static struct notifier_block hisp804_clockevent_cpu_nb = {
	.notifier_call = hisp804_clockevent_cpu_notify,
};
/*****************************************************************************/

static void __init clockevent_init(struct hisp804_clockevent_device *hiclkevt,
				   void __iomem *base, int irq, int cpu,
				   unsigned long rate, unsigned long reload)
{
	struct irqaction *action;
	struct clock_event_device *clkevt;

	hiclkevt->base = base;
	hiclkevt->rate = rate;
	hiclkevt->reload = reload;
	snprintf(hiclkevt->name, sizeof(hiclkevt->name), "clockevent %d", cpu);

	clkevt = &hiclkevt->clkevt;

	clkevt->name = hiclkevt->name;
	clkevt->cpumask = cpumask_of(cpu);
	clkevt->irq = irq;
	clkevt->set_next_event = hisp804_clockevent_set_next_event;
	clkevt->set_state_shutdown = hisp804_clockevent_shutdown;
	clkevt->set_state_periodic = sp804_clockevent_set_periodic;
	clkevt->features = CLOCK_EVT_FEAT_PERIODIC |
			   CLOCK_EVT_FEAT_ONESHOT |
			   CLOCK_EVT_FEAT_DYNIRQ;
	clkevt->rating = 400;

	action = &hiclkevt->action;

	action->name = hiclkevt->name;
	action->dev_id = hiclkevt;
	action->irq = irq;
	action->flags = IRQF_TIMER | IRQF_NOBALANCING;
	action->handler = hisp804_clockevent_timer_interrupt;
}
/******************************************************************************/

static void __init hisp804_timer_init(struct device_node *node)
{
	int ret, irq, ix, nr_cpus;
	struct clk *clk;
	void __iomem *base;
	unsigned long rate, reload;

	hisp804_clkevt = alloc_percpu(struct hisp804_clockevent_device);
	if (!hisp804_clkevt) {
		ret = -ENOMEM;
		pr_err("can't alloc memory.\n");
		goto out;
	}

	clk = of_clk_get(node, 0);
	if (IS_ERR(clk))
		goto out_free;

	clk_prepare_enable(clk);

	rate = clk_get_rate(clk);
	reload = DIV_ROUND_CLOSEST(rate, HZ);

	nr_cpus = of_irq_count(node);
	if (nr_cpus > num_possible_cpus())
		nr_cpus = num_possible_cpus();

	for (ix = 0; ix < nr_cpus; ix++) {
		irq = irq_of_parse_and_map(node, ix);
		base = of_iomap(node, ix + 1);
		if (!base) {
			pr_err("can't iomap timer %d\n", ix);
			while (--ix >= 0)
				iounmap(per_cpu_ptr(hisp804_clkevt, ix)->base);
			goto out_free;
		}

		clockevent_init(per_cpu_ptr(hisp804_clkevt, ix), base, irq,
				ix, rate, reload);
	}

	base = of_iomap(node, 0);
	if (!base) {
		pr_err("can't iomap timer %d\n", 0);
		goto out_unmap;
	}

	hisp804_clocksource_init(base, rate);

	ret = register_cpu_notifier(&hisp804_clockevent_cpu_nb);
	if (ret)
		goto out_notifier;

	hisp804_clockevent_setup(this_cpu_ptr(hisp804_clkevt));

	return;

out_notifier:
	iounmap(base);
out_unmap:
	for (ix = 0; ix < nr_irqs; ix++)
		iounmap(per_cpu_ptr(hisp804_clkevt, ix)->base);
out_free:
	free_percpu(hisp804_clkevt);
out:
	return;
}
CLOCKSOURCE_OF_DECLARE(hisp804, "hisilicon,hisp804",hisp804_timer_init);

