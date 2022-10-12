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


#ifdef RTMP_FREQ_CALIBRATION_SUPPORT
#ifdef CONFIG_STA_SUPPORT

#include	"rt_config.h"

/*
	Sometimes frequency will be shift we need to adjust it when
	the frequencey shift.
*/
VOID InitFrequencyCalibrationMode(PRTMP_ADAPTER pAd, UINT8 Mode)
{
#ifdef RTMP_BBP
	BBP_R179_STRUC BbpR179 = { {0}
	};
	BBP_R180_STRUC BbpR180 = { {0}
	};
	BBP_R182_STRUC BbpR182 = { {0}
	};

	/* TODO: shiang-6590, fix me, I don't know which MODE0 yet for RLT series! */
	if (pAd->chipCap.hif_type == HIF_RTMP) {
		if (Mode == FREQ_CAL_INIT_MODE0) {
			/* Initialize the RX_END_STATUS (1, 5) for "Rx OFDM/CCK frequency offset report" */
			BbpR179.field.DataIndex1 = 1;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R179, BbpR179.byte);
			BbpR180.field.DataIndex2 = 5;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R180, BbpR180.byte);
			BbpR182.field.DataArray = BBP_R57;	/* Rx OFDM/CCK frequency offset report */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R182, BbpR182.byte);
		} else if (Mode == FREQ_CAL_INIT_MODE1) {
			/* Initialize the RX_END_STATUS (1, 3) for "Rx OFDM/CCK frequency offset report" */
			BbpR179.field.DataIndex1 = 1;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R179, BbpR179.byte);
			BbpR180.field.DataIndex2 = 3;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R180, BbpR180.byte);
			BbpR182.field.DataArray = BBP_R57;	/* Rx OFDM/CCK frequency offset report */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R182, BbpR182.byte);
		} else if (Mode == FREQ_CAL_INIT_MODE2) {
			/* Initialize the RX_END_STATUS (1) for "Rx OFDM/CCK frequency offset report" */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R142, 1);
			/* Rx OFDM/CCK frequency offset report */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R143, BBP_R57);
		} else {
			DBGPRINT(RT_DEBUG_ERROR, ("%s:Unknow mode = %d\n", __func__, Mode));
		}
	} else
#endif /* RTMP_BBP */
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s:Unknow mode = %d\n", __func__, Mode));
	}
}

/* Initialize the frequency calibration*/
VOID InitFrequencyCalibration(IN PRTMP_ADAPTER pAd)
{
	if (pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration == TRUE) {
		DBGPRINT(RT_DEBUG_ERROR, ("---> %s\n", __func__));

		InitFrequencyCalibrationMode(pAd, pAd->chipCap.FreqCalInitMode);

		StopFrequencyCalibration(pAd);

		DBGPRINT(RT_DEBUG_ERROR, ("%s: frequency offset in the EEPROM = %d\n",
					  __func__, pAd->RfFreqOffset));

		DBGPRINT(RT_DEBUG_ERROR, ("<--- %s\n", __func__));
	}
}

/* To stop the frequency calibration algorithm*/
VOID StopFrequencyCalibration(IN PRTMP_ADAPTER pAd)
{
	if (pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration == TRUE) {
		DBGPRINT(RT_DEBUG_TRACE, ("---> %s\n", __func__));

		/* Base on the frequency offset of the EEPROM */
		/* C1 value control - Crystal calibration */
		pAd->FreqCalibrationCtrl.AdaptiveFreqOffset = (0x7F & ((CHAR) (pAd->RfFreqOffset)));

		pAd->FreqCalibrationCtrl.LatestFreqOffsetOverBeacon = INVALID_FREQUENCY_OFFSET;
		pAd->FreqCalibrationCtrl.bSkipFirstFrequencyCalibration = TRUE;

		DBGPRINT(RT_DEBUG_TRACE,
			 ("%s: pAd->FreqCalibrationCtrl.AdaptiveFreqOffset = 0x%X\n", __func__,
			  pAd->FreqCalibrationCtrl.AdaptiveFreqOffset));

		DBGPRINT(RT_DEBUG_TRACE, ("<--- %s\n", __func__));
	}
}

