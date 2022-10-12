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


#ifdef RTMP_MAC_USB

#include "rt_config.h"

extern UCHAR EpToQueue[];
/* 802.11 MAC Header, Type:Data, Length:24bytes + 6 bytes QOS/HTC + 2 bytes padding */
extern UCHAR TemplateFrame[32];

INT TxDmaBusy(RTMP_ADAPTER *pAd)
{
	INT result;
	USB_DMA_CFG_STRUC UsbCfg;
	BOOLEAN is_busy;

	USB_CFG_READ(pAd, &UsbCfg.word);
#ifdef MT76x2
	if (IS_MT76x2(pAd))
		is_busy = UsbCfg.field_76xx.TxBusy;
	else
#endif /* MT76x2 */
		is_busy = UsbCfg.field.TxBusy;

	result = (is_busy) ? TRUE : FALSE;

	return result;
}

INT RxDmaBusy(RTMP_ADAPTER *pAd)
{
	INT result;
	USB_DMA_CFG_STRUC UsbCfg;
	BOOLEAN is_busy;

	USB_CFG_READ(pAd, &UsbCfg.word);
#ifdef MT76x2
	if (IS_MT76x2(pAd))
		is_busy = UsbCfg.field_76xx.RxBusy;
	else
#endif /* MT76x2 */
		is_busy = UsbCfg.field.RxBusy;

	result = (is_busy) ? TRUE : FALSE;

	return result;
}

VOID RtmpDmaEnable(RTMP_ADAPTER *pAd, INT Enable)
{
	BOOLEAN value;
	ULONG WaitCnt;
	USB_DMA_CFG_STRUC UsbCfg;

	value = Enable > 0 ? 1 : 0;

	/* check DMA is in busy mode. */
	WaitCnt = 0;

	while (TxDmaBusy(pAd) || RxDmaBusy(pAd)) {
		RtmpusecDelay(10);
		if (WaitCnt++ > 100)
			break;
	}

	USB_CFG_READ(pAd, &UsbCfg.word);
#ifdef MT76x2
	if (IS_MT76x2(pAd)) {
		UsbCfg.field_76xx.TxBulkEn = value;
		UsbCfg.field_76xx.RxBulkEn = value;
	} else
#endif /* MT76x2 */
	{
		UsbCfg.field.TxBulkEn = value;
		UsbCfg.field.RxBulkEn = value;
	}

	USB_CFG_WRITE(pAd, UsbCfg.word);
	RtmpOsMsDelay(5);

}

static VOID ATEWriteTxWI(IN PRTMP_ADAPTER pAd, IN TXWI_STRUC * pTxWI, IN BOOLEAN FRAG,
	IN BOOLEAN InsTimestamp, IN BOOLEAN AMPDU, IN BOOLEAN Ack, IN BOOLEAN NSeq,	/* HW new a sequence. */
	IN UCHAR BASize, IN UCHAR WCID, IN ULONG Length, IN UCHAR PID, IN UCHAR MIMOps,
	IN UCHAR Txopmode, IN BOOLEAN CfAck, IN HTTRANSMIT_SETTING Transmit)
{
	OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_SHORT_PREAMBLE_INUSED);
#ifdef RLT_MAC
	if (pAd->chipCap.hif_type == HIF_RLT) {
		struct _TXWI_NMAC *txwi_n = (struct _TXWI_NMAC *)pTxWI;

		txwi_n->FRAG = FRAG;
		txwi_n->TS = InsTimestamp;
		txwi_n->AMPDU = AMPDU;

		txwi_n->MIMOps = PWR_ACTIVE;
		txwi_n->MpduDensity = 4;
		txwi_n->ACK = Ack;
		txwi_n->txop = Txopmode;
		txwi_n->NSEQ = NSeq;
		txwi_n->BAWinSize = BASize;

		txwi_n->wcid = WCID;
		txwi_n->MPDUtotalByteCnt = Length;
		txwi_n->TxPktId = PID;

		txwi_n->BW = Transmit.field.BW;
		txwi_n->ShortGI = Transmit.field.ShortGI;
		txwi_n->STBC = Transmit.field.STBC;

		txwi_n->MCS = Transmit.field.MCS;
		txwi_n->PHYMODE = Transmit.field.MODE;
		txwi_n->CFACK = CfAck;
	}
#endif /* RLT_MAC */

#ifdef RTMP_MAC
	if (pAd->chipCap.hif_type == HIF_RTMP) {
		struct _TXWI_OMAC *txwi_o = (struct _TXWI_OMAC *)pTxWI;

		txwi_o->FRAG = FRAG;
		txwi_o->TS = InsTimestamp;
		txwi_o->AMPDU = AMPDU;

		txwi_o->MIMOps = PWR_ACTIVE;
		txwi_o->MpduDensity = 4;
		txwi_o->ACK = Ack;
		txwi_o->txop = Txopmode;
		txwi_o->NSEQ = NSeq;
		txwi_o->BAWinSize = BASize;

		txwi_o->wcid = WCID;
		txwi_o->MPDUtotalByteCnt = Length;
		txwi_o->PacketId = PID;

		txwi_o->BW = Transmit.field.BW;
		txwi_o->ShortGI = Transmit.field.ShortGI;
		txwi_o->STBC = Transmit.field.STBC;

		txwi_o->MCS = Transmit.field.MCS;
		txwi_o->PHYMODE = Transmit.field.MODE;
		txwi_o->CFACK = CfAck;
	}
