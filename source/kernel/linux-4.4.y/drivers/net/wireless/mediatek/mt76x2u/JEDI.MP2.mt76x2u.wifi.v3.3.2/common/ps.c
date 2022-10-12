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

    Abstract:

	All related POWER SAVE function body.

***************************************************************************/

#include "rt_config.h"

/*
	========================================================================
	Routine Description:
		This routine is used to do insert packet into power-saveing queue.

	Arguments:
		pAd: Pointer to our adapter
		pPacket: Pointer to send packet
		pMacEntry: portint to entry of MacTab. the pMacEntry store attribute of client (STA).
		QueIdx: Priority queue idex.

	Return Value:
		NDIS_STATUS_SUCCESS:If succes to queue the packet into TxSwQueue.
		NDIS_STATUS_FAILURE: If failed to do en-queue.
========================================================================
*/
NDIS_STATUS RtmpInsertPsQueue(RTMP_ADAPTER *pAd,
			      PNDIS_PACKET pPacket, MAC_TABLE_ENTRY *pMacEntry, UCHAR QueIdx)
{
	ULONG IrqFlags;
#ifdef UAPSD_SUPPORT
	/* put the U-APSD packet to its U-APSD queue by AC ID */
	UINT32 ac_id = QueIdx - QID_AC_BE;	/* should be >= 0 */

	if (UAPSD_MR_IS_UAPSD_AC(pMacEntry, ac_id)) {
		UAPSD_PacketEnqueue(pAd, pMacEntry, pPacket, ac_id);

#if defined(DOT11Z_TDLS_SUPPORT)
		TDLS_UAPSDP_TrafficIndSend(pAd, pMacEntry->Addr);
#endif /* defined(DOT11Z_TDLS_SUPPORT) */
#ifdef CFG_TDLS_SUPPORT
		cfg_tdls_send_PeerTrafficIndication(pAd, pMacEntry->Addr);
#endif /* CFG_TDLS_SUPPORT */
	} else
#endif /* UAPSD_SUPPORT */
	{
		if (pMacEntry->PsQueue.Number >= MAX_PACKETS_IN_PS_QUEUE) {
			RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
			return NDIS_STATUS_FAILURE;
		}

		DBGPRINT(RT_DEBUG_TRACE, ("legacy ps> queue a packet!\n"));
		RTMP_IRQ_LOCK(&pAd->irq_lock, IrqFlags);
		InsertTailQueue(&pMacEntry->PsQueue, PACKET_TO_QUEUE_ENTRY(pPacket));
		RTMP_IRQ_UNLOCK(&pAd->irq_lock, IrqFlags);
	}

#ifdef CONFIG_AP_SUPPORT
	/* mark corresponding TIM bit in outgoing BEACON frame */
#ifdef UAPSD_SUPPORT
	if (UAPSD_MR_IS_NOT_TIM_BIT_NEEDED_HANDLED(pMacEntry, QueIdx)) {
		/* 1. the station is UAPSD station;
		   2. one of AC is non-UAPSD (legacy) AC;
		   3. the destinated AC of the packet is UAPSD AC. */
		/* So we can not set TIM bit due to one of AC is legacy AC */
	} else
#endif /* UAPSD_SUPPORT */
	{
		WLAN_MR_TIM_BIT_SET(pAd, pMacEntry->apidx, pMacEntry->Aid);

	}
#endif /* CONFIG_AP_SUPPORT */

	return NDIS_STATUS_SUCCESS;
}

/*
	==========================================================================
	Description:
		This routine is used to clean up a specified power-saving queue. It's
		used whenever a wireless client is deleted.
	==========================================================================
 */
VOID RtmpCleanupPsQueue(RTMP_ADAPTER *pAd, QUEUE_HEADER *pQueue)
{
	QUEUE_ENTRY *pQEntry;
	PNDIS_PACKET pPacket;

	DBGPRINT(RT_DEBUG_INFO, ("RtmpCleanupPsQueue (0x%08lx)...\n", (ULONG) pQueue));

	while (pQueue->Head) {
		DBGPRINT(RT_DEBUG_TRACE, ("RtmpCleanupPsQueue %u...\n", pQueue->Number));

		pQEntry = RemoveHeadQueue(pQueue);
		/*pPacket = CONTAINING_RECORD(pEntry, NDIS_PACKET, MiniportReservedEx); */
		pPacket = QUEUE_ENTRY_TO_PACKET(pQEntry);
		RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);

		DBGPRINT(RT_DEBUG_TRACE, ("RtmpCleanupPsQueue pkt = %lx...\n", (ULONG) pPacket));
	}
}

