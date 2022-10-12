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


#ifdef RTMP_MAC_USB

#include	"rt_config.h"

#define MAX_VENDOR_REQ_RETRY_COUNT  10

/*
	========================================================================

	Routine Description: NIC initialization complete

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
#ifdef RTMP_MAC
void usb_cfg_read_v1(RTMP_ADAPTER *ad, u32 *value)
{
	RTUSBReadMACRegister(ad, RTMP_USB_DMA_CFG, value);
}

/* For MT76x0 and older */
void usb_cfg_write_v1(RTMP_ADAPTER *ad, u32 value)
{
	RTUSBWriteMACRegister(ad, RTMP_USB_DMA_CFG, value, FALSE);
}
#endif /* RTMP_MAC */

#ifdef RLT_MAC
/* For MT76x0 and older */
void usb_cfg_read_v2(RTMP_ADAPTER *ad, u32 *value)
{
	RTUSBReadMACRegister(ad, RLT_USB_DMA_CFG, value);
}

/* For MT76x0 and older */
void usb_cfg_write_v2(RTMP_ADAPTER *ad, u32 value)
{
	RTUSBWriteMACRegister(ad, RLT_USB_DMA_CFG, value, FALSE);
}

#ifdef MT76x2
/* For MT7662 and newer */
void usb_cfg_read_v3(RTMP_ADAPTER *ad, u32 *value)
{
	int ret;
	u32 io_value;

	ret = RTUSB_VendorRequest(ad,
				  (USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
				  DEVICE_VENDOR_REQUEST_IN, 0x47, 0, U3DMA_WLCFG, &io_value, 4);

	*value = le2cpu32(io_value);

	if (ret)
		*value = 0xffffffff;
}

/* For MT7662 and newer */
void usb_cfg_write_v3(RTMP_ADAPTER *ad, u32 value)
{
	int ret;
	u32 io_value;

	io_value = cpu2le32(value);

	ret = RTUSB_VendorRequest(ad,
				  USBD_TRANSFER_DIRECTION_OUT,
				  DEVICE_VENDOR_REQUEST_OUT, 0x46, 0, U3DMA_WLCFG, &io_value, 4);

	if (ret) {
		DBGPRINT(RT_DEBUG_ERROR, ("usb cfg write fail\n"));
		return;
	}
}
#endif /* MT76x2 */
#endif /* RLT_MAC */

static NTSTATUS RTUSBFirmwareRun(RTMP_ADAPTER *pAd)
{
	NTSTATUS Status;

	Status = RTUSB_VendorRequest(pAd,
				     USBD_TRANSFER_DIRECTION_OUT,
				     DEVICE_VENDOR_REQUEST_OUT, 0x01, 0x8, 0, NULL, 0);

	return Status;
}


/*
	========================================================================

	Routine Description: Write Firmware to NIC.

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBFirmwareWrite(RTMP_ADAPTER *pAd, UCHAR *pFwImage, ULONG FwLen)
{
	UINT32 MacReg;
	NTSTATUS Status;
	USHORT writeLen;

	Status = RTUSBReadMACRegister(pAd, MAC_CSR0, &MacReg);


	/* write firmware */
	writeLen = FwLen;
#ifdef USB_FIRMWARE_MULTIBYTE_WRITE
	DBGPRINT(RT_DEBUG_TRACE,
		 ("USB_FIRMWARE_MULTIBYTE_WRITE defined! Write_Bytes = %d\n", MULTIWRITE_BYTES));
	RTUSBMultiWrite_nBytes(pAd, FIRMWARE_IMAGE_BASE, pFwImage, writeLen, MULTIWRITE_BYTES);
#else
	DBGPRINT(RT_DEBUG_TRACE, ("USB_FIRMWARE_MULTIBYTE_WRITE not defined!\n"));
	RTUSBMultiWrite(pAd, FIRMWARE_IMAGE_BASE, pFwImage, writeLen, FALSE);
#endif /* endif */
	Status = RTUSBWriteMACRegister(pAd, 0x7014, 0xffffffff, FALSE);
	Status = RTUSBWriteMACRegister(pAd, 0x701c, 0xffffffff, FALSE);

	/* change 8051 from ROM to RAM */
	Status = RTUSBFirmwareRun(pAd);


	return Status;
}

NTSTATUS RTUSBVenderReset(RTMP_ADAPTER *pAd)
{
	NTSTATUS Status;

	DBGPRINT_RAW(RT_DEBUG_ERROR, ("-->RTUSBVenderReset\n"));
	Status = RTUSB_VendorRequest(pAd,
				     USBD_TRANSFER_DIRECTION_OUT,
				     DEVICE_VENDOR_REQUEST_OUT, 0x01, 0x1, 0, NULL, 0);

	DBGPRINT_RAW(RT_DEBUG_ERROR, ("<--RTUSBVenderReset\n"));
	return Status;
}

/*
	========================================================================

	Routine Description: Read various length data from RT2573

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBMultiRead(RTMP_ADAPTER *pAd, USHORT addr, UCHAR *buf, USHORT len)
{
	return RTUSB_VendorRequest(pAd, (USBD_TRANSFER_DIRECTION_IN |
					 USBD_SHORT_TRANSFER_OK),
				   DEVICE_VENDOR_REQUEST_IN, 0x7, 0, addr, buf, len);
}

/*
	========================================================================

	Routine Description: Write various length data to RT USB Wifi device, the maxima length should not large
	than 65535 bytes.

	Arguments:

	Return Value:

	IRQL =

	Note:
		Use this funciton carefully cause it may not stable in some special USB host controllers.

	========================================================================
*/
NTSTATUS RTUSBMultiWrite_nBytes(IN RTMP_ADAPTER *pAd,
				IN USHORT Offset, IN UCHAR *buf, IN USHORT len, IN USHORT batchLen)
{
	NTSTATUS Status = STATUS_SUCCESS;
	USHORT index = Offset, actLen = batchLen, leftLen = len;
	UCHAR *pSrc = buf;

	do {
		actLen = (actLen > batchLen ? batchLen : actLen);
		Status = RTUSB_VendorRequest(pAd,
					     USBD_TRANSFER_DIRECTION_OUT,
					     DEVICE_VENDOR_REQUEST_OUT,
					     0x6, 0, index, pSrc, actLen);

		if (Status != STATUS_SUCCESS) {
			if (Status != NDIS_STATUS_SUSPEND) {
				/*
				 * Do not print error message by default
				 * if in Radio_Off case, or if NIC not exist.
				 */
				if (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF) &&
				    !RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
					DBGPRINT(RT_DEBUG_ERROR, ("%s: failed!!\n", __func__));
			}
			break;
		}

		index += actLen;
		leftLen -= actLen;
		pSrc = pSrc + actLen;
	} while (leftLen > 0);

	return Status;
}

/*
	========================================================================

	Routine Description: Write various length data to RT2573

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBMultiWrite_OneByte(RTMP_ADAPTER *pAd, USHORT Offset, UCHAR *pData)
{
	/* TODO: In 2870, use this funciton carefully cause it's not stable. */
	return RTUSB_VendorRequest(pAd, USBD_TRANSFER_DIRECTION_OUT,
				   DEVICE_VENDOR_REQUEST_OUT, 0x6, 0, Offset, pData, 1);
}

NTSTATUS RTUSBMultiWrite(IN RTMP_ADAPTER *pAd,
			 IN USHORT Offset,
			 IN UCHAR *pData, IN USHORT length, IN BOOLEAN bWriteHigh)
{
	NTSTATUS Status;
	USHORT index = 0, Value;
	UCHAR *pSrc = pData;
	USHORT resude = 0;

	resude = length % 2;
	length += resude;
	do {
		Value = (USHORT) (*pSrc | (*(pSrc + 1) << 8));
		Status = RTUSBSingleWrite(pAd, Offset + index, Value, bWriteHigh);
		index += 2;
		length -= 2;
		pSrc = pSrc + 2;
	} while (length > 0);

	return Status;
}

NTSTATUS RTUSBSingleWrite(IN RTMP_ADAPTER *pAd,
			  IN USHORT Offset, IN USHORT Value, IN BOOLEAN WriteHigh)
{
	return RTUSB_VendorRequest(pAd, USBD_TRANSFER_DIRECTION_OUT,
				   DEVICE_VENDOR_REQUEST_OUT,
				   (WriteHigh == TRUE) ? 0x10 : 0x2, Value, Offset, NULL, 0);
}

/*
	========================================================================

	Routine Description: Read 32-bit MAC register

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBReadMACRegister(RTMP_ADAPTER *pAd, USHORT Offset, UINT32 *pValue)
{
	NTSTATUS Status = 0;
	UINT32 localVal;

	Status = RTUSB_VendorRequest(pAd,
				     (USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
				     DEVICE_VENDOR_REQUEST_IN, 0x7, 0, Offset, &localVal, 4);

	*pValue = le2cpu32(localVal);

	if (Status != 0)
		*pValue = 0xffffffff;

	return Status;
}

/*
	========================================================================

	Routine Description: Write 32-bit MAC register

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWriteMACRegister(IN RTMP_ADAPTER *pAd,
			       IN USHORT Offset, IN UINT32 Value, IN BOOLEAN bWriteHigh)
{
	NTSTATUS Status;
	UINT32 localVal;

	localVal = Value;

	/* MT76xx HW has 4 byte alignment constrained */
	if (IS_MT76xx(pAd)) {
		Status = RTUSBMultiWrite_nBytes(pAd, Offset, (UCHAR *) &Value, 4, 4);
	} else {
		Status = RTUSBSingleWrite(pAd, Offset, (USHORT) (localVal & 0xffff), bWriteHigh);
		Status =
		    RTUSBSingleWrite(pAd, Offset + 2, (USHORT) ((localVal & 0xffff0000) >> 16),
				     bWriteHigh);
	}

	return Status;
}

int write_reg(RTMP_ADAPTER *ad, UINT32 base, UINT16 offset, UINT32 val)
{
	NTSTATUS ret;
	UINT8 req;
	UINT32 io_value;

	ASSERT(base == 0x40);
	if (base != 0x40) {
		DBGPRINT(RT_DEBUG_ERROR, ("Unknown base %x should be 0x40\n", base));
		return STATUS_UNSUCCESSFUL;
	}

	req = 0x46;

	io_value = cpu2le32(val);

	ret = RTUSB_VendorRequest(ad,
				  USBD_TRANSFER_DIRECTION_OUT,
				  DEVICE_VENDOR_REQUEST_OUT, req, 0, offset, &io_value, 4);

	if (ret)
		DBGPRINT(RT_DEBUG_ERROR, ("write reg fail\n"));

	return ret;
}

int read_reg(RTMP_ADAPTER *ad, UINT32 base, UINT16 offset, UINT32 *value)
{
	NTSTATUS ret;
	UINT8 req = 0;
	UINT32 io_value;

	if (base == 0x40)
		req = 0x47;
	else if (base == 0x41)
		req = 0x7;
	else
		DBGPRINT(RT_DEBUG_ERROR, ("[%s] Unknown base %x\n", __func__, base));

	ret = RTUSB_VendorRequest(ad,
				  (USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK),
				  DEVICE_VENDOR_REQUEST_IN, req, 0, offset, &io_value, 4);

	*value = le2cpu32(io_value);

	if (ret)
		*value = 0xffffffff;

	return ret;
}

#ifdef NEW_WOW_SUPPORT
int wmt_gpio_configrue(RTMP_ADAPTER *ad, PVOID io_buf, UINT Len)
{
	NTSTATUS ret;
	UINT8 req;

	req = 0x01;

	ret = RTUSB_VendorRequest(ad,
							  USBD_TRANSFER_DIRECTION_OUT,
							  DEVICE_CLASS_REQUEST_OUT,
							  req,
							  0x30,
							  0x00,
							  io_buf,
							  Len);

	if (ret)
		DBGPRINT(RT_DEBUG_ERROR, ("wmt gpio configure command fail\n"));

	return ret;
}
#endif /* NEW_WOW_SUPPORT */

/*
	========================================================================

	Routine Description: disconnect mode while usb enter suspend

	Arguments:
	ad:
	adapter structure pointer

	Discon_mode[2:0]:
	3'b000: disable;
	3'b001: USB disconnect when suspend, SW workaround to avoid current leakage
	3'b010: USB disconnect when WIFI disconnect on WoW;

	GPIO_notify_mode[4:3]:
	2'b00: NO GPIO notify needed;
	2'b01: falling edge notify;
	2'b10: rising edge notify
	2'b11: both falling and rising edge notify;

	GPIO_Notify_Pin[9:5]:
	GPIO for notifying release D+ pull down

	Return Value:

	IRQL =

	Note:

	========================================================================
*/


int usb2_disconnect_cmd(RTMP_ADAPTER *ad, UINT8 Discon_mode,
					UINT8 GPIO_notify_mode, UINT8 GPIO_Notify_Pin)
{
	NTSTATUS ret;
	UINT8 req = 0;
	UINT16 index = 0;

	req = 0x91;
	index = (GPIO_Notify_Pin << 0x05) | (GPIO_notify_mode << 0x03) | Discon_mode;

	DBGPRINT(RT_DEBUG_ERROR, ("usb2 disconnect command\n"));
	ret = RTUSB_VendorRequest(ad,
							  USBD_TRANSFER_DIRECTION_OUT,
							  DEVICE_VENDOR_REQUEST_OUT,
							  req,
							  0x01,
							  index,
							  0,
							  0);

	if (ret)
		DBGPRINT(RT_DEBUG_ERROR, ("usb2 disconnect command fail\n"));

	return ret;
}


#ifdef RTMP_BBP
/*
	========================================================================

	Routine Description: Read 8-bit BBP register directly, i.e., not through the MCU

	Arguments:

	Return Value:

	Note: Obsoleted
	========================================================================
*/
NTSTATUS RTUSBReadBBPRegister_Direct(RTMP_ADAPTER *pAd, UCHAR Id, UCHAR *buf)
{
	BBP_CSR_CFG_STRUC BbpCsr;
	UINT i = 0;
	NTSTATUS status;
	int RET = 0;
	BOOLEAN read_done;

	RTMP_SEM_EVENT_WAIT(&(pAd->reg_atomic), RET);
	if (RET != 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", RET));
		return STATUS_UNSUCCESSFUL;
	}

	/* Verify the busy condition */
	read_done = FALSE;
	for (i = 0; i < RETRY_LIMIT; i++) {
		status = RTUSBReadMACRegister(pAd, BBP_CSR_CFG, &BbpCsr.word);
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			break;

		if (status >= 0 && (BbpCsr.field.Busy == IDLE)) {
			if (read_done == FALSE) {
				/* Prepare for write material */
				BbpCsr.word = 0;
				BbpCsr.field.fRead = 1;
				BbpCsr.field.Busy = 1;
				BbpCsr.field.RegNum = Id;
				RTUSBWriteMACRegister(pAd, BBP_CSR_CFG, BbpCsr.word, FALSE);
				read_done = TRUE;
				i = 0;
			} else {
				*buf = (UCHAR) BbpCsr.field.Value;
				break;
			}
		}
	}
	DBGPRINT(RT_DEBUG_TRACE, ("%s():RetryCnt=%d!read_done=%d\n", __func__, i, read_done));

	if ((i == RETRY_LIMIT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		/* Read failed then Return Default value. */
		*buf = pAd->BbpWriteLatch[Id];
		RTMP_SEM_EVENT_UP(&(pAd->reg_atomic));
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed!!!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	RTMP_SEM_EVENT_UP(&pAd->reg_atomic);

	return STATUS_SUCCESS;
}

/*
	========================================================================

	Routine Description: Read 8-bit BBP register via firmware

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBReadBBPRegister(RTMP_ADAPTER *pAd, UCHAR Id, UCHAR *pValue)
{
	BBP_CSR_CFG_STRUC BbpCsr = {.word = 0 };
	int i, k, ret;
	UINT32 bbp_agent;
	BOOLEAN via_mcu = TRUE;


	bbp_agent = ((via_mcu == TRUE) ? H2M_BBP_AGENT : BBP_CSR_CFG);

	RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, ret);
	if (ret != 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
		return STATUS_UNSUCCESSFUL;
	}

	for (i = 0; i < MAX_BUSY_COUNT; i++) {
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			break;

		RTUSBReadMACRegister(pAd, bbp_agent, &BbpCsr.word);
		if (BbpCsr.field.Busy == BUSY)
			continue;

		BbpCsr.word = 0;
		BbpCsr.field.fRead = 1;
		BbpCsr.field.BBP_RW_MODE = 1;
		BbpCsr.field.Busy = 1;
		BbpCsr.field.RegNum = Id;
		RTUSBWriteMACRegister(pAd, bbp_agent, BbpCsr.word, FALSE);
		if (via_mcu)
			AsicSendCommandToMcu(pAd, 0x80, 0xff, 0x0, 0x0, TRUE);

		for (k = 0; k < MAX_BUSY_COUNT; k++) {
			RTUSBReadMACRegister(pAd, bbp_agent, &BbpCsr.word);
			if ((BbpCsr.field.Busy == IDLE)
			    || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
				break;
		}

		if ((BbpCsr.field.Busy == IDLE) && (BbpCsr.field.RegNum == Id)) {
			*pValue = (UCHAR) BbpCsr.field.Value;
			break;
		}
	}

	RTMP_SEM_EVENT_UP(&pAd->reg_atomic);

	if ((BbpCsr.field.Busy == BUSY) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_ERR(("BBP read R%d=0x%x fail\n", Id, BbpCsr.word));
		*pValue = pAd->BbpWriteLatch[Id];
		return STATUS_UNSUCCESSFUL;
	}
	return STATUS_SUCCESS;
}

/*
	========================================================================

	Routine Description: Write 8-bit BBP register

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWriteBBPRegister_Direct(RTMP_ADAPTER *pAd, UCHAR Id, UCHAR Value)
{
	BBP_CSR_CFG_STRUC BbpCsr;
	UINT i = 0;
	NTSTATUS status;
	int RET = 0;

	RTMP_SEM_EVENT_WAIT(&(pAd->reg_atomic), RET);

	/* Verify the busy condition */
	do {
		status = RTUSBReadMACRegister(pAd, BBP_CSR_CFG, &BbpCsr.word);
		if (status >= 0) {
			if (!(BbpCsr.field.Busy == BUSY))
				break;
		}
		DBGPRINT(RT_DEBUG_TRACE,
			 ("RTUSBWriteBBPRegister(BBP_CSR_CFG):retry count=%d!\n", i));
		i++;
	} while ((i < RETRY_LIMIT) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)));

	if ((i == RETRY_LIMIT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed!!!\n"));
		RTMP_SEM_EVENT_UP(&(pAd->reg_atomic));
		return STATUS_UNSUCCESSFUL;
	}

	/* Prepare for write material */
	BbpCsr.word = 0;
	BbpCsr.field.fRead = 0;
	BbpCsr.field.Value = Value;
	BbpCsr.field.Busy = 1;
	BbpCsr.field.RegNum = Id;
	RTUSBWriteMACRegister(pAd, BBP_CSR_CFG, BbpCsr.word, FALSE);

	pAd->BbpWriteLatch[Id] = Value;
	RTMP_SEM_EVENT_UP(&(pAd->reg_atomic));

	return STATUS_SUCCESS;
}

