#include "hi_asm_define.h"
	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"fsp.c"
	.text
	.align	2
	.type	FSP_ClearContext, %function
FSP_ClearContext:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r5, r0, #0
	beq	.L5
	ldr	r6, .L6
	mov	r4, #0
	mov	r0, #8
	ldr	r3, [r6, #12]
	blx	r3
	strb	r4, [r5, #2]
	strb	r4, [r5, #4]
	mov	r1, r4
	strb	r4, [r5, #5]
	mov	r2, #20
	strb	r4, [r5, #3]
	add	r0, r5, #36
	str	r4, [r5, #12]
	str	r4, [r5, #8]
	str	r4, [r5, #16]
	str	r4, [r5, #20]
	str	r4, [r5, #24]
	str	r4, [r5, #32]
	ldr	r3, [r6, #48]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #88
	add	r0, r5, #56
	blx	r3
	add	r0, r5, #21504
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #2816
	add	r0, r0, #144
	blx	r3
	add	r0, r5, #24320
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #2816
	add	r0, r0, #144
	blx	r3
	add	r0, r5, #27136
	ldr	r3, [r6, #48]
	mov	r1, r4
	mov	r2, #256
	add	r0, r0, #144
	blx	r3
	ldr	r3, [r6, #16]
	mov	r0, #8
	blx	r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5:
	ldr	r3, .L6+4
	mov	r2, #136
	ldr	r1, .L6+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L7:
	.align	2
.L6:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC0
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_ClearContext, .-FSP_ClearContext
	.align	2
	.type	FSP_IsSpecialFrm.part.3, %function
FSP_IsSpecialFrm.part.3:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L18
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	sub	r3, r1, #1
	cmn	r3, #3
	bhi	.L13
	add	r3, r0, #475136
	ldr	ip, [r3, #936]
	cmp	ip, #0
	beq	.L13
	ldr	r3, [r3, #412]
	cmp	r1, r3
	beq	.L16
	mov	r2, #0
	b	.L10
.L11:
	add	r3, r3, #412
	ldr	r3, [r0, r3]
	cmp	r1, r3
	beq	.L16
.L10:
	add	r2, r2, #1
	cmp	r2, ip
	mov	r3, r2, asl #4
	add	r3, r3, #475136
	bne	.L11
.L13:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L16:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L19:
	.align	2
.L18:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	FSP_IsSpecialFrm.part.3, .-FSP_IsSpecialFrm.part.3
	.align	2
	.global	FSP_Init
	.type	FSP_Init, %function
FSP_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L21
	mov	r2, #128
	mov	r1, #0
	ldr	r0, .L21+4
	ldr	r3, [r3, #48]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	r3
.L22:
	.align	2
.L21:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_Init, .-FSP_Init
	.align	2
	.global	FSP_ConfigAttribute
	.type	FSP_ConfigAttribute, %function
FSP_ConfigAttribute:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L27
	ldr	r3, .L29
	ldr	r3, [r3, r0, asl #2]
	ldr	r2, [r3, #28]
	cmp	r2, #1
	bne	.L28
	ldrb	r2, [r1]	@ zero_extendqisi2
	mov	r0, #0
	strb	r2, [r3, #1]
	ldmfd	sp, {fp, sp, pc}
.L28:
	ldr	r3, .L29+4
	movw	r2, #395
	ldr	r1, .L29+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	ldr	r3, .L29+12
	movw	r2, #394
	ldr	r1, .L29+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L30:
	.align	2
.L29:
	.word	.LANCHOR0
	.word	.LC3
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	FSP_ConfigAttribute, .-FSP_ConfigAttribute
	.align	2
	.global	FSP_ClearContextAll
	.type	FSP_ClearContextAll, %function
FSP_ClearContextAll:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L35
	ldr	r3, .L37
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L36
	ldr	r3, .L37+4
	movw	r2, #27536
	ldrb	r7, [r4, #3]	@ zero_extendqisi2
	mov	r1, #0
	ldrb	r6, [r4, #5]	@ zero_extendqisi2
	mov	r0, r4
	ldrb	r10, [r4]	@ zero_extendqisi2
	ldrb	r9, [r4, #1]	@ zero_extendqisi2
	ldr	r8, [r4, #28]
	ldr	r5, [r4, #32]
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, #0
	strb	r10, [r4]
	strb	r9, [r4, #1]
	str	r8, [r4, #28]
	strb	r7, [r4, #3]
	strb	r6, [r4, #5]
	str	r5, [r4, #32]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L35:
	ldr	r3, .L37+8
	movw	r2, #415
	ldr	r1, .L37+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L36:
	mov	r0, r4
	ldr	r3, .L37+16
	mov	r2, #416
	ldr	r1, .L37+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L38:
	.align	2
.L37:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_ClearContextAll, .-FSP_ClearContextAll
	.align	2
	.global	FSP_EnableInstance
	.type	FSP_EnableInstance, %function
FSP_EnableInstance:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r5, r0
	mov	r4, r1
	bhi	.L43
	ldr	r7, .L45
	ldr	r6, [r7, r0, asl #2]
	cmp	r6, #0
	bne	.L44
	ldr	r3, .L45+4
	movw	r2, #27536
	mov	r1, r6
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	strb	r5, [r4]
	mov	r3, #1
	str	r6, [r4, #32]
	str	r3, [r4, #28]
	mov	r0, r6
	str	r4, [r7, r5, asl #2]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L44:
	ldr	r3, .L45+8
	movw	r2, #442
	ldr	r1, .L45+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L43:
	ldr	r3, .L45+16
	movw	r2, #441
	ldr	r1, .L45+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L46:
	.align	2
.L45:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC5
	.word	.LC1
	.word	.LC2
	UNWIND(.fnend)
	.size	FSP_EnableInstance, .-FSP_EnableInstance
	.align	2
	.global	FSP_DisableInstance
	.type	FSP_DisableInstance, %function
FSP_DisableInstance:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L51
	ldr	r2, .L53
	ldr	r3, [r2, r0, asl #2]
	cmp	r3, #0
	beq	.L52
	ldr	r1, [r3, #28]
	cmp	r1, #1
	moveq	r1, #0
	streq	r1, [r3, #28]
	mov	r3, #0
	str	r3, [r2, r0, asl #2]
	ldmfd	sp, {fp, sp, pc}
.L51:
	ldr	r3, .L53+4
	movw	r2, #458
	ldr	r1, .L53+8
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L52:
	mov	r0, r3
	movw	r2, #459
	ldr	r3, .L53+12
	ldr	r1, .L53+8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L54:
	.align	2
.L53:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_DisableInstance, .-FSP_DisableInstance
	.align	2
	.global	FSP_Exit
	.type	FSP_Exit, %function
FSP_Exit:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r5, .L66
	mov	r4, #0
	b	.L57
.L56:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L65
.L57:
	ldr	r3, [r5, #4]!
	cmp	r3, #0
	beq	.L56
	ldr	r3, [r3, #28]
	cmp	r3, #0
	beq	.L56
	mov	r0, r4
	add	r4, r4, #1
	bl	FSP_DisableInstance
	cmp	r4, #32
	bne	.L57
.L65:
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L67:
	.align	2
.L66:
	.word	.LANCHOR0-4
	UNWIND(.fnend)
	.size	FSP_Exit, .-FSP_Exit
	.align	2
	.global	FSP_ResetInstance
	.type	FSP_ResetInstance, %function
FSP_ResetInstance:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L72
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L71
	bl	FSP_ClearContext
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L71:
	ldr	r3, .L72+4
	movw	r2, #477
	ldr	r1, .L72+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L73:
	.align	2
.L72:
	.word	.LANCHOR0
	.word	.LC4
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_ResetInstance, .-FSP_ResetInstance
	.align	2
	.global	FSP_EmptyInstance
	.type	FSP_EmptyInstance, %function
FSP_EmptyInstance:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r8, r0
	bhi	.L94
	ldr	r3, .L96
	ldr	r6, [r3, r0, asl #2]
	cmp	r6, #0
	beq	.L95
	ldr	r3, .L96+4
	mov	r2, #21504
	mov	r1, #0
	add	r0, r6, #144
	ldr	r3, [r3, #48]
	blx	r3
	ldrsb	r10, [r6, #3]
	cmp	r10, #0
	ble	.L84
	add	r4, r6, #21504
	mov	r7, #0
	add	r4, r4, #152
	mov	r5, r7
	mov	r9, #4
	b	.L83
.L81:
	strb	r5, [r4, #-6]
.L82:
	add	r7, r7, #1
	strb	r5, [r4, #-7]
	cmp	r10, r7
	strb	r5, [r4, #-8]
	str	r5, [r4, #64]
	add	r4, r4, #88
	beq	.L84
.L83:
	cmp	r8, #31
	ldr	r1, [r4]
	bgt	.L81
	mov	r0, r8
	bl	FSP_IsSpecialFrm.part.3
	cmp	r0, #1
	bne	.L81
	strb	r9, [r4, #-6]
	b	.L82
.L84:
	ldrsb	r10, [r6, #4]
	cmp	r10, #0
	ble	.L80
	add	r4, r6, #24320
	mov	r7, #0
	add	r4, r4, #152
	mov	r5, r7
	mov	r9, #4
	b	.L89
.L87:
	strb	r5, [r4, #-6]
.L88:
	add	r7, r7, #1
	strb	r5, [r4, #-7]
	cmp	r7, r10
	strb	r5, [r4, #-8]
	str	r5, [r4, #64]
	add	r4, r4, #88
	beq	.L80
.L89:
	cmp	r8, #31
	ldr	r1, [r4]
	bgt	.L87
	mov	r0, r8
	bl	FSP_IsSpecialFrm.part.3
	cmp	r0, #1
	bne	.L87
	strb	r9, [r4, #-6]
	b	.L88
.L80:
	ldrsb	r1, [r6, #5]
	cmp	r1, #0
	ble	.L86
	add	r3, r6, #27136
	mov	r2, #0
	add	r3, r3, #148
	mov	ip, r2
	mov	r0, #1
.L90:
	add	r2, r2, #1
	strb	r0, [r3]
	cmp	r2, r1
	strb	ip, [r3, #1]
	add	r3, r3, #8
	bne	.L90
.L86:
	mov	r0, #0
	str	r0, [r6, #12]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L94:
	ldr	r3, .L96+8
	movw	r2, #491
	ldr	r1, .L96+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	mov	r0, r6
	ldr	r3, .L96+16
	mov	r2, #492
	ldr	r1, .L96+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L97:
	.align	2
.L96:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_EmptyInstance, .-FSP_EmptyInstance
	.align	2
	.global	FSP_ConfigInstance
	.type	FSP_ConfigInstance, %function
FSP_ConfigInstance:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r0, #31
	bhi	.L108
	cmp	r1, #0
	beq	.L109
	ldr	r3, .L111
	ldr	r4, [r3, r0, asl #2]
	cmp	r4, #0
	beq	.L102
	ldr	r3, [r4, #28]
	cmp	r3, #1
	bne	.L102
	ldr	r3, .L111+4
	ldr	r3, [r3, r0, asl #2]
	add	r3, r3, #471040
	ldr	r3, [r3, #888]
	cmp	r3, #0
	beq	.L110
.L104:
	ldr	r3, .L111+8
	add	r0, r4, #36
	mov	r2, #20
	ldr	r3, [r3, #52]
	blx	r3
	mov	r0, #0
.L100:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L110:
	mov	r0, r4
	str	r1, [fp, #-24]
	bl	FSP_ClearContext
	ldr	r1, [fp, #-24]
	b	.L104
.L102:
	ldr	r3, .L111+12
	mov	r2, #572
	ldr	r1, .L111+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L100
.L108:
	ldr	r3, .L111+20
	movw	r2, #569
	ldr	r1, .L111+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L100
.L109:
	mov	r0, r1
	ldr	r3, .L111+24
	movw	r2, #570
	ldr	r1, .L111+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L100
.L112:
	.align	2
.L111:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC7
	.word	.LC1
	.word	.LC2
	.word	.LC6
	UNWIND(.fnend)
	.size	FSP_ConfigInstance, .-FSP_ConfigInstance
	.align	2
	.global	FSP_ConfigFrameBuf
	.type	FSP_ConfigFrameBuf, %function
FSP_ConfigFrameBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #60)
	sub	sp, sp, #60
	mov	r10, r2
	ldr	r2, .L175
	mov	r6, r0
	ldr	r5, .L175+4
	mov	r9, r1
	mov	r1, #0
	str	r3, [fp, #-76]
	ldr	ip, [r2, #48]
	add	r0, r5, #128
	mov	r2, #1232
	blx	ip
	cmp	r6, #31
	bhi	.L166
	ldr	r4, [r5, r6, asl #2]
	cmp	r4, #0
	beq	.L167
	ldr	r3, .L175+8
	ldr	r1, [r3, r6, asl #2]
	add	r3, r1, #475136
	ldr	r3, [r3, #948]
	cmp	r3, #1
	beq	.L117
	mov	r0, r6
	bl	VCTRL_GetChanCapLevel
	cmp	r0, #32
	bls	.L168
	ldrsb	r3, [r4, #36]
	cmp	r3, #1
	bne	.L169
	ldr	lr, [r4, #40]
	ldr	r7, [r4, #44]
	ldr	r3, .L175+8
	mul	ip, r7, lr
	ldr	r1, [r3, r6, asl #2]
.L148:
	ldr	r2, [r1, #144]
	ldr	r3, [r1, #148]
	mul	r0, r3, r2
	cmp	r0, ip
	blt	.L170
	ldr	r3, [r1, #1384]
	ldrsb	r8, [r4, #37]
	cmp	r3, #1
	beq	.L171
.L123:
	add	r1, r1, #471040
	ldr	r2, .L175+12
	ldr	r3, [r1, #896]
	ldr	ip, [r2, #64]
	cmp	r8, r3
	movne	r3, #1
	moveq	r3, #0
	str	r3, [r1, #912]
	cmp	ip, #0
	ldrsb	r3, [r4, #37]
	str	r3, [r1, #896]
	beq	.L127
	ldr	r7, .L175+4
	mov	r0, r9
	ldr	r3, [r4, #44]
	mov	r1, r10
	ldr	r2, [r4, #40]
	add	r9, r7, #128
	str	r6, [sp, #12]
	mov	r10, #32
	str	r9, [sp, #16]
	ldrsb	lr, [r4, #36]
	stmib	sp, {r10, lr}
	ldrsb	lr, [r4, #39]
	str	lr, [sp]
	blx	ip
	ldr	r3, .L175+8
	ldr	r2, [r3, r6, asl #2]
	add	r2, r2, #471040
	ldr	r2, [r2, #3280]
	cmp	r2, #32
	movge	r2, #32
	strb	r2, [r4, #5]
	cmp	r0, #2
	mov	r10, r0
	beq	.L172
	cmp	r0, #0
	bne	.L130
	ldr	r2, [r7, #176]
	mov	r0, #31
	ldr	r1, .L175+16
	strb	r2, [r4, #2]
	ldr	r3, [r3, r6, asl #2]
	str	r10, [r3, #1432]
	strb	r10, [r3, #1456]
	bl	dprint_vfmw
	ldr	r3, [r7, #176]
	cmp	r8, r3
	bgt	.L173
	strb	r10, [r4, #4]
	mov	r0, #8
	ldr	r3, [r7, #176]
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r4, #3]
	ldr	r3, .L175
	ldr	r3, [r3, #12]
	blx	r3
	ldr	r3, [r7, #188]
	cmp	r3, #0
	beq	.L174
	ldr	r3, [r7, #132]
	mov	r2, r10
	ldr	r1, [r4, #16]
	mov	r10, #88
	mov	r8, r6
	str	r3, [fp, #-64]
	add	r3, r7, #204
	str	r3, [fp, #-52]
	ldr	r3, [r7, #136]
	str	r3, [fp, #-68]
	ldr	r3, [r7, #140]
	str	r3, [fp, #-72]
	ldr	r3, [r4, #40]
	str	r3, [fp, #-56]
	ldr	r3, [r4, #44]
	str	r3, [fp, #-60]
.L138:
	mla	r3, r10, r1, r4
	ldr	r0, .L175+8
	ldr	lr, [fp, #-52]
	ldr	ip, [r0, r8, asl #2]
	add	r0, r3, #21504
	mov	r3, #0
	str	r1, [r0, #148]
	ldr	r6, [r9, #464]
	str	ip, [fp, #-48]
	str	r6, [r0, #152]
	ldr	ip, [r9, #468]
	ldr	r6, [r5, #164]
	str	ip, [r0, #156]
	ldr	ip, [lr, #4]!
	str	r6, [r0, #204]
	str	ip, [r0, #164]
	ldr	ip, [fp, #-64]
	str	lr, [fp, #-52]
	ldr	lr, [r5, #172]
	str	ip, [r0, #168]
	ldr	ip, [fp, #-68]
	str	ip, [r0, #172]
	ldr	ip, [r5, #148]
	str	ip, [r0, #176]
	ldr	ip, [r5, #156]
	str	ip, [r0, #180]
	ldr	ip, [fp, #-72]
	str	ip, [r0, #188]
	ldr	ip, [r5, #160]
	str	ip, [r0, #184]
	ldr	ip, [fp, #-48]
	add	r7, ip, #475136
	ldr	ip, [fp, #-56]
	str	ip, [r0, #196]
	ldr	ip, [r5, #144]
	str	ip, [r0, #192]
	ldr	ip, [fp, #-60]
	str	ip, [r0, #200]
	ldr	ip, [r5, #168]
	str	lr, [r0, #212]
	strb	r3, [r0, #145]
	str	ip, [r0, #208]
	strb	r3, [r0, #146]
	ldr	r3, [r7, #940]
	ldr	r0, [r5, r8, asl #2]
	cmp	r3, #0
	bne	.L135
	ldr	lr, [r7, #936]
	cmp	lr, #0
	beq	.L135
	ldr	r1, [r0, #16]
	ldr	ip, [fp, #-48]
	mla	r0, r10, r1, r0
	add	r1, r0, #21504
	add	r0, r1, #144
	ldr	lr, [r1, #152]
.L137:
	mov	r1, r3, asl #4
	add	r3, r3, #1
	add	r1, r1, #475136
	add	r1, r1, #412
	ldr	r1, [ip, r1]
	cmp	lr, r1
	moveq	r1, #4
	streqb	r1, [r0, #2]
	ldr	r1, [r7, #936]
	cmp	r3, r1
	bcc	.L137
	ldr	r3, [r4, #40]
	ldr	r1, [r4, #16]
	str	r3, [fp, #-56]
	ldr	r3, [r4, #44]
	str	r3, [fp, #-60]
.L135:
	mla	r3, r10, r1, r4
	mov	r0, #1
	add	r1, r1, #1
	add	r2, r2, #1
	add	r9, r9, #12
	add	r3, r3, #21504
	str	r0, [r3, #228]
	str	r1, [r4, #16]
	ldr	r3, [r5, #188]
	cmp	r3, r2
	bhi	.L138
.L134:
	ldr	r3, [r5, #196]
	cmp	r3, #0
	beq	.L143
	ldr	r1, [r4, #24]
	mov	r0, #88
	ldr	r2, .L175+20
	mov	r3, #0
	add	ip, r1, #1
	mla	r1, r0, r1, r4
	add	r1, r1, #21504
	add	r1, r1, #160
.L142:
	ldr	lr, [r2, #848]
	add	r0, ip, r3
	add	r3, r3, #1
	add	r2, r2, #12
	str	lr, [r1], #88
	str	r0, [r4, #24]
	ldr	r0, [r5, #196]
	cmp	r0, r3
	bhi	.L142
.L143:
	ldr	r3, [r5, #184]
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r4, #5]
	ldr	r3, [r5, #192]
	cmp	r3, #0
	beq	.L141
	ldr	lr, [r4, #20]
	mov	r1, #0
	ldr	r0, .L175+20
	mov	r7, r1
	add	r2, lr, #3408
	add	lr, lr, #1
	add	r2, r2, #2
	mov	r6, #1
	add	r2, r4, r2, lsl #3
.L144:
	ldr	r3, [r0, #208]
	add	ip, lr, r1
	add	r1, r1, #1
	add	r0, r0, #8
	add	r2, r2, #8
	str	r3, [r2, #-8]
	ldr	r3, [r4, #20]
	add	r3, r3, #3408
	add	r3, r3, #2
	add	r3, r4, r3, lsl #3
	strb	r7, [r3, #5]
	strb	r6, [r2, #-4]
	str	ip, [r4, #20]
	ldr	r3, [r5, #192]
	cmp	r3, r1
	bhi	.L144
.L141:
	ldr	r0, [r5, #180]
	add	r1, r4, #20480
	mov	r10, #0
	ldr	r8, [fp, #-56]
	str	r10, [r4, #60]
	mov	r3, #1
	str	r0, [r4, #8]
	mov	r0, #8
	ldr	lr, [r1, #1176]
	ldr	r9, [fp, #-60]
	ldr	r2, [r5, #132]
	ldr	ip, [r5, #136]
	ldr	r1, [r5, #148]
	ldr	r6, [r5, #156]
	ldr	r7, [r5, #160]
	str	lr, [r4, #64]
	str	r8, [r4, #108]
	ldr	lr, [r5, #164]
	ldr	r8, [r5, #168]
	str	r9, [r4, #112]
	str	r3, [r4, #140]
	ldr	r9, [r5, #172]
	ldr	r3, [fp, #-76]
	ldr	r5, [r5, #128]
	strb	r10, [r4, #57]
	strb	r10, [r4, #58]
	str	ip, [r4, #84]
	str	r1, [r4, #88]
	str	r6, [r4, #92]
	str	r7, [r4, #96]
	str	lr, [r4, #116]
	str	r8, [r4, #120]
	str	r9, [r4, #124]
	str	r2, [r4, #80]
	str	r5, [r3]
	ldr	r3, .L175
	ldr	r3, [r3, #16]
	blx	r3
	mov	r0, r10
.L158:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L168:
	ldr	r1, .L175+24
	mov	r3, r0, asl #5
	sub	r3, r3, r0, asl #2
	ldr	lr, [r4, #40]
	add	r2, r1, r3
	ldr	r7, [r4, #44]
	ldr	r3, [r1, r3]
	ldr	r1, [r2, #4]
	mul	ip, r7, lr
	mul	r2, r1, r3
	cmp	r0, #25
	cmpne	ip, r2
	ble	.L162
	ldrsb	r2, [r4, #36]
	cmp	r2, #1
	bne	.L147
.L162:
	ldr	r3, .L175+8
	ldr	r1, [r3, r6, asl #2]
	b	.L148
.L117:
	ldr	lr, [r4, #40]
	ldr	r7, [r4, #44]
	mul	ip, r7, lr
	b	.L148
.L170:
	str	r7, [sp, #4]
	mov	r0, #0
	str	lr, [sp]
	ldr	r1, .L175+28
	bl	dprint_vfmw
	ldr	r3, .L175+32
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L158
	mov	r3, #0
	mov	r0, r6
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L172:
	ldr	r1, [r7, #176]
	mov	r2, #1
	strb	r1, [r4, #2]
	ldr	r3, [r3, r6, asl #2]
	str	r2, [r3, #1432]
	strb	r2, [r3, #1456]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L171:
	add	r3, r1, #442368
	ldr	r3, [r3, #2056]
	bics	r2, r3, #2
	beq	.L123
	cmp	r3, #1
	moveq	r0, #0
	beq	.L158
	mov	r3, #0
	strb	r3, [r4, #2]
	ldr	r3, .L175+8
	mov	r0, #31
	ldr	r1, .L175+36
	ldr	r3, [r3, r6, asl #2]
	add	r3, r3, #442368
	ldr	r2, [r3, #2056]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L158
.L127:
	ldr	r3, [r1, #3280]
	mvn	r10, #0
	cmp	r3, #32
	movge	r3, #32
	strb	r3, [r4, #5]
.L130:
	ldr	r2, .L175+8
	mov	r3, #0
	strb	r3, [r4, #2]
	mov	r0, r3
	ldr	r1, .L175+40
	ldr	ip, [r2, r6, asl #2]
	mov	r2, r10
	str	r3, [ip, #1432]
	strb	r3, [ip, #1456]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L158
.L174:
	ldr	r3, [r4, #40]
	str	r3, [fp, #-56]
	ldr	r3, [r4, #44]
	str	r3, [fp, #-60]
	b	.L134
.L147:
	mov	r2, r0
	str	r1, [sp]
	str	r7, [sp, #8]
	mov	r0, #0
	str	lr, [sp, #4]
	ldr	r1, .L175+44
	bl	dprint_vfmw
.L121:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #2]
	b	.L158
.L169:
	mov	r2, r0
	ldr	r1, .L175+48
	mov	r0, #0
	bl	dprint_vfmw
	b	.L121
.L166:
	ldr	r3, .L175+52
	movw	r2, #601
	ldr	r1, .L175+56
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L158
.L173:
	str	r3, [sp]
	mov	r2, r10
	mov	r3, r8
	mov	r0, r10
	ldr	r1, .L175+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L158
.L167:
	mov	r0, r4
	ldr	r3, .L175+64
	movw	r2, #602
	ldr	r1, .L175+56
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L158
.L176:
	.align	2
.L175:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	g_vdm_hal_fun_ptr
	.word	.LC12
	.word	.LANCHOR0+128
	.word	CapItem
	.word	.LC10
	.word	g_event_report
	.word	.LC11
	.word	.LC13
	.word	.LC9
	.word	.LC8
	.word	.LC2
	.word	.LC1
	.word	.LC14
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_ConfigFrameBuf, .-FSP_ConfigFrameBuf
	.align	2
	.global	FSP_GetOccupiedNum
	.type	FSP_GetOccupiedNum, %function
FSP_GetOccupiedNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #1088
	bgt	.L179
	ldr	r3, .L181
	ldr	r3, [r3, r2, asl #2]
	add	r3, r3, #475136
	ldr	r3, [r3, #996]
	cmp	r3, #0
	movne	r0, #1
	moveq	r0, #4
	ldmfd	sp, {fp, sp, pc}
.L179:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L182:
	.align	2
.L181:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	FSP_GetOccupiedNum, .-FSP_GetOccupiedNum
	.align	2
	.global	FSP_IsDecFsAvailable
	.type	FSP_IsDecFsAvailable, %function
FSP_IsDecFsAvailable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r1, #84]
	cmp	r3, #1
	beq	.L188
.L186:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L188:
	ldr	r2, [r1]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	bne	.L186
	cmp	r0, #31
	ldr	r1, [r1, #8]
	ble	.L189
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L189:
	bl	FSP_IsSpecialFrm.part.3
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FSP_IsDecFsAvailable, .-FSP_IsDecFsAvailable
	.align	2
	.global	FSP_IsPmvAvailable
	.type	FSP_IsPmvAvailable, %function
FSP_IsPmvAvailable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrh	r0, [r0, #4]
	sub	r0, r0, #1
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FSP_IsPmvAvailable, .-FSP_IsPmvAvailable
	.align	2
	.global	FSP_IsNewFsAvalible
	.type	FSP_IsNewFsAvalible, %function
FSP_IsNewFsAvalible:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r5, r0
	bhi	.L231
	ldr	r8, .L235
	ldr	r7, [r8, r0, asl #2]
	cmp	r7, #0
	beq	.L232
	ldrsb	r3, [r7, #3]
	cmp	r3, #0
	bne	.L195
.L207:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L195:
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L196
	ldrsb	r9, [r7, #3]
	cmp	r9, #0
	addgt	r4, r7, #21504
	movgt	r6, #0
	addgt	r4, r4, #144
	bgt	.L201
	b	.L202
.L233:
	add	r6, r6, #1
	cmp	r6, r9
	beq	.L202
.L201:
	mov	r1, r4
	mov	r0, r5
	bl	FSP_IsDecFsAvailable
	add	r4, r4, #88
	cmp	r0, #1
	bne	.L233
	cmp	r9, r6
	ble	.L202
.L203:
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L207
	ldrsb	r1, [r7, #5]
	cmp	r1, #0
	ble	.L208
	add	r3, r7, #27136
	ldrh	r3, [r3, #148]
	cmp	r3, #1
	beq	.L207
	mov	r2, #0
	b	.L209
.L210:
	add	r3, r7, r3, lsl #3
	ldrh	r3, [r3, #4]
	cmp	r3, #1
	beq	.L207
.L209:
	add	r2, r2, #1
	cmp	r2, r1
	add	r3, r2, #3408
	add	r3, r3, #2
	bne	.L210
.L211:
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #0
	beq	.L207
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #16
	beq	.L207
	mov	r0, r5
	bl	VCTRL_GetVidStd
	cmp	r0, #15
	beq	.L207
.L202:
	ldr	r3, [r8, r5, asl #2]
	cmp	r3, #0
	beq	.L234
.L199:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L196:
	ldr	r3, .L235+4
	add	r4, r7, #21504
	add	r4, r4, #144
	mov	r6, #0
	ldr	r3, [r3, r5, asl #2]
	add	r3, r3, #786432
	ldr	r9, [r3, #3732]
	b	.L206
.L204:
	add	r6, r6, #1
	add	r4, r4, #88
	cmp	r6, #32
	beq	.L202
.L206:
	mov	r1, r4
	mov	r0, r5
	bl	FSP_IsDecFsAvailable
	cmp	r0, #1
	bne	.L204
	ldr	r3, [r4, #12]
	cmp	r3, r9
	bne	.L204
	cmp	r6, #31
	ble	.L203
	b	.L202
.L231:
	ldr	r3, .L235+8
	movw	r2, #818
	ldr	r1, .L235+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L208:
	bne	.L202
	b	.L211
.L232:
	mov	r0, r7
	ldr	r3, .L235+16
	movw	r2, #819
	ldr	r1, .L235+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L234:
	ldr	r1, .L235+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L199
.L236:
	.align	2
.L235:
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	.LC2
	.word	.LC1
	.word	.LC4
	.word	.LC15
	UNWIND(.fnend)
	.size	FSP_IsNewFsAvalible, .-FSP_IsNewFsAvalible
	.align	2
	.global	FSP_NewLogicFs
	.type	FSP_NewLogicFs, %function
FSP_NewLogicFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r8, r0
	mov	r10, r1
	bhi	.L275
	ldr	r4, .L281
	ldr	r0, [r4, r0, asl #2]
	cmp	r0, #0
	beq	.L276
	ldr	r3, .L281+4
	mov	r0, #3
	mov	r7, #0
	ldr	r3, [r3, #12]
	blx	r3
	ldr	r5, [r4, r8, asl #2]
	mov	r3, r5
.L243:
	ldrsb	r2, [r3, #144]
	cmp	r2, #0
	bne	.L241
	ldrsb	r9, [r3, #145]
	cmp	r9, #0
	beq	.L277
.L241:
	add	r7, r7, #1
	add	r3, r3, #672
	cmp	r7, #32
	bne	.L243
.L244:
	ldr	r1, .L281+8
	mov	r0, #0
	bl	dprint_vfmw
.L274:
	ldr	r3, .L281+4
	mov	r0, #3
	ldr	r3, [r3, #16]
	blx	r3
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L277:
	mov	r4, #672
	mul	r4, r4, r7
	add	r3, r5, r4
	add	r4, r4, #144
	add	r1, r3, #144
	adds	r4, r5, r4
	strb	r7, [r1, #3]
	strb	r9, [r1, #2]
	beq	.L244
	cmp	r10, #0
	str	r9, [r3, #172]
	str	r9, [r3, #176]
	str	r9, [r3, #152]
	bne	.L245
	add	r2, r5, #24576
	add	ip, r5, #56
	str	ip, [r3, #172]
	mov	r0, #1
	str	ip, [r3, #176]
	ldr	r2, [r2, #2704]
	str	r2, [r3, #152]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	strb	r0, [r1, #2]
	sub	r3, r3, #1
	strb	r3, [r1, #4]
.L246:
	mov	r0, #672
	add	r3, r4, #544
	mul	r0, r0, r7
	mov	r7, r3
	mov	ip, #1
	mov	r1, #0
	mov	r2, #632
	add	r8, r4, #560
	add	r3, r5, r0
	add	r0, r0, #184
	add	r9, r3, #144
	add	r0, r5, r0
	ldr	r6, [r3, #176]
	strb	ip, [r3, #145]
	strb	ip, [r6, #2]
	str	ip, [r3, #168]
	ldr	r6, [r3, #172]
	ldr	ip, [r5, #12]
	str	ip, [r3, #164]
	str	ip, [r6, #72]
	ldr	r10, [r3, #164]
	ldr	ip, [r3, #176]
	str	r10, [ip, #72]
	ldr	ip, [r5, #12]
	add	ip, ip, #1
	str	ip, [r5, #12]
	ldr	ip, .L281+4
	ldr	r5, [r3, #172]
	ldr	r10, [r3, #176]
	ldr	ip, [ip, #48]
	blx	ip
	ldrsb	r3, [r9, #3]
	str	r3, [r4, #188]
	ldr	r3, [r5, #52]
	str	r3, [r4, #108]
	ldr	r3, [r5, #56]
	str	r3, [r4, #112]
	ldr	r3, [r10, #24]
	str	r3, [r4, #152]
	ldr	r3, [r10, #28]
	str	r3, [r4, #156]
	ldr	r3, [r10, #44]
	str	r3, [r4, #176]
	ldr	r3, [r10, #48]
	str	r3, [r4, #180]
	ldr	r0, [r5, #8]
	str	r0, [r4, #76]
	bl	MEM_Phy2Vir
	mov	r2, #0
	str	r0, [r4, #544]
	str	r2, [r7, #4]
	ldr	r3, [r5, #60]
	ldr	r0, [r4, #76]
	add	r0, r3, r0
	str	r0, [r4, #80]
	bl	MEM_Phy2Vir
	mov	r3, #0
	str	r3, [r4, #556]
	add	ip, r4, #576
	ldr	lr, [r4, #76]
	add	r4, r4, #480
	str	r0, [r4, #72]
	ldr	r1, [r10, #8]
	str	r1, [r4, #-420]
	ldr	r3, [r10, #60]
	add	r3, r1, r3
	str	r3, [r4, #-416]
	ldr	r2, [r10, #24]
	add	r2, r2, r1
	str	r2, [r4, #-412]
	ldr	r2, [r10, #28]
	add	r3, r3, r2
	str	r3, [r4, #-408]
	ldr	r3, [r5, #32]
	str	r3, [r4, #-296]
	ldr	r3, [r5, #36]
	add	r3, r3, lr
	str	r3, [r4, #-396]
	ldrd	r0, [r7]
	ldr	r10, [r5, #36]
	adds	r2, r0, r10
	adc	r3, r1, r10, asr #31
	strd	r2, [ip, #-8]
	ldr	r2, [r5, #40]
	ldr	r3, [r5, #36]
	add	r3, r3, r2
	add	lr, r3, lr
	str	lr, [r4, #-392]
	ldr	r2, [r5, #40]
	ldr	lr, [r5, #36]
	mov	r3, r2, asr #31
	adds	r6, r2, lr
	adc	r7, r3, lr, asr #31
	adds	r2, r6, r0
	adc	r3, r7, r1
	strd	r2, [ip]
	ldr	r3, [r5, #20]
	str	r3, [r4, #-228]
	ldr	r0, [r5, #20]
	bl	MEM_Phy2Vir
	mov	r3, #0
	str	r3, [r4, #84]
	str	r0, [r4, #80]
	ldr	r0, [r5, #16]
	str	r0, [r4, #-16]
	bl	MEM_Phy2Vir
	ldr	r3, .L281+4
	mov	r2, #0
	str	r2, [r4, #-4]
	ldr	r3, [r3, #16]
	str	r0, [r4, #-8]
	mov	r0, #3
	blx	r3
	ldrsb	r0, [r9, #3]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L245:
	mov	r0, r8
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L247
	ldrsb	r3, [r5, #3]
	cmp	r3, #0
	ble	.L248
	add	r10, r5, #21504
	mov	r6, r4
	add	r10, r10, #144
	mov	r4, r10
	mov	r10, r3
	b	.L250
.L278:
	cmp	r9, r10
	add	r4, r4, #88
	beq	.L273
.L250:
	mov	r1, r4
	mov	r0, r8
	bl	FSP_IsDecFsAvailable
	add	r9, r9, #1
	cmp	r0, #1
	bne	.L278
.L272:
	mov	r10, r4
	mov	r4, r6
	str	r10, [r6, #28]
.L248:
	mov	r9, #672
	mla	r9, r9, r7, r5
	add	r10, r9, #168
	ldr	r0, [r10, #4]
	cmp	r0, #0
	beq	.L279
	ldrsb	r3, [r5, #5]
	cmp	r3, #0
	ble	.L254
	mov	r0, r8
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L255
	ldrsb	r0, [r5, #5]
	add	ip, r5, #24576
	cmp	r0, #0
	ble	.L256
	movw	r3, #2708
	ldrh	r3, [ip, r3]
	cmp	r3, #1
	beq	.L257
	mov	r3, #0
	b	.L258
.L260:
	add	r1, r5, r2, lsl #3
	ldrh	r1, [r1, #4]
	cmp	r1, #1
	beq	.L280
.L258:
	add	r3, r3, #1
	cmp	r3, r0
	add	r2, r3, #3408
	add	r2, r2, #2
	bne	.L260
.L256:
	cmp	r0, #0
	ldr	lr, [r5, #8]
	ble	.L262
.L259:
	mov	r2, #0
	mov	r1, r2
.L261:
	mov	r3, r2, asl #3
	add	r2, r2, #1
	add	r3, r3, #27136
	cmp	r2, r0
	add	r3, r3, #149
	strb	r1, [r5, r3]
	bne	.L261
.L262:
	mov	r8, #672
	mov	r3, #0
	mla	r8, r8, r7, r5
	mov	r0, r3
	ldr	r1, .L281+12
	strb	r3, [r8, #148]
	ldr	r3, [ip, #2704]
	str	lr, [r8, #156]
	str	r3, [r8, #152]
	bl	dprint_vfmw
	ldr	r0, [r8, #172]
.L254:
	mov	r3, #672
	mla	r3, r3, r7, r5
	str	r0, [r3, #176]
	b	.L246
.L273:
	mov	r4, r6
	b	.L248
.L247:
	ldr	r2, .L281+16
	add	r10, r5, #21504
	add	r10, r10, #144
	add	r9, r5, #24320
	mov	r6, r4
	add	r9, r9, #144
	ldr	r2, [r2, r8, asl #2]
	mov	r4, r10
	add	r2, r2, #786432
	ldr	r3, [r2, #3732]
	mov	r10, r3
	b	.L252
.L251:
	add	r4, r4, #88
	cmp	r4, r9
	beq	.L273
.L252:
	mov	r1, r4
	mov	r0, r8
	bl	FSP_IsDecFsAvailable
	cmp	r0, #1
	bne	.L251
	ldr	r2, [r4, #12]
	cmp	r10, r2
	bne	.L251
	b	.L272
.L280:
	mov	r1, #672
	cmp	r3, r0
	mla	r1, r1, r7, r5
	strb	r3, [r1, #148]
	ldr	r3, [r5, r2, asl #3]
	str	r3, [r1, #152]
	ldr	lr, [r5, #8]
	str	lr, [r1, #156]
	bge	.L259
.L263:
	mov	r3, #672
	mla	r3, r3, r7, r5
	ldr	r0, [r3, #172]
	b	.L254
.L255:
	add	r3, r5, #24576
	mov	r1, #0
	strb	r1, [r9, #148]
	ldr	r3, [r3, #2704]
	str	r3, [r9, #152]
	ldr	r3, [r5, #8]
	str	r3, [r9, #156]
	ldr	r0, [r10, #4]
	b	.L254
.L275:
	ldr	r3, .L281+20
	movw	r2, #913
	ldr	r1, .L281+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L276:
	ldr	r3, .L281+28
	movw	r2, #914
	ldr	r1, .L281+24
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L257:
	mov	r2, #0
	strb	r2, [r9, #148]
	ldr	r3, [ip, #2704]
	str	r3, [r9, #152]
	ldr	r3, [r5, #8]
	str	r3, [r9, #156]
	b	.L263
.L279:
	ldr	r2, .L281+32
	ldr	r1, .L281+36
	bl	dprint_vfmw
	b	.L274
.L282:
	.align	2
.L281:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC16
	.word	.LC18
	.word	s_pstVfmwChan
	.word	.LC2
	.word	.LC1
	.word	.LC4
	.word	.LANCHOR1
	.word	.LC17
	UNWIND(.fnend)
	.size	FSP_NewLogicFs, .-FSP_NewLogicFs
	.align	2
	.global	FSP_GetPhyFsNum
	.type	FSP_GetPhyFsNum, %function
FSP_GetPhyFsNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r6, .L291
	mov	r7, r0
	mov	r0, #3
	mov	r4, r1
	mov	r5, #0
	ldr	r3, [r6, #12]
	blx	r3
	ldr	r3, .L291+4
	ldr	ip, [r3, r7, asl #2]
	add	r3, ip, #21504
	add	ip, ip, #24320
	add	r3, r3, #228
	add	ip, ip, #228
	b	.L285
.L284:
	add	r3, r3, #88
	cmp	r3, ip
	beq	.L290
.L285:
	ldr	r2, [r3]
	cmp	r2, #1
	bne	.L284
	ldr	r2, [r3, #-72]
	add	r3, r3, #88
	cmp	r4, #0
	cmpne	r2, r4
	addeq	r5, r5, #1
	cmp	r3, ip
	bne	.L285
.L290:
	ldr	r3, [r6, #16]
	mov	r0, #3
	blx	r3
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L292:
	.align	2
.L291:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetPhyFsNum, .-FSP_GetPhyFsNum
	.align	2
	.global	FSP_RelsePhyFs
	.type	FSP_RelsePhyFs, %function
FSP_RelsePhyFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r5, .L324
	mov	r6, r0
	mov	r0, #3
	mov	r7, r1
	mov	r4, #0
	ldr	r3, [r5, #12]
	blx	r3
	ldr	r3, .L324+4
	ldr	r1, [r3, r6, asl #2]
	add	r3, r1, #21504
	add	r3, r3, #228
	b	.L297
.L294:
	add	r4, r4, #1
	add	r3, r3, #88
	cmp	r4, #32
	beq	.L321
.L297:
	ldr	r2, [r3]
	cmp	r2, #1
	bne	.L294
	ldrsb	r2, [r3, #-83]
	cmp	r2, #0
	bne	.L294
	ldrsb	ip, [r3, #-82]
	cmp	ip, #0
	bne	.L294
	ldr	r2, [r3, #-72]
	cmp	r2, r7
	beq	.L294
	mov	r3, #88
	movw	r2, #21656
	mla	r10, r3, r4, r1
	str	ip, [fp, #-72]
	add	r8, r10, #21504
	add	r8, r8, #152
	ldr	r9, [r10, r2]
	mov	r0, r9
	bl	MEM_Phy2Vir
	cmp	r4, #31
	ldr	r8, [r8, #4]
	ldr	ip, [fp, #-72]
	mov	r7, r0
	bgt	.L321
	add	r3, r10, #21504
	ldr	r10, .L324+8
	mov	r1, r0
	mov	r2, r8
	str	ip, [r3, #228]
	mov	r0, r9
	bl	MEM_DelMemRecord
	ldr	r3, [r10, r6, asl #2]
	mov	r2, r4, asl #6
	add	r2, r2, r4, lsl #3
	str	r2, [fp, #-72]
	add	r3, r3, r2
	add	r3, r3, #471040
	ldr	r1, [r3, #928]
	cmp	r1, #255
	beq	.L299
	ldr	r4, [r3, #984]
	mov	r0, r4
	bl	MEM_Phy2Vir
	ldr	r2, [fp, #-72]
	ldr	r3, [r10, r6, asl #2]
	add	r3, r3, r2
	add	r3, r3, #471040
	ldr	r2, [r3, #940]
	mov	r1, r0
	mov	r0, r4
	bl	MEM_DelMemRecord
.L299:
	ldr	r3, [r5, #16]
	mov	r0, #3
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #8
	blx	r3
	ldr	r0, [r10, r6, asl #2]
	mov	ip, #0
	add	r2, r0, #471040
	add	r3, r2, #3696
	b	.L302
.L300:
	add	ip, ip, #1
	add	r3, r3, #12
	cmp	ip, #32
	beq	.L303
.L302:
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L300
	ldr	r1, [r3, #-8]
	cmp	r9, r1
	bne	.L300
	cmp	ip, #31
	movle	r3, ip, asl #4
	suble	r3, r3, ip, asl #2
	movle	r1, #0
	addle	r3, r2, r3
	strleb	r1, [r3, #3696]
.L303:
	add	r3, r2, #920
	mov	r4, #0
	b	.L306
.L304:
	add	r4, r4, #1
	add	r3, r3, #72
	cmp	r4, #32
	beq	.L307
.L306:
	ldr	r2, [r3]
	cmp	r2, #255
	beq	.L304
	ldr	r2, [r3, #32]
	cmp	r9, r2
	bne	.L304
	cmp	r4, #31
	bgt	.L307
	ldr	r1, .L324+12
	mov	r3, r4, asl #6
	add	r3, r3, r4, lsl #3
	mov	r2, #255
	add	r3, r0, r3
	ldr	ip, [r1]
	add	r3, r3, #471040
	cmp	ip, #0
	str	r2, [r3, #920]
	beq	.L307
	mov	lr, #0
	str	r9, [fp, #-68]
	mov	r0, r6
	str	r7, [fp, #-60]
	str	r8, [fp, #-52]
	mov	r3, #24
	str	lr, [fp, #-64]
	sub	r2, fp, #68
	str	lr, [fp, #-56]
	mov	r1, #123
	str	lr, [fp, #-48]
	blx	ip
.L307:
	ldr	r3, [r5, #16]
	mov	r0, #8
	blx	r3
	cmp	r4, #31
	movle	r0, #0
	mvngt	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L321:
	ldr	r3, [r5, #16]
	mov	r0, #3
	blx	r3
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L325:
	.align	2
.L324:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0
	.word	s_pstVfmwChan
	.word	g_event_report
	UNWIND(.fnend)
	.size	FSP_RelsePhyFs, .-FSP_RelsePhyFs
	.align	2
	.global	FSP_RemovePmv
	.type	FSP_RemovePmv, %function
FSP_RemovePmv:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	ldrhi	r3, .L335
	movwhi	r2, #1153
	bhi	.L332
	cmp	r1, #31
	bhi	.L333
	ldr	r3, .L335+4
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L334
	mov	r3, #672
	mla	r3, r3, r1, r0
	ldr	r2, [r3, #168]
	cmp	r2, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r3, [r3, #148]	@ zero_extendqisi2
	cmp	r3, #31
	bhi	.L331
	sxtb	r3, r3
	mov	r2, #0
	add	r3, r3, #3408
	add	r3, r3, #2
	add	r3, r0, r3, lsl #3
	strb	r2, [r3, #5]
.L331:
	mov	r2, #672
	mov	r3, #0
	mla	r1, r2, r1, r0
	str	r3, [r1, #168]
	ldmfd	sp, {fp, sp, pc}
.L333:
	ldr	r3, .L335+8
	movw	r2, #1154
.L332:
	ldr	r1, .L335+12
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L334:
	ldr	r3, .L335+16
	movw	r2, #1155
	ldr	r1, .L335+12
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L336:
	.align	2
.L335:
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC19
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_RemovePmv, .-FSP_RemovePmv
	.align	2
	.global	FSP_SetRef
	.type	FSP_SetRef, %function
FSP_SetRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r6, r2
	mov	r4, r1
	ldrhi	r3, .L371
	movwhi	r2, #1178
	bhi	.L363
	cmp	r1, #31
	bhi	.L364
	ldr	r3, .L371+4
	ldr	r5, [r3, r0, asl #2]
	cmp	r5, #0
	beq	.L365
	mov	r3, #672
	uxtb	r2, r6
	mla	r3, r3, r1, r5
	ldrsb	r1, [r3, #146]
	strb	r2, [r3, #144]
	cmp	r1, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r3, #172]
	cmp	r1, #0
	beq	.L343
	ldr	r3, [r3, #164]
	ldr	r0, [r1, #72]
	cmp	r0, r3
	streqb	r2, [r1, #1]
.L343:
	mov	r2, #672
	mla	r2, r2, r4, r5
	ldrb	r3, [r2, #148]	@ zero_extendqisi2
	cmp	r3, #31
	bhi	.L344
	cmp	r6, #1
	beq	.L366
	cmp	r6, #0
	bne	.L347
	ldr	r1, [r2, #168]
	cmp	r1, #2
	beq	.L367
.L354:
	mov	r3, #672
	mla	r3, r3, r4, r5
	ldr	r3, [r3, #176]
	cmp	r3, #0
	beq	.L357
	ldrsb	r2, [r3, #2]
	cmp	r2, #1
	moveq	r2, #0
	streqb	r2, [r3, #2]
.L357:
	mov	r3, #672
	mla	r4, r3, r4, r5
	str	r6, [r4, #172]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L364:
	ldr	r3, .L371+8
	movw	r2, #1179
.L363:
	ldr	r1, .L371+12
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L366:
	ldr	r1, [r2, #168]
	cmp	r1, #1
	beq	.L368
.L346:
	mov	r3, #672
	mla	r3, r3, r4, r5
	ldr	r2, [r3, #176]
	cmp	r2, #0
	beq	.L369
.L353:
	mov	r3, #672
	ldr	r0, [r2, #72]
	mla	r3, r3, r4, r5
	ldr	r1, [r3, #164]
	cmp	r6, #1
	cmpeq	r0, r1
	beq	.L370
.L350:
	cmp	r6, #0
	beq	.L357
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L344:
	sxtb	r3, r3
	mov	r2, #1232
	ldr	r1, .L371+16
	mov	r0, #0
	bl	dprint_vfmw
	cmp	r6, #0
	beq	.L354
	b	.L346
.L368:
	sxtb	r3, r3
	mov	r1, #2
	add	r3, r3, #3408
	add	r3, r3, r1
	add	r3, r5, r3, lsl #3
	strb	r6, [r3, #5]
	str	r1, [r2, #168]
.L347:
	mov	r3, #672
	mla	r3, r3, r4, r5
	ldr	r2, [r3, #176]
	cmp	r2, #0
	bne	.L353
	b	.L350
.L367:
	sxtb	r3, r3
	add	r3, r3, #3408
	add	r3, r3, #2
	add	r3, r5, r3, lsl #3
	strb	r6, [r3, #5]
	str	r6, [r2, #152]
	str	r6, [r2, #168]
	b	.L354
.L365:
	mov	r0, r5
	ldr	r3, .L371+20
	movw	r2, #1180
	ldr	r1, .L371+12
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L370:
	ldrsb	r1, [r2, #2]
	cmp	r1, #1
	moveq	r1, #2
	streqb	r1, [r2, #2]
	streqb	r1, [r3, #145]
	b	.L350
.L369:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L372:
	.align	2
.L371:
	.word	.LC2
	.word	.LANCHOR0
	.word	.LC19
	.word	.LC1
	.word	.LC20
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_SetRef, .-FSP_SetRef
	.align	2
	.global	FSP_GetRef
	.type	FSP_GetRef, %function
FSP_GetRef:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L378
	cmp	r1, #31
	bhi	.L379
	ldr	r3, .L381
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L380
	mov	r0, #672
	mla	r1, r0, r1, r3
	ldrsb	r0, [r1, #144]
	ldmfd	sp, {fp, sp, pc}
.L378:
	ldr	r3, .L381+4
	mov	r2, #1264
	ldr	r1, .L381+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L379:
	ldr	r3, .L381+12
	movw	r2, #1265
	ldr	r1, .L381+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L380:
	mov	r0, r3
	movw	r2, #1266
	ldr	r3, .L381+16
	ldr	r1, .L381+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L382:
	.align	2
.L381:
	.word	.LANCHOR0
	.word	.LC21
	.word	.LC1
	.word	.LC22
	.word	.LC23
	UNWIND(.fnend)
	.size	FSP_GetRef, .-FSP_GetRef
	.align	2
	.global	FSP_SetDisplay
	.type	FSP_SetDisplay, %function
FSP_SetDisplay:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r8, r2
	mov	r4, r0
	mov	r7, r1
	ldrhi	r3, .L416
	movwhi	r2, #1279
	bhi	.L410
	cmp	r1, #31
	bhi	.L411
	ldr	r5, .L416+4
	ldr	r0, [r5, r0, asl #2]
	cmp	r0, #0
	beq	.L412
	ldr	r6, .L416+8
	mov	r0, #3
	ldr	r3, [r6, #12]
	blx	r3
	ldr	r9, [r5, r4, asl #2]
	mov	r5, #672
	cmp	r8, #0
	mla	r5, r5, r7, r9
	moveq	r3, #0
	movne	r3, #3
	add	ip, r5, #144
	ldrsb	r0, [ip, #2]
	strb	r3, [ip, #1]
	cmp	r0, #0
	bne	.L396
	ldr	r3, [r5, #176]
	cmp	r3, #0
	beq	.L396
	ldr	r3, [r3, #72]
	ldr	r2, [r5, #164]
	cmp	r3, r2
	bne	.L413
	cmp	r8, #0
	bne	.L391
	strb	r8, [ip, #1]
	mov	r0, r4
	ldr	r3, [r5, #176]
	strb	r8, [r3, #2]
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L414
.L393:
	mov	r1, #672
	mov	r3, #0
	mla	r1, r1, r7, r9
	str	r3, [r1, #176]
.L396:
	ldr	r3, [r6, #16]
	mov	r0, #3
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L411:
	ldr	r3, .L416+12
	mov	r2, #1280
.L410:
	ldr	r1, .L416+16
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L391:
	mov	r0, r4
	bl	VCTRL_GetVidStd
	cmp	r0, #17
	beq	.L415
.L395:
	mov	r1, #672
	mov	r3, #3
	mla	r1, r1, r7, r9
	ldr	r2, [r1, #176]
	strb	r3, [r1, #145]
	strb	r3, [r2, #2]
	b	.L396
.L413:
	ldr	r1, .L416+20
	bl	dprint_vfmw
	b	.L396
.L412:
	ldr	r3, .L416+24
	movw	r2, #1281
	ldr	r1, .L416+16
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L415:
	ldr	r3, [r5, #176]
	cmp	r3, #0
	ldrne	r2, [r3, #80]
	addne	r2, r2, #1
	strne	r2, [r3, #80]
	b	.L395
.L414:
	ldr	r3, [r5, #176]
	cmp	r3, #0
	beq	.L393
	ldr	r2, [r3, #80]
	cmp	r2, #0
	beq	.L393
	sub	r2, r2, #1
	str	r2, [r3, #80]
	ldr	r3, [r5, #176]
	ldr	r2, [r3, #80]
	cmp	r2, #0
	movne	r2, #3
	strneb	r2, [r3, #2]
	b	.L393
.L417:
	.align	2
.L416:
	.word	.LC2
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	.word	.LC1
	.word	.LC24
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_SetDisplay, .-FSP_SetDisplay
	.align	2
	.global	FSP_ClearNotInVoQueue
	.type	FSP_ClearNotInVoQueue, %function
FSP_ClearNotInVoQueue:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	mov	r5, r0
	mov	r7, r1
	bhi	.L429
	cmp	r1, #0
	beq	.L430
	ldr	r3, .L433
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	addne	r6, r0, #21504
	addne	r4, r0, #184
	addne	r6, r6, #184
	bne	.L424
	b	.L431
.L423:
	add	r4, r4, #672
	cmp	r4, r6
	beq	.L432
.L424:
	mov	r2, #0
	ldr	r1, [r4, #148]
	mov	r0, r5
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r7
	bl	IsImageInVoQueue
	cmp	r0, #0
	beq	.L423
	ldr	r1, [r4, #148]
	mov	r2, #0
	mov	r0, r5
	add	r4, r4, #672
	bl	FSP_SetDisplay
	cmp	r4, r6
	bne	.L424
.L432:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L429:
	ldr	r3, .L433+4
	movw	r2, #546
	ldr	r1, .L433+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L431:
	ldr	r3, .L433+12
	mov	r2, #548
	ldr	r1, .L433+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L430:
	mov	r0, r1
	ldr	r3, .L433+16
	movw	r2, #547
	ldr	r1, .L433+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L434:
	.align	2
.L433:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	.word	.LC25
	UNWIND(.fnend)
	.size	FSP_ClearNotInVoQueue, .-FSP_ClearNotInVoQueue
	.align	2
	.global	FSP_GetDisplay
	.type	FSP_GetDisplay, %function
FSP_GetDisplay:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L439
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L438
	mov	r0, #672
	mla	r1, r0, r1, r3
	ldrsb	r0, [r1, #145]
	ldmfd	sp, {fp, sp, pc}
.L438:
	mov	r0, r3
	movw	r2, #1354
	ldr	r3, .L439+4
	ldr	r1, .L439+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L440:
	.align	2
.L439:
	.word	.LANCHOR0
	.word	.LC4
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_GetDisplay, .-FSP_GetDisplay
	.align	2
	.global	FSP_SetStoreType
	.type	FSP_SetStoreType, %function
FSP_SetStoreType:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L449
	ldr	ip, .L452
	ldr	ip, [ip, r0, asl #2]
	cmp	ip, #0
	beq	.L450
	cmp	r1, #0
	bne	.L445
	ldrsb	r0, [ip, #3]
	cmp	r0, r2
	ble	.L448
	mov	lr, #88
	mov	r0, r1
	mla	r2, lr, r2, ip
	add	r2, r2, #21504
	str	r3, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L445:
	cmp	r1, #1
	beq	.L451
.L448:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L451:
	ldrsb	r1, [ip, #4]
	cmp	r2, r1
	bge	.L448
	mov	r1, #88
	mov	r0, #0
	mla	r2, r1, r2, ip
	add	r2, r2, #24320
	str	r3, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L449:
	ldr	r3, .L452+4
	movw	r2, #1367
	ldr	r1, .L452+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L450:
	mov	r0, ip
	ldr	r3, .L452+12
	movw	r2, #1368
	ldr	r1, .L452+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L453:
	.align	2
.L452:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_SetStoreType, .-FSP_SetStoreType
	.align	2
	.global	FSP_GetStoreType
	.type	FSP_GetStoreType, %function
FSP_GetStoreType:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L462
	ldr	r3, .L465
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L463
	cmp	r1, #0
	bne	.L458
	ldrsb	r3, [r0, #3]
	cmp	r3, r2
	ble	.L461
	mov	r3, #88
	mla	r2, r3, r2, r0
	add	r2, r2, #21504
	ldr	r0, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L458:
	cmp	r1, #1
	beq	.L464
.L461:
	mov	r0, #2
	ldmfd	sp, {fp, sp, pc}
.L462:
	ldr	r3, .L465+4
	movw	r2, #1397
	ldr	r1, .L465+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L463:
	ldr	r3, .L465+12
	movw	r2, #1398
	ldr	r1, .L465+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L464:
	ldrsb	r3, [r0, #4]
	cmp	r2, r3
	bge	.L461
	mov	r3, #88
	mla	r2, r3, r2, r0
	add	r2, r2, #24320
	ldr	r0, [r2, #220]
	ldmfd	sp, {fp, sp, pc}
.L466:
	.align	2
.L465:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetStoreType, .-FSP_GetStoreType
	.align	2
	.global	FSP_ClearLogicFs
	.type	FSP_ClearLogicFs, %function
FSP_ClearLogicFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	cmpls	r1, #31
	mov	r4, r0
	mov	r5, r1
	ldmhifd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r6, .L477
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r2, #0
	bl	FSP_SetRef
	ldr	r2, [r6, r4, asl #2]
	mov	r3, #672
	mla	r3, r3, r5, r2
	ldrsb	r3, [r3, #145]
	cmp	r3, #3
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, r5
	mov	r0, r4
	mov	r2, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	FSP_SetDisplay
.L478:
	.align	2
.L477:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_ClearLogicFs, .-FSP_ClearLogicFs
	.align	2
	.global	FSP_GetLogicFs
	.type	FSP_GetLogicFs, %function
FSP_GetLogicFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L481
	ldr	r3, .L483
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #672
	mlane	r1, r3, r1, r0
	addne	r0, r1, #144
	ldmfd	sp, {fp, sp, pc}
.L481:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L484:
	.align	2
.L483:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetLogicFs, .-FSP_GetLogicFs
	.align	2
	.global	FSP_GetFsImagePtr
	.type	FSP_GetFsImagePtr, %function
FSP_GetFsImagePtr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L487
	ldr	r3, .L489
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #672
	mlane	r1, r3, r1, r0
	addne	r0, r1, #184
	ldmfd	sp, {fp, sp, pc}
.L487:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L490:
	.align	2
.L489:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetFsImagePtr, .-FSP_GetFsImagePtr
	.align	2
	.global	FSP_GetDecPhyFs
	.type	FSP_GetDecPhyFs, %function
FSP_GetDecPhyFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L493
	ldr	r3, .L495
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #672
	mlane	r0, r3, r1, r0
	ldrne	r0, [r0, #172]
	ldmfd	sp, {fp, sp, pc}
.L493:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L496:
	.align	2
.L495:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetDecPhyFs, .-FSP_GetDecPhyFs
	.align	2
	.global	FSP_GetDispPhyFs
	.type	FSP_GetDispPhyFs, %function
FSP_GetDispPhyFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L499
	ldr	r3, .L501
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #672
	mlane	r0, r3, r1, r0
	ldrne	r0, [r0, #176]
	ldmfd	sp, {fp, sp, pc}
.L499:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L502:
	.align	2
.L501:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetDispPhyFs, .-FSP_GetDispPhyFs
	.align	2
	.global	FSP_GetPmvAddr
	.type	FSP_GetPmvAddr, %function
FSP_GetPmvAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	cmpls	r1, #31
	movls	r3, #1
	movhi	r3, #0
	bhi	.L505
	ldr	r3, .L507
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, #672
	mlane	r0, r3, r1, r0
	ldrne	r0, [r0, #152]
	ldmfd	sp, {fp, sp, pc}
.L505:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L508:
	.align	2
.L507:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetPmvAddr, .-FSP_GetPmvAddr
	.align	2
	.global	FSP_GetDecFsAddrTab
	.type	FSP_GetDecFsAddrTab, %function
FSP_GetDecFsAddrTab:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L520
	cmp	r2, #0
	moveq	r0, r2
	ldreq	r3, .L522
	movweq	r2, #1516
	beq	.L519
	cmp	r1, #0
	moveq	r0, r1
	ldreq	r3, .L522+4
	movweq	r2, #1517
	beq	.L519
	ldr	lr, .L522+8
	ldr	ip, [lr, r0, asl #2]
	cmp	ip, #0
	beq	.L521
	ldrsb	ip, [ip, #3]
	cmp	ip, #0
	str	ip, [r1]
	ldr	ip, [lr, r0, asl #2]
	add	ip, ip, #21504
	add	ip, ip, #144
	ldmlefd	sp, {r4, fp, sp, pc}
	sub	r2, r2, #4
	sub	r3, r3, #4
	mov	lr, #0
.L516:
	ldr	r0, [ip, #8]
	add	lr, lr, #1
	add	ip, ip, #88
	str	r0, [r2, #4]!
	ldr	r4, [ip, #-68]
	str	r4, [r3, #4]!
	ldr	r4, [r1]
	cmp	r4, lr
	bgt	.L516
	ldmfd	sp, {r4, fp, sp, pc}
.L520:
	ldr	r3, .L522+12
	movw	r2, #1515
	ldr	r1, .L522+16
	mov	r0, #0
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L521:
	ldr	r3, .L522+20
	mov	r0, ip
	movw	r2, #1518
.L519:
	ldr	r1, .L522+16
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L523:
	.align	2
.L522:
	.word	.LC26
	.word	.LC27
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetDecFsAddrTab, .-FSP_GetDecFsAddrTab
	.align	2
	.global	FSP_GetPmvAddrTab
	.type	FSP_GetPmvAddrTab, %function
FSP_GetPmvAddrTab:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L535
	cmp	r2, #0
	moveq	r0, r2
	ldreq	r3, .L537
	movweq	r2, #1540
	beq	.L534
	cmp	r1, #0
	moveq	r0, r1
	ldreq	r3, .L537+4
	movweq	r2, #1541
	beq	.L534
	ldr	r3, .L537+8
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L536
	ldrsb	r3, [r0, #5]
	str	r3, [r1]
	ldrsb	r3, [r0, #5]
	cmp	r3, #0
	ldmlefd	sp, {fp, sp, pc}
	sub	r2, r2, #4
	mov	r1, #0
.L531:
	mov	r3, r1, asl #3
	add	r1, r1, #1
	add	r3, r3, #27136
	add	r3, r3, #144
	ldr	r3, [r0, r3]
	str	r3, [r2, #4]!
	ldrsb	r3, [r0, #5]
	cmp	r3, r1
	bgt	.L531
	ldmfd	sp, {fp, sp, pc}
.L535:
	ldr	r3, .L537+12
	movw	r2, #1539
	ldr	r1, .L537+16
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L536:
	ldr	r3, .L537+20
	movw	r2, #1542
.L534:
	ldr	r1, .L537+16
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L538:
	.align	2
.L537:
	.word	.LC28
	.word	.LC29
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetPmvAddrTab, .-FSP_GetPmvAddrTab
	.align	2
	.global	FSP_GetInstInfo
	.type	FSP_GetInstInfo, %function
FSP_GetInstInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L542
	mov	ip, r1
	ldr	r3, [r3, r0, asl #2]
	cmp	r3, #0
	beq	.L541
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	add	r4, r3, #20480
	ldr	r5, .L542+4
	add	r1, r3, #21504
	add	r1, r1, #144
	add	r0, ip, #8
	strb	r2, [ip, #2]
	mov	r2, #2816
	ldr	lr, [r4, #1264]
	ldr	r4, [r4, #1176]
	rsb	lr, r4, lr
	str	lr, [ip, #4]
	ldrb	lr, [r3, #4]	@ zero_extendqisi2
	strb	lr, [ip, #3]
	ldrb	lr, [r3]	@ zero_extendqisi2
	strb	lr, [ip]
	ldrb	r3, [r3, #5]	@ zero_extendqisi2
	strb	r3, [ip, #1]
	ldr	r3, [r5, #52]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L541:
	mov	r0, r3
	movw	r2, #1559
	ldr	r3, .L542+8
	ldr	r1, .L542+12
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L543:
	.align	2
.L542:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	.word	.LC1
	UNWIND(.fnend)
	.size	FSP_GetInstInfo, .-FSP_GetInstInfo
	.align	2
	.global	FSP_GetLogicIdByPhyAddr
	.type	FSP_GetLogicIdByPhyAddr, %function
FSP_GetLogicIdByPhyAddr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L555
	ldr	r3, .L557
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	movne	r3, r0
	movne	r0, #0
	beq	.L556
.L549:
	ldr	r2, [r3, #172]
	add	r3, r3, #672
	cmp	r2, #0
	beq	.L548
	ldr	r2, [r2, #8]
	cmp	r2, r1
	ldmeqfd	sp, {fp, sp, pc}
.L548:
	add	r0, r0, #1
	cmp	r0, #32
	bne	.L549
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L555:
	ldr	r3, .L557+4
	movw	r2, #1580
	ldr	r1, .L557+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L556:
	ldr	r3, .L557+12
	movw	r2, #1581
	ldr	r1, .L557+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L558:
	.align	2
.L557:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetLogicIdByPhyAddr, .-FSP_GetLogicIdByPhyAddr
	.align	2
	.global	FSP_GetNullLogicFs
	.type	FSP_GetNullLogicFs, %function
FSP_GetNullLogicFs:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L567
	ldr	ip, [r3, r0, asl #2]
	add	r3, ip, #20736
	ldrsb	r3, [r3, #241]
	cmp	r3, #0
	beq	.L564
	add	r2, ip, #20224
	mov	r3, #30
	add	r2, r2, #81
	b	.L563
.L561:
	subs	r3, r3, #1
	bcc	.L566
.L563:
	ldrsb	r1, [r2]
	sub	r2, r2, #672
	cmp	r1, #0
	bne	.L561
.L562:
	mov	r2, #672
	mov	r0, r3
	mla	r3, r2, r3, ip
	mov	r2, #0
	str	r2, [r3, #172]
	str	r2, [r3, #176]
	ldmfd	sp, {fp, sp, pc}
.L566:
	mov	r3, #0
	b	.L562
.L564:
	mov	r3, #31
	b	.L562
.L568:
	.align	2
.L567:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	FSP_GetNullLogicFs, .-FSP_GetNullLogicFs
	.align	2
	.global	FSP_GetFspType
	.type	FSP_GetFspType, %function
FSP_GetFspType:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L573
	ldr	r3, .L575
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L574
	ldr	r0, [r0, #28]
	subs	r0, r0, #1
	mvnne	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L573:
	ldr	r3, .L575+4
	movw	r2, #1626
	ldr	r1, .L575+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L574:
	ldr	r3, .L575+12
	movw	r2, #1627
	ldr	r1, .L575+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L576:
	.align	2
.L575:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetFspType, .-FSP_GetFspType
	.align	2
	.global	FSP_GetTotalValidFsNum
	.type	FSP_GetTotalValidFsNum, %function
FSP_GetTotalValidFsNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L581
	ldr	r3, .L583
	ldr	r0, [r3, r0, asl #2]
	cmp	r0, #0
	beq	.L582
	ldrsb	r0, [r0, #2]
	ldmfd	sp, {fp, sp, pc}
.L581:
	ldr	r3, .L583+4
	movw	r2, #1641
	ldr	r1, .L583+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L582:
	ldr	r3, .L583+12
	movw	r2, #1642
	ldr	r1, .L583+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L584:
	.align	2
.L583:
	.word	.LANCHOR0
	.word	.LC2
	.word	.LC1
	.word	.LC4
	UNWIND(.fnend)
	.size	FSP_GetTotalValidFsNum, .-FSP_GetTotalValidFsNum
	.align	2
	.global	FSP_IsSpecialFrm
	.type	FSP_IsSpecialFrm, %function
FSP_IsSpecialFrm:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bgt	.L586
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_IsSpecialFrm.part.3
.L586:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FSP_IsSpecialFrm, .-FSP_IsSpecialFrm
	.align	2
	.global	FSP_SetSingleFrameBuf
	.type	FSP_SetSingleFrameBuf, %function
FSP_SetSingleFrameBuf:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, .L636
	ldr	r6, [r3, r0, asl #2]
	add	r2, r6, #471040
	add	r3, r6, #475136
	ldr	r5, [r2, #900]
	ldr	lr, [r3, #360]
	cmp	r5, #32
	movge	r5, #32
	str	r5, [r2, #3272]
	ldr	r3, [r1]
	cmp	r3, #255
	beq	.L606
	ldrb	r4, [r2, #3696]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L589
	movw	r3, #15996
	mov	r4, #1
	movt	r3, 7
	add	r3, r6, r3
	b	.L590
.L634:
	add	r4, r4, #1
	cmp	r4, #32
	beq	.L633
.L590:
	ldrb	ip, [r3]	@ zero_extendqisi2
	add	r3, r3, #12
	cmp	ip, #0
	bne	.L634
.L589:
	ldr	r3, [r1, #32]
	mov	ip, r4, asl #4
	sub	ip, ip, r4, asl #2
	mov	r7, #1
	add	r3, r3, #1020
	add	ip, r2, ip
	add	r3, r3, #3
	add	r8, r2, r4, lsl #2
	bic	r3, r3, #1020
	bic	r3, r3, #3
	str	r3, [ip, #3688]
	ldr	r9, [r1, #12]
	add	r3, r3, lr
	strb	r7, [ip, #3696]
	str	r9, [ip, #3692]
	ldr	lr, [r2, #3284]
	add	lr, lr, r7
	str	lr, [r2, #3284]
	str	r3, [r8, #3304]
	ldr	r3, [r1, #4]
	cmp	r3, #255
	beq	.L588
	ldr	r3, [r1, #48]
	strb	r7, [ip, #4080]
	str	r3, [ip, #4072]
	ldr	r3, [r2, #3292]
	add	r3, r3, #1
	str	r3, [r2, #3292]
.L588:
	ldr	r3, [r1, #8]
	cmp	r3, #255
	beq	.L604
	ldrb	r3, [r2, #3436]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L610
	mov	ip, #1
.L593:
	mov	lr, ip, asl #3
	movw	r3, #15724
	movt	r3, 7
	add	r3, lr, r3
	add	ip, ip, #1
	ldrb	r3, [r6, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L592
	cmp	ip, #32
	bne	.L593
.L604:
	ldr	ip, .L636+4
	mov	r3, #0
	ldr	ip, [ip, r0, asl #2]
	add	r0, ip, #20480
	str	r0, [fp, #-48]
	strb	r5, [ip, #3]
	strb	r3, [ip, #4]
	mov	lr, r0
	ldrb	r9, [r2, #3280]	@ zero_extendqisi2
	strb	r9, [ip, #5]
	ldr	r10, [r0, #1252]
	cmp	r10, #0
	beq	.L608
	add	r0, ip, #21760
	mov	r3, #1
	add	r0, r0, #60
	b	.L596
.L595:
	add	r3, r3, #1
	cmp	r3, #32
	beq	.L635
.L596:
	ldr	r5, [r0]
	add	r0, r0, #88
	cmp	r5, #0
	bne	.L595
	mov	r10, r3
	str	lr, [fp, #-48]
.L594:
	mov	r0, #88
	mov	r6, r4, asl #4
	mla	r3, r0, r3, ip
	sub	r6, r6, r4, asl #2
	ldr	r5, [ip, #16]
	add	r6, r2, r6
	movw	r8, #21656
	add	r4, r2, r4, lsl #2
	add	r0, r3, #21504
	add	r5, r5, #1
	str	r5, [ip, #16]
	sxtb	r9, r9
	str	r10, [r0, #148]
	movw	r5, #21688
	ldr	r10, [r6, #3688]
	movw	r7, #21696
	str	r9, [fp, #-52]
	movw	r9, #21672
	str	r10, [r3, r8]
	ldr	r6, [r6, #3692]
	str	r6, [r0, #156]
	movw	r6, #21680
	ldr	r4, [r4, #3304]
	str	r4, [r0, #164]
	mov	r4, r0
	ldr	lr, [r2, #3228]
	str	lr, [r3, r9]
	ldr	lr, [r2, #3232]
	str	lr, [r0, #172]
	movw	lr, #21704
	ldr	r10, [r2, #3244]
	str	r10, [r3, r6]
	ldr	r10, [r2, #3252]
	str	r10, [r0, #180]
	mov	r10, #1
	ldr	r8, [r2, #3256]
	str	r8, [r3, r5]
	ldr	r8, [r2, #3236]
	str	r8, [r0, #188]
	ldr	r8, [r2, #3240]
	str	r8, [r3, r7]
	mov	r7, #0
	ldr	r8, [ip, #40]
	str	r8, [r0, #196]
	ldr	r9, [ip, #44]
	str	r9, [r3, lr]
	ldr	lr, [r2, #3260]
	str	lr, [r0, #204]
	movw	lr, #21712
	ldr	r6, [r2, #3264]
	str	r6, [r3, lr]
	ldr	r3, [r2, #3268]
	str	r3, [r0, #212]
	strb	r7, [r0, #145]
	strb	r7, [r0, #146]
	str	r10, [r4, #228]
	ldr	r0, [fp, #-52]
	ldr	r3, [ip, #20]
	cmp	r3, r0
	bcs	.L598
	ldr	r0, [r1, #8]
	cmp	r0, #255
	beq	.L598
	add	r4, r2, r3, lsl #3
	add	r0, ip, r3, lsl #3
	add	r0, r0, #24576
	add	r3, r3, #1
	ldr	r4, [r4, #3432]
	strb	r7, [r0, #2709]
	strb	r10, [r0, #2708]
	str	r4, [r0, #2704]
	str	r3, [ip, #20]
.L598:
	ldr	r3, [ip, #24]
	ldr	r0, [r2, #3272]
	cmp	r3, r0
	bcs	.L599
	ldr	r1, [r1, #4]
	cmp	r1, #255
	beq	.L599
	ldr	r1, [r2, #3292]
	mov	r4, #88
	mla	r4, r4, r3, ip
	sub	r0, r1, #1
	movw	r5, #21664
	add	r3, r3, #1
	mov	r1, r0, asl #4
	sub	r1, r1, r0, asl #2
	add	r1, r2, r1
	ldr	r1, [r1, #4072]
	str	r1, [r4, r5]
	str	r3, [ip, #24]
.L599:
	ldr	r3, [ip, #140]
	ldr	r1, [r2, #3276]
	cmp	r3, #0
	str	r1, [ip, #8]
	movne	r0, #0
	bne	.L628
	ldr	r1, [fp, #-48]
	mov	r0, r3
	str	r3, [ip, #60]
	ldr	lr, [r1, #1176]
	mov	r1, #1
	str	lr, [ip, #64]
	ldr	lr, [r2, #3228]
	str	lr, [ip, #80]
	ldr	lr, [r2, #3232]
	str	r8, [ip, #108]
	str	r9, [ip, #112]
	str	lr, [ip, #84]
	ldr	lr, [r2, #3260]
	str	lr, [ip, #116]
	ldr	lr, [r2, #3264]
	str	lr, [ip, #120]
	ldr	r2, [r2, #3268]
	strb	r3, [ip, #57]
	strb	r3, [ip, #58]
	str	r2, [ip, #124]
	str	r1, [ip, #140]
.L628:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L635:
	ldr	r2, .L636+8
	mov	r0, #1
	ldr	r1, .L636+12
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L606:
	mov	r4, #0
	b	.L588
.L633:
	ldr	r2, .L636+8
	mov	r0, #1
	ldr	r1, .L636+16
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L608:
	mov	r3, r10
	b	.L594
.L610:
	mov	lr, r3
.L592:
	ldr	ip, [r1, #64]
	add	lr, r6, lr
	add	lr, lr, #471040
	mov	r3, #1
	str	ip, [lr, #3432]
	strb	r3, [lr, #3436]
	ldr	r3, [r2, #3288]
	add	r3, r3, #1
	str	r3, [r2, #3288]
	b	.L604
.L637:
	.align	2
.L636:
	.word	s_pstVfmwChan
	.word	.LANCHOR0
	.word	.LANCHOR1+16
	.word	.LC31
	.word	.LC30
	UNWIND(.fnend)
	.size	FSP_SetSingleFrameBuf, .-FSP_SetSingleFrameBuf
	.align	2
	.global	FSP_GetInst
	.type	FSP_GetInst, %function
FSP_GetInst:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r0, #31
	bhi	.L641
	ldr	r3, .L642
	ldr	r0, [r3, r0, asl #2]
	ldmfd	sp, {fp, sp, pc}
.L641:
	mov	r3, r0
	ldr	r2, .L642+4
	ldr	r1, .L642+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L643:
	.align	2
.L642:
	.word	.LANCHOR0
	.word	.LANCHOR1+40
	.word	.LC32
	UNWIND(.fnend)
	.size	FSP_GetInst, .-FSP_GetInst
	.global	s_pFspInst
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.14724, %object
	.size	__func__.14724, 15
__func__.14724:
	.ascii	"FSP_NewLogicFs\000"
	.space	1
	.type	__func__.14916, %object
	.size	__func__.14916, 22
__func__.14916:
	.ascii	"FSP_SetSingleFrameBuf\000"
	.space	2
	.type	__func__.14926, %object
	.size	__func__.14926, 12
__func__.14926:
	.ascii	"FSP_GetInst\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"pFspInst = NULL\000" )
.LC1:
	ASCII(.ascii	"fsp.c,L%d: %s\012\000" )
	.space	1
.LC2:
	ASCII(.ascii	"InstID out of range\000" )
.LC3:
	ASCII(.ascii	"fsp instance not in used\000" )
	.space	3
.LC4:
	ASCII(.ascii	"fsp is not inited\000" )
	.space	2
.LC5:
	ASCII(.ascii	"fsp is already inited\000" )
	.space	2
.LC6:
	ASCII(.ascii	"pstFspInstCfg = NULL\000" )
	.space	3
.LC7:
	ASCII(.ascii	"This inst is not active\000" )
.LC8:
	ASCII(.ascii	"eChanCapLevel = %d is not expected!\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"decode channel CapLevel is %d(w=%d,h=%d), this stre" )
	ASCII(.ascii	"am (w=%d,h=%d) can NOT be decoded!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"user set decode channel max resolution is (w=%d,h=%" )
	ASCII(.ascii	"d), this stream (w=%d,h=%d) can NOT be decoded!\012" )
	ASCII(.ascii	"\000" )
.LC11:
	ASCII(.ascii	"DFS, Wrong Partition State. State: 0x%x\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"DFS, Mem Element Fill Successed! Ready to Decode!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC13:
	ASCII(.ascii	"Fsp arrange failed, return %d\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"arrange ret %d, min = %d, actual = %d\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"FSP_IsFsLeak: fsp is not inited \012\000" )
	.space	2
.LC16:
	ASCII(.ascii	"no logic frame store!!!\012\000" )
	.space	3
.LC17:
	ASCII(.ascii	"%s no decode phy fs\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"no pmv memory\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"LogicFrameID out of range\000" )
	.space	2
.LC20:
	ASCII(.ascii	"fsp.c, line %d: pstLogicFs->PmvIdc out of range(=%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"FSP_GetRef: InstID out of range\000" )
.LC22:
	ASCII(.ascii	"FSP_GetRef: LogicFrameID out of range\000" )
	.space	2
.LC23:
	ASCII(.ascii	"FSP_GetRef: Fsp is not inited\000" )
	.space	2
.LC24:
	ASCII(.ascii	"FSP_SetDisplay: LogicTick=%d, DispTick=%d!\012\000" )
.LC25:
	ASCII(.ascii	"pstVoQue is NULL\000" )
	.space	3
.LC26:
	ASCII(.ascii	"DecFsAddrTab is NULL\012\000" )
	.space	2
.LC27:
	ASCII(.ascii	"DecFsNum is NULL\012\000" )
	.space	2
.LC28:
	ASCII(.ascii	"PmvAddrTab is NULL\012\000" )
.LC29:
	ASCII(.ascii	"PmvNum is NULL\012\000" )
.LC30:
	ASCII(.ascii	"%s no free frame record position.\012\000" )
	.space	1
.LC31:
	ASCII(.ascii	"%s no free dec fs record position.\012\000" )
.LC32:
	ASCII(.ascii	"%s InstID %d out of range\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	s_pFspInst, %object
	.size	s_pFspInst, 128
s_pFspInst:
	.space	128
	.type	MemArrange.14674, %object
	.size	MemArrange.14674, 1232
MemArrange.14674:
	.space	1232
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
