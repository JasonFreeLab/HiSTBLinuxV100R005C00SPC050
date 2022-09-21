/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#define _RTL8812AE_XMIT_C_

/* #include <drv_types.h> */
#include <rtl8812a_hal.h>


s32	rtl8812ae_init_xmit_priv(_adapter *padapter)
{
	s32	ret = _SUCCESS;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);

	_rtw_spinlock_init(&pdvobjpriv->irq_th_lock);

#ifdef PLATFORM_LINUX
	tasklet_init(&pxmitpriv->xmit_tasklet,
		     (void(*)(unsigned long))rtl8812ae_xmit_tasklet,
		     (unsigned long)padapter);
#endif

	return ret;
}

void	rtl8812ae_free_xmit_priv(_adapter *padapter)
{
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);

	_rtw_spinlock_free(&pdvobjpriv->irq_th_lock);
}

s32 rtl8812ae_enqueue_xmitbuf(struct rtw_tx_ring	*ring, struct xmit_buf *pxmitbuf)
{
	_irqL irqL;
	_queue *ppending_queue = &ring->queue;


	/* RTW_INFO("+enqueue_xmitbuf\n"); */

	if (pxmitbuf == NULL)
		return _FAIL;

	/* _enter_critical(&ppending_queue->lock, &irqL); */

	rtw_list_delete(&pxmitbuf->list);

	rtw_list_insert_tail(&(pxmitbuf->list), get_list_head(ppending_queue));

	ring->qlen++;

	/* RTW_INFO("FREE, free_xmitbuf_cnt=%d\n", pxmitpriv->free_xmitbuf_cnt); */

	/* _exit_critical(&ppending_queue->lock, &irqL);	 */


	return _SUCCESS;
}

struct xmit_buf *rtl8812ae_dequeue_xmitbuf(struct rtw_tx_ring	*ring)
{
	_irqL irqL;
	_list *plist, *phead;
	struct xmit_buf *pxmitbuf =  NULL;
	_queue *ppending_queue = &ring->queue;


	/* _enter_critical(&ppending_queue->lock, &irqL); */

	if (_rtw_queue_empty(ppending_queue) == _TRUE)
		pxmitbuf = NULL;
	else {

		phead = get_list_head(ppending_queue);

		plist = get_next(phead);

		pxmitbuf = LIST_CONTAINOR(plist, struct xmit_buf, list);

		rtw_list_delete(&(pxmitbuf->list));

		ring->qlen--;
	}

	/* _exit_critical(&ppending_queue->lock, &irqL);	 */


	return pxmitbuf;
}

static u16 ffaddr2dma(u32 addr)
{
	u16	dma_ctrl;
	switch (addr) {
	case VO_QUEUE_INX:
		dma_ctrl = BIT3;
		break;
	case VI_QUEUE_INX:
		dma_ctrl = BIT2;
		break;
	case BE_QUEUE_INX:
		dma_ctrl = BIT1;
		break;
	case BK_QUEUE_INX:
		dma_ctrl = BIT0;
		break;
	case BCN_QUEUE_INX:
		dma_ctrl = BIT4;
		break;
	case MGT_QUEUE_INX:
		dma_ctrl = BIT6;
		break;
	case HIGH_QUEUE_INX:
		dma_ctrl = BIT7;
		break;
	default:
		dma_ctrl = 0;
		break;
	}

	return dma_ctrl;
}

