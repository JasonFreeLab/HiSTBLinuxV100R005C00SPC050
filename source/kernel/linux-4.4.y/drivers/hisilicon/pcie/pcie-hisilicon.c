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
 * Create By Liu Hui 2015.09.20
 *
******************************************************************************/
#define DRVNAME "hipcie"
#define pr_fmt(fmt) DRVNAME ":" fmt

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/resource.h>
#include <linux/signal.h>
#include <linux/types.h>
#include <linux/memblock.h>
#include <linux/hisilicon/himisc.h>
#include <linux/hikapi.h>

#include "../../pci/pci.h"
#include "../../pci/host/pcie-designware.h"
/******************************************************************************/

#define PCIE_SYS_CTRL0                    0x0000
#define PCIE_SYS_CTRL1                    0x0004
#define PCIE_SYS_CTRL7                    0x001C
#define PCIE_SYS_CTRL13                   0x0034
#define PCIE_SYS_CTRL15                   0x003c
#define PCIE_SYS_CTRL16                   0x0040
#define PCIE_SYS_CTRL17                   0x0044

#define PCIE_SYS_STAT0                    0x0100
#define PCIE_SYS_STAT4                    0x0110

#define PCIE_RDLH_LINK_UP                 BIT(5)
#define PCIE_XMLH_LINK_UP                 BIT(15)
#define PCIE_ELBI_SLV_DBI_ENABLE          BIT(21)
#define PCIE_APP_LTSSM_ENABLE             BIT(11)
#define PCIE_DBI_ENABLE                   BIT(13)

#define PCIE_DEVICE_TYPE_MASK            (0xf << 28)
#define PCIE_WM_EP                       (0x0 << 28)
#define PCIE_WM_LEGACY                   (0x1 << 28)
#define PCIE_WM_RC                       (0x4 << 28)

#define PCIE_LTSSM_STATE_MASK            (0x3f)
#define PCIE_LTSSM_STATE_ACTIVE          (0x11)

#define PCIE_BAK_REG_LOCK                (0x0B50)
#define PCIE_SYS_STATE_SHW7              (0X0BC0)
#define PCIE_SYS_STATE_SHW8              (0X0BC4)
#define PCIE_SYS_STATE_SHW9              (0X0BC8)

#define PCIE_BAK_REG_LOCK_EN             (0x1 << 0)

#define PCIE_PERI_COMBPHY1_CFG           (0xf8a20858)
#define PCIE_LINK_CTRL_2_REG             (0xf00000a0)
#define PCIE_LINk2_TRANSMIT_MASK         (0x7 << 7)
#define PCIE_LINk2_TRANSMIT_700          (0x3 << 7)
/******************************************************************************/

struct hipcie_host {
	void __iomem *sys_addr;
	void __iomem *ca_reg_addr;
	void __iomem *ctrl_addr;
	struct clk *clk;
	struct pcie_port pp;
};

#define to_hipcie(x) container_of(x, struct hipcie_host, pp)
/******************************************************************************/

extern struct pcie_alloc_ctrl_t pcie_read_ctrl;
extern struct pcie_alloc_ctrl_t pcie_write_ctrl;
#if 0
static int __init early_pcie_dma_addr(char *p)
{
	u32 start, size;
	char *endp;

	start = memparse(p, &endp);
	if (*endp != ',')
		return 0;

	size = memparse(endp + 1, &endp);
	if (*endp != ',')
		return 0;

	pcie_dma_addr_read.start = start;
	pcie_dma_addr_read.size = size;

	start = memparse(endp + 1, &endp);
	if (*endp != ',')
		return 0;

	size = memparse(endp + 1, NULL);

	pcie_dma_addr_write.start = start;
	pcie_dma_addr_write.size = size;

	return 0;
}
early_param("pcieaddr", early_pcie_dma_addr);
#endif
/*****************************************************************************/

void pcie_reserve_memory(void)
{
#if 0
	u32 start, size;
	int ret;

	if ((!pcie_dma_addr_read.start) && (!pcie_dma_addr_read.size)
		&& (!pcie_dma_addr_write.start) && (!pcie_dma_addr_write.size)) {
		/* no pcieaddr in bootargs*/
		return;
	}

	start = pcie_dma_addr_read.start;
	size = pcie_dma_addr_read.size;
	if ((start&(SZ_1M- 1)) || (size&(SZ_1M- 1))) {
		pr_err("read start:%08x or size:%08x is not 1M align\n", start, size);
		goto fail;
	}

	start = pcie_dma_addr_write.start;
	size = pcie_dma_addr_write.size;
	if ((start&(SZ_1M- 1)) || (size&(SZ_1M- 1))) {
		pr_err("write start:%08x or size:%08x is not 1M align\n", start, size);
		goto fail;
	}

	ret = fdt_add_memory_reserve((u64)pcie_dma_addr_read.start, 
			(u64)pcie_dma_addr_read.size);
	if (ret)
		goto fail;
	
	ret = fdt_add_memory_reserve((u64)pcie_dma_addr_write.start, 
			(u64)pcie_dma_addr_write.size);
	if (ret)
		goto fail;
	
	pr_info("Reserved read %d MiB at 0x%08x\n", 
		pcie_dma_addr_read.size/SZ_1M, pcie_dma_addr_read.start);
	pr_info("Reserved write %d MiB at 0x%08x\n", 
		pcie_dma_addr_write.size/SZ_1M, pcie_dma_addr_write.start);

	return;

fail:
	pcie_dma_addr_read.start = 0;
	pcie_dma_addr_read.size = 0;
	pcie_dma_addr_write.start = 0;
	pcie_dma_addr_write.size =0;
	return;
#endif
}
/*****************************************************************************/

static void hipcie_dbi_w_mode(struct pcie_port *pp, bool on)
{
#if !defined (CONFIG_ARCH_HI3798MV2X) && !defined(CONFIG_ARCH_HI3796MV2X)
	u32 val;
	struct hipcie_host *hipcie = to_hipcie(pp);

	if (on) {
		val = readl(hipcie->sys_addr + PCIE_SYS_CTRL0);
		val |= PCIE_ELBI_SLV_DBI_ENABLE;
		writel(val, hipcie->sys_addr + PCIE_SYS_CTRL0);
	} else {
		val = readl(hipcie->sys_addr + PCIE_SYS_CTRL0);
		val &= ~PCIE_ELBI_SLV_DBI_ENABLE;
		writel(val, hipcie->sys_addr + PCIE_SYS_CTRL0);
	}
#endif
}
/******************************************************************************/

static void hipcie_dbi_r_mode(struct pcie_port *pp, bool on)
{
#if !defined (CONFIG_ARCH_HI3798MV2X) && !defined(CONFIG_ARCH_HI3796MV2X)
	u32 val;
	struct hipcie_host *hipcie = to_hipcie(pp);

	if (on) {
		val = readl(hipcie->sys_addr + PCIE_SYS_CTRL1);
		val |= PCIE_ELBI_SLV_DBI_ENABLE;
		writel(val, hipcie->sys_addr + PCIE_SYS_CTRL1);
	} else {
		val = readl(hipcie->sys_addr + PCIE_SYS_CTRL1);
		val &= ~PCIE_ELBI_SLV_DBI_ENABLE;
		writel(val, hipcie->sys_addr + PCIE_SYS_CTRL1);
	}
#endif
}
/******************************************************************************/

static inline void hipcie_readl_rc(struct pcie_port *pp,
				void __iomem *dbi_base, u32 *val)
{
	hipcie_dbi_r_mode(pp, true);
	*val = readl(dbi_base);
	hipcie_dbi_r_mode(pp, false);
	return;
}
/******************************************************************************/

static inline void hipcie_writel_rc(struct pcie_port *pp,
				u32 val, void __iomem *dbi_base)
{
	hipcie_dbi_w_mode(pp, true);
	writel(val, dbi_base);
	hipcie_dbi_w_mode(pp, false);
	return;
}
/******************************************************************************/

static int hipcie_rd_own_conf(struct pcie_port *pp, int where, int size,
				u32 *val)
{
	int ret;

	hipcie_dbi_r_mode(pp, true);
	ret = dw_pcie_cfg_read(pp->dbi_base + where, size, val);
	hipcie_dbi_r_mode(pp, false);
	return ret;
}
/******************************************************************************/

