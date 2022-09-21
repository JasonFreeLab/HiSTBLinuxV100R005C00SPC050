/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_demux_utils.h
* Description:  tee demux helper functions.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20151012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_DEMUX_UTILS_H__
#define __TEE_DEMUX_UTILS_H__

#define HI_LOG_D_MODULE_ID     HI_MODULE_ID_DEMUX
#define HI_LOG_D_FUNCTRACE     (1)
#define HI_LOG_D_UNFTRACE      (1)

#include "hi_type.h"
#include "hi_tee_debug.h"
#include "hi_tee_log.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define HI_FATAL_DEMUX(fmt...)    HI_LOG_FATAL(fmt)
#define HI_ERR_DEMUX(fmt...)      HI_LOG_ERROR(fmt)
#define HI_WARN_DEMUX(fmt...)     HI_LOG_WARN(fmt)
#define HI_INFO_DEMUX(fmt...)     HI_LOG_INFO(fmt)
#define HI_DBG_DEMUX(fmt...)      HI_LOG_DEBUG(fmt)

#define TEE_DMX_ENTER()                         HI_LOG_FuncEnter()
#define TEE_DMX_EXIT()                          HI_LOG_FuncExit()

#define TEE_DMX_PrintFuncWar(Func, ErrCode)     HI_LOG_PrintFuncWar(Func, ErrCode)
#define TEE_DMX_PrintFuncErr(Func, ErrCode)     HI_LOG_PrintFuncErr(Func, ErrCode)
#define TEE_DMX_PrintErrCode(ErrCode)           HI_LOG_PrintErrCode(ErrCode)

#define TEE_DMX_LOG_PrintS32(val)               HI_LOG_PrintS32(val)
#define TEE_DMX_LOG_PrintU32(val)               HI_LOG_PrintU32(val)
#define TEE_DMX_LOG_PrintS64(val)               HI_LOG_PrintS64(val)
#define TEE_DMX_LOG_PrintU64(val)               HI_LOG_PrintU64(val)
#define TEE_DMX_LOG_PrintH32(val)               HI_LOG_PrintH32(val)
#define TEE_DMX_LOG_PrintH64(val)               HI_LOG_PrintH64(val)
#define TEE_DMX_LOG_PrintStr(val)               HI_LOG_PrintStr(val)
#define TEE_DMX_LOG_PrintVoid(val)              HI_LOG_PrintVoid(val)
#define TEE_DMX_LOG_PrintFloat(val)             HI_LOG_PrintFloat(val)
#define TEE_DMX_LOG_PrintInfo(val)              HI_LOG_PrintInfo(val)

#define TEE_DMX_DBG_PrintS32(val)               HI_DBG_PrintS32(val)
#define TEE_DMX_DBG_PrintU32(val)               HI_DBG_PrintU32(val)
#define TEE_DMX_DBG_PrintS64(val)               HI_DBG_PrintS64(val)
#define TEE_DMX_DBG_PrintU64(val)               HI_DBG_PrintU64(val)
#define TEE_DMX_DBG_PrintH32(val)               HI_DBG_PrintH32(val)
#define TEE_DMX_DBG_PrintH64(val)               HI_DBG_PrintH64(val)
#define TEE_DMX_DBG_PrintStr(val)               HI_DBG_PrintStr(val)
#define TEE_DMX_DBG_PrintVoid(val)              HI_DBG_PrintVoid(val)
#define TEE_DMX_DBG_PrintFloat(val)             HI_DBG_PrintFloat(val)
#define TEE_DMX_DBG_PrintInfo(val)              HI_DBG_PrintInfo(val)

/*
 * keep synchronization with sdk/source/common/include/hi_module.h
 */
#define HI_ID_DEMUX                   (0x0A)
#define HI_MAX_PID                    (0x1FFF)
#define DMX_KEY_MIN_LEN                 8
#define DMX_KEY_MAX_LEN                 16



/*
 * the next definition keep similar with sdk/source/msp/api/include/hi_mpi_demux.h.
 */
#define DMX_DMXID(ChanHandle)  ( ((ChanHandle) & 0x0000ff00) >> 8)

