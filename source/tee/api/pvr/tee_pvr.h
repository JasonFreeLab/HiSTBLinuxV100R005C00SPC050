#define HI_LOG_D_MODULE_ID             HI_MODULE_ID_PVR
#include "hi_tee_debug.h"

#ifndef __TEE_PVR_H__
#define __TEE_PVR_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define TEE_PVR_LOG_ERRCODE_DEF(errid)      (HI_U32)(((HI_MODULE_ID_PVR) << 16)  | (errid))
#define HI_TEE_ERROR_PVR_BASE               TEE_PVR_LOG_ERRCODE_DEF(0)          /*general error*/
//#define HI_TEE_ERROR_PVR_BASE                      (0x81300000)                                         /*general error*/
#define HI_TEE_ERROR_PVR_NOT_SUPPORT        TEE_PVR_LOG_ERRCODE_DEF(1)          /*not support the operation*/
#define HI_TEE_ERROR_PVR_NULL_PTR           TEE_PVR_LOG_ERRCODE_DEF(2)          /*null pointer*/
#define HI_TEE_ERROR_PVR_NO_ENOUGH_DATA     TEE_PVR_LOG_ERRCODE_DEF(3)          /*the ts data is less than 47k, can't be got*/
#define HI_TEE_ERROR_PVR_INVALID_PARAM      TEE_PVR_LOG_ERRCODE_DEF(4)          /*the inputed param is invalid*/
#define HI_TEE_ERROR_PVR_NO_MEM             TEE_PVR_LOG_ERRCODE_DEF(5)          /*malloc memory failed*/
#define HI_TEE_ERROR_PVR_INVALID_LEN        TEE_PVR_LOG_ERRCODE_DEF(6)          /*invalid data length from demux*/
#define HI_TEE_ERROR_PVR_LOW_BUFFER         TEE_PVR_LOG_ERRCODE_DEF(7)          /*the un-used buffer is low*/
#define HI_TEE_ERROR_PVR_INDEX_MORE         TEE_PVR_LOG_ERRCODE_DEF(8)          /*reserved*/
#define HI_TEE_ERROR_NO_CHANNEL             TEE_PVR_LOG_ERRCODE_DEF(9)          /* no free channel left*/
#define HI_TEE_ERROR_BUSY                   TEE_PVR_LOG_ERRCODE_DEF(10)         /*reserved*/

#define TEE_PVR_MAX_INSTANCE                (4)                                 /*support 4 channels for recording*/
#define TEE_PVR_DATA_ALIGN                  (47*1024)                           /*align length*/
#define REE_PVR_MAX_INDEX_NUM               (256)                               /*max index num from demux*/
#define TEE_PVR_MAX_BUF_LENGTH              (2*47*1024*1024)                    /*max buffer length*/
#define TEE_INVALID_PVR_CHANNEL             (0xFFFFFFFF)

typedef enum
{
    TEE_PVR_RECORD = 0, /*recording*/
    TEE_PVR_PLAYBACK,   /*playback, reserved*/
    TEE_PVR_BUTT
} TEE_PVR_TYPE_E;

enum PVR_DRV_IOCTL_FUNC_ID
{
    TEE_DRV_PVR_DEINIT = 0x0,
    TEE_DRV_PVR_OPENCHANNEL,
    TEE_DRV_PVR_CLOSECHANNEL,
    TEE_DRV_PVR_RECPROCTSDATA,
    TEE_DRV_PVR_RECCOPYTOREE,
    TEE_DRV_PVR_PLAYCOPYTOTEE,
    TEE_DRV_PVR_PLAYPROCTSDATA,
    TEE_DRV_PVR_RECGETOUTPUTBUFINFO,
    TEE_DRV_PVR_RECGETSTATUS,
};

typedef struct
{
    TEE_PVR_TYPE_E enType;
    HI_U32 u32RecChn;
    HI_U32 u32DmxRecChn;
    HI_U32 u32NSSmmuAddr;
    HI_U32 u32SSmmuAddr;
    HI_U32 u32DataLen;
    HI_U32 *pu32RecChn;
    HI_U32 *pu32SSmmuAddr;
    HI_U32 *pu32DataLen;
    HI_U32 u32HeadOffset;
    HI_U32 u32EndOffset;
    HI_U32 u32HeadToAdd;
    HI_U32 u32EndToAdd;
} HI_TEE_PVR_DRV_IOCTRL_BUF;

