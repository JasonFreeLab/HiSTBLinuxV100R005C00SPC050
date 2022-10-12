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

extern UCHAR CISCO_OUI[];

extern UCHAR WPA_OUI[];
extern UCHAR RSN_OUI[];
extern UCHAR WME_INFO_ELEM[];
extern UCHAR WME_PARM_ELEM[];
extern UCHAR RALINK_OUI[];
extern UCHAR BROADCOM_OUI[];
extern UCHAR WPS_OUI[];

#ifdef IWSC_SUPPORT
extern UCHAR IWSC_OUI[];
#endif /* IWSC_SUPPORT // */

typedef struct wsc_ie_probreq_data {
	UCHAR ssid[32];
	UCHAR macAddr[6];
	UCHAR data[2];
} WSC_IE_PROBREQ_DATA;

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN MlmeAddBAReqSanity(IN PRTMP_ADAPTER pAd, IN VOID * Msg, IN ULONG MsgLen, OUT PUCHAR pAddr2)
{
	PMLME_ADDBA_REQ_STRUCT pInfo;

	pInfo = (MLME_ADDBA_REQ_STRUCT *) Msg;

	if (MsgLen != sizeof(MLME_ADDBA_REQ_STRUCT)) {
		DBGPRINT(RT_DEBUG_TRACE,
			("MlmeAddBAReqSanity fail - message length not correct.\n"));
		return FALSE;
	}

	if (pInfo->Wcid >= MAX_LEN_OF_MAC_TABLE) {
		DBGPRINT(RT_DEBUG_TRACE,
			("MlmeAddBAReqSanity fail - The peer Mac is not associated yet.\n"));
		return FALSE;
	}

	/*
	   if ((pInfo->BaBufSize > MAX_RX_REORDERBUF) || (pInfo->BaBufSize < 2))
	   {
	   DBGPRINT(RT_DEBUG_TRACE, ("MlmeAddBAReqSanity fail - Rx Reordering buffer too big or too small\n"));
	   return FALSE;
	   }
	 */

	if ((pInfo->pAddr[0] & 0x01) == 0x01) {
		DBGPRINT(RT_DEBUG_TRACE,
			("MlmeAddBAReqSanity fail - broadcast address not support BA\n"));
		return FALSE;
	}

	return TRUE;
}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN MlmeDelBAReqSanity(IN PRTMP_ADAPTER pAd, IN VOID * Msg, IN ULONG MsgLen)
{
	MLME_DELBA_REQ_STRUCT *pInfo;

	pInfo = (MLME_DELBA_REQ_STRUCT *) Msg;

	if (MsgLen != sizeof(MLME_DELBA_REQ_STRUCT)) {
		DBGPRINT(RT_DEBUG_ERROR,
			("MlmeDelBAReqSanity fail - message length not correct.\n"));
		return FALSE;
	}

	if (pInfo->Wcid >= MAX_LEN_OF_MAC_TABLE) {
		DBGPRINT(RT_DEBUG_ERROR,
			("MlmeDelBAReqSanity fail - The peer Mac is not associated yet.\n"));
		return FALSE;
	}

	if ((pInfo->TID & 0xf0)) {
		DBGPRINT(RT_DEBUG_ERROR,
			("MlmeDelBAReqSanity fail - The peer TID is incorrect.\n"));
		return FALSE;
	}

	if (NdisEqualMemory(pAd->MacTab.Content[pInfo->Wcid].Addr, pInfo->Addr, MAC_ADDR_LEN) == 0) {
		DBGPRINT(RT_DEBUG_ERROR,
			("MlmeDelBAReqSanity fail - the peer addr doesn't exist.\n"));
		return FALSE;
	}

	return TRUE;
}

BOOLEAN PeerAddBAReqActionSanity(IN PRTMP_ADAPTER pAd,
	IN VOID * pMsg, IN ULONG MsgLen, OUT PUCHAR pAddr2)
{
	PFRAME_802_11 pFrame = (PFRAME_802_11) pMsg;
	PFRAME_ADDBA_REQ pAddFrame;

	pAddFrame = (PFRAME_ADDBA_REQ) (pMsg);
	if (MsgLen < (sizeof(FRAME_ADDBA_REQ))) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("PeerAddBAReqActionSanity: ADDBA Request frame length size = %ld incorrect\n",
			  MsgLen));
		return FALSE;
	}
	/* we support immediate BA. */
#ifdef UNALIGNMENT_SUPPORT
	{
		BA_PARM tmpBaParm;

		NdisMoveMemory((PUCHAR) (&tmpBaParm), (PUCHAR) (&pAddFrame->BaParm),
			sizeof(BA_PARM));
		*(USHORT *) (&tmpBaParm) = cpu2le16(*(USHORT *) (&tmpBaParm));
		NdisMoveMemory((PUCHAR) (&pAddFrame->BaParm), (PUCHAR) (&tmpBaParm),
			sizeof(BA_PARM));
	}
#else
	*(USHORT *) (&pAddFrame->BaParm) = cpu2le16(*(USHORT *) (&pAddFrame->BaParm));
#endif /* endif */
	pAddFrame->TimeOutValue = cpu2le16(pAddFrame->TimeOutValue);
	pAddFrame->BaStartSeq.word = cpu2le16(pAddFrame->BaStartSeq.word);

	COPY_MAC_ADDR(pAddr2, pFrame->Hdr.Addr2);

	if (pAddFrame->BaParm.BAPolicy != IMMED_BA) {
		DBGPRINT(RT_DEBUG_ERROR,
			("PeerAddBAReqActionSanity: ADDBA Request Ba Policy[%d] not support\n",
			pAddFrame->BaParm.BAPolicy));
		DBGPRINT(RT_DEBUG_ERROR,
			("ADDBA Request. tid=%x, Bufsize=%x, AMSDUSupported=%x\n",
			pAddFrame->BaParm.TID, pAddFrame->BaParm.BufSize,
			pAddFrame->BaParm.AMSDUSupported));
		return FALSE;
	}

	return TRUE;
}

BOOLEAN PeerAddBARspActionSanity(IN PRTMP_ADAPTER pAd, IN VOID * pMsg, IN ULONG MsgLen)
{
	PFRAME_ADDBA_RSP pAddFrame;

	pAddFrame = (PFRAME_ADDBA_RSP) (pMsg);
	if (MsgLen < (sizeof(FRAME_ADDBA_RSP))) {
		DBGPRINT(RT_DEBUG_ERROR,
			("%s(): ADDBA Resp frame length incorrect(len=%ld)\n", __func__, MsgLen));
		return FALSE;
	}
	/* we support immediate BA. */
#ifdef UNALIGNMENT_SUPPORT
	{
		BA_PARM tmpBaParm;

		NdisMoveMemory((PUCHAR) (&tmpBaParm), (PUCHAR) (&pAddFrame->BaParm),
			sizeof(BA_PARM));
		*(USHORT *) (&tmpBaParm) = cpu2le16(*(USHORT *) (&tmpBaParm));
		NdisMoveMemory((PUCHAR) (&pAddFrame->BaParm), (PUCHAR) (&tmpBaParm),
			sizeof(BA_PARM));
	}
#else
	*(USHORT *) (&pAddFrame->BaParm) = cpu2le16(*(USHORT *) (&pAddFrame->BaParm));
#endif /* endif */
	pAddFrame->StatusCode = cpu2le16(pAddFrame->StatusCode);
	pAddFrame->TimeOutValue = cpu2le16(pAddFrame->TimeOutValue);

	if (pAddFrame->BaParm.BAPolicy != IMMED_BA) {
		DBGPRINT(RT_DEBUG_ERROR,
			("%s(): ADDBA Resp Ba Policy[%d] not support\n", __func__,
			pAddFrame->BaParm.BAPolicy));
		return FALSE;
	}

	return TRUE;

}

