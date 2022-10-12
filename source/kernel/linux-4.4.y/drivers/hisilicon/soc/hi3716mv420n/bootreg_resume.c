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
#include <mach/platform.h>

//#define __DUMP_REG
//#define _REG_DEBUG

#ifdef CONFIG_DDR_TRAINING_V2
extern int ddr_sw_training_if(void *ddrtr_result);
#endif

extern char *boot_bootreg;

void __iomem *reg_base_fmc = NULL;
void __iomem *reg_scpu_support = NULL;
void __iomem *reg_base_peri_ctrl = NULL;
void __iomem *_io_base_virt = NULL;
unsigned long _io_virt_to_phys_offset = 0;

#define CONFIG_UNIFIED_BOOT

#ifndef CONFIG_UNIFIED_BOOT

#define	W_WHETHER_WRITE		(1<<0)
#define	W_WHETHER_PM		(1<<1)
#define	W_WHETHER_BOOT_NORMAL	(1<<2)
#define	W_BIT_OFFSET		(3)
#define	W_BIT_MASK		(0x1f<<W_BIT_OFFSET)
#define W_REG_BIT_OFFSET	(11)
#define W_REG_BIT_MASK		(0x1f<<W_REG_BIT_OFFSET)

#define	R_WHETHER_READ		(W_WHETHER_WRITE<<16)
#define	R_WHETHER_PM		(W_WHETHER_PM<<16)
#define	R_WHETHER_BOOT_NORMAL	(W_WHETHER_BOOT_NORMAL<<16)
#define	R_BIT_OFFSET		(W_BIT_OFFSET+16)
#define	R_BIT_MASK		(W_BIT_MASK<<16)
#define R_REG_BIT_OFFSET	(W_REG_BIT_OFFSET+16)
#define R_REG_BIT_MASK		(W_REG_BIT_MASK<<16)

extern long long get_chipid_reg(void);
extern unsigned int get_ca_vendor_reg(void);
extern void reset_cpu(unsigned long addr);
#if defined(CONFIG_AVS_SUPPORT) && !defined(CONFIG_PMU_DEVICE)
extern void set_core_voltage(void);
#endif

struct regentry {
	unsigned int reg_addr;
	unsigned int value;
	unsigned int delay;
	unsigned int attr;
};

static inline void delay(void)
{
	__asm__ __volatile__("nop");
}

static inline void reg_read(struct regentry *reg, unsigned int *ret)
{
	unsigned int reg_val_r;
	unsigned int bit_start_r;
	unsigned int bit_num_r;

	bit_start_r = ((reg->attr&R_REG_BIT_MASK)>>R_REG_BIT_OFFSET);
	bit_num_r = ((reg->attr&R_BIT_MASK)>>R_BIT_OFFSET)+1;
	reg_val_r = (*(volatile unsigned *) (reg->reg_addr));

	if (32 != bit_num_r) {
		reg_val_r >>= bit_start_r;
		reg_val_r &= ((1<<bit_num_r)-1);
	}

	*ret = ((reg_val_r == reg->value)?0:1);
}

static inline void reg_write(struct regentry *reg)
{
	unsigned int reg_val_w;
	unsigned int delay_2;
	unsigned int bit_start_w;
	unsigned int bit_num_w;

	delay_2 = reg->delay;
	bit_start_w = ((reg->attr&W_REG_BIT_MASK)>>W_REG_BIT_OFFSET);
	bit_num_w = ((reg->attr&W_BIT_MASK)>>W_BIT_OFFSET)+1;
	reg_val_w = (*(volatile unsigned *) (reg->reg_addr));

	if (32 == bit_num_w) {
		reg_val_w = reg->value;
	} else {
		reg_val_w &= (~(((1<<bit_num_w)-1)<<bit_start_w));
		reg_val_w |= (reg->value)<<bit_start_w;
	}
	writel(reg_val_w, (void __iomem *)reg->reg_addr);

	while (delay_2--)
		delay();
}

static inline void read_write(struct regentry *reg, unsigned int pm)
{
	unsigned int ret;
	unsigned int delay_1;

	ret = 0;
	delay_1 = reg->delay;

	if(pm) {
		if(reg->attr&W_WHETHER_PM) {
			reg_write(reg);
		} else if(reg->attr&R_WHETHER_PM) {
			do {
				reg_read(reg,&ret);
				delay();
			} while(ret);

			while (delay_1--)
				delay();
		} else {
			while(delay_1--)
				delay();
		}
	} else {
		if (reg->attr&W_WHETHER_BOOT_NORMAL) {
			reg_write(reg);
		} else if (reg->attr&R_WHETHER_BOOT_NORMAL) {
			do {
				reg_read(reg,&ret);
				delay();
			} while(ret);

			while(delay_1--)
				delay();
		} else {
			while(delay_1--)
				delay();
		}
	}
}

