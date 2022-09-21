#ifndef TEE_DRV_SP804_TIMER_H
#define TEE_DRV_SP804_TIMER_H

typedef void (*timer_callback_func)(void);

void sp804_init(timer_callback_func func);

void sp804_set_nextevent(unsigned long next);

unsigned long long sp804_clocksource_gettime(void);

unsigned long usec_to_clocktime(unsigned long us);

#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || \
 defined (CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3796mv200)

#define SP804_TIMER_CLK_MHZ	24
/**
 * IRQ number and REG BASE are both soc relative
 * currently hi3798cvx/hi3796cvx are supported
 * Fix it later
 */
#define TIMER1_IRQ	50
#define TIMER3_IRQ	88
#define TIMER_1_BASE	0xf8008100
#define TIMER_3_BASE	0xf8009100
#else
#error "SecTimer is not support for this soc, please check"
#endif

#define TIMER_LOAD	0x00			/* ACVR rw */
#define TIMER_VALUE	0x04			/* ACVR ro */
#define TIMER_CTR	0x08			/* ACVR rw */
#define TIMER_CTR_ONESHOT	(1 << 0)	/*  CVR */
#define TIMER_CTR_32BIT	(1 << 0)	/*  CVR */
#define TIMER_CTR_64BIT	(1 << 1)	/*  CVR */
#define TIMER_CTR_DIV1		(0 << 2)	/* ACVR */
#define TIMER_CTR_DIV16	(1 << 2)	/* ACVR */
#define TIMER_CTR_DIV256	(2 << 2)	/* ACVR */
#define TIMER_CTR_IE		(1 << 5)	/*   VR */
#define TIMER_CTR_PERIODIC	(1 << 6)	/* ACVR */
#define TIMER_CTR_ENABLE	(1 << 7)	/* ACVR */

#define TIMER_INTCLR	0x0c			/* ACVR wo */
#define TIMER_RIS	0x10			/*  CVR ro */
#define TIMER_MIS	0x14			/*  CVR ro */
#define TIMER_BGLOAD	0x18			/*  CVR rw */
#define TIMER_LOCK	0x1c
#define TIMER_HIGH_LOAD	0x20
#define TIMER_HIGH_VALUE	0x24
#define TIMER_HIGH_BGLOAD	0x38

#endif