/* just for app level, we can use DMX_CNT in driver level */
#define DMX_CHECKDMXID(DmxId) \
    do {  \
        DMX_Capability_S stCap = {0};\
        if (HI_SUCCESS != TEE_DMX_GetCapability(&stCap))\
        {\
            TEE_DMX_LOG_PrintInfo("DMX_GETCAP Failed.\n"); \
            return HI_FAILURE; \
        } \
        if (DmxId < 0 || DmxId >= stCap.u32DmxNum)\
        {\
            TEE_DMX_DBG_PrintInfo("DmxId invalid.\n");\
            TEE_DMX_DBG_PrintU32(DmxId);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA; \
        } \
    } while (0)

#define DMX_CHECKPID(PID) \
    do {  \
        if (PID < 0 || PID > HI_MAX_PID)\
        {\
            TEE_DMX_DBG_PrintInfo("PID invalid.\n");\
            TEE_DMX_DBG_PrintU32(PID);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA; \
        } \
    } while (0)

#define DMX_CHANHANDLE_MAGIC      (0x1)
#define DMX_CHANID(ChanHandle)      ((ChanHandle) & 0x000000ff)
#define DMX_CHANHANDLE(DmxId, ChanId)    ((HI_ID_DEMUX << 28) | (DMX_CHANHANDLE_MAGIC << 24) | \
                    ((0 << 16) & 0xff0000) | ((DmxId << 8) & 0x0000ff00) | (ChanId & 0x000000ff))

#define DMX_CHECK_CHANHANDLE(ChanHandle)                                \
    do                                                                  \
    {                                                                   \
        if (((ChanHandle >> 28) & 0x0000000f) != HI_ID_DEMUX || ((ChanHandle >> 24) & 0x0000000f) != DMX_CHANHANDLE_MAGIC) \
        {\
            TEE_DMX_DBG_PrintInfo("Invalid Channel handle \n");\
            TEE_DMX_DBG_PrintU32(ChanHandle);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA;\
        }\
    } while (0)

#define DMX_RECHANDLE_MAGIC      (0x3)
#define DMX_RECID(RecHandle)    ((RecHandle) & 0x000000ff)
#define DMX_RECHANDLE(DmxId, RecId)    ((HI_ID_DEMUX << 24) | (DMX_RECHANDLE_MAGIC << 16) | ((DmxId << 8) & 0x0000ff00) | (RecId & 0x000000ff))
#define DMX_CHECK_RECHANDLE(RecHandle)                                  \
    do                                                                  \
    {                                                                   \
        if (((RecHandle >> 24) & 0x000000ff) != HI_ID_DEMUX || ((RecHandle >> 16) & 0x000000ff) != DMX_RECHANDLE_MAGIC) \
        {                                                               \
            TEE_DMX_DBG_PrintInfo("Invalid Rec handle \n");\
            TEE_DMX_DBG_PrintU32(RecHandle);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA;                             \
        }                                                               \
    } while (0)

/*
 * the next definition keep similar with sdk/source/msp/api/include/hi_mpi_descrambler.h.
 */
#define DMX_KEYHANDLE_MAGIC      (0x5)
#define DMX_KEYID(KeyHandle)    ((KeyHandle) & 0x000000ff)
#define DMX_KEYHANDLE(DmxId, KeyId)    ((HI_ID_DEMUX << 24) | (DMX_KEYHANDLE_MAGIC << 16) | ((DmxId << 8) & 0x0000ff00) | (KeyId & 0x000000ff))
#define DMX_CHECK_KEYHANDLE(KeyHandle)                                  \
    do                                                                  \
    {                                                                   \
        if (((KeyHandle >> 24) & 0x000000ff) != HI_ID_DEMUX || ((KeyHandle >> 16) & 0x000000ff) != DMX_KEYHANDLE_MAGIC) \
        {                                                               \
            TEE_DMX_DBG_PrintInfo("Invalid Key handle \n");\
            TEE_DMX_DBG_PrintU32(KeyHandle);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA;                             \
        }                                                               \
    } while (0)

#define DMX_KEYHANDLE2_MAGIC      (0x7)
#define DMX_KEYHANDLE2(DmxId, KeyId)    ((HI_ID_DEMUX << 24) | (DMX_KEYHANDLE2_MAGIC << 16) | ((DmxId << 8) & 0x0000ff00) | (KeyId & 0x000000ff))
#define DMX_CHECK_KEYHANDLE2(KeyHandle)                                  \
    do                                                                  \
    {                                                                   \
        if (((KeyHandle >> 24) & 0x000000ff) != HI_ID_DEMUX || ((KeyHandle >> 16) & 0x000000ff) != DMX_KEYHANDLE2_MAGIC) \
        {                                                               \
            TEE_DMX_DBG_PrintInfo("Invalid Encrypt Key handle \n");\
            TEE_DMX_DBG_PrintU32(KeyHandle);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA;                             \
        }                                                               \
    } while (0)

#define DMX_CHECKPOINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            TEE_DMX_LOG_PrintInfo("pointer parameter is NULL.\n"); \
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_TEE_ERR_INVALID_PARAM; \
        } \
    } while (0)

/*
 * sync with source/msp/drv/demux/demux_v2/drv_demux_define.h
 */

/**Defines the capability of the DEMUX module*/
/**CNcomment:定义DEMUX模块业务功能结构体*/
typedef struct hiDMX_CAPABILITY_S
{
    HI_U32 u32DmxNum;           /**<Number of DEMUX devices*/ /**< CNcomment:设备数量     */
    HI_U32 u32RamPortNum;       /**<Number of Ram ports. */ /**< CNcomment: Ram端口数量     */
    HI_U32 u32ChannelNum;       /**<Number of channels, containing the audio and video channels */ /**< CNcomment:通道数量，含音视频通道的数量 */
    HI_U32 u32KeyNum;           /**<Number of keys*/ /**< CNcomment:密钥区数量   */
    HI_U32 u32RecChnNum;        /**<Number of record channels */ /**< CNcomment:录制通道的数量 */
} DMX_Capability_S;

typedef struct hi_Disp_Control_t
{
    HI_U32          u32DispTime;
    HI_U32          u32DispEnableFlag;
    HI_U32          u32DispFrameDistance;
    HI_U32          u32DistanceBeforeFirstFrame;
    HI_U32          u32GopNum;
} Disp_Control_t;

typedef struct hiDMX_UserMsg_S
{
    HI_U32                  u32BufStartAddr;
    HI_U32                  u32MsgLen;
    HI_U32                  reserved;
} DMX_UserMsg_S;

/*  refer to hi_unf_video.h */
/**Defines the type of the video frame.*/
/**CNcomment: 定义视频帧的类型枚举*/
typedef enum hiUNF_VIDEO_FRAME_TYPE_E
{
    TEE_FRAME_TYPE_UNKNOWN,   /**<Unknown*/ /**<CNcomment: 未知的帧类型*/
    TEE_FRAME_TYPE_I,         /**<I frame*/ /**<CNcomment: I帧*/
    TEE_FRAME_TYPE_P,         /**<P frame*/ /**<CNcomment: P帧*/
    TEE_FRAME_TYPE_B,         /**<B frame*/ /**<CNcomment: B帧*/
    TEE_FRAME_TYPE_IDR,       /**<IDR frame*/ /**<CNcomment: IDR帧*/
    TEE_FRAME_TYPE_BUTT
}TEE_VIDEO_FRAME_TYPE_E;

/*  refer to hi_mpi_demux.h */
typedef struct hiMPI_DMX_REC_INDEX_S
{
    TEE_VIDEO_FRAME_TYPE_E      enFrameType;
    HI_U32                      u32PtsMs;
    HI_U64                      u64GlobalOffset;
    HI_U32                      u32FrameSize;
    HI_U32                      u32DataTimeMs;

    /* hevc private */
    HI_S16                      s16CurPoc;
    HI_U16                      u16RefPocCnt;
    HI_S16                      as16RefPoc[16]; /* according to hevc protocol , max reference poc is 16. */
} TEE_DMX_REC_INDEX_S;
/* refer end */

/*  refer to drv_demux_index.h */
/* pvr index's SCD descriptor*/
typedef struct hiFINDEX_SCD_S
{
    HI_U8   u8IndexType;             /* type of index(pts,sc,pause,ts) */
    HI_U8   u8StartCode;             /* type of start code, 1Byte after 000001 */
    HI_U16  u16Reservd;
    HI_U32  u32PtsMs;

    HI_S64  s64GlobalOffset;        /* start code offset in global buffer */
    HI_U8   au8DataAfterSC[8];      /* 1~8 Byte next to SC */
    HI_U32  u32ExtraSCDataSize;     /* extra data size */
    HI_U32  u32ExtraSCRealDataSize; /* real extra data size */
    HI_U8   *pu8ExtraSCData;        /* save extra more data */
    HI_U32  u32ExtraSCDataPhyAddr;  /* extra data phy addr */
} FINDEX_SCD_S;
/* refer end */

HI_S32 TEE_DMX_GetCapability(DMX_Capability_S *pstCap);
HI_S32 TEE_DMX_RegisterChannel(HI_U32 DmxId, HI_U32 ChanId);
HI_S32 TEE_DMX_UnregisterChannel(HI_U32 DmxId, HI_U32 ChanId);

HI_S32 TEE_DMX_LockChannel(HI_U32 DmxId, HI_U32 ChanId);
HI_VOID TEE_DMX_UnlockChannel(HI_U32 DmxId, HI_U32 ChanId);

HI_S32 TEE_DMX_RegisterOq(HI_U32 DmxId, HI_U32 OqId);
HI_S32 TEE_DMX_UnregisterOq(HI_U32 DmxId, HI_U32 OqId);

HI_S32 TEE_DMX_RegisterVidSecBuf(HI_HANDLE Handle, HI_U32 SecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DMX_UnregisterVidSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DMX_RegisterAudSecBuf(HI_HANDLE Handle, HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DMX_UnregisterAudSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DMX_FixupAudSecBuf(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen);

HI_S32 TEE_DMX_ParserPesHeader(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen, HI_U32 *PesPktLen, HI_U32 *LastPts, HI_U8 *pstreamId);
HI_S32 TEE_DMX_ParserPesDispCtrlInfo(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen, Disp_Control_t *pstDispCtrlInfo);
HI_S32 TEE_DMX_GetPesHeaderLen(HI_HANDLE Handle, HI_U32 ParserAddr, HI_U32 ParserLen, HI_U32 *PesHeaderLen);

HI_S32 TEE_DMX_RegisterRecSecBuf(HI_HANDLE Handle, HI_U32 SecBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DMX_UnregisterRecSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DMX_FixupHevcIndex(HI_HANDLE Handle, HI_U32 Pid, HI_U32 ParseOffset, FINDEX_SCD_S *pstFindexScd, HI_U32 FindexScdBufSize, TEE_DMX_REC_INDEX_S *pstDmxRecIndex, HI_U32 DmxRecIndexBufSize);
HI_S32 TEE_DMX_CheckRecSecBufAddr(HI_HANDLE RecChnHandle, HI_U32 BufPhyAddr, HI_U32 BufLen);

HI_S32 TEE_DMX_RegisterRamPort(HI_U32 RamPortId);
HI_S32 TEE_DMX_UnregisterRamPort(HI_U32 RamPortId);

HI_S32 TEE_DMX_RegisterSectionSecBuf(HI_HANDLE Handle, HI_U32 ShadowBufStartAddr, HI_U32 ShadowBufSize, HI_U32 *pBufStartAddr, HI_U32 *pBufSize);
HI_S32 TEE_DMX_UnregisterSectionSecBuf(HI_HANDLE Handle, HI_U32 BufStartAddr);
HI_S32 TEE_DMX_FixupSectionSecBuf(HI_HANDLE Handle, HI_U32 *Parsed, HI_U32 AcqNum, HI_U32 *Offset, HI_U32 BufPhyAddr, HI_U32 BufLen, HI_U32 PbBufPhyAddr);

HI_S32 TEE_DMX_DescramblerNonsecKeyAcquire(HI_U32 DmxId, HI_U32 *KeyId);
HI_S32 TEE_DMX_DescramblerNonsecKeyRelease(HI_U32 DmxId, HI_U32 KeyId);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DEMUX_UTILS_H__ */
