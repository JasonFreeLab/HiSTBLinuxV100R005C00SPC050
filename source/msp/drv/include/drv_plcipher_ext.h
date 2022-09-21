/**
\file
\brief plcipher osi
\copyright Shenzhen Hisilicon Co., Ltd.
\version draft
\author QuYaxin 46153
\date 2009-11-8
*/

#ifndef __DRV_PLCIPHER_EXT_H__
#define __DRV_PLCIPHER_EXT_H__

/* add include here */
#include "hi_error_mpi.h"
#include "hi_unf_payloadcipher.h"
#include "hi_drv_plcipher.h"
#include "drv_plcipher_ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * export to other module.
 */

typedef HI_S32  (*FN_PLCIPHER_SetKey)(HI_HANDLE KeyHandle, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8Key, HI_U32 u32KeyLen);
typedef HI_S32  (*FN_PLCIPHER_SetIV)(HI_HANDLE KeyHandle, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyType, HI_U8 *pu8IV, HI_U32 u32IVLen);


typedef struct
{
    FN_PLCIPHER_SetKey  pfnPlcipherSetKey;
    FN_PLCIPHER_SetIV   pfnPlcipherSetIV;
} PLCIPHER_EXPORT_FUNC_S;

HI_S32  PLCIPHER_DRV_ModInit(HI_VOID);
HI_VOID PLCIPHER_DRV_ModExit(HI_VOID);

#ifdef __cplusplus
}
#endif
#endif /* __DRV_PLCIPHER_EXT_H__ */

