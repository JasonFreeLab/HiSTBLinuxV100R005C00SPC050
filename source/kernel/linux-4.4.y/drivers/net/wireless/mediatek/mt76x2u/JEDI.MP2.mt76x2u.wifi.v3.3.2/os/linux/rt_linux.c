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

/****************************************************************************

    Module Name:
    UTIL/rt_linux.c

    Abstract:
	All functions provided from OS module are put here.

	Note:
	1. Can not use sizeof() for a structure with any parameter included
	by any compile option, such as RTMP_ADAPTER.

	Because the RTMP_ADAPTER size in the UTIL module is different with
	DRIVER/NETIF.

	2. Do not use any structure with any parameter included by PCI/USB/RBUS/
	AP/STA.

	Because the structure size in the UTIL module is different with
	DRIVER/NETIF.

	3. Do not use any structure defined in DRIVER module, EX: pAd.
	So we can do module partition.

	Revision History:
	Who	   When		 What
	---------  ----------	 -------------------------------------------

***************************************************************************/

#define RTMP_MODULE_OS
#define RTMP_MODULE_OS_UTIL

#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "dot11i_wpa.h"
#include <linux/rtnetlink.h>
#include <linux/freezer.h>


#if defined(CONFIG_RA_HW_NAT) || defined(CONFIG_RA_HW_NAT_MODULE)
#include "../../../../../../net/nat/hw_nat/ra_nat.h"
#include "../../../../../../net/nat/hw_nat/frame_engine.h"
#endif /* endif */

#include <linux/kallsyms.h>

/* TODO */
#undef RT_CONFIG_IF_OPMODE_ON_AP
#undef RT_CONFIG_IF_OPMODE_ON_STA

#if defined(CONFIG_AP_SUPPORT) && defined(CONFIG_STA_SUPPORT)
#define RT_CONFIG_IF_OPMODE_ON_AP(__OpMode)	(__OpMode == OPMODE_AP)
#define RT_CONFIG_IF_OPMODE_ON_STA(__OpMode)	(__OpMode == OPMODE_STA)
#else
#define RT_CONFIG_IF_OPMODE_ON_AP(__OpMode)
#define RT_CONFIG_IF_OPMODE_ON_STA(__OpMode)	(__OpMode == OPMODE_STA)
#endif /* endif */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 3)
static inline void *netdev_priv(struct net_device *dev)
{
	return dev->priv;
}
#endif /* endif */

/*
	Used for backward compatible with previous linux version which
	used "net_device->priv" as device driver structure hooking point
*/
static inline void netdev_priv_set(struct net_device *dev, void *priv)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 3)
	dev->priv = priv;
#endif /* endif */
}

ULONG RTDebugLevel = RT_DEBUG_OFF;
ULONG RTDebugFunc = 0;


#ifdef VENDOR_FEATURE4_SUPPORT
ULONG OS_NumOfMemAlloc = 0, OS_NumOfMemFree = 0;
#endif /* VENDOR_FEATURE4_SUPPORT */
#ifdef VENDOR_FEATURE2_SUPPORT
ULONG OS_NumOfPktAlloc = 0, OS_NumOfPktFree = 0;
#endif /* VENDOR_FEATURE2_SUPPORT */

/*
 * the lock will not be used in TX/RX
 * path so throughput should not be impacted
 */
BOOLEAN FlgIsUtilInit = FALSE;
OS_NDIS_SPIN_LOCK UtilSemLock;

BOOLEAN RTMP_OS_Alloc_RscOnly(VOID *pRscSrc, UINT32 RscLen);
BOOLEAN RTMP_OS_Remove_Rsc(LIST_HEADER *pRscList, VOID *pRscSrc);

/*
========================================================================
Routine Description:
	Initialize something in UTIL module.

Arguments:
	None

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpUtilInit(VOID)
{
	if (FlgIsUtilInit == FALSE) {
		OS_NdisAllocateSpinLock(&UtilSemLock);
		FlgIsUtilInit = TRUE;
	}
}

/* timeout -- ms */
static inline VOID __RTMP_SetPeriodicTimer(IN OS_NDIS_MINIPORT_TIMER * pTimer,
					   IN unsigned long timeout)
{
	timeout = ((timeout * OS_HZ) / 1000);
	pTimer->expires = jiffies + timeout;
	add_timer(pTimer);
}

/* convert NdisMInitializeTimer --> RTMP_OS_Init_Timer */
static inline VOID __RTMP_OS_Init_Timer(IN VOID *pReserved,
					IN OS_NDIS_MINIPORT_TIMER * pTimer,
					IN TIMER_FUNCTION function, IN PVOID data)
{
	if (!timer_pending(pTimer)) {
		init_timer(pTimer);
		pTimer->data = (unsigned long)data;
		pTimer->function = function;
	}
}

static inline VOID __RTMP_OS_Add_Timer(IN OS_NDIS_MINIPORT_TIMER * pTimer, IN unsigned long timeout)
{
	if (timer_pending(pTimer))
		return;

	timeout = ((timeout * OS_HZ) / 1000);
	pTimer->expires = jiffies + timeout;
	add_timer(pTimer);
}

static inline VOID __RTMP_OS_Mod_Timer(IN OS_NDIS_MINIPORT_TIMER * pTimer, IN unsigned long timeout)
{
	timeout = ((timeout * OS_HZ) / 1000);
	mod_timer(pTimer, jiffies + timeout);
}

static inline VOID __RTMP_OS_Del_Timer(IN OS_NDIS_MINIPORT_TIMER * pTimer, OUT BOOLEAN *pCancelled)
{
	if (timer_pending(pTimer))
		*pCancelled = del_timer_sync(pTimer);
	else
		*pCancelled = TRUE;
}

static inline VOID __RTMP_OS_Release_Timer(IN OS_NDIS_MINIPORT_TIMER * pTimer)
{
	/* nothing to do */
}


/* Unify all delay routine by using udelay */
VOID RtmpusecDelay(ULONG usec)
{
	ULONG i;

	for (i = 0; i < (usec / 50); i++)
		udelay(50);

	if (usec % 50)
		udelay(usec % 50);
}

VOID RtmpOsMsDelay(ULONG msec)
{
	mdelay(msec);
}

void RTMP_GetCurrentSystemTime(LARGE_INTEGER *time)
{
	time->u.LowPart = jiffies;
}

void RTMP_GetCurrentSystemTick(ULONG *pNow)
{
	*pNow = jiffies;
}

ULONG RTMPMsecsToJiffies(UINT32 m)
{

	return msecs_to_jiffies(m);
}

/* pAd MUST allow to be NULL */

NDIS_STATUS os_alloc_mem(VOID *pReserved, UCHAR **mem, ULONG size)
{
	*mem = (PUCHAR) kmalloc(size, GFP_ATOMIC);
	if (*mem) {
#ifdef VENDOR_FEATURE4_SUPPORT
		OS_NumOfMemAlloc++;
#endif/* VENDOR_FEATURE4_SUPPORT */
		return NDIS_STATUS_SUCCESS;
	} else
		return NDIS_STATUS_FAILURE;
}

NDIS_STATUS os_alloc_mem_suspend(VOID *pReserved, UCHAR **mem, ULONG size)
{
	*mem = (PUCHAR) kmalloc(size, GFP_KERNEL);
	if (*mem) {
#ifdef VENDOR_FEATURE4_SUPPORT
		OS_NumOfMemAlloc++;
#endif/* VENDOR_FEATURE4_SUPPORT */
		return NDIS_STATUS_SUCCESS;
	} else
		return NDIS_STATUS_FAILURE;
}

/* pAd MUST allow to be NULL */
NDIS_STATUS os_free_mem(VOID *pReserved, PVOID mem)
{
	ASSERT(mem);
	kfree(mem);

#ifdef VENDOR_FEATURE4_SUPPORT
	OS_NumOfMemFree++;
#endif/* VENDOR_FEATURE4_SUPPORT */
	return NDIS_STATUS_SUCCESS;
}

NDIS_STATUS os_alloc_vmem(VOID *pReserved, UCHAR **mem, ULONG size)
{
	*mem = (PUCHAR) vmalloc(size);
	if (*mem)
		return NDIS_STATUS_SUCCESS;
	else
		return NDIS_STATUS_FAILURE;
}

NDIS_STATUS os_free_vmem(VOID *pReserved, PVOID mem)
{
	ASSERT(mem);
	vfree(mem);
	return NDIS_STATUS_SUCCESS;
}

#if defined(RTMP_RBUS_SUPPORT) || defined(RTMP_FLASH_SUPPORT)
/* The flag "CONFIG_RALINK_FLASH_API" is used for APSoC Linux SDK */
#ifdef CONFIG_RALINK_FLASH_API

int32_t FlashRead(uint32_t *dst, uint32_t *src, uint32_t count);

int32_t FlashWrite(uint16_t *source, uint16_t *destination, uint32_t numBytes);
#else /* CONFIG_RALINK_FLASH_API */

#ifdef RA_MTD_RW_BY_NUM
#if defined(CONFIG_RT2880_FLASH_32M)
#define MTD_NUM_FACTORY 5
#else
#define MTD_NUM_FACTORY 2
#endif /* endif */
extern int ra_mtd_write(int num, loff_t to, size_t len, const u_char *buf);
extern int ra_mtd_read(int num, loff_t from, size_t len, u_char *buf);
#else
extern int ra_mtd_write_nm(char *name, loff_t to, size_t len, const u_char *buf);
extern int ra_mtd_read_nm(char *name, loff_t from, size_t len, u_char *buf);
#endif /* endif */

#endif /* CONFIG_RALINK_FLASH_API */

void RtmpFlashRead(UCHAR *p, ULONG a, ULONG b)
{
#ifdef CONFIG_RALINK_FLASH_API
	FlashRead((uint32_t *) p, (uint32_t *) a, (uint32_t) b);
#else
#ifdef RA_MTD_RW_BY_NUM
	ra_mtd_read(MTD_NUM_FACTORY, 0, (size_t) b, p);
#else
	ra_mtd_read_nm("Factory", a & 0xFFFF, (size_t) b, p);
#endif /* endif */
#endif /* CONFIG_RALINK_FLASH_API */
}

void RtmpFlashWrite(UCHAR *p, ULONG a, ULONG b)
{
#ifdef CONFIG_RALINK_FLASH_API
	FlashWrite((uint16_t *) p, (uint16_t *) a, (uint32_t) b);
#else
#ifdef RA_MTD_RW_BY_NUM
	ra_mtd_write(MTD_NUM_FACTORY, 0, (size_t) b, p);
#else
	ra_mtd_write_nm("Factory", a & 0xFFFF, (size_t) b, p);
#endif /* endif */
#endif /* CONFIG_RALINK_FLASH_API */
}
#endif /* defined(RTMP_RBUS_SUPPORT) || defined(RTMP_FLASH_SUPPORT) */

PNDIS_PACKET RtmpOSNetPktAlloc(VOID *dummy, int size)
{
	struct sk_buff *skb;
	/* Add 2 more bytes for ip header alignment */
	skb = dev_alloc_skb(size + 2);
	if (skb != NULL)
		MEM_DBG_PKT_ALLOC_INC(skb);

	return ((PNDIS_PACKET) skb);
}

PNDIS_PACKET RTMP_AllocateFragPacketBuffer(VOID *dummy, ULONG len)
{
	struct sk_buff *pkt;

	pkt = dev_alloc_skb(len);

	if (pkt == NULL)
		DBGPRINT(RT_DEBUG_ERROR, ("can't allocate frag rx %ld size packet\n", len));

	if (pkt)
		MEM_DBG_PKT_ALLOC_INC(pkt);

	return (PNDIS_PACKET) pkt;
}

/*
	The allocated NDIS PACKET must be freed via RTMPFreeNdisPacket()
*/
NDIS_STATUS RTMPAllocateNdisPacket(IN VOID *pReserved,
				   OUT PNDIS_PACKET *ppPacket,
				   IN UCHAR *pHeader,
				   IN UINT HeaderLen, IN UCHAR *pData, IN UINT DataLen)
{
	struct sk_buff *pPacket;

	ASSERT(pData);
	ASSERT(DataLen);

	/* Add LEN_CCMP_HDR + LEN_CCMP_MIC for PMF */
	pPacket =
	    dev_alloc_skb(HeaderLen + DataLen + RTMP_PKT_TAIL_PADDING + LEN_CCMP_HDR +
			  LEN_CCMP_MIC);
	if (pPacket == NULL) {
		*ppPacket = NULL;
#ifdef DEBUG
		printk(KERN_ERR "RTMPAllocateNdisPacket Fail\n\n");
#endif /* endif */
		return NDIS_STATUS_FAILURE;
	}
	MEM_DBG_PKT_ALLOC_INC(pPacket);

	/* Clone the frame content and update the length of packet */
	if (HeaderLen > 0)
		NdisMoveMemory(pPacket->data, pHeader, HeaderLen);
	if (DataLen > 0)
		NdisMoveMemory(pPacket->data + HeaderLen, pData, DataLen);
	skb_put(pPacket, HeaderLen + DataLen);
/* printk(KERN_ERR "%s : pPacket = %p, len = %d\n", __FUNCTION__, pPacket, GET_OS_PKT_LEN(pPacket));*/

	*ppPacket = (PNDIS_PACKET) pPacket;

	return NDIS_STATUS_SUCCESS;
}

/*
  ========================================================================
  Description:
	This routine frees a miniport internally allocated NDIS_PACKET and its
	corresponding NDIS_BUFFER and allocated memory.
  ========================================================================
*/
VOID RTMPFreeNdisPacket(VOID *pReserved, PNDIS_PACKET pPacket)
{
	dev_kfree_skb_any(RTPKT_TO_OSPKT(pPacket));
	MEM_DBG_PKT_FREE_INC(pPacket);
}

void RTMP_QueryPacketInfo(IN PNDIS_PACKET pPacket,
			  OUT PACKET_INFO * info, OUT UCHAR **pSrcBufVA, OUT UINT * pSrcBufLen)
{
	info->BufferCount = 1;
	info->pFirstBuffer = (PNDIS_BUFFER) GET_OS_PKT_DATAPTR(pPacket);
	info->PhysicalBufferCount = 1;
	info->TotalPacketLength = GET_OS_PKT_LEN(pPacket);

	*pSrcBufVA = GET_OS_PKT_DATAPTR(pPacket);
	*pSrcBufLen = GET_OS_PKT_LEN(pPacket);

#ifdef TX_PKT_SG
	if (RTMP_GET_PKT_SG(pPacket)) {
		struct sk_buff *skb = (struct sk_buff *)pPacket;
		int i, nr_frags = skb_shinfo(skb)->nr_frags;

		info->BufferCount = nr_frags + 1;
		info->PhysicalBufferCount = info->BufferCount;
		info->sg_list[0].data = (VOID *) GET_OS_PKT_DATAPTR(pPacket);
		info->sg_list[0].len = skb_headlen(skb);
		for (i = 0; i < nr_frags; i++) {
			skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			info->sg_list[i + 1].data = ((void *)page_address(frag->page) +
						     frag->page_offset);
			info->sg_list[i + 1].len = frag->size;
		}
	}
#endif /* TX_PKT_SG */
}


PNDIS_PACKET DuplicatePacket(IN PNET_DEV pNetDev, IN PNDIS_PACKET pPacket, IN UCHAR FromWhichBSSID)
{
	struct sk_buff *skb;
	PNDIS_PACKET pRetPacket = NULL;
	USHORT DataSize;
	UCHAR *pData;

	DataSize = (USHORT) GET_OS_PKT_LEN(pPacket);
	pData = (PUCHAR) GET_OS_PKT_DATAPTR(pPacket);

	skb = skb_clone(RTPKT_TO_OSPKT(pPacket), MEM_ALLOC_FLAG);
	if (skb) {
		MEM_DBG_PKT_ALLOC_INC(skb);
		skb->dev = pNetDev;
		pRetPacket = OSPKT_TO_RTPKT(skb);
	}

	return pRetPacket;

}

PNDIS_PACKET duplicate_pkt(IN PNET_DEV pNetDev,
			   IN PUCHAR pHeader802_3,
			   IN UINT HdrLen,
			   IN PUCHAR pData, IN ULONG DataSize, IN UCHAR FromWhichBSSID)
{
	struct sk_buff *skb;
	PNDIS_PACKET pPacket = NULL;

	skb = __dev_alloc_skb(HdrLen + DataSize + 2, MEM_ALLOC_FLAG);
	if (skb != NULL) {
		MEM_DBG_PKT_ALLOC_INC(skb);

		skb_reserve(skb, 2);
		memcpy(skb_put(skb, HdrLen), pHeader802_3, HdrLen);
		memcpy(skb_put(skb, DataSize), pData, DataSize);
		skb->dev = pNetDev;
		pPacket = OSPKT_TO_RTPKT(skb);
	}

	return pPacket;
}

#define TKIP_TX_MIC_SIZE		8
PNDIS_PACKET duplicate_pkt_with_TKIP_MIC(VOID *pReserved, PNDIS_PACKET pPacket)
{
	struct sk_buff *skb, *newskb;

	skb = RTPKT_TO_OSPKT(pPacket);
	if (skb_tailroom(skb) < TKIP_TX_MIC_SIZE) {
		/* alloc a new skb and copy the packet */
		newskb = skb_copy_expand(skb, skb_headroom(skb), TKIP_TX_MIC_SIZE, GFP_ATOMIC);

		dev_kfree_skb_any(skb);
		MEM_DBG_PKT_FREE_INC(skb);

		if (newskb == NULL) {
			DBGPRINT(RT_DEBUG_ERROR,
				 ("Extend Tx.MIC for packet failed!, dropping packet!\n"));
			return NULL;
		}
		skb = newskb;
		MEM_DBG_PKT_ALLOC_INC(skb);
	}

	return OSPKT_TO_RTPKT(skb);


}

#ifdef CONFIG_AP_SUPPORT
PNDIS_PACKET duplicate_pkt_with_VLAN(IN PNET_DEV pNetDev,
				     IN USHORT VLAN_VID,
				     IN USHORT VLAN_Priority,
				     IN PUCHAR pHeader802_3,
				     IN UINT HdrLen,
				     IN PUCHAR pData,
				     IN ULONG DataSize, IN UCHAR FromWhichBSSID, IN UCHAR *TPID)
{
	struct sk_buff *skb;
	PNDIS_PACKET pPacket = NULL;
	UINT16 VLAN_Size;

	skb = __dev_alloc_skb(HdrLen + DataSize + LENGTH_802_1Q + 2, MEM_ALLOC_FLAG);
	if (skb != NULL) {
		MEM_DBG_PKT_ALLOC_INC(skb);

		skb_reserve(skb, 2);

		/* copy header (maybe +VLAN tag) */
		VLAN_Size = VLAN_8023_Header_Copy(VLAN_VID, VLAN_Priority,
						  pHeader802_3, HdrLen,
						  skb_tail_pointer(skb), FromWhichBSSID, TPID);
		skb_put(skb, HdrLen + VLAN_Size);

		/* copy data body */
		memcpy(skb_put(skb, DataSize), pData, DataSize);
		skb->dev = pNetDev;	/*get_netdev_from_bssid(pAd, FromWhichBSSID); */
		pPacket = OSPKT_TO_RTPKT(skb);
	}

	return pPacket;
}
#endif /* CONFIG_AP_SUPPORT */

/*
	========================================================================

	Routine Description:
		Send a L2 frame to upper daemon to trigger state machine

	Arguments:
		pAd - pointer to our pAdapter context

	Return Value:

	Note:

	========================================================================
*/
BOOLEAN RTMPL2FrameTxAction(IN VOID *pCtrlBkPtr,
			    IN PNET_DEV pNetDev,
			    IN RTMP_CB_8023_PACKET_ANNOUNCE _announce_802_3_packet,
			    IN UCHAR apidx, IN UCHAR *pData, IN UINT32 data_len, IN UCHAR OpMode)
{
	struct sk_buff *skb = dev_alloc_skb(data_len + 2);

	if (!skb) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s : Error! Can't allocate a skb.\n", __func__));
		return FALSE;
	}

	MEM_DBG_PKT_ALLOC_INC(skb);
	SET_OS_PKT_NETDEV(skb, pNetDev);

	/* 16 byte align the IP header */
	skb_reserve(skb, 2);

	/* Insert the frame content */
	NdisMoveMemory(GET_OS_PKT_DATAPTR(skb), pData, data_len);

	/* End this frame */
	skb_put(GET_OS_PKT_TYPE(skb), data_len);

	DBGPRINT(RT_DEBUG_TRACE, ("%s doen\n", __func__));

	_announce_802_3_packet(pCtrlBkPtr, skb, OpMode);

	return TRUE;

}

PNDIS_PACKET ExpandPacket(IN VOID *pReserved,
			  IN PNDIS_PACKET pPacket, IN UINT32 ext_head_len, IN UINT32 ext_tail_len)
{
	struct sk_buff *skb, *newskb;

	skb = RTPKT_TO_OSPKT(pPacket);
	if (skb_cloned(skb) || (skb_headroom(skb) < ext_head_len)
	    || (skb_tailroom(skb) < ext_tail_len)) {
		UINT32 head_len =
		    (skb_headroom(skb) < ext_head_len) ? ext_head_len : skb_headroom(skb);
		UINT32 tail_len =
		    (skb_tailroom(skb) < ext_tail_len) ? ext_tail_len : skb_tailroom(skb);

		/* alloc a new skb and copy the packet */
		newskb = skb_copy_expand(skb, head_len, tail_len, GFP_ATOMIC);

		dev_kfree_skb_any(skb);
		MEM_DBG_PKT_FREE_INC(skb);

		if (newskb == NULL) {
			DBGPRINT(RT_DEBUG_ERROR,
				 ("Extend Tx buffer for WPI failed!, dropping packet!\n"));
			return NULL;
		}
		skb = newskb;
		MEM_DBG_PKT_ALLOC_INC(skb);
	}

	return OSPKT_TO_RTPKT(skb);

}

