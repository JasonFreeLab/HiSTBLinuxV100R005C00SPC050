/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_drv_hal.c
Version           : Initial Draft
Author            :
Created          : 2017/07/05
Description     : ²Ù×÷¼Ä´æÆ÷
Function List   :


History           :
Date                     Author                Modification
2017/07/05            sdk                   Created file
******************************************************************************/



/*********************************add include here******************************/
#include "hi_jpeg_config.h"
#include "jpeg_drv_hal.h"
#include "hi_jpeg_reg.h"
#include "hi_jpeg_checkpara.h"

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/

static volatile HI_U32 *s_pu32JpgRegAddr = 0;

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/
HI_U32 jpeg_reg_read(HI_U32 offset)
{
    CHECK_JPEG_EQUAL_RETURN(0, s_pu32JpgRegAddr, 0);
    CHECK_JPEG_LESS_RETURN(JPGD_REG_LENGTH - 4,offset,0);

    return (*(volatile HI_U32 *)((s_pu32JpgRegAddr) + (offset) / 4));
}

HI_VOID  jpeg_reg_write(HI_U32 offset, HI_U32 value)
{
    CHECK_JPEG_EQUAL_UNRETURN(0, s_pu32JpgRegAddr);
    CHECK_JPEG_LESS_UNRETURN(JPGD_REG_LENGTH - 4,offset);

    (*(volatile HI_U32 *)((s_pu32JpgRegAddr) + (offset) / 4) = (value));

    return;
}

HI_VOID jpeg_reg_writebuf(const HI_VOID *pInMem,HI_S32 s32PhyOff,HI_U32 u32Bytes)
{
    HI_U32 u32Cnt = 0;
    CHECK_JPEG_EQUAL_UNRETURN(0, s_pu32JpgRegAddr);
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pInMem);
    CHECK_JPEG_LESS_UNRETURN(JPGD_REG_LENGTH - 4,(s32PhyOff + u32Bytes));

    for (u32Cnt = 0; u32Cnt < u32Bytes; u32Cnt += 4)
    {
        *(volatile int *)((s_pu32JpgRegAddr) + (s32PhyOff + u32Cnt) / 4) = *(int *)((char*)pInMem + u32Cnt);
    }

    return;
}

HI_VOID JPEG_HAL_Init(volatile HI_U32 *pu32JpegRegBase)
{
     s_pu32JpgRegAddr = pu32JpegRegBase;
}

HI_VOID JPEG_HAL_DInit(HI_VOID)
{
    s_pu32JpgRegAddr = 0;
}

HI_VOID DRV_JPEG_GetIntStatus(HI_U32 *pIntStatus)
{
    CHECK_JPEG_EQUAL_UNRETURN(NULL, pIntStatus);
    *pIntStatus = jpeg_reg_read(JPGD_REG_INT);
}

HI_VOID DRV_JPEG_ClearIntStatus(HI_U32 IntStatus)
{
    jpeg_reg_write(JPGD_REG_INT, IntStatus);
}

HI_VOID DRV_JPEG_SetIntMask(HI_U32 IntMask)
{
    jpeg_reg_write(JPGD_REG_INTMASK, IntMask);
}
