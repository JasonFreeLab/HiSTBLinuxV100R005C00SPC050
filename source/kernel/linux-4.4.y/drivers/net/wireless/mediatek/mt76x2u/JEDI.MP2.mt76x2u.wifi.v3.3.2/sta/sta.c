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

/*
VOID STARxErrorHandle(RTMP_ADAPTER *pAd, RX_BLK *pRxBlk)
{

}
*/
/*
	========================================================================
	Routine Description:
		Check Rx descriptor, return NDIS_STATUS_FAILURE if any error found
	========================================================================
*/
INT RTMPCheckRxError(IN RTMP_ADAPTER * pAd,
		     IN HEADER_802_11 * pHeader, IN RX_BLK * pRxBlk, IN RXINFO_STRUC * pRxInfo)
{
	if (pRxInfo == NULL)
		return NDIS_STATUS_FAILURE;

	/* Phy errors & CRC errors */
	if (pRxInfo->Crc) {
		INT dBm = (pRxBlk->rssi[0]) - pAd->BbpRssiToDbmDelta;

		/* Check RSSI for Noise Hist statistic collection. */
		if (dBm <= -87)
			pAd->StaCfg.RPIDensity[0] += 1;
		else if (dBm <= -82)
			pAd->StaCfg.RPIDensity[1] += 1;
		else if (dBm <= -77)
			pAd->StaCfg.RPIDensity[2] += 1;
		else if (dBm <= -72)
			pAd->StaCfg.RPIDensity[3] += 1;
		else if (dBm <= -67)
			pAd->StaCfg.RPIDensity[4] += 1;
		else if (dBm <= -62)
			pAd->StaCfg.RPIDensity[5] += 1;
		else if (dBm <= -57)
			pAd->StaCfg.RPIDensity[6] += 1;
		else if (dBm > -57)
			pAd->StaCfg.RPIDensity[7] += 1;

		return NDIS_STATUS_FAILURE;
	}

	/* Drop ToDs promiscous frame, it is opened due to CCX 2 channel load statistics */
	if (pHeader != NULL) {
		if (pHeader->FC.ToDs
		    ) {
			return NDIS_STATUS_FAILURE;
		}
	}

	/* Paul 04-03 for OFDM Rx length issue */
	if (pRxBlk->MPDUtotalByteCnt > MAX_AGGREGATION_SIZE) {
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("received packet too long\n"));
		return NDIS_STATUS_FAILURE;
	}

	/*
	   Drop not U2M frames, cant's drop here because we will drop beacon in this case
	   I am kind of doubting the U2M bit operation
	 */
	/*
	   if (pRxInfo->U2M == 0)
	   return NDIS_STATUS_FAILURE;
	 */

	/* drop decyption fail frame */
	if (pRxInfo->Decrypted && pRxInfo->CipherErr) {

		if (pRxInfo->CipherErr == 2)
			DBGPRINT_RAW(RT_DEBUG_TRACE, ("RxErr: ICV ok but MICErr"));
		else if (pRxInfo->CipherErr == 1)
			DBGPRINT_RAW(RT_DEBUG_TRACE, ("RxErr: ICV Err"));
		else if (pRxInfo->CipherErr == 3)
			DBGPRINT_RAW(RT_DEBUG_TRACE, ("RxErr: Key not valid"));

		if (INFRA_ON(pAd) && pRxInfo->MyBss) {
			if ((pRxInfo->CipherErr & 1) == 1) {
				RTMPSendWirelessEvent(pAd, IW_ICV_ERROR_EVENT_FLAG,
						      pAd->MacTab.Content[BSSID_WCID].Addr,
						      BSS0, 0);
			}

			/* MIC Error */
			if (pRxInfo->CipherErr == 2) {
				CIPHER_KEY *pWpaKey = &pAd->SharedKey[BSS0][pRxBlk->key_idx];

#ifdef WPA_SUPPLICANT_SUPPORT
				if (pAd->StaCfg.wpa_supplicant_info.WpaSupplicantUP)
					WpaSendMicFailureToWpaSupplicant(pAd->net_dev,
									 pHeader->Addr2,
									 (pWpaKey->Type ==
									  PAIRWISEKEY) ? TRUE :
									 FALSE,
									 (INT) pRxBlk->key_idx,
									 NULL);
				else
#endif /* WPA_SUPPLICANT_SUPPORT */
					RTMPReportMicError(pAd, pWpaKey);

				RTMPSendWirelessEvent(pAd, IW_MIC_ERROR_EVENT_FLAG,
						      pAd->MacTab.Content[BSSID_WCID].Addr,
						      BSS0, 0);
			}
		}

		DBGPRINT_RAW(RT_DEBUG_TRACE,
			     ("%s(): %d (len=%d, Mcast=%d, MyBss=%d, Wcid=%d, KeyId=%d)\n",
			      __func__, pRxInfo->CipherErr, pRxBlk->MPDUtotalByteCnt,
			      pRxInfo->Mcast | pRxInfo->Bcast, pRxInfo->MyBss, pRxBlk->wcid,
			      pRxBlk->key_idx));

		dump_rxinfo(pAd, pRxInfo);
		dump_rxwi(pAd, pRxBlk->pRxWI);
		if (pHeader)
			hex_dump("ErrorPkt", (UCHAR *) pHeader, pRxBlk->MPDUtotalByteCnt);

		if (pHeader == NULL)
			return NDIS_STATUS_SUCCESS;

		return NDIS_STATUS_FAILURE;
	}

	return NDIS_STATUS_SUCCESS;
}

static INT StaAllowToSendPacket(RTMP_ADAPTER *pAd,
				struct wifi_dev *wdev, PNDIS_PACKET pPacket, UCHAR *pWcid)
{
	BOOLEAN allowToSend;

	if (!INFRA_ON(pAd) && !ADHOC_ON(pAd))
		return FALSE;

	if (ADHOC_ON(pAd))
		RTMP_SET_PACKET_WCID(pPacket, MCAST_WCID);

	if (INFRA_ON(pAd) && (0
#ifdef QOS_DLS_SUPPORT
			      || (pAd->CommonCfg.bDLSCapable)
#endif /* QOS_DLS_SUPPORT */
#if defined(DOT11Z_TDLS_SUPPORT) || defined(CFG_TDLS_SUPPORT)
			      || IS_TDLS_SUPPORT(pAd)
#endif /* defined(DOT11Z_TDLS_SUPPORT) || defined(CFG_TDLS_SUPPORT) */
	    )) {
		MAC_TABLE_ENTRY *pEntry;
		PUCHAR pSrcBufVA = GET_OS_PKT_DATAPTR(pPacket);

		pEntry = MacTableLookup(pAd, pSrcBufVA);

		if (pEntry && (IS_ENTRY_DLS(pEntry)
#if defined(DOT11Z_TDLS_SUPPORT) || defined(CFG_TDLS_SUPPORT)
			       || IS_ENTRY_TDLS(pEntry)
#endif /* defined(DOT11Z_TDLS_SUPPORT) || defined(CFG_TDLS_SUPPORT) */
		    )) {
			*pWcid = pEntry->wcid;
		} else
			*pWcid = 0;
	} else {
		*pWcid = 0;
	}

	allowToSend = TRUE;

	return allowToSend;
}

INT STAInitialize(RTMP_ADAPTER *pAd)
{
	struct wifi_dev *wdev = &pAd->StaCfg.wdev;

	wdev->wdev_type = WDEV_TYPE_STA;
	wdev->tx_pkt_allowed = StaAllowToSendPacket;
	wdev->allow_data_tx = TRUE;

	return 0;
}
