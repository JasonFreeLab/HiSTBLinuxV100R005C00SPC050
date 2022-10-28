#include "util.h"
#include "higmac.h"
#include "ctrl.h"

#define MAC0_RST_BIT	BIT(0)
#define MAC0_CLK_BIT	BIT(1)
#define MACIF0_RST_BIT	BIT(2)
#define MACIF0_CLK_BIT	BIT(3)
#define MAC1_CLK_BIT	BIT(9)
#define MAC_PUB_CLK_BIT	BIT(10)
#define MAC1_RST_BIT	BIT(12)
#define MACIF1_CLK_BIT	BIT(13)
#define MACIF1_RST_BIT	BIT(14)

#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3799MV310) || defined(CONFIG_ARCH_HI3796MV2X)
#define PHY0_RST_BIT	BIT(5)
#define PHY1_RST_BIT	BIT(15)
#else
#define PHY0_RST_BIT	BIT(12)
#define PHY1_RST_BIT	BIT(13)
#endif

#ifdef MAC_USE_INTERNAL_FEPHY
/* register REG_CRG_FEPHY */
#define BIT_FEPHY_CLK           BIT(0)
#define BIT_FEPHY_RST           BIT(4)
#define BIT_MASK_FEPHY_ADDR	0x1F
/* register PERI_FEPHY_LDO */
#define BIT_LDO_EN		BIT(4)
#define BIT_LDO_ENZ		BIT(5)
#define BIT_LDO_RSTN		BIT(6)
#define BIT_IDDQ_MODE		BIT(7)
#endif

#define msleep(a)	udelay((a) * 1000)

#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3799MV310) || defined(CONFIG_ARCH_HI3796MV2X)
void higmac_set_macif(struct higmac_netdev_local *ld, int mode, int speed)
{
	unsigned int p = HIGMAC_SYS_CTL_IO_BASE;
	unsigned long v;

	/* enable change: port_mode */
	higmac_writel_bits(ld, 1, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);
	if (speed == 2)/* FIXME */
		speed = 5;/* 1000M */
	higmac_writel_bits(ld, speed, PORT_MODE, BITS_PORT_MODE);
	/* disable change: port_mode */
	higmac_writel_bits(ld, 0, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);

	/* soft reset mac_if */
	v = readl(p + RESET_CTRL);
	v |= (ld->index ? MACIF1_RST_BIT : MACIF0_RST_BIT);
	writel(v, p + RESET_CTRL);

	/* config mac_if */
	if (ld->index)/* eth1 */
		writel(mode, HIGMAC_MACIF1_CTRL);
	else
		writel(mode, HIGMAC_MACIF0_CTRL);

	v = readl(p + RESET_CTRL);
	v &= ~(ld->index ? MACIF1_RST_BIT : MACIF0_RST_BIT);
	writel(v, p + RESET_CTRL);
}
#else
void higmac_set_macif(struct higmac_netdev_local *ld, int mode, int speed)
{
	unsigned int p = HIGMAC_SYS_CTL_IO_BASE;
	unsigned long v;

	/* enable change: port_mode */
	higmac_writel_bits(ld, 1, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);
	if (speed == 2)/* FIXME */
		speed = 5;/* 1000M */
	higmac_writel_bits(ld, speed, PORT_MODE, BITS_PORT_MODE);
	/* disable change: port_mode */
	higmac_writel_bits(ld, 0, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);

	/* soft reset mac_if */
	v = readl(p + RESET_CTRL);
#if GMAC_AT_LEAST_3PORT
	if (ld->index < 2) {
		if (_HI3798CV100A == get_chipid() || _HI3798CV100 == get_chipid()
				|| _HI3796CV100 == get_chipid())
			v |= BIT(ld->index + 14);/* bit10 mac_if0 */
		else
			v |= BIT(ld->index + 10);/* bit10 mac_if0 */
	} else
		v |= BIT(23);
#else
	if (_HI3798CV100A == get_chipid() || _HI3798CV100 == get_chipid()
			|| _HI3796CV100 == get_chipid())
		v |= BIT(ld->index + 14);/* bit10 mac_if0 */
	else
		v |= BIT(ld->index + 10);/* bit10 mac_if0 */
#endif
	writel(v, p + RESET_CTRL);

	/* config mac_if */
#if GMAC_AT_LEAST_3PORT
	if (ld->index == 2)/* eth2 */
		writel(mode, HIGMAC_MACIF2_CTRL);
	else if (ld->index == 1)/* eth1 */
		writel(mode, HIGMAC_MACIF1_CTRL);
	else
		writel(mode, HIGMAC_MACIF0_CTRL);
#else
	if (ld->index)/* eth1 */
		writel(mode, HIGMAC_MACIF1_CTRL);
	else
		writel(mode, HIGMAC_MACIF0_CTRL);
#endif
	v = readl(p + RESET_CTRL);
#if GMAC_AT_LEAST_3PORT
	if (ld->index < 2) {
		if (_HI3798CV100A == get_chipid() || _HI3798CV100 == get_chipid()
				|| _HI3796CV100 == get_chipid()) 
			v &= ~BIT(ld->index + 14);/* undo reset */
		else
			v &= ~BIT(ld->index + 10);/* undo reset */
	} else
		v &= ~BIT(23);
#else
	if (_HI3798CV100A == get_chipid() || _HI3798CV100 == get_chipid()
		|| _HI3796CV100 == get_chipid()) 
		v &= ~BIT(ld->index + 14);/* undo reset */
	else
		v &= ~BIT(ld->index + 10);/* undo reset */

#endif
	writel(v, p + RESET_CTRL);
}
#endif