#endif /* RTMP_MAC */

}

/*
========================================================================
	Routine	Description:
		Write TxInfo for ATE mode.

	Return Value:
		None
========================================================================
*/
static VOID ATEWriteTxInfo(IN PRTMP_ADAPTER pAd,
			   IN TXINFO_STRUC * pTxInfo,
			   IN USHORT USBDMApktLen,
			   IN BOOLEAN bWiv, IN UCHAR QueueSel, IN UCHAR NextValid, IN UCHAR TxBurst)
{
	rlt_usb_write_txinfo(pAd, pTxInfo, USBDMApktLen, bWiv, QueueSel, NextValid, TxBurst);
}

INT ATESetUpFrame(IN PRTMP_ADAPTER pAd, IN UINT32 TxIdx)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UINT pos = 0;
	PTX_CONTEXT pNullContext;
	PUCHAR pDest;
	HTTRANSMIT_SETTING TxHTPhyMode;
	TXWI_STRUC *pTxWI;
	TXINFO_STRUC *pTxInfo;
	UINT32 TransferBufferLength, OrgBufferLength = 0;
	UCHAR padLen = 0;
	UINT8 TXWISize = pAd->chipCap.TXWISize;
	UCHAR bw, sgi, stbc, mcs, phymode, frag, ts, ampdu, ack, nseq, basize, pid, txop, cfack;
	USHORT mpdu_len;
#ifdef RALINK_QA
	PHEADER_802_11 pHeader80211 = NULL;
#endif /* RALINK_QA */

	bw = sgi = stbc = mcs = phymode = frag = ts = ampdu = ack = nseq = basize = pid = txop =
	    cfack = 0;
	mpdu_len = 0;

	if ((RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS)) ||
	    (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET)) ||
	    (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS)) ||
	    (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		return -1;
	}

	/* We always use QID_AC_BE and FIFO_EDCA in ATE mode. */

	pNullContext = &(pAd->NullContext);
	if (!pNullContext) {
		ASSERT(pNullContext != NULL);
		return -1;
	}

	if (pNullContext->InUse == FALSE) {
		/* set the in use bit */
		pNullContext->InUse = TRUE;
		pATEInfo->HLen = sizeof(HEADER_802_11);
		NdisZeroMemory(&(pAd->NullFrame), sizeof(HEADER_802_11));

		/* fill 802.11 header */
#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			pHeader80211 = NdisMoveMemory(&(pAd->NullFrame),
						      pATEInfo->Header, pATEInfo->HLen);
		} else
#endif /* RALINK_QA */
		{
#ifdef TXBF_SUPPORT
			TemplateFrame[0] = 0x08;	/* Data */
			TemplateFrame[1] = 0x00;
			if (pATEInfo->bTxBF && pATEInfo->txSoundingMode != 0
			    && pATEInfo->TxDoneCount != 0) {
				/* QoS Data */
				pATEInfo->HLen = 30;
				TemplateFrame[0] = 0x88;
				TemplateFrame[1] = 0x80;

				switch (pATEInfo->txSoundingMode) {
				case 1:
					/* Data Sounding */
					TemplateFrame[28] =
					    pAd->CommonCfg.ETxBfNoncompress ? 0x80 : 0xc0;
					TemplateFrame[29] = 0x00;
					break;
				case 2:
				case 3:
					/* 2 or 3 Stream NDP */
					TemplateFrame[28] =
					    pAd->CommonCfg.ETxBfNoncompress ? 0x80 : 0xc0;
					/* NDP Announce */
					TemplateFrame[29] = 0x01;
					break;
				default:
					TemplateFrame[28] = TemplateFrame[29] = 0x0;
				}
			} else
				TemplateFrame[28] = TemplateFrame[29] = 0x0;
#endif /* TXBF_SUPPORT */
			NdisMoveMemory(&(pAd->NullFrame), TemplateFrame, sizeof(HEADER_802_11));
		}

#ifdef RT_BIG_ENDIAN
		RTMPFrameEndianChange(pAd, (PUCHAR) &(pAd->NullFrame), DIR_READ, FALSE);
#endif /* RT_BIG_ENDIAN */

#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			/* modify sequence number... */
			if (pATEInfo->TxDoneCount == 0)
				pATEInfo->seq = pHeader80211->Sequence;
			 else
				pHeader80211->Sequence = ++pATEInfo->seq;
			/* We already got all the address fields from QA GUI. */
		} else
#endif /* RALINK_QA */
		{
			COPY_MAC_ADDR(pAd->NullFrame.Addr1, pATEInfo->Addr1);
			COPY_MAC_ADDR(pAd->NullFrame.Addr2, pATEInfo->Addr2);
			COPY_MAC_ADDR(pAd->NullFrame.Addr3, pATEInfo->Addr3);
		}

		RTMPZeroMemory(&pAd->NullContext.TransferBuffer->field.WirelessPacket[0],
			       TX_BUFFER_NORMSIZE);
		pTxInfo =
		    (TXINFO_STRUC *) &pAd->NullContext.TransferBuffer->field.WirelessPacket[0];

