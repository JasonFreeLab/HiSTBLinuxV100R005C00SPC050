/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     :hi_tee_drv_cert.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __HI_TEE_DRV_CERT_H__
#define __HI_TEE_DRV_CERT_H__
#define HI_LOG_D_MODULE_ID HI_MODULE_ID_CERT
#include "hi_type.h"
#include "hi_tee_debug.h"
#include "hi_tee_cert.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define KLAD_CERT_CHECK_PORT(port_sel) \
    do{ \
        if ((port_sel < HI_TEE_CERT_KEY_PORT_DEMUX) || (port_sel > HI_TEE_CERT_KEY_PORT_UNKNOWN))\
        {\
            KLAD_ERR_PrintHex(port_sel); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_TARGET); \
            return HI_ERR_KLAD_INVALID_TARGET;\
        }\
    }while(0)

#define KLAD_CERT_CHECK_ENGINE(engine) \
    do{ \
        if ((engine < HI_TEE_CERT_TARGET_ENGINE_PAYLOAD_CSA2) || (engine >= HI_TEE_CERT_TARGET_ENGINE_BUTT)) \
        {\
            KLAD_ERR_PrintHex(engine); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_ENGINE); \
            return HI_ERR_KLAD_INVALID_ENGINE;\
        }\
    }while(0)


typedef enum
{
    CERT_CMD_DEFAULT     = 0x0,
    CERT_CMD_START       = 0x1,
    CERT_TYPE_BUTT,
} CERT_CMD_E;

typedef enum
{
    CERT_KEY_SEND_DEFAULT     = 0x0,
    CERT_KEY_SEND_DONE        = 0x1,
    CERT_KEY_SEND_BUTT,
} CERT_KEY_CTL_E;

typedef struct  hiCERT_DATA_S
{
    HI_U32 data[CERT_AKL_REG_DATA_NUM];
} CERT_DATA_S;

typedef struct
{
    HI_TEE_CERT_RES_HANDLE handle;
    HI_TEE_CERT_COMMAND cmd;
} CERT_CMD_CTL;

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* End of #ifndef __HI_TEE_DRV_CERT_H__*/