BOOLEAN PeerDelBAActionSanity(IN PRTMP_ADAPTER pAd, IN UCHAR Wcid, IN VOID * pMsg, IN ULONG MsgLen)
{
	PFRAME_DELBA_REQ pDelFrame;

	if (MsgLen != (sizeof(FRAME_DELBA_REQ)))
		return FALSE;

	if (Wcid >= MAX_LEN_OF_MAC_TABLE)
		return FALSE;

	pDelFrame = (PFRAME_DELBA_REQ) (pMsg);

	*(USHORT *) (&pDelFrame->DelbaParm) = cpu2le16(*(USHORT *) (&pDelFrame->DelbaParm));
	pDelFrame->ReasonCode = cpu2le16(pDelFrame->ReasonCode);

	return TRUE;
}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN PeerBeaconAndProbeRspSanity(IN PRTMP_ADAPTER pAd,
				    IN VOID * Msg,
				    IN ULONG MsgLen,
				    IN UCHAR MsgChannel,
				    OUT BCN_IE_LIST * ie_list,
				    OUT USHORT *LengthVIE, OUT PNDIS_802_11_VARIABLE_IEs pVIE)
{
	UCHAR *Ptr;
#ifdef CONFIG_STA_SUPPORT
	UCHAR TimLen;
#ifdef IWSC_SUPPORT
	BOOLEAN bFoundIWscIe = FALSE;
	USHORT PeerConfigMethod = 0;
#endif /* IWSC_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
	PFRAME_802_11 pFrame;
	PEID_STRUCT pEid;
	UCHAR SubType;
	UCHAR Sanity;
	ULONG Length = 0;
	UCHAR *pPeerWscIe = NULL;
	INT PeerWscIeLen = 0;
	BOOLEAN bWscCheck = TRUE;
	UCHAR LatchRfChannel = 0;

	/*
	   For some 11a AP which didn't have DS_IE, we use two conditions to decide the channel
	   1. If the AP is 11n enabled, then check the control channel.
	   2. If the AP didn't have any info about channel, use the channel we received this
	   frame as the channel. (May inaccuracy!!)
	 */
	UCHAR CtrlChannel = 0;

	os_alloc_mem(NULL, &pPeerWscIe, 512);
	Sanity = 0;		/* Add for 3 necessary EID field check */

	ie_list->AironetCellPowerLimit = 0xFF;	/* Default of AironetCellPowerLimit is 0xFF */
	ie_list->NewExtChannelOffset = 0xff;	/*Default 0xff means no such IE */
	*LengthVIE = 0;		/* Set the length of VIE to init value 0 */

	pFrame = (PFRAME_802_11) Msg;

	/* get subtype from header */
	SubType = (UCHAR) pFrame->Hdr.FC.SubType;

	/* get Addr2 and BSSID from header */
	COPY_MAC_ADDR(&ie_list->Addr2[0], pFrame->Hdr.Addr2);
	COPY_MAC_ADDR(&ie_list->Bssid[0], pFrame->Hdr.Addr3);

	Ptr = pFrame->Octet;
	Length += LENGTH_802_11;

	/* get timestamp from payload and advance the pointer */
	NdisMoveMemory(&ie_list->TimeStamp, Ptr, TIMESTAMP_LEN);

	ie_list->TimeStamp.u.LowPart = cpu2le32(ie_list->TimeStamp.u.LowPart);
	ie_list->TimeStamp.u.HighPart = cpu2le32(ie_list->TimeStamp.u.HighPart);

	Ptr += TIMESTAMP_LEN;
	Length += TIMESTAMP_LEN;

	/* get beacon interval from payload and advance the pointer */
	NdisMoveMemory(&ie_list->BeaconPeriod, Ptr, 2);
	Ptr += 2;
	Length += 2;

	/* get capability info from payload and advance the pointer */
	NdisMoveMemory(&ie_list->CapabilityInfo, Ptr, 2);
	Ptr += 2;
	Length += 2;

	if (CAP_IS_ESS_ON(ie_list->CapabilityInfo))
		ie_list->BssType = BSS_INFRA;
	else
		ie_list->BssType = BSS_ADHOC;

	/* init ExtCapInfo length to zero */
	ie_list->ExtCapInfoLen = 0;

	pEid = (PEID_STRUCT) Ptr;

	/* get variable fields from payload and advance the pointer */
	while ((Length + 2 + pEid->Len) <= MsgLen) {

		/* Secure copy VIE to VarIE[MAX_VIE_LEN] didn't overflow. */
		if ((*LengthVIE + pEid->Len + 2) >= MAX_VIE_LEN) {
			DBGPRINT(RT_DEBUG_WARN,
				 ("%s() - Variable IEs out of resource [len(=%d) > MAX_VIE_LEN(=%d)]\n",
				  __func__, (*LengthVIE + pEid->Len + 2), MAX_VIE_LEN));
			break;
		}

		switch (pEid->Eid) {
		case IE_SSID:
			/* Already has one SSID EID in this beacon, ignore the second one */
			if (Sanity & 0x1)
				break;
			if (pEid->Len <= MAX_LEN_OF_SSID) {
				NdisMoveMemory(&ie_list->Ssid[0], pEid->Octet, pEid->Len);
				ie_list->SsidLen = pEid->Len;
				Sanity |= 0x1;
			} else {
				DBGPRINT(RT_DEBUG_TRACE,
					("%s() - wrong IE_SSID (len=%d)\n", __func__, pEid->Len));
				goto SanityCheck;
			}
			break;

		case IE_SUPP_RATES:
			if (pEid->Len <= MAX_LEN_OF_SUPPORTED_RATES) {
				Sanity |= 0x2;
				NdisMoveMemory(&ie_list->SupRate[0], pEid->Octet, pEid->Len);
				ie_list->SupRateLen = pEid->Len;

				/*
				   TODO: 2004-09-14 not a good design here, cause it exclude extra
				   rates from ScanTab. We should report as is. And filter out
				   unsupported rates in MlmeAux
				 */
				/* Check against the supported rates */
				/* RTMPCheckRates(pAd, SupRate, pSupRateLen); */
			} else {
				DBGPRINT(RT_DEBUG_TRACE,
					("%s() - wrong IE_SUPP_RATES (len=%d)\n", __func__,
					pEid->Len));
				goto SanityCheck;
			}
			break;

		case IE_HT_CAP:
			if (pEid->Len >= SIZE_HT_CAP_IE) {	/*Note: allow extension.!! */
				NdisMoveMemory(&ie_list->HtCapability, pEid->Octet,
					sizeof(HT_CAPABILITY_IE));
				ie_list->HtCapabilityLen = SIZE_HT_CAP_IE;	/* Nnow we only support 26 bytes. */

				*(USHORT *) (&ie_list->HtCapability.HtCapInfo) =
				    cpu2le16(*(USHORT *) (&ie_list->HtCapability.HtCapInfo));
#ifdef UNALIGNMENT_SUPPORT
				{
					EXT_HT_CAP_INFO extHtCapInfo;

					NdisMoveMemory((PUCHAR) (&extHtCapInfo),
						(PUCHAR) (&ie_list->HtCapability.
						ExtHtCapInfo),
						sizeof(EXT_HT_CAP_INFO));
					*(USHORT *) (&extHtCapInfo) =
						cpu2le16(*(USHORT *) (&extHtCapInfo));
					NdisMoveMemory((PUCHAR)
						(&ie_list->HtCapability.ExtHtCapInfo),
						(PUCHAR) (&extHtCapInfo),
						sizeof(EXT_HT_CAP_INFO));
				}
#else
				*(USHORT *) (&ie_list->HtCapability.ExtHtCapInfo) =
				    cpu2le16(*(USHORT *) (&ie_list->HtCapability.ExtHtCapInfo));
#endif /* UNALIGNMENT_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
				IF_DEV_CONFIG_OPMODE_ON_STA(pAd) {
					ie_list->PreNHtCapabilityLen = 0;	/* Now we only support 26 bytes. */

					Ptr = (PUCHAR) pVIE;
					NdisMoveMemory(Ptr + *LengthVIE, &pEid->Eid, pEid->Len + 2);
					*LengthVIE += (pEid->Len + 2);
				}
#endif /* CONFIG_STA_SUPPORT */
			} else {
				DBGPRINT(RT_DEBUG_WARN,
					("%s() - wrong IE_HT_CAP. pEid->Len = %d\n", __func__,
					pEid->Len));
			}

			break;
		case IE_ADD_HT:
			if (pEid->Len >= sizeof(ADD_HT_INFO_IE)) {
				/*
				   This IE allows extension, but we can ignore extra bytes beyond our
				   knowledge , so only copy first sizeof(ADD_HT_INFO_IE)
				 */
				NdisMoveMemory(&ie_list->AddHtInfo, pEid->Octet,
					sizeof(ADD_HT_INFO_IE));
				ie_list->AddHtInfoLen = SIZE_ADD_HT_INFO_IE;

				CtrlChannel = ie_list->AddHtInfo.ControlChan;

				*(USHORT *) (&ie_list->AddHtInfo.AddHtInfo2) =
				    cpu2le16(*(USHORT *) (&ie_list->AddHtInfo.AddHtInfo2));
				*(USHORT *) (&ie_list->AddHtInfo.AddHtInfo3) =
				    cpu2le16(*(USHORT *) (&ie_list->AddHtInfo.AddHtInfo3));

#ifdef CONFIG_STA_SUPPORT
				IF_DEV_CONFIG_OPMODE_ON_STA(pAd) {
					Ptr = (PUCHAR) pVIE;
					NdisMoveMemory(Ptr + *LengthVIE, &pEid->Eid, pEid->Len + 2);
					*LengthVIE += (pEid->Len + 2);
				}
#endif /* CONFIG_STA_SUPPORT */
			} else
				DBGPRINT(RT_DEBUG_WARN, ("%s() - wrong IE_ADD_HT.\n", __func__));

			break;
		case IE_SECONDARY_CH_OFFSET:
			if (pEid->Len == 1)
				ie_list->NewExtChannelOffset = pEid->Octet[0];
			else
				DBGPRINT(RT_DEBUG_WARN,
					("%s() - wrong IE_SECONDARY_CH_OFFSET.\n", __func__));
			break;

		case IE_FH_PARM:
			DBGPRINT(RT_DEBUG_TRACE, ("%s(IE_FH_PARM)\n", __func__));
			break;

		case IE_DS_PARM:
			if (pEid->Len == 1) {
				ie_list->Channel = *pEid->Octet;
#ifdef CONFIG_STA_SUPPORT
				IF_DEV_CONFIG_OPMODE_ON_STA(pAd) {
					if (ChannelSanity(pAd, ie_list->Channel) == 0)
						goto SanityCheck;
				}
#endif /* CONFIG_STA_SUPPORT */
				Sanity |= 0x4;
			} else {
				DBGPRINT(RT_DEBUG_TRACE,
					("%s() - wrong IE_DS_PARM (len=%d)\n", __func__,
					pEid->Len));
				goto SanityCheck;
			}
			break;

		case IE_CF_PARM:
			if (pEid->Len == 6) {
				ie_list->CfParm.bValid = TRUE;
				ie_list->CfParm.CfpCount = pEid->Octet[0];
				ie_list->CfParm.CfpPeriod = pEid->Octet[1];
				ie_list->CfParm.CfpMaxDuration =
					pEid->Octet[2] + 256 * pEid->Octet[3];
				ie_list->CfParm.CfpDurRemaining =
					pEid->Octet[4] + 256 * pEid->Octet[5];
			} else {
				DBGPRINT(RT_DEBUG_TRACE, ("%s() - wrong IE_CF_PARM\n", __func__));
				if (pPeerWscIe)
					os_free_mem(NULL, pPeerWscIe);
				return FALSE;
			}
			break;

		case IE_IBSS_PARM:
			if (pEid->Len == 2) {
				NdisMoveMemory(&ie_list->AtimWin, pEid->Octet, pEid->Len);
			} else {
				DBGPRINT(RT_DEBUG_TRACE, ("%s() - wrong IE_IBSS_PARM\n", __func__));
				if (pPeerWscIe)
					os_free_mem(NULL, pPeerWscIe);
				return FALSE;
			}
			break;

#ifdef CONFIG_STA_SUPPORT
		case IE_TIM:
			if (SubType == SUBTYPE_BEACON) {
#if defined(P2P_SUPPORT) || defined(RT_CFG80211_P2P_SUPPORT)
				if (
#ifdef RT_CFG80211_P2P_SUPPORT
					   CFG_P2PCLI_ON(pAd)
#endif /* RT_CFG80211_P2P_SUPPORT */
					   && NdisEqualMemory(&ie_list->Bssid[0],
							pAd->ApCfg.ApCliTab[0].MlmeAux.Bssid,
							MAC_ADDR_LEN)) {
					GetTimBit((PCHAR) pEid, pAd->ApCfg.ApCliTab[0].MlmeAux.Aid,
						  &TimLen, &ie_list->BcastFlag, &ie_list->DtimCount,
						  &ie_list->DtimPeriod, &ie_list->MessageToMe);
				}
#endif /*defined(P2P_SUPPORT) || defined(RT_CFG80211_P2P_SUPPORT) */

				if (INFRA_ON(pAd)
				    && NdisEqualMemory(&ie_list->Bssid[0], pAd->CommonCfg.Bssid,
					MAC_ADDR_LEN)) {
					GetTimBit((PCHAR) pEid, pAd->StaActive.Aid, &TimLen,
						  &ie_list->BcastFlag, &ie_list->DtimCount,
						  &ie_list->DtimPeriod, &ie_list->MessageToMe);
				}
			}
			break;
#endif /* CONFIG_STA_SUPPORT */
		case IE_CHANNEL_SWITCH_ANNOUNCEMENT:
			if (pEid->Len == 3 && MAC_ADDR_EQUAL(pAd->MlmeAux.Bssid, ie_list->Bssid)) {
				ie_list->NewChannel = pEid->Octet[1];	/*extract new channel number */
#ifdef CONFIG_DFS_SLAVE
				pAd->StaCfg.bChannelSwitchCountingDown = TRUE;
				pAd->CommonCfg.ChannelSwitchMode = pEid->Octet[0];
				pAd->CommonCfg.NewChannel = pEid->Octet[1];
				pAd->CommonCfg.ChannelSwitchCount = pEid->Octet[2];

				if (pAd->CommonCfg.ChannelSwitchCount > 0)
					--pAd->CommonCfg.ChannelSwitchCount;

				DBGPRINT(RT_DEBUG_ERROR,
					 ("%s, CSA IE from current BSS[%02x:%02x:%02x:%02x:%02x:%02x]: Mode:%d, New_Chnl:%d, Cnt:%d\n",
					  __func__, ie_list->Bssid[0], ie_list->Bssid[1],
					  ie_list->Bssid[2], ie_list->Bssid[3], ie_list->Bssid[4],
					  ie_list->Bssid[5], pAd->CommonCfg.ChannelSwitchMode,
					  pAd->CommonCfg.NewChannel,
					  pAd->CommonCfg.ChannelSwitchCount));
#endif /* endif */

			}
			break;

			/*
			   New for WPA
			   CCX v2 has the same IE, we need to parse that too
			   Wifi WMM use the same IE vale, need to parse that too
			 */
			/* case IE_WPA: */
		case IE_VENDOR_SPECIFIC:
			/* Check the OUI version, filter out non-standard usage */
			if (NdisEqualMemory(pEid->Octet, RALINK_OUI, 3) && (pEid->Len == 7)) {
				if (pEid->Octet[3] != 0)
					ie_list->RalinkIe = pEid->Octet[3];
				else
					/* Set to non-zero value (can't set bit0-2)
					* to represent this is Ralink Chip.
					* So at linkup, we will set ralinkchip flag.
					*/
					ie_list->RalinkIe = 0xf0000000;
			}
#ifdef CONFIG_STA_SUPPORT
			/* This HT IE is before IEEE draft set HT IE value.2006-09-28 by Jan. */

			/* Other vendors had production before IE_HT_CAP value
			* is assigned. To backward support those old-firmware AP,
			* Check broadcom-defiend pre-802.11nD1.0 OUI for HT related IE,
			* including HT Capatilities IE and HT Information IE
			*/
			else if ((ie_list->HtCapabilityLen == 0)
				 && NdisEqualMemory(pEid->Octet, BROADCOM_OUI, 3)
				 && (pEid->Len >= 4) && (pAd->OpMode == OPMODE_STA)) {
				if ((pEid->Octet[3] == OUI_BROADCOM_HT) && (pEid->Len >= 30)
				    && (ie_list->HtCapabilityLen == 0)) {
					NdisMoveMemory(&ie_list->HtCapability, &pEid->Octet[4],
						       sizeof(HT_CAPABILITY_IE));
					ie_list->PreNHtCapabilityLen = SIZE_HT_CAP_IE;
				}

				if ((pEid->Octet[3] == OUI_PREN_ADD_HT) && (pEid->Len >= 26)) {
					NdisMoveMemory(&ie_list->AddHtInfo, &pEid->Octet[4],
						sizeof(ADD_HT_INFO_IE));
					ie_list->AddHtInfoLen = SIZE_ADD_HT_INFO_IE;
				}
			}
#endif /* CONFIG_STA_SUPPORT */
			else if (NdisEqualMemory(pEid->Octet, WPA_OUI, 4)) {
				/* Copy to pVIE which will report to bssid list. */
				Ptr = (PUCHAR) pVIE;
				NdisMoveMemory(Ptr + *LengthVIE, &pEid->Eid, pEid->Len + 2);
				*LengthVIE += (pEid->Len + 2);
			} else if (NdisEqualMemory(pEid->Octet, WME_PARM_ELEM, 6)
				   && (pEid->Len == 24)) {
				PUCHAR ptr;
				int i;

				/* parsing EDCA parameters */
				ie_list->EdcaParm.bValid = TRUE;
				ie_list->EdcaParm.bQAck = FALSE;	/* pEid->Octet[0] & 0x10; */
				ie_list->EdcaParm.bQueueRequest = FALSE;	/* pEid->Octet[0] & 0x20; */
				ie_list->EdcaParm.bTxopRequest = FALSE;	/* pEid->Octet[0] & 0x40; */
				ie_list->EdcaParm.EdcaUpdateCount = pEid->Octet[6] & 0x0f;
				ie_list->EdcaParm.bAPSDCapable = (pEid->Octet[6] & 0x80) ? 1 : 0;
				ptr = &pEid->Octet[8];
				for (i = 0; i < 4; i++) {
					UCHAR aci = (*ptr & 0x60) >> 5;	/* b5~6 is AC INDEX */

					ie_list->EdcaParm.bACM[aci] = (((*ptr) & 0x10) == 0x10);	/* b5 is ACM */
					ie_list->EdcaParm.Aifsn[aci] = (*ptr) & 0x0f;	/* b0~3 is AIFSN */
					ie_list->EdcaParm.Cwmin[aci] = *(ptr + 1) & 0x0f;	/* b0~4 is Cwmin */
					ie_list->EdcaParm.Cwmax[aci] = *(ptr + 1) >> 4;	/* b5~8 is Cwmax */
					/* in unit of 32-us */
					ie_list->EdcaParm.Txop[aci] =
						*(ptr + 2) + 256 * (*(ptr + 3));
					ptr += 4;	/* point to next AC */
				}
			} else if (NdisEqualMemory(pEid->Octet, WME_INFO_ELEM, 6)
				   && (pEid->Len == 7)) {
				/* parsing EDCA parameters */
				ie_list->EdcaParm.bValid = TRUE;
				ie_list->EdcaParm.bQAck = FALSE;	/* pEid->Octet[0] & 0x10; */
				ie_list->EdcaParm.bQueueRequest = FALSE;	/* pEid->Octet[0] & 0x20; */
				ie_list->EdcaParm.bTxopRequest = FALSE;	/* pEid->Octet[0] & 0x40; */
				ie_list->EdcaParm.EdcaUpdateCount = pEid->Octet[6] & 0x0f;
				ie_list->EdcaParm.bAPSDCapable = (pEid->Octet[6] & 0x80) ? 1 : 0;

				/* use default EDCA parameter */
				ie_list->EdcaParm.bACM[QID_AC_BE] = 0;
				ie_list->EdcaParm.Aifsn[QID_AC_BE] = 3;
				ie_list->EdcaParm.Cwmin[QID_AC_BE] = pAd->wmm_cw_min;
				ie_list->EdcaParm.Cwmax[QID_AC_BE] = pAd->wmm_cw_max;
				ie_list->EdcaParm.Txop[QID_AC_BE] = 0;

				ie_list->EdcaParm.bACM[QID_AC_BK] = 0;
				ie_list->EdcaParm.Aifsn[QID_AC_BK] = 7;
				ie_list->EdcaParm.Cwmin[QID_AC_BK] = pAd->wmm_cw_min;
				ie_list->EdcaParm.Cwmax[QID_AC_BK] = pAd->wmm_cw_max;
				ie_list->EdcaParm.Txop[QID_AC_BK] = 0;

				ie_list->EdcaParm.bACM[QID_AC_VI] = 0;
				ie_list->EdcaParm.Aifsn[QID_AC_VI] = 2;
				ie_list->EdcaParm.Cwmin[QID_AC_VI] = pAd->wmm_cw_min - 1;
				ie_list->EdcaParm.Cwmax[QID_AC_VI] = pAd->wmm_cw_max;
				ie_list->EdcaParm.Txop[QID_AC_VI] = 96;	/* AC_VI: 96*32us ~= 3ms */

				ie_list->EdcaParm.bACM[QID_AC_VO] = 0;
				ie_list->EdcaParm.Aifsn[QID_AC_VO] = 2;
				ie_list->EdcaParm.Cwmin[QID_AC_VO] = pAd->wmm_cw_min - 2;
				ie_list->EdcaParm.Cwmax[QID_AC_VO] = pAd->wmm_cw_max - 1;
				ie_list->EdcaParm.Txop[QID_AC_VO] = 48;	/* AC_VO: 48*32us ~= 1.5ms */
			} else if (NdisEqualMemory(pEid->Octet, WPS_OUI, 4)
#ifdef IWSC_SUPPORT
				   || NdisEqualMemory(pEid->Octet, IWSC_OUI, 4)
#endif /* IWSC_SUPPORT // */
			    ) {
				if (pPeerWscIe) {
					/* Ignore old WPS IE fragments, if we get the version 0x10 */
					if (pEid->Octet[4] == 0x10) {	/* First WPS IE will have version 0x10 */
						NdisMoveMemory(pPeerWscIe, pEid->Octet + 4,
							pEid->Len - 4);
						PeerWscIeLen = (pEid->Len - 4);
					} else {
						/* reassembly remanning, other IE
						*  fragmentations will not have
						* version 0x10
						*/

						if ((PeerWscIeLen + (pEid->Len - 4)) <= 512) {
							NdisMoveMemory(pPeerWscIe + PeerWscIeLen,
									pEid->Octet + 4,
									pEid->Len - 4);
							PeerWscIeLen += (pEid->Len - 4);
						} else {	/* ((PeerWscIeLen +(pEid->Len - 4)) > 512) */

							bWscCheck = FALSE;
							DBGPRINT(RT_DEBUG_ERROR,
								 ("%s: Error!!! Sum of All PeerWscIeLen = %d (> 512)\n",
								  __func__,
								  (PeerWscIeLen +
								   (pEid->Len - 4))));
						}
					}
				} else {
					bWscCheck = FALSE;
					DBGPRINT(RT_DEBUG_ERROR,
						("%s: Error!!! pPeerWscIe is empty!\n", __func__));
				}

#ifdef IWSC_SUPPORT
				if (NdisEqualMemory(pEid->Octet, IWSC_OUI, 4))
					bFoundIWscIe = TRUE;
#endif /* IWSC_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef NATIVE_WPA_SUPPLICANT_SUPPORT
				if (SubType == SUBTYPE_BEACON) {
					PUCHAR pData;
					INT Len = 0;
					USHORT DataLen = 0;
					PWSC_IE pWscIE;

					pData = (PUCHAR) pEid->Octet + 4;
					Len = (SHORT) (pEid->Len - 4);

					while (Len > 0) {
						WSC_IE WscIE;

						NdisMoveMemory(&WscIE, pData, sizeof(WSC_IE));
						/* Check for WSC IEs */
						pWscIE = &WscIE;

						if (be2cpu16(pWscIE->Type) ==
							0x1041 /*WSC_ID_SEL_REGISTRAR */) {
							DataLen = be2cpu16(pWscIE->Length);
							NdisMoveMemory(&ie_list->selReg, pData + 4,
								sizeof(ie_list->selReg));
							break;
						}
						/* Set the offset and look for next WSC Tag information */
						/* Since Type and Length are both short type,
						*  we need to offset 4, not 2
						*/
						pData += (be2cpu16(pWscIE->Length) + 4);
						Len -= (be2cpu16(pWscIE->Length) + 4);
					}

					/* WscGetDataFromPeerByTag(pAd, pPeerWscIe, PeerWscIeLen,
					*  WSC_ID_SEL_REGISTRAR, &bSelReg, NULL);
					*/
				}
#endif /* NATIVE_WPA_SUPPLICANT_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

			}

			break;

		case IE_EXT_SUPP_RATES:
			if (pEid->Len <= MAX_LEN_OF_SUPPORTED_RATES) {
				NdisMoveMemory(&ie_list->ExtRate[0], pEid->Octet, pEid->Len);
				ie_list->ExtRateLen = pEid->Len;

				/*
				   TODO: 2004-09-14 not a good design here, cause it exclude extra rates
				   from ScanTab. We should report as is. And filter out unsupported
				   rates in MlmeAux
				 */
				/* Check against the supported rates */
				/* RTMPCheckRates(pAd, ExtRate, pExtRateLen); */
			}
			break;

		case IE_ERP:
			if (pEid->Len == 1)
				ie_list->Erp = (UCHAR) pEid->Octet[0];
			break;

		case IE_AIRONET_CKIP:
			/*
			   0. Check Aironet IE length, it must be larger or equal to 28
			   Cisco AP350 used length as 28
			   Cisco AP12XX used length as 30
			 */
			if (pEid->Len < (CKIP_NEGOTIATION_LENGTH - 2))
				break;

			/* 1. Copy CKIP flag byte to buffer for process */
			ie_list->CkipFlag = *(pEid->Octet + 8);
			break;

		case IE_AP_TX_POWER:
			/* AP Control of Client Transmit Power */
			/*0. Check Aironet IE length, it must be 6 */
			if (pEid->Len != 0x06)
				break;

			/* Get cell power limit in dBm */
			if (NdisEqualMemory(pEid->Octet, CISCO_OUI, 3) == 1)
				ie_list->AironetCellPowerLimit = *(pEid->Octet + 4);
			break;

			/* WPA2 & 802.11i RSN */
		case IE_RSN:
			/* There is no OUI for version anymore, check the group cipher OUI before copying */
			if (RTMPEqualMemory(pEid->Octet + 2, RSN_OUI, 3)) {
				/* Copy to pVIE which will report to microsoft bssid list. */
				Ptr = (PUCHAR) pVIE;
				NdisMoveMemory(Ptr + *LengthVIE, &pEid->Eid, pEid->Len + 2);
				*LengthVIE += (pEid->Len + 2);
			}
			break;

#ifdef WAPI_SUPPORT
			/* WAPI information element */
		case IE_WAPI:
			if (RTMPEqualMemory(pEid->Octet + 4, WAPI_OUI, 3)) {
				/* Copy to pVIE */
				Ptr = (PUCHAR) pVIE;
				NdisMoveMemory(Ptr + *LengthVIE, &pEid->Eid, pEid->Len + 2);
				*LengthVIE += (pEid->Len + 2);
			}
			break;
#endif /* WAPI_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#if defined(EXT_BUILD_CHANNEL_LIST) || defined(RT_CFG80211_SUPPORT)
		case IE_COUNTRY:
			Ptr = (PUCHAR) pVIE;
			NdisMoveMemory(Ptr + *LengthVIE, &pEid->Eid, pEid->Len + 2);
			*LengthVIE += (pEid->Len + 2);
			break;
#endif /* EXT_BUILD_CHANNEL_LIST */
#endif /* CONFIG_STA_SUPPORT */

		case IE_QBSS_LOAD:
			if (pEid->Len == 5) {
				ie_list->QbssLoad.bValid = TRUE;
				ie_list->QbssLoad.StaNum = pEid->Octet[0] + pEid->Octet[1] * 256;
				ie_list->QbssLoad.ChannelUtilization = pEid->Octet[2];
				ie_list->QbssLoad.RemainingAdmissionControl =
					pEid->Octet[3] + pEid->Octet[4] * 256;

				/* Copy to pVIE */
				Ptr = (PUCHAR) pVIE;
				NdisMoveMemory(Ptr + *LengthVIE, &pEid->Eid, pEid->Len + 2);
				*LengthVIE += (pEid->Len + 2);
			}
			break;

		case IE_EXT_CAPABILITY:
			if (pEid->Len >= 1) {
				UCHAR cp_len, buf_space = sizeof(EXT_CAP_INFO_ELEMENT);

				cp_len = min(pEid->Len, buf_space);
				NdisMoveMemory(&ie_list->ExtCapInfo, &pEid->Octet[0], cp_len);
				ie_list->ExtCapInfoLen = cp_len;
			}
			break;

#ifdef DOT11_VHT_AC
		case IE_VHT_CAP:
			if (pEid->Len == sizeof(VHT_CAP_IE)) {
				NdisMoveMemory(&ie_list->vht_cap_ie, &pEid->Octet[0],
					sizeof(VHT_CAP_IE));
				ie_list->vht_cap_len = pEid->Len;
			}
			break;
		case IE_VHT_OP:
			if (pEid->Len == sizeof(VHT_OP_IE)) {
				NdisMoveMemory(&ie_list->vht_op_ie, &pEid->Octet[0],
					sizeof(VHT_OP_IE));
				ie_list->vht_op_len = pEid->Len;
			}
			break;
		case IE_OPERATING_MODE_NOTIFY:
			if (pEid->Len == sizeof(OPERATING_MODE)) {
				NdisMoveMemory(&ie_list->operating_mode, &pEid->Octet[0],
					sizeof(OPERATING_MODE));
				ie_list->vht_op_mode_len = pEid->Len;

				DBGPRINT(RT_DEBUG_INFO,
					("%s() - IE_OPERATING_MODE_NOTIFY(=%d)\n", __func__,
					pEid->Eid));
			}
			break;
#endif /* DOT11_VHT_AC */

		default:
			break;
		}

		Length = Length + 2 + pEid->Len;	/* Eid[1] + Len[1]+ content[Len] */
		pEid = (PEID_STRUCT) ((UCHAR *) pEid + 2 + pEid->Len);
	}

	LatchRfChannel = MsgChannel;

/* this will lead Infra can't get beacon, when Infra on 5G then p2p in 2G. */
#ifdef CONFIG_MULTI_CHANNEL
	if (((Sanity & 0x4) == 0))
#else /* CONFIG_MULTI_CHANNEL */
	if ((pAd->LatchRfRegs.Channel > 14) && ((Sanity & 0x4) == 0))
#endif /* !CONFIG_MULTI_CHANNEL */
		{
			if (CtrlChannel != 0)
				ie_list->Channel = CtrlChannel;
			else {
				if ((pAd->CommonCfg.RegTransmitSetting.field.BW == BW_40)
#ifdef DOT11_VHT_AC
				    || (pAd->CommonCfg.RegTransmitSetting.field.BW == BW_80)
#endif /* DOT11_VHT_AC */
				    ) {
					if (pAd->MlmeAux.Channel)
						ie_list->Channel = pAd->MlmeAux.Channel;
					else
						ie_list->Channel = pAd->CommonCfg.Channel;
				} else
					ie_list->Channel = LatchRfChannel;
			}
			Sanity |= 0x4;
		}

	if (pPeerWscIe && (PeerWscIeLen > 0) && (PeerWscIeLen <= 512) && (bWscCheck == TRUE)) {
		UCHAR WscIe[] = { 0xdd, 0x00, 0x00, 0x50, 0xF2, 0x04 };

		Ptr = (PUCHAR) pVIE;
		WscIe[1] = PeerWscIeLen + 4;
		NdisMoveMemory(Ptr + *LengthVIE, WscIe, 6);
		NdisMoveMemory(Ptr + *LengthVIE + 6, pPeerWscIe, PeerWscIeLen);
		*LengthVIE += (PeerWscIeLen + 6);
#ifdef IWSC_SUPPORT
		if ((pAd->StaCfg.BssType == BSS_ADHOC) &&
			(SubType == SUBTYPE_PROBE_RSP) && (bFoundIWscIe == TRUE)) {
			BOOLEAN bSelReg = FALSE;
			USHORT DataLen = 0;

			/* re-use this boolean variable */
			bFoundIWscIe = FALSE;
			WscGetDataFromPeerByTag(pAd, pPeerWscIe, PeerWscIeLen, WSC_ID_SEL_REGISTRAR,
				&bSelReg, NULL);
			if (bSelReg) {
				bFoundIWscIe = TRUE;
				if (WscGetDataFromPeerByTag(pAd,
							pPeerWscIe,
							PeerWscIeLen,
							WSC_ID_MAC_ADDR,
							&pAd->StaCfg.WscControl.WscPeerMAC[0],
							NULL) == FALSE) {
					NdisMoveMemory(&pAd->StaCfg.WscControl.WscPeerMAC[0],
						       &ie_list->Addr2[0], MAC_ADDR_LEN);
				}
				NdisMoveMemory(&pAd->StaCfg.WscControl.EntryAddr[0],
					       &pAd->StaCfg.WscControl.WscPeerMAC[0], MAC_ADDR_LEN);
				hex_dump("PeerBeaconAndProbeRspSanity - WscPeerMAC",
					 &pAd->StaCfg.WscControl.WscPeerMAC[0], MAC_ADDR_LEN);

				WscGetDataFromPeerByTag(pAd,
							pPeerWscIe,
							PeerWscIeLen,
							WSC_ID_SEL_REG_CFG_METHODS,
							&PeerConfigMethod, NULL);
			}
		}
#endif /* IWSC_SUPPORT */
	}

SanityCheck:
	if (pPeerWscIe)
		os_free_mem(NULL, pPeerWscIe);

	if ((Sanity != 0x7) || (bWscCheck == FALSE)) {

#ifdef CONFIG_MULTI_CHANNEL	/* def WIDI_SUPPORT */
		DBGPRINT(RT_DEBUG_TRACE,
			 ("%s Sanity Failed, Sanity=%02x, MsgChannel=%u, pAd->LatchRfRegs.Channel=%u\n",
			  __func__, Sanity, MsgChannel, pAd->LatchRfRegs.Channel));
#endif /* CONFIG_MULTI_CHANNEL */
		DBGPRINT(RT_DEBUG_LOUD,
			("%s() - missing field, Sanity=0x%02x\n", __func__, Sanity));
		return FALSE;
	}
#ifdef IWSC_SUPPORT
	if (bFoundIWscIe && (pAd->StaCfg.BssType == BSS_ADHOC)) {
		PWSC_CTRL pWscCtrl = &pAd->StaCfg.WscControl;

		if ((pWscCtrl->WscConfMode == WSC_ENROLLEE) &&
		    (pWscCtrl->WscMode == WSC_PIN_MODE) && (pWscCtrl->bWscTrigger == TRUE)) {
			NdisZeroMemory(&pWscCtrl->WscSsid, sizeof(NDIS_802_11_SSID));
			if ((ie_list->SsidLen) <= 32 && (ie_list->SsidLen) != 0) {
				pWscCtrl->WscSsid.SsidLength = ie_list->SsidLen;
				NdisMoveMemory(pWscCtrl->WscSsid.Ssid, &ie_list->Ssid[0],
					pWscCtrl->WscSsid.SsidLength);
				PeerConfigMethod = be2cpu16(PeerConfigMethod);
				MlmeEnqueue(pAd, IWSC_STATE_MACHINE,
					IWSC_MT2_PEER_PROBE_RSP, sizeof(USHORT),
					&PeerConfigMethod, 0);
			}
		}
	}
#endif /* IWSC_SUPPORT */
	return TRUE;
}