int higmac_hw_set_macaddress(struct higmac_netdev_local *ld, unsigned char *mac)
{
	unsigned long reg;

	reg = mac[1] | (mac[0] <<8);
	higmac_writel(ld, reg, STATION_ADDR_HIGH);

	reg = mac[5] | (mac[4]<<8) | (mac[3]<<16) | (mac[2]<<24);
	higmac_writel(ld, reg, STATION_ADDR_LOW);

	return 0;
}

int higmac_hw_get_macaddress(struct higmac_netdev_local *ld, unsigned char *mac)
{
	unsigned long reg;

	reg = higmac_readl(ld, STATION_ADDR_HIGH);
	mac[0] = (reg>>8) & 0xff;
	mac[1] = reg & 0xff;

	reg = higmac_readl(ld, STATION_ADDR_LOW);
	mac[2] = (reg>>24) & 0xff;
	mac[3] = (reg>>16) & 0xff;
	mac[4] = (reg>>8) & 0xff;
	mac[5] = reg & 0xff;

	return 0;
}

static inline int _higmac_read_irqstatus(struct higmac_netdev_local *ld)
{
	int status;

	status = higmac_readl(ld, STATUS_PMU_INT);

	return status;
}

int higmac_clear_irqstatus(struct higmac_netdev_local *ld, int irqs)
{
	int status;

	higmac_writel(ld, irqs, RAW_PMU_INT);
	status = _higmac_read_irqstatus(ld);

	return status;
}

/*FIXME*/
int higmac_glb_preinit_dummy(struct higmac_netdev_local *ld)
{
	/* drop packet enable */
	higmac_writel(ld, 0x3F, REC_FILT_CONTROL);
	higmac_writel_bits(ld, 0, REC_FILT_CONTROL, BIT_BC_DROP_EN);

	/* fix bug for udp and ip error check */
	higmac_writel(ld, CONTROL_WORD_CONFIG, CONTROL_WORD);

	/*clear all interrupt status*/
	higmac_clear_irqstatus(ld, RAW_INT_ALL_MASK);

	/* disable interrupts */
	higmac_writel(ld, ~RAW_INT_ALL_MASK, ENA_PMU_INT);

	return 0;
}

