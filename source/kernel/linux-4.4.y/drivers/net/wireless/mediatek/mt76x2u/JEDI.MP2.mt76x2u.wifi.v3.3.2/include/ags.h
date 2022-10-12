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

	All AGS (Adaptive Group Switching) Related Structure & Definition

***************************************************************************/

#ifndef __AGS_H__
#define __AGS_H__


extern UCHAR AGS1x1HTRateTable[];
extern UCHAR AGS2x2HTRateTable[];
extern UCHAR AGS3x3HTRateTable[];
#ifdef DOT11_VHT_AC
extern UCHAR Ags1x1VhtRateTable[];
extern UCHAR Ags2x2VhtRateTable[];
#endif /* DOT11_VHT_AC */

#define AGS_TX_QUALITY_WORST_BOUND	 8
#define AGS_QUICK_RA_TIME_INTERVAL	  50	/* 50ms */

/* The size, in bytes, of an AGS entry in the rate switch table */
#define SIZE_OF_AGS_RATE_TABLE_ENTRY	9

typedef struct _RTMP_RA_AGS_TB {
	UCHAR	ItemNo;

	UCHAR	STBC:1;
	UCHAR	ShortGI:1;
	UCHAR	BW:2;
	UCHAR	Mode:3;
	UCHAR	Rsv1:1;

	UCHAR Nss:2; // NSS_XXX (VHT only)
	UCHAR rsv2:6; // Reserved

	UCHAR	CurrMCS;
	UCHAR	TrainUp;
	UCHAR	TrainDown;
	UCHAR	downMcs;
	UCHAR	upMcs3;
	UCHAR	upMcs2;
	UCHAR	upMcs1;
}RTMP_RA_AGS_TB;


/* AGS control */
typedef struct _AGS_CONTROL {
	UCHAR MCSGroup; /* The MCS group under testing */
	UCHAR lastRateIdx;
} AGS_CONTROL,*PAGS_CONTROL;


/* The statistics information for AGS */
typedef struct _AGS_STATISTICS_INFO {
	CHAR	RSSI;
	ULONG	TxErrorRatio;
	ULONG	AccuTxTotalCnt;
	ULONG	TxTotalCnt;
	ULONG	TxSuccess;
	ULONG	TxRetransmit;
	ULONG	TxFailCount;
} AGS_STATISTICS_INFO, *PAGS_STATISTICS_INFO;


/* Support AGS (Adaptive Group Switching) */
#define SUPPORT_AGS(__pAd)		((__pAd)->rateAlg == RATE_ALG_AGS)

#ifdef DOT11_VHT_AC
#define AGS_IS_USING(__pAd, __pRateTable)	\
    (SUPPORT_AGS(__pAd) && \
     ((__pRateTable == AGS1x1HTRateTable) ||\
      (__pRateTable == AGS2x2HTRateTable) ||\
      (__pRateTable == AGS3x3HTRateTable) ||\
      (__pRateTable == Ags1x1VhtRateTable) ||\
      (__pRateTable == Ags2x2VhtRateTable)))
#else
#define AGS_IS_USING(__pAd, __pRateTable)	\
    (SUPPORT_AGS(__pAd) && \
     ((__pRateTable == AGS1x1HTRateTable) || \
      (__pRateTable == AGS2x2HTRateTable) || \
      (__pRateTable == AGS3x3HTRateTable)))
#endif /* DOT11_VHT_AC */

#endif /* __AGS_H__ */
