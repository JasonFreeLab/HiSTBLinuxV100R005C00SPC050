/*
  * Copyright (c) 2016 MediaTek Inc.  All rights reserved.
  *
  * This software is available to you under a choice of one of two
  * licenses.  You may choose to be licensed under the terms of the GNU
  * General Public License (GPL) Version 2, available from the file
  * COPYING in the main directory of this source tree, or the
  * BSD license below:
  *
  *	Redistribution and use in source and binary forms, with or
  *	without modification, are permitted provided that the following
  *	conditions are met:
  *
  *	 - Redistributions of source code must retain the above
  *	   copyright notice, this list of conditions and the following
  *	   disclaimer.
  *
  *	 - Redistributions in binary form must reproduce the above
  *	   copyright notice, this list of conditions and the following
  *	   disclaimer in the documentation and/or other materials
  *	   provided with the distribution.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  */


#define RTMP_MODULE_OS

/*#include "rt_config.h" */
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24)
#ifndef SA_SHIRQ
#define SA_SHIRQ IRQF_SHARED
#endif /* endif */
#endif /* endif */


/*---------------------------------------------------------------------*/
/* Private Variables Used					       */
/*---------------------------------------------------------------------*/

PSTRING mac = "";		/* default 00:00:00:00:00:00 */
PSTRING mode = "";		/* supported mode: normal/ate/monitor;	default: normal */
PSTRING hostname = "";		/* default CMPC */

#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 12)
MODULE_PARM(mac, "s");
MODULE_PARM(mode, "s");
#else
module_param(mac, charp, 0);
module_param(mode, charp, 0);
#endif /* endif */
MODULE_PARM_DESC(mac, "rt_wifi: wireless mac addr");
MODULE_PARM_DESC(mode, "rt_wifi: wireless operation mode");

/*---------------------------------------------------------------------*/
/* Prototypes of Functions Used					       */
/*---------------------------------------------------------------------*/

/* private function prototype */
INT rt28xx_send_packets(IN struct sk_buff *skb_p, IN struct net_device *net_dev);


struct net_device_stats *RT28xx_get_ether_stats(struct net_device *net_dev);

/*
========================================================================
Routine Description:
    Close raxx interface.

Arguments:
	*net_dev			the raxx interface pointer

Return Value:
    0					Open OK
	otherwise			Open Fail

Note:
	1. if open fail, kernel will not call the close function.
	2. Free memory for
		(1) Mlme Memory Handler:		MlmeHalt()
		(2) TX & RX:					RTMPFreeTxRxRingMemory()
		(3) BA Reordering:				ba_reordering_resource_release()
========================================================================
*/
int MainVirtualIF_close(IN struct net_device *net_dev)
{
	VOID *pAd = NULL;

	pAd = RTMP_OS_NETDEV_GET_PRIV(net_dev);

	if (pAd == NULL)
		return 0;

	netif_carrier_off(net_dev);
	netif_stop_queue(net_dev);

	RTMPInfClose(pAd);

	VIRTUAL_IF_DOWN(pAd);

	RT_MOD_DEC_USE_COUNT();

	return 0;		/* close ok */
}

/*
========================================================================
Routine Description:
    Open raxx interface.

Arguments:
	*net_dev			the raxx interface pointer

Return Value:
    0					Open OK
	otherwise			Open Fail

Note:
	1. if open fail, kernel will not call the close function.
	2. Free memory for
		(1) Mlme Memory Handler:		MlmeHalt()
		(2) TX & RX:					RTMPFreeTxRxRingMemory()
		(3) BA Reordering:				ba_reordering_resource_release()
========================================================================
*/
int MainVirtualIF_open(struct net_device *net_dev)
{
	VOID *pAd = NULL;

	GET_PAD_FROM_NET_DEV(pAd, net_dev);

	if (pAd == NULL)
		return 0;

#ifdef CONFIG_AP_SUPPORT
	/* pAd->ApCfg.MBSSID[MAIN_MBSSID].bBcnSntReq = TRUE; */
	RTMP_DRIVER_AP_MAIN_OPEN(pAd);
#endif /* CONFIG_AP_SUPPORT */

	if (VIRTUAL_IF_UP(pAd) != 0)
		return -1;

	RT_MOD_INC_USE_COUNT();

	netif_start_queue(net_dev);
	netif_carrier_on(net_dev);
	netif_wake_queue(net_dev);

	return 0;
}

