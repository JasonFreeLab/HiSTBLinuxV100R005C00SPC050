#ifndef __VPSS_COMMON_H__
#define __VPSS_COMMON_H__

#include"hi_drv_mem.h"
#include"hi_drv_log.h"
#include"hi_drv_sys.h"
#include"hi_drv_stat.h"
#include"hi_drv_video.h"
#include"hi_drv_vpss.h"
#include "hi_debug.h"
#include <linux/list.h>
#include <linux/io.h>
#include <linux/delay.h>
#include"drv_vdec_ext.h"

#define DEF_FILE_NAMELENGTH 64
#define VPSS_ISLOSS_CMP     HI_FALSE
#define DEF_VPSS_LOGIC_WORK 1
typedef struct list_head LIST;

#if 1
#define VPSS_SAFE_MEMCPY(dst, src, size) \
    {\
        memcpy(dst, src, size);\
    }
#else
#define VPSS_SAFE_MEMCPY(dst, src, size) \
    { \
        if ((HI_NULL == dst) || (HI_NULL == src)) \
        {\
            VPSS_FATAL("dst src size 0x%x 0x%x %u\n", dst, src, size);\
        } \
        else \
        { \
            memcpy(dst, src, size);\
        }\
    }
#endif
#define ZME_2L_TEST   //@sdk
#define FB_DBG 0
#define DEF_VPSS_DEBUG 1
#define DEF_VPSS_HIGH_4K 1
#define DEF_VPSS_ANDROID_BYPASS 1
#define VPSS_INSTANCE_MAX_NUMB          36

#define VPSS_NAME  "HI_VPSS"

#define VPSS_KMALLOC(fmt...)      HI_KMALLOC  (HI_ID_VPSS, fmt)
#define VPSS_KFREE(fmt...)        HI_KFREE    (HI_ID_VPSS, fmt)
#define VPSS_VMALLOC(fmt...)       HI_VMALLOC   (HI_ID_VPSS, fmt)
#define VPSS_VFREE(fmt...)       HI_VFREE   (HI_ID_VPSS, fmt)
#define VPSS_VFREE_SAFE(ptr) {if (HI_NULL!=ptr){HI_VFREE(HI_ID_VPSS, ptr);}}

#define VPSS_FATAL(fmt...) \
    HI_FATAL_PRINT(HI_ID_VPSS, fmt)

#define VPSS_ERROR(fmt...) \
    HI_ERR_PRINT(HI_ID_VPSS, fmt)

#define VPSS_WARN(fmt...) \
    HI_WARN_PRINT(HI_ID_VPSS, fmt)

#define VPSS_INFO(fmt...) \
    HI_INFO_PRINT(HI_ID_VPSS, fmt)
#if 1
#define VPSS_DBG_INFO(fmt...)
#else
#define VPSS_DBG_INFO(fmt...) \
    HI_ERR_PRINT(HI_ID_VPSS, fmt)
#endif
#define VPSS_DBG() \
    do{\
        HI_PRINT("--->%s %d\n",__func__,__LINE__);\
    }while(0)

