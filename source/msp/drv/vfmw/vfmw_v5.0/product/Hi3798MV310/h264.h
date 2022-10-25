#ifndef __H264_H__
#define __H264_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "basedef.h"
#include "vfmw.h"
#include "public.h"
#include "bitstream.h"
#include "vdm_hal.h"

/************************ se err check define *********************/
#define   SE_ERR_CHECK           \
    do                               \
    {                                \
        if (pH264Ctx->SeErrFlg)      \
        {                            \
            return H264_ERR;         \
        }                            \
    } while(0)



#define   H264_ERR_FS_OUT_AGAIN   (-3)
#define   H264_NOTDEC             (-2)    //��ʾH264DEC_DecodePacket()������һ��NALû�н���ͷ����ˣ��´ε��ò�����������
#define   H264_ERR                (-1)
#define   H264_OK                 (0)
#define   H264_ALREADY_OUT        (1)
#define   H264_OUTPUT_FAIL        (2)
#define   H264_MEET_EOS           (3)

/********************* error information define *******************/
#define   SPS_ERR            -1
#define   SE_ERR             -1
#define   PPS_ERR            -1
#define   VLC_CODE_ERR       -1
#define   FLC_ERR            -1
#define   IDR_ERR            -1
#define   SLICE_HEADER_ERR   -1
#define   MMCO_NOT_EQUAL     -1
#define   RECOVERPOINT_ERR   -1
#define   REDUNDANTPIC_ERR   -1
#define   PIC_INITIAL_ERR    -1
#define   INITDPB_ERR        -1
#define   OUTPUT_ERR         -1

/******************* some define of start contrl ******************/
#define   START_FRAME                         0

#define   MAX_BYTES_START                     (512*1024)    // 512*1024 bytes received, start VDM to dec
#define   GET_ONE_NALU_SIZE                   (4*1024) //SCD_SEG_BLANK_LEN           // ƴ������С����

/***************************** define *****************************/
#define   PIC_DECODING                        1
#define   EMPTY                               0

#define   BASELINE                            66
#define   MAINPROFILE                         77
#define   EXTENDED                            88
#define   HIGHPROFILE                         100      //!< YUV 4:2:0/8 "High"
#define   HIGH10P                             110      //!< YUV 4:2:0/10 "High 10"
#define   HIGH422P                            122      //!< YUV 4:2:2/10 "High 4:2:2"
#define   HIGH444P                            144      //!< YUV 4:4:4/12 "High 4:4:4"
#define   SCALABLE_BASELINE_PROFILE           83       //add for svc base profile
#define   SCALABLE_HIGH_PROFILE               86       //add for svc high profile

// define para
#define   FRAME                               0
#define   TOP_FIELD                           1
#define   BOTTOM_FIELD                        2
#define   FIELD_PAIR                          3

#define   P_SLICE                             0
#define   B_SLICE                             1
#define   I_SLICE                             2

#define   MAX_DPB_LEN                         33
#define   MAX_LIST_SIZE                       33
#define   MAX_FRAME_STORE                     40   // Maximun vdm slot
#define   MAX_PMV_STORE                       17   // 16 for max dpb + 1 for dec_pic
#define   VO_HOLD_FRAME_NUM                   3    // vo hold the number of frames
#define   MAX_MMCO_LEN                        100

#define   NALU_TYPE_NULL       0
#define   NALU_TYPE_SLICE      1
#define   NALU_TYPE_DPA        2
#define   NALU_TYPE_DPB        3
#define   NALU_TYPE_DPC        4
#define   NALU_TYPE_IDR        5
#define   NALU_TYPE_SEI        6
#define   NALU_TYPE_SPS        7
#define   NALU_TYPE_PPS        8
#define   NALU_TYPE_AUD        9
#define   NALU_TYPE_EOSEQ     10
#define   NALU_TYPE_EOSTREAM  11
#define   NALU_TYPE_FILL      12
#define   NALU_TYPE_SPSEXT    13
#define   NALU_TYPE_AUX       19
#define   NALU_TYPE_EOPIC     30              // end curr pic, followed by 0x4853504943454E44
#define   NALU_TYPE_TSTEND    31              // end test, start last pic
#define   NALU_TYPE_SUB_SPS   15
#define   NALU_TYPE_SLC_EXT   20
#define   NALU_TYPE_RESERVED  23              //Reserved [20,23]
#define   NALU_TYPE_UNSPECIFIED 24
#define   NALU_TYPE_END       31              //Unspecified [24,31]

/*�������ģʽ*/
#define  IMODE                2               // only dec I pic
#define  IPMODE               1               // dec I pic, p pic and ref b pic, no ref b pic not dec
#define  IPBMODE              0               // all pic dec

// for ue_v() and se_v()
#define ue_vld(code, bits, val, zeros)            \
    do                                                \
    {                                                 \
        (bits) = ((zeros)<<1) + 1;                    \
        (val)  = ((code)>>(32-(bits))) - 1;           \
    } while(0)

