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

static VOID APMlmeDeauthReqAction(IN PRTMP_ADAPTER pAd, IN MLME_QUEUE_ELEM * Elem);

static VOID APPeerDeauthReqAction(IN PRTMP_ADAPTER pAd, IN MLME_QUEUE_ELEM * Elem);

static VOID APPeerAuthReqAtIdleAction(IN PRTMP_ADAPTER pAd, IN MLME_QUEUE_ELEM * Elem);

static VOID APPeerAuthConfirmAction(IN PRTMP_ADAPTER pAd, IN MLME_QUEUE_ELEM * Elem);

static VOID APPeerAuthSimpleRspGenAndSend(IN PRTMP_ADAPTER pAd,
					  IN PHEADER_802_11 pHdr80211,
					  IN USHORT Alg, IN USHORT Seq, IN USHORT StatusCode);

/*
    ==========================================================================
    Description:
	authenticate state machine init, including state transition and timer init
    Parameters:
	Sm - pointer to the auth state machine
    Note:
	The state machine looks like this

				    AP_AUTH_REQ_IDLE
	APMT2_MLME_DEAUTH_REQ	  mlme_deauth_req_action
    ==========================================================================
 */
void APAuthStateMachineInit(IN PRTMP_ADAPTER pAd,
			    IN STATE_MACHINE * Sm, OUT STATE_MACHINE_FUNC Trans[])
{
	StateMachineInit(Sm, (STATE_MACHINE_FUNC *) Trans, AP_MAX_AUTH_STATE,
			 AP_MAX_AUTH_MSG, (STATE_MACHINE_FUNC) Drop,
			 AP_AUTH_REQ_IDLE, AP_AUTH_MACHINE_BASE);

	/* the first column */
	StateMachineSetAction(Sm, AP_AUTH_REQ_IDLE, APMT2_MLME_DEAUTH_REQ,
			      (STATE_MACHINE_FUNC) APMlmeDeauthReqAction);
	StateMachineSetAction(Sm, AP_AUTH_REQ_IDLE, APMT2_PEER_DEAUTH,
			      (STATE_MACHINE_FUNC) APPeerDeauthReqAction);
	StateMachineSetAction(Sm, AP_AUTH_REQ_IDLE, APMT2_PEER_AUTH_REQ,
			      (STATE_MACHINE_FUNC) APPeerAuthReqAtIdleAction);
	StateMachineSetAction(Sm, AP_AUTH_REQ_IDLE, APMT2_PEER_AUTH_CONFIRM,
			      (STATE_MACHINE_FUNC) APPeerAuthConfirmAction);
}

/*
    ==========================================================================
    Description:
	Upper Layer request to kick out a STA
    ==========================================================================
 */
static VOID APMlmeDeauthReqAction(IN PRTMP_ADAPTER pAd, IN MLME_QUEUE_ELEM * Elem)
{
	MLME_DEAUTH_REQ_STRUCT *pInfo;
	HEADER_802_11 Hdr;
	PUCHAR pOutBuffer = NULL;
	NDIS_STATUS NStatus;
	ULONG FrameLen = 0;
	MAC_TABLE_ENTRY *pEntry;
	UCHAR apidx;

	pInfo = (MLME_DEAUTH_REQ_STRUCT *) Elem->Msg;

	if (Elem->Wcid < MAX_LEN_OF_MAC_TABLE) {
		pEntry = &pAd->MacTab.Content[Elem->Wcid];
		if (!pEntry)
			return;

#ifdef WAPI_SUPPORT
		WAPI_InternalCmdAction(pAd,
				       pEntry->AuthMode,
				       pEntry->apidx, pEntry->Addr, WAI_MLME_DISCONNECT);
#endif /* WAPI_SUPPORT */

		/* send wireless event - for deauthentication */
		RTMPSendWirelessEvent(pAd, IW_DEAUTH_EVENT_FLAG, pInfo->Addr, 0, 0);
		ApLogEvent(pAd, pInfo->Addr, EVENT_DISASSOCIATED);

		apidx = pEntry->apidx;

		/* 1. remove this STA from MAC table */
		MacTableDeleteEntry(pAd, Elem->Wcid, pInfo->Addr);

		/* 2. send out DE-AUTH request frame */
		NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);
		if (NStatus != NDIS_STATUS_SUCCESS)
			return;

		DBGPRINT(RT_DEBUG_OFF,
			 ("AUTH - Send DE-AUTH req to %02x:%02x:%02x:%02x:%02x:%02x\n",
			  PRINT_MAC(pInfo->Addr)));

		MgtMacHeaderInit(pAd, &Hdr, SUBTYPE_DEAUTH, 0, pInfo->Addr,
				 pAd->ApCfg.MBSSID[apidx].wdev.if_addr,
				 pAd->ApCfg.MBSSID[apidx].wdev.bssid);
		MakeOutgoingFrame(pOutBuffer, &FrameLen,
				  sizeof(HEADER_802_11), &Hdr, 2, &pInfo->Reason, END_OF_ARGS);
		MiniportMMRequest(pAd, 0, pOutBuffer, FrameLen);

		MlmeFreeMemory(pAd, pOutBuffer);
	}
}

