#include "higmac.h"
#include "phy_fix.h"
#include "mdio.h"

static const u32 phy_fix_param[] = {
#include "festa_v200.h"
};

static const u32 phy_v300_fix_param[] = {
#include "festa_v300_2204.h"
};

#ifdef HIGMAC_INTERNAL_PHY_TRIM
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

static inline int higmac_phy_expanded_read(struct mii_bus *bus, int phyaddr,
					   u32 reg_addr)
{
	int ret;

	higmac_mdio_write(bus, phyaddr, MII_EXPMA, reg_addr);
	ret = higmac_mdio_read(bus, phyaddr, MII_EXPMD);

	return ret;
}

static inline int higmac_phy_expanded_write(struct mii_bus *bus, int phyaddr,
					    u32 reg_addr, u16 val)
{
	int ret;

	higmac_mdio_write(bus, phyaddr, MII_EXPMA, reg_addr);
	ret = higmac_mdio_write(bus, phyaddr, MII_EXPMD, val);

	return ret;
}

void higmac_use_default_trim(struct mii_bus *bus, int phyaddr)
{
	unsigned short v;
	int timeout = 3;

	pr_info("No OTP data, festa PHY use default ATE parameters!\n");

	do {
		msleep(250);
		v = higmac_phy_expanded_read(bus, phyaddr, REG_DEF_ATE);
		v &= BIT(0);
	} while (!v && --timeout);
	WARN(!timeout, "festa PHY 0x3057 wait bit0 timeout!\n");

	mdelay(5);
}
#endif

#ifdef HIGMAC_INTERNAL_PHY_TRIM
void higmac_internal_fephy_trim(struct mii_bus *bus, int phyaddr,
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
		higmac_use_default_trim(bus, phyaddr);
		return;
	}

	ld_amptlitude = trim_params & LD_AM_MASK;
	ldo_amptlitude = (trim_params >> 8) & LDO_AM_MASK;
	r_tuning_val = (trim_params >> 16) & R_TUNING_MASK;

	v = higmac_phy_expanded_read(bus, phyaddr, REG_LD_AM);
	v = (v & ~LD_AM_MASK) | (ld_amptlitude & LD_AM_MASK);
	higmac_phy_expanded_write(bus, phyaddr, REG_LD_AM, v);

	v = higmac_phy_expanded_read(bus, phyaddr, REG_LDO_AM);
	v = (v & ~LDO_AM_MASK) | (ldo_amptlitude & LDO_AM_MASK);
	higmac_phy_expanded_write(bus, phyaddr, REG_LDO_AM, v);

	v = higmac_phy_expanded_read(bus, phyaddr, REG_R_TUNING);
	v = (v & ~R_TUNING_MASK) | (r_tuning_val & R_TUNING_MASK);
	higmac_phy_expanded_write(bus, phyaddr, REG_R_TUNING, v);

	v = higmac_phy_expanded_read(bus, phyaddr, REG_WR_DONE);
	WARN(v & BIT(1), "festa PHY 0x3053 bit1 CFG_ACK value: 1\n");
	v = v | BIT(0);
	higmac_phy_expanded_write(bus, phyaddr, REG_WR_DONE, v);

	do {
		usleep_range(100, 150);
		v = higmac_phy_expanded_read(bus, phyaddr, REG_WR_DONE);
		v &= BIT(1);
	} while (!v && --timeout);
	WARN(!timeout, "festa PHY 0x3053 wait bit1 CFG_ACK timeout!\n");

	mdelay(5);

	pr_info("FEPHY:addr=%d, la_am=0x%x, ldo_am=0x%x, r_tuning=0x%x\n",
		phyaddr,
		higmac_phy_expanded_read(bus, phyaddr, REG_LD_AM),
		higmac_phy_expanded_read(bus, phyaddr, REG_LDO_AM),
		higmac_phy_expanded_read(bus, phyaddr, REG_R_TUNING));
}
#else
void higmac_internal_fephy_trim(struct mii_bus *bus, int phyaddr,
				u32 trim_params)
{
}
#endif

static int __maybe_unused set_phy_expanded_access_mode(struct phy_device *phy_dev, int access_mode)
{
	int v, ret;

	v = phy_read(phy_dev, MII_MISC_CTL);
	v &= (~0x3);
	v |= (access_mode & 0x3);
	ret = phy_write(phy_dev, MII_MISC_CTL, v);

	return ret;
}

static int __maybe_unused phy_expanded_read(struct phy_device *phy_dev, u32 reg_addr)
{
	int v, ret;

	v = phy_read(phy_dev, MII_BMCR);
	v |= BMCR_PDOWN;
	phy_write(phy_dev, MII_BMCR, v);

	phy_write(phy_dev, MII_EXPMA, reg_addr);
	ret = phy_read(phy_dev, MII_EXPMD);

	v = phy_read(phy_dev, MII_BMCR);
	v &= (~BMCR_PDOWN);
	phy_write(phy_dev, MII_BMCR, v);

	return ret;
}

static int __maybe_unused phy_expanded_write(struct phy_device *phy_dev, u32 reg_addr, u16 val)
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

static int phy_expanded_write_bulk(struct phy_device *phy_dev, const u32 reg_and_val[],
			    int count)
{
	int i, v, ret = 0;
	u32 reg_addr;
	u16 val;

	v = phy_read(phy_dev, MII_BMCR);
	v |= BMCR_PDOWN;
	phy_write(phy_dev, MII_BMCR, v);

	for (i = 0; i < (2 * count); i += 2) {
		reg_addr = reg_and_val[i];
		val = (u16) reg_and_val[i + 1];
		phy_write(phy_dev, MII_EXPMA, reg_addr);
		ret = phy_write(phy_dev, MII_EXPMD, val);
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

	count = sizeof(phy_fix_param) / sizeof(phy_fix_param[0]);
	if (count % 2)
		pr_warn("internal FEPHY fix register count is not right.\n");
	count /= 2;

	phy_expanded_write_bulk(phy_dev, phy_fix_param, count);

	return 0;
}

static int hisilicon_fephy_v300_fix(struct phy_device *phy_dev)
{
	int count;

	count = sizeof(phy_v300_fix_param) / sizeof(phy_v300_fix_param[0]);
	if (count % 2)
		pr_warn("internal FEPHY fix register count is not right.\n");
	count /= 2;

	phy_expanded_write_bulk(phy_dev, phy_v300_fix_param, count);

	return 0;
}

/*
 * for a better Electromagnetic Compatibility
 */
static int realtek_gephy_fix(struct phy_device *phy_dev)
{
#if 0
	int v;

	pr_info("RealTek phy fix: phy id=0x%x\n", phy_dev->phy_id);

	v = phy_read(phy_dev, 16);      /* PHYCR reg */
	v |= 1 << 4;                    /* clk125 remains at logic low */
	phy_write(phy_dev, 16, v);

	phy_write(phy_dev, 31, 0x0007);	/* set to extension page */
	phy_write(phy_dev, 30, 0x00A0);	/* set to extension page 160 */

	v = phy_read(phy_dev, 26);
	v &= ~(1 << 2);			/* enable RXC SSC */
	phy_write(phy_dev, 26, v);

	phy_write(phy_dev, 31, 0x0);	/* back to page 0 */

#endif

	return 0;
}

/* copy from phy_quirk() in hieth-sf/net.c */
static int KSZ8051MNL_phy_fix(struct phy_device *phy_dev)
{
	u32 v;

	if (phy_dev->interface != PHY_INTERFACE_MODE_RMII)
		return 0;

	v = phy_read(phy_dev, 0x1F);
	v |= (1 << 7);       /* set phy RMII 50MHz clk; */
	phy_write(phy_dev, 0x1F, v);

	v = phy_read(phy_dev, 0x16);
	v |= (1 << 1);       /* set phy RMII override; */
	phy_write(phy_dev, 0x16, v);

	return 0;
}

/* copy from phy_quirk() in hieth-sf/net.c */
static int KSZ8081RNB_phy_fix(struct phy_device *phy_dev)
{
	u32 v;

	if (phy_dev->interface != PHY_INTERFACE_MODE_RMII)
		return 0;

	v = phy_read(phy_dev, 0x1F);
	v |= (1 << 7);       /* set phy RMII 50MHz clk; */
	phy_write(phy_dev, 0x1F, v);

	return 0;
}

static int KSZ9031RNX_phy_fix(struct phy_device *phy_dev)
{
	u32 v;

	/* RX_CLK Pad Skew: 1_1101(+0.84) */
	v = phy_mmd_read(phy_dev, 0x2, 0x8);
	v = (v & ~0x1F) | 0x1D;
	phy_mmd_write(phy_dev, 0x2, 0x8, v);

	return 0;
}

static int at803x_phy_debug_read(struct phy_device *phy_dev, u32 reg_addr)
{
	int ret;

	phy_write(phy_dev, MII_ATH_DEBUG_ADDR, reg_addr);
	ret = phy_read(phy_dev, MII_ATH_DEBUG_DATA);

	return ret;
}

static int at803x_phy_debug_write(struct phy_device *phy_dev, u32 reg_addr, u16 val)
{
	int ret;

	phy_write(phy_dev, MII_ATH_DEBUG_ADDR, reg_addr);
	ret = phy_write(phy_dev, MII_ATH_DEBUG_DATA, val);

	return ret;
}

static int at803x_phy_fix(struct phy_device *phy_dev)
{
	/* PHY-AR8035 */
	u16 tx_delay;
	int ret;

	/* enable rgmii tx clock delay */
	tx_delay = at803x_phy_debug_read(phy_dev, 0x05);
	tx_delay |= BIT(8);
	ret = at803x_phy_debug_write(phy_dev, 0x05, tx_delay);

	return ret;
}

#define RTL8211F_PAGE_SELECT	0x1f
#define RTL8211F_TX_DELAY	BIT(8)
static int rtl8211f_phy_fix(struct phy_device *phy_dev)
{
	u16 reg;

	if (phy_dev->interface != PHY_INTERFACE_MODE_RGMII)
		return 0;

	/* enable TXDLY */
	phy_write(phy_dev, RTL8211F_PAGE_SELECT, 0xd08);
	reg = phy_read(phy_dev, 0x11);
	reg |= RTL8211F_TX_DELAY;
	phy_write(phy_dev, 0x11, reg);
	/* restore to default page 0 */
	phy_write(phy_dev, RTL8211F_PAGE_SELECT, 0x0);

	return 0;
}

void phy_register_fixups(void)
{
	phy_register_fixup_for_uid(REALTEK_PHY_ID_8211EG,
			REALTEK_PHY_MASK, realtek_gephy_fix);
	phy_register_fixup_for_uid(HISILICON_PHY_ID_FESTAV200,
			HISILICON_PHY_MASK, hisilicon_fephy_fix);
	phy_register_fixup_for_uid(HISILICON_PHY_ID_FESTAV300,
			HISILICON_PHY_MASK, hisilicon_fephy_v300_fix);
	phy_register_fixup_for_uid(PHY_ID_KSZ8051MNL,
			DEFAULT_PHY_MASK, KSZ8051MNL_phy_fix);
	phy_register_fixup_for_uid(PHY_ID_KSZ8081RNB,
			DEFAULT_PHY_MASK, KSZ8081RNB_phy_fix);
	phy_register_fixup_for_uid(PHY_ID_KSZ9031RNX,
			DEFAULT_PHY_MASK, KSZ9031RNX_phy_fix);
	phy_register_fixup_for_uid(ATH8035_PHY_ID,
			ATH_PHY_ID_MASK, at803x_phy_fix);
	phy_register_fixup_for_uid(PHY_ID_RTL8211F,
			PHY_ID_MASK_RTL8211F, rtl8211f_phy_fix);
}

void phy_unregister_fixups(void)
{
	phy_unregister_fixup_for_uid(REALTEK_PHY_ID_8211EG, REALTEK_PHY_MASK);
	phy_unregister_fixup_for_uid(HISILICON_PHY_ID_FESTAV200,
				     HISILICON_PHY_MASK);
	phy_unregister_fixup_for_uid(HISILICON_PHY_ID_FESTAV300,
				     HISILICON_PHY_MASK);
	phy_unregister_fixup_for_uid(PHY_ID_KSZ8051MNL, DEFAULT_PHY_MASK);
	phy_unregister_fixup_for_uid(PHY_ID_KSZ8081RNB, DEFAULT_PHY_MASK);
	phy_unregister_fixup_for_uid(PHY_ID_KSZ9031RNX, DEFAULT_PHY_MASK);
	phy_unregister_fixup_for_uid(ATH8035_PHY_ID, ATH_PHY_ID_MASK);
	phy_unregister_fixup_for_uid(PHY_ID_RTL8211F, PHY_ID_MASK_RTL8211F);
}