static s32 update_txdesc(struct xmit_frame *pxmitframe, u8 *pmem, s32 sz)
{
	uint	qsel;
	u8 data_rate, pwr_status;
	dma_addr_t	mapping;
	_adapter			*padapter = pxmitframe->padapter;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;
	struct dvobj_priv		*pdvobjpriv = adapter_to_dvobj(padapter);
	struct pkt_attrib	*pattrib = &pxmitframe->attrib;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	u8	*ptxdesc =  pmem;
	sint	bmcst = IS_MCAST(pattrib->ra);

	mapping = pci_map_single(pdvobjpriv->ppcidev, pxmitframe->buf_addr , sz, PCI_DMA_TODEVICE);

	_rtw_memset(ptxdesc, 0, TX_DESC_NEXT_DESC_OFFSET);

	/* 4 offset 0 */
	SET_TX_DESC_FIRST_SEG_8812(ptxdesc, 1);
	SET_TX_DESC_LAST_SEG_8812(ptxdesc, 1);
	/* SET_TX_DESC_OWN_8812(ptxdesc, 1); */

	SET_TX_DESC_PKT_SIZE_8812(ptxdesc, sz);

	SET_TX_DESC_OFFSET_8812(ptxdesc, TXDESC_SIZE);

#ifdef CONFIG_TX_EARLY_MODE
	SET_TX_DESC_PKT_OFFSET_8812(ptxdesc, 1);
	SET_TX_DESC_OFFSET_8812(ptxdesc, TXDESC_SIZE + EARLY_MODE_INFO_SIZE);
#endif

	if (bmcst)
		SET_TX_DESC_BMC_8812(ptxdesc, 1);

	SET_TX_DESC_MACID_8812(ptxdesc, pattrib->mac_id);
	SET_TX_DESC_RATE_ID_8812(ptxdesc, pattrib->raid);

	SET_TX_DESC_QUEUE_SEL_8812(ptxdesc,  pattrib->qsel);

	if (!pattrib->qos_en) {
		SET_TX_DESC_HWSEQ_EN_8812(ptxdesc, 1); /* Hw set sequence number */
	} else
		SET_TX_DESC_SEQ_8812(ptxdesc, pattrib->seqnum);

	if ((pxmitframe->frame_tag & 0x0f) == DATA_FRAMETAG) {
		/* RTW_INFO("pxmitframe->frame_tag == DATA_FRAMETAG\n");		 */

		rtl8812a_fill_txdesc_sectype(pattrib, ptxdesc);
#if defined(CONFIG_CONCURRENT_MODE)
		if (bmcst)
			fill_txdesc_force_bmc_camid(pattrib, ptxdesc);
#endif

		rtl8812a_fill_txdesc_vcs(padapter, pattrib, ptxdesc);

		if ((pattrib->ether_type != 0x888e) &&
		    (pattrib->ether_type != 0x0806) &&
		    (pattrib->ether_type != 0x88b4) &&
		    (pattrib->dhcp_pkt != 1)
#ifdef CONFIG_AUTO_AP_MODE
		    && (pattrib->pctrl != _TRUE)
#endif
		   ) {
			/* Non EAP & ARP & DHCP type data packet */

			if (pattrib->ampdu_en == _TRUE) {
				SET_TX_DESC_AGG_ENABLE_8812(ptxdesc, 1);
				SET_TX_DESC_MAX_AGG_NUM_8812(ptxdesc, 0x1f);
				/* Set A-MPDU aggregation. */
				SET_TX_DESC_AMPDU_DENSITY_8812(ptxdesc, pattrib->ampdu_spacing);
			} else
				SET_TX_DESC_AGG_BREAK_8812(ptxdesc, 1);

			rtl8812a_fill_txdesc_phy(padapter, pattrib, ptxdesc);

			/* DATA  Rate FB LMT */
			SET_TX_DESC_DATA_RATE_FB_LIMIT_8812(ptxdesc, 0x1f);

			if (pHalData->fw_ractrl == _FALSE) {
				SET_TX_DESC_USE_RATE_8812(ptxdesc, 1);

				if (pHalData->INIDATA_RATE[pattrib->mac_id] & BIT(7))
					SET_TX_DESC_DATA_SHORT_8812(ptxdesc,	1);

				SET_TX_DESC_TX_RATE_8812(ptxdesc, (pHalData->INIDATA_RATE[pattrib->mac_id] & 0x7F));
			}

			if (padapter->fix_rate != 0xFF) { /* modify data rate by iwpriv */
				SET_TX_DESC_USE_RATE_8812(ptxdesc, 1);
				if (padapter->fix_rate & BIT(7))
					SET_TX_DESC_DATA_SHORT_8812(ptxdesc,	1);

				SET_TX_DESC_TX_RATE_8812(ptxdesc, (padapter->fix_rate & 0x7F));
				if (!padapter->data_fb)
					SET_TX_DESC_DISABLE_FB_8812(ptxdesc, 1);
			}

			if (pattrib->ldpc)
				SET_TX_DESC_DATA_LDPC_8812(ptxdesc, 1);
			if (pattrib->stbc)
				SET_TX_DESC_DATA_STBC_8812(ptxdesc, 1);
		} else {
			/* EAP data packet and ARP packet and DHCP. */
			/* Use the 1M data rate to send the EAP/ARP packet. */
			/* This will maybe make the handshake smooth. */

			SET_TX_DESC_USE_RATE_8812(ptxdesc, 1);

			SET_TX_DESC_AGG_BREAK_8812(ptxdesc, 1);

			/* HW will ignore this setting if the transmission rate is legacy OFDM. */
			if (pmlmeinfo->preamble_mode == PREAMBLE_SHORT)
				SET_TX_DESC_DATA_SHORT_8812(ptxdesc, 1);

			SET_TX_DESC_TX_RATE_8812(ptxdesc, MRateToHwRate(pmlmeext->tx_rate));
		}

#ifdef CONFIG_TDLS
#ifdef CONFIG_XMIT_ACK
		/* CCX-TXRPT ack for xmit mgmt frames. */
		if (pxmitframe->ack_report) {
			SET_TX_DESC_SPE_RPT_8812(ptxdesc, 1);
#ifdef DBG_CCX
			RTW_INFO("%s set tx report\n", __func__);
#endif
		}
#endif /* CONFIG_XMIT_ACK */
#endif
	} else if ((pxmitframe->frame_tag & 0x0f) == MGNT_FRAMETAG) {
		/* RTW_INFO("pxmitframe->frame_tag == MGNT_FRAMETAG\n");	 */

		if (IS_HARDWARE_TYPE_8821(padapter))
			SET_TX_DESC_MBSSID_8821(ptxdesc, pattrib->mbssid);

#ifdef CONFIG_BEAMFORMING
		if ((pattrib->subtype == WIFI_NDPA) || ((pattrib->subtype == WIFI_ACTION_NOACK) && (pattrib->order == 1))) {
			SET_TX_DESC_NAV_USE_HDR_8812(ptxdesc, 1);
			SET_TX_DESC_DATA_BW_8812(ptxdesc, BWMapping_8812(padapter, pattrib));
			SET_TX_DESC_RTS_SC_8812(ptxdesc, SCMapping_8812(padapter, pattrib));

			SET_TX_DESC_RETRY_LIMIT_ENABLE_8812(ptxdesc, 1);
			SET_TX_DESC_DATA_RETRY_LIMIT_8812(ptxdesc, 5);
			SET_TX_DESC_DISABLE_FB_8812(ptxdesc, 1);
			SET_TX_DESC_NDPA_8812(ptxdesc, 1);
		} else
#endif
		{
			/*offset 20*/
			SET_TX_DESC_RETRY_LIMIT_ENABLE_8812(ptxdesc, 1);
			if (pattrib->retry_ctrl == _TRUE)
				SET_TX_DESC_DATA_RETRY_LIMIT_8812(ptxdesc, 6);
			else
				SET_TX_DESC_DATA_RETRY_LIMIT_8812(ptxdesc, 12);
		}
		SET_TX_DESC_USE_RATE_8812(ptxdesc, 1);

#ifdef CONFIG_INTEL_PROXIM
		if ((padapter->proximity.proxim_on == _TRUE) && (pattrib->intel_proxim == _TRUE)) {
			RTW_INFO("\n %s pattrib->rate=%d\n", __FUNCTION__, pattrib->rate);
			SET_TX_DESC_TX_RATE_8812(ptxdesc, pattrib->rate);
		} else
#endif
		{
			SET_TX_DESC_TX_RATE_8812(ptxdesc, MRateToHwRate(pattrib->rate));
		}

#ifdef CONFIG_XMIT_ACK
		/* CCX-TXRPT ack for xmit mgmt frames. */
		if (pxmitframe->ack_report) {
			SET_TX_DESC_SPE_RPT_8812(ptxdesc, 1);
#ifdef DBG_CCX
			RTW_INFO("%s set tx report\n", __func__);
#endif
		}
#endif /* CONFIG_XMIT_ACK */
	} else if ((pxmitframe->frame_tag & 0x0f) == TXAGG_FRAMETAG)
		RTW_INFO("pxmitframe->frame_tag == TXAGG_FRAMETAG\n");
#ifdef CONFIG_MP_INCLUDED
	else if (((pxmitframe->frame_tag & 0x0f) == MP_FRAMETAG) &&
		 (padapter->registrypriv.mp_mode == 1))
		fill_txdesc_for_mp(padapter, ptxdesc);
#endif
	else {
		RTW_INFO("pxmitframe->frame_tag = %d\n", pxmitframe->frame_tag);

		SET_TX_DESC_USE_RATE_8812(ptxdesc, 1);
		SET_TX_DESC_TX_RATE_8812(ptxdesc, MRateToHwRate(pmlmeext->tx_rate));
	}

#ifdef CONFIG_ANTENNA_DIVERSITY
	ODM_SetTxAntByTxInfo(&pHalData->odmpriv, ptxdesc, pxmitframe->attrib.mac_id);
#endif

#ifdef CONFIG_BEAMFORMING
	SET_TX_DESC_GID_8812(ptxdesc, pattrib->txbf_g_id);
	SET_TX_DESC_PAID_8812(ptxdesc, pattrib->txbf_p_aid);
#endif

	SET_TX_DESC_TX_BUFFER_SIZE_8812(ptxdesc, sz);
	SET_TX_DESC_TX_BUFFER_ADDRESS_8812(ptxdesc, mapping);

	_dbg_dump_tx_info(padapter, pxmitframe->frame_tag, ptxdesc);
	return 0;
}

