#ifndef __ASM_ARM_SYSTEM_H
#define __ASM_ARM_SYSTEM_H

#ifdef CONFIG_ARM64
#include <mmu.h>

/*
 * SCTLR_EL1/SCTLR_EL2/SCTLR_EL3 bits definitions
 */
#define CR_M		(1 << 0)	/* MMU enable			*/
#define CR_A		(1 << 1)	/* Alignment abort enable	*/
#define CR_C		(1 << 2)	/* Dcache enable		*/
#define CR_SA		(1 << 3)	/* Stack Alignment Check Enable	*/
#define CR_I		(1 << 12)	/* Icache enable		*/
#define CR_WXN		(1 << 19)	/* Write Permision Imply XN	*/
#define CR_EE		(1 << 25)	/* Exception (Big) Endian	*/

#ifndef __ASSEMBLY__
#include <types.h>

u64 get_page_table_size(gd_t *gd);
#define PGTABLE_SIZE	get_page_table_size()

/* 2MB granularity */
#define MMU_SECTION_SHIFT	21
#define MMU_SECTION_SIZE	(1 << MMU_SECTION_SHIFT)

/* These constants need to be synced to the MT_ types in asm/armv8/mmu.h */
enum dcache_option {
	DCACHE_OFF = 0 << 2,
	DCACHE_WRITETHROUGH = 3 << 2,
	DCACHE_WRITEBACK = 4 << 2,
	DCACHE_WRITEALLOC = 4 << 2,
};

#define wfi()				\
	({asm volatile(			\
	"wfi" : : : "memory");		\
	})

static inline unsigned int current_el(void)
{
	unsigned int el;
	asm volatile("mrs %0, CurrentEL" : "=r" (el) : : "cc");
	return el >> 2;
}

static inline unsigned int get_sctlr(void)
{
	unsigned int el, val;

	el = current_el();
	if (el == 1)
		asm volatile("mrs %0, sctlr_el1" : "=r" (val) : : "cc");
	else if (el == 2)
		asm volatile("mrs %0, sctlr_el2" : "=r" (val) : : "cc");
	else
		asm volatile("mrs %0, sctlr_el3" : "=r" (val) : : "cc");

	return val;
}

static inline void set_sctlr(unsigned int val)
{
	unsigned int el;

	el = current_el();
	if (el == 1)
		asm volatile("\n\r"
		"msr sctlr_el1, %0\n\r" : : "r" (val) : "cc");
	else if (el == 2)
		asm volatile("msr sctlr_el2, %0" : : "r" (val) : "cc");
	else
		asm volatile("msr sctlr_el3, %0" : : "r" (val) : "cc");

	asm volatile("isb");
}

static inline unsigned long read_mpidr(void)
{
	unsigned long val;

	asm volatile("mrs %0, mpidr_el1" : "=r" (val));

	return val;
}

#define BSP_COREID	0

void __asm_flush_dcache_all(void);
void __asm_invalidate_dcache_all(void);
void __asm_flush_dcache_range(u64 start, u64 end);
void __asm_invalidate_tlb_all(void);
void __asm_invalidate_icache_all(void);
int __asm_invalidate_l3_dcache(void);
int __asm_flush_l3_dcache(void);
int __asm_invalidate_l3_icache(void);
void __asm_switch_ttbr(u64 new_ttbr);

void armv8_switch_to_el2(void);
void armv8_switch_to_el1(void);
void gic_init(void);
void gic_send_sgi(unsigned long sgino);
void wait_for_wakeup(void);
void protect_secure_region(void);
void smp_kick_all_cpus(void);

void flush_l3_cache(void);

/*
 *Issue a secure monitor call in accordance with ARM "SMC Calling convention",
 * DEN0028A
 *
 * @args: input and output arguments
 *
 */
void smc_call(struct pt_regs *args);

void psci_system_reset(void);
void psci_system_off(void);

#endif	/* __ASSEMBLY__ */

#endif /* CONFIG_ARM64 */

#ifndef __ASSEMBLY__
/**
 * Change the cache settings for a region.
 *
 * \param start		start address of memory region to change
 * \param size		size of memory region to change
 * \param option	dcache option to select
 */
void mmu_set_region_dcache_behaviour(gd_t *gd, phys_addr_t start, size_t size,
				     enum dcache_option option);

#endif /* __ASSEMBLY__ */

#endif
