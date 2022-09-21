/******************************************************************************

  Copyright (C), 2013-2020, Hisilicon. Co., Ltd.

******************************************************************************
File Name	    : main.c
Version		    : Initial Draft
Author		    : 
Created		    : 2013/06/20
Description	    : bmp save的入口函数
                  CNcomment: bmp save的入口函数 CNend\n
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2013/06/20		    y00181162  		    Created file      	
******************************************************************************/


/*********************************add include here******************************/

#include <stdio.h>

#include "bmp_input.h"
#include "bmp_Gen.h"

/***************************** Macro Definition ******************************/


/******************** to see which include file we want to use***************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/

int main(int args, char ** argv)
{

        HI_VOID *pDataAddr  = NULL;
		HI_BOOL bIsSuccess  = HI_FALSE;
		HI_S32 s32Cnt = 0;
		
        if(1 == args)
        {
           fprintf(stderr,"\n===============================================================\n");
           fprintf(stderr,"you can run as follows to look how to use this exe file\n");
		   fprintf(stderr,"./bmpGen --help\n");
		   fprintf(stderr,"===============================================================\n\n");
		   return 0;
        }
		for (s32Cnt = 1 ; s32Cnt < args ; s32Cnt++)
		{
		   if (  (!strncmp("--help", argv[s32Cnt], strlen("--help")>strlen(argv[s32Cnt])?strlen("--help"):strlen(argv[s32Cnt])))
		   	    ||(7 != args && args > 3))
		   {

			   fprintf(stderr,"\n===============================================================================================================================\n\n");
			   printf("\nUsage:  bmpGen [options]\n\n"
			   	       "export the fb input ui data.\n\n"
		               "             layerNum        0 SD layer, 2 HD layer.\n\n"
		               "             outfile         save file name.\n\n"
		               "For Example: ./bmpGen layerNum outfile \n\n"
		               "             ./bmpGen 2 data.bmp \n\n"
		               "export the physical ddr data.\n\n"
		               "             phyaddr         physical ddr that save data.\n\n"
					   "             width           width.the max value is %d\n\n"
					   "             height          height.the max value is %d\n\n"
					   "             stride          stride.\n\n"
					   "             pixformat       pixel format.support RGB565,BGR565,ARGB4444,ARGB1555,ABGR1555,RGB888,BGR888,ARGB8888 and ABGR8888\n\n"
					   "             outfile         save file name.\n\n"
					   "For Example: ./bmpGen phyaddr width height stride pixformat outfile\n\n",BMP_MAX_BMP_WIDTH,BMP_MAX_BMP_HIGHT);
               fprintf(stderr,"===============================================================================================================================\n\n");
			   return 0;
		   }
		   
		}
		
	    if(!BMP_INPUT_getInput(args, argv))
		{
		   return 1;
	    }
		
	    pDataAddr = BMP_DATA_GetData();
	    if(pDataAddr == HI_NULL_PTR)
	    {
	        fprintf(stderr,"Extract data from memory fails!\n");
			return -1;
	    }
		
	    bIsSuccess = BMP_DATA_GenBmp(pDataAddr);
	    if(bIsSuccess)
	    {
	        fprintf(stderr,"\n==================================================================================================\n");
	        fprintf(stderr,"save data to bmp file success!\n");
			fprintf(stderr,"==================================================================================================\n");
	        return 0;
	    }
	    else
	    {
	        fprintf(stderr,"\n===============================================================\n");
	        fprintf(stderr,"save data to bmp file fails!\n");
			fprintf(stderr,"===============================================================\n");
	        return 1;
	    }
	
}
