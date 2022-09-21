/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : sample_animation.c
Version             : Initial Draft
Author              :
Created            : 2017/02/13
Description       : decode gif images
                          CNcomment: ½âÂëgif Í¼Æ¬ CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/02/13                  y00181162               Created file
******************************************************************************/


/***************************** add include here*********************************/
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "hi_go.h"
#include "sample_displayInit.h"


/***************************** Macro Definition ******************************/
#define WINDOWSSTYLE 0

#define PIC_DIRNAME "../res/gif"
#define MAX_FILENAME_LEN 256

#define DEFPIXELFORMAT    HIGO_PF_1555

/**===============================**/
#define DISPLAY_POS_X     200
#define DISPLAY_POS_Y     100
#define DISPLAY_WIDTH     500
#define DISPLAY_HEIGHT    400
/**===============================**/

#define CHECK_RETURN(Ret) \
    do {\
        if (HI_SUCCESS != Ret)\
        {\
            fprintf(stderr,"error :%x, line: %d\n", Ret, __LINE__); \
            return Ret;\
        }\
    }while (0)

#define SAMPLE_TRACE() \
    do {\
         fprintf(stderr,"============error line: %d\n",__LINE__); \
    }while (0)

/*************************** Structure Definition *****************************/
typedef struct
{
    HI_HANDLE BkSurface;
    HI_HANDLE DecHandle;
    HI_RECT   BKRect;
}ANIMATION_INFO;



/********************** Global Variable declaration *****************************/
static HI_HANDLE gs_hLayer = HI_INVALID_HANDLE;
static HI_HANDLE gs_hLayerSurface = HI_INVALID_HANDLE;
static HI_HANDLE gs_ColorKeyDstSurface = HI_INVALID_HANDLE;

static HI_S32 sample_animation_init(HI_VOID);
static HI_VOID sample_animation_dinit(HI_VOID);
static HI_S32 sample_animation_createlayersurface(HIGO_LAYER_E eLayerID);
static HI_VOID sample_animation_destorylayersurface(HI_VOID);
static HI_S32 sample_animation_createdecsurface(HI_CHAR *pFileName, HI_HANDLE *phRender);
static HI_S32 sample_animation_destorydecsurface(HI_HANDLE hRender);
static HI_S32 sample_animation_getprimaryInfo(HI_HANDLE hRender, HIGO_DEC_PRIMARYINFO_S * pPrimaryInfo);
static HI_S32 sample_animation_renderframe(HI_HANDLE hRender,HI_U32 Index,HI_S32 *pDelayTime,HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);


