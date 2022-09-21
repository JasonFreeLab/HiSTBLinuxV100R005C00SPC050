/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name          : hi_gfx_mem.h
Version             : Initial Draft
Author              :
Created            : 2017/06/08
Description       : memory manage
                          CNcomment: 内存管理 CNend\n
Function List     :
History             :
Date                                 Author                     Modification
2017/06/08                    sdk                          Created file
******************************************************************************/

#ifndef  __HI_GFX_MEM_H__
#define  __HI_GFX_MEM_H__

/*********************************add include here******************************/
#include "hi_type.h"

/***************************** Macro Definition ******************************/
#define HI_GFX_RESERVE_Malloc(size,module)    BOOT_GFX_RESERVE_Alloc(size,module)
#define HI_GFX_MMZ_Malloc(size,module)        BOOT_GFX_MMZ_Alloc(size)
#define HI_GFX_MMZ_Free(phy)                  BOOT_GFX_MMZ_Free(phy)
#define HI_GFX_Malloc(size,module)            BOOT_GFX_Malloc(size)
#define HI_GFX_Free(phy)                      BOOT_GFX_Free(phy)

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

/*****************************************************************************
* func             : BOOT_GFX_RESERVE_Alloc
* description   : 分配保留内存
* retval           : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_RESERVE_Alloc(HI_U32 u32Size,HI_CHAR* pModuleName);


/*****************************************************************************
* func             : BOOT_GFX_MMZ_Alloc
* description   : 分配连续的物理地址，boot下连续地址也可以做虚拟地址，可直接读写,
                        这里使用保留内存
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_MMZ_Alloc(HI_U32 u32Size);


/*****************************************************************************
* func            : BOOT_GFX_MMZ_Free
* description  : 释放地址
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_MMZ_Free(HI_CHAR* pPhyAddr);


/*****************************************************************************
* func             : BOOT_GFX_Malloc
* description   : 使用malloc分配内存，使用完释放给其它功能使用,小内存
                        使用该接口比如handle等，减少内存碎片
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_Malloc(HI_U32 u32Size);


/*****************************************************************************
* func            : BOOT_GFX_Free
* description  : 释放地址
* retval          : HI_SUCCESS
* retval          : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_Free(HI_CHAR* pVirAddr);


#endif /*__HI_GFX_MEM_H__ */
