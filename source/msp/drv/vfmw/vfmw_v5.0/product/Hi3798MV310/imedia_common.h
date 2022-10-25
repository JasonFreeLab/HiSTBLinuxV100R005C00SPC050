#ifndef __IMEDIA_COMMON_H__
#define __IMEDIA_COMMON_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif    /* __cpluscplus*/
#endif    /* __cpluscplus*/

#include "basetype.h"

#if defined(_MSC_VER)
#if defined(EXPORT_LIB)
#define EXPORT_API
#elif defined(EXPORT_DLL)
#define EXPORT_API extern __declspec(dllexport)
#else
#define EXPORT_API extern __declspec(dllimport)
#endif

#include <string.h>
#include <memory.h>
#include <windows.h>

//#pragma  warning(disable:4786)
#pragma  warning(disable:4996)

#ifndef inline
#define inline __inline
#endif

#define PRE64 "I64"

#elif defined(__GNUC__)
#define EXPORT_API extern

#define stricmp  strcasecmp
#define strnicmp strncasecmp

#define PRE64 "ll"
#else
#define EXPORT_API
#define PRE64
#endif

#ifndef IMEDIA_DECLARE_ALIGNED
#ifdef _MSC_VER
#define IMEDIA_DECLARE_ALIGNED(var, n) __declspec(align(n)) var
#elif defined(__GNUC__)
#define IMEDIA_DECLARE_ALIGNED(var, n) var __attribute__((aligned(n)))
#endif

#define IMEDIA_DECLARE_ALIGNED_16(var) IMEDIA_DECLARE_ALIGNED(var, 16)
#define IMEDIA_DECLARE_ALIGNED_8(var)  IMEDIA_DECLARE_ALIGNED(var, 8)
#define IMEDIA_DECLARE_ALIGNED_4(var)  IMEDIA_DECLARE_ALIGNED(var, 4)
#endif

#pragma pack(push, 1)

/****************************************************************************************
 * �����������ݽṹ
 ****************************************************************************************/
/** ��ģ�鹫�����ñ�ǣ���1���ֽڣ��ɱ�ʾ8��״̬ */
#define IMEDIA_FLAG_DISABLE_ASM         0x00000001 /**< ����Ż��رձ�ǣ�����ʱʹ�ã� .D.E.M */
#define IMEDIA_FLAG_CALC_FPS            0x00000002 /**< ͨ������ͳ��ʹ�ܱ�ǣ���������Զ�ͳ����������FPS������ʱʹ�ã� .D.E */

/** ����ģ�鳣�ñ�ǣ���2���ֽڣ��ɱ�ʾ8��״̬ */
#define IMEDIA_FLAG_DEBLOCK_FILTER      0x00000100 /**< MPEG2�Ƚ���������Deblock�˲�ʹ�ܱ�ǣ�H264��������˹��ܣ������ֶ� .D */
#define IMEDIA_FLAG_ERROR_RESILIENCE    0x00000200 /**< ��������������ʹ�ܱ�ǣ������ù��ܺ�������һ�����½��������ֶ� .D */

/** ����ģ�鳣�ñ�ǣ���3���ֽڣ��ɱ�ʾ8��״̬ */
#define IMEDIA_FLAG_CALC_PSNR           0x00010000 /**< �������͹�����PSNRͳ�Ʊ�ǣ��ù��ܶ�����Ӱ��ϴ󣬽�����������ʱ�ſɿ���������ʱʹ�ã� .E */

/** ��������ö�����Ͷ��� */
typedef enum ENUM_IMEDIA_CMD
{
    IMEDIA_GET_VERSION = 0,        /**< ��ȡ�汾��Ϣ .D.E.M */
    IMEDIA_GET_STATUS,             /**< ��ȡͨ��״̬��Ϣ .D.E */
    IMEDIA_GET_STREAM_INFO,        /**< ��ȡ������Ϣ .D.E */
    IMEDIA_GET_PARAMS,             /**< ��ȡ������Ϣ .D.E */

    /**< ��������ֻ�ڱ���ģ����Ч */
    IMEDIA_GET_DYN_PARAMS,         /**< ��ȡ��̬���� .E */
    IMEDIA_GET_SPS_PPS,            /**< ��ȡ����ͷͼ��ͷNALU���� .E */
    IMEDIA_SET_DYN_PARAMS,         /**< ���ö�̬���� .E */
    IMEDIA_SET_FUNCTION,           /**< ���ûص������������ֶΣ�һ��ûʵ�� */

    /**< ��������ֻ�ڽ���ģ����Ч */
    IMEDIA_SET_DEBUG_FLAG,         /**< ���õ�����Ϣ��� .D */

    IMEDIA_FLUSH,                  /**< ����㷨ͨ����cache��Ϣ��֡YUV���ݣ� .D */
    IMEDIA_RESET,                  /**< ��λ�㷨ͨ�� .D */

    IMEDIA_PICTURE_RELEASE,        /**< �ͷŽ���ģ�������YUV֡����Ȩ */
} ENUM_IMEDIA_CMD;

