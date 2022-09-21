
#include <osl.h>
#include <dhd_linux.h>
#include <linux/gpio.h>

#ifdef CUSTOMER_HW_PLATFORM
#include <plat/sdhci.h>
#define	sdmmc_channel	sdmmc_device_mmc0
#endif /* CUSTOMER_HW_PLATFORM */

#if defined(BUS_POWER_RESTORE) && defined(BCMSDIO)
#include <linux/mmc/core.h>
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/sdio_func.h>
#endif /* defined(BUS_POWER_RESTORE) && defined(BCMSDIO) */

#ifdef CONFIG_DHD_USE_STATIC_BUF
extern void *dhd_wlan_mem_prealloc(int section, unsigned long size);
#endif /* CONFIG_DHD_USE_STATIC_BUF */

static int gpio_wl_reg_on = -1; // WL_REG_ON is input pin of WLAN module
#ifdef CUSTOMER_OOB
static int gpio_wl_host_wake = -1; // WL_HOST_WAKE is output pin of WLAN module
#endif

#ifdef CONFIG_PLATFORM_HISILICON
#include "mach/io.h"
#include <linux/mmc/host.h>
//#define __io_address(n) IOMEM(n)
#include "hi_drv_gpio.h"
#include "mach/hardware.h"

typedef enum hi_GPIO_DIR_E
{
	HI_DIR_OUT = 0,
	HI_DIR_IN  = 1,
} HI_GPIO_DIR_E;

#ifndef HI_MCI_HOST_ID
#define HI_MCI_HOST_ID       0            //mmc host ID
#endif

//#if defined(CONFIG_PLATFORM_HISILICON_CV200)
//CV200
//#define BCM_REG_ON_GPIO	(4*8 + 6)	//modify by hcm (7*8 + 3)
//#define BCM_OOB_INT_GPIO	(6*8 + 4)	//WL_HOST_WAKE gpio
//#elif defined(CONFIG_PLATFORM_HISILICON_MV200)
//MV200
#define BCM_REG_ON_GPIO     (4*8 + 3) //modify by hcm (7*8 + 3)     //WL_REG_ON gpio
#define BCM_OOB_INT_GPIO    (3*8 + 5) //(4*8 + 2)     //WL_HOST_WAKE gpio
//#endif

#define REG_BASE_LDO               __io_address(0xf8a2011c)
#define REG_BASE_CTRL              __io_address(0xf8a20008)

/* PERI_SD_LDO details */
#define SD_LDO_MASK                        (0x70)
#define SD_LDO_ENABLE                      BIT(5)

uint gpio_wlan_reg_on = BCM_REG_ON_GPIO;
module_param(gpio_wlan_reg_on, uint, 0644);
MODULE_PARM_DESC(gpio_wlan_reg_on, "wlan reg_on gpio num (default:gpio7_3))");

uint gpio_wlan_wake_host = BCM_OOB_INT_GPIO;
module_param(gpio_wlan_wake_host, uint, 0644);
MODULE_PARM_DESC(gpio_wlan_wake_host, "wlan wake host gpio num (default:gpio6_4))");

uint wlan_mmc_host_id = HI_MCI_HOST_ID;
module_param(wlan_mmc_host_id, uint, 0644);
MODULE_PARM_DESC(wlan_mmc_host_id, "himmc host ID (default: 0))");

static HI_S32 hi_gpio_set_value(HI_U32 gpio, HI_U32 value)
{
	HI_S32  s32Status;

	s32Status = HI_DRV_GPIO_SetDirBit(gpio, HI_DIR_OUT);
	if ( s32Status!= HI_SUCCESS ) {
		printk("BCMDHD:gpio(%d) HI_DRV_GPIO_SetDirBit HI_DIR_OUT failed \n", gpio);
		return s32Status;
	}

	s32Status = HI_DRV_GPIO_WriteBit(gpio, value);
	if ( s32Status!= HI_SUCCESS ) {
		printk("BCMDHD:gpio(%d) HI_DRV_GPIO_WriteBit value(%d) failed \n", gpio, value);
		return s32Status;
	}

	return HI_SUCCESS;
}
#endif //CONFIG_PLATFORM_HISILICON