/*
========================================================================
Routine Description:
    Close raxx interface.

Arguments:
	*net_dev			the raxx interface pointer

Return Value:
    0					Open OK
	otherwise			Open Fail

Note:
	1. if open fail, kernel will not call the close function.
	2. Free memory for
		(1) Mlme Memory Handler:		MlmeHalt()
		(2) TX & RX:					RTMPFreeTxRxRingMemory()
		(3) BA Reordering:				ba_reordering_resource_release()
========================================================================
*/
int rt28xx_close(VOID *dev)
{
	struct net_device *net_dev = (struct net_device *)dev;
	VOID *pAd = NULL;

	GET_PAD_FROM_NET_DEV(pAd, net_dev);

	DBGPRINT(RT_DEBUG_TRACE, ("===> rt28xx_close\n"));

	if (pAd == NULL)
		return 0;

	RTMPDrvClose(pAd, net_dev);

	DBGPRINT(RT_DEBUG_TRACE, ("<=== rt28xx_close\n"));
	return 0;
}

/*
========================================================================
Routine Description:
    Open raxx interface.

Arguments:
	*net_dev			the raxx interface pointer

Return Value:
    0					Open OK
	otherwise			Open Fail

Note:
========================================================================
*/
int rt28xx_open(VOID *dev)
{
	struct net_device *net_dev = (struct net_device *)dev;
	VOID *pAd = NULL;
	int retval = 0;
	ULONG OpMode;

#ifdef CONFIG_STA_SUPPORT
#ifdef CONFIG_PM
#ifdef USB_SUPPORT_SELECTIVE_SUSPEND
	struct usb_interface *intf;
	struct usb_device *pUsb_Dev;
	INT pm_usage_cnt;
#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
#endif /* CONFIG_PM */
#endif /* CONFIG_STA_SUPPORT */

	if (sizeof(ra_dma_addr_t) < sizeof(dma_addr_t))
		DBGPRINT(RT_DEBUG_ERROR, ("Fatal error for DMA address size!!!\n"));

	GET_PAD_FROM_NET_DEV(pAd, net_dev);
	if (pAd == NULL) {
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -1;
	}

	RTMP_DRIVER_MCU_SLEEP_CLEAR(pAd);

	RTMP_DRIVER_OP_MODE_GET(pAd, &OpMode);

#ifdef CONFIG_STA_SUPPORT
#ifdef CONFIG_PM
#ifdef USB_SUPPORT_SELECTIVE_SUSPEND

	RTMP_DRIVER_USB_DEV_GET(pAd, &pUsb_Dev);
	RTMP_DRIVER_USB_INTF_GET(pAd, &intf);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 32)
	pm_usage_cnt = atomic_read(&intf->pm_usage_cnt);
#else
	pm_usage_cnt = intf->pm_usage_cnt;
#endif /* endif */
	if (pm_usage_cnt == 0) {
		int res = 1;

		res = usb_autopm_get_interface(intf);
		if (res) {
			DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_open autopm_resume fail!\n"));
			return (-1);
		}
	}
#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
#endif /* CONFIG_PM */
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_WIRELESS_EXT
#if WIRELESS_EXT >= 12
	if (RTMP_DRIVER_MAIN_INF_CHECK(pAd, RT_DEV_PRIV_FLAGS_GET(net_dev)) == NDIS_STATUS_SUCCESS) {
#ifdef CONFIG_APSTA_MIXED_SUPPORT
		if (OpMode == OPMODE_AP)
			net_dev->wireless_handlers =
			    (struct iw_handler_def *)&rt28xx_ap_iw_handler_def;
#endif /* CONFIG_APSTA_MIXED_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
		if (OpMode == OPMODE_STA)
			net_dev->wireless_handlers =
			    (struct iw_handler_def *)&rt28xx_iw_handler_def;
#endif /* CONFIG_STA_SUPPORT */
	}