static u8 *get_txdesc(_adapter *padapter, u8 queue_index)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct rtw_tx_ring	*ring;
	u8	*pdesc = NULL;
	int	idx;

	ring = &pxmitpriv->tx_ring[queue_index];
	if (queue_index != BCN_QUEUE_INX)
		idx = (ring->idx + ring->qlen) % ring->entries;
	else
		idx = 0;

	pdesc = (u8 *)&ring->desc[idx];
	if ((GET_TX_DESC_OWN_8812(pdesc)) && (queue_index != BCN_QUEUE_INX)) {
		RTW_INFO("No more TX desc@%d, ring->idx = %d,idx = %d\n", queue_index, ring->idx, idx);
		return NULL;
	}

	return pdesc;
}

s32 rtw_dump_xframe(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	s32 ret = _SUCCESS;
	s32 inner_ret = _SUCCESS;
	_irqL irqL;
	int	t, sz, w_sz, pull = 0;
	u32	ff_hwaddr;
	struct xmit_buf		*pxmitbuf = pxmitframe->pxmitbuf;
	struct pkt_attrib		*pattrib = &pxmitframe->attrib;
	struct xmit_priv		*pxmitpriv = &padapter->xmitpriv;
	struct dvobj_priv		*pdvobjpriv = adapter_to_dvobj(padapter);
	struct security_priv		*psecuritypriv = &padapter->securitypriv;
	u8					*ptxdesc;
	struct rtw_tx_ring		*ptx_ring = GET_PRIMARY_ADAPTER(padapter)->xmitpriv.tx_ring;

	if ((pxmitframe->frame_tag == DATA_FRAMETAG) &&
	    (pxmitframe->attrib.ether_type != 0x0806) &&
	    (pxmitframe->attrib.ether_type != 0x888e) &&
	    (pxmitframe->attrib.dhcp_pkt != 1))
		rtw_issue_addbareq_cmd(padapter, pxmitframe);

	/* mem_addr = pxmitframe->buf_addr; */


	for (t = 0; t < pattrib->nr_frags; t++) {
		if (inner_ret != _SUCCESS && ret == _SUCCESS)
			ret = _FAIL;

		if (t != (pattrib->nr_frags - 1)) {

			sz = pxmitpriv->frag_len;
			sz = sz - 4 - (psecuritypriv->sw_encrypt ? 0 : pattrib->icv_len);
		} else /* no frag */
			sz = pattrib->last_txcmdsz;

		ff_hwaddr = rtw_get_ff_hwaddr(pxmitframe);

		_enter_critical(&pdvobjpriv->irq_th_lock, &irqL);
		ptxdesc = get_txdesc(GET_PRIMARY_ADAPTER(padapter), ff_hwaddr);

		if (BCN_QUEUE_INX == ff_hwaddr)
			padapter->xmitpriv.beaconDMAing = _TRUE;

		if (ptxdesc == NULL) {
			_exit_critical(&pdvobjpriv->irq_th_lock, &irqL);
			rtw_sctx_done_err(&pxmitbuf->sctx, RTW_SCTX_DONE_TX_DESC_NA);
			rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
			RTW_INFO("##### Tx desc unavailable !#####\n");
			break;
		}
		update_txdesc(pxmitframe, ptxdesc, sz);

		if (pxmitbuf->buf_tag != XMITBUF_CMD)
			rtl8812ae_enqueue_xmitbuf(&ptx_ring[ff_hwaddr], pxmitbuf);

		pxmitbuf->len = sz;
		w_sz = sz;

		wmb();
		SET_TX_DESC_OWN_8812(ptxdesc, 1);

		_exit_critical(&pdvobjpriv->irq_th_lock, &irqL);
		rtw_write16(padapter, REG_PCIE_CTRL_REG, ffaddr2dma(ff_hwaddr));
		inner_ret = rtw_write_port(padapter, ff_hwaddr, w_sz, (unsigned char *)pxmitbuf);

		rtw_count_tx_stats(padapter, pxmitframe, sz);
		/* RTW_INFO("rtw_write_port, w_sz=%d, sz=%d, txdesc_sz=%d, tid=%d\n", w_sz, sz, w_sz-sz, pattrib->priority);       */

		/* mem_addr += w_sz; */

		/* mem_addr = (u8 *)RND4(((SIZE_PTR)(mem_addr))); */

	}

	rtw_free_xmitframe(pxmitpriv, pxmitframe);

	if (ret != _SUCCESS)
		rtw_sctx_done_err(&pxmitbuf->sctx, RTW_SCTX_DONE_UNKNOWN);

	return ret;
}
static u8 check_nic_enough_desc(_adapter *padapter, struct pkt_attrib *pattrib)
{
	u32 prio;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct rtw_tx_ring	*ring;

	switch (pattrib->qsel) {
	case 0:
	case 3:
		prio = BE_QUEUE_INX;
		break;
	case 1:
	case 2:
		prio = BK_QUEUE_INX;
		break;
	case 4:
	case 5:
		prio = VI_QUEUE_INX;
		break;
	case 6:
	case 7:
		prio = VO_QUEUE_INX;
		break;
	default:
		prio = BE_QUEUE_INX;
		break;
	}

	ring = &pxmitpriv->tx_ring[prio];

	/* for now we reserve two free descriptor as a safety boundary */
	/* between the tail and the head */
	/*  */
	if ((ring->entries - ring->qlen) >= 2)
		return _TRUE;
	else {
		/* RTW_INFO("do not have enough desc for Tx\n"); */
		return _FALSE;
	}
}