/*
	==========================================================================
	Description:
		MLME message sanity check for some IE addressed	 in 802.11n d3.03.
	Return:
		TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

	==========================================================================
 */
BOOLEAN PeerBeaconAndProbeRspSanity2(IN PRTMP_ADAPTER pAd,
				IN VOID * Msg,
				IN ULONG MsgLen,
				IN OVERLAP_BSS_SCAN_IE * BssScan,
				OUT BCN_IE_LIST * ie_list, OUT UCHAR *RegClass)
{
	CHAR *Ptr;
	PFRAME_802_11 pFrame;
	PEID_STRUCT pEid;
	ULONG Length = 0;
	BOOLEAN brc;

	pFrame = (PFRAME_802_11) Msg;
	*RegClass = 0;
	Ptr = pFrame->Octet;
	Length += LENGTH_802_11;

	/* get timestamp from payload and advance the pointer */
	Ptr += TIMESTAMP_LEN;
	Length += TIMESTAMP_LEN;

	/* get beacon interval from payload and advance the pointer */
	Ptr += 2;
	Length += 2;

	/* get capability info from payload and advance the pointer */
	Ptr += 2;
	Length += 2;

	pEid = (PEID_STRUCT) Ptr;
	brc = FALSE;

	RTMPZeroMemory(BssScan, sizeof(OVERLAP_BSS_SCAN_IE));
	/* get variable fields from payload and advance the pointer */
	while ((Length + 2 + pEid->Len) <= MsgLen) {
		switch (pEid->Eid) {
		case IE_SUPP_REG_CLASS:
			if (pEid->Len > 0) {
				*RegClass = *pEid->Octet;
			} else {
				DBGPRINT(RT_DEBUG_TRACE,
					 ("PeerBeaconAndProbeRspSanity - wrong IE_SUPP_REG_CLASS (len=%d)\n",
					  pEid->Len));
			}
			break;
		case IE_OVERLAPBSS_SCAN_PARM:
			if (pEid->Len == sizeof(OVERLAP_BSS_SCAN_IE)) {
				brc = TRUE;
				RTMPMoveMemory(BssScan, pEid->Octet, sizeof(OVERLAP_BSS_SCAN_IE));
			} else {
				DBGPRINT(RT_DEBUG_TRACE,
					 ("PeerBeaconAndProbeRspSanity - wrong IE_OVERLAPBSS_SCAN_PARM (len=%d)\n",
					  pEid->Len));
			}
			break;

		case IE_EXT_CHANNEL_SWITCH_ANNOUNCEMENT:

#ifdef CONFIG_DFS_SLAVE
			if (pEid->Len == 4 && MAC_ADDR_EQUAL(pAd->MlmeAux.Bssid, ie_list->Bssid)) {
				pAd->StaCfg.bExtChannelSwitchCountingDown = TRUE;
				pAd->CommonCfg.ExtChannelSwitchMode = pEid->Octet[0];
				pAd->CommonCfg.ExtNewOperatingClass = pEid->Octet[1];
				pAd->CommonCfg.ExtNewChannel = pEid->Octet[2];
				pAd->CommonCfg.ExtChannelSwitchCount = pEid->Octet[3];
				if (pAd->CommonCfg.ExtChannelSwitchCount > 0)
					--pAd->CommonCfg.ExtChannelSwitchCount;
				DBGPRINT(RT_DEBUG_ERROR,
					 ("%s, ECSA IE from current BSS[%02x:%02x:%02x:%02x:%02x:%02x]: "
					  "Mode %d, Op Class %d, New Chnl %d, Cnt %d\n",
					  __func__, ie_list->Bssid[0], ie_list->Bssid[1],
					  ie_list->Bssid[2], ie_list->Bssid[3], ie_list->Bssid[4],
					  ie_list->Bssid[5], pAd->CommonCfg.ExtChannelSwitchMode,
					  pAd->CommonCfg.ExtNewOperatingClass,
					  pAd->CommonCfg.ExtNewChannel,
					  pAd->CommonCfg.ExtChannelSwitchCount));
				DBGPRINT(RT_DEBUG_ERROR,
					 ("Trigger LinkDown due to receiving CSA (ChannelSwitchAnnouncement) from AP\n"));
				LinkDown(pAd, FALSE);
				DBGPRINT(RT_DEBUG_TRACE,
					("%s - IE_EXT_CHANNEL_SWITCH_ANNOUNCEMENT\n", __func__));
			}
#endif /* endif */
			break;

		default:
			DBGPRINT(RT_DEBUG_INFO,
				("%s - Unsupported pEid->Eid Type = %d\n", __func__, pEid->Eid));
			break;
		}

		Length = Length + 2 + pEid->Len;	/* Eid[1] + Len[1]+ content[Len]      */
		pEid = (PEID_STRUCT) ((UCHAR *) pEid + 2 + pEid->Len);
	}

	return brc;

}

#if defined(AP_SCAN_SUPPORT) || defined(CONFIG_STA_SUPPORT)
/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
 */
BOOLEAN MlmeScanReqSanity(IN PRTMP_ADAPTER pAd,
			IN VOID * Msg,
			IN ULONG MsgLen,
			OUT UCHAR *pBssType,
			OUT CHAR Ssid[], OUT UCHAR *pSsidLen, OUT UCHAR *pScanType)
{
	MLME_SCAN_REQ_STRUCT *Info;

	Info = (MLME_SCAN_REQ_STRUCT *) (Msg);
	*pBssType = Info->BssType;
	*pSsidLen = Info->SsidLen;
	NdisMoveMemory(Ssid, Info->Ssid, *pSsidLen);
	*pScanType = Info->ScanType;

	if ((*pBssType == BSS_INFRA || *pBssType == BSS_ADHOC || *pBssType == BSS_ANY)
	    && (SCAN_MODE_VALID(*pScanType))
	    )
		return TRUE;

	DBGPRINT(RT_DEBUG_TRACE, ("MlmeScanReqSanity fail - wrong BssType or ScanType\n"));
	return FALSE;
}
#endif /* endif */

/* IRQL = DISPATCH_LEVEL*/
UCHAR ChannelSanity(IN PRTMP_ADAPTER pAd, IN UCHAR channel)
{
	int i;

	for (i = 0; i < pAd->ChannelListNum; i++) {
		if (channel == pAd->ChannelList[i].Channel)
			return 1;
	}
	return 0;
}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN PeerDeauthSanity(IN PRTMP_ADAPTER pAd,
			IN VOID * Msg,
			IN ULONG MsgLen,
			OUT PUCHAR pAddr1,
			OUT PUCHAR pAddr2, OUT PUCHAR pAddr3, OUT USHORT *pReason)
{
	PFRAME_802_11 pFrame = (PFRAME_802_11) Msg;

	COPY_MAC_ADDR(pAddr1, pFrame->Hdr.Addr1);
	COPY_MAC_ADDR(pAddr2, pFrame->Hdr.Addr2);
	COPY_MAC_ADDR(pAddr3, pFrame->Hdr.Addr3);
	NdisMoveMemory(pReason, &pFrame->Octet[0], 2);

	return TRUE;
}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN PeerAuthSanity(IN PRTMP_ADAPTER pAd,
			IN VOID * Msg,
			IN ULONG MsgLen,
			OUT PUCHAR pAddr,
			OUT USHORT *pAlg, OUT USHORT *pSeq, OUT USHORT *pStatus, CHAR *pChlgText)
{
	PFRAME_802_11 pFrame = (PFRAME_802_11) Msg;

	COPY_MAC_ADDR(pAddr, pFrame->Hdr.Addr2);
	NdisMoveMemory(pAlg, &pFrame->Octet[0], 2);
	NdisMoveMemory(pSeq, &pFrame->Octet[2], 2);
	NdisMoveMemory(pStatus, &pFrame->Octet[4], 2);

	if (*pAlg == AUTH_MODE_OPEN) {
		if (*pSeq == 1 || *pSeq == 2)
			return TRUE;

		DBGPRINT(RT_DEBUG_TRACE, ("PeerAuthSanity fail - wrong Seg#\n"));
		return FALSE;

	}

	if (*pAlg == AUTH_MODE_KEY) {
		if (*pSeq == 1 || *pSeq == 4)
			return TRUE;
		if (*pSeq == 2 || *pSeq == 3) {
			NdisMoveMemory(pChlgText, &pFrame->Octet[8], CIPHER_TEXT_LEN);
			return TRUE;
		}
		DBGPRINT(RT_DEBUG_TRACE, ("PeerAuthSanity fail - wrong Seg#\n"));
		return FALSE;

	}

	DBGPRINT(RT_DEBUG_TRACE, ("PeerAuthSanity fail - wrong algorithm\n"));
	return FALSE;
}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
 */
