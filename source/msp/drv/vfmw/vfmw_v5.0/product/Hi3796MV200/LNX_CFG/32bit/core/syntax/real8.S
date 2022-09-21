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
	.file	"real8.c"
	.text
	.align	2
	.global	Real8_CB_GetBits
	.type	Real8_CB_GetBits, %function
Real8_CB_GetBits:
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
	.size	Real8_CB_GetBits, .-Real8_CB_GetBits
	.align	2
	.global	Real8_CB_Get1Bit
	.type	Real8_CB_Get1Bit, %function
Real8_CB_Get1Bit:
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
	.size	Real8_CB_Get1Bit, .-Real8_CB_Get1Bit
	.align	2
	.global	Real8_CB_GetVLCBits
	.type	Real8_CB_GetVLCBits, %function
Real8_CB_GetVLCBits:
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
	.size	Real8_CB_GetVLCBits, .-Real8_CB_GetVLCBits
	.align	2
	.global	Real8_GetImageBuffer
	.type	Real8_GetImageBuffer, %function
Real8_GetImageBuffer:
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
	ldr	r0, [r4, #1448]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #1052]
	blt	.L16
	mov	r1, r0
	ldr	r0, [r4, #1448]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L17
	ldr	r2, [r4, #1052]
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
	ldr	r1, [r4, #1048]
	ldr	r0, [r4, #1448]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #1044]
	mov	r5, #0
	ldr	r0, [r4, #1448]
	bl	FSP_ClearLogicFs
	str	r5, [r4, #1044]
	str	r5, [r4, #1048]
	ldr	r0, [r4, #1448]
	bl	FSP_GetNullLogicFs
	add	r1, r6, #54272
	add	r1, r1, #72
	str	r0, [r4, #1048]
	str	r0, [r4, #1044]
	strb	r5, [r7, #3191]
	ldr	r0, [r4, #1448]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L17:
	movw	r2, #511
	ldr	r1, .L18+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L19:
	.align	2
.L18:
	.word	.LC6
	.word	.LC7
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	Real8_GetImageBuffer, .-Real8_GetImageBuffer
	.align	2
	.global	Real8_ArrangeVHBMem
	.type	Real8_ArrangeVHBMem, %function
Real8_ArrangeVHBMem:
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
	ldr	r2, [r2, #104]
	mov	r5, r1
	ldr	r3, [r4, #100]
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
	ldr	r9, [r4, #96]
	mov	r7, #5
	ldr	r10, [r4, #92]
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
	ldr	r2, [r4, #96]
	ldr	r3, [r4, #92]
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
	ldr	r0, [r4, #1448]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	movne	r0, #0
	bne	.L47
	ldr	r1, [r5]
	sub	r3, fp, #68
	ldr	r0, [r4, #1448]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L49
	cmp	r0, #0
	addeq	r5, r5, #8192
	moveq	r3, #1
	moveq	r0, r3
	streqb	r3, [r5, #3188]
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
	ldr	r2, [r4, #96]
	ldr	r0, [r1, #684]
	ldr	r3, [r4, #92]
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
	ldr	r2, [r4, #96]
	ldr	r9, [r1, #684]
	ldr	r3, [r4, #92]
	cmp	r2, r9
	ldr	r10, [r1, #688]
	bhi	.L28
	cmp	r3, r10
	bhi	.L28
	add	r3, r5, #8192
	ldrb	r0, [r3, #3188]	@ zero_extendqisi2
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
	add	r0, r0, #72
	bl	ResetVoQueue
	b	.L40
.L51:
	.align	2
.L50:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC10
	.word	.LC8
	.word	.LC9
	UNWIND(.fnend)
	.size	Real8_ArrangeVHBMem, .-Real8_ArrangeVHBMem
	.align	2
	.global	Real8_CB_GetCPFMT
	.type	Real8_CB_GetCPFMT, %function
Real8_CB_GetCPFMT:
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
	str	r4, [r6, #96]
	bl	Real8_CB_Get1Bit
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
	str	r7, [r6, #92]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_CB_GetCPFMT, .-Real8_CB_GetCPFMT
	.align	2
	.global	Real8_CB_SetDimensions
	.type	Real8_CB_SetDimensions, %function
Real8_CB_SetDimensions:
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
	ldr	r3, [r0, #96]
	ldr	r2, [r0, #92]
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
	str	r3, [r0, #36]
	mul	r3, r3, r2
	str	r2, [r0, #32]
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
	str	r3, [r0, #40]
	ldmfd	sp, {fp, sp, pc}
.L77:
	cmp	r2, #1152
	bne	.L58
	mov	r2, #88
	mov	r3, #72
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L72:
	mov	r2, #4
	b	.L59
.L73:
	cmp	r2, #96
	bne	.L58
	mov	r2, #8
	mov	r3, #6
	str	r2, [r0, #36]
	mov	r2, #0
	str	r3, [r0, #32]
	b	.L59
.L74:
	cmp	r2, #144
	bne	.L58
	mov	r2, #11
	mov	r3, #9
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L68:
	mov	r2, #1
	b	.L59
.L75:
	cmp	r2, #288
	bne	.L58
	mov	r2, #22
	mov	r3, #18
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L69:
	mov	r2, #2
	b	.L59
.L76:
	cmp	r2, #576
	bne	.L58
	mov	r2, #44
	mov	r3, #36
	str	r2, [r0, #36]
	str	r3, [r0, #32]
.L70:
	mov	r2, #3
	b	.L59
.L79:
	.align	2
.L78:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real8_CB_SetDimensions, .-Real8_CB_SetDimensions
	.align	2
	.global	Real8_CB_GetPicSize
	.type	Real8_CB_GetPicSize, %function
Real8_CB_GetPicSize:
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
	ldr	ip, [r9, #32]
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
	bl	Real8_CB_Get1Bit
	cmp	r0, #0
	beq	.L81
	ldr	r3, [r9, #64]
	str	r3, [r8]
	ldr	r3, [r9, #68]
	str	r3, [r7]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L95:
	mov	r0, r4
	mov	r9, r9, asl #1
	bl	Real8_CB_Get1Bit
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
	.size	Real8_CB_GetPicSize, .-Real8_CB_GetPicSize
	.align	2
	.global	Real8_CB_FindNextSliceStartCode
	.type	Real8_CB_FindNextSliceStartCode, %function
Real8_CB_FindNextSliceStartCode:
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
	movgt	r4, #0
	bgt	.L101
	b	.L102
.L107:
	bl	BsSkip
	cmp	r4, r6
	beq	.L102
.L101:
	mov	r1, #17
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L107
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L102:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_CB_FindNextSliceStartCode, .-Real8_CB_FindNextSliceStartCode
	.align	2
	.global	Real8_CB_SearchBits_IgnoreOnly0
	.type	Real8_CB_SearchBits_IgnoreOnly0, %function
Real8_CB_SearchBits_IgnoreOnly0:
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
	beq	.L109
	ands	r5, r4, r6
	bne	.L109
	ldr	r3, .L115
	add	r10, r3, r10, lsl #2
	ldr	r10, [r10, #360]
	b	.L110
.L111:
	tst	r4, r6
	bne	.L109
.L110:
	mov	r0, r8
	and	r4, r10, r4, asl #1
	bl	Real8_CB_Get1Bit
	add	r5, r5, #1
	orr	r4, r0, r4
	cmp	r7, r4
	cmpne	r9, r5
	bhi	.L111
.L109:
	rsb	r0, r7, r4
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L116:
	.align	2
.L115:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real8_CB_SearchBits_IgnoreOnly0, .-Real8_CB_SearchBits_IgnoreOnly0
	.align	2
	.global	Real8_CB_SetRPRSizes
	.type	Real8_CB_SetRPRSizes, %function
Real8_CB_SetRPRSizes:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	ldr	lr, .L118
	sub	r3, fp, #28
	mov	r4, r0
	mov	r5, r1
	mov	r7, r2
	add	r6, r3, r1, lsl #2
	sub	ip, fp, #64
	ldmia	lr!, {r0, r1, r2, r3}
	str	r5, [r4, #24]
	str	r7, [r4, #20]
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	lr, [lr]
	stmia	ip!, {r0, r1, r2, r3}
	str	lr, [ip]
	ldr	r3, [r6, #-36]
	str	r3, [r4, #16]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L119:
	.align	2
.L118:
	.word	.LANCHOR0+460
	UNWIND(.fnend)
	.size	Real8_CB_SetRPRSizes, .-Real8_CB_SetRPRSizes
	.align	2
	.global	Real8_CB_GetSSC
	.type	Real8_CB_GetSSC, %function
Real8_CB_GetSSC:
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
	beq	.L122
	bl	Real8_CB_FindNextSliceStartCode
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L122:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_CB_GetSSC, .-Real8_CB_GetSSC
	.align	2
	.global	Real8_CB_GetSliceHeader
	.type	Real8_CB_GetSliceHeader, %function
Real8_CB_GetSliceHeader:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r4, [fp, #8]
	mov	r5, r2
	mov	r7, r3
	mov	r6, r0
	ldr	ip, [r4, #84]
	cmp	ip, #1
	beq	.L157
	cmp	r1, #0
	beq	.L158
	mov	r2, #0
	str	r2, [r5]
	ldr	r2, [fp, #4]
	mvn	r3, #0
	mov	r0, #1
	str	r3, [r2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L157:
	cmp	r1, #0
	bne	.L126
	mov	r1, #3
	ldr	r9, [r4, #48]
	bl	BsShow
	mov	r1, #3
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	cmp	r8, #7
	bhi	.L129
	ldr	r3, .L161
	add	r8, r3, r8, lsl #2
	ldr	r3, [r8, #496]
	cmp	r3, #2
	bhi	.L129
	cmn	r9, #1
	mov	r1, #2
	mov	r0, r6
	movne	r9, #0
	moveq	r9, #1
	cmp	r9, #0
	bne	.L159
	bl	BsShow
	mov	r1, #2
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #44]
	cmp	r3, r8
	bne	.L129
.L131:
	mov	r0, r6
	bl	Real8_CB_Get1Bit
	cmp	r0, #0
	bne	.L129
	mov	r1, #5
	mov	r0, r6
	bl	BsShow
	mov	r1, #5
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	uxtb	r0, r8
	cmp	r0, #31
	strb	r0, [r4, #14]
	bhi	.L129
	mov	r1, #1
	mov	r0, r6
	bl	BsShow
	mov	r1, #1
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	adds	r8, r8, #0
	mov	r1, #13
	mov	r0, r6
	movne	r8, #1
	cmp	r9, #0
	strb	r8, [r4, #13]
	beq	.L132
	bl	BsShow
	mov	r1, #13
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r8, [r4, #16]
	str	r9, [r4, #52]
	cmp	r8, #0
	beq	.L150
	mov	r1, r8
	mov	r0, r6
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #20]
	str	r9, [r4, #64]
	cmp	r3, #0
	beq	.L129
	add	r1, r3, r9, lsl #3
	ldr	r2, [r3, r9, asl #3]
	mov	r0, r4
	ldr	r3, [r1, #4]
	str	r2, [r4, #68]
	str	r2, [r4, #96]
	str	r3, [r4, #72]
	str	r3, [r4, #92]
	bl	Real8_CB_SetDimensions
.L150:
	ldr	r8, [r4, #40]
	mov	r0, r6
	mov	r1, r8
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	mov	r1, #1
	str	r9, [r4, #48]
	mov	r0, r6
	bl	BsShow
	mov	r1, #1
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	strb	r8, [r4, #12]
.L126:
	ldr	r2, [r4, #48]
	mov	r3, #0
	ldr	r1, [fp, #4]
	mov	r0, #1
	str	r2, [r5]
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	str	r2, [r1]
	str	r3, [r7]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L158:
	bl	Real8_CB_Get1Bit
	cmp	r0, #1
	beq	.L160
.L129:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L160:
	ldr	r8, [r4, #40]
	mov	r0, r6
	mov	r1, r8
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	str	r9, [r5]
	ldr	r3, [r4, #40]
	cmp	r3, #11
	bls	.L142
	mov	r0, r6
	bl	Real8_CB_Get1Bit
	cmp	r0, #1
	bne	.L129
.L142:
	mov	r1, #5
	mov	r0, r6
	bl	BsShow
	mov	r1, #5
	mov	r4, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [fp, #4]
	cmp	r4, #31
	str	r4, [r3]
	bgt	.L129
	mov	r0, r6
	bl	Real8_CB_Get1Bit
	cmp	r0, #1
	mov	r4, r0
	bne	.L129
	mov	r1, #2
	mov	r0, r6
	bl	BsShow
	mov	r1, #2
	mov	r5, r0
	mov	r0, r6
	bl	BsSkip
	str	r5, [r7]
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L159:
	bl	BsShow
	mov	r1, #2
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	str	r8, [r4, #44]
	b	.L131
.L132:
	bl	BsShow
	mov	r1, #13
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #52]
	cmp	r3, r8
	bne	.L129
	ldr	r8, [r4, #16]
	cmp	r8, #0
	beq	.L154
	mov	r1, r8
	mov	r0, r6
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	ldr	r3, [r4, #64]
	cmp	r3, r9
	bne	.L129
.L154:
	ldr	r8, [r4, #40]
	mov	r0, r6
	mov	r1, r8
	bl	BsShow
	mov	r1, r8
	mov	r9, r0
	mov	r0, r6
	bl	BsSkip
	mov	r1, #1
	str	r9, [r4, #48]
	mov	r0, r6
	bl	BsShow
	mov	r1, #1
	mov	r8, r0
	mov	r0, r6
	bl	BsSkip
	ldrb	r3, [r4, #12]	@ zero_extendqisi2
	cmp	r3, r8
	bne	.L129
	b	.L126
.L162:
	.align	2
.L161:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	Real8_CB_GetSliceHeader, .-Real8_CB_GetSliceHeader
	.align	2
	.global	Real8_CB_GetPictureHeader
	.type	Real8_CB_GetPictureHeader, %function
Real8_CB_GetPictureHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, [r1, #84]
	mov	r4, r1
	mov	r5, r0
	cmp	r3, #1
	beq	.L189
	ldr	r3, .L192
	mov	r2, #148
	mov	r1, #0
	mov	r0, r4
	ldr	r3, [r3, #48]
	blx	r3
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	mov	r1, #24
	mov	r6, r0
	mov	r0, r5
	bl	BsSkip
	cmp	r6, #1
	bne	.L182
	mov	r0, r5
	sub	r1, fp, #32
	bl	Real8_CB_GetVLCBits
	cmp	r0, #30
	bls	.L182
	ldr	r3, [fp, #-32]
	ands	r2, r3, #1
	bne	.L182
	tst	r3, #2
	mov	r0, r5
	strne	r2, [r4, #96]
	moveq	r1, #176
	moveq	r2, #144
	streq	r1, [r4, #96]
	sub	r1, fp, #32
	str	r2, [r4, #92]
	ubfx	r2, r3, #2, #5
	ubfx	r3, r3, #7, #8
	str	r2, [r4, #128]
	str	r3, [r4, #116]
	bl	Real8_CB_GetVLCBits
	cmp	r0, #1
	streq	r0, [r4, #88]
	beq	.L177
	cmp	r0, #3
	beq	.L190
	cmp	r0, #5
	bne	.L182
	ldr	r3, [fp, #-32]
	cmp	r3, #0
	bne	.L182
	mov	r3, #2
	str	r3, [r4, #88]
.L177:
	ldr	r3, [r4, #96]
	cmp	r3, #0
	beq	.L191
.L179:
	sub	r3, r3, #48
	movw	r2, #8144
	cmp	r3, r2
	bhi	.L182
.L188:
	ldr	r3, [r4, #92]
	sub	r3, r3, #48
	cmp	r3, r2
	bhi	.L182
	mov	r0, r4
	bl	Real8_CB_SetDimensions
	mov	r0, #1
.L165:
	ldr	r3, [r4, #96]
	ldr	r2, [r4, #92]
	add	r3, r3, #15
	add	r2, r2, #15
	mov	r3, r3, lsr #4
	str	r3, [r4, #104]
	mov	r2, r2, lsr #4
	str	r2, [r4, #100]
	mul	r3, r3, r2
	str	r3, [r4, #108]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L190:
	ldr	r3, [fp, #-32]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r4, #88]
	beq	.L177
.L182:
	mvn	r0, #1
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L189:
	str	r1, [sp, #4]
	mvn	r2, #0
	sub	r3, fp, #32
	str	r2, [r1, #48]
	str	r3, [sp]
	sub	r2, fp, #36
	sub	r3, fp, #40
	mov	r1, #0
	bl	Real8_CB_GetSliceHeader
	cmp	r0, #1
	mvnne	r0, #1
	bne	.L165
	ldr	r3, [r4, #44]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L166
.L168:
	.word	.L167
	.word	.L169
	.word	.L170
	.word	.L171
.L191:
	mov	r0, r5
	mov	r1, r4
	bl	Real8_CB_GetCPFMT
	cmp	r0, #0
	beq	.L182
	ldr	r3, [r4, #96]
	b	.L179
.L169:
	mov	r3, #0
	str	r3, [r4, #88]
	str	r3, [r4, #28]
.L166:
	ldr	r3, [r4, #96]
	add	r0, r4, #52
	movw	r2, #8144
	ldrb	r5, [r4, #12]	@ zero_extendqisi2
	sub	r3, r3, #48
	ldrb	lr, [r4, #13]	@ zero_extendqisi2
	cmp	r3, r2
	ldrb	ip, [r4, #14]	@ zero_extendqisi2
	ldmia	r0, {r0, r1, r3}
	str	r5, [r4, #120]
	str	lr, [r4, #124]
	str	ip, [r4, #128]
	str	r0, [r4, #116]
	str	r1, [r4, #136]
	str	r3, [r4, #140]
	bls	.L188
	b	.L182
.L171:
	mov	r3, #2
	str	r3, [r4, #88]
	b	.L166
.L170:
	mov	r3, #1
	str	r3, [r4, #88]
	b	.L166
.L167:
	mov	r2, #0
	mov	r3, #1
	str	r2, [r4, #88]
	str	r3, [r4, #28]
	b	.L166
.L193:
	.align	2
.L192:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	Real8_CB_GetPictureHeader, .-Real8_CB_GetPictureHeader
	.align	2
	.global	Real8_SetImgFormat
	.type	Real8_SetImgFormat, %function
Real8_SetImgFormat:
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
	ldr	r1, [r3, #1052]
	ldr	r0, [r3, #1448]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r2, r5, #49152
	ldrb	lr, [r4, #64]	@ zero_extendqisi2
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	mov	r1, #5
	ldr	ip, [r2, #3864]
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
	ldr	r3, [r2, #3872]
	str	r3, [r4, #68]
	ldr	r3, [r2, #3868]
	str	r3, [r4, #72]
	bl	SetAspectRatio
	ldr	r3, [r5]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L200
.L196:
	mov	r3, #8
	mov	r2, #1
	mov	r1, #0
	str	r3, [r4, #296]
	str	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	strb	r1, [r4, #284]
	strb	r2, [r4, #291]
	strb	r2, [r4, #289]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L200:
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
	b	.L196
	UNWIND(.fnend)
	.size	Real8_SetImgFormat, .-Real8_SetImgFormat
	.align	2
	.global	RV8_RecordVFMWState
	.type	RV8_RecordVFMWState, %function
RV8_RecordVFMWState:
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
	.size	RV8_RecordVFMWState, .-RV8_RecordVFMWState
	.align	2
	.global	Real8_WriteSliceMsg
	.type	Real8_WriteSliceMsg, %function
Real8_WriteSliceMsg:
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
	mov	r3, #44
	add	r2, r0, #49152
	mla	r3, r3, r1, r0
	ldr	ip, [r2, #3952]
	add	r1, r1, #1
	str	ip, [r3, #104]
	ldr	ip, [r2, #3944]
	str	ip, [r3, #112]
	ldr	ip, [r2, #3948]
	str	ip, [r3, #120]
	ldr	ip, [r2, #3964]
	str	ip, [r3, #108]
	ldr	ip, [r2, #3956]
	str	ip, [r3, #116]
	ldr	ip, [r2, #3960]
	str	ip, [r3, #124]
	ldr	ip, [r2, #3932]
	str	ip, [r3, #128]
	ldr	ip, [r2, #3928]
	str	ip, [r3, #132]
	ldr	ip, [r2, #3924]
	str	ip, [r3, #136]
	ldr	r2, [r2, #3936]
	str	r2, [r3, #140]
	str	r1, [r0, #44]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_WriteSliceMsg, .-Real8_WriteSliceMsg
	.align	2
	.global	Real8_WritePicMsg
	.type	Real8_WritePicMsg, %function
Real8_WritePicMsg:
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
	ldr	r1, [r3, #3864]
	cmp	r1, #2
	strb	r1, [r0, #20]
	ldr	r1, [r3, #3880]
	str	r1, [r0, #12]
	ldr	r1, [r3, #3876]
	str	r1, [r0, #16]
	ldr	r1, [r2, #968]
	str	r1, [r0, #24]
	ldr	r2, [r2, #972]
	str	r2, [r0, #28]
	ldr	r2, [r3, #3904]
	str	r2, [r0, #32]
	ldr	r1, [r3, #3968]
	str	r1, [r0, #36]
	ldr	r1, [r3, #3972]
	str	r1, [r0, #40]
	strne	r2, [r3, #3968]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_WritePicMsg, .-Real8_WritePicMsg
	.align	2
	.global	Real8_WriteReg
	.type	Real8_WriteReg, %function
Real8_WriteReg:
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
	str	r1, [r0, #48]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_WriteReg, .-Real8_WriteReg
	.align	2
	.global	Real8_ModifySliceMsg
	.type	Real8_ModifySliceMsg, %function
Real8_ModifySliceMsg:
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
	ldr	r2, [r0, #140]
	ldr	r3, [r0, #12]
	cmp	r2, #0
	ldr	ip, [r0, #16]
	bne	.L213
	mul	ip, r3, ip
	ldr	r5, [r0, #44]
	cmp	r5, #2
	sub	ip, ip, #1
	bls	.L212
	ldr	r3, [r0, #184]
	sub	lr, r5, #1
	cmp	r3, #0
	cmpgt	ip, r3
	ble	.L213
	mov	r2, r0
	mov	r3, #1
	b	.L214
.L215:
	ldr	r1, [r2, #228]
	add	r2, r2, #44
	cmp	ip, r1
	cmpgt	r1, #0
	ble	.L213
.L214:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L215
.L212:
	cmp	r5, #1
	bls	.L216
	sub	r4, r5, #1
	mov	r3, r0
	mov	r2, #0
	b	.L217
.L218:
	ldr	lr, [r3, #140]
	add	r3, r3, #44
	add	r2, r2, #1
	ldr	r1, [r3, #140]
	cmp	lr, r1
	bge	.L213
.L217:
	cmp	r2, r4
	bne	.L218
	mov	r3, #44
	mla	r2, r3, r2, r0
	ldr	r3, [r2, #140]
	cmp	ip, r3
	cmpge	r3, #0
	ble	.L213
.L216:
	cmp	r5, #0
	beq	.L219
	sub	r7, r5, #1
	mov	r6, r0
	mov	lr, r0
	mov	r4, #0
	b	.L222
.L237:
	cmp	r4, r5
	beq	.L236
.L222:
	cmp	r4, r7
	streq	ip, [lr, #144]
	add	r4, r4, #1
	add	lr, lr, #44
	ldrne	r3, [lr, #140]
	moveq	r1, ip
	subne	r1, r3, #1
	ldr	r3, [lr, #96]
	strne	r1, [lr, #100]
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
	beq	.L237
.L213:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L236:
	ldr	r2, [r0, #104]
	mov	r1, r2
	b	.L225
.L238:
	ldr	r1, [r6, #104]
.L225:
	cmp	r2, r1
	ldr	ip, [r6, #108]
	add	r3, r3, #1
	movcs	r2, r1
	cmp	ip, r2
	bcs	.L223
	ldr	r1, [r6, #124]
	cmp	r1, #0
	movne	r2, ip
.L223:
	cmp	r5, r3
	add	r6, r6, #44
	bne	.L238
	bic	r2, r2, #15
	ldr	lr, [r0, #44]
	str	r2, [r0, #52]
	mov	r3, r0
	mov	ip, #0
	b	.L229
.L239:
	ldr	r4, [r3, #112]
	rsb	r2, r2, r1
	and	r1, r4, #7
	add	r2, r2, r4, lsr #3
	and	r4, r2, #15
	bic	r2, r2, #15
	str	r2, [r3, #104]
	add	r2, r1, r4, lsl #3
	str	r2, [r3, #112]
.L227:
	add	ip, ip, #1
	add	r3, r3, #44
	cmp	lr, ip
	bls	.L228
	ldr	r2, [r0, #52]
.L229:
	ldr	r1, [r3, #108]
	cmp	r1, #0
	rsb	r4, r2, r1
	ldr	r1, [r3, #104]
	beq	.L239
	ldr	r5, [r3, #112]
	rsb	r2, r2, r1
	ldr	r7, [r3, #116]
	and	r6, r5, #7
	add	r2, r2, r5, lsr #3
	and	r5, r7, #7
	add	r1, r4, r7, lsr #3
	and	r4, r2, #15
	and	r7, r1, #15
	bic	r2, r2, #15
	add	r4, r6, r4, lsl #3
	str	r2, [r3, #104]
	bic	r1, r1, #15
	add	r2, r5, r7, lsl #3
	str	r4, [r3, #112]
	str	r2, [r3, #116]
	str	r1, [r3, #108]
	b	.L227
.L219:
	ldr	r3, [r0, #104]
	bic	r3, r3, #15
	str	r3, [r0, #52]
.L228:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	Real8_ModifySliceMsg, .-Real8_ModifySliceMsg
	.align	2
	.global	REAL8DEC_Init
	.type	REAL8DEC_Init, %function
REAL8DEC_Init:
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
	ldr	r3, .L244
	add	r6, r0, #53248
	mov	r7, r1
	movw	r2, #54712
	ldr	r8, [r6, #1440]
	mov	r1, #0
	ldr	r3, [r3, #48]
	mov	r4, r0
	mov	r5, r1
	blx	r3
	add	r0, r4, #54272
	str	r8, [r6, #1440]
	add	r0, r0, #72
	bl	ResetVoQueue
	add	r3, r4, #49152
	str	r7, [r4]
	mov	r2, #15
	str	r2, [r3, #3968]
	add	ip, r4, #8192
	str	r2, [r3, #3972]
	mov	r1, #8192
	ldr	lr, [r7, #8]
	mov	r2, #1
	strb	r5, [ip, #3188]
	mov	r0, r4
	strb	lr, [ip, #3186]
	str	r1, [r3, #3888]
	str	r2, [r3, #3860]
	strb	r2, [r3, #3784]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r6, #1448]
	mov	r0, r5
	beq	.L243
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L243:
	ldr	r1, .L244+4
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L245:
	.align	2
.L244:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC11
	UNWIND(.fnend)
	.size	REAL8DEC_Init, .-REAL8DEC_Init
	.align	2
	.global	REAL8DEC_Destroy
	.type	REAL8DEC_Destroy, %function
REAL8DEC_Destroy:
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
	ldr	r1, .L247
	mov	r0, #2
	ldr	r2, [r3, #944]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L248:
	.align	2
.L247:
	.word	.LC12
	UNWIND(.fnend)
	.size	REAL8DEC_Destroy, .-REAL8DEC_Destroy
	.global	__aeabi_idiv
	.align	2
	.global	REAL8DEC_Decode
	.type	REAL8DEC_Decode, %function
REAL8DEC_Decode:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 304
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #324)
	sub	sp, sp, #324
	mov	r2, #148
	mov	r10, r0
	mov	r4, r1
	add	r5, r10, #49152
	mov	r1, #0
	sub	r0, fp, #192
	bl	memset
	mov	r2, #64
	mov	r1, #0
	sub	r0, fp, #256
	bl	memset
	ldr	r2, [r5, #3844]
	ldr	r3, [r5, #3848]
	cmp	r4, #0
	mov	r0, #1
	mov	r1, #8192
	add	ip, r10, #8
	str	r2, [r5, #3852]
	str	ip, [fp, #-304]
	str	r2, [fp, #-116]
	str	r2, [fp, #-124]
	str	r3, [r5, #3856]
	str	r3, [fp, #-112]
	str	r3, [fp, #-120]
	str	r0, [r5, #3860]
	str	r0, [fp, #-108]
	str	r1, [r5, #3888]
	str	r1, [fp, #-80]
	beq	.L379
	ldr	r3, .L401
	add	r6, r10, #53248
	add	ip, r10, #8192
	movw	r2, #11360
	mov	r1, #0
	ldr	r0, [fp, #-304]
	ldr	r3, [r3, #48]
	mov	r8, ip
	mov	r7, r1
	str	ip, [fp, #-308]
	blx	r3
	str	r7, [r6, #908]
	ldr	r3, [r4, #16]
	str	r3, [r6, #928]
	ldr	r3, [r4, #12]
	str	r3, [r6, #912]
	ldr	r3, [r4]
	str	r3, [r8, #3176]
	ldr	r2, [r4, #16]
	str	r2, [r6, #916]
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	strb	r3, [r8, #3184]
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L252
	ldr	r3, [r4, #92]
	str	r3, [r6, #920]
	ldr	r3, [r4, #80]
	str	r3, [r8, #3180]
	ldr	r3, [r4, #96]
	str	r3, [r6, #924]
	ldrb	r3, [r4, #86]	@ zero_extendqisi2
	strb	r3, [r8, #3185]
	ldrb	r3, [r4, #86]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L380
.L253:
	movw	r3, #65460
	sub	r1, r2, #75
	movt	r3, 47
	cmp	r1, r3
	bhi	.L375
	ldr	r8, [fp, #-308]
	ldr	r1, [r8, #3176]
	cmp	r1, #0
	beq	.L375
	add	r4, r10, #54272
	add	r4, r4, #40
	mov	r0, r4
	bl	BsInit
	mov	r1, #8
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	mov	r7, r0
	str	r0, [fp, #-312]
	mov	r0, r4
	bl	BsSkip
	cmp	r7, #8
	bhi	.L375
	sub	r7, fp, #260
.L256:
	mov	r1, #32
	mov	r0, r4
	bl	BsShow
	mov	r1, #32
	mov	r9, r0
	mov	r0, r4
	bl	BsSkip
	sub	r3, fp, #196
	rev	r9, r9
	str	r9, [r7, #4]!
	cmp	r7, r3
	bne	.L256
	mov	r1, #8
	mov	r0, r4
	str	r8, [fp, #-308]
	bl	BsShow
	mov	r1, #8
	mov	r7, r0
	mov	r0, r4
	bl	BsSkip
	cmp	r7, #255
	add	r0, r7, #1
	str	r0, [r5, #3976]
	bhi	.L375
	cmp	r0, #0
	beq	.L257
	add	r9, r10, #52992
	movw	r3, #65535
	add	r9, r9, #136
	movt	r3, 47
	str	r6, [fp, #-316]
	mov	r7, #0
	mov	r6, r9
	mov	r9, r3
	b	.L258
.L382:
	ldr	r0, [r5, #3976]
	cmp	r0, r7
	bls	.L381
.L258:
	mov	r1, #32
	mov	r0, r4
	bl	BsSkip
	mov	r1, #32
	mov	r0, r4
	add	r7, r7, #1
	bl	BsShow
	mov	r1, #32
	mov	r8, r0
	mov	r0, r4
	bl	BsSkip
	rev	r0, r8
	cmp	r0, r9
	str	r0, [r6, #4]!
	ble	.L382
.L375:
	mov	r7, #0
.L364:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L380:
	ldr	r1, [r4, #20]
	ldr	r0, [r6, #1448]
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r4, #100]
	ldr	r0, [r6, #1448]
	bl	SM_ReleaseStreamSeg
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L252:
	ldr	r3, [fp, #-308]
	str	r7, [r6, #920]
	str	r7, [r3, #3180]
	str	r7, [r6, #924]
	strb	r7, [r3, #3185]
	b	.L253
.L379:
	add	r3, r10, #53248
	ldr	r1, .L401+4
	mov	r7, r4
	ldr	r2, [r3, #944]
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L381:
	ldr	r6, [fp, #-316]
.L257:
	add	r3, r10, #52992
	sub	lr, r0, #1
	add	r3, r3, #140
	mov	r2, #0
	ldr	r8, [fp, #-308]
	b	.L259
.L260:
	ldr	ip, [r3, #4]!
	ldr	r1, [r3, #-4]
	cmp	ip, r1
	ble	.L375
.L259:
	cmp	r2, lr
	add	r2, r2, #1
	bne	.L260
	ldr	r2, [r5, #3980]
	mov	r0, r0, asl #3
	add	r1, r0, #66
	movw	r3, #65461
	add	r0, r1, r2
	cmp	r1, #3145728
	sub	r9, r0, #74
	movt	r3, 47
	movlt	r2, #0
	movge	r2, #1
	cmp	r9, r3
	movls	r9, r2
	orrhi	r9, r2, #1
	str	r8, [fp, #-308]
	cmp	r9, #0
	str	r1, [fp, #-316]
	str	r0, [fp, #-320]
	bne	.L375
	ldr	r2, [r6, #916]
	mov	r3, r0
	rsb	r2, r0, r2
	cmp	r2, #0
	ble	.L375
	ldr	r1, [r8, #3176]
	mov	r0, r4
	sub	r8, fp, #256
	add	r1, r1, r3
	bl	BsInit
	ldr	r3, [fp, #-312]
	ldr	lr, .L401+8
	sub	r2, fp, #44
	sub	ip, fp, #292
	str	r8, [fp, #-172]
	add	r7, r2, r3, lsl #2
	str	r3, [fp, #-168]
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	ldr	lr, [lr]
	stmia	ip!, {r0, r1, r2, r3}
	sub	r1, fp, #192
	str	lr, [ip]
	mov	r0, r4
	ldr	r3, [r7, #-248]
	str	r3, [fp, #-176]
	bl	Real8_CB_GetPictureHeader
	cmp	r0, #1
	mov	r7, r0
	bne	.L383
	ldr	r3, [fp, #-308]
	ldrb	r3, [r3, #3188]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L262
	ldr	r9, .L401+12
	ldr	ip, [r9]
	cmp	ip, #0
	beq	.L263
	ldr	lr, [r5, #3880]
	sub	r2, fp, #292
	ldr	r1, [r5, #3876]
	mov	r3, #8
	ldr	r0, [fp, #-88]
	strh	lr, [r2]	@ movhi
	sub	lr, fp, #288
	sub	lr, lr, #2
	strh	r1, [lr]	@ movhi
	sub	lr, fp, #288
	mov	r1, #2
	strh	r0, [lr]	@ movhi
	sub	r0, fp, #284
	ldrh	lr, [fp, #-92]
	sub	r0, r0, #2
	strh	lr, [r0]	@ movhi
	ldr	r0, [r6, #1448]
	blx	ip
.L263:
	ldr	r0, [r6, #1448]
	bl	FSP_GetFspType
	subs	ip, r0, #0
	bne	.L264
	sub	r3, fp, #292
	sub	r2, fp, #296
	sub	r1, fp, #300
	ldr	r0, [r6, #1448]
	str	ip, [fp, #-300]
	str	ip, [fp, #-296]
	str	ip, [fp, #-292]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r10]
	ldr	r2, [r3, #724]
	cmp	r2, #1
	beq	.L384
.L264:
	mov	r2, #1
	ldr	r1, [r6, #1048]
	ldr	r0, [r6, #1448]
	add	r9, r10, #54272
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r6, #1044]
	add	r9, r9, #72
	ldr	r0, [r6, #1448]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r6, #1448]
	str	r3, [r6, #1044]
	str	r3, [r6, #1048]
	str	r3, [fp, #-312]
	bl	FSP_GetNullLogicFs
	ldr	r3, [fp, #-312]
	mov	r1, r9
	ldr	r2, [fp, #-308]
	str	r0, [r6, #1048]
	str	r0, [r6, #1044]
	strb	r3, [r2, #3191]
	ldr	r0, [r6, #1448]
	bl	FSP_ClearNotInVoQueue
	ldr	r2, [fp, #-88]
	ldr	r3, [fp, #-92]
	cmp	r2, #512
	bhi	.L271
	cmp	r3, #512
	bhi	.L271
	ldr	r3, [r10]
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L273
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L385
.L273:
	ldr	r0, [r6, #1448]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L370
.L275:
	ldr	r3, [fp, #-92]
	mov	r0, #1
	ldr	r2, [fp, #-88]
	ldr	r1, .L401+16
	bl	dprint_vfmw
	sub	r2, fp, #192
	mov	r1, r10
	mov	r0, #6
	bl	Real8_ArrangeVHBMem
	subs	r3, r0, #0
	beq	.L386
.L262:
	add	r3, r10, #52736
	sub	r1, fp, #192
	mov	r2, r3
	ldr	r3, .L401
	add	r2, r2, #192
	str	r2, [fp, #-328]
	ldr	r3, [r3, #52]
	mov	r0, r2
	mov	r2, #148
	blx	r3
	ldr	r3, [r10]
	ldr	r2, [fp, #-308]
	mov	r0, r10
	ldr	r3, [r3, #8]
	strb	r3, [r2, #3186]
	bl	Real8_GetImageBuffer
	subs	r3, r0, #0
	beq	.L387
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L278
	ldr	r2, [r10]
	add	r3, ip, #592
	add	lr, ip, #608
	ldr	r1, .L401+20
	mov	r0, #29
	ldrd	r8, [r2, #56]
	strd	r8, [r3, #-8]
	ldr	r2, [r10]
	ldrd	r8, [r2, #72]
	strd	r8, [r3]
	ldr	r2, [r10]
	ldrd	r8, [r2, #88]
	strd	r8, [lr, #-8]
	mvn	r8, #0
	ldr	r2, [r10]
	mvn	r9, #0
	ldr	r2, [r2, #104]
	str	r2, [ip]
	ldr	r2, [r10]
	ldr	r2, [r2, #108]
	str	r2, [ip, #4]
	ldr	r2, [r10]
	ldr	r2, [r2, #112]
	str	r2, [ip, #8]
	ldr	r2, [r10]
	ldr	r2, [r2, #128]
	str	r2, [ip, #12]
	ldr	r2, [r10]
	strd	r8, [r2, #56]
	ldrd	r8, [r3]
	ldrd	r2, [r3, #-8]
	strd	r8, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #3864]
	cmp	r3, #2
	beq	.L388
	cmp	r3, #1
	ldr	r3, [fp, #-308]
	ldrb	r3, [r3, #3191]	@ zero_extendqisi2
	beq	.L389
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #1
.L282:
	ldr	r2, [fp, #-308]
	strb	r3, [r2, #3191]
	ldr	r2, [r6, #1044]
	ldr	r3, [r6, #1048]
	cmp	r2, r3
	beq	.L283
	ldr	r1, .L401+24
	mov	r0, #13
	bl	dprint_vfmw
	mov	r2, #0
	ldr	r1, [r6, #1044]
	ldr	r0, [r6, #1448]
	bl	FSP_SetRef
.L283:
	ldr	r3, [r6, #1048]
	mov	r2, #1
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	str	r3, [r6, #1044]
	str	r1, [r6, #1048]
	bl	FSP_SetRef
	ldr	r1, [r6, #1044]
	ldr	r0, [r6, #1448]
	bl	FSP_RemovePmv
	ldr	r2, [r6, #1052]
	ldr	r1, .L401+28
	mov	r0, #13
	bl	dprint_vfmw
	ldr	r3, [fp, #-308]
	ldrb	r3, [r3, #3186]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L285
	ldr	r3, [r5, #3864]
	cmp	r3, #0
	bne	.L390
.L371:
	str	r3, [r6, #1060]
.L285:
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #1044]
	str	r0, [fp, #-312]
	ldr	r0, [r6, #1448]
	bl	FSP_GetLogicFs
	ldr	r1, [r6, #1048]
	mov	r9, r0
	ldr	r0, [r6, #1448]
	bl	FSP_GetLogicFs
	ldr	ip, [fp, #-312]
	cmp	ip, #0
	cmpne	r9, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	str	r0, [fp, #-324]
	cmp	r3, #0
	bne	.L391
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L292
	ldr	r2, [ip, #32]
	cmp	r2, #0
	beq	.L292
	ldr	r2, [fp, #-324]
	mov	r0, #13
	ldr	r1, .L401+32
	ldr	r2, [r2, #28]
	cmp	r2, #0
	ldrne	r3, [r2, #8]
	ldreq	r3, [r3, #8]
	str	r3, [fp, #-312]
	ldr	r3, [fp, #-312]
	str	r3, [r10, #56]
	ldr	r3, [r9, #28]
	cmp	r3, #0
	ldreq	r3, [ip, #28]
	ldr	lr, [r3, #8]
	str	ip, [fp, #-336]
	str	lr, [r10, #60]
	ldr	r3, [ip, #28]
	ldr	r2, [r3, #8]
	str	r2, [r10, #64]
	ldr	r3, [ip, #8]
	str	r3, [r10, #76]
	mov	r8, r3
	ldr	r3, [fp, #-324]
	ldr	r3, [r3, #8]
	str	r3, [fp, #-332]
	str	r3, [r10, #80]
	ldr	r3, [ip, #32]
	ldr	ip, [fp, #-332]
	ldr	r3, [r3, #8]
	str	ip, [sp, #12]
	ldr	ip, [fp, #-312]
	str	r8, [sp, #8]
	str	r3, [r10, #68]
	str	ip, [sp, #4]
	str	lr, [sp]
	bl	dprint_vfmw
	ldr	ip, [fp, #-336]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #24]
	str	r3, [r10, #72]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #60]
	str	r3, [r10, #92]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #44]
	str	r3, [r10, #96]
	ldr	r3, [ip, #32]
	ldr	r3, [r3, #48]
	str	r3, [r10, #100]
	ldr	r3, [r5, #3864]
	cmp	r3, #2
	beq	.L392
.L298:
	ldr	r3, [r5, #3892]
	mov	r0, r4
	str	r3, [ip, #16]
	ldr	r3, [r5, #3864]
	ldr	r2, [r5, #3904]
	cmp	r3, #2
	strb	r3, [r10, #20]
	ldr	r3, [r5, #3880]
	str	r2, [fp, #-324]
	str	r3, [r10, #12]
	ldr	r3, [r5, #3876]
	str	r3, [r10, #16]
	ldr	r3, [r6, #968]
	str	r3, [r10, #24]
	ldr	r3, [r6, #972]
	str	r2, [r10, #32]
	str	r3, [r10, #28]
	ldr	r3, [r5, #3968]
	str	r3, [r10, #36]
	ldr	r3, [r5, #3972]
	str	r3, [r10, #40]
	strne	r2, [r5, #3968]
	bl	BsPos
	ldr	r3, [r5, #3976]
	ands	r0, r0, #-2147483641
	submi	r0, r0, #1
	mvnmi	r0, r0, asl #29
	mvnmi	r0, r0, lsr #29
	addmi	r0, r0, #1
	cmp	r3, #1
	str	r0, [r5, #3944]
	ldreq	r1, [fp, #-316]
	moveq	r0, r4
	ldreq	r3, [r6, #916]
	movne	r0, r4
	ldreq	r2, [r5, #3980]
	ldrne	r2, [r5, #3980]
	rsbeq	r3, r1, r3
	ldrne	r3, [r5, #3984]
	rsb	r3, r2, r3
	mov	r9, r3, asl #3
	bl	BsPos
	ldr	r2, [fp, #-320]
	rsb	r0, r0, r9
	str	r0, [r5, #3948]
	ldr	r3, [r6, #912]
	mov	r0, r4
	add	r9, r2, r3
	bl	BsPos
	ldr	r2, [r5, #3908]
	mov	r1, #1
	ldr	ip, [r5, #3900]
	ldr	lr, [fp, #-324]
	str	r2, [r5, #3928]
	str	ip, [r5, #3932]
	str	lr, [r5, #3924]
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	mov	r3, #0
	add	r0, r9, r0, asr #3
	str	r3, [r5, #3956]
	str	r0, [r5, #3952]
	str	r3, [r5, #3960]
	str	r3, [r5, #3964]
	str	r3, [r5, #3936]
	str	r0, [r10, #104]
	ldr	r0, [r5, #3944]
	str	r0, [r10, #112]
	ldr	r0, [r5, #3948]
	str	ip, [r10, #128]
	str	r3, [r10, #108]
	str	r0, [r10, #120]
	str	r3, [r10, #116]
	str	r3, [r10, #124]
	str	r2, [r10, #132]
	str	r3, [r10, #140]
	str	lr, [r10, #136]
	str	r1, [r10, #44]
	ldr	r2, [r5, #3976]
	cmp	r2, r1
	bls	.L326
	ldr	r9, [r5, #3984]
	movw	r0, #65535
	ldr	r2, [fp, #-316]
	movt	r0, 47
	add	r9, r2, r9
	cmp	r9, r0
	bgt	.L312
	cmp	r9, #73
	ble	.L312
	ldr	r2, [r6, #916]
	rsb	r2, r9, r2
	cmp	r2, #0
	ble	.L312
	add	ip, r10, #52992
	str	r7, [fp, #-340]
	add	ip, ip, #144
	str	r3, [fp, #-336]
	str	ip, [fp, #-312]
	mov	r7, r1
	str	r0, [fp, #-332]
	str	r1, [fp, #-320]
	ldr	r8, [fp, #-308]
	b	.L315
.L316:
	ldr	r3, [r5, #3976]
	add	r7, r7, #1
	cmp	r3, r7
	bls	.L393
	ldr	r3, [fp, #-312]
	ldr	r9, [r3, #4]!
	str	r3, [fp, #-312]
	ldr	r3, [fp, #-316]
	add	r9, r3, r9
	ldr	r3, [fp, #-332]
	cmp	r9, r3
	bgt	.L312
	cmp	r9, #73
	ble	.L312
	ldr	r2, [r6, #916]
	rsb	r2, r9, r2
	cmp	r2, #0
	ble	.L312
.L315:
	ldr	r1, [r8, #3176]
	mov	r0, r4
	add	r1, r1, r9
	bl	BsInit
	ldr	r3, [fp, #-328]
	sub	r2, fp, #300
	mov	r1, #0
	mov	r0, r4
	str	r3, [sp, #4]
	sub	r3, fp, #292
	str	r3, [sp]
	sub	r3, fp, #296
	bl	Real8_CB_GetSliceHeader
	cmp	r0, #1
	bne	.L316
	ldr	r3, [r5, #3880]
	ldr	r2, [fp, #-300]
	cmp	r3, #0
	str	r2, [fp, #-308]
	beq	.L394
	ldr	r3, [fp, #-292]
	mov	r0, r4
	ldr	r2, [fp, #-324]
	cmp	r3, #0
	movge	r2, r3
	str	r2, [fp, #-324]
	bl	BsPos
	ldr	r3, [r5, #3976]
	sub	lr, r3, #1
	cmp	lr, r7
	mov	r2, r0, asr #31
	mov	r1, r2, lsr #29
	add	r2, r0, r1
	and	r2, r2, #7
	rsb	r2, r1, r2
	str	r2, [r5, #3944]
	beq	.L395
	cmp	r7, #254
	bhi	.L396
	ldr	r2, [fp, #-312]
	mov	r0, r4
	ldr	r3, [r2, #4]
	ldr	r2, [r2]
	rsb	r3, r2, r3
.L374:
	mov	r3, r3, asl #3
	str	r3, [fp, #-344]
	bl	BsPos
	ldr	r3, [fp, #-344]
	rsb	r0, r0, r3
	str	r0, [r5, #3948]
	ldr	r3, [r6, #912]
	mov	r0, r4
	add	r9, r9, r3
	bl	BsPos
	ldr	ip, [fp, #-336]
	mov	r3, #44
	ldr	lr, [fp, #-320]
	ldr	r1, [r5, #3900]
	str	ip, [r5, #3956]
	str	ip, [r5, #3960]
	str	ip, [r5, #3964]
	mla	r3, r3, lr, r10
	ldr	ip, [fp, #-324]
	str	r1, [r5, #3932]
	add	lr, lr, #1
	str	lr, [fp, #-320]
	str	ip, [r5, #3924]
	ldr	ip, [fp, #-308]
	str	ip, [r5, #3936]
	add	r2, r0, #7
	cmp	r0, #0
	movlt	r0, r2
	ldr	r2, [r5, #3908]
	add	r0, r9, r0, asr #3
	str	r0, [r5, #3952]
	cmp	lr, #131
	mov	r9, #0
	str	r2, [r5, #3928]
	str	r0, [r3, #104]
	ldr	r2, [r5, #3944]
	str	r2, [r3, #112]
	ldr	r2, [r5, #3948]
	str	r2, [r3, #120]
	ldr	r2, [r5, #3964]
	str	r2, [r3, #108]
	ldr	r2, [r5, #3956]
	str	r2, [r3, #116]
	ldr	r2, [r5, #3960]
	str	r2, [r3, #124]
	ldr	r2, [r5, #3932]
	str	r2, [r3, #128]
	ldr	r2, [r5, #3928]
	str	r2, [r3, #132]
	ldr	r2, [r5, #3924]
	str	r2, [r3, #136]
	ldr	r2, [r5, #3936]
	str	r2, [r3, #140]
	str	lr, [r10, #44]
	ble	.L316
	mov	r0, r10
	bl	Real8_ModifySliceMsg
	cmp	r0, #1
	bne	.L397
	ldr	r3, [fp, #-304]
	cmp	r3, #0
	str	r3, [r10, #4]
	beq	.L398
	ldr	r3, [r10]
	ldr	r2, [r3, #880]
	cmp	r2, #1
	beq	.L399
	cmp	r2, #2
	bne	.L316
	ldr	r3, [r3, #884]
	cmp	r3, #0
	ble	.L316
	ldrb	r3, [r10, #20]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L316
	str	r9, [r10, #4]
	mov	r2, r9
	ldr	r1, [r6, #1052]
	mov	r7, r9
	ldr	r0, [r6, #1448]
	bl	FSP_SetDisplay
	ldr	r2, [r10]
	mov	r1, r10
	mov	r0, #8
	ldr	r3, [r2, #884]
	sub	r3, r3, #1
	str	r3, [r2, #884]
	bl	ReleasePacket
	b	.L364
.L383:
	ldr	r1, .L401+36
	mov	r0, #1
	mov	r7, r9
	bl	dprint_vfmw
	b	.L364
.L271:
	ldr	r1, .L401+40
	mov	r0, #18
	bl	dprint_vfmw
	b	.L375
.L387:
	ldr	r2, [r6, #944]
	mov	r7, r3
	ldr	r1, .L401+44
	bl	dprint_vfmw
	b	.L364
.L390:
	cmp	r3, #2
	beq	.L328
	cmp	r3, #1
	beq	.L371
	b	.L285
.L389:
	cmp	r3, #0
	movne	r3, #2
	bne	.L282
.L312:
	mov	r2, #1
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	mov	r7, #0
	bl	FSP_ClearLogicFs
	b	.L364
.L391:
	movw	r3, #1979
	ldr	r2, .L401+48
	ldr	r1, .L401+52
	mov	r0, #22
	bl	dprint_vfmw
	mov	r7, #0
	b	.L364
.L388:
	ldr	r3, [fp, #-308]
	ldrb	r3, [r3, #3191]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L312
	ldr	r3, [fp, #-308]
	ldrb	r3, [r3, #3186]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L285
.L328:
	ldr	r3, [r6, #1060]
	cmp	r3, #0
	bne	.L285
	mov	r2, #1
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	mov	r7, r3
	bl	FSP_ClearLogicFs
	b	.L364
.L385:
	ldr	r3, [fp, #-308]
	ldrb	r3, [r3, #3188]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L275
.L370:
	mov	r0, r9
	bl	ResetVoQueue
	b	.L275
.L386:
	ldr	r1, .L401+56
	mov	r0, #1
	mov	r7, r3
	bl	dprint_vfmw
	b	.L364
.L392:
	ldr	r1, [fp, #-324]
	ldr	r3, [r9, #16]
	ldr	r2, [r5, #3892]
	ldr	r9, [r1, #16]
	subs	r2, r2, r3
	rsb	r9, r3, r9
	ldrmi	r3, [r5, #3888]
	addmi	r2, r2, r3
	cmp	r9, #0
	ldrlt	r3, [r5, #3888]
	addlt	r9, r9, r3
	cmp	r2, r9
	movgt	r2, #0
	cmp	r9, #0
	ble	.L331
	mov	r1, r9
	mov	r0, r2, asl #14
	str	ip, [fp, #-332]
	str	r2, [fp, #-312]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-312]
	mov	r1, r9
	str	r0, [fp, #-324]
	rsb	r0, r2, r9
	mov	r0, r0, asl #14
	bl	__aeabi_idiv
	ldr	r2, [fp, #-312]
	ldr	r3, [fp, #-324]
	ldr	ip, [fp, #-332]
.L302:
	str	r2, [r6, #960]
	str	r9, [r6, #964]
	str	r3, [r6, #968]
	str	r0, [r6, #972]
	b	.L298
.L384:
	ldr	r3, [fp, #-292]
	cmp	r3, #0
	bgt	.L267
	ldr	r3, [fp, #-296]
	cmp	r3, #32
	bgt	.L267
	ldr	r3, [r10, #4]
	cmp	r3, #0
	bne	.L267
	ldr	r3, [r6, #940]
	cmp	r3, #0
	beq	.L264
	ldr	lr, [r5, #3880]
	cmp	lr, #0
	beq	.L264
	ldr	r0, [fp, #-92]
	ldr	r1, [r6, #1452]
	cmp	r0, r1
	beq	.L264
	ldr	r1, [fp, #-88]
	ldr	ip, [r6, #1456]
	cmp	r1, ip
	beq	.L264
	ldr	ip, [r5, #3876]
	str	r0, [sp, #12]
	mov	r0, r2
	str	r1, [sp, #8]
	str	ip, [sp, #4]
	str	lr, [sp]
	ldr	r1, .L401+60
	bl	dprint_vfmw
	ldr	ip, [r9]
	ldr	r2, [fp, #-92]
	ldr	r3, [fp, #-88]
	cmp	ip, #0
	str	r2, [r6, #1452]
	str	r3, [r6, #1456]
	beq	.L264
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r6, #1448]
	blx	ip
	b	.L264
.L395:
	add	r3, r3, #10432
	ldr	r2, [r6, #916]
	add	r3, r3, #7
	ldr	r1, [fp, #-316]
	mov	r0, r4
	add	r3, r8, r3, lsl #2
	rsb	r2, r1, r2
	ldr	r3, [r3, #3180]
	rsb	r3, r3, r2
	b	.L374
.L394:
	mov	r2, r0
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	mov	r7, r3
	bl	FSP_ClearLogicFs
	b	.L364
.L397:
	mov	r2, #1
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	mov	r7, r9
	bl	FSP_ClearLogicFs
	b	.L364
.L396:
	movw	r2, #2146
	ldr	r1, .L401+64
	mov	r0, #22
	mov	r7, #0
	bl	dprint_vfmw
	b	.L364
.L393:
	ldr	r7, [fp, #-340]
.L326:
	ldr	r4, [r10, #4]
	mov	r5, #1
	str	r5, [r10, #48]
	cmp	r4, #0
	beq	.L400
.L309:
	ldr	r3, [r10]
	ldr	r2, [r3, #592]
	str	r2, [r10, #84]
	ldr	r3, [r3, #644]
	str	r3, [r10, #88]
	b	.L364
.L278:
	mov	r2, #1
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	mov	r7, ip
	bl	FSP_ClearLogicFs
	b	.L364
.L331:
	mov	r0, #0
	mov	r3, r0
	b	.L302
.L400:
	mov	r0, r10
	bl	Real8_ModifySliceMsg
	cmp	r0, #1
	ldreq	r3, [fp, #-304]
	streq	r3, [r10, #4]
	beq	.L309
	mov	r2, r5
	ldr	r1, [r6, #1052]
	ldr	r0, [r6, #1448]
	mov	r7, r4
	bl	FSP_ClearLogicFs
	b	.L364
.L399:
	ldrb	r3, [r10, #20]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L316
	str	r9, [r10, #4]
	mov	r2, r9
	ldr	r1, [r6, #1052]
	mov	r7, r9
	ldr	r0, [r6, #1448]
	bl	FSP_SetDisplay
	mov	r1, r10
	mov	r0, #8
	bl	ReleasePacket
	b	.L364
.L398:
	movw	r3, #2179
	ldr	r2, .L401+48
	ldr	r1, .L401+68
	mov	r0, #22
	ldr	r7, [fp, #-304]
	bl	dprint_vfmw
	b	.L364
.L292:
	ldr	r1, [r6, #1052]
	mov	r2, #1
	ldr	r0, [r6, #1448]
	mov	r7, #0
	bl	FSP_ClearLogicFs
	ldr	r1, .L401+72
	mov	r0, r7
	bl	dprint_vfmw
	b	.L364
.L267:
	mvn	r7, #1
	b	.L364
.L402:
	.align	2
.L401:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC13
	.word	.LANCHOR0+460
	.word	g_event_report
	.word	.LC17
	.word	.LC20
	.word	.LC21
	.word	.LC22
	.word	.LC25
	.word	.LC14
	.word	.LC16
	.word	.LC19
	.word	.LANCHOR0+528
	.word	.LC23
	.word	.LC18
	.word	.LC15
	.word	.LC26
	.word	.LC27
	.word	.LC24
	UNWIND(.fnend)
	.size	REAL8DEC_Decode, .-REAL8DEC_Decode
	.align	2
	.global	REAL8DEC_RecycleImage
	.type	REAL8DEC_RecycleImage, %function
REAL8DEC_RecycleImage:
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
	ldr	r0, [r4, #1448]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #1448]
	bl	FSP_GetFsImagePtr
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL8DEC_RecycleImage, .-REAL8DEC_RecycleImage
	.align	2
	.global	REAL8DEC_GetRemainImg
	.type	REAL8DEC_GetRemainImg, %function
REAL8DEC_GetRemainImg:
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
	beq	.L421
	add	r6, r0, #53248
	ldr	r1, [r6, #1048]
	ldr	r0, [r6, #1448]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L421
	ldr	r1, [r6, #1048]
	ldr	r0, [r6, #1448]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L420
.L421:
	add	r5, r4, #54272
	add	r5, r5, #72
.L411:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	GetVoLastImageID
.L420:
	mov	r0, r4
	add	r5, r4, #54272
	bl	Real8_SetImgFormat
	add	r5, r5, #72
	mov	r3, #1
	str	r3, [r7, #180]
	mov	r2, r3
	ldr	r1, [r6, #1048]
	ldr	r0, [r6, #1448]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #1448]
	mov	r2, r4
	str	r7, [sp]
	mov	r3, r5
	mov	r1, #8
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L408
	mov	r2, #0
	ldr	r1, [r6, #1048]
	ldr	r0, [r6, #1448]
	bl	FSP_SetDisplay
	b	.L411
.L408:
	ldr	r3, [r7, #152]
	cmp	r3, #100
	bhi	.L411
	ldr	r3, [r7, #68]
	cmp	r3, #31
	bls	.L411
	ldr	r3, [r7, #72]
	cmp	r3, #31
	bls	.L411
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL8DEC_GetRemainImg, .-REAL8DEC_GetRemainImg
	.align	2
	.global	REAL8DEC_VDMPostProc
	.type	REAL8DEC_VDMPostProc, %function
REAL8DEC_VDMPostProc:
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
	ldr	r1, .L448
	mov	r9, r2
	mov	r0, #22
	mov	r2, r6
	add	r7, r5, #49152
	bl	dprint_vfmw
	ldr	r3, [r5, #4]
	add	r4, r5, #53248
	mov	r1, r5
	mov	r0, #8
	add	r8, r5, #8192
	ldrb	r2, [r3]	@ zero_extendqisi2
	strb	r2, [r7, #3776]
	ldr	r3, [r3, #76]
	str	r3, [r7, #3780]
	bl	ReleasePacket
	ldr	r1, [r4, #1052]
	ldr	r0, [r4, #1448]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L423
	ldr	r3, [r7, #3864]
	cmp	r3, #2
	andne	r9, r9, #31
	strb	r3, [r8, #3189]
	strne	r9, [r7, #3972]
	cmp	r6, #0
	movlt	r6, #0
	blt	.L425
	cmp	r6, #100
	movge	r6, #100
.L425:
	str	r6, [r0, #152]
	mov	r0, #22
	ldr	r1, .L448+4
	bl	dprint_vfmw
	mov	r0, r5
	bl	Real8_SetImgFormat
	ldrb	r3, [r8, #3186]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L428
	ldr	r3, [r5]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	bne	.L428
	ldr	r3, [r7, #3864]
	cmp	r3, #2
	beq	.L428
	ldrb	r3, [r8, #3191]	@ zero_extendqisi2
	cmp	r3, #1
	ldrhi	r1, [r4, #1044]
	mvnls	r1, #0
	cmn	r1, #1
	str	r1, [r4, #1056]
	beq	.L430
.L447:
	ldr	r0, [r4, #1448]
	bl	FSP_GetFsImagePtr
	ldr	r6, [r4, #1056]
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r4, #1448]
	bl	FSP_GetRef
	mov	r2, r6
	ldr	r1, .L448+8
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #1056]
	ldr	r0, [r4, #1448]
	bl	FSP_SetDisplay
	add	r3, r5, #54272
	ldr	r0, [r4, #1448]
	add	r3, r3, #72
	str	r7, [sp]
	mov	r2, r5
	mov	r1, #8
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L446
.L430:
	ldr	r3, [r4, #944]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r4, #944]
.L423:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L428:
	ldr	r1, [r4, #1052]
	cmn	r1, #1
	str	r1, [r4, #1056]
	bne	.L447
	b	.L430
.L446:
	ldr	r0, [r4, #1448]
	mov	r2, #0
	ldr	r1, [r4, #1056]
	bl	FSP_SetDisplay
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L449:
	.align	2
.L448:
	.word	.LC28
	.word	.LC29
	.word	.LC30
	UNWIND(.fnend)
	.size	REAL8DEC_VDMPostProc, .-REAL8DEC_VDMPostProc
	.align	2
	.global	REAL8DEC_GetImageBuffer
	.type	REAL8DEC_GetImageBuffer, %function
REAL8DEC_GetImageBuffer:
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
	ldr	r0, [r4, #1448]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #1448]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L456
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L456:
	add	r1, r5, #54272
	ldr	r0, [r4, #1448]
	add	r1, r1, #72
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	REAL8DEC_GetImageBuffer, .-REAL8DEC_GetImageBuffer
	.align	2
	.global	REAL8DEC_Support
	.type	REAL8DEC_Support, %function
REAL8DEC_Support:
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
	.size	REAL8DEC_Support, .-REAL8DEC_Support
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
.LC3:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
	.word	3
	.type	s_RVVersionEncodingToMinorVersion, %object
	.size	s_RVVersionEncodingToMinorVersion, 32
s_RVVersionEncodingToMinorVersion:
	.word	2
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.word	9999
	.type	__FUNCTION__.14879, %object
	.size	__FUNCTION__.14879, 16
__FUNCTION__.14879:
	.ascii	"REAL8DEC_Decode\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC4:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"image size abnormal (%dx%d) in MB\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"real8 actual frame size(%dx%d) exeed max config(%dx" )
	ASCII(.ascii	"%d)\012\000" )
.LC10:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC12:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC14:
	ASCII(.ascii	"Real8_CB_GetPictureHeader Error!\012\000" )
	.space	2
.LC15:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"pic width/height to large,MbWidth = %d, MbHeight = " )
	ASCII(.ascii	"%d\000" )
	.space	2
.LC17:
	ASCII(.ascii	"new seq size %d * %d\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"Real8_ArrangeVHBMem err\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"Fatal Error: frm%d, get image buffer failed\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC21:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"++++++++++ ref %d\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"%s %d unknow error!!\012\000" )
	.space	2
.LC24:
	ASCII(.ascii	"CurFsID abnormal!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,currpmv,colpmv = %p,%p," )
	ASCII(.ascii	"%p,%p,%p,%p\012\000" )
.LC26:
	ASCII(.ascii	"line:%d! i > (RV8_MAX_SLC_PARAM_NUM - 2)\012\000" )
	.space	2
.LC27:
	ASCII(.ascii	"%s %d NULL == pCtx->pRv8DecParam!!\012\000" )
.LC28:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