static int hipcie_wr_own_conf(struct pcie_port *pp, int where, int size,
				u32 val)
{
	int ret;

	hipcie_dbi_w_mode(pp, true);
	ret = dw_pcie_cfg_write(pp->dbi_base + where, size, val);
	hipcie_dbi_w_mode(pp, false);
	return ret;
}
/******************************************************************************/

static int hipcie_link_up(struct pcie_port *pp)
{
	u32 regval;
	u32 status;
	struct hipcie_host *hipcie = to_hipcie(pp);

	regval = readl(hipcie->sys_addr + PCIE_SYS_STAT0);

	status = readl(hipcie->sys_addr + PCIE_SYS_STAT4);
	status &= PCIE_LTSSM_STATE_MASK;

	if ((regval&PCIE_XMLH_LINK_UP) 	&& (regval&PCIE_RDLH_LINK_UP)
		&& (status == PCIE_LTSSM_STATE_ACTIVE)) 
		return 1;

	return 0;
}
/******************************************************************************/

static int hipcie_establish_link(struct pcie_port *pp)
{
	u32 regval;
	int count = 0;
	struct hipcie_host *hipcie = to_hipcie(pp);
	u32 reg = 0;
	void __iomem *pcie_host0_regbase = NULL;

	if (dw_pcie_link_up(pp)) {
		dev_err(pp->dev, "Link already up\n");
		return 0;
	}

#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3796MV2X)
	/* dbi read/write enable */
	regval = readl(hipcie->sys_addr + PCIE_SYS_CTRL7);
	regval |= PCIE_DBI_ENABLE;
	writel(regval,  hipcie->sys_addr + PCIE_SYS_CTRL7);
#endif

	/* PCIe RC work mode */
	regval = readl(hipcie->sys_addr + PCIE_SYS_CTRL0);
	regval &= ~PCIE_DEVICE_TYPE_MASK;
	regval |= PCIE_WM_RC ;
	writel(regval, hipcie->sys_addr + PCIE_SYS_CTRL0);

	/* setup root complex */
	dw_pcie_setup_rc(pp);

#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3796MV2X)
	/* ioremap pcie Link Control 2 Register */
	if (!pcie_host0_regbase) {
		pcie_host0_regbase = ioremap_nocache(PCIE_LINK_CTRL_2_REG, 0x20);
		if (!pcie_host0_regbase) {
			printk("ioremap pcie link control 2 register failed.\n");
			return -1;
		}
	}
	/* config pcie link control 2 transmit margin bit[9:7],011 for 700mv,000 for 1000mv */
	reg = readl(pcie_host0_regbase);
	reg &= ~PCIE_LINk2_TRANSMIT_MASK;
	reg |= PCIE_LINk2_TRANSMIT_700;
	writel(reg, pcie_host0_regbase);
	if (pcie_host0_regbase) {
		iounmap(pcie_host0_regbase);
		pcie_host0_regbase = NULL;
	}
#endif

	/* assert LTSSM enable */
	regval = readl(hipcie->sys_addr + PCIE_SYS_CTRL7);
	regval |= PCIE_APP_LTSSM_ENABLE;
	writel(regval,  hipcie->sys_addr + PCIE_SYS_CTRL7);


	/* check if the link is up or not */
	while (!dw_pcie_link_up(pp)) {
		mdelay(1);
		count++;
		if (count == 50) {
			dev_err(pp->dev, "PCIe Link Fail\n");
			return -EINVAL;
		}
	}

#if defined(CONFIG_ARCH_HI3798CV2X)
	/* only for HI3798CV200 */
	void __iomem *combophy1_cfg = NULL;
	combophy1_cfg = ioremap_nocache(PCIE_PERI_COMBPHY1_CFG, 0x20);
	if (!combophy1_cfg) {
		printk("ioremap combophy1_cfg failed.\n");
		return -1;
	}
	regval=readl(combophy1_cfg);
	printk("ComboPHY CFG:%#x\n",regval);
	/* if pcie linkup, config PWON to auto mode */
	writel(0x1203001,combophy1_cfg);
	/* release test_write */
	writel(0x0203001,combophy1_cfg);
	if(combophy1_cfg){
		iounmap(combophy1_cfg);
		combophy1_cfg = NULL;
	}
#endif

	dev_info(pp->dev, "Link up\n");

	return 0;
}
/******************************************************************************/

