/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_drv_proc.h
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : the proc information define in this file
                      CNcomment: proc 相关的信息都在这里 CNend\n
Function List   :


History           :
Date                      Author           Modification
2017/07/05            sdk              Created file
******************************************************************************/

#ifndef __JPEG_DRV_PROC_H__
#define __JPEG_DRV_PROC_H__

/*********************************add include here********************************/
#include "hi_jpeg_config.h"


#ifdef CONFIG_JPEG_PROC_ENABLE

#include "hi_type.h"

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


   /***************************** Macro Definition ********************************/

   /*************************** Structure Definition *******************************/


   /********************** Global Variable declaration ******************************/


   /******************************* API declaration ******************************/

   /*****************************************************************************
       * Function      : JPEG_PROC_Init
       * Description  :  initial jpeg proc
       * param[in]    : NA
       * retval          : NA
     *****************************************************************************/
   HI_S32 JPEG_PROC_Init(HI_VOID);


   /*****************************************************************************
       * Function      : JPEG_PROC_DInit
       * Description  :  dinitial jpeg proc
       * param[in]    : NA
       * retval          : NA
     *****************************************************************************/
   HI_VOID JPEG_PROC_DInit(HI_VOID);

   /*****************************************************************************
       * Function      : JPEG_PROC_GetInflexionSize
       * Description  :  get decode inflexion size
       * param[ou]   : pInflexionSize
       * retval          : NA
     *****************************************************************************/
   HI_VOID JPEG_PROC_GetInflexionSize(HI_U32 *pInflexionSize);

   /*****************************************************************************
       * Function      : JPEG_PROC_SetStreamBuf
       * Description  :  set jpeg stream buffer
       * param[in]    : StartStreamBuf
       * param[in]    : EndStreamBuf
       * retval          : NA
     *****************************************************************************/
   HI_VOID JPEG_PROC_SetStreamBuf(HI_U32 StartStreamBuf, HI_U32 EndStreamBuf);

   /*****************************************************************************
       * Function      : JPEG_PROC_SetSaveDataBuf
       * Description  :  set jpeg save data buffer
       * param[in]    : StartSaveDataBuf
       * param[in]    : EndSaveDataBuf
       * retval          : NA
     *****************************************************************************/
   HI_VOID JPEG_PROC_SetSaveDataBuf(HI_U32 StartSaveDataBuf, HI_U32 EndSaveDataBuf);

   /*****************************************************************************
       * Function      : JPEG_PROC_SetPthreadNum
       * Description  :  set jpeg decode pthread numbers
       * param[in]    : PthreadNums
       * retval          : NA
     *****************************************************************************/
   HI_VOID JPEG_PROC_SetPthreadNum(HI_U32 PthreadNums);

   /*****************************************************************************
       * Function      : JPEG_PROC_SetDecLockTimes
       * Description  :  set jpeg decode has been lock times
       * param[in]    : PthreadNums
       * retval          : NA
     *****************************************************************************/
    HI_VOID JPEG_PROC_SetDecLockTimes(HI_U32 LockTimes);


   /*****************************************************************************
      * Function      : JPEG_PROC_SetOpenDevCnt
      * Description  :  set jpeg decode has been open times
      * param[in]    : PthreadNums
      * retval          : NA
    *****************************************************************************/
   HI_VOID JPEG_PROC_SetOpenDevCnt(HI_S32 OpenTimes);

   /*****************************************************************************
       * Function      : JPEG_PROC_SetInfo
       * Description  :  set jpeg proc information from user
       * param[in]    : Argc
       * retval          : HI-SUCCESS
     *****************************************************************************/
   HI_S32 JPEG_PROC_SetInfo(HI_ULONG Argc);

   /****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif/**CONFIG_JPEG_PROC_ENABLE**/

#endif /** use the proc information -DCONFIG_JPEG_PROC_ENABLE **/
