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
#define _HCI_OPS_OS_C_

/* #include <drv_types.h> */
#include <rtl8812a_hal.h>

static int rtl8812ae_init_rx_ring(_adapter *padapter)
{
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct pci_dev	*pdev = pdvobjpriv->ppcidev;
	struct net_device	*dev = padapter->pnetdev;
	dma_addr_t *mapping = NULL;
	struct sk_buff *skb = NULL;
	u8	*rx_desc = NULL;
	int	i, rx_queue_idx;


	/* rx_queue_idx 0:RX_MPDU_QUEUE */
	/* rx_queue_idx 1:RX_CMD_QUEUE */
	for (rx_queue_idx = 0; rx_queue_idx < 1/*RX_MAX_QUEUE*/; rx_queue_idx++) {
		precvpriv->rx_ring[rx_queue_idx].desc =
			pci_alloc_consistent(pdev,
			sizeof(*precvpriv->rx_ring[rx_queue_idx].desc) * precvpriv->rxringcount,
				     &precvpriv->rx_ring[rx_queue_idx].dma);

		if (!precvpriv->rx_ring[rx_queue_idx].desc
		    || (unsigned long)precvpriv->rx_ring[rx_queue_idx].desc & 0xFF) {
			RTW_INFO("Cannot allocate RX ring\n");
			return _FAIL;
		}

		_rtw_memset(precvpriv->rx_ring[rx_queue_idx].desc, 0, sizeof(*precvpriv->rx_ring[rx_queue_idx].desc) * precvpriv->rxringcount);
		precvpriv->rx_ring[rx_queue_idx].idx = 0;

		for (i = 0; i < precvpriv->rxringcount; i++) {
			skb = rtw_skb_alloc(precvpriv->rxbuffersize);
			if (!skb) {
				RTW_INFO("Cannot allocate skb for RX ring\n");
				return _FAIL;
			}

			rx_desc = (u8 *)(&precvpriv->rx_ring[rx_queue_idx].desc[i]);

			precvpriv->rx_ring[rx_queue_idx].rx_buf[i] = skb;

			mapping = (dma_addr_t *)skb->cb;

			/* just set skb->cb to mapping addr for pci_unmap_single use */
			*mapping = pci_map_single(pdev, skb_tail_pointer(skb),
						  precvpriv->rxbuffersize,
						  PCI_DMA_FROMDEVICE);

			SET_RX_STATUS_DESC_BUFF_ADDR_8812(rx_desc, *mapping);
			SET_RX_STATUS_DESC_PKT_LEN_8812(rx_desc, precvpriv->rxbuffersize);
			SET_RX_STATUS_DESC_OWN_8812(rx_desc, 1);
		}

		SET_RX_STATUS_DESC_EOR_8812(rx_desc, 1);
	}


	return _SUCCESS;
}

static void rtl8812ae_free_rx_ring(_adapter *padapter)
{
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct pci_dev	*pdev = pdvobjpriv->ppcidev;
	int i, rx_queue_idx;


	/* rx_queue_idx 0:RX_MPDU_QUEUE */
	/* rx_queue_idx 1:RX_CMD_QUEUE */
	for (rx_queue_idx = 0; rx_queue_idx < 1/*RX_MAX_QUEUE*/; rx_queue_idx++) {
		for (i = 0; i < precvpriv->rxringcount; i++) {
			struct sk_buff *skb = precvpriv->rx_ring[rx_queue_idx].rx_buf[i];
			if (!skb)
				continue;

			pci_unmap_single(pdev,
					 *((dma_addr_t *) skb->cb),
					 precvpriv->rxbuffersize,
					 PCI_DMA_FROMDEVICE);
			kfree_skb(skb);
		}

		pci_free_consistent(pdev,
			    sizeof(*precvpriv->rx_ring[rx_queue_idx].desc) *
				    precvpriv->rxringcount,
				    precvpriv->rx_ring[rx_queue_idx].desc,
				    precvpriv->rx_ring[rx_queue_idx].dma);
		precvpriv->rx_ring[rx_queue_idx].desc = NULL;
	}

}


