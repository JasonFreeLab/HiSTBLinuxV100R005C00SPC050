/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * (C) Copyright 2016
 * Alexander Graf <agraf@suse.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <system.h>
#include <mmu.h>
#include <types.h>


void mem_layout_init(gd_t *gd)
{
	/* Note: mem_map size is mem_map[4] */
	u32 i=0;

	/* DDR RAM */
	gd->mem_map[i].phys = 0x0UL;
	gd->mem_map[i].virt = 0x0UL;
	gd->mem_map[i].size = 0x40000000UL;
	gd->mem_map[i].attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE;

	/* UART Register, MMIO regions - Internal register */	 
	i++;
	gd->mem_map[i].phys = 0xC0000000UL;
	gd->mem_map[i].virt = 0xC0000000UL;
	gd->mem_map[i].size = 0x40000000UL;
	gd->mem_map[i].attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE;

	i++;
	gd->mem_map[i].attrs = 0;
			 	
}

#ifndef CONFIG_SYS_DCACHE_OFF

/*
 *  With 4k page granule, a virtual address is split into 4 lookup parts
 *  spanning 9 bits each:
 *
 *    _______________________________________________
 *   |       |       |       |       |       |       |
 *   |   0   |  Lv0  |  Lv1  |  Lv2  |  Lv3  |  off  |
 *   |_______|_______|_______|_______|_______|_______|
 *     63-48   47-39   38-30   29-21   20-12   11-00
 *
 *             mask        page size
 *
 *    Lv0: FF8000000000       --
 *    Lv1:   7FC0000000       1G
 *    Lv2:     3FE00000       2M
 *    Lv3:       1FF000       4K
 *    off:          FFF
 */

u64 get_tcr(struct mm_region *mem_map, int el, u64 *pips, u64 *pva_bits)
{
	u64 max_addr = 0;
	u64 ips, va_bits;
	u64 tcr;
	int i;

	/* Find the largest address we need to support */
	for (i = 0; mem_map[i].size || mem_map[i].attrs; i++)
		max_addr = max(max_addr, mem_map[i].virt + mem_map[i].size);

	/* Calculate the maximum physical (and thus virtual) address */
	if (max_addr > (1ULL << 44)) {
		ips = 5;
		va_bits = 48;
	} else  if (max_addr > (1ULL << 42)) {
		ips = 4;
		va_bits = 44;
	} else  if (max_addr > (1ULL << 40)) {
		ips = 3;
		va_bits = 42;
	} else  if (max_addr > (1ULL << 36)) {
		ips = 2;
		va_bits = 40;
	} else  if (max_addr > (1ULL << 32)) {
		ips = 1;
		va_bits = 36;
	} else {
		ips = 0;
		va_bits = 32;
	}

	if (el == 1) {
		tcr = TCR_EL1_RSVD | (ips << 32) | TCR_EPD1_DISABLE;
	} else if (el == 2) {
		tcr = TCR_EL2_RSVD | (ips << 16);
	} else {
		tcr = TCR_EL3_RSVD | (ips << 16);
	}

	/* PTWs cacheable, inner/outer WBWA and inner shareable */
	tcr |= TCR_TG0_4K | TCR_SHARED_INNER | TCR_ORGN_WBWA | TCR_IRGN_WBWA;
	tcr |= TCR_T0SZ(va_bits);

	if (pips)
		*pips = ips;
	if (pva_bits)
		*pva_bits = va_bits;

	return tcr;
}

#define MAX_PTE_ENTRIES 512

static int pte_type(u64 *pte)
{
	return *pte & PTE_TYPE_MASK;
}

/* Returns the LSB number for a PTE on level <level> */
static int level2shift(int level)
{
	/* Page is 12 bits wide, every level translates 9 bits */
	return (12 + 9 * (3 - level));
}

static u64 *find_pte(gd_t *gd, u64 addr, int level)
{
	int start_level = 0;
	u64 *pte;
	u64 idx;
	u64 va_bits;
	int i;
			
	get_tcr((struct mm_region *)&gd->mem_map, 0, NULL, &va_bits);
	if (va_bits < 39)
		start_level = 1;

	if (level < start_level)
		return NULL;

	/* Walk through all page table levels to find our PTE */
	pte = (u64*)gd->arch.tlb_addr;
	for (i = start_level; i < 4; i++) {
		idx = (addr >> level2shift(i)) & 0x1FF;
		pte += idx;

		/* Found it */
		if (i == level)
			return pte;
		/* PTE is no table (either invalid or block), can't traverse */
		if (pte_type(pte) != PTE_TYPE_TABLE)
			return NULL;
		/* Off to the next level */
		pte = (u64*)(*pte & 0x0000fffffffff000ULL);
	}

	/* Should never reach here */
	return NULL;
}

