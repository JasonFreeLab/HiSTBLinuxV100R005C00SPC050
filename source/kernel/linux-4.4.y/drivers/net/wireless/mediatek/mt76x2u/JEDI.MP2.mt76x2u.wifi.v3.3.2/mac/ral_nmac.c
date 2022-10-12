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

INT rlt_get_rxwi_phymode(RXWI_STRUC *rxwi)
{
	return rxwi->RXWI_N.phy_mode;
}

INT rlt_get_rxwi_rssi(RXWI_STRUC *rxwi, INT size, CHAR *rssi)
{
	if (size < sizeof(rxwi->RXWI_N.rssi) / sizeof(UINT8))
		NdisMoveMemory(rssi, &rxwi->RXWI_N.rssi[0], size);

	return 0;
}

INT rlt_get_rxwi_snr(RTMP_ADAPTER *pAd, RXWI_STRUC *rxwi, INT size, UCHAR *snr)
{
	if (IS_MT76x2(pAd))
		NdisMoveMemory(snr, &rxwi->RXWI_N.bbp_rxinfo[2], size);
	/* TODO: shiang-6590, fix me for SNR info of RXWI!! */
	if (size < 3)
		NdisMoveMemory(snr, &rxwi->RXWI_N.bbp_rxinfo[0], size);

	return 0;
}


#ifdef RLT_MAC
VOID dumpRxFCEInfo(RTMP_ADAPTER *pAd, RXFCE_INFO *pRxFceInfo)
{
	hex_dump("RxFCEInfo Raw Data", (UCHAR *) pRxFceInfo, sizeof(RXFCE_INFO));

	DBGPRINT(RT_DEBUG_TRACE, ("RxFCEInfo Fields:\n"));

	DBGPRINT(RT_DEBUG_TRACE, ("\tinfo_type=%d\n", pRxFceInfo->info_type));
	DBGPRINT(RT_DEBUG_TRACE, ("\ts_port=%d\n", pRxFceInfo->s_port));
	DBGPRINT(RT_DEBUG_TRACE, ("\tqsel=%d\n", pRxFceInfo->qsel));
	DBGPRINT(RT_DEBUG_TRACE, ("\tpcie_intr=%d\n", pRxFceInfo->pcie_intr));
	DBGPRINT(RT_DEBUG_TRACE, ("\tmac_len=%d\n", pRxFceInfo->mac_len));
	DBGPRINT(RT_DEBUG_TRACE, ("\tl3l4_done=%d\n", pRxFceInfo->l3l4_done));
	DBGPRINT(RT_DEBUG_TRACE, ("\tpkt_80211=%d\n", pRxFceInfo->pkt_80211));
	DBGPRINT(RT_DEBUG_TRACE, ("\tip_err=%d\n", pRxFceInfo->ip_err));
	DBGPRINT(RT_DEBUG_TRACE, ("\ttcp_err=%d\n", pRxFceInfo->tcp_err));
	DBGPRINT(RT_DEBUG_TRACE, ("\tudp_err=%d\n", pRxFceInfo->udp_err));
	DBGPRINT(RT_DEBUG_TRACE, ("\tpkt_len=%d\n", pRxFceInfo->pkt_len));
}
#endif /* RLT_MAC */

static UCHAR *txwi_txop_str[] = { "HT_TXOP", "PIFS", "SIFS", "BACKOFF", "Invalid" };

#define TXWI_TXOP_STR(_x)	((_x) <= 3 ? txwi_txop_str[(_x)] : txwi_txop_str[4])

VOID dump_rlt_txwi(RTMP_ADAPTER *pAd, TXWI_STRUC *pTxWI)
{
	struct _TXWI_NMAC *txwi_nmac = (struct _TXWI_NMAC *)pTxWI;

	ASSERT((sizeof(struct _TXWI_NMAC) == pAd->chipCap.TXWISize));

	DBGPRINT(RT_DEBUG_TRACE,
		 ("\tPHYMODE=%d(%s)\n", txwi_nmac->PHYMODE, get_phymode_str(txwi_nmac->PHYMODE)));
	DBGPRINT(RT_DEBUG_TRACE, ("\tITxBf=%d\n", txwi_nmac->iTxBF));
	DBGPRINT(RT_DEBUG_TRACE, ("\tETxBf=%d\n", txwi_nmac->eTxBF));
	DBGPRINT(RT_DEBUG_TRACE, ("\tSounding=%d\n", txwi_nmac->Sounding));
	DBGPRINT(RT_DEBUG_TRACE, ("\tNDP Sounding BW=%d\n", txwi_nmac->NDPSndBW));
	DBGPRINT(RT_DEBUG_TRACE, ("\tNDP Sounding Rate=%d\n", txwi_nmac->NDPSndRate));
	DBGPRINT(RT_DEBUG_TRACE, ("\tSTBC=%d\n", txwi_nmac->STBC));
	DBGPRINT(RT_DEBUG_TRACE, ("\tShortGI=%d\n", txwi_nmac->ShortGI));
	DBGPRINT(RT_DEBUG_TRACE, ("\tBW=%d(%sMHz)\n", txwi_nmac->BW, get_bw_str(txwi_nmac->BW)));
	DBGPRINT(RT_DEBUG_TRACE, ("\tMCS=%d\n", txwi_nmac->MCS));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("\tTxOP=%d(%s)\n", txwi_nmac->txop, TXWI_TXOP_STR(txwi_nmac->txop)));
	DBGPRINT(RT_DEBUG_TRACE, ("\tMpduDensity=%d\n", txwi_nmac->MpduDensity));
	DBGPRINT(RT_DEBUG_TRACE, ("\tAMPDU=%d\n", txwi_nmac->AMPDU));
	DBGPRINT(RT_DEBUG_TRACE, ("\tTS=%d\n", txwi_nmac->TS));
	DBGPRINT(RT_DEBUG_TRACE, ("\tCF-ACK=%d\n", txwi_nmac->CFACK));
	DBGPRINT(RT_DEBUG_TRACE, ("\tMIMO-PS=%d\n", txwi_nmac->MIMOps));
	DBGPRINT(RT_DEBUG_TRACE, ("\tNSEQ=%d\n", txwi_nmac->NSEQ));
	DBGPRINT(RT_DEBUG_TRACE, ("\tACK=%d\n", txwi_nmac->ACK));
	DBGPRINT(RT_DEBUG_TRACE, ("\tFRAG=%d\n", txwi_nmac->FRAG));
	DBGPRINT(RT_DEBUG_TRACE, ("\tWCID=%d\n", txwi_nmac->wcid));
	DBGPRINT(RT_DEBUG_TRACE, ("\tBAWinSize=%d\n", txwi_nmac->BAWinSize));
	DBGPRINT(RT_DEBUG_TRACE, ("\tMPDUtotalByteCnt=%d\n", txwi_nmac->MPDUtotalByteCnt));
	DBGPRINT(RT_DEBUG_TRACE, ("\tPID=%d\n", txwi_nmac->TxPktId));
}

VOID dump_rlt_rxwi(RTMP_ADAPTER *pAd, RXWI_STRUC *pRxWI)
{
	struct _RXWI_NMAC *rxwi_n = (struct _RXWI_NMAC *)pRxWI;

	ASSERT((sizeof(struct _RXWI_NMAC) == pAd->chipCap.RXWISize));

	DBGPRINT(RT_DEBUG_TRACE, ("\tWCID=%d\n", rxwi_n->wcid));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("\tPhyMode=%d(%s)\n", rxwi_n->phy_mode, get_phymode_str(rxwi_n->phy_mode)));

	if (rxwi_n->phy_mode == MODE_VHT)
		DBGPRINT(RT_DEBUG_TRACE, ("\tMCS=%d(Nss:%d, MCS:%d)\n",
					  rxwi_n->mcs, (rxwi_n->mcs >> 4), (rxwi_n->mcs & 0xf)));
	else
		DBGPRINT(RT_DEBUG_TRACE, ("\tMCS=%d\n", rxwi_n->mcs));

	DBGPRINT(RT_DEBUG_TRACE, ("\tBW=%d\n", rxwi_n->bw));
	DBGPRINT(RT_DEBUG_TRACE, ("\tSGI=%d\n", rxwi_n->sgi));
	DBGPRINT(RT_DEBUG_TRACE, ("\tMPDUtotalByteCnt=%d\n", rxwi_n->MPDUtotalByteCnt));
	DBGPRINT(RT_DEBUG_TRACE, ("\tTID=%d\n", rxwi_n->tid));
	DBGPRINT(RT_DEBUG_TRACE, ("\tSTBC=%d\n", rxwi_n->stbc));
	DBGPRINT(RT_DEBUG_TRACE, ("\tkey_idx=%d\n", rxwi_n->key_idx));
	DBGPRINT(RT_DEBUG_TRACE, ("\tBSS_IDX=%d\n", rxwi_n->bss_idx));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("\tRSSI=%d:%d:%d!\n", (CHAR) (rxwi_n->rssi[0]), (CHAR) (rxwi_n->rssi[1]),
		  (CHAR) (rxwi_n->rssi[2])));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("\tSNR=%d:%d:%d!\n", (CHAR) rxwi_n->bbp_rxinfo[0], (CHAR) rxwi_n->bbp_rxinfo[1],
		  (CHAR) rxwi_n->bbp_rxinfo[2]));
	DBGPRINT(RT_DEBUG_TRACE, ("\tFreqOffset=%d!\n", (CHAR) rxwi_n->bbp_rxinfo[4]));
}