#ifdef CONFIG_XMIT_THREAD_MODE
/*
 * Description
 *	Transmit xmitbuf to hardware tx fifo
 *
 * Return
 *	_SUCCESS	ok
 *	_FAIL		something error
 */
s32 rtl8812ae_xmit_buf_handler(_adapter *padapter)
{
	PHAL_DATA_TYPE phal;
	struct xmit_priv *pxmitpriv;
	struct xmit_buf *pxmitbuf;
	struct xmit_frame *pxmitframe;
	s32 ret;

	phal = GET_HAL_DATA(padapter);
	pxmitpriv = &padapter->xmitpriv;

	ret = _rtw_down_sema(&pxmitpriv->xmit_sema);
	
	if (_FAIL == ret) {
		RT_TRACE(_module_hal_xmit_c_, _drv_emerg_,
				("%s: down XmitBufSema fail!\n", __FUNCTION__));
		return _FAIL;
	}

	if (RTW_CANNOT_RUN(padapter)) {
		RT_TRACE(_module_hal_xmit_c_, _drv_notice_
				, ("%s: bDriverStopped(%s) bSurpriseRemoved(%s)!\n"
				, __func__
				, rtw_is_drv_stopped(padapter)?"True":"False"
				, rtw_is_surprise_removed(padapter)?"True":"False"));
		return _FAIL;
	}

	if(check_pending_xmitbuf(pxmitpriv) == _FALSE)
		return _SUCCESS;

#ifdef CONFIG_LPS_LCLK
	ret = rtw_register_tx_alive(padapter);
	if (ret != _SUCCESS) {
		RT_TRACE(_module_hal_xmit_c_, _drv_notice_,
				 ("%s: wait to leave LPS_LCLK\n", __FUNCTION__));
		return _SUCCESS;
	}
#endif

	do {
		pxmitbuf = select_and_dequeue_pending_xmitbuf(padapter);
		
		if (pxmitbuf == NULL) 
			break;
		pxmitframe = (struct xmit_frame *)pxmitbuf->priv_data;

		if(check_nic_enough_desc(padapter, &pxmitframe->attrib)==_FALSE)
		{
			enqueue_pending_xmitbuf_to_head(pxmitpriv, pxmitbuf);
			break;
		}
		rtw_dump_xframe(padapter, pxmitframe);
	} while (1);


	return _SUCCESS;
}
#endif
void rtl8812ae_xmitframe_resume(_adapter *padapter)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct xmit_frame *pxmitframe = NULL;
	struct xmit_buf	*pxmitbuf = NULL;
	int res = _SUCCESS, xcnt = 0;


	while (1) {
		if (RTW_CANNOT_RUN(padapter)) {
			RTW_INFO("rtl8188ee_xmitframe_resume => bDriverStopped or bSurpriseRemoved\n");
			break;
		}

	#ifndef CONFIG_XMIT_THREAD_MODE
		if (rtw_xmit_ac_blocked(padapter) == _TRUE)
			break;
	#endif

		pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
		if (!pxmitbuf)
			break;

		pxmitframe =  rtw_dequeue_xframe(pxmitpriv, pxmitpriv->hwxmits, pxmitpriv->hwxmit_entry);

		if (pxmitframe) {
			pxmitframe->pxmitbuf = pxmitbuf;

			pxmitframe->buf_addr = pxmitbuf->pbuf;

			pxmitbuf->priv_data = pxmitframe;

			if ((pxmitframe->frame_tag & 0x0f) == DATA_FRAMETAG) {
				if (pxmitframe->attrib.priority <= 15) /* TID0~15 */
					res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);

				rtw_os_xmit_complete(padapter, pxmitframe);/* always return ndis_packet after rtw_xmitframe_coalesce			 */
			}


			if (res == _SUCCESS)
			#ifdef CONFIG_XMIT_THREAD_MODE
				enqueue_pending_xmitbuf(pxmitpriv,pxmitframe->pxmitbuf);
			#else
				rtw_dump_xframe(padapter, pxmitframe);
			#endif
			else {
				rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
				rtw_free_xmitframe(pxmitpriv, pxmitframe);
			}

			xcnt++;
		} else {
			rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
			break;
		}
	}
}


