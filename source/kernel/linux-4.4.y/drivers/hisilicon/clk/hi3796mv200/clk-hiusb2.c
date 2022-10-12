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
 * Create By Liu Hui 2015.06.23
 *
******************************************************************************/

#include <linux/delay.h>
#include <dt-bindings/clock/hi3798mv200-clock.h>
#include <linux/hikapi.h>

#include "clk-hisi.h"

/******************************************************************************/
#define PERI_CTRL_USB3                  (0x12c)

#define USB2_2P_SS_WORD_IF_I            BIT(0)
#define USB2_2P_SS_ENA_INCR16_I         BIT(9)

#define TEST_WRDATA                     (0xc)
#define TEST_ADDR                       (0x6 << 8)
#define TEST_WREN                       BIT(13)
#define TEST_CLK                        BIT(14)
#define TEST_RSTN                       BIT(15)

#define USB2_BUS_CKEN                   BIT(0)
#define USB2_OHCI48M_CKEN               BIT(1)
#define USB2_OHCI12M_CKEN               BIT(2)
#define USB2_OTG_UTMI_CKEN              BIT(3)
#define USB2_HST_PHY_CKEN               BIT(4)
#define USB2_UTMI0_CKEN                 BIT(5)
#define USB2_UTMI1_CKEN                 BIT(6)
#define USB2_PHY0_SRST_TREQ             BIT(8)
#define USB2_PHY1_SRST_TREQ             BIT(9)
#define USB2_BUS_SRST_REQ               BIT(12)
#define USB2_UTMI0_SRST_REQ             BIT(13)
#define USB2_UTMI1_SRST_REQ             BIT(14)
#define USB2_HST_PHY_SYST_REQ           BIT(16)
#define USB2_OTG_PHY_SYST_REQ           BIT(17)
#define USB2_CLK48_SEL                  BIT(20)

#define USB2_PHY01_REF_CKEN             BIT(0)
#define USB2_PHY2_REF_CKEN              BIT(2)
#define USB2_PHY01_SRST_REQ             BIT(4)
#define USB2_PHY2_SRST_REQ              BIT(6)
#define USB2_PHY0_SRST_TREQ             BIT(8)
#define USB2_PHY1_SRST_TREQ             BIT(9)
#define USB2_PHY2_SRST_TREQ             BIT(10)
#define USB2_PHY01_REFCLK_SEL           BIT(12)
#define USB2_PHY2_REFCLK_SEL            BIT(14)
#define USB2_PHY2_TEST_SRST_REQ         BIT(15)
#define USB2_PHY01_TEST_SRST_REQ        BIT(16)

#define USB2_PHY01_REGBASE              0xf9865000
#define USB2_1PORT_PHY_REGBASE          0xf9960000

#define PERI_USB2PHY0                   0xf8030000
#define PERI_USB2PHY1                   0xff2f4000

#define REG_BASE_OTP 			0xF8AB0000
#define REG_OTP_USB_TRIM		0x032C
#define REG_MASK_OTP_USB_TRIM		GENMASK(15, 0)

/******************************************************************************/
struct hisi_priv {
	void __iomem    *base_otp;
	void __iomem    *base_usb2_2p_phy;
	void __iomem    *base_usb2_1p_phy;
	void __iomem    *peri_usb2phy0;
	void __iomem    *peri_usb2phy1;
};

static struct hisi_priv hisi_usb2 = {
	.base_otp = NULL,
	.base_usb2_2p_phy = NULL,
	.base_usb2_1p_phy = NULL,
	.peri_usb2phy0 = NULL,
	.peri_usb2phy1 = NULL,
};

static atomic_t dev_open_cnt = {
	.counter = 0,
};
/******************************************************************************/

