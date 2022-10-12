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

#ifndef __AP_CFG_H__
#define __AP_CFG_H__

#include "rt_config.h"

INT RTMPAPPrivIoctlSet(RTMP_ADAPTER *pAd, RTMP_IOCTL_INPUT_STRUCT *wrq);

INT RTMPAPPrivIoctlShow(RTMP_ADAPTER *pAd, RTMP_IOCTL_INPUT_STRUCT *wrq);

VOID RTMPAPGetAssoMacTable(IN RTMP_ADAPTER * pAd, IN RTMP_IOCTL_INPUT_STRUCT * pIoctlCmdStr);

#if defined(INF_AR9) || defined(BB_SOC)
#if defined(AR9_MAPI_SUPPORT) || defined(BB_SOC)
INT RTMPAPPrivIoctlAR9Show(IN RTMP_ADAPTER * pAd, IN RTMP_IOCTL_INPUT_STRUCT * pIoctlCmdStr);

VOID RTMPAR9IoctlGetMacTable(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlGetSTAT2(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlGetRadioDynInfo(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);
#endif /*AR9_MAPI_SUPPORT */
#endif /* INF_AR9 */

INT RTMPAPSetInformation(PRTMP_ADAPTER pAd, RTMP_IOCTL_INPUT_STRUCT *wrq,
			 INT cmd);

INT RTMPAPQueryInformation(RTMP_ADAPTER *pAd, RTMP_IOCTL_INPUT_STRUCT *wrq,
			   INT cmd);

VOID RTMPIoctlStatistics(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlGetMacTableStaInfo(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlGetMacTable(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPAPIoctlE2PROM(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

#if defined(DBG) || (defined(BB_SOC) && defined(RALINK_ATE))
VOID RTMPAPIoctlBBP(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPAPIoctlMAC(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

#ifdef RTMP_RF_RW_SUPPORT
VOID RTMPAPIoctlRF(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);
#endif /* RTMP_RF_RW_SUPPORT */

#endif /* DBG */

VOID RtmpDrvRateGet(IN VOID *pReserved,
/*	IN	PHTTRANSMIT_SETTING		pHtPhyMode, */
		    IN UINT8 MODE,
		    IN UINT8 ShortGI,
		    IN UINT8 BW, IN UINT8 MCS, IN UINT8 Antena, OUT UINT32 * pRate);

#ifdef WSC_AP_SUPPORT
VOID RTMPIoctlWscProfile(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlWscProfile(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);
/*add by woody */
#if defined(INF_AR9) || defined(BB_SOC)
#if defined(AR9_MAPI_SUPPORT) || defined(BB_SOC)
VOID RTMPAR9IoctlWscProfile(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlWscPINCode(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlWscStatus(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlGetWscDynInfo(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlGetWscRegsDynInfo(IN PRTMP_ADAPTER pAdapter, IN RTMP_IOCTL_INPUT_STRUCT * wrq);
#endif /*AR9_MAPI_SUPPORT */
#endif /* INF_AR9 */
#endif /* WSC_AP_SUPPORT */

VOID RTMPIoctlQueryBaTable(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

#ifdef DOT1X_SUPPORT
VOID RTMPIoctlStaticWepCopy(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlRadiusData(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlAddWPAKey(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlAddPMKIDCache(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlSetIdleTimeout(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);

VOID RTMPIoctlQueryStaAid(IN PRTMP_ADAPTER pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq);
#endif /* DOT1X_SUPPORT */

INT Set_AP_Daemon_Status(IN PRTMP_ADAPTER pAd, IN UINT8 WorkSpaceID, IN BOOLEAN Status);

INT Set_AP_IE(IN PRTMP_ADAPTER pAd, IN PSTRING IE, IN UINT32 IELen);

#ifdef CONFIG_HOTSPOT
INT Send_ANQP_Rsp(IN PRTMP_ADAPTER pAd,
		  IN PSTRING PeerMACAddr, IN PSTRING ANQPReq, IN UINT32 ANQPReqLen);
#endif /* endif */

INT ApCfg_Set_AuthMode_Proc(IN PRTMP_ADAPTER pAd, IN INT apidx, IN PSTRING arg);

INT ApCfg_Set_MaxStaNum_Proc(IN PRTMP_ADAPTER pAd, IN INT apidx, IN PSTRING arg);

INT ApCfg_Set_IdleTimeout_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#ifdef APCLI_SUPPORT
#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
VOID RTMPApCliAddKey(IN PRTMP_ADAPTER pAd, IN INT apidx, IN PNDIS_APCLI_802_11_KEY pApcliKey);
#endif /* APCLI_WPA_SUPPLICANT_SUPPORT */
#endif /* APCLI_SUPPORT */
#endif /* __AP_CFG_H__ */
