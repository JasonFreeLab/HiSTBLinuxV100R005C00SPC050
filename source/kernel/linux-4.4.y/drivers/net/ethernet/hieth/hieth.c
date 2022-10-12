#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/etherdevice.h>
#include <linux/platform_device.h>
#include <linux/of_net.h>
#include <linux/of_mdio.h>
#include <linux/clk.h>
#include <linux/circ_buf.h>
#include <linux/hikapi.h>
#include <linux/netdevice.h>

#include "hieth.h"
#include "mdio.h"
#include "hieth_dbg.h"

#define FEMAC_RX_REFILL_IN_IRQ

/* default, eth enable */
static bool hieth_disable;
bool hieth_fephy_opt;

#ifdef MODULE
module_param(hieth_disable, bool, 0);
module_param(hieth_fephy_opt, bool, 0);
#else
static int __init hieth_noeth(char *str)
{
	hieth_disable = true;

	return 0;
}

early_param("noeth", hieth_noeth);

static int __init hieth_fephy_opt_check(char *str)
{
	hieth_fephy_opt = true;

	return 0;
}
early_param("fephy_opt", hieth_fephy_opt_check);
#endif

#include "pm.c"

int hieth_set_fephy_ed_time(unsigned int ed_time, struct hieth_platdrv_data *pdata)
{
	struct net_device *ndev;
	int ret;
	int i;

	for (i = 0; i < HIETH_MAX_PORT; i++) {
		ndev = pdata->hieth_devs_save[i];
		if (ndev && pdata->hieth_phy_param[i].isinternal) {
			ret = fephy_set_ed_time(ndev->phydev, ed_time);
			if (ret)
				return ret;
		}
	}

	return 0;
}

static int hieth_hw_set_macaddress(struct hieth_netdev_priv *priv,
				   unsigned char *mac)
{
	u32 reg;

	if (priv->port == HIETH_PORT_1) {
		reg = hieth_readl(priv->glb_base, HIETH_GLB_DN_HOSTMAC_ENA);
		reg |= HIETH_GLB_DN_HOSTMAC_ENA_BIT;
		hieth_writel(priv->glb_base, reg, HIETH_GLB_DN_HOSTMAC_ENA);
	}

	reg = mac[1] | (mac[0] << 8);
	if (priv->port == HIETH_PORT_0)
		hieth_writel(priv->glb_base, reg, HIETH_GLB_HOSTMAC_H16);
	else
		hieth_writel(priv->glb_base, reg, HIETH_GLB_DN_HOSTMAC_H16);

	reg = mac[5] | (mac[4] << 8) | (mac[3] << 16) | (mac[2] << 24);
	if (priv->port == HIETH_PORT_0)
		hieth_writel(priv->glb_base, reg, HIETH_GLB_HOSTMAC_L32);
	else
		hieth_writel(priv->glb_base, reg, HIETH_GLB_DN_HOSTMAC_L32);

	return 0;
}

static void hieth_irq_enable(struct hieth_netdev_priv *priv, int irqs)
{
	u32 val;

	local_lock(priv);
	val = hieth_readl(priv->glb_base, HIETH_GLB_IRQ_ENA);
	hieth_writel(priv->glb_base, val | irqs, HIETH_GLB_IRQ_ENA);
	local_unlock(priv);
}

static void hieth_irq_disable(struct hieth_netdev_priv *priv, int irqs)
{
	u32 val;

	local_lock(priv);
	val = hieth_readl(priv->glb_base, HIETH_GLB_IRQ_ENA);
	hieth_writel(priv->glb_base, val & (~irqs), HIETH_GLB_IRQ_ENA);
	local_unlock(priv);
}

static void hieth_clear_irqstatus(struct hieth_netdev_priv *priv, int irqs)
{
	local_lock(priv);
	hieth_writel(priv->glb_base, irqs, HIETH_GLB_IRQ_RAW);
	local_unlock(priv);
}

static int hieth_port_reset(struct hieth_netdev_priv *priv)
{
	struct hieth_platdrv_data *pdata = dev_get_drvdata(priv->dev);
	u32 rst_bit = 0;
	u32 val;

	if (pdata->hieth_real_port_cnt == 1)
		rst_bit = HIETH_GLB_SOFT_RESET_ALL;
	else {
		if (priv->port == HIETH_PORT_0) {
			rst_bit |= HIETH_GLB_SOFT_RESET_P0;
		} else if (priv->port == HIETH_PORT_1) {
			rst_bit |= HIETH_GLB_SOFT_RESET_P1;
		}
	}

	val = hieth_readl(priv->glb_base, HIETH_GLB_SOFT_RESET);

	val |= rst_bit;
	hieth_writel(priv->glb_base, val, HIETH_GLB_SOFT_RESET);
	usleep_range(1000, 10000);
	val &= ~rst_bit;
	hieth_writel(priv->glb_base, val, HIETH_GLB_SOFT_RESET);
	usleep_range(1000, 10000);
	val |= rst_bit;
	hieth_writel(priv->glb_base, val, HIETH_GLB_SOFT_RESET);
	usleep_range(1000, 10000);
	val &= ~rst_bit;
	hieth_writel(priv->glb_base, val, HIETH_GLB_SOFT_RESET);

	return 0;
}

static void hieth_port_init(struct hieth_netdev_priv *priv)
{
	u32 val;
	int phy_intf = (priv->phy_mode == PHY_INTERFACE_MODE_MII ?
			HIETH_P_MAC_PORTSEL_MII : HIETH_P_MAC_PORTSEL_RMII);

	/* set little endian */
	val = hieth_readl(priv->glb_base, HIETH_GLB_ENDIAN_MOD);
	val |= HIETH_GLB_ENDIAN_MOD_IN;
	val |= HIETH_GLB_ENDIAN_MOD_OUT;
	hieth_writel(priv->glb_base, val, HIETH_GLB_ENDIAN_MOD);

	/* set stat ctrl to cpuset, and MII or RMII mode */
	hieth_writel(priv->port_base, phy_intf | HIETH_P_MAC_PORTSEL_STAT_CPU,
		     HIETH_P_MAC_PORTSEL);

	/*clear all interrupt status */
	hieth_clear_irqstatus(priv, UD_BIT_NAME(HIETH_GLB_IRQ_ENA_BIT));

	/*disable interrupts */
	hieth_irq_disable(priv, UD_BIT_NAME(HIETH_GLB_IRQ_ENA_BIT) |
			  UD_BIT_NAME(HIETH_GLB_IRQ_ENA_IEN));

	/* disable vlan, enable UpEther<->CPU */
	val = hieth_readl(priv->glb_base, HIETH_GLB_FWCTRL);
	val &= ~HIETH_GLB_FWCTRL_VLAN_ENABLE;
	val |= UD_BIT_NAME(HIETH_GLB_FWCTRL_FW2CPU_ENA);
	val &= ~(UD_BIT_NAME(HIETH_GLB_FWCTRL_FWALL2CPU));
	hieth_writel(priv->glb_base, val, HIETH_GLB_FWCTRL);
	val = hieth_readl(priv->glb_base, HIETH_GLB_MACTCTRL);
	val |= UD_BIT_NAME(HIETH_GLB_MACTCTRL_BROAD2CPU);
	val |= UD_BIT_NAME(HIETH_GLB_MACTCTRL_MACT_ENA);
	hieth_writel(priv->glb_base, val, HIETH_GLB_MACTCTRL);

	/* set pre count limit */
	val = hieth_readl(priv->port_base, HIETH_P_MAC_TX_IPGCTRL);
	val &= ~HIETH_P_MAC_TX_IPGCTRL_PRE_CNT_LMT_MSK;
	val |= 0;
	hieth_writel(priv->port_base, val, HIETH_P_MAC_TX_IPGCTRL);

	/* set max receive length */
	val = hieth_readl(priv->port_base, HIETH_P_MAC_SET);
	val &= ~HIETH_P_MAC_SET_LEN_MAX_MSK;
	val |= HIETH_P_MAC_SET_LEN_MAX(HIETH_MAX_RCV_LEN);
	hieth_writel(priv->port_base, val, HIETH_P_MAC_SET);

	/* config Rx Checksum Offload,
	 * disable TCP/UDP payload checksum bad drop
	 */
	val = hieth_readl(priv->port_base, HIETH_P_RX_COE_CTRL);
	val &= ~BIT_COE_PAYLOAD_DROP;
	hieth_writel(priv->port_base, val, HIETH_P_RX_COE_CTRL);
}

static void hieth_set_hwq_depth(struct hieth_netdev_priv *priv)
{
	u32 val;

	val = hieth_readl(priv->port_base, HIETH_P_GLB_QLEN_SET);
	val &= ~HIETH_P_GLB_QLEN_SET_TXQ_DEP_MSK;
	val |= HIETH_P_GLB_QLEN_SET_TXQ_DEP(priv->depth.hw_xmitq);
	val &= ~HIETH_P_GLB_QLEN_SET_RXQ_DEP_MSK;
	val |= HIETH_P_GLB_QLEN_SET_RXQ_DEP(HIETH_MAX_QUEUE_DEPTH -
					    priv->depth.hw_xmitq);
	hieth_writel(priv->port_base, val, HIETH_P_GLB_QLEN_SET);
}

static inline int hieth_hw_xmitq_ready(struct hieth_netdev_priv *priv)
{
	int ret;

	ret = hieth_readl(priv->port_base, HIETH_P_GLB_RO_QUEUE_STAT);
	ret &= HIETH_P_GLB_RO_QUEUE_STAT_XMITQ_RDY_MSK;

	return ret;
}

static int hieth_xmit_release_skb(struct hieth_netdev_priv *priv)
{
	struct hieth_queue *txq = &priv->txq;
	u32 val;
	int ret = 0;
	struct sk_buff *skb;
	dma_addr_t dma_addr;
	u32 tx_comp = 0;
	struct net_device *ndev = priv->ndev;

	local_lock(priv);

	val = hieth_readl(priv->port_base, HIETH_P_GLB_RO_QUEUE_STAT) &
			  HIETH_P_GLB_RO_QUEUE_STAT_XMITQ_CNT_INUSE_MSK;
	while (val < priv->tx_fifo_used_cnt) {
		skb = txq->skb[txq->tail];

		if (!skb) {
			pr_err("hw_xmitq_cnt_inuse=%d, tx_fifo_used_cnt=%d\n",
			       val, priv->tx_fifo_used_cnt);
			ret = -1;
			goto error_exit;
		}
#ifdef HIETH_SKB_MEMORY_STATS
		atomic_dec(&priv->tx_skb_occupied);
		atomic_sub(skb->truesize, &priv->tx_skb_mem_occupied);
#endif
		dma_addr = priv->txq.dma_phys[txq->tail];
		dma_unmap_single(priv->dev, dma_addr, skb->len, DMA_TO_DEVICE);
		dev_kfree_skb_any(skb);

		priv->tx_fifo_used_cnt--;
		tx_comp++;

		val = hieth_readl(priv->port_base, HIETH_P_GLB_RO_QUEUE_STAT) &
				HIETH_P_GLB_RO_QUEUE_STAT_XMITQ_CNT_INUSE_MSK;
		txq->skb[txq->tail] = NULL;
		txq->tail = (txq->tail + 1) % txq->num;
	}

	if (tx_comp)
		netif_wake_queue(ndev);

error_exit:
	local_unlock(priv);
	return ret;
}

#if CONFIG_HIETH_MAX_RX_POOLS
static __maybe_unused struct sk_buff *hieth_platdev_alloc_skb(struct hieth_netdev_priv *priv)
{
	struct sk_buff *skb;
	int i;

	skb = priv->rx_pool.sk_pool[priv->rx_pool.next_free_skb++];

	if (priv->rx_pool.next_free_skb == CONFIG_HIETH_MAX_RX_POOLS)
		priv->rx_pool.next_free_skb = 0;

	/*current skb is used by kernel or other process,find another skb*/
	if (skb_shared(skb) || (atomic_read(&(skb_shinfo(skb)->dataref)) > 1)) {
		for (i = 0; i < CONFIG_HIETH_MAX_RX_POOLS; i++) {
			skb = priv->rx_pool.sk_pool[priv->
						    rx_pool.next_free_skb++];
			if (priv->rx_pool.next_free_skb ==
			    CONFIG_HIETH_MAX_RX_POOLS)
				priv->rx_pool.next_free_skb = 0;

			if ((skb_shared(skb) == 0) &&
			    (atomic_read(&(skb_shinfo(skb)->dataref)) <= 1))
				break;
		}

		if (i == CONFIG_HIETH_MAX_RX_POOLS) {
			priv->stat.rx_pool_dry_times++;
			pr_debug("%ld: no free skb\n",
				    priv->stat.rx_pool_dry_times);
			skb = netdev_alloc_skb_ip_align(priv->ndev, SKB_SIZE);
			return skb;
		}
	}
	memset(skb, 0, offsetof(struct sk_buff, tail));

	skb->data = skb->head;
	skb_reset_tail_pointer(skb);
	WARN(skb->end != (skb->tail + SKB_DATA_ALIGN(SKB_SIZE + NET_IP_ALIGN + NET_SKB_PAD)),
	     "head=%p, tail=%x, end=%x\n", skb->head, (unsigned int)skb->tail,
	     (unsigned int)skb->end);
	skb->end = skb->tail + SKB_DATA_ALIGN(SKB_SIZE + NET_IP_ALIGN + NET_SKB_PAD);

	skb_reserve(skb, NET_IP_ALIGN + NET_SKB_PAD);
	skb->len = 0;
	skb->data_len = 0;
	skb->cloned = 0;
	skb->dev = priv->ndev;
	atomic_inc(&skb->users);
	return skb;
}
#endif

static int hieth_feed_hw(struct hieth_netdev_priv *priv)
{
	struct hieth_queue *rxq = &priv->rxq;
	struct sk_buff *skb;
	dma_addr_t addr;
	int cnt = 0;
	int rx_head_len;
	u32 pos;

	/* if skb occupied too much, then do not alloc any more. */
	rx_head_len = skb_queue_len(&priv->rx_head);
	if (rx_head_len > HIETH_MAX_RX_HEAD_LEN)
		return 0;

	local_lock(priv);

	pos = rxq->head;
	while (hieth_readl(priv->port_base, HIETH_P_GLB_RO_QUEUE_STAT) &
		HIETH_P_GLB_RO_QUEUE_STAT_RECVQ_RDY_MSK) {
		if (unlikely(!CIRC_SPACE(pos, rxq->tail, rxq->num)))
			break;
		if (unlikely(rxq->skb[pos])) {
			netdev_err(priv->ndev, "err skb[%d]=%p\n",
					pos, rxq->skb[pos]);
			break;
		}

		skb = netdev_alloc_skb_ip_align(priv->ndev, HIETH_MAX_FRAME_SIZE);
		if (!skb)
			break;

		addr = dma_map_single(priv->dev, skb->data, HIETH_MAX_FRAME_SIZE,
				DMA_FROM_DEVICE);
		if (dma_mapping_error(priv->dev, addr)) {
			dev_kfree_skb_any(skb);
			break;
		}
		rxq->dma_phys[pos] = addr;
		rxq->skb[pos] = skb;

		hieth_writel(priv->port_base, addr, HIETH_P_GLB_IQ_ADDR);
		pos = (pos + 1) % rxq->num;
		cnt++;

#ifdef HIETH_SKB_MEMORY_STATS
		atomic_inc(&priv->rx_skb_occupied);
		atomic_add(skb->truesize, &priv->rx_skb_mem_occupied);
#endif
	}
	rxq->head = pos;

	local_unlock(priv);
	return cnt;
}

