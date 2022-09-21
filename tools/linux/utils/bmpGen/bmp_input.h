/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : bmp_input.h
Version		    : Initial Draft
Author		    : 
Created		    : 2013/06/20
Description	    : 获取输入参数信息头文件
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file      	
******************************************************************************/


#ifndef __BMP_INPUT_H__
#define __BMP_INPUT_H__


/*********************************add include here******************************/
#include <stdio.h>
#include <stdlib.h>

#include "bmpGenerator.h"


/*****************************************************************************/
	
	
#ifdef __cplusplus
#if __cplusplus
	   extern "C" 
	{
#endif
#endif /* __cplusplus */
	
	
			/***************************** Macro Definition ******************************/


			#define BMP_MAX_BMP_WIDTH      8192
			#define BMP_MAX_BMP_HIGHT      8192

			/*************************** Enum Definition ****************************/

			typedef  enum  hiBMP_INPUT_TYPE_E 
			{
				BMP_MEM_ADDR = 1,
				BMP_MEM_WIDTH,
				BMP_MEM_HIGHT,
				BMP_MEM_STRIDE,
				BMP_PIX_FMT
			} BMP_INPUT_TYPE;

			/*************************** Structure Definition ****************************/
			/********************** Global Variable declaration **************************/


			/******************************* API declaration *****************************/


			/****************************************************************************
			* func			: BMP_INPUT_getInput
			* description	: CNcomment: 获取输入的参数 CNend\n
			* param[in] 	: NA
			* retval		: HI_SUCCESS
			* retval		: HI_FAILURE
			* others:		: NA
			*****************************************************************************/
			HI_BOOL BMP_INPUT_getInput(HI_U32, HI_PCHAR *);

			/*****************************************************************************
			* func			: BMP_INPUT_isValid
			* description	: 验证用户输入的有效性
			* param[in] 	: eInputType   输入类型以及相应的值
			* param[in] 	: pInput
			* retval		: NA
			* others:		: NA
			*****************************************************************************/
			HI_BOOL BMP_INPUT_isValid(BMP_INPUT_TYPE, HI_PCHAR);

		 

#ifdef __cplusplus
			
#if __cplusplus
		   
		}
#endif
#endif /* __cplusplus */
		

#endif /* __BMP_INPUT_H__*/
