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


#ifndef __RTUSB_IO_H__
#define __RTUSB_IO_H__

#include "wpa_cmm.h"
#include "rtmp_type.h"

/* First RTUSB IO command number */
#define CMDTHREAD_FIRST_CMD_ID						0x0D730101

#define CMDTHREAD_RESET_BULK_OUT						0x0D730101
#define CMDTHREAD_RESET_BULK_IN						0x0D730102
#define CMDTHREAD_CHECK_GPIO							0x0D730103
#define CMDTHREAD_SET_ASIC_WCID						0x0D730104
#define CMDTHREAD_DEL_ASIC_WCID						0x0D730105
#define CMDTHREAD_SET_CLIENT_MAC_ENTRY				0x0D730106

#ifdef CONFIG_STA_SUPPORT
#define CMDTHREAD_SET_PSM_BIT							0x0D730107
#define CMDTHREAD_FORCE_WAKE_UP						0x0D730108
#define CMDTHREAD_FORCE_SLEEP_AUTO_WAKEUP			0x0D730109
#define CMDTHREAD_QKERIODIC_EXECUT					0x0D73010A
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
#define CMDTHREAD_AP_UPDATE_CAPABILITY_AND_ERPIE	0x0D73010B
#define CMDTHREAD_AP_ENABLE_TX_BURST				0x0D73010C
#define CMDTHREAD_AP_DISABLE_TX_BURST				0x0D73010D
#define CMDTHREAD_AP_ADJUST_EXP_ACK_TIME			0x0D73010E
#define CMDTHREAD_AP_RECOVER_EXP_ACK_TIME			0x0D73010F
#define CMDTHREAD_CHAN_RESCAN						0x0D730110
#endif /* CONFIG_AP_SUPPORT */

#define CMDTHREAD_SET_LED_STATUS				0x0D730111	/* Set WPS LED status (LED_WPS_XXX). */
#ifdef WSC_INCLUDED
#ifdef WSC_LED_SUPPORT
#define CMDTHREAD_LED_WPS_MODE10					0x0D730112
#endif /* WSC_LED_SUPPORT */
#endif /* WSC_INCLUDED */

/* Security related */
#define CMDTHREAD_SET_WCID_SEC_INFO					0x0D730113
#define CMDTHREAD_SET_ASIC_WCID_IVEIV				0x0D730114
#define CMDTHREAD_SET_ASIC_WCID_ATTR				0x0D730115
#define CMDTHREAD_SET_ASIC_SHARED_KEY				0x0D730116
#define CMDTHREAD_SET_ASIC_PAIRWISE_KEY				0x0D730117
#define CMDTHREAD_REMOVE_PAIRWISE_KEY				0x0D730118
#ifdef CONFIG_STA_SUPPORT
#define CMDTHREAD_SET_PORT_SECURED					0x0D730119
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
#define CMDTHREAD_802_11_COUNTER_MEASURE			0x0D73011A
#endif /* CONFIG_AP_SUPPORT */

/* add by johnli, fix "in_interrupt" error when call "MacTableDeleteEntry" in Rx tasklet */
#define CMDTHREAD_UPDATE_PROTECT					0x0D73011B
/* end johnli */

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
#define CMDTHREAD_REG_HINT							0x0D73011C
#define CMDTHREAD_REG_HINT_11D						0x0D73011D
#define CMDTHREAD_SCAN_END							0x0D73011E
#define CMDTHREAD_CONNECT_RESULT_INFORM				0x0D73011F
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */




/* 0x0D730123 is reserved for CMDTHREAD_RESPONSE_EVENT_CALLBACK */

#ifdef CFG_TDLS_SUPPORT
#define CMDTHREAD_TDLS_SEND_CH_SW_SETUP				0x0D730124
#define CMDTHREAD_TDLS_AUTO_TEARDOWN				0x0D730125
#endif /* CFG_TDLS_SUPPORT */


typedef struct _CMDHandler_TLV {
	USHORT Offset;
	USHORT Length;
	UCHAR DataFirst;
} CMDHandler_TLV, *PCMDHandler_TLV;


typedef struct _RT_SET_ASIC_WCID {
	ULONG WCID;		/* mechanism for rekeying: 0:disable, 1: time-based, 2: packet-based */
	ULONG SetTid;		/* time-based: seconds, packet-based: kilo-packets */
	ULONG DeleteTid;	/* time-based: seconds, packet-based: kilo-packets */
	UCHAR Addr[MAC_ADDR_LEN];	/* avoid in interrupt when write key */
} RT_SET_ASIC_WCID, *PRT_SET_ASIC_WCID;

typedef struct _RT_ASIC_WCID_SEC_INFO {
	UCHAR BssIdx;
	UCHAR KeyIdx;
	UCHAR CipherAlg;
	UINT8 Wcid;
	UINT8 KeyTabFlag;
} RT_ASIC_WCID_SEC_INFO, *PRT_ASIC_WCID_SEC_INFO;

typedef struct _RT_ASIC_WCID_IVEIV_ENTRY {
	UINT8 Wcid;
	UINT32 Iv;
	UINT32 Eiv;
} RT_ASIC_WCID_IVEIV_ENTRY, *PRT_ASIC_WCID_IVEIV_ENTRY;

