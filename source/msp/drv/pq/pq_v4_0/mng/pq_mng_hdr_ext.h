/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_hdr_ext.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/06/13
  Description  :

******************************************************************************/
#ifndef __PQ_MNG_HDR_EXT_H__
#define __PQ_MNG_HDR_EXT_H__

#include "hi_drv_video.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)

#define PQ_DEGMM_SEG_SIZE       4
#define PQ_TMAP_SEG_SIZE        8
#define PQ_SMAP_SEG_SIZE        8
#define PQ_GMM_SEG_SIZE         8
#define PQ_DEGMM_LUT_SIZE      64
#define PQ_TMAP_LUT_SIZE       64
#define PQ_SMAP_LUT_SIZE       64
#define PQ_GMM_LUT_SIZE        64

#elif  defined(CHIP_TYPE_hi3798mv200_a)

#define PQ_DEGMM_SEG_SIZE       4
#define PQ_TMAP_SEG_SIZE        8
#define PQ_SMAP_SEG_SIZE        8
#define PQ_GMM_SEG_SIZE         8
#define PQ_DEGMM_LUT_SIZE      64
#define PQ_TMAP_LUT_SIZE       64
#define PQ_SMAP_LUT_SIZE       64
#define PQ_GMM_LUT_SIZE        64


#elif  defined(CHIP_TYPE_hi3796mv200)

#define PQ_DEGMM_SEG_SIZE       8
#define PQ_TMAP_SEG_SIZE        8
#define PQ_SMAP_SEG_SIZE        8
#define PQ_GMM_SEG_SIZE         8
#define PQ_DEGMM_LUT_SIZE      64
#define PQ_TMAP_LUT_SIZE       64
#define PQ_SMAP_LUT_SIZE       64
#define PQ_GMM_LUT_SIZE        64

#else

#define PQ_DEGMM_SEG_SIZE       8
#define PQ_TMAP_SEG_SIZE        8
#define PQ_SMAP_SEG_SIZE        8
#define PQ_GMM_SEG_SIZE         8
#define PQ_DEGMM_LUT_SIZE      64
#define PQ_TMAP_LUT_SIZE       64
#define PQ_SMAP_LUT_SIZE       64
#define PQ_GMM_LUT_SIZE        64
#endif

typedef enum hiPQ_DISP_OUT_TYPE_E
{
    HI_PQ_DISP_TYPE_NORMAL = 0,    /* ÆÕÍ¨ÐÅºÅÏÔÊ¾ BT601 BT709*/
    HI_PQ_DISP_TYPE_HDR10  = 1,    /* ±ê×¼HDRÐÅºÅÏÔÊ¾ */
    HI_PQ_DISP_TYPE_HLG    = 2,    /* ±ê×¼HLGÐÅºÅÏÔÊ¾ */

    HI_PQ_DISP_TYPE_BUTT
} HI_PQ_DISP_OUT_TYPE_E;

typedef enum hiPQ_HDR_MODE_E
{
    HI_PQ_HDR_MODE_HDR10_TO_SDR   = 0,
    HI_PQ_HDR_MODE_HDR10_TO_HDR10 = 1,
    HI_PQ_HDR_MODE_HDR10_TO_HLG   = 2,
    HI_PQ_HDR_MODE_HLG_TO_SDR     = 3,
    HI_PQ_HDR_MODE_HLG_TO_HDR10   = 4,
    HI_PQ_HDR_MODE_HLG_TO_HLG     = 5,
    HI_PQ_HDR_MODE_SLF_TO_SDR     = 6,
    HI_PQ_HDR_MODE_SLF_TO_HDR10   = 7,
    HI_PQ_HDR_MODE_SDR_TO_HDR10   = 8,
    HI_PQ_HDR_MODE_SDR_TO_SDR     = 9,
    HI_PQ_HDR_MODE_SDR_TO_HLG     = 10,

    HI_PQ_HDR_MODE_BUTT,
} HI_PQ_HDR_MODE_E;


