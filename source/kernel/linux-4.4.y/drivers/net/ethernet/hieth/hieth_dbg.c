/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by ZhangYixing
 *
******************************************************************************/
#define pr_fmt(fmt) "mmcdbg: " fmt

#include <linux/platform_device.h>
#include <linux/kobject.h>
#include <linux/slab.h>
#include <linux/kmod.h>
#include <linux/vmalloc.h>
#include <linux/debugfs.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <uapi/linux/if_ether.h>
#include <linux/if_ether.h>
#include <uapi/linux/if.h>

#ifndef CONFIG_ARM64
#include <mach/hardware.h>
#endif

#include "hieth.h"

#define MAC_FMT "	MAC%d: %02x:%02x:%02x:%02x:%02x:%02x\n"

struct cmd_val_t {
	const char *key;
	int sz_key;
	char *buf;
	int sz_buf;
};

/******************************************************************************/
static int dump_eth_stats(int index, void __iomem *macbase, char *buf, int sz_buf)
{
	int ix;
	int count;
	char *ptr = buf;

	struct regdef {
		char *fmt;
		u32 offset;
	} regdef[] = {
		{"  Rx:%u Bytes\n", 0x608},
		{"    total packets:%u ", 0x610},
		{"broadcast:%u ", 0x614},
		{"multicast:%u ", 0x618},
		{"unicast:%u ", 0x61C},
		{"to me:%u\n", 0x60C},
		{"    error packets:%u ", 0x620},
		{"crc/alignment:%u ", 0x624},
		{"invalid size:%u ", 0x628},
		{"nibble error:%u\n", 0x62C},
		{"    pause frame:%u, ", 0x630},
		{"overflow: %u ", 0x634},
		{"mac filterd: %u\n", 0x64c},
		{"  Tx:%u Bytes\n", 0x790},
		{"    total packets:%u ", 0x780},
		{"broadcast:%u ", 0x784},
		{"multicast:%u ", 0x788},
		{"unicast:%u\n", 0x78C},
	};

	count = snprintf(ptr, sz_buf, "eth%d:\n", index);
	sz_buf -= count;
	ptr += count;

	for (ix = 0; ix < ARRAY_SIZE(regdef); ix++) {
		count = snprintf(ptr, sz_buf, regdef[ix].fmt, readl(macbase + regdef[ix].offset));
		sz_buf -= count;
		ptr += count;
	}

	return ptr - buf;
}

#ifdef HIETH_SKB_MEMORY_STATS
static int dump_eth_mem_stats(struct hieth_platdrv_data *pdata, char *buf, int sz_buf)
{
	int ix;
	int count;
	char *ptr = buf;
	struct net_device *ndev;
	struct hieth_netdev_priv *priv;


	for (ix = 0; ix < pdata->hieth_real_port_cnt; ix++) {
		ndev = pdata->hieth_devs_save[ix];
		priv = netdev_priv(ndev);

		count = snprintf(ptr, sz_buf, "%s:\n", ndev->name);
		sz_buf -= count;
		ptr += count;

		count = snprintf(ptr, sz_buf, "tx skb occupied: %d\n",
				atomic_read(&priv->tx_skb_occupied));
		sz_buf -= count;
		ptr += count;

		count = snprintf(ptr, sz_buf, "tx skb memory occupied: %d Bytes\n",
				atomic_read(&priv->tx_skb_mem_occupied));
		sz_buf -= count;
		ptr += count;

		count = snprintf(ptr, sz_buf, "rx skb occupied: %d\n",
				atomic_read(&priv->rx_skb_occupied));
		sz_buf -= count;
		ptr += count;

		count = snprintf(ptr, sz_buf, "rx skb memory occupied: %d Bytes\n",
				atomic_read(&priv->rx_skb_mem_occupied));
		sz_buf -= count;
		ptr += count;
	}

	return ptr - buf;
}
#endif

/******************************************************************************/

static ssize_t fo_dump_ethstats_read(struct file *filp, char __user *ubuf,
			size_t sz_ubuf, loff_t *ppos)
{
	struct ethstats *stats = filp->private_data;

	return simple_read_from_buffer(ubuf, sz_ubuf, ppos, stats->prbuf,
		stats->sz_prbuf);
}

/******************************************************************************/

static int fo_dump_ethstats_open(struct inode *inode, struct file *file)
{
	struct ethstats *data;
	int count = 0, sz_buf;
	char *ptr;
	struct hieth_platdrv_data *pdata = inode->i_private;

	data = &pdata->ethstats;

	file->private_data = (void *)data;

	ptr = data->prbuf;
	sz_buf = sizeof(data->prbuf);

	count = dump_eth_stats(0, data->macbase[0], ptr, sz_buf);

	data->sz_prbuf = count;

	return nonseekable_open(inode, file);
}
/******************************************************************************/