PNDIS_PACKET ClonePacket(IN VOID *pReserved,
			 IN PNDIS_PACKET pPacket, IN PUCHAR pData, IN ULONG DataSize)
{
	struct sk_buff *pRxPkt;
	struct sk_buff *pClonedPkt;

	ASSERT(pPacket);
	pRxPkt = RTPKT_TO_OSPKT(pPacket);

	/* clone the packet */
	pClonedPkt = skb_clone(pRxPkt, MEM_ALLOC_FLAG);

	if (pClonedPkt) {
		/* set the correct dataptr and data len */
		MEM_DBG_PKT_ALLOC_INC(pClonedPkt);
		SET_OS_PKT_NETDEV(pClonedPkt, pRxPkt->dev);
		SET_OS_PKT_DATAPTR(pClonedPkt, pData);
		SET_OS_PKT_LEN(pClonedPkt, DataSize);
		SET_OS_PKT_DATATAIL(pClonedPkt, pData, DataSize);
		ASSERT(DataSize < 1530);
	}
	return pClonedPkt;
}

VOID RtmpOsPktInit(IN PNDIS_PACKET pNetPkt,
		   IN PNET_DEV pNetDev, IN UCHAR *pData, IN USHORT DataSize)
{
	PNDIS_PACKET pRxPkt;

	pRxPkt = RTPKT_TO_OSPKT(pNetPkt);

	SET_OS_PKT_NETDEV(pRxPkt, pNetDev);
	SET_OS_PKT_DATAPTR(pRxPkt, pData);
	SET_OS_PKT_LEN(pRxPkt, DataSize);
	SET_OS_PKT_DATATAIL(pRxPkt, pData, DataSize);
}

void wlan_802_11_to_802_3_packet(IN PNET_DEV pNetDev,
				 IN UCHAR OpMode,
				 IN USHORT VLAN_VID,
				 IN USHORT VLAN_Priority,
				 IN PNDIS_PACKET pRxPacket,
				 IN UCHAR *pData,
				 IN ULONG DataSize,
				 IN PUCHAR pHeader802_3, IN UCHAR FromWhichBSSID, IN UCHAR *TPID)
{
	struct sk_buff *pOSPkt;

	ASSERT(pHeader802_3);

	pOSPkt = RTPKT_TO_OSPKT(pRxPacket);

	SET_OS_PKT_NETDEV(pOSPkt, pNetDev);
	SET_OS_PKT_DATAPTR(pOSPkt, pData);
	SET_OS_PKT_LEN(pOSPkt, DataSize);
	SET_OS_PKT_DATATAIL(pOSPkt, pData, DataSize);

	/* copy 802.3 header */
#ifdef CONFIG_AP_SUPPORT
	if (RT_CONFIG_IF_OPMODE_ON_AP(OpMode)) {
		/* maybe insert VLAN tag to the received packet */
		UCHAR VLAN_Size = 0;
		UCHAR *data_p;

		if (VLAN_VID != 0)
			VLAN_Size = LENGTH_802_1Q;

		data_p = skb_push(pOSPkt, LENGTH_802_3 + VLAN_Size);

		VLAN_8023_Header_Copy(VLAN_VID, VLAN_Priority,
				      pHeader802_3, LENGTH_802_3, data_p, FromWhichBSSID, TPID);
	}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	if (RT_CONFIG_IF_OPMODE_ON_STA(OpMode))
		NdisMoveMemory(skb_push(pOSPkt, LENGTH_802_3), pHeader802_3, LENGTH_802_3);
#endif /* CONFIG_STA_SUPPORT */

}
#ifdef WOW_BUF_PKT_SUPPORT
/*
	FW will buffer the waking up packet (ex. magic packet or TCP/UDP packet),
	and driver get it from FW event and pass it to OS directly.
*/
void RtmpOsBufPktRcvHandle(PNET_DEV pNetDev, PUCHAR pRxRspEvtPayload, UINT32 PktLen)
{
	int i;
	const int FrameControlLen = 2;
	const int DurationLen = 2;
	const int LLCLen = 8;
	UCHAR Header802_3[LENGTH_802_3];
	PUCHAR A1, A2, A3, ptr;
	PUCHAR pPayload = 0;
	PUCHAR pEthType = 0;
	const int EthTypeLen = 2;
	UCHAR SNAP_identifier[2] = {0xaa, 0xaa};
	const int SNAPLen = 2;
	UINT32 PayloadLen = 0;
	struct sk_buff *pRxPkt = NULL;

	DBGPRINT(RT_DEBUG_TRACE, ("[bufPkt] pRxRspEvtPayload:%p %d\n", pRxRspEvtPayload, PktLen));
	DBGPRINT(RT_DEBUG_TRACE, ("RAW data:\n"));
	for (i = 0; i < PktLen; i++)
		DBGPRINT(RT_DEBUG_TRACE, ("%02x%s",
		pRxRspEvtPayload[i], (i+1)%16 == 0 ? "\n":" "));
	DBGPRINT(RT_DEBUG_TRACE, ("len:%d\n", i));

	/* Parsing 80211 header */
	A1 = &pRxRspEvtPayload[FrameControlLen+DurationLen];
	A2 = A1 + MAC_ADDR_LEN;
	A3 = A2 + MAC_ADDR_LEN;

	DBGPRINT(RT_DEBUG_TRACE, ("[bufPkt] A1=%02x:%02x:%02x:%02x:%02x:%02x\n", PRINT_MAC(A1)));
	DBGPRINT(RT_DEBUG_TRACE, ("[bufPkt] A2=%02x:%02x:%02x:%02x:%02x:%02x\n", PRINT_MAC(A2)));
	DBGPRINT(RT_DEBUG_TRACE, ("[bufPkt] A3=%02x:%02x:%02x:%02x:%02x:%02x\n", PRINT_MAC(A3)));

	/* Get data payload */
	for (i = LENGTH_802_11; i <= LENGTH_802_11_WITH_ADDR4; i++) {
		if (RTMPEqualMemory(&pRxRspEvtPayload[i], &SNAP_identifier, SNAPLen)) {
			pPayload = &pRxRspEvtPayload[i + LLCLen];
			PayloadLen = PktLen - (i + LLCLen);
			pEthType = pPayload - EthTypeLen;
			DBGPRINT(RT_DEBUG_TRACE, ("[bufPkt] Payload idx(%d):%p\n",
				i+LLCLen, pPayload));
			break;
		}
	}
	if (PayloadLen == 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("[bufPkt] Parsing error and drop buffered packet!\n"));
		return;
	}
	DBGPRINT(RT_DEBUG_TRACE, ("[bufPkt] pRxRspEvtPayload:%p PayloadLen(%d)\n",
		pRxRspEvtPayload, PayloadLen));
	pRxPkt = dev_alloc_skb(PayloadLen + 2);
	if (!pRxPkt) {
		DBGPRINT(RT_DEBUG_ERROR, ("low on mem - packet dropped\n"));
		return;
	}
	skb_put(pRxPkt, PayloadLen);
	pRxPkt->dev = pNetDev;

	/* Copy data payload and mac header to skb */
	NdisCopyMemory(pRxPkt->data, pPayload, PayloadLen);
	NdisCopyMemory(Header802_3, A1, MAC_ADDR_LEN);
	NdisCopyMemory(Header802_3 + MAC_ADDR_LEN, A3, MAC_ADDR_LEN);
	NdisCopyMemory(Header802_3 + MAC_ADDR_LEN * 2, pEthType, 2);
	NdisCopyMemory(skb_push(pRxPkt, LENGTH_802_3), Header802_3, LENGTH_802_3);

	RtmpOsPktProtocolAssign(pRxPkt);

	DBGPRINT(RT_DEBUG_TRACE, ("Head\n"));
	for (ptr = pRxPkt->head, i = 0; ptr < pRxPkt->data; ptr++, i++)
		DBGPRINT(RT_DEBUG_TRACE, ("%02x%s", *ptr, (i+1)%16 == 0 ? "\n":" "));
	DBGPRINT(RT_DEBUG_TRACE, ("\nHead_len:%d\n\nData\n", i));
	for (ptr = pRxPkt->data, i = 0; ptr < skb_tail_pointer(pRxPkt); ptr++, i++)
		DBGPRINT(RT_DEBUG_TRACE, ("%02x%s", *ptr, (i+1)%16 == 0 ? "\n":" "));
	DBGPRINT(RT_DEBUG_TRACE, ("\nData_len:%d\n", i));
	netif_rx(pRxPkt);
}
#endif

int os_set_chip_reset(void)
{
#ifdef MT53XX
	typedef void (*fpBt_func) (void);
	typedef int (*fpGpio_set) (unsigned, int);

	char *bt_sym_name = "btmtk_usb_trigger_core_dump";
	char *gpio_sym_name = "mtk_gpio_direction_output";
	fpBt_func btFunc = NULL;
	fpGpio_set gpioFunc = NULL;
	char *usb_in_suspend = "is_musb_suspend";
	BOOLEAN *is_musb_suspend = NULL;

	/* Trigger Dongle Reset by BT Driver (if available) */
#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 32)
	/* GeK: kallsyms_lookup_name is NOT EXPORTED until > 2.6.32. We shall
	 * try to avoid using such UNRECOMMENDED way.
	 */
	btFunc = (fpBt_func) kallsyms_lookup_name(bt_sym_name);
	is_musb_suspend = (BOOLEAN *)kallsyms_lookup_name(usb_in_suspend);
#endif /* LINUX_VERSION_CODE > 2.6.32 */

	if (is_musb_suspend) {
		DBGPRINT(RT_DEBUG_OFF,
			("%s() set is_musb_suspend to 0, ori = %d\n", __func__, *is_musb_suspend));
		*is_musb_suspend = 0;
	}

	if (btFunc) {
		DBGPRINT(RT_DEBUG_OFF, ("[%s] %s (%p)\n", __this_module.name,
			 bt_sym_name, btFunc));

		btFunc();

		return 0;
	}

	DBGPRINT(RT_DEBUG_OFF, ("%s - No BT Driver Func [%s] Found\n",
		__func__, bt_sym_name));

	/* Trigger Dongle Reset by Wi-Fi Driver */
#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 32)
	/* GeK: kallsyms_lookup_name is NOT EXPORTED until > 2.6.32. We shall
	 * try to avoid using such UNRECOMMENDED way.
	 */
	gpioFunc = (fpGpio_set) kallsyms_lookup_name(gpio_sym_name);
#endif /* LINUX_VERSION_CODE > 2.6.32 */
	if (gpioFunc) {
		DBGPRINT(RT_DEBUG_OFF, ("[%s] %s (%p)\n", __this_module.name,
			 gpio_sym_name, gpioFunc));

		gpioFunc(209, 0);
		mdelay(20);
		gpioFunc(209, 1);

		return 0;
	}
#endif /* MT53XX */

#ifdef MS_TV_SUPPORT
	typedef int (*fp_mGpio_set_high) (int);
	typedef int (*fp_mGpio_set_low) (int);
	typedef void (*fpBt_func) (void);

	char *bt_sym_name = "btmtk_usb_trigger_core_dump";
	char *gpio_sym_name_low = "MDrv_GPIO_Pull_Low";
	char *gpio_sym_name_high = "MDrv_GPIO_Pull_High";
	fp_mGpio_set_high m_gpiohighFunc = NULL;
	fp_mGpio_set_low m_gpiolowFunc = NULL;
	fpBt_func btFunc = NULL;

	m_gpiolowFunc = (fp_mGpio_set_low) kallsyms_lookup_name(gpio_sym_name_low);
	m_gpiohighFunc = (fp_mGpio_set_high) kallsyms_lookup_name(gpio_sym_name_high);
	btFunc = (fpBt_func) kallsyms_lookup_name(bt_sym_name);
	if (btFunc) {
		DBGPRINT(RT_DEBUG_OFF, ("[%s] %s (%p)\n", __this_module.name,
			 bt_sym_name, btFunc));

		btFunc();

		return 0;
	}
	DBGPRINT(RT_DEBUG_OFF, ("%s - No BT Driver Func [%s] Found\n",
			 __func__, bt_sym_name));

	if (m_gpiolowFunc) {
		DBGPRINT(RT_DEBUG_OFF, ("[%s] %s (%p)\n", __this_module.name, gpio_sym_name_low,
		   m_gpiolowFunc));
		m_gpiolowFunc(57);
	} else {
		DBGPRINT(RT_DEBUG_OFF, ("MDrv_GPIO_Pull_Low NOT FOUND!\n"));
		return 0;
	}
	mdelay(20);
	if (m_gpiohighFunc) {
		DBGPRINT(RT_DEBUG_OFF, ("[%s] %s (%p)\n", __this_module.name, gpio_sym_name_high,
			m_gpiohighFunc));
		m_gpiohighFunc(57);
	} else {
		DBGPRINT(RT_DEBUG_OFF, ("MDrv_GPIO_Pull_High NOT FOUND!\n"));
	}
#endif /*MS_TV_SUPPORT*/
	return 0;
}