static int
dhd_wlan_set_power(bool on
#ifdef BUS_POWER_RESTORE
, wifi_adapter_info_t *adapter
#endif /* BUS_POWER_RESTORE */
)
{
	int err = 0;
	u32 regval = 0;

	if (on) {
		printf("======== PULL WL_REG_ON(%d) HIGH! ========\n", gpio_wl_reg_on);
		if (gpio_wl_reg_on >= 0) {
			err = gpio_direction_output(gpio_wl_reg_on, 1);
			if (err) {
				printf("%s: WL_REG_ON didn't output high\n", __FUNCTION__);
				return -EIO;
			}
		}
#ifdef CONFIG_PLATFORM_HISILICON
//#if defined(CONFIG_PLATFORM_HISILICON_CV200)
//		/* step 1: config ldo 1.8V */
//		regval = readl(REG_BASE_LDO);
//		regval &= ~(SD_LDO_MASK<<16);
//		regval |= SD_LDO_ENABLE<<16;
//		writel(regval, REG_BASE_LDO);
//#endif
		//hi_gpio_set_value((5*8 + 0), 0);
		/* step 2: set reg_on high */
		hi_gpio_set_value(gpio_wlan_reg_on, 1);
#endif
#if defined(BUS_POWER_RESTORE)
#if defined(BCMSDIO)
		if (adapter->sdio_func && adapter->sdio_func->card && adapter->sdio_func->card->host) {
			printf("======== mmc_power_restore_host! ========\n");
			mmc_power_restore_host(adapter->sdio_func->card->host);
		}
#elif defined(BCMPCIE)
		OSL_SLEEP(50); /* delay needed to be able to restore PCIe configuration registers */
		if (adapter->pci_dev) {
			printf("======== pci_set_power_state PCI_D0! ========\n");
			pci_set_power_state(adapter->pci_dev, PCI_D0);
			if (adapter->pci_saved_state)
				pci_load_and_free_saved_state(adapter->pci_dev, &adapter->pci_saved_state);
			pci_restore_state(adapter->pci_dev);
			err = pci_enable_device(adapter->pci_dev);
			if (err < 0)
				printf("%s: PCI enable device failed", __FUNCTION__);
			pci_set_master(adapter->pci_dev);
		}
#endif /* BCMPCIE */
#endif /* BUS_POWER_RESTORE */
		/* Lets customer power to get stable */
		mdelay(100);
	} else {
#if defined(BUS_POWER_RESTORE)
#if defined(BCMSDIO)
		if (adapter->sdio_func && adapter->sdio_func->card && adapter->sdio_func->card->host) {
			printf("======== mmc_power_save_host! ========\n");
			mmc_power_save_host(adapter->sdio_func->card->host);
		}
#elif defined(BCMPCIE)
		if (adapter->pci_dev) {
			printf("======== pci_set_power_state PCI_D3hot! ========\n");
			pci_save_state(adapter->pci_dev);
			adapter->pci_saved_state = pci_store_saved_state(adapter->pci_dev);
			if (pci_is_enabled(adapter->pci_dev))
				pci_disable_device(adapter->pci_dev);
			pci_set_power_state(adapter->pci_dev, PCI_D3hot);
		}
#endif /* BCMPCIE */
#endif /* BUS_POWER_RESTORE */
		printf("======== PULL WL_REG_ON(%d) LOW! ========\n", gpio_wl_reg_on);
		if (gpio_wl_reg_on >= 0) {
			err = gpio_direction_output(gpio_wl_reg_on, 0);
			if (err) {
				printf("%s: WL_REG_ON didn't output low\n", __FUNCTION__);
				return -EIO;
			}
		}
#ifdef CONFIG_PLATFORM_HISILICON
		hi_gpio_set_value(gpio_wlan_reg_on, 0);
		//hi_gpio_set_value((5*8 + 0), 1);
		mdelay(100);
#endif
	}

	return err;
}

static int dhd_wlan_set_reset(int onoff)
{
	return 0;
}

