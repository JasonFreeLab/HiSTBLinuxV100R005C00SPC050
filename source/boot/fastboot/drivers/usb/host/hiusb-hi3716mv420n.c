#include <asm/io.h>
#include <common.h>

/******************************************************************************/
#define BIT(nr)                     (1UL << (nr))

#define PERI_CTRL_USB0                  (REG_BASE_PERI_CTRL + 0x120)
#define PERI_CTRL_USB1                  (REG_BASE_PERI_CTRL + 0x124)
#define PERI_CTRL_USB2                  (REG_BASE_PERI_CTRL + 0x128)
#define PERI_CTRL_USB4                  (REG_BASE_PERI_CTRL + 0x130)

#define PERI_CRG46                         (REG_BASE_CRG + 0xb8)
#define PERI_CRG47                         (REG_BASE_CRG + 0xbc)

#define USB2_BUS_CKEN                   BIT(0)
#define USB2_OHCI48M_CKEN               BIT(1)
#define USB2_OHCI12M_CKEN               BIT(2)
#define USB2_OTG_UTMI_CKEN              BIT(3)
#define USB2_HST_PHY_CKEN               BIT(4)
#define USB2_UTMI0_CKEN                 BIT(5)
#define USB2_UTMI1_CKEN                 BIT(6)
#define USB2_UTMI2_CKEN                 BIT(7)
#define USB2_ADP_CKEN                   BIT(8)
#define USB2_BUS_SRST_REQ               BIT(12)
#define USB2_UTMI0_SRST_REQ             BIT(13)
#define USB2_UTMI1_SRST_REQ             BIT(14)
#define USB2_UTMI2_SRST_REQ             BIT(15)
#define USB2_HST_PHY_SYST_REQ           BIT(16)
#define USB2_OTG_PHY_SRST_REQ           BIT(17)
#define USB2_ADP_SRST_REQ               BIT(18)
#define USB2_CLK48_SEL                  BIT(20)

#define USB_PHY0_REF_CKEN               BIT(0)
#define USB_PHY1_REF_CKEN               BIT(1)
#define USB_PHY2_REF_CKEN               BIT(2)
#define USB_PHY0_SRST_REQ               BIT(8)
#define USB_PHY0_SRST_TREQ              BIT(9)
#define USB_PHY1_SRST_REQ               BIT(10)
#define USB_PHY1_SRST_TREQ              BIT(11)
#define USB_PHY2_SRST_REQ               BIT(12)
#define USB_PHY2_SRST_TREQ              BIT(13)
#define USB_PHY0_REFCLK_SEL             BIT(16)
#define USB_PHY1_REFCLK_SEL             BIT(17)
#define USB_PHY2_REFCLK_SEL             BIT(18)

#define WORDINTERFACE                   BIT(0)
#define ULPI_BYPASS_EN_PORT0            BIT(3)
#define ULPI_BYPASS_EN_PORT1_2          BIT(4)
#define SS_BURST4_EN                    BIT(7)
#define SS_BURST8_EN                    BIT(8)
#define SS_BURST16_EN                   BIT(9)
#define DWC_OTG_EN                      BIT(28)

#define PHY_TXPREEMPAMPTUNE_MASK        ~(0x3 << 27)
#define PHY_TXPREEMPAMPTUNE_VALUE       (0x3 << 27)
#define PHY_TXVREFTUNE_MASK             ~(0xF << 0)
#define PHY_TXVREFTUNE_VALUE            (0x8 << 0)
#define PHY_SIDDQ_MASK                  ~(0x1 << 22)
#define PHY_SIDDQ_VALUE                 BIT(22)
/******************************************************************************/
extern void udelay(unsigned long usec);

