/******************************************************************************

  Copyright (C), 2001-2014, Hisilicon. Co., Ltd.

******************************************************************************
File Name       : sample_dec.c
Version         : Initial Draft
Author          :
Created         : 2013/06/08
Description     : test emc
Function List   :

History         :
Date                Author              Modification
2013/06/08          y00181162
******************************************************************************/


/*********************************add include here******************************/
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#include "hi_go.h"
#include "hi_go_decoder.h"
#include "hi_unf_disp.h"


/***************************** Macro Definition ******************************/
#define PIC_FILENAME      "../../res/ddr_test/jpg/emc_test.jpg"
#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
typedef struct hiSAMPLE_OSD_S
{
    pthread_t       ThreadId;
    HI_BOOL bExit;
    HI_BOOL bOnce;
    HI_HANDLE hDecTempSurface;
    HI_HANDLE hLayerSurface;
    HI_HANDLE hDecSurface;
    HI_HANDLE hLayer;
    HI_RECT stRect;
    HIGO_BLTOPT_S stBltOpt;
    HI_S32 s32MaxW; 
}SAMPLE_OSD_S;
static SAMPLE_OSD_S g_osdInfo;

static HI_S32 jpeg_dec(HI_CHAR *pszFileName, HI_HANDLE *pSurface)
{
    HI_S32 ret         = HI_SUCCESS;
    HI_HANDLE hDecoder = 0;
    HIGO_DEC_ATTR_S stSrcDesc;
    HIGO_DEC_IMGINFO_S stImgInfo;
    HIGO_DEC_IMGATTR_S stAttr;

    stSrcDesc.SrcType = HIGO_DEC_SRCTYPE_FILE;
    stSrcDesc.SrcInfo.pFileName = pszFileName;

    ret = HI_GO_CreateDecoder(&stSrcDesc, &hDecoder);
    if(HI_SUCCESS != ret){
        return ret;
    }

    ret = HI_GO_DecImgInfo(hDecoder, 0, &stImgInfo);
    if(HI_SUCCESS != ret){
        HI_GO_DestroyDecoder(hDecoder);
        return ret;
    }

    if(stImgInfo.Width > 4095){
       stAttr.Width = 4095;
    }else{
       stAttr.Width = stImgInfo.Width;
    }

    if(stImgInfo.Height > 4095){
        stAttr.Height = 4095;
    }else{
        stAttr.Height = stImgInfo.Height;
    }

    stAttr.Format = HIGO_PF_8888;

    if(stImgInfo.Width > 4095 || stImgInfo.Height > 4095){
        ret = HI_GO_DecImgData(hDecoder, 0, &stAttr, pSurface);
    }else{  
        ret  = HI_GO_DecImgData(hDecoder, 0, NULL, pSurface);
    }
    ret |= HI_GO_DestroyDecoder(hDecoder);
    
    return ret;
    
}


HI_VOID *OstThread(HI_VOID *pArgs)
{
    HI_S32 ret;
    
    if (HI_TRUE == g_osdInfo.bOnce)
    {
        fprintf(stderr,"decode the picture once!\n");
    }
    else
    {
        fprintf(stderr,"decode the picture each time!\n");
    }
    pthread_detach(g_osdInfo.ThreadId);
    while (HI_FALSE == g_osdInfo.bExit)
    {
        if (HI_FALSE == g_osdInfo.bOnce)
        {
            ret = jpeg_dec(PIC_FILENAME, &g_osdInfo.hDecTempSurface);
            if (HI_SUCCESS != ret)
            {
                fprintf(stderr,"========= jpeg dec failure ret = 0x%08x\n", ret);
            }
            
            HI_GO_FreeSurface(g_osdInfo.hDecTempSurface);
        }
        //printf("u32CurTimeMs = %ums\n", u32CurTimeMs);
        /** Blit it to graphic layer Surface */
        ret = HI_GO_Blit(g_osdInfo.hDecSurface, NULL, g_osdInfo.hLayerSurface, &g_osdInfo.stRect, &g_osdInfo.stBltOpt);
        if (HI_SUCCESS == ret)
        {
            /** fresh display*/
            HI_GO_RefreshLayer(g_osdInfo.hLayer, NULL);
            HI_GO_FillRect(g_osdInfo.hLayerSurface, &g_osdInfo.stRect, 0x80000000, HIGO_COMPOPT_NONE);
            if(g_osdInfo.stRect.w >= g_osdInfo.s32MaxW)
            {
               g_osdInfo.stRect.w = 5;
            }
            else
            {
               g_osdInfo.stRect.w += 1;
            }
        }
        usleep(30 * 1000);
    }
    return NULL;
}

HI_S32  HiOsdStart(HI_U32 u32Mode)
{
    HI_S32 ret     = 0;
    HIGO_LAYER_INFO_S stLayerInfo ;
    HIGO_LAYER_E eLayerID  = HIGO_LAYER_HD_1;

    /**initial resource*/
    ret  = HI_GO_Init();
    if (HI_SUCCESS != ret)
    {
        goto ERR1;
    }
    ret = HI_GO_GetLayerDefaultParam(eLayerID, &stLayerInfo);
    if (HI_SUCCESS != ret)
    {
        goto ERR1;
    }

    stLayerInfo.ScreenWidth    = SCREEN_WIDTH;
    stLayerInfo.ScreenHeight   = SCREEN_HEIGHT;
    stLayerInfo.DisplayWidth   = SCREEN_WIDTH;
    stLayerInfo.DisplayHeight  = SCREEN_HEIGHT;
    stLayerInfo.CanvasWidth    = SCREEN_WIDTH;
    stLayerInfo.CanvasHeight   = SCREEN_HEIGHT;
    stLayerInfo.PixelFormat     = HIGO_PF_8888;
    stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_DOUBBUFER;

    /** create the graphic layer and get the handler */
    ret = HI_GO_CreateLayer(&stLayerInfo, &g_osdInfo.hLayer);
    if (HI_SUCCESS != ret)
    {
        goto ERR1;
    }

    ret = HI_GO_GetLayerSurface(g_osdInfo.hLayer, &g_osdInfo.hLayerSurface);
    if (HI_SUCCESS != ret)
    {
        goto ERR2;
    }
    if (0 == u32Mode)
    {
        g_osdInfo.bOnce = HI_TRUE;
    }
    else
    {
        g_osdInfo.bOnce = HI_FALSE;
    }
    /**
     **rect pos and size
     **/
    g_osdInfo.stRect.x = 100;
    g_osdInfo.stRect.y = stLayerInfo.DisplayHeight/2 - 50;
    g_osdInfo.stRect.w = stLayerInfo.DisplayWidth - 2 * g_osdInfo.stRect.x;
    g_osdInfo.stRect.h = 2 * 50;

    g_osdInfo.s32MaxW = stLayerInfo.DisplayWidth - 2 * g_osdInfo.stRect.x;
    
    g_osdInfo.stBltOpt.EnableScale = HI_TRUE;
    /** clean the graphic layer Surface */
    HI_GO_FillRect(g_osdInfo.hLayerSurface, NULL, 0x80000000, HIGO_COMPOPT_NONE);

    /**decoding*/
    ret = jpeg_dec(PIC_FILENAME, &g_osdInfo.hDecSurface);
    if(HI_SUCCESS != ret)
    {
        fprintf(stderr,"========= jpeg dec failure \n");
        goto ERR2;
    }

    if (0 != pthread_create(&g_osdInfo.ThreadId, HI_NULL, OstThread, (HI_VOID*)&g_osdInfo))
    {
        printf("[%s] pthread_create failed\n", __FUNCTION__);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
ERR2:
    ret |= HI_GO_DestroyLayer(g_osdInfo.hLayer);
ERR1:
    ret |= HI_GO_Deinit();
    return ret;
}

HI_VOID HiOsdStop(HI_VOID)
{
    g_osdInfo.bExit = HI_TRUE;
    
    usleep(200 * 1000);
    HI_GO_FreeSurface(g_osdInfo.hDecSurface);
    HI_GO_DestroyLayer(g_osdInfo.hLayer);
    HI_GO_Deinit();

    return;
}

