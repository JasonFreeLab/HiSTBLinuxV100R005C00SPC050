/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

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

#ifndef __DRV_CIPHER_IOCTL_H__
#define __DRV_CIPHER_IOCTL_H__

#include "hi_type.h"
#include "hi_unf_cipher.h"
#include "hi_drv_cipher.h"
#include "hi_debug.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define _IOC_NA	    0U
#define _IOC_W	    1U
#define _IOC_R	    2U
#define _IOC_RW	    3U

#define _IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

#define _IOR(type,nr,size)	_IOC(_IOC_R,(type),(nr), sizeof(size))
#define _IOW(type,nr,size)	_IOC(_IOC_W,(type),(nr), sizeof(size))
#define _IOWR(type,nr,size)	_IOC(_IOC_RW,(type),(nr),sizeof(size))

#define _IOC_DIR(nr)		(((nr) >> 30) & 0x03)
#define _IOC_TYPE(nr)		(((nr) >> 8) & 0xFF)
#define _IOC_NR(nr)		(((nr) >> 0) & 0xFF)
#define _IOC_SIZE(nr)		(((nr) >> 16) & 0x3FFF)

#define HI_ID_CIPHER 0x4D

HI_S32 CIPHER_MODULE_Init(HI_VOID);
HI_VOID CIPHER_MODULE_Exit(HI_VOID);
HI_S32 CIPHER_Ioctl(HI_VOID *inode, HI_VOID *file, unsigned int cmd, HI_VOID *argp);

typedef struct
{
    HI_U32    u32Resv;
}CIPHER_PROC_ITEM_S;

typedef struct
{
    HI_U32 u32Status;
}CIPHER_HDCPKEYSTATUS_S;

typedef struct
{
    HI_U32 u32ChnId;
    HI_CHAR *ps8Openstatus;
    HI_CHAR *ps8Alg;
    HI_CHAR *ps8Mode;
    HI_U32 u32KeyLen;
    HI_CHAR *ps8KeyFrom;
    HI_BOOL bIsDecrypt;
    HI_U32 u32DataInSize;
    HI_U32 u32DataInAddr;
    HI_U32 u32DataOutSize;
    HI_U32 u32DataOutAddr;
    HI_BOOL bInINTAllEn;
    HI_BOOL bInINTEn;
    HI_BOOL bInINTRaw;
    HI_BOOL bOutINTEn;
    HI_BOOL bOutINTRaw;
    HI_U32 u32OutINTCount;      //CHANn_INT_OCNTCFG
    HI_U8  u8IVString[33];
}CIPHER_CHN_STATUS_S;

/* Ioctl definitions */
#define    CMD_CIPHER_CREATEHANDLE           _IOWR(HI_ID_CIPHER, 0x1, CIPHER_HANDLE_S)
#define    CMD_CIPHER_DESTROYHANDLE          _IOW(HI_ID_CIPHER,  0x2, HI_U32)
#define    CMD_CIPHER_CONFIGHANDLE           _IOW(HI_ID_CIPHER,  0x3, CIPHER_Config_CTRL)
#define    CMD_CIPHER_ENCRYPT                _IOW(HI_ID_CIPHER,  0x4, CIPHER_DATA_S)
#define    CMD_CIPHER_DECRYPT                _IOW(HI_ID_CIPHER,  0x5, CIPHER_DATA_S)
#define    CMD_CIPHER_DECRYPTMULTI           _IOW(HI_ID_CIPHER,  0x6, CIPHER_PKG_S)
#define    CMD_CIPHER_ENCRYPTMULTI           _IOW(HI_ID_CIPHER,  0x7, CIPHER_PKG_S)
#define    CMD_CIPHER_GETRANDOMNUMBER        _IOWR(HI_ID_CIPHER, 0x8, CIPHER_RNG_S)
#define    CMD_CIPHER_GETHANDLECONFIG        _IOWR(HI_ID_CIPHER, 0x9, CIPHER_Config_CTRL)
#define    CMD_CIPHER_CALCHASHINIT           _IOWR(HI_ID_CIPHER, 0xa, CIPHER_HASH_DATA_S)
#define    CMD_CIPHER_CALCHASHUPDATE         _IOWR(HI_ID_CIPHER, 0xb, CIPHER_HASH_DATA_S)
#define    CMD_CIPHER_CALCHASHFINAL          _IOWR(HI_ID_CIPHER, 0xc, CIPHER_HASH_DATA_S)
#define    CMD_CIPHER_CBCMAC_AUTH            _IOW(HI_ID_CIPHER,  0xf, CIPHER_CBCMAC_DATA_S)
#define    CMD_CIPHER_CALCRSA                _IOWR(HI_ID_CIPHER, 0x10, CIPHER_RSA_DATA_S)
#define    CMD_CIPHER_GETTAG                 _IOWR(HI_ID_CIPHER, 0x11, CIPHER_TAG_S)
#define    CMD_CIPHER_CONFIGHANDLE_EX        _IOW(HI_ID_CIPHER,  0x17, CIPHER_CONFIG_CTRL_EX)
#define    CMD_CIPHER_GETHANDLECONFIG_EX     _IOWR(HI_ID_CIPHER, 0x18, CIPHER_CONFIG_CTRL_EX)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_CIPHER_IOCTL_H__*/