typedef enum hiPQ_HDR_COLOR_PRIMARIES_E
{
    HI_PQ_HDR_COLOR_PRIMARIES_BT601_L = 0x0,
    HI_PQ_HDR_COLOR_PRIMARIES_BT601_F,
    HI_PQ_HDR_COLOR_PRIMARIES_BT709_L,
    HI_PQ_HDR_COLOR_PRIMARIES_BT709_F,
    HI_PQ_HDR_COLOR_PRIMARIES_BT2020_L,
    HI_PQ_HDR_COLOR_PRIMARIES_BT2020_F,
    HI_PQ_HDR_COLOR_PRIMARIES_UNKNOW,

    HI_PQ_HDR_COLOR_PRIMARIES_BUTT
} HI_PQ_HDR_COLOR_PRIMARIES_E;


typedef struct hiPQ_WIN_HDR_INFO_S
{
    HI_DRV_VIDEO_FRAME_TYPE_E           enSrcFrameType;
    HI_DRV_VIDEO_STD_E                  enCodecType;
    union
    {
        HI_DRV_VIDEO_DOLBY_INFO_S       stDolbyInfo;        /*Dolby frame info.*/
        HI_DRV_VIDEO_HDR10_INFO_S       stHDR10Info;        /*HDR10 frame info.*/
        HI_DRV_VIDEO_HLG_INFO_S         stHLGInfo;          /*HLG frame info.*/
        HI_DRV_VIDEO_SLF_INFO_S         stSLFInfo;          /*SLF frame info.*/
        HI_DRV_VIDEO_TECHNICOLOR_INFO_S stTechnicolorInfo;  /*Technicolor frame info.*/
    } unHDRInfo;

    HI_PQ_DISP_OUT_TYPE_E               enDispType;         /* SDR/HDR10/... */
    /* add for 96 */
    HI_DRV_COLOUR_DESCRIPTION_INFO_S    stInColourInfo;     /* input color */
    HI_PQ_HDR_COLOR_PRIMARIES_E         enOutColorSpace;    /* output color */
    HI_DRV_COLOR_SPACE_E                enInCS;             /* input color */
    HI_DRV_COLOR_SPACE_E                enOutCS;            /* output color */
} HI_PQ_WIN_HDR_INFO;

#if 1
typedef enum hiPQ_HDR_CSC_GAMUT_S
{
    HI_PQ_HDR_CSC_GAMUT_BT2020 = 0,
    HI_PQ_HDR_CSC_GAMUT_BT709  = 1,
    HI_PQ_HDR_CSC_GAMUT_BT601  = 2,

    HI_PQ_HDR_CSC_GAMUT_BUTT
} HI_PQ_HDR_CSC_GAMUT_S;

typedef enum hiPQ_HDR_CSC_SPACE_S
{
    HI_PQ_HDR_CSC_SPACE_YUV = 0,
    HI_PQ_HDR_CSC_SPACE_RGB = 1,

    HI_PQ_HDR_CSC_SPACE_BUTT
} HI_PQ_HDR_CSC_SPACE_S;

typedef struct hiPQ_HDR_CSC_MODE_S
{
    HI_PQ_HDR_CSC_GAMUT_S  enCscGamut;    /* 2020/709/601 */
    HI_PQ_HDR_CSC_SPACE_S  enCscSpace;    /* yuv/rgb */
    HI_BOOL                bCscLimited;   /* limited range , full range */
} HI_PQ_HDR_CSC_MODE_S;
#endif

typedef struct hiPQ_HDR_TM_PARAM_S
{
    HI_U32    u32SrcMinLum ;       // Src Min Luminance Value : nits        x1 = 0.005*10000;       //METADATE
    HI_U32    u32SrcAvgLum ;       // Src Avg Luminance Value : nits     x2 = 15*10000;              //ÐéÄâ¼Ä´æÆ÷
    HI_U32    u32SrcMaxLum ;      // Src Max Luminance Value : nits    x3 = 1200*10000;           //METADATE
    HI_U32    u32TargMinLum ;       // Target min Luminance Value : nits  y1 = 0.1*10000;          //ÐéÄâ¼Ä´æÆ÷
    HI_U32    u32TargAvgLum;       // Target Avg Luminance Value : nits   y2 = 200*10000;        //ÐéÄâ¼Ä´æÆ÷
    HI_U32    u32TargMaxLum ;      // Target Max Luminance Value : nits     y3 = 300*10000;        //ÐéÄâ¼Ä´æÆ÷
    HI_U32    u32Contrast  ;     //µ÷½Ú¶Ô±È¶È             n = 1.25*256;             //ÐéÄâ¼Ä´æÆ÷
    HI_U32    u32LwAvg    ;  // Ô´¾ùÖµÁÁ¶È //TM_EXP                                   //ÐéÄâ¼Ä´æÆ÷
} HDR_TM_PARAM_S;

typedef struct hiPQ_HDR_TMExpPARAM_S
{
    HI_U32  u32QBbitX  ;
    HI_U32  u32QBbitY  ;
    HI_U32  u32LwAvg  ;
    HI_U32  u32Acoef  ;
    HI_U32  u32Log2exp ;
    HI_U32  u32QBbitSclCoef  ;
} HDR_TMExpPARAM_S;

typedef struct hiDM_INFO_S
{
    HI_U32 u32SrcMaxPQ;   //Ô´µÄ
    HI_U32 u32SrcMinPQ;
} DM_INFO_S;

typedef enum hiPQ_HDR_EOTF_E
{
    HI_PQ_HDR_EOTF_1886 = 0x0,
    HI_PQ_HDR_EOTF_2084 ,
    HI_PQ_HDR_EOTF_HLG ,
    HI_PQ_HDR_EOTF_SLF ,

    HI_PQ_HDR_EOTF_BUTT
} HI_PQ_HDR_EOTF_E;

typedef enum hiPQ_HDR_MATRIX_COEFF_E
{
    HI_PQ_HDR_MATRIX_COEFF_BT601_L = 0x0,
    HI_PQ_HDR_MATRIX_COEFF_BT601_F,
    HI_PQ_HDR_MATRIX_COEFF_BT709_L,
    HI_PQ_HDR_MATRIX_COEFF_BT709_F,
    HI_PQ_HDR_MATRIX_COEFF_BT2020_NCL,
    HI_PQ_HDR_MATRIX_COEFF_BT2020_CL,
    HI_PQ_HDR_MATRIX_COEFF_UNKNOW,

    HI_PQ_HDR_MATRIX_COEFF_BT2020_BUTT

} HI_PQ_HDR_MATRIX_COEFF_E;

typedef struct hiPQ_HDR_UNIFIED_METADATA_IN_S
{
    HI_DRV_VIDEO_FRAME_TYPE_E        enSrcFrameType;
    HI_DRV_COLOUR_DESCRIPTION_INFO_S stColorDescriptionInfo;
    HI_U8 u8TransferCharacteristics;

    HI_BOOL  bMasteringAvailable;
    HI_BOOL  bContentAvailable;
    HI_DRV_MASTERING_DISPLAY_COLOUR_VOLUME_S stMasteringInfo;
    HI_DRV_CONTENT_LIGHT_LEVEL_INFO_S        stContentInfo;
} HI_PQ_HDR_UNIFIED_METADATA_IN_S;