/* Returns and creates a new full table (512 entries) */
static u64 *create_table(gd_t *gd)
{
	u64 *new_table = (u64*)gd->arch.tlb_fillptr;
	u64 pt_len = MAX_PTE_ENTRIES * sizeof(u64);

	/* Allocate MAX_PTE_ENTRIES pte entries */
	gd->arch.tlb_fillptr += pt_len;

	if (gd->arch.tlb_fillptr - gd->arch.tlb_addr > gd->arch.tlb_size) {
		uart_early_puts(5);
		__asm__ __volatile__ (" b .");
	}

	/* Mark all entries as invalid */
	memset(new_table, 0, pt_len);

	return new_table;
}

static void set_pte_table(u64 *pte, u64 *table)
{
	/* Point *pte to the new table */
	*pte = PTE_TYPE_TABLE | (ulong)table;
}

/* Splits a block PTE into table with subpages spanning the old block */
static void split_block(gd_t *gd, u64 *pte, int level)
{
	u64 old_pte = *pte;
	u64 *new_table;
	u64 i = 0;
	/* level describes the parent level, we need the child ones */
	int levelshift = level2shift(level + 1);

	if (pte_type(pte) != PTE_TYPE_BLOCK) {
		uart_early_puts(6);
		__asm__ __volatile__ (" b .");
	}

	new_table = create_table(gd);

	for (i = 0; i < MAX_PTE_ENTRIES; i++) {
		new_table[i] = old_pte | (i << levelshift);

		/* Level 3 block PTEs have the table type */
		if ((level + 1) == 3)
			new_table[i] |= PTE_TYPE_TABLE;
	}

	/* Set the new table into effect */
	set_pte_table(pte, new_table);
}

/* Add one mm_region map entry to the page tables */
static void add_map(gd_t *gd, struct mm_region *map)
{
	u64 *pte;
	u64 virt = map->virt;
	u64 phys = map->phys;
	u64 size = map->size;
	u64 attrs = map->attrs | PTE_TYPE_BLOCK | PTE_BLOCK_AF;
	u64 blocksize;
	int level;
	u64 *new_table;

	while (size) {
		pte = find_pte(gd, virt, 0);
		if (pte && (pte_type(pte) == PTE_TYPE_FAULT)) {
			new_table = create_table(gd);
			set_pte_table(pte, new_table);
		}

		for (level = 1; level < 4; level++) {
			pte = find_pte(gd, virt, level);
			if (!pte)
				uart_early_puts(7);

			blocksize = 1ULL << level2shift(level);
			if (size >= blocksize && !(virt & (blocksize - 1))) {
				/* Page fits, create block PTE */
				*pte = phys | attrs;
				virt += blocksize;
				phys += blocksize;
				size -= blocksize;
				break;
			} else if (pte_type(pte) == PTE_TYPE_FAULT) {
				/* Page doesn't fit, create subpages */
				new_table = create_table(gd);
				set_pte_table(pte, new_table);
			} else if (pte_type(pte) == PTE_TYPE_BLOCK) {
				split_block(gd, pte, level);
			}
		}
	}
}

enum pte_type {
	PTE_INVAL,
	PTE_BLOCK,
	PTE_LEVEL,
};

/*
 * This is a recursively called function to count the number of
 * page tables we need to cover a particular PTE range. If you
 * call this with level = -1 you basically get the full 48 bit
 * coverage.
 */
static int count_required_pts(gd_t *gd, u64 addr, int level, u64 maxaddr)
{
	int levelshift = level2shift(level);
	u64 levelsize = 1ULL << levelshift;
	u64 levelmask = levelsize - 1;
	u64 levelend = addr + levelsize;
	int r = 0;
	int i;
	enum pte_type pte_type = PTE_INVAL;

	for (i = 0; gd->mem_map[i].size || gd->mem_map[i].attrs; i++) {
		struct mm_region *map = &gd->mem_map[i];
		u64 start = map->virt;
		u64 end = start + map->size;

		/* Check if the PTE would overlap with the map */
		if (max(addr, start) <= min(levelend, end)) {
			start = max(addr, start);
			end = min(levelend, end);

			/* We need a sub-pt for this level */
			if ((start & levelmask) || (end & levelmask)) {
				pte_type = PTE_LEVEL;
				break;
			}

			/* Lv0 can not do block PTEs, so do levels here too */
			if (level <= 0) {
				pte_type = PTE_LEVEL;
				break;
			}

			/* PTE is active, but fits into a block */
			pte_type = PTE_BLOCK;
		}
	}

	/*
	 * Block PTEs at this level are already covered by the parent page
	 * table, so we only need to count sub page tables.
	 */
	if (pte_type == PTE_LEVEL) {
		int sublevel = level + 1;
		u64 sublevelsize = 1ULL << level2shift(sublevel);

		/* Account for the new sub page table ... */
		r = 1;

		/* ... and for all child page tables that one might have */
		for (i = 0; i < MAX_PTE_ENTRIES; i++) {
			r += count_required_pts(gd, addr, sublevel, maxaddr);
			addr += sublevelsize;

			if (addr >= maxaddr) {
				/*
				 * We reached the end of address space, no need
				 * to look any further.
				 */
				break;
			}
		}
	}

	return r;
}