#define se_vld(code, bits, val, zeros)            \
    do                                                \
    {                                                 \
        SINT32 tmp;                                   \
        (bits) = ((zeros)<<1) + 1;                    \
        tmp    = ((code)>>(32-(bits)))>>1;            \
        (val)  = ((code)>>(32-(bits)))&1?-1*tmp:tmp;  \
    } while(0)

/************************ structure define ************************/

typedef enum
{
    SEI_BUFFERING_PERIOD = 0,
    SEI_PIC_TIMING,
    SEI_PAN_SCAN_RECT,
    SEI_FILLER_PAYLOAD,
    SEI_USER_DATA_REGISTERED_ITU_T_T35,
    SEI_USER_DATA_UNREGISTERED,
    SEI_RECOVERY_POINT,
    SEI_DEC_REF_PIC_MARKING_REPETITION,
    SEI_SPARE_PIC,
    SEI_SCENE_INFO,
    SEI_SUB_SEQ_INFO,
    SEI_SUB_SEQ_LAYER_CHARACTERISTICS,
    SEI_SUB_SEQ_CHARACTERISTICS,
    SEI_FULL_FRAME_FREEZE,
    SEI_FULL_FRAME_FREEZE_RELEASE,
    SEI_FULL_FRAME_SNAPSHOT,
    SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,
    SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,
    SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,
    SEI_FILM_GRAIN_CHARACTERISTICS,
    SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,
    SEI_STEREO_VIDEO_INFO,
    SEI_FRAME_PACKING_ARRANGEMENT = 45,
    SEI_BVT_USER_DATA = 0xf0,
    SEI_MAX_ELEMENTS  // number of maximum syntax elements
} SEI_type;

typedef struct
{
    UINT8  *alloc_stream_word_addr;
    UINT8  *align_stream_word_addr;
    UINT8  *tab_base_addr;
    UINT32  used_words;
} H264DEC_BitStreamBuffer;

typedef struct
{
    UINT8  *streamBuffer;       // [MAX_CODED_FRAME_SIZE], actual codebuffer for read bytes
    UINT32  bitstream_length;   // over codebuffer length, byte oriented, UVLC only
    UADDR   stream_phy_addr;    // physic addr of stream
    UINT32  valid_bitlen;       // valid bits when dec slice data
    UINT32  bitsoffset;         // offset in 32 bits when this segment stream start
    UINT32  bytespos;           // stream VDM will used start bytes ph addr, word addr aligned
    SINT32  StreamID;
} H264_BITSTREAM_S;

typedef struct
{
    UINT8   nal_used_segment;     // which segment using decode
    UINT8   is_valid;
    UINT8   nal_unit_type;
    UINT8   svc_extension_flag;
    UINT8   nal_integ;
    H264_BITSTREAM_S  stream[2];
    UINT32  nal_bitoffset;
    UINT32  nal_segment;          // how many stream segment received in this nal
    UINT32  nal_trail_zero_bit_num;
    UINT32  nal_ref_idc;
    UINT32  forbidden_bit;
    UINT64  PTS;
} H264_NALU_S;

typedef struct
{
    UINT8   cbr_flag[32];
    UINT8   bit_rate_scale;
    UINT8   cpb_size_scale;
    UINT32  cpb_cnt_minus1;
    UINT32  bit_rate_value_minus1[32];
    UINT32  cpb_size_value_minus1[32];
    UINT32  initial_cpb_removal_delay_length_minus1;
    UINT32  cpb_removal_delay_length_minus1;
    UINT32  dpb_output_delay_length_minus1;
    UINT32  time_offset_length;
} HRD_PARAMETERS_S;

typedef struct
{
    UINT8   aspect_ratio_info_present_flag;
    UINT8   overscan_info_present_flag;
    UINT8   overscan_appropriate_flag;
    UINT8   video_signal_type_present_flag;
    UINT8   video_full_range_flag;
    UINT8   colour_description_present_flag;
    UINT8   chroma_location_info_present_flag;
    UINT8   nal_hrd_parameters_present_flag;
    UINT8   timing_info_present_flag;
    UINT8   fixed_frame_rate_flag;
    UINT8   vcl_hrd_parameters_present_flag;
    UINT8   pic_struct_present_flag;
    UINT8   bitstream_restriction_flag;
    UINT8   motion_vectors_over_pic_boundaries_flag;
    UINT8   low_delay_hrd_flag;
    UINT8   aspect_ratio_idc;
    UINT32  sar_width;
    UINT32  sar_height;
    UINT32  aspect_ratio;
    UINT32  video_format;
    UINT32  colour_primaries;
    UINT32  transfer_characteristics;
    UINT32  matrix_coefficients;
    UINT32  chroma_sample_loc_type_top_field;
    UINT32  chroma_sample_loc_type_bottom_field;
    UINT32  num_units_in_tick;
    UINT32  time_scale;
    UINT32  max_bytes_per_pic_denom;
    UINT32  max_bits_per_mb_denom;
    UINT32  log2_max_mv_length_vertical;
    UINT32  log2_max_mv_length_horizontal;
    UINT32  num_reorder_frames;
    UINT32  max_dec_frame_buffering;
    HRD_PARAMETERS_S  nal_hrd_parameters;
    HRD_PARAMETERS_S  vcl_hrd_parameters;
} VUI_SEQ_PARAMETERS_S;