static VOID APPeerDeauthReqAction(IN PRTMP_ADAPTER pAd, IN PMLME_QUEUE_ELEM Elem)
{
	UCHAR Addr2[MAC_ADDR_LEN];
	USHORT Reason;
	UINT16 SeqNum;
	MAC_TABLE_ENTRY *pEntry;


	if (!PeerDeauthReqSanity(pAd, Elem->Msg, Elem->MsgLen, Addr2, &SeqNum, &Reason))
		return;

	pEntry = NULL;

	/*pEntry = MacTableLookup(pAd, Addr2); */
	if (Elem->Wcid < MAX_LEN_OF_MAC_TABLE) {
		pEntry = &pAd->MacTab.Content[Elem->Wcid];

#ifdef DOT1X_SUPPORT
		/* Notify 802.1x daemon to clear this sta info */
		if (pEntry->AuthMode == Ndis802_11AuthModeWPA ||
		    pEntry->AuthMode == Ndis802_11AuthModeWPA2 ||
		    pAd->ApCfg.MBSSID[pEntry->apidx].wdev.IEEE8021X)
			DOT1X_InternalCmdAction(pAd, pEntry, DOT1X_DISCONNECT_ENTRY);
#endif /* DOT1X_SUPPORT */

#ifdef WAPI_SUPPORT
		WAPI_InternalCmdAction(pAd,
				       pEntry->AuthMode,
				       pEntry->apidx, pEntry->Addr, WAI_MLME_DISCONNECT);
#endif /* WAPI_SUPPORT */

		/* send wireless event - for deauthentication */
		RTMPSendWirelessEvent(pAd, IW_DEAUTH_EVENT_FLAG, Addr2, 0, 0);
		ApLogEvent(pAd, Addr2, EVENT_DISASSOCIATED);

		if (pEntry->CMTimerRunning == TRUE) {
			/*
			   If one who initilized Counter Measure deauth itself,
			   AP doesn't log the MICFailTime
			 */
			pAd->ApCfg.aMICFailTime = pAd->ApCfg.PrevaMICFailTime;
		}

		MacTableDeleteEntry(pAd, Elem->Wcid, Addr2);

		DBGPRINT(RT_DEBUG_OFF,
			 ("AUTH - receive DE-AUTH(seq-%d) from %02x:%02x:%02x:%02x:%02x:%02x, reason=%d\n",
			  SeqNum, PRINT_MAC(Addr2), Reason));

#ifdef MAC_REPEATER_SUPPORT
		if (pAd->ApCfg.bMACRepeaterEn == TRUE) {
			UCHAR apCliIdx, CliIdx;
			REPEATER_CLIENT_ENTRY *pReptEntry = NULL;

			pReptEntry = RTMPLookupRepeaterCliEntry(pAd, TRUE, Addr2);
			if (pReptEntry && (pReptEntry->CliConnectState != 0)) {
				apCliIdx = pReptEntry->MatchApCliIdx;
				CliIdx = pReptEntry->MatchLinkIdx;
				/* free resources of BA */
				BASessionTearDownALL(pAd, pReptEntry->MacTabWCID);
				RTMPRemoveRepeaterDisconnectEntry(pAd, apCliIdx, CliIdx);
				RTMPRemoveRepeaterEntry(pAd, apCliIdx, CliIdx);
			}
		}
#endif /* MAC_REPEATER_SUPPORT */
	}
}

