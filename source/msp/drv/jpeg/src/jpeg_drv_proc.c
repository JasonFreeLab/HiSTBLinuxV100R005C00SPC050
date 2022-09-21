/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_drv_proc.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description      : release jpeg proc debug
Function List   :

History           :
Date                            Author                     Modification
2017/07/05                    sdk                       Created file
******************************************************************************/

/*********************************add include here******************************/
#include "hi_jpeg_config.h"

#ifdef CONFIG_JPEG_PROC_ENABLE
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#include "hi_jpeg_checkpara.h"
#include "hi_drv_jpeg.h"
#include "hi_drv_proc.h"
#include "hi_gfx_comm_k.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition ******************************/

#define PROC_JPEG_ENTRY_NAME            "jpeg"

/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/

HI_JPEG_PROC_INFO_S *g_stJpegDecProcInfo = NULL;
static HI_BOOL gs_bProcOn = HI_FALSE;

/******************************* API forward declarations *******************/

static inline HI_VOID JPEG_PROC_PrintImagePixFmt (struct seq_file *pProcFile, HI_U32 ImagePixFmt);

/******************************* API realization *****************************/
static HI_S32 JPEG_PROC_Read(struct seq_file *p, HI_VOID *v)
{
   DRV_PROC_ITEM_S *item  = NULL;
   HI_JPEG_PROC_INFO_S *procinfo = NULL;

   CHECK_JPEG_EQUAL_RETURN(NULL, p, HI_FAILURE);

   item = (DRV_PROC_ITEM_S *)(p->private);
   CHECK_JPEG_EQUAL_RETURN(NULL, item, HI_FAILURE);

   procinfo = (HI_JPEG_PROC_INFO_S *)(item->data);
   CHECK_JPEG_EQUAL_RETURN(NULL, procinfo, HI_FAILURE);

   CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, gs_bProcOn, HI_SUCCESS);

   SEQ_Printf(p, "++++++++++++++++++++++++++++ decode state +++++++++++++++++++++++++\n");
   if (HI_TRUE == procinfo->bHardDec)
   {
      SEQ_Printf(p, "hard decode\t\t:true\n");
   }
   else
   {
       SEQ_Printf(p, "soft decode\t\t:true\n");
   }
   SEQ_Printf(p, "hard dec cost times\t:%ums\n", procinfo->HardDecTimes);
   SEQ_Printf(p, "decode cost times\t:%ums\n", procinfo->DecCostTimes);
   SEQ_Printf(p, "decode inflexion\t:%u\n",    procinfo->DecInflexion);
   SEQ_Printf(p, "decode scal times\t:%u\n",   procinfo->ScaleTimes);
   SEQ_Printf(p, "decode lock times\t:%d\n",   procinfo->DecLockTimes);
   SEQ_Printf(p, "decode pthread nums\t:%u\n", procinfo->DecPthreadNums);
   SEQ_Printf(p, "continue open times\t:%u\n", procinfo->OpenDevConTimes);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   SEQ_Printf(p, "++++++++++++++++++++++++++++ resolution +++++++++++++++++++++++++++\n");
   SEQ_Printf(p, "input width\t\t:%u\n",   procinfo->ImageWidth);
   SEQ_Printf(p, "input height\t\t:%u\n",  procinfo->ImageHeight);
   SEQ_Printf(p, "output width\t\t:%u\n",  procinfo->OutputWidth);
   SEQ_Printf(p, "output height\t\t:%u\n", procinfo->OutputHeight);
   SEQ_Printf(p, "output stride\t\t:%u\n", procinfo->OutputStride);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   SEQ_Printf(p, "++++++++++++++++++++++++++++ decode fmt +++++++++++++++++++++++++++\n");
   JPEG_PROC_PrintImagePixFmt(p, procinfo->ImageFmt);
   SEQ_Printf(p, "output format\t\t:%u\n",    procinfo->OutputFmt);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   SEQ_Printf(p, "++++++++++++++++++++++++++++ crop and skip ++++++++++++++++++++++++\n");
   SEQ_Printf(p, "crop rect\t\t:[%u %u %u %u]\n", procinfo->stCropRect.x,procinfo->stCropRect.y,procinfo->stCropRect.w,procinfo->stCropRect.h);
   SEQ_Printf(p, "skip scan lines\t\t:%u\n",      procinfo->SkipScanLines);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   SEQ_Printf(p, "++++++++++++++++++++++++++++ seek to soft  ++++++++++++++++++++++++\n");
   if (HI_TRUE == procinfo->bSeekToSoftDec)
   {
      SEQ_Printf(p, "seek soft dec\t\t:true\n");
   }
   else
   {
      SEQ_Printf(p, "seek soft dec\t\t:false\n");
   }
   SEQ_Printf(p, "seek cur pos\t\t:%u\n",  procinfo->CurOffset);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   SEQ_Printf(p, "++++++++++++++++++++++++++++ decode address +++++++++++++++++++++++\n");
   SEQ_Printf(p, "outbuf lu address\t\t:0x%x\n", procinfo->OutputLuPhyBuf);
   SEQ_Printf(p, "outbuf ch address\t\t:0x%x\n", procinfo->OutputChPhyBuf);
   SEQ_Printf(p, "buffer start address     \t:0x%x\n", procinfo->StartStreamBuf);
   SEQ_Printf(p, "buffer end address       \t:0x%x\n", procinfo->EndStreamBuf);
   SEQ_Printf(p, "save stream start address\t:0x%x\n", procinfo->StartSaveDataBuf);
   SEQ_Printf(p, "save stream end address  \t:0x%x\n", procinfo->EndSaveDataBuf);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   SEQ_Printf(p, "++++++++++++++++++++++++++++ YCbCr Info +++++++++++++++++++++++++++\n");
   SEQ_Printf(p, "lu width\t\t:%u\n",       procinfo->u32YWidth);
   SEQ_Printf(p, "lu height\t\t:%u\n",      procinfo->u32YHeight);
   SEQ_Printf(p, "lu stride\t\t:%u\n",      procinfo->u32YStride);
   SEQ_Printf(p, "lu size  \t\t:%u\n",      procinfo->u32YSize);
   SEQ_Printf(p, "ch width\t\t:%u\n",       procinfo->u32CWidth);
   SEQ_Printf(p, "ch height\t\t:%u\n",      procinfo->u32CHeight);
   SEQ_Printf(p, "ch stride\t\t:%u\n",      procinfo->u32CbCrStride);
   SEQ_Printf(p, "ch size  \t\t:%u\n",      procinfo->u32CSize);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   return HI_SUCCESS;
}