static void config_ufsphy_chiptrim(void)
{
	u32 reg, chiptrim_usbphy;
	void __iomem *peri_usb2phy0 = hisi_usb2.peri_usb2phy0;
	void __iomem *peri_usb2phy1 = hisi_usb2.peri_usb2phy1;
	void __iomem *otp_chiptrim  = hisi_usb2.base_otp;

	//chiptrim_usbphy config
	chiptrim_usbphy = (readl(otp_chiptrim + REG_OTP_USB_TRIM)& REG_MASK_OTP_USB_TRIM);
    chiptrim_usbphy <<= 2;
    chiptrim_usbphy &= 0x7C;  //bit[6:2]
    if (chiptrim_usbphy) {
        //1xport
        reg = readl(peri_usb2phy0 + 0x00c);
        reg &= ~0x7C;
        reg |= chiptrim_usbphy;
        writel(reg, peri_usb2phy0 + 0x00c);
        udelay(20);
        //2xport port0:
        reg = readl(peri_usb2phy1 + 0x00c);
        reg &= ~0x7C;
        reg |= chiptrim_usbphy;
        writel(reg, peri_usb2phy1 + 0x00c);
        udelay(20);
        //2xport port1:
        reg = readl(peri_usb2phy1 + 0x40c);
        reg &= ~0x7C;
        reg |= chiptrim_usbphy;
        writel(reg, peri_usb2phy1 + 0x40c);
        udelay(20);
    }
}

static void inno_phy_config_2p_1(struct hiclk_hw *clk)
{
	void __iomem *regbase = hisi_usb2.base_usb2_2p_phy;
	if (!regbase) {
		printk("ioremap ehci regbase failed.\n");
		return;
	}

	writel(0x4, regbase + 0x18);
	mdelay(2);
	//eye diagram
	writel(0x6c, regbase + 0x408);
	mdelay(2);
	//slew rate
	writel(0x1e, regbase + 0x474);
	mdelay(2);
	//EOP pre-emph off
	writel(0x1c, regbase + 0x400);
	mdelay(2);
	//disconnect =625
	writel(0xd7, regbase + 0x410);
	mdelay(2);
	//second handshake
	writel(0x0e, regbase + 0x47c);
	mdelay(2);
}

static void inno_phy_config_1p(struct hiclk_hw *clk)
{
	void __iomem *regbase = hisi_usb2.base_usb2_1p_phy;
	if (!regbase) {
		printk("ioremap ehci regbase failed.\n");
		return;
	}

	//eye diagram
	writel(0x6c, regbase + 0x008);
	mdelay(2);
	//slew rate
	writel(0x1e, regbase + 0x074);
	mdelay(2);
	//EOP pre-emph off
	writel(0x1c, regbase + 0x000);
	mdelay(2);
	//disconnect =625
	writel(0xd7, regbase + 0x010);
	mdelay(2);
	//second handshake
	writel(0x0e, regbase + 0x07c);
	mdelay(2);
}

/******************************************************************************/
static int hiclk_prepare_usb2(struct clk_hw *hw)
{
	u32 reg;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	if(!hisi_usb2.base_otp)
		hisi_usb2.base_otp = ioremap_nocache(REG_BASE_OTP, 0x4);
	if(!hisi_usb2.base_usb2_2p_phy)
		hisi_usb2.base_usb2_2p_phy = ioremap_nocache(USB2_PHY01_REGBASE, 0x1000);
	if(!hisi_usb2.base_usb2_1p_phy)
		hisi_usb2.base_usb2_1p_phy = ioremap_nocache(USB2_1PORT_PHY_REGBASE, 0x1000);
	if(!hisi_usb2.peri_usb2phy0)
		hisi_usb2.peri_usb2phy0 = ioremap_nocache(PERI_USB2PHY0, 0x1000);
	if(!hisi_usb2.peri_usb2phy1)
		hisi_usb2.peri_usb2phy1 = ioremap_nocache(PERI_USB2PHY1, 0x1000);

	return 0;
}

static void hiclk_unprepare_usb2(struct clk_hw *hw)
{

	if(hisi_usb2.base_otp)
		iounmap(hisi_usb2.base_otp);
	if(hisi_usb2.base_usb2_2p_phy)
		iounmap(hisi_usb2.base_usb2_2p_phy);
	if(hisi_usb2.base_usb2_1p_phy)
		iounmap(hisi_usb2.base_usb2_1p_phy);
	if(hisi_usb2.peri_usb2phy0)
		iounmap(hisi_usb2.peri_usb2phy0);
	if(hisi_usb2.peri_usb2phy1)
		iounmap(hisi_usb2.peri_usb2phy1);

	hisi_usb2.base_otp = NULL;
	hisi_usb2.base_usb2_2p_phy = NULL;
	hisi_usb2.base_usb2_1p_phy = NULL;
	hisi_usb2.peri_usb2phy0 = NULL;
	hisi_usb2.peri_usb2phy1 = NULL;
}

