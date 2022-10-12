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

#ifndef	__RT_CONFIG_H__
#define	__RT_CONFIG_H__

#include "rtmp_comm.h"

#include "rtmp_def.h"
#include "rtmp_chip.h"
#include "rtmp_timer.h"


#ifdef AGS_SUPPORT
#include "ags.h"
#endif /* AGS_SUPPORT */

#ifdef CONFIG_FPGA_MODE
#include "fpga/fpga_ctl.h"
#endif /* endif */

#include "mlme.h"
#include "crypt_md5.h"
#include "crypt_sha2.h"
#include "crypt_hmac.h"
#include "crypt_aes.h"
#include "crypt_arc4.h"
/*#include "rtmp_cmd.h" */
#include "rtmp.h"
#include "wpa.h"
#include "chlist.h"
#include "spectrum.h"
#ifdef CONFIG_AP_SUPPORT
#include "ap.h"
#include "ap_autoChSel.h"
#endif /* CONFIG_AP_SUPPORT */
#include "rt_os_util.h"

#include "eeprom.h"
#if defined(RTMP_PCI_SUPPORT) || defined(RTMP_USB_SUPPORT)
#include "mcu/mcu.h"
#endif /* endif */

#undef AP_WSC_INCLUDED
#undef STA_WSC_INCLUDED
#undef WSC_INCLUDED

#include "rt_os_net.h"


#ifdef UAPSD_SUPPORT
#include "uapsd.h"
#endif /* UAPSD_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
#ifdef MBSS_SUPPORT
#include "ap_mbss.h"
#endif /* MBSS_SUPPORT */

#ifdef WDS_SUPPORT
#include "ap_wds.h"
#endif /* WDS_SUPPORT */

#ifdef APCLI_SUPPORT
#include "ap_apcli.h"
#endif /* APCLI_SUPPORT */

#ifdef WSC_AP_SUPPORT
#define AP_WSC_INCLUDED
#endif /* WSC_AP_SUPPORT */

#include "ap_ids.h"
#include "ap_cfg.h"

#endif /* CONFIG_AP_SUPPORT */

#ifdef MAT_SUPPORT
#include "mat.h"
#endif /* MAT_SUPPORT */


#ifdef CONFIG_STA_SUPPORT
#include "sta.h"
#ifdef WSC_STA_SUPPORT
#define STA_WSC_INCLUDED
#endif /* WSC_STA_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

#ifdef BLOCK_NET_IF
#include "netif_block.h"
#endif /* BLOCK_NET_IF */

#ifdef IGMP_SNOOP_SUPPORT
#include "igmp_snoop.h"
#endif /* IGMP_SNOOP_SUPPORT */

#ifdef RALINK_ATE
#include "rt_ate.h"
#endif /* RALINK_ATE */

#ifdef WCX_SUPPORT
#include "meta_agent.h"
#ifndef RALINK_ATE
#error "For supporting META GUI, please set HAS_ATE=y and WCX_SUPPORT=y."
#endif /* RALINK_ATE */
#endif /* endif */

#ifdef RALINK_QA
#include "rt_qa.h"
#endif /* RALINK_QA */

#ifdef RALINK_QA
#ifndef RALINK_ATE
#error "For supporting QA GUI, please set HAS_ATE=y and HAS_QA_SUPPORT=y."
#endif /* RALINK_ATE */
#endif /* RALINK_QA */



#ifdef WAPI_SUPPORT
#include "wapi.h"
#endif /* WAPI_SUPPORT */


#ifdef DOT11Z_TDLS_SUPPORT
#include "tdls.h"
#include "tdls_uapsd.h"
#endif /* DOT11Z_TDLS_SUPPORT */

#if defined(AP_WSC_INCLUDED) || defined(STA_WSC_INCLUDED)
#define WSC_INCLUDED
#endif /* endif */

#ifdef CONFIG_AP_SUPPORT
#ifdef WDS_SUPPORT
#define RALINK_PASSPHRASE	"Ralink"
#endif /* WDS_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
#ifndef APCLI_SUPPORT
#error "Build Apcli for being controlled by NetworkManager or wext, please set HAS_APCLI_SUPPORT=y and HAS_APCLI_WPA_SUPPLICANT=y"
#endif /* APCLI_SUPPORT */
#define WPA_SUPPLICANT_SUPPORT
#endif /* APCLI_WPA_SUPPLICANT_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef NATIVE_WPA_SUPPLICANT_SUPPORT
#ifndef WPA_SUPPLICANT_SUPPORT
#error "Build for being controlled by NetworkManager or wext, please set HAS_WPA_SUPPLICANT=y and HAS_NATIVE_WPA_SUPPLICANT_SUPPORT=y"
#endif /* WPA_SUPPLICANT_SUPPORT */
#endif /* NATIVE_WPA_SUPPLICANT_SUPPORT */

#endif /* CONFIG_STA_SUPPORT */

#ifdef WSC_INCLUDED
#include "crypt_biginteger.h"
#include "crypt_dh.h"
#include "wsc_tlv.h"

#ifdef WSC_NFC_SUPPORT
#include "nfc.h"
#endif /* WSC_NFC_SUPPORT */
#endif /* WSC_INCLUDED */

#ifdef IKANOS_VX_1X0
#include "vr_ikans.h"
#endif /* IKANOS_VX_1X0 */



#ifdef DOT11W_PMF_SUPPORT
#include "pmf.h"
#endif /* DOT11W_PMF_SUPPORT */


#ifdef WAPI_SUPPORT
#include "wapi.h"
#endif /* WAPI_SUPPORT */


#ifdef WFD_SUPPORT
#include "wfd.h"
#endif /* WFD_SUPPORT */

#ifdef DOT11_VHT_AC
#include "vht.h"
#endif /* DOT11_VHT_AC */
#ifdef CONFIG_STA_SUPPORT
#include "sta_cfg.h"
#endif /* CONFIG_STA_SUPPORT */



#ifdef WORKQUEUE_BH
#include <linux/workqueue.h>
#endif /* WORKQUEUE_BH / */

#ifdef RTMP_FREQ_CALIBRATION_SUPPORT
#include "frq_cal.h"
#endif /* RTMP_FREQ_CALIBRATION_SUPPORT */

#ifdef TXBF_SUPPORT
#include "rt_txbf.h"
#endif /* TXBF_SUPPORT */


#ifdef RLT_MAC
#include "mac_ral/fce.h"
#endif /* RLT_MAC */

#ifdef CONFIG_SNIFFER_SUPPORT
#include "sniffer/sniffer.h"
#endif /* CONFIG_SNIFFER_SUPPORT */

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
#include "cfg80211extr.h"
#include "cfg80211_cmm.h"
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */

#endif /* __RT_CONFIG_H__ */
