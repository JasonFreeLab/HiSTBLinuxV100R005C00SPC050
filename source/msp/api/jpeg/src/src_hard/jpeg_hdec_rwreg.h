/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hdec_rwreg.h
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : ¼Ä´æÆ÷²Ù×÷
Function List   :


History           :
Date                      Author                   Modification
2017/07/05             sdk                       Created file
******************************************************************************/
#ifndef __JPEG_HDEC_RWREG_H__
#define __JPEG_HDEC_RWREG_H__


/*********************************add include here******************************/
#include  "hi_type.h"


/*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

    /***************************** Macro Definition *******************************/

    /*************************** Enum Definition ********************************/

    /*************************** Structure Definition *******************************/


    /********************** Global Variable declaration *******************************/

    /******************************* API declaration *****************************/
    HI_VOID JPEG_HDEC_WriteReg(volatile HI_CHAR *pJpegRegVirAddr, const HI_U32 PhyOff, const HI_U32 Val);
    HI_S32  JPEG_HDEC_ReadReg(const volatile HI_CHAR *pJpegRegVirAddr, const HI_U32 PhyOff);
    HI_VOID JPEG_HDEC_CpyData2Reg(volatile HI_CHAR *pJpegRegVirAddr,const HI_VOID *pInMem,const HI_U32 PhyOff,const HI_U32 u32Bytes);
    HI_S32  JPEG_HDEC_CpyData2Buf(const volatile HI_CHAR *pJpegRegVirAddr,const HI_U32 PhyOff,const HI_U32 u32Bytes,HI_VOID *pOutMem);

    /****************************************************************************/

#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_HDEC_RWREG_H__*/
