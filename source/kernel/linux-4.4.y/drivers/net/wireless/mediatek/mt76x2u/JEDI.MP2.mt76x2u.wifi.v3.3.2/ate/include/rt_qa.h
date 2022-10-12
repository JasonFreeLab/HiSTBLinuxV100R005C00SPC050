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


#ifndef __RT_QA_H__
#define __RT_QA_H__

#ifdef RALINK_QA
#ifndef RALINK_ATE
#error "For supporting QA GUI, please set HAS_ATE=y and HAS_QA_SUPPORT=y."
#endif /* RALINK_ATE */

#include "rt_ate.h"

typedef struct ate_racfghdr {
	UINT32 magic_no;
	USHORT command_type;
	USHORT command_id;
	USHORT length;
	USHORT sequence;
	USHORT status;
	UCHAR data[2046];
} __packed RACFGHDR, *pRACFGHDR;

/* Stop Transmission */
#define ATE_TXSTOP		    ((~(fATE_TX_ENABLE))&(~(fATE_TXCONT_ENABLE))\
	&(~(fATE_TXCARR_ENABLE))&(~(fATE_TXCARRSUPP_ENABLE)))
/* Stop Receiving Frames */
#define ATE_RXSTOP					(~(fATE_RX_ENABLE))

/* NOTE : may be different with chipset in the future ++ */
#define	BBP22_TXFRAME				0x00	/* Transmit Frames */
#define	BBP22_TXCONT_OR_CARRSUPP    0x80	/* Continuous Transmit or Carrier Suppression */
#define	BBP22_TXCARR		    0xc1	/* Transmit Carrier */
#define	BBP24_TXCONT		    0x00	/* Continuous Transmit */
#define	BBP24_CARRSUPP		    0x01	/* Carrier Suppression */
/* NOTE : may be different with chipset in the future -- */

/* Eth QA RACFG Command */
#define RACFG_MAGIC_NO			0x18142880
/* command id with Cmd Type == 0x0005(for iNIC)/0x0008(for others) */
#define RACFG_CMD_RF_WRITE_ALL			0x0000
#define RACFG_CMD_E2PROM_READ16			0x0001
#define RACFG_CMD_E2PROM_WRITE16		0x0002
#define RACFG_CMD_E2PROM_READ_ALL		0x0003
#define RACFG_CMD_E2PROM_WRITE_ALL		0x0004
#define RACFG_CMD_IO_READ				0x0005
#define RACFG_CMD_IO_WRITE				0x0006
#define RACFG_CMD_IO_READ_BULK			0x0007
#define RACFG_CMD_BBP_READ8				0x0008
#define RACFG_CMD_BBP_WRITE8			0x0009
#define RACFG_CMD_BBP_READ_ALL			0x000a
#define RACFG_CMD_GET_COUNTER			0x000b
#define RACFG_CMD_CLEAR_COUNTER			0x000c

#define RACFG_CMD_RSV1					0x000d
#define RACFG_CMD_RSV2					0x000e
#define RACFG_CMD_RSV3					0x000f

#define RACFG_CMD_TX_START				0x0010
#define RACFG_CMD_GET_TX_STATUS			0x0011
#define RACFG_CMD_TX_STOP				0x0012
#define RACFG_CMD_RX_START				0x0013
#define RACFG_CMD_RX_STOP				0x0014
#define RACFG_CMD_GET_NOISE_LEVEL		0x0015

#define RACFG_CMD_ATE_START				0x0080
#define RACFG_CMD_ATE_STOP				0x0081

