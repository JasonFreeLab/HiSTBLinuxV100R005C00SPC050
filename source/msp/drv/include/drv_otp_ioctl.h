/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_otp_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_OTP_IOCTL_H__
#define __DRV_OTP_IOCTL_H__

/* add include here */
#include "hi_unf_otp.h"
#include "hi_type.h"
#include "hi_drv_otp.h"
#include "hi_drv_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    HI_U32 addr;
    HI_U32 value;
}OTP_ENTRY_S;

typedef struct
{
    HI_U32 customer_key[4];
}OTP_CUSTOMER_KEY_S;

typedef struct
{
    HI_U32 key_len;
    OTP_CUSTOMER_KEY_S key;
}OTP_CUSTOMER_KEY_TRANSTER_S;

typedef struct
{
    HI_U8 key[16];
}OTP_HDCP_ROOT_KEY_S;

typedef struct
{
    HI_U8 key[16];
}OTP_STB_ROOT_KEY_S;

typedef struct
{
    HI_U32 offset;
    HI_U8 data;
}OTP_STB_PRIV_DATA_S;


typedef struct
{
    HI_U32 addr;
    HI_U8 start_bit;
    HI_U8 bit_width;
    HI_U8  value[OTP_FIELD_VALUE_MAX_LEN];
}OTP_DYNAMIC_DATA_S;

typedef enum
{
    OTP_OEM_ROOTKEY        = 0,
    OTP_HDCP_ROOTKEY,
    OTP_STB_ROOTKEY,
    OTP_SW_ROOTKEY,
    OTP_STBTA_ROOTKEY,
} OTP_ROOTKEY_E;


typedef struct
{
    OTP_ROOTKEY_E type;
    HI_U8 key[16];
} OTP_ROOT_KEY_S;

typedef struct
{
    OTP_ROOTKEY_E type;
    HI_BOOL bLock;
} OTP_ROOT_KEY_LOCK_S;

#define OTP_START_BIT(value)  (((value & 0xff0000) >> 16) & 0xff)
#define OTP_BIT_WIDTH(value)  (((value & 0xff00) >> 8) & 0xff)
#define OTP_VALUE_BYTE(value) (value & 0xff)
#define OTP_GET_PARA(start_bit, bit_width, value) \
    (((start_bit << 16) & 0xff0000) | ((bit_width << 8) & 0xff00) | (value & 0xff))


#define CMD_OTP_READ                    _IOWR(IOC_TYPE_OTP, 0x1, OTP_ENTRY_S)
#define CMD_OTP_WRITE                   _IOW(IOC_TYPE_OTP,  0x2, OTP_ENTRY_S)
#define CMD_OTP_WRITE_BYTE              _IOW(IOC_TYPE_OTP,  0x3, OTP_ENTRY_S)
#define CMD_OTP_SETPROTECT              _IO(IOC_TYPE_OTP,   0x4)
#define CMD_OTP_GETPROTECT              _IOR(IOC_TYPE_OTP,  0x5, HI_U32)
#define CMD_OTP_FUNCDISABLE             _IOW(IOC_TYPE_OTP,  0x6, HI_U32)
#define CMD_OTP_SETCUSTOMERKEY          _IOW(IOC_TYPE_OTP,  0x7, OTP_CUSTOMER_KEY_TRANSTER_S)
#define CMD_OTP_GETCUSTOMERKEY          _IOWR(IOC_TYPE_OTP, 0x8, OTP_CUSTOMER_KEY_TRANSTER_S)
#define CMD_OTP_GETDDPLUSFLAG           _IOR(IOC_TYPE_OTP,  0x9, HI_BOOL)
#define CMD_OTP_GETDTSFLAG              _IOR(IOC_TYPE_OTP,  0xA, HI_BOOL)
#define CMD_OTP_SETSTBPRIVDATA          _IOW(IOC_TYPE_OTP,  0xB, OTP_STB_PRIV_DATA_S)
#define CMD_OTP_GETSTBPRIVDATA          _IOWR(IOC_TYPE_OTP, 0xC, OTP_STB_PRIV_DATA_S)

#define CMD_OTP_WRITEHDCPROOTKEY        _IOW(IOC_TYPE_OTP,  0xD, OTP_HDCP_ROOT_KEY_S)
#define CMD_OTP_READHDCPROOTKEY         _IOWR(IOC_TYPE_OTP, 0xE, OTP_HDCP_ROOT_KEY_S)
#define CMD_OTP_LOCKHDCPROOTKEY         _IO(IOC_TYPE_OTP,   0xF)
#define CMD_OTP_GETHDCPROOTKEYLOCKFLAG  _IOR(IOC_TYPE_OTP,  0x10, HI_BOOL)
#define CMD_OTP_GETDTSENFLAG            _IOR(IOC_TYPE_OTP,  0x11, HI_BOOL)
#define CMD_OTP_GETDOLBYENFLAG          _IOR(IOC_TYPE_OTP,  0x12, HI_BOOL)

#define CMD_OTP_WRITESTBROOTKEY         _IOW(IOC_TYPE_OTP,  0x13, OTP_STB_ROOT_KEY_S)
#define CMD_OTP_READSTBROOTKEY          _IOWR(IOC_TYPE_OTP, 0x14, OTP_STB_ROOT_KEY_S)
#define CMD_OTP_LOCKSTBROOTKEY          _IO(IOC_TYPE_OTP,   0x15)
#define CMD_OTP_GETSTBROOTKEYLOCKFLAG   _IOR(IOC_TYPE_OTP,  0x16, HI_BOOL)

#define CMD_OTP_WRITE_BIT               _IOW(IOC_TYPE_OTP,  0x17, OTP_ENTRY_S)
#define CMD_OTP_RESET                   _IO(IOC_TYPE_OTP,   0x18)

#define CMD_OTP_WRITE_ROOT_KEY          _IOW(IOC_TYPE_OTP,  0x1A, OTP_ROOT_KEY_S)
#define CMD_OTP_GET_ROOT_KEYLOCK        _IOWR(IOC_TYPE_OTP,  0x1B, OTP_ROOT_KEY_LOCK_S)

#define CMD_OTP_READ_BYTE               _IOWR(IOC_TYPE_OTP, 0x20, OTP_ENTRY_S)
#define CMD_OTP_READ_BITS_ONEBYTE       _IOWR(IOC_TYPE_OTP, 0x21, OTP_ENTRY_S)
#define CMD_OTP_WRITE_BITS_ONEBYTE      _IOW(IOC_TYPE_OTP,  0x22, OTP_ENTRY_S)

#ifdef __cplusplus
}
#endif
#endif /* __DRV_OTP_IOCTL_H__ */

