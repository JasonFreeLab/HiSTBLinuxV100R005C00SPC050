/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name     : df_fill_rect.c
Version         :
Author          :
Created        : 2017/07/16
Description   : 填充矩形框, 可以和播视频一起测试
                      ./sample_tsplay ../res/test.ts 1080P_50
Function List :
History         :
Date                              Author                  Modification
2017/07/16                   sdk
******************************************************************************/


/*********************************add include here******************************/
#include <directfb.h>
#include <directfb_strings.h>
#include <directfb_util.h>
#include <direct/util.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "directfb_version.h"

#include "hi_adp_gfx.h"
/***************************** Macro Definition ******************************/
#define DFBCHECK(x...) \
     {                                                                \
          err = x;                                                    \
          if (err != DFB_OK) {                                        \
               SAMPLE_TRACE("%s <%d>:\n\t", __FILE__, __LINE__ );     \
               DirectFBErrorFatal( #x, err );                         \
          }                                                           \
     }
/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/
static IDirectFB *dfb = NULL;
static IDirectFBSurface *primary = NULL;

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/
int main( int argc, char *argv[] )
{
	DFBResult err;
	DFBSurfaceDescription dsc;
    static DFBSurfacePixelFormat PixelFormat = DSPF_UNKNOWN;
    HI_S32 SurfaceWidth  = -1;
    HI_S32 SurfaceHeight = -1;
    HI_S32 Pox_X  = -1;
    HI_S32 Pox_Y  = -1;
	HI_S32	alpha = -1;
	HI_S32  red	  = -1;
	HI_S32	green = -1;
	HI_S32	blue  = -1;
    HI_CHAR key;

    if (7 != argc)
    {
       SAMPLE_TRACE("\n====================================================\n");
       SAMPLE_TRACE("please run as follows\n");
       SAMPLE_TRACE("./df_fill_rect alpha red green blue pox_x pox_y\n");
       SAMPLE_TRACE("./df_fill_rect 255 0   0   0  0  0\n");
       SAMPLE_TRACE("./df_fill_rect 255 255 0   0  100 100\n");
       SAMPLE_TRACE("./df_fill_rect 128 0   255 0  100 100\n");
       SAMPLE_TRACE("./df_fill_rect 255 1   1   1  100 100\n");
       SAMPLE_TRACE("====================================================\n");
       return 0;
    }
    alpha = atoi(argv[1]);
	red	  = atoi(argv[2]);
	green = atoi(argv[3]);
	blue  = atoi(argv[4]);
    Pox_X = atoi(argv[5]);
    Pox_Y = atoi(argv[6]);

    DFBCHECK(DirectFBInit(&argc, &argv));

	DFBCHECK(DirectFBSetOption("bg-none", NULL));
	DFBCHECK(DirectFBSetOption("no-init-layer", NULL));

	DFBCHECK(DirectFBCreate(&dfb));

	DFBCHECK(dfb->SetCooperativeLevel(dfb, DFSCL_FULLSCREEN));

	dsc.flags = DSDESC_CAPS;
	dsc.caps  = DSCAPS_PRIMARY;
	DFBCHECK(dfb->CreateSurface(dfb, &dsc, &primary));

	DFBCHECK(primary->GetPixelFormat(primary, &PixelFormat));
	DFBCHECK(primary->GetSize(primary, &SurfaceWidth, &SurfaceHeight));
	DFBCHECK(primary->Clear(primary, 0, 0, 0, 0x80));

    SAMPLE_TRACE("\n============================================================\n");
    SAMPLE_TRACE("get surface size [%d %d], pix [0x%x]\n", SurfaceWidth, SurfaceHeight, PixelFormat);
	SAMPLE_TRACE("set layer color argb with [0x%x 0x%x 0x%x 0x%x]\n",(short)alpha,(short)red,(short)green,(short)blue);
    SAMPLE_TRACE("============================================================\n");

	DFBCHECK(primary->SetColor(primary,(short)red,(short)green,(short)blue,(short)alpha));
	DFBCHECK(primary->FillRectangle(primary,Pox_X,Pox_Y,(SurfaceWidth - 200), (SurfaceHeight - 200)));

	SAMPLE_TRACE("press q to exit\n");
    key = getchar();
    while ('q' != key && 'Q' != key)
    {
        key = getchar();
    }
    
    while(1)
    {
      sleep(1);
    }

    DFBCHECK(primary->Clear(primary, 0, 0, 0, 0));

    DFBCHECK(primary->Release(primary));

    DFBCHECK(dfb->Release(dfb));

    return 0;
}
