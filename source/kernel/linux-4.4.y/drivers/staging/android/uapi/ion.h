/*
 * drivers/staging/android/uapi/ion.h
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _UAPI_LINUX_ION_H
#define _UAPI_LINUX_ION_H

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/iommu.h>

typedef int ion_user_handle_t;
#define ion_phys_addr_t unsigned long

/**
 * enum ion_heap_types - list of all possible types of heaps
 * @ION_HEAP_TYPE_SYSTEM:	 memory allocated via vmalloc
 * @ION_HEAP_TYPE_SYSTEM_CONTIG: memory allocated via kmalloc
 * @ION_HEAP_TYPE_CARVEOUT:	 memory allocated from a prereserved
 *				 carveout heap, allocations are physically
 *				 contiguous
 * @ION_HEAP_TYPE_DMA:		 memory allocated via DMA API
 * @ION_NUM_HEAPS:		 helper for iterating over heaps, a bit mask
 *				 is used to identify the heaps, so only 32
 *				 total heap types are supported
 */
enum ion_heap_type {
	ION_HEAP_TYPE_SYSTEM,
	ION_HEAP_TYPE_SYSTEM_CONTIG,
	ION_HEAP_TYPE_CARVEOUT,
	ION_HEAP_TYPE_CHUNK,
	ION_HEAP_TYPE_DMA,
	ION_HEAP_TYPE_TEE_SEC_MEM,
	/* backwards compatible with v3.4 ion */
	ION_HEAP_ID_CMA = 15, /* cma: ddr */
	ION_HEAP_ID_TEE_SEC_MEM, /* secure mem in TEE */
	ION_HEAP_ID_MULTI_CMA, /* support multi cma   */
	ION_HEAP_TYPE_CUSTOM, /*
			       * must be last so device specific heaps always
			       * are at the end of this enum
			       */
	ION_NUM_HEAPS = 31,
};

#define ION_HEAP_SYSTEM_MASK		(1 << ION_HEAP_TYPE_SYSTEM)
#define ION_HEAP_SYSTEM_CONTIG_MASK	(1 << ION_HEAP_TYPE_SYSTEM_CONTIG)
#define ION_HEAP_CARVEOUT_MASK		(1 << ION_HEAP_TYPE_CARVEOUT)
#define ION_HEAP_TYPE_DMA_MASK		(1 << ION_HEAP_TYPE_DMA)
#define ION_HEAP_CMA_MASK		(1 << ION_HEAP_ID_CMA)
#define ION_HEAP_TEE_SEC_MASK		(1 << ION_HEAP_ID_TEE_SEC_MEM)

#define ION_NUM_HEAP_IDS		(sizeof(unsigned int) * 8)

/**
 * allocation flags - the lower 16 bits are used by core ion, the upper 16
 * bits are reserved for use by the heaps themselves.
 */
#define ION_FLAG_CACHED 1		/*
					 * mappings of this buffer should be
					 * cached, ion will do cache
					 * maintenance when the buffer is
					 * mapped for dma
					*/
#define ION_FLAG_CACHED_NEEDS_SYNC 2	/*
					 * mappings of this buffer will created
					 * at mmap time, if this is set
					 * caches must be managed
					 * manually
					 */

/**
 * DOC: Ion Userspace API
 *
 * create a client by opening /dev/ion
 * most operations handled via following ioctls
 *
 */

/**
 * struct ion_allocation_data - metadata passed from userspace for allocations
 * @len:		size of the allocation
 * @align:		required alignment of the allocation
 * @heap_id_mask:	mask of heap ids to allocate from
 * @flags:		flags passed to heap
 * @handle:		pointer that will be populated with a cookie to use to
 *			refer to this allocation
 *
 * Provided by userspace as an argument to the ioctl
 */
struct ion_allocation_data {
	size_t len;
	size_t align;
	unsigned int heap_id_mask;
	unsigned int flags;
	ion_user_handle_t handle;
};

/**
 * struct ion_fd_data - metadata passed to/from userspace for a handle/fd pair
 * @handle:	a handle
 * @fd:		a file descriptor representing that handle
 *
 * For ION_IOC_SHARE or ION_IOC_MAP userspace populates the handle field with
 * the handle returned from ion alloc, and the kernel returns the file
 * descriptor to share or map in the fd field.  For ION_IOC_IMPORT, userspace
 * provides the file descriptor and the kernel returns the handle.
 */
struct ion_fd_data {
	ion_user_handle_t handle;
	int fd;
};

/**
 * struct ion_handle_data - a handle passed to/from the kernel
 * @handle:	a handle
 */
struct ion_handle_data {
	ion_user_handle_t handle;
};

/**
 * struct ion_phys_data - metadata passed to/from the kernel to get the physic
 *                        address
 * @handle:    a handle
 * @len:        buffer len
 * @phys_addr:  physic address of the handle
 */
struct ion_phys_data {
	ion_user_handle_t handle;
	size_t len;
	ion_phys_addr_t phys_addr;
};

/**
 * struct ion_custom_data - metadata passed to/from userspace for a custom ioctl
 * @cmd:	the custom ioctl function to call
 * @arg:	additional data to pass to the custom ioctl, typically a user
 *		pointer to a predefined structure
 *
 * This works just like the regular cmd and arg fields of an ioctl.
 */
