
#ifndef __PLAY_H__
#define __PLAY_H__

#include "hi_type.h"
#include "hi_psi_si.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HI_PLAY_COUNT   5

HI_S32  HiPlayDvb(HI_U32 PlayId, HI_U32 TunerId, HI_U32 ProgNum);
HI_S32  HiPlayDvbStop(HI_U32 PlayId);

HI_S32  HiPlayTs(HI_U32 PlayId, HI_CHAR *TsFile, HI_U32 VidPid, HI_CHAR *VidFmt, HI_U32 AudPid, HI_CHAR *AudFmt, HI_BOOL bHDDisplay);
HI_S32  HiPlayTsStop(HI_U32 PlayId);

HI_S32  HiPlayIp(HI_U32 PlayId, HI_CHAR *IpAddr);
HI_S32  HiPlayIpStop(HI_U32 PlayId);

HI_S32  HiPlayEs(HI_U32 PlayId, HI_CHAR *VidFile, HI_CHAR *VidFmt, HI_CHAR *AudFile, HI_CHAR *AudFmt, HI_U32 u32Fps);
HI_S32  HiPlayEsStop(HI_U32 PlayId);

HI_S32  HiPlayPvr(HI_U32 PlayId, HI_U32 DmxId, HiPmtData *PmtData, HI_HANDLE *Avplay);
HI_S32  HiPlayPvrStop(HI_U32 PlayId);

HI_S32  HiPlayGetInfo(HI_U32 PlayId, HI_HANDLE *Avplay);
HI_VOID HiPlayCleanPmt(HI_U32 TunerId);

HI_S32  HiPlayInit(HI_VOID);
HI_S32  HiPlayDeInit(HI_VOID);

#ifdef __cplusplus
}
#endif

#endif

