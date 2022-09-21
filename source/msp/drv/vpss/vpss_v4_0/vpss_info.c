#include "vpss_info.h"
#include "drv_vdec_ext.h"
#include "vpss_in_common.h"
#include "hi_drv_proc.h"
#include "vpss_ctrl.h"
#include "vpss_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct
{
    char *pInputString;
    HI_U32 u32Context;
} VPSS_PROC_REF_TABLE_S;

HI_U8 *g_pAlgModeString[4] =
{
    "off",
    "on",
    "auto",
    "butt",
};
HI_U8 *g_pInstState[3] =
{
    "stop",
    "working",
    "butt",
};
HI_U8 *g_pProgDetectString[4] =
{
    "P",
    "I",
    "auto",
    "butt",
};
HI_U8 *g_pRotationString[5] =
{
    "00",
    "90",
    "180",
    "270",
    "butt",
};
HI_U8 *g_pDeiString[9] =
{
    "off",
    "auto",
    "2 field",
    "3 field",
    "4 field",
    "5 field",
    "6 field",
    "7 field",
    "butt",
};

HI_U8 *g_pSrcMutualString[3] =
{
    "src active",
    "vpss active",
    "butt",
};

HI_U8 *g_pPixString[14] =
{
    "YCbCr420",
    "YCrCb420",
    "YCbCr411",
    "YCbCr422",
    "YCrCb422",
    "YCbCr422_2X1",
    "YCrCb422_2X1",
    "YCbCr420_cmp",
    "YCrCb420_cmp",
    "YCbCr422_cmp",
    "YCrCb422_cmp",
    "YCbCr422_2X1_cmp",
    "YCrCb422_2X1_cmp",
    "butt",
};

HI_U8 *g_pAspString[8] =
{
    "Full",
    "LBOX",
    "PANSCAN",
    "COMBINED",
    "FULL_H",
    "FULL_V",
    "CUSTOMER",
    "butt",
};

HI_U8 *g_pSrcModuleString[10] =
{
    "Vdec",
    "Unknow",
    "Unknow",
    "Unknow",
    "Unknow",
    "Unknow",
    "Unknow",
    "Vi",
    "Venc",
    "Unknow"
};

HI_U8 *g_pBufTypeString[3] =
{
    "vpss",
    "usr",
    "unknow",
};
HI_U8 *g_pRotateString[5] =
{
    "Rotation_00",
    "Rotation_90",
    "Rotation_180",
    "Rotation_270",
    "Rotation_butt",
};
HI_U8 *g_pCscString[20] =
{
    "UNKNOWN",
    "DEFAULT",
    "BT601_YUV",
    "BT601_YUV",
    "BT601_RGB",
    "BT601_RGB",
    "NTSC1953",
    "BT470_SYSTEM_M",
    "BT470_SYSTEM_BG",
    "BT709_YUV",
    "BT709_YUV",
    "BT709_RGB",
    "BT709_RGB",
    "REC709",
    "SMPT170M",
    "SMPT240M",
    "BT878",
    "XVYCC",
    "JPEG",
    "BUTT",
};
HI_U8 *g_pOutBitWidthString[] =
{
    "8BIT",
    "10BIT",
    "12BIT",
    "10BIT_CTS"
    "BUTT",
};
#ifdef VPSS_SUPPORT_PROC_V2
#define NUM_2_STRING(num) (#num)
HI_U8 *g_pcPixelFormatString[] =
{
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB332  ),  /*  8  RGB-3-3-2     */
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB444  ),     /* 16  xxxxrrrr ggggbbbb */
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB555  ),     /* 16  RGB-5-5-5     */
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB565  ),     /* 16  RGB-5-6-5     */
    NUM_2_STRING(HI_DRV_PIX_FMT_BGR565  ),    /* 16  RGB-5-6-5     */
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB555X ),    /* 16  RGB-5-5-5 BE  */
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB565X ),    /* 16  RGB-5-6-5 BE  */
    NUM_2_STRING(HI_DRV_PIX_FMT_BGR666  ),    /* 18  BGR-6-6-6   */
    NUM_2_STRING(HI_DRV_PIX_FMT_BGR24   ),    /* 24  BGR-8-8-8     */
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB24   ),    /* 24  RGB-8-8-8     */
    NUM_2_STRING(HI_DRV_PIX_FMT_BGR32   ),    /* 32  BGR-8-8-8-8   */
    NUM_2_STRING(HI_DRV_PIX_FMT_RGB32   ),    /* 32  RGB-8-8-8-8   */
    NUM_2_STRING(HI_DRV_PIX_FMT_CLUT_1BPP),
    NUM_2_STRING(HI_DRV_PIX_FMT_CLUT_2BPP),
    NUM_2_STRING(HI_DRV_PIX_FMT_CLUT_4BPP),
    NUM_2_STRING(HI_DRV_PIX_FMT_CLUT_8BPP),
    NUM_2_STRING(HI_DRV_PIX_FMT_ACLUT_44),
    NUM_2_STRING(HI_DRV_PIX_FMT_ACLUT_88),
    NUM_2_STRING(HI_DRV_PIX_FMT_ARGB4444),
    NUM_2_STRING(HI_DRV_PIX_FMT_ABGR4444),
    NUM_2_STRING(HI_DRV_PIX_FMT_RGBA4444),
    NUM_2_STRING(HI_DRV_PIX_FMT_ARGB1555),
    NUM_2_STRING(HI_DRV_PIX_FMT_ABGR1555),
    NUM_2_STRING(HI_DRV_PIX_FMT_RGBA5551),
    NUM_2_STRING(HI_DRV_PIX_FMT_ARGB8565),
    NUM_2_STRING(HI_DRV_PIX_FMT_ABGR8565),
    NUM_2_STRING(HI_DRV_PIX_FMT_RGBA5658),
    NUM_2_STRING(HI_DRV_PIX_FMT_ARGB6666),
    NUM_2_STRING(HI_DRV_PIX_FMT_RGBA6666),
    NUM_2_STRING(HI_DRV_PIX_FMT_ARGB8888),
    NUM_2_STRING(HI_DRV_PIX_FMT_ABGR8888),
    NUM_2_STRING(HI_DRV_PIX_FMT_RGBA8888),
    NUM_2_STRING(HI_DRV_PIX_FMT_AYUV8888),
    NUM_2_STRING(HI_DRV_PIX_FMT_YUVA8888),
    NUM_2_STRING(HI_DRV_PIX_FMT_GREY    ),     /*  8  Greyscale     */
    NUM_2_STRING(HI_DRV_PIX_FMT_Y4      ),     /*  4  Greyscale     */
    NUM_2_STRING(HI_DRV_PIX_FMT_Y6      ),     /*  6  Greyscale     */
    NUM_2_STRING(HI_DRV_PIX_FMT_Y10     ),     /* 10  Greyscale     */
    NUM_2_STRING(HI_DRV_PIX_FMT_Y12     ),     /* 12  Greyscale     */
    NUM_2_STRING(HI_DRV_PIX_FMT_Y16     ),     /* 16  Greyscale     */
    NUM_2_STRING(HI_DRV_PIX_FMT_Y10BPACK    ),    /* 10  Greyscale bit-packed */
    NUM_2_STRING(HI_DRV_PIX_FMT_PAL8    ),     /*  8  8-bit palette */
    NUM_2_STRING(HI_DRV_PIX_FMT_YVU410  ),     /*  9  YVU 4:1:0     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YVU420  ),     /* 12  YVU 4:2:0     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUYV    ),     /* 16  YUV 4:2:2     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YYUV    ),     /* 16  YUV 4:2:2     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YVYU    ),     /* 16  YVU 4:2:2 */
    NUM_2_STRING(HI_DRV_PIX_FMT_UYVY    ),     /* 16  YUV 4:2:2     */
    NUM_2_STRING(HI_DRV_PIX_FMT_VYUY    ),     /* 16  YUV 4:2:2     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV422P ),     /* 16  YVU422 planar */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV411P ),     /* 16  YVU411 planar */
    NUM_2_STRING(HI_DRV_PIX_FMT_Y41P    ),     /* 12  YUV 4:1:1     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV444  ),     /* 16  xxxxyyyy uuuuvvvv */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV555  ),     /* 16  YUV-5-5-5     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV565  ),     /* 16  YUV-5-6-5     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV32   ),     /* 32  YUV-8-8-8-8   */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV410  ),     /*  9  YUV 4:1:0     */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV420  ),     /* 12  YUV 4:2:0     */
    NUM_2_STRING(HI_DRV_PIX_FMT_HI240   ),     /*  8  8-bit color   */
    NUM_2_STRING(HI_DRV_PIX_FMT_HM12    ),     /*  8  YUV 4:2:0 16x16 macroblocks */
    NUM_2_STRING(HI_DRV_PIX_FMT_M420    ),     /* 12  YUV 4:2:0 2 lines y), 1 line uv interleaved */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV08    ),      /*08  Y/CbCr 4:0:0 @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV80    ),      /*08  Y/CrCb 4:0:0 @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV12    ),     /* 12  Y/CbCr 4:2:0  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV21    ),     /* 12  Y/CrCb 4:2:0  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV12_411),     /* 12  Y/CbCr 4:1:1  @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV16    ),     /* 16  Y/CbCr 4:2:2  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV61    ),     /* 16  Y/CrCb 4:2:2  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV16_2X1),     /* 16  Y/CbCr 4:2:2 2X1 @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV61_2X1),     /* 16  Y/CrCb 4:2:2  2X1 @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV24    ),     /* 24  Y/CbCr 4:4:4  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV42    ),     /* 24  Y/CrCb 4:4:4  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV42_RGB),     /* 24  G/RB 4:4:4  */
    NUM_2_STRING(HI_DRV__PIX_FMT_NV12M  ),     /* 12  Y/CbCr 4:2:0  */
    NUM_2_STRING(HI_DRV__PIX_FMT_NV12MT ),     /* 12  Y/CbCr 4:2:0 64x32 macroblocks */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV420M ),     /* 12  YUV420 planar */
    NUM_2_STRING(HI_DRV_PIX_FMT_SBGGR8  ),     /*  8  BGBG.. GRGR.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SGBRG8  ),     /*  8  GBGB.. RGRG.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SGRBG8  ),     /*  8  GRGR.. BGBG.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SRGGB8  ),     /*  8  RGRG.. GBGB.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SBGGR10 ),     /* 10  BGBG.. GRGR.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SGBRG10 ),     /* 10  GBGB.. RGRG.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SGRBG10 ),     /* 10  GRGR.. BGBG.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SRGGB10 ),     /* 10  RGRG.. GBGB.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SBGGR12 ),     /* 12  BGBG.. GRGR.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SGBRG12 ),     /* 12  GBGB.. RGRG.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SGRBG12 ),     /* 12  GRGR.. BGBG.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_SRGGB12 ),     /* 12  RGRG.. GBGB.. */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV08_CMP),      /*08   Y/CbCr 4:0:0 compressed @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV80_CMP),      /*08   Y/CrCb 4:0:0 compressed @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV12_CMP ),     /* 12  Y/CbCr 4:2:0 compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV21_CMP ),     /* 12  Y/CrCb 4:2:0 compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV16_CMP ),     /* 16  Y/CbCr 4:2:2 compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV61_CMP ),     /* 16  Y/CrCb 4:2:2 compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV16_2X1_CMP),     /* 16  Y/CbCr 4:2:2   2X1@*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV61_2X1_CMP),     /* 16  Y/CrCb 4:2:2  2X1@*/
    NUM_2_STRING(HI_DRV_PIX_FMT_NV24_CMP ),     /* 24  Y/CbCr 4:4:4 compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV42_CMP ),     /* 24  Y/CrCb 4:4:4 compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV12_TILE),     /* 12 tile  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV21_TILE),     /* 21 tile  */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV400_TILE),     /* 21 tile  */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV12_TILE_CMP),    /* 12 tile compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_NV21_TILE_CMP),    /* 21 tile compressed */
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV400  ),    /*08  YUV400 planar @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV410p  ),    /*10  YUV410 planar @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV420p ),    /*12  YUV420 planar @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV411  ),    /*12  YUV411  planar @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV422_1X2),  /*16  YUV422  planar 1X2 @*/
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV422_2X1),  /*16  YUV422  planar 2X1@*/
    NUM_2_STRING(HI_DRV_PIX_FMT_YUV_444 ),    /*24  YUV444  planar @*/
};
HI_U8 *g_pcFrameTypeString[] =
{
    NUM_2_STRING(SDR),          /*Normal SDR frame.*/
    NUM_2_STRING(DOLBY_BL),     /*Dolby BL frame.*/
    NUM_2_STRING(DOLBY_EL),     /*Dolby EL frame.*/
    NUM_2_STRING(HDR10),        /*HDR10 frame.*/
    NUM_2_STRING(HLG),          /*HLG frame.*/
    NUM_2_STRING(SLF),          /*SLF frame.*/
    NUM_2_STRING(TECHNICOLOR),  /*TECHNICOLOR frame.*/
};
HI_U8 *g_pc3DTypeString[] =
{
    NUM_2_STRING(NOT_STEREO),
    NUM_2_STRING(SBS),
    NUM_2_STRING(TAB),
    NUM_2_STRING(FPK),
    NUM_2_STRING(TILE),
};
HI_U8 *g_pcProDetectString[] =
{
    NUM_2_STRING(PRODETECT_PROGRESSIVE),
    NUM_2_STRING(PRODETECT_INTERLACE),
    NUM_2_STRING(PRODETECT_AUTO),
};
HI_U8 *g_pcProColorSpaceString[] =
{
    NUM_2_STRING(UNKNOWN),
    NUM_2_STRING(DEFAULT),
    NUM_2_STRING(BT601_YUV_LIMITED), /* BT.601 */
    NUM_2_STRING(BT601_YUV_FULL),
    NUM_2_STRING(BT601_RGB_LIMITED),
    NUM_2_STRING(BT601_RGB_FULL),
    NUM_2_STRING(NTSC1953),
    NUM_2_STRING(BT470_SYSTEM_M),
    NUM_2_STRING(BT470_SYSTEM_BG),
    NUM_2_STRING(BT709_YUV_LIMITED), /* BT.709 */
    NUM_2_STRING(BT709_YUV_FULL),
    NUM_2_STRING(BT709_RGB_LIMITED),
    NUM_2_STRING(BT709_RGB_FULL),
    NUM_2_STRING(BT2020_YUV_LIMITED), /* ::::Current Used:::: BT.2020 */
    NUM_2_STRING(BT2020_YUV_FULL),
    NUM_2_STRING(BT2020_RGB_LIMITED),
    NUM_2_STRING(BT2020_RGB_FULL),    /* ::::Current Used:::: */
    NUM_2_STRING(REC709),       /* HD and modern captures. */
    NUM_2_STRING(SMPT170M),  /* ITU-R 601 -- broadcast NTSC/PAL */
    NUM_2_STRING(SMPT240M),  /* 1125-Line (US) HDTV */
    NUM_2_STRING(BT878),     /* broken BT878 extents (601),  luma range 16-253 instead of 16-235) */
    NUM_2_STRING(XVYCC),
    NUM_2_STRING(JPEG),
};

