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

	All related WMM UAPSD definitions & function prototype.

***************************************************************************/
#ifndef __UAPSD_H__
#define __UAPSD_H__
/* only for UAPSD_TIMING_RECORD */


#define UAPSD_TIMING_RECORD_MAX				1000
#define UAPSD_TIMING_RECORD_DISPLAY_TIMES	10

#define UAPSD_QUEUE_TIMEOUT					5	/* unit: seconds */

#define UAPSD_TIMING_RECORD_ISR				1
#define UAPSD_TIMING_RECORD_TASKLET			2
#define UAPSD_TIMING_RECORD_TRG_RCV			3
#define UAPSD_TIMING_RECORD_MOVE2TX			4
#define UAPSD_TIMING_RECORD_TX2AIR			5

#define UAPSD_TIMING_CTRL_STOP				0
#define UAPSD_TIMING_CTRL_START				1
#define UAPSD_TIMING_CTRL_SUSPEND			2

#ifdef UAPSD_TIMING_RECORD_FUNC
#define UAPSD_TIMING_RECORD_START() (UAPSD_TimingRecordCtrl(UAPSD_TIMING_CTRL_START))
#define UAPSD_TIMING_RECORD_STOP()  (UAPSD_TimingRecordCtrl(UAPSD_TIMING_CTRL_STOP))
#define UAPSD_TIMING_RECORD(__pAd, __Type) (UAPSD_TimingRecord(__pAd, __Type))
#define UAPSD_TIMING_RECORD_INDEX(__LoopIndex) (UAPSD_TimeingRecordLoopIndex(__LoopIndex))
#else

#define UAPSD_TIMING_RECORD_START()
#define UAPSD_TIMING_RECORD_STOP()
#define UAPSD_TIMING_RECORD(__pAd, __type)
#define UAPSD_TIMING_RECORD_INDEX(__LoopIndex)
#endif /* UAPSD_TIMING_RECORD_FUNC */

/* timing */
#define UAPSD_TIMESTAMP_GET(__pAd, __TimeStamp)			\
	{													\
		UINT32 __CSR = 0;	UINT64 __Value64;				\
		RTMP_IO_READ32((__pAd), TSF_TIMER_DW0, &__CSR);	\
		__TimeStamp = (UINT64)__CSR;					\
		RTMP_IO_READ32((__pAd), TSF_TIMER_DW1, &__CSR);	\
		__Value64 = (UINT64)__CSR;						\
		__TimeStamp |= (__Value64 << 32);				\
	}


#define UAPSD_TIME_GET(__pAd, __Time)					\
	{													\
		NdisGetSystemUpTime(&__Time);					\
	}

/* uapsd packet */
#ifdef VENDOR_FEATURE3_SUPPORT
#define UAPSD_INSERT_QUEUE_AC	UAPSD_InsertTailQueueAc
#else
#define UAPSD_INSERT_QUEUE_AC	InsertTailQueueAc
#endif /* VENDOR_FEATURE3_SUPPORT */

/* uapsd initialization */
#define UAPSD_INFO_INIT(__pInfo)						\
{														\
	(__pInfo)->bAPSDCapable = FALSE;					\
}

#define UAPSD_SP_START(__pAd, __pEntry) (pEntry->bAPSDFlagSPStart = 1)

#ifdef CONFIG_STA_SUPPORT
#define UAPSD_SP_END(__pAd, __pEntry)					\
	do {						    \
		__pEntry->bAPSDFlagSPStart = 0;					\
		RtmpAsicSleepHandle(__pAd);			\
	} while (0)
#else
/* for AP, we maybe sleep until all SPs are closed */
#define UAPSD_SP_END(__pAd, __pEntry) (__pEntry->bAPSDFlagSPStart = 0)
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_STA_SUPPORT

/* ASIC power save behavior */
/* TODO: maybe need to do protection */
#define ASIC_PS_CAN_SLEEP(__pAd)     (__pAd->StaCfg.FlgPsmCanNotSleep = FALSE)

