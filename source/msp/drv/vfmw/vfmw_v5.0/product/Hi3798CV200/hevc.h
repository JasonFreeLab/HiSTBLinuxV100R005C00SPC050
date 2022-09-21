
#ifndef _HEVC_HEADER_
#define _HEVC_HEADER_

#ifdef __cplusplus
extern "C" {
#endif

#include "basedef.h"
#include "vfmw.h"
#include "public.h"
#include "bitstream.h"
#include "vdm_hal.h"


#define HEVC_STREAM_END_CODE1                (0x48535049)
#define HEVC_STREAM_END_CODE2                (0x43454E44)

// profile related constant
#define HEVC_MAX_VIDEO_PARAM_SET_ID          (16+1)
#define HEVC_MAX_SEQ_PARAM_SET_ID            (16+1)
#define HEVC_MAX_PIC_PARAM_SET_ID            (64+1)
#define HEVC_MAX_DPB_PIC_BUF                 (6)
#define HEVC_MAX_LSB_NUM                     (33)

#define HEVC_MAX_TEMPLAYER                   (8)             //max number of temporal layer
#define HEVC_MAX_VPS_OP_SETS_PLUS1           (1024)
#define HEVC_MAX_STRPS_NUM                   (64)
#define HEVC_MAX_NESTING_NUM_LAYER           (64)

#define HEVC_MAX_INT                         (2147483647)    //max value of signed 32-bit integer
#define HEVC_MAX_UINT                        (0xFFFFFFFFU)   //max. value of unsigned 32-bit integer

#ifdef MV_HEVC_SUPPORT
#define HEVC_SCALE_TYPE_10X                  (0)
#define HEVC_SCALE_TYPE_15X                  (1)
#define HEVC_SCALE_TYPE_20X                  (2)
#define HEVC_SCALE_TYPE_30X                  (3)

#define HEVC_MAX_NUM_LAYERS                  (2)
#define HEVC_MAX_VPS_OUTPUTLAYER_SETS        (HEVC_MAX_VPS_OP_SETS_PLUS1 + 1)
#define HEVC_MAX_NUM_SCALED_REF_LAYERS       (HEVC_MAX_NUM_LAYERS-1)
#define HEVC_EXT_MAX_REF_LOC_OFFSET          (64)
#define HEVC_MAX_NUM_SCALABILITY_TYPES       (16)
#define HEVC_MAX_PARTITION_NUM               (16)
#define HEVC_MAX_SIZE_VIEW_QUEUE             (16)
#else

#define HEVC_MAX_NUM_LAYERS                  (1)
#endif

#if !defined (CFG_HEVC_MAX_CU_DEPTH)
#define HEVC_MAX_CU_DEPTH                    (7)           // log2(LCUSize)
#else
#define HEVC_MAX_CU_DEPTH                    (CFG_HEVC_MAX_CU_DEPTH)
#endif

#define HEVC_MAX_CU_SIZE                     (1<<(HEVC_MAX_CU_DEPTH))      // maximum allowable size of CU
#define HEVC_MIN_PU_SIZE                     (4)
#define HEVC_MRG_MAX_NUM_CANDS               (5)

#define HEVC_SCALING_LIST_NUM                (6)           //< list number for quantization matrix
#define HEVC_SCALING_LIST_DC                 (16)          //< default DC value
#define HEVC_SCALING_LIST_START_VALUE        (8)           //< start value for dpcm mode
#define HEVC_MAX_MATRIX_COEF_NUM             (64)          //< max coefficient number for quantization matrix

#define HEVC_MAX_LIST_SIZE                   (16+1)
#define HEVC_MAX_FRAME_STORE                 (20)          // Maximun Frame Store Num
#define HEVC_MAX_PMV_STORE                   (20)          // Maximun PMV   Store Num

#define HEVC_SINT8_MAX_VAL                   (127)
#define HEVC_SINT8_MIN_VAL                   (-128)
#define HEVC_SINT13_MAX_VAL                  (4095)
#define HEVC_SINT13_MIN_VAL                  (-4096)

#define HEVC_I_SLICE                         (2)
#define HEVC_P_SLICE                         (1)
#define HEVC_B_SLICE                         (0)

#define HEVC_I_FRAME                         (0)
#define HEVC_P_FRAME                         (1)
#define HEVC_B_FRAME                         (2)

#define HEVC_ERR_FS_OUT_AGAIN                (-3)
#define HEVC_NOTDEC                          (-2)
#define HEVC_DEC_ERR                         (-1)
#define HEVC_DEC_NORMAL                      (0)

#define HEVC_MEET_EOS                        (2)
#define HEVC_PIC_DECODING                    (1)
#define HEVC_PIC_EMPTY                       (0)

#define HEVC_GET_ONE_NALU_SIZE               (4*1024)


/************************ enum define ************************/
// coefficient scanning type used in ACS
typedef enum
{
    SCAN_ZIGZAG = 0,       //< typical zigzag scan
    SCAN_HOR,              //< horizontal first scan
    SCAN_VER,              //< vertical first scan
    SCAN_DIAG              //< up-right diagonal scan
} HEVC_COEFF_SCAN_TYPE;

// reference list index
typedef enum
{
    REF_PIC_LIST_0 = 0,    //< reference list 0
    REF_PIC_LIST_1 = 1,    //< reference list 1
    REF_PIC_LIST_C = 2,    //< combined reference list for uni-prediction in B-Slices
    REF_PIC_LIST_X = 100   //< special mark
} HEVC_REF_PIC_LIST;

typedef enum
{
    SCALING_LIST_4x4 = 0,
    SCALING_LIST_8x8,
    SCALING_LIST_16x16,
    SCALING_LIST_32x32,
    SCALING_LIST_SIZE_NUM
} HEVC_SCALING_LIST_SIZE;

typedef enum
{
    BUFFERING_PERIOD                      = 0,
    PICTURE_TIMING                        = 1,
    PAN_SCAN_RECT                         = 2,
    FILLER_PAYLOAD                        = 3,
    USER_DATA_REGISTERED_ITU_T_T35        = 4,
    USER_DATA_UNREGISTERED                = 5,
    RECOVERY_POINT                        = 6,
    SCENE_INFO                            = 9,
    FULL_FRAME_SNAPSHOT                   = 15,
    PROGRESSIVE_REFINEMENT_SEGMENT_START  = 16,
    PROGRESSIVE_REFINEMENT_SEGMENT_END    = 17,
    FILM_GRAIN_CHARACTERISTICS            = 19,
    POST_FILTER_HINT                      = 22,
    TONE_MAPPING_INFO                     = 23,
    FRAME_PACKING                         = 45,
    DISPLAY_ORIENTATION                   = 47,
    SOP_DESCRIPTION                       = 128,
    ACTIVE_PARAMETER_SETS                 = 129,
    DECODING_UNIT_INFO                    = 130,
    TEMPORAL_LEVEL0_INDEX                 = 131,
    DECODED_PICTURE_HASH                  = 132,
    SCALABLE_NESTING                      = 133,
    REGION_REFRESH_INFO                   = 134,
} HEVC_SEI_PAYLOADTYPE;

typedef enum
{
    MD5 = 0,
    CRC,
    CHECKSUM,
    RESERVED,
} HEVC_SEI_Method;

typedef enum
{
    NOT_NEW_PIC = 0,
    IS_NEW_PIC,
    IS_SKIP_PIC,
} HEVC_PIC_TYPE;

typedef enum
{
    FIRST_FRAME_OUT_INIT = 0,
    FIRST_FRAME_WAIT_OUT,
    FIRST_FRAME_ALREADY_OUT,
} HEVC_FO_STATE_E;

typedef enum
{
    FS_NOT_USED = 0,
    FS_IN_DPB,
    FS_DISPLAY_ONLY,
} HEVC_FS_STATE_E;

typedef enum
{
    FIRST_FRAME_INIT = 0,
    FIRST_FRAME_PROCESSED,
} HEVC_FIRST_FRAME_STATE_E;

typedef enum
{
    NAL_UNIT_CODED_SLICE_TRAIL_N = 0,  // 0
    NAL_UNIT_CODED_SLICE_TRAIL_R,      // 1

    NAL_UNIT_CODED_SLICE_TSA_N,        // 2
    NAL_UNIT_CODED_SLICE_TLA_R,        // 3    // Current name in the spec: TSA_R

    NAL_UNIT_CODED_SLICE_STSA_N,       // 4
    NAL_UNIT_CODED_SLICE_STSA_R,       // 5

    NAL_UNIT_CODED_SLICE_RADL_N,       // 6
    NAL_UNIT_CODED_SLICE_RADL_R,       // 7    // Current name in the spec: RADL_R

    NAL_UNIT_CODED_SLICE_RASL_N,       // 8
    NAL_UNIT_CODED_SLICE_RASL_R,       // 9    // Current name in the spec: RASL_R

    NAL_UNIT_RESERVED_VCL_N10,
    NAL_UNIT_RESERVED_VCL_R11,
    NAL_UNIT_RESERVED_VCL_N12,
    NAL_UNIT_RESERVED_VCL_R13,
    NAL_UNIT_RESERVED_VCL_N14,
    NAL_UNIT_RESERVED_VCL_R15,

    NAL_UNIT_CODED_SLICE_BLA_W_LP,     // 16   // Current name in the spec: BLA_W_LP
    NAL_UNIT_CODED_SLICE_BLA_W_RADL,   // 17   // Current name in the spec: BLA_W_DLP
    NAL_UNIT_CODED_SLICE_BLA_N_LP,     // 18
    NAL_UNIT_CODED_SLICE_IDR_W_RADL,   // 19   // Current name in the spec: IDR_W_DLP
    NAL_UNIT_CODED_SLICE_IDR_N_LP,     // 20
    NAL_UNIT_CODED_SLICE_CRA,          // 21
    NAL_UNIT_RESERVED_IRAP_VCL22,
    NAL_UNIT_RESERVED_IRAP_VCL23,

    NAL_UNIT_RESERVED_VCL24,
    NAL_UNIT_RESERVED_VCL25,
    NAL_UNIT_RESERVED_VCL26,
    NAL_UNIT_RESERVED_VCL27,
    NAL_UNIT_RESERVED_VCL28,
    NAL_UNIT_RESERVED_VCL29,
    NAL_UNIT_RESERVED_VCL30,
    NAL_UNIT_RESERVED_VCL31,

    NAL_UNIT_VPS,                      // 32
    NAL_UNIT_SPS,                      // 33
    NAL_UNIT_PPS,                      // 34
    NAL_UNIT_ACCESS_UNIT_DELIMITER,    // 35
    NAL_UNIT_EOS,                      // 36
    NAL_UNIT_EOB,                      // 37
    NAL_UNIT_FILLER_DATA,              // 38
    NAL_UNIT_PREFIX_SEI,               // 39 Prefix SEI
    NAL_UNIT_SUFFIX_SEI,               // 40 Suffix SEI
    NAL_UNIT_RESERVED_NVCL41,
    NAL_UNIT_RESERVED_NVCL42,
    NAL_UNIT_RESERVED_NVCL43,
    NAL_UNIT_RESERVED_NVCL44,
    NAL_UNIT_RESERVED_NVCL45,
    NAL_UNIT_RESERVED_NVCL46,
    NAL_UNIT_RESERVED_NVCL47,

    NAL_UNIT_EOPIC,                    // NAL_UNIT_UNSPECIFIED_48
    NAL_UNIT_EOSTREAM,                 // NAL_UNIT_UNSPECIFIED_49
    NAL_UNIT_UNSPECIFIED_50,
    NAL_UNIT_UNSPECIFIED_51,
    NAL_UNIT_UNSPECIFIED_52,
    NAL_UNIT_UNSPECIFIED_53,
    NAL_UNIT_UNSPECIFIED_54,
    NAL_UNIT_UNSPECIFIED_55,
    NAL_UNIT_UNSPECIFIED_56,
    NAL_UNIT_UNSPECIFIED_57,
    NAL_UNIT_UNSPECIFIED_58,
    NAL_UNIT_UNSPECIFIED_59,
    NAL_UNIT_UNSPECIFIED_60,
    NAL_UNIT_UNSPECIFIED_61,
    NAL_UNIT_UNSPECIFIED_62,
    NAL_UNIT_UNSPECIFIED_63,
    NAL_UNIT_INVALID,
} NalUnitType;


/************************ structure define ************************/
typedef struct
{
    UINT8  general_progressive_source_flag;
    UINT8  general_interlaced_source_flag;
    SINT32 general_level_idc;
} HEVC_PROFILE_TIER_LEVEL_S;

typedef struct
{
    UINT8  scalingListCoef[SCALING_LIST_SIZE_NUM][HEVC_SCALING_LIST_NUM][HEVC_MAX_MATRIX_COEF_NUM];
    SINT32 scalingListDC[SCALING_LIST_SIZE_NUM][HEVC_SCALING_LIST_NUM]; //!< the DC value of the matrix coefficient for 16x16
} HEVC_SCALING_LIST;

typedef struct
{
    UINT32 num_negative_pics;
    UINT32 num_positive_pics;
    UINT32 num_of_pics;
    UINT8  used_flag[HEVC_MAX_NUM_REF_PICS + 1];
    SINT32 delta_poc[HEVC_MAX_NUM_REF_PICS + 1];
    SINT32 poc[HEVC_MAX_NUM_REF_PICS];
} HEVC_SHORT_TERM_RPSET_S;

typedef struct
{
    UINT8  ref_pic_list_modification_flag_l0;
    UINT8  ref_pic_list_modification_flag_l1;
    UINT32 list_entry_l0[32];
    UINT32 list_entry_l1[32];
} HEVC_REF_PIC_LISTS_MODDIFICATION;

typedef struct
{
    UINT32 luma_log2_weight_denom;
    SINT32 luma_offset_l0[HEVC_MAX_NUM_REF_PICS];
    SINT32 luma_offset_l1[HEVC_MAX_NUM_REF_PICS];
    UINT32 chroma_log2_weight_denom;
    SINT32 LumaWeightL0[HEVC_MAX_NUM_REF_PICS];
    SINT32 ChromaWeightL0[HEVC_MAX_NUM_REF_PICS][2];
    SINT32 ChromaOffsetL0[HEVC_MAX_NUM_REF_PICS][2];
    SINT32 LumaWeightL1[HEVC_MAX_NUM_REF_PICS];
    SINT32 ChromaWeightL1[HEVC_MAX_NUM_REF_PICS][2];
    SINT32 ChromaOffsetL1[HEVC_MAX_NUM_REF_PICS][2];
} HEVC_PRED_WEIGHT_TABLE;

typedef struct
{
    UINT32 cpb_cnt_minus1;
} HEVC_HRD_SUBLAYER_SET_S;

typedef struct
{
    UINT8  nal_hrd_parameters_present_flag;
    UINT8  vcl_hrd_parameters_present_flag;
    UINT8  sub_pic_hrd_params_present_flag;
    UINT8  sub_pic_cpb_params_in_pic_timing_sei_flag;
    UINT32 du_cpb_removal_delay_increment_length_minus1;
    UINT32 dpb_output_delay_du_length_minus1;
    UINT32 initial_cpb_removal_delay_length_minus1;
    UINT32 au_cpb_removal_delay_length_minus1;
    UINT32 dpb_output_delay_length_minus1;
    HEVC_HRD_SUBLAYER_SET_S hrd_sublayer[HEVC_MAX_TEMPLAYER];
} HEVC_HRD_PARAM_SET_S;

#ifdef MV_HEVC_SUPPORT
typedef struct
{
    UINT8  separate_colour_plane_vps_flag;
    UINT32 pic_width_vps_in_luma_samples;
    UINT32 pic_height_vps_in_luma_samples;
    UINT32 chroma_format_vps_idc;
    UINT32 bit_depth_vps_luma_minus8;
    UINT32 bit_depth_vps_chroma_minus8;
    UINT32 conf_win_vps_left_offset;
    UINT32 conf_win_vps_right_offset;
    UINT32 conf_win_vps_top_offset;
    UINT32 conf_win_vps_bottom_offset;
} HEVC_REP_FORMAT_SET_S;

typedef struct
{
    //SINT8  max_vps_dec_pic_buffering_minus1[HEVC_MAX_VPS_OUTPUTLAYER_SETS][HEVC_MAX_NUM_LAYER_IDS][HEVC_MAX_TEMPLAYER];
    //SINT8  max_vps_num_reorder_pics        [HEVC_MAX_VPS_OUTPUTLAYER_SETS][HEVC_MAX_TEMPLAYER];
} HEVC_DPB_SIZE_SET_S;

typedef struct
{
} HEVC_VIDEO_SIGNAL_INFO_SET_S;

typedef struct
{
} HEVC_VPS_VUI_BSP_HRDPARA_SET_S;

typedef struct
{
    HEVC_VPS_VUI_BSP_HRDPARA_SET_S vps_vui_bsp_hrdpara;
} HEVC_VPS_VUI_SET_S;

typedef struct
{
    UINT8  head_reserved;

    UINT8  max_one_active_ref_layer_flag;
    UINT8  all_ref_layers_active_flag;
    UINT8  poc_lsb_not_present_flag[HEVC_MAX_NUM_LAYERS];
    UINT8  direct_dependency_flag[HEVC_MAX_NUM_LAYERS][HEVC_MAX_NUM_LAYERS];
    UINT8  output_layer_flag[HEVC_MAX_VPS_OUTPUTLAYER_SETS][HEVC_MAX_NUM_LAYERS];
    UINT8  necessary_layer_flag[HEVC_MAX_VPS_OUTPUTLAYER_SETS][HEVC_MAX_NUM_LAYERS];
    SINT32 num_layer_sets;
    SINT32 max_layers_minus1;
    SINT32 num_output_layer_sets;
    UINT32 vps_num_rep_formats_minus1;
    SINT32 view_id_val[HEVC_MAX_NUM_LAYERS];
    SINT32 layer_id_in_nuh[HEVC_MAX_NUM_LAYERS];
    SINT32 layer_idx_in_vps[HEVC_MAX_NUM_LAYERS];
    SINT32 vps_rep_format_idx[HEVC_MAX_NUM_LAYERS];
    SINT32 num_direct_ref_layers[HEVC_MAX_NUM_LAYERS];
    SINT32 sub_layers_vps_max_minus1[HEVC_MAX_NUM_LAYERS];
    SINT32 ref_layer_id[HEVC_MAX_NUM_LAYERS][HEVC_MAX_NUM_LAYERS];
    SINT32 layer_set_idx_for_ols_minus1[HEVC_MAX_VPS_OUTPUTLAYER_SETS];
    SINT32 max_sub_layers_in_layer_set_minus1[HEVC_MAX_VPS_OUTPUTLAYER_SETS];
    SINT32 max_tid_il_ref_pics_plus1[HEVC_MAX_NUM_LAYERS][HEVC_MAX_NUM_LAYERS];
    //UINT32 target_dec_layer_id_lists[HEVC_MAX_VPS_OP_SETS_PLUS1];  //not used

    HEVC_VPS_VUI_SET_S vui;
    HEVC_DPB_SIZE_SET_S dpb;
    HEVC_REP_FORMAT_SET_S repFormat[HEVC_MAX_NUM_LAYERS];

    UINT8  tail_reserved;
} HEVC_VPS_EXTENSION_SET_S;

typedef struct
{
    UINT8  sps_infer_scaling_list_flag;
    SINT32 sps_scaling_list_ref_layer_id;
}HEVC_SPS_EXTENSION_SET_S;

typedef struct
{
    UINT8  head_reserved;

    UINT8  pps_infer_scaling_list_flag;
    UINT8  resample_phase_set_present_flag[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 pps_scaling_list_ref_layer_id;
    SINT32 scaled_ref_layer_left_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 scaled_ref_layer_top_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 scaled_ref_layer_right_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 scaled_ref_layer_bottom_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 ref_region_left_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 ref_region_top_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 ref_region_right_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    SINT32 ref_region_bottom_offset[HEVC_EXT_MAX_REF_LOC_OFFSET];
    UINT32 phase_hor_luma[HEVC_EXT_MAX_REF_LOC_OFFSET];
    UINT32 phase_ver_luma[HEVC_EXT_MAX_REF_LOC_OFFSET];
    UINT32 phase_hor_chroma_plus8[HEVC_EXT_MAX_REF_LOC_OFFSET];
    UINT32 phase_ver_chroma_plus8[HEVC_EXT_MAX_REF_LOC_OFFSET];

    UINT8  tail_reserved;
}HEVC_PPS_EXTENSION_SET_S;

typedef struct
{
    UINT8  head_reserved;

    SINT32 num_active_ref_layer_pics;
    SINT32 inter_layer_pred_layer_idc[HEVC_MAX_NUM_LAYERS];

    UINT8  tail_reserved;
}HEVC_SLICE_EXTENSION_SET_S;

typedef struct
{
    SINT32 poc;
    SINT32 logic_fs_id;
    IMAGE *pImage;
} HEVC_VIEW_FRAME_S;

typedef struct
{
    UINT16 head;
    UINT16 tail;
    HEVC_VIEW_FRAME_S frame[HEVC_MAX_SIZE_VIEW_QUEUE];
} HEVC_VIEW_QUEUE_S;
#endif

typedef struct
{
    UINT8  valid;
    UINT8  vps_temporal_id_nesting_flag;
    UINT8  is_refresh;
    UINT8  vps_base_layer_internal_flag;
    SINT32 video_parameter_set_id;
    SINT32 vps_max_layers_minus1;
    SINT32 vps_max_sub_layers_minus1;
    UINT32 vps_max_layer_id;
    SINT32 vps_num_layer_sets_minus1;
    SINT32 vps_num_hrd_parameters;
    SINT32 vps_max_dec_pic_buffering[HEVC_MAX_TEMPLAYER];
    SINT32 vps_num_reorder_pics[HEVC_MAX_TEMPLAYER];
    SINT32 vps_max_latency_increase[HEVC_MAX_TEMPLAYER];

    HEVC_PROFILE_TIER_LEVEL_S profile_tier_level;  // should be [64], but we only use 0 index

#ifdef MV_HEVC_SUPPORT
    UINT32 layer_set_layer_id_list[HEVC_MAX_VPS_OP_SETS_PLUS1][HEVC_MAX_NUM_LAYERS];
    UINT32 num_layers_in_id_list[HEVC_MAX_VPS_OP_SETS_PLUS1];
    HEVC_VPS_EXTENSION_SET_S vps_extension;
#endif
} HEVC_VIDEO_PARAM_SET_S;

typedef struct
{
    UINT8  video_full_range_flag;
    UINT8  colour_description_present_flag;
    UINT8  frame_field_info_present_flag;
    UINT32 aspect_ratio;
    UINT32 aspect_ratio_idc;
    UINT32 sar_width;
    UINT32 sar_height;
    UINT32 video_format;
    UINT32 colour_primaries;
    UINT32 transfer_characteristics;
    UINT32 matrix_coeffs;
    UINT32 vui_num_units_in_tick;
    UINT32 vui_time_scale;
    HEVC_HRD_PARAM_SET_S hrd_parameters;
} HEVC_VUI_PARAM_SET_S;

typedef struct
{
    UINT8  is_refresh;
    UINT8  valid;
    UINT8  sps_temporal_id_nesting_flag;
    UINT8  scaling_list_enabled_flag;
    UINT8  sps_scaling_list_data_present_flag;
    UINT8  amp_enabled_flag;
    UINT8  sample_adaptive_offset_enabled_flag;
    UINT8  pcm_loop_filter_disable_flag;
    UINT8  long_term_ref_pics_present_flag;
    UINT8  sps_temporal_mvp_enable_flag;
    UINT8  sps_strong_intra_smoothing_enable_flag;
    UINT8  vui_parameters_present_flag;
    UINT8  sps_extension_flag;
    UINT8  used_by_curr_pic_lt_sps_flag[HEVC_MAX_LSB_NUM];
    UINT8  sps_ext_or_max_sub_layers_minus1;
    UINT8  separate_colour_plane_flag;
    UINT32 video_parameter_set_id;
    UINT32 sps_max_sub_layers_minus1;
    UINT32 seq_parameter_set_id;
    UINT32 chroma_format_idc;
    UINT32 pic_width_in_luma_samples;
    UINT32 pic_height_in_luma_samples;
    UINT32 conf_win_left_offset;
    UINT32 conf_win_right_offset;
    UINT32 conf_win_top_offset;
    UINT32 conf_win_bottom_offset;
    UINT32 bit_depth_luma;
    UINT32 qp_bdOffset_y;
    UINT32 bit_depth_chroma;
    UINT32 qp_bdOffset_c;
    UINT32 pcm_enabled_flag;
    UINT32 pcm_bit_depth_luma;
    UINT32 pcm_bit_depth_chroma;
    UINT32 max_pic_order_cnt_lsb;
    UINT32 bits_for_poc;
    UINT32 log2_min_cb_sizeY;
    UINT32 log2_ctb_sizeY;
    UINT32 min_cb_sizeY;
    UINT32 ctb_sizeY;
    UINT32 max_cu_width;
    UINT32 max_cu_height;
    UINT32 quadtree_tu_log2_min_size;
    UINT32 quadtree_tu_log2_max_size;
    UINT32 pcm_log2_min_size;
    UINT32 pcm_log2_max_size;
    UINT32 max_transform_hierarchy_depth_inter;
    UINT32 max_transform_hierarchy_depth_intra;
    UINT32 max_cu_depth;
    UINT32 num_short_term_ref_pic_sets;
    UINT32 num_long_term_ref_pic_sps;
    UINT32 dpb_size;
    UINT32 ctb_num_width;
    UINT32 ctb_num_height;
    UINT32 lt_ref_pic_poc_lsb_sps[HEVC_MAX_LSB_NUM];
    UINT32 max_dec_pic_buffering[HEVC_MAX_TEMPLAYER];
    UINT32 num_reorder_pics[HEVC_MAX_TEMPLAYER];
    UINT32 max_latency_increase[HEVC_MAX_TEMPLAYER];

    HEVC_PROFILE_TIER_LEVEL_S profile_tier_level;
    HEVC_SCALING_LIST scaling_list;
    HEVC_VUI_PARAM_SET_S vui_parameters;
    HEVC_SHORT_TERM_RPSET_S short_term_ref_pic_set[HEVC_MAX_STRPS_NUM];
#ifdef MV_HEVC_SUPPORT
    HEVC_SPS_EXTENSION_SET_S sps_extension;
#endif
} HEVC_SEQ_PARAM_SET_S;

typedef struct HEVC_SEI_PTS_PARSER_S_
{
    UINT8  IDR_pic_found;
    UINT8  NewBpStart;
    UINT32 sei_timing_num;
    UINT32 sei_timing_num_sub;
    UINT32 vui_num_units_in_tick;
    UINT32 vui_time_scale;
    UINT64 u64_last_IDR_pts;
    UINT64 u64_frame_output_time;
    UINT64 u64_last_IDRFrame_output_time;
    UINT64 last_Frame_output_time;
} HEVC_SEI_PTS_PARSER_S;

typedef struct
{
    UINT8  concatenation_flag;
    SINT32 i_init_cpb_removal_delay;
} HEVC_SEI_BUF_PERIOD_S;

typedef struct
{
    UINT32 pic_struct;
    UINT32 source_scan_type;
    UINT32 au_cpb_removal_delay_minus1;
    UINT32 pic_dpb_output_delay;
    SINT64 i64_removal_tm_of_first_pic_in_bp;
    SINT64 i64_removal_tm_of_prev_non_discardable_pic;
    SINT64 i64_removal_tm_of_prev_picture;
    SINT64 i64_au_removal_tm;
} HEVC_SEI_PIC_TIMMING_S;

typedef struct
{
} HEVC_SEI_USER_DATA_REG_ITU_T_T35_S;

typedef struct
{
    UINT8  is_avalible;
    UINT8  ts_103_433_spec_version;
    UINT8  ts_103_433_payload_mode;
} HEVC_SEI_TSI_S;

typedef struct
{
    UINT8  is_avalible;
    UINT8  cv_rec_primaries;
    UINT8  tone_mapping_input_signal_black_level_offset;
    UINT8  tone_mapping_input_signal_white_level_offset;
    UINT8  shadow_gain_control;
    UINT8  highlight_gain_control;
    UINT8  mid_tone_width_adjustment_factor;
    UINT8  tone_mapping_output_fine_tuning_num_val; // shall be in the range of 0 to 10
    UINT8  tone_mapping_output_fine_tuning_x[15];
    UINT8  tone_mapping_output_fine_tuning_y[15];
    UINT8  saturation_gain_num_val;                 // shall be in the range of 0 to 6
    UINT8  saturation_gain_x[15];
    UINT8  saturation_gain_y[15];
}HEVC_SEI_COLOR_VOLUME_RECONSTRUCTION_INFO_S;

typedef struct
{
    UINT8  is_avalible;
    UINT8  colour_remap_primaries ;
    SINT32 colour_remap_coeffs[3][3];
    UINT8  post_lut_num_val_minus1[3];
    UINT16 post_lut_coded_value[3][33];
    UINT16 post_lut_target_value[3][33];
} HEVC_SEI_COLOR_REMAPPING_INFO_S;

typedef struct
{
} HEVC_SEI_USER_DATA_UNREG_S;

typedef struct
{
} HEVC_SEI_ACTIVE_PARAMETER_SET_S;

typedef struct
{
} HEVC_SEI_DECODEING_UNIT_INFO_S;

typedef struct
{
} HEVC_SEI_RECOVERY_POINT_S;

typedef struct
{
} HEVC_SEI_FRAME_PACKING_ARRANGEMENT_S;

typedef struct
{
} HEVC_SEI_DISPLAY_ORIENTATION_S;

typedef struct
{
} HEVC_SEI_TEMPORAL_SUB_LAYER_S;

typedef struct
{
} HEVC_SEI_REGION_REFRESH_INFO_S;

typedef struct
{
    UINT8  is_avalible;
    UINT32 display_primaries_x[3];
    UINT32 display_primaries_y[3];
    UINT32 white_point_x;
    UINT32 white_point_y;
    UINT32 max_display_mastering_luminance;
    UINT32 min_display_mastering_luminance;
} HEVC_SEI_MASTERING_DISPLAY_COLOUR_VOLUME_S;

typedef struct
{
    UINT8  is_avalible;
    UINT16 max_content_light_level;
    UINT16 max_pic_average_light_level;
} HEVC_SEI_CONTENT_LIGHT_LEVEL_INFO_S;

typedef struct
{
    UINT8 hdr_transfer_characteristic_idc;
} HEVC_SEI_HLG_COMPATIBLE_INFO_S;

typedef struct
{
} HEVC_SEI_TONE_MAPPING_INFO_S;

typedef struct
{
} HEVC_SEI_SOP_INFO_S;

typedef struct
{
} HEVC_SEI_DECODED_PICTURE_HASH_S;

typedef struct
{
} HEVC_SEI_SCALABLE_NESTING_S;

typedef struct
{
    HEVC_SEI_BUF_PERIOD_S buf_period;
    HEVC_SEI_PIC_TIMMING_S pic_timming;
    HEVC_SEI_USER_DATA_REG_ITU_T_T35_S itu_t35;
    HEVC_SEI_TSI_S tsi;
    HEVC_SEI_COLOR_VOLUME_RECONSTRUCTION_INFO_S color_volume_rec_info;
    HEVC_SEI_COLOR_REMAPPING_INFO_S color_remapping_info;
    HEVC_SEI_USER_DATA_UNREG_S user_data_unreg;
    HEVC_SEI_ACTIVE_PARAMETER_SET_S active_param_sets;
    HEVC_SEI_DECODEING_UNIT_INFO_S decoding_unit_info;
    HEVC_SEI_RECOVERY_POINT_S recovery_point;
    HEVC_SEI_FRAME_PACKING_ARRANGEMENT_S frame_packing;
    HEVC_SEI_DISPLAY_ORIENTATION_S display_orientation;
    HEVC_SEI_TEMPORAL_SUB_LAYER_S temporal_sub_layer;
    HEVC_SEI_REGION_REFRESH_INFO_S region_refresh_info;
    HEVC_SEI_MASTERING_DISPLAY_COLOUR_VOLUME_S mastering_display_colour_volume;
    HEVC_SEI_CONTENT_LIGHT_LEVEL_INFO_S content_light_level;
    HEVC_SEI_HLG_COMPATIBLE_INFO_S hdr_compatible_info;
    HEVC_SEI_TONE_MAPPING_INFO_S tone_mapping_info;
    HEVC_SEI_SOP_INFO_S sop_info;
    HEVC_SEI_SCALABLE_NESTING_S scalable_nesting;
    HEVC_SEI_DECODED_PICTURE_HASH_S decoded_picture_hash;
} HEVC_SEI_PARAM_SET_S;

typedef struct
{
    UINT8  valid;
    UINT8  is_refresh;
    UINT8  dependent_slice_segments_enabled_flag;
    UINT8  sign_data_hiding_flag;
    UINT8  output_flag_present_flag;
    UINT8  cabac_init_present_flag;
    UINT8  constrained_intra_pred_flag;
    UINT8  transform_skip_enabled_flag;
    UINT8  cu_qp_delta_enabled_flag;
    UINT8  pic_slice_chroma_qp_offsets_present_flag;
    UINT8  weighted_pred_flag;
    UINT8  weighted_bipred_flag;
    UINT8  transquant_bypass_enable_flag;
    UINT8  tiles_enabled_flag;
    UINT8  entropy_coding_sync_enabled_flag;
    UINT8  uniform_spacing_flag;
    UINT8  loop_filter_across_tiles_enabled_flag;
    UINT8  loop_filter_across_slices_enabled_flag;
    UINT8  deblocking_filter_control_present_flag;
    UINT8  deblocking_filter_override_enabled_flag;
    UINT8  pic_disable_deblocking_filter_flag;
    UINT8  pic_scaling_list_data_present_flag;
    UINT8  lists_modification_present_flag;
    UINT8  slice_segment_header_extension_present_flag;
    UINT8  pps_extension_flag;
    UINT8  pps_extension_data_flag;
    SINT32 pic_parameter_set_id;
    SINT32 seq_parameter_set_id;
    UINT32 num_extra_slice_header_bits;
    SINT32 num_ref_idx_l0_default_active;
    SINT32 num_ref_idx_l1_default_active;
    SINT32 pic_init_qp;
    SINT32 diff_cu_qp_delta_depth;
    SINT32 max_cu_qp_delta_depth;
    SINT32 pic_cb_qp_offset;
    SINT32 pic_cr_qp_offset;
    SINT32 num_tile_columns;
    SINT32 num_tile_rows;
    SINT32 pps_beta_offset_div2;
    SINT32 pps_tc_offset_div2;
    SINT32 log2_parallel_merge_level;
    SINT16 column_width[HEVC_MAX_TILE_COLUMNS];
    SINT16 row_height[HEVC_MAX_TILE_ROWS];
    SINT16 column_bd[HEVC_MAX_TILE_COLUMNS];
    SINT16 row_bd[HEVC_MAX_TILE_ROWS];

    HEVC_SCALING_LIST  scaling_list;
#ifdef MV_HEVC_SUPPORT
    HEVC_PPS_EXTENSION_SET_S pps_extension;
#endif
} HEVC_PIC_PARAM_SET_S;

typedef struct
{
    UINT8  first_slice_segment_in_pic_flag;
    UINT8  dependent_slice_segment_flag;
    UINT8  slice_sao_luma_flag;
    UINT8  slice_sao_chroma_flag;
    UINT8  slice_temporal_mvp_enable_flag;
    UINT8  num_ref_idx_active_override_flag;
    UINT8  mvd_l1_zero_flag;
    UINT8  cabac_init_flag;
    UINT8  collocated_from_l0_flag;
    UINT8  slice_disable_deblocking_filter_flag;
    UINT8  slice_loop_filter_across_slices_enabled_flag;
    SINT32 poc;
    SINT32 slice_qp;
    SINT32 slice_type;
    UINT32 nuh_temporal_id;
    UINT32 nal_unit_type;
    UINT32 view_id;
    SINT32 pic_parameter_set_id;
    SINT32 slice_segment_address;
    SINT32 collocated_ref_idx;
    SINT32 max_num_merge_cand;
    SINT32 slice_cb_qp_offset;
    SINT32 slice_cr_qp_offset;
    SINT32 slice_beta_offset_div2;
    SINT32 slice_tc_offset_div2;
    UINT32 listXsize[2];
    UINT32 num_ref_idx[3];
    SINT32 check_lt_msb[HEVC_MAX_NUM_REF_PICS];

    HEVC_PIC_TYPE new_pic_type;
    HEVC_PRED_WEIGHT_TABLE pred_weight_table;
    HEVC_SHORT_TERM_RPSET_S short_term_ref_pic_set;
    HEVC_REF_PIC_LISTS_MODDIFICATION ref_pic_lists_modification;
#ifdef MV_HEVC_SUPPORT
    HEVC_SLICE_EXTENSION_SET_S slice_extension;
#endif
} HEVC_SLICE_SEGMENT_HEADER;

typedef struct
{
    UINT32 structure;     // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT32 is_long_term;  // 0: not long term ref,  1: long term ref
    UINT32 is_short_term; // 0: not short term ref, 1: short term ref. BUT one pic cann't long and short.
    SINT32 AvgQp;
#ifdef MV_HEVC_SUPPORT
    SINT32 is_inter_layer;
#endif
    struct HEVC_FRAMESTORE_S *frame_store;
} HEVC_STORABLEPIC_S;

typedef struct HEVC_FRAMESTORE_S
{
    UINT8  non_existing;              // 0: real frame, 1: fake frame from creat lost ref pic
    UINT8  is_reference;              // 0: not ref,    1: for ref
    UINT8  is_displayed;              // 0: not insert, 1: already insert in vo queue
    UINT8  linear_en;
    UINT8  CompressEn;
    SINT32 poc;
    UINT32 pic_type;
    UINT32 err_level;
    UINT32 pmv_address_idc;
    UINT32 apc_idc;
    SINT32 logic_fs_id;
    UINT32 view_id;
    UINT32 apc_idc_il;
    UINT32 sei_field_flag;
    UINT32 sei_source_scan_type;
    HEVC_FS_STATE_E eFrameStoreState; // frame store state
    HEVC_FO_STATE_E eFirstFrameState; // first frame fast out state

    HEVC_STORABLEPIC_S  frame;
    IMAGE  fs_image;
} HEVC_FRAMESTORE_S;

typedef struct
{
    UINT8  is_ref_idc;
    UINT8  state;
    UINT32 nal_unit_type;
    UINT32 view_id;
    SINT32 thispoc;
    UINT32 pic_type;
    UINT32 pic_width;
    UINT32 pic_height;
    UINT32 start_count;
    UADDR  stream_base_addr;
    UINT32 pmv_address_idc;
    UINT32 err_level;
    UINT32 sei_field_flag;
    UINT32 sei_source_scan_type;
    UINT32 FrameStreamSize;
    UINT32 CurrentNalSize;
    HEVC_FRAMESTORE_S *frame_store;
    IMAGE  fs_image;
} HEVC_CURRPIC_S;

typedef struct
{
    UINT32 size;
    UINT32 used_size;
    UINT32 is_used[HEVC_APC_SIZE];
    UINT32 idc[HEVC_APC_SIZE];
    SINT32 poc[HEVC_APC_SIZE];
#ifdef MV_HEVC_SUPPORT
    SINT32 view_id[HEVC_APC_SIZE];
    SINT8  inter_layer_ref[HEVC_APC_SIZE];
#endif
} HEVC_APC_S;

typedef struct
{
    UINT32 size;
    UINT32 used_size;
    UINT32 max_long_term_pic_idx;
    UINT32 ltref_frames_in_buffer;
    UINT32 negative_ref_frames_in_buffer;
    UINT32 positive_ref_frames_in_buffer;
#ifdef MV_HEVC_SUPPORT
    UINT32 inter_size;
    UINT32 negative_inter_layer_ref_frames;
    UINT32 positive_inter_layer_ref_frames;
    HEVC_FRAMESTORE_S *fs_negative_inter_layer_ref[HEVC_MAX_DPB_NUM];
    HEVC_FRAMESTORE_S *fs_positive_inter_layer_ref[HEVC_MAX_DPB_NUM];
#endif
    HEVC_FRAMESTORE_S *fs[HEVC_MAX_DPB_NUM];
    HEVC_FRAMESTORE_S *fs_negative_ref[HEVC_MAX_DPB_NUM];
    HEVC_FRAMESTORE_S *fs_positive_ref[HEVC_MAX_DPB_NUM];
    HEVC_FRAMESTORE_S *fs_ltref[HEVC_MAX_DPB_NUM];
} HEVC_DPB_S;

typedef struct
{
    UINT8 *streamBuffer;       // [MAX_CODED_FRAME_SIZE], actual codebuffer for read bytes
    UINT32 bitstream_length;   // over codebuffer length, byte oriented, UVLC only
    UADDR  stream_phy_addr;    // physic addr of stream    unit: byte
    UINT32 valid_bitlen;       // valid pBs when dec slice data    unit: bit
    UINT32 bitsoffset;         // offset in 128 pBs when this segment stream start    unit: bit
    UINT32 bytespos;           // stream VDH will used start bytes ph addr, 4words/16bytes addr aligned     unit: byte
    SINT32 StreamID;           // stream seg id for release used
} HEVC_BITSTREAM_S;

typedef struct
{
    UINT8  nal_used_segment;     // which segment using decode
    UINT32 nal_bitoffset;
    UINT32 nal_segment;          // how many stream segment received in this nal
    UINT32 nal_trail_zero_bit_num;
    UINT32 nal_unit_type;
    UINT32 nal_ref_idc;
    UINT32 nal_layer_id;
    UINT32 nuh_temporal_id;
    UINT32 is_valid;
    UINT32 nal_integ;

    HEVC_BITSTREAM_S stream[2];
} HEVC_NALU_S;

typedef struct
{
    HEVC_NALU_S *slice_nal;
} HEVC_MSGSLOT_S;

typedef struct
{
    UINT8  uniform_spacing_flag;
    SINT32 num_tile_rows_minus1;
    SINT32 num_tile_columns_minus1;
    SINT32 row_height_minus1[HEVC_MAX_TILE_ROWS];
    SINT32 column_width_minus1[HEVC_MAX_TILE_COLUMNS];
} HEVC_TILE_INFO_S;

typedef struct
{
    SINT32 pic_width_in_luma_sample;
    SINT32 pic_height_in_luma_sample;
    SINT32 CtbSizeYLog2;
    SINT32 MinTbSizeLog2;
    SINT32 PicWidthInCtb;
    SINT32 PicHeithtInCtb;
} HEVC_PIC_SIZE_INFO_S;

typedef struct
{
    UINT8  last_pack_in_nal;
    UINT8 *p_stream;
    UADDR  strm_phy_addr;
    SINT32 SegCutState;
    SINT32 stream_len;
    SINT32 StreamID;
} HEVC_STREAM_PACKET;

typedef union
{
    HEVC_VIDEO_PARAM_SET_S VpsTmp;
    HEVC_SEQ_PARAM_SET_S   SpsTmp;
    HEVC_PIC_PARAM_SET_S   PpsTmp;
} HEVC_TMP_PARAM_SET_S;

typedef struct
{
    UINT8  bIsInit;
    UINT8  IsMultiLayers;
    UINT8  IsShvcType;
    UINT8  bNewSequence;
    UINT8  bNoOutputOfPriorPicsFlag[HEVC_MAX_NUM_LAYERS];
    UINT8  bNoRaslOutputFlag[HEVC_MAX_NUM_LAYERS];
    UINT8  bPPicFound;
    UINT8  bHaveNalNotDecoded;
    UINT8  bIsInsertEOPICNal;
    UINT8  IsStreamEndFlag;
    UINT8  PrevRAPIsBLA[HEVC_MAX_NUM_LAYERS];
    SINT8  bHaveIndependentSlice;
    SINT8  aucConvertToBit[HEVC_MAX_CU_SIZE + 1];
    UINT32 frame_rate;
    SINT32 NalArrayPos;
    SINT32 MaxSliceNum;
    SINT32 MaxVpsNum;
    SINT32 MaxSpsNum;
    SINT32 MaxPpsNum;
    SINT32 MaxSlotNum;
    UINT32 AllowStartDec;
    UINT32 CurrMsgSlotNum;
    UINT32 TotalFsNum;
    UINT32 TotalPmvNum;
    SINT32 PrevSlicePoc;
    SINT32 LastSlicePoc;
    UINT32 BitDepthY;
    UINT32 BitDepthC;
    UINT32 NumSlicePara;
    SINT32 LastSlicePpsId;
    SINT32 LastDisplayPoc[HEVC_MAX_NUM_LAYERS];
    SINT32 CurrVpsId[HEVC_MAX_NUM_LAYERS];
    SINT32 CurrSpsId[HEVC_MAX_NUM_LAYERS];
    SINT32 CurrPpsId[HEVC_MAX_NUM_LAYERS];
    SINT32 PocRandomAccess[HEVC_MAX_NUM_LAYERS];
    SINT32 PocCRA[HEVC_MAX_NUM_LAYERS];
    UINT32 TotalSliceNum;
    UINT32 TotalPicNum;
    UINT32 MaxBytesReceived;
    UINT32 AdvancedCfg;
    SINT32 ChanID;
    UINT32 OldDecMode;
    SINT32 prev_poc;
    SINT32 PrevSpsId;
    UINT32 PrevPicWidth;
    UINT32 PrevPicHeight;
    UINT32 PrevLog2CtbSizeY;
    UINT32 NewPicCounter;
    UINT32 PicOutCounter;
    SINT32 TotalFrameNum;
    SINT32 OutputFrameNum;
    UINT32 prev_pic_parameter_set_id;
    UINT32 general_profile_idc;
    UINT32 general_profile_compatibility_flag_1;
    UINT32 general_profile_compatibility_flag_2;
    UINT32 FakeFrmHeightInMb;
    UINT32 FakeFrmWidthInMb;
    UINT32 SCDWrapAround;
    UINT32 scalingListSize[4];
    UINT32 sigLastScanCG32x32[64];
    UINT32 qmatrix[4][6][16];
    UINT32 PmvStoreUsedFlag[HEVC_MAX_PMV_STORE];
    UINT32 scalingListNum[SCALING_LIST_SIZE_NUM];
    UINT32 scalingListDC[SCALING_LIST_SIZE_NUM][HEVC_SCALING_LIST_NUM];
#ifdef VFMW_HEVC_SED_ONLY_SUPPORT
    UINT32  SedOnlyEnable;
    UINT32  SegCutState;
    UINT32  SedOnlyTry;
    UINT32  SedOnlySucc;
    UINT32  NoNextSlice;
    UINT32  PrePicstate;
    UINT32  SedSliceNum;
    UINT32  PostPicCount;
#endif

#ifdef MV_HEVC_SUPPORT
    UINT32 LayerNum;
    VBOOL  IsMemArrangeDone;
    UINT32 LayerWidth[HEVC_MAX_NUM_LAYERS];
    UINT32 LayerHeight[HEVC_MAX_NUM_LAYERS];
    HEVC_VIEW_QUEUE_S          ViewQue[HEVC_MAX_NUM_LAYERS];
#endif

    BS                        *pBS;
    HEVC_VIDEO_PARAM_SET_S    *pVPS;
    HEVC_SEQ_PARAM_SET_S      *pSPS;
    HEVC_PIC_PARAM_SET_S      *pPPS;
    HEVC_SEQ_PARAM_SET_S      *pSEISPS;
    HEVC_NALU_S               *pCurrNal;
    HEVC_NALU_S               *pLastNal;
    HEVC_VIDEO_PARAM_SET_S    *pCurrVPS;
    HEVC_SEQ_PARAM_SET_S      *pCurrSPS;
    HEVC_PIC_PARAM_SET_S      *pCurrPPS;
    HEVC_MSGSLOT_S            *pMsgSlot;
    HEVC_NALU_S               *pNalArray;
    SYNTAX_EXTRA_DATA_S       *pstExtraData;
    HEVC_DEC_SLICE_PARAM_S    *pDecSlicePara;
    HEVC_DEC_PIC_PARAM_S      *pHevcDecParam;
    HEVC_STORABLEPIC_S        *pListX[2][HEVC_MAX_LIST_SIZE];

    BS                         Bs;
    HEVC_DPB_S                 DPB;
    HEVC_SEI_PARAM_SET_S       SEI;
    HEVC_CURRPIC_S             CurrPic;
    HEVC_SLICE_SEGMENT_HEADER  CurrSlice;
    IMAGE_VO_QUEUE             ImageQue;
    HEVC_DEC_PIC_PARAM_S       DecPicPara;
    HEVC_SEI_PTS_PARSER_S      PtsParser;
    HEVC_FIRST_FRAME_STATE_E   FirstFrameState;
    HEVC_SLICE_SEGMENT_HEADER  IndependentSlice;
    HEVC_APC_S                 APC[HEVC_MAX_NUM_LAYERS];
    HEVC_FRAMESTORE_S          FrameStore[HEVC_MAX_FRAME_STORE];

} HEVC_CTX_S;


/*************************** Function Declare *************************/
SINT32 HEVCDEC_Init(HEVC_CTX_S *pHevcCtx, SYNTAX_EXTRA_DATA_S *pstExtraData);
VOID   HEVC_InitDecPara(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_ClearAll(HEVC_CTX_S *pHevcCtx, SINT32 flag);
VOID   HEVC_InitScalingOrderTable(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_InitSigLastScan(HEVC_CTX_S *pHevcCtx, UINT32 *pBuffZ, UINT32 *pBuffH, UINT32 *pBuffV, UINT32 *pBuffD, SINT32 iWidth, SINT32 iHeight, SINT32 iDepth);
UINT8 *HEVC_GetScalingListDefaultAddress(UINT32 sizeId, UINT32 matrixId);
SINT32 HEVCDEC_DecodePacket(HEVC_CTX_S *pHevcCtx, HEVC_STREAM_PACKET *pPacket);
SINT32 HEVC_DecOneNal(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecVPS(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecSPS(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecPPS(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecSEI(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecSlice(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecSliceSegmentHeader(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecVDM(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_VpsSpsPpsCheck(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_IsNewPic(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecPTL(HEVC_CTX_S *pHevcCtx, HEVC_PROFILE_TIER_LEVEL_S *pPTL, SINT32 ProfilePresentFlag, SINT32 MaxNumSubLayersMinus1);
SINT32 HEVC_DecScalingListData(HEVC_CTX_S *pHevcCtx, HEVC_SCALING_LIST *pScalingList);
SINT32 HEVC_DecShortTermRefPicSet(HEVC_CTX_S *pHevcCtx, HEVC_SEQ_PARAM_SET_S *pSPS, HEVC_SHORT_TERM_RPSET_S *pShortTermRpset, UINT32 idx);
SINT32 HEVC_DecRefPicListsModification(HEVC_CTX_S *pHevcCtx, HEVC_SLICE_SEGMENT_HEADER *pSlice, HEVC_REF_PIC_LISTS_MODDIFICATION *pRpListModification, SINT32 numRpsCurrTempList);
SINT32 HEVC_DecPredWeightTable(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_DecHrdParam(HEVC_CTX_S *pHevcCtx, HEVC_HRD_PARAM_SET_S *pHrd, UINT8 commonInfPresentFlag, UINT32 maxNumSubLayersMinus1);
SINT32 HEVC_DecVuiParam(HEVC_CTX_S *pHevcCtx, HEVC_VUI_PARAM_SET_S *pVui, HEVC_SEQ_PARAM_SET_S *pSps);
SINT32 HEVC_MoreRbspData(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_More_Rbsp_Data(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_WritePicMsg(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_WriteSliceMsg(HEVC_CTX_S *pHevcCtx);
UINT32 *HEVC_GetVirAddr(UINT32 Dn, UINT32 *pbase_vir_addr);
UADDR  HEVC_GetPhyAddr(UINT32 Dn, UADDR base_phy_addr);
SINT32 HEVC_InitPic(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_InitDPB(HEVC_CTX_S *pHevcCtx, UINT32 ReRangeFlag);
SINT32 HEVC_StorePicInDPB(HEVC_CTX_S *pHevcCtx, LUMA_INFO_S *pLumaInfo);
SINT32 HEVC_DecList(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_AllocFrameStore(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_GetReRangeFlag(HEVC_CTX_S *pHevcCtx, SINT32 OldWidth, SINT32 OldHeight, SINT32 OldLog2CtbSizeY, SINT32 DpbSizeChanged);
VOID   HEVC_GetBackPicFromVOQueue(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_RemoveDummyFrame(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_CheckThatAllRefPicsAreAvailable(HEVC_CTX_S *pHevcCtx, SINT32 *piLostPoc);
SINT32 HEVC_CreateLostPicture(HEVC_CTX_S *pHevcCtx, SINT32 iLostPoc);
VOID   HEVC_ApplyReferencePictureSet(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_RemoveApcStore(HEVC_CTX_S *pHevcCtx, UINT32 pos);
VOID   HEVC_RemoveUnusedApcStore(HEVC_CTX_S *pHevcCtx);
UINT32 HEVC_RemoveUnUsedFrameStore(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_RemoveFrameStoreOutDPB(HEVC_CTX_S *pHevcCtx, UINT32 pos);
VOID   HEVC_GetMinPOC(HEVC_CTX_S *pHevcCtx, SINT32 *poc, UINT32 *pos);
SINT32 HEVC_OutputFrmFromDPB(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_FlushOutputFrmFromDPB(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_EmptyFrmFromDPB(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_OutputFrmToVO(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S *pFrameStore);
SINT32 HEVC_InsertFrmInDPB(HEVC_CTX_S *pHevcCtx, UINT32 pos, HEVC_CURRPIC_S *pCurrPic);
SINT32 HEVC_GetAPC(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S *pFrameStore);
VOID   HEVC_UpdateReflist(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_UpdateLTReflist(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_InitListX(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_FindMinRefIdx(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_SetScalingList(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_SetDefaultScalingList(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_CalScalingList(HEVC_CTX_S *pHevcCtx, UINT8 *pScalingListCoef, UINT32 ListSize, UINT32 MatrixId);
SINT32 HEVC_SeiMessage(HEVC_CTX_S *pHevcCtx, HEVC_SEI_PARAM_SET_S *pSEI, HEVC_SEQ_PARAM_SET_S *pSPS);
SINT32 HEVC_Sei_Payload(HEVC_CTX_S *pHevcCtx, HEVC_SEI_PARAM_SET_S *pSEI, HEVC_SEQ_PARAM_SET_S *pSPS, UINT32 payloadType, UINT32 payloadSize);
#ifdef DOLBY_VISION_HDR_SUPPORT
VOID   HEVC_Sei_ParsePts_Init(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_Sei_Get_Dpb_Output_Time(HEVC_CTX_S *pHevcCtx, HEVC_SEI_PIC_TIMMING_S *pPic, HEVC_VUI_PARAM_SET_S *pVui);
VOID   HEVC_Get_Last_IDR_Frame_Info(HEVC_CTX_S *pHevcCtx, UINT32 nal_unit_type);
VOID   HEVC_Sei_Get_Frame_Pts(HEVC_CTX_S *pHevcCtx);
#endif
UINT32 HEVC_Sei_More_Data_In_Payload( HEVC_CTX_S *pHevcCtx, UINT32 payloadSize);
UINT32 HEVC_Sei_Payload_Extension_Present( HEVC_CTX_S *pHevcCtx, UINT32 payloadSize);
SINT32 HEVC_Sei_Decoded_Picture_Hash( HEVC_CTX_S *pHevcCtx, HEVC_SEI_DECODED_PICTURE_HASH_S *pDec);
SINT32 HEVC_Sei_Scalable_Nesting(HEVC_CTX_S *pHevcCtx, HEVC_SEI_PARAM_SET_S *pSEI, HEVC_SEQ_PARAM_SET_S *pSPS, UINT32 payloadSize);
SINT32 HEVC_Sei_Structure_Of_Pictures_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_SOP_INFO_S *pSop, UINT32 payloadSize);
SINT32 HEVC_Sei_Tone_Mapping_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_TONE_MAPPING_INFO_S *pTon);
SINT32 HEVC_Sei_Region_Refresh_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_REGION_REFRESH_INFO_S *pReg);
SINT32 HEVC_Sei_Mastering_Display_Colour_Volume(HEVC_CTX_S *pHevcCtx, HEVC_SEI_MASTERING_DISPLAY_COLOUR_VOLUME_S *pReg);
SINT32 HEVC_Sei_Content_Light_Level_Information(HEVC_CTX_S *pHevcCtx, HEVC_SEI_CONTENT_LIGHT_LEVEL_INFO_S *pReg);
SINT32 HEVC_Sei_HLGHDR_Comapitibility_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_HLG_COMPATIBLE_INFO_S *pReg);
SINT32 HEVC_Sei_Temporal_Sub_Layer_Zero_Index(HEVC_CTX_S *pHevcCtx, HEVC_SEI_TEMPORAL_SUB_LAYER_S *pTem);
SINT32 HEVC_Sei_Display_Orientation(HEVC_CTX_S *pHevcCtx, HEVC_SEI_DISPLAY_ORIENTATION_S *pDis);
SINT32 HEVC_Sei_Frame_Packing_Arrangement(HEVC_CTX_S *pHevcCtx, HEVC_SEI_FRAME_PACKING_ARRANGEMENT_S *pFrm);
SINT32 HEVC_Sei_Recovery_Point(HEVC_CTX_S *pHevcCtx, HEVC_SEI_RECOVERY_POINT_S *pRec);
SINT32 HEVC_Sei_Dec_Unit_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_DECODEING_UNIT_INFO_S *pDec, HEVC_HRD_PARAM_SET_S *pHrd);
SINT32 HEVC_Sei_Active_Param_sets(HEVC_CTX_S *pHevcCtx, HEVC_SEI_ACTIVE_PARAMETER_SET_S *pAct);
SINT32 HEVC_Sei_Buf_Period(HEVC_CTX_S *pHevcCtx, HEVC_SEI_BUF_PERIOD_S *pBuf, HEVC_HRD_PARAM_SET_S *pHrd);
SINT32 HEVC_Sei_Pic_Timming(HEVC_CTX_S *pHevcCtx, HEVC_SEI_PIC_TIMMING_S *pPic, HEVC_VUI_PARAM_SET_S *pVui);
SINT32 HEVC_Sei_User_Data_Registered_Itu_T_T35(HEVC_CTX_S *pHevcCtx, HEVC_SEI_USER_DATA_REG_ITU_T_T35_S *pItu_T35, UINT32 payloadSize);
SINT32 HEVC_Sei_Color_Remapping_Info(HEVC_CTX_S *pHevcCtx, HEVC_SEI_COLOR_REMAPPING_INFO_S *pRemapping);
SINT32 HEVC_Sei_User_Data_Unregistered(HEVC_CTX_S *pHevcCtx, HEVC_SEI_USER_DATA_UNREG_S *pData, UINT32 payloadSize);
VOID   HEVC_CalcStreamBits(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_StreamAddr_ReW(HEVC_CTX_S *pHevcCtx, UADDR new_stream_base_addr, UADDR old_stream_base_addr);
SINT32 HEVC_ReadByteAlignment(HEVC_CTX_S *pHevcCtx);
UINT8  HEVC_GetRapPicFlag(HEVC_CTX_S *pHevcCtx);
UINT8  HEVC_GetIdrPicFlag(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_FindTrailZeros(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_ReceivePacket(HEVC_CTX_S *pHevcCtx, HEVC_STREAM_PACKET *pPacket);
VOID   HEVC_CombinePacket(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_ReleaseNAL(SINT32 ChanID, HEVC_NALU_S *p_nal);
SINT32 HEVC_CheckFrameStore(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S *pFrameStore);
VOID   HEVC_GetImagePara(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S *pFrameStore);
SINT32 HEVC_DECRecycleImage(HEVC_CTX_S *pHevcCtx, UINT32 PicID);
SINT32 HEVC_CheckOutputImage(HEVC_CTX_S *pHevcCtx, UINT32 PicID);
VOID   HEVC_InitDecBuffers(HEVC_CTX_S *pHevcCtx);
UINT8  HEVC_IsEosNal(HEVC_CTX_S *pHevcCtx);
UINT32 HEVC_u_v(BS *pBs, SINT32 v, SINT8 *Name);
UINT32 HEVC_f_v(BS *pBs, SINT32 v, SINT8 *Name);
UINT32 HEVC_ue_v(BS *pBs, SINT8 *Name);
SINT32 HEVC_se_v(BS *pBs, SINT8 *Name);
SINT32 HEVCDEC_GetImageBuffer( HEVC_CTX_S *pHevcCtx );
SINT32 HEVC_IsNewPicNal( SINT32 *pNewPicDetector, UINT8 *pu8 );
VOID   HEVCDEC_Exit(VOID);
UINT32 HEVCDEC_VDMPostProc( HEVC_CTX_S *pHevcCtx, SINT32 ErrRatio, SINT32 CalledByISR, LUMA_INFO_S *pLumaInfo, SINT32 ModuleLowlyEnable, SINT32 VdhId);
SINT32 HEVC_IsOutDPB(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S  *pFrameStore);
SINT32 HEVC_ClearCurrNal(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_ClearDPB(HEVC_CTX_S *pHevcCtx);
UINT32 HEVC_FrameStoreRefFlg(const HEVC_FRAMESTORE_S *pFS);
SINT32 HEVC_ClearAllSlice(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_ClearCurrSlice(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_ClearAllNal(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_ClearCurrPic(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_FlushDPB(HEVC_CTX_S *pHevcCtx);
VOID   HEVC_UnMarkFrameStoreRef(HEVC_CTX_S *pHevcCtx, HEVC_FRAMESTORE_S *pFrameStore);
SINT32 HEVC_OutputOneFrmFromDPB(HEVC_CTX_S *pHevcCtx, UINT32 pos);
SINT32 HEVC_HaveSliceToDec(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_InquireSliceProperty(HEVC_CTX_S *pHevcCtx, SINT32 *IsNewPic, SINT32 *IsSizeChanged);
SINT32 HEVC_GetPicStreamSize(HEVC_CTX_S *pHevcCtx);
SINT32 HEVCDEC_GetRemainImg(HEVC_CTX_S *pHevcCtx);
SINT32 HEVCDEC_GetImageWidth(HEVC_CTX_S *pHevcCtx);
SINT32 HEVCDEC_GetImageHeight(HEVC_CTX_S *pHevcCtx);
SINT32 HEVC_CRAOutputFrame(HEVC_CTX_S *pHevcCtx);
#ifdef VFMW_HEVC_SED_ONLY_SUPPORT
UINT32 HEVCDEC_VDMProcSedOnly( HEVC_CTX_S *pHevcCtx, SINT32 VdhId);
#endif
#ifdef MV_HEVC_SUPPORT
UINT32 HEVC_CheckVpsExtOverlap(HEVC_VPS_EXTENSION_SET_S *pVPSExt);
UINT32 HEVC_CheckPpsExtOverlap(HEVC_PPS_EXTENSION_SET_S *pPPSExt);
UINT32 HEVC_CheckSliceExtOverlap(HEVC_SLICE_EXTENSION_SET_S *pSlcExt);
#endif

#ifdef __cplusplus
}
#endif

#endif
