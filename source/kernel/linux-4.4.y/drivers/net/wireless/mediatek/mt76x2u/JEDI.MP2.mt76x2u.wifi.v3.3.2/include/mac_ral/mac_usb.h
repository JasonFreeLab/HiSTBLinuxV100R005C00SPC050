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


#ifndef __MAC_USB_H__
#define __MAC_USB_H__

#include "rtmp_type.h"
#ifdef RLT_MAC
#include "mac_ral/nmac/ral_nmac_usb.h"
#endif /* RLT_MAC */
#ifdef RTMP_MAC
#include "mac_ral/omac/ral_omac_usb.h"
#endif /* RTMP_MAC */

#include "mac_ral/rtmp_mac.h"
#include "chip/rtmp_phy.h"
#include "rtmp_iface.h"
#include "rtmp_dot11.h"

#define USB_CYC_CFG				0x02a4

#ifdef RTMP_MAC
#define RTMP_USB_DMA_CFG 0x02a0
#endif /* RTMP_MAC */

#ifdef RT_BIG_ENDIAN
typedef union _USB_DMA_CFG_STRUC {
#if defined(MT76x0) || defined(MT76x2)
	struct {
		UINT32 TxBusy:1;	/*USB DMA TX FSM busy. debug only */
		UINT32 RxBusy:1;	/*USB DMA RX FSM busy. debug only */
		UINT32 EpoutValid:6;	/*OUT endpoint data valid. debug only */
		UINT32 TxBulkEn:1;	/*Enable USB DMA Tx */
		UINT32 RxBulkEn:1;	/*Enable USB DMA Rx */
		UINT32 RxBulkAggEn:1;	/*Enable Rx Bulk Aggregation */
		UINT32 WL_LPK_EN:1;	/*Halt TXOP count down when TX buffer is full. */
		UINT32 TxClear:1;	/*Clear USB DMA TX path */
		UINT32 RX_DROP_OR_PADDING:1;	/* Drop current WL RX packets in UDMA */
		UINT32 wakeup_en:1;	/* USB wakeup host enable */
		UINT32 UDMA_TX_WL_DROP:1;	/* Drop current WL TX packets in UDMA */
		UINT32 RxBulkAggLmt:8;	/*Rx Bulk Aggregation Limit  in unit of 1024 bytes */
		UINT32 RxBulkAggTOut:8;	/*Rx Bulk Aggregation TimeOut  in unit of 33ns */
	} field_76xx;
#endif				/* defined(MT76x0) || defined(MT76x2) */
	struct {
		UINT32 TxBusy:1;	/*USB DMA TX FSM busy. debug only */
		UINT32 RxBusy:1;	/*USB DMA RX FSM busy. debug only */
		UINT32 EpoutValid:6;	/*OUT endpoint data valid. debug only */
		UINT32 TxBulkEn:1;	/*Enable USB DMA Tx */
		UINT32 RxBulkEn:1;	/*Enable USB DMA Rx */
		UINT32 RxBulkAggEn:1;	/*Enable Rx Bulk Aggregation */
		UINT32 TxopHalt:1;	/*Halt TXOP count down when TX buffer is full. */
		UINT32 TxClear:1;	/*Clear USB DMA TX path */
		UINT32 rsv:2;
		UINT32 phyclear:1;	/*phy watch dog enable. write 1 */
		UINT32 RxBulkAggLmt:8;	/*Rx Bulk Aggregation Limit  in unit of 1024 bytes */
		UINT32 RxBulkAggTOut:8;	/*Rx Bulk Aggregation TimeOut  in unit of 33ns */
	} field;
	UINT32 word;
} USB_DMA_CFG_STRUC;
#else
typedef union _USB_DMA_CFG_STRUC {
#if defined(MT76x0) || defined(MT76x2)
	struct {
		UINT32 RxBulkAggTOut:8;	/*Rx Bulk Aggregation TimeOut  in unit of 33ns */
		UINT32 RxBulkAggLmt:8;	/*Rx Bulk Aggregation Limit  in unit of 256 bytes */
		UINT32 UDMA_TX_WL_DROP:1;	/* Drop current WL TX packets in UDMA */
		UINT32 wakeup_en:1;	/* USB wakeup host enable */
		UINT32 RX_DROP_OR_PADDING:1;	/* Drop current WL RX packets in UDMA */
		UINT32 TxClear:1;	/*Clear USB DMA TX path */
		UINT32 WL_LPK_EN:1;	/*Halt TXOP count down when TX buffer is full. */
		UINT32 RxBulkAggEn:1;	/*Enable Rx Bulk Aggregation */
		UINT32 RxBulkEn:1;	/*Enable USB DMA Rx */
		UINT32 TxBulkEn:1;	/*Enable USB DMA Tx */
		UINT32 EpoutValid:6;	/*OUT endpoint data valid */
		UINT32 RxBusy:1;	/*USB DMA RX FSM busy */
		UINT32 TxBusy:1;	/*USB DMA TX FSM busy */
	} field_76xx;
#endif				/* defined(MT76x0) || defined(MT76x2) */
	struct {
		UINT32 RxBulkAggTOut:8;	/*Rx Bulk Aggregation TimeOut  in unit of 33ns */
		UINT32 RxBulkAggLmt:8;	/*Rx Bulk Aggregation Limit  in unit of 256 bytes */
		UINT32 phyclear:1;	/*phy watch dog enable. write 1 */
		UINT32 rsv:2;
		UINT32 TxClear:1;	/*Clear USB DMA TX path */
		UINT32 TxopHalt:1;	/*Halt TXOP count down when TX buffer is full. */
		UINT32 RxBulkAggEn:1;	/*Enable Rx Bulk Aggregation */
		UINT32 RxBulkEn:1;	/*Enable USB DMA Rx */
		UINT32 TxBulkEn:1;	/*Enable USB DMA Tx */
		UINT32 EpoutValid:6;	/*OUT endpoint data valid */
		UINT32 RxBusy:1;	/*USB DMA RX FSM busy */
		UINT32 TxBusy:1;	/*USB DMA TX FSM busy */
	} field;
	UINT32 word;
} USB_DMA_CFG_STRUC;
#endif /* endif */

