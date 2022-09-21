/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hi_gfx_comm.h
Version           : version 1.0
Author            :
Created          : 2017/07/05
Description     : 这个头文件不要多个地方引用，否则代码
                        会变大，最好只有内存分配的地方包含CNend\n
Function List   :

History           :
Date                       Author                Modification
2017/07/05             sdk                     Created
******************************************************************************/

#ifndef  _HI_GFX_COMM_H_
#define  _HI_GFX_COMM_H_

/***************************** SDK Version Macro Definition *********************/


/*********************************add include here******************************/
#if defined(CONFIG_GFX_MEM_MMZ)
   #include <string.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include <fcntl.h>
   #include <errno.h>
   #include <sys/ioctl.h>
   #include <sys/syscall.h>
   #include <sys/mman.h>
   #include "mpi_mmz.h"
#else
   #include <sys/ioctl.h>
   #include <sys/syscall.h>
   #include <sys/mman.h>
   #include <fcntl.h>
   #include <errno.h>
   #include <string.h>
   #include <stdlib.h>
   #include <sys/types.h>
   #include <sys/stat.h>
#endif

#include "hi_type.h"
#include "hi_gfx_sys.h"

/***************************** Macro Definition ******************************/
#if defined(CONFIG_GFX_MEM_ION)
    #define ION_IOC_MAGIC                 'I'
    #define ION_IOC_ALLOC                 _IOWR(ION_IOC_MAGIC, 0,  struct ion_allocation_data)
    #define ION_IOC_FREE                  _IOWR(ION_IOC_MAGIC, 1,  struct ion_handle_data)
    #define ION_IOC_MAP                   _IOWR(ION_IOC_MAGIC, 2,  struct ion_fd_data)
    #define ION_IOC_SYNC                  _IOWR(ION_IOC_MAGIC, 7,  struct ion_fd_data)
    #define ION_IOC_PHYS                  _IOWR(ION_IOC_MAGIC, 8,  struct ion_phys_data)
    #define ION_IOC_MAP_IOMMU             _IOWR(ION_IOC_MAGIC, 9,  struct ion_map_iommu_data)
    #define ION_IOC_UNMAP_IOMMU           _IOWR(ION_IOC_MAGIC, 10, struct ion_map_iommu_data)
    #define ION_FLAG_CACHED               1
    #define ION_FLAG_CACHED_NEEDS_SYNC    2
    #define ION_HEAP_SYSTEM_MASK          (1 << ION_HEAP_TYPE_SYSTEM)
    #define ION_HEAP_SYSTEM_CONTIG_MASK   (1 << ION_HEAP_TYPE_SYSTEM_CONTIG)
    #define ION_HEAP_CARVEOUT_MASK        (1 << ION_HEAP_TYPE_CARVEOUT)
    #define ION_HEAP_TYPE_DMA_MASK        (1 << ION_HEAP_TYPE_DMA)
    #define ION_HEAP_CMA_MASK             (1 << ION_HEAP_ID_CMA)
    #define ION_NUM_HEAP_IDS              (sizeof(unsigned int) * 8)
#endif

/*************************** Enum Definition ****************************/
typedef enum tagHIGFX_MODE_ID_E
{
    HIGFX_TDE_ID = 0,   /**<-- TDE ID      >**/
    HIGFX_JPGDEC_ID,    /**<-- JPEG DECODE ID   >**/
    HIGFX_JPGENC_ID,    /**<-- JPEG_ENCODE ID  >**/
    HIGFX_FB_ID,        /**<-- FRAMEBUFFER ID  >**/
    HIGFX_PNG_ID,       /**<-- PNG ID >**/
    HIGFX_BUTT_ID,
}HIGFX_MODE_ID_E;

typedef enum tagHIGFX_MODE_MEM_E
{
    HIGFX_MODE_ALLOC = 0,
    HIGFX_MODE_FREE,
    HIGFX_MODE_MAP,
    HIGFX_MODE_UNMAP,
    HIGFX_MODE_BUTT,
}HIGFX_MODE_MEM_E;

