/******************************************************************************
 *  Copyright (C) 2014 Hisilicon Technologies CO.,LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiyong 2014.1.26
 *
******************************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/genalloc.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/hikapi.h>
#include <linux/syscore_ops.h>

struct pcie_alloc_ctrl_t pcie_read_ctrl = {0};
struct pcie_alloc_ctrl_t pcie_write_ctrl = {0};
/******************************************************************************/

void *pice_read_alloc(size_t len, dma_addr_t *dma)
{
	unsigned long vaddr;

	if (dma)
		*dma = 0;

	if (!pcie_read_ctrl.size || (dma && !pcie_read_ctrl.phyaddr))
		return NULL;

	vaddr = gen_pool_alloc(pcie_read_ctrl.pool, len);
	if (!vaddr)
		return NULL;

	if (dma)
		*dma = gen_pool_virt_to_phys(pcie_read_ctrl.pool, vaddr);

	return (void *)vaddr;
}
EXPORT_SYMBOL(pice_read_alloc);
/******************************************************************************/

void pice_read_free(void *vaddr, size_t len)
{
	if (pcie_read_ctrl.pool)
		gen_pool_free(pcie_read_ctrl.pool, (unsigned long)vaddr, len);
}
EXPORT_SYMBOL(pice_read_free);
/******************************************************************************/

void *pice_write_alloc(size_t len, dma_addr_t *dma)
{
	unsigned long vaddr;

	if (dma)
		*dma = 0;

	if (!pcie_write_ctrl.size || (dma && !pcie_write_ctrl.phyaddr))
		return NULL;

	vaddr = gen_pool_alloc(pcie_write_ctrl.pool, len);
	if (!vaddr)
		return NULL;

	if (dma)
		*dma = gen_pool_virt_to_phys(pcie_write_ctrl.pool, vaddr);

	return (void *)vaddr;
}
EXPORT_SYMBOL(pice_write_alloc);
/******************************************************************************/

void pice_write_free(void *vaddr, size_t len)
{
	if (pcie_write_ctrl.pool)
		gen_pool_free(pcie_write_ctrl.pool, (unsigned long)vaddr, len);
}
EXPORT_SYMBOL(pice_write_free);
/******************************************************************************/

static int __init pcie_write_init(void)
{
	int status = -ENOMEM;

	pcie_write_ctrl.size = CONFIG_PCIE_DMA_SIZE_WRITE;

	if(!pcie_write_ctrl.size) {
		/* if size = 0, we don't need pcie alloc */
		status = 0;
		goto out;
	}

	pcie_write_ctrl.pool = gen_pool_create(ilog2(SRAM_GRANULARITY), -1);
	if (!pcie_write_ctrl.pool)
		goto out;

	pcie_write_ctrl.viraddr = dma_alloc_coherent(NULL, pcie_write_ctrl.size,
		&pcie_write_ctrl.phyaddr, GFP_KERNEL);

	if (!pcie_write_ctrl.viraddr)
		goto out1;

	status = gen_pool_add_virt(pcie_write_ctrl.pool,
				   (unsigned long)pcie_write_ctrl.viraddr,
				   (unsigned long)pcie_write_ctrl.phyaddr,
				   pcie_write_ctrl.size, -1);
	if (status < 0) {
		dma_free_coherent(NULL, pcie_write_ctrl.size,
					  pcie_write_ctrl.viraddr, pcie_write_ctrl.phyaddr);
		goto out1;
	}
out:
	printk("PCIe write alloc area phyaddr %0x8  size %08x\n", 
		pcie_write_ctrl.phyaddr,pcie_write_ctrl.size);
	WARN_ON(status < 0);
	return status;
out1:
	gen_pool_destroy(pcie_write_ctrl.pool);
	goto out;
}
core_initcall(pcie_write_init);
/******************************************************************************/

static int __init pcie_read_init(void)
{
	int status = -ENOMEM;

	pcie_read_ctrl.size = CONFIG_PCIE_DMA_SIZE_READ;

	if(!pcie_read_ctrl.size) {
		/* if size = 0, we don't need pcie alloc */
		status = 0;
		goto out;
	}

	pcie_read_ctrl.pool = gen_pool_create(ilog2(SRAM_GRANULARITY), -1);
	if (!pcie_read_ctrl.pool)
		goto out;

	pcie_read_ctrl.viraddr = dma_alloc_coherent(NULL, pcie_read_ctrl.size,
		&pcie_read_ctrl.phyaddr, GFP_KERNEL);
	
	if (!pcie_read_ctrl.viraddr)
		goto out1;

	status = gen_pool_add_virt(pcie_read_ctrl.pool,
				   (unsigned long)pcie_read_ctrl.viraddr,
				   (unsigned long)pcie_read_ctrl.phyaddr,
				   pcie_read_ctrl.size, -1);
	if (status < 0) {
		dma_free_coherent(NULL, pcie_read_ctrl.size,
				  pcie_read_ctrl.viraddr, pcie_read_ctrl.phyaddr);
		goto out1;
	}
out:
	printk("PCIe read alloc area phyaddr %0x8  size %08x\n", 
		pcie_read_ctrl.phyaddr,pcie_read_ctrl.size);
	WARN_ON(status < 0);
	return status;
out1:
	gen_pool_destroy(pcie_read_ctrl.pool);
	goto out;
}
core_initcall(pcie_read_init);