static inline void part_read_write(struct regentry *reg_table, unsigned int pm)
{
	unsigned int i;

	for (i=0;;i++) {
		if ((!reg_table[i].reg_addr) && (!reg_table[i].value)
			&& (!reg_table[i].delay) && (!reg_table[i].attr))
			goto main_end;

		read_write(&reg_table[i],pm);
	}

main_end:
	delay();

}

struct reg_hdr {
	unsigned char ver[16];
	unsigned int item1;
	unsigned int item2;
	unsigned int resverd[2];
};

#ifdef CONFIG_HI3716MV410_FPGA
static void s40v200_fpga_ddrtraining(void)
{
#define DDRC0_BASE		0xF8A30000
#define CFG_DQSG_PHSE		0x8004
#define	CFG_DQSG_CYCL		0x8008

	int i, j, m;
	unsigned int val[4];
	unsigned int magic[4];
	volatile unsigned int *ddr = (volatile unsigned int *)0x100000;

	magic[0] = 0xff;
	magic[1] = 0x00;
	magic[2] = 0x55;
	magic[3] = 0xaa;

	val[0] = 0x00;
	val[1] = 0x5a5a5a5a;
	val[2] = ~0;
	val[3] = 0xa5a5a5a5;

again:
	i = 0;
	for (i = 0; i < 8; i++) {
		writel(0x1111 * i, DDRC0_BASE + CFG_DQSG_CYCL);

		for (j = 0; j < 4; j++)	{
			writel(magic[j], DDRC0_BASE + CFG_DQSG_PHSE);
			delay(); delay(); delay(); delay();
			for (m = 0; m < 4; m++) {
				ddr[0] = val[m];
				ddr[1] = val[m];
				ddr[2] = val[m];
				ddr[3] = val[m];
				ddr[4] = val[m];
				ddr[5] = val[m];
				delay(); delay(); delay(); delay();
				if (ddr[0] != val[m] || ddr[1] != val[m])
					break;
				if (ddr[2] != val[m] || ddr[3] != val[m])
					break;
				if (ddr[4] != val[m] || ddr[5] != val[m])
					break;
				if (ddr[0] != val[m] || ddr[1] != val[m])
					break;
				if (ddr[2] != val[m] || ddr[3] != val[m])
					break;
				if (ddr[4] != val[m] || ddr[5] != val[m])
					break;
			}
			if (m == 4)
				goto success;
		}
	}

	if (i == 8)
		goto again;

success:
	return ;
}
#endif

static void reg_v110_init(unsigned int base, unsigned int pm,
	unsigned int which)
{
	struct reg_hdr *hdr = (struct reg_hdr *)base;
	struct regentry *reg_table;
	unsigned int item1_addr, item2_addr;

	item1_addr = hdr->item1 + base;
	item2_addr = hdr->item2 + base;

	if (which & INIT_REG_ITEM1) {
		if (!pm) {
			/* write random DDR CA */
			writel(readl((void __iomem *)REG_RNG_DATA), (void __iomem *)REG_DDRCA_RANDOM0);
			writel(readl((void __iomem *)REG_RNG_DATA), (void __iomem *)REG_DDRCA_RANDOM1);
		}

		reg_table = (struct regentry *)item1_addr;
		part_read_write(reg_table, pm);

#ifdef CONFIG_HI3716MV410_FPGA
		s40v200_fpga_ddrtraining();
#else
#if defined(CONFIG_AVS_SUPPORT) && !defined(CONFIG_PMU_DEVICE)
		set_core_voltage();
#endif
		#ifdef CONFIG_DDR_TRAINING_V2
		if (!pm) {
			ret = ddr_sw_training_if(0);

			if (ret) {
				reset_cpu(0);
			}
		}
		#endif

#endif

		/* Enable ddrca */
		writel(0, (void __iomem *)REG_DDRCA_EN);
	}

	if (which & INIT_REG_ITEM2) {
		reg_table = (struct regentry *)item2_addr;
		part_read_write(reg_table, pm);
	}
}

/*
 * base - reg base address
 * pm   - is suspend
 *      0 normal
 *      1 pm
 * which - init which item
 *         INIT_REG_ITEM1, INIT_REG_ITEM2
 */