static int hieth_recv_budget(struct hieth_netdev_priv *priv)
{
	struct hieth_queue *rxq = &priv->rxq;
	struct sk_buff *skb;
	dma_addr_t addr;
	u32 pos;
	uint32_t rlen;
	int cnt = 0;

	local_lock(priv);

	pos = rxq->tail;
	while ((hieth_readl(priv->glb_base, HIETH_GLB_IRQ_RAW) &
		(UD_BIT_NAME(HIETH_GLB_IRQ_INT_RX_RDY)))) {
		rlen = hieth_readl(priv->port_base, HIETH_P_GLB_RO_IQFRM_DES);
		rlen &= HIETH_P_GLB_RO_IQFRM_DES_FDIN_LEN_MSK;
		rlen -= ETH_FCS_LEN; /* remove FCS 4Bytes */

		/* hw set rx pkg finish */
		hieth_writel(priv->glb_base,
			     UD_BIT_NAME(HIETH_GLB_IRQ_INT_RX_RDY),
			     HIETH_GLB_IRQ_RAW);

		skb = rxq->skb[pos];

		if (!skb) {
			pr_err("chip told us to receive pkg,"
			       "but no more can be received!\n");
			break;
		}
		rxq->skb[pos] = NULL;

		addr = rxq->dma_phys[pos];
		dma_unmap_single(priv->dev, addr, HIETH_MAX_FRAME_SIZE,
			DMA_FROM_DEVICE);
		skb_put(skb, rlen);

		skb_queue_tail(&priv->rx_head, skb);
		pos = (pos + 1) % rxq->num;
		cnt++;
	}
	rxq->tail = pos;

	local_unlock(priv);

	/* fill hardware receive queue again */
	hieth_feed_hw(priv);

	return cnt;
}

static void hieth_adjust_link(struct net_device *dev)
{
	int stat = 0;
	struct hieth_netdev_priv *priv = netdev_priv(dev);

	stat |= (priv->phy->link) ? HIETH_P_MAC_PORTSET_LINKED : 0;
	stat |= (priv->phy->duplex == DUPLEX_FULL) ?
		HIETH_P_MAC_PORTSET_DUP_FULL : 0;
	stat |= (priv->phy->speed == SPEED_100) ?
		HIETH_P_MAC_PORTSET_SPD_100M : 0;

	/* The following expression
	 * "(stat | priv->link_stat) & HIETH_P_MAC_PORTSET_LINKED"
	 * means we only consider three link status change as valid:
	 * 1) down -> up;
	 * 2) up -> down;
	 * 3) up -> up; (maybe the link speed and duplex changed)
	 * We will ignore the "down -> down" condition.
	 */
	if ((stat != priv->link_stat) &&
	    ((stat | priv->link_stat) & HIETH_P_MAC_PORTSET_LINKED)) {
		hieth_writel(priv->port_base, stat, HIETH_P_MAC_PORTSET);
		phy_print_status(priv->phy);
		priv->link_stat = stat;

		if (priv->autoeee_enabled)
			hieth_autoeee_init(priv, stat);
	}
}

#if CONFIG_HIETH_MAX_RX_POOLS
static int hieth_init_skb_buffers(struct hieth_netdev_priv *priv)
{
	int i;
	struct sk_buff *skb;

	for (i = 0; i < CONFIG_HIETH_MAX_RX_POOLS; i++) {
		skb = netdev_alloc_skb_ip_align(priv->ndev, SKB_SIZE);
		if (!skb)
			break;
		priv->rx_pool.sk_pool[i] = skb;
	}

	if (i < CONFIG_HIETH_MAX_RX_POOLS) {
		pr_err("no mem\n");
		for (i--; i > 0; i--)
			dev_kfree_skb_any(priv->rx_pool.sk_pool[i]);
		return -ENOMEM;
	}

	priv->rx_pool.next_free_skb = 0;
	priv->stat.rx_pool_dry_times = 0;
	return 0;
}

static void hieth_destroy_skb_buffers(struct hieth_netdev_priv *priv)
{
	int i;

	for (i = 0; i < CONFIG_HIETH_MAX_RX_POOLS; i++)
		dev_kfree_skb_any(priv->rx_pool.sk_pool[i]);

	priv->rx_pool.next_free_skb = 0;
	priv->stat.rx_pool_dry_times = 0;
}
#endif

static void hieth_net_isr_proc(struct net_device *ndev, int ints)
{
	struct hieth_netdev_priv *priv = netdev_priv(ndev);

	if ((ints & UD_BIT_NAME(HIETH_GLB_IRQ_INT_MULTI_RXRDY)) ||
	    (ints & UD_BIT_NAME(HIETH_GLB_IRQ_INT_TXQUE_RDY))) {
		hieth_clear_irqstatus(priv, UD_BIT_NAME(HIETH_GLB_IRQ_INT_TXQUE_RDY));
#ifdef FEMAC_RX_REFILL_IN_IRQ
		hieth_recv_budget(priv);
#else
		hieth_irq_disable(priv,
				UD_BIT_NAME(HIETH_GLB_IRQ_INT_MULTI_RXRDY));
		hieth_irq_disable(priv,
				UD_BIT_NAME(HIETH_GLB_IRQ_INT_TXQUE_RDY));
#endif
		napi_schedule(&priv->napi);
	}
}

static irqreturn_t hieth_net_isr(int irq, void *dev_id)
{
	int ints;
	struct net_device *dev = (struct net_device *)dev_id;
	struct hieth_netdev_priv *priv = netdev_priv(dev);

	/*mask the all interrupt */
	hieth_irq_disable(priv, HIETH_GLB_IRQ_ENA_IEN_A);

	ints = hieth_readl(priv->glb_base, HIETH_GLB_IRQ_STAT);

	if ((HIETH_PORT_0 == priv->port) &&
	    likely(ints & HIETH_GLB_IRQ_ENA_BIT_U)) {
		hieth_net_isr_proc(dev, (ints & HIETH_GLB_IRQ_ENA_BIT_U));
		hieth_clear_irqstatus(priv, (ints & HIETH_GLB_IRQ_ENA_BIT_U));
		ints &= ~HIETH_GLB_IRQ_ENA_BIT_U;
	}

	if ((HIETH_PORT_1 == priv->port) &&
	    likely(ints & HIETH_GLB_IRQ_ENA_BIT_D)) {
		hieth_net_isr_proc(dev, (ints & HIETH_GLB_IRQ_ENA_BIT_D));
		hieth_clear_irqstatus(priv, (ints & HIETH_GLB_IRQ_ENA_BIT_D));
		ints &= ~HIETH_GLB_IRQ_ENA_BIT_D;
	}

	/*unmask the all interrupt */
	hieth_irq_enable(priv, HIETH_GLB_IRQ_ENA_IEN_A);

	return IRQ_HANDLED;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
/* Polling receive - used by NETCONSOLE and other diagnostic tools
 * to allow network I/O with interrupts disabled.
 */
static void hieth_poll_controller(struct net_device *dev)
{
	disable_irq(dev->irq);
	hieth_net_isr(dev->irq, dev);
	enable_irq(dev->irq);
}
#endif

static void hieth_monitor_func(unsigned long arg)
{
	struct net_device *dev = (struct net_device *)arg;
	struct hieth_netdev_priv *priv = netdev_priv(dev);

	if (!priv || !netif_running(dev)) {
		pr_debug("network driver is stopped.\n");
		return;
	}

	hieth_feed_hw(priv);
	hieth_xmit_release_skb(priv);

	priv->monitor.expires =
	    jiffies + msecs_to_jiffies(HIETH_MONITOR_TIMER);
	add_timer(&priv->monitor);
}

static int hieth_net_open(struct net_device *dev)
{
	int ret = 0;
	struct cpumask cpumask;
	struct hieth_netdev_priv *priv = netdev_priv(dev);

	ret = request_irq(dev->irq, hieth_net_isr, IRQF_SHARED,
			  dev->name, dev);
	if (ret) {
		pr_err("request_irq %d failed!\n", dev->irq);
		return ret;
	}

	/* set irq affinity */
	if ((num_online_cpus() > 1) && cpu_online(HIETH_IRQ_AFFINITY_CPU)) {
		cpumask_clear(&cpumask);
		cpumask_set_cpu(HIETH_IRQ_AFFINITY_CPU, &cpumask);
		irq_set_affinity(dev->irq, &cpumask);
	}

	if (!is_valid_ether_addr(dev->dev_addr))
		random_ether_addr(dev->dev_addr);

	hieth_hw_set_macaddress(priv, dev->dev_addr);

	/* setup hardware */
	hieth_set_hwq_depth(priv);
	hieth_clear_irqstatus(priv, UD_BIT_NAME(HIETH_GLB_IRQ_ENA_BIT));

	netif_carrier_off(dev);
	hieth_feed_hw(priv);

	netif_wake_queue(dev);
	napi_enable(&priv->napi);

	priv->link_stat = 0;
	if (priv->phy)
		phy_start(priv->phy);

	hieth_irq_enable(priv, UD_BIT_NAME(HIETH_GLB_IRQ_INT_MULTI_RXRDY) |
			UD_BIT_NAME(HIETH_GLB_IRQ_ENA_IEN) |
			HIETH_GLB_IRQ_ENA_IEN_A);

	priv->monitor.expires =
	    jiffies + msecs_to_jiffies(HIETH_MONITOR_TIMER);
	add_timer(&priv->monitor);

	return 0;
}

static void hieth_free_skb_rings(struct hieth_netdev_priv *priv);

static int hieth_net_close(struct net_device *dev)
{
	struct hieth_netdev_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;

	hieth_irq_disable(priv, UD_BIT_NAME(HIETH_GLB_IRQ_INT_MULTI_RXRDY));
	napi_disable(&priv->napi);
	netif_stop_queue(dev);
	if (priv->phy)
		phy_stop(priv->phy);

	del_timer_sync(&priv->monitor);

	/* reset and init port */
	hieth_port_reset(priv);

	while ((skb = skb_dequeue(&priv->rx_head)) != NULL) {
#ifdef HIETH_SKB_MEMORY_STATS
		atomic_dec(&priv->rx_skb_occupied);
		atomic_sub(skb->truesize, &priv->rx_skb_mem_occupied);
#endif
		kfree_skb(skb);
	}

	hieth_free_skb_rings(priv);

	free_irq(dev->irq, dev);
	return 0;
}

static void hieth_net_timeout(struct net_device *dev)
{
	pr_err("tx timeout\n");
}

#if defined(CONFIG_ARCH_HI3798MV2X)
#define HIETH_COPY_WHEN_XMIT
#endif

#ifdef HIETH_COPY_WHEN_XMIT
static struct sk_buff *hieth_skb_copy(const struct sk_buff *skb, gfp_t gfp_mask)
{
	unsigned int size = skb->len + ETH_FCS_LEN;
	struct sk_buff *n = __alloc_skb(size, gfp_mask, 0, NUMA_NO_NODE);

	if (!n)
		return NULL;

	/* Set the tail pointer and length */
	skb_put(n, skb->len);

	if (skb_copy_bits(skb, 0, n->data, skb->len))
		WARN_ON(1);

	return n;
}
#endif

static int hieth_net_hard_start_xmit(struct sk_buff *skb,
				     struct net_device *dev)
{
	struct hieth_netdev_priv *priv = netdev_priv(dev);
	struct hieth_queue *txq = &priv->txq;
#ifdef HIETH_COPY_WHEN_XMIT
	bool tx_buff_not_aligned = false;
#endif
	dma_addr_t addr;
	u32 val;

	if (!hieth_hw_xmitq_ready(priv) ||
	    unlikely(!CIRC_SPACE(txq->head, txq->tail, txq->num))) {
		netif_stop_queue(dev);
		hieth_irq_enable(priv,
				UD_BIT_NAME(HIETH_GLB_IRQ_INT_TXQUE_RDY));
		return NETDEV_TX_BUSY;
	}

#ifdef HIETH_COPY_WHEN_XMIT
	tx_buff_not_aligned = (unsigned long)(skb->data) & GENMASK(5, 2);
	if (tx_buff_not_aligned) {
		struct sk_buff *new_skb = NULL;

		new_skb = hieth_skb_copy(skb, GFP_ATOMIC);
		if (new_skb) {
			dev_kfree_skb_any(skb);
			skb = new_skb;
		}
	}
#endif

	addr = dma_map_single(priv->dev, skb->data, skb->len, DMA_TO_DEVICE);
	if (dma_mapping_error(priv->dev, addr)) {
		netdev_err(priv->ndev, "DMA mapping error when sending.");
		priv->stats.tx_errors++;
		priv->stats.tx_dropped++;
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	local_lock(priv);

	/* we must use "skb->len" before sending packet to hardware,
	 * because once we send packet to hardware,
	 * "hieth_xmit_release_skb" in softirq may free this skb.
	 * This bug is reported by KASAN: use-after-free.
	 */
	priv->stats.tx_packets++;
	priv->stats.tx_bytes += skb->len;
#ifdef HIETH_SKB_MEMORY_STATS
	atomic_inc(&priv->tx_skb_occupied);
	atomic_add(skb->truesize, &priv->tx_skb_mem_occupied);
#endif

	txq->dma_phys[txq->head] = addr;
	txq->skb[txq->head] = skb;

	/* for recalc CRC, 4 bytes more is needed */
	hieth_writel(priv->port_base, addr, HIETH_P_GLB_EQ_ADDR);
	val = hieth_readl(priv->port_base, HIETH_P_GLB_EQFRM_LEN);
	val &= ~HIETH_P_GLB_EQFRM_TXINQ_LEN_MSK;
	val |= skb->len + ETH_FCS_LEN;
	hieth_writel(priv->port_base, val, HIETH_P_GLB_EQFRM_LEN);

	txq->head = (txq->head + 1) % txq->num;
	priv->tx_fifo_used_cnt++;

	dev->trans_start = jiffies;

	local_unlock(priv);

	return NETDEV_TX_OK;
}

static struct net_device_stats *hieth_net_get_stats(struct net_device *dev)
{
	struct hieth_netdev_priv *priv = netdev_priv(dev);

	return &priv->stats;
}

static int hieth_net_set_mac_address(struct net_device *dev, void *p)
{
	struct hieth_netdev_priv *priv = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	eth_commit_mac_addr_change(dev, p);
	dev->addr_assign_type &= ~NET_ADDR_RANDOM;

	hieth_hw_set_macaddress(priv, dev->dev_addr);

	return 0;
}

static inline void hieth_enable_mac_addr_filter(struct hieth_netdev_priv *priv,
						unsigned int reg_n, int enable)
{
	u32 val;

	val = hieth_readl(priv->glb_base, GLB_MAC_H16(priv->port, reg_n));
	if (enable)
		val |= UD_BIT_NAME(HIETH_GLB_MACFLT_ENA);
	else
		val &= ~(UD_BIT_NAME(HIETH_GLB_MACFLT_ENA));
	hieth_writel(priv->glb_base, val, GLB_MAC_H16(priv->port, reg_n));
}

static void hieth_set_mac_addr(struct hieth_netdev_priv *priv, u8 addr[6],
			       unsigned int high, unsigned int low)
{
	u32 val;
	u32 data;

	val = hieth_readl(priv->glb_base, high);
	val |= UD_BIT_NAME(HIETH_GLB_MACFLT_ENA);
	hieth_writel(priv->glb_base, val, high);

	val &= ~HIETH_GLB_MACFLT_HI16;
	val |= ((addr[0] << 8) | addr[1]);
	hieth_writel(priv->glb_base, val, high);

	data = (addr[2] << 24) | (addr[3] << 16) | (addr[4] << 8) | addr[5];
	hieth_writel(priv->glb_base, data, low);

	val |= UD_BIT_NAME(HIETH_GLB_MACFLT_FW2CPU);
	hieth_writel(priv->glb_base, val, high);
}

static inline void hieth_set_mac_addr_filter(struct hieth_netdev_priv *priv,
					     unsigned char *addr,
					     unsigned int reg_n)
{
	hieth_set_mac_addr(priv, addr, GLB_MAC_H16(priv->port, reg_n),
			   GLB_MAC_L32(priv->port, reg_n));
}

static void hieth_net_set_rx_mode(struct net_device *dev)
{
	u32 val;
	struct hieth_netdev_priv *priv = netdev_priv(dev);
	struct hieth_platdrv_data *pdata = dev_get_drvdata(priv->dev);

	local_lock(priv);
	multicast_dump_netdev_flags(dev->flags, pdata);
	val = hieth_readl(priv->glb_base, HIETH_GLB_FWCTRL);
	if (dev->flags & IFF_PROMISC) {
		val |= ((priv->port == HIETH_PORT_0) ?
			HIETH_GLB_FWCTRL_FWALL2CPU_U :
			HIETH_GLB_FWCTRL_FWALL2CPU_D);
		hieth_writel(priv->glb_base, val, HIETH_GLB_FWCTRL);
	} else {
		val &= ~((priv->port == HIETH_PORT_0) ?
			HIETH_GLB_FWCTRL_FWALL2CPU_U :
			HIETH_GLB_FWCTRL_FWALL2CPU_D);
		hieth_writel(priv->glb_base, val, HIETH_GLB_FWCTRL);

		val = hieth_readl(priv->glb_base, HIETH_GLB_MACTCTRL);
		if ((netdev_mc_count(dev) > HIETH_MAX_MULTICAST_ADDRESSES) ||
		    (dev->flags & IFF_ALLMULTI)) {
			val |= UD_BIT_NAME(HIETH_GLB_MACTCTRL_MULTI2CPU);
		} else {
			int reg = HIETH_MAX_UNICAST_ADDRESSES;
			int i, nr = 0;
			struct netdev_hw_addr *ha;

			for (i = reg; i < HIETH_MAX_MAC_FILTER_NUM; i++)
				hieth_enable_mac_addr_filter(priv, i, 0);

			netdev_for_each_mc_addr(ha, dev) {
				hieth_set_mac_addr_filter(priv, ha->addr, reg);
				multicast_dump_macaddr(nr++, ha->addr, pdata);
				reg++;
			}

			val &= ~(UD_BIT_NAME(HIETH_GLB_MACTCTRL_MULTI2CPU));
		}

		/* Handle multiple unicast addresses (perfect filtering)*/
		if (netdev_uc_count(dev) > HIETH_MAX_UNICAST_ADDRESSES) {
			val |= UD_BIT_NAME(HIETH_GLB_MACTCTRL_UNI2CPU);
		} else {
			int reg = 0;
			int i;
			struct netdev_hw_addr *ha;

			for (i = reg; i < HIETH_MAX_UNICAST_ADDRESSES; i++)
				hieth_enable_mac_addr_filter(priv, i, 0);

			netdev_for_each_uc_addr(ha, dev) {
				hieth_set_mac_addr_filter(priv, ha->addr, reg);
				reg++;
			}

			val &= ~(UD_BIT_NAME(HIETH_GLB_MACTCTRL_UNI2CPU));
		}
		hieth_writel(priv->glb_base, val, HIETH_GLB_MACTCTRL);
	}

	local_unlock(priv);
}

static int hieth_net_ioctl(struct net_device *net_dev,
			   struct ifreq *ifreq, int cmd)
{
	struct hieth_netdev_priv *priv = netdev_priv(net_dev);
	struct hieth_pm_config pm_config;

	switch (cmd) {
	case SIOCSETPM:
		if (copy_from_user(&pm_config, ifreq->ifr_data,
				   sizeof(pm_config)))
			return -EFAULT;
		return hieth_pmt_config(net_dev, &pm_config);

	default:
		if (!netif_running(net_dev))
			return -EINVAL;

		if (!priv->phy)
			return -EINVAL;

		return phy_mii_ioctl(priv->phy, ifreq, cmd);
	}

	return 0;
}

static void hieth_ethtools_get_drvinfo(struct net_device *net_dev,
				       struct ethtool_drvinfo *info)
{
	strcpy(info->driver, "hieth driver");
	strcpy(info->version, "v300");
	strcpy(info->bus_info, "platform");
}

static u32 hieth_ethtools_get_link(struct net_device *net_dev)
{
	struct hieth_netdev_priv *priv = netdev_priv(net_dev);

	return ((priv->phy->link) ? HIETH_P_MAC_PORTSET_LINKED : 0);
}

static int hieth_ethtools_get_settings(struct net_device *net_dev,
				       struct ethtool_cmd *cmd)
{
	struct hieth_netdev_priv *priv = netdev_priv(net_dev);

	if (priv->phy)
		return phy_ethtool_gset(priv->phy, cmd);

	return -EINVAL;
}

static int hieth_ethtools_set_settings(struct net_device *net_dev,
				       struct ethtool_cmd *cmd)
{
	struct hieth_netdev_priv *priv = netdev_priv(net_dev);

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (priv->phy)
		return phy_ethtool_sset(priv->phy, cmd);

	return -EINVAL;
}

static void hieth_get_mac_wol(struct net_device *dev,
			       struct ethtool_wolinfo *wol)
{
	wol->supported = WAKE_UCAST | WAKE_MAGIC;
	wol->wolopts = 0;
}

static void hieth_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	wol->supported = 0;
	wol->wolopts = 0;

	if (dev->phydev)
		phy_ethtool_get_wol(dev->phydev, wol);

	if (!wol->supported)
		hieth_get_mac_wol(dev, wol);
}

static int hieth_set_mac_wol(struct net_device *dev,
			     struct ethtool_wolinfo *wol)
{
	struct hieth_netdev_priv *priv = netdev_priv(dev);
	int err = 0;
	struct hieth_pm_config mac_pm_config = { 0 };

	mac_pm_config.index = BIT(priv->port);
	if (wol->wolopts & WAKE_UCAST)
		mac_pm_config.uc_pkts_enable = 1;

	if (wol->wolopts & WAKE_MAGIC)
		mac_pm_config.magic_pkts_enable = 1;

	hieth_pmt_config(dev, &mac_pm_config);

	return err;
}

static int hieth_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct hieth_netdev_priv *priv = netdev_priv(dev);
	int err = 0;

	if (dev->phydev)
		err = phy_ethtool_set_wol(dev->phydev, wol);
	if (err == -EOPNOTSUPP)
		err = hieth_set_mac_wol(dev, wol);

	if (!err)
		priv->mac_wol_enabled = true;

	return err;
}

