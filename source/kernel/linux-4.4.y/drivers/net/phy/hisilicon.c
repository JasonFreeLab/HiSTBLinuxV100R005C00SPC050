/*
 * drivers/net/phy/hisilicon.c
 *
 * Driver for HiSilicon PHYs
 *
 * Author: Dongpo Li <lidongpo@hisilicon.com>
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/of_irq.h>
#include <linux/etherdevice.h>
#include <linux/ethtool.h>
#include <linux/phy.h>
#include <linux/hisilicon_phy.h>

/* PHY registers */
#define MII_INT_SR		0x14
#define MII_INT_CLR		0x15
#define BIT_SPEED_CHG_INT	BIT(15)
#define BIT_LINK_CHG_INT	BIT(14)
#define BIT_DUPLEX_CHG_INT	BIT(13)
#define BIT_PHY_STATE_CHG_INT	(BIT_SPEED_CHG_INT | BIT_LINK_CHG_INT | \
				BIT_DUPLEX_CHG_INT)
#define MII_EXPMD		0x1d
#define MII_EXPMA		0x1e

#define INT_MASK_H		0x0157
#define BIT_SPEED_INT_EN	BIT(7)
#define BIT_LINK_INT_EN		BIT(6)
#define BIT_DUPLEX_INT_EN	BIT(5)
#define BIT_PHY_STATE_INT_EN	(BIT_SPEED_INT_EN | BIT_LINK_INT_EN | \
				BIT_DUPLEX_INT_EN)
#define WOL_CTRL_STATUS		0x1f00
#define WOL_MAGIC_PKT_ENABLE	BIT(1)
#define WOL_WAKE_PKT_ENABLE	BIT(2)
#define WOL_INTR_ENABLE		BIT(3)
#define WOL_MAGIC_PKT_INTR_RAW	BIT(4)
#define WOL_WAKE_PKT_INTR_RAW	BIT(6)

#define WOL_UNICAST_CTRL	0x1f01
#define WOL_UNICAST_ENABLE	BIT(1)
#define WOL_FILTER0_MASK0	0x1f04
#define WOL_FILTER0_MASK1	0x1f05
#define WOL_FILTER0_MASK2	0x1f06
#define WOL_FILTER0_MASK3	0x1f07
#define WOL_FILTER0_CTRL	0x1f14
#define WOL_FILTER_ENABLE	BIT(0)
#define WOL_FILTER_TYPE		BIT(4)
#define WOL_FILTER_TYPE_OFFSET	4
#define WOL_FILTER0_OFFSET	0x1f18
#define WOL_FILTER0_CRC0	0x1f1c
#define WOL_FILTER0_CRC1	0x1f1d
#define LOCAL_MACADDR_MSB	0x1f29

enum filter_type {
	MATCH_UCAST_BCAST = 0,
	MATCH_MCAST_BCAST,
};

struct festa_filter {
	enum filter_type type;
	u8 offset;
	u32 bytemask;
	u16 crc;
};

static struct festa_filter broadcast_template = {
	.type = MATCH_UCAST_BCAST,
	.offset = 0,
	.bytemask = 0x3f,
	.crc = 0x8029,
};

static struct festa_filter arp_template = {
	.type = MATCH_UCAST_BCAST,
	.offset = 12,
	.bytemask = 0x3,
	.crc = 0x614e,
};

static int phy_expanded_read_atomic(struct phy_device *phydev, u32 reg_addr)
{
	struct mii_bus *bus = phydev->bus;
	int ret;

	bus->write(bus, phydev->addr, MII_EXPMA, reg_addr);
	ret = bus->read(bus, phydev->addr, MII_EXPMD);

	return ret;
}

static int phy_expanded_read(struct phy_device *phydev, u32 reg_addr)
{
	struct mii_bus *bus = phydev->bus;
	int ret;

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, phydev->addr, MII_EXPMA, reg_addr);
	ret = bus->read(bus, phydev->addr, MII_EXPMD);

	mutex_unlock(&bus->mdio_lock);

	return ret;
}

static int phy_expanded_write_atomic(struct phy_device *phydev,
				     u32 reg_addr, u16 val)
{
	struct mii_bus *bus = phydev->bus;
	int ret;

	bus->write(bus, phydev->addr, MII_EXPMA, reg_addr);
	ret = bus->write(bus, phydev->addr, MII_EXPMD, val);

	return ret;
}

static int phy_expanded_write(struct phy_device *phydev, u32 reg_addr, u16 val)
{
	struct mii_bus *bus = phydev->bus;
	int ret;

	mutex_lock(&bus->mdio_lock);

	bus->write(bus, phydev->addr, MII_EXPMA, reg_addr);
	ret = bus->write(bus, phydev->addr, MII_EXPMD, val);

	mutex_unlock(&bus->mdio_lock);

	return ret;
}