#endif

HI_S32 VPSS_DBG_DbgInit(VPSS_DBG_S *pstDbg)
{
    HI_U32 u32Count;

    pstDbg->stInstDbg.unInfo.u64 = 0;

    pstDbg->stInstDbg.u32LastH = 0;
    pstDbg->stInstDbg.u32LastM = 0;
    pstDbg->stInstDbg.u32LastS = 0;
    pstDbg->stInstDbg.bResetPerFrame = HI_TRUE;
#ifdef VPSS_SUPPORT_PROC_V2
    pstDbg->stInstDbg.eProcPrintLevel = PROC_PRINT_LEVEL_ORI;
#endif
    /*TEST*/
    //pstDbg->stInstDbg.unInfo.bits.imginfo = 1;

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstDbg->stPortDbg[u32Count].unInfo.u64 = 0;

        pstDbg->stPortDbg[u32Count].u32LastH = 0;
        pstDbg->stPortDbg[u32Count].u32LastM = 0;
        pstDbg->stPortDbg[u32Count].u32LastS = 0;
        //pstDbg->stPortDbg[u32Count].unInfo.bits.frameinfo = 1;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_DbgDeInit(VPSS_DBG_S *pstDbg)
{
    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_SendDbgCmd_SaveYUV(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    HI_U32  u32Count = 0;

    VPSS_DBG_PORT_S *pstPortDbg;
    VPSS_DBG_INST_S *pstInstDbg;

    HI_U32 u32Hour = 0;
    HI_U32 u32Minute = 0;
    HI_U32 u32Second = 0;

    (HI_VOID)VPSS_OSAL_GetCurTime(&u32Hour, &u32Minute, &u32Second);

    switch (pstCmd->hDbgPart)
    {
        case DEF_DBG_SRC_ID:
            pstInstDbg = &(pstDbg->stInstDbg);
            pstInstDbg->unInfo.bits.writeyuv = HI_TRUE;
            pstInstDbg->unInfo.bits.start_index = (((HI_U32)pstCmd->hDbgValue) >> 16) & 0xFFFF;
            pstInstDbg->unInfo.bits.end_index = pstInstDbg->unInfo.bits.start_index
                                                + (((HI_U32)pstCmd->hDbgValue) & 0xFFFF);

            if (DBG_W_YUV == pstCmd->enDbgType)
            {
                pstInstDbg->unInfo.bits.writeyuv = HI_TRUE;
            }
            else
            {
                pstInstDbg->unInfo.bits.writestream = HI_TRUE;
            }

            break;
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            pstPortDbg->unInfo.bits.start_index = (((HI_U32)pstCmd->hDbgValue) >> 16) & 0xFFFF;
            pstPortDbg->unInfo.bits.end_index = pstPortDbg->unInfo.bits.start_index +
                                                (((((HI_U32)pstCmd->hDbgValue) & 0xFFFF) > 16) ? 16 : (((HI_U32)pstCmd->hDbgValue) & 0xFFFF));

            if (DBG_W_YUV == pstCmd->enDbgType)
            {
                pstPortDbg->unInfo.bits.writeyuv = HI_TRUE;
            }
            else if (DBG_W_YUV_IDX == pstCmd->enDbgType)
            {
                pstPortDbg->unInfo.bits.writestreamIdx = HI_TRUE;
                VPSS_PROC_MSG_PRINT("VPSS will save yuv from %d to %d\n", pstPortDbg->unInfo.bits.start_index,
                                    pstPortDbg->unInfo.bits.end_index);
            }
            else
            {
                pstPortDbg->unInfo.bits.writestream = HI_TRUE;
                VPSS_PROC_MSG_PRINT("VPSS will save yuv from %d to %d\n", pstPortDbg->unInfo.bits.start_index,
                                    pstPortDbg->unInfo.bits.end_index);
            }
            break;
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_SendDbgCmd_Rotation(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    HI_U32  u32Count = 0;
    VPSS_DBG_PORT_S *pstPortDbg;

    switch (pstCmd->hDbgPart)
    {
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);

            if (HI_DRV_VPSS_ROTATION_BUTT == pstCmd->hDbgValue)
            {
                pstPortDbg->unInfo.bits.dbg_rotation_en = HI_FALSE;

                VPSS_PROC_MSG_PRINT("set port%d rotation debug disable!!\n", u32Count);
            }
            else
            {
                pstPortDbg->unInfo.bits.dbg_rotation_en = HI_TRUE;

                pstPortDbg->unInfo.bits.dbg_rotation_angle = pstCmd->hDbgValue;
                VPSS_PROC_MSG_PRINT("set port%d rotation %d !!\n", u32Count, pstCmd->hDbgValue * 90);
            }

            break;
        default:
            VPSS_ERROR("Invalid Port %d\n", pstCmd->hDbgPart);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_SendDbgCmd_SetOutBitWidth(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    HI_U32  u32Count = 0;
    VPSS_DBG_PORT_S *pstPortDbg;

    switch (pstCmd->hDbgPart)
    {
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);

            if (HI_DRV_PIXEL_BITWIDTH_BUTT == (HI_DRV_PIXEL_BITWIDTH_E)pstCmd->hDbgValue)
            {
                pstPortDbg->unInfo.bits.dbg_output_bitwidth_en = HI_FALSE;

                VPSS_PROC_MSG_PRINT("set prot%d outbitwidth debug disable!!\n", u32Count);
            }
            else
            {
                pstPortDbg->unInfo.bits.dbg_output_bitwidth_en = HI_TRUE;
                pstPortDbg->unInfo.bits.output_bitwidth_mode = pstCmd->hDbgValue;

                VPSS_PROC_MSG_PRINT("set prot%d outbitwidth %d bit!!\n", u32Count, pstCmd->hDbgValue * 2 + 8);
            }

            break;
        default:
            VPSS_ERROR("Invalid Port %d\n", pstCmd->hDbgPart);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_SendDbgCmd_None(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    HI_U32  u32Count = 0;
    VPSS_DBG_PORT_S *pstPortDbg;
    VPSS_DBG_INST_S *pstInstDbg;

    switch (pstCmd->hDbgPart)
    {
        case DEF_DBG_SRC_ID:
            pstInstDbg = &(pstDbg->stInstDbg);
            memset(pstInstDbg, 0x0, sizeof(pstDbg->stInstDbg));
            break;
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count =  pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            memset(pstPortDbg, 0x0, sizeof(pstDbg->stPortDbg[u32Count]));
            break;
        default:
            break;
    }

    return HI_SUCCESS;
}
HI_S32 VPSS_DBG_SendDbgCmd_UVInvert(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    HI_U32  u32Count = 0;
    VPSS_DBG_PORT_S *pstPortDbg;

    switch (pstCmd->hDbgPart)
    {
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            pstPortDbg->unInfo.bits.uv_invert = pstCmd->hDbgValue;

            VPSS_PROC_MSG_PRINT("set prot%d uv Invert %s !!\n", u32Count,
                                (pstPortDbg->unInfo.bits.uv_invert == HI_TRUE) ? "ON" : "OFF");
            break;
        default:
            VPSS_ERROR("Invalid Port %d\n", pstCmd->hDbgPart);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_SendDbgCmd_SetUHD(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    VPSS_DBG_INST_S *pstInstDbg;

    switch (pstCmd->enDbgType)
    {
        case DBG_SET_UHD_LOW:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_SRC_ID:
                    pstInstDbg = &(pstDbg->stInstDbg);
                    pstInstDbg->u32UhdSetW = VPSS_UHD_LOW_W;
                    pstInstDbg->u32UhdSetH = VPSS_UHD_LOW_H;
                    break;
                default:
                    VPSS_ERROR("Invalid Setting Dst %d\n", pstCmd->hDbgPart);
            }
            break;
        case DBG_SET_UHD_MID:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_SRC_ID:
                    pstInstDbg = &(pstDbg->stInstDbg);
                    pstInstDbg->u32UhdSetW = VPSS_UHD_MIDDLE_W;
                    pstInstDbg->u32UhdSetH = VPSS_UHD_MIDDLE_H;
                    break;
                default:
                    VPSS_ERROR("Invalid Setting Dst %d\n", pstCmd->hDbgPart);
            }
            break;
        case DBG_SET_UHD_HIGH:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_SRC_ID:
                    pstInstDbg = &(pstDbg->stInstDbg);
                    pstInstDbg->u32UhdSetW = VPSS_UHD_HIGH_W;
                    pstInstDbg->u32UhdSetH = VPSS_UHD_HIGH_H;
                    break;
                default:
                    VPSS_ERROR("Invalid Setting Dst %d\n", pstCmd->hDbgPart);
            }
            break;
        case DBG_SET_UHD_USR:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_SRC_ID:
                    pstInstDbg = &(pstDbg->stInstDbg);
                    pstInstDbg->u32UhdSetW = 0;
                    pstInstDbg->u32UhdSetH = 0;
                    break;
                default:
                    VPSS_ERROR("Invalid Setting Dst %d\n", pstCmd->hDbgPart);
            }
            break;
        default:
            VPSS_ERROR("Cmd isn't Supported.\n");
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_SendDbgCmd_LBoxColor(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    HI_U32  u32Count = 0;
    VPSS_DBG_PORT_S *pstPortDbg;

    switch (pstCmd->hDbgPart)
    {
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);

            if (VPSS_COLOR_BUTT <= pstCmd->hDbgValue)
            {
                pstPortDbg->unInfo.bits.dbg_lbox_color_en = HI_FALSE;

                VPSS_PROC_MSG_PRINT("set prot%d letterbox color revise disable!!\n", u32Count);
            }
            else
            {
                pstPortDbg->unInfo.bits.dbg_lbox_color_en = HI_TRUE;
                pstPortDbg->unInfo.bits.dbg_lbox_color_mode = pstCmd->hDbgValue;
                VPSS_PROC_MSG_PRINT("set prot%d letterbox color %d !!\n", u32Count, pstCmd->hDbgValue);
            }

            break;
        default:
            VPSS_ERROR("Invalid Port %d\n", pstCmd->hDbgPart);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_SendDbgCmd(VPSS_DBG_S *pstDbg, VPSS_DBG_CMD_S *pstCmd)
{
    HI_U32  u32Count = 0;
    VPSS_DBG_PORT_S *pstPortDbg;
    VPSS_DBG_INST_S *pstInstDbg;

    switch (pstCmd->enDbgType)
    {
        case DBG_W_YUV:
        case DBG_W_YUV_IDX:
        case DBG_W_YUV_FILE:
            VPSS_DBG_SendDbgCmd_SaveYUV(pstDbg, pstCmd);
            break;

        case DBG_INFO_FRM:

            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_SRC_ID:
                    pstInstDbg = &(pstDbg->stInstDbg);
                    pstInstDbg->unInfo.bits.imginfo = HI_TRUE;
                    pstInstDbg->unInfo.bits.start_index = (((HI_U32)pstCmd->hDbgValue) >> 16) & 0xFFFF;
                    pstInstDbg->unInfo.bits.end_index = pstInstDbg->unInfo.bits.start_index
                                                        + (pstCmd->hDbgValue & 0xFFFF);
                    VPSS_PROC_MSG_PRINT("Print src image info from index %d to %d\n",
                                        pstInstDbg->unInfo.bits.start_index,
                                        pstInstDbg->unInfo.bits.end_index);
                    break;
                case DEF_DBG_PORT0_ID:
                case DEF_DBG_PORT1_ID:
                case DEF_DBG_PORT2_ID:
                    u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
                    pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
                    pstPortDbg->unInfo.bits.frameinfo = HI_TRUE;
                    break;
                default:
                    break;
            }
            break;
        case DBG_INFO_ASP:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_PORT0_ID:
                case DEF_DBG_PORT1_ID:
                case DEF_DBG_PORT2_ID:
                    u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
                    pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
                    pstPortDbg->unInfo.bits.asp = HI_TRUE;
                    break;
                default:
                    break;
            }
            break;
        case DBG_INFO_NONE:
            VPSS_DBG_SendDbgCmd_None(pstDbg, pstCmd);

            break;

        case DBG_SET_UHD_LOW:
        case DBG_SET_UHD_MID:
        case DBG_SET_UHD_HIGH:
        case DBG_SET_UHD_USR:
            VPSS_DBG_SendDbgCmd_SetUHD(pstDbg, pstCmd);
            break;

        case DBG_SET_UV_INVERT:
            VPSS_DBG_SendDbgCmd_UVInvert(pstDbg, pstCmd);
            break;

        case DBG_SET_CMP_ON:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_PORT0_ID:
                    u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
                    pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
                    pstPortDbg->unInfo.bits.cmp = 1;
                    VPSS_PROC_MSG_PRINT("set prot%d cmp on !!\n", u32Count);
                    break;
                default:
                    VPSS_ERROR("Invalid Port %d, only HD port support cmp\n", u32Count);
            }
            break;

        case DBG_SET_CMP_OFF:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_PORT0_ID:
                    u32Count = pstCmd->hDbgPart - DEF_DBG_PORT0_ID;
                    pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
                    pstPortDbg->unInfo.bits.cmp = 2;
                    VPSS_PROC_MSG_PRINT("set prot%d cmp off !!\n", u32Count);
                    break;
                default:
                    VPSS_ERROR("Invalid Port %d, only HD port support cmp\n", u32Count);
            }
            break;

        case DBG_SET_I2P:
            switch (pstCmd->hDbgPart)
            {
                case DEF_DBG_SRC_ID:
                    pstInstDbg = &(pstDbg->stInstDbg);
                    pstInstDbg->unInfo.bits.dei = pstCmd->hDbgValue ;

                    VPSS_PROC_MSG_PRINT("set interlace to progress %s !!\n",
                                        (pstInstDbg->unInfo.bits.dei == HI_TRUE) ? "ON" : "OFF");
                    break;
                default:
                    VPSS_ERROR("Invalid input %d\n", pstCmd->hDbgPart);
            }
            break;

        case DBG_SET_RATATION:
            VPSS_DBG_SendDbgCmd_Rotation(pstDbg, pstCmd);
            break;

        case DBG_SET_OUTBITWIDTH:
            VPSS_DBG_SendDbgCmd_SetOutBitWidth(pstDbg, pstCmd);
            break;

        case DBG_REVISE_SRC_WH:
            pstInstDbg = &(pstDbg->stInstDbg);
            pstInstDbg->bReviseSrcWH = HI_TRUE;
            pstInstDbg->u32SrcWH = pstCmd->hDbgValue;
            VPSS_PROC_MSG_PRINT("Revise src image width*height %d*%d \n",
                                (((HI_U32)pstCmd->hDbgValue) >> 16) & 0xFFFF, ((HI_U32)pstCmd->hDbgValue) & 0xFFFF);
            break;
        case DBG_SET_LBX_COLOR:
            VPSS_DBG_SendDbgCmd_LBoxColor(pstDbg, pstCmd);
            break;
        default:
            VPSS_ERROR("Cmd isn't Supported.\n");
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_ReplyDbgCmd_SaveYUV(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_DRV_VIDEO_FRAME_S *pstFrm;
    HI_U32 u32Count;
    HI_U32 u32DbgPart;
    VPSS_DBG_PORT_S *pstPortDbg;
    HI_DRV_VID_FRAME_ADDR_S stTmpAddr;
    HI_S8 chFile[DEF_FILE_NAMELENGTH];
    HI_U32 u32Hour = 0;
    HI_U32 u32Minute = 0;
    HI_U32 u32Second = 0;
    HI_U16 u16StartIdx;
    HI_U16 u16EndIdx;
    HI_BOOL bExpectFrame;

    u32DbgPart = *((HI_U32 *)para1);

    (HI_VOID)VPSS_OSAL_GetCurTime(&u32Hour, &u32Minute, &u32Second);
    pstFrm = (HI_DRV_VIDEO_FRAME_S *)para2;

    switch (u32DbgPart)
    {
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);

            bExpectFrame = HI_FALSE;
            u16StartIdx = pstPortDbg->unInfo.bits.start_index;
            u16EndIdx = pstPortDbg->unInfo.bits.end_index;

            if ((enCmd == DBG_W_YUV) && (pstPortDbg->unInfo.bits.writeyuv))
            {
                bExpectFrame = HI_TRUE;
            }
            else if (((enCmd == DBG_W_YUV_FILE) && pstPortDbg->unInfo.bits.writestream)
                     || ((enCmd == DBG_W_YUV_IDX) && pstPortDbg->unInfo.bits.writestreamIdx))
            {
                if ((u16StartIdx <= pstFrm->u32FrameIndex) && (pstFrm->u32FrameIndex <= u16EndIdx))
                {
                    bExpectFrame = HI_TRUE;
                }
            }

            if (HI_FALSE == bExpectFrame)
            {
                return HI_SUCCESS;
            }

            if (pstPortDbg->unInfo.bits.writestreamIdx || pstPortDbg->unInfo.bits.writeyuv)
            {
                HI_OSAL_Snprintf(chFile, DEF_FILE_NAMELENGTH, "vpss_p%d_LEye_%dx%d_idx%d_%02d_%02d_%02d.yuv", u32Count,
                                 pstFrm->u32Width, pstFrm->u32Height, pstFrm->u32FrameIndex, u32Hour, u32Minute, u32Second);
            }
            else
            {
                HI_OSAL_Snprintf(chFile, DEF_FILE_NAMELENGTH, "vpss_p%d_LEye_%dx%d_idx(%d_%d).yuv", u32Count,
                                 pstFrm->u32Width, pstFrm->u32Height, u16StartIdx, u16EndIdx);
            }

            VPSS_OSAL_WRITEYUV(pstFrm, chFile);
            if (pstFrm->eFrmType == HI_DRV_FT_FPK)
            {
                if (pstPortDbg->unInfo.bits.writestreamIdx || pstPortDbg->unInfo.bits.writeyuv)
                {
                    HI_OSAL_Snprintf(chFile, DEF_FILE_NAMELENGTH, "vpss_p%d_REye_%dx%d_idx%d_%02d_%02d_%02d.yuv", u32Count,
                                     pstFrm->u32Width, pstFrm->u32Height, pstFrm->u32FrameIndex, u32Hour, u32Minute, u32Second);
                }
                else
                {
                    HI_OSAL_Snprintf(chFile, DEF_FILE_NAMELENGTH, "vpss_p%d_REye_%dx%d_idx(%d_%d).yuv", u32Count,
                                     pstFrm->u32Width, pstFrm->u32Height, u16StartIdx, u16EndIdx);
                }

                VPSS_SAFE_MEMCPY(&stTmpAddr, &pstFrm->stBufAddr[0], sizeof(HI_DRV_VID_FRAME_ADDR_S));

                VPSS_SAFE_MEMCPY(&(pstFrm->stBufAddr[0]),
                                 &(pstFrm->stBufAddr[1]),
                                 sizeof(HI_DRV_VID_FRAME_ADDR_S));

                VPSS_OSAL_WRITEYUV(pstFrm, chFile);

                VPSS_SAFE_MEMCPY(&(pstFrm->stBufAddr[0]),
                                 &(stTmpAddr),
                                 sizeof(HI_DRV_VID_FRAME_ADDR_S));
            }


            if (pstPortDbg->unInfo.bits.writeyuv)
            {
                pstPortDbg->unInfo.bits.writeyuv = HI_FALSE;
            }
            else
            {
                if (pstFrm->u32FrameIndex > u16EndIdx)
                {
                    pstPortDbg->unInfo.bits.writestream = HI_FALSE;
                    pstPortDbg->unInfo.bits.writestreamIdx = HI_FALSE;
                }
            }

            break;
        case DEF_DBG_SRC_ID:
            VPSS_PROC_MSG_PRINT("Do not support saving src frame!\n");
            break;
        default:
            VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_ReplyDbgCmd_PrintFrameInfo(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_DRV_VIDEO_FRAME_S *pstFrm;
    HI_U32 u32Count;
    HI_U32 u32DbgPart;
    VPSS_DBG_PORT_S *pstPortDbg;
    VPSS_SET_DBG_INFO_S *pstDbginfo;

    u32DbgPart = *((HI_U32 *)para1);

    switch (u32DbgPart)
    {
        case DEF_DBG_SRC_ID:
            pstDbginfo = (VPSS_SET_DBG_INFO_S *)para2;
            pstDbginfo->bPrintSrcInfo = pstDbg->stInstDbg.unInfo.bits.imginfo;
            if (HI_TRUE == pstDbginfo->bPrintSrcInfo)
            {
                pstDbginfo->u32PrintStartIndex = pstDbg->stInstDbg.unInfo.bits.start_index;
                pstDbginfo->u32PrintEndIndex = pstDbg->stInstDbg.unInfo.bits.end_index;
            }
            break;
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            pstFrm = (HI_DRV_VIDEO_FRAME_S *)para2;
            u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            if (pstPortDbg->unInfo.bits.frameinfo)
            {
                VPSS_DBG_PrintFrameInfo(pstFrm, HI_FALSE, 0, 0xFFFFFFFF);
            }
            break;
        default:
            VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_ReplyDbgCmd_UVInvert(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_U32 u32Count;
    HI_U32 u32DbgPart;
    VPSS_DBG_PORT_S *pstPortDbg;
    HI_BOOL *bUV_Invert;

    u32DbgPart = *((HI_U32 *)para1);

    switch (u32DbgPart)
    {


        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            bUV_Invert = (HI_BOOL *)para2;

            if (pstPortDbg->unInfo.bits.uv_invert)
            {
                *bUV_Invert = HI_TRUE;
            }
            else
            {
                *bUV_Invert = HI_FALSE;
            }
            break;
        default:
            VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_ReplyDbgCmd_Rotation(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_U32 u32Count;
    HI_U32 u32DbgPart;
    VPSS_DBG_PORT_S *pstPortDbg;
    HI_DRV_VPSS_ROTATION_E *peRotation;

    u32DbgPart = *((HI_U32 *)para1);

    switch (u32DbgPart)
    {

        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:

            u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            peRotation = (HI_DRV_VPSS_ROTATION_E *)para2;

            if (pstPortDbg->unInfo.bits.dbg_rotation_en)
            {
                *peRotation = pstPortDbg->unInfo.bits.dbg_rotation_angle;
            }
            else
            {
                //do not change external config
            }
            break;
        default:
            VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_ReplyDbgCmd_SetOutBitWidth(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_U32 u32Count;
    HI_U32 u32DbgPart;
    VPSS_DBG_PORT_S *pstPortDbg;
    HI_DRV_PIXEL_BITWIDTH_E *peOutBitWidth;

    u32DbgPart = *((HI_U32 *)para1);

    switch (u32DbgPart)
    {

        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:

            u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            peOutBitWidth = (HI_DRV_PIXEL_BITWIDTH_E *)para2;

            if (pstPortDbg->unInfo.bits.dbg_output_bitwidth_en)
            {
                *peOutBitWidth = pstPortDbg->unInfo.bits.output_bitwidth_mode;
            }
            break;
        default:
            VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_DBG_ReplyDbgCmd_SetSrcI2P(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_U32 u32DbgPart;
    HI_BOOL *bDei;

    u32DbgPart = *((HI_U32 *)para1);
    switch (u32DbgPart)
    {
        case DEF_DBG_SRC_ID:
            bDei = (HI_BOOL *)para2;

            if (pstDbg->stInstDbg.unInfo.bits.dei)
            {
                *bDei = HI_TRUE;
            }
            else
            {
                *bDei = HI_FALSE;
            }
            break;
        default:
            VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_DBG_ReplyDbgCmd_LBoxColor(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_U32 u32Count;
    HI_U32 u32DbgPart;
    VPSS_DBG_PORT_S *pstPortDbg;
    VPSS_COLOR_E *peLBoxColor;

    u32DbgPart = *((HI_U32 *)para1);

    switch (u32DbgPart)
    {
        case DEF_DBG_PORT0_ID:
        case DEF_DBG_PORT1_ID:
        case DEF_DBG_PORT2_ID:
            u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
            pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
            peLBoxColor = (VPSS_COLOR_E *)para2;

            if (pstPortDbg->unInfo.bits.dbg_lbox_color_en)
            {
                *peLBoxColor = pstPortDbg->unInfo.bits.dbg_lbox_color_mode;
            }
            else
            {
                *peLBoxColor = VPSS_COLOR_BLACK;
            }
            break;
        default:
            VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_DBG_ReplyDbgCmd(VPSS_DBG_S *pstDbg, VPSS_DEBUG_E enCmd, HI_VOID *para1, HI_VOID *para2)
{
    HI_U32 u32Count;
    HI_U32 u32DbgPart;
    VPSS_DBG_PORT_S *pstPortDbg;

    u32DbgPart = *((HI_U32 *)para1);
    switch (enCmd)
    {
        case DBG_W_YUV:
        case DBG_W_YUV_IDX:
        case DBG_W_YUV_FILE:
            VPSS_DBG_ReplyDbgCmd_SaveYUV(pstDbg, enCmd, para1, para2);
            break;
        case DBG_INFO_FRM:
            VPSS_DBG_ReplyDbgCmd_PrintFrameInfo(pstDbg, enCmd, para1, para2);
            break;
        case DBG_INFO_ASP:
            break;
        case DBG_SET_UHD:
        {
            VPSS_DBG_INST_S *pstInstDbg;
            HI_U32 *pu32LevelW;
            HI_U32 *pu32LevelH;

            pstInstDbg = &(pstDbg->stInstDbg);
            pu32LevelW = (HI_U32 *)para1;
            pu32LevelH = (HI_U32 *)para2;

            if (pstInstDbg->u32UhdSetW != 0 && pstInstDbg->u32UhdSetH != 0)
            {
                *pu32LevelW = pstInstDbg->u32UhdSetW;
                *pu32LevelH = pstInstDbg->u32UhdSetH;
            }
        }
        break;
        case DBG_SET_UV_INVERT:
            VPSS_DBG_ReplyDbgCmd_UVInvert(pstDbg, enCmd, para1, para2);
            break;
        case DBG_SET_CMP_ON:
            switch (u32DbgPart)
            {
                    HI_U32 *bCmpflag;

                case DEF_DBG_PORT0_ID:
                case DEF_DBG_PORT1_ID:
                case DEF_DBG_PORT2_ID:
                    u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
                    pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
                    bCmpflag = (HI_U32 *)para2;

                    if (pstPortDbg->unInfo.bits.cmp == 1 )
                    {
                        *bCmpflag = 1;
                    }
                    break;
                default:
                    VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
            }
            break;
        case DBG_SET_CMP_OFF:
            switch (u32DbgPart)
            {
                    HI_U32 *bCmpflag;

                case DEF_DBG_PORT0_ID:
                case DEF_DBG_PORT1_ID:
                case DEF_DBG_PORT2_ID:
                    u32Count = u32DbgPart - DEF_DBG_PORT0_ID;
                    pstPortDbg = &(pstDbg->stPortDbg[u32Count]);
                    bCmpflag = (HI_U32 *)para2;

                    if (pstPortDbg->unInfo.bits.cmp == 2 )
                    {
                        *bCmpflag = 2;
                    }
                    break;
                default:
                    VPSS_ERROR("Invalid para2 %#x\n", u32DbgPart);
            }
            break;
        case DBG_SET_I2P:
            VPSS_DBG_ReplyDbgCmd_SetSrcI2P(pstDbg, enCmd, para1, para2);
            break;

        case DBG_SET_FRMRATE:
        {
            HI_BOOL *frameEn;
            HI_U32  *framerate;

            frameEn = (HI_BOOL *)para1;
            framerate = (HI_U32 *)para2;

            if (pstDbg->stInstDbg.unInfo.bits.frameEn)
            {
                *frameEn = HI_TRUE;
            }
            else
            {
                *frameEn = HI_FALSE;
            }

            *framerate = pstDbg->stInstDbg.unInfo.bits.framerate;
        }
        break;
        case DBG_SET_RATATION:
            VPSS_DBG_ReplyDbgCmd_Rotation(pstDbg, enCmd, para1, para2);
            break;
        case DBG_SET_OUTBITWIDTH:
            VPSS_DBG_ReplyDbgCmd_SetOutBitWidth(pstDbg, enCmd, para1, para2);
            break;
        case DBG_REVISE_SRC_WH:
        {
            HI_U32 *pu32WH;
            HI_BOOL *pbEnable;

            pbEnable = (HI_BOOL *)para1;
            pu32WH = (HI_U32 *)para2;

            *pbEnable = pstDbg->stInstDbg.bReviseSrcWH;
            *pu32WH   = pstDbg->stInstDbg.u32SrcWH;
            break;
        }
        case DBG_SET_LBX_COLOR:
            VPSS_DBG_ReplyDbgCmd_LBoxColor(pstDbg, enCmd, para1, para2);
            break;

        default:
            VPSS_ERROR("Invalid para1 cmd=%#x\n", enCmd);
            break;
    }

    return HI_SUCCESS;
}

HI_VOID VPSS_DBG_PrintFrameInfo(HI_DRV_VIDEO_FRAME_S *pstFrame, HI_BOOL bSrcFrame, HI_U32 u32StartIndex, HI_U32 u32EndIndex)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;

    if ((pstFrame->u32FrameIndex < u32StartIndex) || (pstFrame->u32FrameIndex > u32EndIndex))
    {
        return;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrame->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pstPriv->u32Reserve[0]);

    if (HI_TRUE == bSrcFrame)
    {
        VPSS_PROC_MSG_PRINT("Src Frame : Index %d Type %d Format %d W %d H %d Prog %d topfirst %d FieldMode %d enBufValidMode %d\n"
                            "            SrcPTS %d PTS %d OMXPTS %lld Rate %d LastFlag %#x Delta %d CodeType %d,SourceType %d,BitWidth %d,bSecure:%d\n"
                            "            L:Y %#x YVIR %#llx C %#x YH %#x CH %#x YS %d CS %d HS %d HSize: %d\n"
                            "            R:Y %#x C %#x YH %#x CH %#x YS %d CS %d HS %d HSize: %d\n",
                            pstFrame->u32FrameIndex,
                            pstFrame->eFrmType,
                            pstFrame->ePixFormat,
                            pstFrame->u32Width,
                            pstFrame->u32Height,
                            pstFrame->bProgressive,
                            pstFrame->bTopFieldFirst,
                            pstFrame->enFieldMode,
                            pstFrame->enBufValidMode,
                            pstFrame->u32SrcPts,
                            pstFrame->u32Pts,
                            pstFrame->s64OmxPts,
                            pstFrame->u32FrameRate,
                            pstPriv->u32LastFlag,
                            pstVdecPriv->s32InterPtsDelta,
                            pstVdecPriv->entype,
                            pstPriv->stVideoOriginalInfo.enSource,
                            pstFrame->enBitWidth,
                            pstFrame->bSecure,
                            pstFrame->stBufAddr[0].u32PhyAddr_Y,
                            pstFrame->stBufAddr[0].vir_addr_y,
                            pstFrame->stBufAddr[0].u32PhyAddr_C,
                            pstFrame->stBufAddr[0].u32PhyAddr_YHead,
                            pstFrame->stBufAddr[0].u32PhyAddr_CHead,
                            pstFrame->stBufAddr[0].u32Stride_Y,
                            pstFrame->stBufAddr[0].u32Stride_C,
                            pstFrame->stBufAddr[0].u32Head_Stride,
                            pstFrame->stBufAddr[0].u32Head_Size,
                            pstFrame->stBufAddr[1].u32PhyAddr_Y,
                            pstFrame->stBufAddr[1].u32PhyAddr_C,
                            pstFrame->stBufAddr[1].u32PhyAddr_YHead,
                            pstFrame->stBufAddr[1].u32PhyAddr_CHead,
                            pstFrame->stBufAddr[1].u32Stride_Y,
                            pstFrame->stBufAddr[1].u32Stride_C,
                            pstFrame->stBufAddr[1].u32Head_Stride,
                            pstFrame->stBufAddr[1].u32Head_Size
                           );
    }
    else
    {
        VPSS_PROC_MSG_PRINT("Out Frame : Index %d Type %d Format %d W %d H %d LW %d LH %d SrcPTS %d PTS %d OMXPTS %lld Rate %d Cnt %d Fidelity %d\n"
                            "            u32LastFlag %d,oriField %d,BitWidth %d,u32TunnelPhyAddr %x AspW %d AspH %d\n",
                            pstFrame->u32FrameIndex,
                            pstFrame->eFrmType,
                            pstFrame->ePixFormat,
                            pstFrame->u32Width,
                            pstFrame->u32Height,
                            pstFrame->stLbxInfo.s32Width,
                            pstFrame->stLbxInfo.s32Height,
                            pstFrame->u32SrcPts,
                            pstFrame->u32Pts,
                            pstFrame->s64OmxPts,
                            pstFrame->u32FrameRate,
                            pstPriv->u32FrmCnt,
                            pstPriv->u32Fidelity,
                            pstPriv->u32LastFlag,
                            pstPriv->eOriginField,
                            pstFrame->enBitWidth,
                            pstFrame->u32TunnelPhyAddr,
                            pstFrame->u32AspectWidth,
                            pstFrame->u32AspectHeight);
    }

    return;
}



#ifdef VPSS_SUPPORT_PROC_V2
HI_VOID VPSS_CTRL_ProcPrintWBCList(struct seq_file *p, VPSS_IN_ENTITY_S *pstInEntity)
{
    VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL2 "ALG WBC List : ");
    if (pstInEntity->stWbcInfo[0].bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "wbc ");
    }
    if (pstInEntity->stSttWbc[0].bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "stt-wbc ");
    }
    if (pstInEntity->stDieStInfo[0].bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "dei-st ");
    }
    if (pstInEntity->stNrMadInfo[0].bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "nr-mad ");
    }
    if (pstInEntity->stMcdeiInfo[0].stRgmeInfo.bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "rgme ");
    }
    if (pstInEntity->stMcdeiInfo[0].stRgmeWbcInfo.bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "rgme-wbc ");
    }
    if (pstInEntity->stMcdeiInfo[0].stBlendWbcInfo.bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "blend-wbc ");
    }
    if (pstInEntity->stMcdeiInfo[0].stBlkmvInfo.bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "blkmv ");
    }
    if (pstInEntity->stMcdeiInfo[0].stPrjhInfo.bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "prjh ");
    }
    if (pstInEntity->stMcdeiInfo[0].stPrjhInfo.bInit)
    {
        VPSS_PROC_INFO_PRINT(p, "prjv ");
    }
}
HI_VOID VPSS_CTRL_ProcPrintStreamInfo(struct seq_file *p, VPSS_IN_STREAM_INFO_S *pstStreamInfo)
{
    VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL3"Src Image Info"
                         VPSS_PROC_LEVEL4"Progress       : %s"
                         VPSS_PROC_LEVEL4"FieldMode      : %s"
                         VPSS_PROC_LEVEL4"TopFirst       : %s"
                         VPSS_PROC_LEVEL4"BufValid       : %s"
                         VPSS_PROC_LEVEL4"Security       : %s"
                         VPSS_PROC_LEVEL4"Width*Heigth   : %d * %d"
                         VPSS_PROC_LEVEL4"AspectRatio    : %d / %d"
                         VPSS_PROC_LEVEL4"FrameType      : %s(%d)"
                         VPSS_PROC_LEVEL4"PixelFormat    : %s(%d)"
                         VPSS_PROC_LEVEL4"BitWidth       : %s(%d)"
                         VPSS_PROC_LEVEL4"3DType         : %s(%d)"
                         VPSS_PROC_LEVEL4"H265iIn2Frm    : %s"
                         ,
                         VPSS_PROC_PRINT_YN(pstStreamInfo->u32StreamProg),
                         (HI_DRV_FIELD_ALL == pstStreamInfo->enFieldMode) ? "All" :
                         ((HI_DRV_FIELD_TOP == pstStreamInfo->enFieldMode) ? "Top" : "Bot"),
                         VPSS_PROC_PRINT_YN(pstStreamInfo->bTopFieldFirst),
                         (HI_DRV_FIELD_ALL == pstStreamInfo->enBufValidMode) ? "All" :
                         ((HI_DRV_FIELD_TOP == pstStreamInfo->enBufValidMode) ? "Top" : "Bot"),
                         VPSS_PROC_PRINT_YN_COL(pstStreamInfo->bSecure),
                         pstStreamInfo->u32StreamW, pstStreamInfo->u32StreamH,
                         pstStreamInfo->u32StreamAspW, pstStreamInfo->u32StreamAspH,
                         VPSS_PROC_PRINT_ENUM(pstStreamInfo->enSrcFrameType, HI_DRV_VIDEO_FRAME_TYPE_BUTT, g_pcFrameTypeString), pstStreamInfo->enSrcFrameType,
                         VPSS_PROC_PRINT_ENUM(pstStreamInfo->ePixFormat, HI_DRV_PIX_BUTT, g_pcPixelFormatString), pstStreamInfo->ePixFormat,
                         VPSS_PROC_PRINT_ENUM(pstStreamInfo->enBitWidth, HI_DRV_PIXEL_BITWIDTH_BUTT, g_pOutBitWidthString),
                         pstStreamInfo->enBitWidth,
                         VPSS_PROC_PRINT_ENUM(pstStreamInfo->eFrmType, HI_DRV_FT_BUTT, g_pc3DTypeString), pstStreamInfo->eFrmType,
                         VPSS_PROC_PRINT_YN(pstStreamInfo->bH265Interlace)
                        );
}

HI_VOID VPSS_CTRL_ProcPrintPortUserCfg(struct seq_file *p, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_DRV_VPSS_PORT_CFG_S *pstUsrPortCfg;
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        VPSS_PROC_INFO_PRINT(p,  VPSS_PROC_LEVEL3 "Port%d Config Info", u32Count);
        if (pstPort->bEnble)
        {
            pstUsrPortCfg = &(pstInstance->stUsrPortCfg[u32Count]);
            VPSS_PROC_INFO_PRINT(p,
                                 VPSS_PROC_LEVEL4"Bypass         : %s"
                                 VPSS_PROC_LEVEL4"3DSupport      : %s"
                                 VPSS_PROC_LEVEL4"Width          : %d"
                                 VPSS_PROC_LEVEL4"Height         : %d"
                                 VPSS_PROC_LEVEL4"BitWidth       : %s"
                                 VPSS_PROC_LEVEL4"PixelFormat    : %s(%d)"
                                 VPSS_PROC_LEVEL4"Rotation       : %s"
                                 VPSS_PROC_LEVEL4"FlipV          : %s"
                                 VPSS_PROC_LEVEL4"FlipH          : %s"
                                 VPSS_PROC_LEVEL4"MaxFrameRate   : %d"
                                 ,
                                 VPSS_PROC_PRINT_YN(pstUsrPortCfg->bPassThrough),
                                 VPSS_PROC_PRINT_YN(pstUsrPortCfg->b3Dsupport),
                                 pstUsrPortCfg->s32OutputWidth,
                                 pstUsrPortCfg->s32OutputHeight,
                                 VPSS_PROC_PRINT_ENUM(pstUsrPortCfg->enOutBitWidth, HI_DRV_PIXEL_BITWIDTH_BUTT, g_pOutBitWidthString),
                                 VPSS_PROC_PRINT_ENUM(pstUsrPortCfg->eFormat, HI_DRV_PIX_BUTT, g_pcPixelFormatString),
                                 pstUsrPortCfg->eFormat,
                                 VPSS_PROC_PRINT_ENUM(pstUsrPortCfg->enRotation, HI_DRV_VPSS_ROTATION_BUTT, g_pRotateString),
                                 VPSS_PROC_PRINT_YN(pstUsrPortCfg->bVertFlip),
                                 VPSS_PROC_PRINT_YN(pstUsrPortCfg->bHoriFlip),
                                 pstUsrPortCfg->u32MaxFrameRate
                                );
            VPSS_PROC_INFO_PRINT(p,
                                 VPSS_PROC_LEVEL4"UseCrop        : %s"
                                 VPSS_PROC_LEVEL4"Crop(LTRB)     : %d, %d, %d, %d"
                                 VPSS_PROC_LEVEL4"AspectMode     : %s(%d)"
                                 VPSS_PROC_LEVEL4"InRect(XYWH)   : %d, %d, %d, %d"
                                 VPSS_PROC_LEVEL4"VideoRect(XYWH): %d, %d, %d, %d"
                                 VPSS_PROC_LEVEL4"Screen(XYWH)   : %d, %d, %d, %d"
                                 VPSS_PROC_LEVEL4"CustomAR(W/H)  : %d / %d"
                                 VPSS_PROC_LEVEL4"DispPixAR(W/H) : %d / %d"
                                 ,
                                 VPSS_PROC_PRINT_YN(pstUsrPortCfg->bUseCropRect),
                                 pstUsrPortCfg->stCropRect.u32LeftOffset,
                                 pstUsrPortCfg->stCropRect.u32TopOffset,
                                 pstUsrPortCfg->stCropRect.u32RightOffset,
                                 pstUsrPortCfg->stCropRect.u32BottomOffset,
                                 VPSS_PROC_PRINT_ENUM(pstUsrPortCfg->eAspMode, HI_DRV_ASP_RAT_MODE_BUTT, g_pAspString),
                                 pstUsrPortCfg->eAspMode,
                                 pstUsrPortCfg->stInRect.s32X, pstUsrPortCfg->stInRect.s32Y,
                                 pstUsrPortCfg->stInRect.s32Width, pstUsrPortCfg->stInRect.s32Height,
                                 pstUsrPortCfg->stVideoRect.s32X, pstUsrPortCfg->stVideoRect.s32Y,
                                 pstUsrPortCfg->stVideoRect.s32Width, pstUsrPortCfg->stVideoRect.s32Height,
                                 pstUsrPortCfg->stCustmAR.u32ARw, pstUsrPortCfg->stCustmAR.u32ARh,
                                 pstUsrPortCfg->stDispPixAR.u32ARw, pstUsrPortCfg->stDispPixAR.u32ARh,
                                 pstUsrPortCfg->stScreen.s32X, pstUsrPortCfg->stScreen.s32Y,
                                 pstUsrPortCfg->stScreen.s32Width, pstUsrPortCfg->stScreen.s32Height
                                );
        }
        else
        {
            VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL4"Port is disable.");
        }
    }
}
HI_VOID VPSS_CTRL_ProcPrintTimeStamp(struct seq_file *p, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    // HI_ULONG ulSoftWareTime;
    // HI_ULONG ulSoftwareWakeupTime;
    HI_ULONG ulTotalTime;
    HI_U32   u32LogicTick;
    HI_BOOL  bTunnelEnable;

    for (u32Count = 0; u32Count < VPSS_PROC_TIMESTAMP_MAXCNT; u32Count++)
    {
        if (pstInstance->u32LogicClock > 0)
        {
            u32LogicTick = pstInstance->u32LogicTick[u32Count] * 1000 / (pstInstance->u32LogicClock / 1000);
        }
        else
        {
            u32LogicTick = 0xFFFFFFFF;
        }

        ulTotalTime = pstInstance->aulFinishTime[u32Count] - pstInstance->aulCreatTime[u32Count];

        bTunnelEnable = (0xFFFFFFFE != pstInstance->aulTunnelOutTime[u32Count]) ? HI_TRUE : HI_FALSE;

#if 0
        ulSoftWareTime = ulTotalTime - u32LogicTick;
        ulSoftwareWakeupTime = pstInstance->aulLogicEndTime[u32Count]
                               - pstInstance->aulLogicStartTime[u32Count]
                               - u32LogicTick;
        ulSoftwareWakeupTime,
        ulSoftWareTime, ulTotalTime, ((ulTotalTime > 0) ? (ulSoftWareTime * 100 / ulTotalTime) : 0)
#endif
        if (HI_TRUE == bTunnelEnable)
        {
            VPSS_PROC_INFO_PRINT(p,
                                 VPSS_PROC_LEVEL4 "TaskN+%d"
                                 VPSS_PROC_LEVEL4 "InstCreat            : %lu"
                                 VPSS_PROC_LEVEL4 "LogicStart           : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "TunnelOut            : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "ThreadWakeupTunenl   : %lu(+%lums)"

                                 VPSS_PROC_LEVEL4 "LogicFinish          : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "ThreadWakeupAll      : %lu(+%lums)"

                                 VPSS_PROC_LEVEL4 "PQAlgStart           : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "PQAlgFinish          : %lu(+%lums)"

                                 VPSS_PROC_LEVEL4 "InstFinish           : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "LogicTick(1node)     : %u(%#x) %u.%ums"
                                 VPSS_PROC_LEVEL4 "LogicClock           : %uHz"
                                 VPSS_PROC_LEVEL4 "TotalTime            : %lu"
                                 ,
                                 u32Count,
                                 pstInstance->aulCreatTime[u32Count],

                                 pstInstance->aulLogicStartTime[u32Count],
                                 pstInstance->aulLogicStartTime[u32Count] - pstInstance->aulCreatTime[u32Count],

                                 pstInstance->aulTunnelOutTime[u32Count],
                                 pstInstance->aulTunnelOutTime[u32Count] - pstInstance->aulLogicStartTime[u32Count],

                                 pstInstance->aulThreadWakeUpTunnel[u32Count],
                                 pstInstance->aulThreadWakeUpTunnel[u32Count] - pstInstance->aulTunnelOutTime[u32Count],

                                 pstInstance->aulLogicEndTime[u32Count],
                                 pstInstance->aulLogicEndTime[u32Count] - pstInstance->aulThreadWakeUpTunnel[u32Count],

                                 pstInstance->aulThreadWakeUpAll[u32Count],
                                 pstInstance->aulThreadWakeUpAll[u32Count] - pstInstance->aulLogicEndTime[u32Count],

                                 pstInstance->aulPQAlgStartTime[u32Count],
                                 pstInstance->aulPQAlgStartTime[u32Count] - pstInstance->aulThreadWakeUpAll[u32Count],
                                 pstInstance->aulPQAlgEndTime[u32Count],
                                 pstInstance->aulPQAlgEndTime[u32Count] - pstInstance->aulPQAlgStartTime[u32Count],

                                 pstInstance->aulFinishTime[u32Count],
                                 pstInstance->aulFinishTime[u32Count] - pstInstance->aulPQAlgEndTime[u32Count],

                                 pstInstance->u32LogicTick[u32Count], pstInstance->u32LogicTick[u32Count],
                                 u32LogicTick / 1000, u32LogicTick % 1000,
                                 pstInstance->u32LogicClock,
                                 ulTotalTime
                                );
        }
        else
        {
            VPSS_PROC_INFO_PRINT(p,
                                 VPSS_PROC_LEVEL4 "TaskN+%d"
                                 VPSS_PROC_LEVEL4 "InstCreat            : %lu"
                                 VPSS_PROC_LEVEL4 "LogicStart           : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "LogicFinish          : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "ThreadWakeupAll      : %lu(+%lums)"

                                 VPSS_PROC_LEVEL4 "PQAlgStart           : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "PQAlgFinish          : %lu(+%lums)"

                                 VPSS_PROC_LEVEL4 "InstFinish           : %lu(+%lums)"
                                 VPSS_PROC_LEVEL4 "LogicTick(1node)     : %u(%#x) %u.%ums"
                                 VPSS_PROC_LEVEL4 "LogicClock           : %uHz"
                                 VPSS_PROC_LEVEL4 "TotalTime            : %lu"
                                 ,
                                 u32Count,
                                 pstInstance->aulCreatTime[u32Count],

                                 pstInstance->aulLogicStartTime[u32Count],
                                 pstInstance->aulLogicStartTime[u32Count] - pstInstance->aulCreatTime[u32Count],

                                 pstInstance->aulLogicEndTime[u32Count],
                                 pstInstance->aulLogicEndTime[u32Count] - pstInstance->aulLogicStartTime[u32Count],

                                 pstInstance->aulThreadWakeUpAll[u32Count],
                                 pstInstance->aulThreadWakeUpAll[u32Count] - pstInstance->aulLogicEndTime[u32Count],

                                 pstInstance->aulPQAlgStartTime[u32Count],
                                 pstInstance->aulPQAlgStartTime[u32Count] - pstInstance->aulThreadWakeUpAll[u32Count],
                                 pstInstance->aulPQAlgEndTime[u32Count],
                                 pstInstance->aulPQAlgEndTime[u32Count] - pstInstance->aulPQAlgStartTime[u32Count],

                                 pstInstance->aulFinishTime[u32Count],
                                 pstInstance->aulFinishTime[u32Count] - pstInstance->aulPQAlgEndTime[u32Count],

                                 pstInstance->u32LogicTick[u32Count], pstInstance->u32LogicTick[u32Count],
                                 u32LogicTick / 1000, u32LogicTick % 1000,

                                 pstInstance->u32LogicClock,
                                 ulTotalTime
                                );
        }


    }
}
HI_S32 VPSS_CTRL_ProcPrint_V2(struct seq_file *p, HI_VOID *v)
{
    VPSS_INSTANCE_S *pstInstance;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;
    VPSS_IN_ENTITY_S *pstInEntity;
    VPSS_IN_IMAGELIST_STATE_S stImgListState;
    HI_DRV_VPSS_CFG_S *pstUsrInstCfg;
    DRV_PROC_ITEM_S *pProcItem;
    VPSS_PORT_PRC_S *pstPortPrc[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];
    VPSS_PORT_S *pstPort;
    VPSS_DBG_S  *pstDbgCtrl;
    HI_S32 s32SrcModuleID;
    HI_U32 u32Count;
    HI_CHAR *pcSourceName;
    S_VPSS_REGS_TYPE *pstNodeReg;
    HI_BOOL bInputBusy      = HI_FALSE;
    HI_BOOL bInputNormal    = HI_FALSE;
    HI_BOOL bInputIdle      = HI_FALSE;
    HI_BOOL bOutputBlock    = HI_FALSE;
    HI_BOOL bOutputNormal   = HI_FALSE;
    HI_BOOL bOutputIdle     = HI_FALSE;


    pProcItem = p->private;
    pstInstance = VPSS_CTRL_GetInstance((VPSS_HANDLE)((unsigned long)pProcItem->data));
    if (!pstInstance)
    {
        VPSS_FATAL("Can't get instance %x proc!\n", (VPSS_HANDLE)((unsigned long)pProcItem->data));
        return HI_FAILURE;
    }
    pstInEntity = &(pstInstance->stInEntity);
    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);
    pstUsrInstCfg = &(pstInstance->stUsrInstCfg);
    pstDbgCtrl    = &(pstInstance->stDbgCtrl);
    VPSS_INST_GetSrcListState(pstInstance, &stImgListState);
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPortPrc[u32Count] = VPSS_VMALLOC(sizeof(VPSS_PORT_PRC_S));
        if (pstPortPrc[u32Count] == HI_NULL)
        {
            VPSS_FATAL("Vmalloc Proc space Failed.\n");
            goto READFREE;
        }
        memset(pstPortPrc[u32Count], 0, sizeof(VPSS_PORT_PRC_S));
    }
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        VPSS_INST_GetPortPrc(pstInstance, pstPort->s32PortId, pstPortPrc[u32Count]);
    }
    s32SrcModuleID = (pstInstance->hDst & 0x00ff0000) >> 16;
    pcSourceName = ((s32SrcModuleID >= HI_ID_VFMW) && (s32SrcModuleID <= HI_ID_VENC)) ?
                   g_pSrcModuleString[s32SrcModuleID - HI_ID_VFMW] : (s32SrcModuleID == 0 ? g_pSrcModuleString[0] : g_pSrcModuleString[9]);
    VPSS_PROC_INFO_PRINT(p, "------------------(%s) DATE:%s --- SN:%s ------------------",
                         VPSS_CODE_MODE, VPSS_CODE_TIMESTAMP, VPSS_CODE_LASTGITNO);
    VPSS_PROC_INFO_PRINT(p,   VPSS_PROC_LEVEL1
                         "VPSS : %d"
                         " |State : %s"
                         " |Bypass : %s"
                         " |QuickOut : %s"
                         " |Source : %s"
                         " |ProcLevel : %d"
                         ,
                         pstInstance->ID,
                         g_pInstState[pstInstance->enState],
                         VPSS_PROC_PRINT_YN_COL(pstInstance->stInEntity.stTransFbInfo.bLogicTransState),
                         g_pAlgModeString[pstInstance->bAlwaysFlushSrc],
                         pcSourceName,
                         pstDbgCtrl->stInstDbg.eProcPrintLevel
                        );
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL3)
    {
        VPSS_CTRL_ProcPrintWBCList(p, pstInEntity);
    }
    VPSS_PROC_INFO_PRINT(p, (VPSS_PROC_LEVEL2 "Input Info"));
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL1)
    {
        VPSS_CTRL_ProcPrintStreamInfo(p, pstStreamInfo);
    }
    if (pstInEntity->u32ScenceChgCnt > 1)
    {
        VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL4      "ScenceChange   : "COLOR_RED"%d"COLOR_NORMAL, pstInEntity->u32ScenceChgCnt);
    }
    else
    {
        VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL4      "ScenceChange   : %d", pstInEntity->u32ScenceChgCnt);
    }
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL3)
    {
        VPSS_PROC_INFO_PRINT(p,   VPSS_PROC_LEVEL3 "Instance Config Info"
                             VPSS_PROC_LEVEL4"QuickOut       : %s"
                             VPSS_PROC_LEVEL4"Secure         : %s"
                             VPSS_PROC_LEVEL4"ProgRevise     : %s"
                             VPSS_PROC_LEVEL4"ProgInfo       : %s"
                             VPSS_PROC_LEVEL4"SrcColorSpace  : %s"
                             ,
                             VPSS_PROC_PRINT_YN(pstUsrInstCfg->bAlwaysFlushSrc),
                             VPSS_PROC_PRINT_YN(pstUsrInstCfg->bSecure),
                             VPSS_PROC_PRINT_YN(pstUsrInstCfg->bProgRevise),
                             VPSS_PROC_PRINT_ENUM(pstUsrInstCfg->enProgInfo, HI_DRV_VPSS_PRODETECT_BUTT, g_pcProDetectString),
                             VPSS_PROC_PRINT_ENUM(pstUsrInstCfg->enSrcCS, HI_DRV_CS_BUTT, g_pcProColorSpaceString)
                            );
    }
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL2)
    {
        VPSS_PROC_INFO_PRINT(p,   VPSS_PROC_LEVEL3 "Instance RWZB Info"
                             VPSS_PROC_LEVEL4"RWZB           : %s"
                             VPSS_PROC_LEVEL4"Fidelity       : %d"
                             ,
                             VPSS_PROC_PRINT_YN_COL(pstInstance->stRwzbInfo.u32Rwzb > 0),
                             pstInstance->stRwzbInfo.u32Rwzb
                            );
    }
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL3)
    {
        VPSS_CTRL_ProcPrintPortUserCfg(p, pstInstance);
    }
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL2)
    {
        VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL2 "Statistic Info");
        VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL3 "TimeStamp");
        VPSS_CTRL_ProcPrintTimeStamp(p, pstInstance);
    }
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL1)
    {
        if (pstInstance->u32LogicTimeoutCnt > 1)
        {
            VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL3 "Logic Timeout : " COLOR_RED"%d"COLOR_NORMAL, pstInstance->u32LogicTimeoutCnt);
        }
        else
        {
            VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL3 "Logic Timeout : %d", 0);
        }
    }

    if (pstInstance->u32BufSucCnt == pstInstance->u32BufCnt)
    {
        bOutputIdle = HI_TRUE;
    }
    else if (pstInstance->u32BufSucCnt * 100 > pstInstance->u32BufCnt * 99)
    {
        bOutputNormal = HI_TRUE;
    }
    else
    {
        bOutputBlock = HI_TRUE;
    }

    if (stImgListState.u32GetUsrSuccess * 100 < stImgListState.u32GetUsrTotal * 50)
    {
        bInputIdle = HI_TRUE;
    }
    else if ((stImgListState.u32GetUsrSuccess * 100 > stImgListState.u32GetUsrTotal * 98)
             && (HI_TRUE != bOutputBlock))
    {
        bInputBusy = HI_TRUE;
    }
    else
    {
        bInputNormal = HI_TRUE;
    }

    VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL3 "Input");
    VPSS_PROC_INFO_PRINT(p,
                         VPSS_PROC_LEVEL4 "InputFrame    (try/ok) : %d/%d\tHz"
                         VPSS_PROC_LEVEL4 "ProcessField  (try/ok) : %d/%d\tHz"
                         VPSS_PROC_LEVEL4 "InputFrame    (try/ok) : %d/%d\t%s"
                         VPSS_PROC_LEVEL4 "SrcList put/proc/rel   : %d/%d/%d"
                         ,
                         pstInstance->u32ImgRate, pstInstance->u32ImgSucRate,
                         pstInstance->u32CheckRate, pstInstance->u32CheckSucRate,
                         stImgListState.u32GetUsrTotal, stImgListState.u32GetUsrSuccess,
                         ((bInputNormal) ? "Normal" : ((bInputIdle) ? COLOR_GREEN"Idle"COLOR_NORMAL : COLOR_RED"Busy"COLOR_NORMAL)),
                         pstInEntity->stSrc.u32PutSrcCount,
                         pstInEntity->stSrc.u32CompleteSrcCount,
                         pstInEntity->stSrc.u32ReleaseSrcCount
                        );
    VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL3 "Output");
    VPSS_PROC_INFO_PRINT(p,
                         VPSS_PROC_LEVEL4 "GetOutbuf (try/ok)     : %d/%d\tHz"
                         VPSS_PROC_LEVEL4 "GetOutbuf (try/ok)     : %d/%d\t%s"
                         ,
                         pstInstance->u32BufRate, pstInstance->u32BufSucRate,
                         pstInstance->u32BufCnt, pstInstance->u32BufSucCnt,
                         ((bOutputNormal) ? "Normal" : ((bOutputIdle) ? COLOR_GREEN"Idle"COLOR_NORMAL : COLOR_RED"Block"COLOR_NORMAL))
                        );
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL2)
    {
        for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
        {
            pstPort = &(pstInstance->stPort[u32Count]);
            VPSS_PROC_INFO_PRINT(p,  VPSS_PROC_LEVEL3 "Port%d FBState ", u32Count);
            if (pstPort->bEnble)
            {
                VPSS_PROC_INFO_PRINT(p,
                                     VPSS_PROC_LEVEL4 "BufManager           : %s"
                                     VPSS_PROC_LEVEL4 "BufNumber            : %d(L) + %d(R)"
                                     VPSS_PROC_LEVEL4 "BufFul               : %d"
                                     VPSS_PROC_LEVEL4 "BufEmpty             : %d"
                                     VPSS_PROC_LEVEL4 "Acquire              : %d\tHz"
                                     VPSS_PROC_LEVEL4 "Acquire(try/ok)      : %d/%d"
                                     VPSS_PROC_LEVEL4 "Release(try/ok)      : %d/%d"
                                     ,
                                     g_pBufTypeString[pstPortPrc[u32Count]->stBufListCfg.eBufType],
                                     pstPortPrc[u32Count]->stBufListCfg.u32BufNumber,
                                     pstPortPrc[u32Count]->stFbPrc.u32ExtListNumb,
                                     pstPortPrc[u32Count]->stFbPrc.u32FulListNumb,
                                     pstPortPrc[u32Count]->stFbPrc.u32EmptyListNumb,
                                     pstPortPrc[u32Count]->stFbPrc.u32GetHZ,
                                     pstPortPrc[u32Count]->stFbPrc.u32GetTotal, pstPortPrc[u32Count]->stFbPrc.u32GetSuccess,
                                     pstPortPrc[u32Count]->stFbPrc.u32RelTotal, pstPortPrc[u32Count]->stFbPrc.u32RelSuccess
                                    );
            }
            else
            {
                VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL4"Port is disable.");
            }
        }
    }
    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL1)
    {
        VPSS_PROC_INFO_PRINT(p,  VPSS_PROC_LEVEL2 "Hal Info");
        VPSS_PROC_INFO_PRINT(p,  VPSS_PROC_LEVEL3 "Node Enable List");
        for (u32Count = 0; u32Count < VPSS_HAL_NODE_BUTT; u32Count++)
        {
            if (HI_TRUE == pstInstance->abNodeVaild[u32Count])
            {
                HI_CHAR *pNodeName;

                pstNodeReg = HI_NULL;
                if (HI_SUCCESS == VPSS_HAL_GetNodeAddr(VPSS_IP_0, u32Count, (HI_U8 **)&pstNodeReg, &pNodeName))
                {
                    VPSS_PROC_INFO_PRINT(p,  VPSS_PROC_LEVEL4 "%s(%d)", pNodeName, u32Count);

                    if (pstDbgCtrl->stInstDbg.eProcPrintLevel >= PROC_PRINT_LEVEL3)
                    {
                        VPSS_Hal_PrintHalInfo(p, pstNodeReg);
                    }
                }
                else
                {
                    VPSS_PROC_INFO_PRINT(p, VPSS_PROC_LEVEL5 "Get node info fail.");
                }
            }
        }
    }
    VPSS_PROC_INFO_PRINT(p, "\n"VPSS_PROC_GAP"\n");
