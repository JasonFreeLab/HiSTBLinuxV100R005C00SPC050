#ifndef _VC1_HEADER_
#define _VC1_HEADER_

#include    "basedef.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vdm_hal.h"
#include    "syn_cmn.h"
#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
* 宏定义                                       *
*----------------------------------------------*/
#define VC1_VFMW_FALSE 0
#define VC1_VFMW_TRUE 1
#define VC1_NOT_DEC   2

#define VC1_OUTPUT_IN_DEC 1
#define VC1_OUTPUT_IN_DSP 0

#define VC1_REG_SIZE        128  //寄存器信息长度，单位WORDs
#define VC1_PICDNMSG_SIZE   96   //Pic下行消息长度，单位WORD
#define VC1_SLCDNMSG_SIZE   64   //Slc下行消息长度，单位WORD




#define VC1_SPSOK 1
#define VC1_ENTOK 2
#define VC1_PPSOK 4
#define VC1_MALCOK 8
#define VC1_ALLSLCOK 16
#define VC1_EOSOK 32

#define VC1_PRF_BLK_HSIZE 8
#define VC1_PRF_BLK_VSIZE 8
#define VC1_PRF_MAX_SAMPLE_VALUE (255)

#define VC1_PRF_MAX_FETCH_HSIZE    (8 + 7)
#define VC1_PRF_MAX_FETCH_VSIZE    (8 + 7)
#define VC1_PRF_MAX_FETCH_SIZE     (VC1_PRF_MAX_FETCH_HSIZE * VC1_PRF_MAX_FETCH_VSIZE)

#define VC1_MAX_PIC_WIDTH 128 // unit: MB
#define VC1_MAX_PIC_HEIGHT 128 // unit: MB
#define VC1_MAX_PIC_MB (VC1_MAX_PIC_WIDTH * VC1_MAX_PIC_HEIGHT) // 16129, unit: MB

#define VC1_MB_PITCH 16   /* 亮度块的边长 */
#define VC1_SUBMB_PITCH 8    /* 色度块的边长 */

#define VC1_ALL_BLK_4x4 15

#define VC1VFMW_MAX_FRAME_BUF_NUM 5
#define VC1VFMW_MAX_MBNUM 8192

#define VC1VFMW_MSG_SLOT_STAR_ADDR 0
#define VC1VFMW_DNMSG_NUM 2
#define VC1VFMW_UPMSG_NUM 1
#define VC1VFMW_RPMSG_NUM 1
#define VC1VFMW_MSG_BUF_SIZE (((((VC1VFMW_DNMSG_NUM + VC1VFMW_UPMSG_NUM + VC1VFMW_RPMSG_NUM) * 4) + 1023) >> 10) << 10)        /* 32 行深度:32*1024  */

#define VC1VFMW_NEIGHBOR_BUF_SIZE       ((((VC1VFMW_MAX_PIC_WIDTH * 4) + 1023) >> 10) << 10)  /* 32 行深度:32*1024  */

//#define VC1VDH_REG_PHY_ADDR 0x10100000       // VDH 寄存器映射到ARM空间的地址

#define  MAX_PACKET_NUM  300//512
#define  VC1_ERROR  (-1)

#define VC1DEC_ASSERT_RET(cond, else_print)                            \
do {                                                                \
    if (!(cond))                                                    \
    {                                                               \
        dprint(PRN_FATAL,"vc1.c,L%d: %s\n", __LINE__, else_print ); \
        return VC1_ERROR;                                             \
    }                                                               \
}while(0)

typedef enum
{
    VC1_SCEOS = 0xa,
    VC1_SCSLC,
    VC1_SCFLD,
    VC1_SCFRM,
    VC1_SCENT,
    VC1_SCSEQ,
    VC1_SCSLCUD = 0x1b,
    VC1_SCFLDUD,
    VC1_SCFRMUD,
    VC1_SCENTUD,
    VC1_SCSEQUD,
    HISI_VC1AP_STREAM_END_CODE = 0xfe,
} VC1_STARTCODE_EN;

typedef enum
{
    WMV1 = 0,
    MP43,
    WMV2,
    MP42,
    MP4S,
    WMV3,
    WMVA,
    WMVUNSPT,
    WMVC1
} VC1CODEC_VERSION_EN;

typedef enum
{
    VC1_VFMW_SIMPLE = 0,
    VC1_VFMW_MAIN,
    VC1_VFMW_ADVANCED
} VC1PROFILE_EN;

typedef enum
{
    VC1_EXPLICITFRAMEQ0 = 0,
    VC1_EXPLICITFRAMEQ1,
    VC1_3QPDZ0,
    VC1_3QPDZ1
} VC1QUANTTYPE_EN;

typedef enum
{
    VC1_VFMW_IPIC = 0,
    VC1_VFMW_PPIC,
    VC1_VFMW_BPIC,
    VC1_VFMW_SPRITE, 
    VC1_VFMW_BIPIC,
    VC1_VFMW_SKPIC
} VC1_PICTYPE_EN;

typedef enum
{
    VC1_VFMW_PROGRESSIVE = 0,
    VC1_VFMW_FRAMEINTER = 2,
    VC1_VFMW_FIELDINTER
} VC1_PICSTRUCTURE_EN;


typedef enum
{
    VC1_II = 0,
    VC1_IP,
    VC1_PI,
    VC1_PP,
    VC1_BB,
    VC1_BBI,
    VC1_BIB,
    VC1_BIBI
} VC1_FLDPICTYPE_EN;

typedef enum
{
    VC1_MIXMV = 0,
    VC1_1MV,
    VC1_1MVHP,
    VC1_1MVHPB,
    VC1_INTCMP
} VC1_MVMODE_EN;

typedef enum
{
    VC1_ALLFOUREDGE = 0,
    VC1_DOUBLEEDGE,
    VC1_SINGLEEDGE,
    VC1_ALLMB
} VC1_MBDQPROFILE_EN;

typedef enum
{
    VC1_RAW = 0,
    VC1_NORM2,
    VC1_DIFF2,
    VC1_NORM6,
    VC1_DIFF6,
    VC1_ROWSKIP,
    VC1_COLSKIP,
    VC1_DECIDED
} VC1_BITPLANEMODE_EN;

typedef enum
{
    VC1_BOTHFLDINT = 0,
    VC1_TOPHFLDINT,
    VC1_BOTFLDINT
} VC1_INTCOMPFIELD_EN;
typedef enum
{
    VC1_VFMW_TOPFLD = 0,
    VC1_VFMW_BOTFLD
} VC1_FLD_TB;


/**
* Description:
* Per macroblock quantizer step size enumeration
*/
typedef enum
{
    VC1_QUANTMODEDEFAULT,       /** All macroblocks use PQUANT */
    VC1_QUANTMODEALLEDGES,        /** Edge macroblocks use ALTPQUANT */
    VC1_QUANTMODELEFTTOP,        /** Left/Top     macroblocks use ALTPQUANT */
    VC1_QUANTMODETOPRIGHT,        /** Top/Right    macroblocks use ALTPQUANT */
    VC1_QUANTMODERIGHTBOTTOM,    /** Right/Bottom macroblocks use ALTPQUANT */
    VC1_QUANTMODEBOTTOMLEFT,    /** Bottom/Left  macroblocks use ALTPQUANT */
    VC1_QUANTMODELEFT,            /** Left         macroblocks use ALTPQUANT */
    VC1_QUANTMODETOP,            /** Top          macroblocks use ALTPQUANT */
    VC1_QUANTMODERIGHT,            /** Right        macroblocks use ALTPQUANT */
    VC1_QUANTMODEBOTTOM,        /** Bottom       macroblocks use ALTPQUANT */
    VC1_QUANTMODEMBDUAL,        /** PQUANT/ALTPQUANT selected on macroblock basis */
    VC1_QUANTMODEMBANY            /** Any QUANT selected on a macroblock basis */
} VC1_QUANTMODE;



typedef struct
{
    SINT32 Code;
    SINT32 Len;
} VC1_VFMW_VLC_S;

typedef struct
{
    SINT8 *pElement;
    SINT32 Invert;
    SINT32 Imode;
} VC1_BITPLANE_S;

typedef struct
{
    UINT8 PROFILE;
    UINT8 FRMRTQ;
    UINT8 BITRTQ;
    UINT8 LOOPFILTER;
    UINT8 MULTIRES;
    UINT8 B16BITTRANSFORM; //corresponding to m_b16bitXform, an unknow flag from refcode but protocol document
    UINT8 FASTUVMC; //it's m_bUVHpelBilinear
    UINT8 EXTENDED_MV;
    UINT8 DQUANT;
    UINT8 VSTRANSFORM; //it's m_bXformSwitch
    UINT8 OVERLAP;
    UINT8 SYNCMARKER;
    UINT8 RANGERED;
    UINT8 MAXBFRAMES;
    UINT8 QUANTIZER;
    UINT8 FINTERPFLAG;
} VC1_SMPSEQSYNTAX_S;