#ifdef HIETH_SKB_MEMORY_STATS
static ssize_t fo_dump_eth_mem_stats_read(struct file *filp, char __user *ubuf,
			size_t sz_ubuf, loff_t *ppos)
{
	struct eth_mem_stats *mem_stats = filp->private_data;

	return simple_read_from_buffer(ubuf, sz_ubuf, ppos, mem_stats->prbuf,
		mem_stats->sz_prbuf);
}

static int fo_dump_eth_mem_stats_open(struct inode *inode, struct file *file)
{
	struct eth_mem_stats *data;
	int count = 0, sz_buf;
	char *ptr;
	struct hieth_platdrv_data *pdata = inode->i_private;

	data = &pdata->eth_mem_stats;

	file->private_data = (void *)data;

	ptr = data->prbuf;
	sz_buf = sizeof(data->prbuf);

	count = dump_eth_mem_stats(pdata, ptr, sz_buf);

	data->sz_prbuf = count;

	return nonseekable_open(inode, file);
}
#endif

int multicast_dump_netdev_flags(u32 flags, struct hieth_platdrv_data *pdata)
{
	u32 old = pdata->mcdump.net_flags;
	spin_lock(&pdata->mcdump.lock);
	pdata->mcdump.net_flags = flags;
	spin_unlock(&pdata->mcdump.lock);
	return old;
}
/******************************************************************************/

void multicast_dump_macaddr(u32 nr, char *macaddr, struct hieth_platdrv_data *pdata)
{
	char *ptr;
	if (nr > MAX_MULTICAST_FILTER)
		return;

	ptr = pdata->mcdump.mac + nr*ETH_ALEN;
	spin_lock(&pdata->mcdump.lock);
	memcpy(ptr, macaddr, ETH_ALEN);
	pdata->mcdump.mac_nr = nr+1;
	spin_unlock(&pdata->mcdump.lock);
}

/******************************************************************************/

static int dump_mc_drop(int index, struct mcdump *dump, char *buf, int sz_buf)
{
	int ix;
	int count;
	char *ptr = buf;
	char *pmac;

	struct regdef {
		char *fmt;
		u32 offset;
	} regdef[] = {
		{"	Rx packets:%u ", 0x618},
		{"dropped:%u\n", 0x64C},
	};

	count = snprintf(ptr, sz_buf, "eth%d multicast:\n", index);
	sz_buf -= count;
	ptr += count;

	for (ix = 0; ix < ARRAY_SIZE(regdef); ix++) {
		count = snprintf(ptr, sz_buf, regdef[ix].fmt, readl(dump->base + regdef[ix].offset));
		sz_buf -= count;
		ptr += count;
	}

	count = snprintf(ptr, sz_buf, "%s", "	state:");
	sz_buf -= count;
	ptr += count;

	if (dump->net_flags & IFF_MULTICAST) {
		count = snprintf(ptr, sz_buf, "%s", "MULTICAST ");
		sz_buf -= count;
		ptr += count;
	}

	if (dump->net_flags & IFF_PROMISC) {
		count = snprintf(ptr, sz_buf, "%s", "PROMISC ");
		sz_buf -= count;
		ptr += count;
	}

	if (dump->net_flags & IFF_ALLMULTI) {
		count = snprintf(ptr, sz_buf, "%s", "ALLMULTI ");
		sz_buf -= count;
		ptr += count;
	}

	count = snprintf(ptr, sz_buf, "\n	mac filters:%d \n", dump->mac_nr);
	sz_buf -= count;
	ptr += count;

	for (ix = 0; ix < dump->mac_nr; ix++) {
		pmac = dump->mac + ix*ETH_ALEN;
		count = snprintf(ptr, sz_buf, MAC_FMT, ix,
					pmac[0], pmac[1], pmac[2],
					pmac[3], pmac[4], pmac[5]);
		sz_buf -= count;
		ptr += count;
	}


	return ptr - buf;
}
/******************************************************************************/

static int fo_dump_ethmc_open(struct inode *inode, struct file *file)
{
	struct mcdump *data;
	int count = 0, sz_buf;
	char *ptr;
	struct hieth_platdrv_data *pdata = inode->i_private;

	data = &pdata->mcdump;

	file->private_data = (void *)data;

	ptr = data->prbuf;
	sz_buf = sizeof(data->prbuf);

	count = dump_mc_drop(0, data, ptr, sz_buf);

	data->sz_prbuf = count;

	return nonseekable_open(inode, file);
	//return 0;
}

