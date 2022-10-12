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

extern UCHAR CISCO_OUI[];

extern UCHAR WPA_OUI[];
extern UCHAR RSN_OUI[];
extern UCHAR WME_INFO_ELEM[];
extern UCHAR WME_PARM_ELEM[];
extern UCHAR RALINK_OUI[];
extern UCHAR BROADCOM_OUI[];

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
 */
BOOLEAN MlmeStartReqSanity(IN PRTMP_ADAPTER pAd,
			   IN VOID * Msg, IN ULONG MsgLen, OUT CHAR Ssid[], OUT UCHAR *pSsidLen)
{
	MLME_START_REQ_STRUCT *Info;

	Info = (MLME_START_REQ_STRUCT *) (Msg);

	if (Info->SsidLen > MAX_LEN_OF_SSID) {
		DBGPRINT(RT_DEBUG_TRACE, ("%s(): fail - wrong SSID length\n", __func__));
		return FALSE;
	}

	*pSsidLen = Info->SsidLen;
	NdisMoveMemory(Ssid, Info->Ssid, *pSsidLen);

	return TRUE;
}

/*
    ==========================================================================
    Description:
	MLME message sanity check
    Return:
	TRUE if all parameters are OK, FALSE otherwise

    IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN PeerAssocRspSanity(IN PRTMP_ADAPTER pAd,
			IN VOID * pMsg, IN ULONG MsgLen, OUT PUCHAR pAddr2,
			OUT USHORT * pCapabilityInfo, OUT USHORT * pStatus,
			OUT USHORT * pAid, OUT UCHAR SupRate[],
			OUT UCHAR *pSupRateLen, OUT UCHAR ExtRate[],
			OUT UCHAR *pExtRateLen, OUT HT_CAPABILITY_IE * pHtCapability,
			/* AP might use this additional ht info IE */
			OUT ADD_HT_INFO_IE * pAddHtInfo,
			OUT UCHAR *pHtCapabilityLen,
			OUT UCHAR *pAddHtInfoLen,
			OUT UCHAR *pNewExtChannelOffset,
			OUT PEDCA_PARM pEdcaParm,
			OUT EXT_CAP_INFO_ELEMENT * pExtCapInfo,
			OUT UCHAR *pCkipFlag, OUT IE_LISTS * ie_list)
{
	CHAR IeType, *Ptr;
	PFRAME_802_11 pFrame = (PFRAME_802_11) pMsg;
	PEID_STRUCT pEid;
	ULONG Length = 0;

	*pNewExtChannelOffset = 0xff;
	*pHtCapabilityLen = 0;
	*pAddHtInfoLen = 0;
	COPY_MAC_ADDR(pAddr2, pFrame->Hdr.Addr2);
	Ptr = (CHAR *) pFrame->Octet;
	Length += LENGTH_802_11;

	NdisMoveMemory(pCapabilityInfo, &pFrame->Octet[0], 2);
	Length += 2;
	NdisMoveMemory(pStatus, &pFrame->Octet[2], 2);
	Length += 2;
	*pCkipFlag = 0;
	*pExtRateLen = 0;
	pEdcaParm->bValid = FALSE;

	if (*pStatus != MLME_SUCCESS)
		return TRUE;

	NdisMoveMemory(pAid, &pFrame->Octet[4], 2);
	Length += 2;

	/* Aid already swaped byte order in RTMPFrameEndianChange() for big endian platform */
	*pAid = (*pAid) & 0x3fff;	/* AID is low 14-bit */

	/* -- get supported rates from payload and advance the pointer */
	IeType = pFrame->Octet[6];
	*pSupRateLen = pFrame->Octet[7];
	if ((IeType != IE_SUPP_RATES) || (*pSupRateLen > MAX_LEN_OF_SUPPORTED_RATES)) {
		DBGPRINT(RT_DEBUG_TRACE, ("%s(): fail - wrong SupportedRates IE\n", __func__));
		return FALSE;
	}

	NdisMoveMemory(SupRate, &pFrame->Octet[8], *pSupRateLen);


	Length = Length + 2 + *pSupRateLen;

	/*
	   many AP implement proprietary IEs in non-standard order, we'd better
	   tolerate mis-ordered IEs to get best compatibility
	 */
	pEid = (PEID_STRUCT) &pFrame->Octet[8 + (*pSupRateLen)];

	/* get variable fields from payload and advance the pointer */
	while ((Length + 2 + pEid->Len) <= MsgLen) {
		switch (pEid->Eid) {
		case IE_EXT_SUPP_RATES:
			if (pEid->Len <= MAX_LEN_OF_SUPPORTED_RATES) {
				NdisMoveMemory(ExtRate, pEid->Octet, pEid->Len);
				*pExtRateLen = pEid->Len;
			}
			break;

		case IE_HT_CAP:
		case IE_HT_CAP2:
			if (pEid->Len >= SIZE_HT_CAP_IE) {	/* Note: allow extension.!! */
				NdisMoveMemory(pHtCapability, pEid->Octet, SIZE_HT_CAP_IE);

				*(USHORT *) (&pHtCapability->HtCapInfo) =
				    cpu2le16(*(USHORT *) (&pHtCapability->HtCapInfo));
				*(USHORT *) (&pHtCapability->ExtHtCapInfo) =
				    cpu2le16(*(USHORT *) (&pHtCapability->ExtHtCapInfo));

				*pHtCapabilityLen = SIZE_HT_CAP_IE;
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_HT_CAP\n", __func__));
			}

			break;

		case IE_ADD_HT:
		case IE_ADD_HT2:
			if (pEid->Len >= sizeof(ADD_HT_INFO_IE)) {
				/*
				   This IE allows extension, but we can ignore extra bytes beyond
				   our knowledge, so only copy first sizeof(ADD_HT_INFO_IE)
				 */
				NdisMoveMemory(pAddHtInfo, pEid->Octet, sizeof(ADD_HT_INFO_IE));

				*(USHORT *) (&pAddHtInfo->AddHtInfo2) =
				    cpu2le16(*(USHORT *) (&pAddHtInfo->AddHtInfo2));
				*(USHORT *) (&pAddHtInfo->AddHtInfo3) =
				    cpu2le16(*(USHORT *) (&pAddHtInfo->AddHtInfo3));

				*pAddHtInfoLen = SIZE_ADD_HT_INFO_IE;
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_ADD_HT\n", __func__));
			}

			break;
		case IE_SECONDARY_CH_OFFSET:
			if (pEid->Len == 1) {
				*pNewExtChannelOffset = pEid->Octet[0];
			} else {
				DBGPRINT(RT_DEBUG_WARN,
					 ("%s():wrong IE_SECONDARY_CH_OFFSET\n", __func__));
			}
			break;

#ifdef DOT11_VHT_AC
		case IE_VHT_CAP:
			if (pEid->Len == sizeof(VHT_CAP_IE)) {
				NdisMoveMemory(&ie_list->vht_cap, pEid->Octet, sizeof(VHT_CAP_IE));
				ie_list->vht_cap_len = sizeof(VHT_CAP_IE);
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_VHT_CAP\n", __func__));
			}
			break;

		case IE_VHT_OP:
			if (pEid->Len == sizeof(VHT_OP_IE)) {
				NdisMoveMemory(&ie_list->vht_op, pEid->Octet, sizeof(VHT_OP_IE));
				ie_list->vht_op_len = sizeof(VHT_OP_IE);
			} else {
				DBGPRINT(RT_DEBUG_WARN, ("%s():wrong IE_VHT_OP\n", __func__));
			}
			break;
#endif /* DOT11_VHT_AC */

		case IE_VENDOR_SPECIFIC:
			/* handle WME PARAMTER ELEMENT */
			if (NdisEqualMemory(pEid->Octet, WME_PARM_ELEM, 6) && (pEid->Len == 24)) {
				PUCHAR ptr;
				int i;

				/* parsing EDCA parameters */
				pEdcaParm->bValid = TRUE;
				pEdcaParm->bQAck = FALSE;	/* pEid->Octet[0] & 0x10; */
				pEdcaParm->bQueueRequest = FALSE;	/* pEid->Octet[0] & 0x20; */
				pEdcaParm->bTxopRequest = FALSE;	/* pEid->Octet[0] & 0x40; */
				pEdcaParm->EdcaUpdateCount = pEid->Octet[6] & 0x0f;
				pEdcaParm->bAPSDCapable = (pEid->Octet[6] & 0x80) ? 1 : 0;
				ptr = (PUCHAR) &pEid->Octet[8];
				for (i = 0; i < 4; i++) {
					UCHAR aci = (*ptr & 0x60) >> 5;	/* b5~6 is AC INDEX */

					pEdcaParm->bACM[aci] = (((*ptr) & 0x10) == 0x10);	/* b5 is ACM */
					pEdcaParm->Aifsn[aci] = (*ptr) & 0x0f;	/* b0~3 is AIFSN */
					pEdcaParm->Cwmin[aci] = *(ptr + 1) & 0x0f;	/* b0~4 is Cwmin */
					pEdcaParm->Cwmax[aci] = *(ptr + 1) >> 4;	/* b5~8 is Cwmax */
					pEdcaParm->Txop[aci] = *(ptr + 2) + 256 * (*(ptr + 3));	/* in unit of 32-us */
					ptr += 4;	/* point to next AC */
				}
			}
			break;
		case IE_EXT_CAPABILITY:
			if (pEid->Len >= 1) {
				UCHAR MaxSize;
				UCHAR MySize = sizeof(EXT_CAP_INFO_ELEMENT);

				MaxSize = min(pEid->Len, MySize);
				NdisMoveMemory(pExtCapInfo, &pEid->Octet[0], MaxSize);
				DBGPRINT(RT_DEBUG_WARN,
					 ("PeerAssocReqSanity - IE_EXT_CAPABILITY!\n"));
			}
			break;
		default:
			DBGPRINT(RT_DEBUG_TRACE,
				 ("%s():ignore unrecognized EID = %d\n", __func__, pEid->Eid));
			break;
		}

		Length = Length + 2 + pEid->Len;
		pEid = (PEID_STRUCT) ((UCHAR *) pEid + 2 + pEid->Len);
	}


	return TRUE;
}

/*
    ==========================================================================
    Description:

	IRQL = DISPATCH_LEVEL

    ==========================================================================
 */
BOOLEAN GetTimBit(IN CHAR *Ptr,
		  IN USHORT Aid,
		  OUT UCHAR *TimLen,
		  OUT UCHAR *BcastFlag,
		  OUT UCHAR *DtimCount, OUT UCHAR *DtimPeriod, OUT UCHAR *MessageToMe)
{
	UCHAR BitCntl, N1, N2, MyByte, MyBit;
	CHAR *IdxPtr;

	IdxPtr = Ptr;

	IdxPtr++;
	*TimLen = *IdxPtr;

	/* get DTIM Count from TIM element */
	IdxPtr++;
	*DtimCount = *IdxPtr;

	/* get DTIM Period from TIM element */
	IdxPtr++;
	*DtimPeriod = *IdxPtr;

	/* get Bitmap Control from TIM element */
	IdxPtr++;
	BitCntl = *IdxPtr;

	if ((*DtimCount == 0) && (BitCntl & 0x01))
		*BcastFlag = TRUE;
	else
		*BcastFlag = FALSE;

	/* Parse Partial Virtual Bitmap from TIM element */
	N1 = BitCntl & 0xfe;	/* N1 is the first bitmap byte# */
	N2 = *TimLen - 4 + N1;	/* N2 is the last bitmap byte# */

	if ((Aid < (N1 << 3)) || (Aid >= ((N2 + 1) << 3)))
		*MessageToMe = FALSE;
	else {
		MyByte = (Aid >> 3) - N1;	/* my byte position in the bitmap byte-stream */
		MyBit = Aid % 16 - ((MyByte & 0x01) ? 8 : 0);

		IdxPtr += (MyByte + 1);

		if (*IdxPtr & (0x01 << MyBit))
			*MessageToMe = TRUE;
		else
			*MessageToMe = FALSE;
	}

	return TRUE;
}
