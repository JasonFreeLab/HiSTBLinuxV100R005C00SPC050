/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : tee_drv_cert_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __TEE_DRV_CERT_IOCTL_H__
#define __TEE_DRV_CERT_IOCTL_H__

#include "hi_type.h"
#include "hi_tee_drv_cert.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define HI_ID_CERT 0x6A
#define TEE_CERT_IOC_NA        0U
#define TEE_CERT_IOC_W         1U
#define TEE_CERT_IOC_R         2U
#define TEE_CERT_IOC_RW        3U
#define TEE_CERT_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define TEE_CERT_IO(type,nr)           TEE_CERT_IOC(TEE_CERT_IOC_R,(type),(nr), 0)
#define TEE_CERT_IOR(type,nr,size)     TEE_CERT_IOC(TEE_CERT_IOC_R,(type),(nr), sizeof(size))
#define TEE_CERT_IOW(type,nr,size)     TEE_CERT_IOC(TEE_CERT_IOC_W,(type),(nr), sizeof(size))
#define TEE_CERT_IOWR(type,nr,size)    TEE_CERT_IOC(TEE_CERT_IOC_RW,(type),(nr),sizeof(size))
#define TEE_CERT_IOC_DIR(cmd)               (((cmd) >> 30) & 0x3)
#define TEE_CERT_IOC_SIZE(cmd)              (((cmd) >> 16) & 0x3fff)
#define TEE_CERT_IOC_TYPE(cmd)              (((cmd) >> 8) & 0xff)
#define TEE_CERT_IOC_NR(cmd)                ((cmd) & 0xff)

/* Ioctl definitions */
#define    CMD_CERT_AKLEXCHANGE         TEE_CERT_IOWR(HI_ID_CERT, 0x1, CERT_CMD_CTL)
#define    CMD_CERT_AKLKEYSEND_CTL      TEE_CERT_IOW(HI_ID_CERT, 0x2, HI_TEE_CERT_KEY_DATA_S)
#define    CMD_CERT_LOCK                TEE_CERT_IOR(HI_ID_CERT, 0x3, HI_TEE_CERT_RES_HANDLE)
#define    CMD_CERT_UNLOCK              TEE_CERT_IOWR(HI_ID_CERT, 0x4, HI_TEE_CERT_RES_HANDLE)
#define    CMD_CERT_RESET               TEE_CERT_IO(HI_ID_CERT,  0x5)
#define    CMD_CERT_AKLSETIV            TEE_CERT_IOW(HI_ID_CERT, 0x6, HI_TEE_CERT_IV_S)
#define    CMD_CERT_READL               TEE_CERT_IOWR(HI_ID_CERT,  0x7, CERT_REG_S)
#define    CMD_CERT_WRITEL              TEE_CERT_IOW(HI_ID_CERT,  0x8, CERT_REG_S)

#define TEE_CERT_ALLOC_BUFFER(size, from)  \
        void *p = NULL;                    \
        if(size != 0){                     \
            p = (void *) tee_hal_malloc((size)); \
            if (p == NULL) { \
                tee_hal_printf("ERROR!!!, klad alloc buffer failed\n"); \
                regs->r0 = HI_TEE_ERR_MEM; \
            break; }\
            memcpy_s(p, size, from, size); \
        }

#define TEE_CERT_FILL_RETURN(size, from) \
        if(size != 0){ \
            memcpy_s(from, size, p, size); \
        }

#define TEE_CERT_FREE_BUFFER() tee_hal_free(p)

HI_S32 TEE_CERT_Ioctl(HI_U32 cmd, HI_VOID *argp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __TEE_DRV_CERT_IOCTL_H__*/
