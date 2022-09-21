#ifndef __VENC_HAL_EXT_H__
#define __VENC_HAL_EXT_H__

#include "drv_venc_osal_ext.h"

#ifdef __cplusplus
extern "C" {
#endif

#define  VENC_NULL_FUN_PTR    (-1)

typedef enum
{
    INTERRUPT_TYPE_PIC_END    = 0,
    INTERRUPT_TYPE_SLICE_END  = 1,
    INTERRUPT_TYPE_TIMEOUT    = 2,
    INTERRUPT_TYPE_ALL        = 3,
    INTERRUPT_TYPE_BUTT,
} INTERRUPT_TYPE_E;

typedef struct
{
    UINT32 Protocol;
    UINT32 Profile;
    UINT32 EncWidth;
    UINT32 EncHeight;
    UINT32 SlcSplitEn;
    UINT32 SlcSplitMode;
    UINT32 SplitSize;
    UINT32 CscMode;            /*0: disable 1:601->709 2:709->601*/
    UINT32 SecureEn;
    UINT32 LowDlyMode;
    UINT32 TimeOutEn;
    UINT32 PtBitsEn;
    UINT32 ParameterSetEn;
    UINT32 RegConfigMode;      /*0: Reg; 1:ddr;*/
} VENC_HAL_CTRL_S;

typedef struct
{
    UINT32 StoreFmt;           /* 0, semiplannar; 1, package; 2,planer */
    UINT32 PackageSel;
    UINT32 SrcYAddr;
    UINT32 SrcCAddr;
    UINT32 SrcVAddr;                  //just for input of planner
    UINT32 SStrideY;
    UINT32 SStrideC;
    UINT32 RcnYAddr[2];
    UINT32 RcnCAddr[2];
    UINT32 RStrideY;
    UINT32 RStrideC;
    UINT32 RcnHYAddr[2];
    UINT32 RcnHCAddr[2];
    UINT32 RHStrideY;
    UINT32 RHStrideC;
    UINT32 RcnIdx;             /* 0 or 1, idx for rcn, !idx for ref */

    UINT32 TmvAddr[2];
    UINT32 PmeAddr[2];
    UINT32 PmeInfoAddr[3];
    UINT32 PmeInfoIdx;
    UINT32 PmvPoc[6];

    UINT32 TunlCellAddr;

    UINT32 StrmBufAddr[16];
    UINT32 StrmBufSize[16];
    UINT32 StrmBufRpAddr; /* phy addr for hardware */
    UINT32 StrmBufWpAddr;

    UINT32 ParaSetAddr;
    UINT32 ParaSetBufSize;
    UINT32 ParaSetReg[48];
} VENC_HAL_BUF_S;

typedef struct
{
    UINT32 IntraPic;
    UINT32 TargetBits;         /* targetBits of each frame */
    UINT32 StartQp;
    UINT32 MinQp;
    UINT32 MaxQp;
    SINT32 IQpDelta;
    SINT32 PQpDelta;
} VENC_HAL_RC_S;

typedef struct
{
    UINT32 SrcyBypass;
    UINT32 SrcuBypass;
    UINT32 SrcvBypass;

    UINT32 SmmuNsPageBaseAddr;
    UINT32 SmmuNsErrWriteAddr;
    UINT32 SmmuNsErrReadAddr;

    UINT32 SmmuSPageBaseAddr;
    UINT32 SmmuSErrWriteAddr;
    UINT32 SmmuSErrReadAddr;
} VENC_HAL_SMMU_S;

typedef struct
{
    UINT32 SlcHdrStream [4];
    UINT32 ReorderStream[2];
    UINT32 MarkingStream[2];
    UINT32 SlcHdrBits[2];         /* 8bit_0 | mark | reorder | slchdr *****h264:only use SlcHdrBits[0], h265 use two*/
    UINT32 CABAC_SLCHDR_PART2_SEG[8]; /*for h265 slchead*/
    UINT32 slchdr_part1;

} VENC_HAL_STREAM_S;

typedef struct
{
    UINT32  PTS0;
    UINT32  PTS1;

    UINT32  DdrRegCfgPhyAddr;
    VIRT_ADDR DdrRegCfgVirAddr;
} VENC_HAL_EXT_S;

typedef struct
{
    UINT32 *pRegBase;

    VENC_HAL_CTRL_S CtrlCfg;

    VENC_HAL_BUF_S  BufCfg;

    VENC_HAL_RC_S   RcCfg;

    VENC_HAL_SMMU_S SmmuCfg;

    VENC_HAL_STREAM_S StreamCfg;

    //other
    VENC_HAL_EXT_S ExtCfg;
} VENC_HAL_CFG_S;

typedef struct
{
    //status
    HI_U32 VencTimeOut;
    HI_U32 VencSliceInt;
    HI_U32 VencEndOfPic;
    HI_U32 VencBufFull;
    HI_U32 VencPbitOverflow;

    //rc
    HI_U32 PicBits;
    HI_U32 MeanQP;
    HI_S32 NumIMBCurFrm;

    //stream
    HI_U32   SliceLength[16];
    HI_U32   SliceIsEnd[16];
} VENC_HAL_READ_S;

typedef struct
{
    HI_U32 TlbMissStatNs;
    HI_U32 PtwTransStatNs;
    HI_U32 TlbInvalidStatNsRd;
    HI_U32 TlbInvalidStatNsWr;
    HI_U32 TlbMissStatS;
    HI_U32 PtwTransStatS;
    HI_U32 TlbInvalidStatSRd;
    HI_U32 TlbInvalidStatSWr;

    HI_U32 FaultAddrRdNs;
    HI_U32 FaultAddrWrNs;
    HI_U32 FaultAddrRdS;
    HI_U32 FaultAddrWrS;
} VENC_HAL_READ_SMMU_S;


typedef struct hiVENC_HAL_FUN_PTR_S
{
    VOID   (*pfun_HAL_ClearInt)(INTERRUPT_TYPE_E interruptType);
    VOID   (*pfun_HAL_DisableInt)(INTERRUPT_TYPE_E interruptType);

    SINT32 (*pfun_HAL_ReadReg)(VENC_HAL_READ_S *pReadBack);
    SINT32 (*pfun_HAL_ReadSmmuReg)(VENC_HAL_READ_SMMU_S *pReadBack);
    SINT32 (*pfun_HAL_CfgReg)(VENC_HAL_CFG_S *pRegCfg);

    SINT32 (*pfun_HAL_Init)(VOID);
    VOID   (*pfun_HAL_Deinit)(VOID);

    VOID (*pfun_HAL_OpenHardware)(VOID);
    VOID (*pfun_HAL_CloseHardware)(VOID);
    VOID (*pfun_HAL_ResetHardware)(VOID);
} VENC_HAL_FUN_PTR_S;

extern VENC_HAL_FUN_PTR_S g_venc_hal_fun_ptr;

#define VENC_HAL_ClearInt(InterruptType) \
    do \
    { \
        if(NULL != g_venc_hal_fun_ptr.pfun_HAL_ClearInt)  \
        { \
            g_venc_hal_fun_ptr.pfun_HAL_ClearInt(InterruptType); \
        }  \
    }while(0)

#define VENC_HAL_DisableInt(InterruptType) \
    do \
    { \
        if(NULL != g_venc_hal_fun_ptr.pfun_HAL_DisableInt)  \
        { \
            g_venc_hal_fun_ptr.pfun_HAL_DisableInt(InterruptType); \
        }  \
    }while(0)

#define VENC_HAL_Deinit() \
    do \
    { \
        if(NULL != g_venc_hal_fun_ptr.pfun_HAL_Deinit)  \
        { \
            g_venc_hal_fun_ptr.pfun_HAL_Deinit(); \
        }  \
    }while(0)

#define VENC_HAL_Init() \
    (g_venc_hal_fun_ptr.pfun_HAL_Init? \
     g_venc_hal_fun_ptr.pfun_HAL_Init(): \
     VENC_NULL_FUN_PTR)

#define VENC_HAL_ReadReg(pReadBack) \
    (g_venc_hal_fun_ptr.pfun_HAL_ReadReg? \
     g_venc_hal_fun_ptr.pfun_HAL_ReadReg(pReadBack): \
     VENC_NULL_FUN_PTR)

#define VENC_HAL_ReadReg_Smmu(pReadBack) \
    (g_venc_hal_fun_ptr.pfun_HAL_ReadSmmuReg? \
     g_venc_hal_fun_ptr.pfun_HAL_ReadSmmuReg(pReadBack): \
     VENC_NULL_FUN_PTR)

#define VENC_HAL_CfgReg(pRegCfg) \
    (g_venc_hal_fun_ptr.pfun_HAL_CfgReg? \
     g_venc_hal_fun_ptr.pfun_HAL_CfgReg(pRegCfg): \
     VENC_NULL_FUN_PTR)

////product
#define VENC_PDT_OpenHardware() \
    do \
    { \
        if(NULL != g_venc_hal_fun_ptr.pfun_HAL_OpenHardware)  \
        { \
            g_venc_hal_fun_ptr.pfun_HAL_OpenHardware(); \
        }  \
    }while(0)

#define VENC_PDT_CloseHardware() \
    do \
    { \
        if(NULL != g_venc_hal_fun_ptr.pfun_HAL_CloseHardware)  \
        { \
            g_venc_hal_fun_ptr.pfun_HAL_CloseHardware(); \
        }  \
    }while(0)

#define VENC_PDT_ResetHardware() \
    do \
    { \
        if(NULL != g_venc_hal_fun_ptr.pfun_HAL_ResetHardware)  \
        { \
            g_venc_hal_fun_ptr.pfun_HAL_ResetHardware(); \
        }  \
    }while(0)

#ifdef __cplusplus
}
#endif

