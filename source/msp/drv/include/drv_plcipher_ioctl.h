/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_plcipher_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_PLCIPHER_IOCTL_H__
#define __DRV_PLCIPHER_IOCTL_H__

#include "hi_type.h"
#include "hi_unf_payloadcipher.h"
#include "hi_drv_plcipher.h"
#include "hi_debug.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef struct
{
    HI_U32 ChanID;
    HI_BOOL bOpen;                 /* mark soft channel open or not*/
    HI_BOOL bDataDone;                    /* mark the data done or not */
    HI_BOOL bEncryptOrDecrypt;
    HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd;
    HI_UNF_PLCIPHER_ALG_E enAlg;           /**< Operating mode */
    HI_U32 InPhyAddr;
    HI_U32 OutPhyAddr;
    HI_U32 DataLen;
    HI_U32 OddCW[4];
    HI_U32 EvenCW[4];
    HI_U32 IV[4];
}PLCIPHER_CHN_STATUS_S;
typedef struct
{
    HI_U32 InDescWPtr;
    HI_U32 InDescRPtr;
    HI_U32 InDescStartAddr;
    HI_U32 OutDescWPtr;
    HI_U32 OutDescRPtr;
    HI_U32 OutDescStartAddr;
    HI_U32 InDescValidNum;
    HI_U32 OutDescValidNum;
    HI_U32 LastChanNum;
    HI_U32 DescDepth;
}PLCIPHER_DESC_STATUS_S;

/* Ioctl definitions */
#define    CMD_PLCIPHER_CREATEHANDLE           _IOWR(HI_ID_PLCIPHER, 0x1, HI_U32)
#define    CMD_PLCIPHER_DESTROYHANDLE          _IOW(HI_ID_PLCIPHER,  0x2, HI_U32)
#define    CMD_PLCIPHER_GETATTR                _IOWR(HI_ID_PLCIPHER, 0x3, PLCIPHER_CONFIG_S)
#define    CMD_PLCIPHER_SETATTR                _IOW(HI_ID_PLCIPHER,  0x4, PLCIPHER_CONFIG_S)
#define    CMD_PLCIPHER_SETKEY                 _IOW(HI_ID_PLCIPHER,  0x5, PLCIPHER_SetKey)
#define    CMD_PLCIPHER_ENCRYPT                _IOW(HI_ID_PLCIPHER,  0x6, PLCIPHER_DATA_S)
#define    CMD_PLCIPHER_DECRYPT                _IOW(HI_ID_PLCIPHER,  0x7, PLCIPHER_DATA_S)


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_PLCIPHER_IOCTL_H__*/