#define ASIC_PS_CAN_NOT_SLEEP(__pAd) (__pAd->StaCfg.FlgPsmCanNotSleep = TRUE)

/* we will recover ps mode after 5 second if no packet is received. */
#define RTMP_PS_VIRTUAL_MAX_TIME_OUT		5

/* reset virtual ps mode timeout when we receive any packet from the peer */
#define RTMP_PS_VIRTUAL_TIMEOUT_RESET(__pMacEntry)							\
	do {									\
		if (__pMacEntry->VirtualTimeout > 0)				\
			__pMacEntry->VirtualTimeout = RTMP_PS_VIRTUAL_MAX_TIME_OUT;	\
	} while (0)

/* wake up the peer virtually */
#define RTMP_PS_VIRTUAL_WAKEUP_PEER(__pMacEntry)							\
{									    \
	__pMacEntry->FlgPsModeIsWakeForAWhile = TRUE;							\
	__pMacEntry->VirtualTimeout = RTMP_PS_VIRTUAL_MAX_TIME_OUT;				\
	DBGPRINT(RT_DEBUG_TRACE,						\
		("%02x:%02x:%02x:%02x:%02x:%02x will not sleep for a while!\n",		\
		__pMacEntry->Addr[0], __pMacEntry->Addr[1], __pMacEntry->Addr[2],	\
		__pMacEntry->Addr[3], __pMacEntry->Addr[4], __pMacEntry->Addr[5])); \
}
#endif /* CONFIG_STA_SUPPORT */

/* recover the peer power save mode virtually */
#define RTMP_PS_VIRTUAL_SLEEP(__pMacEntry)									\
{									    \
	__pMacEntry->FlgPsModeIsWakeForAWhile = FALSE;				\
	__pMacEntry->VirtualTimeout = 0;					\
	DBGPRINT(RT_DEBUG_TRACE,						\
		("%02x:%02x:%02x:%02x:%02x:%02x can sleep (ps mode = %d)!\n",		\
		__pMacEntry->Addr[0], __pMacEntry->Addr[1], __pMacEntry->Addr[2],	\
		__pMacEntry->Addr[3], __pMacEntry->Addr[4], __pMacEntry->Addr[5],	\
		__pMacEntry->PsMode));						    \
}

/* check if the peer virtual ps mode timeout */
#define RTMP_PS_VIRTUAL_TIMEOUT_HANDLE(__pMacEntry)							\
{									    \
	if (__pMacEntry->VirtualTimeout > 0) {					\
		__pMacEntry->VirtualTimeout--;					    \
		if (__pMacEntry->VirtualTimeout == 0) {				    \
			DBGPRINT(RT_DEBUG_TRACE,					\
					("tdls uapsd> virtual ps timeout!\n"));					\
			RTMP_PS_VIRTUAL_SLEEP(__pMacEntry);				\
		}								    \
	}									\
}

/* Public Marco list */

/*
	Init some parameters in packet structure for QoS Null frame;
	purpose: is for management frame tx done use
*/
#define UAPSD_MR_QOS_NULL_HANDLE(__pAd, __pData, __pPacket)					\
	{									\
		PHEADER_802_11 __pHeader = (PHEADER_802_11)(__pData);				\
		MAC_TABLE_ENTRY *__pEntry;					    \
		if (__pHeader->FC.SubType == SUBTYPE_QOS_NULL) {		    \
			RTMP_SET_PACKET_QOS_NULL((__pPacket));							\
			__pEntry = MacTableLookup((__pAd), __pHeader->Addr1);			\
			if (__pEntry != NULL)						\
				RTMP_SET_PACKET_WCID((__pPacket), __pEntry->wcid);			\
		} else {							    \
			RTMP_SET_PACKET_NON_QOS_NULL((__pPacket));						\
		}								    \
	}