typedef struct
{
    UINT8   constrained_set0_flag;                 // u(1)
    UINT8   constrained_set1_flag;                 // u(1)
    UINT8   constrained_set2_flag;                 // u(1)
    UINT8   constrained_set3_flag;                 // u(1)
    SINT8   seq_scaling_list_present_flag[12];     // u(1)
    UINT8   delta_pic_order_always_zero_flag;      // u(1)
    UINT8   gaps_in_frame_num_value_allowed_flag;  // u(1)
    UINT8   frame_mbs_only_flag;                   // u(1)
    UINT8   mb_adaptive_frame_field_flag;          // u(1)
    UINT8   direct_8x8_inference_flag;             // u(1)
    UINT8   frame_cropping_flag;                   // u(1)
    UINT8   vui_parameters_present_flag;           // u(1)
    UINT8   is_valid;                              // the sps content of this sps_id is geted or not
    UINT8   is_refreshed;                          // �Ƿ���£���ʼֵΪ0
    UINT8   seq_scaling_matrix_present_flag;

    UINT32  profile_idc;                           // u(8)
    UINT32  level_idc;                             // u(8)
    UINT32  seq_parameter_set_id;                  // ue(v)
    UINT32  chroma_format_idc;
    UINT32  bit_depth_luma;                        // ue(v)
    UINT32  bit_depth_chroma;                      // ue(v)
    SINT32  ScalingList4x4[6][16];                 // se(v)
    SINT32  ScalingList8x8[6][64];                 // se(v)
    UINT32  qmatrix4x4[6][4];                      // 16 ��bytesƴ��4words��
    UINT32  qmatrix8x8[2][16];                     // 64 ��bytesƴ��16words��
    UINT32  log2_max_frame_num_minus4;             // ue(v)
    UINT32  pic_order_cnt_type;                    // ue(v)
    UINT32  log2_max_pic_order_cnt_lsb_minus4;     // ue(v)
    SINT32  offset_for_non_ref_pic;                // se(v)
    SINT32  offset_for_top_to_bottom_field;        // se(v)
    UINT32  num_ref_frames_in_pic_order_cnt_cycle; // ue(v)
    SINT32  offset_for_ref_frame[256];             // se(v)
    UINT32  num_ref_frames;                        // ue(v)
    UINT32  pic_width_in_mbs_minus1;               // ue(v)
    UINT32  pic_height_in_map_units_minus1;        // ue(v)
    UINT32  frame_crop_left_offset;                // ue(v)
    UINT32  frame_crop_right_offset;               // ue(v)
    UINT32  frame_crop_top_offset;                 // ue(v)
    UINT32  frame_crop_bottom_offset;              // ue(v)
    UINT32  dpb_size_plus1;                        // calculate from level_idc
    UINT32  disp_width;
    UINT32  disp_height;
    UINT32  disp_center_x;
    UINT32  disp_center_y;
    VUI_SEQ_PARAMETERS_S  vui_seq_parameters;
} H264_SPS_S;

typedef struct
{
    UINT8   entropy_coding_mode_flag;                 // u(1)
    UINT8   pic_order_present_flag;                   // u(1)
    UINT8   weighted_pred_flag;                        // u(1)
    UINT8   deblocking_filter_control_present_flag; // u(1)
    UINT8   constrained_intra_pred_flag;             // u(1)
    SINT8   pic_scaling_list_present_flag[12];       // u(1)
    UINT8   redundant_pic_cnt_present_flag;          // u(1)
    UINT8   pic_scaling_matrix_present_flag;
    UINT8   is_valid;                               // the Pps content of this Pps_id is geted or not
    UINT8   is_refreshed;
    UINT32  pic_parameter_set_id;                   // ue(v)
    UINT32  seq_parameter_set_id;                   // ue(v)
    UINT32  num_slice_groups_minus1;                // ue(v)
    UINT32  num_ref_idx_l0_active_minus1;           // ue(v)
    UINT32  num_ref_idx_l1_active_minus1;           // ue(v)
    UINT32  weighted_bipred_idc;                    // u(2)
    SINT32  pic_init_qp_minus26;                    // se(v)
    SINT32  chroma_qp_index_offset;                 // se(v)
    SINT32  second_chroma_qp_index_offset;
    UINT32  transform_8x8_mode_flag;
    SINT32  ScalingList4x4[6][16];                  // se(v)
    SINT32  ScalingList8x8[6][64];                  // se(v)
    UINT32  qmatrix4x4[6][4];                       // 16 ��bytesƴ��4words��
    UINT32  qmatrix8x8[2][16];                      // 64 ��bytesƴ��16words��
} H264_PPS_S;

typedef struct
{
    UINT8   field_pic_flag;
    UINT8   bottom_field_flag;
    UINT8   nal_unit_type;
    UINT32  seq_parameter_set_id;
    UINT32  pic_parameter_set_id;
    UINT32  nal_ref_idc;
    UINT32  frame_num;
    UINT32  idr_pic_id;
    UINT32  pic_oder_cnt_lsb;
    SINT32  delta_pic_oder_cnt_bottom;
    SINT32  delta_pic_order_cnt[2];
    UINT32  first_mb_in_slice;
} H264_PREVSLICE_S;

typedef struct
{
    UINT8   slice_type;
    UINT8   field_pic_flag;
    UINT8   bottom_field_flag;
    UINT8   nal_unit_type;
    UINT8   MbaffFrameFlag;
    UINT8   new_pic_flag;
    UINT8   direct_spatial_mv_pred_flag;
    UINT8   apply_weights_flag;
    UINT32  pic_parameter_set_id;
    UINT32  prev_frame_num;
    UINT32  frame_num;
    UINT32  len;
    UINT32  valid_bitlen;
    UINT32  nal_ref_idc;
    UINT32  bit_num;
    UINT32  idr_pic_id;
    UINT32  listXsize[2];
    UINT32  first_mb_in_slice;
    UINT32  num_ref_idx_l0_active_minus1;
    UINT32  num_ref_idx_l1_active_minus1;
    UINT32  luma_log2_weight_denom;
    UINT32  chroma_log2_weight_denom;
    SINT32  wp_weight_l0_y[32];
    SINT32  wp_weight_l0_u[32];
    SINT32  wp_weight_l0_v[32];
    SINT32  wp_weight_l1_y[32];
    SINT32  wp_weight_l1_u[32];
    SINT32  wp_weight_l1_v[32];
    SINT32  wp_offset_l0_y[32];
    SINT32  wp_offset_l0_u[32];
    SINT32  wp_offset_l0_v[32];
    SINT32  wp_offset_l1_y[32];
    SINT32  wp_offset_l1_u[32];
    SINT32  wp_offset_l1_v[32];
    UINT32  cabac_init_idc;
    SINT32  slice_qp_delta;
    UINT32  disable_deblocking_filter_idc;
    SINT32  slice_alpha_c0_offset_div2;
    SINT32  slice_beta_offset_div2;
    SINT32  picid_refidx0; // ��ǰslice��list0�е�һ��Ԫ�ض�Ӧ��֡���λ�ţ�������Ч
    SINT32  picid_nearpoc; // ��ǰslice��dpb���ҵ���poc���������֡��Ĳ�λ�ţ�������Ч
    UINT64  PTS;
} H264_SLICE_S;

typedef struct
{
    /* for POC mode 0:*/
    UINT32  pic_order_cnt_lsb;
    SINT32  delta_pic_order_cnt_bottom;
    SINT32  PrevPicOrderCntMsb;
    UINT32  PrevPicOrderCntLsb;
    SINT32  PicOrderCntMsb;
    SINT32  last_pic_order_cnt_lsb;
    SINT32  last_has_mmco_5;
    SINT32  last_pic_bottom_field;
    SINT32  toppoc;
    SINT32  bottompoc;
    SINT32  framepoc;
    SINT32  ThisPOC;
    /* for POC mode 1:*/
    SINT32  delta_pic_order_cnt[2];
    UINT32  AbsFrameNum;
    UINT32  PreviousFrameNum;
    UINT32  frame_num;
    UINT32  FrameNumOffset;
    SINT32  PrevFrameNumOffset;
    /* for POC mode 2:*/
    SINT32  FrameNumInPicOrderCntCycle;
    SINT32  PicOrderCntCycleCnt;
    SINT32  ExpectedPicOrderCnt;
    SINT32  ExpectedDeltaPerPicOrderCntCycle;
} H264_POC_S;

typedef struct
{
    UINT8   ref_pic_list_reordering_flag_l0;
    UINT8   ref_pic_list_reordering_flag_l1;
    UINT32  reordering_of_pic_nums_idc_l0[33];
    UINT32  reordering_of_pic_nums_idc_l1[33];
    UINT32  abs_diff_pic_num_minus1_l0[33];
    UINT32  abs_diff_pic_num_minus1_l1[33];
    UINT32  long_term_pic_idx_l0[32];
    UINT32  long_term_pic_idx_l1[32];
} H264_REORDER_S;