static struct ethtool_ops hieth_ethtools_ops = {
	.get_drvinfo = hieth_ethtools_get_drvinfo,
	.get_link = hieth_ethtools_get_link,
	.get_settings = hieth_ethtools_get_settings,
	.set_settings = hieth_ethtools_set_settings,
	.get_wol = hieth_get_wol,
	.set_wol = hieth_set_wol,
};

static const struct net_device_ops hieth_netdev_ops = {
	.ndo_open = hieth_net_open,
	.ndo_stop = hieth_net_close,
	.ndo_start_xmit = hieth_net_hard_start_xmit,
	.ndo_tx_timeout = hieth_net_timeout,
	.ndo_do_ioctl = hieth_net_ioctl,
	.ndo_set_mac_address = hieth_net_set_mac_address,
	.ndo_set_rx_mode	= hieth_net_set_rx_mode,
	.ndo_change_mtu		= eth_change_mtu,
	.ndo_get_stats = hieth_net_get_stats,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller = hieth_poll_controller,
#endif
};

void hieth_clean_rx(struct hieth_netdev_priv *priv, unsigned int *workdone, int budget)
{
	unsigned int nr_recv = 0;
	struct sk_buff *skb;
	struct net_device *dev = priv->ndev;
	int ret = 0;

	hieth_recv_budget(priv);

	while ((skb = skb_dequeue(&priv->rx_head)) != NULL) {
#ifdef HIETH_SKB_MEMORY_STATS
		atomic_dec(&priv->rx_skb_occupied);
		atomic_sub(skb->truesize, &priv->rx_skb_mem_occupied);
#endif

		skb->protocol = eth_type_trans(skb, dev);

		if (HIETH_INVALID_RXPKG_LEN(skb->len)) {
			pr_err("pkg len error");
			priv->stats.rx_errors++;
			priv->stats.rx_length_errors++;
			dev_kfree_skb_any(skb);
			continue;
		}

		priv->stats.rx_packets++;
		priv->stats.rx_bytes += skb->len;
		dev->last_rx = jiffies;
		skb->dev = dev;

		ret = netif_receive_skb(skb);
		if (ret) {
			priv->stats.rx_dropped++;
		}

		nr_recv++;
		if (nr_recv >= budget)
			break;
	}

	if (workdone)
		*workdone = nr_recv;
}

