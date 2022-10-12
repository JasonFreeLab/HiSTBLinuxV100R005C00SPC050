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


#ifndef _RT_OS_H_
#define _RT_OS_H_

#ifdef LINUX
#if WIRELESS_EXT <= 11
#ifndef SIOCDEVPRIVATE
#define SIOCDEVPRIVATE				    0x8BE0
#endif /* endif */
#define SIOCIWFIRSTPRIV								SIOCDEVPRIVATE
#endif /* endif */
#endif /* LINUX */

#ifdef CONFIG_STA_SUPPORT
#define RT_PRIV_IOCTL	(SIOCIWFIRSTPRIV + 0x01)	/* Sync. with AP for wsc upnp daemon */
#ifdef MT53XX
#define RTPRIV_IOCTL_SET			    (SIOCIWFIRSTPRIV + 0x02)
#else
#define RTPRIV_IOCTL_SET			    (SIOCIWFIRSTPRIV + 0x1D)
#endif

#ifdef DBG
#define RTPRIV_IOCTL_BBP			    (SIOCIWFIRSTPRIV + 0x03)
#define RTPRIV_IOCTL_MAC			    (SIOCIWFIRSTPRIV + 0x05)

#ifdef RTMP_RF_RW_SUPPORT
#define RTPRIV_IOCTL_RF	   (SIOCIWFIRSTPRIV + 0x13)	/* edit by johnli, fix read rf register problem */
#endif /* RTMP_RF_RW_SUPPORT */
#define RTPRIV_IOCTL_E2P			    (SIOCIWFIRSTPRIV + 0x07)
#endif /* DBG */

#ifdef WCX_SUPPORT
#define RTPRIV_IOCTL_META_SET			    (SIOCIWFIRSTPRIV + 0x08)
#define RTPRIV_IOCTL_META_QUERY			    (SIOCIWFIRSTPRIV + 0x09)
#define RTPRIV_IOCTL_META_SET_EM		    (SIOCIWFIRSTPRIV + 0x0B)
#define RTPRIV_IOCTL_STATISTICS			    (SIOCIWFIRSTPRIV + 0x15)
#else
#define RTPRIV_IOCTL_ATE			    (SIOCIWFIRSTPRIV + 0x08)	/* For QA Tool */
#define RTPRIV_IOCTL_STATISTICS			    (SIOCIWFIRSTPRIV + 0x09)
#endif /* WCX_SUPPORT */

#define RTPRIV_IOCTL_ADD_PMKID_CACHE		    (SIOCIWFIRSTPRIV + 0x0A)
#define RTPRIV_IOCTL_RADIUS_DATA		    (SIOCIWFIRSTPRIV + 0x0C)
#define RTPRIV_IOCTL_GSITESURVEY					(SIOCIWFIRSTPRIV + 0x0D)
#define RT_PRIV_IOCTL_EXT	(SIOCIWFIRSTPRIV + 0x0E)	/* Sync. with RT61 (for wpa_supplicant) */
#define RTPRIV_IOCTL_GET_MAC_TABLE					(SIOCIWFIRSTPRIV + 0x0F)
#define RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT	(SIOCIWFIRSTPRIV + 0x1F)	/* modified by Red@Ralink, 2009/09/30 */

#define RTPRIV_IOCTL_SHOW							(SIOCIWFIRSTPRIV + 0x11)