/*
	========================================================================

	Routine Description: Write 8-bit BBP register via firmware

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWriteBBPRegister(RTMP_ADAPTER *pAd, UCHAR Id, UCHAR Value)
{
	BBP_CSR_CFG_STRUC BbpCsr;
	int BusyCnt, ret;
	UINT32 bbp_agent;
	BOOLEAN via_mcu = TRUE;


	bbp_agent = ((via_mcu == TRUE) ? H2M_BBP_AGENT : BBP_CSR_CFG);

	RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, ret);
	if (ret != 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", ret));
		return STATUS_UNSUCCESSFUL;
	}

	for (BusyCnt = 0; BusyCnt < MAX_BUSY_COUNT; BusyCnt++) {
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			break;

		RTMP_IO_READ32(pAd, bbp_agent, &BbpCsr.word);
		if (BbpCsr.field.Busy == BUSY)
			continue;
		BbpCsr.word = 0;
		BbpCsr.field.fRead = 0;
		BbpCsr.field.BBP_RW_MODE = 1;
		BbpCsr.field.Busy = 1;
		BbpCsr.field.Value = Value;
		BbpCsr.field.RegNum = Id;
		RTMP_IO_WRITE32(pAd, bbp_agent, BbpCsr.word);
		if (via_mcu)
			AsicSendCommandToMcu(pAd, 0x80, 0xff, 0x0, 0x0, TRUE);
		pAd->BbpWriteLatch[Id] = Value;
		break;
	}

	RTMP_SEM_EVENT_UP(&pAd->reg_atomic);

	if ((BusyCnt == MAX_BUSY_COUNT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_ERR(("BBP write R%d=0x%x fail\n", Id, BbpCsr.word));
		return STATUS_UNSUCCESSFUL;
	}
	return STATUS_SUCCESS;
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
NTSTATUS RTUSBWriteRFRegister(RTMP_ADAPTER *pAd, UINT32 Value)
{
	RF_CSR_CFG0_STRUC PhyCsr4;
	UINT i = 0;
	NTSTATUS status;

	NdisZeroMemory(&PhyCsr4, sizeof(RF_CSR_CFG0_STRUC));

	RTMP_SEM_EVENT_WAIT(&pAd->reg_atomic, status);
	if (status != 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("reg_atomic get failed(ret=%d)\n", status));
		return STATUS_UNSUCCESSFUL;
	}

	status = STATUS_UNSUCCESSFUL;
	do {
		status = RTUSBReadMACRegister(pAd, RF_CSR_CFG0, &PhyCsr4.word);
		if (status >= 0) {
			if (!(PhyCsr4.field.Busy))
				break;
		}
		DBGPRINT(RT_DEBUG_TRACE,
			 ("RTUSBWriteRFRegister(RF_CSR_CFG0):retry count=%d!\n", i));
		i++;
	} while ((i < RETRY_LIMIT) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)));

	if ((i == RETRY_LIMIT) || (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
		DBGPRINT_RAW(RT_DEBUG_ERROR, ("Retry count exhausted or device removed!!!\n"));
		goto done;
	}

	RTUSBWriteMACRegister(pAd, RF_CSR_CFG0, Value, FALSE);
	status = STATUS_SUCCESS;

done:
	RTMP_SEM_EVENT_UP(&pAd->reg_atomic);

	return status;
}
#endif /* RTMP_BBP */

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBReadEEPROM(RTMP_ADAPTER *pAd, USHORT adr, UCHAR *buf, USHORT len)
{
	return RTUSB_VendorRequest(pAd, (USBD_TRANSFER_DIRECTION_IN |
					 USBD_SHORT_TRANSFER_OK),
				   DEVICE_VENDOR_REQUEST_IN, 0x9, 0, adr, buf, len);
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWriteEEPROM(RTMP_ADAPTER *pAd, USHORT adr, UCHAR *buf, USHORT len)
{
	return RTUSB_VendorRequest(pAd, USBD_TRANSFER_DIRECTION_OUT,
				   DEVICE_VENDOR_REQUEST_OUT, 0x8, 0, adr, buf, len);
}

NTSTATUS RTUSBReadEEPROM16(RTMP_ADAPTER *pAd, USHORT offset, USHORT *pData)
{
	NTSTATUS status;
	USHORT localData;

	status = RTUSBReadEEPROM(pAd, offset, (PUCHAR) (&localData), 2);
	if (status == STATUS_SUCCESS)
		*pData = le2cpu16(localData);

	return status;

}

NTSTATUS RTUSBWriteEEPROM16(RTMP_ADAPTER *pAd, USHORT offset, USHORT value)
{
	USHORT tmpVal;

	tmpVal = cpu2le16(value);
	return RTUSBWriteEEPROM(pAd, offset, (PUCHAR) & (tmpVal), 2);
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
VOID RTUSBPutToSleep(RTMP_ADAPTER *pAd)
{
	UINT32 value;

	/* Timeout 0x40 x 50us */
	value = (SLEEPCID << 16) + (OWNERMCU << 24) + (0x40 << 8) + 1;
	RTUSBWriteMACRegister(pAd, 0x7010, value, FALSE);
	RTUSBWriteMACRegister(pAd, 0x404, 0x30, FALSE);
	DBGPRINT_RAW(RT_DEBUG_ERROR, ("Sleep Mailbox testvalue %x\n", value));
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NTSTATUS RTUSBWakeUp(RTMP_ADAPTER *pAd)
{
	return RTUSB_VendorRequest(pAd, USBD_TRANSFER_DIRECTION_OUT,
				   DEVICE_VENDOR_REQUEST_OUT, 0x01, 0x09, 0, NULL, 0);
}

/*
	========================================================================

	Routine Description:

	Arguments:

	Return Value:

	IRQL =

	Note:

	========================================================================
*/
NDIS_STATUS RTUSBEnqueueCmdFromNdis(IN PRTMP_ADAPTER pAd,
				    IN NDIS_OID Oid,
				    IN BOOLEAN SetInformation,
				    IN PVOID pInformationBuffer, IN UINT32 InformationBufferLength)
{
	NDIS_STATUS status;
	PCmdQElmt cmdqelmt = NULL;
	RTMP_OS_TASK *pTask = &pAd->cmdQTask;

	RTMP_OS_TASK_LEGALITY(pTask);
	else
	return NDIS_STATUS_RESOURCES;

	status = os_alloc_mem(pAd, (PUCHAR *) (&cmdqelmt), sizeof(CmdQElmt));
	if ((status != NDIS_STATUS_SUCCESS) || (cmdqelmt == NULL))
		return NDIS_STATUS_RESOURCES;

	cmdqelmt->buffer = NULL;
	if (pInformationBuffer != NULL) {
		status = os_alloc_mem(pAd, (PUCHAR *) &cmdqelmt->buffer, InformationBufferLength);
		if ((status != NDIS_STATUS_SUCCESS) || (cmdqelmt->buffer == NULL)) {
			os_free_mem(NULL, cmdqelmt);
			return NDIS_STATUS_RESOURCES;
		}

		NdisMoveMemory(cmdqelmt->buffer, pInformationBuffer,
			       InformationBufferLength);
		cmdqelmt->bufferlength = InformationBufferLength;

	} else
		cmdqelmt->bufferlength = 0;

	cmdqelmt->command = Oid;
	cmdqelmt->CmdFromNdis = TRUE;
	if (SetInformation == TRUE)
		cmdqelmt->SetOperation = TRUE;
	else
		cmdqelmt->SetOperation = FALSE;

	NdisAcquireSpinLock(&pAd->CmdQLock);
	if (pAd->CmdQ.CmdQState & RTMP_TASK_CAN_DO_INSERT) {
		EnqueueCmd((&pAd->CmdQ), cmdqelmt);
		status = NDIS_STATUS_SUCCESS;
	} else {
		status = NDIS_STATUS_FAILURE;
	}
	NdisReleaseSpinLock(&pAd->CmdQLock);

	if (status == NDIS_STATUS_FAILURE) {
		if (cmdqelmt->buffer)
			os_free_mem(pAd, cmdqelmt->buffer);
		os_free_mem(pAd, cmdqelmt);
	} else
		RTCMDUp(&pAd->cmdQTask);

	return NDIS_STATUS_SUCCESS;
}

/*
    ========================================================================
	Routine Description:
		RTUSB_VendorRequest - Builds a ralink specific request, sends it off to USB endpoint zero and waits for
		completion

	Arguments:
		@pAd:
		@TransferFlags:
		@RequestType: USB message request type value
		@Request: USB message request value
		@Value: USB message value
		@Index: USB message index value
		@TransferBuffer: USB data to be sent
		@TransferBufferLength: Lengths in bytes of the data to be sent

	Context: ! in atomic context

	Return Value:
		NDIS_STATUS_SUCCESS
		NDIS_STATUS_FAILURE

	Note:
		This function sends a simple control message to endpoint zero
		and waits for the message to complete, or CONTROL_TIMEOUT_JIFFIES timeout.
		Because it is synchronous transfer, so don't use this function within an atomic context,
		otherwise system will hang, do be careful.

		TransferBuffer may located in stack region which may not in DMA'able region in some embedded platforms,
		so need to copy TransferBuffer to UsbVendorReqBuf allocated by kmalloc to do DMA transfer.
		Use UsbVendorReq_semaphore to protect this region which may be accessed by multi task.
		Normally, coherent issue is resloved by low-level HC driver, so do not flush this zone by
		RTUSB_VendorRequest.

	========================================================================
*/
NTSTATUS RTUSB_VendorRequest(IN PRTMP_ADAPTER pAd,
			     IN UINT32 TransferFlags,
			     IN UCHAR RequestType,
			     IN UCHAR Request,
			     IN USHORT Value,
			     IN USHORT Index,
			     IN PVOID TransferBuffer, IN UINT32 TransferBufferLength)
{
	int RET = 0;
	POS_COOKIE pObj = (POS_COOKIE) pAd->OS_Cookie;
	static int fail_cnt;
	const int fail_cnt_threshold = 10;
	int RetryCount = 0;	/* RTUSB_CONTROL_MSG retry counts */

#ifndef NEW_WOW_SUPPORT
	if (pAd->PM_FlgSuspend == 1) {
		DBGPRINT(RT_DEBUG_ERROR, ("USB has entered SUSPEND mode\n"));
		return NDIS_STATUS_FAILURE;
	}
#endif /* NEW_WOW_SUPPORT */

	if (TransferBufferLength > 0) {
		ASSERT(TransferBuffer);
		if (!TransferBuffer) {
			DBGPRINT(RT_DEBUG_ERROR,
				 ("TransferBufferLength > 0 but TransferBuffer is NULL"));
			return NDIS_STATUS_FAILURE;
		}
	}

	if (in_interrupt()) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("BUG: RTUSB_VendorRequest is called from invalid context\n"));
		return NDIS_STATUS_FAILURE;
	}
#ifdef NEW_WOW_SUPPORT
	if (pAd->WOW_Cfg.bInSuspendMode & WOW_SUSPEND_COMPLETE) {
		DBGPRINT(RT_DEBUG_INFO, ("[%s] Block Vendor Request\n", __func__));
		return NDIS_STATUS_SUSPEND;
	}
#endif /* NEW_WOW_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef CONFIG_PM
#ifdef USB_SUPPORT_SELECTIVE_SUSPEND
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_SUSPEND))
		return NDIS_STATUS_SUSPEND;
