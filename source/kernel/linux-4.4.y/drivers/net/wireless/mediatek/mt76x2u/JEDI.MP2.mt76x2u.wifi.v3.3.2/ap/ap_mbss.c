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

    Support multi-BSS function.

    Note:
    1. Call RT28xx_MBSS_Init() in init function and
       call RT28xx_MBSS_Remove() in close function

    2. MAC of different BSS is initialized in APStartUp()

    3. BSS Index (0 ~ 15) of different rx packet is got in
       APHandleRxDoneInterrupt() by using FromWhichBSSID = pEntry->apidx;
       Or FromWhichBSSID = BSS0;

    4. BSS Index (0 ~ 15) of different tx packet is assigned in
       rt28xx_send_packets() by using RTMP_SET_PACKET_NET_DEVICE_MBSSID()
    5. BSS Index (0 ~ 15) of different BSS is got in APHardTransmit() by using
       RTMP_GET_PACKET_IF()

    6. BSS Index (0 ~ 15) of IOCTL command is put in pAd->OS_Cookie->ioctl_if

    7. Beacon of different BSS is enabled in APMakeAllBssBeacon() by writing 1
       to the register MAC_BSSID_DW1

    8. The number of MBSS can be 1, 2, 4, or 8

***************************************************************************/
#ifdef MBSS_SUPPORT

#include "rt_config.h"

/* --------------------------------- Public -------------------------------- */
/*
========================================================================
Routine Description:
    Initialize Multi-BSS function.

Arguments:
    pAd			points to our adapter
    pDevMain		points to the main BSS network interface

Return Value:
    None

Note:
	1. Only create and initialize virtual network interfaces.
	2. No main network interface here.
	3. If you down ra0 and modify the BssNum of RT2860AP.dat/RT2870AP.dat,
		it will not work! You must rmmod rt2860ap.ko and lsmod rt2860ap.ko again.
========================================================================
*/
VOID MBSS_Init(RTMP_ADAPTER *pAd, RTMP_OS_NETDEV_OP_HOOK *pNetDevOps)
{
#define MBSS_MAX_DEV_NUM	32
	PNET_DEV pDevNew;
	INT32 IdBss, MaxNumBss;
	INT status;
	RTMP_OS_NETDEV_OP_HOOK netDevHook;

	/* sanity check to avoid redundant virtual interfaces are created */
	if (pAd->FlgMbssInit != FALSE)
		return;


	MaxNumBss = pAd->ApCfg.BssidNum;
	if (MaxNumBss > MAX_MBSSID_NUM(pAd))
		MaxNumBss = MAX_MBSSID_NUM(pAd);

	/* first IdBss must not be 0 (BSS0), must be 1 (BSS1) */
	for (IdBss = FIRST_MBSSID; IdBss < MAX_MBSSID_NUM(pAd); IdBss++)
		pAd->ApCfg.MBSSID[IdBss].wdev.if_dev = NULL;

	/* create virtual network interface */
	for (IdBss = FIRST_MBSSID; IdBss < MaxNumBss; IdBss++) {
		struct wifi_dev *wdev;
		UINT32 MC_RowID = 0, IoctlIF = 0;
		char *dev_name;
#ifdef MULTIPLE_CARD_SUPPORT
		MC_RowID = pAd->MC_RowID;
#endif /* MULTIPLE_CARD_SUPPORT */
#ifdef HOSTAPD_SUPPORT
		IoctlIF = pAd->IoctlIF;
#endif /* HOSTAPD_SUPPORT */

		dev_name = get_dev_name_prefix(pAd, INT_MBSSID);
		if (!dev_name) {
			DBGPRINT(RT_DEBUG_ERROR, ("%s(): Get dev name prefix fail!\n",
					 __func__));
			break;
		}

		pDevNew =
		    RtmpOSNetDevCreate(MC_RowID, &IoctlIF, INT_MBSSID, IdBss,
				       sizeof(struct mt_dev_priv), dev_name);
#ifdef HOSTAPD_SUPPORT
		pAd->IoctlIF = IoctlIF;
#endif /* HOSTAPD_SUPPORT */
		if (pDevNew == NULL) {
			pAd->ApCfg.BssidNum = IdBss;	/* re-assign new MBSS number */
			break;
		}

		DBGPRINT(RT_DEBUG_TRACE,
			 ("Register MBSSID IF (%s)\n",
			  RTMP_OS_NETDEV_GET_DEVNAME(pDevNew)));


		if (IdBss < HW_BEACON_MAX_NUM) {
			wdev = &pAd->ApCfg.MBSSID[IdBss].wdev;
			wdev->wdev_type = WDEV_TYPE_AP;
			wdev->func_dev = &pAd->ApCfg.MBSSID[IdBss];
			wdev->sys_handle = (void *)pAd;
			wdev->if_dev = pDevNew;
		} else {
			DBGPRINT(RT_DEBUG_ERROR, ("%s: IdBss >= HW_BEACON_MAX_NUM.\n", __func__));
			break;
		}

		if (rtmp_wdev_idx_reg(pAd, wdev) < 0) {
			DBGPRINT(RT_DEBUG_ERROR,
				 ("Assign wdev idx for %s failed, free net device!\n",
				  RTMP_OS_NETDEV_GET_DEVNAME(pDevNew)));
			RtmpOSNetDevFree(pDevNew);
			pDevNew = NULL;
			wdev->if_dev = NULL;
			break;
		}
		wdev->tx_pkt_allowed = ApAllowToSendPacket;

		RTMP_OS_NETDEV_SET_PRIV(pDevNew, pAd);
		RTMP_OS_NETDEV_SET_WDEV(pDevNew, wdev);

		/* init operation functions and flags */
		NdisCopyMemory(&netDevHook, pNetDevOps, sizeof(netDevHook));

		netDevHook.priv_flags = INT_MBSSID;
		netDevHook.needProtcted = TRUE;
		netDevHook.wdev = wdev;

		/* Init MAC address of virtual network interface */
		NdisMoveMemory(&netDevHook.devAddr[0], &wdev->bssid[0], MAC_ADDR_LEN);

		/* register this device to OS */
		status = RtmpOSNetDevAttach(pAd->OpMode, pDevNew, &netDevHook);
	}

	pAd->FlgMbssInit = TRUE;

}