/******************************* API declaration ****************************/
HI_S32 filter(const struct dirent *pentry)
{
    HI_CHAR *pos = NULL;

    pos = strrchr(pentry->d_name, '.');
    if (NULL == pos)
    {
        return 0;
    }

    pos++;
    if (strcasecmp(pos, "gif") != 0)
    {
        return 0;
    }

    return 1;
}

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 Index = 0;
    HI_S32 s32FileNum;
    struct dirent **filelist = NULL;
    HIGO_DEC_PRIMARYINFO_S PrimaryInfo;
    HI_S32 LoopCount = 0;
    HI_S32 DelayTime = 0;
    HI_HANDLE hRender;
    HI_CHAR aszFileName[MAX_FILENAME_LEN + 1];

    Ret = sample_animation_init();
    CHECK_RETURN(Ret);

    Ret = sample_animation_createlayersurface(HIGO_LAYER_HD_0);
    CHECK_RETURN(Ret);


    s32FileNum = scandir(PIC_DIRNAME, &filelist, filter, alphasort);
    if (s32FileNum < 0)
    {
        Ret = HI_FAILURE;
        goto ERR_EXIT;
    }

    while (s32FileNum--)
    {
        sprintf(aszFileName, "%s/%s", PIC_DIRNAME, filelist[s32FileNum]->d_name);
        HI_PRINT("\n============================================================\n");
        HI_PRINT("dec file name:%s\n", aszFileName);
        HI_PRINT("============================================================\n");

        Ret = sample_animation_createdecsurface(aszFileName, &hRender);
        if (HI_SUCCESS != Ret)
        {
            SAMPLE_TRACE();
            break;
        }

        Ret = sample_animation_getprimaryInfo(hRender, &PrimaryInfo);
        if (Ret != HI_SUCCESS)
        {
            sample_animation_destorydecsurface(hRender);
            break;
        }

        Ret = HI_GO_CreateSurface(PrimaryInfo.ScrWidth,PrimaryInfo.ScrHeight, DEFPIXELFORMAT, &gs_ColorKeyDstSurface);
        if (Ret != HI_SUCCESS)
        {
            SAMPLE_TRACE();
            goto ERR_EXIT;
        }

        /**========================================================
                ** begin render every gif picture
                **========================================================**/
        LoopCount = PrimaryInfo.Count;
        Index = 0;
        while (LoopCount--)
        {
            Ret = sample_animation_renderframe(hRender,Index,&DelayTime,&PrimaryInfo);
            if (HI_SUCCESS != Ret)
            {
                break;
            }

            Ret = HI_GO_RefreshLayer(gs_hLayer, NULL);
            if (HI_SUCCESS != Ret)
            {
                break;
            }

            if (DelayTime == 0)
            {
               usleep(10000*20);
            }
            else
            {
                usleep(10000*DelayTime);
            }

            Index++;

            if (Index == (PrimaryInfo.Count))
            {
               Index = 0;
            }
        }
        /**========================================================
                ** end render gif picture
                **========================================================**/

        sample_animation_destorydecsurface(hRender);

        if (HI_INVALID_HANDLE != gs_ColorKeyDstSurface)
        {
           HI_GO_FreeSurface(gs_ColorKeyDstSurface);
        }
        gs_ColorKeyDstSurface = HI_INVALID_HANDLE;
    }

ERR_EXIT:
    sample_animation_destorylayersurface();
    sample_animation_dinit();

    return Ret;
}

static HI_S32 sample_animation_init(HI_VOID)
{
    HI_S32 Ret = HI_SUCCESS;

    Ret = Display_Init();
    if (HI_SUCCESS != Ret)
    {
      SAMPLE_TRACE();
      return HI_FAILURE;
    }
    sleep(3);

    Ret = HI_GO_Init();
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        Display_DeInit();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static HI_VOID sample_animation_dinit(HI_VOID)
{
    HI_GO_Deinit();
    Display_DeInit();
    return;
}


static HI_S32 sample_animation_createlayersurface(HIGO_LAYER_E eLayerID)
{
    HI_S32 Ret = HI_SUCCESS;
    HIGO_LAYER_INFO_S stLayerInfo;

    memset(&stLayerInfo, 0x0, sizeof(HIGO_LAYER_INFO_S));
    Ret = HI_GO_GetLayerDefaultParam(eLayerID, &stLayerInfo);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        return Ret;
    }

    stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_DOUBBUFER;
    Ret = HI_GO_CreateLayer(&stLayerInfo, &gs_hLayer);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        return Ret;
    }

    Ret = HI_GO_GetLayerSurface(gs_hLayer, &gs_hLayerSurface);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        HI_GO_DestroyLayer(gs_hLayer);
        gs_hLayer = HI_INVALID_HANDLE;
        gs_hLayerSurface = HI_INVALID_HANDLE;
        return Ret;
    }

    Ret = HI_GO_FillRect(gs_hLayerSurface , NULL, 0xffffffff, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        HI_GO_DestroyLayer(gs_hLayer);
        gs_hLayer = HI_INVALID_HANDLE;
        gs_hLayerSurface = HI_INVALID_HANDLE;
        return Ret;
    }

    return HI_SUCCESS;
}


static HI_VOID sample_animation_destorylayersurface(HI_VOID)
{
    if (HI_INVALID_HANDLE == gs_hLayer)
    {
       return;
    }

    HI_GO_DestroyLayer(gs_hLayer);

    gs_hLayer = HI_INVALID_HANDLE;
    gs_hLayerSurface = HI_INVALID_HANDLE;

    return;
}