static int rtl8812ae_init_tx_ring(_adapter *padapter, unsigned int prio, unsigned int entries)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct pci_dev	*pdev = pdvobjpriv->ppcidev;
	struct tx_desc	*ring;
	u8				*tx_desc;
	dma_addr_t		dma;
	int	i;


	/* RTW_INFO("%s entries num:%d\n", __func__, entries); */
	ring = pci_alloc_consistent(pdev, sizeof(*ring) * entries, &dma);
	if (!ring || (unsigned long)ring & 0xFF) {
		RTW_INFO("Cannot allocate TX ring (prio = %d)\n", prio);
		return _FAIL;
	}

	_rtw_memset(ring, 0, sizeof(*ring) * entries);
	pxmitpriv->tx_ring[prio].desc = ring;
	pxmitpriv->tx_ring[prio].dma = dma;
	pxmitpriv->tx_ring[prio].idx = 0;
	pxmitpriv->tx_ring[prio].entries = entries;
	_rtw_init_queue(&pxmitpriv->tx_ring[prio].queue);
	pxmitpriv->tx_ring[prio].qlen = 0;

	/* RTW_INFO("%s queue:%d, ring_addr:%p\n", __func__, prio, ring); */

	for (i = 0; i < entries; i++) {
		tx_desc = (u8 *)&ring[i];
		SET_TX_DESC_NEXT_DESC_ADDRESS_8812(tx_desc, ((u32) dma + ((i + 1) % entries) * sizeof(*ring)));
	}


	return _SUCCESS;
}

static void rtl8812ae_free_tx_ring(_adapter *padapter, unsigned int prio)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct pci_dev	*pdev = pdvobjpriv->ppcidev;
	struct rtw_tx_ring *ring = &pxmitpriv->tx_ring[prio];
	u8				*tx_desc;
	struct xmit_buf	*pxmitbuf;


	while (ring->qlen) {
		tx_desc = (u8 *)(&ring->desc[ring->idx]);

		SET_TX_DESC_OWN_8812(tx_desc, 0);

		if (prio != BCN_QUEUE_INX)
			ring->idx = (ring->idx + 1) % ring->entries;

		pxmitbuf = rtl8812ae_dequeue_xmitbuf(ring);
		if (pxmitbuf) {
			pci_unmap_single(pdev, GET_TX_DESC_TX_BUFFER_ADDRESS_8812(tx_desc), pxmitbuf->len, PCI_DMA_TODEVICE);
			rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
		} else {
			RTW_INFO("%s(): qlen(%d) is not zero, but have xmitbuf in pending queue\n", __func__, ring->qlen);
			break;
		}
	}

	pci_free_consistent(pdev, sizeof(*ring->desc) * ring->entries, ring->desc, ring->dma);
	ring->desc = NULL;

}

static void init_desc_ring_var(_adapter *padapter)
{
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	u8 i = 0;

	for (i = 0; i < HW_QUEUE_ENTRY; i++)
		pxmitpriv->txringcount[i] = TXDESC_NUM;

	/* we just alloc 2 desc for beacon queue, */
	/* because we just need first desc in hw beacon. */
	pxmitpriv->txringcount[BCN_QUEUE_INX] = 2;

	/* BE queue need more descriptor for performance consideration */
	/* or, No more tx desc will happen, and may cause mac80211 mem leakage. */
	/* if(!padapter->registrypriv.wifi_spec) */
	/*	pxmitpriv->txringcount[BE_QUEUE_INX] = TXDESC_NUM_BE_QUEUE; */

	pxmitpriv->txringcount[TXCMD_QUEUE_INX] = 2;

	precvpriv->rxbuffersize = MAX_RECVBUF_SZ;	/* 2048; */ /* 1024; */
	precvpriv->rxringcount = PCI_MAX_RX_COUNT;	/* 64; */
}


u32 rtl8812ae_init_desc_ring(_adapter *padapter)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	int	i, ret = _SUCCESS;


	init_desc_ring_var(padapter);

	ret = rtl8812ae_init_rx_ring(padapter);
	if (ret == _FAIL)
		return ret;

	/* general process for other queue */
	for (i = 0; i < PCI_MAX_TX_QUEUE_COUNT; i++) {
		ret = rtl8812ae_init_tx_ring(padapter, i, pxmitpriv->txringcount[i]);
		if (ret == _FAIL)
			goto err_free_rings;
	}

	return ret;

err_free_rings:

	rtl8812ae_free_rx_ring(padapter);

	for (i = 0; i < PCI_MAX_TX_QUEUE_COUNT; i++)
		if (pxmitpriv->tx_ring[i].desc)
			rtl8812ae_free_tx_ring(padapter, i);


	return ret;
}

u32 rtl8812ae_free_desc_ring(_adapter *padapter)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	u32 i;


	/* free rx rings */
	rtl8812ae_free_rx_ring(padapter);

	/* free tx rings */
	for (i = 0; i < HW_QUEUE_ENTRY; i++)
		rtl8812ae_free_tx_ring(padapter, i);


	return _SUCCESS;
}

void rtl8812ae_reset_desc_ring(_adapter *padapter)
{
	_irqL	irqL;
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	struct xmit_buf	*pxmitbuf = NULL;
	u8	*tx_desc, *rx_desc;
	int	i, rx_queue_idx;

	InitTRXDescHwAddress8812AE(padapter);

	for (rx_queue_idx = 0; rx_queue_idx < 1; rx_queue_idx++) {
		if (precvpriv->rx_ring[rx_queue_idx].desc) {
			rx_desc = NULL;
			for (i = 0; i < precvpriv->rxringcount; i++) {
				rx_desc = (u8 *)(&precvpriv->rx_ring[rx_queue_idx].desc[i]);
				SET_RX_STATUS_DESC_OWN_8812(rx_desc, 1);
			}
			precvpriv->rx_ring[rx_queue_idx].idx = 0;
		}
	}

	_enter_critical(&pdvobjpriv->irq_th_lock, &irqL);
	for (i = 0; i < PCI_MAX_TX_QUEUE_COUNT; i++) {
		if (pxmitpriv->tx_ring[i].desc) {
			struct rtw_tx_ring *ring = &pxmitpriv->tx_ring[i];

			while (ring->qlen) {
				tx_desc = (u8 *)(&ring->desc[ring->idx]);

				SET_TX_DESC_OWN_8812(tx_desc, 0);

				if (i != BCN_QUEUE_INX)
					ring->idx = (ring->idx + 1) % ring->entries;

				pxmitbuf = rtl8812ae_dequeue_xmitbuf(ring);
				if (pxmitbuf) {
					pci_unmap_single(pdvobjpriv->ppcidev, GET_TX_DESC_TX_BUFFER_ADDRESS_8812(tx_desc), pxmitbuf->len, PCI_DMA_TODEVICE);
					rtw_free_xmitbuf(pxmitpriv, pxmitbuf);
				} else {
					RTW_INFO("%s(): qlen(%d) is not zero, but have xmitbuf in pending queue\n", __func__, ring->qlen);
					break;
				}
			}
			ring->idx = 0;
		}
	}
	_exit_critical(&pdvobjpriv->irq_th_lock, &irqL);
}