static int dhd_wlan_set_carddetect(bool present)
{
	int err = 0;
	u32 regval;

#if !defined(BUS_POWER_RESTORE)
	if (present) {
#if defined(BCMSDIO)
		printf("======== Card detection to detect SDIO card! ========\n");
#ifdef CUSTOMER_HW_PLATFORM
		err = sdhci_force_presence_change(&sdmmc_channel, 1);
#endif /* CUSTOMER_HW_PLATFORM */
#ifdef CONFIG_PLATFORM_HISILICON
		/*set card_detect low to detect card*/
		regval = readl(REG_BASE_CTRL);
//#if defined(CONFIG_PLATFORM_HISILICON_CV200)
//		regval &= ~(0x1);
//#elif defined(CONFIG_PLATFORM_HISILICON_MV200)			
		regval |= 0x1;
//#endif	
		writel(regval, REG_BASE_CTRL);
#endif
#elif defined(BCMPCIE)
		printf("======== Card detection to detect PCIE card! ========\n");
#endif
	} else {
#if defined(BCMSDIO)
		printf("======== Card detection to remove SDIO card! ========\n");
#ifdef CUSTOMER_HW_PLATFORM
		err = sdhci_force_presence_change(&sdmmc_channel, 0);
#endif /* CUSTOMER_HW_PLATFORM */
#ifdef CONFIG_PLATFORM_HISILICON
		/*set card_detect high to remove card*/
		regval = readl(REG_BASE_CTRL);
//#if defined(CONFIG_PLATFORM_HISILICON_CV200)
//		regval |= 0x1;			
//#elif defined(CONFIG_PLATFORM_HISILICON_MV200)			
		regval &= ~(0x1);
//#endif	
		writel(regval, REG_BASE_CTRL);	
#endif
#elif defined(BCMPCIE)
		printf("======== Card detection to remove PCIE card! ========\n");
#endif
	}
#endif /* BUS_POWER_RESTORE */

	return err;
}

static int dhd_wlan_get_mac_addr(unsigned char *buf)
{
	int err = 0;

	printf("======== %s ========\n", __FUNCTION__);
#ifdef EXAMPLE_GET_MAC
	/* EXAMPLE code */
	{
		struct ether_addr ea_example = {{0x00, 0x11, 0x22, 0x33, 0x44, 0xFF}};
		bcopy((char *)&ea_example, buf, sizeof(struct ether_addr));
	}
#endif /* EXAMPLE_GET_MAC */

	return err;
}

#if !defined(WL_WIRELESS_EXT)
struct cntry_locales_custom {
	char iso_abbrev[WLC_CNTRY_BUF_SZ];	/* ISO 3166-1 country abbreviation */
	char custom_locale[WLC_CNTRY_BUF_SZ];	/* Custom firmware locale */
	int32 custom_locale_rev;		/* Custom local revisin default -1 */
};
#endif

static struct cntry_locales_custom brcm_wlan_translate_custom_table[] = {
	/* Table should be filled out based on custom platform regulatory requirement */
	{"",   "XT", 49},  /* Universal if Country code is unknown or empty */
	{"US", "US", 0},
};

#ifdef CUSTOM_FORCE_NODFS_FLAG
struct cntry_locales_custom brcm_wlan_translate_nodfs_table[] = {
	{"",   "XT", 50},  /* Universal if Country code is unknown or empty */
	{"US", "US", 0},
};
#endif

static void *dhd_wlan_get_country_code(char *ccode
#ifdef CUSTOM_FORCE_NODFS_FLAG
	, u32 flags
#endif
)
{
	struct cntry_locales_custom *locales;
	int size;
	int i;

	if (!ccode)
		return NULL;

#ifdef CUSTOM_FORCE_NODFS_FLAG
	if (flags & WLAN_PLAT_NODFS_FLAG) {
		locales = brcm_wlan_translate_nodfs_table;
		size = ARRAY_SIZE(brcm_wlan_translate_nodfs_table);
	} else {
#endif
		locales = brcm_wlan_translate_custom_table;
		size = ARRAY_SIZE(brcm_wlan_translate_custom_table);
#ifdef CUSTOM_FORCE_NODFS_FLAG
	}
#endif

	for (i = 0; i < size; i++)
		if (strcmp(ccode, locales[i].iso_abbrev) == 0)
			return &locales[i];
	return NULL;
}

struct resource dhd_wlan_resources[] = {
	[0] = {
		.name	= "bcmdhd_wlan_irq",
		.start	= 0, /* Dummy */
		.end	= 0, /* Dummy */
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_SHAREABLE
			| IORESOURCE_IRQ_HIGHLEVEL, /* Dummy */
	},
};

