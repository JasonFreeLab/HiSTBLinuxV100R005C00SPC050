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

***************************************************************************/

#ifndef __WNM_H__
#define __WNM_H__

#include "ipv6.h"

#define BTM_MACHINE_BASE 0
#define WaitPeerBTMRspTimeoutVale 1024

/* BTM states */
enum BTM_STATE {
	WAIT_BTM_QUERY,
	WAIT_PEER_BTM_QUERY,
	WAIT_BTM_REQ,
	WAIT_BTM_RSP,
	WAIT_PEER_BTM_REQ,
	WAIT_PEER_BTM_RSP,
	BTM_UNKNOWN,
	MAX_BTM_STATE,
};

/* BTM events */
enum BTM_EVENT {
	BTM_QUERY,
	PEER_BTM_QUERY,
	BTM_REQ,
	BTM_RSP,
	PEER_BTM_REQ,
	PEER_BTM_RSP,
	MAX_BTM_MSG,
};

#define BTM_FUNC_SIZE (MAX_BTM_STATE * MAX_BTM_MSG)

enum IPV6_TYPE {
	IPV6_LINK_LOCAL,
	IPV6_GLOBAL,
};

typedef struct GNU_PACKED _BTM_EVENT_DATA {
	UCHAR ControlIndex;
	UCHAR PeerMACAddr[MAC_ADDR_LEN];
	UINT16 EventType;
	union {
#ifdef CONFIG_STA_SUPPORT
		struct {
			UCHAR DialogToken;
			UINT16 BTMQueryLen;
			UCHAR BTMQuery[0];
		} GNU_PACKED BTM_QUERY_DATA;

		struct {
			UCHAR DialogToken;
			UINT16 BTMRspLen;
			UCHAR BTMRsp[0];
		} GNU_PACKED BTM_RSP_DATA;

		struct {
			UCHAR DialogToken;
			UINT16 BTMReqLen;
			UCHAR BTMReq[0];
		} GNU_PACKED PEER_BTM_REQ_DATA;
#endif				/* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
		struct {
			UCHAR DialogToken;
			UINT16 BTMReqLen;
			UCHAR BTMReq[0];
		} GNU_PACKED BTM_REQ_DATA;

		struct {
			UCHAR DialogToken;
			UINT16 BTMQueryLen;
			UCHAR BTMQuery[0];
		} GNU_PACKED PEER_BTM_QUERY_DATA;

		struct {
			UCHAR DialogToken;
			UINT16 BTMRspLen;
			UCHAR BTMRsp[0];
		} GNU_PACKED PEER_BTM_RSP_DATA;
#endif				/* CONFIG_AP_SUPPORT */
	} u;
} BTM_EVENT_DATA, *PBTM_EVENT_DATA;

typedef struct _BTM_PEER_ENTRY {
	DL_LIST List;
	enum BTM_STATE CurrentState;
	UCHAR ControlIndex;
	UCHAR PeerMACAddr[MAC_ADDR_LEN];
	UCHAR DialogToken;
	void *Priv;
#ifdef CONFIG_AP_SUPPORT
	RALINK_TIMER_STRUCT WaitPeerBTMRspTimer;
#endif				/* CONFIG_AP_SUPPORT */
} BTM_PEER_ENTRY, *PBTM_PEER_ENTRY;

typedef struct _PROXY_ARP_IPV4_ENTRY {
	DL_LIST List;
	UCHAR TargetMACAddr[MAC_ADDR_LEN];
	UCHAR TargetIPAddr[4];
} PROXY_ARP_IPV4_ENTRY, *PPROXY_ARP_IPV4_ENTRY;

typedef struct _PROXY_ARP_IPV4_UNIT {
	UCHAR TargetMACAddr[MAC_ADDR_LEN];
	UCHAR TargetIPAddr[4];
} PROXY_ARP_IPV4_UNIT, *PPROXY_ARP_IPV4_UNIT;

typedef struct _PROXY_ARP_IPV6_ENTRY {
	DL_LIST List;
	UCHAR TargetMACAddr[MAC_ADDR_LEN];
	UCHAR TargetIPType;
	UCHAR TargetIPAddr[16];
} PROXY_ARP_IPV6_ENTRY, *PPROXY_ARP_IPV6_ENTRY;

typedef struct _PROXY_ARP_IPV6_UNIT {
	UCHAR TargetMACAddr[MAC_ADDR_LEN];
	UCHAR TargetIPType;
	UCHAR TargetIPAddr[16];
} PROXY_ARP_IPV6_UNIT, *PPROXY_ARP_IPV6_UNIT;