#define VPSS_CHECK_NULL(ptr)\
    do\
    {\
        if (HI_NULL == ptr)\
        {\
            VPSS_ERROR("Para is Null\n");\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_CHECK_HANDLE(handle)\
    do\
    {\
        if (HI_INVALID_HANDLE == handle)\
        {\
            VPSS_ERROR("handle is HI_INVALID_HANDLE\n");\
            return HI_FAILURE;\
        }\
    }while(0)

#define VPSS_CHECK_VERSION(version,exp)\
    do\
    {\
        if (version != exp)\
        {\
            VPSS_ERROR("Invalid Version %d.Expect %d\n",version,exp);\
            return HI_FAILURE;\
        }\
    }while(0)


#define VPSS_GET_TIME(time)\
    do\
    {\
        HI_U32 u32Tmp;\
        if(!HI_DRV_SYS_GetTimeStampMs(&u32Tmp))\
        {\
            time = u32Tmp;\
            VPSS_ERROR("Get Time %d \n",time);\
        }\
        else\
        {\
            time = 0;\
            VPSS_ERROR("Get Time Failed\n");\
        }\
    }while(0)

#define VPSS_IS_TILE_FMT(fmt) (\
                               (HI_DRV_PIX_FMT_NV12_TILE == (fmt))\
                               || (HI_DRV_PIX_FMT_NV21_TILE == (fmt))\
                               || (HI_DRV_PIX_FMT_YUV400_TILE == (fmt))\
                               || (HI_DRV_PIX_FMT_NV12_TILE_CMP == (fmt))\
                               || (HI_DRV_PIX_FMT_NV21_TILE_CMP == (fmt)))

#define VPSS_IS_YUV422_FMT(fmt) (\
                                 (HI_DRV_PIX_FMT_YUYV == (fmt))\
                                 || (HI_DRV_PIX_FMT_YVYU == (fmt))\
                                 || (HI_DRV_PIX_FMT_UYVY == (fmt)))

#define VPSS_IS_YUV420_FMT(pix) (\
                                 (HI_DRV_PIX_FMT_NV12 == (pix)) || (HI_DRV_PIX_FMT_NV21 == (pix)) \
                                 || (HI_DRV_PIX_FMT_NV12_CMP == (pix)) || (HI_DRV_PIX_FMT_NV21_CMP == (pix)) \
                                 || (HI_DRV_PIX_FMT_NV12_TILE == (pix)) || (HI_DRV_PIX_FMT_NV21_TILE == (pix))\
                                 || (HI_DRV_PIX_FMT_NV12_TILE_CMP == (pix)) || (HI_DRV_PIX_FMT_NV21_TILE_CMP == (pix)))


typedef enum hiVPSS_VERSION_E
{
    VPSS_VERSION_V1_0 = 0,
    VPSS_VERSION_V2_0 ,
    VPSS_VERSION_V3_0 ,
    VPSS_VERSION_V4_0 ,
    VPSS_VERSION_BUTT
} VPSS_VERSION_E;

typedef enum hiVPSS_RET_CODE_E
{
    HI_VPSS_RET_SUCCESS             = 0x0,
    HI_VPSS_RET_FAIL                = 0x1,
    HI_VPSS_RET_PARA                = 0x2,
    HI_VPSS_RET_NULL_POINTER        = 0x3,
    HI_VPSS_RET_UNSUPPORT           = 0x4,
    HI_VPSS_RET_NOT_READY           = 0x5,
    HI_VPSS_RET_UNDERFLOW           = 0x6,
    HI_VPSS_RET_OVERFLOW            = 0x7,
    HI_VPSS_RET_TIMEOUT             = 0x8,
    HI_VPSS_RET_NO_ACK              = 0x9,
    HI_VPSS_RET_BUSY                = 0xA,
    HI_VPSS_RET_LOSS                = 0xB,
    HI_VPSS_RET_ERROR               = 0xC,
    HI_VPSS_RET_DIVZERO             = 0xD,
} VPSS_RET_CODE_E;

typedef enum
{
    VPSS_COLOR_BLACK = 0,
    VPSS_COLOR_RED,
    VPSS_COLOR_WHITE,
    VPSS_COLOR_GREEN,
    VPSS_COLOR_BLUE,
    VPSS_COLOR_YELLOW,
    VPSS_COLOR_BUTT,
} VPSS_COLOR_E;


typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    hi3798mv100          : 1   ;
        unsigned int    hi3716mv410          : 1   ;
        unsigned int    hi3798cv200_a        : 1   ;
        unsigned int    reserve_2            : 1   ;
        unsigned int    reserve_3            : 28  ;

    } bits;
    // Define an unsigned member
    unsigned int    u32;

} VPSS_CAPABILITY_U;