#ifdef WSC_STA_SUPPORT
#define RTPRIV_IOCTL_SET_WSC_PROFILE_U32_ITEM	    (SIOCIWFIRSTPRIV + 0x14)
#define RTPRIV_IOCTL_SET_WSC_PROFILE_STRING_ITEM    (SIOCIWFIRSTPRIV + 0x16)
#endif /* WSC_STA_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
/* Ralink defined OIDs */
#define RT_PRIV_IOCTL								(SIOCIWFIRSTPRIV + 0x01)
#ifdef MT53XX
#define RTPRIV_IOCTL_SET			    (SIOCIWFIRSTPRIV + 0x02)
#else
#define RTPRIV_IOCTL_SET			    (SIOCIWFIRSTPRIV + 0x1D)
#endif
#define RT_PRIV_IOCTL_EXT		(SIOCIWFIRSTPRIV + 0x0E)	/* Sync. with RT61 (for wpa_supplicant) */
#if defined(DBG) || defined(BB_SOC)
#define RTPRIV_IOCTL_BBP			    (SIOCIWFIRSTPRIV + 0x03)
#define RTPRIV_IOCTL_MAC			    (SIOCIWFIRSTPRIV + 0x05)

#ifdef RTMP_RF_RW_SUPPORT
#define RTPRIV_IOCTL_RF				    (SIOCIWFIRSTPRIV + 0x13)
#endif /* RTMP_RF_RW_SUPPORT */

#endif /* DBG */
#define RTPRIV_IOCTL_E2P			    (SIOCIWFIRSTPRIV + 0x07)

#ifdef WCX_SUPPORT
#define MTPRIV_IOCTL_META_SET			    (SIOCIWFIRSTPRIV + 0x08)
#define MTPRIV_IOCTL_META_QUERY			    (SIOCIWFIRSTPRIV + 0x09)
#define MTPRIV_IOCTL_META_SET_EM		    (SIOCIWFIRSTPRIV + 0x0B)
#define RTPRIV_IOCTL_STATISTICS			    (SIOCIWFIRSTPRIV + 0x15)
#else
#define RTPRIV_IOCTL_ATE			    (SIOCIWFIRSTPRIV + 0x08)	/* For QA Tool */
#define RTPRIV_IOCTL_STATISTICS			    (SIOCIWFIRSTPRIV + 0x09)
#endif /* WCX_SUPPORT */

#define RTPRIV_IOCTL_ADD_PMKID_CACHE		    (SIOCIWFIRSTPRIV + 0x0A)
#define RTPRIV_IOCTL_RADIUS_DATA		    (SIOCIWFIRSTPRIV + 0x0C)
#define RTPRIV_IOCTL_GSITESURVEY					(SIOCIWFIRSTPRIV + 0x0D)
#define RTPRIV_IOCTL_ADD_WPA_KEY		    (SIOCIWFIRSTPRIV + 0x0E)
#define RTPRIV_IOCTL_GET_MAC_TABLE					(SIOCIWFIRSTPRIV + 0x0F)
#define RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT	(SIOCIWFIRSTPRIV + 0x1F)	/* modified by Red@Ralink, 2009/09/30 */
#define RTPRIV_IOCTL_STATIC_WEP_COPY		    (SIOCIWFIRSTPRIV + 0x10)

#define RTPRIV_IOCTL_SHOW							(SIOCIWFIRSTPRIV + 0x11)
#define RTPRIV_IOCTL_WSC_PROFILE		    (SIOCIWFIRSTPRIV + 0x12)
#define RTPRIV_IOCTL_QUERY_BATABLE		    (SIOCIWFIRSTPRIV + 0x16)
#if defined(INF_AR9)  || defined(BB_SOC)
#define RTPRIV_IOCTL_GET_AR9_SHOW   (SIOCIWFIRSTPRIV + 0x17)
#endif /* INF_AR9 */
#define RTPRIV_IOCTL_SET_WSCOOB	(SIOCIWFIRSTPRIV + 0x19)
#define RTPRIV_IOCTL_WSC_CALLBACK	(SIOCIWFIRSTPRIV + 0x1A)
#endif /* CONFIG_AP_SUPPORT */

#define RTPRIV_IOCTL_SET_SET_MAX_LEN 1024U /* max length in set_arg */
#define RTPRIV_IOCTL_SHOW_SET_MAX_LEN 32U /* max length in set_arg */
#endif /* _RT_OS_H_ */