#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			/* Avoid to exceed the range of WirelessPacket[]. */
			ASSERT(pATEInfo->TxInfo.TxInfoPktLen <=
			       (MAX_FRAME_SIZE - 34 /* == 2312 */));
			NdisMoveMemory(pTxInfo, &(pATEInfo->TxInfo), sizeof(pATEInfo->TxInfo));
		} else
#endif /* RALINK_QA */
		{
			/* Avoid to exceed the range of WirelessPacket[]. */
			ASSERT(pATEInfo->TxLength <= (MAX_FRAME_SIZE - 34 /* == 2312 */));

			/* pTxInfo->TxInfoPktLen will be updated to include padding later */
			ATEWriteTxInfo(pAd, pTxInfo, (USHORT) (TXWISize + pATEInfo->TxLength)
				       , TRUE, FIFO_EDCA, FALSE, FALSE);
		}

		pTxWI =
		    (TXWI_STRUC *) &pAd->NullContext.TransferBuffer->field.
		    WirelessPacket[TXINFO_SIZE];

#ifdef RLT_MAC
		if (pAd->chipCap.hif_type == HIF_RLT) {
			bw = pATEInfo->TxWI.TXWI_N.BW;
			sgi = pATEInfo->TxWI.TXWI_N.ShortGI;
			stbc = pATEInfo->TxWI.TXWI_N.STBC;
			mcs = pATEInfo->TxWI.TXWI_N.MCS;
			phymode = pATEInfo->TxWI.TXWI_N.PHYMODE;
			frag = pATEInfo->TxWI.TXWI_N.FRAG;
			ts = pATEInfo->TxWI.TXWI_N.TS;
			ampdu = pATEInfo->TxWI.TXWI_N.AMPDU;
			ack = pATEInfo->TxWI.TXWI_N.ACK;
			nseq = pATEInfo->TxWI.TXWI_N.NSEQ;
			basize = pATEInfo->TxWI.TXWI_N.BAWinSize;
			mpdu_len = pATEInfo->TxWI.TXWI_N.MPDUtotalByteCnt;
			pid = pATEInfo->TxWI.TXWI_N.TxPktId;
			txop = pATEInfo->TxWI.TXWI_N.txop;
			cfack = pATEInfo->TxWI.TXWI_N.CFACK;
		}
#endif /* RLT_MAC */

#ifdef RTMP_MAC
		if (pAd->chipCap.hif_type == HIF_RTMP) {
			bw = pATEInfo->TxWI.TXWI_O.BW;
			sgi = pATEInfo->TxWI.TXWI_O.ShortGI;
			stbc = pATEInfo->TxWI.TXWI_O.STBC;
			mcs = pATEInfo->TxWI.TXWI_O.MCS;
			phymode = pATEInfo->TxWI.TXWI_O.PHYMODE;
			frag = pATEInfo->TxWI.TXWI_O.FRAG;
			ts = pATEInfo->TxWI.TXWI_O.TS;
			ampdu = pATEInfo->TxWI.TXWI_O.AMPDU;
			ack = pATEInfo->TxWI.TXWI_O.ACK;
			nseq = pATEInfo->TxWI.TXWI_O.NSEQ;
			basize = pATEInfo->TxWI.TXWI_O.BAWinSize;
			mpdu_len = pATEInfo->TxWI.TXWI_O.MPDUtotalByteCnt;
			pid = pATEInfo->TxWI.TXWI_O.PacketId;
			txop = pATEInfo->TxWI.TXWI_O.txop;
			cfack = pATEInfo->TxWI.TXWI_O.CFACK;
		}
#endif /* RTMP_MAC */

		/* fill TxWI */
		if (pATEInfo->bQATxStart == TRUE) {
			TxHTPhyMode.field.BW = bw;
			TxHTPhyMode.field.ShortGI = sgi;
			TxHTPhyMode.field.STBC = stbc;
			TxHTPhyMode.field.MCS = mcs;
			TxHTPhyMode.field.MODE = phymode;
			ATEWriteTxWI(pAd, pTxWI, frag, ts,
				     ampdu, ack, nseq,
				     basize, BSSID_WCID, mpdu_len /* include 802.11 header */ ,
				     pid, 0, txop /*IFS_HTTXOP */ , cfack
				      /*FALSE*/, TxHTPhyMode);
#ifdef TXBF_SUPPORT
#ifdef RLT_MAC
			if (IS_MT76x2(pAd)) {
				/* Must copy rsv bits to actual TxWI */
				pTxWI->TXWI_N.Rsv4 = pATEInfo->TxWI.TXWI_N.Rsv4;
				pTxWI->TXWI_N.iTxBF = pATEInfo->TxWI.TXWI_N.iTxBF;
				pTxWI->TXWI_N.Sounding = pATEInfo->TxWI.TXWI_N.Sounding;
				pTxWI->TXWI_N.eTxBF = pATEInfo->TxWI.TXWI_N.eTxBF;
				/* pTxWI->TXWI_N.Autofallback = pATEInfo->TxWI.TXWI_N.
				Autofallback; */
				pTxWI->TXWI_N.NDPSndBW = pATEInfo->TxWI.TXWI_N.NDPSndBW;
				pTxWI->TXWI_N.NDPSndRate = pATEInfo->TxWI.TXWI_N.NDPSndRate;
				pTxWI->TXWI_N.TXBF_PT_SCA = pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
			}
#endif
#endif /* TXBF_SUPPORT */
		} else {
			TxHTPhyMode.field.BW = bw;
			TxHTPhyMode.field.ShortGI = sgi;
			TxHTPhyMode.field.STBC = 0;
			TxHTPhyMode.field.MCS = mcs;
			TxHTPhyMode.field.MODE = phymode;

			ATEWriteTxWI(pAd, pTxWI, FALSE, FALSE, FALSE, FALSE
				     /* No ack required. */ , FALSE, 0, BSSID_WCID,
				     pATEInfo->TxLength, 0, 0, IFS_HTTXOP, FALSE, TxHTPhyMode);
		}
#ifdef TXBF_SUPPORT
		if (pATEInfo->bTxBF == 1) {
#ifdef RLT_MAC
			if (IS_MT76x2(pAd)) {
				pTxWI->TXWI_N.Rsv4 = 0;

				pTxWI->TXWI_N.Sounding = (pATEInfo->txSoundingMode == 1 ? 1 : 0);
				if (pATEInfo->txSoundingMode) {
					pTxWI->TXWI_N.iTxBF = FALSE;
					pTxWI->TXWI_N.eTxBF = FALSE;
				} else {
					pTxWI->TXWI_N.iTxBF = pATEInfo->TxWI.TXWI_N.iTxBF;
					pTxWI->TXWI_N.eTxBF = pATEInfo->TxWI.TXWI_N.eTxBF;
				}
				pTxWI->TXWI_N.NDPSndBW = pATEInfo->TxWI.TXWI_N.BW;
				if (pATEInfo->txSoundingMode == 3) {
					/* pTxWI->TXWI_N.NDPSndRate = 2; */
					pTxWI->TXWI_N.NDPSndRate = 1;
				} else if (pATEInfo->txSoundingMode == 2)
					pTxWI->TXWI_N.NDPSndRate = 1;
				else
					pTxWI->TXWI_N.NDPSndRate = 0;
				pTxWI->TXWI_N.TXBF_PT_SCA = pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
			}
#endif
		}
#endif /* TXBF_SUPPORT */

		RTMPMoveMemory(&pAd->NullContext.TransferBuffer->field.
			       WirelessPacket[TXINFO_SIZE + TXWISize], TemplateFrame,
			       pATEInfo->HLen);
		RTMPMoveMemory(&pAd->NullContext.TransferBuffer->field.
			       WirelessPacket[TXINFO_SIZE + TXWISize], &pAd->NullFrame,
			       sizeof(HEADER_802_11));

		pDest =
		    &(pAd->NullContext.TransferBuffer->field.
		      WirelessPacket[TXINFO_SIZE + TXWISize + pATEInfo->HLen]);

		/* prepare frame payload */
#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			/* copy the pattern one by one to the frame payload */
			if ((pATEInfo->PLen != 0) && (pATEInfo->DLen != 0)) {
				for (pos = 0; pos < pATEInfo->DLen; pos += pATEInfo->PLen) {
					RTMPMoveMemory(pDest, pATEInfo->Pattern, pATEInfo->PLen);
					pDest += pATEInfo->PLen;
				}
			}
			TransferBufferLength = TXINFO_SIZE + TXWISize + mpdu_len;
		} else
#endif /* RALINK_QA */
		{
			for (pos = 0; pos < (pATEInfo->TxLength - pATEInfo->HLen); pos++) {
				if (pos + sizeof(HEADER_802_11) < pATEInfo->HLen) {
					*pDest = TemplateFrame[pos + sizeof(HEADER_802_11)];
				} else if (pATEInfo->bFixedPayload) {
					/* default payload is 0xA5 */
					*pDest = pATEInfo->Payload;
				} else {
					*pDest = RandomByte(pAd);
				}
				pDest += 1;
			}
			TransferBufferLength = TXINFO_SIZE + TXWISize + pATEInfo->TxLength;
		}

		OrgBufferLength = TransferBufferLength;
		TransferBufferLength = (TransferBufferLength + 3) & (~3);

		/* Always add 4 extra bytes at every packet. */
		padLen = TransferBufferLength - OrgBufferLength + 4;	/* 4 == last packet padding */

		/*
		   RTMP_PKT_TAIL_PADDING == 11.
		   [11 == 3(max 4 byte padding) + 4(last packet padding) + 4(MaxBulkOutsize align padding)]
		 */
		ASSERT((padLen <=
			(RTMP_PKT_TAIL_PADDING - 4 /* 4 == MaxBulkOutsize alignment padding */)));

		/* Now memzero all extra padding bytes. */
		NdisZeroMemory(pDest, padLen);
		pDest += padLen;

		/* Update pTxInfo->TxInfoPktLen to include padding. */
		pTxInfo->TxInfoPktLen = TransferBufferLength - TXINFO_SIZE;

		TransferBufferLength += 4;

		/* If TransferBufferLength is multiple of 64, add extra 4 bytes again. */
		if ((TransferBufferLength % pAd->BulkOutMaxPacketSize) == 0) {
			NdisZeroMemory(pDest, 4);
			TransferBufferLength += 4;
		}
		/* Fill out frame length information for global Bulk out arbitor. */
		pAd->NullContext.BulkOutSize = TransferBufferLength;
	}