#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3799MV310) || defined(CONFIG_ARCH_HI3796MV2X)
/* reset phy by GMAC CRG register */
void higmac_reset_phy_by_crg(void)
{
	unsigned long p = 0;
	unsigned int v = 0;

	p = (unsigned long)(HIGMAC_SYS_CTL_IO_BASE);

	/* write 0 to undo reset */
	v = readl(p + RESET_CTRL);
	v &= ~PHY0_RST_BIT;
#if GMAC_AT_LEAST_2PORT
	v &= ~PHY1_RST_BIT;
#endif
	writel(v, p + RESET_CTRL);

	msleep(10);

	/* write 1 to reset phy */
	v = readl(p + RESET_CTRL);
	v |= PHY0_RST_BIT;
#if GMAC_AT_LEAST_2PORT
	v |= PHY1_RST_BIT;
#endif
	writel(v, p + RESET_CTRL);

	/* reset time */
	msleep(30);

	/* write 0 to undo reset */
	v = readl(p + RESET_CTRL);
	v &= ~PHY0_RST_BIT;
#if GMAC_AT_LEAST_2PORT
	v &= ~PHY1_RST_BIT;
#endif
	writel(v, p + RESET_CTRL);

	/* delay at least 30ms for MDIO operation */
	msleep(30);
}

#ifdef MAC_USE_INTERNAL_FEPHY
static void higmac_reset_internal_fephy(void)
{
	unsigned int crg_iobase = 0;
	unsigned int peri_iobase = 0;
	volatile unsigned int val = 0;

	crg_iobase = REG_BASE_CRG;

	/* MDCK clock disable */
	val = readl(crg_iobase + REG_CRG_GSF);
	val &= ~(MACIF0_CLK_BIT | MAC0_CLK_BIT);
	writel(val, crg_iobase + REG_CRG_GSF);

	/* reset FEPHY and load PHY address */
	peri_iobase = REG_BASE_PERI_CTRL;

	/* PERI_FEPHY_LDO_CTRL config. */
	val = readl(peri_iobase + REG_PERI_FEPHY_LDO);
	val |= (BIT_LDO_EN | BIT_LDO_RSTN);
	val &= ~(BIT_LDO_ENZ | BIT_IDDQ_MODE);
	writel(val, peri_iobase + REG_PERI_FEPHY_LDO);

	/* FEPHY enable clock */
	val = readl(crg_iobase + REG_CRG_FEPHY);
	val |= BIT_FEPHY_CLK;
	writel(val, crg_iobase + REG_CRG_FEPHY);

	/* set FEPHY address */
	val = readl(peri_iobase + REG_PERI_FEPHY);
	val &= ~BIT_MASK_FEPHY_ADDR;
	val |= (higmac_board_info[0].phy_addr & BIT_MASK_FEPHY_ADDR);
	writel(val, peri_iobase + REG_PERI_FEPHY);

	/* FEPHY set reset */
	val = readl(crg_iobase + REG_CRG_FEPHY);
	val |= BIT_FEPHY_RST;
	writel(val, crg_iobase + REG_CRG_FEPHY);

	udelay(10);

	/* FEPHY cancel reset */
	val = readl(crg_iobase + REG_CRG_FEPHY);
	val &= ~BIT_FEPHY_RST;
	writel(val, crg_iobase + REG_CRG_FEPHY);

	mdelay(20);

	/* MDCK clock enable */
	val = readl(crg_iobase + REG_CRG_GSF);
	val |= (MACIF0_CLK_BIT | MAC0_CLK_BIT);
	writel(val, crg_iobase + REG_CRG_GSF);

	mdelay(5);
}

static void higmac_trim_internal_fephy(void)
{
	mdelay(300);
}

static void higmac_init_internal_fephy(void)
{
	higmac_reset_internal_fephy();
	higmac_trim_internal_fephy();
}
#endif