/*
	Init MAC entry UAPSD parameters;
	purpose: initialize UAPSD PS queue and control parameters
*/
#define UAPSD_MR_ENTRY_INIT(__pEntry)										\
	{									\
		UINT16	__IdAc;							    \
		for (__IdAc = 0; __IdAc < WMM_NUM_OF_AC; __IdAc++)		    \
			InitializeQueueHeader(&(__pEntry)->UAPSDQueue[__IdAc]);			\
		(__pEntry)->UAPSDTxNum = 0;					    \
		(__pEntry)->pUAPSDEOSPFrame = NULL;				    \
		(__pEntry)->bAPSDFlagSPStart = 0;				    \
		(__pEntry)->bAPSDFlagEOSPOK = 0;				    \
		(__pEntry)->MaxSPLength = 0;					    \
		DBGPRINT(RT_DEBUG_TRACE, ("uapsd> MaxSPLength = 0!\n"));			\
	}

/*
	Reset MAC entry UAPSD parameters;
   purpose: clean all UAPSD PS queue; release the EOSP frame if exists;
			reset control parameters
*/
#define UAPSD_MR_ENTRY_RESET(__pAd, __pEntry)								\
	{									\
		MAC_TABLE_ENTRY *__pSta;					    \
		UINT32 __IdAc;							    \
		__pSta = (__pEntry);						    \
		/* clear all U-APSD queues */						   \
		for (__IdAc = 0; __IdAc < WMM_NUM_OF_AC; __IdAc++)	\
			RtmpCleanupPsQueue((__pAd), &__pSta->UAPSDQueue[__IdAc]);		\
		/* clear EOSP frame */							 \
		__pSta->UAPSDTxNum = 0;						    \
		if (__pSta->pUAPSDEOSPFrame != NULL) {								\
			RELEASE_NDIS_PACKET((__pAd),					\
							QUEUE_ENTRY_TO_PACKET(__pSta->pUAPSDEOSPFrame),	\
							NDIS_STATUS_FAILURE);		      \
		__pSta->pUAPSDEOSPFrame = NULL; }				     \
		__pSta->bAPSDFlagSPStart = 0;					    \
		__pSta->bAPSDFlagEOSPOK = 0;					    \
		UAPSD_SP_END(__pAd, __pSta);					    \
		DBGPRINT(RT_DEBUG_INFO, ("uapsd> clear UAPSD queues!\n")); }

/*
 * we can not use bMoreData bit to get EOSP bit because
 * maybe bMoreData = 1 & EOSP = 1 when Max SP Length != 0
 */
#define UAPSD_MR_EOSP_SET(__pQosCtrl, __pTxBlk)								\
	do {									\
		if (CLIENT_STATUS_TEST_FLAG((__pTxBlk)->pMacEntry,		\
				fCLIENT_STATUS_APSD_CAPABLE)) {				    \
			if (TX_BLK_TEST_FLAG((__pTxBlk), fTX_bWMM_UAPSD_EOSP))		    \
				*(__pQosCtrl) |= (1 << 4);				    \
	}									\
	} while (0)

/*
	Enable or disable UAPSD flag in WMM element in beacon frame;
	purpose: set UAPSD enable/disable bit
*/
#define UAPSD_MR_IE_FILL(__QosCtrlField, __pUapsdInfo)						\
		((__QosCtrlField) |= ((__pUapsdInfo)->bAPSDCapable) ? 0x80 : 0x00)

/*
	Check if we do NOT need to control TIM bit for the station;
	note: we control TIM bit only when all AC are UAPSD AC
*/
#define UAPSD_MR_IS_NOT_TIM_BIT_NEEDED_HANDLED(__pMacEntry, __QueIdx)		\
		(CLIENT_STATUS_TEST_FLAG((__pMacEntry), fCLIENT_STATUS_APSD_CAPABLE) && \
			(!(__pMacEntry)->bAPSDDeliverEnabledPerAC[QID_AC_VO] ||			\
			!(__pMacEntry)->bAPSDDeliverEnabledPerAC[QID_AC_VI] ||			\
			!(__pMacEntry)->bAPSDDeliverEnabledPerAC[QID_AC_BE] ||			\
			!(__pMacEntry)->bAPSDDeliverEnabledPerAC[QID_AC_BK]) &&			\
		(__pMacEntry)->bAPSDDeliverEnabledPerAC[__QueIdx])