/** ���Լ���ö�����Ͷ��� */
typedef enum ENUM_IMEDIA_MSG_LEVEL
{
    IMEDIA_ERROR = 0,
    IMEDIA_WARNING,
    IMEDIA_INFO,
    IMEDIA_DEBUG,
} ENUM_IMEDIA_MSG_LEVEL;

typedef void *IMEDIA_CODEC_CTX;
typedef void *IMEDIA_IMAGE_CTX;

#define IMEDIA_VERSION_LENGTH  48    /* �汾���ַ������� */
#define IMEDIA_TIME_LENGTH     28    /* ����ʱ���ַ������� */

/*!�汾�ṹ*/
typedef struct STRU_IMEDIA_VERSION
{
    char cVersionChar[IMEDIA_VERSION_LENGTH];  /**< �汾���ַ�����ʾ */
    char cReleaseTime[IMEDIA_TIME_LENGTH];     /**< �汾����ʱ���ַ�����ʾ */
    UINT32 uiCompileVersion;                   /**< �������汾��4���ַ���� */
} STRU_IMEDIA_VERSION;

typedef void *funMalloc(unsigned int len);
typedef void  funFree(void *ptr);
typedef void  funMsgOutput(int level, const char *msg); /**< level�����ENUM_IMEDIA_MSG_LEVEL */

/*!ϵͳ��Ϣ�ṹ */
typedef struct STRU_IMEDIA_SYSINFO
{
    funMsgOutput  *pfnPrintf;       /**< ��־��Ϣ����ص���������Ϣ�ռ䳤�Ƚ���4096 Bytes */
    funMalloc     *pfnMalloc;       /**< �ڴ����ص����� */
    funFree       *pfnFree;         /**< �ڴ��ͷŻص����� */
} STRU_IMEDIA_SYSINFO;

#define MAX_BUF_NUM     64  /**< just a example ,will be set to the max buf num with codec's need */

/*!������ṹ���� */
typedef struct STRU_IMEDIA_SINGLE_BUFFER
{
    UINT8  *pucBuf;        /**< �������ַ */
    UINT32  uiSize;        /**< �����С */
} STRU_IMEDIA_SINGLE_BUFFER;

typedef struct STRU_IMEDIA_MEMBUF
{
    UINT32  uiSize;        /**< �ڴ��С */
    UINT32  uiAlignment;   /**< �ڴ�����С */
    UINT8   *pucbase;      /**< �ڴ��ַ */
} STRU_IMEDIA_MEMBUF;

typedef struct STRU_IMEDIA_RESTAB
{
    UINT32 uiNumBuf;
    STRU_IMEDIA_MEMBUF stMemTab[MAX_BUF_NUM];
} STRU_IMEDIA_RESTAB;

/*****************************************************************************************
 * ��Ƶ���ֹ������ݽṹ
 *****************************************************************************************/
#define IVIDEO_PIXEL_ALIGN_VALUE 16

/** ͼ���߶���ֵ�������Ϊ16�ı������߱���Ϊ2�ı��� */
#define IVIDEO_WIDTH_STRIDE(w)  ((((w)+15)>>4)<<4)
#define IVIDEO_HEIGHT_STRIDE(h) ((((h)+1)>>1)<<1)

/** ͼ��YUV��С���� */
#define IVIDEO_YUV_SIZE(w, h)  ((IVIDEO_WIDTH_STRIDE(w) * IVIDEO_HEIGHT_STRIDE(h) * 3) >> 1)
#define IVIDEO_Y_SIZE(w, h)     (IVIDEO_WIDTH_STRIDE(w) * IVIDEO_HEIGHT_STRIDE(h))
#define IVIDEO_UV_SIZE(w, h)    (IVIDEO_Y_SIZE(w, h) >> 2)

#define IVIDEO_MIN_WIDTH  32
#define IVIDEO_MAX_WIDTH  1920
#define IVIDEO_MAX_PITCH  131072

#define IVIDEO_MIN_HEIGHT 16
#define IVIDEO_MAX_HEIGHT 1088

/** ��Ƶ�㷨ͨ������״̬ */
typedef enum ENUM_IVIDEO_CODEC_STATUS
{
    IVIDEO_CODEC_INVALID = 0,   /**< ��Ч״̬ */
    IVIDEO_CODEC_READY,         /**< ׼��״̬��������׼��������ز�����δ���� */
    IVIDEO_CODEC_RUNNING,       /**< ����״̬ */
    IVIDEO_CODEC_STOPPED,       /**< ֹͣ״̬ */
} ENUM_IVIDEO_CODEC_STATUS;

/*!��Ƶ�㷨���� */
typedef enum ENUM_IVIDEO_CODEC_TYPE
{
    IVIDEO_CODEC_UNKNOWN = -1,
    IVIDEO_CODEC_H264 = 0,
    IVIDEO_CODEC_MPEG2,
    IVIDEO_CODEC_H263,
    IVIDEO_CODEC_MPEG4,
    IVIDEO_CODEC_WMV3,          /* VC1��simple profile��main profile */
    IVIDEO_CODEC_VC1,           /* VC1��advanced profile */
    IVIDEO_CODEC_VP6F,          /* On2 VP6 (Flash version), .flv/.f4v/.avi(strf.biCompression=VP6F)������ʹ�� */
    IVIDEO_CODEC_VP6,           /* On2 VP6 (Flip version), .avi(strf.biCompression=VP60/VP61/VP62)������ʹ�� */
    IVIDEO_CODEC_SORENSON,      /* ��������flv������*/
} ENUM_IVIDEO_CODEC_TYPE;

/*!��Ƶ�㷨profile���� */
typedef enum ENUM_IVIDEO_CODEC_PROFILE
{
    IVIDEO_PROFILE_UNKNOWN = -1,

    /**< MPEG2 */
    IVIDEO_PROFILE_MPEG2_HIGH      = 1,
    IVIDEO_PROFILE_MPEG2_SPATIALLY = 2, //reserved, not support now
    IVIDEO_PROFILE_MPEG2_SNR       = 3, //reserved, not support now
    IVIDEO_PROFILE_MPEG2_MAIN      = 4,
    IVIDEO_PROFILE_MPEG2_SIMPLE    = 5,

    /**< H264 */
    IVIDEO_PROFILE_H264_BASELINE = 66,
    IVIDEO_PROFILE_H264_MAIN     = 77,
    IVIDEO_PROFILE_H264_EXTENTED = 88,  //reserved, not support now
    IVIDEO_PROFILE_H264_HIGH     = 100,
    IVIDEO_PROFILE_H264_HIGH10   = 110, //reserved, not support now
    IVIDEO_PROFILE_H264_HIGH422  = 122, //reserved, not support now
    IVIDEO_PROFILE_H264_HIGH444  = 144, //reserved, not support now

    /**< H263 */
    IVIDEO_PROFILE_H263          = 6,
    IVIDEO_PROFILE_H263_PLUS     = 7,

    /**< MPEG4 */
    IVIDEO_PROFILE_MPEG4_SP      = 0,
    IVIDEO_PROFILE_MPEG4_MP      = 3,
    IVIDEO_PROFILE_MPEG4_ASP     = 15,


    /**< WMV/VC-1 */
    IVIDEO_PROFILE_VC1_SP        = 0,
    IVIDEO_PROFILE_VC1_MP        = 4,
    IVIDEO_PROFILE_VC1_AP        = 3,

    /**< VP6 */

    /**< Sorenson Spark */
    IVIDEO_VERSION_0             = 0,
    IVIDEO_VERSION_1             = 1,
} ENUM_IVIDEO_CODEC_PROFILE;

