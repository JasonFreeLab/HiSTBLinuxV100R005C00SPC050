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

#include <linux/delay.h>
#include <linux/clkdev.h>
#include <linux/hisilicon/freq.h>
#include <dt-bindings/clock/hi3796mv200-clock.h>

#include "clk-hisi.h"

/* 00 PCIE,01 USB3.0,10 SATA */
#define COMBPHY1_SEL_MASK                (BIT(11) | BIT(12))
#define COMBPHY1_SEL_SATA                 BIT(12)

#define SATA_SRST_REQ                     BIT(11)
#define SATA_RX_SRST_REQ                  BIT(10)
#define SATA_CKO_ALIVE_SRST_REQ           BIT(9)
#define SATA_BUS_SRST_REQ                 BIT(8)

#define SATA_TX_CKEN                      BIT(3)
#define SATA_CKO_ALIVE_CKEN               BIT(2)
#define SATA_RX_CKEN                      BIT(1)
#define SATA_BUS_CKEN                     BIT(0)

#define PERI_CTRL                        (0x0008)
/******************************************************************************/

static int hiclk_enable_hiahci(struct clk_hw *hw)
{
	struct hiclk_hw *clk = to_hiclk_hw(hw);
	u32 reg, mux;

	mux = readl(clk->peri_ctrl_base + PERI_CTRL);
	mux &= COMBPHY1_SEL_MASK;

	if (mux != COMBPHY1_SEL_SATA) {
		return -1;
	}

	/* enable phy clock BPLL 25MHz*/
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &= (~0xff00);
	reg |= (0x1<<8);
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(200);

	/* enable sata controller clock */
	reg = readl(clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	reg |= (SATA_TX_CKEN
		|SATA_CKO_ALIVE_CKEN
		|SATA_RX_CKEN
		|SATA_BUS_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	udelay(200);

	/* cancel control reset */
	reg = readl(clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	reg &= ~(SATA_SRST_REQ
		|SATA_RX_SRST_REQ
		|SATA_CKO_ALIVE_SRST_REQ
		|SATA_BUS_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	udelay(200);

	return 0;
}
/******************************************************************************/

static void hiclk_disable_hiahci(struct clk_hw *hw)
{
	struct hiclk_hw *clk = to_hiclk_hw(hw);
	u32 reg, mux;

	//TODO: make sure if combphy1 connected
	mux = readl(clk->peri_ctrl_base + PERI_CTRL);
	mux &= COMBPHY1_SEL_MASK;

	if (mux != COMBPHY1_SEL_SATA) {
		return;
	}

	/* control reset */
	reg = readl(clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	reg |= (SATA_SRST_REQ
		|SATA_RX_SRST_REQ
		|SATA_CKO_ALIVE_SRST_REQ
		|SATA_BUS_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	udelay(200);

	/* close sata controller clock */
	reg = readl(clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	reg &= ~(SATA_TX_CKEN
		|SATA_CKO_ALIVE_CKEN
		|SATA_RX_CKEN
		|SATA_BUS_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG42_SATA3CTRL);
	udelay(200);

	/* disable phy clock */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &= (~0xff00);
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(200);
}
/******************************************************************************/

struct clk_ops clk_ops_hiahci = {
	.enable =	hiclk_enable_hiahci,
	.disable = hiclk_disable_hiahci,
};