void hex_dump(char *str, const unsigned char *pSrcBufVA, UINT SrcBufLen)
{
#ifdef DBG
	const unsigned char *pt;
	int x;

	if (RTDebugLevel < RT_DEBUG_TRACE)
		return;

	pt = pSrcBufVA;
	printk(KERN_DEBUG "%s: %p, len = %d\n", str, pSrcBufVA, SrcBufLen);
	for (x = 0; x < SrcBufLen; x++) {
		if (x % 16 == 0)
			printk(KERN_DEBUG "0x%04x : ", x);
		printk(KERN_DEBUG "%02x ", pt[x]);
		if (x % 16 == 15)
			printk(KERN_DEBUG "\n");
	}
	printk(KERN_DEBUG "\n");
#endif /* DBG */
}

void hex_dump2(char *str, const unsigned char *pSrcBufVA, UINT SrcBufLen)
{
#ifdef DBG
	const unsigned char *pt;
	int x;

/* if (RTDebugLevel < RT_DEBUG_TRACE) */
/* return; */

	pt = pSrcBufVA;
	DBGPRINT(RT_DEBUG_TRACE, ("%s: %p, len = %d\n", str, pSrcBufVA, SrcBufLen));
	for (x = 0; x < SrcBufLen; x++) {
		if (x % 16 == 0)
			DBGPRINT(RT_DEBUG_TRACE, ("0x%04x : ", x));
		DBGPRINT(RT_DEBUG_TRACE, ("%02x ", pt[x]));
		if (x % 16 == 15)
			DBGPRINT(RT_DEBUG_TRACE, ("\n"));
	}
	DBGPRINT(RT_DEBUG_TRACE, ("\n"));
#endif /* DBG */
}

#ifdef SYSTEM_LOG_SUPPORT
/*
	========================================================================

	Routine Description:
		Send log message through wireless event

		Support standard iw_event with IWEVCUSTOM. It is used below.

		iwreq_data.data.flags is used to store event_flag that is
		defined by user. iwreq_data.data.length is the length of the
		event log.

		The format of the event log is composed of the entry's MAC
		address and the desired log message (refer to
		pWirelessEventText).

			ex: 11:22:33:44:55:66 has associated successfully

		p.s. The requirement of Wireless Extension is v15 or newer.

	========================================================================
*/
VOID RtmpOsSendWirelessEvent(IN VOID *pAd,
			     IN USHORT Event_flag,
			     IN PUCHAR pAddr,
			     IN UCHAR BssIdx, IN CHAR Rssi, IN RTMP_OS_SEND_WLAN_EVENT pFunc)
{
#if WIRELESS_EXT >= 15
	pFunc(pAd, Event_flag, pAddr, BssIdx, Rssi);
#else
	DBGPRINT(RT_DEBUG_ERROR, ("%s : The Wireless Extension MUST be v15 or newer.\n", __func__));
#endif /* WIRELESS_EXT >= 15 */
}
#endif /* SYSTEM_LOG_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
VOID SendSignalToDaemon(IN INT sig, RTMP_OS_PID pid, unsigned long pid_no)
{
}
#endif /* CONFIG_AP_SUPPORT */

/*******************************************************************************

	File open/close related functions.

 *******************************************************************************/
RTMP_OS_FD RtmpOSFileOpen(char *pPath, int flag, int mode)
{
	struct file *filePtr;

	if (flag == RTMP_FILE_RDONLY)
		flag = O_RDONLY;
	else if (flag == RTMP_FILE_WRONLY)
		flag = O_WRONLY;
	else if (flag == RTMP_FILE_CREAT)
		flag = O_CREAT;
	else if (flag == RTMP_FILE_TRUNC)
		flag = O_TRUNC;

	filePtr = filp_open(pPath, flag, 0);
	if (IS_ERR(filePtr)) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("%s(): Error %ld opening %s\n", __func__,
			 -PTR_ERR(filePtr), pPath));
	}

	return (RTMP_OS_FD) filePtr;
}

int RtmpOSFileClose(RTMP_OS_FD osfd)
{
	filp_close(osfd, NULL);
	return 0;
}

void RtmpOSFileSeek(RTMP_OS_FD osfd, int offset)
{
	osfd->f_pos = offset;
}

int RtmpOSFileRead(RTMP_OS_FD osfd, char *pDataPtr, int readLen)
{
#if LINUX_VERSION_CODE >= (KERNEL_VERSION(4, 1, 0))
	return vfs_read(osfd, pDataPtr, readLen, &osfd->f_pos);
#else
	/* The object must have a read method */
	if (osfd->f_op && osfd->f_op->read)
		return osfd->f_op->read(osfd, pDataPtr, readLen, &osfd->f_pos);

	DBGPRINT(RT_DEBUG_ERROR, ("no file read method\n"));
	return -1;
#endif
}

int RtmpOSFileWrite(RTMP_OS_FD osfd, char *pDataPtr, int writeLen)
{
	return osfd->f_op->write(osfd, pDataPtr, (size_t) writeLen, &osfd->f_pos);
}

static inline void __RtmpOSFSInfoChange(OS_FS_INFO *pOSFSInfo, BOOLEAN bSet)
{
	if (bSet) {
		/* Save uid and gid used for filesystem access. */
		/* Set user and group to 0 (root) */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 29)
		pOSFSInfo->fsuid = current->fsuid;
		pOSFSInfo->fsgid = current->fsgid;
		current->fsuid = current->fsgid = 0;
#else
		pOSFSInfo->fsuid = current_fsuid();
		pOSFSInfo->fsgid = current_fsgid();
#endif /* endif */
		pOSFSInfo->fs = get_fs();
		set_fs(KERNEL_DS);
	} else {
		set_fs(pOSFSInfo->fs);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 29)
		current->fsuid = pOSFSInfo->fsuid;
		current->fsgid = pOSFSInfo->fsgid;
#endif /* endif */
	}
}

/*******************************************************************************

	Task create/management/kill related functions.

 *******************************************************************************/
static inline NDIS_STATUS __RtmpOSTaskKill(OS_TASK *pTask)
{
	int ret = NDIS_STATUS_FAILURE;

#ifdef KTHREAD_SUPPORT
	if (pTask->kthread_task) {
		kthread_stop(pTask->kthread_task);
		ret = NDIS_STATUS_SUCCESS;
	}
#else
	CHECK_PID_LEGALITY(pTask->taskPID) {
		DBGPRINT(RT_DEBUG_TRACE,
			 ("Terminate the task(%s) with pid(%d)!\n",
			  pTask->taskName, GET_PID_NUMBER(pTask->taskPID)));
		mb();
		pTask->task_killed = 1;
		mb();
		ret = KILL_THREAD_PID(pTask->taskPID, SIGTERM, 1);
		if (ret) {
			printk(KERN_WARNING
				  "kill task(%s) with pid(%d) failed(retVal=%d)!\n",
			       pTask->taskName, GET_PID_NUMBER(pTask->taskPID), ret);
		} else {
			wait_for_completion(&pTask->taskComplete);
			pTask->taskPID = THREAD_PID_INIT_VALUE;
			pTask->task_killed = 0;
			RTMP_SEM_EVENT_DESTORY(&pTask->taskSema);
			ret = NDIS_STATUS_SUCCESS;
		}
	}
#endif /* endif */

	return ret;

}

static inline INT __RtmpOSTaskNotifyToExit(OS_TASK *pTask)
{
#ifndef KTHREAD_SUPPORT
	pTask->taskPID = THREAD_PID_INIT_VALUE;
	complete_and_exit(&pTask->taskComplete, 0);
#endif /* endif */

	return 0;
}

static inline void __RtmpOSTaskCustomize(OS_TASK *pTask)
{
#ifndef KTHREAD_SUPPORT

	daemonize((PSTRING) & pTask->taskName[0] /*"%s",pAd->net_dev->name */);

	allow_signal(SIGTERM);
	allow_signal(SIGKILL);
	current->flags |= PF_NOFREEZE;

	RTMP_GET_OS_PID(pTask->taskPID, current->pid);

	/* signal that we've started the thread */
	complete(&pTask->taskComplete);
#else
	set_freezable();

#endif /* endif */
}

static inline NDIS_STATUS __RtmpOSTaskAttach(IN OS_TASK *pTask,
					     IN RTMP_OS_TASK_CALLBACK fn, IN ULONG arg)
{
	NDIS_STATUS status = NDIS_STATUS_SUCCESS;
#ifndef KTHREAD_SUPPORT
	pid_t pid_number = -1;
#endif /* KTHREAD_SUPPORT */

#ifdef KTHREAD_SUPPORT
	pTask->task_killed = 0;
	pTask->kthread_task = NULL;
	pTask->kthread_task = kthread_run((cast_fn) fn, (void *)arg, pTask->taskName);
	if (IS_ERR(pTask->kthread_task))
		status = NDIS_STATUS_FAILURE;
#else
	pid_number = kernel_thread((cast_fn) fn, (void *)arg, RTMP_OS_MGMT_TASK_FLAGS);
	if (pid_number < 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("Attach task(%s) failed!\n", pTask->taskName));
		status = NDIS_STATUS_FAILURE;
	} else {
		/* Wait for the thread to start */
		wait_for_completion(&pTask->taskComplete);
		status = NDIS_STATUS_SUCCESS;
	}
#endif /* endif */
	return status;
}

static inline NDIS_STATUS __RtmpOSTaskInit(IN OS_TASK *pTask,
					   IN PSTRING pTaskName,
					   IN VOID *pPriv, IN LIST_HEADER *pSemList)
{
	int len;

	ASSERT(pTask);

#ifndef KTHREAD_SUPPORT
	NdisZeroMemory((PUCHAR) (pTask), sizeof(OS_TASK));
#endif /* endif */

	len = strlen(pTaskName);
	len = len > (RTMP_OS_TASK_NAME_LEN - 1) ? (RTMP_OS_TASK_NAME_LEN - 1) : len;
	NdisMoveMemory(&pTask->taskName[0], pTaskName, len);
	pTask->priv = pPriv;

#ifndef KTHREAD_SUPPORT
	RTMP_SEM_EVENT_INIT_LOCKED(&(pTask->taskSema), pSemList);
	pTask->taskPID = THREAD_PID_INIT_VALUE;
	init_completion(&pTask->taskComplete);
#endif /* endif */

#ifdef KTHREAD_SUPPORT
	init_waitqueue_head(&(pTask->kthread_q));
#endif /* KTHREAD_SUPPORT */

	return NDIS_STATUS_SUCCESS;
}

static inline BOOLEAN __RtmpOSTaskWait(IN VOID *pReserved, IN OS_TASK *pTask, IN INT32 * pStatus)
{
#ifdef KTHREAD_SUPPORT
	RTMP_WAIT_EVENT_INTERRUPTIBLE((*pStatus), pTask);

	if ((pTask->task_killed == 1) || ((*pStatus) != 0))
		return FALSE;
	try_to_freeze();
#else

	RTMP_SEM_EVENT_WAIT(&(pTask->taskSema), (*pStatus));

	/* unlock the device pointers */
	if ((*pStatus) != 0) {
		/* RTMP_SET_FLAG_(*pFlags, fRTMP_ADAPTER_HALT_IN_PROGRESS); */
		return FALSE;
	}
#endif /* KTHREAD_SUPPORT */

	return TRUE;
}

static UINT32 RtmpOSWirelessEventTranslate(IN UINT32 eventType)
{
	switch (eventType) {
	case RT_WLAN_EVENT_CUSTOM:
		eventType = IWEVCUSTOM;
		break;

	case RT_WLAN_EVENT_CGIWAP:
		eventType = SIOCGIWAP;
		break;

#if WIRELESS_EXT > 17
	case RT_WLAN_EVENT_ASSOC_REQ_IE:
		eventType = IWEVASSOCREQIE;
		break;
#endif /* WIRELESS_EXT */

#if WIRELESS_EXT >= 14
	case RT_WLAN_EVENT_SCAN:
		eventType = SIOCGIWSCAN;
		break;
#endif /* WIRELESS_EXT */

	case RT_WLAN_EVENT_EXPIRED:
		eventType = IWEVEXPIRED;
		break;

	default:
		printk(KERN_DEBUG "Unknown event: 0x%x\n", eventType);
		break;
	}

	return eventType;
}

int RtmpOSWrielessEventSend(IN PNET_DEV pNetDev,
			    IN UINT32 eventType,
			    IN INT flags, IN PUCHAR pSrcMac, IN PUCHAR pData, IN UINT32 dataLen)
{
	union iwreq_data wrqu;

	/* translate event type */
	eventType = RtmpOSWirelessEventTranslate(eventType);

	memset(&wrqu, 0, sizeof(wrqu));

	if (flags > -1)
		wrqu.data.flags = flags;

	if (pSrcMac)
		memcpy(wrqu.ap_addr.sa_data, pSrcMac, MAC_ADDR_LEN);

	if ((pData != NULL) && (dataLen > 0))
		wrqu.data.length = dataLen;
	else
		wrqu.data.length = 0;

	wireless_send_event(pNetDev, eventType, &wrqu, (char *)pData);
	return 0;
}

int RtmpOSWrielessEventSendExt(IN PNET_DEV pNetDev,
			       IN UINT32 eventType,
			       IN INT flags,
			       IN PUCHAR pSrcMac,
			       IN PUCHAR pData, IN UINT32 dataLen, IN UINT32 family)
{
	union iwreq_data wrqu;

	/* translate event type */
	eventType = RtmpOSWirelessEventTranslate(eventType);

	/* translate event type */
	memset(&wrqu, 0, sizeof(wrqu));

	if (flags > -1)
		wrqu.data.flags = flags;

	if (pSrcMac)
		memcpy(wrqu.ap_addr.sa_data, pSrcMac, MAC_ADDR_LEN);

	if ((pData != NULL) && (dataLen > 0))
		wrqu.data.length = dataLen;

	wrqu.addr.sa_family = family;

	wireless_send_event(pNetDev, eventType, &wrqu, (char *)pData);
	return 0;
}

/*
========================================================================
Routine Description:
	Check if the network interface is up.

Arguments:
	*pDev			- Network Interface

Return Value:
	None

Note:
========================================================================
*/
BOOLEAN RtmpOSNetDevIsUp(VOID *pDev)
{
	struct net_device *pNetDev = (struct net_device *)pDev;

	if ((pNetDev == NULL) || !(pNetDev->flags & IFF_UP))
		return FALSE;

	return TRUE;
}

/*
========================================================================
Routine Description:
	Assign sys_handle data pointer (pAd) to the priv info structured linked to
	the OS network interface.

Arguments:
	pDev			- the os net device data structure
	pPriv			- the sys_handle want to assigned

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsSetNetDevPriv(VOID *pDev, VOID *pPriv)
{
	struct mt_dev_priv *priv_info = NULL;

	priv_info = (struct mt_dev_priv *)netdev_priv((struct net_device *)pDev);

	priv_info->sys_handle = (VOID *) pPriv;
	priv_info->priv_flags = 0;
}

/*
========================================================================
Routine Description:
	Get wifi_dev from the priv info linked to OS network interface data structure.

Arguments:
	pDev			- the device

Return Value:
	sys_handle

Note:
========================================================================
*/
VOID *RtmpOsGetNetDevPriv(VOID *pDev)
{
	return ((struct mt_dev_priv *)netdev_priv((struct net_device *)pDev))->sys_handle;
}

VOID RtmpOsSetNetDevWdev(VOID *net_dev, VOID *wdev)
{
	struct mt_dev_priv *priv_info;

	priv_info = (struct mt_dev_priv *)netdev_priv((struct net_device *)net_dev);
	priv_info->wifi_dev = wdev;
}

VOID *RtmpOsGetNetDevWdev(VOID *pDev)
{
	return ((struct mt_dev_priv *)netdev_priv((struct net_device *)pDev))->wifi_dev;
}

/*
========================================================================
Routine Description:
	Get private flags from the network interface.

Arguments:
	pDev			- the device

Return Value:
	pPriv			- the pointer

Note:
========================================================================
*/
USHORT RtmpDevPrivFlagsGet(VOID *pDev)
{
	return ((struct mt_dev_priv *)netdev_priv((struct net_device *)pDev))->priv_flags;
}

/*
========================================================================
Routine Description:
	Get private flags from the network interface.

Arguments:
	pDev			- the device

Return Value:
	pPriv			- the pointer

Note:
========================================================================
*/
VOID RtmpDevPrivFlagsSet(VOID *pDev, USHORT PrivFlags)
{
	struct mt_dev_priv *priv_info;

	priv_info = (struct mt_dev_priv *)netdev_priv((struct net_device *)pDev);
	priv_info->priv_flags = PrivFlags;
}

UCHAR get_sniffer_mode(VOID *pDev)
{
	struct mt_dev_priv *priv_info;

	priv_info = (struct mt_dev_priv *)netdev_priv((struct net_device *)pDev);
	return priv_info->sniffer_mode;
}

VOID set_sniffer_mode(VOID *net_dev, UCHAR sniffer_mode)
{
	struct mt_dev_priv *priv_info;

	priv_info = (struct mt_dev_priv *)netdev_priv((struct net_device *)net_dev);
	priv_info->sniffer_mode = sniffer_mode;
}

/*
========================================================================
Routine Description:
	Get network interface name.

Arguments:
	pDev			- the device

Return Value:
	the name

Note:
========================================================================
*/
char *RtmpOsGetNetDevName(VOID *pDev)
{
	return ((PNET_DEV) pDev)->name;
}

UINT32 RtmpOsGetNetIfIndex(IN VOID *pDev)
{
	return ((PNET_DEV) pDev)->ifindex;
}

int RtmpOSNetDevAddrSet(IN UCHAR OpMode,
			IN PNET_DEV pNetDev, IN PUCHAR pMacAddr, IN PUCHAR dev_name)
{
	struct net_device *net_dev = (struct net_device *)pNetDev;

#ifdef CONFIG_STA_SUPPORT
	/* work-around for the SuSE due to it has it's own interface name management system. */
	if (RT_CONFIG_IF_OPMODE_ON_STA(OpMode)) {
		if (dev_name != NULL) {
			NdisZeroMemory(dev_name, 16);
			NdisMoveMemory(dev_name, net_dev->name, strlen(net_dev->name));
		}
	}
#endif /* CONFIG_STA_SUPPORT */

	NdisMoveMemory(net_dev->dev_addr, pMacAddr, 6);

	return 0;
}

/*
  *	Assign the network dev name for created Ralink WiFi interface.
  */
static int RtmpOSNetDevRequestName(IN INT32 MC_RowID,
				   IN UINT32 *pIoctlIF,
				   IN PNET_DEV dev, IN PSTRING pPrefixStr, IN INT devIdx)
{
	PNET_DEV existNetDev;
	STRING suffixName[IFNAMSIZ];
	STRING desiredName[IFNAMSIZ];
	int ifNameIdx, prefixLen, slotNameLen;
	int Status;

	prefixLen = strlen(pPrefixStr);
	ASSERT((prefixLen < IFNAMSIZ));

	for (ifNameIdx = devIdx; ifNameIdx < 32; ifNameIdx++) {
		memset(suffixName, 0, IFNAMSIZ);
		memset(desiredName, 0, IFNAMSIZ);
		strncpy(&desiredName[0], pPrefixStr, prefixLen);

#ifdef MULTIPLE_CARD_SUPPORT
#ifdef RT_SOC_SUPPORT
		if (MC_RowID > 0)
			sprintf(suffixName, "i%d", ifNameIdx);
		else
#else
		if (MC_RowID >= 0)
			sprintf(suffixName, "%02d_%d", MC_RowID, ifNameIdx);
		else
#endif /* RT_SOC_SUPPORT */
#endif /* MULTIPLE_CARD_SUPPORT */
			sprintf(suffixName, "%d", ifNameIdx);

		slotNameLen = strlen(suffixName);
		ASSERT(((slotNameLen + prefixLen) < IFNAMSIZ));
		strcat(desiredName, suffixName);

		existNetDev = RtmpOSNetDevGetByName(dev, &desiredName[0]);
		if (existNetDev == NULL)
			break;

		RtmpOSNetDeviceRefPut(existNetDev);
	}

	if (ifNameIdx < 32) {
#ifdef HOSTAPD_SUPPORT
		*pIoctlIF = ifNameIdx;
#endif /*HOSTAPD_SUPPORT */
		strcpy(&dev->name[0], &desiredName[0]);
		Status = NDIS_STATUS_SUCCESS;
	} else {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("Cannot request DevName with preifx(%s) and in range(0~32) as suffix from OS!\n",
			  pPrefixStr));
		Status = NDIS_STATUS_FAILURE;
	}

	return Status;
}