/******************************************************************************/

static ssize_t fo_dump_ethmc_read(struct file *filp, char __user *ubuf,
				 size_t sz_ubuf, loff_t *ppos)
{
	struct mcdump *dump = (struct mcdump *)filp->private_data;

	return simple_read_from_buffer(ubuf, sz_ubuf, ppos, dump->prbuf,
		dump->sz_prbuf);
}

static ssize_t fo_fephy_ed_time_read(struct file *filp, char __user *ubuf,
				 size_t sz_ubuf, loff_t *ppos)
{
#define BUF_LEN	8
	char prbuf[BUF_LEN];
	int len;
	unsigned int fephy_ed_time = fephy_get_ed_time();

	len = snprintf(prbuf, BUF_LEN, "%u\n", fephy_ed_time);
	if (len <= 0)
		return -EINVAL;

	return simple_read_from_buffer(ubuf, sz_ubuf, ppos, prbuf, len);
}

static ssize_t fo_fephy_ed_time_write(struct file *filp,
				      const char __user *ubuf,
				      size_t sz_ubuf, loff_t *ppos)
{
	struct hieth_platdrv_data *pdata = filp->private_data;
	u16 ed_time;
	ssize_t ret;

	ret = kstrtou16_from_user(ubuf, sz_ubuf, 0, &ed_time);
	if (ret)
		return ret;

	ret = hieth_set_fephy_ed_time(ed_time, pdata);
	if (ret)
		return ret;

	return sz_ubuf;
}

/******************************************************************************/

static const struct file_operations ethmc_fops = {
	.owner = THIS_MODULE,
	.open = fo_dump_ethmc_open,
	.read  = fo_dump_ethmc_read,
	.llseek = no_llseek,
};

static const struct file_operations ethstats_fops = {
	.owner = THIS_MODULE,
	.open = fo_dump_ethstats_open,
	.read  = fo_dump_ethstats_read,
	.llseek = no_llseek,
};

#ifdef HIETH_SKB_MEMORY_STATS
static const struct file_operations eth_mem_stats_fops = {
	.owner = THIS_MODULE,
	.open = fo_dump_eth_mem_stats_open,
	.read  = fo_dump_eth_mem_stats_read,
	.llseek = no_llseek,
};
#endif

static const struct file_operations eth_fephy_ed_time_fops = {
	.owner = THIS_MODULE,
	.open = simple_open,
	.read  = fo_fephy_ed_time_read,
	.write = fo_fephy_ed_time_write,
	.llseek = no_llseek,
};

/******************************************************************************/

int hieth_dbg_init(void __iomem *base, struct platform_device *pdev)
{
	char buf[30];
	unsigned int mode = S_IFREG | S_IRUSR | S_IWUSR;
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);

	snprintf(buf, sizeof(buf), "%s", pdev->name);
	pdata->root = debugfs_create_dir(buf, NULL);
	if (!pdata->root) {
		pr_err("Can't create '%s' dir.\n", buf);
		return -ENOENT;
	}

	pdata->mcdump.base = base;
	pdata->mcdump.dentry = debugfs_create_file("multicast", mode, pdata->root,
					    pdata, &ethmc_fops);
	if (!pdata->mcdump.dentry) {
		pr_err("Can't create 'read' file.\n");
		goto fail;
	}
	spin_lock_init(&pdata->mcdump.lock);

	pdata->ethstats.base = base;
	pdata->ethstats.macbase[0] = base;
	pdata->ethstats.macbase[1] = base + 0x2000;
	pdata->ethstats.dentry = debugfs_create_file("stats", mode, pdata->root,
					      pdata, &ethstats_fops);
	if (!pdata->ethstats.dentry) {
		pr_err("Can't create 'write' file.\n");
		goto fail;
	}

#ifdef HIETH_SKB_MEMORY_STATS
	pdata->eth_mem_stats.dentry = debugfs_create_file("mem_stats", mode,
						pdata->root, pdata,
						&eth_mem_stats_fops);
	if (!pdata->eth_mem_stats.dentry) {
		pr_err("Can't create 'write' file.\n");
		goto fail;
	}
#endif

	if (!debugfs_create_file("fephy_ed_time", mode, pdata->root,
				 pdata,
				 &eth_fephy_ed_time_fops)) {
		pr_err("Can't create 'fephy_ed_time' file.\n");
		goto fail;
	}

	return 0;
fail:
	debugfs_remove_recursive(pdata->root);

	return -ENOENT;
}
/*****************************************************************************/

int hieth_dbg_deinit(struct platform_device *pdev)
{
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);

	debugfs_remove_recursive(pdata->root);
	return 0;
}