VOID FrequencyCalibrationMode(PRTMP_ADAPTER pAd, UINT8 Mode)
{
	UCHAR RFValue = 0;

	if (Mode == FREQ_CAL_MODE0) {
		RT30xxReadRFRegister(pAd, RF_R23, (UCHAR *) (&RFValue));
		RFValue =
		    ((RFValue & ~0x7F) | (pAd->FreqCalibrationCtrl.AdaptiveFreqOffset & 0x7F));
		RFValue = RFValue < 0x5F ? RFValue : 0x5F;
		pAd->FreqCalibrationCtrl.AdaptiveFreqOffset = RFValue;	/* Keep modified RF R23 value */
		RT30xxWriteRFRegister(pAd, RF_R23, RFValue);
		RT30xxReadRFRegister(pAd, RF_R07, (UCHAR *) (&RFValue));
		/* Tune_en (initiate VCO calibration (reset after completion)) */
		RFValue = ((RFValue & ~0x01) | 0x01);
		RT30xxWriteRFRegister(pAd, RF_R07, RFValue);
	} else if (Mode == FREQ_CAL_MODE1) {
		/* Adjust the frequency offset and keep the modified value in AdaptiveFreqOffset */
		RTMPAdjustFrequencyOffset(pAd, &pAd->FreqCalibrationCtrl.AdaptiveFreqOffset);

		/* vcocal_en (initiate VCO calibration (reset after completion))
		 * - It should be at the end of RF configuration. */
		RTMP_WriteRF(pAd, RF_R03, 0x80, 0x80);
	} else
		DBGPRINT(RT_DEBUG_ERROR, ("Unknown FrqCalibration Mode\n"));
}