/*
  ========================================================================
  Description:
	This routine frees all packets in PSQ that's destined to a specific DA.
	BCAST/MCAST in DTIMCount=0 case is also handled here, just like a PS-POLL
	is received from a WSTA which has MAC address FF:FF:FF:FF:FF:FF
  ========================================================================
*/
VOID RtmpHandleRxPsPoll(RTMP_ADAPTER *pAd, UCHAR *pAddr, USHORT wcid, BOOLEAN isActive)
{
	QUEUE_ENTRY *pQEntry;
	MAC_TABLE_ENTRY *pMacEntry;
	unsigned long IrqFlags;

	/*
	   DBGPRINT(RT_DEBUG_TRACE, ("rcv PS-POLL (AID=%d) from %02x:%02x:%02x:%02x:%02x:%02x\n",
	   Aid, PRINT_MAC(pAddr)));
	 */

	pMacEntry = &pAd->MacTab.Content[wcid];
	if (RTMPEqualMemory(pMacEntry->Addr, pAddr, MAC_ADDR_LEN)) {
#ifdef DROP_MASK_SUPPORT
		/* Disable Drop Mask */
		set_drop_mask_per_client(pAd, pMacEntry, 2, 0);
#endif /* DROP_MASK_SUPPORT */

#ifdef PS_ENTRY_MAITENANCE
		pMacEntry->continuous_ps_count = 0;
#endif /* PS_ENTRY_MAITENANCE */

		/* Sta is change to Power Active stat. Reset ContinueTxFailCnt */
		pMacEntry->ContinueTxFailCnt = 0;

#ifdef UAPSD_SUPPORT
		if (UAPSD_MR_IS_ALL_AC_UAPSD(isActive, pMacEntry)) {
			/*
			   IEEE802.11e spec.
			   11.2.1.7 Receive operation for STAs in PS mode during the CP
			   When a non-AP QSTA that is using U-APSD and has all ACs
			   delivery-enabled detects that the bit corresponding to its AID
			   is set in the TIM, the non-AP QSTA shall issue a trigger frame
			   or a PS-Poll frame to retrieve the buffered MSDU or management
			   frames.

			   WMM Spec. v1.1a 070601
			   3.6.2	U-APSD STA Operation
			   3.6.2.3	In case one or more ACs are not
			   delivery-enabled ACs, the WMM STA may retrieve MSDUs and
			   MMPDUs belonging to those ACs by sending PS-Polls to the WMM AP.
			   In case all ACs are delivery enabled ACs, WMM STA should only
			   use trigger frames to retrieve MSDUs and MMPDUs belonging to
			   those ACs, and it should not send PS-Poll frames.

			   Different definitions in IEEE802.11e and WMM spec.
			   But we follow the WiFi WMM Spec.
			 */

			DBGPRINT(RT_DEBUG_TRACE, ("All AC are UAPSD, can not use PS-Poll\n"));
			return;	/* all AC are U-APSD, can not use PS-Poll */
		}
#endif /* UAPSD_SUPPORT */

		RTMP_IRQ_LOCK(&pAd->irq_lock, IrqFlags);
		if (isActive == FALSE) {
			if (pMacEntry->PsQueue.Head) {
#ifdef UAPSD_SUPPORT
				UINT32 NumOfOldPsPkt;

				NumOfOldPsPkt = pAd->TxSwQueue[QID_AC_BE].Number;
#endif /* UAPSD_SUPPORT */

				pQEntry = RemoveHeadQueue(&pMacEntry->PsQueue);
				if (pMacEntry->PsQueue.Number >= 1)
					RTMP_SET_PACKET_MOREDATA(RTPKT_TO_OSPKT(pQEntry), TRUE);

#ifdef CONFIG_MULTI_CHANNEL
				if (pAd->Mlme.bStartMcc == TRUE) {
					InsertTailQueueAc(pAd, pMacEntry, &pAd->TxSwQueue[QID_HCCA],
							  pQEntry);
				} else
#endif /* CONFIG_MULTI_CHANNEL */
				{
					InsertTailQueueAc(pAd, pMacEntry,
							  &pAd->TxSwQueue[QID_AC_BE], pQEntry);
				}
#ifdef UAPSD_SUPPORT
				/* we need to call RTMPDeQueuePacket() immediately as below */
				if (NumOfOldPsPkt != pAd->TxSwQueue[QID_AC_BE].Number) {
					if (RTMP_GET_PACKET_DHCP(RTPKT_TO_OSPKT(pQEntry)) ||
					    RTMP_GET_PACKET_EAPOL(RTPKT_TO_OSPKT(pQEntry)) ||
					    RTMP_GET_PACKET_WAI(RTPKT_TO_OSPKT(pQEntry))) {
						/*
						   These packets will use 1M/6M rate to send.
						   If you use 1M(2.4G)/6M(5G) to send, no statistics
						   count in NICUpdateFifoStaCounters().

						   So we can not count it for UAPSD; Or the SP will
						   not closed until timeout.
						 */
					} else
						UAPSD_MR_MIX_PS_POLL_RCV(pAd, pMacEntry);
				}
#endif /* UAPSD_SUPPORT */
			} else {
				/*
				   or transmit a (QoS) Null Frame;

				   In addtion, in Station Keep Alive mechanism, we need to
				   send a QoS Null frame to detect the station live status.
				 */
				BOOLEAN bQosNull = FALSE;

				if (CLIENT_STATUS_TEST_FLAG(pMacEntry, fCLIENT_STATUS_WMM_CAPABLE))
					bQosNull = TRUE;

				RtmpEnqueueNullFrame(pAd, pMacEntry->Addr, pMacEntry->CurrTxRate,
						     pMacEntry->Aid, pMacEntry->apidx,
						     bQosNull, TRUE, 0);
			}
		} else {
#ifdef UAPSD_SUPPORT
			/* deliver all queued UAPSD packets */
			UAPSD_AllPacketDeliver(pAd, pMacEntry);

			/* end the SP if exists */
			UAPSD_MR_ENTRY_RESET(pAd, pMacEntry);
#endif /* UAPSD_SUPPORT */

			while (pMacEntry->PsQueue.Head) {
				pQEntry = RemoveHeadQueue(&pMacEntry->PsQueue);
#ifdef CONFIG_MULTI_CHANNEL
				if (pAd->Mlme.bStartMcc == TRUE) {
					InsertTailQueueAc(pAd, pMacEntry, &pAd->TxSwQueue[QID_HCCA],
							  pQEntry);
				} else
#endif /* CONFIG_MULTI_CHANNEL */
				{
					InsertTailQueueAc(pAd, pMacEntry,
							  &pAd->TxSwQueue[QID_AC_BE], pQEntry);
				}
			}
		}

		if ((pMacEntry->Aid > 0) && (pMacEntry->Aid < MAX_LEN_OF_MAC_TABLE) &&
		    (pMacEntry->PsQueue.Number == 0)) {
			/* clear corresponding TIM bit because no any PS packet */
#ifdef CONFIG_AP_SUPPORT
			if (pMacEntry->wdev->wdev_type == WDEV_TYPE_AP)
				WLAN_MR_TIM_BIT_CLEAR(pAd, pMacEntry->apidx, pMacEntry->Aid);
#endif /* CONFIG_AP_SUPPORT */
			pMacEntry->PsQIdleCount = 0;
		}

		RTMP_IRQ_UNLOCK(&pAd->irq_lock, IrqFlags);

		/*
		   Dequeue outgoing frames from TxSwQueue0..3 queue and process it
		   TODO: 2004-12-27 it's not a good idea to handle "More Data" bit here.
		   because the RTMPDeQueue process doesn't guarantee to de-queue the
		   desired MSDU from the corresponding TxSwQueue/PsQueue when QOS
		   in-used. We should consider "HardTransmt" this MPDU using MGMT
		   queue or things like that.
		 */
		RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, MAX_TX_PROCESS);
	} else {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("rcv PS-POLL (AID=%d not match) from %02x:%02x:%02x:%02x:%02x:%02x\n",
			  pMacEntry->Aid, PRINT_MAC(pAddr)));

	}
}