/*#define BEACON_RING_SIZE		2 */
/* #ifdef CONFIG_MULTI_CHANNEL */
#define MGMTPIPEIDX				5	/* EP6 is highest priority */

#define fRTMP_ADAPTER_NEED_STOP_TX		\
		(fRTMP_ADAPTER_NIC_NOT_EXIST | fRTMP_ADAPTER_HALT_IN_PROGRESS |	\
		 fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_BULKOUT_RESET | \
		 fRTMP_ADAPTER_RADIO_OFF | fRTMP_ADAPTER_REMOVE_IN_PROGRESS | \
		 fRTMP_ADAPTER_IDLE_RADIO_OFF)

/* ====================================================================
	USB TX / RX Frame Descriptors format

	Tx Memory Layout
	1. Packet Buffer
		TxINFO(4 bytes) + TXWI( 16 bytes) + 802.11
	 31													   0
	+-------------------------------------------------------------------+
	|				    TXINFO[31:0]						      |
	+-------------------------------------------------------------------+
	|				    TxWI								  |
	+													     +
	|													     |
	+													     +
	|													     |
	+													       +
	|													       |
	+-------------------------------------------------------------------+
	|				       802.11								  |
	|				       .........							     |
	+-------------------------------------------------------------------+

	Rx Memory Layout
	1. Packet Buffer
		RxDMALen(4 bytes) + RXWI(16 bytes) + 802.11 + RXINFO (4 bytes)
	 31													0
	+-----------------------------------------------------------------+
	|				   RXDMALen[31:0]						 |
	+-----------------------------------------------------------------+
	|					 RxWI								       |
	+													 +
	|													 |
	+													 +
	|													 |
	+													   +
	|													   |
	+-----------------------------------------------------------------+
	|				   802.11							      |
	|				   .........								 |
	+-----------------------------------------------------------------+
	|				   RXINFO							     |
	+-----------------------------------------------------------------+

=====================================================================*/

/*
	RXINFO appends at the end of each rx packet
*/
#define RXDMA_FIELD_SIZE	4

