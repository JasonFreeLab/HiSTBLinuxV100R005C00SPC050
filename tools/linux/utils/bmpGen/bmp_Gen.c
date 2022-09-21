/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : bmp_gen.c
Version		    : Initial Draft
Author		    :
Created		    : 2013/06/20
Description	    : generate bmp picture
                  CNcomment: 生成位图图片 CNend\n
Function List 	:


History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file
******************************************************************************/


/*********************************add include here******************************/

#include "bmp_Gen.h"
#include "hi_common.h"

/***************************** Macro Definition ******************************/
#define CONFIG_SAVE_FILE_NAME           "./save_yuv"

#define TEST_TRACE( fmt, args... )\
        do { \
                fprintf(stderr,fmt, ##args );\
        } while (0)

#define FILE_WRITE( file,fmt, args... )\
do { \
        fprintf(file,fmt, ##args );\
} while (0)

/******************** to see which include file we want to use***************/



/*************************** Structure Definition ****************************/
typedef enum
{
    SAVE_PF_YUV400 = 0,
    SAVE_PF_YUV420,
    SAVE_PF_YUV422_21,
    SAVE_PF_YUV422_12,
    SAVE_PF_YUV444,
    SAVE_PF_BUTT
}SAVE_PF_E;


/********************** Global Variable declaration **************************/

/** the defination of initial address of memory **/
HI_U32  g_u32BmpMemAddr;

/** the width of memory **/
HI_U32 g_u32BmpMemWidth;

/** the hight of memory **/
HI_U32 g_u32BmpMemHight;

/** the stride of memory **/
HI_U32 g_u32BmpMemStride;

/** the pixel format **/
BMP_PIX_FMTS g_eBmpPixFmt;

/** the name of bmp file finally generated  **/
HI_PCHAR g_pBmpFileName;



SAVE_PF_E gs_enFmt = SAVE_PF_BUTT;
char* gs_pYVir = NULL;
char* gs_pCbCrVir = NULL;
unsigned int gs_YWidth  = 0;
unsigned int gs_YHeight = 0;
unsigned int gs_YStride = 0;

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/


/*****************************************************************************
* func			: BMP_DATA_GetData
* description	: 提取出指定物理内存中的数据
* param[in] 	: NA
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID * BMP_DATA_GetData(HI_VOID)
{
	    HI_U32 map_Size, stride, line, pixel;
	    HI_PCHAR pData, pSou;
        HI_PCHAR pVirt;
#ifndef BMPGEM_SMMU_SUPPORT
        HI_S32 fd_mem = 0;
        HI_S32 s32align = 0;
        HI_U32 pTmpPhyAddr = 0;
#endif

        map_Size = g_u32BmpMemStride * g_u32BmpMemHight;
        if (0 == map_Size)
        {
            BMPGEN_TRACE("============= %s : %s : %d \n",__FILE__,__FUNCTION__,__LINE__);
		}

#ifdef BMPGEM_SMMU_SUPPORT
        pVirt = HI_MMZ_Map(g_u32BmpMemAddr,0);
#else
	    /** 打开内存文件 **/
	    fd_mem = open("/dev/mem", O_RDWR);
	    if(fd_mem < 0)
		{
	         BMPGEN_TRACE("open dev mem failed!\n");
	         return HI_NULL_PTR;
	    }

		/**
		 **使用mem or mmz设备，映射要按照4K对齐
		 **/
		/**
		 **0x1000 = 4096 = 4K，也就是地址末尾三位要为0
		 **/
		s32align = g_u32BmpMemAddr & 0xFFF;
		if(0!=s32align)
		{

		   pTmpPhyAddr = (HI_U32)(g_u32BmpMemAddr & 0xFFFFF000);
		   pVirt = (HI_PCHAR)mmap(NULL, map_Size, PROT_READ|PROT_WRITE, MAP_SHARED, fd_mem, pTmpPhyAddr);
           /** 对齐后的映射地址加上偏移就是实际物理地址的虚拟地址**/
		   pVirt = pVirt + (g_u32BmpMemAddr - pTmpPhyAddr);
		}
		else
		{
	        pVirt = (HI_PCHAR)mmap(NULL, map_Size, PROT_READ|PROT_WRITE, MAP_SHARED, fd_mem, g_u32BmpMemAddr);
		}
		if(MAP_FAILED == pVirt)
	    {
	        perror("mmap");
	        BMPGEN_TRACE("map to virtual mem failed!\n");
	        return HI_NULL_PTR;
	    }
#endif

	    /** 调用malloc分配指定大小的内存空间，确定每行像素的位数 **/
	    stride = g_u32BmpMemWidth * 3;
	    u32BmpStride = (stride&0x3) ? ((stride&0xfffc) + 4) : stride;

		//BMPGEN_TRACE("u32BmpStride is %d !\n", u32BmpStride);

		pData = (HI_PCHAR)malloc(u32BmpStride * g_u32BmpMemHight);
	    memset(pData, 0, u32BmpStride * g_u32BmpMemHight);

	    if(pData == HI_NULL_PTR)
	    {
	        BMPGEN_TRACE("######%s,memory allocation fail!\n", __FUNCTION__);
	        return HI_NULL_PTR;
	    }

	    /** 定义一个指针，并让它指向指定物理内存的最后一行的首地址 **/
	    pSou = pVirt + map_Size - g_u32BmpMemStride;

	    if(pSou == HI_NULL_PTR)
	    {
	        BMPGEN_TRACE("######BMP_DATA_GetData(),memory allocation fail!\n");
	        return HI_NULL_PTR;
	    }

	    HI_U8 * pB8 ;             /** = (HI_U8 *)pSou;     **/
	    HI_U16 * pB16;            /** = (HI_U16 *)pSou;    **/
	    HI_U32 * pB32;            /** = (HI_U32 *)pSou;     **/
	    HI_U8 * pDb8 = (HI_U8*)pData;
	    HI_U16 u16Data;

	    /** 将每一行中的填充数据清除，并把数据DWORD对齐 **/
	    /** 把处理后的行写入到分配的内存空间中去        **/
	    switch(g_eBmpPixFmt)
		{
	        case BMP_FMT_RGB565:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                         pB16 = (HI_U16 *)pSrc;
                         pSrc += 2;
                         *pDb8++ = (*pB16 & 0x1F) << 3;
                         *pDb8++ = ((*pB16 >> 5) & 0x3F) << 2;
                         *pDb8++ = ((*pB16 >> 11) &0x1F) << 3;
                    }
                }
	            break;
	        case BMP_FMT_BGR565:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                         pB16 = (HI_U16 *)pSrc;
                         pSrc += 2;
                         *pDb8++ = ((*pB16 >> 11) &0x1F) << 3;
                         *pDb8++ = ((*pB16 >> 5) & 0x3F) << 2;
                         *pDb8++ = (*pB16 & 0x1F) << 3;
                    }
                }
	            break;
	        case BMP_FMT_ARGB4444:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                        pB16 = (HI_U16 *)pSrc;
                        pSrc += 2;
                        *pDb8++ = (*pB16 & 0xF) << 4;
                        *pDb8++ = ((*pB16 >> 4) & 0xF) << 4;
                        *pDb8++ = ((*pB16 >> 8) & 0xF) << 4;
                    }
                }
	            break;
	        case BMP_FMT_ARGB1555:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                        u16Data = *(HI_U16 *)pSrc;
                        pSrc += 2;
                        *pDb8++ = (u16Data & 0x1F) << 3;
                        *pDb8++ = ((u16Data >> 5) & 0x1F) << 3;
                        *pDb8++ = ((u16Data >> 10) & 0x1F) << 3;
                    }
                }
	            break;
	        case BMP_FMT_ABGR1555:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                        u16Data = *(HI_U16 *)pSrc;
                        pSrc += 2;
                        *pDb8++ = ((u16Data >> 10) & 0x1F) << 3;
                        *pDb8++ = ((u16Data >> 5) & 0x1F) << 3;
                        *pDb8++ = (u16Data & 0x1F) << 3;
                    }
                }
	            break;
	        case BMP_FMT_RGB888:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                        pB8 = (HI_U8 *)pSrc;
                        pSrc += 3;
                        *pDb8++ = *pB8++;
                        *pDb8++ = *pB8++;
                        *pDb8++ = *pB8++;
                    }
                }
	            break;
	        case BMP_FMT_BGR888:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                        pB8 = (HI_U8 *)pSrc;
                        pDb8[0] = pB8[2];
                        pDb8[1] = pB8[1];
                        pDb8[2] = pB8[0];
                        pSrc += 3;
                        pDb8 += 3;
                    }
                }
	            break;
	        case BMP_FMT_ARGB8888:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                        pB32 = (HI_U32 *)pSrc;
                        pSrc += 4;
                        *pDb8++ = *pB32 & 0xFF;
                        *pDb8++ = (*pB32 >> 8) & 0xFF;
                        *pDb8++ = (*pB32 >> 16) & 0xFF;
                    }
                }
	            break;
	        case BMP_FMT_ABGR8888:
	            for(line = 0; line < g_u32BmpMemHight; line++)
                {
                    HI_U8 *pSrc;
                    pSrc =  (HI_U8 *)pSou - line * g_u32BmpMemStride;

                    pDb8 = (HI_U8 *)pData + line * u32BmpStride;
                    for(pixel = 0; pixel < g_u32BmpMemWidth; pixel++)
                    {
                        pB32 = (HI_U32 *)pSrc;
                        pSrc += 4;
                        *pDb8++ = (*pB32 >> 16) & 0xFF;
                        *pDb8++ = (*pB32 >> 8) & 0xFF;
                        *pDb8++ = *pB32 & 0xFF;
                    }
                }
	            break;
	         default:
	                   return NULL;
	    }

#ifdef BMPGEM_SMMU_SUPPORT
        HI_MMZ_Unmap(g_u32BmpMemAddr);
#else
	    close(fd_mem);
#endif

        #if 0
	    BMPGEN_TRACE("\n=====================================================================\n");
	    BMPGEN_TRACE("Extract Data Complete!\n");
        #endif

		/** 返回分配的内存空间的首地址 **/
		return pData;


}

/*****************************************************************************
* func			: BMP_DATA_GenBmp
* description	: 生成位图文件
* param[in] 	: pDataAddr  输入的数据地址
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_BOOL BMP_DATA_GenBmp(HI_VOID * pDataAddr)
{


	    /** 定义一个位图文件头结构*/
	    BMP_BMFHEADER_S sBmpHeader;

	    /** 给每一个数据项赋值*/
	    sBmpHeader.u16Type = 0x4D42;
	    sBmpHeader.u32Size = u32BmpStride * g_u32BmpMemHight\
			                 + sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S);
	    sBmpHeader.u16Reserved1 = 0;
	    sBmpHeader.u16Reserved2 = 0;
	    sBmpHeader.u32OffBits = sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S); //+ 2;//

		#if 0
	    BMPGEN_TRACE("sBmpHeader.u16Type:   %c\n", sBmpHeader.u16Type);
	    BMPGEN_TRACE("sBmpHeader.u32Size:   %d\n", sBmpHeader.u32Size);
	    BMPGEN_TRACE("sBmpHeader.u32OffBits:%d\n", sBmpHeader.u32OffBits);
	    #endif

	    /** 定义一个位图信息头结构*/
	    BMP_BMIHEADER_S sBmpInfoHeader;

	    /** 给每一个数据项赋值*/
	    sBmpInfoHeader.u32Size          = sizeof(BMP_BMIHEADER_S);
	    sBmpInfoHeader.u32Width         = g_u32BmpMemWidth;
	    sBmpInfoHeader.u32Height        = g_u32BmpMemHight;
	    sBmpInfoHeader.u32Planes        = 1;
	    sBmpInfoHeader.u32PixbitCount   = 24;
	    sBmpInfoHeader.u32Compression   = 0;
	    sBmpInfoHeader.u32SizeImage     = 0;
	    sBmpInfoHeader.u32XPelsPerMeter = g_u32BmpMemWidth;
	    sBmpInfoHeader.u32YPelsPerMeter = g_u32BmpMemHight;
	    sBmpInfoHeader.u32ClrUsed       = 256;
	    sBmpInfoHeader.u32ClrImportant  = 0;

		#if 0
	    BMPGEN_TRACE("sBmpInfoHeader.u32Size:       %d\n", sBmpInfoHeader.u32Size);
	    BMPGEN_TRACE("sBmpInfoHeader.u32Width:      %d\n", sBmpInfoHeader.u32Width);
	    BMPGEN_TRACE("sBmpInfoHeader.u32Height:     %d\n", sBmpInfoHeader.u32Height);
	    BMPGEN_TRACE("sBmpInfoHeader.u32PixbitCount:%d\n", sBmpInfoHeader.u32PixbitCount);
	    BMPGEN_TRACE("sBmpInfoHeader.u32SizeImage:  %d\n", sBmpInfoHeader.u32SizeImage);
        #endif

	    /** 打开一个文件，把位图文件头，位图信息头，调色板以及位图数据写入*/
	    FILE * file = fopen(g_pBmpFileName, "wb");
		if(NULL==file)
		{
		    BMPGEN_TRACE("============= g_pBmpFileName = %s \n",g_pBmpFileName);
			BMPGEN_TRACE("===== please creat %s file \n",g_pBmpFileName);
		    BMPGEN_TRACE("============= open file failure \n");
		}

	    /** write the bmp file header **/
	    /** HI_S32 size = write(fd_file, &sBmpHeader, sizeof(BMP_BMFHEADER_S)); **/
	    int size = fwrite(&sBmpHeader, 1, sizeof(BMP_BMFHEADER_S), file);
	    if(size == -1)
	    {
	        BMPGEN_TRACE("Write BMP_BMFHEADER_S fail!\n");
	        return HI_FALSE;
	    }

		/** write the bmp infomation header **/
	    size = fwrite(&sBmpInfoHeader, 1, sizeof(BMP_BMIHEADER_S), file);
	    if(size == -1)
	    {
	        BMPGEN_TRACE("Write BMP_BMIHEADER_S fail!\n");
	        return HI_FALSE;
	    }

	    size = fwrite(pDataAddr, 1, u32BmpStride * g_u32BmpMemHight, file);
	    if(size == -1)
	    {
	        BMPGEN_TRACE("Write BMP DATA fail!\n");
	        return HI_FALSE;
	    }

	    /** 关闭文件 **/
	    fclose(file);

	    /** 释放分配的内存 **/
	    free(pDataAddr);

		#if 0
	    BMPGEN_TRACE("Generate bmp file success!\n");
		BMPGEN_TRACE("=====================================================================\n");
		#endif

	    return HI_TRUE;

}