static inline HI_VOID JPEG_PROC_PrintImagePixFmt(struct seq_file *pProcFile, HI_U32 ImagePixFmt)
{
     HI_CHAR FmtName[50] = {'\0'};
     switch(ImagePixFmt)
     {
         case 0:
             strncpy(FmtName, "yuv400",strlen("yuv400"));
             FmtName[strlen("yuv400")] = '\0';
             break;
         case 1:
             strncpy(FmtName, "yuv420",strlen("yuv420"));
             FmtName[strlen("yuv420")] = '\0';
             break;
         case 2:
             strncpy(FmtName, "yuv422_21",strlen("yuv422_21"));
             FmtName[strlen("yuv422_21")] = '\0';
             break;
         case 3:
             strncpy(FmtName, "yuv422_12",strlen("yuv422_12"));
             FmtName[strlen("yuv422_12")] = '\0';
             break;
         case 4:
             strncpy(FmtName, "yuv444",strlen("yuv444"));
             FmtName[strlen("yuv444")] = '\0';
             break;
         default:
             strncpy(FmtName, "Unknown",strlen("Unknown"));
             FmtName[strlen("Unknown")] = '\0';
             break;
    }

    SEQ_Printf(pProcFile, "image format\t\t:%s\n", FmtName);

    return;
}

static HI_S32 JPEG_PROC_Write(struct file * file,const char __user * pBuf,size_t count,loff_t *ppos)
{
     HI_CHAR buf[128] = {'\0'};
     HI_CHAR *pStr = NULL;

     CHECK_JPEG_EQUAL_RETURN(NULL, pBuf, 0);

     if (count > sizeof(buf))
     {
        return 0;
     }

     if (copy_from_user(buf, pBuf, count))
     {
         return 0;
     }
     buf[sizeof(buf) - 1] = '\0';

     pStr = strstr(buf, "proc on");
     if (NULL != pStr)
     {
        gs_bProcOn = HI_TRUE;
        return count;
     }

     pStr = strstr(buf, "proc off");
     if (NULL != pStr)
     {
        gs_bProcOn = HI_FALSE;
        return count;
     }

     pStr = strstr(buf, "InflexionSize");
     if ((NULL != pStr) && (strlen(pStr) > strlen("InflexionSize")))
     {
         pStr = pStr + strlen("InflexionSize") + 1;
         g_stJpegDecProcInfo->DecInflexion = simple_strtoul(pStr,(char **)NULL, 0);
         return count;
     }

     return count;
}

