#ifndef _SEC_MMZ_H
#define _SEC_MMZ_H

typedef enum {
       HI_MMZ_NEW = 0x1000,
       HI_MMZ_DEL,
       HI_MMZ_CP_CA2TA,
       HI_MMZ_CP_TA2CA,
       HI_MMZ_CP_TA2TA,
	HI_MMZ_TEST,
	HI_MMZ_DEBUG,
	HI_MMZ_NEW_MAPSMMU,
	HI_MMZ_DEL_UNMAPSMMU,
} E_HI_MMZ_CommandId;

#ifdef CONFIG_TEE
/**
\brief Allocate secure memory block.
\attention \n
N/A
\param[in]  size        The size of the memory block to be allocated.
\param[in]  mmz_name    The name of the memory pool to allocate from.
\param[in]  mmb_name    The name of the memory block.
\retval ::non-zero   Success, return the phisical address of the block.
\retval ::NULL       Calling this API fails.
\see \n
N/A
*/
void *HI_SEC_MMZ_New(unsigned long size , char *mmz_name, char *mmb_name);

/**
\brief Relieve the secure memory block.
\attention \n
N/A
\param[in]  phys_addr    The phisical address of the secure memory block.
\retval ::0   Success
\see \n
N/A
*/
int HI_SEC_MMZ_Delete(unsigned long phys_addr);

/**
\brief Memory copy from client side to trusted side.
\attention \n
N/A
\param[in]  CAphyaddr    The phisical address of client side.
\param[in]  TAphyaddr    The phisical address of the trusted side.
\param[in]  CopySize     The size to be copyed.
\retval ::0   Success
\see \n
N/A
*/
int HI_SEC_MMZ_CA2TA(unsigned long CAphyaddr, unsigned long TAphyaddr, unsigned long CopySize);

//int HI_SEC_MMZ_TA2CA(unsigned long TAphyaddr, unsigned long CAphyaddr, unsigned long CopySize);

/**
\brief Memory copy from secure mem1 to secure mem2.
\attention \n
N/A
\param[in]  phyaddr1    The phisical address of secure mem1.
\param[in]  phyaddr2    The phisical address of secure mem2.
\param[in]  CopySize     The size to be copyed.
\retval ::0   Success
\see \n
N/A
*/
int HI_SEC_MMZ_TA2TA(unsigned long phyaddr1, unsigned long phyaddr2, unsigned long CopySize);


/**
\brief alloc mmz and map sec smmu address
\attention \n
N/A
\param[in]  size    The mem size to be alloc.
\param[in]  mmz_name    The mem zone name.
\param[in]  mmb_name     The mem buffer name.
\retval ::!0   Success, return the sec smmu addr
\retval ::0   Calling this API fails.
\see \n
N/A
*/
unsigned long HI_SEC_MMZ_New_And_Map_SecSmmu(unsigned long size,
					     char *mmz_name, char *mmb_name);

/**
\brief free mmz and unmap sec smmu address
\attention \n
N/A
\param[in]  smmu_addr    The sec smmu address of secure mem.
\param[in]  size    	The size of secure mem.
\retval ::0   Success
\retval ::!0   Calling this API fails.
\see \n
N/A
*/
int HI_SEC_MMZ_Delete_And_Unmap_SecSmmu(unsigned long smmu_addr,
					unsigned long size);

#else
static inline void *HI_SEC_MMZ_New(unsigned long size , char *mmz_name, char *mmb_name)
{
	return NULL;
}

static inline int HI_SEC_MMZ_Delete(unsigned long phys_addr)
{
	return 0;
}

static inline int HI_SEC_MMZ_CA2TA(unsigned long CAphyaddr, unsigned long TAphyaddr, unsigned long CopySize)
{
	return 0;
}

static inline int HI_SEC_MMZ_TA2TA(unsigned long phyaddr1, unsigned long phyaddr2, unsigned long CopySize)
{
	return 0;
}

static inline unsigned long HI_SEC_MMZ_New_And_Map_SecSmmu(unsigned long size,
				                    char *mmz_name, char *mmb_name)
{
	return 0;
}

static inline int HI_SEC_MMZ_Delete_And_Unmap_SecSmmu(unsigned long smmu_addr,
					unsigned long size)
{
	return 0;
}
#endif
#endif