static int festa_ack_interrupt(struct phy_device *phydev)
{
	return phy_write(phydev, MII_INT_CLR, BIT_PHY_STATE_CHG_INT);
}

static int festa_config_intr(struct phy_device *phydev)
{
	int err;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		err = phy_expanded_write(phydev, INT_MASK_H, BIT_PHY_STATE_INT_EN);
	else
		err = phy_expanded_write(phydev, INT_MASK_H, 0);

	return err;
}

static int festa_did_interrupt(struct phy_device *phydev)
{
	int ret;

	ret = phy_read(phydev, MII_INT_SR);
	if (ret < 0)
		return 0;

	return (ret & BIT_PHY_STATE_CHG_INT) != 0;
}

static void festa_set_mac_address(struct phy_device *phydev, const u8 *mac)
{
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		phy_expanded_write(phydev, LOCAL_MACADDR_MSB - i, mac[i]);
}

static void festa_set_filter(struct phy_device *phydev, int index,
			     struct festa_filter *filter)
{
	u32 val;

	phy_expanded_write(phydev, WOL_FILTER0_OFFSET + index, filter->offset);
	phy_expanded_write(phydev, WOL_FILTER0_MASK0 + index * 0x4,
			   filter->bytemask & 0xff);
	phy_expanded_write(phydev, WOL_FILTER0_MASK1 + index * 0x4,
			   (filter->bytemask >> 8) & 0xff);
	phy_expanded_write(phydev, WOL_FILTER0_MASK2 + index * 0x4,
			   (filter->bytemask >> 16) & 0xff);
	phy_expanded_write(phydev, WOL_FILTER0_MASK3 + index * 0x4,
			   (filter->bytemask >> 24) & 0xff);
	phy_expanded_write(phydev, WOL_FILTER0_CRC0 + index * 0x2,
			   filter->crc & 0xff);
	phy_expanded_write(phydev, WOL_FILTER0_CRC1 + index * 0x2,
			   (filter->crc >> 8) & 0xff);

	val = phy_expanded_read(phydev, WOL_FILTER0_CTRL + index);
	val &= ~WOL_FILTER_TYPE;
	val |= (filter->type << WOL_FILTER_TYPE_OFFSET);
	val |= WOL_FILTER_ENABLE;
	phy_expanded_write(phydev, WOL_FILTER0_CTRL + index, val);
}

static void festa_clear_filter(struct phy_device *phydev, int index)
{
	u32 val;

	val = phy_expanded_read(phydev, WOL_FILTER0_CTRL + index);
	val &= ~WOL_FILTER_ENABLE;
	phy_expanded_write(phydev, WOL_FILTER0_CTRL + index, val);
}

static bool festa_filter_enabled(struct phy_device *phydev, int index)
{
	u32 val;

	val = phy_expanded_read(phydev, WOL_FILTER0_CTRL + index);

	return val & WOL_FILTER_ENABLE;
}

static void festa_get_wol(struct phy_device *phydev,
			  struct ethtool_wolinfo *wol)
{
	u32 val;

	wol->supported = WAKE_UCAST | WAKE_BCAST | WAKE_ARP | WAKE_MAGIC;
	wol->wolopts = 0;

	val = phy_expanded_read(phydev, WOL_UNICAST_CTRL);
	if (val & WOL_UNICAST_ENABLE)
		wol->wolopts |= WAKE_UCAST;

	val = phy_expanded_read(phydev, WOL_CTRL_STATUS);
	if (val & WOL_MAGIC_PKT_ENABLE)
		wol->wolopts |= WAKE_MAGIC;

	if (festa_filter_enabled(phydev, 0))
		wol->wolopts |= WAKE_BCAST;

	if (festa_filter_enabled(phydev, 1))
		wol->wolopts |= WAKE_ARP;
}