static s32 xmitframe_direct(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	s32 res = _SUCCESS;
#ifdef CONFIG_XMIT_THREAD_MODE
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
#endif

	res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
	if (res == _SUCCESS)
	{
	#ifdef CONFIG_XMIT_THREAD_MODE
		enqueue_pending_xmitbuf(pxmitpriv,pxmitframe->pxmitbuf);
	#else
		rtw_dump_xframe(padapter, pxmitframe);
	#endif

	}
	return res;
}

/*
 * Return
 *	_TRUE	dump packet directly
 *	_FALSE	enqueue packet
 */
static s32 pre_xmitframe(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	_irqL irqL;
	s32 res;
	struct xmit_buf *pxmitbuf = NULL;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	struct pkt_attrib *pattrib = &pxmitframe->attrib;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	_enter_critical_bh(&pxmitpriv->lock, &irqL);

	if ((rtw_txframes_sta_ac_pending(padapter, pattrib) > 0))
		goto enqueue;
	
#ifndef CONFIG_XMIT_THREAD_MODE
	if (check_nic_enough_desc(padapter, pattrib) == _FALSE)
		goto enqueue;

	if (rtw_xmit_ac_blocked(padapter) == _TRUE)
		goto enqueue;
#endif

	if (padapter->dvobj->iface_state.lg_sta_num)
		goto enqueue;

	pxmitbuf = rtw_alloc_xmitbuf(pxmitpriv);
	if (pxmitbuf == NULL)
		goto enqueue;

	_exit_critical_bh(&pxmitpriv->lock, &irqL);

	pxmitframe->pxmitbuf = pxmitbuf;
	pxmitframe->buf_addr = pxmitbuf->pbuf;
	pxmitbuf->priv_data = pxmitframe;

	if (xmitframe_direct(padapter, pxmitframe) != _SUCCESS) {
		rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
		rtw_free_xmitframe(pxmitpriv, pxmitframe);
	}

	return _TRUE;

enqueue:
	res = rtw_xmitframe_enqueue(padapter, pxmitframe);
	_exit_critical_bh(&pxmitpriv->lock, &irqL);

	if (res != _SUCCESS) {
		rtw_free_xmitframe(pxmitpriv, pxmitframe);

		pxmitpriv->tx_drop++;
		return _TRUE;
	}

	return _FALSE;
}

s32 rtl8812ae_mgnt_xmit(_adapter *padapter, struct xmit_frame *pmgntframe)
{
#ifdef CONFIG_XMIT_THREAD_MODE
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;
	enqueue_pending_xmitbuf(pxmitpriv,pmgntframe->pxmitbuf);
	return _SUCCESS;
#else
	return rtw_dump_xframe(padapter, pmgntframe);
#endif
}

/*
 * Return
 *	_TRUE	dump packet directly ok
 *	_FALSE	temporary can't transmit packets to hardware
 */
s32	rtl8812ae_hal_xmit(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	return pre_xmitframe(padapter, pxmitframe);
}

s32	rtl8812ae_hal_xmitframe_enqueue(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	s32 err;

	err = rtw_xmitframe_enqueue(padapter, pxmitframe);
	if (err != _SUCCESS) {
		rtw_free_xmitframe(pxmitpriv, pxmitframe);

		pxmitpriv->tx_drop++;
	} else {
		if (check_nic_enough_desc(padapter, &pxmitframe->attrib) == _TRUE) {
#ifdef PLATFORM_LINUX
			tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
#endif
		}
	}

	return err;
}

#ifdef CONFIG_HOSTAPD_MLME

static void rtl8812ae_hostap_mgnt_xmit_cb(struct urb *urb)
{
#ifdef PLATFORM_LINUX
	struct sk_buff *skb = (struct sk_buff *)urb->context;

	/* RTW_INFO("%s\n", __FUNCTION__); */

	rtw_skb_free(skb);
#endif
}

