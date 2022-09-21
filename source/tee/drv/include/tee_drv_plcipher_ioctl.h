/******************************************************************************

  Copyright (C), 2011-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_drv_plcipher_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __TEE_DRV_PLCIPHER_IOCTL_H__
#define __TEE_DRV_PLCIPHER_IOCTL_H__

#include "hi_type.h"
#include "hi_tee_drv_plcipher.h"
#include "tee_plcipher_utils.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


//#define HI_ID_PLCIPHER 0x69

#define TEE_PLCIPHER_IOC_NA       0U
#define TEE_PLCIPHER_IOC_W        1U
#define TEE_PLCIPHER_IOC_R        2U
#define TEE_PLCIPHER_IOC_RW       3U

#define TEE_PLCIPHER_IOC(dir, type, nr, size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define TEE_PLCIPHER_IOR(type,nr,size)    TEE_PLCIPHER_IOC(TEE_PLCIPHER_IOC_R,(type),(nr), sizeof(size))
#define TEE_PLCIPHER_IOW(type,nr,size)    TEE_PLCIPHER_IOC(TEE_PLCIPHER_IOC_W,(type),(nr), sizeof(size))
#define TEE_PLCIPHER_IOWR(type,nr,size)   TEE_PLCIPHER_IOC(TEE_PLCIPHER_IOC_RW,(type),(nr),sizeof(size))

#define TEE_PLCIPHER_IOC_DIR(nr)      (((nr) >> 30) & 0x03)
#define TEE_PLCIPHER_IOC_TYPE(nr)     (((nr) >> 8) & 0xFF)
#define TEE_PLCIPHER_IOC_NR(nr)       (((nr) >> 0) & 0xFF)
#define TEE_PLCIPHER_IOC_SIZE(nr)     (((nr) >> 16) & 0x3FFF)



/* Ioctl definitions */
#define    TEE_CMD_PLCIPHER_INIT                   TEE_PLCIPHER_IOWR(HI_ID_PLCIPHER, 0x1, NULL)
#define    TEE_CMD_PLCIPHER_DEINIT                 TEE_PLCIPHER_IOWR(HI_ID_PLCIPHER, 0x2, NULL)
#define    TEE_CMD_PLCIPHER_CREATEHANDLE           TEE_PLCIPHER_IOWR(HI_ID_PLCIPHER, 0x3, HI_HANDLE)
#define    TEE_CMD_PLCIPHER_DESTROYHANDLE          TEE_PLCIPHER_IOW(HI_ID_PLCIPHER,  0x4, HI_HANDLE)
#define    TEE_CMD_PLCIPHER_GETATTR                TEE_PLCIPHER_IOWR(HI_ID_PLCIPHER, 0x5, PLCIPHER_CONFIG_S)
#define    TEE_CMD_PLCIPHER_SETATTR                TEE_PLCIPHER_IOW(HI_ID_PLCIPHER,  0x6, PLCIPHER_CONFIG_S)
#define    TEE_CMD_PLCIPHER_SETKEY                 TEE_PLCIPHER_IOW(HI_ID_PLCIPHER,  0x7, PLCIPHER_SetKey)
#define    TEE_CMD_PLCIPHER_ENCRYPT                TEE_PLCIPHER_IOW(HI_ID_PLCIPHER,  0x8, PLCIPHER_DATA_S)
#define    TEE_CMD_PLCIPHER_DECRYPT                TEE_PLCIPHER_IOW(HI_ID_PLCIPHER,  0x9, PLCIPHER_DATA_S)
#define    TEE_CMD_PLCIPHER_GETHANDLEID            TEE_PLCIPHER_IOWR(HI_ID_PLCIPHER, 0xB, HI_U32)
#define    TEE_CMD_PLCIPHER_PUTHANDLEID            TEE_PLCIPHER_IOW(HI_ID_PLCIPHER,  0xC, HI_U32)

HI_S32 TEE_PLCIPHER_Ioctl(HI_U32 cmd, HI_VOID *argp);

HI_S32 HI_DRV_PLCIPHER_GetHandleId(HI_U32 *HandleId);
HI_S32 HI_DRV_PLCIPHER_PutHandleId(HI_U32 HandleId);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __TEE_DRV_PLCIPHER_IOCTL_H__*/
