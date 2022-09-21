/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_debug.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : debug for jpeg decode problem
                        解码问题调试
Function List   :


History           :
Date                          Author                    Modification
2017/07/05                 sdk                        Created file
******************************************************************************/

/****************************  add include here     *********************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE

#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
#include <cutils/properties.h>
#endif

/***************************** Macro Definition ***********************************/
#define DADA_WRITE( file,fmt, args... )\
     do { \
          fprintf(file,fmt, ##args );\
     } while (0)
#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
    #define SAVE_DATA_FILE_DIR             "/mnt/sdcard/Movies"
#else
    #define SAVE_DATA_FILE_DIR             "/tmp"
#endif

#ifdef CONFIG_JPEG_SAVE_SCEN
#define  PRN_SCENE(pFile,addr,data)        fprintf(pFile, "W 0x%08x 0x%08x word single\n",addr,data)
#define  SCEN_FILE_NAME                    "/tmp/output_file.scen"
#define  SCEN_PRINT                        fprintf
#endif

/***************************** Structure Definition ********************************/

#ifdef JPEG_HDEC_DEBUG_SAVE_BMP
typedef struct  tagBITMAPFILEHEADER
{
    HI_U16 u16Type;
    HI_U32 u32Size;
    HI_U16 u16Reserved1;
    HI_U16 u16Reserved2;
    HI_U32 u32OffBits;
}__attribute__((packed)) BMP_BMFHEADER_S;


typedef  struct tagBITMAPINFOHEADER
{
    HI_U32 u32Size;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U16 u32Planes;
    HI_U16 u32PixbitCount;
    HI_U32 u32Compression;
    HI_U32 u32SizeImage;
    HI_U32 u32XPelsPerMeter;
    HI_U32 u32YPelsPerMeter;
    HI_U32 u32ClrUsed;
    HI_U32 u32ClrImportant;
} BMP_BMIHEADER_S;
#endif

/***************************** Global Variable declaration ****************************/

/***************************** API forward declarations *****************************/

/***************************** API realization *************************************/
#ifdef JPEG_HDEC_DEBUG_PROC

#ifdef CONFIG_JPEG_PROC_ENABLE
static inline HI_S32 JPEG_HDEC_GetScalRation(HI_U32 ScaleRation)
{
    if (0 == ScaleRation)
    {
       return 1;
    }
    else if (1 == ScaleRation)
    {
       return 2;
    }
    else if (2 == ScaleRation)
    {
       return 4;
    }
    else
    {
       return 8;
    }
}

static HI_VOID JPEG_HDEC_SetProcInfo(const struct jpeg_decompress_struct *cinfo)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_JPEG_PROC_INFO_S stProcInfo;
     JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     stProcInfo.bHardDec     = pJpegHandle->bHdecEnd;
     stProcInfo.DecCostTimes = pJpegHandle->DecCostTimes;
     stProcInfo.HardDecTimes = pJpegHandle->HardDecTimes;

     stProcInfo.u32YWidth   = pJpegHandle->stJpegSofInfo.u32YWidth;
     stProcInfo.u32YHeight  = pJpegHandle->stJpegSofInfo.u32YHeight;
     stProcInfo.u32YSize    = pJpegHandle->stJpegSofInfo.u32YSize;
     stProcInfo.u32CWidth   = pJpegHandle->stJpegSofInfo.u32CWidth;
     stProcInfo.u32CHeight  = pJpegHandle->stJpegSofInfo.u32CHeight;
     stProcInfo.u32CSize    = pJpegHandle->stJpegSofInfo.u32CSize;
     stProcInfo.u32YStride  = pJpegHandle->stJpegSofInfo.u32YStride;
     stProcInfo.u32CbCrStride = pJpegHandle->stJpegSofInfo.u32CbCrStride;

     stProcInfo.SkipScanLines = pJpegHandle->SkipLines;
     stProcInfo.stCropRect.x  = pJpegHandle->stCropRect.x;
     stProcInfo.stCropRect.y  = pJpegHandle->stCropRect.y;
     stProcInfo.stCropRect.w  = pJpegHandle->stCropRect.w;
     stProcInfo.stCropRect.h  = pJpegHandle->stCropRect.h;

     stProcInfo.bSeekToSoftDec = pJpegHandle->bSeekToSoftDec;
     stProcInfo.CurOffset = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos;

     stProcInfo.ImageWidth   = cinfo->image_width;
     stProcInfo.ImageHeight  = cinfo->image_height;
     stProcInfo.OutputWidth  = cinfo->output_width;
     stProcInfo.OutputHeight = cinfo->output_height;
     stProcInfo.OutputStride = pJpegHandle->stOutSurface.u32OutStride[0];
     stProcInfo.ImageFmt     = (HI_U32)pJpegHandle->enImageFmt;
     stProcInfo.OutputFmt    = (HI_U32)cinfo->out_color_space;
     stProcInfo.OutputLuPhyBuf = pJpegHandle->stDecSurface.DecOutPhy[0];
     stProcInfo.OutputChPhyBuf = pJpegHandle->stDecSurface.DecOutPhy[1];

     stProcInfo.ScaleTimes = JPEG_HDEC_GetScalRation(pJpegHandle->ScalRation);

     if (pJpegHandle->JpegDev < 0)
     {
        return;
     }

     Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_READPROC, &stProcInfo);
     if (HI_SUCCESS != Ret)
     {
        JPEG_TRACE("+++++set jpeg proc failure\n");
        return;
     }

     return;
}
#endif
#endif