typedef struct
{
    UINT32  memory_management_control_operation;
    UINT32  difference_of_pic_nums_minus1;
    UINT32  long_term_pic_num;
    UINT32  long_term_frame_idx;
    UINT32  max_long_term_frame_idx_plus1;
} H264_MMCO_S;

typedef struct
{
    UINT8   is_valid;
    UINT8   no_output_of_prior_pics_flag;
    UINT8   long_term_reference_flag;
    UINT8   adaptive_ref_pic_marking_mode_flag;
    H264_MMCO_S  MMCO[MAX_MMCO_LEN];
} H264_MARK_S;

typedef struct
{
    SINT8  frame_packing_dec_ok;
    SINT8  frame_packing_arrangement_cancel_flag;
    SINT8  frame_packing_arrangement_extension_flag;
    SINT8  quincunx_sampling_flag;
    SINT8  spatial_flipping_flag;
    SINT8  frame0_flipped_flag;
    SINT8  field_views_flag;
    SINT8  current_frame_is_frame0_flag;
    SINT8  frame0_self_contained_flag;
    SINT8  frame1_self_contained_flag;
    SINT8  frame0_grid_position_x;
    SINT8  frame0_grid_position_y;
    SINT8  frame1_grid_position_x;
    SINT8  frame1_grid_position_y;
    SINT32 frame_packing_arrangement_type;
    SINT32 content_interpretation_type;
    SINT32 frame_packing_arrangement_id;
    SINT32 frame_packing_arrangement_reserved_byte;
    SINT32 frame_packing_arrangement_repetition_period;
} H264_FRAME_PACKING_ARRANGEMENT_S;

typedef struct H264_SEI_PTS_PARSER_S_
{
    UINT32 bp_num;
    UINT32 sei_timing_num;
    UINT32 sei_timing_num_sub;

    UINT32 cpb_removal_delay;
    UINT32 prev_au_cpb_removal_delay;
    UINT32 dpb_output_delay;
    UINT64 u64_dpb_output_time;
    UINT64 u64_frame_output_time;
    UINT64 i64_au_removal_tm;
    UINT64 i64_removal_tm_of_first_pic_in_bp;

    UINT32 vui_num_units_in_tick;
    UINT32 vui_time_scale;

    UINT64 u64_last_IDR_pts;
    UINT64 u64_last_IDRFrame_output_time;
    UINT8 NewBpStart;
} H264_SEI_PTS_PARSER_S;

typedef struct
{
    UINT8  pic_struct;
    UINT32 cpb_removal_delay;
    UINT32 dpb_output_delay;
    /* ���滹������﷨Ԫ�أ���ʱ�ò����������� */
} H264_PIC_TIMING_SEI_S;

typedef struct
{
    UINT8   structure;     // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT8   is_long_term;  // 0: not long term ref, 1: long term ref
    UINT8   is_short_term; // 0: not short term ref, 1: short term ref. BUT one pic cann't long and short.

    SINT32  long_term_pic_num;
    SINT32  pic_num;
    SINT32  poc;

    UINT32  err_level;
    UINT32  pic_type;
    /* BEGIN: Added 2010/9/27 */
    SINT32  MaxQp;
    SINT32  MinQp;
    /* END:   Added 2010/9/27 */

    SINT32  AvgQp;
    struct  H264_FRAMESTORE_S *frame_store;
} H264_STORABLEPIC_S;

typedef enum
{
    FO_STATE_NA,
    FO_STATE_FAST_OUTPUT,
    FO_STATE_NORMAL_ORDER_OUTPUT,
    FO_STATE_BUTT
} FO_STATE_E;

typedef struct H264_FRAMESTORE_S
{
    UINT8   non_existing;   // 1: ��fs��ͼ�񲻴���, 0: ����
    UINT8   is_used;        // 0: empty, 1: top, 2: bottom, 3: both fields (or frame)--output
    UINT8   is_reference;   // 0: not used for ref, 1: top used, 2: bottom used,
    UINT8   mode_skip_flag; // 0: all dec, 1: top not dec, 2: bottom not dec, 3: both fields (or frame) not dec
    UINT8   is_in_dpb;       // �Ѿ�����DPB, 0: already out from dpb, 1: still in dpb
    UINT8   linear_en;      //0: tile; 1: 2D
    UINT32  CompressEn;
    IMAGE   fs_image;
    SINT32  logic_fs_id;
    UINT32  frame_num;
    SINT32  frame_num_wrap;
    UINT32  long_term_frame_idx;
    SINT32  poc;

    UINT32  is_displayed;    // VO �Ƿ���ʾ��0: not display; 1: displayed
    UINT32  MbaffFrameFlag;
    UINT32  pic_type;
    UINT32  err_level;
    UINT32  pmv_address_idc;
    UINT32  apc_idc;
    SINT32  AvgQp;

    H264_STORABLEPIC_S  frame;
    H264_STORABLEPIC_S  top_field;
    H264_STORABLEPIC_S  bottom_field;
    FO_STATE_E  eFoState;  // �����һ֡�������ʱʹ��
} H264_FRAMESTORE_S;