/* TODO: power on gmac here */
void higmac_sys_init(void)
{
	unsigned long p = 0;
	volatile unsigned int v = 0;

	/*soft reset*/
	p = (unsigned long)(HIGMAC_SYS_CTL_IO_BASE);

	/* clock enable */
	v = readl(p + RESET_CTRL);
	v |= MACIF0_CLK_BIT | MAC0_CLK_BIT;
#if GMAC_AT_LEAST_2PORT
	v |= MACIF1_CLK_BIT | MAC1_CLK_BIT | MAC_PUB_CLK_BIT;
#endif
	writel(v, p + RESET_CTRL);

	/* reset mac and mac_if */
	v = readl(p + RESET_CTRL);
	v |= MACIF0_RST_BIT | MAC0_RST_BIT;
#if GMAC_AT_LEAST_2PORT
	v |= MACIF1_RST_BIT | MAC1_RST_BIT;
#endif
	writel(v, p + RESET_CTRL);

	udelay(10);

	/* undo reset */
	v = readl(p + RESET_CTRL);
	v &= ~(MACIF0_RST_BIT | MAC0_RST_BIT);
#if GMAC_AT_LEAST_2PORT
	v &= ~(MACIF1_RST_BIT | MAC1_RST_BIT);
#endif
	writel(v, p + RESET_CTRL);

	higmac_reset_phy_by_crg();
#ifdef MAC_USE_INTERNAL_FEPHY
	higmac_init_internal_fephy();
#endif
}
#else
/* reset phy by GMAC CRG register */
void higmac_reset_phy_by_crg(void)
{
	unsigned long p = 0;
	unsigned int v = 0;

	p = (unsigned long)(HIGMAC_SYS_CTL_IO_BASE);

	/* write 1 to undo reset */
	v = readl(p + RESET_CTRL);
	v |= (PHY0_RST_BIT | PHY1_RST_BIT);
	writel(v, p + RESET_CTRL);

	msleep(10);

	/* write 0 to reset phy */
	v = readl(p + RESET_CTRL);
	v &= ~(PHY0_RST_BIT | PHY1_RST_BIT);
	writel(v, p + RESET_CTRL);

	/* reset time */
	msleep(30);

	/* write 1 to undo reset */
	v = readl(p + RESET_CTRL);
	v |= (PHY0_RST_BIT | PHY1_RST_BIT);
	writel(v, p + RESET_CTRL);

	/* delay at least 30ms for MDIO operation */
	msleep(30);
}

/* TODO: power on gmac here */
void higmac_sys_init(void)
{
	unsigned long p = 0;
	volatile unsigned int v = 0;

#ifdef CONFIG_HI3716MV410_FPGA
	/* timing */
	writel(0x40033002, 0xF8A20050);
#endif

	/*soft reset*/
	p = (unsigned long)(HIGMAC_SYS_CTL_IO_BASE);

	v = readl(p + RESET_CTRL);
	if (_HI3798CV100A == get_chipid() || _HI3798CV100 == get_chipid()
		|| _HI3796CV100 == get_chipid()) 
		v |= 0x0f3ff;//reset g1, g0, mac_if1, mac_if0
	else if (_HI3716M_V410 == get_chipid())
		v |= 7 << 22;
	else
		v |= 0x0f3f;//reset g1, g0, mac_if1, mac_if0
#if GMAC_AT_LEAST_3PORT
	v |= 0x7fc0000;
#endif
	writel(v, p + RESET_CTRL);

	udelay(10);

	v = readl(p + RESET_CTRL);
	if (_HI3798CV100A == get_chipid() || _HI3798CV100 == get_chipid()
		|| _HI3796CV100 == get_chipid()) 
		v &= ~(0xf << 12);//undo reset
	else if (_HI3716M_V410 == get_chipid())
		v &= ~(3 << 22);
	else
#if defined(CONFIG_ARCH_HIFONE) || defined(CONFIG_ARCH_HI3798CV2X)
		v &= ~(1<<11 | 1<< 10 | 1<<9 | 1 <<8);//undo reset
#else
		v = 0x3f;//undo reset
#endif
#if GMAC_AT_LEAST_3PORT
	v |= 0x73c0000;
	v &= ~(0x3 << 22);
#endif
	writel(v, p + RESET_CTRL);
#ifdef MAC_USE_INTERNAL_FEPHY
	writel(0, INTERNAL_FEPHY_CTRL);
	udelay(10);
	/* suppose inside fephy can only be mac0's phy */
	writeb(higmac_board_info[0].phy_addr & 0x1F, INTERNAL_FEPHY_ADDR);

	v = readl(INTERNAL_FEPHY_LDO);
	/* set internal FEPHY LDO_VSET value */
	v = (v & ~LDO_VSET_MASK) | LDO_VSET_VAL;
#if defined(CONFIG_ARCH_HIFONE)
	/* enalbe internal FEPHY LDO_EN for hifone_b02 */
	v |= BIT_LDO_EN;
#endif
	writel(v, INTERNAL_FEPHY_LDO);

	/* reset internal FEPHY */
	v = 0x1; /* use 25MHz clock, enable clk */
	writel(v, INTERNAL_FEPHY_CTRL);

	udelay(10);

	v = readl(INTERNAL_FEPHY_CTRL);
	v |= BIT_FEPHY_RST; /* reset */
	writel(v, INTERNAL_FEPHY_CTRL);

	udelay(10);

	v = readl(INTERNAL_FEPHY_CTRL);
	v &= ~BIT_FEPHY_RST; /* undo reset */
	writel(v, INTERNAL_FEPHY_CTRL);
#endif

	/* PHY_RSTN reset */
	v = readl(MAC1_PHY_RESET_BASE);
	v |= MAC1_PHY_RESET_BIT;
	writel(v, MAC1_PHY_RESET_BASE);

	udelay(20000);

	/* then, cancel reset, and should delay 200ms */
	v &= ~MAC1_PHY_RESET_BIT;
	writel(v, MAC1_PHY_RESET_BASE);

	udelay(20000);
	v |= MAC1_PHY_RESET_BIT;
	writel(v, MAC1_PHY_RESET_BASE);

	udelay(15000); /* delay at least 15ms for MDIO operation */

#if defined(CONFIG_ARCH_HIFONE) || defined(CONFIG_ARCH_HI3798CV2X)
	higmac_reset_phy_by_crg();
#endif

#if GMAC_AT_LEAST_3PORT
	writel(0xe, HIGMAC_DUAL_MAC_CRF_ACK_TH);
	writel(0xe, HIGMAC_THIRD_MAC_CRF_ACK_TH);
#endif
}
#endif

void higmac_sys_allstop(void)
{

}

int higmac_set_hwq_depth(struct higmac_netdev_local *ld)
{
	if(HIGMAC_HWQ_RX_FQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH)
	{
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, RX_FQ_REG_EN, \
		BITS_RX_FQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_RX_FQ_DEPTH << DESC_WORD_SHIFT, RX_FQ_DEPTH, \
		BITS_RX_FQ_DEPTH);

	higmac_writel_bits(ld, 0, RX_FQ_REG_EN, \
		BITS_RX_FQ_DEPTH_EN);

	if(HIGMAC_HWQ_RX_BQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH)
	{
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, RX_BQ_REG_EN, \
		BITS_RX_BQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_RX_BQ_DEPTH << DESC_WORD_SHIFT, RX_BQ_DEPTH, \
		BITS_RX_BQ_DEPTH);

	higmac_writel_bits(ld, 0, RX_BQ_REG_EN, \
		BITS_RX_BQ_DEPTH_EN);

	if(HIGMAC_HWQ_TX_BQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH)
	{
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, TX_BQ_REG_EN, \
		BITS_TX_BQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_TX_BQ_DEPTH << DESC_WORD_SHIFT, TX_BQ_DEPTH, \
		BITS_TX_BQ_DEPTH);

	higmac_writel_bits(ld, 0, TX_BQ_REG_EN, \
		BITS_TX_BQ_DEPTH_EN);

	if(HIGMAC_HWQ_TX_RQ_DEPTH > HIGMAC_MAX_QUEUE_DEPTH)
	{
		BUG();
		return -1;
	}

	higmac_writel_bits(ld, 1, TX_RQ_REG_EN, \
		BITS_TX_RQ_DEPTH_EN);

	higmac_writel_bits(ld, HIGMAC_HWQ_TX_RQ_DEPTH << DESC_WORD_SHIFT, TX_RQ_DEPTH, \
		BITS_TX_RQ_DEPTH);

	higmac_writel_bits(ld, 0, TX_RQ_REG_EN, \
		BITS_TX_RQ_DEPTH_EN);

	return 0;
}

