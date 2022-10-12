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

    Module Name:
    rt_os_util.c

    Abstract:
	All functions provided from UTIL module are put here (OS independent).

    Revision History:
    Who	       When	     What
    ---------  ----------    ----------------------------------------------

***************************************************************************/

#define RTMP_MODULE_OS
#define RTMP_MODULE_OS_UTIL

/*#include "rt_config.h"
*/
#include "rtmp_comm.h"
#include "rt_os_util.h"


VOID RtmpDrvRateGet(IN VOID *pReserved,
		    IN UINT8 MODE,
		    IN UINT8 ShortGI,
		    IN UINT8 BW, IN UINT8 MCS, IN UINT8 Antenna, OUT UINT32 * pRate)
{
	UINT32 MCS_1NSS = (UINT32) MCS;
	*pRate = 0;

	DBGPRINT(RT_DEBUG_INFO,
		 ("<==== %s\nMODE: %x shortGI: %x BW: %x MCS: %x Antenna: %x\n", __func__,
		  MODE, ShortGI, BW, MCS, Antenna));
	if ((BW >= Rate_BW_MAX) || (ShortGI >= Rate_GI_MAX) || (BW >= Rate_BW_MAX)) {
		DBGPRINT(RT_DEBUG_INFO,
			 ("<==== %s MODE: %x shortGI: %x BW: %x MCS: %x Antenna: %x , param error\n",
			  __func__, MODE, ShortGI, BW, MCS, Antenna));
		return;
	}
#ifdef DOT11_VHT_AC
	if (MODE >= MODE_VHT) {
		if (MCS_1NSS > 9) {
			Antenna = (MCS / 10) + 1;
			MCS_1NSS %= 10;
		}
		*pRate = RalinkRate_VHT_1NSS[BW][ShortGI][MCS_1NSS];
	} else
#endif /* DOT11_VHT_AC */

	if ((MODE >= MODE_HTMIX) && (MODE < MODE_VHT)) {
		if (MCS_1NSS > 7) {
			Antenna = (MCS / 8) + 1;
			MCS_1NSS %= 8;
		}
		*pRate = RalinkRate_HT_1NSS[BW][ShortGI][MCS_1NSS];
	} else if (MODE == MODE_OFDM)
		*pRate = RalinkRate_Legacy[MCS_1NSS + 4];
	else
		*pRate = RalinkRate_Legacy[MCS_1NSS];

	*pRate *= 500000;
	if (MODE >= MODE_HTMIX)
		*pRate *= Antenna;

	DBGPRINT(RT_DEBUG_INFO,
		 ("=====> %s\nMODE: %x shortGI: %x BW: %x MCS: %x Antenna: %x  Rate = %d\n",
		  __func__, MODE, ShortGI, BW, MCS_1NSS, Antenna, (*pRate) / 1000000));

}

VOID DrvRateGet(IN UINT16 TxRate, OUT UINT32 *pRate)
{
	UINT8 uBW = (TxRate >> 7) & 0x03;
	UINT8 uMode = (TxRate >> 13) & 0x07;
	UINT8 uMCS = 0;
	UINT8 uShortGI =  (TxRate >> 9) & 0x01;
	UINT8 uSS = 0;
	*pRate = 0;

	if (uMode >=  MODE_VHT) {
		uMCS = TxRate & 0x0f;
		uSS = ((TxRate >> 4) & 0x3) + 1;
	} else {
		uMCS = TxRate & 0x3f;
	}

#ifdef DOT11_VHT_AC
	if (uMode >= MODE_VHT) {
		*pRate = RalinkRate_VHT_1NSS[uBW][uShortGI][uMCS];
	} else
#endif /* DOT11_VHT_AC */

	if ((uMode >= MODE_HTMIX) && (uMode < MODE_VHT)) {
		if (uMCS > 9) {
			uSS = (uMCS / 10) + 1;
			uMCS %= 10;
		}
		*pRate = RalinkRate_HT_1NSS[uBW][uShortGI][uMCS];
	} else if (uMode == MODE_OFDM)
		*pRate = RalinkRate_Legacy[uMCS + 4];
	else
		*pRate = RalinkRate_Legacy[uMCS];

	*pRate *= 500000;
	if (uMode >= MODE_HTMIX)
		*pRate *= uSS;
	DBGPRINT(RT_DEBUG_INFO,
			("%s == >Mode = %d, MSC = %d,BW = %d, GI = %d, SS = %d Rate %d\n",
			__func__, uMode, uMCS, uBW, uShortGI, uSS, (*pRate) / 1000000));
}

char *rtstrchr(const char *s, int c)
{
	for (; *s != (char)c; ++s)
		if (*s == '\0')
			return NULL;
	return (char *)s;
}

VOID RtmpMeshDown(IN VOID *pDrvCtrlBK,
		  IN BOOLEAN WaitFlag, IN BOOLEAN(*RtmpMeshLinkCheck) (IN VOID *pAd))
{
}


BOOLEAN RtmpOsCmdDisplayLenCheck(IN UINT32 LenSrc, IN UINT32 Offset)
{
	if (LenSrc > (IW_PRIV_SIZE_MASK - Offset))
		return FALSE;

	return TRUE;
}

