#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <asm/memory.h>
#include <asm/cpuidle.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/kmemleak.h>
#include <linux/device.h>
#include <asm/suspend.h>
#include <asm/bug.h>
#include <asm/io.h>
#include <asm/types.h>
#include <linux/syscore_ops.h>
#include <linux/hikapi.h>
#include <linux/hisilicon/platform.h>

extern void set_cpu_core_lowpower(void);

void *hi_mailbox_base_addr = NULL;

int mailbox_to_smcu(void)
{
	if (!scpu_enabled())
		return 0;

	if (!is_tee())
		return 0;

	printk(KERN_INFO "Mailbox REE info to SMCU");
	/* CEP */
	writel(virt_to_phys(cpu_resume), hi_mailbox_base_addr + REG_MAILBOX_ARG_0);
	/* REE CEP */
	writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_1);
	/* DDR SHA Algorithm */
	writel(SHA_3, hi_mailbox_base_addr + REG_MAILBOX_ARG_2);
	/* aarch64 */
	writel(1, hi_mailbox_base_addr + REG_MAILBOX_ARG_3);
	/* REE CEP Flag */
	writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_4);
	/* Count */
	writel(1, hi_mailbox_base_addr + REG_MAILBOX_ARG_5);
	/* REE Resume Address */
	writel(virt_to_phys(cpu_resume), hi_mailbox_base_addr + REG_MAILBOX_ARG_6);
	/* size of REE Resume code area */
	writel(0x220000, hi_mailbox_base_addr + REG_MAILBOX_ARG_7);
	/* Mailbox to SMCU */
	writel(0x62211f01, hi_mailbox_base_addr + REG_MAILBOX_CMD);
	writel(0x1, hi_mailbox_base_addr + REG_MAILBOX_ACPU_TO_SMCU);

	return 0;
}
/*****************************************************************************/
int hipm_suspend(void)
{
	if (mailbox_to_smcu() != 0)
		return -1;

	set_cpu_core_lowpower();

	return 0;
}
/*************************************************************************/
static struct syscore_ops hipm_syscore_ops = {
	.suspend	= hipm_suspend,
	.resume		= NULL,
};
static int __init hi_pm_init(void)
{
	hi_mailbox_base_addr = (void __iomem *)ioremap_nocache(MAILBOX_BASE_ADDR, PAGE_SIZE);
	BUG_ON(!hi_mailbox_base_addr);
	printk(KERN_INFO "Register hipm syscore operation\n");
	register_syscore_ops(&hipm_syscore_ops);
	return 0;
}

module_init(hi_pm_init);
