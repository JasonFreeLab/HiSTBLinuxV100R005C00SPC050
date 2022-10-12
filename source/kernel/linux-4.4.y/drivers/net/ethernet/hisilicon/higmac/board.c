#include <linux/kernel.h>
#include <linux/reset.h>
#include <linux/clk-provider.h>
#include <linux/hikapi.h>
#include <linux/clk.h>
#include "higmac.h"

#ifdef HIGMAC_HAS_INTERNAL_PHY
/* register REG_CRG_FEPHY */
#define REG_CRG_FEPHY		0x0388
#define BIT_FEPHY_CLK		BIT(0)
#define BIT_FEPHY_RST		BIT(4)
/* register REG_PERI_FEPHY */
#define REG_PERI_FEPHY		0x0118
#define BIT_MASK_FEPHY_ADDR	0x1F
#define BIT_MASK_FEPHY_WOL	BIT(5)
/* register REG_PERI_FEPHY_LDO */
#define REG_PERI_FEPHY_LDO	0x0844
#define BIT_LDO_EN		BIT(4)
#define BIT_LDO_ENZ		BIT(5)
#define BIT_LDO_RSTN		BIT(6)
#define BIT_IDDQ_MODE		BIT(7)
#define LDO_VSET_MASK		0xF
#define LDO_VSET_VAL		0x8
#endif

void higmac_mac_core_reset(struct higmac_netdev_local *priv)
{
	/* undo reset */
	reset_control_deassert(priv->port_rst);
	usleep_range(50, 60);

	/* soft reset mac port */
	reset_control_assert(priv->port_rst);
	usleep_range(50, 60);
	/* undo reset */
	reset_control_deassert(priv->port_rst);
}

void higmac_hw_internal_phy_reset(struct higmac_netdev_local *priv)
{
#ifdef HIGMAC_HAS_INTERNAL_PHY
	unsigned int v = 0;

	/* disable MDCK clock to make sure FEPHY reset success */
	clk_disable_unprepare(priv->clk);

	v = readl(priv->crg_iobase + REG_CRG_FEPHY);
	v &= ~BIT_FEPHY_CLK;
	writel(v, priv->crg_iobase + REG_CRG_FEPHY);/* disable clk */

	v = readl(priv->peri_iobase + REG_PERI_FEPHY_LDO);
#if defined(CONFIG_ARCH_HI3796MV2X)
	v |= (BIT_LDO_EN | BIT_LDO_RSTN);
	v &= ~(BIT_LDO_ENZ | BIT_IDDQ_MODE);
#else
	/* set internal FEPHY LDO_VSET value, LDO output 1.1V */
	v = (v & ~LDO_VSET_MASK) | LDO_VSET_VAL;
#if defined(CONFIG_ARCH_HIFONE)
	/* enalbe internal FEPHY LDO_EN for hifone_b02 */
	v |= BIT_LDO_EN;
#endif
#endif
	writel(v, priv->peri_iobase + REG_PERI_FEPHY_LDO);

	v = readl(priv->crg_iobase + REG_CRG_FEPHY);
	v |= BIT_FEPHY_CLK; /* use 25MHz clock, enable clk */
	writel((u32)v, priv->crg_iobase + REG_CRG_FEPHY);

	udelay(10);

	/* suppose internal phy can only be used as mac0's phy */
	v = readl(priv->peri_iobase + REG_PERI_FEPHY);
	v &= ~BIT_MASK_FEPHY_ADDR;
	v |= (priv->phy_addr & BIT_MASK_FEPHY_ADDR);
	v |= BIT_MASK_FEPHY_WOL;
	writel(v, priv->peri_iobase + REG_PERI_FEPHY);

	v = readl(priv->crg_iobase + REG_CRG_FEPHY);
	v |= BIT_FEPHY_RST; /* set reset bit */
	writel((u32)v, priv->crg_iobase + REG_CRG_FEPHY);

	udelay(10);

	v = readl(priv->crg_iobase + REG_CRG_FEPHY);
	v &= ~BIT_FEPHY_RST; /* clear reset bit */
	writel((u32)v, priv->crg_iobase + REG_CRG_FEPHY);

	msleep(20); /* delay at least 15ms for MDIO operation */

	clk_prepare_enable(priv->clk);
#endif
}

void higmac_hw_phy_reset(struct higmac_netdev_local *priv)
{
	if (priv->internal_phy)
		higmac_hw_internal_phy_reset(priv);
	else
		higmac_hw_external_phy_reset(priv);
}

