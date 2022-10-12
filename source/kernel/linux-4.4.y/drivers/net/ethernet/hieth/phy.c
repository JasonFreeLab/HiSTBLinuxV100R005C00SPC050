#include <linux/platform_device.h>
#include <linux/hikapi.h>
#include <linux/hisilicon_phy.h>
#include "hieth.h"
#include "mdio.h"
#include "phy.h"

static const u32 phy_fix_param[] = {
#include "festa_v220.h"
};

static const u32 phy212_fix_param[] = {
#include "festa_v212.h"
};

/* Hi3798MV200 */
static const u32 phy330_fix_param[] = {
#include "festa_v330.h"
};

/* Hi3798MV300 */
static const u32 phy_s28v112_fix_param[] = {
#include "festa_s28v112.h"
};

static unsigned int fephy_ed_time_in_sec = DEFAULT_FEPHY_ED_TIME;

static int phy_expanded_write(struct phy_device *phy_dev, u32 reg_addr, u16 val)
{
	int v, ret;

	v = phy_read(phy_dev, MII_BMCR);
	v |= BMCR_PDOWN;
	phy_write(phy_dev, MII_BMCR, v);

	phy_write(phy_dev, MII_EXPMA, reg_addr);
	ret = phy_write(phy_dev, MII_EXPMD, val);

	v = phy_read(phy_dev, MII_BMCR);
	v &= (~BMCR_PDOWN);
	phy_write(phy_dev, MII_BMCR, v);

	return ret;
}

#define CONFIG_FEPHY_TRIM
#ifdef CONFIG_FEPHY_TRIM
#define REG_LD_AM		0x3050
#define LD_AM_MASK		GENMASK(4, 0)
#define REG_LDO_AM		0x3051
#define LDO_AM_MASK		GENMASK(2, 0)
#define REG_R_TUNING		0x3052
#define R_TUNING_MASK		GENMASK(5, 0)
#define REG_WR_DONE		0x3053
#define REG_DEF_ATE		0x3057
#define DEF_LD_AM		0x0f
#define DEF_LDO_AM		0x7
#define DEF_R_TUNING		0x15

static inline int hieth_phy_expanded_read(struct mii_bus *bus, int phyaddr,
						u32 reg_addr)
{
	int ret;

	hieth_mdiobus_write(bus, phyaddr, MII_EXPMA, reg_addr);
	ret = hieth_mdiobus_read(bus, phyaddr, MII_EXPMD);

	return ret;
}

static inline int hieth_phy_expanded_write(struct mii_bus *bus, int phyaddr,
						u32 reg_addr, u16 val)
{
	int ret;

	hieth_mdiobus_write(bus, phyaddr, MII_EXPMA, reg_addr);
	ret = hieth_mdiobus_write(bus, phyaddr, MII_EXPMD, val);

	return ret;
}

void hieth_use_default_trim(struct mii_bus *bus, int phyaddr)
{
	unsigned short v;
	int timeout = 3;

	pr_info("FEPHY: No OTP data, use default ATE parameters to auto-trim!\n");

	do {
		msleep(250);
		v = hieth_phy_expanded_read(bus, phyaddr, REG_DEF_ATE);
		v &= BIT(0);
	} while (!v && --timeout);

	if (!timeout)
		pr_warn("FEPHY: fail to wait auto-trim finish!\n");
}