static UCHAR *txinfo_type_str[] = { "PKT", "", "CMD", "RSV", "Invalid" };
static UCHAR *txinfo_d_port_str[] = {
	"WLAN", "CPU_RX", "CPU_TX", "HOST", "VIRT_RX", "VIRT_TX", "DROP", "Invalid" };
static UCHAR *txinfo_que_str[] = { "MGMT", "HCCA", "EDCA_1", "EDCA_2", "Invalid" };

#define TXINFO_TYPE_STR(_x)	((_x) <= 3 ?  txinfo_type_str[_x] : txinfo_type_str[4])
#define TXINFO_DPORT_STR(_x)	((_x) <= 6 ? txinfo_d_port_str[_x] : txinfo_d_port_str[7])
#define TXINFO_QUE_STR(_x)		((_x) <= 3 ? txinfo_que_str[_x] : txinfo_que_str[4])

VOID dump_rlt_txinfo(RTMP_ADAPTER *pAd, TXINFO_STRUC *pTxInfo)
{
	struct _TXINFO_NMAC_PKT *pkt_txinfo = (struct _TXINFO_NMAC_PKT *)pTxInfo;

	DBGPRINT(RT_DEBUG_TRACE,
		 ("\tInfo_Type=%d(%s)\n", pkt_txinfo->info_type,
		  TXINFO_TYPE_STR(pkt_txinfo->info_type)));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("\td_port=%d(%s)\n", pkt_txinfo->d_port, TXINFO_DPORT_STR(pkt_txinfo->d_port)));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("\tQSEL=%d(%s)\n", pkt_txinfo->QSEL, TXINFO_QUE_STR(pkt_txinfo->QSEL)));
	DBGPRINT(RT_DEBUG_TRACE, ("\tWIV=%d\n", pkt_txinfo->wiv));
	DBGPRINT(RT_DEBUG_TRACE, ("\t802.11=%d\n", pkt_txinfo->pkt_80211));
	DBGPRINT(RT_DEBUG_TRACE, ("\tcso=%d\n", pkt_txinfo->cso));
	DBGPRINT(RT_DEBUG_TRACE, ("\ttso=%d\n", pkt_txinfo->tso));
	DBGPRINT(RT_DEBUG_TRACE, ("\tpkt_len=0x%x\n", pkt_txinfo->pkt_len));
}


static UINT32 asic_set_wlan_func(RTMP_ADAPTER *pAd, BOOLEAN enable)
{
	UINT32 reg;

	RTMP_IO_FORCE_READ32(pAd, WLAN_FUN_CTRL, &reg);

	if (enable == TRUE) {
		/*
		   Enable WLAN function and clock
		   WLAN_FUN_CTRL[1:0] = 0x3
		 */
		reg |= WLAN_FUN_CTRL_WLAN_CLK_EN;
		reg |= WLAN_FUN_CTRL_WLAN_EN;
	} else {
		/*
		   Diable WLAN function and clock
		   WLAN_FUN_CTRL[1:0] = 0x0
		 */
		if (IS_PCIE_INF(pAd))
			reg &= ~WLAN_FUN_CTRL_PCIE_APP0_CLK_REQ;

		reg &= ~WLAN_FUN_CTRL_WLAN_EN;
		reg &= ~WLAN_FUN_CTRL_WLAN_CLK_EN;
	}

	DBGPRINT(RT_DEBUG_TRACE, ("WlanFunCtrl= 0x%x\n", reg));
	RTMP_IO_FORCE_WRITE32(pAd, WLAN_FUN_CTRL, reg);
	RtmpusecDelay(20);

	return reg;
}

#define MAX_CHECK_COUNT 200

