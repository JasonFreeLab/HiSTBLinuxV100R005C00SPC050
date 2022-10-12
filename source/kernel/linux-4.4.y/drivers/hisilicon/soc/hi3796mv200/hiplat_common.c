
/******************************************************************************
 *  Copyright (C) 2014 Hisilicon Technologies CO.,LTD.
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
 * Create By Hisilicon 2017.5.12
 *
 ******************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/syscore_ops.h>
#include <linux/hikapi.h>
#include <linux/hisilicon/platform.h>

/******************************************************************************/
#define REG_WAKEUP_DDR_CHECK_EN      (0xF8AB0004)

static void __iomem *plat_io_base_virt = NULL;
static ulong plat_io_offset = 0;

int scpu_enabled(void)
{
	if (SCPU_NOT_SUPPORT == (readl(io_address(REG_SCPU_SUPPORT)) & SCPU_SUPPORT_MASK))  {
		return 0;
	}

	return 1;
}

/******************************************************************************/
int is_tee(void)
{
#ifdef REG_SOC_TEE_ENABLE
	if (0x42 != (readl(io_address(REG_SOC_TEE_ENABLE)) >> 8 & 0xFF)) {
		return 1;
	} else {
		return 0;
	}
#else
#ifdef CONFIG_TEE
	return 1;
#else
	return 0;
#endif
#endif
}

static int hipm_clk_off = 1;

static int __init parse_hipm_clkoff(char *str)
{
	hipm_clk_off = 0;

	return 0;
}

early_param("nocpuclkoff", parse_hipm_clkoff);

/******************************************************************************/
/*
 * Set cpu core and PLL to a low clock rate, and so into a low power state
 */
void set_cpu_core_lowpower(void)
{
	if (!hipm_clk_off) {
		printk(KERN_DEBUG "no cpu core clk off\n");
		return;
	}

	if (0xa0 != (readl(io_address(REG_WAKEUP_DDR_CHECK_EN)) & 0xF0))
		return; /* ddr wakeup check is enable */

        writel(0x204,      io_address(REG_BASE_CPU_LP)); //CPU
	udelay(1);
        writel(0x604,      io_address(REG_BASE_CPU_LP)); //CPU to 24M
	udelay(1);

        writel(0,          io_address(REG_PERI_BUS_CLK)); //BUS to 24M
	udelay(1);

        writel(0x0A1030C8, io_address(REG_PERI_APLL2)); //APLL
	udelay(1);
        writel(0x0A1020C8, io_address(REG_PERI_QPLL2)); //QPLL
	udelay(1);
        writel(0x08101025, io_address(REG_PERI_EPLL2)); //EPLL
	udelay(1);
        writel(0x0A102063, io_address(REG_PERI_HPLL2)); //HPLL
	udelay(1);
        writel(0x0A101048, io_address(REG_PERI_VPLL2)); //VPLL
	udelay(1);

	printk(KERN_DEBUG "--Set cpu cort to a low clock rate mode--");
	printk(KERN_DEBUG "CPU_LP=0x%X\n", readl(io_address(REG_BASE_CPU_LP)));
	printk(KERN_DEBUG "BUS_CLK=0x%X\n", readl(io_address(REG_PERI_BUS_CLK)));
	printk(KERN_DEBUG "APLL2=0x%X\n", readl(io_address(REG_PERI_APLL2)));
	printk(KERN_DEBUG "QPLL2=0x%X\n", readl(io_address(REG_PERI_QPLL2)));
	printk(KERN_DEBUG "EPLL2=0x%X\n", readl(io_address(REG_PERI_EPLL2)));
	printk(KERN_DEBUG "HPLL2=0x%X\n", readl(io_address(REG_PERI_HPLL2)));
	printk(KERN_DEBUG "VPLL2=0x%X\n", readl(io_address(REG_PERI_VPLL2)));
	printk(KERN_DEBUG "-----------------------------------------");
}

/******************************************************************************/
void __iomem *io_address(ulong phys_addr)
{
	BUG_ON(!plat_io_offset);
	return (void __iomem *)(phys_addr + plat_io_offset);
}

/******************************************************************************/
static int __init hiplat_common_init(void)
{
	/* Fixed io mapping */
	plat_io_base_virt = ioremap_nocache(PLAT_IO_BASE_PHYS, PLAT_IO_SIZE);
	BUG_ON(!plat_io_base_virt);
	printk(KERN_INFO "Fixed io virt address: %p, phys address: 0x%lX, size: 0x%lX\n",
		plat_io_base_virt, (ulong)PLAT_IO_BASE_PHYS, (ulong)PLAT_IO_SIZE);
	BUG_ON((ulong)plat_io_base_virt < PLAT_IO_BASE_PHYS);
	plat_io_offset = (ulong)plat_io_base_virt - PLAT_IO_BASE_PHYS;

	printk(KERN_INFO "Fixed virt-to-phys Offset: 0x%lX\n", plat_io_offset);

	return 0;
}

/******************************************************************************/
early_initcall(hiplat_common_init);