/*
	Rx descriptor format, Rx Ring
*/
#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RXD_STRUC {
	UINT32 dma_len;
} RXD_STRUC, *PRXD_STRUC;
#else
typedef struct GNU_PACKED _RXD_STRUC {
	UINT32 dma_len;
} RXD_STRUC, *PRXD_STRUC;
#endif /* endif */

/*
	Management ring buffer format
*/
typedef struct _MGMT_STRUC {
	BOOLEAN Valid;
	PUCHAR pBuffer;
	ULONG Length;
} MGMT_STRUC, *PMGMT_STRUC;

/*////////////////////////////////////////////////////////////////////////*/
/* The TX_BUFFER structure forms the transmitted USB packet to the device */
/*////////////////////////////////////////////////////////////////////////*/
typedef struct __TX_BUFFER {
	union {
		UCHAR WirelessPacket[TX_BUFFER_NORMSIZE];
		HEADER_802_11 NullFrame;
		PSPOLL_FRAME PsPollPacket;
		RTS_FRAME RTSFrame;
	} field;
	UCHAR Aggregation[4];	/*Buffer for save Aggregation size. */
} TX_BUFFER, *PTX_BUFFER;

typedef struct __HTTX_BUFFER {
	union {
#ifdef USB_BULK_BUF_ALIGMENT
		UCHAR WirelessPacket[MAX_ALIGMENT_TXBULK_SIZE];
#else
		UCHAR WirelessPacket[MAX_TXBULK_SIZE];
#endif				/* USB_BULK_BUF_ALIGMENT */
		HEADER_802_11 NullFrame;
		PSPOLL_FRAME PsPollPacket;
		RTS_FRAME RTSFrame;
	} field;
	UCHAR Aggregation[4];	/*Buffer for save Aggregation size. */
} HTTX_BUFFER, *PHTTX_BUFFER;

#define EDCA_AC0_PIPE	0	/* Bulk EP1 OUT */
#define EDCA_AC1_PIPE	1	/* Bulk EP2 OUT */
#define EDCA_AC2_PIPE	2	/* Bulk EP3	OUT */
#define	EDCA_AC3_PIPE	3	/* Bulk EP4 OUT */
#define	HCCA_PIPE		4	/* Bulk EP5	OUT */

/* used to track driver-generated write irps */
typedef struct _TX_CONTEXT {
	PVOID pAd;		/*Initialized in MiniportInitialize */
	PURB pUrb;		/*Initialized in MiniportInitialize */
	PIRP pIrp;		/*used to cancel pending bulk out. */
	/*Initialized in MiniportInitialize */
	PTX_BUFFER TransferBuffer;	/*Initialized in MiniportInitialize */
	ULONG BulkOutSize;
	UCHAR BulkOutPipeId;
	UCHAR SelfIdx;
	BOOLEAN InUse;
	BOOLEAN bWaitingBulkOut;	/* at least one packet is in this TxContext, ready for making IRP anytime. */
	BOOLEAN bFullForBulkOut;	/* all tx buffer are full , so waiting for tx bulkout. */
	BOOLEAN IRPPending;
	BOOLEAN LastOne;
	BOOLEAN bAggregatible;
	UCHAR Header_802_3[LENGTH_802_3];
	UCHAR Rsv[2];
	ULONG DataOffset;
	UINT TxRate;
	ra_dma_addr_t data_dma;

#ifdef UAPSD_SUPPORT
	USHORT Wcid;
#endif				/* UAPSD_SUPPORT */
} TX_CONTEXT, *PTX_CONTEXT, **PPTX_CONTEXT;

/* used to track driver-generated write irps */
typedef struct _HT_TX_CONTEXT {
	PVOID pAd;		/*Initialized in MiniportInitialize */
#ifdef USB_BULK_BUF_ALIGMENT
	PURB pUrb[BUF_ALIGMENT_RINGSIZE];	/*Initialized in MiniportInitialize */
#else
	PURB pUrb;		/*Initialized in MiniportInitialize */
#endif				/* USB_BULK_BUF_ALIGMENT */

	PIRP pIrp;		/*used to cancel pending bulk out. */
	/*Initialized in MiniportInitialize */
#ifdef USB_BULK_BUF_ALIGMENT
	PHTTX_BUFFER TransferBuffer[BUF_ALIGMENT_RINGSIZE];	/*Initialized in MiniportInitialize */
#else
	PHTTX_BUFFER TransferBuffer;	/*Initialized in MiniportInitialize */
#endif				/* USB_BULK_BUF_ALIGMENT */
	ULONG BulkOutSize;	/* Indicate the total bulk-out size in bytes in one bulk-transmission */
	UCHAR BulkOutPipeId;
	BOOLEAN IRPPending;
	BOOLEAN LastOne;
	BOOLEAN bCurWriting;
	BOOLEAN bRingEmpty;
	BOOLEAN bCopySavePad;
	UCHAR SavedPad[8];
	UCHAR Header_802_3[LENGTH_802_3];
	ULONG CurWritePosition;	/* Indicate the buffer offset which packet will be inserted start from. */
	ULONG CurWriteRealPos;	/* Indicate the buffer offset which packet now are writing to. */
	ULONG NextBulkOutPosition;	/* Indicate the buffer start offset of a bulk-transmission */
	ULONG ENextBulkOutPosition;	/* Indicate the buffer end offset of a bulk-transmission */
	UINT TxRate;
#ifdef USB_BULK_BUF_ALIGMENT
	ra_dma_addr_t data_dma[BUF_ALIGMENT_RINGSIZE];	/* urb dma on linux */
#else
	ra_dma_addr_t data_dma;	/* urb dma on linux */
#endif				/* USB_BULK_BUF_ALIGMENT */
#ifdef USB_BULK_BUF_ALIGMENT
	ULONG CurWriteIdx;	/* pointer to next 32k bytes position when write tx resource or
						when bulk out sizze not > 0x6000 */
	ULONG NextBulkIdx;	/* pointer to next alignment section when bulk ot */
	ULONG CurtBulkIdx;	/* pointer to next alignment section when bulk ot */
#endif				/* USB_BULK_BUF_ALIGMENT */
} HT_TX_CONTEXT, *PHT_TX_CONTEXT, **PPHT_TX_CONTEXT;

typedef struct _CMD_CONTEXT {
	PVOID pAd;
	PURB pUrb;
	ra_dma_addr_t data_dma;
	PUCHAR TransferBuffer;
	BOOLEAN IRPPending;
} CMD_CONTEXT, *PCMD_CONTEXT, **PPCMD_CONTEXT;

/*
	Structure to keep track of receive packets and buffers to indicate
	receive data to the protocol.
*/
typedef struct _RX_CONTEXT {
	PUCHAR TransferBuffer;
	PVOID pAd;
	PIRP pIrp;		/*used to cancel pending bulk in. */
	PURB pUrb;
	/*These 2 Boolean shouldn't both be 1 at the same time. */
	ULONG BulkInOffset;	/* number of packets waiting for reordering . */
/*	BOOLEAN				ReorderInUse;	// At least one packet in this buffer are in
						reordering buffer and wait for receive indication */
	BOOLEAN bRxHandling;	/* Notify this packet is being process now. */
	BOOLEAN InUse;		/* USB Hardware Occupied. Wait for USB HW to put packet. */
	BOOLEAN Readable;	/* Receive Complete back. OK for driver to indicate receiving packet. */
	BOOLEAN IRPPending;	/* TODO: To be removed */
	/*atomic_t				IrpLock; */
	NDIS_SPIN_LOCK RxContextLock;
	ra_dma_addr_t data_dma;	/* urb dma on linux */
} RX_CONTEXT, *PRX_CONTEXT;

typedef struct _CMD_RSP_CONTEXT {
	PUCHAR CmdRspBuffer;
	PVOID pAd;
	PURB pUrb;
	BOOLEAN IRPPending;
	BOOLEAN InUse;
	BOOLEAN Readable;
	ra_dma_addr_t data_dma;
} CMD_RSP_CONTEXT, *PCMD_RSP_CONTEXT;

/******************************************************************************

	USB Frimware Related MACRO

******************************************************************************/
/* 8051 firmware image for usb - use last-half base address = 0x3000 */
#define FIRMWARE_IMAGE_BASE			0x3000
#define MAX_FIRMWARE_IMAGE_SIZE		0x1000	/* 4kbyte */