void RtmpOSNetDevClose(PNET_DEV pNetDev)
{
	dev_close(pNetDev);
}

void RtmpOSNetDevFree(PNET_DEV pNetDev)
{
	ASSERT(pNetDev);

	free_netdev(pNetDev);

#ifdef VENDOR_FEATURE4_SUPPORT
	printk(KERN_DEBUG
		 "OS_NumOfMemAlloc = %ld, OS_NumOfMemFree = %ld\n",
	       OS_NumOfMemAlloc, OS_NumOfMemFree);
#endif /* VENDOR_FEATURE4_SUPPORT */
#ifdef VENDOR_FEATURE2_SUPPORT
	printk(KERN_DEBUG
		 "OS_NumOfPktAlloc = %ld, OS_NumOfPktFree = %ld\n",
	       OS_NumOfPktAlloc, OS_NumOfPktFree);
#endif /* VENDOR_FEATURE2_SUPPORT */
}

INT RtmpOSNetDevAlloc(IN PNET_DEV *new_dev_p, IN UINT32 privDataSize)
{
	*new_dev_p = NULL;

	DBGPRINT(RT_DEBUG_TRACE,
		 ("Allocate a net device with private data size=%d!\n", privDataSize));
	*new_dev_p = alloc_etherdev(privDataSize);

	if (*new_dev_p)
		return NDIS_STATUS_SUCCESS;
	else
		return NDIS_STATUS_FAILURE;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
INT RtmpOSNetDevOpsAlloc(PVOID *pNetDevOps)
{
	*pNetDevOps = (PVOID) vmalloc(sizeof(struct net_device_ops));
	if (*pNetDevOps) {
		NdisZeroMemory(*pNetDevOps, sizeof(struct net_device_ops));
		return NDIS_STATUS_SUCCESS;
	} else {
		return NDIS_STATUS_FAILURE;
	}
}
#endif /* endif */

PNET_DEV RtmpOSNetDevGetByName(PNET_DEV pNetDev, PSTRING pDevName)
{
	PNET_DEV pTargetNetDev = NULL;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 26)
	pTargetNetDev = dev_get_by_name(dev_net(pNetDev), pDevName);
#else
	ASSERT(pNetDev);
	pTargetNetDev = dev_get_by_name(pNetDev->nd_net, pDevName);
#endif /* endif */
#else
	pTargetNetDev = dev_get_by_name(pDevName);
#endif /* KERNEL_VERSION(2,6,24) */

	return pTargetNetDev;
}

void RtmpOSNetDeviceRefPut(PNET_DEV pNetDev)
{
	/*
	   every time dev_get_by_name is called, and it has returned a valid struct
	   net_device*, dev_put should be called afterwards, because otherwise the
	   machine hangs when the device is unregistered (since dev->refcnt > 1).
	 */
	if (pNetDev)
		dev_put(pNetDev);
}

INT RtmpOSNetDevDestory(VOID *pReserved, PNET_DEV pNetDev)
{

	/* TODO: Need to fix this */
	printk(KERN_DEBUG "WARNING: This function(%s) not implement yet!!!\n", __func__);
	return 0;
}

void RtmpOSNetDevDetach(PNET_DEV pNetDev)
{

	unregister_netdevice(pNetDev);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	if (pNetDev->netdev_ops) {
		DBGPRINT(RT_DEBUG_OFF, ("vfree net device ops <- %p\n", pNetDev->netdev_ops));
		vfree(pNetDev->netdev_ops);
		pNetDev->netdev_ops = NULL;
	}
#endif /* endif */
}

void RtmpOSNetDevProtect(BOOLEAN lock_it)
{
	if (lock_it)
		rtnl_lock();
	else
		rtnl_unlock();

}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 18)
static void RALINK_ET_DrvInfoGet(struct net_device *pDev, struct ethtool_drvinfo *pInfo)
{
	strcpy(pInfo->driver, "RALINK WLAN");
	sprintf(pInfo->bus_info, "CSR 0x%lx", pDev->base_addr);
}

static struct ethtool_ops RALINK_Ethtool_Ops = {
	.get_drvinfo = RALINK_ET_DrvInfoGet,
};
#endif /* endif */

int RtmpOSNetDevAttach(IN UCHAR OpMode, IN PNET_DEV pNetDev, IN RTMP_OS_NETDEV_OP_HOOK * pDevOpHook)
{
	int ret, rtnl_locked = FALSE;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	struct net_device_ops *pNetDevOps = (struct net_device_ops *)pNetDev->netdev_ops;
#endif /* endif */

	DBGPRINT(RT_DEBUG_TRACE, ("RtmpOSNetDevAttach()--->\n"));

	/* If we need hook some callback function to the net device structrue, now do it. */
	if (pDevOpHook) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
		pNetDevOps->ndo_open = pDevOpHook->open;
		pNetDevOps->ndo_stop = pDevOpHook->stop;
		pNetDevOps->ndo_start_xmit = (HARD_START_XMIT_FUNC) (pDevOpHook->xmit);
		pNetDevOps->ndo_do_ioctl = pDevOpHook->ioctl;
		if (pDevOpHook->set_mac_addr)
			pNetDevOps->ndo_set_mac_address = pDevOpHook->set_mac_addr;
#else
		pNetDev->open = pDevOpHook->open;
		pNetDev->stop = pDevOpHook->stop;
		pNetDev->hard_start_xmit = (HARD_START_XMIT_FUNC) (pDevOpHook->xmit);
		pNetDev->do_ioctl = pDevOpHook->ioctl;
#endif /* endif */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 18)
		pNetDev->ethtool_ops = &RALINK_Ethtool_Ops;
#endif /* endif */

		/* if you don't implement get_stats, just leave the callback function as NULL, a dummy
		   function will make kernel panic.
		 */
		if (pDevOpHook->get_stats)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
			pNetDevOps->ndo_get_stats = pDevOpHook->get_stats;
#else
			pNetDev->get_stats = pDevOpHook->get_stats;
#endif /* endif */

		/* OS specific flags, here we used to indicate if we are virtual interface */
/*		pNetDev->priv_flags = pDevOpHook->priv_flags; */
		RT_DEV_PRIV_FLAGS_SET(pNetDev, pDevOpHook->priv_flags);

#if (WIRELESS_EXT < 21) && (WIRELESS_EXT >= 12)
		pNetDev->get_wireless_stats = pDevOpHook->get_wstats;
#endif /* endif */

#ifdef CONFIG_WIRELESS_EXT
#if WIRELESS_EXT >= 12
#ifdef CONFIG_STA_SUPPORT
		if (OpMode == OPMODE_STA)
			pNetDev->wireless_handlers = pDevOpHook->iw_handler;
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_APSTA_MIXED_SUPPORT
		if (OpMode == OPMODE_AP)
			pNetDev->wireless_handlers = pDevOpHook->iw_handler;
#endif /* CONFIG_APSTA_MIXED_SUPPORT */
#endif /*WIRELESS_EXT >= 12 */
#endif /* CONFIG_WIRELESS_EXT */
		/* copy the net device mac address to the net_device structure. */
		NdisMoveMemory(pNetDev->dev_addr, &pDevOpHook->devAddr[0], MAC_ADDR_LEN);

		rtnl_locked = pDevOpHook->needProtcted;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24)
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	pNetDevOps->ndo_validate_addr = NULL;
	/*pNetDev->netdev_ops = ops; */
#else
	pNetDev->validate_addr = NULL;
#endif /* endif */
#endif /* endif */

	if (rtnl_locked)
		ret = register_netdevice(pNetDev);
	else
		ret = register_netdev(pNetDev);

	netif_stop_queue(pNetDev);

	DBGPRINT(RT_DEBUG_TRACE, ("<---RtmpOSNetDevAttach(), ret=%d\n", ret));
	if (ret == 0)
		return NDIS_STATUS_SUCCESS;
	else
		return NDIS_STATUS_FAILURE;
}

PNET_DEV RtmpOSNetDevCreate(IN INT32 MC_RowID,
			    IN UINT32 *pIoctlIF,
			    IN INT devType,
			    IN INT devNum, IN INT privMemSize, IN PSTRING pNamePrefix)
{
	struct net_device *pNetDev = NULL;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	struct net_device_ops *pNetDevOps = NULL;
#endif /* endif */
	int status;

	/* allocate a new network device */
	status = RtmpOSNetDevAlloc(&pNetDev, privMemSize);
	if (status != NDIS_STATUS_SUCCESS) {
		DBGPRINT(RT_DEBUG_ERROR, ("Allocate network device fail (%s)...\n", pNamePrefix));
		return NULL;
	}
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 31)
	status = RtmpOSNetDevOpsAlloc((PVOID) &pNetDevOps);
	if (status != NDIS_STATUS_SUCCESS) {
		DBGPRINT(RT_DEBUG_TRACE, ("Allocate net device ops fail!\n"));
		RtmpOSNetDevFree(pNetDev);
		pNetDev = NULL;

		return NULL;
	}

	pNetDev->netdev_ops = pNetDevOps;
	DBGPRINT(RT_DEBUG_TRACE,
		("Allocate net device ops success! -> %p\n", pNetDev->netdev_ops));

#endif /* endif */
	/* find a available interface name, max 32 interfaces */
	status = RtmpOSNetDevRequestName(MC_RowID, pIoctlIF, pNetDev, pNamePrefix, devNum);
	if (status != NDIS_STATUS_SUCCESS) {
		/* error! no any available ra name can be used! */
		DBGPRINT(RT_DEBUG_ERROR,
			 ("Assign inf name (%s with suffix 0~32) failed\n", pNamePrefix));
		RtmpOSNetDevFree(pNetDev);
		pNetDev = NULL;

		return NULL;
	}

	DBGPRINT(RT_DEBUG_TRACE, ("The name of the new %s interface is %s\n",
		pNamePrefix, pNetDev->name));

	return pNetDev;
}

#ifdef CONFIG_AP_SUPPORT
UCHAR VLAN_8023_Header_Copy(IN USHORT VLAN_VID,
			    IN USHORT VLAN_Priority,
			    IN PUCHAR pHeader802_3,
			    IN UINT HdrLen,
			    OUT PUCHAR pData, IN UCHAR FromWhichBSSID, IN UCHAR *TPID)
{
	UINT16 TCI;
	UCHAR VLAN_Size = 0;

	if (VLAN_VID != 0) {
		/* need to insert VLAN tag */
		VLAN_Size = LENGTH_802_1Q;

		/* make up TCI field */
		TCI = (VLAN_VID & 0x0fff) | ((VLAN_Priority & 0x7) << 13);

#ifndef RT_BIG_ENDIAN
		TCI = SWAP16(TCI);
#endif /* RT_BIG_ENDIAN */

		/* copy dst + src MAC (12B) */
		memcpy(pData, pHeader802_3, LENGTH_802_3_NO_TYPE);

		/* copy VLAN tag (4B) */
		/* do NOT use memcpy to speed up */
		*(UINT16 *) (pData + LENGTH_802_3_NO_TYPE) = *(UINT16 *) TPID;
		*(UINT16 *) (pData + LENGTH_802_3_NO_TYPE + 2) = TCI;

		/* copy type/len (2B) */
		*(UINT16 *) (pData + LENGTH_802_3_NO_TYPE + LENGTH_802_1Q) =
		    *(UINT16 *) &pHeader802_3[LENGTH_802_3 - LENGTH_802_3_TYPE];

		/* copy tail if exist */
		if (HdrLen > LENGTH_802_3)
			memcpy(pData + LENGTH_802_3 + LENGTH_802_1Q, pHeader802_3 + LENGTH_802_3,
			       HdrLen - LENGTH_802_3);
	} else {
		/* no VLAN tag is needed to insert */
		memcpy(pData, pHeader802_3, HdrLen);
	}

	return VLAN_Size;
}
#endif /* CONFIG_AP_SUPPORT */