struct ion_custom_data {
	unsigned int cmd;
	unsigned long arg;
};

/**
 * struct ion_map_iommu_data - metadata passed between userspace for iommu mapping
 * @handle:	the handle of buffer
 * @format:	the format of iommu mapping
 * Provided by userspace as an argument to the ioctl
 */
struct iommu_map_format;
struct ion_map_iommu_data {
	ion_user_handle_t handle;
	struct iommu_map_format format;
};

/*
 * struct ion_ref - get the buffer reference count(such as iommu map)
 * @handle:	the handle of buffer
 * @ref:	the a kind of attr's ref of buffer
 */
struct ion_ref {
	ion_user_handle_t handle;
	unsigned int ref;
};

#define ION_IOC_MAGIC		'I'

/**
 * DOC: ION_IOC_ALLOC - allocate memory
 *
 * Takes an ion_allocation_data struct and returns it with the handle field
 * populated with the opaque handle for the allocation.
 */
#define ION_IOC_ALLOC		_IOWR(ION_IOC_MAGIC, 0, \
				      struct ion_allocation_data)

/**
 * DOC: ION_IOC_FREE - free memory
 *
 * Takes an ion_handle_data struct and frees the handle.
 */
#define ION_IOC_FREE		_IOWR(ION_IOC_MAGIC, 1, struct ion_handle_data)

/**
 * DOC: ION_IOC_MAP - get a file descriptor to mmap
 *
 * Takes an ion_fd_data struct with the handle field populated with a valid
 * opaque handle.  Returns the struct with the fd field set to a file
 * descriptor open in the current address space.  This file descriptor
 * can then be used as an argument to mmap.
 */
#define ION_IOC_MAP		_IOWR(ION_IOC_MAGIC, 2, struct ion_fd_data)

/**
 * DOC: ION_IOC_SHARE - creates a file descriptor to use to share an allocation
 *
 * Takes an ion_fd_data struct with the handle field populated with a valid
 * opaque handle.  Returns the struct with the fd field set to a file
 * descriptor open in the current address space.  This file descriptor
 * can then be passed to another process.  The corresponding opaque handle can
 * be retrieved via ION_IOC_IMPORT.
 */
#define ION_IOC_SHARE		_IOWR(ION_IOC_MAGIC, 4, struct ion_fd_data)

/**
 * DOC: ION_IOC_IMPORT - imports a shared file descriptor
 *
 * Takes an ion_fd_data struct with the fd field populated with a valid file
 * descriptor obtained from ION_IOC_SHARE and returns the struct with the handle
 * filed set to the corresponding opaque handle.
 */
#define ION_IOC_IMPORT		_IOWR(ION_IOC_MAGIC, 5, struct ion_fd_data)

/**
 * DOC: ION_IOC_SYNC - syncs a shared file descriptors to memory
 *
 * Deprecated in favor of using the dma_buf api's correctly (syncing
 * will happen automatically when the buffer is mapped to a device).
 * If necessary should be used after touching a cached buffer from the cpu,
 * this will make the buffer in memory coherent.
 */
#define ION_IOC_SYNC		_IOWR(ION_IOC_MAGIC, 7, struct ion_fd_data)

/**
 * DOC: ION_IOC_CUSTOM - call architecture specific ion ioctl
 *
 * Takes the argument of the architecture specific ioctl to call and
 * passes appropriate userdata for that ioctl
 */
#define ION_IOC_CUSTOM		_IOWR(ION_IOC_MAGIC, 6, struct ion_custom_data)

/**
 * DOC: ION_IOC_PHYS - given an ion_handle,return the physic address of the buffer
 *
 * Takes an ion_phys_data struct with the handle field populated with a valid
 * opaque handle.  Returns the struct with the physic_addr field set the physic
 * address of the internal buffer and the buffer len
 */
#define ION_IOC_PHYS		_IOWR(ION_IOC_MAGIC, 8, struct ion_phys_data)
/**
 * DOC: ION_IOC_MAP_IOMMU - map a buffr to iova
 */
#define ION_IOC_MAP_IOMMU       _IOWR(ION_IOC_MAGIC, 9, struct ion_map_iommu_data)

/**
 * DOC: ION_IOC_UNMAP_IOMMU - destory iommu mapping of a buffer
 */
#define ION_IOC_UNMAP_IOMMU     _IOWR(ION_IOC_MAGIC, 10, struct ion_map_iommu_data)

/**
 * DOC: ION_IOC_MAP_SEC_IOMMU - map a buffr to SEC SMMU iova
 */
#define ION_IOC_MAP_SEC_IOMMU       _IOWR(ION_IOC_MAGIC, 11, struct ion_map_iommu_data)

/**
 * DOC: ION_IOC_UNMAP_SEC_IOMMU - destory iommu SEC mapping of a buffer
 */
#define ION_IOC_UNMAP_SEC_IOMMU     _IOWR(ION_IOC_MAGIC, 12, struct ion_map_iommu_data)

/*
 * DOC: ION_IOC_IOMMU_REF_CNT - get iommu ref cnt
 */
#define ION_IOC_IOMMU_REF_CNT	_IOWR(ION_IOC_MAGIC, 13, struct ion_ref)

#endif /* _UAPI_LINUX_ION_H */
