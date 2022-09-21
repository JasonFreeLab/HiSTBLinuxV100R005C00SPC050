/* linux/include/asm-arm/arch-hi3510_v100_m01/media-mem.h
*
* Copyright (c) 2006 Hisilicon Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*
*/

#ifndef __ASM_ARCH_MEDIA_MEM_H
#define __ASM_ARCH_MEDIA_MEM_H

#ifdef __cplusplus
extern "C"{
#endif

#include "hi_list.h"
#include "tee_os_hal.h"
#include "hi_tee_debug.h"

#define PRINTK_CA(fmt...)	HI_LOG_INFO(fmt)

#ifdef HI_ADVCA_FUNCTION_RELEASE
#define MMZ_RELEASE_SUPPORT
#else
#undef	MMZ_RELEASE_SUPPORT
#endif

#ifndef SECURE_MEM
#define SECURE_MEM 0
#endif

#ifndef NON_SECURE_MEM
#define NON_SECURE_MEM 1
#endif

#define MEM_LIMIT_SIZE          (0x40000000)

#define HIL_MAX_NAME_LEN 16
#define UUID_LENGTH 16
struct hil_media_memory_block {
	char name[HIL_MAX_NAME_LEN];
	struct hil_media_memory_zone *zone;
	struct list_head list;
	unsigned long phys_addr;
	void *kvirt;
	unsigned long length;
	unsigned long flags;
	int map_ref;
	TEE_UUID uuid;
	void *uvirt; // ta virt
	int u_map_ref;
};
typedef struct hil_media_memory_block hil_mmb_t;

/********** API_0 for inf *********/
extern void *hil_mmz_create(const char *name, unsigned int alloc_type, /*unsigned long gfp, */
                unsigned long phys_start,
                unsigned long nbytes);
extern int   hil_mmz_destroy(void *mmz);
extern int   hil_mmz_register(void* mmz);
extern int   hil_mmz_unregister(void *mmz);
extern int   hil_mmb_unmap(void *_mmb);
extern void* hil_mmb_getby_phys(unsigned long addr);
extern void* hil_mmb_getby_kvirt(void *virt);
extern void* hil_mmb_map2kern(void *_mmb);
extern void* hil_mmb_map2kern_cached(void *_mmb);
extern void* hil_mmb_map2uk(void *_mmb);
extern void* hil_mmb_map2uk_cached(void *_mmb);
extern void* hil_mmb_kvirt(void *_mmb);
extern void  hil_mmb_flush_l2cached(void *_mmb);
extern void  hil_mmz_dump(void);
extern unsigned long hil_mmb_phys(void *_mmb);
extern void *hil_mmb_getby_uvirt(void *virt);
extern int hil_mmb_unmap_uk(void *_mmb);

/********** API_1 for inf & usr *********/

extern void *hil_mmb_alloc(const char *name, unsigned long size,
                unsigned int alloc_type, const char *mmz_name);
extern int hil_mmb_free(void *mmb);
extern int hil_tee_is_sec_mem(unsigned long phy_addr, unsigned long size);
extern int hil_tee_is_nonsec_mem(unsigned long phy_addr, unsigned long size);

#ifdef __cplusplus
}
#endif

#endif