static VOID APPeerAuthReqAtIdleAction(IN PRTMP_ADAPTER pAd, IN MLME_QUEUE_ELEM * Elem)
{
	INT i;
	USHORT Seq, Alg, RspReason, Status;
	UCHAR Addr1[MAC_ADDR_LEN];
	UCHAR Addr2[MAC_ADDR_LEN];
	CHAR Chtxt[CIPHER_TEXT_LEN];
	UINT32 apidx;

	PHEADER_802_11 pRcvHdr;
	HEADER_802_11 AuthHdr;
	PUCHAR pOutBuffer = NULL;
	NDIS_STATUS NStatus;
	ULONG FrameLen = 0;
	MAC_TABLE_ENTRY *pEntry;
	UCHAR ChTxtIe = 16, ChTxtLen = CIPHER_TEXT_LEN;
	MULTISSID_STRUCT *pMbss;
	struct wifi_dev *wdev;
	CHAR rssi;


	if (pAd->ApCfg.BANClass3Data == TRUE) {
		DBGPRINT(RT_DEBUG_TRACE, ("Disallow new Association\n"));
		return;
	}

	if (!APPeerAuthSanity(pAd, Elem->Msg, Elem->MsgLen, Addr1, Addr2, &Alg, &Seq, &Status, Chtxt
	    ))
		return;


	/* Find which MBSSID to be authenticate */
	apidx = get_apidx_by_addr(pAd, Addr1);
	if (apidx >= pAd->ApCfg.BssidNum) {
		DBGPRINT(RT_DEBUG_TRACE, ("AUTH - Bssid not found\n"));
		return;
	}

	if (apidx < HW_BEACON_MAX_NUM) {
		pMbss = &pAd->ApCfg.MBSSID[apidx];
		wdev = &pMbss->wdev;
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: apidx >= HW_BEACON_MAX_NUM\n", __func__));
		return;
	}

#ifdef MAX_ALLOW_CLIENT
	if (pMbss->StaCount >= MAX_ALLOW_CLIENT_NUM) {
		DBGPRINT(RT_DEBUG_ERROR,
			("[%s] reach MAX_ALLOW_CLIENT=%d reject this one\n",
			__func__, MAX_ALLOW_CLIENT_NUM));
		pRcvHdr = (PHEADER_802_11)(Elem->Msg);
		APPeerAuthSimpleRspGenAndSend(pAd,
			pRcvHdr, Alg, Seq + 1, MLME_ASSOC_REJ_UNABLE_HANDLE_STA);
		return;
	}
#endif /* MAX_ALLOW_CLIENT */

	if ((wdev->if_dev == NULL) || ((wdev->if_dev != NULL) &&
				       !(RTMP_OS_NETDEV_STATE_RUNNING(wdev->if_dev)))) {
		DBGPRINT(RT_DEBUG_TRACE, ("AUTH - Bssid IF didn't up yet.\n"));
		return;
	}

	pEntry = MacTableLookup(pAd, Addr2);
	if (pEntry && IS_ENTRY_CLIENT(pEntry)) {
#ifdef DOT11W_PMF_SUPPORT
		if ((CLIENT_STATUS_TEST_FLAG(pEntry, fCLIENT_STATUS_PMF_CAPABLE))
		    && (pEntry->PortSecured == WPA_802_1X_PORT_SECURED))
			goto SendAuth;
#endif /* DOT11W_PMF_SUPPORT */

		if (!RTMPEqualMemory
		    (Addr1, pAd->ApCfg.MBSSID[pEntry->apidx].wdev.bssid, MAC_ADDR_LEN)) {
			MacTableDeleteEntry(pAd, pEntry->wcid, pEntry->Addr);
			pEntry = NULL;
			DBGPRINT(RT_DEBUG_WARN, ("AUTH - Bssid does not match\n"));
		} else {
			if (pEntry->bIAmBadAtheros == TRUE) {
				AsicUpdateProtect(pAd, 8, ALLN_SETPROTECT, FALSE, FALSE);
				DBGPRINT(RT_DEBUG_TRACE, ("Atheros Problem. Turn on RTS/CTS!!!\n"));
				pEntry->bIAmBadAtheros = FALSE;
			}

			BASessionTearDownALL(pAd, pEntry->wcid);
			ASSERT(pEntry->Aid == Elem->Wcid);
		}
	}
#ifdef DOT11W_PMF_SUPPORT
SendAuth:
#endif /* DOT11W_PMF_SUPPORT */

	pRcvHdr = (PHEADER_802_11) (Elem->Msg);
	DBGPRINT(RT_DEBUG_TRACE,
		 ("AUTH - MBSS(%d), Rcv AUTH seq#%d, Alg=%d, Status=%d from [wcid=%d]%02x:%02x:%02x:%02x:%02x:%02x\n",
		  apidx, Seq, Alg, Status, Elem->Wcid, PRINT_MAC(Addr2)));

	/* YF@20130102: Refuse the weak signal of AuthReq */
	rssi = RTMPMaxRssi(pAd, ConvertToRssi(pAd, (CHAR) Elem->Rssi0, RSSI_0),
			   ConvertToRssi(pAd, (CHAR) Elem->Rssi1, RSSI_1),
			   ConvertToRssi(pAd, (CHAR) Elem->Rssi2, RSSI_2));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("%s: AUTH_FAIL_REQ Threshold = %d, AUTH_NO_RSP_REQ Threshold = %d, AUTH RSSI = %d\n",
		  wdev->if_dev->name, pMbss->AuthFailRssiThreshold, pMbss->AuthNoRspRssiThreshold,
		  rssi));

	if (((pMbss->AuthFailRssiThreshold != 0) && (rssi < pMbss->AuthFailRssiThreshold)) ||
	    ((pMbss->AuthNoRspRssiThreshold != 0) && (rssi < pMbss->AuthNoRspRssiThreshold))) {
		DBGPRINT(RT_DEBUG_TRACE, ("Reject this AUTH_REQ due to Weak Signal.\n"));

		if ((pMbss->AuthFailRssiThreshold != 0) && (rssi < pMbss->AuthFailRssiThreshold))
			APPeerAuthSimpleRspGenAndSend(pAd, pRcvHdr, Alg, Seq + 1,
						      MLME_UNSPECIFY_FAIL);

		/* If this STA exists, delete it. */
		if (pEntry)
			MacTableDeleteEntry(pAd, pEntry->Aid, pEntry->Addr);

		RTMPSendWirelessEvent(pAd, IW_MAC_FILTER_LIST_EVENT_FLAG, Addr2, apidx, 0);
		return;
	}
#ifdef WSC_V2_SUPPORT
	/* Do not check ACL when WPS V2 is enabled and ACL policy is positive. */
	if ((pMbss->WscControl.WscConfMode != WSC_DISABLE) &&
	    (pMbss->WscControl.WscV2Info.bEnableWpsV2) &&
	    (pMbss->WscControl.WscV2Info.bWpsEnable) && (pMbss->AccessControlList.Policy == 1))
			;
	else
#endif /* WSC_V2_SUPPORT */
		/* fail in ACL checking => send an AUTH-Fail seq#2. */

	if (apidx >= HW_BEACON_MAX_NUM) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: apidx >= HW_BEACON_MAX_NUM\n", __func__));
		return;
	}

	if (!ApCheckAccessControlList(pAd, Addr2, apidx)) {
#ifdef CUSTOMIZED_ACL_SUPPORT
		DBGPRINT(RT_DEBUG_TRACE, ("ACL checking => No AUTH resp\n"));
#else
		ASSERT(Seq == 1);
		ASSERT(pEntry == NULL);
		APPeerAuthSimpleRspGenAndSend(pAd, pRcvHdr, Alg, Seq + 1, MLME_UNSPECIFY_FAIL);

		/* If this STA exists, delete it. */
		if (pEntry)
			MacTableDeleteEntry(pAd, pEntry->wcid, pEntry->Addr);

		RTMPSendWirelessEvent(pAd, IW_MAC_FILTER_LIST_EVENT_FLAG, Addr2, apidx, 0);

		DBGPRINT(RT_DEBUG_TRACE,
			 ("Failed in ACL checking => send an AUTH seq#2 with Status code = %d\n",
			 MLME_UNSPECIFY_FAIL));
#endif /* CUSTOMIZED_ACL_SUPPORT */
		return;
	}
	if ((Alg == AUTH_MODE_OPEN) && (pMbss->wdev.AuthMode != Ndis802_11AuthModeShared)) {
		if (!pEntry)
			pEntry = MacTableInsertEntry(pAd, Addr2, wdev, apidx, OPMODE_AP, TRUE);

		if (pEntry) {
#ifdef DOT11W_PMF_SUPPORT
			if (!(CLIENT_STATUS_TEST_FLAG(pEntry, fCLIENT_STATUS_PMF_CAPABLE))
			    || (pEntry->PortSecured != WPA_802_1X_PORT_SECURED))
#endif /* DOT11W_PMF_SUPPORT */
				{
					pEntry->AuthState = AS_AUTH_OPEN;
					pEntry->Sst = SST_AUTH;	/* what if it already in SST_ASSOC ??????? */
				}
				APPeerAuthSimpleRspGenAndSend(pAd, pRcvHdr, Alg, Seq + 1, MLME_SUCCESS);

		} else
		;		/* MAC table full, what should we respond ????? */
	} else if ((Alg == AUTH_MODE_KEY) && ((wdev->AuthMode == Ndis802_11AuthModeShared)
					      || (wdev->AuthMode == Ndis802_11AuthModeAutoSwitch))) {
		if (!pEntry)
			pEntry = MacTableInsertEntry(pAd, Addr2, wdev, apidx, OPMODE_AP, TRUE);

		if (pEntry) {
			pEntry->AuthState = AS_AUTHENTICATING;
			pEntry->Sst = SST_NOT_AUTH;	/* what if it already in SST_ASSOC ??????? */

			/* log this STA in AuthRspAux machine, only one STA is stored. If two STAs using */
			/* SHARED_KEY authentication mingled together, then the late comer will win. */
			COPY_MAC_ADDR(&pAd->ApMlmeAux.Addr, Addr2);
			for (i = 0; i < CIPHER_TEXT_LEN; i++)
				pAd->ApMlmeAux.Challenge[i] = RandomByte(pAd);

			RspReason = 0;
			Seq++;

			NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);
			if (NStatus != NDIS_STATUS_SUCCESS)
				return;	/* if no memory, can't do anything */

			DBGPRINT(RT_DEBUG_TRACE, ("AUTH - Send AUTH seq#2 (Challenge)\n"));

			MgtMacHeaderInit(pAd, &AuthHdr, SUBTYPE_AUTH, 0, Addr2,
					 wdev->if_addr, wdev->bssid);
			MakeOutgoingFrame(pOutBuffer, &FrameLen,
					  sizeof(HEADER_802_11), &AuthHdr,
					  2, &Alg,
					  2, &Seq,
					  2, &RspReason,
					  1, &ChTxtIe,
					  1, &ChTxtLen,
					  CIPHER_TEXT_LEN, pAd->ApMlmeAux.Challenge, END_OF_ARGS);

#ifdef CONFIG_MULTI_CHANNEL
			if ((pAd->Mlme.bStartMcc == TRUE) && RTMP_CFG80211_VIF_P2P_GO_ON(pAd)) {
				/*when MCC STAR, map MGMPACKET to HCCA */
				MiniportMMRequest(pAd, QID_HCCA, pOutBuffer, FrameLen);
			} else
#endif /* CONFIG_MULTI_CHANNEL */
				MiniportMMRequest(pAd, 0, pOutBuffer, FrameLen);

			MlmeFreeMemory(pAd, pOutBuffer);
		} else
		;		/* MAC table full, what should we respond ???? */
	} else {
		/* wrong algorithm */
		APPeerAuthSimpleRspGenAndSend(pAd, pRcvHdr, Alg, Seq + 1, MLME_ALG_NOT_SUPPORT);

		/* If this STA exists, delete it. */
		if (pEntry)
			MacTableDeleteEntry(pAd, pEntry->wcid, pEntry->Addr);

		if (apidx < HW_BEACON_MAX_NUM) {
			DBGPRINT(RT_DEBUG_TRACE, ("AUTH - Alg=%d, Seq=%d, AuthMode=%d\n",
						  Alg, Seq,
						  pAd->ApCfg.MBSSID[apidx].wdev.AuthMode));
		}
	}
}

