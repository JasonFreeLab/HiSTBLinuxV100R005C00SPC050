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


#include "rt_config.h"

INT rtmp_wdev_idx_unreg(RTMP_ADAPTER *pAd, struct wifi_dev *wdev)
{
	INT idx;
	ULONG flags;

	if (!wdev)
		return -1;

	RTMP_INT_LOCK(&pAd->irq_lock, flags);
	for (idx = 0; idx < WDEV_NUM_MAX; idx++) {
		if (pAd->wdev_list[idx] == wdev) {
			DBGPRINT(RT_DEBUG_WARN,
				 ("unregister wdev(type:%d, idx:%d) from wdev_list\n",
				  wdev->wdev_type, wdev->wdev_idx));
			pAd->wdev_list[idx] = NULL;
			wdev->wdev_idx = WDEV_NUM_MAX;
			break;
		}
	}

	if (idx == WDEV_NUM_MAX) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("Cannot found wdev(%p, type:%d, idx:%d) in wdev_list\n",
			  wdev, wdev->wdev_type, wdev->wdev_idx));
		DBGPRINT(RT_DEBUG_OFF, ("Dump wdev_list:\n"));
		for (idx = 0; idx < WDEV_NUM_MAX; idx++)
			DBGPRINT(RT_DEBUG_OFF, ("Idx %d: 0x%p\n", idx, pAd->wdev_list[idx]));
	}
	RTMP_INT_UNLOCK(&pAd->irq_lock, flags);

	return ((idx < WDEV_NUM_MAX) ? 0 : -1);

}

INT rtmp_wdev_idx_reg(RTMP_ADAPTER *pAd, struct wifi_dev *wdev)
{
	INT idx;
	ULONG flags;

	if (!wdev)
		return -1;

	RTMP_INT_LOCK(&pAd->irq_lock, flags);
	for (idx = 0; idx < WDEV_NUM_MAX; idx++) {
		if (pAd->wdev_list[idx] == wdev) {
			DBGPRINT(RT_DEBUG_WARN,
				 ("wdev(type:%d) already registered and idx(%d) %smatch\n",
				  wdev->wdev_type, wdev->wdev_idx,
				  ((idx != wdev->wdev_idx) ? "mis" : "")));
			break;
		}
		if (pAd->wdev_list[idx] == NULL) {
			pAd->wdev_list[idx] = wdev;
			break;
		}
	}

	wdev->wdev_idx = idx;
	if (idx < WDEV_NUM_MAX)
		DBGPRINT(RT_DEBUG_TRACE, ("Assign wdev_idx=%d\n", idx));
	RTMP_INT_UNLOCK(&pAd->irq_lock, flags);

	return ((idx < WDEV_NUM_MAX) ? idx : -1);
}

#ifdef DELAYED_TCP_ACK
UINT flush_tcp_ack_queue(PRTMP_ADAPTER pAd, PMAC_TABLE_ENTRY pEntry, BOOLEAN bCancelTimer)
{
	PNDIS_PACKET pPacket;
	BOOLEAN Cancelled;
	UINT cnt = 0;

	if (bCancelTimer && pEntry->QueueAckTimerRunning == TRUE)
		RTMPCancelTimer(&pEntry->QueueAckTimer, &Cancelled);

	pEntry->QueueAckTimerRunning = FALSE;

	while (1) {
		pPacket = skb_dequeue(&pEntry->ack_queue);
		if (pPacket == NULL)
			break;

		cnt++;
		APSendPacket(pAd, pPacket);
	}

	return cnt;
}

VOID RTMPQueueAckPeriodicExec(IN PVOID SystemSpecific1,
			      IN PVOID FunctionContext,
			      IN PVOID SystemSpecific2, IN PVOID SystemSpecific3)
{
	MAC_TABLE_ENTRY *pEntry = (MAC_TABLE_ENTRY *) FunctionContext;
	PNDIS_PACKET pPacket;
	UINT cnt = 0;

	if (pEntry) {
		PRTMP_ADAPTER pAd = (PRTMP_ADAPTER) pEntry->pAd;

		cnt = flush_tcp_ack_queue(pAd, pEntry, FALSE);
		pAd->CommonCfg.AckTimeout += cnt;

		if (cnt <= TCP_ACK_BURST_LEVEL)
			pAd->CommonCfg.TcpAck[cnt]++;
		else
			DBGPRINT(RT_DEBUG_TRACE, ("TcpAck: cnt not range=%d\n", cnt));

		RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, MAX_TX_PROCESS);
	}
}

