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

/*
========================================================================
Routine Description:
	write high memory.
	if firmware do not support auto high/low memory switching, we should switch to high memory by ourself.

Arguments:
	pAd				- WLAN control block pointer
	Offset			- Memory offsets
	Value			- Written value
	Unit				- Unit in "Byte"

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpChipWriteHighMemory(IN RTMP_ADAPTER * pAd,
			     IN USHORT Offset, IN UINT32 Value, IN UINT8 Unit)
{
#ifdef RTMP_MAC_USB
	switch (Unit) {
	case 1:
		RTUSBSingleWrite(pAd, Offset, Value, TRUE);
		break;
	case 2:
		{
			UINT16 ShortVal = (UINT16) Value;

			RTUSBMultiWrite(pAd, Offset, (UCHAR *) &ShortVal, 2, TRUE);
			break;
		}
	case 4:
		RTUSBWriteMACRegister(pAd, Offset, Value, TRUE);
	default:
		break;
	}
#endif /* RTMP_MAC_USB */
}

/*
========================================================================
Routine Description:
	write memory

Arguments:
	pAd				- WLAN control block pointer
	Offset			- Memory offsets
	Value			- Written value
	Unit				- Unit in "Byte"
Return Value:
	None

Note:
========================================================================
*/
VOID RtmpChipWriteMemory(IN RTMP_ADAPTER * pAd, IN USHORT Offset, IN UINT32 Value, IN UINT8 Unit)
{
	switch (Unit) {
	case 1:
		RTMP_IO_WRITE8(pAd, Offset, Value);
		break;
	case 2:
		RTMP_IO_WRITE16(pAd, Offset, Value);
		break;
	case 4:
		RTMP_IO_WRITE32(pAd, Offset, Value);
	default:
		break;
	}
}

#ifdef RLT_MAC
/*
========================================================================
Routine Description:
	Initialize specific beacon frame architecture.

Arguments:
	pAd				- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID rlt_bcn_buf_init(RTMP_ADAPTER *pAd)
{
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;

	pChipCap->FlgIsSupSpecBcnBuf = FALSE;
#if defined(MT7601) || defined(MT76x2)
	if (IS_MT7601(pAd) || IS_MT76x2(pAd)) {
		pChipCap->BcnMaxHwNum = 8;
		pChipCap->WcidHwRsvNum = 127;
	} else
#endif /* MT7601 || MT76x2 */
	{
		pChipCap->BcnMaxHwNum = 16;
		pChipCap->WcidHwRsvNum = 255;
	}

/*
	In 16-MBSS support mode, if AP-Client is enabled,
	the last 8-MBSS would be occupied for AP-Client using.
*/
#ifdef APCLI_SUPPORT
	pChipCap->BcnMaxNum = (8 - MAX_MESH_NUM);
#else
	pChipCap->BcnMaxNum = (pChipCap->BcnMaxHwNum - MAX_MESH_NUM);
#endif /* APCLI_SUPPORT */

	pChipCap->BcnMaxHwSize = 0x2000;

	pChipCap->BcnBase[0] = 0xc000;
	pChipCap->BcnBase[1] = 0xc200;
	pChipCap->BcnBase[2] = 0xc400;
	pChipCap->BcnBase[3] = 0xc600;
	pChipCap->BcnBase[4] = 0xc800;
	pChipCap->BcnBase[5] = 0xca00;
	pChipCap->BcnBase[6] = 0xcc00;
	pChipCap->BcnBase[7] = 0xce00;
	pChipCap->BcnBase[8] = 0xd000;
	pChipCap->BcnBase[9] = 0xd200;
	pChipCap->BcnBase[10] = 0xd400;
	pChipCap->BcnBase[11] = 0xd600;
	pChipCap->BcnBase[12] = 0xd800;
	pChipCap->BcnBase[13] = 0xda00;
	pChipCap->BcnBase[14] = 0xdc00;
	pChipCap->BcnBase[15] = 0xde00;

#ifdef CONFIG_MULTI_CHANNEL
#define NULLFRAME0		 0xB700
#define NULLFRAME1		 0xB780
#define NULLFRAME2		 0xD000
#define NULLFRAME3		 0xD200
#define NULLFRAME4		 0xD400
#define NULLFRAME5		 0xD600
#define NULLFRAME6		 0xD800
#define NULLFRAME7		 0xDA00
#define NULLFRAME8		 0xDC00
#define NULLFRAME9		 0xDE00

	/* Record HW Null Frame offset */
	/* yiwei mcc f/w discuss to use 8,9 */
	pAd->NullBufOffset[0] = NULLFRAME8 /*NULLFRAME2 *//*0xd000 */;
	pAd->NullBufOffset[1] = NULLFRAME9 /*NULLFRAME3 *//*0xd200 */;
#endif /* CONFIG_MULTI_CHANNEL */

	pAd->chipOps.BeaconUpdate = RtmpChipWriteMemory;
}
#endif /* RLT_MAC */


#ifdef HW_ANTENNA_DIVERSITY_SUPPORT
UINT32 SetHWAntennaDivsersity(IN PRTMP_ADAPTER pAd, IN BOOLEAN Enable)
{
	if (Enable == TRUE) {
		UINT8 BBPValue = 0, RFValue = 0;
		USHORT value;

		/* RF_R29 bit7:6 */
		RT28xx_EEPROM_READ16(pAd, EEPROM_RSSI_GAIN, value);

		RT30xxReadRFRegister(pAd, RF_R29, &RFValue);
		RFValue &= 0x3f;	/* clear bit7:6 */
		RFValue |= (value << 6);
		RT30xxWriteRFRegister(pAd, RF_R29, RFValue);

		/* BBP_R47 bit7=1 */
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BBPValue);
		BBPValue |= 0x80;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BBPValue);

		BBPValue = 0xbe;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R150, BBPValue);
		BBPValue = 0xb0;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R151, BBPValue);
		BBPValue = 0x23;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BBPValue);
		BBPValue = 0x3a;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R153, BBPValue);
		BBPValue = 0x10;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R154, BBPValue);
		BBPValue = 0x3b;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R155, BBPValue);
		BBPValue = 0x04;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R253, BBPValue);

		DBGPRINT(RT_DEBUG_TRACE, ("HwAnDi> Enable!\n"));
	} else {
		UINT8 BBPValue = 0;

		/*
		   main antenna: BBP_R152 bit7=1
		   aux antenna: BBP_R152 bit7=0
		 */
		if (pAd->FixDefaultAntenna == 0) {
			/* fix to main antenna */
			/* do not care BBP R153, R155, R253 */
			BBPValue = 0x3e;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R150, BBPValue);
			BBPValue = 0x30;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R151, BBPValue);
			BBPValue = 0x23;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BBPValue);
			BBPValue = 0x00;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R154, BBPValue);
		} else {
			/* fix to aux antenna */
			/* do not care BBP R153, R155, R253 */
			BBPValue = 0x3e;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R150, BBPValue);
			BBPValue = 0x30;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R151, BBPValue);
			BBPValue = 0xa3;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BBPValue);
			BBPValue = 0x00;
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R154, BBPValue);
		}

		DBGPRINT(RT_DEBUG_TRACE, ("HwAnDi> Disable!\n"));
	}

	return 0;
}
#endif /* HW_ANTENNA_DIVERSITY_SUPPORT // */


INT WaitForAsicReady(RTMP_ADAPTER *pAd)
{
	UINT32 mac_val = 0, reg = MAC_CSR0;
	int idx = 0;

	do {
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			return FALSE;

		RTMP_IO_READ32(pAd, reg, &mac_val);
		if ((mac_val != 0x00) && (mac_val != 0xFFFFFFFF))
			return TRUE;

		RtmpOsMsDelay(5);
	} while (idx++ < 500);

	DBGPRINT(RT_DEBUG_ERROR, ("%s(0x%x):AsicNotReady!\n", __func__, mac_val));

	return FALSE;
}

INT AsicGetMacVersion(RTMP_ADAPTER *pAd)
{
	UINT32 reg = MAC_CSR0;


#ifdef RT65xx
	if (IS_RT65XX(pAd))
		RTMP_IO_READ32(pAd, ASIC_VERSION, &pAd->ChipID);
#endif /* RT65xx */

	if (WaitForAsicReady(pAd) == TRUE) {
		RTMP_IO_READ32(pAd, reg, &pAd->MACVersion);
		DBGPRINT(RT_DEBUG_OFF, ("MACVersion[Ver:Rev]=0x%08x : 0x%08x\n",
					pAd->MACVersion, pAd->ChipID));
		return TRUE;
	}
	DBGPRINT(RT_DEBUG_ERROR, ("%s() failed!\n", __func__));
	return FALSE;
}

