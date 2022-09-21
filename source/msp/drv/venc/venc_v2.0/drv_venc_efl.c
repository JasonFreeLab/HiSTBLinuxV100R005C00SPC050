#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"
#include "drv_venc.h"

#include "hi_drv_log.h"
#include "hi_osal.h"

#include "hi_drv_reg.h"
#include "hi_reg_common.h"

#include "hi_drv_stat.h"
#include "hi_drv_sys.h"

#ifdef VENC_SUPPORT_JPGE
#include "drv_jpge_ext.h"
#endif

#ifdef VENC_DPT_ONLY
#include "hi_math.h"
#endif

#include "venc_hal_ext.h"
#include "public.h"
#include "sysconfig.h"
#include "product.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

VENC_HAL_FUN_PTR_S g_venc_hal_fun_ptr;
extern Venc_Osal_Func_Ptr venc_Osal_Func_Ptr_S;

static HI_U32 g_idr_pic_id = 0;

//#define __VENC_FREQ_DYNAMIC__


extern HI_VOID VENC_DRV_BoardInit(HI_VOID);
extern HI_VOID VENC_DRV_BoardDeinit(HI_VOID);

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define Smooth_printk printk
#else
#define Smooth_printk(format, arg...)
#endif

#ifdef HI_SMMU_SUPPORT
HI_U32 VeduEfl_SmmuToPhyAddr(HI_U32 PageTabBaseAddr ,HI_U32 SmmuAddr  );
#endif

enum
{
    VENC_YUV_420    = 0,
    VENC_YUV_422    = 1,
    VENC_YUV_444    = 2,
    VENC_YUV_NONE   = 3
};

enum
{
    VENC_V_U        = 0,
    VENC_U_V        = 1
};


enum
{
    VENC_STORE_SEMIPLANNAR    = 0,
    VENC_STORE_PACKAGE       = 1,
    VENC_STORE_PLANNAR      = 2
};

enum
{
    VENC_PACKAGE_UY0VY1      = 0b10001101,
    VENC_PACKAGE_Y0UY1V        = 0b11011000,
    VENC_PACKAGE_Y0VY1U     = 0b01111000
};

enum
{
    VENC_SEMIPLANNAR_420_UV  = 0,
    VENC_SEMIPLANNAR_420_VU  = 1,
    VENC_PLANNAR_420         = 2,
    VENC_PLANNAR_422         = 3,
    VENC_PACKAGE_422_YUYV    = 4,
    VENC_PACKAGE_422_UYVY    = 5,
    VENC_PACKAGE_422_YVYU    = 6,
    VENC_SEMIPLANNAR_422     = 7,
    VENC_UNKNOW              = 8

};

enum
{
    JPGE_STORE_SEMIPLANNAR    = 0,
    JPGE_STORE_PLANNAR       = 1,
    JPGE_STORE_PACKAGE      = 2
};

enum
{
    VEDU_CAP_LEVEL_QCIF = 0, /**<The resolution of the picture to be decoded is less than or equal to 176x144.*/ /**<CNcomment: 解码的图像大小不超过176*144 */
    VEDU_CAP_LEVEL_CIF  = 1,      /**<The resolution of the picture to be decoded less than or equal to 352x288.*/ /**<CNcomment: 解码的图像大小不超过352*288 */
    VEDU_CAP_LEVEL_D1   = 2,       /**<The resolution of the picture to be decoded less than or equal to 720x576.*/ /**<CNcomment: 解码的图像大小不超过720*576 */
    VEDU_CAP_LEVEL_720P = 3,     /**<The resolution of the picture to be decoded is less than or equal to 1280x720.*/ /**<CNcomment: 解码的图像大小不超过1280*720 */
    VEDU_CAP_LEVEL_1080P = 4,   /**<The resolution of the picture to be decoded is less than or equal to 1920x1080.*/ /**<CNcomment: 解码的图像大小不超过1920*1080 */
    VEDU_CAP_LEVEL_BUTT
} ;

enum
{
    VENC_FREQUENCY_200M      = 0,
    VENC_FREQUENCY_150M      = 2,
    VENC_FREQUENCY_100M     = 3
};

#ifdef __VENC_DRV_DBG__

HI_U32 TmpTime_dbg[100][7] = {{0, 0, 0, 0, 0, 0, 0}};
HI_U32 Isr_ID = 0;
HI_U32 PutMsg_EBD_ID = 0;
HI_U32 PutMsg_FBD_ID = 0;
HI_U32 GetMsg_EBD_ID = 0;
HI_U32 GetMsg_FBD_ID = 0;
HI_BOOL flage_dbg = 1;

#endif

#ifdef VENC_SUPPORT_JPGE
static const HI_U8 ZigZagScan[64] =
{
    0,  1,  5,  6, 14, 15, 27, 28,
    2,  4,  7, 13, 16, 26, 29, 42,
    3,  8, 12, 17, 25, 30, 41, 43,
    9, 11, 18, 24, 31, 40, 44, 53,
    10, 19, 23, 32, 39, 45, 52, 54,
    20, 22, 33, 38, 46, 51, 55, 60,
    21, 34, 37, 47, 50, 56, 59, 61,
    35, 36, 48, 49, 57, 58, 62, 63
};

static const HI_U8 Jpge_Yqt[64] =
{
    16, 11, 10, 16,  24,  40,  51,  61,
    12, 12, 14, 19,  26,  58,  60,  55,
    14, 13, 16, 24,  40,  57,  69,  56,
    14, 17, 22, 29,  51,  87,  80,  62,
    18, 22, 37, 56,  68, 109, 103,  77,
    24, 35, 55, 64,  81, 104, 113,  92,
    49, 64, 78, 87, 103, 121, 120, 101,
    72, 92, 95, 98, 112, 100, 103,  99
};
static const HI_U8 Jpge_Cqt[64] =
{
    17, 18, 24, 47, 99, 99, 99, 99,
    18, 21, 26, 66, 99, 99, 99, 99,
    24, 26, 56, 99, 99, 99, 99, 99,
    47, 66, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99
};


static const HI_U8 Jpge_JfifHdr[698] =  /* 2(SOI)+18(APP0)+207(DQT)+19(SOF)+432(DHT)+6(DRI)+14(SOS) */
{
    0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
    0xff, 0xdb, 0x00, 0x43, 0x00, 0x10, 0x0b, 0x0c, 0x0e, 0x0c, 0x0a, 0x10, 0x0e, 0x0d, 0x0e, 0x12, 0x11, 0x10, 0x13, 0x18,
    0x28, 0x1a, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25, 0x1d, 0x28, 0x3a, 0x33, 0x3d, 0x3c, 0x39, 0x33, 0x38, 0x37, 0x40,
    0x48, 0x5c, 0x4e, 0x40, 0x44, 0x57, 0x45, 0x37, 0x38, 0x50, 0x6d, 0x51, 0x57, 0x5f, 0x62, 0x67, 0x68, 0x67, 0x3e, 0x4d,
    0x71, 0x79, 0x70, 0x64, 0x78, 0x5c, 0x65, 0x67, 0x63, 0xff, 0xdb, 0x00, 0x43, 0x01, 0x11, 0x12, 0x12, 0x18, 0x15, 0x18,
    0x2f, 0x1a, 0x1a, 0x2f, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xff, 0xdb,
    0x00, 0x43, 0x02, 0x11, 0x12, 0x12, 0x18, 0x15, 0x18, 0x2f, 0x1a, 0x1a, 0x2f, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xff, 0xc0, 0x00, 0x11, 0x08, 0x01, 0x20, 0x01, 0x60, 0x03, 0x01, 0x22, 0x00,
    0x02, 0x11, 0x01, 0x03, 0x11, 0x02, 0xff, 0xc4, 0x00, 0x1f, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff,
    0xc4, 0x00, 0x1f, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x10, 0x00, 0x02, 0x01,
    0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05,
    0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1,
    0xc1, 0x15, 0x52, 0xd1, 0xf0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54,
    0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2,
    0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4,
    0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5,
    0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xc4, 0x00, 0xb5, 0x11,
    0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03,
    0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
    0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0, 0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17,
    0x18, 0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x73, 0x74,
    0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8,
    0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
    0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xdd,
    0x00, 0x04, 0x00, 0x64, 0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00
};
#endif

static const unsigned char QpTable[96] =
{
    16, 16, 16, 16,    16, 16, 16, 16,    16, 16, 16, 16,    16, 16, 16, 16,
    16, 16, 16, 16,    16, 16, 16, 16,    16, 16, 16, 16,    16, 16, 16, 16,
    16, 16, 16, 16,    16, 16, 18, 20,    21, 22, 23, 24,    25, 25, 26, 27,
    28, 28, 29, 29,    30, 30, 30, 31,    31, 32, 32, 33,    33, 33, 34, 34,
    34, 34, 35, 35,    35, 36, 36, 36,    36, 36, 37, 37,    37, 37, 38, 38,
    38, 38, 38, 39,    39, 39, 39, 39,    39, 40, 40, 40,    40, 41, 41, 41,
};
static const int TabLnx[64] =
{
       0, -1216, -972, -830, -729, -651, -587, -533,
    -486,  -445, -408, -374, -344, -316, -290, -265,
    -243,  -221, -201, -182, -164, -147, -131, -115,
    -100,   -86,  -72,  -59,  -46,  -34,  -22,  -11,
       0,    10,   21,   31,   41,   50,   60,   69,
      78,    86,   95,  103,  111,  119,  127,  134,
     142,   149,  156,  163,  170,  177,  183,  190,
     196,   202,  208,  214,  220,  226,  232,  237,
};
static const int MaxIPropDeltaQP[52] =
{
    10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
     9,  9,  8,  8,  7,  7,  6,  6,  5,  5,  5,  4,  4,  4,
     3,  3,  3,  3,  3,  2,  2,  2,  2,  2,  2,  1,  1,  1,
     1,  1,  1,  0,  0,  0,  0,  0,  0,  0,
};
/*******************************************************************/

VeduEfl_ChnCtx_S VeduChnCtx[HI_VENC_MAX_CHN];

VeduEfl_IpCtx_S VeduIpCtx;

extern OPTM_VENC_CHN_S g_stVencChn[HI_VENC_MAX_CHN];

extern VEDU_OSAL_EVENT g_VencWait_Stream[HI_VENC_MAX_CHN];

wait_queue_head_t gqueue;
volatile HI_U32 gwait;

extern volatile HI_U32 gencodeframe;
extern wait_queue_head_t gEncodeFrame;

extern spinlock_t g_SendFrame_Lock[HI_VENC_MAX_CHN];     /*lock the destroy and send frame*/
VEDU_OSAL_EVENT g_VENC_Event;
VEDU_OSAL_EVENT g_VENC_Event_stream;

static HI_VOID VENC_DRV_GetLastFrmInfo_OMX(VeduEfl_EncPara_S *pEncPara, VeduEfl_EncIn_S *pEncIn);
extern VENC_BUFFER_S g_stKernelOmxmmz[HI_VENC_MAX_CHN][OMX_OUTPUT_PORT_BUFFER_MAX];
extern HI_U32 g_map_count;
extern HI_U32 g_ummap_count;

#ifdef VENC_SUPPORT_JPGE
extern JPGE_EXPORT_FUNC_S *pJpgeFunc;
#endif

extern HI_S8 PriorityTab[2][16];

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        if (hVencChn == NULL)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
           break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_CHN_BY_UHND(u32VeChn, hVencUsrChn) \
    do {\
        if (hVencUsrChn == HI_INVALID_HANDLE)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hUsrHandle == hVencUsrChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_CHECK_ALL_EQUAL(wh,wt,rh,rt,flag)\
    do{  \
        if( (wh == wt) && (rh == rt) && (wt == rh))\
            flag = HI_TRUE; \
         else               \
            flag = HI_FALSE; \
      } while (0)

#define D_VENC_GET_CHN_FROM_TAB(s32ChnID,TabNO)\
    do{  \
         s32ChnID = PriorityTab[0][TabNO];\
      } while (0)

#define D_VENC_CHECK_ZERO(x, def) \
    do {\
        if ((x) == 0)\
        {\
          HI_ERR_VENC("Error: Division by zero in kernel\n"); \
           x = (def);\
        }\
    } while (0)

#define D_VENC_RC_ABS(x,y) (((x) > (y)) ? ((x) - (y)):((y) - (x)))

#define D_VENC_RC_UPDATE(data,curdata) \
    do{\
          *(data + 5) = *(data + 4);\
          *(data + 4) = *(data + 3);\
          *(data + 3) = *(data + 2);\
          *(data + 2) = *(data + 1);\
          *(data + 1) = *data;\
          *data = curdata;\
        }while(0)

#define D_VENC_RC_MAX(x,y) ((x)>(y) ? (x) : (y))
#define D_VENC_RC_MIN(x,y) ((x)>(y) ? (y) : (x))


#define D_VENC_RC_MIN3(x,y,z) (((x) < (y)) ? D_VENC_RC_MIN(x, z) : D_VENC_RC_MIN(y, z))
#define D_VENC_RC_MAX3(x,y,z) (((x) > (y)) ? D_VENC_RC_MAX(x, z) : D_VENC_RC_MAX(y, z))
#define D_VENC_RC_MEDIAN(x,y,z) (((x) + (y) + (z) - D_VENC_RC_MAX3(x, y, z)) - D_VENC_RC_MIN3(x, y, z))

HI_S32 VEDU_DRV_RCProcessOfRecoding(VeduEfl_EncPara_S *pEncPara, VeduEfl_EncIn_S *EncIn);
HI_S32 VENC_DRV_GetEncodePara(VeduEfl_EncPara_S *pEncPara, VeduEfl_EncIn_S *pEncIn);

HI_BOOL IsChipIDV500R001(HI_CHIP_TYPE_E enChipType, HI_CHIP_VERSION_E enChipVersion)
{
    if (((enChipType == HI_CHIP_TYPE_HI3798M) && (enChipVersion == HI_CHIP_VERSION_V300)) ||
        ((enChipType == HI_CHIP_TYPE_HI3796M) && (enChipVersion == HI_CHIP_VERSION_V200)))
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

void Update_StreamBuffer(int data[30],int data2)
{
    int i;
    for(i = 29; i > 0;i--)
    {
        data[i] = data[i-1];
    }
    data[0] = data2;
}

static HI_VOID H264e_PutTrailingBits(tBitStream *pBS)
{
    VENC_DRV_BsPutBits31(pBS, 1, 1);

    if (pBS->totalBits & 7)
    {
        VENC_DRV_BsPutBits31(pBS, 0, 8 - (pBS->totalBits & 7));
    }

    *pBS->pBuff++ = (pBS->bBigEndian ? pBS->tU32b : REV32(pBS->tU32b));
}

static HI_U32 H264e_MakeSPS(HI_U8 *pSPSBuf, const VeduEfl_H264e_SPS_S *pSPS)
{
    HI_U32 code, TotalMb, profile_idc, level_idc,direct_8x8_interence_flag;
    int bits;

    tBitStream BS;

    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pSPSBuf);

    TotalMb = pSPS->FrameWidthInMb * pSPS->FrameHeightInMb;

    if (TotalMb <= 99)
    {
        level_idc = 10;
    }
    else if (TotalMb <= 396)
    {
        level_idc = 20;
    }
    else if (TotalMb <= 792)
    {
        level_idc = 21;
    }
    else if (TotalMb <= 1620)
    {
        level_idc = 30;
    }
    else if (TotalMb <= 3600)
    {
        level_idc = 31;
    }
    else if (TotalMb <= 5120)
    {
        level_idc = 32;
    }
    else if (TotalMb <= 8192)
    {
        level_idc = 41;
    }
    else
    {
        level_idc = 0;
    }

    if (TotalMb < 1620)
    {
        direct_8x8_interence_flag = 0;
    }
    else
    {
        direct_8x8_interence_flag = 1;
    }

    profile_idc = pSPS->ProfileIDC;

    VENC_DRV_BsPutBits32(&BS, 1, 32);

    VENC_DRV_BsPutBits31(&BS, 0, 1); // forbidden_zero_bit
    VENC_DRV_BsPutBits31(&BS, 3, 2); // nal_ref_idc
    VENC_DRV_BsPutBits31(&BS, 7, 5); // nal_unit_type

    VENC_DRV_BsPutBits31(&BS, profile_idc, 8);
    VENC_DRV_BsPutBits31(&BS, 0x00, 8);
    VENC_DRV_BsPutBits31(&BS, level_idc, 8);

    VENC_DRV_BsPutBits31(&BS, 1, 1); // ue, sps_id = 0

   if(100 == pSPS->ProfileIDC)   //just for high profile
   {
        VENC_DRV_BsPutBits31(&BS, 0x2, 3);
        VENC_DRV_BsPutBits31(&BS, 0xC, 4);
   }

    VENC_DRV_BsPutBits31(&BS, 1, 1); // ue, log2_max_frame_num_minus4 = 0

    VENC_DRV_BsPutBits31(&BS, 3, 3); // ue, pic_order_cnt_type = 2
    VENC_DRV_BsPutBits31(&BS, 2, 3); // ue, num_ref_frames = 1 (or 2)
    VENC_DRV_BsPutBits31(&BS, 0, 1); // u1, gaps_in_frame_num_value_allowed_flag

    ue_vlc(bits, code, (pSPS->FrameWidthInMb - 1));
    VENC_DRV_BsPutBits31(&BS, code, bits);
    ue_vlc(bits, code, (pSPS->FrameHeightInMb - 1));
    VENC_DRV_BsPutBits31(&BS, code, bits);

    VENC_DRV_BsPutBits31(&BS, 1, 1); // u1, frame_mbs_only_flag = 1 (or 0)

    if (0)                // !pSPS->FrameMbsOnlyFlag
    {
        VENC_DRV_BsPutBits31(&BS, 0, 1); // mb_adaptive_frame_field_flag = 0
        VENC_DRV_BsPutBits31(&BS, 1, 1); // direct_8x8_inference_flag
    }
    else
    {
        VENC_DRV_BsPutBits31(&BS, direct_8x8_interence_flag, 1); // direct_8x8_inference_flag
    }

    {
        int bFrameCropping = ((pSPS->FrameCropLeft | pSPS->FrameCropRight |
                               pSPS->FrameCropTop | pSPS->FrameCropBottom) != 0);

        VENC_DRV_BsPutBits31(&BS, bFrameCropping, 1);

        if (bFrameCropping)
        {
            ue_vlc(bits, code, pSPS->FrameCropLeft);
            VENC_DRV_BsPutBits31(&BS, code, bits);
            ue_vlc(bits, code, pSPS->FrameCropRight);
            VENC_DRV_BsPutBits31(&BS, code, bits);
            ue_vlc(bits, code, pSPS->FrameCropTop);
            VENC_DRV_BsPutBits31(&BS, code, bits);
            ue_vlc(bits, code, pSPS->FrameCropBottom);
            VENC_DRV_BsPutBits31(&BS, code, bits);
        }
    }
    VENC_DRV_BsPutBits31(&BS, 0, 1); // vui_parameters_present_flag
    H264e_PutTrailingBits(&BS);

    HI_INFO_VENC("VENC h264 profile_id:%d,level_id:%d,num_ref_frames: %d\n",profile_idc,level_idc,1);
    return (HI_U32)BS.totalBits;
}

static HI_U32 H264e_MakePPS(HI_U8 *pPPSBuf, const VeduEfl_H264e_PPS_S *pPPS)
{
    HI_U32 code;
    int bits;
    HI_U32 b = pPPS->H264CabacEn ? 1 : 0;

    tBitStream BS;



    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pPPSBuf);

    VENC_DRV_BsPutBits32(&BS, 1, 32);

    VENC_DRV_BsPutBits31(&BS, 0, 1); // forbidden_zero_bit
    VENC_DRV_BsPutBits31(&BS, 3, 2); // nal_ref_idc
    VENC_DRV_BsPutBits31(&BS, 8, 5); // nal_unit_type

    VENC_DRV_BsPutBits31(&BS, 1, 1); // pps_id = 0
    VENC_DRV_BsPutBits31(&BS, 1, 1); // sps_id = 0

    VENC_DRV_BsPutBits31(&BS, b, 1); // entropy_coding_mode_flag = 0
    VENC_DRV_BsPutBits31(&BS, 0, 1); // pic_order_present_flag
    VENC_DRV_BsPutBits31(&BS, 1, 1); // num_slice_groups_minus1
    VENC_DRV_BsPutBits31(&BS, 1, 1); // num_ref_idx_l0_active_minus1 = 0 (or 1)
    VENC_DRV_BsPutBits31(&BS, 1, 1); // num_ref_idx_l1_active_minus1 = 0
    VENC_DRV_BsPutBits31(&BS, 0, 3); // weighted_pred_flag & weighted_bipred_idc
    VENC_DRV_BsPutBits31(&BS, 3, 2); // pic_init_qp_minus26 & pic_init_qs_minus26

    se_vlc(bits, code, pPPS->ChrQpOffset); // chroma_qp_index_offset
    VENC_DRV_BsPutBits31(&BS, code, bits);

    VENC_DRV_BsPutBits31(&BS, 1, 1);                // deblocking_filter_control_present_flag
    VENC_DRV_BsPutBits31(&BS, pPPS->ConstIntra, 1); // constrained_intra_pred_flag

    VENC_DRV_BsPutBits31(&BS, 0, 1);                // redundant_pic_cnt_present_flag

    if (pPPS->H264HpEn)
    {
        VENC_DRV_BsPutBits31(&BS, 1, 1); // transform_8x8_mode_flag
        VENC_DRV_BsPutBits31(&BS, 0, 1); // pic_scaling_matrix_present_flag
        se_vlc(bits, code, pPPS->ChrQpOffset);
        VENC_DRV_BsPutBits31(&BS, code, bits);
    }

    H264e_PutTrailingBits(&BS);
    return (HI_U32)BS.totalBits;
}

static HI_U32 H264e_MakeSlcHdr(HI_U32* pHdrBuf, HI_U32* pReorderBuf, HI_U32* pMarkBuf,
                               const VeduEfl_H264e_SlcHdr_S*pSlcHdr)
{
    HI_U32 code   = 0;
    HI_U32 buf[8] = {0};
    int bits, i, bitPara;

    tBitStream BS;

    VENC_DRV_BsOpenBitStream(&BS, buf);

    ue_vlc(bits, code, pSlcHdr->slice_type);
    VENC_DRV_BsPutBits31(&BS, code, bits);                                        // slice_type, 0(P) or 2(I)

    VENC_DRV_BsPutBits31(&BS, 1, 1);                      // pic_parameter_set_id
    VENC_DRV_BsPutBits31(&BS, pSlcHdr->frame_num & 0xF, 4); // frame number

    if (pSlcHdr->slice_type == 2) // all I Picture be IDR
    {
        ue_vlc(bits, code, g_idr_pic_id & 0xF);
        VENC_DRV_BsPutBits31(&BS, code, bits);
        g_idr_pic_id++;
    }
    else if(pSlcHdr->NumRefIndex ==  0)
    {
      VENC_DRV_BsPutBits31(&BS, 0, 1); // num_ref_idx_active_override_flag
    }
    else
    {
      VENC_DRV_BsPutBits31(&BS, 1, 1); // num_ref_idx_active_override_flag
      ue_vlc(bits, code, pSlcHdr->NumRefIndex);
      VENC_DRV_BsPutBits31(&BS, code, bits);
    }

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pHdrBuf[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32)
        {
            pHdrBuf[i] >>= (32 - bits);
        }
    }

    bitPara = BS.totalBits;

    /****** RefPicListReordering() ************************************/

    VENC_DRV_BsOpenBitStream(&BS, buf);

    VENC_DRV_BsPutBits31(&BS, 0, 1);/* ref_pic_list_reordering_flag_l0 = 0 ("0") */

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pReorderBuf[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32)
        {
            pReorderBuf[i] >>= (32 - bits);
        }
    }

    bitPara |= BS.totalBits << 8;

    /****** DecRefPicMarking() *****************************************/

    VENC_DRV_BsOpenBitStream(&BS, buf);

    if (pSlcHdr->slice_type == 2)
    {
        VENC_DRV_BsPutBits31(&BS, 0, 1);/* no_output_of_prior_pics_flag */
        VENC_DRV_BsPutBits31(&BS, 0, 1);/* long_term_reference_flag     */
    }
    else
    {
        VENC_DRV_BsPutBits31(&BS, 0, 1);/* adaptive_ref_pic_marking_mode_flag */
    }

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pMarkBuf[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32)
        {
            pMarkBuf[i] >>= (32 - bits);
        }
    }

    bitPara |= BS.totalBits << 16;
    return (HI_U32)bitPara;
}

/*获取VPS语法信息*/
static HI_U32 H265e_MakeVPS(HI_U8 *pVPSBuf, const VeduEfl_H265e_VPS_S *pVPS)
{
    HI_U32 code;
    int    bits;

    int i = 0;
    tBitStream BS;

    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pVPSBuf);

    VENC_DRV_BsPutBits32(&BS, 1, 32);
    VENC_DRV_BsPutBits31(&BS, 0x4001, 16);

    VENC_DRV_BsPutBits31(&BS, 0, 4);           //video_parameter_set_id = 0  u(4)
    VENC_DRV_BsPutBits31(&BS, 3, 2);           //vps_reserved_three_2bits = 3  u(2)
    VENC_DRV_BsPutBits31(&BS, 0, 6);           //vps_max_layers_minus1 = 0   u(6)
    VENC_DRV_BsPutBits31(&BS, 0, 3);           //vps_max_sub_layers_minus1 = 0或1  u(3)   开大小P，取值为1；否则取值为0
    VENC_DRV_BsPutBits31(&BS, 1, 1);           //vps_temporal_id_nesting_flag = 1 u(1)
    VENC_DRV_BsPutBits31(&BS, 0xffff, 16);     //vps_reserved_ffff_16bits = 0xffff u(16)

    {   ////////profile_tier_level
        VENC_DRV_BsPutBits31(&BS, 0, 2);       //general_profile_space=0  u(2)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_tier_flag=0  u(1)
        VENC_DRV_BsPutBits31(&BS, 1, 5);       //general_profile_idc =1   u(5)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_profile_compatibility_flag[0]  u(1)
        VENC_DRV_BsPutBits31(&BS, 1, 1);       //general_profile_compatibility_flag[1]  u(1)
        VENC_DRV_BsPutBits31(&BS, 1, 1);       //general_profile_compatibility_flag[2]  u(1)

        for(i = 3; i<32;i++)
        {
            VENC_DRV_BsPutBits31(&BS, 0, 1);   //general_profile_compatibility_flag[][j]  u(1)
        }

        VENC_DRV_BsPutBits31(&BS, pVPS->general_progressive_source_flag, 1);       //general_progressive_source_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, pVPS->general_interlaced_source_flag, 1);       //general_interlaced_source_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_non_packed_constraint_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_frame_only_constraint_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, 0, 16);      //general_reserved_zero_44bits[0..15] = 0  u(16)
        VENC_DRV_BsPutBits31(&BS, 0, 16);      //general_reserved_zero_44bits[16..31] = 0  u(16)
        VENC_DRV_BsPutBits31(&BS, 0, 12);      //general_reserved_zero_44bits[32..43] = 0  u(12)
        VENC_DRV_BsPutBits31(&BS, 0, 8);       //general_level_idc=0    u(8)
    }

    VENC_DRV_BsPutBits31(&BS, 1, 1);           //vps_sub_layer_ordering_info_present_flag = 1  u(1)

    for( i = 0; i <= 0; i++ )
    {
        ue_vlc(bits, code, 1);
        VENC_DRV_BsPutBits31(&BS, code, bits); //vps_max_dec_pic_buffering_minus1[ j ]  ue(v), 1

        ue_vlc(bits, code, 0);
        VENC_DRV_BsPutBits31(&BS, code, bits); //vps_max_num_reorder_pics[ j ]  ue(v),0

        ue_vlc(bits, code, 0);
        VENC_DRV_BsPutBits31(&BS, code, bits); //vps_max_latency_increase_plus1[ j ]  ue(v),0
    }


    VENC_DRV_BsPutBits31(&BS, 0, 6);           //vps_max_layer_id=0  u(6)

    ue_vlc(bits, code, 0);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //vps_num_layer_sets_minus1=0  ue(v)

    VENC_DRV_BsPutBits31(&BS, 0, 1);           //vps_timing_info_present_flag = 0  u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //vps_extension_flag=0    u(1)

    H264e_PutTrailingBits(&BS);

    return (HI_U32)BS.totalBits;
}

