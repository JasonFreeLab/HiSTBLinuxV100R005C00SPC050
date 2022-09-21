
#ifndef __DSP_ELF_H__
#define __DSP_ELF_H__

#include "hi_type.h"

HI_S32 CopyELFSection(HI_UCHAR* pElfAddr);
HI_S32 CheckELFPaser(HI_UCHAR* pElfAddr);
HI_S32 ResetELFSection(HI_U32 u32BaseAddr, HI_U32 u32Size);

#endif