/* check if the AC is UAPSD delivery-enabled AC */
#define UAPSD_MR_IS_UAPSD_AC(__pMacEntry, __AcId)							\
		(CLIENT_STATUS_TEST_FLAG((__pMacEntry), fCLIENT_STATUS_APSD_CAPABLE) &&	\
			((0 <= (__AcId)) && ((__AcId) < WMM_NUM_OF_AC)) && /* 0 ~ 3 */	\
			(__pMacEntry)->bAPSDDeliverEnabledPerAC[(__AcId)])

/* check if all AC are UAPSD delivery-enabled AC */
#define UAPSD_MR_IS_ALL_AC_UAPSD(__FlgIsActive, __pMacEntry)				\
		(((__FlgIsActive) == FALSE) && ((__pMacEntry)->bAPSDAllAC == 1))

/* suspend SP */
#define UAPSD_MR_SP_SUSPEND(__pAd)((__pAd)->bAPSDFlagSPSuspend = 1)

/* resume SP */
#define UAPSD_MR_SP_RESUME(__pAd) ((__pAd)->bAPSDFlagSPSuspend = 0)

/* mark PS poll frame sent in mix mode */

#ifdef RTMP_MAC_USB
#define UAPSD_MR_MIX_PS_POLL_RCV(__pAd, __pMacEntry)
#endif /* RTMP_MAC_USB */

#define UAPSD_EXTERN
#define UAPSD_QOS_NULL_QUE_ID	0x7f


#define UAPSD_EPT_SP_INT		(100000/(1000000/OS_HZ))	/* 100ms */

/* max UAPSD buffer queue size */
#define MAX_PACKETS_IN_UAPSD_QUEUE	16	/* for each AC = 16*4 = 64 */

/* Public function list */
/*
========================================================================
Routine Description:
	UAPSD Module Init.

Arguments:
	pAd		Pointer to our adapter

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_Init(IN PRTMP_ADAPTER pAd);

/*
========================================================================
Routine Description:
	UAPSD Module Release.

Arguments:
	pAd		Pointer to our adapter

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_Release(IN PRTMP_ADAPTER pAd);


/*
========================================================================
Routine Description:
    Check if ASIC can enter sleep mode. Not software sleep.

Arguments:
	pAd		Pointer to our adapter

Return Value:
    None

Note:
========================================================================
*/
UAPSD_EXTERN VOID RtmpAsicSleepHandle(IN PRTMP_ADAPTER pAd);