/*****************************************************************************
   * Function      : JPEG_PROC_Init
   * Description  :  initial jpeg proc
   * param[in]    : NA
   * retval          : NA
 *****************************************************************************/
HI_S32 JPEG_PROC_Init(HI_VOID)
{
     GFX_PROC_ITEM_S pProcItem;
     HI_CHAR *pEntry_name = PROC_JPEG_ENTRY_NAME;

     pProcItem.fnRead   = JPEG_PROC_Read;
     pProcItem.fnWrite  = JPEG_PROC_Write;
     pProcItem.fnIoctl  = NULL;

     g_stJpegDecProcInfo = (HI_JPEG_PROC_INFO_S*)vmalloc(sizeof(HI_JPEG_PROC_INFO_S));
     if (NULL == g_stJpegDecProcInfo)
     {
        return HI_FAILURE;
     }

     HI_GFX_Memset((HI_VOID*)g_stJpegDecProcInfo, 0x0, sizeof(HI_JPEG_PROC_INFO_S));

     HI_GFX_PROC_AddModule(pEntry_name,&pProcItem,(HI_VOID *)g_stJpegDecProcInfo);

     return HI_SUCCESS;
}


/*****************************************************************************
  * Function      : JPEG_PROC_DInit
  * Description  :  dinitial jpeg proc
  * param[in]    : NA
  * retval          : NA
*****************************************************************************/
HI_VOID JPEG_PROC_DInit(HI_VOID)
{
     HI_CHAR *pEntry_name =  PROC_JPEG_ENTRY_NAME;

     if (NULL == g_stJpegDecProcInfo)
     {
        return;
     }

     HI_GFX_PROC_RemoveModule(pEntry_name);

     vfree(g_stJpegDecProcInfo);
     g_stJpegDecProcInfo = NULL;

     return;
}


/*****************************************************************************
   * Function      : JPEG_PROC_GetInflexionSize
   * Description  :  get decode inflexion size
   * param[ou]   : pInflexionSize
   * retval          : NA
 *****************************************************************************/
HI_VOID JPEG_PROC_GetInflexionSize(HI_U32 *pInflexionSize)
{
    if (NULL == pInflexionSize)
    {
       return;
    }
    *pInflexionSize = g_stJpegDecProcInfo->DecInflexion;
}

/*****************************************************************************
   * Function      : JPEG_PROC_SetStreamBuf
   * Description  :  set jpeg stream buffer
   * param[in]    : StartStreamBuf
   * param[in]    : EndStreamBuf
   * retval          : NA
 *****************************************************************************/
HI_VOID JPEG_PROC_SetStreamBuf(HI_U32 StartStreamBuf, HI_U32 EndStreamBuf)
{
    g_stJpegDecProcInfo->StartStreamBuf = StartStreamBuf;
    g_stJpegDecProcInfo->EndStreamBuf = EndStreamBuf;
}

/*****************************************************************************
   * Function      : JPEG_PROC_SetSaveDataBuf
   * Description  :  set jpeg save data buffer
   * param[in]    : StartSaveDataBuf
   * param[in]    : EndSaveDataBuf
   * retval          : NA
 *****************************************************************************/
HI_VOID JPEG_PROC_SetSaveDataBuf(HI_U32 StartSaveDataBuf, HI_U32 EndSaveDataBuf)
{
    g_stJpegDecProcInfo->StartSaveDataBuf = StartSaveDataBuf;
    g_stJpegDecProcInfo->EndSaveDataBuf = EndSaveDataBuf;
}

/*****************************************************************************
   * Function      : JPEG_PROC_SetPthreadNum
   * Description  :  set jpeg decode pthread numbers
   * param[in]    : PthreadNums
   * retval          : NA
 *****************************************************************************/
HI_VOID JPEG_PROC_SetPthreadNum(HI_U32 PthreadNums)
{
    g_stJpegDecProcInfo->DecPthreadNums = PthreadNums;
}


/*****************************************************************************
   * Function      : JPEG_PROC_SetDecLockTimes
   * Description  :  set jpeg decode has been lock times
   * param[in]    : PthreadNums
   * retval          : NA
 *****************************************************************************/