void init_reg(unsigned int base, unsigned int pm, unsigned int which)
{
	char *ver = (char *)base;

	/*
	 * init reg table v1.1.1
	 * 0x312E3176 and 0x0000312E ansi code is "v1.1.1\0\0"
	 */
	if ((*(int *)ver == 0x312E3176) && (*(int *)&ver[4] == 0x0000312E)) {
		reg_v110_init(base, pm, which);
	} else {
		/* the old table, only init when init item1 */
		if (which & INIT_REG_ITEM1)
			part_read_write((struct regentry *)base, pm);
	}
}
#ifdef CONFIG_SHOW_REG_INFO
extern int display_regv110_info(unsigned int base);
extern int display_regunknow_info(unsigned int base);

int display_register_info(unsigned int base)
{
	struct reg_hdr *hdr = (struct reg_hdr *)base;

	if ((*(int *)hdr->ver == 0x312E3176)
	    && (*(int *)&hdr->ver[4] == 0x0000312E)) {
		display_regv110_info(base);
	} else {
		display_regunknow_info(base);
	}
	return base;
}
#endif /* CONFIG_SHOW_REG_INFO */

#else /* CONFIG_UNIFIED_BOOT */

#define REG_MODULE_HEAD_SIZE 2
#define REG_LEN_SIZE         2
#define REG_BASE_SIZE        3
#define REG_CFG_LEN_SIZE     2
#define REG_FMT_SIZE         3
#define REG_TABLE_END_FLAG   0
#define REG_OFFSET_POS       10
#define REG_MAX_LENGTH       8192
#define REG_VERSION_V120     0x30323176  /* v120 */

/* Boot mode */
#define BOOT_MODE_EMMC                  0x6
#define BOOT_MODE_SD                    0x2
#define BOOT_MODE_NAND                  0x1
#define BOOT_MODE_SPI                   0x0

enum mod_type {
	MOD_TYPE_NORMAL = 0,
	MOD_TYPE_SPI,
	MOD_TYPE_NAND,
	MOD_TYPE_EMMC,
	MOD_TYPE_SD,
	MOD_TYPE_BUTT,
};

union reg_module_head {
	struct {
		unsigned char ca_flag : 1;     /* whether execute when ca chip */
		unsigned char normal_flag : 1; /* whether execute when normal(no-ca) chip */
		unsigned char wakeup_flag : 1; /* whether execute when wakeup from standby */
		unsigned char boot_flag : 1;   /* whether execute when power on */
		unsigned char module_type : 4; /* module type, like: spi,nand...  */
	} member;
	unsigned char val;
};

union reg_format {
	struct {
		/* byte 0 */
		unsigned char rw_flag : 1;     /* read or write: 0-write; 1-read */
		unsigned char reserve : 1;
		unsigned char offset : 6;      /* real offset = (offset << 2)*/

		/* byte 1 */
		unsigned char bit_off : 5;     /* bit offset of read/write */
		unsigned char val_len : 3;     /* byte length of val to be read/write: 0-0; 1~3 - 1~3byte; */

		/* byte 2 */
		unsigned char bit_num : 5;     /* bit num of read/write, real bit number = bit_num + 1 */
		unsigned char delay_len : 3;   /* byte length of delay: 0-endless; 1~3 - 1~3byte; */
	} member;
	unsigned char val[3];
};

struct reg_init_param {
	void * buf;
	int pm_flag; /* wakeup flag, 0-normal, 1-wakeup */
	int ca_flag; /* secure chip flag, 0-normal, 1-CA */
	unsigned int ddr_size;
};
/*****************************************************************************/

static inline void delay(unsigned int cnt)
{
	while (cnt--)
		__asm__ __volatile__("nop");
}
/*****************************************************************************/

static unsigned int boottype2modtype(unsigned int boot_type)
{
	int i, size;
	unsigned int array[][2] = {
		{BOOT_MODE_SPI, MOD_TYPE_SPI},
		{BOOT_MODE_NAND, MOD_TYPE_NAND},
		{BOOT_MODE_EMMC, MOD_TYPE_EMMC},
		{BOOT_MODE_SD, MOD_TYPE_SD},
	};

	size = sizeof(array) / sizeof((array)[0]);

	for (i = 0; i < size; i++) {
		if (array[i][0] == boot_type)
			return array[i][1];
	}

	return MOD_TYPE_NORMAL;
}
/*****************************************************************************/

static unsigned int baseaddr_is_valid(unsigned int regaddr)
{
	unsigned int ret = 1;
	unsigned int base = regaddr&0xffffff00;


	if (((base&0xffff0000) == 0xf8a30000)
		|| ((base&0xfffff000) == 0xf8a23000)){
		ret = 0;
	}

	return ret;
}
/*****************************************************************************/

static unsigned int offset_is_valid(unsigned int base)
{
	unsigned char offset = (unsigned char)(base&0xff);
	unsigned int ret = 1;

	if ((base == 0xf8000f04) || (base == 0xf8a20044) ||( base == 0xf8a20820))  {
		ret = 0;
	} else if ((base&0xffffff00) == 0xf8a21000) {
		if ((offset>=0x08)&&(offset<=0x44))
			ret = 0;
	} else if ((base&0xffffff00) == 0xf8000000) {
		if ((offset == 0x00) ||
		(offset == 0x58) ||
		(offset == 0x8c) ||
		(offset == 0x90) ||
		(offset == 0x98) ||
		(offset == 0xc4) ||
		(offset == 0xc8) ||
		(offset == 0xd0))
			ret = 0;
	} else if ((base&0xffffff00) == 0xf8a22100) {
		if ((offset == 0x28) ||
		(offset == 0x58) ||
		(offset == 0x5c) ||
		(offset == 0x60) ||
		(offset == 0x64) ||
		(offset == 0x94) ||
		(offset == 0x34) ||
		(offset == 0xac))
			ret = 0;
	} else if ((base&0xffffff00) == 0xf8a22000) {
		if (((offset>=0x00)&&(offset<=0x14)) ||
		((offset>=0x20)&&(offset<=0x34)) ||
		(offset == 0x48) ||
		(offset == 0x4c) ||
		(offset == 0x54) ||
		(offset == 0x58) ||
		(offset == 0x64) ||
		(offset == 0xa0) ||
		(offset == 0xc8))
			ret = 0;
	}

	return ret;
}

/*****************************************************************************/

static unsigned int bit_is_valid(unsigned int base ,unsigned int val)
{
	unsigned int tmp_val;

 	if (base == 0xf8a22064) {
		tmp_val = readl((void __iomem *)base);
		val &= 0x01fc;
		val |= (tmp_val&0xFFFFFE03);
	} else if (base == 0xf8a20044) {
		tmp_val = readl((void __iomem *)base);
		val &= 0x88FFFFFF;
		val |= (tmp_val&0x77000000);
	} else if (base == 0xf8a20820) {
		tmp_val = readl((void __iomem *)base);
		val &= 0xCCFFFFFF;
		val |= (tmp_val&0x33000000);
	}

	return val;
}
/*****************************************************************************/

static void reg_read_write(unsigned int addr,
		unsigned int val,
		unsigned int wait,
		union reg_format *reg)
{
	unsigned int tmp_val;
	unsigned int bit_num = reg->member.bit_num + 1;
	int forever = 0;

#ifdef _REG_DEBUG
	printk(KERN_DEBUG "\n r/w 0x%X", reg->member.rw_flag);
	printk(KERN_DEBUG " addr 0x%lX", addr);
	printk(KERN_DEBUG " bn 0x%X", reg->member.bit_num);
	printk(KERN_DEBUG " bo 0x%X", reg->member.bit_off);
	printk(KERN_DEBUG " v 0x%X", val);
	printk(KERN_DEBUG " d 0x%X", wait);
#endif

	if (reg->member.rw_flag) { /* read */
		/* if wait == 0, then wait endless */
		if (!wait)
			forever = 1;

		do {
			tmp_val = readl((void __iomem *)addr);
			if (bit_num != 32) {
				tmp_val >>= reg->member.bit_off;
				tmp_val &= ((1<<bit_num)-1);
			}

			/* timeout */
			if (!forever && (0 == wait--))
				break;

			delay(1);
		} while (tmp_val != val);

		if (tmp_val != val) {
			printk("Warning: read reg: 0x%x fail.\n", addr);
		}

	} else { /* write */
		if (bit_num != 32) {
			tmp_val = readl((void __iomem *)addr);
			tmp_val &= (~(((1<<bit_num)-1)<<reg->member.bit_off));
			val = val<<reg->member.bit_off;
			val |= tmp_val;
		}

		val = bit_is_valid(addr, val);
		writel(val, (void __iomem *)addr);

		delay(wait);
	}
}
/*****************************************************************************/

static void reg_parse_register(unsigned char *buf, unsigned int base, int length)
{
	unsigned char *pbuf = buf;
	union reg_format reg;
	unsigned int reg_addr;
	unsigned int val, delay;

	while (pbuf < (buf + length)) {
		reg.val[0] = pbuf[0];
		reg.val[1] = pbuf[1];
		reg.val[2] = pbuf[2];
		pbuf += REG_FMT_SIZE;

		val = delay = 0;

		while (reg.member.val_len--)
			val = (val << 8) | (*pbuf++);

		while (reg.member.delay_len--)
			delay = (delay << 8) | (*pbuf++);

		reg_addr = base + (reg.member.offset<<2);

		if(offset_is_valid(reg_addr))
			reg_read_write((unsigned long)reg_addr + _io_virt_to_phys_offset , val, delay, &reg);
	}
}
/*****************************************************************************/

static void reg_parse_group(unsigned char *buf, int length)
{
	unsigned int base;
	int regcfg_len;
	unsigned char *pbuf = buf;

	while (pbuf < (buf + length)) {
		base = (pbuf[0]<<24) | (pbuf[1]<<16) | (pbuf[2]<<8);
		regcfg_len = (pbuf[3]<<8) | pbuf[4];

		pbuf += REG_BASE_SIZE + REG_CFG_LEN_SIZE;
		if (baseaddr_is_valid(base))
			reg_parse_register(pbuf, base, regcfg_len);
		pbuf += regcfg_len;
	}
}
/******************************************************************************/

int get_boot_mode(void)
{
	int boot_media;

	/* read from pin */
	boot_media = readl(reg_base_peri_ctrl + REG_START_MODE);
	boot_media = ((boot_media >> NORMAL_BOOTMODE_OFFSET)
		& NORMAL_BOOTMODE_MASK);

	return boot_media;
}
/*****************************************************************************/

void init_reg(unsigned int base, unsigned int pm, unsigned int which)
{
	unsigned int regbase = base;
	unsigned int pm_flag = 0;
	unsigned int ca_flag = (0x2a13c812 == readl(reg_scpu_support))? 0:1;
	unsigned int module_type;
	union reg_module_head head;
	int length = 0;
	unsigned short offset = *(unsigned short *)(regbase + REG_OFFSET_POS);
	unsigned char *regbuf = (unsigned char *)(regbase + offset);
	int boot_mode;

	boot_mode = get_boot_mode();
	module_type = boottype2modtype(boot_mode);

	printk("boot_mode=%X, module_type=%X\n",boot_mode, module_type);
#ifdef __DUMP_REG
	{
		unsigned int reg_len = *((unsigned int *)boot_bootreg);
		printk(KERN_INFO "-----------Boot Reg-------------");
		print_hex_dump(KERN_INFO, " ", DUMP_PREFIX_OFFSET, 16, 4,
					boot_bootreg, reg_len, true);
		printk(KERN_INFO "--------------End---------------");
	}
#endif
	while ((REG_TABLE_END_FLAG != (*(unsigned int *)regbuf)) && (length < REG_MAX_LENGTH)) {
		length = (regbuf[2]<<8) | regbuf[3];
		head.val = regbuf[1];
		regbuf += REG_MODULE_HEAD_SIZE + REG_LEN_SIZE;
		if ((!head.member.module_type) || (head.member.module_type == module_type)) {
			if ((head.member.boot_flag & (!pm_flag)) || (head.member.wakeup_flag & pm_flag))
				if ((head.member.normal_flag & (!ca_flag)) || (head.member.ca_flag & ca_flag)) {
					reg_parse_group(regbuf, length);
				}
		}


		length = (length + 3) & (~3);
		regbuf += length;
	}
}
#endif

void bootreg_resume(void)
{
	printk("\nBootreg resume...");
	reg_scpu_support = ioremap_nocache(REG_SCPU_SUPPORT, PAGE_SIZE);
	BUG_ON(!reg_scpu_support);

	reg_base_peri_ctrl = ioremap_nocache(REG_BASE_PERI_CTRL, PAGE_SIZE);
	BUG_ON(!reg_base_peri_ctrl);

	_io_base_virt = ioremap_nocache(PLAT_IO_BASE_PHYS, PLAT_IO_SIZE);
	BUG_ON(!_io_base_virt);

	BUG_ON((ulong)_io_base_virt < PLAT_IO_BASE_PHYS);
	_io_virt_to_phys_offset = (unsigned long)_io_base_virt - PLAT_IO_BASE_PHYS;
	
	init_reg((u32)(boot_bootreg + 4), 0, 0);
	
	iounmap(reg_scpu_support);
	iounmap(reg_base_peri_ctrl);
	iounmap(_io_base_virt);
	
	printk("done!\n");
}

static struct syscore_ops bootreg_pm_syscore_ops = {
	.suspend	= NULL,
	.resume		= bootreg_resume,
};

static int __init bootreg_init(void)
{
	printk(KERN_INFO "Register bootreg syscore ops\n");
	register_syscore_ops(&bootreg_pm_syscore_ops);

	return 0;
}

early_initcall(bootreg_init);