static void higmac_phy_reset_assert(struct reset_control *rst,
				    bool rst_when_set)
{
	if (rst_when_set)
		reset_control_assert(rst);
	else
		reset_control_deassert(rst);
}

static void higmac_phy_reset_deassert(struct reset_control *rst,
				      bool rst_when_set)
{
	if (rst_when_set)
		reset_control_deassert(rst);
	else
		reset_control_assert(rst);
}

#define RESET_DATA		1
#define GPIO_DIR		0x400
void higmac_hw_external_phy_reset(struct higmac_netdev_local *priv)
{
	u64 chipid;
	bool rst_when_set;

	/* HIFONE or 98cv200 use CRG register to reset phy */
	/* RST_BIT, write 0 to reset phy, write 1 to cancel reset */
	chipid = get_chipid(0ULL);
	if (chipid == _HI3798CV200)
		rst_when_set = false;
	else
		rst_when_set = true;

	if (priv->phy_rst) {
		higmac_phy_reset_deassert(priv->phy_rst, rst_when_set);
		msleep(10);

		higmac_phy_reset_assert(priv->phy_rst, rst_when_set);

		/* delay some time to ensure reset ok,
		 * this depends on PHY hardware feature
		 */
		msleep(20);

		higmac_phy_reset_deassert(priv->phy_rst, rst_when_set);
		/* delay some time to ensure later MDIO access */
		msleep(50);
	} else if (priv->gpio_base) {
#ifdef HIGMAC_RESET_PHY_BY_GPIO
		/* use gpio to control mac's phy reset */
		void __iomem *gpio_base;
		u32 gpio_bit;
		u32 v;

		gpio_base = (void __iomem *)IO_ADDRESS(
				(unsigned int)priv->gpio_base);
		gpio_bit = priv->gpio_bit;

		/* config gpip[x] dir to output */
		v = readb(gpio_base + GPIO_DIR);
		v |= (1 << gpio_bit);
		writeb(v, gpio_base + GPIO_DIR);

		/* gpiox[x] set to reset, then delay 200ms */
		writeb(RESET_DATA << gpio_bit, gpio_base + (4 << gpio_bit));
		msleep(20);
		/* then,cancel reset,and should delay 200ms */
		writeb((!RESET_DATA) << gpio_bit, gpio_base + (4 << gpio_bit));
		msleep(20);
		writeb(RESET_DATA << gpio_bit, gpio_base + (4 << gpio_bit));

		/* add some delay in case mdio cann't access now! */
		msleep(30);
#endif
	}
}

void higmac_internal_phy_clk_disable(struct higmac_netdev_local *priv)
{
#ifdef HIGMAC_HAS_INTERNAL_PHY
	u32 v = 0;

	v = readl(priv->crg_iobase + REG_CRG_FEPHY);
	v &= ~BIT_FEPHY_CLK;
	v |= BIT_FEPHY_RST;
	writel(v, priv->crg_iobase + REG_CRG_FEPHY);/* inside fephy clk disable */

#if defined(CONFIG_ARCH_HI3796MV2X)
	/* config FEPHY LDO to iddq mode to save power */
	v = readl(priv->peri_iobase + REG_PERI_FEPHY_LDO);
	v &= ~(BIT_LDO_EN | BIT_LDO_RSTN);
	v |= (BIT_LDO_ENZ | BIT_IDDQ_MODE);
	writel(v, priv->peri_iobase + REG_PERI_FEPHY_LDO);
#endif
#endif
}

void higmac_internal_phy_clk_enable(struct higmac_netdev_local *priv)
{
#ifdef HIGMAC_HAS_INTERNAL_PHY
	u32 v = 0;

	v = readl(priv->crg_iobase + REG_CRG_FEPHY);
	v |= BIT_FEPHY_CLK;
	writel(v, priv->crg_iobase + REG_CRG_FEPHY);/* inside fephy clk enable */
#endif
}

void higmac_hw_all_clk_disable(struct higmac_netdev_local *priv)
{
	if (netif_running(priv->netdev)) {
		clk_disable_unprepare(priv->macif_clk);
		clk_disable_unprepare(priv->clk);
	}

	if (priv->internal_phy && !priv->phy_wol_enable)
		higmac_internal_phy_clk_disable(priv);
}

void higmac_hw_all_clk_enable(struct higmac_netdev_local *priv)
{
	if (priv->internal_phy)
		higmac_internal_phy_clk_enable(priv);

	if (netif_running(priv->netdev)) {
		clk_prepare_enable(priv->macif_clk);
		clk_prepare_enable(priv->clk);
	}
}
