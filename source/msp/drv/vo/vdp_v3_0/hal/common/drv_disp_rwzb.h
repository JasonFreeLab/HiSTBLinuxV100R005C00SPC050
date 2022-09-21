#ifndef __VDP_RWZB_H_
#define __VDP_RWZB_H_

#include "drv_disp_com.h"

/*for full drive capability*/
#ifdef HI_VO_VDAC_LC_CIRCUIT
	 #if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420))
     #define  VDAC_DEFAULT_VALUE   0x801f0000
     #define SCH_PHASE 0xa3
	 #endif	 
#else
	#if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420))
    #define  VDAC_DEFAULT_VALUE   0x86048000
    #define SCH_PHASE 0x90
	#endif
	
#endif	

HI_U32 * VDP_Get_HDateSrc13Coef( HI_U32 u32Fmt);
HI_U32 * VDP_Get_SDateSrcCoef( HI_U32 Index);

#endif


