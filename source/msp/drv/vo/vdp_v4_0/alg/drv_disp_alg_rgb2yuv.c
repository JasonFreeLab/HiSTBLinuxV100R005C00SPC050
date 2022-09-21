
#include "drv_disp_alg_rgb2yuv.h"


//RGB_YUVÉ«²Ê¿Õ¼ä×ª»»
HI_VOID DISP_ALG_CscRgb2Yuv(ALG_COLOR_S *pstRgbColor, ALG_COLOR_S *pYuvColor)
{
    HI_S32 s32Red = 0, s32Y = 0;
    HI_S32 s32Green = 0, s32U = 0;
    HI_S32 s32Blue = 0, s32V = 0;

    s32Red   = (HI_S32)pstRgbColor->u8Red;
    s32Green = (HI_S32)pstRgbColor->u8Green;
    s32Blue  = (HI_S32)pstRgbColor->u8Blue;

    //change rgb to yuv.
    s32Y = (257 * s32Red  + 504 * s32Green  + 98 * s32Blue ) / 1000 + 16;
    s32U = (-148 * s32Red  - 291 * s32Green  + 439 * s32Blue ) / 1000 + 128;
    s32V = (439 * s32Red  - 368 * s32Green  - 71 * s32Blue ) / 1000 + 128;

    if (s32Y < 16)
    {
        s32Y = 16;
    }

    if (s32Y > 235)
    {
        s32Y = 235;
    }

    if (s32U < 16)
    {
        s32U = 16;
    }

    if (s32U > 240)
    {
        s32U = 240;
    }

    if (s32V < 16)
    {
        s32V = 16;
    }

    if (s32V > 240)
    {
        s32V = 240;
    }

    pYuvColor->u8Y  = (HI_U8)s32Y;
    pYuvColor->u8Cb = (HI_U8)s32U;
    pYuvColor->u8Cr = (HI_U8)s32V;

    return;
}


