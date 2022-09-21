#ifndef __DRV_ADSP_EXT_H__
#define __DRV_ADSP_EXT_H__

#include "hi_drv_dev.h"
#include "hi_type.h"
#include "hi_audsp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef struct
{
    HI_S32 (*pfnADSP_LoadFirmware)(ADSP_CODEID_E);
    HI_S32 (*pfnADSP_UnLoadFirmware)(ADSP_CODEID_E);
    HI_S32 (*pfnADSP_GetAoeFwmInfo)(ADSP_CODEID_E, AOE_FW_INFO_S*);
} ADSP_EXPORT_FUNC_S;

HI_S32  ADSP_DRV_ModInit(HI_VOID);
HI_VOID ADSP_DRV_ModExit(HI_VOID);

#if defined(HI_MCE_SUPPORT)
HI_S32  HI_DRV_ADSP_Init(HI_VOID);
HI_VOID HI_DRV_ADSP_DeInit(HI_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __DRV_ADSP_EXT_H__ */