/*!��Ƶ�㷨level���� */
typedef enum ENUM_IVIDEO_CODEC_LEVEL
{
    IVIDEO_LEVEL_UNKNOWN = -1,
    IVIDEO_LEVEL_AUTO = IVIDEO_LEVEL_UNKNOWN,

    /**< MPEG2 */
    IVIDEO_LEVEL_MPEG2_HIGH      = 4,
    IVIDEO_LEVEL_MPEG2_HIGH_1440 = 6,
    IVIDEO_LEVEL_MPEG2_MAIN      = 8,
    IVIDEO_LEVEL_MPEG2_LOW       = 10,

    /**< H264 */
    IVIDEO_LEVEL_H264_10 = 10,
    IVIDEO_LEVEL_H264_11 = 11,
    IVIDEO_LEVEL_H264_12 = 12,
    IVIDEO_LEVEL_H264_13 = 13,
    IVIDEO_LEVEL_H264_20 = 20,
    IVIDEO_LEVEL_H264_21 = 21,
    IVIDEO_LEVEL_H264_22 = 22,
    IVIDEO_LEVEL_H264_30 = 30,
    IVIDEO_LEVEL_H264_31 = 31,
    IVIDEO_LEVEL_H264_32 = 32,
    IVIDEO_LEVEL_H264_40 = 40,
    IVIDEO_LEVEL_H264_41 = 41,
    IVIDEO_LEVEL_H264_42 = 42,
    IVIDEO_LEVEL_H264_50 = 50,
    IVIDEO_LEVEL_H264_51 = 51,

    /**< H263 */
    IVIDEO_LEVEL_H263_10 = 10,
    IVIDEO_LEVEL_H263_20 = 20,
    IVIDEO_LEVEL_H263_30 = 30,
    IVIDEO_LEVEL_H263_40 = 40,
    IVIDEO_LEVEL_H263_50 = 50,
    IVIDEO_LEVEL_H263_60 = 60,
    IVIDEO_LEVEL_H263_70 = 70,

    /**< MPEG4 */
    IVIDEO_LEVEL_MPEG4_0  = 0x00,
    IVIDEO_LEVEL_MPEG4_1  = 0x01,
    IVIDEO_LEVEL_MPEG4_2  = 0x02,
    IVIDEO_LEVEL_MPEG4_3  = 0x03,
    IVIDEO_LEVEL_MPEG4_4  = 0x04,
    IVIDEO_LEVEL_MPEG4_5  = 0x05,
    IVIDEO_LEVEL_MPEG4_3b = 0x06,  /*only for MPEG-4 ASP*/

    /**< WMV3 */
    IVIDEO_LEVEL_WMV3_LOW  = 0,
    IVIDEO_LEVEL_WMV3_MAIN = 2,
    IVIDEO_LEVEL_WMV3_HIGH = 4,

    /**< VC-1 */
    IVIDEO_LEVEL_VC1_0 = 0,
    IVIDEO_LEVEL_VC1_1 = 1,
    IVIDEO_LEVEL_VC1_2 = 2,
    IVIDEO_LEVEL_VC1_3 = 3,
    IVIDEO_LEVEL_VC1_4 = 4,

    /**< VP6 */
} ENUM_IVIDEO_CODEC_LEVEL;

/*!��Ƶ���ݸ�ʽ */
typedef enum ENUM_IVIDEO_CONTENT_TYPE
{
    IVIDEO_CONTENT_UNKNOW = -1,
    IVIDEO_PROGRESSIVE = 0,         /**< ֡��Progressive frame. */
    IVIDEO_INTERLACED,              /**< ����Interlaced frame, ��֯�洢. */
    IVIDEO_AUTO,                    /**< ���ڱ���ģ��ʹ�� */
} ENUM_IVIDEO_CONTENT_TYPE;

/*!��Ƶ֡���� */
typedef enum ENUM_IVIDEO_FRAME_TYPE
{
    IVIDEO_FRAME_UNKNOWN = -1,
    IVIDEO_FRAME_P,     /*����MPEG-4�е�S(GMC)����*/
    IVIDEO_FRAME_B,
    IVIDEO_FRAME_I,
    IVIDEO_FRAME_SI,
    IVIDEO_FRAME_SP,
    IVIDEO_FRAME_IDR,
    IVIDEO_FRAME_BREF,
} ENUM_IVIDEO_FRAME_TYPE;

/*!��Ƶ���ʱ������� */
typedef enum ENUM_IVIDEO_FRAME_RATE_CODE
{
    IVIDEO_FRAME_RATE_UNKNOWN = 0,
    IVIDEO_FRAME_RATE_23_976,    /**< 24 000/1001 */
    IVIDEO_FRAME_RATE_24,
    IVIDEO_FRAME_RATE_25,
    IVIDEO_FRAME_RATE_29_97,     /**< 30 000/1001 */
    IVIDEO_FRAME_RATE_30,
    IVIDEO_FRAME_RATE_50,
    IVIDEO_FRAME_RATE_59_94,     /**< 60 000/1001 */
    IVIDEO_FRAME_RATE_60,
} ENUM_IVIDEO_FRAME_RATE_CODE;

/*!��Ƶɫ�ȸ�ʽ���� */
typedef enum ENUM_IVIDEO_COLOR_SPACE_TYPE
{
    IVIDEO_CSP_UNKNOWN = -1,

    /**< YUV 420/411 - Planar Format */
    IVIDEO_CSP_IYUV = 0,
    IVIDEO_CSP_YV12,

    /**< YUV 422 - Packed Format */
    IVIDEO_CSP_UYVY, /**< Most popular of the various YUV 4:2:2 formats */
    IVIDEO_CSP_YUY2,
    IVIDEO_CSP_YVYU,

    /**< YUV 444 - Packed Format */
    IVIDEO_CSP_YUV444,

    /**< RGB Format */
    IVIDEO_CSP_RGB32,
    IVIDEO_CSP_RGB24,
    IVIDEO_CSP_RGB555,
    IVIDEO_CSP_RGB565,

    /**< Y only */
    IVIDEO_CSP_MONOCHROME,

    /**< None */
    IVIDEO_CSP_NONE,

    /**< Duplication Name */
    IVIDEO_CSP_YUV420 = IVIDEO_CSP_IYUV,
    IVIDEO_CSP_YUV422 = IVIDEO_CSP_UYVY,
    IVIDEO_CSP_YUYV   = IVIDEO_CSP_YUY2,
} ENUM_IVIDEO_COLOR_SPACE_TYPE;

/*!��Ƶɫ�ȸ�ʽ���� */
typedef enum ENUM_IVIDEO_YUV_BUF_ORDER
{
    IVIDEO_Y = 0,
    IVIDEO_U,
    IVIDEO_V,
} ENUM_IVIDEO_YUV_BUF_ORDER;

/*!ͼ�����ؿ�߱Ƚṹ��Ϣ */
typedef struct STRU_IVIDEO_ASPECT_RATIO
{
    UINT16  usSarWidth;         /**< ͼ�����ص������Range[0-65535] */
    UINT16  usSarHeight;        /**< ͼ�����ص�����ߣ�Range[0-65535] */
} STRU_IVIDEO_ASPECT_RATIO;

/*!��Ƶͼ��ṹ��Ϣ */
typedef struct STRU_IVIDEO_PICTURE
{
    UINT8  *apucBuf[4];         /**< ָ��ǰͼ�����ݵ�ָ��(0-Y 1-U 2-V 3-private)���м�ģ�飺Yƽ���ַ��16�ֽڶ��룬U��Vƽ���ַ��8�ֽڶ��룻����ģ�������� */
    UINT16  usWidth;            /**< ͼ���ȵ�ʵ��ֵ����λ���أ�Range[32-1920] */
    UINT16  usHeight;           /**< ͼ��߶ȵ�ʵ��ֵ����λ���أ�Range[16-1088] */
    UINT16  usWidthPitch;       /**< ͼ���ȵ��ڴ��ȣ���λ���أ�Range[>=usWidth] (�м�ģ����resize�㷨��Ϊ16�ı���������ģ����Ϊ2�ı��������֧�ֵ�3840)  */
    ENUM_IVIDEO_CONTENT_TYPE  eContentType;         /**< ͼ������ͣ�IVIDEO_PROGRESSIVE or IVIDEO_INTERLACED) */
    STRU_IVIDEO_ASPECT_RATIO  stAspectRatio;        /**< ͼ�����ؿ�߱� */
    //ENUM_IVIDEO_COLOR_SPACE_TYPE eColorSpaceType; /**< reserved, ���ͼ��ĸ�ʽ��Ĭ��ΪYUV420��ʽ */
} STRU_IVIDEO_PICTURE;

/*!��Ƶ������Ϣ */
typedef struct STRU_IVIDEO_STREAM_INFO
{
    UINT16 usWidth;                                /**< ͼ���ȣ���λ���أ�Range[32-1920] */
    UINT16 usHeight;                               /**< ͼ��߶ȣ���λ���أ�Range[16-1088] */

    ENUM_IVIDEO_CODEC_TYPE       eCodecType;
    ENUM_IVIDEO_CODEC_PROFILE    eProfile;         /**< profile idc */
    ENUM_IVIDEO_CODEC_LEVEL      eLevel;           /**< level idc */
    ENUM_IVIDEO_CONTENT_TYPE     eContentType;     /**< ͼ������ (IVIDEO_PROGRESSIVE or IVIDEO_INTERLACED) */
    ENUM_IVIDEO_COLOR_SPACE_TYPE eColorSpaceType;  /**< ͼ���ʽ (YUV420, YUV422, etc) */

    UINT32 uiRefFrameNum;                          /**< �ο�֡������������ Range[0-16]�������� Range[1-16] */
    UINT32 uiFrameRate;                            /**< ����֡�� x 1000��Range[5000-60000]������������Ч */
    UINT32 uiBitrate;                              /**< ���������ʣ���λkbps, Range[10-30000]������������Ч */
    UINT32 uiVbvBuf;                               /**< VBV���棬��λms��Range[500-10000]������������Ч */

    STRU_IVIDEO_ASPECT_RATIO stAspectRatio;        /**< ͼ�����ؿ�߱� */
} STRU_IVIDEO_STREAM_INFO;