void hieth_config_festa_phy_trim(struct mii_bus *bus, int phyaddr,
					u32 trim_params)
{
	unsigned short ld_amptlitude;
	unsigned short ldo_amptlitude;
	unsigned short r_tuning_val;
	unsigned short v;
	int timeout = 3000;

	ld_amptlitude = DEF_LD_AM;
	ldo_amptlitude = DEF_LDO_AM;
	r_tuning_val = DEF_R_TUNING;

	if (!trim_params) {
		hieth_use_default_trim(bus, phyaddr);
		return;
	}

	ld_amptlitude = trim_params & LD_AM_MASK;
	ldo_amptlitude = (trim_params >> 8) & LDO_AM_MASK;
	r_tuning_val = (trim_params >> 16) & R_TUNING_MASK;

	v = hieth_phy_expanded_read(bus, phyaddr, REG_LD_AM);
	v = (v & ~LD_AM_MASK) | (ld_amptlitude & LD_AM_MASK);
	hieth_phy_expanded_write(bus, phyaddr, REG_LD_AM, v);

	v = hieth_phy_expanded_read(bus, phyaddr, REG_LDO_AM);
	v = (v & ~LDO_AM_MASK) | (ldo_amptlitude & LDO_AM_MASK);
	hieth_phy_expanded_write(bus, phyaddr, REG_LDO_AM, v);

	v = hieth_phy_expanded_read(bus, phyaddr, REG_R_TUNING);
	v = (v & ~R_TUNING_MASK) | (r_tuning_val & R_TUNING_MASK);
	hieth_phy_expanded_write(bus, phyaddr, REG_R_TUNING, v);

	v = hieth_phy_expanded_read(bus, phyaddr, REG_WR_DONE);
	if (v & BIT(1))
		pr_warn("FEPHY: invalid trim status.\n");
	v = v | BIT(0);
	hieth_phy_expanded_write(bus, phyaddr, REG_WR_DONE, v);

	do {
		usleep_range(100, 150);
		v = hieth_phy_expanded_read(bus, phyaddr, REG_WR_DONE);
		v &= BIT(1);
	} while (!v && --timeout);
	if (!timeout)
		pr_warn("FEPHY: faile to wait trim finish!\n");

	pr_info("FEPHY:addr=%d, la_am=0x%x, ldo_am=0x%x, r_tuning=0x%x\n",
		phyaddr,
		hieth_phy_expanded_read(bus, phyaddr, REG_LD_AM),
		hieth_phy_expanded_read(bus, phyaddr, REG_LDO_AM),
		hieth_phy_expanded_read(bus, phyaddr, REG_R_TUNING));
}
#endif

#ifdef CONFIG_FEPHY_TRIM
void hieth_fix_festa_phy_trim(struct mii_bus *bus, struct hieth_platdrv_data *pdata)
{
	struct hieth_phy_param_s *phy_param;
	int i;
	int phyaddr;

	if ((_HI3798MV200 != get_chipid(0ULL))&&
		(_HI3798MV300 != get_chipid(0ULL)) &&
		(_HI3798MV300_H != get_chipid(0ULL)) &&
		(_HI3798MV310 != get_chipid(0ULL)))
		return;

	for (i = 0; i < HIETH_MAX_PORT; i++) {
		phy_param = &pdata->hieth_phy_param[i];

		if (!phy_param->isvalid || !phy_param->isinternal)
			continue;

		phyaddr = phy_param->phy_addr;
		hieth_config_festa_phy_trim(bus, phyaddr,
				phy_param->trim_params);
		mdelay(5);
	}
}
#else
void hieth_fix_festa_phy_trim(struct mii_bus *bus, struct hieth_platdrv_data *pdata)
{
	msleep(300);
}
#endif

static int phy_expanded_write_bulk(struct phy_device *phy_dev,
				   const u32 reg_and_val[],
				   int count)
{
	int i, v, ret = 0;
	u32 reg_addr;
	u16 val;

	v = phy_read(phy_dev, MII_BMCR);
	v |= BMCR_PDOWN;
	phy_write(phy_dev, MII_BMCR, v);

	for (i = 0; i < (2 * count); i += 2) {
		if ((i % 50) == 0)
			schedule();

		reg_addr = reg_and_val[i];
		val = (u16)reg_and_val[i + 1];
		hieth_mdiobus_write_nodelay(phy_dev->bus, phy_dev->addr,
					    MII_EXPMA, reg_addr);
		ret = hieth_mdiobus_write_nodelay(phy_dev->bus, phy_dev->addr,
						  MII_EXPMD, val);
	}

	v = phy_read(phy_dev, MII_BMCR);
	v &= (~BMCR_PDOWN);
	phy_write(phy_dev, MII_BMCR, v);

	return ret;
}

