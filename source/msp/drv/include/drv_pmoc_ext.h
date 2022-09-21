#ifndef __DRV_PMOC_EXT_H__
#define __DRV_PMOC_EXT_H__

#include "hi_type.h"

typedef HI_S32 (*FN_PMOC_Set_CPU_Freq)(HI_S32 bFlag, HI_S32 s32Freq);
typedef struct
{
    FN_PMOC_Set_CPU_Freq                pfnPmocSetCPUFreq;

}PMOC_EXT_FUNC_S;


HI_S32 PMOC_DRV_ModInit(HI_VOID);
HI_VOID PMOC_DRV_ModExit(HI_VOID);

#endif /* __DRV_PMOC_EXT_H__ */