/*
	==========================================================================
	Description:
		Update the station current power save mode. Calling this routine also
		prove the specified client is still alive. Otherwise AP will age-out
		this client once IdleCount exceeds a threshold.
	==========================================================================
 */
BOOLEAN RtmpPsIndicate(RTMP_ADAPTER *pAd, UCHAR *pAddr, UCHAR wcid, UCHAR Psm)
{
	MAC_TABLE_ENTRY *pEntry;
	UCHAR old_psmode;

	if (wcid >= MAX_LEN_OF_MAC_TABLE)
		return PWR_ACTIVE;

	pEntry = &pAd->MacTab.Content[wcid];
	old_psmode = pEntry->PsMode;

	/*
	   Change power save mode first because we will call
	   RTMPDeQueuePacket() in RtmpHandleRxPsPoll().

	   Or when Psm = PWR_ACTIVE, we will not do Aggregation in
	   RTMPDeQueuePacket().
	 */
	pEntry->NoDataIdleCount = 0;
	pEntry->PsMode = Psm;

	if (old_psmode != Psm) {
		DBGPRINT(RT_DEBUG_INFO, ("%s():%02x:%02x:%02x:%02x:%02x:%02x %s!\n",
					 __func__, PRINT_MAC(pAddr),
					 (Psm ==
					  PWR_SAVE ? "Sleep" : "wakes up, act like rx PS-POLL")));
	}

	if ((old_psmode == PWR_SAVE) && (Psm == PWR_ACTIVE)) {
#ifdef DROP_MASK_SUPPORT
		/* Disable Drop Mask */
		set_drop_mask_per_client(pAd, pEntry, 2, 0);
#endif /* DROP_MASK_SUPPORT */

#ifdef PS_ENTRY_MAITENANCE
		pEntry->continuous_ps_count = 0;
#endif /* PS_ENTRY_MAITENANCE */


		/* sleep station awakes, move all pending frames from PSQ to TXQ if any */
		RtmpHandleRxPsPoll(pAd, pAddr, pEntry->wcid, TRUE);
	}
#ifdef DROP_MASK_SUPPORT
	else if ((old_psmode == PWR_ACTIVE) && (Psm == PWR_SAVE)) {
		/* Enable Drop Mask */
		set_drop_mask_per_client(pAd, pEntry, 2, 1);
	}
#endif /* DROP_MASK_SUPPORT */

	return old_psmode;
}

#ifdef CONFIG_STA_SUPPORT
/*
========================================================================
Routine Description:
    Check if PM of any packet is set.

Arguments:
	pAd		Pointer to our adapter

Return Value:
    TRUE	can set
	FALSE	can not set

Note:
========================================================================
*/
BOOLEAN RtmpPktPmBitCheck(RTMP_ADAPTER *pAd)
{
	BOOLEAN FlgCanPmBitSet = TRUE;

#ifdef DOT11Z_TDLS_SUPPORT
	/* check TDLS condition */
	if (pAd->StaCfg.TdlsInfo.TdlsFlgIsKeepingActiveCountDown == TRUE)
		FlgCanPmBitSet = FALSE;
#endif /* DOT11Z_TDLS_SUPPORT */

	if (FlgCanPmBitSet == TRUE)
		return (pAd->StaCfg.Psm == PWR_SAVE);

	return FALSE;
}

VOID RtmpPsActiveExtendCheck(RTMP_ADAPTER *pAd)
{
	/* count down the TDLS active counter */
#ifdef DOT11Z_TDLS_SUPPORT
	if (pAd->StaCfg.TdlsInfo.TdlsPowerSaveActiveCountDown > 0) {
		pAd->StaCfg.TdlsInfo.TdlsPowerSaveActiveCountDown--;

		if (pAd->StaCfg.TdlsInfo.TdlsPowerSaveActiveCountDown == 0) {
			/* recover our power save state */
			TDLS_RECOVER_POWER_SAVE(pAd);
			DBGPRINT(RT_DEBUG_TRACE, ("TDLS PS> Recover PS mode!\n"));
		}
	}
#endif /* DOT11Z_TDLS_SUPPORT */
}

VOID RtmpPsModeChange(RTMP_ADAPTER *pAd, UINT32 PsMode)
{
	if (pAd->StaCfg.BssType == BSS_INFRA) {
		/* reset ps mode */
		if (PsMode == Ndis802_11PowerModeMAX_PSP) {
			/* do NOT turn on PSM bit here, wait until MlmeCheckForPsmChange() */
			/* to exclude certain situations. */
			/* MlmeSetPsm(pAd, PWR_SAVE); */
			OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
			if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
				pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeMAX_PSP;
			pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeMAX_PSP;
			pAd->StaCfg.DefaultListenCount = 5;
		} else if (PsMode == Ndis802_11PowerModeFast_PSP) {
			/* do NOT turn on PSM bit here, wait until MlmeCheckForPsmChange() */
			/* to exclude certain situations. */
			OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
			if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
				pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeFast_PSP;
			pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeFast_PSP;
			pAd->StaCfg.DefaultListenCount = 3;
		} else if (PsMode == Ndis802_11PowerModeLegacy_PSP) {
			/* do NOT turn on PSM bit here, wait until MlmeCheckForPsmChange() */
			/* to exclude certain situations. */
			OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
			if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
				pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeLegacy_PSP;
			pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeLegacy_PSP;
#if defined(DOT11Z_TDLS_SUPPORT) || defined(CFG_TDLS_SUPPORT)
			pAd->StaCfg.DefaultListenCount = 1;
#else
			pAd->StaCfg.DefaultListenCount = 3;
#endif /* defined(DOT11Z_TDLS_SUPPORT) || defined(CFG_TDLS_SUPPORT) // */
		} else {	/* Default Ndis802_11PowerModeCAM */
			/* clear PSM bit immediately */
			RTMP_SET_PSM_BIT(pAd, PWR_ACTIVE);
			OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
			if (pAd->StaCfg.bWindowsACCAMEnable == FALSE)
				pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeCAM;
			pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeCAM;
		}

		/* change ps mode */
		RTMPSendNullFrame(pAd, pAd->CommonCfg.TxRate, TRUE, FALSE);

		DBGPRINT(RT_DEBUG_TRACE, ("PSMode=%ld\n", pAd->StaCfg.WindowsPowerMode));
	}
}
#endif /* CONFIG_STA_SUPPORT */