READFREE:
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        if (pstPortPrc[u32Count] != HI_NULL)
        {
            VPSS_VFREE(pstPortPrc[u32Count]);
        }
    }
    return HI_SUCCESS;
}
#endif
HI_S32 VPSS_CTRL_ProcPrint_V1(struct seq_file *p, HI_VOID *v)
{
    VPSS_INSTANCE_S *pstInstance;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;
    VPSS_IN_ENTITY_S *pstInEntity;
    VPSS_IN_IMAGELIST_STATE_S stImgListState;
    DRV_PROC_ITEM_S *pProcItem;
    VPSS_PORT_PRC_S *pstPortPrc[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];
    HI_U8 *pProcPortFmt[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER];
    VPSS_PORT_S *pstPort;
    HI_S32 s32SrcModuleID;
    HI_U32 u32Count;
    pProcItem = p->private;

    pstInstance = VPSS_CTRL_GetInstance((VPSS_HANDLE)((unsigned long)(pProcItem->data)));

    if (!pstInstance)
    {
        VPSS_FATAL("Can't get instance %x proc!\n", (unsigned long)((VPSS_HANDLE *)pProcItem->data));
        return HI_FAILURE;
    }
    pstInEntity = &(pstInstance->stInEntity);
    pstStreamInfo = &(pstInstance->stInEntity.stStreamInfo);

    VPSS_INST_GetSrcListState(pstInstance, &stImgListState);

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPortPrc[u32Count] = VPSS_VMALLOC(sizeof(VPSS_PORT_PRC_S));
        if (pstPortPrc[u32Count] == HI_NULL)
        {
            VPSS_FATAL("Vmalloc Proc space Failed.\n");

            goto READFREE;
        }
        memset(pstPortPrc[u32Count], 0, sizeof(VPSS_PORT_PRC_S));

    }

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        VPSS_INST_GetPortPrc(pstInstance, pstPort->s32PortId, pstPortPrc[u32Count]);

        if ((pstPortPrc[u32Count]->eFormat >= HI_DRV_PIX_FMT_NV12_CMP) &&
            ((pstPortPrc[u32Count]->eFormat - HI_DRV_PIX_FMT_NV12_CMP) <= 5))
        {
            pProcPortFmt[u32Count] = g_pPixString[pstPortPrc[u32Count]->eFormat - HI_DRV_PIX_FMT_NV12_CMP + 7] ;
        }
        else if ((pstPortPrc[u32Count]->eFormat >= HI_DRV_PIX_FMT_NV12) &&
                 ((pstPortPrc[u32Count]->eFormat - HI_DRV_PIX_FMT_NV12) <= 6 ))
        {
            pProcPortFmt[u32Count] = g_pPixString[pstPortPrc[u32Count]->eFormat - HI_DRV_PIX_FMT_NV12];
        }
        else
        {
            pProcPortFmt[u32Count] = g_pPixString[13];
        }
    }

    s32SrcModuleID = (pstInstance->hDst & 0x00ff0000) >> 16;

    VPSS_PROC_INFO_PRINT(p,
                         "--------VPSS%04x---------------|"   "------------------------PortInfo------------------------|\n"
                         "ID               :0x%-8x   |"       "ID               :0x%-8x  |0x%-8x  |0x%-8x  |\n"
                         "State            :%-10s   |"        "State            :%-3s         |%-3s         |%-3s         |\n"
                         "Priority         :%-10d   |"        "PixelFormat      :%-12s|%-12s|%-12s|\n"
                         "QuickOutPut      :%-10s   |"        "Resolution       :%4d*%-4d   |%4d*%-4d   |%4d*%-4d   |\n"
                         "SourceID         :%-6s(%02x)   |"   "ColorSpace       :%-12s|%-12s|%-12s|\n"
                         "Version          :%-10s   |"        "DispPixelAR(W/H) :%2d/%-2d       |%2d/%-2d       |%2d/%-2d       |\n"
                         "                               |"   "Aspect Mode      :%-12s|%-12s|%-12s|\n"
                         "                               |"   "Support3DStream  :%-12s|%-12s|%-12s|\n"
                         "                               |"   "MaxFrameRate     :%-5d       |%-5d       |%-5d       |\n"
                         "-------- Algorithm-------------|"   "*LowDelay        :%-12s|%-12s|%-12s|\n"
                         "P/I Setting   :%-10s      |"        "HorizonFlip      :%-12s|%-12s|%-12s|\n"
                         "Deinterlace   :%-10s      |"        "VerticalFlip     :%-12s|%-12s|%-12s|\n"
                         "Sharpness     :%-10s      |"        "Rotation         :%-12s|%-12s|%-12s|\n"
#ifdef ZME_2L_TEST
                         "*ProgRevise   :%-10s      |"        "*ZME1LResolution :%4d*%-4d   |%4d*%-4d   |%4d*%-4d   |\n"
#else
                         "*ProgRevise   :%-10s      |"        "                              |            |            |\n"
#endif
                         "                               |"   "OutBitWidth      :%-12s|%-12s|%-12s|\n"
                         "--------Detect Info------------|"   "                              |            |            |\n"
                         "TopFirst(Src):%6s(%-6s)   |"        "                              |            |            |\n"
                         "InRate(Src)  :%6d(%-6d)   |"        "                              |            |            |\n"
                         "*Trans       :%8s         |"        "                              |            |            |\n"
                         "Progressive/Interlace(Src):%-1s(%-1s)|"        "                              |            |            |\n",
                         /* attribute */
                         pstInstance->ID,
                         pstInstance->ID,
                         pstPortPrc[0]->s32PortId,
                         pstPortPrc[1]->s32PortId,
                         pstPortPrc[2]->s32PortId,
                         g_pInstState[pstInstance->enState],
                         g_pAlgModeString[pstInstance->stPort[0].bEnble],
                         g_pAlgModeString[pstInstance->stPort[1].bEnble],
                         g_pAlgModeString[pstInstance->stPort[2].bEnble],

                         0,
                         pProcPortFmt[0],
                         pProcPortFmt[1],
                         pProcPortFmt[2],

                         g_pAlgModeString[pstInstance->bAlwaysFlushSrc],
                         pstPortPrc[0]->s32OutputWidth,
                         pstPortPrc[0]->s32OutputHeight,
                         pstPortPrc[1]->s32OutputWidth,
                         pstPortPrc[1]->s32OutputHeight,
                         pstPortPrc[2]->s32OutputWidth,
                         pstPortPrc[2]->s32OutputHeight,

                         (s32SrcModuleID >= HI_ID_VFMW && s32SrcModuleID <= HI_ID_VENC) ?
                         g_pSrcModuleString[s32SrcModuleID - HI_ID_VFMW] :
                         (s32SrcModuleID == 0 ? g_pSrcModuleString[0] :
                          g_pSrcModuleString[9]),
                         (pstInstance->hDst & 0x000000ff),
                         g_pCscString[pstPortPrc[0]->eDstCS],
                         g_pCscString[pstPortPrc[1]->eDstCS],
                         g_pCscString[pstPortPrc[2]->eDstCS],
                         VPSS_CODE_VERSION,
                         pstPortPrc[0]->stDispPixAR.u32ARw,
                         pstPortPrc[0]->stDispPixAR.u32ARh,
                         pstPortPrc[1]->stDispPixAR.u32ARw,
                         pstPortPrc[1]->stDispPixAR.u32ARh,
                         pstPortPrc[2]->stDispPixAR.u32ARw,
                         pstPortPrc[2]->stDispPixAR.u32ARh,

                         g_pAspString[pstPortPrc[0]->eAspMode],
                         g_pAspString[pstPortPrc[1]->eAspMode],
                         g_pAspString[pstPortPrc[2]->eAspMode],

                         g_pAlgModeString[pstPortPrc[0]->b3Dsupport],
                         g_pAlgModeString[pstPortPrc[1]->b3Dsupport],
                         g_pAlgModeString[pstPortPrc[2]->b3Dsupport],

                         pstPortPrc[0]->u32MaxFrameRate,
                         pstPortPrc[1]->u32MaxFrameRate,
                         pstPortPrc[2]->u32MaxFrameRate,
                         /*alg config*/                             g_pAlgModeString[pstPortPrc[0]->bTunnelEnable],
                         g_pAlgModeString[pstPortPrc[1]->bTunnelEnable],
                         g_pAlgModeString[pstPortPrc[2]->bTunnelEnable],

                         g_pProgDetectString[pstInEntity->enProgInfo],
                         g_pAlgModeString[pstPortPrc[0]->bHoriFlip],
                         g_pAlgModeString[pstPortPrc[1]->bHoriFlip],
                         g_pAlgModeString[pstPortPrc[2]->bHoriFlip],
                         g_pDeiString[pstInstance->stProcCtrl.eDEI],
                         g_pAlgModeString[pstPortPrc[0]->bVertFlip],
                         g_pAlgModeString[pstPortPrc[1]->bVertFlip],
                         g_pAlgModeString[pstPortPrc[2]->bVertFlip],
                         g_pAlgModeString[pstInstance->stProcCtrl.eSharpness],
                         g_pRotationString[pstPortPrc[0]->enRotation],
                         g_pRotationString[pstPortPrc[1]->enRotation],
                         g_pRotationString[pstPortPrc[2]->enRotation],
#ifdef ZME_2L_TEST
                         g_pAlgModeString[pstInEntity->bProgRevise],
                         pstInstance->stPort[0].u32ZME1LWidth,
                         pstInstance->stPort[0].u32ZME1LHeight,
                         pstInstance->stPort[1].u32ZME1LWidth,
                         pstInstance->stPort[1].u32ZME1LHeight,
                         pstInstance->stPort[2].u32ZME1LWidth,
                         pstInstance->stPort[2].u32ZME1LHeight,
#else
                         g_pAlgModeString[pstInEntity->bProgRevise],
#endif
                         (pstInstance->stPort[0].enOutBitWidth < HI_DRV_PIXEL_BITWIDTH_BUTT) ?
                         (HI_CHAR *)g_pOutBitWidthString[pstInstance->stPort[0].enOutBitWidth] : "UNKONWN",
                         (pstInstance->stPort[1].enOutBitWidth < HI_DRV_PIXEL_BITWIDTH_BUTT) ?
                         (HI_CHAR *)g_pOutBitWidthString[pstInstance->stPort[1].enOutBitWidth] : "UNKONWN",
                         (pstInstance->stPort[2].enOutBitWidth < HI_DRV_PIXEL_BITWIDTH_BUTT) ?
                         (HI_CHAR *)g_pOutBitWidthString[pstInstance->stPort[2].enOutBitWidth] : "UNKONWN",

                         (pstStreamInfo->u32RealTopFirst == 0 || pstStreamInfo->u32RealTopFirst == 1) ?
                         ((pstStreamInfo->u32RealTopFirst == 0) ? "Bottom" : "Top") : "NA",
                             (pstStreamInfo->u32StreamTopFirst == 0) ? "Bottom" : "Top",

                             pstStreamInfo->u32InRate * 1000, pstStreamInfo->u32StreamInRate,
                             (pstInstance->stInEntity.stTransFbInfo.bLogicTransState == HI_TRUE) ? "ON" : "OFF",


                             (pstStreamInfo->u32RealTopFirst == 0 || pstStreamInfo->u32RealTopFirst == 1) ?
                             "I" : "P",
                             (pstStreamInfo->u32StreamTopFirst == 0) ? "I" : "P"
                            );