static int hiclk_enable_usb2(struct clk_hw *hw)
{
	u32 reg;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	if (atomic_add_return(1, &dev_open_cnt) == 1) {

		/* reset controller bus/utmi/roothub  */
		reg = readl(clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		reg |= (USB2_BUS_SRST_REQ
			| USB2_UTMI0_SRST_REQ
			| USB2_UTMI1_SRST_REQ
			| USB2_HST_PHY_SYST_REQ
			| USB2_OTG_PHY_SYST_REQ);
		writel(reg, clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		udelay(200);

		/* reset phy por/utmi */
		reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
		reg |= (USB2_PHY0_SRST_TREQ
			| USB2_PHY1_SRST_TREQ);
		writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
		udelay(200);

#if defined(CONFIG_HI3798MV2X_FPGA) || defined(CONFIG_HI3796MV2X_FPGA)
		reg = readl(clk->peri_ctrl_base + PERI_CTRL_USB3);
		reg |= USB2_2P_SS_WORD_IF_I;  
		reg &= ~(USB2_2P_SS_ENA_INCR16_I);
		writel(reg, clk->peri_ctrl_base + PERI_CTRL_USB3);
		udelay(100);
#else
		reg = readl(clk->peri_ctrl_base + PERI_CTRL_USB3);
		reg &= ~(USB2_2P_SS_WORD_IF_I);
		reg &= ~(USB2_2P_SS_ENA_INCR16_I);
		writel(reg, clk->peri_ctrl_base + PERI_CTRL_USB3);
		udelay(100);
#endif
		/* open ref clk */
		reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
		reg |= (USB2_PHY01_REF_CKEN);
		writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
		udelay(300);
		reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
		reg &= ~(USB2_PHY01_TEST_SRST_REQ | USB2_PHY2_TEST_SRST_REQ);
		writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
		udelay(200);

		/* cancel power on reset */
		reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
		reg &= ~(USB2_PHY01_SRST_REQ);
		writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
		udelay(500);

		inno_phy_config_2p_1(clk);
		inno_phy_config_1p(clk);
		config_ufsphy_chiptrim();

		/* cancel port reset 
		* delay 2ms for waiting comp circuit stable
		*/
		reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
		reg &= ~(USB2_PHY0_SRST_TREQ | USB2_PHY1_SRST_TREQ);
		writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
		mdelay(2);
		/* open controller clk */
		reg = readl(clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		reg |= (USB2_BUS_CKEN
			| USB2_OHCI48M_CKEN
			| USB2_OHCI12M_CKEN
			| USB2_OTG_UTMI_CKEN
			| USB2_HST_PHY_CKEN
			| USB2_UTMI0_CKEN
			| USB2_UTMI1_CKEN);
		writel(reg, clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		udelay(200);
		
		/* cancel control reset */
		reg = readl(clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		reg &= ~(USB2_BUS_SRST_REQ
			| USB2_UTMI0_SRST_REQ
			| USB2_UTMI1_SRST_REQ
			| USB2_HST_PHY_SYST_REQ
			| USB2_OTG_PHY_SYST_REQ);
		writel(reg, clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		udelay(200);
	}

	return 0;
}
/******************************************************************************/

static void hiclk_disable_usb2(struct clk_hw *hw)
{
	u32 reg;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	if (atomic_sub_return(1, &dev_open_cnt) == 0) {

		reg = readl(clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		reg &= ~(USB2_BUS_CKEN
			| USB2_OTG_UTMI_CKEN
			| USB2_HST_PHY_CKEN
			| USB2_UTMI0_CKEN
			| USB2_UTMI1_CKEN);
		writel(reg, clk->peri_crg_base + PERI_CRG46_USB2CTRL);
		udelay(200);

		reg = readl(clk->peri_crg_base + PERI_CRG47_USB2PHY);
		reg |= (USB2_PHY01_SRST_REQ
			| USB2_PHY0_SRST_TREQ
			| USB2_PHY1_SRST_TREQ);
		writel(reg, clk->peri_crg_base + PERI_CRG47_USB2PHY);
		udelay(100);

	}
}
/******************************************************************************/

struct clk_ops clk_ops_hiusb2 = {
	.prepare = hiclk_prepare_usb2,
	.unprepare = hiclk_unprepare_usb2,
	.enable = hiclk_enable_usb2,
	.disable = hiclk_disable_usb2,
};