#endif /* USB_SUPPORT_SELECTIVE_SUSPEND */
#endif /* CONFIG_PM */
#endif /* CONFIG_STA_SUPPORT */

	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)) {
		/*DBGPRINT(RT_DEBUG_ERROR, ("WIFI device has been disconnected\n")); */
		return NDIS_STATUS_FAILURE;
	} else if (RTMP_TEST_PSFLAG(pAd, fRTMP_PS_MCU_SLEEP)) {
		/* Do not print error message by default if in Radio_Off case. */
		if (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF))
			DBGPRINT(RT_DEBUG_ERROR, ("MCU has entered sleep mode\n"));
		return NDIS_STATUS_FAILURE;
	}

	ASSERT(TransferBufferLength < MAX_PARAM_BUFFER_SIZE);

	RTMP_SEM_EVENT_WAIT(&(pAd->UsbVendorReq_semaphore), RET);
	if (RET != 0) {
		DBGPRINT(RT_DEBUG_ERROR, ("UsbVendorReq_semaphore get failed\n"));
		return NDIS_STATUS_FAILURE;
	}

	if ((TransferBufferLength > 0)
	    && ((RequestType == DEVICE_VENDOR_REQUEST_OUT)
		|| (RequestType == DEVICE_CLASS_REQUEST_OUT)))
		NdisMoveMemory(pAd->UsbVendorReqBuf, TransferBuffer, TransferBufferLength);

	do {
		RTUSB_CONTROL_MSG(pObj->pUsb_Dev, 0, Request, RequestType, Value,
				  Index, pAd->UsbVendorReqBuf, TransferBufferLength,
				  CONTROL_TIMEOUT_JIFFIES, RET);

		if (RET < 0) {
			DBGPRINT(RT_DEBUG_INFO, ("#\n"));
			if (RET == RTMP_USB_CONTROL_MSG_ENODEV) {
				RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
				break;
			}
			RetryCount++;
			RtmpusecDelay(5000);	/* wait for 5ms */
		}
	} while ((RET < 0) && (RetryCount < MAX_VENDOR_REQ_RETRY_COUNT));

	if ((!(RET < 0)) && (TransferBufferLength > 0)
	    && (RequestType == DEVICE_VENDOR_REQUEST_IN))
		NdisMoveMemory(TransferBuffer, pAd->UsbVendorReqBuf, TransferBufferLength);

	RTMP_SEM_EVENT_UP(&(pAd->UsbVendorReq_semaphore));

	if (RET < 0) {
		DBGPRINT(RT_DEBUG_ERROR,
			 ("RTUSB_VendorRequest failed(%d),TxFlags=0x%x, ReqType=%s, Req=0x%x, Idx=0x%x,pAd->Flags=0x%lx\n",
			  RET, TransferFlags,
			  (RequestType == DEVICE_VENDOR_REQUEST_OUT ? "OUT" : "IN"),
			  Request, Index, pAd->Flags));
		if (Request == 0x2)
			DBGPRINT(RT_DEBUG_ERROR, ("\tRequest Value=0x%04x!\n", Value));

		if (TransferBuffer && (TransferBufferLength > 0))
			hex_dump("Failed TransferBuffer value", TransferBuffer,
				 TransferBufferLength);

		if (RET == RTMP_USB_CONTROL_MSG_ENODEV)
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);

	}

	if (RET < 0) {
		fail_cnt += 1;
		DBGPRINT(RT_DEBUG_ERROR,
			 ("send vendor request fail continuous count = %d\n",
			  fail_cnt));
		if (fail_cnt >= fail_cnt_threshold) {
			DBGPRINT(RT_DEBUG_ERROR, ("Try to Reset Dongle\n"));
			Set_Chip_Reset(pAd, NULL);
		}
		return NDIS_STATUS_FAILURE;
	}

	fail_cnt = 0;

	return NDIS_STATUS_SUCCESS;
}


static NTSTATUS CheckGPIOHdlr(RTMP_ADAPTER *pAd, PCmdQElmt CMDQelmt)
{
#ifdef RALINK_ATE
	if (ATE_ON(pAd)) {
		DBGPRINT(RT_DEBUG_TRACE, ("The driver is in ATE mode now\n"));
		return NDIS_STATUS_SUCCESS;
	}
#endif /* RALINK_ATE */

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd) {
		UINT32 data;

		/* Read GPIO pin2 as Hardware controlled radio state */
		RTUSBReadMACRegister(pAd, GPIO_CTRL_CFG, &data);
		pAd->StaCfg.bHwRadio = (data & 0x04) ? TRUE : FALSE;

		if (pAd->StaCfg.bRadio != (pAd->StaCfg.bHwRadio && pAd->StaCfg.bSwRadio)) {
			pAd->StaCfg.bRadio = (pAd->StaCfg.bHwRadio && pAd->StaCfg.bSwRadio);
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("!!! Radio %s !!!\n",
						      (pAd->StaCfg.bRadio == TRUE ? "On" : "Off")));
			if (pAd->StaCfg.bRadio == TRUE) {
				MlmeRadioOn(pAd);
				pAd->ExtraInfo = EXTRA_INFO_CLEAR;
			} else {
				MlmeRadioOff(pAd);
				pAd->ExtraInfo = HW_RADIO_OFF;
			}
		}
	}
#endif /* CONFIG_STA_SUPPORT */

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS ResetBulkOutHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	INT32 MACValue = 0;
	UCHAR Index = 0;
	int ret = 0;
	PHT_TX_CONTEXT pHTTXContext;
	unsigned long IrqFlags;

	DBGPRINT(RT_DEBUG_TRACE,
		 ("CMDTHREAD_RESET_BULK_OUT(ResetPipeid=0x%0x)===>\n", pAd->bulkResetPipeid));

	/* All transfers must be aborted or cancelled before attempting to reset the pipe. */
	/*RTUSBCancelPendingBulkOutIRP(pAd); */
	/* Wait 10ms to let previous packet that are already in HW FIFO to clear. by MAXLEE 12-25-2007 */
	do {
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			break;
#ifdef NEW_WOW_SUPPORT
		if (pAd->WOW_Cfg.bInSuspendMode & WOW_SUSPEND_COMPLETE)
			break;
#endif

		RTUSBReadMACRegister(pAd, TXRXQ_PCNT, &MACValue);
		if ((MACValue & 0xf00000 /*0x800000 */) == 0)
			break;

		Index++;
		RtmpusecDelay(10000);
	} while (Index < 100);

	USB_CFG_READ(pAd, &MACValue);

	/* 2nd, to prevent Read Register error, we check the validity. */
	if ((MACValue & 0xc00000) == 0)
		USB_CFG_READ(pAd, &MACValue);

	/* 3rd, to prevent Read Register error, we check the validity. */
	if ((MACValue & 0xc00000) == 0)
		USB_CFG_READ(pAd, &MACValue);

	MACValue |= 0x80000;
	USB_CFG_WRITE(pAd, MACValue);

	/* Wait 1ms to prevent next URB to bulkout before HW reset. by MAXLEE 12-25-2007 */
	RtmpusecDelay(1000);

	MACValue &= (~0x80000);
	USB_CFG_WRITE(pAd, MACValue);
	DBGPRINT(RT_DEBUG_TRACE, ("\tSet 0x2a0 bit19. Clear USB DMA TX path\n"));

	/* Wait 5ms to prevent next URB to bulkout before HW reset. by MAXLEE 12-25-2007 */
	/*RtmpusecDelay(5000); */

	if ((pAd->bulkResetPipeid & BULKOUT_MGMT_RESET_FLAG) == BULKOUT_MGMT_RESET_FLAG) {
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

		if (pAd->MgmtRing.TxSwFreeIdx <
		    MGMT_RING_SIZE /* pMLMEContext->bWaitingBulkOut == TRUE */)
			RTUSB_SET_BULK_FLAG(pAd, fRTUSB_BULK_OUT_MLME);

		RTUSBKickBulkOut(pAd);
		DBGPRINT(RT_DEBUG_TRACE, ("\tTX MGMT RECOVER Done!\n"));
	} else {
		pHTTXContext = &(pAd->TxContext[pAd->bulkResetPipeid]);

		/*NdisAcquireSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]); */
		RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);
		if (pAd->BulkOutPending[pAd->bulkResetPipeid] == FALSE) {
			pAd->BulkOutPending[pAd->bulkResetPipeid] = TRUE;
			pHTTXContext->IRPPending = TRUE;
			pAd->watchDogTxPendingCnt[pAd->bulkResetPipeid] = 1;

			/* no matter what, clean the flag */
			RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

			/*NdisReleaseSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]); */
			RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

#ifdef RALINK_ATE
			if (ATE_ON(pAd))
				ret = ATEResetBulkOut(pAd);
			else
#endif /* RALINK_ATE */
			{
				RTUSBInitHTTxDesc(pAd, pHTTXContext, pAd->bulkResetPipeid,
						  pHTTXContext->BulkOutSize,
						  RtmpUsbBulkOutDataPacketComplete);

#ifdef USB_BULK_BUF_ALIGMENT
				ret = RTUSB_SUBMIT_URB(pHTTXContext->pUrb[pHTTXContext->CurtBulkIdx]);
#else
				ret = RTUSB_SUBMIT_URB(pHTTXContext->pUrb);
#endif /* USB_BULK_BUF_ALIGMENT */
				if (ret != 0) {
					RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid],
						      IrqFlags);
					pAd->BulkOutPending[pAd->bulkResetPipeid] = FALSE;
					pHTTXContext->IRPPending = FALSE;
					pAd->watchDogTxPendingCnt[pAd->bulkResetPipeid] = 0;
					RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid],
							IrqFlags);

					DBGPRINT(RT_DEBUG_ERROR,
						 ("CMDTHREAD_RESET_BULK_OUT:Submit Tx URB failed %d\n",
						  ret));
				} else {
					RTMP_INT_LOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid],
						      IrqFlags);

					DBGPRINT(RT_DEBUG_TRACE,
						 ("\tCMDTHREAD_RESET_BULK_OUT: TxContext[%d]:CWPos=%ld, NBPos=%ld, ENBPos=%ld, bCopy=%d, pending=%d!\n",
						  pAd->bulkResetPipeid,
						  pHTTXContext->CurWritePosition,
						  pHTTXContext->NextBulkOutPosition,
						  pHTTXContext->ENextBulkOutPosition,
						  pHTTXContext->bCopySavePad,
						  pAd->BulkOutPending[pAd->bulkResetPipeid]));
					DBGPRINT(RT_DEBUG_TRACE,
						 ("\t\tBulkOut Req=0x%lx, Complete=0x%lx, Other=0x%lx\n",
						  pAd->BulkOutReq, pAd->BulkOutComplete,
						  pAd->BulkOutCompleteOther));

					RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid],
							IrqFlags);

					DBGPRINT(RT_DEBUG_TRACE,
						 ("\tCMDTHREAD_RESET_BULK_OUT: Submit Tx DATA URB for failed BulkReq(0x%lx) Done, status=%d!\n",
						  pAd->bulkResetReq[pAd->bulkResetPipeid],
#ifdef USB_BULK_BUF_ALIGMENT
						  RTMP_USB_URB_STATUS_GET(pHTTXContext->pUrb
									  [pHTTXContext->
									   CurtBulkIdx])));
#else
						  RTMP_USB_URB_STATUS_GET(pHTTXContext->pUrb)));
#endif /* USB_BULK_BUF_ALIGMENT */

				}
			}
		} else {
			/*NdisReleaseSpinLock(&pAd->BulkOutLock[pAd->bulkResetPipeid]); */
			/*RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags); */

			DBGPRINT(RT_DEBUG_ERROR,
				 ("CmdThread : TX DATA RECOVER FAIL for BulkReq(0x%lx) because BulkOutPending[%d] is TRUE!\n",
				  pAd->bulkResetReq[pAd->bulkResetPipeid], pAd->bulkResetPipeid));

			if (pAd->bulkResetPipeid == 0) {
				UCHAR pendingContext = 0;
				PHT_TX_CONTEXT pHTTXContext =
				    (PHT_TX_CONTEXT) (&pAd->TxContext[pAd->bulkResetPipeid]);
				PTX_CONTEXT pMLMEContext =
				    (PTX_CONTEXT) (pAd->MgmtRing.Cell[pAd->MgmtRing.TxDmaIdx].
						   AllocVa);
				PTX_CONTEXT pNULLContext = (PTX_CONTEXT) (&pAd->PsPollContext);
				PTX_CONTEXT pPsPollContext = (PTX_CONTEXT) (&pAd->NullContext);

				if (pHTTXContext->IRPPending)
					pendingContext |= 1;
				else if (pMLMEContext->IRPPending)
					pendingContext |= 2;
				else if (pNULLContext->IRPPending)
					pendingContext |= 4;
				else if (pPsPollContext->IRPPending)
					pendingContext |= 8;
				else
					pendingContext = 0;

				DBGPRINT(RT_DEBUG_ERROR,
					 ("\tTX Occupied by %d!\n", pendingContext));
			}

			/* no matter what, clean the flag */
			RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);

			RTMP_INT_UNLOCK(&pAd->BulkOutLock[pAd->bulkResetPipeid], IrqFlags);

			RTUSB_SET_BULK_FLAG(pAd,
					    (fRTUSB_BULK_OUT_DATA_NORMAL << pAd->bulkResetPipeid));
		}

		RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, MAX_TX_PROCESS);
		/*RTUSBKickBulkOut(pAd); */
	}

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_OUT<===\n"));
	return NDIS_STATUS_SUCCESS;

}

/* All transfers must be aborted or cancelled before attempting to reset the pipe.*/
static NTSTATUS ResetBulkInHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	UINT32 MACValue;
	NTSTATUS ntStatus;

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_IN === >\n"));

#ifdef CONFIG_STA_SUPPORT
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF)) {
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);
		return NDIS_STATUS_SUCCESS;
	}
#endif /* CONFIG_STA_SUPPORT */

#ifdef RALINK_ATE
	if (ATE_ON(pAd))
		ATEResetBulkIn(pAd);
	else
