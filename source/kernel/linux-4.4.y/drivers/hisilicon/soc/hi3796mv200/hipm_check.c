#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <asm/memory.h>
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
#include <linux/fs.h>

#define REG_WAKEUP_DDR_CHECK_EN      (0xF8AB0004)

#define MAX_IOMEM_SIZE               (0x400)
#define INTR_FROM_ACPU_STATUS        (0x408)

/* If ddr wakeup check algorithm is SHA3, check area lenth should be alignment with 136.
Otherwise, if algorithm is hash-256, the checke area lenth should be alignment with 64.
the actually used algorithm can be refered to the file hipm_sleep.S or sleep.S*/
#define  SHA3_BLOCK_SIZE             (136)
#define  HASH_BLOCK_SIZE             (64)

static void *hi_mailbox_base_addr = NULL;

static int get_kernel_info(unsigned int* start_addr, unsigned int* length)
{
	unsigned char* pbuf = NULL;
	unsigned int end_addr = 0;
	struct file* fp = NULL;
	mm_segment_t fs;
	loff_t pos = 0;
	char tmp_buf[32];
	char* pstr = NULL;

	memset(tmp_buf, 0, sizeof(tmp_buf));
	memcpy(tmp_buf, "Kernel code", strlen("Kernel code"));
	tmp_buf[sizeof (tmp_buf) - 1] = '\0';

	memset(&fs, 0, sizeof(mm_segment_t));

	fs = get_fs();
	set_fs(KERNEL_DS);
	set_fs(fs);

	/* get file handle */
	fp = filp_open("/proc/iomem", O_RDONLY | O_LARGEFILE, 0644);
	if (IS_ERR(fp)) {
		return -1;
	}

	pbuf = kmalloc(MAX_IOMEM_SIZE, GFP_TEMPORARY);
	if (pbuf == NULL)  {
		filp_close(fp, NULL);
		return -1;
	}
	memset(pbuf, 0, MAX_IOMEM_SIZE);

	/* get file content */
	pos = 0;
	fs = get_fs();
	set_fs(KERNEL_DS);
	vfs_read(fp, pbuf, MAX_IOMEM_SIZE - 1, &pos);
	set_fs(fs);

	pstr = strstr(pbuf, tmp_buf);
	if (pstr == NULL) {
		kfree(pbuf);
		filp_close(fp, NULL);
		return -1;
	}
	pos = pstr - (char*)pbuf;

	memset(tmp_buf, 0, sizeof(tmp_buf));
	memcpy(tmp_buf, pbuf + pos - 20, 8);
	*start_addr = simple_strtoul(tmp_buf, 0, 16);

	memset(tmp_buf, 0, sizeof(tmp_buf));
	memcpy(tmp_buf, pbuf + pos - 11, 8);
	end_addr = simple_strtoul(tmp_buf, 0, 16);

	*length = end_addr - *start_addr;

	kfree(pbuf);
	/* close file handle */
	filp_close(fp, NULL);

	return 0;
}
static void get_ko_info(unsigned int* start_addr, unsigned int* length)
{
	struct module* p = NULL;
	struct module* mod = NULL;
	struct list_head* pmodules = NULL;
	void *ptr = NULL;
	void *end = NULL;
	unsigned int start_phy_addr = 0;
	unsigned int end_phy_addr = 0;
	unsigned int tmp_phy_addr = 0;
	int flag = 0;

	module_get_pointer(&pmodules);
	list_for_each_entry_rcu(mod, pmodules, list) {
		p = find_module(mod->name);
		if (p) {
			if (0 == flag){
				tmp_phy_addr = page_to_phys(vmalloc_to_page(p->module_core));
				start_phy_addr = tmp_phy_addr;
				end_phy_addr = tmp_phy_addr;
				flag = 1;
			}

			ptr = p->module_core;
			end = p->module_core + p->core_text_size;

			for (; ptr < end; ptr += PAGE_SIZE){
				tmp_phy_addr = page_to_phys(vmalloc_to_page(ptr));
				if (tmp_phy_addr < start_phy_addr)
					start_phy_addr = tmp_phy_addr;
				if (tmp_phy_addr > end_phy_addr)
					end_phy_addr = tmp_phy_addr;
			}
		}
	}

	*start_addr = start_phy_addr;
	*length = end_phy_addr - start_phy_addr + PAGE_SIZE;

	return;
}

static int mailbox_to_smcu(void)
{
	int ret = -1;
	unsigned int kernel_start_addr = 0;
	unsigned int kernel_size = 0;
	unsigned int ko_start_addr = 0;
	unsigned int ko_size = 0;

	if (!scpu_enabled())
		return 0;

	ret = get_kernel_info(&kernel_start_addr, &kernel_size);
	if (0 != ret) {
		return -1;
	}

	//printk("-----------ddr_wakeup_check: kernel_start_addr:0x%x, kernel_size%x \n", kernel_start_addr, kernel_size - kernel_size % SHA3_BLOCK_SIZE + SHA3_BLOCK_SIZE);

	/* send ddr wakeup check area of kernel to smcu */
	while (1) {
	   if (0 == readl(hi_mailbox_base_addr + INTR_FROM_ACPU_STATUS)) {
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_0);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_1);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_2);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_3);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_4);
			/* ddr wakeup check count */
			writel(1, hi_mailbox_base_addr + REG_MAILBOX_ARG_5);
			/* start address of kernel checked area  */
			writel(kernel_start_addr, hi_mailbox_base_addr + REG_MAILBOX_ARG_6);
			/* size of kernel checked area, should be aligned with 136 bytes */
			writel(kernel_size - kernel_size % SHA3_BLOCK_SIZE + SHA3_BLOCK_SIZE, hi_mailbox_base_addr + REG_MAILBOX_ARG_7);
			/* Mailbox to SMCU */
			writel(0x62211f01, hi_mailbox_base_addr + REG_MAILBOX_CMD);
			writel(0x1, hi_mailbox_base_addr + REG_MAILBOX_ACPU_TO_SMCU);

			break;
		}
		udelay(1000);
	}

	get_ko_info(&ko_start_addr, &ko_size);
	//printk("ddr_wakeup_check: ko_start_addr:0x%x, ko_size0x%x \n", ko_start_addr, ko_size - ko_size % SHA3_BLOCK_SIZE + SHA3_BLOCK_SIZE);

	/* send ddr wakeup check area of KO to smcu */
	while (1) {
		if (0 == readl(hi_mailbox_base_addr + INTR_FROM_ACPU_STATUS)) {
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_0);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_1);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_2);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_3);
			writel(0, hi_mailbox_base_addr + REG_MAILBOX_ARG_4);
			/* ddr wakeup check count */
			writel(1, hi_mailbox_base_addr + REG_MAILBOX_ARG_5);
			/* start address of KO checked area  */
			writel(ko_start_addr, hi_mailbox_base_addr + REG_MAILBOX_ARG_6);
			/* size of KO checked area, should be aligned with 136 bytes */
			writel(ko_size - ko_size % SHA3_BLOCK_SIZE + SHA3_BLOCK_SIZE, hi_mailbox_base_addr + REG_MAILBOX_ARG_7);
			/* Mailbox to SMCU */
			writel(0x62211f01, hi_mailbox_base_addr + REG_MAILBOX_CMD);
			writel(0x1, hi_mailbox_base_addr + REG_MAILBOX_ACPU_TO_SMCU);

			break;
		}
		udelay(1000);
	}

	return 0;
}
/*****************************************************************************/
int hipm_wakeup_check(void)
{
	if (0xa0 == (readl(io_address(REG_WAKEUP_DDR_CHECK_EN)) & 0xF0))
		return 0; /* ddr wakeup check is disable */

	if (mailbox_to_smcu() != 0)
		return -1;

	return 0;
}
/*************************************************************************/
static struct syscore_ops hipm_wakeup_check_ops = {
	.suspend	= hipm_wakeup_check,
	.resume		= NULL,
};
static int __init hi_pm_init(void)
{
	hi_mailbox_base_addr = (void __iomem *)ioremap_nocache(MAILBOX_BASE_ADDR, PAGE_SIZE);
	BUG_ON(!hi_mailbox_base_addr);
	printk(KERN_INFO "Register hipm syscore operation\n");
	register_syscore_ops(&hipm_wakeup_check_ops);
	return 0;
}

module_init(hi_pm_init);