/* Returns the estimated required size of all page tables */
__weak u64 get_page_table_size(gd_t *gd)
{
	u64 one_pt = MAX_PTE_ENTRIES * sizeof(u64);
	u64 size = 0;
	u64 va_bits;
	int start_level = 0;

	get_tcr(gd->mem_map, 0, NULL, &va_bits);
	if (va_bits < 39)
		start_level = 1;

	/* Account for all page tables we would need to cover our memory map */
	size = one_pt * count_required_pts(gd, 0, start_level - 1, 1ULL << va_bits);

	/*
	 * We need to duplicate our page table once to have an emergency pt to
	 * resort to when splitting page tables later on
	 */
	size *= 2;

	/*
	 * We may need to split page tables later on if dcache settings change,
	 * so reserve up to 4 (random pick) page tables for that.
	 */
	size += one_pt * 4;

	return size;
}

void setup_pgtables(gd_t *gd)
{
	int i;

	if (!gd->arch.tlb_fillptr || !gd->arch.tlb_addr) {
		uart_early_puts(8);
		__asm__ __volatile__ (" b .");
	}

	/*
	 * Allocate the first level we're on with invalidate entries.
	 * If the starting level is 0 (va_bits >= 39), then this is our
	 * Lv0 page table, otherwise it's the entry Lv1 page table.
	 */
	create_table(gd);

	/* Now add all MMU table entries one after another to the table */
	for (i = 0; gd->mem_map[i].size || gd->mem_map[i].attrs; i++) {
		add_map(gd, &gd->mem_map[i]);
	}
}

static void setup_all_pgtables(gd_t *gd)
{
	u64 tlb_addr = gd->arch.tlb_addr = (u64)__page_table_start;
	u64 tlb_size = gd->arch.tlb_size = (u64)(__page_table_end - __page_table_start);

	/* Reset the fill ptr */
	gd->arch.tlb_fillptr = tlb_addr;

	/* Create normal system page tables */
	setup_pgtables(gd);
	
	/* Create emergency page tables */
	gd->arch.tlb_size -= (uintptr_t)gd->arch.tlb_fillptr -
			     (uintptr_t)gd->arch.tlb_addr;
	gd->arch.tlb_addr = gd->arch.tlb_fillptr;
	setup_pgtables(gd);
	gd->arch.tlb_emerg = gd->arch.tlb_addr;
	gd->arch.tlb_addr = tlb_addr;
	gd->arch.tlb_size = tlb_size;
}

/* to activate the MMU we need to set up virtual memory */
__weak void mmu_setup(void)
{
	int el;
	gd_t gd;
	
	memset(&gd, 0x0, sizeof(gd_t));
	mem_layout_init(&gd);

	/* Set up page tables only once */
	setup_all_pgtables(&gd);

	el = current_el();
	set_ttbr_tcr_mair(el, gd.arch.tlb_addr, get_tcr((struct mm_region *)&gd.mem_map, el, NULL, NULL),
			  MEMORY_ATTRIBUTES);

	/* enable the mmu */
	set_sctlr(get_sctlr() | CR_M);
}

/*
 * Performs a invalidation of the entire data cache at all levels
 */
void invalidate_dcache_all(void)
{
	__asm_invalidate_dcache_all();
	__asm_invalidate_l3_dcache();
}

/*
 * Performs a clean & invalidation of the entire data cache at all levels.
 * This function needs to be inline to avoid using stack.
 * __asm_flush_l3_dcache return status of timeout
 */
inline void flush_dcache_all(void)
{
	int ret;

	__asm_flush_dcache_all();
	ret = __asm_flush_l3_dcache();
	if (ret)
		uart_early_puts(9);
}

/*
 * Invalidates range in all levels of D-cache/unified cache
 */
void invalidate_dcache_range(unsigned long start, unsigned long stop)
{
	__asm_flush_dcache_range(start, stop);
}

/*
 * Flush range(clean & invalidate) from all levels of D-cache/unified cache
 */
void flush_dcache_range(unsigned long start, unsigned long stop)
{
	__asm_flush_dcache_range(start, stop);
}

void dcache_enable(void)
{
	/* The data cache is not active unless the mmu is enabled */
	if (!(get_sctlr() & CR_M)) {
		invalidate_dcache_all();
		__asm_invalidate_tlb_all();
		mmu_setup();
	}

	set_sctlr(get_sctlr() | CR_C);
}

void dcache_disable(void)
{
	uint32_t sctlr;

	sctlr = get_sctlr();

	/* if cache isn't enabled no need to disable */
	if (!(sctlr & CR_C))
		return;

	set_sctlr(sctlr & ~(CR_C|CR_M));

	flush_dcache_all();
	__asm_invalidate_tlb_all();
}

int dcache_status(void)
{
	return (get_sctlr() & CR_C) != 0;
}

u64 *__weak arch_get_page_table(void) {

	return NULL;
}

static bool is_aligned(u64 addr, u64 size, u64 align)
{
	return !(addr & (align - 1)) && !(size & (align - 1));
}

static u64 set_one_region(gd_t *gd, u64 start, u64 size, u64 attrs, int level)
{
	int levelshift = level2shift(level);
	u64 levelsize = 1ULL << levelshift;
	u64 *pte = find_pte(gd, start, level);

	/* Can we can just modify the current level block PTE? */
	if (is_aligned(start, size, levelsize)) {
		*pte &= ~PMD_ATTRINDX_MASK;
		*pte |= attrs;
		return levelsize;
	}

	/* Unaligned or doesn't fit, maybe split block into table */

	/* Maybe we need to split the block into a table */
	if (pte_type(pte) == PTE_TYPE_BLOCK)
		split_block(gd, pte, level);

	/* And then double-check it became a table or already is one */
	if (pte_type(pte) != PTE_TYPE_TABLE)
		uart_early_puts(10);

	/* Roll on to the next page table level */
	return 0;
}

void mmu_set_region_dcache_behaviour(gd_t *gd, phys_addr_t start, size_t size,
				     enum dcache_option option)
{
	u64 attrs = PMD_ATTRINDX(option);
	u64 real_start = start;
	u64 real_size = size;

	if (!gd->arch.tlb_emerg)
		uart_early_puts(11);

	/*
	 * We can not modify page tables that we're currently running on,
	 * so we first need to switch to the "emergency" page tables where
	 * we can safely modify our primary page tables and then switch back
	 */
	__asm_switch_ttbr(gd->arch.tlb_emerg);

	/*
	 * Loop through the address range until we find a page granule that fits
	 * our alignment constraints, then set it to the new cache attributes
	 */
	while (size > 0) {
		int level;
		u64 r;

		for (level = 1; level < 4; level++) {
			r = set_one_region(gd, start, size, attrs, level);
			if (r) {
				/* PTE successfully replaced */
				size -= r;
				start += r;
				break;
			}
		}

	}

	/* We're done modifying page tables, switch back to our primary ones */
	__asm_switch_ttbr(gd->arch.tlb_addr);

	/*
	 * Make sure there's nothing stale in dcache for a region that might
	 * have caches off now
	 */
	flush_dcache_range(real_start, real_start + real_size);
}

#else	/* CONFIG_SYS_DCACHE_OFF */

/*
 * For SPL builds, we may want to not have dcache enabled. Any real U-Boot
 * running however really wants to have dcache and the MMU active. Check that
 * everything is sane and give the developer a hint if it isn't.
 */
#ifndef CONFIG_SPL_BUILD
#error Please describe your MMU layout in CONFIG_SYS_MEM_MAP and enable dcache.
#endif

void invalidate_dcache_all(void)
{
}

void flush_dcache_all(void)
{
}

void dcache_enable(void)
{
}

void dcache_disable(void)
{
}

int dcache_status(void)
{
	return 0;
}

void mmu_set_region_dcache_behaviour(phys_addr_t start, size_t size,
				     enum dcache_option option)
{
}

#endif	/* CONFIG_SYS_DCACHE_OFF */

#ifndef CONFIG_SYS_ICACHE_OFF

void invalidate_icache_all(void)
{
	__asm_invalidate_icache_all();
	__asm_invalidate_l3_icache();
}

void icache_enable(void)
{
	invalidate_icache_all();
	set_sctlr(get_sctlr() | CR_I);
}

void icache_disable(void)
{
	set_sctlr(get_sctlr() & ~CR_I);
}

int icache_status(void)
{
	return (get_sctlr() & CR_I) != 0;
}

#else	/* CONFIG_SYS_ICACHE_OFF */

void icache_enable(void)
{
}

void icache_disable(void)
{
}

int icache_status(void)
{
	return 0;
}

void invalidate_icache_all(void)
{
}

#endif	/* CONFIG_SYS_ICACHE_OFF */

/*
 * Enable dCache & iCache, whether cache is actually enabled
 * depend on CONFIG_SYS_DCACHE_OFF and CONFIG_SYS_ICACHE_OFF
 */
void __weak enable_caches(void)
{
	debug(0);	
	icache_enable();
	debug(1);
	dcache_enable();
}