static void hipcie_host_init(struct pcie_port *pp)
{
	hipcie_establish_link(pp);
}
/******************************************************************************/

static struct pcie_host_ops hipcie_host_ops = {
	.readl_rc = hipcie_readl_rc,
	.writel_rc = hipcie_writel_rc,
	.rd_own_conf = hipcie_rd_own_conf,
	.wr_own_conf = hipcie_wr_own_conf,
	.link_up = hipcie_link_up,
	.host_init = hipcie_host_init,
};
/******************************************************************************/
static void hipcie_config_ddr_bank(u32 writeaddr, u32 readadddr, void *reg_addr_base)
{
	writel(writeaddr, reg_addr_base + PCIE_SYS_CTRL15);

	writel(readadddr, reg_addr_base + PCIE_SYS_CTRL16);

	writel(0x11, reg_addr_base + PCIE_SYS_CTRL17);
}
/******************************************************************************/

static int __init hipcie_pltm_probe(struct platform_device *pdev)
{
	int ret;
	u32 regvalrd;
	u32 regvalwt;
	struct hipcie_host *hipcie;
	struct pcie_port *pp;
	struct resource *res;
	unsigned int size;

	hipcie = devm_kzalloc(&pdev->dev, sizeof(*hipcie), GFP_KERNEL);
	if (!hipcie)
		return -ENOMEM;

	pp = &hipcie->pp;

	pp->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	hipcie->sys_addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hipcie->sys_addr)) {
		ret = PTR_ERR(hipcie->sys_addr);
		goto fail_clk;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	pp->dbi_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pp->dbi_base)) {
		ret = PTR_ERR(pp->dbi_base);
		goto fail_clk;
	}

#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3796MV2X)
	res = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	hipcie->ca_reg_addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hipcie->ca_reg_addr)) {
		ret = PTR_ERR(hipcie->ca_reg_addr);
		goto fail_clk;
	}
#endif

#ifdef CONFIG_ARCH_HI3796MV2X
	res = platform_get_resource(pdev, IORESOURCE_MEM, 3);
	hipcie->ctrl_addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(hipcie->ctrl_addr)) {
		ret = PTR_ERR(hipcie->ctrl_addr);
		goto fail_clk;
	}
#endif

	pp->irq = platform_get_irq(pdev, 0);
	if (!pp->irq) {
		dev_err(&pdev->dev, "failed to get irq\n");
		return -ENODEV;
	}

	hipcie->clk = devm_clk_get(&pdev->dev, "clk");
	if (IS_ERR(hipcie->clk)) {
		dev_err(&pdev->dev, "Failed to get pcie rc clock\n");
		return PTR_ERR(hipcie->clk);
	}

	if ((!pcie_read_ctrl.size) && (!pcie_write_ctrl.size)) {
		get_mem_size(&size,  HIKAPI_GET_RAM_SIZE);
		pcie_write_ctrl.size = size<<20;
		pcie_read_ctrl.size = size<<20;
	}

	regvalwt = (pcie_write_ctrl.phyaddr >> 20)
		| (pcie_write_ctrl.phyaddr+ pcie_write_ctrl.size);

	regvalrd = (pcie_read_ctrl.phyaddr>> 20)
		| (pcie_read_ctrl.phyaddr + pcie_read_ctrl.size);

	/* ca: config ddr bank for ep dma before cancel reset */
#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3796MV2X)
	hipcie_config_ddr_bank(regvalwt, regvalrd, hipcie->ca_reg_addr);
#else
	hipcie_config_ddr_bank(regvalwt, regvalrd, hipcie->sys_addr);
#endif
	/*ca: config DDR read and write protected address to bakeup register*/
#ifdef CONFIG_ARCH_HI3796MV2X
	writel(regvalwt, hipcie->ctrl_addr + PCIE_SYS_STATE_SHW7);

	writel(regvalrd, hipcie->ctrl_addr + PCIE_SYS_STATE_SHW8);

	writel(0x11, hipcie->ctrl_addr + PCIE_SYS_STATE_SHW9);

	writel(PCIE_BAK_REG_LOCK_EN, hipcie->ctrl_addr + PCIE_BAK_REG_LOCK);
