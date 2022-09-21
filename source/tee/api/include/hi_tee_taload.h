/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : hi_tee_taload.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2015-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2015-07-29  sdk  N/A               Create this file.
 ******************************************************************************/

#ifndef __HI_TEE_TALOAD_H__
#define __HI_TEE_TALOAD_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup      HI_TEE_TALOAD */
/** @{ */  /** <!-- [HI_TEE_TALOAD] */
/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup      HI_TEE_TALOAD */
/** @{ */  /** <!-- [HI_TEE_TALOAD] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @} */  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup      HI_TEE_TALOAD */
/** @{ */  /** <!-- [HI_TEE_TALOAD] */

int hisi_check_header(char *buf, unsigned int size);
int hisi_get_total_len(char *buf, unsigned int size, unsigned int *total_len);
int hisi_get_private_data(char *buf, unsigned int size, unsigned int *data_size, unsigned int *data_offest);

/** @} */  /** <!-- ==== API Declaration End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif /*__LOADER_OSAL_H__*/
