/******************************************************************************
Copyright (C), 2009-2019, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : smmu_struct.h
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
#ifndef __SMMU_STRUCT_H__
#define __SMMU_STRUCT_H__
#include <hi_tee_debug.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_1_2 */
/** @{ */  /** <!-- 【Common data structure. CNcomment: 通用数据结构】 */

typedef struct {
	char *bufname;
	unsigned long phys_addr;
	unsigned long sec_addr;
	unsigned long nonsec_addr;
	unsigned long buf_phys;
	unsigned long buf_size;
	unsigned long smmu_addr;
	unsigned long align;
	unsigned long cmd;
	unsigned long arg0;
	unsigned long arg1;
	int memtype;
	int share_mem;
} HI_TEE_SMMU_DRV_IOCTRL_BUF;

enum SMMU_DRV_IOCTL_FUNC_ID
{
	HISI_SEC_MAPTOSMMU = 0x0,
	HISI_SEC_UNMAPFROMSMMU,
	HISI_SEC_MAPTOSMMU_AND_SETFLAG,
	HISI_SEC_UNMAPFROMSMMU_AND_CLRFLG,
	HISI_SEC_ALLOC,
	HISI_SEC_FREE,
	HISI_SEC_MAP_TO_SEC_SMMU,
	HISI_SEC_UNMAP_FROM_SEC_SMMU,
	HISI_NOSEC_MEM_MAP_TO_SEC_SMMU,
	HISI_NOSEC_MEM_UNMAP_FROM_SEC_SMMU,
	AGENT_CLOSED,
	SEC_IOCTL,
	CHECK_SEC_SMMU,
	CHECK_SEC_MMZ,
};

#define SMMU_LOG_ERROR(fmt...)		HI_LOG_ERROR(fmt)
#define SMMU_LOG_WARN(fmt...)		HI_LOG_WARN(fmt)
#define SMMU_LOG_INFO(fmt...)		HI_LOG_INFO(fmt)


/*End of CMPI */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __SMMU_STRUCT_H__ */

