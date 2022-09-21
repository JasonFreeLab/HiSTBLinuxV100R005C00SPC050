#ifndef _TEE_DRV_TZASC_COMMON_H_
#define _TEE_DRV_TZASC_COMMON_H_

#include "tee_os_hal.h"

/*
 * Suppress GCC warning on expansion of the macro with no argument:
 *  'ISO C99 requires at least one argument for the "..." in a variadic macro'
 * Occurs when '-pedantic' is combined with '-std=gnu99'.
 * Suppression applies only to this file and the expansion of macros defined in
 * this file.
 */
#pragma GCC system_header


#undef TZASC_REG_TRACE

#define TZASC_PRINTF(fmt...)       HI_LOG_INFO(fmt)
#define TZASC_ERROR(fmt...)        HI_LOG_ERROR(fmt)
#ifdef TEE_DRV_TZASC_DEBUG
#define TZASC_DEBUG(fmt...)        HI_LOG_DEBUG(fmt)
#define TZASC_INFO(fmt...)         HI_LOG_INFO(fmt)
#else
#define TZASC_DEBUG(fmt...)
#define TZASC_INFO(fmt...)
#endif

#define TZASC_ASSERT(expr) \
	do { \
		if (!(expr)) { \
			TZASC_PRINTF("TZASC ASSERT: Assertion [%s] failed. File[%s] Func[%s] Line[%d]\n", #expr, __FILE__, __func__, __LINE__); \
			tzasc_sys_reset(); \
		} \
	} while (0)


#define TZASC_DSB()                       asm volatile ("dsb")

#ifdef TZASC_REG_TRACE
#define TZASC_READ(addr)             ({ unsigned int __v = (*(volatile unsigned int *)(tee_hal_phys_to_virt(addr))); TZASC_DSB(); TZASC_PRINTF("read %p = 0x%X\n", (unsigned int *)(tee_hal_phys_to_virt(addr)), __v);__v; })
#define TZASC_WRITE(val, addr)       ({ TZASC_DSB(); TZASC_PRINTF("write %p = 0x%X\n", (unsigned int *)(tee_hal_phys_to_virt(addr)), val); ((*(volatile unsigned int *)(tee_hal_phys_to_virt(addr))) = (val)); TZASC_DSB();})
#else
#define TZASC_READ(addr)	({ unsigned int __v = (*(volatile unsigned int *)(tee_hal_phys_to_virt(addr))); TZASC_DSB(); __v; })
#define TZASC_WRITE(val, addr) ({ TZASC_DSB(); ((*(volatile unsigned int *)(tee_hal_phys_to_virt(addr))) = (val)); TZASC_DSB();})
#endif

/* for security */
#define TZASC_SEC_WRITE(value, addr) do { \
	volatile unsigned int v; \
	TZASC_WRITE(value, addr); \
	v = TZASC_READ(addr); \
	if (value != v) { \
		TZASC_ERROR("Fail to set 0x%X(0x%X) to 0x%X\n", addr, v, value); \
		tzasc_sys_reset(); \
	} \
	tzasc_random_delay(); \
	v = TZASC_READ(addr); \
	v = ~v; \
	if (~value != v) { \
		TZASC_ERROR("Fail to set 0x%X(~0x%X) to 0x%X\n", addr, v, value); \
		tzasc_sys_reset(); \
	} \
	tzasc_random_delay(); \
	v = TZASC_READ(addr); \
	if (value != v) { \
		TZASC_ERROR("Fail to set 0x%X(0x%X) to 0x%X\n", addr, v, value); \
		tzasc_sys_reset(); \
	} \
} while(0);


#define BITS_MASK(nbits)			((1u << nbits) - 1)
#define GET_BITS_SHIFT(x, nbits, nshift)	(((x) >> nshift) & BITS_MASK(nbits))
#define BITS_SHIFT_MASK(nbits, nshift)		(BITS_MASK(nbits) << nshift)
#define BITS_SHIFT_VAL(x, nbits, nshift)	(((x) & BITS_MASK(nbits)) << nshift)

unsigned int tzasc_get_bit(unsigned long long addr, unsigned int shift);
void tzasc_set_bit(unsigned long long addr, unsigned int shift);
void tzasc_clear_bit(unsigned long long addr, unsigned int shift);

void tzasc_dump_addr(const char *name, char *addr, unsigned int size);
void tzasc_sys_reset(void);
void tzasc_random_delay(void);
int tzasc_request_irq(unsigned int irq, void *handler, void *arg);

static inline unsigned int tzasc_read_bits(unsigned long long addr, unsigned int shift, unsigned int bits)
{
	unsigned int reg_val = TZASC_READ((unsigned int)addr);
	return GET_BITS_SHIFT(reg_val, bits, shift);
}

static inline void tzasc_write_bits(unsigned long long addr, unsigned int value, unsigned int shift, unsigned int bits)
{
	unsigned int reg_val = TZASC_READ((unsigned int)addr);
	reg_val &= ~(BITS_SHIFT_MASK(bits, shift));
	reg_val |= BITS_SHIFT_VAL(value, bits, shift);
	TZASC_SEC_WRITE(reg_val, (unsigned int)addr);
}

#endif /* _TEE_DRV_TZASC_COMMON_H_ */
