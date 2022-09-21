/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : drv_pq_ext_csc.h
  Version       : Initial Draft
  Author        : sdk sdk
  Created       : 2014/04/01
  Description   :

******************************************************************************/

#ifndef __DRV_PQ_EXT_CSC_V4_H__
#define __DRV_PQ_EXT_CSC_V4_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* color space convert type */
typedef enum hiPQ_CSC_MODE_E
{
    HI_PQ_CSC_YUV2RGB_601 = 0      , /* YUV_601 L  -> RGB        */
    HI_PQ_CSC_YUV2RGB_709          , /* YUV_709 L  -> RGB        */
    HI_PQ_CSC_RGB2YUV_601          , /* RGB        -> YUV_601 L  */
    HI_PQ_CSC_RGB2YUV_709          , /* RGB        -> YUV_709 L  */
    HI_PQ_CSC_YUV2YUV_709_601      , /* YUV_709 L  -> YUV_601 L  */
    HI_PQ_CSC_YUV2YUV_601_709      , /* YUV_601 L  -> YUV_709 L  */
    HI_PQ_CSC_YUV2YUV              , /* YUV L      -> YUV L      */

    HI_PQ_CSC_RGB2RGB_709_2020     , /* RGB_709    -> RGB_2020   */
    HI_PQ_CSC_RGB2YUV_2020_2020_L  , /* RGB_2020   -> YUV_2020 L */
    HI_PQ_CSC_RGB2RGB_2020_709     , /* RGB_2020   -> RGB_709    */
    HI_PQ_CSC_RGB2YUV_2020_709_L   , /* RGB_2020   -> YUV_601 L  */

    HI_PQ_CSC_RGB2RGB_601_2020     , /* RGB_601    -> RGB_2020   */
    HI_PQ_CSC_RGB2RGB_2020_601     , /* RGB_2020   -> RGB_601    */
    HI_PQ_CSC_RGB2YUV_2020_601_L   , /* RGB_2020     -> YCbCr_601 L */

    HI_PQ_CSC_YUV2YUV_709_2020_L_L , /* YUV_709 L  -> YUV_2020 L */
    HI_PQ_CSC_YUV2RGB_709_2020_L   , /* YUV_709 L  -> RGB_2020   */

    HI_PQ_CSC_YUV2YUV_601_2020_L_L , /* YUV_601 L  -> YUV_2020 L */
    HI_PQ_CSC_YUV2RGB_601_2020_L   , /* YUV_601 L  -> RGB_2020   */

    HI_PQ_CSC_YUV2YUV_2020_2020_L_L, /* YUV_2020 L -> YUV_2020 L */
    HI_PQ_CSC_YUV2YUV_2020_709_L_L , /* YUV_2020 L -> YUV_709 L  */
    HI_PQ_CSC_YUV2YUV_2020_601_L_L , /* YUV_2020 L -> YUV_601 L  */
    HI_PQ_CSC_YUV2RGB_2020_2020_L  , /* YUV_2020 L -> RGB_2020   */
    HI_PQ_CSC_YUV2RGB_2020_709_L   , /* YUV_2020 L -> RGB_709    */
    HI_PQ_CSC_YUV2RGB_2020_601_L   , /* YUV_2020 L -> RGB_601    */

    HI_PQ_CSC_YUV2RGB_601_FULL     , /* YUV_601 F  -> RGB        */
    HI_PQ_CSC_YUV2RGB_709_FULL     , /* YUV_709 F  -> RGB        */
    HI_PQ_CSC_RGB2YUV_601_FULL     , /* RGB        -> YUV_601 F  */
    HI_PQ_CSC_RGB2YUV_709_FULL     , /* RGB        -> YUV_709 F  */
    HI_PQ_CSC_RGB2RGB              , /* RGB        -> RGB        */

    HI_PQ_CSC_BUTT
} HI_PQ_CSC_MODE_E;


