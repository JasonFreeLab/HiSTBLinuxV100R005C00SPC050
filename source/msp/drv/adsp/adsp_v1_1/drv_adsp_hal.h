#ifndef __DRV_ADSP_HAL_H__
#define __DRV_ADSP_HAL_H__

#include "hi_type.h"
#include "hi_audsp_common.h"

/******************************************************************************/
#ifdef __aarch64__
#define adsp_ioremap ioremap_wc
#else
#define adsp_ioremap ioremap_nocache
#endif
#define adsp_iounmap iounmap
/******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern AOE_FW_INFO_S g_stDspFwInfo;

HI_VOID HAL_ADSP_DeInit(HI_VOID);
HI_S32  HAL_ADSP_Init(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __DRV_ADSP_HAL_H__ */