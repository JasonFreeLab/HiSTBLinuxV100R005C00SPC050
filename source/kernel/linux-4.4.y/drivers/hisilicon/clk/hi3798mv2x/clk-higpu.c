
/*
 * devfreq clock for utgard GPUs
 *
 * Copyright (c) <2011-2015> HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <dt-bindings/clock/hi3798mv200-clock.h>
#include <linux/hikapi.h>

#include <linux/of.h>
#include <linux/of_address.h>
#include "clk-hisi.h"

#define CLOCK_ERROR_INFO() \
	printk("error: func = %s, line = %d\n", __FUNCTION__, __LINE__);

#define CLOCK_DEBUG 0

typedef enum
{
	CRG_REG_ADDR_SOFTRESET = 0x00d4,
	CRG_REG_ADDR_LOWPOWER = 0x0124
}crg_register_addr;

typedef enum
{
	PMC_REG_ADDR_FREQ = 0x0034,
	PMC_REG_ADDR_CNTBYPASS = 0x0090
}pmc_register_addr;

typedef enum
{
	CRG_REG_MASK_ENABLE = 0x1,
	CRG_REG_MASK_ENABLE_PP0 = (0x1 << 8),
	CRG_REG_MASK_ENABLE_PP1 = (0x1 << 9),
	CRG_REG_MASK_ENABLE_PP2 = (0x1 << 10),
	CRG_REG_MASK_ENABLE_PP3 = (0x1 << 11),

	CRG_REG_MASK_RESET = (0x1 << 4),
	CRG_REG_MASK_FREQ_SEL = 0x7
}crg_register_mask;

typedef enum
{
	PMC_REG_MASK_CNT_BYPASS = 0x1,
	PMC_REG_MASK_FSM_ENABLE = (0x1 << 20),
	PMC_REG_MASK_WAIT_POWER_GOOD_MASK = 0xffff,
	PMC_REG_MASK_WAIT_POWER_GOOD_VALUE = 0x2fff,
	PMC_REG_MASK_WAIT_POWER_GOOD_CPU = (0x1 << 16),
	PMC_REG_MASK_BEGIN_CFG_BYPASS = (0x1 << 9),
	PMC_REG_MASK_FREQ_SW_TREND = (0x1 << 18),
	PMC_REG_MASK_FREQ_SW_REQUSET = (0x1 << 21)
}pmc_register_mask;

struct pll_table {
	unsigned long rate;
	int value;
};

struct device_node *pmc_node;
void __iomem *pmc_base;

static struct pll_table gpu_pll_table[] = {
	{200000000, 0x7},
	{300000000, 0x4},
	{400000000, 0x1},
	{500000000, 0x6},
	{600000000, 0x3},
	{675000000, 0x5},
	{750000000, 0x2},
	{800000000, 0x0}
};

static struct pll_table gpu_pll_table_98mv300[] = {
	{200000000, 0x7},
	{300000000, 0x4},
	{400000000, 0x1},
	{500000000, 0x6},
	{540000000, 0x0},
	{600000000, 0x3},
	{675000000, 0x5},
	{860000000, 0x2}
};

static struct pll_table gpu_pll_table_youtube[] = {
        {200000000, 0x7},
        {300000000, 0x4},
        {400000000, 0x1},
        {500000000, 0x6},
        {600000000, 0x3},
        {675000000, 0x5},
        {800000000, 0x0}
};

static int CLOCK_MAX_FREQ_NUM = (sizeof(gpu_pll_table)/sizeof(gpu_pll_table[0]));

/************ private function ************/

static void hisi_gpu_update_vmin_table(void)
{
#define SYSID_REG_ADDR_BASE   (0xf8000ee0)
#define SYSID_REG_ADDR_SIZE   (0x1000)
#define SYSID_REG_VERTION300  (0x37980210)
#define MODEID_REG_ADDR_BASE  (0xf8a22030)
#define MODEID_REG_ADDR_SIZE  (0x1000)
#define MODEID_REG_YOUTUBE    (0x12560418)
	unsigned int *chip_info = (unsigned int*)ioremap_nocache(SYSID_REG_ADDR_BASE, SYSID_REG_ADDR_SIZE);
	unsigned int *chip_mode = (unsigned int*)ioremap_nocache(MODEID_REG_ADDR_BASE, MODEID_REG_ADDR_SIZE);

	if (*chip_info == SYSID_REG_VERTION300) {
		memcpy(gpu_pll_table, gpu_pll_table_98mv300, sizeof(gpu_pll_table_98mv300));
	}

	if ((*chip_mode & 0xffffffff) == MODEID_REG_YOUTUBE) {
		CLOCK_MAX_FREQ_NUM = 7;
		memcpy(gpu_pll_table, gpu_pll_table_youtube, sizeof(gpu_pll_table_youtube));
	}

	iounmap(chip_info);
	iounmap(chip_mode);

	if (CLOCK_DEBUG)
		printk("hisi_gpu_update_vmin_table@\n");
}

