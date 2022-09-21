#ifndef _AVS2_HEADER_
#define _AVS2_HEADER_

#include    "basedef.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"
#include    "syn_cmn.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
* 宏定义                                       *
*----------------------------------------------*/

#define AVS2_SLICE_START_CODE_BIGIN    (0x8F)
#define AVS2_VIDEO_SEQUENCE_START_CODE (0xb0)
#define AVS2_VIDEO_SEQUENCE_END_CODE   (0xb1)
#define AVS2_USER_DATA_START_CODE      (0xb2)
#define AVS2_INTRA_PICTURE_START_CODE  (0xb3)
#define AVS2_EXTENSION_START_CODE      (0xb5)
#define AVS2_INTER_PICTURE_START_CODE  (0xb6)
#define AVS2_VIDEO_EDIT_CODE           (0xb7)
#define HISI_AVS2_STREAM_END_CODE      (0xFE)

#define AVS2_EXTCODE_SEQDISP           (0x2)
#define AVS2_EXTCODE_TEMEXT            (0x3)
#define AVS2_EXTCODE_COPYRT            (0x4)
#define AVS2_EXTCODE_PICDISP           (0x7)
#define AVS2_EXTCODE_METADAT           (0xa)
#define AVS2_EXTCODE_CMRPRM            (0xb)
#define AVS2_EXTCODE_ROIEXT            (0xc)

#define AVS2_I_PIC                     (0)
#define AVS2_P_PIC                     (1)
#define AVS2_B_PIC                     (2)
#define AVS2_F_PIC                     (3)
#define AVS2_S_PIC                     (4)
#define AVS2_G_PIC                     (5)
#define AVS2_GB_PIC                    (6)

#define AVS2_FOUND_NEXTHDR             (0x1 << 14)
#define AVS2_FOUND_SLCHDR              (0x1 << 15)
#define AVS2_FOUND_SEQHDR              (0x1 << 16)
#define AVS2_FOUND_PICHDR              (0x1 << 18)
#define AVS2_BASIC_HDR                 (AVS_FOUND_SEQHDR|AVS_FOUND_PICHDR)
#define AVS2_PIC_OK                    (AVS_FOUND_SEQHDR|AVS_FOUND_PICHDR|AVS_FOUND_SLCHDR|AVS_FOUND_NEXTHDR)

#define AVS2_LEVEL_2_0_15              (0x10)
#define AVS2_LEVEL_2_0_30              (0x12)
#define AVS2_LEVEL_2_0_60              (0x14)
#define AVS2_LEVEL_4_0_30              (0x20)
#define AVS2_LEVEL_4_0_60              (0x22)
#define AVS2_LEVEL_6_0_30              (0x40)
#define AVS2_LEVEL_6_2_30              (0x42)
#define AVS2_LEVEL_6_0_60              (0x44)
#define AVS2_LEVEL_6_2_60              (0x46)
#define AVS2_LEVEL_6_0_120             (0x48)
#define AVS2_LEVEL_6_2_120             (0x4A)
#define AVS2_LEVEL_8_0_30              (0x50)
#define AVS2_LEVEL_8_2_30              (0x52)
#define AVS2_LEVEL_8_0_60              (0x54)
#define AVS2_LEVEL_8_2_60              (0x56)
#define AVS2_LEVEL_8_0_120             (0x58)
#define AVS2_LEVEL_8_2_120             (0x5A)
#define AVS2_LEVEL_10_0_30             (0x60)
#define AVS2_LEVEL_10_2_30             (0x62)
#define AVS2_LEVEL_10_0_60             (0x64)
#define AVS2_LEVEL_10_2_60             (0x66)
#define AVS2_LEVEL_10_0_120            (0x68)
#define AVS2_LEVEL_10_2_120            (0x6A)

#define AVS2_FALSE                     (0)
#define AVS2_TRUE                      (1)
#define AVS2_WAIT                      (3)

#define AVS2_MAX_RCS                   (32)
#define AVS2_ALF_MAX_LUMA_FILTER_NUM   (16)
#define AVS2_ALF_MAX_COEF_NUM          (9)
#define AVS2_MAX_REF_FRAME             (15)
#define AVS2_MAX_FRAME_BUF             (AVS2_MAX_REF_FRAME + 1)
#define AVS2_MAX_SINGLE_PIC_REF_NUM    (7)
#define AVS2_MAX_TEMPORAL_LEVEL_NUM    (7)