INT rlt_wlan_chip_onoff(RTMP_ADAPTER *pAd, BOOLEAN bOn, BOOLEAN bResetWLAN)
{
	UINT32 reg = 0;

#ifdef RTMP_FLASH_SUPPORT
#endif /* RTMP_FLASH_SUPPORT */


#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		UINT32 ret;

		RTMP_SEM_EVENT_WAIT(&pAd->hw_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RTMP_MAC_USB */

	RTMP_IO_FORCE_READ32(pAd, WLAN_FUN_CTRL, &reg);
	DBGPRINT(RT_DEBUG_OFF,
		 ("==>%s(): OnOff:%d, Reset= %d, pAd->WlanFunCtrl:0x%x, Reg-WlanFunCtrl=0x%x\n",
		  __func__, bOn, bResetWLAN, pAd->WlanFunCtrl.word, reg));

	if (bResetWLAN == TRUE) {
#ifdef MT76x2
		if (!IS_MT76x2(pAd))
#endif /* MT76x2 */
			reg &= ~WLAN_FUN_CTRL_GPIO0_OUT_OE_N_MASK;

		reg &= ~WLAN_FUN_CTRL_FRC_WL_ANT_SEL;

		if (pAd->WlanFunCtrl.field.WLAN_EN) {
			/*
			   Restore all HW default value and reset RF.
			 */
#ifdef MT76x2
			if (!IS_MT76x2(pAd))
#endif /* MT76x2 */
				reg |= WLAN_FUN_CTRL_WLAN_RESET;

			reg |= WLAN_FUN_CTRL_WLAN_RESET_RF;
			DBGPRINT(RT_DEBUG_TRACE, ("Reset(1) WlanFunCtrl.word = 0x%x\n", reg));
			RTMP_IO_FORCE_WRITE32(pAd, WLAN_FUN_CTRL, reg);
			RtmpusecDelay(20);

#ifdef MT76x2
			if (!IS_MT76x2(pAd))
#endif /* MT76x2 */
				reg &= ~WLAN_FUN_CTRL_WLAN_RESET;

			reg &= ~WLAN_FUN_CTRL_WLAN_RESET_RF;

			DBGPRINT(RT_DEBUG_TRACE, ("Reset(2) WlanFunCtrl.word = 0x%x\n", reg));
			RTMP_IO_FORCE_WRITE32(pAd, WLAN_FUN_CTRL, reg);
			RtmpusecDelay(20);
		} else
			RTMP_IO_FORCE_WRITE32(pAd, WLAN_FUN_CTRL, reg);
	}

	reg = asic_set_wlan_func(pAd, bOn);

	if (bOn) {
		RTMP_IO_FORCE_READ32(pAd, MAC_CSR0, &pAd->MACVersion);
		DBGPRINT(RT_DEBUG_TRACE, ("MACVersion = 0x%08x\n", pAd->MACVersion));
	}

	if (bOn == TRUE
#ifdef MT76x2
	    && (!IS_MT76x2(pAd))
#endif /* MT76x2 */
	    ) {
		UINT index = 0;
		u32 value;

		do {
			do {
				RTMP_IO_FORCE_READ32(pAd, CMB_CTRL, &value);

				/*
				   Check status of PLL_LD & XTAL_RDY.
				   HW issue: Must check PLL_LD&XTAL_RDY when setting EEP to disable PLL power down
				 */
				if (((value & CMB_CTRL_PLL_LD) == CMB_CTRL_PLL_LD) &&
				    ((value & CMB_CTRL_XTAL_RDY) == CMB_CTRL_XTAL_RDY))
					break;

				RtmpusecDelay(20);
			} while (index++ < MAX_CHECK_COUNT);

			if (index >= MAX_CHECK_COUNT) {
				DBGPRINT(RT_DEBUG_ERROR,
					 ("Lenny:[boundary]Check PLL_LD ..CMB_CTRL 0x%08x, index=%d!\n",
					  value, index));
				/*
				   Disable WLAN then enable WLAN again
				 */
				reg = asic_set_wlan_func(pAd, 0);
				reg = asic_set_wlan_func(pAd, 1);

				index = 0;
			} else {
				break;
			}
		} while (TRUE);
	}

	pAd->WlanFunCtrl.word = reg;
	RTMP_IO_FORCE_READ32(pAd, WLAN_FUN_CTRL, &reg);
	DBGPRINT(RT_DEBUG_TRACE,
		 ("<== %s():pAd->WlanFunCtrl.word = 0x%x, Reg->WlanFunCtrl=0x%x!\n",
		  __func__, pAd->WlanFunCtrl.word, reg));


#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd))
		RTMP_SEM_EVENT_UP(&pAd->hw_atomic);
#endif /* RTMP_MAC_USB */

	return 0;
}