#if 1
    VPSS_PROC_INFO_PRINT(p,
                         "-----SourceFrameList Info------|"  "--------------------OutFrameList Info-------------------|\n"
                         "      (source to vpss)         |"  "                     (vpss to sink)                     |\n"
                         "*Mutual Mode  :%-11s     |"        "BufManager       :%-10s  |%-10s  |%-10s  |\n"
                         "                               |"  "BufNumber        :%-2d+%-2d       |%-2d+%-2d       |%-2d+%-2d       |\n"
                         "GetSrcImgHZ(Try/OK)  :%3d/%-3d  |" "BufFul           :%-2d          |%-2d          |%-2d          |\n"
                         "GetOutBufHZ(Try/OK)  :%3d/%-3d  |" "BufEmpty         :%-2d          |%-2d          |%-2d          |\n"
                         "ProcessHZ(Try/OK)    :%3d/%-3d  |" "AcquireHZ        :%-10d  |%-10d  |%-10d  |\n"
                         "Acquire(Try/OK):               |"  "Acquire(Try/OK):              |            |            |\n"
                         " %10d/%-10d         |"             " %10d/%-10d%10d/%-10d%10d/%-10d\n"
                         "Release(Try/OK):               |"  "Release(Try/OK):              |            |            |\n"
                         " %10d/%-10d         |"             " %10d/%-10d%10d/%-10d%10d/%-10d\n",

                         g_pSrcMutualString[pstInstance->eSrcImgMode],
                         g_pBufTypeString[pstPortPrc[0]->stBufListCfg.eBufType],
                         g_pBufTypeString[pstPortPrc[1]->stBufListCfg.eBufType],
                         g_pBufTypeString[pstPortPrc[2]->stBufListCfg.eBufType],

                         pstPortPrc[0]->stBufListCfg.u32BufNumber,
                         pstPortPrc[0]->stFbPrc.u32ExtListNumb,
                         pstPortPrc[1]->stBufListCfg.u32BufNumber,
                         pstPortPrc[1]->stFbPrc.u32ExtListNumb,
                         pstPortPrc[2]->stBufListCfg.u32BufNumber,
                         pstPortPrc[2]->stFbPrc.u32ExtListNumb,


                         pstInstance->u32ImgRate,
                         pstInstance->u32ImgSucRate,
                         pstPortPrc[0]->stFbPrc.u32FulListNumb,
                         pstPortPrc[1]->stFbPrc.u32FulListNumb,
                         pstPortPrc[2]->stFbPrc.u32FulListNumb,
                         pstInstance->u32BufRate,
                         pstInstance->u32BufSucRate,
                         pstPortPrc[0]->stFbPrc.u32EmptyListNumb,
                         pstPortPrc[1]->stFbPrc.u32EmptyListNumb,
                         pstPortPrc[2]->stFbPrc.u32EmptyListNumb,
                         pstInstance->u32CheckRate,
                         pstInstance->u32CheckSucRate,
                         pstPortPrc[0]->stFbPrc.u32GetHZ,
                         pstPortPrc[1]->stFbPrc.u32GetHZ,
                         pstPortPrc[2]->stFbPrc.u32GetHZ,


                         stImgListState.u32GetUsrTotal,      stImgListState.u32GetUsrSuccess,
                         pstPortPrc[0]->stFbPrc.u32GetTotal, pstPortPrc[0]->stFbPrc.u32GetSuccess,
                         pstPortPrc[1]->stFbPrc.u32GetTotal, pstPortPrc[1]->stFbPrc.u32GetSuccess,
                         pstPortPrc[2]->stFbPrc.u32GetTotal, pstPortPrc[2]->stFbPrc.u32GetSuccess,
                         stImgListState.u32RelUsrTotal,      stImgListState.u32RelUsrSuccess,
                         pstPortPrc[0]->stFbPrc.u32RelTotal, pstPortPrc[0]->stFbPrc.u32RelSuccess,
                         pstPortPrc[1]->stFbPrc.u32RelTotal, pstPortPrc[1]->stFbPrc.u32RelSuccess,
                         pstPortPrc[2]->stFbPrc.u32RelTotal, pstPortPrc[2]->stFbPrc.u32RelSuccess
                        );


