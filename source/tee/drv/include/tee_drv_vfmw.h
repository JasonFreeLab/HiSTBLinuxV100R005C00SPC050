#ifndef __TEE_DRV_VFMW_H__
#define __TEE_DRV_VFMW_H__

#include "hi_type.h"

HI_S32 HI_DRV_VDEC_GetHandle(const HI_U32 StartAddr, HI_U32 *pHandle);
HI_VOID HI_DRV_VDEC_ResetBuff();

#endif
