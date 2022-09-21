/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_drv_demux_func.h
* Description:  Define function implement.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20151012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_DRV_DEMUX_FUNC_H__
#define __TEE_DRV_DEMUX_FUNC_H__

#include "tee_drv_demux_define.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_S32  DMX_OsiDescramblerCreate(HI_U32 DmxId, HI_U32 *KeyId, const HI_TEE_DMX_DESCRAMBLER_ATTR_S *DescAttr);
HI_S32  DMX_OsiDescramblerDestroy(HI_U32 DmxId, HI_U32 KeyId);
HI_S32  DMX_OsiDescramblerGetAttr(HI_U32 DmxId, HI_U32 KeyId, HI_TEE_DMX_DESCRAMBLER_ATTR_S *pstDesramblerAttr);
HI_S32  DMX_OsiDescramblerSetAttr(HI_U32 DmxId, HI_U32 KeyId, HI_TEE_DMX_DESCRAMBLER_ATTR_S *pstDesramblerAttr);
HI_S32  DMX_OsiDescramblerSetKey(HI_U32 DmxId, HI_U32 KeyId, HI_U32 KeyType, HI_U8 *Key);
HI_S32  DMX_OsiDescramblerSetIVKey(HI_U32 DmxId, HI_U32 KeyId, HI_U32 KeyType, HI_U8 *Key);
HI_S32  DMX_OsiDescramblerAttach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId);
HI_S32  DMX_OsiDescramblerDetach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId);
HI_S32  DMX_OsiDescramblerGetKeyId(HI_U32 DmxId, HI_U32 ChanId, HI_U32 *KeyId);
HI_S32  DMX_OsiDescramblerNonsecKeyIdAcquire(HI_U32 DmxId, HI_U32 *KeyId);
HI_S32  DMX_OsiDescramblerNonsecKeyIdRelease(HI_U32 DmxId, HI_U32 KeyId);

HI_S32  DMX_OsiScramblerCreate(HI_U32 DmxId, HI_U32 *KeyId, const HI_TEE_DMX_SCRAMBLER_ATTR_S *DescAttr);
HI_S32  DMX_OsiScramblerDestroy(HI_U32 DmxId, HI_U32 KeyId);
HI_S32  DMX_OsiScramblerGetAttr(HI_U32 DmxId, HI_U32 KeyId, HI_TEE_DMX_SCRAMBLER_ATTR_S *pstScramblerAttr);
HI_S32  DMX_OsiScramblerSetAttr(HI_U32 DmxId, HI_U32 KeyId, HI_TEE_DMX_SCRAMBLER_ATTR_S *pstScramblerAttr);

HI_S32  DMX_OsiScramblerSetKey(HI_U32 DmxId, HI_U32 KeyId, DMX_KEY_TYPE_E KeyType, HI_U8 *Key);
HI_S32  DMX_OsiScramblerAttach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId);
HI_S32  DMX_OsiScramblerDetach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId);
HI_S32  DMX_OsiScramblerGetKeyId(HI_U32 DmxId, HI_U32 ChanId, HI_U32 *KeyId);
HI_S32  DMX_OsiDescramblerGetUserUUID(HI_U32 DmxId, HI_U32 KeyId,TEE_UUID *pstUUID);

HI_S32  DMX_OsiGetChannelId(HI_U32 DmxId, HI_U32 Pid, HI_U32 *ChanId);

HI_S32  DMX_Utils_GetCapability(DMX_Capability_S *pstCap);
HI_S32  DMX_Utils_RegisterChannel(HI_U32 DmxId, HI_U32 ChanId);
HI_S32  DMX_Utils_UnregisterChannel(HI_U32 DmxId, HI_U32 ChanId);

HI_S32  DMX_Utils_RegisterOq(HI_U32 DmxId, HI_U32 OqId);
HI_S32  DMX_Utils_UnregisterOq(HI_U32 DmxId, HI_U32 OqId);

HI_S32  DMX_Utils_RegisterRamPort(HI_U32 RamPortId);
HI_S32  DMX_Utils_UnregisterRamPort(HI_U32 RamPortId);

HI_S32  DMX_Utils_LockChannel(HI_U32 DmxId, HI_U32 ChanId);
HI_VOID DMX_Utils_UnlockChannel(HI_U32 DmxId, HI_U32 ChanId);

