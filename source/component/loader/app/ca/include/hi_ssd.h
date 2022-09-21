/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : hi_ssd.h
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


#ifndef __HI_SSD_H__
#define __HI_SSD_H__

#include "hi_type.h"

HI_S32 HI_SSD_Init(HI_VOID);

HI_S32 HI_SSD_DeInit(HI_VOID);

HI_S32 HI_SSD_WholeImageVerify
(
    HI_U8*      pu8ImageData,
    HI_U32      u32ImageSize,
    HI_U8**     ppu8DataAddr,
    HI_U32*     pu32DataSize
);

HI_S32 HI_SSD_PartitionImageVerify
(
    HI_U8*      pu8PartitionName,
    HI_U64      u64FlashStartAddr,
    HI_U8*      pu8ImageData,
    HI_U32      u32ImageSize,
    HI_BOOL*    pbNeedUpgrade
);


#endif /* __HI_SSD_H__ */

