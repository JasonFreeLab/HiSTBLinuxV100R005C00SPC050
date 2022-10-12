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


#include "rt_config.h"

#ifdef RTMP_RF_RW_SUPPORT
/*
	========================================================================

	Routine Description: Read RF register through MAC with specified bit mask

	Arguments:
		pAd		- pointer to the adapter structure
		regID	- RF register ID
		pValue1	- (RF value & BitMask)
		pValue2	- (RF value & (~BitMask))
		BitMask	- bit wise mask

	Return Value:

	Note:

	========================================================================
*/
VOID RTMP_ReadRF(IN PRTMP_ADAPTER pAd,
		 IN UCHAR RegID, OUT PUCHAR pValue1, OUT PUCHAR pValue2, IN UCHAR BitMask)
{
	UCHAR RfReg = 0;

	RT30xxReadRFRegister(pAd, RegID, &RfReg);
	if (pValue1 != NULL)
		*pValue1 = RfReg & BitMask;
	if (pValue2 != NULL)
		*pValue2 = RfReg & (~BitMask);
}

/*
	========================================================================

	Routine Description: Write RF register through MAC with specified bit mask

	Arguments:
		pAd		- pointer to the adapter structure
		regID	- RF register ID
		Value	- only write the part of (Value & BitMask) to RF register
		BitMask	- bit wise mask

	Return Value:

	Note:

	========================================================================
*/
VOID RTMP_WriteRF(IN PRTMP_ADAPTER pAd, IN UCHAR RegID, IN UCHAR Value, IN UCHAR BitMask)
{
	UCHAR RfReg = 0;

	RTMP_ReadRF(pAd, RegID, NULL, &RfReg, BitMask);
	RfReg |= ((Value) & BitMask);
	RT30xxWriteRFRegister(pAd, RegID, RfReg);
}

/*
	========================================================================

	Routine Description: Write RF register through MAC

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NDIS_STATUS RT30xxWriteRFRegister(IN PRTMP_ADAPTER pAd, IN UCHAR regID, IN UCHAR value)
{
	RF_CSR_CFG_STRUC rfcsr = { {0}
	};
	UINT i = 0;
	NDIS_STATUS ret;


	ASSERT((regID <= pAd->chipCap.MaxNumOfRfId));

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RTMP_MAC_USB */

	ret = STATUS_UNSUCCESSFUL;
	do {
		RTMP_IO_READ32(pAd, RF_CSR_CFG, &rfcsr.word);

		if (!rfcsr.non_bank.RF_CSR_KICK)
			break;
		i++;
	} while ((i < MAX_BUSY_COUNT) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)));

	if ((i == MAX_BUSY_COUNT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_RAW(RT_DEBUG_ERROR,
			     ("%s():RF Write failed(RetryCnt=%d, DevNotExistFlag=%d)\n",
			      __func__, i, RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)));
		goto done;
	}

	rfcsr.non_bank.RF_CSR_WR = 1;
	rfcsr.non_bank.RF_CSR_KICK = 1;
	rfcsr.non_bank.TESTCSR_RFACC_REGNUM = regID;

	if ((pAd->chipCap.RfReg17WtMethod == RF_REG_WT_METHOD_STEP_ON) && (regID == RF_R17)) {
		UCHAR IdRf;
		UCHAR RfValue = 0;
		BOOLEAN beAdd;

		RT30xxReadRFRegister(pAd, RF_R17, &RfValue);
		beAdd = (RfValue < value) ? TRUE : FALSE;
		IdRf = RfValue;
		while (IdRf != value) {
			if (beAdd)
				IdRf++;
			else
				IdRf--;

			rfcsr.non_bank.RF_CSR_DATA = IdRf;
			RTMP_IO_WRITE32(pAd, RF_CSR_CFG, rfcsr.word);
			RtmpOsMsDelay(1);
		}
	}

	rfcsr.non_bank.RF_CSR_DATA = value;
	RTMP_IO_WRITE32(pAd, RF_CSR_CFG, rfcsr.word);

	ret = NDIS_STATUS_SUCCESS;