/*获取SPS语法信息*/
static HI_U32 H265e_MakeSPS(HI_U8 *pSPSBuf, const VeduEfl_H265e_SPS_S *pSPS)
{
    HI_U32 code;
    int    bits, i;

    tBitStream BS;
    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pSPSBuf);

    VENC_DRV_BsPutBits32(&BS, 1, 32);
    VENC_DRV_BsPutBits31(&BS, 0x4201, 16);

    VENC_DRV_BsPutBits31(&BS, 0, 4);           // video_parameter_set_id  u(4)
    VENC_DRV_BsPutBits31(&BS, 0, 3);           // sps_max_sub_layers_minus1=0  u(3)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           // sps_temporal_id_nesting_flag = 1  u(1)

    {   //profile_tier_level
        VENC_DRV_BsPutBits31(&BS, 0, 2);       //general_profile_space  u(2)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_tier_flag=0  u(1)
        VENC_DRV_BsPutBits31(&BS, 1, 5);       //general_profile_idc=1   u(5)

        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_profile_compatibility_flag[][0] =1u(1)
        VENC_DRV_BsPutBits31(&BS, 1, 1);       //general_profile_compatibility_flag[][1] =1u(1)
        VENC_DRV_BsPutBits31(&BS, 1, 1);       //general_profile_compatibility_flag[][2] =1u(1)
        for ( i = 3; i < 32; i++ )
        {
            VENC_DRV_BsPutBits31(&BS, 0, 1);   //general_profile_compatibility_flag[][j]=0  u(1)
        }
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_progressive_source_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_interlaced_source_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_non_packed_constraint_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //general_frame_only_constraint_flag = 0  u(1)
        VENC_DRV_BsPutBits31(&BS, 0, 16);      //general_reserved_zero_44bits[0..15] = 0  u(16)
        VENC_DRV_BsPutBits31(&BS, 0, 16);      //general_reserved_zero_44bits[16..31] = 0  u(16)
        VENC_DRV_BsPutBits31(&BS, 0, 12);      //general_reserved_zero_44bits[32..43] = 0  u(12)
        VENC_DRV_BsPutBits31(&BS, 0, 8);       //general_level_idc    u(8)
    }


    VENC_DRV_BsPutBits31(&BS, 1, 1);           //seq_parameter_set_id   ue(v) //sps_id = 0

    ue_vlc(bits, code, 1);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //chroma_format_idc = 1  ue(v)

    ue_vlc(bits, code, pSPS->uiPicWidthInLumaSamples);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //pic_width_in_luma_samples   ue(v)

    ue_vlc(bits, code, pSPS->uiPicHeightInLumaSamples);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //pic_height_in_luma_samples  ue(v)

    VENC_DRV_BsPutBits31(&BS, pSPS->bPicCroppingFlag, 1);

    if(pSPS->bPicCroppingFlag == 1)
    {
        ue_vlc(bits, code, pSPS->uiPicCropLeftOffset);
        VENC_DRV_BsPutBits31(&BS, code, bits);

        ue_vlc(bits, code, pSPS->uiPicCropRightOffset);
        VENC_DRV_BsPutBits31(&BS, code, bits);

        ue_vlc(bits, code, pSPS->uiPicCropTopOffset);
        VENC_DRV_BsPutBits31(&BS, code, bits);

        ue_vlc(bits, code, pSPS->uiPicCropBottomOffset);
        VENC_DRV_BsPutBits31(&BS, code, bits);
    }

    VENC_DRV_BsPutBits31(&BS, 1, 1);           // bit_depth_luma_minus8 = 0    ue(v)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           // bit_depth_chroma_minus8 = 0   ue(v)

    ue_vlc(bits, code, 12);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //log2_max_pic_order_cnt_lsb_minus4 =12   ue(v)

    VENC_DRV_BsPutBits31(&BS, 1, 1);           //sps_sub_layer_ordering_info_present_flag = 1   u(1)

    ue_vlc(bits, code, 1);
    VENC_DRV_BsPutBits31(&BS, code, bits); //sps_max_dec_pic_buffering_minus1[ i ] = 1    ue(v)

    ue_vlc(bits, code, 0);
    VENC_DRV_BsPutBits31(&BS, code, bits); //sps_max_num_reorder_pics[ i ]=0      ue(v),

    VENC_DRV_BsPutBits31(&BS, 1, 1);       //sps_max_latency_increase_plus1[ i ]=0     ue(v)

    VENC_DRV_BsPutBits31(&BS, 1, 1);           // log2_min_luma_coding_block_size_minus3=0     ue(v)

    if (VeduIpCtx.IsChipIDV500R001 == HI_TRUE)
    {
        ue_vlc(bits, code, 2);
    }
    else
    {
        ue_vlc(bits, code, 3);
    }

    VENC_DRV_BsPutBits31(&BS, code, bits);     // log2_diff_max_min_luma_coding_block_size = 3   ue(v)

    VENC_DRV_BsPutBits31(&BS, 1, 1);           //log2_min_transform_block_size_minus2 =0    ue(v)

    ue_vlc(bits, code, 2);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //log2_diff_max_min_transform_block_size=2   ue(v)

    VENC_DRV_BsPutBits31(&BS, 1, 1);           //max_transform_hierarchy_depth_inter =0   ue(v)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           //max_transform_hierarchy_depth_intra =0   ue(v)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //scaling_list_enable_flag=0         u(1)

    VENC_DRV_BsPutBits31(&BS, 0, 1);           //amp_enabled_flag =0        u(1)

    VENC_DRV_BsPutBits31(&BS, 1, 1);           //sample_adaptive_offset_enabled_flag =0   u(1)

    VENC_DRV_BsPutBits31(&BS, pSPS->bPcmEnable, 1);
    if (1 == pSPS->bPcmEnable)
    {
        VENC_DRV_BsPutBits31(&BS, 7, 4);       //pcm_sample_bit_depth_luma_minus1=7    u(4)
        VENC_DRV_BsPutBits31(&BS, 7, 4);       //pcm_sample_bit_depth_chroma_minus1=7  u(4)

        ue_vlc(bits, code, (pSPS->iPcmLog2MinSize - 3));
        VENC_DRV_BsPutBits31(&BS, code, bits); //log2_min_pcm_luma_coding_block_size_minus3    ue(v)

        ue_vlc(bits, code, (pSPS->iPcmLog2MaxSize - pSPS->iPcmLog2MinSize));
        VENC_DRV_BsPutBits31(&BS, code, bits); //log2_diff_max_min_pcm_luma_coding_block_size    ue(v)

        VENC_DRV_BsPutBits31(&BS, 0, 1);       //pcm_loop_filter_disabled_flag    u(1)
    }

    ue_vlc(bits, code, 1);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //num_short_term_ref_pic_sets = 1   ue(v)

    {   /*short_term_ref_pic_set*/
        ue_vlc(bits, code, 1);
        VENC_DRV_BsPutBits31(&BS, code, bits); //num_Negative_pics = 1

        ue_vlc(bits, code, 0);
        VENC_DRV_BsPutBits31(&BS, code, bits); //num_positive_pics = 0  ue(v)

        ue_vlc(bits, code,  0);
        VENC_DRV_BsPutBits31(&BS, code, bits); //delta_poc_s0_minus1 = 0        ue(v)

        VENC_DRV_BsPutBits31(&BS, 1, 1);       //used_by_curr_pic_s0_flag = 1   u(1)
    }

    VENC_DRV_BsPutBits31(&BS, 0, 1);           //long_term_ref_pics_present_flag = 0     u(1)

    VENC_DRV_BsPutBits31(&BS, pSPS->sps_temporal_mvp_enable_flag, 1);  //sps_temporal_mvp_enable_flag =1           u(1)
    VENC_DRV_BsPutBits31(&BS, pSPS->bStrongIntraSmoothingFlag, 1);     //strong_intra_smoothing_enable_flag=1      u(1)

    VENC_DRV_BsPutBits31(&BS, 0, 1);           //vui_parameters_present_flag =0        u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //sps_extension_flag = 0                u(1)

    H264e_PutTrailingBits(&BS);

    return (HI_U32)BS.totalBits;
}

/*获取PPS语法信息*/

static HI_U32 H265e_MakePPS(HI_U8 *pPPSBuf, const VeduEfl_H265e_PPS_S *pPPS)
{
    HI_U32 code;
    int    bits;

    tBitStream BS;
    VENC_DRV_BsOpenBitStream(&BS, (HI_U32 *)pPPSBuf);

    VENC_DRV_BsPutBits32(&BS, 1, 32);
    VENC_DRV_BsPutBits31(&BS, 0x4401, 16);

    VENC_DRV_BsPutBits31(&BS, 1, 1);           // pic_parameter_set_id=0   ue(v)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           // seq_parameter_set_id=0   ue(v)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           // dependent_slice_segments_enabled_flag=0        u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           // output_flag_present_flag=0        u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 3);           // num_extra_slice_header_bits = 0     u(3)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           // sign_data_hiding_flag = 0   u(1)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           // cabac_init_present_flag=0    u(1)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           // num_ref_idx_l0_default_active_minus1 =0     ue(v)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           // num_ref_idx_l1_default_active_minus1=0      ue(v)

    se_vlc(bits, code, 0);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //pic_init_qp_minus26=0                       se(v)

    VENC_DRV_BsPutBits31(&BS, 0, 1);           //constrained_intra_pred_flag =0              u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //transform_skip_enabled_flag=0               u(1)

    VENC_DRV_BsPutBits31(&BS, pPPS->bCUQpDeltaEnable, bits);    //cu_qp_delta_enabled_flag               u(1)
    if (pPPS->bCUQpDeltaEnable == 1)
    {
        if (VeduIpCtx.IsChipIDV500R001 == HI_TRUE)
        {
            ue_vlc(bits, code, 1);
        }
        else
        {
            ue_vlc(bits, code, 2);
        }

        VENC_DRV_BsPutBits31(&BS, code, bits); //diff_cu_qp_delta_depth                ue(v)
    }

    se_vlc(bits, code, pPPS->iCbQpOffset);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //pic_cb_qp_offset                    se(v)

    se_vlc(bits, code, pPPS->iCrQpOffset);
    VENC_DRV_BsPutBits31(&BS, code, bits);     //pic_cr_qp_offset                    se(v)

    VENC_DRV_BsPutBits31(&BS, 0, 1);           //pic_slice_chroma_qp_offsets_present_flag = 0   u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //weighted_pred_flag = 0        u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //weighted_bipred_flag = 0        u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //transquant_bypass_enable_flag   u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //tiles_enabled_flag = 0             u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //entropy_coding_sync_enabled_flag    u(1)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           //loop_filter_across_slices_enabled_flag    u(1)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           //deblocking_filter_control_present_flag = 1   u(1)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           //deblocking_filter_override_enabled_flag   u(1)
    VENC_DRV_BsPutBits31(&BS, pPPS->bPicDisableDBFilter, 1);        //pic_disable_deblocking_filter_flag   u(1)
    if( 0 == pPPS->bPicDisableDBFilter )
    {
        se_vlc(bits, code, 0);
        VENC_DRV_BsPutBits31(&BS, code, bits); //pps_beta_offset_div2    se(v)

        se_vlc(bits, code, 0);
        VENC_DRV_BsPutBits31(&BS, code, bits); //pps_tc_offset_div2       se(v)
    }

    VENC_DRV_BsPutBits31(&BS, 0, 1);           //pic_scaling_list_data_present_flag    u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //lists_modification_present_flag = 0   u(1)
    VENC_DRV_BsPutBits31(&BS, 1, 1);           //log2_parallel_merge_level_minus2=0    ue(v)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //slice_segment_header_extension_present_flag=0     u(1)
    VENC_DRV_BsPutBits31(&BS, 0, 1);           //pps_extension_flag    u(1)

    H264e_PutTrailingBits(&BS);

    return (HI_U32)BS.totalBits;
}

static HI_VOID H265e_MakeSliceHead_DBSAO(VeduEfl_EncPara_S *pEncPara, const VeduEfl_H265e_SlcHdr_S *pSlcHdr, tBitStream *pBS)
{
    HI_U32 code, bSAOEnabled, bDBFEnabled;
    int    bits;

    if ( 1 == pSlcHdr->bDBFilterCtlPresent )
    {
        if ( 1 == pSlcHdr->bDBFilterOverrideEnabled )
        {
            VENC_DRV_BsPutBits31(pBS, pSlcHdr->bDFOverrideFlag, 1);        //deblocking_filter_override_flag        u(1)
        }
        if ( 1 == pSlcHdr->bDFOverrideFlag )
        {
            VENC_DRV_BsPutBits31(pBS, pSlcHdr->bSliceHeaderDisableDF, 1);  //slice_disable_deblocking_filter_flag     u(1)
            if( 0 == pSlcHdr->bSliceHeaderDisableDF )
            {
                se_vlc(bits, code, 0);
                VENC_DRV_BsPutBits31(pBS, code, bits);                     //beta_offset_div2        se(v)

                se_vlc(bits, code, 0);
                VENC_DRV_BsPutBits31(pBS, code, bits);                     //tc_offset_div2          se(v)
            }
        }
    }
    bSAOEnabled = (0 == pSlcHdr->bSAOEnabledFlag) ? 0 : (pSlcHdr->bSliceSaoLuma || pSlcHdr->bSliceSaoChroma);
    bDBFEnabled = (0 == pSlcHdr->bSliceHeaderDisableDF) ? 1 : 0;

    if( 1 == bSAOEnabled || 1 == bDBFEnabled ||pSlcHdr->bSliceHeaderDisableDF == 0 )
    {
        VENC_DRV_BsPutBits31(pBS, pSlcHdr->bSliceLFAcrossSlice, 1);        //slice_loop_filter_across_slices_enabled_flag     u(1)
    }

    return;
}

static HI_U32 H265e_MakeSliceHead(VeduEfl_EncPara_S* pEncPara, const VeduEfl_H265e_SlcHdr_S *pSlcHdr)
{
    HI_U32 code, buf[8];
    int    bits, i;

    tBitStream BS;

    // part1
    VENC_DRV_BsOpenBitStream(&BS, buf);

    if( 2 == pSlcHdr->eSliceType )  //H265E_I_SLICE
    {
        VENC_DRV_BsPutBits31(&BS, 0, 1);       //no_output_of_prior_pics_flag = 0    u(1)
    }

    VENC_DRV_BsPutBits31(&BS, 1, 1);           //slice_pic_parameter_set_id=0         ue(v)
    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pEncPara->stHal.slchdr_part1 = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32) { pEncPara->stHal.slchdr_part1 >>= (32 - bits); }
    }
    pEncPara->stHal.slchdr_size_part1 = BS.totalBits;

    // part2
    VENC_DRV_BsOpenBitStream(&BS, buf);

    ue_vlc(bits, code, pSlcHdr->eSliceType);
    VENC_DRV_BsPutBits31(&BS, code, bits);                     //slice_type    ue(v)

    if ( 2 != pSlcHdr->eSliceType )
    {
        VENC_DRV_BsPutBits31(&BS, pSlcHdr->uiPocLsb, 16);      //pic_order_cnt_lsb         u(16)
        VENC_DRV_BsPutBits31(&BS, 1, 1);                       //short_term_ref_pic_set_sps_flag=1     u(1)

        if ( pSlcHdr->bSpsTemporalMvpEnableFlag )
        {
            VENC_DRV_BsPutBits31(&BS, 1, 1);                   //enable_temporal_mvp_flag=1        u(1)
        }
    }

    VENC_DRV_BsPutBits31(&BS, pSlcHdr->bSliceSaoLuma, 1);      //slice_sao_luma_flag                  u(1)
    VENC_DRV_BsPutBits31(&BS, pSlcHdr->bSliceSaoChroma, 1);    //slice_sao_chroma_flag                u(1)

    if ( pSlcHdr->eSliceType != 2 )
    {
        VENC_DRV_BsPutBits31(&BS, 1, 1);                       //num_ref_idx_active_override_flag = 1    u(1)

        ue_vlc(bits, code,  pSlcHdr->num_ref_idx_l0_active_minus1);
        VENC_DRV_BsPutBits31(&BS, code, bits);                 //num_ref_idx_l0_active_minus1

        if( pSlcHdr->eSliceType == 0)
        {
            VENC_DRV_BsPutBits31(&BS, 1, 1);                   //num_ref_idx_l1_active_minus1
        }

        if( pSlcHdr->eSliceType == 0)
        {
            VENC_DRV_BsPutBits31(&BS, 0, 1);                   //mvd_l1_zero_flag
        }

        VENC_DRV_BsPutBits31(&BS, 0, 1);                       //cabac_init_flag

        if (pSlcHdr->bSpsTemporalMvpEnableFlag)
        {
            if( pSlcHdr->eSliceType == 0)
            {
                VENC_DRV_BsPutBits31(&BS, pSlcHdr->collocated_from_l0_flag, 1);
            }

            if( ((pSlcHdr->collocated_from_l0_flag ==1) &&(pSlcHdr->num_ref_idx_l0_active_minus1>0))
            || ((pSlcHdr->collocated_from_l0_flag ==0)  &&(pSlcHdr->num_ref_idx_l0_active_minus1>0)))
            {
                ue_vlc(bits, code, 0);
                VENC_DRV_BsPutBits31(&BS, code, bits);
            }
        }

        ue_vlc(bits, code, pSlcHdr->five_minus_max_num_merge_cand);
        VENC_DRV_BsPutBits31(&BS, code, bits);                             //five_minus_max_num_merge_cand=3         ue(v)

    }

    se_vlc(bits, code, pSlcHdr->iSliceQPDelta);
    VENC_DRV_BsPutBits31(&BS, code, bits);                                 //slice_qp_delta     se(v)

    H265e_MakeSliceHead_DBSAO(pEncPara, pSlcHdr, &BS);

    *BS.pBuff++ = (BS.bBigEndian ? BS.tU32b : REV32(BS.tU32b));

    bits = BS.totalBits;

    for (i = 0; bits > 0; i++, bits -= 32)
    {
        pEncPara->stHal.CABAC_SLCHDR_PART2_SEG[i] = BS.bBigEndian ? buf[i] : REV32(buf[i]);
        if (bits < 32) { pEncPara->stHal.CABAC_SLCHDR_PART2_SEG[i] >>= (32 - bits); }
    }
    pEncPara->stHal.slchdr_size_part2 = BS.totalBits;

    return (HI_U32)BS.totalBits;
}

static HI_U32 CheckPreventionThreeByte(HI_U8 *pcStream, HI_U32 iNum ,HI_U8 *tempStream)
{
    HI_U32 iInsertBytes  = 0;
    HI_U32 i = 0, j = 0;
    HI_U32 inum = iNum/8;

    if ( inum < 5 )
    {
        return iInsertBytes;
       //return;
    }
    for ( i=0; i<6; i++,j++ )
    {
        tempStream[j]     = pcStream[i];

    }
    for ( i=6,j = 6; i<=inum-3; i++ )
    {
        tempStream[j]     = pcStream[i];
        tempStream[j + 1] = pcStream[i + 1];

        if ( ( 0 == pcStream[i] ) && ( 0 == pcStream[i+1] ) )
        {
            if ( ( 0 == pcStream[i+2] ) || ( 1 == pcStream[i+2] ) || ( 2 == pcStream[i+2] ) || ( 3 == pcStream[i+2] ))
            {
                tempStream[j + 2] = 0x03;
                iInsertBytes++;


                if ( (i == (inum - 3)) || (i == (inum - 4)) )
                {
                    tempStream[j + 3] = pcStream[i + 2];
                    tempStream[j + 4] = pcStream[i + 3];
                    i += 1;
                }
                else
                {
                    i += 1;
                    j += 3;
                }
            }
            else
            {
                tempStream[j + 2] = pcStream[i + 2];
                j++;
            }
        }
        else
        {
            tempStream[j + 2] = pcStream[i + 2];
            j++;
        }
    }

    return iInsertBytes;
}

HI_VOID SetStreamInfo(VeduEfl_EncPara_S *pEncPara, STRMMNG_STREAM_INFO_S *pstStreamInfo)
{
    memset(pstStreamInfo, 0, sizeof(STRMMNG_STREAM_INFO_S));

    pstStreamInfo->ParaSetLen = pEncPara->stHal.ParaSetLen;
    pstStreamInfo->ParaSetRealLen = pEncPara->stHal.ParaSetRealLen;
    pstStreamInfo->pParaSetArray  = pEncPara->stHal.ParaSetArray;

    pstStreamInfo->StrmBufRpVirAddr = pEncPara->StrmBufRpVirAddr;
    pstStreamInfo->StrmBufWpVirAddr = pEncPara->StrmBufWpVirAddr;;

    pstStreamInfo->pStreamBufAddrArray = pEncPara->stHal.VEDU_STRM_ADDR;
    pstStreamInfo->pStreamBufLenArray  = pEncPara->stHal.VEDU_STRM_BUFLEN;

    pstStreamInfo->StrmBufSize = pEncPara->stHal.StrmBufSize;
    pstStreamInfo->CurStrmBufSize = pEncPara->CurStrmBufSize;
    pstStreamInfo->StreamTotalByte = pEncPara->stStat.StreamTotalByte;

    pstStreamInfo->StreamMMZBuf = pEncPara->StreamMMZBuf;
    pstStreamInfo->SliceBuf = pEncPara->stHal.SliceBuf;
    pstStreamInfo->pstBuf = pEncPara->stBuf;

    pstStreamInfo->SliceIdx = pEncPara->stHal.SliceIdx;
    pstStreamInfo->TooFewBufferSkip = pEncPara->stStat.TooFewBufferSkip;
    pstStreamInfo->bFirstSlcOneFrm = pEncPara->stHal.bFirstSlcOneFrm;
#ifdef VENC_SUPPORT_JPGE
    pstStreamInfo->pstJpgMMZBuf = &pEncPara->JpgMMZBuf;
#endif
}

static HI_VOID SetStrmMngInputInfo(VeduEfl_EncPara_S* pEncPara, STRMMNG_INPUT_INFO_S* pstInputInfo)
{
    HI_U32 i = 0;

    memset(pstInputInfo, 0, sizeof(STRMMNG_INPUT_INFO_S));

    pstInputInfo->PrependSpsPpsEnable = pEncPara->PrependSpsPpsEnable;
    pstInputInfo->VpsBits = pEncPara->VpsBits;
    pstInputInfo->PpsBits = pEncPara->PpsBits;
    pstInputInfo->SpsBits = pEncPara->SpsBits;

    pstInputInfo->pVpsStream = pEncPara->VpsStream;
    pstInputInfo->pSpsStream = pEncPara->SpsStream;
    pstInputInfo->pPpsStream = pEncPara->PpsStream;

    for ( i = 0; i < 16; i++)
    {
        pstInputInfo->SliceLength[i] = pEncPara->stHal.SliceLength[i];
        pstInputInfo->SliceIsEnd[i] = pEncPara->stHal.SliceIsEnd[i];
    }

    pstInputInfo->SlcSplitEn = pEncPara->stHal.SlcSplitEn;
    pstInputInfo->Protocol = pEncPara->Protocol;
    pstInputInfo->IsIntraPic = pEncPara->stRc.IsIntraPic;
    pstInputInfo->PTS0 = pEncPara->stHal.PTS0;
    pstInputInfo->PTS1 = pEncPara->stHal.PTS1;
    pstInputInfo->TargetBits = pEncPara->stRc.TargetBits;
    pstInputInfo->GetFrameNumOK = pEncPara->stStat.GetFrameNumOK;
    pstInputInfo->VencBufFull = pEncPara->stRc.VencBufFull;
    pstInputInfo->VencPbitOverflow = pEncPara->stRc.VencPbitOverflow;
    pstInputInfo->LowDlyMod = pEncPara->stRc.LowDlyMod;
    pstInputInfo->Recode    = pEncPara->stRc.Recode;
#ifdef VENC_SUPPORT_JPGE
    pstInputInfo->pJfifHdr = pEncPara->pJfifHdr;
#endif
}

static HI_VOID GetStreamInfo(VeduEfl_EncPara_S* pEncPara, STRMMNG_STREAM_INFO_S* pstStreamInfo)
{
    pEncPara->stHal.ParaSetLen = pstStreamInfo->ParaSetLen;
    pEncPara->stHal.ParaSetRealLen = pstStreamInfo->ParaSetRealLen;

    pEncPara->StrmBufRpVirAddr = pstStreamInfo->StrmBufRpVirAddr;
    pEncPara->StrmBufWpVirAddr = pstStreamInfo->StrmBufWpVirAddr;

    pEncPara->CurStrmBufSize = pstStreamInfo->CurStrmBufSize;
    pEncPara->stStat.StreamTotalByte = pstStreamInfo->StreamTotalByte;

    pEncPara->stHal.SliceIdx = pstStreamInfo->SliceIdx;

    pEncPara->stStat.TooFewBufferSkip = pstStreamInfo->TooFewBufferSkip;
    pEncPara->stHal.bFirstSlcOneFrm = pstStreamInfo->bFirstSlcOneFrm;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
#ifdef VENC_SUPPORT_JPGE
static HI_VOID Jpge_MakeQTable(HI_S32 s32Q, HI_U8* pLumaQt, HI_U8 *pChromaQt)
{
    HI_S32 i = 0;
    HI_S32 lq = 0;
    HI_S32 cq = 0;
    HI_S32 factor = s32Q;
    HI_S32 q = s32Q;

    if (q < 1)
    {
        factor = 1;
    }
    if (q > 99)
    {
        factor = 99;
    }

    if (q < 50)
    {
        q = 5000 / factor;
    }
    else
    {
        q = 200 - factor * 2;
    }

    /* Calculate the new quantizer */
    for (i = 0; i < 64; i++)
    {
        lq = (Jpge_Yqt[i] * q + 50) / 100;
        cq = (Jpge_Cqt[i] * q + 50) / 100;

        /* Limit the quantizers to 1 <= q <= 255 */
        if (lq < 1) { lq = 1; }
        else if (lq > 255) { lq = 255; }
        pLumaQt[i] = lq;

        if (cq < 1) { cq = 1; }
        else if (cq > 255) { cq = 255; }
        pChromaQt[i] = cq;
    }
}

static HI_VOID JPGE_MakeJFIF(VeduEfl_EncPara_S* EncHandle)
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;
    /* Make JFIF header bitstream */
    HI_U32 w = pEncPara->stRc.PicWidth, t, i;
    HI_U32 h = pEncPara->stRc.PicHeight;
    STRMMNG_INPUT_INFO_S stInputInfo;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    HI_U8  dri[] = {0xff, 0xdd, 0x00, 0x04, 0x00, 0x64};
    HI_U8  sos[] = {0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00};

    for ( i = 0; i < 698; i++ )
    { pEncPara->pJfifHdr[i] = Jpge_JfifHdr[i]; }

    /* 420 422 or 444 */
    if     ( pEncPara->YuvSampleType == JPGE_YUV420 ) { pEncPara->pJfifHdr[238] = 0x22; }
    else if ( pEncPara->YuvSampleType == JPGE_YUV422 ) { pEncPara->pJfifHdr[238] = 0x21; }
    else if ( pEncPara->YuvSampleType == JPGE_YUV444 ) { pEncPara->pJfifHdr[238] = 0x11; }

    if ( pEncPara->RotationAngle == JPGE_ROTATION_90 ||
         pEncPara->RotationAngle == JPGE_ROTATION_270 )
    {
        if (pEncPara->YuvSampleType == JPGE_YUV422) /* 90 or 270 @ 422 */
        { pEncPara->pJfifHdr[238] = 0x22; }       /* change 422 to 420 */
        t = w;
        w = h;
        h = t;
    }

    /* img size */
    pEncPara->pJfifHdr[232] = h >> 8;
    pEncPara->pJfifHdr[233] = h & 0xFF;
    pEncPara->pJfifHdr[234] = w >> 8;
    pEncPara->pJfifHdr[235] = w & 0xFF;

    /* DRI & SOS */
    t = 678;

    if (pEncPara->stHal.SlcSplitEn)
    {
        dri[4] = pEncPara->stHal.SplitSize >> 8;
        dri[5] = pEncPara->stHal.SplitSize & 0xFF;

        for ( i = 0; i < 6; i++, t++ )
        { pEncPara->pJfifHdr[t] = dri[i]; }
    }

    for ( i = 0; i < 14; i++, t++ )
    { pEncPara->pJfifHdr[t] = sos[i]; }

    /* DQT */
    Jpge_MakeQTable( pEncPara->QLevel, pEncPara->pJpgeYqt, pEncPara->pJpgeCqt );

    for ( i = 0; i < 64; i++ )
    {
        t = ZigZagScan[i];
        pEncPara->pJfifHdr[t +  25] = pEncPara->pJpgeYqt[i];
        pEncPara->pJfifHdr[t +  94] = pEncPara->pJpgeCqt[i];
        pEncPara->pJfifHdr[t + 163] = pEncPara->pJpgeCqt[i];
    }

    SetStreamInfo(pEncPara, &stStreamInfo);
    SetStrmMngInputInfo(pEncPara, &stInputInfo);
    STRM_JPGEWriteHeader(pEncPara->hStrmMng, &stInputInfo, &stStreamInfo);

    return;
}