#endif /* WIRELESS_EXT >= 12 */
#endif /* CONFIG_WIRELESS_EXT */

	/*
	   Request interrupt service routine for PCI device
	   register the interrupt routine with the os

	   AP Channel auto-selection will be run in rt28xx_init(),
	   so we must reqister IRQ hander here.
	 */
	RtmpOSIRQRequest(net_dev);

	/* Init IRQ parameters stored in pAd */
/*	rtmp_irq_init(pAd); */
	RTMP_DRIVER_IRQ_INIT(pAd);

	/* Chip & other init */
	if (rt28xx_init(pAd, mac, hostname) == FALSE)
		goto err;

#ifdef MBSS_SUPPORT
	/*
	   the function can not be moved to RT2860_probe() even register_netdev()
	   is changed as register_netdevice().
	   Or in some PC, kernel will panic (Fedora 4)
	 */
#if defined(P2P_APCLI_SUPPORT) || defined(RT_CFG80211_P2P_SUPPORT)

#else
	RT28xx_MBSS_Init(pAd, net_dev);
#endif /* P2P_APCLI_SUPPORT */
#endif /* MBSS_SUPPORT */

#ifdef WDS_SUPPORT
	RT28xx_WDS_Init(pAd, net_dev);
#endif /* WDS_SUPPORT */

#ifdef APCLI_SUPPORT
#if defined(P2P_APCLI_SUPPORT) || defined(RT_CFG80211_P2P_CONCURRENT_DEVICE)
#else
	RT28xx_ApCli_Init(pAd, net_dev);
#endif /* P2P_APCLI_SUPPORT || RT_CFG80211_P2P_CONCURRENT_DEVICE */
#endif /* APCLI_SUPPORT */

#ifdef CONFIG_SNIFFER_SUPPORT
	RT28xx_Monitor_Init(pAd, net_dev);
#endif /* CONFIG_SNIFFER_SUPPORT */


#ifdef RT_CFG80211_SUPPORT
#ifdef RT_CFG80211_P2P_CONCURRENT_DEVICE
#ifdef CFG80211_STA_AP_CONCURRENT
	if (strcmp(net_dev->name, "ap0") != 0)
#endif
		RTMP_CFG80211_DummyP2pIf_Init(pAd);

#endif /* RT_CFG80211_P2P_CONCURRENT_DEVICE */
#ifdef RT_CFG80211_AP_SUPPORT
	RTMP_CFG80211_ApIf_Init(pAd);
#endif /* RT_CFG80211_AP_SUPPORT */
#else
#endif /* RT_CFG80211_SUPPORT */

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
	RTMP_DRIVER_CFG80211_START(pAd);
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */

	RTMPDrvOpen(pAd);

#ifdef VENDOR_FEATURE2_SUPPORT
	printk(KERN_DEBUG "Number of Packet Allocated in open = %lu\n", OS_NumOfPktAlloc);
	printk(KERN_DEBUG "Number of Packet Freed in open = %lu\n", OS_NumOfPktFree);
#endif /* VENDOR_FEATURE2_SUPPORT */

	return retval;

err:
	RTMP_DRIVER_IRQ_RELEASE(pAd);

	return (-1);
}

PNET_DEV RtmpPhyNetDevInit(VOID *pAd, RTMP_OS_NETDEV_OP_HOOK *pNetDevHook)
{
	struct net_device *net_dev = NULL;
	ULONG InfId, OpMode;

	RTMP_DRIVER_MAIN_INF_GET(pAd, &InfId);

/*	net_dev = RtmpOSNetDevCreate(pAd, INT_MAIN, 0, sizeof(struct mt_dev_priv), INF_MAIN_DEV_NAME); */
	RTMP_DRIVER_MAIN_INF_CREATE(pAd, &net_dev);
	if (net_dev == NULL) {
		printk(KERN_DEBUG "%s(): main physical net device creation failed!\n", __func__);
		return NULL;
	}

	NdisZeroMemory((unsigned char *)pNetDevHook, sizeof(RTMP_OS_NETDEV_OP_HOOK));
	pNetDevHook->open = MainVirtualIF_open;
	pNetDevHook->stop = MainVirtualIF_close;
	pNetDevHook->xmit = rt28xx_send_packets;
#ifdef IKANOS_VX_1X0
	pNetDevHook->xmit = IKANOS_DataFramesTx;
#endif /* IKANOS_VX_1X0 */
	pNetDevHook->ioctl = rt28xx_ioctl;
	pNetDevHook->priv_flags = InfId;	/*INT_MAIN; */
	pNetDevHook->get_stats = RT28xx_get_ether_stats;

	pNetDevHook->needProtcted = FALSE;

#if (WIRELESS_EXT < 21) && (WIRELESS_EXT >= 12)
	pNetDevHook->get_wstats = rt28xx_get_wireless_stats;
#endif /* endif */

	RTMP_DRIVER_OP_MODE_GET(pAd, &OpMode);

	/* put private data structure */
	RTMP_OS_NETDEV_SET_PRIV(net_dev, pAd);

#ifdef CONFIG_STA_SUPPORT
#if WIRELESS_EXT >= 12
	if (OpMode == OPMODE_STA)
		pNetDevHook->iw_handler = (void *)&rt28xx_iw_handler_def;
#endif /*WIRELESS_EXT >= 12 */
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_APSTA_MIXED_SUPPORT
#if WIRELESS_EXT >= 12
	if (OpMode == OPMODE_AP)
		pNetDevHook->iw_handler = &rt28xx_ap_iw_handler_def;
#endif /*WIRELESS_EXT >= 12 */
#endif /* CONFIG_APSTA_MIXED_SUPPORT */

	/* double-check if pAd is associated with the net_dev */
	if (RTMP_OS_NETDEV_GET_PRIV(net_dev) == NULL) {
		RtmpOSNetDevFree(net_dev);
		return NULL;
	}

	RTMP_DRIVER_NET_DEV_SET(pAd, net_dev);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
	SET_MODULE_OWNER(net_dev);
#endif /* endif */



	return net_dev;
}

VOID *RtmpNetEthConvertDevSearch(VOID *net_dev_, UCHAR *pData)
{
	struct net_device *pNetDev;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 26)
	struct net_device *net_dev = (struct net_device *)net_dev_;
	struct net *net;

	net = dev_net(net_dev);

	BUG_ON(!net);
	for_each_netdev(net, pNetDev)
#else
	struct net *net;

	struct net_device *net_dev = (struct net_device *)net_dev_;

	BUG_ON(!net_dev->nd_net);
	net = net_dev->nd_net;
	for_each_netdev(net, pNetDev)
#endif /* endif */
#else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 22)
	for_each_netdev(pNetDev)
#else
	for (pNetDev = dev_base; pNetDev; pNetDev = pNetDev->next)
#endif /* endif */
#endif /* endif */
		{
		if ((pNetDev->type == ARPHRD_ETHER)
			&& NdisEqualMemory(pNetDev->dev_addr, &pData[6], pNetDev->addr_len))
				break;
		}

	return (VOID *) pNetDev;
}


/*
========================================================================
Routine Description:
    The entry point for Linux kernel sent packet to our driver.

Arguments:
    sk_buff *skb	the pointer refer to a sk_buffer.

Return Value:
    0

Note:
	This function is the entry point of Tx Path for OS delivery packet to
	our driver. You only can put OS-depened & STA/AP common handle procedures
	in here.
========================================================================
*/
int rt28xx_packet_xmit(void *pkt)
{
	struct sk_buff *skb = (struct sk_buff *)pkt;
	struct net_device *net_dev = skb->dev;
	struct wifi_dev *wdev;
	PNDIS_PACKET pPacket = (PNDIS_PACKET) skb;

	wdev = RTMP_OS_NETDEV_GET_WDEV(net_dev);
	ASSERT(wdev);


	return RTMPSendPackets((NDIS_HANDLE) wdev, (PPNDIS_PACKET) & pPacket, 1,
			       skb->len, RtmpNetEthConvertDevSearch);
}

/*
========================================================================
Routine Description:
    Send a packet to WLAN.

Arguments:
    skb_p	    points to our adapter
    dev_p	    which WLAN network interface

Return Value:
    0: transmit successfully
    otherwise: transmit fail

Note:
========================================================================
*/
int rt28xx_send_packets(struct sk_buff *skb, struct net_device *ndev)
{
	MEM_DBG_PKT_ALLOC_INC(skb);
	if (!(RTMP_OS_NETDEV_STATE_RUNNING(ndev))) {
		RELEASE_NDIS_PACKET(NULL, (PNDIS_PACKET) skb, NDIS_STATUS_FAILURE);
		return 0;
	}

	NdisZeroMemory((PUCHAR) & skb->cb[CB_OFF], 26);

	return rt28xx_packet_xmit(skb);
}

#if WIRELESS_EXT >= 12
/* This function will be called when query /proc */
struct iw_statistics *rt28xx_get_wireless_stats(struct net_device *net_dev)
{
	VOID *pAd = NULL;
	struct iw_statistics *pStats;
	RT_CMD_IW_STATS DrvIwStats, *pDrvIwStats = &DrvIwStats;

	GET_PAD_FROM_NET_DEV(pAd, net_dev);

	DBGPRINT(RT_DEBUG_TRACE, ("rt28xx_get_wireless_stats --->\n"));

	pDrvIwStats->priv_flags = RT_DEV_PRIV_FLAGS_GET(net_dev);
	pDrvIwStats->dev_addr = (PUCHAR) net_dev->dev_addr;

	if (RTMP_DRIVER_IW_STATS_GET(pAd, pDrvIwStats) != NDIS_STATUS_SUCCESS)
		return NULL;

	pStats = (struct iw_statistics *)(pDrvIwStats->pStats);
	pStats->status = 0;	/* Status - device dependent for now */
	pStats->qual.updated = 1;	/* Flags to know if updated */
#ifdef IW_QUAL_DBM
	pStats->qual.updated |= IW_QUAL_DBM;	/* Level + Noise are dBm */
#endif /* IW_QUAL_DBM */
	pStats->qual.qual = pDrvIwStats->qual;
	pStats->qual.level = pDrvIwStats->level;
	pStats->qual.noise = pDrvIwStats->noise;
	pStats->discard.nwid = 0;	/* Rx : Wrong nwid/essid */
	pStats->miss.beacon = 0;	/* Missed beacons/superframe */

	DBGPRINT(RT_DEBUG_TRACE, ("<--- rt28xx_get_wireless_stats\n"));
	return pStats;
}
#endif /* WIRELESS_EXT */

