/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hisi_dfb_opentv5_layer.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : control hard decode dispose
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                sdk                         Created file
******************************************************************************/

/****************************  add include here     *******************************/
#include <config.h>
#include <asm/types.h>
#include <stdio.h>
#include <sys/mman.h>
#include <directfb.h>
#include <direct/debug.h>
#include <direct/messages.h>
#include <sys/ioctl.h>
#include <fbdev/fbdev.h>
#include <core/layers.h>

#include "hi_mpi_disp.h"
#include "hi_unf_vo.h"
#include "hi_mpi_win.h"
#include "hi_mpi_hdmi.h"

/***************************** Macro Definition     *******************************/
#define VIDEO_LAY_ID (1UL)

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration *******************************/



/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/

static DFBResult hisi_init_layer (CoreLayer                  *layer,
                                   void                       *driver_data,
                                   void                       *layer_data,
                                   DFBDisplayLayerDescription *description,
                                   DFBDisplayLayerConfig      *config,
                                   DFBColorAdjustment         *adjustment )
{
    if (HI_SUCCESS != HI_MPI_WIN_Init())
    {
		D_ERROR("%s->%d, fail!\n",__func__,__LINE__);
		return DFB_FAILURE;
	}

    description->caps = DLCAPS_SCREEN_LOCATION | DLCAPS_SURFACE;
    description->type = DLTF_VIDEO | DLTF_STILL_PICTURE;

    /* set name */
    snprintf(description->name, DFB_DISPLAY_LAYER_DESC_NAME_LENGTH, "HISI Video" );

    /* fill out the default configuration */
    config->flags      = DLCONF_WIDTH | DLCONF_HEIGHT | DLCONF_BUFFERMODE;
    config->buffermode = DLBM_FRONTONLY;
    config->width      = 1920;
    config->height     = 1080;

    return DFB_OK;
}


static DFBResult hisi_test_region(CoreLayer                  *layer,
                                     void                       *driver_data,
                                     void                       *layer_data,
                                     CoreLayerRegionConfig      *config,
                                     CoreLayerRegionConfigFlags *failed )
{
    if (failed)
    {
       *failed = CLRCF_NONE;
    }

    return DFB_OK;
}


static DFBResult hisi_set_region(CoreLayer                  *layer,
                                    void                       *driver_data,
                                    void                       *layer_data,
                                    void                       *region_data,
                                    CoreLayerRegionConfig      *config,
                                    CoreLayerRegionConfigFlags  updated,
                                    CoreSurface                *surface,
                                    CorePalette                *palette,
                                    CoreSurfaceBufferLock      *lock )
{
	HI_DRV_WIN_ATTR_S attr;
	HI_HANDLE win;

	if (!layer || !layer->shared)
    {
		D_ERROR("%s->%d, !layer %d, !layer->shared:%d,Cannot get window handle!\n",__func__,__LINE__,!layer, !layer->shared);
		return DFB_FAILURE;
	}

	win = (HI_HANDLE)((HI_ID_VO << 16) | (HI_UNF_DISPLAY1 << 8)  |(((HI_U32)layer->shared->layer_id - VIDEO_LAY_ID)&0xff));

	if (HI_SUCCESS != HI_MPI_WIN_GetAttr(win,  &attr))
    {
		D_ERROR("hisi_set_region Fail to get window attr!\n");
		return DFB_FAILURE;
	}

	attr.stOutRect.s32X = config->dest.x;
	attr.stOutRect.s32Y = config->dest.y;
	attr.stOutRect.s32Width = config->dest.w;
	attr.stOutRect.s32Height = config->dest.h;

	if (HI_SUCCESS != HI_MPI_WIN_SetAttr(win, &attr))
    {
		D_ERROR("hisi_set_region Fail to set window attr!\n");
		return DFB_FAILURE;
	}

	return DFB_OK;
}


static DFBResult hisi_get_level(CoreLayer *layer, void *driver_data, void *layer_data, int *level)
{
	return DFB_UNSUPPORTED;
}


static DFBResult hisi_set_level(CoreLayer *layer, void *driver_data, void *layer_data, int level)
{
	return DFB_UNSUPPORTED;
}


static DFBResult hisi_set_color_adjustment(CoreLayer *layer, void *driver_data, void *layer_data, DFBColorAdjustment *adjustment)
{
	return DFB_UNSUPPORTED;
}


static DisplayLayerFuncs hisi_layer_funcs = {
	.InitLayer  = hisi_init_layer,
	.TestRegion = hisi_test_region,
	.SetRegion  = hisi_set_region,
    .GetLevel   = hisi_get_level,
    .SetLevel   = hisi_set_level,
    .SetColorAdjustment = hisi_set_color_adjustment,
};