static VOID APPeerAuthConfirmAction(IN PRTMP_ADAPTER pAd, IN MLME_QUEUE_ELEM * Elem)
{
	USHORT Seq, Alg, Status;
	UCHAR Addr2[MAC_ADDR_LEN];
	PHEADER_802_11 pRcvHdr;
	CHAR Chtxt[CIPHER_TEXT_LEN];
	MAC_TABLE_ENTRY *pEntry;
	UCHAR Addr1[MAC_ADDR_LEN];
	UINT32 apidx;



	if (!APPeerAuthSanity(pAd, Elem->Msg, Elem->MsgLen, Addr1, Addr2, &Alg, &Seq, &Status, Chtxt
	    ))
		return;

	if (pAd == NULL) {
		DBGPRINT(RT_DEBUG_ERROR, ("pAd is NULL\n"));
		return;
	}

	apidx = get_apidx_by_addr(pAd, Addr1);
	if (apidx >= pAd->ApCfg.BssidNum) {
		DBGPRINT(RT_DEBUG_TRACE, ("AUTH - Bssid not found\n"));
		return;
	}

	if (apidx >= HW_BEACON_MAX_NUM) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s: apidx > HW_BEACON_MAX_NUM\n", __func__));
		return;
	}

	if ((pAd->ApCfg.MBSSID[apidx].wdev.if_dev != NULL) &&
	    !(RTMP_OS_NETDEV_STATE_RUNNING(pAd->ApCfg.MBSSID[apidx].wdev.if_dev))) {
		DBGPRINT(RT_DEBUG_TRACE, ("AUTH - Bssid IF didn't up yet.\n"));
		return;
	}
	/* End of if */
	if (Elem->Wcid >= MAX_LEN_OF_MAC_TABLE) {
		DBGPRINT(RT_DEBUG_ERROR, ("AUTH - Invalid wcid (%d).\n", Elem->Wcid));
		return;
	}

	pEntry = &pAd->MacTab.Content[Elem->Wcid];
	if (pEntry && IS_ENTRY_CLIENT(pEntry)) {
		if (!RTMPEqualMemory
		    (Addr1, pAd->ApCfg.MBSSID[pEntry->apidx].wdev.bssid, MAC_ADDR_LEN)) {
			MacTableDeleteEntry(pAd, pEntry->wcid, pEntry->Addr);
			pEntry = NULL;
			DBGPRINT(RT_DEBUG_WARN, ("AUTH - Bssid does not match\n"));
		} else {
			if (pEntry->bIAmBadAtheros == TRUE) {
				AsicUpdateProtect(pAd, 8, ALLN_SETPROTECT, FALSE, FALSE);
				DBGPRINT(RT_DEBUG_TRACE, ("Atheros Problem. Turn on RTS/CTS!!!\n"));
				pEntry->bIAmBadAtheros = FALSE;
			}

			ASSERT(pEntry->Aid == Elem->Wcid);

			BASessionTearDownALL(pAd, pEntry->wcid);
		}
	}

	pRcvHdr = (PHEADER_802_11) (Elem->Msg);

	DBGPRINT(RT_DEBUG_TRACE,
		 ("AUTH - MBSS(%d), Rcv AUTH seq#%d, Alg=%d, Status=%d from [wcid=%d]%02x:%02x:%02x:%02x:%02x:%02x\n",
		  apidx, Seq, Alg, Status, Elem->Wcid, PRINT_MAC(Addr2)));

	if (pEntry && MAC_ADDR_EQUAL(Addr2, pAd->ApMlmeAux.Addr)) {
		if ((pRcvHdr->FC.Wep == 1) &&
			    NdisEqualMemory(Chtxt, pAd->ApMlmeAux.Challenge, CIPHER_TEXT_LEN)) {
			/* Successful */
			APPeerAuthSimpleRspGenAndSend(pAd, pRcvHdr, Alg, Seq + 1, MLME_SUCCESS);
			pEntry->AuthState = AS_AUTH_KEY;
			pEntry->Sst = SST_AUTH;
		} else {

			/* send wireless event - Authentication rejected because of challenge failure */
			RTMPSendWirelessEvent(pAd, IW_AUTH_REJECT_CHALLENGE_FAILURE, pEntry->Addr,
					      0, 0);

			/* fail - wep bit is not set or challenge text is not equal */
			APPeerAuthSimpleRspGenAndSend(pAd, pRcvHdr, Alg, Seq + 1,
						      MLME_REJ_CHALLENGE_FAILURE);
			MacTableDeleteEntry(pAd, pEntry->wcid, pEntry->Addr);

			/*Chtxt[127]='\0'; */
			/*pAd->ApMlmeAux.Challenge[127]='\0'; */
			DBGPRINT(RT_DEBUG_TRACE, ("%s\n",
						  ((pRcvHdr->FC.Wep ==
						    1) ? "challenge text is not equal" :
						   "wep bit is not set")));
			/*DBGPRINT(RT_DEBUG_TRACE, ("Sent Challenge = %s\n",&pAd->ApMlmeAux.Challenge[100])); */
			/*DBGPRINT(RT_DEBUG_TRACE, ("Rcv Challenge = %s\n",&Chtxt[100])); */
		}
	} else {
		/* fail for unknown reason. most likely is AuthRspAux machine be overwritten by another */
		/* STA also using SHARED_KEY authentication */
		APPeerAuthSimpleRspGenAndSend(pAd, pRcvHdr, Alg, Seq + 1, MLME_UNSPECIFY_FAIL);

		/* If this STA exists, delete it. */
		if (pEntry)
			MacTableDeleteEntry(pAd, pEntry->wcid, pEntry->Addr);
	}
}

