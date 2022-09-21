#ifndef __VDEC_FIRMWARE_SECURE_H__
#define __VDEC_FIRMWARE_SECURE_H__
#if defined(VFMW_EXTRA_TYPE_DEFINE)
#include "hi_type.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "vfmw.h"

/***********************************************************************
      structures
 ***********************************************************************/

/* channel config info */
typedef struct hiCHAN_CFG_SECURE_S
{
    SINT32           eVidStd;            /* video compressing standard */
    STD_EXTENSION_U  StdExt;             /* extended info, for VC1 indicate AP or not, and other version info */
    SINT32           s32ChanPriority;    /* channel priority */
    SINT32           s32ChanErrThr;      /* channel error torlerance threshold. 0: zero torlerance; 100: display no matter how many error occured */
    SINT32           s32ChanStrmOFThr;   /* stream overflow control threshold, must >= 0, 0 means do not enable overflow control */
    DEC_MODE_E       s32DecMode;         /* decode mode，0：IPB， 1：IP， 2：I */
    SINT32           s32DecOrderOutput;  /* 0: output by display order，1:output by decode order */
    SINT32           s32DnrTfEnable;
    SINT32           s32DnrDispOutEnable;
    SINT32           s32BtlDbdrEnable;
    SINT32           s32Btl1Dt2DEnable;
    SINT32           s32LowdlyEnable;    /* lowdly enable */
    SINT32           s32SedOnlyEnable;    /* sedonly enable */
    SINT32           s32VcmpEn;          /* frame compress enable */
    SINT32           s32WmEn;            /* water marker enable */
    SINT32           s32VpssInfoEn;            /* vpss info enable */
    SINT32           s32VcmpWmStartLine; /* water marker start line number */
    SINT32           s32VcmpWmEndLine;   /* water marker end line number */
    SINT32           s32SupportAllP;     /* support stream of all p frames */
    SINT32           s32ModuleLowlyEnable;
    SINT32           s32ChanLowlyEnable;
    SINT32           s32IsOmxPath;       /* specify for omx path */
    SINT32           s32MaxRawPacketNum;
    SINT32           s32MaxRawPacketSize;
    SINT32           s32ExtraFrameStoreNum;
    SINT32           s32MaxWidth;
    SINT32           s32MaxHeight;/*if the stream to be decoded w*h > s32MaxWidth*s32MaxHeight vfmw will stop syntax stream*/
    SINT8            s8BeHDRChan;/*0:not hdr chan, 1:hdr chan*/
    SINT8            isMiracastChan;
#ifdef DOLBY_VISION_HDR_SUPPORT
    DV_CODEC_CAP_E_  dv_codec_capacity;/*only s8BeHDRChan==1 useful*/
    DV_VES_IMP_E_    ves_imp;/*only s8BeHDRChan==1 useful*/
    DV_LAYER_IMP_E_  layer_imp;/*only s8BeHDRChan==1 useful*/
#endif
    HI_BOOL           b98mv200Vp9Burst;
    UINT32            hVdecHandle;
} VDEC_CHAN_CFG_SECURE_S;

/* BEGIN: Added  for HDR */
/* decoded Colour description info */
typedef struct
{
    UINT8  FullRangeFlag;
    UINT8 ColourPrimaries;
    UINT8 MatrixCoeffs;
} COLOUR_DESCRIPTION_INFO_SECURE_S;

typedef struct
{
    UINT8 YUV_RANGE;       //Informs on the range of the YUV input signal
    UINT8 HDRContainerCS;    //Gives the color space of the original HDR video container
    UINT8 HDRContentCS;      //Informs on the content HDR YUV color space
    UINT8 LDRContentCS;      //Informs on the content LDR YUV color space
    UINT32 PeakLuma ;        //Peak luminance of the sequence, in NITs.
    SINT32 OCT[7];  //Signed array of seven integers, depending on COLOR_CONTAINER parameter
} TECHNICOLOR_HDR_SEQ_PARAMS;//"static" parameters

typedef struct
{
    UINT32 BA; //Used to compute the content of the P_LUT, once per picture
} TECHNICOLOR_HDR_FRM_PARAMS;//"danamic" parameters


typedef struct
{
    UINT8 IsValid;
    TECHNICOLOR_HDR_SEQ_PARAMS TCH_HDR_StaticParms;
    TECHNICOLOR_HDR_FRM_PARAMS TCH_HDR_DanamicParms;
} TECHNICOLOR_HDR_INFO_S;
/* END: Added  for HDR */

typedef struct
{
    UINT32      u32AspectWidth;
    UINT32      u32AspectHeight;

    UINT32      DispEnableFlag;
    UINT32      DispFrameDistance;
    UINT32      DistanceBeforeFirstFrame;
    UINT32      GopNum;
    UINT32      u32RepeatCnt;

    UADDR       top_luma_phy_addr;
    UADDR       top_chrom_phy_addr;
    UADDR       btm_luma_phy_addr;
    UADDR       btm_chrom_phy_addr;

    UADDR       luma_phy_addr;
    UADDR       chrom_phy_addr;
    UADDR       luma_tf_phy_addr;
    UADDR       chrom_tf_phy_addr;
    UADDR       luma_2d_phy_addr;
    UADDR       chrom_2d_phy_addr;

    //HEVC 10bit

    UADDR       luma_2bit_phy_addr;

    UADDR       chrom_2bit_phy_addr;

    //DBM Info
    UADDR       dbm_info_phy_addr;
    UINT32      dbm_vaild;
    UINT32      dbm_qp_avg;
    UINT32      dbm_info_stride;
    UINT32      dbm_info_size;

    UINT32      is_fld_save;  //0:frm, 1:fld
    UINT32      top_fld_type;
    UINT32      bottom_fld_type;

    UINT32      format;                           /* [1:0] frame_type: 00(I), 01(P), 10(B), 11(Reserved)*/
    /* [4:2] CSP: 000(YUV:4:2:0), 001(YUV:4:0:0), 010~111(Reserved)*/
    /* [7:5] Norm: 000(component), 001(PLA), 010(NTSC), 011(SECAM), 100(MAC), 101(Unspecified Video Format), 110~111(Reserved)*/
    /* [9:8] source_format: 00(progressive), 01(interlaced), 10(infered_progressive), 11(infered_interlaced)*/
    /* [11:10] field_valid_flag: 00(top_field invalid, bottom_field invalid), 01(top_field valid, bottom_field invalid),
                                            10(top_field invalid, bottom_field valid), 11(top_field valid, bottom_field valid)*/
    /* [13:12]top_field_first: 00(bottom field first), 01(top field first), 10(un-know), 11(Reserved)*/
    /* [16:14] aspect_ratio: 000(unspecified), 001(4:3), 010(16:9), 011(2.21:1),100(2.35:1),101(origin width and height), 111(Reserved)*/
    /* [17] yuv_2d_en, 0:1d, 1:2d*/
    /* [18] yuv_cmp: 0:raw yuv, 1:compress yuv*/
    /* [31:19](Reserved)*/
    UINT32      image_width;
    UINT32      image_height;
    UINT32      disp_width;
    UINT32      disp_height;
    UINT32      disp_center_x;
    UINT32      disp_center_y;

    UINT32      frame_rate;     /* frame rate, in Q10 */
    UINT32      image_stride;
    UINT32      head_stride;
    UINT32      head_info_size;
    UINT32      image_stride_2bit;
    UINT32      image_id;
    UINT32      error_level;
    UINT32      seq_cnt;
    UINT32      seq_img_cnt;


    UINT32      chroma_idc;
    UINT32      bit_depth_luma;
    UINT32      bit_depth_chroma;
    UINT32      frame_num;
    SINT32      last_frame;
    SINT32      view_id;      //h264 mvc
    SINT32      image_id_1;
    UINT32      is_3D;
    UADDR       top_luma_phy_addr_1;
    UADDR       top_chrom_phy_addr_1;
    UADDR       btm_luma_phy_addr_1;
    UADDR       btm_chrom_phy_addr_1;
    UADDR       line_num_phy_addr;

    UINT32 HDR_Metadata_size;
    UINT32 HDR_Metadata_phy_addr;
    UINT64 HDR_Metadata_vir_addr;
    UINT8  MasteringAvailable;
    UINT8  ContentAvailable;
    UINT32 TransferCharacteristics;
    COLOUR_DESCRIPTION_INFO_SECURE_S ColourInfo;
    MASTERING_DISPLAY_COLOUR_VOLUME_S MasteringDisplayColourVolume;
    CONTENT_LIGHT_LEVEL_INFO_S ContentLightLevel;
    HLG_COMPATIBLE_INFO_S ComapitibilityInfo;
    TECHNICOLOR_HDR_INFO_S TechnicolorInfo;

    /* BEGIN: Added  for hevc */
    UINT32      left_offset;
    UINT32      right_offset;
    UINT32      top_offset;
    UINT32      bottom_offset;
    /* END: Added  for hevc */

    /* Begin: UvMOS parameter */
    UINT32      AvgQp;
    UINT32      FrameStreamSize;
    UINT32      MaxMV;
    UINT32      MinMV;
    UINT32      AvgMV;
    UINT32      SkipRatio;
    /* End:   UvMOS parameter */

#ifdef VFMW_BVT_SUPPORT
    UINT32      luma_sum_h;
    UINT32      luma_sum_l;
    UINT32      luma_historgam[32];
    SINT32      compress_luma_offset;
    SINT32      compress_chroma_offset;
#endif

    UINT16      DispCtrlWidth;
    UINT16      DispCtrlHeight;

    UINT32      is_SecureFrame;                    /*add for tvp support*/

    UINT32      is_1Dcompress;
    FRAME_PACKING_TYPE_E  eFramePackingType;
    IMAGE_DNR_S ImageDnr;
    IMAGE_BTL_S BTLInfo;
    /* BEGIN:  2010/8/19 */
    VDEC_OPTMALG_INFO_S optm_inf;
    /* END:   2010/8/19 */
    UINT64     dbm_info_vir_addr;
    UINT64     luma_vir_addr;
    UINT64     chrom_vir_addr;
    UINT64     luma_2d_vir_addr;
    UINT64     chrom_2d_vir_addr;
    UINT64     line_num_vir_addr;
    UINT64     luma_2bit_vir_addr;
    UINT64     chrom_2bit_vir_addr;
    //VDEC_USRDAT_S     *p_usrdat[4];
    UINT64      p_usrdat[4]; //存储的
    UINT64      SrcPts;
    UINT64      PTS;
    UINT64      Usertag;
    UINT64      DispTime;

    VID_STD_E   eVidStd;
} IMAGE_SECURE;

typedef struct
{
    MEM_DESC_S  ChanMemVdh;
    MEM_DESC_S  ChanMemScd;
    MEM_DESC_S  ChanMemCtx;
    MEM_DESC_S  ChanMemRpu; //for Dolby Vision HDR metadata
    MEM_DESC_S  ChanMemEs;
} VDEC_SECURE_CHAN_MEM_DETAIL_S;


/* user defined channel option*/
typedef struct
{
    VDEC_ADAPTER_TYPE_E eAdapterType;          /* channel type vdec/omxvdec */
    VDEC_CHAN_PURPOSE_E Purpose;               /* channel purpose, indicate if this channel is used for decoding or frame path only*/
    VDEC_CHAN_MEM_ALLOC_MODE_E MemAllocMode;   /* who alloc memory for the channel */
    SINT32 s32MaxWidth;                        /* max resolution supported by the channel*/
    SINT32 s32MaxHeight;
    SINT32 s32MaxSliceNum;                     /* for H264,H265 max slice number */
    SINT32 s32MaxVpsNum;                       /* for H264,H265 max vps number */
    SINT32 s32MaxSpsNum;                       /* for H264,H265 max sps number */
    SINT32 s32MaxPpsNum;                       /* for H264,H265 max pps number */
    SINT32 s32MaxRefFrameNum;                  /* max reference frame num*/
    SINT32 s32SupportBFrame;                   /* if support B frame. 1: yes, 0: no */
    SINT32 s32SupportH264;                     /* if this channel support H.264/H.265 decoding. 2: both 1: 264 only 0: no */
    SINT32 s32ScdLowdlyEnable;                 /* if this channel support scd lowdly. 1: yes, 0: no */
    SINT32 s32ReRangeEn;                       /* when resolution change, if the framestore be re-partitioned according to the new resolution. */
    /* 1:yes. can decode smaller(but more ref) stream, but one or more frame may be discarded */
    /* 0:no.  no frame discarded, but the stream with more ref can not dec, even if the total memory is enough */
    SINT32 s32SCDBufSize;                      /* SCD buf size */
    SINT32 s32DisplayFrameNum;                 /* user defined display frame num */
    SINT32 s32SlotWidth;                       /*if Purpose==PURPOSE_FRAME_PATH_ONLY, frame store width*/
    SINT32 s32SlotHeight;                      /*if Purpose==PURPOSE_FRAME_PATH_ONLY, frame store height*/
    SINT32 s32BtlDbdrEnable;                   /*btl calculate DBDR info flag, 1:enable,0:disable*/
    SINT32 s32Btl1Dt2DEnable;                  /*btl do 1D to 2D flag, 1:enable,0:disable*/
    VDEC_SECURE_CHAN_MEM_DETAIL_S MemDetail;
    UINT32 u32DynamicFrameStoreAllocEn;
    SINT32 s32DelayTime;
    SINT32 s32ExtraFrameStoreNum;
    UINT32 u32CfgFrameNum;
    UINT32 u32MaxMemUse;
    SINT32 s32IsSecMode;                       /*add sec mode*/
    SINT32 s32ScdMmuEn;
    SINT32 s32VdhMmuEn;
    SINT32 s32ScdInputMmuEn;
} VDEC_SECURE_CHAN_OPTION_S;

typedef struct
{
    SINT32 IsOmxPath;
    SINT32 eVidStd;
    UINT8 BeDVHDRChan;
    UINT8 bDVCompatible;
#ifdef DOLBY_VISION_HDR_SUPPORT
    DV_VES_IMP_E_    VesImp;
    DV_LAYER_IMP_E_  LayerImp;
    DV_CODEC_CAP_E_  DVCapacity;
#endif
}VDEC_SECURE_ADAPTER_ATTR_S;

