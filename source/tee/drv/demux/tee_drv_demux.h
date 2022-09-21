/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_drv_descrambler.h
* Description:  Define interfaces of demux interface.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20151012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_DRV_DEMUX_H__
#define __TEE_DRV_DEMUX_H__

#include "hi_tee_descrambler.h"
#include "hi_tee_scrambler.h"
#include "tee_demux_utils.h"
#include "tee_drv_common.h"
#include "tee_internal_api.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum
{
    DMX_KEY_TYPE_EVEN   = 0,
    DMX_KEY_TYPE_ODD    = 1
} DMX_KEY_TYPE_E;

typedef enum
{
    DMX_KEY_CW = 0,
    DMX_KEY_IV = 1
} DMX_CW_TYPE;

#define DMX_MEM_ACCESS_CHECK(addr, size) \
        if (!tee_hal_access_check((void *)addr, size)) { \
            TEE_DMX_LOG_PrintInfo("access check failed");\
            TEE_DMX_LOG_PrintH32(addr);\
            TEE_DMX_LOG_PrintH32(size);\
            break; \
        } \
        if (!tee_hal_write_right_check((void *)addr, size)) { \
            TEE_DMX_LOG_PrintInfo("write access check failed");\
            TEE_DMX_LOG_PrintH32(addr);\
            TEE_DMX_LOG_PrintH32(size);\
            break; \
        }

HI_S32 TEE_DRV_DMX_CreateDescrambler(HI_U32 DmxId, HI_TEE_DMX_DESCRAMBLER_ATTR_S *DesrAttr, HI_HANDLE *KeyHandle, HI_U32 file);
HI_S32 TEE_DRV_DMX_DestroyDescrambler(HI_HANDLE KeyHandle);
HI_S32 TEE_DRV_DMX_GetDescramblerAttr(HI_HANDLE KeyHandle, HI_TEE_DMX_DESCRAMBLER_ATTR_S *pstDescramblerAttr);
HI_S32 TEE_DRV_DMX_SetDescramblerAttr(HI_HANDLE KeyHandle, HI_TEE_DMX_DESCRAMBLER_ATTR_S *pstDescramblerAttr);
HI_S32 TEE_DRV_DMX_SetDescramblerEvenKey(HI_HANDLE KeyHandle, HI_U8 *Key);
HI_S32 TEE_DRV_DMX_SetDescramblerOddKey(HI_HANDLE KeyHandle, HI_U8 *Key);
HI_S32 TEE_DRV_DMX_SetDescramblerEvenIVKey(HI_HANDLE KeyHandle, HI_U8 *Key);
HI_S32 TEE_DRV_DMX_SetDescramblerOddIVKey(HI_HANDLE KeyHandle, HI_U8 *Key);
HI_S32 TEE_DRV_DMX_AttachDescrambler(HI_HANDLE KeyHandle, HI_HANDLE ChanHandle);
HI_S32 TEE_DRV_DMX_DetachDescrambler(HI_HANDLE KeyHandle, HI_HANDLE ChanHandle);
HI_S32 TEE_DRV_DMX_GetDescramblerKeyHandle(HI_HANDLE ChanHandle, HI_HANDLE *KeyHandle);

/*
 * secure scrambler function interface.
 */
HI_S32 TEE_DRV_DMX_CreateScrambler(HI_U32 DmxId, HI_TEE_DMX_SCRAMBLER_ATTR_S *ScramAttr, HI_HANDLE *KeyHandle);
HI_S32 TEE_DRV_DMX_DestroyScrambler(HI_HANDLE KeyHandle);
HI_S32 TEE_DRV_DMX_GetScramblerAttr(HI_HANDLE KeyHandle, HI_TEE_DMX_SCRAMBLER_ATTR_S *pstScramblerAttr);
HI_S32 TEE_DRV_DMX_SetScramblerAttr(HI_HANDLE KeyHandle, HI_TEE_DMX_SCRAMBLER_ATTR_S *pstScramblerAttr);
HI_S32 TEE_DRV_DMX_SetScramblerEvenKey(HI_HANDLE KeyHandle, HI_U8 *Key);
HI_S32 TEE_DRV_DMX_SetScramblerOddKey(HI_HANDLE KeyHandle, HI_U8 *Key);
HI_S32 TEE_DRV_DMX_AttachScrambler(HI_HANDLE KeyHandle, HI_HANDLE ChanHandle);
HI_S32 TEE_DRV_DMX_DetachScrambler(HI_HANDLE KeyHandle, HI_HANDLE ChanHandle);
HI_S32 TEE_DRV_DMX_GetScramblerKeyHandle(HI_HANDLE ChanHandle, HI_HANDLE *KeyHandle);