#endif




READFREE:
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
{
        if (pstPortPrc[u32Count] != HI_NULL)
        {
            VPSS_VFREE(pstPortPrc[u32Count]);
        }
    }
    return HI_SUCCESS;

}

HI_S32 VPSS_CTRL_ProcRead(struct seq_file *p, HI_VOID *v)
{
#ifndef HI_ADVCA_FUNCTION_RELEASE
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INSTANCE_S *pstInstance;
    DRV_PROC_ITEM_S *pProcItem;
    pProcItem = p->private;
    pstInstance = VPSS_CTRL_GetInstance((VPSS_HANDLE)((unsigned long)pProcItem->data));
    if (!pstInstance)
    {
        VPSS_FATAL("Can't get instance %x proc!\n", (VPSS_HANDLE)((unsigned long)pProcItem->data));
        return HI_FAILURE;
    }
    if (PROC_PRINT_LEVEL_ORI == pstInstance->stDbgCtrl.stInstDbg.eProcPrintLevel)
    {
        return VPSS_CTRL_ProcPrint_V1(p, v);
    }
    else
    {
        return VPSS_CTRL_ProcPrint_V2(p, v);
    }
#else
    return VPSS_CTRL_ProcPrint_V1(p, v);
#endif
#else
    return HI_SUCCESS;
#endif
}