int higmac_set_rx_fq_hwq_addr(struct higmac_netdev_local *ld, unsigned int phy_addr)
{
	higmac_writel_bits(ld, 1, RX_FQ_REG_EN, \
		BITS_RX_FQ_START_ADDR_EN);

	higmac_writel(ld, phy_addr, RX_FQ_START_ADDR);

	higmac_writel_bits(ld, 0, RX_FQ_REG_EN, \
		BITS_RX_FQ_START_ADDR_EN);

	return 0;
}

int higmac_set_rx_bq_hwq_addr(struct higmac_netdev_local *ld, unsigned int phy_addr)
{
	higmac_writel_bits(ld, 1, RX_BQ_REG_EN, \
		BITS_RX_BQ_START_ADDR_EN);

	higmac_writel(ld, phy_addr, RX_BQ_START_ADDR);

	higmac_writel_bits(ld, 0, RX_BQ_REG_EN, \
		BITS_RX_BQ_START_ADDR_EN);

	return 0;
}

int higmac_set_tx_bq_hwq_addr(struct higmac_netdev_local *ld, unsigned int phy_addr)
{
	higmac_writel_bits(ld, 1, TX_BQ_REG_EN, \
		BITS_TX_BQ_START_ADDR_EN);

	higmac_writel(ld, phy_addr, TX_BQ_START_ADDR);

	higmac_writel_bits(ld, 0, TX_BQ_REG_EN, \
		BITS_TX_BQ_START_ADDR_EN);

	return 0;
}

int higmac_set_tx_rq_hwq_addr(struct higmac_netdev_local *ld, unsigned int phy_addr)
{
	higmac_writel_bits(ld, 1, TX_RQ_REG_EN, \
		BITS_TX_RQ_START_ADDR_EN);

	higmac_writel(ld, phy_addr, TX_RQ_START_ADDR);

	higmac_writel_bits(ld, 0, TX_RQ_REG_EN, \
		BITS_TX_RQ_START_ADDR_EN);

	return 0;
}

int higmac_desc_enable(struct higmac_netdev_local *ld, int desc_ena)
{
	int old;

	old = higmac_readl(ld, DESC_WR_RD_ENA);
	higmac_writel(ld, old | desc_ena, DESC_WR_RD_ENA);

	return old;
}

int higmac_desc_disable(struct higmac_netdev_local *ld, int desc_dis)
{
	int old;

	old = higmac_readl(ld, DESC_WR_RD_ENA);
	higmac_writel(ld, old & (~desc_dis), DESC_WR_RD_ENA);

	return old;
}

void higmac_desc_flush(struct higmac_netdev_local *ld)
{
	higmac_writel_bits(ld, 1, STOP_CMD, BITS_TX_STOP_EN);
	while(higmac_readl_bits(ld,FLUSH_CMD, BITS_TX_FLUSH_FLAG) != 1);
	higmac_writel_bits(ld, 1, FLUSH_CMD, BITS_TX_FLUSH_CMD);
	while(higmac_readl_bits(ld,FLUSH_CMD, BITS_TX_FLUSH_FLAG) != 0);
	higmac_writel_bits(ld, 0, FLUSH_CMD, BITS_TX_FLUSH_CMD);
	higmac_writel_bits(ld, 0, STOP_CMD, BITS_TX_STOP_EN);

	higmac_writel_bits(ld, 1, STOP_CMD, BITS_RX_STOP_EN);
	while(higmac_readl_bits(ld,FLUSH_CMD, BITS_RX_FLUSH_FLAG) != 1);
	higmac_writel_bits(ld, 1, FLUSH_CMD, BITS_RX_FLUSH_CMD);
	while(higmac_readl_bits(ld,FLUSH_CMD, BITS_RX_FLUSH_FLAG) != 0);
	higmac_writel_bits(ld, 0, FLUSH_CMD, BITS_RX_FLUSH_CMD);
	higmac_writel_bits(ld, 0, STOP_CMD, BITS_RX_STOP_EN);
}
