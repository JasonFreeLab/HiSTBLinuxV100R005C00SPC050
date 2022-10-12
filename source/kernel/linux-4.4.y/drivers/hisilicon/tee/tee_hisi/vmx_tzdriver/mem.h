/*
 * FileName:
 * Author:         sdk
 * Description:
 * Version:
 * Function List:
 */

#ifndef _MEM_H_
#define _MEM_H_

#include "teek_ns_client.h"

#define PRE_ALLOCATE_SIZE (1024*1024)
#define MEM_POOL_ELEMENT_SIZE (64*1024)
#define MEM_POOL_ELEMENT_NR (8)
#define MEM_POOL_ELEMENT_ORDER (4)

int tc_mem_init(void);
void tc_mem_destroy(void);

TC_NS_Shared_MEM *tc_mem_allocate(TC_NS_DEV_File *dev, size_t len);
void tc_mem_free(TC_NS_Shared_MEM *shared_mem);

static inline void get_sharemem_struct(struct tag_TC_NS_Shared_MEM *sharemem)
{
	if (sharemem)
		atomic_inc(&sharemem->usage);
}

static inline void put_sharemem_struct(struct tag_TC_NS_Shared_MEM *sharemem)
{
	if (sharemem) {
		if (atomic_dec_and_test(&sharemem->usage))
			tc_mem_free(sharemem);
	}
}

#endif
