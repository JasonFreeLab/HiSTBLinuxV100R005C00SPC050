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

#ifdef BLOCK_NET_IF

#include "rt_config.h"
#include "netif_block.h"

static NETIF_ENTRY freeNetIfEntryPool[FREE_NETIF_POOL_SIZE];
static LIST_HEADER freeNetIfEntryList;

void initblockQueueTab(
	IN PRTMP_ADAPTER pAd)
{
	int i;

	initList(&freeNetIfEntryList);
	for (i = 0; i < FREE_NETIF_POOL_SIZE; i++)
		insertTailList(&freeNetIfEntryList, (PLIST_ENTRY)&freeNetIfEntryPool[i]);

	for (i=0; i < NUM_OF_TX_RING; i++)
		initList(&pAd->blockQueueTab[i].NetIfList);

	return;
}

BOOLEAN blockNetIf(
	IN PBLOCK_QUEUE_ENTRY pBlockQueueEntry,
	IN PNET_DEV pNetDev)
{
	PNETIF_ENTRY pNetIfEntry = NULL;

	if ((pNetIfEntry = (PNETIF_ENTRY)removeHeadList(&freeNetIfEntryList)) != NULL)
	{
		RTMP_OS_NETDEV_STOP_QUEUE(pNetDev);
		pNetIfEntry->pNetDev = pNetDev;
		insertTailList(&pBlockQueueEntry->NetIfList, (PLIST_ENTRY)pNetIfEntry);

		pBlockQueueEntry->SwTxQueueBlockFlag = TRUE;
		DBGPRINT(RT_DEBUG_TRACE, ("RTMP_OS_NETDEV_STOP_QUEUE(%s)\n", RTMP_OS_NETDEV_GET_DEVNAME(pNetDev)));
	}
	else
		return FALSE;

	return TRUE;
}

VOID releaseNetIf(
	IN PBLOCK_QUEUE_ENTRY pBlockQueueEntry)
{
	PNETIF_ENTRY pNetIfEntry = NULL;
	PLIST_HEADER pNetIfList = &pBlockQueueEntry->NetIfList;

	while((pNetIfEntry = (PNETIF_ENTRY)removeHeadList(pNetIfList)) !=  NULL)
	{
		PNET_DEV pNetDev = pNetIfEntry->pNetDev;
		RTMP_OS_NETDEV_WAKE_QUEUE(pNetDev);
		insertTailList(&freeNetIfEntryList, (PLIST_ENTRY)pNetIfEntry);

		DBGPRINT(RT_DEBUG_TRACE, ("RTMP_OS_NETDEV_WAKE_QUEUE(%s)\n", RTMP_OS_NETDEV_GET_DEVNAME(pNetDev)));
	}
	pBlockQueueEntry->SwTxQueueBlockFlag = FALSE;
	return;
}


VOID StopNetIfQueue(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR QueIdx,
	IN PNDIS_PACKET pPacket)
{
	PNET_DEV NetDev = NULL, wdev_NetDev= NULL;
	UCHAR IfIdx = 0;
	BOOLEAN valid = FALSE;


	IfIdx = RTMP_GET_PACKET_WDEV(pPacket);
	if ((IfIdx < WDEV_NUM_MAX) && (pAd->wdev_list[IfIdx] != NULL)) {
		wdev_NetDev = pAd->wdev_list[IfIdx]->if_dev;
	}

#ifdef APCLI_SUPPORT
	if (RTMP_GET_PACKET_NET_DEVICE(pPacket) >= MIN_NET_DEVICE_FOR_APCLI)
	{
		IfIdx = (RTMP_GET_PACKET_NET_DEVICE(pPacket) - MIN_NET_DEVICE_FOR_APCLI) % MAX_APCLI_NUM;
		NetDev = pAd->ApCfg.ApCliTab[IfIdx].wdev.if_dev;
	}
	else
#endif /* APCLI_SUPPORT */
#ifdef WDS_SUPPORT
	if (RTMP_GET_PACKET_NET_DEVICE(pPacket) >= MIN_NET_DEVICE_FOR_WDS)
	{
		IfIdx = (RTMP_GET_PACKET_NET_DEVICE(pPacket) - MIN_NET_DEVICE_FOR_WDS) % MAX_WDS_ENTRY;
		NetDev = pAd->WdsTab.WdsEntry[IfIdx].wdev.if_dev;
	}
	else
#endif /* WDS_SUPPORT */
	{
#ifdef MBSS_SUPPORT
		if (pAd->OpMode == OPMODE_AP)
		{
			IfIdx = (RTMP_GET_PACKET_NET_DEVICE(pPacket) - MIN_NET_DEVICE_FOR_MBSSID) % MAX_MBSSID_NUM(pAd);
			NetDev = pAd->ApCfg.MBSSID[IfIdx].wdev.if_dev;
		}
		else
		{
			IfIdx = MAIN_MBSSID;
			NetDev = pAd->net_dev;
		}
#else
		IfIdx = MAIN_MBSSID;
		NetDev = pAd->net_dev;
#endif /* MBSS_SUPPORT */
	}


	/* WMM support 4 software queues.*/
	/* One software queue full doesn't mean device have no capbility to transmit packet.*/
	/* So disable block Net-If queue function while WMM enable.*/
#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
		valid = (pAd->ApCfg.MBSSID[IfIdx].wdev.bWmmCapable == TRUE) ? FALSE : TRUE;
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
	{
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		valid = (pAd->CommonCfg.bWmmCapable == TRUE) ? FALSE : TRUE;
	}
#endif /* CONFIG_STA_SUPPORT */

	if (valid)
		blockNetIf(&pAd->blockQueueTab[QueIdx], NetDev);
	return;
}

#endif /* BLOCK_NET_IF */
