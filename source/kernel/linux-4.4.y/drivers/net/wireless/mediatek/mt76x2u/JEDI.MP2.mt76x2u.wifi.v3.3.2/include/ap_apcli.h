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


#ifndef _AP_APCLI_H_
#define _AP_APCLI_H_

#ifdef APCLI_SUPPORT

#include "rtmp.h"
/*little retry interval for peer p2p GO PS-NOA IOT issue */
#define APCLI_AUTH_LITTLE_TIMEOUT	40	/* unit: msec */
#define APCLI_ASSOC_LITTLE_TIMEOUT	40	/* unit: msec */
#define APCLI_PROBE_LITTLE_TIMEOUT	40	/* unit: msec */

#define APCLI_AUTH_TIMEOUT	340	/* unit: msec */
#define APCLI_ASSOC_TIMEOUT	340	/* unit: msec */
#define APCLI_PROBE_TIMEOUT	1040	/* unit: msec */
#ifdef APCLI_CONNECTION_TRIAL
#define TRIAL_TIMEOUT	400	/* unit: msec */
#endif /* APCLI_CONNECTION_TRIAL */

#define APCLI_ROOT_BSSID_GET(pAd, wcid) ((pAd)->MacTab.Content[(wcid)].Addr)

/* sanity check for apidx */
#define APCLI_MR_APIDX_SANITY_CHECK(idx) \
{ \
	if ((idx) >= MAX_APCLI_NUM) { \
		(idx) = 0; \
		DBGPRINT(RT_DEBUG_ERROR, ("%s> Error! apcli-idx > MAX_APCLI_NUM!\n", __func__)); \
	} \
}

typedef struct _APCLI_MLME_JOIN_REQ_STRUCT {
	UCHAR Bssid[MAC_ADDR_LEN];
	UCHAR SsidLen;
	UCHAR Ssid[MAX_LEN_OF_SSID];
} APCLI_MLME_JOIN_REQ_STRUCT;

typedef struct _APCLI_CTRL_MSG_STRUCT {
	USHORT Status;
	UCHAR SrcAddr[MAC_ADDR_LEN];
#ifdef MAC_REPEATER_SUPPORT
	UCHAR BssIdx;
	UCHAR CliIdx;
#endif				/* MAC_REPEATER_SUPPORT */
} APCLI_CTRL_MSG_STRUCT, *PSTA_CTRL_MSG_STRUCT;

BOOLEAN isValidApCliIf(SHORT ifIndex);

VOID ApCliCtrlStateMachineInit(IN PRTMP_ADAPTER pAd,
			       IN STATE_MACHINE * Sm, OUT STATE_MACHINE_FUNC Trans[]);

VOID ApCliSyncStateMachineInit(IN PRTMP_ADAPTER pAd,
			       IN STATE_MACHINE * Sm, OUT STATE_MACHINE_FUNC Trans[]);

VOID ApCliAuthStateMachineInit(IN PRTMP_ADAPTER pAd,
			       IN STATE_MACHINE * Sm, OUT STATE_MACHINE_FUNC Trans[]);
VOID ApCliMlmeDeauthReqAction(IN PRTMP_ADAPTER pAd, IN PMLME_QUEUE_ELEM Elem);
VOID ApCliAssocStateMachineInit(IN PRTMP_ADAPTER pAd,
				IN STATE_MACHINE * Sm, OUT STATE_MACHINE_FUNC Trans[]);

MAC_TABLE_ENTRY *ApCliTableLookUpByWcid(IN RTMP_ADAPTER * pAd, IN UCHAR wcid, IN UCHAR *pAddrs);

INT ApCliAllowToSendPacket(IN RTMP_ADAPTER * pAd,
			   IN struct wifi_dev *wdev, IN PNDIS_PACKET pPacket, OUT UCHAR *pWcid);

BOOLEAN ApCliValidateRSNIE(IN RTMP_ADAPTER * pAd,
			   IN PEID_STRUCT pEid_ptr, IN USHORT eid_len, IN USHORT idx);

VOID ApCli_Remove(IN PRTMP_ADAPTER pAd);

VOID RT28xx_ApCli_Close(IN PRTMP_ADAPTER pAd);

INT ApCliIfLookUp(IN PRTMP_ADAPTER pAd, IN PUCHAR pAddr);


VOID ApCliMgtMacHeaderInit(IN PRTMP_ADAPTER pAd,
			   IN OUT PHEADER_802_11 pHdr80211,
			   IN UCHAR SubType,
			   IN UCHAR ToDs, IN PUCHAR pDA, IN PUCHAR pBssid, IN USHORT ifIndex);

BOOLEAN ApCliCheckHt(IN PRTMP_ADAPTER pAd,
		     IN USHORT IfIndex,
		     IN OUT HT_CAPABILITY_IE * pHtCapability, IN OUT ADD_HT_INFO_IE * pAddHtInfo);

#ifdef DOT11_VHT_AC
BOOLEAN ApCliCheckVht(IN PRTMP_ADAPTER pAd,
		      IN UCHAR Wcid,
		      IN MAC_TABLE_ENTRY *pEntry, IN VHT_CAP_IE * vht_cap, IN VHT_OP_IE * vht_op);
#endif /* DOT11_VHT_AC */

BOOLEAN ApCliLinkUp(IN PRTMP_ADAPTER pAd, IN UCHAR ifIndex);

VOID ApCliLinkDown(IN PRTMP_ADAPTER pAd, IN UCHAR ifIndex);

VOID ApCliIfUp(IN PRTMP_ADAPTER pAd);

VOID ApCliIfDown(IN PRTMP_ADAPTER pAd);

VOID ApCliIfMonitor(IN PRTMP_ADAPTER pAd);

BOOLEAN ApCliMsgTypeSubst(IN PRTMP_ADAPTER pAd,
			  IN PFRAME_802_11 pFrame, OUT INT *Machine, OUT INT *MsgType);

BOOLEAN preCheckMsgTypeSubset(IN PRTMP_ADAPTER pAd,
			      IN PFRAME_802_11 pFrame, OUT INT *Machine, OUT INT *MsgType);

BOOLEAN ApCliPeerAssocRspSanity(IN PRTMP_ADAPTER pAd, IN VOID * pMsg, IN ULONG MsgLen,
				OUT PUCHAR pAddr2, OUT USHORT *pCapabilityInfo, OUT USHORT *pStatus,
				OUT USHORT *pAid,
				OUT UCHAR SupRate[], OUT UCHAR *pSupRateLen, OUT UCHAR ExtRate[],
				OUT UCHAR *pExtRateLen,
				OUT HT_CAPABILITY_IE * pHtCapability,
			OUT ADD_HT_INFO_IE *pAddHtInfo,/* AP might use this additional ht info IE */
				OUT UCHAR *pHtCapabilityLen,
				OUT UCHAR *pAddHtInfoLen,
				OUT UCHAR *pNewExtChannelOffset,
				OUT PEDCA_PARM pEdcaParm,
				OUT UCHAR *pCkipFlag, OUT IE_LISTS * ie_list);

VOID ApCliPeerPairMsg1Action(IN PRTMP_ADAPTER pAd,
			     IN MAC_TABLE_ENTRY *pEntry, IN MLME_QUEUE_ELEM * Elem);

VOID ApCliPeerPairMsg3Action(IN PRTMP_ADAPTER pAd,
			     IN MAC_TABLE_ENTRY *pEntry, IN MLME_QUEUE_ELEM * Elem);

VOID ApCliPeerGroupMsg1Action(IN PRTMP_ADAPTER pAd,
			      IN MAC_TABLE_ENTRY *pEntry, IN MLME_QUEUE_ELEM * Elem);

BOOLEAN ApCliCheckRSNIE(IN PRTMP_ADAPTER pAd,
			IN PUCHAR pData,
			IN UCHAR DataLen, IN MAC_TABLE_ENTRY *pEntry, OUT UCHAR *Offset);

BOOLEAN ApCliParseKeyData(IN PRTMP_ADAPTER pAd,
			  IN PUCHAR pKeyData,
			  IN UCHAR KeyDataLen,
			  IN MAC_TABLE_ENTRY *pEntry, IN UCHAR IfIdx, IN UCHAR bPairewise);

BOOLEAN ApCliHandleRxBroadcastFrame(IN PRTMP_ADAPTER pAd,
				    IN RX_BLK * pRxBlk,
				    IN MAC_TABLE_ENTRY *pEntry, IN UCHAR FromWhichBSSID);

VOID APCliInstallPairwiseKey(IN PRTMP_ADAPTER pAd, IN MAC_TABLE_ENTRY *pEntry);

BOOLEAN APCliInstallSharedKey(IN PRTMP_ADAPTER pAd,
			      IN PUCHAR pKey,
			      IN UCHAR KeyLen, IN UCHAR DefaultKeyIdx, IN MAC_TABLE_ENTRY *pEntry);

VOID ApCliUpdateMlmeRate(RTMP_ADAPTER *pAd, USHORT ifIndex);

VOID APCli_Init(IN RTMP_ADAPTER *pAd, IN RTMP_OS_NETDEV_OP_HOOK * pNetDevOps);

BOOLEAN ApCli_Open(RTMP_ADAPTER *pAd, PNET_DEV dev_p);
BOOLEAN ApCli_Close(RTMP_ADAPTER *pAd, PNET_DEV dev_p);

BOOLEAN ApCliWaitProbRsp(RTMP_ADAPTER *pAd, USHORT ifIndex);
VOID ApCliSimulateRecvBeacon(RTMP_ADAPTER *pAd);

#ifdef APCLI_AUTO_CONNECT_SUPPORT
extern INT Set_ApCli_Enable_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

extern INT Set_ApCli_Bssid_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

BOOLEAN ApCliAutoConnectExec(IN PRTMP_ADAPTER pAd);

BOOLEAN ApcliCompareAuthEncryp(IN PAPCLI_STRUCT pApCliEntry,
			       IN NDIS_802_11_AUTHENTICATION_MODE AuthMode,
			       IN NDIS_802_11_AUTHENTICATION_MODE AuthModeAux,
			       IN NDIS_802_11_WEP_STATUS WEPstatus, IN CIPHER_SUITE WPA);

VOID ApCliSwitchCandidateAP(IN PRTMP_ADAPTER pAd);

VOID RTMPApCliReconnectionCheck(IN PRTMP_ADAPTER pAd);

#endif /* APCLI_AUTO_CONNECT_SUPPORT */

#endif /* APCLI_SUPPORT */
#endif /* _AP_APCLI_H_ */