/* The frequency calibration algorithm*/
VOID FrequencyCalibration(IN PRTMP_ADAPTER pAd)
{

	/*BOOLEAN bUpdateRFR = FALSE; */
	CHAR HighFreqTriggerPoint = 0, LowFreqTriggerPoint = 0;
	CHAR DecreaseFreqOffset = 0, IncreaseFreqOffset = 0;

#ifdef MT76x2
	if (IS_MT76x2(pAd)) {
		PFREQUENCY_CALIBRATION_CONTROL pFrqCal = &pAd->FreqCalibrationCtrl;
		CHAR upBound = 0, lowBound = 0;

		if (pFrqCal->bEnableFrequencyCalibration &&
		    pFrqCal->LatestFreqOffsetOverBeacon != INVALID_FREQUENCY_OFFSET) {
			if (pFrqCal->BeaconPhyMode == MODE_CCK) {
				upBound = 4;
				lowBound = -4;
			} else {
				/* Beacon on OFDM Mode */
				upBound = 32;
				lowBound = -32;
			}
		}

		if ((pFrqCal->LatestFreqOffsetOverBeacon >= upBound) ||
		    (pFrqCal->LatestFreqOffsetOverBeacon <= lowBound)) {
			pFrqCal->bApproachFrequency = TRUE;
		} else {
			pFrqCal->bApproachFrequency = FALSE;
		}

		if (pFrqCal->bApproachFrequency == TRUE) {
			u32 value = 0;

			read_reg(pAd, 0x40, XO_CTRL5, &value);
			DBGPRINT(RT_DEBUG_TRACE, ("FRQ:	 Read Value => %08x\n", value));
			pFrqCal->AdaptiveFreqOffset = (value & ~0xffff80ff) >> 8;

			if (pFrqCal->LatestFreqOffsetOverBeacon > 0) {
				if (pFrqCal->AdaptiveFreqOffset > 0)
					pFrqCal->AdaptiveFreqOffset--;
			} else {
				if (pFrqCal->AdaptiveFreqOffset < 0x7F)
					pFrqCal->AdaptiveFreqOffset++;
			}

			value = (value & 0xffff80ff) | (pFrqCal->AdaptiveFreqOffset << 8);
			DBGPRINT(RT_DEBUG_TRACE, ("FRQ:	 After just Value => %08x\n", value));
			write_reg(pAd, 0x40, XO_CTRL5, value);
		}

		return;
	}
#endif /* MT76x2 */

	/* Frequency calibration period: */
	/* a) 10 seconds: Check the reported frequency offset */
	/* b) 500 ms: Update the RF frequency if possible */
	if ((pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration == TRUE) &&
	    (((pAd->FreqCalibrationCtrl.bApproachFrequency == FALSE)
	      && ((pAd->Mlme.PeriodicRound % FREQUENCY_CALIBRATION_PERIOD) == 0))
	     || ((pAd->FreqCalibrationCtrl.bApproachFrequency == TRUE)
		 && ((pAd->Mlme.PeriodicRound % (FREQUENCY_CALIBRATION_PERIOD / 20)) == 0)))) {
		DBGPRINT(RT_DEBUG_INFO, ("---> %s\n", __func__));

		if (pAd->FreqCalibrationCtrl.bSkipFirstFrequencyCalibration == TRUE) {
			pAd->FreqCalibrationCtrl.bSkipFirstFrequencyCalibration = FALSE;

			DBGPRINT(RT_DEBUG_INFO,
				 ("%s: Skip cuurent frequency calibration (avoid calibrating frequency at the time the STA is just link-up)\n",
				  __func__));
		} else {
			if (pAd->FreqCalibrationCtrl.LatestFreqOffsetOverBeacon !=
			    INVALID_FREQUENCY_OFFSET) {
				if (pAd->FreqCalibrationCtrl.BeaconPhyMode == MODE_CCK) {	/* CCK */
					{
						HighFreqTriggerPoint =
						    HIGH_FREQUENCY_TRIGGER_POINT_CCK;
						LowFreqTriggerPoint =
						    LOW_FREQUENCY_TRIGGER_POINT_CCK;

						DecreaseFreqOffset = DECREASE_FREQUENCY_OFFSET_CCK;
						IncreaseFreqOffset = INCREASE_FREQUENCY_OFFSET_CCK;
					}
				} else {	/* OFDM */

					{
						HighFreqTriggerPoint =
						    HIGH_FREQUENCY_TRIGGER_POINT_OFDM;
						LowFreqTriggerPoint =
						    LOW_FREQUENCY_TRIGGER_POINT_OFDM;

						DecreaseFreqOffset = DECREASE_FREQUENCY_OFFSET_OFDM;
						IncreaseFreqOffset = INCREASE_FREQUENCY_OFFSET_OFDM;
					}
				}

				if ((pAd->FreqCalibrationCtrl.LatestFreqOffsetOverBeacon >=
				     HighFreqTriggerPoint)
				    || (pAd->FreqCalibrationCtrl.LatestFreqOffsetOverBeacon <=
					LowFreqTriggerPoint)) {
					pAd->FreqCalibrationCtrl.bApproachFrequency = TRUE;
				}

				if (pAd->FreqCalibrationCtrl.bApproachFrequency == TRUE) {
					if ((pAd->FreqCalibrationCtrl.LatestFreqOffsetOverBeacon <=
					     DecreaseFreqOffset)
					    && (pAd->FreqCalibrationCtrl.
						LatestFreqOffsetOverBeacon >= IncreaseFreqOffset)) {
						/* Stop approaching frquency if -10 < reported frequency offset < 10 */
						pAd->FreqCalibrationCtrl.bApproachFrequency = FALSE;
					} else if (pAd->FreqCalibrationCtrl.
						   LatestFreqOffsetOverBeacon >
						   DecreaseFreqOffset) {
						pAd->FreqCalibrationCtrl.AdaptiveFreqOffset--;
						DBGPRINT(RT_DEBUG_TRACE,
							 ("%s: -- frequency offset = 0x%X\n",
							  __func__,
							  pAd->FreqCalibrationCtrl.
							  AdaptiveFreqOffset));
						FrequencyCalibrationMode(pAd,
									 pAd->chipCap.FreqCalMode);
					} else if (pAd->FreqCalibrationCtrl.
						   LatestFreqOffsetOverBeacon <
						   IncreaseFreqOffset) {
						pAd->FreqCalibrationCtrl.AdaptiveFreqOffset++;
						DBGPRINT(RT_DEBUG_TRACE,
							 ("%s: ++ frequency offset = 0x%X\n",
							  __func__,
							  pAd->FreqCalibrationCtrl.
							  AdaptiveFreqOffset));
						FrequencyCalibrationMode(pAd,
									 pAd->chipCap.FreqCalMode);
					}
				}

				DBGPRINT(RT_DEBUG_INFO,
					 ("%s: AdaptiveFreqOffset = %d, LatestFreqOffsetOverBeacon = %d, bApproachFrequency = %d\n",
					  __func__, pAd->FreqCalibrationCtrl.AdaptiveFreqOffset,
					  pAd->FreqCalibrationCtrl.LatestFreqOffsetOverBeacon,
					  pAd->FreqCalibrationCtrl.bApproachFrequency));

			}
		}

		DBGPRINT(RT_DEBUG_INFO, ("<--- %s\n", __func__));
	}
}

