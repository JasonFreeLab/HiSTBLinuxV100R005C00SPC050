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
	.file	"real9.c"
	.text
	.align	2
	.global	Real9_CB_GetBits
	.type	Real9_CB_GetBits, %function
Real9_CB_GetBits:
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
	mov	r5, r0
	mov	r6, r1
	bl	BsShow
	mov	r1, r6
	mov	r4, r0
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_GetBits, .-Real9_CB_GetBits
	.align	2
	.global	Real9_CB_Get1Bit
	.type	Real9_CB_Get1Bit, %function
Real9_CB_Get1Bit:
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
	mov	r1, #1
	mov	r5, r0
	bl	BsShow
	mov	r1, #1
	mov	r4, r0
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_Get1Bit, .-Real9_CB_Get1Bit
	.align	2
	.global	Real9_CB_GetVLCBits
	.type	Real9_CB_GetVLCBits, %function
Real9_CB_GetVLCBits:
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
	ldr	r7, .L8
	mov	r4, #0
	mov	r6, r0
	mov	r8, r1
	mov	r5, r4
.L4:
	mov	r1, #8
	mov	r0, r6
	bl	BsShow
	ldrb	r3, [r7, r0]	@ zero_extendqisi2
	mov	r0, r6
	and	r2, r3, #15
	mov	r1, r3, lsr #4
	mov	r3, r3, lsr #5
	add	r4, r4, r1
	orr	r5, r2, r5, asl r3
	bl	BsSkip
	tst	r4, #1
	beq	.L4
	str	r5, [r8]
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L9:
	.align	2
.L8:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_GetVLCBits, .-Real9_CB_GetVLCBits
	.align	2
	.global	Real9_GetImageBuffer
	.type	Real9_GetImageBuffer, %function
Real9_GetImageBuffer:
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
	add	r4, r0, #53248
	mov	r6, r0
	mov	r1, #1
	add	r7, r0, #8192
	ldr	r0, [r4, #1440]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #1040]
	blt	.L16
	mov	r1, r0
	ldr	r0, [r4, #1440]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L17
	ldr	r2, [r4, #1040]
	mov	r0, #18
	ldr	r1, .L18
	bl	dprint_vfmw
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L15
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L15
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L18+4
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L15:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L16:
	ldr	r1, .L18+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #1036]
	ldr	r0, [r4, #1440]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1032]
	mov	r5, #0
	ldr	r0, [r4, #1440]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #1032]
	str	r5, [r4, #1036]
	ldr	r0, [r4, #1440]
	bl	FSP_GetNullLogicFs
	add	r1, r6, #54272
	add	r1, r1, #64
	str	r0, [r4, #1036]
	str	r0, [r4, #1032]
	strb	r5, [r7, #3189]
	ldr	r0, [r4, #1440]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L17:
	movw	r2, #510
	ldr	r1, .L18+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L19:
	.align	2
.L18:
	.word	.LC5
	.word	.LC6
	.word	.LC3
	.word	.LC4
	UNWIND(.fnend)
	.size	Real9_GetImageBuffer, .-Real9_GetImageBuffer
	.align	2
	.global	Real9_ArrangeVHBMem
	.type	Real9_ArrangeVHBMem, %function
Real9_ArrangeVHBMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
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
	mov	r4, r2
	ldr	r2, [r2, #32]
	mov	r5, r1
	ldr	r3, [r4, #28]
	cmp	r2, #1
	bls	.L22
	sub	r0, r3, #2
	movw	r1, #510
	cmp	r2, #512
	cmpls	r0, r1
	bhi	.L22
	ldr	r1, [r5]
	ldr	r3, [r1, #724]
	cmp	r3, #0
	ldr	r3, [r1, #28]
	bne	.L25
	cmp	r3, #25
	beq	.L48
.L26:
	ldr	r9, [r4, #24]
	mov	r7, #5
	ldr	r10, [r4, #20]
	mov	r6, #2
	mov	r8, #4
.L32:
	ldr	r3, .L50
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, [r5]
	ldr	r2, [r4, #24]
	ldr	r3, [r4, #20]
	ldr	r1, [r1, #28]
	str	r9, [fp, #-60]
	cmp	r1, #24
	str	r10, [fp, #-56]
	str	r2, [fp, #-52]
	str	r3, [fp, #-48]
	beq	.L38
	uxtb	r3, r6
	strb	r8, [fp, #-63]
	strb	r7, [fp, #-62]
.L42:
	add	r4, r5, #53248
	sub	r1, fp, #64
	strb	r3, [fp, #-61]
	ldr	r0, [r4, #1440]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	movne	r0, #0
	bne	.L47
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r4, #1440]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L49
	cmp	r0, #0
	addeq	r5, r5, #8192
	moveq	r3, #1
	moveq	r0, r3
	streqb	r3, [r5, #3192]
	beq	.L47
.L40:
	ldr	r1, .L50+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L47
.L22:
	ldr	r1, .L50+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
.L47:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L25:
	cmp	r3, #25
	bne	.L26
	ldr	r2, [r4, #24]
	ldr	r0, [r1, #684]
	ldr	r3, [r4, #20]
	cmp	r2, r0
	ldr	ip, [r1, #688]
	bhi	.L35
	cmp	r3, ip
	bhi	.L35
	ldr	r0, [r1, #712]
	mov	r9, r2
	ldr	r6, [r1, #708]
	mov	r10, r3
	cmp	r0, #0
	add	r8, r6, #2
	beq	.L45
	add	r3, r6, #1
	cmp	r3, #17
	movlt	r6, r3
	movge	r6, #17
.L37:
	ldrb	r7, [r1, #732]	@ zero_extendqisi2
	b	.L32
.L38:
	mov	r3, #1
	strb	r7, [fp, #-62]
	strb	r3, [fp, #-63]
	b	.L42
.L35:
	stmia	sp, {r0, ip}
	mov	r0, #0
	ldr	r1, .L50+12
	bl	dprint_vfmw
	mov	r0, #0
	b	.L47
.L48:
	ldr	r2, [r4, #24]
	ldr	r9, [r1, #684]
	ldr	r3, [r4, #20]
	cmp	r2, r9
	ldr	r10, [r1, #688]
	bhi	.L28
	cmp	r3, r10
	bhi	.L28
	add	r3, r5, #8192
	ldrb	r0, [r3, #3192]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L47
	ldr	r2, [r1, #712]
	ldr	r3, [r1, #708]
	cmp	r2, #0
	add	r8, r3, #2
	beq	.L45
	add	r3, r3, #1
	cmp	r3, #17
	movlt	r6, r3
	movge	r6, #17
	b	.L37
.L45:
	mov	r6, #1
	b	.L37
.L28:
	stmia	sp, {r9, r10}
	mov	r0, #0
	ldr	r1, .L50+12
	bl	dprint_vfmw
	mov	r0, #0
	b	.L47
.L49:
	add	r0, r5, #54272
	add	r0, r0, #64
	bl	ResetVoQueue
	b	.L40
.L51:
	.align	2
.L50:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	.word	.LC7
	.word	.LC8
	UNWIND(.fnend)
	.size	Real9_ArrangeVHBMem, .-Real9_ArrangeVHBMem
	.align	2
	.global	Real9_CB_GetCPFMT
	.type	Real9_CB_GetCPFMT, %function
Real9_CB_GetCPFMT:
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
	mov	r6, r1
	mov	r1, #4
	mov	r5, r0
	bl	BsShow
	mov	r1, #4
	mov	r4, r0
	mov	r0, r5
	bl	BsSkip
	strb	r4, [r6, #8]
	mov	r1, #9
	mov	r0, r5
	bl	BsShow
	mov	r1, #9
	mov	r4, r0
	add	r4, r4, #1
	mov	r0, r5
	bl	BsSkip
	mov	r4, r4, asl #2
	mov	r0, r5
	str	r4, [r6, #24]
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	mov	r4, r0
	beq	.L55
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L55:
	mov	r1, #9
	mov	r0, r5
	bl	BsShow
	mov	r1, #9
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	mov	r7, r7, asl #2
	mov	r0, r4
	str	r7, [r6, #20]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_GetCPFMT, .-Real9_CB_GetCPFMT
	.align	2
	.global	Real9_CB_SetDimensions
	.type	Real9_CB_SetDimensions, %function
Real9_CB_SetDimensions:
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
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #20]
	cmp	r3, #128
	beq	.L73
	cmp	r3, #176
	beq	.L74
	cmp	r3, #352
	beq	.L75
	cmp	r3, #704
	beq	.L76
	cmp	r3, #1408
	beq	.L77
.L58:
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	mov	r2, r2, lsr #4
	str	r3, [r0, #84]
	mul	r3, r3, r2
	str	r2, [r0, #80]
	sub	r3, r3, #1
	cmp	r3, #47
	movls	r2, #0
	bls	.L59
	cmp	r3, #98
	bls	.L68
	cmp	r3, #396
	bcc	.L69
	cmp	r3, #1584
	bcc	.L70
	cmp	r3, #6336
	movcs	r2, #5
	bcc	.L72
.L59:
	ldr	r3, .L78
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #256]
	str	r3, [r0, #88]
	ldmfd	sp, {fp, sp, pc}
.L77:
	cmp	r2, #1152
	bne	.L58
	mov	r2, #88
	mov	r3, #72
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L72:
	mov	r2, #4
	b	.L59
.L73:
	cmp	r2, #96
	bne	.L58
	mov	r2, #8
	mov	r3, #6
	str	r2, [r0, #84]
	mov	r2, #0
	str	r3, [r0, #80]
	b	.L59
.L74:
	cmp	r2, #144
	bne	.L58
	mov	r2, #11
	mov	r3, #9
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L68:
	mov	r2, #1
	b	.L59
.L75:
	cmp	r2, #288
	bne	.L58
	mov	r2, #22
	mov	r3, #18
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L69:
	mov	r2, #2
	b	.L59
.L76:
	cmp	r2, #576
	bne	.L58
	mov	r2, #44
	mov	r3, #36
	str	r2, [r0, #84]
	str	r3, [r0, #80]
.L70:
	mov	r2, #3
	b	.L59
.L79:
	.align	2
.L78:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_SetDimensions, .-Real9_CB_SetDimensions
	.align	2
	.global	Real9_CB_GetPicSize
	.type	Real9_CB_GetPicSize, %function
Real9_CB_GetPicSize:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #84)
	sub	sp, sp, #84
	ldr	ip, .L96
	mov	r9, r1
	mov	r4, r0
	mov	r8, r2
	mov	r7, r3
	ldmia	ip!, {r0, r1, r2, r3}
	sub	r6, fp, #108
	sub	lr, fp, #76
	add	r5, ip, #16
	add	r10, ip, #48
	stmia	r6!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	stmia	r6, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r5, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldmia	r10, {r0, r1, r2, r3}
	ldr	ip, [r9, #20]
	sub	ip, ip, #2
	cmp	ip, #1
	sub	ip, fp, #124
	stmia	ip, {r0, r1, r2, r3}
	bls	.L94
.L81:
	mov	r1, #3
	mov	r0, r4
	bl	BsShow
	mov	r1, #3
	mov	r5, r0
	mov	r0, r4
	bl	BsSkip
	sub	r3, fp, #44
	add	r5, r3, r5, lsl #2
	ldr	r6, [r5, #-64]
	cmp	r6, #0
	beq	.L84
.L83:
	mov	r1, #3
	mov	r0, r4
	bl	BsShow
	mov	r1, #3
	mov	r9, r0
	mov	r0, r4
	bl	BsSkip
	sub	r3, fp, #44
	add	r3, r3, r9, lsl #2
	ldr	r5, [r3, #-32]
	cmp	r5, #0
	beq	.L95
.L85:
	str	r6, [r8]
	str	r5, [r7]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L84:
	mov	r1, #8
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	mov	r5, r0
	mov	r0, r4
	bl	BsSkip
	cmp	r5, #255
	add	r6, r6, r5, lsl #2
	beq	.L84
	b	.L83
.L94:
	mov	r0, r4
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	beq	.L81
	ldr	r3, [r9, #52]
	str	r3, [r8]
	ldr	r3, [r9, #56]
	str	r3, [r7]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	mov	r0, r4
	mov	r9, r9, asl #1
	bl	Real9_CB_Get1Bit
	sub	r2, fp, #44
	orr	r0, r0, r9
	and	r3, r0, #3
	add	r3, r2, r3, lsl #2
	ldr	r5, [r3, #-80]
	cmp	r5, #0
	bne	.L85
.L86:
	mov	r1, #8
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	mov	r9, r0
	mov	r0, r4
	bl	BsSkip
	cmp	r9, #255
	add	r5, r5, r9, lsl #2
	beq	.L86
	b	.L85
.L97:
	.align	2
.L96:
	.word	.LANCHOR0+280
	UNWIND(.fnend)
	.size	Real9_CB_GetPicSize, .-Real9_CB_GetPicSize
	.align	2
	.global	Real9_CB_FindNextSliceStartCode
	.type	Real9_CB_FindNextSliceStartCode, %function
Real9_CB_FindNextSliceStartCode:
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
	mov	r5, r0
	bl	BsToNextByte
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #2
	subgt	r6, r6, #2
	movwgt	r7, #7184
	movgt	r4, #0
	movtgt	r7, 29
	bgt	.L101
	b	.L102
.L105:
	bl	BsSkip
	cmp	r4, r6
	beq	.L102
.L101:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, r7
	mov	r0, r5
	bne	.L105
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L102:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_FindNextSliceStartCode, .-Real9_CB_FindNextSliceStartCode
	.align	2
	.global	Real9_CB_SearchBits_IgnoreOnly0
	.type	Real9_CB_SearchBits_IgnoreOnly0, %function
Real9_CB_SearchBits_IgnoreOnly0:
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
	mov	r6, #1
	sub	ip, r1, #1
	mov	r7, r2
	mov	r9, r3
	mov	r10, r1
	mov	r8, r0
	mov	r6, r6, asl ip
	bl	BsShow
	mov	r1, r10
	mov	r4, r0
	mov	r0, r8
	bl	BsSkip
	cmp	r7, r4
	cmpne	r9, #0
	beq	.L107
	ands	r5, r4, r6
	bne	.L107
	ldr	r3, .L113
	add	r10, r3, r10, lsl #2
	ldr	r10, [r10, #360]
	b	.L108
.L109:
	tst	r4, r6
	bne	.L107
.L108:
	mov	r0, r8
	and	r4, r10, r4, asl #1
	bl	Real9_CB_Get1Bit
	add	r5, r5, #1
	orr	r4, r0, r4
	cmp	r7, r4
	cmpne	r9, r5
	bhi	.L109
.L107:
	rsb	r0, r7, r4
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L114:
	.align	2
.L113:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real9_CB_SearchBits_IgnoreOnly0, .-Real9_CB_SearchBits_IgnoreOnly0
	.align	2
	.global	Real9_CB_GetSSC
	.type	Real9_CB_GetSSC, %function
Real9_CB_GetSSC:
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
	ldr	r3, [r1, #12]
	cmp	r3, #1
	beq	.L117
	bl	Real9_CB_FindNextSliceStartCode
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L117:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_CB_GetSSC, .-Real9_CB_GetSSC
	.align	2
	.global	Real9_CB_GetSliceHeader
	.type	Real9_CB_GetSliceHeader, %function
Real9_CB_GetSliceHeader:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 8
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
	ldr	r4, [fp, #8]
	mov	r5, r1
	mov	r7, r2
	mov	r8, r3
	mov	r9, r0
	ldr	r6, [r4, #12]
	cmp	r6, #1
	beq	.L154
	cmp	r1, #0
	beq	.L155
	mov	r2, #0
	str	r2, [r7]
	ldr	r2, [fp, #4]
	mov	r0, #1
	mvn	r3, #0
	str	r3, [r2]
.L143:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L154:
	cmp	r1, #0
	bne	.L120
	ldr	r3, [r4, #96]
	cmn	r3, #1
	beq	.L156
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [r4, #92]
	cmp	r3, r6
	beq	.L123
.L133:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L155:
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	bne	.L133
	ldr	r5, [r4, #88]
	mov	r0, r9
	mov	r1, r5
	bl	BsShow
	mov	r1, r5
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	str	r6, [r7]
	ldr	r3, [r4, #88]
	cmp	r3, #11
	bls	.L138
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	bne	.L133
.L138:
	mov	r1, #5
	mov	r0, r9
	bl	BsShow
	mov	r1, #5
	mov	r5, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [fp, #4]
	cmp	r5, #31
	str	r5, [r3]
	bgt	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r5, r0
	mov	r0, r9
	bl	BsSkip
	str	r5, [r4, #60]
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	cmp	r0, #1
	mov	r4, r0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r5, r0
	mov	r0, r9
	bl	BsSkip
	str	r5, [r8]
	mov	r0, r4
	b	.L143
.L156:
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r5, r6
	mov	r1, #2
	mov	r10, r0
	mov	r0, r9
	bl	BsSkip
	str	r10, [r4, #92]
.L123:
	mov	r1, #5
	mov	r0, r9
	bl	BsShow
	mov	r1, #5
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	uxtb	r0, r6
	cmp	r0, #31
	strb	r0, [r4, #74]
	bhi	.L133
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	cmp	r0, #0
	bne	.L133
	mov	r0, r9
	bl	Real9_CB_Get1Bit
	subs	r10, r0, #0
	bne	.L133
	mov	r1, #2
	mov	r0, r9
	bl	BsShow
	mov	r1, #2
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	str	r6, [r4, #60]
	mov	r1, #1
	mov	r0, r9
	bl	BsShow
	mov	r1, #1
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	adds	r6, r6, #0
	mov	r1, #13
	mov	r0, r9
	movne	r6, #1
	cmp	r5, #0
	strb	r6, [r4, #73]
	add	r5, r4, #72
	beq	.L126
	bl	BsShow
	mov	r1, #13
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [r4, #92]
	str	r6, [r4, #100]
	cmp	r3, #1
	bls	.L128
	cmp	r3, #2
	ldreq	r2, [r4, #116]
	ldreq	r3, [r4, #120]
	streq	r2, [r4, #124]
	streq	r3, [r4, #128]
.L144:
	mov	r1, r5
	sub	r3, fp, #48
	sub	r2, fp, #52
	mov	r0, r9
	bl	Real9_CB_GetPicSize
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	movw	r1, #8144
	sub	r0, r2, #48
	cmp	r0, r1
	str	r2, [r4, #116]
	str	r2, [r4, #24]
	str	r3, [r4, #120]
	str	r3, [r4, #20]
	bhi	.L133
	sub	r3, r3, #48
	cmp	r3, r1
	bhi	.L133
	mov	r0, r4
	bl	Real9_CB_SetDimensions
.L134:
	ldr	r5, [r4, #88]
	mov	r0, r9
	mov	r1, r5
	bl	BsShow
	mov	r1, r5
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	str	r6, [r4, #96]
.L120:
	ldr	r2, [r4, #96]
	mov	r3, #0
	ldr	r1, [fp, #4]
	mov	r0, #1
	str	r2, [r7]
	ldrb	r2, [r4, #74]	@ zero_extendqisi2
	str	r2, [r1]
	str	r3, [r8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L126:
	bl	BsShow
	mov	r1, #13
	mov	r6, r0
	mov	r0, r9
	bl	BsSkip
	ldr	r3, [r4, #100]
	cmp	r3, r6
	bne	.L133
	sub	r3, fp, #48
	sub	r2, fp, #52
	mov	r1, r5
	mov	r0, r9
	bl	Real9_CB_GetPicSize
	ldr	r2, [r4, #116]
	ldr	r3, [fp, #-52]
	cmp	r2, r3
	bne	.L133
	ldr	r2, [r4, #120]
	ldr	r3, [fp, #-48]
	cmp	r2, r3
	bne	.L133
	b	.L134
.L128:
	str	r10, [r4, #124]
	str	r10, [r4, #128]
	b	.L144
	UNWIND(.fnend)
	.size	Real9_CB_GetSliceHeader, .-Real9_CB_GetSliceHeader
	.align	2
	.global	Real9_CB_GetPictureHeader
	.type	Real9_CB_GetPictureHeader, %function
Real9_CB_GetPictureHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #24)
	sub	sp, sp, #24
	ldr	r3, [r1, #12]
	mov	r4, r1
	mov	r5, r0
	cmp	r3, #1
	beq	.L181
	ldr	r3, .L184
	mov	r2, #136
	mov	r1, #0
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	mov	r1, #16
	mov	r0, r5
	bl	BsShow
	mov	r1, #16
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	movw	r3, #21845
	cmp	r6, r3
	bne	.L177
	mov	r1, #16
	mov	r0, r5
	bl	BsShow
	mov	r1, #16
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r7, r6
	bne	.L177
	mov	r0, r5
	sub	r1, fp, #32
	bl	Real9_CB_GetVLCBits
	cmp	r0, #30
	bls	.L177
	ldr	r3, [fp, #-32]
	ands	r2, r3, #1
	bne	.L177
	tst	r3, #2
	mov	r0, r5
	strne	r2, [r4, #24]
	moveq	r1, #176
	moveq	r2, #144
	streq	r1, [r4, #24]
	sub	r1, fp, #32
	str	r2, [r4, #20]
	ubfx	r2, r3, #2, #5
	ubfx	r3, r3, #7, #8
	str	r2, [r4, #56]
	str	r3, [r4, #44]
	bl	Real9_CB_GetVLCBits
	cmp	r0, #1
	streq	r0, [r4, #16]
	beq	.L171
	cmp	r0, #3
	beq	.L182
	cmp	r0, #5
	bne	.L177
	ldr	r3, [fp, #-32]
	cmp	r3, #0
	bne	.L177
	mov	r3, #2
	str	r3, [r4, #16]
.L171:
	ldr	r3, [r4, #24]
	cmp	r3, #0
	beq	.L183
.L173:
	sub	r3, r3, #48
	movw	r2, #8144
	cmp	r3, r2
	bhi	.L177
	ldr	r3, [r4, #20]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L177
	mov	r0, r4
	mov	r6, #1
	bl	Real9_CB_SetDimensions
	mov	r1, #2
	mov	r0, r5
	bl	BsShow
	mov	r1, #2
	mov	r7, r0
	mov	r0, r5
	bl	BsSkip
	str	r7, [r4, #60]
.L159:
	ldr	r3, [r4, #24]
	mov	r0, r6
	ldr	r2, [r4, #20]
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	str	r3, [r4, #32]
	mov	r2, r2, lsr #4
	str	r2, [r4, #28]
	mul	r3, r3, r2
	str	r3, [r4, #36]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L182:
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r4, #16]
	beq	.L171
.L177:
	mvn	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L181:
	str	r1, [sp, #4]
	mvn	r2, #0
	sub	r3, fp, #32
	str	r2, [r1, #96]
	str	r3, [sp]
	sub	r2, fp, #36
	sub	r3, fp, #40
	mov	r1, #0
	bl	Real9_CB_GetSliceHeader
	cmp	r0, #1
	mvnne	r6, #1
	bne	.L159
	ldr	r3, [r4, #92]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L175
.L162:
	.word	.L161
	.word	.L163
	.word	.L164
	.word	.L165
.L183:
	mov	r1, r4
	mov	r0, r5
	bl	Real9_CB_GetCPFMT
	cmp	r0, #0
	beq	.L177
	ldr	r3, [r4, #24]
	b	.L173
.L165:
	mov	r6, #1
	mov	r3, #2
	str	r3, [r4, #16]
.L160:
	ldr	r3, [r4, #24]
	movw	r2, #8144
	ldrb	lr, [r4, #73]	@ zero_extendqisi2
	sub	r3, r3, #48
	ldrb	ip, [r4, #74]	@ zero_extendqisi2
	ldr	r0, [r4, #100]
	cmp	r3, r2
	ldr	r1, [r4, #104]
	ldr	r3, [r4, #108]
	str	lr, [r4, #52]
	str	ip, [r4, #56]
	str	r0, [r4, #44]
	str	r1, [r4, #64]
	str	r3, [r4, #68]
	bhi	.L177
	ldr	r3, [r4, #20]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L177
	mov	r0, r4
	bl	Real9_CB_SetDimensions
	b	.L159
.L164:
	mov	r0, #1
	str	r0, [r4, #16]
	mov	r6, r0
	b	.L160
.L163:
	mov	r3, #0
	mov	r6, #1
	str	r3, [r4, #16]
	str	r3, [r4, #76]
	b	.L160
.L161:
	mov	r0, #1
	mov	r3, #0
	str	r0, [r4, #76]
	mov	r6, r0
	str	r3, [r4, #16]
	b	.L160
.L175:
	mvn	r6, #1
	b	.L160
.L185:
	.align	2
.L184:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Real9_CB_GetPictureHeader, .-Real9_CB_GetPictureHeader
	.align	2
	.global	Real9_SetImgFormat
	.type	Real9_SetImgFormat, %function
Real9_SetImgFormat:
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
	add	r3, r0, #53248
	mov	r5, r0
	ldr	r1, [r3, #1040]
	ldr	r0, [r3, #1440]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r2, r5, #49152
	ldrb	lr, [r4, #64]	@ zero_extendqisi2
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	mov	r1, #5
	ldr	ip, [r2, #3792]
	mov	r7, #1
	and	r3, r3, #252
	mov	r6, #0
	bfi	lr, ip, #0, #2
	orr	r3, r3, #12
	and	lr, lr, #227
	bfi	r3, r7, #4, #2
	bfi	lr, r1, #5, #3
	strb	r3, [r4, #65]
	strb	lr, [r4, #64]
	and	ip, ip, #3
	ldr	r3, [r4, #64]
	mov	r1, r6
	bfc	r3, #14, #3
	str	r3, [r4, #64]
	ldrb	lr, [r2, #3776]	@ zero_extendqisi2
	mov	r3, r3, lsr #16
	bfi	r3, lr, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r2, #3780]
	str	ip, [r4, #56]
	str	ip, [r4, #60]
	str	r3, [r4, #120]
	str	r6, [r4, #52]
	ldr	r3, [r2, #3800]
	str	r3, [r4, #68]
	ldr	r3, [r2, #3796]
	str	r3, [r4, #72]
	bl	SetAspectRatio
	ldr	r3, [r5]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L192
.L188:
	mov	r2, #9
	mov	r3, #0
	str	r2, [r4, #296]
	mov	r2, #1
	strb	r3, [r4, #284]
	mov	r3, #8
	strb	r2, [r4, #291]
	strb	r2, [r4, #289]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L192:
	ldr	r3, [r4, #72]
	add	lr, r4, #512
	ldr	r2, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	mov	r1, r2, asl #4
	mov	r3, r3, lsr #4
	add	r6, ip, r2
	mul	r3, r3, r1
	add	r5, r3, ip
	str	r5, [r4, #40]
	ldrd	r0, [lr, #-8]
	add	r2, r5, r2
	adds	r0, r0, r3
	adc	r1, r1, r3, asr #31
	strd	r0, [lr]
	str	r5, [r4, #24]
	str	r2, [r4, #32]
	str	r6, [r4, #28]
	str	ip, [r4, #20]
	b	.L188
	UNWIND(.fnend)
	.size	Real9_SetImgFormat, .-Real9_SetImgFormat
	.align	2
	.global	RV9_RecordVFMWState
	.type	RV9_RecordVFMWState, %function
RV9_RecordVFMWState:
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
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	RV9_RecordVFMWState, .-RV9_RecordVFMWState
	.align	2
	.global	Real9_WriteSliceMsg
	.type	Real9_WriteSliceMsg, %function
Real9_WriteSliceMsg:
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
	mov	r2, #44
	add	r3, r0, #49152
	mla	r2, r2, r1, r0
	ldr	r4, [r3, #3940]
	add	r1, r1, #1
	add	ip, r2, #120
	add	lr, r2, #128
	str	r4, [r2, #100]
	ldr	r4, [r3, #3932]
	str	r4, [r2, #108]
	ldr	r4, [r3, #3936]
	str	r4, [r2, #116]
	ldr	r4, [r3, #3952]
	str	r4, [r2, #104]
	ldr	r4, [r3, #3944]
	str	r4, [r2, #112]
	ldr	r4, [r3, #3948]
	str	r4, [r2, #120]
	ldr	r2, [r3, #3920]
	str	r2, [ip, #4]
	ldr	r2, [r3, #3916]
	str	r2, [ip, #8]
	ldr	r2, [r3, #3912]
	str	r2, [lr, #4]
	ldr	r3, [r3, #3924]
	str	r3, [lr, #8]
	str	r1, [r0, #40]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_WriteSliceMsg, .-Real9_WriteSliceMsg
	.align	2
	.global	Real9_WritePicMsg
	.type	Real9_WritePicMsg, %function
Real9_WritePicMsg:
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
	add	r3, r0, #49152
	add	r2, r0, #53248
	ldr	r1, [r3, #3792]
	cmp	r1, #2
	strb	r1, [r0, #8]
	ldr	r1, [r3, #3808]
	str	r1, [r0, #12]
	ldr	r1, [r3, #3804]
	str	r1, [r0, #16]
	ldr	r1, [r2, #956]
	str	r1, [r0, #20]
	ldr	r2, [r2, #960]
	str	r2, [r0, #24]
	ldr	r2, [r3, #3832]
	str	r2, [r0, #28]
	ldr	r1, [r3, #3956]
	str	r1, [r0, #32]
	ldr	r1, [r3, #3960]
	str	r1, [r0, #36]
	strne	r2, [r3, #3956]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_WritePicMsg, .-Real9_WritePicMsg
	.align	2
	.global	Real9_WriteReg
	.type	Real9_WriteReg, %function
Real9_WriteReg:
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
	str	r1, [r0, #44]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_WriteReg, .-Real9_WriteReg
	.align	2
	.global	Real9_ModifySliceMsg
	.type	Real9_ModifySliceMsg, %function
Real9_ModifySliceMsg:
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
	ldr	r2, [r0, #136]
	ldr	r3, [r0, #12]
	cmp	r2, #0
	ldr	ip, [r0, #16]
	bne	.L205
	mul	ip, r3, ip
	ldr	r5, [r0, #40]
	cmp	r5, #2
	sub	ip, ip, #1
	bls	.L204
	ldr	r3, [r0, #180]
	sub	lr, r5, #1
	cmp	r3, #0
	cmpgt	ip, r3
	ble	.L205
	mov	r2, r0
	mov	r3, #1
	b	.L206
.L207:
	ldr	r1, [r2, #224]
	add	r2, r2, #44
	cmp	ip, r1
	cmpgt	r1, #0
	ble	.L205
.L206:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L207
.L204:
	cmp	r5, #1
	bls	.L208
	sub	r4, r5, #1
	mov	r3, r0
	mov	r2, #0
	b	.L209
.L210:
	ldr	lr, [r3, #136]
	add	r3, r3, #44
	add	r2, r2, #1
	ldr	r1, [r3, #136]
	cmp	lr, r1
	bge	.L205
.L209:
	cmp	r2, r4
	bne	.L210
	mov	r3, #44
	mla	r2, r3, r2, r0
	ldr	r3, [r2, #136]
	cmp	ip, r3
	cmpge	r3, #0
	ble	.L205
.L208:
	cmp	r5, #0
	beq	.L211
	sub	r7, r5, #1
	mov	r6, r0
	mov	lr, r0
	mov	r4, #0
	b	.L214
.L229:
	cmp	r4, r5
	beq	.L228
.L214:
	cmp	r4, r7
	streq	ip, [lr, #140]
	add	r4, r4, #1
	add	lr, lr, #44
	ldrne	r3, [lr, #136]
	moveq	r1, ip
	subne	r1, r3, #1
	ldr	r3, [lr, #92]
	strne	r1, [lr, #96]
	mov	r2, r3, lsr #31
	cmp	ip, r3
	orrlt	r2, r2, #1
	cmp	r3, r1
	movle	r3, r2
	orrgt	r3, r2, #1
	orr	r3, r3, r1, lsr #31
	cmp	ip, r1
	orrlt	r3, r3, #1
	cmp	r3, #0
	beq	.L229
.L205:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L228:
	ldr	r2, [r0, #100]
	mov	r1, r2
	b	.L217
.L230:
	ldr	r1, [r6, #100]
.L217:
	cmp	r2, r1
	ldr	ip, [r6, #104]
	add	r3, r3, #1
	movcs	r2, r1
	cmp	ip, r2
	bcs	.L215
	ldr	r1, [r6, #120]
	cmp	r1, #0
	movne	r2, ip
.L215:
	cmp	r5, r3
	add	r6, r6, #44
	bne	.L230
	bic	r2, r2, #15
	ldr	lr, [r0, #40]
	str	r2, [r0, #48]
	mov	r3, r0
	mov	ip, #0
	b	.L221
.L231:
	ldr	r4, [r3, #108]
	rsb	r2, r2, r1
	and	r1, r4, #7
	add	r2, r2, r4, lsr #3
	and	r4, r2, #15
	bic	r2, r2, #15
	str	r2, [r3, #100]
	add	r2, r1, r4, lsl #3
	str	r2, [r3, #108]
.L219:
	add	ip, ip, #1
	add	r3, r3, #44
	cmp	lr, ip
	bls	.L220
	ldr	r2, [r0, #48]
.L221:
	ldr	r1, [r3, #104]
	cmp	r1, #0
	rsb	r4, r2, r1
	ldr	r1, [r3, #100]
	beq	.L231
	ldr	r5, [r3, #108]
	rsb	r2, r2, r1
	ldr	r7, [r3, #112]
	and	r6, r5, #7
	add	r2, r2, r5, lsr #3
	and	r5, r7, #7
	add	r1, r4, r7, lsr #3
	and	r4, r2, #15
	and	r7, r1, #15
	bic	r2, r2, #15
	add	r4, r6, r4, lsl #3
	str	r2, [r3, #100]
	bic	r1, r1, #15
	add	r2, r5, r7, lsl #3
	str	r4, [r3, #108]
	str	r2, [r3, #112]
	str	r1, [r3, #104]
	b	.L219
.L211:
	ldr	r3, [r0, #100]
	bic	r3, r3, #15
	str	r3, [r0, #48]
.L220:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real9_ModifySliceMsg, .-Real9_ModifySliceMsg
	.align	2
	.global	REAL9DEC_Init
	.type	REAL9DEC_Init, %function
REAL9DEC_Init:
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
	ldr	r3, .L236
	mov	r6, r1
	movw	r2, #54704
	mov	r1, #0
	mov	r4, r0
	mov	r5, r1
	ldr	r3, [r3, #48]
	blx	r3
	add	r0, r4, #54272
	add	r0, r0, #64
	bl	ResetVoQueue
	add	r3, r4, #49152
	str	r6, [r4]
	mov	r2, #15
	str	r2, [r3, #3956]
	add	ip, r4, #8192
	str	r2, [r3, #3960]
	mov	r1, #8192
	ldr	lr, [r6, #8]
	mov	r2, #1
	strb	r5, [ip, #3192]
	mov	r0, r4
	add	r4, r4, #53248
	strb	lr, [ip, #3188]
	str	r1, [r3, #3816]
	str	r2, [r3, #3788]
	strb	r2, [r3, #3784]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #1440]
	mov	r0, r5
	beq	.L235
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L235:
	ldr	r1, .L236+4
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L237:
	.align	2
.L236:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	UNWIND(.fnend)
	.size	REAL9DEC_Init, .-REAL9DEC_Init
	.align	2
	.global	REAL9DEC_Destroy
	.type	REAL9DEC_Destroy, %function
REAL9DEC_Destroy:
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
	add	r3, r0, #53248
	ldr	r1, .L239
	mov	r0, #2
	ldr	r2, [r3, #932]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L240:
	.align	2
.L239:
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL9DEC_Destroy, .-REAL9DEC_Destroy
	.global	__aeabi_idiv
	.align	2
	.global	REAL9DEC_Decode
	.type	REAL9DEC_Decode, %function
REAL9DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 200
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #220)
	sub	sp, sp, #220
	add	r10, r0, #49152
	mov	r3, r0
	str	r0, [fp, #-200]
	mov	r4, r1
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	add	r3, r3, #8
	str	r3, [fp, #-204]
	bl	memset
	ldr	r2, [r10, #3892]
	ldr	r3, [r10, #3896]
	cmp	r4, #0
	mov	r0, #1
	mov	r1, #8192
	str	r2, [r10, #3900]
	str	r2, [fp, #-56]
	str	r2, [fp, #-64]
	str	r3, [r10, #3904]
	str	r3, [fp, #-52]
	str	r3, [fp, #-60]
	str	r0, [r10, #3788]
	str	r0, [fp, #-168]
	str	r1, [r10, #3816]
	str	r1, [fp, #-140]
	beq	.L383
	ldr	ip, [fp, #-200]
	movw	r2, #11356
	ldr	r3, .L404
	mov	r1, #0
	add	r5, ip, #53248
	ldr	r0, [fp, #-204]
	add	r8, ip, #8192
	mov	r9, r1
	ldr	r3, [r3, #48]
	blx	r3
	str	r9, [r5, #896]
	ldr	r3, [r4, #12]
	str	r3, [r5, #916]
	ldr	r3, [r4, #8]
	str	r3, [r5, #900]
	ldr	r3, [r4]
	str	r3, [r8, #3176]
	ldr	r2, [r4, #12]
	str	r2, [r5, #904]
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	strb	r3, [r8, #3180]
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L244
	ldr	r3, [r4, #88]
	str	r3, [r5, #908]
	ldr	r3, [r4, #80]
	str	r3, [r8, #3184]
	ldr	r3, [r4, #92]
	str	r3, [r5, #912]
	ldrb	r3, [r4, #85]	@ zero_extendqisi2
	strb	r3, [r8, #3181]
	ldrb	r3, [r4, #85]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L384
.L245:
	movw	r3, #65525
	sub	r1, r2, #10
	movt	r3, 47
	cmp	r1, r3
	bhi	.L379
	ldr	r1, [r8, #3176]
	cmp	r1, #0
	beq	.L379
	ldr	r7, [fp, #-200]
	add	r4, r7, #54272
	add	r4, r4, #32
	mov	r0, r4
	bl	BsInit
	mov	r1, #8
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	mov	r6, r0
	mov	r0, r4
	bl	BsSkip
	cmp	r6, #255
	add	r0, r6, #1
	str	r0, [r10, #3964]
	bhi	.L379
	cmp	r0, #0
	beq	.L248
	add	r9, r7, #52992
	movw	r3, #65535
	add	r9, r9, #124
	movt	r3, 47
	str	r5, [fp, #-208]
	mov	r6, #0
	mov	r5, r9
	mov	r9, r3
	b	.L249
.L386:
	ldr	r0, [r10, #3964]
	cmp	r0, r6
	bls	.L385
.L249:
	mov	r1, #32
	mov	r0, r4
	bl	BsSkip
	mov	r1, #32
	mov	r0, r4
	add	r6, r6, #1
	bl	BsShow
	mov	r1, #32
	mov	r7, r0
	mov	r0, r4
	bl	BsSkip
	rev	r0, r7
	cmp	r0, r9
	str	r0, [r5, #4]!
	ble	.L386
.L379:
	mov	r9, #0
.L368:
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L384:
	ldr	r1, [r4, #16]
	ldr	r0, [r5, #1440]
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r4, #96]
	ldr	r0, [r5, #1440]
	bl	SM_ReleaseStreamSeg
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L244:
	str	r9, [r5, #908]
	str	r9, [r8, #3184]
	str	r9, [r5, #912]
	strb	r9, [r8, #3181]
	b	.L245
.L383:
	ldr	r3, [fp, #-200]
	mov	r9, r4
	ldr	r1, .L404+4
	add	r7, r3, #53248
	ldr	r2, [r7, #932]
	bl	dprint_vfmw
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L385:
	ldr	r5, [fp, #-208]
.L248:
	ldr	r7, [fp, #-200]
	sub	r6, r0, #1
	mov	r2, #0
	add	r3, r7, #52992
	add	r3, r3, #128
	b	.L250
.L251:
	ldr	ip, [r3, #4]!
	ldr	r1, [r3, #-4]
	cmp	ip, r1
	ble	.L379
.L250:
	cmp	r2, r6
	add	r2, r2, #1
	bne	.L251
	ldr	r2, [r10, #3968]
	mov	r0, r0, asl #3
	add	r1, r0, #1
	movw	r3, #65534
	add	r0, r1, r2
	cmp	r1, #3145728
	sub	r6, r0, #1
	movt	r3, 47
	movlt	r2, #0
	movge	r2, #1
	cmp	r6, r3
	movls	r6, r2
	orrhi	r6, r2, #1
	str	r7, [fp, #-200]
	cmp	r6, #0
	str	r1, [fp, #-208]
	str	r0, [fp, #-212]
	bne	.L379
	ldr	r2, [r5, #904]
	mov	r3, r0
	rsb	r2, r0, r2
	cmp	r2, #0
	ble	.L379
	ldr	r1, [r8, #3176]
	mov	r0, r4
	add	r1, r1, r3
	bl	BsInit
	sub	r1, fp, #180
	mov	r0, r4
	bl	Real9_CB_GetPictureHeader
	cmp	r0, #1
	mov	r9, r0
	bne	.L387
	ldrb	r3, [r8, #3192]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L253
	ldr	r2, [fp, #-148]
	ldr	r3, [r10, #3808]
	cmp	r2, r3
	beq	.L388
.L253:
	ldr	r3, .L404+8
	ldr	r6, [r3]
	cmp	r6, #0
	beq	.L255
	ldr	r0, [fp, #-148]
	mov	r3, #8
	ldr	r1, [r10, #3804]
	sub	r2, fp, #188
	ldr	lr, [r10, #3808]
	strh	r0, [fp, #-184]	@ movhi
	ldrh	r0, [fp, #-152]
	strh	r1, [fp, #-186]	@ movhi
	mov	r1, #2
	strh	lr, [fp, #-188]	@ movhi
	strh	r0, [fp, #-182]	@ movhi
	ldr	r0, [r5, #1440]
	blx	r6
.L255:
	ldr	r0, [r5, #1440]
	bl	FSP_GetFspType
	subs	lr, r0, #0
	bne	.L256
	sub	r3, fp, #44
	sub	r2, fp, #192
	sub	r1, fp, #196
	ldr	r0, [r5, #1440]
	str	lr, [r3, #-144]!
	str	lr, [fp, #-196]
	str	lr, [fp, #-192]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [fp, #-200]
	ldr	r3, [r3]
	ldr	r2, [r3, #724]
	cmp	r2, #1
	beq	.L389
.L256:
	ldr	r3, [fp, #-200]
	mov	r2, #1
	ldr	r1, [r5, #1036]
	ldr	r0, [r5, #1440]
	add	r6, r3, #54272
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r5, #1032]
	add	r6, r6, #64
	ldr	r0, [r5, #1440]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r5, #1440]
	str	r3, [r5, #1032]
	str	r3, [r5, #1036]
	str	r3, [fp, #-216]
	bl	FSP_GetNullLogicFs
	ldr	r3, [fp, #-216]
	mov	r1, r6
	str	r0, [r5, #1036]
	str	r0, [r5, #1032]
	strb	r3, [r8, #3189]
	ldr	r0, [r5, #1440]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [fp, #-148]
	ldr	r3, [fp, #-152]
	cmp	r2, #512
	bhi	.L263
	cmp	r3, #512
	bhi	.L263
	ldr	r3, [fp, #-200]
	ldr	r3, [r3]
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L265
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L390
.L265:
	ldr	r0, [r5, #1440]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L374
.L267:
	ldr	r3, [fp, #-152]
	mov	r0, #1
	ldr	r2, [fp, #-148]
	ldr	r1, .L404+12
	bl	dprint_vfmw
	sub	r2, fp, #180
	ldr	r1, [fp, #-200]
	mov	r0, #6
	bl	Real9_ArrangeVHBMem
	subs	r3, r0, #0
	beq	.L391
.L254:
	ldr	r6, [fp, #-200]
	sub	r1, fp, #180
	add	r3, r6, #52736
	mov	r2, r3
	ldr	r3, .L404
	add	r2, r2, #192
	str	r2, [fp, #-216]
	ldr	r3, [r3, #52]
	mov	r0, r2
	mov	r2, #136
	blx	r3
	ldr	r3, [r6]
	mov	r0, r6
	ldr	r3, [r3, #8]
	strb	r3, [r8, #3188]
	bl	Real9_GetImageBuffer
	subs	r3, r0, #0
	beq	.L392
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	bl	FSP_GetFsImagePtr
	subs	lr, r0, #0
	beq	.L270
	ldr	r2, [fp, #-200]
	add	r3, lr, #592
	add	ip, lr, #608
	ldr	r1, .L404+16
	mov	r0, #29
	ldr	r2, [r2]
	ldrd	r6, [r2, #56]
	ldr	r2, [fp, #-200]
	strd	r6, [r3, #-8]
	ldr	r2, [r2]
	ldrd	r6, [r2, #72]
	ldr	r2, [fp, #-200]
	strd	r6, [r3]
	ldr	r2, [r2]
	ldrd	r6, [r2, #88]
	strd	r6, [ip, #-8]
	mvn	r6, #0
	ldr	ip, [fp, #-200]
	mvn	r7, #0
	ldr	r2, [ip]
	ldr	r2, [r2, #104]
	str	r2, [lr]
	ldr	r2, [ip]
	ldr	r2, [r2, #108]
	str	r2, [lr, #4]
	ldr	r2, [ip]
	ldr	r2, [r2, #112]
	str	r2, [lr, #8]
	ldr	r2, [ip]
	ldr	r2, [r2, #128]
	str	r2, [lr, #12]
	ldr	r2, [ip]
	strd	r6, [r2, #56]
	ldrd	r6, [r3]
	ldrd	r2, [r3, #-8]
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [r10, #3792]
	cmp	r3, #2
	beq	.L393
	cmp	r3, #1
	ldrb	r3, [r8, #3189]	@ zero_extendqisi2
	beq	.L394
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #1
.L274:
	strb	r3, [r8, #3189]
	ldr	r2, [r5, #1032]
	ldr	r3, [r5, #1036]
	cmp	r2, r3
	beq	.L275
	ldr	r1, .L404+20
	mov	r0, #13
	bl	dprint_vfmw
	mov	r2, #0
	ldr	r1, [r5, #1032]
	ldr	r0, [r5, #1440]
	bl	FSP_SetRef
.L275:
	ldr	r3, [r5, #1036]
	mov	r2, #1
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	str	r3, [r5, #1032]
	str	r1, [r5, #1036]
	bl	FSP_SetRef
	ldr	r1, [r5, #1032]
	ldr	r0, [r5, #1440]
	bl	FSP_RemovePmv
	ldr	r2, [r5, #1040]
	ldr	r1, .L404+24
	mov	r0, #13
	bl	dprint_vfmw
	ldrb	r3, [r8, #3188]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L277
	ldr	r3, [r10, #3792]
	cmp	r3, #0
	beq	.L375
	cmp	r3, #2
	beq	.L318
	cmp	r3, #1
	beq	.L375
.L277:
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #1032]
	str	r0, [fp, #-220]
	ldr	r0, [r5, #1440]
	bl	FSP_GetLogicFs
	ldr	r1, [r5, #1036]
	mov	r6, r0
	str	r0, [fp, #-228]
	ldr	r0, [r5, #1440]
	bl	FSP_GetLogicFs
	ldr	ip, [fp, #-220]
	mov	r3, r6
	cmp	ip, #0
	cmpne	r6, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r6, r0
	cmp	r3, #0
	bne	.L395
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L283
	ldr	r2, [ip, #32]
	cmp	r2, #0
	beq	.L283
	ldr	r2, [r0, #28]
	mov	r0, #13
	ldr	lr, [fp, #-200]
	cmp	r2, #0
	ldr	r1, .L404+28
	ldrne	r3, [r2, #8]
	ldreq	r3, [r3, #8]
	ldr	r2, [fp, #-200]
	str	r3, [fp, #-220]
	ldr	r3, [fp, #-220]
	str	r3, [r2, #52]
	ldr	r3, [fp, #-228]
	ldr	r3, [r3, #28]
	cmp	r3, #0
	ldreq	r3, [ip, #28]
	ldr	r3, [r3, #8]
	str	ip, [fp, #-236]
	str	r3, [fp, #-224]
	ldr	r3, [fp, #-224]
	str	r3, [lr, #56]
	ldr	r3, [ip, #28]
	ldr	r2, [r3, #8]
	str	r2, [lr, #60]
	ldr	r3, [ip, #8]
	str	r3, [lr, #72]
	mov	r7, r3
	ldr	r3, [r6, #8]
	str	r3, [fp, #-232]
	str	r3, [lr, #76]
	ldr	r3, [ip, #32]
	ldr	ip, [fp, #-232]
	ldr	r3, [r3, #8]
	str	ip, [sp, #12]
	ldr	ip, [fp, #-220]
	str	r7, [sp, #8]
	mov	r7, lr
	str	r3, [lr, #64]
	str	ip, [sp, #4]
	ldr	ip, [fp, #-224]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [fp, #-236]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #24]
	str	r3, [r7, #68]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #24]
	str	r3, [r5, #1004]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #60]
	str	r3, [r7, #88]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #44]
	str	r3, [r7, #92]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #48]
	str	r3, [r7, #96]
	ldr	r3, [r10, #3792]
	cmp	r3, #2
	beq	.L396
.L289:
	ldr	r3, [r10, #3820]
	mov	r0, r4
	ldr	r1, [fp, #-200]
	str	r3, [ip, #16]
	ldr	r3, [r10, #3792]
	ldr	r2, [r10, #3832]
	cmp	r3, #2
	strb	r3, [r1, #8]
	ldr	r3, [r10, #3808]
	str	r2, [fp, #-224]
	str	r3, [r1, #12]
	ldr	r3, [r10, #3804]
	str	r3, [r1, #16]
	ldr	r3, [r5, #956]
	str	r3, [r1, #20]
	ldr	r3, [r5, #960]
	str	r2, [r1, #28]
	str	r3, [r1, #24]
	ldr	r3, [r10, #3956]
	str	r3, [r1, #32]
	ldr	r3, [r10, #3960]
	str	r3, [r1, #36]
	strne	r2, [r10, #3956]
	bl	BsPos
	ldr	r1, [r10, #3964]
	cmp	r1, #1
	ldreq	r6, [r10, #3968]
	ldrne	r6, [r10, #3968]
	mov	r3, r0, asr #31
	mov	r2, r3, lsr #29
	add	r3, r0, r2
	moveq	r0, r4
	and	r3, r3, #7
	movne	r0, r4
	rsb	r3, r2, r3
	ldreq	r2, [fp, #-208]
	str	r3, [r10, #3932]
	ldreq	r3, [r5, #904]
	ldrne	r3, [r10, #3972]
	rsbeq	r3, r2, r3
	rsb	r6, r6, r3
	bl	BsPos
	ldr	r3, [fp, #-212]
	mov	r6, r6, asl #3
	rsb	r0, r0, r6
	str	r0, [r10, #3936]
	ldr	r6, [r5, #900]
	mov	r0, r4
	add	r6, r3, r6
	bl	BsPos
	ldr	r2, [r10, #3836]
	mov	r1, #1
	ldr	lr, [r10, #3828]
	ldr	ip, [fp, #-224]
	str	r2, [r10, #3916]
	str	lr, [r10, #3920]
	str	ip, [r10, #3912]
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	mov	r3, #0
	add	r0, r6, r0, asr #3
	ldr	r6, [fp, #-200]
	str	r0, [r10, #3940]
	str	r3, [r10, #3944]
	str	r3, [r10, #3948]
	str	r3, [r10, #3952]
	str	r3, [r10, #3924]
	str	r0, [r6, #100]
	ldr	r0, [r10, #3932]
	str	r0, [r6, #108]
	ldr	r0, [r10, #3936]
	str	lr, [r6, #124]
	mov	lr, r6
	str	r3, [r6, #104]
	str	r0, [r6, #116]
	mov	r0, r6
	str	r3, [r6, #112]
	str	r3, [r6, #120]
	str	r2, [r6, #128]
	str	r3, [r6, #136]
	str	ip, [r0, #132]
	str	r1, [r6, #40]
	ldr	r2, [r10, #3964]
	cmp	r2, r1
	bls	.L314
	ldr	r2, [r10, #3972]
	movw	r0, #65535
	ldr	ip, [fp, #-208]
	movt	r0, 47
	add	ip, ip, r2
	cmp	ip, r0
	bgt	.L302
	cmp	ip, #0
	ble	.L302
	ldr	r2, [r5, #904]
	rsb	r2, ip, r2
	cmp	r2, #0
	ble	.L302
	ldr	lr, [fp, #-200]
	mov	r6, r1
	str	r9, [fp, #-240]
	mov	r7, r5
	add	lr, lr, #52992
	str	r3, [fp, #-236]
	add	r1, lr, #132
	str	r0, [fp, #-220]
	sub	lr, fp, #188
	str	r6, [fp, #-228]
	str	lr, [fp, #-212]
	mov	r9, ip
	mov	r5, r1
	b	.L305
.L306:
	ldr	r3, [r10, #3964]
	add	r6, r6, #1
	cmp	r3, r6
	bls	.L397
	ldr	r3, [fp, #-208]
	ldr	r9, [r5, #4]!
	add	r9, r3, r9
	ldr	r3, [fp, #-220]
	cmp	r9, r3
	bgt	.L373
	cmp	r9, #0
	ble	.L373
	ldr	r2, [r7, #904]
	rsb	r2, r9, r2
	cmp	r2, #0
	ble	.L373
.L305:
	ldr	r1, [r8, #3176]
	mov	r0, r4
	add	r1, r1, r9
	bl	BsInit
	ldr	r3, [fp, #-216]
	sub	r2, fp, #196
	mov	r1, #0
	mov	r0, r4
	str	r3, [sp, #4]
	ldr	r3, [fp, #-212]
	str	r3, [sp]
	sub	r3, fp, #192
	bl	Real9_CB_GetSliceHeader
	cmp	r0, #1
	bne	.L306
	ldr	r3, [r10, #3808]
	ldr	r2, [fp, #-196]
	cmp	r3, #0
	str	r2, [fp, #-232]
	beq	.L398
	ldr	r3, [fp, #-188]
	mov	r0, r4
	ldr	r2, [fp, #-224]
	cmp	r3, #0
	movge	r2, r3
	str	r2, [fp, #-224]
	bl	BsPos
	ldr	r2, [r10, #3964]
	sub	lr, r2, #1
	cmp	lr, r6
	mov	r3, r0, asr #31
	mov	r1, r3, lsr #29
	add	r3, r0, r1
	and	r3, r3, #7
	rsb	r3, r1, r3
	str	r3, [r10, #3932]
	beq	.L399
	cmp	r6, #254
	bhi	.L400
	ldr	r3, [r5, #4]
	mov	r0, r4
	ldr	r2, [r5]
.L378:
	rsb	r3, r2, r3
	mov	r3, r3, asl #3
	str	r3, [fp, #-244]
	bl	BsPos
	ldr	r3, [fp, #-244]
	rsb	r0, r0, r3
	str	r0, [r10, #3936]
	ldr	r2, [r7, #900]
	mov	r0, r4
	add	r9, r9, r2
	bl	BsPos
	ldr	r1, [fp, #-200]
	mov	r3, #44
	ldr	ip, [fp, #-236]
	ldr	lr, [r10, #3828]
	str	ip, [r10, #3944]
	str	ip, [r10, #3948]
	str	lr, [r10, #3920]
	add	r2, r0, #7
	cmp	r0, #0
	movlt	r0, r2
	ldr	r2, [fp, #-228]
	mla	r3, r3, r2, r1
	add	r2, r9, r0, asr #3
	ldr	r0, [fp, #-228]
	ldr	r1, [r10, #3836]
	add	r0, r0, #1
	str	r0, [fp, #-228]
	str	r2, [r10, #3940]
	mov	r9, r0
	mov	r0, ip
	str	r0, [r10, #3952]
	cmp	r9, #131
	ldr	r0, [fp, #-224]
	str	r1, [r10, #3916]
	add	r1, r3, #128
	str	r0, [r10, #3912]
	ldr	r0, [fp, #-232]
	str	r0, [r10, #3924]
	add	r0, r3, #120
	str	r2, [r3, #100]
	ldr	r2, [r10, #3932]
	str	r2, [r3, #108]
	ldr	r2, [r10, #3936]
	str	r2, [r3, #116]
	ldr	r2, [r10, #3952]
	str	r2, [r3, #104]
	ldr	r2, [r10, #3944]
	str	r2, [r3, #112]
	ldr	r2, [r10, #3948]
	str	r2, [r3, #120]
	ldr	r3, [r10, #3920]
	str	r3, [r0, #4]
	ldr	r3, [r10, #3916]
	str	r3, [r0, #8]
	ldr	r3, [r10, #3912]
	str	r3, [r1, #4]
	ldr	r3, [r10, #3924]
	str	r3, [r1, #8]
	ldr	r1, [fp, #-200]
	str	r9, [r1, #40]
	ble	.L306
	mov	r0, r1
	bl	Real9_ModifySliceMsg
	cmp	r0, #1
	bne	.L373
	ldr	r3, [fp, #-200]
	ldr	r2, [fp, #-204]
	str	r2, [r3, #4]
	b	.L306
.L387:
	ldr	r1, .L404+32
	mov	r0, #1
	mov	r9, r6
	bl	dprint_vfmw
	b	.L368
.L263:
	ldr	r1, .L404+36
	mov	r0, #18
	bl	dprint_vfmw
	b	.L379
.L392:
	ldr	r2, [r5, #932]
	mov	r9, r3
	ldr	r1, .L404+40
	bl	dprint_vfmw
	b	.L368
.L389:
	ldr	r3, [fp, #-188]
	cmp	r3, #0
	bgt	.L259
	ldr	r3, [fp, #-192]
	cmp	r3, #32
	bgt	.L259
	ldr	r3, [fp, #-200]
	ldr	r3, [r3, #4]
	cmp	r3, #0
	bne	.L259
	ldr	r3, [r5, #928]
	cmp	r3, #0
	beq	.L256
	ldr	r6, [r10, #3808]
	cmp	r6, #0
	beq	.L256
	ldr	r0, [fp, #-152]
	ldr	r1, [r5, #1444]
	cmp	r0, r1
	beq	.L256
	ldr	r1, [fp, #-148]
	ldr	lr, [r5, #1448]
	cmp	r1, lr
	beq	.L256
	ldr	lr, [r10, #3804]
	str	r0, [sp, #12]
	mov	r0, r2
	str	r1, [sp, #8]
	stmia	sp, {r6, lr}
	ldr	r1, .L404+44
	bl	dprint_vfmw
	ldr	r3, .L404+8
	ldr	r2, [fp, #-152]
	ldr	r6, [r3]
	ldr	r3, [fp, #-148]
	cmp	r6, #0
	str	r2, [r5, #1444]
	str	r3, [r5, #1448]
	beq	.L256
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r5, #1440]
	blx	r6
	b	.L256
.L388:
	ldr	r2, [fp, #-152]
	ldr	r3, [r10, #3804]
	cmp	r2, r3
	bne	.L253
	b	.L254
.L390:
	ldrb	r3, [r8, #3192]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L267
.L374:
	mov	r0, r6
	bl	ResetVoQueue
	b	.L267
.L391:
	ldr	r1, .L404+48
	mov	r0, #1
	mov	r9, r3
	bl	dprint_vfmw
	b	.L368
.L373:
	mov	r5, r7
.L302:
	mov	r2, #1
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	mov	r9, #0
	bl	FSP_ClearLogicFs
	b	.L368
.L393:
	ldrb	r3, [r8, #3189]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L302
	ldrb	r3, [r8, #3188]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L277
.L318:
	ldr	r3, [r5, #1048]
	cmp	r3, #0
	bne	.L277
	mov	r2, #1
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	mov	r9, r3
	bl	FSP_ClearLogicFs
	b	.L368
.L375:
	str	r3, [r5, #1048]
	b	.L277
.L395:
	movw	r3, #1958
	ldr	r2, .L404+52
	ldr	r1, .L404+56
	mov	r0, #0
	bl	dprint_vfmw
	mov	r9, #0
	b	.L368
.L394:
	cmp	r3, #0
	movne	r3, #2
	bne	.L274
	b	.L379
.L399:
	add	r2, r2, #10432
	ldr	r3, [r7, #904]
	add	r2, r2, #5
	ldr	r1, [fp, #-208]
	mov	r0, r4
	add	r2, r8, r2, lsl #2
	rsb	r3, r1, r3
	ldr	r2, [r2, #3176]
	b	.L378
.L259:
	mvn	r9, #1
	b	.L368
.L270:
	mov	r2, #1
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	mov	r9, lr
	bl	FSP_ClearLogicFs
	b	.L368
.L397:
	ldr	r9, [fp, #-240]
	mov	r5, r7
.L314:
	ldr	r3, [fp, #-200]
	mov	r6, #1
	ldr	r4, [r3, #4]
	str	r6, [r3, #44]
	cmp	r4, #0
	beq	.L401
	ldr	r3, [fp, #-200]
	ldr	r3, [r3]
	ldr	r2, [r3, #880]
	cmp	r2, #1
	beq	.L319
.L316:
	cmp	r2, #2
	beq	.L402
.L317:
	ldr	r2, [r3, #592]
	ldr	r1, [fp, #-200]
	str	r2, [r1, #80]
	ldr	r3, [r3, #644]
	str	r3, [r1, #84]
	b	.L368
.L396:
	ldr	r3, [fp, #-228]
	ldr	r6, [r6, #16]
	ldr	r2, [r3, #16]
	ldr	r3, [r10, #3820]
	rsb	r6, r2, r6
	subs	r3, r3, r2
	ldrmi	r2, [r10, #3816]
	addmi	r3, r3, r2
	cmp	r6, #0
	ldrlt	r2, [r10, #3816]
	addlt	r6, r6, r2
	cmp	r3, r6
	movgt	r3, #0
	cmp	r6, #0
	ble	.L321
	mov	r1, r6
	mov	r0, r3, asl #14
	str	ip, [fp, #-228]
	str	r3, [fp, #-220]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-220]
	mov	r1, r6
	str	r0, [fp, #-224]
	rsb	r0, r3, r6
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
	ldr	r3, [fp, #-220]
	ldr	r2, [fp, #-224]
	ldr	ip, [fp, #-228]
.L293:
	str	r3, [r5, #948]
	str	r6, [r5, #952]
	str	r2, [r5, #956]
	str	r0, [r5, #960]
	b	.L289
.L283:
	ldr	r1, [r5, #1040]
	mov	r2, #1
	ldr	r0, [r5, #1440]
	mov	r9, #0
	bl	FSP_ClearLogicFs
	ldr	r1, .L404+60
	mov	r0, r9
	bl	dprint_vfmw
	b	.L368
.L400:
	movw	r2, #2190
	ldr	r1, .L404+64
	mov	r0, #22
	mov	r9, #0
	bl	dprint_vfmw
	b	.L368
.L398:
	mov	r2, r0
	ldr	r1, [r7, #1040]
	ldr	r0, [r7, #1440]
	mov	r9, r3
	bl	FSP_ClearLogicFs
	b	.L368
.L401:
	ldr	r0, [fp, #-200]
	bl	Real9_ModifySliceMsg
	cmp	r0, #1
	bne	.L403
	ldr	r1, [fp, #-200]
	ldr	r2, [fp, #-204]
	ldr	r3, [r1]
	str	r2, [r1, #4]
	ldr	r2, [r3, #880]
	cmp	r2, #1
	bne	.L316
	ldr	r2, [fp, #-204]
	cmp	r2, #0
	beq	.L317
	mov	r4, r2
.L319:
	ldrb	r2, [r4]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L317
	ldr	r4, [fp, #-200]
	mov	r2, #0
	mov	r9, r2
	str	r2, [r4, #4]
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	bl	FSP_SetDisplay
	mov	r1, r4
	mov	r0, #9
	bl	ReleasePacket
	b	.L368
.L402:
	ldr	r2, [r3, #884]
	cmp	r2, #0
	ble	.L317
	ldr	r2, [fp, #-200]
	ldr	r2, [r2, #4]
	cmp	r2, #0
	beq	.L317
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L317
	ldr	r4, [fp, #-200]
	mov	r2, #0
	mov	r9, r2
	str	r2, [r4, #4]
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	bl	FSP_SetDisplay
	ldr	r2, [r4]
	mov	r1, r4
	mov	r0, #9
	ldr	r3, [r2, #884]
	sub	r3, r3, #1
	str	r3, [r2, #884]
	bl	ReleasePacket
	b	.L368
.L321:
	mov	r0, #0
	mov	r2, r0
	b	.L293
.L403:
	mov	r2, r6
	ldr	r1, [r5, #1040]
	ldr	r0, [r5, #1440]
	mov	r9, r4
	bl	FSP_ClearLogicFs
	b	.L368
.L405:
	.align	2
.L404:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	.word	g_event_report
	.word	.LC16
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LC24
	.word	.LC13
	.word	.LC15
	.word	.LC18
	.word	.LC14
	.word	.LC17
	.word	.LANCHOR0+460
	.word	.LC22
	.word	.LC23
	.word	.LC25
	UNWIND(.fnend)
	.size	REAL9DEC_Decode, .-REAL9DEC_Decode
	.align	2
	.global	REAL9DEC_RecycleImage
	.type	REAL9DEC_RecycleImage, %function
REAL9DEC_RecycleImage:
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
	cmp	r0, #0
	mov	r5, r1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r4, r0, #53248
	mov	r2, #0
	ldr	r0, [r4, #1440]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #1440]
	bl	FSP_GetFsImagePtr
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL9DEC_RecycleImage, .-REAL9DEC_RecycleImage
	.align	2
	.global	REAL9DEC_GetRemainImg
	.type	REAL9DEC_GetRemainImg, %function
REAL9DEC_GetRemainImg:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, [r0]
	mov	r4, r0
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L424
	add	r6, r0, #53248
	ldr	r1, [r6, #1036]
	ldr	r0, [r6, #1440]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L424
	ldr	r1, [r6, #1036]
	ldr	r0, [r6, #1440]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L423
.L424:
	add	r5, r4, #54272
	add	r5, r5, #64
.L414:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	GetVoLastImageID
.L423:
	mov	r0, r4
	add	r5, r4, #54272
	bl	Real9_SetImgFormat
	add	r5, r5, #64
	mov	r3, #1
	str	r3, [r7, #180]
	mov	r2, r3
	ldr	r1, [r6, #1036]
	ldr	r0, [r6, #1440]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #1440]
	mov	r2, r4
	str	r7, [sp]
	mov	r3, r5
	mov	r1, #9
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L411
	mov	r2, #0
	ldr	r1, [r6, #1036]
	ldr	r0, [r6, #1440]
	bl	FSP_SetDisplay
	b	.L414
.L411:
	ldr	r3, [r7, #152]
	cmp	r3, #100
	bhi	.L414
	ldr	r3, [r7, #68]
	cmp	r3, #31
	bls	.L414
	ldr	r3, [r7, #72]
	cmp	r3, #31
	bls	.L414
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL9DEC_GetRemainImg, .-REAL9DEC_GetRemainImg
	.align	2
	.global	REAL9DEC_VDMPostProc
	.type	REAL9DEC_VDMPostProc, %function
REAL9DEC_VDMPostProc:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	mov	r6, r1
	mov	r5, r0
	ldr	r1, .L451
	mov	r9, r2
	mov	r0, #22
	mov	r2, r6
	add	r7, r5, #49152
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	add	r4, r5, #53248
	mov	r1, r5
	mov	r0, #9
	add	r8, r5, #8192
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	strb	r2, [r7, #3776]
	ldr	r3, [r3, #72]
	str	r3, [r7, #3780]
	bl	ReleasePacket
	ldr	r1, [r4, #1040]
	ldr	r0, [r4, #1440]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L426
	ldr	r3, [r7, #3792]
	cmp	r3, #2
	andne	r9, r9, #31
	strb	r3, [r8, #3190]
	strne	r9, [r7, #3960]
	cmp	r6, #0
	movlt	r6, #0
	blt	.L428
	cmp	r6, #100
	movge	r6, #100
.L428:
	str	r6, [r0, #152]
	mov	r0, #22
	ldr	r1, .L451+4
	bl	dprint_vfmw
	mov	r0, r5
	bl	Real9_SetImgFormat
	ldrb	r3, [r8, #3188]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L431
	ldr	r3, [r5]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	bne	.L431
	ldr	r3, [r7, #3792]
	cmp	r3, #2
	beq	.L431
	ldrb	r3, [r8, #3189]	@ zero_extendqisi2
	cmp	r3, #1
	ldrhi	r1, [r4, #1032]
	mvnls	r1, #0
	cmn	r1, #1
	str	r1, [r4, #1044]
	beq	.L433
.L450:
	ldr	r0, [r4, #1440]
	bl	FSP_GetFsImagePtr
	ldr	r6, [r4, #1044]
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r4, #1440]
	bl	FSP_GetRef
	mov	r2, r6
	ldr	r1, .L451+8
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #1044]
	ldr	r0, [r4, #1440]
	bl	FSP_SetDisplay
	add	r3, r5, #54272
	ldr	r0, [r4, #1440]
	add	r3, r3, #64
	str	r7, [sp]
	mov	r2, r5
	mov	r1, #9
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L449
.L433:
	ldr	r3, [r4, #932]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r4, #932]
.L426:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L431:
	ldr	r1, [r4, #1040]
	cmn	r1, #1
	str	r1, [r4, #1044]
	bne	.L450
	b	.L433
.L449:
	ldr	r0, [r4, #1440]
	mov	r2, #0
	ldr	r1, [r4, #1044]
	bl	FSP_SetDisplay
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L452:
	.align	2
.L451:
	.word	.LC26
	.word	.LC27
	.word	.LC28
	UNWIND(.fnend)
	.size	REAL9DEC_VDMPostProc, .-REAL9DEC_VDMPostProc
	.align	2
	.global	REAL9DEC_GetImageBuffer
	.type	REAL9DEC_GetImageBuffer, %function
REAL9DEC_GetImageBuffer:
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
	add	r4, r0, #53248
	mov	r5, r0
	ldr	r0, [r4, #1440]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #1440]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L459
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L459:
	add	r1, r5, #54272
	ldr	r0, [r4, #1440]
	add	r1, r1, #64
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL9DEC_GetImageBuffer, .-REAL9DEC_GetImageBuffer
	.align	2
	.global	REAL9DEC_Support
	.type	REAL9DEC_Support, %function
REAL9DEC_Support:
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
	mov	r3, #1
	str	r3, [r0]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL9DEC_Support, .-REAL9DEC_Support
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	gs_VLCDecodeTable, %object
	.size	gs_VLCDecodeTable, 256
gs_VLCDecodeTable:
	.byte	-128
	.byte	-127
	.byte	112
	.byte	112
	.byte	-126
	.byte	-125
	.byte	113
	.byte	113
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	80
	.byte	-124
	.byte	-123
	.byte	114
	.byte	114
	.byte	-122
	.byte	-121
	.byte	115
	.byte	115
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	81
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	48
	.byte	-120
	.byte	-119
	.byte	116
	.byte	116
	.byte	-118
	.byte	-117
	.byte	117
	.byte	117
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	82
	.byte	-116
	.byte	-115
	.byte	118
	.byte	118
	.byte	-114
	.byte	-113
	.byte	119
	.byte	119
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	83
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	49
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.type	MBA_FieldWidth, %object
	.size	MBA_FieldWidth, 24
MBA_FieldWidth:
	.word	6
	.word	7
	.word	9
	.word	11
	.word	13
	.word	14
.LC0:
	.word	160
	.word	176
	.word	240
	.word	320
	.word	352
	.word	640
	.word	704
	.word	0
.LC1:
	.word	120
	.word	132
	.word	144
	.word	240
	.word	288
	.word	480
	.word	0
	.word	0
.LC2:
	.word	180
	.word	360
	.word	576
	.word	0
	.type	GetBitsMask, %object
	.size	GetBitsMask, 100
GetBitsMask:
	.word	0
	.word	1
	.word	3
	.word	7
	.word	15
	.word	31
	.word	63
	.word	127
	.word	255
	.word	511
	.word	1023
	.word	2047
	.word	4095
	.word	8191
	.word	16383
	.word	32767
	.word	65535
	.word	131071
	.word	262143
	.word	524287
	.word	1048575
	.word	2097151
	.word	4194303
	.word	8388607
	.word	16777215
	.type	__FUNCTION__.14335, %object
	.size	__FUNCTION__.14335, 16
__FUNCTION__.14335:
	.ascii	"REAL9DEC_Decode\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC7:
	ASCII(.ascii	"image size abnormal (%dx%d) in MB\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"real9 actual frame size(%dx%d) exeed max config(%dx" )
	ASCII(.ascii	"%d)\012\000" )
.LC9:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC11:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC13:
	ASCII(.ascii	"Real9_CB_GetPictureHeader Error!\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC16:
	ASCII(.ascii	"new seq size %d * %d\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"Real9_ArrangeVHBMem err\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"Fatal Error: frm%d, get image buffer failed\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"++++++++++ ref %d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"CurFsID abnormal!,%s %d (NULL == pCur) || (NULL == " )
	ASCII(.ascii	"pFwd) || (NULL == pBwd)!!\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"CurFsID abnormal!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p," )
	ASCII(.ascii	"%p,%p,%p,%p\012\000" )
.LC25:
	ASCII(.ascii	"line:%d! i > (RV9_MAX_SLC_PARAM_NUM - 2)\012\000" )
	.space	2
.LC26:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