struct wifi_platform_data dhd_wlan_control = {
	.set_power	= dhd_wlan_set_power,
	.set_reset	= dhd_wlan_set_reset,
	.set_carddetect	= dhd_wlan_set_carddetect,
	.get_mac_addr	= dhd_wlan_get_mac_addr,
#ifdef CONFIG_DHD_USE_STATIC_BUF
	.mem_prealloc	= dhd_wlan_mem_prealloc,
#endif /* CONFIG_DHD_USE_STATIC_BUF */
	.get_country_code = dhd_wlan_get_country_code,
};

int dhd_wlan_init_gpio(void)
{
	int err = 0;
#ifdef CUSTOMER_OOB
	int host_oob_irq = -1;
	uint host_oob_irq_flags = 0;
#endif

	/* Please check your schematic and fill right GPIO number which connected to
	* WL_REG_ON and WL_HOST_WAKE.
	*/
	gpio_wl_reg_on = -1;
#ifdef CUSTOMER_OOB
	gpio_wl_host_wake = BCM_OOB_INT_GPIO;
#endif

	printf("%s: GPIO(WL_REG_ON) = %d\n", __FUNCTION__, gpio_wl_reg_on);
	if (gpio_wl_reg_on >= 0) {
		err = gpio_request(gpio_wl_reg_on, "WL_REG_ON");
		if (err < 0) {
			printf("%s: Faiiled to request gpio %d for WL_REG_ON\n",
				__FUNCTION__, gpio_wl_reg_on);
			gpio_wl_reg_on = -1;
		}
	}

#ifdef CUSTOMER_OOB
	printf("%s: GPIO(WL_HOST_WAKE) = %d\n", __FUNCTION__, gpio_wl_host_wake);
	if (gpio_wl_host_wake >= 0) {
		err = gpio_request(gpio_wl_host_wake, "bcmdhd");
		if (err < 0) {
			printf("%s: gpio_request failed\n", __FUNCTION__);
			return -1;
		}
		err = gpio_direction_input(gpio_wl_host_wake);
		if (err < 0) {
			printf("%s: gpio_direction_input failed\n", __FUNCTION__);
			gpio_free(gpio_wl_host_wake);
			return -1;
		}
		host_oob_irq = gpio_to_irq(gpio_wl_host_wake);
		if (host_oob_irq < 0) {
			printf("%s: gpio_to_irq failed\n", __FUNCTION__);
			gpio_free(gpio_wl_host_wake);
			return -1;
		}
	}
	printf("%s: host_oob_irq: %d\n", __FUNCTION__, host_oob_irq);

#ifdef HW_OOB
#ifdef HW_OOB_LOW_LEVEL
	host_oob_irq_flags = IORESOURCE_IRQ | IORESOURCE_IRQ_LOWLEVEL | IORESOURCE_IRQ_SHAREABLE;
#else
	host_oob_irq_flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL | IORESOURCE_IRQ_SHAREABLE;
#endif
#else
	host_oob_irq_flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE | IORESOURCE_IRQ_SHAREABLE;
#endif

	dhd_wlan_resources[0].start = dhd_wlan_resources[0].end = host_oob_irq;
	dhd_wlan_resources[0].flags = host_oob_irq_flags;
	printf("%s: host_oob_irq_flags=0x%x\n", __FUNCTION__, host_oob_irq_flags);
#endif /* CUSTOMER_OOB */

	return 0;
}

static void dhd_wlan_deinit_gpio(void)
{
	if (gpio_wl_reg_on >= 0) {
		printf("%s: gpio_free(WL_REG_ON %d)\n", __FUNCTION__, gpio_wl_reg_on);
		gpio_free(gpio_wl_reg_on);
		gpio_wl_reg_on = -1;
	}
#ifdef CUSTOMER_OOB
	if (gpio_wl_host_wake >= 0) {
		printf("%s: gpio_free(WL_HOST_WAKE %d)\n", __FUNCTION__, gpio_wl_host_wake);
		gpio_free(gpio_wl_host_wake);
		gpio_wl_host_wake = -1;
	}
#endif /* CUSTOMER_OOB */
}

int dhd_wlan_init_plat_data(void)
{
	int err = 0;

	printf("======== %s ========\n", __FUNCTION__);
	err = dhd_wlan_init_gpio();
	return err;
}

void dhd_wlan_deinit_plat_data(wifi_adapter_info_t *adapter)
{
	printf("======== %s ========\n", __FUNCTION__);
	dhd_wlan_deinit_gpio();
}