#ifdef WPA_SUPPLICANT_SUPPORT
VOID WpaSendMicFailureToWpaSupplicant(IN PNET_DEV pNetDev,
				      IN const PUCHAR src_addr,
				      IN BOOLEAN bUnicast, IN INT key_id, IN const PUCHAR tsc)
{
#ifdef RT_CFG80211_SUPPORT
	CFG80211OS_MICFailReport(pNetDev, src_addr, bUnicast, key_id, tsc);
#else
	char custom[IW_CUSTOM_MAX] = { 0 };

	snprintf(custom, sizeof(custom), "MLME-MICHAELMICFAILURE.indication");
	if (bUnicast)
		sprintf(custom, "%s unicast", custom);

	RtmpOSWrielessEventSend(pNetDev, RT_WLAN_EVENT_CUSTOM, -1, NULL, (PUCHAR) custom,
				strlen(custom));
#endif /* RT_CFG80211_SUPPORT */

}
#endif /* WPA_SUPPLICANT_SUPPORT */

#ifdef NATIVE_WPA_SUPPLICANT_SUPPORT
int wext_notify_event_assoc(IN PNET_DEV pNetDev, IN UCHAR * ReqVarIEs, IN UINT32 ReqVarIELen)
{
	char custom[IW_CUSTOM_MAX] = { 0 };

#if WIRELESS_EXT > 17
	if (ReqVarIELen <= IW_CUSTOM_MAX) {
		NdisMoveMemory(custom, ReqVarIEs, ReqVarIELen);
		RtmpOSWrielessEventSend(pNetDev, RT_WLAN_EVENT_ASSOC_REQ_IE, -1, NULL,
					(UCHAR *) custom, ReqVarIELen);
	} else
		DBGPRINT(RT_DEBUG_TRACE, ("pAd->StaCfg.ReqVarIELen > MAX_CUSTOM_LEN\n"));
#else
	int len;

	len = (ReqVarIELen * 2) + 17;
	if (len <= IW_CUSTOM_MAX) {
		UCHAR idx;

		snprintf(custom, sizeof(custom), "ASSOCINFO(ReqIEs=");
		for (idx = 0; idx < ReqVarIELen; idx++)
			sprintf(custom, "%s%02x", custom, ReqVarIEs[idx]);
		RtmpOSWrielessEventSend(pNetDev, RT_WLAN_EVENT_CUSTOM, -1, NULL, custom, len);
	} else
		DBGPRINT(RT_DEBUG_TRACE, ("len(%d) > MAX_CUSTOM_LEN\n", len));
#endif /* WIRELESS_EXT > 17 */

	return 0;

}
#endif /* NATIVE_WPA_SUPPLICANT_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef WPA_SUPPLICANT_SUPPORT
#ifndef NATIVE_WPA_SUPPLICANT_SUPPORT
VOID SendAssocIEsToWpaSupplicant(IN PNET_DEV pNetDev, IN UCHAR *ReqVarIEs, IN UINT32 ReqVarIELen)
{
	STRING custom[IW_CUSTOM_MAX] = { 0 };

	if ((ReqVarIELen + 17) <= IW_CUSTOM_MAX) {
		snprintf(custom, sizeof(custom), "ASSOCINFO_ReqIEs=");
		NdisMoveMemory(custom + 17, ReqVarIEs, ReqVarIELen);
		RtmpOSWrielessEventSend(pNetDev, RT_WLAN_EVENT_CUSTOM, RT_REQIE_EVENT_FLAG, NULL,
					(PUCHAR) custom, ReqVarIELen + 17);

		RtmpOSWrielessEventSend(pNetDev, RT_WLAN_EVENT_CUSTOM, RT_ASSOCINFO_EVENT_FLAG,
					NULL, NULL, 0);
	} else
		DBGPRINT(RT_DEBUG_TRACE, ("pAd->StaCfg.ReqVarIELen + 17 > MAX_CUSTOM_LEN\n"));

}
#endif /* NATIVE_WPA_SUPPLICANT_SUPPORT */
#endif /* WPA_SUPPLICANT_SUPPORT */
#endif /*CONFIG_STA_SUPPORT */

INT32 RtPrivIoctlSetVal(VOID)
{
	return (INT32) RTPRIV_IOCTL_SET;
}

#ifndef RTMP_ANDES_JAY
#ifdef RTMP_USB_SUPPORT
/*
PVOID RtmpAllocCompletion(VOID)
{
	struct completion *comp = NULL;
	os_alloc_mem(NULL, (UCHAR **)&comp, sizeof(struct completion));
	if (comp)
		init_completion(comp);

	return comp;
}

VOID RtmpInitCompletion(VOID *comp)
{
	struct completion *complete = (struct completion *)comp;
	init_completion(complete);
}

ULONG RtmpWaitForCompletionTimeout(VOID *Completion, ULONG Expire)
{
	return wait_for_completion_timeout((struct completion *)Completion, Expire);
}

VOID RtmpComplete(VOID *Completion)
{
	complete((struct completion *)Completion);
}

ULONG RtmpMsecsToJiffies(UINT32 msecs)
{
	return msecs_to_jiffies(msecs);
}
*/
#endif /* RTMP_USB_SUPPORT */
#endif /* RTMP_ANDES_JAY */