/*
========================================================================
Routine Description:
    Allocate memory for adapter control block.

Arguments:
    pAd					Pointer to our adapter

Return Value:
	NDIS_STATUS_SUCCESS
	NDIS_STATUS_FAILURE
	NDIS_STATUS_RESOURCES

Note:
========================================================================
*/
NDIS_STATUS AdapterBlockAllocateMemory(VOID *handle, VOID **ppAd, UINT32 SizeOfpAd)
{

	*ppAd = (PVOID) vmalloc(SizeOfpAd);
	if (*ppAd) {
		NdisZeroMemory(*ppAd, SizeOfpAd);
		return NDIS_STATUS_SUCCESS;
	} else
		return NDIS_STATUS_FAILURE;
}

/* ========================================================================== */

UINT RtmpOsWirelessExtVerGet(VOID)
{
	return WIRELESS_EXT;
}

static void mt76x2_print_val2file(const char *fn, const void *buf,
				  const UINT32 start, const UINT32 end,
				  const UINT32 size)
{
	struct file *file_w;
	mm_segment_t orig_fs;
	char msg[32];

	if (start > end) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: invalid param s:0x%x e:0x%x\n",
			 __func__, start, end));
		return;
	}

	if (size != 1 && size != 2 && size != 4) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: invalid param unit size %u\n",
			 __func__, size));
		return;
	}

	orig_fs = get_fs();
	set_fs(KERNEL_DS);

	/* open file */
	file_w = filp_open(fn, O_WRONLY | O_CREAT | O_APPEND, 0444);
	if (IS_ERR(file_w)) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: Error %ld opening %s\n",
			 __func__, -PTR_ERR(file_w), fn));
		goto done;
	}

	if (file_w->f_op && file_w->f_op->write) {
		const u8 *p1 = (const u8 *)buf;
		const u16 *p2 = (const u16 *)buf;
		const u32 *p4 = (const u32 *)buf;
		UINT32 addr;

		file_w->f_pos = 0;
		addr = start;
		while (addr <= end) {
			if (size == 4)
				snprintf(msg, sizeof(msg), "%04x = %08x\n",
					 addr, *p4++);
			else if (size == 2)
				snprintf(msg, sizeof(msg), "%04x = %04x\n",
					 addr, *p2++);
			else
				snprintf(msg, sizeof(msg), "%04x = %02x\n",
					 addr, *p1++);
			addr += size;

			/* write data to file */
			file_w->f_op->write(file_w, msg, strlen(msg),
					    &file_w->f_pos);

			DBGPRINT(RT_DEBUG_TRACE, ("%s\n", msg));
		}

		DBGPRINT(RT_DEBUG_OFF, ("Dump all values to %s done\n", fn));
	}
	filp_close(file_w, NULL);

done:
	set_fs(orig_fs);
}

VOID RtmpDrvAllBbpPrint(UINT32 *pBufBbp, UINT32 start, UINT32 end, UINT32 step)
{
	mt76x2_print_val2file("BbpDump.txt", pBufBbp, start, end, step);
}

VOID RtmpDrvAllMacPrint(UINT32 *pBufMac, UINT32 start, UINT32 end, UINT32 step)
{
	mt76x2_print_val2file("MacDump.txt", pBufMac, start, end, step);
}

VOID RtmpDrvAllE2PPrint(IN VOID *pReserved,
			IN USHORT *pMacContent, IN UINT32 AddrEnd, IN UINT32 AddrStep)
{
	struct file *file_w;
	PSTRING fileName = "EEPROMDump.txt";
	mm_segment_t orig_fs;
	STRING *msg;
	USHORT eepAddr = 0;
	USHORT eepValue;

	os_alloc_mem(NULL, (UCHAR **) &msg, 1024);
	if (!msg)
		return;

	orig_fs = get_fs();
	set_fs(KERNEL_DS);

	/* open file */
	file_w = filp_open(fileName, O_WRONLY | O_CREAT | O_APPEND, 0444);
	if (IS_ERR(file_w)) {
		DBGPRINT(RT_DEBUG_TRACE,
			 ("-->2) %s: Error %ld opening %s\n", __func__,
			  -PTR_ERR(file_w), fileName));
	} else {
		if (file_w->f_op && file_w->f_op->write) {
			file_w->f_pos = 0;
			eepAddr = 0x00;

			while (eepAddr <= AddrEnd) {
				eepValue = *pMacContent;
				sprintf(msg, "%08x = %04x\n", eepAddr, eepValue);

				/* write data to file */
				file_w->f_op->write(file_w, msg, strlen(msg), &file_w->f_pos);

				printk(KERN_DEBUG "%s", msg);
				eepAddr += AddrStep;
				pMacContent += (AddrStep >> 1);
			}
			sprintf(msg, "\nDump all EEPROM values to %s\n", fileName);
		}
		filp_close(file_w, NULL);
	}
	set_fs(orig_fs);
	os_free_mem(NULL, msg);
}

VOID RtmpDrvAllRFPrint(IN VOID *pReserved, IN UCHAR *pBuf, IN UINT32 BufLen)
{
	struct file *file_w;
	PSTRING fileName = "RFDump.txt";
	mm_segment_t orig_fs;

	orig_fs = get_fs();
	set_fs(KERNEL_DS);

	/* open file */
	file_w = filp_open(fileName, O_WRONLY | O_CREAT | O_APPEND, 0444);
	if (IS_ERR(file_w)) {
		DBGPRINT(RT_DEBUG_TRACE,
			 ("-->2) %s: Error %ld opening %s\n", __func__,
			  -PTR_ERR(file_w), fileName));
	} else {
		if (file_w->f_op && file_w->f_op->write) {
			file_w->f_pos = 0;
			/* write data to file */
			file_w->f_op->write(file_w, pBuf, BufLen, &file_w->f_pos);
		}
		filp_close(file_w, NULL);
	}
	set_fs(orig_fs);
}

/*
========================================================================
Routine Description:
	Wake up the command thread.

Arguments:
	pAd				- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsCmdUp(RTMP_OS_TASK *pCmdQTask)
{
	OS_TASK *pTask = RTMP_OS_TASK_GET(pCmdQTask);
#ifdef KTHREAD_SUPPORT
	pTask->kthread_running = TRUE;
	wake_up(&pTask->kthread_q);
#else
	CHECK_PID_LEGALITY(pTask->taskPID) {
		RTMP_SEM_EVENT_UP(&(pTask->taskSema));
	}
#endif /* KTHREAD_SUPPORT */
}

/*
========================================================================
Routine Description:
	Wake up USB Mlme thread.

Arguments:
	pAd				- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsMlmeUp(IN RTMP_OS_TASK *pMlmeQTask)
{
	OS_TASK *pTask = RTMP_OS_TASK_GET(pMlmeQTask);

#ifdef KTHREAD_SUPPORT
	if ((pTask != NULL) && (pTask->kthread_task)) {
		pTask->kthread_running = TRUE;
		wake_up(&pTask->kthread_q);
	}
#else
	if (pTask != NULL) {
		CHECK_PID_LEGALITY(pTask->taskPID) {
			RTMP_SEM_EVENT_UP(&(pTask->taskSema));
		}
	}
#endif /* KTHREAD_SUPPORT */
}

/*
========================================================================
Routine Description:
	Check if the file is error.

Arguments:
	pFile			- the file

Return Value:
	OK or any error

Note:
	rt_linux.h, not rt_drv.h
========================================================================
*/
INT32 RtmpOsFileIsErr(IN VOID *pFile)
{
	return IS_FILE_OPEN_ERR(pFile);
}

int RtmpOSIRQRelease(IN PNET_DEV net_dev,
		     IN UINT32 infType, IN PPCI_DEV pci_dev, IN BOOLEAN *pHaveMsi)
{


	return 0;
}

/*
========================================================================
Routine Description:
	Enable or disable wireless event sent.

Arguments:
	pReserved		- Reserved
	FlgIsWEntSup	- TRUE or FALSE

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsWlanEventSet(IN VOID *pReserved, IN BOOLEAN *pCfgWEnt, IN BOOLEAN FlgIsWEntSup)
{
#if WIRELESS_EXT >= 15
/*	pAd->CommonCfg.bWirelessEvent = FlgIsWEntSup; */
	*pCfgWEnt = FlgIsWEntSup;
#else
	*pCfgWEnt = 0;		/* disable */
#endif /* endif */
}

/*
========================================================================
Routine Description:
	vmalloc

Arguments:
	Size			- memory size

Return Value:
	the memory

Note:
========================================================================
*/
VOID *RtmpOsVmalloc(ULONG Size)
{
	return vmalloc(Size);
}

/*
========================================================================
Routine Description:
	vfree

Arguments:
	pMem			- the memory

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsVfree(VOID *pMem)
{
	if (pMem != NULL)
		vfree(pMem);
}

/*
========================================================================
Routine Description:
	Assign protocol to the packet.

Arguments:
	pPkt			- the packet

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsPktProtocolAssign(PNDIS_PACKET pNetPkt)
{
	struct sk_buff *pRxPkt = RTPKT_TO_OSPKT(pNetPkt);

	pRxPkt->protocol = eth_type_trans(pRxPkt, pRxPkt->dev);
}

BOOLEAN RtmpOsStatsAlloc(IN VOID **ppStats, IN VOID **ppIwStats)
{
	os_alloc_mem(NULL, (UCHAR **) ppStats, sizeof(struct net_device_stats));
	if ((*ppStats) == NULL)
		return FALSE;
	NdisZeroMemory((UCHAR *) *ppStats, sizeof(struct net_device_stats));

#if WIRELESS_EXT >= 12
	os_alloc_mem(NULL, (UCHAR **) ppIwStats, sizeof(struct iw_statistics));
	if ((*ppIwStats) == NULL) {
		os_free_mem(NULL, *ppStats);
		return FALSE;
	}
	NdisZeroMemory((UCHAR *) *ppIwStats, sizeof(struct iw_statistics));
#endif /* endif */

	return TRUE;
}

/*
========================================================================
Routine Description:
	Pass the received packet to OS.

Arguments:
	pPkt			- the packet

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsPktRcvHandle(PNDIS_PACKET pNetPkt)
{
	struct sk_buff *pRxPkt = RTPKT_TO_OSPKT(pNetPkt);


	netif_rx(pRxPkt);
}

VOID RtmpOsTaskPidInit(RTMP_OS_PID *pPid)
{
	*pPid = THREAD_PID_INIT_VALUE;
}

/*
========================================================================
Routine Description:
	Get the network interface for the packet.

Arguments:
	pPkt			- the packet

Return Value:
	None

Note:
========================================================================
*/
PNET_DEV RtmpOsPktNetDevGet(VOID *pPkt)
{
	return GET_OS_PKT_NETDEV(pPkt);
}