#ifdef RT_BIG_ENDIAN
	RTMPWIEndianChange(pAd, (PUCHAR) pTxWI, TYPE_TXWI);
	RTMPFrameEndianChange(pAd, (((PUCHAR) pTxInfo) + TXWISize + TXINFO_SIZE), DIR_WRITE, FALSE);
	RTMPDescriptorEndianChange((PUCHAR) pTxInfo, TYPE_TXINFO);
#endif /* RT_BIG_ENDIAN */

	return 0;
}

INT ATESetUpNDPAFrame(IN PRTMP_ADAPTER pAd, IN UINT32 TxIdx)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UINT pos = 0;
	PTX_CONTEXT pNullContext;
	PUCHAR pDest;
	HTTRANSMIT_SETTING TxHTPhyMode;
	TXWI_STRUC *pTxWI;
	TXINFO_STRUC *pTxInfo;
	UINT32 TransferBufferLength, OrgBufferLength = 0;
	UCHAR padLen = 0;
	UINT8 TXWISize = pAd->chipCap.TXWISize;
	UCHAR bw, sgi, stbc, mcs, phymode, frag, ts, ampdu, ack, nseq, basize, pid, txop, cfack;
	USHORT mpdu_len;
	UCHAR *buf;
	VHT_NDPA_FRAME *vht_ndpa;
	SNDING_STA_INFO *sta_info;
#ifdef RALINK_QA
	PHEADER_802_11 pHeader80211 = NULL;
#endif /* RALINK_QA */

	bw = sgi = stbc = mcs = phymode = frag = ts = ampdu = ack = nseq = basize = pid = txop =
	    cfack = 0;
	mpdu_len = 0;

	if ((RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS)) ||
	    (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET)) ||
	    (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS)) ||
	    (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		return -1;
	}

	/* We always use QID_AC_BE and FIFO_EDCA in ATE mode. */

	pNullContext = &(pAd->NullContext);
	if (!pNullContext) {
		ASSERT(pNullContext != NULL);
		return -1;
	}

	if (pNullContext->InUse == FALSE) {
		/* set the in use bit */
		pNullContext->InUse = TRUE;
		NdisZeroMemory(&(pAd->NullFrame), sizeof(HEADER_802_11));

		/* fill 802.11 header */
#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			pHeader80211 = NdisMoveMemory(&(pAd->NullFrame),
						      pATEInfo->Header, pATEInfo->HLen);
		} else
#endif /* RALINK_QA */
		{
#ifdef TXBF_SUPPORT
			buf = (UCHAR *) &pAd->NullFrame;
			vht_ndpa = (VHT_NDPA_FRAME *) buf;
			pATEInfo->HLen = sizeof(VHT_NDPA_FRAME);
			vht_ndpa->fc.Type = FC_TYPE_CNTL;
			vht_ndpa->fc.SubType = SUBTYPE_VHT_NDPA;
			COPY_MAC_ADDR(vht_ndpa->ra, pATEInfo->Addr1);
			COPY_MAC_ADDR(vht_ndpa->ta, pATEInfo->Addr3);
			hex_dump("NDPA Frame", buf, pATEInfo->HLen);
			/* Currnetly we only support 1 STA for a VHT DNPA */
			sta_info = vht_ndpa->sta_info;
			sta_info->aid12 = 1;
			sta_info->fb_type = SNDING_FB_SU;
			sta_info->nc_idx = 0;
			vht_ndpa->token.token_num = 0;
			vht_ndpa->duration = 100;
#endif /* TXBF_SUPPORT */
		}

#ifdef RT_BIG_ENDIAN
		RTMPFrameEndianChange(pAd, (PUCHAR) &(pAd->NullFrame), DIR_READ, FALSE);
#endif /* RT_BIG_ENDIAN */

#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			/* modify sequence number... */
			if (pATEInfo->TxDoneCount == 0)
				pATEInfo->seq = pHeader80211->Sequence;
			else
				pHeader80211->Sequence = ++pATEInfo->seq;
			/* We already got all the address fields from QA GUI. */
		} else
#endif /* RALINK_QA */

			RTMPZeroMemory(&pAd->NullContext.TransferBuffer->field.WirelessPacket[0],
				       TX_BUFFER_NORMSIZE);
		pTxInfo =
		    (TXINFO_STRUC *) &pAd->NullContext.TransferBuffer->field.WirelessPacket[0];

#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			/* Avoid to exceed the range of WirelessPacket[]. */
			ASSERT(pATEInfo->TxInfo.TxInfoPktLen <=
			       (MAX_FRAME_SIZE - 34 /* == 2312 */));
			NdisMoveMemory(pTxInfo, &(pATEInfo->TxInfo), sizeof(pATEInfo->TxInfo));
		} else
#endif /* RALINK_QA */
		{
			/* Avoid to exceed the range of WirelessPacket[]. */
			ASSERT(pATEInfo->TxLength <= (MAX_FRAME_SIZE - 34 /* == 2312 */));

			/* pTxInfo->TxInfoPktLen will be updated to include padding later */
			ATEWriteTxInfo(pAd, pTxInfo, (USHORT) (TXWISize + pATEInfo->TxLength)
				       , TRUE, FIFO_EDCA, FALSE, FALSE);
		}

		pTxWI =
		    (TXWI_STRUC *) &pAd->NullContext.TransferBuffer->field.
		    WirelessPacket[TXINFO_SIZE];