#endif /* RALINK_ATE */
	{
		/*while ((atomic_read(&pAd->PendingRx) > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) */
		if ((pAd->PendingRx > 0) && (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))) {
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("BulkIn IRP Pending!!!\n"));
			RTUSBCancelPendingBulkInIRP(pAd);
			RtmpusecDelay(100000);
			pAd->PendingRx = 0;
		}
	}

	/* Wait 10ms before reading register. */
	RtmpusecDelay(10000);
	ntStatus = RTUSBReadMACRegister(pAd, MAC_CSR0, &MACValue);

	/* It must be removed. Or ATE will have no RX success. */
	if ((NT_SUCCESS(ntStatus) == TRUE) &&
		    (!(RTMP_TEST_FLAG
			       (pAd,
					(fRTMP_ADAPTER_RESET_IN_PROGRESS |
						 fRTMP_ADAPTER_RADIO_OFF |
						 fRTMP_ADAPTER_HALT_IN_PROGRESS |
						 fRTMP_ADAPTER_NIC_NOT_EXIST))))) {
		UCHAR i;

		if (RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_RADIO_OFF |
					 fRTMP_ADAPTER_HALT_IN_PROGRESS |
					 fRTMP_ADAPTER_NIC_NOT_EXIST)))
			return NDIS_STATUS_SUCCESS;

		pAd->NextRxBulkInPosition = pAd->RxContext[pAd->NextRxBulkInIndex].BulkInOffset;

		DBGPRINT(RT_DEBUG_TRACE,
			 ("BULK_IN_RESET: NBIIdx=0x%x,NBIRIdx=0x%x, BIRPos=0x%lx. BIReq=x%lx, BIComplete=0x%lx, BICFail0x%lx\n",
			  pAd->NextRxBulkInIndex, pAd->NextRxBulkInReadIndex,
			  pAd->NextRxBulkInPosition, pAd->BulkInReq, pAd->BulkInComplete,
			  pAd->BulkInCompleteFail));

		for (i = 0; i < RX_RING_SIZE; i++) {
			DBGPRINT(RT_DEBUG_TRACE,
				 ("\tRxContext[%d]: IRPPending=%d, InUse=%d, Readable=%d!\n", i,
				  pAd->RxContext[i].IRPPending, pAd->RxContext[i].InUse,
				  pAd->RxContext[i].Readable));
		}

		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);

		for (i = 0; i < pAd->CommonCfg.NumOfBulkInIRP; i++) {
			/*RTUSBBulkReceive(pAd); */
			PRX_CONTEXT pRxContext;
			PURB pUrb;
			int ret = 0;
			unsigned long IrqFlags;

			RTMP_IRQ_LOCK(&pAd->BulkInLock, IrqFlags);
			pRxContext = &(pAd->RxContext[pAd->NextRxBulkInIndex]);

			if ((pAd->PendingRx > 0) || (pRxContext->Readable == TRUE)
			    || (pRxContext->InUse == TRUE)) {
				RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);
				return NDIS_STATUS_SUCCESS;
			}

			pRxContext->InUse = TRUE;
			pRxContext->IRPPending = TRUE;
			pAd->PendingRx++;
			pAd->BulkInReq++;
			RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);

			/* Init Rx context descriptor */
			RTUSBInitRxDesc(pAd, pRxContext);
			pUrb = pRxContext->pUrb;
			ret = RTUSB_SUBMIT_URB(pUrb);
			if (ret != 0) {	/* fail */
				RTMP_IRQ_LOCK(&pAd->BulkInLock, IrqFlags);
				pRxContext->InUse = FALSE;
				pRxContext->IRPPending = FALSE;
				pAd->PendingRx--;
				pAd->BulkInReq--;
				RTMP_IRQ_UNLOCK(&pAd->BulkInLock, IrqFlags);
				DBGPRINT(RT_DEBUG_ERROR,
					 ("CMDTHREAD_RESET_BULK_IN: Submit Rx URB failed(%d), status=%d\n",
					  ret, RTMP_USB_URB_STATUS_GET(pUrb)));
			} else {	/* success */
				/* DBGPRINT(RT_DEBUG_TRACE, ("BIDone, Pend=%d,BIIdx=%d,BIRIdx=%d!\n", */
				/* pAd->PendingRx, pAd->NextRxBulkInIndex, pAd->NextRxBulkInReadIndex)); */
				DBGPRINT_RAW(RT_DEBUG_TRACE,
					     ("CMDTHREAD_RESET_BULK_IN: Submit Rx URB Done, status=%d!\n",
					      RTMP_USB_URB_STATUS_GET(pUrb)));
				ASSERT((pRxContext->InUse == pRxContext->IRPPending));
			}
		}

	} else {
		/* Card must be removed */
		if (NT_SUCCESS(ntStatus) != TRUE) {
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST);
			DBGPRINT_RAW(RT_DEBUG_ERROR,
				     ("CMDTHREAD_RESET_BULK_IN: Read Register Failed!Card must be removed!!\n\n"));
		} else
			DBGPRINT_RAW(RT_DEBUG_ERROR,
				     ("CMDTHREAD_RESET_BULK_IN: Cannot do bulk in because flags(0x%lx) on !\n",
				      pAd->Flags));
	}

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("CmdThread : CMDTHREAD_RESET_BULK_IN <===\n"));
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetAsicWcidHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_SET_ASIC_WCID SetAsicWcid;
	USHORT offset;
	UINT32 MACValue, MACRValue = 0;

	SetAsicWcid = *((PRT_SET_ASIC_WCID) (CMDQelmt->buffer));

	if (SetAsicWcid.WCID >= MAX_LEN_OF_MAC_TABLE)
		return NDIS_STATUS_FAILURE;

	offset = MAC_WCID_BASE + ((UCHAR) SetAsicWcid.WCID) * HW_WCID_ENTRY_SIZE;

	DBGPRINT_RAW(RT_DEBUG_TRACE,
		     ("CmdThread : CMDTHREAD_SET_ASIC_WCID : WCID = %ld, SetTid	 = %lx, DeleteTid = %lx.\n",
		      SetAsicWcid.WCID, SetAsicWcid.SetTid, SetAsicWcid.DeleteTid));

	MACValue =
	    (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[3] << 24) +
	    (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[2] << 16) +
	    (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[1] << 8) +
	    (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[0]);

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("1-MACValue= %x,\n", MACValue));
	RTUSBWriteMACRegister(pAd, offset, MACValue, FALSE);
	/* Read bitmask */
	RTUSBReadMACRegister(pAd, offset + 4, &MACRValue);
	if (SetAsicWcid.DeleteTid != 0xffffffff)
		MACRValue &= (~SetAsicWcid.DeleteTid);
	if (SetAsicWcid.SetTid != 0xffffffff)
		MACRValue |= (SetAsicWcid.SetTid);

	MACRValue &= 0xffff0000;
	MACValue =
	    (pAd->MacTab.Content[SetAsicWcid.WCID].Addr[5] << 8) +
	    pAd->MacTab.Content[SetAsicWcid.WCID].Addr[4];
	MACValue |= MACRValue;
	RTUSBWriteMACRegister(pAd, offset + 4, MACValue, FALSE);

	DBGPRINT_RAW(RT_DEBUG_TRACE, ("2-MACValue= %x,\n", MACValue));

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS DelAsicWcidHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	RT_SET_ASIC_WCID SetAsicWcid;

	SetAsicWcid = *((PRT_SET_ASIC_WCID) (CMDQelmt->buffer));

	if (SetAsicWcid.WCID >= MAX_LEN_OF_MAC_TABLE)
		return NDIS_STATUS_FAILURE;

	AsicDelWcidTab(pAd, (UCHAR) SetAsicWcid.WCID);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetWcidSecInfoHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_SEC_INFO pInfo;

	pInfo = (PRT_ASIC_WCID_SEC_INFO) CMDQelmt->buffer;
	RTMPSetWcidSecurityInfo(pAd,
				pInfo->BssIdx,
				pInfo->KeyIdx, pInfo->CipherAlg, pInfo->Wcid, pInfo->KeyTabFlag);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetAsicWcidIVEIVHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_IVEIV_ENTRY pInfo;

	pInfo = (PRT_ASIC_WCID_IVEIV_ENTRY) CMDQelmt->buffer;
	AsicUpdateWCIDIVEIV(pAd, pInfo->Wcid, pInfo->Iv, pInfo->Eiv);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetAsicWcidAttrHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_WCID_ATTR_ENTRY pInfo;

	pInfo = (PRT_ASIC_WCID_ATTR_ENTRY) CMDQelmt->buffer;
	AsicUpdateWcidAttributeEntry(pAd,
				     pInfo->BssIdx,
				     pInfo->KeyIdx,
				     pInfo->CipherAlg, pInfo->Wcid, pInfo->KeyTabFlag);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SETAsicSharedKeyHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_SHARED_KEY pInfo;

	pInfo = (PRT_ASIC_SHARED_KEY) CMDQelmt->buffer;
	AsicAddSharedKeyEntry(pAd, pInfo->BssIndex, pInfo->KeyIdx, &pInfo->CipherKey);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetAsicPairwiseKeyHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_PAIRWISE_KEY pInfo;

	pInfo = (PRT_ASIC_PAIRWISE_KEY) CMDQelmt->buffer;
	AsicAddPairwiseKeyEntry(pAd, pInfo->WCID, &pInfo->CipherKey);

	return NDIS_STATUS_SUCCESS;
}

#ifdef CONFIG_STA_SUPPORT
static NTSTATUS SetPortSecuredHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	STA_PORT_SECURED(pAd);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_STA_SUPPORT */

static NTSTATUS RemovePairwiseKeyHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	UCHAR Wcid = *((PUCHAR) (CMDQelmt->buffer));

	AsicRemovePairwiseKeyEntry(pAd, Wcid);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS SetClientMACEntryHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_SET_ASIC_WCID pInfo;

	pInfo = (PRT_SET_ASIC_WCID) CMDQelmt->buffer;
	AsicUpdateRxWCIDTable(pAd, pInfo->WCID, pInfo->Addr);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS UpdateProtectHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PRT_ASIC_PROTECT_INFO pAsicProtectInfo;

	pAsicProtectInfo = (PRT_ASIC_PROTECT_INFO) CMDQelmt->buffer;
	AsicUpdateProtect(pAd, pAsicProtectInfo->OperationMode, pAsicProtectInfo->SetMask,
			  pAsicProtectInfo->bDisableBGProtect, pAsicProtectInfo->bNonGFExist);

	return NDIS_STATUS_SUCCESS;
}

#ifdef CFG_TDLS_SUPPORT
static NTSTATUS CFGTdlsAutoTeardownHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	UCHAR Addr[MAC_ADDR_LEN];

	COPY_MAC_ADDR(Addr, (UCHAR *) (CMDQelmt->buffer));
	cfg_auto_teardown(pAd, Addr);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS TdlsSendCHSWSetupHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	PCFG_TDLS_CHSW_PARAM pTdlsCHSWParam;

	pTdlsCHSWParam = (PCFG_TDLS_CHSW_PARAM) CMDQelmt->buffer;

	if (pTdlsCHSWParam->cmd == 1)
		;	/* cfg_tdls_send_CH_SW_SETUP(pAd,1,0,0,0,0,0,0,0,0,0,0,0); */
	else {
		UINT32 start_time_tsf = 0;
		/* TDLS_TIMESTAMP_GET(pAd,start_time_tsf); */
		/* RTMP_IO_READ32(pAd, TSF_TIMER_DW0, &start_time_tsf); */
		cfg_tdls_send_CH_SW_SETUP(pAd, 0, start_time_tsf);
	}
	return NDIS_STATUS_SUCCESS;
}
#endif /* CFG_TDLS_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
static NTSTATUS APUpdateCapabilityAndErpieHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	APUpdateCapabilityAndErpIe(pAd);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
static NTSTATUS _802_11_CounterMeasureHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd) {
		MAC_TABLE_ENTRY *pEntry;

		pEntry = (MAC_TABLE_ENTRY *) CMDQelmt->buffer;
		HandleCounterMeasure(pAd, pEntry);
	}

	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
static NTSTATUS SetPSMBitHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd) {
		USHORT *pPsm = (USHORT *) CMDQelmt->buffer;

		MlmeSetPsmBit(pAd, *pPsm);
	}

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS ForceWakeUpHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	    AsicForceWakeup(pAd, TRUE);

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS ForceSleepAutoWakeupHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	USHORT TbttNumToNextWakeUp;
	USHORT NextDtim = pAd->StaCfg.DtimPeriod;
	ULONG Now;

	NdisGetSystemUpTime(&Now);
	NextDtim -= (USHORT) (Now - pAd->StaCfg.LastBeaconRxTime) / pAd->CommonCfg.BeaconPeriod;

	TbttNumToNextWakeUp = pAd->StaCfg.DefaultListenCount;
	if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM) && (TbttNumToNextWakeUp > NextDtim))
		TbttNumToNextWakeUp = NextDtim;

	RTMP_SET_PSM_BIT(pAd, PWR_SAVE);

	/* if WMM-APSD is failed, try to disable following line */
	/* AsicSleepThenAutoWakeup(pAd, TbttNumToNextWakeUp); */

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS QkeriodicExecutHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	StaQuickResponeForRateUpExec(NULL, pAd, NULL, NULL);
	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
static NTSTATUS APEnableTXBurstHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd) {
		EDCA_AC_CFG_STRUC Ac0Cfg;

		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_ENABLE_TX_BURST\n"));

		RTUSBReadMACRegister(pAd, EDCA_AC0_CFG, &Ac0Cfg.word);
		Ac0Cfg.field.AcTxop = 0x20;
		RTUSBWriteMACRegister(pAd, EDCA_AC0_CFG, Ac0Cfg.word, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS APDisableTXBurstHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd) {
		EDCA_AC_CFG_STRUC Ac0Cfg;

		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_DISABLE_TX_BURST\n"));

		RTUSBReadMACRegister(pAd, EDCA_AC0_CFG, &Ac0Cfg.word);
		Ac0Cfg.field.AcTxop = 0x0;
		RTUSBWriteMACRegister(pAd, EDCA_AC0_CFG, Ac0Cfg.word, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS APAdjustEXPAckTimeHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd) {
		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_ADJUST_EXP_ACK_TIME\n"));
		RTUSBWriteMACRegister(pAd, EXP_ACK_TIME, 0x005400ca, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS APRecoverEXPAckTimeHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd) {
		DBGPRINT(RT_DEBUG_TRACE, ("CmdThread::CMDTHREAD_AP_RECOVER_EXP_ACK_TIME\n"));
		RTUSBWriteMACRegister(pAd, EXP_ACK_TIME, 0x002400ca, FALSE);
	}

	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT */

#ifdef LED_CONTROL_SUPPORT
static NTSTATUS SetLEDStatusHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	UCHAR LEDStatus = *((PUCHAR) (CMDQelmt->buffer));

	RTMPSetLEDStatus(pAd, LEDStatus);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: CMDTHREAD_SET_LED_STATUS (LEDStatus = %d)\n",
				  __func__, LEDStatus));

	return NDIS_STATUS_SUCCESS;
}
#endif /* LED_CONTROL_SUPPORT */