static int hieth_poll(struct napi_struct *napi, int budget)
{
	struct hieth_netdev_priv *priv = NULL;
	unsigned int work_done = 0;
	priv= container_of(napi, struct hieth_netdev_priv, napi);

	hieth_xmit_release_skb(priv);
	hieth_clean_rx(priv, &work_done, budget);

	if (work_done < budget) {
		napi_complete(napi);
		hieth_irq_enable(priv, UD_BIT_NAME(HIETH_GLB_IRQ_INT_MULTI_RXRDY));
	}
	return work_done;
}

static int hieth_init_queue(struct device *dev,
		struct hieth_queue *queue,
		unsigned int num)
{
	queue->skb = devm_kcalloc(dev, num, sizeof(struct sk_buff *),
			GFP_KERNEL);
	if (!queue->skb)
		return -ENOMEM;

	queue->dma_phys = devm_kcalloc(dev, num, sizeof(dma_addr_t),
			GFP_KERNEL);
	if (!queue->dma_phys)
		return -ENOMEM;

	queue->num = num;
	queue->head = 0;
	queue->tail = 0;

	return 0;
}

static int hieth_init_tx_and_rx_queues(struct hieth_netdev_priv *priv)
{
	int ret;

	ret = hieth_init_queue(priv->dev, &priv->txq, TXQ_NUM);
	if (ret)
		return ret;

	ret = hieth_init_queue(priv->dev, &priv->rxq, RXQ_NUM);
	if (ret)
		return ret;

	priv->tx_fifo_used_cnt = 0;

	return 0;
}

static void hieth_free_skb_rings(struct hieth_netdev_priv *priv)
{
	struct hieth_queue *txq = &priv->txq;
	struct hieth_queue *rxq = &priv->rxq;
	struct sk_buff *skb;
	dma_addr_t dma_addr;
	u32 pos;

	pos = rxq->tail;
	while (pos != rxq->head) {
		skb = rxq->skb[pos];
		if (unlikely(!skb)) {
			netdev_err(priv->ndev, "NULL rx skb. pos=%d, head=%d\n",
					pos, rxq->head);
			continue;
		}

		dma_addr = rxq->dma_phys[pos];
		dma_unmap_single(priv->dev, dma_addr, HIETH_MAX_FRAME_SIZE,
				DMA_FROM_DEVICE);
#ifdef HIETH_SKB_MEMORY_STATS
		atomic_dec(&priv->rx_skb_occupied);
		atomic_sub(skb->truesize, &priv->rx_skb_mem_occupied);
#endif
		dev_kfree_skb_any(skb);
		rxq->skb[pos] = NULL;
		pos = (pos + 1) % rxq->num;
	}
	rxq->tail = pos;

	pos = txq->tail;
	while (pos != txq->head) {
		skb = txq->skb[pos];
		if (unlikely(!skb)) {
			netdev_err(priv->ndev, "NULL tx skb. pos=%d, head=%d\n",
					pos, txq->head);
			continue;
		}
		dma_addr = txq->dma_phys[pos];
		dma_unmap_single(priv->dev, dma_addr, skb->len, DMA_TO_DEVICE);
#ifdef HIETH_SKB_MEMORY_STATS
		atomic_dec(&priv->tx_skb_occupied);
		atomic_sub(skb->truesize, &priv->tx_skb_mem_occupied);
#endif
		dev_kfree_skb_any(skb);
		txq->skb[pos] = NULL;
		pos = (pos + 1) % txq->num;
	}
	txq->tail = pos;
	priv->tx_fifo_used_cnt = 0;
}

