/******************************************************************************

  Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_cipher_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :
******************************************************************************/

#ifndef __TEE_DRV_CIPHER_IOCTL_H__
#define __TEE_DRV_CIPHER_IOCTL_H__

#include "hi_type.h"
#include "hi_tee_drv_cipher.h"
#include "hi_tee_cipher.h"

#define TEE_CIPHER_IOC_NA	    0U
#define TEE_CIPHER_IOC_W	    1U
#define TEE_CIPHER_IOC_R	    2U
#define TEE_CIPHER_IOC_RW	    3U

#define HASH_BLOCK_SIZE		(64)

#define TEE_CIPHER_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define TEE_CIPHER_IOR(type,nr,size)	TEE_CIPHER_IOC(TEE_CIPHER_IOC_R,(type),(nr), sizeof(size))
#define TEE_CIPHER_IOW(type,nr,size)	TEE_CIPHER_IOC(TEE_CIPHER_IOC_W,(type),(nr), sizeof(size))
#define TEE_CIPHER_IOWR(type,nr,size)	TEE_CIPHER_IOC(TEE_CIPHER_IOC_RW,(type),(nr),sizeof(size))

#define TEE_CIPHER_IOC_DIR(nr)		(((nr) >> 30) & 0x03)
#define TEE_CIPHER_IOC_TYPE(nr)		(((nr) >> 8) & 0xFF)
#define TEE_CIPHER_IOC_NR(nr)		(((nr) >> 0) & 0xFF)
#define TEE_CIPHER_IOC_SIZE(nr)		(((nr) >> 16) & 0x3FFF)

#define HI_ID_CIPHER 0x4D

HI_S32 TEE_CIPHER_Ioctl(HI_U32 cmd, HI_VOID *argp); 
HI_S32 __TEE_CIPHER_Ioctl(HI_U32 u32Cmd, HI_VOID *args);

#define cipher_memcmp           TEE_MemCompare

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#define    CMD_CIPHER_CREATEHANDLE           TEE_CIPHER_IOWR(HI_ID_CIPHER,  0x1,  CIPHER_HANDLE_S)
#define    CMD_CIPHER_DESTROYHANDLE          TEE_CIPHER_IOW(HI_ID_CIPHER,  0x2,  HI_U32)
#define    CMD_CIPHER_CONFIGHANDLE           TEE_CIPHER_IOW(HI_ID_CIPHER,  0x3,  CIPHER_Config_CTRL)
#define    CMD_CIPHER_ENCRYPT                TEE_CIPHER_IOW(HI_ID_CIPHER,  0x4,  CIPHER_DATA_S)
#define    CMD_CIPHER_DECRYPT                TEE_CIPHER_IOW(HI_ID_CIPHER,  0x5,  CIPHER_DATA_S)
#define    CMD_CIPHER_DECRYPTMULTI           TEE_CIPHER_IOW(HI_ID_CIPHER,  0x6,  CIPHER_PKG_S)
#define    CMD_CIPHER_ENCRYPTMULTI           TEE_CIPHER_IOW(HI_ID_CIPHER,  0x7,  CIPHER_PKG_S)
#define    CMD_CIPHER_GETRANDOMNUMBER        TEE_CIPHER_IOWR(HI_ID_CIPHER,  0x8,  CIPHER_RNG_S)
#define    CMD_CIPHER_GETHANDLECONFIG        TEE_CIPHER_IOWR(HI_ID_CIPHER,  0x9,  CIPHER_Config_CTRL)
#define    CMD_CIPHER_CALCHASHINIT           TEE_CIPHER_IOWR(HI_ID_CIPHER,  0xa,  CIPHER_HASH_INIT_S)
#define    CMD_CIPHER_CALCHASHUPDATE         TEE_CIPHER_IOW(HI_ID_CIPHER,  0xb,  CIPHER_HASH_UPDATE_S)
#define    CMD_CIPHER_CALCHASHFINAL          TEE_CIPHER_IOWR(HI_ID_CIPHER, 0xc,  CIPHER_HASH_FINISH_S)
#define    CMD_CIPHER_CALCRSA                TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x10, CIPHER_RSA_DATA_S)
#define    CMD_CIPHER_GETTAG                 TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x11, CIPHER_TAG_S)
#define    CMD_SM2_SIGN                      TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x12, SM2_SIGN_DATA_S)
#define    CMD_SM2_VERIFY                    TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x13, SM2_VERIFY_DATA_S)
#define    CMD_SM2_ENCRYPT                   TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x14, SM2_ENC_DATA_S)
#define    CMD_SM2_DECRYPT                   TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x15, SM2_ENC_DATA_S)
#define    CMD_SM2_KEY                       TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x16, SM2_KEY_DATA_S)
#define    CMD_CIPHER_WAIT_DONE              TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x17, CIPHER_WAIT_DONE_S)
#define    CMD_HASH_WAIT_DONE                TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x18, HI_HANDLE)
#define    CMD_CIPHER_DECRYPTMULTI_ASYN      TEE_CIPHER_IOW(HI_ID_CIPHER,  0x19, CIPHER_PKG_S)
#define    CMD_CIPHER_ENCRYPTMULTI_ASYN      TEE_CIPHER_IOW(HI_ID_CIPHER,  0x20, CIPHER_PKG_S)
#define    CMD_CIPHER_PBKDF2                 TEE_CIPHER_IOWR(HI_ID_CIPHER,  0x22, HI_TEE_CIPHER_PBKDF2_S)
#define    CMD_CIPHER_CONFIGHANDLE_EX        TEE_CIPHER_IOW(HI_ID_CIPHER,  0x23, CIPHER_CONFIG_CTRL_EX)
#define    CMD_CIPHER_GETHANDLECONFIG_EX     TEE_CIPHER_IOWR(HI_ID_CIPHER,  0x24, CIPHER_CONFIG_CTRL_EX)

#define    CMD_CIPHER_GET_INFO               TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x25, CIPHER_INFO_S)
#define    CMD_CIPHER_CENC_DECRYPT           TEE_CIPHER_IOW(HI_ID_CIPHER, 0x26, CIPHER_CENC_DECRYPT_S)
#define    CMD_CIPHER_SETUSGAERULE           TEE_CIPHER_IOW(HI_ID_CIPHER,  0x27, CIPHER_USAGE_RULE)

#define    CMD_CIPHER_INIT                   TEE_CIPHER_IOW(HI_ID_CIPHER, 0x20, NULL)
#define    CMD_CIPHER_DEINIT                 TEE_CIPHER_IOW(HI_ID_CIPHER, 0x21, NULL)
#define    CMD_CIPHER_TEST                   TEE_CIPHER_IOWR(HI_ID_CIPHER, 0x30, CIPHER_TEST_DATA_S)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_CIPHER_IOCTL_H__*/
