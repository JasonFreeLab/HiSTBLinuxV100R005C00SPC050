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



#ifdef RLT_RF

#include "rt_config.h"


static inline BOOLEAN rf_csr_poll_idle(RTMP_ADAPTER *pAd, UINT32 *rfcsr)
{
	RF_CSR_CFG_STRUC *csr_val;
	BOOLEAN idle = BUSY;
	INT i = 0;

	do
	{
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			break;

		RTMP_IO_READ32(pAd, RF_CSR_CFG, rfcsr);

		csr_val = (RF_CSR_CFG_STRUC *)rfcsr;
#ifdef RT65xx
		if (IS_RT65XX(pAd))
			idle = csr_val->bank_65xx.RF_CSR_KICK;
		else
#endif /* RT65xx */
			idle = csr_val->non_bank.RF_CSR_KICK;

		if (idle == IDLE)
			break;

		i++;
	} while (i < MAX_BUSY_COUNT);

	if ((i == MAX_BUSY_COUNT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
	{
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed(cnt=%d)!\n", i));
	}

	return idle;
}


NDIS_STATUS rlt_rf_write(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR bank,
	IN UCHAR regID,
	IN UCHAR value)
{
	RF_CSR_CFG_STRUC rfcsr = { { 0 } };
	NDIS_STATUS	 ret;



#ifdef RLT_MAC
	// TODO: shiang-usw, why we need to check this for MT7601?? Get these code from MT7601!
	if (pAd->chipCap.hif_type == HIF_RLT) {
		if (pAd->WlanFunCtrl.field.WLAN_EN == 0)
		{
			DBGPRINT_ERR(("rlt_rf_write. Not allow to write RF 0x%x : fail\n",  regID));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RLT_MAC */

#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, ret);
		if (ret != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RTMP_MAC_USB */

	ASSERT((regID <= pAd->chipCap.MaxNumOfRfId));

	ret = STATUS_UNSUCCESSFUL;
	if (rf_csr_poll_idle(pAd, &rfcsr.word) != IDLE)
		goto done;

#ifdef RT65xx
	if (IS_RT65XX(pAd)) {
		rfcsr.bank_65xx.RF_CSR_WR = 1;
		rfcsr.bank_65xx.RF_CSR_KICK = 1;
		rfcsr.bank_65xx.RF_CSR_REG_BANK = bank;
		rfcsr.bank_65xx.RF_CSR_REG_ID = regID;
		rfcsr.bank_65xx.RF_CSR_DATA = value;
	}
	else
#endif /* RT65xx */
	{
		DBGPRINT_ERR(("%s():RF write with wrong handler!\n", __FUNCTION__));
		goto done;
	}
	RTMP_IO_WRITE32(pAd, RF_CSR_CFG, rfcsr.word);

	ret = NDIS_STATUS_SUCCESS;

done:
#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
	}
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
NDIS_STATUS rlt_rf_read(
	IN RTMP_ADAPTER *pAd,
	IN UCHAR bank,
	IN UCHAR regID,
	IN UCHAR *pValue)
{
	RF_CSR_CFG_STRUC rfcsr = { { 0 } };
	UINT i=0, k=0;
	BOOLEAN rf_status;
	NDIS_STATUS	 ret = STATUS_UNSUCCESSFUL;



#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, i);
		if (i != 0) {
			DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", i));
			return STATUS_UNSUCCESSFUL;
		}
	}
#endif /* RTMP_MAC_USB */

	ASSERT((regID <= pAd->chipCap.MaxNumOfRfId));

	rfcsr.word = 0;

	for (i=0; i<MAX_BUSY_COUNT; i++)
	{
		if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			goto done;

		rf_status = rf_csr_poll_idle(pAd, &rfcsr.word);
		if ( rf_status == BUSY)
			break;

		rfcsr.word = 0;
#ifdef RT65xx
		if (IS_RT65XX(pAd)) {
			rfcsr.bank_65xx.RF_CSR_WR = 0;
			rfcsr.bank_65xx.RF_CSR_KICK = 1;
			rfcsr.bank_65xx.RF_CSR_REG_ID = regID;
			rfcsr.bank_65xx.RF_CSR_REG_BANK = bank;
		}
		else
#endif /* RT65xx */
		{
			DBGPRINT_ERR(("RF[%d] read function for non-supported chip[0x%x]\n", regID, pAd->MACVersion));
			break;
		}

		RTMP_IO_WRITE32(pAd, RF_CSR_CFG, rfcsr.word);

		rf_status = rf_csr_poll_idle(pAd, &rfcsr.word);
		if (rf_status == IDLE)
		{
#ifdef RT65xx
			if (IS_RT65XX(pAd) && (rfcsr.bank_65xx.RF_CSR_REG_ID == regID) &&
				(rfcsr.bank_65xx.RF_CSR_REG_BANK == bank))
			{
				*pValue = (UCHAR)(rfcsr.bank_65xx.RF_CSR_DATA);
				break;
			}
#endif /* RT65xx */
		}
	}

	if (rf_status == BUSY)
	{
		DBGPRINT_ERR(("RF read R%d=0x%X fail, i[%d], k[%d]\n", regID, rfcsr.word,i,k));
		goto done;
	}
	ret = STATUS_SUCCESS;

done:
#ifdef RTMP_MAC_USB
	if (IS_USB_INF(pAd)) {
		RTMP_SEM_EVENT_UP(&pAd->reg_atomic);
	}
#endif /* RTMP_MAC_USB */

	return ret;
}

#endif /* RLT_RF */
