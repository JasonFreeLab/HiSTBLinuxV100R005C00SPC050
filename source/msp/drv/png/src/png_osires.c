/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name   : png_hal.h
Version     : Initial Draft
Author      : sdk
Created     : 2010/10/11
Description : PNG osires layer code     CNcomment:PNG osires实现
Function List   :

History         :
Date                Author              Modification
2010/10/11      sdk       Created file
******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cplusplus */
#endif  /* __cplusplus */

//#include <linux/kcom.h>
//#include <kcom/mmz.h>
#include "hi_drv_mmz.h"
#include "hi_drv_png.h"
#include "hi_png_errcode.h"
#include "png_define.h"
#include "png_osires.h"
#include "hi_gfx_sys_k.h"

/* handle instance*/
static PNG_INSTANCE_S g_PngInstance[PNG_MAX_HANDLE];

/* handle lock */
HI_DECLARE_MUTEX(g_HandleMutex);

/********************************************************************************************
* func: handle init
* in:   none
* out:  none
* ret:  1--32   decoder handle
* ret:  HI_ERR_PNG_NOOPEN   not open devide
* ret:  HI_ERR_PNG_NOHANDLE no decoder resource
* others:   support 32 decoder at most
*********************************************************************************************/
HI_S32 PngOsiResInitHandle(HI_VOID)
{
    return HI_SUCCESS;
}

/********************************************************************************************
* func: handle deinit
* in:   none
* out:  none
* ret:   none
* others:   support 32 decoder at most
*********************************************************************************************/
HI_VOID PngOsiResDeinitHandle(HI_VOID)
{
    return;
}

/********************************************************************************************
* func: alloc handle
* in:   none
* out:  none
* ret:  1--32   decoder handle
* ret:  HI_ERR_PNG_NOHANDLE no handle resource
* others: Max handle count is 32
             CNcomment:最多支持创建32个handle
*********************************************************************************************/
HI_S32 PngOsiResAllocHandle(HI_PNG_HANDLE *ps32Handle)
{
    HI_U32 i = 0;
    HI_S32 s32Ret;

    if (HI_NULL == ps32Handle)
    {
        return HI_ERR_PNG_NULLPTR;
    }

    PNG_DOWN_INTERRUPTIBLE(&g_HandleMutex, s32Ret);
    if (s32Ret < 0)
    {
        return HI_ERR_PNG_INTERRUPT;
    }

    /* find handle */
    for (i = 0; i < PNG_MAX_HANDLE; i++)
    {
        if (!g_PngInstance[i].bInUse)
        {
            break;
        }
    }

    /* no handle */
    if (PNG_MAX_HANDLE == i)
    {
        PNG_WARNING("No handle!\n");
        PNG_UP(&g_HandleMutex);
        return HI_ERR_PNG_NOHANDLE;
    }

    HI_GFX_Memset(&g_PngInstance[i], 0, sizeof(PNG_INSTANCE_S));

    g_PngInstance[i].bInUse = HI_TRUE;
    sema_init(&g_PngInstance[i].stInstanceLock, 1);

    PNG_UP(&g_HandleMutex);

    *ps32Handle = (i + 1);

    return HI_SUCCESS;
}