typedef struct
{
    UINT8   state;
    UINT8   field_pair_flag;
    UINT8   non_existing;  // 0����ǰͼ�����, 1����ǰͼ�񲻴���. ��Ҫ����Frame_num gap�������.
    UINT8   structure;     // 0: frame, 1: top_field, 2: bottom_field, 3: reserved
    UINT8   is_long_term;  // 0: not long term ref,  1: long term ref
    UINT8   is_short_term; // 0: not short term ref, 1: short term ref. BUT one pic cann't long and short.
    UINT8   nal_unit_type;
    UINT8   mode_skip_flag;
    UINT8   entropy_coding_mode_flag;
    UINT8   MbaffFrameFlag;
    //    UINT8   FrameStoreFlag;
    IMAGE   fs_image;

    H264_FRAMESTORE_S *frame_store;
    H264_MARK_S       *pMarkPara;

    UINT32  frame_num;
    UINT32  long_term_frame_idx;
    UINT32  nal_ref_idc;
    SINT32  thispoc;
    SINT32  framepoc;
    SINT32  toppoc;
    SINT32  bottompoc;

    UINT32  pic_type;
    UINT32  is_idr_pic;
    UINT32  err_level;
    UINT32  pic_width_in_mb;
    UINT32  pic_height_in_mb;
    UINT32  frame_height_in_mb;
    UINT32  pic_mbs;
    UADDR   stream_base_addr;
    UINT32  pmv_address_idc;

    UINT32  FrameStreamSize;
    UINT32  CurrentNalSize;
} H264_CURRPIC_S;

typedef struct
{
    UINT8   structure;    // ͼ��ṹ, 0: frame, 1: top field, 2:bottom field, 3: rsv
    UINT8   FrameStoreFlag;
    UINT32  nal_ref_idc;
    UINT32  frame_num;
    UINT32  pic_type;
    UINT32  pic_counter;
    UINT32  image_id;
    UINT32  Dpb_pos;

} H264_PREVPIC_S;

typedef struct
{
    UINT32  is_used[16];
    UINT32  idc[16];
    UINT32  poc[2][16];
    UINT32  size;
    UINT32  used_size;
    UINT32  RefIdx[32];
} H264_APC_S;

typedef struct
{
    H264_FRAMESTORE_S *fs[16];
    H264_FRAMESTORE_S *fs_ref[16];
    H264_FRAMESTORE_S *fs_ltref[16];
    UINT32  size;
    UINT32  used_size;
    UINT32  ref_frames_in_buffer;
    UINT32  ltref_frames_in_buffer;
    UINT32  max_long_term_pic_idx;
} H264_DPB_S;

typedef struct
{
    H264_NALU_S *pSliceNal;
} H264_SLCINFO_S;  //Slice��Ϣ, ��Ҫ�Ǽ�¼δ�ͷŵ�����

typedef struct
{
    UINT8   last_pack_in_nal;
    UINT8   pack_is_pic_over_flag;
    UINT8   *p_stream;
    UADDR   strm_phy_addr;
    SINT32  stream_len;
    SINT32  StreamID;
    SINT32  SegCutState;
    UINT64  pts;
} H264_STREAM_PACKET;

typedef enum
{
    FIRST_DISP_INIT = 0,
    FIRST_DISP_UNPAIRED,
    FIRST_DISP_OUTPUT
} H264_FIRSTDISPSTATE_E;

typedef struct
{
    UINT8  idr_flag;
    UINT8  priority_id;
    UINT8  no_inter_layer_pred_flag;
    UINT8  dependency_id;
    UINT8  quality_id;
    UINT8  temporal_id;
    UINT8  use_ref_base_pic_flag;
    UINT8  discardable_flag;
    UINT8  output_flag;
    UINT8  reserved_three_2bits;
} SVC_NALUSVCEXT_S;

typedef struct
{
    SYNTAX_EXTRA_DATA_S     *pstExtraData;
    IMAGE_VO_QUEUE           ImageQue;
    H264_DEC_PIC_PARAM_S    *pH264DecParam;
    UINT32                   StartMode;  // 0:Normal Mode, 1: Flush Mode

    H264_NALU_S        *pCurrNal;
    H264_NALU_S         NalArray[MAX_SLICE_SLOT_NUM + 1];
    BS                  BS;  // for bstream.c�еĵ���֮��
    UINT8               IsStreamEndFlag;
    SINT32              CurWidthInMb;
    SINT32              CurHeightInMb;
    SINT32              MaxSliceNum;
    SINT32              MaxSpsNum;
    SINT32              MaxPpsNum;
    SINT32              TrueDpbSize;
    H264_SPS_S          *SPS;
    H264_PPS_S          *PPS;
    H264_SPS_S          CurrSPS;
    H264_PPS_S          CurrPPS;
    H264_POC_S          CurrPOC;
    H264_REORDER_S      CurrReorder;
    H264_SLICE_S        CurrSlice;
    H264_PREVSLICE_S    PrevSlice;
    H264_MARK_S         Mark[2];
    UINT32              CurrMarkIdx;
    H264_FRAME_PACKING_ARRANGEMENT_S  FramePackSEI;
    H264_PIC_TIMING_SEI_S PicTimingSEI;
    H264_SEI_PTS_PARSER_S PtsParser;
    H264_DPB_S          DPB;
    H264_APC_S          APC;
    H264_STORABLEPIC_S *pListX[2][MAX_LIST_SIZE];
    H264_FRAMESTORE_S   FrameStore[MAX_FRAME_STORE];
    H264_CURRPIC_S      CurrPic;
    H264_CURRPIC_S      LastPic;
    H264_PREVPIC_S      PrevPic;
    H264_FRAMESTORE_S  *pDirectOutBuf;
    H264_FRAMESTORE_S  *pLastFieldBuf;
    SVC_NALUSVCEXT_S SVC_NALUSVCEXT_S;
    H264_SLCINFO_S      SlcInfo[MAX_SLICE_SLOT_NUM];     //Slice��Ϣ, ��Ҫ�Ǽ�¼δ�ͷŵ�����
    UINT32              PmvStoreUsedFlag[MAX_PMV_STORE]; // pmv store memory allocate statistic
    UINT32              TotalFsNum;      // change while g_DPB.size change
    UINT32              TotalPmvNum;     // change while g_DPB.size change

    UINT32              AllowStartDec;   // 0: find recover point, when recover point found and decode right this flag =1;
    UINT32              HaveNalNotDecoded;
    UINT32              IDRFound;          // 0: to find I/IDR, 1: I/IDR found
    UINT32              PPicFound;
    UINT32              frame_rate;

    UINT32              TotalUsrDatNum;
    VDEC_USRDAT_S      *pUsrDatArray[MAX_USERDATA_NUM];

    H264_DEC_PIC_PARAM_S    DecPicPara;
    H264_DEC_SLICE_PARAM_S  *DecSlicePara;
    UINT32                  SliceParaNum;
    UINT32                  OldDecMode;
    UINT32                  IModeOutFlag;
    UINT32                  MutexHold;

    UINT32     SeErrFlg;
    UINT32     TotalNal;
    UINT32     TotalSPS ;
    UINT32     TotalPPS;
    UINT32     TotalSlice;
    UINT32     SeqCnt;
    UINT32     TotalPicNum;
    UINT32     TotalFrameNum;
    UINT32     TotalFieldNum;
    UINT32     IDRPicOfCurrPic;
    UINT32     SliceNumInPic;
    UINT32     MaxBytesReceived;

    UINT32     advanced_cfg;
    UINT32     ref_error_thr;
    UINT32     out_error_thr;
    SINT32     ChanID;

#ifdef VFMW_H264_SED_ONLY_SUPPORT
    UINT32 SedOnlyEnable;
    UINT32 SegCutState;
    UINT32 SedOnlyTry;
    UINT32 SedOnlySucc;
    UINT32 PrePicstate;
    UINT32 SedSliceNum;
    UINT32 PostPicCount;
#endif

    H264_FIRSTDISPSTATE_E     FirstFrameDisplayed;

    UINT32     PrevStorePicCounter;
    UINT32     PicCounter;
    UINT32     NewPicCounter;
    UINT32     PicOutCounter;
    SINT32     numTotalFrame;
    SINT32     numOutputFrame;
    UINT32     u32SCDWrapAround;
    H264_NALU_S *pLastNal;
    UINT32     FakeFrmHeightInMb;
    UINT32     FakeFrmWidthInMb;
} H264_CTX_S;


