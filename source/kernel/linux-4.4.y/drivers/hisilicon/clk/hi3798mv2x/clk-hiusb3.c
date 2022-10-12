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
#include <dt-bindings/clock/hi3798mv200-clock.h>
#include <linux/hikapi.h>
#include "clk-hisi.h"

extern int combphy_fixed;

static void __iomem *xhci_host0_regbase;
static void __iomem *xhci_host1_regbase;

/******************************************************************************/
#define XHCI_HOST0_ADDR             (0xF98A0000)
#define XHCI_HOST1_ADDR             (0xF98B0000)

#define PERI_CTRL                   (0x0008)
#define PERI_USB0                   (0x120)
#define PERI_USB1                   (0x124)
#define PERI_USB2                   (0x128)
#define PERI_USB5                   (0x134)
#define PERI_USB7                   (0x13c)
#define PERI_COMBPHY0               (0x850)

#define GTXTHRCFG                   (0xc108)
#define GRXTHRCFG                   (0xc10c)
#define REG_GCTL                    (0xc110)
#define REG_GUSB2PHYCFG0            (0xC200)
#define REG_GUSB3PIPECTL0           (0xc2c0)

#define USB2_PHY2_SRST_REQ            BIT(6)
#define USB2_PHY2_SRST_TREQ           BIT(10)
#define USB2_PHY2_REF_CKEN              BIT(2)
#define USB2_PHY2_TEST_SRST_REQ         BIT(16)

#define USB3_BUS_CKEN                 BIT(0)
#define USB3_REF_CKEN                 BIT(1)
#define USB3_SUSPEND_CKEN             BIT(2)
#define USB3_PIPE_CKEN                BIT(3)
#define USB3_UTMI_CKEN                BIT(4)
#define USB3_BUS_GS_CKEN              BIT(5)
#define USB3_BUS_GM_CKEN              BIT(6)
#define USB3_VCC_SRST_REQ             BIT(12)
#define USB3_BUS_CKEN1                BIT(16)
#define USB3_REF_CKEN1                BIT(17)
#define USB3_SUSPEND_CKEN1            BIT(18)
#define USB3_PIPE_CKEN1               BIT(19)
#define USB3_UTMI_CKEN1               BIT(20)
#define USB3_BUS_GS_CKEN1             BIT(21)
#define USB3_BUS_GM_CKEN1             BIT(22)
#define USB3_VCC_SRST_REQ1            BIT(28)

#define USB3_PORT_DISABLE             BIT(5)

#define COMBPHY0_REF_CKEN             BIT(0)
#define COMBPHY0_REF_SEL0             BIT(2)
#define COMBPHY0_REF_SEL1             BIT(3)
#define COMBPHY0_SRST_REQ             BIT(4)

#define COMBPHY1_SEL_MASK             (BIT(11) | BIT(12))
#define COMBPHY1_SEL_USB3              BIT(11)

#define BIT_UTMI_8_16                 BIT(3)
#define BIT_UTMI_ULPI                 BIT(4)
#define BIT_FREECLK_EXIST             BIT(30)

#define PCS_SSP_SOFT_RESET            BIT(31)

#define USB3_DEEMPHASIS0              BIT(1)
#define USB3_DEEMPHASIS1              BIT(2)
#define USB3_TX_MARGIN0               BIT(3)
#define USB3_TX_MARGIN1               BIT(4)
#define USB3_TX_MARGIN2               BIT(5)
#define USB3_SUSPEND_EN               BIT(17)
#define USB3_DEEMPHASIS_MASK          (0x6)

#define USB2_PHY2_REGBASE              0xf9960000
#define USB3_NANOPHY_REGBASE              0x850

#define CLK_NAME(_id) (#_id)

extern struct clk_ops clk_ops_hiusb2;