static void rtl8812ae_xmit_beacon(PADAPTER Adapter)
{
#if defined(CONFIG_AP_MODE) && defined (CONFIG_NATIVEAP_MLME)
	struct mlme_priv *pmlmepriv = &Adapter->mlmepriv;

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
		/* send_beacon(Adapter); */
		if (pmlmepriv->update_bcn == _TRUE) {
			WLAN_BSSID_EX *cur_network = &Adapter->mlmeextpriv.mlmext_info.network;
			/* prevent beacon IE length is 0! */
			if (cur_network->IELength < _FIXED_IE_LENGTH_) {
				/* RTW_INFO( "%s:%d cur_network->IELength=%u\n", __FUNCTION__, __LINE__, cur_network->IELength ); */
				return;
			}
			tx_beacon_hdl(Adapter, NULL);
		}
	}
#endif
}

void rtl8812ae_prepare_bcn_tasklet(void *priv)
{
	_adapter	*padapter = (_adapter *)priv;

	rtl8812ae_xmit_beacon(padapter);
}

static u8 check_tx_desc_resource(_adapter *padapter, int prio)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;
	struct rtw_tx_ring	*ring;

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

static void rtl8812ae_tx_isr(PADAPTER Adapter, int prio)
{
	struct xmit_priv	*pxmitpriv = &Adapter->xmitpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(Adapter);
	struct rtw_tx_ring	*ring = &pxmitpriv->tx_ring[prio];
	struct xmit_buf	*pxmitbuf;
	u8	*tx_desc;

#ifdef CONFIG_LPS_LCLK
	int index ; 
	s32 enter32k = _SUCCESS ;
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(Adapter);
#endif
	while (ring->qlen) {
		tx_desc = (u8 *)&ring->desc[ring->idx];

		/* beacon packet will only use the first descriptor defautly, */
		/* and the OWN may not be cleared by the hardware */
		/*  */
		if (prio != BCN_QUEUE_INX) {
			if (GET_TX_DESC_OWN_8812(tx_desc))
				return;
			ring->idx = (ring->idx + 1) % ring->entries;
		} else if (prio == BCN_QUEUE_INX)
			SET_TX_DESC_OWN_8812(tx_desc, 0);

		pxmitbuf = rtl8812ae_dequeue_xmitbuf(ring);
		if (pxmitbuf) {
			pci_unmap_single(pdvobjpriv->ppcidev, GET_TX_DESC_TX_BUFFER_ADDRESS_8812(tx_desc), pxmitbuf->len, PCI_DMA_TODEVICE);
			rtw_sctx_done(&pxmitbuf->sctx);
			rtw_free_xmitbuf(&(pxmitbuf->padapter->xmitpriv), pxmitbuf);
		} else
			RTW_INFO("%s(): qlen(%d) is not zero, but have xmitbuf in pending queue\n", __func__, ring->qlen);
	}

#ifdef CONFIG_LPS_LCLK
	for(index = 0; index < HW_QUEUE_ENTRY; index ++)
	{
		if (index != BCN_QUEUE_INX)
		{
			if(_rtw_queue_empty(&(Adapter->xmitpriv.tx_ring[index].queue)) == _FALSE)
			{
				enter32k = _FAIL;
				break;
			}
		}
	}	
	if(enter32k)
		_set_workitem(&(pwrpriv->dma_event));	
#endif	

	if ((prio != BCN_QUEUE_INX) && check_tx_desc_resource(Adapter, prio)
	    && rtw_xmit_ac_blocked(Adapter) != _TRUE
	   )
		rtw_mi_xmit_tasklet_schedule(Adapter);
}


