/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hisi_dfb_opentv5_fbdev.c
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
#include "hi_unf_disp.h"

/***************************** Macro Definition     *******************************/

/***************************** Structure Definition *******************************/
typedef struct
{
	DFBScreenEncoderDescription desc;
	DFBScreenEncoderConfig old_config;
}hisi_screen_data;

typedef struct {
	HI_UNF_ENC_FMT_E fmt;
	DFBScreenEncoderTVStandards	stand;
	DFBScreenEncoderFrequency freq;
	DFBScreenOutputResolution res;
	DFBScreenEncoderScanMode ip;
}dfb_res_map;


/********************** Global Variable declaration *******************************/
dfb_res_map map[] = {
	{HI_UNF_ENC_FMT_1080P_60, DSETV_NTSC, DSEF_60HZ, DSOR_1920_1080, DSESM_PROGRESSIVE}, /* 1080P 60Hz */
	{HI_UNF_ENC_FMT_1080P_50, DSETV_PAL,  DSEF_50HZ, DSOR_1920_1080, DSESM_PROGRESSIVE}, /* 1080P 50Hz */
	{HI_UNF_ENC_FMT_1080i_60, DSETV_NTSC, DSEF_60HZ, DSOR_1920_1080, DSESM_INTERLACED},  /* 1080I 60Hz */
	{HI_UNF_ENC_FMT_1080i_50, DSETV_PAL,  DSEF_50HZ, DSOR_1920_1080, DSESM_INTERLACED},	 /* 1080I 50Hz */

	{HI_UNF_ENC_FMT_720P_60,  DSETV_NTSC, DSEF_60HZ, DSOR_1280_720, DSESM_PROGRESSIVE},	 /* 720P 60Hz */
	{HI_UNF_ENC_FMT_720P_50,  DSETV_PAL,  DSEF_50HZ, DSOR_1280_720, DSESM_PROGRESSIVE},	 /* 720P 50Hz */

	{HI_UNF_ENC_FMT_576P_50,  DSETV_PAL,  DSEF_50HZ, DSOR_720_576, DSESM_PROGRESSIVE},	 /* 576P 50Hz */
	{HI_UNF_ENC_FMT_480P_60,  DSETV_NTSC, DSEF_60HZ, DSOR_720_480, DSESM_PROGRESSIVE},	 /* 480P 60Hz */
};

/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/
static HI_UNF_ENC_FMT_E find_fmt(DFBScreenEncoderTVStandards stand, DFBScreenEncoderScanMode ip, DFBScreenEncoderFrequency freq, DFBScreenOutputResolution res)
{
	int i, cnt = sizeof(map) / sizeof(map[0]);

	for (i = 0; i < cnt; i++)
	{
		if (stand == map[i].stand && ip == map[i].ip && freq == map[i].freq && res == map[i].res)
		{
			return map[i].fmt;
		}
	}

	return HI_UNF_ENC_FMT_BUTT;
}

static int hisi_screen_data_size(void)
{
	return sizeof(hisi_screen_data);
}


static HI_S32 O5SDK_Disp_Init(HI_UNF_ENC_FMT_E enFormat)
{
	HI_S32 Ret = HI_SUCCESS;
    HI_UNF_DISP_BG_COLOR_S BgColor;
    HI_UNF_DISP_INTF_S DispIntf;
    HI_UNF_DISP_OFFSET_S  offset;
    HI_UNF_ENC_FMT_E SdFmt = HI_UNF_ENC_FMT_PAL;

	Ret = HI_UNF_DISP_Init();
	if (Ret != HI_SUCCESS)
	{
		D_ERROR("call HI_UNF_DISP_Init failed.\n");
		goto err0;
	}

    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_HDMI;
    DispIntf.unIntf.enHdmi = HI_UNF_HDMI_ID_0;
	Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &DispIntf, 1);
	if (Ret)
	{
		D_ERROR("call HI_UNF_DISP_AddIntf failed.\n");
		goto err0_1;
	}

#if defined(HI_DAC_YPBPR_Y) && defined(HI_DAC_YPBPR_PB) && defined(HI_DAC_YPBPR_PR)
    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_YPBPR;
    DispIntf.unIntf.stYPbPr.u8DacY  = HI_DAC_YPBPR_Y;
    DispIntf.unIntf.stYPbPr.u8DacPb = HI_DAC_YPBPR_PB;
    DispIntf.unIntf.stYPbPr.u8DacPr = HI_DAC_YPBPR_PR;
    Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &DispIntf, 1);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_AttachIntf ypbpr failed 0x%x\n", Ret);
        goto err0_1;
    }
