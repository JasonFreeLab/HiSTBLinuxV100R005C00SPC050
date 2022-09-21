#ifndef __VPSS_CBB_INFO_H__
#define __VPSS_CBB_INFO_H__

#include "vpss_cbb_common.h"
//#include "vpss_stt_reg.h"

#if 0
typedef struct
{
    HI_U32 u32VirAddr;
    HI_U32 u32VirAddr;
    HI_U32 u32VirAddr;
    HI_U32 u32VirAddr;
} CBB_INFO_ADDR;

typedef struct
{
    CBB_INFO_ADDR stPrjH[3];
    CBB_INFO_ADDR stPrjV[3];
    HI_U32 u32Stride;
    HI_BOOL bMMU;
    HI_BOOL bSecure;
} CBB_INFO_PRJ;
#endif

typedef struct
{
    HI_U32 u32WPhyAddr;
    HI_U8 *pu8WVirAddr;
    HI_U32 u32RPhyAddr;
    HI_U8 *pu8RVirAddr;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32ByteSize;
    HI_U32 u32Stride;
    HI_BOOL bSmmu_R;            //µ◊≤?∏˘æ?mmu±Í÷æ …Ë÷?Õ®µ¿µƒmmu bypass Ù?‘
    HI_BOOL bSmmu_W;
    HI_BOOL bSecure;

} CBB_INFO_S;

typedef struct
{
    //HI_U32        u32Tnr_cfg_addr;
    //HI_U32        u32Tnr_clut_addr;
    CBB_INFO_S stBaseInfo;
} CBB_INFO_TNR_S;

typedef struct
{
    //HI_U32        u32Snr_cfg_addr;
    CBB_INFO_S stBaseInfo;
} CBB_INFO_SNR_S;


typedef struct
{
    HI_U32 u32CurReadAddr;  //Cur∂¡µÿ÷∑
    HI_U32 u32Nx2WriteAddr; //Nx2–¥µÿ÷∑
    HI_U8 *pu8CurReadAddr;  //Cur∂¡µÿ÷∑
    HI_U8 *pu8Nx2WriteAddr; //Nx2–¥µÿ÷∑
    HI_U32 u32Stride;       //‘À∂Ø÷∏ ˝––º‰æ‡
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Nx2;
    HI_BOOL bSecure;
} CBB_INFO_PRJV_S;

typedef struct
{
    HI_U32 u32CurReadAddr;  //Cur∂¡µÿ÷∑
    HI_U32 u32Nx2WriteAddr; //Nx2–¥µÿ÷∑
    HI_U8 *pu8CurReadAddr;  //Cur∂¡µÿ÷∑
    HI_U8 *pu8Nx2WriteAddr; //Nx2–¥µÿ÷∑
    HI_U32 u32Stride;       //‘À∂Ø÷∏ ˝––º‰æ‡
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Nx2;
    HI_BOOL bSecure;
} CBB_INFO_PRJH_S;

typedef struct
{
    HI_U32 u32RefReadAddr;      //Ref∂¡µÿ÷∑
    HI_U32 u32CurReadAddr;      //Cur∂¡µÿ÷∑
    HI_U32 u32Nx1WriteAddr;      //Nx1–¥µÿ÷∑
    HI_U8 *pu8CurReadAddr;  //Cur∂¡µÿ÷∑
    HI_U8 *pu8RefReadAddr;  //Nx1∂¡µÿ÷∑
    HI_U8 *pu8Nx1WriteAddr; //Nx2–¥µÿ÷∑
    HI_U32 u32Stride;       //‘À∂Ø÷∏ ˝––º‰æ‡
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Ref;
    HI_BOOL bSmmu_Nx1;
    HI_BOOL bSecure;
} CBB_INFO_BLKMV_S;

typedef struct
{
    HI_U32 u32CurReadAddr;  //Cur∂¡µÿ÷∑
    HI_U32 u32Nx1ReadAddr;  //Nx1∂¡µÿ÷∑
    HI_U32 u32Nx2WriteAddr; //Nx2–¥µÿ÷∑
    HI_U8 *pu8CurReadAddr;  //Cur∂¡µÿ÷∑
    HI_U8 *pu8Nx1ReadAddr;  //Nx1∂¡µÿ÷∑
    HI_U8 *pu8Nx2WriteAddr; //Nx2–¥µÿ÷∑
    HI_U32 u32Stride;       //‘À∂Ø÷∏ ˝––º‰æ‡
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Nx2;
    HI_BOOL bSmmu_Nx1;
    HI_BOOL bSecure;
} CBB_INFO_RGMV_S;

typedef struct
{
    HI_U32 u32CurWriteAddr;  //Cur∂¡µÿ÷∑
    HI_U32 u32RefReadAddr;  //ref∂¡µÿ÷∑

    HI_U8 *pu8CurWriteAddr;  //Cur∂¡µÿ÷∑
    HI_U8 *pu8RefReadAddr;  //Ref∂¡µÿ÷∑

    HI_U32 u32Stride;       //‘À∂Ø÷∏ ˝––º‰æ‡
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Ref;
    HI_BOOL bSecure;
} CBB_INFO_BLKMT_S;

#if 0
typedef struct
{
    HI_U32 u32CurAddr;  //Cur∂¡µÿ÷∑
    HI_U32 u32Nx1Addr;  //Nx1∂¡µÿ÷∑
    HI_U32 u32Nx2Addr; //Nx2–¥µÿ÷∑
    HI_U32 u32Stride;       //‘À∂Ø÷∏ ˝––º‰æ‡
    HI_BOOL bSmmu;
    HI_BOOL bSecure;
} CBB_INFO_TNRRGMV_S;
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern HI_VOID VPSS_InfoCfg_Blkmv(CBB_INFO_BLKMV_S *pstInfoBlkmvCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Blkmt(CBB_INFO_BLKMT_S *pstInfoBlkmtCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Dei_ST(CBB_INFO_S *pstInfoDeiCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Prjh(CBB_INFO_PRJH_S *pstInfoPrjhCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Prjv(CBB_INFO_PRJV_S *pstInfoPrjvCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Rgmv(CBB_INFO_RGMV_S *pstInfoRgmvCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Snr_Mad(CBB_INFO_S *pstInfoSnrCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_INFOCfg_SttInfo(CBB_INFO_S *pstInfoStt, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Tnr_Mad(CBB_INFO_S *pstInfoTnrCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoGet_All(S_STT_REGS_TYPE *pstSttReg, CBB_INFO_S *pstInfoStt);
extern HI_VOID VPSS_InfoCfg_Di_CNT(CBB_INFO_S *pstInfoDiCntCfg, CBB_REG_ADDR_S stRegAddr);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif
