/****************************************************************************
* This product contains one or more programs protected under international
* and U.S. copyright laws as unpublished works.  They are confidential and
* proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
* whole or in part, or the production of derivative works therefrom without
* the express permission of Dolby Laboratories is prohibited.
*
*             Copyright 2011 - 2015 by Dolby Laboratories.
*                     All rights reserved.
****************************************************************************/
#ifndef K_DM_TYPE_FXP_H
#define K_DM_TYPE_FXP_H

//VDP_CBB_FPGA
#include "KCdmModCtrl.h"
#include "KdmType.h"
#include "KdmTypeFxpCmn.h"
//#include "vdp_hdr_fpga.h"

typedef   int                int32_t;
typedef   unsigned int       uint32_t;
typedef   unsigned char      uint8_t;
typedef   short   		     int16_t;
typedef   unsigned short     uint16_t;
typedef   unsigned long long uint64_t;
#define MAX_PIVOT       9
#define MAX_POLY_ORDER  2
#define MAX_DM_EXT_BLOCKS 255

/*! @brief HDR10 infoframe data structure.
           This is the data structure used for the HDR10 infoframe.
           Details for each entry can be found in CEA-861.3
*/
typedef struct hdr_10_infoframe_s
{
    uint8_t infoframe_type_code      ;
    uint8_t infoframe_version_number ;
    uint8_t length_of_info_frame     ;
    uint8_t data_byte_1              ;
    uint8_t data_byte_2              ;
    uint8_t display_primaries_x_0_LSB;
    uint8_t display_primaries_x_0_MSB;
    uint8_t display_primaries_y_0_LSB;
    uint8_t display_primaries_y_0_MSB;
    uint8_t display_primaries_x_1_LSB;
    uint8_t display_primaries_x_1_MSB;
    uint8_t display_primaries_y_1_LSB;
    uint8_t display_primaries_y_1_MSB;
    uint8_t display_primaries_x_2_LSB;
    uint8_t display_primaries_x_2_MSB;
    uint8_t display_primaries_y_2_LSB;
    uint8_t display_primaries_y_2_MSB;
    uint8_t white_point_x_LSB        ;
    uint8_t white_point_x_MSB        ;
    uint8_t white_point_y_LSB        ;
    uint8_t white_point_y_MSB        ;
    uint8_t max_display_mastering_luminance_LSB;
    uint8_t max_display_mastering_luminance_MSB;
    uint8_t min_display_mastering_luminance_LSB;
    uint8_t min_display_mastering_luminance_MSB;
    uint8_t max_content_light_level_LSB        ;
    uint8_t max_content_light_level_MSB        ;
    uint8_t max_frame_average_light_level_LSB  ;
    uint8_t max_frame_average_light_level_MSB  ;
} hdr_10_infoframe_t;

typedef struct rpu_ext_config_fixpt_main_s
{
    uint32_t  rpu_VDR_bit_depth;
    uint32_t  rpu_BL_bit_depth;
    uint32_t  rpu_EL_bit_depth;
    uint32_t  coefficient_log2_denom;
    uint32_t  num_pivots[3];
    uint32_t  pivot_value[3][MAX_PIVOT];
    uint32_t  mapping_idc[3];
    uint32_t  poly_order[3][MAX_PIVOT-1];
    int32_t   poly_coef_int[3][MAX_PIVOT-1][MAX_POLY_ORDER+1];
    uint32_t  poly_coef[3][MAX_PIVOT-1][MAX_POLY_ORDER+1];
    uint32_t  MMR_order[2];
    int32_t   MMR_coef_int[2][22];
    uint32_t  MMR_coef[2][22];
    uint8_t   NLQ_method_idc;
    uint8_t   disable_residual_flag;
    uint8_t   el_spatial_resampling_filter_flag;
    uint8_t   reserved_8bit;
    uint32_t  NLQ_offset[3];
    int32_t   NLQ_coeff_int[3][3];
    uint32_t  NLQ_coeff[3][3];
    uint32_t  spatial_resampling_filter_flag;
    uint32_t  spatial_resampling_explicit_filter_flag;
    uint32_t  spatial_filter_exp_coef_log2_denom;
    uint32_t  spatial_resampling_mode_hor_idc;
    uint32_t  spatial_resampling_mode_ver_idc;
    uint32_t  spatial_resampling_filter_hor_idc[3];
    uint32_t  spatial_resampling_filter_ver_idc[3];
    uint32_t  spatial_resampling_luma_pivot[2];
    int32_t   spatial_filter_coeff_hor_int[3][8];
    uint32_t  spatial_filter_coeff_hor[3][8];
    int32_t   spatial_filter_coeff_ver_int[2][3][6];
    uint32_t  spatial_filter_coeff_ver[2][3][6];
} rpu_ext_config_fixpt_main_t;

typedef struct dm_metadata_base_s
{
    /* signal attributes */
    unsigned char dm_metadata_id; // affected_dm_metadata_id<<4|current_dm_metadata_id
    unsigned char scene_refresh_flag;
    unsigned char YCCtoRGB_coef0_hi;
    unsigned char YCCtoRGB_coef0_lo;
    unsigned char YCCtoRGB_coef1_hi;
    unsigned char YCCtoRGB_coef1_lo;
    unsigned char YCCtoRGB_coef2_hi;
    unsigned char YCCtoRGB_coef2_lo;
    unsigned char YCCtoRGB_coef3_hi;
    unsigned char YCCtoRGB_coef3_lo;
    unsigned char YCCtoRGB_coef4_hi;
    unsigned char YCCtoRGB_coef4_lo;
    unsigned char YCCtoRGB_coef5_hi;
    unsigned char YCCtoRGB_coef5_lo;
    unsigned char YCCtoRGB_coef6_hi;
    unsigned char YCCtoRGB_coef6_lo;
    unsigned char YCCtoRGB_coef7_hi;
    unsigned char YCCtoRGB_coef7_lo;
    unsigned char YCCtoRGB_coef8_hi;
    unsigned char YCCtoRGB_coef8_lo;
    unsigned char YCCtoRGB_offset0_byte3;
    unsigned char YCCtoRGB_offset0_byte2;
    unsigned char YCCtoRGB_offset0_byte1;
    unsigned char YCCtoRGB_offset0_byte0;
    unsigned char YCCtoRGB_offset1_byte3;
    unsigned char YCCtoRGB_offset1_byte2;
    unsigned char YCCtoRGB_offset1_byte1;
    unsigned char YCCtoRGB_offset1_byte0;
    unsigned char YCCtoRGB_offset2_byte3;
    unsigned char YCCtoRGB_offset2_byte2;
    unsigned char YCCtoRGB_offset2_byte1;
    unsigned char YCCtoRGB_offset2_byte0;
    unsigned char RGBtoLMS_coef0_hi;
    unsigned char RGBtoLMS_coef0_lo;
    unsigned char RGBtoLMS_coef1_hi;
    unsigned char RGBtoLMS_coef1_lo;
    unsigned char RGBtoLMS_coef2_hi;
    unsigned char RGBtoLMS_coef2_lo;
    unsigned char RGBtoLMS_coef3_hi;
    unsigned char RGBtoLMS_coef3_lo;
    unsigned char RGBtoLMS_coef4_hi;
    unsigned char RGBtoLMS_coef4_lo;
    unsigned char RGBtoLMS_coef5_hi;
    unsigned char RGBtoLMS_coef5_lo;
    unsigned char RGBtoLMS_coef6_hi;
    unsigned char RGBtoLMS_coef6_lo;
    unsigned char RGBtoLMS_coef7_hi;
    unsigned char RGBtoLMS_coef7_lo;
    unsigned char RGBtoLMS_coef8_hi;
    unsigned char RGBtoLMS_coef8_lo;
    unsigned char signal_eotf_hi;
    unsigned char signal_eotf_lo;
    unsigned char signal_eotf_param0_hi;
    unsigned char signal_eotf_param0_lo;
    unsigned char signal_eotf_param1_hi;
    unsigned char signal_eotf_param1_lo;
    unsigned char signal_eotf_param2_byte3;
    unsigned char signal_eotf_param2_byte2;
    unsigned char signal_eotf_param2_byte1;
    unsigned char signal_eotf_param2_byte0;
    unsigned char signal_bit_depth;
    unsigned char signal_color_space;
    unsigned char signal_chroma_format;
    unsigned char signal_full_range_flag;
    /* source display attributes */
    unsigned char source_min_PQ_hi;
    unsigned char source_min_PQ_lo;
    unsigned char source_max_PQ_hi;
    unsigned char source_max_PQ_lo;
    unsigned char source_diagonal_hi;
    unsigned char source_diagonal_lo;
    /* extended metadata */
    unsigned char num_ext_blocks;
} dm_metadata_base_t;

typedef struct ext_level_1_s
{
    unsigned char min_PQ_hi;
    unsigned char min_PQ_lo;
    unsigned char max_PQ_hi;
    unsigned char max_PQ_lo;
    unsigned char avg_PQ_hi;
    unsigned char avg_PQ_lo;
} ext_level_1_t;

typedef struct ext_level_2_s
{
    unsigned char target_max_PQ_hi       ;
    unsigned char target_max_PQ_lo       ;
    unsigned char trim_slope_hi          ;
    unsigned char trim_slope_lo          ;
    unsigned char trim_offset_hi         ;
    unsigned char trim_offset_lo         ;
    unsigned char trim_power_hi          ;
    unsigned char trim_power_lo          ;
    unsigned char trim_chroma_weight_hi  ;
    unsigned char trim_chroma_weight_lo  ;
    unsigned char trim_saturation_gain_hi;
    unsigned char trim_saturation_gain_lo;
    unsigned char ms_weight_hi           ;
    unsigned char ms_weight_lo           ;
} ext_level_2_t;

typedef struct ext_level_4_s
{
    unsigned char anchor_PQ_hi       ;
    unsigned char anchor_PQ_lo       ;
    unsigned char anchor_power_hi    ;
    unsigned char anchor_power_lo    ;
} ext_level_4_t;

typedef struct ext_level_5_s
{
    unsigned char active_area_left_offset_hi  ;
    unsigned char active_area_left_offset_lo  ;
    unsigned char active_area_right_offset_hi ;
    unsigned char active_area_right_offset_lo ;
    unsigned char active_area_top_offset_hi   ;
    unsigned char active_area_top_offset_lo   ;
    unsigned char active_area_bottom_offset_hi;
    unsigned char active_area_bottom_offset_lo;
} ext_level_5_t;

typedef struct ext_level_6_s
{
    unsigned char max_display_mastering_luminance_hi;
    unsigned char max_display_mastering_luminance_lo;
    unsigned char min_display_mastering_luminance_hi;
    unsigned char min_display_mastering_luminance_lo;
    unsigned char max_content_light_level_hi        ;
    unsigned char max_content_light_level_lo        ;
    unsigned char max_frame_average_light_level_hi  ;
    unsigned char max_frame_average_light_level_lo  ;
} ext_level_6_t;
typedef struct dm_metadata_ext_s
{
    unsigned char ext_block_length_byte3;
    unsigned char ext_block_length_byte2;
    unsigned char ext_block_length_byte1;
    unsigned char ext_block_length_byte0;
    unsigned char ext_block_level;
    union {
        ext_level_1_t level_1;
        ext_level_2_t level_2;
        ext_level_4_t level_4;
        ext_level_5_t level_5;
        ext_level_6_t level_6;
    } l;
} dm_metadata_ext_t;

typedef struct dm_metadata_s {
    dm_metadata_base_t base;
    dm_metadata_ext_t ext[MAX_DM_EXT_BLOCKS];
} dm_metadata_t;

////// data path/kernel structure: KS
//// E=>O
typedef struct EotfParamFxp_t_
{
  // range
  uint16_t rangeMin, range;
  uint32_t rangeInv;
  uint16_t bdp;
  // gamma stuff
  KEotf_t eotf;   // CEotfBt1886, CEotfPq coded
#if (REDUCED_COMPLEXITY == 0)
  uint16_t gamma;
  uint16_t a, b;
  uint32_t g;
#endif
} EotfParamFxp_t;

//// O=>E
typedef struct OetfParamFxp_t_
{
  //// range
  uint32_t min, max; // in linear output space
  uint16_t rangeMin, range; // in final output
  uint32_t rangeOverOne;
  uint16_t bdp;

  // gamma stuff
  KEotf_t oetf;   // CEotfBt1886, CEotfPq coded
} OetfParamFxp_t;

//// input mapping
typedef struct DmKsIMapFxp_t_ {
#if !EN_IPT_PQ_ONLY_OPTION
  KClr_t clr;
  int16_t m33Yuv2RgbScale2P;
  int16_t m33Yuv2Rgb[3][3];
  int32_t v3Yuv2RgbOffInRgb[3];

  EotfParamFxp_t eotfParam;
#if REDUCED_COMPLEXITY
  uint32_t g2L[DEF_G2L_LUT_SIZE];
#endif

  int16_t m33Rgb2LmsScale2P;
  int16_t m33Rgb2Lms[3][3];

  int16_t m33Lms2IptScale2P;
  int16_t m33Lms2Ipt[3][3];
#endif

  int32_t iptScale;
  int32_t v3IptOff[3];
} DmKsIMapFxp_t;

#if DM_SIMPLE_SEC_INPUT
//// input mapping for SDR Gamma RGB case
typedef struct DmKsIMapSdrFxp_t_ {
  KClr_t clr;
  EotfParamFxp_t eotfParam;

  int16_t m33Rgb2LmsScale2P;
  int16_t m33Rgb2Lms[3][3];

  int16_t m33Lms2IptScale2P;
  int16_t m33Lms2Ipt[3][3];
} DmKsIMapSdrFxp_t;
#endif // DM_SIMPLE_SEC_INPUT

/// tone curve mapping
typedef struct Dm3KsTMapFxp_t_ {
#if EN_SKIP_TMAP_MS
  KTcLutDir_t tcLutDir; // to signal the lut direction or bypass
#endif

  int16_t tmLutISizeM1;


  int16_t tmLutSSizeM1;
  int16_t tmLutI[TM1_LUT_MAX_SIZE];
  int16_t tmLutS[TM1_LUT_MAX_SIZE];
  //uint16_t satWeight;

  int16_t smLutISizeM1, smLutSSizeM1;
  int16_t smLutI[TM1_LUT_MAX_SIZE];
  int16_t smLutS[TM1_LUT_MAX_SIZE];
  //uint16_t chromaWeight;
} DmKsTMapFxp_t;

#if DM_SIMPLE_SEC_INPUT
/// tone curve mapping with reduced size (for SDR)
typedef struct Dm3KsTMapReducedFxp_t_ {
#if EN_SKIP_TMAP_MS
  KTcLutDir_t tcLutDir; // to signal the lut direction or bypass
#endif

  int16_t tmLutISizeM1;

  int16_t tmLutSSizeM1;
  int16_t tmLutI[TM2_LUT_MAX_SIZE];
  int16_t tmLutS[TM2_LUT_MAX_SIZE];
  //uint16_t satWeight;

  int16_t smLutISizeM1, smLutSSizeM1;
  int16_t smLutI[TM2_LUT_MAX_SIZE];
  int16_t smLutS[TM2_LUT_MAX_SIZE];
  //uint16_t chromaWeight;
} DmKsTMapReducedFxp_t;
#endif // DM_SIMPLE_SEC_INPUT

//// ms blending

/// output mapping
typedef struct Dm3KsOMapFxp_t_ {
  // lms => target rgb
  int16_t m33Ipt2LmsScale2P;
  int16_t m33Ipt2Lms[3][3];

  // lms => target rgb
  int16_t m33Lms2RgbScale2P;
  int16_t m33Lms2Rgb[3][3];

  OetfParamFxp_t oetfParam;


  KClr_t clr;
  int16_t m33Rgb2YuvScale2P;
  int16_t m33Rgb2Yuv[3][3];
  int32_t v3Rgb2YuvOff[3];
  int32_t iptScale;
  int32_t v3IptOff[3];
} Dm3KsOMapFxp_t;

typedef struct Dm3KsOMapFxp_t_  DmKsOMapFxp_t_;
typedef Dm3KsOMapFxp_t DmKsOMapFxp_t;



// for pre-post processing: up/down sampling
//#if !EN_GENERAL_SEC_INPUT

