/******************************************************************************

  Copyright (C), 2015-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_tee_mem.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/01/010
  Description   :
  History       :
  1.Date        : 2016/01/10
    Author      : sdk
    Modification: Created file

*******************************************************************************/
/**
 * \file
 * \brief Describes the API about the smmu mem interface.
 */
#ifndef _HI_TEE_MEM_H
#define _HI_TEE_MEM_H

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      SMMU_MEM */
/** @{ */  /** <!-- [SMMU_MEM] */


/** the type of continuous mem */
typedef enum hiTEE_MMZ_TYEP_E
{
	HI_TEE_SEC_MMZ = 0,  /**< mem in trustedzone  */
	HI_TEE_NORMAL_MMZ,   /**< mem in share mem area */
}HI_TEE_MMZ_TYEP_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      SMMU_MEM */
/** @{ */  /** <!-- [SMMU_MEM] */


/**
\brief alloc sec mem in share mem, system mem.
\attention \n
The hi_mmz.ko need to insmod in REE first.
\param[in] pBufName The name of the buf which will be allocated.
\param[in] ulSize   The size of buf.
\param[in] ulAlign  Reserved.
\retval ::sec smmu address  Success.
\retval ::0                 Failure.
\see \n
N/A
*/
HI_ULONG HI_TEE_SMMU_Alloc(const HI_CHAR *pBufName, HI_ULONG ulSize, HI_ULONG ulAlign);

/**
\brief free sec mem in share mem, system mem.
\attention \n
The hi_mmz.ko need to insmod in REE first.
\param[in] ulSecSmmu    The sec smmu address of the mem which will be freed.
\retval ::HI_SUCCESS    Success.
\retval ::HI_FAILURE    Failure.
\see \n
N/A
*/
HI_S32 HI_TEE_SMMU_Free(HI_ULONG ulSecSmmu);

/**
\brief alloc sec mem, continuous phys mem.
\attention \n
The hi_mmz.ko need to insmod in REE first.
\param[in] pBufName The name of the buf which will be allocated.
\param[in] ulSize   The size of buf.
\param[in] ulAlign  Reserved.
\param[in] eMemType The mem type:sec mmz zone or share cma mem.
\retval ::sec phys address  Success.
\retval ::0                 Failure.
\see \n
N/A
*/
HI_ULONG HI_TEE_MMZ_Alloc(const HI_CHAR *pBufName, HI_ULONG ulSize, HI_ULONG ulAlign, HI_TEE_MMZ_TYEP_E eMemType);

/**
\brief free sec mem, continuous phy mem.
\attention \n
The hi_mmz.ko need to insmod in REE first.
\param[in] ulPhysAddr   The phys addr of the buf which will be freed.
\retval ::HI_SUCCESS    Success.
\retval ::HI_FAILURE    Failure.
\see \n
N/A
*/
HI_S32 HI_TEE_MMZ_Free(HI_ULONG ulPhysAddr);

/**
\brief normal smmu mem map to sec smmu address.
\attention \n
The hi_mmz.ko need to insmod in REE first.
\param[in] ulNormalSmmu     The normal smmu address of the mem.
\retval ::sec smmu address  Success.
\retval ::0                 Failure.
\see \n
N/A
*/
HI_ULONG HI_TEE_SMMU_NonsecSmmu_MapToSecSmmu(HI_ULONG ulNormalSmmu);

/**
\brief normal smmu mem unmap from sec smmu address.
\attention \n
The hi_mmz.ko need to insmod in REE first.
\param[in] ulSecSmmu    The sec smmu address of the mem.
\retval ::HI_SUCCESS    Success.
\retval ::HI_FAILURE    Failure.
\see \n
N/A
*/
HI_S32 HI_TEE_SMMU_NonsecSmmu_UnmapFromSecSmmu(HI_ULONG ulSecSmmu);

/**
\brief alloc sec mmz area and map cpu/sec smmu
\attention \n
\param[in] pBufName    The name of the mem.
\param[in] ulSize      The size of the mem.
\param[out] ulSecSmmu    The sec smmu address of the mem.
\param[out] ulPhysAddr    The phy address of the mem.
\retval ::!NULL    CPU ADDR,Success.
\retval ::NULL    Failure.
\see \n
N/A
*/
HI_VOID *HI_TEE_MMZ_Alloc_And_MapAll(const HI_CHAR *pBufName, HI_ULONG ulSize,
				     HI_ULONG *ulSecSmmu, HI_ULONG *ulPhysAddr);

/**
\brief free sec mmz area and unmap cpu/sec smmu
\attention \n
\param[in] virt    The cpu addr of the mem.
\param[in] ulSecSmmu    The sec smmu address of the mem.
\param[in] ulPhysAddr    The phy address of the mem.
\retval ::0    Success.
\retval ::!0   Failure.
\see \n
N/A
*/
HI_S32 HI_TEE_MMZ_Free_And_UnmapAll(HI_VOID *virt, HI_ULONG ulSecSmmu,
				    HI_ULONG ulPhysAddr);

/**
\brief check the smmu addr if it is sec
\attention \n
\param[in] ulSmmu    The smmu addr of the mem.
\param[out] is_sec   the ulSmmu sec attr, legal value only return success
\retval ::0    Success.
\retval ::!0   Failure.
\see \n
N/A
*/
HI_S32 HI_TEE_SMMU_IsSec(HI_ULONG ulSmmu, HI_BOOL *is_sec);

/**
\brief check the mmz addr if it is sec
\attention \n
\param[in] ulPhysAddr    The phys addr of the mem.
\param[out] is_sec   the ulPhysAddr sec attr, legal value only return success
\retval ::0    Success.
\retval ::!0   Failure.
\see \n
N/A
*/
HI_S32 HI_TEE_MMZ_IsSec(HI_ULONG ulPhysAddr, HI_BOOL *is_sec);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