/*****************************************************************************************
 * H264���ݽṹ
 *****************************************************************************************/
/*!NALU������ */
typedef enum ENUM_H264_NALU_TYPE
{
    H264_NAL_UNKNOWN     = 0,
    H264_NAL_SLICE       = 1,
    H264_NAL_SLICE_DPA   = 2,
    H264_NAL_SLICE_DPB   = 3,
    H264_NAL_SLICE_DPC   = 4,
    H264_NAL_SLICE_IDR   = 5,          /* ref_idc != 0 */
    H264_NAL_SEI         = 6,          /* ref_idc == 0 */
    H264_NAL_SPS         = 7,
    H264_NAL_PPS         = 8,
    H264_NAL_AUD         = 9,
    /* ref_idc == 0 for 6,9,10,11,12 */
} ENUM_H264_NALU_TYPE;

/*!NALU�����ȼ� */
typedef enum ENUM_H264_NALU_PRIORITY
{
    H264_NAL_PRIORITY_DISPOSABLE = 0,  /* SEI,B-NoRef */
    H264_NAL_PRIORITY_LOW        = 1,
    H264_NAL_PRIORITY_HIGH       = 2,  /* I, P, B-ref */
    H264_NAL_PRIORITY_HIGHEST    = 3   /* SPS, PPS, IDR */
} ENUM_H264_NALU_PRIORITY;

/*!H264 NALU�����ṹ */
typedef struct STRU_H264_NALU_STREAM
{
    UINT8  *pucData;                   /**< ��ַ */
    UINT32  uiSize;                    /**< ��С */
    ENUM_H264_NALU_TYPE     eType;     /**< ���� */
    ENUM_H264_NALU_PRIORITY ePriority; /**< ���ȼ� */
} STRU_H264_NALU_STREAM;

#define MAX_NALU_COUNT_OF_FRAME 200

/*!H264 ֡�������ݽṹ */
typedef struct STRU_H264_FRAME_STREAM
{
    UINT8  *pucStream;                 /**< ֡���ݻ��棬���һ��NALU��ַ��ͬ */

    STRU_H264_NALU_STREAM stNalu[MAX_NALU_COUNT_OF_FRAME]; /**< NALU���� */

    BOOL16  bSkipFlag;                 /**< ��ǰ֡�Ƿ񱻶��� */
    UINT16  usNaluCount;               /**< NALU���� */
    UINT32  uiDataSize;                /**< ֡���ݴ�С����ֱ�Ӵӵ�һ��NALU��ַ��ʼȡ�ô�С������ */
    UINT32  uiFrameID;                 /**< ֡����˳���ţ��ɻ���ΪDTS��ÿ��segment��0��ʼ���� */
    UINT32  uiDisplayID;               /**< ֡��ʾ˳���ţ��ɻ���ΪPTS��ÿ��segment��0��ʼ���� */
    ENUM_IVIDEO_FRAME_TYPE eFrameType; /**< ��ǰ֡�������� */
} STRU_H264_FRAME_STREAM;

/*!������λ��״̬ */
typedef enum ENUM_BITSTREAM_STATUS
{
    BITSTREAM_UNKNOWN = 0,
    BITSTREAM_SEGMENT_BEGIN,           /**< ��ǰ��Ƭ�ĵ�һ������ */
    BITSTREAM_SEGMENT_END,             /**< ��ǰ��Ƭ�����һ������ */
    BITSTREAM_OTHER,
} ENUM_BITSTREAM_STATUS;

#pragma pack(pop)

#ifdef __cplusplus
#if __cplusplus
}
#endif    /* __cpluscplus*/
#endif    /* __cpluscplus*/

#endif /**< __IMEDIA_COMMON_H__ */

/************************************************************************
* $Log$
************************************************************************/