s32	rtl8812ae_interrupt(PADAPTER Adapter)
{
	_irqL	irqL;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(Adapter);
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(Adapter);
	struct xmit_priv	*pxmitpriv = &Adapter->xmitpriv;
	int	ret = _SUCCESS;

	_enter_critical(&pdvobjpriv->irq_th_lock, &irqL);

	/* read ISR: 4/8bytes */
	if (InterruptRecognized8812AE(Adapter) == _FALSE) {
		ret = _FAIL;
		goto done;
	}

	/* <1> beacon related */
	if (pHalData->IntArray[0] & IMR_TXBCN0OK_8812) {
		PADAPTER bcn_adapter = rtw_mi_get_ap_adapter(Adapter);/*Modify for MI temporary,this processor cannot apply to multi-ap*/

		if (bcn_adapter && bcn_adapter->xmitpriv.beaconDMAing) {
			bcn_adapter->xmitpriv.beaconDMAing = _FAIL;
			rtl8812ae_tx_isr(Adapter, BCN_QUEUE_INX);
		}
	}

	if (pHalData->IntArray[0] & IMR_TXBCN0ERR_8812) {
		PADAPTER bcn_adapter = rtw_mi_get_ap_adapter(Adapter);/*Modify for MI temporary,this processor cannot apply to multi-ap*/

		if (bcn_adapter->xmitpriv.beaconDMAing) {
			bcn_adapter->xmitpriv.beaconDMAing = _FAIL;
			rtl8812ae_tx_isr(Adapter, BCN_QUEUE_INX);
		}
	}

	if (pHalData->IntArray[0] & IMR_BCNDERR0_8812) {
		/* Release resource and re-transmit beacon to HW */
		struct tasklet_struct  *bcn_tasklet;
		PADAPTER bcn_adapter = rtw_mi_get_ap_adapter(Adapter);/*Modify for MI temporary,this processor cannot apply to multi-ap*/

		rtl8812ae_tx_isr(Adapter, BCN_QUEUE_INX);
		bcn_adapter->mlmepriv.update_bcn = _TRUE;
		bcn_tasklet = &bcn_adapter->recvpriv.irq_prepare_beacon_tasklet;
		tasklet_hi_schedule(bcn_tasklet);
	}

	if (pHalData->IntArray[0] & IMR_BCNDMAINT0_8812) {
		struct tasklet_struct  *bcn_tasklet;
		PADAPTER bcn_adapter = rtw_mi_get_ap_adapter(Adapter);/*Modify for MI temporary,this processor cannot apply to multi-ap*/

		bcn_tasklet = &bcn_adapter->recvpriv.irq_prepare_beacon_tasklet;
		tasklet_hi_schedule(bcn_tasklet);
	}

	/* <2> Rx related */
	if ((pHalData->IntArray[0] & (IMR_ROK_8812 | IMR_RDU_8812)) || (pHalData->IntArray[1] & IMR_RXFOVW_8812)) {
		pHalData->IntrMask[0] &= (~(IMR_ROK_8812 | IMR_RDU_8812));
		pHalData->IntrMask[1] &= (~IMR_RXFOVW_8812);
		rtw_write32(Adapter, REG_HIMR0_8812, pHalData->IntrMask[0]);
		rtw_write32(Adapter, REG_HIMR1_8812, pHalData->IntrMask[1]);
		tasklet_hi_schedule(&Adapter->recvpriv.recv_tasklet);
	}

	/* <3> Tx related */
	if (pHalData->IntArray[1] & IMR_TXFOVW_8812) {
		/* RTW_INFO("IMR_TXFOVW!\n"); */
	}

	/*if (pHalData->IntArray[0] & IMR_TX_MASK) {
		pHalData->IntrMask[0] &= (~(IMR_TX_MASK));
		rtw_write32(Adapter, REG_HIMR0_8812, pHalData->IntrMask[0]);
		tasklet_hi_schedule(&pxmitpriv->xmit_tasklet);
	}*/

	if (pHalData->IntArray[0] & IMR_MGNTDOK_8812) {
		/* RTW_INFO("Manage ok interrupt!\n");		 */
		rtl8812ae_tx_isr(Adapter, MGT_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_HIGHDOK_8812) {
		/* RTW_INFO("HIGH_QUEUE ok interrupt!\n"); */
		rtl8812ae_tx_isr(Adapter, HIGH_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_BKDOK_8812) {
		/* RTW_INFO("BK Tx OK interrupt!\n"); */
		rtl8812ae_tx_isr(Adapter, BK_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_BEDOK_8812) {
		/* RTW_INFO("BE TX OK interrupt!\n"); */
		rtl8812ae_tx_isr(Adapter, BE_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_VIDOK_8812) {
		/* RTW_INFO("VI TX OK interrupt!\n"); */
		rtl8812ae_tx_isr(Adapter, VI_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_VODOK_8812) {
		/* RTW_INFO("Vo TX OK interrupt!\n"); */
		rtl8812ae_tx_isr(Adapter, VO_QUEUE_INX);
	}

#ifdef CONFIG_LPS_LCLK
	if (pHalData->IntArray[0] & IMR_CPWM_8812){
		struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(Adapter);	
		_set_workitem(&(pwrpriv->cpwm_event));	
	}
#endif

done:

	_exit_critical(&pdvobjpriv->irq_th_lock, &irqL);

	return ret;
}

static void rtl8812ae_rx_mpdu(_adapter *padapter)
{
	struct recv_priv	*precvpriv = &padapter->recvpriv;
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	_queue			*pfree_recv_queue = &precvpriv->free_recv_queue;
	HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(padapter);
	union recv_frame	*precvframe = NULL;
	u8				*pphy_info = NULL;
	struct rx_pkt_attrib	*pattrib = NULL;
	int	rx_queue_idx = RX_MPDU_QUEUE;
	u32	count = precvpriv->rxringcount;

	/*RX NORMAL PKT*/
	while (count--) {
		u8	*rx_desc = (u8 *)&precvpriv->rx_ring[rx_queue_idx].desc[precvpriv->rx_ring[rx_queue_idx].idx];/* rx descriptor */
		struct sk_buff *skb = precvpriv->rx_ring[rx_queue_idx].rx_buf[precvpriv->rx_ring[rx_queue_idx].idx];/* rx pkt */

		if (GET_RX_STATUS_DESC_OWN_8812(rx_desc)) {/* OWN bit */
			/* wait data to be filled by hardware */
			return;
		} else {
			precvframe = rtw_alloc_recvframe(pfree_recv_queue);
			if (precvframe == NULL) {
				RTW_INFO("%s: precvframe==NULL\n", __func__);

				goto done;
			}

			_rtw_init_listhead(&precvframe->u.hdr.list);
			precvframe->u.hdr.len = 0;

			pci_unmap_single(pdvobjpriv->ppcidev,
					 *((dma_addr_t *)skb->cb),
					 precvpriv->rxbuffersize,
					 PCI_DMA_FROMDEVICE);

			rtl8812_query_rx_desc_status(precvframe, rx_desc);
			pattrib = &precvframe->u.hdr.attrib;

#ifdef CONFIG_RX_PACKET_APPEND_FCS
			if (check_fwstate(&padapter->mlmepriv, WIFI_MONITOR_STATE) == _FALSE)
				if ((pattrib->pkt_rpt_type == NORMAL_RX) && (pHalData->ReceiveConfig & RCR_APPFCS))
					pattrib->pkt_len -= IEEE80211_FCS_LEN;
#endif

			if (rtw_os_alloc_recvframe(padapter, precvframe,
				(skb->data + pattrib->drvinfo_sz + pattrib->shift_sz), skb) == _FAIL) {

				rtw_free_recvframe(precvframe, &precvpriv->free_recv_queue);
				RTW_INFO("rtl8812ae_rx_mpdu:can not allocate memory for skb copy\n");
				*((dma_addr_t *) skb->cb) = pci_map_single(pdvobjpriv->ppcidev, skb_tail_pointer(skb), precvpriv->rxbuffersize, PCI_DMA_FROMDEVICE);
				goto done;
			}

			recvframe_put(precvframe, pattrib->pkt_len);

			if (pattrib->pkt_rpt_type == NORMAL_RX) { /* Normal rx packet */
				if (pattrib->physt)
					pphy_info = (u8 *)(skb->data);

#ifdef CONFIG_CONCURRENT_MODE
				pre_recv_entry(precvframe, pphy_info);
#endif

				if (pattrib->physt && pphy_info)
					rx_query_phy_status(precvframe, pphy_info);

				rtw_recv_entry(precvframe);
			} else {
				if (pattrib->pkt_rpt_type == C2H_PACKET) {
					/*RTW_INFO("rx C2H_PACKET\n");*/
					C2HPacketHandler_8812(padapter, precvframe->u.hdr.rx_data, pattrib->pkt_len);
				}
				rtw_free_recvframe(precvframe, pfree_recv_queue);
			}
			*((dma_addr_t *) skb->cb) = pci_map_single(pdvobjpriv->ppcidev, skb_tail_pointer(skb), precvpriv->rxbuffersize, PCI_DMA_FROMDEVICE);
		}
done:

		SET_RX_STATUS_DESC_BUFF_ADDR_8812(rx_desc, *((dma_addr_t *)skb->cb));
		SET_RX_STATUS_DESC_PKT_LEN_8812(rx_desc, precvpriv->rxbuffersize);
		SET_RX_STATUS_DESC_OWN_8812(rx_desc, 1);

		if (precvpriv->rx_ring[rx_queue_idx].idx == precvpriv->rxringcount - 1)
			SET_RX_STATUS_DESC_EOR_8812(rx_desc, 1);

		precvpriv->rx_ring[rx_queue_idx].idx = (precvpriv->rx_ring[rx_queue_idx].idx + 1) % precvpriv->rxringcount;
	}

}

void rtl8812ae_recv_tasklet(void *priv)
{
	_irqL	irqL;
	_adapter	*padapter = (_adapter *)priv;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);

	rtl8812ae_rx_mpdu(padapter);
	_enter_critical(&pdvobjpriv->irq_th_lock, &irqL);
	pHalData->IntrMask[0] |= (IMR_ROK_8812 | IMR_RDU_8812);
	pHalData->IntrMask[1] |= IMR_RXFOVW_8812;
	rtw_write32(padapter, REG_HIMR0_8812, pHalData->IntrMask[0]);
	rtw_write32(padapter, REG_HIMR1_8812, pHalData->IntrMask[1]);
	_exit_critical(&pdvobjpriv->irq_th_lock, &irqL);
}

static u8 pci_read8(struct intf_hdl *pintfhdl, u32 addr)
{
	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv *)pintfhdl->pintf_dev;
	/*	printk("%s, addr=%08x,  val=%02x\n", __func__, addr,  readb((u8 *)pdvobjpriv->pci_mem_start + addr)); */
	return 0xff & readb((u8 *)pdvobjpriv->pci_mem_start + addr);
}

static u16 pci_read16(struct intf_hdl *pintfhdl, u32 addr)
{
	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv *)pintfhdl->pintf_dev;
	/*	printk("%s, addr=%08x,  val=%04x\n", __func__, addr,  readw((u8 *)pdvobjpriv->pci_mem_start + addr)); */
	return readw((u8 *)pdvobjpriv->pci_mem_start + addr);
}

static u32 pci_read32(struct intf_hdl *pintfhdl, u32 addr)
{
	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv *)pintfhdl->pintf_dev;
	/*	printk("%s, addr=%08x,  val=%08x\n", __func__, addr,  readl((u8 *)pdvobjpriv->pci_mem_start + addr)); */
	return readl((u8 *)pdvobjpriv->pci_mem_start + addr);
}

/* 2009.12.23. by tynli. Suggested by SD1 victorh. For ASPM hang on AMD and Nvidia.
 * 20100212 Tynli: Do read IO operation after write for all PCI bridge suggested by SD1.
 * Origianally this is only for INTEL. */
static int pci_write8(struct intf_hdl *pintfhdl, u32 addr, u8 val)
{
	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv *)pintfhdl->pintf_dev;

	writeb(val, (u8 *)pdvobjpriv->pci_mem_start + addr);
	/* readb((u8 *)pdvobjpriv->pci_mem_start + addr); */
	return 1;
}