#ifdef JPEG_HDEC_DEBUG_CHECK_SAVE_DATA
/*****************************************************************************
* func           : JPEG_HDEC_WhetherSaveData
* description :  check whethe should save data
                       CNcomment:判断是否可以保存内容
* param[in]  : SaveMode               CNcomment: 要保存的类型  CNend\n
* others:     : NA
*****************************************************************************/
static HI_BOOL JPEG_HDEC_WhetherSaveData(HI_CHAR* SaveMode)
{
#ifdef CONFIG_GFX_PROPERTY_SUPPORT
     HI_CHAR JpegDecMod[256] = {'\0'};
     property_get(SaveMode,JpegDecMod,"no");
     JpegDecMod[sizeof(JpegDecMod) - 1] = '\0';
     if (0 == strncmp("no", JpegDecMod, strlen("no") > strlen(JpegDecMod) ? (strlen("no")) : (strlen(JpegDecMod))))
     {
        return HI_FALSE;
     }
#else
     HI_CHAR *pJpegDecMod = NULL;
     pJpegDecMod = getenv(SaveMode);
     if (NULL == pJpegDecMod)
     {
         return HI_FALSE;
     }
     if (0 != strncmp("yes", pJpegDecMod, strlen("yes") > strlen(pJpegDecMod)? strlen("yes"):strlen(pJpegDecMod)))
     {
        return HI_FALSE;
     }
#endif
    return HI_TRUE;
}
#endif

#ifdef JPEG_HDEC_DEBUG_SAVE_YUVSP
/*****************************************************************************
* func           : JPEG_HDEC_SaveYUVSP
* description : save hard decode yuvsp data
                       CNcomment:保存YUV 数据，定位解码是否正确
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* others:     : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_SaveYUVSP(const struct jpeg_decompress_struct *cinfo)
{
     HI_CHAR pFileName[256];
     HI_CHAR pHdrName[256];
     HI_CHAR *pFile = "hard_dec_yuvsp";

     FILE* pOutFile = NULL;
     FILE* pHdrFile = NULL;
     HI_S32 s32Cnt  = 0;
     HI_S32 s32Cnt1 = 0;
     HI_CHAR *pTmp  = NULL;

     HI_CHAR pTmpCbCr[10000];
     HI_CHAR* pYAddr   = NULL;
     HI_CHAR* pUVAddr  = NULL;

     HI_BOOL SaveYuvSp = HI_FALSE;
     static HI_U32 Count = 0;

     JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     /** setprop persist.sys.jpeg.save_yuvsp yes **/
     /** export HISI_JPEG_SAVE_YUVSP=yes **/
