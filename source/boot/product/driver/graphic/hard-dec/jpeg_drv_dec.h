/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_drv_dec.c
Version            : Initial Draft
Author             :
Created           : 2017/06/08
Description      : 这个只有在boot和OMX环境下使用，其它不使用
Function List    :


History           :
Date                        Author                Modification
2017/06/08            sdk                     Created file
******************************************************************************/
#ifndef __JPEG_DRV_DEC_H__
#define __JPEG_DRV_DEC_H__


/*********************************add include here******************************/
#ifndef HI_BUILD_IN_BOOT
    #include <linux/syscalls.h>
    #include <linux/ipc.h>
#endif

#include "hi_jpeg_config.h"
#include "hi_drv_jpeg.h"
#include "hi_type.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */



     /***************************** Macro Definition ******************************/
     /** \addtogroup      JPEG */
     /** @{ */    /** <!--[JPEG]*/


     /** @} */  /** <!-- ==== Macro Definition end ==== */

     /*************************** Enum Definition ****************************/
    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /** @} */  /** <!-- ==== enum Definition end ==== */

    /*************************** Structure Definition ****************************/
    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    /** @} */  /** <!-- ==== Structure Definition End ==== */

    /********************** Global Variable declaration **************************/

    /******************************* API declaration *****************************/

    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/

    #ifndef HI_BUILD_IN_BOOT
    /***************************************************************************************
     * func          : jpg_dec_getintstatus
     * description     :
                       CNcomment: 获取中断状态 CNend\n
     * param[in]     : irq
     * param[in]     : * devId
     * param[in]     : * ptrReg
     * retval         : HI_SUCCESS 成功
     * retval         : HI_FAILURE 失败
     * others:         : NA
     ***************************************************************************************/
    HI_S32 JPEG_DRV_GetIntStatusValue(JPEG_GETINTTYPE_S *pstIntType);

    /***************************************************************************************
     * func          : JPEG_DRV_UnLock
     * description     : release dec mutex
                       CNcomment: 释放解码信号量 CNend\n
     * param[in]     : eIntType : 解码状态
     * retval         : HI_SUCCESS 成功
     * retval         : HI_FAILURE 失败
     * others:         : NA
     ***************************************************************************************/
    HI_VOID JPEG_DRV_UnLock(JPEG_INTTYPE_E eIntType);


    /***************************************************************************************
     * func          : JPEG_DRV_Lock
     * description     : lock dec
                       CNcomment: 锁状态 CNend\n
     * retval         : HI_SUCCESS 成功
     * retval         : HI_FAILURE 失败
     * others:         : NA
     ***************************************************************************************/
    HI_S32 JPEG_DRV_Lock(HI_VOID);

    #endif

    /** @} */  /** <!-- ==== API Declaration End ==== */

    /****************************************************************************/

#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_DRV_DEC_H__*/
