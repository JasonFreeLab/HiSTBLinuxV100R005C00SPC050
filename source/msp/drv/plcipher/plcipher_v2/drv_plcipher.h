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
#include "drv_plcipher_ioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

/******* proc function begin ********/
#ifdef HI_PLCIPHER_PROC_SUPPORT
HI_S32 DRV_PLCIPHER_GetChanStatus(PLCIPHER_CHN_STATUS_S *pstChanStatus);
#endif
/******* proc function end ********/


#ifdef __cplusplus
}
#endif
#endif /* __DRV_PLCIPHER_H__ */