#ifdef RLT_MAC
		if (pAd->chipCap.hif_type == HIF_RLT) {
			bw = pATEInfo->TxWI.TXWI_N.BW;
			sgi = pATEInfo->TxWI.TXWI_N.ShortGI;
			stbc = pATEInfo->TxWI.TXWI_N.STBC;
			mcs = pATEInfo->TxWI.TXWI_N.MCS;
			phymode = pATEInfo->TxWI.TXWI_N.PHYMODE;
			frag = pATEInfo->TxWI.TXWI_N.FRAG;
			ts = pATEInfo->TxWI.TXWI_N.TS;
			ampdu = pATEInfo->TxWI.TXWI_N.AMPDU;
			ack = pATEInfo->TxWI.TXWI_N.ACK;
			nseq = pATEInfo->TxWI.TXWI_N.NSEQ;
			basize = pATEInfo->TxWI.TXWI_N.BAWinSize;
			mpdu_len = pATEInfo->TxWI.TXWI_N.MPDUtotalByteCnt;
			pid = pATEInfo->TxWI.TXWI_N.TxPktId;
			txop = pATEInfo->TxWI.TXWI_N.txop;
			cfack = pATEInfo->TxWI.TXWI_N.CFACK;
		}
#endif /* RLT_MAC */

#ifdef RTMP_MAC
		if (pAd->chipCap.hif_type == HIF_RTMP) {
			bw = pATEInfo->TxWI.TXWI_O.BW;
			sgi = pATEInfo->TxWI.TXWI_O.ShortGI;
			stbc = pATEInfo->TxWI.TXWI_O.STBC;
			mcs = pATEInfo->TxWI.TXWI_O.MCS;
			phymode = pATEInfo->TxWI.TXWI_O.PHYMODE;
			frag = pATEInfo->TxWI.TXWI_O.FRAG;
			ts = pATEInfo->TxWI.TXWI_O.TS;
			ampdu = pATEInfo->TxWI.TXWI_O.AMPDU;
			ack = pATEInfo->TxWI.TXWI_O.ACK;
			nseq = pATEInfo->TxWI.TXWI_O.NSEQ;
			basize = pATEInfo->TxWI.TXWI_O.BAWinSize;
			mpdu_len = pATEInfo->TxWI.TXWI_O.MPDUtotalByteCnt;
			pid = pATEInfo->TxWI.TXWI_O.PacketId;
			txop = pATEInfo->TxWI.TXWI_O.txop;
			cfack = pATEInfo->TxWI.TXWI_O.CFACK;
		}
#endif /* RTMP_MAC */

		/* fill TxWI */
		if (pATEInfo->bQATxStart == TRUE) {
			TxHTPhyMode.field.BW = bw;
			TxHTPhyMode.field.ShortGI = sgi;
			TxHTPhyMode.field.STBC = stbc;
			TxHTPhyMode.field.MCS = mcs;
			TxHTPhyMode.field.MODE = phymode;
			ATEWriteTxWI(pAd, pTxWI, frag, ts,
				     ampdu, ack, nseq,
				     basize, BSSID_WCID, mpdu_len /* include 802.11 header */ ,
				     pid, 0, txop /*IFS_HTTXOP */ , cfack
				      /*FALSE*/, TxHTPhyMode);
#ifdef TXBF_SUPPORT
#ifdef RLT_MAC
			if (IS_MT76x2(pAd)) {
				/* Must copy rsv bits to actual TxWI */
				pTxWI->TXWI_N.Rsv4 = pATEInfo->TxWI.TXWI_N.Rsv4;
				pTxWI->TXWI_N.iTxBF = pATEInfo->TxWI.TXWI_N.iTxBF;
				pTxWI->TXWI_N.Sounding = pATEInfo->TxWI.TXWI_N.Sounding;
				pTxWI->TXWI_N.eTxBF = pATEInfo->TxWI.TXWI_N.eTxBF;
				pTxWI->TXWI_N.NDPSndBW = pATEInfo->TxWI.TXWI_N.NDPSndBW;
				pTxWI->TXWI_N.NDPSndRate = pATEInfo->TxWI.TXWI_N.NDPSndRate;
				pTxWI->TXWI_N.TXBF_PT_SCA = pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
			}
#endif
#endif /* TXBF_SUPPORT */
		} else {
			TxHTPhyMode.field.BW = bw;
			TxHTPhyMode.field.ShortGI = sgi;
			TxHTPhyMode.field.STBC = 0;
			TxHTPhyMode.field.MCS = mcs;
			TxHTPhyMode.field.MODE = phymode;

			ATEWriteTxWI(pAd, pTxWI, FALSE, FALSE, FALSE, FALSE
				     /* No ack required. */ , FALSE, 0, BSSID_WCID,
				     pATEInfo->TxLength, 0, 0, IFS_HTTXOP, FALSE, TxHTPhyMode);
		}