static int hieth_platdev_probe_port(struct platform_device *pdev,
				    struct hieth_netdev_priv *com_priv,
				    int port)
{
	int ret = -1;
	struct net_device *netdev = NULL;
	struct device *dev = &pdev->dev;
	struct hieth_netdev_priv *priv;
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);

	if ((HIETH_PORT_0 != port) && (HIETH_PORT_1 != port)) {
		pr_err("port error!\n");
		ret = -ENODEV;
		goto _error_exit;
	}

	netdev = alloc_etherdev(sizeof(*priv));
	if (netdev == NULL) {
		pr_err("alloc_etherdev fail!\n");
		ret = -ENOMEM;
		goto _error_exit;
	}

	SET_NETDEV_DEV(netdev, &pdev->dev);

	netdev->irq = com_priv->irq;

	netdev->watchdog_timeo = 3 * HZ;
	netdev->netdev_ops = &hieth_netdev_ops;
	netdev->ethtool_ops = &hieth_ethtools_ops;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	if (pdata->hieth_phy_param[port].macaddr)
		ether_addr_copy(netdev->dev_addr,
				pdata->hieth_phy_param[port].macaddr);

	if (!is_valid_ether_addr(netdev->dev_addr))
		eth_hw_addr_random(netdev);

	/* init hieth_global somethings... */
	pdata->hieth_devs_save[port] = netdev;

	/* init hieth_local_driver */
	priv = netdev_priv(netdev);
	memset(priv, 0, sizeof(*priv));
	memcpy(priv, com_priv, sizeof(*priv));

	local_lock_init(priv);

	priv->port = port;

	if (port == HIETH_PORT_0)
		priv->port_base = priv->glb_base;
	else
		priv->port_base = priv->glb_base + 0x2000;

	priv->dev = dev;
	priv->ndev = netdev;

	init_timer(&priv->monitor);
	priv->monitor.function = hieth_monitor_func;
	priv->monitor.data = (unsigned long)netdev;
	priv->monitor.expires =
	    jiffies + msecs_to_jiffies(HIETH_MONITOR_TIMER);

	/* wol need */
	device_set_wakeup_capable(priv->dev, 1);
	/* TODO: when we can let phy powerdown?
	 * In forcing fwd mode, we don't want phy powerdown,
	 * so I set wakeup enable all the time
	 */
	device_set_wakeup_enable(priv->dev, 1);
	priv->pm_state_set = false;

	/* reset and init port */
	hieth_port_init(priv);

	priv->depth.hw_xmitq = HIETH_HWQ_XMIT_DEPTH;

	priv->phy = of_phy_connect(netdev, priv->phy_node,
				   hieth_adjust_link, 0, priv->phy_mode);
	if (!(priv->phy) || IS_ERR(priv->phy)) {
		pr_info("connect to port[%d] PHY failed!\n", port);
		priv->phy = NULL;
		goto _error_phy_connect;
	}

	pr_info("attached port %d PHY %d to driver %s\n",
		port, priv->phy->addr, priv->phy->drv->name);

	if (priv->autoeee_enabled)
		hieth_autoeee_init(priv, 0);

	skb_queue_head_init(&priv->rx_head);

#ifdef HIETH_SKB_MEMORY_STATS
	atomic_set(&priv->tx_skb_occupied, 0);
	atomic_set(&priv->tx_skb_mem_occupied, 0);
	atomic_set(&priv->rx_skb_occupied, 0);
	atomic_set(&priv->rx_skb_mem_occupied, 0);
#endif

#if CONFIG_HIETH_MAX_RX_POOLS
	ret = hieth_init_skb_buffers(priv);
	if (ret) {
		pr_err("hieth_init_skb_buffers failed!\n");
		goto _error_init_skb_buffers;
	}
#endif
	ret = hieth_init_tx_and_rx_queues(priv);
	if (ret)
		goto _error_register_netdev;

	netif_napi_add(netdev, &priv->napi, hieth_poll, HIETH_NAPI_WEIGHT);

	ret = register_netdev(netdev);
	if (ret) {
		pr_err("register_netdev %s failed!\n", netdev->name);
		goto _error_register_netdev;
	}

	phy_stop(priv->phy);

	return ret;

_error_register_netdev:
#if CONFIG_HIETH_MAX_RX_POOLS
	hieth_destroy_skb_buffers(priv);

_error_init_skb_buffers:
#endif
	phy_disconnect(priv->phy);
	priv->phy = NULL;

_error_phy_connect:
	local_lock_exit();
	pdata->hieth_devs_save[port] = NULL;
	free_netdev(netdev);

_error_exit:
	return ret;
}

static int hieth_platdev_remove_port(struct platform_device *pdev, int port)
{
	struct net_device *ndev;
	struct hieth_netdev_priv *priv;
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);

	ndev = pdata->hieth_devs_save[port];

	if (!ndev)
		goto _ndev_exit;

	priv = netdev_priv(ndev);

	unregister_netdev(ndev);
#if CONFIG_HIETH_MAX_RX_POOLS
	hieth_destroy_skb_buffers(priv);
#endif

	phy_disconnect(priv->phy);
	priv->phy = NULL;

	iounmap((void *)priv->glb_base);

	local_lock_exit();

	pdata->hieth_devs_save[port] = NULL;
	free_netdev(ndev);

_ndev_exit:
	return 0;
}

#define DEFAULT_LD_AM          0xe
#define DEFAULT_LDO_AM         0x3
#define DEFAULT_R_TUNING       0x16
static void hieth_of_get_phy_trim_params(struct hieth_platdrv_data *pdata, int port_index)
{
	struct device_node *chiptrim_node;
	u32 phy_trim_val = 0;
	u8 ld_am, ldo_am, r_tuning;
	int ret;

	/* currently only one internal PHY */
	if (port_index == HIETH_PORT_1)
		return;

	chiptrim_node = of_find_node_by_path("chiptrim");
	if (!chiptrim_node)
		return;

	ld_am = DEFAULT_LD_AM;
	ldo_am = DEFAULT_LDO_AM;
	r_tuning = DEFAULT_R_TUNING;

	ret = of_property_read_u32(chiptrim_node, "chiptrim0", &phy_trim_val);
	if (ret) {
		pr_err("%s,%d: chiptrim0 property not found\n",
			__func__, __LINE__);
		return;
	}

	if (phy_trim_val) {
		ld_am = (phy_trim_val >> 11) & 0x1f;
		ldo_am = (phy_trim_val >> 8) & 0x7;
		r_tuning = phy_trim_val & 0x3f;
	}

	pdata->hieth_phy_param[port_index].trim_params =
		(r_tuning << 16) | (ldo_am << 8) | ld_am;
}

static int hieth_of_get_param(struct device_node *node, struct hieth_platdrv_data *pdata)
{
	struct device_node *child = NULL;
	int idx = 0;
	int data;

	for_each_available_child_of_node(node, child) {
		/* get phy-addr */
		if (of_property_read_u32(child, "reg", &data))
			return -EINVAL;
		if ((data < 0) || (data >= PHY_MAX_ADDR)) {
			pr_info("%s has invalid PHY address\n",
				child->full_name);
			data = HIETH_INVALID_PHY_ADDR;
		}

		pdata->hieth_phy_param[idx].phy_addr = data;
		if (data != HIETH_INVALID_PHY_ADDR)
			pdata->hieth_phy_param[idx].isvalid = true;

		/* get phy_mode */
		pdata->hieth_phy_param[idx].phy_mode = of_get_phy_mode(child);

		/* get mac */
		pdata->hieth_phy_param[idx].macaddr = of_get_mac_address(child);

		/* get gpio_base and bit */
		of_property_read_u32(child, "phy-gpio-base",
				     (u32 *)(&pdata->hieth_phy_param[idx].gpio_base));
		of_property_read_u32(child, "phy-gpio-bit",
				     &pdata->hieth_phy_param[idx].gpio_bit);

		/* get internal flag */
		pdata->hieth_phy_param[idx].isinternal =
			of_property_read_bool(child, "internal-phy");

		hieth_of_get_phy_trim_params(pdata, idx);

		if (++idx >= HIETH_MAX_PORT)
			break;
	}

	return 0;
}