INT rt28xx_ioctl(PNET_DEV net_dev, struct ifreq *rq, INT cmd)
{
	VOID *pAd = NULL;
	INT ret = 0;
	ULONG OpMode;

	GET_PAD_FROM_NET_DEV(pAd, net_dev);
	if (pAd == NULL) {
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	RTMP_DRIVER_OP_MODE_GET(pAd, &OpMode);

#ifdef CONFIG_AP_SUPPORT
/*	IF_DEV_CONFIG_OPMODE_ON_AP(pAd) */
	if (RT_CONFIG_IF_OPMODE_ON_AP(OpMode))
		ret = rt28xx_ap_ioctl(net_dev, rq, cmd);
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
/*	IF_DEV_CONFIG_OPMODE_ON_STA(pAd) */
	if (RT_CONFIG_IF_OPMODE_ON_STA(OpMode))
			ret = rt28xx_sta_ioctl(net_dev, rq, cmd);
#endif /* CONFIG_STA_SUPPORT */

	return ret;
}

/*
    ========================================================================

    Routine Description:
	return ethernet statistics counter

    Arguments:
	net_dev			    Pointer to net_device

    Return Value:
	net_device_stats*

    Note:

    ========================================================================
*/
struct net_device_stats *RT28xx_get_ether_stats(struct net_device *net_dev)
{
	VOID *pAd = NULL;
	struct net_device_stats *pStats;
	RT_CMD_STATS DrvStats, *pDrvStats = &DrvStats;

	if (net_dev)
		GET_PAD_FROM_NET_DEV(pAd, net_dev);

	if (!pAd)
		return NULL;

	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __func__));

	/* assign net device for RTMP_DRIVER_INF_STATS_GET() */
	pDrvStats->pNetDev = net_dev;
	RTMP_DRIVER_INF_STATS_GET(pAd, pDrvStats);

	pStats = (struct net_device_stats *)(pDrvStats->pStats);
	pStats->rx_packets = pDrvStats->rx_packets;
	pStats->tx_packets = pDrvStats->tx_packets;

	pStats->rx_bytes = pDrvStats->rx_bytes;
	pStats->tx_bytes = pDrvStats->tx_bytes;

	pStats->rx_errors = pDrvStats->rx_errors;
	pStats->tx_errors = pDrvStats->tx_errors;

	pStats->rx_dropped = 0;
	pStats->tx_dropped = 0;

	pStats->multicast = pDrvStats->multicast;
	pStats->collisions = pDrvStats->collisions;

	pStats->rx_length_errors = 0;
	pStats->rx_over_errors = pDrvStats->rx_over_errors;
	pStats->rx_crc_errors = 0;	/*pAd->WlanCounters.FCSErrorCount; rx with crc error */
	pStats->rx_frame_errors = pDrvStats->rx_frame_errors;
	pStats->rx_fifo_errors = pDrvStats->rx_fifo_errors;
	pStats->rx_missed_errors = 0;	/* receiver missed packet */

	/* detailed tx_errors */
	pStats->tx_aborted_errors = 0;
	pStats->tx_carrier_errors = 0;
	pStats->tx_fifo_errors = 0;
	pStats->tx_heartbeat_errors = 0;
	pStats->tx_window_errors = 0;

	/* for cslip etc */
	pStats->rx_compressed = 0;
	pStats->tx_compressed = 0;

	return pStats;
}

BOOLEAN RtmpPhyNetDevExit(VOID *pAd, PNET_DEV net_dev)
{

#ifdef CONFIG_AP_SUPPORT
#ifdef APCLI_SUPPORT
#if defined(P2P_APCLI_SUPPORT) || defined(RT_CFG80211_P2P_CONCURRENT_DEVICE)
#else
	/* remove all AP-client virtual interfaces. */
	RT28xx_ApCli_Remove(pAd);
#endif /* P2P_APCLI_SUPPORT  || RT_CFG80211_P2P_CONCURRENT_DEVICE */
#endif /* APCLI_SUPPORT */

#ifdef WDS_SUPPORT
	/* remove all WDS virtual interfaces. */
	RT28xx_WDS_Remove(pAd);
#endif /* WDS_SUPPORT */

#ifdef MBSS_SUPPORT
#if defined(P2P_APCLI_SUPPORT) || defined(RT_CFG80211_P2P_SUPPORT)

#else
	RT28xx_MBSS_Remove(pAd);
#endif /* P2P_APCLI_SUPPORT */
#endif /* MBSS_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_SNIFFER_SUPPORT
	RT28xx_Monitor_Remove(pAd);
#endif /* CONFIG_SNIFFER_SUPPORT */

#ifdef RT_CFG80211_SUPPORT
#ifdef RT_CFG80211_AP_SUPPORT
	RTMP_CFG80211_ApIf_Remove(pAd);
#endif

#ifdef RT_CFG80211_P2P_CONCURRENT_DEVICE
#ifndef RT_CFG80211_P2P_STATIC_CONCURRENT_DEVICE
	RTMP_CFG80211_AllVirtualIF_Remove(pAd);
#endif /* RT_CFG80211_P2P_STATIC_CONCURRENT_DEVICE */
	RTMP_CFG80211_DummyP2pIf_Remove(pAd);
#endif /* RT_CFG80211_P2P_CONCURRENT_DEVICE */

#else
#endif /* RT_CFG80211_SUPPORT */

#ifdef INF_PPA_SUPPORT
	RTMP_DRIVER_INF_PPA_EXIT(pAd);
#endif /* INF_PPA_SUPPORT */

#ifdef CFG80211_STA_AP_CONCURRENT
	RTMP_CFG80211_MultiApIf_Remove(pAd);
#endif /* CFG80211_STA_AP_CONCURRENT */

	/* Unregister network device */
	if (net_dev != NULL) {
		printk(KERN_DEBUG "RtmpOSNetDevDetach(): RtmpOSNetDeviceDetach(), dev->name=%s!\n",
		       net_dev->name);
		RtmpOSNetDevProtect(1);
		RtmpOSNetDevDetach(net_dev);
		RtmpOSNetDevProtect(0);
	}

	return TRUE;

}