typedef struct
{
    UINT8  PROFILE;
    UINT8  LEVEL;
    UINT8  CHROMFORMAT;
    UINT8  FRMRTQ_POSTPROC;
    UINT8  BITRTQ_POSTPROC;
    UINT8  POSTPROCFLAG;
    UINT8  PULLDOWN;
    UINT8  INTERLACE;
    UINT8  TFCNTRFLAG;
    UINT8  FINTERPFLAG;
    UINT8  DISPLAY_EXT;
    UINT8  ASPECT_RATIO_FLAG;
    UINT8  ASPECT_RATIO;
    UINT8  ASPECT_HORIZ_SIZE;
    UINT8  ASPECT_VERT_SIZE;
    UINT8  FRAMERATE_FLAG;
    UINT8  FRAMERATEIND;
    UINT8  FRAMERATENR;
    UINT8  FRAMERATEDR;
    UINT8  COLOR_FORMAT_FLAG;
    UINT8  COLOR_PRIM;
    UINT8  TRANSFER_CHAR;
    UINT8  MATRIX_COEF;
    UINT8  HRD_PARAM_FLAG;
    UINT8  HRD_NUM_LEAKY_BUCKETS;
    UINT8  BIT_RATE_EXPONENT;
    UINT8  BUFFER_SIZE_EXPONENT;
    UINT16 HRD_RATE[32];
    UINT16 HRD_BUFFER[32];
    UINT16 MAX_CODED_WIDTH;
    UINT16 MAX_CODED_HEIGHT;
    UINT16 DISP_HORIZ_SIZE;
    UINT16 DISP_VERT_SIZE;
    UINT16 FRAMERATEXP;

    //derived
    SINT32 HdrLen;
} VC1_ADVSEQSYNTAX_S;

typedef struct
{
    UINT8  BROKEN_LINK;
    UINT8  CLOSED_ENTRY;
    UINT8  PANSCAN_FLAG;
    UINT8  REFDIST_FLAG;
    UINT8  LOOPFILTER;
    UINT8  FASTUVMC;
    UINT8  EXTENDED_MV;
    UINT8  DQUANT;
    UINT8  VSTRANSFORM;
    UINT8  OVERLAP;
    UINT8  QUANTIZER;
    UINT8  CODED_SIZE_FLAG;
    UINT8  EXTENDED_DMV;
    UINT8  RANGE_MAPY_FLAG;
    UINT8  RANGE_MAPY;
    UINT8  RANGE_MAPUV_FLAG;
    UINT8  RANGE_MAPUV;
    UINT8  HRD_FULLNESS[32];
    UINT16 CODED_WIDTH;
    UINT16 CODED_HEIGHT;

    //derived
    SINT32 HdrLen;
} VC1_ADVENTSYNTAX_S;

typedef struct
{
    UINT8  DQUANTFRM;
    UINT8  DQPROFILE;
    UINT8  DQBILEVEL;
    UINT8  UseAltQp;
    UINT8  PQDIFF;
    UINT8  ABSPQ;
    UINT8  DQSBEDGE;
    UINT8  DQDBEDGE;

    //derived
    UINT8  ALTPQUANT;
    VC1_QUANTMODE QuantMode; // 哪条边用ALTPQUANT, fk ms
} VC1_VOPDQUANT_S;

typedef struct
{
    UINT8  INTERPFRM;
    UINT8  FRMCNT;
    UINT8  RANGEREDFRM;
    UINT8  PTYPE;
    UINT8  BFRACTION;
    UINT8  BF;
    UINT8  PQINDEX;
    UINT8  HALFQP;
    UINT8  PQUANTIZER;
    UINT8  MVRANGE;
    UINT8  RESPIC;
    UINT8  MVMODE;
    UINT8  MVMODE2;
    UINT8  LUMSCALE;
    UINT8  LUMSHIFT;
    UINT8  MVTAB;
    UINT8  CBPTAB;
    UINT8  TTMBF;
    UINT8  TTFRM;
    UINT8  TRANSACFRM;
    UINT8  TRANSACFRM2;
    UINT8  TRANSDCTAB;
    UINT8  RNDCTRL;
    VC1_VOPDQUANT_S VOPDQUANT;
    VC1_BITPLANE_S  MVTYPEMB;
    VC1_BITPLANE_S  DIRECTMB;
    VC1_BITPLANE_S  SKIPMB;

    //derived
    SINT32 HdrLen;
    SINT32 MVTYPEMBMode;
    SINT32 DIRECTMBMode;
    SINT32 SKIPMBMode;
    SINT32 PQUANT;
    SINT32 ScaleFactor;
} VC1_SMPPICSYNTAX_S;

typedef struct
{
    UINT8  RNDCTRL;
    UINT8  PTYPE;
    UINT8  BFRACTION;
    UINT8  HALFQP;
    UINT8  TFF;
    UINT8  RFF;
    UINT8  RPTFRM;
    UINT8  PS_PRESENT;
    UINT8  UVSAMP;
    UINT8  INTERPFRM;
    UINT8  PQINDEX;
    UINT8  PQUANTIZER;
    UINT8  POSTPROC;
    UINT8  MVRANGE;
    UINT8  MVMODE;
    UINT8  MVMODE2;
    UINT8  LUMSCALE;
    UINT8  LUMSHIFT;

    UINT8  MVTAB;
    UINT8  CBPTAB;
    UINT8  TTMBF;
    UINT8  TTFRM;

    UINT8  TRANSACFRM;
    UINT8  TRANSACFRM2;
    UINT8  TRANSDCTAB;
    UINT8  DMVRANGE;
    UINT8  QMVSWITCH;
    UINT8  MBMODETAB;
    UINT8  BMVBPTAB;
    UINT8  QMVBPTAB;
    UINT8  CONDOVER;
    UINT8  REFDIST;
    UINT8  NUMREF;
    UINT8  REFFIELD;
    UINT8  MVTYPEMBMode;
    UINT8  DIRECTMBMode;
    UINT8  SKIPMBMode;
    UINT8  ACPREDMode;
    UINT8  OVERFLAGSMode;
    UINT8  FIELDTXMode;
    UINT8  FORWARDMBMode;
    UINT8  CurParity; //0 is top, 1 is bot

    SINT32 FCM;
    SINT32 TFCNTR;
    SINT32 PS_HOFFSET[4];
    SINT32 PS_VOFFSET[4];
    SINT32 PS_WIDTH[4];
    SINT32 PS_HEIGHT[4];
    SINT32 PQUANT;
    //for interlaced frame
    SINT32         INTCOMP;

    //for interlaced field
    SINT32         FPTYPE;
    SINT32         INTCOMPFIELD;
    SINT32         LUMSCALE2;
    SINT32         LUMSHIFT2;

    //derived
    SINT32 HdrLen;

    SINT32 NumOfPanScanWindows;
    SINT32 ScaleFactor;
    SINT32 FldPicType[2];

    //for intra pic
#ifndef VFMW_BPD_H_SUPPORT
    VC1_BITPLANE_S ACPRED;
    VC1_BITPLANE_S OVERFLAGS;
    VC1_BITPLANE_S MVTYPEMB;
    VC1_BITPLANE_S DIRECTMB;
    VC1_BITPLANE_S SKIPMB;
    VC1_BITPLANE_S FIELDTX;
    VC1_BITPLANE_S FORWARDMB;
#endif
    //for inter pic
    VC1_VOPDQUANT_S VOPDQUANT;

} VC1_ADVPICSYNTAX_S;

typedef struct
{
    SINT8  PIC_HEADER_FLAG;
    UADDR  SLICE_ADDR;

    //derived
    SINT32 HdrLen;
} VC1_ADVSLCSYNTAX_S;

typedef struct
{
    SINT8              IsAdvProfile;
    UINT8              RcvVersion;
    UINT8              CodecVersion;
    SINT32             NumOfPic;
    SINT32             FrmWidth;
    SINT32             FrmHeight;
    VC1_SMPSEQSYNTAX_S SMPSeqSyntax;
} VC1_PREPARSEINFO_S;

typedef struct
{
    UINT8  is_to_ref;
    UINT8  is_to_display;
    UINT8  RANGEREDFRM;
    UINT8  IntensityConvertTab[2][2][256];  // [TopFld/BotFld][Y/C][256]
    UINT8  PicStruct;
    UINT8  PicCodingType;
    UINT8  IsHalfPel[2];
    SINT8  TopFldFirst;
    UINT32 pic_distance;
    IMAGE  img;
    //FSP_LOGIC_FS_S *FS;
} VC1_VFMWFRAMEOBJ_S;

typedef struct
{
    SINT8  FldFlag[2];
    SINT32 ListLen;
    SINT32 ImgObj[2];
} VC1_REFLIST_OBJS;

typedef struct
{
    VC1_SMPSEQSYNTAX_S SMPSeqSyntax;
    VC1_ADVSEQSYNTAX_S AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S AdvEntSyntax;
    VC1_SMPPICSYNTAX_S SMPPicSyntax;
    VC1_ADVPICSYNTAX_S AdvPicSyntax;
    VC1_ADVSLCSYNTAX_S AdvSlcSyntax[256]; //1080p just need these. max is 512 for VC1 original protocol  //20130730  维数128
} VC1_VFMWSYNTAX_S;

typedef struct
{
    UINT8   *BsVirAddr[2];
    SINT8    IsLastSeg[2];
    UADDR    BsPhyAddr[2];
    SINT32   BsLength[2];
    SINT32   StreamID[2];

} VC1_STREAM_PACKET;

typedef struct
{
#ifndef VFMW_BPD_H_SUPPORT
    SINT8   ACPRED[VC1VFMW_MAX_PIC_MB];
    SINT8   OVERFLAGS[VC1VFMW_MAX_PIC_MB];
    SINT8   MVTYPEMB[VC1VFMW_MAX_PIC_MB];
    SINT8   DIRECTMB[VC1VFMW_MAX_PIC_MB];
    SINT8   SKIPMB[VC1VFMW_MAX_PIC_MB];
    SINT8   FIELDTX[VC1VFMW_MAX_PIC_MB];
    SINT8   FORWARDMB[VC1VFMW_MAX_PIC_MB];
#endif
    UINT8   CodecStatus;
    SINT8   RefId;
    UINT8   PicCodingType;
    SINT8   Last_Struct_IPB;  //no matter which type of last pic is, record it
    SINT8   PicStructure;
    SINT8   Last_Struct;// Last pic is I or P, record it
    SINT8   IsWaitToDec;
    UINT8   IsStreamEndFlag;
    UINT8   Is2ndFld;
    UINT8   LastIs2ndFld;
    SINT8   LastPicRNDCTRL;
    UINT8   CodecVersion;
    UINT8   PostCresent;
    UINT8   IntensityConvertTab[3][2][2][256];
    UINT8  *BwdColmbVirAddr;
    UINT8  *CurrColmbVirAddr;
    VC1_PREPARSEINFO_S  PreParseInfo;
    BS                 *pBs;
    BS                  Bs;
    VC1_VFMWSYNTAX_S    SynNew;
    VC1_VFMWSYNTAX_S    SynNewPicInSlcHeader;
    VC1_SMPSEQSYNTAX_S  SMPSeqSyntax;
    VC1_ADVSEQSYNTAX_S  AdvSeqSyntax;
    VC1_ADVENTSYNTAX_S  AdvEntSyntax;
    VC1_SMPPICSYNTAX_S  SMPPicSyntax;
    VC1_ADVPICSYNTAX_S  AdvPicSyntax;
    VC1_ADVSLCSYNTAX_S  AdvSlcSyntax[256]; //1080p just need these. max is 512 for VC1 original protocol    //20130730  维数128
    VC1_VFMWFRAMEOBJ_S  FrameObj[VC1VFMW_MAX_FRAME_BUF_NUM];
    VC1_VFMWFRAMEOBJ_S  ZeroFrm;
    VC1_VFMWFRAMEOBJ_S *pCurFrm;
    VC1_VFMWFRAMEOBJ_S *pRef[3];    /*其中0为最近解出的参考图，1为较早解出的参考图*/
    SINT32              MbWidth;
    SINT32              MbHeight;
    SINT32              MbWidthLast;
    SINT32              MbHeightLast;
    UINT32              DispPicWidth;         //Frame width in pix
    UINT32              DispPicHeight;        //Frame height in in pix
    SINT32              DDR_Stride;
    SINT32              NumOfAllocatedFrameObj;
    VC1_REFLIST_OBJS    RefList0;
    VC1_REFLIST_OBJS    RefList1;
    UINT32              RefNum;
    SINT32              FwdFsID;
    SINT32              BwdFsID;
    SINT32              CurFsID;
    SINT32              ToQueFsID;
    //stream
    UINT32              SlcNum;
    VC1_SLCSTREAM_S     SlcStr[VC1VFMW_MAX_SLC_NUM];
    SINT32              PicCnt;

    VC1_STREAM_PACKET   stCurPacket;
    SINT32              FRFD, BRFD; //10.4.6.2 & 10.4.6.3 for B mv predict
    UINT32              PPicFound;
    UINT32              BPicCount;

    //add for multi res
    SINT32              CurPicWidth;
    SINT32              CurPicHeight;
    SINT32              CurPicMbWidth;
    SINT32              CurPicMbHeight;
    SINT32              CurPicMbNum;

    UADDR               BwdColmbAddr;
    UADDR               CurrColmbAddr;

    SINT32              skpic_flag;
    UADDR               MVTYPEMB_ADDR;
    UADDR               SKIPMB_ADDR;
    UADDR               DIRECTMB_ADDR;
    UADDR               ACPRED_ADDR;
    UADDR               OVERFLAGS_ADDR;
    UADDR               FIELDTX_ADDR;
    UADDR               FORWARDMB_ADDR;

    UINT32              UsedDecMode;      //当前正在使用的解码模式(IPB, IP, I)

    UINT8               u8LastCodecStatus;
    UINT8               linear_en;
    UINT32              CompressEn;
} VC1_VFMWCODECINF_S;

typedef struct
{
    UINT8   *p_stream;
    UINT8    last_pack_in_nal;
    UADDR    strm_phy_addr;
    SINT32   stream_len;
    UINT64   pts;
} STREAM_PACKET;


typedef struct
{
    SINT32 tmp;
} VC1_DECPARA_S;


typedef union
{
    struct
    {
        USIGN forwardmb : 1;
        USIGN directmb  : 1;
        USIGN mbtypemb  : 1;
        USIGN fieldtx   : 1;
        USIGN skipmb    : 1;
        USIGN acpred    : 1;
        USIGN overflags : 1;
        USIGN reserved  : 1;
    } bits;
    UINT8 u8;
} VC1BITPLANE_MB;

typedef struct
{
    UINT8  MVMODE;
    UINT8  MVMODE2;
    UINT8  FwBwFlg;
    UINT8  YcFlg; //0: luma;  1: chroma
    SINT8  XFrac;
    SINT8  YFrac;

    SINT32 Block8x8PartIdx;
    SINT32 MvX;
    SINT32 MvY;
    SINT32 InStride;
    SINT32 FldPrd;

    SINT32 SubWidth;
    SINT32 SubHeight;
    SINT32 iRndCtrl;

    SINT32 PrfBuf[VC1_PRF_MAX_FETCH_HSIZE *VC1_PRF_MAX_FETCH_VSIZE];
    SINT32 Prc2PrfBuf[8 * 26];
    SINT32 Prf2RcnBuf[2][VC1_PRF_BLK_HSIZE *VC1_PRF_BLK_VSIZE];
} VC1_PRFINFO_S;

typedef enum
{
    VC1_FALSE = 0,
    VC1_TRUE
} VC1_RETTYPE_E;


typedef struct
{
    SYNTAX_EXTRA_DATA_S  *pstExtraData;
    VC1_DEC_PARAM_S      *pVc1DecParam;
    VC1_DEC_PARAM_S       Vc1DecParam;
    DEC_STREAM_PACKET_S   LastPacket;
    VC1_VFMWCODECINF_S    CodecInfo;
    BS                    Bs;
    IMAGE_VO_QUEUE        ImageQue;
    SINT32                ChanID;
} VC1_CTX_S;


SINT32        VC1DEC_Decode(VC1_CTX_S *pVC1_CTX_S, DEC_STREAM_PACKET_S *p_Packet);
SINT32        Vc1SMPSeqHdr(UINT8 *pBitBuf, SINT32 ByteLen, VC1_PREPARSEINFO_S *pVc1Info);
UINT32        VC1DEC_VDMPostProc(VC1_CTX_S *pCtx, SINT32 ErrRatio);
SINT32        VC1DEC_GetRemainImg(VC1_CTX_S *pCtx);
SINT32        VC1DEC_GetImageBuffer(VC1_CTX_S *pCtx);
SINT32        VC1DEC_Init(VC1_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData);
SINT32        VC1DEC_RecycleImage(VC1_CTX_S *pCtx, UINT32 img_id);
SINT32        VC1_GetPacketState(VC1_CTX_S *pCtx);
VOID          VC1_ClearCurPic(VC1_VFMWCODECINF_S *pCodeInfo, SINT32 ChanID);


#ifdef __cplusplus
}
#endif

#endif //_VC1_HEADER_