#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
     SaveYuvSp = JPEG_HDEC_WhetherSaveData("persist.sys.jpeg.save_yuvsp");
#else
     SaveYuvSp = JPEG_HDEC_WhetherSaveData("HISI_JPEG_SAVE_YUVSP");
#endif
     if (HI_FALSE == SaveYuvSp)
     {
        return;
     }

     snprintf(pFileName,256,"%s/%s%d.yuv",SAVE_DATA_FILE_DIR,pFile,Count);
     pFileName[sizeof(pFileName) - 1] = '\0';

     snprintf(pHdrName,256,"%s/%s%d.hdr",SAVE_DATA_FILE_DIR,pFile,Count);
     pHdrName[sizeof(pHdrName) - 1] = '\0';

     Count++;

     pOutFile = fopen(pFileName,"wb+");
     if (NULL == pOutFile)
     {
        JPEG_TRACE("open %s failure\n",pFileName);
        return;
     }

     pYAddr  = pJpegHandle->stDecSurface.DecOutVir[0];
     pUVAddr = pJpegHandle->stDecSurface.DecOutVir[1];

     if (0 != pJpegHandle->stJpegSofInfo.u32YWidth)
     {
         pTmp = pYAddr;
         for (s32Cnt = 0; s32Cnt < (HI_S32)pJpegHandle->stJpegSofInfo.u32YHeight; s32Cnt++)
         {
             fwrite(pTmp, pJpegHandle->stJpegSofInfo.u32YWidth, 1, pOutFile);
             pTmp += pJpegHandle->stJpegSofInfo.u32YStride;
         }
     }

     if (0 != pJpegHandle->stJpegSofInfo.u32CWidth){

         pTmp = pUVAddr;
         for (s32Cnt = 0; s32Cnt < (HI_S32)pJpegHandle->stJpegSofInfo.u32CHeight; s32Cnt++)
         {
             for (s32Cnt1=0; s32Cnt1 < (HI_S32)pJpegHandle->stJpegSofInfo.u32CWidth; s32Cnt1++)
             {
                 pTmpCbCr[s32Cnt1] = pTmp[2*s32Cnt1 + 1];
             }
             fwrite(pTmpCbCr, pJpegHandle->stJpegSofInfo.u32CWidth, 1, pOutFile );
             pTmp += pJpegHandle->stJpegSofInfo.u32CbCrStride;
         }

         pTmp = pUVAddr;
         for (s32Cnt = 0; s32Cnt < (HI_S32)pJpegHandle->stJpegSofInfo.u32CHeight; s32Cnt++)
         {
             for (s32Cnt1 = 0; s32Cnt1 < (HI_S32)pJpegHandle->stJpegSofInfo.u32CWidth; s32Cnt1++)
             {
                 pTmpCbCr[s32Cnt1] = pTmp[2*s32Cnt1 + 0];
             }
             fwrite(pTmpCbCr, pJpegHandle->stJpegSofInfo.u32CWidth, 1, pOutFile);
             pTmp += pJpegHandle->stJpegSofInfo.u32CbCrStride;
         }
     }

     fclose(pOutFile);

     pHdrFile = fopen(pHdrName,"wb+");
     if (NULL == pHdrFile)
     {
         JPEG_TRACE("open %s failure\n",pHdrName);
         return;
     }

     switch (pJpegHandle->enImageFmt)
     {
         case JPEG_FMT_YUV400:
             DADA_WRITE(pHdrFile, "format = \"Y\" ;\n");
             break;
         case JPEG_FMT_YUV420:
             DADA_WRITE(pHdrFile, "format = \"YUV420\" ;\n");
             break;
         case JPEG_FMT_YUV422_12:
             DADA_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
             break;
         case JPEG_FMT_YUV422_21:
             DADA_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
             break;
         case JPEG_FMT_YUV444:
             DADA_WRITE(pHdrFile, "format = \"YUV444\" ;\n");
             break;
         default:
             JPEG_TRACE("format is unknow ;\n");
             break;
     }

     DADA_WRITE(pHdrFile, "offset = 0 ;\n");
     DADA_WRITE(pHdrFile, "width = %d ;\n", pJpegHandle->stJpegSofInfo.u32YWidth);
     DADA_WRITE(pHdrFile, "height = %d ;\n", pJpegHandle->stJpegSofInfo.u32YHeight);
     DADA_WRITE(pHdrFile, "framerate = 50 ;\n");
     DADA_WRITE(pHdrFile, "loop = 1 ;\n");

     fclose(pHdrFile);

     JPEG_TRACE("\n===============================================================================\n");
     JPEG_TRACE("save yuvsp data success\n");
     JPEG_TRACE("the yuvsp file name is %s\n",pFileName);
     JPEG_TRACE("the hdr file name is %s\n",pHdrName);
     JPEG_TRACE("y width   = %d\n",   pJpegHandle->stJpegSofInfo.u32YWidth);
     JPEG_TRACE("y height  = %d\n",   pJpegHandle->stJpegSofInfo.u32YHeight);
     JPEG_TRACE("y stride  = %d\n",   pJpegHandle->stJpegSofInfo.u32YStride);
     JPEG_TRACE("uv width  = %d\n",   pJpegHandle->stJpegSofInfo.u32CWidth);
     JPEG_TRACE("uv height = %d\n",   pJpegHandle->stJpegSofInfo.u32CHeight);
     JPEG_TRACE("uv stride = %d\n",   pJpegHandle->stJpegSofInfo.u32CbCrStride);
     JPEG_TRACE("y ddr     = 0x%lx\n",(unsigned long)pYAddr);
     JPEG_TRACE("uv ddr    = 0x%lx\n",(unsigned long)pUVAddr);
     JPEG_TRACE("img fmt   = %d\n",   pJpegHandle->enImageFmt);
     JPEG_TRACE("===============================================================================\n");

     return;
}
#endif



