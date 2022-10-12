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


#ifndef __RT_ATE_H__
#define __RT_ATE_H__

#ifdef RALINK_ATE
#ifndef STATS_COUNT_SUPPORT
#error "For ATE support, please set HAS_ATE=y and HAS_STATS_COUNT=y."
#endif /* !STATS_COUNT_SUPPORT */
#endif /* RALINK_ATE */

#include "mac_ral/rtmp_mac.h"
#include "chip/rtmp_phy.h"

/* TODO: shiang-6590, remove it after ATE code is re-organized!! */
#define BBP_R1			1
#define BBP_R3			3
#define BBP_R4			4
#define BBP_R21			21
#define BBP_R22			22
#define BBP_R24			24
#define BBP_R27			27
#define BBP_R50			50
#define BBP_R51			51
#define BBP_R52			52
#define BBP_R60			60
#define BBP_R66			66
#define BBP_R69			69
#define BBP_R70			70
#define BBP_R174			174
#define BBP_R182			182
/* TODO: ---End */

typedef struct _ATE_CHIP_STRUCT {
	/* functions */
	VOID(*ChannelSwitch) (PRTMP_ADAPTER pAd);
	INT(*TxPwrHandler) (PRTMP_ADAPTER pAd, char index);
	INT(*TxPwrEvaluation) (PRTMP_ADAPTER pAd);
	INT(*TssiCalibration) (PRTMP_ADAPTER pAd, PSTRING arg);
	INT(*ExtendedTssiCalibration) (PRTMP_ADAPTER pAd, PSTRING arg);
	VOID(*RxVGAInit) (PRTMP_ADAPTER pAd);
	VOID(*AsicSetTxRxPath) (PRTMP_ADAPTER pAd);
	VOID(*AdjustTxPower) (PRTMP_ADAPTER pAd);
	VOID(*AsicExtraPowerOverMAC) (PRTMP_ADAPTER pAd);
	VOID(*AsicCalibration) (PRTMP_ADAPTER pAd, UCHAR ate_mode);
	VOID(*TemperCompensation) (RTMP_ADAPTER * pAd);
#ifdef SINGLE_SKU_V2
	VOID(*do_ATE_single_sku) (RTMP_ADAPTER * pAd, BOOLEAN value);
#endif				/* endif */

	/* command handlers */
	INT(*Set_BW_Proc) (PRTMP_ADAPTER pAd, PSTRING arg);
	INT(*Set_FREQ_OFFSET_Proc) (PRTMP_ADAPTER pAd, PSTRING arg);

	/* variables */
	INT maxTxPwrCnt;
	BOOLEAN bBBPStoreTXCARR;
	BOOLEAN bBBPStoreTXCARRSUPP;
	BOOLEAN bBBPStoreTXCONT;
	BOOLEAN bBBPLoadATESTOP;

	/* TSSI related */
	INT32 tssi_slope[2];
	INT32 tssi_offset[3][2];
	INT32 pwr_diff_pre[2];
	INT32 ant_pwr_offset[2];
	INT32 curr_temperature;
} ATE_CHIP_STRUCT, *PATE_CHIP_STRUCT;

typedef union _CAPTURE_MODE_SHARE_MEMORY {
	struct {
		UINT32 LOW_BYTE0:8;
		UINT32 LOW_BYTE1:8;
		UINT32 HIGH_BYTE0:8;
		UINT32 HIGH_BYTE1:8;
	} field;
	UINT32 Value;
} CAPTURE_MODE_SHARE_MEMORY, *PCAPTURE_MODE_SHARE_MEMORY;

typedef struct _ATE_INFO {
	PATE_CHIP_STRUCT pChipStruct;
	UCHAR Mode;
	BOOLEAN PassiveMode;
#ifdef RT3350
	UCHAR PABias;
#endif				/* RT3350 */
	CHAR TxPower0;
	CHAR TxPower1;
#ifdef DOT11N_SS3_SUPPORT
	CHAR TxPower2;
#endif				/* DOT11N_SS3_SUPPORT */
	CHAR MinTxPowerBandA;	/* Power range of early chipsets is -7~15 in A band */
	CHAR MaxTxPowerBandA;	/* Power range of early chipsets is -7~15 in A band */
	CHAR TxAntennaSel;
	CHAR RxAntennaSel;
	USHORT TxInfoLen;
	USHORT TxWILen;
	TXINFO_STRUC TxInfo;	/* TxInfo */
	TXWI_STRUC TxWI;	/* TXWI */
	USHORT QID;
	UCHAR Addr1[MAC_ADDR_LEN];
	UCHAR Addr2[MAC_ADDR_LEN];
	UCHAR Addr3[MAC_ADDR_LEN];
	UCHAR Channel;
	UCHAR Payload;		/* Payload pattern */
	BOOLEAN bFixedPayload;
	UCHAR TxMethod;		/* Early chipsets must be applied old TXCONT/TXCARR/TXCARS mechanism. */
	UINT32 TxLength;
	UINT32 TxCount;
	UINT32 TxDoneCount;	/* Tx DMA Done */
	UINT32 RFFreqOffset;
	UINT32 IPG;
	BOOLEAN bRxFER;		/* Show Rx Frame Error Rate */
	BOOLEAN bQAEnabled;	/* QA is used. */
	BOOLEAN bQATxStart;	/* Have compiled QA in and use it to ATE tx. */
	BOOLEAN bQARxStart;	/* Have compiled QA in and use it to ATE rx. */
	BOOLEAN bAutoTxAlc;	/* Set Auto Tx Alc */
#ifdef SINGLE_SKU_V2
	BOOLEAN bDoSingleSKU;	/*Do Single SKU in ATE */
#endif				/* endif */
	BOOLEAN bAutoVcoCal;	/* Set Auto VCO periodic calibration. */
	BOOLEAN bLowTemperature;	/* Trigger Temperature Sensor */
#ifdef RTMP_INTERNAL_TX_ALC
#if defined(RT3350) || defined(RT3352)
	BOOLEAN bTSSICalbrEnableG;	/* Enable TSSI calibration */
	CHAR TssiRefPerChannel[CFG80211_NUM_OF_CHAN_2GHZ];
	CHAR TssiDeltaPerChannel[CFG80211_NUM_OF_CHAN_2GHZ];
#endif				/* defined(RT3350) || defined(RT3352) */
#endif				/* RTMP_INTERNAL_TX_ALC */
#ifdef TXBF_SUPPORT
	BOOLEAN bTxBF;		/* Enable Tx Bean Forming */
	SHORT txSoundingMode;	/* Sounding mode for non-QA ATE. 0=none, 1=Data Sounding, 2=NDP */
	UCHAR calParams[2];
#endif				/* TXBF_SUPPORT */
	UINT32 RxTotalCnt;
	UINT32 RxCntPerSec;
	UCHAR forceBBPReg;	/* force to not update the specific BBP register, now used for ATE TxBF */

	CHAR LastSNR0;		/* last received SNR */
	CHAR LastSNR1;		/* last received SNR for 2nd  antenna */
#ifdef DOT11N_SS3_SUPPORT
	CHAR LastSNR2;
#endif				/* DOT11N_SS3_SUPPORT */
	CHAR LastRssi0;		/* last received RSSI */
	CHAR LastRssi1;		/* last received RSSI for 2nd  antenna */
	CHAR LastRssi2;		/* last received RSSI for 3rd  antenna */
	CHAR AvgRssi0;		/* last 8 frames' average RSSI */
	CHAR AvgRssi1;		/* last 8 frames' average RSSI */
	CHAR AvgRssi2;		/* last 8 frames' average RSSI */
	SHORT AvgRssi0X8;	/* sum of last 8 frames' RSSI */
	SHORT AvgRssi1X8;	/* sum of last 8 frames' RSSI */
	SHORT AvgRssi2X8;	/* sum of last 8 frames' RSSI */
	CHAR MaxRssi0;		/* Maximum received RSSI */
	CHAR MaxRssi1;		/* Maximum received RSSI for 2nd  antenna */
	CHAR MaxRssi2;		/* Maximum received RSSI for 3rd  antenna */
	CHAR MinRssi0;		/* Minimum received RSSI */
	CHAR MinRssi1;		/* Minimum received RSSI for 2nd  antenna */
	CHAR MinRssi2;		/* Minimum received RSSI for 3rd  antenna */
	UINT32 NumOfAvgRssiSample;
	UINT32 Default_TX_PIN_CFG;
	USHORT HLen;		/* Header Length */

#ifdef RALINK_QA
	/* Tx frame */
	USHORT PLen;		/* Pattern Length */
	UCHAR Header[32];	/* Header buffer */
	UCHAR Pattern[32];	/* Pattern buffer */
	USHORT DLen;		/* Data Length */
	USHORT seq;
	UINT32 CID;
	RTMP_OS_PID AtePid;
	/* counters */
	UINT32 U2M;
	UINT32 OtherData;
	UINT32 Beacon;
	UINT32 OtherCount;
	UINT32 TxAc0;
	UINT32 TxAc1;
	UINT32 TxAc2;
	UINT32 TxAc3;
	UINT32 TxHCCA;
	UINT32 TxMgmt;
	UINT32 RSSI0;
	UINT32 RSSI1;
	UINT32 RSSI2;
	UINT32 SNR0;
	UINT32 SNR1;
#ifdef DOT11N_SS3_SUPPORT
	UINT32 SNR2;
#endif				/* DOT11N_SS3_SUPPORT */
	INT32 BF_SNR[3];	/* Last RXWI BF SNR. Units=0.25 dB */
	/* TxStatus : 0 --> task is idle, 1 --> task is running */
	UCHAR TxStatus;
#ifdef DOT11_VHT_AC
	UCHAR vht_nss;
#endif				/* DOT11_VHT_AC */
#endif				/* RALINK_QA */
#ifdef TXBF_SUPPORT
/* Assume 114 carriers (40MHz), 3x3, 8bits/coeff, + SNR + HT HEADER + MIMO CONTROL FIELD */
#define MAX_SOUNDING_RESPONSE_SIZE	(57*2*2*9+3+2+6)
	UCHAR sounding;
	UINT32 sounding_jiffies;
	CHAR soundingSNR[3];
	UINT32 LastRxRate;
	UINT32 LastTxRate;
	UINT32 soundingRespSize;	/* Size of Sounding response */
	UCHAR soundingResp[MAX_SOUNDING_RESPONSE_SIZE];	/* Entire Sounding response */
#endif				/* TXBF_SUPPORT */
	RALINK_TIMER_STRUCT PeriodicTimer;
	ULONG OneSecPeriodicRound;
	ULONG PeriodicRound;
	OS_NDIS_SPIN_LOCK TssiSemLock;
} ATE_INFO, *PATE_INFO;

