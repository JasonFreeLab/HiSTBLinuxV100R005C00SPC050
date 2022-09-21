#include "hi_type.h"
#include "drv_tee_mem.h"
#include "tee_drv_pvr.h"
#include "tee_os_hal.h"

#ifndef __TE_DRV_PVR_PRIV_H__
#define __TE_DRV_PVR_PRIV_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*this macro is open, pvr will map the un-secure memory each communication. if overflow, please close the macro to try*/
//#define TEE_PVR_MAP_UN_SEC_MEM_EACH
#define TEE_PVR_OPTIMIZE_FLAG   (1)

typedef struct tagTEE_DRV_PVR_REC_CHAN_S
{
#ifndef TEE_PVR_MAP_UN_SEC_MEM_EACH
    TEE_SMMU_BUFFER_S stRecIdxBuf;
#endif
    TEE_DRV_PVR_BUFFER_INFO_S stTsBuf;/*receive ts buffer used to save ts data from demux info*/
}TEE_DRV_PVR_REC_CHAN_S;/*recording channel param*/

typedef struct tagTEE_DRV_PVR_PLAY_CHAN_S
{
    HI_U32 u32Dummy;/*don't need now, reserved*/
}TEE_DRV_PVR_PLAY_CHAN_S;/*paly channel param*/

typedef union
{
    TEE_DRV_PVR_REC_CHAN_S stRecInfo;
    TEE_DRV_PVR_PLAY_CHAN_S stPlayInfo;
}TEE_DRV_PVR_CHAN_INFO_S;

typedef struct tagTEE_DRV_PVR_INST_S
{
    TEE_PVR_TYPE_E enType;/*channel type*/
    TEE_DRV_PVR_CHAN_INFO_S stChnInfo;/*channel info*/
}TEE_DRV_PVR_INST_S;

typedef struct tagTEE_DRV_PVR_INST_CTRL_S
{
    struct tee_hal_mutex PvrMutex; /*channel lock*/
    HI_BOOL bUsed[TEE_PVR_MAX_INSTANCE];/*channel stat*/
    TEE_DRV_PVR_INST_S stInstInfo[TEE_PVR_MAX_INSTANCE];/*channel instance*/
}TEE_DRV_PVR_INST_CTRL_S;

/**********************************************************************************/
HI_S32 DRV_PVR_RecOpenChannel(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, HI_S32 s32BufLen);
HI_S32 DRV_PVR_RecCloseChannel(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo);
HI_S32 DRV_PVR_RecCheckDmxBuf(HI_HANDLE u32DmxHandle, TEE_DRV_PVR_INDEX_INFO_S* pstRecIdxBuf);
HI_S32 DRV_PVR_RecProcTsData(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, TEE_DRV_PVR_INDEX_INFO_S *pstRecIdxBuf);
HI_S32 DRV_PVR_RecGetBufInfo(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, HI_U32 *pu32Addr, HI_U32 u32MaxLen, HI_U32 *pu32BufLen);
HI_S32 DRV_PVR_RecGetStatus(TEE_DRV_PVR_REC_CHAN_S *pstRecInfo, TEE_DRV_PVR_REC_STATUS_S *pstTeeState);
/**********************************************************************************/
HI_S32 DRV_PVR_PlayCopyReeDataToTee(HI_VOID *pDst, HI_VOID *pSrc, HI_U32 u32DataLen);
HI_S32 DRV_PVR_PlayProcTsData(TEE_PVR_PLAY_TSDATA_INFO_S *pstDataInfo, HI_VOID *pDataAddr);
/**********************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