#ifdef JPEG_HDEC_DEBUG_SAVE_INPUT_STREAM
/*****************************************************************************
* func           : JPEG_HDEC_SaveInputStream
* description : save input stream
                       CNcomment:保存输入的码流数据
* param[in]  : cinfo               CNcomment: 解码对象  CNend\n
* others:     : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_SaveInputStream(HI_UCHAR* InputStreamVirBuf, HI_ULONG InputStreamSize, HI_UCHAR* InputSecodStreamVirBuf, HI_ULONG InputSecondStreamSize)
{
     HI_CHAR OutFileName[256];
     HI_CHAR *pFile = "input_stream_";
     FILE* OutFile  = NULL;
     static HI_U32 SameFileCnt = 0;

     HI_BOOL SaveInputStream = HI_FALSE;

     if ((NULL == InputStreamVirBuf) || (0 == InputStreamSize))
     {
         return;
     }

     /** setprop persist.sys.jpeg.save_input_stream yes **/
     /** export HISI_JPEG_SAVE_INPUT_STREAM=yes **/
 #ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
     SaveInputStream = JPEG_HDEC_WhetherSaveData("persist.sys.jpeg.save_input_stream");
 #else
     SaveInputStream = JPEG_HDEC_WhetherSaveData("HISI_JPEG_SAVE_INPUT_STREAM");
 #endif
     if (HI_FALSE == SaveInputStream)
     {
        return;
     }

     snprintf(OutFileName,256,"%s/%s%d.jpg",SAVE_DATA_FILE_DIR,pFile,SameFileCnt++);
     OutFileName[sizeof(OutFileName) - 1] = '\0';

     OutFile = fopen(OutFileName,"wb+");
     if (NULL == OutFile)
     {
         return;
     }

     fwrite((void*)InputStreamVirBuf, InputStreamSize, 1, OutFile);

     if (NULL != InputSecodStreamVirBuf)
     {
        fwrite((void*)InputSecodStreamVirBuf, InputSecondStreamSize, 1, OutFile);
     }

     fclose(OutFile);

     JPEG_TRACE("\n========================================================\n");
     JPEG_TRACE("save input data %s success\n",OutFileName);
     JPEG_TRACE("========================================================\n");

     return;
}
#endif



