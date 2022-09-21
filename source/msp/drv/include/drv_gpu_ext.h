#ifndef __DRV_GPU_EXT_H__
#define __DRV_GPU_EXT_H__

#include "hi_drv_module.h"
#include "hi_module.h"
#include "hi_type.h"

typedef HI_S32 (*FN_GPU_Set_Freq_And_Volt)(HI_S32 s32Freq, HI_S32 s32Volt, HI_S32 s32DvfsEnable);
typedef HI_S32 (*FN_GPU_Set_Max_Freq)(HI_S32 s32Freq);
typedef struct
{
    FN_GPU_Set_Freq_And_Volt	pfnGPUSetFreqAndVolt;
    FN_GPU_Set_Max_Freq		pfnGPUSetMaxFreq;
}GPU_EXT_FUNC_S;

#endif /* __DRV_GPU_EXT_H__ */