#endif

    DispIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_CVBS;
    DispIntf.unIntf.stCVBS.u8Dac = HI_DAC_CVBS;
    Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY0, &DispIntf, 1);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_AttachIntf cvbs failed 0x%x\n", Ret);
        goto err0_1;
    }

    Ret = HI_UNF_DISP_Attach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_Attach failed 0x%x\n", Ret);
        goto err0_1;
    }

    Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, enFormat);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_SetFormat DISPLAY1 0x%x failed 0x%x\n", enFormat, Ret);
        goto err2;
    }

    switch (enFormat)
    {
        case HI_UNF_ENC_FMT_4096X2160_60 :
        case HI_UNF_ENC_FMT_4096X2160_30 :
        case HI_UNF_ENC_FMT_4096X2160_24 :
        case HI_UNF_ENC_FMT_3840X2160_60 :
        case HI_UNF_ENC_FMT_3840X2160_30 :
        case HI_UNF_ENC_FMT_3840X2160_24 :
        case HI_UNF_ENC_FMT_1080P_60 :
        case HI_UNF_ENC_FMT_1080P_30 :
        case HI_UNF_ENC_FMT_1080i_60 :
        case HI_UNF_ENC_FMT_720P_60 :
        case HI_UNF_ENC_FMT_480P_60 :
        case HI_UNF_ENC_FMT_NTSC :
            SdFmt = HI_UNF_ENC_FMT_NTSC;
            break;

        case HI_UNF_ENC_FMT_4096X2160_50 :
        case HI_UNF_ENC_FMT_4096X2160_25 :
        case HI_UNF_ENC_FMT_3840X2160_50 :
        case HI_UNF_ENC_FMT_3840X2160_25 :
        case HI_UNF_ENC_FMT_1080P_50 :
        case HI_UNF_ENC_FMT_1080P_25 :
        case HI_UNF_ENC_FMT_1080i_50 :
        case HI_UNF_ENC_FMT_720P_50 :
        case HI_UNF_ENC_FMT_576P_50 :
        case HI_UNF_ENC_FMT_PAL :
            SdFmt = HI_UNF_ENC_FMT_PAL;
            break;

        default:
            break;
    }

    Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, SdFmt);
    if (HI_SUCCESS != Ret)
    {
        D_ERROR("HI_UNF_DISP_SetFormat DISPLAY0 0x%x failed 0x%x\n", SdFmt, Ret);
        goto err2;
    }

    Ret = HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, 1280, 720);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_SetVirtualScreen failed 0x%x\n", Ret);
        goto err2;
    }

    offset.u32Left      = 0;
    offset.u32Top       = 0;
    offset.u32Right     = 0;
    offset.u32Bottom    = 0;

    /*set display1 screen offset*/
    Ret = HI_UNF_DISP_SetScreenOffset(HI_UNF_DISPLAY1, &offset);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_SetScreenOffset DISPLAY1 failed 0x%x\n", Ret);
        goto err2;
    }

    /*set display0 screen offset*/
    Ret = HI_UNF_DISP_SetScreenOffset(HI_UNF_DISPLAY0, &offset);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_SetScreenOffset DISPLAY0 failed 0x%x\n", Ret);
        goto err2;
    }

    BgColor.u8Red   = 0;
    BgColor.u8Green = 0;
    BgColor.u8Blue  = 0;

    Ret = HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &BgColor);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_SetBgColor failed 0x%x\n", Ret);
        goto err2;
    }

    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_Open DISPLAY1 failed 0x%x\n", Ret);
        goto err2;
    }

    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY0);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("HI_UNF_DISP_Open DISPLAY0 failed 0x%x\n", Ret);
        HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
        goto err2;
    }

    return HI_SUCCESS;

err2:
    HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
err0_1:
	HI_UNF_DISP_DeInit();

err0:
	return Ret;

}