static int festa_set_wol(struct phy_device *phydev, struct ethtool_wolinfo *wol)
{
	struct net_device *ndev = phydev->attached_dev;
	u32 val, wol_ctrl;

	if (!ndev)
		return -ENODEV;

	if (wol->wolopts & (WAKE_PHY | WAKE_MCAST | WAKE_MAGICSECURE))
		return -EOPNOTSUPP;

	wol_ctrl = phy_expanded_read(phydev, WOL_CTRL_STATUS);

	if (wol->wolopts & WAKE_MAGIC) {
		festa_set_mac_address(phydev, (const u8 *)ndev->dev_addr);

		/* write 1 to clear raw interrupt */
		wol_ctrl |= WOL_MAGIC_PKT_INTR_RAW;
		/* enable magic packet recv and interrupt */
		wol_ctrl |= WOL_MAGIC_PKT_ENABLE | WOL_INTR_ENABLE;
	} else {
		wol_ctrl &= ~WOL_MAGIC_PKT_ENABLE;
	}

	if (wol->wolopts & WAKE_UCAST) {
		festa_set_mac_address(phydev, (const u8 *)ndev->dev_addr);

		val = phy_expanded_read(phydev, WOL_UNICAST_CTRL);
		val |= WOL_UNICAST_ENABLE;
		phy_expanded_write(phydev, WOL_UNICAST_CTRL, val);

		/* write 1 to clear raw interrupt */
		wol_ctrl |= WOL_WAKE_PKT_INTR_RAW;
		wol_ctrl |= WOL_WAKE_PKT_ENABLE | WOL_INTR_ENABLE;
	} else {
		val = phy_expanded_read(phydev, WOL_UNICAST_CTRL);
		val &= ~WOL_UNICAST_ENABLE;
		phy_expanded_write(phydev, WOL_UNICAST_CTRL, val);
	}

	if (wol->wolopts & WAKE_BCAST) {
		festa_set_filter(phydev, 0, &broadcast_template);
		/* write 1 to clear raw interrupt */
		wol_ctrl |= WOL_WAKE_PKT_INTR_RAW;
		wol_ctrl |= WOL_WAKE_PKT_ENABLE | WOL_INTR_ENABLE;
	} else {
		festa_clear_filter(phydev, 0);
	}

	if (wol->wolopts & WAKE_ARP) {
		festa_set_filter(phydev, 1, &arp_template);
		/* write 1 to clear raw interrupt */
		wol_ctrl |= WOL_WAKE_PKT_INTR_RAW;
		wol_ctrl |= WOL_WAKE_PKT_ENABLE | WOL_INTR_ENABLE;
	} else {
		festa_clear_filter(phydev, 1);
	}

	if (!(wol->wolopts & (WAKE_UCAST | WAKE_BCAST | WAKE_ARP)))
		wol_ctrl &= ~WOL_WAKE_PKT_ENABLE;

	if (!wol->wolopts)
		wol_ctrl &= ~WOL_INTR_ENABLE;

	phy_expanded_write(phydev, WOL_CTRL_STATUS, wol_ctrl);

	return 0;
}

static int festa_suspend(struct phy_device *phydev)
{
	int value;
	int wol_enabled;

	mutex_lock(&phydev->lock);

	value = phy_expanded_read(phydev, WOL_CTRL_STATUS);
	wol_enabled = value & WOL_INTR_ENABLE;

	value = phy_read(phydev, MII_BMCR);

	if (!wol_enabled)
		value |= BMCR_PDOWN;

	phy_write(phydev, MII_BMCR, value);

	mutex_unlock(&phydev->lock);

	return 0;
}

static int festa_resume(struct phy_device *phydev)
{
	int value;

	mutex_lock(&phydev->lock);

	value = phy_read(phydev, MII_BMCR);
	value &= ~(BMCR_PDOWN | BMCR_ISOLATE);
	phy_write(phydev, MII_BMCR, value);

	mutex_unlock(&phydev->lock);

	return 0;
}

struct festa_phy_priv {
	const struct festa_driver_data *type;
	int wol_irq;
};

struct festa_driver_data {
	bool wol_enable;
};

static const struct festa_driver_data festa_v330_data = {
	.wol_enable = true,
};

static const struct festa_driver_data festa_v331_data = {
	.wol_enable = true,
};

static irqreturn_t festa_wol_irq_handler(int irq, void *phy_dat)
{
	struct phy_device *phydev = phy_dat;
	u32 wol_ctrl;

	if (phydev->state == PHY_HALTED)
		return IRQ_NONE;

	wol_ctrl = phy_expanded_read_atomic(phydev, WOL_CTRL_STATUS);
	wol_ctrl |= WOL_MAGIC_PKT_INTR_RAW;
	wol_ctrl |= WOL_WAKE_PKT_INTR_RAW;
	wol_ctrl &= ~WOL_WAKE_PKT_ENABLE;
	wol_ctrl &= ~WOL_INTR_ENABLE;
	phy_expanded_write_atomic(phydev, WOL_CTRL_STATUS, wol_ctrl);

	return IRQ_HANDLED;
}