static HI_VOID JPGE_RemoveJFIF(VeduEfl_EncPara_S* EncHandle)
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;
    STRMMNG_INPUT_INFO_S stInputInfo;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStreamInfo(pEncPara, &stStreamInfo);
    SetStrmMngInputInfo(pEncPara, &stInputInfo);

    STRM_JPGERemoveHeader(pEncPara->hStrmMng, &stInputInfo, &stStreamInfo);

    return;
}
#endif

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     : flag :0 -> YUVStoreType; 1 -> YUVSampleType; 2 -> PackageSel
******************************************************************************/
static HI_U32 Convert_PIX_Format_YUVStoreType(HI_DRV_PIX_FORMAT_E oldFormat)
{
    HI_U32 Ret = HI_SUCCESS;

    switch (oldFormat)
    {
        case HI_DRV_PIX_FMT_NV61_2X1:
            Ret = VENC_STORE_SEMIPLANNAR;
            break;

        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
            Ret = VENC_STORE_SEMIPLANNAR;
            break;

        case HI_DRV_PIX_FMT_NV80:
            Ret = VENC_STORE_SEMIPLANNAR;
            break;

        case HI_DRV_PIX_FMT_NV12_411:
            Ret = VENC_STORE_SEMIPLANNAR;
            break;

        case HI_DRV_PIX_FMT_NV61:
            Ret = VENC_STORE_SEMIPLANNAR;
            break;

        case HI_DRV_PIX_FMT_NV42:
            Ret = VENC_STORE_SEMIPLANNAR;
            break;

        case HI_DRV_PIX_FMT_UYVY:
            Ret = VENC_STORE_PACKAGE;
            break;

        case HI_DRV_PIX_FMT_YUYV:
            Ret = VENC_STORE_PACKAGE;
            break;

        case HI_DRV_PIX_FMT_YVYU :
            Ret = VENC_STORE_PACKAGE;
            break;

        case HI_DRV_PIX_FMT_YUV400:
            Ret = VENC_STORE_PLANNAR;
            break;

        case HI_DRV_PIX_FMT_YUV411:
            Ret = VENC_STORE_PLANNAR;
            break;

        case HI_DRV_PIX_FMT_YUV420p:
            Ret = VENC_STORE_PLANNAR;
            break;

        case HI_DRV_PIX_FMT_YUV422_1X2:
            Ret = VENC_STORE_PLANNAR;
            break;

        case HI_DRV_PIX_FMT_YUV422_2X1:
            Ret = VENC_STORE_PLANNAR;
            break;

        case HI_DRV_PIX_FMT_YUV_444:
            Ret = VENC_STORE_PLANNAR;
            break;

        case HI_DRV_PIX_FMT_YUV410p:
            Ret = VENC_STORE_PLANNAR;
            break;

        default:
            Ret = VENC_STORE_SEMIPLANNAR;
            break;
    }

    return Ret;
}

static HI_U32 Convert_PIX_Format_YUVSampleType(HI_DRV_PIX_FORMAT_E oldFormat)
{
    HI_U32 Ret = HI_SUCCESS;

    switch (oldFormat)
    {
        case HI_DRV_PIX_FMT_NV61_2X1:
            Ret = VENC_YUV_422;
            break;

        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
            Ret = VENC_YUV_420;
            break;

        case HI_DRV_PIX_FMT_NV80:     //400
            Ret = VENC_YUV_NONE;
            break;

        case HI_DRV_PIX_FMT_NV12_411:
            Ret = VENC_YUV_NONE;
            break;

        case HI_DRV_PIX_FMT_NV61:
        case HI_DRV_PIX_FMT_NV16:
            Ret = VENC_YUV_422;
            break;

        case HI_DRV_PIX_FMT_NV42:
            Ret = VENC_YUV_444;
            break;

        case HI_DRV_PIX_FMT_UYVY:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
            Ret = VENC_YUV_422;
            break;

        case HI_DRV_PIX_FMT_YUV400:
            Ret = VENC_YUV_NONE;
            break;

        case HI_DRV_PIX_FMT_YUV411:
            Ret = VENC_YUV_NONE;
            break;

        case HI_DRV_PIX_FMT_YUV420p:
            Ret = VENC_YUV_420;
            break;

        case HI_DRV_PIX_FMT_YUV422_1X2:
            Ret = VENC_YUV_422;
            break;

        case HI_DRV_PIX_FMT_YUV422_2X1:
            Ret = VENC_YUV_422;
            break;

        case HI_DRV_PIX_FMT_YUV_444:
            Ret = VENC_YUV_444;
            break;

        case HI_DRV_PIX_FMT_YUV410p:
            Ret = VENC_YUV_NONE;
            break;

        default:
            Ret = VENC_YUV_NONE;
            break;
    }

    return Ret;
}

static HI_U32 Convert_PIX_Format_PackageSel(HI_DRV_PIX_FORMAT_E oldFormat)
{
    HI_U32 Ret = HI_SUCCESS;

    switch (oldFormat)
    {
        case HI_DRV_PIX_FMT_NV61_2X1:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_NV21:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_NV12:
            Ret = VENC_U_V;
            break;

        case HI_DRV_PIX_FMT_NV80:     //400
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_NV12_411:
            Ret = VENC_U_V;
            break;

        case HI_DRV_PIX_FMT_NV61:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_NV16:
            Ret = VENC_U_V;
            break;

        case HI_DRV_PIX_FMT_NV42:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_UYVY:
            Ret = VENC_PACKAGE_UY0VY1;
            break;

        case HI_DRV_PIX_FMT_YUYV:
            Ret = VENC_PACKAGE_Y0UY1V;
            break;

        case HI_DRV_PIX_FMT_YVYU :
            Ret = VENC_PACKAGE_Y0VY1U;
            break;

        case HI_DRV_PIX_FMT_YUV400:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_YUV411:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_YUV420p:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_YUV422_1X2:
            Ret = VENC_U_V;
            break;

        case HI_DRV_PIX_FMT_YUV422_2X1:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_YUV_444:
            Ret = VENC_V_U;
            break;

        case HI_DRV_PIX_FMT_YUV410p:
            Ret = VENC_V_U;
            break;

        default:
            Ret = VENC_YUV_NONE;
            break;
    }

    return Ret;
}

