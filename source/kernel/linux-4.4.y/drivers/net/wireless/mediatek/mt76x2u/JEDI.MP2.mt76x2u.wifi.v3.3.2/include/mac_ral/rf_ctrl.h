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


#ifndef __RF_CTRL_H__
#define __RF_CTRL_H__

#ifdef RTMP_MAC
#include "mac_ral/omac/ral_omac_rf_ctrl.h"
#endif /* RTMP_MAC */

#ifdef RLT_MAC
#include "mac_ral/nmac/ral_nmac_rf_ctrl.h"
#endif /* RLT_MAC */

/* =================================================================*/
/* Register format  for RFCTRL										      */
/* =================================================================*/

#define	RF_CSR_CFG	0x500

#ifdef RLT_RF

#define RF_BANK0	0
#define RF_BANK1	1
#define RF_BANK2	2
#define RF_BANK3	3
#define RF_BANK4	4
#define RF_BANK5	5
#define RF_BANK6	6
#define RF_BANK7	7
#define RF_BANK8	8
#define RF_BANK9	9
#define RF_BANK10	10
#define RF_BANK11	11
#define RF_BANK12	12
#define RF_BANK13	13
#define RF_BANK14	14
#define RF_BANK15	15

#define MAX_RF_ID	127
#define MAC_RF_BANK 7

/* @!Release
	RF_CSR_KICK:1
			Write - kick RF register read/write
				0: do nothing
				1: kick read/write process
			Read - Polling RF register read/write
				0: idle
				1: busy
	RF_CSR_RW:1
			0: read	 1: write
	rsv:12
	RF_CSR_REG_ID:10
			RF register ID, 0 for R0, 1 for R1 and so on
				Bits [17:15] 3 bits, indicates the bank number
				Bits [14:08] 7 bits, indicates the register number

	RF_CSR_DATA:8
			DATA written to/read from RF
*/
#endif /* RLT_RF */

typedef union _RF_CSR_CFG_STRUC {
#ifdef RT_BIG_ENDIAN
	struct {
		UINT32 Rsvd18:14;	/* Reserved */
		UINT32 RF_CSR_KICK:1;	/* kick RF register read/write */
		UINT32 RF_CSR_WR:1;	/* 0: read  1: write */
		UINT32 TESTCSR_RFACC_REGNUM:8;	/* RF register ID */
		UINT32 RF_CSR_DATA:8;	/* DATA */
	} non_bank;
#ifdef RLT_RF
#ifdef RT65xx
	struct {
		UINT32 RF_CSR_KICK:1;
		UINT32 RF_CSR_WR:1;
		UINT32 rsv18:12;
		UINT32 RF_CSR_REG_BANK:3;
		UINT32 RF_CSR_REG_ID:7;
		UINT32 RF_CSR_DATA:8;
	} bank_65xx;
#endif				/* RT65xx */
#endif				/* RLT_RF */
#else
	struct {
		UINT32 RF_CSR_DATA:8;
		UINT32 TESTCSR_RFACC_REGNUM:8;
		UINT32 RF_CSR_WR:1;
		UINT32 RF_CSR_KICK:1;
		UINT32 Rsvd18:14;
	} non_bank;
#ifdef RLT_RF
#ifdef RT65xx
	struct {
		UINT32 RF_CSR_DATA:8;
		UINT32 RF_CSR_REG_ID:7;
		UINT32 RF_CSR_REG_BANK:3;
		UINT32 rsv18:12;
		UINT32 RF_CSR_WR:1;
		UINT32 RF_CSR_KICK:1;
	} bank_65xx;
#endif				/* RT65xx */
#endif				/* RLT_RF */
#endif				/* RT_BIG_ENDIAN */
	UINT32 word;
} RF_CSR_CFG_STRUC;

#define	RF_PA_MODE_CCK_1M				(pAd->chipCap.PAModeCCK[0])
#define	RF_PA_MODE_CCK_2M				(pAd->chipCap.PAModeCCK[1])
#define	RF_PA_MODE_CCK_5M				(pAd->chipCap.PAModeCCK[2])
#define	RF_PA_MODE_CCK_11M				(pAd->chipCap.PAModeCCK[3])