void BMP_DATA_GenYuv(void)
{
   FILE* pOutFile = NULL;
   FILE* pHdrFile = NULL;
   unsigned int Row = 0;
   unsigned int Col = 0;

   HI_CHAR* pTmp = NULL;
   char pTmpCbCr[10000];

   unsigned int CbCrWidth  = 0;
   unsigned int CbCrHeight = 0;
   unsigned int CbCrStride = 0;

   static char PicInforName[256] = {'\0'};
   static char SaveFileName[256] = {'\0'};


   sprintf(PicInforName, "%s%s", CONFIG_SAVE_FILE_NAME, ".hdr");
   sprintf(SaveFileName, "%s%s", CONFIG_SAVE_FILE_NAME, ".yuv");

   TEST_TRACE("\n=========================================================\n");

   /** save picture information **/
   pHdrFile = fopen(PicInforName, "wb+");
   if (NULL == pHdrFile)
   {
       TEST_TRACE("===== open %s failure\n",PicInforName);
   }

   switch (gs_enFmt)
   {
      case SAVE_PF_YUV400:
         FILE_WRITE(pHdrFile, "format = \"Y\" ;\n");
         break;
      case SAVE_PF_YUV420:
         CbCrStride = gs_YStride;
         CbCrWidth  = gs_YWidth  >> 1;
         CbCrHeight = gs_YHeight >> 1;
         FILE_WRITE(pHdrFile, "format = \"YUV420\" ;\n");
         break;
      case SAVE_PF_YUV422_12:
         CbCrStride = gs_YStride << 1;
         CbCrWidth  = gs_YWidth;
         CbCrHeight = gs_YHeight >> 1;
         FILE_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
         break;
      case SAVE_PF_YUV422_21:
         CbCrStride = gs_YStride;
         CbCrWidth  = gs_YWidth  >> 1;
         CbCrHeight = gs_YHeight;
         FILE_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
         break;
      case SAVE_PF_YUV444:
         CbCrStride = gs_YStride << 1;
         CbCrWidth  = gs_YWidth;
         CbCrHeight = gs_YHeight;
         FILE_WRITE(pHdrFile, "format = \"YUV444\" ;\n");
         break;
      default:
         TEST_TRACE("format is unknow ;\n");
         break;
   }

   FILE_WRITE(pHdrFile, "offset = 0 ;\n");
   FILE_WRITE(pHdrFile, "width = %d ;\n", gs_YWidth);
   FILE_WRITE(pHdrFile, "height = %d ;\n", gs_YHeight);
   FILE_WRITE(pHdrFile, "framerate = 50 ;\n");
   FILE_WRITE(pHdrFile, "loop = 1 ;\n");

   fclose(pHdrFile);


   /** save yuv data **/
   pOutFile = fopen(SaveFileName, "wb+");
   if (NULL == pOutFile)
   {
       TEST_TRACE("===== open %s failure\n",SaveFileName);
       return;
   }

   if (0 == gs_YWidth)
   {
       fclose(pOutFile);
       goto ERR_EXIT;
   }

   pTmp = gs_pYVir;

   for (Row = 0; Row < gs_YHeight; Row++)
   {
      fwrite(pTmp, gs_YWidth, 1, pOutFile);
      pTmp += gs_YStride;
   }

   if (0 == CbCrWidth)
   {
       goto SUCCESS_EXTI;
   }

   pTmp = gs_pCbCrVir;

   for ( Row = 0; Row < CbCrHeight; Row ++ )
   {

      for (Col = 0; Col < CbCrWidth; Col++ )
      {
         pTmpCbCr[Col] = pTmp[2 * Col + 1];
      }

      fwrite(pTmpCbCr, CbCrWidth, 1, pOutFile );

      pTmp += CbCrStride;
   }

   pTmp = gs_pCbCrVir;

   for ( Row = 0; Row < CbCrHeight; Row ++ )
   {
      for (Col = 0; Col < CbCrWidth; Col++ )
      {
         pTmpCbCr[Col] = pTmp[2 * Col + 0];
      }

      fwrite(pTmpCbCr, CbCrWidth, 1, pOutFile);

      pTmp += CbCrStride;
   }

SUCCESS_EXTI:
   if (NULL != pOutFile)
   {
     fclose(pOutFile);
     pOutFile = NULL;
   }

   TEST_TRACE("save yuv data success\n");
   TEST_TRACE("YVir = 0x%x, CbCrVir = 0x%x, Format = %d\n",(unsigned int)gs_pYVir,(unsigned int)gs_pCbCrVir,gs_enFmt);
   TEST_TRACE("YWidth = %d, YHeight = %d, YStride = %d\n",gs_YWidth,gs_YHeight,gs_YStride);
   TEST_TRACE("CbCrWidth = %d, CbCrHeight = %d, CbCrStride = %d\n",CbCrWidth,CbCrHeight,CbCrStride);
   TEST_TRACE("=========================================================\n");

   return;

ERR_EXIT:

   if (NULL != pOutFile)
   {
     fclose(pOutFile);
     pOutFile = NULL;
   }

   TEST_TRACE("save yuv data failure\n");
   TEST_TRACE("=========================================================\n");

   return;
}