#ifdef WSC_INCLUDED
#ifdef WSC_LED_SUPPORT
/*WPS LED MODE 10*/
static NTSTATUS LEDWPSMode10Hdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	UINT WPSLedMode10 = *((PUINT) (CMDQelmt->buffer));

	DBGPRINT(RT_DEBUG_INFO, ("WPS LED mode 10::ON or Flash or OFF : %x\n", WPSLedMode10));

	switch (WPSLedMode10) {
	case LINK_STATUS_WPS_MODE10_TURN_ON:
		RTMPSetLEDStatus(pAd, LED_WPS_MODE10_TURN_ON);
		break;
	case LINK_STATUS_WPS_MODE10_FLASH:
		RTMPSetLEDStatus(pAd, LED_WPS_MODE10_FLASH);
		break;
	case LINK_STATUS_WPS_MODE10_TURN_OFF:
		RTMPSetLEDStatus(pAd, LED_WPS_MODE10_TURN_OFF);
		break;
	default:
		DBGPRINT(RT_DEBUG_INFO, ("WPS LED mode 10:: No this status %d!!!\n", WPSLedMode10));
		break;
	}

	return NDIS_STATUS_SUCCESS;
}
#endif /* WSC_LED_SUPPORT */
#endif /* WSC_INCLUDED */

#ifdef CONFIG_AP_SUPPORT
static NTSTATUS ChannelRescanHdlr(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	DBGPRINT(RT_DEBUG_TRACE, ("cmd> Re-scan channel!\n"));

	pAd->CommonCfg.Channel = AP_AUTO_CH_SEL(pAd, TRUE);
	/* If WMODE_CAP_N(phymode) and BW=40 check extension channel, after select channel  */
	N_ChannelCheck(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("cmd> Switch to %d!\n", pAd->CommonCfg.Channel));
	APStop(pAd);
	APStartUp(pAd);

#ifdef AP_QLOAD_SUPPORT
	QBSS_LoadAlarmResume(pAd);
#endif /* AP_QLOAD_SUPPORT */

	return NDIS_STATUS_SUCCESS;
}
#endif /* CONFIG_AP_SUPPORT */

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
static NTSTATUS RegHintHdlr(RTMP_ADAPTER *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_CRDA_REG_HINT(pAd, CMDQelmt->buffer, CMDQelmt->bufferlength);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS RegHint11DHdlr(RTMP_ADAPTER *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_CRDA_REG_HINT11D(pAd, CMDQelmt->buffer, CMDQelmt->bufferlength);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS RT_Mac80211_ScanEnd(RTMP_ADAPTER *pAd, IN PCmdQElmt CMDQelmt)
{
	RT_CFG80211_SCAN_END(pAd, FALSE);
	return NDIS_STATUS_SUCCESS;
}

static NTSTATUS RT_Mac80211_ConnResultInfom(RTMP_ADAPTER *pAd, IN PCmdQElmt CMDQelmt)
{
#ifdef CONFIG_STA_SUPPORT
	RT_CFG80211_CONN_RESULT_INFORM(pAd, pAd->MlmeAux.Bssid,
				       pAd->StaCfg.ReqVarIEs, pAd->StaCfg.ReqVarIELen,
				       CMDQelmt->buffer, CMDQelmt->bufferlength, TRUE);
#endif /*CONFIG_STA_SUPPORT */
	return NDIS_STATUS_SUCCESS;
}
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */


#ifdef STREAM_MODE_SUPPORT
static NTSTATUS UpdateTXChainAddress(RTMP_ADAPTER *pAd, IN PCmdQElmt CMDQelmt)
{
	AsicUpdateTxChainAddress(pAd, CMDQelmt->buffer);
	return NDIS_STATUS_SUCCESS;
}
#endif /* STREAM_MODE_SUPPORT */

#ifdef DOT11Z_TDLS_SUPPORT
static NTSTATUS TdlsReceiveNotifyFrame(IN PRTMP_ADAPTER pAd, IN PCmdQElmt CMDQelmt)
{
	TDLS_EnableMacTx(pAd);
	TDLS_EnablePktChannel(pAd, FIFO_HCCA);
	RTMP_CLEAR_MORE_FLAG(pAd, fRTMP_ADAPTER_DISABLE_DEQUEUE);
	RTMP_OS_NETDEV_WAKE_QUEUE(pAd->net_dev);
	return NDIS_STATUS_SUCCESS;
}
#endif /* DOT11Z_TDLS_SUPPORT */

typedef NTSTATUS(*CMDHdlr) (RTMP_ADAPTER *pAd, IN PCmdQElmt CMDQelmt);

static CMDHdlr CMDHdlrTable[] = {
	ResetBulkOutHdlr,	/* CMDTHREAD_RESET_BULK_OUT */
	ResetBulkInHdlr,	/* CMDTHREAD_RESET_BULK_IN */
	CheckGPIOHdlr,		/* CMDTHREAD_CHECK_GPIO */
	SetAsicWcidHdlr,	/* CMDTHREAD_SET_ASIC_WCID */
	DelAsicWcidHdlr,	/* CMDTHREAD_DEL_ASIC_WCID */
	SetClientMACEntryHdlr,	/* CMDTHREAD_SET_CLIENT_MAC_ENTRY */

#ifdef CONFIG_STA_SUPPORT
	SetPSMBitHdlr,		/* CMDTHREAD_SET_PSM_BIT */
	ForceWakeUpHdlr,	/* CMDTHREAD_FORCE_WAKE_UP */
	ForceSleepAutoWakeupHdlr,	/* CMDTHREAD_FORCE_SLEEP_AUTO_WAKEUP */
	QkeriodicExecutHdlr,	/* CMDTHREAD_QKERIODIC_EXECUT */
#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
	APUpdateCapabilityAndErpieHdlr,	/* CMDTHREAD_AP_UPDATE_CAPABILITY_AND_ERPIE */
	APEnableTXBurstHdlr,	/* CMDTHREAD_AP_ENABLE_TX_BURST */
	APDisableTXBurstHdlr,	/* CMDTHREAD_AP_DISABLE_TX_BURST */
	APAdjustEXPAckTimeHdlr,	/* CMDTHREAD_AP_ADJUST_EXP_ACK_TIME */
	APRecoverEXPAckTimeHdlr,	/* CMDTHREAD_AP_RECOVER_EXP_ACK_TIME */
	ChannelRescanHdlr,	/* CMDTHREAD_CHAN_RESCAN */
#else
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* CONFIG_AP_SUPPORT */

#ifdef LED_CONTROL_SUPPORT
	SetLEDStatusHdlr,	/* CMDTHREAD_SET_LED_STATUS */
#else
	NULL,
#endif /* LED_CONTROL_SUPPORT */

#ifdef WSC_INCLUDED
#ifdef WSC_LED_SUPPORT
	LEDWPSMode10Hdlr,	/* CMDTHREAD_LED_WPS_MODE10 */
#else
	NULL,
#endif /* WSC_LED_SUPPORT */

#else
	NULL,
#endif /* WSC_INCLUDED */

	/* Security related */
	SetWcidSecInfoHdlr,	/* CMDTHREAD_SET_WCID_SEC_INFO */
	SetAsicWcidIVEIVHdlr,	/* CMDTHREAD_SET_ASIC_WCID_IVEIV */
	SetAsicWcidAttrHdlr,	/* CMDTHREAD_SET_ASIC_WCID_ATTR */
	SETAsicSharedKeyHdlr,	/* CMDTHREAD_SET_ASIC_SHARED_KEY */
	SetAsicPairwiseKeyHdlr,	/* CMDTHREAD_SET_ASIC_PAIRWISE_KEY */
	RemovePairwiseKeyHdlr,	/* CMDTHREAD_REMOVE_PAIRWISE_KEY */

#ifdef CONFIG_STA_SUPPORT
	SetPortSecuredHdlr,	/* CMDTHREAD_SET_PORT_SECURED */
#else
	NULL,
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
	_802_11_CounterMeasureHdlr,	/* CMDTHREAD_802_11_COUNTER_MEASURE */
#else
	NULL,
#endif /* CONFIG_AP_SUPPORT */

	UpdateProtectHdlr,	/* CMDTHREAD_UPDATE_PROTECT */

#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
	RegHintHdlr,
	RegHint11DHdlr,
	RT_Mac80211_ScanEnd,
	RT_Mac80211_ConnResultInfom,
#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* RT_CFG80211_SUPPORT */

#else
	NULL,
	NULL,
	NULL,
	NULL,
#endif /* LINUX */

	NULL,

	NULL,

#ifdef STREAM_MODE_SUPPORT
	UpdateTXChainAddress,	/* CMDTHREAD_UPDATE_TX_CHAIN_ADDRESS */
#else
	NULL,
#endif /* STREAM_MODE_SUPPORT */

	NULL, /* CMDTHREAD_RESPONSE_EVENT_CALLBACK */

#ifdef CFG_TDLS_SUPPORT
	TdlsSendCHSWSetupHdlr,	/* CMDTHREAD_TDLS_SEND_CH_SW_SETUP */
	CFGTdlsAutoTeardownHdlr,	/* CMDTHREAD_TDLS_AUTO_TEARDOWN */
#else
	NULL,
	NULL,
#endif /* CFG_TDLS_SUPPORT */
};

static inline BOOLEAN ValidCMD(IN PCmdQElmt CMDQelmt)
{
	SHORT CMDIndex = CMDQelmt->command - CMDTHREAD_FIRST_CMD_ID;
	USHORT CMDHdlrTableLength = sizeof(CMDHdlrTable) / sizeof(CMDHdlr);

	if ((CMDIndex >= 0) && (CMDIndex < CMDHdlrTableLength)) {
		if (CMDHdlrTable[CMDIndex] > 0)
			return TRUE;

		DBGPRINT(RT_DEBUG_ERROR,
			 ("No corresponding CMDHdlr for this CMD(%x)\n",
			  CMDQelmt->command));
		return FALSE;

	}

	DBGPRINT(RT_DEBUG_ERROR, ("CMD(%x) is out of boundary\n", CMDQelmt->command));
	return FALSE;
}

VOID CMDHandler(RTMP_ADAPTER *pAd)
{
	PCmdQElmt cmdqelmt;
	NDIS_STATUS NdisStatus = NDIS_STATUS_SUCCESS;
	NTSTATUS ntStatus;
/*	unsigned long	IrqFlags;*/

	while (pAd && pAd->CmdQ.size > 0) {
		NdisStatus = NDIS_STATUS_SUCCESS;

		NdisAcquireSpinLock(&pAd->CmdQLock);
		RTThreadDequeueCmd(&pAd->CmdQ, &cmdqelmt);
		NdisReleaseSpinLock(&pAd->CmdQLock);

		if (cmdqelmt == NULL)
			break;


		if (!(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)
		      || RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS))) {
			if (ValidCMD(cmdqelmt))
				ntStatus =
				    (*CMDHdlrTable[cmdqelmt->command - CMDTHREAD_FIRST_CMD_ID])
				    (pAd, cmdqelmt);
		}

		if (cmdqelmt->CmdFromNdis == TRUE) {
			if (cmdqelmt->buffer != NULL)
				os_free_mem(pAd, cmdqelmt->buffer);
			os_free_mem(pAd, cmdqelmt);
		} else {
			if ((cmdqelmt->buffer != NULL) && (cmdqelmt->bufferlength != 0))
				os_free_mem(pAd, cmdqelmt->buffer);
			os_free_mem(pAd, cmdqelmt);
		}
	}			/* end of while */
}