/*
	Use bitmap to allow coexist of ATE_TXFRAME
	and ATE_RXFRAME(i.e.,to support LoopBack mode).
*/
#define fATE_IDLE					0x00
#define fATE_TX_ENABLE				0x01
#define fATE_RX_ENABLE				0x02
#define fATE_TXCONT_ENABLE			0x04
#define fATE_TXCARR_ENABLE			0x08
#define fATE_TXCARRSUPP_ENABLE		0x10
#define fATE_RESERVED_1				0x20
#define fATE_RESERVED_2				0x40
#define fATE_EXIT					0x80

/* Enter/Reset ATE */
#define	ATE_START		    (fATE_IDLE)
/* Stop/Exit ATE */
#define	ATE_STOP		    (fATE_EXIT)
/* Continuous Transmit Frames (without time gap) */
#define	ATE_TXCONT		    ((fATE_TX_ENABLE)|(fATE_TXCONT_ENABLE))
/* Transmit Carrier */
#define	ATE_TXCARR		    ((fATE_TX_ENABLE)|(fATE_TXCARR_ENABLE))
/* Transmit Carrier Suppression (information without carrier) */
#define	ATE_TXCARRSUPP		    ((fATE_TX_ENABLE)|(fATE_TXCARRSUPP_ENABLE))
/* Transmit Frames */
#define	ATE_TXFRAME		    (fATE_TX_ENABLE)
/* Receive Frames */
#define	ATE_RXFRAME		    (fATE_RX_ENABLE)


#ifdef RTMP_INTERNAL_TX_ALC
#define EEPROM_TSSI_ENABLE 0x36
#define EEPROM_TSSI_MODE_EXTEND 0x76

#define ATE_MDSM_NORMAL_TX_POWER						0x00
#define ATE_MDSM_DROP_TX_POWER_BY_6dBm					0x01
#define ATE_MDSM_DROP_TX_POWER_BY_12dBm					0x02
#define ATE_MDSM_ADD_TX_POWER_BY_6dBm					0x03
#define ATE_MDSM_BBP_R1_STATIC_TX_POWER_CONTROL_MASK	0x03
#endif /* RTMP_INTERNAL_TX_ALC */

#define	LEN_OF_ARG 16
#define ATE_ON(_p)		(((_p)->ate.Mode) != ATE_STOP)
#define TX_METHOD_0 0		/* Early chipsets must be applied this original TXCONT/TXCARR/TXCARS mechanism. */
#define TX_METHOD_1 1		/* Default TXCONT/TXCARR/TXCARS mechanism is TX_METHOD_1 */
#define ANT_ALL 0
#define ANT_0 1
#define ANT_1 2
#ifdef DOT11N_SS3_SUPPORT
#define ANT_2 3
#endif /* DOT11N_SS3_SUPPORT */

#define ATE_ASIC_CALIBRATION(__pAd, __ate_mode)	\
do {	\
		if (__pAd->ate.pChipStruct->AsicCalibration != NULL)	\
			__pAd->ate.pChipStruct->AsicCalibration(__pAd, __ate_mode);	\
} while (0)

#define ATE_MAC_TX_ENABLE(_A, _I, _pV)	\
{										\
	RTMP_IO_READ32(_A, _I, _pV);		\
	(*(_pV)) |= (1 << 2);				\
	RTMP_IO_WRITE32(_A, _I, (*(_pV)));	\
}

#define ATE_MAC_TX_DISABLE(_A, _I, _pV)	\
{										\
	RTMP_IO_READ32(_A, _I, _pV);		\
	(*(_pV)) &= ~(1 << 2);				\
	RTMP_IO_WRITE32(_A, _I, (*(_pV)));	\
}

#define ATE_MAC_RX_ENABLE(_A, _I, _pV)	\
{										\
	RTMP_IO_READ32(_A, _I, _pV);		\
	(*(_pV)) |= (1 << 3);				\
	RTMP_IO_WRITE32(_A, _I, (*(_pV)));	\
}

#define ATE_MAC_RX_DISABLE(_A, _I, _pV)	\
{										\
	RTMP_IO_READ32(_A, _I, _pV);		\
	(*(_pV)) &= ~(1 << 3);				\
	RTMP_IO_WRITE32(_A, _I, (*(_pV)));	\
}

/* Set MAC_SYS_CTRL(0x1004) Continuous Tx Production Test (bit4) = 1. */
#define ATE_MAC_TX_CTS_ENABLE(_A, _I, _pV)	\
{											\
	RTMP_IO_READ32(_A, _I, _pV);			\
	(*(_pV)) |= (1 << 4);					\
	RTMP_IO_WRITE32(_A, _I, (*(_pV)));		\
}

/* Clear MAC_SYS_CTRL(0x1004) Continuous Tx Production Test (bit4) = 0. */
#define ATE_MAC_TX_CTS_DISABLE(_A, _I, _pV)	\
{											\
	RTMP_IO_READ32(_A, _I, _pV);			\
	(*(_pV)) &= ~(1 << 4);					\
	RTMP_IO_WRITE32(_A, _I, (*(_pV)));		\
}

/* Clear BBP R22 to reset Tx Mode (bit7~bit0) = 0. */
#ifdef RTMP_BBP
#define ATE_BBP_RESET_TX_MODE(_A, _I, _pV)			\
{													\
	ATE_BBP_IO_READ8_BY_REG_ID(_A, _I, _pV);		\
	(*(_pV)) &= (0x00);							\
	ATE_BBP_IO_WRITE8_BY_REG_ID(_A, _I, (*(_pV)));	\
}
#endif /* RTMP_BBP */