static HI_S32 sample_animation_createdecsurface(HI_CHAR *pFileName, HI_HANDLE *phRender)
{
    HI_S32 Ret = HI_SUCCESS;
    HIGO_DEC_ATTR_S SrcDesc;
    HIGO_DEC_PRIMARYINFO_S PrimaryInfo;
    ANIMATION_INFO *pRender;
    HI_HANDLE DecHanle, Surface;

    if ((pFileName == NULL)|| (phRender == NULL))
    {
        SAMPLE_TRACE();
        return HI_FAILURE;
    }

    SrcDesc.SrcType = HIGO_DEC_SRCTYPE_FILE;
    SrcDesc.SrcInfo.pFileName = pFileName;
    Ret = HI_GO_CreateDecoder(&SrcDesc, &DecHanle);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        return HI_FAILURE;
    }

    Ret = HI_GO_DecCommInfo(DecHanle, &PrimaryInfo);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        goto err1;
    }

    Ret = HI_GO_CreateSurface(PrimaryInfo.ScrWidth, PrimaryInfo.ScrHeight, DEFPIXELFORMAT, &Surface);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE();
        goto err1;
    }

    pRender = (ANIMATION_INFO *)malloc(sizeof(ANIMATION_INFO));
    if (pRender == NULL)
    {
        SAMPLE_TRACE();
        Ret = HI_FAILURE;
        goto err2;
    }
    memset (pRender, 0, sizeof(ANIMATION_INFO));
    pRender->BkSurface = Surface;
    pRender->DecHandle = DecHanle;

    *phRender = (unsigned long)pRender;

    return HI_SUCCESS;

err2:
    HI_GO_FreeSurface(Surface);

err1:
    HI_GO_DestroyDecoder(DecHanle);

    return Ret;
}

static HI_S32 sample_animation_destorydecsurface(HI_HANDLE hRender)
{
    ANIMATION_INFO *pRender = NULL;

    pRender = (ANIMATION_INFO *)(unsigned long)hRender;
    if (NULL == pRender)
    {
        SAMPLE_TRACE();
        return HI_FAILURE;
    }

    HI_GO_DestroyDecoder(pRender->DecHandle);

    HI_GO_FreeSurface(pRender->BkSurface);

    free(pRender);

    return HI_SUCCESS;
}


static HI_S32 sample_animation_getprimaryInfo(HI_HANDLE hRender, HIGO_DEC_PRIMARYINFO_S * pPrimaryInfo)
{
    HI_S32 Ret = HI_SUCCESS;
    ANIMATION_INFO *pRender = NULL;

    pRender = (ANIMATION_INFO *)(unsigned long)hRender;
    if (NULL == pRender)
    {
        SAMPLE_TRACE();
        return HI_FAILURE;
    }

    Ret = HI_GO_DecCommInfo(pRender->DecHandle, pPrimaryInfo);
    CHECK_RETURN(Ret);

    return HI_SUCCESS;
}

static HI_S32 sample_animation_renderframe(HI_HANDLE hRender,HI_U32 Index,HI_S32 *pDelayTime,HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_HANDLE ImgSurface = HI_INVALID_HANDLE;
    HIGO_DEC_IMGINFO_S ImgInfo, LastImgInfo;
    HI_COLOR BKColor;
#if 0
    HI_COLOR ColorKey = 0;
#endif
    HIGO_BLTOPT_S BltOpt;
    HI_RECT Rect,LastRect;
    ANIMATION_INFO *pRender;

#ifndef WINDOWSSTYLE
    if (pPrimaryInfo->IsHaveBGColor)
    {
        BKColor = pPrimaryInfo->BGColor;
    }
    else
    {
        BKColor = 0xffffffff;
    }
#else
    BKColor = 0xffffffff;
#endif

    pRender = (ANIMATION_INFO *)(unsigned long)hRender;

    if (0 == Index)
    {
        Ret = HI_GO_FillRect(gs_ColorKeyDstSurface, NULL, BKColor, HIGO_COMPOPT_NONE);
        CHECK_RETURN(Ret);
    }
    else
    {
        Ret = HI_GO_DecImgInfo(pRender->DecHandle, (Index - 1), &LastImgInfo);
        CHECK_RETURN(Ret);

        LastRect.x = pRender->BKRect.x;
        LastRect.y = pRender->BKRect.y;
        LastRect.w = pRender->BKRect.w;
        LastRect.h = pRender->BKRect.h;

        if (2 == LastImgInfo.DisposalMethod)
        {
            Ret = HI_GO_FillRect(gs_ColorKeyDstSurface, &LastRect, BKColor, HIGO_COMPOPT_NONE);
            CHECK_RETURN(Ret);
        }
        else if (3 == LastImgInfo.DisposalMethod)
        {
            memset(&BltOpt, 0x0, sizeof(HIGO_BLTOPT_S));
            Ret = HI_GO_Blit(pRender->BkSurface, &(pRender->BKRect), gs_ColorKeyDstSurface, &LastRect, &BltOpt);
            CHECK_RETURN(Ret);
        }
    }

    /** get curent gif picture information **/
    Ret = HI_GO_DecImgInfo(pRender->DecHandle, Index, &ImgInfo);
    CHECK_RETURN(Ret);

    if (3 == ImgInfo.DisposalMethod)
    {
        memset(&BltOpt, 0x0, sizeof(HIGO_BLTOPT_S));
        Ret = HI_GO_Blit(gs_ColorKeyDstSurface, NULL, pRender->BkSurface, NULL, &BltOpt);
        CHECK_RETURN(Ret);
    }

    Ret = HI_GO_DecImgData(pRender->DecHandle, Index, NULL, &ImgSurface);
    CHECK_RETURN(Ret);

    /**
         ** if this gif picture has key info, should colorkey first, here should not scale for blit.
         **/
    if (ImgInfo.IsHaveKey)
    {
        Rect.x = ImgInfo.OffSetX;
        Rect.y = ImgInfo.OffSetY;
        Rect.w = pPrimaryInfo->ScrWidth;
        Rect.h = pPrimaryInfo->ScrHeight;

        memset(&BltOpt, 0x0, sizeof(HIGO_BLTOPT_S));
        BltOpt.ColorKeyFrom = HIGO_CKEY_SRC;
        Ret = HI_GO_Blit(ImgSurface, HI_NULL, gs_ColorKeyDstSurface, &Rect, &BltOpt);
        CHECK_RETURN(Ret);

        #if 0
        HI_GO_Surface2Bmp(gs_ColorKeyDstSurface,NULL);
        HI_GO_GetSurfaceColorKey(ImgSurface,&ColorKey);
        HI_PRINT("[%d %d %d %d],ColorKey = 0x%x image method = %d\n",Rect.x,Rect.y,Rect.w,Rect.h,ColorKey,ImgInfo.DisposalMethod);
        #endif
    }
    if (HI_SUCCESS != Ret)
    {
       SAMPLE_TRACE();
       goto err;
    }

    /**
         ** blit picture surface to layer surface.
         **/
    Rect.x = DISPLAY_POS_X;
    Rect.y = DISPLAY_POS_Y;
    Rect.w = DISPLAY_WIDTH;
    Rect.h = DISPLAY_HEIGHT;
    memset(&BltOpt, 0x0, sizeof(HIGO_BLTOPT_S));
    BltOpt.EnableScale = HI_TRUE;
    if (ImgInfo.IsHaveKey)
    {
       /** if the gif picture has key information, blit the surface that has been colorkey to layersurface **/
       Ret = HI_GO_Blit(gs_ColorKeyDstSurface, HI_NULL, gs_hLayerSurface, &Rect, &BltOpt);
    }
    else
    {
       /** if the gif picture has not key information, blit the decode surface to layersurface **/
       Ret = HI_GO_Blit(ImgSurface, HI_NULL, gs_hLayerSurface, &Rect, &BltOpt);
    }

    if (HI_SUCCESS != Ret)
    {
       SAMPLE_TRACE();
       goto err;
    }

    if (HI_INVALID_HANDLE != ImgSurface)
    {
       HI_GO_FreeSurface(ImgSurface);
    }

    *pDelayTime = ImgInfo.DelayTime;

    return HI_SUCCESS;
err:

    if (HI_INVALID_HANDLE != ImgSurface)
    {
       HI_GO_FreeSurface(ImgSurface);
    }

    return Ret;
}