typedef struct
{
    SINT16  sDoi;
    SINT16  sPoi;
    UINT8   ucDisplayed;
    UINT8   ucUsedAsRef;
    UINT8   ucOccupied;  // 1: In reference picture buffer only. 2: In scene picture buffer only. 3: In both scene & reference picture buffers.
    UINT8   ucPictureType;
    SINT16  sDistanceIndex;
    SINT16  sDoiPlusOutputDelay;

    UINT8   ucTopField;
    UINT8   ucPictureStructure;
    UINT8   ucTopFieldFirst;
    UINT8   linear_en;
    UINT8   CompressEn;

    SINT16  sDistanceCurRef[AVS2_MAX_SINGLE_PIC_REF_NUM];
    SINT16  sDivCurRef[AVS2_MAX_SINGLE_PIC_REF_NUM];
    UINT8   aucRefTopField[AVS2_MAX_SINGLE_PIC_REF_NUM];

    SINT32  FspID;

    UADDR   luma_phy_addr;
    UADDR   chrom_phy_addr;

    SINT32  Stride_nbit;
    SINT32  LumaOffset_nbit;
    SINT32  ChromaOffset_nbit;

    UADDR   colmv_phy_addr;
    UINT32  chroma_offset;
    UINT32  y_stride;
    UINT32  uv_stride;
    UINT32  head_info_size;
    UADDR   line_num_phy_addr;

} AVS2_FRAME_MEMORY_S;

typedef struct
{
    UINT32 refered_by_others_flag;
    UINT32 num_of_reference_picture;
    UINT32 delta_doi_of_reference_picture[AVS2_MAX_SINGLE_PIC_REF_NUM];
    UINT32 num_of_removed_picture;
    UINT32 delta_doi_of_removed_picture[AVS2_MAX_SINGLE_PIC_REF_NUM];

} AVS2_RCS_S;

typedef struct
{
    UINT32 profile_id;
    UINT32 level_id;
    UINT32 progressive_sequence;
    UINT32 field_coded_sequence;
    UINT32 horizontal_size;
    UINT32 horizontal_size_disp;
    UINT32 vertical_size;
    UINT32 vertical_size_disp;
    UINT32 chroma_format;
    UINT32 sample_precision;
    UINT32 encoding_precision;
    UINT32 aspect_ratio;
    UINT32 frame_rate_code;
    UINT32 bit_rate_lower;
    UINT32 marker_bit;
    UINT32 bit_rate_upper;
    UINT32 low_delay;
    UINT32 temporal_id_enable;
    UINT32 bbv_buffer_size;
    UINT32 lcu_size;
    UINT32 weight_quant_enable;
    UINT32 load_seq_weight_quant_data_flag;
    UINT32 scene_picture_disable;
    UINT32 multi_hypothesis_skip_enable;
    UINT32 dual_hypothesis_prediction_enable;
    UINT32 weighted_skip_enable;

    UINT8  aucWQM_4x4[4][4];
    UINT8  aucWQM_8x8[8][8];

    UINT32 asymmetric_motion_partitions_enable;
    UINT32 nonsquare_quadtree_transform_enable;
    UINT32 nonsquare_intra_prediction_enable;
    UINT32 secondary_transform_enable_flag;
    UINT32 sample_adaptive_offset_enable;
    UINT32 adaptive_loop_filter_enable;
    UINT32 pmvr_enable;
    UINT32 num_of_rcs;
    AVS2_RCS_S rcs[AVS2_MAX_RCS];
    UINT32 output_reorder_delay;
    UINT32 cross_slice_loopfilter_enable;
    UINT32 reserved_bits;
    UINT32 alf_enable_flag;

    UINT16 usFrmWidthInLcu;
    UINT16 usFrmHeightInLcu;

    UINT8  ucMaxDpbNum;
    UINT8  ucBitDepth;
    UINT32 frame_rate;

} AVS2_SEQ_S;

typedef struct
{
    UINT32 video_format;
    UINT32 sample_range;
    UINT32 colour_description;
    UINT32 colour_primaries;
    UINT32 transfer_characteristics;
    UINT32 matrix_coefficients;
    UINT32 display_horizontal_size;
    UINT32 marker_bit;
    UINT32 display_vertical_size;
    UINT32 td_mode_flag;
    UINT32 td_packing_mode;
    UINT32 view_reverse_flag;

} AVS2_SDEXT_S;

typedef struct
{
    UINT32 num_of_temporal_level_minus1;
    UINT32 temporal_frame_rate_code[AVS2_MAX_TEMPORAL_LEVEL_NUM];
    UINT32 temporal_bit_rate_lower[AVS2_MAX_TEMPORAL_LEVEL_NUM];
    UINT32 marker_bit;
    UINT32 temporal_bit_rate_upper[AVS2_MAX_TEMPORAL_LEVEL_NUM];

} AVS2_TEMEXT_S;

typedef struct
{
    UINT32 asisx;
    UINT32 asisy;
    UINT32 width;
    UINT32 height;

} AVS2_ROIINFO_S;

typedef struct
{
    UINT32 extension_id;
    UINT32 current_picture_roi_num;
    UINT32 prev_picture_roi_num;
    UINT32 roi_skip_run;
    UINT32 skip_roi_mode;  // 初始为skip_roi_mode[10]，按协议应该是数组，但没说明数组应开多大，同时根据实际运算，取一位即可，同时可以防止数组越界
    UINT32 roi_axisx_delta;
    UINT32 roi_axisy_delta;
    UINT32 roi_width_delta;
    UINT32 roi_height_delta;
    UINT32 roi_axisx;
    UINT32 roi_axisy;
    UINT32 roi_width;
    UINT32 roi_height;

    AVS2_ROIINFO_S ROIInfo[10];      // old AVS2_ROIINFO_S* ROIInfo[10]; should not be pointer, it will null pointer crash, still have risk of array overflow.
    AVS2_ROIINFO_S PrevROIInfo[10];  // old AVS2_ROIINFO_S* PrevROIInfo[10]; should not be pointer, it will null pointer crash, still have risk of array overflow.

} AVS2_ROIEXT_S;

typedef struct
{
    UINT8  ucRefPicNum;
    UINT8  ucWqmShift;
    SINT8  weighting_quant_param_delta1[6];
    SINT8  weighting_quant_param_delta2[6];
    UINT8  aucWQM_4x4[4][4];
    UINT8  aucWQM_8x8[8][8];

    /* Intra_Pic :I G GB*/
    UINT32 bbv_delay;
    UINT32 bbv_delay_extension;
    UINT32 time_code_flag;
    UINT32 time_code;
    UINT32 marker_bit;

    /* Inter_Pic: P B F S  */
    UINT32 picture_coding_type;
    UINT32 scene_pred_flag;
    UINT32 scene_reference_enable;
    UINT32 random_access_decodable_flag;
    UINT32 derived_pic_coding_type;
    UINT32 IsIntraPic;

    UINT32 scene_picture_flag;
    UINT32 scene_picture_output_flag;
    UINT32 decode_order_index;
    UINT32 temporal_id;
    UINT32 picture_output_delay;
    UINT32 use_rcs_flag;
    UINT32 rcs_index;
    UINT32 bbv_check_times;
    UINT32 progressive_frame;
    UINT32 picture_structure;
    UINT32 top_field_first;
    UINT32 repeat_first_field;
    UINT32 top_field_picture_flag;
    UINT32 fixed_picture_qp;
    UINT32 picture_qp;
    UINT32 skip_mode_flag;
    UINT32 reserved_bits;
    UINT32 loop_filter_disable;
    UINT32 loop_filter_parameter_flag;
    SINT32 alpha_c_offset;
    SINT32 beta_offset;
    UINT32 pic_weight_quant_enable;
    UINT32 pic_weight_quant_data_index;
    UINT32 chroma_quant_param_disable;
    SINT32 chroma_quant_param_delta_cb;
    SINT32 chroma_quant_param_delta_cr;
    UINT32 weighting_quant_param_index;
    UINT32 weighting_quant_model;
    UINT32 picture_alf_enable[3];
    UINT32 alf_filter_num_minus1;
    UINT32 alf_region_distance[16];
    SINT32 alf_coeff_luma[16][AVS2_ALF_MAX_COEF_NUM];
    SINT32 alf_coeff_chroma[2][AVS2_ALF_MAX_COEF_NUM];

    /* cur frame use ref frame info */
    AVS2_RCS_S stPicRcs;

} AVS2_PIC_S;