static int festa_phy_probe(struct phy_device *phydev)
{
	const struct festa_driver_data *type = phydev->drv->driver_data;
	struct device_node *np = phydev->dev.of_node;
	struct festa_phy_priv *priv;
	int ret;

	priv = devm_kzalloc(&phydev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	phydev->priv = priv;

	priv->type = type;

	if (type && type->wol_enable) {
		ret = irq_of_parse_and_map(np, 1);
		priv->wol_irq = ret;
	}

	if (priv->wol_irq > 0) {
		ret = devm_request_irq(&phydev->dev, priv->wol_irq,
				       festa_wol_irq_handler, 0,
				       "festa_phy_wol", phydev);
		if (ret)
			return ret;
	}

	return 0;
}

static struct phy_driver hisilicon_drivers[] = {
	{
		.phy_id = HISILICON_PHY_ID_FESTAV200,
		.phy_id_mask = HISILICON_PHY_ID_MASK,
		.name = "HiSilicon Festa v200/v210",
		.features = PHY_BASIC_FEATURES,
		.flags = PHY_IS_INTERNAL,
		.config_init = genphy_config_init,
		.config_aneg = genphy_config_aneg,
		.read_status = genphy_read_status,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.driver = { .owner = THIS_MODULE },
	},
	{
		.phy_id = HISILICON_PHY_ID_FESTAV220,
		.phy_id_mask = HISILICON_PHY_ID_MASK,
		.name = "HiSilicon Festa v220",
		.features = PHY_BASIC_FEATURES,
		.flags = PHY_IS_INTERNAL,
		.config_init = genphy_config_init,
		.config_aneg = genphy_config_aneg,
		.read_status = genphy_read_status,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.driver = {.owner = THIS_MODULE,},
	},
	{
		.phy_id = HISILICON_PHY_ID_FESTAV330,
		.phy_id_mask = HISILICON_PHY_ID_MASK,
		.name = "HiSilicon Festa v330",
		.features = PHY_BASIC_FEATURES,
		.flags = PHY_IS_INTERNAL | PHY_HAS_INTERRUPT,
		.driver_data = &festa_v330_data,
		.probe = festa_phy_probe,
		.config_init = genphy_config_init,
		.config_aneg = genphy_config_aneg,
		.read_status = genphy_read_status,
		.ack_interrupt = festa_ack_interrupt,
		.config_intr = festa_config_intr,
		.did_interrupt = festa_did_interrupt,
		.get_wol = festa_get_wol,
		.set_wol = festa_set_wol,
		.resume = festa_resume,
		.suspend = festa_suspend,
		.driver = { .owner = THIS_MODULE },
	},

	{
		.phy_id = HISILICON_PHY_ID_FESTAV331,
		.phy_id_mask = HISILICON_PHY_ID_MASK,
		.name = "HiSilicon Festa v331",
		.features = PHY_BASIC_FEATURES,
		.flags = PHY_IS_INTERNAL,
		.driver_data = &festa_v331_data,
		.probe = festa_phy_probe,
		.config_init = genphy_config_init,
		.config_aneg = genphy_config_aneg,
		.read_status = genphy_read_status,
		.get_wol = festa_get_wol,
		.set_wol = festa_set_wol,
		.resume = festa_resume,
		.suspend = festa_suspend,
		.driver = { .owner = THIS_MODULE },
	},
	{
		.phy_id = HISILICON_PHY_ID_FESTA_S28V112,
		.phy_id_mask = HISILICON_PHY_ID_MASK,
		.name = "HiSilicon Festa s28v112",
		.features = PHY_BASIC_FEATURES,
		.flags = PHY_IS_INTERNAL | PHY_HAS_INTERRUPT,
		.driver_data = &festa_v330_data,
		.probe = festa_phy_probe,
		.config_init = genphy_config_init,
		.config_aneg = genphy_config_aneg,
		.read_status = genphy_read_status,
		.ack_interrupt = festa_ack_interrupt,
		.config_intr = festa_config_intr,
		.did_interrupt = festa_did_interrupt,
		.get_wol = festa_get_wol,
		.set_wol = festa_set_wol,
		.resume = festa_resume,
		.suspend = festa_suspend,
		.driver = { .owner = THIS_MODULE },
	},
};

module_phy_driver(hisilicon_drivers);

static struct mdio_device_id __maybe_unused hisilicon_tbl[] = {
	{ HISILICON_PHY_ID_FESTAV200, HISILICON_PHY_ID_MASK },
	{ HISILICON_PHY_ID_FESTAV220, HISILICON_PHY_ID_MASK },
	{ HISILICON_PHY_ID_FESTAV330, HISILICON_PHY_ID_MASK },
	{ HISILICON_PHY_ID_FESTAV331, HISILICON_PHY_ID_MASK },
	{ HISILICON_PHY_ID_FESTA_S28V112, HISILICON_PHY_ID_MASK },
	{ }
};

MODULE_DEVICE_TABLE(mdio, hisilicon_tbl);

MODULE_DESCRIPTION("HiSilicon PHY driver");
MODULE_AUTHOR("Dongpo Li <lidongpo@hisilicon.com>");
MODULE_LICENSE("GPL v2");