static int pci_write16(struct intf_hdl *pintfhdl, u32 addr, u16 val)
{
	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv *)pintfhdl->pintf_dev;
	writew(val, (u8 *)pdvobjpriv->pci_mem_start + addr);
	/* readw((u8 *)pdvobjpriv->pci_mem_start + addr); */
	return 2;
}

static int pci_write32(struct intf_hdl *pintfhdl, u32 addr, u32 val)
{
	struct dvobj_priv  *pdvobjpriv = (struct dvobj_priv *)pintfhdl->pintf_dev;
	writel(val, (u8 *)pdvobjpriv->pci_mem_start + addr);
	/* readl((u8 *)pdvobjpriv->pci_mem_start + addr); */
	return 4;
}


static void pci_read_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem)
{

}

static void pci_write_mem(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem)
{

}

static u32 pci_read_port(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem)
{
	return 0;
}

void rtl8812ae_xmit_tasklet(void *priv)
{
	_irqL	irqL;
	_adapter			*padapter = (_adapter *)priv;
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	struct dvobj_priv	*pdvobjpriv = adapter_to_dvobj(padapter);
	/* struct xmit_priv	*pxmitpriv = &padapter->xmitpriv; */

	/*_enter_critical(&pdvobjpriv->irq_th_lock, &irqL);

	if (pHalData->IntArray[0] & IMR_MGNTDOK_8812) {

		rtl8812ae_tx_isr(padapter, MGT_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_HIGHDOK_8812) {

		rtl8812ae_tx_isr(padapter, HIGH_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_BKDOK_8812) {

		rtl8812ae_tx_isr(padapter, BK_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_BEDOK_8812) {

		rtl8812ae_tx_isr(padapter, BE_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_VIDOK_8812) {

		rtl8812ae_tx_isr(padapter, VI_QUEUE_INX);
	}

	if (pHalData->IntArray[0] & IMR_VODOK_8812) {

		rtl8812ae_tx_isr(padapter, VO_QUEUE_INX);
	}

	pHalData->IntrMask[0] |= IMR_TX_MASK;
	rtw_write32(padapter, REG_HIMR0_8812, pHalData->IntrMask[0]);

	_exit_critical(&pdvobjpriv->irq_th_lock, &irqL);
	*/
	/* if (check_fwstate(&padapter->mlmepriv, _FW_UNDER_SURVEY) != _TRUE) */
	{
		/* try to deal with the pending packets */
		rtl8812ae_xmitframe_resume(padapter);

	#if defined(CONFIG_PCI_HCI) && defined(CONFIG_XMIT_THREAD_MODE)
		if (_rtw_queue_empty(&padapter->xmitpriv.pending_xmitbuf_queue) == _FALSE)
			_rtw_up_sema(&padapter->xmitpriv.xmit_sema);
	#endif

	}

}

static u32 pci_write_port(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem)
{
	_adapter			*padapter = (_adapter *)pintfhdl->padapter;

	padapter->pnetdev->trans_start = jiffies;

	return 0;
}

void rtl8812ae_set_intf_ops(struct _io_ops	*pops)
{

	_rtw_memset((u8 *)pops, 0, sizeof(struct _io_ops));

	pops->_read8 = &pci_read8;
	pops->_read16 = &pci_read16;
	pops->_read32 = &pci_read32;

	pops->_read_mem = &pci_read_mem;
	pops->_read_port = &pci_read_port;

	pops->_write8 = &pci_write8;
	pops->_write16 = &pci_write16;
	pops->_write32 = &pci_write32;

	pops->_write_mem = &pci_write_mem;
	pops->_write_port = &pci_write_port;


}