/*
========================================================================
Routine Description:
	Close current Service Period.

Arguments:
	pAd				Pointer to our adapter
	pEntry			Close the SP of the entry

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_SP_Close(IN PRTMP_ADAPTER pAd, IN MAC_TABLE_ENTRY *pEntry);

/*
========================================================================
Routine Description:
	Check if the SP for entry is closed.

Arguments:
	pAd				Pointer to our adapter
	pEntry			the peer entry

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN BOOLEAN UAPSD_SP_IsClosed(IN PRTMP_ADAPTER pAd, IN MAC_TABLE_ENTRY *pEntry);

/*
========================================================================
Routine Description:
	Deliver all queued packets.

Arguments:
	pAd	       Pointer to our adapter
	*pEntry	       STATION

Return Value:
	None

Note:
	SMP protection by caller for packet enqueue.
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_AllPacketDeliver(IN PRTMP_ADAPTER pAd, IN MAC_TABLE_ENTRY *pEntry);

/*
========================================================================
Routine Description:
	Parse the UAPSD field in WMM element in (re)association request frame.

Arguments:
	pAd				Pointer to our adapter
	*pEntry			STATION
	*pElm			QoS information field
	FlgApsdCapable	TRUE: Support UAPSD

Return Value:
	None

Note:
	No protection is needed.

	1. Association -> TSPEC:
		use static UAPSD settings in Association
		update UAPSD settings in TSPEC

	2. Association -> TSPEC(11r) -> Reassociation:
		update UAPSD settings in TSPEC
		backup static UAPSD settings in Reassociation

	3. Association -> Reassociation:
		update UAPSD settings in TSPEC
		backup static UAPSD settings in Reassociation
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_AssocParse(IN PRTMP_ADAPTER pAd,
				   IN MAC_TABLE_ENTRY *pEntry,
				   IN UCHAR * pElm, IN BOOLEAN FlgApsdCapable);

/*
========================================================================
Routine Description:
	Enqueue a UAPSD packet.

Arguments:
	pAd				Pointer to our adapter
	*pEntry			STATION
	pPacket			UAPSD dnlink packet
	IdAc			UAPSD AC ID (0 ~ 3)

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_PacketEnqueue(IN PRTMP_ADAPTER pAd,
				      IN MAC_TABLE_ENTRY *pEntry,
				      IN PNDIS_PACKET pPacket, IN UINT32 IdAc);

/*
========================================================================
Routine Description:
	Handle QoS Null Frame Tx Done or Management Tx Done interrupt.

Arguments:
	pAd				Pointer to our adapter
	pPacket			Completed TX packet
	pDstMac			Destinated MAC address

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_QoSNullTxMgmtTxDoneHandle(IN PRTMP_ADAPTER pAd,
						  IN PNDIS_PACKET pPacket, IN UCHAR * pDstMac);

/*
========================================================================
Routine Description:
	Maintenance our UAPSD PS queue.	 Release all queued packet if timeout.

Arguments:
	pAd				Pointer to our adapter
	*pEntry			STATION

Return Value:
	None

Note:
	If in RT2870, pEntry can not be removed during UAPSD_QueueMaintenance()
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_QueueMaintenance(IN PRTMP_ADAPTER pAd, IN MAC_TABLE_ENTRY *pEntry);

/*
========================================================================
Routine Description:
	Close SP in Tx Done, not Tx DMA Done.

Arguments:
	pAd	       Pointer to our adapter
	pEntry			destination entry
	FlgSuccess		0:tx success, 1:tx fail

Return Value:
    None

Note:
	For RT28xx series, for packetID=0 or multicast frame, no statistics
	count can be got, ex: ARP response or DHCP packets, we will use
	low rate to set (CCK, MCS=0=packetID).
	So SP will not be close until UAPSD_EPT_SP_INT timeout.

	So if the tx rate is 1Mbps for a entry, we will use DMA done, not
	use UAPSD_SP_AUE_Handle().
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_SP_AUE_Handle(IN RTMP_ADAPTER * pAd,
				      IN MAC_TABLE_ENTRY *pEntry, IN UCHAR FlgSuccess);

/*
========================================================================
Routine Description:
	Close current Service Period.

Arguments:
	pAd				Pointer to our adapter

Return Value:
	None

Note:
	When we receive EOSP frame tx done interrupt and a uplink packet
	from the station simultaneously, we will regard it as a new trigger
	frame because the packet is received when EOSP frame tx done interrupt.

	We can not sure the uplink packet is sent after old SP or in the old SP.
	So we must close the old SP in receive done ISR to avoid the problem.
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_SP_CloseInRVDone(IN PRTMP_ADAPTER pAd);

/*
========================================================================
Routine Description:
	Check if we need to close current SP.

Arguments:
	pAd				Pointer to our adapter
	pPacket			Completed TX packet
	pDstMac			Destinated MAC address

Return Value:
	None

Note:
	1. We need to call the function in TxDone ISR.
	2. SMP protection by caller for packet enqueue.
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_SP_PacketCheck(IN PRTMP_ADAPTER pAd,
				       IN PNDIS_PACKET pPacket, IN UCHAR * pDstMac);

#ifdef UAPSD_TIMING_RECORD_FUNC
/*
========================================================================
Routine Description:
	Enable/Disable Timing Record Function.

Arguments:
	pAd				Pointer to our adapter
	Flag			1 (Enable) or 0 (Disable)

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_TimingRecordCtrl(IN UINT32 Flag);

/*
========================================================================
Routine Description:
	Record some timings.

Arguments:
	pAd				Pointer to our adapter
	Type			The timing is for what type

Return Value:
	None

Note:
	UAPSD_TIMING_RECORD_ISR
	UAPSD_TIMING_RECORD_TASKLET
	UAPSD_TIMING_RECORD_TRG_RCV
	UAPSD_TIMING_RECORD_MOVE2TX
	UAPSD_TIMING_RECORD_TX2AIR
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_TimingRecord(IN PRTMP_ADAPTER pAd, IN UINT32 Type);

/*
========================================================================
Routine Description:
	Record the loop index for received packet handle.

Arguments:
	pAd				Pointer to our adapter
	LoopIndex		The RxProcessed in rtmp_rx_done_handle()

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_TimeingRecordLoopIndex(IN UINT32 LoopIndex);
#endif /* UAPSD_TIMING_RECORD_FUNC */