BOOLEAN MlmeAuthReqSanity(IN PRTMP_ADAPTER pAd,
			  IN VOID * Msg,
			  IN ULONG MsgLen,
			  OUT PUCHAR pAddr, OUT ULONG *pTimeout, OUT USHORT *pAlg)
{
	MLME_AUTH_REQ_STRUCT *pInfo;

	pInfo = (MLME_AUTH_REQ_STRUCT *) Msg;
	COPY_MAC_ADDR(pAddr, pInfo->Addr);
	*pTimeout = pInfo->Timeout;
	*pAlg = pInfo->Alg;

	if (((*pAlg == AUTH_MODE_KEY) || (*pAlg == AUTH_MODE_OPEN)
	    ) && ((*pAddr & 0x01) == 0)) {
#ifdef CONFIG_STA_SUPPORT
#ifdef WSC_INCLUDED
		if (pAd->StaCfg.WscControl.bWscTrigger
			&& (pAd->StaCfg.WscControl.WscConfMode != WSC_DISABLE))
			*pAlg = AUTH_MODE_OPEN;
#endif /* WSC_INCLUDED */
#endif /* CONFIG_STA_SUPPORT */
		return TRUE;
	}
	DBGPRINT(RT_DEBUG_TRACE, ("MlmeAuthReqSanity fail - wrong algorithm\n"));
	return FALSE;

}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN MlmeAssocReqSanity(IN PRTMP_ADAPTER pAd,
			   IN VOID * Msg,
			   IN ULONG MsgLen,
			   OUT PUCHAR pApAddr,
			   OUT USHORT *pCapabilityInfo,
			   OUT ULONG *pTimeout, OUT USHORT *pListenIntv)
{
	MLME_ASSOC_REQ_STRUCT *pInfo;

	pInfo = (MLME_ASSOC_REQ_STRUCT *) Msg;
	*pTimeout = pInfo->Timeout;	/* timeout */
	COPY_MAC_ADDR(pApAddr, pInfo->Addr);	/* AP address */
	*pCapabilityInfo = pInfo->CapabilityInfo;	/* capability info */
	*pListenIntv = pInfo->ListenIntv;

	return TRUE;
}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN PeerDisassocSanity(IN PRTMP_ADAPTER pAd,
			   IN VOID * Msg, IN ULONG MsgLen, OUT PUCHAR pAddr2, OUT USHORT *pReason)
{
	PFRAME_802_11 pFrame = (PFRAME_802_11) Msg;

	COPY_MAC_ADDR(pAddr2, pFrame->Hdr.Addr2);
	NdisMoveMemory(pReason, &pFrame->Octet[0], 2);

	return TRUE;
}

/*
	========================================================================
	Routine Description:
		Sanity check NetworkType (11b, 11g or 11a)

	Arguments:
		pBss - Pointer to BSS table.

	Return Value:
	Ndis802_11DS .......(11b)
	Ndis802_11OFDM24....(11g)
	Ndis802_11OFDM5.....(11a)

	IRQL = DISPATCH_LEVEL

	========================================================================
*/
NDIS_802_11_NETWORK_TYPE NetworkTypeInUseSanity(BSS_ENTRY *pBss)
{
	NDIS_802_11_NETWORK_TYPE NetWorkType;
	UCHAR rate, i;

	NetWorkType = Ndis802_11DS;

	if (pBss->Channel <= 14) {

		/* First check support Rate. */
		for (i = 0; i < pBss->SupRateLen; i++) {
			rate = pBss->SupRate[i] & 0x7f;	/* Mask out basic rate set bit */
			if ((rate == 2) || (rate == 4) || (rate == 11) || (rate == 22)) {
				continue;
			} else {

				/* Otherwise (even rate > 108) means Ndis802_11OFDM24 */
				NetWorkType = Ndis802_11OFDM24;
				break;
			}
		}

		/* Second check Extend Rate. */
		if (NetWorkType != Ndis802_11OFDM24) {
			for (i = 0; i < pBss->ExtRateLen; i++) {
				rate = pBss->SupRate[i] & 0x7f;	/* Mask out basic rate set bit */
				if ((rate == 2) || (rate == 4) || (rate == 11) || (rate == 22)) {
					continue;
				} else {

					/* Otherwise (even rate > 108) means Ndis802_11OFDM24 */
					NetWorkType = Ndis802_11OFDM24;
					break;
				}
			}
		}
	} else {
		NetWorkType = Ndis802_11OFDM5;
	}

	if (pBss->HtCapabilityLen != 0) {
		if (NetWorkType == Ndis802_11OFDM5) {
#ifdef DOT11_VHT_AC
			if (pBss->vht_cap_len != 0)
				NetWorkType = Ndis802_11OFDM5_AC;
			else
#endif /* DOT11_VHT_AC */
				NetWorkType = Ndis802_11OFDM5_N;
		} else
			NetWorkType = Ndis802_11OFDM24_N;
	}

	return NetWorkType;
}

#ifdef CONFIG_STA_SUPPORT
#ifdef QOS_DLS_SUPPORT
BOOLEAN MlmeDlsReqSanity(IN PRTMP_ADAPTER pAd,
			IN VOID * Msg,
			IN ULONG MsgLen, OUT PRT_802_11_DLS * pDLS, OUT PUSHORT pReason)
{
	MLME_DLS_REQ_STRUCT *pInfo;

	pInfo = (MLME_DLS_REQ_STRUCT *) Msg;

	*pDLS = pInfo->pDLS;
	*pReason = pInfo->Reason;

	return TRUE;
}
#endif /* QOS_DLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

