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


#ifndef __WAPI_DEF_H__
#define __WAPI_DEF_H__

#ifndef IN
#define IN
#endif /* endif */
#ifndef OUT
#define OUT
#endif /* endif */
#ifndef INOUT
#define INOUT
#endif /* endif */
#ifndef MAC_ADDR_LEN
#define MAC_ADDR_LEN   6
#endif
#ifndef TRUE
#define TRUE	1
#endif /* endif */
#ifndef FALSE
#define FALSE	0
#endif /* endif */

#define WAPI_IFNAMSIZ		16
#define MAX_WAPI_MBSSID_NUM 8
#define MAX_ID_NO 10

#define LENGTH_WAI_H	12
#define LEN_WAPI_TSC	16
#define LEN_WPI_MIC		16
#define LEN_WPI_IV_HDR	18
#define LEN_WAPI_NMK	16
#define LEN_WAPI_GTK	32

/* trigger message from driver */
#define WAI_MLME_CERT_AUTH_START	1
#define WAI_MLME_KEY_HS_START		2
#define WAI_MLME_UPDATE_BK			3
#define WAI_MLME_UPDATE_USK			4
#define WAI_MLME_UPDATE_MSK			5
#define WAI_MLME_DISCONNECT			0xff

#define WAPI_KEY_UPDATE_EXEC_INTV   1000				/* 1 sec */

/* WAPI rekey method */
#define REKEY_METHOD_DISABLE	    0
#define REKEY_METHOD_TIME	    1
#define REKEY_METHOD_PKT	    2
/*#define REKEY_METHOD_TIME_PKT	    3 */

#define STATUS_WAPI_KEY_INVALID		1
#define STATUS_WAPI_IV_MISMATCH		2
#define STATUS_WAPI_MIC_DIFF		3

extern UCHAR AE_BCAST_PN[LEN_WAPI_TSC];
extern UCHAR ASUE_UCAST_PN[LEN_WAPI_TSC];
extern UCHAR AE_UCAST_PN[LEN_WAPI_TSC];

/* WAPI authentication mode */
typedef enum _WAPI_AUTH_MODE
{
   WAPI_AUTH_DISABLE,
   WAPI_AUTH_PSK,
   WAPI_AUTH_CERT,
} WAPI_AUTH_MODE, *PWAPI_AUTH_MODE;

/* WAPI authentication mode */
typedef enum _KEY_TYPE_MODE
{
   HEX_MODE,
   ASCII_MODE
} KEY_TYPE_MODE, *PKEY_TYPE_MODE;

/* the defintion of WAI header */
typedef	struct GNU_PACKED _HEADER_WAI	{
    USHORT	    version;
	UCHAR			type;
	UCHAR			sub_type;
	USHORT			reserved;
	USHORT			length;
	USHORT			pkt_seq;
	UCHAR			frag_seq;
	UCHAR			flag;
}	HEADER_WAI, *PHEADER_WAI;

/* For WAPI */
typedef struct GNU_PACKED _WAPIIE {
    USHORT  version;
    USHORT  acount;
    struct GNU_PACKED {
	UCHAR oui[4];
    }auth[1];
} WAPIIE, *PWAPIIE;

/* unicast key suite */
typedef struct GNU_PACKED _WAPIIE_UCAST {
    USHORT ucount;
    struct GNU_PACKED {
	UCHAR oui[4];
    }ucast[1];
} WAPIIE_UCAST,*PWAPIIE_UCAST;

/* multi-cast key suite and capability */
typedef struct GNU_PACKED _WAPIIE_MCAST {
    UCHAR   mcast[4];
    USHORT  capability;
} WAPIIE_MCAST,*PWAPIIE_MCAST;

/* the relative to wapi daemon */
typedef struct GNU_PACKED _COMMON_WAPI_INFO
{
	UINT8			wapi_ifname[WAPI_IFNAMSIZ];		/* wai negotiation */
	UINT8			wapi_ifname_len;
	UINT8			preauth_ifname[WAPI_IFNAMSIZ];	/* pre-authentication */
	UINT8			preauth_ifname_len;
	UINT8			as_cert_no;
	UINT8			as_cert_path[MAX_ID_NO][128];			/* the path of as certification */
	UINT8			as_cert_path_len[MAX_ID_NO];
	UINT8			ca_cert_path[128];			/* the path of ca certification */
	UINT8			ca_cert_path_len;
	UINT8			user_cert_path[128];		/* the path of local user certification */
	UINT8			user_cert_path_len;
	UINT32			wapi_as_ip;					/* the ip address of authentication server */
	UINT32			wapi_as_port;				/* the port of authentication server */
} COMMON_WAPI_INFO, *PCOMMON_WAPI_INFO;

typedef struct GNU_PACKED _MBSS_WAPI_INFO
{
	UINT8			ifname[WAPI_IFNAMSIZ];
	UINT8			ifname_len;
	UINT8			auth_mode;
    UINT8		psk[64];
	UINT8			psk_len;
	UINT8			wie[128];
	UINT8			wie_len;
} MBSS_WAPI_INFO, *PMBSS_WAPI_INFO;

/* It's used by wapi daemon to require relative configuration */
typedef struct GNU_PACKED _WAPI_CONF
{
    UINT8				mbss_num;					/* indicate multiple BSS number */
	COMMON_WAPI_INFO	comm_wapi_info;
	MBSS_WAPI_INFO		mbss_wapi_info[MAX_WAPI_MBSSID_NUM];
} WAPI_CONF, *PWAPI_CONF;

#ifdef LINUX
#define WapiMoveMemory(Destination, Source, Length) memmove(Destination, Source, Length)
#define WapiZeroMemory(Destination, Length)	    memset(Destination, 0, Length)
#define WapiEqualMemory(Source1, Source2, Length)   (!memcmp(Source1, Source2, Length))
#endif /* LINUX */

#endif /* __WAPI_DEF_H__ */