#ifdef JPEG_HDEC_DEBUG_SAVE_BMP
/*****************************************************************************
* func           : JPEG_HDEC_SaveBmp
* description : save xrgb to bmp picture
                       CNcomment:保存bmp图片
* param[in]  : cinfo                 CNcomment: 解码对象  CNend\n
* param[in]  : 其他信息
* others:     : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_SaveBmp(const struct jpeg_decompress_struct *cinfo,HI_CHAR* DataVir,HI_U32 u32Width,HI_U32 u32Height,HI_U32 u32Stride)
{
     HI_CHAR OutFileName[256];
     HI_CHAR *pFile = "jpeg_hard_xrgb";
     FILE* OutFile  = NULL;
     static HI_U32 u32Cnt = 0;

     HI_BOOL SaveBmp = HI_FALSE;

     BMP_BMFHEADER_S sBmpHeader;
     BMP_BMIHEADER_S sBmpInfoHeader;

     HI_UNUSED(cinfo);

     /** setprop persist.sys.jpeg.save_bmp yes **/
     /** export HISI_JPEG_SAVE_BMP=yes **/
#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
     SaveBmp = JPEG_HDEC_WhetherSaveData("persist.sys.jpeg.save_bmp");
#else
     SaveBmp = JPEG_HDEC_WhetherSaveData("HISI_JPEG_SAVE_BMP");
#endif
     if (HI_FALSE == SaveBmp)
     {
        return;
     }

     HI_GFX_Memset(&sBmpHeader,0x0,sizeof(BMP_BMFHEADER_S));
     HI_GFX_Memset(&sBmpInfoHeader,0x0,sizeof(BMP_BMIHEADER_S));

     sBmpHeader.u16Type = 0x4D42;
     sBmpHeader.u32Size = (u32Stride * u32Height) + sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S);
     sBmpHeader.u16Reserved1 = 0;
     sBmpHeader.u16Reserved2 = 0;
     sBmpHeader.u32OffBits   = sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S);

     sBmpInfoHeader.u32Size = sizeof(BMP_BMIHEADER_S);
     sBmpInfoHeader.u32Width = u32Width;
     sBmpInfoHeader.u32Height = u32Height;
     sBmpInfoHeader.u32Planes = 1;
     sBmpInfoHeader.u32PixbitCount = 24;
     sBmpInfoHeader.u32Compression = 0;
     sBmpInfoHeader.u32SizeImage = 0;
     sBmpInfoHeader.u32XPelsPerMeter = u32Width;
     sBmpInfoHeader.u32YPelsPerMeter = u32Height;
     sBmpInfoHeader.u32ClrUsed = 0;
     sBmpInfoHeader.u32ClrImportant = 0;

     snprintf(OutFileName,256,"%s/%s%d.bmp",SAVE_DATA_FILE_DIR,pFile,u32Cnt++);
     OutFileName[sizeof(OutFileName) - 1] = '\0';

     OutFile = fopen(OutFileName,"wb+");
     if (NULL == OutFile)
     {
         return;
     }

     fwrite((HI_S8*)&sBmpHeader, sizeof(BMP_BMFHEADER_S), 1, OutFile);
     fwrite((HI_S8*)&sBmpInfoHeader, sizeof(BMP_BMIHEADER_S), 1, OutFile);
     fwrite(DataVir, (u32Stride * u32Height), 1, OutFile);

     fclose(OutFile);

     JPEG_TRACE("\n========================================================\n");
     JPEG_TRACE("save bmp data %s success\n",OutFileName);
     JPEG_TRACE("========================================================\n");

     return;
}
#endif