/*************************** func declare *************************/
SINT32 FindTrailZeros(H264_CTX_S *pH264Ctx);
SINT32 RecivePacket(H264_CTX_S *pH264Ctx, H264_STREAM_PACKET *pPacket);
VOID   CombinePacket(H264_CTX_S *pH264Ctx);
SINT32 FindNaluArraySlot(H264_CTX_S *pH264Ctx);
SINT32 H264_DecOneNal(H264_CTX_S *pH264Ctx, UINT32 NalMode);
SINT32 H264_DecSPS(H264_CTX_S *pH264Ctx);
SINT32 ProcessSPS(H264_CTX_S *pH264Ctx, H264_SPS_S *pSPS);
SINT32 vui_parameters(H264_CTX_S *pH264Ctx, VUI_SEQ_PARAMETERS_S *pVUI);
SINT32 SPSEqual(H264_SPS_S *pSPS1, H264_SPS_S *pSPS2);
SINT32 H264_DecPPS(H264_CTX_S *pH264Ctx);
SINT32 ProcessPPS(H264_CTX_S *pH264Ctx, H264_PPS_S *pPPS);
SINT32 PPSEqual(H264_PPS_S *pPPS1, H264_PPS_S *pPPS2);
SINT32 H264_DecSEI(H264_CTX_S *pH264Ctx);
SINT32 SliceCheck(H264_CTX_S *pH264Ctx);
SINT32 H264_DecSlice(H264_CTX_S *pH264Ctx);
SINT32 ProcessSliceHeaderFirstPart(H264_CTX_S *pH264Ctx);
SINT32 ProcessSliceHeaderSecondPart(H264_CTX_S *pH264Ctx);
SINT32 ref_pic_list_reordering(H264_CTX_S *pH264Ctx);
SINT32 pred_weight_table(H264_CTX_S *pH264Ctx);
SINT32 dec_ref_pic_marking(H264_CTX_S *pH264Ctx);
SINT32 DecMMCO(H264_CTX_S *pH264Ctx, UINT32 save);
SINT32 PPSSPSCheck(H264_CTX_S *pH264Ctx);
SINT32 PPSSPSCheckTmpId(H264_CTX_S *pH264Ctx, UINT32 tmp_pic_parameter_set_id);
UINT32 IsNewPic(H264_CTX_S *pH264Ctx);
VOID   PicTypeStatistic(H264_CTX_S *pH264Ctx);
VOID   CalcPicNum(H264_CTX_S *pH264Ctx);
VOID   CalcStreamBits(H264_CTX_S *pH264Ctx);
VOID   ExitSlice(H264_CTX_S *pH264Ctx);
SINT32 DecList(H264_CTX_S *pH264Ctx);
SINT32 WritePicMsg(H264_CTX_S *pH264Ctx);
VOID   WriteSliceMsg(H264_CTX_S *pH264Ctx);
SINT32 DecVDM(H264_CTX_S *pH264Ctx);
VOID   InitOldSlice(H264_CTX_S *pH264Ctx);
SINT32 InitListX(H264_CTX_S *pH264Ctx);
VOID   ReorderListX(H264_CTX_S *pH264Ctx);
SINT32 RepairList(H264_CTX_S *pH264Ctx);
SINT32 StorePicInDPB(H264_CTX_S *pH264Ctx, LUMA_INFO_S *pLumaInfo);
SINT32 InitPic(H264_CTX_S *pH264Ctx);
VOID   ReleaseNAL(SINT32 ChanId, H264_NALU_S *p_nal);
VOID   H264_FlushDecoder(H264_CTX_S *pH264Ctx);
SINT32 H264_IsNewPicNal( SINT32 *pNewPicDetector, UINT8 *pu8 );
SINT32 IsRefListWrong(H264_CTX_S *pH264Ctx);
SINT32 FlushDPB(H264_CTX_S *pH264Ctx);
SINT32 InitDPB(H264_CTX_S *pH264Ctx);

SINT32 H264DEC_Init(H264_CTX_S *pH264Ctx, SYNTAX_EXTRA_DATA_S *pstExtraData);
VOID   H264DEC_Destroy(H264_CTX_S *pH264Ctx);
SINT32 H264DEC_DecodePacket(H264_CTX_S *pH264Ctx, H264_STREAM_PACKET *pPacket);
SINT32 H264DEC_RecycleImage(H264_CTX_S *pH264Ctx, UINT32 PicID);
UINT32 H264DEC_VDMPostProc( H264_CTX_S *pH264Ctx, SINT32 ErrRatio, SINT32 CalledByISR, LUMA_INFO_S *pLumaInfo, SINT32 s32LowdelayFlag, SINT32 VdhId);
SINT32 H264DEC_GetImageBuffer( H264_CTX_S *pH264Ctx );
SINT32 H264DEC_GetRemainImg(H264_CTX_S *pH264Ctx);
SINT32 H264_ClearCurrPic(H264_CTX_S *pH264Ctx);

SINT32 H264DEC_GetImageWidth(H264_CTX_S *pH264Ctx);
SINT32 H264DEC_GetImageHeight(H264_CTX_S *pH264Ctx);

#ifdef  DOLBY_VISION_HDR_SUPPORT
HI_VOID H264_Sei_Get_Dpb_Output_Time(H264_CTX_S *pH264Ctx);
HI_VOID H264_Get_Last_IDR_Frame_Info(H264_CTX_S *pH264Ctx, UINT32 nal_unit_type);
HI_VOID H264_Sei_Get_Frame_Pts(H264_CTX_S *pH264Ctx);
#endif
#ifdef VFMW_H264_SED_ONLY_SUPPORT
UINT32 H264DEC_VDMProcSedOnly( H264_CTX_S *pH264Ctx, SINT32 VdhId);
#endif

#ifdef __cplusplus
}
#endif


#endif  // __H264_H__
