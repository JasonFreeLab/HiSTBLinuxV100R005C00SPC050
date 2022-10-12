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

struct chip_map {
	UINT32 ChipVersion;
	PSTRING name;
};

struct chip_map RTMP_CHIP_E2P_FILE_TABLE[] = {
	{0x3071, "RT3092_PCIe_LNA_2T2R_ALC_V1_2.bin"},
	{0x3090, "RT3092_PCIe_LNA_2T2R_ALC_V1_2.bin"},
	{0x3593, "HMC_RT3593_PCIe_3T3R_V1_3.bin"},
	{0x5392, "RT5392_PCIe_2T2R_ALC_V1_4.bin"},
	{0x5592, "RT5592_PCIe_2T2R_V1_7.bin"},
	{0x7602, "MT7602E_EEPROM.bin"},
	{0x7612, "MT7612E_EEPROM.bin"},
	{0x7620, "MT7620_AP_2T2R-4L_V15.BIN"},
	{0,}
};

struct chip_map chip_card_id_map[] = {
	{7620, ""},
};

static UCHAR RtmpEepromGetDefault(IN RTMP_ADAPTER * pAd)
{
	UCHAR e2p_dafault = 0;

#ifdef CONFIG_RT_FIRST_CARD
	if (pAd->dev_idx == 0) {
		if (RTMPEqualMemory("efuse", CONFIG_RT_FIRST_CARD_EEPROM, 5))
			e2p_dafault = E2P_EFUSE_MODE;
		if (RTMPEqualMemory("prom", CONFIG_RT_FIRST_CARD_EEPROM, 4))
			e2p_dafault = E2P_EEPROM_MODE;
		if (RTMPEqualMemory("flash", CONFIG_RT_FIRST_CARD_EEPROM, 5))
			e2p_dafault = E2P_FLASH_MODE;
		goto out;
	}
#endif /* CONFIG_RT_FIRST_CARD */

#ifdef CONFIG_RT_SECOND_CARD
	if (pAd->dev_idx == 1) {
		if (RTMPEqualMemory("efuse", CONFIG_RT_SECOND_CARD_EEPROM, 5))
			e2p_dafault = E2P_EFUSE_MODE;
		if (RTMPEqualMemory("prom", CONFIG_RT_SECOND_CARD_EEPROM, 4))
			e2p_dafault = E2P_EEPROM_MODE;
		if (RTMPEqualMemory("flash", CONFIG_RT_SECOND_CARD_EEPROM, 5))
			e2p_dafault = E2P_FLASH_MODE;
		goto out;
	}
#endif /* CONFIG_RT_SECOND_CARD */

	if (IS_RT2860(pAd) || IS_RT2870(pAd))
		e2p_dafault = E2P_EEPROM_MODE;
	else if (pAd->infType == RTMP_DEV_INF_RBUS)
		e2p_dafault = E2P_FLASH_MODE;
	else
		e2p_dafault = E2P_EFUSE_MODE;
#if defined(CONFIG_RT_FIRST_CARD) || defined(CONFIG_RT_SECOND_CARD)
out:
#endif /* defined(CONFIG_RT_FIRST_CARD) || defined(CONFIG_RT_SECOND_CARD) */

	DBGPRINT(RT_DEBUG_OFF, ("%s::e2p_dafault=%d\n", __func__, e2p_dafault));
	return e2p_dafault;
}