#ifdef JPEG_HDEC_DEBUG_SAVE_SCEN
#ifdef CONFIG_JPEG_SAVE_SCEN
/*****************************************************************************
* func            : JPEG_HDEC_OpenScenFile
* description  : open the scen file
                        CNcomment: 打开导现场的文件 CNend\n
* param[in]   : cinfo.       CNcomment:解码对象     CNend\n
* retval         : NA
* others:       : NA
*****************************************************************************/
HI_S32 JPEG_HDEC_OpenScenFile(const struct jpeg_decompress_struct *cinfo)
{
     char pFileName[256] = {'\0'};
     char pNum[20] = {'\0'};
     static HI_S32 s32Cnt = 0;

     CHECK_JPEG_EQUAL_RETURN(NULL, cinfo, HI_FAILURE);
     JPEG_API_MODULE_DEFINE_HANDLE();

     if (NULL != pJpegHandle->pScenFile)
     {
        return HI_SUCCESS;
     }

     snprintf(pNum,sizeof(pNum), "%d", s32Cnt++);
     pNum[sizeof(pNum) - 1] = '\0';

     strncpy(pFileName, SCEN_FILE_NAME,strlen(SCEN_FILE_NAME));
     strncat(pFileName,pNum,strlen(pNum));
     pFileName[sizeof(pFileName) - 1] = '\0';

     pJpegHandle->pScenFile = fopen(pFileName,"wb+");
     if (NULL == pJpegHandle->pScenFile)
     {
        JPEG_TRACE("open scen file failure\n");
        return HI_FAILURE;
     }

     SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
     SCEN_PRINT(pJpegHandle->pScenFile,"the dec file name is %s\n",pFileName);
     SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");

     return HI_SUCCESS;
}