/* VDEC control command id, different function have different CID. */
typedef enum hiVDEC_CID_SECURE_E
{
    VDEC_CID_SEC_GET_GLOBAL_STATE,                     /* get global state */
    VDEC_CID_SEC_GET_CAPABILITY,                       /* get the capacity of the decoder */
    VDEC_CID_SEC_GET_GLOBAL_CFG,                       /* get the configured info of the decoder */
    VDEC_CID_SEC_CFG_DECODER,                          /* congfig the decoder */
    VDEC_CID_SEC_CREATE_CHAN,                          /* create channel */
    VDEC_CID_SEC_DESTROY_CHAN,                         /* destroy channel */
    VDEC_CID_SEC_GET_CHAN_CFG,                         /* get the configuration of the decode channel */
    VDEC_CID_SEC_CFG_CHAN,                             /* config the decode channel */
    VDEC_CID_SEC_GET_CHAN_STATE,                       /* get the state of the decode channel */
    VDEC_CID_SEC_START_CHAN,                           /* start channel */
    VDEC_CID_SEC_STOP_CHAN,                            /* stop channel */
    VDEC_CID_SEC_RESET_CHAN,                           /* reset channel */
    VDEC_CID_SEC_SET_STREAM_INTF,                      /* set the stream access interface for the decode channel */
    VDEC_CID_SEC_GET_STREAM_SIZE,                      /* get the stream size(in byte) held by vfmw */
    VDEC_CID_SEC_SET_FRAME_BUF_INTF,
    VDEC_CID_SEC_GET_CHAN_MEMSIZE,                     /* get the memory budget for the specified channel capacity level */
    VDEC_CID_SEC_GET_CHAN_MEMADDR,                     /* get chan mem addr */
    VDEC_CID_SEC_GET_CHAN_ID_BY_MEM,                   /* querry the channel number according the memroy physical address */
    VDEC_CID_SEC_RELEASE_STREAM,                       /* reset scd to release stream buffers */
    VDEC_CID_SEC_RESET_CHAN_WITH_OPTION,               /* reset channel with options to keep some characters of the channel */
    VDEC_CID_SEC_CFG_EXTRA,                            /* set decoder's extra_ref & extra_disp */
    VDEC_CID_SEC_SET_FRAME_INTF,                       /* bvt set get frame interface */
    VDEC_CID_SEC_GET_USRDEC_FRAME,                     /* for VFMW_USER channel, get a frame block from vfmw */
    VDEC_CID_SEC_PUT_USRDEC_FRAME,                     /* for VFMW_USER channel, push a frame(info) into vfmw */
    VDEC_CID_SEC_REGISTER_EXTRA_ACCELERATOR,           /* register external accelerator(normally refer to VEDU) */
    VDEC_CID_SEC_SET_DISCARDPICS_PARAM,                /* get discard pictures parameters*/
    VDEC_CID_SEC_FRAME_BTL,                            /* capture */
    VDEC_CID_SEC_EXTRA_WAKEUP_THREAD,                  /* bvt set wake up vfmw thread */
    VDEC_CID_SEC_SET_DBG_OPTION,                       /* set debug options */
    VDEC_CID_SEC_GET_DGB_OPTION,                       /* get debug options */
    VDEC_CID_SEC_SET_PTS_TO_SEEK,                      /* set pts to be seeked by vfmw */
    VDEC_CID_SEC_SET_TRICK_MODE,                       /* set fast forward or backword speed */
    VDEC_CID_SEC_SET_CTRL_INFO ,                       /* set pvr fast forward or backword stream info and control info*/
    VDEC_CID_SEC_SET_FRAME_RATE,
    VDEC_CID_SEC_START_LOWDLAY_CALC,
    VDEC_CID_SEC_STOP_LOWDLAY_CALC,
    VDEC_CID_SEC_ALLOC_MEM_TO_CHANNEL,
    VDEC_CID_SEC_ALLOC_MEM_TO_DECODER,
    VDEC_CID_SEC_SET_FRAME_BUFFER_NUM,
    VDEC_CID_SEC_SET_MORE_GAP_ENABLE,
    VDEC_CID_SEC_REPORT_DEMUX_RELEASE,

#ifdef VFMW_VPSS_BYPASS_EN
    VDEC_CID_SEC_SET_IMG_OUTPUT_INFO,
    VDEC_CID_SEC_REPORT_OCCUQIED_FRM,
#endif

    VDEC_CID_SEC_BUTT,
} VDEC_CID_SECURE_E;

#ifdef __cplusplus
}
#endif

#endif  // __VDEC_FIRMWARE_SECURE_H__
