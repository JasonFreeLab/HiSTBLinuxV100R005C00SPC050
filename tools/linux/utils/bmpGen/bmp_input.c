/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : Bmp_input.c
Version		    : Initial Draft
Author		    : 
Created		    : 2013/06/20
Description	    : 
                  CNcomment: 获取输入参数信息 CNend\n
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file      	
******************************************************************************/


/*********************************add include here******************************/

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <stdlib.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 
#include "bmp_input.h"
#include "hifb.h"

 
/***************************** Macro Definition ******************************/


/******************** to see which include file we want to use***************/



/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

/** the initial address of memory **/
HI_U32	g_u32BmpMemAddr;

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

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/


/*****************************************************************************
* func			: str2enum
* description	: 用来把像素格式字符串转化成像素格式枚举
* param[in] 	: pString
* retval		: NA
* others:		: NA
*****************************************************************************/
BMP_PIX_FMTS str2enum(HI_PCHAR pString)
{
        BMP_PIX_FMTS input; 
		if(!strncmp("RGB565", pString, strlen("RGB565")>strlen(pString)?strlen("RGB565"):strlen(pString)))
		{
		  input = BMP_FMT_RGB565;
		}
		else if(!strncmp("BGR565", pString, strlen("BGR565")>strlen(pString)?strlen("BGR565"):strlen(pString)))
		{
		  input = BMP_FMT_BGR565;
		}
        else if(!strncmp("ARGB4444", pString, strlen("ARGB4444")>strlen(pString)?strlen("ARGB4444"):strlen(pString)))
		{
            input = BMP_FMT_ARGB4444;
        }
        else if(!strncmp("ARGB1555", pString, strlen("ARGB1555")>strlen(pString)?strlen("ARGB1555"):strlen(pString)))
		{
            input = BMP_FMT_ARGB1555;
        }
        else if(!strncmp("ABGR1555", pString, strlen("ABGR1555")>strlen(pString)?strlen("ABGR1555"):strlen(pString)))
		{
            input = BMP_FMT_ABGR1555;
        }
        else if(!strncmp("RGB888", pString, strlen("RGB888")>strlen(pString)?strlen("RGB888"):strlen(pString)))
        {
            input = BMP_FMT_RGB888;
        }
        else if(!strncmp("BGR888", pString, strlen("BGR888")>strlen(pString)?strlen("BGR888"):strlen(pString)))
        {
            input = BMP_FMT_BGR888;
        }
        else if(!strncmp("ARGB8888", pString, strlen("ARGB8888")>strlen(pString)?strlen("ARGB8888"):strlen(pString)))
	    {
            input = BMP_FMT_ARGB8888;
        }
        else if(!strncmp("ABGR8888", pString, strlen("ABGR8888")>strlen(pString)?strlen("ABGR8888"):strlen(pString)))
	    {
            input = BMP_FMT_ABGR8888;
        }
        else
		{
            input = BMP_FMT_NONE;
        }
        return input;
		
}

/*****************************************************************************
* func			: BMP_INPUT_isValid
* description	: 验证用户输入的有效性
* param[in] 	: eInputType   输入类型以及相应的值
* param[in] 	: pInput
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_BOOL BMP_INPUT_isValid(BMP_INPUT_TYPE eInputType, HI_PCHAR  pInput)
{

    HI_U32 input;
    BMP_PIX_FMTS ePixFmt;
    
	switch(eInputType)
	{
		case BMP_MEM_ADDR:
			/** 将字符串转换成无符号长整型数 **/
			input = strtoul(pInput, (char **)NULL, 16);
			return HI_TRUE;
			
		case BMP_MEM_WIDTH:
            input = atoi(pInput);
			if(input > BMP_MAX_BMP_WIDTH || input<= 0)
            {
                BMPGEN_TRACE("\n===========================================================\n");
                BMPGEN_TRACE("The width should between 0 and %d!\n", BMP_MAX_BMP_WIDTH);
				BMPGEN_TRACE("===========================================================\n");
				return HI_FALSE;
            }
			return HI_TRUE;

		case BMP_MEM_HIGHT:

            input = atoi(pInput);
			if(input > BMP_MAX_BMP_HIGHT || input <= 0)
            {         
				BMPGEN_TRACE("\n===========================================================\n");
                BMPGEN_TRACE("The height should between 0 and %d!\n", BMP_MAX_BMP_HIGHT);
				BMPGEN_TRACE("===========================================================\n");
			    return HI_FALSE;
            }
			return HI_TRUE;

		case BMP_MEM_STRIDE:

            input = atoi(pInput);
			if(input < g_u32BmpMemWidth)
            {         
				BMPGEN_TRACE("\n===========================================================\n");
                BMPGEN_TRACE("The stride should be greater than memory width!\n");
				BMPGEN_TRACE("===========================================================\n");
				return HI_FALSE;
            }
			return HI_TRUE;

		case BMP_PIX_FMT:
            
            ePixFmt = str2enum(pInput);
			if(ePixFmt == BMP_FMT_NONE)
            {            
				BMPGEN_TRACE("\n===========================================================\n");
                BMPGEN_TRACE("The pixel format should be as follow:RGB565,ARGB4444,ARGB1555,RGB888,ARGB8888!\n");  
                BMPGEN_TRACE("===========================================================\n");
				return HI_FALSE;
            }
			return HI_TRUE;

		default:
			return HI_FALSE;
			
	}
	
	
}