#ifdef TXBF_SUPPORT
		if (pATEInfo->bTxBF == 1) {
#ifdef RLT_MAC
			if (IS_MT76x2(pAd)) {
				pTxWI->TXWI_N.Rsv4 = 0;

				pTxWI->TXWI_N.Sounding = (pATEInfo->txSoundingMode == 1 ? 1 : 0);
				pTxWI->TXWI_N.iTxBF = pATEInfo->TxWI.TXWI_N.iTxBF;
				pTxWI->TXWI_N.eTxBF = pATEInfo->TxWI.TXWI_N.eTxBF;
				pTxWI->TXWI_N.NDPSndBW = pATEInfo->TxWI.TXWI_N.BW;
				if (pATEInfo->txSoundingMode == 3) {
					/* pTxWI->TXWI_N.NDPSndRate = 2; */
					pTxWI->TXWI_N.NDPSndRate = 1;
				} else if (pATEInfo->txSoundingMode == 2)
					pTxWI->TXWI_N.NDPSndRate = 1;
				else
					pTxWI->TXWI_N.NDPSndRate = 0;
				pTxWI->TXWI_N.TXBF_PT_SCA = pATEInfo->TxWI.TXWI_N.TXBF_PT_SCA;
			}
#endif
		}
#endif /* TXBF_SUPPORT */

		RTMPMoveMemory(&pAd->NullContext.TransferBuffer->field.
			       WirelessPacket[TXINFO_SIZE + TXWISize], &pAd->NullFrame,
			       pATEInfo->HLen);

		pDest =
		    &(pAd->NullContext.TransferBuffer->field.
		      WirelessPacket[TXINFO_SIZE + TXWISize + pATEInfo->HLen]);

		/* prepare frame payload */
#ifdef RALINK_QA
		if (pATEInfo->bQATxStart == TRUE) {
			/* copy the pattern one by one to the frame payload */
			if ((pATEInfo->PLen != 0) && (pATEInfo->DLen != 0)) {
				for (pos = 0; pos < pATEInfo->DLen; pos += pATEInfo->PLen) {
					RTMPMoveMemory(pDest, pATEInfo->Pattern, pATEInfo->PLen);
					pDest += pATEInfo->PLen;
				}
			}
			TransferBufferLength = TXINFO_SIZE + TXWISize + mpdu_len;
		} else
#endif /* RALINK_QA */
		{
			for (pos = 0; pos < (pATEInfo->TxLength - pATEInfo->HLen); pos++) {
				*pDest = 0x00;
				pDest += 1;
			}
			TransferBufferLength = TXINFO_SIZE + TXWISize + pATEInfo->TxLength;
		}

		OrgBufferLength = TransferBufferLength;
		TransferBufferLength = (TransferBufferLength + 3) & (~3);

		/* Always add 4 extra bytes at every packet. */
		/* 4 == last packet padding */
		padLen = TransferBufferLength - OrgBufferLength + 4;

		/*
		   RTMP_PKT_TAIL_PADDING == 11.
		   [11 == 3(max 4 byte padding) + 4(last packet padding)
						+ 4(MaxBulkOutsize align padding)]
		 */
		ASSERT((padLen <=
			(RTMP_PKT_TAIL_PADDING - 4 /* 4 == MaxBulkOutsize alignment padding */)));

		/* Now memzero all extra padding bytes. */
		NdisZeroMemory(pDest, padLen);
		pDest += padLen;

		/* Update pTxInfo->TxInfoPktLen to include padding. */
		pTxInfo->TxInfoPktLen = TransferBufferLength - TXINFO_SIZE;

		TransferBufferLength += 4;

		/* If TransferBufferLength is multiple of 64, add extra 4 bytes again. */
		if ((TransferBufferLength % pAd->BulkOutMaxPacketSize) == 0) {
			NdisZeroMemory(pDest, 4);
			TransferBufferLength += 4;
		}
		/* Fill out frame length information for global Bulk out arbitor. */
		pAd->NullContext.BulkOutSize = TransferBufferLength;
	}
#ifdef RT_BIG_ENDIAN
	RTMPWIEndianChange(pAd, (PUCHAR) pTxWI, TYPE_TXWI);
	RTMPFrameEndianChange(pAd, (((PUCHAR) pTxInfo) + TXWISize + TXINFO_SIZE), DIR_WRITE, FALSE);
	RTMPDescriptorEndianChange((PUCHAR) pTxInfo, TYPE_TXINFO);
#endif /* RT_BIG_ENDIAN */

	return 0;
}

