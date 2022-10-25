#ifndef _DECPARAM_HEADER_
#define _DECPARAM_HEADER_

#ifdef __cplusplus
extern "C" {
#endif

#include "vfmw.h"
#include "basedef.h"
/************************************************************************/
/*   ����                                                               */
/************************************************************************/

#define    MAX_FRAME_NUM                  32 //64
#define    MAX_PMV_SLOT_NUM               MAX_FRAME_NUM //for lowdelay pmv=frame
#define    MAX_AVS_SLICE_NUM              512
#define    AVS2_MAX_SLICE_NUM             256

#define    DEI_WIDTH_THRESHOLD            1920
#define    DEI_HEIGHT_THRESHOLD           1088

#ifdef DOLBY_VISION_HDR_SUPPORT
#define META_DATA_STARTCODE  0x7c01
#define EL_DATA_STARTCODE 0x7e01
#define VDR_RPU_NAL_TYPE   0x19
#endif


#ifdef VFMW_AVS_SUPPORT
/*********************************************/
/***come from vdm_hal_avs.h, by lkf56013******/
/********************************************/
typedef struct
{
    UADDR   stream_phy_addr[2];
    SINT32  stream_lenInByte [2];
    UINT32  slice_start_mbn;
    SINT32  steram_id[2];
} AVS_SLCSTR_S;

typedef struct
{
    UINT8     mbamt_to_dec;
    UINT8     mv_output_en;
    UINT8     load_qmatrix_flag;
    UINT8     ddr_stride;
    UINT8     video_standard;
    UADDR     tab_base_addr;
    UADDR     ystaddr_1d;
    UINT8     PicCodingType;
    UINT8     PicStruct;
    UINT8     NoFwdRefFlag;
    UINT8     PicRefFlag;
    UINT8     SkipModeFlag;
    UINT8     PicQuant;
    UINT8     FixQPFlag;
    UINT8     RepeatFirstField;
    UINT8     TopFieldFirst;
    UINT8     ProgrsvFrame;
    UINT8     BetaOffset;
    UINT8     AlphaOffset;
    UINT8     LoopFiltParamFlag;
    UINT8     LoopFiltDisable;
    UINT8     ColPicStruct;
    UINT8     AdvPredModeDisable;
    UINT8     BwdTopFieldFirst;
    UINT8     BwdPicStruct;
    UINT8     FwdTopFieldFirst0;
    UINT8     FwdPicStruct0;
    UINT8     FwdTopFieldFirst1;
    UINT8     FwdPicStruct1;
    UINT8     ColPicType;
    UINT8     SamplePrecision;
    UINT8     ChromaFormat;
    UINT8     weighting_quant_flag;
    UINT8     chroma_quant_param_disable;
    UINT8     chroma_quant_param_delta_u ;
    UINT8     chroma_quant_param_delta_v;
    UINT8     aec_enable;
    UINT8     p_filed_enhanced_flag;
    UINT8     b_filed_enhanced_flag;
    UINT8     linear_en;
    UINT8    *StreamVirAddr[2];
    UINT16    PicWidthInMb;
    UINT16    PicHeightInMb;

    UADDR     StreamBaseAddr;
    UINT32    StreamSegID[2];
    UADDR     StreamPhyAddr[2];
    UINT32    StreamBitOffset[2];
    SINT32    StreamLength[2];
    //STREAM_SEG_PACKET_S *pSegMan;//ΪPoliat�汾д������Ϣ�ص������ṹ��
    //    S_SEG_S   SSeg[512];
    //    SINT32    SegNum;
    AVS_SLCSTR_S SlcStr[MAX_AVS_SLICE_NUM];
    SINT32    SlcNum;
    UADDR     BwdRefPicAddr;
    UADDR     FwdRefPic0Addr;
    UADDR     FwdRefPic1Addr;
    UADDR     CurPicAddr; //ystaddr_1d

    UADDR     CurPmvAddr;
    UADDR     ColPmvAddr;

    /* ��ʾͼ�������ַ */
    UADDR     rcn_address; //���� DispFramePhyAddr
    UADDR     pmv_colmb_addr;
    UINT32    PmvConfigTab[32];
    UINT32    cur_wq_matrix[64];
    UINT32    VahbStride;
    UADDR     line_num_addr;
    UINT32    UVOffset;
    UINT32    HeadStride;
    UINT32    HeadInfoSize;

    UINT32    RefPicType0; //bwd
    UINT32    RefPicType1;//fwd0
    UINT32    RefPicType2;//fwd1
    UINT32    RefPicType3;//curr
    SINT32    CompressEn;
    SINT32    VdhMmuEn;
} AVS_DEC_PARAM_S;
#endif

#ifdef VFMW_AVS2_SUPPORT
/*********************************************/
/*************     AVS2    ******************/
/********************************************/
typedef struct
{
    UINT16 LcuX;
    UINT16 LcuY;
    UINT32 FirstCtbInSlice;
    UADDR  PhyAddr[2];
    UINT32 LenInByte[2];
    UINT8  IsLastSeg[2];
    SINT32 StreamID[2];
} AVS2_SLC_INFO_S;

typedef struct
{
    UINT8  BitDepth;
    UINT8  VdhMmuEn;
    UINT8  CompressEn;
    UINT8  LinearEn;
    UINT8  ModuleLowdelayEn;
    UINT8  WeightQuantMatrix_4x4[4][4];
    UINT8  WeightQuantMatrix_8x8[8][8];

    UADDR  StreamBaseAddr;
    UADDR  CurPicAddr;
    UADDR  LineNumAddr;

    UINT32 FrameWidth;
    UINT32 FrameHeight;
    UINT32 FrmWidthInLcu;
    UINT32 FrmHeightInLcu;
    UINT32 LcuSize;
    UINT32 TopFieldPictureFlag;
    UINT32 PicQP;
    UINT32 FixedPicQP;
    UINT32 PicCodingType;
    UINT32 PicStructure;
    UINT32 CrossSliceLoopFilterEn;
    UINT32 NonsquareQuadtreeTransformEn;
    UINT32 ChromaFormat;
    UINT32 NonsquareIntraPredictionEn;
    UINT32 MultiHypothesisSkipEn;
    UINT32 WeightedSkipEn;
    UINT32 DualHypothesisPredictionEn;
    UINT32 RefPicNum;
    UINT32 AsymmetricMotionPartitionsEn;
    UINT32 AlfPicFlag;
    UINT32 SampleAdaptiveOffsetEn;
    UINT32 AdaptiveLoopFilterEn;
    UINT32 SecondaryTransformEn;
    UINT32 WeightQuantEn;
    SINT32 ChromaQuantParamDeltaCr;
    SINT32 ChromaQuantParamDeltaCb;
    UINT32 ChromaQuantParamDisable;
    UINT32 PicWeightQuantEn;
    UINT32 BetaOffset;
    UINT32 AlphaChromaOffset;
    UINT32 LoopFltParamFlag;
    UINT32 LoopFltDisable;
    UINT32 CurPicTopFieldFlag;
    UINT32 CurPicStructure;
    UINT32 CurPicTopFieldFirst;
    UINT32 ColMvWriteAddr;
    UINT32 ColMvReadAddr;
    UINT32 WeightQuantMatrixShift;
    UINT32 PmvrEn;
    UINT32 SceneReferenceEn;
    UINT32 LumaStride;
    UINT32 ChromaStride;
    UINT32 ChromaOffset;
    UINT32 HeadInfoSize;
    UINT32 Stride_nbit;
    UINT32 LumaOffset_nbit;
    UINT32 ChromaOffset_nbit;
    UINT32 ColRefPicTopFieldFlag[7];
    UINT32 RefPicTopFieldFlag[7];
    UINT32 RefPicStructure[7];
    UINT32 RefPicTopFieldFirst[7];
    UINT32 RefPicAddr[7];
    SINT16 DistanceCurRef[8];
    SINT16 DistanceColRef[8];
    SINT16 DivCurRef[8];
    SINT16 DivColRef[8];
    SINT32 AlfCoeffLuma[16][9];
    SINT32 AlfCoeffChroma[2][9];

    UINT32 SliceNum;
    AVS2_SLC_INFO_S SliceInfo[AVS2_MAX_SLICE_NUM];

} AVS2_DEC_PARAM_S;
#endif

/***********************************************************/
/**come from vdm_hal_h264.h, by lkf56013***********************/
/**********************************************************/
#ifdef VFMW_H264_SUPPORT
#define   H264_MIN_LEVEL                 10
#define   H264_MAX_LEVEL                 41
#define   QMATRIX_NUM                    56

typedef struct
{
    UINT8   list_structure;        // pic structure of this list element. 0: frame, 1: top_field, 2: bottom_field,
    UINT8   is_used;                // 0: empty, 1: top, 2: bottom, 3: both fields (or frame)--output
    UINT8   frame_structure;       // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT8   frame_is_long_term;    // 0: not long term ref,  1: long term ref
    UINT8   top_structure;         // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT8   top_is_long_term;      // 0: not long term ref,  1: long term ref
    UINT8   btm_structure;         // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT8   btm_is_long_term;      // 0: not long term ref,  1: long term ref

    SINT32  poc;
    UINT32  pmv_address_idc;
    UINT32  img_idc;
    UINT32  apc_idc;

    SINT32  frame_poc;
    SINT32  top_poc;
    SINT32  btm_poc;
} H264_DEC_LIST_S;

typedef struct  H264_DEC_SLICE_PARAM_S
{
    UINT8   slice_type;
    UINT8   MbaffFrameFlag;
    UINT8   direct_spatial_mv_pred_flag;
    UINT8   direct_8x8_inference_flag;
    UINT8   weight_flag;
    UINT32  valid_bitlen[2];       // valid bits when dec slice data
    UINT32  bitsoffset[2];         // offset in 32 bits when this segment stream start
    UINT32  bytespos[2];           // stream VDM will used start bytes ph addr, word addr aligned
    UINT32  SliceQPy;
    UINT32  cabac_init_idc;
    UINT32  num_ref_idx_l1_active_minus1;
    UINT32  num_ref_idx_l0_active_minus1;
    UINT32  first_mb_in_slice;
    UINT32  listXsize[2];
    SINT32  chroma_qp_index_offset;
    SINT32  second_chroma_qp_index_offset;
    SINT32  slice_alpha_c0_offset_div2;
    SINT32  slice_beta_offset_div2;
    UINT32  disable_deblocking_filter_idc;
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

    H264_DEC_LIST_S  declist[2][32];
    UINT32  Apc2RefIdx[32];

    struct  H264_DEC_SLICE_PARAM_S  *pNextSlice;
} H264_DEC_SLICE_PARAM_S;

typedef struct
{
    UINT8   pic_structure;
    UINT8   chroma_format_idc;  //0:400, 1:420
    SINT8   NewPicFlag;
    UINT8   frame_mbs_only_flag;
    UINT8   CompressEn;
    UINT8   LossCompressEn;
    UINT8   LossLow2BitsEn;
    UINT32  YCompRatio;
    UINT32  UVCompRatio ;
    UINT8   VdhMmuEn;
    UINT8   linear_en;

    UINT64  Pts;
    UINT32  nal_ref_idc;
    UINT32  pic_height_in_mb;
    UINT32  frame_height_in_mb;
    UINT32  pic_width_in_mb;
    UINT32  mb_adaptive_frame_field_flag;
    UINT32  transform_8x8_mode_flag;
    UINT32  entropy_coding_mode_flag;
    UINT32  constrained_intra_pred_flag;
    SINT32  ThisPoc;
    SINT32  TopPoc;
    SINT32  BottomPoc;
    UINT32  Qmatrix[QMATRIX_NUM];

    UINT32  weighted_pred_flag;
    UINT32  weighted_bipred_idc;

    UINT32  CurrPicImgIdc;
    UADDR   CurrPicImg2DAddr;  /*20100510 */
    UINT32  CurrPicPmvIdc;
    UINT32  ChromaOffset;

    UADDR   ImgPhyAddr[MAX_FRAME_NUM];

    //add 2013-04-28 fordsp
    UADDR   LineNumPhyAddr[MAX_FRAME_NUM];
    //end add

    UINT32  ImgSlotNum;
    UADDR   PmvPhyAddr[MAX_PMV_SLOT_NUM];
    SINT32  PmvSlotNum;
    UINT32  half_pmvblk_offset;
    UINT32  YStride;
    UINT32  UVStride;
    UINT32  HeadStride;
    UINT32  HeadInfoSize;

    UADDR   stream_base_addr;    //word addr
    SINT32  mbtodec;

    UINT32  Apc2Idc[16];
    UINT32  Apc2Poc[2][16];
    UINT32  ApcSize;

    SINT32  SliceParaNum;
    struct  H264_DEC_SLICE_PARAM_S  *pFirstSlice;

    //reg tmp
    UINT32  vdh_start;
    UINT32  vdh_repair;
    UINT32  basic_cfg0;
    UINT32  basic_cfg1;
    UADDR   avm_addr;
    UADDR   vam_addr;
    UADDR   stream_base_addr_reg_tmp;

    UINT32  emar_id;
    UINT32  sed_to;
    UINT32  itrans_to;
    UINT32  pmv_to;
    UINT32  prc_to;
    UINT32  rcn_to;
    UINT32  dblk_to;
    UINT32  ppfd_to;

    UADDR   ystaddr_1d;
    UADDR   ystride_1d;
    UINT32  uvoffset_1d;

    UINT32  prcnum_1d_cnt;
    UINT32  prcnum1_1d_cnt;
    UINT32  prcnum2_1d_cnt;

    UADDR   ppfd_buf_addr;
    UINT32  ppfd_buf_len;

    UINT32  vdh_state;
    UINT32  int_state;
    UINT32  int_mask;

    UINT32  RefPicType[16];
    UINT32  RefPicFsId[16];
    UINT32  MbaffFrameFlag;

#ifdef VFMW_H264_SED_ONLY_SUPPORT
    UINT32  IsSedOnly;
#endif
} H264_DEC_PIC_PARAM_S;
#endif


/*********************************************************
                       for hevc
**********************************************************/
#ifdef VFMW_HEVC_SUPPORT

/*** UHD decode memory define ***/
#define CFG_HEVC_PROFILE_LEVEL_5
#define   CFG_HEVC_MAX_PIX_HEIGHT 2304
#if defined (CFG_HEVC_PROFILE_LEVEL_4)
#define HEVC_PROFILE_LEVEL_4
#elif defined (CFG_HEVC_PROFILE_LEVEL_5)
#define HEVC_PROFILE_LEVEL_5
#else
#define HEVC_PROFILE_LEVEL_6
#endif

#if defined (HEVC_PROFILE_LEVEL_4)
#define HEVC_MAX_SLICE_NUM                              (75)
#define HEVC_LOGIC_TILE_ROWS_LIMIT                      (5)
#define HEVC_LOGIC_TILE_COLUMNS_LIMIT                   (5)
#elif defined (HEVC_PROFILE_LEVEL_5)
#define HEVC_MAX_SLICE_NUM                              (200)
#define HEVC_LOGIC_TILE_ROWS_LIMIT                      (11)
#define HEVC_LOGIC_TILE_COLUMNS_LIMIT                   (10)
#else
#define HEVC_MAX_SLICE_NUM                              (600)
#define HEVC_LOGIC_TILE_ROWS_LIMIT                      (22)
#define HEVC_LOGIC_TILE_COLUMNS_LIMIT                   (20)
#endif
#if !defined (CFG_HEVC_MAX_NUM_REF_PICS)
#define HEVC_MAX_NUM_REF_PICS                           (16)
#else
#define HEVC_MAX_NUM_REF_PICS                           CFG_HEVC_MAX_NUM_REF_PICS
#endif
#if !defined (CFG_HEVC_MAX_PIX_WIDTH)
#define HEVC_MAX_PIX_WIDTH                           (4096)
#else
#define HEVC_MAX_PIX_WIDTH                           CFG_HEVC_MAX_PIX_WIDTH
#endif

#if !defined (CFG_HEVC_MAX_PIX_HEIGHT)
#define HEVC_MAX_PIX_HEIGHT                             (4096)
#else
#define HEVC_MAX_PIX_HEIGHT                             CFG_HEVC_MAX_PIX_HEIGHT
#endif
#if !defined (CFG_HEVC_MIN_LOG2_CTB_SIZE)
#define HEVC_MIN_LOG2_CTB_SIZE                          (4)
#else
#define HEVC_MIN_LOG2_CTB_SIZE                          CFG_HEVC_MIN_LOG2_CTB_SIZE
#endif
#if !defined (CFG_HEVC_MAX_LOG2_CTB_SIZE)
#define HEVC_MAX_LOG2_CTB_SIZE                          (6)
#else
#define HEVC_MAX_LOG2_CTB_SIZE                          CFG_HEVC_MAX_LOG2_CTB_SIZE
#endif
#define HEVC_MIN_CTB_SIZE               (1<<HEVC_MIN_LOG2_CTB_SIZE)
#define HEVC_MAX_CTB_SIZE               (1<<HEVC_MAX_LOG2_CTB_SIZE)
#define HEVC_MB_SIZE                        (16)

#define HEVC_MAX_MB_NUM                  (HEVC_MAX_PIX_WIDTH/HEVC_MB_SIZE*HEVC_MAX_PIX_HEIGHT/HEVC_MB_SIZE)
#define HEVC_MAX_CTB_NUM_PER_LINE        (HEVC_MAX_PIX_WIDTH/HEVC_MB_SIZE)
#define HEVC_MAX_TILE_COLUMNS                        (20)
#define HEVC_MAX_TILE_ROWS                           (22)
#define HEVC_MAX_DPB_NUM                             (17)  //hevc_uhd.h has same HEVC_MAX_DPB_NUM
//#ifndef CTX_MEM_CUT
#define HEVC_APC_SIZE                                (16)  //< max. number of apc size

#define HEVC_STREAM_BASE_ALIGN                       (15)  // 4 words align in UHD, word align in UHD

#define HEVC_SED_TOP_ADDR_LEN                        (64*4*HEVC_MAX_PIX_WIDTH)
#define HEVC_PMV_TOP_ADDR_LEN                        (64*4*HEVC_MAX_PIX_WIDTH)
#define HEVC_PMV_LEFT_ADDR_LEN                       (64*4*HEVC_MAX_PIX_HEIGHT)
#define HEVC_RCN_TOP_ADDR_LEN                        (64*4*HEVC_MAX_PIX_WIDTH)
#define    HEVC_CA_MN_ADDR_LEN                       (1024)         //20141016   H265Э��CA_MN�ɼ�Ϊ1K
#define HEVC_ONEMB_PMV_COLMB_ADDR_LEN                (260*14)
#define HEVC_UPMSG_ADDR_LEN                          (4*4*HEVC_MAX_SLICE_NUM)       //20141016   ���߼�ȷ�Ϲ�
#define HEVC_PPFD_BUFFER_LEN                         (64*4*800)                      //8192 words
#define HEVC_TILE_SEGMENT_INFO_LEN                   (2048)     //(512*2+20*4+22*4=1192, 1024����) 20141024
#define HEVC_SAO_LEFT_ADDR_LEN                       (64*4*HEVC_MAX_PIX_HEIGHT)
#define HEVC_DBLK_LEFT_ADDR_LEN                      (64*4*HEVC_MAX_PIX_HEIGHT)
#define HEVC_SAO_TOP_ADDR_LEN                        (64*4*HEVC_MAX_PIX_WIDTH)
#define HEVC_DBLK_TOP_ADDR_LEN                       (64*4*HEVC_MAX_PIX_WIDTH)

/*********************** MSG SLOT PARA DEFINE *********************/
#define HEVC_MAX_SLOT_NUM                            (HEVC_MAX_SLICE_NUM+10)        //20141025
#define HEVC_ONE_MSG_SLOT_LEN                        (64*4*5)
#define HEVC_PIC_SLOT_NUM                            (2)
#define HEVC_SLICE_SLOT_START_NUM                    (3)

#ifdef MV_HEVC_SUPPORT
typedef struct
{
    UINT8  InterLayerMPEnabled;
    UINT8  ColMvRefEqualFlag;
    SINT32 ScaleType;
    SINT32 RefFrameWidth;
    SINT32 RefFrameHeight;
    SINT32 RefFrameWidthAlignCtb;
    SINT32 RefFrameHeightAlignCtb;
    SINT32 ScaleHorY;
    SINT32 ScaleVerY;
    SINT32 ScaleHorC;
    SINT32 ScaleVerC;
    SINT32 CurrOffsetLeftY;
    SINT32 CurrOffsetTopY;
    SINT32 CurrOffsetLeftC;
    SINT32 CurrOffsetTopC;
    SINT32 RefOffsetLeftY;
    SINT32 RefOffsetTopY;
    SINT32 RefOffsetLeftC;
    SINT32 RefOffsetTopC;
    SINT32 PhaseHorY;
    SINT32 PhaseVerY;
    SINT32 PhaseHorC;
    SINT32 PhaseVerC;
    SINT32 AddHorY;
    SINT32 AddVerY;
    SINT32 AddHorC;
    SINT32 AddVerC;
    SINT32 ScaleMVX;
    SINT32 ScaleMVY;
    UINT32 YBitDepth;
    UINT32 CBitDepth;
    SINT32 YStride;
    SINT32 UVOffset;
    SINT32 HeadInfoSize;
    SINT32 YStride_nbit;
    SINT32 YOffset_nbit;
    SINT32 UVOffset_nbit;
    SINT32 BaseLayerRefEn;
}SHVC_DEC_SLICE_PARAM_S;
#endif


typedef struct  tag_HEVC_DEC_SLICE_PARAM_S
{
    UINT32  valid_bitlen[2];       // valid bits when dec slice data
    UINT32  bitsoffset[2];         // offset in 32 bits when this segment stream start
    UINT32  bytespos[2];           // stream VDM will used start bytes ph addr, word addr aligned

    UINT8   IsLowDelay;
    UINT8   dependent_slice_segment_flag;

    SINT32  SliceQpY;
    UINT8   cabac_init_flag;
    UINT32  IndependentSliceSegmentAddr;

    SINT32  ColPicApc;
    UINT32  MaxNumMergeCand;
    UINT32  collocated_ref_idx;
    UINT8   collocated_from_l0_flag;
    UINT32  num_ref_idx_l1_active_minus1;
    UINT32  num_ref_idx_l0_active_minus1;
    UINT8   slice_temporal_mvp_enabled_flag;
    UINT8   mvd_l1_zero_flag;
    UINT32  listXsize[2];
    UINT32  SliceType;
    UINT32  slice_segment_address;//slice��ʼ��դɨ�� ��ַ
    UINT32  SliceSegmentAddressX; //slice��ʼ��ַX
    UINT32  SliceSegmentAddressY; //slice��ʼ��ַ Y
    UINT32  SliceSegmentTileAddress;//slice ��ʼtile��ַ
    SINT32  slice_cb_qp_offset;
    SINT32  slice_cr_qp_offset;
    SINT32  slice_tc_offset_div2;
    SINT32  slice_beta_offset_div2;
    UINT8   slice_sao_chroma_flag;
    UINT8   slice_sao_luma_flag;
    UINT8   slice_deblocking_filter_disabled_flag;
    UINT8   slice_loop_filter_across_slices_enabled_flag;
    UINT32  IsLongTerm[2][HEVC_MAX_NUM_REF_PICS];
    UINT32  ApcList[2][HEVC_MAX_NUM_REF_PICS];
    UINT32  Idx2Apc[2][HEVC_APC_SIZE];
    UINT32  Apc2MvAddrTable[HEVC_APC_SIZE];
    UADDR  Apc2MvAddr;
    SINT32  end_ctb_in_slice_raster;  // slice ������դɨ���ַ
    SINT32  end_ctb_in_slice_tile;    // slice ����tile ��ַ
    UADDR  next_slice_para_address;
    UINT32  luma_log2_weight_denom;
    UINT32  chroma_log2_weight_denom;
    SINT32  LumaWeightL0[HEVC_MAX_NUM_REF_PICS];
    SINT32  LumaWeightL1[HEVC_MAX_NUM_REF_PICS];
    SINT32  luma_offset_l0[HEVC_MAX_NUM_REF_PICS];
    SINT32  luma_offset_l1[HEVC_MAX_NUM_REF_PICS];
    SINT32  ChromaWeightL0[HEVC_MAX_NUM_REF_PICS][2];
    SINT32  ChromaWeightL1[HEVC_MAX_NUM_REF_PICS][2];
    SINT32  ChromaOffsetL0[HEVC_MAX_NUM_REF_PICS][2];
    SINT32  ChromaOffsetL1[HEVC_MAX_NUM_REF_PICS][2];

#ifdef MV_HEVC_SUPPORT
    SHVC_DEC_SLICE_PARAM_S ShvcSliceParam;
#endif

    struct  tag_HEVC_DEC_SLICE_PARAM_S *pNextSlice;
} HEVC_DEC_SLICE_PARAM_S;


typedef struct
{
    UINT8 CompressEn;
    UINT8 LossCompressEn;
    UINT8 LossLow2BitEn;
    UINT8 YCompRatio;
    UINT8 UVCompRatio;
    UINT8 linear_en;
    UINT8 strong_intra_smoothing_enabled_flag;
    UINT8 scaling_list_enabled_flag;
    UINT8 pcm_loop_filter_disabled_flag;
    UINT8 sample_adaptive_offset_enabled_flag;
    UINT8 amp_enabled_flag;
    UINT32 chroma_format_idc;
    UINT8  pcm_enabled_flag;
    UINT32 PicHightInCtbsYMinus1;
    UINT32 PicWidthInCtbsYMinus1;
    SINT32 ThisPoc;
    SINT32 view_id;
    UINT32 log2_parallel_merge_level_minus2;
    UINT8  weighted_bipred_flag;
    UINT8  weighted_pred_flag;


    UINT32 max_transform_hierarchy_depth_inter;
    UINT32 max_transform_hierarchy_depth_intra;
    UINT32 Log2MinIpcmCbSizeY;
    UINT32 Log2MaxIpcmCbSizeY;
    UINT32 Log2MinTrafoSize;
    UINT32 Log2MaxTrafoSize;
    UINT32 MaxCuDepth;
    UINT32 Log2MinCbSizeY;
    UINT32 CtbLog2SizeY;
    UINT32 QpBdOffsetC;
    UINT32 QpBdOffsetY;
    UINT32 PcmBitDepthC;
    UINT32 PcmBitDepthY;
    UINT32 BitDepthC;
    UINT32 BitDepthY;
    UADDR  sed_top_addr;
    UADDR  pmv_top_addr;
    UADDR  pmv_colmb_addr;
    UADDR  rcn_top_addr;
    UADDR  Apc2PicAddr;
    UADDR  ca_mn_addr;
    UINT32 Apc2PocTable[HEVC_APC_SIZE];
    UINT32 pic_height_in_luma_samples;
    UINT32 pic_width_in_luma_samples;
    UADDR  tile_segment_info_phy_addr;
    UADDR  sao_left_phy_addr;
    UADDR  dblk_left_phy_addr;
    UADDR  sao_top_phy_addr;
    UADDR  dblk_top_phy_addr;
    UINT8 loop_filter_across_tiles_enabled_flag;
    UINT8 transform_skip_enabled_flag;
    UINT8 sign_data_hiding_enabled_flag;
    UINT8 entropy_coding_sync_enabled_flag;
    UINT8 uniform_spacing_flag;
    UINT8 tiles_enabled_flag;
    SINT32 Log2MinCuQpDeltaSize;
    SINT32 diff_cu_qp_delta_depth;
    UINT8 cu_qp_delta_enabled_flag;
    UINT8 transquant_bypass_enabled_flag;
    UINT8 constrained_intra_pred_flag;
    SINT32 pps_cb_qp_offset;
    SINT32 pps_cr_qp_offset;
    SINT32 num_tile_rows_minus1;
    SINT32 num_tile_columns_minus1;
    UADDR  next_slice_para_address;
    UINT32 Qmatrix[4 * 64]; //need 3 bursts for Qmatrix  //

    UINT32 pmv_address_idc;

    UINT32  CurrPicImgIdc;
    UINT32  CurrPicPmvIdc;
    UINT32  YStride;
    UINT32  UVStride;

    UINT32 UVOffset;
    UINT32 HeadStride;
    UINT32 HeadInfoSize;

    UINT32 imgstride_2bit;
    UINT32 YOffset_2bit;
    UINT32 UVOffset_2bit;
    UINT32  VdhMmuEn;
    UADDR  stream_base_addr;    //word addr
    SINT32  mbtodec;
    SINT32  NewPicFlag;
    UADDR  ImgPhyAddr[MAX_FRAME_NUM];
    UINT32  ImgSlotNum;
    UADDR  PmvPhyAddr[MAX_PMV_SLOT_NUM];
    SINT32  PmvSlotNum;
    UINT32  half_pmvblk_offset;

    //add 2013-04-28 fordsp
    UADDR  LineNumPhyAddr[MAX_FRAME_NUM];

    UINT8  TileId[2][HEVC_MAX_CTB_NUM_PER_LINE];//2014102
    UINT32  TilePosX[HEVC_LOGIC_TILE_COLUMNS_LIMIT][2];
    UINT32  TilePosY[HEVC_LOGIC_TILE_ROWS_LIMIT][2];

    UINT32  Apc2Idc[HEVC_APC_SIZE];
    UINT32  ApcSize;

    SINT32  NumSlicePara;
    struct  tag_HEVC_DEC_SLICE_PARAM_S *pFirstSlice;

    //reg tmp
    UINT32  vdh_start;
    UINT32  vdh_repair;
    UINT32  basic_cfg0;
    UINT32  basic_cfg1;
    UADDR   avm_addr;
    UADDR   vam_addr;
    UADDR   stream_base_addr_reg_tmp;

    UINT32  emar_id;
    UINT32  sed_to;
    UINT32  itrans_to;
    UINT32  pmv_to;
    UINT32  prc_to;
    UINT32  rcn_to;
    UINT32  dblk_to;
    UINT32  ppfd_to;

    UADDR   ystaddr_1d;
    UINT32  ystride_1d;
    UINT32  uvoffset_1d;
    UINT32  head_inf_offset;
    UINT32 ystaddr_2bit;
    UINT32 uvstaddr_2bit;
    UINT32 ystride_2bit;
    UINT32 yoffset_2bit;
    UINT32 uvoffset_2bit;

    UINT32  prcnum_1d_cnt;
    UINT32  prcnum1_1d_cnt;
    UINT32  prcnum2_1d_cnt;

    UADDR   ppfd_buf_addr;
    UINT32  ppfd_buf_len;

    UINT32  vdh_state;
    UINT32  int_state;
    UINT32  int_mask;
    UINT32  RefPicType[16];
    UADDR   CurrPicImg2DAddr;
    UINT32  ChromaOffset;
    UINT32  TileNum;
    UINT32  TileGroup[HEVC_LOGIC_TILE_ROWS_LIMIT *HEVC_LOGIC_TILE_COLUMNS_LIMIT][2];
    UINT32  SliceGroup[HEVC_MAX_SLICE_NUM][2];

#ifdef VFMW_HEVC_SED_ONLY_SUPPORT
    UINT32  IsSedOnly;
#endif

    UINT32  sei_field_flag;
    UINT32  sei_source_scan_type;
} HEVC_DEC_PIC_PARAM_S;

typedef struct
{
    UINT32  list_structure;        // pic structure of this list element. 0: frame, 1: top_field, 2: bottom_field,

    UINT32  is_used;               // 0: empty, 1: top, 2: bottom, 3: both fields (or frame)--output
    SINT32  poc;
    UINT32  pmv_address_idc;
    UINT32  img_idc;
    UINT32  apc_idc;

    UINT32  frame_structure;       // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT32  frame_is_long_term;    // 0: not long term ref,  1: long term ref
    SINT32  frame_poc;

    UINT32  top_structure;         // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT32  top_is_long_term;      // 0: not long term ref,  1: long term ref
    SINT32  top_poc;

    UINT32  btm_structure;         // 0: frame, 1: top_field, 2: bottom_field, 3: field pair
    UINT32  btm_is_long_term;      // 0: not long term ref,  1: long term ref
    SINT32  btm_poc;
} HEVC_DEC_LIST_S;

#endif

#ifdef VFMW_VP9_SUPPORT

/*********************************************************
                       for vp9
**********************************************************/
#define VP9_MAX_PIC_WIDTH           4096
#define VP9_MAX_PIC_HEIGHT          4096

#define  VP9_SED_TOP_ADDR_LEN                     (64*4*VP9_MAX_PIC_WIDTH)
#define  VP9_PMV_TOP_ADDR_LEN                     (64*4*VP9_MAX_PIC_WIDTH)
#define  VP9_RCN_TOP_ADDR_LEN                     (64*4*VP9_MAX_PIC_WIDTH)
#define  VP9_DBLK_TOP_ADDR_LEN                    (64*4*VP9_MAX_PIC_WIDTH)
#define  VP9_DBLK_LEFT_ADDR_LEN                    (16*VP9_MAX_PIC_HEIGHT*2 + (VP9_MAX_PIC_HEIGHT/16)*8)  //�����ȷ��z00290437
#ifndef VP9_NEW_PROB
#define  VP9_PROB_TAB_ADDR_LEN                    (20 * 64 * 4)//(18 * 64 * 4)
#define  VP9_PROB_CNT_ADDR_LEN                    11*1024//(VP9_MAX_PIC_WIDTH * 4)    /* 3301 is enought */
#else
#define  VP9_PROB_TAB_ADDR_LEN                    (20 * 64 * 4) // (18 * 64 * 4)
#define  VP9_PROB_CNT_ADDR_LEN                    (20 * 64 * 4) // 11*1024
#endif

typedef struct
{
    UINT32 frame_info[64*4]; //for test 2015-02-09 //save frame info
    UINT32 tile_info[1024][64];//8192/256*8192/256
    UINT32  TotalTileNum;

    UINT8  IsRptFrmCopy;

    //UINT8 table[2752];//3000
    UINT8 prob_table[18*64*4];
    UINT8 pre_prob[18*64*4];
    UINT8 prob_skip_false;
    UINT8 mb_no_coeff_skip;
    UINT8 multi_token_partition;

    UINT8 segmentation_enable;
    UINT8 update_mb_segmentation_map;
    UINT8 mb_segmentation_abs_delta;
    UINT8 mode_ref_lf_delta_enabled;

    UINT8 base_qindex;
    UINT8 filter_type;
    UINT8 last_filter_type;
    UINT8 filter_level;
    UINT8 sharpness_level;
    UINT8 last_sharpness_level;

    UINT8 y1dc_sign;
    UINT8 y1dc_absdelta_q;
    UINT8 y2dc_sign;
    UINT8 y2dc_absdelta_q;
    UINT8 y2ac_sign;
    UINT8 y2ac_absdelta_q;
    UINT8 uvdc_sign;
    UINT8 uvdc_absdelta_q;
    UINT8 uvac_sign;
    UINT8 uvac_absdelta_q;
    UINT8 prob_intra;
    UINT8 prob_last;
    UINT8 prob_gf;

    /* bool coder element */
    UINT8 range;
    UINT8 count;
    UINT8 linear_en;

    UINT32 value;
    UINT32 pic_width_in_mb;
    UINT32 pic_height_in_mb;
    UINT32 ddr_stride;
    UINT32 YStride;
    UINT32 UVStride;
    UINT32 uvoffset_1d;
    UINT32 frame_type;
    UINT32 last_frame_type;

    UINT32 use_bilinear_mc_filter;
    UINT32 full_pixel;

    UADDR  stream_base_addr;

    /* the fisrt bitstream part */
    UINT32 bit_len_0;
    UINT32 bit_offset_0;
    UINT32 bit_byte_offset_0;

    UINT32 bit_len_1;
    UINT32 bit_offset_1;
    UINT32 bit_byte_offset_1;

    /*the second bitstream part*/
    UINT32 stream_num_part;

    UINT32 bitn_len_0[8];
    UINT32 bitn_offset_0[8];
    UINT32 bitn_byte_offset_0[8];

    UINT32 bitn_len_1[8];
    UINT32 bitn_offset_1[8];
    UINT32 bitn_byte_offset_1[8];

    /* tab used to pass VP9 probs */
    UADDR tab_phy_addr;
    UADDR cnt_phy_addr;

    UINT32 segment_feature_dat0[4];
    UINT32 segment_feature_dat1[4];
    UINT32 ref_lf_delta[4];
    UINT32 mode_lf_delta[4];
    UINT32 ref_frame_sign_bias[4];

    /*img phy addr pass to VDH*/
    UADDR image_curr_rcn_addr;
    UADDR image_alt_ref_addr;
    UADDR image_gld_ref_addr;
    UADDR image_last_ref_addr;
    UADDR CurrPmvAddr;
    UADDR SegIdAddr;
    UINT32 SegIdStride;
    UINT32 CompressEn;
    SINT32 LossCompressEn;
    UINT8  LossLow2BitsEn;
    SINT32 YCompRatio;
    SINT32 UVCompRatio;

    UINT32 VdhMmuEn;
    UINT32 mbinfo_offset;
    UADDR line_num_addr;
    UINT32 HeadStride;
    UINT32 HeadInfoSize;

    UINT32 Stride_nbit;
    UINT32 YOffset_2bit;
    UINT32 UVOffset_2bit;

    SINT32 pic_width[3];
    SINT32 pic_height[3];
}VP9_DEC_PARAM_S;
#endif


/***********************************************************/
/****************for mvc********************/
/**********************************************************/
#ifdef VFMW_MVC_SUPPORT
#define   MVC_MIN_LEVEL                 10
#define   MVC_MAX_LEVEL                 41
#define   MVC_QMATRIX_NUM                    56

typedef H264_DEC_LIST_S                     MVC_DEC_LIST_S;
typedef H264_DEC_SLICE_PARAM_S       MVC_DEC_SLICE_PARAM_S;
typedef H264_DEC_PIC_PARAM_S           MVC_DEC_PIC_PARAM_S;
#endif

/************************************************************/
/*****come from vdm_hal_mpeg2.h, by lkf56013*****************/
/***********************************************************/
/* MPEG2Э��Ľ�������ṹ */
#ifdef VFMW_MPEG2_SUPPORT
#define MP2_MAX_SLC_PARAM_NUM  1024//512  //���Slice����

typedef struct
{
    UADDR    BsPhyAddr[2];
    SINT32  BsLenInBit [2];
    SINT32  BsBitOffset[2];
    SINT32  BsID[2];
    UINT32  slice_start_mbn;
    SINT32  intra_slice;
    SINT32  quantiser_scale_code;
} MP2_SLCSTR_S;

typedef struct
{
    UINT8     PicCodingType;
    UINT8     Mp1BwdmvFullPel;
    UINT8     Mp1FwdmvFullPel;
    UINT8     PictureStructure;
    UINT8     SecondFieldFlag;
    UINT8     FramePredFrameDct;
    UINT8     TopFieldFirst;
    UINT8     ConcealmentMotionVectors;
    UINT8     AlternateScan;
    UINT8     IntraVlcFormat;
    UINT8     QuantType;
    UINT8     IntraDcPrecision;
    UINT8     Fcode[4];
    UINT8     NonIntraQuantTab[64];
    UINT8     IntraQuantTab[64];
    UINT8     linear_en;
    /* �������� */
    /* BEGIN: Added 2010/9/13 */
    UINT8     EstmatedPicQp;
    /* END:   Added 2010/9/13 */

    UINT16    PicHeightInMb;
    UINT16    FrameHeightInMb;
    UINT16    PicWidthInMb;

    UADDR     StreamPhyAddr[2];
    UINT32    StreamBitOffset[2];
    SINT32    StreamLength[2];
    UINT32    Mpeg1Flag;

    /* ����ͼ��(����ο�ͼ)�ĵ�ַ */
    UADDR     BwdRefPhyAddr;
    UADDR     FwdRefPhyAddr;
    UADDR     CurPicPhyAddr;

    UINT32    BwdRefIsFldSave;
    UINT32    FwdRefIsFldSave;

    /* ��ʾͼ�������ַ */
    UADDR     DispFramePhyAddr;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    //add fordsp 2013-04-25
    UADDR       CurPicLineNumAddr;
    //end add
#endif

    UINT32    VahbStride;
    UINT32    UvOffset;
    UINT32    HeadStride;
    UINT32    HeadInfoSize;
    UADDR    PmvColmbPhyAddr;
    //FRAME_POOL_S      *pFramePool;  /* ����֡���ַ��id֮�以�� */

    UINT32    AdjustQpDb;
    UINT32    AdjustQpDr;

    MP2_SLCSTR_S SlcStr[MP2_MAX_SLC_PARAM_NUM];
    UINT32       SlcNum;

    UINT32    CompressEn;
    UINT32    VdhMmuEn;
} MP2_DEC_PARAM_S;
#endif
/************************************************************/
/********come from vdm_hal_mpeg4.h, by lkf56013****************/
/***********************************************************/
#define MAX_SLICE_NUM_IN_VOP  512   //�����������slice num Ϊ475
//����ʼ������Cfg_Tab����
#ifdef VFMW_MPEG4_SUPPORT
typedef struct
{
    UINT8      *MvdPrefixVirAddr;
    UINT8      *MvdSuffixVirAddr;
    UINT8      *DctIntraPrefixVirAddr;
    UINT8      *DctIntraSuffixVirAddr;
    UINT8      *DctInterPrefixVirAddr;
    UINT8      *DctInterSuffixVirAddr;
    UINT8      *InterEscpVirAddr;
    UINT8      *IntraEscpVirAddr;

    SINT32      MvdPrefixSize; //
    SINT32      MvdSuffixSize;
    SINT32      DctIntraPrefixSize;
    SINT32      DctIntraSuffixSize;
    SINT32      DctInterPrefixSize;
    SINT32      DctInterSuffixSize;
    SINT32      InterEscpSize;
    SINT32      IntraEscpSize;
} MP4_CODE_TAB_S;

//slice info
typedef struct
{
    UINT8   start_code_bit_offset;
    UINT8   vop_fcode_forward;
    UINT8   vop_fcode_backward;
    UINT8   intra_dc_vlc_thr;
    UINT8   vop_coding_type;
    UINT8   vop_quant;
    UINT8   bit_offset[2];
    UINT32  bit_len[2];
    UADDR   phy_address[2];
    UINT32  mb_start_num;
} MP4_SLICE_INFO;

typedef struct
{
    UINT8       PicCodingType;            //p_syntax_des->syn_vop.vop_coding_type
    UINT8       PicQuantType;             //p_syntax_des->syn_vol.quant_type
    UINT8       IsShortHeader;            //p_syntax_des->is_short_header
    UINT8       VopQuant;                 //p_syntax_des->syn_vop.vop_quant
    UINT8       GobMbNum;                 //p_syntax_des->syn_vop.num_mb_ingob
    UINT8       VopGobNum;                //p_syntax_des->syn_vop.num_gobs_invop
    UINT8       BitsOfVopTimeIncr;        //p_syntax_des->syn_vol.vop_time_incr_bits
    UINT8       FwdFcode;                 //p_syntax_des->syn_vop.vop_fcode_forward
    UINT8       BwdFcode;                 //p_syntax_des->syn_vop.vop_fcode_backward
    UINT8       intra_dc_vlc_thr;         //p_syntax_des->syn_vop.intra_dc_vlc_thr
    UINT8       resync_marker_disable;    //p_syntax_des->syn_vol.resync_marker_disable
    UINT8       QuarterSample;            //p_syntax_des->syn_vol.quarter_sample
    UINT8       vop_rounding_type;        //p_syntax_des->syn_vop.vop_rounding_type
    UINT8       alternate_vertical_scan;  //p_syntax_des->syn_vop.alternate_vertical_scan_flag
    UINT8       top_field_first;          //p_syntax_des->syn_vop.top_field_first
    UINT8       Interlaced;               //p_syntax_des->syn_vol.interlaced
    UINT8      *StreamVirAddr[2];
    UINT8       IntraQuantTab[64];        //p_syntax_des->syn_vol.intra_quant_mat[]
    UINT8       NonintraQuantTab[64];     //p_syntax_des->syn_vol.nonintra_quant_mat[]
    UINT8       FF_BUG_EDGE_FIND_POINT;
    UINT8       FF_BUG_EDGE_EXTEND;
    UINT8       FF_BUG_DIVX500B413;
    UINT8       FF_BUG_QPEL_CHROMA;
    UINT8       FF_BUG_QPEL_CHROMA2;
    UINT8       FF_BUG_QPEL_FILED;

    //UINT32      AcdcPredDataAddr;
    UINT8      IsNvopCopy;

    UINT8      linear_en;
    MP4_CODE_TAB_S   *pMp4CodeTab;

    UINT16      PicWidthInMb;             //( p_syntax_des->image_width+ 15 ) >> 4;
    UINT16      PicHeightInMb;            //( p_syntax_des->image_height+ 15 ) >> 4;

    UADDR       StreamBaseAddr;
    UINT32      StreamSegID;
    SINT32      StreamFirstIsLastFlag;
    UADDR       StreamPhyAddr[2];         //g_BitsObj.phy_addr&(0xFFFFFFF0) �� ptr_strm_para->StreamPack[1].PhyAddr &(0xFFFFFFF0)
    UINT32      StreamBitOffset[2];
    SINT32      StreamLength[2];
    UINT32      Trb;                      //p_syntax_des->time_bp
    UINT32      Trd;                      //p_syntax_des->time_pp
    UADDR       CurPicPhyAddr;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
    //add fordsp 2013-04-25
    UADDR       CurPicLineNumAddr;
    //end add
#endif
    UADDR       FwdRefPicPhyAddr;
    UADDR       BwdRefPicPhyAddr;
    UADDR       CurPmvPhyAddr;
    UADDR       BwdPmvPhyAddr;

    /* slice info */
    MP4_SLICE_INFO SlcPara[MAX_SLICE_NUM_IN_VOP];
    UINT32      SlcNum;

    /* ��ʾͼ�������ַ */
    UADDR     DispFramePhyAddr;

    UINT32    AdjustQpDb;
    UINT32    AdjustQpDr;

    UINT32    YStride;
    UINT32    UVStride;
    UINT32    UVOffset;
    UINT32    HeadStride;
    UINT32    HeadInfoSize;
    //GMC
    UINT32    image_height;
    UINT32    image_width;
    UINT32    sprite_enable;
    UINT32    sprite_warping_points;
    UINT32    sprite_warping_accuracy;
    SINT32    dU[2];
    SINT32    dV[2];
    SINT32    Uo;
    SINT32    Vo;
    SINT32    Uco;
    SINT32    Vco;
    UINT32    CompressEn;
    UINT32    VdhMmuEn;
} MP4_DEC_PARAM_S;
#endif
/*******************************************************/
/***come from vdm_hal_real8.h, by lkf56013******************/
/*******************************************************/
#ifdef VFMW_REAL8_SUPPORT
#define RV8_MAX_SLC_PARAM_NUM  256  //���Slice����

typedef struct
{
    UADDR     StreamPhyAddr[2];
    UINT32    StreamBitOffset[2];
    SINT32    StreamLength[2];

    SINT32    dblk_filter_passthrough;
    SINT32    osvquant;
    SINT32    sliceqp;
    SINT32    first_mb_in_slice;
    SINT32    last_mb_in_slice;
} RV8_SLC_PARAM_S;

/* REAL8Э��Ľ�������ṹ */
typedef struct
{
    UINT8     linear_en;

    UINT32    PicWidthInMb;
    UINT32    PicHeightInMb;

    UINT8     PicCodingType;
    UINT32    Ratio0;
    UINT32    Ratio1;
    UINT32    PQUANT;
    UINT32    PrevPicQP;
    UINT32    PrevPicMb0QP;
    UINT32    TotalSliceNum;
    UINT32    FstSlcGrp;
    UADDR     StreamBaseAddr;

    /* ����ͼ��(����ο�ͼ)�ĵ�ַ */
    UADDR     BwdRefPhyAddr;
    UADDR     FwdRefPhyAddr;
    UADDR     CurPicPhyAddr;

    /* ��ʾͼ�������ַ */
    UADDR     DispFramePhyAddr;

    UINT32    DDRStride;
    UADDR     CurrPmvPhyAddr;
    UADDR     ColPmvPhyAddr;

    UINT32    CompressEn;
    UINT32    VdhMmuEn;
    UINT32    UVOffset;
    UINT32    HeadStride;
    UINT32    HeadInfoSize;

    RV8_SLC_PARAM_S   SliceParam[RV8_MAX_SLC_PARAM_NUM];
    //FRAME_POOL_S      *pFramePool;  /* ����֡���ַ��id֮�以�� */
} RV8_DEC_PARAM_S;
#endif
/**********************************************************/
/******come from vdm_hal_real9.h, by lkf56013**************/
/**********************************************************/
#ifdef VFMW_REAL9_SUPPORT
#define RV9_MAX_SLC_PARAM_NUM  256  //���Slice����

typedef struct
{
    UADDR     StreamPhyAddr[2];
    UINT32    StreamBitOffset[2];
    SINT32    StreamLength[2];

    SINT32    dblk_filter_passthrough;
    SINT32    osvquant;
    SINT32    sliceqp;
    SINT32    first_mb_in_slice;
    SINT32    last_mb_in_slice;
} RV9_SLC_PARAM_S;

/* REAL9Э��Ľ�������ṹ */
typedef struct
{
    UINT8     PicCodingType;
    UINT8     linear_en;
    UINT32    PicWidthInMb;
    UINT32    PicHeightInMb;

    UINT32    Ratio0;
    UINT32    Ratio1;
    UINT32    PQUANT;
    UINT32    PrevPicQP;
    UINT32    PrevPicMb0QP;
    UINT32    TotalSliceNum;
    UINT32    FstSlcGrp;
    UADDR     StreamBaseAddr;

    /* ����ͼ��(����ο�ͼ)�ĵ�ַ */
    UADDR     BwdRefPhyAddr;
    UADDR     FwdRefPhyAddr;
    UADDR     CurPicPhyAddr;

    /* ��ʾͼ�������ַ */
    UADDR     DispFramePhyAddr;

    UINT32    DDRStride;
    UADDR     CurrPmvPhyAddr;
    UADDR     ColPmvPhyAddr;

    UINT32    CompressEn;
    UINT32    VdhMmuEn;
    UINT32    UVOffset;
    UINT32    HeadStride;
    UINT32    HeadInfoSize;

    RV9_SLC_PARAM_S   SliceParam[RV9_MAX_SLC_PARAM_NUM];
    //FRAME_POOL_S      *pFramePool;  /* ����֡���ַ��id֮�以�� */
} RV9_DEC_PARAM_S;
#endif

#ifdef VFMW_DIVX3_SUPPORT
/* DIVX3Э��Ľ�������ṹ */
typedef struct
{
    UINT8  linear_en;

    UINT32 prediction_type;

    UINT32 PicWidthInMb;
    UINT32 PicHeightInMb;

    UINT32 quantizer;
    UINT32 rounding_type;
    UINT32 has_skips;

    UINT32 alternative_I_AC_chrom_DCT;  // 0/1: 311_0, 2: 311_10, 3: 311_11
    UINT32 alternative_I_AC_lum_DCT;    // 0/1: 311_0, 2: 311_10, 3: 311_11
    UINT32 alternative_I_DC_DCT;        // 0: 311_0, 1: 311_1
    UINT32 alternative_P_AC_DCT;        // 0/1: 311_0, 2: 311_10, 3: 311_11
    UINT32 alternative_P_DC_DCT;        // 0: 311_0, 1: 311_1
    UINT32 alternative_MV;              // 0: 311_0, 1: 311_1

    UINT32 TotalSliceNum;
    UINT32 slice_start_mbn[5];
    UINT32 slice_end_mbn[5];

    UADDR  StreamBaseAddr;

    UADDR  StreamPhyAddr[2];
    UINT32    StreamBitOffset[2];
    SINT32    StreamLength[2];

    /* ����ͼ��(����ο�ͼ)�ĵ�ַ */
    UADDR  FwdRefPhyAddr;
    UADDR  CurPicPhyAddr;

    /* ��ʾͼ�������ַ */
    UADDR  DispFramePhyAddr;

    UINT32    DDRStride;
    UINT32    UVOffset;
    UINT32    HeadStride;
    UINT32    HeadInfoSize;
    UADDR  CurrPmvPhyAddr;
    UADDR  ColPmvPhyAddr;
    SINT32    CompressEn;
    UINT32    VdhMmuEn;
    //FRAME_POOL_S      *pFramePool;  /* ����֡���ַ��id֮�以�� */
} DIVX3_DEC_PARAM_S;
#endif

/**********************************************************/
/**************come from vc1.h, by lkf56013****************/
/**********************************************************/
#ifdef VFMW_VC1_SUPPORT

#define VC1VFMW_MAX_SLC_NUM    256//128
#define VC1VFMW_MAX_PIC_WIDTH  128 //unit: MB
#define VC1VFMW_MAX_PIC_HEIGHT 128 //unit: MB
#define VC1VFMW_MAX_PIC_MB (VC1VFMW_MAX_PIC_WIDTH * VC1VFMW_MAX_PIC_HEIGHT) //16129 //unit: MB

/******************************************************/
/********come from vdm_hal_vc1.h, by lkf56013**********/
/******************************************************/
typedef struct
{
    UINT8 *pStream;
    UINT8 *pStream2;
    UINT8  SlcNo;

    UADDR  Phy_addr;
    SINT32 BitOffset;
    SINT32 Len;
    SINT32 SlcEndMbn;
    UADDR  Phy_addr2;
    SINT32 BitOffset2;
    SINT32 Len2;
    SINT32 StreamID;
    SINT32 StreamID2;
} VC1_SLCSTREAM_S;

/* VC1Э��Ľ�������ṹ */
typedef struct
{
    UINT8 picstructure;
    UINT8 IsSkpicCopy;
    UINT8 NoBitplaneFlag;
    //PIC������Ϣ
    UINT8 ptype;
    UINT8 profile;
    UINT8 fcm;
    UINT8 loopfilter ;
    UINT8 issecondfld;
    UINT8 curparity  ;
    UINT8 numref     ;
    UINT8 fwd_fcm    ;
    UINT8 bwd_fcm    ;
    UINT8 rndctrl    ;
    UINT8 fastuvmc   ;
    UINT8 overlap    ;
    UINT8 condover   ;
    UINT8 pquant     ;
    UINT8 pqindex    ;
    UINT8 altpquant  ;
    UINT8 halfqp     ;
    UINT8 buniform   ;
    UINT8 usealtqp   ;
    UINT8 dquant     ;
    UINT8 dqprofile  ;
    UINT8 dqbilevel  ;
    UINT8 dquantfrm  ;
    UINT8 quantmode  ;
    UINT8 mvmode     ;
    UINT8 mvmode2    ;
    UINT8 curishalfpel;
    UINT8 colishalfpel;
    UINT8 mvrange     ;
    UINT8 refdist     ;
    UINT8 dmvrange    ;
    UINT8 reffiled    ;
    UINT8 transdctab  ;
    UINT8 vstransform ;
    UINT8 ttmbf       ;
    UINT8 transacfrm  ;
    UINT8 transacfrm2 ;
    UINT8 ttfrm       ;
    UINT8 forwardmbmodeisskipraw ;
    UINT8 directmbmodeisskipraw  ;
    UINT8 mvtypembmodeisskipraw  ;
    UINT8 fieldtxmodeisskipraw   ;
    UINT8 skipmbmodeisskipraw    ;
    UINT8 acpredmodeisskipraw    ;
    UINT8 overflagsmodeisskipraw ;
    UINT8 mvtab      ;
    UINT8 cbptab     ;
    UINT8 bfraction  ;
    UINT8 mbmodetab    ;
    UINT8 twomvbptab   ;
    UINT8 fourmvbptab  ;
    UINT8 fourmvswtich ;
    UINT8 rangemapyflag   ;
    UINT8 rangemapy       ;
    UINT8 rangemapuvflag  ;
    UINT8 rangemapuv      ;
    UINT8 RANGEREDFRM  ;
    UINT8 RANGEREDFRM0 ;
    UINT8 RANGEREDFRM1 ;
    UINT8 PostCresent  ;
    UINT8 CodecVersion ;
    UINT8 *pIntensityConvertTab;
    UINT8 ref_pic_type;
    UINT8 ff_apt_en;
    //SLICE������Ϣ
    UINT8 SlcNum;
    UINT8 linear_en;

    UINT16 totalslicenum   ;
    UINT16 DispPicWidth ;
    UINT16 DispPicHeight;

    UINT16 mbwidth;
    UINT16 mbheight;

    VC1_SLCSTREAM_S     SlcStr[VC1VFMW_MAX_SLC_NUM];

    UINT32 ScaleFactor ;
    UINT32 FRFD ;
    UINT32 BRFD ;
    UADDR  CurFrmImgLuma2dPhyAddr  ;
    UADDR  FwdRefAddr  ;
    UADDR  BwdRefAddr  ;
    UADDR  CurrColmbAddr  ;
    UADDR  BwdColmbAddr  ;

    UINT32 BPD_STRIDE;
    UADDR  MVTYPEMB_ADDR;
    UADDR  SKIPMB_ADDR;
    UADDR  DIRECTMB_ADDR;
    UADDR  ACPRED_ADDR;
    UADDR  OVERFLAGS_ADDR;
    UADDR  FIELDTX_ADDR;
    UADDR  FORWARDMB_ADDR;

    //PIC������Ϣ
    UINT32 PicCnt;

    //BITPLANE������Ϣ
    UINT32 BitPlaneNum;
#ifndef VFMW_BPD_H_SUPPORT
    UINT32 vc1bitplane[VC1VFMW_MAX_PIC_MB];
#endif
    //�Ĵ���

    //reg tmp
    UINT32  vdh_start;
    UINT32  vdh_repair;
    UINT32  basic_cfg0;
    UINT32  basic_cfg1;
    //UINT32  avm_addr;
    //UINT32  vam_addr;
    UADDR   stream_base_addr;

    UINT32 YStride;
    UINT32 UVStride;
    UINT32 UVOffset;
    UINT32 HeadStride;
    UINT32 HeadInfoSize;

    UINT32  emar_id;
    UINT32  sed_to;
    UINT32  itrans_to;
    UINT32  pmv_to;
    UINT32  prc_to;
    UINT32  rcn_to;
    UINT32  dblk_to;
    UINT32  ppfd_to;

    UADDR   ystaddr_1d;
    UADDR   ystride_1d;
    UINT32  uvoffset_1d;

    UINT32  prcnum_1d_cnt;
    UINT32  prcnum1_1d_cnt;
    UINT32  prcnum2_1d_cnt;

    UADDR   ppfd_buf_addr;
    UINT32  ppfd_buf_len;
    UINT32 CompressEn;
    UINT32 VdhMmuEn;
    SINT32 ChanMaxWidthInMb;
    SINT32 ChanMaxHeightInMb;
} VC1_DEC_PARAM_S;
#endif

#ifdef VFMW_VP6_SUPPORT
typedef struct
{
    UINT8    FLimit;
    UINT8    IsNvopCopy;
    UINT8     *TblProbModeSame;
    UINT8     *TblProbMode;
    UINT8     *TblProbMv;  //include IsMvShort,MvSign,Mvshort,Mvlong.

    UINT8    *TblModifiedScanOrder;
    UINT8    *TblEobOffsetTable;
    UINT8    *TblHuffTree;
    UINT8    *TblDcNodeContexts;   //used for boolcoder
    UINT8   *TblACProbs;
    UINT8   *TblZeroProbs;

    UINT8     *TblDcHuffLUT;
    UINT8     *TblAcHuffLUT;
    UINT8     *TblZeroHuffLUT;
    UINT8    linear_en;
    UINT16   PicWidthInMb;
    UINT16   PicHeightInMb;

    UADDR   StreamBaseAddr;
    //UINT32    StreamSegID[2];

    /*vfmw vp6 info to sed*/
    UINT32  FrameType;
    UINT32  DctQMask;
    UINT32  MultiStream;
    UINT32  UseHuffman;

    UINT32  DcQuant;
    UINT32  AcQuant;

    UINT32  PredictionFilterMode;
    UINT32  PredictionFilterVarThresh;
    UINT32  PredictionFilterMvSizeThresh;
    UINT32  PredictionFilterAlpha;

    UINT32  Vp3VersionNo;
    UINT32  VpProfile;
    //UINT32  ScalingMode;

    //UINT32  RefreshGoldenFrame;
    UINT32  UseLoopFilter;

    /*the fisrt bitstream part*/
    UINT32  bit0_len_0;
    UINT32  bit0_offset_0;
    UADDR   bit0_stream_addr_0;

    UINT32  bit0_len_1;
    UINT32  bit0_offset_1;
    UADDR   bit0_stream_addr_1;

    /*the second bitstream part*/
    UINT32  bit1_len_0;
    UINT32  bit1_offset_0;
    UADDR   bit1_stream_addr_0;
    UINT32  bit1_len_1;
    UINT32  bit1_offset_1;
    UADDR   bit1_stream_addr_1;

    /* Current access points fopr input and output buffers */
    UINT32 value;
    UINT32 range;
    UINT32 count;

    UADDR   image_curr_recon_addr;
    UADDR   image_golden_ref_addr;
    UADDR   image_last_ref_addr;
    UADDR   CurPmvAddr;
    //UINT32  sed_top_addr;
    //UINT32  pmv_top_addr;
    //UINT32  rcn_top_addr;

    UINT32     YStride;
    UINT32     UVStride;
    UINT32     UVOffset;
    UINT32     HeadStride;
    UINT32     HeadInfoSize;
    UINT32     CompressEn;
    UINT32     VdhMmuEn;
} VP6_DEC_PARAM_S;
#endif

#ifdef VFMW_VP8_SUPPORT
typedef struct
{
    UINT8 table[2752];//3000
    UINT8 prob_skip_false;
    UINT8 mb_no_coeff_skip;
    UINT8 multi_token_partition;

    UINT8 segmentation_enable;
    UINT8 update_mb_segmentation_map;
    UINT8 mb_segmentation_abs_delta;
    UINT8 mode_ref_lf_delta_enabled;

    UINT8 base_qindex;
    UINT8 filter_type;
    UINT8 last_filter_type;
    UINT8 filter_level;
    UINT8 sharpness_level;
    UINT8 last_sharpness_level;

    UINT8 y1dc_sign;
    UINT8 y1dc_absdelta_q;
    UINT8 y2dc_sign;
    UINT8 y2dc_absdelta_q;
    UINT8 y2ac_sign;
    UINT8 y2ac_absdelta_q;
    UINT8 uvdc_sign;
    UINT8 uvdc_absdelta_q;
    UINT8 uvac_sign;
    UINT8 uvac_absdelta_q;
    UINT8 prob_intra;
    UINT8 prob_last;
    UINT8 prob_gf;
    UINT8 linear_en;
    /* bool coder element */
    UINT8 range;
    UINT8 count;
    UINT32 value;

    UINT32 pic_width_in_mb;
    UINT32 pic_height_in_mb;
    UINT32 ddr_stride;
    UINT32 frame_type;
    UINT32 last_frame_type;

    UINT32 use_bilinear_mc_filter;
    UINT32 full_pixel;

    UADDR  stream_base_addr;

    /* the fisrt bitstream part */
    UINT32 bit_len_0;
    UINT32 bit_offset_0;
    UINT32 bit_byte_offset_0;

    UINT32 bit_len_1;
    UINT32 bit_offset_1;
    UINT32 bit_byte_offset_1;

    /*the second bitstream part*/
    UINT32 stream_num_part;

    UINT32 bitn_len_0[8];
    UINT32 bitn_offset_0[8];
    UINT32 bitn_byte_offset_0[8];

    UINT32 bitn_len_1[8];
    UINT32 bitn_offset_1[8];
    UINT32 bitn_byte_offset_1[8];

    UINT32 segment_feature_dat0[4];
    UINT32 segment_feature_dat1[4];
    UINT32 ref_lf_delta[4];
    UINT32 mode_lf_delta[4];
    UINT32 ref_frame_sign_bias[4];

    /*img phy addr pass to VDH*/
    UADDR  image_curr_rcn_addr;
    UADDR  image_alt_ref_addr;
    UADDR  image_gld_ref_addr;
    UADDR  image_last_ref_addr;
    UADDR  CurrPmvAddr;
    UADDR  SegIdAddr;
    UINT32 CompressEn;
    UINT32 VdhMmuEn;
    UINT32 UVOffset;
    UINT32 HeadStride;
    UINT32 HeadInfoSize;
} VP8_DEC_PARAM_S;
#endif


#ifdef __cplusplus
}
#endif


#endif
