/******************************************************************************

Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

******************************************************************************
File Name : tee_otp.h
Version : Initial Draft
Author : Hisilicon multimedia software group
Created : 2016/06/08
Description :
History :
1.Date : 2016/06/08
Author :
Modification: Created file

*******************************************************************************/
/**
* \file
* \brief Describes the API about the otp.
CNcomment:Ã·π©OTP API CNend
*/

#ifndef _TEE_OTP_H__
#define _TEE_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define OTP_ADDR_CHIPID                     0xB0
#define OTP_ADDR_DIEID                      0x300

#define OTP_ADDR_TA1_CERT_VERSION           0x198
#define OTP_ADDR_TA2_CERT_VERSION           0x19E
#define OTP_ADDR_TA3_CERT_VERSION           0x1A4
#define OTP_ADDR_TA4_CERT_VERSION           0x1AA
#define OTP_ADDR_TA5_CERT_VERSION           0x1B0
#define OTP_ADDR_TA6_CERT_VERSION           0x1B6

#define OTP_TA_CERT_VERSION_LEN             0x02

#define OTP_ADDR_TA1_VERSION                0x19A
#define OTP_ADDR_TA2_VERSION                0x1A0
#define OTP_ADDR_TA3_VERSION                0x1A6
#define OTP_ADDR_TA4_VERSION                0x1AC
#define OTP_ADDR_TA5_VERSION                0x1B2
#define OTP_ADDR_TA6_VERSION                0x1B8

#define OTP_TA_VERSION_LEN                  0x06

#define OTP_ADDR_TA1_SEGMENTATIONID         0x800
#define OTP_ADDR_TA2_SEGMENTATIONID         0x810
#define OTP_ADDR_TA3_SEGMENTATIONID         0x820
#define OTP_ADDR_TA4_SEGMENTATIONID         0x830
#define OTP_ADDR_TA5_SEGMENTATIONID         0x840
#define OTP_ADDR_TA6_SEGMENTATIONID         0x850

#define OTP_TA_SEGMENTATIONID_LEN           0x10
#define OTP_TA_ID_LEN                       0x4
#define OTP_TA_SM_LEN                       0x4
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _TEE_OTP_H__ */