#ifdef IAPP_SUPPORT
/* Layer 2 Update frame to switch/bridge */
/* For any Layer2 devices, e.g., bridges, switches and other APs, the frame
   can update their forwarding tables with the correct port to reach the new
   location of the STA */
typedef struct GNU_PACKED _RT_IAPP_L2_UPDATE_FRAME {

	UCHAR DA[ETH_ALEN];	/* broadcast MAC address */
	UCHAR SA[ETH_ALEN];	/* the MAC address of the STA that has just associated
				   or reassociated */
	USHORT Len;		/* 8 octets */
	UCHAR DSAP;		/* null */
	UCHAR SSAP;		/* null */
	UCHAR Control;		/* reference to IEEE Std 802.2 */
	UCHAR XIDInfo[3];	/* reference to IEEE Std 802.2 */
} RT_IAPP_L2_UPDATE_FRAME, *PRT_IAPP_L2_UPDATE_FRAME;

PNDIS_PACKET RtmpOsPktIappMakeUp(IN PNET_DEV pNetDev, IN UINT8 * pMac)
{
	RT_IAPP_L2_UPDATE_FRAME frame_body;
	INT size = sizeof(RT_IAPP_L2_UPDATE_FRAME);
	PNDIS_PACKET pNetBuf;

	if (pNetDev == NULL)
		return NULL;

	pNetBuf = RtmpOSNetPktAlloc(NULL, size);
	if (!pNetBuf) {
		DBGPRINT(RT_DEBUG_ERROR, ("Error! Can't allocate a skb.\n"));
		return NULL;
	}

	/* init the update frame body */
	NdisZeroMemory(&frame_body, size);

	memset(frame_body.DA, 0xFF, ETH_ALEN);
	ether_addr_copy(frame_body.SA, pMac);

	frame_body.Len = OS_HTONS(ETH_ALEN);
	frame_body.DSAP = 0;
	frame_body.SSAP = 0x01;
	frame_body.Control = 0xAF;

	frame_body.XIDInfo[0] = 0x81;
	frame_body.XIDInfo[1] = 1;
	frame_body.XIDInfo[2] = 1 << 1;

	SET_OS_PKT_NETDEV(pNetBuf, pNetDev);
	skb_reserve(pNetBuf, 2);
	memcpy(skb_put(pNetBuf, size), &frame_body, size);
	return pNetBuf;
}
#endif /* IAPP_SUPPORT */

VOID RtmpOsPktNatMagicTag(IN PNDIS_PACKET pNetPkt)
{
#if !defined(CONFIG_RA_NAT_NONE)
#if defined(CONFIG_RA_HW_NAT)  || defined(CONFIG_RA_HW_NAT_MODULE)
	struct sk_buff *pRxPkt = RTPKT_TO_OSPKT(pNetPkt);

	FOE_MAGIC_TAG(pRxPkt) = FOE_MAGIC_WLAN;
#endif /* CONFIG_RA_HW_NAT || CONFIG_RA_HW_NAT_MODULE */
#endif /* CONFIG_RA_NAT_NONE */
}

VOID RtmpOsPktNatNone(IN PNDIS_PACKET pNetPkt)
{
#if defined(CONFIG_RA_NAT_NONE)
#if defined(CONFIG_RA_HW_NAT)  || defined(CONFIG_RA_HW_NAT_MODULE)
	FOE_AI(((struct sk_buff *)pNetPkt)) = UN_HIT;
#endif /* CONFIG_RA_HW_NAT || CONFIG_RA_HW_NAT_MODULE */
#endif /* CONFIG_RA_NAT_NONE */
}

/*
========================================================================
Routine Description:
	Flush a data cache line.

Arguments:
	AddrStart		- the start address
	Size			- memory size

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsDCacheFlush(IN ULONG AddrStart, IN ULONG Size)
{
	RTMP_UTIL_DCACHE_FLUSH(AddrStart, Size);
}

#ifdef CONFIG_STA_SUPPORT
INT RtmpOSNotifyRawData(IN PNET_DEV pNetDev,
			IN PUCHAR buff, IN INT len, IN ULONG type, IN USHORT protocol)
{
	struct sk_buff *skb = NULL;

	skb = dev_alloc_skb(len + 2);

	if (!skb) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("%s: failed to allocate sk_buff for notification\n", pNetDev->name));
		return -ENOMEM;
	}

	skb_reserve(skb, 2);
	memcpy(skb_put(skb, len), buff, len);
	skb->len = len;
	skb->dev = pNetDev;
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 21))
	skb->mac.raw = skb->data;
#else
	skb_set_mac_header(skb, 0);
#endif /* endif */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(protocol);
	memset(skb->cb, 0, sizeof(skb->cb));

	netif_rx(skb);

	return 0;
}

#endif /* CONFIG_STA_SUPPORT */

void OS_SPIN_LOCK_IRQSAVE(NDIS_SPIN_LOCK *lock, unsigned long *flags)
{
	spin_lock_irqsave((spinlock_t *) (lock), *flags);
}

void OS_SPIN_UNLOCK_IRQRESTORE(NDIS_SPIN_LOCK *lock, unsigned long *flags)
{
	spin_unlock_irqrestore((spinlock_t *) (lock), *flags);
}

void OS_SPIN_LOCK(NDIS_SPIN_LOCK *lock)
{
	spin_lock((spinlock_t *) (lock));
}

void OS_SPIN_UNLOCK(NDIS_SPIN_LOCK *lock)
{
	spin_unlock((spinlock_t *) (lock));
}

void OS_SPIN_LOCK_IRQ(NDIS_SPIN_LOCK *lock)
{
	spin_lock_irq((spinlock_t *) (lock));
}

void OS_SPIN_UNLOCK_IRQ(NDIS_SPIN_LOCK *lock)
{
	spin_unlock_irq((spinlock_t *) (lock));
}

int OS_TEST_BIT(int bit, unsigned long *flags)
{
	return test_bit(bit, flags);
}

void OS_SET_BIT(int bit, unsigned long *flags)
{
	set_bit(bit, flags);
}

void OS_CLEAR_BIT(int bit, unsigned long *flags)
{
	clear_bit(bit, flags);
}

#ifndef BB_SOC
void OS_LOAD_CODE_FROM_BIN(unsigned char **image, char *bin_name, void *inf_dev, UINT32 *code_len)
{
	struct device *dev;
	const struct firmware *fw_entry;


#ifdef RTMP_USB_SUPPORT
	dev = (struct device *)(&(((struct usb_device *)(inf_dev))->dev));
#endif /* endif */

	if (request_firmware(&fw_entry, bin_name, dev) != 0) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("%s: FW not available at $FIRMWARE_PATH/%s\n", __func__, bin_name));
		*image = NULL;
		return;
	}

	*image = vmalloc(fw_entry->size);
	memcpy(*image, fw_entry->data, fw_entry->size);
	*code_len = fw_entry->size;

	release_firmware(fw_entry);
}
#endif /* !BB_SOC */

#ifdef WSC_NFC_SUPPORT
INT RtmpOSNotifyRawData(IN PNET_DEV pNetDev,
			IN PUCHAR buff, IN INT len, IN ULONG type, IN USHORT protocol)
{
	struct sk_buff *skb = NULL;

	skb = dev_alloc_skb(len + 2);

	if (!skb) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("%s: failed to allocate sk_buff for notification\n", pNetDev->name));
		return -ENOMEM;
	}

	skb_reserve(skb, 2);
	memcpy(skb_put(skb, len), buff, len);
	skb->len = len;
	skb->dev = pNetDev;
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 21))
	skb->mac.raw = skb->data;
#else
	skb_set_mac_header(skb, 0);
#endif /* endif */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(protocol);
	memset(skb->cb, 0, sizeof(skb->cb));

	netif_rx(skb);

	return 0;
}
#endif /* WSC_NFC_SUPPORT */

void RtmpOSFSInfoChange(RTMP_OS_FS_INFO *pOSFSInfoOrg, BOOLEAN bSet)
{
	__RtmpOSFSInfoChange(pOSFSInfoOrg, bSet);
}

/* timeout -- ms */
VOID RTMP_SetPeriodicTimer(NDIS_MINIPORT_TIMER *pTimerOrg, unsigned long timeout)
{
	__RTMP_SetPeriodicTimer(pTimerOrg, timeout);
}

/* convert NdisMInitializeTimer --> RTMP_OS_Init_Timer */
VOID RTMP_OS_Init_Timer(VOID *pReserved,
			NDIS_MINIPORT_TIMER *pTimerOrg,
			TIMER_FUNCTION function, PVOID data, LIST_HEADER *pTimerList)
{
	__RTMP_OS_Init_Timer(pReserved, pTimerOrg, function, data);
}

VOID RTMP_OS_Add_Timer(NDIS_MINIPORT_TIMER *pTimerOrg, unsigned long timeout)
{
	__RTMP_OS_Add_Timer(pTimerOrg, timeout);
}

VOID RTMP_OS_Mod_Timer(NDIS_MINIPORT_TIMER *pTimerOrg, unsigned long timeout)
{
	__RTMP_OS_Mod_Timer(pTimerOrg, timeout);
}

VOID RTMP_OS_Del_Timer(NDIS_MINIPORT_TIMER *pTimerOrg, BOOLEAN *pCancelled)
{
	__RTMP_OS_Del_Timer(pTimerOrg, pCancelled);
}

VOID RTMP_OS_Release_Timer(NDIS_MINIPORT_TIMER *pTimerOrg)
{
	__RTMP_OS_Release_Timer(pTimerOrg);
}

NDIS_STATUS RtmpOSTaskKill(RTMP_OS_TASK *pTask)
{
	return __RtmpOSTaskKill(pTask);
}

INT RtmpOSTaskNotifyToExit(RTMP_OS_TASK *pTask)
{
	return __RtmpOSTaskNotifyToExit(pTask);
}

void RtmpOSTaskCustomize(RTMP_OS_TASK *pTask)
{
	__RtmpOSTaskCustomize(pTask);
}

NDIS_STATUS RtmpOSTaskAttach(RTMP_OS_TASK *pTask, RTMP_OS_TASK_CALLBACK fn, ULONG arg)
{
	return __RtmpOSTaskAttach(pTask, fn, arg);
}

NDIS_STATUS RtmpOSTaskInit(RTMP_OS_TASK *pTask,
			   PSTRING pTaskName,
			   VOID *pPriv, LIST_HEADER *pTaskList, LIST_HEADER *pSemList)
{
	return __RtmpOSTaskInit(pTask, pTaskName, pPriv, pSemList);
}

BOOLEAN RtmpOSTaskWait(VOID *pReserved, RTMP_OS_TASK *pTask, INT32 *pStatus)
{
	return __RtmpOSTaskWait(pReserved, pTask, pStatus);
}

VOID RtmpOsTaskWakeUp(RTMP_OS_TASK *pTask)
{
#ifdef KTHREAD_SUPPORT
	WAKE_UP(pTask);
#else
	RTMP_SEM_EVENT_UP(&pTask->taskSema);
#endif /* endif */
}
