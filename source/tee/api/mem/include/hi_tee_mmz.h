/** 
 * \file
 * \brief Describes the information about HiSilicion SecureMMZ.
*/


#ifndef __HI_TEE_MMZ_H__
#define __HI_TEE_MMZ_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************** Macro Definition ****************************/
/** \addtogroup     SecureMMZ */
/** @{ */  /** <!-- [SecureMMZ] */

/** @} */  /*! <!-- Macro Definition End */

/******************************* API Declaration *****************************/
/** \addtogroup      SecureMMZ*/
/** @{*/  /** <!-- -SecureMMZ=*/

/**
\brief Allocate memory block.
\attention \n
N/A
\param[in]  size        The size of the memory block to be allocated.
\param[in]  mmz_name    The name of the memory pool for allocation, should be "SEC-MMZ" currently.
\param[in]  mmb_name    The name of the memory block.
\retval ::non-zero   Success, return the physical address of the block.
\retval ::zero       Fail to allocate memory block.
\see \n
N/A
*/
HI_ULONG HI_TEE_MMZ_New(HI_ULONG size, const HI_CHAR *mmz_name, const HI_CHAR *buf_name);

/**
\brief Free the memory block.
\attention \n
N/A
\param[in]  phys_addr    The physical address of the memory block.
\retval ::0   Success.
\retval ::non-zero Fail to free the memory block.
\see \n
N/A
*/
HI_S32 HI_TEE_MMZ_Delete(HI_ULONG phys_addr);

/**
\brief judge if the mem is in sec mmz zone.
\attention \n
N/A
\param[in]  phys_addr    The phys address of the memory block.
\retval ::0   the mem is not in sec mmz zone
\retval ::1   the mem is in sec mmz zone.
\retval ::-1   check failed.
\see \n
N/A
*/
HI_S32 HI_TEE_MMZ_IsSecMMZ(HI_ULONG phys_addr);

/**
\brief alloc sec mmz mem and map to cpu/ sec smmu
\attention \n
N/A
\param[in]  size    The size of the memory block to alloc
\param[in]  mmz_name    The name of the memory pool
\param[in]  buf_name    The name of the memory block
\param[out]  smmu_addr    the sec smmu addr of the memory block
\param[out]  phys_addr    The phyaddr of the memory block
\retval ::NULL   exec failed
\retval ::!NULL   the cpu address, exec successfully
\see \n
N/A
*/
HI_VOID *HI_TEE_MMZ_AllocAndMapAll(HI_ULONG size, const HI_CHAR *mmz_name,
				   const HI_CHAR *buf_name, HI_ULONG *smmu_addr,
				   HI_ULONG *phys_addr);

/**
\brief free and unmap cpu/sec smmu.
\attention \n
N/A
\param[in]  virt    The cpu address of the memory block.
\param[in]  smmu_addr    The sec smmu address of the memory block.
\param[in]  phys_addr    The phys address of the memory block.
\retval ::0   exec successfully
\retval ::1   exec failed
\see \n
N/A
*/
int HI_TEE_MMZ_FreeAndUnmapAll(HI_VOID *virt, HI_ULONG smmu_addr,
				HI_ULONG phy_addr);




/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __HI_TEE_MEM_H__ */

