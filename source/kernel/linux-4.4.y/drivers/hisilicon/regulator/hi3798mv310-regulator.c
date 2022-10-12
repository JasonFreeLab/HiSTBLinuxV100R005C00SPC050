
/*
 * devfreq regulator for utgard GPUs
 *
 * Copyright (c) <2011-2015> HiSilicon Technologies Co., Ltd.
 *              http://www.hisilicon.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define DRVNAME "gpu-regulator-driver"
#define REGNAME "Hisilicon GPU Regulator"
#define pr_fmt(fmt) DRVNAME ": " fmt

#include <linux/device.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/of_regulator.h>
#include <asm/delay.h>

#define REGULATOR_ERROR_INFO() \
	printk("error: func = %s, line = %d\n", __FUNCTION__, __LINE__);

#define REGULATOR_DEBUG 0

#define REGULATOR_STEP 5
#define REGULATOR_OFFSET (1<<17)
#define REGULATOR_BASE 0x000100DD
#define REGULATOR_VMIN 700
#define REGULATOR_VMAX 1250
#define REG_SC_GEN6 (0xF8000098)
#define REG_PWM_CORE (0xF8A2301C)

#define REGULATOR_GPU 0
#define REGULATOR_CPU 1

struct hisi_gpu_regulator {
	struct regulator_desc desc;
	struct regulator_dev *regdev;
	void __iomem *base;
	int min_uV;
	int max_uV;
};

static unsigned int core_hpm = 0;
static unsigned int core_volt = 0;
static unsigned int cpu_volt = 0;
static unsigned int gpu_volt = 0;

static void __iomem *virtbase_sc = NULL;
static void __iomem *virtbase_pwm = NULL;
static DEFINE_MUTEX(regulator_mutex);

/* To get the core hpm and core voltage */
static void hisi_regulator_core_init(void)
{
	unsigned int value;

	virtbase_sc = (void __iomem *)IO_ADDRESS(REG_SC_GEN6);
	virtbase_pwm = (void __iomem *)IO_ADDRESS(REG_PWM_CORE);

	value = readl(virtbase_sc);
	core_hpm = (value & 0x3ff);

	value = readl(virtbase_pwm);
	core_volt = REGULATOR_VMAX - (value - REGULATOR_BASE) * REGULATOR_STEP / REGULATOR_OFFSET;

	cpu_volt = core_volt;
	gpu_volt = core_volt;

	return;
}
/* GPU/CPU/Core had a common power domain, should give consideration to each other */
int hisi_regulator_set_voltage(int type, int volt)
{
    unsigned int value, real_volt;

	mutex_lock(&regulator_mutex);

	switch (type) {
		case REGULATOR_CPU:
			cpu_volt = volt;
			break;

		case REGULATOR_GPU:
			gpu_volt = volt;
			break;

		default:
			REGULATOR_ERROR_INFO();
			mutex_unlock(&regulator_mutex);
			return -EINVAL;
	}

	real_volt = (cpu_volt > gpu_volt) ? cpu_volt : gpu_volt;

	real_volt = (real_volt > REGULATOR_VMAX) ? REGULATOR_VMAX : real_volt;

	value = REGULATOR_BASE + ((REGULATOR_VMAX - real_volt) / REGULATOR_STEP) * REGULATOR_OFFSET;
	writel(value, virtbase_pwm);

	mutex_unlock(&regulator_mutex);

	return real_volt;
}
EXPORT_SYMBOL(hisi_regulator_set_voltage);
static int hisi_gpu_regulator_get_voltage(struct regulator_dev *regdev)
{
	struct hisi_gpu_regulator *regulator = rdev_get_drvdata(regdev);

	unsigned int vmax = REGULATOR_VMAX;
	unsigned int vmin = REGULATOR_VMIN;
	unsigned int step = REGULATOR_STEP;
	unsigned int base = REGULATOR_BASE;
	unsigned int offset = REGULATOR_OFFSET;
	unsigned int volt, value;

	value = readl(regulator->base);

	volt = vmax - (value - base)*step/offset;

	if ((volt < vmin) || (volt > vmax)) {
		REGULATOR_ERROR_INFO();
		return -EINVAL;
	}

	if (REGULATOR_DEBUG)
		printk("hisi_gpu_regulator_get_voltage@ Volt = %d\n", volt);

	return volt*1000;
}

static int hisi_gpu_regulator_set_voltage(struct regulator_dev *regdev, int min_uV, int max_uV, unsigned *selector)
{
#define R1 1875
#define O1 1462
#define R2 1667
#define O2 1447

#define BOUNDARY 540000
#define MAX_VOLT 1000

	unsigned int freq = min_uV;
	unsigned int volt;

	/* compute the gpu voltage, based on gpu frequency */
	if (freq <= BOUNDARY) {
		volt = O1 - (R1 * core_hpm) / 1000;
		volt = (volt > MAX_VOLT) ? MAX_VOLT : volt;
	} else {
		volt = O2 - (R2 * core_hpm) / 1000;
		volt = (volt > MAX_VOLT) ? MAX_VOLT : volt;
	}

	if (volt >= REGULATOR_VMIN && volt <= REGULATOR_VMAX) {
		volt = hisi_regulator_set_voltage(REGULATOR_GPU, volt);
	} else {
		REGULATOR_ERROR_INFO();
		return -EINVAL;
	}

	udelay(1000);

	if (REGULATOR_DEBUG)
		printk("hisi_gpu_regulator_set_voltage@ Volt = %d\n", volt);

	return 0;
}

static struct regulator_ops hisi_gpu_regulator_ops = {
	.get_voltage = hisi_gpu_regulator_get_voltage,
	.set_voltage = hisi_gpu_regulator_set_voltage,
};

static int hisi_regulator_probe(struct platform_device *pdev)
{
	struct hisi_gpu_regulator *regulator;
	struct regulator_init_data *init_data;
	struct regulator_config config = {0};
	struct resource *res;
	char *pname;

	regulator = devm_kzalloc(&pdev->dev, sizeof(*regulator), GFP_KERNEL);

	if (!regulator) {
		REGULATOR_ERROR_INFO();
		return -ENOMEM;
	}

	pname = REGNAME;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, pname);
	if (!res) {
		REGULATOR_ERROR_INFO();
		return -ENODEV;
	}

	regulator->base = devm_ioremap_nocache(&pdev->dev, res->start, resource_size(res));
	if (!regulator->base) {
		devm_kfree(&pdev->dev, regulator);
		REGULATOR_ERROR_INFO();
		return -ENOMEM;
	}

	regulator->desc.name = dev_name(&pdev->dev);
	regulator->desc.type = REGULATOR_VOLTAGE;
	regulator->desc.owner = THIS_MODULE;
	regulator->desc.continuous_voltage_range = true;

	init_data = of_get_regulator_init_data(&pdev->dev, pdev->dev.of_node, &regulator->desc);
	if (!init_data) {
		devm_iounmap(&pdev->dev, regulator->base);
		devm_kfree(&pdev->dev, regulator);
		REGULATOR_ERROR_INFO();
		return -EINVAL;
	}

	init_data->constraints.apply_uV = 0;
	regulator->min_uV = init_data->constraints.min_uV;
	regulator->max_uV = init_data->constraints.max_uV;

	if (regulator->min_uV >= regulator->max_uV) {
		devm_iounmap(&pdev->dev, regulator->base);
		devm_kfree(&pdev->dev, regulator);
		REGULATOR_ERROR_INFO();
		return -EINVAL;
	}

	regulator->desc.ops = &hisi_gpu_regulator_ops;

	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.driver_data = regulator;
	config.of_node = pdev->dev.of_node;

	regulator->regdev = devm_regulator_register(&pdev->dev, &regulator->desc, &config);
	if (IS_ERR(regulator->regdev)) {
		devm_iounmap(&pdev->dev, regulator->base);
		devm_kfree(&pdev->dev, regulator);
		REGULATOR_ERROR_INFO();
		return PTR_ERR(regulator->regdev);
	}

	platform_set_drvdata(pdev, regulator);

	hisi_regulator_core_init();
	if (REGULATOR_DEBUG)
		printk("hisi_regulator_probe@\n");

	return 0;
}

static const struct of_device_id hisi_regulator_of_match[] = {
	{ .compatible = "hisilicon,hi3798mv310-volt", },
	{ }
};

static struct platform_driver hisi_regulator_driver = {
	.probe = hisi_regulator_probe,
	.driver = {
		.name = DRVNAME,
		.owner = THIS_MODULE,
		.of_match_table = hisi_regulator_of_match,
	},
};

module_platform_driver(hisi_regulator_driver);

MODULE_AUTHOR("Hisilicon GPU Team");
MODULE_DESCRIPTION("Hisilicon GPU Regulator");
MODULE_LICENSE("GPLv2");
MODULE_ALIAS("Hisilicon GPU Regulator");