#define PVR_UNUSED(x)   ((x)=(x))

#define TEE_WARN_PVR(fmt...)                    HI_LOG_WARN(fmt)
#define TEE_DEBUG_PVR(fmt...)                   HI_LOG_DEBUG(fmt)
#define TEE_FATAL_PVR(fmt...)                   HI_LOG_FATAL(fmt)
#define TEE_ERR_PVR(fmt...)                     HI_LOG_ERROR(fmt)

#define TEE_PVR_ENTER()                         HI_LOG_FuncEnter()
#define TEE_PVR_EXIT()                          HI_LOG_FuncExit()

#define TEE_PVR_PrintFuncWar(Func, ErrCode)     HI_LOG_PrintFuncWar(Func, ErrCode)
#define TEE_PVR_PrintFuncErr(Func, ErrCode)     HI_LOG_PrintFuncErr(Func, ErrCode)
#define TEE_PVR_PrintErrCode(ErrCode)           HI_LOG_PrintErrCode(ErrCode)

#define TEE_PVR_LOG_PrintS32(val)               HI_LOG_PrintS32(val)
#define TEE_PVR_LOG_PrintU32(val)               HI_LOG_PrintU32(val)
#define TEE_PVR_LOG_PrintS64(val)               HI_LOG_PrintS64(val)
#define TEE_PVR_LOG_PrintU64(val)               HI_LOG_PrintU64(val)
#define TEE_PVR_LOG_PrintH32(val)               HI_LOG_PrintH32(val)
#define TEE_PVR_LOG_PrintH64(val)               HI_LOG_PrintH64(val)
#define TEE_PVR_LOG_PrintStr(val)               HI_LOG_PrintStr(val)
#define TEE_PVR_LOG_PrintVoid(val)              HI_LOG_PrintVoid(val)
#define TEE_PVR_LOG_PrintFloat(val)             HI_LOG_PrintFloat(val)
#define TEE_PVR_LOG_PrintInfo(val)              HI_LOG_PrintInfo(val)

#define TEE_PVR_DBG_PrintS32(val)               HI_DBG_PrintS32(val)
#define TEE_PVR_DBG_PrintU32(val)               HI_DBG_PrintU32(val)
#define TEE_PVR_DBG_PrintS64(val)               HI_DBG_PrintS64(val)
#define TEE_PVR_DBG_PrintU64(val)               HI_DBG_PrintU64(val)
#define TEE_PVR_DBG_PrintH32(val)               HI_DBG_PrintH32(val)
#define TEE_PVR_DBG_PrintH64(val)               HI_DBG_PrintH64(val)
#define TEE_PVR_DBG_PrintStr(val)               HI_DBG_PrintStr(val)
#define TEE_PVR_DBG_PrintVoid(val)              HI_DBG_PrintVoid(val)
#define TEE_PVR_DBG_PrintFloat(val)             HI_DBG_PrintFloat(val)
#define TEE_PVR_DBG_PrintInfo(val)              HI_DBG_PrintInfo(val)

HI_S32 TEE_PVR_DeInit(HI_VOID);
HI_S32 TEE_PVR_RecOpenChannel(HI_U32 *pu32RecChnId, HI_S32 s32BufferLen);
HI_S32 TEE_PVR_RecCloseChannel(HI_U32 u32ChnId);
HI_S32 TEE_PVR_RecProcTsData(HI_U32 u32ChnId, HI_U32 u32NSSmmuAddr, HI_U32 u32DemuxHandle);
HI_S32 TEE_PVR_RecCopyToRee(HI_U32 u32SrcAddr, HI_U32 u32DstAddr, HI_U32 *pu32Len, HI_BOOL bPlayback);
HI_S32 TEE_PVR_RecGetOutputBufInfo(HI_U32 u32ChnId, HI_U32 u32MaxLen, HI_U32 *pu32SmmuAddr, HI_U32 *pu32ValidLen);
HI_S32 TEE_PVR_RecGetStatus(HI_U32 u32ChnId, HI_U32 u32SmmuAddr);
HI_S32 TEE_PVR_PlayCopyFromRee(HI_U32 u32ReeAddr, HI_U32 u32TeeAddr, HI_U32 u32DataLen );
HI_S32 TEE_PVR_PlayProcessTsData(HI_U32 u32DataAddr, HI_U32 u32HeadOffset, HI_U32 u32EndOffset, HI_U32 u32HeadToAdd, HI_U32 u32EndToAdd);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif
