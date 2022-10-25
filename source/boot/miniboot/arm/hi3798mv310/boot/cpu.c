/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <stddef.h>
#include <cpuinfo.h>
#include <boot.h>
#include <stdio.h>
#include <asm/io.h>

/******************************************************************************/
static int hi3798mv310_boot_media(char **media)
{
	int boot_media;
	unsigned int regval;
	char *boot_media_str = "Unknown";

	/* read from pin */
	boot_media = readl(REG_BASE_PERI_CTRL + REG_START_MODE);
	boot_media = ((boot_media >> NORMAL_BOOTMODE_OFFSET)
		& NORMAL_BOOTMODE_MASK);

	switch (boot_media) {
	case BOOT_FROM_SPI:
		boot_media     = BOOT_MEDIA_SPIFLASH;
		boot_media_str = "SPI Flash";
		break;
	case BOOT_FROM_NAND:
		boot_media     = BOOT_MEDIA_NAND;
		regval = readl(REG_BASE_FMC + REG_FMC_CFG);
		if (regval & REG_FMC_CFG_NFMODE)
			boot_media_str = "SYNC-NAND";
		else
			boot_media_str = "NAND";
		break;
	case BOOT_FROM_SPI_NAND:
		boot_media     = BOOT_MEDIA_SPI_NAND;
		boot_media_str = "SPI-NAND";
		break;
	case BOOT_FROM_EMMC:
		boot_media     = BOOT_MEDIA_EMMC;
		boot_media_str = "eMMC";
		break;
	default:
		boot_media     = BOOT_MEDIA_UNKNOWN;
		boot_media_str = "Unknown";
		uart_early_puts("Unknown boot mode:");
		uart_early_put_hex(boot_media);
		uart_early_puts("\n");
		break;
	}


	if (media)
		*media = boot_media_str;

	return boot_media;
}
/*****************************************************************************/

static void get_hi3798mv310_clock(unsigned int *cpu, unsigned int *timer)
{
	unsigned long FREF = HI3798MV310_OSC_FREQ;

	if (cpu)
		(*cpu) = 0;
	if (timer)
		(*timer) = FREF;
}
/*****************************************************************************/

/* return CHIPSET_CATYPE_NORMAL - normal, CHIPSET_CATYPE_CA - secure */
static int hi3798mv310_get_ca_type(void)
{
	unsigned int id_word;

	id_word = readl(REG_OTP_ID_WORD);

	if (OTP_ID_WORD_VALUE_SECURE == id_word)
		return CHIPSET_CATYPE_CA;
	else
		return CHIPSET_CATYPE_NORMAL;
}
/*****************************************************************************/

static struct cpu_info_t cpu_info[] = {
	{
		.name   = "Unknown",
		.chipid = 0,
		.chipid_mask = ~0,
		.max_ddr_size = 0,
		.boot_media = NULL,
		.get_clock  = NULL,
	},
	{
		.name   = "Hi3798Mv310",
		.chipid = _HI3798M_V310,
		.chipid_mask = _HI3798M_V310_MASK,
#ifdef CONFIG_HI3798MV310_FPGA
		.max_ddr_size = _1G,
#else
		.max_ddr_size = _3G + _750M,
#endif
		.boot_media = hi3798mv310_boot_media,
		.get_clock  = get_hi3798mv310_clock,
	},
	{0},
};
/*****************************************************************************/

int get_cpuno(void)
{
	int cpuno = 0;
	asm("mrc	p15, 0, %0, c0, c0, 5" :"=r"(cpuno) : :"memory");
	return (cpuno & 0x03);
}
/*****************************************************************************/

unsigned int get_timer_clock(void)
{
	return OSC_FREQ;
}

struct cpu_info_t *get_cpuinfo(void)
{
	static struct cpu_info_t *info = NULL;
	long long chipid = get_chipid_reg();

	if (info)
		return info;

	for (info = cpu_info; info->name; info++) {
		if ((info->chipid & info->chipid_mask) ==
		    (chipid & info->chipid_mask))
			return info;
	}

	early_puts("No cpu info found!!\n");

	return cpu_info;
}
