/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_plcipher.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_PLCIPHER_H__
#define __DRV_PLCIPHER_H__

/* add include here */
#include "hal_plcipher.h"
#include "drv_plcipher_ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
HI_S32 DRV_PLCIPHER_Init(HI_VOID);
HI_VOID DRV_PLCIPHER_DeInit(HI_VOID);
HI_S32 DRV_PLCIPHER_Open(struct inode * inode, struct file * file);
HI_S32 DRV_PLCIPHER_Release(struct inode * inode, struct file * file);

/******* proc function begin ********/
#ifdef HI_PLCIPHER_PROC_SUPPORT
HI_S32 DRV_PLCIPHER_GetChanStatus(PLCIPHER_CHN_STATUS_S *pstChanStatus);
HI_S32 DRV_PLCIPHER_GetDESCStatus(PLCIPHER_DESC_STATUS_S *pstDescStatus);
#endif
/******* proc function end ********/


#ifdef __cplusplus
}
#endif
#endif /* __DRV_PLCIPHER_H__ */