/*
    ==========================================================================
    Description:
	Some STA/AP
    Note:
	This action should never trigger AUTH state transition, therefore we
	separate it from AUTH state machine, and make it as a standalone service
    ==========================================================================
 */
VOID APCls2errAction(IN RTMP_ADAPTER * pAd, IN ULONG Wcid, IN HEADER_802_11 *pHeader)
{
	HEADER_802_11 Hdr;
	UCHAR *pOutBuffer = NULL;
	NDIS_STATUS NStatus;
	ULONG FrameLen = 0;
	USHORT Reason = REASON_CLS2ERR;
	MAC_TABLE_ENTRY *pEntry = NULL;
	UCHAR apidx;

	if (Wcid < MAX_LEN_OF_MAC_TABLE)
		pEntry = &(pAd->MacTab.Content[Wcid]);

	if (pEntry && IS_ENTRY_CLIENT(pEntry)) {
		/*ApLogEvent(pAd, pAddr, EVENT_DISASSOCIATED); */
		MacTableDeleteEntry(pAd, pEntry->wcid, pHeader->Addr2);
	} else {

		apidx = get_apidx_by_addr(pAd, pHeader->Addr1);
		if (apidx >= pAd->ApCfg.BssidNum) {
			DBGPRINT(RT_DEBUG_TRACE,
				 ("AUTH - Class 2 error but not my bssid %02x:%02x:%02x:%02x:%02x:%02x\n",
				  PRINT_MAC(pHeader->Addr1)));
			return;
		}
	}

	/* send out DEAUTH frame */
	NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);
	if (NStatus != NDIS_STATUS_SUCCESS)
		return;

	DBGPRINT(RT_DEBUG_TRACE,
		 ("AUTH - Class 2 error, Send DEAUTH frame to %02x:%02x:%02x:%02x:%02x:%02x\n",
		 PRINT_MAC(pHeader->Addr2)));

	MgtMacHeaderInit(pAd, &Hdr, SUBTYPE_DEAUTH, 0, pHeader->Addr2,
			 pHeader->Addr1, pHeader->Addr1);
	MakeOutgoingFrame(pOutBuffer, &FrameLen,
			  sizeof(HEADER_802_11), &Hdr, 2, &Reason, END_OF_ARGS);

