/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

 File Name    : pq_hal_vdp4ksnr.h
 Version        : Initial Draft
 Author         : sdk
 Created       : 2017/04/14
 Description   :
******************************************************************************/
#ifndef __PQ_HAL_VDP4KSNR_H__
#define __PQ_HAL_VDP4KSNR_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


typedef enum
{
    VDP4KSNR_DEMO_ENABLE_L = 0,
    VDP4KSNR_DEMO_ENABLE_R
} VDP4KSNR_DEMO_MODE_E;

typedef struct  hiPQ_HAL_VDP4KSNR_MEAN_RATIO_S
{
    HI_S32 s32MappingMax;    /*meanedgeratio max映射表最大值 0~127 */
    HI_S32 s32MappingMin;    /*meanedgeratio min映射表最小值 0~127 */
    HI_S32 s32MappingX[6];   /*meanedgeratio X*/
    HI_S32 s32MappingY[5];   /*meanedgeratio Y*/
    HI_S32 s32MappingK[4];   /*meanedgeratio K*/

} PQ_HAL_VDP4KSNR_MEAN_RATIO_S;

typedef struct  hiPQ_HAL_VDP4KSNR_EDGE_STR_S
{
    HI_S32 s32MappingMax;    /*edgestrmapping max映射表最大值 0~63*/
    HI_S32 s32MappingMin;    /*edgestrmapping min映射表最小值 0~63*/
    HI_S32 s32MappingX[8];   /*edgestrmapping X*/
    HI_S32 s32MappingY[7];   /*edgestrmapping Y*/
    HI_S32 s32MappingK[6];   /*edgestrmapping K*/

} PQ_HAL_VDP4KSNR_EDGE_STR_S;


/*SNR*/
HI_S32 PQ_HAL_SetVdp4KSnrParaUpd (HI_U32 u32Data);
HI_S32 PQ_HAL_SetVdp4KSnrEnable(HI_U32 u32Data, HI_U32 u32Data1);
//HI_S32 PQ_HAL_InitVdp4KSnr(HI_VOID);

HI_S32 PQ_HAL_SetVdp4KSnrMotionEdgeLut (HI_U32 u32Data, HI_U32 u32Width);
HI_S32 PQ_HAL_SetVdp4KSnrEnable(HI_U32 u32Data, HI_BOOL bEnable);
HI_S32 PQ_HAL_SetVdp4KSnrstrength(HI_U32 u32Data, HI_U32 snrstrength);
HI_S32 PQ_HAL_SetVdp4KSnrDemomodeen(HI_U32 u32Data, HI_BOOL bDemoEn);
HI_S32 PQ_HAL_SetVdp4KSnrDemomodelr(HI_U32 u32Data, HI_U32 demomodelr);
HI_S32 PQ_HAL_SetVdp4KSnrDemoModeCoor(HI_U32 u32Data, HI_U32 u32XPos);
HI_S32 PQ_HAL_SetVdp4KSnrMeanRatio(HI_U32 u32Data, PQ_HAL_VDP4KSNR_MEAN_RATIO_S *pstMeanRatio);
HI_S32 PQ_HAL_GetVdp4KSnrMeanRatio(HI_U32 u32Data, PQ_HAL_VDP4KSNR_MEAN_RATIO_S *pstMeanRatio);
HI_S32 PQ_HAL_SetVdp4KSnrEdgeStr(HI_U32 u32Data, PQ_HAL_VDP4KSNR_EDGE_STR_S *pstEdgeStr);
HI_S32 PQ_HAL_GetVdp4KSnrEdgeStr(HI_U32 u32Data, PQ_HAL_VDP4KSNR_EDGE_STR_S *pstEdgeStr);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