static HI_U32 Convert_PIX_Format_FrameInfo(HI_DRV_PIX_FORMAT_E oldFormat)
{
    HI_U32 Ret = HI_SUCCESS;

    switch (oldFormat)
    {
        case HI_DRV_PIX_FMT_NV21:
            Ret = VENC_SEMIPLANNAR_420_VU;
            break;

        case HI_DRV_PIX_FMT_NV12:
            Ret = VENC_SEMIPLANNAR_420_UV;
            break;

        case HI_DRV_PIX_FMT_UYVY:
            Ret = VENC_PACKAGE_422_UYVY;
            break;

        case HI_DRV_PIX_FMT_YUYV:
            Ret = VENC_PACKAGE_422_YUYV;
            break;

        case HI_DRV_PIX_FMT_YVYU :
            Ret = VENC_PACKAGE_422_YVYU;
            break;

        case HI_DRV_PIX_FMT_YUV420p:
            Ret = VENC_PLANNAR_420;
            break;

        case HI_DRV_PIX_FMT_YUV422_1X2:
            Ret = VENC_PLANNAR_422;
            break;

        case HI_DRV_PIX_FMT_YUV422_2X1:
            Ret = VENC_PLANNAR_422;
            break;

        default:
            Ret = VENC_UNKNOW;
            break;
    }

    return Ret;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     : flag :0 -> YUVStoreType; 1 -> YUVSampleType; 2 -> PackageSel
******************************************************************************/
static HI_U32 Convert_PIX_Format(HI_DRV_PIX_FORMAT_E oldFormat,HI_U32 flag)
{
   HI_U32 Ret = HI_SUCCESS;
   if(0 == flag) /*YUVStoreType*/
   {
        Ret = Convert_PIX_Format_YUVStoreType(oldFormat);
   }
   else if (1 == flag) /*YUVSampleType*/
   {
        Ret = Convert_PIX_Format_YUVSampleType(oldFormat);
   }
   else if(2 == flag) /*PackageSel*/
   {
        Ret = Convert_PIX_Format_PackageSel(oldFormat);
   }
   else if (3 == flag)   /*for proc FrameInfo*/
   {
     Ret = Convert_PIX_Format_FrameInfo(oldFormat);
   }
   else
   {
      Ret = HI_FALSE;
   }

   return Ret;
}

static HI_S32 QuickEncode_Process(VeduEfl_EncPara_S* EncHandle, HI_HANDLE GetImgHhd)         //成功取帧返回 HI_SUCCESS,连一次都取不成功返回HI_FAILURE
{
    HI_BOOL bLastFrame = HI_FALSE;
    HI_DRV_VIDEO_FRAME_S stImage_temp;
    VeduEfl_EncPara_S *pEncPara;
    HI_U32 u32VeChn;
    pEncPara = EncHandle;

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);

    pEncPara->stStat.GetFrameNumTry++;

    if ( HI_SUCCESS == (pEncPara->stSrcInfo.pfGetImage)(GetImgHhd, &pEncPara->stImage))
    {
        pEncPara->stStat.GetFrameNumOK++;
        while (!bLastFrame)
        {
            pEncPara->stStat.GetFrameNumTry++;

            if ( HI_SUCCESS == (pEncPara->stSrcInfo.pfGetImage)(GetImgHhd, &stImage_temp))
            {
                pEncPara->stStat.GetFrameNumOK++;

                pEncPara->stStat.PutFrameNumTry++;
                (*pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &pEncPara->stImage);
                pEncPara->stStat.PutFrameNumOK++;
                pEncPara->stStat.QuickEncodeSkip++;
                pEncPara->stImage = stImage_temp;
            }
            else
            {
                bLastFrame = HI_TRUE;
            }
        }
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID VENC_DRV_EflWakeUpThread( HI_VOID)
{
    VENC_DRV_OsalGiveEvent(&g_VENC_Event);

    return ;
}

HI_VOID VENC_DRV_EflSortPriority(HI_VOID)
{
   HI_U32 i,j;
   for( i = 0; i < HI_VENC_MAX_CHN - 1; i++)
   {
      for(j =  HI_VENC_MAX_CHN - 1; j > i; j--)
      {
          if(PriorityTab[1][j]>PriorityTab[1][j-1])
          {
             HI_U32 temp0 = PriorityTab[0][j];
             HI_U32 temp1 = PriorityTab[1][j];
             PriorityTab[0][j]   = PriorityTab[0][j-1];
             PriorityTab[1][j]   = PriorityTab[1][j-1];
             PriorityTab[0][j-1] = temp0;
             PriorityTab[1][j-1] = temp1;
          }
      }
   }
}

HI_S32 VENC_DRV_EflSortPriority_2(HI_S8 priority)
{
   HI_U32 i;
   HI_U32 cnt = 0;
   HI_U32 id  = HI_VENC_MAX_CHN-1;
   HI_BOOL bFind = 0;

   for (i = 0; i < HI_VENC_MAX_CHN; i++)
   {
      if ((priority == PriorityTab[1][i]) && (INVAILD_CHN_FLAG != PriorityTab[0][i]))
      {
         if (!bFind)
         {
            id = i;
            bFind = 1;
         }
         cnt++;
      }
   }

   if (!bFind)
   {
      HI_WARN_VENC("can't fine the channel match with priority(%d)\n",priority);
      return HI_FAILURE;
   }

   if (1 == cnt || (id>=HI_VENC_MAX_CHN-1))
   {
      return HI_SUCCESS;
   }

   for(i = 0; (i<(cnt-1)) && (id<(HI_VENC_MAX_CHN-1)); i++,id++)
   {
       HI_U32 temp0 = PriorityTab[0][id];
       HI_U32 temp1 = PriorityTab[1][id];
       PriorityTab[0][id]   = PriorityTab[0][id+1];
       PriorityTab[1][id]   = PriorityTab[1][id+1];
       PriorityTab[0][id+1] = temp0;
       PriorityTab[1][id+1] = temp1;
   }

   return HI_SUCCESS;
}

HI_VOID VENC_DRV_EflSetRegCfgData(VENC_HAL_CFG_S *pRegCfg, VeduEfl_EncPara_S *pEncPara)
{
    HI_U32 i = 0;
    /*get CtrlCfg default info*/
    pRegCfg->CtrlCfg.Protocol = pEncPara->Protocol;
    pRegCfg->CtrlCfg.Profile  = pEncPara->H264HpEn;
    pRegCfg->CtrlCfg.EncWidth = pEncPara->stRc.PicWidth;
    pRegCfg->CtrlCfg.EncHeight = pEncPara->stRc.PicHeight;
    pRegCfg->CtrlCfg.SlcSplitEn = pEncPara->stHal.SlcSplitEn;   /*0: not enable 1: enable*/
    pRegCfg->CtrlCfg.SplitSize = pEncPara->stHal.SplitSize;
    pRegCfg->CtrlCfg.CscMode  = 0;
    pRegCfg->CtrlCfg.SecureEn = 0;
    pRegCfg->CtrlCfg.LowDlyMode = pEncPara->stRc.LowDlyMod;
    pRegCfg->CtrlCfg.TimeOutEn = 3;
    pRegCfg->CtrlCfg.RegConfigMode = 1;/*0: cfg mode 1: ddr mode*/

    if (pEncPara->stRc.IsIntraPic)
    {
        if ((pEncPara->PrependSpsPpsEnable == HI_TRUE) || (pEncPara->stStat.GetFrameNumOK == 1))
        {
            pRegCfg->CtrlCfg.ParameterSetEn = 1;
        }
        else
        {
            pRegCfg->CtrlCfg.ParameterSetEn = 0;
        }
    }

    /*get BufCfg default info*/
    pRegCfg->BufCfg.StoreFmt = pEncPara->stHal.YuvStoreType;           /* 0, semiplannar; 1, package; 2,planer */
    pRegCfg->BufCfg.PackageSel = pEncPara->stHal.PackageSel;
    pRegCfg->BufCfg.SrcYAddr = pEncPara->stHal.SrcYAddr;
    pRegCfg->BufCfg.SrcCAddr = pEncPara->stHal.SrcCAddr;
    pRegCfg->BufCfg.SrcVAddr = pEncPara->stHal.SrcVAddr;                  //just for input of planner
    pRegCfg->BufCfg.SStrideY = pEncPara->stHal.SStrideY;
    pRegCfg->BufCfg.SStrideC = pEncPara->stHal.SStrideC;

    pRegCfg->BufCfg.RcnYAddr[0] = pEncPara->stHal.RcnYAddr[0];
    pRegCfg->BufCfg.RcnYAddr[1] = pEncPara->stHal.RcnYAddr[1];
    pRegCfg->BufCfg.RcnCAddr[0] = pEncPara->stHal.RcnCAddr[0];
    pRegCfg->BufCfg.RcnCAddr[1] = pEncPara->stHal.RcnCAddr[1];

    pRegCfg->BufCfg.RStrideY = pEncPara->stHal.RStrideY;
    pRegCfg->BufCfg.RStrideC = pEncPara->stHal.RStrideC;
    pRegCfg->BufCfg.RcnHYAddr[0] = pEncPara->stHal.RcnYAddr_head[0];
    pRegCfg->BufCfg.RcnHYAddr[1] = pEncPara->stHal.RcnYAddr_head[1];
    pRegCfg->BufCfg.RcnHCAddr[0] = pEncPara->stHal.RcnCAddr_head[0];
    pRegCfg->BufCfg.RcnHCAddr[1] = pEncPara->stHal.RcnCAddr_head[1];

    pRegCfg->BufCfg.RHStrideY = pEncPara->stHal.RHStrideY;
    pRegCfg->BufCfg.RHStrideC = pEncPara->stHal.RHStrideC;
    pRegCfg->BufCfg.RcnIdx    = pEncPara->stRc.RcnIdx;             /* 0 or 1, idx for rcn, !idx for ref */

    pRegCfg->BufCfg.TmvAddr[0] = pEncPara->stHal.TmvAddr[0];
    pRegCfg->BufCfg.TmvAddr[1] = pEncPara->stHal.TmvAddr[1];
    pRegCfg->BufCfg.PmeAddr[0] = pEncPara->stHal.PmeAddr[0];
    pRegCfg->BufCfg.PmeAddr[1] = pEncPara->stHal.PmeAddr[1];
    pRegCfg->BufCfg.PmeInfoAddr[0] = pEncPara->stHal.PmeInfoAddr[0];
    pRegCfg->BufCfg.PmeInfoAddr[1] = pEncPara->stHal.PmeInfoAddr[1];
    pRegCfg->BufCfg.PmeInfoAddr[2] = pEncPara->stHal.PmeInfoAddr[2];

    pRegCfg->BufCfg.PmeInfoIdx = pEncPara->stRc.PmeInfoIdx;
    pRegCfg->BufCfg.PmvPoc[0] = pEncPara->stHal.BaseCfg.pmv_poc[0];
    pRegCfg->BufCfg.PmvPoc[1] = pEncPara->stHal.BaseCfg.pmv_poc[1];
    pRegCfg->BufCfg.PmvPoc[2] = pEncPara->stHal.BaseCfg.pmv_poc[2];
    pRegCfg->BufCfg.PmvPoc[3] = pEncPara->stHal.BaseCfg.pmv_poc[3];
    pRegCfg->BufCfg.PmvPoc[4] = pEncPara->stHal.BaseCfg.pmv_poc[4];
    pRegCfg->BufCfg.PmvPoc[5] = pEncPara->stHal.BaseCfg.pmv_poc[5];

    pRegCfg->BufCfg.TunlCellAddr = pEncPara->stHal.tunlcellAddr;

    if (VeduIpCtx.IsChipIDV500R001 == HI_TRUE)
    {
        for (i = 0; i < 16; i++)
        {
            pRegCfg->BufCfg.StrmBufAddr[i] = pEncPara->stHal.VEDU_STRM_ADDR[i];//96mv200
            pRegCfg->BufCfg.StrmBufSize[i] = pEncPara->stHal.VEDU_STRM_BUFLEN[i];
        }

        for (i = 0; i < 48; i++)
        {
            pRegCfg->BufCfg.ParaSetReg[i] = pEncPara->stHal.ParaSetArray[i];
        }

        pRegCfg->BufCfg.ParaSetAddr = pEncPara->stHal.ParaSetPhyAddr;
        pRegCfg->BufCfg.ParaSetBufSize = pEncPara->stHal.ParaSetLen;
    }
    else
    {
        pRegCfg->BufCfg.StrmBufAddr[0] = pEncPara->stHal.StrmBufAddr;//98mv200
        pRegCfg->BufCfg.StrmBufSize[0] = pEncPara->stHal.StrmBufSize;
    }

    pRegCfg->BufCfg.StrmBufRpAddr = pEncPara->stHal.StrmBufRpAddr; /* phy addr for hardware */
    pRegCfg->BufCfg.StrmBufWpAddr = pEncPara->stHal.StrmBufWpAddr;
   /*get RcCfg default info*/
    pRegCfg->RcCfg.IntraPic = pEncPara->stRc.IsIntraPic;
    pRegCfg->RcCfg.TargetBits = pEncPara->stRc.TargetBits;         /* targetBits of each frame */
    pRegCfg->RcCfg.StartQp = pEncPara->stRc.StartQP;
    pRegCfg->RcCfg.MinQp = pEncPara->stRc.MinQp;
    pRegCfg->RcCfg.MaxQp = pEncPara->stRc.MaxQp;
    pRegCfg->RcCfg.IQpDelta = pEncPara->stRc.IQpDelta;
    pRegCfg->RcCfg.PQpDelta = pEncPara->stRc.PQpDelta;

   /*get SmmuCfg default info*/
    pRegCfg->SmmuCfg.SmmuNsPageBaseAddr = pEncPara->stHal.u32SmmuPageBaseAddr;
    pRegCfg->SmmuCfg.SmmuNsErrWriteAddr = pEncPara->stHal.u32SmmuErrWriteAddr;
    pRegCfg->SmmuCfg.SmmuNsErrReadAddr  = pEncPara->stHal.u32SmmuErrReadAddr;

   /*get StreamCfg info*/
    pRegCfg->StreamCfg.SlcHdrStream[0] = pEncPara->stHal.SlcHdrStream[0];
    pRegCfg->StreamCfg.SlcHdrStream[1] = pEncPara->stHal.SlcHdrStream[1];
    pRegCfg->StreamCfg.SlcHdrStream[2] = pEncPara->stHal.SlcHdrStream[2];
    pRegCfg->StreamCfg.SlcHdrStream[3] = pEncPara->stHal.SlcHdrStream[3];

    pRegCfg->StreamCfg.ReorderStream[0] = pEncPara->stHal.ReorderStream[0];
    pRegCfg->StreamCfg.ReorderStream[1] = pEncPara->stHal.ReorderStream[1];
    pRegCfg->StreamCfg.MarkingStream[0] = pEncPara->stHal.MarkingStream[0];
    pRegCfg->StreamCfg.MarkingStream[1] = pEncPara->stHal.MarkingStream[1];

    if (pRegCfg->CtrlCfg.Protocol == VEDU_H264)
    {
        pRegCfg->StreamCfg.SlcHdrBits[0] = pEncPara->stHal.SlcHdrBits;         /* 8bit_0 | mark | reorder | slchdr */
    }
    else
    {
        pRegCfg->StreamCfg.SlcHdrBits[0] = pEncPara->stHal.slchdr_size_part1;         /* 8bit_0 | mark | reorder | slchdr */
        pRegCfg->StreamCfg.SlcHdrBits[1] = pEncPara->stHal.slchdr_size_part2;         /* 8bit_0 | mark | reorder | slchdr */
        pRegCfg->StreamCfg.slchdr_part1  = pEncPara->stHal.slchdr_part1;
        for (i = 0; i < 8; i++)
        {
            pRegCfg->StreamCfg.CABAC_SLCHDR_PART2_SEG[i] = pEncPara->stHal.CABAC_SLCHDR_PART2_SEG[i];
        }
    }
    pRegCfg->ExtCfg.PTS0 = pEncPara->stHal.PTS0;
    pRegCfg->ExtCfg.PTS1 = pEncPara->stHal.PTS1;
    pRegCfg->ExtCfg.DdrRegCfgPhyAddr = pEncPara->stHal.DdrRegCfgBuf.u32StartPhyAddr;
    pRegCfg->ExtCfg.DdrRegCfgVirAddr = (VIRT_ADDR)pEncPara->stHal.DdrRegCfgBuf.pu8StartVirAddr;
}

HI_S32 VENC_DRV_EflCfgRegVenc(VeduEfl_EncPara_S* EncHandle)
{
    VENC_HAL_CFG_S pRegCfg;
    VeduEfl_EncPara_S* pEncPara = EncHandle;

    memset(&pRegCfg, 0, sizeof(VENC_HAL_CFG_S));
    VENC_DRV_BoardInit();
    VENC_DRV_EflSetRegCfgData(&pRegCfg, pEncPara);
    VENC_HAL_CfgReg(&pRegCfg);

    return HI_SUCCESS;
}

HI_VOID VENC_DRV_EflGetReadBackData(VENC_HAL_READ_S* pReadBack, Vedu_Hal_S* pstHal, VeduEfl_Rc_S* pstRc)
{
    HI_U32 i = 0;

    pstHal->VencEndOfPic = pReadBack->VencEndOfPic;
    pstRc->VencBufFull  = pReadBack->VencBufFull;
    pstRc->VencPbitOverflow = pReadBack->VencPbitOverflow;
    pstHal->MeanQP = pReadBack->MeanQP;
    pstRc->PicBits = pReadBack->PicBits;
    pstRc->NumIMBCurFrm = pReadBack->NumIMBCurFrm;

    for (i = 0; i < 16; i++)
    {
        pstHal->SliceLength[i] = pReadBack->SliceLength[i];
        pstHal->SliceIsEnd[i]  = pReadBack->SliceIsEnd[i];
    }
}

static HI_VOID MakeSliceHeader(VeduEfl_EncPara_S *pEncPara)
{
    if (pEncPara->Protocol == VEDU_H264)
    {
        VeduEfl_H264e_SlcHdr_S SlcHdr;

        pEncPara->stRc.H264FrmNum = pEncPara->stRc.IsIntraPic ? 0 : pEncPara->stRc.H264FrmNum  + 1;
        SlcHdr.frame_num  = pEncPara->stRc.H264FrmNum ;
        SlcHdr.slice_type = pEncPara->stRc.IsIntraPic ? 2 : 0;
        SlcHdr.NumRefIndex= pEncPara->NumRefIndex;
        pEncPara->stHal.SlcHdrBits = H264e_MakeSlcHdr(pEncPara->stHal.SlcHdrStream,
                                                pEncPara->stHal.ReorderStream,
                                                pEncPara->stHal.MarkingStream, &SlcHdr);
    }
    else if(pEncPara->Protocol == VEDU_H265)
    {
        VeduEfl_H265e_SlcHdr_S  SlcHdr;

        pEncPara->stRc.H264FrmNum  = pEncPara->stRc.IsIntraPic ? 0 : pEncPara->stRc.H264FrmNum  + 1;
        SlcHdr.frame_num     = pEncPara->stRc.H264FrmNum ;
        SlcHdr.eSliceType    = pEncPara->stRc.IsIntraPic ? 2 : 1;

        SlcHdr.uiPocLsb = SlcHdr.frame_num ;

        SlcHdr.bSpsTemporalMvpEnableFlag    = pEncPara->stHal.BaseCfg.tmv_en;

        SlcHdr.bSAOEnabledFlag              = pEncPara->stHal.BaseCfg.vcpi_sao_luma || pEncPara->stHal.BaseCfg.vcpi_sao_chroma;
        SlcHdr.bSliceSaoLuma                = pEncPara->stHal.BaseCfg.vcpi_sao_luma;
        SlcHdr.bSliceSaoChroma              = pEncPara->stHal.BaseCfg.vcpi_sao_chroma;

        SlcHdr.iSliceQPDelta = pEncPara->stRc.StartQP - 26;
        SlcHdr.bDBFilterCtlPresent = 1;
        SlcHdr.bDBFilterOverrideEnabled = 1;

        SlcHdr.bFirstSliceInPic = 1;

        SlcHdr.bSliceHeaderDisableDF = 0;
        SlcHdr.bDFOverrideFlag = 1;

        SlcHdr.bSliceLFAcrossSlice = 1;

        SlcHdr.five_minus_max_num_merge_cand = 5 - pEncPara->stHal.BaseCfg.max_num_mergecand;
        SlcHdr.num_ref_idx_l0_active_minus1  = 0;
        SlcHdr.collocated_from_l0_flag       = 1;

        pEncPara->stHal.SlcHdrBits = H265e_MakeSliceHead(pEncPara, &SlcHdr);
    }
}

static HI_VOID GetHalInfo(VeduEfl_EncPara_S *pEncPara, VeduEfl_EncIn_S *pEncIn)
{
    pEncPara->stHal.SrcYAddr   = pEncIn->BusViY;
    pEncPara->stHal.SrcCAddr   = pEncIn->BusViC;
    pEncPara->stHal.SrcVAddr   = pEncIn->BusViV;
    pEncPara->stHal.SStrideY = pEncIn->ViYStride;
    pEncPara->stHal.SStrideC = pEncIn->ViCStride;

    if (pEncPara->stRc.LowDlyMod)
    {
        pEncPara->stHal.tunlcellAddr = pEncIn->TunlCellAddr;
    }

    pEncPara->stHal.PTS0 = pEncIn->PTS0;
    pEncPara->stHal.PTS1 = pEncIn->PTS1;

    if (pEncPara->Protocol == VEDU_H265)
    {
        // pmv_poc
        if (pEncPara->stRc.H264FrmNum % pEncPara->stRc.Gop == 0)
        {
            pEncPara->stHal.BaseCfg.pmv_poc[0] = 0;
            pEncPara->stHal.BaseCfg.pmv_poc[1] = 0;
        }
        else
        {
            pEncPara->stHal.BaseCfg.pmv_poc[0] = pEncPara->stRc.H264FrmNum;
            pEncPara->stHal.BaseCfg.pmv_poc[1] = pEncPara->stRc.H264FrmNum - 1;
        }

        pEncPara->stHal.BaseCfg.pmv_poc[3] = pEncPara->stHal.BaseCfg.pmv_poc[1] ;

        if (pEncPara->stRc.H264FrmNum % pEncPara->stRc.Gop > 1)
        {
            pEncPara->stHal.BaseCfg.pmv_poc[4] = pEncPara->stHal.BaseCfg.pmv_poc[3] - 1;
        }
    }

    pEncPara->stRc.PmeInfoIdx = (pEncPara->stRc.PmeInfoIdx + 1) % 3;
    pEncPara->stRc.RcnIdx = !pEncPara->stRc.RcnIdx;
    pEncPara->stHal.RStrideY = pEncIn->RStrideY;
    pEncPara->stHal.RStrideC = pEncIn->RStrideC;
}

static HI_S32 GetFrameWriteBuf(VeduEfl_EncPara_S *pEncPara)
{
    HI_U32 ret = HI_SUCCESS;
    STRMMNG_INPUT_INFO_S stInputInfo;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStreamInfo(pEncPara, &stStreamInfo);
    SetStrmMngInputInfo(pEncPara, &stInputInfo);

    ret = STRM_GetWriteBuffer(pEncPara->hStrmMng, &stInputInfo, &stStreamInfo);
    if (ret != HI_SUCCESS)
    {
        return ret;
    }

    GetStreamInfo(pEncPara, &stStreamInfo);

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflStartOneFrameVenc(VeduEfl_EncPara_S *EncHandle, VeduEfl_EncIn_S *pEncIn )
{
    HI_U32 ret = HI_SUCCESS;
    VeduEfl_EncPara_S *pEncPara  = EncHandle;

    if (pEncPara->bNotEnoughBuf != HI_TRUE)
    {
        if (!pEncPara->stRc.VencBufFull && !pEncPara->stRc.VencPbitOverflow)
        {
            VENC_DRV_RcOpenOneFrm(&pEncPara->stRc);
        }


        MakeSliceHeader(pEncPara);
        GetHalInfo(pEncPara, pEncIn);
    }

    ret = GetFrameWriteBuf(pEncPara);

    pEncPara->bNotEnoughBuf = (ret == HI_SUCCESS) ? HI_FALSE : HI_TRUE;

    return ret;
}

static HI_VOID PutFrameWriteBuffer(VeduEfl_EncPara_S *pEncPara)
{
    STRMMNG_INPUT_INFO_S stInputInfo;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStrmMngInputInfo(pEncPara, &stInputInfo);
    SetStreamInfo(pEncPara, &stStreamInfo);

    STRM_PutWriteBuffer(pEncPara->hStrmMng, &stInputInfo, &stStreamInfo);

    pEncPara->stStat.TooFewBufferSkip = stStreamInfo.TooFewBufferSkip;
    pEncPara->stHal.SliceIdx = stStreamInfo.SliceIdx;
}

HI_S32 VENC_DRV_EflEndOneFrameVenc(VeduEfl_EncPara_S *EncHandle)
{
    VeduEfl_EncPara_S *pEncPara  = EncHandle;

    PutFrameWriteBuffer(pEncPara);

    pEncPara->stHal.SliceIdx = 0;

    VENC_DRV_RcCloseOneFrm(&pEncPara->stRc, &pEncPara->stBitsFifo, &pEncPara->TrCount, &pEncPara->InterFrmCnt);

    return HI_SUCCESS;
}

#ifdef VENC_SUPPORT_JPGE
static HI_VOID PutJPGEWriteBuffer(VeduEfl_EncPara_S *pEncPara)
{
    STRMMNG_INPUT_INFO_S stInputInfo;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    SetStrmMngInputInfo(pEncPara, &stInputInfo);
    SetStreamInfo(pEncPara, &stStreamInfo);

    STRM_PutJPGEWriteBuffer(pEncPara->hStrmMng, &stInputInfo, &stStreamInfo);

    pEncPara->stStat.TooFewBufferSkip = stStreamInfo.TooFewBufferSkip;
}

HI_S32 VENC_DRV_EflEndOneFrameJpge( VeduEfl_EncPara_S *EncHandle)
{
    VeduEfl_EncPara_S *pEncPara  = EncHandle;

    PutJPGEWriteBuffer(pEncPara);

    return HI_SUCCESS;
}
#endif

HI_S32 VENC_DRV_EflEndOneSliceVenc(VeduEfl_EncPara_S* EncHandle)
{
    VeduEfl_EncPara_S* pEncPara = EncHandle;

    PutFrameWriteBuffer(pEncPara);

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflFlushStrmHeader( VeduEfl_EncPara_S  *pEncPara )
{
    D_VENC_CHECK_PTR(pEncPara);

    /* make sps & pps & VOL stream */
    if (pEncPara->Protocol == VEDU_H264)
    {
        VeduEfl_H264e_SPS_S sps;
        VeduEfl_H264e_PPS_S pps;

        switch(pEncPara->H264HpEn)
        {
           case VEDU_H264_BASELINE_PROFILE:
               sps.ProfileIDC = 66;
               break;
           case VEDU_H264_MAIN_PROFILE:
               sps.ProfileIDC = 77;
               break;
           case VEDU_H264_HIGH_PROFILE:
               sps.ProfileIDC = 100;
               break;
           default:
               sps.ProfileIDC = 100;
               break;
        }

        sps.FrameWidthInMb  = (pEncPara->stRc.PicWidth + 15) >> 4;
        sps.FrameHeightInMb = (pEncPara->stRc.PicHeight+ 15) >> 4;
        sps.FrameCropLeft = 0;
        sps.FrameCropTop    = 0;
        sps.FrameCropRight  = (sps.FrameWidthInMb * 16 - pEncPara->stRc.PicWidth) >> 1;
        sps.FrameCropBottom = (sps.FrameHeightInMb * 16 - pEncPara->stRc.PicHeight) >> 1;

        pps.ChrQpOffset = pEncPara->ChrQpOffset;
        pps.ConstIntra  = pEncPara->ConstIntra;
        pps.H264HpEn    = (pEncPara->H264HpEn == VEDU_H264_HIGH_PROFILE)? 1 : 0;
        pps.H264CabacEn = pEncPara->H264CabacEn;
        pps.pScale8x8   = pEncPara->Scale8x8;

        pEncPara->SpsBits = H264e_MakeSPS(pEncPara->SpsStream, &sps);
        pEncPara->PpsBits = H264e_MakePPS(pEncPara->PpsStream, &pps);
    }
    else if (pEncPara->Protocol == VEDU_H265)
    {
        VeduEfl_H265e_VPS_S vps;
        VeduEfl_H265e_SPS_S sps;
        VeduEfl_H265e_PPS_S pps;
        HI_U32 insert;

        vps.general_interlaced_source_flag = !pEncPara->IsProgressive;
        vps.general_progressive_source_flag = pEncPara->IsProgressive;
        sps.uiPicWidthInLumaSamples  = ((pEncPara->stRc.PicWidth  + 7) >> 3) << 3;
        sps.uiPicHeightInLumaSamples = ((pEncPara->stRc.PicHeight + 7) >> 3) << 3;
        sps.uiPicCropLeftOffset = 0 ;
        sps.uiPicCropRightOffset = (sps.uiPicWidthInLumaSamples  - pEncPara->stRc.PicWidth) >> 1;
        sps.uiPicCropTopOffset = 0 ;
        sps.uiPicCropBottomOffset = (sps.uiPicHeightInLumaSamples - pEncPara->stRc.PicHeight) >> 1;
        sps.bPicCroppingFlag  = sps.uiPicCropLeftOffset  || sps.uiPicCropTopOffset |sps.uiPicCropRightOffset || sps.uiPicCropBottomOffset;

        sps.bSAOEnabledFlag = 0;
        sps.sps_temporal_mvp_enable_flag = pEncPara->stHal.BaseCfg.tmv_en;
        sps.bPcmEnable = pEncPara->stHal.BaseCfg.vcpi_ipcm_en;
        sps.iPcmLog2MaxSize = 3 ;
        sps.iPcmLog2MinSize = 3 ;

        sps.bStrongIntraSmoothingFlag = 0;
        sps.ProfileIDC = 100;

        pps.bCUQpDeltaEnable = 1;
        pps.iCbQpOffset = 0;
        pps.iCrQpOffset = 0;

        pps.bPicDisableDBFilter = 1;

        pEncPara->VpsBits = H265e_MakeVPS(pEncPara->VpsStream, &vps);
        pEncPara->SpsBits = H265e_MakeSPS(pEncPara->SpsStream, &sps);
        pEncPara->PpsBits = H265e_MakePPS(pEncPara->PpsStream, &pps);

        memcpy(pEncPara->tempVpsStream, pEncPara->VpsStream, sizeof(pEncPara->tempVpsStream));
        memcpy(pEncPara->tempSpsStream, pEncPara->SpsStream, sizeof(pEncPara->tempSpsStream));
        memcpy(pEncPara->tempPpsStream, pEncPara->PpsStream, sizeof(pEncPara->tempPpsStream));
        memset(pEncPara->VpsStream, 0, sizeof(pEncPara->VpsStream));
        memset(pEncPara->SpsStream, 0, sizeof(pEncPara->SpsStream));
        memset(pEncPara->PpsStream, 0, sizeof(pEncPara->PpsStream));

        insert = CheckPreventionThreeByte(pEncPara->tempVpsStream, pEncPara->VpsBits, pEncPara->VpsStream);
        pEncPara->VpsBits = pEncPara->VpsBits + insert*8;
        insert = CheckPreventionThreeByte(pEncPara->tempSpsStream, pEncPara->SpsBits, pEncPara->SpsStream);
        pEncPara->SpsBits = pEncPara->SpsBits + insert*8;
        insert = CheckPreventionThreeByte(pEncPara->tempPpsStream, pEncPara->PpsBits, pEncPara->PpsStream);
        pEncPara->PpsBits = pEncPara->PpsBits + insert*8;
    }

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflGetLumaSize(VeduEfl_EncCfg_S *pEncCfg, HI_U32 *pLumaSize)
{
    HI_U32 LumaSize = 0;

    switch (pEncCfg->CapLevel)
    {
        case VEDU_CAP_LEVEL_QCIF:
            LumaSize = 144 * D_VENC_ALIGN_UP(176 , VEDU_MMZ_ALIGN);
            break;

        case VEDU_CAP_LEVEL_CIF:
            LumaSize = 288 * D_VENC_ALIGN_UP(352 , VEDU_MMZ_ALIGN);
            break;

        case VEDU_CAP_LEVEL_D1:
            LumaSize = 576 * D_VENC_ALIGN_UP(720 , VEDU_MMZ_ALIGN);
            break;

        case VEDU_CAP_LEVEL_720P:
            LumaSize = 720 * D_VENC_ALIGN_UP(1280 , VEDU_MMZ_ALIGN);
            break;

        case VEDU_CAP_LEVEL_1080P:
            LumaSize = 1088 * D_VENC_ALIGN_UP(1920 , VEDU_MMZ_ALIGN);
            break;

        default:
            return HI_ERR_VENC_INVALID_PARA;
            break;
    }

    *pLumaSize = LumaSize;

    return HI_SUCCESS;
}

HI_U32 VENC_DRV_EflGetFrameStride(VeduEfl_EncCfg_S *pEncCfg)
{
    HI_U32 Stride = 0;

    if (pEncCfg->Protocol == VEDU_H264)
    {
        Stride = (pEncCfg->FrameWidth + 255) / 256 * 32;
    }
    else
    {
        Stride = (pEncCfg->FrameWidth + 63) / 64 * 32;
    }

    return Stride;
}

HI_VOID VENC_DRV_EflInitCfg(VeduEfl_EncPara_S *pEncPara, VeduEfl_EncCfg_S *pEncCfg)
{
    /* get channel para */
    pEncPara->stHal.RHStrideY = VENC_DRV_EflGetFrameStride(pEncCfg);
    pEncPara->stHal.RHStrideC = VENC_DRV_EflGetFrameStride(pEncCfg);

    pEncPara->stHal.StrmBufAddr   = pEncPara->StreamMMZBuf.u32StartPhyAddr  + VEDU_MMZ_ALIGN;
    pEncPara->stHal.StrmBufSize   = pEncCfg->streamBufSize - VEDU_MMZ_ALIGN;

    pEncPara->Vir2BusOffset = pEncPara->StreamMMZBuf.u32Size;//for jpeg

    pEncPara->Protocol  = pEncCfg->Protocol;
    pEncPara->IsProgressive = 1;
    pEncPara->stRc.PicWidth  = pEncCfg->FrameWidth;
    pEncPara->stRc.PicHeight = pEncCfg->FrameHeight;

    pEncPara->RotationAngle = VEDU_ROTATION_0;

    pEncPara->stHal.SlcSplitEn = pEncCfg->SlcSplitEn;
    pEncPara->QuickEncode = pEncCfg->QuickEncode;
#ifdef VENC_SUPPORT_JPGE
    pEncPara->QLevel     = pEncCfg->QLevel;
    pEncPara->WaitingIsr_jpge = 0;
#endif
    pEncPara->Priority   = pEncCfg->Priority;
    pEncPara->stRc.Gop        = pEncCfg->Gop;
    pEncPara->WaitingIsr = 0;
    pEncPara->OMXChn     = pEncCfg->bOMXChn;
    pEncPara->ICatchEnable = pEncCfg->bAutoRequestIfrm;
    pEncPara->PrependSpsPpsEnable = pEncCfg->bPrependSpsPps;
    pEncPara->AutoSkipFrameEn = pEncCfg->bRCSkipFrmEn;
    pEncPara->DriftRcSkipThr  = pEncCfg->DriftRCThr;

    /* other */
    pEncPara->bNeverEnc   = HI_TRUE;
    pEncPara->stHal.SlcSplitMod = 1;                                          //just choose the mb line Mode
    pEncPara->NumRefIndex = 0;

    if (pEncPara->Protocol == VEDU_H264)
    {
        pEncPara->H264HpEn    = pEncCfg->Profile;
        pEncPara->H264CabacEn = (pEncCfg->Profile == VEDU_H264_BASELINE_PROFILE) ? 0 : 1;
    }

    pEncPara->stHal.BaseCfg.vcpi_ipcm_en      = 1 ;

    pEncPara->stHal.BaseCfg.vcpi_sao_chroma   = 1 ;
    pEncPara->stHal.BaseCfg.vcpi_sao_luma     = 1 ;

    pEncPara->stHal.BaseCfg.max_num_mergecand = 2 ;
    pEncPara->stHal.BaseCfg.tmv_en            = 1 ;

    /* make sps & pps & VOL stream */
    VENC_DRV_EflFlushStrmHeader(pEncPara);

    /* init RC para */
    pEncPara->stRc.IsIntraPic = 1;

    pEncPara->stRc.MinTimeOfP = 3;
    pEncPara->stRc.MaxTimeOfP = 6;
    pEncPara->stRc.DeltaTimeOfP = 0;
    pEncPara->stRc.IQpDelta = 2;
    pEncPara->stRc.PQpDelta = 2;

    /* init stat info */
    pEncPara->stStat.GetFrameNumTry  = 0;
    pEncPara->stStat.PutFrameNumTry  = 0;
    pEncPara->stStat.GetStreamNumTry = 0;
    pEncPara->stStat.PutStreamNumTry = 0;
    pEncPara->stStat.GetFrameNumOK  = 0;
    pEncPara->stStat.PutFrameNumOK  = 0;
    pEncPara->stStat.GetStreamNumOK = 0;
    pEncPara->stStat.PutStreamNumOK = 0;
    pEncPara->stStat.BufFullNum = 0;
    pEncPara->stStat.QuickEncodeSkip = 0;
    pEncPara->stStat.FrmRcCtrlSkip   = 0;
    pEncPara->stStat.TooFewBufferSkip = 0;
    pEncPara->stStat.TooManyBitsSkip = 0;
    pEncPara->stStat.ErrCfgSkip      = 0;
    pEncPara->stStat.SamePTSSkip     = 0;
    pEncPara->stStat.StreamTotalByte = 0;

    pEncPara->stStat.u32RealSendInputRrmRate = 0;
    pEncPara->stStat.u32RealSendOutputFrmRate = 0;

    pEncPara->stStat.QueueNum        = 0;
    pEncPara->stStat.DequeueNum      = 0;
    pEncPara->stStat.StreamQueueNum  = 0;
    pEncPara->stStat.MsgQueueNum     = 0;
    pEncPara->stStat.UsedStreamBuf   = 0;

    pEncPara->stStat.u32TotalEncodeNum = 0;
    pEncPara->stStat.u32TotalPicBits   = 0;

    /* init src info */
    pEncPara->stSrcInfo.pfGetImage = VENC_DRV_EflGetImage;
    pEncPara->stSrcInfo.pfPutImage = VENC_DRV_EflPutImage;

    pEncPara->stSrcInfo.handle = HI_INVALID_HANDLE;
}

static HI_S32 GetWriteReadPtrBufAddr(VeduEfl_EncPara_S *pEncPara)
{
    if (STRM_AllocWriteReadPtrBuf(pEncPara->hStrmMng, &pEncPara->WpRpMMZBuf) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    memset(pEncPara->WpRpMMZBuf.pu8StartVirAddr, 0 , 4096);
    pEncPara->stHal.StrmBufRpAddr = pEncPara->WpRpMMZBuf.u32StartPhyAddr;
    pEncPara->stHal.StrmBufWpAddr = pEncPara->WpRpMMZBuf.u32StartPhyAddr + 16;
    pEncPara->StrmBufRpVirAddr = (HI_U32*)pEncPara->WpRpMMZBuf.pu8StartVirAddr;
    pEncPara->StrmBufWpVirAddr = (HI_U32*)(pEncPara->WpRpMMZBuf.pu8StartVirAddr + 16);

    return HI_SUCCESS;
}

static HI_S32 GetDdrCfgModeBufAddr(Vedu_Hal_S *pstHal, HI_U32 Protocol)
{
    HI_S32 Ret;
    if ((pstHal->RegConfigMode) && (Protocol != VEDU_JPGE))
    {
        HI_U32 DdrRegCfgBufSize = 4096;

        Ret = HI_DRV_VENC_MMZ_AllocAndMap("VENC_DdrRegCfgBuf", HI_NULL, DdrRegCfgBufSize, 64, &pstHal->DdrRegCfgBuf);

        if (Ret != HI_SUCCESS)
        {
            return HI_FAILURE;
        }

        memset(pstHal->DdrRegCfgBuf.pu8StartVirAddr, 0 , DdrRegCfgBufSize);
    }

    return HI_SUCCESS;
}

static HI_VOID GetRcnAndMVAddr(Vedu_Hal_S *pstHal, HI_U32 LumaSize, HI_U32 BusRcnBuf)
{
    HI_U32 j = BusRcnBuf + LumaSize * 3;

    pstHal->RcnYAddr[0] = BusRcnBuf;
    pstHal->RcnCAddr[0] = BusRcnBuf + LumaSize;
    pstHal->RcnYAddr[1] = BusRcnBuf + LumaSize * 3 / 2;
    pstHal->RcnCAddr[1] = BusRcnBuf + LumaSize * 5 / 2;

    pstHal->RcnYAddr_head[0] = j;
    j += 0x08000;   //(width+63)/64* (height+63)/64*2*16
    pstHal->RcnYAddr_head[1] = j;
    j += 0x08000;
    pstHal->RcnCAddr_head[0] = j;
    j += 0x04000;   //(width+63)/64* (height/2+63)/64*2*16
    pstHal->RcnCAddr_head[1] = j;
    j += 0x04000;

    pstHal->TmvAddr      [0] = j;
    j += 0x100000;  //H265: (width+63)/64* (height+63)/64*8*16 ;H264:((width+15)/16* (height+15)/16+7)/8*8*1601425.83333333333333333333
    pstHal->TmvAddr      [1] = j;
    j += 0x100000;
    pstHal->PmeAddr      [0] = j;
    j += 0x100000;  //(width+63)/4* (height+63)/4
    pstHal->PmeAddr      [1] = j;
    j += 0x100000;
    pstHal->PmeInfoAddr  [0] = j;
    j += 0x20000;   //(((width+15)/16))+127)/128*(height+15)/16
    pstHal->PmeInfoAddr  [1] = j;
    j += 0x20000;
    pstHal->PmeInfoAddr  [2] = j;
    j += 0x20000;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     : EncHandle
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflCreateVenc(VeduEfl_EncPara_S **pEncHandle, VeduEfl_EncCfg_S *pEncCfg)
{
    VeduEfl_EncPara_S *pEncPara;
    HI_U32 LumaSize;
    HI_U32 BusRcnBuf; /* 16 aligned, = 2.0 frame mb-yuv */
    HI_U32 BitBufSize;
    Vedu_Hal_S *pstHal = HI_NULL;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    /* get Config info */
    memset(&stStreamInfo, 0, sizeof(STRMMNG_STREAM_INFO_S));

    /* get current luma size */
    if (VENC_DRV_EflGetLumaSize(pEncCfg, &LumaSize) != HI_SUCCESS)
    {
        return HI_ERR_VENC_INVALID_PARA;
    }

    /* malloc encoder parameter */
    pEncPara = (VeduEfl_EncPara_S *)HI_VMALLOC(HI_ID_VENC, sizeof(VeduEfl_EncPara_S));
    if (pEncPara == HI_NULL)
    {
        HI_ERR_VENC("HI_VMALLOC failed, size = %d\n", sizeof(VeduEfl_EncPara_S));
        goto error_0;
    }
    memset(pEncPara, 0, sizeof(VeduEfl_EncPara_S));
    pstHal = &pEncPara->stHal;

    /* get stream manange handle */
    if (STRM_GetMatchMode(pEncCfg->Protocol, &pEncPara->hStrmMng, VeduIpCtx.IsChipIDV500R001) != HI_SUCCESS)
    {
        HI_ERR_VENC("Get STRM match Mode failed\n");
        goto error_1;
    }

    /* get smmu addr when SMMU support */
#ifdef HI_SMMU_SUPPORT
    HI_DRV_VENC_GetSmmuAddr(&pstHal->u32SmmuPageBaseAddr, &pstHal->u32SmmuErrReadAddr, &pstHal->u32SmmuErrWriteAddr);
#endif

    /* get bit stream buffer size */
    BitBufSize = STRM_GetBitBufSize(pEncPara->hStrmMng, &pEncCfg->streamBufSize, pEncCfg->SlcSplitEn, LumaSize);
    if (BitBufSize == 0)
    {
        goto error_1;
    }

    /* malloc stream buffer */
    if (STRM_AllocStreamBuf(pEncPara->hStrmMng, &pEncPara->StreamMMZBuf, pEncCfg->Protocol, BitBufSize, LumaSize) != HI_SUCCESS)
    {
        goto error_1;
    }

    /* Get write/read ptr buffer */
    if (GetWriteReadPtrBufAddr(pEncPara) != HI_SUCCESS)
    {
        goto error_2;
    }

    /* get parameter set buffer */
    if (STRM_AllocParaSetBufAddr(pEncPara->hStrmMng, &pstHal->SliceBuf, &pstHal->ParaSetPhyAddr)!= HI_SUCCESS)
    {
        goto error_3;
    }

    /* get DDR Cfg mode buffer addr*/
    pstHal->RegConfigMode = 1;
    if (GetDdrCfgModeBufAddr(pstHal, pEncCfg->Protocol) != HI_SUCCESS)
    {
        goto error_4;
    }

    /* ArrangeChnBuf -> rcn & bits */
    BusRcnBuf = pEncPara->StreamMMZBuf.u32StartPhyAddr + BitBufSize;
    GetRcnAndMVAddr(pstHal, LumaSize, BusRcnBuf);

    /************************************* add ******************************************/

    if (pEncCfg->bOMXChn)
    {
        pEncPara->FrameQueue_OMX = VENC_DRV_MngQueueInit(MAX_VEDU_QUEUE_NUM, HI_TRUE);

        if (HI_NULL == pEncPara->FrameQueue_OMX)
        {
            HI_ERR_VENC("failed to init FrameQueue, size = %d\n", sizeof(queue_info_s));
            goto error_5;
        }

        pEncPara->StreamQueue_OMX = VENC_DRV_MngQueueInit(MAX_VEDU_STRM_QUEUE_NUM, HI_TRUE);

        if (HI_NULL == pEncPara->StreamQueue_OMX)
        {
            HI_ERR_VENC("failed to init StreamQueue, size = %d\n", sizeof(queue_info_s));
            goto error_6;
        }

        pEncPara->MsgQueue_OMX = VENC_DRV_MngQueueInit(MSG_QUEUE_NUM, HI_TRUE);

        if (HI_NULL == pEncPara->MsgQueue_OMX)
        {
            HI_ERR_VENC("failed to init MsgQueue, size = %d\n", sizeof(queue_info_s));
            goto error_7;
        }
    }
    else
    {
        pEncPara->FrameQueue = VENC_DRV_MngQueueInit(MAX_VEDU_QUEUE_NUM, HI_FALSE);

        if (HI_NULL == pEncPara->FrameQueue)
        {
            HI_ERR_VENC("failed to init FrameQueue, size = %d\n", sizeof(queue_info_s));
            goto error_5;
        }

        pEncPara->FrameDequeue = VENC_DRV_MngQueueInit(MAX_VEDU_QUEUE_NUM * 2, HI_FALSE);

        if (HI_NULL == pEncPara->FrameDequeue)
        {
            HI_ERR_VENC("failed to init FrameDequeue, size = %d\n", sizeof(queue_info_s));
            goto error_6;
        }
    }

    /* give cfg info to encpara*/
    VENC_DRV_EflInitCfg(pEncPara, pEncCfg);

    /*create inst, get handle num*/
    SetStreamInfo(pEncPara, &stStreamInfo);
    if (STRM_Create(&pEncPara->hStrmMng, &stStreamInfo) != HI_SUCCESS)
    {
        goto error_8;
    }

    /* get return val */
    *pEncHandle = pEncPara;

    return HI_SUCCESS;

error_8:
    if (pEncCfg->bOMXChn)
    {
        if (VENC_DRV_MngQueueDeinit(pEncPara->MsgQueue_OMX) != HI_SUCCESS)
        {
            HI_ERR_VENC("HI_VFREE failed to free MsgQueue_OMX, size = %d\n", sizeof(queue_info_s));
        }
    }
    else
    {
        if (VENC_DRV_MngQueueDeinit(pEncPara->FrameDequeue) != HI_SUCCESS)
        {
            HI_ERR_VENC("HI_VFREE failed to free FrameDequeue, size = %d\n", sizeof(queue_info_s));
        }
    }
error_7:

    if (pEncCfg->bOMXChn)
    {
        if (VENC_DRV_MngQueueDeinit(pEncPara->StreamQueue_OMX) != HI_SUCCESS)
        {
            HI_ERR_VENC("HI_VFREE failed to free StreamQueue_OMX, size = %d\n", sizeof(queue_info_s));
        }
    }

error_6:

    if (pEncCfg->bOMXChn)
    {
        if (VENC_DRV_MngQueueDeinit(pEncPara->FrameQueue_OMX) != HI_SUCCESS)
        {
            HI_ERR_VENC("HI_VFREE failed to free FrameQueue_OMX, size = %d\n", sizeof(queue_info_s));
        }
    }
    else
    {
        if (VENC_DRV_MngQueueDeinit(pEncPara->FrameQueue) != HI_SUCCESS)
        {
            HI_ERR_VENC("HI_VFREE failed to free FrameQueue, size = %d\n", sizeof(queue_info_s));
        }
    }

error_5:
    HI_DRV_VENC_MMZ_UnmapAndRelease(&pstHal->DdrRegCfgBuf);
error_4:
    if (STRM_RlsParaSetBufAddr(pEncPara->hStrmMng, &pstHal->SliceBuf) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
error_3:
    if (STRM_RlsWriteReadPtrBuf(pEncPara->hStrmMng, &pEncPara->WpRpMMZBuf)!= HI_SUCCESS)
    {
        return HI_FAILURE;
    }
error_2:
    if (STRM_RlsStreamBuf(pEncPara->hStrmMng, &pEncPara->StreamMMZBuf, pEncCfg->Protocol) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }
error_1:
    HI_VFREE(HI_ID_VENC, pEncPara);
error_0:
    return HI_FAILURE;
}

HI_S32 VENC_DRV_EflDestroyVenc( VeduEfl_EncPara_S* EncHandle )
{
    VENC_BUFFER_S sMBufVenc_temp  = {0};
    HI_U32 i = 0;
    HI_U32 ChanId = 0;
    VeduEfl_EncPara_S*  pEncPara = EncHandle;

    if (pEncPara == NULL)
    {
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (STRM_RlsStreamBuf(pEncPara->hStrmMng, &pEncPara->StreamMMZBuf, pEncPara->Protocol)!= HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    if (STRM_RlsWriteReadPtrBuf(pEncPara->hStrmMng, &pEncPara->WpRpMMZBuf)!= HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    if (pEncPara->stHal.RegConfigMode)
    {
        HI_DRV_VENC_MMZ_UnmapAndRelease(&pEncPara->stHal.DdrRegCfgBuf);
    }

    if (STRM_Destroy(pEncPara->hStrmMng) != HI_SUCCESS)
    {
        HI_ERR_VENC("STRMMNG_Destroy failed!");
    }

    if (STRM_RlsParaSetBufAddr(pEncPara->hStrmMng, &pEncPara->stHal.SliceBuf) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    if (pEncPara->OMXChn)
    {
        for(i = 0; i < OMX_OUTPUT_PORT_BUFFER_MAX;i++)
        {
            if ( 0 != g_stKernelOmxmmz[ChanId][i].pu8StartVirAddr)
            {
               sMBufVenc_temp.pu8StartVirAddr = g_stKernelOmxmmz[ChanId][i].pu8StartVirAddr;
               HI_DRV_VENC_Unmap(&sMBufVenc_temp);
            }
        }

        if( VENC_DRV_MngQueueDeinit(pEncPara->StreamQueue_OMX))
        {
            HI_ERR_VENC("HI_VFREE failed to free StreamQueue_OMX, size = %d\n", sizeof(queue_info_s));
            return HI_FAILURE;
        }

        if( VENC_DRV_MngQueueDeinit(pEncPara->FrameQueue_OMX))
        {
            HI_ERR_VENC("HI_VFREE failed to free FrameQueue_OMX, size = %d\n", sizeof(queue_info_s));
            return HI_FAILURE;
        }

        if( VENC_DRV_MngQueueDeinit(pEncPara->MsgQueue_OMX))
        {
            HI_ERR_VENC("HI_VFREE failed to free MsgQueue_OMX, size = %d\n", sizeof(queue_info_s));
            return HI_FAILURE;
        }

    }
    else
    {
        if( VENC_DRV_MngQueueDeinit(pEncPara->FrameQueue))
        {
            HI_ERR_VENC("HI_VFREE failed to free FrameQueue, size = %d\n", sizeof(queue_info_s));
            return HI_FAILURE;
        }
        if( VENC_DRV_MngQueueDeinit(pEncPara->FrameDequeue))
        {
            HI_ERR_VENC("HI_VFREE failed to free FrameDequeue, size = %d\n", sizeof(queue_info_s));
            return HI_FAILURE;
        }
    }

    HI_VFREE(HI_ID_VENC, pEncPara);

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflAttachInput( VeduEfl_EncPara_S* EncHandle, VeduEfl_SrcInfo_S* pSrcInfo )
{
    HI_U32 u32ChnID = 0;
    VeduEfl_EncPara_S  *pEncPara;
    D_VENC_GET_CHN(u32ChnID,EncHandle);
    D_VENC_CHECK_CHN(u32ChnID);

    pEncPara = EncHandle;

    if (pEncPara->OMXChn)
    {
        if (!pSrcInfo->pfGetImage_OMX)
        {
            return HI_FAILURE;
        }
    }
    else
    {
        if ((!pSrcInfo->pfGetImage) || (!pSrcInfo->pfPutImage) || (!pSrcInfo->pfChangeInfo))
        {
            return HI_FAILURE;
        }
    }

    pEncPara->stSrcInfo = *pSrcInfo;

    g_stVencChn[u32ChnID].stSrcInfo = *pSrcInfo;
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflDetachInput( VeduEfl_EncPara_S* EncHandle, VeduEfl_SrcInfo_S* pSrcInfo )
{
    HI_U32 u32ChnID = 0;
    VeduEfl_EncPara_S  *pEncPara;
    D_VENC_GET_CHN(u32ChnID,EncHandle);
    D_VENC_CHECK_CHN(u32ChnID);
    pEncPara = EncHandle;
    pEncPara->stSrcInfo = *pSrcInfo;
    g_stVencChn[u32ChnID].stSrcInfo = *pSrcInfo;
    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_VOID VENC_DRV_EflRequestIframe( VeduEfl_EncPara_S* EncHandle )
{
    VeduEfl_EncPara_S* pEncPara = EncHandle;

    pEncPara->InterFrmCnt = pEncPara->stRc.Gop - 1;

    pEncPara->stRc.IFrmInsertFlag = 1;
    pEncPara->stRc.RcStart = 1;

    return;
}

HI_S32 VENC_DRV_EflRcGetAttr( VeduEfl_EncPara_S* EncHandle, VeduEfl_RcAttr_S* pRcAttr )
{
    VeduEfl_EncPara_S* pEncPara = EncHandle;

    pRcAttr->BitRate = pEncPara->stRc.BitRate;
    pRcAttr->OutFrmRate = pEncPara->stRc.VoFrmRate;
    pRcAttr->InFrmRate = pEncPara->stRc.ViFrmRate;

    pRcAttr->MaxQp  = pEncPara->stRc.MaxQp;
    pRcAttr->MinQp  = pEncPara->stRc.MinQp;

    return HI_SUCCESS;
}

#ifdef VENC_SUPPORT_JPGE
HI_S32 VENC_DRV_EflAllocBuf2Jpge(VeduEfl_EncPara_S* EncHandle, HI_U32 CapLevel)
{
    HI_S32 s32Ret = 0;
    HI_U32 u32Size = 0;
    VeduEfl_EncPara_S  *pEncPara = EncHandle;
    if (pEncPara == NULL)
    {
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    switch (CapLevel)
    {
        case VEDU_CAP_LEVEL_QCIF:
            u32Size = 176*144*3/2;
            break;
        case VEDU_CAP_LEVEL_CIF:
            u32Size = 352*288*3/2;
            break;
        case VEDU_CAP_LEVEL_D1:
            u32Size = 720*576*3/2;
            break;
        case VEDU_CAP_LEVEL_720P:
            u32Size = 1280*720*3/2;
            break;
        case VEDU_CAP_LEVEL_1080P:
            u32Size = 1920*1088*3/2;
            break;
        default:
            return HI_ERR_VENC_INVALID_PARA;
    }

    s32Ret = HI_DRV_VENC_AllocAndMap("Venc_JpegOutBuf", HI_NULL, u32Size, 64, &pEncPara->JpgMMZBuf);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("HI_DRV_VENC_AllocAndMap failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;

}

HI_S32 VENC_DRV_EflFreeBuf2Jpge( VeduEfl_EncPara_S* EncHandle )
{
    VeduEfl_EncPara_S* pEncPara = EncHandle;
    if (pEncPara == NULL)
    {
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }


    HI_DRV_VENC_UnmapAndRelease(&pEncPara->JpgMMZBuf);


    return HI_SUCCESS;
}
#endif

#ifndef __VEDU_NEW_RC_ALG__
HI_S32 VENC_DRV_EflRcAttrInit( VeduEfl_EncPara_S* EncHandle, VeduEfl_RcAttr_S* pRcAttr )
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;
    HI_U32 i;
    HI_U32 TrCountTemp = 0;
    HI_U32 *pTrCount = NULL;

    if ((pRcAttr->InFrmRate > HI_VENC_MAX_fps) || (pRcAttr->InFrmRate < pRcAttr->OutFrmRate))
    {
        return HI_FAILURE;
    }

    if (pRcAttr->OutFrmRate == 0)
    {
        return HI_FAILURE;
    }

    if (pEncPara->stRc.VoFrmRate != pRcAttr->OutFrmRate || pEncPara->stRc.ViFrmRate != pRcAttr->InFrmRate)
    {
        pTrCount = &pEncPara->TrCount;
    }
    else
    {
        pTrCount = &TrCountTemp;
    }

    pEncPara->stRc.BitRate   = pRcAttr->BitRate;
    pEncPara->stRc.VoFrmRate = pRcAttr->OutFrmRate;
    pEncPara->stRc.ViFrmRate = pRcAttr->InFrmRate;
    pEncPara->stRc.MaxQp     = pRcAttr->MaxQp;
    pEncPara->stRc.MinQp     = pRcAttr->MinQp;

    /*initialize frame rate control parameter*/
    VENC_DRV_FifoInit( &pEncPara->stBitsFifo, pEncPara->BitsFifo, pEncPara->stRc.ViFrmRate,
                       pEncPara->stRc.BitRate / pEncPara->stRc.ViFrmRate);

    pEncPara->MeanBit = pEncPara->stRc.BitRate / pEncPara->stRc.VoFrmRate;
    *pTrCount = pEncPara->stRc.ViFrmRate;

    for (i = 0; i < pEncPara->stRc.ViFrmRate; i++)
    {
        *pTrCount += pEncPara->stRc.VoFrmRate;

        if (*pTrCount > pEncPara->stRc.ViFrmRate)
        {
            *pTrCount -= pEncPara->stRc.ViFrmRate;
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, pEncPara->MeanBit);
        }
        else
        {
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, 0);
        }
    }

    /*initialize re-start parameter*/
    pEncPara->stRc.RcStart = 1;

    return HI_SUCCESS;
}

#else

HI_S32 VENC_DRV_EflRcAttrInit( VeduEfl_EncPara_S* EncHandle, VeduEfl_RcAttr_S* pRcAttr )
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;
    HI_U32 i;
    HI_U32 TrCountTemp = 0;
    HI_U32 *pTrCount = NULL;

    if ((pRcAttr->InFrmRate > HI_VENC_MAX_fps) || (pRcAttr->InFrmRate < pRcAttr->OutFrmRate))
    {
        return HI_FAILURE;
    }

    if (pRcAttr->OutFrmRate == 0)
    {
        return HI_FAILURE;
    }

    if (pEncPara->stRc.VoFrmRate != pRcAttr->OutFrmRate || pEncPara->stRc.ViFrmRate != pRcAttr->InFrmRate)
    {
        pTrCount = &pEncPara->TrCount;
    }
    else
    {
        pTrCount = &TrCountTemp;
    }

    pEncPara->stRc.BitRate   = pRcAttr->BitRate;
    pEncPara->stRc.VoFrmRate = pRcAttr->OutFrmRate;
    pEncPara->stRc.ViFrmRate = pRcAttr->InFrmRate;
    pEncPara->stRc.MaxQp     = pRcAttr->MaxQp;
    pEncPara->stRc.MinQp     = pRcAttr->MinQp;

    /*initialize frame rate control parameter*/
    VENC_DRV_FifoInit( &pEncPara->stBitsFifo, pEncPara->BitsFifo, pEncPara->stRc.ViFrmRate,
                       pEncPara->stRc.BitRate / pEncPara->stRc.ViFrmRate);

    pEncPara->MeanBit = pEncPara->stRc.BitRate / pEncPara->stRc.VoFrmRate;
    *pTrCount         = pEncPara->stRc.ViFrmRate;

    for (i = 0; i < pEncPara->stRc.ViFrmRate; i++)
    {
        *pTrCount += pEncPara->stRc.VoFrmRate;

        if (*pTrCount > pEncPara->stRc.ViFrmRate)
        {
            *pTrCount -= pEncPara->stRc.ViFrmRate;
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, pEncPara->MeanBit);
        }
        else
        {
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, 0);
        }
    }

    /*initialize re-start parameter*/
    pEncPara->stRc.RcStart = 1;

    return HI_SUCCESS;
}

#endif

HI_S32 VENC_DRV_EflRcFrmRateCtrl( VeduEfl_EncPara_S* EncHandle, HI_U32 TR )
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;
    HI_U32  DiffTR = (TR - pEncPara->LastTR);
    HI_U32 i;

    if (pEncPara->stRc.RcStart)
    {
        pEncPara->TrCount  = pEncPara->stRc.ViFrmRate;
        pEncPara->TrCount += pEncPara->stRc.VoFrmRate;
        pEncPara->LastTR   = TR;
        pEncPara->stRc.IsIntraPic = 1;
        pEncPara->FrmCnt   = 0;
    }
    else
    {
        /* don't run too many loop */
        if (DiffTR < VEDU_TR_STEP)
        {
            return HI_FAILURE;
        }
        else if (DiffTR > 0x1f)
        {
            DiffTR = 0x1f;
        }

        /* LOST frames into fifo */
        for (i = 0; i < DiffTR - VEDU_TR_STEP; i += VEDU_TR_STEP)
        {
            pEncPara->TrCount += pEncPara->stRc.VoFrmRate;
            VENC_DRV_FifoWrite( &pEncPara->stBitsFifo, 0);
        }

        /* this frame */
        pEncPara->TrCount += pEncPara->stRc.VoFrmRate;
        pEncPara->LastTR = TR;

        /* don't care too many Lost frames */
        if (pEncPara->TrCount > pEncPara->stRc.VoFrmRate + pEncPara->stRc.ViFrmRate)
        {
            pEncPara->TrCount = pEncPara->stRc.VoFrmRate + pEncPara->stRc.ViFrmRate;
        }

        /* skip this frame */
        if ((pEncPara->TrCount <= pEncPara->stRc.ViFrmRate)      /* time to skip */
            || (pEncPara->stBitsFifo.Sum > (pEncPara->stRc.BitRate / 100 * (pEncPara->DriftRcSkipThr + 100)))) /* too many bits */ //RC_Threshold = 20%
        {
            if (pEncPara->TrCount <= pEncPara->stRc.ViFrmRate)
            {
                pEncPara->stStat.FrmRcCtrlSkip++;
            }
            else
            {
                if ((!pEncPara->OMXChn) && (pEncPara->AutoSkipFrameEn))
                {
                    pEncPara->stStat.TooManyBitsSkip++;
                }
                else
                {
                    goto OMX_SKIP;
                }

            }
            VENC_DRV_FifoWrite( &pEncPara->stBitsFifo, 0);
            return HI_FAILURE;
        }
OMX_SKIP:
        /* intra or inter based gop */
        if (pEncPara->InterFrmCnt >= pEncPara->stRc.Gop - 1)
        {
            pEncPara->stRc.IsIntraPic = 1;
            pEncPara->FrmCnt   = 0;
            pEncPara->stRc.FrmNumInGop = 0;
        }
        else
        {
            pEncPara->stRc.IsIntraPic = 0;
            pEncPara->stRc.FrmNumInGop = pEncPara->InterFrmCnt + 1;
        }
    }

    return HI_SUCCESS;
}

HI_S32 VENC_DRV_EflRcSetAttr( VeduEfl_EncPara_S* EncHandle, VeduEfl_RcAttr_S* pRcAttr )
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;
    VeduEfl_Rc_S stRc_old;
    HI_U32 i;
    HI_U32 TrCountTemp = 0;
    HI_U32 *pTrCount = NULL;

    if ((pRcAttr->InFrmRate > HI_VENC_MAX_fps) || (pRcAttr->InFrmRate < pRcAttr->OutFrmRate))
    {
        return HI_FAILURE;
    }

    if (pRcAttr->OutFrmRate == 0)
    {
        return HI_FAILURE;
    }

    if (pEncPara->stRc.VoFrmRate != pRcAttr->OutFrmRate || pEncPara->stRc.ViFrmRate != pRcAttr->InFrmRate)
    {
        pTrCount = &pEncPara->TrCount;
    }
    else
    {
        pTrCount = &TrCountTemp;
    }

    memcpy(&stRc_old,&(pEncPara->stRc),sizeof(stRc_old));

    /* updata the RC structure*/
    pEncPara->stRc.AverageFrameBits = pRcAttr->BitRate / pRcAttr->OutFrmRate;
    pEncPara->stRc.InstBitsLen = pRcAttr->OutFrmRate;

    if (pRcAttr->Gop <= (pEncPara->stRc.FrmNumInGop+1))
    {
         VENC_DRV_EflRequestIframe(pEncPara);
         goto init_process;
    }

init_process:

    /*initialize  parameter*/
    pEncPara->stRc.BitRate   = pRcAttr->BitRate;
    pEncPara->stRc.VoFrmRate = pRcAttr->OutFrmRate;
    pEncPara->stRc.ViFrmRate = pRcAttr->InFrmRate;
    pEncPara->stRc.Gop  = pRcAttr->Gop;
    *pTrCount           = pEncPara->stRc.ViFrmRate;

    /*updata the RC strmBuffer*/
    VENC_DRV_FifoInit( &pEncPara->stBitsFifo, pEncPara->BitsFifo, pEncPara->stRc.ViFrmRate,
                       pEncPara->stRc.BitRate / pEncPara->stRc.ViFrmRate);

    pEncPara->MeanBit = pEncPara->stRc.BitRate / pEncPara->stRc.VoFrmRate;

    for (i = 0; i < pEncPara->stRc.ViFrmRate; i++)
    {
        *pTrCount += pEncPara->stRc.VoFrmRate;

        if (*pTrCount > pEncPara->stRc.ViFrmRate)
        {
            *pTrCount -= pEncPara->stRc.ViFrmRate;
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, pEncPara->MeanBit);
        }
        else
        {
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, 0);
        }
    }

    return HI_SUCCESS;
}

#if 0
static HI_VOID VENC_DRV_EflIntraFrmRateChange( VeduEfl_EncPara_S *pEncPara,HI_U32 newViFrmRate,HI_UNF_VENC_CHN_ATTR_S stSrcUserCfg)
{
    HI_U32 i;
    pEncPara->ViFrmRate = newViFrmRate;
    if (stSrcUserCfg.u32TargetFrmRate > pEncPara->ViFrmRate)
    {
        pEncPara->VoFrmRate = pEncPara->ViFrmRate;

    }
    else
    {
        pEncPara->VoFrmRate = stSrcUserCfg.u32TargetFrmRate;
    }

    /* updata the RC structure*/
    pEncPara->stRc.AverageFrameBits   = pEncPara->BitRate / pEncPara->VoFrmRate;

    pEncPara->stRc.GopBitsLeft    = pEncPara->stRc.AverageFrameBits * (pEncPara->Gop - pEncPara->stRc.FrmNumInGop -1);

    pEncPara->stRc.TotalBitsLeft += pEncPara->stRc.GopBitsLeft;

    /*initialize  parameter*/
    pEncPara->TrCount   = pEncPara->ViFrmRate;

    /*updata the RC strmBuffer*/
    VENC_DRV_FifoInit( &pEncPara->stBitsFifo, pEncPara->BitsFifo, pEncPara->ViFrmRate,
                       pEncPara->BitRate / pEncPara->ViFrmRate);

    pEncPara->MeanBit = pEncPara->BitRate / pEncPara->VoFrmRate;

    for (i = 0; i < pEncPara->ViFrmRate; i++)
    {
        pEncPara->TrCount += pEncPara->VoFrmRate;

        if (pEncPara->TrCount > pEncPara->ViFrmRate)
        {
            pEncPara->TrCount -= pEncPara->ViFrmRate;
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, pEncPara->MeanBit);
        }
        else
        {
            VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, 0);
        }
    }

    return;
}
#endif

/******************************************************************************
Function   :
Description: 获取尽量可靠的输入帧率 与对应的输出帧率 并做相应的处理
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
static HI_VOID GetFrmRate_Attach( VeduEfl_EncPara_S *pEncPara,HI_UNF_VENC_CHN_ATTR_S stSrcUserCfg)
{
    HI_U32 diff1 = 0;
    HI_U32 newViFrmRate = 0;
    HI_U32 i = 0;

    HI_U32 max1,max2;

    if (0/*!pEncPara->AutoSkipFrameEn*/)
    {
        newViFrmRate = pEncPara->LastFrmRate[0] ;
    }
    else
    {
        if (pEncPara->LastFrmRate[5] == 0)  /*前6 帧还没有满，一直相信最大的那个帧率*/
        {
            max1 = D_VENC_RC_MAX3(pEncPara->LastFrmRate[0], pEncPara->LastFrmRate[1], pEncPara->LastFrmRate[2]);
            max2 = D_VENC_RC_MAX3(pEncPara->LastFrmRate[3], pEncPara->LastFrmRate[4], pEncPara->LastFrmRate[5]);
            newViFrmRate = D_VENC_RC_MAX(max1, max2);
        }
        else
        {
            if (pEncPara->stRc.bFrmRateSataError)
            {
                newViFrmRate = pEncPara->stRc.ViFrmRate;
            }
            else if (pEncPara->LastSecInputFrmRate[1] != 0) /*前2s帧率都统计出来了*/
            {
                diff1 = D_VENC_RC_ABS(pEncPara->LastSecInputFrmRate[0], pEncPara->LastSecInputFrmRate[1]);
                if ( diff1 <= 3)
                {
                    newViFrmRate = D_VENC_RC_MAX(pEncPara->LastSecInputFrmRate[0], pEncPara->LastSecInputFrmRate[1]);
                }
                else
                {
                    newViFrmRate = pEncPara->LastSecInputFrmRate[0];
                }
            }
            else if (pEncPara->LastSecInputFrmRate[0] != 0)  /*前1s帧率已经统计出来*/
            {
                newViFrmRate = pEncPara->LastSecInputFrmRate[0];
            }
            else  /*第一s的帧率还没有统计出来*/
            {
                max1 = D_VENC_RC_MAX3(pEncPara->LastFrmRate[0], pEncPara->LastFrmRate[1], pEncPara->LastFrmRate[2]);
                max2 = D_VENC_RC_MAX3(pEncPara->LastFrmRate[3], pEncPara->LastFrmRate[4], pEncPara->LastFrmRate[5]);
                newViFrmRate = D_VENC_RC_MAX(max1, max2);
            }
        }

        if (pEncPara->stRc.LastSecFrameCnt >= (1 + newViFrmRate))
        {
            if ( pEncPara->LastFrmRate[0] > newViFrmRate )
            {
                newViFrmRate = pEncPara->LastFrmRate[0] + (pEncPara->LastFrmRate[0] - newViFrmRate) + 6;
                pEncPara->stRc.bFrmRateSataError = 1;
            }
            else if (newViFrmRate < pEncPara->stRc.LastSecFrameCnt)
            {
                newViFrmRate = pEncPara->stRc.LastSecFrameCnt + 15;
                pEncPara->stRc.bFrmRateSataError = 1;
            }

        }
    }

    if ((newViFrmRate != pEncPara->stRc.ViFrmRate) && (newViFrmRate <= FrmRateCntBufNum))
    {
        if (newViFrmRate >= FrmRateCntBufNum)
        {
            newViFrmRate = FrmRateCntBufNum;   // fifo buffer range
        }

        pEncPara->stRc.ViFrmRate = newViFrmRate;

        if (stSrcUserCfg.u32TargetFrmRate > pEncPara->stRc.ViFrmRate)
        {
            pEncPara->stRc.VoFrmRate = pEncPara->stRc.ViFrmRate;

        }
        else
        {
            pEncPara->stRc.VoFrmRate = stSrcUserCfg.u32TargetFrmRate;
        }

        /* updata the RC structure*/
        if (pEncPara->stRc.bFrmRateSataError)    //error!
        {
            pEncPara->stRc.AverageFrameBits   = pEncPara->stRc.BitRate / (pEncPara->stRc.VoFrmRate + 8);
        }
        else
        {
            pEncPara->stRc.AverageFrameBits   = pEncPara->stRc.BitRate / pEncPara->stRc.VoFrmRate;
        }


        /*initialize  parameter*/
        pEncPara->TrCount   = pEncPara->stRc.ViFrmRate;

        /*updata the RC strmBuffer*/
        VENC_DRV_FifoInit( &pEncPara->stBitsFifo, pEncPara->BitsFifo, pEncPara->stRc.ViFrmRate,
                           pEncPara->stRc.BitRate / pEncPara->stRc.ViFrmRate);

        pEncPara->MeanBit = pEncPara->stRc.BitRate / pEncPara->stRc.VoFrmRate;

        for (i = 0; i < pEncPara->stRc.ViFrmRate; i++)
        {
            pEncPara->TrCount += pEncPara->stRc.VoFrmRate;

            if (pEncPara->TrCount > pEncPara->stRc.ViFrmRate)
            {
                pEncPara->TrCount -= pEncPara->stRc.ViFrmRate;
                VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, pEncPara->MeanBit);
            }
            else
            {
                VENC_DRV_FifoWriteInit( &pEncPara->stBitsFifo, 0);
            }
        }
    }

    return;
}

static HI_VOID GetFrmRate_User( VeduEfl_EncPara_S* pEncPara, HI_U32 u32ChnID)
{
    pEncPara->stRc.ViFrmRate = g_stVencChn[u32ChnID].stChnUserCfg.u32InputFrmRate;
    pEncPara->stRc.VoFrmRate = g_stVencChn[u32ChnID].stChnUserCfg.u32TargetFrmRate;
    pEncPara->stRc.LastSecFrameCntForUsr = pEncPara->stRc.RcStart ? 0 : pEncPara->stRc.LastSecFrameCntForUsr + 1;

    if (pEncPara->stRc.LastSecFrameCntForUsr >= pEncPara->stRc.ViFrmRate)
    {
        pEncPara->stRc.LastSecFrameCntForUsr = 0;
        pEncPara->stRc.Waterline = pEncPara->stRc.WaterlineInit;
    }
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflSetResolution( VeduEfl_EncPara_S* EncHandle, HI_U32 FrameWidth, HI_U32 FrameHeight )
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;
    VeduEfl_RcAttr_S RcAttr;
    HI_U32 WidthInMb  = (FrameWidth + 15) >> 4;
    HI_U32 HeightInMb = (FrameHeight + 15) >> 4;
    HI_U32 LumaSize = (WidthInMb * HeightInMb) << 8;

    /* check config */
    if (LumaSize > pEncPara->stHal.RcnCAddr[0] - pEncPara->stHal.RcnYAddr[0])
    {
        return HI_FAILURE;
    }

    VENC_DRV_EflRcGetAttr(pEncPara, &RcAttr );
    if (HI_SUCCESS != VENC_DRV_EflRcAttrInit(EncHandle, &RcAttr ))
    {
        HI_ERR_VENC("config venc Rate Control Attribute err!.\n");
        return HI_FAILURE;
    }

    pEncPara->stHal.SlcSplitMod = 1;
    pEncPara->NumRefIndex = 0;
    pEncPara->stRc.PicWidth  = FrameWidth;
    pEncPara->stRc.PicHeight = FrameHeight;

    VENC_DRV_EflFlushStrmHeader( pEncPara );
    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/

HI_S32 VENC_DRV_EflStartVenc(VeduEfl_EncPara_S* EncHandle)
{
    HI_U32 i,j;
    VEDU_LOCK_FLAG flag;
    VeduEfl_EncPara_S *pEncPara = NULL;
    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag );

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (VeduChnCtx[i].EncHandle == NULL)
        {
            VeduChnCtx[i].EncHandle = EncHandle;
            pEncPara = EncHandle;
            break;
        }
    }
    if ((i >= HI_VENC_MAX_CHN) || (pEncPara == NULL))
    {
        VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    for (j = 0;j < HI_VENC_MAX_CHN; j++)
    {
        if( INVAILD_CHN_FLAG ==PriorityTab[0][j])
        {
           PriorityTab[0][j] = i;
           PriorityTab[1][j] = pEncPara->Priority;
           VENC_DRV_EflSortPriority();
           break;
        }
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    pEncPara->bNeverEnc = HI_TRUE;
    pEncPara->bFirstNal2Send = HI_TRUE;

    return HI_SUCCESS;
}

static HI_VOID VENC_DRV_EflInitLastFrmRate(HI_U32 *LastFrmRate, HI_U32 *LastSecInputFrmRate)
{
    HI_U32 i;

    for(i = 0; i < 6; i++)
    {
        LastFrmRate[i] = 0;
    }
    for(i = 0; i < 2; i++)
    {
        LastSecInputFrmRate[i] = 0;
    }

    return;
}

HI_S32 VENC_DRV_EflStopVenc(VeduEfl_EncPara_S* EncHandle)
{
    HI_U32 i,j;
    HI_U32 timeCnt = 0;

    VEDU_LOCK_FLAG flag;
    HI_U32 u32VeChn;
    VeduEfl_EncPara_S *pEncPara = NULL;

    D_VENC_GET_CHN(u32VeChn, EncHandle);
    D_VENC_CHECK_CHN(u32VeChn);
    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag );

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (VeduChnCtx[i].EncHandle == EncHandle)
        {
            VeduChnCtx[i].EncHandle = NULL;
            break;
        }
    }
    for (j = 0;(i < HI_VENC_MAX_CHN)&&(j < HI_VENC_MAX_CHN); j++)
    {
        if( i ==PriorityTab[0][j])
        {
           PriorityTab[0][j] = INVAILD_CHN_FLAG;
           PriorityTab[1][j] = 0;
           VENC_DRV_EflSortPriority();
           break;
        }
    }
    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    if (i == HI_VENC_MAX_CHN)
    {
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    /* wait finish last frame */
    while ((((VeduEfl_EncPara_S *)EncHandle)->WaitingIsr) && (timeCnt < 1000))
    {
        msleep(1);
        timeCnt++;
        HI_WARN_VENC("wait the VEDU isr!!! timeCnt = %d\n",timeCnt);
    }

    if (timeCnt == 1000)
    {
        HI_ERR_VENC("wait the VEDU isr time out!!Force to stop the channel\n");
    }
#ifdef VENC_SUPPORT_JPGE
    /* wait finish last frame */
    while (((VeduEfl_EncPara_S *)EncHandle)->WaitingIsr_jpge)
    {
        msleep(1);
    }
#endif

    VENC_DRV_OsalGiveEvent(&g_VencWait_Stream[u32VeChn]);

    /* rfresh the queue of the Img */
    pEncPara = EncHandle;
    if (g_stVencChn[u32VeChn].enSrcModId >= HI_ID_BUTT)
    {
        if (!pEncPara->OMXChn)  /* for venc */
        {
            VENC_DRV_MngMoveQueueToDequeue(pEncPara->FrameQueue, pEncPara->FrameDequeue);
        }
        else                    /* for omxvenc */
        {
            VENC_DRV_EflFlushPort_OMX(EncHandle, ALL_PORT, HI_TRUE);
        }
    }
    else
    {
       VENC_DRV_EflRlsAllFrame( EncHandle);
    }

    pEncPara->stRc.bFrmRateSataError = 0;
    VENC_DRV_EflInitLastFrmRate(pEncPara->LastFrmRate, pEncPara->LastSecInputFrmRate);

    STRM_ResetBuffer(pEncPara->hStrmMng, pEncPara->Protocol);

    if (g_stVencChn[u32VeChn].bOMXChn)
       {
         VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_STOP_DONE, HI_SUCCESS, NULL);
         pEncPara->stStat.MsgQueueNum++;
       }

    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_VOID VENC_DRV_DbgLowdelayEvent(HI_S32 ChanId,HI_LD_Event_ID_E eventId, HI_U32 u32FrameId,HI_HANDLE hSrcHd)
{
    HI_LD_Event_S evt;
    HI_U32 TmpTime = 0;
    HI_DRV_SYS_GetTimeStampMs(&TmpTime);

    evt.evt_id = eventId;
    evt.frame = u32FrameId;
    evt.handle = hSrcHd;
    evt.time = TmpTime;
    HI_DRV_LD_Notify_Event(&evt);
}
static HI_S32 VENC_DRV_EflCheckImgCfg(const HI_DRV_VIDEO_FRAME_S *pstPreImage,HI_U32 yuvStoreType)
{
    HI_BOOL flag = 0;

    flag |= (pstPreImage->u32Width > HI_VENC_MAX_WIDTH)||(pstPreImage->u32Width < HI_VENC_MIN_WIDTH);
    flag |= (pstPreImage->u32Height> HI_VENC_MAX_HEIGTH)||(pstPreImage->u32Height< HI_VENC_MIN_HEIGTH);
    flag |= (!pstPreImage->stBufAddr[0].u32PhyAddr_Y) || (pstPreImage->stBufAddr[0].u32PhyAddr_Y % 16);
    flag |= (!pstPreImage->stBufAddr[0].u32Stride_Y ) || (pstPreImage->stBufAddr[0].u32Stride_Y  % 16);
    if (VENC_STORE_PLANNAR == yuvStoreType)
    {
        flag |= (!pstPreImage->stBufAddr[0].u32PhyAddr_C)  || (pstPreImage->stBufAddr[0].u32PhyAddr_C %16);
        flag |= (!pstPreImage->stBufAddr[0].u32PhyAddr_Cr) || (pstPreImage->stBufAddr[0].u32PhyAddr_Cr%16);
        flag |= (!pstPreImage->stBufAddr[0].u32Stride_C )  || (pstPreImage->stBufAddr[0].u32Stride_C  %16);
        flag |= (!pstPreImage->stBufAddr[0].u32Stride_Cr)  || (pstPreImage->stBufAddr[0].u32Stride_Cr %16);

        flag |= (pstPreImage->stBufAddr[0].u32Stride_Cr != pstPreImage->stBufAddr[0].u32Stride_C);
    }
    else if (VENC_STORE_SEMIPLANNAR == yuvStoreType)
    {
        flag |= (!pstPreImage->stBufAddr[0].u32PhyAddr_C)  || (pstPreImage->stBufAddr[0].u32PhyAddr_C %16);
        flag |= (!pstPreImage->stBufAddr[0].u32Stride_C )  || (pstPreImage->stBufAddr[0].u32Stride_C  %16);
    }

    if (HI_TRUE == flag)
    {
       return HI_FAILURE;
    }
    else { return HI_SUCCESS; }
}


static HI_S32 VENC_DRV_EflQueryChn_X_Resize(HI_U32 u32ChnID, VeduEfl_EncPara_S* pEncPara)
{
    /* configured the resolving power dynamically */
    if ((pEncPara->stImage.u32Width != pEncPara->stRc.PicWidth) || (pEncPara->stImage.u32Height != pEncPara->stRc.PicHeight))
    {
        if ((pEncPara->stImage.u32Width == g_stVencChn[u32ChnID].stChnUserCfg.u32Width)
            && (pEncPara->stImage.u32Height == g_stVencChn[u32ChnID].stChnUserCfg.u32Height))
        {
            if (HI_INVALID_HANDLE == g_stVencChn[u32ChnID].hJPGE)   /*h264*/
            {
                HI_S32 s32Ret = HI_FAILURE;
                VENC_DRV_EflRequestIframe(g_stVencChn[u32ChnID].hVEncHandle);
                s32Ret = VENC_DRV_EflSetResolution(g_stVencChn[u32ChnID].hVEncHandle, pEncPara->stImage.u32Width, pEncPara->stImage.u32Height);

                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_VENC("VeduEfl_SetResolution err:%#x.\n", s32Ret);
                    pEncPara->stStat.ErrCfgSkip++;
                    pEncPara->stStat.PutFrameNumTry++;
                    (pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &pEncPara->stImage);
                    pEncPara->stStat.PutFrameNumOK++;
                    pEncPara->stHal.PTS0 = pEncPara->stImage.u32Pts;

                    return HI_FAILURE;
                }
            }
#ifdef VENC_SUPPORT_JPGE
            else   /* JPEG */
            {
                pEncPara->stRc.PicWidth  = pEncPara->stImage.u32Width;
                pEncPara->stRc.PicHeight = pEncPara->stImage.u32Height;
            }
#endif
        }
        else
        {
            HI_ERR_VENC("ERR:Different resolution between the frame Info and the Encoder Cfg!Encode: %dX%d,FrameInfo: %dX%d\n",
                        g_stVencChn[u32ChnID].stChnUserCfg.u32Width, g_stVencChn[u32ChnID].stChnUserCfg.u32Height,
                        pEncPara->stImage.u32Width, pEncPara->stImage.u32Height);
            pEncPara->stStat.ErrCfgSkip++;
            pEncPara->stStat.PutFrameNumTry++;
            (pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &pEncPara->stImage);
            pEncPara->stStat.PutFrameNumOK++;

            pEncPara->stHal.PTS0 = pEncPara->stImage.u32Pts;
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static HI_VOID VENC_DRV_EflQueryChn_X_Stride(VeduEfl_EncIn_S* pEncIn, VeduEfl_EncPara_S* pEncPara)
{
    if (pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR)
    {
       pEncIn->BusViV = pEncPara->stImage.stBufAddr[0].u32PhyAddr_Cr;//pEncPara->stImage.u32CAddr;      //目前帧信息结构体缺少该结构,planer格式时需要；
    }

    if ((pEncPara->stHal.YuvStoreType == VENC_STORE_SEMIPLANNAR) && (VENC_YUV_422 == pEncPara->YuvSampleType))  /*==强制把SEMIPLANAR_422 当semiplaner 420编码*/
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
        pEncIn->ViCStride = pEncPara->stImage.stBufAddr[0].u32Stride_C * 2;
    }
    else if ((pEncPara->stHal.YuvStoreType == VENC_STORE_PACKAGE) && (VENC_YUV_422 == pEncPara->YuvSampleType))
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
        //pEncIn->ViCStride = pEncPara->stImage.stBufAddr[0].u32Stride_C;
    }
    else if ((pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR) && (VENC_YUV_420 == pEncPara->YuvSampleType))
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
        pEncIn->ViCStride = pEncPara->stImage.stBufAddr[0].u32Stride_C;
    }
    else
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
        pEncIn->ViCStride = pEncPara->stImage.stBufAddr[0].u32Stride_C;
    }
}

