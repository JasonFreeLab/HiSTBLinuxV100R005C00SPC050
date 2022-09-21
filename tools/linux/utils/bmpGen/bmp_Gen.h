/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : bmp_gen.h
Version		    : Initial Draft
Author		    :
Created		    : 2013/06/20
Description	    : 生成bmp图片头文件
Function List 	:


History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file
******************************************************************************/

#ifndef __BMP_GEN_H__
#define __BMP_GEN_H__


/*********************************add include here******************************/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "bmpGenerator.h"


/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
	   extern "C"
	{
#endif
#endif /* __cplusplus */


			/***************************** Macro Definition ******************************/


            /*************************** Enum Definition ****************************/

            /*************************** Structure Definition ****************************/

			/** 位图头文件结构，注意字节对齐情况 **/
			/** __attribute__ ((packed)) 的作用就是告诉编译器取消结构
			 ** 在编译过程中的优化对齐,按照实际占用字节数进行对齐，是
			 ** GCC特有的语法。这个功能是跟操作系统没关系，跟编译器有关
			 **/
			typedef struct	tagBITMAPFILEHEADER
			{
				HI_U16 u16Type; 		    /** 文件类型，设为0x4D42                   **/
				HI_U32 u32Size; 		    /** 文件大小，像素数据加上头文件大小sizeof **/
				HI_U16 u16Reserved1;		/** 保留位                                 **/
				HI_U16 u16Reserved2;		/** 保留位                                 **/
				HI_U32 u32OffBits;			/** 文件头到实际位图数据的偏移量           **/
			}__attribute__((packed)) BMP_BMFHEADER_S;

			/** 位图信息头结构 **/
			typedef  struct tagBITMAPINFOHEADER{
				HI_U32 u32Size; 		    /** 位图信息头的大小,sizeof(BMP_BMIHEADER_S) 		**/
				HI_U32 u32Width;			/** 图像宽度                                 		**/
				HI_U32 u32Height;			/** 图像高度                                 		**/
				HI_U16 u32Planes;			/** 位图位面数，设为1                        		**/
				HI_U16 u32PixbitCount;	    /** 每个像素的位数，如RGB8888就是32          		**/
				HI_U32 u32Compression;     /** 位图数据压缩类型，设为0，表示不会压缩    		**/
				HI_U32 u32SizeImage;		/** 位图数据大小，设为0                      		**/
				HI_U32 u32XPelsPerMeter;	/** 位图水平分辨率，与图像宽度相同           		**/
				HI_U32 u32YPelsPerMeter;	/** 位图垂直分辨率，与图像高度相同           		**/
				HI_U32 u32ClrUsed;		    /** 说明位图实际使用的彩色表中的颜色索引数，设为0   **/
				HI_U32 u32ClrImportant;    /** 对图像显示很重要的颜色索引数，设为0            **/
			} BMP_BMIHEADER_S;

			/********************** Global Variable declaration **************************/
			/** the bytes of a line gernerated **/
			HI_U32 u32BmpStride;

			/******************************* API declaration *****************************/

			/*****************************************************************************
			* func			: BMP_DATA_GetData
			* description	: 提取出指定物理内存中的数据
			* param[in] 	: NA
			* retval		: NA
			* others:		: NA
			*****************************************************************************/
			HI_VOID * BMP_DATA_GetData(HI_VOID);

			/*****************************************************************************
			* func			: BMP_DATA_GenBmp
			* description	: 生成位图文件
			* param[in] 	: pDataAddr  输入的数据地址
			* retval		: NA
			* others:		: NA
			*****************************************************************************/
			HI_BOOL BMP_DATA_GenBmp(HI_VOID *);


            void BMP_DATA_GenYuv(void);



#ifdef __cplusplus

#if __cplusplus

		}
#endif
#endif /* __cplusplus */


#endif /* __BMP_GEN_H__*/