HI_S32 TEE_DRV_DMX_GetChannelHandle(HI_U32 DmxId, HI_U32 Pid, HI_HANDLE *ChanHandle);

/*
 * utils function set
 */
HI_S32 TEE_DRV_DMX_GetCapability(DMX_Capability_S *pstCap);
HI_S32 TEE_DRV_DMX_RegisterChannel(HI_U32  DmxId, HI_U32 ChanId);
HI_S32 TEE_DRV_DMX_UnregisterChannel(HI_U32  DmxId, HI_U32 ChanId);

HI_S32 TEE_DRV_DMX_RegisterOq(HI_U32  DmxId, HI_U32 OqId);
HI_S32 TEE_DRV_DMX_UnregisterOq(HI_U32  DmxId, HI_U32 OqId);

HI_S32 TEE_DRV_DMX_LockChannel(HI_U32  DmxId, HI_U32 ChanId);
HI_S32 TEE_DRV_DMX_UnlockChannel(HI_U32  DmxId, HI_U32 ChanId);

HI_S32 TEE_DRV_DMX_RegisterVidSecBuf(HI_HANDLE Handle, HI_U32 SecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DRV_DMX_UnregisterVidSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DRV_DMX_RegisterAudSecBuf(HI_HANDLE Handle, HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DRV_DMX_UnregisterAudSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DRV_DMX_FixupAudSecBuf(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen);
HI_S32 TEE_DRV_DMX_RegisterSectionSecBuf(HI_HANDLE Handle, HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DRV_DMX_UnregisterSectionSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DRV_DMX_FixupSectionSecBuf(HI_HANDLE Handle, HI_U32 *pParsed, HI_U32 AcqNum, HI_U32 *pOffset, HI_U32 BufPhyAddr, HI_U32 BufLen, HI_U32 PbBufPhyAddr);
HI_S32 TEE_DRV_DMX_GetUserUUID(HI_HANDLE KeyHandle,TEE_UUID *pstUUID);

HI_S32 TEE_DRV_DMX_ParserPesHeader(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen, HI_U32 *PesPktLen, HI_U32 *LastPts, HI_U8 *StreamId);
HI_S32 TEE_DRV_DMX_ParserPesDispCtrlInfo(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen, Disp_Control_t *pstDispCtrlInfo);
HI_S32 TEE_DRV_DMX_GetPesHeaderLen(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen);

HI_S32 TEE_DRV_DMX_RegisterRecSecBuf(HI_HANDLE Handle, HI_U32 RecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DRV_DMX_UnregisterRecSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DRV_DMX_FixupHevcIndex(HI_HANDLE Handle, HI_U32 Pid, HI_U32 ParseOffset, FINDEX_SCD_S *pstFindexScd, HI_U32 FindexScdBufSize, TEE_DMX_REC_INDEX_S *pstDmxRecIndex, HI_U32 DmxRecIndexBufSize);
HI_S32 TEE_DRV_DMX_CheckRecSecBufAddr(HI_HANDLE RecChnHandle, HI_U32 BufPhyAddr, HI_U32 BufLen);

HI_S32 TEE_DRV_DMX_RegisterRamPort(HI_U32 RamPortId);
HI_S32 TEE_DRV_DMX_UnregisterRamPort(HI_U32 RamPortId);

/*******export IV interface for keyladder *******/
HI_S32 TEE_DRV_DMX_SetDescramblerIV(HI_HANDLE KeyHandle, DMX_KEY_TYPE_E enKeyType, HI_U8 *pu8IV, HI_U32 u32IVLen);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DRV_DEMUX_H__ */