done:
#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd))
		RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
#endif /* RTMP_MAC_USB */

	return ret;
}

/*
	========================================================================

	Routine Description: Read RF register through MAC

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NDIS_STATUS RT30xxReadRFRegister(IN PRTMP_ADAPTER pAd, IN UCHAR regID, IN PUCHAR pValue)
{
	RF_CSR_CFG_STRUC rfcsr = { {0}
	};
	UINT i = 0, k = 0;
	NDIS_STATUS ret = STATUS_UNSUCCESSFUL;


	ASSERT((regID <= pAd->chipCap.MaxNumOfRfId));

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, i);
		if (i != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", i));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RTMP_MAC_USB */

	for (i = 0; i < MAX_BUSY_COUNT; i++) {
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			goto done;

		RTMP_IO_READ32(pAd, RF_CSR_CFG, &rfcsr.word);

		if (rfcsr.non_bank.RF_CSR_KICK == BUSY)
			continue;

		rfcsr.word = 0;
		rfcsr.non_bank.RF_CSR_WR = 0;
		rfcsr.non_bank.RF_CSR_KICK = 1;
		rfcsr.non_bank.TESTCSR_RFACC_REGNUM = regID;
		RTMP_IO_WRITE32(pAd, RF_CSR_CFG, rfcsr.word);

		for (k = 0; k < MAX_BUSY_COUNT; k++) {
			if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
				goto done;

			RTMP_IO_READ32(pAd, RF_CSR_CFG, &rfcsr.word);

			if (rfcsr.non_bank.RF_CSR_KICK == IDLE)
				break;
		}

		if ((rfcsr.non_bank.RF_CSR_KICK == IDLE) &&
		    (rfcsr.non_bank.TESTCSR_RFACC_REGNUM == regID)) {
			*pValue = (UCHAR) (rfcsr.non_bank.RF_CSR_DATA);
			break;
		}
	}

	if (rfcsr.non_bank.RF_CSR_KICK == BUSY) {
		DBGPRINT_ERR(("%s(): RF read R%d=0x%X fail, i[%d], k[%d]\n",
			      __func__, regID, rfcsr.word, i, k));
		goto done;
	}
	ret = STATUS_SUCCESS;

done:
#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd))
		RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
#endif /* RTMP_MAC_USB */

	return ret;
}


/*
    ========================================================================
    Routine Description:
	Adjust frequency offset when do channel switching or frequency calabration.

    Arguments:
	pAd			- Adapter pointer
	pRefFreqOffset	in: referenced Frequency offset	  out: adjusted frequency offset

    Return Value:
	None

    ========================================================================
*/
BOOLEAN RTMPAdjustFrequencyOffset(RTMP_ADAPTER *pAd, UCHAR *pRefFreqOffset)
{
	BOOLEAN RetVal = TRUE;
	UCHAR RFValue = 0;
	UCHAR PreRFValue = 0;
	UCHAR FreqOffset = 0;
	UCHAR HighCurrentBit = 0;

	RTMP_ReadRF(pAd, RF_R17, &FreqOffset, &HighCurrentBit, 0x7F);
	PreRFValue = HighCurrentBit | FreqOffset;
	FreqOffset = min((*pRefFreqOffset & 0x7F), 0x5F);
	RFValue = HighCurrentBit | FreqOffset;
	if (PreRFValue != RFValue) {
#ifdef RTMP_MAC_USB
		RetVal = AsicSendCommandToMcu(pAd, 0x74, 0xff, FreqOffset, PreRFValue, FALSE);
#else
		RetVal =
		    (RT30xxWriteRFRegister(pAd, RF_R17, RFValue) == STATUS_SUCCESS ? TRUE : FALSE);
#endif /* !RTMP_MAC_USB */
	}

	if (RetVal == FALSE)
		DBGPRINT(RT_DEBUG_TRACE, ("%s(): Error in tuning frequency offset !!\n", __func__));
	else
		*pRefFreqOffset = FreqOffset;

	return RetVal;

}

#endif /* RTMP_RF_RW_SUPPORT */
