/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : tee_drv_i2c_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/07/23
  Description   :
  History       :
  1.Date        : 2017/07/23
    Modification: Created file

******************************************************************************/

#ifndef __TEE_DRV_I2C_IOCTL_H__
#define __TEE_DRV_I2C_IOCTL_H__


typedef struct hiI2C_DATA_S
{
    HI_U32    I2cNum;
    HI_U8     I2cDevAddr;
    HI_U32    I2cRegAddr;
    HI_U32    I2cRegCount;
    HI_U8    *pData;
    HI_U32    DataLen;
} I2C_DATA_S;

typedef struct hiI2C_RATE_S
{
    HI_U32 I2cNum;
    HI_U32 I2cRate;
} I2C_RATE_S;

#define TEE_IOC_NA        0U
#define TEE_IOC_W         1U
#define TEE_IOC_R         2U
#define TEE_IOC_RW        3U

#define TEE_I2C_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))

/* This is just magic number, need fix? */
#define IOC_TYPE_I2C    0x63

/* Ioctl definitions */
#define CMD_I2C_READ	TEE_I2C_IOC(TEE_IOC_RW, IOC_TYPE_I2C, 0x1, sizeof(I2C_DATA_S))
#define CMD_I2C_WRITE	TEE_I2C_IOC(TEE_IOC_RW, IOC_TYPE_I2C, 0x2, sizeof(I2C_DATA_S))
#define CMD_I2C_SET_RATE	TEE_I2C_IOC(TEE_IOC_R, IOC_TYPE_I2C, 0x3, sizeof(I2C_RATE_S))
#define CMD_I2C_INIT	TEE_I2C_IOC(TEE_IOC_R, IOC_TYPE_I2C, 0x4, 0)
#define CMD_I2C_DEINIT	TEE_I2C_IOC(TEE_IOC_R, IOC_TYPE_I2C, 0x5, 0)

#endif /* End of #ifndef __TEE_DRV_I2C_IOCTL_H__*/