/*
========================================================================
Routine Description:
    Handle PS-Poll Frame.

Arguments:
	pAd				Pointer to our adapter
	*pEntry			the source STATION

Return Value:
    TRUE			Handle OK
	FALSE			Handle FAIL

Note:
========================================================================
*/
BOOLEAN UAPSD_PsPollHandle(RTMP_ADAPTER * pAd, MAC_TABLE_ENTRY *pEntry);

/*
========================================================================
Routine Description:
    Get the queue status for delivery-enabled AC.

Arguments:
	pAd					Pointer to our adapter
	pEntry				the peer entry
	pFlgIsAnyPktForBK	TRUE: At lease a BK packet is queued
	pFlgIsAnyPktForBE	TRUE: At lease a BE packet is queued
	pFlgIsAnyPktForVI	TRUE: At lease a VI packet is queued
	pFlgIsAnyPktForVO	TRUE: At lease a VO packet is queued

Return Value:
    None

Note:
========================================================================
*/
VOID UAPSD_QueueStatusGet(IN PRTMP_ADAPTER pAd,
			  IN MAC_TABLE_ENTRY *pEntry,
			  OUT BOOLEAN *pFlgIsAnyPktForBK,
			  OUT BOOLEAN *pFlgIsAnyPktForBE,
			  OUT BOOLEAN * pFlgIsAnyPktForVI, OUT BOOLEAN *pFlgIsAnyPktForVO);

/*
========================================================================
Routine Description:
	Handle UAPSD Trigger Frame.

Arguments:
	pAd				Pointer to our adapter
	*pEntry			the source STATION
	UpOfFrame		the UP of the trigger frame

Return Value:
	None

Note:
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_TriggerFrameHandle(IN PRTMP_ADAPTER pAd,
					   IN MAC_TABLE_ENTRY *pEntry, IN UCHAR UpOfFrame);

#ifdef RTMP_MAC_USB
/*
========================================================================
Routine Description:
	Tag current offset of the AC in USB URB tx buffer.

Arguments:
	pAd				Pointer to our adapter
	*pPkt			the tx packet
	Wcid			destination entry id
	PktOffset		USB tx buffer offset

Return Value:
    None

Note:
	Only for RT2870.
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_TagFrame(IN RTMP_ADAPTER * pAd,
				 IN NDIS_PACKET * pPkt, IN UCHAR Wcid, IN UINT32 PktOffset);

/*
========================================================================
Routine Description:
	Check if UAPSD packets are tx ok.

Arguments:
	pAd				Pointer to our adapter
	AcQueId			TX completion for the AC (0 ~ 3)
	bulkStartPos
	bulkEnPos

Return Value:
	None

Note:
	Only for RT2870.
========================================================================
*/
UAPSD_EXTERN VOID UAPSD_UnTagFrame(IN RTMP_ADAPTER * pAd,
				   IN UCHAR AcQueId, IN UINT32 bulkStartPos, IN UINT32 bulkEnPos);
#endif /* RTMP_MAC_USB */

#endif /* __UAPSD_H__ */