HI_VOID VENC_DRV_EflUpdateScanType(VeduEfl_EncPara_S *pEncPara)
{
    if ((pEncPara->Protocol == VEDU_H265) && (pEncPara->IsProgressive != pEncPara->stImage.bProgressive))
    {
        VeduEfl_H265e_VPS_S vps;
        pEncPara->IsProgressive = pEncPara->stImage.bProgressive;
        vps.general_interlaced_source_flag  = !pEncPara->IsProgressive;
        vps.general_progressive_source_flag =  pEncPara->IsProgressive;
        pEncPara->VpsBits = H265e_MakeVPS(pEncPara->VpsStream, &vps);
    }
}

static HI_S32 GetChannelImage(VeduEfl_EncPara_S* pEncPara, HI_HANDLE hHd)
{
    pEncPara->stStat.GetFrameNumTry++;

    if (!pEncPara->stSrcInfo.pfGetImage)
    {
        HI_ERR_VENC(" pfGetImage is NULL!!\n");

        return HI_FAILURE;
    }

    if ((pEncPara->stSrcInfo.pfGetImage)(hHd, &(pEncPara->stImage)) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    pEncPara->stStat.GetFrameNumOK++;

    return HI_SUCCESS;
}

static HI_VOID PutChannelImageForError(VeduEfl_EncPara_S* pEncPara)
{
    pEncPara->stStat.PutFrameNumTry++;
    (pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &(pEncPara->stImage));
    pEncPara->stStat.PutFrameNumOK++;
}

static HI_VOID GetChannelFrameRate(VeduEfl_EncPara_S* pEncPara, HI_U32 u32ChnID)
{
    if ( g_stVencChn[u32ChnID].enSrcModId != HI_ID_BUTT)
    {
        D_VENC_RC_UPDATE(pEncPara->LastFrmRate, pEncPara->stImage.u32FrameRate / 1000);
        pEncPara->stRc.LastSecFrameCnt++;
        GetFrmRate_Attach(pEncPara, g_stVencChn[u32ChnID].stChnUserCfg);
    }
    else
    {
        GetFrmRate_User(pEncPara, u32ChnID);
    }

    pEncPara->stStat.u32RealSendInputRrmRate  = pEncPara->stRc.ViFrmRate;
    pEncPara->stStat.u32RealSendOutputFrmRate = pEncPara->stRc.VoFrmRate;
}

static HI_VOID GetChannelPixelFormat(VeduEfl_EncPara_S* pEncPara)
{
    pEncPara->stHal.YuvStoreType  = Convert_PIX_Format(pEncPara->stImage.ePixFormat, 0);
    pEncPara->YuvSampleType       = Convert_PIX_Format(pEncPara->stImage.ePixFormat, 1);
    pEncPara->stHal.PackageSel    = Convert_PIX_Format(pEncPara->stImage.ePixFormat, 2);
    pEncPara->stStat.u32FrameType = Convert_PIX_Format(pEncPara->stImage.ePixFormat, 3);
}

static HI_S32 GetLocalChannelInfo_X(VeduEfl_EncPara_S* pEncPara, HI_U32 u32ChnID)
{
    HI_HANDLE hHd;

    hHd = (g_stVencChn[u32ChnID].bFrameBufMng) ? g_stVencChn[u32ChnID].hUsrHandle : pEncPara->stSrcInfo.handle;

    if (pEncPara->QuickEncode)
    {
        if (QuickEncode_Process(g_stVencChn[u32ChnID].hVEncHandle, hHd)!= HI_SUCCESS)
        {
            return HI_FAILURE;
        }
    }
    else
    {
        if (GetChannelImage(pEncPara, hHd) != HI_SUCCESS)
        {
            return HI_FAILURE;
        }
    }

   /* don't re-get */
   if (pEncPara->stHal.PTS0 == pEncPara->stImage.u32Pts)
   {
        PutChannelImageForError(pEncPara);
        pEncPara->stStat.SamePTSSkip++;

        return HI_FAILURE;
    }

    /* video encoder does frame rate control by two value: input frame rate and target frame rate */
    /* input frame rate is calculated by timer mechanism accurately */
    /* target frame rate is input by user and can be changed dynamiclly */
    GetChannelFrameRate(pEncPara, u32ChnID);

    VENC_DRV_EflUpdateScanType(pEncPara);

    /* configured the resolving power dynamically */
    if (VENC_DRV_EflQueryChn_X_Resize(u32ChnID, pEncPara) != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    /* skip - frame rate ctrl */
    if (VENC_DRV_EflRcFrmRateCtrl( g_stVencChn[u32ChnID].hVEncHandle, pEncPara->stStat.PutFrameNumOK) != HI_SUCCESS)
    {
        PutChannelImageForError(pEncPara);
        pEncPara->stHal.PTS0 = pEncPara->stImage.u32Pts;

        return HI_FAILURE;
    }

    GetChannelPixelFormat(pEncPara);

    /* check the picture resolving power ,stride ,addr info first*/
    if (VENC_DRV_EflCheckImgCfg(&pEncPara->stImage, pEncPara->stHal.YuvStoreType) != HI_SUCCESS)
    {
        HI_ERR_VENC("stImg cfg erro!!\n");
        PutChannelImageForError(pEncPara);
        pEncPara->stStat.ErrCfgSkip++;
        pEncPara->stHal.PTS0 = pEncPara->stImage.u32Pts;
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static HI_VOID GetGlobalChannelInfo_X(VeduEfl_EncPara_S* pEncPara, VeduEfl_EncIn_S *pEncIn)
{
    /****************get addr information**************/
    pEncIn->BusViY = pEncPara->stImage.stBufAddr[0].u32PhyAddr_Y;
    pEncIn->BusViC = pEncPara->stImage.stBufAddr[0].u32PhyAddr_C;

    if (pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR)
    {
        pEncIn->BusViV = pEncPara->stImage.stBufAddr[0].u32PhyAddr_Cr;
    }

    /****************get tunnel addr information**************/
    if (pEncPara->stImage.u32TunnelPhyAddr)
    {
        pEncPara->stRc.LowDlyMod = HI_TRUE;
        pEncIn->TunlCellAddr = pEncPara->stImage.u32TunnelPhyAddr;
    }
    else
    {
        pEncPara->stRc.LowDlyMod = HI_FALSE;
        pEncIn->TunlCellAddr = 0;
    }

    /****************get stride information**************/
    VENC_DRV_EflQueryChn_X_Stride(pEncIn, pEncPara);

#ifdef VENC_DPT_ONLY
    pEncIn->RStrideY  = D_VENC_ALIGN_UP(pEncPara->stImage.u32Width , 16);//HI_SYS_GET_STRIDE(pEncPara->stImage.u32Width);//D_VENC_ALIGN_UP(pEncPara->stImage.u32Width , VEDU_MMZ_ALIGN);   //16
#else
    pEncIn->RStrideY  = D_VENC_ALIGN_UP(pEncPara->stImage.u32Width , 16);
#endif
    pEncIn->RStrideC  = pEncIn->RStrideY;

    /****************get pts information**************/
    pEncIn->PTS0 = pEncPara->stImage.u32Pts;
    pEncIn->PTS1 = 0;
}

static HI_S32 VENC_DRV_EflQueryChn_X(HI_U32 u32ChnID, VeduEfl_EncIn_S *pEncIn)
{
    VeduEfl_EncPara_S* pEncPara = (VeduEfl_EncPara_S*)g_stVencChn[u32ChnID].hVEncHandle;
    if (pEncPara->bNotEnoughBuf != HI_TRUE)
    {

        if (GetLocalChannelInfo_X(pEncPara, u32ChnID) != HI_SUCCESS)
        {
            return HI_FAILURE;
        }
    }

    GetGlobalChannelInfo_X(pEncPara, pEncIn);

    return HI_SUCCESS;
}

static HI_S32 VENC_DRV_EflQueryChn_Y(HI_U32 u32ChnID, VeduEfl_EncIn_S *pEncIn)
{
    //HI_HANDLE hHd;
    //HI_S32 s32Ret = 0;
    VeduEfl_EncPara_S* pEncPara = (VeduEfl_EncPara_S*)g_stVencChn[u32ChnID].hVEncHandle;

    pEncPara->stStat.GetFrameNumTry++;
    if (!pEncPara->stSrcInfo.pfGetImage_OMX)
    { return HI_FAILURE; }
    if (HI_SUCCESS != (pEncPara->stSrcInfo.pfGetImage_OMX)(pEncPara->stSrcInfo.handle, &(pEncPara->stImage_OMX)))
    { return HI_FAILURE; }
    pEncPara->stStat.GetFrameNumOK++;

    pEncPara->stStat.u32RealSendInputRrmRate  = pEncPara->stRc.ViFrmRate;
    pEncPara->stStat.u32RealSendOutputFrmRate = pEncPara->stRc.VoFrmRate;

    /* video encoder does frame rate control by two value: input frame rate and target frame rate */
    /* input frame rate is calculated by timer mechanism accurately */
    /* target frame rate is input by user and can be changed dynamiclly */

    /* skip - frame rate ctrl */
    if (HI_SUCCESS
        != VENC_DRV_EflRcFrmRateCtrl( g_stVencChn[u32ChnID].hVEncHandle,pEncPara->stStat.PutFrameNumOK))
    {
        pEncPara->stStat.PutFrameNumTry++;

        VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS , &(pEncPara->stImage_OMX));
        pEncPara->stStat.MsgQueueNum++;
        pEncPara->stStat.PutFrameNumOK++;

        pEncPara->stHal.PTS0 = pEncPara->stImage_OMX.timestamp0;
        pEncPara->stHal.PTS1 = pEncPara->stImage_OMX.timestamp1;
        return HI_FAILURE;
    }

    pEncPara->stHal.YuvStoreType  = pEncPara->stImage_OMX.store_type;//VENC_STORE_SEMIPLANNAR;
    pEncPara->YuvSampleType = pEncPara->stImage_OMX.sample_type;//VENC_YUV_420;//Convert_PIX_Format(pEncPara->stImage.ePixFormat,1);
    pEncPara->stHal.PackageSel    = pEncPara->stImage_OMX.package_sel;//VENC_V_U;

    VENC_DRV_GetLastFrmInfo_OMX(pEncPara, pEncIn);
    return 0;
}

static VeduEfl_EncPara_S* VENC_DRV_EflQueryChn_H264( VeduEfl_EncIn_S* pEncIn )
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32StartQueryNo = 0;
    HI_S32 s32StartChnID   = 0;     /*this ID correspond to VeduChnCtx(class:VeduEfl_ChnCtx_S) */
    HI_U32 u32ChnID = 0;            /*this ID correspond to g_stVencChn(class:OPTM_VENC_CHN_S)*/
    VeduEfl_EncPara_S *pEncPara = HI_NULL;
    VEDU_LOCK_FLAG flag;
    VeduEfl_EncPara_S* hHd_ret = HI_NULL;

    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
    for (u32StartQueryNo = 0;u32StartQueryNo < HI_VENC_MAX_CHN;u32StartQueryNo++)
    {
        D_VENC_GET_CHN_FROM_TAB(s32StartChnID,u32StartQueryNo);

        if ( INVAILD_CHN_FLAG == s32StartChnID )
        {
            continue;
        }

        D_VENC_GET_CHN(u32ChnID,VeduChnCtx[s32StartChnID].EncHandle);

        if (u32ChnID >= HI_VENC_MAX_CHN)
        {
            VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
            return HI_NULL;
        }

        pEncPara = (VeduEfl_EncPara_S *) VeduChnCtx[s32StartChnID].EncHandle;

        if( HI_INVALID_HANDLE == pEncPara->stSrcInfo.handle )
        {
            pEncPara->stSrcInfo.handle = g_stVencChn[u32ChnID].hUsrHandle;
        }

        Ret = STRM_CheckBufferSize(pEncPara->hStrmMng, pEncPara->stHal.StrmBufSize, pEncPara->CurStrmBufSize);

        if (Ret != HI_SUCCESS)
        {
            pEncPara->stStat.CheckBufSizeNumFail++;
            continue;
        }

       /* this QueryChn just for H264*/
    #ifdef VENC_SUPPORT_JPGE
       if (HI_INVALID_HANDLE != g_stVencChn[u32ChnID].hJPGE)
       {
           continue;
       }
    #endif

       if (g_stVencChn[u32ChnID].bOMXChn)
       {
            VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
            if (HI_SUCCESS != VENC_DRV_EflQueryChn_Y(u32ChnID, pEncIn))
            {
               VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
               continue;
            }
            VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
       }
       else
       {
          if (HI_SUCCESS != VENC_DRV_EflQueryChn_X(u32ChnID, pEncIn))
            { continue;}
        }

       VENC_DRV_DbgLowdelayEvent(u32ChnID,EVENT_VENC_FRM_IN,pEncPara->stImage.u32FrameIndex,pEncPara->stImage.hTunnelSrc);

        pEncPara->WaitingIsr = 1;
        break; /* find channel:s32StartChnID  to enc */
    }

    if (HI_VENC_MAX_CHN != u32StartQueryNo)
    {
       VENC_DRV_EflSortPriority_2(PriorityTab[1][u32StartQueryNo]);
    }

    if ((s32StartChnID >= 0)&&(s32StartChnID < HI_VENC_MAX_CHN))
    {
       hHd_ret = VeduChnCtx[s32StartChnID].EncHandle;
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    if (HI_VENC_MAX_CHN == u32StartQueryNo)
    {
        return HI_NULL;
    }
    else
    {
        if (g_stVencChn[u32ChnID].stProcWrite.bSaveYUVFileRun && pEncPara && (g_stVencChn[u32ChnID].enSrcModId < HI_ID_BUTT))
        {
           VENC_DRV_DbgWriteYUV(&pEncPara->stImage, g_stVencChn[u32ChnID].stProcWrite.YUVFileName);
        }
        return hHd_ret;
    }
}

#ifdef VENC_SUPPORT_JPGE
static VeduEfl_EncPara_S* VENC_DRV_EflQueryChn_JPEG( VeduEfl_EncIn_S* pEncIn )
{
    HI_U32 u32StartQueryNo = 0;
    HI_S32 s32StartChnID   = 0;     /*this ID correspond to VeduChnCtx(class:VeduEfl_ChnCtx_S) */
    HI_U32 u32ChnID = 0;            /*this ID correspond to g_stVencChn(class:OPTM_VENC_CHN_S)*/
    VeduEfl_EncPara_S *pEncPara = HI_NULL;
    VEDU_LOCK_FLAG flag;
    VeduEfl_EncPara_S* hHd_ret = HI_NULL;

    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);

    for (u32StartQueryNo = 0;u32StartQueryNo < HI_VENC_MAX_CHN;u32StartQueryNo++)
    {
        D_VENC_GET_CHN_FROM_TAB(s32StartChnID,u32StartQueryNo);
        if ( INVAILD_CHN_FLAG == s32StartChnID )
        {
            continue;
        }
        D_VENC_GET_CHN(u32ChnID,VeduChnCtx[s32StartChnID].EncHandle);
        if (u32ChnID >= HI_VENC_MAX_CHN)
        {
            VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
            return HI_NULL;
        }
        pEncPara = (VeduEfl_EncPara_S *) VeduChnCtx[s32StartChnID].EncHandle;
        if( HI_INVALID_HANDLE == pEncPara->stSrcInfo.handle )
        {
            pEncPara->stSrcInfo.handle = g_stVencChn[u32ChnID].hUsrHandle;
        }

       /* this QueryChn just for jpeg*/
       if (HI_INVALID_HANDLE == g_stVencChn[u32ChnID].hJPGE)
       {
           continue;
       }
       if (g_stVencChn[u32ChnID].bOMXChn)
       {
            if (HI_SUCCESS != VENC_DRV_EflQueryChn_Y(u32ChnID, pEncIn))
            { continue; }
       }
       else
        {
            if (HI_SUCCESS != VENC_DRV_EflQueryChn_X(u32ChnID, pEncIn))
            { continue; }
       }

       VENC_DRV_DbgLowdelayEvent(u32ChnID,EVENT_VENC_FRM_IN,pEncPara->stImage.u32FrameIndex,pEncPara->stImage.hTunnelSrc);

        pEncPara->WaitingIsr_jpge = 1;
        break; /* find channel:s32StartChnID  to enc */
    }

    if (HI_VENC_MAX_CHN != u32StartQueryNo)
    {
       VENC_DRV_EflSortPriority_2(PriorityTab[1][u32StartQueryNo]);
    }

    if ((s32StartChnID >= 0)&&(s32StartChnID < HI_VENC_MAX_CHN))
    {
       hHd_ret = VeduChnCtx[s32StartChnID].EncHandle;
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

    if (HI_VENC_MAX_CHN == u32StartQueryNo)
    {
        return HI_NULL;
    }
    else
    {
        if (g_stVencChn[u32ChnID].stProcWrite.bSaveYUVFileRun && pEncPara && (g_stVencChn[u32ChnID].enSrcModId < HI_ID_BUTT))
        {
           VENC_DRV_DbgWriteYUV(&pEncPara->stImage, g_stVencChn[u32ChnID].stProcWrite.YUVFileName);
        }

        if (pEncIn->TunlCellAddr != 0)
        {
            HI_ERR_VENC("Warning!!!!! JPEG encoder not support lowdelay!!!The output maybe error!\n");
        }

        return hHd_ret;
    }
}
#endif

#ifdef __VENC_FREQ_DYNAMIC__
static HI_S32 VENC_DRV_EflCurrentCap(HI_S32 *pClkSel)
{
    HI_U32 u32ChnID = 0;
    HI_U32 u32TotalMB = 0,u32MBNum = 0;
    HI_U32 WidthInMb = 0;
    HI_U32 HeightInMb= 0;
    for (u32ChnID = 0; u32ChnID < HI_VENC_MAX_CHN; u32ChnID++)
    {
       if (g_stVencChn[u32ChnID].bEnable)
       {
           WidthInMb  = (g_stVencChn[u32ChnID].stChnUserCfg.u32Width + 15) >> 4;
           HeightInMb = (g_stVencChn[u32ChnID].stChnUserCfg.u32Height+ 15) >> 4;
           u32MBNum = WidthInMb * HeightInMb * g_stVencChn[u32ChnID].stChnUserCfg.u32TargetFrmRate;
           u32TotalMB += u32MBNum;
       }
    }

    if (u32TotalMB < 125000) /* 0.5s = 400*(MB)*(1/100MHZ)   MB=125000*/
    {
        *pClkSel = VENC_FREQUENCY_100M;
    }
    else if (u32TotalMB < 187500)
    {
        *pClkSel = VENC_FREQUENCY_150M;
    }
    else
    {
        *pClkSel = VENC_FREQUENCY_200M;
    }
    return HI_SUCCESS;
}
#endif

static HI_BOOL bFirstSlc = HI_TRUE;

static HI_VOID Venc_SmmuFaultCheck(VOID)
{
#ifdef HI_SMMU_SUPPORT
    VENC_HAL_READ_SMMU_S ReadBack;

    memset(&ReadBack, 0, sizeof(VENC_HAL_READ_SMMU_S));

    VENC_HAL_ReadReg_Smmu(&ReadBack);

    if (ReadBack.TlbMissStatNs)
    {
        HI_ERR_VENC("%s,%d, SMMU Table miss error!\n", __func__, __LINE__);
    }

    if (ReadBack.PtwTransStatNs)
    {
        HI_ERR_VENC("%s,%d, SMMU Table pre get error!\n", __func__, __LINE__);
    }

    /*for not safe mode*/
    if (ReadBack.TlbInvalidStatNsRd)
    {
        HI_ERR_VENC("SMMU_READ_ERR MODULE : %s NSSTATE : %#x RdAddr:%#x\n", "HI_MOD_VENC", ReadBack.TlbInvalidStatNsRd, ReadBack.FaultAddrRdNs);
    }

    if (ReadBack.TlbInvalidStatNsWr)
    {

        HI_ERR_VENC("SMMU_WRITE_ERR MODULE : %s NSSTATE : %#x WrAddr:%#x\n", "HI_MOD_VENC", ReadBack.TlbInvalidStatNsWr, ReadBack.FaultAddrWrNs);
    }
    /*for safe mode*/
    if (ReadBack.TlbInvalidStatSRd)
    {
        HI_ERR_VENC("SMMU_READ_ERR MODULE : %s NSSTATE : %#x RdAddr:%#x\n", "HI_MOD_VENC", ReadBack.TlbInvalidStatSRd, ReadBack.FaultAddrRdS);
    }

    if (ReadBack.TlbInvalidStatSWr)
    {
        HI_ERR_VENC("SMMU_WRITE_ERR MODULE : %s NSSTATE : %#x WrAddr:%#x\n", "HI_MOD_VENC", ReadBack.TlbInvalidStatSWr, ReadBack.FaultAddrWrS);
    }
#endif
    return;
}


static HI_VOID VENC_DRV_RcIFrmInsertForLargeImb(VeduEfl_EncPara_S *pEncPara)
{
    HI_U32 ImbRatio = 0;
    HI_U32 Mbtotal = 0;

    Mbtotal =  pEncPara->stRc.PicWidth * pEncPara->stRc.PicHeight / (16 * 16);

    if (Mbtotal != 0)
    {
        ImbRatio = pEncPara->stRc.NumIMBCurFrm * 1000 / Mbtotal;
    }

#ifdef AUTO_CATCH_I_FRAME
    if (pEncPara->ICatchEnable)
    {
        pEncPara->FrmCnt++;

        if (pEncPara->FrmCnt > 30)
        {
            HI_U32 ImbRatioAvg = 0;
            HI_U32 diff = 0, i = 0;
            ImbRatioAvg =  VENC_DRV_EflRcAverage(pEncPara->stRc.IMBRatioCurScen, 6);
            ImbRatioAvg = D_VENC_RC_MAX(ImbRatioAvg, 1);

            diff = D_VENC_RC_ABS(ImbRatioAvg, ImbRatio);

            if ((ImbRatio > ImbRatioAvg) && ((diff * 100 / ImbRatioAvg) > 200) && (ImbRatio > 500) )
            {
                pEncPara->InterFrmCnt = pEncPara->stRc.Gop - 1;
                pEncPara->stRc.IFrmInsertFlag = 1;
                pEncPara->stRc.RcStart = 1;

                for (i = 0; i < 6; i++)
                {
                    pEncPara->stRc.IMBRatioCurScen[i] = 0;
                }
            }
            else
            {
                D_VENC_RC_UPDATE(pEncPara->stRc.IMBRatioCurScen, ImbRatio);
            }
        }
        else
        {
            if (pEncPara->FrmCnt != 1)   //if it is I frame not update IMBRatioCurScen.
            {
                D_VENC_RC_UPDATE(pEncPara->stRc.IMBRatioCurScen, ImbRatio);
            }
        }
    }
#endif

    return;
}

static HI_VOID VENC_DRV_EncNextFrm(HI_U32 u32VeChn, VeduEfl_EncIn_S *pEncIn)
{
    VeduEfl_EncPara_S* pEncPara;

    if (((!g_stVencChn[u32VeChn].stProcWrite.bSaveYUVFileRun) || (g_stVencChn[u32VeChn].enSrcModId == HI_ID_BUTT))
        && (g_stVencChn[u32VeChn].bOMXChn == HI_FALSE))
    {
        /* next frame to encode */
        pEncPara = VENC_DRV_EflQueryChn_H264( pEncIn );

        if (pEncPara != NULL )
        {
            VeduIpCtx.IpFree = 0;
            VeduIpCtx.CurrHandle = pEncPara;
            if (VENC_DRV_EflStartOneFrameVenc(pEncPara, pEncIn ) != HI_SUCCESS)
            {
                VeduIpCtx.IpFree = 1;
                VENC_DRV_BoardDeinit();

                return;
            }

            VENC_DRV_EflCfgRegVenc(pEncPara);
        }
        else
        {
            VeduIpCtx.IpFree = 1;
            VENC_DRV_BoardDeinit();
        }
    }
    else
    {
        VeduIpCtx.IpFree = 1;
        VENC_DRV_BoardDeinit();
    }

    return;
}

static HI_VOID Venc_ISR( HI_VOID )
{
    VeduEfl_EncIn_S EncIn;
    HI_U32 u32VeChn;
    VeduEfl_EncPara_S *pEncPara;
    VENC_HAL_READ_S ReadBack;

    D_VENC_GET_CHN(u32VeChn, VeduIpCtx.CurrHandle);
    if (u32VeChn >= HI_VENC_MAX_CHN)
    {
       return;
    }

    pEncPara = (VeduEfl_EncPara_S *) VeduIpCtx.CurrHandle;

    Venc_SmmuFaultCheck();

    memset(&ReadBack, 0, sizeof(ReadBack));
    VENC_HAL_ReadReg(&ReadBack);

    if (ReadBack.VencTimeOut)
    {
        HI_INFO_VENC("VENC timeout interrupt!! lowdelay= %d\n",pEncPara->stRc.LowDlyMod);

        VENC_HAL_ClearInt(INTERRUPT_TYPE_TIMEOUT);
        VENC_PDT_ResetHardware();
        VENC_PDT_OpenHardware();

        pEncPara->WaitingIsr = 0;
        VeduIpCtx.IpFree = 1;
        /* release image encoded */
        {
            pEncPara->stStat.PutFrameNumTry++;

            if (pEncPara->OMXChn)
            {
                VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS, &pEncPara->stImage_OMX);
                pEncPara->stStat.MsgQueueNum++;
            }
            else
            {
                (pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &pEncPara->stImage);
            }

            pEncPara->stStat.PutFrameNumOK++;

            if ((!pEncPara->stRc.LowDlyMod) || (!pEncPara->stHal.SlcSplitEn))
            {
                VENC_DRV_DbgLowdelayEvent(u32VeChn, EVENT_VENC_FRM_OUT, pEncPara->stImage.u32FrameIndex, pEncPara->stImage.hTunnelSrc);
            }

            bFirstSlc = HI_TRUE;
        }
    }

    if (ReadBack.VencSliceInt)
    {
          VENC_DRV_EflGetReadBackData(&ReadBack, &pEncPara->stHal, &pEncPara->stRc);

         if (bFirstSlc)
         {
            VENC_DRV_DbgLowdelayEvent(u32VeChn,EVENT_VENC_FRM_OUT, pEncPara->stImage.u32FrameIndex,pEncPara->stImage.hTunnelSrc);
            bFirstSlc = HI_FALSE;
         }

         VENC_DRV_EflEndOneSliceVenc( VeduIpCtx.CurrHandle );

         VENC_HAL_ClearInt(INTERRUPT_TYPE_SLICE_END);
    }

    if (ReadBack.VencEndOfPic)
    {
         //printk("%s,%d, Frm Isr OK\n\n",__func__,__LINE__);
      #ifdef __VENC_DRV_DBG__
         if (Isr_ID < 100)
         {
             HI_DRV_SYS_GetTimeStampMs(&TmpTime_dbg[Isr_ID][2]);
             Isr_ID++;
         }
      #endif

         {
            VENC_DRV_EflGetReadBackData(&ReadBack, &pEncPara->stHal, &pEncPara->stRc);

            VENC_HAL_ClearInt(INTERRUPT_TYPE_ALL);

            /* add for oversized frame recoding */
            if (pEncPara->stRc.PicBits != 0)
            {
                pEncPara->stStat.RateControlRatio = VENC_DRV_CalRCRatio(pEncPara->stRc.InstBitsSum, pEncPara->stRc.BitRate);
                VEDU_DRV_RCUpdateInfo(&pEncPara->stRc);

            #if RC_RECODE_USE
                if (VEDU_DRV_RCProcessOfRecoding(pEncPara, &EncIn) == HI_SUCCESS)
                {
                    return;
                }
            #endif
            }

        pEncPara->stStat.PutFrameNumTry++;

        if (pEncPara->OMXChn)
        {
            VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_INPUT_DONE, HI_SUCCESS, &pEncPara->stImage_OMX);
            pEncPara->stStat.MsgQueueNum++;
#ifdef __VENC_DRV_DBG__

            if (PutMsg_EBD_ID < 100)
            {
                HI_DRV_SYS_GetTimeStampMs(&TmpTime_dbg[PutMsg_EBD_ID][3]);
                PutMsg_EBD_ID++;
            }

#endif
        }
        else
        {
            (pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &pEncPara->stImage);
        }

        pEncPara->stStat.PutFrameNumOK++;
        pEncPara->WaitingIsr = 0;

        if ((!pEncPara->stRc.LowDlyMod) || (!pEncPara->stHal.SlcSplitEn))
        {
            VENC_DRV_DbgLowdelayEvent(u32VeChn, EVENT_VENC_FRM_OUT, pEncPara->stImage.u32FrameIndex, pEncPara->stImage.hTunnelSrc);
        }

        bFirstSlc = HI_TRUE;
    }

        gencodeframe = 1;
        wake_up(&gEncodeFrame);

        VENC_DRV_EflEndOneFrameVenc( VeduIpCtx.CurrHandle );

        VENC_DRV_RcIFrmInsertForLargeImb(pEncPara);

        VENC_DRV_EncNextFrm(u32VeChn, &EncIn);

        VENC_DRV_OsalGiveEvent(&g_VencWait_Stream[u32VeChn]);

        if (g_stVencChn[u32VeChn].bOMXChn)
        {
            VENC_DRV_OsalGiveEvent(&g_VENC_Event_stream);
        }
    }
}

HI_S32 VEDU_DRV_RCProcessOfRecoding(VeduEfl_EncPara_S *pEncPara, VeduEfl_EncIn_S *EncIn)
{
    STRMMNG_INPUT_INFO_S stInputInfo;
    STRMMNG_STREAM_INFO_S stStreamInfo;

    if ((VEDU_DRV_RCIsNeedRecoding(&pEncPara->stRc) != HI_SUCCESS)
        ||(VEDU_DRV_RCStartQPChange(&pEncPara->stRc) != HI_SUCCESS)
        ||(VENC_DRV_GetEncodePara(pEncPara, EncIn) != HI_SUCCESS))
    {
        pEncPara->stRc.Recode = 0;

        return HI_FAILURE;
    }
    else
    {
        pEncPara->stRc.H264FrmNum--;
        pEncPara->stRc.RcnIdx = !pEncPara->stRc.RcnIdx;
        pEncPara->stRc.PmeInfoIdx = pEncPara->stRc.PmeInfoIdx == 0 ? 2 : pEncPara->stRc.PmeInfoIdx - 1;

        SetStreamInfo(pEncPara, &stStreamInfo);
        SetStrmMngInputInfo(pEncPara, &stInputInfo);
        STRM_PutBufferForRecode(pEncPara->hStrmMng, &stInputInfo, &stStreamInfo);

        if (VENC_DRV_EflStartOneFrameVenc(pEncPara, EncIn) == HI_SUCCESS)
        {
            VeduIpCtx.IpFree = 0;
            pEncPara->stStat.RecodeNum++;
            VENC_DRV_EflCfgRegVenc(pEncPara);

            return HI_SUCCESS;
        }
        else
        {
            pEncPara->stRc.H264FrmNum++;
            pEncPara->stRc.RcnIdx = !pEncPara->stRc.RcnIdx;
            pEncPara->stRc.PmeInfoIdx = pEncPara->stRc.PmeInfoIdx == 2 ? 0 : pEncPara->stRc.PmeInfoIdx + 1;
            pEncPara->stRc.Recode = 0;
            HI_ERR_VENC("RECODING START FRAME FAILURE!");

            return HI_FAILURE;
        }
    }
}

static HI_VOID VENC_DRV_GetLastFrmInfo(VeduEfl_EncPara_S* pEncPara, VeduEfl_EncIn_S* pEncIn)
{
    if (pEncPara->stImage.u32TunnelPhyAddr)      //待明确!!
    {
        pEncPara->stRc.LowDlyMod = HI_TRUE;
        pEncIn->TunlCellAddr = pEncPara->stImage.u32TunnelPhyAddr;
    }
    else
    {
        pEncPara->stRc.LowDlyMod = HI_FALSE;
        pEncIn->TunlCellAddr = 0;
    }

    pEncIn->BusViY = pEncPara->stImage.stBufAddr[0].u32PhyAddr_Y;
    pEncIn->BusViC = pEncPara->stImage.stBufAddr[0].u32PhyAddr_C;

    if (pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR)
    {
        pEncIn->BusViV = pEncPara->stImage.stBufAddr[0].u32PhyAddr_Cr;//pEncPara->stImage.u32CAddr;      //目前帧信息结构体缺少该结构,planer格式时需要；
    }

    if ((pEncPara->stHal.YuvStoreType == VENC_STORE_SEMIPLANNAR) && (pEncPara->YuvSampleType == VENC_YUV_422))  /*==强制把SEMIPLANAR_422 当semiplaner 420编码*/
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
        pEncIn->ViCStride = pEncPara->stImage.stBufAddr[0].u32Stride_C * 2;
    }
    else if ((pEncPara->stHal.YuvStoreType == VENC_STORE_PACKAGE) && (pEncPara->YuvSampleType == VENC_YUV_422))
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
    }
    else if ((pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR) && (pEncPara->YuvSampleType == VENC_YUV_420))
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
        pEncIn->ViCStride = pEncPara->stImage.stBufAddr[0].u32Stride_C;
    }
    else
    {
        pEncIn->ViYStride = pEncPara->stImage.stBufAddr[0].u32Stride_Y;
        pEncIn->ViCStride = pEncPara->stImage.stBufAddr[0].u32Stride_C;
    }

    pEncIn->RStrideY  = D_VENC_ALIGN_UP(pEncPara->stImage.u32Width , 16);
    pEncIn->RStrideC  = pEncIn->RStrideY;

    pEncIn->PTS0 = pEncPara->stImage.u32Pts;
    pEncIn->PTS1 = 0;

    return ;
}

