#ifndef __HI_TEE_VDP_WATERMARK_H__
#define __HI_TEE_VDP_WATERMARK_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

typedef struct {
    HI_S32 (*SetRenderParam) (const HI_U32 u32ServiceIdx, const  HI_TEE_VWM_PARAM_U *puNxgParam);
    HI_S32 (*GetRenderParam) (HI_HANDLE hVWM, HI_TEE_VWM_PARAM_U * pUWatermarkParam);
    HI_S32 (*CreateInstance) (const HI_TEE_VWM_INS_ATTR_S *pstAttr, HI_HANDLE *phVWM);
    HI_S32 (*DestroyInstance)(HI_HANDLE hVWM);
}VDP_VWM_OPERATION_S;

typedef HI_S32 (*RegisterCallbackOps)(HI_TEE_VWM_TYPE_E enType,
                                       VDP_VWM_OPERATION_S *pstvwmCallOps);


#ifdef __cplusplus
 #if __cplusplus
       }
 #endif
#endif

#endif
