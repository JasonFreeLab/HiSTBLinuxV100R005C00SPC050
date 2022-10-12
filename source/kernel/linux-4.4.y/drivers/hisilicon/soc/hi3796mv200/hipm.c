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
#include <linux/irqchip/arm-gic.h>
#include <mach/hardware.h>
#include <linux/hikapi.h>
#include <asm/suspend.h>
#include <asm/bug.h>
#include <asm/io.h>
#include <asm/types.h>

#define CA_DDR_WAKEUPCHECK_START	0xffff2000
#define CA_DDR_WAKEUPCHECK_LENTH	0x2000

void __iomem *hi_sc_virtbase = NULL;
void __iomem *hi_ca_ddrwakeupcheck_virt = NULL;
unsigned long hi_ca_ddrwakeupcheck_phys = CA_DDR_WAKEUPCHECK_START;

/**/
#define MCU_START_CTRL  0xf840f000      /* mcu start control */
#define OTP_IDWORD_ADDR 0xf8ab0060      /* OTP shadow register to indicate if it is advca chipset */
#define OTP_CA_ID_WORD  0x6EDBE953
#define MAILBOX_BASE_ADDR 0xf9a39000


void __iomem *hi_uart_virtbase = NULL;
extern void *hi_otp_idword_addr;
extern void *hi_mcu_start_ctrl;
extern void *hi_mailbox_base_addr;
extern void set_cpu_core_lowpower(void);

asmlinkage int hi_pm_sleep(unsigned long arg);

/*****************************************************************************/

static int hi_pm_suspend(void)
{
	int ret = 0;

	set_cpu_core_lowpower();

	ret = cpu_suspend(0, hi_pm_sleep);

	return ret;
}

static int hi_pm_enter(suspend_state_t state)
{
	int ret = 0;
	switch (state) {
	case PM_SUSPEND_STANDBY:
	case PM_SUSPEND_MEM:
		ret = hi_pm_suspend();
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

int hi_pm_valid(suspend_state_t state)
{
	return 1;
}

static const struct platform_suspend_ops hi_pm_ops = {
	.enter = hi_pm_enter,
	.valid = hi_pm_valid,
};
/*****************************************************************************/

static int __init hi_pm_init(void)
{
	hi_sc_virtbase = (void __iomem *)IO_ADDRESS(REG_BASE_SCTL);
	hi_uart_virtbase = (void __iomem *)IO_ADDRESS(REG_BASE_UART0);

	hi_mcu_start_ctrl = (void __iomem *)ioremap_nocache(MCU_START_CTRL, 0x1000);
	hi_mailbox_base_addr = (void __iomem *)ioremap_nocache(MAILBOX_BASE_ADDR, 0x1000);

	hi_otp_idword_addr = (void __iomem *)ioremap_nocache(OTP_IDWORD_ADDR, 0x1000);
	suspend_set_ops(&hi_pm_ops);

	return 0;
}

module_init(hi_pm_init);