#define RTMP_WRITE_FIRMWARE(_pAd, _pFwImage, _FwLen)		\
	RTUSBFirmwareWrite(_pAd, _pFwImage, _FwLen)

/******************************************************************************

	USB TX Related MACRO

******************************************************************************/
#define RTMP_START_DEQUEUE(pAd, QueIdx, irqFlags)				\
			{ \
				RTMP_IRQ_LOCK(&pAd->DeQueueLock[QueIdx], irqFlags);		\
				if (pAd->DeQueueRunning[QueIdx]) {						\
					RTMP_IRQ_UNLOCK(&pAd->DeQueueLock[QueIdx], irqFlags);\
					DBGPRINT(RT_DEBUG_INFO, ("DeQueueRunning[%d]= TRUE!\n", QueIdx));\
					continue;\
				} \
				else { \
					pAd->DeQueueRunning[QueIdx] = TRUE;					\
					RTMP_IRQ_UNLOCK(&pAd->DeQueueLock[QueIdx], irqFlags);\
				} \
			}

#define RTMP_STOP_DEQUEUE(pAd, QueIdx, irqFlags)						\
			do {								\
				RTMP_IRQ_LOCK(&pAd->DeQueueLock[QueIdx], irqFlags);		\
				pAd->DeQueueRunning[QueIdx] = FALSE;					\
				RTMP_IRQ_UNLOCK(&pAd->DeQueueLock[QueIdx], irqFlags);	\
			} while (0)

#define	RTMP_HAS_ENOUGH_FREE_DESC(pAd, pTxBlk, freeNum, pPacket) \
		(RTUSBFreeDescRequest(pAd, pTxBlk->QueIdx, (pTxBlk->TotalFrameLen + \
			GET_OS_PKT_LEN(pPacket))) == NDIS_STATUS_SUCCESS)

#define RTMP_RELEASE_DESC_RESOURCE(pAd, QueIdx)			\
		do {} while (0)

#define NEED_QUEUE_BACK_FOR_AGG(_pAd, _QueIdx, _freeNum, _TxFrameType)		\
		((_TxFrameType == TX_RALINK_FRAME) && (RTUSBNeedQueueBackForAgg(_pAd, _QueIdx)))

#define HAL_WriteSubTxResource(pAd, pTxBlk, bIsLast, pFreeNumber)	\
			RtmpUSB_WriteSubTxResource(pAd, pTxBlk, bIsLast, pFreeNumber)

#define HAL_WriteTxResource(pAd, pTxBlk, bIsLast, pFreeNumber)	\
			RtmpUSB_WriteSingleTxResource(pAd, pTxBlk, bIsLast, pFreeNumber)

#define HAL_WriteFragTxResource(pAd, pTxBlk, fragNum, pFreeNumber) \
			RtmpUSB_WriteFragTxResource(pAd, pTxBlk, fragNum, pFreeNumber)

#define HAL_WriteMultiTxResource(pAd, pTxBlk, frameNum, pFreeNumber)	\
			RtmpUSB_WriteMultiTxResource(pAd, pTxBlk, frameNum, pFreeNumber)

#define HAL_FinalWriteTxResource(pAd, pTxBlk, totalMPDUSize, TxIdx)	\
			RtmpUSB_FinalWriteTxResource(pAd, pTxBlk, totalMPDUSize, TxIdx)

#define HAL_LastTxIdx(pAd, QueIdx, TxIdx) \
				/*RtmpUSBDataLastTxIdx(pAd, QueIdx,TxIdx) */

#define HAL_KickOutTx(pAd, pTxBlk, QueIdx)	\
			RtmpUSBDataKickOut(pAd, pTxBlk, QueIdx)

#define HAL_KickOutMgmtTx(pAd, QueIdx, pPacket, pSrcBufVA, SrcBufLen)	\
			RtmpUSBMgmtKickOut(pAd, QueIdx, pPacket, pSrcBufVA, SrcBufLen)

#define HAL_KickOutNullFrameTx(_pAd, _QueIdx, _pNullFrame, _frameLen)	\
			RtmpUSBNullFrameKickOut(_pAd, _QueIdx, _pNullFrame, _frameLen)

#define GET_TXRING_FREENO(_pAd, _QueIdx)	(_QueIdx)	/*(_pAd->TxRing[_QueIdx].TxSwFreeIdx) */
#define GET_MGMTRING_FREENO(_pAd)			(_pAd->MgmtRing.TxSwFreeIdx)

/* ----------------- RX Related MACRO ----------------- */

/*
  *	MLME Related MACRO
  */
#define RTMP_MLME_HANDLER(pAd)			RtmpMLMEUp(&(pAd->mlmeTask))

#define RTMP_MLME_PRE_SANITY_CHECK(pAd)								\
	{	if ((pAd->StaCfg.bHardwareRadio == TRUE) &&					\
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)) &&		\
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS))) {	\
			RTEnqueueInternalCmd(pAd, CMDTHREAD_CHECK_GPIO, NULL, 0); } }

#define RTMP_MLME_RESET_STATE_MACHINE(pAd)	\
		do { \
			MlmeEnqueue(pAd, MLME_CNTL_STATE_MACHINE, MT2_RESET_CONF, 0, NULL, 0);	\
			RTMP_MLME_HANDLER(pAd); \
		} while (0)

#define RTMP_HANDLE_COUNTER_MEASURE(_pAd, _pEntry)		\
	{	RTEnqueueInternalCmd(_pAd, CMDTHREAD_802_11_COUNTER_MEASURE, _pEntry, sizeof(MAC_TABLE_ENTRY));	\
		RTMP_MLME_HANDLER(_pAd);									\
	}

/*
  *	Power Save Related MACRO
  */
#ifdef CONFIG_STA_SUPPORT
#define RTMP_PS_POLL_ENQUEUE(pAd)						\
	{	RTUSB_SET_BULK_FLAG(pAd, fRTUSB_BULK_OUT_PSPOLL); \
		RTUSBKickBulkOut(pAd); }

#define RTMP_STA_FORCE_WAKEUP(_pAd, bFromTx) \
	RT28xxUsbStaAsicForceWakeup(_pAd, bFromTx)

#define RTMP_STA_SLEEP_THEN_AUTO_WAKEUP(pAd, TbttNumToNextWakeUp) \
	RT28xxUsbStaAsicSleepThenAutoWakeup(pAd, TbttNumToNextWakeUp)

#define RTMP_SET_PSM_BIT(_pAd, _val) \
	{\
		if ((_pAd)->StaCfg.WindowsPowerMode == Ndis802_11PowerModeFast_PSP) \
			MlmeSetPsmBit(_pAd, _val);\
		else {\
			USHORT _psm_val = _val; \
			RTEnqueueInternalCmd(_pAd, CMDTHREAD_SET_PSM_BIT, &(_psm_val), sizeof(USHORT)); \
		} \
	}
#endif /* CONFIG_STA_SUPPORT */

#define RTMP_MLME_RADIO_ON(pAd) \
	RT28xxUsbMlmeRadioOn(pAd)

#define RTMP_MLME_RADIO_OFF(pAd) \
	RT28xxUsbMlmeRadioOFF(pAd)

/* MAC Search table */
/* add this entry into ASIC RX WCID search table */
#define RTMP_STA_ENTRY_ADD(pAd, pEntry)					\
{														\
	RT_SET_ASIC_WCID Info;								\
														\
	Info.WCID = pEntry->wcid;							\
	NdisMoveMemory(Info.Addr, pEntry->Addr, MAC_ADDR_LEN); \
														\
	RTEnqueueInternalCmd(pAd, CMDTHREAD_SET_CLIENT_MAC_ENTRY, \
							&Info, sizeof(RT_SET_ASIC_WCID)); \
}

/* ----------------- Security Related MACRO ----------------- */

/* Set Asic WCID Attribute table */
#define RTMP_SET_WCID_SEC_INFO(_pAd, _BssIdx, _KeyIdx, _CipherAlg, _Wcid, _KeyTabFlag)	\
{														\
	RT_ASIC_WCID_SEC_INFO Info;							\
														\
	Info.BssIdx = _BssIdx;								\
	Info.KeyIdx = _KeyIdx;								\
	Info.CipherAlg = _CipherAlg;						\
	Info.Wcid = _Wcid;									\
	Info.KeyTabFlag = _KeyTabFlag;						\
														\
	RTEnqueueInternalCmd(_pAd, CMDTHREAD_SET_WCID_SEC_INFO,			\
							&Info, sizeof(RT_ASIC_WCID_SEC_INFO));	\
}

