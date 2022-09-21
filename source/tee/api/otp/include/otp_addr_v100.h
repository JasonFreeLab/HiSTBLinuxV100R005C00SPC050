/******************************************************************************

Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

******************************************************************************
File Name : mpi_otp_addr.h
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

#ifndef __MPI_OTP_ADDR_H__
#define __MPI_OTP_ADDR_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define OTP_ADDR_CHIPID                     0x68
#define OTP_ADDR_DIEID                      0xF0

#define OTP_ADDR_ANTIROLLBACK_NUMBER        (0x500)
#define ANTIROLLBACK_MAX_LEN                (0x7F)

#define OTP_ADDR_SECSTORE_ROOTKEY           (0x1d0)
#define OTP_ADDR_SECSTORE_ROOTKEY_LOCK      (0x1e)
#define OTP_ADDR_SECSTORE_ROOTKEY_CRC       (0x42e)
#define OTP_ADDR_SECSTORE_ROOTKEY_CRC_LOCK  (0x431)

#ifdef HI_TEE_OTP_HI3798CV200
/*only for hi3798cv200 chipset:
0x520-0x57f total 8*x byte. ta_id(4bytes) + sm_id(4bytes).
0x580-0x5ff total 8*x bytes. ta_cert_cersion(2bytes)+ta_version(6bytes).
            ignore trustzone lock flag,so use 8 bytes for each group*/
#define OTP_ADDR_TA1_CERT_VERSION           0x580
#define OTP_TA_CERT_VERSION_LEN             0x02
#define OTP_ADDR_TA1_VERSION                0x582
#define OTP_TA_VERSION_LEN                  0x06

#define OTP_ADDR_TA1_SEGMENTATIONID         0x520
#define OTP_TA_SEGMENTATIONID_LEN           0x08
#define OTP_TA_ID_LEN                       0x4
#define OTP_TA_SM_LEN                       0x4
#else
/*Except for hi3798cv200 chipset, only for vmx, 0x520-0x57f used for secure os anti-rollback,
   so we use 0x600-0x67f instead
0x520-0x57f total 8*x bytes. vmx ultra secure os anti-rollback.
0x580-0x5ff total 16*x byte. ta_id(4bytes) + sm_id(4bytes) + reserved(8bytes).
0x600-0x67f total 8*x bytes. ta_cert_cersion(2bytes)+ta_version(6bytes).*/

#ifdef HI_OTP_VERIMATRIX_ULTRA
#define OTP_ADDR_TA1_CERT_VERSION           0x600
#define OTP_TA_CERT_VERSION_LEN             0x02
#define OTP_ADDR_TA1_VERSION                0x602
#define OTP_TA_VERSION_LEN                  0x06

#define OTP_ADDR_TA1_SEGMENTATIONID         0x580
#define OTP_TA_SEGMENTATIONID_LEN           0x10
#define OTP_TA_ID_LEN                       0x4
#define OTP_TA_SM_LEN                       0x4
#else
/*Except for hi3798cv200 chipset, for others ca:
0x520-0x57f total 8*x bytes. ta_cert_cersion(2bytes)+ta_version(6bytes).
0x580-0x5ff total 16*x byte. ta_id(4bytes) + sm_id(4bytes) + reserved(8bytes).*/
#define OTP_ADDR_TA1_CERT_VERSION           0x520
#define OTP_TA_CERT_VERSION_LEN             0x02
#define OTP_ADDR_TA1_VERSION                0x522
#define OTP_TA_VERSION_LEN                  0x06

#define OTP_ADDR_TA1_SEGMENTATIONID         0x580
#define OTP_TA_SEGMENTATIONID_LEN           0x10
#define OTP_TA_ID_LEN                       0x4
#define OTP_TA_SM_LEN                       0x4
#endif

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _TEE_OTP_H__ */