/*************************** Structure Definition ****************************/
#ifdef CONFIG_GFX_MEM_ION
    typedef int ion_user_handle_t;
    typedef unsigned long ion_phys_addr_t;
    typedef struct
    {
        ion_user_handle_t pIonHandle;
        HI_S32 s32MapFd;
        HI_U32 u32Phyaddr;
        HI_VOID *pViraddr;
        HI_U32 u32Size;
    }HI_GFX_MEM_HANDLE_S;

    struct ion_allocation_data
    {
        size_t len;
        size_t align;
        unsigned int heap_id_mask;
        unsigned int flags;
        ion_user_handle_t handle;
    };

    struct ion_fd_data
    {
        ion_user_handle_t handle;
        int fd;
    };

    struct ion_handle_data
    {
        ion_user_handle_t handle;
    };

    struct ion_phys_data
    {
        ion_user_handle_t handle;
        size_t len;
        ion_phys_addr_t phys_addr;
    };

    struct iommu_map_format
    {
        unsigned long iova_start;
        unsigned long iova_size;
        unsigned long iommu_ptb_base;
        unsigned long iommu_iova_base;
        unsigned long phys_page_line;
        unsigned long virt_page_line;
        unsigned long is_tile;
    };

    struct ion_map_iommu_data
    {
        ion_user_handle_t handle;
        struct iommu_map_format format;
    };

    enum ion_heap_type
    {
        ION_HEAP_TYPE_SYSTEM,
        ION_HEAP_TYPE_SYSTEM_CONTIG,
        ION_HEAP_TYPE_CARVEOUT,
        ION_HEAP_TYPE_CHUNK,
        ION_HEAP_TYPE_DMA,
        ION_HEAP_ID_CMA = 15,
        ION_NUM_HEAPS   = 31,
    };
#endif


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/
static inline HI_VOID HI_GFX_LOG_Display(HI_U32 u32Size, HI_U32 u32VirBuf, HI_U32 u32Buf, const HI_CHAR* pBufName, HIGFX_MODE_MEM_E eMemMod)
{
    HI_UNUSED(u32Size);
    HI_UNUSED(u32VirBuf);
    HI_UNUSED(u32Buf);
    HI_UNUSED(pBufName);
    HI_UNUSED(eMemMod);
#ifdef CFG_HI_GFX_DEBUG_LOG_SUPPORT
    GFX_Printf("\n==============================================================\n");
    switch (eMemMod)
    {
        case HIGFX_MODE_ALLOC:
            if (NULL != pBufName)
            {
                GFX_Printf("alloc %s buffer information\n",pBufName);
            }
            else
            {
                GFX_Printf("alloc buffer information\n");
            }
            GFX_Printf("buffer[0x%x  0x%x] size = %d\n",u32Buf,u32Buf + u32Size,u32Size);
            break;
        case HIGFX_MODE_FREE:
            if (NULL != pBufName)
            {
                GFX_Printf("free %s buffer information\n",pBufName);
            }
            else
            {
                GFX_Printf("free buffer information\n");
            }
            GFX_Printf("buffer 0x%x\n",u32Buf);
            break;
         case HIGFX_MODE_MAP:
            if (NULL != pBufName)
            {
                GFX_Printf("map %s buffer information\n",pBufName);
            }
            else
            {
                GFX_Printf("map buffer information\n");
            }
            GFX_Printf("buffer 0x%x vir buffer 0x%x\n",u32Buf,u32VirBuf);
            break;
         case HIGFX_MODE_UNMAP:
            if (NULL != pBufName)
            {
                GFX_Printf("unmap %s buffer information\n",pBufName);
            }
            else
            {
                GFX_Printf("unmap buffer information\n");
            }
            GFX_Printf("buffer 0x%x\n",u32Buf);
            break;
         default:
            break;
    }
    GFX_Printf("==============================================================\n");
#endif
    return;
}


#ifdef CONFIG_GFX_MEM_MMZ
static inline HI_S32 HI_GFX_FreeMem(HI_U32 u32PhyAddr, HI_BOOL bMmu)
{
    HI_S32 Ret = HI_SUCCESS;

    if (0 == u32PhyAddr)
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (bMmu)
    {
        Ret = HI_MPI_SMMU_Delete(u32PhyAddr);
    }
    else
#endif
    {
        Ret = HI_MPI_MMZ_Delete(u32PhyAddr);
    }

    HI_GFX_LOG_Display(0,0,u32PhyAddr,NULL,HIGFX_MODE_FREE);

    return Ret;
}


static inline HI_U32 HI_GFX_AllocMem(HI_U32 u32Size, HI_U32 u32Align, HI_CHAR* pZoneName, HI_CHAR *pName, HI_BOOL *pbMmu)
{
    HI_U32 u32PhyAddr = 0;

#ifdef CONFIG_GFX_256BYTE_ALIGN
    HI_U32 u32MMZAlign  = 256;
#else
    HI_U32 u32MMZAlign  = u32Align;
#endif
    HI_UNUSED(pZoneName);

    if ((NULL == pName) || (NULL == pbMmu) || (0 == u32Size))
    {
        GFX_Printf("=====the input para is null!\n");
        return 0;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if ((NULL != pZoneName) && (0 == strncmp(pZoneName, "iommu", strlen("iommu"))))
    {
        *pbMmu = HI_TRUE;
        u32PhyAddr = HI_MPI_SMMU_New(pName, u32Size);
    }
    else
#endif
    {
        *pbMmu = HI_FALSE;
        u32PhyAddr = HI_MPI_MMZ_New(u32Size, u32MMZAlign,NULL,pName);
    }

    HI_GFX_LOG_Display(u32Size,0,u32PhyAddr,pName,HIGFX_MODE_ALLOC);

    return u32PhyAddr;
}

static inline HI_VOID *HI_GFX_Map(HI_U32 u32PhyAddr, HI_BOOL bMmu)
{
    if (0 == u32PhyAddr)
    {
        return NULL;
    }

    HI_GFX_LOG_Display(0,0,u32PhyAddr,0,HIGFX_MODE_MAP);

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (bMmu)
    {
        return HI_MPI_SMMU_Map(u32PhyAddr, HI_FALSE);
    }
#endif

    return HI_MPI_MMZ_Map(u32PhyAddr, HI_FALSE);
}

static inline HI_VOID *HI_GFX_MapCached(HI_U32 u32PhyAddr, HI_BOOL bMmu)
{
    if (0 == u32PhyAddr)
    {
        return NULL;
    }

    HI_GFX_LOG_Display(0,0,u32PhyAddr,0,HIGFX_MODE_MAP);

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (bMmu)
    {
        return HI_MPI_SMMU_Map(u32PhyAddr, HI_TRUE);
    }
#endif

    return HI_MPI_MMZ_Map(u32PhyAddr, HI_TRUE);
}


static inline HI_S32 HI_GFX_Unmap(HI_U32 u32PhyAddr, HI_BOOL bMmu)
{
    if (0 == u32PhyAddr)
    {
        return HI_FAILURE;
    }

    HI_GFX_LOG_Display(0,0,u32PhyAddr,0,HIGFX_MODE_UNMAP);

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (bMmu)
    {
        return HI_MPI_SMMU_Unmap(u32PhyAddr);
    }
#endif

    return HI_MPI_MMZ_Unmap(u32PhyAddr);
}

static inline HI_S32 HI_GFX_Flush(HI_U32 u32PhyAddr, HI_BOOL bMmu)
{
    if (0 == u32PhyAddr)
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (bMmu)
    {
        return HI_MPI_SMMU_Flush(u32PhyAddr);
    }
#endif

    return HI_MPI_MMZ_Flush(u32PhyAddr);
}


static inline HI_S32 HI_GFX_GetPhyaddr(HI_VOID *pVir, HI_U32 *pPhyaddr, HI_U32 *pu32Size, HI_BOOL *pbMmu)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNUSED(pbMmu);

    if ((NULL == pVir) || (NULL == pPhyaddr))
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    Ret = HI_MPI_SMMU_GetSmmuAddrByMapAddr(pVir,pPhyaddr,pu32Size);
    *pbMmu = HI_TRUE;
#else
    Ret = HI_MPI_MMZ_GetPhyAddr(pVir,pPhyaddr,pu32Size);
    *pbMmu = HI_FALSE;
#endif

    return Ret;
}


#elif defined(CONFIG_GFX_MEM_ION)

/***************************************************************************
* func             : gfx_mem_open
* description   : open ion device
                         CNcomment: 打开ion设备 CNend\n
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_mem_open()
{
    int fd = open("/dev/ion", O_RDWR, S_IRUSR);
    if (fd < 0)
    {
         GFX_Printf("open /dev/ion failed!\n");
    }

    return fd;
}

/***************************************************************************
* func          : gfx_mem_close
* description : close ion device
                       CNcomment: 关闭ion设备 CNend\n
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:     : NA
****************************************************************************/
static inline HI_VOID gfx_mem_close(int fd)
{
    if (fd >= 0)
    {
       close(fd);
    }
}


/***************************************************************************
* func             : gfx_ion_ioctl
* description   : the ion ioctl
                         CNcomment: ioctl操作 CNend\n
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_ion_ioctl(int fd, int req, void *arg)
{
    int ret = 0;

    if (fd < 0)
    {
       return HI_FAILURE;
    }

    ret = ioctl(fd, req, arg);
    if (ret < 0)
    {
       GFX_Printf("ioctl %x failed with code %d\n", req,ret);
       return HI_FAILURE;
    }

    return ret;
}

/***************************************************************************
* func             : gfx_ion_alloc
* description   : alloc mem
                        CNcomment: 内存分配 CNend\n
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_ion_alloc(int fd, size_t len, size_t align, unsigned int heap_mask, unsigned int flags, ion_user_handle_t *handle)
{
    int ret = 0;
    struct ion_allocation_data data =
        {
            .len   = len,
            .align = align,
            .heap_id_mask = heap_mask,
            .flags = flags,
        };

    ret = gfx_ion_ioctl(fd, ION_IOC_ALLOC, &data);
    if (ret < 0)
    {
       return ret;
    }

    *handle = data.handle;

    return ret;
}

/***************************************************************************
* func            : gfx_ion_free
* description  : fremm mem
                        CNcomment: 内存释放 CNend\n
* retval         : HI_SUCCESS 成功
* retval         : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_ion_smmu_free(int fd, ion_user_handle_t handle, unsigned long Phyaddr)
{
#ifdef CONFIG_GFX_MMU_SUPPORT
    struct ion_map_iommu_data map_iommu;

    HI_GFX_Memset(&map_iommu, 0, sizeof(struct ion_map_iommu_data));
    map_iommu.handle            = handle;
    map_iommu.format.iova_start = Phyaddr;

    return gfx_ion_ioctl(fd, ION_IOC_UNMAP_IOMMU, &map_iommu);
#else
    HI_UNUSED(fd);
    HI_UNUSED(handle);
    HI_UNUSED(Phyaddr);
    return HI_SUCCESS;
#endif
}

/***************************************************************************
* func             : gfx_ion_free
* description   : fremm mem
                        CNcomment: 内存释放 CNend\n
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_ion_free(int fd, ion_user_handle_t handle)
{
    struct ion_handle_data data =
        {
             .handle = handle,
        };

    return gfx_ion_ioctl(fd, ION_IOC_FREE, &data);
}


/***************************************************************************
* func             : gfx_ion_phys
* description   : get phy ddr
                        CNcomment: 获取连续的物理地址 CNend\n
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_ion_phys(int fd, ion_user_handle_t handle, HI_U32 *phys_addr, HI_U32 *len)
{
    int ret = 0;

    struct ion_phys_data data =
        {
            .handle = handle,
        };

    ret = gfx_ion_ioctl(fd, ION_IOC_PHYS, &data);
    if (ret < 0)
    {
       return ret;
    }

    *phys_addr = data.phys_addr;
    *len = data.len;

    return ret;
}

/***************************************************************************
* func             : gfx_ion_smmu
* description   : get smmu ddr
                        CNcomment: 获取smmu地址 CNend\n
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_ion_smmu(int fd, ion_user_handle_t handle, HI_U32 *phys_addr, HI_U32 *len)
{
    int ret = 0;
    struct ion_map_iommu_data map_iommu;

    HI_GFX_Memset(&map_iommu, 0, sizeof(struct ion_map_iommu_data));
    map_iommu.handle = handle;

    ret = gfx_ion_ioctl(fd, ION_IOC_MAP_IOMMU, &map_iommu);
    if (ret < 0)
    {
        return ret;
    }

    *phys_addr = map_iommu.format.iova_start;
    *len       = map_iommu.format.iova_size;

    return ret;
}

/***************************************************************************
* func             : gfx_ion_map
* description   : map phy to vir
                         CNcomment: 内存映射 CNend\n
* retval           : HI_SUCCESS 成功
* retval           : HI_FAILURE 失败
* others:        : NA
****************************************************************************/
static inline HI_S32 gfx_ion_map(int fd, ion_user_handle_t handle, size_t length, int prot, int flags, off_t offset, unsigned char **ptr, int *map_fd)
{
    int ret = 0;
    struct ion_fd_data data =
        {
            .handle = handle,
        };

    if (length <= 0)
    {
       GFX_Printf("map length is zero\n");
       return -EINVAL;
    }

    ret = gfx_ion_ioctl(fd, ION_IOC_MAP, &data);
    if (ret < 0)
    {
        return ret;
    }

    *map_fd = data.fd;
    if (*map_fd < 0)
    {
        GFX_Printf("map ioctl returned negative fd\n");
        return -EINVAL;
    }

    *ptr = mmap(NULL, length, prot, flags, *map_fd, offset);
    if (*ptr == MAP_FAILED)
    {
        GFX_Printf("mmap failed\n");
        close(data.fd);
        *ptr = NULL;
        return HI_FAILURE;
    }

    return ret;
}


/***************************************************************************
* func             : gfx_ion_sync_fd
* description   : sync
                         CNcomment: 同步 CNend\n
* retval          : HI_SUCCESS 成功
* retval          : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 gfx_ion_sync_fd(int fd, int handle_fd)
{
    struct ion_fd_data data =
    {
        .fd = handle_fd,
    };

    return gfx_ion_ioctl(fd, ION_IOC_SYNC, &data);
}


static inline HI_S32 HI_GFX_FreeMem(HI_S32 s32MMZDev,HI_U32 u32Phyaddr, HI_VOID *pMemHandle, HI_BOOL bMmu)
{
    HI_S32 Ret = HI_SUCCESS;

    HI_UNUSED(u32Phyaddr);

    HI_GFX_LOG_Display(0,0,u32Phyaddr,0,HIGFX_MODE_FREE);

    if (0 != u32Phyaddr)
    {
       if (bMmu)
       {
          Ret = gfx_ion_smmu_free(s32MMZDev, ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->pIonHandle,u32Phyaddr);
       }

       Ret |= gfx_ion_free(s32MMZDev, ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->pIonHandle);
       if (Ret)
       {
           return HI_FAILURE;
       }
    }

    if (NULL == pMemHandle)
    {
       return HI_SUCCESS;
    }

    free(pMemHandle);
    pMemHandle = NULL;

    return HI_SUCCESS;
}

static inline HI_U32 HI_GFX_AllocMem(HI_S32 s32MMZDev,HI_U32 u32Size , HI_U32 u32Align, HI_CHAR* pZoneName, HI_CHAR *pName, HI_VOID **ppMemHandle, HI_BOOL *pbMmu)
{
    HI_GFX_MEM_HANDLE_S *pstMemHandle = NULL;
    HI_U32 u32Phyaddr = 0;
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32MMZAlign = u32Align;
    HI_S32 s32MemSize = 0;

    HI_UNUSED(pName);

#ifdef CONFIG_GFX_256BYTE_ALIGN
    u32MMZAlign = 256;
#endif

    if ((NULL == ppMemHandle) || (NULL == pbMmu))
    {
       return 0;
    }

    s32MemSize = sizeof(HI_GFX_MEM_HANDLE_S);
    pstMemHandle = (HI_GFX_MEM_HANDLE_S *)malloc(s32MemSize);
    if (NULL == pstMemHandle)
    {
        *ppMemHandle = NULL;
        return 0;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if ((NULL != pZoneName) && (0 == strncmp(pZoneName, "iommu", strlen("iommu"))))
    {
       Ret = gfx_ion_alloc(s32MMZDev, u32Size, u32MMZAlign, ION_HEAP_SYSTEM_MASK, ION_FLAG_CACHED | ION_FLAG_CACHED_NEEDS_SYNC, &(pstMemHandle->pIonHandle));
    }
    else
#endif
    {
        Ret = gfx_ion_alloc(s32MMZDev, u32Size, u32MMZAlign, ION_HEAP_CMA_MASK, ION_FLAG_CACHED | ION_FLAG_CACHED_NEEDS_SYNC, &(pstMemHandle->pIonHandle));
    }

    if (HI_SUCCESS != Ret)
    {
        GFX_Printf("ion_alloc failed!size:0x%x\n", u32Size);
        free(pstMemHandle);
        *ppMemHandle = NULL;
        return 0;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if ((NULL != pZoneName) && (0 == strncmp(pZoneName, "iommu", strlen("iommu"))) )
    {
        *pbMmu = HI_TRUE;
        Ret = gfx_ion_smmu(s32MMZDev, pstMemHandle->pIonHandle, &u32Phyaddr, &u32Size);
        if (Ret)
        {
            GFX_Printf("ion_phys failed!\n");
            gfx_ion_free(s32MMZDev, pstMemHandle->pIonHandle);
            free(pstMemHandle);
            *ppMemHandle = NULL;
            return 0;
        }
    }
    else
#endif
    {
        *pbMmu = HI_FALSE;
        Ret = gfx_ion_phys(s32MMZDev, pstMemHandle->pIonHandle, &u32Phyaddr, &u32Size);
        if (Ret)
        {
            GFX_Printf("ion_phys failed!\n");
            gfx_ion_free(s32MMZDev, pstMemHandle->pIonHandle);
            free(pstMemHandle);
            *ppMemHandle = NULL;
            return 0;
        }
    }

    pstMemHandle->u32Phyaddr = u32Phyaddr;
    pstMemHandle->u32Size    = u32Size;
    *ppMemHandle = pstMemHandle;

    HI_GFX_LOG_Display(u32Size,0,u32Phyaddr,pName,HIGFX_MODE_ALLOC);

    return u32Phyaddr;
}


static inline HI_VOID *HI_GFX_Map(HI_S32 s32MMZDev,HI_U32 u32PhyAddr, HI_VOID *pMemHandle)
{
    unsigned char *ptr = HI_NULL;
    HI_S32 Ret = HI_SUCCESS;

    HI_UNUSED(u32PhyAddr);

    if (NULL == pMemHandle)
    {
        return NULL;
    }

    Ret = gfx_ion_map(s32MMZDev,                                       \
                      ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->pIonHandle, \
                      ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->u32Size,    \
                      PROT_READ | PROT_WRITE, MAP_SHARED,              \
                      0,                                               \
                      &ptr,                                            \
                      &(((HI_GFX_MEM_HANDLE_S *)pMemHandle)->s32MapFd));
    if (Ret)
    {
        GFX_Printf("ion_map failed!\n");
        return NULL;
    }

    ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->pViraddr = ptr;

    HI_GFX_LOG_Display(0,(unsigned long)ptr,u32PhyAddr,NULL,HIGFX_MODE_MAP);

    return ptr;
}


static inline HI_VOID *HI_GFX_MapCached(HI_S32 s32MMZDev,HI_U32 u32PhyAddr, HI_VOID *pMemHandle)
{
    return HI_GFX_Map(s32MMZDev,u32PhyAddr,pMemHandle);
}

static inline HI_S32 HI_GFX_Unmap(HI_S32 s32MMZDev,HI_U32 u32PhyAddr, HI_VOID *pMemHandle)
{
    HI_U32 u32Size = 0;
    HI_S32 Ret  = 0;
    HI_UNUSED(u32PhyAddr);
    HI_UNUSED(s32MMZDev);

    if (NULL == pMemHandle)
    {
        return HI_FAILURE;
    }

    u32Size = ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->u32Size;
    if ((NULL != ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->pViraddr) && (0 != u32Size))
    {
       Ret = munmap(((HI_GFX_MEM_HANDLE_S *)pMemHandle)->pViraddr, u32Size);
    }

    if (((HI_GFX_MEM_HANDLE_S *)pMemHandle)->s32MapFd >= 0)
    {
       close(((HI_GFX_MEM_HANDLE_S *)pMemHandle)->s32MapFd);
    }

    ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->s32MapFd = 0;

    if (0 != Ret)
    {
       return HI_FAILURE;
    }

    HI_GFX_LOG_Display(0,0,u32PhyAddr,NULL,HIGFX_MODE_UNMAP);

    return HI_SUCCESS;
}

static inline HI_S32 HI_GFX_Flush(HI_S32 s32MMZDev,HI_U32 u32PhyAddr, HI_VOID *pMemHandle)
{
    HI_UNUSED(u32PhyAddr);
    return gfx_ion_sync_fd(s32MMZDev, ((HI_GFX_MEM_HANDLE_S *)pMemHandle)->s32MapFd);
}

static inline HI_S32 HI_GFX_GetPhyaddr(HI_S32 s32MMZDev,HI_VOID * pVir, HI_U32 *pPhyaddr, HI_U32 *pu32Size, HI_VOID *pMemHandle)
{
    HI_UNUSED(s32MMZDev);
    HI_UNUSED(pVir);
    HI_UNUSED(pPhyaddr);
    HI_UNUSED(pu32Size);
    HI_UNUSED(pMemHandle);
    return HI_FAILURE;
}
#endif

#endif /*_HI_GFX_COMM_H_ */
