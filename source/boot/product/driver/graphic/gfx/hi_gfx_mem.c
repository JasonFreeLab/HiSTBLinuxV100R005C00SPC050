/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_mem.c
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : memory manage
                          CNcomment: 内存管理 CNend\n
Function List     :
History             :
Date                              Author                     Modification
2017/06/08                    sdk                          Created file
******************************************************************************/



/*********************************add include here******************************/
#include "hi_gfx_mem.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_sys.h"

#include "hi_common.h"
#include "hi_drv_pdm.h"
/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/



/**********************       API realization       **************************/

/*****************************************************************************
* func            : BOOT_GFX_RESERVE_Alloc
* description  : 分配保留内存
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_RESERVE_Alloc(HI_U32 u32Size,HI_CHAR* pModuleName)
{
    HI_S32 Ret = HI_SUCCESS;
    MMZ_BUFFER_S stMBuf;

    if (0 == u32Size)
    {
       return NULL;
    }
    HI_GFX_Memset(&stMBuf,0x0,sizeof(stMBuf));

    Ret = HI_DRV_PDM_AllocReserveMem(pModuleName, u32Size, &stMBuf.u32StartPhyAddr);
    if ((HI_SUCCESS != Ret) || (0 == stMBuf.u32StartPhyAddr))
    {
        return NULL;
    }

    return (HI_CHAR*)stMBuf.u32StartPhyAddr;
}

/*****************************************************************************
* func            : BOOT_GFX_MMZ_Alloc
* description  : 分配连续的物理地址，boot下连续地址也可以做虚拟地址，可直接读写
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_MMZ_Alloc(HI_U32 u32Size)
{
    HI_S32 s32Ret = HI_SUCCESS;
    MMZ_BUFFER_S stMBuf;

    if (0 == u32Size)
    {
       return NULL;
    }
    HI_GFX_Memset(&stMBuf,0x0,sizeof(stMBuf));

    s32Ret = HI_MEM_Alloc(&stMBuf.u32StartPhyAddr, u32Size);
    if ((HI_SUCCESS != s32Ret) || (0 == stMBuf.u32StartPhyAddr))
    {
        return NULL;
    }

    return (HI_CHAR*)stMBuf.u32StartPhyAddr;
}


/*****************************************************************************
* func            : BOOT_GFX_MMZ_Free
* description  : 释放地址
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_MMZ_Free(HI_CHAR* pPhyAddr)
{
   HI_UNUSED(*pPhyAddr);
   return;
}


/*****************************************************************************
* func            : BOOT_GFX_Malloc
* description  : 使用malloc分配内存，使用完释放给其它功能使用,小内存
                       使用该接口比如handle等，减少内存碎片
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_Malloc(HI_U32 u32Size)
{
    if (0 == u32Size)
    {
        return NULL;
    }

    return (HI_CHAR*)malloc(u32Size);
}

/*****************************************************************************
* func            : BOOT_GFX_Free
* description  : 释放地址
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_Free(HI_CHAR* pVirAddr)
{
    if (NULL != pVirAddr)
    {
        free(pVirAddr);
    }

    return;
}