HI_S32  DMXDescramblerSetIVKey(HI_U32 DmxId, HI_U32 KeyId, DMX_KEY_TYPE_E KeyType, HI_U8 *Key);

#ifdef DMX_SECURE_CHANNEL_SUPPORT
HI_S32  DMX_Utils_RegisterVidSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 SecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32  DMX_Utils_UnregisterVidSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 BufStartAddr);
HI_S32  DMX_Utils_RegisterAudSecBuf(HI_U32 DmxId, HI_U32 ChanId,HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize,  HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32  DMX_Utils_UnregisterAudSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 BufStartAddr);
HI_S32  DMX_Utils_FixupAudSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen);
HI_S32  DMX_Utils_ParserPesHeader(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen, HI_U32 *PesPktLen, HI_U32 *LastPts, HI_U8 *StreamId);
HI_S32  DMX_Utils_ParserPesDispCtrlInfo(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen, Disp_Control_t *pstDispCtrlInfo);
HI_S32  DMX_Utils_GetPesHeaderLen(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen);
HI_S32  DMX_Utils_RegisterRecSecBuf(HI_U32 DmxId, HI_U32 RecId, HI_U32 SecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32  DMX_Utils_UnregisterRecSecBuf(HI_U32 DmxId, HI_U32 RecId, HI_U32 BufStartAddr);
HI_S32  DMX_Utils_FixupHevcIndex(HI_U32 DmxId, HI_U32 RecId, HI_U32 Pid, HI_U32 ParseOffset, FINDEX_SCD_S *pstFindexScd, HI_U32 FindexScdBufSize, TEE_DMX_REC_INDEX_S *pstDmxRecIndex, HI_U32 DmxRecIndexBufSize);
HI_S32  DMX_Utils_RegisterSectionSecBuf(HI_U32 DmxId, HI_U32 ChanId,HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize,  HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32  DMX_Utils_UnregisterSectionSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 BufStartAddr);
HI_S32  DMX_Utils_FixupSectionSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 *Parsed, HI_U32 AcqNum, HI_U32 *Offset, HI_U32 BufPhyAddr, HI_U32 BufLen, HI_U32 PbBufPhyAddr);
HI_S32  DMX_Utils_CheckRecSecBufAddr(HI_U32 DmxId, HI_U32 RecId, HI_U32 BufPhyAddr, HI_U32 BufLen);
#else
static inline HI_S32  DMX_Utils_RegisterVidSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 SecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_UnregisterVidSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 BufStartAddr)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_RegisterAudSecBuf(HI_U32 DmxId, HI_U32 ChanId,HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize,  HI_U32 *pBufStartAddr, HI_U32 *pBufSize)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_UnregisterAudSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 BufStartAddr)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_FixupAudSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_ParserPesHeader(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen, HI_U32 *PesPktLen, HI_U32 *LastPts, HI_U8 *StreamId)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_ParserPesDispCtrlInfo(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen, Disp_Control_t *pstDispCtrlInfo)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_GetPesHeaderLen(HI_U32 DmxId, HI_U32 ChanId, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_RegisterRecSecBuf(HI_U32 DmxId, HI_U32 RecId, HI_U32 SecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_UnregisterRecSecBuf(HI_U32 DmxId, HI_U32 RecId, HI_U32 BufStartAddr)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_FixupHevcIndex(HI_U32 DmxId, HI_U32 RecId, HI_U32 Pid, HI_U32 ParseOffset, FINDEX_SCD_S *pstFindexScd, HI_U32 FindexScdBufSize, TEE_DMX_REC_INDEX_S *pstDmxRecIndex, HI_U32 DmxRecIndexBufSize)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_RegisterSectionSecBuf(HI_U32 DmxId, HI_U32 ChanId,HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize,  HI_U32 *pBufStartAddr, HI_U32 *pBufSize)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_UnregisterSectionSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 BufStartAddr)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_FixupSectionSecBuf(HI_U32 DmxId, HI_U32 ChanId, HI_U32 *Parsed, HI_U32 AcqNum, HI_U32 *Offset, HI_U32 BufPhyAddr, HI_U32 BufLen, HI_U32 PbBufPhyAddr)
{
    return HI_FAILURE;
}

static inline HI_S32 DMX_Utils_CheckRecSecBufAddr(HI_U32 DmxId, HI_U32 RecId, HI_U32 BufPhyAddr, HI_U32 BufLen)
{
    return HI_FAILURE;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DRV_DEMUX_FUNC_H__ */