static HI_S32 O5SDK_Disp_DeInit(HI_VOID)
{
    HI_S32 Ret = HI_SUCCESS;

    Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("call HI_UNF_DISP_Close failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("call HI_UNF_DISP_Close failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("call HI_UNF_DISP_Detach failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_DISP_DeInit();
    if (Ret != HI_SUCCESS)
    {
        D_ERROR("call HI_UNF_DISP_DeInit failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    return HI_SUCCESS;
}


static DFBResult hisi_init_encoder(CoreScreen *screen, void *driver_data, void *screen_data, int encoder, DFBScreenEncoderDescription *description, DFBScreenEncoderConfig *config)
{
	u32 val;
	hisi_screen_data *old = (hisi_screen_data *)screen_data;
	HI_UNF_ENC_FMT_E enFormat = HI_UNF_ENC_FMT_1080i_50;

	if (HI_SUCCESS != O5SDK_Disp_Init(enFormat))
    {
		D_ERROR("hisi_init_encoder fail to call disp init!\n");
		return DFB_FAILURE;
	}

	/* Set the encoder capabilities & type. */
	description->caps =   DSECAPS_TV_STANDARDS
	                    | DSECAPS_RESOLUTION
	                    | DSECAPS_FREQUENCY
	                    | DSECAPS_SCANMODE
		                | DSECAPS_BRIGHTNESS
		                | DSECAPS_CONTRAST
		                | DSECAPS_HUE|DSECAPS_SATURATION;

	description->type = DSET_TV;

	/* Set supported TV standards. */
	description->tv_standards = DSETV_PAL | DSETV_NTSC ;

	description->all_resolutions =    DSOR_720_576	    /* 576P/I */
                            		| DSOR_720_480		/* 480P/I */
                            		| DSOR_1280_720		/* 720P/I */
                            		| DSOR_1920_1080;	/* 1080P/I */

	/* Set default configuration. 1080I 50Hz PAL. */
	config->flags =  DSECONF_TV_STANDARD
	               | DSECONF_RESOLUTION
	               | DSECONF_FREQUENCY
	               | DSECONF_SCANMODE
		           | DSECONF_ADJUSTMENT;

	config->tv_standard	= DSETV_PAL;
	config->resolution	= DSOR_1920_1080;
	config->frequency	= DSEF_50HZ;
	config->scanmode	= DSESM_INTERLACED;
	config->adjustment.flags= DCAF_ALL;

	(HI_VOID)HI_UNF_DISP_GetBrightness(HI_UNF_DISPLAY0, &val);
	config->adjustment.brightness = (u16)val;

	(HI_VOID)HI_UNF_DISP_GetContrast(HI_UNF_DISPLAY0, &val);
	config->adjustment.contrast = (u16)val;

	(HI_VOID)HI_UNF_DISP_GetHuePlus(HI_UNF_DISPLAY0, &val);
	config->adjustment.hue = (u16)val;

	(HI_VOID)HI_UNF_DISP_GetSaturation(HI_UNF_DISPLAY0, &val);
	config->adjustment.saturation = (u16)val;

    /* keep default config */
	memcpy(&old->old_config, config, sizeof(DFBScreenEncoderConfig));
	memcpy(&old->desc, description, sizeof(DFBScreenEncoderDescription));

	return DFB_OK;
}


static DFBResult hisi_test_encoder_config(CoreScreen *screen, void *driver_data, void *screen_data, int encoder, const DFBScreenEncoderConfig *config, DFBScreenEncoderConfigFlags *failed)
{
	hisi_screen_data *old = (hisi_screen_data *)screen_data;

	if (!config || !failed)
    {
		return DFB_INVARG;
	}

	/* flag check. */
	if (config->flags & ~old->old_config.flags)
    {
		*failed = (config->flags & ~old->old_config.flags);
		return DFB_UNSUPPORTED;
	}

	/* tv standard check. */
	if (config->flags & DSECONF_TV_STANDARD)
	{
		if ((old->desc.tv_standards & config->tv_standard) == 0)
        {
			*failed |= DSECONF_TV_STANDARD;
			return  DFB_INVARG;
		}
	}

	/* resolution check. */
	if (config->flags & DSECONF_RESOLUTION)
    {
		if ((old->desc.all_resolutions & config->resolution) == 0)
        {
			*failed |= DSECONF_RESOLUTION;
			return  DFB_INVARG;
		}
	}

	/* freq check. FIXME! Only support 50Hz and 60Hz. */
	if (config->flags & DSECONF_FREQUENCY)
    {
		if (((DSEF_60HZ | DSEF_50HZ) & config->frequency) == 0)
        {
			*failed |= DSECONF_FREQUENCY;
			return DFB_INVARG;
		}
	}

	if (config->flags & (DSECONF_TV_STANDARD | DSECONF_RESOLUTION | DSECONF_FREQUENCY | DSECONF_SCANMODE))
    {
		/* resolution and freq check. */
		if (HI_UNF_ENC_FMT_BUTT == find_fmt(config->tv_standard, config->scanmode, config->frequency, config->resolution))
        {
			*failed |= DSECONF_TV_STANDARD | DSECONF_FREQUENCY | DSECONF_RESOLUTION | DSECONF_SCANMODE;
			return DFB_INVARG;
		}
	}
	return DFB_OK;
}


static DFBResult hisi_config_encoder(CoreScreen *screen, void *driver_data, void *screen_data, int encoder, const DFBScreenEncoderConfig *config)
{
	HI_S32 ret;
	HI_UNF_ENC_FMT_E enFormat;

	if (config->flags & (DSECAPS_TV_STANDARDS | DSECAPS_RESOLUTION | DSECAPS_FREQUENCY | DSECAPS_SCANMODE))
    {
		enFormat = find_fmt(config->tv_standard, config->scanmode, config->frequency, config->resolution);
		if (HI_UNF_ENC_FMT_BUTT == enFormat)
        {
			D_ERROR("%s->%d, tv:%x, scan:%x, freq:%x, res:%x\n",__func__,__LINE__,
				config->tv_standard, config->scanmode, config->frequency, config->resolution);
			return DFB_INVARG;
		}

		ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, enFormat);
		if (HI_SUCCESS != ret)
		{
			D_ERROR("call HI_UNF_DISP_SetFormat failed.\n");
			return DFB_FAILURE;
		}

		if (  (HI_UNF_ENC_FMT_1080P_60 == enFormat) ||(HI_UNF_ENC_FMT_1080i_60 == enFormat)
            ||(HI_UNF_ENC_FMT_720P_60 == enFormat)  ||(HI_UNF_ENC_FMT_480P_60 == enFormat))
		{
			ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, HI_UNF_ENC_FMT_NTSC);
			if (HI_SUCCESS != ret)
			{
				D_ERROR("call HI_UNF_DISP_SetFormat failed.\n");
				return DFB_FAILURE;
			}
		}
		if (  (HI_UNF_ENC_FMT_1080P_50 == enFormat) || (HI_UNF_ENC_FMT_1080i_50 == enFormat)
            ||(HI_UNF_ENC_FMT_720P_50 == enFormat)  || (HI_UNF_ENC_FMT_576P_50 == enFormat))
		{
			ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, HI_UNF_ENC_FMT_PAL);
			if (HI_SUCCESS != ret)
			{
				D_ERROR("call HI_UNF_DISP_SetFormat failed.\n");
				return DFB_FAILURE;
			}
		}
	}

	/* adjustment */
	if (config->flags & DSECONF_ADJUSTMENT)
    {
		if (config->adjustment.flags & DCAF_BRIGHTNESS)
        {
			if (HI_SUCCESS != HI_UNF_DISP_SetBrightness(HI_UNF_DISPLAY0, (HI_U32)config->adjustment.brightness))
            {
				return DFB_FAILURE;
			}
		}

		if (config->adjustment.flags & DCAF_CONTRAST)
        {
			if (HI_SUCCESS != HI_UNF_DISP_SetContrast(HI_UNF_DISPLAY0, (HI_U32)config->adjustment.contrast))
            {
				return DFB_FAILURE;
			}
		}

		if (config->adjustment.flags & DCAF_HUE)
        {
			if (HI_SUCCESS != HI_UNF_DISP_SetHuePlus(HI_UNF_DISPLAY0, (HI_U32)config->adjustment.hue))
            {
				return DFB_FAILURE;
			}
		}

		if (config->adjustment.flags & DCAF_SATURATION)
        {
			if (HI_SUCCESS != HI_UNF_DISP_SetSaturation(HI_UNF_DISPLAY0, (HI_U32)config->adjustment.saturation))
            {
				return DFB_FAILURE;
			}
		}
	}
	return DFB_OK;
}


static DFBResult hisi_init_mixer (CoreScreen *screen, void *driver_data, void *screen_data, int mixer, DFBScreenMixerDescription *description, DFBScreenMixerConfig *config)
{
	return DFB_UNSUPPORTED;
}


static DFBResult hisi_config_mixer(CoreScreen *screen, void *driver_data, void *screen_data, int mixer, const DFBScreenMixerConfig *config)

{
	return DFB_UNSUPPORTED;
}


static DFBResult hisi_get_screen_size(CoreScreen *screen, void *driver_data, void *screen_data,int *ret_width, int *ret_height)
{
	HI_UNF_ENC_FMT_E eFormat;
	int i, cnt = sizeof(map) / sizeof(map[0]);


	if (HI_UNF_DISP_GetFormat(HI_UNF_DISPLAY1, &eFormat))
    {
		D_ERROR("%s->%d, fail to call HI_UNF_DISP_GetFormat\n",__func__,__LINE__);
		return DFB_FAILURE;
	}

	for (i = 0; i < cnt; i++)
    {
		if (map[i].fmt == eFormat)
		{
			break;
		}
	}

	if (i >= cnt)
	{
		return DFB_FAILURE;
	}

	switch (map[i].res)
    {
		case DSOR_1920_1080:
			*ret_width = 1920;
			*ret_height = 1080;
	    	break;

		case DSOR_1280_720:
			*ret_width  = 1280;
			*ret_height = 720;
			break;

		case DSOR_720_576:
			*ret_width = 720;
			*ret_height = 576;
			break;

		case DSOR_720_480:
			*ret_width = 720;
			*ret_height = 480;
			break;

		default:
			D_ERROR("%s->%d, cannot find fmt!\n",__func__,__LINE__);

			return DFB_FAILURE;
	}

	return DFB_OK;
}