INT RtmpChipOpsEepromHook(IN RTMP_ADAPTER * pAd, IN INT infType)
{
	RTMP_CHIP_OP *pChipOps = &pAd->chipOps;
	UCHAR e2p_type;

#ifdef TXBF_SUPPORT
	if (pAd->chipCap.FlgITxBfBinWrite)
		pAd->E2pAccessMode = E2P_BIN_MODE;
#endif /* endif */

	e2p_type = pAd->E2pAccessMode;

	DBGPRINT(RT_DEBUG_OFF, ("%s::e2p_type=%d, inf_Type=%d\n", __func__,
		e2p_type, infType));

	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
		return -1;

	/* If e2p_type is out of range, get the default mode */
	if (e2p_type == 0 || e2p_type >= NUM_OF_E2P_MODE)
		e2p_type = RtmpEepromGetDefault(pAd);

	if (infType == RTMP_DEV_INF_RBUS) {
		e2p_type = E2P_FLASH_MODE;
		pChipOps->loadFirmware = NULL;
	}

	pAd->E2pAccessMode = e2p_type;

	switch (e2p_type) {
	case E2P_EEPROM_MODE:
		break;
	case E2P_BIN_MODE:
		{
			pChipOps->eeinit = rtmp_ee_load_from_bin;
			pChipOps->eeread = rtmp_ee_bin_read16;
			pChipOps->eewrite = rtmp_ee_bin_write16;
			DBGPRINT(RT_DEBUG_OFF, ("NVM is BIN mode\n"));
			return 0;
		}

#ifdef RTMP_FLASH_SUPPORT
	case E2P_FLASH_MODE:
		{
			pChipOps->eeinit = rtmp_nv_init;
			pChipOps->eeread = rtmp_ee_flash_read;
			pChipOps->eewrite = rtmp_ee_flash_write;
			pAd->flash_offset = DEFAULT_RF_OFFSET;
#ifdef CONFIG_RT_FIRST_CARD
			if (pAd->dev_idx == 0)
				pAd->flash_offset = CONFIG_RT_FIRST_IF_RF_OFFSET;
#endif /* CONFIG_RT_FIRST_CARD */
#ifdef CONFIG_RT_SECOND_CARD
			if (pAd->dev_idx == 1)
				pAd->flash_offset = CONFIG_RT_SECOND_IF_RF_OFFSET;
#endif /* CONFIG_RT_FIRST_CARD */
			DBGPRINT(RT_DEBUG_OFF, ("NVM is FLASH mode\n"));
			return 0;
		}
#endif /* RTMP_FLASH_SUPPORT */

#ifdef RTMP_EFUSE_SUPPORT
	case E2P_EFUSE_MODE:
	default:
		efuse_probe(pAd);
		if (pAd->bUseEfuse != FALSE) {
			pChipOps->eeinit = eFuse_init;
			pChipOps->eeread = rtmp_ee_efuse_read16;
			pChipOps->eewrite = rtmp_ee_efuse_write16;
			DBGPRINT(RT_DEBUG_OFF, ("NVM is EFUSE mode\n"));
			return 0;
		}

		DBGPRINT(RT_DEBUG_ERROR, ("%s::hook efuse mode failed\n",
			__func__));
		break;
#else
	default:
		DBGPRINT(RT_DEBUG_ERROR, ("%s::hook efuse mode failed, e2p_type = %d\n",
			__func__, e2p_type));
		return -1;
#endif /* RTMP_EFUSE_SUPPORT */
	}

	/* Hook functions based on interface types for EEPROM */
	switch (infType) {

#ifdef RTMP_USB_SUPPORT
	case RTMP_DEV_INF_USB:
		pChipOps->eeinit = NULL;
		pChipOps->eeread = RTUSBReadEEPROM16;
		pChipOps->eewrite = RTUSBWriteEEPROM16;
		break;
#endif /* RTMP_USB_SUPPORT */

	default:
		DBGPRINT(RT_DEBUG_ERROR, ("%s::hook failed\n", __func__));
		break;
	}

	DBGPRINT(RT_DEBUG_OFF, ("NVM is EEPROM mode\n"));
	return 0;
}

BOOLEAN rtmp_get_default_bin_file_by_chip(IN PRTMP_ADAPTER pAd,
					  IN UINT32 ChipVersion, OUT PSTRING *pBinFileName)
{
	BOOLEAN found = FALSE;
	INT i;

	DBGPRINT(RT_DEBUG_OFF, ("%s::chip version=0x%04x\n", __func__, ChipVersion));

	for (i = 0; RTMP_CHIP_E2P_FILE_TABLE[i].ChipVersion != 0; i++) {
		if (IS_RT6352(pAd))
			ChipVersion = 0x7620;

		if (RTMP_CHIP_E2P_FILE_TABLE[i].ChipVersion == ChipVersion) {
			*pBinFileName = RTMP_CHIP_E2P_FILE_TABLE[i].name;
			DBGPRINT(RT_DEBUG_OFF,
				("%s(): Found E2P bin file name:%s\n",
				__func__, *pBinFileName));
			found = TRUE;
			break;
		}
	}

	if (found == TRUE)
		DBGPRINT(RT_DEBUG_OFF,
			("%s::Found E2P bin file name=%s\n",
			__func__, *pBinFileName));
	else
		DBGPRINT(RT_DEBUG_ERROR,
			("%s::E2P bin file name not found\n", __func__));

	return found;
}

INT rtmp_ee_bin_read16(IN RTMP_ADAPTER * pAd, IN USHORT Offset, OUT USHORT * pValue)
{
	DBGPRINT(RT_DEBUG_TRACE, ("%s::Read from EEPROM buffer\n", __func__));
	NdisMoveMemory(pValue, &(pAd->EEPROMImage[Offset]), 2);
	*pValue = le2cpu16(*pValue);

	return *pValue;
}

INT rtmp_ee_bin_write16(IN RTMP_ADAPTER * pAd, IN USHORT Offset, IN USHORT data)
{
	DBGPRINT(RT_DEBUG_TRACE, ("%s::Write to EEPROM buffer\n", __func__));
	data = le2cpu16(data);
	NdisMoveMemory(&(pAd->EEPROMImage[Offset]), &data, 2);

	return 0;
}

INT rtmp_ee_load_from_bin(IN PRTMP_ADAPTER pAd)
{
	PSTRING src = NULL;
#ifdef WCX_SUPPORT
	POS_COOKIE obj = (POS_COOKIE) pAd->OS_Cookie;
	UINT32 bin_file_len;
	UCHAR *bin_file;
#else
	INT ret_val;
	RTMP_OS_FD srcf;
	RTMP_OS_FS_INFO osFSInfo;
#endif /* WCX_SUPPORT */
#ifdef RT_SOC_SUPPORT
#ifdef MULTIPLE_CARD_SUPPORT
	STRING bin_file_path[128];
	PSTRING bin_file_name = NULL;
	UINT32 chip_ver = (pAd->MACVersion >> 16);

	if (rtmp_get_default_bin_file_by_chip(pAd, chip_ver, &bin_file_name) == TRUE) {
		if (pAd->MC_RowID > 0)
			sprintf(bin_file_path, "%s%s", EEPROM_2ND_FILE_DIR, bin_file_name);
		else
			sprintf(bin_file_path, "%s%s", EEPROM_1ST_FILE_DIR, bin_file_name);

		src = bin_file_path;
	} else
#endif /* MULTIPLE_CARD_SUPPORT */
#endif /* RT_SOC_SUPPORT */
		src = BIN_FILE_PATH;

	DBGPRINT(RT_DEBUG_TRACE, ("%s::FileName=%s\n", __func__, src));
#ifdef WCX_SUPPORT
	/* use request firmware replace filp_open */
	OS_LOAD_CODE_FROM_BIN(&bin_file, src, obj->pUsb_Dev, &bin_file_len);
	if (!bin_file) {
		DBGPRINT(RT_DEBUG_ERROR, ("%s::Error opening %s\n", __func__, src));
		return FALSE;
	}
	NdisZeroMemory(pAd->EEPROMImage, MAX_EEPROM_BIN_FILE_SIZE);
	NdisCopyMemory(pAd->EEPROMImage, bin_file, bin_file_len);
	hex_dump("NVRAM", pAd->EEPROMImage, MAX_EEPROM_BIN_FILE_SIZE);
	RtmpOsVfree(bin_file);
#else
	RtmpOSFSInfoChange(&osFSInfo, TRUE);

	if (src && *src) {
		srcf = RtmpOSFileOpen(src, O_RDONLY, 0);
		if (IS_FILE_OPEN_ERR(srcf)) {
			DBGPRINT(RT_DEBUG_ERROR, ("%s::Error opening %s\n", __func__, src));
			return FALSE;
		}
		NdisZeroMemory(pAd->EEPROMImage, MAX_EEPROM_BIN_FILE_SIZE);
		ret_val = RtmpOSFileRead(srcf,
			(PSTRING) pAd->EEPROMImage, MAX_EEPROM_BIN_FILE_SIZE);

		if (ret_val > 0)
			ret_val = NDIS_STATUS_SUCCESS;
		else
			DBGPRINT(RT_DEBUG_ERROR,
				 ("%s::Read file \"%s\" failed(errCode=%d)!\n",
				__func__, src, ret_val));
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("%s::Error src or srcf is null\n", __func__));
		return FALSE;
	}

	ret_val = RtmpOSFileClose(srcf);

	if (ret_val)
		DBGPRINT(RT_DEBUG_ERROR, ("%s::Error %d closing %s\n", __func__, -ret_val, src));

	RtmpOSFSInfoChange(&osFSInfo, FALSE);
#endif /* WCX_SUPPORT */
	return TRUE;
}