#ifdef QOS_DLS_SUPPORT
BOOLEAN PeerDlsReqSanity(IN PRTMP_ADAPTER pAd,
			IN VOID * Msg,
			IN ULONG MsgLen,
			OUT PUCHAR pDA,
			OUT PUCHAR pSA,
			OUT USHORT *pCapabilityInfo,
			OUT USHORT *pDlsTimeout,
			OUT UCHAR *pRatesLen,
			OUT UCHAR Rates[],
			OUT UCHAR *pHtCapabilityLen, OUT HT_CAPABILITY_IE * pHtCapability)
{
	CHAR *Ptr;
	PFRAME_802_11 Fr = (PFRAME_802_11) Msg;
	PEID_STRUCT eid_ptr;

	/* to prevent caller from using garbage output value */
	*pCapabilityInfo = 0;
	*pDlsTimeout = 0;
	*pHtCapabilityLen = 0;

	Ptr = (PCHAR) Fr->Octet;

	/* offset to destination MAC address (Category and Action field) */
	Ptr += 2;

	/* get DA from payload and advance the pointer */
	NdisMoveMemory(pDA, Ptr, MAC_ADDR_LEN);
	Ptr += MAC_ADDR_LEN;

	/* get SA from payload and advance the pointer */
	NdisMoveMemory(pSA, Ptr, MAC_ADDR_LEN);
	Ptr += MAC_ADDR_LEN;

	/* get capability info from payload and advance the pointer */
	NdisMoveMemory(pCapabilityInfo, Ptr, 2);
	Ptr += 2;

	/* get capability info from payload and advance the pointer */
	NdisMoveMemory(pDlsTimeout, Ptr, 2);
	Ptr += 2;

	/* Category and Action field + DA + SA + capability + Timeout */
	eid_ptr = (PEID_STRUCT) &Fr->Octet[18];

	while (((UCHAR *) eid_ptr + eid_ptr->Len + 1) < ((UCHAR *) Fr + MsgLen)) {
		switch (eid_ptr->Eid) {
		case IE_SUPP_RATES:
			if ((eid_ptr->Len <= MAX_LEN_OF_SUPPORTED_RATES) && (eid_ptr->Len > 0)) {
				NdisMoveMemory(Rates, eid_ptr->Octet, eid_ptr->Len);
				DBGPRINT(RT_DEBUG_TRACE,
					 ("PeerDlsReqSanity - IE_SUPP_RATES., Len=%d. Rates[0]=%x\n",
					  eid_ptr->Len, Rates[0]));
				DBGPRINT(RT_DEBUG_TRACE,
					 ("Rates[1]=%x %x %x %x %x %x %x\n", Rates[1], Rates[2],
					  Rates[3], Rates[4], Rates[5], Rates[6], Rates[7]));
				*pRatesLen = eid_ptr->Len;
			} else {
				*pRatesLen = 8;
				Rates[0] = 0x82;
				Rates[1] = 0x84;
				Rates[2] = 0x8b;
				Rates[3] = 0x96;
				Rates[4] = 0x12;
				Rates[5] = 0x24;
				Rates[6] = 0x48;
				Rates[7] = 0x6c;
				DBGPRINT(RT_DEBUG_TRACE,
					("PeerDlsReqSanity - wrong IE_SUPP_RATES., Len=%d\n",
					eid_ptr->Len));
			}
			break;

		case IE_EXT_SUPP_RATES:
			if (eid_ptr->Len + *pRatesLen <= MAX_LEN_OF_SUPPORTED_RATES) {
				NdisMoveMemory(&Rates[*pRatesLen], eid_ptr->Octet, eid_ptr->Len);
				*pRatesLen = (*pRatesLen) + eid_ptr->Len;
			} else {
				NdisMoveMemory(&Rates[*pRatesLen], eid_ptr->Octet,
					       MAX_LEN_OF_SUPPORTED_RATES - (*pRatesLen));
				*pRatesLen = MAX_LEN_OF_SUPPORTED_RATES;
			}
			break;

		case IE_HT_CAP:
			if (eid_ptr->Len >= sizeof(HT_CAPABILITY_IE)) {
				NdisMoveMemory(pHtCapability, eid_ptr->Octet,
					sizeof(HT_CAPABILITY_IE));

				*(USHORT *) (&pHtCapability->HtCapInfo) =
				    cpu2le16(*(USHORT *) (&pHtCapability->HtCapInfo));
#ifdef UNALIGNMENT_SUPPORT
				{
					EXT_HT_CAP_INFO extHtCapInfo;

					NdisMoveMemory((PUCHAR) (&extHtCapInfo),
						(PUCHAR) (&pHtCapability->ExtHtCapInfo),
						sizeof(EXT_HT_CAP_INFO));
					*(USHORT *) (&extHtCapInfo) =
						cpu2le16(*(USHORT *) (&extHtCapInfo));
					NdisMoveMemory((PUCHAR) (&pHtCapability->ExtHtCapInfo),
						(PUCHAR) (&extHtCapInfo),
						sizeof(EXT_HT_CAP_INFO));
				}
#else
				*(USHORT *) (&pHtCapability->ExtHtCapInfo) =
				    cpu2le16(*(USHORT *) (&pHtCapability->ExtHtCapInfo));
#endif /* UNALIGNMENT_SUPPORT */
				*pHtCapabilityLen = sizeof(HT_CAPABILITY_IE);

				DBGPRINT(RT_DEBUG_TRACE, ("PeerDlsReqSanity - IE_HT_CAP\n"));
			} else {
				DBGPRINT(RT_DEBUG_TRACE,
					("PeerDlsReqSanity - wrong IE_HT_CAP.eid_ptr->Len = %d\n",
					eid_ptr->Len));
			}
			break;

		default:
			break;
		}

		eid_ptr = (PEID_STRUCT) ((UCHAR *) eid_ptr + 2 + eid_ptr->Len);
	}

	return TRUE;
}

BOOLEAN PeerDlsRspSanity(IN PRTMP_ADAPTER pAd,
			IN VOID * Msg,
			IN ULONG MsgLen,
			OUT PUCHAR pDA,
			OUT PUCHAR pSA,
			OUT USHORT *pCapabilityInfo,
			OUT USHORT *pStatus,
			OUT UCHAR *pRatesLen,
			OUT UCHAR Rates[],
			OUT UCHAR *pHtCapabilityLen, OUT HT_CAPABILITY_IE * pHtCapability)
{
	CHAR *Ptr;
	PFRAME_802_11 Fr = (PFRAME_802_11) Msg;
	PEID_STRUCT eid_ptr;

	/* to prevent caller from using garbage output value */
	if (pStatus)
		*pStatus = 0;
	*pCapabilityInfo = 0;
	*pHtCapabilityLen = 0;

	Ptr = (PCHAR) Fr->Octet;

	/* offset to destination MAC address (Category and Action field) */
	Ptr += 2;

	/* get status code from payload and advance the pointer */
	if (pStatus)
		NdisMoveMemory(pStatus, Ptr, 2);
	Ptr += 2;

	/* get DA from payload and advance the pointer */
	NdisMoveMemory(pDA, Ptr, MAC_ADDR_LEN);
	Ptr += MAC_ADDR_LEN;

	/* get SA from payload and advance the pointer */
	NdisMoveMemory(pSA, Ptr, MAC_ADDR_LEN);
	Ptr += MAC_ADDR_LEN;

	if (pStatus == 0) {
		/* get capability info from payload and advance the pointer */
		NdisMoveMemory(pCapabilityInfo, Ptr, 2);
		Ptr += 2;
	}

	/* Category and Action field + status code + DA + SA + capability */
	eid_ptr = (PEID_STRUCT) &Fr->Octet[18];

	while (((UCHAR *) eid_ptr + eid_ptr->Len + 1) < ((UCHAR *) Fr + MsgLen)) {
		switch (eid_ptr->Eid) {
		case IE_SUPP_RATES:
			if ((eid_ptr->Len <= MAX_LEN_OF_SUPPORTED_RATES) && (eid_ptr->Len > 0)) {
				NdisMoveMemory(Rates, eid_ptr->Octet, eid_ptr->Len);
				DBGPRINT(RT_DEBUG_TRACE,
					 ("PeerDlsRspSanity - IE_SUPP_RATES., Len=%d. Rates[0]=%x\n",
					  eid_ptr->Len, Rates[0]));
				DBGPRINT(RT_DEBUG_TRACE,
					 ("Rates[1]=%x %x %x %x %x %x %x\n", Rates[1], Rates[2],
					  Rates[3], Rates[4], Rates[5], Rates[6], Rates[7]));
				*pRatesLen = eid_ptr->Len;
			} else {
				*pRatesLen = 8;
				Rates[0] = 0x82;
				Rates[1] = 0x84;
				Rates[2] = 0x8b;
				Rates[3] = 0x96;
				Rates[4] = 0x12;
				Rates[5] = 0x24;
				Rates[6] = 0x48;
				Rates[7] = 0x6c;
				DBGPRINT(RT_DEBUG_TRACE,
					("PeerDlsRspSanity - wrong IE_SUPP_RATES., Len=%d\n",
					eid_ptr->Len));
			}
			break;

		case IE_EXT_SUPP_RATES:
			if (eid_ptr->Len + *pRatesLen <= MAX_LEN_OF_SUPPORTED_RATES) {
				NdisMoveMemory(&Rates[*pRatesLen], eid_ptr->Octet, eid_ptr->Len);
				*pRatesLen = (*pRatesLen) + eid_ptr->Len;
			} else {
				NdisMoveMemory(&Rates[*pRatesLen], eid_ptr->Octet,
					       MAX_LEN_OF_SUPPORTED_RATES - (*pRatesLen));
				*pRatesLen = MAX_LEN_OF_SUPPORTED_RATES;
			}
			break;

		case IE_HT_CAP:
			if (eid_ptr->Len >= sizeof(HT_CAPABILITY_IE)) {
				NdisMoveMemory(pHtCapability, eid_ptr->Octet,
					sizeof(HT_CAPABILITY_IE));

				*(USHORT *) (&pHtCapability->HtCapInfo) =
				    cpu2le16(*(USHORT *) (&pHtCapability->HtCapInfo));
#ifdef UNALIGNMENT_SUPPORT
				{
					EXT_HT_CAP_INFO extHtCapInfo;

					NdisMoveMemory((PUCHAR) (&extHtCapInfo),
						(PUCHAR) (&pHtCapability->ExtHtCapInfo),
						sizeof(EXT_HT_CAP_INFO));
					*(USHORT *) (&extHtCapInfo) =
						cpu2le16(*(USHORT *) (&extHtCapInfo));
					NdisMoveMemory((PUCHAR) (&pHtCapability->ExtHtCapInfo),
						(PUCHAR) (&extHtCapInfo),
						sizeof(EXT_HT_CAP_INFO));
				}
#else
				*(USHORT *) (&pHtCapability->ExtHtCapInfo) =
				    cpu2le16(*(USHORT *) (&pHtCapability->ExtHtCapInfo));
#endif /* UNALIGNMENT_SUPPORT */
				*pHtCapabilityLen = sizeof(HT_CAPABILITY_IE);

				DBGPRINT(RT_DEBUG_TRACE, ("PeerDlsRspSanity - IE_HT_CAP\n"));
			} else {
				DBGPRINT(RT_DEBUG_TRACE,
					("PeerDlsRspSanity - wrong IE_HT_CAP.eid_ptr->Len = %d\n",
					eid_ptr->Len));
			}
			break;

		default:
			break;
		}

		eid_ptr = (PEID_STRUCT) ((UCHAR *) eid_ptr + 2 + eid_ptr->Len);
	}

	return TRUE;
}

BOOLEAN PeerDlsTearDownSanity(IN PRTMP_ADAPTER pAd,
				IN VOID * Msg,
				IN ULONG MsgLen, OUT PUCHAR pDA,
				OUT PUCHAR pSA, OUT USHORT *pReason)
{
	CHAR *Ptr;
	PFRAME_802_11 Fr = (PFRAME_802_11) Msg;

	/* to prevent caller from using garbage output value */
	*pReason = 0;

	Ptr = (PCHAR) Fr->Octet;

	/* offset to destination MAC address (Category and Action field) */
	Ptr += 2;

	/* get DA from payload and advance the pointer */
	NdisMoveMemory(pDA, Ptr, MAC_ADDR_LEN);
	Ptr += MAC_ADDR_LEN;

	/* get SA from payload and advance the pointer */
	NdisMoveMemory(pSA, Ptr, MAC_ADDR_LEN);
	Ptr += MAC_ADDR_LEN;

	/* get reason code from payload and advance the pointer */
	NdisMoveMemory(pReason, Ptr, 2);
	Ptr += 2;

	return TRUE;
}
#endif /* QOS_DLS_SUPPORT */

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
 */
BOOLEAN PeerProbeReqSanity(IN PRTMP_ADAPTER pAd,
			   IN VOID * Msg, IN ULONG MsgLen, OUT PEER_PROBE_REQ_PARAM * ProbeReqParam)
{
	PFRAME_802_11 Fr = (PFRAME_802_11) Msg;
	UCHAR *Ptr;
	UCHAR eid = 0, eid_len = 0, *eid_data;
#ifdef CONFIG_AP_SUPPORT
	UCHAR apidx = MAIN_MBSSID;
	UCHAR Addr1[MAC_ADDR_LEN];
#ifdef WSC_INCLUDED
	UCHAR *pPeerWscIe = NULL;
	UINT PeerWscIeLen = 0;
	BOOLEAN bWscCheck = TRUE;
#endif /* WSC_INCLUDED */
#endif /* CONFIG_AP_SUPPORT */
	UINT total_ie_len = 0;

	NdisZeroMemory(ProbeReqParam, sizeof(*ProbeReqParam));

	/* to prevent caller from using garbage output value */
#ifdef CONFIG_AP_SUPPORT
	apidx = apidx;		/* avoid compile warning */
#endif /* CONFIG_AP_SUPPORT */

	COPY_MAC_ADDR(ProbeReqParam->Addr2, &Fr->Hdr.Addr2);

	if (Fr->Octet[0] != IE_SSID || Fr->Octet[1] > MAX_LEN_OF_SSID) {
		DBGPRINT(RT_DEBUG_TRACE, ("%s(): sanity fail - wrong SSID IE\n", __func__));
		return FALSE;
	}

	ProbeReqParam->SsidLen = Fr->Octet[1];
	NdisMoveMemory(ProbeReqParam->Ssid, &Fr->Octet[2], ProbeReqParam->SsidLen);

#ifdef CONFIG_AP_SUPPORT
	COPY_MAC_ADDR(Addr1, &Fr->Hdr.Addr1);
#ifdef WSC_AP_SUPPORT
	os_alloc_mem(NULL, &pPeerWscIe, 512);
#endif /* WSC_AP_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

	Ptr = Fr->Octet;
	eid = Ptr[0];
	eid_len = Ptr[1];
	total_ie_len = eid_len + 2;
	eid_data = Ptr + 2;

	/* get variable fields from payload and advance the pointer */
	while ((eid_data + eid_len) <= ((UCHAR *) Fr + MsgLen)) {
		switch (eid) {
		case IE_VENDOR_SPECIFIC:
			if (eid_len <= 4)
				break;
#ifdef RSSI_FEEDBACK
			if (ProbeReqParam->bRssiRequested &&
				NdisEqualMemory(eid_data, RALINK_OUI, 3)
				&& (eid_len == 7)) {
				if (*(eid_data + 3 /* skip RALINK_OUI */) & 0x8)
					ProbeReqParam->bRssiRequested = TRUE;
				break;
			}
#endif /* RSSI_FEEDBACK */

			if (NdisEqualMemory(eid_data, WPS_OUI, 4)
#ifdef IWSC_SUPPORT
			    || NdisEqualMemory(eid_data, IWSC_OUI, 4)
#endif /* IWSC_SUPPORT // */
			    ) {
#ifdef CONFIG_AP_SUPPORT
#endif /* CONFIG_AP_SUPPORT */

#ifdef WSC_INCLUDED

#ifdef IWSC_SUPPORT
#ifdef CONFIG_STA_SUPPORT
				if (pAd->StaCfg.BssType == BSS_ADHOC) {
					if (NdisEqualMemory(eid_data, IWSC_OUI, 4))
						WscCheckPeerDPID(pAd, Fr, eid_data, eid_len);
				} else if (NdisEqualMemory(eid_data, WPS_OUI, 4))
#endif /* CONFIG_STA_SUPPORT */
#endif /* IWSC_SUPPORT */
					WscCheckPeerDPID(pAd, Fr, eid_data, eid_len);

#ifdef CONFIG_AP_SUPPORT
				if (pPeerWscIe) {
					/* Ignore old WPS IE fragments, if we get the version 0x10 */
					if (*(eid_data + 4) == 0x10) {	/* First WPS IE will have version 0x10 */
						NdisMoveMemory(pPeerWscIe, eid_data + 4,
							eid_len - 4);
						PeerWscIeLen = (eid_len - 4);
					} else {
						/* reassembly remanning, other
						*  IE fragmentations will not
						*  have version 0x10
						*/

						if ((PeerWscIeLen + (eid_len - 4)) <= 512) {
							NdisMoveMemory(pPeerWscIe + PeerWscIeLen,
								       eid_data + 4, eid_len - 4);
							PeerWscIeLen += (eid_len - 4);
						} else {	/* ((PeerWscIeLen +(eid_len-4)) > 512) */

							bWscCheck = FALSE;
							DBGPRINT(RT_DEBUG_ERROR,
								 ("%s: Error!!! Sum of All PeerWscIeLen = %d (> 512)\n",
								  __func__,
								  (PeerWscIeLen + (eid_len - 4))));
						}
					}
				} else {
					bWscCheck = FALSE;
					DBGPRINT(RT_DEBUG_ERROR,
						("%s: Error!!! pPeerWscIe is empty!\n", __func__));
				}
#endif /* CONFIG_AP_SUPPORT */
#endif /* WSC_INCLUDED */
			}
			break;
#ifdef CONFIG_HOTSPOT
		case IE_INTERWORKING:
			ProbeReqParam->AccessNetWorkType = (*eid_data) & 0x0F;

			if (eid_len > 3) {
				if (eid_len == 7)
					NdisMoveMemory(ProbeReqParam->Hessid, eid_data + 1,
						MAC_ADDR_LEN);
				else
					NdisMoveMemory(ProbeReqParam->Hessid, eid_data + 3,
						MAC_ADDR_LEN);

				ProbeReqParam->IsHessid = TRUE;
			}

			ProbeReqParam->IsIWIE = TRUE;
			break;
#endif /* endif */
		case IE_EXT_CAPABILITY:
#ifdef CONFIG_HOTSPOT
			if (eid_len >= 4) {
				if (((*(eid_data + 3)) & 0x80) == 0x80)
					ProbeReqParam->IsIWCapability = TRUE;
			}
#endif /* endif */
			break;
		default:
			break;
		}
		eid = Ptr[total_ie_len];
		eid_len = Ptr[total_ie_len + 1];
		eid_data = Ptr + total_ie_len + 2;
		total_ie_len += (eid_len + 2);
	}

#ifdef CONFIG_AP_SUPPORT
#ifdef WSC_INCLUDED
	if (pPeerWscIe && (PeerWscIeLen > 0) && (bWscCheck == TRUE)) {
		for (apidx = 0; apidx < pAd->ApCfg.BssidNum; apidx++) {
			if (NdisEqualMemory
				(Addr1, pAd->ApCfg.MBSSID[apidx].wdev.bssid, MAC_ADDR_LEN))
				break;
		}

		/*
		   Due to Addr1 in Probe Request may be FF:FF:FF:FF:FF:FF
		   and we need to send out this information to external registrar.
		   Therefore we choose ra0 to send this probe req when we couldn't find apidx by Addr1.
		 */
		if (apidx >= pAd->ApCfg.BssidNum)
			apidx = MAIN_MBSSID;


		if ((pAd->ApCfg.MBSSID[apidx].WscControl.WscConfMode & WSC_PROXY) != WSC_DISABLE) {
			int bufLen = 0;
			PUCHAR pBuf = NULL;
			WSC_IE_PROBREQ_DATA *pprobreq = NULL;

			/*
			   PeerWscIeLen: Len of WSC IE without WSC OUI
			 */
			bufLen = sizeof(WSC_IE_PROBREQ_DATA) + PeerWscIeLen;
			os_alloc_mem(NULL, &pBuf, bufLen);
			if (pBuf) {
				/*Send WSC probe req to UPnP */
				NdisZeroMemory(pBuf, bufLen);
				pprobreq = (WSC_IE_PROBREQ_DATA *) pBuf;
				/*Well, I think that it must be TRUE! */
				if (32 >= ProbeReqParam->SsidLen) {
					/* SSID */
					NdisMoveMemory(pprobreq->ssid, ProbeReqParam->Ssid,
						ProbeReqParam->SsidLen);
					/* Mac address */
					NdisMoveMemory(pprobreq->macAddr, Fr->Hdr.Addr2, 6);
					pprobreq->data[0] = PeerWscIeLen >> 8;	/* element ID */
					/* element Length */
					pprobreq->data[1] = PeerWscIeLen & 0xff;
					/* (WscProbeReqData) */
					NdisMoveMemory((pBuf + sizeof(WSC_IE_PROBREQ_DATA)),
						pPeerWscIe, PeerWscIeLen);
					WscSendUPnPMessage(pAd, apidx,
							WSC_OPCODE_UPNP_MGMT,
							WSC_UPNP_MGMT_SUB_PROBE_REQ, pBuf,
							bufLen, 0, 0, &Fr->Hdr.Addr2[0],
							AP_MODE);
				}
				os_free_mem(NULL, pBuf);
			}
		}
	}
	if (pPeerWscIe)
		os_free_mem(NULL, pPeerWscIe);
#endif /* WSC_INCLUDED */
#endif /* CONFIG_AP_SUPPORT */

	return TRUE;
}
