#ifndef __VPSS_CBB_FRAME_H__
#define __VPSS_CBB_FRAME_H__

#include "vpss_cbb_common.h"
#define CBB_TEST      0

typedef struct
{
    HI_U32              u32Width;
    HI_U32              u32Height;
    HI_RECT_S           stOffset;
    CBB_FRAME_ADDR_S    stAddr[CBB_FREAM_BUF_CNT];// 定义多组地址使用bit宽度区分
    CBB_BITWIDTH_E      enBitWidth;
    //CBB_PIXEL_FMT_E       enPixelFmt;
    HI_DRV_PIX_FORMAT_E enPixelFmt;
    HI_BOOL             bSecure;
    HI_BOOL             bCompress;
    HI_BOOL             bProgressive;
    HI_BOOL             bTopFirst;
    HI_BOOL             bTop;

    //VC_1    stVcInfo;
} CBB_FRAME_S;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
#if 0
typedef enum hiDRV_PIX_FORMAT_E
{
    /* RGB formats */
    HI_DRV_PIX_FMT_RGB332 = 0, /*  8  RGB-3-3-2     */
    HI_DRV_PIX_FMT_RGB444  ,   /* 16  xxxxrrrr ggggbbbb */
    HI_DRV_PIX_FMT_RGB555  ,   /* 16  RGB-5-5-5     */
    HI_DRV_PIX_FMT_RGB565  ,   /* 16  RGB-5-6-5     */
    HI_DRV_PIX_FMT_BGR565  ,   /* 16  RGB-5-6-5     */
    HI_DRV_PIX_FMT_RGB555X ,   /* 16  RGB-5-5-5 BE  */
    HI_DRV_PIX_FMT_RGB565X ,   /* 16  RGB-5-6-5 BE  */
    HI_DRV_PIX_FMT_BGR666  ,   /* 18  BGR-6-6-6   */
    HI_DRV_PIX_FMT_BGR24   ,   /* 24  BGR-8-8-8     */
    HI_DRV_PIX_FMT_RGB24   ,   /* 24  RGB-8-8-8     */
    HI_DRV_PIX_FMT_BGR32   ,   /* 32  BGR-8-8-8-8   */
    HI_DRV_PIX_FMT_RGB32   ,   /* 32  RGB-8-8-8-8   */

    /****** HISI CLUT formats ******/
    HI_DRV_PIX_FMT_CLUT_1BPP,
    HI_DRV_PIX_FMT_CLUT_2BPP,
    HI_DRV_PIX_FMT_CLUT_4BPP,
    HI_DRV_PIX_FMT_CLUT_8BPP,
    HI_DRV_PIX_FMT_ACLUT_44,
    HI_DRV_PIX_FMT_ACLUT_88,

    /****** HISI 16bit RGB formats ******/
    HI_DRV_PIX_FMT_ARGB4444,
    HI_DRV_PIX_FMT_ABGR4444,
    HI_DRV_PIX_FMT_RGBA4444,

    HI_DRV_PIX_FMT_ARGB1555,
    HI_DRV_PIX_FMT_ABGR1555,
    HI_DRV_PIX_FMT_RGBA5551,

    /****** HISI 24bit RGB formats ******/
    HI_DRV_PIX_FMT_ARGB8565,
    HI_DRV_PIX_FMT_ABGR8565,
    HI_DRV_PIX_FMT_RGBA5658,

    HI_DRV_PIX_FMT_ARGB6666,
    HI_DRV_PIX_FMT_RGBA6666,

    /****** HISI 32bit RGB formats ******/
    HI_DRV_PIX_FMT_ARGB8888,
    HI_DRV_PIX_FMT_ABGR8888,
    HI_DRV_PIX_FMT_RGBA8888,

    HI_DRV_PIX_FMT_AYUV8888,
    HI_DRV_PIX_FMT_YUVA8888,

    /* Grey formats */
    HI_DRV_PIX_FMT_GREY    ,    /*  8  Greyscale     */
    HI_DRV_PIX_FMT_Y4      ,    /*  4  Greyscale     */
    HI_DRV_PIX_FMT_Y6      ,    /*  6  Greyscale     */
    HI_DRV_PIX_FMT_Y10     ,    /* 10  Greyscale     */
    HI_DRV_PIX_FMT_Y12     ,    /* 12  Greyscale     */
    HI_DRV_PIX_FMT_Y16     ,    /* 16  Greyscale     */

    /* Grey bit-packed formats */
    HI_DRV_PIX_FMT_Y10BPACK    ,   /* 10  Greyscale bit-packed */

    /* Palette formats */
    HI_DRV_PIX_FMT_PAL8    ,    /*  8  8-bit palette */

    /* Luminance+Chrominance formats */
    HI_DRV_PIX_FMT_YVU410  ,    /*  9  YVU 4:1:0     */
    HI_DRV_PIX_FMT_YVU420  ,    /* 12  YVU 4:2:0     */
    HI_DRV_PIX_FMT_YUYV    ,    /* 16  YUV 4:2:2     */
    HI_DRV_PIX_FMT_YYUV    ,    /* 16  YUV 4:2:2     */
    HI_DRV_PIX_FMT_YVYU    ,    /* 16  YVU 4:2:2 */
    HI_DRV_PIX_FMT_UYVY    ,    /* 16  YUV 4:2:2     */
    HI_DRV_PIX_FMT_VYUY    ,    /* 16  YUV 4:2:2     */
    HI_DRV_PIX_FMT_YUV422P ,    /* 16  YVU422 planar */
    HI_DRV_PIX_FMT_YUV411P ,    /* 16  YVU411 planar */
    HI_DRV_PIX_FMT_Y41P    ,    /* 12  YUV 4:1:1     */
    HI_DRV_PIX_FMT_YUV444  ,    /* 16  xxxxyyyy uuuuvvvv */
    HI_DRV_PIX_FMT_YUV555  ,    /* 16  YUV-5-5-5     */
    HI_DRV_PIX_FMT_YUV565  ,    /* 16  YUV-5-6-5     */
    HI_DRV_PIX_FMT_YUV32   ,    /* 32  YUV-8-8-8-8   */
    HI_DRV_PIX_FMT_YUV410  ,    /*  9  YUV 4:1:0     */
    HI_DRV_PIX_FMT_YUV420  ,    /* 12  YUV 4:2:0     */
    HI_DRV_PIX_FMT_HI240   ,    /*  8  8-bit color   */
    HI_DRV_PIX_FMT_HM12    ,    /*  8  YUV 4:2:0 16x16 macroblocks */
    HI_DRV_PIX_FMT_M420    ,    /* 12  YUV 4:2:0 2 lines y,
                                       1 line uv interleaved */

    /* two planes -- one Y, one Cr + Cb interleaved  */
    HI_DRV_PIX_FMT_NV08    ,     /*08  Y/CbCr 4:0:0 @*/
    HI_DRV_PIX_FMT_NV80    ,     /*08  Y/CrCb 4:0:0 @*/
    HI_DRV_PIX_FMT_NV12    ,    /* 12  Y/CbCr 4:2:0  */
    HI_DRV_PIX_FMT_NV21    ,    /* 12  Y/CrCb 4:2:0  */
    HI_DRV_PIX_FMT_NV12_411,    /* 12  Y/CbCr 4:1:1  @*/
    HI_DRV_PIX_FMT_NV16    ,    /* 16  Y/CbCr 4:2:2  */
    HI_DRV_PIX_FMT_NV61    ,    /* 16  Y/CrCb 4:2:2  */
    HI_DRV_PIX_FMT_NV16_2X1,    /* 16  Y/CbCr 4:2:2 2X1 @*/
    HI_DRV_PIX_FMT_NV61_2X1,    /* 16  Y/CrCb 4:2:2  2X1 @*/
    HI_DRV_PIX_FMT_NV24    ,    /* 24  Y/CbCr 4:4:4  */
    HI_DRV_PIX_FMT_NV42    ,    /* 24  Y/CrCb 4:4:4  */
    HI_DRV_PIX_FMT_NV42_RGB,    /* 24  G/RB 4:4:4  */

    /* two non contiguous planes - one Y, one Cr + Cb interleaved  */
    HI_DRV__PIX_FMT_NV12M  ,    /* 12  Y/CbCr 4:2:0  */
    HI_DRV__PIX_FMT_NV12MT ,    /* 12  Y/CbCr 4:2:0 64x32 macroblocks */

    /* three non contiguous planes - Y, Cb, Cr */
    HI_DRV_PIX_FMT_YUV420M ,    /* 12  YUV420 planar */

    /* Bayer formats - see http://www.siliconimaging.com/RGB%20Bayer.htm */
    HI_DRV_PIX_FMT_SBGGR8  ,    /*  8  BGBG.. GRGR.. */
    HI_DRV_PIX_FMT_SGBRG8  ,    /*  8  GBGB.. RGRG.. */
    HI_DRV_PIX_FMT_SGRBG8  ,    /*  8  GRGR.. BGBG.. */
    HI_DRV_PIX_FMT_SRGGB8  ,    /*  8  RGRG.. GBGB.. */
    HI_DRV_PIX_FMT_SBGGR10 ,    /* 10  BGBG.. GRGR.. */
    HI_DRV_PIX_FMT_SGBRG10 ,    /* 10  GBGB.. RGRG.. */
    HI_DRV_PIX_FMT_SGRBG10 ,    /* 10  GRGR.. BGBG.. */
    HI_DRV_PIX_FMT_SRGGB10 ,    /* 10  RGRG.. GBGB.. */
    HI_DRV_PIX_FMT_SBGGR12 ,    /* 12  BGBG.. GRGR.. */
    HI_DRV_PIX_FMT_SGBRG12 ,    /* 12  GBGB.. RGRG.. */
    HI_DRV_PIX_FMT_SGRBG12 ,    /* 12  GRGR.. BGBG.. */
    HI_DRV_PIX_FMT_SRGGB12 ,    /* 12  RGRG.. GBGB.. */

    /****** HISI Luminance+Chrominance formats ******/

    /****** HISI  contiguoustwo planes -- one Y, one Cr + Cb interleaved ******/
    HI_DRV_PIX_FMT_NV08_CMP,     /*08   Y/CbCr 4:0:0 compressed @*/
    HI_DRV_PIX_FMT_NV80_CMP,     /*08   Y/CrCb 4:0:0 compressed @*/
    HI_DRV_PIX_FMT_NV12_CMP ,    /* 12  Y/CbCr 4:2:0 compressed */
    HI_DRV_PIX_FMT_NV21_CMP ,    /* 12  Y/CrCb 4:2:0 compressed */
    HI_DRV_PIX_FMT_NV16_CMP ,    /* 16  Y/CbCr 4:2:2 compressed */
    HI_DRV_PIX_FMT_NV61_CMP ,    /* 16  Y/CrCb 4:2:2 compressed */
    HI_DRV_PIX_FMT_NV16_2X1_CMP,    /* 16  Y/CbCr 4:2:2   2X1@*/
    HI_DRV_PIX_FMT_NV61_2X1_CMP,    /* 16  Y/CrCb 4:2:2  2X1@*/
    HI_DRV_PIX_FMT_NV24_CMP ,    /* 24  Y/CbCr 4:4:4 compressed */
    HI_DRV_PIX_FMT_NV42_CMP ,    /* 24  Y/CrCb 4:4:4 compressed */

    HI_DRV_PIX_FMT_NV12_TILE,    /* 12 tile  */
    HI_DRV_PIX_FMT_NV21_TILE,    /* 21 tile  */
    HI_DRV_PIX_FMT_YUV400_TILE,    /* 21 tile  */

    HI_DRV_PIX_FMT_NV12_TILE_CMP,   /* 12 tile compressed */
    HI_DRV_PIX_FMT_NV21_TILE_CMP,   /* 21 tile compressed */

    /****** HISI three non contiguous planes - Y, Cb, Cr ******/
    HI_DRV_PIX_FMT_YUV400  ,   /*08  YUV400 planar @*/
    HI_DRV_PIX_FMT_YUV410p  ,   /*10  YUV410 planar @*/
    HI_DRV_PIX_FMT_YUV420p ,   /*12  YUV420 planar @*/
    HI_DRV_PIX_FMT_YUV411  ,   /*12  YUV411  planar @*/
    HI_DRV_PIX_FMT_YUV422_1X2, /*16  YUV422  planar 1X2 @*/
    HI_DRV_PIX_FMT_YUV422_2X1, /*16  YUV422  planar 2X1@*/
    HI_DRV_PIX_FMT_YUV_444 ,   /*24  YUV444  planar @*/

    /****** HISI three non contiguous planes - Y, Cb, Cr ******/

    HI_DRV_PIX_BUTT


} HI_DRV_PIX_FORMAT_E;
#endif
#if 0
typedef enum hiREG_DITHER_MODE_E
{
    REG_DITHER_MODE_DITHER = 0,
    REG_DITHER_MODE_ROUND,
    REG_DITHER_MODE_BUTT

} REG_DITHER_MODE_E;
#endif

extern HI_S32 CBB_CfgFrm_ReadCur(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadNx1(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadNx2(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadRee(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadRef(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_WriteCue(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_WriteRfr(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, HI_BOOL bEnable);
extern HI_S32 CBB_CfgFrm_WriteVhd0(CBB_FRAME_S *pstFrmCfg, HI_VOID *pArgs, CBB_REG_ADDR_S stRegAddr);
extern HI_U32 CBB_FrameFmtTrans( HI_DRV_PIX_FORMAT_E    enPixelFmt );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif

