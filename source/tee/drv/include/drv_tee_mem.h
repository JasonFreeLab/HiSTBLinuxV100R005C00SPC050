#ifndef _DRV_TEE_MEM_H
#define _DRV_TEE_MEM_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "hi_type.h"

typedef unsigned int HI_U32;
typedef int	HI_S32;
typedef char    HI_CHAR;

typedef enum
{
	SEC_MMZ = 0,
	NORMAL_MMZ,
}TEE_MMZ_TYEP_E;

typedef struct
{
	void* pu8StartVirAddr;
	HI_U32 u32StartPhyAddr;
	HI_U32 u32Size;
} TEE_MMZ_BUFFER_S;

typedef struct
{
	void* pu8StartVirAddr;
	HI_U32 u32StartSmmuAddr;
	HI_U32 u32Size;
} TEE_SMMU_BUFFER_S;

#ifdef CFG_HI_TEE_SMMU_SUPPORT
/*
 * brief: alloc discontinuous mem and map to sec smmu
 * bufname: input, the name of buffer need to alloc
 * size: input, the size of buffer need to alloc
 * align: input, the align of buffer
 * pSecSmmuBuf: output, the sec smmu addr will output
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_SMMU_Alloc(const HI_CHAR *bufname, HI_U32 size, HI_U32 align, TEE_SMMU_BUFFER_S *pSecSmmuBuf);

/*
 ** brief: free sec smmu buffer
 * pSecSmmuBuf: input, the buffer info
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 **/
HI_S32 DRV_TEE_SMMU_Free(const TEE_SMMU_BUFFER_S *pSecSmmuBuf);


/*
 * brief: map cpu addr with sec smmu addr
 * pSecSmmuBuf: inout, sec smmu addr and size should be input, and cpu addr
 *                       will be output.
 * cached: input, the cache attr when map
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 **/
HI_S32 DRV_TEE_SMMU_MapCpu(TEE_SMMU_BUFFER_S *pSecSmmuBuf, HI_BOOL cached);

/*
 * brief: umap from cpu addr
 * pSecSmmuBuf: input, cpu addr of buffer should input
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 **/
HI_S32 DRV_TEE_SMMU_UnmapCpu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf);

/*
 * brief: alloc sec mmz mem
 * bufname: input, the name of buffer need to alloc
 * size: input, the size of buffer to alloc
 * align: input, the align of buffer
 * memtype: input, the type to separate static sec mmz or dynamic sec mmz(cma)
 * pSecMBuf: output, the sec mmz addr will output
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_Alloc(const HI_CHAR *bufname, HI_U32 size, HI_U32 align,
			TEE_MMZ_TYEP_E memtype, TEE_MMZ_BUFFER_S *pSecMBuf);

/*
 * brief: free mmz mem
 * pSecMBuf: input, the info of buffer need to free
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_Free(const TEE_MMZ_BUFFER_S *pSecMBuf);

/*
 * brief: map cpu addr
 * pSecMBuf: inout, the mem info
 * cached: input, the map attr of cache
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_MapCpu(TEE_MMZ_BUFFER_S *pSecMBuf, HI_BOOL cached);

/*
 * brief: flush cache, just for sec mmz
 * pSecMBuf: input, the sec phys addr should input
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_FlushSecMMZ(TEE_MMZ_BUFFER_S *pSecMBuf);

/*
 * brief: flush cache
 * virt: input, the cpu addr
 * size: input, the size of mem
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MEM_FlushCache(HI_VOID *virt, HI_U32 size);

/*
 * brief: unmap from cpu virt addr
 * pSecMBuf: input, the cpu virt addr and phys addr should input
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_UnmapCpu(const TEE_MMZ_BUFFER_S *pSecMBuf);

/*
 * brief: map phys addr to sec smmu addr
 * pSecMBuf: input, the mem info
 * pSecSmmuBuf: output, sec smmu will output
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_MapToSmmu(const TEE_MMZ_BUFFER_S *pSecMBuf, TEE_SMMU_BUFFER_S *pSecSmmuBuf);

/*
 * brief: phys addr unmap from smmu addr
 * pSecSmmuBuf: input, the mem info
 * phys_addr: input, the phys addr of mem
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_UmapFromSmmu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf, HI_ULONG phys_addr);

/*
 * brief: non sec mmz map to sec cpu addr
 * pSecMBuf: inout, the first phys addr should input
 * cached: input, the map cache attr
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSMMZ_MapCpu(TEE_MMZ_BUFFER_S *pSecMBuf, HI_BOOL cached);

/*
 * brief: non sec mmz unmap from sec cpu addr
 * pSecMBuf: input, buffer info
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSMMZ_UmapCpu(const TEE_MMZ_BUFFER_S *pSecMBuf);

/*
 * brief: non sec mmz map to sec smmu addr
 * psMBuf: input, the first phys addr should input
 * pSecSmmuBuf: output, the sec smmu will output
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSMMZ_MapSmmu(const TEE_MMZ_BUFFER_S *psMBuf, TEE_SMMU_BUFFER_S *pSecSmmuBuf);

/*
 * brief: non sec mmz unmap from sec smmu
 * pSecSmmuBuf: input, buffer info
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSMMZ_UmapSmmu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf);

/*
 * brief: non sec smmu mem map to sec cpu addr
 * pSmmuBuf: inout, the first non sec smmu should input
 * cached: input, the map cache attr
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSSMMU_MapCpu(TEE_SMMU_BUFFER_S *pSmmuBuf, HI_BOOL cached);

/*
 * brief: non sec smmu mem unmap from sec cpu addr
 * pSecSmmuBuf: input, buffer info
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSSMMU_UmapCpu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf);

/*
 * brief: non sec smmu map to sec smmu addr
 * pSmmuBuf: input, the first non sec smmu addr should input
 * sec_smmu: output, the sec smmu addr
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSSMMU_MapSmmu(const TEE_SMMU_BUFFER_S *pSmmuBuf, HI_U32 *sec_smmu);

/*
 * brief: non sec smmu unmap from sec smmu
 * pSecSmmuBuf: input, the sec smmu addr should input
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_NSSMMU_UmapSmmu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf);

/*
 * brief: get smmu pgt table addr and rw err addr
 * smmu_e_raddr: output, read addr when smmu hw read err
 * smmu_e_waddr: output, write addr when smmu hw write err
 * smmu_pgtbl: output, smmu gpt addr
 * return:
 *      NULL
 */
