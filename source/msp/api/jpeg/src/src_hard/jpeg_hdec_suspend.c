/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_suspend.c
Version           : Initial Draft
Author            : sdk
Created          : 2017/07/05
Description      : 待机处理
Function List    :


History          :
Date                         Author                Modification
2017/07/05               sdk                    Created file
******************************************************************************/

/***************************** add include here************************************/
#ifdef CONFIG_JPEG_SUSPEND

#include "jpeg_hdec_api.h"
#include "jpeg_hdec_rwreg.h"
#include "hi_drv_jpeg.h"
#include "hi_jpeg_reg.h"
#include "hi_gfx_sys.h"

/***************************** Macro Definition *************************************/

/******************** to see which include file we want to use***************************/



/*************************** Structure Definition ************************************/



/********************** Global Variable declaration ***********************************/



/******************************* API forward declarations ****************************/

extern  HI_S32 JPEG_HDEC_SetPara(const struct jpeg_decompress_struct *cinfo);

/******************************* API realization ************************************/


/*****************************************************************************
* func             : JPEG_HDEC_GetSuspendSignal
* description   :  get the suspend signal
                        CNcomment:  获取待机信号             CNend\n
* param[in]    : *pJpegHandle    CNcomment:  解码器句柄   CNend\n
* param[in]    :  bSuspendSignal  CNcomment:  待机信号 CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_GetSuspendSignal(const JPEG_HDEC_HANDLE_S  *pJpegHandle,HI_BOOL *bSuspendSignal)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_BOOL bSuspend  = HI_FALSE;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, bSuspendSignal);

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETSUSPEND, &bSuspend);
    if (HI_SUCCESS != Ret)
    {
        return;
    }

    *bSuspendSignal = bSuspend;

    return;
}

/*****************************************************************************
* func            : JPEG_HDEC_GetResumeSignal
* description   : get the resume signal
                        CNcomment:  获取待机唤醒信号             CNend\n
* param[in]    : *pJpegHandle    CNcomment:  解码器句柄   CNend\n
* param[in]    : bResumeSignal  CNcomment:   待机唤醒信号 CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_GetResumeSignal(const JPEG_HDEC_HANDLE_S  *pJpegHandle,HI_BOOL *bResumeSignal)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_BOOL bResume = HI_FALSE;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, bResumeSignal);

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETRESUME, &bResume);
    if (HI_SUCCESS != Ret)
    {
        return;
    }

    *bResumeSignal = bResume;

    return;
}

/*****************************************************************************
* func            : JPEG_HDEC_Resume
* description   : suspend resume
                         CNcomment: 待机唤醒 CNend\n
* param[in]    : cinfo       CNcomment:  解码对象         CNend\n
* retval           : NA
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_HDEC_Resume(const struct jpeg_decompress_struct *cinfo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_JPG_SAVEINFO_S stResumeValue;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;

    CHECK_JPEG_EQUAL_UNRETURN(NULL, cinfo);

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pJpegHandle);

    HI_GFX_Memset(&stResumeValue,0,sizeof(HI_JPG_SAVEINFO_S));

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_CANCEL_RESET);
    if (HI_SUCCESS != Ret)
    {
       return;
    }

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETRESUMEVALUE, &stResumeValue);
    if (HI_SUCCESS != Ret)
    {
       return;
    }
    pJpegHandle->ResByteConsum = stResumeValue.u32ResByteConsu;

    Ret = JPEG_HDEC_SetPara(cinfo);
    if (HI_SUCCESS != Ret)
    {
       return;
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_BSRES_DATA0_CFG, stResumeValue.u32ResumeData0);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_BSRES_DATA1_CFG, stResumeValue.u32ResumeData1);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_BSRES_BIT_CFG,   stResumeValue.u32ResBitRemain);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_MCUY_CFG,        stResumeValue.u32ResMcuy);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PD_Y_CFG,        stResumeValue.u32Pdy);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PD_CBCR_CFG,     stResumeValue.u32Pdcbcr);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_DRI_CNT_CFG,     stResumeValue.u32DriCnt);

#if 0
    JPEG_TRACE("===============================================================\n");
    JPEG_TRACE("pJpegHandle->ResByteConsum = %d\n",pJpegHandle->ResByteConsum);
    JPEG_TRACE("stResumeValue.u32ResumeData0  = %d\n",stResumeValue.u32ResumeData0);
    JPEG_TRACE("stResumeValue.u32ResumeData1  = %d\n",stResumeValue.u32ResumeData1);
    JPEG_TRACE("stResumeValue.u32ResBitRemain = %d\n",stResumeValue.u32ResBitRemain);
    JPEG_TRACE("stResumeValue.u32ResMcuy      = %d\n",stResumeValue.u32ResMcuy);
    JPEG_TRACE("stResumeValue.u32Pdy          = %d\n",stResumeValue.u32Pdy);
    JPEG_TRACE("stResumeValue.u32Pdcbcr       = %d\n",stResumeValue.u32Pdcbcr);
    JPEG_TRACE("stResumeValue.u32DriCnt       = %d\n",stResumeValue.u32DriCnt);
    JPEG_TRACE("===============================================================\n");
#endif
}
#endif /** END IF  CONFIG_JPEG_SUSPEND **/