#define VPSS_NTSC_WIDTH  720
#define VPSS_NTSC_HEIGHT 480
#define VPSS_PAL_WIDTH 720
#define VPSS_PAL_HEIGHT 576
#define VPSS_HD_WIDTH  1280
#define VPSS_HD_HEIGHT 720
#define VPSS_FHD_WIDTH 1920
#define VPSS_FHD_HEIGHT 1080
#define VPSS_UHD_WIDTH  4096
#define VPSS_UHD_HEIGHT 2304


#define VPSS_IN_HEIGHT_ALIGN        0XFFFFFFFC

#define VPSS_HEIGHT_ALIGN           0XFFFFFFFE

#define VPSS_WIDTH_ALIGN            0XFFFFFFFE

#define VPSS_HEIGHT_ALIGN_4PIXELCLK 0XFFFFFFFC
#define VPSS_WIDTH_ALIGN_4PIXELCLK  0XFFFFFFFC

#define VPSS_PIXLE_UPALIGN_W(w, fourpixelclk) {\
        if (fourpixelclk) {\
            (w) = (((HI_U32)(w)+3) & (VPSS_WIDTH_ALIGN_4PIXELCLK));\
        } else {\
            (w) = (((HI_U32)(w)+1) & (VPSS_WIDTH_ALIGN));\
        }}

#define VPSS_PIXLE_UPALIGN_H(h, fourpixelclk) {\
        if (fourpixelclk) {\
            (h) = (((HI_U32)(h)+3) & (VPSS_HEIGHT_ALIGN_4PIXELCLK));\
        } else {\
            (h) = (((HI_U32)(h)+1) & (VPSS_HEIGHT_ALIGN));\
        }}


#define VPSS_PIXLE_DOWNALIGN_W(w, fourpixelclk) {\
        if (fourpixelclk) {\
            (w) = (((HI_U32)(w)) & (VPSS_WIDTH_ALIGN_4PIXELCLK));\
        } else {\
            (w) = (((HI_U32)(w)) & (VPSS_WIDTH_ALIGN));\
        }}

#define VPSS_PIXLE_DOWNALIGN_H(h, fourpixelclk) {\
        if (fourpixelclk) {\
            (h) = (((HI_U32)(h)) & (VPSS_HEIGHT_ALIGN_4PIXELCLK));\
        } else {\
            (h) = (((HI_U32)(h)) & (VPSS_HEIGHT_ALIGN));\
        }}

#define VPSS_GET_ARRAY_CNT(array) (sizeof(array)/sizeof(array[0]))

#if !defined(CHIP_TYPE_hi3798cv200_a) && !defined(CHIP_TYPE_hi3798cv200)

#define VPSS_HDR_TYPE_NEED_BYPASS_VPSS(type) ( \
        (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL == (type)))
/* 98mv200,96mv200 hdr need vpss translate linear8+2->10bit */
#define VPSS_HDR_TYPE_NEED_DETILE_NOALG(type) ( \
        (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_HDR10 == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_HLG      == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_SLF      == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_TECHNICOLOR == (type)))
#else
#define VPSS_HDR_TYPE_NEED_BYPASS_VPSS(type) ( \
        (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_HLG      == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_SLF      == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_HDR10 == (type)) \
        || (HI_DRV_VIDEO_FRAME_TYPE_TECHNICOLOR == (type)))
/* 98cv200 hdr can handle 8+2bit linear */
#define VPSS_HDR_TYPE_NEED_DETILE_NOALG(type) ( \
        (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL == (type)) \
                                              )
#endif
#define VPSS_HDR_TYPE_NEED_TRANS_METADATA(type) ( \
        (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL == (type)) \
                                                )
#define VPSS_SUPPORT_PROC_V2
#define VPSS_SUPPORT_OUT_TUNNEL