/*******************************************************************************

	Device IRQ related functions.

 *******************************************************************************/
int RtmpOSIRQRequest(IN PNET_DEV net_dev)
{
	ULONG infType;
	VOID *pAd = NULL;
	int retval = 0;

	GET_PAD_FROM_NET_DEV(pAd, net_dev);

	ASSERT(pAd);

	RTMP_DRIVER_INF_TYPE_GET(pAd, &infType);



	return retval;
}

#ifdef WDS_SUPPORT
/*
    ========================================================================

    Routine Description:
	return ethernet statistics counter

    Arguments:
	net_dev			    Pointer to net_device

    Return Value:
	net_device_stats*

    Note:

    ========================================================================
*/
struct net_device_stats *RT28xx_get_wds_ether_stats(IN PNET_DEV net_dev)
{
	VOID *pAd = NULL;
/*	INT WDS_apidx = 0,index; */
	struct net_device_stats *pStats;
	RT_CMD_STATS WdsStats, *pWdsStats = &WdsStats;

	if (net_dev)
		GET_PAD_FROM_NET_DEV(pAd, net_dev);

/*	if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_WDS) */
	{
		if (pAd) {
			pWdsStats->pNetDev = net_dev;
			if (RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_WDS_STATS_GET,
						 0, pWdsStats,
						 RT_DEV_PRIV_FLAGS_GET(net_dev)) !=
			    NDIS_STATUS_SUCCESS)
				return NULL;

			pStats = (struct net_device_stats *)pWdsStats->pStats;	/*pAd->stats; */

		/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.ReceivedFragmentCount.QuadPart; */
			pStats->rx_packets = pWdsStats->rx_packets;
		/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.TransmittedFragmentCount.QuadPart; */
			pStats->tx_packets = pWdsStats->tx_packets;

			/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.ReceivedByteCount; */
			pStats->rx_bytes = pWdsStats->rx_bytes;
			/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.TransmittedByteCount; */
			pStats->tx_bytes = pWdsStats->tx_bytes;

			/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.RxErrors; */
			pStats->rx_errors = pWdsStats->rx_errors;
			/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.TxErrors; */
			pStats->tx_errors = pWdsStats->tx_errors;

			pStats->rx_dropped = 0;
			pStats->tx_dropped = 0;

		/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.MulticastReceivedFrameCount.QuadPart;
			* multicast packets received
			*/
			pStats->multicast = pWdsStats->multicast;
			pStats->collisions = pWdsStats->collisions;	/* Collision packets */

			pStats->rx_length_errors = 0;
			/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.RxNoBuffer;
			*receiver ring buff overflow
			*/
			pStats->rx_over_errors = pWdsStats->rx_over_errors;
			/*pAd->WlanCounters.FCSErrorCount;     // recved pkt with crc error */
			pStats->rx_crc_errors = 0;
			pStats->rx_frame_errors = 0;	/* recv'd frame alignment error */
			/*pAd->WdsTab.WdsEntry[WDS_apidx].WdsCounter.RxNoBuffer;
			* recv'r fifo overrun
			*/
			pStats->rx_fifo_errors = pWdsStats->rx_fifo_errors;
			pStats->rx_missed_errors = 0;	/* receiver missed packet */

			/* detailed tx_errors */
			pStats->tx_aborted_errors = 0;
			pStats->tx_carrier_errors = 0;
			pStats->tx_fifo_errors = 0;
			pStats->tx_heartbeat_errors = 0;
			pStats->tx_window_errors = 0;

			/* for cslip etc */
			pStats->rx_compressed = 0;
			pStats->tx_compressed = 0;

			return pStats;
		} else
			return NULL;
	}
/*	else */
/*		return NULL; */
}
#endif /* WDS_SUPPORT */
