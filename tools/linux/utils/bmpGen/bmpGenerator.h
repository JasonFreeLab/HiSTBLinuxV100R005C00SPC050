/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : bmpgenerator.h
Version		    : Initial Draft
Author		    : 
Created		    : 2013/06/20
Description	    : 输入头文件
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file      	
******************************************************************************/


#ifndef __BMPGENERATOR_H__
#define __BMPGENERATOR_H__


/*********************************add include here******************************/

#include "hi_type.h"

/*****************************************************************************/
	
	
#ifdef __cplusplus
#if __cplusplus
	   extern "C" 
	{
#endif
#endif /* __cplusplus */
	
	
			/***************************** Macro Definition ******************************/
			#define BMPGEN_TRACE( fmt, args... )\
		    do { \
		            fprintf(stderr,fmt, ##args );\
		    } while (0)
            /*************************** Enum Definition ****************************/

			/** define all pixel formats supported by application **/
			typedef  enum  hiBMP_PIX_FMT_E 
			{
				BMP_FMT_RGB565    = 1,
				BMP_FMT_BGR565,
			    BMP_FMT_ARGB4444,
			   	BMP_FMT_ARGB1555,
			   	BMP_FMT_ABGR1555,
			   	BMP_FMT_RGB888,
			   	BMP_FMT_BGR888,
			    BMP_FMT_ARGB8888,
			    BMP_FMT_ABGR8888,
			    BMP_FMT_NONE
			} BMP_PIX_FMTS;

			/*************************** Structure Definition ****************************/
			/********************** Global Variable declaration **************************/
			/** the declareof initial address of memory  **/
			extern HI_U32  g_u32BmpMemAddr;
			
			/** the width of memory **/
			extern HI_U32 g_u32BmpMemWidth;
			
			/** the hight of memory **/
			extern HI_U32 g_u32BmpMemHight;
			
			/** the stride of memory **/
			extern HI_U32 g_u32BmpMemStride;
			
			/** the pixel format **/
			extern BMP_PIX_FMTS g_eBmpPixFmt;
			
			/** the name of bmp file finally generated  **/
			extern HI_PCHAR g_pBmpFileName;

			/******************************* API declaration *****************************/


#ifdef __cplusplus
			
#if __cplusplus
		   
		}
#endif
#endif /* __cplusplus */
		

#endif /* __BMPGENERATOR_H__*/