/* fix FEPHY for better eye diagram */
static int hisilicon_fephy_fix(struct phy_device *phy_dev)
{
	int count;

	count = ARRAY_SIZE(phy_fix_param);
	if (count % 2)
		pr_warn("internal FEPHY fix register count is not right.\n");
	count /= 2;

	phy_expanded_write_bulk(phy_dev, phy_fix_param, count);
	udelay(200);
	phy_expanded_write(phy_dev, 0x01ff, 0x13);

	return 0;
}

/* fix FEPHY for better eye diagram */
static int hisilicon_fephy212_fix(struct phy_device *phy_dev)
{
	int count;

	count = ARRAY_SIZE(phy212_fix_param);
	if (count % 2)
		pr_warn("internal FEPHY fix register count is not right.\n");
	count /= 2;

	phy_expanded_write_bulk(phy_dev, phy212_fix_param, count);

	return 0;
}

static int hisilicon_fephy330_fix(struct phy_device *phy_dev)
{
	int count;

	count = ARRAY_SIZE(phy330_fix_param);
	if (count % 2)
		pr_warn("internal FEPHY fix register count is not right.\n");
	count /= 2;

	phy_expanded_write_bulk(phy_dev, phy330_fix_param, count);

	/* disable FEPHY ED mode */
	if (hieth_fephy_opt)
		phy_write(phy_dev, 0x0b, 0);

	return 0;
}

inline bool fephy_ed_time_is_valid(unsigned int ed_time)
{
	return (ed_time >= MIN_FEPHY_ED_TIME && ed_time <= MAX_FEPHY_ED_TIME);
}

unsigned int fephy_get_ed_time(void)
{
	return fephy_ed_time_in_sec;
}

int fephy_set_ed_time(struct phy_device *phy_dev, unsigned int ed_time)
{
	int ret = 0;

	if (!fephy_ed_time_is_valid(ed_time))
		return -EINVAL;

	fephy_ed_time_in_sec = ed_time;
	ret = phy_expanded_write(phy_dev, REG_FEPHY_ED_TIME,
				 ED_TIME_SEC_TO_REG(fephy_ed_time_in_sec));

	return ret;
}

static int hisilicon_fephy_s28v112_fix(struct phy_device *phy_dev)
{
	int ret = 0;
	int count;

	count = ARRAY_SIZE(phy_s28v112_fix_param);
	if (count % 2)
		pr_warn("internal FEPHY fix register count is not right.\n");
	count /= 2;

	phy_expanded_write_bulk(phy_dev, phy_s28v112_fix_param, count);

	ret = fephy_set_ed_time(phy_dev, fephy_ed_time_in_sec);

	return ret;
}

static int KSZ8051MNL_phy_fix(struct phy_device *phy_dev)
{
	u32 v;

	v = phy_read(phy_dev, 0x1F);
	v |= (1 << 7);       /* set phy RMII 50MHz clk; */
	phy_write(phy_dev, 0x1F, v);

	v = phy_read(phy_dev, 0x16);
	v |= (1 << 1);       /* set phy RMII override; */
	phy_write(phy_dev, 0x16, v);

	return 0;
}

static int KSZ8081RNB_phy_fix(struct phy_device *phy_dev)
{
	u32 v;

	v = phy_read(phy_dev, 0x1F);
	v |= (1 << 7);       /* set phy RMII 50MHz clk; */
	phy_write(phy_dev, 0x1F, v);

	return 0;
}

void hieth_phy_register_fixups(void)
{
	phy_register_fixup_for_uid(HISILICON_PHY_ID_FESTAV220,
				   HISILICON_PHY_ID_MASK, hisilicon_fephy_fix);
	phy_register_fixup_for_uid(HISILICON_PHY_ID_FESTAV212,
				   HISILICON_PHY_ID_MASK, hisilicon_fephy212_fix);
	phy_register_fixup_for_uid(HISILICON_PHY_ID_FESTAV330,
				   HISILICON_PHY_ID_MASK, hisilicon_fephy330_fix);
	phy_register_fixup_for_uid(HISILICON_PHY_ID_FESTA_S28V112,
				   HISILICON_PHY_ID_MASK,
				   hisilicon_fephy_s28v112_fix);
	phy_register_fixup_for_uid(PHY_ID_KSZ8051MNL,
				   DEFAULT_PHY_MASK, KSZ8051MNL_phy_fix);
	phy_register_fixup_for_uid(PHY_ID_KSZ8081RNB,
				   DEFAULT_PHY_MASK, KSZ8081RNB_phy_fix);
}

void hieth_phy_unregister_fixups(void)
{
	phy_unregister_fixup_for_uid(HISILICON_PHY_ID_FESTAV220,
				     HISILICON_PHY_ID_MASK);
	phy_unregister_fixup_for_uid(HISILICON_PHY_ID_FESTAV212,
				     HISILICON_PHY_ID_MASK);
	phy_unregister_fixup_for_uid(HISILICON_PHY_ID_FESTAV330,
				     HISILICON_PHY_ID_MASK);
	phy_unregister_fixup_for_uid(HISILICON_PHY_ID_FESTA_S28V112,
				     HISILICON_PHY_ID_MASK);
	phy_unregister_fixup_for_uid(PHY_ID_KSZ8051MNL, DEFAULT_PHY_MASK);
	phy_unregister_fixup_for_uid(PHY_ID_KSZ8081RNB, DEFAULT_PHY_MASK);
}

static void hieth_internal_phy_clk_disable(void)
{
	unsigned int val;
	void *hieth_sys_regbase = ioremap_nocache(0xF8A22000, 0x1000);

	/* FEPHY disable clock and keep reset */
	val = readl(hieth_sys_regbase + HIETHPHY_SYSREG_REG);
	val &= ~BIT(0);
	val |= BIT(4);
	writel(val, hieth_sys_regbase + HIETHPHY_SYSREG_REG);

	iounmap(hieth_sys_regbase);
}

static void hieth_internal_phy_reset(struct hieth_phy_param_s *phy_param)
{
	unsigned int val;
	void *hieth_sys_regbase = ioremap_nocache(0xF8A22000, 0x1000);
	void *hieth_fephy_base = ioremap_nocache(0xF8A20000, 0x1000);

	if ((get_chipid(0ULL) == _HI3716MV410) ||
		(get_chipid(0ULL) == _HI3716MV420N) ||
		(get_chipid(0ULL) == _HI3716MV410N) ||
		(get_chipid(0ULL) == _HI3716MV420)) {
		/* LDO output 1.1V */
		writel(0x8, hieth_fephy_base + HIETH_FEPHY_LDO_CTRL);
	} else if ((get_chipid(0ULL) == _HI3798MV200)
		|| (get_chipid(0ULL) == _HI3798MV300)
		|| (get_chipid(0ULL) == _HI3798MV300_H)
		|| (get_chipid(0ULL) == _HI3798MV310)) {
		val = readl(hieth_fephy_base + HIETH_FEPHY_LDO_CTRL);
		val |= BIT(4) | BIT(6);
		val &= ~(BIT(5) | BIT(7));
		writel(val, hieth_fephy_base + HIETH_FEPHY_LDO_CTRL);
	} else {
		val = readl(hieth_fephy_base + HIETH_FEPHY_SELECT);
		if ((val & (1 << 8)) != 0)
			return;/* if not use fephy, leave it's clk disabled */

		/* LDO output 1.1V */
		writel(0x68, hieth_fephy_base + HIETH_FEPHY_LDO_CTRL);
	}

	/* FEPHY enable clock */
	val = readl(hieth_sys_regbase + HIETHPHY_SYSREG_REG);
	val |= (1);
	writel(val, hieth_sys_regbase + HIETHPHY_SYSREG_REG);

	/* set FEPHY address */
	val = readl(hieth_fephy_base + HIETH_FEPHY_ADDR);
	val &= ~(0x1F);
	val |= (phy_param->phy_addr & 0x1F);
	writel(val, hieth_fephy_base + HIETH_FEPHY_ADDR);

	/* FEPHY set reset */
	val = readl(hieth_sys_regbase + HIETHPHY_SYSREG_REG);
	val |= (1 << 4);
	writel(val, hieth_sys_regbase + HIETHPHY_SYSREG_REG);

	usleep_range(10, 1000);

	/* FEPHY cancel reset */
	val = readl(hieth_sys_regbase + HIETHPHY_SYSREG_REG);
	val &= ~(1 << 4);
	writel(val, hieth_sys_regbase + HIETHPHY_SYSREG_REG);

	msleep(20); /* delay at least 15ms for MDIO operation */

	iounmap(hieth_sys_regbase);
	iounmap(hieth_fephy_base);
}

