/**
\file
\brief common head file or PVR
\copyright Shenzhen Hisilicon Co., Ltd.
\version draft
\author QuYaxin 46153
\date 2010-3-26
*/

#ifndef __SAMPLE_PVR_COMMON_H__
#define __SAMPLE_PVR_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_unf_pvr.h"

#include "hi_adp_search.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
#define PVR_FS_DIR              "/tmpfs/"
#define PVR_CIPHER_KEY          "688PVR-KEY-123456789"

#define PVR_DMX_ID_LIVE             0
#define PVR_DMX_PORT_ID_IP          HI_UNF_DMX_PORT_RAM_0
#if defined(CHIP_TYPE_hi3719cv100)\
    || defined(CHIP_TYPE_hi3716mv420)\
    || defined(CHIP_TYPE_hi3718cv100)\
    || defined(CHIP_TYPE_hi3798cv200)\
    || defined(CHIP_TYPE_hi3798mv200)\
    || defined(CHIP_TYPE_hi3798mv300)\
    || defined(CHIP_TYPE_hi3798mv310)\
    || defined(CHIP_TYPE_hi3798mv200_a)\
    || defined(CHIP_TYPE_hi3796mv100)\
    || defined(CHIP_TYPE_hi3716dv100)\
    || defined(CHIP_TYPE_hi3796mv200)
#define PVR_DMX_PORT_ID_DVB HI_UNF_DMX_PORT_TSI_0
#else
#define PVR_DMX_PORT_ID_DVB HI_UNF_DMX_PORT_IF_0
#endif
#define PVR_DMX_PORT_ID_PLAYBACK    HI_UNF_DMX_PORT_RAM_1
#define PVR_DMX_ID_REC              1