HI_VOID DRV_TEE_SMMU_GetPgtbladdr(HI_ULONG *smmu_e_raddr, HI_ULONG *smmu_e_waddr,
						HI_ULONG *smmu_pgtbl);

/*
 * brief: check if a smmu addr is sec
 * smmu_addr: input, smmu addr
 * is_sec: output, the sec attr of the smmu addr
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_SMMU_IsSec(HI_ULONG smmu_addr, HI_BOOL *is_sec);

/*
 * brief: check if a phys addr is sec
 * phys_addr: input, phys addr
 * is_sec: output, the sec attr of the phys addr
 * return:
 *      HI_SUCCESS, if exec successfully
 *      HI_FAILED, if exec failed
 */
HI_S32 DRV_TEE_MMZ_IsSec(HI_ULONG phys_addr, HI_BOOL *is_sec);


#else
static inline HI_S32 DRV_TEE_SMMU_Alloc(const HI_CHAR *bufname, HI_U32 size, HI_U32 align, TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_SMMU_Free(const TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_SMMU_MapCpu(TEE_SMMU_BUFFER_S *pSecSmmuBuf, HI_BOOL cached)
{
	return 0;
}

static inline HI_S32 DRV_TEE_SMMU_UnmapCpu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_Alloc(const HI_CHAR *bufname, HI_U32 size, HI_U32 align,
			TEE_MMZ_TYEP_E memtype, TEE_MMZ_BUFFER_S *pSecMBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_Free(const TEE_MMZ_BUFFER_S *pSecMBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_MapCpu(TEE_MMZ_BUFFER_S *pSecMBuf, HI_BOOL cached)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_FlushSecMMZ(TEE_MMZ_BUFFER_S *pSecMBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_UnmapCpu(const TEE_MMZ_BUFFER_S *pSecMBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_MapToSmmu(const TEE_MMZ_BUFFER_S *pSecMBuf, TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_UmapFromSmmu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf, HI_ULONG phys_addr)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSMMZ_MapCpu(TEE_MMZ_BUFFER_S *pSecMBuf, HI_BOOL cached)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSMMZ_UmapCpu(const TEE_MMZ_BUFFER_S *pSecMBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSMMZ_MapSmmu(const TEE_MMZ_BUFFER_S *psMBuf, TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSMMZ_UmapSmmu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSSMMU_MapCpu(TEE_SMMU_BUFFER_S *pSmmuBuf, HI_BOOL cached)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSSMMU_UmapCpu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSSMMU_MapSmmu(const TEE_SMMU_BUFFER_S *pSmmuBuf, HI_U32 *sec_smmu)
{
	return 0;
}

static inline HI_S32 DRV_TEE_NSSMMU_UmapSmmu(const TEE_SMMU_BUFFER_S *pSecSmmuBuf)
{
	return 0;
}

static inline HI_VOID DRV_TEE_SMMU_GetPgtbladdr(HI_ULONG *smmu_e_raddr, HI_ULONG *smmu_e_waddr,
						HI_ULONG *smmu_pgtbl)
{
	return;
}


static inline HI_S32 DRV_TEE_MEM_FlushCache(HI_VOID *virt, HI_U32 size)
{
	return 0;
}

static inline HI_S32 DRV_TEE_SMMU_IsSec(HI_ULONG smmu_addr, HI_BOOL *is_sec)
{
	return 0;
}

static inline HI_S32 DRV_TEE_MMZ_IsSec(HI_ULONG phys_addr, HI_BOOL *is_sec)
{
	return 0;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
