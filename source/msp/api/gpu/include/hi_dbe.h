/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hi_dbe.h
Version             : Initial Draft
Author              :
Created             : 2015/09/29
Description         :
Function List       :
History             :
Date                       Author                   Modification
2015/09/29                 00270170                 Created file
******************************************************************************/

#ifndef _LINUX_HI_DMA_BUF_EXPORTER_H_
#define _LINUX_HI_DMA_BUF_EXPORTER_H_

#include <linux/types.h>
#include <asm/ioctl.h>

struct hidbe_ioctl_wrap
{
    __u64 dbe_phyaddr;
    __u64 dbe_size;       /* size of buffer to allocate, in pages */
    __u8 dbe_smmuflag;    /* when it is 1, dbe_phyaddr will be smmu address,
                             when it is 0, dbe_phyaddr will be physical address */
};

#define DBE_IOCTL_BASE 'E'

/* wrap physical address into dmabuf fd */
#define DBE_COMMAND_WRAP                _IOR(DBE_IOCTL_BASE, 0x00, struct hidbe_ioctl_wrap)

/* wrap physical or smmu address into dmabuf fd */
#define DBE_COMMAND_WRAP_ADDRESS        _IOR(DBE_IOCTL_BASE, 0x01, struct hidbe_ioctl_wrap)

#endif /* _LINUX_DMA_BUF_TEST_EXPORTER_H_ */
