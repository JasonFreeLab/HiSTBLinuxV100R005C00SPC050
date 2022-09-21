/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_drv_suspend.h
Version            : Initial Draft
Author             :
Created           : 2017/07/05
Description      : the suspend dispose
                        CNcomment: 待机处理 CNend\n
Function List    :


History            :
Date                     Author                    Modification
2017/07/05            sdk                       Created file
******************************************************************************/
#ifndef __JPEG_DRV_SUSPEND_H__
#define __JPEG_DRV_SUSPEND_H__


/*********************************add include here******************************/

#include "hi_jpeg_config.h"
#include "hi_type.h"
#include "hi_drv_jpeg.h"

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */



    /***************************** Macro Definition ******************************/

     /*************************** Enum Definition ****************************/

    /*************************** Structure Definition ****************************/

    /********************** Global Variable declaration **************************/

    /******************************* API declaration *****************************/

    /***************************************************************************************
       * func           : JPGE_DRV_Suspend
       * description : get the suspend signale.
                                 CNcomment: 收到待机信号 CNend\n
      * param[in]     : *pdev
      * param[in]     : state
      * retval           : HI_SUCCESS 成功
      * retval          : HI_FAILURE 失败
      * others:        : NA
      ***************************************************************************************/
    HI_S32 JPGE_DRV_Suspend(PM_BASEDEV_S *pdev, pm_message_t state);

    /***************************************************************************************
         * func          : JPGE_DRV_Resume
         * description: get the resume signale.
                                  CNcomment: 收到待机唤醒信号 CNend\n
         * param[in]   : *pdev
         * retval         : HI_SUCCESS 成功
         * retval         : HI_FAILURE 失败
         * others:      : NA
        ***************************************************************************************/
    HI_S32 JPGE_DRV_Resume(PM_BASEDEV_S *pdev);

    #ifdef CONFIG_JPEG_SUSPEND
    /*****************************************************************************
    * func            : JPG_WaitDecTaskDone
    * description    : waite the jpeg decode task done
                      CNcomment: 等待解码任务完成  CNend\n
    * param[in]     : NULL
    * retval        : NA
    * others:        : NA
    *****************************************************************************/
    HI_VOID JPG_WaitDecTaskDone(HI_VOID);


    /*****************************************************************************
    * func            : JPG_GetResumeValue
    * description    : get the value that resume need
                      CNcomment: 获取待机唤醒需要的值  CNend\n
    * param[in]     : *pSaveInfo
    * retval        : NA
    * others:        : NA
    *****************************************************************************/
    HI_VOID JPG_GetResumeValue(HI_JPG_SAVEINFO_S *pSaveInfo);

    #endif/** CONFIG_JPEG_SUSPEND **/

    /****************************************************************************/



#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif/** __JPEG_DRV_SUSPEND_H__ **/