HI_VOID JPEG_PROC_SetDecLockTimes(HI_U32 LockTimes)
{
    g_stJpegDecProcInfo->DecLockTimes = LockTimes;
}


/*****************************************************************************
  * Function      : JPEG_PROC_SetOpenDevCnt
  * Description  :  set jpeg decode has been open times
  * param[in]    : PthreadNums
  * retval          : NA
*****************************************************************************/
HI_VOID JPEG_PROC_SetOpenDevCnt(HI_S32 OpenTimes)
{
    g_stJpegDecProcInfo->OpenDevConTimes += OpenTimes;
}


/*****************************************************************************
   * Function      : JPEG_PROC_SetInfo
   * Description  :  set jpeg proc information from user
   * param[in]    : Argc
   * retval          : HI-SUCCESS
 *****************************************************************************/
HI_S32 JPEG_PROC_SetInfo(HI_ULONG Argc)
{
    HI_JPEG_PROC_INFO_S stJpegDecProcInfo = {0};

    if (0 == Argc)
    {
        return -EFAULT;
    }

    if (copy_from_user((HI_VOID *)(&stJpegDecProcInfo), (HI_VOID *)Argc, sizeof(HI_JPEG_PROC_INFO_S)))
    {
        return -EFAULT;
    }

    g_stJpegDecProcInfo->bSeekToSoftDec = stJpegDecProcInfo.bSeekToSoftDec;
    g_stJpegDecProcInfo->bHardDec       = stJpegDecProcInfo.bHardDec;
    g_stJpegDecProcInfo->CurOffset      = stJpegDecProcInfo.CurOffset;
    g_stJpegDecProcInfo->SkipScanLines  = stJpegDecProcInfo.SkipScanLines;
    g_stJpegDecProcInfo->HardDecTimes   = stJpegDecProcInfo.HardDecTimes;
    g_stJpegDecProcInfo->DecCostTimes   = stJpegDecProcInfo.DecCostTimes;
    g_stJpegDecProcInfo->u32YWidth      = stJpegDecProcInfo.u32YWidth;
    g_stJpegDecProcInfo->u32YHeight     = stJpegDecProcInfo.u32YHeight;
    g_stJpegDecProcInfo->u32YSize       = stJpegDecProcInfo.u32YSize;
    g_stJpegDecProcInfo->u32CWidth      = stJpegDecProcInfo.u32CWidth;
    g_stJpegDecProcInfo->u32CHeight     = stJpegDecProcInfo.u32CHeight;
    g_stJpegDecProcInfo->u32CSize       = stJpegDecProcInfo.u32CSize;
    g_stJpegDecProcInfo->u32YStride     = stJpegDecProcInfo.u32YStride;
    g_stJpegDecProcInfo->u32CbCrStride  = stJpegDecProcInfo.u32CbCrStride;
    g_stJpegDecProcInfo->ImageWidth     = stJpegDecProcInfo.ImageWidth;
    g_stJpegDecProcInfo->ImageHeight    = stJpegDecProcInfo.ImageHeight;
    g_stJpegDecProcInfo->OutputWidth    = stJpegDecProcInfo.OutputWidth;
    g_stJpegDecProcInfo->OutputHeight   = stJpegDecProcInfo.OutputHeight;
    g_stJpegDecProcInfo->OutputStride   = stJpegDecProcInfo.OutputStride;
    g_stJpegDecProcInfo->ImageFmt       = stJpegDecProcInfo.ImageFmt;
    g_stJpegDecProcInfo->OutputFmt      = stJpegDecProcInfo.OutputFmt;
    g_stJpegDecProcInfo->OutputLuPhyBuf = stJpegDecProcInfo.OutputLuPhyBuf;
    g_stJpegDecProcInfo->OutputChPhyBuf = stJpegDecProcInfo.OutputChPhyBuf;
    g_stJpegDecProcInfo->ScaleTimes = stJpegDecProcInfo.ScaleTimes;
    g_stJpegDecProcInfo->stCropRect.x = stJpegDecProcInfo.stCropRect.x;
    g_stJpegDecProcInfo->stCropRect.y = stJpegDecProcInfo.stCropRect.y;
    g_stJpegDecProcInfo->stCropRect.w = stJpegDecProcInfo.stCropRect.w;
    g_stJpegDecProcInfo->stCropRect.h = stJpegDecProcInfo.stCropRect.h;

    return HI_SUCCESS;
}


#endif/**CONFIG_JPEG_PROC_ENABLE**/