typedef struct
{
    UINT32 frame_centre_horizontal_offset[3];
    UINT32 frame_centre_vertical_offset[3];

} AVS2_PDEXT_S;

typedef struct
{
    UINT32 MasteringAvailable;
    UINT32 ContentAvailable;

    UINT32 display_primaries_x[3];
    UINT32 display_primaries_y[3];
    UINT32 white_point_x;
    UINT32 white_point_y;
    UINT32 max_display_mastering_luminance;
    UINT32 min_display_mastering_luminance;
    UINT32 max_content_light_level;
    UINT32 max_picture_average_light_level;

} AVS2_METADAT_S;

typedef struct
{
    UINT32         NumOfFrameCentreOffsets;
    AVS2_SEQ_S     syn_seq;      //序列头
    AVS2_SDEXT_S   syn_sdext;    //序列显示扩展
    AVS2_PIC_S     syn_pic;      //图像头
    AVS2_PDEXT_S   syn_pdext;
    AVS2_TEMEXT_S  syn_tsext;    //时域可伸缩扩展
    //AVS2_ROIEXT_S  syn_roiext;   //感兴趣区域  // not support now for it is unnecessary and with null pointer crash risk
    AVS2_METADAT_S syn_metaext;

} AVS2_SYNTAX_S;

typedef struct
{
    SINT16 sDoiPrev;
    SINT16 sDoi;
    SINT16 sPoi;

    SINT32 ErrRatio;

    SINT16 sDistanceCurRef[AVS2_MAX_SINGLE_PIC_REF_NUM];
    SINT16 sDivCurRef[AVS2_MAX_SINGLE_PIC_REF_NUM];
    SINT16 sDistanceColRef[AVS2_MAX_SINGLE_PIC_REF_NUM];
    SINT16 sDivColRef[AVS2_MAX_SINGLE_PIC_REF_NUM];

    AVS2_FRAME_MEMORY_S  stZeroFrm;
    AVS2_FRAME_MEMORY_S *pstCurFrmMem;
    AVS2_FRAME_MEMORY_S *pstRefFrmMem[AVS2_MAX_REF_FRAME];

    /*usr data*/
    VDEC_USRDAT_S       *pSeqUD;
    VDEC_USRDAT_S       *pPicUD;
} AVS2_PICINFO_S;

typedef struct
{
    UINT8                IsStreamEndFlag;
    UINT8                IsFirstFrameDisplayed;
    SINT32               ChanID;
    SINT32               IsPackWaitDec;
    UINT32               Integrity;
    UINT32               LastIntegrity;
    SINT32               SizeChanged;
    SINT32               FspPartitionOK;
    SINT32               FrameNum;
    SINT32               UsedDecMode;

    SYNTAX_EXTRA_DATA_S *pstExtraData;
    AVS2_DEC_PARAM_S    *pAvs2DecParam;

    BS                   Bs;
    AVS2_DEC_PARAM_S     Avs2DecParam;
    AVS2_PICINFO_S       PicInfo;
    AVS2_SYNTAX_S        Syntax;
    AVS2_SYNTAX_S        SyntaxNew;
    IMAGE_VO_QUEUE       ImageQue;
    DEC_STREAM_PACKET_S  LastPacket;
    AVS2_FRAME_MEMORY_S  stFrameBuf[AVS2_MAX_FRAME_BUF];

} AVS2_CTX_S;


SINT32 AVS2DEC_Init(AVS2_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData);
SINT32 AVS2DEC_Destroy(VOID);
SINT32 AVS2DEC_GetImageBuffer( AVS2_CTX_S *pCtx);
SINT32 AVS2DEC_Decode(AVS2_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket);
SINT32 AVS2DEC_VDMPostProc(AVS2_CTX_S *pCtx, SINT32 ErrRatio, SINT32 ModuleLowlyEnable, SINT32 VdhId);
SINT32 AVS2DEC_RecycleImage(AVS2_CTX_S *pCtx, UINT32 ImageId);
SINT32 AVS2DEC_GetRemainImg(AVS2_CTX_S *pCtx);
SINT32 AVS2DEC_ClearCurPic(AVS2_CTX_S *pCtx);

#ifdef __cplusplus
}
#endif


#endif