s32 rtl8812ae_hostap_mgnt_xmit_entry(_adapter *padapter, _pkt *pkt)
{
#ifdef PLATFORM_LINUX
	u16 fc;
	int rc, len, pipe;
	unsigned int bmcst, tid, qsel;
	struct sk_buff *skb, *pxmit_skb;
	struct urb *urb;
	unsigned char *pxmitbuf;
	struct tx_desc *ptxdesc;
	struct rtw_ieee80211_hdr *tx_hdr;
	struct hostapd_priv *phostapdpriv = padapter->phostapdpriv;
	struct net_device *pnetdev = padapter->pnetdev;
	HAL_DATA_TYPE *pHalData = GET_HAL_DATA(padapter);
	struct dvobj_priv *pdvobj = adapter_to_dvobj(padapter);


	/* RTW_INFO("%s\n", __FUNCTION__); */

	skb = pkt;

	len = skb->len;
	tx_hdr = (struct rtw_ieee80211_hdr *)(skb->data);
	fc = le16_to_cpu(tx_hdr->frame_ctl);
	bmcst = IS_MCAST(tx_hdr->addr1);

	if ((fc & RTW_IEEE80211_FCTL_FTYPE) != RTW_IEEE80211_FTYPE_MGMT)
		goto _exit;

	pxmit_skb = rtw_skb_alloc(len + TXDESC_SIZE);

	if (!pxmit_skb)
		goto _exit;

	pxmitbuf = pxmit_skb->data;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		goto _exit;

	/* ----- fill tx desc -----	 */
	ptxdesc = (struct tx_desc *)pxmitbuf;
	_rtw_memset(ptxdesc, 0, sizeof(*ptxdesc));

	/* offset 0	 */
	ptxdesc->txdw0 |= cpu_to_le32(len & 0x0000ffff);
	ptxdesc->txdw0 |= cpu_to_le32(((TXDESC_SIZE + OFFSET_SZ) << OFFSET_SHT) & 0x00ff0000); /* default = 32 bytes for TX Desc */
	ptxdesc->txdw0 |= cpu_to_le32(OWN | FSG | LSG);

	if (bmcst)
		ptxdesc->txdw0 |= cpu_to_le32(BIT(24));

	/* offset 4	 */
	ptxdesc->txdw1 |= cpu_to_le32(0x00);/* MAC_ID */

	ptxdesc->txdw1 |= cpu_to_le32((0x12 << QSEL_SHT) & 0x00001f00);

	ptxdesc->txdw1 |= cpu_to_le32((0x06 << 16) & 0x000f0000); /* b mode */

	/* offset 8			 */

	/* offset 12		 */
	ptxdesc->txdw3 |= cpu_to_le32((le16_to_cpu(tx_hdr->seq_ctl) << 16) & 0xffff0000);

	/* offset 16		 */
	ptxdesc->txdw4 |= cpu_to_le32(BIT(8));/* driver uses rate */

	/* offset 20 */

	rtl8188e_cal_txdesc_chksum(ptxdesc);
	/* ----- end of fill tx desc ----- */

	/*  */
	skb_put(pxmit_skb, len + TXDESC_SIZE);
	pxmitbuf = pxmitbuf + TXDESC_SIZE;
	_rtw_memcpy(pxmitbuf, skb->data, len);

	/* RTW_INFO("mgnt_xmit, len=%x\n", pxmit_skb->len); */


	/* ----- prepare urb for submit ----- */

	/* translate DMA FIFO addr to pipehandle */
	/* pipe = ffaddr2pipehdl(pdvobj, MGT_QUEUE_INX); */
	pipe = usb_sndbulkpipe(pdvobj->pusbdev, pHalData->Queue2EPNum[(u8)MGT_QUEUE_INX] & 0x0f);

	usb_fill_bulk_urb(urb, pdvobj->pusbdev, pipe,
		pxmit_skb->data, pxmit_skb->len, rtl8188ee_hostap_mgnt_xmit_cb, pxmit_skb);

	urb->transfer_flags |= URB_ZERO_PACKET;
	usb_anchor_urb(urb, &phostapdpriv->anchored);
	rc = usb_submit_urb(urb, GFP_ATOMIC);
	if (rc < 0) {
		usb_unanchor_urb(urb);
		kfree_skb(skb);
	}
	usb_free_urb(urb);


_exit:

	rtw_skb_free(skb);

#endif

	return 0;

}
#endif