#if 0
// an all in one structure
typedef struct DmKsUdsFxp_t_
{
  //// for UV
#if EN_UP_DOWN_SAMPLE_OPTION
  KChrm_t chrmIn, chrmOut;
#endif

  int16_t minUs, maxUs, minDs, maxDs;

#if EN_UP_DOWN_SAMPLE_OPTION
  int16_t filterUvRowUsHalfSize;
  int16_t filterUvRowUsScale2P;
  int16_t filterUvRowUs0_m[8];
  int16_t filterUvRowUs1_m[8];

  int16_t filterUvColUsHalfSize;
  int16_t filterUvColUsScale2P;
  int16_t filterUvColUs_m[8];

  int16_t filterUvColDsRadius;
  int16_t filterUvColDsScale2P;
  int16_t filterUvColDs_m[16];
#endif
} DmKsUdsFxp_t;

#define DmKsUsFxp_t DmKsUdsFxp_t
#define DmKsDsFxp_t DmKsUdsFxp_t
#else

typedef struct DmKsUsFxp_t_
{
  //// for UV
//#if EN_UP_DOWN_SAMPLE_OPTION
#if 1
  KChrm_t chrmIn;
#endif

  int16_t minUs, maxUs;

//#if EN_UP_DOWN_SAMPLE_OPTION
#if 1

  int16_t filterUvRowUsHalfSize;
  int16_t filterUvRowUsScale2P;
  int16_t filterUvRowUs0_m[8];
  int16_t filterUvRowUs1_m[8];

  int16_t filterUvColUsHalfSize;
  int16_t filterUvColUsScale2P;
  int16_t filterUvColUs_m[8];
#endif
} DmKsUsFxp_t;

typedef struct DmKsDsFxp_t_
{
  //// for UV
#if 1
  KChrm_t chrmOut;
#endif

  int16_t minDs, maxDs;

#if 1

  int16_t filterUvColDsRadius;
  int16_t filterUvColDsScale2P;
  int16_t filterUvColDs_m[16];
#endif
} DmKsDsFxp_t;

#endif

//// the ks collection
typedef struct DmKsFxp_t_
{
#if 1//EN_UP_DOWN_SAMPLE_OPTION || EN_MS_OPTION
  //// tmp buf to store (I, P, T), post up sample or pre down sample (Y, U, V)
  int16_t rowPitchNum;   // pitch in index

  //unsigned long long frmBuf0, frmBuf1, frmBuf2;
  unsigned long long frmBuf0, frmBuf1, frmBuf2;

#endif

#if 1//EN_UP_DOWN_SAMPLE_OPTION && EN_GENERAL_SEC_INPUT
  //// tmp buf for 2nd channel upsample result
  unsigned long long frmBuf0G, frmBuf1G, frmBuf2G;
#endif

  //// HARDWARE REGISTER MAP START ////

#if 0

  DmKsUdsFxp_t ksUds;
#define ksUs   ksUds
#define ksDs   ksUds
#else
  DmKsUsFxp_t ksUs;
  DmKsDsFxp_t ksDs;

#endif

  DmKsCtrl_t ksDmCtrl;

  DmKsFrmFmt_t ksFrmFmtI;

  DmKsIMapFxp_t  ksIMap;

  DmKsTMapFxp_t ksTMap;

#if DM_SEC_INPUT
#if EN_GENERAL_SEC_INPUT
  DmKsUsFxp_t ksUsG;
  DmKsFrmFmt_t ksFrmFmtA; // for alpha if it does not in rgba
  uint32_t rangeInvA;     // alpha remap factor
#endif

  DmKsFrmFmt_t ksFrmFmtG;

#if DM_SIMPLE_SEC_INPUT
  DmKsIMapSdrFxp_t  ksIMapSdrG;

  DmKsTMapReducedFxp_t ksTMapReducedG;
#endif // if DM_SIMPLE_SEC_INPUT

  DmKsIMapFxp_t  ksIMapG;

  DmKsTMapFxp_t ksTMapG;
#endif // # if DM_SEC_INPUT


  DmKsOMapFxp_t ksOMap;

  DmKsFrmFmt_t ksFrmFmtO;

#if EN_BYPASS_DM
  int16_t bypassShift;
#endif

  //// HARDWARE REGISTER MAP END ////

} DmKsFxp_t;


#endif // K_DM_TYPE_FXP_H