/* Set BBP R22 to start Continuous Tx Mode (bit7) = 1. */
#define ATE_BBP_START_CTS_TX_MODE(_A, _I, _pV)		\
{													\
	ATE_BBP_IO_READ8_BY_REG_ID(_A, _I, _pV);		\
	(*(_pV)) |= (1 << 7);							\
	ATE_BBP_IO_WRITE8_BY_REG_ID(_A, _I, (*(_pV)));	\
}

/* Clear BBP R22 to stop Continuous Tx Mode (bit7) = 0. */
#define ATE_BBP_STOP_CTS_TX_MODE(_A, _I, _pV)		\
{													\
	ATE_BBP_IO_READ8_BY_REG_ID(_A, _I, _pV);		\
	(*(_pV)) &= ~(1 << 7);							\
	ATE_BBP_IO_WRITE8_BY_REG_ID(_A, _I, (*(_pV)));	\
}

/* Set BBP R24 to send out Continuous Tx sin wave (bit0) = 1. */
#define ATE_BBP_CTS_TX_SIN_WAVE_ENABLE(_A, _I, _pV)	\
{													\
	ATE_BBP_IO_READ8_BY_REG_ID(_A, _I, _pV);		\
	(*(_pV)) |= (1 << 0);							\
	ATE_BBP_IO_WRITE8_BY_REG_ID(_A, _I, (*(_pV)));	\
}

/* Clear BBP R24 to stop Continuous Tx sin wave (bit0) = 0. */
#define ATE_BBP_CTS_TX_SIN_WAVE_DISABLE(_A, _I, _pV)	\
{													\
	ATE_BBP_IO_READ8_BY_REG_ID(_A, _I, _pV);		\
	(*(_pV)) &= ~(1 << 0);							\
	ATE_BBP_IO_WRITE8_BY_REG_ID(_A, _I, (*(_pV)));	\
}

/*
==========================================================================
	Description:
		This routine sets initial value of VGA in the RX chain.
		AGC is the abbreviation of "Automatic Gain Controller",
		while VGA (Variable Gain Amplifier) is a part of AGC loop.
		(i.e., VGA + level detector + feedback loop = AGC)

    Return:
	VOID
==========================================================================
*/
#define ATE_CHIP_RX_VGA_GAIN_INIT(__pAd) do {		\
	if (__pAd->ate.pChipStruct->RxVGAInit != NULL)	\
		__pAd->ate.pChipStruct->RxVGAInit(__pAd);	\
} while (0)

#define ATE_CHIP_SET_TX_RX_PATH(__pAd)	do {				\
	if (__pAd->ate.pChipStruct->AsicSetTxRxPath != NULL)	\
		__pAd->ate.pChipStruct->AsicSetTxRxPath(__pAd);		\
} while (0)


#ifdef RTMP_MAC_USB
#define ATE_BBP_IO_READ8_BY_REG_ID(_A, _I, _pV)	   RTMP_BBP_IO_READ8_BY_REG_ID(_A, _I, _pV)
#define ATE_BBP_IO_WRITE8_BY_REG_ID(_A, _I, _V)	   RTMP_BBP_IO_WRITE8_BY_REG_ID(_A, _I, _V)

#define BULK_OUT_LOCK(pLock, IrqFlags)		RTMP_IRQ_LOCK(pLock, IrqFlags)
#define BULK_OUT_UNLOCK(pLock, IrqFlags)	RTMP_IRQ_UNLOCK(pLock, IrqFlags)

VOID ATE_RTUSBBulkOutDataPacket(IN PRTMP_ADAPTER pAd, IN UCHAR BulkOutPipeId);

VOID ATE_RTUSBCancelPendingBulkInIRP(IN PRTMP_ADAPTER pAd);

VOID ATEResetBulkIn(IN PRTMP_ADAPTER pAd);

INT ATEResetBulkOut(IN PRTMP_ADAPTER pAd);
#endif /* RTMP_MAC_USB */

INT DefaultATETxPwrHandler(IN PRTMP_ADAPTER pAd, IN char index);

#ifdef WCX_SUPPORT
INT32 do_meta_cmd(INT32 ioctl_cmd, PRTMP_ADAPTER pAd, RTMP_IOCTL_INPUT_STRUCT * WRQ,
		  PSTRING * wrq_name);