static int hieth_plat_driver_probe(struct platform_device *pdev)
{
	int ret = 0;
	int irq;
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct resource *res;
	struct hieth_netdev_priv *priv;
	struct device_node *child = NULL;
	int port = -1;
	struct hieth_platdrv_data *pdata;

	pdata = devm_kzalloc(dev, sizeof(struct hieth_platdrv_data), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	platform_set_drvdata(pdev, pdata);

	priv = &pdata->hieth_priv;

	if (hieth_of_get_param(node, pdata)) {
		pr_err("of get parameter fail\n");
		ret = -ENODEV;
		goto exit;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->glb_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->glb_base)) {
		pr_err("error ioremap resource[%x - %x]\n", res->start, res->end);
		ret = PTR_ERR(priv->glb_base);
		goto exit;
	}
	hieth_dbg_init(priv->glb_base, pdev);

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk)) {
		pr_err("failed to get clk\n");
		ret = -ENODEV;
		goto exit;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		pr_err("no IRQ defined!\n");
		ret = -ENODEV;
		goto exit;
	}
	priv->irq = irq;

	/* first disable ETH clock, then reset PHY to load PHY address */
	hieth_phy_reset(pdata);

	ret = clk_prepare_enable(priv->clk);
	if (ret < 0) {
		pr_err("failed to enable clk %d\n", ret);
		goto exit;
	}
	/* After MDCK clock giving, wait 5ms before MDIO access */
	mdelay(5);

	if (hieth_mdiobus_driver_init(pdev, priv)) {
		pr_err("mdio bus init error!\n");
		ret = -ENODEV;
		goto exit_clk_disable;
	}

	/* phy param */
	hieth_phy_register_fixups();

	for_each_available_child_of_node(node, child) {
		if (++port >= HIETH_MAX_PORT)
			break;

		if (!pdata->hieth_phy_param[port].isvalid)
			continue;

		priv->phy_node = of_parse_phandle(node, "phy-handle", port);
		if (!priv->phy_node) {
			pr_err("not find phy-handle [%d]\n", port);
			continue;
		}

		priv->phy_mode = pdata->hieth_phy_param[port].phy_mode;
		priv->autoeee_enabled = of_property_read_bool(child, "autoeee");

		if (!hieth_platdev_probe_port(pdev, priv, port))
			pdata->hieth_real_port_cnt++;
	}

	if (!pdata->hieth_devs_save[HIETH_PORT_0] &&
	    !pdata->hieth_devs_save[HIETH_PORT_1]) {
		pr_err("no dev probed!\n");
		ret = -ENODEV;
		goto exit_mdiobus;
	}

	return ret;

exit_mdiobus:
	hieth_mdiobus_driver_exit(priv);

exit_clk_disable:
	clk_disable_unprepare(priv->clk);

exit:

	return ret;
}

static int hieth_plat_driver_remove(struct platform_device *pdev)
{
	int i;
	struct net_device *ndev = NULL;
	struct hieth_netdev_priv *priv = NULL;
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);

	if (pdata->hieth_devs_save[HIETH_PORT_0])
		ndev = pdata->hieth_devs_save[HIETH_PORT_0];
	else if (pdata->hieth_devs_save[HIETH_PORT_1])
		ndev = pdata->hieth_devs_save[HIETH_PORT_1];

	priv = netdev_priv(ndev);

	hieth_dbg_deinit(pdev);

	for (i = 0; i < HIETH_MAX_PORT; i++)
		hieth_platdev_remove_port(pdev, i);

	hieth_mdiobus_driver_exit(priv);

	clk_disable_unprepare(priv->clk);

	memset(pdata->hieth_devs_save, 0, sizeof(pdata->hieth_devs_save));

	hieth_phy_unregister_fixups();

	return 0;
}

#ifdef CONFIG_PM
static int hieth_plat_driver_suspend_port(struct platform_device *pdev,
					  pm_message_t state, int port)
{
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);
	struct net_device *ndev = pdata->hieth_devs_save[port];

	if (ndev) {
		if (netif_running(ndev)) {
			netif_device_detach(ndev);
			hieth_net_close(ndev);
		}
	}

	return 0;
}

int hieth_plat_driver_suspend(struct platform_device *pdev,
			      pm_message_t state)
{
	int i;
	bool power_off = true;
	struct hieth_netdev_priv *priv = NULL;
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);

	for (i = 0; i < HIETH_MAX_PORT; i++)
		hieth_plat_driver_suspend_port(pdev, state, i);

	if (hieth_pmt_enter(pdev))
		power_off = false;

	if (power_off) {
		for (i = 0; i < HIETH_MAX_PORT; i++) {
			if (pdata->hieth_devs_save[i]) {
				priv = netdev_priv(pdata->hieth_devs_save[i]);
				genphy_suspend(priv->phy);/* power down phy */
			}
		}

		/* need some time before phy suspend finished. */
		usleep_range(1000, 10000);

		if (priv)
			clk_disable_unprepare(priv->clk);

		hieth_phy_clk_disable(pdata);
	}

	return 0;
}

static int hieth_plat_driver_resume_port(struct platform_device *pdev, int port)
{
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);
	struct net_device *ndev = pdata->hieth_devs_save[port];
	struct hieth_netdev_priv *priv = netdev_priv(ndev);

	if (ndev) {
		phy_init_hw(ndev->phydev);
		if (netif_running(ndev)) {
			hieth_port_init(priv);
			hieth_net_open(ndev);
			netif_device_attach(ndev);
		}
	}

	return 0;
}

static bool hieth_mac_wol_enabled(struct platform_device *pdev)
{
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);
	struct hieth_netdev_priv *priv = NULL;
	bool mac_wol_enabled = false;
	int i;

	for (i = 0; i < HIETH_MAX_PORT; i++) {
		if (!pdata->hieth_devs_save[i])
			continue;

		priv = netdev_priv(pdata->hieth_devs_save[i]);
		if (priv->mac_wol_enabled) {
			mac_wol_enabled = true;
			break;
		}
	}

	return mac_wol_enabled;
}

int hieth_plat_driver_resume(struct platform_device *pdev)
{
	int i;
	struct hieth_platdrv_data *pdata = platform_get_drvdata(pdev);
	struct hieth_netdev_priv *priv = &pdata->hieth_priv;

	/* first disable ETH clock, then reset PHY to load PHY address */
	if (hieth_mac_wol_enabled(pdev))
		clk_disable_unprepare(priv->clk);
	hieth_phy_reset(pdata);
	/* enable clk */
	clk_prepare_enable(priv->clk);
	/* After MDCK clock giving, wait 5ms before MDIO access */
	mdelay(5);
	hieth_fix_festa_phy_trim(priv->mii_bus, pdata);

	for (i = 0; i < HIETH_MAX_PORT; i++)
		hieth_plat_driver_resume_port(pdev, i);

	hieth_pmt_exit(pdev);
	return 0;
}
#else
#  define hieth_plat_driver_suspend	NULL
#  define hieth_plat_driver_resume	NULL
#endif

static const struct of_device_id hieth_of_match[] = {
	{.compatible = "hisilicon,hieth", },
	{},
};

MODULE_DEVICE_TABLE(of, hieth_of_match);

static struct platform_driver hieth_platform_driver = {
	.probe = hieth_plat_driver_probe,
	.remove = hieth_plat_driver_remove,
	.suspend = hieth_plat_driver_suspend,
	.resume = hieth_plat_driver_resume,
	.driver = {
		   .owner = THIS_MODULE,
		   .name = HIETH_DRIVER_NAME,
		   .bus = &platform_bus_type,
		   .of_match_table = of_match_ptr(hieth_of_match),
		   },
};

static int hieth_mod_init(void)
{
	int ret = 0;

	if (hieth_disable)
		return 0;

	ret = platform_driver_register(&hieth_platform_driver);
	if (ret)
		pr_err("register platform driver failed!\n");

	return ret;
}

static void hieth_mod_exit(void)
{
	if (hieth_disable)
		return;

	platform_driver_unregister(&hieth_platform_driver);
}

module_init(hieth_mod_init);
module_exit(hieth_mod_exit);

MODULE_DESCRIPTION("Hisilicon ETH driver whith MDIO support");
MODULE_LICENSE("GPL");

/* vim: set ts=8 sw=8 tw=78: */