typedef struct _RT_ASIC_WCID_ATTR_ENTRY {
	UCHAR BssIdx;
	UCHAR KeyIdx;
	UCHAR CipherAlg;
	UINT8 Wcid;
	UINT8 KeyTabFlag;
} RT_ASIC_WCID_ATTR_ENTRY, *PRT_ASIC_WCID_ATTR_ENTRY;

typedef struct _RT_ASIC_PAIRWISE_KEY {
	UINT8 WCID;
	CIPHER_KEY CipherKey;
} RT_ASIC_PAIRWISE_KEY, *PRT_ASIC_PAIRWISE_KEY;

typedef struct _RT_ASIC_SHARED_KEY {
	UCHAR BssIndex;
	UCHAR KeyIdx;
	CIPHER_KEY CipherKey;
} RT_ASIC_SHARED_KEY, *PRT_ASIC_SHARED_KEY;

typedef struct _RT_ASIC_PROTECT_INFO {
	USHORT OperationMode;
	UCHAR SetMask;
	BOOLEAN bDisableBGProtect;
	BOOLEAN bNonGFExist;
} RT_ASIC_PROTECT_INFO, *PRT_ASIC_PROTECT_INFO;

/******************************************************************************

	USB Cmd to ASIC Related MACRO

******************************************************************************/
/* reset MAC of a station entry to 0xFFFFFFFFFFFF */
#define RTMP_STA_ENTRY_MAC_RESET(pAd, Wcid)					\
	{	RT_SET_ASIC_WCID	SetAsicWcid;						\
		SetAsicWcid.WCID = Wcid;								\
		RTEnqueueInternalCmd(pAd, CMDTHREAD_DEL_ASIC_WCID,	\
				&SetAsicWcid, sizeof(RT_SET_ASIC_WCID));	}

/* Set MAC register value according operation mode */
#ifdef CONFIG_AP_SUPPORT
#define RTMP_AP_UPDATE_CAPABILITY_AND_ERPIE(pAd)	\
	RTEnqueueInternalCmd(pAd, CMDTHREAD_AP_UPDATE_CAPABILITY_AND_ERPIE, NULL, 0)
#endif /* CONFIG_AP_SUPPORT */

/* Insert the BA bitmap to ASIC for the Wcid entry */
#define RTMP_ADD_BA_SESSION_TO_ASIC(_pAd, _Aid, _TID)					\
		do {								\
			RT_SET_ASIC_WCID	SetAsicWcid;							\
			SetAsicWcid.WCID = (_Aid);					\
			SetAsicWcid.SetTid = (0x10000<<(_TID));						\
			SetAsicWcid.DeleteTid = 0xffffffff;							\
			RTEnqueueInternalCmd((_pAd), CMDTHREAD_SET_ASIC_WCID, \
			&SetAsicWcid, sizeof(RT_SET_ASIC_WCID));	\
		} while (0)

/* Remove the BA bitmap from ASIC for the Wcid entry */
#define RTMP_DEL_BA_SESSION_FROM_ASIC(_pAd, _Wcid, _TID)				\
		do {								\
			RT_SET_ASIC_WCID	SetAsicWcid;							\
			SetAsicWcid.WCID = (_Wcid);					\
			SetAsicWcid.SetTid = (0xffffffff);							\
			SetAsicWcid.DeleteTid = (0x10000<<(_TID));					\
			RTEnqueueInternalCmd((_pAd), CMDTHREAD_SET_ASIC_WCID, \
			&SetAsicWcid, sizeof(RT_SET_ASIC_WCID));	\
		} while (0)

#define RTMP_UPDATE_PROTECT(_pAd, _OperationMode, _SetMask, _bDisableBGProtect, _bNonGFExist)	\
		do {\
			RT_ASIC_PROTECT_INFO AsicProtectInfo;\
			AsicProtectInfo.OperationMode = (_OperationMode);\
			AsicProtectInfo.SetMask = (_SetMask);\
			AsicProtectInfo.bDisableBGProtect = (_bDisableBGProtect);\
			AsicProtectInfo.bNonGFExist = (_bNonGFExist);\
			RTEnqueueInternalCmd((_pAd), CMDTHREAD_UPDATE_PROTECT, \
			&AsicProtectInfo, sizeof(RT_ASIC_PROTECT_INFO));\
		} while (0)

void usb_cfg_read_v1(struct _RTMP_ADAPTER *ad, u32 *value);
void usb_cfg_write_v1(struct _RTMP_ADAPTER *ad, u32 value);
void usb_cfg_read_v2(struct _RTMP_ADAPTER *ad, u32 *value);
void usb_cfg_write_v2(struct _RTMP_ADAPTER *ad, u32 value);
void usb_cfg_read_v3(struct _RTMP_ADAPTER *ad, u32 *value);
void usb_cfg_write_v3(struct _RTMP_ADAPTER *ad, u32 value);
int write_reg(struct _RTMP_ADAPTER *ad, UINT32 base, UINT16 offset, UINT32 val);
int read_reg(struct _RTMP_ADAPTER *ad, UINT32 base, UINT16 offset, UINT32 *value);
int usb2_disconnect_cmd(struct _RTMP_ADAPTER *ad, UINT8 Discon_mode,
	UINT8 GPIO_notify_mode, UINT8 GPIO_Notify_Pin);

#ifdef NEW_WOW_SUPPORT
int wmt_gpio_configrue(struct _RTMP_ADAPTER *ad, PVOID io_buf, UINT Len);
#endif /* NEW_WOW_SUPPORT */
#endif /* __RTUSB_IO_H__ */
