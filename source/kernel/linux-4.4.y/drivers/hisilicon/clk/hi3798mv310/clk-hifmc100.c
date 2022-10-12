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
 * Create By Cai Zhiyong 2014.12.22
 *
******************************************************************************/

#include <linux/clkdev.h>
#include <asm/delay.h>
#include <linux/hisilicon/freq.h>
#include <dt-bindings/clock/hi3716cv200-clock.h>

#include "clk-hisi.h"

/******************************************************************************/

#define CRG224_SPI_NAND_CLK_SEL(_clk)           (((_clk) & 0x7) << 5)
#define CRG224_SPI_NAND_CLK_EN                  (1 << 0)
#define CRG224_SPI_NAND_SOFT_RST_REQ            (1 << 4)
/******************************************************************************/

static struct clk_rate_reg clk_rate_reg_hifmc100 [] = {
	{_12MHz, 0x4 },
	{_37dot5MHz, 0x7 },
	{_62dot5MHz, 0x5 },
	{_75MHz, 0x6 },
	{_100MHz, 0x1 },
	{_125MHz, 0x2 },
	{_150MHz, 0x3 },
	{_200MHz, 0x0 },
	{0 ,0},
};
/******************************************************************************/

static int hiclk_set_rate_hifmc100(struct clk_hw *hw, unsigned long rate,
				   unsigned long parent_rate)
{
	u32 val = 0;
	u32 rate_val = _12MHz;
	u32 rate_reg = 0x04;
	struct hiclk_hw *hihw = to_hiclk_hw(hw);
	struct clk_rate_reg *reg = clk_rate_reg_hifmc100;

	while (reg->rate) {
		if (rate < reg->rate)
			break;
		rate_val = reg->rate;
		rate_reg = reg->regval;
		reg++;
	}

	pr_debug("%s: clk:'%s' want:%luHz real:%dHz, reg:%#x\n",
		__func__, hihw->name, (ulong)rate, (u32)rate_val, rate_reg);

	/* first disable CRG. */
	val = readl(hihw->peri_crgx);
	val &= ~CRG224_SPI_NAND_CLK_EN;
	writel(val, hihw->peri_crgx);
	udelay(10);

	/* then change clk. */
	val &= ~0xe0;
	val |= (rate_reg << 5);
	writel(val, hihw->peri_crgx);
	udelay(10);

	/* last enable CRG. */
	val |= CRG224_SPI_NAND_CLK_EN;
	writel(val, hihw->peri_crgx);

	return 0;
}
/******************************************************************************/

static void hiclk_disable_hifmc100(struct clk_hw *hw)
{
	u32 val = 0;
	struct hiclk_hw *hihw = to_hiclk_hw(hw);

	val = readl(hihw->peri_crgx);
	val &= ~0x1;
	writel(val, hihw->peri_crgx);
}
/******************************************************************************/

static int hiclk_determine_rate_hifmc100(struct clk_hw *hw,
							struct clk_rate_request *req)
{
	return 0;
}
/******************************************************************************/

struct clk_ops clk_ops_hifmc100 = {
	.set_rate = hiclk_set_rate_hifmc100,
	.determine_rate = hiclk_determine_rate_hifmc100,
	.disable = hiclk_disable_hifmc100,
};
/******************************************************************************/