/********************************************************************************************
* func: release handle
* in:   s32Handle   decoder handle
* out:  none
* ret:  HI_SUCCESS  success
* ret:  HI_ERR_PNG_INVALID_HANDLE   invalid handle
* others:
*********************************************************************************************/
HI_S32 PngOsiResReleaseHandle(HI_PNG_HANDLE s32Handle)
{
    HI_S32 s32Ret;

    if ((s32Handle <= 0) || (s32Handle > PNG_MAX_HANDLE))
    {
        PNG_ERROR("Invalid handle:%d!\n", s32Handle);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    PNG_DOWN_INTERRUPTIBLE(&g_HandleMutex, s32Ret);

    if (!g_PngInstance[s32Handle - 1].bInUse)
    {
        PNG_ERROR("handle %d not in use!\n", s32Handle);
        PNG_UP(&g_HandleMutex);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    /* clear instance*/
    HI_GFX_Memset(&g_PngInstance[s32Handle - 1], 0, sizeof(PNG_INSTANCE_S));
    PNG_UP(&g_HandleMutex);

    return HI_SUCCESS;
}

/********************************************************************************************
* func: get handle instance
* in:   s32Handle   decoder handle
* out:  none
* ret:  HI_SUCCESS  success
* ret:  HI_ERR_PNG_INVALID_HANDLE   invalid handle
* others:
*********************************************************************************************/
HI_S32 PngOsiResGetInstance(HI_PNG_HANDLE s32Handle, PNG_INSTANCE_S **ppstInstance)
{
    HI_S32 s32Ret;

    if ((s32Handle <= 0) || (s32Handle > PNG_MAX_HANDLE))
    {
        //PNG_ERROR("Invalid handle:%d!\n", s32Handle);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    PNG_DOWN_INTERRUPTIBLE(&g_HandleMutex, s32Ret);

    if (!g_PngInstance[s32Handle - 1].bInUse)
    {
        //PNG_ERROR("handle %d not in use!\n", s32Handle);
        PNG_UP(&g_HandleMutex);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    *ppstInstance = &g_PngInstance[s32Handle - 1];

    PNG_UP_INT(&g_HandleMutex);

    return HI_SUCCESS;
}

/********************************************************************************************
* func: allock mem
* in:   pName mem name
* in:   u32Size mem size
* in:   u32Align align setting
* out:  pu32Phyaddr starting of memory
* ret:  HI_SUCCESS  success
* ret:  HI_ERR_PNG_NOMEM    no memory
* others:
*********************************************************************************************/
HI_S32 PngOsiResAllocMem(HI_UCHAR *pName, HI_U32 u32Size, HI_U32 u32Align, HI_U32 *pu32Phyaddr)
{
    HI_BOOL bMmu = HI_TRUE;

    *pu32Phyaddr = HI_GFX_AllocMem(pName, "iommu", u32Size, &bMmu);
    if (0 == *pu32Phyaddr)
    {
        PNG_ERROR("No mem!\n");
        return HI_ERR_PNG_NOMEM;
    }

    return HI_SUCCESS;
}

/********************************************************************************************
* func: release memory
* in:   u32Phyaddr release physical address
* out:  none
* ret:  none
* others:
*********************************************************************************************/
HI_VOID PngOsiResReleaseMem(HI_U32 u32Phyaddr)
{
    if (u32Phyaddr)
    {
        HI_GFX_FreeMem(u32Phyaddr, HI_TRUE);
    }

    return;
}

/* default stream buffer size*/
#define PNG_BUF_DEFAULTSIZE (128 * 1024)

#ifdef HIPNG_STREAMBUF_KERNEL
/********************************************************************************************
* func: alloc buf
* in:   pu32Size:    buffer size
* out:  pu32Phyaddr: starting address
* out:  pu32Size:    actual buffer size
* ret:  HI_SUCCESS: success
* ret:  HI_ERR_PNG_NOMEM:   no mem
* others:
*********************************************************************************************/
HI_S32 PngOsiResAllocBuf(HI_U32 *pu32Phyaddr, HI_U32 *pu32Size)
{
    HI_S32 s32Ret = HI_SUCCESS;

    /* if size is 0, then use default size*/
    if (*pu32Size <= PNG_BUF_DEFAULTSIZE)
    {
        *pu32Size = PNG_BUF_DEFAULTSIZE;
    }

    s32Ret = PngOsiResAllocMem("PNG_StreamBuf", *pu32Size, 16, pu32Phyaddr);
    if (s32Ret < 0)
    {
        return s32Ret;
    }

    *pu32Size = (*pu32Size + 0xf) & ~0xf;

    return HI_SUCCESS;
}

/********************************************************************************************
* func: release buf
* in:   u32Phyaddr : starting addres
* out:  none
* ret:  none
* others:
*********************************************************************************************/
HI_VOID PngOsiResReleaseBuf(HI_U32 u32Phyaddr)
{

    PngOsiResReleaseMem(u32Phyaddr);

    return;
}
#endif

HI_VOID PngOsiShowInstanceState(struct seq_file *p)
{
    HI_U32 i;

    PROC_PRINT(p, "***********png state start******************\n");
    for (i = 0; i < PNG_MAX_HANDLE; i++)
    {
        if (!g_PngInstance[i].bInUse)
        {
            continue;
        }

        PROC_PRINT(p, "handle:%d\n", i);
        PROC_PRINT(p, "state:%d\n", g_PngInstance[i].eState);
        PROC_PRINT(p, "sync:%d\n", g_PngInstance[i].bSync);

    }
    PROC_PRINT(p, "***********png state end******************\n");

}

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */
