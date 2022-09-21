/******************************************************************************
Copyright (C), 2009-2019, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mmz_struct.h
Version       : Initial Draft
Author        : Hisilicon
Created       : 2009/12/16
Last Modified :
Description   : Defines the common data type of the system.
                CNcomment: 系统共用的数据类型定义
Function List :
History       :
******************************************************************************/
/**
 * \file
 * \brief Describes the information about basic data types. CNcomment: 提供基本数据类型的相关信息
 */
#ifndef __MMZ_STRUCT_H__
#define __MMZ_STRUCT_H__
#include <hi_tee_debug.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_1_2 */
/** @{ */  /** <!-- 【Common data structure. CNcomment: 通用数据结构】 */


/**Maximum bytes of a buffer name*/
/**CNcomment:  buffer命名的最大字节数 */
#define MAX_BUFFER_NAME_SIZE 16

/**alloc_type*/
/**CNcomment:  alloc_type */
#define SECURE_MEM 0
#define NON_SECURE_MEM 1

/**Structure of an MMZ buffer*/
/**CNcomment:  MMZ buffer信息结构 */
typedef struct hiMMZ_BUF_S
{
    unsigned int  phyaddr;                /**<Physical address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer物理地址 */
    unsigned int alloc_type;        /**<Indicate to alloc mem from the non-secure or secure memory*/ /**<CNcomment:  指示从安全内存还是非安全内存中分配 */
    unsigned int  bufsize;                /**<Size of an MMZ buffer*/ /**<CNcomment:  MMZ buffer大小 */
}HI_MMZ_BUF_S;

typedef struct hiSMMU_BUF_S
{
    unsigned int phyaddr;		/**<Physical address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer物理地址 */
    unsigned int smmuaddr;		/**<SMMU address of an MMZ buffer mapped via physical address*/ /**<CNcomment:  MMZ buffer的映射后的SMMU地址 */
    unsigned int alloc_type;	/**<Indicate to alloc mem from the non-secure or secure memory*/ /**<CNcomment:  指示从安全内存还是非安全内存中分配 */
    void *virt;					/**<Virtual address of an MMZ buffer*/ /**<CNcomment:  MMZ buffer的cpu虚拟地址 */
    unsigned int bufsize;		/**<Size of an MMZ buffer*/ /**<CNcomment:  MMZ buffer大小 */
}HI_SMMU_BUF_S;

typedef struct {
    HI_MMZ_BUF_S *pBuf;
    HI_SMMU_BUF_S *pSmmuBuf;
    char *mmz_name;
    char *mmb_name;
    unsigned long addr;
    unsigned long size;
    unsigned long phys_addr;
    unsigned long arg0;
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
} HI_TEE_MMZ_DRV_IOCTRL_BUF;

enum MMZ_DRV_IOCTL_FUNC_ID
{
	MMZ_NEW_ID = 0x0,
	MMZ_DEL_ID,
	TEE_ISSECMMZ,
	TEE_ISSECMEM,
	TEE_ISNONSECMEM,
	CALL_DEBUG,
	MMZ_ALLOC_MAPALL_ID,
	MMZ_FREE_UNMAPALL_ID,
};

#define MMZ_LOG_ERROR(fmt...)          HI_LOG_ERROR(fmt)
#define MMZ_LOG_WARN(fmt...)           HI_LOG_WARN(fmt)
#define MMZ_LOG_INFO(fmt...)           HI_LOG_INFO(fmt)
#define MMZ_LOG_DEBUG(fmt...)		HI_LOG_DEBUG(fmt)

/*End of CMPI */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __MMZ_STRUCT_H__ */