inline CHAR GetFrequencyOffsetField(PRTMP_ADAPTER pAd, RXWI_STRUC *pRxWI, UINT8 RxWIFrqOffsetField)
{
	CHAR FreqOffset = 0;

	if (RxWIFrqOffsetField == RXWI_FRQ_OFFSET_FIELD0) {
#ifdef RLT_MAC
		if (pAd->chipCap.hif_type == HIF_RLT)
				FreqOffset = (CHAR) (pRxWI->RXWI_N.bbp_rxinfo[1]);
#endif /* RLT_MAC */
#ifdef RTMP_MAC
		if (pAd->chipCap.hif_type == HIF_RTMP)
			FreqOffset = (CHAR) (pRxWI->RXWI_O.SNR1);
#endif /* RTMP_MAC */
	} else if (RxWIFrqOffsetField == RXWI_FRQ_OFFSET_FIELD1) {
#ifdef RLT_MAC
		if (pAd->chipCap.hif_type == HIF_RTMP)
				FreqOffset = (CHAR) (pRxWI->RXWI_N.bbp_rxinfo[4]);
#endif /* RLT_MAC */
#ifdef RTMP_MAC
		if (pAd->chipCap.hif_type == HIF_RTMP)
			FreqOffset = (CHAR) (pRxWI->RXWI_O.FOFFSET);
#endif /* RTMP_MAC */
	} else
		DBGPRINT(RT_DEBUG_ERROR,
			 ("%s:Unknow Frequency Offset location(%d)\n", __func__,
			  RxWIFrqOffsetField));

	return FreqOffset;
}

/* Get the frequency offset*/
CHAR GetFrequencyOffset(IN PRTMP_ADAPTER pAd, IN RXWI_STRUC *pRxWI)
{
	CHAR FreqOffset = 0;

	if (pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration) {
		DBGPRINT(RT_DEBUG_INFO, ("---> %s\n", __func__));

		FreqOffset = GetFrequencyOffsetField(pAd, pRxWI, pAd->chipCap.RxWIFrqOffset);

#ifdef MT76x2
		if (IS_MT76x2(pAd))
			goto ret;
#endif /* MT76x2 */

		if ((FreqOffset < LOWERBOUND_OF_FREQUENCY_OFFSET) ||
		    (FreqOffset > UPPERBOUND_OF_FREQUENCY_OFFSET)) {
			FreqOffset = INVALID_FREQUENCY_OFFSET;

			DBGPRINT(RT_DEBUG_ERROR, ("%s: (out-of-range) FreqOffset = %d\n",
						  __func__, FreqOffset));
		}

		DBGPRINT(RT_DEBUG_INFO, ("%s: FreqOffset = %d\n", __func__, FreqOffset));

		DBGPRINT(RT_DEBUG_INFO, ("<--- %s\n", __func__));
	}

ret:
	return FreqOffset;
}
#endif /* CONFIG_STA_SUPPORT */

#endif /* RTMP_FREQ_CALIBRATION_SUPPORT */
