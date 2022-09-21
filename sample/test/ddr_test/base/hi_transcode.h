
#ifndef __HI_TRANSCODE_H__
#define __HI_TRANSCODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define HI_TRANSCODE_COUNT  2

HI_S32  HiTranscodeStart(HI_U32 PlayId, HI_CHAR *VidFile, HI_CHAR *AudFile);
HI_S32  HiTranscodeStop(HI_U32 PlayId);
HI_S32  HiTransCastStart(HI_CHAR *VidFile, HI_CHAR *AudFile);
HI_S32  HiTransCastStop(HI_VOID);
HI_S32  HiTranscodeInit(HI_VOID);
HI_S32  HiTranscodeDeInit(HI_VOID);

#ifdef __cplusplus
}
#endif

#endif