#if !defined(CHIP_TYPE_hi3798cv200_a) && !defined(CHIP_TYPE_hi3798cv200)
#define VPSS_HAL_WITH_CBB
#define VPSS_SUPPORT_ALG_MCNR
/*
    When zme enable, The max output width is 1920, So 3D@4K SBS src should output 1/2*src_width;
    3D@4K TAB src should output 1/2 * src_height and 4k width, And disable zme.
*/

#define VPSS_ZME_WIDTH_MAX_FHD
#else
#define VPSS_ZME_SUPPORT_10BIT
#endif

#ifdef VPSS_SUPPORT_PROC_V2
#define VPSS_PROC_TIMESTAMP_MAXCNT 3
#endif

#if defined(CHIP_TYPE_hi3796mv200)
#define VPSS_SUPPORT_BLKMT
#define VPSS_SUPPORT_DICNT
#define VPSS_SUPPORT_MCDEI_IN_H265I  //mcdei is supported when h265 interlace frame processing
#define VPSS_NOT_SUPPORT_MCNR_FMT(fmt) (HI_FALSE)
#endif

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3798mv200_a)
#define VPSS_NOT_SUPPORT_MCNR_FMT(fmt) (VPSS_IS_TILE_FMT(fmt))
#endif


#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200)
#define VPSS_HAS_LBADDR(type) (HI_DRV_PIXEL_BITWIDTH_10BIT == (type))
#else
#define VPSS_HAS_LBADDR(type) (( HI_DRV_PIXEL_BITWIDTH_10BIT == (type)) ||\
                               (HI_DRV_PIXEL_BITWIDTH_10BIT_CTS == (type)))
#endif

#define VPSS_FRAME_MIN_WIDTH            64
#define VPSS_FRAME_MIN_HEIGHT           64

#define VPSS_FRAME_MAX_WIDTH            4096
#define VPSS_FRAME_MAX_HEIGHT           2304



#define VPSS_SYS_MEM_MIN               512

#define VPSS_UHD_LOW_W          1920
#define VPSS_UHD_LOW_H          1080

#define VPSS_UHD_MIDDLE_W       1920
#define VPSS_UHD_MIDDLE_H       2160

#if DEF_VPSS_HIGH_4K
#define VPSS_UHD_HIGH_W         3840
#define VPSS_UHD_HIGH_H         2160
#else
#define VPSS_UHD_HIGH_W         1920
#define VPSS_UHD_HIGH_H         2160
#endif

#ifdef VPSS_SUPPORT_PROC_V2
#define COLOR_NORMAL            "\033[0m"
#define COLOR_BLACK             "\033[30m"
#define COLOR_GRAY              "\033[1;30m"
#define COLOR_RED               "\033[1;31m"
#define COLOR_GREEN             "\033[1;32m"
#define COLOR_YELLOW            "\033[1;33m"
#define COLOR_BLUE              "\033[1;34m"
#define COLOR_MAGENTA           "\033[1;35m"
#define COLOR_AQUA              "\033[1;36m"
#define COLOR_WHITE             "\033[1;37m"
#define BLINK                   "\033[5m"
#define VPSS_PROC_GAP "------------------------------------------------------------------------------------------------------------------"
#define VPSS_PROC_LEVEL1 "\n|-->"
#define VPSS_PROC_LEVEL2 "\n|---"
#define VPSS_PROC_LEVEL3 "\n|   |---"
#define VPSS_PROC_LEVEL4 "\n|   |   |---"
#define VPSS_PROC_LEVEL5 "\n|   |   |   "
#define VPSS_PROC_PRINT_ENUM(val, max, valstr) (HI_CHAR*)(((val) < (max)) ? valstr[(val)] : (HI_U8*)"Invalid")
#define VPSS_PROC_PRINT_YN(cdt) ((HI_TRUE == (cdt)) ? "Y" : "N")
#define VPSS_PROC_PRINT_YN_COL(cdt) ((HI_TRUE == (cdt)) ? COLOR_RED"Y"COLOR_NORMAL : "N")
#endif


#endif