#define	RF_PA_MODE_OFDM_6M				(pAd->chipCap.PAModeOFDM[0])
#define	RF_PA_MODE_OFDM_9M				(pAd->chipCap.PAModeOFDM[1])
#define	RF_PA_MODE_OFDM_12M				(pAd->chipCap.PAModeOFDM[2])
#define	RF_PA_MODE_OFDM_18M				(pAd->chipCap.PAModeOFDM[3])
#define	RF_PA_MODE_OFDM_24M				(pAd->chipCap.PAModeOFDM[4])
#define	RF_PA_MODE_OFDM_36M				(pAd->chipCap.PAModeOFDM[5])
#define	RF_PA_MODE_OFDM_48M				(pAd->chipCap.PAModeOFDM[6])
#define	RF_PA_MODE_OFDM_54M				(pAd->chipCap.PAModeOFDM[7])

#define	RF_PA_MODE_HT_MCS0				(pAd->chipCap.PAModeHT[0])
#define	RF_PA_MODE_HT_MCS1				(pAd->chipCap.PAModeHT[1])
#define	RF_PA_MODE_HT_MCS2				(pAd->chipCap.PAModeHT[2])
#define	RF_PA_MODE_HT_MCS3				(pAd->chipCap.PAModeHT[3])
#define	RF_PA_MODE_HT_MCS4				(pAd->chipCap.PAModeHT[4])
#define	RF_PA_MODE_HT_MCS5				(pAd->chipCap.PAModeHT[5])
#define	RF_PA_MODE_HT_MCS6				(pAd->chipCap.PAModeHT[6])
#define	RF_PA_MODE_HT_MCS7				(pAd->chipCap.PAModeHT[7])
#define	RF_PA_MODE_HT_MCS8				(pAd->chipCap.PAModeHT[8])
#define	RF_PA_MODE_HT_MCS9				(pAd->chipCap.PAModeHT[9])
#define	RF_PA_MODE_HT_MCS10				(pAd->chipCap.PAModeHT[10])
#define	RF_PA_MODE_HT_MCS11				(pAd->chipCap.PAModeHT[11])
#define	RF_PA_MODE_HT_MCS12				(pAd->chipCap.PAModeHT[12])
#define	RF_PA_MODE_HT_MCS13				(pAd->chipCap.PAModeHT[13])
#define	RF_PA_MODE_HT_MCS14				(pAd->chipCap.PAModeHT[14])
#define	RF_PA_MODE_HT_MCS15				(pAd->chipCap.PAModeHT[15])

#ifdef MT_RF
#define W_RFDATA 0x0524
#define R_RFDATA 0x052C
#define RF_CTRL 0x0528
#define RF_ADDR_MASK 0xfff
#define RF_ADDR(p) ((p) & 0xfff)
#define RF_R_W_CTRL (1 << 12)
#define RF_READY_MASK (1 << 13)
#define RF_READY(p) (((p) & RF_READY_MASK) == (0x0 << 13))
#define RF_IDX_MASK (1 << 16)
#define RF_IDX(p) (((p) & 0x1) << 16)
#endif /* MT_RF */

typedef struct _BANK_RF_REG_PAIR {
	UCHAR Bank;
	UCHAR Register;
	UCHAR Value;
} BANK_RF_REG_PAIR, *PBANK_RF_REG_PAIR;

typedef struct _R_M_W_REG {
	UINT32 Register;
	UINT32 ClearBitMask;
	UINT32 Value;
} R_M_W_REG, *PR_M_W_REG;

typedef struct _RF_R_M_W_REG {
	UCHAR Bank;
	UCHAR Register;
	UCHAR ClearBitMask;
	UCHAR Value;
} RF_R_M_W_REG, *PRF_R_M_W_REG;

#endif /* __RF_CTRL_H__ */