/*****************************************************************************
* func            : JPEG_HDEC_CloseScenFile
* description  : close the scen file
                          CNcomment: 关闭导现场的文件 CNend\n
* param[in]   : cinfo.       CNcomment:解码对象     CNend\n
* retval         : NA
* others:       : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_CloseScenFile(const struct jpeg_decompress_struct *cinfo)
{
     CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
     JPEG_API_MODULE_DEFINE_HANDLE();

     if (NULL != pJpegHandle->pScenFile)
     {
         fclose(pJpegHandle->pScenFile);
     }
     pJpegHandle->pScenFile = NULL;

     return;
}


/*****************************************************************************
* func            : JPEG_HDEC_GetScenData
* description  : get scen data.
                        CNcomment: 获取现场数据 CNend\n
* param[in]   : cinfo.       CNcomment:解码对象     CNend\n
* retval          : NA
* others:       : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_GetScenData(const struct jpeg_decompress_struct *cinfo)
{
    HI_S32 offset = 0;
    HI_S32 cnt = 0;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    for (offset = 0xc; offset <= 0x6bc; offset+= 4)
    {
        if (JPGD_REG_STADD == offset)
        {
            cnt++;
        }
        else if (JPGD_REG_ENDADD == offset)
        {
            cnt++;
        }
        else
        {
            pJpegHandle->s32RegData[cnt] = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,offset);
            cnt++;
        }
    }

    return;
}

/*****************************************************************************
* func              : JPEG_HDEC_PrintScenData
* description    : export the scen data.
                          CNcomment: 导出现场数据 CNend\n
* param[in]      : cinfo.                 CNcomment:解码对象         CNend\n
* param[in]      : pStreamStartBuf.       CNcomment:码流起始地址     CNend\n
* param[in]      : pStreamEndBuf.         CNcomment:码流结束地址     CNend\n
* retval            : NA
* others:        : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_PrintScenData(const struct jpeg_decompress_struct *cinfo, HI_U32 StartDataBuf, HI_U32 EndDataBuf)
{
    HI_S32 offset = 0;
    HI_S32 cnt  = 0;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (NULL == pJpegHandle->pScenFile)
    {
        return;
    }

    SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
    SCEN_PRINT(pJpegHandle->pScenFile,"   the register data \n");
    SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");

    for (offset = 0xc; offset <= 0x6bc; offset += 4)
    {
        if (JPGD_REG_STADD == offset)
        {
            PRN_SCENE(pJpegHandle->pScenFile,JPGD_REG_BASEADDR + offset, StartDataBuf);
            cnt++;
        }
        else if (JPGD_REG_ENDADD == offset)
        {
            PRN_SCENE(pJpegHandle->pScenFile,JPGD_REG_BASEADDR + offset, EndDataBuf);
            cnt++;
        }
        else
        {
            PRN_SCENE(pJpegHandle->pScenFile,JPGD_REG_BASEADDR + offset, pJpegHandle->s32RegData[cnt]);
            cnt++;
        }
    }

    return;
}

/*****************************************************************************
* func            : JPEG_HDEC_OutScenData
* description   : get the scen data
                          CNcomment: 获取现场数据 CNend\n
* param[in]    : cinfo.                 CNcomment:解码对象         CNend\n
* param[in]     : pStreamStartBuf.       CNcomment:码流起始地址     CNend\n
* param[in]     : pStreamEndBuf.         CNcomment:码流结束地址     CNend\n
* param[in]     : pData.                 CNcomment:数据地址         CNend\n
* param[in]     : s32DataSize.           CNcomment:数据大小         CNend\n
* param[in]     : bStartFirst            CNcomment:第一次启动解码   CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_OutScenData(const struct jpeg_decompress_struct *cinfo, HI_U32 StartStreamDdr, HI_U32 EndStreamDdr, HI_CHAR* pDataVir, HI_U64 DataSize)
{
    HI_U32 data = 0;
    HI_S32 offset = 0;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);
    JPEG_API_MODULE_DEFINE_HANDLE();

    JPEG_HDEC_GetScenData(cinfo);
    JPEG_HDEC_PrintScenData(cinfo,StartStreamDdr,EndStreamDdr);

    SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
    SCEN_PRINT(pJpegHandle->pScenFile,"    the dec data \n");
    SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
    SCEN_PRINT(pJpegHandle->pScenFile,"======================= data begin ==================\n\n");

    for (offset = 0; offset < DataSize; offset += 4)
    {
       data = (pDataVir[offset + 3] << 24) | (pDataVir[offset + 2] << 16) | (pDataVir[offset + 1] << 8) | (pDataVir[offset]);
       PRN_SCENE(pJpegHandle->pScenFile,(HI_U32)(StartStreamDdr + offset),data);
    }
#if 0
    if (HI_TRUE != bStartFirst)
    {
      PRN_SCENE(pJpegHandle->pScenFile,JPGD_REG_BASEADDR + 4,0x00000001);
    }
    else
#endif
    {
      PRN_SCENE(pJpegHandle->pScenFile,JPGD_REG_BASEADDR,0x00000001);
    }

    SCEN_PRINT(pJpegHandle->pScenFile,"\n======================= data end ==================\n");

    return;
}

HI_VOID JPEG_HDEC_SetSaveScen(const struct jpeg_decompress_struct *cinfo, HI_U32 StartStreamDdr, HI_U32 EndStreamDdr, HI_CHAR* pDataVir, HI_U64 DataSize)
{
    JPEG_HDEC_OpenScenFile(cinfo);

    JPEG_HDEC_OutScenData(cinfo,StartStreamDdr,EndStreamDdr,pDataVir,DataSize);

    JPEG_HDEC_CloseScenFile(cinfo);

    return;
}
#endif
#endif

#endif