extern char no_usb3_0;
extern char no_usb3_1;
/******************************************************************************/
static void nano_phy_config_0(struct hiclk_hw *clk)
{
	u32 reg;
	u64 chipid = get_chipid(0ULL);

	/* write 0x010c0012 to GUSB3PIPECTL0
	* GUSB3PIPECTL0[17] = 0 : disable U3 suspend 
	* GUSB3PIPECTL0[5:3] = 010 : Tx Margin = 900mV , decrease TX voltage
	* GUSB3PIPECTL0[2:1] = 01 : Tx Deemphasis = -3.5dB, refer to spec
	*/
	reg = readl(xhci_host0_regbase + REG_GUSB3PIPECTL0);
	reg |= USB3_SUSPEND_EN;
	reg &= ~USB3_DEEMPHASIS_MASK;
	reg |= USB3_DEEMPHASIS0;
	reg |= USB3_TX_MARGIN1;
	writel(reg, xhci_host0_regbase + REG_GUSB3PIPECTL0);
	udelay(20);

	if (_HI3798MV200 == chipid) {
		writel(0x203000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x1203000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x203000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x0, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
	} else if (_HI3798MV300 == chipid) {
		writel(0x81b000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x181b000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x81b000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x0, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x81a000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x181a000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x81a000, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
		writel(0x0, clk->peri_ctrl_base + USB3_NANOPHY_REGBASE);
		udelay(20);
	}
}
/******************************************************************************/

static void inno_phy_config_1p(struct hiclk_hw *clk)
{
	u64 chipid = get_chipid(0ULL);
	void __iomem *regbase = ioremap_nocache(USB2_PHY2_REGBASE, 0x1000);
	if (!regbase) {
		printk("ioremap ehci regbase failed.\n");
		return;
	}

	mdelay(2);
	writel(0x4, regbase + 0x18);
	mdelay(2);

	if (chipid == _HI3798MV200) {
		writel(0x1c, regbase);
		udelay(20);
		writel(0xc1, regbase + 0x44);
		udelay(20);
		writel(0x5b, regbase + 0x28);
		udelay(20);
		writel(0x7, regbase + 0x18);
		udelay(20);
		writel(0x92, regbase + 0x14);
		udelay(20);
	} else if (chipid == _HI3798MV300) {
		/* eye height 450mv */
		writel(0x0c, regbase + 0x08);
		udelay(20);

		/* pre-emphasis */
		writel(0x18, regbase);
		udelay(20);

		/* disconnects detection trigger 562.5mv */
		writel(0xd7, regbase + 0x10);
		udelay(20);

		/* HS driver slew rate tunning */
		writel(0x1e, regbase + 0x74);
		udelay(20);

		/* Second handshake */
		writel(0x6e, regbase + 0x7c);
		udelay(20);
	}
	iounmap(regbase);
	regbase = NULL;
	mdelay(2);
}
/******************************************************************************/

static int hiclk_enable_usb3_host0(struct clk_hw *hw)
{
	u32 reg, mux = 0;
	struct hiclk_hw *clk = to_hiclk_hw(hw);
	const char * clkname = CLK_NAME(PERI_CRG46_USB2CTRL);
	struct clk * usb2clk =__clk_lookup(clkname);

	if (!xhci_host0_regbase) {
		xhci_host0_regbase = ioremap_nocache(XHCI_HOST0_ADDR, 0x10000);
		if (!xhci_host0_regbase) {
			printk("ioremap xhci host0 failed.\n");
			return -1;
		}
	}

	/* TODO: make sure if combphy1 connected */
	mux = readl(clk->peri_ctrl_base + PERI_CTRL);
	mux &= COMBPHY1_SEL_MASK;

	if (no_usb3_0)
		mux &= ~COMBPHY1_SEL_MASK;

	if (mux != COMBPHY1_SEL_USB3) {
		reg = readl(clk->peri_ctrl_base + PERI_USB5);
		reg |= USB3_PORT_DISABLE;
		writel(reg, clk->peri_ctrl_base + PERI_USB5);
	}

	/* init usb2 phy */
	/* open ref clk */
	reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
	reg |= (USB2_PHY2_REF_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
	udelay(300);
	
	reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
	reg &= ~(USB2_PHY2_TEST_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
	udelay(200);
	
	/* cancel usb2 1p phy POR */
	reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
	reg &= ~(USB2_PHY2_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
	udelay(200);

	inno_phy_config_1p(clk);

	/* cancel 2p phy utmi reset0 
	* delay 2ms for waiting comp circuit stable
	*/
	reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
	reg &= ~(USB2_PHY2_SRST_TREQ);
	writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
	mdelay(2);

	if (mux == COMBPHY1_SEL_USB3) {
		/* select VPLL 25MHz ref clock for COMB0
		* BPLL may be SSC in Hi3798CV200 
		*/
		reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
		reg |= (COMBPHY0_REF_SEL1);
		writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
		udelay(100);

		/* open combphy0 cken */
		reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
		reg |= (COMBPHY0_REF_CKEN);
		writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
		udelay(200);

		/* cancel combphy0 POR */
		reg = readl(clk->peri_crg_base + PERI_CRG98_COMBPHY);
		reg &= ~(COMBPHY0_SRST_REQ);
		writel(reg, clk->peri_crg_base + PERI_CRG98_COMBPHY);
		mdelay(1);
	}

	/* open u3 ctrl0 bus cken */
	reg = readl(clk->peri_crg_base + PERI_CRG44_USB3CTRL);
	reg |= (USB3_BUS_GM_CKEN
		| USB3_BUS_GS_CKEN
		| USB3_BUS_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG44_USB3CTRL);
	udelay(100);

	/* cancel u3 ctrl0 reset */
	reg = readl(clk->peri_crg_base + PERI_CRG44_USB3CTRL);
	reg &= ~(USB3_VCC_SRST_REQ);
	writel(reg, clk->peri_crg_base + PERI_CRG44_USB3CTRL);
	udelay(200);

	//reg = readl(XHCI_HOST0_ADDR + REG_GUSB3PIPECTL0);
	//reg |= PCS_SSP_SOFT_RESET;
	//writel(reg, XHCI_HOST0_ADDR + REG_GUSB3PIPECTL0);

	/* USB2 PHY chose ulpi 8bit interface */
	reg = readl(xhci_host0_regbase + REG_GUSB2PHYCFG0);
	reg &= ~BIT_UTMI_ULPI;
	reg &= ~(BIT_UTMI_8_16);
	reg &= ~BIT_FREECLK_EXIST;
	writel(reg, xhci_host0_regbase + REG_GUSB2PHYCFG0);
	
	/* [13:12] 01: Host; 10: Device; 11: OTG */
	reg = readl(xhci_host0_regbase + REG_GCTL);
	reg &= ~(0x3<<12);
	reg |= (0x1<<12);
	writel(reg, xhci_host0_regbase + REG_GCTL);

	if (mux == COMBPHY1_SEL_USB3) {
		nano_phy_config_0(clk);
	}

	/* open USB3 cken */
	reg = readl(clk->peri_crg_base + PERI_CRG44_USB3CTRL);
	reg |= (USB3_UTMI_CKEN
		| USB3_PIPE_CKEN
		| USB3_SUSPEND_CKEN
		| USB3_REF_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG44_USB3CTRL);
	mdelay(1);

	writel(0x23100000, xhci_host0_regbase + GTXTHRCFG);
	writel(0x23180000, xhci_host0_regbase + GRXTHRCFG);

	udelay(200);

	if (xhci_host0_regbase) {
		iounmap(xhci_host0_regbase);
		xhci_host0_regbase = NULL;
	}

	return 0;
}
/******************************************************************************/

static void hiclk_disable_usb3_host0(struct clk_hw *hw)
{
	u32 reg;
	struct hiclk_hw *clk = to_hiclk_hw(hw);
	const char * clkname = CLK_NAME(PERI_CRG46_USB2CTRL);
	struct clk * usb2clk =__clk_lookup(clkname);
	
	mdelay(100);

	reg = readl(clk->peri_crg_base + PERI_CRG44_USB3CTRL);
	reg &= ~(USB3_UTMI_CKEN
		| USB3_SUSPEND_CKEN
		| USB3_REF_CKEN
		| USB3_BUS_CKEN);
	writel(reg, clk->peri_crg_base + PERI_CRG44_USB3CTRL);

}
/******************************************************************************/

struct clk_ops clk_ops_hiusb3_host0 = {
	.enable = hiclk_enable_usb3_host0,
	.disable = hiclk_disable_usb3_host0,
};