#endif /* endif */

#ifdef RALINK_QA
VOID ATE_QA_Statistics(IN RTMP_ADAPTER * pAd,
		       IN RXWI_STRUC * pRxWI, IN RXINFO_STRUC * pRxInfo, IN PHEADER_802_11 pHeader);

INT RtmpDoAte(IN RTMP_ADAPTER * pAd, IN RTMP_IOCTL_INPUT_STRUCT * wrq, IN PSTRING wrq_name);

INT Set_TxStop_Proc(IN RTMP_ADAPTER * pAd, IN PSTRING arg);

INT Set_RxStop_Proc(IN RTMP_ADAPTER * pAd, IN PSTRING arg);

#ifdef DBG
INT Set_EERead_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_EEWrite_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_BBPRead_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_BBPWrite_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_RFWrite_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* DBG */
#endif /* RALINK_QA */

#ifdef RTMP_RF_RW_SUPPORT
#ifdef RLT_RF
#define ATE_RF_IO_READ8_BY_REG_ID(_A, _B, _I, _pV)     rlt_rf_read(_A, _B, _I, _pV)
#define ATE_RF_IO_WRITE8_BY_REG_ID(_A, _B, _I, _V)     rlt_rf_write(_A, _B, _I, _V)
#endif /* RLT_RF */
#ifndef RLT_RF
#define ATE_RF_IO_READ8_BY_REG_ID(_A, _I, _pV)	   RT30xxReadRFRegister(_A, _I, _pV)
#define ATE_RF_IO_WRITE8_BY_REG_ID(_A, _I, _V)	   RT30xxWriteRFRegister(_A, _I, _V)
#endif /* !RLT_RF */
#endif /* RTMP_RF_RW_SUPPORT */

VOID rt_ee_read_all(IN PRTMP_ADAPTER pAd, OUT USHORT *Data);

VOID rt_ee_write_all(IN PRTMP_ADAPTER pAd, IN USHORT *Data);

VOID rt_ee_write_bulk(IN PRTMP_ADAPTER pAd, IN USHORT *Data, IN USHORT offset, IN USHORT length);

INT Set_ATE_SET_AUTORESP_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_GET_EFUSE_MODE_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_GET_KFREE_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_DA_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_SA_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_BSSID_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);


INT Set_ATE_CHANNEL_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_INIT_CHAN_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ADCDump_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION)
INT Set_ATE_TSSI_CALIBRATION_EX_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) */

#ifdef RTMP_INTERNAL_TX_ALC
INT Set_ATE_TSSI_CALIBRATION_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TSSI_CALIBRATION_EX_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);


#if defined(RT3350) || defined(RT3352)
INT RT335x_Set_ATE_TSSI_CALIBRATION_ENABLE_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

CHAR InsertTssi(IN UCHAR InChannel,
		IN UCHAR Channel0, IN UCHAR Channel1, IN CHAR Tssi0, IN CHAR Tssi1);

INT RT335xATETssiCalibrationExtend(IN struct _RTMP_ADAPTER *pAd, IN PSTRING arg);
#endif /* defined(RT3350) || defined(RT3352) */

CHAR ATEGetDesiredTSSI(IN PRTMP_ADAPTER pAd);

#endif /* RTMP_INTERNAL_TX_ALC */

#ifdef RTMP_TEMPERATURE_CALIBRATION
INT Set_ATE_TEMP_CAL_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_SHOW_TSSI_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* RTMP_TEMPERATURE_CALIBRATION */


#ifdef RTMP_TEMPERATURE_COMPENSATION

INT Set_ATE_READ_EXTERNAL_TSSI_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* RTMP_TEMPERATURE_COMPENSATION */

INT Set_ATE_TX_POWER0_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_POWER1_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#ifdef DOT11N_SS3_SUPPORT
INT Set_ATE_TX_POWER2_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* DOT11N_SS3_SUPPORT */

INT Set_ATE_TX_POWER_EVALUATION_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_Antenna_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_RX_Antenna_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

VOID DefaultATEAsicExtraPowerOverMAC(IN PRTMP_ADAPTER pAd);

VOID ATEAsicExtraPowerOverMAC(IN PRTMP_ADAPTER pAd);
#ifdef RT3350
INT Set_ATE_PA_Bias_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* RT3350 */

INT Default_Set_ATE_TX_FREQ_OFFSET_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_FREQ_OFFSET_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Default_Set_ATE_TX_BW_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_BW_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_LENGTH_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_COUNT_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_MCS_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_STBC_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_MODE_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TX_GI_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_RX_FER_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Read_RF_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#if (!defined(RTMP_RF_RW_SUPPORT)) && (!defined(RLT_RF))
INT Set_ATE_Write_RF1_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Write_RF2_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Write_RF3_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Write_RF4_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* (!defined(RTMP_RF_RW_SUPPORT)) && (!defined(RLT_RF)) */

INT Set_ATE_Load_E2P_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#ifdef RTMP_EFUSE_SUPPORT
INT Set_ATE_Load_E2P_From_Buf_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* RTMP_EFUSE_SUPPORT */

INT Set_ATE_Read_E2P_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#ifdef LED_CONTROL_SUPPORT
#endif /* LED_CONTROL_SUPPORT */

INT Set_ATE_AUTO_ALC_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TEMP_SENSOR_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_SINGLE_SKU_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_IPG_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Payload_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Fixed_Payload_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#ifdef TXBF_SUPPORT
INT Set_ATE_TXBF_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TXSOUNDING_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TXBF_DIVCAL_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TXBF_LNACAL_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TXBF_INIT_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TXBF_CAL_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

#ifdef MT76x2
INT Set_ATE_TXBF_New_CAL_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_New_Phase_Verify(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* endif */

INT Set_ATE_TXBF_GOLDEN_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TXBF_VERIFY_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_TXBF_VERIFY_NoComp_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_ForceBBP_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* TXBF_SUPPORT */


INT Set_ATE_Show_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Help_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

VOID DefaultATEAsicAdjustTxPower(IN PRTMP_ADAPTER pAd);



#ifdef MT76x2
INT Set_ATE_DO_CALIBRATION_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);

INT Set_ATE_Load_CR_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg);
#endif /* MT76x2 */

VOID ATEAsicAdjustTxPower(IN PRTMP_ADAPTER pAd);

VOID ATESampleRssi(IN PRTMP_ADAPTER pAd, IN RXWI_STRUC * pRxWI);

INT ATESetUpNDPAFrame(IN PRTMP_ADAPTER pAd, IN UINT32 TxIdx);


#ifdef RTMP_MAC_USB
INT TxDmaBusy(IN PRTMP_ADAPTER pAd);

INT RxDmaBusy(IN PRTMP_ADAPTER pAd);

VOID RtmpDmaEnable(IN PRTMP_ADAPTER pAd, IN INT Enable);

INT ATESetUpFrame(IN PRTMP_ADAPTER pAd, IN UINT32 TxIdx);

VOID RTUSBRejectPendingPackets(IN PRTMP_ADAPTER pAd);
#endif /* RTMP_MAC_USB */


NDIS_STATUS ChipStructAssign(IN PRTMP_ADAPTER pAd);

NDIS_STATUS ATEInit(IN PRTMP_ADAPTER pAd);

#ifdef RALINK_QA
VOID ReadQATxTypeFromBBP(IN PRTMP_ADAPTER pAd);
#endif /* RALINK_QA */

#ifdef RTMP_BBP
NDIS_STATUS ATEBBPWriteWithRxChain(IN RTMP_ADAPTER * pAd,
				   IN UCHAR bbpId, IN CHAR bbpVal, IN RX_CHAIN_IDX rx_ch_idx);
#endif /* RTMP_BBP */

VOID ATEPeriodicExec(IN PVOID SystemSpecific1,
		     IN PVOID FunctionContext, IN PVOID SystemSpecific2, IN PVOID SystemSpecific3);

VOID ATEAsicSetTxRxPath(RTMP_ADAPTER *pAd);

VOID RtmpRfIoWrite(RTMP_ADAPTER *pAd);

VOID ATEAsicSwitchChannel(RTMP_ADAPTER *pAd);

VOID BbpSoftReset(RTMP_ADAPTER *pAd);


#endif /* __RT_ATE_H__ */
