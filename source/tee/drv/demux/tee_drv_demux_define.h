/***********************************************************************************
*              Copyright 2004 - 2015, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_drv_demux_define.h
* Description:  Define basic definition.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20151012    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_DRV_DEMUX_DEFINE_H__
#define __TEE_DRV_DEMUX_DEFINE_H__

#include <tee_os_hal.h>
#include "hi_type.h"
#include "tee_demux_utils.h"

#include "drv_tee_mem.h"

#include "tee_demux_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*
 * linux helpers utils.
 */
#define BITS_PER_BYTE       8
#define BITS_PER_LONG       32
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1) / (d))
#define BITS_TO_LONGS(nr)   DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define DECLARE_BITMAP(name,bits) \
                        unsigned long name[BITS_TO_LONGS(bits)]

#define unlikely(condition) (condition)

#define BUG_ON(condition) if(condition) {HI_FATAL_DEMUX("BUG ...\n");while(1);}

#define DMX_INVALID_DEMUX_ID            0xffffffff
#define DMX_INVALID_REC_ID              0xffffffff
#define DMX_INVALID_CHAN_ID             0xffff
#define DMX_INVALID_KEY_ID              0xffff

#define DMX_INVALID_PID                 0x1fff

#define DMX_KEY_HARDONLY_FLAG           0xffffffff

#define DMX_PES_HEADER_LENGTH           9
#define INVALID_PTS                     0xFFFFFFFFL

#define DMX_DRV_MEMCPY asm_memmove

#define DMX_DRV_CHECK_DMXID(DMXID) \
    do {  \
            if (DMXID < 0 || DMXID >= DMX_CNT)\
            {\
                TEE_DMX_LOG_PrintInfo("DMXID invalid");\
                TEE_DMX_LOG_PrintInfo(DMXID);\
                TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
                return HI_ERR_DMX_INVALID_PARA; \
            } \
    } while (0)

#define DMX_DRV_CHECK_CHANID(CHANID) \
    do {  \
        if (CHANID < 0 || CHANID >= DMX_CHANNEL_CNT)\
        {\
            TEE_DMX_LOG_PrintInfo("CHANID invalid");\
            TEE_DMX_LOG_PrintInfo(CHANID);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA; \
        } \
    } while (0)

#define DMX_DRV_CHECK_KEYID(KEYID) \
    do {  \
        if (KEYID < DMX_SEC_KEY_OFFSET || KEYID >= DMX_KEY_CNT)\
        {\
            TEE_DMX_LOG_PrintInfo("KEYID invalid");\
            TEE_DMX_LOG_PrintInfo(KEYID);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA; \
        } \
    } while (0)

#define DMX_DRV_CHECK_RECID(RECID) \
    do {  \
        if (RECID < 0 || RECID >= DMX_REC_CNT)\
        {\
            TEE_DMX_LOG_PrintInfo("RECID invalid");\
            TEE_DMX_LOG_PrintInfo(RECID);\
            TEE_DMX_PrintErrCode(HI_ERR_DMX_INVALID_PARA);\
            return HI_ERR_DMX_INVALID_PARA; \
        } \
    } while (0)

typedef struct ChanBufInfo {
    HI_U8 *BufStartVirAddr;
    HI_U32 BufStartAddr;
    HI_U32 BufSize;
    HI_U32 ShadowBufStartAddr;
    HI_U32 BufSmmz2StartAddr;
    HI_BOOL FlushShadowBuf;
}ChanBufInfo_S;

typedef struct RecBufInfo {
    HI_U8 *BufStartVirAddr;
    HI_U32 BufStartAddr;
    HI_U32 BufSize;
    HI_U32 BufSmmz2StartAddr;
}RecBufInfo_S;

typedef struct
{
    HI_U32          DmxId;
    HI_U32          KeyId;
    ChanBufInfo_S   ChanSecBufInfo;
    struct tee_hal_mutex    LockChn;
    TEE_UUID        UserUUID;
} DMX_ChanInfo_S;

typedef enum
{
    DMX_KEY_MODE_TEE_SECURE = 0,  //create in TEE, secure key
    DMX_KEY_MODE_TEE_NONSECURE,   //create in TEE, nonsecure key
    DMX_KEY_MODE_REE_NONSECURE,   //create in REE, nonsecure key

    DMX_KEY_MODE_BUTT
} DMX_KeySecureMode;

typedef struct
{
    HI_U32         DmxId;
    HI_U32         KeyId;
    HI_U32         CaType;
    HI_U32         CaEntropy;
    HI_U32         DescType;
    HI_U32         KeyLen;
    TEE_UUID       UserUUID;
    DMX_KeySecureMode KeySecureMode;
} DMX_KeyInfo_S;

typedef struct
{
    HI_U32         Scrambler;
    HI_U32         ActiveKey;
}DMX_Encrypt_KeyInfo_S;

typedef struct
{
    HI_S32         PicParser;
    RecBufInfo_S   RecSecBufInfo;
    TEE_SMMU_BUFFER_S TmpHevcIdxMmuBuf;
    TEE_DMX_REC_INDEX_S   LastFrameInfo;
    TEE_UUID       UserUUID;
}DMX_RecInfo_S;

typedef struct hiDmx_Set_S
{
    HI_U32                      IoBase;
    HI_U32                      MmuIoBase;

    HI_U32                      RamPortCnt;

    DMX_ChanInfo_S              DmxChanInfo[DMX_CHANNEL_CNT];
    HI_U32                      DmxChanCnt;
    struct tee_hal_mutex        LockAllChn;
    DECLARE_BITMAP(ChnBitmap, DMX_CHANNEL_CNT);

    DMX_KeyInfo_S               DmxKeyInfo[DMX_KEY_CNT];
    DMX_Encrypt_KeyInfo_S       DmxEncryptKeyInfo[DMX_KEY_CNT];
    HI_U32                      DmxKeyCnt;
    struct tee_hal_mutex        LockAllKey;
    DECLARE_BITMAP(KeyBitmap, DMX_KEY_CNT);

    DMX_RecInfo_S               DmxRecInfo[DMX_REC_CNT];
    HI_U32                      DmxRecCnt;

    HI_U32                      DmxOqCnt;
}Dmx_Set_S;

Dmx_Set_S *GetDmxSetByDmxid(HI_U32 DmxId);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __TEE_DRV_DEMUX_DEFINE_H__ */
