/*
 * include/asm-arm/macro.h
 *
 * Copyright (C) 2009 Jean-Christophe PLAGNIOL-VILLARD <plagnioj@jcrosoft.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_ARM_MACRO_H__
#define __ASM_ARM_MACRO_H__
#ifdef __ASSEMBLY__

#ifdef CONFIG_ARM64
/*
 * Register aliases.
 */
lr	.req	x30

/*
 * Branch according to exception level
 */
.macro	switch_el, xreg, el3_label, el2_label, el1_label
	mrs	\xreg, CurrentEL
	cmp	\xreg, 0xc
	b.eq	\el3_label
	cmp	\xreg, 0x8
	b.eq	\el2_label
	cmp	\xreg, 0x4
	b.eq	\el1_label
.endm
#endif /* CONFIG_ARM64 */

#endif /* __ASSEMBLY__ */
#endif /* __ASM_ARM_MACRO_H__ */
