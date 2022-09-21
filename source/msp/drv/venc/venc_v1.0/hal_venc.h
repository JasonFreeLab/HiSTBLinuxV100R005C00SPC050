#ifndef __HAL_VENC_H__
#define __HAL_VENC_H__

#include "hi_type.h"
#include "drv_venc.h"

#ifdef VENC_S40V200_CONFIG
#include "drv_venc_reg_r006.h"
#endif

#ifdef VENC_3716CV200_CONFIG
#include "drv_venc_reg_r008.h"
#endif

#if ((defined VENC_S5V100_CONFIG)|(defined VENC_98M_CONFIG))
#include "drv_venc_reg_s5v100.h"
#endif

#if (defined VENC_98CV200_CONFIG)
#include "drv_venc_reg_98cv200.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef VENC_DPT_ONLY
#define VEDU_REG_BASE_ADDR 0xff360000
#define VEDU_IRQ_ID 133
#else
#define VEDU_REG_BASE_ADDR 0xf8c80000
#define VEDU_IRQ_ID 133                        /* 101+32 */
#endif

#ifdef HI_SMMU_SUPPORT
#define VEDU_SMMU_NS_IRQ_ID    133    /*101 + 32*/
#define VEDU_SMMU_S_IRQ_ID     133   /* 99 + 32*/
#endif

typedef unsigned long VEDU_LOCK_FLAG;

HI_VOID VENC_HAL_ClrAllInt( S_VEDU_REGS_TYPE *pVeduReg );
HI_VOID VENC_HAL_DisableAllInt( S_VEDU_REGS_TYPE *pVeduReg );
HI_VOID VENC_HAL_ReadReg( VeduEfl_EncPara_S *EncHandle );
HI_VOID VENC_HAL_CfgReg ( VeduEfl_EncPara_S *EncHandle );
HI_VOID VENC_HAL_ReadReg_Smmu( VeduEfl_EncPara_S *EncHandle );

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif //__HAL_VENC_H__