typedef struct _WNM_CTRL {
	UINT32 TimeadvertisementIELen;
	UINT32 TimezoneIELen;
	PUCHAR TimeadvertisementIE;
	PUCHAR TimezoneIE;
	RTMP_OS_SEM BTMPeerListLock;
	BOOLEAN ProxyARPEnable;
	RTMP_OS_SEM ProxyARPListLock;
	RTMP_OS_SEM ProxyARPIPv6ListLock;
	DL_LIST IPv4ProxyARPList;
	DL_LIST IPv6ProxyARPList;
	DL_LIST BTMPeerList;
} WNM_CTRL, *PWNM_CTRL;

enum IPTYPE {
	IPV4,
	IPV6
};

BOOLEAN IsGratuitousARP(IN PUCHAR pData);

BOOLEAN IsUnsolicitedNeighborAdver(PRTMP_ADAPTER pAd, PUCHAR pData);

BOOLEAN IsIPv4ProxyARPCandidate(IN PRTMP_ADAPTER pAd, IN PUCHAR pData);

BOOLEAN IsIPv6ProxyARPCandidate(IN PRTMP_ADAPTER pAd, IN PUCHAR pData);

BOOLEAN IsIPv6RouterSolicitation(IN PRTMP_ADAPTER pAd, IN PUCHAR pData);

BOOLEAN IsIPv6RouterAdvertisement(IN PRTMP_ADAPTER pAd, IN PUCHAR pData);

BOOLEAN IsTDLSPacket(IN PRTMP_ADAPTER pAd, IN PUCHAR pData);

struct _MULTISSID_STRUCT;

BOOLEAN IPv4ProxyARP(IN PRTMP_ADAPTER pAd,
		     IN struct _MULTISSID_STRUCT *pMbss, IN PUCHAR pData, IN BOOLEAN FromDS);

BOOLEAN IsIpv6DuplicateAddrDetect(PRTMP_ADAPTER pAd, PUCHAR pData);

BOOLEAN IPv6ProxyARP(IN PRTMP_ADAPTER pAd,
		     IN struct _MULTISSID_STRUCT *pMbss, IN PUCHAR pData, IN BOOLEAN FromDS);

UINT32 AddIPv4ProxyARPEntry(IN PRTMP_ADAPTER pAd,
			    IN struct _MULTISSID_STRUCT *pMbss,
			    IN PUCHAR pTargetMACAddr, IN PUCHAR pTargetIPAddr);

UINT32 AddIPv6ProxyARPEntry(IN PRTMP_ADAPTER pAd,
			    IN struct _MULTISSID_STRUCT *pMbss,
			    IN PUCHAR pTargetMACAddr, IN PUCHAR pTargetIPAddr);

UINT32 IPv4ProxyARPTableLen(IN PRTMP_ADAPTER pAd, IN struct _MULTISSID_STRUCT *pMbss);

UINT32 IPv6ProxyARPTableLen(IN PRTMP_ADAPTER pAd, IN struct _MULTISSID_STRUCT *pMbss);

BOOLEAN GetIPv4ProxyARPTable(IN PRTMP_ADAPTER pAd,
			     IN struct _MULTISSID_STRUCT *pMbss, OUT PUCHAR *ProxyARPTable);

BOOLEAN GetIPv6ProxyARPTable(IN PRTMP_ADAPTER pAd,
			     IN struct _MULTISSID_STRUCT *pMbss, OUT PUCHAR *ProxyARPTable);

VOID RemoveIPv4ProxyARPEntry(IN PRTMP_ADAPTER pAd,
			     IN struct _MULTISSID_STRUCT *pMbss, PUCHAR pTargetMACAddr);

VOID RemoveIPv6ProxyARPEntry(IN PRTMP_ADAPTER pAd,
			     IN struct _MULTISSID_STRUCT *pMbss, PUCHAR pTargetMACAddr);

VOID WNMCtrlInit(IN PRTMP_ADAPTER pAd);
VOID WNMCtrlExit(IN PRTMP_ADAPTER pAd);
VOID Clear_All_PROXY_TABLE(IN PRTMP_ADAPTER pAd);
#ifdef CONFIG_AP_SUPPORT
VOID WNMIPv4ProxyARPCheck(IN PRTMP_ADAPTER pAd,
			  PNDIS_PACKET pPacket, USHORT srcPort, USHORT dstPort, PUCHAR pSrcBuf);

VOID WNMIPv6ProxyARPCheck(IN PRTMP_ADAPTER pAd, PNDIS_PACKET pPacket, PUCHAR pSrcBuf);
#endif /* CONFIG_AP_SUPPORT */


#endif /* __WNM_H__ */