HI_S32 VPSS_CTRL_ProcWrite(struct file *file,
                           const char __user *buf, size_t count, loff_t *ppos)
{
#ifndef HI_ADVCA_FUNCTION_RELEASE
    struct seq_file   *s = file->private_data;
    DRV_PROC_ITEM_S  *pProcItem = s->private;
    VPSS_HANDLE hVpss;
    HI_CHAR  chCmd[DEF_FILE_NAMELENGTH] = {0};
    HI_CHAR  chArg1[DEF_FILE_NAMELENGTH] = {0};
    HI_CHAR  chArg2[DEF_FILE_NAMELENGTH] = {0};
    HI_CHAR  chArg3[DEF_FILE_NAMELENGTH] = {0};
    HI_CHAR  chArg4[DEF_FILE_NAMELENGTH] = {0};
    VPSS_INSTANCE_S *pstInstance;
    VPSS_DBG_INST_S *pstInstDbg;
    HI_S32   s32Idx;
    VPSS_DBG_CMD_S stDbgCmd;

    VPSS_PROC_REF_TABLE_S au32VPSSRotationRefTable [] =
    {
        {DEF_DBG_ROTATION_90, HI_DRV_VPSS_ROTATION_90},
        {DEF_DBG_ROTATION_180, HI_DRV_VPSS_ROTATION_180},
        {DEF_DBG_ROTATION_270, HI_DRV_VPSS_ROTATION_270},
        {DEF_DBG_ROTATION_0, HI_DRV_VPSS_ROTATION_DISABLE}
    };
    VPSS_PROC_REF_TABLE_S au32VPSSLBoxColorRefTable [] =
    {
        {DEF_DBG_COLOR_BLACK, VPSS_COLOR_BLACK},
        {DEF_DBG_COLOR_RED, VPSS_COLOR_RED},
        {DEF_DBG_COLOR_WHITE, VPSS_COLOR_WHITE},
        {DEF_DBG_COLOR_GREEN, VPSS_COLOR_GREEN},
        {DEF_DBG_COLOR_BLUE, VPSS_COLOR_BLUE},
        {DEF_DBG_COLOR_YELLOW, VPSS_COLOR_YELLOW}
    };
    VPSS_PROC_REF_TABLE_S au32VPSSOutBitWidthRefTbl [] =
    {
        {DEF_DBG_SET_OUTWIDTH_8BIT, HI_DRV_PIXEL_BITWIDTH_8BIT},
        {DEF_DBG_SET_OUTWIDTH_10BIT, HI_DRV_PIXEL_BITWIDTH_10BIT},
        {DEF_DBG_SET_OUTWIDTH_12BIT, HI_DRV_PIXEL_BITWIDTH_12BIT}
    };
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_PROC_REF_TABLE_S au32VPSSProcLevelRefTbl [] =
    {
        {DEF_DBG_PROCLEVEL_1, PROC_PRINT_LEVEL1},
        {DEF_DBG_PROCLEVEL_2, PROC_PRINT_LEVEL2},
        {DEF_DBG_PROCLEVEL_3, PROC_PRINT_LEVEL3},
    };
#endif
    VPSS_PROC_REF_TABLE_S au32VPSSProcMenuRefTbl [] =
    {
        {DEF_DBG_CMD_YUV, DBG_W_YUV},
        {DEF_DBG_CMD_YUVIDX, DBG_W_YUV_IDX},
        {DEF_DBG_CMD_YUVFILE, DBG_W_YUV_FILE},
        {DEF_DBG_CMD_REVISEIMGWH, DBG_REVISE_SRC_WH},
        {DEF_DBG_CMD_FRAME_INFO, DBG_INFO_FRM},
        {DEF_DBG_CMD_NONE, DBG_INFO_NONE},
        {DEF_DBG_CMD_STREAM, DBG_W_STREAM},
        {DEF_DBG_CMD_UHD_LOW, DBG_SET_UHD_LOW},
        {DEF_DBG_CMD_UHD_MIDDLE, DBG_SET_UHD_MID},
        {DEF_DBG_CMD_UHD_HIGH, DBG_SET_UHD_HIGH},
        {DEF_DBG_CMD_UHD_USR, DBG_SET_UHD_USR},
        {DEF_DBG_CMD_SET_UV, DBG_SET_UV_INVERT},
        {DEF_DBG_CMD_CMP_ON, DBG_SET_CMP_ON},
        {DEF_DBG_CMD_CMP_OFF, DBG_SET_CMP_OFF},
        {DEF_DBG_CMD_SET_I2P, DBG_SET_I2P},
        {DEF_DBG_CMD_SETROTATION, DBG_SET_RATATION},
        {DEF_DBG_CMD_SETOUTBITWIDTH, DBG_SET_OUTBITWIDTH},
        {DEF_DBG_CMD_LBOXCOLOR, DBG_SET_LBX_COLOR},

    };
    VPSS_PROC_REF_TABLE_S au32VPSSProcPortRefTbl [] =
    {
        {DEF_DBG_SRC, DEF_DBG_SRC_ID},
        {DEF_DBG_PORT_0, DEF_DBG_PORT0_ID},
        {DEF_DBG_PORT_1, DEF_DBG_PORT1_ID},
        {DEF_DBG_PORT_2, DEF_DBG_PORT2_ID},
    };

    hVpss = (VPSS_HANDLE)((unsigned long)pProcItem->data);
    pstInstance = VPSS_CTRL_GetInstance(hVpss);
    if (pstInstance == HI_NULL)
    {
        VPSS_FATAL("Can't Get Debug Instance.\n");
        return count;
    }

    if (count >= DEF_FILE_NAMELENGTH)
    {
        VPSS_FATAL("Error:Echo too long.\n");
        return (-1);
    }

    if (copy_from_user(chCmd, buf, count))
    {
        VPSS_FATAL("copy from user failed\n");
        return (-1);
    }

    pstInstDbg = &(pstInstance->stDbgCtrl.stInstDbg);

    VPSS_OSAL_GetProcArg(chCmd, chArg1, 1);
    VPSS_OSAL_GetProcArg(chCmd, chArg2, 2);
    VPSS_OSAL_GetProcArg(chCmd, chArg3, 3);
    VPSS_OSAL_GetProcArg(chCmd, chArg4, 4);


    stDbgCmd.enDbgType = DBG_BUTT;
    for (s32Idx = 0; s32Idx < VPSS_GET_ARRAY_CNT(au32VPSSProcMenuRefTbl); s32Idx++)
    {
        if (0 == HI_OSAL_Strncmp(chArg1, au32VPSSProcMenuRefTbl[s32Idx].pInputString, DEF_FILE_NAMELENGTH))
        {
            stDbgCmd.enDbgType = au32VPSSProcMenuRefTbl[s32Idx].u32Context;
            break;
        }
    }

    if (DBG_BUTT == stDbgCmd.enDbgType)
    {
        if (!HI_OSAL_Strncmp(chArg1, DEF_DBG_CMD_SETBYPASS, DEF_FILE_NAMELENGTH))
        {
            pstInstDbg->unInfo.bits.vpssbypass = 0;
            if (!HI_OSAL_Strncmp(chArg2, DEF_DBG_SET_ON, DEF_FILE_NAMELENGTH))
            {
                pstInstDbg->unInfo.bits.vpssbypass = 1;
            }

            return count;
        }
        else if (!HI_OSAL_Strncmp(chArg1, DEF_DBG_CMD_RESET, DEF_FILE_NAMELENGTH))
        {
            pstInstDbg->bResetPerFrame = HI_FALSE;
            if (!HI_OSAL_Strncmp(chArg2, DEF_DBG_SET_ON, DEF_FILE_NAMELENGTH))
            {
                pstInstDbg->bResetPerFrame = HI_TRUE;
            }

            return count;
        }
        else if (!HI_OSAL_Strncmp(chArg1, DEF_DBG_CMD_SETRATE, DEF_FILE_NAMELENGTH))
        {
            pstInstDbg->unInfo.bits.frameEn = 0;
            if (!HI_OSAL_Strncmp(chArg2, DEF_DBG_SET_ON, DEF_FILE_NAMELENGTH))
            {
                pstInstDbg->unInfo.bits.frameEn = 1;
            }

            pstInstDbg->unInfo.bits.framerate = (HI_U32)(simple_strtol(chArg3, NULL, 10));
            if (strlen(chArg3) == 0)
            {
                pstInstDbg->unInfo.bits.framerate = pstInstance->stInEntity.stStreamInfo.u32InRate;
            }

            return count;
        }
#ifdef VPSS_SUPPORT_PROC_V2
        else if (!HI_OSAL_Strncmp(chArg1, DEF_DBG_CMD_SETPROCLEVEL, DEF_FILE_NAMELENGTH))
        {
            pstInstDbg->eProcPrintLevel = PROC_PRINT_LEVEL_ORI;
            for (s32Idx = 0; s32Idx < VPSS_GET_ARRAY_CNT(au32VPSSProcLevelRefTbl); s32Idx++)
            {
                if (0 == HI_OSAL_Strncmp(chArg2, au32VPSSProcLevelRefTbl[s32Idx].pInputString, DEF_FILE_NAMELENGTH))
                {
                    pstInstDbg->eProcPrintLevel = (VPSS_PROC_PRINT_LEVEL_E)au32VPSSProcLevelRefTbl[s32Idx].u32Context;
                    break;
                }
            }
            return count;
        }
#endif
        else
        {
            VPSS_ERROR("Cmd Can't Support\n");
            goto PROC_EXIT;
        }
    }

    stDbgCmd.hDbgPart = DEF_DBG_SRC_PORT_BUT;
    for (s32Idx = 0; s32Idx < VPSS_GET_ARRAY_CNT(au32VPSSProcPortRefTbl); s32Idx++)
    {
        if (0 == HI_OSAL_Strncmp(chArg2, au32VPSSProcPortRefTbl[s32Idx].pInputString, DEF_FILE_NAMELENGTH))
        {
            stDbgCmd.hDbgPart = au32VPSSProcPortRefTbl[s32Idx].u32Context;
            break;
        }
    }
    if (DEF_DBG_SRC_PORT_BUT == stDbgCmd.hDbgPart)
    {
        VPSS_ERROR("Invalid para2 %s\n", chArg2);
        goto PROC_EXIT;
    }

    if (stDbgCmd.enDbgType == DBG_SET_RATATION)
    {
        stDbgCmd.hDbgValue = (VPSS_HANDLE)HI_DRV_VPSS_ROTATION_BUTT;
        for (s32Idx = 0; s32Idx < VPSS_GET_ARRAY_CNT(au32VPSSRotationRefTable); s32Idx++)
        {
            if (0 == HI_OSAL_Strncmp(chArg3, au32VPSSRotationRefTable[s32Idx].pInputString, DEF_FILE_NAMELENGTH))
            {
                stDbgCmd.hDbgValue = (VPSS_HANDLE)au32VPSSRotationRefTable[s32Idx].u32Context;
                break;
            }
        }
    }
    else if (stDbgCmd.enDbgType == DBG_SET_LBX_COLOR)
    {
        stDbgCmd.hDbgValue = (VPSS_HANDLE)VPSS_COLOR_BUTT;
        for (s32Idx = 0; s32Idx < VPSS_GET_ARRAY_CNT(au32VPSSLBoxColorRefTable); s32Idx++)
        {
            if (0 == HI_OSAL_Strncmp(chArg3, au32VPSSLBoxColorRefTable[s32Idx].pInputString, DEF_FILE_NAMELENGTH))
            {
                stDbgCmd.hDbgValue = (VPSS_HANDLE)au32VPSSLBoxColorRefTable[s32Idx].u32Context;
                break;
            }
        }
    }
    else if (stDbgCmd.enDbgType == DBG_SET_OUTBITWIDTH)
    {
        stDbgCmd.hDbgValue = (VPSS_HANDLE)HI_DRV_PIXEL_BITWIDTH_BUTT;
        for (s32Idx = 0; s32Idx < VPSS_GET_ARRAY_CNT(au32VPSSOutBitWidthRefTbl); s32Idx++)
        {
            if (0 == HI_OSAL_Strncmp(chArg3, au32VPSSOutBitWidthRefTbl[s32Idx].pInputString, DEF_FILE_NAMELENGTH))
            {
                stDbgCmd.hDbgValue = (VPSS_HANDLE)au32VPSSOutBitWidthRefTbl[s32Idx].u32Context;
                break;
            }
        }
    }
    else if ((stDbgCmd.enDbgType == DBG_W_YUV_IDX) || (stDbgCmd.enDbgType == DBG_W_YUV_FILE))
    {
        stDbgCmd.hDbgValue = simple_strtoul(chArg3, NULL, 10);
        stDbgCmd.hDbgValue = stDbgCmd.hDbgValue << 16;
        stDbgCmd.hDbgValue = stDbgCmd.hDbgValue + (simple_strtoul(chArg4, NULL, 10) & 0xFFFF);
    }

    else if (stDbgCmd.enDbgType == DBG_REVISE_SRC_WH)
    {
        stDbgCmd.hDbgValue = simple_strtoul(chArg3, NULL, 10);
        stDbgCmd.hDbgValue = stDbgCmd.hDbgValue << 16;
        stDbgCmd.hDbgValue = stDbgCmd.hDbgValue + (simple_strtoul(chArg4, NULL, 10) & 0xFFFF);
    }
    else if (stDbgCmd.enDbgType == DBG_INFO_FRM)
    {
        if (stDbgCmd.hDbgPart == DEF_DBG_SRC_ID)
        {
            stDbgCmd.hDbgValue = simple_strtoul(chArg3, NULL, 10);
            stDbgCmd.hDbgValue = stDbgCmd.hDbgValue << 16;
            stDbgCmd.hDbgValue = stDbgCmd.hDbgValue + (simple_strtoul(chArg4, NULL, 10) & 0xFFFF);
        }
    }
    else
    {
        stDbgCmd.hDbgValue = (VPSS_HANDLE)HI_FALSE;
        if (!HI_OSAL_Strncmp(chArg3, DEF_DBG_SET_ON, DEF_FILE_NAMELENGTH))
        {
            stDbgCmd.hDbgValue = (VPSS_HANDLE)HI_TRUE;
        }
    }


#if DEF_VPSS_DEBUG
    VPSS_DBG_SendDbgCmd(&(pstInstance->stDbgCtrl), &stDbgCmd);
#endif
    return count;

PROC_EXIT:
    HI_DRV_PROC_EchoHelper("-------------------VPSS debug options--------------------\n"
                           "you can perform VPSS debug with such command\n"
                           "echo [arg1] [arg2] [arg3] > /proc/msp/vpssXX\n"
                           "debug action                    arg1        arg2                    arg3\n"
                           "-------------                   ----------  ---------------------   -----------\n"
                           " save one yuv                   saveyuv     src/port0/port1/port2\n");
    HI_DRV_PROC_EchoHelper(" print frameinfo                printinfo   src/port0/port1/port2\n"
                           " turn off info                  none        src/port0/port1/port2\n");

    HI_DRV_PROC_EchoHelper(" set progress/interlace on/off  i2p         src                     on/off\n"
                           " set vpssbypass                 setbypass   on/off\n"
                           " set uvinvert                   uvinvert    port0/port1/port2       on/off \n"
                           " set letterbox color            setcolor    port0/port1/port2       red/yellow/green...\n"
                           " set cmpon                      cmpon       port0/port1/port2\n");

    HI_DRV_PROC_EchoHelper(" set cmpoff                     cmpoff      port0/port1/port2\n"
                           " set rate                       setrate     on/off                  framerate\n"
                           " set out bitwidth               setbitwidth port0/port1/port2       8bit/10bit/12bit/disable\n"
                           " set rotation                   setrota     port0/port1/port2       0/90/180/270/disable\n"
                           " set src image w h              setsrcwh    port0/port1/port2/src   width  heigth\n"
                           " reset logic afer frame process reset       on/off\n"
#ifdef VPSS_SUPPORT_PROC_V2
                           " set proc level                 proc        0/1/2/3\n"
#endif
                           " save yuv in file with index    saveyuvidx  src/port0/port1/port2   index  count\n"
                           " save yuv in one file           saveyuvfile src/port0/port1/port2   index  count\n"

                          );
#endif //#ifndef HI_ADVCA_FUNCTION_RELEASE



    return count;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

