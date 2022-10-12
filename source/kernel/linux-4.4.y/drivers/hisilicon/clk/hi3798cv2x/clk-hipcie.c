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
 * Create By Liu Hui 2015.07.10
 *
******************************************************************************/

#include <linux/delay.h>
#include <dt-bindings/clock/hi3798cv200-clock.h>
#include <linux/hikapi.h>

#include "clk-hisi.h"
/******************************************************************************/
static u32 gpio_regbase[14] = {
	0xf8b20000, 0xf8b21000, 0xf8b22000, 0xf8b23000,
	0xf8b24000, 0xf8004000, 0xf8b26000, 0xf8b27000,
	0xf8b28000, 0xf8b29000, 0xf8b2a000, 0xf8b2b000,
	0xf8b2c000, 0xf8b2d000
};

#define PCIE_GPIO_MAX                    (0x0C)
#define PCIE_GPIO_NUM_MASK               (0x07)

#define PERI_CTRL                        (0x0008)
#define PERI_COMBPHY1_CFG                (0x858)

#define COMBPHY1_REF_CKEN                BIT(8)
#define COMBPHY1_SRST_REQ                BIT(12)
#define COMBPHY1_RSTN_SEL_CTRL           BIT(13)
#define COMBPHY1_REFCLK_SEL             (0x3<<10)

#define COMBPHY1_SEL_MASK               (BIT(11) | BIT(12))
#define COMBPHY1_SEL_PCIE                0

#define NANO_BYPASS_CODEC                BIT(31)
#define NANO_BUFFER_MODE                 BIT(28)
#define NANO_TEST_WRITE                  BIT(24)
#define NANO_TEST_DATA                   (0xf<<20)
#define NANO_TEST_ADDR                   (0x1f<<12)
#define NANO_RX_STANDBY                  BIT(11)
#define NANO_TXDEEMPH_2                  BIT(5)
#define NANO_TX_PATTERN                  (0x3<<2)
#define CLKREF_OUT_IEN                   BIT(1)
#define CLKREF_OUT_OEN                   BIT(0)

#define PCIE0_BUS_CKEN                   BIT(0)
#define PCIE0_SYS_CKEN                   BIT(1)
#define PCIE0_PIPE_CKEN                  BIT(2)
#define PCIE0_AUX_CKEN                   BIT(3)
#define PCIE0_BUS_SRST_REQ               BIT(4)
#define PCIE0_SYS_SRST_REQ               BIT(5)
#define PCIE0_SRST_REQ                   BIT(6)
#define PCIE_REFCLK_SEL                  BIT(7)

 /******************************************************************************/

static void nano_register_write(struct hiclk_hw *clk, u32 addr, 
				u32 offset, u32 value)
{
	u32 reg;

	reg = readl(clk->peri_ctrl_base + addr);
	reg &= ~NANO_TEST_ADDR;
	reg &= ~NANO_TEST_DATA;
	reg |= (offset << 12);
	reg |= (value << 20);
	writel(reg, clk->peri_ctrl_base + addr);
	udelay(20);

	reg = readl(clk->peri_ctrl_base + addr);
	reg |= NANO_TEST_WRITE;
	writel(reg, clk->peri_ctrl_base + addr);
	udelay(20);

	reg = readl(clk->peri_ctrl_base + addr);
	reg &= ~NANO_TEST_WRITE;
	writel(reg, clk->peri_ctrl_base + addr);
	udelay(20);
}
/******************************************************************************/

static int hipcie_ioremap(u32 addr, void **pcie_reg_addr)
{
	if (!(*pcie_reg_addr)) {
		*pcie_reg_addr = ioremap_nocache(addr, 0x20);
		if (!(*pcie_reg_addr)) {
			printk("ioremap pcie reg failed.\n");
			return -1;
		}
	}
	return 0;
}

/******************************************************************************/

static void hipcie_iounmap(void **pcie_reg_addr)
{
	if (*pcie_reg_addr) {
		iounmap(*pcie_reg_addr);
		*pcie_reg_addr = NULL;
	}
}

/******************************************************************************/

static int hipcie_config_power_on(u32 gpio_value)
{
	u32 reg, temp_addr;
	int ret = -1;
	void __iomem *pcie_reg_addr0 = NULL;
	void __iomem *pcie_reg_addr1 = NULL;

	if ((gpio_value >> 3) > PCIE_GPIO_MAX)
		return -1;
	temp_addr = gpio_regbase[gpio_value >> 3] + 0x400;
	ret = hipcie_ioremap(temp_addr, &pcie_reg_addr0);
	if (ret == -1)
		return -1;
	/* Set GPIO output */
	reg = readl(pcie_reg_addr0);
	reg |= 0x1 << (gpio_value & PCIE_GPIO_NUM_MASK);
	writel(reg, pcie_reg_addr0);
	udelay(20);
	hipcie_iounmap(&pcie_reg_addr0);

	temp_addr = gpio_regbase[gpio_value >> 3] + (0x04 << (gpio_value & PCIE_GPIO_NUM_MASK));
	ret = hipcie_ioremap(temp_addr, &pcie_reg_addr1);
	if (ret == -1)
		return -1;
	/* Set GPIO output High */
	reg = 0x1 << (gpio_value & PCIE_GPIO_NUM_MASK);
	writel(reg, pcie_reg_addr1);
	udelay(20);
	hipcie_iounmap(&pcie_reg_addr1);

	return 0;
}

/******************************************************************************/

static int hipcie_config_reset(u32 gpio_value)
{
	u32 reg, temp_addr;
	int ret = -1;
	void __iomem *pcie_reg_addr0 = NULL;
	void __iomem *pcie_reg_addr1 = NULL;

	if ((gpio_value >> 3) > PCIE_GPIO_MAX)
		return -1;
	temp_addr = gpio_regbase[gpio_value >> 3] + 0x400;
	ret = hipcie_ioremap(temp_addr, &pcie_reg_addr0);
	if (ret == -1)
		return -1;
	/* Set GPIO to output mode */
	reg = readl(pcie_reg_addr0);
	reg |= 0x1 << (gpio_value & PCIE_GPIO_NUM_MASK);
	writel(reg, pcie_reg_addr0);
	udelay(20);
	hipcie_iounmap(&pcie_reg_addr0);

	temp_addr = gpio_regbase[gpio_value >> 3] + (0x04 << (gpio_value & PCIE_GPIO_NUM_MASK));
	ret = hipcie_ioremap(temp_addr, &pcie_reg_addr1);
	if (ret == -1)
		return -1;

	reg = readl(pcie_reg_addr1);

	/* Set GPIO output low to reset PCIE */
	reg &= ~(1<<(gpio_value & PCIE_GPIO_NUM_MASK));
	writel(reg, pcie_reg_addr1);
	mdelay(10);

	/* Set GPIO output High to release reset */
	reg |= (1<<(gpio_value & PCIE_GPIO_NUM_MASK));
	writel(reg, pcie_reg_addr1);
	udelay(20);

	hipcie_iounmap(&pcie_reg_addr1);

	return 0;
}

/******************************************************************************/

static int hiclk_enable_pcie(struct clk_hw *hw)
{
	u32 reg, mux;
	int ret = -1;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	mux = readl(clk->peri_ctrl_base + PERI_CTRL);
	mux &= COMBPHY1_SEL_MASK;

	if (mux != COMBPHY1_SEL_PCIE)
		return -1;
	
#ifdef CONFIG_GPIO_PCIE_POWER_EN_SUPPORT
	/* Config Power on PCIe*/
	if (CONFIG_GPIO_PCIE_POWER_EN != 0xff) {
		ret = hipcie_config_power_on(CONFIG_GPIO_PCIE_POWER_EN);
		if (ret == -1)
			return -1;
	}
#endif

	/* Config ComboPHY1 enable 8B10B */
	reg = readl(clk->peri_ctrl_base + PERI_COMBPHY1_CFG);
	reg &= ~NANO_BYPASS_CODEC;
	writel(reg, clk->peri_ctrl_base + PERI_COMBPHY1_CFG);
	udelay(20);

	/*combphy reset from crg*/
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &= ~COMBPHY1_RSTN_SEL_CTRL;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* reset ComboPHY1 */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg |= COMBPHY1_SRST_REQ;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* close ComboPHY1 cken */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &=~COMBPHY1_REF_CKEN;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* select refclk from combphy */
	reg = readl(clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	reg &=~PCIE_REFCLK_SEL;
	writel(reg,clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	udelay(20);

	/* Config ComboPHY1 refclk:0x0:BPLL 100MHz 0x2:VPLL 100MHz */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &= ~COMBPHY1_REFCLK_SEL;
	reg |= 0x2<<10;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* open ComboPHY1 cken */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg |= COMBPHY1_REF_CKEN;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* release reset ComboPHY1 */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &= ~COMBPHY1_SRST_REQ;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);
	/* Output EP clock by phy1*/
	reg = readl(clk->peri_ctrl_base + PERI_COMBPHY1_CFG);
	reg |= CLKREF_OUT_OEN;
	writel(reg, clk->peri_ctrl_base + PERI_COMBPHY1_CFG);
	mdelay(5);//need to wait for EP clk  stable
#ifdef CONFIG_PCIE_RESET
	/* PCIe reset and release*/
	if (CONFIG_GPIO_PCIE_RESET != 0xff) {
		ret = hipcie_config_reset(CONFIG_GPIO_PCIE_RESET);
		if (ret == -1)
			return -1;
	}
#endif
	/* SSC on */
//	nano_register_write(clk, PERI_COMBPHY1_CFG, 0x2, 0x8);

	/* PHY SSC on when use PHYclk */
//	nano_register_write(clk, PERI_COMBPHY0_CFG, 0x3, 0x8);

	/* seperate_rate 1'b1 */
	nano_register_write(clk, PERI_COMBPHY1_CFG, 0x1, 0x8);

	/* SPLIT_CP_DIS */
	nano_register_write(clk, PERI_COMBPHY1_CFG, 0xc, 0x9);

	/* PLL 3rd filter bypass */
	nano_register_write(clk, PERI_COMBPHY1_CFG, 0x1a, 0x4);

	/* PWON Manual */
	nano_register_write(clk, PERI_COMBPHY1_CFG, 0x4, 0x7);
	nano_register_write(clk, PERI_COMBPHY1_CFG, 0x5, 0x3);
	nano_register_write(clk, PERI_COMBPHY1_CFG, 0x3, 0x3);

	/* Open Pcie0 Controller clk */
	reg = readl(clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	reg |= ( PCIE0_BUS_CKEN
		| PCIE0_PIPE_CKEN
		| PCIE0_AUX_CKEN
		| PCIE0_SYS_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	udelay(20);

	/* Reset Pcie0 Controller */
	reg = readl(clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	reg |= (PCIE0_BUS_SRST_REQ
		|PCIE0_SYS_SRST_REQ
		|PCIE0_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	udelay(20);

	/* Deassert reset Pcie0 Controller */
	reg = readl(clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	reg &= ~(PCIE0_BUS_SRST_REQ
		|PCIE0_SYS_SRST_REQ
		|PCIE0_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	udelay(20);

	return 0;
}
/*****************************************************************************/

static void hiclk_disable_pcie(struct clk_hw *hw)
{
	u32 reg, mux;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	mux = readl(clk->peri_ctrl_base + PERI_CTRL);
	mux &= COMBPHY1_SEL_MASK;

	if (mux != COMBPHY1_SEL_PCIE)
		return;

	/* reset PCIe0 Controller */
	reg = readl(clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	reg |= (PCIE0_BUS_SRST_REQ
		| PCIE0_SYS_SRST_REQ
		| PCIE0_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	udelay(20);

	/* close PCIe0 Controller clk */
	reg = readl(clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	reg &= ~(PCIE0_BUS_CKEN
		| PCIE0_SYS_CKEN
		| PCIE0_PIPE_CKEN
		| PCIE0_AUX_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG99_PCIECTRL);
	udelay(20);

	/* close EP clock */
	reg = readl(clk->peri_ctrl_base + PERI_COMBPHY1_CFG);
	reg &= ~CLKREF_OUT_OEN;
	writel(reg, clk->peri_ctrl_base + PERI_COMBPHY1_CFG);
	udelay(20);

	/*combphy reset from crg*/
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &= ~COMBPHY1_RSTN_SEL_CTRL;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* reset ComboPHY1 */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg |= COMBPHY1_SRST_REQ;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* close ComboPHY1 cken */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &=~COMBPHY1_REF_CKEN;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);

	/* Config ComboPHY1 refclk */
	reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
	reg &= ~COMBPHY1_REFCLK_SEL;
	writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
	udelay(20);
}
/******************************************************************************/

struct clk_ops clk_ops_hipcie = {
	.enable = hiclk_enable_pcie,
	.disable = hiclk_disable_pcie,
};