#define PVR_PROG_INFO_MAGIC  0xABCDE
#ifdef CONFIG_SUPPORT_CA_RELEASE
#define PVR_SAMPLE_Printf(fmt, args...)
#else
#define PVR_SAMPLE_Printf(fmt, args...) \
    ({printf("[%s:%d]: " fmt "", __FUNCTION__, __LINE__, ## args);})
#endif
#define PVR_PROG_MAX_AUDIO      (8)
#define PVR_SUBTITLING_MAX      (15)
#define PVR_SUBTDES_INFO_MAX    (10)
#define PVR_CAPTION_SERVICE_MAX (16)
#define PVR_TTX_MAX             (15)
#define PVR_TTX_DES_MAX         (10)
/*************************** Structure Definition ****************************/
typedef struct hiPVR_PMT_AUDIO_S
{
    HI_U32 u32AudioEncType;
    HI_U16 u16AudioPid;
} PVR_PMT_AUDIO;

typedef struct hiPVR_PMP_SUBTITLE_DES_S
{
    HI_U32 u32LangCode; /* low 24-bit valid */
    HI_U8  u8SubtitleType;
    HI_U16 u16PageID;
    HI_U16 u16AncillaryPageID;
}PVR_PMP_SUBTITLE_DES;

typedef struct hiPVR_PMT_SUBTITLE_S
{
    HI_U16 u16SubtitlingPID;
    HI_U8 u8DesTag; /*  */
    HI_U8 u8DesLength;
    HI_U8 u8DesInfoCnt;
    PVR_PMP_SUBTITLE_DES DesInfo[SUBTDES_INFO_MAX];
}PVR_PMT_SUBTITLE;

typedef struct hiPVR_PMT_SCTE_SUBTITLE_S
{
    HI_U16 u16SCTESubtPID;
    HI_U32 u32LanguageCode;
}PVR_PMT_SCTE_SUBTITLE_S;

typedef struct hiPVR_PMT_CLOSED_CAPTION_S
{
    HI_U32 u32LangCode;
    HI_U8 u8IsDigitalCC;
    HI_U8 u8ServiceNumber;
    HI_U8 u8IsEasyReader;
    HI_U8 u8IsWideAspectRatio;
}PVR_PMT_CLOSED_CAPTION_S;

typedef struct hiPVR_PMT_TTX_DES_S
{
    HI_U32 u32ISO639LanguageCode; /* low 24-bit valid */
    HI_U8  u8TtxType;
    HI_U8  u8TtxMagazineNumber;
    HI_U8  u8TtxPageNumber;
} PVR_PMT_TTX_DES_S;

typedef struct hiPVR_PMT_TTX_S
{
    HI_U16 u16TtxPID;
    HI_U8 u8DesTag;
    HI_U8 u8DesLength;
    HI_U8 u8DesInfoCnt;
    PVR_PMT_TTX_DES_S stTtxDes[TTX_DES_MAX];
} PVR_PMT_TTX_S;

typedef struct hiPVR_PROG_INFO_S
{
    HI_U32                  u32MagicNumber;
    HI_U32 ProgID;          /* program ID */
    HI_U32 PmtPid;          /*program PMT PID*/
    HI_U32 PcrPid;          /*program PCR PID*/
    HI_U32 VideoType;
    HI_U16 VElementNum;        /* video stream number */
    HI_U16 VElementPid;        /* the first video stream PID*/
    HI_U32 AudioType;
    HI_U16 AElementNum;        /* audio stream number */
    HI_U16 AElementPid;        /* the first audio stream PID*/
    PVR_PMT_AUDIO Audioinfo[PROG_MAX_AUDIO];     /* multi-audio info, added by gaoyanfeng 00182102 */
    HI_U32 SubtType;            /*0---NONE,1---DVB,2---SCTE,3---BOTH*/
    HI_U16 u16SubtitlingNum;
    PVR_PMT_SUBTITLE SubtitingInfo[SUBTITLING_MAX];
    PVR_PMT_SCTE_SUBTITLE_S stSCTESubtInfo;
    HI_U16 u16ClosedCaptionNum;
    PVR_PMT_CLOSED_CAPTION_S stClosedCaption[CAPTION_SERVICE_MAX];
    HI_U16 u16ARIBCCPid;
    HI_U16 u16TtxNum;
    PVR_PMT_TTX_S stTtxInfo[TTX_MAX];
    HI_UNF_PVR_REC_ATTR_S   stRecAttr;
}PVR_PROG_INFO_S;


/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/
HI_S32 PVR_checkIdx(char *pfileName);
HI_S32 PVR_SavePorgInfo(PVR_PROG_INFO_S *pstProgInfo, HI_CHAR *pszPvrRecFile);
HI_S32 PVR_GetPorgInfo(PVR_PROG_INFO_S *pstProgInfo, const HI_CHAR *pszPvrRecFile);

HI_S32 PVR_RecStart(char *path, PMT_COMPACT_PROG *pstProgInfo, HI_U32 u32DemuxID,
            HI_BOOL bRewind, HI_BOOL bDoCipher, HI_U64 maxSize, HI_U32 *pRecChn);
HI_S32 PVR_RecStop(HI_U32 u32RecChnID);


HI_S32 PVR_StartLivePlay(HI_HANDLE hAvplay, const PMT_COMPACT_PROG *pProgInfo);
HI_S32 PVR_StopLivePlay(HI_HANDLE hAvplay);

HI_S32 PVR_StartPlayBack(const HI_CHAR *pszFileName, HI_U32 *pu32PlayChn, HI_HANDLE hAvplay);
HI_VOID PVR_StopPlayBack(HI_U32 playChn);
HI_S32 PVR_SwitchDmxSource(HI_U32 dmxId, HI_U32 protId);
HI_S32 PVR_SearchFile(HI_U32 u32DmxId, HI_U32 u32PortId, const HI_CHAR *pszFileName, PMT_COMPACT_TBL **ppProgTbl);

HI_S32 PVR_AvplayInit(HI_HANDLE hWin, HI_HANDLE *phAvplay, HI_HANDLE* phSoundTrack);
HI_S32  PVR_AvplayDeInit(HI_HANDLE hAvplay, HI_HANDLE hWin, HI_HANDLE hSoundTrack);
HI_S32 PVR_SetAvplayPidAndCodecType(HI_HANDLE hAvplay, const PMT_COMPACT_PROG *pProgInfo);

HI_VOID PVR_CallBack(HI_U32 u32ChnID, HI_UNF_PVR_EVENT_E EventType, HI_S32 s32EventValue, HI_VOID *args);
HI_S32 PVR_RegisterCallBacks(HI_VOID);
HI_S32 PVR_CheckKeyladder(HI_UNF_PVR_CIPHER_S* PvrCipher);
HI_U8* PVR_GetEventTypeStringByID(HI_UNF_PVR_EVENT_E eEventID);
HI_VOID PVR_SetTvpFlag(HI_BOOL bSupport);
HI_VOID PVR_SetCallbackFlag(HI_BOOL bExtra, HI_BOOL bExtendTee);
HI_VOID PVR_RecProgInfoTrans(PVR_PROG_INFO_S *pstFileInfo, PMT_COMPACT_PROG *pstProgInfo);
HI_VOID PVR_PlayProgInfoTrans(PMT_COMPACT_PROG *pstProgInfo, PVR_PROG_INFO_S *pstFileInfo);
#if 0
HI_VOID PVR_SetSecBufFlag(HI_BOOL bSupport);
HI_S32 SampleTeeInit(HI_VOID);
HI_S32 SampleTeeDeInit(HI_VOID);
#endif


#ifdef __cplusplus
}
#endif
#endif /* __SAMPLE_PVR_COMMON_H__ */


