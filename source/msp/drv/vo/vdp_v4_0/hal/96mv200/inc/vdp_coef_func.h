#ifndef __VDP_COEF_FUNC_H__
#define __VDP_COEF_FUNC_H__


#include "vdp_define.h"
#include "hi_reg_common.h"
#include "hi_type.h"
#if EDA_TEST
#include "vdp_sti.h"
#include "vdp_env_def.h"
#include "vdp_frw.h"
#endif
#include "vdp_hal_comm.h"
#include "vdp_drv_coef.h"

typedef struct
{
    HI_U32 data3;
    HI_U32 data2;
    HI_U32 data1;
    HI_U32 data0;
    HI_U32 depth;
}VDP_U128_S;




HI_U32 VDP_FUNC_GenCoef(VDP_COEF_GEN_CFG* stCfg);
HI_U32 VDP_FUNC_SendCoef(VDP_DRV_COEF_SEND_CFG* stCfg);
HI_U32 VDP_FUNC_Push128(VDP_U128_S* pstData128, HI_U32 coef_data, HI_U32 bit_len);
HI_U32 VDP_FUNC_WriteDDR(STI_FILE_TYPE_E enStiType, FILE* fp_coef ,HI_U32 addr, VDP_U128_S * pstData128 );

HI_S32 VDP_FUNC_CoefUpSortU8  ( const void *a, const void *b);
HI_S32 VDP_FUNC_CoefUpSortS8  ( const void *a, const void *b);
HI_S32 VDP_FUNC_CoefUpSortU16 ( const void *a, const void *b);
HI_S32 VDP_FUNC_CoefUpSortS16 ( const void *a, const void *b);
HI_S32 VDP_FUNC_CoefUpSortU32 ( const void *a, const void *b);
HI_S32 VDP_FUNC_CoefUpSortS32 ( const void *a, const void *b);


#endif

