#ifndef __HIETH_FEPHY_FIX_H
#define __HIETH_FEPHY_FIX_H

#ifdef CONFIG_ARM64
#  ifdef CONFIG_ARCH_HI3798MV2X
#    define HIETHPHY_SYSREG_REG         0x0388
#  endif
#endif
#define HIETH_FEPHY_ADDR                0x118
#define HIETH_FEPHY_SELECT              0x8
#define HIETH_FEPHY_LDO_CTRL            0x844

/* DEFAULT external phy reset pin */
#define HIETH_FEPHY_RST_BASE            0x168
#define HIETH_FEPHY_RST_BIT             1

#define MII_EXPMD			0x1D
#define MII_EXPMA			0x1E

/* the following two copied from phy_quirk()
 * in "./drivers/net/ethernet/hieth-sf/net.c"
 */
#define PHY_ID_KSZ8051MNL		0x00221550
#define PHY_ID_KSZ8081RNB		0x00221560
#define DEFAULT_PHY_MASK		0xfffffff0

#define REG_FEPHY_ED_TIME		0x3160
#define DEFAULT_FEPHY_ED_TIME		(8 * 60)
#define MIN_FEPHY_ED_TIME		13
#define MAX_FEPHY_ED_TIME		(10 * 60)
#define ED_TIME_SEC_TO_REG(sec)		(((sec) * 4 / 10) - 1)
#endif