/*
========================================================================

	Routine Description:

	Arguments:

	Return Value:
		None

	Note:

========================================================================
*/
VOID ATE_RTUSBBulkOutDataPacket(IN PRTMP_ADAPTER pAd, IN UCHAR BulkOutPipeId)
{
	PTX_CONTEXT pNullContext = &(pAd->NullContext);
	PURB pUrb;
	INT ret = 0;
	ULONG IrqFlags;


	ASSERT(BulkOutPipeId == 0);

	/* Build up the frame first. */
	BULK_OUT_LOCK(&pAd->BulkOutLock[BulkOutPipeId], IrqFlags);

	if (pAd->BulkOutPending[BulkOutPipeId] == TRUE) {
		BULK_OUT_UNLOCK(&pAd->BulkOutLock[BulkOutPipeId], IrqFlags);
		return;
	}

	pAd->BulkOutPending[BulkOutPipeId] = TRUE;
	BULK_OUT_UNLOCK(&pAd->BulkOutLock[BulkOutPipeId], IrqFlags);

	/* Increase total transmit byte counter. */
	pAd->RalinkCounters.OneSecTransmittedByteCount += pNullContext->BulkOutSize;
	pAd->RalinkCounters.TransmittedByteCount += pNullContext->BulkOutSize;

	/* Clear ATE frame bulk out flag. */
	RTUSB_CLEAR_BULK_FLAG(pAd, fRTUSB_BULK_OUT_DATA_ATE);

	/* Init Tx context descriptor. */
	pNullContext->IRPPending = TRUE;
	RTUSBInitTxDesc(pAd, pNullContext, BulkOutPipeId,
			(usb_complete_t) RTUSBBulkOutDataPacketComplete);
	pUrb = pNullContext->pUrb;

	ret = RTUSB_SUBMIT_URB(pUrb);
	if (ret != 0) {
		DBGPRINT_ERR(("ATE_RTUSBBulkOutDataPacket: Submit Tx URB failed %d\n", ret));
		return;
	}

	pAd->BulkOutReq++;

}

/*
========================================================================

	Routine Description:

	Arguments:

	Return Value:
		None

	Note:

========================================================================
*/
VOID ATE_RTUSBCancelPendingBulkInIRP(IN PRTMP_ADAPTER pAd)
{
	PRX_CONTEXT pRxContext = NULL;
	UINT rx_ring_index;

	DBGPRINT(RT_DEBUG_TRACE, ("--->ATE_RTUSBCancelPendingBulkInIRP\n"));

	for (rx_ring_index = 0; rx_ring_index < (RX_RING_SIZE); rx_ring_index++) {
		pRxContext = &(pAd->RxContext[rx_ring_index]);

		if (pRxContext->IRPPending == TRUE) {
			RTUSB_UNLINK_URB(pRxContext->pUrb);
			pRxContext->IRPPending = FALSE;
			pRxContext->InUse = FALSE;
		}
	}

	DBGPRINT(RT_DEBUG_TRACE, ("<---ATE_RTUSBCancelPendingBulkInIRP\n"));

}

/*
========================================================================

	Routine Description:

	Arguments:

	Return Value:
		None

	Note:

========================================================================
*/
VOID ATEResetBulkIn(IN PRTMP_ADAPTER pAd)
{
	if ((pAd->PendingRx > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_ERR(("ATE : BulkIn IRP Pending!!!\n"));
		ATE_RTUSBCancelPendingBulkInIRP(pAd);
		RtmpOsMsDelay(100);
		pAd->PendingRx = 0;
	}

}

/*
========================================================================

	Routine Description:

	Arguments:

	Return Value:

	Note:

========================================================================
*/
INT ATEResetBulkOut(IN PRTMP_ADAPTER pAd)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	PTX_CONTEXT pNullContext = &(pAd->NullContext);
	INT ret = 0;

	pNullContext->IRPPending = TRUE;

	/*
	   If driver is still in ATE TXFRAME mode,
	   keep on transmitting ATE frames.
	 */
	DBGPRINT(RT_DEBUG_TRACE,
		 ("pATEInfo->Mode == %d\npAd->ContinBulkOut == %d\npAd->BulkOutRemained == %d\n",
		  pATEInfo->Mode, pAd->ContinBulkOut, atomic_read(&pAd->BulkOutRemained)));

	if ((pATEInfo->Mode == ATE_TXFRAME)
	    && ((pAd->ContinBulkOut == TRUE) || (atomic_read(&pAd->BulkOutRemained) > 0))) {
		DBGPRINT(RT_DEBUG_TRACE,
			 ("After CMDTHREAD_RESET_BULK_OUT, continue to bulk out frames !\n"));

		/* Init Tx context descriptor. */
		RTUSBInitTxDesc(pAd, pNullContext, 0 /* pAd->bulkResetPipeid */ ,
				(usb_complete_t) RTUSBBulkOutDataPacketComplete);

		ret = RTUSB_SUBMIT_URB(pNullContext->pUrb);
		if (ret != 0)
			DBGPRINT_ERR(("ATE_RTUSBBulkOutDataPacket: Submit Tx URB failed %d\n",
				      ret));

		pAd->BulkOutReq++;
	}

	return ret;
}

/*
========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

========================================================================
*/
VOID RTUSBRejectPendingPackets(IN PRTMP_ADAPTER pAd)
{
	UCHAR Index;
	PQUEUE_ENTRY pEntry;
	PNDIS_PACKET pPacket;
	PQUEUE_HEADER pQueue;


	for (Index = 0; Index < 4; Index++) {
		NdisAcquireSpinLock(&pAd->TxSwQueueLock[Index]);
		while (pAd->TxSwQueue[Index].Head != NULL) {
			pQueue = (PQUEUE_HEADER) &(pAd->TxSwQueue[Index]);
			pEntry = RemoveHeadQueue(pQueue);
			pPacket = QUEUE_ENTRY_TO_PACKET(pEntry);
			RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
		}
		NdisReleaseSpinLock(&pAd->TxSwQueueLock[Index]);

	}

}

#endif /* RTMP_MAC_USB */