#define RACFG_CMD_ATE_START_TX_CARRIER		0x0100
#define RACFG_CMD_ATE_START_TX_CONT			0x0101
#define RACFG_CMD_ATE_START_TX_FRAME		0x0102
#define RACFG_CMD_ATE_SET_BW		    0x0103
#define RACFG_CMD_ATE_SET_TX_POWER0		0x0104
#define RACFG_CMD_ATE_SET_TX_POWER1			0x0105
#define RACFG_CMD_ATE_SET_FREQ_OFFSET		0x0106
#define RACFG_CMD_ATE_GET_STATISTICS		0x0107
#define RACFG_CMD_ATE_RESET_COUNTER			0x0108
#define RACFG_CMD_ATE_SEL_TX_ANTENNA		0x0109
#define RACFG_CMD_ATE_SEL_RX_ANTENNA		0x010a
#define RACFG_CMD_ATE_SET_PREAMBLE			0x010b
#define RACFG_CMD_ATE_SET_CHANNEL			0x010c
#define RACFG_CMD_ATE_SET_ADDR1				0x010d
#define RACFG_CMD_ATE_SET_ADDR2				0x010e
#define RACFG_CMD_ATE_SET_ADDR3				0x010f
#define RACFG_CMD_ATE_SET_RATE				0x0110
#define RACFG_CMD_ATE_SET_TX_FRAME_LEN		0x0111
#define RACFG_CMD_ATE_SET_TX_FRAME_COUNT	0x0112
#define RACFG_CMD_ATE_START_RX_FRAME		0x0113
#define RACFG_CMD_ATE_E2PROM_READ_BULK		0x0114
#define RACFG_CMD_ATE_E2PROM_WRITE_BULK		0x0115
#define RACFG_CMD_ATE_IO_WRITE_BULK			0x0116
#define RACFG_CMD_ATE_BBP_READ_BULK			0x0117
#define RACFG_CMD_ATE_BBP_WRITE_BULK		0x0118
#define RACFG_CMD_ATE_RF_READ_BULK			0x0119
#define RACFG_CMD_ATE_RF_WRITE_BULK			0x011a
#define RACFG_CMD_ATE_SET_TX_POWER2			0x011b
#ifdef TXBF_SUPPORT
#define RACFG_CMD_ATE_TXBF_DUT_INIT		0x011c
#define RACFG_CMD_ATE_TXBF_LNA_CAL		0x011d
#define RACFG_CMD_ATE_TXBF_DIV_CAL		0x011e
#define RACFG_CMD_ATE_TXBF_PHASE_CAL		0x011f
#define RACFG_CMD_ATE_TXBF_GOLDEN_INIT		0x0120
#define RACFG_CMD_ATE_TXBF_VERIFY		0x0121
#endif /* TXBF_SUPPORT */
#ifdef RLT_RF
#define RACFG_CMD_ATE_RF_READ_BULK_BANK		0x0123
#define RACFG_CMD_ATE_RF_WRITE_BULK_BANK	0x0124
#endif /* RLT_RF */
#define RACFG_CMD_TX_START_V2				0x0125



/* QA RACFG Command for ate test from localhost */
#define RACFG_CMD_ATE_SHOW_PARAM 0xff00

/* ATE export paramters to uppler layer */
typedef struct __ATE_EX_PARAM {
	unsigned char mode;
	char TxPower0;
	char TxPower1;
#ifdef DOT11N_SS3_SUPPORT
	char TxPower2;
#endif				/* DOT11N_SS3_SUPPORT */
	char TxAntennaSel;
	char RxAntennaSel;
	unsigned char DA[MAC_ADDR_LEN];
	unsigned char SA[MAC_ADDR_LEN];
	unsigned char BSSID[MAC_ADDR_LEN];
	unsigned char MCS;
	unsigned char PhyMode;
	BOOLEAN ShortGI;
	BOOLEAN BW;
	unsigned int Channel;
	unsigned int TxLength;
	unsigned int TxCount;
	unsigned int RFFreqOffset;
	unsigned int IPG;
	unsigned int RxTotalCnt;
	unsigned int RxCntPerSec;
	char LastSNR0;
	char LastSNR1;
#ifdef DOT11N_SS3_SUPPORT
	char LastSNR2;
#endif				/* DOT11N_SS3_SUPPORT */
	char LastRssi0;
	char LastRssi1;
	char LastRssi2;
	char AvgRssi0;
	char AvgRssi1;
	char AvgRssi2;
	short AvgRssi0X8;
	short AvgRssi1X8;
	short AvgRssi2X8;
} ATE_EX_PARAM, *pATE_EX_PARAM;

NDIS_STATUS TXSTOP(IN PRTMP_ADAPTER pAd);

NDIS_STATUS RXSTOP(IN PRTMP_ADAPTER pAd);

#endif /* RALINK_QA */

#endif /* __RT_QA_H__ */