void hieth_gpio_reset(void __iomem *gpio_base, u32 gpio_bit)
{
	u32 v;

#define RESET_DATA      (1)

	if (!gpio_base)
		return;

	gpio_base = (void *)ioremap_nocache((unsigned long)gpio_base, 0x1000);

	/* config gpio[x] dir to output */
	v = readb(gpio_base + 0x400);
	v |= (1 << gpio_bit);
	writeb(v, gpio_base + 0x400);

	/* output 1--0--1 */
	writeb(RESET_DATA << gpio_bit, gpio_base + (4 << gpio_bit));
	msleep(20);
	writeb((!RESET_DATA) << gpio_bit, gpio_base + (4 << gpio_bit));
	msleep(20);
	writeb(RESET_DATA << gpio_bit, gpio_base + (4 << gpio_bit));
	msleep(20);

	iounmap(gpio_base);
}

static void hieth_external_phy_reset(struct hieth_phy_param_s *phy_param)
{
	unsigned int val;
	void *hieth_sys_regbase = ioremap_nocache(0xF8A22000, 0x1000);
	void *hieth_fephy_base = ioremap_nocache(0xF8A20000, 0x1000);

	if ((get_chipid(0ULL) == _HI3716MV410) ||
		(get_chipid(0ULL) == _HI3716MV420N) ||
		(get_chipid(0ULL) == _HI3716MV420)) {
		;
	} else {
		/* if use internal fephy, return */
		val = readl(hieth_fephy_base + HIETH_FEPHY_SELECT);
		if ((val & (1 << 8)) == 0)
			return;
	}

	/************************************************/
	/* reset external phy with default reset pin */
	val = readl(hieth_sys_regbase + HIETH_FEPHY_RST_BASE);
	val |= (1 << HIETH_FEPHY_RST_BIT);
	writel(val, hieth_sys_regbase + HIETH_FEPHY_RST_BASE);

	msleep(20);

	/* then, cancel reset, and should delay 200ms */
	val &= ~(1 << HIETH_FEPHY_RST_BIT);
	writel(val, hieth_sys_regbase + HIETH_FEPHY_RST_BASE);

	msleep(20);
	val |=  1 << HIETH_FEPHY_RST_BIT;
	writel(val, hieth_sys_regbase + HIETH_FEPHY_RST_BASE);

	/************************************************/
	/* reset external phy with gpio */
	hieth_gpio_reset(phy_param->gpio_base, phy_param->gpio_bit);

	/************************************************/

	/* add some delay in case mdio cann't access now! */
	msleep(30);

	iounmap(hieth_sys_regbase);
	iounmap(hieth_fephy_base);
}

void hieth_phy_reset(struct hieth_platdrv_data *pdata)
{
	int i;
	struct hieth_phy_param_s *phy_param;

	for (i = 0; i < HIETH_MAX_PORT; i++) {
		phy_param = &pdata->hieth_phy_param[i];

		if (!phy_param->isvalid)
			continue;

		if (phy_param->isinternal)
			hieth_internal_phy_reset(phy_param);
		else
			hieth_external_phy_reset(phy_param);
	}
}

void hieth_phy_clk_disable(struct hieth_platdrv_data *pdata)
{
	int i;
	struct hieth_phy_param_s *phy_param;

	for (i = 0; i < HIETH_MAX_PORT; i++) {
		phy_param = &pdata->hieth_phy_param[i];

		if (!phy_param->isvalid)
			continue;

		if (phy_param->isinternal)
			hieth_internal_phy_clk_disable();
	}
}