static void inno_phy_config_2p(void)
{
	/* config PHY clock */
	writel(0xA00604, PERI_CTRL_USB1);
	writel(0xE00604, PERI_CTRL_USB1);
	writel(0xA00604, PERI_CTRL_USB1);
	mdelay(10);

	/* 0x02[6:4] 3'b100:412.5mV phy0/1 */
	writel(0xa0024c, PERI_CTRL_USB1);
	writel(0xe0024c, PERI_CTRL_USB1);
	writel(0xa0024c, PERI_CTRL_USB1);
	udelay(100);

	writel(0xa1024c, PERI_CTRL_USB1);
	writel(0xe1024c, PERI_CTRL_USB1);
	writel(0xa1024c, PERI_CTRL_USB1);
	udelay(100);

	/* driver slew rate tunning 0x1d[3:1] phy0/1 */
	writel(0xa01d1e, PERI_CTRL_USB1);
	writel(0xe01d1e, PERI_CTRL_USB1);
	writel(0xa01d1e, PERI_CTRL_USB1);
	udelay(100);

	writel(0xa11d1e, PERI_CTRL_USB1);
	writel(0xe11d1e, PERI_CTRL_USB1);
	writel(0xa11d1e, PERI_CTRL_USB1);
	udelay(100);

	/* disconnects 0x04[7:4] 4'b0001:625mV phy0/1 */
	writel(0xa00417, PERI_CTRL_USB1);
	writel(0xe00417, PERI_CTRL_USB1);
	writel(0xa00417, PERI_CTRL_USB1);
	udelay(100);
	writel(0xa10417, PERI_CTRL_USB1);
	writel(0xe10417, PERI_CTRL_USB1);
	writel(0xa10417, PERI_CTRL_USB1);
	udelay(100);

	/* EOP pre-emphasis off */
	writel(0xa00018, PERI_CTRL_USB1);
	writel(0xe00018, PERI_CTRL_USB1);
	writel(0xa00018, PERI_CTRL_USB1);
	udelay(100);

	writel(0xa10018, PERI_CTRL_USB1);
	writel(0xe10018, PERI_CTRL_USB1);
	writel(0xa10018, PERI_CTRL_USB1);
	udelay(100);

	/* the second handshake config phy0/1 */
	writel(0xa01f0e, PERI_CTRL_USB1);
	writel(0xe01f0e, PERI_CTRL_USB1);
	writel(0xa01f0e, PERI_CTRL_USB1);
	udelay(100);

	writel(0xa11f0e, PERI_CTRL_USB1);
	writel(0xe11f0e, PERI_CTRL_USB1);
	writel(0xa11f0e, PERI_CTRL_USB1);
	udelay(100);
}
/******************************************************************************/

static int usb0_cpu_init(void)
{
	u32 reg;

	reg = readl(PERI_CTRL_USB2);
	reg |= PHY_SIDDQ_VALUE;
	writel(reg, PERI_CTRL_USB2);

	reg = readl(PERI_CTRL_USB4);
	reg |= PHY_SIDDQ_VALUE;
	writel(reg, PERI_CTRL_USB4);
	udelay(2000);

	/* reset enable */
	reg = readl(PERI_CRG46);
	reg |= (USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_UTMI2_SRST_REQ
		| USB2_HST_PHY_SYST_REQ
		| USB2_OTG_PHY_SRST_REQ
		| USB2_CLK48_SEL);

	writel(reg, PERI_CRG46);
	udelay(200);

	reg = readl(PERI_CRG47);
	reg |= (USB_PHY0_SRST_REQ
		| USB_PHY1_SRST_REQ
		| USB_PHY2_SRST_REQ
		| USB_PHY0_SRST_TREQ
		| USB_PHY1_SRST_TREQ
		| USB_PHY2_SRST_TREQ);
	writel(reg, PERI_CRG47);
	udelay(200);

	reg = readl(PERI_CTRL_USB0);
	reg |= ULPI_BYPASS_EN_PORT0;
	reg &= ~(WORDINTERFACE);
	reg &= ~(SS_BURST16_EN);
	writel(reg, PERI_CTRL_USB0);

	udelay(100);

	/* open ref clk */
	reg = readl(PERI_CRG47);
	reg |= (USB_PHY0_REF_CKEN
		| USB_PHY1_REF_CKEN
		| USB_PHY2_REF_CKEN);
	writel(reg, PERI_CRG47);
	udelay(300);

	/* cancel power on reset */
	reg = readl(PERI_CRG47);
	reg &= ~(USB_PHY0_SRST_REQ
		| USB_PHY1_SRST_REQ
		| USB_PHY2_SRST_REQ);
	writel(reg, PERI_CRG47);
	udelay(300);

	inno_phy_config_2p();

	/* cancel port reset */
	reg = readl(PERI_CRG47);
	reg &=~(USB_PHY0_SRST_TREQ
		| USB_PHY1_SRST_TREQ
		| USB_PHY2_SRST_TREQ);
	reg |= (USB_PHY0_REF_CKEN
		| USB_PHY1_REF_CKEN
		| USB_PHY2_REF_CKEN);
	writel(reg, PERI_CRG47);
	mdelay(10);

	/* cancel control reset */
	reg = readl(PERI_CRG46);
	reg &=~(USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_UTMI2_SRST_REQ
		| USB2_HST_PHY_SYST_REQ
		| USB2_OTG_PHY_SRST_REQ);
	reg |= (USB2_BUS_CKEN
		| USB2_OHCI48M_CKEN
		| USB2_OHCI12M_CKEN
		| USB2_OTG_UTMI_CKEN
		| USB2_HST_PHY_CKEN
		| USB2_UTMI0_CKEN
		| USB2_UTMI1_CKEN
		| USB2_UTMI2_CKEN
		| USB2_ADP_CKEN);
	writel(reg, PERI_CRG46);
	udelay(200);


	reg = readl(PERI_CTRL_USB2);
	reg &= PHY_SIDDQ_MASK;
	reg &= ~PHY_SIDDQ_VALUE;
	writel(reg, PERI_CTRL_USB2);
	udelay(200);

	reg = readl(PERI_CTRL_USB4);
	reg &= PHY_SIDDQ_MASK;
	reg &= ~PHY_SIDDQ_VALUE;
	writel(reg, PERI_CTRL_USB4);
	udelay(200);

	return 0;
}
/******************************************************************************/

static int usb0_cpu_stop(void)
{
	u32 reg;

	reg = readl(PERI_CRG47);
	reg |=(USB_PHY0_SRST_REQ
		| USB_PHY1_SRST_REQ
		| USB_PHY2_SRST_REQ
		| USB_PHY0_SRST_TREQ
		| USB_PHY1_SRST_TREQ
		| USB_PHY2_SRST_TREQ);
	writel(reg, PERI_CRG47);
	udelay(100);

	/* close clock */
	reg = readl(PERI_CRG47);
	reg &=~ (USB_PHY0_REFCLK_SEL
		| USB_PHY1_REFCLK_SEL
		| USB_PHY2_REFCLK_SEL
		| USB_PHY0_REF_CKEN
		| USB_PHY1_REF_CKEN
		| USB_PHY2_REF_CKEN);
	writel(reg, PERI_CRG47);
	udelay(300);

	/* close clock  */
	reg = readl(PERI_CRG46);
	reg &=~(USB2_BUS_CKEN
		| USB2_OHCI48M_CKEN
		| USB2_OHCI12M_CKEN
		| USB2_OTG_UTMI_CKEN
		| USB2_HST_PHY_CKEN
		| USB2_UTMI0_CKEN
		| USB2_UTMI1_CKEN
		| USB2_UTMI2_CKEN
		| USB2_ADP_CKEN);
	writel(reg, PERI_CRG46);
	udelay(200);
}

int usb_cpu_init(int index, unsigned int *addr)
{
	if (addr)
#ifdef  CONFIG_USB_EHCI
		*addr = REG_BASE_EHCI;
#else
		*addr = REG_BASE_OHCI;
#endif
	return usb0_cpu_init();;
}

int usb_cpu_stop(int index)
{
	return usb0_cpu_stop();
}

int usb_cpu_init_fail(void)
{
	usb0_cpu_stop();

	return 0;
}