/* Set Asic WCID IV/EIV table */
#define RTMP_ASIC_WCID_IVEIV_TABLE(_pAd, _Wcid, _uIV, _uEIV)	\
{														\
	RT_ASIC_WCID_IVEIV_ENTRY Info;						\
														\
	Info.Wcid = _Wcid;									\
	Info.Iv = _uIV;										\
	Info.Eiv = _uEIV;									\
														\
	RTEnqueueInternalCmd(_pAd, CMDTHREAD_SET_ASIC_WCID_IVEIV,	\
							&Info,						\
							sizeof(RT_ASIC_WCID_IVEIV_ENTRY));	\
}

/* Set Asic WCID Attribute table */
#define RTMP_ASIC_WCID_ATTR_TABLE(_pAd, _BssIdx, _KeyIdx, _CipherAlg, _Wcid, _KeyTabFlag)	\
{														\
	RT_ASIC_WCID_ATTR_ENTRY Info;						\
														\
	Info.BssIdx = _BssIdx;								\
	Info.KeyIdx = _KeyIdx;								\
	Info.CipherAlg = _CipherAlg;						\
	Info.Wcid = _Wcid;									\
	Info.KeyTabFlag = _KeyTabFlag;						\
														\
	RTEnqueueInternalCmd(_pAd, CMDTHREAD_SET_ASIC_WCID_ATTR, \
							&Info, sizeof(RT_ASIC_WCID_ATTR_ENTRY)); \
}

/* Set Asic Pairwise key table */
#define RTMP_ASIC_PAIRWISE_KEY_TABLE(_pAd, _WCID, _pCipherKey) \
{														\
	RT_ASIC_PAIRWISE_KEY Info;							\
														\
	Info.WCID = _WCID;									\
	NdisMoveMemory(&Info.CipherKey, _pCipherKey, sizeof(CIPHER_KEY));	\
														\
	RTEnqueueInternalCmd(_pAd, CMDTHREAD_SET_ASIC_PAIRWISE_KEY,			\
							&Info, sizeof(RT_ASIC_PAIRWISE_KEY));		\
}

/* Set Asic Shared key table */
#define RTMP_ASIC_SHARED_KEY_TABLE(_pAd, _BssIndex, _KeyIdx, _pCipherKey) \
{														\
	RT_ASIC_SHARED_KEY Info;							\
														\
	Info.BssIndex = _BssIndex;							\
	Info.KeyIdx = _KeyIdx;								\
	NdisMoveMemory(&Info.CipherKey, _pCipherKey, sizeof(CIPHER_KEY)); \
														\
	RTEnqueueInternalCmd(_pAd, CMDTHREAD_SET_ASIC_SHARED_KEY,	  \
							&Info, sizeof(RT_ASIC_SHARED_KEY));	  \
}

#ifdef CONFIG_STA_SUPPORT
/* Set Port Secured */
#define RTMP_SET_PORT_SECURED(_pAd)						\
{														\
	RTEnqueueInternalCmd(_pAd, CMDTHREAD_SET_PORT_SECURED, NULL, 0); \
}
#endif /* CONFIG_STA_SUPPORT */

/* Remove Pairwise Key table */
#define RTMP_REMOVE_PAIRWISE_KEY_ENTRY(_pAd, _Wcid)		\
{														\
	UCHAR _tWcid = _Wcid;								\
	RTEnqueueInternalCmd(_pAd, CMDTHREAD_REMOVE_PAIRWISE_KEY, &(_tWcid), sizeof(UCHAR));\
}

#define RTMP_OS_IRQ_RELEASE(_pAd, _NetDev)

VOID BeaconUpdateExec(IN PVOID SystemSpecific1,
		      IN PVOID FunctionContext, IN PVOID SystemSpecific2, IN PVOID SystemSpecific3);

#endif /*__MAC_USB_H__ */
