
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