INT rtmp_ee_write_to_bin(IN PRTMP_ADAPTER pAd)
{
	PSTRING src = NULL;
	INT ret_val;
	RTMP_OS_FD srcf;
	RTMP_OS_FS_INFO osFSInfo;

#ifdef RT_SOC_SUPPORT
#ifdef MULTIPLE_CARD_SUPPORT
	STRING bin_file_path[128];
	PSTRING bin_file_name = NULL;
	UINT32 chip_ver = (pAd->MACVersion >> 16);

	if (rtmp_get_default_bin_file_by_chip(pAd, chip_ver, &bin_file_name) == TRUE) {
		if (pAd->MC_RowID > 0)
			sprintf(bin_file_path, "%s%s", EEPROM_2ND_FILE_DIR, bin_file_name);
		else
			sprintf(bin_file_path, "%s%s", EEPROM_1ST_FILE_DIR, bin_file_name);

		src = bin_file_path;
	} else
#endif /* MULTIPLE_CARD_SUPPORT */
#endif /* RT_SOC_SUPPORT */
		src = BIN_FILE_PATH;

	DBGPRINT(RT_DEBUG_TRACE, ("%s::FileName=%s\n", __func__, src));

	RtmpOSFSInfoChange(&osFSInfo, TRUE);

	if (src && *src) {
		srcf = RtmpOSFileOpen(src, O_WRONLY | O_CREAT, 0);

		if (IS_FILE_OPEN_ERR(srcf)) {
			DBGPRINT(RT_DEBUG_ERROR, ("%s::Error opening %s\n", __func__, src));
			return FALSE;
		}
		RtmpOSFileWrite(srcf, (PSTRING) pAd->EEPROMImage, MAX_EEPROM_BIN_FILE_SIZE);
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("%s::Error src or srcf is null\n", __func__));
		return FALSE;
	}

	ret_val = RtmpOSFileClose(srcf);

	if (ret_val)
		DBGPRINT(RT_DEBUG_ERROR, ("%s::Error %d closing %s\n", __func__, -ret_val, src));

	RtmpOSFSInfoChange(&osFSInfo, FALSE);
	return TRUE;
}

INT Set_LoadEepromBufferFromBin_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg)
{
	LONG bEnable;
	INT result;

#ifdef CAL_FREE_IC_SUPPORT
	BOOLEAN bCalFree = 0;
#endif /* CAL_FREE_IC_SUPPORT */

	if (kstrtol(arg, 10, &bEnable) != 0)
		return FALSE;
	if (bEnable < 0)
		return FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("Load EEPROM buffer from BIN, and change to BIN buffer mode\n"));
	result = rtmp_ee_load_from_bin(pAd);

	if (result == FALSE) {
		if (pAd->chipCap.EEPROM_DEFAULT_BIN != NULL) {
			NdisMoveMemory(pAd->EEPROMImage, pAd->chipCap.EEPROM_DEFAULT_BIN,
				       pAd->chipCap.EEPROM_DEFAULT_BIN_SIZE >
				       MAX_EEPROM_BUFFER_SIZE ? MAX_EEPROM_BUFFER_SIZE :
				       pAd->chipCap.EEPROM_DEFAULT_BIN_SIZE);
			DBGPRINT(RT_DEBUG_TRACE, ("Load EEPROM Buffer from default BIN.\n"));
		}

	}

	/* Change to BIN eeprom buffer mode */
	pAd->E2pAccessMode = E2P_BIN_MODE;
	RtmpChipOpsEepromHook(pAd, pAd->infType);

#ifdef CAL_FREE_IC_SUPPORT
	RTMP_CAL_FREE_IC_CHECK(pAd, bCalFree);

	if (bCalFree == TRUE) {
		RTMP_CAL_FREE_DATA_GET(pAd);
		DBGPRINT(RT_DEBUG_TRACE, ("Load Cal Free data from e-fuse.\n"));
	}
#endif /* CAL_FREE_IC_SUPPORT */

	return TRUE;
}

INT Set_EepromBufferWriteBack_Proc(IN PRTMP_ADAPTER pAd, IN PSTRING arg)
{
	ULONG e2p_mode;

	if (kstrtol(arg, 10, &e2p_mode) != 0)
		return FALSE;
	if (e2p_mode >= NUM_OF_E2P_MODE)
		return FALSE;

	switch (e2p_mode) {
#ifdef RTMP_EFUSE_SUPPORT
	case E2P_EFUSE_MODE:
		DBGPRINT(RT_DEBUG_OFF, ("Write EEPROM buffer back to eFuse\n"));
		rtmp_ee_write_to_efuse(pAd);
		break;
#endif /* RTMP_EFUSE_SUPPORT */

#ifdef RTMP_FLASH_SUPPORT
	case E2P_FLASH_MODE:
		DBGPRINT(RT_DEBUG_OFF, ("Write EEPROM buffer back to Flash\n"));
		rtmp_ee_flash_write_all(pAd, (PUSHORT) pAd->EEPROMImage);
		break;
#endif /* RTMP_FLASH_SUPPORT */

#ifdef RT65xx
	case E2P_EEPROM_MODE:
		DBGPRINT(RT_DEBUG_OFF, ("Write EEPROM buffer back to EEPROM\n"));
		rtmp_ee_write_to_prom(pAd);
		break;
#endif /* RT65xx */

	case E2P_BIN_MODE:
		DBGPRINT(RT_DEBUG_OFF, ("Write EEPROM buffer back to BIN\n"));
		rtmp_ee_write_to_bin(pAd);
		break;

	default:
		DBGPRINT(RT_DEBUG_ERROR,
			("%s::do not support this EEPROM access mode\n", __func__));
		return FALSE;
	}

	return TRUE;
}