/*
========================================================================
Routine Description:
    Remove Multi-BSS network interface.

Arguments:
	pAd			points to our adapter

Return Value:
    None

Note:
    FIRST_MBSSID = 1
    Main BSS is not removed here.
========================================================================
*/
VOID MBSS_Remove(RTMP_ADAPTER *pAd)
{
	struct wifi_dev *wdev;
	UINT IdBss;


	for (IdBss = FIRST_MBSSID; IdBss < MAX_MBSSID_NUM(pAd); IdBss++) {
		wdev = &pAd->ApCfg.MBSSID[IdBss].wdev;
		if (wdev->if_dev) {
			RtmpOSNetDevProtect(1);
			RtmpOSNetDevDetach(wdev->if_dev);
			RtmpOSNetDevProtect(0);
			rtmp_wdev_idx_unreg(pAd, wdev);
			RtmpOSNetDevFree(wdev->if_dev);
			wdev->if_dev = NULL;
		}
	}
}

/*
========================================================================
Routine Description:
    Get multiple bss idx.

Arguments:
	pAd				points to our adapter
	pDev			which WLAN network interface

Return Value:
    0: close successfully
    otherwise: close fail

Note:
========================================================================
*/
INT32 RT28xx_MBSS_IdxGet(RTMP_ADAPTER *pAd, PNET_DEV pDev)
{
	INT32 BssId = -1;
	INT32 IdBss;

	for (IdBss = 0; IdBss < pAd->ApCfg.BssidNum; IdBss++) {
		if (pAd->ApCfg.MBSSID[IdBss].wdev.if_dev == pDev) {
			BssId = IdBss;
			break;
		}
	}

	return BssId;
}

/*
========================================================================
Routine Description:
    Open a virtual network interface.

Arguments:
	pDev			which WLAN network interface

Return Value:
    0: open successfully
    otherwise: open fail

Note:
========================================================================
*/
INT MBSS_Open(PNET_DEV pDev)
{
	PRTMP_ADAPTER pAd;
	INT BssId;

	pAd = RTMP_OS_NETDEV_GET_PRIV(pDev);
	BssId = RT28xx_MBSS_IdxGet(pAd, pDev);
	if (BssId < 0)
		return -1;
	if (BssId < HW_BEACON_MAX_NUM)
		pAd->ApCfg.MBSSID[BssId].bBcnSntReq = TRUE;

	return 0;
}

/*
========================================================================
Routine Description:
    Close a virtual network interface.

Arguments:
    pDev	   which WLAN network interface

Return Value:
    0: close successfully
    otherwise: close fail

Note:
========================================================================
*/
INT MBSS_Close(PNET_DEV pDev)
{
	PRTMP_ADAPTER pAd;
	INT BssId;

	pAd = RTMP_OS_NETDEV_GET_PRIV(pDev);
	BssId = RT28xx_MBSS_IdxGet(pAd, pDev);
	if (BssId < 0)
		return -1;

	RTMP_OS_NETDEV_STOP_QUEUE(pDev);

	/* kick out all stas behind the Bss */
	MbssKickOutStas(pAd, BssId, REASON_DISASSOC_INACTIVE);

	if (BssId < HW_BEACON_MAX_NUM)
		pAd->ApCfg.MBSSID[BssId].bBcnSntReq = FALSE;

	APMakeAllBssBeacon(pAd);
	APUpdateAllBeaconFrame(pAd);

	return 0;
}

#endif /* MBSS_SUPPORT */