/* CSC Tuning Or No Tuning; limit: There is only one Csc needing tuning at every layer */
typedef enum hiPQ_CSC_TYPE_E
{
    HI_PQ_CSC_TUNING_V0 = 0  , /* Tuning Csc; need tune bright etc. */
    HI_PQ_CSC_TUNING_V1      ,
    HI_PQ_CSC_TUNING_V2      ,
    HI_PQ_CSC_TUNING_V3      ,
    HI_PQ_CSC_TUNING_V4      ,
    HI_PQ_CSC_TUNING_GP0     ,
    HI_PQ_CSC_TUNING_GP1     ,
    HI_PQ_CSC_NORMAL_SETTING , /* Normal Csc; only need Coef */

    HI_PQ_CSC_TYPE_BUUT
} HI_PQ_CSC_TYPE_E;

/* CSC Tuning Or No Tuning */
typedef struct hiPQ_CSC_CTRL_S
{
    HI_BOOL           bCSCEn;     /* Current Csc Enable: 1:Open; 0:Close */
    HI_U32            u32CscPre;  /* Current Csc Pecision: 10~15 */
    HI_PQ_CSC_TYPE_E  enCscType;  /* Current Csc Type: Normal or Setting */

} HI_PQ_CSC_CRTL_S;

/* VDP CSC  Ù–‘ */
typedef struct  hiPQ_VDP_CSC_S
{
    HI_BOOL           bCSCEn;
    HI_PQ_CSC_MODE_E  enCscMode;
} HI_PQ_VDP_CSC_S;




/* CSC matrix coefficient */
typedef struct  hiPQ_CSC_COEF_S
{
    HI_S32 csc_coef00;
    HI_S32 csc_coef01;
    HI_S32 csc_coef02;

    HI_S32 csc_coef10;
    HI_S32 csc_coef11;
    HI_S32 csc_coef12;

    HI_S32 csc_coef20;
    HI_S32 csc_coef21;
    HI_S32 csc_coef22;
} HI_PQ_CSC_COEF_S;

/* CSC DC component */
typedef struct  hiPQ_CSC_DCCOEF_S
{
    HI_S32 csc_in_dc0;
    HI_S32 csc_in_dc1;
    HI_S32 csc_in_dc2;

    HI_S32 csc_out_dc0;
    HI_S32 csc_out_dc1;
    HI_S32 csc_out_dc2;
} HI_PQ_CSC_DCCOEF_S;


typedef enum hiPQ_GFX_COLOR_SPACE_E
{
    PQ_GFX_CS_UNKNOWN = 0,

    PQ_GFX_CS_BT601_YUV_LIMITED,  /* BT.601 */
    PQ_GFX_CS_BT601_YUV_FULL,
    PQ_GFX_CS_BT601_RGB_LIMITED,
    PQ_GFX_CS_BT601_RGB_FULL,

    PQ_GFX_CS_BT709_YUV_LIMITED,  /* BT.709 */
    PQ_GFX_CS_BT709_YUV_FULL,
    PQ_GFX_CS_BT709_RGB_LIMITED,
    PQ_GFX_CS_BT709_RGB_FULL,

    PQ_GFX_CS_BT2020_YUV_LIMITED, /* BT.2020 */
    PQ_GFX_CS_BT2020_RGB_FULL,

    PQ_GFX_CS_BUTT
} HI_PQ_GFX_COLOR_SPACE_E;

typedef struct hiPQ_GFX_CSC_MODE_S
{
    HI_PQ_GFX_COLOR_SPACE_E eInputCS;  /* input  color space type, should be set carefully according to the application situation. */
    HI_PQ_GFX_COLOR_SPACE_E eOutputCS; /* output color space type, should be set carefully according to the application situation. */

} HI_PQ_GFX_CSC_MODE_S;

typedef struct hiPQ_GFX_CSC_PARA_S
{
    HI_BOOL                bIsBGRIn;  /* Is BGR in */
    HI_PQ_GFX_CSC_MODE_S   sGfxCscMode;

} HI_PQ_GFX_CSC_PARA_S;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_PQ_EXT_CSC_H__ */