#endif  // __VENC_HAL_EXT_H__

VOID DRV_VENC_HAL_V400R004C02_ClrInt(INTERRUPT_TYPE_E interruptType);
VOID DRV_VENC_HAL_V400R004C02_DisableInt(INTERRUPT_TYPE_E interruptType);
SINT32 DRV_VENC_HAL_V400R004C02_ReadReg_Smmu(VENC_HAL_READ_SMMU_S* pReadBack);
SINT32 DRV_VENC_HAL_V400R004C02_ReadReg(VENC_HAL_READ_S *pReadBack);
SINT32 DRV_VENC_HAL_V400R004C02_CfgReg(VENC_HAL_CFG_S *pRegCfg);
SINT32 DRV_VENC_HAL_V400R004C02_Init(VOID);
VOID DRV_VENC_HAL_V400R004C02_Deinit(VOID);

VOID DRV_VENC_HAL_V500R001_ClrInt(INTERRUPT_TYPE_E interruptType);
VOID DRV_VENC_HAL_V500R001_DisableInt(INTERRUPT_TYPE_E interruptType);
SINT32 DRV_VENC_HAL_V500R001_ReadReg_Smmu(VENC_HAL_READ_SMMU_S* pReadBack);
SINT32 DRV_VENC_HAL_V500R001_ReadReg(VENC_HAL_READ_S *pReadBack);
SINT32 DRV_VENC_HAL_V500R001_CfgReg(VENC_HAL_CFG_S *pRegCfg);
SINT32 DRV_VENC_HAL_V500R001_Init(VOID);
VOID DRV_VENC_HAL_V500R001_Deinit(VOID);