#endif

	ret = clk_prepare_enable(hipcie->clk);
	if (ret)
		return ret;

	pp->root_bus_nr = -1;
	pp->ops = &hipcie_host_ops;

	ret = dw_pcie_host_init(pp);
	if (ret) {
		dev_err(&pdev->dev, "failed to initialize host\n");
		goto fail_clk;
	}

	platform_set_drvdata(pdev, hipcie);
	return 0;

fail_clk:
	clk_disable_unprepare(hipcie->clk);
	return ret;
}
/******************************************************************************/

static int __exit hipcie_pltm_remove(struct platform_device *pdev)
{
	struct hipcie_host *hipcie = platform_get_drvdata(pdev);

	clk_disable_unprepare(hipcie->clk);

	return 0;
}

/******************************************************************************/

/* host bridge support power switch */
static bool hipci_power_manageable(struct pci_dev *dev)
{
	if ((dev->vendor == 0x19e5) && ((dev->device == 0x5610) || (dev->device == 0x3798))) {
	  	return true;
	} else {
		return false;
	}
}
/******************************************************************************/

static int hipci_set_power_state(struct pci_dev *dev, pci_power_t state)
{
	int ret;
	u32 regvalrd;
	u32 regvalwt;
	struct hipcie_host *hipcie = dev_get_drvdata(dev->bus->bridge->parent);

	clk_disable_unprepare(hipcie->clk);
	
	regvalwt = (pcie_write_ctrl.phyaddr >> 20)
		| (pcie_write_ctrl.phyaddr + pcie_write_ctrl.size);
	
	regvalrd = (pcie_read_ctrl.phyaddr >> 20)
		| (pcie_read_ctrl.phyaddr + pcie_read_ctrl.size);

	/* ca: config ddr bank for ep dma before cancel reset */
#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3796MV2X)
	hipcie_config_ddr_bank(regvalwt, regvalrd, hipcie->ca_reg_addr);
#else
	hipcie_config_ddr_bank(regvalwt, regvalrd, hipcie->sys_addr);
#endif

	ret = clk_prepare_enable(hipcie->clk);

	if (ret)
		ret = -ENOSYS;


	hipcie_establish_link(&hipcie->pp);
	
	dw_pcie_init_outbound_atu(&hipcie->pp);

	return ret;
	
}
/******************************************************************************/

/* for pci_set_platform_pm ok */
static pci_power_t hipci_choose_state(struct pci_dev *pdev)
{
	return PCI_POWER_ERROR;
}
/******************************************************************************/

/* for pci_set_platform_pm ok */
static int hipci_sleep_wake(struct pci_dev *dev, bool enable)
{
	return -ENODEV;
}
/******************************************************************************/

/* for pci_set_platform_pm ok */
static int hipci_run_wake(struct pci_dev *dev, bool enable)
{
	return -ENODEV;
}
/******************************************************************************/

static struct pci_platform_pm_ops hipci_platform_pm = {
	.is_manageable = hipci_power_manageable,
	.set_state = hipci_set_power_state,
	.choose_state = hipci_choose_state,
	.sleep_wake = hipci_sleep_wake,
	.run_wake = hipci_run_wake,
};
/******************************************************************************/

static const struct of_device_id hipcie_of_match[] = {
	{ .compatible = "hisilicon,hisilicon-pcie", },
	{},
};
MODULE_DEVICE_TABLE(of, hipcie_of_match);

static struct platform_driver hipcie_pltm_driver = {
	.remove		= __exit_p(hipcie_pltm_remove),
	.driver = {
		.name	= "hisilicon-pcie",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(hipcie_of_match),
	},
};
/******************************************************************************/

/* Hisilicon PCIe driver does not allow module unload */
static int __init pcie_init(void)
{
	pci_set_platform_pm(&hipci_platform_pm);

	return platform_driver_probe(&hipcie_pltm_driver, hipcie_pltm_probe);
}
subsys_initcall(pcie_init);

MODULE_AUTHOR("Hisilicon");
MODULE_DESCRIPTION("Hisilicon PCIe host controller driver");
MODULE_LICENSE("GPL v2");