static HI_VOID VENC_DRV_GetLastFrmInfo_OMX(VeduEfl_EncPara_S* pEncPara, VeduEfl_EncIn_S* pEncIn)
{
    pEncPara->stRc.LowDlyMod = HI_FALSE;
    pEncIn->TunlCellAddr = 0;

    if (pEncPara->stImage_OMX.MetaDateFlag)   //storeMetaData case
    {
        pEncIn->BusViY = pEncPara->stImage_OMX.stMetaData.bufferaddr_Phy + pEncPara->stImage_OMX.offset; //pEncPara->stImage.stBufAddr[0].u32PhyAddr_Y;
    }
    else
    {
        pEncIn->BusViY = pEncPara->stImage_OMX.bufferaddr_Phy + pEncPara->stImage_OMX.offset; //pEncPara->stImage.stBufAddr[0].u32PhyAddr_Y;
    }

    pEncIn->BusViC = pEncIn->BusViY + pEncPara->stImage_OMX.offset_YC;//pEncPara->stImage.stBufAddr[0].u32PhyAddr_C;

    if (pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR)
    {
        pEncIn->BusViV = pEncIn->BusViY + pEncPara->stImage_OMX.offset_YCr;//pEncPara->stImage_OMX.strideC*pEncPara->stImage_OMX.picHeight /2;//pEncPara->stImage.u32CAddr;      //目前帧信息结构体缺少该结构,planer格式时需要；
    }

    if ((pEncPara->stHal.YuvStoreType == VENC_STORE_SEMIPLANNAR) && (VENC_YUV_422 == pEncPara->YuvSampleType)) /*==强制把SEMIPLANAR_422 当semiplaner 420编码*/
    {
        pEncIn->ViYStride = pEncPara->stImage_OMX.strideY;
        pEncIn->ViCStride = pEncPara->stImage_OMX.strideC * 2;
        pEncPara->stStat.u32FrameType = VENC_SEMIPLANNAR_422;
    }
    else if ((pEncPara->stHal.YuvStoreType == VENC_STORE_PACKAGE) && (VENC_YUV_422 == pEncPara->YuvSampleType))
    {
        pEncIn->ViYStride = pEncPara->stImage_OMX.strideY;

        switch (pEncPara->stHal.PackageSel)
        {
            case VENC_PACKAGE_UY0VY1:
                pEncPara->stStat.u32FrameType = VENC_PACKAGE_422_UYVY;
                break;

            case VENC_PACKAGE_Y0UY1V:
                pEncPara->stStat.u32FrameType = VENC_PACKAGE_422_YUYV;
                break;

            case VENC_PACKAGE_Y0VY1U:
                pEncPara->stStat.u32FrameType = VENC_PACKAGE_422_YVYU;
                break;

            default:
                pEncPara->stStat.u32FrameType = VENC_UNKNOW;
                break;
        }
    }
    else if ((pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR) && (VENC_YUV_420 == pEncPara->YuvSampleType))
    {
        pEncIn->ViYStride = pEncPara->stImage_OMX.strideY;
        pEncIn->ViCStride = pEncPara->stImage_OMX.strideC;
        pEncPara->stStat.u32FrameType = VENC_PLANNAR_420;
    }
    else
    {
        pEncIn->ViYStride = pEncPara->stImage_OMX.strideY;
        pEncIn->ViCStride = pEncPara->stImage_OMX.strideC;

        if ((pEncPara->stHal.YuvStoreType == VENC_STORE_PLANNAR) && (VENC_YUV_422 == pEncPara->YuvSampleType))
        {
            pEncPara->stStat.u32FrameType = VENC_PLANNAR_422;
        }
        else if ((pEncPara->stHal.YuvStoreType == VENC_STORE_SEMIPLANNAR) && (VENC_YUV_420 == pEncPara->YuvSampleType))
        {
            if (pEncPara->stHal.PackageSel == 0)
            {
                pEncPara->stStat.u32FrameType = VENC_SEMIPLANNAR_420_VU;
            }
            else
            {
                pEncPara->stStat.u32FrameType = VENC_SEMIPLANNAR_420_UV;
            }
        }

    }

    pEncIn->RStrideY  = D_VENC_ALIGN_UP(pEncPara->stRc.PicWidth, 16);
    pEncIn->RStrideC  = pEncIn->RStrideY;

    pEncIn->PTS0 = pEncPara->stImage_OMX.timestamp0;
    pEncIn->PTS1 = pEncPara->stImage_OMX.timestamp1;

    return;
}

HI_S32 VENC_DRV_GetEncodePara(VeduEfl_EncPara_S* pEncPara, VeduEfl_EncIn_S* pEncIn)
{
    if (pEncPara->OMXChn)
    {
        VENC_DRV_GetLastFrmInfo_OMX(pEncPara, pEncIn);
    }
    else
    {
        VENC_DRV_GetLastFrmInfo(pEncPara, pEncIn);
    }

    return HI_SUCCESS;
}

static HI_VOID VENC_DRV_EflTask( HI_VOID )
{
    HI_S32 s32Ret = 0;
    VeduEfl_EncIn_S EncIn;

#ifdef VENC_SUPPORT_JPGE
    Venc2Jpge_EncIn_S JpgeEncIn;
    HI_BOOL  bJpgeBufFull = HI_FALSE;
#endif

    VeduEfl_EncPara_S *pEncPara = HI_NULL;
    HI_U32 i = 0;
    HI_U32 u32ChnID = 0;
    HI_BOOL bTmpValue = HI_FALSE;
    VeduIpCtx.TaskRunning = 1;

    /* 初始化等待队列头*/
    VENC_DRV_OsalInitEvent(&g_VENC_Event, 0);

    /* wait for venc start */
    while (!VeduIpCtx.StopTask)
    {
        for (i = 0; i < HI_VENC_MAX_CHN; i++)
        {
            bTmpValue |= g_stVencChn[i].bEnable;
        }

        if (HI_FALSE == bTmpValue)
        {
            msleep(10);
        }
        else
        {
            break;
        }
    }

    /* find valid venc handle */
    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        pEncPara = (VeduEfl_EncPara_S *)g_stVencChn[i].hVEncHandle;
        if ((HI_NULL == pEncPara))
        {
            continue;
        }
    }

    while (!VeduIpCtx.StopTask)
    {
        /* vedu_ip for h264*/
        if (VeduIpCtx.IpFree)
        {
            /* if ipfree, don't irqlock */
            // VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
            memset(&EncIn, 0, sizeof(VeduEfl_EncIn_S));
            pEncPara = VENC_DRV_EflQueryChn_H264( &EncIn );
            //VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );

            if (pEncPara != NULL)
            {
                D_VENC_GET_CHN(u32ChnID, pEncPara);

                if (u32ChnID >= HI_VENC_MAX_CHN)
                {
                    continue;
                }

                if (HI_INVALID_HANDLE == g_stVencChn[u32ChnID].hJPGE)
                {
                    if (VENC_DRV_EflStartOneFrameVenc(pEncPara, &EncIn) != HI_SUCCESS)
                    {
                        continue;
                    }

                    VeduIpCtx.CurrHandle = pEncPara;
                    VeduIpCtx.IpFree = 0;

                    VENC_DRV_EflCfgRegVenc( pEncPara );
                }
            }
        }


#ifdef VENC_SUPPORT_JPGE
        {
            pEncPara = VENC_DRV_EflQueryChn_JPEG(&EncIn);

            if (pEncPara != NULL)
            {
                D_VENC_GET_CHN(u32ChnID, pEncPara);

                if (u32ChnID >= HI_VENC_MAX_CHN)
                {
                    continue;
                }

                if (HI_INVALID_HANDLE != g_stVencChn[u32ChnID].hJPGE)  /*JPGE CHANNEL*/
                {
                    pEncPara->stHal.PTS0 = EncIn.PTS0;
                    pEncPara->stHal.PTS1 = EncIn.PTS1;

                    JPGE_MakeJFIF(pEncPara);

                    JpgeEncIn.BusViY = EncIn.BusViY;
                    JpgeEncIn.BusViC = EncIn.BusViC;
                    JpgeEncIn.BusViV = EncIn.BusViV;
                    JpgeEncIn.ViYStride = EncIn.ViYStride;
                    JpgeEncIn.ViCStride = EncIn.ViCStride;

                    JpgeEncIn.StrmBufAddr   = pEncPara->stHal.StrmBufAddr;
                    JpgeEncIn.StrmBufRpAddr = pEncPara->stHal.StrmBufRpAddr;
                    JpgeEncIn.StrmBufWpAddr = pEncPara->stHal.StrmBufWpAddr;
                    JpgeEncIn.StrmBufSize = pEncPara->stHal.StrmBufSize;
                    JpgeEncIn.Vir2BusOffset = pEncPara->Vir2BusOffset;
                    JpgeEncIn.pJpgeYqt      = pEncPara->pJpgeYqt;
                    JpgeEncIn.pJpgeCqt      = pEncPara->pJpgeCqt;
                    JpgeEncIn.FrameHeight   = pEncPara->stRc.PicHeight;
                    JpgeEncIn.FrameWidth    = pEncPara->stRc.PicWidth;
                    JpgeEncIn.YuvSampleType = pEncPara->YuvSampleType;
                    JpgeEncIn.PTS0          = EncIn.PTS0;

                    switch (pEncPara->stHal.YuvStoreType)
                    {
                        case VENC_STORE_SEMIPLANNAR:
                            JpgeEncIn.YuvStoreType = JPGE_STORE_SEMIPLANNAR;
                            break;

                        case VENC_STORE_PACKAGE:
                            JpgeEncIn.YuvStoreType = JPGE_STORE_PACKAGE;
                            break;

                        case VENC_STORE_PLANNAR:
                            JpgeEncIn.YuvStoreType = JPGE_STORE_PLANNAR;
                            break;

                        default:
                            JpgeEncIn.YuvStoreType = JPGE_STORE_SEMIPLANNAR;
                            break;
                    }

                    JpgeEncIn.PackageSel = pEncPara->stHal.PackageSel;
                    JpgeEncIn.RotationAngle = pEncPara->RotationAngle;
                    s32Ret = pJpgeFunc->pfnJpgeEncodeFrame(g_stVencChn[u32ChnID].hJPGE, &JpgeEncIn, &bJpgeBufFull);

                    if (s32Ret != HI_SUCCESS)
                    {
                        JPGE_RemoveJFIF(pEncPara);
                        pEncPara->stStat.ErrCfgSkip++;
                    }
                    else if (bJpgeBufFull)
                    {
                        /*remove the heard of JFIF before*/
                        JPGE_RemoveJFIF(pEncPara);
                        pEncPara->stStat.TooFewBufferSkip++;
                    }
                    else
                    {
                        VENC_DRV_EflEndOneFrameJpge(pEncPara);
                    }

                    /*release the Img*/
                    pEncPara->stStat.PutFrameNumTry++;
                    (pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &pEncPara->stImage);

                    pEncPara->stRc.RcStart  = 0;
                    pEncPara->TrCount -= pEncPara->stRc.ViFrmRate;
                    pEncPara->stStat.PutFrameNumOK++;

                    //VeduIpCtx.IpFree = 1;  /*NEXT*/

                    pEncPara->WaitingIsr_jpge = 0;
                }
            }

        }
#endif
        /* if ipfree, sleep */
        s32Ret = VENC_DRV_OsalWaitEvent(&g_VENC_Event, msecs_to_jiffies(30));

        if (0 != s32Ret)
        {
            HI_INFO_VENC("wait time out!\n");
        }

        //msleep(10*1000);
    }

    VeduIpCtx.TaskRunning = 0;
    return;
}

static VeduEfl_EncPara_S* VENC_DRV_EflQueryChn_Stream(venc_msginfo* pMsgInfo)
{
    HI_U32 u32StartQueryNo = 0;
    HI_S32 s32StartChnID   = 0;     /*this ID correspond to VeduChnCtx(class:VeduEfl_ChnCtx_S) */
    HI_U32 u32ChnID = 0;            /*this ID correspond to g_stVencChn(class:OPTM_VENC_CHN_S)*/
    VEDU_LOCK_FLAG flag;
    VeduEfl_EncPara_S *pEncPara = NULL;
    VeduEfl_EncPara_S* hVencHandle = HI_NULL;
    queue_data_s Queue_Data;

    VENC_DRV_OsalLock(VeduIpCtx.pChnLock, &flag);
    for (u32StartQueryNo = 0; u32StartQueryNo < HI_VENC_MAX_CHN; u32StartQueryNo++)
    {
        D_VENC_GET_CHN_FROM_TAB(s32StartChnID,u32StartQueryNo);
        if ( INVAILD_CHN_FLAG == s32StartChnID )
        { continue; }
        D_VENC_GET_CHN(u32ChnID, VeduChnCtx[s32StartChnID].EncHandle);
        if (u32ChnID >= HI_VENC_MAX_CHN)
        {
            VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag );
            return HI_NULL;
        }

        if (!g_stVencChn[u32ChnID].bOMXChn)
        { continue; }

        hVencHandle = VeduChnCtx[s32StartChnID].EncHandle;
        pEncPara    = hVencHandle;

        pEncPara->stStat.GetStreamNumTry++;

        if( STRM_GetWrittenLength(pEncPara->hStrmMng) > 0)
        {
            if( VENC_DRV_MngQueueEmpty(pEncPara->StreamQueue_OMX))
            { continue; }

            VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag);
            if( VENC_DRV_MngDequeue(pEncPara->StreamQueue_OMX, &Queue_Data))
            {
                VENC_DRV_OsalLock(VeduIpCtx.pChnLock, &flag);
                continue;
            }
            VENC_DRV_OsalLock(VeduIpCtx.pChnLock, &flag);

            pEncPara->StreamQueue_OMX->bStrmLock = 1;   //mutex with the stop processing
            pEncPara->stStat.StreamQueueNum--;
            if (Queue_Data.bToOMX)
            {
                memcpy(pMsgInfo,&(Queue_Data.unFrmInfo.msg_info_omx),sizeof(venc_msginfo));
            }
            else
            {
                HI_ERR_VENC("Err:output stream queue not match with Omx Component!\n");
                continue;
            }
            pEncPara->stStat.GetStreamNumOK++;
            break; /* find channel:s32StartChnID  have buffer to fill */
        }
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag);

    if (HI_VENC_MAX_CHN == u32StartQueryNo)
    {
        return HI_NULL;
    }
    else
    {
        return hVencHandle;
    }
}

static HI_VOID H264_GetStrmBufFlag(HI_U32 NaluType, HI_BOOL *pFirstNal2Send, venc_user_buf *pStreamBuf)
{
    switch (NaluType)
    {
        case H264_NALU_TYPE_IDR:
            {
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_SYNCFRAME;
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
            }
            break;

        case H264_NALU_TYPE_P:
            pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
            break;

        case H264_NALU_TYPE_PPS:
            if (*pFirstNal2Send)
            {
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_STARTTIME;
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_CODECCONFIG;
                *pFirstNal2Send = HI_FALSE;
            }
            else
            {
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_EXTRADATA;
            }
            break;

        default:
            HI_ERR_VENC("Nalu.NaluType(%d) is invalid\n",NaluType);
            break;
    }
}

static HI_VOID H265_GetStrmBufFlag(HI_U32 NaluType, HI_BOOL *pFirstNal2Send, venc_user_buf *pStreamBuf)
{
    switch (NaluType)
    {
        case H265_NALU_TYPE_IDR:
            {
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_SYNCFRAME;
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
            }
            break;

        case H265_NALU_TYPE_P:
            pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_ENDOFFRAME;
            break;

        case H265_NALU_TYPE_PPS:
            if (*pFirstNal2Send)
            {
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_STARTTIME;
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_CODECCONFIG;
                *pFirstNal2Send = HI_FALSE;
            }
            else
            {
                pStreamBuf->flags |=  OMXVENC_BUFFERFLAG_EXTRADATA;
            }
            break;

        default:
            HI_ERR_VENC("Nalu.NaluType(%d) is invalid\n",NaluType);
            break;
    }
}

static HI_VOID VENC_DRV_OMXGetStrmBufFlag(HI_U32 Protocol, HI_U32 NaluType, HI_BOOL *pFirstNal2Send, venc_user_buf *pStreamBuf)
{
    if (Protocol == VEDU_H264)
    {
        H264_GetStrmBufFlag(NaluType, pFirstNal2Send, pStreamBuf);
    }
    else
    {
        H265_GetStrmBufFlag(NaluType, pFirstNal2Send, pStreamBuf);
    }
}

static HI_VOID EflTask_Stream_ListBuf(VeduEfl_EncPara_S* pEncPara, venc_user_buf *pstStreamBuf, HI_VOID* venc_stream_addr)
{
    VeduEfl_NALU_S Nalu ={{NULL,NULL}};
    HI_S32 s32Ret = 0,s32Ret2 = 0;
    HI_U32 DataLen = 0;

    if (STRM_GetWrittenLength(pEncPara->hStrmMng) > 0)
    {
        s32Ret = AcqReadBuffer(pEncPara, &Nalu);
        DataLen = Nalu.SlcLen[0];

        if (pstStreamBuf->buffer_size >= DataLen)
        {
            memcpy(venc_stream_addr, Nalu.pVirtAddr[0], DataLen);
            pstStreamBuf->data_len = DataLen;
        }
        else
        {
            HI_ERR_VENC("StreamBuf.buffer_size(%d) smaller than sliceLen(%d).\n", pstStreamBuf->buffer_size, DataLen);
        }

        pstStreamBuf->timestamp0 =  Nalu.PTS0;
        pstStreamBuf->timestamp1 =  Nalu.PTS1;

        s32Ret |= RlsReadBuffer(pEncPara, &Nalu);
    }
    else
    {
        s32Ret2 = VENC_DRV_OsalWaitEvent(&g_VENC_Event_stream, msecs_to_jiffies(10));

        if (0 != s32Ret2)
        {
            HI_INFO_VENC("wait stream time out! %d\n", __LINE__);
        }
    }

    VENC_DRV_OMXGetStrmBufFlag(pEncPara->Protocol, Nalu.NaluType, &pEncPara->bFirstNal2Send, pstStreamBuf);
    VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, s32Ret , pstStreamBuf);
}