/* Delayed TCP Ack */
BOOLEAN delay_tcp_ack(RTMP_ADAPTER *pAd, UCHAR wcid, PNDIS_PACKET pPacket)
{
	PUCHAR pSrcBuf;
	UINT32 pktLen, qlen;
	PMAC_TABLE_ENTRY pEntry;
	BOOLEAN bDelay = FALSE;

	pEntry = &pAd->MacTab.Content[wcid];
	pSrcBuf = GET_OS_PKT_DATAPTR(pPacket);
	pktLen = GET_OS_PKT_LEN(pPacket);

	if (pAd->CommonCfg.ACKQEN == 1) {
		/* get Ethernet protocol field */
		USHORT TypeLen = OS_NTOHS(*((UINT16 *) (pSrcBuf + 12)));

		/* bypass VALN 802.1Q field */
		if (TypeLen == 0x8100)
			pSrcBuf += 4;
		else if ((TypeLen == 0x9100) || (TypeLen == 0x9200) || (TypeLen == 0x9300))
			pSrcBuf += 8;

		if ((TypeLen == 0x0800)	/* Type: IP (0x0800) */
			&& (pSrcBuf[23] == 0x06)	/* Protocol: TCP (0x06) */
			&& (pktLen >= 48) && ((pSrcBuf[47] & 0x10) == 0x10)) {	/* Flags: Ack bit is set */
			skb_queue_tail(&pEntry->ack_queue, pPacket);
			qlen = skb_queue_len(&pEntry->ack_queue);
			bDelay = TRUE;

			if (qlen == 1) {
				if (pEntry->QueueAckTimerRunning == FALSE) {
					DBGPRINT(RT_DEBUG_LOUD, ("found tcp ack..\n"));
					RTMPSetTimer(&pEntry->QueueAckTimer,
						     pAd->CommonCfg.AckWaitTime);
					pEntry->QueueAckTimerRunning = TRUE;
				}
			} else if ((qlen >= pAd->CommonCfg.Acklen)
				   || ((pSrcBuf[47] & 0x03) != 0)	/* Flags: FIN(bit0) or SYN(bit1) is set */
				   || (pktLen > 66)) {	/* TCP ACK with other payload in IPv4 format */
				pAd->CommonCfg.AckNOTimeout +=
				    flush_tcp_ack_queue(pAd, pEntry, TRUE);
			}
		}
	} else {
		flush_tcp_ack_queue(pAd, pEntry, TRUE);
	}

	return bDelay;
}
#endif /* DELAYED_TCP_ACK */

/*
========================================================================
Routine Description:
    Early checking and OS-depened parsing for Tx packet to AP device.

Arguments:
    NDIS_HANDLE	MiniportAdapterContext	Pointer refer to the device handle, i.e., the pAd.
	PPNDIS_PACKET	ppPacketArray			The packet array need to do transmission.
	UINT			NumberOfPackets			Number of packet in packet array.

Return Value:
	NONE

Note:
	This function do early checking and classification for send-out packet.
	You only can put OS-depened & AP related code in here.
========================================================================
*/
VOID wdev_tx_pkts(NDIS_HANDLE dev_hnd, PPNDIS_PACKET pkt_list, UINT pkt_cnt, struct wifi_dev *wdev)
{
	RTMP_ADAPTER *pAd = (RTMP_ADAPTER *) dev_hnd;
	PNDIS_PACKET pPacket;
	BOOLEAN allowToSend;
	UCHAR wcid = MCAST_WCID;
	UINT Index;


	for (Index = 0; Index < pkt_cnt; Index++) {
		pPacket = pkt_list[Index];

		if (RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS |
					 fRTMP_ADAPTER_HALT_IN_PROGRESS |
					 fRTMP_ADAPTER_RADIO_OFF))) {
			/* Drop send request since hardware is in reset state */
			RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
			continue;
		}

		if ((wdev->allow_data_tx == TRUE) && (wdev->tx_pkt_allowed))
			allowToSend = wdev->tx_pkt_allowed(pAd, wdev, pPacket, &wcid);
		else
			allowToSend = FALSE;

		if (allowToSend == TRUE) {
			RTMP_SET_PACKET_WCID(pPacket, wcid);
			RTMP_SET_PACKET_WDEV(pPacket, wdev->wdev_idx);
			NDIS_SET_PACKET_STATUS(pPacket, NDIS_STATUS_PENDING);
			pAd->RalinkCounters.PendingNdisPacketCount++;

#ifdef CONFIG_AP_SUPPORT
			IF_DEV_CONFIG_OPMODE_ON_AP(pAd) {
#ifdef DELAYED_TCP_ACK
				if (!delay_tcp_ack(pAd, wcid, pPacket))
#endif /* DELAYED_TCP_ACK */
					APSendPacket(pAd, pPacket);
			}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
			IF_DEV_CONFIG_OPMODE_ON_STA(pAd) {
#ifdef RT_CFG80211_P2P_SUPPORT
				if (RTMP_GET_PACKET_OPMODE(pPacket))
					APSendPacket(pAd, pPacket);
				else
#endif /* RT_CFG80211_P2P_SUPPORT */
					STASendPacket(pAd, pPacket);
			}
#endif /* CONFIG_STA_SUPPORT */
		} else {
			RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
		}
	}

	/* Dequeue outgoing frames from TxSwQueue[] and process it */
	RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, MAX_TX_PROCESS);
}