/*
========================================================================
Routine Description:
	Initialize chip related information.

Arguments:
	pCB				- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
int RtmpChipOpsHook(VOID *pCB)
{
	RTMP_ADAPTER *pAd = (RTMP_ADAPTER *) pCB;
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;
	UINT32 MacValue;
	int ret = 0;
	RTMP_CHIP_OP *pChipOps = &pAd->chipOps;

	/* sanity check */
	if (WaitForAsicReady(pAd) == FALSE)
		return -1;

	RTMP_IO_READ32(pAd, MAC_CSR0, &MacValue);
	pAd->MACVersion = MacValue;

	if (pAd->MACVersion == 0xffffffff)
		return -1;

#ifdef RT65xx
	RTMP_IO_READ32(pAd, ASIC_VERSION, &MacValue);
	pAd->ChipID = MacValue;

	if (pAd->ChipID == 0xffffffff)
		return -1;
#endif /* RT65xx */

	/* default init */
	RTMP_DRS_ALG_INIT(pAd, RATE_ALG_LEGACY);


	/* EDCCA */
	pChipOps->ChipSetEDCCA = NULL;



#ifdef RT8592
	if (IS_RT8592(pAd)) {
		RT85592_Init(pAd);
		goto done;
	}
#endif /* RT8592 */


#ifdef MT76x2
	if (IS_MT76x2(pAd)) {
		mt76x2_init(pAd);
		goto done;
	}
#endif /* endif */

#ifdef GREENAP_SUPPORT
	pChipOps->EnableAPMIMOPS = EnableAPMIMOPSv1;
	pChipOps->DisableAPMIMOPS = DisableAPMIMOPSv1;
#endif /* GREENAP_SUPPORT */

	/* We depends on RfICType and MACVersion to assign the corresponding operation callbacks. */

done:
	DBGPRINT(RT_DEBUG_TRACE, ("Chip specific bbpRegTbSize=%d!\n", pChipCap->bbpRegTbSize));
	DBGPRINT(RT_DEBUG_TRACE,
		 ("Chip VCO calibration mode = %d!\n", pChipCap->FlgIsVcoReCalMode));
#ifdef DOT11W_PMF_SUPPORT
	DBGPRINT(RT_DEBUG_TRACE, ("[PMF] Encryption mode = %d\n", pChipCap->FlgPMFEncrtptMode));
#endif /* DOT11W_PMF_SUPPORT */

	return ret;
}

#ifdef RT65xx
BOOLEAN isExternalPAMode(RTMP_ADAPTER *ad, INT channel)
{
	BOOLEAN pa_mode = FALSE;

	if (channel > 14) {
		if (ad->chipCap.PAType == EXT_PA_2G_5G)
			pa_mode = TRUE;
		else if (ad->chipCap.PAType == EXT_PA_5G_ONLY)
			pa_mode = TRUE;
		else
			pa_mode = FALSE;
	} else {
		if (ad->chipCap.PAType == EXT_PA_2G_5G)
			pa_mode = TRUE;
		else if ((ad->chipCap.PAType == EXT_PA_5G_ONLY) ||
			 (ad->chipCap.PAType == INT_PA_2G_5G))
			pa_mode = FALSE;
		else if (ad->chipCap.PAType == EXT_PA_2G_ONLY)
			pa_mode = TRUE;
	}

	return pa_mode;
}

BOOLEAN is_external_lna_mode(RTMP_ADAPTER *ad, INT channel)
{
	BOOLEAN lna_mode = FALSE;

	/* b'00: 2.4G+5G external LNA, b'01: 5G external LNA, b'10: 2.4G external LNA, b'11: Internal LNA */
	if (channel > 14) {
		if ((ad->chipCap.LNA_type == 0x0) || (ad->chipCap.LNA_type == 0x1))
			lna_mode = TRUE;
		else
			lna_mode = FALSE;
	} else {
		if ((ad->chipCap.LNA_type == 0x0) || (ad->chipCap.LNA_type == 0x10))
			lna_mode = TRUE;
		else
			lna_mode = FALSE;
	}

	return lna_mode;
}
#endif /* RT65xx */