#ifdef CONFIG_MULTI_CHANNEL
	if ((pAd->Mlme.bStartMcc == TRUE) && RTMP_CFG80211_VIF_P2P_GO_ON(pAd)) {
		/*when MCC STAR, map MGMPACKET to HCCA */
		MiniportMMRequest(pAd, QID_HCCA, pOutBuffer, FrameLen);
	} else
#endif /* CONFIG_MULTI_CHANNEL */
		MiniportMMRequest(pAd, 0, pOutBuffer, FrameLen);

	MlmeFreeMemory(pAd, pOutBuffer);
}

/*
    ==========================================================================
    Description:
	Send out a Authentication (response) frame
    ==========================================================================
*/
VOID APPeerAuthSimpleRspGenAndSend(IN PRTMP_ADAPTER pAd,
				   IN PHEADER_802_11 pHdr,
				   IN USHORT Alg, IN USHORT Seq, IN USHORT StatusCode)
{
	HEADER_802_11 AuthHdr;
	ULONG FrameLen = 0;
	PUCHAR pOutBuffer = NULL;
	NDIS_STATUS NStatus;

	NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);
	if (NStatus != NDIS_STATUS_SUCCESS)
		return;

	if (StatusCode == MLME_SUCCESS) {
		DBGPRINT(RT_DEBUG_OFF, ("AUTH_RSP - Send AUTH response (SUCCESS)...\n"));
	} else {
		/* For MAC wireless client(Macintosh), need to send AUTH_RSP with Status Code
		(fail reason code) to reject it. */
		DBGPRINT(RT_DEBUG_OFF,
			 ("AUTH_RSP - Peer AUTH fail (Status = %d)...\n", StatusCode));
	}

	MgtMacHeaderInit(pAd, &AuthHdr, SUBTYPE_AUTH, 0, pHdr->Addr2, pHdr->Addr1, pHdr->Addr1);
	MakeOutgoingFrame(pOutBuffer, &FrameLen,
			  sizeof(HEADER_802_11), &AuthHdr,
			  2, &Alg, 2, &Seq, 2, &StatusCode, END_OF_ARGS);

#ifdef CONFIG_MULTI_CHANNEL
	if ((pAd->Mlme.bStartMcc == TRUE) && RTMP_CFG80211_VIF_P2P_GO_ON(pAd)) {
		/*when MCC STAR, map MGMPACKET to HCCA */
		MiniportMMRequest(pAd, QID_HCCA, pOutBuffer, FrameLen);
	} else
#endif /* CONFIG_MULTI_CHANNEL */
		MiniportMMRequest(pAd, 0, pOutBuffer, FrameLen);

	MlmeFreeMemory(pAd, pOutBuffer);
}