static void hisi_gpu_clk_on(struct clk_hw *hw)
{
	unsigned int value;
	struct hiclk_hw *clock = to_hiclk_hw(hw);

	value = readl(clock->peri_crg_base + CRG_REG_ADDR_SOFTRESET);
	value |= CRG_REG_MASK_ENABLE | CRG_REG_MASK_ENABLE_PP0 | CRG_REG_MASK_ENABLE_PP1;
	writel(value, clock->peri_crg_base + CRG_REG_ADDR_SOFTRESET);

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_on@\n");
}

static void hisi_gpu_clk_off(struct clk_hw *hw)
{
	unsigned int value;
	struct hiclk_hw *clock = to_hiclk_hw(hw);

	value = readl(clock->peri_crg_base + CRG_REG_ADDR_SOFTRESET);
	value &= ~(CRG_REG_MASK_ENABLE | CRG_REG_MASK_ENABLE_PP0 | CRG_REG_MASK_ENABLE_PP1);
	writel(value, clock->peri_crg_base + CRG_REG_ADDR_SOFTRESET);

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_off@\n");
}

static void hisi_gpu_clk_reset(struct clk_hw *hw)
{
	unsigned int value;
	struct hiclk_hw *clock = to_hiclk_hw(hw);

	/* reset */
	value = readl(clock->peri_crg_base + CRG_REG_ADDR_SOFTRESET);
	value |= CRG_REG_MASK_RESET;
	writel(value, clock->peri_crg_base + CRG_REG_ADDR_SOFTRESET);

	udelay(1);

	/* cancel reset */
	value &= ~CRG_REG_MASK_RESET;
	writel(value, clock->peri_crg_base + CRG_REG_ADDR_SOFTRESET);

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_reset@\n");
}

static int hisi_gpu_clk_get_index(unsigned int rate)
{
	int index;

	for (index = 0; index < CLOCK_MAX_FREQ_NUM; index++) {
		if (gpu_pll_table[index].rate == rate) {
			/*if(CLOCK_DEBUG)
				printk("hisi_gpu_clk_get_index@ index = %d\n", index);*/

			return index;
		}
	}

	CLOCK_ERROR_INFO();

	return -1;
}

static unsigned long hisi_gpu_clk_get_rate(struct clk_hw *hw)
{
	unsigned int i, value;
	struct hiclk_hw *clock = to_hiclk_hw(hw);

	value = readl(clock->peri_crg_base + CRG_REG_ADDR_LOWPOWER);
	value &= CRG_REG_MASK_FREQ_SEL;

	for (i = 0; i < CLOCK_MAX_FREQ_NUM; i++) {
		if (gpu_pll_table[i].value == value) {
			if (CLOCK_DEBUG)
				printk("hisi_gpu_clk_get_rate@ Freq = %ld\n", gpu_pll_table[i].rate);

			return gpu_pll_table[i].rate;
		}
	}

	CLOCK_ERROR_INFO();

	return 0;
}

static void hisi_gpu_pmc_node_create(void)
{
	pmc_node = of_find_compatible_node(NULL, NULL, "hisilicon,hi3798mv200-volt");
	if (NULL == pmc_node) {
		CLOCK_ERROR_INFO();
		return;
	}

	pmc_base = of_iomap(pmc_node, 0);
	if (NULL == pmc_base) {
		CLOCK_ERROR_INFO();
		of_node_put(pmc_node);
		return;
	}

	if (CLOCK_DEBUG)
		printk("hisi_gpu_pmc_node_create@\n");
}

static void hisi_gpu_pmc_node_destroy(void)
{
	iounmap(pmc_base);
	of_node_put(pmc_node);

	pmc_base = NULL;
	pmc_node = NULL;

	if (CLOCK_DEBUG)
		printk("hisi_gpu_pmc_node_destroy@\n");
}

static void hisi_gpu_pmc_init(struct clk_hw *hw)
{
	unsigned int value;
	struct hiclk_hw *clock = to_hiclk_hw(hw);

	value = readl(pmc_base + PMC_REG_ADDR_CNTBYPASS);
	value &= ~PMC_REG_MASK_CNT_BYPASS;              /* use cnt */
	writel(value, pmc_base + PMC_REG_ADDR_CNTBYPASS);

	value = readl(pmc_base + PMC_REG_ADDR_FREQ);
	value |= PMC_REG_MASK_FSM_ENABLE;               /* use hardware status machine */
	value &= ~PMC_REG_MASK_WAIT_POWER_GOOD_MASK;    /* clear power good value */
	value |= PMC_REG_MASK_WAIT_POWER_GOOD_VALUE;    /* set power good value */
	value &= ~PMC_REG_MASK_WAIT_POWER_GOOD_CPU;     /* use hardware power good signal */
	writel(value, pmc_base + PMC_REG_ADDR_FREQ);

	value = readl(clock->peri_crg_base + CRG_REG_ADDR_LOWPOWER);    /* status machine output signal */
	value &= ~PMC_REG_MASK_BEGIN_CFG_BYPASS;
	writel(value, clock->peri_crg_base + CRG_REG_ADDR_LOWPOWER);

	if (CLOCK_DEBUG)
		printk("hisi_gpu_pmc_init@\n");
}

/************ plugin function ************/

static int hisi_gpu_clk_prepare(struct clk_hw *hw)
{
	hisi_gpu_update_vmin_table();

	hisi_gpu_pmc_node_create();

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_prepare@\n");

	return 0;
}


static void hisi_gpu_clk_unprepare(struct clk_hw *hw)
{
	hisi_gpu_pmc_node_destroy();

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_unprepare@\n");
}

static int hisi_gpu_clk_enable(struct clk_hw *hw)
{
	hisi_gpu_clk_on(hw);

	hisi_gpu_clk_reset(hw);

	hisi_gpu_pmc_init(hw);

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_enable@\n");

	return 0;
}


static void hisi_gpu_clk_disable(struct clk_hw *hw)
{
	hisi_gpu_clk_off(hw);

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_disable@\n");
}

static int hisi_gpu_clk_set_rate(struct clk_hw *hw, unsigned long rate, unsigned long parent_rate)
{
	unsigned int pmc_value, crg_vale, index;
	unsigned long old_rate;
	struct hiclk_hw *clock = to_hiclk_hw(hw);

	index = hisi_gpu_clk_get_index(rate);

	if (-1 == index) {
		CLOCK_ERROR_INFO();
		return -1;
	}

	old_rate = clock->rate;

	/* (1)judge increase or decrease frequency */
	pmc_value = readl(pmc_base + PMC_REG_ADDR_FREQ);

	if (rate > old_rate) {
		pmc_value |= PMC_REG_MASK_FREQ_SW_TREND;
	} else {
		pmc_value &= ~PMC_REG_MASK_FREQ_SW_TREND;
	}

	writel(pmc_value, pmc_base + PMC_REG_ADDR_FREQ);

	/* (2)set frequency */
	crg_vale = readl(clock->peri_crg_base + CRG_REG_ADDR_LOWPOWER);

	crg_vale &= ~CRG_REG_MASK_FREQ_SEL;
	crg_vale |= gpu_pll_table[index].value;

	writel(crg_vale, clock->peri_crg_base + CRG_REG_ADDR_LOWPOWER);

	/* (3)frequency request and canel frequency request */
	pmc_value |= PMC_REG_MASK_FREQ_SW_REQUSET;
	writel(pmc_value, pmc_base + PMC_REG_ADDR_FREQ);

	pmc_value &= ~PMC_REG_MASK_FREQ_SW_REQUSET;
	writel(pmc_value, pmc_base + PMC_REG_ADDR_FREQ);

	clock->rate = rate;

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_set_rate@ cur = %lu, next = %lu\n", old_rate, rate);

	return 0;
}

static unsigned long hisi_gpu_clk_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct hiclk_hw *clock = to_hiclk_hw(hw);
	unsigned long rate = hisi_gpu_clk_get_rate(hw);

	if (0 == rate) {
		CLOCK_ERROR_INFO();
		return -1;
	}

	clock->rate = rate;

	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_recalc_rate@ Freq = %ld\n", rate);

	return rate;
}

static long hisi_gpu_clk_round_rate(struct clk_hw *hw, unsigned long rate, unsigned long *parent_rate)
{
	if (CLOCK_DEBUG)
		printk("hisi_gpu_clk_round_rate@ next = %lu\n", rate);

	return rate;
}

struct clk_ops clk_ops_higpu = {
	.prepare = hisi_gpu_clk_prepare,
	.unprepare = hisi_gpu_clk_unprepare,
	.enable = hisi_gpu_clk_enable,
	.disable = hisi_gpu_clk_disable,
	.set_rate = hisi_gpu_clk_set_rate,
	.recalc_rate = hisi_gpu_clk_recalc_rate,
	.round_rate = hisi_gpu_clk_round_rate,
};

