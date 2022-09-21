#ifndef __HI_DRV_AO_EXT_H__
#define __HI_DRV_AO_EXT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_drv_dev.h"
#include "hi_drv_ao.h"

typedef struct
{
    HI_S32 (*pfnAO_DrvResume)(PM_BASEDEV_S*);
    HI_S32 (*pfnAO_DrvSuspend)(PM_BASEDEV_S*, pm_message_t);
    //for voip
    HI_S32  (*pfnAO_TrackGetDefAttr)(HI_UNF_AUDIOTRACK_ATTR_S *);
    HI_S32  (*pfnAO_TrackAllocHandle)(HI_UNF_SND_E, HI_UNF_SND_TRACK_TYPE_E, struct file*, HI_HANDLE*);
    HI_VOID (*pfnAO_TrackFreeHandle)(HI_HANDLE);
    HI_S32  (*pfnAO_TrackCreate)(HI_UNF_SND_E, HI_UNF_AUDIOTRACK_ATTR_S*, HI_BOOL, AO_BUF_ATTR_S*, HI_HANDLE);
    HI_S32  (*pfnAO_TrackDestory)(HI_U32);
    HI_S32  (*pfnAO_TrackStart)(HI_U32);
    HI_S32  (*pfnAO_TrackStop)(HI_U32);
    HI_S32  (*pfnAO_TrackSendData)(HI_U32, AO_FRAMEINFO_S*);
} AIAO_EXPORT_FUNC_S;

HI_S32 AIAO_DRV_ModInit(HI_VOID);
HI_VOID AIAO_DRV_ModExit(HI_VOID);

#if defined(HI_MCE_SUPPORT)
HI_S32  HI_DRV_AO_Init(HI_VOID);
HI_VOID HI_DRV_AO_DeInit(HI_VOID);
HI_S32  HI_DRV_AO_SND_Init(struct file *pfile);
HI_S32  HI_DRV_AO_SND_DeInit(struct file *pfile);
HI_S32  HI_DRV_AO_SND_GetDefaultOpenAttr(HI_UNF_SND_E enSound, HI_UNF_SND_ATTR_S *pstAttr);
HI_S32  HI_DRV_AO_SND_Open(HI_UNF_SND_E enSound, HI_UNF_SND_ATTR_S *pstAttr, struct file *pfile);
HI_S32  HI_DRV_AO_SND_Close(HI_UNF_SND_E enSound, struct file *pfile);
HI_S32  HI_DRV_AO_SND_SetVolume(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_GAIN_ATTR_S* pstGain);
HI_S32  HI_DRV_AO_Track_GetDefaultOpenAttr(HI_UNF_SND_TRACK_TYPE_E enTrackType, HI_UNF_AUDIOTRACK_ATTR_S *pstAttr);
HI_S32  HI_DRV_AO_Track_Create(HI_UNF_SND_E enSound, HI_UNF_AUDIOTRACK_ATTR_S *pstAttr, HI_BOOL bAlsaTrack, struct file *pfile, HI_HANDLE *phTrack);
HI_S32  HI_DRV_AO_Track_Destroy(HI_HANDLE hSndTrack);
HI_S32  HI_DRV_AO_Track_Flush(HI_HANDLE hSndTrack);
HI_S32  HI_DRV_AO_Track_Start(HI_HANDLE hSndTrack);
HI_S32  HI_DRV_AO_Track_Stop(HI_HANDLE hSndTrack);
HI_S32  HI_DRV_AO_Track_GetDelayMs(HI_HANDLE hSndTrack, HI_U32 *pDelayMs);
HI_S32  HI_DRV_AO_Track_SendData(HI_HANDLE hSndTrack, AO_FRAMEINFO_S *pstAOFrame);
HI_S32  HI_DRV_AO_Track_AttachAi(HI_HANDLE hSndTrack, HI_HANDLE hAi);
HI_S32  HI_DRV_AO_Track_DetachAi(HI_HANDLE hSndTrack, HI_HANDLE hAi);
#endif

#if    defined (CHIP_TYPE_hi3798mv100)  \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)   \
    || defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)
#define AIAO_SRC_PLL_REG_FRAC_VAL (0x11e353f8)
#define AIAO_SRC_PLL_REG_INT_VAL  (0x08201025)
#elif defined(CHIP_TYPE_hi3798cv200)
#define AIAO_SRC_PLL_REG_FRAC_VAL (0x12a5e354)
#define AIAO_SRC_PLL_REG_INT_VAL  (0x0800209b)
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv200_a)
#define AIAO_SRC_PLL_REG_FRAC_VAL (0x12ed9169)
#define AIAO_SRC_PLL_REG_INT_VAL  (0x0800207c)
#elif defined(CHIP_TYPE_hi3796mv200)
#define AIAO_SRC_PLL_REG_FRAC_VAL (0x11e353f8)
#define AIAO_SRC_PLL_REG_INT_VAL  (0x08201025)
#else
#define AIAO_SRC_PLL_REG_FRAC_VAL (0xffffffff)
#define AIAO_SRC_PLL_REG_INT_VAL  (0xffffffff)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif//__HI_DRV_AO_EXT_H__