static HI_S32 VENC_DRV_OMXOutputCheck(HI_U32 Protocol, HI_U32 NaluType, HI_U32 PackageFlag)
{
    HI_S32 ret = HI_FAILURE;

    switch (PackageFlag)
    {
        case OMX_PACKAGE_ONEINONEOUT:
            if (Protocol == VEDU_H265)
            {
                if ((NaluType != H265_NALU_TYPE_VPS)
                    && (NaluType != H265_NALU_TYPE_SPS)
                    && (NaluType != H265_NALU_TYPE_PPS))
                {
                    ret = HI_SUCCESS;
                }
            }
            else
            {
                /*H264*/
                if ((NaluType != H264_NALU_TYPE_SPS) && (NaluType != H264_NALU_TYPE_PPS))
                {
                    ret = HI_SUCCESS;
                }
            }
            break;

        case OMX_PACKAGE_SPLIT:
            if (Protocol == VEDU_H265)
            {
                if ((NaluType != H265_NALU_TYPE_VPS)
                    && (NaluType != H265_NALU_TYPE_SPS))
                {
                    ret = HI_SUCCESS;
                }
            }
            else
            {
                /*H264*/
                if ((NaluType != H264_NALU_TYPE_SPS))
                {
                    ret = HI_SUCCESS;
                }
            }
            break;

        case OMX_PACKAGE_ALONE:
            ret = HI_SUCCESS;
            break;

        default:
            HI_ERR_VENC("not support this PackageFlag = %d\n",PackageFlag);
            ret = HI_SUCCESS;
            break;
    }

    return ret;
}

static HI_VOID EflTask_Stream_LoopBuf(VeduEfl_EncPara_S* pEncPara, venc_user_buf *pstStreamBuf, HI_VOID* venc_stream_addr)
{
    HI_S32 s32Ret = 0,s32Ret2 = 0;
    VeduEfl_NALU_S Nalu ={{NULL,NULL}};

    do
    {
        if (STRM_GetWrittenLength(pEncPara->hStrmMng) > 0)
        {
            memset(&Nalu, 0, sizeof(VeduEfl_NALU_S));

            s32Ret = AcqReadBuffer(pEncPara, &Nalu);
            if (pstStreamBuf->buffer_size >= (Nalu.SlcLen[0] + Nalu.SlcLen[1]))
            {
                if (Nalu.SlcLen[0] > 0)
                {
                    memcpy(venc_stream_addr, Nalu.pVirtAddr[0], Nalu.SlcLen[0]);
                    pstStreamBuf->data_len += Nalu.SlcLen[0];
                    venc_stream_addr += Nalu.SlcLen[0];
                }

                if (Nalu.SlcLen[1] > 0)
                {
                    memcpy(venc_stream_addr, Nalu.pVirtAddr[1], Nalu.SlcLen[1]);
                    pstStreamBuf->data_len += Nalu.SlcLen[1];
                    venc_stream_addr += Nalu.SlcLen[1];
                }
            }
            else
            {
                HI_ERR_VENC("StreamBuf.buffer_size(%d) smaller than sliceLen(%d).\n", pstStreamBuf->buffer_size, (Nalu.SlcLen[0] + Nalu.SlcLen[1]));
            }

            pstStreamBuf->timestamp0 =  Nalu.PTS0;
            pstStreamBuf->timestamp1 =  Nalu.PTS1;

            s32Ret |= RlsReadBuffer(pEncPara, &Nalu);
        }
        else
        {
            s32Ret2 = VENC_DRV_OsalWaitEvent(&g_VENC_Event_stream, msecs_to_jiffies(10));

            if (0 != s32Ret2)
            {
                HI_INFO_VENC("wait stream time out! %d\n", __LINE__);
            }
        }

#ifdef __OMXVENC_ONE_IN_ONE_OUT__
    }while ((!s32Ret) && (VENC_DRV_OMXOutputCheck(pEncPara->Protocol, Nalu.NaluType, OMX_PACKAGE_ONEINONEOUT) == HI_FAILURE));
#else
    }while ((!s32Ret) && (VENC_DRV_OMXOutputCheck(pEncPara->Protocol, Nalu.NaluType, OMX_PACKAGE_SPLIT) == HI_FAILURE));
#endif

        VENC_DRV_OMXGetStrmBufFlag(pEncPara->Protocol, Nalu.NaluType, &pEncPara->bFirstNal2Send, pstStreamBuf);

        VENC_DRV_EflPutMsg_OMX(pEncPara->MsgQueue_OMX, VENC_MSG_RESP_OUTPUT_DONE, s32Ret , pstStreamBuf);
}

static HI_VOID VENC_DRV_EflTask_Stream( HI_VOID )
{
    VeduEfl_EncPara_S* EncHandle;
    VeduEfl_EncPara_S *pEncPara = HI_NULL;
    HI_U32 i = 0;
    HI_S32 s32Ret = 0;
    HI_BOOL bTmpValue = HI_FALSE;
    venc_user_buf StreamBuf;
    venc_msginfo msg_info;
    HI_VOID* venc_stream_addr = NULL;

    /* wait for venc start */
    while (!VeduIpCtx.StopTask)
    {
        for (i = 0; i < HI_VENC_MAX_CHN; i++)
        {
            bTmpValue |= (g_stVencChn[i].bEnable && g_stVencChn[i].bOMXChn);
        }

        if (HI_FALSE == bTmpValue)
        {
            msleep(10);
        }
        else
        {
            break;
        }
    }

    while (!VeduIpCtx.StopTask)
    {
        /* if ipfree, don't irqlock */
        EncHandle = VENC_DRV_EflQueryChn_Stream(&msg_info);
        if (EncHandle != NULL)
        {
            pEncPara = EncHandle;

            memcpy(&StreamBuf, &(msg_info.buf), sizeof(venc_user_buf));
            venc_stream_addr = (HI_VOID*)(StreamBuf.bufferaddr_Phy + StreamBuf.vir2phy_offset);

            if (VeduIpCtx.IsChipIDV500R001 == HI_TRUE)
            {
                EflTask_Stream_ListBuf(pEncPara, &StreamBuf, venc_stream_addr);
            }
            else
            {
                EflTask_Stream_LoopBuf(pEncPara, &StreamBuf, venc_stream_addr);
            }

            pEncPara->StreamQueue_OMX->bStrmLock = 0;
            pEncPara->stStat.MsgQueueNum++;

#ifdef __VENC_DRV_DBG__
            if (PutMsg_FBD_ID < 100)
            {
                HI_DRV_SYS_GetTimeStampMs(&TmpTime_dbg[PutMsg_FBD_ID][4]);
                PutMsg_FBD_ID++;
            }
#endif
        }
        else
        {
            /* if channel not ready, sleep */
           //msleep(10);
           s32Ret = VENC_DRV_OsalWaitEvent(&g_VENC_Event_stream, msecs_to_jiffies(30));
           if (0 != s32Ret)
           {
               HI_INFO_VENC("wait stream time out! %d\n",__LINE__);
           }
        }
    }

    return;
}

/******************************************************************************
Function   :
Description: IP-VEDU & IP-JPGE Open & Close
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflOpenVedu( HI_VOID )
{
    HI_U32 i;
    HI_CHIP_TYPE_E enChipType = 0;
    HI_CHIP_VERSION_E enChipVersion = 0;

    /* create channel control mutex */
    if (VENC_DRV_OsalLockCreate( &VeduIpCtx.pChnLock ) == HI_FAILURE)
    {
        return HI_FAILURE;
    }

    /* get chip type */
    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

    /* initial func */
    if (IsChipIDV500R001(enChipType, enChipVersion))
    {
        VeduIpCtx.IsChipIDV500R001 = HI_TRUE;
        DRV_VENC_PDT_V500R001_Init();
    }
    else
    {
        VeduIpCtx.IsChipIDV500R001 = HI_FALSE;
        DRV_VENC_PDT_V400R004C02_Init();
    }

    if (VENC_HAL_Init() != HI_SUCCESS)
    {
        HI_ERR_VENC("Hal init failure!\n");

        VENC_DRV_OsalLockDestroy( VeduIpCtx.pChnLock );

        return HI_FAILURE;
    }

    if (STRM_Init()!= HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    /* set ip free status */
    VeduIpCtx.IpFree = 1;

    /* set ip free status */
    VeduIpCtx.CurrFreq = VENC_FREQUENCY_200M;

    /* clear channel status */
    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        VeduChnCtx[i].EncHandle = NULL;
    }

    /* init IRQ */
    VENC_HAL_DisableInt(INTERRUPT_TYPE_ALL);
    VENC_HAL_ClearInt(INTERRUPT_TYPE_ALL);

    if (HI_FAILURE == VENC_DRV_OsalIrqInit(VEDU_IRQ_ID, Venc_ISR))
    {
        return HI_FAILURE;
    }

    /* creat thread to manage channel */
    VeduIpCtx.StopTask = 0;
    VeduIpCtx.TaskRunning = 0;

    /* for test compare*/
    g_idr_pic_id = 0;

    init_waitqueue_head(&gqueue);
    gwait = 0;

    VENC_DRV_OsalCreateTask(&VeduIpCtx.pTask_Frame, "HI_VENC_FrameTask", VENC_DRV_EflTask);
    msleep(1);
    VENC_DRV_OsalCreateTask(&VeduIpCtx.pTask_Stream, "HI_VENC_StreamTask", VENC_DRV_EflTask_Stream);

    return HI_SUCCESS;
}

HI_VOID VENC_DRV_EflCloseVedu( HI_VOID )
{
    HI_U32 RecycleCnt = 0;

    VeduIpCtx.StopTask = 1;

    while ((VeduIpCtx.TaskRunning) && (RecycleCnt < 50))
    {
        RecycleCnt++;

        msleep(1);
    }

    if (RecycleCnt == 50)
    {
        HI_INFO_VENC("Vedu close timeout! force to close Vedu\n");
    }

    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Frame);
    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Stream);

    VENC_HAL_DisableInt(INTERRUPT_TYPE_ALL);
    VENC_HAL_ClearInt(INTERRUPT_TYPE_ALL);

    VENC_DRV_OsalIrqFree(VEDU_IRQ_ID);

    VENC_HAL_Deinit();

    STRM_DeInit();
    /* for test compare*/
    g_idr_pic_id = 0;

    VENC_DRV_OsalLockDestroy( VeduIpCtx.pChnLock );

    return;
}

HI_VOID VENC_DRV_EflSuspendVedu( HI_VOID )
{
    HI_U32 RecycleCnt = 0;

    VeduIpCtx.StopTask = 1;

    while ((VeduIpCtx.TaskRunning) && (RecycleCnt < 50))
    {
        RecycleCnt++;

        msleep(1);
    }

    if (RecycleCnt == 50)
    {
        HI_INFO_VENC("Vedu close timeout! force to close Vedu\n");
    }

    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Frame);
    VENC_DRV_OsalDeleteTask(VeduIpCtx.pTask_Stream);

    VENC_HAL_DisableInt(INTERRUPT_TYPE_ALL);
    VENC_HAL_ClearInt  (INTERRUPT_TYPE_ALL);

    VENC_DRV_OsalIrqFree( VEDU_IRQ_ID );

    //VENC_HAL_Deinit();

    return ;
}

/*****************************************************************************
 Prototype    : VENC_DRV_Resume
 Description  : VENC resume function
 Input        : None
 Output       : None
 Return Value : None
 Others       : Delete initialization of global value compared with VeduEfl_OpenVedu
*****************************************************************************/
HI_S32 VENC_DRV_EflResumeVedu(HI_VOID)
{
    /* init IRQ */
    if (VENC_DRV_OsalIrqInit(VEDU_IRQ_ID, Venc_ISR) == HI_FAILURE)
    {
        return HI_FAILURE;
    }

    /* creat channel control mutex */
    /*if (HI_FAILURE == VENC_DRV_OsalLockCreate( &VeduIpCtx.pChnLock ))
    {
        return HI_FAILURE;
    }*/


    /* creat thread to manage channel */
    VeduIpCtx.StopTask = 0;
    VENC_DRV_OsalCreateTask(&VeduIpCtx.pTask_Frame, "HI_VENC_FrameTask", VENC_DRV_EflTask );
    msleep(1);
    VENC_DRV_OsalCreateTask(&VeduIpCtx.pTask_Stream, "HI_VENC_StreamTask", VENC_DRV_EflTask_Stream);

    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflQueryStatInfo( VeduEfl_EncPara_S* EncHandle, VeduEfl_StatInfo_S* pStatInfo )
{
    VeduEfl_EncPara_S*  pEncPara = EncHandle;

    if ((pEncPara == NULL) || (pStatInfo == NULL))
    {
        return HI_FAILURE;
    }

    pEncPara->stStat.UsedStreamBuf = STRM_GetWrittenLength(pEncPara->hStrmMng);
    *pStatInfo = pEncPara->stStat;

    return HI_SUCCESS;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflQueueFrame( VeduEfl_EncPara_S* EncHandle, HI_DRV_VIDEO_FRAME_S*  pstFrame)
{
    VeduEfl_EncPara_S  *pEncPara = NULL;
    HI_S32 s32Ret;
    queue_data_s  Queue_data;
    HI_U32 i;
    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if ((g_stVencChn[i].hVEncHandle == EncHandle) && (g_stVencChn[i].hVEncHandle != NULL))
        {
            pEncPara  = EncHandle;
            break;
        }
    }
    if ((i == HI_VENC_MAX_CHN) || (pEncPara == NULL))
    {
        HI_ERR_VENC(" bad handle!!\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Queue_data.bToOMX = 0;
    memcpy(&(Queue_data.unFrmInfo.queue_info),pstFrame,sizeof(HI_DRV_VIDEO_FRAME_S));
    s32Ret = VENC_DRV_MngQueue(pEncPara->FrameQueue,&Queue_data,0,0);
    if (HI_SUCCESS == s32Ret)
    {
       pEncPara->stStat.QueueNum++;
       VENC_DRV_EflWakeUpThread();

    }
    return s32Ret;
}

HI_S32 VENC_DRV_EflQFrameByAttach( HI_U32 EncUsrHandle, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_S32 s32ChIndx = 0;
    HI_S32 s32Ret = 0;
    unsigned long flags;

    while (s32ChIndx < HI_VENC_MAX_CHN)
    {
        if (g_stVencChn[s32ChIndx].hUsrHandle == EncUsrHandle)
        {
            break;
        }

        s32ChIndx++;
    }

    if (s32ChIndx >= HI_VENC_MAX_CHN)
    {
        HI_ERR_VENC(" bad handle!!\n");

        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[s32ChIndx].hVEncHandle == NULL)
    {
        return HI_ERR_VENC_CHN_NO_ATTACH;
    }

    if (HI_VENC_MAX_CHN  == s32ChIndx)
    {
        HI_ERR_VENC(" bad handle!!\n");

        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[s32ChIndx].enSrcModId >= HI_ID_BUTT)
    {
        return HI_ERR_VENC_CHN_NO_ATTACH;
    }

    spin_lock_irqsave(&g_SendFrame_Lock[s32ChIndx], flags);
    s32Ret = VENC_DRV_EflQueueFrame(g_stVencChn[s32ChIndx].hVEncHandle, pstFrame);
    spin_unlock_irqrestore(&g_SendFrame_Lock[s32ChIndx], flags);

    return s32Ret;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32  VENC_DRV_EflDequeueFrame( VeduEfl_EncPara_S* EncHandle, HI_DRV_VIDEO_FRAME_S* pstFrame)
{
    VeduEfl_EncPara_S  *pEncPara = NULL;
    HI_S32 s32Ret;
    HI_U32 i;

    queue_data_s  Queue_data;
    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if ((g_stVencChn[i].hVEncHandle == EncHandle) && (g_stVencChn[i].hVEncHandle != NULL))
        {
            pEncPara  = EncHandle;
            break;
        }
    }

    if ((i == HI_VENC_MAX_CHN) || (pEncPara == NULL))
    {
        HI_ERR_VENC(" bad handle!!\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    s32Ret = VENC_DRV_MngDequeue(pEncPara->FrameDequeue, &Queue_data);
    if (Queue_data.bToOMX || s32Ret)
    {
        HI_INFO_VENC("NOT FOR OMX FREAM!!\n");
        return s32Ret;
    }
    else
    {
       memcpy(pstFrame,&(Queue_data.unFrmInfo.queue_info),sizeof(HI_DRV_VIDEO_FRAME_S));
    }
    pEncPara->stStat.DequeueNum--;
    return s32Ret;
}


HI_S32 VENC_DRV_EflRlsAllFrame( VeduEfl_EncPara_S* EncHandle)
{
    VEDU_LOCK_FLAG flag;
    //HI_DRV_VIDEO_FRAME_S stFrame ;
    VeduEfl_EncPara_S  *pEncPara = NULL;
    HI_S32 s32Ret = 0;
    HI_U32 i;
    queue_data_s  Queue_data;

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if ((g_stVencChn[i].hVEncHandle == EncHandle) && (g_stVencChn[i].hVEncHandle != NULL))
        {
            pEncPara  = EncHandle;
            break;
        }
    }

    if ((i == HI_VENC_MAX_CHN) || ((pEncPara == NULL)))
    {
        HI_ERR_VENC(" bad handle!!\n");
        return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    VENC_DRV_OsalLock( VeduIpCtx.pChnLock, &flag);
    while ( (!VENC_DRV_MngQueueEmpty(pEncPara->FrameQueue)) && (!s32Ret) )
    {
        s32Ret = VENC_DRV_MngDequeue(pEncPara->FrameQueue, &Queue_data);
        if (!s32Ret && !Queue_data.bToOMX)
        {
            (pEncPara->stSrcInfo.pfPutImage)(pEncPara->stSrcInfo.handle, &(Queue_data.unFrmInfo.queue_info));
           if (g_stVencChn[i].enSrcModId < HI_ID_BUTT)
           {
              pEncPara->stStat.QueueNum--;
           }
        }
    }

    VENC_DRV_OsalUnlock( VeduIpCtx.pChnLock, &flag);
    return s32Ret;
}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflGetImage(HI_S32 EncUsrHandle, HI_DRV_VIDEO_FRAME_S* pstFrame)
{
    HI_U32 u32ChnID;
    HI_S32 s32Ret;
    VeduEfl_EncPara_S *pEncPara;
    queue_data_s  Queue_data;
    D_VENC_GET_CHN_BY_UHND(u32ChnID, EncUsrHandle);
    D_VENC_CHECK_CHN(u32ChnID);
    pEncPara = g_stVencChn[u32ChnID].hVEncHandle;
    s32Ret = VENC_DRV_MngDequeue(pEncPara->FrameQueue, &Queue_data);
    if (Queue_data.bToOMX || s32Ret)
    {
        HI_INFO_VENC("NOT FOR OMX FREAM!!\n");
        return s32Ret;
    }
    else
    {
       memcpy(pstFrame,&(Queue_data.unFrmInfo.queue_info),sizeof(HI_DRV_VIDEO_FRAME_S));
    }
    pEncPara->stStat.QueueNum--;
    return s32Ret;
}

HI_S32 VENC_DRV_EflGetImage_OMX(HI_S32 EncUsrHandle, venc_user_buf* pstFrame)
{
    HI_U32 u32ChnID;
    HI_S32 s32Ret;
    VeduEfl_EncPara_S  *pEncPara;
    queue_data_s  Queue_data;

    D_VENC_GET_CHN_BY_UHND(u32ChnID, EncUsrHandle);
    D_VENC_CHECK_CHN(u32ChnID);
    pEncPara = g_stVencChn[u32ChnID].hVEncHandle;

    if( VENC_DRV_MngQueueEmpty(pEncPara->FrameQueue_OMX))
    {
       return HI_FAILURE;
    }
    s32Ret = VENC_DRV_MngDequeue(pEncPara->FrameQueue_OMX, &Queue_data);
    if( !Queue_data.bToOMX || s32Ret)
    {
       HI_INFO_VENC("err:not match for OMX!! ret = %d\n",s32Ret);
       return s32Ret;
    }
    else
    {
       memcpy(pstFrame,&(Queue_data.unFrmInfo.msg_info_omx.buf),sizeof(venc_user_buf));
    }
    pEncPara->stStat.QueueNum--;
    return HI_SUCCESS;

}

/******************************************************************************
Function   :
Description:
Calls      :
Input      :
Output     :
Return     :
Others     :
******************************************************************************/
HI_S32 VENC_DRV_EflPutImage(HI_S32 EncUsrHandle, HI_DRV_VIDEO_FRAME_S* pstFrame)
{
    HI_U32 u32ChnID;
    HI_S32 s32Ret;
    VeduEfl_EncPara_S *pEncPara;
    queue_data_s  Queue_data;
    D_VENC_GET_CHN_BY_UHND(u32ChnID, EncUsrHandle);
    D_VENC_CHECK_CHN(u32ChnID);

    pEncPara = g_stVencChn[u32ChnID].hVEncHandle;

    Queue_data.bToOMX = 0;
    memcpy(&(Queue_data.unFrmInfo.queue_info),pstFrame,sizeof(HI_DRV_VIDEO_FRAME_S));
    s32Ret = VENC_DRV_MngQueue(pEncPara->FrameDequeue, &Queue_data,0,0);
    if (!s32Ret)
    {
       pEncPara->stStat.DequeueNum++;
    }
    return s32Ret;

}

#ifdef HI_SMMU_SUPPORT
HI_U32 VeduEfl_SmmuToPhyAddr(HI_U32 PageTabBaseAddr ,HI_U32 SmmuAddr  )
{
   //HI_U32 PageTabBaseAddr = 0;
   HI_U32 PageIndex = 0;
   HI_U32 PageOffset = 0;
   HI_U32 PhyAddr = 0;
   HI_U32  *pPage;
   HI_U32 Hige20Bit,Low12Bit;
   //PageTabBaseAddr = pAllReg->SMMU_CB_TTBR;

   HI_INFO_VENC("%s,%d,PageTabBaseAddr = 0x%x,smmuAddr = 0x%x\n",__func__,__LINE__,PageTabBaseAddr,SmmuAddr);

   if (PageTabBaseAddr == 0)
   {
        HI_ERR_VENC("%s,%d, pageTabBaseAddr = %d Error!\n",__func__,__LINE__,PageTabBaseAddr);
        return -1;
   }

   PageOffset = SmmuAddr / 4096 * 4;//one phypage has 4k bytes memory, its length is 4 byte

   PageIndex = PageTabBaseAddr + PageOffset;
   HI_INFO_VENC("%s,%d,PageIndex = 0x%x\n",__func__,__LINE__,PageIndex);

   pPage = (HI_U32 *)phys_to_virt(PageIndex);//(HI_U32 *)ioremap(PageIndex, 4);

   Hige20Bit = ((*pPage) & 0xfffff000);
   HI_INFO_VENC("%s,%d,Hige20Bit = 0x%x(0x%x)\n",__func__,__LINE__,Hige20Bit,*pPage);

   Low12Bit = SmmuAddr & 0xfff;
   HI_INFO_VENC("%s,%d,Low12Bit = 0x%x\n",__func__,__LINE__,Low12Bit);

   PhyAddr = Hige20Bit + Low12Bit;

   HI_INFO_VENC("\n%s,%d,~ PhyAddr = 0x%x\n",__func__,__LINE__,PhyAddr);
   return PhyAddr;
}
#endif

/////////////////////////////////////////////////////////////////debug
HI_S32 VENC_DRV_DbgWriteYUV(HI_DRV_VIDEO_FRAME_S *pstFrame,HI_CHAR *pFileName)
{
    char str[64] = {0};
    unsigned char *ptr;
    struct file *fp;

    HI_U8 *pu8Udata;
    HI_U8 *pu8Vdata;
    HI_U8 *pu8Ydata;
    HI_S8  s_VencSavePath[64];
    HI_U32 i,j;
#ifdef HI_SMMU_SUPPORT
    VENC_BUFFER_S stMBuf;
    HI_S32 Ret;

    memset(&stMBuf, 0, sizeof(VENC_BUFFER_S));
#endif
    HI_DRV_LOG_GetStorePath(s_VencSavePath, 64);

    pu8Udata = HI_VMALLOC(HI_ID_VENC,pstFrame->u32Width * pstFrame->u32Height / 2 /2);
    if (pu8Udata == HI_NULL)
    {
        return HI_FAILURE;
    }
    pu8Vdata = HI_VMALLOC(HI_ID_VENC,pstFrame->u32Width * pstFrame->u32Height / 2 /2);
    if (pu8Vdata == HI_NULL)
    {
        HI_VFREE(HI_ID_VENC,pu8Udata);
        return HI_FAILURE;
    }
    pu8Ydata = HI_VMALLOC(HI_ID_VENC,pstFrame->stBufAddr[0].u32Stride_Y);
    if (pu8Ydata == HI_NULL)
    {
        HI_VFREE(HI_ID_VENC,pu8Udata);
        HI_VFREE(HI_ID_VENC,pu8Vdata);
        return HI_FAILURE;
    }
#ifdef HI_SMMU_SUPPORT
    stMBuf.u32StartPhyAddr = pstFrame->stBufAddr[0].u32PhyAddr_Y;
    Ret = HI_DRV_VENC_Map(&stMBuf);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("SMMU map is failure!\n");
        HI_VFREE(HI_ID_VENC, pu8Udata);
        HI_VFREE(HI_ID_VENC, pu8Vdata);
        HI_VFREE(HI_ID_VENC, pu8Ydata);

        return HI_FAILURE;
    }
    else
    {
        ptr = stMBuf.pu8StartVirAddr;
    }
#else
    ptr = (unsigned char *)phys_to_virt(pstFrame->stBufAddr[0].u32PhyAddr_Y);
#endif
    if (!ptr)
    {
        HI_ERR_VENC("address is not valid!\n");
    }
    else
    {
        HI_OSAL_Snprintf(str, 64, "%s/%s", s_VencSavePath,pFileName);

        fp = VENC_DRV_OsalFopen(str, O_RDWR | O_CREAT|O_APPEND, 0);
        if (fp == HI_NULL)
        {
            HI_ERR_VENC("open file '%s' fail!\n", str);
            HI_VFREE(HI_ID_VENC,pu8Udata);
            HI_VFREE(HI_ID_VENC,pu8Vdata);
            HI_VFREE(HI_ID_VENC,pu8Ydata);
        #ifdef HI_SMMU_SUPPORT
            HI_DRV_VENC_Unmap(&stMBuf);
        #endif
            return HI_FAILURE;
        }

        /*写 Y 数据*/
        for (i=0; i<pstFrame->u32Height; i++)
        {
            memcpy(pu8Ydata,ptr,sizeof(HI_U8)*pstFrame->stBufAddr[0].u32Stride_Y);
            if(pstFrame->u32Width != VENC_DRV_OsalFwrite(pu8Ydata,pstFrame->u32Width, fp))
              {
                HI_ERR_VENC("fwrite fail!\n");
            }
            ptr += pstFrame->stBufAddr[0].u32Stride_Y;
        }

#ifdef HI_SMMU_SUPPORT
        ptr = stMBuf.pu8StartVirAddr + (pstFrame->stBufAddr[0].u32PhyAddr_C - pstFrame->stBufAddr[0].u32PhyAddr_Y);
#else
        ptr = (unsigned char *)phys_to_virt(pstFrame->stBufAddr[0].u32PhyAddr_C);
#endif

        /* U V 数据 转存*/
        for (i=0; i<pstFrame->u32Height/2; i++)
        {
            for (j=0; j<pstFrame->u32Width/2; j++)
            {
                if(pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV21)
                {
                    pu8Vdata[i*pstFrame->u32Width/2+j] = ptr[2*j];
                    pu8Udata[i*pstFrame->u32Width/2+j] = ptr[2*j+1];
                }
                else if (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV12)
                {
                    pu8Udata[i*pstFrame->u32Width/2+j] = ptr[2*j];
                    pu8Vdata[i*pstFrame->u32Width/2+j] = ptr[2*j+1];
                }
                else
                {
                    HI_ERR_VENC("other pix formet= %d\n",pstFrame->ePixFormat);
                }
            }
            ptr += pstFrame->stBufAddr[0].u32Stride_C;
        }
        /*写 U */
        VENC_DRV_OsalFwrite(pu8Udata, pstFrame->u32Width * pstFrame->u32Height / 2 /2, fp);

        /*写 V */
        VENC_DRV_OsalFwrite(pu8Vdata, pstFrame->u32Width * pstFrame->u32Height / 2 /2, fp);

        VENC_DRV_OsalFclose(fp);
        HI_INFO_VENC("2d image has been saved to '%s' W=%d H=%d Format=%d \n",
                    str,pstFrame->u32Width,pstFrame->u32Height,pstFrame->ePixFormat);
    }

    HI_VFREE(HI_ID_VENC,pu8Udata);
    HI_VFREE(HI_ID_VENC,pu8Vdata);
    HI_VFREE(HI_ID_VENC,pu8Ydata);
#ifdef HI_SMMU_SUPPORT
    HI_DRV_VENC_Unmap(&stMBuf);
#endif

    return HI_SUCCESS;
}

/////////////////////////////////////////////////////////////////debug end
/*************************************************************************************/
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