/*****************************************************************************
* func			: BMP_INPUT_getInput
* description	: 提示、接受并处理用户输入
* param[in] 	: u32Args   用户输入的指定物理内存地址、高度、宽度、
                            行间距和像素格式的字符串
* param[in] 	: pArgv
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_BOOL BMP_INPUT_getInput(HI_U32 u32Args, HI_PCHAR * pArgv)
{
		
	    if (3 == u32Args)
	    {/** 直接导出fb图层内容的 **/

				HI_PCHAR layerDevName = malloc(40);
				HI_S32 layerNum       = atoi(pArgv[1]);     /** 导出哪个图层的数据  **/
				if(layerNum < 0 || layerNum > 3)
				{
					BMPGEN_TRACE("The max layer num is 3!\n");
					return HI_FALSE;
				}
				
				sprintf(layerDevName,"/dev/fb%d", layerNum);

				HI_S32 fd = open(layerDevName, O_RDWR, 0);
				if ( fd < 0 )
				{
					BMPGEN_TRACE("cannot open %s!\n", layerDevName);
					return HI_FALSE;
				}
				struct fb_fix_screeninfo fix;
				struct fb_var_screeninfo var;

				if(ioctl(fd, FBIOGET_FSCREENINFO, &fix) < 0)
				{
					BMPGEN_TRACE("cannot get the fb_fix_screeninfo!\n");
					return HI_FALSE;
				}

				g_u32BmpMemAddr = (HI_U32)fix.smem_start;
				g_u32BmpMemStride = fix.line_length;
				if(ioctl(fd, FBIOGET_VSCREENINFO, &var) < 0)
				{
					BMPGEN_TRACE("cannot get the fb_var_screeninfo!\n");
					return HI_FALSE;
				}

				g_u32BmpMemWidth = var.xres;
				g_u32BmpMemHight = var.yres;

				HI_U32 transp = var.transp.length;
				HI_U32 red    = var.red.length;
				HI_U32 green  = var.green.length;
				/** HI_U32 blue  = var.blue.length; **/

				if( 1 == transp)
				{
					g_eBmpPixFmt = BMP_FMT_ARGB1555;
				}
				else if(4 == transp)
				{
					g_eBmpPixFmt = BMP_FMT_ARGB4444;
				}
				else if(8 == transp)
				{
					g_eBmpPixFmt = BMP_FMT_ARGB8888;
				}
				else if(6 == green)
				{
					g_eBmpPixFmt = BMP_FMT_RGB565;
				}
				else if(8 == red && 0 == transp)
				{
					g_eBmpPixFmt = BMP_FMT_RGB888;
				}
				else
				{
					BMPGEN_TRACE("donot support this color formate!\n");
					return HI_FALSE;
				}

				close(fd);
				free(layerDevName);

				g_pBmpFileName = pArgv[2];

				return HI_TRUE;
				
    	}


	   	HI_BOOL isValid = BMP_INPUT_isValid(BMP_MEM_ADDR, pArgv[1]);
		if(isValid)
	    {/** 判断输入的地址是否正确 **/
	        g_u32BmpMemAddr = strtoul(pArgv[1], (char **)NULL, 16);
	    }
		else
		{
	        return HI_FALSE;  
		}
		
		isValid = BMP_INPUT_isValid(BMP_MEM_WIDTH, pArgv[2]);
		if(isValid)
		{
		    /** 把width赋给u32BmpMemWidth **/
	        g_u32BmpMemWidth = atoi(pArgv[2]);
		}
		else
		{
	        return HI_FALSE;
		}
		isValid = BMP_INPUT_isValid(BMP_MEM_HIGHT, pArgv[3]);
		if(isValid)
		{
			/** 把hight赋给u32BmpMemHight **/
	        g_u32BmpMemHight = atoi(pArgv[3]);
		}
		else
		{
	        return HI_FALSE;
		}
		isValid = BMP_INPUT_isValid(BMP_MEM_STRIDE, pArgv[4]);
		if(isValid)
		{
			/** 把stride赋给u32BmpMemStride **/
	        g_u32BmpMemStride = atoi(pArgv[4]);
		}
		else
		{
	        return HI_FALSE;
		}

		isValid = BMP_INPUT_isValid(BMP_PIX_FMT, pArgv[5]);
		if(isValid)
		{
		    /** 把format赋给u32BmpPixFmt **/
	        g_eBmpPixFmt = str2enum(pArgv[5]);
		}
		else
		{
	        return HI_FALSE;
		}
	    g_pBmpFileName = pArgv[6];

        #if 0
		BMPGEN_TRACE("\n==============================================================\n");
	    BMPGEN_TRACE("g_u32BmpMemAddr   = 0x%x\n", g_u32BmpMemAddr);
	    BMPGEN_TRACE("g_u32BmpMemWidth  = %d\n",   g_u32BmpMemWidth);
	    BMPGEN_TRACE("g_u32BmpMemHight  = %d\n",   g_u32BmpMemHight);
	    BMPGEN_TRACE("g_u32BmpMemStride = %d\n",   g_u32BmpMemStride);
	    BMPGEN_TRACE("g_eBmpPixFmt      = %d\n",   g_eBmpPixFmt);
	    BMPGEN_TRACE("eBmpFileName      = %s\n",   g_pBmpFileName);
	    BMPGEN_TRACE("Input completed!\n");
        BMPGEN_TRACE("\n==============================================================\n");
        #endif
		
		return HI_TRUE;
	
}