VOID RTUSBWatchDog(RTMP_ADAPTER *pAd)
{
#ifdef RTMP_MAC
	PHT_TX_CONTEXT pHTTXContext;
	int idx;
	ULONG irqFlags;
	PURB pUrb;
	BOOLEAN needDumpSeq = FALSE;
	UINT32 MACValue;
#endif /* endif */

	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
		return;

#ifdef CONFIG_STA_SUPPORT
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
		return;
#endif /* CONFIG_STA_SUPPORT */

#ifdef RLT_MAC
	/* TODO: shiang-usw, need to check if this function still required!! */
	if (pAd->chipCap.hif_type == HIF_RLT)
		return;
#endif /* RLT_MAC */

#ifdef RTMP_MAC
	idx = 0;
	RTMP_IO_READ32(pAd, TXRXQ_PCNT, &MACValue);
	if ((MACValue & 0xff) != 0) {
		DBGPRINT(RT_DEBUG_TRACE,
			 ("TX QUEUE 0 Not EMPTY(Value=0x%0x). !!!!!!!!!!!!!!!\n", MACValue));
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf40012);
		while ((MACValue & 0xff) != 0 && (idx++ < 10)) {
			RTMP_IO_READ32(pAd, TXRXQ_PCNT, &MACValue);
			RtmpusecDelay(1);
		}
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf40006);
	}

	idx = 0;
	if ((MACValue & 0xff00) != 0) {
		DBGPRINT(RT_DEBUG_TRACE,
			 ("TX QUEUE 1 Not EMPTY(Value=0x%0x). !!!!!!!!!!!!!!!\n", MACValue));
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf4000a);
		while ((MACValue & 0xff00) != 0 && (idx++ < 10)) {
			RTMP_IO_READ32(pAd, TXRXQ_PCNT, &MACValue);
			RtmpusecDelay(1);
		}
		RTMP_IO_WRITE32(pAd, PBF_CFG, 0xf40006);
	}

	if (pAd->watchDogRxOverFlowCnt >= 2) {
		DBGPRINT(RT_DEBUG_TRACE,
			 ("Maybe the Rx Bulk-In hanged! Cancel the pending Rx bulks request!\n"));
		if ((!RTMP_TEST_FLAG
		     (pAd,
		      (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_BULKIN_RESET |
		       fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST)))) {
			DBGPRINT(RT_DEBUG_TRACE,
				 ("Call CMDTHREAD_RESET_BULK_IN to cancel the pending Rx Bulk!\n"));
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_BULKIN_RESET);
			RTEnqueueInternalCmd(pAd, CMDTHREAD_RESET_BULK_IN, NULL, 0);
			needDumpSeq = TRUE;
		}
		pAd->watchDogRxOverFlowCnt = 0;
	}

	for (idx = 0; idx < NUM_OF_TX_RING; idx++) {
		pUrb = NULL;

		RTMP_IRQ_LOCK(&pAd->BulkOutLock[idx], irqFlags);
/*		if ((pAd->BulkOutPending[idx] == TRUE) && pAd->watchDogTxPendingCnt)*/
		if (pAd->BulkOutPending[idx] == TRUE) {
			pAd->watchDogTxPendingCnt[idx]++;

			if ((pAd->watchDogTxPendingCnt[idx] > 2) &&
			    (!RTMP_TEST_FLAG
			     (pAd,
			      (fRTMP_ADAPTER_RESET_IN_PROGRESS | fRTMP_ADAPTER_HALT_IN_PROGRESS |
			       fRTMP_ADAPTER_NIC_NOT_EXIST | fRTMP_ADAPTER_BULKOUT_RESET)))
			    ) {
				/* FIXME: Following code just support single bulk out.
				 * If you wanna support multiple bulk out. Modify it! */
				pHTTXContext = (PHT_TX_CONTEXT) (&pAd->TxContext[idx]);
				if (pHTTXContext->IRPPending) {	/* Check TxContext. */
#ifdef USB_BULK_BUF_ALIGMENT
					pUrb = pHTTXContext->pUrb[pHTTXContext->CurtBulkIdx];
#else
					pUrb = pHTTXContext->pUrb;
#endif /* USB_BULK_BUF_ALIGMENT */
				} else if (idx == MGMTPIPEIDX) {
					PTX_CONTEXT pMLMEContext, pNULLContext, pPsPollContext;

					/*Check MgmtContext. */
					pMLMEContext =
					    (PTX_CONTEXT) (pAd->MgmtRing.
							   Cell[pAd->MgmtRing.TxDmaIdx].AllocVa);
					pPsPollContext = (PTX_CONTEXT) (&pAd->PsPollContext);
					pNULLContext = (PTX_CONTEXT) (&pAd->NullContext[0]);

					if (pMLMEContext->IRPPending) {
						ASSERT(pMLMEContext->IRPPending);
						pUrb = pMLMEContext->pUrb;
					} else if (pNULLContext->IRPPending) {
						ASSERT(pNULLContext->IRPPending);
						pUrb = pNULLContext->pUrb;
					} else if (pPsPollContext->IRPPending) {
						ASSERT(pPsPollContext->IRPPending);
						pUrb = pPsPollContext->pUrb;
					}
				}

				RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[idx], irqFlags);

				DBGPRINT(RT_DEBUG_TRACE,
					 ("Maybe the Tx Bulk-Out hanged! Cancel the pending Tx bulks request of idx(%d)!\n",
					  idx));
				if (pUrb) {
					DBGPRINT(RT_DEBUG_TRACE, ("Unlink the pending URB!\n"));
					/* unlink it now */
					RTUSB_UNLINK_URB(pUrb);
					/* Sleep 200 microseconds to give cancellation time to work */
					RtmpusecDelay(200);
					needDumpSeq = TRUE;
				} else {
					DBGPRINT(RT_DEBUG_ERROR,
						 ("Unkonw bulkOut URB maybe hanged!!!!!!!!!!!!\n"));
				}
			} else {
				RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[idx], irqFlags);
			}
		} else {
			RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[idx], irqFlags);
		}
	}

	/* For Sigma debug, dump the ba_reordering sequence. */
	if ((needDumpSeq == TRUE) /*&& (pAd->CommonCfg.bDisableReordering == 0) */) {
		USHORT Idx;
		PBA_REC_ENTRY pBAEntry = NULL;
		UCHAR count = 0;
		struct reordering_mpdu *mpdu_blk;

		Idx = pAd->MacTab.Content[BSSID_WCID].BARecWcidArray[0];

		pBAEntry = &pAd->BATable.BARecEntry[Idx];
		if ((pBAEntry->list.qlen > 0) && (pBAEntry->list.next != NULL)) {
			DBGPRINT(RT_DEBUG_TRACE,
				 ("NICUpdateRawCounters():The Queueing pkt in reordering buffer:\n"));
			NdisAcquireSpinLock(&pBAEntry->RxReRingLock);
			mpdu_blk = pBAEntry->list.next;
			while (mpdu_blk) {
				DBGPRINT(RT_DEBUG_TRACE,
					 ("\t%d:Seq-%d, bAMSDU-%d!\n", count, mpdu_blk->Sequence,
					  mpdu_blk->bAMSDU));
				mpdu_blk = mpdu_blk->next;
				count++;
			}

			DBGPRINT(RT_DEBUG_TRACE,
				 ("\npBAEntry->LastIndSeq=%d!\n", pBAEntry->LastIndSeq));
			NdisReleaseSpinLock(&pBAEntry->RxReRingLock);
		}
	}
#endif /* RTMP_MAC */
}

#endif /* RTMP_MAC_USB */