typedef struct hiPQ_HDR_UNIFIED_METADATA_OUT_S
{
    HI_DRV_VIDEO_FRAME_TYPE_E enSrcFrameType;
    //HI_PQ_HDR_COLOR_PRIMARIES_E enColorSpace;

    HI_DRV_COLOR_SPACE_E      enOutCS;  /* output color */

    HI_PQ_HDR_EOTF_E          enEotfType;
    HI_PQ_HDR_MATRIX_COEFF_E  enMatrixType;

    HI_BOOL  bMasteringAvailable;
    HI_BOOL  bContentAvailable;
    HI_DRV_MASTERING_DISPLAY_COLOUR_VOLUME_S stMasteringInfo;
    HI_DRV_CONTENT_LIGHT_LEVEL_INFO_S        stContentInfo;
} HI_PQ_HDR_UNIFIED_METADATA_OUT_S;

#if defined(CHIP_TYPE_hi3798cv200)

#define HI_PQ_HDR_TM_LUT_SIZE 512

typedef struct HiPQ_HDR_TM
{
    /*ToneMapping*/
    HI_S16 s16aTMLutI[HI_PQ_HDR_TM_LUT_SIZE];
    HI_S16 s16aTMLutS[HI_PQ_HDR_TM_LUT_SIZE];
    HI_S16 s16aSMLutI[HI_PQ_HDR_TM_LUT_SIZE];
    HI_S16 s16aSMLutS[HI_PQ_HDR_TM_LUT_SIZE];
} HI_PQ_HDR_TM;

typedef struct HiPQ_HDR_CFG
{
    HI_PQ_HDR_TM stPQHdrTm;
} HI_PQ_HDR_CFG;

#else

typedef struct hiPQ_HDR_Y2R
{
    HI_U16 u16ScaleY2R;                     /* U4.0  [0,15] */
    HI_S16 as16M33Y2R[3][3];                /* S2.13 [-2^15, 2^15-1] = [-32768, 32767] */
    HI_S16 as16DcInY2R[3];                  /* S10.0  [-1024, 1023] */
    HI_S16 as16DcOutY2R[3];                 /* S12.0  [-4096, 4095] */
    HI_U16 u16ClipMinY2R ;                  /* U12.0  [0,4095]  */
    HI_U16 u16ClipMaxY2R ;                  /* U12.0  [0,4095]  */
} PQ_HDR_Y2R;

typedef struct hiPQ_HDR_DEGMM
{
    HI_U32  au32Step[PQ_DEGMM_SEG_SIZE];    /* U4.0  [0,15] */
    HI_U32  au32Pos[PQ_DEGMM_SEG_SIZE];     /* U12.0  [0,4095] */
    HI_U32  au32Num[PQ_DEGMM_SEG_SIZE];     /* U6.0  [0,63] */
    HI_U32  pu32LUT[PQ_DEGMM_LUT_SIZE] ;    /* U21.0 [0,2097151]   Size:PQ_DEGMM_LUT_SIZE */
} PQ_HDR_DEGMM;

typedef struct hiPQ_HDR_TMAP
{
    HI_U16 u16ScaleLumaCal ;                /* U4.0  [0,15]*/
    HI_U16 au16M3LumaCal[3] ;               /* U1.15 [0, 65535]*/
    HI_U32 u32ClipMinTM ;                   /* U21.0 [0,2097151]*/
    HI_U32 u32ClipMaxTM ;                   /* U21.0 [0,2097151]*/
    HI_S32 as32TMOff[3] ;                   /* S21.0 [-2097151,2097151]*/

    HI_U16  u16ScaleCoefTM ;                /* U4.0  [0,15]*/
    HI_U32  au32StepTM[PQ_TMAP_SEG_SIZE];   /* U5.0  [0,21]*/
    HI_U32  au32PosTM[PQ_TMAP_SEG_SIZE];    /* U21.0 [0,2097151]*/
    HI_U32  au32NumTM[PQ_TMAP_SEG_SIZE];    /* U6.0  [0,63]*/
    HI_U32  pu32LUTTM[PQ_TMAP_LUT_SIZE];    /* U16.0 [0,65535]   Size:PQ_TMAP_LUT_SIZE*/

    HI_U16  u16ScaleCoefSM ;                /* U4.0  [0,15]*/
    HI_U32  u32StepSM[PQ_SMAP_SEG_SIZE];    /* U5.0  [0,21]*/
    HI_U32  u32PosSM[PQ_SMAP_SEG_SIZE];     /* U21.0 [0,2097151]*/
    HI_U32  u32NumSM[PQ_SMAP_SEG_SIZE];     /* U6.0  [0,63]*/
    HI_U32  pu32LUTSM[PQ_SMAP_LUT_SIZE];     /* U16.0 [0,65535]   Size:PQ_SMAP_LUT_SIZE*/
} PQ_HDR_TMAP;

typedef struct hiPQ_HDR_GMAP
{
    HI_U16 u16ScaleGMAP;                    /* U4.0  [0,15] */
    HI_S16 as16M33GMAP[3][3];               /* S1.14 [-2^15, 2^15-1] = [-32768, 32767]  */
    HI_U32 u32ClipMinGMAP;                  /* U21.0 [0,2097151] */
    HI_U32 u32ClipMaxGMAP;                  /*  U21.0 [0,2097151] */
    HI_S32 as32DcInGMAP[3];                 /*  S21.0 [-2097152,2097151] */
    HI_S32 as32DcOutGMAP[3];                /*  S21.0 [-2097152,2097151] */
} PQ_HDR_GMAP;

typedef struct hiPQ_HDR_GMM
{
    HI_U32  au32Step[PQ_GMM_SEG_SIZE];      /* U5.0  [0,21] */
    HI_U32  au32Pos[PQ_GMM_SEG_SIZE];       /* U21.0 [0,2097151] */
    HI_U32  au32Num[PQ_GMM_SEG_SIZE];       /* U6.0  [0,63] */
    HI_U32  pu32LUT[PQ_GMM_LUT_SIZE] ;      /* U12.0 [0,4095]   Size:PQ_GMM_LUT_SIZE */
} PQ_HDR_GMM;

typedef struct hiPQ_HDR_R2Y
{
    HI_U16 u16ScaleR2Y ;                     /*U4.0  [0,15] */
    HI_S16 as16M33R2Y[3][3];                 /* S1.14 [-32768, 32767] */
    HI_S16 as16DcInR2Y[3] ;                  /* S10.0  [-1024, 1023] */
    HI_S16 as16DcOutR2Y[3] ;                 /* S10.0  [-1024,1023] */
    HI_U16 u16ClipMinR2Y_Y ;                 /* U10.0  [0,1023] */
    HI_U16 u16ClipMaxR2Y_Y ;                 /* U10.0  [0,1023] */
    HI_U16 u16ClipMinR2Y_UV ;                /* U10.0  [0,1023] */
    HI_U16 u16ClipMaxR2Y_UV ;                /* U10.0  [0,1023] */
} PQ_HDR_R2Y;

#if defined(CHIP_TYPE_hi3798mv200)||defined(CHIP_TYPE_hi3798mv300)||defined(CHIP_TYPE_hi3798mv200_a)

typedef struct hiPQ_HDR_CFG
{
    /**** Enable  ****/
    HI_BOOL bY2REn          ;         /*YUV2RGB enable*/
    HI_BOOL bDegammaEn      ;         /*DeGamma enable*/
    HI_BOOL bTMapEn         ;         /*ToneMapping enable*/
    HI_BOOL bGMapEn         ;         /*GamutMapping enable*/
    HI_BOOL bGammaEn        ;         /*Gamma enable*/
    HI_BOOL bDitherEn       ;         /*Dither enable*/
    HI_BOOL bR2YEn          ;         /*RGB2YUV enable*/
    HI_BOOL bChromaAdjEn    ;         /*ChromaAdjust enable*/
    HI_BOOL bBT2020CL       ;         /* 1£ºBT2020CL£» 0£ºBT2020NCL */
    HI_BOOL vdm_v0_gamma_en ;         /* 96add vdm bypass or not */
    HI_BOOL vdm_v1_gamma_en ;         /* 96add vdm bypass or not */

    /**** Mode Sel ****/
    HI_BOOL bGMapPosSel     ;         /* 1: GMAP after TMAP;   0: GMAP before TMAP */
    HI_BOOL bDitherMode     ;         /* 1: Dither; 0: Round */

    /***** Coef *****/
    PQ_HDR_Y2R   stY2R      ;         /* YUV2RGB */
    PQ_HDR_DEGMM stDeGmm    ;         /* DeGamma */
    PQ_HDR_TMAP  stTMAP     ;         /* ToneMapping */
    PQ_HDR_GMAP  stGMAP     ;         /* GamutMapping */
    PQ_HDR_GMM   stGmm      ;         /* Gamma */
    PQ_HDR_R2Y   stR2Y      ;         /* RGB2YUV */
} HI_PQ_HDR_CFG;

#elif defined(CHIP_TYPE_hi3796mv200)

typedef struct hiPQ_HDR_CADJ
{
    HI_U16 u16Scale2P ;

} PQ_HDR_CADJ;


typedef struct hiPQ_HDR_CFG
{
    /**** Enable  ****/
    HI_BOOL bY2REn          ;         /*YUV2RGB enable*/
    HI_BOOL bV0Y2REn        ;         /*YUV2RGB enable*/
    HI_BOOL bV1Y2REn        ;         /*YUV2RGB enable*/ //96add

    HI_BOOL vdm_v0_gamma_en ;         /* 96add vdm bypass or not */
    HI_BOOL vdm_v1_gamma_en ;         /* 96add vdm bypass or not */

    HI_BOOL bDegammaEn      ;         /*DeGamma enable*/

    HI_BOOL bTMapEn         ;         /*ToneMapping enable*/
    HI_BOOL bGMapEn         ;         /*GamutMapping enable*/
    HI_BOOL bGammaEn        ;         /*Gamma enable*/
    HI_BOOL bV1GammaEn      ;         /*Gamma enable*/  //96add
    HI_BOOL bDitherEn       ;         /*Dither enable*/
    HI_BOOL bR2YEn          ;         /*RGB2YUV enable*/
    HI_BOOL bChromaAdjEn    ;         /*ChromaAdjust enable*/
    HI_BOOL bBT2020CL       ;         /* 1:BT2020CL; 0:BT2020NCL */
    HI_BOOL bR2YPipEn       ;         /*RGB2YUV enable*/  //96add
    HI_BOOL bV0CLEn         ;         /* 1:BT2020CL; 0:BT2020NCL */ //96add
    HI_BOOL bV1CLEn         ;         /* 1:BT2020CL; 0:BT2020NCL */ //96add

    /**** Mode Sel ****/
    HI_BOOL bGMapPosSel     ;         /* 1: GMAP after TMAP;   0: GMAP before TMAP */
    HI_BOOL bDitherMode     ;         /* 1: Dither; 0: Round */

    /***** Coef *****/
    PQ_HDR_Y2R   stY2R      ;         /* YUV2RGB */
    PQ_HDR_Y2R   stY2RV1    ;         /* YUV2RGB */ //96add
    PQ_HDR_DEGMM stDeGmm    ;         /* DeGamma */
    PQ_HDR_TMAP  stTMAP     ;         /* ToneMapping */
    PQ_HDR_TMAP  stSMAP     ;         /* ToneMapping *///96MV200 add
    PQ_HDR_GMAP  stGMAP     ;         /* GamutMapping */
    PQ_HDR_GMM   stGmm      ;         /* Gamma */
    PQ_HDR_R2Y   stR2Y      ;         /* RGB2YUV */
    PQ_HDR_CADJ  stCadj     ;         /* CADJ*/  //96add
} HI_PQ_HDR_CFG;


#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


