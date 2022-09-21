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
	.file	"hevc.c"
	.text
	.align	2
	.type	HEVC_ComparePicByPocAsc, %function
HEVC_ComparePicByPocAsc:
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
	ldr	r2, [r0]
	ldr	r3, [r1]
	ldr	r2, [r2, #8]
	ldr	r3, [r3, #8]
	cmp	r2, r3
	blt	.L3
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L3:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ComparePicByPocAsc, .-HEVC_ComparePicByPocAsc
	.align	2
	.type	HEVC_UpdateInterLayerReflist, %function
HEVC_UpdateInterLayerReflist:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	add	r9, r0, #4096
	mov	r5, r0
	ldr	r3, [r9, #728]
	cmp	r3, #0
	streq	r3, [r0, #3052]
	streq	r3, [r0, #3056]
	beq	.L5
	ldr	r2, [r9, #2056]
	ldr	r1, [r0, #2824]
	cmp	r2, #0
	ble	.L34
	add	r2, r3, #1024
	add	r0, r1, #12288
	add	r2, r2, #8
	add	ip, r5, #6144
	mov	r3, r3, asl #1
	str	r3, [fp, #-52]
	add	r3, r1, #16384
	str	r3, [fp, #-48]
	add	r3, r0, r2, lsl #2
	str	r3, [fp, #-56]
	add	r3, ip, #8
	mov	r6, #0
	mov	r8, r6
	str	r6, [fp, #-60]
	str	r6, [fp, #-64]
	mov	r7, r0
	mov	r6, r3
.L26:
	ldr	r1, [fp, #-52]
	ldr	r3, [r6, #4]!
	ldr	r2, [fp, #-56]
	add	r3, r1, r3
	ldr	r1, [fp, #-48]
	add	r3, r3, #1040
	add	r3, r3, #4
	ldr	r2, [r2, #132]
	ldr	r4, [r1, #164]
	add	r3, r7, r3, lsl #2
	cmp	r2, r4
	ldr	r10, [r3, #132]
	add	r3, r10, #1024
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ble	.L56
	ldr	r4, [r3, #132]
	cmp	r2, r4
	movlt	r4, #0
	movge	r4, #1
.L10:
	ldr	ip, [r5, #3028]
	cmp	ip, #0
	beq	.L12
	add	r1, r5, #3184
	ldr	lr, [r9, #708]
	add	r1, r1, #8
	mov	r3, #0
	b	.L25
.L13:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L12
.L25:
	ldr	r2, [r1, #4]!
	ldr	r0, [r2, #8]
	cmp	r0, lr
	bne	.L13
	ldr	r0, [r2, #32]
	cmp	r0, r10
	bne	.L13
	add	r10, r5, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r2, [r10, #3196]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L57
.L14:
	mov	r3, #0
	str	r3, [r2, #64]
	ldr	r2, [r10, #3196]
	mov	r1, #1
	str	r1, [r2, #60]
	ldr	r2, [r10, #3196]
	str	r1, [r2, #72]
	ldr	ip, [r10, #3196]
	cmp	ip, r3
	beq	.L58
	ldr	r2, [r9, #728]
	mov	r1, #280
	mul	r1, r1, r2
	add	lr, r5, r1
	add	r0, lr, #13120
	add	r0, r0, #24
	ldr	r0, [r0, #4]
	cmp	r0, #0
	beq	.L16
	add	lr, lr, #13120
	add	lr, lr, #32
	ldr	lr, [lr, #4]
	cmp	lr, #0
	addne	r1, r1, #13120
	addne	r1, r1, #36
	addne	r1, r5, r1
	bne	.L19
	b	.L59
.L23:
	ldr	lr, [r1, #4]!
	cmp	lr, #0
	beq	.L17
.L19:
	add	r3, r3, #1
	cmp	r3, r0
	bne	.L23
.L16:
	cmp	r4, #0
	beq	.L24
	ldr	r2, [fp, #-60]
	add	r3, r5, r2, lsl #2
	str	ip, [r3, #3060]
	add	r3, r2, #1
	str	r3, [fp, #-60]
.L12:
	ldr	r3, [r9, #2056]
	add	r8, r8, #1
	cmp	r3, r8
	bgt	.L26
	ldr	r7, [fp, #-60]
	ldr	r6, [fp, #-64]
	mov	r1, r7
	mov	r3, r6
.L8:
	ldr	r2, [r5, #3024]
	str	r3, [r5, #3056]
	cmp	r2, r7
	str	r1, [r5, #3052]
	addgt	r3, r7, #764
	movgt	r1, #0
	addgt	r3, r5, r3, lsl #2
	ble	.L31
.L30:
	add	r7, r7, #1
	str	r1, [r3, #4]!
	cmp	r7, r2
	bne	.L30
.L31:
	cmp	r2, r6
	ble	.L5
	add	r1, r6, #780
	mov	r3, #0
	add	r1, r1, #1
	add	r5, r5, r1, lsl #2
.L32:
	add	r6, r6, #1
	str	r3, [r5, #4]!
	cmp	r6, r2
	bne	.L32
.L5:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L56:
	ldr	r3, [r3, #132]
	cmp	r2, r3
	movle	r4, #1
	ble	.L10
	cmp	r2, r4
	movlt	r4, #0
	movge	r4, #1
	b	.L10
.L24:
	ldr	r2, [fp, #-64]
	add	r3, r2, #780
	add	r2, r2, #1
	add	r3, r3, #2
	str	r2, [fp, #-64]
	str	ip, [r5, r3, asl #2]
	b	.L12
.L59:
	mov	r3, lr
.L17:
	ldr	r1, [ip, #28]
	ldr	r0, [r5, #276]
	str	ip, [fp, #-68]
	str	r3, [fp, #-76]
	str	r2, [fp, #-72]
	bl	FSP_GetLogicFs
	ldr	ip, [fp, #-68]
	subs	lr, r0, #0
	beq	.L20
	ldr	r1, [lr, #28]
	ldr	r2, [fp, #-72]
	cmp	r1, #0
	ldr	r3, [fp, #-76]
	beq	.L20
	mov	r1, #70
	mov	r0, #280
	mla	r1, r1, r2, r3
	mla	r2, r0, r2, r5
	add	r1, r5, r1, lsl #2
	add	r0, r2, #13120
	add	r1, r1, #12288
	add	r2, r2, r3
	str	r2, [fp, #-68]
	mov	r2, #1
	str	r2, [r1, #868]
	ldr	lr, [lr, #28]
	ldr	r2, [fp, #-68]
	ldr	lr, [lr, #4]
	add	r2, r2, #13376
	str	lr, [r1, #932]
	ldr	lr, [ip, #8]
	str	lr, [r1, #996]
	ldr	lr, [r0, #32]
	add	lr, lr, #1
	str	lr, [r0, #32]
	ldr	r0, [ip, #32]
	str	r0, [r1, #1060]
	str	r3, [ip, #36]
	mov	r3, #1
	strb	r3, [r2, #36]
	ldr	ip, [r10, #3196]
	b	.L16
.L57:
	ldr	r1, [r2, #28]
	mov	r2, #1
	ldr	r0, [r5, #276]
	bl	FSP_SetRef
	ldr	r2, [r10, #3196]
	b	.L14
.L34:
	mov	r3, #0
	mov	r1, r3
	mov	r6, r3
	mov	r7, r3
	b	.L8
.L58:
	mov	r0, ip
	mov	r3, #200
	ldr	r2, .L60
	ldr	r1, .L60+4
	bl	dprint_vfmw
	ldr	ip, [r10, #3196]
	b	.L16
.L20:
	ldrb	r1, [ip, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	r2, [ip, #28]
	ldr	r3, [ip, #8]
	stmia	sp, {r1, lr}
	str	r0, [sp, #8]
	ldr	r1, .L60+8
	bl	dprint_vfmw
	ldr	ip, [r10, #3196]
	b	.L16
.L61:
	.align	2
.L60:
	.word	.LC2
	.word	.LC3
	.word	.LC4
	UNWIND(.fnend)
	.size	HEVC_UpdateInterLayerReflist, .-HEVC_UpdateInterLayerReflist
	.global	__aeabi_idivmod
	.align	2
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.15, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.15:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r3, r0, #4096
	ldr	ip, [r0, #2808]
	movw	r6, #5036
	ldr	r2, [r3, #732]
	movw	r4, #12668
	ldr	r5, [r3, #1632]
	mov	r7, r0
	str	r1, [fp, #-84]
	mla	ip, r6, r2, ip
	ldr	r1, [r3, #1628]
	ldr	lr, [r0, #2804]
	add	r1, r5, r1
	ldr	r2, [r3, #1636]
	str	r1, [fp, #-80]
	mov	r5, r1
	cmp	r1, r2
	ldr	ip, [ip, #32]
	str	r0, [fp, #-60]
	mov	r0, #1
	mla	r1, r4, ip, lr
	ldr	r10, [r1, #116]
	mov	r10, r0, asl r10
	bcs	.L63
	add	r9, r5, #1456
	ldr	r6, [r7, #3028]
	mov	r0, #0
	add	r2, r2, #5696
	add	r1, r5, #5696
	add	r9, r7, r9, lsl #2
	mov	ip, r0
	add	r2, r2, #40
	add	r1, r1, #40
	str	r0, [fp, #-64]
	mov	r0, r7
	add	r2, r7, r2
	str	ip, [fp, #-72]
	str	r2, [fp, #-68]
	add	r2, r7, r1
	str	r3, [fp, #-76]
	str	r2, [fp, #-56]
.L64:
	cmp	r6, #0
	beq	.L70
	ldr	r3, [fp, #-60]
	mov	r2, #0
	mov	r5, r2
	ldr	r8, [r9, #-944]
	add	r4, r3, #3184
	str	r2, [fp, #-52]
	add	r4, r4, #12
	b	.L67
.L107:
	ldr	r3, [r4]
	ldr	r1, [r3, #60]
	cmp	r1, #0
	beq	.L66
	ldr	r0, [r3, #8]
	ldr	r1, [r9]
	cmp	r0, r1
	ldreqb	r3, [r3, #1]	@ zero_extendqisi2
	beq	.L105
.L66:
	add	r5, r5, #1
	add	r4, r4, #4
	cmp	r5, r6
	beq	.L106
.L67:
	cmp	r8, #0
	bne	.L107
	ldr	r7, [r4]
	mov	r1, r10
	ldr	r3, [r7, #60]
	cmp	r3, #0
	beq	.L66
	ldr	r0, [r7, #8]
	bl	__aeabi_idivmod
	ldr	r0, [r9]
	str	r1, [fp, #-48]
	mov	r1, r10
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-48]
	cmp	r3, r1
	bne	.L66
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
.L105:
	cmp	r3, #0
	add	r5, r5, #1
	ldr	r3, [fp, #-52]
	add	r4, r4, #4
	movne	r3, #1
	cmp	r5, r6
	str	r3, [fp, #-52]
	bne	.L67
.L106:
	ldr	r2, [fp, #-52]
	cmp	r2, #0
	beq	.L70
.L68:
	ldr	r3, [fp, #-56]
	add	r9, r9, #4
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r3, r2
	bne	.L64
	ldr	r2, [fp, #-80]
	ldr	r3, [fp, #-76]
	cmp	r2, #0
	beq	.L72
.L71:
	ldr	r2, [fp, #-60]
	mov	r7, #0
	ldr	r10, [fp, #-80]
	add	r4, r2, #5696
	ldr	r0, [fp, #-72]
	mov	r9, r2
	mov	r8, r4
	add	r4, r4, #60
	add	r8, r8, #40
.L76:
	cmp	r6, #0
	beq	.L77
	add	lr, r9, #3184
	mov	r5, #0
	add	lr, lr, #8
	mov	r2, r5
	str	r0, [fp, #-48]
	b	.L74
.L73:
	cmp	r2, r6
	beq	.L108
.L74:
	ldr	r1, [lr, #4]!
	add	r2, r2, #1
	ldr	ip, [r1, #60]
	cmp	ip, #0
	bne	.L73
	ldr	r0, [r4]
	ldr	ip, [r3, #708]
	add	ip, ip, r0
	ldr	r0, [r1, #8]
	cmp	r0, ip
	bne	.L73
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, #0
	movne	r5, #1
	cmp	r2, r6
	bne	.L74
.L108:
	cmp	r5, #0
	ldr	r0, [fp, #-48]
	beq	.L77
.L75:
	add	r7, r7, #1
	add	r4, r4, #4
	cmp	r10, r7
	add	r8, r8, #1
	bhi	.L76
	str	r0, [fp, #-72]
.L72:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	ldrne	r3, [fp, #-84]
	movne	r0, #0
	ldrne	r2, [fp, #-64]
	moveq	r0, #1
	strne	r2, [r3]
.L104:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L77:
	ldr	r1, [r3, #728]
	ldr	r2, [r3, #708]
	ldr	ip, [r4]
	add	r1, r9, r1, lsl #2
	add	r2, r2, ip
	ldr	r1, [r1, #244]
	cmp	r2, r1
	blt	.L75
	ldrb	r1, [r8]	@ zero_extendqisi2
	cmp	r1, #0
	ldr	r1, [fp, #-64]
	movne	r0, #1
	movne	r1, r2
	str	r1, [fp, #-64]
	b	.L75
.L70:
	ldr	r3, [fp, #-76]
	ldr	r0, [r9, #-68]
	ldr	r1, [r3, #728]
	ldr	r2, [r3, #708]
	ldr	r3, [fp, #-60]
	add	r2, r2, r0
	add	r1, r3, r1, lsl #2
	ldr	r1, [r1, #244]
	cmp	r2, r1
	blt	.L68
	ldr	r3, [fp, #-56]
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldr	r3, [fp, #-64]
	cmp	r1, #0
	movne	r3, r2
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-72]
	movne	r3, #1
	str	r3, [fp, #-72]
	b	.L68
.L63:
	ldr	r2, [fp, #-80]
	cmp	r2, #0
	beq	.L104
	ldr	r1, [fp, #-60]
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-72]
	ldr	r6, [r1, #3028]
	b	.L71
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.15, .-HEVC_CheckThatAllRefPicsAreAvailable.part.15
	.align	2
	.type	HEVC_SetFrmRepeatCount.part.16, %function
HEVC_SetFrmRepeatCount.part.16:
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
	ldr	ip, [r0, #308]
	ldr	r2, [r0, #3024]
	ldr	r3, [r0, #304]
	add	r2, r2, ip
	add	ip, r2, #1
	cmp	r3, ip
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	r3, r3, #1
	rsb	r3, r2, r3
	cmp	r3, #1
	movhi	r3, #2
	movls	r3, #1
	strhi	r3, [r1, #16]
	strls	r3, [r1, #16]
	ldrhi	r3, [r0, #308]
	ldrls	r3, [r0, #308]
	addhi	r3, r3, #2
	addls	r3, r3, #1
	str	r3, [r0, #308]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount.part.16, .-HEVC_SetFrmRepeatCount.part.16
	.align	2
	.type	HEVC_OutputFrame, %function
HEVC_OutputFrame:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r4, r0
	mov	r6, r1
	ldr	r0, [r0, #276]
	ldr	r1, [r1, #28]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L164
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L165
.L116:
	mov	r2, #1
	ldr	r1, [r6, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	add	r3, r4, #6144
	ldr	r0, [r4, #276]
	add	r3, r3, #24
	str	r5, [sp]
	mov	r2, r4
	mov	r1, #16
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L166
.L136:
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r5, #16]
	bcs	.L167
.L134:
	ldr	r2, [r4, #316]
	mov	r0, #0
	ldr	r3, [r4, #308]
	add	r2, r2, #1
	str	r2, [r4, #316]
	add	r3, r3, #1
	str	r3, [r4, #308]
.L157:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L167:
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.part.16
	b	.L134
.L165:
	ldr	r1, [r6, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	cmp	r3, #6
	beq	.L168
	bics	r2, r3, #4
	bne	.L131
	ldr	r3, [r6, #32]
	cmp	r3, #0
	beq	.L116
	b	.L132
.L131:
	cmp	r3, #5
	bne	.L116
	ldr	r3, [r6, #32]
	cmp	r3, #1
	beq	.L116
.L132:
	ldr	r1, [r6, #28]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	b	.L136
.L168:
	cmp	r6, #0
	addeq	r10, r4, #2400
	addeq	r10, r10, #4
	beq	.L118
	ldr	r3, [r6, #32]
	cmp	r3, #0
	movw	r3, #2404
	addeq	r10, r4, #2400
	addne	r7, r4, #2592
	addeq	r10, r10, #4
	addne	r7, r7, #8
	ldrh	r3, [r4, r3]
	addne	r10, r4, #2400
	moveq	r7, r10
	addne	r10, r10, #4
	ldrh	r1, [r7, #2]
	add	r2, r1, #1
	and	r0, r2, #15
	cmp	r0, r3
	beq	.L169
.L121:
	mov	r3, r1, asl #4
	ldr	r0, [r6, #8]
	sub	r3, r3, r1, asl #2
	and	r2, r2, #15
	add	r3, r7, r3
	str	r0, [r3, #4]
	ldr	r1, [r6, #28]
	str	r1, [r3, #8]!
	str	r5, [r3, #4]
	strh	r2, [r7, #2]	@ movhi
.L118:
	movw	r3, #2404
	add	r2, r4, #6144
	ldrh	r3, [r4, r3]
	add	r2, r2, #24
	str	r5, [fp, #-52]
	str	r2, [fp, #-48]
.L122:
	ldrh	r2, [r10, #2]
	cmp	r2, r3
	beq	.L161
.L172:
	add	r8, r4, #2592
	add	r8, r8, #8
	ldrh	r1, [r8]
	ldrh	r2, [r8, #2]
	cmp	r2, r1
	beq	.L161
	mov	r7, r3, asl #4
	sub	r7, r7, r3, asl #2
	add	r7, r4, r7
	add	r2, r7, #2400
	add	r2, r2, #12
	ldr	lr, [r2, #4]
	cmp	lr, #0
	beq	.L161
	mov	r9, r1, asl #2
	mov	r6, r1, asl #4
	rsb	ip, r9, r6
	add	r5, r4, ip
	ldr	r3, [r5, #2612]
	cmp	r3, #0
	beq	.L161
	ldr	r3, [r7, #2408]
	ldr	r1, [r5, #2604]
	cmp	r3, r1
	bgt	.L170
	blt	.L171
	ldr	r3, [lr, #180]
	cmp	r3, #0
	beq	.L127
	mov	r3, #0
	str	r3, [lr, #180]
	ldr	r3, [r5, #2612]
	mov	r1, #1
	str	r1, [r3, #180]
	ldr	lr, [r2, #4]
.L127:
	ldr	r0, [r4, #276]
	mov	r2, r4
	ldr	r3, [fp, #-48]
	mov	r1, #16
	str	lr, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L128
	ldr	r2, .L173
	mov	r0, #1
	ldr	r1, .L173+4
	ldr	r3, [r7, #2408]
	bl	dprint_vfmw
	ldr	r1, [r7, #2412]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
.L128:
	ldrh	r0, [r10]
	rsb	r1, r9, r6
	add	r1, r4, r1
	ldr	r3, [fp, #-48]
	add	r0, r0, #1
	mov	r2, r4
	and	r0, r0, #15
	strh	r0, [r10]	@ movhi
	ldr	lr, [r1, #2612]
	mov	r1, #16
	ldr	r0, [r4, #276]
	str	lr, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L129
	ldr	r3, [r5, #2604]
	mov	r0, #1
	ldr	r2, .L173
	ldr	r1, .L173+8
	bl	dprint_vfmw
.L162:
	ldr	r1, [r5, #2608]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
.L129:
	ldrh	r3, [r8]
	add	r3, r3, #1
	and	r3, r3, #15
	strh	r3, [r8]	@ movhi
	ldrh	r3, [r10]
	ldrh	r2, [r10, #2]
	cmp	r2, r3
	bne	.L172
.L161:
	ldr	r5, [fp, #-52]
	b	.L136
.L170:
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L173
	ldr	r1, .L173+12
	bl	dprint_vfmw
	b	.L162
.L171:
	str	r3, [sp]
	mov	r0, #1
	mov	r3, r1
	ldr	r2, .L173
	ldr	r1, .L173+16
	bl	dprint_vfmw
	ldr	r1, [r7, #2412]
	mov	r2, #0
	ldr	r0, [r4, #276]
	bl	FSP_SetDisplay
	ldrh	r3, [r10]
	add	r3, r3, #1
	and	r3, r3, #15
	strh	r3, [r10]	@ movhi
	b	.L122
.L166:
	ldr	r2, .L173+20
	mov	r0, #1
	ldr	r1, .L173+24
	bl	dprint_vfmw
	ldr	r0, [r4, #276]
	ldr	r1, [r6, #28]
	mov	r2, #0
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L157
.L164:
	ldr	r2, .L173+20
	ldr	r1, .L173+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L157
.L169:
	ldrh	r1, [r7]
	mov	r2, #0
	ldr	r0, [r4, #276]
	mov	r3, r1, asl #4
	sub	r3, r3, r1, asl #2
	add	r3, r7, r3
	ldr	r8, [r3, #8]
	mov	r1, r8
	bl	FSP_SetDisplay
	ldrh	r2, [r7]
	ldr	r1, .L173+32
	mov	r3, r8
	add	r2, r2, #1
	mov	r0, #1
	and	r2, r2, #15
	strh	r2, [r7]	@ movhi
	ldr	r2, [r6, #32]
	bl	dprint_vfmw
	ldrh	r1, [r7, #2]
	add	r2, r1, #1
	b	.L121
.L174:
	.align	2
.L173:
	.word	.LANCHOR0+20
	.word	.LC9
	.word	.LC10
	.word	.LC7
	.word	.LC8
	.word	.LANCHOR0
	.word	.LC11
	.word	.LC5
	.word	.LC6
	UNWIND(.fnend)
	.size	HEVC_OutputFrame, .-HEVC_OutputFrame
	.align	2
	.global	HEVC_CheckVpsExtOverlap
	.type	HEVC_CheckVpsExtOverlap, %function
HEVC_CheckVpsExtOverlap:
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
	subs	r4, r0, #0
	beq	.L179
.L176:
	add	r3, r4, #12288
	ldrb	r0, [r4]	@ zero_extendqisi2
	ldrb	r3, [r3, #200]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L179:
	ldr	r2, .L180
	mov	r0, #1
	ldr	r1, .L180+4
	bl	dprint_vfmw
	b	.L176
.L181:
	.align	2
.L180:
	.word	.LANCHOR0+48
	.word	.LC12
	UNWIND(.fnend)
	.size	HEVC_CheckVpsExtOverlap, .-HEVC_CheckVpsExtOverlap
	.align	2
	.global	HEVC_CheckPpsExtOverlap
	.type	HEVC_CheckPpsExtOverlap, %function
HEVC_CheckPpsExtOverlap:
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
	subs	r4, r0, #0
	beq	.L186
.L183:
	ldrb	r3, [r4, #3144]	@ zero_extendqisi2
	ldrb	r0, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L186:
	ldr	r2, .L187
	mov	r0, #1
	ldr	r1, .L187+4
	bl	dprint_vfmw
	b	.L183
.L188:
	.align	2
.L187:
	.word	.LANCHOR0+72
	.word	.LC13
	UNWIND(.fnend)
	.size	HEVC_CheckPpsExtOverlap, .-HEVC_CheckPpsExtOverlap
	.align	2
	.global	HEVC_CheckSliceExtOverlap
	.type	HEVC_CheckSliceExtOverlap, %function
HEVC_CheckSliceExtOverlap:
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
	subs	r4, r0, #0
	beq	.L193
.L190:
	ldrb	r3, [r4, #16]	@ zero_extendqisi2
	ldrb	r0, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #2
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, r3
	orrne	r0, r3, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L193:
	ldr	r2, .L194
	mov	r0, #1
	ldr	r1, .L194+4
	bl	dprint_vfmw
	b	.L190
.L195:
	.align	2
.L194:
	.word	.LANCHOR0+96
	.word	.LC14
	UNWIND(.fnend)
	.size	HEVC_CheckSliceExtOverlap, .-HEVC_CheckSliceExtOverlap
	.align	2
	.global	HEVC_Sei_ParsePts_Init
	.type	HEVC_Sei_ParsePts_Init, %function
HEVC_Sei_ParsePts_Init:
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
	ldr	r3, .L197
	mov	r6, r0
	mov	r2, #56
	add	r0, r0, #11712
	mov	r1, #0
	mov	r4, #0
	ldr	r3, [r3, #48]
	mov	r5, #0
	blx	r3
	add	r3, r6, #3488
	mov	r2, #0
	strd	r4, [r3, #32]
	strd	r4, [r3, #8]
	strd	r4, [r3, #16]
	strd	r4, [r3, #24]
	str	r2, [r6, #3476]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L198:
	.align	2
.L197:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_Sei_ParsePts_Init, .-HEVC_Sei_ParsePts_Init
	.align	2
	.global	HEVC_Sei_Get_Dpb_Output_Time
	.type	HEVC_Sei_Get_Dpb_Output_Time, %function
HEVC_Sei_Get_Dpb_Output_Time:
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
	add	r3, r0, #4096
	ldr	r5, [r0, #2808]
	movw	r6, #5036
	ldr	r1, [r0, #2804]
	ldr	ip, [r3, #732]
	movw	r4, #12668
	ldr	lr, [r2, #36]
	add	r3, r0, #8192
	mla	ip, r6, ip, r5
	ldr	r5, [r3, #3524]
	cmp	r5, #1
	ldr	ip, [ip, #32]
	str	lr, [r3, #3532]
	ldr	lr, [r2, #40]
	mla	r1, r4, ip, r1
	str	lr, [r3, #3536]
	ldr	ip, [r1, #52]
	add	ip, ip, #90
	ldrb	ip, [r1, ip, asl #2]	@ zero_extendqisi2
	beq	.L207
	ldrb	r1, [r3, #3521]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L208
	add	r1, r0, #3488
	ldr	lr, [r0, #3488]
	ldrd	r4, [r1, #8]
	adds	r4, r4, lr
	adc	r5, r5, #0
	strd	r4, [r1, #32]
.L201:
	add	lr, r0, #11712
	strd	r4, [r1, #24]
	mov	r1, #0
	strb	r1, [r3, #3521]
	ldrd	r6, [lr, #32]
	strd	r6, [lr, #48]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	cmp	r3, r1
	ldr	r3, [r0, #3492]
	bne	.L209
	adds	r4, r4, r3
	adc	r5, r5, #0
	subs	r4, r4, ip
	sbc	r5, r5, #0
	strd	r4, [lr, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L208:
	ldrb	r1, [r0, #3472]	@ zero_extendqisi2
	cmp	r1, #0
	add	r1, r0, #3488
	bne	.L210
	ldrd	r4, [r1, #8]
	ldrd	r8, [r1, #16]
.L204:
	ldr	r6, [r0, #3488]
	mov	r7, #0
	adds	r4, r4, r6
	adc	r5, r5, r7
	cmp	r4, r8
	sbcs	lr, r5, r9
	strd	r4, [r1, #32]
	strd	r4, [r1, #8]
	bge	.L201
	adds	r4, r6, r8
	adc	r5, r7, r9
	strd	r4, [r1, #32]
	strd	r4, [r1, #8]
	b	.L201
.L209:
	adds	r4, r4, r3
	adc	r5, r5, #0
	movs	r5, r5, asr #1
	mov	r4, r4, rrx
	subs	r4, r4, ip
	sbc	r5, r5, #0
	strd	r4, [lr, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L207:
	ldr	r4, [r0, #3476]
	add	r1, r0, #3488
	mov	r5, r4, asr #31
	strd	r4, [r1, #32]
	strd	r4, [r1, #8]
	b	.L201
.L210:
	ldrd	r4, [r1, #16]
	mov	r8, r4
	mov	r9, r5
	b	.L204
	UNWIND(.fnend)
	.size	HEVC_Sei_Get_Dpb_Output_Time, .-HEVC_Sei_Get_Dpb_Output_Time
	.align	2
	.global	HEVC_Get_Last_IDR_Frame_Info
	.type	HEVC_Get_Last_IDR_Frame_Info, %function
HEVC_Get_Last_IDR_Frame_Info:
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
	sub	r3, r1, #19
	cmp	r3, #1
	bls	.L215
.L212:
	sub	r1, r1, #6
	cmp	r1, #3
	addhi	r0, r0, #3488
	ldrhid	r2, [r0, #32]
	strhid	r2, [r0, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L215:
	ldr	ip, [r0, #2844]
	mvn	r3, #0
	mvn	r2, #0
	ldrd	r4, [ip, #56]
	cmp	r5, r3
	cmpeq	r4, r2
	beq	.L213
	add	r3, r0, #11712
	movw	r2, #11744
	add	r3, r3, #32
	add	ip, r0, #11712
	strd	r4, [r3, #-8]
	ldrd	r2, [r2, r0]
	strd	r2, [ip, #40]
.L213:
	add	r3, r0, #8192
	mov	r2, #1
	strb	r2, [r3, #3520]
	b	.L212
	UNWIND(.fnend)
	.size	HEVC_Get_Last_IDR_Frame_Info, .-HEVC_Get_Last_IDR_Frame_Info
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	HEVC_Sei_Get_Frame_Pts
	.type	HEVC_Sei_Get_Frame_Pts, %function
HEVC_Sei_Get_Frame_Pts:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r2, r0, #11712
	add	r1, r0, #8192
	add	r3, r2, #48
	ldrd	r6, [r2, #24]
	mov	r4, r0
	ldr	r5, [r1, #3532]
	movw	r0, #11744
	ldrd	r2, [r3, #-8]
	cmp	r5, #0
	strd	r6, [fp, #-52]
	ldr	r10, [r1, #3536]
	strd	r2, [fp, #-60]
	ldrd	r6, [r4, r0]
	beq	.L219
	mov	r9, r5
	mov	r0, r10
	b	.L218
.L220:
	mov	r9, r1
.L218:
	mov	r1, r9
	bl	__aeabi_uidivmod
	mov	r0, r9
	cmp	r1, #0
	bne	.L220
.L217:
	ldrd	r2, [fp, #-60]
	mov	r1, r9
	mov	r0, r5
	mov	r8, #1000
	subs	r2, r6, r2
	add	r4, r4, #4736
	mul	r6, r8, r2
	bl	__aeabi_uidiv
	mov	r1, r9
	mul	r6, r0, r6
	mov	r0, r10
	bl	__aeabi_uidiv
	mov	r1, r0
	mov	r0, r6
	bl	__aeabi_uidiv
	ldrd	r2, [fp, #-52]
	adds	r2, r2, r0
	adc	r3, r3, #0
	mov	r0, r2
	mov	r1, r3
	strd	r0, [r4, #8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L219:
	mov	r9, r10
	b	.L217
	UNWIND(.fnend)
	.size	HEVC_Sei_Get_Frame_Pts, .-HEVC_Sei_Get_Frame_Pts
	.align	2
	.global	HEVC_InitSigLastScan
	.type	HEVC_InitSigLastScan, %function
HEVC_InitSigLastScan:
	UNWIND(.fnstart)
	@ args = 16, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r4, [fp, #8]
	str	r0, [fp, #-48]
	cmp	r4, #15
	ldr	r6, [fp, #4]
	bgt	.L222
	cmp	r4, #8
	mul	r9, r4, r4
	beq	.L255
	cmp	r9, #0
	movne	r10, r6
	beq	.L222
.L224:
	mov	r5, #0
	rsb	r7, r4, #1
	mov	r8, r5
.L230:
	cmp	r4, r8
	bgt	.L242
	rsb	lr, r4, r8
	sub	r2, r4, #1
	add	lr, lr, #1
.L231:
	cmp	r2, #0
	cmpge	r4, lr
	ble	.L228
	mla	r0, r2, r4, lr
	add	ip, r10, r5, lsl #2
	mov	r1, r5
.L229:
	add	r1, r1, #1
	sub	r2, r2, #1
	rsb	r3, r5, r1
	str	r0, [ip], #4
	add	r3, r3, lr
	add	r0, r0, r7
	cmp	r2, #0
	cmpge	r4, r3
	bgt	.L229
	mov	r5, r1
.L228:
	cmp	r9, r5
	add	r8, r8, #1
	bhi	.L230
.L222:
	cmp	r4, #4
	ble	.L221
	mov	r3, r4, asr #2
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-64]
	mov	r2, r3
	add	r3, r1, r3
	mul	r2, r2, r2
	mov	r0, r2
	str	r2, [fp, #-60]
	cmp	r0, #0
	ldrsb	r2, [r3, #15]
	add	r2, r2, #1
	beq	.L221
	add	r3, r1, #364
.L226:
	ldr	r1, .L256
	rsb	r7, r4, #1
	str	r3, [fp, #-52]
	mov	r3, #0
	add	r2, r1, r2, lsl #16
	str	r3, [fp, #-48]
	sub	r3, r2, #4
	str	r3, [fp, #-56]
.L240:
	ldr	r3, [fp, #-56]
	cmp	r4, #32
	ldr	r9, [fp, #-64]
	mov	r8, #0
	ldr	r5, [r3, #4]!
	mov	r1, r9
	str	r3, [fp, #-56]
	ldreq	r3, [fp, #-52]
	ldreq	r5, [r3]
	mov	r0, r5
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-48]
	mov	r3, r8
	mov	r2, r8
	mov	lr, r8
	mov	r10, ip, asl #4
	mla	r1, r4, r0, r5
	mls	r1, r9, r0, r1
	mov	r9, r1, asl #2
.L234:
	cmp	lr, #3
	mvn	r1, r2
	mov	r1, r1, lsr #31
	movgt	r1, #0
	cmp	r1, #0
	beq	.L235
	mla	r1, r2, r4, lr
	add	r0, r3, r10
	rsb	lr, r3, lr
	add	r0, r6, r0, lsl #2
	add	r1, r1, r9
.L236:
	add	r3, r3, #1
	sub	r2, r2, #1
	add	r5, lr, r3
	str	r1, [r0], #4
	cmp	r5, #3
	mvn	ip, r2
	mov	ip, ip, lsr #31
	add	r1, r1, r7
	movgt	ip, #0
	cmp	ip, #0
	bne	.L236
.L235:
	cmp	r3, #15
	add	r8, r8, #1
	bhi	.L237
	cmp	r8, #3
	movle	r2, r8
	movle	lr, #0
	subgt	lr, r8, #3
	movgt	r2, #3
	b	.L234
.L237:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #4
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L240
.L221:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L242:
	mov	r2, r8
	mov	lr, #0
	b	.L231
.L255:
	add	r3, r0, #364
	cmp	r9, #0
	mov	r10, r3
	bne	.L224
	ldr	r2, [fp, #-48]
	mov	r1, #2
	str	r1, [fp, #-64]
	mov	r1, #4
	str	r1, [fp, #-60]
	ldrsb	r2, [r2, #17]
	add	r2, r2, #1
	b	.L226
.L257:
	.align	2
.L256:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	HEVC_InitSigLastScan, .-HEVC_InitSigLastScan
	.align	2
	.global	HEVC_InitScalingOrderTable
	.type	HEVC_InitScalingOrderTable, %function
HEVC_InitScalingOrderTable:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	add	r3, r0, #14
	add	r1, r0, #143
	mov	r7, r0
	mvn	r2, #0
.L259:
	strb	r2, [r3, #1]!
	cmp	r3, r1
	bne	.L259
	ldr	r6, .L263
	mov	r2, #0
	mov	r3, #2
	mov	r5, r2
	mov	r4, r3
	strb	r2, [r7, #19]
	strb	r3, [r7, #31]
	mov	r2, #1
	mov	r3, #3
	strb	r2, [r7, #23]
	strb	r3, [r7, #47]
	mov	r3, #4
	strb	r3, [r7, #79]
.L260:
	mov	r3, #0
	str	r5, [sp, #12]
	str	r4, [sp, #8]
	add	r5, r5, #1
	str	r4, [sp, #4]
	mov	r2, r3
	str	r6, [sp]
	mov	r1, r3
	mov	r0, r7
	mov	r4, r4, asl #1
	bl	HEVC_InitSigLastScan
	cmp	r5, #7
	add	r6, r6, #65536
	bne	.L260
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L264:
	.align	2
.L263:
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	HEVC_InitScalingOrderTable, .-HEVC_InitScalingOrderTable
	.global	__aeabi_idiv
	.align	2
	.global	HEVC_GetDar
	.type	HEVC_GetDar, %function
HEVC_GetDar:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
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
	cmp	r0, #0
	mov	ip, r1
	moveq	r4, r0
	beq	.L266
	subs	lr, r0, #255
	movne	lr, #1
	cmp	r0, #16
	movle	r4, #0
	andgt	r4, lr, #1
	cmp	r4, #0
	movne	r4, #0
	bne	.L266
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #255
	movne	r1, #0
	andeq	r1, r1, #1
	cmp	r1, #0
	bne	.L266
	cmp	r0, #1
	moveq	r4, #5
	beq	.L266
	cmp	lr, #0
	str	r3, [fp, #-24]
	ldrne	r2, .L288
	addne	r0, r2, r0, lsl #3
	ldrne	r2, [r0, #128]
	ldrne	ip, [r0, #124]
	mov	r1, r2
	mov	r0, ip, asl #10
	bl	__aeabi_idiv
	ldr	r3, [fp, #-24]
	ldr	r1, [fp, #4]
	mov	r4, r0
	mov	r0, r3, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r2, #2262
	mul	r0, r0, r4
	add	r4, r0, #1020
	cmp	r0, #0
	add	r4, r4, #3
	movlt	r0, r4
	mov	r0, r0, asr #10
	cmp	r0, r3
	rsble	r3, r0, #2400
	subgt	r3, r0, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r0, r2
	bgt	.L270
	rsb	r2, r0, #2256
	add	r2, r2, #7
	cmp	r3, r2
	bge	.L271
.L281:
	mov	r4, #4
.L266:
	mov	r2, r4
	ldr	r1, .L288+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L270:
	sub	r2, r0, #2256
	sub	r2, r2, #7
	cmp	r3, r2
	blt	.L281
.L271:
	movw	r3, #1819
	cmp	r0, r3
	bgt	.L272
	rsb	r3, r0, #1808
	add	r3, r3, #12
	cmp	r2, r3
	blt	.L283
.L273:
	movw	r2, #1364
	cmp	r0, r2
	rsble	r0, r0, #1360
	subgt	r0, r0, #1360
	addle	r0, r0, #5
	subgt	r0, r0, #5
	cmp	r3, r0
	movlt	r4, #2
	movge	r4, #1
	b	.L266
.L272:
	sub	r3, r0, #1808
	sub	r3, r3, #12
	cmp	r2, r3
	bge	.L273
.L283:
	mov	r4, #3
	b	.L266
.L289:
	.align	2
.L288:
	.word	.LANCHOR0
	.word	.LC15
	UNWIND(.fnend)
	.size	HEVC_GetDar, .-HEVC_GetDar
	.align	2
	.global	HEVC_PrintNaluArraySlot
	.type	HEVC_PrintNaluArraySlot, %function
HEVC_PrintNaluArraySlot:
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
	ldr	r1, .L296
	mov	r7, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #168]
	cmn	r3, #1
	movne	r5, #0
	movwne	r6, #52429
	movne	r4, r5
	movtne	r6, 52428
	bne	.L293
	b	.L294
.L292:
	ldr	r3, [r7, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bls	.L294
.L293:
	ldr	r3, [r7, #2840]
	mov	r2, r4
	ldr	r1, .L296+4
	mov	r0, #1
	add	r3, r3, r5
	add	r5, r5, #96
	ldr	ip, [r3, #32]
	str	ip, [sp]
	bl	dprint_vfmw
	umull	r2, r3, r4, r6
	mov	r2, r3, lsr #3
	mov	r3, r2, asl #3
	add	r3, r3, r2, lsl #1
	cmp	r4, r3
	add	r4, r4, #1
	bne	.L292
	ldr	r1, .L296+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bhi	.L293
.L294:
	ldr	r1, .L296+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, .L296+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L297:
	.align	2
.L296:
	.word	.LC16
	.word	.LC19
	.word	.LC17
	.word	.LC18
	UNWIND(.fnend)
	.size	HEVC_PrintNaluArraySlot, .-HEVC_PrintNaluArraySlot
	.align	2
	.global	HEVC_PrintCurrSlicelistX
	.type	HEVC_PrintCurrSlicelistX, %function
HEVC_PrintCurrSlicelistX:
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
	add	r6, r0, #4096
	mov	r7, r0
	ldr	r1, .L319
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #764]
	ldr	r1, .L319+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #764]
	cmp	r3, #0
	addne	r5, r7, #2848
	movne	r4, #0
	addne	r5, r5, #4
	beq	.L306
.L305:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L319+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L319+12
	cmp	r3, #0
	beq	.L303
	ldr	r2, [r3, #20]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L303
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #276]
	bl	FSP_GetLogicFs
	ldr	r1, .L319+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L303:
	ldr	r1, .L319+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #764]
	cmp	r3, r4
	bhi	.L305
.L306:
	ldr	r2, [r6, #768]
	mov	r0, #1
	ldr	r1, .L319+24
	bl	dprint_vfmw
	ldr	r3, [r6, #768]
	cmp	r3, #0
	addne	r5, r7, #2912
	movne	r4, #0
	addne	r5, r5, #8
	beq	.L301
.L310:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L319+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L319+12
	cmp	r3, #0
	beq	.L308
	ldr	r2, [r3, #20]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L308
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #276]
	bl	FSP_GetLogicFs
	ldr	r1, .L319+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L308:
	ldr	r1, .L319+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #768]
	cmp	r3, r4
	bhi	.L310
.L301:
	ldr	r1, .L319+32
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L320:
	.align	2
.L319:
	.word	.LC20
	.word	.LC21
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC17
	.word	.LC22
	.word	.LC27
	.word	.LC26
	UNWIND(.fnend)
	.size	HEVC_PrintCurrSlicelistX, .-HEVC_PrintCurrSlicelistX
	.align	2
	.global	HEVC_PrintFrameStoreState
	.type	HEVC_PrintFrameStoreState, %function
HEVC_PrintFrameStoreState:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r1, .L328
	mov	r10, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	cmp	r3, #0
	addne	r8, r10, #13696
	movne	r9, #0
	addne	r8, r8, #16
	beq	.L325
.L324:
	ldrb	ip, [r8, #2]	@ zero_extendqisi2
	mov	r3, r8
	mov	r2, r9
	ldr	r1, .L328+4
	mov	r0, #1
	add	r5, r8, #616
	str	ip, [sp, #8]
	mov	r4, #0
	ldrb	ip, [r8, #1]	@ zero_extendqisi2
	str	ip, [sp, #4]
	ldr	ip, [r8, #48]
	str	ip, [sp]
	bl	dprint_vfmw
.L323:
	ldrd	r6, [r5, #8]!
	mov	r2, r4
	ldr	r1, .L328+8
	add	r4, r4, #1
	mov	r0, #1
	strd	r6, [sp]
	bl	dprint_vfmw
	cmp	r4, #4
	bne	.L323
	ldr	r1, .L328+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	add	r9, r9, #1
	add	r8, r8, #712
	cmp	r3, r9
	bhi	.L324
.L325:
	ldr	r1, .L328+16
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L329:
	.align	2
.L328:
	.word	.LC28
	.word	.LC30
	.word	.LC31
	.word	.LC17
	.word	.LC29
	UNWIND(.fnend)
	.size	HEVC_PrintFrameStoreState, .-HEVC_PrintFrameStoreState
	.align	2
	.global	HEVC_PrintAPCState
	.type	HEVC_PrintAPCState, %function
HEVC_PrintAPCState:
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
	ldr	r1, .L335
	mov	r6, r0
	mov	r0, #1
	bl	dprint_vfmw
	add	r6, r6, #13120
	add	r6, r6, #32
	mov	r7, #0
.L332:
	ldr	ip, [r6, #-4]
	mov	r2, r7
	ldr	r3, [r6]
	mov	r0, #1
	ldr	r1, .L335+4
	mov	r5, r6
	str	ip, [sp]
	mov	r4, #0
	bl	dprint_vfmw
.L331:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L335+8
	add	r4, r4, #1
	mov	r0, #1
	ldr	ip, [r5, #128]
	str	ip, [sp, #4]
	ldr	ip, [r5, #64]
	str	ip, [sp]
	bl	dprint_vfmw
	cmp	r4, #16
	bne	.L331
	add	r7, r7, #1
	add	r6, r6, #280
	cmp	r7, #2
	bne	.L332
	ldr	r1, .L335+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L336:
	.align	2
.L335:
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC35
	UNWIND(.fnend)
	.size	HEVC_PrintAPCState, .-HEVC_PrintAPCState
	.align	2
	.global	HEVC_PrintDPBState
	.type	HEVC_PrintDPBState, %function
HEVC_PrintDPBState:
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
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r1, .L353
	mov	r9, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r9, #3040]
	ldr	lr, [r9, #3036]
	mov	r0, #1
	ldr	ip, [r9, #3044]
	ldr	r3, [r9, #3028]
	ldr	r2, [r9, #3024]
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L353+4
	bl	dprint_vfmw
	ldr	r3, [r9, #3028]
	cmp	r3, #0
	addne	r4, r9, #3184
	movne	r5, #0
	addne	r4, r4, #8
	beq	.L342
.L341:
	ldr	r3, [r4, #4]!
	ldr	r0, [r9, #276]
	ldrb	ip, [r3]	@ zero_extendqisi2
	ldr	r2, [r3, #32]
	ldr	lr, [r3, #48]
	ldrb	r6, [r3, #1]	@ zero_extendqisi2
	str	ip, [fp, #-52]
	ldr	ip, [r3, #60]
	ldr	r1, [r3, #28]
	str	r2, [fp, #-48]
	str	lr, [fp, #-56]
	ldrb	r8, [r3, #2]	@ zero_extendqisi2
	str	ip, [fp, #-64]
	ldr	r10, [r3, #8]
	str	r6, [fp, #-60]
	bl	FSP_GetLogicFs
	ldr	r3, [r4]
	ldr	r1, [r3, #28]
	mov	r6, r0
	ldr	r0, [r9, #276]
	bl	FSP_GetRef
	ldr	r3, [r4]
	ldr	r1, [r3, #28]
	mov	r7, r0
	ldr	r0, [r9, #276]
	bl	FSP_GetDisplay
	ldr	r1, [r4]
	ldr	ip, [fp, #-64]
	mov	r2, r5
	add	r5, r5, #1
	ldr	lr, [r1, #228]
	mov	r3, r1
	str	lr, [sp, #44]
	ldr	r1, [r1, #28]
	ldr	lr, [fp, #-56]
	str	ip, [sp, #24]
	str	r1, [sp, #40]
	str	r8, [sp, #16]
	ldr	r1, [fp, #-48]
	ldr	r8, [fp, #-60]
	ldr	ip, [fp, #-52]
	str	r1, [sp]
	str	r10, [sp, #20]
	str	r8, [sp, #12]
	str	lr, [sp, #8]
	str	ip, [sp, #4]
	str	r7, [sp, #32]
	str	r6, [sp, #28]
	ldr	r1, .L353+8
	str	r0, [sp, #36]
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #3028]
	cmp	r3, r5
	bhi	.L341
.L342:
	ldr	r1, .L353+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #3028]
	cmp	r3, #0
	addne	r5, r9, #3184
	movne	r6, #0
	addne	r5, r5, #8
	bne	.L349
	b	.L340
.L352:
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L353+16
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4]
	ldr	r1, .L353+20
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4, #1]
	ldr	r1, .L353+24
	mov	r0, #1
	bl	dprint_vfmw
.L344:
	cmp	r8, #0
	mov	r2, r8
	ldr	r1, .L353+28
	mov	r0, #1
	beq	.L345
	bl	dprint_vfmw
	ldr	r2, [r8, #72]
	ldr	r1, .L353+32
	mov	r0, #1
	bl	dprint_vfmw
.L346:
	cmp	r7, #0
	mov	r2, r7
	ldr	r1, .L353+36
	mov	r0, #1
	beq	.L347
	bl	dprint_vfmw
	ldr	r2, [r7, #72]
	ldr	r1, .L353+40
	mov	r0, #1
	bl	dprint_vfmw
.L348:
	ldr	r1, .L353+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #3028]
	add	r6, r6, #1
	cmp	r3, r6
	bls	.L340
.L349:
	ldr	r3, [r5, #4]!
	ldr	r0, [r9, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r4, r0
	ldr	r0, [r9, #276]
	bl	FSP_GetDecPhyFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r8, r0
	ldr	r0, [r9, #276]
	bl	FSP_GetDispPhyFs
	mov	r2, r6
	ldr	r1, .L353+44
	mov	r7, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r4, #0
	mov	r2, r4
	ldr	r1, .L353+48
	mov	r0, #1
	bne	.L352
	ldr	r1, .L353+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L344
.L347:
	ldr	r1, .L353+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L348
.L345:
	ldr	r1, .L353+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L346
.L340:
	ldr	r1, .L353+64
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L354:
	.align	2
.L353:
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC17
	.word	.LC42
	.word	.LC43
	.word	.LC44
	.word	.LC46
	.word	.LC47
	.word	.LC49
	.word	.LC50
	.word	.LC40
	.word	.LC41
	.word	.LC45
	.word	.LC51
	.word	.LC48
	.word	.LC39
	UNWIND(.fnend)
	.size	HEVC_PrintDPBState, .-HEVC_PrintDPBState
	.align	2
	.global	HEVC_IsSliceUnit
	.type	HEVC_IsSliceUnit, %function
HEVC_IsSliceUnit:
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
	cmp	r0, #9
	bls	.L357
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L357:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsSliceUnit, .-HEVC_IsSliceUnit
	.align	2
	.global	HEVC_IsIUnit
	.type	HEVC_IsIUnit, %function
HEVC_IsIUnit:
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
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsIUnit, .-HEVC_IsIUnit
	.align	2
	.global	HEVC_IsNonRefPic
	.type	HEVC_IsNonRefPic, %function
HEVC_IsNonRefPic:
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
	bics	r0, r0, #6
	subne	r0, r0, #8
	clzne	r0, r0
	movne	r0, r0, lsr #5
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsNonRefPic, .-HEVC_IsNonRefPic
	.align	2
	.global	HEVC_IsFlushUnit
	.type	HEVC_IsFlushUnit, %function
HEVC_IsFlushUnit:
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
	sub	r0, r0, #16
	cmp	r0, #4
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsFlushUnit, .-HEVC_IsFlushUnit
	.align	2
	.global	HEVC_IsPVRFlushPic
	.type	HEVC_IsPVRFlushPic, %function
HEVC_IsPVRFlushPic:
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
	add	r3, r0, #4096
	ldr	r3, [r3, #16]
	cmp	r3, #0
	bne	.L365
	ldr	r2, [r0, #2844]
	ldr	r1, [r2, #652]
	cmp	r1, #1
	beq	.L369
.L367:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L365:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L369:
	ldr	r0, [r2, #648]
	cmp	r0, #0
	bne	.L367
	ldr	r3, [r2, #656]
	cmp	r3, #0
	ldmnefd	sp, {fp, sp, pc}
	ldr	r3, [r2, #612]
	add	r3, r3, #1024
	cmp	r3, #2048
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPVRFlushPic, .-HEVC_IsPVRFlushPic
	.align	2
	.global	HEVC_IsEosNal
	.type	HEVC_IsEosNal, %function
HEVC_IsEosNal:
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
	mov	r1, #32
	mov	r4, r0
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	moveq	r0, #1
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsEosNal, .-HEVC_IsEosNal
	.align	2
	.global	HEVC_CalcTileInfo
	.type	HEVC_CalcTileInfo, %function
HEVC_CalcTileInfo:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r8, r1
	ldr	r1, [r0, #2832]
	mov	r6, r2
	ldr	r2, [r0, #2828]
	mov	r5, r0
	str	r3, [fp, #-48]
	ldr	r7, [r1, #68]
	ldr	r2, [r2, #128]
	sub	r3, r7, #1
	ldr	r9, [r1, #72]
	cmp	r3, #9
	str	r2, [fp, #-52]
	bhi	.L399
	sub	r3, r9, #1
	cmp	r3, #10
	bhi	.L400
	ldr	r4, .L401
	mov	r2, #512
	mov	r1, #0
	mov	r0, r8
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #80
	mov	r1, #0
	mov	r0, r6
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #88
	mov	r1, #0
	ldr	r0, [fp, #-48]
	blx	r3
	cmp	r7, #0
	ble	.L380
	ldr	r3, [fp, #-52]
	mov	r2, #0
	mov	r1, r2
	mov	r0, r6
	sub	r10, r3, #4
.L379:
	str	r2, [r6, r1, asl #3]
	mov	r3, r2, asl r10
	ldr	ip, [r5, #2832]
	add	ip, ip, r1, lsl #1
	ldrsh	ip, [ip, #172]
	add	r2, ip, r2
	sub	ip, r2, #1
	str	ip, [r0, #4]
	mov	lr, r2, asl r10
	cmp	r3, lr
	bge	.L385
	cmp	r3, #255
	bhi	.L381
	uxtb	r4, r1
	add	ip, r8, r3
	b	.L383
.L384:
	cmp	r3, #256
	beq	.L381
.L383:
	add	r3, r3, #1
	strb	r4, [ip], #1
	cmp	r3, lr
	bne	.L384
.L385:
	add	r1, r1, #1
	add	r0, r0, #8
	cmp	r1, r7
	bne	.L379
.L380:
	cmp	r9, #0
	ble	.L377
	ldr	r3, [fp, #-52]
	mov	ip, #0
	ldr	r7, [fp, #-48]
	mov	lr, ip
	sub	r4, r3, #4
	mov	r6, r7
.L387:
	str	ip, [r7, lr, asl #3]
	mov	r3, ip, asl r4
	ldr	r2, [r5, #2832]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #212]
	add	ip, r2, ip
	sub	r2, ip, #1
	str	r2, [r6, #4]
	mov	r1, ip, asl r4
	cmp	r3, r1
	bge	.L392
	cmp	r3, #255
	bhi	.L388
	add	r2, r3, #255
	uxtb	r0, lr
	add	r2, r8, r2
	b	.L390
.L391:
	cmp	r3, #256
	beq	.L388
.L390:
	add	r3, r3, #1
	strb	r0, [r2, #1]!
	cmp	r3, r1
	bne	.L391
.L392:
	add	lr, lr, #1
	add	r6, r6, #8
	cmp	lr, r9
	bne	.L387
.L377:
	mov	r0, #0
	b	.L373
.L381:
	ldr	r2, .L401+4
	mov	r0, #1
	ldr	r1, .L401+8
	bl	dprint_vfmw
	mvn	r0, #0
.L373:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L388:
	ldr	r2, .L401+4
	mov	r0, #1
	ldr	r1, .L401+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L373
.L400:
	mov	r1, #11
	mov	r3, r9
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L401+4
	ldr	r1, .L401+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L373
.L399:
	mov	r1, #10
	mov	r3, r7
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L401+4
	ldr	r1, .L401+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L373
.L402:
	.align	2
.L401:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+260
	.word	.LC54
	.word	.LC55
	.word	.LC53
	.word	.LC52
	UNWIND(.fnend)
	.size	HEVC_CalcTileInfo, .-HEVC_CalcTileInfo
	.align	2
	.global	HEVC_Sei_More_Data_In_Payload
	.type	HEVC_Sei_More_Data_In_Payload, %function
HEVC_Sei_More_Data_In_Payload:
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
	ldr	r2, [r0, #2796]
	mov	r5, r1
	ldr	r3, [r2, #24]
	mov	r0, r2
	ldr	r4, [r2, #28]
	rsb	r4, r4, r3
	bl	BsIsByteAligned
	cmp	r4, r5, asl #3
	movne	r3, #1
	moveq	r3, #0
	cmp	r0, #0
	moveq	r0, #0
	andne	r0, r3, #1
	eor	r0, r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_More_Data_In_Payload, .-HEVC_Sei_More_Data_In_Payload
	.align	2
	.global	HEVC_Sei_Payload_Extension_Present
	.type	HEVC_Sei_Payload_Extension_Present, %function
HEVC_Sei_Payload_Extension_Present:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	ldr	r3, .L411
	mov	r5, r1
	mov	r2, #32
	ldr	r1, [r0, #2796]
	sub	r0, fp, #52
	ldr	r3, [r3, #52]
	mov	r5, r5, asl #3
	blx	r3
	ldr	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	rsb	r3, r2, r3
	cmp	r3, r5
	movcs	r0, #0
	bcc	.L410
.L405:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L410:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r0, #0
	moveq	r0, #1
	beq	.L405
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
	b	.L406
.L407:
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
.L406:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r4, r5
	mov	r1, #1
	movcs	r3, #0
	movcc	r3, #1
	cmp	r0, #0
	movne	r2, #0
	andeq	r2, r3, #1
	sub	r0, fp, #52
	cmp	r2, #0
	bne	.L407
	mov	r0, r3
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L412:
	.align	2
.L411:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_Sei_Payload_Extension_Present, .-HEVC_Sei_Payload_Extension_Present
	.align	2
	.global	HEVC_Sei_Decoded_Picture_Hash
	.type	HEVC_Sei_Decoded_Picture_Hash, %function
HEVC_Sei_Decoded_Picture_Hash:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	beq	.L421
	mov	r1, #8
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r6, #3
	mov	r7, r0
.L420:
	cmp	r7, #0
	bne	.L415
	mov	r4, #16
.L416:
	mov	r1, #8
	ldr	r0, [r5, #2796]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L416
.L417:
	subs	r6, r6, #1
	bne	.L420
.L425:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L415:
	cmp	r7, #1
	beq	.L424
	cmp	r7, #2
	bne	.L417
	mov	r1, #32
	ldr	r0, [r5, #2796]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L420
	b	.L425
.L424:
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L420
	b	.L425
.L421:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Decoded_Picture_Hash, .-HEVC_Sei_Decoded_Picture_Hash
	.align	2
	.global	HEVC_Sei_Region_Refresh_Info
	.type	HEVC_Sei_Region_Refresh_Info, %function
HEVC_Sei_Region_Refresh_Info:
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
	cmp	r1, #0
	cmpne	r0, #0
	moveq	r4, #1
	movne	r4, #0
	beq	.L428
	mov	r1, #1
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L428:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Region_Refresh_Info, .-HEVC_Sei_Region_Refresh_Info
	.align	2
	.global	HEVC_Sei_Mastering_Display_Colour_Volume
	.type	HEVC_Sei_Mastering_Display_Colour_Volume, %function
HEVC_Sei_Mastering_Display_Colour_Volume:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	mov	r6, r1
	beq	.L432
	add	r7, r1, #12
	mov	r4, r1
	mov	r3, #1
	strb	r3, [r1]
.L431:
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #4]!
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r4, r7
	str	r0, [r4, #12]
	bne	.L431
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #28]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #32]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #36]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r3, #0
	str	r0, [r6, #40]
.L430:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L432:
	mvn	r3, #0
	b	.L430
	UNWIND(.fnend)
	.size	HEVC_Sei_Mastering_Display_Colour_Volume, .-HEVC_Sei_Mastering_Display_Colour_Volume
	.align	2
	.global	HEVC_Sei_Content_Light_Level_Information
	.type	HEVC_Sei_Content_Light_Level_Information, %function
HEVC_Sei_Content_Light_Level_Information:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r0
	mov	r5, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L436
	mov	r3, #1
	mov	r1, #16
	strb	r3, [r5]
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #16
	strh	r0, [r5, #2]	@ movhi
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r3, r4
	strh	r0, [r5, #4]	@ movhi
.L435:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L436:
	mvn	r3, #0
	b	.L435
	UNWIND(.fnend)
	.size	HEVC_Sei_Content_Light_Level_Information, .-HEVC_Sei_Content_Light_Level_Information
	.align	2
	.global	HEVC_Sei_HLGHDR_Comapitibility_Info
	.type	HEVC_Sei_HLGHDR_Comapitibility_Info, %function
HEVC_Sei_HLGHDR_Comapitibility_Info:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L439
	ldr	r0, [r0, #2796]
	mov	r1, #8
	bl	BsGet
	mov	r3, r4
	strb	r0, [r5]
.L438:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L439:
	mvn	r3, #0
	b	.L438
	UNWIND(.fnend)
	.size	HEVC_Sei_HLGHDR_Comapitibility_Info, .-HEVC_Sei_HLGHDR_Comapitibility_Info
	.align	2
	.global	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.type	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, %function
HEVC_Sei_Temporal_Sub_Layer_Zero_Index:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L442
	mov	r1, #1
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldr	r0, [r5, #2796]
	bl	BsToNextByte
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L442:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Temporal_Sub_Layer_Zero_Index, .-HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	.align	2
	.global	HEVC_Sei_Display_Orientation
	.type	HEVC_Sei_Display_Orientation, %function
HEVC_Sei_Display_Orientation:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	beq	.L446
	mov	r1, #1
	ldr	r0, [r0, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L447
.L445:
	ldr	r0, [r4, #2796]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L447:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L445
.L446:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_Sei_Display_Orientation, .-HEVC_Sei_Display_Orientation
	.align	2
	.global	HEVC_Sei_TSI
	.type	HEVC_Sei_TSI, %function
HEVC_Sei_TSI:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r0
	mov	r5, r1
	moveq	r4, #1
	movne	r4, #0
	beq	.L450
	mov	r1, #4
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #1]
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r3, r4
	mov	r2, #1
	strb	r2, [r5]
	strb	r0, [r5, #2]
.L449:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L450:
	mvn	r3, #0
	b	.L449
	UNWIND(.fnend)
	.size	HEVC_Sei_TSI, .-HEVC_Sei_TSI
	.align	2
	.global	HEVC_Sei_User_Data_Unregistered
	.type	HEVC_Sei_User_Data_Unregistered, %function
HEVC_Sei_User_Data_Unregistered:
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
	cmp	r2, #15
	mov	r6, r2
	mov	r5, r0
	movhi	r4, #16
	bls	.L460
.L454:
	mov	r1, #8
	ldr	r0, [r5, #2796]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L454
	subs	r6, r6, #16
	beq	.L456
.L455:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r6, r4
	bne	.L455
.L456:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L460:
	ldr	r1, .L461
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L462:
	.align	2
.L461:
	.word	.LC56
	UNWIND(.fnend)
	.size	HEVC_Sei_User_Data_Unregistered, .-HEVC_Sei_User_Data_Unregistered
	.align	2
	.global	HEVC_IsRefListWrong
	.type	HEVC_IsRefListWrong, %function
HEVC_IsRefListWrong:
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
	add	r7, r0, #4096
	mov	r5, r0
	ldr	r3, [r7, #764]
	cmp	r3, #0
	beq	.L464
	ldr	r4, [r0, #2856]
	cmp	r4, #0
	beq	.L465
	ldr	r2, [r4, #20]
	cmp	r2, #0
	addne	r6, r0, #2848
	movne	r4, #0
	addne	r6, r6, #8
	bne	.L470
	b	.L508
.L471:
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L472
	ldr	r3, [r7, #764]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L509
	ldr	r2, [r6, #4]!
	cmp	r2, #0
	beq	.L465
	ldr	r2, [r2, #20]
	cmp	r2, #0
	beq	.L466
.L470:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	bne	.L471
.L472:
	add	r3, r4, #712
	mov	r2, r4
	add	r3, r3, #2
	ldr	r1, .L513
	mov	r0, #1
	ldr	r3, [r5, r3, asl #2]
	ldr	r3, [r3, #20]
	str	ip, [sp]
	bl	dprint_vfmw
.L469:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L509:
	cmp	r3, #0
	beq	.L464
	ldr	r2, [r7, #768]
	cmp	r2, #0
	beq	.L464
	ldr	r4, [r5, #2924]
	cmp	r4, #0
	beq	.L477
	ldr	r2, [r4, #20]
	cmp	r2, #0
	addne	r6, r5, #2912
	movne	r4, #0
	addne	r6, r6, #12
	bne	.L481
	b	.L510
.L482:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L483
	ldr	r3, [r7, #768]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L464
	ldr	r3, [r6, #4]!
	cmp	r3, #0
	beq	.L511
	ldr	r2, [r3, #20]
	cmp	r2, #0
	beq	.L512
.L481:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L482
.L483:
	mov	r3, r0
	mov	r2, r4
	ldr	r1, .L513+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L503
.L464:
	mov	r0, #0
.L503:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L465:
	mov	r2, r4
	ldr	r1, .L513+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L469
.L508:
	mov	r4, r2
.L466:
	mov	r2, r4
	ldr	r1, .L513+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L469
.L511:
	ldr	r3, [r7, #764]
.L477:
	mov	r2, r4
	ldr	r1, .L513+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L503
.L512:
	ldr	r3, [r7, #764]
.L478:
	mov	r2, r4
	ldr	r1, .L513+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L503
.L510:
	mov	r4, r2
	b	.L478
.L514:
	.align	2
.L513:
	.word	.LC59
	.word	.LC62
	.word	.LC57
	.word	.LC58
	.word	.LC60
	.word	.LC61
	UNWIND(.fnend)
	.size	HEVC_IsRefListWrong, .-HEVC_IsRefListWrong
	.align	2
	.global	HEVC_GetUnRefPicWithMinPoc
	.type	HEVC_GetUnRefPicWithMinPoc, %function
HEVC_GetUnRefPicWithMinPoc:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mvn	r4, #0
	str	r4, [r1]
	ldr	r3, [r0, #3028]
	cmp	r3, #16
	bhi	.L516
	cmp	r3, #0
	addne	ip, r0, #3184
	mvnne	r4, #-2147483648
	addne	ip, ip, #8
	movne	r3, #0
	beq	.L518
.L521:
	ldr	r2, [ip, #4]!
	ldr	lr, [r2, #8]
	cmp	lr, r4
	bge	.L520
	ldr	r2, [r2]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	streq	r3, [r1]
	moveq	r4, lr
.L520:
	ldr	r2, [r0, #3028]
	add	r3, r3, #1
	cmp	r2, r3
	bhi	.L521
	ldr	r3, [r1]
	cmn	r3, #1
	beq	.L518
	str	r4, [sp]
	mov	r0, #1
	ldr	r2, .L524
	ldr	r1, .L524+4
	bl	dprint_vfmw
	mov	r0, #0
.L519:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L516:
	ldr	r2, .L524
	mov	r0, #1
	ldr	r1, .L524+8
	bl	dprint_vfmw
	mov	r0, r4
	b	.L519
.L518:
	ldr	r2, .L524
	mov	r0, #1
	ldr	r1, .L524+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L519
.L525:
	.align	2
.L524:
	.word	.LANCHOR0+280
	.word	.LC65
	.word	.LC63
	.word	.LC64
	UNWIND(.fnend)
	.size	HEVC_GetUnRefPicWithMinPoc, .-HEVC_GetUnRefPicWithMinPoc
	.align	2
	.global	HEVC_IncreaseDPBSize
	.type	HEVC_IncreaseDPBSize, %function
HEVC_IncreaseDPBSize:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, [r0, #3024]
	mov	r5, r0
	cmp	r3, #16
	bhi	.L530
	ldr	r0, [r0, #276]
	bl	FSP_GetTotalValidFsNum
	add	r3, r5, #4096
	ldr	r2, [r5, #276]
	ldr	r1, [r3, #24]
	mov	r4, r0
	ldr	r0, [r3, #20]
	bl	FSP_GetOccupiedNum
	rsb	r0, r0, r4
	bic	r2, r0, r0, asr #31
	cmp	r2, #0
	ble	.L529
	ldr	r3, [r5, #3024]
	add	r3, r3, #1
	cmp	r2, r3
	bcc	.L529
	str	r3, [r5, #3024]
	mov	r0, #13
	ldr	r2, .L531
	ldr	r1, .L531+4
	bl	dprint_vfmw
	mov	r0, #0
.L528:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L529:
	mov	r3, r2
	ldr	r1, .L531+8
	ldr	r2, .L531
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L528
.L530:
	mov	r4, #17
	ldr	r2, .L531
	mov	r0, #1
	str	r4, [sp]
	ldr	r1, .L531+12
	bl	dprint_vfmw
	str	r4, [r5, #3024]
	mvn	r0, #0
	b	.L528
.L532:
	.align	2
.L531:
	.word	.LANCHOR0+308
	.word	.LC67
	.word	.LC68
	.word	.LC66
	UNWIND(.fnend)
	.size	HEVC_IncreaseDPBSize, .-HEVC_IncreaseDPBSize
	.align	2
	.global	HEVC_PicTypeStatistic
	.type	HEVC_PicTypeStatistic, %function
HEVC_PicTypeStatistic:
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
	add	r0, r0, #4096
	ldr	r3, [r0, #724]
	sub	r2, r3, #16
	cmp	r2, #5
	bls	.L534
	ldr	r3, [r0, #4]
	sub	r3, r3, #16
	cmp	r3, #5
	bls	.L545
	ldr	r3, [r0, #716]
	cmp	r3, #1
	beq	.L537
	cmp	r3, #2
	beq	.L538
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
.L534:
	str	r3, [r0, #4]
	mov	r3, #0
	str	r3, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
.L537:
	ldr	r2, [r0, #16]
	cmp	r2, #2
	beq	.L546
	str	r3, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
.L538:
	ldr	r3, [r0, #16]
	sub	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	strhi	r3, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
.L546:
	ldmfd	sp, {fp, sp, pc}
.L545:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_PicTypeStatistic, .-HEVC_PicTypeStatistic
	.align	2
	.global	HEVC_IsReferenceNalu
	.type	HEVC_IsReferenceNalu, %function
HEVC_IsReferenceNalu:
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
	add	r0, r0, #4096
	ldr	r0, [r0, #724]
	cmp	r0, #15
	bhi	.L548
	tst	r0, #1
	bne	.L550
.L548:
	sub	r0, r0, #16
	cmp	r0, #7
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L550:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsReferenceNalu, .-HEVC_IsReferenceNalu
	.align	2
	.global	HEVC_WriteQmatrix_4x4
	.type	HEVC_WriteQmatrix_4x4, %function
HEVC_WriteQmatrix_4x4:
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
	add	r1, r1, r0, lsl #6
	ldr	r0, [r1, #628]
	ldr	r3, [r1, #632]
	ldrb	ip, [r1, #620]	@ zero_extendqisi2
	ldrb	lr, [r1, #624]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r0, r0
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r0
	str	r3, [r2]
	ldr	r0, [r1, #628]
	ldrb	lr, [r1, #621]	@ zero_extendqisi2
	ldrb	r3, [r1, #633]	@ zero_extendqisi2
	and	r0, r0, #65280
	ldrb	ip, [r1, #625]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #4]
	ldr	r0, [r1, #624]
	ldrb	lr, [r1, #622]	@ zero_extendqisi2
	ldrb	r3, [r1, #634]	@ zero_extendqisi2
	and	r0, r0, #16711680
	ldrb	ip, [r1, #630]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #8]
	ldr	r0, [r1, #632]
	ldrb	r3, [r1, #627]	@ zero_extendqisi2
	ldrb	lr, [r1, #623]	@ zero_extendqisi2
	and	r0, r0, #-16777216
	ldrb	ip, [r1, #631]	@ zero_extendqisi2
	orr	r1, lr, r0
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #12]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_4x4, .-HEVC_WriteQmatrix_4x4
	.align	2
	.global	HEVC_WriteQmatrix_32x32
	.type	HEVC_WriteQmatrix_32x32, %function
HEVC_WriteQmatrix_32x32:
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
	add	lr, r0, #18
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1780]
	ldr	r3, [r0, #1796]
	ldrb	ip, [lr, #620]	@ zero_extendqisi2
	ldrb	r4, [r0, #1788]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1812]
	ldr	r3, [r0, #1828]
	ldrb	ip, [r0, #1804]	@ zero_extendqisi2
	ldrb	r4, [r0, #1820]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1780]
	ldrb	r4, [lr, #621]	@ zero_extendqisi2
	ldrb	r3, [r0, #1797]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1789]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1812]
	ldrb	r4, [r0, #1805]	@ zero_extendqisi2
	ldrb	r3, [r0, #1829]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1821]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1788]
	ldrb	r4, [lr, #622]	@ zero_extendqisi2
	ldrb	r3, [r0, #1798]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1782]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1820]
	ldrb	r4, [r0, #1806]	@ zero_extendqisi2
	ldrb	r3, [r0, #1830]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1814]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1796]
	ldrb	lr, [lr, #623]	@ zero_extendqisi2
	ldrb	r3, [r0, #1791]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1783]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1828]
	ldrb	lr, [r0, #1807]	@ zero_extendqisi2
	ldrb	r3, [r0, #1823]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1815]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1784]
	ldr	r3, [r0, #1800]
	ldrb	ip, [r0, #1776]	@ zero_extendqisi2
	ldrb	lr, [r0, #1792]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1816]
	ldr	r3, [r0, #1832]
	ldrb	ip, [r0, #1808]	@ zero_extendqisi2
	ldrb	lr, [r0, #1824]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1784]
	ldrb	lr, [r0, #1777]	@ zero_extendqisi2
	ldrb	r3, [r0, #1801]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1793]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1816]
	ldrb	lr, [r0, #1809]	@ zero_extendqisi2
	ldrb	r3, [r0, #1833]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1825]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1792]
	ldrb	lr, [r0, #1778]	@ zero_extendqisi2
	ldrb	r3, [r0, #1802]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1786]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #1810]	@ zero_extendqisi2
	ldr	r1, [r0, #1824]
	ldrb	r3, [r0, #1834]	@ zero_extendqisi2
	ldrb	ip, [r0, #1818]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1800]
	ldrb	lr, [r0, #1779]	@ zero_extendqisi2
	ldrb	r3, [r0, #1795]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1787]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1832]
	ldrb	ip, [r0, #1811]	@ zero_extendqisi2
	ldrb	r3, [r0, #1827]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1819]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_32x32, .-HEVC_WriteQmatrix_32x32
	.align	2
	.global	HEVC_WriteQmatrix_8x8
	.type	HEVC_WriteQmatrix_8x8, %function
HEVC_WriteQmatrix_8x8:
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
	add	lr, r0, #6
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1020]
	ldr	r3, [r0, #1052]
	ldrb	ip, [lr, #620]	@ zero_extendqisi2
	ldrb	r4, [r0, #1036]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1028]
	ldr	r3, [r0, #1060]
	ldrb	ip, [r0, #1012]	@ zero_extendqisi2
	ldrb	r4, [r0, #1044]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1020]
	ldrb	r4, [lr, #621]	@ zero_extendqisi2
	ldrb	r3, [r0, #1053]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1037]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1028]
	ldrb	r4, [r0, #1013]	@ zero_extendqisi2
	ldrb	r3, [r0, #1061]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1045]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1036]
	ldrb	r4, [lr, #622]	@ zero_extendqisi2
	ldrb	r3, [r0, #1054]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1022]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1044]
	ldrb	r4, [r0, #1014]	@ zero_extendqisi2
	ldrb	r3, [r0, #1062]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1030]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1052]
	ldrb	lr, [lr, #623]	@ zero_extendqisi2
	ldrb	r3, [r0, #1039]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1023]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1060]
	ldrb	lr, [r0, #1015]	@ zero_extendqisi2
	ldrb	r3, [r0, #1047]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1031]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1024]
	ldr	r3, [r0, #1056]
	ldrb	ip, [r0, #1008]	@ zero_extendqisi2
	ldrb	lr, [r0, #1040]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1032]
	ldr	r3, [r0, #1064]
	ldrb	ip, [r0, #1016]	@ zero_extendqisi2
	ldrb	lr, [r0, #1048]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1024]
	ldrb	lr, [r0, #1009]	@ zero_extendqisi2
	ldrb	r3, [r0, #1057]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1041]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1032]
	ldrb	lr, [r0, #1017]	@ zero_extendqisi2
	ldrb	r3, [r0, #1065]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1049]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1040]
	ldrb	lr, [r0, #1010]	@ zero_extendqisi2
	ldrb	r3, [r0, #1058]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1026]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #1018]	@ zero_extendqisi2
	ldr	r1, [r0, #1048]
	ldrb	r3, [r0, #1066]	@ zero_extendqisi2
	ldrb	ip, [r0, #1034]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1056]
	ldrb	lr, [r0, #1011]	@ zero_extendqisi2
	ldrb	r3, [r0, #1043]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1027]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1064]
	ldrb	ip, [r0, #1019]	@ zero_extendqisi2
	ldrb	r3, [r0, #1051]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1035]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_8x8, .-HEVC_WriteQmatrix_8x8
	.align	2
	.global	HEVC_WriteQmatrix_16x16
	.type	HEVC_WriteQmatrix_16x16, %function
HEVC_WriteQmatrix_16x16:
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
	add	lr, r0, #12
	add	r0, r1, r0, lsl #6
	add	lr, r1, lr, lsl #6
	ldr	r1, [r0, #1396]
	ldr	r3, [r0, #1412]
	ldrb	ip, [lr, #620]	@ zero_extendqisi2
	ldrb	r4, [r0, #1404]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1428]
	ldr	r3, [r0, #1444]
	ldrb	ip, [r0, #1420]	@ zero_extendqisi2
	ldrb	r4, [r0, #1436]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1396]
	ldrb	r4, [lr, #621]	@ zero_extendqisi2
	ldrb	r3, [r0, #1413]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1405]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1428]
	ldrb	r4, [r0, #1421]	@ zero_extendqisi2
	ldrb	r3, [r0, #1445]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1437]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1404]
	ldrb	r4, [lr, #622]	@ zero_extendqisi2
	ldrb	r3, [r0, #1414]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1398]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1436]
	ldrb	r4, [r0, #1422]	@ zero_extendqisi2
	ldrb	r3, [r0, #1446]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1430]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1412]
	ldrb	lr, [lr, #623]	@ zero_extendqisi2
	ldrb	r3, [r0, #1407]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1399]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1444]
	ldrb	lr, [r0, #1423]	@ zero_extendqisi2
	ldrb	r3, [r0, #1439]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1431]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1400]
	ldr	r3, [r0, #1416]
	ldrb	ip, [r0, #1392]	@ zero_extendqisi2
	ldrb	lr, [r0, #1408]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1432]
	ldr	r3, [r0, #1448]
	ldrb	ip, [r0, #1424]	@ zero_extendqisi2
	ldrb	lr, [r0, #1440]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1400]
	ldrb	lr, [r0, #1393]	@ zero_extendqisi2
	ldrb	r3, [r0, #1417]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1409]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1432]
	ldrb	lr, [r0, #1425]	@ zero_extendqisi2
	ldrb	r3, [r0, #1449]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1441]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1408]
	ldrb	lr, [r0, #1394]	@ zero_extendqisi2
	ldrb	r3, [r0, #1418]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1402]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #1426]	@ zero_extendqisi2
	ldr	r1, [r0, #1440]
	ldrb	r3, [r0, #1450]	@ zero_extendqisi2
	ldrb	ip, [r0, #1434]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1416]
	ldrb	lr, [r0, #1395]	@ zero_extendqisi2
	ldrb	r3, [r0, #1411]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1403]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1448]
	ldrb	ip, [r0, #1427]	@ zero_extendqisi2
	ldrb	r3, [r0, #1443]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1435]	@ zero_extendqisi2
	orr	r1, ip, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, r0, asl #8
	str	r3, [r2, #60]
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix_16x16, .-HEVC_WriteQmatrix_16x16
	.align	2
	.global	HEVC_CtbRsAddrToTsAddr
	.type	HEVC_CtbRsAddrToTsAddr, %function
HEVC_CtbRsAddrToTsAddr:
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
	UNWIND(.pad #204)
	sub	sp, sp, #204
	ldr	ip, [r0, #2832]
	mov	r6, r1
	ldrb	r3, [ip, #13]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L590
	ldr	r3, [ip, #72]
	ldr	r7, [ip, #68]
	ldrb	r4, [ip, #15]	@ zero_extendqisi2
	mov	r2, r3
	str	r3, [fp, #-236]
	ldr	r3, [r0, #2828]
	cmp	r2, #0
	sub	r8, r2, #1
	sub	r2, r7, #1
	str	r2, [fp, #-240]
	ldr	r5, [r3, #64]
	ldr	r1, [r3, #128]
	ble	.L561
	ldr	r3, [fp, #-236]
	add	r2, ip, #210
	sub	r0, fp, #216
	add	lr, r3, #105
	add	lr, ip, lr, lsl #1
.L560:
	ldrsh	r3, [r2, #2]!
	cmp	r2, lr
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L560
.L561:
	cmp	r7, #0
	ble	.L559
	add	r3, r7, #85
	add	r2, ip, #170
	sub	r0, fp, #128
	add	ip, ip, r3, lsl #1
.L564:
	ldrsh	r3, [r2, #2]!
	cmp	r2, ip
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L564
.L559:
	mov	r10, #1
	mov	r0, r5
	mov	r10, r10, asl r1
	mov	r1, r10
	bl	__aeabi_idiv
	mov	r1, r10
	mov	r9, r0
	mov	r0, r5
	bl	__aeabi_idivmod
	mov	r0, r6
	cmp	r1, #0
	addne	r9, r9, #1
	mov	r1, r9
	bl	__aeabi_idivmod
	mov	r0, r6
	mov	r5, r1
	mov	r1, r9
	bl	__aeabi_idiv
	cmp	r4, #0
	beq	.L602
	cmp	r8, #0
	mov	r3, #0
	blt	.L581
	sub	r10, fp, #212
	mov	r4, r3
	mov	r6, r3
	mov	r8, r3
	str	r3, [fp, #-232]
	str	r3, [fp, #-244]
.L567:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L584
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	r1, r2
	add	r8, r8, #1
	sub	lr, fp, #128
	mov	r6, r4
	add	r9, r3, r8
	b	.L570
.L582:
	mov	r6, r4
.L570:
	ldr	r3, [lr, #4]!
	add	r1, r1, #1
	add	r3, r3, #1
	add	ip, r2, r3
	cmp	r5, ip
	mla	r4, r8, r3, r4
	bge	.L568
	cmp	r0, r9
	blt	.L600
.L568:
	cmp	r1, r7
	mov	r2, ip
	bne	.L582
.L573:
	add	r2, ip, r3
	cmp	r5, r2
	bge	.L583
	cmp	r0, r9
	blt	.L603
.L583:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	r1, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, r1
	str	r2, [fp, #-244]
	bne	.L567
	rsb	r0, r9, r0
	mov	r2, ip
	rsb	r2, r2, r5
	mul	r3, r0, r3
	add	r3, r2, r3
	add	r6, r3, r6
.L590:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L602:
	cmp	r8, #0
	mov	r3, r4
	blt	.L581
	sub	r10, fp, #212
	mov	lr, r4
	mov	r6, r4
	mov	r8, r4
	str	r4, [fp, #-232]
	str	r4, [fp, #-244]
.L566:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L587
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	ip, r2
	add	r8, r8, #1
	sub	r4, fp, #128
	mov	r6, lr
	add	r9, r3, r8
	b	.L576
.L585:
	mov	r6, lr
.L576:
	ldr	r3, [r4, #4]!
	add	ip, ip, #1
	add	r3, r3, #1
	add	r1, r2, r3
	cmp	r5, r1
	mla	lr, r8, r3, lr
	bge	.L574
	cmp	r0, r9
	blt	.L575
.L574:
	cmp	ip, r7
	mov	r2, r1
	bne	.L585
.L579:
	add	r2, r1, r3
	cmp	r5, r2
	bge	.L599
	cmp	r0, r9
	blt	.L604
.L599:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	ip, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, ip
	str	r2, [fp, #-244]
	bne	.L566
	rsb	r0, r9, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L565
.L600:
	ldr	r1, [fp, #-232]
	rsb	r0, r1, r0
	mul	r3, r0, r3
.L565:
	rsb	r2, r2, r5
	add	r3, r2, r3
	add	r6, r3, r6
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L575:
	cmp	r1, r5
	bgt	.L600
	mov	r1, r2
	b	.L599
.L584:
	ldr	r2, [fp, #-232]
	mov	ip, #0
	add	r9, r2, r8
	b	.L573
.L587:
	ldr	r2, [fp, #-232]
	mov	r1, #0
	add	r9, r2, r8
	b	.L579
.L603:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, ip
	mul	r3, r0, r3
	b	.L565
.L604:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L565
.L581:
	mov	r2, r3
	mov	r6, r3
	b	.L565
	UNWIND(.fnend)
	.size	HEVC_CtbRsAddrToTsAddr, .-HEVC_CtbRsAddrToTsAddr
	.align	2
	.global	HEVC_CtbTsAddrToRsAddr
	.type	HEVC_CtbTsAddrToRsAddr, %function
HEVC_CtbTsAddrToRsAddr:
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
	UNWIND(.pad #204)
	sub	sp, sp, #204
	ldr	lr, [r0, #2832]
	mov	r7, r1
	ldrb	r3, [lr, #13]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r0, r1
	beq	.L629
	ldr	r3, [lr, #72]
	ldr	r8, [lr, #68]
	mov	r2, r3
	str	r3, [fp, #-232]
	ldr	r3, [r0, #2828]
	cmp	r2, #0
	ldr	r4, [r3, #64]
	ldr	ip, [r3, #128]
	ble	.L611
	ldr	r3, [fp, #-232]
	add	r2, lr, #210
	sub	r1, fp, #216
	add	r0, r3, #105
	add	r0, lr, r0, lsl #1
.L610:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L610
.L611:
	cmp	r8, #0
	ble	.L609
	add	r0, r8, #85
	add	r2, lr, #170
	sub	r1, fp, #128
	add	r0, lr, r0, lsl #1
.L614:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L614
.L609:
	mov	r5, #1
	mov	r0, r4
	mov	r5, r5, asl ip
	mov	r1, r5
	bl	__aeabi_idiv
	mov	r1, r5
	mov	r6, r0
	mov	r0, r4
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-232]
	cmp	r1, #0
	addne	r6, r6, #1
	cmp	r3, #0
	str	r6, [fp, #-240]
	ble	.L613
	mov	r9, #0
	ldr	r2, [fp, #-124]
	sub	r0, fp, #212
	mov	r10, r9
	mov	r3, r9
	mov	r1, r9
	mov	r6, r9
	mov	r4, r9
	add	r2, r2, #1
	str	r2, [fp, #-236]
.L615:
	cmp	r8, #0
	ble	.L625
	ldr	r6, [r0]
	ldr	r4, [fp, #-236]
	add	r6, r6, #1
	mla	ip, r6, r4, r3
	cmp	r7, ip
	blt	.L626
	mov	r5, #0
	mov	r1, r3
	mov	r2, r5
	mov	r3, ip
	sub	lr, fp, #124
	b	.L620
.L617:
	ldr	r4, [lr, #4]!
	mov	r1, r3
	add	r4, r4, #1
	mla	ip, r6, r4, r3
	cmp	ip, r7
	bgt	.L618
	mov	r3, ip
.L620:
	add	r2, r2, #1
	add	r5, r5, r4
	cmp	r2, r8
	bne	.L617
.L619:
	cmp	r3, r7
	bgt	.L624
	ldr	r2, [fp, #-232]
	add	r10, r10, #1
	add	r9, r9, r6
	add	r0, r0, #4
	cmp	r10, r2
	bne	.L615
.L624:
	mov	r3, r1
.L618:
	cmp	r4, #0
	beq	.L613
	rsb	r7, r3, r7
	mov	r1, r4
	mov	r0, r7
	bl	__aeabi_idiv
	ldr	r3, [fp, #-240]
	mov	r1, r4
	add	r4, r0, r9
	mov	r0, r7
	mul	r4, r4, r3
	bl	__aeabi_idivmod
	add	r1, r1, r5
	add	r0, r4, r1
.L629:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L625:
	mov	r5, #0
	b	.L619
.L626:
	ldr	r4, [fp, #-236]
	mov	r5, #0
	b	.L618
.L613:
	ldr	r1, .L631
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L629
.L632:
	.align	2
.L631:
	.word	.LC69
	UNWIND(.fnend)
	.size	HEVC_CtbTsAddrToRsAddr, .-HEVC_CtbTsAddrToRsAddr
	.align	2
	.global	HEVC_CalcTileMap
	.type	HEVC_CalcTileMap, %function
HEVC_CalcTileMap:
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
	ldr	r4, .L656
	mov	r10, r0
	mov	r2, #147456
	mov	r1, #0
	ldr	r0, .L656+4
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #36864
	mov	r1, #0
	ldr	r0, .L656+8
	blx	r3
	add	r0, r10, #9216
	ldr	r3, [r4, #48]
	mov	r2, #880
	mov	r1, #0
	add	r0, r0, #4
	blx	r3
	add	r3, r10, #8192
	str	r3, [fp, #-56]
	mov	r2, r3
	mov	r3, #0
	str	r3, [r2, #1024]
	ldr	r9, [r10, #2832]
	ldr	r1, [r10, #2828]
	ldr	r2, [r9, #72]
	ldr	r8, [r1, #188]
	cmp	r2, r3
	strne	r3, [fp, #-68]
	strne	r3, [fp, #-72]
	beq	.L633
.L641:
	ldr	r2, [r9, #68]
	cmp	r2, #0
	ldr	r2, [fp, #-68]
	add	r2, r2, #104
	streq	r2, [fp, #-76]
	beq	.L642
	mov	r1, r2
	str	r2, [fp, #-76]
	mov	r7, r1, asl #1
	ldr	r1, [fp, #-72]
	mov	r2, #0
	str	r2, [fp, #-48]
	str	r2, [fp, #-52]
	mul	r1, r8, r1
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #1024]
	str	r1, [fp, #-64]
.L640:
	add	r1, r2, #1152
	add	r0, r9, r7
	add	r1, r10, r1, lsl #3
	str	r3, [r1, #4]
	ldrsh	r1, [r0, #4]
	cmp	r1, #0
	ldreq	r1, [fp, #-48]
	addeq	r1, r1, #84
	streq	r1, [fp, #-60]
	beq	.L636
	ldr	r2, [fp, #-48]
	mov	r5, #0
	ldr	r1, [fp, #-52]
	add	r2, r2, #84
	ldr	r0, [fp, #-64]
	str	r2, [fp, #-60]
	add	r6, r1, r0
	mov	ip, r2, asl #1
.L637:
	add	r2, r9, ip
	ldrsh	r2, [r2, #4]
	cmp	r2, #0
	beq	.L639
	ldr	r2, .L656+4
	rsb	lr, r3, r6
	mov	r4, r3
	add	r2, r2, r3, lsl #2
.L638:
	add	r1, lr, r3
	str	r1, [r2], #4
	ldr	r9, [r10, #2832]
	add	r3, r3, #1
	rsb	r1, r4, r3
	add	r0, r9, ip
	ldrsh	r0, [r0, #4]
	cmp	r0, r1
	bhi	.L638
.L639:
	add	r2, r9, r7
	add	r5, r5, #1
	add	r6, r6, r8
	ldrsh	r2, [r2, #4]
	cmp	r2, r5
	bhi	.L637
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #1024]
.L636:
	add	r1, r10, r2, lsl #3
	sub	ip, r3, #1
	add	r1, r1, #9216
	ldr	r0, [fp, #-60]
	ldr	lr, [fp, #-48]
	add	r2, r2, #1
	str	ip, [r1, #8]
	ldr	r1, [fp, #-56]
	add	r0, r9, r0, lsl #1
	add	lr, lr, #1
	str	lr, [fp, #-48]
	str	r2, [r1, #1024]
	ldr	ip, [r9, #68]
	ldrsh	r1, [r0, #4]
	cmp	ip, lr
	ldr	r0, [fp, #-52]
	add	r1, r0, r1
	str	r1, [fp, #-52]
	bhi	.L640
.L642:
	ldr	r2, [fp, #-76]
	ldr	r0, [fp, #-68]
	ldr	r1, [r9, #72]
	add	r2, r9, r2, lsl #1
	add	r0, r0, #1
	cmp	r1, r0
	ldr	r1, [fp, #-72]
	ldrsh	r2, [r2, #4]
	str	r0, [fp, #-68]
	add	r2, r1, r2
	str	r2, [fp, #-72]
	bhi	.L641
.L633:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L657:
	.align	2
.L656:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR2+448
	.word	.LANCHOR3+592
	UNWIND(.fnend)
	.size	HEVC_CalcTileMap, .-HEVC_CalcTileMap
	.align	2
	.global	HEVC_WritePicMsg
	.type	HEVC_WritePicMsg, %function
HEVC_WritePicMsg:
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
	add	r4, r0, #4096
	mov	r5, r0
	ldr	r1, .L681
	mov	r0, #2
	ldr	r3, [r4, #36]
	add	r6, r5, #8192
	ldr	r2, [r4, #212]
	mov	r7, #0
	bl	dprint_vfmw
	ldr	r1, .L681+4
	mov	r0, #4
	bl	dprint_vfmw
	ldr	r1, [r4, #176]
	ldr	ip, [r4, #180]
	mov	lr, #280
	ldr	r9, [r4, #36]
	add	r0, r5, #6592
	str	r1, [r4, #3720]
	mov	r2, #64
	str	ip, [r4, #3724]
	add	r0, r0, #56
	ldr	r1, [r4, #100]
	ldr	ip, [r4, #104]
	ldr	r8, [r4, #200]
	str	r9, [r4, #3716]
	rsb	ip, r1, ip
	ldr	r9, [r4, #108]
	str	ip, [r4, #3728]
	ldr	ip, [r4, #112]
	rsb	r1, r1, r9
	str	r8, [r4, #3732]
	ldr	r3, [r4, #8]
	rsb	r9, r9, ip
	ldr	r8, [r4, #204]
	ldr	ip, [r4, #208]
	ldr	r10, [r4, #212]
	str	r8, [r4, #3736]
	str	ip, [r4, #3740]
	str	r10, [r4, #3712]
	str	r1, [r4, #3744]
	str	r9, [r4, #3748]
	str	r3, [r4, #2456]
	ldr	r1, [r5, #2848]
	str	r7, [r5, #204]
	mul	r8, lr, r3
	str	r1, [r6, #820]
	ldr	ip, [r5, #2828]
	ldr	r7, .L681+8
	add	r1, r5, r8
	ldrb	r3, [ip, #10]	@ zero_extendqisi2
	add	r1, r1, #13248
	add	r1, r1, #36
	strb	r3, [r4, #2430]
	ldrb	r3, [ip, #3]	@ zero_extendqisi2
	strb	r3, [r4, #2431]
	ldrb	r3, [ip, #7]	@ zero_extendqisi2
	strb	r3, [r4, #2432]
	ldrb	r3, [ip, #6]	@ zero_extendqisi2
	ldr	lr, [r4, #12]
	strb	r3, [r4, #2433]
	ldrb	r3, [ip, #5]	@ zero_extendqisi2
	strb	r3, [r4, #2434]
	ldr	r3, [ip, #60]
	str	r3, [r4, #2436]
	ldr	r3, [ip, #104]
	strb	r3, [r4, #2440]
	ldr	r3, [ip, #192]
	sub	r3, r3, #1
	str	r3, [r4, #2444]
	ldr	r3, [ip, #188]
	str	lr, [r4, #2452]
	sub	r3, r3, #1
	str	r3, [r4, #2448]
	ldr	r3, [r5, #2832]
	ldr	lr, [r3, #84]
	sub	lr, lr, #2
	str	lr, [r4, #2460]
	ldrb	lr, [r3, #11]	@ zero_extendqisi2
	strb	lr, [r4, #2464]
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	strb	r3, [r4, #2465]
	ldr	r3, [ip, #164]
	str	r3, [r4, #2468]
	ldr	r3, [ip, #168]
	str	r3, [r4, #2472]
	ldr	r3, [ip, #156]
	str	r3, [r4, #2476]
	ldr	r3, [ip, #160]
	str	r3, [r4, #2480]
	ldr	r3, [ip, #148]
	str	r3, [r4, #2484]
	ldr	r3, [ip, #152]
	str	r3, [r4, #2488]
	ldr	lr, [ip, #172]
	ldr	r3, [r7, #52]
	str	lr, [r4, #2492]
	ldr	lr, [ip, #124]
	str	lr, [r4, #2496]
	ldr	lr, [ip, #128]
	str	lr, [r4, #2500]
	ldr	lr, [ip, #100]
	str	lr, [r4, #2504]
	ldr	lr, [ip, #92]
	str	lr, [r4, #2508]
	ldr	lr, [ip, #112]
	str	lr, [r4, #2512]
	ldr	lr, [ip, #108]
	str	lr, [r4, #2516]
	ldr	lr, [ip, #96]
	str	lr, [r4, #2520]
	ldr	ip, [ip, #88]
	str	ip, [r4, #2524]
	blx	r3
	ldr	ip, [r5, #2828]
	add	r3, r5, #8832
	add	r2, r5, #8768
	add	r1, r5, #8256
	add	r3, r3, #20
	ldr	lr, [ip, #68]
	add	r2, r2, #4
	add	r1, r1, #4
	mov	r0, r5
	str	lr, [r4, #2616]
	ldr	ip, [ip, #64]
	str	ip, [r4, #2620]
	bl	HEVC_CalcTileInfo
	subs	r7, r0, #0
	bne	.L679
	ldr	r3, [r5, #2832]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	strb	r2, [r4, #2644]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	strb	r2, [r4, #2645]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	strb	r2, [r4, #2646]
	ldrb	r2, [r3, #14]	@ zero_extendqisi2
	strb	r2, [r4, #2647]
	ldrb	r2, [r3, #15]	@ zero_extendqisi2
	strb	r2, [r4, #2648]
	ldrb	r2, [r3, #13]	@ zero_extendqisi2
	strb	r2, [r4, #2649]
	ldr	r2, [r5, #2828]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #128]
	rsb	r2, r1, r2
	str	r2, [r4, #2652]
	ldr	r2, [r3, #52]
	str	r2, [r4, #2656]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	strb	r2, [r4, #2660]
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	strb	r2, [r4, #2661]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	strb	r2, [r4, #2662]
	ldr	r2, [r3, #60]
	str	r2, [r4, #2664]
	ldr	r2, [r3, #64]
	str	r2, [r4, #2668]
	ldr	r2, [r3, #72]
	sub	r2, r2, #1
	str	r2, [r4, #2672]
	ldr	r2, [r3, #68]
	sub	r2, r2, #1
	str	r2, [r4, #2676]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	strb	r2, [r4, #2465]
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	strb	r3, [r4, #2464]
	ldr	r3, [r5, #2356]
	str	r7, [r5, #2372]
	cmp	r3, #1
	beq	.L670
	ldr	r3, [r4, #60]
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	subs	r9, r0, #0
	beq	.L680
	ldr	r2, [r9, #28]
	ldr	r3, [r9, #32]
	cmp	r2, #0
	beq	.L663
	cmp	r3, #0
	beq	.L663
	add	r3, r5, #8128
	add	r2, r5, #7808
	add	r1, r5, #7936
	add	r3, r3, #4
	add	r2, r2, #56
	add	r1, r1, #56
	ldr	r0, [r5, #276]
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r9, #28]
	add	r2, r5, #7936
	add	r1, r5, #8064
	add	r2, r2, #60
	add	r1, r1, #60
	ldr	r3, [r3, #4]
	str	r3, [r4, #3712]
	ldr	r0, [r5, #276]
	bl	FSP_GetPmvAddrTab
	ldr	r2, [r4, #36]
	add	r3, r5, r8
	add	r3, r3, #13120
	str	r2, [r4, #3716]
	ldr	r2, [r9, #12]
	str	r2, [r4, #4032]
	ldr	r2, [r9, #32]
	ldr	r2, [r2, #8]
	str	r2, [r6, #1016]
	ldr	r2, [r9, #32]
	ldr	r2, [r2, #60]
	str	r2, [r6, #1020]
	ldr	ip, [r3, #28]
	cmp	ip, #0
	str	ip, [r6, #812]
	beq	.L665
	add	r3, r8, #13184
	add	r2, r5, #8896
	add	r3, r3, #32
	add	r2, r2, #40
	add	r3, r5, r3
	mov	r0, r7
.L666:
	add	r0, r0, #1
	ldr	r1, [r3, #4]!
	cmp	r0, ip
	str	r1, [r2, #4]!
	bne	.L666
.L665:
	add	r7, r5, #6720
	mov	r6, #0
	add	r7, r7, #60
.L667:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_8x8
	cmp	r6, #4
	add	r7, r7, #64
	bne	.L667
	add	r2, r5, #6976
	mov	r0, r6
	add	r2, r2, #60
	mov	r1, r5
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r5, #7040
	add	r2, r2, #60
	mov	r1, r5
	mov	r0, #5
	add	r7, r5, #7232
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r5, #7104
	add	r2, r2, #60
	mov	r1, r5
	mov	r0, #0
	add	r7, r7, #60
	bl	HEVC_WriteQmatrix_16x16
	add	r2, r5, #7168
	add	r2, r2, #60
	mov	r1, r5
	mov	r0, #1
	mov	r6, #2
	bl	HEVC_WriteQmatrix_16x16
.L668:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_16x16
	cmp	r6, #6
	add	r7, r7, #64
	bne	.L668
	add	r2, r5, #7488
	mov	r1, r5
	add	r2, r2, #60
	mov	r0, #0
	bl	HEVC_WriteQmatrix_32x32
	add	r2, r5, #7552
	add	r2, r2, #60
	mov	r1, r5
	mov	r0, #1
	add	r7, r5, #7616
	bl	HEVC_WriteQmatrix_32x32
	add	r7, r7, #60
	mov	r6, #0
.L669:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r5
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_4x4
	cmp	r6, #6
	add	r7, r7, #16
	bne	.L669
	ldr	r1, [r5, #2308]
	mov	r0, #0
	ldr	r3, [r5, #2312]
	ldr	r2, [r5, #2300]
	ldr	ip, [r5, #2304]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	ldr	lr, [r4, #36]
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #3676]
	ldr	r1, [r5, #2324]
	ldr	r3, [r5, #2328]
	ldr	r2, [r5, #2316]
	ldr	ip, [r5, #2320]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	str	lr, [r4, #3708]
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r4, #3680]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L670:
	mov	r0, r7
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L679:
	ldr	r2, .L681+12
	mov	r0, #1
	ldr	r1, .L681+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L663:
	ldr	r1, .L681+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L680:
	ldr	r3, [r4, #60]
	mov	r0, #1
	ldr	r1, .L681+24
	ldr	r2, [r3, #28]
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L682:
	.align	2
.L681:
	.word	.LC70
	.word	.LC71
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+332
	.word	.LC72
	.word	.LC74
	.word	.LC73
	UNWIND(.fnend)
	.size	HEVC_WritePicMsg, .-HEVC_WritePicMsg
	.align	2
	.global	HEVC_CheckListX
	.type	HEVC_CheckListX, %function
HEVC_CheckListX:
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
	add	r3, r0, #4096
	ldrb	r3, [r3, #697]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r3, r0, #4736
	addeq	r3, r3, #56
	beq	.L685
	ldrsb	r3, [r0, #14]
	cmp	r3, #0
	addne	r3, r0, #11712
	addne	r3, r3, #60
	beq	.L718
.L685:
	ldr	ip, [r3, #68]
	ldr	lr, [r3, #72]
	cmp	ip, #16
	bhi	.L719
	cmp	lr, #16
	bhi	.L689
	cmp	ip, #0
	beq	.L690
	ldr	r3, [r0, #2856]
	cmp	r3, #0
	beq	.L703
	ldr	r3, [r3, #20]
	cmp	r3, #0
	addne	r1, r0, #2848
	movne	r2, #0
	addne	r1, r1, #8
	bne	.L695
	b	.L720
.L696:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L691
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L692
.L695:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L696
.L690:
	cmp	lr, #0
	beq	.L715
	ldr	r3, [r0, #2924]
	cmp	r3, #0
	beq	.L706
	ldr	r3, [r3, #20]
	cmp	r3, #0
	addne	r0, r0, #2912
	movne	r2, #0
	addne	r0, r0, #12
	bne	.L701
	b	.L721
.L702:
	ldr	r3, [r0, #4]!
	cmp	r3, #0
	beq	.L697
	ldr	r3, [r3, #20]
	cmp	r3, #0
	beq	.L698
.L701:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L702
.L715:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L703:
	mov	r2, r3
.L691:
	ldr	r1, .L722
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L720:
	mov	r2, r3
.L692:
	ldr	r1, .L722+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L706:
	mov	r2, r3
.L697:
	ldr	r1, .L722+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L721:
	mov	r2, r3
.L698:
	ldr	r1, .L722+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L718:
	mov	r0, r3
	ldr	r2, .L722+16
	ldr	r1, .L722+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L689:
	mov	r2, lr
	mov	r3, #17
	ldr	r1, .L722+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L719:
	mov	r2, ip
	mov	r3, #17
	ldr	r1, .L722+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L723:
	.align	2
.L722:
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LANCHOR0+352
	.word	.LC75
	.word	.LC77
	.word	.LC76
	UNWIND(.fnend)
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.align	2
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	add	r9, r0, #4096
	mov	r4, r0
	ldr	r8, [r9, #8]
	bl	HEVC_CheckListX
	subs	r3, r0, #0
	str	r3, [fp, #-116]
	bne	.L794
	ldr	r0, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r0, r3
	bcs	.L868
	ldr	r5, [r4, #2848]
	movw	r6, #1508
	ldr	r10, [fp, #-116]
	mov	r2, r6
	ldr	r3, .L876
	mla	r5, r6, r0, r5
	mov	r1, r10
	ldr	r3, [r3, #48]
	mov	r0, r5
	blx	r3
	ldr	r3, .L876
	mov	r2, #64
	mov	r1, r10
	sub	r0, fp, #108
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	add	r3, r3, #1
	str	r3, [r4, #204]
	cmp	r3, r2
	ldrcc	r2, [r4, #2848]
	ldrcs	r3, [fp, #-116]
	mlacc	r3, r6, r3, r2
	str	r3, [r5, #1504]
	ldr	r1, [r9, #732]
	ldr	r2, [r4, #2816]
	ldr	r0, [r4, #176]
	ldr	r3, [r4, #260]
	add	r0, r0, #1
	str	r1, [r4, #208]
	str	r0, [r4, #176]
	add	r3, r3, #1
	str	r3, [r4, #260]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	str	r0, [fp, #-120]
	cmp	r1, #1
	cmpls	r1, r3
	bcs	.L729
	add	r0, r5, r1, lsl #2
.L730:
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r1, r1, #1
	add	r2, r2, r3
	ldr	r2, [r2, #56]
	str	r2, [r0, #8]
	ldr	r2, [r4, #2816]
	add	r2, r2, r3
	ldr	r2, [r2, #52]
	str	r2, [r0], #4
	ldr	r2, [r4, #2816]
	add	r3, r2, r3
	ldr	r3, [r3, #60]
	str	r3, [r0, #12]
	ldr	r2, [r4, #2816]
	ldr	r3, [r2, #8]
	cmp	r3, r1
	movhi	ip, #1
	movls	ip, #0
	cmp	r1, #1
	movhi	ip, #0
	cmp	ip, #0
	bne	.L730
.L729:
	cmp	r3, #1
	addls	r3, r5, r3, lsl #2
	addls	r1, r5, #8
	movls	r2, #0
	bhi	.L735
.L734:
	str	r2, [r3, #8]
	str	r2, [r3], #4
	cmp	r3, r1
	str	r2, [r3, #12]
	bne	.L734
.L735:
	ldrb	r3, [r9, #697]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L869
.L733:
	add	r3, r4, #8192
	str	r3, [fp, #-112]
	mov	r6, r3
	ldr	r3, [r3, #3648]
	cmp	r3, #0
	beq	.L736
	add	r1, r4, #2848
	add	r0, r5, #112
	add	r1, r1, #4
	mov	ip, #0
	mov	lr, #1
	b	.L740
.L871:
	ldr	r3, [r10, #16]
	cmp	r3, #0
	beq	.L738
	ldr	r3, [r9, #728]
	cmp	r3, #0
	beq	.L738
	ldr	r2, [r10, #20]
	sub	r7, fp, #44
	add	ip, ip, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #36]
	add	r3, r3, #1984
	add	r3, r3, #14
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r10, #20]
	ldr	r3, [r3, #36]
	str	r3, [r0, #256]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	strne	lr, [r0]
	ldr	r2, [r6, #3648]
	cmp	r2, ip
	bls	.L870
.L740:
	ldr	r3, [r1, #4]!
	ldr	r3, [r3, #4]
	str	r3, [r0, #4]!
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldr	r10, [r1]
	cmp	r3, #0
	bne	.L871
.L738:
	ldr	r2, [r10, #20]
	sub	r7, fp, #44
	add	ip, ip, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #24]
	add	r3, r3, #1984
	add	r3, r3, #14
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r10, #20]
	ldr	r3, [r3, #24]
	str	r3, [r0, #256]
	ldr	r2, [r6, #3648]
	cmp	r2, ip
	bhi	.L740
.L870:
	ldr	r0, [r6, #3652]
	str	r6, [fp, #-112]
	cmp	r0, #0
	beq	.L741
.L793:
	add	r1, r4, #2912
	add	ip, r5, #176
	add	r1, r1, #8
	mov	lr, #0
	mov	r10, #1
	ldr	r6, [fp, #-112]
	b	.L745
.L873:
	ldr	r3, [r0, #16]
	cmp	r3, #0
	beq	.L743
	ldr	r3, [r9, #728]
	cmp	r3, #0
	beq	.L743
	ldr	r2, [r0, #20]
	sub	r7, fp, #44
	add	lr, lr, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #36]
	add	r3, r3, #1984
	add	r3, r3, #14
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #20]
	ldr	r3, [r3, #36]
	str	r3, [ip, #256]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	strne	r10, [ip]
	ldr	r0, [r6, #3652]
	cmp	r0, lr
	bls	.L872
.L745:
	ldr	r3, [r1, #4]!
	ldr	r3, [r3, #4]
	str	r3, [ip, #4]!
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldr	r0, [r1]
	cmp	r3, #0
	bne	.L873
.L743:
	ldr	r2, [r0, #20]
	sub	r7, fp, #44
	add	lr, lr, #1
	ldr	r3, [r2, #20]
	ldr	r2, [r2, #24]
	add	r3, r3, #1984
	add	r3, r3, #14
	add	r2, r7, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r2, #-64]
	ldr	r3, [r0, #20]
	ldr	r3, [r3, #24]
	str	r3, [ip, #256]
	ldr	r0, [r6, #3652]
	cmp	r0, lr
	bhi	.L745
.L872:
	ldr	r2, [r6, #3648]
	str	r6, [fp, #-112]
.L741:
	cmp	r2, #0
	beq	.L746
	mov	lr, #70
	ldr	r3, [r5, #372]
	mul	lr, lr, r8
	ldr	r10, [r9, #12]
	add	r3, lr, r3
	add	r3, r3, #3312
	add	r3, r3, #8
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r10, r3
	blt	.L865
	add	ip, r5, #372
	mov	r1, #0
	ldr	r6, [fp, #-112]
	b	.L748
.L749:
	ldr	r3, [ip, #4]!
	add	r3, lr, r3
	add	r3, r3, #3312
	add	r3, r3, #8
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, r10
	bgt	.L800
.L748:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L749
	str	r6, [fp, #-112]
.L746:
	ldr	r3, [fp, #-112]
	ldr	r2, [r3, #3600]
	cmp	r2, #0
	bne	.L866
	cmp	r0, #0
	beq	.L866
	mov	r1, #70
	ldr	r3, [r5, #436]
	mul	r8, r1, r8
	ldr	ip, [r9, #12]
	add	r3, r8, r3
	add	r3, r3, #3312
	add	r3, r3, #8
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	ip, r3
	blt	.L747
	add	r1, r5, #436
	ldr	r6, [fp, #-112]
	b	.L750
.L751:
	ldr	r3, [r1, #4]!
	add	r3, r8, r3
	add	r3, r3, #3312
	add	r3, r3, #8
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, ip
	bgt	.L800
.L750:
	add	r2, r2, #1
	cmp	r2, r0
	bne	.L751
	str	r6, [fp, #-112]
	mov	r2, #1
	b	.L747
.L800:
	str	r6, [fp, #-112]
.L865:
	mov	r2, #0
.L747:
	strb	r2, [r5, #24]
	ldr	r1, [fp, #-112]
	ldrb	r3, [r9, #697]	@ zero_extendqisi2
	strb	r3, [r5, #25]
	ldr	r3, [r1, #3596]
	str	r3, [r5, #28]
	ldrb	r2, [r1, #3587]	@ zero_extendqisi2
	strb	r2, [r5, #32]
	ldr	r2, [r1, #3620]
	str	r2, [r5, #36]
	ldr	r2, [r4, #2356]
	cmp	r2, #0
	bne	.L752
	ldr	r8, [r9, #60]
	ldr	r1, [r4, #204]
	ldr	r0, [r8, #316]
	sub	r2, r1, #1
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	str	r0, [r8, #68]
.L752:
	ldr	r3, [fp, #-112]
	ldr	r3, [r3, #3600]
	cmp	r3, #0
	bne	.L753
	ldr	r3, [fp, #-112]
	ldrb	r3, [r3, #3588]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L754
	ldr	r3, [fp, #-112]
	ldr	r3, [r3, #3624]
	add	r3, r5, r3, lsl #2
	ldr	r8, [r3, #436]
.L755:
	ldr	r2, [fp, #-112]
	str	r8, [r5, #40]
	ldr	r6, [fp, #-112]
	ldr	r3, [r2, #3624]
	str	r3, [r5, #48]
	ldrb	r3, [r2, #3588]	@ zero_extendqisi2
	strb	r3, [r5, #52]
	ldr	r3, [r2, #3628]
	str	r3, [r5, #44]
	ldr	r3, [r2, #3656]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r5, #60]
	ldr	r3, [fp, #-112]
	ldr	r3, [r3, #3660]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r5, #56]
	ldrb	r3, [r6, #3584]	@ zero_extendqisi2
	strb	r3, [r5, #64]
	ldrb	r3, [r6, #3586]	@ zero_extendqisi2
	strb	r3, [r5, #65]
	ldr	r3, [r6, #3648]
	str	r3, [r5, #68]
	ldr	r3, [r6, #3652]
	str	r3, [r5, #72]
	ldr	r3, [r6, #3600]
	str	r3, [r5, #76]
	ldr	r3, [r9, #736]
	str	r3, [r5, #80]
	ldr	r3, [r4, #2828]
	ldr	r0, [r9, #736]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidivmod
	str	r1, [r5, #84]
	ldr	r3, [r4, #2828]
	ldr	r0, [r9, #736]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidiv
	str	r0, [r5, #88]
	mov	r0, r4
	ldr	r1, [r9, #736]
	bl	HEVC_CtbRsAddrToTsAddr
	str	r0, [r5, #92]
	ldr	r3, [r6, #3632]
	str	r3, [r5, #96]
	ldr	r3, [r6, #3636]
	str	r3, [r5, #100]
	ldr	r3, [r6, #3644]
	str	r3, [r5, #104]
	ldr	r3, [r6, #3640]
	str	r3, [r5, #108]
	ldrb	r3, [r6, #3583]	@ zero_extendqisi2
	strb	r3, [r5, #112]
	ldrb	r3, [r6, #3582]	@ zero_extendqisi2
	strb	r3, [r5, #113]
	ldrb	r3, [r6, #3589]	@ zero_extendqisi2
	strb	r3, [r5, #114]
	ldrb	r3, [r6, #3590]	@ zero_extendqisi2
	strb	r3, [r5, #115]
	ldr	r3, [r4, #2832]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L760
	ldr	r2, [fp, #-112]
	ldr	r2, [r2, #3600]
	cmp	r2, #1
	beq	.L761
.L760:
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L874
.L763:
	ldr	r3, [fp, #-112]
	ldrb	r3, [r3, #3584]	@ zero_extendqisi2
	cmp	r3, #0
	subne	r3, fp, #44
	addne	r8, r3, r8, lsl #2
	ldreq	r3, [r9, #3900]
	ldrne	r3, [r8, #-64]
	str	r3, [r5, #564]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L767
	ldr	r3, [r9, #728]
	cmp	r3, #0
	beq	.L767
	ldr	r8, [r4, #2848]
	ldr	lr, [r5, #68]
	cmp	r5, r8
	moveq	r3, #0
	streq	r3, [r5, #1360]
	streqb	r3, [r5, #1356]
	cmp	lr, #0
	beq	.L771
	add	r1, r4, #2848
	ldr	r6, [fp, #-112]
	mov	ip, #0
	add	r1, r1, #4
	mov	r3, ip
.L773:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldr	r2, [r2, #20]
	ldr	r0, [r2, #32]
	cmp	r0, #0
	addeq	ip, r2, #80
	cmp	r3, lr
	bne	.L773
	cmp	ip, #0
	str	r6, [fp, #-112]
	beq	.L771
.L774:
	ldr	r3, [r5, #40]
	ldr	r2, [r9, #20]
	add	r3, r4, r3
	add	r3, r3, #13632
	add	r3, r3, #56
	str	r2, [fp, #-140]
	ldr	r2, [r9, #24]
	ldrsb	r3, [r3, #4]
	cmp	r3, #0
	str	r2, [fp, #-144]
	moveq	r3, #1
	movne	r3, #0
	cmp	ip, #0
	strb	r3, [r5, #1357]
	beq	.L779
	ldr	r3, [ip, #168]
	ldr	r0, [ip, #68]
	ldr	r2, [ip, #72]
	str	r3, [r8, #1468]
	ldr	r3, [ip, #172]
	mov	r6, r2
	str	r2, [fp, #-136]
	ldr	r7, [fp, #-140]
	str	r3, [r8, #1472]
	ldr	r3, [ip, #112]
	str	r0, [fp, #-124]
	str	r3, [r8, #1476]
	ldr	r2, [ip, #20]
	ldr	r3, [ip, #24]
	rsb	r3, r2, r3
	str	r3, [r8, #1480]
	ldr	r3, [ip, #140]
	str	r3, [r8, #1484]
	ldr	r3, [ip, #144]
	str	r3, [r8, #1488]
	ldr	r2, [ip, #20]
	ldr	r3, [ip, #44]
	rsb	r3, r2, r3
	str	r3, [r8, #1492]
	ldr	r2, [ip, #44]
	ldr	r3, [ip, #48]
	rsb	r3, r2, r3
	str	r3, [r8, #1496]
	ldr	r10, [r4, #2832]
	ldr	r3, [r10, #2984]
	ldr	r2, [r10, #3496]
	ldr	r1, [r10, #1960]
	sub	r3, r0, r3, asl #1
	ldr	r0, [r10, #2472]
	sub	lr, r3, r2, asl #1
	str	lr, [fp, #-148]
	sub	r1, r7, r1, asl #1
	ldr	ip, [r10, #3240]
	mov	r3, lr, asr #31
	sub	r1, r1, r0, asl #1
	ldr	lr, [r10, #3752]
	mov	r3, r3, asl #16
	str	r1, [fp, #-160]
	mov	r0, r1
	mov	r2, r3
	ldr	r3, [fp, #-148]
	orr	r2, r2, r3, lsr #16
	mov	r3, r3, asl #16
	str	r3, [fp, #-132]
	sub	r3, r6, ip, asl #1
	sub	ip, r3, lr, asl #1
	ldr	lr, [r10, #2216]
	ldr	r3, [fp, #-144]
	str	r2, [fp, #-128]
	mov	r2, r1
	sub	r3, r3, lr, asl #1
	ldr	lr, [r10, #2728]
	ldrd	r6, [fp, #-132]
	mov	r1, r1, asr #31
	movs	r1, r1, lsr #1
	mov	r0, r0, rrx
	str	ip, [fp, #-152]
	adds	r6, r6, r0
	sub	lr, r3, lr, asl #1
	ldr	r3, .L876
	adc	r7, r7, r1
	mov	r0, r6
	str	lr, [fp, #-132]
	mov	r1, r7
	mov	r6, ip
	ldr	r3, [r3, #236]
	blx	r3
	mov	r1, r6, asr #31
	ldr	lr, [fp, #-132]
	mov	ip, r6, asl #16
	mov	r1, r1, asl #16
	ldr	r3, .L876
	mov	r7, r1
	mov	r1, lr, asr #31
	ldr	r3, [r3, #236]
	mov	r2, lr
	str	r0, [fp, #-156]
	mov	r0, lr
	strd	r0, [fp, #-172]
	orr	r1, r7, r6, lsr #16
	mov	r7, r1
	ldrd	r0, [fp, #-172]
	movs	r1, r1, lsr #1
	mov	r0, r0, rrx
	adds	r6, ip, r0
	adc	r7, r7, r1
	mov	r0, r6
	mov	r1, r7
	blx	r3
	ldr	r7, [fp, #-140]
	mov	ip, r0
	ldr	r0, [fp, #-124]
	cmp	r7, r0
	bgt	.L780
	ldr	r3, [fp, #-156]
	cmp	r3, #65536
	movgt	r7, #0
	movle	r7, #1
.L781:
	ldr	r3, [fp, #-144]
	ldr	r2, [fp, #-136]
	cmp	r3, r2
	bgt	.L782
	cmp	ip, #65536
	movgt	r2, #0
	movle	r2, #1
.L783:
	ldr	r3, [fp, #-124]
	cmp	r7, #0
	orrne	r7, r2, r7
	str	ip, [r8, #1384]
	strne	r7, [r8, #1360]
	str	r3, [r8, #1364]
	ldr	r3, [fp, #-136]
	str	ip, [r8, #1392]
	str	r3, [r8, #1368]
	mov	r3, #1
	strb	r3, [r8, #1356]
	ldr	r3, [fp, #-156]
	str	r3, [r8, #1380]
	str	r3, [r8, #1388]
	ldrb	r7, [r10, #1890]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L785
	ldr	r3, [fp, #-152]
	add	r0, r10, #4096
	ldr	r1, [r10, #4008]
	ldr	lr, [fp, #-156]
	mov	r3, r3, asr #1
	str	r1, [r8, #1428]
	mov	r6, r3
	ldr	r3, [r0, #168]
	mul	r1, r1, lr
	str	r3, [r8, #1432]
	ldr	r2, [r0, #424]
	mul	r3, r3, ip
	sub	r2, r2, #8
	str	r2, [r8, #1436]
	add	r1, r1, #8
	mul	r2, r2, lr
	add	r3, r3, #8
	mov	r1, r1, asr #4
	ldr	r0, [r0, #680]
	mov	lr, r3, asr #4
	rsb	r1, r1, #0
	add	r3, r2, #8
	rsb	r2, lr, #0
	sub	r0, r0, #8
	str	r0, [r8, #1440]
	mov	r3, r3, asr #4
	rsb	r3, r3, #0
.L786:
	mul	ip, r0, ip
	ldr	lr, [fp, #-148]
	str	r1, [r8, #1444]
	mov	r7, #61440
	ldr	r1, [fp, #-160]
	movt	r7, 65535
	add	ip, ip, #8
	mov	r0, lr, asr #1
	str	r3, [r8, #1452]
	mov	ip, ip, asr #4
	add	r0, r0, r1, lsl #8
	rsb	ip, ip, #0
	mov	r1, lr
	str	ip, [r8, #1456]
	str	r2, [r8, #1448]
	movw	r2, #4095
	str	r2, [fp, #-140]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-140]
	ldr	r1, [fp, #-152]
	cmp	r0, r2
	movge	ip, r2
	ldr	r2, [fp, #-132]
	movlt	ip, r0
	cmp	ip, r7
	add	r0, r6, r2, lsl #8
	movlt	ip, r7
	str	ip, [r8, #1460]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-140]
	mov	r1, #1
	cmp	r0, r2
	movge	r0, r2
	cmp	r0, r7
	movlt	r0, r7
	str	r0, [r8, #1464]
	ldr	r2, [r10, #1960]
	ldr	r0, [fp, #-136]
	mov	r2, r2, asl r1
	str	r2, [r8, #1396]
	ldr	r3, [r10, #2216]
	mov	r2, r2, asr r1
	str	r2, [r8, #1404]
	mov	r3, r3, asl r1
	str	r3, [r8, #1400]
	mov	r3, r3, asr r1
	str	r3, [r8, #1408]
	ldr	r2, [r10, #2984]
	mov	r2, r2, asl r1
	str	r2, [r8, #1412]
	ldr	r3, [r10, #3240]
	mov	r2, r2, asr r1
	str	r2, [r8, #1420]
	mov	r3, r3, asl r1
	str	r3, [r8, #1416]
	mov	r3, r3, asr r1
	str	r3, [r8, #1424]
	ldr	r3, [r4, #2828]
	ldr	r2, [r3, #128]
	ldr	r3, [fp, #-124]
	mov	r2, r1, asl r2
	sub	r1, r2, #1
	rsb	r2, r2, #0
	add	r3, r3, r1
	add	r1, r0, r1
	and	r3, r3, r2
	and	r2, r2, r1
	str	r3, [r8, #1372]
	str	r2, [r8, #1376]
.L779:
	add	ip, r4, #12288
	mov	r2, #0
	str	r2, [r5, #1500]
	ldr	r3, [ip, #1140]
	cmp	r3, r2
	beq	.L769
	add	r1, r4, #13632
	ldr	r6, [fp, #-112]
	add	r1, r1, #59
	mov	r3, r2
.L788:
	ldrsb	r0, [r1, #1]!
	orr	r2, r2, r0, asl r3
	str	r2, [r5, #1500]
	ldr	r0, [ip, #1140]
	add	r3, r3, #1
	cmp	r3, r0
	bcc	.L788
	str	r6, [fp, #-112]
	b	.L769
.L736:
	ldr	r3, [fp, #-112]
	ldr	r3, [r3, #3652]
	cmp	r3, #0
	bne	.L793
.L866:
	mov	r2, #1
	b	.L747
.L753:
	cmp	r3, #1
	movne	r8, #0
	bne	.L755
.L754:
	ldr	r3, [fp, #-112]
	ldr	r3, [r3, #3624]
	add	r3, r5, r3, lsl #2
	ldr	r8, [r3, #372]
	b	.L755
.L767:
	mov	r3, #0
	mov	r2, #1
	str	r3, [r5, #1360]
	strb	r3, [r5, #1356]
	strb	r2, [r5, #1357]
.L769:
	ldr	r3, [r4, #2356]
	cmp	r3, #0
	ldreq	r1, [r4, #2816]
	ldreq	r2, [r4, #2836]
	ldreq	r0, [fp, #-120]
	streq	r1, [r2, r0, asl #2]
	streq	r3, [r4, #2816]
	ldrb	r3, [r9, #2649]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L825
	ldr	r3, [r4, #260]
	cmp	r3, #1
	beq	.L875
	add	r1, r4, r3, lsl #3
	ldr	r0, [r5, #92]
	add	r1, r1, #10048
	add	r2, r3, #1248
	add	r2, r2, #13
	sub	r0, r0, #1
	str	r0, [r1, #40]
	sub	r3, r3, #1
	ldr	r1, [r5, #92]
	add	r2, r4, r2, lsl #3
	str	r1, [r2, #4]
.L792:
	ldr	r1, [r9, #2448]
	add	r3, r4, r3, lsl #3
	ldr	r2, [r9, #2444]
	add	r3, r3, #10048
	mla	r2, r1, r2, r2
	add	r2, r2, r1
	str	r2, [r3, #56]
	ldr	r1, [r5, #92]
	sub	r1, r1, #1
	cmp	r1, #36864
	bcs	.L825
	mov	r0, r4
	bl	HEVC_CtbTsAddrToRsAddr
	str	r0, [r5, #568]
.L825:
	ldr	r0, [fp, #-116]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L869:
	ldr	r3, .L876
	add	r1, r4, #4736
	add	r0, r4, #11712
	add	r1, r1, #56
	add	r0, r0, #60
	mov	r2, #1376
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #1
	strb	r3, [r4, #14]
	b	.L733
.L874:
	ldr	r3, [fp, #-112]
	ldr	r3, [r3, #3600]
	cmp	r3, #0
	bne	.L763
.L761:
	ldr	r6, [fp, #-112]
	add	r1, r4, #12032
	ldr	r3, .L876
	add	r1, r1, #32
	ldr	r10, .L876
	mov	r2, #64
	ldr	ip, [r6, #3736]
	add	r0, r5, #588
	ldr	r3, [r3, #52]
	str	ip, [r5, #580]
	ldr	ip, [r6, #3868]
	str	ip, [r5, #584]
	blx	r3
	add	r1, r4, #11904
	add	r1, r1, #28
	ldr	r3, [r10, #52]
	mov	r2, #64
	add	r0, r5, #716
	blx	r3
	add	r1, r4, #12096
	add	r1, r1, #32
	ldr	r3, [r10, #52]
	mov	r2, #128
	add	r0, r5, #844
	blx	r3
	add	r1, r4, #12224
	add	r0, r5, #1088
	ldr	r3, [r10, #52]
	add	r1, r1, #32
	add	r0, r0, #12
	mov	r2, #128
	blx	r3
	ldr	r3, [r6, #3600]
	cmp	r3, #0
	bne	.L763
	add	r1, r4, #12352
	ldr	r3, [r10, #52]
	add	r1, r1, #32
	mov	r2, #64
	add	r0, r5, #652
	blx	r3
	add	r1, r4, #11968
	ldr	r3, [r10, #52]
	add	r1, r1, #28
	mov	r2, #64
	add	r0, r5, #780
	blx	r3
	add	r1, r4, #12416
	ldr	r3, [r10, #52]
	add	r1, r1, #32
	mov	r2, #128
	add	r0, r5, #972
	blx	r3
	add	r1, r4, #12544
	add	r0, r5, #1216
	ldr	r3, [r10, #52]
	add	r1, r1, #32
	mov	r2, #128
	add	r0, r0, #12
	blx	r3
	b	.L763
.L780:
	ldr	r3, [fp, #-124]
	ldr	r0, [fp, #-140]
	mov	r2, r3, asl #1
	add	r3, r2, r3
	add	r1, r3, r3, lsr #31
	cmp	r0, r1, asr #1
	movle	r7, #1
	ble	.L781
	cmp	r0, r2
	movle	r7, #2
	ble	.L781
	cmp	r0, r3
	mov	r2, r0
	movle	r7, #3
	ble	.L781
	ldr	r3, [fp, #-124]
	mov	r0, #1
	ldr	r1, .L876+4
	mov	r7, #3
	str	ip, [fp, #-172]
	bl	dprint_vfmw
	ldr	ip, [fp, #-172]
	b	.L781
.L875:
	ldr	r2, [r5, #92]
	mov	r3, #0
	ldr	r1, [fp, #-112]
	str	r2, [r1, #1908]
	b	.L792
.L785:
	ldr	r1, [fp, #-152]
	ldr	r2, [fp, #-132]
	str	r7, [r8, #1428]
	mov	r3, r1, asr #1
	str	r7, [r8, #1432]
	add	r0, r3, r2, lsl #2
	str	r7, [r8, #1436]
	str	ip, [fp, #-140]
	mov	r6, r3
	bl	__aeabi_idiv
	mov	r3, r7
	mov	r2, r7
	mov	r1, r7
	ldr	ip, [fp, #-140]
	sub	r0, r0, #4
	str	r0, [r8, #1440]
	b	.L786
.L782:
	ldr	r3, [fp, #-136]
	ldr	r0, [fp, #-144]
	mov	r2, r3, asl #1
	add	r3, r2, r3
	add	r1, r3, r3, lsr #31
	cmp	r0, r1, asr #1
	movle	r2, #1
	ble	.L783
	cmp	r0, r2
	movle	r2, #2
	ble	.L783
	cmp	r0, r3
	mov	r2, r0
	movle	r2, #3
	ble	.L783
	ldr	r3, [fp, #-136]
	mov	r0, #1
	ldr	r1, .L876+8
	str	ip, [fp, #-140]
	bl	dprint_vfmw
	mov	r2, #3
	ldr	ip, [fp, #-140]
	b	.L783
.L771:
	ldr	lr, [r5, #72]
	cmp	lr, #0
	beq	.L802
	add	r1, r4, #2912
	ldr	r6, [fp, #-112]
	mov	ip, #0
	add	r1, r1, #8
	mov	r3, ip
.L776:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldr	r2, [r2, #20]
	ldr	r0, [r2, #32]
	cmp	r0, #0
	addeq	ip, r2, #80
	cmp	r3, lr
	bne	.L776
	str	r6, [fp, #-112]
	b	.L774
.L802:
	mov	ip, lr
	b	.L774
.L794:
	mvn	r3, #0
	str	r3, [fp, #-116]
	b	.L825
.L868:
	mov	r2, r0
	ldr	r1, .L876+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
	str	r3, [fp, #-116]
	b	.L825
.L877:
	.align	2
.L876:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC83
	.word	.LC84
	.word	.LC82
	UNWIND(.fnend)
	.size	HEVC_WriteSliceMsg, .-HEVC_WriteSliceMsg
	.align	2
	.global	HEVC_GetVirAddr
	.type	HEVC_GetVirAddr, %function
HEVC_GetVirAddr:
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
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetVirAddr, .-HEVC_GetVirAddr
	.align	2
	.global	HEVC_GetPhyAddr
	.type	HEVC_GetPhyAddr, %function
HEVC_GetPhyAddr:
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
	add	r0, r1, r0, lsl #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetPhyAddr, .-HEVC_GetPhyAddr
	.align	2
	.global	HEVC_CfgVDMReg
	.type	HEVC_CfgVDMReg, %function
HEVC_CfgVDMReg:
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
	add	r2, r0, #4096
	mov	r1, r0
	add	ip, r0, #8192
	mov	r0, #0
	ldr	r3, [r2, #28]
	ldr	lr, [r2, #32]
	clz	r3, r3
	str	lr, [r2, #3756]
	mov	r3, r3, lsr #5
	str	r3, [r2, #3764]
	ldr	r3, [r1, #204]
	str	r3, [ip, #816]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CfgVDMReg, .-HEVC_CfgVDMReg
	.align	2
	.global	HEVC_IsRefForCurrPic
	.type	HEVC_IsRefForCurrPic, %function
HEVC_IsRefForCurrPic:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #1
	beq	.L910
.L882:
	add	ip, r4, #4096
	ldr	r2, [r4, #164]
	ldr	r3, [ip, #732]
	cmp	r3, #0
	blt	.L899
	cmp	r3, r2
	bge	.L899
	ldr	r2, [r4, #2808]
	movw	r1, #5036
	mla	r3, r1, r3, r2
	ldr	r2, [r4, #160]
	ldr	r3, [r3, #32]
	cmp	r3, #0
	blt	.L886
	cmp	r3, r2
	bge	.L886
	ldr	r2, [r4, #2804]
	movw	r1, #12668
	ldr	r0, [ip, #1628]
	mov	r10, #1
	ldr	lr, [ip, #1632]
	mla	r1, r1, r3, r2
	ldr	r3, [ip, #1636]
	add	r2, lr, r0
	str	r0, [fp, #-56]
	cmp	r2, r3
	str	lr, [fp, #-60]
	mov	r5, r2
	ldr	r1, [r1, #116]
	mov	r10, r10, asl r1
	bcs	.L900
	cmp	r2, #15
	bgt	.L889
	add	r6, r2, #1440
	ldr	r9, [ip, #12]
	add	r6, r6, #15
	str	r4, [fp, #-48]
	str	r2, [fp, #-64]
	add	r6, r4, r6, lsl #2
	mov	r8, r9
	mov	r4, r3
	str	ip, [fp, #-52]
	b	.L891
.L913:
	cmp	r5, r4
	bcs	.L911
	cmp	r5, #16
	beq	.L912
.L891:
	ldr	r7, [r6, #4]!
	mov	r1, r10
	mov	r0, r8
	mov	r9, r8
	ldr	lr, [r6, #-944]
	cmp	lr, #0
	bne	.L892
	bl	__aeabi_idivmod
	mov	r0, r7
	mov	r9, r1
	mov	r1, r10
	bl	__aeabi_idivmod
	mov	r7, r1
.L892:
	cmp	r9, r7
	add	r5, r5, #1
	bne	.L913
	ldr	r2, [fp, #-64]
	mov	r5, #1
	ldr	r4, [fp, #-48]
	ldr	ip, [fp, #-52]
.L888:
	cmp	r2, #0
	beq	.L903
	ldr	lr, [ip, #708]
	ldr	r3, [ip, #1660]
	ldr	r0, [ip, #12]
	add	r3, lr, r3
	cmp	r0, r3
	beq	.L894
	add	r4, r4, #5696
	mov	r1, #0
	add	r4, r4, #60
	b	.L895
.L896:
	ldr	r3, [r4, #4]!
	add	r3, lr, r3
	cmp	r3, r0
	beq	.L894
.L895:
	add	r1, r1, #1
	cmp	r1, r2
	beq	.L903
	cmp	r1, #17
	bne	.L896
	ldr	r3, [fp, #-60]
	mov	r0, #0
	ldr	r2, [fp, #-56]
	str	r1, [sp]
	str	r3, [sp, #8]
	mov	r3, r1
	str	r2, [sp, #4]
	movw	r2, #8976
	ldr	r1, .L914
	bl	dprint_vfmw
	mov	r0, r5
	b	.L908
.L899:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8915
	ldr	r1, .L914+4
	bl	dprint_vfmw
	mov	r0, #0
.L908:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L910:
	ldr	r3, [r0, #2844]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L882
.L894:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L886:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8927
	ldr	r1, .L914+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L912:
	mov	r3, r4
	ldr	ip, [fp, #-52]
	ldr	r4, [fp, #-48]
.L889:
	str	r3, [sp, #4]
	mov	r1, #16
	mov	r3, r5
	movw	r2, #8947
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L914+12
	mov	r5, r0
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	ip, [fp, #-48]
	ldr	r3, [ip, #1628]
	ldr	r2, [ip, #1632]
	str	r3, [fp, #-56]
	str	r2, [fp, #-60]
	add	r2, r2, r3
	b	.L888
.L911:
	ldr	r2, [fp, #-64]
	mov	r5, #0
	ldr	r4, [fp, #-48]
	ldr	ip, [fp, #-52]
	b	.L888
.L903:
	mov	r0, r5
	b	.L908
.L900:
	mov	r5, #0
	b	.L888
.L915:
	.align	2
.L914:
	.word	.LC88
	.word	.LC85
	.word	.LC86
	.word	.LC87
	UNWIND(.fnend)
	.size	HEVC_IsRefForCurrPic, .-HEVC_IsRefForCurrPic
	.align	2
	.global	HEVC_IsPicVPSRefresh
	.type	HEVC_IsPicVPSRefresh, %function
HEVC_IsPicVPSRefresh:
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
	ldr	r2, [r0, #2824]
	ldr	r3, [r1, #4]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	beq	.L919
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L919:
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPicVPSRefresh, .-HEVC_IsPicVPSRefresh
	.align	2
	.global	HEVC_UpdatePicVPS
	.type	HEVC_UpdatePicVPS, %function
HEVC_UpdatePicVPS:
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
	mov	r2, #0
	strb	r2, [r1, #2]
	ldr	r3, [r0, #156]
	movw	r4, #24912
	ldr	ip, .L921
	mov	r5, r0
	ldr	r0, [r0, #2800]
	mov	r2, r4
	mul	r3, r4, r3
	ldr	ip, [ip, #52]
	sub	r3, r3, #24832
	sub	r3, r3, #80
	add	r0, r0, r3
	blx	ip
	ldr	r2, [r5, #156]
	ldr	r3, [r5, #2800]
	mul	r4, r4, r2
	sub	r4, r4, #24832
	sub	r4, r4, #80
	add	r4, r3, r4
	str	r4, [r5, #2824]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L922:
	.align	2
.L921:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_UpdatePicVPS, .-HEVC_UpdatePicVPS
	.align	2
	.global	HEVC_IsPicSPSRefresh
	.type	HEVC_IsPicSPSRefresh, %function
HEVC_IsPicSPSRefresh:
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
	ldr	r2, [r0, #2828]
	ldr	r3, [r1, #56]
	ldr	r2, [r2, #56]
	cmp	r2, r3
	beq	.L926
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L926:
	ldrb	r0, [r1]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPicSPSRefresh, .-HEVC_IsPicSPSRefresh
	.align	2
	.global	HEVC_UpdatePicSPS
	.type	HEVC_UpdatePicSPS, %function
HEVC_UpdatePicSPS:
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
	mov	r2, #0
	strb	r2, [r1]
	ldr	r3, [r0, #160]
	movw	r5, #12668
	ldr	ip, .L928
	mov	r4, r0
	ldr	r0, [r0, #2804]
	mov	r2, r5
	mul	r3, r5, r3
	ldr	ip, [ip, #52]
	sub	r3, r3, #12608
	sub	r3, r3, #60
	add	r0, r0, r3
	blx	ip
	ldr	r2, [r4, #160]
	ldr	r3, [r4, #2804]
	mul	r5, r5, r2
	sub	r5, r5, #12608
	sub	r5, r5, #60
	add	r5, r3, r5
	str	r5, [r4, #2828]
	ldr	r3, [r5, #56]
	str	r3, [r4, #288]
	ldr	r3, [r5, #64]
	str	r3, [r4, #292]
	ldr	r3, [r5, #68]
	str	r3, [r4, #296]
	ldr	r3, [r5, #128]
	str	r3, [r4, #300]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L929:
	.align	2
.L928:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_UpdatePicSPS, .-HEVC_UpdatePicSPS
	.align	2
	.global	HEVC_IsPicPPSRefresh
	.type	HEVC_IsPicPPSRefresh, %function
HEVC_IsPicPPSRefresh:
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
	ldr	r2, [r0, #2832]
	ldr	r3, [r1, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	beq	.L933
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L933:
	ldrb	r0, [r1, #1]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsPicPPSRefresh, .-HEVC_IsPicPPSRefresh
	.align	2
	.global	HEVC_UpdatePicPPS
	.type	HEVC_UpdatePicPPS, %function
HEVC_UpdatePicPPS:
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
	ldrb	r3, [r2, #13]	@ zero_extendqisi2
	mov	r4, #0
	mov	r5, r2
	cmp	r3, r4
	mov	r6, r0
	mov	r7, r1
	strb	r4, [r2, #1]
	beq	.L935
	ldrb	r3, [r2, #15]	@ zero_extendqisi2
	cmp	r3, r4
	bne	.L953
	ldr	lr, [r2, #68]
	ldr	r3, [r1, #188]
	cmp	lr, #1
	add	r0, r2, lr, lsl #1
	strh	r3, [r0, #170]	@ movhi
	ble	.L947
	add	lr, lr, #42
	add	r2, r2, #86
	add	ip, r5, #170
	add	lr, r5, lr, lsl #1
.L946:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #170]
	rsb	r3, r1, r3
	strh	r3, [r0, #170]	@ movhi
	bne	.L946
.L947:
	ldr	lr, [r5, #72]
	ldr	r3, [r7, #192]
	cmp	lr, #1
	add	r0, r5, lr, lsl #1
	strh	r3, [r0, #210]	@ movhi
	ble	.L942
	add	lr, lr, #62
	add	r2, r5, #126
	add	ip, r5, #210
	add	lr, r5, lr, lsl #1
.L948:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #210]
	rsb	r3, r1, r3
	strh	r3, [r0, #210]	@ movhi
	bne	.L948
	b	.L942
.L935:
	ldr	r3, [r1, #188]
	strh	r3, [r2, #172]	@ movhi
	ldr	r3, [r1, #192]
	strh	r3, [r2, #212]	@ movhi
.L942:
	ldr	r3, [r6, #164]
	movw	r4, #5036
	ldr	ip, .L954
	mov	r2, r4
	ldr	r0, [r6, #2808]
	mov	r1, r5
	mul	r3, r4, r3
	ldr	ip, [ip, #52]
	sub	r3, r3, #4992
	sub	r3, r3, #44
	add	r0, r0, r3
	blx	ip
	ldr	r2, [r6, #164]
	ldr	r3, [r6, #2808]
	mul	r4, r4, r2
	sub	r4, r4, #4992
	sub	r4, r4, #44
	add	r4, r3, r4
	str	r4, [r6, #2832]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L953:
	ldr	r9, [r2, #68]
	cmp	r9, r4
	addgt	r3, r2, #170
	ble	.L941
.L940:
	ldr	r10, [r7, #188]
	add	r4, r4, #1
	mov	r1, r9
	str	r3, [fp, #-48]
	mul	r0, r10, r4
	bl	__aeabi_uidiv
	mov	r1, r9
	mov	r8, r0
	sub	r0, r4, #1
	mul	r0, r0, r10
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	cmp	r4, r9
	rsb	r0, r0, r8
	strh	r0, [r3, #2]!	@ movhi
	bne	.L940
.L941:
	ldr	r9, [r5, #72]
	cmp	r9, #0
	addgt	r3, r5, #210
	movgt	r4, #0
	ble	.L942
.L943:
	ldr	r10, [r7, #192]
	add	r4, r4, #1
	mov	r1, r9
	str	r3, [fp, #-48]
	mul	r0, r10, r4
	bl	__aeabi_uidiv
	mov	r1, r9
	mov	r8, r0
	sub	r0, r4, #1
	mul	r0, r0, r10
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	cmp	r4, r9
	rsb	r0, r0, r8
	strh	r0, [r3, #2]!	@ movhi
	bne	.L943
	b	.L942
.L955:
	.align	2
.L954:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_UpdatePicPPS, .-HEVC_UpdatePicPPS
	.align	2
	.global	HEVC_InitPicInfo
	.type	HEVC_InitPicInfo, %function
HEVC_InitPicInfo:
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
	add	r4, r0, #4096
	mov	r5, r0
	mvn	r3, #0
	mov	r0, #1
	ldr	r2, [r4, #724]
	mov	r1, #0
	ldr	lr, [r4, #708]
	str	r3, [r4, #32]
	strb	r0, [r4, #1]
	str	r2, [r4, #4]
	str	lr, [r4, #12]
	ldr	ip, [r5, #2828]
	ldr	r3, .L970
	ldr	r2, [ip, #64]
	str	r2, [r4, #20]
	ldr	r2, [ip, #68]
	str	r1, [r4, #28]
	str	r2, [r4, #24]
	ldr	r2, [r5, #276]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, r0
	beq	.L969
.L957:
	ldr	r3, [r5, #2356]
	cmp	r3, #0
	bne	.L960
	ldr	ip, [r5, #2844]
	add	r6, r5, #4736
	movw	r7, #4752
	mvn	r0, #0
	mov	lr, r6
	mvn	r1, #0
	ldrd	r2, [ip, #56]
	strd	r2, [r6, #8]
	ldrd	r2, [ip, #72]
	strd	r2, [r5, r7]
	ldrd	r2, [ip, #88]
	strd	r2, [lr, #24]
	ldr	r3, [ip, #104]
	str	r3, [r4, #64]
	ldr	r3, [ip, #108]
	str	r3, [r4, #68]
	ldr	r3, [ip, #112]
	str	r3, [r4, #72]
	ldr	r3, [ip, #128]
	str	r3, [r4, #76]
	strd	r0, [ip, #56]
	ldr	ip, [r5, #2828]
.L960:
	ldr	r1, [ip, #64]
	mov	r6, #0
	ldr	r2, [r4, #728]
	add	r0, r5, #4160
	ldrb	r3, [r4, #128]	@ zero_extendqisi2
	str	r1, [r4, #132]
	ldr	r1, [ip, #68]
	str	r2, [r4, #248]
	str	r2, [r4, #8]
	str	r1, [r4, #136]
	str	r6, [r4, #116]
	ldr	r2, [ip, #60]
	ldr	r1, [ip, #2084]
	subs	r2, r2, #1
	bfi	r3, r1, #5, #3
	movne	r2, #1
	bfi	r3, r2, #2, #3
	strb	r3, [r4, #128]
	ldr	r1, [ip, #2068]
	and	r1, r1, #7
	bl	SetAspectRatio
	ldr	r3, [r5, #2356]
	cmp	r3, #1
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #708]
	str	r2, [r3, #8]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #128]
	str	r2, [r3, #144]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #116]
	str	r2, [r3, #132]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #168]
	str	r2, [r3, #184]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #164]
	str	r2, [r3, #180]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #132]
	str	r2, [r3, #148]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #136]
	str	r2, [r3, #152]
	ldr	r3, [r4, #60]
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L962
	ldr	r3, [r4, #116]
	mov	r1, r6
	ldr	r2, [r0, #4]
	subs	r3, r3, r6
	ldr	r0, [r5, #276]
	movne	r3, #1
	bl	FSP_SetStoreType
.L962:
	ldr	r3, [r5, #2828]
	mov	r6, #0
	ldr	ip, [r4, #60]
	ldr	r2, [r3, #72]
	str	r2, [r4, #284]
	ldr	r5, [r3, #76]
	str	r5, [r4, #288]
	ldr	r1, [r3, #80]
	str	r1, [r4, #292]
	ldr	lr, [r3, #84]
	str	lr, [r4, #296]
	ldr	r0, [r3, #64]
	rsb	r2, r2, r0
	rsb	r2, r5, r2
	str	r2, [r4, #140]
	ldr	r0, [r3, #68]
	rsb	r1, r1, r0
	rsb	r1, lr, r1
	str	r1, [r4, #144]
	ldr	r1, [r3, #60]
	str	r1, [r4, #228]
	ldr	r1, [r3, #88]
	str	r1, [r4, #232]
	ldr	r3, [r3, #96]
	str	r3, [r4, #236]
	ldr	r3, [ip, #164]
	str	r3, [r4, #148]
	ldr	r3, [ip, #168]
	str	r3, [r4, #152]
	str	r2, [ip, #156]
	ldr	r2, [r4, #144]
	ldr	r3, [r4, #60]
	str	r2, [r3, #160]
	ldr	r2, [r4, #148]
	ldr	r3, [r4, #60]
	str	r2, [r3, #164]
	ldr	r2, [r4, #152]
	ldr	r3, [r4, #60]
	str	r2, [r3, #168]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #232]
	str	r2, [r3, #248]
	ldr	r3, [r4, #60]
	ldr	r2, [r4, #236]
	str	r2, [r3, #252]
	str	r6, [r4, #16]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L969:
	ldr	r2, [r3, #156]
	cmp	r2, r1
	bne	.L957
	ldr	r3, [r3, #160]
	cmp	r3, r0
	bne	.L957
	add	r3, r5, #8192
	ldrb	r3, [r3, #3520]	@ zero_extendqisi2
	cmp	r3, r0
	bne	.L957
	movw	r2, #11744
	movw	r3, #11760
	ldrd	r0, [r5, r2]
	ldrd	r2, [r3, r5]
	cmp	r1, r3
	cmpeq	r0, r2
	bls	.L958
	subs	r6, r0, r2
	sbc	r7, r1, r3
	cmp	r7, #0
	cmpeq	r6, #16
	bls	.L958
.L959:
	ldr	r0, [r5, #284]
	movw	r1, #11744
	rsb	lr, r0, lr
	adds	r2, r2, lr
	adc	r3, r3, lr, asr #31
	strd	r2, [r5, r1]
	b	.L957
.L958:
	cmp	r1, r3
	cmpeq	r0, r2
	bcs	.L957
	subs	r0, r2, r0
	sbc	r1, r3, r1
	cmp	r1, #0
	cmpeq	r0, #16
	bls	.L957
	b	.L959
.L971:
	.align	2
.L970:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	HEVC_InitPicInfo, .-HEVC_InitPicInfo
	.align	2
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	add	r3, r0, #4096
	str	r3, [fp, #-56]
	mov	ip, r0
	ldr	r3, [r3, #716]
	cmp	r3, #1
	beq	.L989
	cmp	r3, #2
	beq	.L990
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [fp, #-48]
	beq	.L974
	ldr	r2, .L999
	mov	r0, #1
	ldr	r1, .L999+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L989:
	str	r3, [fp, #-48]
.L974:
	add	r8, ip, #4800
	add	r9, ip, #2848
	add	r8, r8, #56
	add	r9, r9, #8
	mov	r10, #0
.L987:
	ldr	r1, [r8, #4]!
	cmp	r1, #0
	beq	.L977
	ldr	r3, [r9]
	cmp	r3, #0
	bne	.L991
	mov	r2, r9
	mov	r4, r3
	b	.L979
.L981:
	ldr	r6, [r2, #4]!
	cmp	r6, #0
	bne	.L997
.L979:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L981
	mov	r4, #255
.L980:
	ldr	r2, [ip, #2844]
	ldr	r2, [r2, #24]
	cmp	r2, #2
	bne	.L982
	ldr	r2, [fp, #-56]
	ldr	r6, [r2, #60]
	add	r6, r6, #56
.L978:
	mov	r7, r9
	mov	r5, #0
	b	.L988
.L984:
	ldr	r3, [r7, #4]!
.L988:
	cmp	r3, #0
	beq	.L998
.L983:
	ldr	r3, [r8]
	add	r5, r5, #1
	cmp	r3, r5
	bhi	.L984
.L985:
	ldr	r3, [fp, #-48]
	add	r10, r10, #1
	add	r9, r9, #68
	cmp	r10, r3
	bcc	.L987
.L990:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L977:
	ldr	r3, [ip, #2844]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L985
	mov	r3, #1
	str	r3, [r8]
	ldr	r3, [fp, #-56]
	ldr	r3, [r3, #60]
	add	r3, r3, #56
	str	r3, [r9]
	b	.L985
.L998:
	sxtb	r2, r4
	str	r5, [sp]
	str	r2, [sp, #4]
	mov	r3, r10
	ldr	r2, .L999
	mov	r0, #1
	ldr	r1, .L999+8
	str	ip, [fp, #-52]
	bl	dprint_vfmw
	str	r6, [r7]
	ldr	ip, [fp, #-52]
	b	.L983
.L997:
	uxtb	r4, r4
	cmp	r4, #255
	bne	.L978
	b	.L980
.L991:
	mov	r6, r3
	mov	r4, #0
	b	.L978
.L982:
	mov	r3, r10
	ldr	r2, .L999
	ldr	r1, .L999+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1000:
	.align	2
.L999:
	.word	.LANCHOR0+368
	.word	.LC89
	.word	.LC91
	.word	.LC90
	UNWIND(.fnend)
	.size	HEVC_RepairList, .-HEVC_RepairList
	.align	2
	.global	HEVC_InitListX
	.type	HEVC_InitListX, %function
HEVC_InitListX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 144
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #148)
	sub	sp, sp, #148
	subs	r4, r0, #0
	beq	.L1064
	ldr	r3, .L1114
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, [r4, #3040]
	cmp	lr, #0
	beq	.L1065
	add	r0, r4, #3248
	mov	r1, #0
	add	r0, r0, #12
	mov	r3, r1
	b	.L1005
.L1004:
	cmp	r3, lr
	beq	.L1003
.L1005:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L1004
	ldr	ip, [r2, #60]
	cmp	ip, #0
	bne	.L1004
	ldr	ip, [r2, #64]
	cmp	ip, #1
	subeq	ip, fp, #44
	addeq	r2, r2, #56
	addeq	ip, ip, r1, lsl #2
	addeq	r1, r1, #1
	streq	r2, [ip, #-136]
	cmp	r3, lr
	bne	.L1005
.L1003:
	ldrb	r8, [r4, #1]	@ zero_extendqisi2
	cmp	r8, #0
	bne	.L1107
	ldr	r3, [r4, #3044]
	mov	r5, r1
	cmp	r3, #0
	moveq	r3, r8
	moveq	ip, r8
	beq	.L1063
	mov	ip, r8
.L1062:
	add	lr, r4, #3328
	mov	r2, #0
	b	.L1012
.L1011:
	cmp	r2, r3
	bcs	.L1108
.L1012:
	ldr	r0, [lr, #4]!
	add	r2, r2, #1
	ldrb	r6, [r0, #1]	@ zero_extendqisi2
	cmp	r6, #1
	bne	.L1011
	ldr	r6, [r0, #60]
	cmp	r6, #0
	bne	.L1011
	ldr	r6, [r0, #64]
	cmp	r6, #1
	subeq	r6, fp, #44
	addeq	r0, r0, #56
	addeq	r6, r6, r5, lsl #2
	addeq	r5, r5, #1
	streq	r0, [r6, #-136]
	cmp	r2, r3
	bcc	.L1012
.L1108:
	cmp	r8, #0
	rsbne	r2, r1, r5
	rsbne	r3, ip, r2
	bne	.L1010
	rsb	r3, r1, r5
.L1063:
	ldr	lr, [r4, #3036]
	cmp	lr, #0
	beq	.L1016
.L1014:
	add	r6, r4, #3392
	mov	r2, #0
	add	r6, r6, #4
	b	.L1018
.L1017:
	cmp	lr, r2
	bls	.L1109
.L1018:
	ldr	r0, [r6, #4]!
	add	r2, r2, #1
	ldrb	r7, [r0, #1]	@ zero_extendqisi2
	cmp	r7, #1
	bne	.L1017
	ldr	r7, [r0, #60]
	cmp	r7, #1
	bne	.L1017
	ldr	r7, [r0, #64]
	sub	r9, fp, #44
	add	r9, r9, r5, lsl #2
	add	r0, r0, #56
	cmp	r7, #0
	addeq	r5, r5, #1
	streq	r0, [r9, #-136]
	cmp	lr, r2
	bhi	.L1018
.L1109:
	cmp	r8, #0
	rsbeq	lr, r1, r5
	rsbeq	lr, r3, lr
	beq	.L1016
	rsb	r2, r1, r5
.L1015:
	ldr	r0, [r4, #3056]
	rsb	lr, r3, r2
	rsb	lr, ip, lr
	cmp	r0, #0
	beq	.L1023
	add	r9, r4, #3120
	mov	r2, #0
	add	r9, r9, #4
.L1022:
	ldr	r6, [r9, #4]!
	add	r2, r2, #1
	ldrb	r7, [r6, #1]	@ zero_extendqisi2
	cmp	r7, #1
	subeq	r7, fp, #44
	addeq	r6, r6, #56
	addeq	r7, r7, r5, lsl #2
	addeq	r5, r5, #1
	streq	r6, [r7, #-136]
	cmp	r2, r0
	bne	.L1022
	rsb	r0, r1, r5
	rsb	r0, r3, r0
	rsb	r0, ip, r0
	rsb	r0, lr, r0
.L1023:
	cmp	r5, #0
	beq	.L1110
.L1024:
	add	r2, r4, #4096
	str	r2, [fp, #-184]
	ldr	r2, [r2, #716]
	cmp	r2, #0
	str	r2, [fp, #-188]
	bne	.L1111
	cmp	r8, #0
	beq	.L1112
	cmp	r3, #0
	beq	.L1070
	add	r8, ip, r1
	sub	r6, fp, #180
	ldr	r2, [fp, #-188]
	sub	r9, fp, #116
	add	r8, r6, r8, lsl #2
.L1033:
	add	r2, r2, #1
	ldr	r6, [r8], #4
	cmp	r2, r3
	str	r6, [r9, #4]!
	bne	.L1033
.L1070:
	cmp	r0, #0
	mov	r2, r3
	beq	.L1031
	add	r8, lr, r3
	add	r9, r3, #16
	add	r8, r8, r1
	sub	r6, fp, #180
	add	r8, r8, ip
	add	r9, r6, r9, lsl #2
	mov	r2, #0
	add	r8, r6, r8, lsl #2
.L1034:
	add	r2, r2, #1
	ldr	r6, [r8], #4
	cmp	r2, r0
	str	r6, [r9, #4]!
	bne	.L1034
	add	r2, r3, r2
	b	.L1031
.L1107:
	ldr	ip, [r4, #3052]
	cmp	ip, #0
	beq	.L1066
	add	r0, r4, #3056
	mov	r5, r1
	mov	r3, #0
	b	.L1009
.L1008:
	cmp	r3, ip
	beq	.L1113
.L1009:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L1008
	ldr	lr, [r2, #72]
	cmp	lr, #1
	subeq	lr, fp, #44
	addeq	r2, r2, #56
	addeq	lr, lr, r5, lsl #2
	addeq	r5, r5, #1
	streq	r2, [lr, #-136]
	cmp	r3, ip
	bne	.L1009
.L1113:
	rsb	ip, r1, r5
.L1007:
	ldr	r3, [r4, #3044]
	cmp	r3, #0
	bne	.L1062
	mov	r2, ip
.L1010:
	ldr	lr, [r4, #3036]
	cmp	lr, #0
	bne	.L1014
	b	.L1015
.L1111:
	ldr	r3, [fp, #-184]
	ldr	r8, [r3, #772]
	ldr	r9, [r3, #776]
	cmp	r8, #0
	str	r8, [r3, #764]
	str	r9, [r3, #768]
	beq	.L1056
.L1027:
	ldr	r3, [fp, #-184]
	add	r7, r4, #2848
	add	r7, r7, #4
	mov	r10, #0
	ldrb	r6, [r3, #1792]	@ zero_extendqisi2
.L1050:
	cmp	r6, #0
	mov	r1, r5
	mov	r0, r10
	ldrne	r1, [r7, #3040]
	bne	.L1049
	bl	__aeabi_uidivmod
.L1049:
	sub	r3, fp, #44
	add	r10, r10, #1
	add	r3, r3, r1, lsl #2
	cmp	r10, r8
	ldr	r3, [r3, #-136]
	str	r3, [r7, #4]!
	bne	.L1050
	ldr	r3, [fp, #-188]
	cmp	r3, #0
	bne	.L1047
.L1046:
	cmp	r9, #0
	beq	.L1052
	ldr	r3, [fp, #-184]
	add	r7, r4, #2912
	add	r7, r7, #8
	mov	r6, #0
	ldrb	r10, [r3, #1793]	@ zero_extendqisi2
.L1055:
	cmp	r10, #0
	mov	r1, r5
	mov	r0, r6
	ldrne	r1, [r7, #3100]
	bne	.L1054
	bl	__aeabi_uidivmod
.L1054:
	sub	r3, fp, #44
	add	r6, r6, #1
	add	r3, r3, r1, lsl #2
	cmp	r6, r9
	ldr	r3, [r3, #-68]
	str	r3, [r7, #4]!
	bne	.L1055
.L1047:
	cmp	r8, #16
	bhi	.L1060
.L1056:
	add	r8, r8, #712
	add	r2, r4, #2912
	add	r8, r8, #1
	add	r2, r2, #8
	add	r8, r4, r8, lsl #2
.L1059:
	ldr	r3, [r4, #2856]
	str	r3, [r8, #4]!
	cmp	r8, r2
	bne	.L1059
.L1060:
	cmp	r9, #16
	bhi	.L1058
	add	r9, r9, #728
	add	r2, r4, #2976
	add	r9, r9, #2
	add	r2, r2, #12
	add	r9, r4, r9, lsl #2
.L1061:
	ldr	r3, [r4, #2924]
	str	r3, [r9, #4]!
	cmp	r9, r2
	bne	.L1061
.L1058:
	mov	r0, #0
.L1100:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1016:
	cmp	r5, #0
	mov	r0, #0
	bne	.L1024
.L1110:
	ldr	r3, .L1114
	add	r6, r4, #4096
	add	r0, r4, #2848
	mov	r2, #136
	add	r0, r0, #8
	str	r5, [r6, #764]
	ldr	r3, [r3, #48]
	mov	r1, r5
	str	r5, [r6, #768]
	blx	r3
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L1058
	ldr	r3, [r6, #60]
	mov	r2, #1
	mov	r0, r5
	str	r2, [r6, #764]
	add	r3, r3, #56
	str	r3, [r4, #2856]
	b	.L1100
.L1112:
	cmp	r3, #0
	beq	.L1102
	sub	r2, fp, #180
	sub	r0, fp, #116
	add	r8, r2, r1, lsl #2
	ldr	r2, [fp, #-188]
.L1037:
	add	r2, r2, #1
	ldr	r6, [r8], #4
	cmp	r2, r3
	str	r6, [r0, #4]!
	bne	.L1037
.L1102:
	mov	r2, r3
.L1031:
	cmp	r1, #0
	beq	.L1036
	add	r8, r2, #16
	sub	r9, fp, #180
	mov	r0, #0
	add	r8, r9, r8, lsl #2
.L1038:
	add	r0, r0, #1
	ldr	r6, [r9], #4
	cmp	r0, r1
	str	r6, [r8, #4]!
	bne	.L1038
	add	r2, r2, r1
.L1036:
	ldrb	r0, [r4, #1]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1039
	cmp	lr, #0
	beq	.L1041
	add	r1, r3, r1
	add	r2, r2, #16
	sub	r3, fp, #180
	add	r1, r3, r1, lsl #2
	add	r3, r3, r2, lsl #2
.L1045:
	add	r0, r0, #1
	ldr	r2, [r1], #4
	cmp	r0, lr
	str	r2, [r3, #4]!
	bne	.L1045
.L1041:
	ldr	r3, [fp, #-184]
	ldr	r8, [r3, #772]
	ldr	r9, [r3, #776]
	cmp	r8, #0
	str	r8, [r3, #764]
	str	r9, [r3, #768]
	bne	.L1027
	b	.L1046
.L1039:
	cmp	lr, #0
	beq	.L1042
	add	r0, r3, ip
	add	r8, r2, #16
	add	r0, r0, r1
	sub	r6, fp, #180
	add	r8, r6, r8, lsl #2
	mov	r3, #0
	add	r0, r6, r0, lsl #2
.L1043:
	add	r3, r3, #1
	ldr	r6, [r0], #4
	cmp	r3, lr
	str	r6, [r8, #4]!
	bne	.L1043
	add	r2, r2, r3
.L1042:
	cmp	ip, #0
	beq	.L1041
	add	r2, r2, #16
	sub	r0, fp, #180
	sub	r3, fp, #180
	add	r2, r0, r2, lsl #2
	add	r1, r3, r1, lsl #2
	mov	r3, #0
.L1044:
	add	r3, r3, #1
	ldr	r0, [r1], #4
	cmp	r3, ip
	str	r0, [r2, #4]!
	bne	.L1044
	b	.L1041
.L1065:
	mov	r1, lr
	b	.L1003
.L1066:
	mov	r5, r1
	b	.L1007
.L1052:
	ldr	r3, .L1114
	add	r1, r4, #2848
	add	r0, r4, #2912
	add	r1, r1, #8
	add	r0, r0, #12
	mov	r2, #68
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-184]
	ldr	r8, [r3, #764]
	str	r8, [r3, #768]
	mov	r9, r8
	b	.L1047
.L1064:
	mvn	r0, #0
	b	.L1100
.L1115:
	.align	2
.L1114:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_InitListX, .-HEVC_InitListX
	.align	2
	.global	HEVC_DecList
	.type	HEVC_DecList, %function
HEVC_DecList:
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
	add	r3, r0, #4096
	mov	r4, r0
	ldr	r2, [r3, #716]
	cmp	r2, #2
	beq	.L1121
	bl	HEVC_InitListX
	cmp	r0, #0
	bne	.L1122
	mov	r0, r4
	bl	HEVC_RepairList
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1123
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1121:
	mov	r0, #0
	str	r0, [r3, #764]
	str	r0, [r3, #768]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1122:
	ldr	r1, .L1123+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1124:
	.align	2
.L1123:
	.word	.LC93
	.word	.LC92
	UNWIND(.fnend)
	.size	HEVC_DecList, .-HEVC_DecList
	.align	2
	.global	HEVC_ArrangeMem
	.type	HEVC_ArrangeMem, %function
HEVC_ArrangeMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	r2, [r0, #2828]
	mov	r4, r0
	movw	r1, #8160
	ldr	r6, [r2, #188]
	ldr	r5, [r2, #192]
	ldr	r2, [r2, #128]
	mov	r5, r5, asl r2
	mov	r6, r6, asl r2
	sub	r0, r5, #32
	sub	r2, r6, #32
	cmp	r2, r1
	cmpls	r0, r1
	movhi	r1, #1
	movls	r1, #0
	bhi	.L1132
	ldr	r3, .L1134
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2844]
	str	r6, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L1128
	ldrb	r3, [r4, #3024]	@ zero_extendqisi2
	strb	r3, [fp, #-47]
.L1130:
	sub	r1, fp, #48
	ldr	r0, [r4, #276]
	strb	r3, [fp, #-45]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L1133
	ldr	r1, [r4, #2844]
	sub	r3, fp, #52
	ldr	r0, [r4, #276]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
.L1131:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1128:
	mov	r3, #1
	strb	r3, [fp, #-47]
	b	.L1130
.L1132:
	str	r5, [sp]
	mov	r3, r6
	ldr	r2, .L1134+4
	mov	r0, #0
	ldr	r1, .L1134+8
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1133:
	ldr	r2, .L1134+4
	mov	r0, #1
	ldr	r1, .L1134+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1131
.L1135:
	.align	2
.L1134:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+384
	.word	.LC94
	.word	.LC95
	UNWIND(.fnend)
	.size	HEVC_ArrangeMem, .-HEVC_ArrangeMem
	.align	2
	.global	HEVC_RemoveApcStore
	.type	HEVC_RemoveApcStore, %function
HEVC_RemoveApcStore:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, r1, lsl #2
	ldr	ip, [r3, #3196]
	ldr	r2, [ip, #32]
	cmp	r2, #1
	bhi	.L1139
	ldr	r3, [ip, #24]
	cmp	r3, #15
	bhi	.L1136
	mov	r1, #70
	mov	r4, #280
	mla	r1, r1, r2, r3
	mov	lr, #0
	mla	r2, r4, r2, r0
	mov	r4, #16
	add	r3, r2, r3
	add	r1, r0, r1, lsl #2
	add	r1, r1, #12288
	add	r3, r3, #13376
	add	r2, r2, #13120
	str	lr, [r1, #868]
	str	lr, [r1, #932]
	str	lr, [r1, #996]
	str	lr, [r1, #1060]
	strb	lr, [r3, #36]
	ldr	r3, [ip, #20]
	add	r3, r3, #536
	add	r3, r3, #2
	add	r0, r0, r3, lsl #2
	str	lr, [r0, #4]
	str	r4, [ip, #24]
	ldr	r3, [r2, #32]
	sub	r3, r3, #1
	str	r3, [r2, #32]
.L1136:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1139:
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L1140
	mov	r0, #1
	ldr	r1, .L1140+4
	bl	dprint_vfmw
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1141:
	.align	2
.L1140:
	.word	.LANCHOR0+400
	.word	.LC96
	UNWIND(.fnend)
	.size	HEVC_RemoveApcStore, .-HEVC_RemoveApcStore
	.align	2
	.global	HEVC_RemoveUnusedApcStore
	.type	HEVC_RemoveUnusedApcStore, %function
HEVC_RemoveUnusedApcStore:
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
	ldr	r3, [r0, #3028]
	mov	r6, r0
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #3184
	mov	r4, #0
	add	r5, r5, #8
	b	.L1145
.L1144:
	ldr	r3, [r6, #3028]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L1148
.L1145:
	ldr	r3, [r5, #4]!
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1144
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_RemoveApcStore
	ldr	r3, [r6, #3028]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L1145
.L1148:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveUnusedApcStore, .-HEVC_RemoveUnusedApcStore
	.align	2
	.global	HEVC_ApplyReferencePictureSet
	.type	HEVC_ApplyReferencePictureSet, %function
HEVC_ApplyReferencePictureSet:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	add	r5, r0, #4096
	ldr	r2, [r0, #2808]
	movw	r4, #5036
	ldr	r1, [r5, #732]
	movw	ip, #12668
	ldr	r3, [r0, #2804]
	mov	r10, r0
	ldr	lr, [r10, #3028]
	mov	r0, #1
	mla	r2, r4, r1, r2
	cmp	lr, #0
	ldr	r2, [r2, #32]
	mla	r3, ip, r2, r3
	ldr	r3, [r3, #116]
	mov	r3, r0, asl r3
	str	r3, [fp, #-52]
	beq	.L1149
	add	ip, r10, #3184
	add	r3, r10, #5696
	add	r3, r3, #60
	add	ip, ip, #8
	str	r3, [fp, #-68]
	mov	r3, #0
	str	r10, [fp, #-48]
	b	.L1166
.L1152:
	ldr	r2, [fp, #-48]
	add	r3, r3, #1
	ldr	r2, [r2, #3028]
	cmp	r3, r2
	bcs	.L1149
.L1166:
	ldr	r7, [ip, #4]!
	ldr	r2, [r5, #728]
	ldr	r1, [r7, #32]
	cmp	r1, r2
	bne	.L1152
	ldr	r0, [r5, #1628]
	ldr	r2, [r5, #1632]
	ldr	r1, [r5, #1636]
	add	r2, r2, r0
	cmp	r2, r1
	mov	r8, r2
	ldrcs	r0, [r7, #8]
	movcs	r4, #0
	bcs	.L1154
	add	r6, r2, #1456
	ldr	r2, [fp, #-48]
	ldr	r9, [r7, #8]
	mov	r4, #0
	add	r6, r2, r6, lsl #2
	str	r3, [fp, #-64]
	mov	r3, r5
	mov	r5, ip
.L1160:
	ldr	r10, [r6, #-944]
	ldr	r2, [r7, #60]
	cmp	r10, #0
	beq	.L1155
	cmp	r2, #0
	beq	.L1156
	ldr	r2, [r6]
	cmp	r2, r9
	beq	.L1188
.L1156:
	cmp	r4, #0
	bne	.L1171
	ldr	r2, [r6]
	mov	r4, r9
.L1168:
	ldrb	r1, [r7, #1]	@ zero_extendqisi2
	rsb	r4, r2, r4
	clz	r4, r4
	cmp	r1, #0
	mov	r4, r4, lsr #5
	moveq	r4, #0
	cmp	r4, #0
	bne	.L1189
.L1171:
	mov	r0, r9
.L1159:
	ldr	r2, [r3, #1636]
	add	r8, r8, #1
	add	r6, r6, #4
	mov	r9, r0
	cmp	r8, r2
	bcc	.L1160
	mov	ip, r5
	mov	r5, r3
	ldr	r2, [r5, #1632]
	ldr	r1, [r5, #1628]
	ldr	r3, [fp, #-64]
	add	r2, r2, r1
.L1154:
	cmp	r2, #0
	ldr	lr, [r5, #708]
	beq	.L1162
	ldr	r8, [fp, #-68]
	mov	r1, r7
	mov	r6, #0
	mov	r9, #1
	mov	r7, r3
	mov	r10, ip
.L1164:
	ldr	r3, [r1, #60]
	add	r6, r6, #1
	cmp	r3, #0
	bne	.L1163
	ldr	r2, [r8]
	add	r2, lr, r2
	cmp	r2, r0
	beq	.L1190
.L1163:
	ldr	r2, [r5, #1632]
	add	r8, r8, #4
	ldr	r3, [r5, #1628]
	add	r2, r2, r3
	cmp	r6, r2
	bcc	.L1164
	mov	r3, r7
	mov	ip, r10
	mov	r7, r1
.L1162:
	eor	r4, r4, #1
	cmp	r0, lr
	moveq	r0, #0
	andne	r0, r4, #1
	cmp	r0, #0
	beq	.L1152
	mov	r2, #0
	strb	r2, [r7, #1]
	ldr	r2, [ip]
	mov	r1, #0
	str	r1, [r2, #60]
	ldr	r2, [ip]
	str	r1, [r2, #72]
	ldr	r2, [ip]
	ldr	r1, [r2, #52]
	cmp	r1, #1
	beq	.L1152
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-48]
	ldr	r1, [r2, #28]
	mov	r2, #0
	str	ip, [fp, #-60]
	ldr	r0, [r3, #276]
	bl	FSP_SetRef
	ldr	ip, [fp, #-60]
	ldr	r3, [fp, #-56]
	b	.L1152
.L1155:
	cmp	r2, #0
	beq	.L1158
	ldr	r1, [fp, #-52]
	mov	r0, r9
	str	r3, [fp, #-60]
	bl	__aeabi_idivmod
	ldr	r0, [r6]
	str	r1, [fp, #-56]
	ldr	r1, [fp, #-52]
	bl	__aeabi_idivmod
	ldr	r2, [fp, #-56]
	ldr	r3, [fp, #-60]
	cmp	r2, r1
	beq	.L1191
.L1158:
	cmp	r4, #0
	bne	.L1171
	ldr	r1, [fp, #-52]
	mov	r0, r9
	str	r3, [fp, #-56]
	bl	__aeabi_idivmod
	ldr	r10, [r6]
	mov	r0, r10
	mov	r4, r1
	ldr	r1, [fp, #-52]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-56]
	mov	r2, r1
	b	.L1168
.L1189:
	str	r3, [fp, #-56]
	mov	r3, #1
	strb	r3, [r7, #1]
	mov	r2, r3
	ldr	r1, [r5]
	mov	r4, r3
	str	r3, [r1, #60]
	mov	r3, #0
	ldr	r1, [r5]
	str	r3, [r1, #72]
	ldr	r1, [r5]
	ldr	r3, [fp, #-48]
	str	r2, [r1, #48]
	ldr	r1, [r5]
	ldr	r0, [r3, #276]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r7, [r5]
	ldr	r3, [fp, #-56]
	ldr	r0, [r7, #8]
	b	.L1159
.L1190:
	strb	r9, [r1, #1]
	mov	r2, #1
	ldr	r1, [r10]
	mov	r4, r2
	str	r3, [r1, #72]
	ldr	r3, [r10]
	ldr	r1, [fp, #-48]
	str	r9, [r3, #48]
	ldr	r3, [r10]
	ldr	r0, [r1, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r1, [r10]
	ldr	lr, [r5, #708]
	ldr	r0, [r1, #8]
	b	.L1163
.L1149:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1191:
	str	r3, [fp, #-56]
	mov	r3, #1
	strb	r3, [r7, #1]
	mov	r2, r3
	ldr	r1, [r5]
	str	r10, [r1, #72]
	ldr	r1, [r5]
.L1187:
	str	r3, [r1, #48]
	mov	r4, #1
	ldr	r3, [fp, #-48]
	ldr	r1, [r5]
	ldr	r0, [r3, #276]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r7, [r5]
	ldr	r3, [fp, #-56]
	ldr	r0, [r7, #8]
	b	.L1159
.L1188:
	str	r3, [fp, #-56]
	mov	r3, #1
	strb	r3, [r7, #1]
	mov	r2, r3
	ldr	r1, [r5]
	mov	r3, #0
	str	r3, [r1, #72]
	mov	r3, r2
	ldr	r1, [r5]
	b	.L1187
	UNWIND(.fnend)
	.size	HEVC_ApplyReferencePictureSet, .-HEVC_ApplyReferencePictureSet
	.align	2
	.global	HEVC_CheckThatAllRefPicsAreAvailable
	.type	HEVC_CheckThatAllRefPicsAreAvailable, %function
HEVC_CheckThatAllRefPicsAreAvailable:
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
	add	r3, r0, #4096
	ldr	r3, [r3, #724]
	sub	r3, r3, #19
	cmp	r3, #2
	bls	.L1193
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_CheckThatAllRefPicsAreAvailable.part.15
.L1193:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable, .-HEVC_CheckThatAllRefPicsAreAvailable
	.align	2
	.global	HEVC_SetFrmRepeatCount
	.type	HEVC_SetFrmRepeatCount, %function
HEVC_SetFrmRepeatCount:
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
	ldr	r3, [r0, #2844]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_SetFrmRepeatCount.part.16
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount, .-HEVC_SetFrmRepeatCount
	.align	2
	.global	HEVC_GetFreeFrameStoreNum
	.type	HEVC_GetFreeFrameStoreNum, %function
HEVC_GetFreeFrameStoreNum:
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
	add	r1, r0, #13696
	add	r4, r0, #27904
	add	r1, r1, #16
	add	r4, r4, #48
	mov	r5, #0
.L1201:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L1197
	cmp	r1, #0
	beq	.L1198
	ldr	lr, [r0, #3028]
	cmp	lr, #0
	beq	.L1198
	ldr	r2, [r0, #3196]
	cmp	r2, r1
	beq	.L1197
	add	r2, r0, #3184
	add	r2, r2, #12
	b	.L1199
.L1200:
	ldr	ip, [r2, #4]!
	cmp	ip, r1
	beq	.L1197
.L1199:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L1200
.L1198:
	add	r5, r5, #1
.L1197:
	add	r1, r1, #712
	cmp	r1, r4
	bne	.L1201
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetFreeFrameStoreNum, .-HEVC_GetFreeFrameStoreNum
	.align	2
	.global	HEVC_UpdateReflist
	.type	HEVC_UpdateReflist, %function
HEVC_UpdateReflist:
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
	add	r4, r0, #4096
	mov	r6, r0
	ldr	r1, [r4, #1628]
	cmp	r1, #0
	beq	.L1231
	add	r9, r0, #5696
	mov	r7, #0
	mov	r5, r7
	mov	r8, r9
	add	r9, r9, #39
	add	r8, r8, #60
.L1217:
	ldrb	r3, [r9, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1213
	ldr	lr, [r6, #3028]
	ldr	ip, [r4, #708]
	ldr	r3, [r8]
	cmp	lr, #0
	add	ip, ip, r3
	beq	.L1213
	add	r1, r6, #3184
	mov	r3, #0
	add	r1, r1, #8
	b	.L1216
.L1214:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1213
.L1216:
	ldr	r2, [r1, #4]!
	ldr	r0, [r2, #8]
	cmp	r0, ip
	bne	.L1214
	ldr	r10, [r4, #728]
	ldr	r0, [r2, #32]
	cmp	r10, r0
	bne	.L1214
	add	r10, r6, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r10, #3196]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1257
.L1215:
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r10, #3196]
	mov	r1, #0
	add	r3, r7, #816
	add	r7, r7, #1
	str	r1, [r2, #60]
	ldr	r2, [r10, #3196]
	str	r2, [r6, r3, asl #2]
.L1213:
	ldr	r1, [r4, #1628]
	add	r5, r5, #1
	add	r8, r8, #4
	cmp	r1, r5
	bhi	.L1217
.L1212:
	ldr	r2, [r6, #3024]
	str	r7, [r6, #3040]
	cmp	r2, r7
	bls	.L1222
	add	r3, r7, #812
	mov	r0, #0
	add	r3, r3, #3
	add	r3, r6, r3, lsl #2
.L1221:
	add	r7, r7, #1
	str	r0, [r3, #4]!
	cmp	r7, r2
	bne	.L1221
.L1222:
	ldr	r3, [r4, #1632]
	add	r10, r1, r3
	cmp	r10, r5
	movls	r7, #0
	bls	.L1220
	add	r8, r5, #1424
	add	r9, r5, #5696
	add	r8, r8, #15
	add	r9, r9, #39
	add	r9, r6, r9
	mov	r7, #0
	add	r8, r6, r8, lsl #2
	str	r7, [fp, #-48]
.L1227:
	ldrb	r3, [r9, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1223
	ldr	ip, [r6, #3028]
	ldr	r0, [r4, #708]
	ldr	r3, [r8]
	cmp	ip, #0
	add	r0, r0, r3
	beq	.L1223
	add	r1, r6, #3184
	mov	r3, #0
	add	r1, r1, #8
	b	.L1226
.L1224:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L1223
.L1226:
	ldr	r2, [r1, #4]!
	ldr	lr, [r2, #8]
	cmp	lr, r0
	bne	.L1224
	ldr	r7, [r4, #728]
	ldr	lr, [r2, #32]
	cmp	r7, lr
	bne	.L1224
	add	r7, r6, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r7, #3196]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1258
.L1225:
	ldr	r1, [fp, #-48]
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r7, #3196]
	add	r3, r6, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-48]
	mov	r1, #0
	str	r1, [r2, #60]
	ldr	r2, [r7, #3196]
	str	r2, [r3, #3332]
.L1223:
	add	r5, r5, #1
	add	r8, r8, #4
	cmp	r10, r5
	bhi	.L1227
	ldr	r7, [fp, #-48]
	ldr	r2, [r6, #3024]
.L1220:
	cmp	r2, r7
	str	r7, [r6, #3044]
	bls	.L1211
	add	r1, r7, #832
	mov	r3, #0
	add	r6, r6, r1, lsl #2
.L1229:
	add	r7, r7, #1
	str	r3, [r6, #4]!
	cmp	r7, r2
	bne	.L1229
.L1211:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1257:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r6, #276]
	bl	FSP_SetRef
	ldr	r3, [r10, #3196]
	b	.L1215
.L1258:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r6, #276]
	bl	FSP_SetRef
	ldr	r3, [r7, #3196]
	b	.L1225
.L1231:
	mov	r7, r1
	mov	r5, r1
	b	.L1212
	UNWIND(.fnend)
	.size	HEVC_UpdateReflist, .-HEVC_UpdateReflist
	.align	2
	.global	HEVC_UpdateLTReflist
	.type	HEVC_UpdateLTReflist, %function
HEVC_UpdateLTReflist:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r5, r0, #4096
	mov	r7, r0
	ldr	r0, [r0, #2808]
	ldr	r3, [r5, #732]
	movw	r4, #5036
	ldr	r2, [r5, #1628]
	movw	lr, #12668
	ldr	ip, [r7, #2804]
	mov	r1, #1
	mla	r0, r4, r3, r0
	ldr	r4, [r5, #1632]
	ldr	r3, [r5, #1636]
	add	r2, r2, r4
	sub	r2, r2, #1
	sub	r10, r3, #1
	cmp	r10, r2
	ldr	r0, [r0, #32]
	mla	r2, lr, r0, ip
	ldr	r2, [r2, #116]
	mov	r2, r1, asl r2
	ble	.L1270
	add	r9, r3, #1440
	add	r3, r3, #5696
	add	r9, r9, #15
	add	r3, r3, #40
	add	r3, r7, r3
	sub	r4, r2, #1
	add	r9, r7, r9, lsl #2
	mov	r8, #0
	str	r8, [fp, #-52]
	mov	r8, r3
	str	r1, [fp, #-56]
.L1266:
	ldrb	r3, [r8, #-1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1261
	ldrb	r0, [r9, #-944]	@ zero_extendqisi2
	ldr	ip, [r9]
	ldr	lr, [r7, #3028]
	cmp	r0, #0
	andeq	ip, ip, r4
	cmp	lr, #0
	ble	.L1261
	add	r1, r7, #3184
	mov	r3, #0
	add	r1, r1, #8
	str	r7, [fp, #-48]
	b	.L1265
.L1264:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1277
.L1265:
	ldr	r2, [r1, #4]!
	cmp	r0, #0
	ldr	r6, [r2, #8]
	andeq	r6, r6, r4
	cmp	ip, r6
	bne	.L1264
	ldr	r6, [r5, #728]
	ldr	r7, [r2, #32]
	cmp	r7, r6
	bne	.L1264
	ldr	r7, [fp, #-48]
	mov	ip, #0
	ldr	r0, [fp, #-56]
	add	r3, r7, r3, lsl #2
	ldr	r1, [fp, #-52]
	strb	r0, [r2, #1]
	add	r2, r1, #848
	add	r1, r1, #1
	str	r1, [fp, #-52]
	ldr	r1, [r3, #3196]
	add	r2, r2, #2
	str	ip, [r1, #64]
	ldr	r1, [r3, #3196]
	str	r0, [r1, #60]
	ldr	r3, [r3, #3196]
	str	r3, [r7, r2, asl #2]
.L1261:
	ldr	r3, [r5, #1628]
	sub	r10, r10, #1
	ldr	r2, [r5, #1632]
	sub	r9, r9, #4
	add	r3, r3, r2
	sub	r3, r3, #1
	cmp	r3, r10
	blt	.L1266
	ldr	r8, [fp, #-52]
	mov	r3, r8
.L1260:
	ldr	r2, [r7, #3024]
	str	r3, [r7, #3036]
	cmp	r2, r8
	ble	.L1259
	add	r3, r8, #848
	mov	r1, #0
	add	r3, r3, #1
	add	r3, r7, r3, lsl #2
.L1268:
	add	r8, r8, #1
	str	r1, [r3, #4]!
	cmp	r8, r2
	bne	.L1268
.L1259:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1277:
	ldr	r7, [fp, #-48]
	b	.L1261
.L1270:
	mov	r3, #0
	mov	r8, r3
	b	.L1260
	UNWIND(.fnend)
	.size	HEVC_UpdateLTReflist, .-HEVC_UpdateLTReflist
	.align	2
	.global	HEVC_GetAPC
	.type	HEVC_GetAPC, %function
HEVC_GetAPC:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L1296
	add	r2, r0, #4096
	mov	r3, #280
	ldr	r7, [r2, #8]
	mul	r3, r3, r7
	add	r2, r0, r3
	add	r1, r2, #13120
	ldr	ip, [r1, #28]
	cmp	ip, #0
	beq	.L1281
	add	r2, r2, #13120
	ldr	r4, [r2, #36]
	cmp	r4, #0
	addne	r3, r3, #13120
	addne	r3, r3, #36
	movne	r4, #0
	addne	r3, r0, r3
	bne	.L1284
	b	.L1282
.L1287:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1282
.L1284:
	add	r4, r4, #1
	cmp	r4, ip
	bne	.L1287
.L1281:
	ldr	r1, .L1297
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L1294:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1282:
	ldr	r1, [r5, #28]
	ldr	r0, [r6, #276]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	beq	.L1285
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L1285
	mov	r2, #70
	mov	r3, #280
	mla	r2, r2, r7, r4
	mov	lr, #1
	mla	r7, r3, r7, r6
	ldr	r1, .L1297+4
	mov	r3, r4
	mov	r0, #13
	add	r6, r6, r2, lsl #2
	add	r2, r7, #13120
	add	r6, r6, #12288
	add	r7, r7, r4
	str	lr, [r6, #868]
	ldr	ip, [ip, #28]
	ldr	ip, [ip, #4]
	str	ip, [r6, #932]
	ldr	ip, [r5, #8]
	str	ip, [r6, #996]
	ldr	ip, [r2, #32]
	add	ip, ip, lr
	str	ip, [r2, #32]
	ldr	r2, [r5, #228]
	bl	dprint_vfmw
	ldr	r1, [r5, #32]
	add	r3, r7, #13376
	mov	r2, #0
	str	r4, [r5, #24]
	mov	r0, r2
	str	r1, [r6, #1060]
	strb	r2, [r3, #36]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1285:
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	r2, [r5, #28]
	ldr	r3, [r5, #8]
	stmia	sp, {r1, ip}
	str	r0, [sp, #8]
	ldr	r1, .L1297+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1294
.L1296:
	mov	r0, r5
	movw	r3, #11486
	ldr	r2, .L1297+12
	ldr	r1, .L1297+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1294
.L1298:
	.align	2
.L1297:
	.word	.LC98
	.word	.LC97
	.word	.LC4
	.word	.LC2
	.word	.LC3
	UNWIND(.fnend)
	.size	HEVC_GetAPC, .-HEVC_GetAPC
	.align	2
	.global	HEVC_CheckFrameStore
	.type	HEVC_CheckFrameStore, %function
HEVC_CheckFrameStore:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r4, r1
	ldr	r0, [r0, #276]
	ldr	r1, [r1, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1300
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L1319
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1306
	ldr	r2, [r4, #48]
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1305
	cmp	r3, #1
	beq	.L1305
.L1316:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1319:
	ldr	r3, [r4, #28]
	mov	r0, #13
	str	r2, [sp]
	ldr	r1, .L1320
	ldr	r2, .L1320+4
	bl	dprint_vfmw
.L1302:
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1306
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r2, .L1320+4
	ldr	r1, .L1320+8
	bl	dprint_vfmw
	mvn	r0, #2
	b	.L1316
.L1300:
	ldr	lr, [r4, #28]
	mov	r2, r4
	ldr	ip, [r4, #52]
	mov	r0, #1
	ldr	r3, [r4, #8]
	ldr	r1, .L1320+12
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	b	.L1302
.L1305:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	mov	r3, r4
	ldr	r2, .L1320+4
	ldr	r1, .L1320+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1316
.L1306:
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r4, #2]
	mvn	r0, #2
	str	r3, [r4, #52]
	b	.L1316
.L1321:
	.align	2
.L1320:
	.word	.LC99
	.word	.LANCHOR0+420
	.word	.LC101
	.word	.LC100
	.word	.LC102
	UNWIND(.fnend)
	.size	HEVC_CheckFrameStore, .-HEVC_CheckFrameStore
	.align	2
	.global	HEVC_GetImagePara
	.type	HEVC_GetImagePara, %function
HEVC_GetImagePara:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	add	r8, r1, #672
	mov	r4, r1
	mvn	r7, #0
	ldrd	r2, [r8, #-8]
	mvn	r6, #0
	ldr	r1, [r1, #12]
	mov	r5, r0
	cmp	r3, r7
	cmpeq	r2, r6
	str	r1, [fp, #-52]
	beq	.L1324
	ldr	r3, [r0, #3028]
	cmp	r3, #0
	beq	.L1324
	add	r10, r0, #3184
	mvn	r6, #1
	add	r10, r10, #8
	mvn	r7, #0
	mov	r9, #0
	mvn	r3, #0
	str	r3, [fp, #-48]
.L1327:
	ldr	r2, [r10, #4]!
	cmp	r2, #0
	beq	.L1326
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1326
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	beq	.L1326
	ldr	r2, [r10]
	add	r2, r2, #672
	ldrd	r0, [r2, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r9, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L1326:
	ldr	r2, [r5, #3028]
	add	r9, r9, #1
	cmp	r9, r2
	bcc	.L1327
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L1324
	ldrd	r2, [r8, #-8]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L1359
.L1324:
	ldrb	r3, [r4, #145]	@ zero_extendqisi2
	ldrb	r2, [r4, #144]	@ zero_extendqisi2
	and	r3, r3, #195
	bfc	r3, #0, #2
	bfc	r2, #0, #2
	strb	r3, [r4, #145]
	strb	r2, [r4, #144]
	ldr	r3, [r5, #144]
	str	r3, [r4, #188]
	ldr	r3, [r5, #2824]
	ldrh	r3, [r3, #124]
	cmp	r3, #1
	moveq	r2, #0
	beq	.L1328
	movw	r2, #257
	cmp	r3, r2
	movne	r2, #1
	bne	.L1328
	ldr	r2, [r5, #3484]
	subs	r2, r2, #1
	movne	r2, #1
.L1328:
	ldr	r3, [r5, #2828]
	ldrb	r3, [r3, #2066]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	ip, #3
	beq	.L1329
	ldr	r3, [r4, #40]
	cmp	r3, #1
	cmpne	r3, #11
	moveq	ip, #1
	bne	.L1360
.L1330:
	ldr	r2, [r4, #44]
	clz	r2, r2
	mov	r2, r2, lsr #5
.L1329:
	ldrb	r3, [r4, #145]	@ zero_extendqisi2
	mov	r0, #2
	ldr	r1, [r4, #48]
	bfi	r3, r0, #4, #2
	ldr	r6, [fp, #-52]
	cmp	r1, #0
	bfi	r3, ip, #2, #2
	bfi	r3, r2, #0, #2
	ldrb	lr, [r4, #4]	@ zero_extendqisi2
	strb	r3, [r4, #145]
	ldrne	r3, [r4, #16]
	ldrb	r0, [r4, #144]	@ zero_extendqisi2
	ldrb	r1, [r4, #146]	@ zero_extendqisi2
	ldrb	ip, [r4, #3]	@ zero_extendqisi2
	bfi	r0, r6, #0, #2
	strne	r3, [r4, #232]
	str	lr, [r4, #200]
	bfi	r1, ip, #1, #1
	strb	r0, [r4, #144]
	strb	r1, [r4, #146]
	ldr	r3, [r5, #2844]
	ldr	r1, [r4, #28]
	ldr	r3, [r3, #596]
	str	r3, [r4, #204]
	ldr	r3, [r5, #2844]
	ldr	r3, [r3, #600]
	str	r3, [r4, #208]
	ldr	r3, [r5, #2844]
	ldr	r3, [r3, #604]
	str	r3, [r4, #212]
	ldr	r0, [r5, #276]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L1322
	ldr	r3, .L1361
	mov	r2, #632
	add	r1, r4, #80
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #16
	str	r3, [r5, #296]
	mov	r3, #1
	ldr	r2, [r4, #56]
	strb	r3, [r5, #291]
	cmp	r2, #0
	strb	r3, [r5, #289]
	moveq	r3, #0
	movne	r3, #4
	strb	r3, [r5, #284]
	ldr	r3, [r4, #68]
	str	r3, [r5, #236]
.L1322:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1360:
	bic	r3, r3, #8
	cmp	r3, #2
	moveq	ip, #2
	movne	ip, #3
	b	.L1330
.L1359:
	ldr	r0, [r5, #276]
	strd	r6, [sp]
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L1324
	ldrd	r2, [r8, #-8]
	mov	r0, #29
	ldr	r1, .L1361+4
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	add	r10, r5, r3, lsl #2
	ldrd	r2, [r8, #-8]
	ldr	r1, [r10, #3196]
	add	r1, r1, #672
	strd	r2, [r1, #-8]
	strd	r6, [r8, #-8]
	b	.L1324
.L1362:
	.align	2
.L1361:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC103
	UNWIND(.fnend)
	.size	HEVC_GetImagePara, .-HEVC_GetImagePara
	.align	2
	.global	HEVC_CheckOutputImage
	.type	HEVC_CheckOutputImage, %function
HEVC_CheckOutputImage:
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
	cmp	r1, #19
	bhi	.L1365
	mov	r3, #712
	mla	r1, r3, r1, r0
	add	r1, r1, #13696
	ldrb	r0, [r1, #17]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1365:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_CheckOutputImage, .-HEVC_CheckOutputImage
	.align	2
	.global	HEVC_DECRecycleImage
	.type	HEVC_DECRecycleImage, %function
HEVC_DECRecycleImage:
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
	mov	r8, r0
	ldr	r0, [r0, #276]
	mov	r9, r1
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1371
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	addne	r4, r0, #576
	addne	r5, r0, #608
	movne	r6, #0
	movne	r7, #0
	beq	.L1376
.L1370:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1369
	ldr	r0, [r8, #276]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1369:
	cmp	r4, r5
	bne	.L1370
	ldr	r0, [r8, #276]
	mov	r1, r9
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1376:
	ldr	r1, .L1377
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1371:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1378:
	.align	2
.L1377:
	.word	.LC104
	UNWIND(.fnend)
	.size	HEVC_DECRecycleImage, .-HEVC_DECRecycleImage
	.align	2
	.global	HEVC_GetSLHDR1MasteringDisplayInfo
	.type	HEVC_GetSLHDR1MasteringDisplayInfo, %function
HEVC_GetSLHDR1MasteringDisplayInfo:
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
	ldr	r3, [r1, #572]
	movw	r2, #14999
	cmp	r3, r2
	bhi	.L1383
	sub	r2, r3, #8448
	movw	ip, #4749
	sub	r2, r2, #52
	cmp	r2, ip
	movls	r3, #1
	strlsb	r3, [r0, #3]
	bls	.L1381
	sub	r3, r3, #13248
	movw	r2, #1749
	sub	r3, r3, #2
	cmp	r3, r2
	bhi	.L1383
	mov	r3, #2
	strb	r3, [r0, #3]
.L1381:
	ldr	r3, [r1, #604]
	movw	r2, #56963
	movt	r2, 17179
	mov	ip, #50
	add	r3, r3, #249856
	movw	lr, #10000
	add	r3, r3, #144
	movw	r4, #2063
	movt	r4, 1526
	umull	r2, r3, r3, r2
	mov	r3, r3, lsr #17
	mul	r3, ip, r3
	cmp	r3, lr
	movcs	r3, lr
	strh	r3, [r0, #4]	@ movhi
	ldr	r3, [r1, #608]
	cmp	r3, r4
	movwls	r2, #5977
	movtls	r2, 53687
	umullls	r2, r3, r3, r2
	ubfxls	lr, r3, #13, #16
	strh	lr, [r0, #6]	@ movhi
	ldmfd	sp, {r4, fp, sp, pc}
.L1383:
	mov	r3, #0
	strb	r3, [r0, #3]
	b	.L1381
	UNWIND(.fnend)
	.size	HEVC_GetSLHDR1MasteringDisplayInfo, .-HEVC_GetSLHDR1MasteringDisplayInfo
	.align	2
	.global	HEVC_PrintSLHDR1Info
	.type	HEVC_PrintSLHDR1Info, %function
HEVC_PrintSLHDR1Info:
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
	ldr	r1, .L1405
	mov	r4, r0
	ldrb	r2, [r0]	@ zero_extendqisi2
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	ldr	r1, .L1405+4
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r1, .L1405+8
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	ldr	r1, .L1405+12
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #4]
	ldr	r1, .L1405+16
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #6]
	ldr	r1, .L1405+20
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ldr	r1, .L1405+24
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #9]	@ zero_extendqisi2
	ldr	r1, .L1405+28
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	mov	r0, #32
	cmp	r5, #0
	bne	.L1387
	ldr	r1, .L1405+32
	bl	dprint_vfmw
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	ldr	r1, .L1405+36
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	ldr	r1, .L1405+40
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	ldr	r1, .L1405+44
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	ldr	r1, .L1405+48
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #15]	@ zero_extendqisi2
	ldr	r1, .L1405+52
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #15
	addne	r6, r4, #26
	beq	.L1392
.L1391:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1405+56
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1405+60
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1391
.L1392:
	ldrb	r2, [r4, #38]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1405+64
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #38
	addne	r6, r4, #45
	movne	r5, #0
	beq	.L1393
.L1394:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1405+68
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1405+72
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1394
.L1393:
	movw	r2, #290
	ldr	r1, .L1405+76
	mov	r0, #32
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1387:
	ldr	r1, .L1405+80
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #10
	addne	r6, r4, #78
	movne	r5, #0
	beq	.L1399
.L1398:
	mov	r2, r5
	ldrh	r3, [r7, #2]!
	ldr	r1, .L1405+84
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r3, [r6, #2]!
	mov	r2, r5
	ldr	r1, .L1405+88
	mov	r0, #32
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1398
.L1399:
	ldrb	r2, [r4, #148]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1405+92
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #148
	addne	r6, r4, #216
	movne	r5, #0
	beq	.L1397
.L1400:
	mov	r3, r5
	ldrh	r2, [r7, #2]!
	ldr	r1, .L1405+96
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrh	r2, [r6, #2]!
	mov	r0, #32
	ldr	r1, .L1405+100
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1400
.L1397:
	movw	r3, #286
	ldr	r1, .L1405+104
	ldrh	r2, [r4, r3]
	add	r4, r4, #288
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r1, .L1405+108
	ldrh	r2, [r4]
	mov	r0, #32
	bl	dprint_vfmw
	b	.L1393
.L1406:
	.align	2
.L1405:
	.word	.LC105
	.word	.LC106
	.word	.LC107
	.word	.LC108
	.word	.LC109
	.word	.LC110
	.word	.LC111
	.word	.LC112
	.word	.LC113
	.word	.LC114
	.word	.LC115
	.word	.LC116
	.word	.LC117
	.word	.LC118
	.word	.LC120
	.word	.LC121
	.word	.LC119
	.word	.LC122
	.word	.LC123
	.word	.LC132
	.word	.LC124
	.word	.LC126
	.word	.LC127
	.word	.LC125
	.word	.LC130
	.word	.LC131
	.word	.LC128
	.word	.LC129
	UNWIND(.fnend)
	.size	HEVC_PrintSLHDR1Info, .-HEVC_PrintSLHDR1Info
	.align	2
	.global	HEVC_GetSLHDR1Info
	.type	HEVC_GetSLHDR1Info, %function
HEVC_GetSLHDR1Info:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 296
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #312)
	sub	sp, sp, #312
	mov	r6, r1
	mov	r5, r0
	mov	r4, r2
	sub	r0, fp, #320
	movw	r2, #290
	mov	r1, #0
	bl	memset
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1410
	ldrb	r2, [r4, #56]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1453
.L1410:
	ldrb	r2, [r4, #56]	@ zero_extendqisi2
	ldrb	ip, [r4, #568]	@ zero_extendqisi2
	ldrb	r0, [r4, #59]	@ zero_extendqisi2
	ldrb	r1, [r4, #128]	@ zero_extendqisi2
.L1409:
	str	r1, [sp, #12]
	str	r0, [sp, #8]
	mov	r0, #22
	stmia	sp, {r2, ip}
	ldr	r1, .L1456
	ldr	r2, .L1456+4
	bl	dprint_vfmw
	mov	r3, #0
	strb	r3, [r5, #458]
.L1407:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1453:
	ldrb	ip, [r4, #568]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1410
	ldrb	r1, [r4, #59]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1411
	ldrb	r1, [r4, #128]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1454
.L1411:
	mov	r3, #1
	strb	r3, [r5, #458]
	ldr	r0, [r6, #24]
	ldrb	r1, [r4, #57]	@ zero_extendqisi2
	ldrb	r2, [r4, #58]	@ zero_extendqisi2
	cmp	r0, #9
	strb	r1, [fp, #-320]
	strb	r2, [fp, #-319]
	bne	.L1413
	ldr	r2, [r6, #32]
	cmp	r2, #9
	streqb	r3, [fp, #-312]
.L1413:
	ldrb	r3, [r4, #60]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1414
	ldrb	r2, [r4, #129]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1414
	cmp	r2, #9
	cmpne	r3, #9
	ldrneb	r3, [fp, #-312]	@ zero_extendqisi2
	moveq	r3, #1
	strb	r3, [fp, #-318]
.L1414:
	mov	r1, r4
	sub	r0, fp, #320
	bl	HEVC_GetSLHDR1MasteringDisplayInfo
	ldrb	r3, [fp, #-318]	@ zero_extendqisi2
	ldrb	r2, [fp, #-312]	@ zero_extendqisi2
	cmp	r2, r3
	ldreqb	r3, [fp, #-317]	@ zero_extendqisi2
	movne	r3, #0
	strb	r3, [fp, #-311]
	ldrb	r3, [fp, #-319]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1418
	ldrb	r7, [r4, #66]	@ zero_extendqisi2
	ldrb	lr, [r4, #61]	@ zero_extendqisi2
	ldrb	ip, [r4, #62]	@ zero_extendqisi2
	cmp	r7, #0
	ldrb	r0, [r4, #63]	@ zero_extendqisi2
	ldrb	r1, [r4, #64]	@ zero_extendqisi2
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	strb	r7, [fp, #-305]
	strb	lr, [fp, #-310]
	strb	ip, [fp, #-309]
	strb	r0, [fp, #-308]
	strb	r1, [fp, #-307]
	strb	r2, [fp, #-306]
	beq	.L1423
	sub	r2, fp, #320
	add	ip, r4, #66
	add	r0, r2, #15
	add	r1, r4, #81
	add	r2, r2, #26
.L1422:
	add	r3, r3, #1
	ldrb	r6, [ip, #1]!	@ zero_extendqisi2
	ldrb	lr, [r1, #1]!	@ zero_extendqisi2
	cmp	r3, r7
	strb	r6, [r0, #1]!
	strb	lr, [r2, #1]!
	bne	.L1422
.L1423:
	ldrb	r6, [r4, #97]	@ zero_extendqisi2
	cmp	r6, #0
	strb	r6, [fp, #-282]
	beq	.L1421
	sub	r1, fp, #280
	sub	r2, fp, #272
	add	r0, r4, #97
	sub	r1, r1, #2
	add	r4, r4, #112
	sub	r2, r2, #3
	mov	r3, #0
.L1426:
	add	r3, r3, #1
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	ldrb	ip, [r4, #1]!	@ zero_extendqisi2
	cmp	r3, r6
	strb	lr, [r1, #1]!
	strb	ip, [r2, #1]!
	bne	.L1426
.L1421:
	ldr	r3, [r5, #464]
	cmp	r3, #0
	bne	.L1455
	ldr	r2, .L1456+4
	mov	r0, #1
	ldr	r1, .L1456+8
	bl	dprint_vfmw
	b	.L1407
.L1418:
	ldrb	r6, [r4, #168]	@ zero_extendqisi2
	ldr	r2, [r4, #136]
	add	r6, r6, #1
	ldr	r3, [r4, #140]
	uxtb	r6, r6
	strh	r2, [fp, #-34]	@ movhi
	cmp	r6, #0
	strh	r3, [fp, #-32]	@ movhi
	strb	r6, [fp, #-310]
	addne	r0, r4, #170
	addne	r1, r4, #368
	subne	r3, fp, #320
	movne	r2, #0
	beq	.L1430
.L1429:
	add	r2, r2, #1
	ldrh	lr, [r0, #2]!
	ldrh	ip, [r1, #2]!
	cmp	r2, r6
	add	r3, r3, #2
	strh	lr, [r3, #10]	@ movhi
	strh	ip, [r3, #78]	@ movhi
	bcc	.L1429
.L1430:
	ldrb	lr, [r4, #169]	@ zero_extendqisi2
	add	lr, lr, #1
	uxtb	lr, lr
	strb	lr, [fp, #-172]
	cmp	lr, #0
	beq	.L1421
	add	r1, r4, #432
	sub	r3, fp, #320
	add	r4, r4, #236
	add	r1, r1, #2
	mov	r2, #0
.L1431:
	add	r2, r2, #1
	ldrh	ip, [r4, #2]!
	ldrh	r0, [r1, #2]!
	cmp	r2, lr
	add	r3, r3, #2
	strh	ip, [r3, #148]	@ movhi
	strh	r0, [r3, #216]	@ movhi
	bcc	.L1431
	b	.L1421
.L1455:
	ldr	r3, .L1456+12
	sub	r1, fp, #320
	movw	r2, #290
	ldr	r0, [r5, #472]
	ldr	r3, [r3, #52]
	blx	r3
	movw	r3, #290
	str	r3, [r5, #460]
	b	.L1407
.L1454:
	mov	r0, r1
	b	.L1409
.L1457:
	.align	2
.L1456:
	.word	.LC133
	.word	.LANCHOR0+444
	.word	.LC134
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_GetSLHDR1Info, .-HEVC_GetSLHDR1Info
	.align	2
	.global	HEVC_ConvertHDRInfo
	.type	HEVC_ConvertHDRInfo, %function
HEVC_ConvertHDRInfo:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldrb	r5, [r1]	@ zero_extendqisi2
	mov	r3, r0
	mov	ip, r2
	add	lr, r0, #484
	add	lr, lr, #2
	add	r4, r0, #492
	strb	r5, [r3, #480]
	mov	r0, r2
	ldr	r5, [r1, #24]
	mov	r2, #0
	strb	r5, [r3, #481]
	ldr	r5, [r1, #32]
	strb	r5, [r3, #482]
	ldr	r5, [r1, #28]
	str	r5, [r3, #484]
	ldrb	r5, [ip, #568]	@ zero_extendqisi2
	strb	r5, [r3, #456]
.L1459:
	ldr	r5, [r0, #572]
	add	r2, r2, #1
	cmp	r2, #3
	add	r0, r0, #4
	strh	r5, [lr, #2]!	@ movhi
	ldr	r5, [r0, #580]
	strh	r5, [r4, #2]!	@ movhi
	bne	.L1459
	ldr	r0, [ip, #596]
	add	lr, r3, #456
	movw	r5, #614
	add	r4, ip, #616
	mov	r2, ip
	strh	r0, [lr, #44]	@ movhi
	mov	r0, r3
	ldr	r6, [ip, #600]
	strh	r6, [lr, #46]	@ movhi
	ldr	lr, [ip, #604]
	str	lr, [r3, #504]
	ldr	lr, [ip, #608]
	str	lr, [r3, #508]
	ldrb	lr, [ip, #612]	@ zero_extendqisi2
	strb	lr, [r3, #457]
	ldrh	lr, [ip, r5]
	str	lr, [r3, #512]
	ldrh	lr, [r4]
	str	lr, [r3, #516]
	ldrb	ip, [ip, #618]	@ zero_extendqisi2
	strb	ip, [r3, #520]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	HEVC_GetSLHDR1Info
	UNWIND(.fnend)
	.size	HEVC_ConvertHDRInfo, .-HEVC_ConvertHDRInfo
	.align	2
	.global	HEVC_AllocFrameStore
	.type	HEVC_AllocFrameStore, %function
HEVC_AllocFrameStore:
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
	add	r6, r0, #4096
	ldr	r3, [r0, #2808]
	movw	ip, #5036
	mov	r7, r0
	ldr	r2, [r6, #732]
	movw	r5, #12668
	ldr	r0, [r0, #2804]
	add	lr, r7, #13696
	mov	r1, #0
	add	lr, lr, #16
	mla	r3, ip, r2, r3
	mov	r8, r1
	ldr	r3, [r3, #32]
	strb	r1, [r6, #1]
	mla	r5, r5, r3, r0
.L1466:
	ldr	r3, [lr, #48]
	cmp	r3, #0
	bne	.L1462
	cmp	lr, #0
	beq	.L1473
	ldr	r1, [r7, #3028]
	cmp	r1, #0
	beq	.L1473
	ldr	r2, [r7, #3196]
	cmp	r2, lr
	beq	.L1462
	add	r2, r7, #3184
	add	r2, r2, #12
	b	.L1464
.L1465:
	ldr	ip, [r2, #4]!
	cmp	ip, lr
	beq	.L1462
.L1464:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L1465
.L1473:
	mov	r3, #712
	add	r9, r7, #4160
	mla	r8, r3, r8, r7
	mov	r2, #101
	mov	r3, #1
	str	r2, [r6, #40]
	strb	r3, [r6, #1]
	mov	r2, #632
	add	r1, r8, #13760
	mov	r0, r9
	add	r1, r1, #32
	mov	r4, lr
	bl	memcpy
	add	r3, r8, #13696
	movw	r2, #13728
	str	r4, [r6, #60]
	mov	r10, #0
	str	r10, [r6, #216]
	str	r10, [r8, r2]
	strb	r10, [r3, #18]
	strb	r10, [r4]
	ldr	r3, [r6, #60]
	str	r10, [r3, #60]
	ldr	r3, [r6, #60]
	str	r10, [r3, #64]
	ldr	r3, [r6, #60]
	str	r10, [r3, #52]
	ldrb	r1, [r6, #1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1470
	ldr	r0, [r7, #276]
	bl	FSP_NewLogicFs
	mov	r8, r0
	mov	r1, r0
	ldr	r0, [r7, #276]
	bl	FSP_GetLogicFs
	mvn	r3, r8
	mov	r3, r3, lsr #31
	cmp	r0, #0
	mov	r4, r0
	moveq	r3, #0
	cmp	r3, #0
	beq	.L1468
	add	r1, r5, #2064
	add	r2, r7, #3472
	bl	HEVC_ConvertHDRInfo
	ldr	r3, [r7, #2844]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1477
.L1469:
	ldr	r5, .L1478
	add	r1, r4, #40
	ldr	r0, [r6, #60]
	mov	r2, #632
	ldr	r3, [r5, #52]
	add	r0, r0, #80
	blx	r3
	ldr	r1, [r6, #60]
	ldr	r3, [r5, #52]
	mov	r0, r9
	add	r1, r1, #80
	mov	r2, #632
	blx	r3
	ldr	r3, [r6, #60]
	mov	r0, #0
	str	r8, [r3, #28]
	ldrsb	r3, [r4, #4]
	str	r3, [r6, #36]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1462:
	add	r8, r8, #1
	add	lr, lr, #712
	cmp	r8, #20
	bne	.L1466
.L1470:
	ldr	r1, .L1478+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1477:
	ldr	r1, [r7, #2828]
	ldr	r5, [r4, #152]
	ldr	r3, [r4, #76]
	ldr	r2, [r1, #68]
	ldr	r1, [r1, #64]
	str	r10, [r4, #280]
	mul	r5, r5, r2
	str	r2, [r4, #112]
	str	r1, [r4, #108]
	str	r10, [r4, #284]
	add	r3, r5, r3
	str	r10, [r4, #288]
	str	r3, [r4, #80]
	mov	r0, r3
	str	r10, [r4, #292]
	str	r10, [r4, #296]
	bl	MEM_Phy2Vir
	ldr	r2, [r4, #60]
	ldr	r3, [r4, #156]
	add	r5, r5, r2
	str	r10, [r4, #556]
	str	r5, [r4, #64]
	add	r5, r5, r3
	str	r5, [r4, #72]
	str	r0, [r4, #552]
	b	.L1469
.L1468:
	strb	r3, [r6, #1]
	mov	r0, r3
	ldr	r1, .L1478+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1479:
	.align	2
.L1478:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC135
	.word	.LC136
	UNWIND(.fnend)
	.size	HEVC_AllocFrameStore, .-HEVC_AllocFrameStore
	.align	2
	.global	HEVC_IsVoFinish
	.type	HEVC_IsVoFinish, %function
HEVC_IsVoFinish:
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
	mov	r5, r0
	ldr	r0, [r0, #276]
	bl	FSP_GetFspType
	cmn	r0, #1
	mov	r4, r0
	movne	r4, #0
	bne	.L1484
	b	.L1487
.L1483:
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1485
	cmp	r4, #32
	beq	.L1488
.L1484:
	mov	r1, r4
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	add	r4, r4, #1
	cmp	r0, #0
	bne	.L1483
	ldr	r1, .L1489
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1487:
	ldr	r1, .L1489+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1485:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1488:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1490:
	.align	2
.L1489:
	.word	.LC138
	.word	.LC137
	UNWIND(.fnend)
	.size	HEVC_IsVoFinish, .-HEVC_IsVoFinish
	.align	2
	.global	HEVC_GetBackPicFromVOQueue
	.type	HEVC_GetBackPicFromVOQueue, %function
HEVC_GetBackPicFromVOQueue:
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
	mov	r8, r0
	add	r0, r0, #6144
	add	r0, r0, #24
	add	r5, r8, #14336
	bl	ResetVoQueue
	add	r9, r8, #28416
	add	r5, r5, #24
	add	r9, r9, #184
	mov	r6, #0
	mov	r7, #0
.L1494:
	sub	r4, r5, #32
	mov	r3, #0
	strb	r3, [r5, #-647]
	str	r3, [r5, #-600]
.L1493:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1492
	ldr	r0, [r8, #276]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1492:
	cmp	r4, r5
	bne	.L1493
	add	r5, r4, #712
	cmp	r5, r9
	bne	.L1494
	ldr	r2, [r8, #184]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r8, r8, #2144
	mov	r3, #0
	add	r8, r8, #8
	mov	r1, r3
.L1496:
	add	r3, r3, #1
	str	r1, [r8, #4]!
	cmp	r3, r2
	bne	.L1496
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetBackPicFromVOQueue, .-HEVC_GetBackPicFromVOQueue
	.align	2
	.global	HEVC_RemoveFrameStoreOutDPB
	.type	HEVC_RemoveFrameStoreOutDPB, %function
HEVC_RemoveFrameStoreOutDPB:
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
	add	r6, r0, r1, lsl #2
	mov	r7, #0
	mov	r4, r1
	mov	r5, r0
	ldr	r3, [r6, #3196]
	str	r7, [r3, #48]
	ldr	r3, [r6, #3196]
	ldr	r0, [r0, #276]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1505
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1506
	ldr	r3, [r6, #3196]
	mov	r2, r7
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
.L1506:
	ldr	r3, [r6, #3196]
	mov	r2, #0
	ldr	r0, [r5, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
.L1505:
	ldr	r1, [r5, #3028]
	sub	r1, r1, #1
	cmp	r4, r1
	addls	r3, r4, #796
	addls	r3, r3, #3
	addls	r3, r5, r3, lsl #2
	bhi	.L1509
.L1508:
	add	r4, r4, #1
	ldr	r2, [r3, #4]!
	cmp	r4, r1
	str	r2, [r3, #-4]
	bls	.L1508
.L1509:
	add	r3, r1, #796
	mov	r2, #0
	add	r3, r3, #2
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	str	r1, [r5, #3028]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveFrameStoreOutDPB, .-HEVC_RemoveFrameStoreOutDPB
	.align	2
	.global	HEVC_RemoveDummyFrame
	.type	HEVC_RemoveDummyFrame, %function
HEVC_RemoveDummyFrame:
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
	ldr	r3, [r0, #3028]
	mov	r5, r0
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r7, #0
	mov	r4, r7
	mov	r6, r7
	b	.L1521
.L1520:
	ldr	r3, [r5, #3028]
	add	r4, r4, #1
	cmp	r4, r3
	mov	r7, r4
	bcs	.L1527
.L1521:
	add	r3, r5, r4, lsl #2
	ldr	r3, [r3, #3196]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1520
	mov	r1, r7
	mov	r0, r5
	strb	r6, [r3]
	sub	r4, r4, #1
	bl	HEVC_RemoveApcStore
	mov	r1, r7
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
	b	.L1520
.L1527:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_RemoveDummyFrame, .-HEVC_RemoveDummyFrame
	.align	2
	.global	HEVC_RemoveUnUsedFrameStore
	.type	HEVC_RemoveUnUsedFrameStore, %function
HEVC_RemoveUnUsedFrameStore:
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
	ldr	r5, [r0, #3028]
	mov	r7, r0
	cmp	r5, #0
	beq	.L1537
	mov	r6, #0
	mvn	r8, #0
	mov	r10, r6
	mov	r9, r6
	b	.L1536
.L1547:
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	cmpne	r3, #3
	ldr	r3, [r4, #3196]
	bne	.L1532
	ldr	r0, [r3, #52]
	cmp	r0, #1
	beq	.L1532
	str	r8, [r3, #28]
	mov	r2, #1
	ldr	r3, [r4, #3196]
	strb	r1, [r3, #1]
	ldr	r3, [r4, #3196]
	strb	r2, [r3, #2]
	ldr	r3, [r4, #3196]
.L1532:
	ldr	r3, [r3]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	addne	r10, r10, #1
	beq	.L1546
	add	r9, r9, #1
	cmp	r9, r5
	beq	.L1529
.L1536:
	add	r4, r7, r10, lsl #2
	ldr	r0, [r7, #276]
	ldr	r3, [r4, #3196]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1530
	ldrsb	r1, [r0]
	cmp	r1, #0
	beq	.L1547
	ldr	r3, [r4, #3196]
	b	.L1532
.L1530:
	ldr	r3, [r4, #3196]
	ldr	r1, [r3, #52]
	cmp	r1, #1
	beq	.L1532
	str	r8, [r3, #28]
	mov	r2, #1
	ldr	r3, [r4, #3196]
	strb	r0, [r3, #1]
	ldr	r3, [r4, #3196]
	strb	r2, [r3, #2]
	ldr	r3, [r4, #3196]
	b	.L1532
.L1546:
	mov	r1, r10
	mov	r0, r7
	add	r9, r9, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	cmp	r9, r5
	mov	r6, #1
	bne	.L1536
.L1529:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1537:
	mov	r6, r5
	b	.L1529
	UNWIND(.fnend)
	.size	HEVC_RemoveUnUsedFrameStore, .-HEVC_RemoveUnUsedFrameStore
	.align	2
	.global	HEVC_SimpleSlideDPB
	.type	HEVC_SimpleSlideDPB, %function
HEVC_SimpleSlideDPB:
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
	add	r3, r0, #12288
	mov	r4, r0
	ldr	r1, [r3, #864]
	ldr	r2, [r3, #860]
	cmp	r1, r2
	bcs	.L1550
	ldr	r2, [r3, #1144]
	ldr	r3, [r3, #1140]
	cmp	r2, r3
	bcs	.L1550
	ldr	r3, [r0, #3024]
	ldr	r2, [r0, #3028]
	cmp	r2, r3
	ldmccfd	sp, {r4, r5, fp, sp, pc}
	cmp	r3, #15
	bls	.L1554
.L1550:
	ldr	r3, [r4, #3196]
	mov	r5, #0
	mov	r2, r5
	strb	r5, [r3, #1]
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetRef
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVC_RemoveFrameStoreOutDPB
.L1554:
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L1550
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SimpleSlideDPB, .-HEVC_SimpleSlideDPB
	.align	2
	.global	HEVC_GetMinPOC
	.type	HEVC_GetMinPOC, %function
HEVC_GetMinPOC:
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
	mov	r7, r2
	mvn	r3, #-2147483648
	mov	r2, #0
	str	r2, [r7]
	str	r3, [r1]
	mov	r5, r1
	ldr	r2, [r0, #3028]
	mov	r6, r0
	ldr	r3, [r0, #3024]
	cmp	r2, r3
	bhi	.L1562
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1563:
	add	lr, r6, #3184
	mov	r3, #0
	add	lr, lr, #8
.L1559:
	ldr	r2, [lr, #4]!
	ldr	r4, [r5]
	ldr	ip, [r2, #8]
	cmp	r4, ip
	strgt	ip, [r5]
	strgt	r3, [r7]
	add	r3, r3, #1
	ldr	ip, [r6, #3028]
	cmp	ip, r3
	bhi	.L1559
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1562:
	ldr	r1, .L1564
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #3024]
	cmp	r2, #0
	str	r2, [r6, #3028]
	bne	.L1563
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1565:
	.align	2
.L1564:
	.word	.LC139
	UNWIND(.fnend)
	.size	HEVC_GetMinPOC, .-HEVC_GetMinPOC
	.align	2
	.global	HEVC_GetReRangeFlag
	.type	HEVC_GetReRangeFlag, %function
HEVC_GetReRangeFlag:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #4096
	ldr	r5, [r0, #2808]
	movw	r6, #5036
	movw	r4, #12668
	ldr	ip, [r3, #732]
	ldr	r3, [r0, #2804]
	ldr	lr, [fp, #4]
	mla	ip, r6, ip, r5
	ldr	ip, [ip, #32]
	mla	r3, r4, ip, r3
	ldr	ip, [r3, #64]
	ldr	r3, [r3, #68]
	cmp	r1, ip
	cmpeq	lr, #0
	bne	.L1567
	cmp	r2, r3
	beq	.L1578
.L1567:
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1579
.L1572:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1579:
	ldr	r2, [r0, #2844]
	ldr	r2, [r2, #24]
	bics	r2, r2, #4
	beq	.L1572
	ldr	r2, [r0, #2384]
	cmp	r2, #0
	bne	.L1577
	str	r3, [r0, #2384]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1578:
	ldr	r3, [r0, #172]
	cmp	r3, #0
	beq	.L1567
	ldr	r3, [r0, #2844]
	ldr	r3, [r3, #904]
	cmp	r3, #0
	bne	.L1567
.L1577:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetReRangeFlag, .-HEVC_GetReRangeFlag
	.align	2
	.global	HEVC_CalcStreamBits
	.type	HEVC_CalcStreamBits, %function
HEVC_CalcStreamBits:
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
	ldr	r4, [r0, #2816]
	ldrb	ip, [r4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1591
	mov	r3, #0
	mov	r2, r4
	mov	lr, r3
.L1582:
	add	r3, r3, #1
	ldr	r1, [r2, #44]
	cmp	r3, ip
	add	r2, r2, #28
	add	lr, lr, r1
	bne	.L1582
.L1581:
	ldr	r2, [r0, #2796]
	mov	r3, ip, asl #5
	sub	ip, r3, ip, asl #2
	add	r4, r4, ip
	ldr	r3, [r2, #24]
	and	r3, r3, #7
	str	r3, [r4, #56]
	ldr	r2, [r0, #2816]
	ldr	r3, [r0, #2796]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #48]
	add	r2, r2, ip, lsr #3
	rsb	r2, lr, r2
	str	r2, [r3, #60]
	ldr	r1, [r0, #2816]
	ldr	r3, [r0, #2796]
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r2, asl #5
	sub	r2, r3, r2, asl #2
	add	r2, r1, r2
	ldr	r3, [r2, #44]
	add	r3, lr, r3
	rsb	r3, ip, r3, lsl #3
	str	r3, [r2, #52]
	ldr	r2, [r0, #2816]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	ldr	r1, [r3, #56]
	and	r2, r2, #3
	add	r2, r1, r2, lsl #3
	str	r2, [r3, #56]
	ldr	r2, [r0, #2816]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #3
	str	r2, [r3, #60]
	ldr	r1, [r0, #2816]
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L1598
	ldrb	ip, [r1]	@ zero_extendqisi2
	add	lr, ip, #1
	cmp	r2, lr
	movhi	r2, #1
	movls	r2, #0
	cmp	lr, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1584
	add	ip, ip, #2
	mov	lr, #0
.L1585:
	sub	r3, ip, #1
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	str	lr, [r1, #56]
	ldr	r2, [r0, #2816]
	add	r2, r2, r3
	ldr	r1, [r2, #48]
	str	r1, [r2, #60]
	ldr	r2, [r0, #2816]
	add	r2, r2, r3
	ldr	r1, [r2, #44]
	mov	r1, r1, asl #3
	str	r1, [r2, #52]
	ldr	r2, [r0, #2816]
	add	r2, r2, r3
	ldr	r1, [r2, #60]
	ldr	r4, [r2, #56]
	and	r1, r1, #15
	add	r1, r4, r1, lsl #3
	str	r1, [r2, #56]
	ldr	r2, [r0, #2816]
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #15
	str	r2, [r3, #60]
	ldr	r1, [r0, #2816]
	ldr	r3, [r1, #8]
	cmp	ip, #1
	cmpls	ip, r3
	add	ip, ip, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L1585
	sub	r3, r3, #1
.L1584:
	mov	r2, r3, asl #5
	ldr	ip, [r1, #12]
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	ldr	r3, [r1, #52]
	rsb	r3, ip, r3
	str	r3, [r1, #52]
	ldr	lr, [r0, #2816]
	ldrb	r1, [lr]	@ zero_extendqisi2
	ldr	r3, [lr, #8]
	cmp	r1, r3
	ldmcsfd	sp, {r4, fp, sp, pc}
	sxth	r3, r1
	add	r0, r0, #4096
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, lr, r3
.L1589:
	ldr	r2, [r3, #60]
	add	r1, r1, #1
	ldr	ip, [r0, #32]
	add	r3, r3, #28
	cmp	r2, ip
	strcc	r2, [r0, #32]
	ldr	r2, [lr, #8]
	cmp	r2, r1
	bhi	.L1589
	ldmfd	sp, {r4, fp, sp, pc}
.L1598:
	ldr	r1, .L1599
	mov	r0, #0
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L1591:
	mov	lr, ip
	b	.L1581
.L1600:
	.align	2
.L1599:
	.word	.LC140
	UNWIND(.fnend)
	.size	HEVC_CalcStreamBits, .-HEVC_CalcStreamBits
	.align	2
	.global	HEVC_VpsSpsPpsCheck
	.type	HEVC_VpsSpsPpsCheck, %function
HEVC_VpsSpsPpsCheck:
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
	add	r2, r0, #4096
	ldr	r3, [r0, #164]
	ldr	r2, [r2, #732]
	cmp	r2, r3
	bge	.L1609
	movw	r3, #5036
	ldr	r1, [r0, #2808]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1610
	ldr	r2, [ip, #32]
	ldr	r3, [r0, #160]
	cmp	r2, r3
	bge	.L1611
	ldr	r1, [r0, #2804]
	movw	r3, #12668
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1612
	ldr	r2, [r3, #48]
	ldr	r3, [r0, #156]
	cmp	r2, r3
	bcs	.L1613
	movw	r3, #24912
	ldr	r1, [r0, #2800]
	mul	r3, r3, r2
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1614
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1609:
	ldr	r1, .L1615
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1610:
	ldr	r1, .L1615+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1611:
	ldr	r1, .L1615+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1612:
	ldr	r1, .L1615+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1613:
	ldr	r1, .L1615+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1614:
	ldr	r1, .L1615+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1616:
	.align	2
.L1615:
	.word	.LC141
	.word	.LC142
	.word	.LC143
	.word	.LC144
	.word	.LC145
	.word	.LC146
	UNWIND(.fnend)
	.size	HEVC_VpsSpsPpsCheck, .-HEVC_VpsSpsPpsCheck
	.align	2
	.global	HEVC_IsNewPic
	.type	HEVC_IsNewPic, %function
HEVC_IsNewPic:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	add	r1, r0, #4096
	ldr	ip, [r0, #2816]
	ldr	r2, [r1, #728]
	ldr	r3, [ip, #16]
	add	r4, r0, r2, lsl #2
	sub	r5, r3, #16
	ldr	lr, [r4, #244]
	cmn	lr, #-2147483647
	beq	.L1651
	cmp	r3, #21
	cmpne	r5, #2
	bls	.L1647
.L1631:
	sub	r3, r3, #19
	cmp	r3, #1
	movls	lr, #-2147483647
	strls	lr, [r4, #244]
.L1647:
	ldr	r5, [r1, #708]
	cmp	r5, lr
	bge	.L1621
	ldr	r3, [ip, #16]
	sub	r6, r3, #8
	cmp	r6, #1
	addhi	r2, r0, r2
	bls	.L1652
.L1624:
	ldrb	lr, [r2, #12]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L1625
	ldr	r6, [r4, #252]
	cmp	r5, r6
	blt	.L1653
.L1625:
	ldrb	r3, [r1, #697]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1626
	ldr	ip, [ip, #16]
	sub	lr, ip, #19
	cmp	lr, #1
	bls	.L1648
	cmp	ip, #21
	beq	.L1648
	sub	ip, ip, #16
	cmp	ip, #2
	strls	r5, [r4, #252]
	movls	r3, #1
	strlsb	r3, [r2, #12]
.L1626:
	ldr	r2, [r0, #260]
	ldrb	r3, [r1, #696]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [r1, #732]
	beq	.L1630
	ldr	r1, [r0, #208]
	cmp	r2, r1
	movne	r3, #1
.L1630:
	ldr	r1, [r0, #320]
	cmp	r1, r2
	movne	r0, #1
	beq	.L1654
.L1645:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1651:
	cmp	r5, #5
	bhi	.L1649
	cmp	r3, #21
	cmpne	r5, #2
	bhi	.L1631
	ldr	r5, [r1, #708]
	str	r5, [r4, #244]
.L1621:
	add	r2, r0, r2
	ldrb	lr, [r2, #6]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L1624
	ldr	r3, [ip, #16]
	sub	r6, r3, #8
	cmp	r6, #1
	bhi	.L1624
	str	r3, [sp, #8]
	mov	r0, #1
	movw	r3, #12854
	str	lr, [sp, #4]
	str	r5, [sp]
	ldr	r2, .L1655
	ldr	r1, .L1655+4
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1645
.L1653:
	ldr	r3, [ip, #16]
	sub	r7, r3, #8
	cmp	r7, #1
	bhi	.L1625
	str	r3, [sp, #12]
	mov	r0, #1
	movw	r3, #12863
	str	r6, [sp, #8]
	str	r5, [sp, #4]
	str	lr, [sp]
	ldr	r2, .L1655
	ldr	r1, .L1655+8
	bl	dprint_vfmw
.L1649:
	mov	r0, #2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1648:
	str	r5, [r4, #252]
	strb	r3, [r2, #12]
	b	.L1626
.L1654:
	ldr	r0, [r0, #284]
	cmp	r5, r0
	moveq	r0, r3
	movne	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1652:
	str	r3, [sp, #8]
	mov	r0, #1
	movw	r3, #12847
	str	lr, [sp, #4]
	str	r5, [sp]
	ldr	r2, .L1655
	ldr	r1, .L1655+12
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1645
.L1656:
	.align	2
.L1655:
	.word	.LANCHOR0+464
	.word	.LC148
	.word	.LC149
	.word	.LC147
	UNWIND(.fnend)
	.size	HEVC_IsNewPic, .-HEVC_IsNewPic
	.align	2
	.global	HEVC_ReadByteAlignment
	.type	HEVC_ReadByteAlignment, %function
HEVC_ReadByteAlignment:
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
	mov	r4, r0
	ldr	r0, [r0, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L1662
	ldr	r0, [r4, #2796]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	beq	.L1661
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r1, .L1663
	mov	r2, r0
	mov	r0, #19
	bl	dprint_vfmw
.L1661:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1662:
	ldr	r1, .L1663+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1664:
	.align	2
.L1663:
	.word	.LC151
	.word	.LC150
	UNWIND(.fnend)
	.size	HEVC_ReadByteAlignment, .-HEVC_ReadByteAlignment
	.align	2
	.global	HEVC_GetRapPicFlag
	.type	HEVC_GetRapPicFlag, %function
HEVC_GetRapPicFlag:
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
	add	r0, r0, #4096
	ldr	r0, [r0, #724]
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetRapPicFlag, .-HEVC_GetRapPicFlag
	.align	2
	.global	HEVC_GetIdrPicFlag
	.type	HEVC_GetIdrPicFlag, %function
HEVC_GetIdrPicFlag:
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
	add	r0, r0, #4096
	ldr	r0, [r0, #724]
	sub	r0, r0, #19
	cmp	r0, #1
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetIdrPicFlag, .-HEVC_GetIdrPicFlag
	.align	2
	.global	HEVC_DecPTL
	.type	HEVC_DecPTL, %function
HEVC_DecPTL:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #52)
	sub	sp, sp, #52
	subs	r8, r2, #0
	mov	r9, r1
	mov	r5, r0
	mov	r6, r3
	moveq	r1, #8
	bne	.L1704
.L1702:
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r6, #0
	str	r0, [r9, #4]
	ble	.L1673
	sub	r3, fp, #84
	sub	r7, fp, #92
	add	r10, r3, r6
	mov	r4, r3
	mov	r9, r7
.L1674:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4], #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r4, r10
	strb	r0, [r9], #1
	bne	.L1674
	cmp	r6, #7
	movle	r4, r6
	ble	.L1678
	b	.L1684
.L1677:
	cmp	r4, #8
	beq	.L1684
.L1678:
	mov	r1, #2
	ldr	r0, [r5, #2796]
	bl	BsGet
	add	r4, r4, #1
	cmp	r0, #0
	beq	.L1677
	ldr	r1, .L1706
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1673:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1684:
	mov	r10, #0
	b	.L1682
.L1681:
	add	r10, r10, #1
	cmp	r6, r10
	ble	.L1673
.L1682:
	cmp	r8, #0
	beq	.L1679
	sub	r3, fp, #84
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1705
.L1679:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1681
	mov	r1, #8
	ldr	r0, [r5, #2796]
	bl	BsGet
	b	.L1681
.L1705:
	mov	r1, #2
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	mov	r4, #32
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2796]
	bl	BsGet
.L1680:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L1680
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r5, #2796]
	bl	BsGet
	b	.L1679
.L1704:
	mov	r1, #2
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	sub	r4, fp, #77
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2796]
	sub	r7, fp, #45
	bl	BsGet
	mov	r10, r0
.L1669:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r7
	bne	.L1669
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #1]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	sub	r3, r10, #4
	cmp	r3, #3
	bls	.L1670
	ldrb	r3, [fp, #-72]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1670
	ldrb	r3, [fp, #-71]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1670
	ldrb	r3, [fp, #-70]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1670
	ldrb	r3, [fp, #-69]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1670
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #11
	ldr	r0, [r5, #2796]
	bl	BsGet
	b	.L1672
.L1670:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #2
	ldr	r0, [r5, #2796]
	bl	BsGet
.L1672:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldrb	r2, [fp, #-75]	@ zero_extendqisi2
	ldrb	r3, [fp, #-74]	@ zero_extendqisi2
	mov	r1, #8
	str	r10, [r5, #324]
	str	r2, [r5, #328]
	str	r3, [r5, #332]
	b	.L1702
.L1707:
	.align	2
.L1706:
	.word	.LC152
	UNWIND(.fnend)
	.size	HEVC_DecPTL, .-HEVC_DecPTL
	.align	2
	.global	HEVC_SetDefaultScalingList
	.type	HEVC_SetDefaultScalingList, %function
HEVC_SetDefaultScalingList:
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
	ldr	r9, .L1726
	add	r10, r0, #2224
	add	r3, r0, #2240
	add	r10, r10, #8
	mov	r6, #0
	add	r3, r3, #8
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L1709:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L1717
	ldr	r3, [fp, #-52]
	mov	r8, r6, asl #9
	ldr	r7, [fp, #-48]
	sub	r8, r8, r6, asl #7
	add	r5, r3, #620
	mov	r4, #0
.L1715:
	cmp	r6, #0
	add	r0, r5, r8
	mov	r2, #64
	ldr	r3, [r9, #52]
	beq	.L1724
	cmp	r6, #3
	beq	.L1725
	ldr	ip, .L1726+4
	cmp	r4, #2
	ldr	r1, .L1726+8
	movhi	r1, ip
	blx	r3
.L1711:
	mov	r3, #16
	str	r3, [r7, #4]!
	ldr	r3, [r10]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1715
.L1717:
	add	r6, r6, #1
	ldr	r3, [fp, #-48]
	cmp	r6, #4
	add	r3, r3, #24
	str	r3, [fp, #-48]
	bne	.L1709
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1724:
	mov	r2, #16
	ldr	r1, .L1726+12
	mov	r0, r5
	blx	r3
	b	.L1711
.L1725:
	ldr	r0, .L1726+4
	cmp	r4, #0
	ldr	r1, .L1726+8
	mov	r2, #64
	movne	r1, r0
	add	r0, r5, #1152
	blx	r3
	b	.L1711
.L1727:
	.align	2
.L1726:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+480
	.word	.LANCHOR4
	.word	.LANCHOR0+544
	UNWIND(.fnend)
	.size	HEVC_SetDefaultScalingList, .-HEVC_SetDefaultScalingList
	.align	2
	.global	HEVC_CalScalingList
	.type	HEVC_CalScalingList, %function
HEVC_CalScalingList:
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
	add	lr, r0, r2, lsl #2
	mov	ip, r2, asl #3
	sub	r2, ip, r2, asl #1
	mov	r5, #0
	ldr	r7, [lr, #348]
	add	r3, r3, r2
	cmp	r7, #64
	mov	r6, r3, asl #4
	movcs	r7, #64
	mov	r8, r7, lsr #2
.L1729:
	cmp	r5, r8
	ldmcsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r7, #0
	beq	.L1729
	add	r3, r5, r6
	ldrb	ip, [r1]	@ zero_extendqisi2
	mov	r4, r1
	mov	r2, #0
	add	r3, r0, r3, lsl #2
	ldr	lr, [r3, #620]
	orr	ip, lr, ip
	str	ip, [r3, #620]
.L1735:
	add	r2, r2, #1
	add	r3, r5, r6
	and	lr, r2, #3
	cmp	r2, r7
	add	r3, r0, r3, lsl #2
	mov	ip, lr, asl #3
	beq	.L1729
	ldrb	r9, [r4, #1]!	@ zero_extendqisi2
	cmp	lr, #3
	ldr	lr, [r3, #620]
	addeq	r5, r5, #1
	orr	ip, lr, r9, asl ip
	str	ip, [r3, #620]
	b	.L1735
	UNWIND(.fnend)
	.size	HEVC_CalScalingList, .-HEVC_CalScalingList
	.align	2
	.global	HEVC_SetScalingList
	.type	HEVC_SetScalingList, %function
HEVC_SetScalingList:
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
	ldr	r1, [r0, #2828]
	mov	r7, r0
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1763
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1774
	ldr	r3, [r0, #2832]
	ldrb	r2, [r3, #21]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1747
	cmn	r3, #256
	add	r2, r3, #256
	str	r2, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
.L1746:
	cmp	r1, #0
	bne	.L1764
.L1749:
	ldr	r10, .L1777
	mov	r2, #1536
	add	r0, r7, #620
	add	r9, r7, #2224
	mov	r6, r1
	add	r9, r9, #8
	ldr	r3, [r10, #48]
	blx	r3
	ldr	r8, [fp, #-48]
.L1750:
	ldr	r3, [r9, #4]!
	cmp	r3, #0
	movne	r5, r8
	movne	r4, #0
	beq	.L1753
.L1751:
	mov	r3, r4
	mov	r1, r5
	mov	r2, r6
	mov	r0, r7
	bl	HEVC_CalScalingList
	ldr	r3, [r9]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1751
.L1753:
	add	r6, r6, #1
	add	r8, r8, #384
	cmp	r6, #4
	bne	.L1750
	ldr	r2, [fp, #-48]
	add	r0, r7, #2240
	ldr	r3, [r10, #52]
	add	r0, r0, #12
	add	r1, r2, #1536
	mov	r2, #96
	blx	r3
.L1763:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1774:
	ldr	r2, [r0, #2832]
	ldrb	r3, [r2, #1889]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1775
	add	r0, r1, #12288
	ldrb	ip, [r0, #372]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L1776
	ldrb	r3, [r2, #21]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1754
.L1747:
	ldrb	r3, [r1, #4]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1764
.L1769:
	cmn	r1, #432
	add	r3, r1, #432
	str	r3, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	cmp	r1, #0
	beq	.L1749
.L1764:
	mov	r0, r7
	bl	HEVC_SetDefaultScalingList
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1743:
	ldrb	r3, [r2, #21]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1769
.L1754:
	cmn	r2, #256
	add	r3, r2, #256
	str	r3, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	b	.L1746
.L1776:
	ldrb	ip, [r1, #4]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1743
	ldrb	r1, [r2, #21]	@ zero_extendqisi2
	orrs	r3, r1, r3
	bne	.L1744
	ldr	r2, [r0, #376]
	movw	r1, #12668
	ldr	r3, [r7, #2804]
	add	r2, r7, r2, lsl #2
	ldr	r2, [r2, #228]
	mla	r3, r1, r2, r3
.L1772:
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1764
	cmn	r3, #432
	add	r2, r3, #432
	str	r2, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	b	.L1746
.L1775:
	ldr	r2, [r2, #1956]
	movw	r0, #5036
	ldr	r1, [r7, #2808]
	movw	lr, #12668
	ldr	r3, [r7, #2804]
	add	r2, r7, r2, lsl #2
	ldr	ip, [r2, #236]
	ldr	r2, [r2, #228]
	mla	r0, r0, ip, r1
	mla	r3, lr, r2, r3
	ldrb	r2, [r0, #21]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1772
	cmn	r0, #256
	add	r3, r0, #256
	str	r3, [fp, #-48]
	movne	r1, #0
	moveq	r1, #1
	b	.L1746
.L1744:
	cmp	r1, #0
	beq	.L1764
	b	.L1754
.L1778:
	.align	2
.L1777:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_SetScalingList, .-HEVC_SetScalingList
	.align	2
	.global	HEVC_GetScalingListDefaultAddress
	.type	HEVC_GetScalingListDefaultAddress, %function
HEVC_GetScalingListDefaultAddress:
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
	cmp	r0, #3
	ldrls	pc, [pc, r0, asl #2]
	b	.L1780
.L1782:
	.word	.L1786
	.word	.L1784
	.word	.L1784
	.word	.L1785
.L1784:
	ldr	r3, .L1790
	cmp	r1, #2
	add	r0, r3, #64
	movhi	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1786:
	ldr	r0, .L1790+4
	ldmfd	sp, {fp, sp, pc}
.L1785:
	ldr	r3, .L1790
	cmp	r1, #0
	add	r0, r3, #64
	movne	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1780:
	ldr	r1, .L1790+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1791:
	.align	2
.L1790:
	.word	.LANCHOR4+80
	.word	.LANCHOR4+64
	.word	.LC153
	UNWIND(.fnend)
	.size	HEVC_GetScalingListDefaultAddress, .-HEVC_GetScalingListDefaultAddress
	.align	2
	.global	HEVC_DecRefPicListsModification
	.type	HEVC_DecRefPicListsModification, %function
HEVC_DecRefPicListsModification:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r5, r3
	mov	r7, r1
	mov	r8, r2
	moveq	ip, #1
	movne	ip, #0
	cmp	r0, #0
	orreq	ip, ip, #1
	mov	r6, r0
	cmp	ip, #0
	bne	.L1802
	sub	ip, r3, #1
	mov	r4, #1
	movs	ip, ip, asr #1
	beq	.L1794
.L1795:
	movs	ip, ip, asr #1
	add	r4, r4, #1
	bne	.L1795
.L1794:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	cmp	r5, #1
	movls	r10, #0
	movhi	r10, #1
	uxtb	r0, r0
	strb	r0, [r8]
	cmp	r0, #0
	cmpne	r5, #1
	bls	.L1799
	ldr	r3, [r7, #76]
	cmp	r3, #0
	beq	.L1799
	mov	r9, r8
	mov	r5, #0
.L1800:
	mov	r1, r4
	ldr	r0, [r6, #2796]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7, #76]
	cmp	r3, r5
	bhi	.L1800
.L1799:
	ldr	r5, [r7, #20]
	cmp	r5, #0
	beq	.L1817
.L1798:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1817:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #1]
	cmp	r0, #0
	moveq	r10, #0
	andne	r10, r10, #1
	cmp	r10, #0
	beq	.L1798
	ldr	r3, [r7, #80]
	cmp	r3, #0
	beq	.L1798
	add	r8, r8, #128
.L1801:
	mov	r1, r4
	ldr	r0, [r6, #2796]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r8, #4]!
	ldr	r3, [r7, #80]
	cmp	r3, r5
	bhi	.L1801
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1802:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_DecRefPicListsModification, .-HEVC_DecRefPicListsModification
	.align	2
	.global	HEVC_MoreRbspData
	.type	HEVC_MoreRbspData, %function
HEVC_MoreRbspData:
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
	mov	r4, r0
	ldr	r0, [r0, #2796]
	bl	BsResidBits
	subs	r3, r0, #0
	ble	.L1820
	ldr	r2, [r4, #2816]
	ldr	r0, [r2, #12]
	add	r0, r0, #3
	cmp	r3, r0
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1820:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_MoreRbspData, .-HEVC_MoreRbspData
	.align	2
	.global	HEVC_More_Rbsp_Data
	.type	HEVC_More_Rbsp_Data, %function
HEVC_More_Rbsp_Data:
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
	ldr	r0, [r0, #2796]
	ldr	r2, [r0, #16]
	ldr	r3, [r0, #24]
	mov	r2, r2, asl #3
	cmp	r2, r3
	bls	.L1824
	mov	r1, #8
	bl	BsShow
	subs	r0, r0, #128
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1824:
	ldr	r1, .L1825
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1826:
	.align	2
.L1825:
	.word	.LC154
	UNWIND(.fnend)
	.size	HEVC_More_Rbsp_Data, .-HEVC_More_Rbsp_Data
	.align	2
	.global	HEVC_FindTrailZeros
	.type	HEVC_FindTrailZeros, %function
HEVC_FindTrailZeros:
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
	mov	r1, #0
	mov	r6, r0
.L1839:
	ldr	r3, [r6, #2816]
	ldr	ip, [r3, #8]
	sub	ip, ip, #1
	mov	r0, ip, asl #2
	mov	ip, ip, asl #5
	rsb	r2, r0, ip
	add	r2, r3, r2
	ldr	r3, [r2, #44]
	ldr	r2, [r2, #40]
	sub	r3, r3, #1
	add	r3, r2, r3
.L1828:
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r5, r0, ip
	cmp	r4, #0
	bne	.L1840
	ldr	r2, [r6, #2816]
	add	r1, r1, #1
	add	lr, r2, r5
	ldr	r2, [r2, #40]
	cmp	r2, r3
	beq	.L1841
	ldr	r2, [lr, #40]
	cmp	r2, r3
	sub	r3, r3, #1
	bne	.L1828
	ldr	r1, [lr, #64]
	ldr	r0, [r6, #276]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #2816]
	mov	r1, r4
	add	r5, r3, r5
	str	r4, [r5, #40]
	ldr	r2, [r6, #2816]
	ldr	r3, [r2, #8]
	sub	r3, r3, #1
	str	r3, [r2, #8]
	b	.L1839
.L1840:
	tst	r4, #1
	mov	r3, #1
	moveq	r2, r3
	bne	.L1835
.L1836:
	ands	r0, r4, r2, asl r3
	add	r3, r3, #1
	bne	.L1835
	cmp	r3, #8
	bne	.L1836
	ldr	r1, .L1842
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1841:
	ldr	r1, .L1842+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1835:
	ldr	ip, [r6, #2816]
	mov	r2, #0
	add	r1, r3, r1, lsl #3
	mov	r0, r2
	str	r2, [ip, #4]
	ldr	r3, [r6, #2816]
	str	r1, [r3, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1843:
	.align	2
.L1842:
	.word	.LC156
	.word	.LC155
	UNWIND(.fnend)
	.size	HEVC_FindTrailZeros, .-HEVC_FindTrailZeros
	.align	2
	.global	HEVC_FindNaluArraySlot
	.type	HEVC_FindNaluArraySlot, %function
HEVC_FindNaluArraySlot:
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
	ldr	r5, [r0, #168]
	mov	r8, r0
	ldr	r3, [r0, #148]
	cmp	r5, #0
	blt	.L1845
	add	r6, r5, #1
	mov	r0, r3
	mov	r1, r6
	bl	__aeabi_uidivmod
	ldr	r7, [r8, #2840]
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1846
	mov	r4, #0
	b	.L1848
.L1849:
	bl	__aeabi_uidivmod
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1846
.L1848:
	add	r4, r4, #1
	mov	r1, r6
	cmp	r4, r5
	add	r0, r3, r4
	ble	.L1849
.L1845:
	mvn	r0, #0
	str	r3, [r8, #148]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1846:
	cmp	r3, r6
	mov	r0, r3
	str	r3, [r8, #148]
	bcs	.L1859
	rsb	r1, r1, ip
	mov	r3, #1
	add	r7, r7, r1
	str	r3, [r7, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1859:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FindNaluArraySlot, .-HEVC_FindNaluArraySlot
	.align	2
	.global	HEVC_ReleaseNAL
	.type	HEVC_ReleaseNAL, %function
HEVC_ReleaseNAL:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L1868
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	str	r3, [r5, #32]
	str	r3, [r5, #36]
.L1863:
	ldr	r3, [r4, #40]
	mov	r0, r6
	cmp	r3, #0
	beq	.L1862
	ldr	r1, [r4, #64]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #44]
	ldr	r3, [r4, #40]
	mov	r0, #7
	ldr	r2, .L1869
	ldr	r1, .L1869+4
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #40]
	str	r3, [r4, #56]
	str	r3, [r4, #44]
.L1862:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L1863
	ldr	r3, .L1869+8
	mov	r0, r5
	mov	r2, #96
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1868:
	mov	r0, r5
	movw	r3, #14174
	ldr	r2, .L1869+12
	ldr	r1, .L1869+16
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1870:
	.align	2
.L1869:
	.word	.LANCHOR0+560
	.word	.LC157
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC2
	.word	.LC3
	UNWIND(.fnend)
	.size	HEVC_ReleaseNAL, .-HEVC_ReleaseNAL
	.align	2
	.global	HEVC_InitDecBuffers
	.type	HEVC_InitDecBuffers, %function
HEVC_InitDecBuffers:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r6, r0
	cmp	r3, #1
	beq	.L1907
.L1872:
	ldr	r3, [r6, #2828]
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r6, #3024]
.L1874:
	cmp	r3, #17
	bhi	.L1908
.L1875:
	add	lr, r6, #3392
	add	ip, r6, #3248
	add	r0, r6, #3184
	add	r1, r6, #3120
	mov	r7, #0
	add	lr, lr, #4
	add	ip, ip, #12
	add	r0, r0, #8
	add	r1, r1, #4
	add	r5, r6, #3328
	add	r4, r6, #3056
	mov	r2, r7
	mov	r3, r7
	str	r7, [r6, #3028]
	str	r7, [r6, #3040]
	str	r7, [r6, #3044]
	str	r7, [r6, #3036]
	str	r7, [r6, #3032]
	str	r7, [r6, #3052]
	str	r7, [r6, #3056]
.L1876:
	add	r2, r2, #1
	str	r3, [lr, #4]!
	cmp	r2, #17
	str	r3, [ip, #4]!
	str	r3, [r5, #4]!
	str	r3, [r0, #4]!
	str	r3, [r4, #4]!
	str	r3, [r1, #4]!
	bne	.L1876
	add	r4, r6, #13760
	ldr	r9, .L1909
	add	r4, r4, #32
	mov	r7, #0
.L1877:
	ldr	r3, [r9, #48]
	mov	r2, #632
	mov	r0, r4
	mov	r1, #0
	blx	r3
	str	r7, [r4, #148]
	add	r7, r7, #1
	mov	r5, #0
	cmp	r7, #20
	sub	r3, r4, #80
	strb	r5, [r4, #-80]
	mov	r2, #20
	str	r5, [r4, #-32]
	mov	r8, #16
	strb	r5, [r4, #-79]
	add	r4, r4, #712
	str	r5, [r4, #-784]
	strb	r5, [r4, #-790]
	str	r5, [r4, #-736]
	str	r2, [r4, #-772]
	str	r8, [r4, #-768]
	str	r3, [r4, #-716]
	ldr	r10, .L1909
	bne	.L1877
	add	r0, r6, #13120
	add	r4, r6, #12288
	ldr	r3, [r10, #48]
	mov	r2, #280
	mov	r1, r5
	add	r0, r0, #28
	blx	r3
	add	r0, r6, #13376
	ldr	r3, [r10, #48]
	mov	r2, #280
	mov	r1, r5
	add	r0, r0, #52
	str	r8, [r4, #860]
	str	r5, [r4, #864]
	blx	r3
	add	r2, r6, #2848
	add	r3, r6, #2912
	add	r2, r2, #4
	add	r3, r3, #8
	mov	r1, r5
	str	r8, [r4, #1140]
	str	r5, [r4, #1144]
.L1878:
	str	r1, [r2, #4]!
	cmp	r2, r3
	mov	r0, #0
	bne	.L1878
	add	r1, r6, #2976
	add	lr, r6, #4096
	add	r1, r1, #12
	mov	ip, r0
	str	r0, [lr, #764]
.L1879:
	str	ip, [r3, #4]!
	cmp	r3, r1
	mov	r2, #0
	bne	.L1879
	str	r2, [lr, #768]
	ldr	r0, [r6, #184]
	cmp	r0, r2
	addne	r1, r6, #2144
	movne	r3, r2
	addne	r1, r1, #8
	movne	r2, r3
	beq	.L1884
.L1883:
	add	r3, r3, #1
	str	r2, [r1, #4]!
	cmp	r3, r0
	bne	.L1883
.L1884:
	ldr	r3, [r6, #168]
	cmp	r3, #0
	movne	r4, #0
	movne	r5, r4
	beq	.L1871
.L1889:
	ldr	r3, [r6, #2836]
	mov	r7, r4, asl #2
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L1885
	ldr	r3, [r6, #2816]
	cmp	r1, r3
	beq	.L1885
	ldr	r0, [r6, #276]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r6, #2836]
	str	r5, [r3, r7]
	ldr	r3, [r6, #204]
	ldr	r2, [r6, #260]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #204]
	ldr	r3, [r6, #176]
	cmp	r2, #0
	subne	r2, r2, #1
	str	r2, [r6, #260]
	cmp	r3, #2
	subhi	r3, r3, #1
	movls	r3, #2
	str	r3, [r6, #176]
.L1885:
	ldr	r3, [r6, #168]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L1889
.L1871:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1908:
	mov	r4, #17
	ldr	r2, .L1909+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L1909+8
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r6, #3024]
	b	.L1875
.L1907:
	ldr	r3, [r0, #2844]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L1872
	ldr	r2, [r0, #2380]
	cmp	r2, #0
	beq	.L1872
	ldr	r3, [r6, #2828]
	ldr	r3, [r3, #184]
	mul	r3, r3, r2
	add	r3, r3, #1
	str	r3, [r6, #3024]
	b	.L1874
.L1910:
	.align	2
.L1909:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+576
	.word	.LC158
	UNWIND(.fnend)
	.size	HEVC_InitDecBuffers, .-HEVC_InitDecBuffers
	.align	2
	.global	HEVC_EmptyFrmFromDPB
	.type	HEVC_EmptyFrmFromDPB, %function
HEVC_EmptyFrmFromDPB:
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
	subs	r6, r0, #0
	beq	.L1922
	ldr	r3, [r6, #3028]
	add	r8, r6, #3184
	cmp	r3, #0
	addne	r8, r8, #8
	movne	r3, #0
	movne	ip, #1
	movne	r1, r8
	beq	.L1937
.L1916:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	streqb	ip, [r2, #2]
	ldr	r2, [r6, #3028]
	cmp	r2, r3
	bhi	.L1916
.L1917:
	mov	r4, r6
	mov	r7, #17
	mov	r5, #0
	mov	r3, #-2147483647
	str	r3, [r6, #212]
	str	r3, [r6, #216]
.L1914:
	ldr	r3, [r8, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L1918
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1918:
	ldr	r3, [r4, #3264]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1919
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1919:
	ldr	r3, [r4, #3332]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1920
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1920:
	ldr	r3, [r4, #3400]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1921
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #276]
	bl	FSP_ClearLogicFs
.L1921:
	subs	r7, r7, #1
	str	r5, [r4, #3400]
	str	r5, [r4, #3332]
	add	r4, r4, #4
	str	r5, [r4, #3260]
	str	r5, [r4, #3192]
	bne	.L1914
	mov	r0, r6
	bl	HEVC_InitDecBuffers
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1937:
	add	r8, r8, #8
	b	.L1917
.L1922:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_EmptyFrmFromDPB, .-HEVC_EmptyFrmFromDPB
	.align	2
	.global	HEVC_CombinePacket
	.type	HEVC_CombinePacket, %function
HEVC_CombinePacket:
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
	mov	r4, r0
	ldr	r0, [r0, #2816]
	cmp	r0, #0
	beq	.L1941
	ldr	r3, [r0, #44]
	cmp	r3, #4096
	ldmcsfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1942
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r3, [r4, #2816]
	ldr	ip, .L1942+4
	mov	r5, #0
	ldr	r2, [r3, #44]
	ldr	r0, [r3, #68]
	ldr	r1, [r3, #40]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #2816]
	mov	r0, #1
	ldr	r2, [r3, #92]
	ldr	r1, [r3, #64]
	str	r2, [r3, #64]
	ldr	r3, [r4, #2816]
	str	r5, [r3, #56]
	ldr	r3, [r4, #2816]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #68]
	rsb	r2, ip, r2
	str	r2, [r3, #40]
	ldr	r3, [r4, #2816]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #76]
	rsb	r2, ip, r2
	str	r2, [r3, #48]
	ldr	r3, [r4, #2816]
	ldr	r2, [r3, #44]
	ldr	ip, [r3, #72]
	add	r2, r2, ip
	str	r2, [r3, #44]
	ldr	r3, [r4, #2816]
	str	r0, [r3, #8]
	ldr	r0, [r4, #276]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #2816]
	str	r5, [r3, #68]
	ldr	r3, [r4, #2816]
	str	r5, [r3, #84]
	ldr	r3, [r4, #2816]
	str	r5, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1941:
	ldr	r1, .L1942+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1943:
	.align	2
.L1942:
	.word	.LC160
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC159
	UNWIND(.fnend)
	.size	HEVC_CombinePacket, .-HEVC_CombinePacket
	.align	2
	.global	HEVC_IsOutDPB
	.type	HEVC_IsOutDPB, %function
HEVC_IsOutDPB:
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
	cmp	r1, #0
	beq	.L1949
	ldr	ip, [r0, #3028]
	cmp	ip, #0
	beq	.L1949
	ldr	r3, [r0, #3196]
	cmp	r3, r1
	beq	.L1951
	add	r0, r0, #3184
	mov	r3, #0
	add	r0, r0, #12
	b	.L1946
.L1947:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1951
.L1946:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1947
.L1949:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1951:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsOutDPB, .-HEVC_IsOutDPB
	.align	2
	.global	HEVC_IsNewPicNal
	.type	HEVC_IsNewPicNal, %function
HEVC_IsNewPicNal:
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
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsNewPicNal, .-HEVC_IsNewPicNal
	.align	2
	.global	HEVC_u_v
	.type	HEVC_u_v, %function
HEVC_u_v:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	HEVC_u_v, .-HEVC_u_v
	.align	2
	.global	HEVC_f_v
	.type	HEVC_f_v, %function
HEVC_f_v:
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
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsGet
	UNWIND(.fnend)
	.size	HEVC_f_v, .-HEVC_f_v
	.align	2
	.global	HEVC_ue_v
	.type	HEVC_ue_v, %function
HEVC_ue_v:
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
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L1958
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1958:
	add	r4, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r4
	mov	r0, r5
	bl	BsShow
	mov	r1, r4
	sub	r4, r0, #1
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ue_v, .-HEVC_ue_v
	.align	2
	.global	HEVC_Sei_Tone_Mapping_Info
	.type	HEVC_Sei_Tone_Mapping_Info, %function
HEVC_Sei_Tone_Mapping_Info:
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
	ldr	r1, .L1981
	mov	r4, r0
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2796]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	beq	.L1978
.L1964:
	mov	r1, #32
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r0, [r4, #2796]
	mov	r1, #32
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1978:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	mov	r6, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #8
	mov	r7, r0
	bhi	.L1979
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #4
	ldrls	pc, [pc, r0, asl #2]
	b	.L1975
.L1963:
	.word	.L1964
	.word	.L1964
	.word	.L1965
	.word	.L1966
	.word	.L1967
.L1966:
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #256
	mov	r8, r0
	bhi	.L1971
	cmp	r0, #0
	beq	.L1975
	add	r6, r6, #7
	add	r7, r7, #7
	bic	r6, r6, #7
	bic	r7, r7, #7
	mov	r5, #0
.L1973:
	mov	r1, r6
	ldr	r0, [r4, #2796]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, r7
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r5, r8
	bne	.L1973
.L1975:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1965:
	mov	r2, #1
	movs	r7, r2, asl r7
	addne	r6, r6, #7
	movne	r5, #0
	bicne	r6, r6, #7
	beq	.L1975
.L1969:
	add	r5, r5, #1
	mov	r1, r6
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r7, r5
	bne	.L1969
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1967:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #255
	beq	.L1980
.L1974:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r0, [r4, #2796]
	mov	r1, #16
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1980:
	mov	r1, #32
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L1974
.L1979:
	mov	r2, r0
	ldr	r1, .L1981+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1971:
	ldr	r1, .L1981+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1982:
	.align	2
.L1981:
	.word	.LC161
	.word	.LC162
	.word	.LC163
	UNWIND(.fnend)
	.size	HEVC_Sei_Tone_Mapping_Info, .-HEVC_Sei_Tone_Mapping_Info
	.align	2
	.global	HEVC_Sei_Frame_Packing_Arrangement
	.type	HEVC_Sei_Frame_Packing_Arrangement, %function
HEVC_Sei_Frame_Packing_Arrangement:
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
	ldr	r1, .L1993
	mov	r4, r0
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2796]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	bne	.L1984
	mov	r1, #7
	ldr	r0, [r4, #2796]
	bl	BsGet
	sub	r3, r0, #3
	mov	r6, r0
	cmp	r3, #2
	bhi	.L1991
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #6
	mov	r5, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	uxtb	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	clz	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	mov	r5, r5, lsr #5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r6, #5
	moveq	r5, #0
	cmp	r5, #0
	bne	.L1992
.L1987:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
.L1984:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r0, [r4, #2796]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1992:
	mov	r1, #4
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L1987
.L1991:
	mov	r2, r0
	ldr	r1, .L1993+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1994:
	.align	2
.L1993:
	.word	.LC164
	.word	.LC165
	UNWIND(.fnend)
	.size	HEVC_Sei_Frame_Packing_Arrangement, .-HEVC_Sei_Frame_Packing_Arrangement
	.align	2
	.global	HEVC_Sei_Dec_Unit_Info
	.type	HEVC_Sei_Dec_Unit_Info, %function
HEVC_Sei_Dec_Unit_Info:
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
	cmp	r2, #0
	cmpne	r1, #0
	mov	r5, r2
	mov	r4, r0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #0
	orreq	r1, r1, #1
	cmp	r1, #0
	bne	.L1999
	ldr	r1, .L2008
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2006
.L1997:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2007
.L1998:
	ldr	r0, [r4, #2796]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2006:
	ldr	r1, [r5, #4]
	ldr	r0, [r4, #2796]
	add	r1, r1, #1
	bl	BsGet
	b	.L1997
.L2007:
	ldr	r1, [r5, #8]
	ldr	r0, [r4, #2796]
	add	r1, r1, #1
	bl	BsGet
	b	.L1998
.L1999:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2009:
	.align	2
.L2008:
	.word	.LC166
	UNWIND(.fnend)
	.size	HEVC_Sei_Dec_Unit_Info, .-HEVC_Sei_Dec_Unit_Info
	.align	2
	.global	HEVC_Sei_Active_Param_sets
	.type	HEVC_Sei_Active_Param_sets, %function
HEVC_Sei_Active_Param_sets:
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
	mov	r1, #4
	mov	r5, r0
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldr	r0, [r5, #2796]
	ldr	r1, .L2017
	bl	HEVC_ue_v
	cmp	r0, #15
	bgt	.L2011
	cmp	r0, #0
	addge	r6, r0, #1
	movge	r4, #0
	blt	.L2015
.L2014:
	add	r4, r4, #1
	ldr	r1, .L2017+4
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r4, r6
	bne	.L2014
.L2015:
	ldr	r0, [r5, #2796]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2011:
	ldr	r1, .L2017+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2018:
	.align	2
.L2017:
	.word	.LC167
	.word	.LC169
	.word	.LC168
	UNWIND(.fnend)
	.size	HEVC_Sei_Active_Param_sets, .-HEVC_Sei_Active_Param_sets
	.align	2
	.global	HEVC_Sei_Buf_Period
	.type	HEVC_Sei_Buf_Period, %function
HEVC_Sei_Buf_Period:
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
	add	r4, r0, #8192
	mov	r5, r0
	mov	r9, r1
	mov	r6, #0
	ldr	r1, .L2048
	mov	r7, r2
	str	r6, [r4, #3528]
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	cmp	r0, #15
	bhi	.L2044
	mov	r1, #1
	strb	r1, [r4, #3521]
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r8, r6
	beq	.L2045
.L2022:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r4, #1
	strb	r0, [r9]
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2796]
	add	r1, r1, r4
	bl	BsGet
	subs	r3, r4, #1
	beq	.L2046
.L2024:
	cmp	r3, #1
	beq	.L2047
.L2028:
	cmp	r4, #1
	bhi	.L2027
.L2026:
	add	r4, r4, #1
	subs	r3, r4, #1
	bne	.L2024
.L2046:
	ldrb	r2, [r7]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2028
	ldr	r2, [r7, #24]
	cmn	r2, #1
	beq	.L2026
.L2035:
	mov	r6, #0
	b	.L2031
.L2030:
	ldr	r3, [r7, #24]
	add	r3, r3, #1
	cmp	r3, r6
	bls	.L2028
.L2031:
	ldr	r1, [r7, #12]
	add	r6, r6, #1
	ldr	r0, [r5, #2796]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2796]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	orrs	r3, r8, r3
	beq	.L2030
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2796]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2796]
	add	r1, r1, #1
	bl	BsGet
	b	.L2030
.L2047:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2027
	ldr	r3, [r7, #24]
	cmn	r3, #1
	bne	.L2035
.L2027:
	ldr	r0, [r5, #2796]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2045:
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	beq	.L2022
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2796]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #20]
	ldr	r0, [r5, #2796]
	add	r1, r1, #1
	bl	BsGet
	b	.L2022
.L2044:
	mov	r2, r0
	ldr	r1, .L2048+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2049:
	.align	2
.L2048:
	.word	.LC170
	.word	.LC171
	UNWIND(.fnend)
	.size	HEVC_Sei_Buf_Period, .-HEVC_Sei_Buf_Period
	.align	2
	.global	HEVC_Sei_Pic_Timming
	.type	HEVC_Sei_Pic_Timming, %function
HEVC_Sei_Pic_Timming:
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
	add	r3, r0, #8192
	mov	r5, r2
	mov	r4, r0
	mov	r6, r1
	ldr	r0, [r3, #3524]
	ldr	r2, [r3, #3528]
	add	r0, r0, #1
	str	r0, [r3, #3524]
	add	r2, r2, #1
	str	r2, [r3, #3528]
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2078
.L2051:
	ldrh	r3, [r5, #44]
	cmp	r3, #0
	beq	.L2053
	ldr	r1, [r5, #60]
	ldr	r0, [r4, #2796]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r6, #8]
	ldr	r1, [r5, #64]
	ldr	r0, [r4, #2796]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #12]
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2054
.L2057:
	ldr	r2, [r4, #276]
	ldr	r3, .L2081
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L2079
.L2053:
	ldr	r0, [r4, #2796]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2078:
	mov	r1, #4
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #2
	str	r0, [r6]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #4]
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L2051
.L2079:
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L2053
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L2053
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L2053
.L2054:
	ldr	r1, [r5, #52]
	ldr	r0, [r4, #2796]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2057
	ldrb	r3, [r5, #47]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2057
	ldr	r1, .L2081+4
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	mov	r1, #1
	mov	r8, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r9, r0
	cmp	r9, #0
	bne	.L2080
.L2058:
	cmp	r8, #255
	bhi	.L2062
	add	r8, r8, #1
	mov	r7, #0
	b	.L2061
.L2060:
	cmp	r7, r8
	beq	.L2057
.L2061:
	ldr	r1, .L2081+8
	add	r7, r7, #1
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r9, #0
	bne	.L2060
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2796]
	add	r1, r1, #1
	bl	BsGet
	b	.L2060
.L2080:
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2796]
	add	r1, r1, #1
	bl	BsGet
	b	.L2058
.L2062:
	ldr	r1, .L2081+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2082:
	.align	2
.L2081:
	.word	s_pstVfmwChan
	.word	.LC172
	.word	.LC174
	.word	.LC173
	UNWIND(.fnend)
	.size	HEVC_Sei_Pic_Timming, .-HEVC_Sei_Pic_Timming
	.align	2
	.global	HEVC_Sei_Color_Volume_Reconstruction_Info
	.type	HEVC_Sei_Color_Volume_Reconstruction_Info, %function
HEVC_Sei_Color_Volume_Reconstruction_Info:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r5, r1
	beq	.L2093
	ldr	r1, .L2097
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2085
.L2089:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2085:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L2096
.L2086:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #4]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #5]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #6]
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #7]
	addne	r7, r5, #7
	movne	r6, #0
	beq	.L2091
.L2090:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L2090
.L2091:
	mov	r1, #4
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #38]
	addne	r7, r5, #38
	movne	r6, #0
	beq	.L2089
.L2092:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #38]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L2092
	b	.L2089
.L2093:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2096:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #1]
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L2086
.L2098:
	.align	2
.L2097:
	.word	.LC175
	UNWIND(.fnend)
	.size	HEVC_Sei_Color_Volume_Reconstruction_Info, .-HEVC_Sei_Color_Volume_Reconstruction_Info
	.align	2
	.global	HEVC_Sei_User_Data_Registered_Itu_T_T35
	.type	HEVC_Sei_User_Data_Registered_Itu_T_T35, %function
HEVC_Sei_User_Data_Registered_Itu_T_T35:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r6, r2
	mov	r5, r0
	moveq	r4, #1
	movne	r4, #0
	beq	.L2106
	cmp	r2, #3
	bls	.L2109
	mov	r1, #8
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #2
	beq	.L2110
	cmp	r0, #4
	beq	.L2111
	subs	r6, r6, #4
	beq	.L2105
.L2104:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r6, r4
	bne	.L2104
.L2105:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2110:
	add	r1, r5, #3520
	mov	r0, r5
	add	r1, r1, #8
	bl	HEVC_Sei_TSI
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2111:
	add	r1, r5, #3520
	mov	r0, r5
	add	r1, r1, #11
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2106:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2109:
	ldr	r1, .L2112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2113:
	.align	2
.L2112:
	.word	.LC176
	UNWIND(.fnend)
	.size	HEVC_Sei_User_Data_Registered_Itu_T_T35, .-HEVC_Sei_User_Data_Registered_Itu_T_T35
	.align	2
	.global	HEVC_DecShortTermRefPicSet
	.type	HEVC_DecShortTermRefPicSet, %function
HEVC_DecShortTermRefPicSet:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	subs	r6, r3, #0
	mov	r5, r0
	mov	r9, r1
	mov	r4, r2
	bne	.L2159
.L2115:
	ldr	r1, .L2168
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4]
	bhi	.L2160
	ldr	r1, .L2168+4
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4, #4]
	bhi	.L2161
	ldr	r6, [r4]
	add	r2, r0, r6
	str	r2, [r4, #8]
	cmp	r2, #16
	bhi	.L2138
	cmp	r6, #0
	addne	r10, r4, #28
	addne	r9, r4, #11
	movne	r7, #0
	movne	r8, r7
	bne	.L2142
	b	.L2140
.L2141:
	str	r8, [r10, #4]!
	ldr	r0, [r5, #2796]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r6, [r4]
	cmp	r6, r7
	bls	.L2162
.L2142:
	ldr	r1, .L2168+8
	add	r7, r7, #1
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	mov	r1, #1
	cmp	r0, #32768
	mvn	r3, r0
	add	r8, r8, r3
	bcc	.L2141
	mov	r2, r0
	ldr	r1, .L2168+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2159:
	mov	r1, #1
	ldr	r0, [r0, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L2115
	ldr	r7, [r9, #176]
	cmp	r7, r6
	movne	r0, #0
	beq	.L2163
.L2116:
	sub	r3, r6, #1
	rsb	r8, r0, r3
	cmp	r8, r3
	bhi	.L2164
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldr	r1, .L2168+16
	mov	r6, r0
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	mov	r3, #164
	mul	r8, r3, r8
	mov	r3, r6, asl #1
	rsb	r3, r3, #1
	add	r2, r9, r8
	ldr	r2, [r2, #2172]
	cmp	r2, #16
	mla	r3, r0, r3, r3
	str	r3, [fp, #-56]
	bhi	.L2165
	add	r6, r8, #2192
	mov	r10, #0
	add	r6, r6, #4
	str	r10, [fp, #-48]
	add	r6, r9, r6
	str	r10, [fp, #-52]
	mov	r7, r10
	b	.L2125
.L2120:
	sub	r3, r0, #1
	cmp	r3, #1
	bls	.L2166
.L2121:
	add	r3, r9, r8
	add	r10, r10, #1
	add	r6, r6, #4
	ldr	r3, [r3, #2172]
	cmp	r3, r10
	bcc	.L2167
.L2125:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #0
	bne	.L2120
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r0, r0, asl #1
	sub	r3, r0, #1
	cmp	r3, #1
	bhi	.L2121
.L2166:
	add	r3, r9, r8
	ldr	r2, [fp, #-56]
	add	r1, r4, r7
	add	ip, r7, #8
	ldr	r3, [r3, #2172]
	sub	r0, r0, #1
	clz	r0, r0
	add	r7, r7, #1
	cmp	r3, r10
	mov	r0, r0, lsr #5
	ldrhi	r3, [r6]
	movls	r3, #0
	add	r3, r3, r2
	str	r3, [r4, ip, asl #2]
	cmp	r3, #0
	mov	r3, r1
	strb	r0, [r1, #12]
	ldrlt	r3, [fp, #-52]
	ldrge	r3, [fp, #-48]
	addlt	r3, r3, #1
	addge	r3, r3, #1
	strlt	r3, [fp, #-52]
	strge	r3, [fp, #-48]
	b	.L2121
.L2167:
	ldr	r3, [fp, #-52]
	cmp	r7, #16
	ldr	r2, [fp, #-48]
	str	r7, [r4, #8]
	str	r3, [r4]
	str	r2, [r4, #4]
	bhi	.L2126
	cmp	r3, #16
	bhi	.L2126
	cmp	r2, #16
	bhi	.L2126
	cmp	r7, #1
	subhi	r7, r7, #1
	addhi	r8, r4, #32
	addhi	r6, r4, #12
	movhi	r5, #0
	bls	.L2132
.L2131:
	ldr	ip, [r8, #4]!
	cmp	r5, #0
	ldrb	lr, [r6, #1]!	@ zero_extendqisi2
	mov	r2, r5
	movge	r1, r8
	movge	r3, r6
	blt	.L2134
.L2130:
	ldr	r0, [r1, #-4]!
	sub	r3, r3, #1
	cmp	ip, r0
	strlt	r0, [r1, #4]
	ldrltb	r0, [r3]	@ zero_extendqisi2
	strltb	r0, [r3, #1]
	strlt	ip, [r1]
	strltb	lr, [r3]
	subs	r2, r2, #1
	bpl	.L2130
.L2134:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L2131
.L2132:
	ldr	r3, [fp, #-52]
	movs	r6, r3, lsr #1
	beq	.L2129
	ldr	r3, [fp, #-52]
	add	r0, r4, #32
	mov	r1, #0
	add	r2, r3, #7
	add	r3, r3, #11
	add	r3, r4, r3
	add	r2, r4, r2, lsl #2
	add	r4, r4, #12
.L2135:
	ldr	r5, [r2]
	add	r1, r1, #1
	ldr	lr, [r0]
	cmp	r1, r6
	ldrb	ip, [r4]	@ zero_extendqisi2
	str	r5, [r0], #4
	ldrb	r5, [r3]	@ zero_extendqisi2
	strb	r5, [r4], #1
	str	lr, [r2], #-4
	strb	ip, [r3], #-1
	bne	.L2135
.L2129:
	mov	r0, #0
.L2117:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2162:
	ldr	r2, [r4, #8]
.L2140:
	cmp	r2, r6
	bls	.L2129
	add	r8, r6, #7
	add	r9, r6, #11
	add	r9, r4, r9
	mov	r7, #0
	add	r8, r4, r8, lsl #2
.L2143:
	ldr	r1, .L2168+20
	add	r6, r6, #1
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	mov	r1, #1
	add	r0, r0, r1
	add	r7, r7, r0
	str	r7, [r8, #4]!
	ldr	r0, [r5, #2796]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r3, [r4, #8]
	cmp	r3, r6
	bhi	.L2143
	b	.L2129
.L2163:
	ldr	r1, .L2168+24
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	add	r2, r0, #1
	cmp	r7, r2
	bcs	.L2116
	mov	r3, r7
	ldr	r1, .L2168+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2117
.L2126:
	ldr	r1, .L2168+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2117
.L2161:
	ldr	r2, [r4]
	mov	r0, #1
	ldr	r1, .L2168+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2117
.L2164:
	mov	r2, r8
	ldr	r1, .L2168+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2117
.L2165:
	ldr	r1, .L2168+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2117
.L2160:
	mov	r2, r0
	ldr	r1, .L2168+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2117
.L2138:
	mov	r3, #16
	ldr	r1, .L2168+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2117
.L2169:
	.align	2
.L2168:
	.word	.LC183
	.word	.LC185
	.word	.LC188
	.word	.LC189
	.word	.LC180
	.word	.LC190
	.word	.LC177
	.word	.LC178
	.word	.LC182
	.word	.LC186
	.word	.LC179
	.word	.LC181
	.word	.LC184
	.word	.LC187
	UNWIND(.fnend)
	.size	HEVC_DecShortTermRefPicSet, .-HEVC_DecShortTermRefPicSet
	.align	2
	.global	HEVC_DecHrdParam
	.type	HEVC_DecHrdParam, %function
HEVC_DecHrdParam:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r8, r3
	mov	r6, r0
	mov	r9, r1
	beq	.L2192
	cmp	r2, #0
	bne	.L2219
.L2175:
	add	r5, r9, #24
	mov	r7, #0
.L2187:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	uxtb	r4, r0
	cmp	r4, #0
	movne	r3, #0
	strne	r3, [r5]
	beq	.L2220
.L2190:
	ldr	r1, .L2225
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
.L2178:
	ldr	r1, .L2225+4
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	mov	r2, r0
	str	r0, [r5]
.L2179:
	cmp	r2, #31
	bhi	.L2221
.L2180:
	mov	r4, #0
.L2191:
	cmp	r4, #0
	beq	.L2222
	cmp	r4, #1
	beq	.L2217
.L2186:
	add	r4, r4, #1
	cmp	r4, #2
	bne	.L2191
.L2185:
	add	r7, r7, #1
	add	r5, r5, #4
	cmp	r8, r7
	bcs	.L2187
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2221:
	ldr	r1, .L2225+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5]
	b	.L2180
.L2220:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	str	r4, [r5]
	tst	r0, #255
	bne	.L2190
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2178
	ldr	r2, [r5]
	b	.L2179
.L2219:
	mov	r1, #1
	ldr	r0, [r0, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r6, #2796]
	bl	BsGet
	strb	r0, [r9, #1]
	ldrh	r3, [r9]
	cmp	r3, #0
	beq	.L2175
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r9, #2]
	cmp	r0, #0
	bne	.L2223
.L2173:
	mov	r1, #4
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2224
.L2174:
	mov	r1, #5
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #12]
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #16]
	ldr	r0, [r6, #2796]
	bl	BsGet
	str	r0, [r9, #20]
	b	.L2175
.L2192:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2224:
	mov	r1, #4
	ldr	r0, [r6, #2796]
	bl	BsGet
	b	.L2174
.L2223:
	mov	r1, #8
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r1, #1
	str	r0, [r9, #4]
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r9, #3]
	ldr	r0, [r6, #2796]
	bl	BsGet
	str	r0, [r9, #20]
	b	.L2173
.L2222:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2194
	mov	r4, #1
.L2217:
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2185
.L2194:
	mov	r10, #0
	b	.L2189
.L2188:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [r5]
	cmp	r3, r10
	bcc	.L2186
.L2189:
	ldr	r1, .L2225+12
	add	r10, r10, #1
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2225+16
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2188
	ldr	r1, .L2225+20
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2225+24
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	b	.L2188
.L2226:
	.align	2
.L2225:
	.word	.LC191
	.word	.LC192
	.word	.LC193
	.word	.LC194
	.word	.LC195
	.word	.LC196
	.word	.LC197
	UNWIND(.fnend)
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	2
	.type	HEVC_ParseVPSExtension, %function
HEVC_ParseVPSExtension:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 672
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #692)
	sub	sp, sp, #692
	mov	r4, #0
	mov	r5, r1
	str	r0, [fp, #-652]
	str	r1, [fp, #-648]
	mov	r2, #64
	mov	r1, r4
	sub	r0, fp, #496
	str	r4, [fp, #-640]
	sub	r7, fp, #304
	str	r4, [fp, #-636]
	bl	memset
	mov	r1, r4
	mov	r2, #128
	sub	r0, fp, #172
	bl	memset
	add	r3, r5, #16384
	mov	r1, r4
	mov	r2, #64
	sub	r0, fp, #432
	mov	r6, r3
	str	r3, [fp, #-660]
	str	r4, [fp, #-632]
	str	r4, [fp, #-628]
	str	r4, [fp, #-624]
	str	r4, [fp, #-620]
	str	r4, [fp, #-608]
	str	r4, [fp, #-604]
	str	r4, [fp, #-600]
	str	r4, [fp, #-596]
	bl	memset
	mov	r1, r4
	mov	r2, #64
	sub	r0, fp, #368
	bl	memset
	mov	r1, r4
	mov	r2, #64
	mov	r0, r7
	bl	memset
	ldr	r3, .L2747
	add	r0, r5, #12416
	mov	r1, r4
	add	r0, r0, #4
	movw	r2, #12492
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r5, #8]
	cmp	r3, #62
	movge	r3, #62
	cmp	r3, #1
	str	r3, [r6, #152]
	bgt	.L2715
	cmp	r3, #0
	ble	.L2230
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2716
.L2230:
	ldr	r8, [fp, #-652]
	mov	r1, #1
	sub	r6, fp, #500
	sub	r4, fp, #436
	mov	r5, #0
	ldr	r0, [r8, #2796]
	bl	BsGet
	uxtb	r3, r0
	str	r3, [fp, #-672]
.L2231:
	mov	r1, #1
	ldr	r0, [r8, #2796]
	bl	BsGet
	str	r0, [r6, #4]!
	cmp	r0, #0
	addne	r5, r5, #1
	cmp	r6, r4
	bne	.L2231
	ldr	r3, [fp, #-672]
	adds	r6, r3, #0
	movne	r6, #1
	rsb	r10, r6, r5
	cmp	r10, #0
	movgt	r9, r7
	movgt	r8, #0
	ble	.L2236
.L2235:
	ldr	r3, [fp, #-652]
	mov	r1, #3
	add	r8, r8, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r8, r10
	add	r0, r0, #1
	str	r0, [r9], #4
	bne	.L2235
.L2236:
	cmp	r5, #0
	addge	r8, r5, #1
	subge	lr, fp, #432
	movge	ip, #0
	movge	r9, #6
	blt	.L2234
.L2244:
	cmp	r5, ip
	movne	r2, #0
	andeq	r2, r6, #1
	cmp	r2, #0
	strne	r9, [lr]
	bne	.L2241
	cmp	ip, #0
	ldrgt	r1, [lr]
	movgt	r0, r7
	ble	.L2241
.L2242:
	add	r2, r2, #1
	ldr	r3, [r0], #4
	cmp	r2, ip
	add	r3, r3, #1
	add	r1, r1, r3
	bne	.L2242
	str	r1, [lr]
.L2241:
	add	ip, ip, #1
	add	lr, lr, #4
	cmp	ip, r8
	bne	.L2244
.L2234:
	cmp	r6, #0
	beq	.L2238
	sub	r3, r5, #1
	sub	r2, fp, #44
	add	r3, r2, r3, lsl #2
	ldr	r2, [r3, #-388]
	rsb	r2, r2, #5
	str	r2, [r3, #-260]
.L2238:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	uxtb	r3, r0
	str	r3, [fp, #-680]
	ldr	r3, [fp, #-648]
	ble	.L2717
	add	r2, r3, #16384
	ldr	r6, [fp, #-652]
	add	r9, r3, #12288
	str	r9, [fp, #-676]
	mov	r1, r2
	mov	r2, #1
	mov	r8, r2
	add	r1, r1, #176
	str	r2, [fp, #-656]
	str	r1, [fp, #-668]
	sub	r1, fp, #112
	str	r1, [fp, #-664]
.L2252:
	ldr	r3, [fp, #-680]
	cmp	r3, #0
	bne	.L2718
	ldr	r3, [fp, #-656]
	ldr	r2, [fp, #-668]
	mov	r0, r3
	str	r3, [r2]
.L2249:
	ldr	r2, [fp, #-672]
	add	r3, r0, #1024
	add	r3, r3, #12
	cmp	r2, #0
	ldr	r2, [fp, #-676]
	add	r3, r2, r3, lsl #2
	ldr	r2, [fp, #-656]
	str	r2, [r3, #132]
	beq	.L2250
	cmp	r5, #0
	ble	.L2254
	ldr	r10, [fp, #-432]
	sub	lr, fp, #432
	ldr	ip, [fp, #-664]
	mov	r2, #0
.L2256:
	ldr	r1, [lr, #4]!
	add	r2, r2, #1
	cmp	r2, r5
	mov	r3, r8, asl r1
	sub	r3, r3, #1
	and	r3, r3, r0
	mov	r3, r3, asr r10
	mov	r10, r1
	str	r3, [ip, #4]!
	bne	.L2256
.L2254:
	ldr	r3, [fp, #-660]
	ldr	r2, [fp, #-656]
	ldr	r1, [fp, #-664]
	ldr	r3, [r3, #152]
	add	r2, r2, #1
	add	r1, r1, #64
	str	r1, [fp, #-664]
	cmp	r3, r2
	ldr	r1, [fp, #-668]
	str	r2, [fp, #-656]
	add	r1, r1, #4
	str	r1, [fp, #-668]
	bge	.L2252
	ldr	r9, [fp, #-676]
.L2253:
	ldr	r3, [fp, #-652]
	mov	r1, #4
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [fp, #-660]
	ldr	r10, [r3, #152]
	cmp	r10, #0
	str	r0, [fp, #-656]
	blt	.L2719
	ldr	r3, [fp, #-648]
	mov	r7, #1
	mov	r5, #0
	add	r8, r3, #16384
	ldr	r3, [fp, #-496]
	add	r8, r8, #168
	str	r8, [fp, #-664]
	str	r3, [fp, #-668]
	add	r3, r10, #1
	str	r3, [fp, #-676]
.L2263:
	ldr	r3, [fp, #-664]
	sub	r2, fp, #496
	str	r2, [fp, #-672]
	mov	lr, r5, asl #4
	ldr	r2, [fp, #-668]
	sub	r1, fp, #368
	ldr	r6, [r3, #4]!
	mov	r0, #0
	mov	ip, r2
	str	r3, [fp, #-664]
	mov	r6, r6, asl #2
	sub	r3, fp, #44
	add	r3, r3, r6
	str	r2, [r3, #-596]
	ldr	r2, [fp, #-672]
	b	.L2259
.L2720:
	ldr	ip, [r2, #4]!
.L2259:
	add	r3, lr, r0
	cmp	ip, #0
	sub	ip, fp, #44
	addne	r0, r0, #1
	add	r3, ip, r3, lsl #2
	add	r1, r1, #4
	ldrne	r3, [r3, #-128]
	strne	r3, [r1, #-4]
	cmp	r2, r4
	bne	.L2720
	ldr	r0, [fp, #-364]
	sub	r3, fp, #44
	add	r6, r3, r6
	cmp	r5, #0
	str	r0, [r6, #-596]
	ble	.L2260
	mov	ip, r8
	mov	r2, #0
	mov	r1, #1
.L2262:
	ldr	r3, [ip, #4]!
	sub	lr, fp, #44
	add	r2, r2, #1
	add	r3, lr, r3, lsl #2
	ldr	r3, [r3, #-596]
	cmp	r0, r3
	moveq	r1, #0
	cmp	r2, r5
	bne	.L2262
	cmp	r1, #0
	addne	r7, r7, #1
.L2260:
	ldr	r3, [fp, #-676]
	add	r5, r5, #1
	cmp	r5, r3
	bne	.L2263
	ldr	r3, [fp, #-656]
	cmp	r3, #0
	ble	.L2264
	cmp	r7, #0
	ble	.L2264
.L2265:
	ldr	r3, [fp, #-648]
	mov	r5, #0
	add	r4, r3, #16384
	add	r4, r4, #160
.L2269:
	ldr	r3, [fp, #-652]
	add	r5, r5, #1
	ldr	r1, [fp, #-656]
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r7, r5
	str	r0, [r4, #4]!
	bgt	.L2269
	ldr	r3, [fp, #-660]
	ldr	r10, [r3, #152]
.L2264:
	cmp	r10, #0
	ble	.L2274
	ldr	r3, [fp, #-648]
	ldr	r6, [fp, #-652]
	add	r4, r3, #12416
	add	r2, r3, #16384
	add	r2, r2, #172
	mov	r3, #1
	mov	r7, r4
	add	r4, r4, #11
	add	r7, r7, #10
	str	r2, [fp, #-676]
	str	r2, [fp, #-668]
	str	r3, [fp, #-656]
	str	r7, [fp, #-664]
.L2273:
	ldr	r3, [fp, #-656]
	cmp	r3, #0
	ldr	r3, [fp, #-668]
	ldr	r2, [r3, #4]!
	str	r2, [fp, #-672]
	str	r3, [fp, #-668]
	ble	.L2507
	ldr	r7, [fp, #-676]
	mov	r5, r2, asl #1
	ldr	r8, [fp, #-664]
	mov	r10, #0
.L2272:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	add	r3, r5, r10
	add	r3, r3, #1040
	add	r7, r7, #4
	add	r3, r3, #4
	add	r3, r9, r3, lsl #2
	uxtb	r0, r0
	strb	r0, [r8, #1]!
	cmp	r0, #0
	addne	r10, r10, #1
	ldrne	r2, [r7, #-4]
	strne	r2, [r3, #132]
	cmp	r4, r8
	bne	.L2272
.L2270:
	ldr	r3, [fp, #-672]
	add	r4, r4, #3
	ldr	r2, [fp, #-656]
	add	r3, r3, #1040
	ldr	r1, [fp, #-664]
	add	r2, r2, #1
	str	r2, [fp, #-656]
	add	r3, r9, r3, lsl #2
	add	r1, r1, #2
	str	r1, [fp, #-664]
	str	r10, [r3, #132]
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #152]
	cmp	r3, r2
	bge	.L2273
.L2274:
	ldr	r3, .L2747
	mov	r2, #16
	mov	r1, #0
	sub	r0, fp, #608
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [fp, #-660]
	ldr	r10, [r3, #152]
	cmp	r10, #0
	blt	.L2511
	ldr	r3, [fp, #-648]
	mov	r6, #1
	add	r8, r3, #16384
	add	r3, r10, #1
	add	r8, r8, #168
	str	r3, [fp, #-668]
	str	r8, [fp, #-656]
	mov	r3, #0
	str	r3, [fp, #-664]
.L2278:
	ldr	r3, [fp, #-656]
	ldr	r2, [r3, #4]!
	str	r3, [fp, #-656]
	add	r3, r2, #1040
	add	r3, r9, r3, lsl #2
	ldr	r4, [r3, #132]
	cmp	r4, #0
	ble	.L2283
	add	lr, r2, #2064
	sub	r3, fp, #44
	mov	r5, r2, asl #1
	add	lr, lr, #10
	add	r2, r3, r2, lsl #3
	ldr	r3, [fp, #-648]
	mov	ip, #0
	str	r8, [fp, #-672]
	add	lr, r3, lr, lsl #3
.L2282:
	ldr	r3, [lr, #4]!
	sub	r8, fp, #44
	sub	r7, fp, #44
	mov	r0, #1
	add	r1, r5, r3
	add	r7, r7, r3, lsl #3
	add	r1, r8, r1, lsl #2
	str	r6, [r1, #-564]
	ldr	r1, [r2, #-564]
	cmp	r1, #0
	bne	.L2280
	ldr	r0, [r7, #-564]
	adds	r0, r0, #0
	movne	r0, #1
.L2280:
	ldr	r1, [r2, #-560]
	sub	r7, fp, #44
	add	r3, r7, r3, lsl #3
	str	r0, [r2, #-564]
	cmp	r1, #0
	mov	r7, #1
	bne	.L2281
	ldr	r7, [r3, #-560]
	adds	r7, r7, #0
	movne	r7, #1
.L2281:
	add	ip, ip, #1
	str	r7, [r2, #-560]
	cmp	ip, r4
	bne	.L2282
	ldr	r8, [fp, #-672]
.L2283:
	ldr	r3, [fp, #-664]
	ldr	r2, [fp, #-668]
	add	r3, r3, #1
	str	r3, [fp, #-664]
	cmp	r3, r2
	bne	.L2278
	cmp	r10, #0
	movgt	r4, r8
	movgt	lr, #0
	ble	.L2289
.L2287:
	ldr	ip, [r4, #4]!
	mov	r1, #0
	add	r3, ip, #1
	cmp	r3, #1
	mov	ip, ip, asl #2
	bgt	.L2284
	sub	r2, fp, #608
	add	r0, r2, ip
.L2286:
	ldr	r2, [r0, r3, asl #3]
	add	r3, r3, #1
	cmp	r2, #0
	addne	r1, r1, #1
	cmp	r3, #2
	bne	.L2286
.L2284:
	add	lr, lr, #1
	sub	r3, fp, #44
	add	ip, r3, ip
	cmp	lr, r10
	str	r1, [ip, #-588]
	bne	.L2287
.L2289:
	mov	r4, #0
	mov	r0, #1
	mov	r2, r4
.L2288:
	ldr	r3, [r8, #4]!
	sub	r1, fp, #44
	add	ip, r1, r4, lsl #2
	sub	lr, fp, #44
	add	r1, r3, #1040
	add	r3, lr, r3, lsl #2
	add	r1, r9, r1, lsl #2
	ldr	r1, [r1, #132]
	cmp	r1, #0
	bne	.L2291
	ldr	r3, [r3, #-588]
	add	r4, r4, #1
	str	r0, [ip, #-580]
	cmp	r3, #0
	add	r3, r3, #1
	strgt	r3, [ip, #-580]
.L2291:
	add	r2, r2, #1
	cmp	r2, r10
	ble	.L2288
	cmp	r4, #1
	ble	.L2511
	ldr	r3, [fp, #-652]
	ldr	r1, .L2747+4
	ldr	r0, [r3, #2796]
	bl	HEVC_ue_v
	cmp	r0, #1024
	mov	r5, r0
	bge	.L2721
	cmp	r0, #0
	ble	.L2290
	ldr	r8, [fp, #-652]
	mov	r6, #0
	mov	r7, #1
	str	r9, [fp, #-656]
.L2299:
	cmp	r4, #1
	ble	.L2300
	sub	r9, fp, #624
	mov	r10, #1
.L2298:
	ldr	r2, [r9, #4]!
	ldr	r0, [r8, #2796]
	add	r2, r2, #1
	cmp	r2, #1
	bls	.L2512
	mov	r3, #0
.L2297:
	add	r3, r3, #1
	cmp	r2, r7, asl r3
	mov	r1, r3
	bhi	.L2297
	add	r10, r10, #1
	bl	BsGet
	cmp	r10, r4
	bne	.L2298
.L2300:
	add	r6, r6, #1
	cmp	r5, r6
	bne	.L2299
	ldr	r9, [fp, #-656]
.L2290:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	uxtb	r3, r0
	cmp	r3, #0
	bne	.L2301
	ldr	r2, [fp, #-660]
	ldr	r1, [r2, #152]
	cmp	r1, #0
	blt	.L2305
	ldr	r0, [fp, #-648]
	add	r1, r1, #1
	add	r2, r0, #16384
	ldr	r0, [r0, #12]
	add	r2, r2, #200
.L2308:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L2308
.L2305:
	ldr	r3, [fp, #-648]
	ldr	r8, [r3, #20]
	cmp	r8, #0
	blt	.L2304
	ldr	r3, [fp, #-648]
	add	r8, r8, #1
	mov	r4, #0
	add	lr, r3, #20480
	add	r7, r3, #8320
	add	lr, lr, #228
	add	r6, r3, #128
.L2307:
	ldr	ip, [r7, #4]!
	cmp	ip, #0
	beq	.L2513
	mov	r2, #0
	mov	r0, r6
	mov	r1, r2
.L2309:
	ldr	r3, [r0, #4]!
	add	r1, r1, #1
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, r3, #1040
	add	r3, r3, #2
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r2, r3
	movlt	r2, r3
	cmp	r1, ip
	bne	.L2309
.L2310:
	add	r4, r4, #1
	str	r2, [lr, #4]!
	cmp	r4, r8
	add	r6, r6, #8
	bne	.L2307
.L2304:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2311
	ldr	r3, [fp, #-660]
	mov	ip, r0
	mov	r1, #7
	ldr	r4, [r3, #152]
	ldr	r3, [fp, #-648]
	cmp	ip, r4
	add	r0, r4, #1
	add	lr, r3, #24576
	add	lr, lr, #236
	bge	.L2325
.L2324:
	add	ip, ip, #1
	cmp	ip, r4
	bgt	.L2321
	mov	r2, lr
	mov	r3, ip
.L2322:
	add	r3, r3, #1
	str	r1, [r2, #4]!
	cmp	r3, r0
	bne	.L2322
.L2321:
	cmp	ip, r4
	add	lr, lr, #12
	blt	.L2324
.L2325:
	ldr	r4, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r1, .L2747+8
	strb	r0, [r9, #134]
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r4, #2
	moveq	r4, #1
	cmp	r0, r4
	str	r0, [fp, #-700]
	ldrge	r6, [fp, #-652]
	blt	.L2330
.L2329:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [fp, #-648]
	sub	r1, fp, #616
	add	r4, r4, #1
	ldr	r3, [r3, #12]
	uxtb	r2, r0
	mov	r0, r6
	bl	HEVC_DecPTL
	ldr	r3, [fp, #-700]
	cmp	r3, r4
	bge	.L2329
.L2330:
	ldr	r3, [fp, #-648]
	ldr	r1, [r3, #20]
	ldr	r3, [fp, #-660]
	add	r1, r5, r1
	add	r1, r1, #1
	cmp	r1, #1
	str	r1, [r3, #148]
	ble	.L2722
	ldr	r5, [fp, #-652]
	ldr	r1, .L2747+12
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	mov	r1, #2
	mov	r4, r0
	ldr	r0, [r5, #2796]
	bl	BsGet
	movw	r3, #1025
	str	r0, [fp, #-704]
	ldr	r0, [fp, #-660]
	ldr	r2, [r0, #148]
	add	r1, r4, r2
	str	r1, [r0, #156]
	cmp	r1, r3
	bgt	.L2503
	cmp	r1, #1
	ldr	r1, [fp, #-660]
	mvn	r3, #0
	str	r3, [r1, #228]
	ble	.L2332
	ldr	r3, [fp, #-648]
	add	r1, r3, #16384
	add	r0, r3, #12416
	add	r3, r3, #14464
	mov	ip, r1
	add	r1, r1, #232
	str	r1, [fp, #-692]
	add	r1, r0, #14
	str	r1, [fp, #-688]
	add	r1, ip, #224
	str	r1, [fp, #-712]
	add	r3, r3, #14
	ldr	r1, [fp, #-704]
	str	r3, [fp, #-716]
	mov	r3, #0
	sub	r1, r1, #2
	str	r3, [fp, #-696]
	clz	r1, r1
	mov	r3, #1
	mov	r10, r3
	str	r3, [fp, #-676]
	mov	r1, r1, lsr #5
	str	r1, [fp, #-708]
.L2367:
	cmp	r2, #2
	ldr	r1, [fp, #-676]
	movgt	r3, #1
	movle	r3, #0
	cmp	r2, r1
	movgt	r3, #0
	cmp	r3, #0
	beq	.L2333
	sub	r2, r2, #1
	ldr	r3, [fp, #-652]
	cmp	r2, #1
	ldr	r0, [r3, #2796]
	bls	.L2515
	mov	r3, #0
.L2335:
	add	r3, r3, #1
	cmp	r2, r10, asl r3
	mov	r1, r3
	bhi	.L2335
.L2334:
	bl	BsGet
	ldr	r3, [fp, #-692]
	str	r0, [r3]
	ldr	r3, [fp, #-660]
	ldr	r2, [r3, #148]
.L2336:
	ldr	r3, [fp, #-676]
	ldr	r1, [fp, #-708]
	cmp	r2, r3
	ldr	r0, [fp, #-676]
	ldrle	r3, [fp, #-692]
	ldrgt	r3, [fp, #-676]
	ldrle	r3, [r3]
	addle	r3, r3, #1
	str	r3, [fp, #-684]
	ldr	r3, [fp, #-648]
	ldr	r2, [r3, #20]
	cmp	r0, r2
	orrgt	r1, r1, #1
	cmp	r1, #0
	mov	r2, r1
	bne	.L2338
	ldr	r1, [fp, #-684]
	add	r1, r3, r1, lsl #2
	add	r1, r1, #8192
	ldr	r3, [r1, #132]
	cmp	r3, #0
	str	r3, [fp, #-680]
	beq	.L2340
	ldr	r3, [fp, #-676]
	ldr	r5, [fp, #-680]
	ldr	r0, [fp, #-704]
	mov	lr, r3, asl #1
	sub	r4, r5, #1
	add	ip, r9, lr
	mov	r3, r2
	b	.L2348
.L2723:
	cmp	r0, #2
	beq	.L2344
	cmp	r0, #0
	addeq	r2, ip, r3
	add	r3, r3, #1
	streqb	r10, [r2, #141]
	cmp	r3, r5
	mov	r2, r3
	bcs	.L2506
.L2348:
	cmp	r0, #1
	bne	.L2723
	add	r6, ip, r3
	rsb	r2, r4, r2
	add	r3, r3, #1
	clz	r2, r2
	cmp	r3, r5
	mov	r2, r2, lsr #5
	strb	r2, [r6, #141]
	mov	r2, r3
	bcc	.L2348
.L2506:
	ldr	r3, [r1, #132]
.L2706:
	str	r3, [fp, #-680]
.L2340:
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #156]
	cmp	r3, #0
	str	r3, [fp, #-672]
	beq	.L2354
	ldr	r3, [fp, #-648]
	ldr	r8, [fp, #-716]
	add	r3, r3, #132
	str	r3, [fp, #-656]
	ldr	r3, [fp, #-712]
	str	r3, [fp, #-668]
	mov	r3, #0
	str	r3, [fp, #-664]
.L2353:
	ldr	r3, [fp, #-668]
	ldr	r2, [fp, #-648]
	ldr	r7, [r3, #4]!
	str	r3, [fp, #-668]
	add	r3, r7, #2080
	add	r3, r3, #1
	add	r3, r2, r3, lsl #2
	ldr	r6, [r3, #4]
	cmp	r6, #0
	beq	.L2357
	add	r7, r7, #17
	ldr	r3, [fp, #-648]
	sub	r5, r8, #2048
	ldr	r4, [fp, #-656]
	sub	r5, r5, #2
	add	r7, r3, r7, lsl #3
	mov	r0, r8
	mov	lr, #0
.L2356:
	mov	r3, #0
	strb	r3, [r0, #1]!
	ldrb	r3, [r5, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2358
	cmp	lr, #0
	strb	r10, [r0]
	ldr	r3, [r4]
	beq	.L2358
	add	r3, r3, #1024
	add	r2, r8, #1
	add	r3, r3, #12
	mov	r1, r7
	add	r3, r9, r3, lsl #2
	ldr	ip, [r3, #132]
	add	ip, r9, ip, lsl #1
.L2360:
	ldr	r3, [r1, #4]!
	add	r2, r2, #1
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, ip, r3
	ldrb	r3, [r3, #137]	@ zero_extendqisi2
	cmp	r3, #0
	strneb	r10, [r2, #-1]
	cmp	r0, r2
	bne	.L2360
.L2358:
	add	lr, lr, #1
	add	r4, r4, #4
	cmp	lr, r6
	bne	.L2356
.L2357:
	ldr	r3, [fp, #-664]
	add	r8, r8, #2
	ldr	r2, [fp, #-672]
	add	r3, r3, #1
	str	r3, [fp, #-664]
	cmp	r3, r2
	ldr	r3, [fp, #-656]
	add	r3, r3, #8
	str	r3, [fp, #-656]
	bne	.L2353
.L2354:
	ldr	r3, [fp, #-680]
	cmp	r3, #0
	beq	.L2351
	ldr	r2, [fp, #-676]
	mov	r7, #0
	ldr	r3, [fp, #-680]
	ldr	r1, [fp, #-684]
	add	r3, r3, r2, lsl #1
	ldr	r0, [fp, #-648]
	add	r3, r3, #12416
	ldr	r2, [fp, #-688]
	add	r1, r0, r1, lsl #3
	add	r3, r3, #12
	ldr	ip, [fp, #-696]
	add	r1, r1, #132
	add	r3, r0, r3
.L2362:
	ldrb	r0, [r2, #1]!	@ zero_extendqisi2
	add	r1, r1, #4
	cmp	r0, #0
	addne	r7, r7, #1
	ldrne	ip, [r1, #-4]
	cmp	r2, r3
	bne	.L2362
	ldr	r3, [fp, #-684]
	mov	r5, #0
	str	r9, [fp, #-664]
	add	r8, r3, #2080
	ldr	r3, [fp, #-688]
	str	r7, [fp, #-656]
	add	r6, r3, #2048
	ldr	r3, [fp, #-700]
	add	r6, r6, #2
	str	ip, [fp, #-696]
	add	r4, r3, #1
	ldr	r3, [fp, #-648]
	add	r8, r3, r8, lsl #2
	mov	r7, r3
	mov	r9, r8
	mov	r8, r6
	ldr	r6, [fp, #-652]
.L2366:
	ldrb	r3, [r8, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2363
	ldr	r3, [r7, #20]
	cmp	r3, #0
	ble	.L2363
	cmp	r4, #1
	ldr	r0, [r6, #2796]
	bls	.L2517
	mov	r3, #0
.L2365:
	add	r3, r3, #1
	cmp	r4, r10, asl r3
	mov	r1, r3
	bhi	.L2365
.L2364:
	bl	BsGet
.L2363:
	ldr	r3, [r9, #4]
	add	r5, r5, #1
	cmp	r5, r3
	bcc	.L2366
	ldr	r7, [fp, #-656]
	ldr	r9, [fp, #-664]
	cmp	r7, #1
	beq	.L2724
.L2351:
	ldr	r1, [fp, #-660]
	ldr	r2, [fp, #-676]
	ldr	r0, [fp, #-692]
	ldr	r3, [r1, #156]
	add	r2, r2, #1
	add	r0, r0, #4
	str	r0, [fp, #-692]
	cmp	r3, r2
	ldr	r0, [fp, #-688]
	str	r2, [fp, #-676]
	add	r0, r0, #2
	str	r0, [fp, #-688]
	ble	.L2332
	mov	r3, r1
	ldr	r2, [r1, #148]
	b	.L2367
.L2512:
	mov	r1, #0
	add	r10, r10, #1
	bl	BsGet
	cmp	r10, r4
	bne	.L2298
	b	.L2300
.L2250:
	cmp	r5, #0
	ble	.L2254
	ldr	r9, [fp, #-664]
	ldr	r10, [fp, #-672]
.L2255:
	ldr	r1, [r7, r10, asl #2]
	add	r10, r10, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	cmp	r10, r5
	str	r0, [r9, #4]!
	bne	.L2255
	b	.L2254
.L2718:
	mov	r1, #6
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [fp, #-668]
	str	r0, [r3]
	b	.L2249
.L2507:
	mov	r10, #0
	b	.L2270
.L2333:
	ldr	r1, [fp, #-692]
	str	r3, [r1]
	b	.L2336
.L2338:
	ldr	r2, [fp, #-684]
	ldr	r3, [fp, #-648]
	add	r4, r3, r2, lsl #2
	add	r4, r4, #8192
	ldr	r3, [r4, #132]
	cmp	r3, #0
	str	r3, [fp, #-680]
	beq	.L2340
	ldr	r6, [fp, #-688]
	mov	r5, #0
	ldr	r7, [fp, #-652]
.L2341:
	mov	r1, #1
	ldr	r0, [r7, #2796]
	bl	BsGet
	add	r5, r5, #1
	strb	r0, [r6, #1]!
	ldr	r3, [r4, #132]
	cmp	r5, r3
	bcc	.L2341
	str	r3, [fp, #-680]
	b	.L2340
.L2344:
	add	lr, lr, #12416
	ldr	r0, [fp, #-680]
	add	lr, lr, #12
.L2505:
	ldr	ip, [fp, #-648]
	add	r2, lr, r3
	add	r2, ip, r2
	ldr	ip, [fp, #-676]
	orrs	ip, r3, ip
	add	r3, r3, #1
	bne	.L2346
.L2725:
	cmp	r3, r0
	strb	r10, [r2, #1]!
	bcs	.L2506
	ldr	ip, [fp, #-676]
	orrs	ip, r3, ip
	add	r3, r3, #1
	beq	.L2725
.L2346:
	cmp	r3, r0
	bcc	.L2505
	ldr	r3, [r1, #132]
	b	.L2706
.L2517:
	mov	r1, #0
	b	.L2364
.L2724:
	ldr	r3, [fp, #-696]
	add	r3, r3, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	ble	.L2351
	ldr	r3, [fp, #-652]
	mov	r1, r7
	ldr	r0, [r3, #2796]
	bl	BsGet
	b	.L2351
.L2722:
	movw	r3, #1025
	cmp	r1, r3
	ldr	r3, [fp, #-660]
	ldrle	r2, [fp, #-660]
	str	r1, [r3, #156]
	mvnle	r3, #0
	strle	r3, [r2, #228]
	bgt	.L2726
.L2332:
	ldr	r8, [fp, #-652]
	ldr	r1, .L2747+16
	ldr	r0, [r8, #2796]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-660]
	cmp	r0, #255
	mov	r2, r0
	str	r0, [r3, #160]
	bhi	.L2500
	ldr	r3, [fp, #-648]
	mov	r4, #0
	add	r6, r3, #24576
	add	r6, r6, #252
	mov	r5, r6
	b	.L2381
.L2370:
	mov	r1, #16
	ldr	r0, [r8, #2796]
	bl	BsGet
	mov	r1, #16
	str	r0, [r7, #4]
	ldr	r0, [r8, #2796]
	bl	BsGet
	mov	r1, #1
	str	r0, [r7, #8]
	ldr	r0, [r8, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2727
	cmp	r10, #0
	beq	.L2375
	ldr	r3, [r10, #12]
	str	r3, [r7, #12]
	ldrb	r3, [r10]	@ zero_extendqisi2
	strb	r3, [r7]
	ldr	r3, [r10, #16]
	str	r3, [r7, #16]
	ldr	r3, [r10, #20]
	str	r3, [r7, #20]
.L2375:
	mov	r1, #1
	ldr	r0, [r8, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2728
	str	r0, [r7, #24]
	str	r0, [r7, #28]
	str	r0, [r7, #32]
	str	r0, [r7, #36]
.L2377:
	ldr	r2, [r7, #16]
	ldr	r3, [r7, #20]
	cmp	r2, #8
	bhi	.L2379
	cmp	r3, #8
	bls	.L2380
.L2379:
	ldr	r1, .L2747+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r7, #16]
	str	r3, [r7, #20]
.L2380:
	ldr	r3, [fp, #-660]
	add	r4, r4, #1
	add	r5, r5, #40
	ldr	r2, [r3, #160]
	cmp	r4, r2
	bhi	.L2729
.L2381:
	cmp	r4, #1
	subgt	r7, fp, #592
	movgt	r10, r6
	bgt	.L2370
	cmp	r4, #0
	mov	r7, r5
	subne	r10, r5, #40
	moveq	r10, r4
	b	.L2370
.L2748:
	.align	2
.L2747:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC199
	.word	.LC201
	.word	.LC202
	.word	.LC227
	.word	.LC209
	.word	.LC205
	.word	.LC206
	.word	.LC207
	.word	.LC208
	.word	.LC213
	.word	.LC211
	.word	.LC212
	.word	.LC210
	.word	.LC214
	.word	.LC215
	.word	.LC216
	.word	.LC198
	.word	.LC217
	.word	.LC219
	.word	.LC220
	.word	.LC221
	.word	.LC223
	.word	.LC224
	.word	.LC226
	.word	.LC225
	.word	.LC228
	.word	.LC203
	.word	.LC222
	.word	.LC218
	.word	.LC200
	.word	.LANCHOR0+596
.L2728:
	ldr	r1, .L2747+24
	ldr	r0, [r8, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2747+28
	str	r0, [r7, #24]
	ldr	r0, [r8, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2747+32
	str	r0, [r7, #28]
	ldr	r0, [r8, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2747+36
	str	r0, [r7, #32]
	ldr	r0, [r8, #2796]
	bl	HEVC_ue_v
	str	r0, [r7, #36]
	b	.L2377
.L2727:
	mov	r1, #2
	ldr	r0, [r8, #2796]
	bl	BsGet
	cmp	r0, #3
	str	r0, [r7, #12]
	beq	.L2730
	cmp	r10, #0
	streqb	r10, [r7]
	ldrneb	r3, [r10]	@ zero_extendqisi2
	strneb	r3, [r7]
.L2373:
	mov	r1, #4
	ldr	r0, [r8, #2796]
	bl	BsGet
	mov	r1, #4
	str	r0, [r7, #16]
	ldr	r0, [r8, #2796]
	bl	BsGet
	str	r0, [r7, #20]
	b	.L2375
.L2729:
	cmp	r2, #0
	bne	.L2731
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ble	.L2385
.L2501:
	ldr	r1, [fp, #-648]
	add	r0, r1, #16384
	mov	r1, #0
	add	r0, r0, #184
	mov	ip, r1
.L2384:
	add	r1, r1, #1
	str	ip, [r0, #4]!
	cmp	r1, r3
	blt	.L2384
.L2383:
	cmp	r2, #0
	beq	.L2385
	ldr	r2, [fp, #-660]
	adds	r4, r3, #0
	movne	r4, #1
	ldr	r2, [r2, #152]
	cmp	r4, r2
	bgt	.L2392
	add	r6, r4, #4096
	ldr	r3, [fp, #-648]
	add	r6, r6, #46
	ldr	r7, [fp, #-660]
	mov	r5, #1
	add	r6, r3, r6, lsl #2
.L2391:
	ldr	r2, [r7, #160]
	ldr	r3, [fp, #-652]
	add	r2, r2, #1
	cmp	r2, #1
	ldr	r0, [r3, #2796]
	bls	.L2519
	mov	r3, #0
.L2390:
	add	r3, r3, #1
	cmp	r2, r5, asl r3
	mov	r1, r3
	bhi	.L2390
.L2389:
	bl	BsGet
	add	r4, r4, #1
	str	r0, [r6, #4]!
	ldr	r3, [r7, #152]
	cmp	r3, r4
	bge	.L2391
.L2392:
	ldr	r4, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #133]
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	ble	.L2388
	ldr	r3, [fp, #-648]
	mov	r6, #1
	ldr	r7, [fp, #-660]
	add	r5, r3, #16384
	add	r4, r3, #12416
	add	r5, r5, #172
	add	r4, r4, #8
	b	.L2397
.L2396:
	ldr	r3, [r7, #152]
	add	r4, r4, #1
	cmp	r3, r6
	blt	.L2388
.L2397:
	ldr	r3, [r5, #4]!
	add	r6, r6, #1
	add	r3, r3, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	bne	.L2396
	ldr	r3, [fp, #-652]
	mov	r1, #1
	add	r4, r4, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	strb	r0, [r4, #-1]
	ldr	r3, [r7, #152]
	cmp	r3, r6
	bge	.L2397
.L2388:
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #156]
	cmp	r3, #1
	bls	.L2395
	ldr	r3, [fp, #-648]
	ldr	r6, [fp, #-652]
	add	r2, r3, #14464
	add	r1, r3, #16384
	mov	r7, r3
	add	r2, r2, #16
	str	r9, [fp, #-656]
	str	r2, [fp, #-672]
	add	r2, r1, #232
	str	r2, [fp, #-688]
	mov	r2, #1
	str	r2, [fp, #-684]
.L2409:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [fp, #-660]
	ldr	r2, [fp, #-684]
	mov	r5, #0
	ldr	r3, [r3, #148]
	cmp	r3, r2
	ldrls	r3, [fp, #-688]
	ldrhi	r3, [fp, #-684]
	ldrls	r3, [r3]
	addls	r3, r3, #1
	add	r1, r3, #2064
	add	r2, r7, r3, lsl #3
	add	r3, r7, r3, lsl #2
	add	r2, r2, #132
	str	r3, [fp, #-676]
	str	r2, [fp, #-680]
	add	r2, r1, #8
	str	r2, [fp, #-668]
	adds	r0, r0, #0
	movne	r0, #1
	str	r0, [fp, #-664]
.L2408:
	ldr	r3, [fp, #-664]
	cmp	r5, #0
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	clzeq	r0, r5
	moveq	r0, r0, lsr #5
	bne	.L2732
.L2402:
	cmp	r0, #0
	beq	.L2403
	ldr	r3, [fp, #-676]
	add	r10, r3, #8192
	ldr	r3, [r10, #132]
	cmp	r3, #0
	beq	.L2407
	ldr	r8, [fp, #-680]
	mov	r4, #0
	ldr	r9, [fp, #-672]
.L2404:
	ldrb	r3, [r9, #1]!	@ zero_extendqisi2
	add	r4, r4, #1
	cmp	r3, #0
	beq	.L2405
	ldrb	r3, [r7, #3]	@ zero_extendqisi2
	ldr	r1, .L2747+40
	cmp	r3, #0
	bne	.L2406
	ldr	r3, [r8]
	cmp	r3, #0
	beq	.L2405
.L2406:
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
.L2405:
	ldr	r3, [r10, #132]
	add	r8, r8, #4
	cmp	r4, r3
	bcc	.L2404
.L2407:
	ldr	r1, .L2747+44
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2747+48
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
.L2403:
	ldr	r2, [fp, #-668]
	add	r5, r5, #1
	ldr	r3, [fp, #-656]
	add	r3, r3, r2, lsl #2
	ldr	r3, [r3, #136]
	cmp	r5, r3
	bls	.L2408
	ldr	r3, [fp, #-660]
	ldr	r2, [fp, #-684]
	ldr	r1, [fp, #-672]
	ldr	r3, [r3, #156]
	add	r2, r2, #1
	add	r1, r1, #2
	str	r1, [fp, #-672]
	cmp	r2, r3
	ldr	r1, [fp, #-688]
	str	r2, [fp, #-684]
	add	r1, r1, #4
	str	r1, [fp, #-688]
	bcc	.L2409
	ldr	r9, [fp, #-656]
.L2395:
	ldr	r4, [fp, #-652]
	ldr	r1, .L2747+52
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2733
	ldr	r1, [fp, #-648]
	ldr	r2, [fp, #-660]
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	ldr	r2, [r2, #152]
	cmp	r3, #0
	movne	r8, #1
	moveq	r8, #2
	cmp	r8, r2
	bgt	.L2410
	mov	r5, r8, asl #1
	ldr	r10, [fp, #-652]
	add	r7, r5, r8
	add	r6, r6, #2
	add	r7, r7, #12416
	add	r7, r7, #8
	add	r7, r1, r7
.L2419:
	clz	r4, r3
	mov	r4, r4, lsr #5
	cmp	r4, r8
	bge	.L2418
	add	r3, r5, #12416
	ldr	r2, [fp, #-648]
	add	r3, r3, #8
	add	r3, r3, r4
	add	r4, r2, r3
	b	.L2417
.L2416:
	cmp	r7, r4
	beq	.L2418
.L2417:
	ldrb	r3, [r4, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2416
	mov	r1, r6
	ldr	r0, [r10, #2796]
	bl	BsGet
	cmp	r7, r4
	bne	.L2417
.L2418:
	ldr	r3, [fp, #-660]
	add	r8, r8, #1
	add	r7, r7, #3
	add	r5, r5, #2
	ldr	r3, [r3, #152]
	cmp	r3, r8
	blt	.L2410
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	b	.L2419
.L2732:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	b	.L2402
.L2733:
	ldr	r3, [fp, #-652]
	add	r1, r6, #2
	ldr	r0, [r3, #2796]
	bl	BsGet
.L2410:
	ldr	r3, [fp, #-652]
	ldr	r1, .L2747+56
	ldr	r0, [r3, #2796]
	bl	HEVC_ue_v
	subs	r5, r0, #0
	movgt	r4, #1
	ble	.L2423
.L2422:
	ldr	r3, [fp, #-652]
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r5, r4
	bge	.L2422
.L2423:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2734
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2513:
	mov	r2, ip
	b	.L2310
.L2519:
	mov	r1, #0
	b	.L2389
.L2385:
	ldr	r0, [fp, #-660]
	adds	r3, r3, #0
	movne	r3, #1
	ldr	r1, [r0, #152]
	cmp	r3, r1
	bgt	.L2392
	add	r2, r3, #4096
	ldr	ip, [fp, #-648]
	add	r2, r2, #46
	ldr	r0, [r0, #160]
	add	r1, r1, #1
	add	r2, ip, r2, lsl #2
.L2393:
	cmp	r3, r0
	movcc	ip, r3
	add	r3, r3, #1
	movcs	ip, r0
	cmp	r3, r1
	str	ip, [r2, #4]!
	bne	.L2393
	b	.L2392
.L2730:
	mov	r1, #1
	ldr	r0, [r8, #2796]
	bl	BsGet
	strb	r0, [r7]
	b	.L2373
.L2511:
	mov	r5, #0
	b	.L2290
.L2311:
	ldr	r3, [fp, #-660]
	mov	r2, #0
	ldr	r0, [fp, #-648]
	mov	r8, #7
	str	r9, [fp, #-664]
	mov	r9, r2
	ldr	r3, [r3, #152]
	add	r10, r0, #24576
	str	r5, [fp, #-656]
	add	r10, r10, #240
	mov	r5, r0
	mov	r1, r3
	cmp	r9, r1
	bge	.L2735
.L2318:
	add	r9, r9, #1
	cmp	r9, r1
	bgt	.L2314
	sub	r7, r9, #1
	mov	r4, r9
	str	r9, [fp, #-668]
	mov	r6, r10
	ldr	r9, [fp, #-660]
	b	.L2317
.L2316:
	ldr	r1, [r9, #152]
	add	r4, r4, #1
	add	r6, r6, #4
	cmp	r1, r4
	blt	.L2736
.L2317:
	add	r3, r7, r4, lsl #1
	add	r3, r3, #12416
	add	r3, r3, #9
	ldrb	r3, [r5, r3]	@ zero_extendqisi2
	cmp	r3, #0
	streq	r8, [r6]
	beq	.L2316
	ldr	r3, [fp, #-652]
	mov	r1, #3
	ldr	r0, [r3, #2796]
	bl	BsGet
	str	r0, [r6]
	b	.L2316
.L2736:
	ldr	r9, [fp, #-668]
.L2314:
	cmp	r9, r1
	add	r10, r10, #12
	blt	.L2318
.L2735:
	ldr	r5, [fp, #-656]
	ldr	r9, [fp, #-664]
	b	.L2325
.L2301:
	ldr	r7, [fp, #-660]
	ldr	r3, [r7, #152]
	cmp	r3, #0
	blt	.L2305
	ldr	r3, [fp, #-648]
	mov	r6, #0
	add	r4, r3, #16384
	add	r4, r4, #200
.L2306:
	ldr	r3, [fp, #-652]
	mov	r1, #3
	add	r6, r6, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	str	r0, [r4, #4]!
	ldr	r3, [r7, #152]
	cmp	r3, r6
	bge	.L2306
	b	.L2305
.L2734:
	ldr	r4, [fp, #-652]
	ldr	r0, [r4, #2796]
	bl	BsToNextByte
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L2737
.L2425:
	ldr	r4, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	orrs	r3, r0, r6
	mov	r7, r0
	beq	.L2427
	ldr	r3, [fp, #-648]
	ldrb	r4, [r3, #3]	@ zero_extendqisi2
	ldr	r3, [r3, #20]
	clz	r4, r4
	mov	r4, r4, lsr #5
	cmp	r4, r3
	bhi	.L2427
	ldr	r5, [fp, #-648]
	mov	r10, #0
	str	r9, [fp, #-656]
	mov	r9, r4
	mov	r4, r10
.L2434:
	mov	r8, #0
	b	.L2433
.L2429:
	cmp	r7, #0
	bne	.L2738
.L2430:
	cmp	r10, #0
	bne	.L2739
.L2431:
	cmp	r4, #0
	bne	.L2740
.L2432:
	ldr	r3, [r5, #12]
	cmp	r8, r3
	bhi	.L2741
.L2433:
	cmp	r6, #0
	add	r8, r8, #1
	beq	.L2429
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r7, #0
	mov	r10, r0
	beq	.L2430
.L2738:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r10, #0
	mov	r4, r0
	beq	.L2431
.L2739:
	ldr	r3, [fp, #-652]
	mov	r1, #16
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [fp, #-652]
	mov	r1, #16
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r4, #0
	beq	.L2432
.L2740:
	ldr	r3, [fp, #-652]
	mov	r1, #2
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [fp, #-652]
	mov	r1, #2
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [r5, #12]
	cmp	r8, r3
	bls	.L2433
.L2741:
	ldr	r3, [r5, #20]
	add	r9, r9, #1
	cmp	r9, r3
	bls	.L2434
	ldr	r9, [fp, #-656]
.L2427:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	subs	r6, r0, #0
	bne	.L2742
	ldr	r3, [fp, #-660]
	ldr	r4, [r3, #152]
.L2436:
	ldr	r7, [fp, #-652]
	mov	r5, #0
.L2437:
	mov	r1, #3
	ldr	r0, [r7, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r7, #2796]
	add	r5, r5, r1
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r7, #2796]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r7, #2796]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r7, #2796]
	bl	BsGet
	cmp	r5, r4
	bls	.L2437
	cmp	r4, #0
	cmpne	r6, #0
	beq	.L2438
	ldr	r3, [fp, #-648]
	ldr	r5, [fp, #-660]
	ldrb	r4, [r3, #3]	@ zero_extendqisi2
	ldr	r3, [r5, #152]
	clz	r4, r4
	mov	r4, r4, lsr #5
	cmp	r4, r3
	bhi	.L2438
.L2439:
	ldr	r3, [fp, #-652]
	mov	r1, #4
	add	r4, r4, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [r5, #152]
	cmp	r4, r3
	bls	.L2439
.L2438:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r0, #0
	bne	.L2502
	sub	r5, fp, #644
	ldr	r7, [fp, #-652]
	mov	r4, r0
	mov	r6, r5
.L2441:
	mov	r1, #1
	ldr	r0, [r7, #2796]
	bl	BsGet
	add	r4, r4, #1
	uxtb	r0, r0
	strb	r0, [r6], #1
	cmp	r0, #0
	beq	.L2440
	mov	r1, #1
	ldr	r0, [r7, #2796]
	bl	BsGet
.L2440:
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #152]
	cmp	r4, r3
	bls	.L2441
	cmp	r3, #0
	beq	.L2502
	ldr	r3, [fp, #-648]
	mov	r7, #1
	ldr	r8, [fp, #-660]
	add	r6, r3, #16384
	add	r6, r6, #172
.L2443:
	ldr	r3, [r6, #4]!
	add	r2, r3, #1040
	add	r2, r9, r2, lsl #2
	ldr	r2, [r2, #132]
	cmp	r2, #0
	beq	.L2446
	ldrb	r10, [r5, r7]	@ zero_extendqisi2
	mov	r4, #0
	b	.L2445
.L2444:
	ldr	r3, [r6]
	add	r2, r3, #1040
	add	r2, r9, r2, lsl #2
	ldr	r2, [r2, #132]
	cmp	r4, r2
	bcs	.L2446
.L2445:
	add	r3, r4, r3, lsl #1
	cmp	r10, #0
	add	r3, r3, #1040
	add	r4, r4, #1
	add	r3, r3, #4
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	beq	.L2444
	sub	r2, fp, #44
	add	r3, r2, r3
	ldrb	r3, [r3, #-600]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2444
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	b	.L2444
.L2446:
	ldr	r3, [r8, #152]
	add	r7, r7, #1
	cmp	r7, r3
	bls	.L2443
.L2502:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L2447
.L2451:
	ldr	r4, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L2449
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	beq	.L2449
	ldr	r3, [fp, #-648]
	mov	r7, #0
	ldr	r5, [fp, #-652]
	mov	r4, #1
	add	r6, r3, #16384
	mov	r10, r7
	add	r6, r6, #172
	mov	r8, r3
.L2452:
	ldr	r3, [r6, #4]!
	add	r1, r3, #1040
	add	r1, r9, r1, lsl #2
	ldr	r1, [r1, #132]
	cmp	r1, #0
	movne	r7, #0
	bne	.L2458
	b	.L2460
.L2456:
	ldr	r3, [r6]
	add	r1, r3, #1040
	add	r1, r9, r1, lsl #2
	ldr	r1, [r1, #132]
	cmp	r7, r1
	bcs	.L2460
.L2458:
	add	r3, r7, r3, lsl #1
	ldrb	r1, [r8, #3]	@ zero_extendqisi2
	add	r3, r3, #1040
	add	r7, r7, #1
	add	r3, r3, #4
	cmp	r1, #0
	ldr	r1, .L2747+60
	add	r3, r9, r3, lsl #2
	bne	.L2453
	ldr	r3, [r3, #132]
	cmp	r3, #0
	ble	.L2454
.L2453:
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	mov	r10, r0
.L2454:
	cmp	r10, #0
	beq	.L2456
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L2456
	ldr	r1, .L2747+64
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	b	.L2456
.L2460:
	ldr	r3, [fp, #-660]
	add	r4, r4, #1
	ldr	r3, [r3, #152]
	cmp	r4, r3
	bls	.L2452
.L2449:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	cmp	r0, #0
	bne	.L2743
.L2461:
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #152]
	cmp	r3, #0
	beq	.L2499
	ldr	r3, [fp, #-648]
	mov	r5, #1
	ldr	r6, [fp, #-660]
	add	r4, r3, #16384
	add	r4, r4, #172
	b	.L2498
.L2497:
	ldr	r3, [r6, #152]
	cmp	r5, r3
	bhi	.L2499
.L2498:
	ldr	r3, [r4, #4]!
	add	r5, r5, #1
	add	r3, r3, #1040
	add	r3, r9, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	bne	.L2497
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [r6, #152]
	cmp	r5, r3
	bls	.L2498
.L2499:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2447:
	ldr	r5, [fp, #-660]
	mov	r4, #0
.L2450:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	add	r4, r4, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [r5, #152]
	cmp	r4, r3
	bls	.L2450
	b	.L2451
.L2715:
	mov	r0, #1
	ldr	r2, .L2747+124
	str	r0, [sp]
	ldr	r1, .L2747+68
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2743:
	ldr	r3, [fp, #-652]
	ldr	r1, .L2747+72
	ldr	r0, [r3, #2796]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-648]
	ldr	r5, [r3, #24]
	add	r4, r0, r5
	cmp	r4, #1024
	bhi	.L2462
	cmp	r5, r4
	ldrcc	r6, [fp, #-652]
	bcc	.L2468
	b	.L2469
.L2745:
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r7, r0
.L2466:
	ldr	r1, .L2747+76
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	uxtb	r2, r7
	sub	r1, fp, #552
	mov	ip, r0
	cmp	ip, #7
	mov	r3, r0
	mov	r0, r6
	bhi	.L2744
	add	r5, r5, #1
	bl	HEVC_DecHrdParam
	cmp	r4, r5
	bls	.L2469
.L2468:
	cmp	r5, #0
	mov	r1, #1
	bne	.L2745
	mov	r7, #1
	b	.L2466
.L2742:
	ldr	r3, [fp, #-652]
	mov	r1, #4
	ldr	r0, [r3, #2796]
	bl	BsGet
	mov	r4, r0
	b	.L2436
.L2744:
	mov	r0, #7
	mov	r2, r5
	str	r0, [sp]
	mov	r0, #1
	ldr	r1, .L2747+80
	bl	dprint_vfmw
	b	.L2461
.L2469:
	cmp	r4, #0
	beq	.L2461
	ldr	r3, [fp, #-660]
	ldr	r3, [r3, #156]
	cmp	r3, #1
	bls	.L2461
	ldr	r3, [fp, #-648]
	mov	r10, #1
	ldr	r6, [fp, #-652]
	add	r8, r3, #16384
	add	r2, r3, #8320
	add	r8, r8, #232
	str	r9, [fp, #-668]
	mov	r9, r4
	add	r3, r2, #4
	str	r3, [fp, #-672]
.L2495:
	ldr	r2, [fp, #-672]
	ldr	r1, .L2747+84
	ldr	r0, [r6, #2796]
	ldr	r3, [r2, #4]!
	cmp	r3, #2
	subhi	r3, r3, #1
	str	r2, [fp, #-672]
	movls	r3, #1
	str	r3, [fp, #-240]
	bl	HEVC_ue_v
	cmp	r0, #16
	bhi	.L2473
	add	r3, r0, #1
	str	r3, [fp, #-676]
	cmp	r3, #1
	bls	.L2484
	sub	r5, fp, #240
	str	r9, [fp, #-664]
	mov	r9, r8
	add	r3, r5, r0, lsl #2
	str	r3, [fp, #-656]
.L2483:
	ldr	r1, .L2747+88
	mov	r4, r10
	ldr	r0, [r6, #2796]
	mov	r7, #0
	bl	HEVC_ue_v
	ldr	r3, [fp, #-660]
	mov	r8, r0
	ldr	r0, [r3, #148]
	str	r8, [r5, #4]!
	mov	r10, r5
.L2478:
	mov	r5, #0
	mov	r3, r4
	mov	r4, r5
	mov	r5, r3
	b	.L2482
.L2480:
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [fp, #-660]
	ldr	r0, [r3, #148]
.L2482:
	cmp	r0, r5
	mov	r3, r5
	ldr	r2, [fp, #-648]
	mov	r1, #1
	ldrls	r3, [r9]
	addls	r3, r3, #1
	add	r3, r3, #2080
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r4, r3
	add	r4, r4, r1
	bcc	.L2480
	add	r7, r7, r1
	mov	r4, r5
	cmp	r8, r7
	bcs	.L2478
	ldr	r3, [fp, #-656]
	mov	r5, r10
	mov	r10, r4
	cmp	r5, r3
	bne	.L2483
	mov	r8, r9
	ldr	r9, [fp, #-664]
.L2484:
	ldr	r3, [fp, #-676]
	cmp	r3, #0
	beq	.L2476
	ldr	r3, [fp, #-660]
	mov	r4, #1
	str	r8, [fp, #-680]
	mov	r8, r9
	ldr	r1, [r3, #148]
	mov	r3, #0
	str	r3, [fp, #-664]
.L2485:
	mov	r9, r8
	mov	r3, #0
	str	r3, [fp, #-656]
.L2494:
	cmp	r1, r10
	ldr	r2, [fp, #-668]
	ldrls	r3, [fp, #-680]
	movhi	r3, r10
	ldrls	r3, [r3]
	addls	r3, r3, #1
	add	r3, r3, #2064
	add	r3, r3, #8
	add	r3, r2, r3, lsl #2
	ldr	r2, [fp, #-656]
	ldr	r3, [r3, #136]
	cmp	r2, r3
	bhi	.L2746
	ldr	r1, .L2747+92
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	cmp	r0, #31
	bhi	.L2486
	add	r2, r0, #1
	str	r2, [fp, #-684]
	ldr	r2, [fp, #-664]
	sub	r3, fp, #240
	mov	r8, #0
	ldr	r7, [r3, r2, asl #2]
.L2487:
	mov	r5, #0
.L2490:
	cmp	r9, #1
	ldr	r0, [r6, #2796]
	bls	.L2525
	mov	r3, #0
.L2489:
	add	r3, r3, #1
	cmp	r9, r4, asl r3
	mov	r1, r3
	bhi	.L2489
.L2488:
	bl	BsGet
	add	r5, r5, #1
	ldr	r1, .L2747+96
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	cmp	r5, r7
	bls	.L2490
	ldr	r3, [fp, #-684]
	add	r8, r8, #1
	cmp	r8, r3
	bne	.L2487
	ldr	r3, [fp, #-660]
	ldr	r1, [r3, #148]
	ldr	r3, [fp, #-656]
	add	r3, r3, #1
	str	r3, [fp, #-656]
	b	.L2494
.L2525:
	mov	r1, #0
	b	.L2488
.L2486:
	ldr	r2, [fp, #-656]
	str	r0, [sp, #4]
	mov	r0, #1
	ldr	r3, [fp, #-664]
	str	r2, [sp]
	mov	r2, r10
	ldr	r1, .L2747+100
	ldr	r9, [fp, #-668]
	bl	dprint_vfmw
.L2477:
	ldr	r1, .L2747+104
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2461
.L2746:
	ldr	r3, [fp, #-664]
	mov	r8, r9
	ldr	r2, [fp, #-676]
	add	r3, r3, #1
	str	r3, [fp, #-664]
	cmp	r3, r2
	bne	.L2485
	ldr	r8, [fp, #-680]
.L2476:
	ldr	r3, [fp, #-660]
	add	r10, r10, #1
	add	r8, r8, #4
	ldr	r3, [r3, #156]
	cmp	r10, r3
	bcc	.L2495
	ldr	r9, [fp, #-668]
	b	.L2461
.L2731:
	ldr	r3, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r3, #2796]
	bl	BsGet
	ldr	r3, [fp, #-648]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	uxtb	r2, r0
	bgt	.L2501
	b	.L2383
.L2737:
	ldr	r4, [fp, #-652]
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L2425
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L2425
.L2726:
	mov	r2, r1
	mov	r4, #0
.L2503:
	str	r2, [sp, #12]
	movw	r3, #1665
	str	r1, [sp]
	movw	r2, #1025
	str	r4, [sp, #8]
	mov	r0, #1
	str	r2, [sp, #4]
	ldr	r1, .L2747+108
	ldr	r2, .L2747+124
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2473:
	mov	r3, r0
	mov	r2, r10
	mov	r0, #16
	ldr	r1, .L2747+112
	str	r0, [sp]
	mov	r0, #1
	ldr	r9, [fp, #-668]
	bl	dprint_vfmw
	b	.L2477
.L2462:
	mov	r2, r4
	mov	r3, #1024
	ldr	r1, .L2747+116
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2461
.L2721:
	str	r0, [sp]
	mov	r2, #1024
	movw	r3, #1567
	str	r2, [sp, #4]
	ldr	r1, .L2747+120
	mov	r0, #1
	ldr	r2, .L2747+124
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2719:
	ldr	r3, [fp, #-656]
	cmp	r3, #0
	movgt	r7, #1
	bgt	.L2265
	b	.L2264
.L2515:
	mov	r1, #0
	b	.L2334
.L2717:
	add	r9, r3, #12288
	b	.L2253
.L2716:
	ldr	r3, [fp, #-648]
	mov	r2, r4
	sub	r1, fp, #616
	ldr	r0, [fp, #-652]
	ldr	r3, [r3, #12]
	bl	HEVC_DecPTL
	b	.L2230
.L2500:
	ldr	r1, .L2749
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2750:
	.align	2
.L2749:
	.word	.LC204
	UNWIND(.fnend)
	.size	HEVC_ParseVPSExtension, .-HEVC_ParseVPSExtension
	.align	2
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	mov	r5, r0
	mov	r10, r1
	ldr	r0, [r0, #2796]
	mov	r1, #1
	bl	BsGet
	mov	r1, #1
	strb	r0, [r10, #3]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r2, r0
	cmp	r2, #1
	beq	.L2752
	ldr	r1, .L2817
	mov	r0, #1
	bl	dprint_vfmw
.L2752:
	mov	r1, #6
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #63
	str	r0, [r10, #8]
	bhi	.L2806
	mov	r1, #3
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #7
	str	r0, [fp, #-104]
	bhi	.L2807
	ldr	r3, [fp, #-104]
	mov	r1, #1
	str	r3, [r10, #12]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r10, #1]
	ldr	r0, [r5, #2796]
	bl	BsGet
	movw	r3, #65535
	cmp	r0, r3
	bne	.L2808
	ldr	r3, [fp, #-104]
	mov	r2, #1
	add	r1, r10, #124
	mov	r0, r5
	bl	HEVC_DecPTL
	subs	r4, r0, #0
	bne	.L2809
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldr	r3, [fp, #-104]
	cmp	r3, #0
	addge	r6, r10, #24
	ldrge	r3, [fp, #-104]
	addge	r7, r3, #1
	uxtb	r8, r0
	bge	.L2764
	b	.L2762
.L2761:
	add	r4, r4, #1
	cmp	r4, r7
	beq	.L2762
.L2764:
	ldr	r1, .L2817+4
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2817+8
	add	r0, r0, #1
	str	r0, [r6, #4]!
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2817+12
	str	r0, [r6, #32]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r8, #0
	str	r0, [r6, #64]
	bne	.L2761
	ldr	r3, [fp, #-104]
	add	r2, r4, #1
	cmp	r3, r2
	blt	.L2762
	add	r3, r4, #7
	add	r3, r10, r3, lsl #2
.L2763:
	ldr	r1, [r10, #28]
	add	r2, r2, #1
	cmp	r2, r7
	str	r1, [r3, #4]!
	ldr	r1, [r10, #60]
	str	r1, [r3, #32]
	ldr	r1, [r10, #92]
	str	r1, [r3, #64]
	bne	.L2763
.L2762:
	mov	r1, #6
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #1
	str	r0, [r10, #16]
	bhi	.L2810
	ldr	r3, [r10, #8]
	adds	r0, r0, #0
	sub	r3, r3, #1
	movne	r0, #1
	cmp	r3, #61
	movhi	r0, #0
	cmp	r0, #0
	bne	.L2811
.L2765:
	ldr	r1, .L2817+16
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r10, #20]
	bcs	.L2812
	ldr	r4, .L2817+20
	add	r8, r10, #8320
	add	r8, r8, #4
	mov	r2, #8192
	mov	r1, #0
	add	r0, r10, #132
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r0, r8
	mov	r2, #4096
	mov	r1, #0
	blx	r3
	ldr	r3, [r10, #20]
	cmp	r3, #0
	ble	.L2767
	mov	r7, #1
.L2768:
	mov	r4, #0
	mov	r6, r7, asl #1
	mov	r9, r4
.L2770:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	add	ip, r6, r9
	add	ip, r10, ip, lsl #2
	tst	r0, #255
	strne	r4, [ip, #132]
	ldr	r2, [r10, #16]
	add	r4, r4, #1
	addne	r9, r9, #1
	cmp	r4, r2
	bls	.L2770
	str	r9, [r8, #4]!
	add	r7, r7, #1
	ldr	r3, [r10, #20]
	cmp	r7, r3
	ble	.L2768
.L2767:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2777
	mov	r1, #32
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2813
.L2774:
	ldr	r1, .L2817+24
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r10, #24]
	bhi	.L2775
	cmp	r0, #0
	ble	.L2777
	ldr	r1, .L2817+28
	mov	r4, #0
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	mov	r0, #1
.L2786:
	uxtb	r2, r0
	sub	r1, fp, #100
	ldr	r3, [fp, #-104]
	mov	r0, r5
	bl	HEVC_DecHrdParam
	add	r4, r4, #1
	ldr	r1, .L2817+28
	cmp	r0, #0
	bne	.L2814
	ldr	r3, [r10, #24]
	cmp	r3, r4
	ble	.L2777
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r4, #0
	mov	r0, #1
	beq	.L2786
	mov	r1, r0
	ldr	r0, [r5, #2796]
	bl	BsGet
	b	.L2786
.L2777:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2773
	ldrb	r4, [r5, #1]	@ zero_extendqisi2
	cmp	r4, #1
	bne	.L2782
	b	.L2815
.L2785:
	ldr	r0, [r5, #2796]
	bl	BsGet
.L2782:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2785
.L2773:
	mov	r0, #0
.L2803:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2814:
	ldr	r1, .L2817+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2813:
	ldr	r1, .L2817+36
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	b	.L2774
.L2811:
	ldr	r1, .L2817+40
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, #1
	strb	r3, [r5, #1]
	b	.L2765
.L2808:
	ldr	r1, .L2817+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2815:
	ldr	r0, [r5, #2796]
	bl	BsToNextByte
	mov	r1, r10
	mov	r0, r5
	bl	HEVC_ParseVPSExtension
	cmp	r0, #0
	bne	.L2816
	mov	r1, r4
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2773
	b	.L2782
.L2807:
	mov	r2, r0
	ldr	r1, .L2817+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2806:
	mov	r2, r0
	ldr	r1, .L2817+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2809:
	ldr	r1, .L2817+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2812:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2817+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2810:
	mov	r2, #1
	ldr	r1, .L2817+64
	mov	r0, r2
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2775:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L2817+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2816:
	mov	r0, r4
	ldr	r1, .L2817+72
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2803
.L2818:
	.align	2
.L2817:
	.word	.LC229
	.word	.LC234
	.word	.LC235
	.word	.LC236
	.word	.LC239
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC242
	.word	.LC244
	.word	.LC245
	.word	.LC241
	.word	.LC238
	.word	.LC232
	.word	.LC231
	.word	.LC230
	.word	.LC233
	.word	.LC240
	.word	.LC237
	.word	.LC243
	.word	.LC246
	UNWIND(.fnend)
	.size	HEVC_ProcessVPS, .-HEVC_ProcessVPS
	.align	2
	.global	HEVC_DecVPS
	.type	HEVC_DecVPS, %function
HEVC_DecVPS:
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
	mov	r1, #4
	mov	r4, r0
	ldr	r0, [r0, #2796]
	bl	BsGet
	cmp	r0, #15
	mov	r6, r0
	bhi	.L2825
	movw	r7, #24912
	ldr	r3, [r4, #2800]
	mul	r5, r7, r0
	add	r2, r3, r5
	ldrb	r9, [r3, r5]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L2826
	str	r0, [r2, #4]
	mov	r0, r4
	ldr	r1, [r4, #2800]
	add	r1, r1, r5
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L2827
	ldr	r3, [r4, #2800]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2800]
	strb	r2, [r3, r5]
.L2821:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2826:
	ldr	r10, .L2829
	mov	r2, r7
	ldr	r9, .L2829+4
	mov	r1, #0
	ldr	r0, .L2829+8
	ldr	r3, [r10, #48]
	blx	r3
	ldr	r1, .L2829+8
	mov	r0, r4
	str	r6, [r9, #-3460]
	bl	HEVC_ProcessVPS
	subs	r8, r0, #0
	bne	.L2828
	ldr	r0, [r4, #2800]
	mov	r3, #1
	mov	r2, r7
	ldr	ip, [r10, #56]
	add	r0, r0, r5
	strb	r3, [r9, #-3462]
	strb	r3, [r9, #-3464]
	ldr	r1, .L2829+8
	blx	ip
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2828:
	mov	r2, r6
	ldr	r1, .L2829+12
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L2821
.L2825:
	ldr	r1, .L2829+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L2821
.L2827:
	mov	r2, r6
	ldr	r1, .L2829+20
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2800]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2800]
	strb	r9, [r3, r5]
	b	.L2821
.L2830:
	.align	2
.L2829:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR5
	.word	.LANCHOR5-3464
	.word	.LC248
	.word	.LC247
	.word	.LC249
	UNWIND(.fnend)
	.size	HEVC_DecVPS, .-HEVC_DecVPS
	.align	2
	.global	HEVC_DecVuiParam
	.type	HEVC_DecVuiParam, %function
HEVC_DecVuiParam:
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
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #2796]
	mov	r1, #1
	mov	r6, r2
	bl	BsGet
	tst	r0, #255
	bne	.L2875
.L2833:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2876
.L2835:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2877
.L2837:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2878
.L2839:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2840
	ldr	r1, .L2884
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r6, #60]
	cmp	r3, #3
	bhi	.L2879
	ldr	r1, .L2884+4
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2884+8
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2884+12
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
.L2840:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2843
	mov	r1, #32
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #32
	str	r0, [r5, #36]
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r2, [r5, #36]
	cmp	r2, #0
	str	r0, [r5, #40]
	bne	.L2880
.L2844:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2881
.L2845:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L2882
.L2843:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r1, .L2884+16
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r0, #4096
	bcs	.L2883
.L2846:
	ldr	r1, .L2884+20
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2884+24
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2884+28
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2796]
	ldr	r1, .L2884+32
	bl	HEVC_ue_v
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2875:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r5, #8]
	bne	.L2833
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	str	r0, [r5, #12]
	ldr	r0, [r4, #2796]
	bl	BsGet
	str	r0, [r5, #16]
	b	.L2833
.L2878:
	ldr	r1, .L2884+36
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L2884+40
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	b	.L2839
.L2877:
	mov	r1, #3
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #20]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5]
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L2837
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #24]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #28]
	ldr	r0, [r4, #2796]
	bl	BsGet
	str	r0, [r5, #32]
	b	.L2837
.L2876:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L2835
.L2882:
	ldr	r3, [r6, #52]
	add	r1, r5, #44
	mov	r2, #1
	mov	r0, r4
	bl	HEVC_DecHrdParam
	cmp	r0, #0
	beq	.L2843
	ldr	r1, .L2884+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2881:
	ldr	r1, .L2884+48
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	b	.L2845
.L2880:
	ldr	r3, .L2884+52
	movw	r1, #10000
	umull	r0, r1, r0, r1
	ldr	r3, [r3, #236]
	blx	r3
	movw	r3, #52429
	movt	r3, 52428
	add	r0, r0, #5
	umull	r0, r1, r0, r3
	mov	r3, r1, lsr #3
	str	r3, [r4, #144]
	b	.L2844
.L2883:
	ldr	r1, .L2884+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2846
.L2879:
	ldr	r1, .L2884+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2885:
	.align	2
.L2884:
	.word	.LC252
	.word	.LC254
	.word	.LC255
	.word	.LC256
	.word	.LC259
	.word	.LC261
	.word	.LC262
	.word	.LC263
	.word	.LC264
	.word	.LC250
	.word	.LC251
	.word	.LC258
	.word	.LC257
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC260
	.word	.LC253
	UNWIND(.fnend)
	.size	HEVC_DecVuiParam, .-HEVC_DecVuiParam
	.align	2
	.global	HEVC_se_v
	.type	HEVC_se_v, %function
HEVC_se_v:
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
	mov	r1, #32
	mov	r5, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	bls	.L2891
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2891:
	add	r6, r0, #1
	mov	r1, r0
	mov	r0, r5
	bl	BsSkip
	mov	r1, r6
	mov	r0, r5
	bl	BsShow
	mov	r1, r6
	sub	r0, r0, #1
	tst	r0, #1
	mov	r3, r0, asr #1
	mov	r0, r5
	addne	r4, r3, #1
	rsbeq	r4, r3, #0
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_se_v, .-HEVC_se_v
	.align	2
	.global	HEVC_Sei_Structure_Of_Pictures_Info
	.type	HEVC_Sei_Structure_Of_Pictures_Info, %function
HEVC_Sei_Structure_Of_Pictures_Info:
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
	ldr	r1, .L2904
	mov	r6, r0
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	ldr	r0, [r6, #2796]
	ldr	r1, .L2904+4
	bl	HEVC_ue_v
	cmp	r0, #1024
	mov	r7, r0
	bhi	.L2893
	cmp	r0, #0
	movne	r4, #0
	beq	.L2899
.L2898:
	mov	r1, #6
	ldr	r0, [r6, #2796]
	bl	BsGet
	mov	r1, #3
	mov	r5, r0
	ldr	r0, [r6, #2796]
	sub	r5, r5, #19
	bl	BsGet
	cmp	r5, #1
	ldr	r1, .L2904+8
	bls	.L2896
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
.L2896:
	cmp	r4, #0
	ldr	r1, .L2904+12
	add	r4, r4, #1
	beq	.L2897
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
.L2897:
	cmp	r4, r7
	bne	.L2898
.L2899:
	ldr	r0, [r6, #2796]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2893:
	ldr	r1, .L2904+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2905:
	.align	2
.L2904:
	.word	.LC265
	.word	.LC266
	.word	.LC268
	.word	.LC269
	.word	.LC267
	UNWIND(.fnend)
	.size	HEVC_Sei_Structure_Of_Pictures_Info, .-HEVC_Sei_Structure_Of_Pictures_Info
	.align	2
	.global	HEVC_Sei_Recovery_Point
	.type	HEVC_Sei_Recovery_Point, %function
HEVC_Sei_Recovery_Point:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	moveq	r5, #1
	movne	r5, #0
	beq	.L2908
	ldr	r1, .L2909
	ldr	r0, [r0, #2796]
	bl	HEVC_se_v
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r0, [r4, #2796]
	bl	BsToNextByte
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2908:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2910:
	.align	2
.L2909:
	.word	.LC270
	UNWIND(.fnend)
	.size	HEVC_Sei_Recovery_Point, .-HEVC_Sei_Recovery_Point
	.align	2
	.global	HEVC_Sei_Color_Remapping_Info
	.type	HEVC_Sei_Color_Remapping_Info, %function
HEVC_Sei_Color_Remapping_Info:
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
	cmp	r1, #0
	cmpne	r0, #0
	mov	r4, r0
	mov	r8, r1
	beq	.L2927
	ldr	r1, .L2939
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L2913
.L2925:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2913:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r1, r0
	cmp	r1, #1
	beq	.L2937
.L2914:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2796]
	mov	r7, #3
	bl	BsGet
.L2916:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	beq	.L2919
	add	r6, r0, #1
	mov	r5, #0
.L2918:
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r5, r6
	bne	.L2918
.L2919:
	subs	r7, r7, #1
	bne	.L2916
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L2938
.L2920:
	add	r10, r8, #42
	add	r7, r8, #39
	mov	r9, r10
.L2924:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #1]!
	cmp	r0, #0
	beq	.L2926
	mov	r6, r9
	mov	r5, #0
.L2923:
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #16
	add	r5, r5, #1
	strh	r0, [r6, #2]!	@ movhi
	ldr	r0, [r4, #2796]
	bl	BsGet
	strh	r0, [r6, #198]	@ movhi
	ldrb	r3, [r7]	@ zero_extendqisi2
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L2923
.L2926:
	cmp	r7, r10
	add	r9, r9, #66
	bne	.L2924
	b	.L2925
.L2927:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2938:
	mov	r1, #4
	ldr	r0, [r4, #2796]
	bl	BsGet
	add	r7, r8, #36
	mov	r5, r8
.L2921:
	add	r6, r5, #12
.L2922:
	ldr	r1, .L2939+4
	ldr	r0, [r4, #2796]
	bl	HEVC_se_v
	str	r0, [r5, #4]!
	cmp	r5, r6
	bne	.L2922
	cmp	r7, r5
	bne	.L2921
	b	.L2920
.L2937:
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r8, #1]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L2914
.L2940:
	.align	2
.L2939:
	.word	.LC271
	.word	.LC272
	UNWIND(.fnend)
	.size	HEVC_Sei_Color_Remapping_Info, .-HEVC_Sei_Color_Remapping_Info
	.align	2
	.global	HEVC_Sei_Payload
	.type	HEVC_Sei_Payload, %function
HEVC_Sei_Payload:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	ip, [r0, #2816]
	mov	r4, r0
	ldr	r6, [fp, #4]
	ldr	ip, [ip, #16]
	cmp	ip, #39
	beq	.L2987
	cmp	r3, #5
	beq	.L2970
	cmp	r3, #132
	beq	.L2971
	cmp	r6, #0
	movne	r5, #0
	beq	.L2964
.L2973:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r5, r6
	bne	.L2973
	b	.L2964
.L2970:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	bne	.L2967
.L2964:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_More_Data_In_Payload
	cmp	r0, #0
	bne	.L2974
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2974:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_Payload_Extension_Present
	cmp	r0, #0
	bne	.L2988
.L2975:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L2976
.L2977:
	ldr	r0, [r4, #2796]
	bl	BsGet
.L2976:
	ldr	r0, [r4, #2796]
	bl	BsIsByteAligned
	mov	r1, #1
	cmp	r0, #0
	beq	.L2977
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2987:
	cmp	r3, #147
	ldrls	pc, [pc, r3, asl #2]
	b	.L2943
.L2945:
	.word	.L2944
	.word	.L2946
	.word	.L2943
	.word	.L2943
	.word	.L2947
	.word	.L2948
	.word	.L2949
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2950
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2951
	.word	.L2943
	.word	.L2952
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2953
	.word	.L2954
	.word	.L2955
	.word	.L2956
	.word	.L2943
	.word	.L2957
	.word	.L2958
	.word	.L2943
	.word	.L2943
	.word	.L2959
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2943
	.word	.L2960
	.word	.L2943
	.word	.L2961
	.word	.L2943
	.word	.L2943
	.word	.L2962
.L2971:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Decoded_Picture_Hash
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2988:
	ldr	r1, .L2989
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	b	.L2975
.L2962:
	add	r1, r1, #616
	add	r1, r1, #2
	bl	HEVC_Sei_HLGHDR_Comapitibility_Info
	cmp	r0, #0
	beq	.L2964
.L2967:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2944:
	add	r2, r2, #2096
	add	r2, r2, #12
	bl	HEVC_Sei_Buf_Period
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2946:
	add	r2, r2, #2064
	add	r1, r1, #8
	bl	HEVC_Sei_Pic_Timming
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2947:
	add	r1, r1, #56
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2948:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2949:
	add	r1, r1, #568
	bl	HEVC_Sei_Recovery_Point
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2950:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Tone_Mapping_Info
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2951:
	add	r1, r1, #568
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2952:
	add	r1, r1, #568
	bl	HEVC_Sei_Display_Orientation
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2953:
	add	r1, r1, #616
	mov	r2, r6
	add	r1, r1, #3
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2954:
	add	r1, r1, #568
	bl	HEVC_Sei_Active_Param_sets
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2955:
	add	r2, r2, #2096
	add	r1, r1, #568
	add	r2, r2, #12
	bl	HEVC_Sei_Dec_Unit_Info
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2956:
	add	r1, r1, #568
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2957:
	mov	r3, r6
	bl	HEVC_Sei_Scalable_Nesting
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2958:
	cmn	r1, #568
	cmpne	r0, #0
	beq	.L2967
	mov	r1, #1
	ldr	r0, [r0, #2796]
	bl	BsGet
	b	.L2964
.L2959:
	add	r1, r1, #568
	bl	HEVC_Sei_Mastering_Display_Colour_Volume
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2960:
	add	r1, r1, #128
	bl	HEVC_Sei_Color_Remapping_Info
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2961:
	add	r1, r1, #612
	bl	HEVC_Sei_Content_Light_Level_Information
	cmp	r0, #0
	beq	.L2964
	b	.L2967
.L2943:
	cmp	r6, #0
	movne	r5, #0
	beq	.L2964
.L2968:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r5, r6
	bne	.L2968
	b	.L2964
.L2990:
	.align	2
.L2989:
	.word	.LC273
	UNWIND(.fnend)
	.size	HEVC_Sei_Payload, .-HEVC_Sei_Payload
	.align	2
	.global	HEVC_SeiMessage
	.type	HEVC_SeiMessage, %function
HEVC_SeiMessage:
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
	mov	r5, #0
	mov	r4, r0
	mov	r6, r1
	mov	r7, r2
	ldr	r0, [r0, #2796]
	b	.L2992
.L2994:
	bl	BsSkip
	ldr	r0, [r4, #2796]
	add	r5, r5, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2
	bhi	.L3000
.L2992:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2796]
	beq	.L2994
	bl	BsGet
	mov	r8, #0
	mov	r9, r0
	ldr	r0, [r4, #2796]
	b	.L2995
.L2996:
	bl	BsSkip
	ldr	r0, [r4, #2796]
	add	r8, r8, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2
	bhi	.L3001
.L2995:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2796]
	beq	.L2996
	bl	BsGet
	add	r3, r9, r5
	mov	r2, r7
	mov	r1, r6
	add	r8, r0, r8
	mov	r0, r4
	str	r8, [sp]
	bl	HEVC_Sei_Payload
	cmp	r0, #0
	bne	.L3002
.L2993:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3000:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5022
	ldr	r1, .L3003
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3001:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5043
	ldr	r1, .L3003
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3002:
	ldr	r1, .L3003+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2993
.L3004:
	.align	2
.L3003:
	.word	.LC274
	.word	.LC275
	UNWIND(.fnend)
	.size	HEVC_SeiMessage, .-HEVC_SeiMessage
	.align	2
	.global	HEVC_DecSEI
	.type	HEVC_DecSEI, %function
HEVC_DecSEI:
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
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #1
	beq	.L3011
	ldr	r5, [r0, #2812]
	add	r6, r0, #3472
	cmp	r5, #0
	bne	.L3014
	b	.L3017
.L3009:
	ldr	r0, [r4, #2796]
	bl	BsIsByteAligned
	cmp	r0, #0
	mov	r0, r4
	beq	.L3018
	bl	HEVC_More_Rbsp_Data
	cmp	r0, #0
	beq	.L3019
.L3014:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	beq	.L3009
	ldr	r1, .L3021
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3019:
	ldr	r0, [r4, #2796]
	mov	r1, #8
	bl	BsGet
	cmp	r0, #128
	bne	.L3020
.L3011:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3018:
	ldr	r1, .L3021+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3020:
	mov	r2, r0
	ldr	r1, .L3021+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3017:
	ldr	r1, .L3021+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3022:
	.align	2
.L3021:
	.word	.LC277
	.word	.LC278
	.word	.LC279
	.word	.LC276
	UNWIND(.fnend)
	.size	HEVC_DecSEI, .-HEVC_DecSEI
	.align	2
	.global	HEVC_Sei_Scalable_Nesting
	.type	HEVC_Sei_Scalable_Nesting, %function
HEVC_Sei_Scalable_Nesting:
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
	mov	r4, r0
	mov	r6, r1
	ldr	r0, [r0, #2796]
	mov	r1, #1
	mov	r7, r2
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	tst	r0, #255
	ldr	r0, [r4, #2796]
	beq	.L3024
	bl	BsGet
	ldr	r1, .L3040
	mov	r5, r0
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r0, #63
	mov	r8, r0
	bhi	.L3037
	uxtb	r5, r5
	cmp	r0, r5
	bcc	.L3030
.L3029:
	mov	r1, #3
	ldr	r0, [r4, #2796]
	bl	BsGet
	add	r5, r5, #1
	ldr	r1, .L3040+4
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r8, r5
	bcs	.L3029
.L3030:
	ldr	r0, [r4, #2796]
	bl	BsToNextByte
	b	.L3028
.L3033:
	bl	HEVC_MoreRbspData
	cmp	r0, #0
	beq	.L3038
.L3028:
	mov	r2, r7
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	mov	r0, r4
	beq	.L3033
	ldr	r1, .L3040+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3024:
	bl	BsGet
	uxtb	r5, r0
	cmp	r5, #0
	bne	.L3030
	mov	r1, #3
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r1, .L3040+12
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r0, #63
	addls	r8, r0, #1
	bhi	.L3039
.L3032:
	add	r5, r5, #1
	mov	r1, #6
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r5, r8
	bne	.L3032
	b	.L3030
.L3038:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3037:
	mov	r2, #64
	ldr	r1, .L3040+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3039:
	ldr	r1, .L3040+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3041:
	.align	2
.L3040:
	.word	.LC280
	.word	.LC282
	.word	.LC277
	.word	.LC283
	.word	.LC281
	.word	.LC284
	UNWIND(.fnend)
	.size	HEVC_Sei_Scalable_Nesting, .-HEVC_Sei_Scalable_Nesting
	.align	2
	.global	HEVC_DecScalingListData
	.type	HEVC_DecScalingListData, %function
HEVC_DecScalingListData:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	r3, .L3080
	mov	r6, r0
	add	r8, r6, #2224
	add	r8, r8, #8
	mov	r4, r1
	str	r1, [fp, #-68]
	mov	r2, #64
	ldr	r3, [r3, #52]
	add	r1, r1, #1216
	add	r0, r4, #1344
	blx	r3
	add	r3, r4, #1536
	str	r4, [fp, #-60]
	str	r3, [fp, #-64]
	mov	r3, #0
	str	r3, [fp, #-52]
.L3043:
	ldr	r3, [r8, #4]!
	cmp	r3, #0
	beq	.L3063
	ldr	r3, [fp, #-64]
	ldr	r7, [fp, #-60]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-48]
.L3062:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r5, [r8, #-1888]
	ldr	r3, [fp, #-52]
	cmp	r5, #64
	movge	r5, #64
	cmp	r3, #0
	uxtb	r0, r0
	beq	.L3044
	cmp	r0, #0
	add	r4, r6, #364
	beq	.L3076
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	bls	.L3069
	ldr	r1, .L3080+4
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #254
	bhi	.L3077
	ldr	r3, [fp, #-56]
	add	r10, r0, #8
	str	r10, [r3]
.L3055:
	cmp	r5, #0
	ble	.L3054
	sub	r4, r4, #4
	mov	r9, #0
	b	.L3059
.L3058:
	mov	r10, r10, lsr #24
	ldr	r2, [r4, #4]!
	add	r3, r3, r10
	cmp	r9, r5
	uxtb	r3, r3
	rsb	r10, r10, r3
	strb	r10, [r7, r2]
	beq	.L3054
.L3059:
	ldr	r1, .L3080+8
	add	r9, r9, #1
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r3, r10, r0
	add	r0, r0, #128
	add	r3, r3, #256
	cmp	r0, #255
	mov	r10, r3, asr #31
	bls	.L3058
	ldr	r1, .L3080+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L3074:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3064:
	ldr	r1, .L3080+16
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	cmp	r0, r3
	bhi	.L3066
	ldr	r3, [fp, #-48]
	rsb	r3, r0, r3
	uxtb	r3, r3
.L3049:
	ldr	r2, [fp, #-48]
	cmp	r3, r2
	beq	.L3078
.L3051:
	ldr	r2, [fp, #-52]
	mov	r1, r2, asl #3
	sub	r1, r1, r2, asl #1
	ldr	r2, [fp, #-68]
	add	r3, r1, r3
	add	r1, r2, r3, lsl #6
.L3052:
	cmp	r1, #0
	beq	.L3079
	ldr	r3, .L3080
	mov	r2, r5
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
.L3054:
	ldr	r3, [fp, #-48]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, #6
	beq	.L3063
	ldr	r2, [fp, #-56]
	add	r7, r7, #64
	ldr	r3, [r8]
	add	r2, r2, #4
	str	r2, [fp, #-56]
	ldr	r2, [fp, #-48]
	cmp	r3, r2
	bhi	.L3062
.L3063:
	ldr	r3, [fp, #-52]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-52]
	cmp	r3, #4
	ldr	r3, [fp, #-64]
	add	r2, r2, #384
	str	r2, [fp, #-60]
	add	r3, r3, #24
	str	r3, [fp, #-64]
	bne	.L3043
	mov	r0, #0
	b	.L3074
.L3069:
	mov	r10, #8
	b	.L3055
.L3076:
	ldr	r1, .L3080+16
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	cmp	r0, r3
	bhi	.L3066
	ldr	r1, [fp, #-48]
	ldr	r2, [fp, #-52]
	rsb	r3, r0, r1
	cmp	r2, #1
	uxtb	r3, r3
	bls	.L3049
	cmp	r1, r3
	movne	r1, r2
	movne	r2, r2, asl #3
	subne	r2, r2, r1, asl #1
	ldrne	r1, [fp, #-68]
	addne	r2, r2, r3
	moveq	r2, #16
	addne	r2, r2, #384
	ldrne	r2, [r1, r2, asl #2]
	ldr	r1, [fp, #-56]
	str	r2, [r1]
	ldr	r2, [fp, #-48]
	cmp	r3, r2
	bne	.L3051
.L3078:
	mov	r1, r2
	ldr	r0, [fp, #-52]
	bl	HEVC_GetScalingListDefaultAddress
	mov	r1, r0
	b	.L3052
.L3077:
	ldr	r1, .L3080+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3074
.L3079:
	ldr	r1, .L3080+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3074
.L3066:
	ldr	r1, .L3080+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3074
.L3044:
	cmp	r0, #0
	beq	.L3064
	ldr	r4, .L3080+32
	mov	r10, #8
	b	.L3055
.L3081:
	.align	2
.L3080:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC288
	.word	.LC290
	.word	.LC291
	.word	.LC285
	.word	.LC289
	.word	.LC287
	.word	.LC286
	.word	.LANCHOR1+65536
	UNWIND(.fnend)
	.size	HEVC_DecScalingListData, .-HEVC_DecScalingListData
	.align	2
	.global	HEVC_ProcessSPS
	.type	HEVC_ProcessSPS, %function
HEVC_ProcessSPS:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r4, r1
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	mov	r5, r0
	cmp	r1, #1
	beq	.L3268
.L3083:
	ldr	r1, .L3296
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #1
	mov	r6, r0
	str	r0, [r4, #60]
	beq	.L3269
	cmp	r6, #3
	bhi	.L3270
	mov	r2, r6
	ldr	r1, .L3296+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L3256:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3270:
	ldr	r1, .L3296+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3268:
	ldr	r3, [r0, #2816]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L3083
	ldrb	r3, [r4, #46]	@ zero_extendqisi2
	cmp	r3, #7
	bne	.L3083
	ldr	r3, [r0, #2800]
	movw	r6, #24912
	ldr	r2, [r4, #48]
	ldr	r0, [r0, #2796]
	mla	r6, r6, r2, r3
	bl	BsGet
	cmp	r0, #0
	bne	.L3271
	ldr	r3, [r5, #2816]
	add	r2, r6, #12288
	ldr	r3, [r3, #24]
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #132]
	add	r3, r3, #1024
	add	r3, r3, #14
	add	r2, r2, r3, lsl #2
	ldr	r0, [r2, #132]
.L3085:
	cmp	r0, #1
	bhi	.L3272
	mov	r3, r0, asl #5
	add	r6, r6, #12288
	add	r0, r3, r0, lsl #3
	movw	r8, #12540
	add	r0, r6, r0
	movw	r9, #12548
	add	r2, r0, #12544
	add	r3, r0, #12480
	add	r2, r2, #4
	add	r3, r3, #60
	movw	r7, #12556
	add	ip, r0, #12544
	ldr	r2, [r2, #4]
	add	ip, ip, #12
	movw	r6, #12564
	add	r1, r0, #12544
	add	r1, r1, #20
	movw	lr, #12572
	str	r2, [r4, #60]
	add	r2, r0, #12544
	ldrb	r8, [r0, r8]	@ zero_extendqisi2
	add	r2, r2, #28
	strb	r8, [r4, #47]
	ldr	r3, [r3, #4]
	str	r3, [r4, #64]
	ldr	r3, [r0, r9]
	str	r3, [r4, #68]
	ldr	r3, [r0, r7]
	add	r3, r3, #8
	str	r3, [r4, #88]
	ldr	ip, [ip, #4]
	add	ip, ip, #8
	str	ip, [r4, #96]
	ldr	ip, [r0, r6]
	str	ip, [r4, #72]
	ldr	r1, [r1, #4]
	str	r1, [r4, #76]
	ldr	r1, [r0, lr]
	str	r1, [r4, #80]
	ldr	r2, [r2, #4]
	str	r2, [r4, #84]
.L3088:
	str	r3, [r5, #196]
	ldr	r3, [r4, #96]
	ldr	r1, .L3296+12
	str	r3, [r5, #200]
	ldr	r0, [r4, #96]
	ldr	ip, [r4, #88]
	mov	r3, r0, asl #3
	mov	r2, ip, asl #3
	sub	r3, r3, r0, asl #1
	sub	r2, r2, ip, asl #1
	sub	r3, r3, #48
	sub	r2, r2, #48
	str	r3, [r4, #100]
	str	r2, [r4, #92]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #12
	bhi	.L3273
	add	r0, r0, #4
	str	r0, [r4, #116]
	str	r0, [r4, #120]
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3274
.L3115:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r9, #0
	mov	r7, r9
	mov	r6, r4
	mov	r8, r0
	b	.L3123
.L3119:
	ldr	r3, [r4, #52]
	add	r7, r7, #1
	add	r6, r6, #4
	cmp	r3, r7
	bcc	.L3122
.L3123:
	ldr	r1, .L3296+16
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L3296+20
	add	r0, r0, #1
	str	r0, [r6, #328]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L3296+24
	str	r0, [r6, #360]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r6, #328]
	cmp	r9, r3
	movcc	r9, r3
	cmp	r8, #0
	str	r0, [r6, #392]
	bne	.L3119
	ldr	r1, [r4, #52]
	add	r3, r7, #1
	cmp	r3, r1
	addls	r7, r7, #82
	addls	r7, r4, r7, lsl #2
	bhi	.L3122
.L3121:
	ldr	r2, [r4, #328]
	add	r3, r3, #1
	cmp	r3, r1
	str	r2, [r7, #4]!
	ldr	r2, [r4, #360]
	str	r2, [r7, #32]
	ldr	r2, [r4, #392]
	str	r2, [r7, #64]
	bls	.L3121
.L3122:
	ldr	r3, [r4, #184]
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r4, #184]
.L3118:
	ldr	r1, .L3296+28
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L3275
	ldr	r1, .L3296+32
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r7, r0
	bhi	.L3276
	add	r3, r6, #3
	str	r3, [r4, #124]
	add	r6, r0, r3
	str	r6, [r4, #128]
	sub	r2, r6, #4
	cmp	r2, #2
	bhi	.L3277
	mov	r2, #1
	ldr	r8, [r4, #64]
	mov	r6, r2, asl r6
	mov	r3, r2, asl r3
	str	r6, [r4, #136]
	str	r6, [r4, #140]
	mov	r1, r6
	str	r6, [r4, #144]
	mov	r0, r8
	str	r3, [r4, #132]
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L3127
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L3128:
	ldr	r8, [r4, #68]
	mov	r1, r6
	str	r0, [r4, #188]
	mov	r0, r8
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L3129
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L3130:
	str	r0, [r4, #192]
	ldr	r1, .L3296+36
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L3278
	ldr	r1, .L3296+40
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #3
	bhi	.L3279
	ldr	r2, [r4, #124]
	add	r3, r6, #2
	str	r3, [r4, #148]
	cmp	r3, r2
	bcs	.L3280
	add	r3, r0, r3
	str	r3, [r4, #152]
	cmp	r3, #5
	bhi	.L3134
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L3134
	ldr	r1, .L3296+44
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r4, #128]
	ldr	r2, [r4, #148]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #164]
	bhi	.L3281
	ldr	r1, .L3296+48
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	ip, [r4, #148]
	ldr	r3, [r4, #128]
	rsb	r3, ip, r3
	cmp	r0, r3
	str	r0, [r4, #168]
	bhi	.L3137
	ldr	r1, [r4, #140]
	mov	r0, #1
	mov	r3, #0
	mov	r1, r1, lsr r7
	cmp	r1, r0, asl ip
	bls	.L3139
.L3140:
	add	r3, r3, #1
	add	r2, r3, ip
	cmp	r1, r0, asl r2
	bhi	.L3140
.L3139:
	add	r3, r3, r7
	mov	r1, #1
	str	r3, [r4, #172]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #0
	beq	.L3144
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L3282
.L3142:
	add	r3, r4, #12288
	mov	r2, #0
	strb	r2, [r3, #372]
.L3175:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #0
	bne	.L3283
.L3144:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #6]
	cmp	r6, #0
	bne	.L3145
	ldr	r2, [r4, #68]
	cmp	r2, #64
	bls	.L3284
.L3145:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #104]
	beq	.L3146
	mov	r1, #4
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #4
	add	r0, r0, #1
	str	r0, [r4, #108]
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldr	r1, .L3296+52
	add	r0, r0, #1
	str	r0, [r4, #112]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r7, r0
	bhi	.L3285
.L3147:
	ldr	r1, .L3296+56
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r6, r0
	bhi	.L3286
.L3148:
	add	r0, r7, #3
	str	r0, [r4, #156]
	add	r0, r6, r0
	str	r0, [r4, #160]
	cmp	r0, #5
	bhi	.L3149
	ldr	r3, [r4, #128]
	cmp	r0, r3
	bhi	.L3149
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	strb	r0, [r4, #7]
.L3146:
	ldr	r1, .L3296+60
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #64
	str	r0, [r4, #176]
	bhi	.L3151
	cmp	r0, #0
	addne	r7, r4, #2160
	movne	r6, #0
	addne	r7, r7, #4
	bne	.L3156
	b	.L3157
.L3155:
	ldr	r3, [r4, #176]
	cmp	r3, r6
	bls	.L3157
.L3156:
	mov	r3, r6
	mov	r2, r7
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_DecShortTermRefPicSet
	add	r6, r6, #1
	add	r7, r7, #164
	cmp	r0, #0
	beq	.L3155
	ldr	r1, .L3296+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3269:
	ldr	r1, .L3296+68
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #8192
	str	r0, [r4, #64]
	bls	.L3090
	ldr	r1, .L3296+72
	mov	r0, r6
.L3261:
	bl	dprint_vfmw
	ldr	r3, .L3296+76
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3259
	mov	r3, #0
	ldr	r0, [r5, #276]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
	b	.L3256
.L3090:
	ldr	r1, .L3296+80
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #4096
	str	r0, [r4, #68]
	bhi	.L3287
	ldr	r2, [r4, #428]
	ldr	r3, [r4, #64]
	cmp	r2, #120
	mul	r0, r3, r0
	beq	.L3095
	bgt	.L3096
	cmp	r2, #60
	beq	.L3097
	ble	.L3288
	cmp	r2, #90
	beq	.L3100
	cmp	r2, #93
	beq	.L3101
	cmp	r2, #63
	beq	.L3289
.L3094:
	ldr	r1, .L3296+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3293:
	ldr	r1, .L3296+88
	mov	r0, #1
	bl	dprint_vfmw
.L3259:
	mvn	r0, #0
	b	.L3256
.L3096:
	cmp	r2, #156
	beq	.L3103
	bgt	.L3104
	cmp	r2, #150
	beq	.L3103
	cmp	r2, #153
	beq	.L3103
	cmp	r2, #123
	bne	.L3094
.L3095:
	mov	r2, #557056
	mov	r3, #2228224
.L3102:
	cmp	r0, r2
	movls	r3, #16
	strls	r3, [r4, #184]
	bls	.L3107
	cmp	r0, r3, lsr #1
	movls	r3, #12
	strls	r3, [r4, #184]
	bls	.L3107
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, lsr #2
	movls	r3, #8
	movhi	r3, #6
	str	r3, [r4, #184]
.L3107:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #0
	beq	.L3110
	ldr	r1, .L3296+92
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r6, .L3296+96
	ldr	r1, .L3296+100
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #620]
	mul	r0, r3, r0
	str	r0, [r4, #72]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r2, [r4, #60]
	ldr	r3, [r4, #64]
	ldr	r1, [r4, #72]
	add	r2, r6, r2, lsl #2
	rsb	r3, r1, r3
	ldr	r2, [r2, #620]
	mul	r0, r2, r0
	rsb	r3, r0, r3
	cmp	r3, #0
	str	r0, [r4, #76]
	blt	.L3290
	ldr	r1, .L3296+104
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r1, .L3296+108
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #636]
	mul	r0, r3, r0
	str	r0, [r4, #80]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, [r4, #60]
	ldr	r2, [r4, #80]
	ldr	r3, [r4, #68]
	add	r6, r6, r1, lsl #2
	rsb	r3, r2, r3
	ldr	r2, [r6, #636]
	mul	r0, r2, r0
	rsb	r3, r0, r3
	cmp	r3, #0
	str	r0, [r4, #84]
	blt	.L3291
.L3110:
	ldr	r1, .L3296+112
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #2
	add	r2, r0, #8
	str	r2, [r4, #88]
	bhi	.L3292
	ldr	r1, .L3296+116
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #6
	add	r2, r0, #8
	str	r2, [r4, #96]
	ldrls	r3, [r4, #88]
	bls	.L3088
	ldr	r1, .L3296+120
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3129:
	bl	__aeabi_uidiv
	b	.L3130
.L3127:
	bl	__aeabi_uidiv
	b	.L3128
.L3274:
	ldr	r3, [r5, #2816]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L3115
	ldrb	r3, [r4, #46]	@ zero_extendqisi2
	cmp	r3, #7
	bne	.L3115
	ldr	r3, [r4, #48]
	movw	ip, #24912
	ldr	r0, [r5, #2800]
	mov	r2, #0
	ldr	r9, [r4, #52]
	add	r8, r4, #324
	add	r7, r4, #356
	add	r6, r4, #388
	mla	r0, ip, r3, r0
	mov	r1, r2
	add	lr, r0, #24
	add	ip, r0, #56
	add	r0, r0, #88
.L3117:
	ldr	r3, [lr, #4]!
	add	r1, r1, #1
	cmp	r2, r3
	str	r3, [r8, #4]!
	ldr	r10, [ip, #4]!
	movcc	r2, r3
	cmp	r1, r9
	str	r10, [r7, #4]!
	ldr	r3, [r0, #4]!
	str	r3, [r6, #4]!
	bls	.L3117
	str	r2, [r4, #184]
	b	.L3118
.L3157:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	beq	.L3154
	ldr	r1, .L3296+124
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #32
	str	r0, [r4, #180]
	bhi	.L3160
	cmp	r0, #0
	addne	r8, r4, #192
	addne	r7, r4, #12
	movne	r6, #0
	beq	.L3154
.L3162:
	ldr	r1, [r4, #116]
	add	r6, r6, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2796]
	bl	BsGet
	strb	r0, [r7, #1]!
	ldr	r3, [r4, #180]
	cmp	r3, r6
	bhi	.L3162
.L3154:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #11]
	cmp	r0, #0
	beq	.L3159
	mov	r2, r4
	add	r1, r4, #2064
	mov	r0, r5
	bl	HEVC_DecVuiParam
	cmp	r0, #0
	bne	.L3293
.L3159:
	ldr	ip, [r4, #68]
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #2080]
	ldr	r1, [r4, #2076]
	ldr	r0, [r4, #2072]
	str	ip, [sp]
	bl	HEVC_GetDar
	str	r0, [r4, #2068]
	ldrb	r6, [r5, #1]	@ zero_extendqisi2
	cmp	r6, #1
	movne	r3, #1
	movne	r0, #0
	strneb	r3, [r4]
	bne	.L3256
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r0, #255
	bne	.L3164
.L3168:
	mov	r0, #0
	b	.L3256
.L3271:
	mov	r1, #8
	ldr	r0, [r5, #2796]
	bl	BsGet
	b	.L3085
.L3284:
	ldr	r1, .L3296+128
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3296+76
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3259
	ldr	r0, [r5, #276]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
	mvn	r0, #0
	b	.L3256
.L3282:
	ldr	r3, [r5, #2816]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L3142
	ldrb	r3, [r4, #46]	@ zero_extendqisi2
	cmp	r3, #7
	bne	.L3142
	ldr	r0, [r5, #2796]
	add	r6, r4, #12288
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r6, #372]
	cmp	r0, #0
	beq	.L3175
	mov	r1, #6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r3, #0
	str	r0, [r6, #376]
	strb	r3, [r4, #4]
	b	.L3144
.L3134:
	ldr	r1, .L3296+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3287:
	mov	r0, r6
	ldr	r1, .L3296+136
	b	.L3261
.L3286:
	mov	r2, r0
	ldr	r1, .L3296+140
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3148
.L3285:
	mov	r2, r0
	ldr	r1, .L3296+144
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3147
.L3283:
	add	r1, r4, #432
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	beq	.L3144
	ldr	r1, .L3296+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3292:
	ldr	r1, .L3296+152
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3296+76
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3259
	ldr	r1, [r4, #88]
	mov	r2, #0
	ldr	r0, [r5, #276]
	mov	r3, #8
	str	r2, [fp, #-52]
	sub	r2, fp, #52
	str	r1, [fp, #-48]
	mov	r1, #119
	blx	ip
	mvn	r0, #0
	b	.L3256
.L3275:
	ldr	r1, .L3296+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3272:
	mov	r2, #1
	ldr	r1, .L3296+160
	mov	r0, r2
	bl	dprint_vfmw
	ldr	r1, .L3296+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3278:
	ldr	r1, .L3296+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3104:
	cmp	r2, #183
	beq	.L3105
	cmp	r2, #186
	beq	.L3105
	cmp	r2, #180
	bne	.L3094
.L3105:
	mov	r2, #8912896
	mov	r3, #35651584
	b	.L3102
.L3288:
	cmp	r2, #0
	beq	.L3099
	cmp	r2, #30
	bne	.L3094
.L3099:
	mov	r2, #9216
	mov	r3, #36864
	b	.L3102
.L3281:
	ldr	r1, .L3296+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3149:
	ldr	r1, .L3296+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3101:
	mov	r2, #245760
	mov	r3, #983040
	b	.L3102
.L3100:
	mov	r2, #138240
	mov	r3, #552960
	b	.L3102
.L3103:
	mov	r2, #2228224
	mov	r3, #8912896
	b	.L3102
.L3097:
	mov	r2, #30720
	mov	r3, #122880
	b	.L3102
.L3289:
	mov	r2, #61440
	mov	r3, #245760
	b	.L3102
.L3273:
	ldr	r1, .L3296+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3276:
	ldr	r1, .L3296+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3277:
	ldr	r1, .L3296+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3280:
	ldr	r1, .L3296+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3279:
	ldr	r1, .L3296+196
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3137:
	ldr	r1, .L3296+200
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3164:
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	mov	r4, r0
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	uxtb	r7, r0
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r4, #255
	uxtb	r4, r0
	bne	.L3294
.L3165:
	cmp	r7, #0
	bne	.L3295
.L3166:
	cmp	r4, #0
	bne	.L3255
	b	.L3168
.L3169:
	ldr	r0, [r5, #2796]
	bl	BsGet
.L3255:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L3169
	b	.L3168
.L3151:
	mov	r2, #64
	ldr	r1, .L3296+204
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3295:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	b	.L3166
.L3294:
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	b	.L3165
.L3160:
	ldr	r1, .L3296+208
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3290:
	ldr	r1, .L3296+212
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3291:
	ldr	r1, .L3296+216
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3256
.L3297:
	.align	2
.L3296:
	.word	.LC344
	.word	.LC295
	.word	.LC294
	.word	.LC311
	.word	.LC313
	.word	.LC314
	.word	.LC315
	.word	.LC316
	.word	.LC318
	.word	.LC321
	.word	.LC323
	.word	.LC327
	.word	.LC329
	.word	.LC333
	.word	.LC335
	.word	.LC338
	.word	.LC340
	.word	.LC296
	.word	.LC297
	.word	g_event_report
	.word	.LC298
	.word	.LC300
	.word	.LC343
	.word	.LC301
	.word	.LANCHOR0
	.word	.LC302
	.word	.LC304
	.word	.LC305
	.word	.LC307
	.word	.LC309
	.word	.LC310
	.word	.LC341
	.word	.LC332
	.word	.LC326
	.word	.LC299
	.word	.LC336
	.word	.LC334
	.word	.LC331
	.word	.LC308
	.word	.LC317
	.word	.LC292
	.word	.LC293
	.word	.LC322
	.word	.LC328
	.word	.LC337
	.word	.LC312
	.word	.LC319
	.word	.LC320
	.word	.LC325
	.word	.LC324
	.word	.LC330
	.word	.LC339
	.word	.LC342
	.word	.LC303
	.word	.LC306
	UNWIND(.fnend)
	.size	HEVC_ProcessSPS, .-HEVC_ProcessSPS
	.align	2
	.global	HEVC_DecSPS
	.type	HEVC_DecSPS, %function
HEVC_DecSPS:
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
	ldr	r9, .L3326
	mov	r4, r0
	mov	r2, #8
	mov	r1, #0
	sub	r0, fp, #60
	ldr	r3, [r9, #48]
	blx	r3
	ldr	r0, [r4, #2796]
	mov	r1, #4
	bl	BsGet
	ldr	r2, [r4, #156]
	cmp	r2, r0
	mov	r10, r0
	bls	.L3319
	ldr	r3, [r4, #2816]
	mov	r1, #3
	ldr	r0, [r4, #2796]
	ldr	r6, [r3, #24]
	cmp	r6, #0
	beq	.L3320
	bl	BsGet
	uxtb	r6, r0
	cmp	r6, #7
	movne	r8, r6
	beq	.L3321
.L3304:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r3, r8
	mov	r2, #1
	sub	r1, fp, #60
	uxtb	r0, r0
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	HEVC_DecPTL
	cmp	r0, #0
	bne	.L3322
.L3305:
	ldr	r1, .L3326+4
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r2, [r4, #160]
	cmp	r0, r2
	mov	r7, r0
	bcs	.L3323
	movw	ip, #12668
	ldr	r2, [r4, #2804]
	mul	r5, ip, r0
	add	r2, r2, r5
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3307
	ldr	r3, .L3326+8
	mov	r2, ip
	mov	r1, #0
	ldr	r0, .L3326+12
	str	ip, [fp, #-68]
	str	r3, [fp, #-72]
	ldr	r3, [r9, #48]
	blx	r3
	ldr	r3, [fp, #-72]
	ldrb	r2, [fp, #-64]	@ zero_extendqisi2
	sub	r1, fp, #60
	sub	r0, r3, #3040
	ldr	r9, [r9, #52]
	strb	r6, [r3, #-3418]
	strb	r2, [r3, #-3462]
	mov	r2, #8
	str	r10, [r3, #-3416]
	str	r8, [r3, #-3412]
	str	r3, [fp, #-64]
	blx	r9
	ldr	r3, [fp, #-64]
	mov	r0, r4
	ldr	r1, .L3326+12
	str	r7, [r3, #-3408]
	bl	HEVC_ProcessSPS
	ldr	r1, .L3326
	ldr	r3, [fp, #-64]
	ldr	ip, [fp, #-68]
	subs	r6, r0, #0
	bne	.L3324
	ldr	r0, [r4, #2804]
	mov	r2, ip
	ldr	ip, [r1, #56]
	mov	r1, #1
	add	r0, r0, r5
	strb	r1, [r3, #-3464]
	strb	r1, [r3, #-3463]
	ldr	r1, .L3326+12
	blx	ip
	ldr	r3, [r4, #2804]
	add	r5, r3, r5
	str	r5, [r4, #2812]
.L3318:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3320:
	bl	BsGet
	cmp	r0, #8
	mov	r8, r0
	bls	.L3304
	mov	r2, #8
	ldr	r1, .L3326+16
	mov	r0, #1
	mvn	r6, #0
	bl	dprint_vfmw
	b	.L3318
.L3307:
	str	r10, [r2, #48]
	sub	r1, fp, #60
	ldr	r0, [r4, #2804]
	mov	r2, #8
	str	r3, [fp, #-68]
	add	r0, r0, r5
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	str	r8, [r0, #52]
	ldr	r0, [r4, #2804]
	add	r0, r0, r5
	strb	r3, [r0, #2]
	ldr	r0, [r4, #2804]
	add	r0, r0, r5
	strb	r6, [r0, #46]
	ldr	r0, [r4, #2804]
	ldr	ip, [r9, #52]
	add	r0, r0, r5
	add	r0, r0, #424
	blx	ip
	ldr	r2, [r4, #2804]
	mov	r0, r4
	add	r2, r2, r5
	str	r7, [r2, #56]
	ldr	r1, [r4, #2804]
	add	r1, r1, r5
	bl	HEVC_ProcessSPS
	ldr	r3, [fp, #-68]
	subs	r6, r0, #0
	bne	.L3325
	ldr	r3, [r4, #2804]
	mov	r2, #1
	mov	r0, r6
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2804]
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2804]
	add	r5, r3, r5
	str	r5, [r4, #2812]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3323:
	ldr	r1, .L3326+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #160]
	cmp	r7, r2
	bcc	.L3314
	ldr	r3, .L3326+24
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3314
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r7, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r4, #276]
	mov	r1, #109
	blx	ip
	mvn	r6, #0
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3314:
	mvn	r6, #0
	b	.L3318
.L3321:
	ldr	r3, [r4, #2816]
	ldr	r8, [r3, #24]
	cmp	r8, #0
	beq	.L3304
	ldr	r2, [r4, #2800]
	movw	r3, #24912
	mla	r3, r3, r10, r2
	ldr	r8, [r3, #12]
	cmp	r8, #0
	moveq	r3, #1
	streq	r3, [fp, #-64]
	ldrneb	r3, [r3, #1]	@ zero_extendqisi2
	strne	r3, [fp, #-64]
	b	.L3305
.L3319:
	ldr	r1, .L3326+28
	mov	r0, #1
	mvn	r6, #0
	bl	dprint_vfmw
	b	.L3318
.L3324:
	ldr	r3, [r4, #2804]
	mov	r2, r7
	ldr	r1, .L3326+32
	mov	r0, #1
	add	r5, r3, r5
	str	r5, [r4, #2812]
	bl	dprint_vfmw
	mvn	r6, #0
	b	.L3318
.L3322:
	ldr	r1, .L3326+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r6, #0
	b	.L3318
.L3325:
	mov	r2, r7
	ldr	r1, .L3326+40
	mov	r0, #1
	str	r3, [fp, #-64]
	bl	dprint_vfmw
	ldr	r2, [r4, #2804]
	mov	r1, #1
	ldr	r3, [fp, #-64]
	mvn	r6, #0
	strb	r1, [r2, r5]
	ldr	r2, [r4, #2804]
	add	r5, r2, r5
	strb	r3, [r5, #1]
	b	.L3318
.L3327:
	.align	2
.L3326:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC348
	.word	.LANCHOR5
	.word	.LANCHOR5-3464
	.word	.LC346
	.word	.LC349
	.word	g_event_report
	.word	.LC345
	.word	.LC350
	.word	.LC347
	.word	.LC351
	UNWIND(.fnend)
	.size	HEVC_DecSPS, .-HEVC_DecSPS
	.align	2
	.global	HEVC_ProcessPPS
	.type	HEVC_ProcessPPS, %function
HEVC_ProcessPPS:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r4, r1
	mov	r7, #1
	mov	r5, r0
	strb	r7, [r4, #16]
	str	r7, [r4, #68]
	str	r7, [r4, #72]
	ldr	r1, .L3502
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	blt	.L3329
	ldr	r3, [r5, #160]
	cmp	r0, r3
	bge	.L3329
	ldr	r3, [r5, #2804]
	movw	r6, #12668
	mla	r6, r6, r0, r3
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3475
	mov	r1, r7
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r7
	str	r0, [r4, #36]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #3]
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldr	r1, .L3502+4
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #40]
	cmp	r0, #15
	bhi	.L3476
	ldr	r1, .L3502+8
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #44]
	cmp	r0, #15
	bhi	.L3477
	ldr	r1, .L3502+12
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	add	r2, r0, #26
	str	r2, [r4, #48]
	ldr	r3, [r6, #92]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L3478
	mov	r1, r7
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #6]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	streq	r0, [r4, #52]
	bne	.L3479
.L3338:
	str	r0, [r4, #56]
	ldr	r1, .L3502+16
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #60]
	cmp	r3, #24
	bhi	.L3480
	ldr	r1, .L3502+20
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #64]
	cmp	r3, #24
	bhi	.L3481
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #14]
	bne	.L3482
	ldr	r3, [r6, #188]
	strh	r3, [r4, #172]	@ movhi
	ldr	r3, [r6, #192]
	strh	r3, [r4, #212]	@ movhi
.L3376:
	ldr	r0, [r4, #68]
	cmp	r0, #0
	ble	.L3381
.L3375:
	ldr	ip, [r6, #140]
	add	r1, r4, #170
	mov	r3, #0
.L3380:
	ldrsh	r2, [r1, #2]!
	add	r3, r3, #1
	mul	r2, ip, r2
	cmp	r2, #64
	bhi	.L3379
	ldr	lr, [r6, #64]
	cmp	lr, #64
	bhi	.L3483
.L3379:
	cmp	r3, r0
	blt	.L3380
.L3381:
	ldr	r1, [r4, #72]
	cmp	r1, #0
	ble	.L3378
	ldr	r0, [r6, #140]
	ldrsh	r2, [r4, #212]
	mul	r2, r0, r2
	cmp	r2, #63
	addhi	r1, r1, #105
	addhi	r3, r4, #212
	addhi	r1, r4, r1, lsl #1
	bhi	.L3384
	b	.L3382
.L3385:
	ldrsh	r2, [r3, #2]!
	mul	r2, r0, r2
	cmp	r2, #63
	bls	.L3382
.L3384:
	cmp	r3, r1
	bne	.L3385
.L3378:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #0
	bne	.L3484
.L3387:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #21]
	cmp	r0, #0
	beq	.L3390
	add	r1, r4, #256
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	bne	.L3485
.L3390:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	ldr	r1, .L3502+24
	strb	r0, [r4, #22]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	add	r2, r0, #2
	str	r2, [r4, #84]
	cmp	r2, #1
	ble	.L3391
	ldr	r3, [r6, #128]
	cmp	r2, r3
	bhi	.L3391
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #24]
	cmp	r0, #0
	beq	.L3461
	ldrb	r6, [r5, #1]	@ zero_extendqisi2
	cmp	r6, #1
	beq	.L3486
.L3416:
	mov	r0, #0
	b	.L3461
.L3479:
	ldr	r1, .L3502+28
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #52]
	bls	.L3338
	mov	r0, r7
	ldr	r1, .L3502+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3482:
	ldr	r1, .L3502+36
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #19
	add	r2, r0, #1
	str	r2, [r4, #68]
	bhi	.L3487
	ldr	r1, .L3502+40
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #21
	add	r3, r0, #1
	str	r3, [r4, #72]
	bhi	.L3488
	ldr	r2, [r4, #68]
	cmp	r2, #10
	bgt	.L3489
	cmp	r3, #11
	ble	.L3346
	ldr	r1, .L3502+44
	mov	r2, #11
.L3472:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3502+48
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3467
.L3468:
	mov	r3, #0
	ldr	r0, [r5, #276]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
.L3461:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3382:
	ldr	r1, .L3502+52
.L3470:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3502+48
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L3468
.L3467:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3483:
	ldr	r1, .L3502+56
	b	.L3470
.L3478:
	mov	r0, r7
	ldr	r1, .L3502+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3346:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #15]
	cmp	r0, #0
	bne	.L3359
	ldr	r3, [r4, #68]
	cmp	r3, #1
	addgt	r8, r4, #86
	movgt	r7, r0
	bgt	.L3357
	b	.L3490
.L3492:
	cmp	r3, r2
	bhi	.L3355
	ldr	r3, [r4, #68]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L3491
.L3357:
	ldr	r1, .L3502+64
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #188]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L3492
.L3355:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r7
	ldr	r1, .L3502+68
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3489:
	mov	r3, r2
	ldr	r1, .L3502+72
	mov	r2, #10
	b	.L3472
.L3484:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r7, r0
	strb	r7, [r4, #20]
	cmp	r7, #0
	bne	.L3387
	ldr	r1, .L3502+76
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #76]
	bhi	.L3493
.L3389:
	ldr	r1, .L3502+80
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #80]
	bls	.L3387
	ldr	r1, .L3502+84
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #80]
	b	.L3387
.L3359:
	ldr	r7, [r4, #68]
	cmp	r7, #0
	addgt	r3, r4, #170
	movgt	r8, #0
	ble	.L3349
.L3367:
	ldr	r10, [r6, #188]
	add	r8, r8, #1
	mov	r1, r7
	str	r3, [fp, #-48]
	mul	r0, r10, r8
	bl	__aeabi_uidiv
	mov	r1, r7
	mov	r9, r0
	sub	r0, r8, #1
	mul	r0, r10, r0
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	cmp	r8, r7
	rsb	r0, r0, r9
	strh	r0, [r3, #2]!	@ movhi
	bne	.L3367
.L3349:
	ldr	r10, [r4, #72]
	cmp	r10, #0
	addgt	r2, r4, #210
	movgt	r8, #0
	ble	.L3366
.L3368:
	ldr	r3, [r6, #192]
	add	r8, r8, #1
	mov	r1, r10
	str	r2, [fp, #-52]
	mul	r0, r3, r8
	str	r3, [fp, #-48]
	bl	__aeabi_uidiv
	ldr	r3, [fp, #-48]
	mov	r1, r10
	mov	r9, r0
	sub	r0, r8, #1
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	ldr	r2, [fp, #-52]
	cmp	r8, r10
	rsb	r0, r0, r9
	strh	r0, [r2, #2]!	@ movhi
	bne	.L3368
.L3366:
	cmp	r7, #1
	bne	.L3374
	ldr	r0, [r4, #72]
	cmp	r0, #1
	beq	.L3375
.L3374:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	strb	r0, [r4, #16]
	b	.L3376
.L3329:
	mov	r2, r0
	ldr	r1, .L3502+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3475:
	mov	r2, r0
	ldr	r1, .L3502+92
	mov	r0, r7
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3476:
	mov	r0, r7
	ldr	r1, .L3502+96
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3477:
	mov	r0, r7
	ldr	r1, .L3502+100
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3480:
	ldr	r1, .L3502+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3481:
	ldr	r1, .L3502+108
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3391:
	ldr	r1, .L3502+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3491:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	ble	.L3353
.L3352:
	add	r8, r4, #126
	mov	r7, #0
	b	.L3364
.L3494:
	cmp	r3, r2
	bhi	.L3362
	ldr	r3, [r4, #72]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L3353
.L3364:
	ldr	r1, .L3502+116
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #192]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L3494
.L3362:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r7
	ldr	r1, .L3502+120
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3486:
	mov	r1, r6
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	mov	r7, r0
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, r6
	uxtb	r8, r0
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r7, #255
	uxtb	r9, r0
	beq	.L3394
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3495
.L3395:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L3399
	ldr	r1, .L3502+124
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L3502+128
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #5
	bgt	.L3397
	cmp	r0, #0
	addge	r7, r0, #1
	movge	r6, #0
	blt	.L3399
.L3401:
	ldr	r1, .L3502+132
	add	r6, r6, #1
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	ldr	r1, .L3502+136
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	cmp	r6, r7
	bne	.L3401
.L3399:
	ldr	r1, .L3502+140
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L3502+144
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
.L3394:
	cmp	r8, #0
	beq	.L3393
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #1889]
	cmp	r0, #0
	streq	r0, [r4, #1956]
	bne	.L3496
.L3403:
	ldr	r1, .L3502+148
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	cmp	r0, #63
	bhi	.L3497
	add	r2, r4, #4096
	cmp	r0, #0
	mov	r3, #0
	mov	r1, #8
	str	r3, [r4, #1960]
	str	r3, [r4, #2216]
	str	r3, [r4, #2472]
	str	r3, [r4, #2728]
	str	r3, [r4, #2984]
	str	r3, [r4, #3240]
	str	r3, [r4, #3496]
	str	r3, [r4, #3752]
	str	r3, [r4, #4008]
	str	r3, [r2, #168]
	str	r1, [r2, #424]
	str	r1, [r2, #680]
	beq	.L3414
	add	r0, r0, #1888
	add	r7, r4, #1888
	add	r0, r0, #1
	add	r7, r7, #1
	add	r8, r4, r0
	b	.L3413
.L3407:
	mov	r6, r6, asl #2
	add	r3, r4, r6
	str	r0, [r3, #1960]
	str	r0, [r3, #2216]
	str	r0, [r3, #2472]
	str	r0, [r3, #2728]
.L3408:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L3498
	add	r3, r4, r6
	str	r0, [r3, #2984]
	str	r0, [r3, #3240]
	str	r0, [r3, #3496]
	str	r0, [r3, #3752]
.L3410:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #1]!
	cmp	r0, #0
	bne	.L3499
	add	r6, r4, r6
	mov	r2, #8
	add	r3, r6, #4096
	str	r0, [r6, #4008]
	str	r0, [r3, #168]
	str	r2, [r3, #424]
	str	r2, [r3, #680]
.L3412:
	cmp	r7, r8
	beq	.L3414
.L3413:
	mov	r1, #6
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #63
	mov	r6, r0
	bgt	.L3500
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	beq	.L3407
	ldr	r1, .L3502+152
	mov	r6, r6, asl #2
	ldr	r0, [r5, #2796]
	add	r10, r4, r6
	bl	HEVC_se_v
	ldr	r1, .L3502+156
	str	r0, [r10, #1960]
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	ldr	r1, .L3502+160
	str	r0, [r10, #2216]
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	ldr	r1, .L3502+164
	str	r0, [r10, #2472]
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	str	r0, [r10, #2728]
	b	.L3408
.L3414:
	mov	r1, #1
	ldr	r0, [r5, #2796]
	bl	BsGet
.L3393:
	cmp	r9, #0
	bne	.L3460
	b	.L3416
.L3417:
	ldr	r0, [r5, #2796]
	bl	BsGet
	strb	r0, [r4, #25]
.L3460:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L3417
	b	.L3416
.L3499:
	ldr	r1, .L3502+168
	add	r6, r4, r6
	ldr	r0, [r5, #2796]
	add	r10, r6, #4096
	bl	HEVC_ue_v
	ldr	r1, .L3502+172
	str	r0, [r6, #4008]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L3502+176
	str	r0, [r10, #168]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	ldr	r1, .L3502+180
	str	r0, [r10, #424]
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	str	r0, [r10, #680]
	b	.L3412
.L3498:
	ldr	r1, .L3502+184
	add	r10, r4, r6
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	ldr	r1, .L3502+188
	str	r0, [r10, #2984]
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	ldr	r1, .L3502+192
	str	r0, [r10, #3240]
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	ldr	r1, .L3502+196
	str	r0, [r10, #3496]
	ldr	r0, [r5, #2796]
	bl	HEVC_se_v
	str	r0, [r10, #3752]
	b	.L3410
.L3495:
	ldr	r1, .L3502+200
	ldr	r0, [r5, #2796]
	bl	HEVC_ue_v
	b	.L3395
.L3500:
	mov	r2, r0
	mov	r3, #64
	ldr	r1, .L3502+204
	mov	r0, #1
	bl	dprint_vfmw
.L3400:
	ldr	r2, [r4, #84]
	mov	r0, #1
	ldr	r1, .L3502+208
	bl	dprint_vfmw
	b	.L3467
.L3487:
	mov	r3, #20
	ldr	r1, .L3502+212
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3496:
	mov	r1, #6
	ldr	r0, [r5, #2796]
	bl	BsGet
	cmp	r0, #1
	mov	r2, r0
	str	r0, [r4, #1956]
	ble	.L3403
	mov	r3, #2
	ldr	r1, .L3502+216
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3400
.L3493:
	ldr	r1, .L3502+220
	mov	r0, #1
	bl	dprint_vfmw
	str	r7, [r4, #76]
	b	.L3389
.L3353:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3359
.L3360:
	ldr	r7, [r4, #68]
	ldrh	r3, [r6, #188]
	sub	r2, r7, #1
	add	ip, r4, r7, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #170]	@ movhi
	ble	.L3369
	add	r8, r7, #42
	add	r1, r4, #86
	add	lr, r4, #170
	add	r8, r4, r8, lsl #1
.L3370:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #170]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #170]	@ movhi
	bne	.L3370
.L3369:
	sxth	r3, r3
	cmp	r3, #0
	ble	.L3501
	ldr	r1, [r4, #72]
	ldrh	r3, [r6, #192]
	sub	r2, r1, #1
	add	ip, r4, r1, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #210]	@ movhi
	ble	.L3372
	add	r8, r1, #62
	add	lr, r4, #210
	add	r1, r4, #126
	add	r8, r4, r8, lsl #1
.L3373:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #210]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #210]	@ movhi
	bne	.L3373
.L3372:
	sxth	r3, r3
	cmp	r3, #0
	bgt	.L3366
	ldr	r1, .L3502+224
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3488:
	mov	r2, r3
	ldr	r1, .L3502+228
	mov	r3, #22
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3485:
	ldr	r1, .L3502+232
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3490:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	bgt	.L3352
	b	.L3360
.L3501:
	ldr	r1, .L3502+236
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3461
.L3397:
	mov	r2, r0
	ldr	r1, .L3502+240
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3400
.L3497:
	mov	r2, r0
	mov	r3, #64
	ldr	r1, .L3502+244
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3400
.L3503:
	.align	2
.L3502:
	.word	.LC352
	.word	.LC355
	.word	.LC357
	.word	.LC359
	.word	.LC363
	.word	.LC365
	.word	.LC386
	.word	.LC361
	.word	.LC362
	.word	.LC367
	.word	.LC369
	.word	.LC372
	.word	g_event_report
	.word	.LC380
	.word	.LC379
	.word	.LC360
	.word	.LC373
	.word	.LC374
	.word	.LC371
	.word	.LC381
	.word	.LC383
	.word	.LC384
	.word	.LC353
	.word	.LC354
	.word	.LC356
	.word	.LC358
	.word	.LC364
	.word	.LC366
	.word	.LC387
	.word	.LC375
	.word	.LC376
	.word	.LC391
	.word	.LC392
	.word	.LC394
	.word	.LC395
	.word	.LC389
	.word	.LC390
	.word	.LC397
	.word	.LC400
	.word	.LC401
	.word	.LC402
	.word	.LC403
	.word	.LC408
	.word	.LC409
	.word	.LC410
	.word	.LC411
	.word	.LC404
	.word	.LC405
	.word	.LC406
	.word	.LC407
	.word	.LC388
	.word	.LC399
	.word	.LC412
	.word	.LC368
	.word	.LC396
	.word	.LC382
	.word	.LC378
	.word	.LC370
	.word	.LC385
	.word	.LC377
	.word	.LC393
	.word	.LC398
	UNWIND(.fnend)
	.size	HEVC_ProcessPPS, .-HEVC_ProcessPPS
	.align	2
	.global	HEVC_DecPPS
	.type	HEVC_DecPPS, %function
HEVC_DecPPS:
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
	ldr	r1, .L3514
	mov	r4, r0
	ldr	r0, [r0, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r4, #164]
	cmp	r0, r3
	mov	r6, r0
	bcs	.L3510
	movw	r7, #5036
	ldr	r3, [r4, #2808]
	mul	r5, r7, r0
	add	r2, r3, r5
	ldrb	r9, [r3, r5]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L3511
	str	r0, [r2, #28]
	mov	r0, r4
	ldr	r1, [r4, #2808]
	add	r1, r1, r5
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L3512
	ldr	r3, [r4, #2808]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2808]
	strb	r2, [r3, r5]
.L3506:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3511:
	ldr	r10, .L3514+4
	mov	r2, r7
	ldr	r9, .L3514+8
	mov	r1, #0
	ldr	r0, .L3514+12
	ldr	r3, [r10, #48]
	blx	r3
	ldr	r1, .L3514+12
	mov	r0, r4
	str	r6, [r9, #-3436]
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L3513
	ldr	r0, [r4, #2808]
	mov	r3, #1
	mov	r2, r7
	ldr	ip, [r10, #56]
	add	r0, r0, r5
	strb	r3, [r9, #-3463]
	strb	r3, [r9, #-3464]
	ldr	r1, .L3514+12
	blx	ip
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3513:
	mov	r2, r6
	ldr	r1, .L3514+16
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L3506
.L3510:
	mov	r2, r0
	ldr	r1, .L3514+20
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L3506
.L3512:
	mov	r2, r6
	ldr	r1, .L3514+16
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2808]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2808]
	strb	r9, [r3, r5]
	b	.L3506
.L3515:
	.align	2
.L3514:
	.word	.LC413
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR5
	.word	.LANCHOR5-3464
	.word	.LC415
	.word	.LC414
	UNWIND(.fnend)
	.size	HEVC_DecPPS, .-HEVC_DecPPS
	.align	2
	.global	HEVC_DecPredWeightTable
	.type	HEVC_DecPredWeightTable, %function
HEVC_DecPredWeightTable:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 136
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #140)
	sub	sp, sp, #140
	add	r4, r0, #4096
	ldr	r3, [r0, #2808]
	mov	r6, r0
	ldr	r2, [r4, #732]
	movw	r0, #5036
	ldr	r1, [r4, #716]
	ldr	r5, [r6, #2804]
	mla	r3, r0, r2, r3
	cmp	r1, #1
	ldr	r7, [r3, #32]
	beq	.L3582
	cmp	r1, #0
	bne	.L3520
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3520
.L3518:
	ldr	r1, .L3593
	ldr	r0, [r6, #2796]
	bl	HEVC_ue_v
	cmp	r0, #7
	str	r0, [r4, #852]
	bhi	.L3583
	movw	r8, #12668
	mla	r8, r8, r7, r5
	ldr	r3, [r8, #60]
	cmp	r3, #0
	streq	r0, [r4, #984]
	bne	.L3584
.L3560:
	ldr	r3, [r4, #772]
	cmp	r3, #0
	subne	r3, fp, #172
	strne	r3, [fp, #-176]
	movne	r5, #0
	movne	r7, r3
	beq	.L3526
.L3527:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [r4, #772]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L3527
	ldr	r2, [r8, #60]
	cmp	r2, #0
	beq	.L3528
	cmp	r3, #0
	subne	r7, fp, #108
	movne	r5, #0
	beq	.L3526
.L3532:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [r4, #772]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L3532
.L3528:
	cmp	r3, #0
	beq	.L3526
	add	r9, r6, #5056
	add	r10, r6, #5120
	add	r9, r9, #28
	add	r10, r10, #36
	mov	r5, #0
	b	.L3543
.L3533:
	ldr	r2, [r4, #852]
	mov	r3, #1
	str	r1, [r9, #-132]
	mov	r2, r3, asl r2
	str	r2, [r9]
.L3535:
	ldr	r2, [r8, #60]
	cmp	r2, #0
	beq	.L3537
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L3538
	ldr	r1, [r4, #984]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L3537:
	ldr	r2, [r4, #772]
	add	r5, r5, #1
	add	r9, r9, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L3526
.L3543:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L3533
	ldr	r1, .L3593+4
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L3585
	ldr	r2, [r4, #852]
	mov	r3, #1
	ldr	r1, .L3593+8
	add	r0, r0, r3, asl r2
	str	r0, [r9]
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r9, #-132]
	cmp	r2, #255
	bls	.L3535
	mov	r2, r0
	ldr	r1, .L3593+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3582:
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3518
.L3520:
	mov	r0, #0
.L3581:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3538:
	sub	r7, r10, #8
.L3541:
	ldr	r1, .L3593+16
	ldr	r0, [r6, #2796]
	str	r7, [fp, #-180]
	bl	HEVC_se_v
	ldr	r1, .L3593+20
	add	lr, r0, #128
	cmp	lr, #255
	bhi	.L3586
	ldr	lr, [r4, #984]
	mov	r3, #1
	add	r7, r7, #4
	add	r0, r0, r3, asl lr
	str	r0, [r7, #-4]
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r1, r0, #512
	cmp	r1, #1024
	bcs	.L3587
	ldr	r3, [fp, #-180]
	cmp	r10, r7
	ldr	lr, [r4, #984]
	ldr	r1, [r3]
	mov	r1, r1, asl #7
	mov	r1, r1, asr lr
	rsb	r1, r1, #128
	add	r0, r0, r1
	ssat	r0, #8, r0
	str	r0, [r7, #124]
	bne	.L3541
	b	.L3537
.L3526:
	ldr	r5, [r4, #716]
	cmp	r5, #0
	bne	.L3520
	ldr	r3, [r4, #776]
	cmp	r3, #0
	beq	.L3520
	sub	r3, fp, #172
	str	r3, [fp, #-176]
	mov	r7, r3
.L3544:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [r4, #776]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L3544
	ldr	r2, [r8, #60]
	cmp	r2, #0
	bne	.L3588
.L3545:
	cmp	r3, #0
	beq	.L3520
	add	r7, r6, #5376
	add	r10, r6, #5440
	add	r7, r7, #28
	add	r10, r10, #36
	mov	r5, #0
	b	.L3559
.L3549:
	ldr	r1, [r4, #852]
	mov	r3, #1
	str	r0, [r7, #-388]
	mov	r1, r3, asl r1
	str	r1, [r7]
.L3551:
	ldr	r1, [r8, #60]
	cmp	r1, #0
	beq	.L3553
	sub	r1, fp, #108
	ldr	r1, [r1, r5, asl #2]
	cmp	r1, #0
	bne	.L3554
	ldr	r0, [r4, #984]
	mov	r3, #1
	str	r1, [r10, #120]
	mov	r0, r3, asl r0
	str	r1, [r10, #124]
	str	r0, [r10, #-8]
	str	r0, [r10, #-4]
.L3553:
	ldr	r1, [r4, #776]
	add	r5, r5, #1
	add	r7, r7, #4
	add	r10, r10, #8
	cmp	r1, r5
	bls	.L3520
.L3559:
	ldr	r3, [fp, #-176]
	ldr	r0, [r3, r5, asl #2]
	cmp	r0, #0
	beq	.L3549
	ldr	r1, .L3593+24
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r1, r0, #128
	cmp	r1, #255
	bhi	.L3589
	ldr	ip, [r4, #852]
	mov	r3, #1
	ldr	r1, .L3593+28
	add	r0, r0, r3, asl ip
	str	r0, [r7]
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r1, r0, #128
	str	r0, [r7, #-388]
	cmp	r1, #255
	bls	.L3551
	ldr	r1, .L3593+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3554:
	sub	r9, r10, #8
.L3557:
	ldr	r1, .L3593+36
	ldr	r0, [r6, #2796]
	str	r9, [fp, #-180]
	bl	HEVC_se_v
	ldr	r1, .L3593+40
	add	lr, r0, #128
	cmp	lr, #255
	bhi	.L3590
	ldr	lr, [r4, #984]
	mov	r3, #1
	add	r9, r9, #4
	add	r0, r0, r3, asl lr
	str	r0, [r9, #-4]
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r1, r0, #512
	cmp	r1, #1024
	bcs	.L3591
	ldr	r3, [fp, #-180]
	cmp	r10, r9
	ldr	lr, [r4, #984]
	ldr	r1, [r3]
	mov	r1, r1, asl #7
	mov	r1, r1, asr lr
	rsb	r1, r1, #128
	add	r1, r0, r1
	ssat	r1, #8, r1
	str	r1, [r9, #124]
	bne	.L3557
	b	.L3553
.L3584:
	ldr	r1, .L3593+44
	ldr	r0, [r6, #2796]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #14
	bhi	.L3592
	ldr	r3, [r4, #852]
	add	r0, r0, r3
	str	r0, [r4, #984]
	cmp	r0, #7
	bls	.L3560
	ldr	r1, .L3593+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3586:
	ldr	r1, .L3593+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3587:
	ldr	r1, .L3593+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3588:
	cmp	r3, #0
	subne	r7, fp, #108
	movne	r5, #0
	beq	.L3520
.L3548:
	mov	r1, #1
	ldr	r0, [r6, #2796]
	bl	BsGet
	ldr	r3, [r4, #776]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L3548
	b	.L3545
.L3585:
	mov	r2, r0
	ldr	r1, .L3593+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3590:
	ldr	r1, .L3593+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3591:
	ldr	r1, .L3593+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3589:
	ldr	r1, .L3593+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3583:
	ldr	r1, .L3593+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3592:
	ldr	r1, .L3593+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3581
.L3594:
	.align	2
.L3593:
	.word	.LC416
	.word	.LC421
	.word	.LC423
	.word	.LC424
	.word	.LC425
	.word	.LC427
	.word	.LC429
	.word	.LC431
	.word	.LC432
	.word	.LC433
	.word	.LC435
	.word	.LC418
	.word	.LC420
	.word	.LC426
	.word	.LC428
	.word	.LC422
	.word	.LC434
	.word	.LC436
	.word	.LC430
	.word	.LC417
	.word	.LC419
	UNWIND(.fnend)
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	2
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #76)
	sub	sp, sp, #76
	ldr	r3, [r0, #2816]
	add	r5, r0, #4096
	mov	r4, r0
	mov	r1, #1
	ldr	r0, [r0, #2796]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-48]
	bl	BsGet
	ldr	r6, [r5, #724]
	sub	r3, r6, #16
	cmp	r3, #5
	movhi	r3, #0
	movls	r3, #1
	cmp	r3, #0
	str	r3, [fp, #-68]
	strb	r0, [r5, #696]
	bne	.L3909
.L3596:
	ldr	r1, .L3954
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r5, #732]
	ldr	r3, [r4, #164]
	blt	.L3598
	cmp	r0, r3
	bge	.L3598
	mov	r0, r4
	bl	HEVC_VpsSpsPpsCheck
	subs	r3, r0, #0
	str	r3, [fp, #-84]
	bne	.L3910
	ldr	r1, [r5, #732]
	movw	r8, #5036
	ldr	r3, [r4, #2808]
	movw	r7, #12668
	ldr	r2, [r4, #2804]
	ldr	r0, [r4, #2800]
	mla	r8, r8, r1, r3
	str	r0, [fp, #-52]
	ldr	r1, [r8, #32]
	ldrb	r3, [r8, #2]	@ zero_extendqisi2
	mla	r7, r7, r1, r2
	cmp	r3, #0
	ldr	r3, [r7, #48]
	str	r3, [fp, #-56]
	bne	.L3911
.L3604:
	mov	r3, #0
	strb	r3, [r5, #697]
.L3605:
	ldr	r9, [r7, #140]
	ldr	r3, [r7, #144]
	cmp	r9, #0
	beq	.L3607
	cmp	r3, #0
	beq	.L3607
	ldr	r0, [r7, #68]
	mov	r1, r3
	add	r0, r3, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	mov	r1, r9
	mov	r10, r0
	ldr	r0, [r7, #64]
	add	r0, r9, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	ldr	ip, [r7, #172]
	mov	r1, #1
	mov	ip, ip, asl r1
	mov	r9, r1, asl ip
	mul	r0, r0, r10
	cmp	r0, r1
	ble	.L3770
	mov	r3, r1
	mov	r1, #0
.L3610:
	add	r1, r1, #1
	cmp	r0, r3, asl r1
	bgt	.L3610
.L3609:
	ldrb	r3, [r5, #696]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [fp, #-72]
	beq	.L3912
.L3611:
	ldrb	r3, [r5, #697]	@ zero_extendqisi2
	ldr	r2, [r4, #192]
	cmp	r3, #0
	str	r2, [r5, #708]
	bne	.L3614
	ldrb	r10, [r4, #1]	@ zero_extendqisi2
	cmp	r10, #1
	beq	.L3615
	ldr	r2, [r8, #36]
	cmp	r2, #0
	movne	r10, r3
	beq	.L3619
.L3621:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r8, #36]
	add	r10, r10, #1
	cmp	r3, r10
	bhi	.L3621
.L3619:
	ldr	r1, .L3954+4
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r5, #716]
	bhi	.L3913
	ldrb	r3, [r8, #4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3914
.L3622:
	sub	r6, r6, #19
	ldr	r1, [fp, #-56]
	cmp	r6, #1
	ldr	r0, [fp, #-52]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	movhi	r2, #0
	movls	r2, #1
	str	r2, [fp, #-80]
	movw	r2, #24912
	mla	r2, r2, r1, r0
	cmp	r3, #1
	str	r2, [fp, #-92]
	movne	r2, #0
	strne	r2, [fp, #-76]
	strne	r2, [fp, #-64]
	beq	.L3915
.L3623:
	ldr	r2, [fp, #-80]
	cmp	r2, #0
	bne	.L3627
	cmp	r3, #0
	beq	.L3916
.L3628:
	ldr	r3, [r7, #116]
	mov	r2, #1
	ldr	r6, [r4, #188]
	mov	r3, r2, asl r3
	str	r3, [fp, #-88]
	mov	r1, r3
	mov	r0, r6
	bl	__aeabi_uidivmod
	ldr	r3, [fp, #-64]
	cmp	r3, r1
	rsb	r3, r1, r6
	bcs	.L3629
	ldr	r0, [fp, #-88]
	ldr	r2, [fp, #-64]
	rsb	r2, r2, r1
	cmp	r2, r0, lsr #1
	movcs	r2, r0
	addcs	r3, r3, r2
	bcs	.L3630
.L3629:
	ldr	r2, [fp, #-64]
	cmp	r2, r1
	bls	.L3630
	rsb	r1, r1, r2
	ldr	r2, [fp, #-88]
	cmp	r1, r2, lsr #1
	rsbhi	r3, r2, r3
.L3630:
	ldr	r1, [r5, #724]
	ldr	r2, [fp, #-48]
	sub	r1, r1, #16
	cmp	r1, #2
	ldr	r1, [fp, #-64]
	add	r2, r4, r2, lsl #2
	movls	r3, #0
	add	r3, r3, r1
	str	r3, [r5, #708]
	ldr	r2, [r2, #212]
	cmp	r3, r2
	bge	.L3632
	ldrb	r0, [r5, #696]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L3917
.L3632:
	ldr	r3, [r4, #2356]
	cmp	r3, #0
	ldreq	r3, [r5, #708]
	streq	r3, [r4, #192]
	ldr	r3, [r5, #720]
	cmp	r3, #0
	bne	.L3634
	ldr	r3, [r5, #724]
	cmp	r3, #15
	bhi	.L3635
	tst	r3, #1
	movne	r2, #1
	beq	.L3635
.L3636:
	sub	r3, r3, #7
	bics	r3, r3, #2
	andne	r3, r2, #1
	moveq	r3, #0
	cmp	r3, #0
	ldrne	r3, [r5, #708]
	strne	r3, [r4, #188]
.L3634:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L3637
	ldr	r3, [r7, #176]
	mov	r1, #0
	cmp	r3, #1
	movhi	r2, #1
	bls	.L3639
.L3641:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L3641
	cmp	r1, #0
	bne	.L3918
.L3642:
	mov	r2, #164
	add	r0, r5, #1616
	mla	r1, r2, r1, r7
	add	r3, r4, #5696
	add	r0, r0, #12
	add	r3, r3, #28
	str	r3, [fp, #-76]
	add	r1, r1, #2160
	add	r1, r1, #4
	bl	memcpy
.L3640:
	ldrb	r3, [r7, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3644
	ldr	r3, [r7, #180]
	ldr	r6, [r5, #1632]
	cmp	r3, #0
	ldr	r2, [r5, #1628]
	streq	r3, [fp, #-96]
	add	r6, r6, r2
	streq	r3, [fp, #-48]
	streq	r3, [fp, #-56]
	bne	.L3919
.L3645:
	ldr	r1, .L3954+8
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r2, [r5, #1628]
	ldr	r3, [r5, #1632]
	ldr	ip, [fp, #-48]
	add	r1, r3, r2
	add	r0, r0, ip
	str	r0, [fp, #-60]
	add	r1, r1, r0
	cmp	r1, #16
	bhi	.L3920
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	add	r3, r6, r3
	str	r3, [fp, #-100]
	beq	.L3661
	ldr	r3, [fp, #-100]
	str	r8, [fp, #-104]
	add	r9, r3, #5696
	add	ip, r3, #1216
	add	r9, r9, #39
	add	ip, ip, #3
	add	r3, r4, r9
	add	r10, r4, ip, lsl #2
	mov	r2, r3
	mov	r3, #0
	mov	r9, r3
	str	r3, [fp, #-52]
	mov	r8, r2
	b	.L3660
.L3924:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ldreq	r0, [fp, #-56]
	bne	.L3921
.L3652:
	add	r3, r7, r0
	add	r0, r7, r0, lsl #2
	ldrb	r3, [r3, #13]	@ zero_extendqisi2
	ldr	r6, [r0, #196]
	strb	r3, [r8]
.L3655:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L3922
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	cmp	r9, r3
	cmpne	r9, #0
	str	r6, [r10, #944]
	str	r0, [r10]
	ldr	r3, [r5, #708]
	moveq	r2, #0
	str	r2, [fp, #-52]
	rsb	r6, r3, r6
	str	r6, [r10, #876]
.L3658:
	ldr	r3, [fp, #-60]
	add	r9, r9, #1
	sub	r10, r10, #4
	sub	r8, r8, #1
	cmp	r9, r3
	beq	.L3923
.L3660:
	ldr	r3, [fp, #-48]
	cmp	r3, r9
	bhi	.L3924
	ldr	r1, [r7, #120]
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r8]
	b	.L3655
.L3944:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #701]
	cmp	r0, #0
	bne	.L3925
	ldr	r3, [r5, #716]
	ldr	r2, [r8, #40]
	cmp	r3, #0
	str	r2, [r5, #772]
	bne	.L3703
	ldr	r2, [r8, #44]
	mov	r6, r3
	mov	r9, r3
	str	r2, [r5, #776]
.L3704:
	ldr	r3, [fp, #-76]
	cmp	r3, #0
	beq	.L3926
	ldr	r3, [fp, #-76]
	ldr	r2, [r3, #8]
	cmp	r2, #16
	bhi	.L3707
	cmp	r2, #0
	moveq	r3, r2
	beq	.L3709
	ldr	r3, [fp, #-76]
	add	r2, r2, #11
	add	r1, r3, #11
	add	ip, r3, r2
	mov	r3, #0
.L3711:
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	cmp	r2, #0
	addne	r3, r3, #1
	cmp	r1, ip
	bne	.L3711
.L3709:
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #1
	ldreq	r2, [r5, #2056]
	addeq	r3, r3, r2
	ldrb	r2, [r8, #22]	@ zero_extendqisi2
	cmp	r2, #0
	cmpne	r3, #1
	ble	.L3905
	add	r1, r4, #4736
	add	r2, r4, #5888
	add	r1, r1, #56
	mov	r0, r4
	bl	HEVC_DecRefPicListsModification
	cmp	r0, #0
	bne	.L3927
.L3705:
	ldr	r3, [r5, #716]
	cmp	r3, #0
	beq	.L3767
.L3713:
	cmp	r3, #2
	beq	.L3697
.L3768:
	ldrb	r3, [r8, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3928
.L3714:
	ldrb	r3, [r5, #700]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r5, #716]
	beq	.L3723
	cmp	r3, #0
	beq	.L3929
	cmp	r3, #2
	mov	r3, #1
	strb	r3, [r5, #704]
	beq	.L3720
.L3719:
	ldr	r3, [r5, #772]
	cmp	r3, #1
	bls	.L3899
.L3722:
	ldr	r1, .L3954+12
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldrb	r2, [r5, #704]	@ zero_extendqisi2
	cmp	r2, #0
	subne	r6, r9, #1
	subeq	r6, r6, #1
	cmp	r6, r0
	str	r0, [r5, #740]
	movcs	r3, #0
	movcc	r3, #1
	orrs	r3, r3, r0, lsr #31
	bne	.L3726
.L3899:
	ldr	r3, [r5, #716]
.L3723:
	ldrb	r2, [r8, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3727
	cmp	r3, #1
	beq	.L3730
.L3727:
	ldrb	r2, [r8, #11]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3718
	cmp	r3, #0
	bne	.L3718
.L3730:
	mov	r0, r4
	bl	HEVC_DecPredWeightTable
	cmp	r0, #0
	ldreq	r3, [r5, #716]
	bne	.L3930
.L3718:
	cmp	r3, #2
	beq	.L3731
	ldr	r1, .L3954+16
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	rsb	r3, r0, #4
	rsb	r2, r0, #5
	cmp	r3, #4
	str	r2, [r5, #744]
	bhi	.L3931
.L3731:
	ldr	r1, .L3954+20
	ldr	r0, [r4, #2796]
	bl	HEVC_se_v
	ldr	r2, [r8, #48]
	add	r2, r0, r2
	str	r2, [r5, #712]
	ldr	r3, [r7, #92]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L3932
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3933
.L3733:
	ldrb	r3, [r8, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3900
	ldrb	r3, [r8, #19]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3934
.L3739:
	ldrb	r0, [r8, #20]	@ zero_extendqisi2
	strb	r0, [r5, #705]
	ldr	r3, [r8, #76]
	str	r3, [r5, #756]
	ldr	r3, [r8, #80]
	str	r3, [r5, #760]
.L3738:
	ldrb	r3, [r7, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3742
	movw	r3, #698
	ldrh	r2, [r5, r3]
	adds	r3, r2, #0
	movne	r3, #1
.L3742:
	ldrb	r2, [r8, #17]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3743
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L3935
.L3743:
	strb	r2, [r5, #706]
.L3614:
	ldr	r3, [r8, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	bne	.L3744
.L3751:
	ldrb	r3, [r8, #23]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3936
.L3746:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	bne	.L3937
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [fp, #-68]
	beq	.L3762
	cmp	r3, #0
	beq	.L3763
	ldr	r3, [r5, #728]
	mov	r2, #1
	add	r3, r4, r3
	strb	r2, [r3, #6]
.L3760:
	ldr	r2, [r5, #708]
	ldr	r1, [fp, #-68]
	cmp	r2, #0
	moveq	r1, #0
	andne	r1, r1, #1
	cmp	r1, #0
	bne	.L3938
.L3761:
	mov	r2, #0
	strb	r2, [r3, #4]
.L3765:
	mov	r0, r4
	bl	HEVC_IsNewPic
	str	r0, [r5, #848]
	mov	r0, r4
	bl	HEVC_ReadByteAlignment
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L3895:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3911:
	ldrb	r3, [r5, #696]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3604
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r5, #697]
	b	.L3605
.L3937:
	ldr	r3, [r5, #728]
	add	r3, r4, r3
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3760
	b	.L3761
.L3909:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L3596
.L3912:
	ldr	r0, [r4, #2796]
	bl	BsGet
	str	r0, [r5, #736]
	cmp	r0, #0
	ldr	r2, [r7, #192]
	ldr	r3, [r7, #188]
	mul	r3, r3, r2
	blt	.L3613
	cmp	r3, r0
	bls	.L3613
	mul	r3, r9, r0
	str	r3, [fp, #-72]
	b	.L3611
.L3744:
	ldr	r1, .L3954+24
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r8, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	ldreq	r3, [r7, #192]
	subeq	r3, r3, #1
	mov	r6, r0
	beq	.L3748
	cmp	r3, #256
	ldreq	r2, [r8, #68]
	ldreq	r3, [r8, #72]
	ldrne	r3, [r7, #192]
	ldrne	r2, [r8, #68]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L3748:
	cmp	r3, #255
	movcs	r3, #255
	cmp	r6, r3
	bhi	.L3939
	cmp	r6, #0
	beq	.L3751
	ldr	r1, .L3954+28
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r0, #31
	add	r7, r0, #1
	movls	r9, #0
	bhi	.L3940
.L3753:
	add	r9, r9, #1
	mov	r1, r7
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r9, r6
	bne	.L3753
	ldrb	r3, [r8, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3746
.L3936:
	ldr	r1, .L3954+32
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	cmp	r0, #256
	mov	r7, r0
	bhi	.L3941
	ldr	r0, [r4, #2796]
	bl	BsResidBits
	cmp	r7, r0
	bhi	.L3757
	cmp	r7, #0
	movne	r6, #0
	beq	.L3746
.L3759:
	add	r6, r6, #1
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	cmp	r6, r7
	bne	.L3759
	b	.L3746
.L3627:
	mov	r2, #0
	str	r2, [r5, #708]
	ldr	r2, [r4, #2356]
	cmp	r2, #0
	streq	r2, [r4, #192]
	ldr	r2, [r5, #720]
	cmp	r2, #0
	streq	r2, [r4, #188]
.L3663:
	cmp	r3, #1
	beq	.L3942
.L3665:
	ldrb	r3, [r7, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3943
.L3695:
	ldr	r3, [fp, #-80]
	cmp	r3, #0
	movne	r3, #0
	strneb	r3, [r5, #700]
	ldr	r3, [r5, #716]
	cmp	r3, #2
	bne	.L3944
.L3697:
	ldrb	r3, [r5, #700]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3720
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r5, #704]
	b	.L3723
.L3762:
	cmp	r3, #0
	beq	.L3763
	ldr	r3, [r5, #728]
	ldrb	r2, [fp, #-72]	@ zero_extendqisi2
	add	r3, r4, r3
	strb	r2, [r3, #6]
	b	.L3761
.L3938:
	ldr	r2, [r5, #724]
	cmp	r2, #21
	moveq	r2, #1
	streqb	r2, [r3, #4]
	bne	.L3761
	b	.L3765
.L3635:
	sub	r2, r3, #16
	cmp	r2, #7
	movhi	r2, #0
	movls	r2, #1
	b	.L3636
.L3922:
	ldr	r1, .L3954+36
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-64]
	cmp	r9, #0
	cmpne	r9, r3
	ldrne	r3, [fp, #-52]
	addne	r0, r0, r3
	mov	r3, #1
	str	r3, [r10]
	ldr	r3, [r5, #708]
	str	r0, [fp, #-52]
	rsb	r1, r2, r3
	ldr	r2, [fp, #-88]
	add	r6, r1, r6
	mls	r0, r2, r0, r6
	rsb	r3, r3, r0
	str	r3, [r10, #876]
	str	r0, [r10, #944]
	b	.L3658
.L3921:
	ldr	r1, [fp, #-96]
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r7, #180]
	sub	r3, r3, #1
	cmp	r0, #0
	blt	.L3654
	cmp	r3, r0
	bcs	.L3652
.L3654:
	str	r3, [sp]
	mov	r2, r9
	mov	r3, r0
	ldr	r1, .L3954+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3763:
	ldr	r3, [r5, #728]
	add	r3, r4, r3
	b	.L3761
.L3900:
	ldrb	r0, [r5, #705]	@ zero_extendqisi2
	b	.L3738
.L3923:
	ldr	r8, [fp, #-104]
.L3661:
	ldr	r3, [fp, #-100]
	cmp	r3, #16
	str	r3, [r5, #1636]
	bhi	.L3945
.L3644:
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r5, #700]
	ldreqb	r3, [r4, #1]	@ zero_extendqisi2
	beq	.L3663
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r5, #700]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	b	.L3663
.L3905:
	ldr	r3, [r5, #716]
	cmp	r3, #0
	bne	.L3768
.L3767:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r5, #716]
	strb	r0, [r5, #702]
	b	.L3713
.L3914:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	b	.L3622
.L3915:
	ldr	r1, [fp, #-48]
	add	r2, r1, #4096
	cmp	r1, #0
	add	r2, r2, #44
	ldr	r1, [fp, #-92]
	add	r2, r1, r2, lsl #2
	ldr	r2, [r2, #4]
	beq	.L3624
	add	r2, r1, r2
	add	r2, r2, #12416
	ldrb	r2, [r2, #7]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3624
.L3625:
	ldr	r1, [r7, #120]
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	str	r0, [fp, #-64]
.L3626:
	add	r2, r4, #5696
	add	r2, r2, #28
	str	r2, [fp, #-76]
	b	.L3623
.L3624:
	ldr	r2, [fp, #-80]
	cmp	r2, #0
	movne	r2, #0
	strne	r2, [fp, #-64]
	bne	.L3626
	b	.L3625
.L3943:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #698]
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r5, #699]
	b	.L3695
.L3598:
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L3954+44
	mov	r0, #1
	ldr	r1, .L3954+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3933:
	ldr	r1, .L3954+52
	ldr	r0, [r4, #2796]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #748]
	cmp	r3, #24
	bhi	.L3946
	ldr	r3, [r8, #60]
	add	r2, r0, r3
	add	r2, r2, #12
	cmp	r2, #24
	bhi	.L3947
	ldr	r1, .L3954+56
	ldr	r0, [r4, #2796]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #752]
	cmp	r3, #24
	bhi	.L3948
	ldr	r2, [r8, #64]
	add	r2, r0, r2
	add	r3, r2, #12
	cmp	r3, #24
	bls	.L3733
	ldr	r1, .L3954+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3770:
	mov	r1, #0
	b	.L3609
.L3928:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r5, #703]
	b	.L3714
.L3703:
	mov	r6, r0
	mov	r9, r0
	str	r0, [r5, #776]
.L3702:
	cmp	r3, #2
	bne	.L3704
	b	.L3705
.L3637:
	add	r6, r4, #5696
	ldr	r3, [r7, #176]
	add	r6, r6, #28
	mov	r1, r7
	mov	r0, r4
	mov	r2, r6
	bl	HEVC_DecShortTermRefPicSet
	cmp	r0, #0
	streq	r6, [fp, #-76]
	beq	.L3640
	ldr	r1, .L3954+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3916:
	ldr	r1, [r7, #120]
	ldr	r0, [r4, #2796]
	bl	BsGet
	str	r0, [fp, #-64]
	b	.L3628
.L3615:
	ldr	r3, [r8, #36]
	cmp	r3, #0
	beq	.L3619
	mov	r1, r10
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r8, #36]
	cmp	r3, #1
	bls	.L3619
	mov	r1, r10
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r8, #36]
	cmp	r3, #2
	bls	.L3619
	mov	r1, r10
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r8, #36]
	cmp	r3, #3
	bls	.L3619
	mov	r10, #3
.L3620:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r8, #36]
	add	r10, r10, #1
	cmp	r10, r3
	bcc	.L3620
	b	.L3619
.L3925:
	ldr	r1, .L3954+68
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	add	r9, r0, #1
	cmp	r9, #16
	bhi	.L3949
	ldr	r3, [r5, #716]
	str	r9, [r5, #772]
	cmp	r3, #0
	movne	r6, #0
	strne	r6, [r5, #776]
	bne	.L3702
	ldr	r1, .L3954+72
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	add	r6, r0, #1
	cmp	r6, #16
	strls	r6, [r5, #776]
	ldrls	r3, [r5, #716]
	bls	.L3702
	mov	r2, r6
	mov	r3, #16
	ldr	r1, .L3954+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3918:
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r7, #176]
	subs	r1, r0, #0
	sublt	r3, r3, #1
	blt	.L3643
.L3639:
	sub	r3, r3, #1
	cmp	r3, r1
	bcs	.L3642
.L3643:
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L3954+80
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3929:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	ldr	r3, [r5, #716]
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #704]
	beq	.L3731
	cmp	r0, #0
	bne	.L3719
	ldr	r2, [r5, #776]
	cmp	r2, #1
	bhi	.L3722
	b	.L3723
.L3720:
	mov	r3, #2
	b	.L3727
.L3941:
	mov	r2, r0
	ldr	r1, .L3954+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3945:
	ldr	r2, [fp, #-100]
	mov	r3, #16
	ldr	r1, .L3954+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3942:
	ldr	r1, [r4, #2816]
	ldr	r0, [r1, #24]
	cmp	r0, #0
	beq	.L3666
	ldr	r2, [fp, #-92]
	add	r10, r2, #12288
	ldrb	r6, [r10, #134]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L3667
	add	r9, r2, r0, lsl #2
	add	r9, r9, #16384
	ldr	r2, [r9, #196]
	cmp	r2, #0
	ble	.L3668
	mov	r1, r3
	ldr	r0, [r4, #2796]
	str	r3, [fp, #-48]
	bl	BsGet
	ldr	ip, [r9, #196]
	ldr	r3, [fp, #-48]
	tst	r0, #255
	beq	.L3670
	cmp	ip, #1
	ble	.L3670
	ldrb	r2, [r10, #133]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3671
	cmp	ip, #1
	ldr	r0, [r4, #2796]
	bls	.L3781
.L3673:
	add	r2, r2, #1
	cmp	ip, r3, asl r2
	mov	r1, r2
	bhi	.L3673
.L3672:
	bl	BsGet
	add	r2, r0, #1
	str	r2, [r5, #2056]
	ldr	r3, [r9, #196]
	cmp	r2, r3
	streq	r2, [fp, #-84]
	moveq	r6, #0
	beq	.L3675
	cmp	r2, #2
	bgt	.L3950
	cmp	r2, #0
	bgt	.L3676
	mov	r6, #1
	str	r2, [fp, #-84]
.L3677:
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	ble	.L3665
.L3689:
	add	r1, r4, #6144
	mov	r2, #0
	add	r1, r1, #12
	ldr	r0, [fp, #-84]
	b	.L3694
.L3693:
	add	r2, r2, #1
	cmp	r2, r0
	beq	.L3665
.L3694:
	cmp	r6, #0
	mov	r3, r2
	streq	r2, [r1]
	add	r1, r1, #4
	ldrne	r3, [r1, #-4]
	cmp	r3, #2
	ble	.L3693
	mov	r0, #2
	ldr	r1, .L3954+92
	str	r0, [sp]
	mov	r0, #1
	bl	dprint_vfmw
.L3679:
	ldr	r1, .L3954+96
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3607:
	mov	r2, r9
	ldr	r1, .L3954+100
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3935:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	strb	r0, [r5, #706]
	b	.L3614
.L3934:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	tst	r0, #255
	beq	.L3739
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #705]
	cmp	r0, #0
	bne	.L3738
	ldr	r1, .L3954+104
	ldr	r0, [r4, #2796]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #756]
	bhi	.L3951
.L3740:
	ldr	r1, .L3954+108
	ldr	r0, [r4, #2796]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #760]
	bls	.L3900
	ldr	r1, .L3954+112
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r8, #80]
	ldrb	r0, [r5, #705]	@ zero_extendqisi2
	str	r3, [r5, #760]
	b	.L3738
.L3955:
	.align	2
.L3954:
	.word	.LC437
	.word	.LC442
	.word	.LC449
	.word	.LC464
	.word	.LC467
	.word	.LC469
	.word	.LC481
	.word	.LC483
	.word	.LC485
	.word	.LC452
	.word	.LC451
	.word	.LANCHOR0+652
	.word	.LC438
	.word	.LC471
	.word	.LC474
	.word	.LC476
	.word	.LC445
	.word	.LC457
	.word	.LC459
	.word	.LC460
	.word	.LC446
	.word	.LC486
	.word	.LC453
	.word	.LC456
	.word	.LC488
	.word	.LC440
	.word	.LC477
	.word	.LC479
	.word	.LC480
	.word	.LC439
	.word	.LC447
	.word	.LC470
	.word	.LC455
	.word	.LC444
	.word	.LC441
	.word	.LC443
	.word	.LC468
	.word	.LC462
	.word	.LC487
	.word	.LC473
	.word	.LC465
	.word	.LC482
	.word	.LC478
	.word	.LC466
	.word	.LC472
	.word	.LC475
	.word	.LC450
	.word	.LC458
	.word	.LC461
	.word	.LC484
	.word	.LC448
	.word	.LC463
	.word	.LC454
.L3666:
	ldr	r3, [fp, #-92]
	add	r9, r3, #12288
	ldrb	r6, [r9, #134]	@ zero_extendqisi2
.L3667:
	cmp	r6, #1
	beq	.L3952
.L3668:
	mov	r3, #0
	str	r3, [r5, #2056]
.L3683:
	mov	r6, #0
	b	.L3677
.L3910:
	ldr	r3, [r4, #260]
	mov	r0, r4
	cmp	r3, #0
	ldrne	r3, [r4, #192]
	str	r3, [r5, #708]
	bl	HEVC_IsNewPic
	ldr	r1, .L3954+116
	str	r0, [r5, #848]
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3919:
	ldr	r1, .L3954+120
	ldr	r0, [r4, #2796]
	bl	HEVC_ue_v
	ldr	r3, [r7, #180]
	cmp	r0, r3
	mov	r2, r0
	str	r0, [fp, #-48]
	bhi	.L3953
	cmp	r3, #1
	bls	.L3778
	mov	r2, #0
	mov	r1, r2
	mov	r2, #1
.L3647:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L3647
	str	r1, [fp, #-96]
	str	r1, [fp, #-56]
	b	.L3645
.L3932:
	ldr	r1, .L3954+124
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3782:
	mov	r1, #0
.L3680:
	str	r2, [fp, #-48]
	bl	BsGet
	add	r4, r4, #1
	ldr	r2, [fp, #-48]
	str	r0, [r10, #4]!
	ldr	r3, [r7, #2056]
	cmp	r4, r3
	blt	.L3682
	mov	r4, r5
	mov	r6, #1
	mov	r5, r7
	mov	r7, r2
	str	r3, [fp, #-84]
.L3675:
	ldr	r3, [fp, #-84]
	cmp	r3, #2
	ble	.L3677
	ldr	r2, [fp, #-84]
	mov	r3, #2
	ldr	r1, .L3954+128
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3679
.L3917:
	ldr	r1, .L3954+132
	bl	dprint_vfmw
	b	.L3632
.L3952:
	ldr	r2, [r4, #2800]
	add	r10, r2, r0, lsl #2
	add	r10, r10, #16384
	ldr	r6, [r10, #196]
	cmp	r6, #0
	ble	.L3783
	add	r3, r0, #2064
	mov	r9, #0
	add	r3, r3, #10
	add	ip, r2, #12288
	ldr	lr, [r1, #28]
	mov	r1, r9
	add	r0, r2, r3, lsl #3
.L3687:
	ldr	r3, [r0, #4]!
	add	r1, r1, #1
	add	r3, r3, #1024
	add	r3, r3, #12
	add	r3, ip, r3, lsl #2
	ldr	r2, [r3, #132]
	add	r3, r2, #1040
	add	r3, r3, #2
	add	r3, ip, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, lr
	blt	.L3685
	cmp	lr, #0
	beq	.L3686
	ldr	r3, [r10, #180]
	add	r3, r3, r2, lsl #1
	add	r3, r3, #3088
	add	r3, r3, #10
	add	r3, ip, r3, lsl #2
	ldr	r3, [r3, #132]
	cmp	r3, #0
	beq	.L3685
.L3686:
	add	r9, r9, #1
.L3685:
	cmp	r1, r6
	bne	.L3687
.L3684:
	str	r9, [fp, #-84]
	mov	r6, #0
	str	r9, [r5, #2056]
	b	.L3675
.L3613:
	mov	r2, r0
	ldr	r1, .L3954+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3913:
	mov	r2, r0
	ldr	r1, .L3954+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3670:
	cmp	ip, #1
	streq	ip, [r5, #2056]
	streq	ip, [fp, #-84]
	bne	.L3668
	b	.L3683
.L3931:
	ldr	r1, .L3954+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3707:
	mov	r3, #16
	ldr	r1, .L3954+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3757:
	mov	r2, r0
	mov	r3, r7
	ldr	r1, .L3954+152
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3947:
	mov	r2, r0
	ldr	r1, .L3954+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3726:
	mov	r3, r0
	str	r6, [sp]
	ldr	r1, .L3954+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3939:
	mov	r2, r6
	ldr	r1, .L3954+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3951:
	ldr	r1, .L3954+168
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r8, #76]
	str	r3, [r5, #756]
	b	.L3740
.L3930:
	ldr	r1, .L3954+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3946:
	mov	r2, r0
	ldr	r1, .L3954+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3948:
	mov	r2, r0
	ldr	r1, .L3954+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3920:
	str	r0, [sp]
	mov	ip, #16
	ldr	r1, .L3954+184
	mov	r0, #1
	str	ip, [sp, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3671:
	str	r3, [r5, #2056]
	ldr	r2, [r9, #196]
	cmp	r2, #1
	streq	r3, [fp, #-84]
	beq	.L3689
.L3676:
	add	r10, r4, #6144
	mov	ip, #0
	add	r10, r10, #8
	mov	r2, r7
	mov	r6, #1
	mov	r7, r5
	mov	r5, r4
	mov	r4, ip
.L3682:
	ldr	ip, [r9, #196]
	ldr	r0, [r5, #2796]
	cmp	ip, #1
	bls	.L3782
	mov	r3, #0
.L3681:
	add	r3, r3, #1
	cmp	ip, r6, asl r3
	mov	r1, r3
	bhi	.L3681
	b	.L3680
.L3949:
	mov	r2, r9
	mov	r3, #16
	ldr	r1, .L3954+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3926:
	ldr	r1, .L3954+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3783:
	mov	r9, #0
	b	.L3684
.L3940:
	mov	r2, r7
	ldr	r1, .L3954+196
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3953:
	ldr	r1, .L3954+200
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3927:
	ldr	r1, .L3954+204
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3895
.L3950:
	mov	r3, #2
	ldr	r1, .L3954+208
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3679
.L3781:
	mov	r1, r2
	b	.L3672
.L3778:
	mov	r3, #0
	str	r3, [fp, #-96]
	str	r3, [fp, #-56]
	b	.L3645
	UNWIND(.fnend)
	.size	HEVC_DecSliceSegmentHeader, .-HEVC_DecSliceSegmentHeader
	.align	2
	.global	HEVC_ClearCurrNal
	.type	HEVC_ClearCurrNal, %function
HEVC_ClearCurrNal:
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
	ldr	r1, [r0, #2816]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3957
	ldr	r0, [r0, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L3957:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrNal, .-HEVC_ClearCurrNal
	.align	2
	.global	HEVC_FrameStoreRefFlg
	.type	HEVC_FrameStoreRefFlg, %function
HEVC_FrameStoreRefFlg:
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
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FrameStoreRefFlg, .-HEVC_FrameStoreRefFlg
	.align	2
	.global	HEVC_ClearCurrSlice
	.type	HEVC_ClearCurrSlice, %function
HEVC_ClearCurrSlice:
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
	ldr	r1, [r0, #2816]
	mov	r4, r0
	cmp	r1, #0
	beq	.L3963
	ldr	r0, [r0, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L3963:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrSlice, .-HEVC_ClearCurrSlice
	.align	2
	.global	HEVC_ClearAllSlice
	.type	HEVC_ClearAllSlice, %function
HEVC_ClearAllSlice:
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
	ldr	r3, [r0, #168]
	mov	r5, r0
	cmp	r3, #0
	beq	.L3971
	mov	r4, #0
	mov	r6, r4
.L3970:
	ldr	r3, [r5, #2836]
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L3969
	ldr	r0, [r5, #276]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2836]
	str	r6, [r3, r4, asl #2]
.L3969:
	ldr	r3, [r5, #168]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L3970
.L3971:
	mov	r0, #0
	mov	r3, #2
	str	r0, [r5, #204]
	str	r0, [r5, #268]
	str	r0, [r5, #260]
	strb	r0, [r5, #14]
	str	r3, [r5, #176]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.align	2
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
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
	mov	r4, r0
	mov	r9, r1
	bl	HEVC_ClearAllSlice
	add	r8, r4, #3184
	mov	r6, r4
	add	r8, r8, #8
	mov	r5, #17
	mov	r7, #0
.L3984:
	ldr	r3, [r8, #4]!
	cmp	r3, #0
	beq	.L3978
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L3978:
	ldr	r3, [r6, #3264]
	cmp	r3, #0
	beq	.L3979
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L3979:
	ldr	r3, [r6, #3332]
	cmp	r3, #0
	beq	.L3980
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L3980:
	ldr	r3, [r6, #3400]
	cmp	r3, #0
	beq	.L3981
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L3981:
	ldr	r3, [r6, #3060]
	str	r7, [r6, #3400]
	cmp	r3, #0
	str	r7, [r6, #3332]
	str	r7, [r6, #3264]
	str	r7, [r6, #3196]
	beq	.L3982
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L3982:
	ldr	r3, [r6, #3128]
	cmp	r3, #0
	beq	.L3983
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #276]
	bl	FSP_ClearLogicFs
.L3983:
	subs	r5, r5, #1
	str	r7, [r6, #3128]
	str	r7, [r6, #3060]
	add	r6, r6, #4
	bne	.L3984
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4048
.L3985:
	ldr	r3, [r4, #2828]
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r4, #3024]
.L3987:
	cmp	r3, #17
	bhi	.L4049
.L3988:
	ldr	r3, .L4057
	mov	r7, #0
	add	r0, r4, #13120
	mov	r1, r7
	mov	r2, #280
	str	r7, [r4, #3028]
	ldr	r3, [r3, #48]
	add	r0, r0, #28
	str	r7, [r4, #3040]
	add	r10, r4, #12288
	str	r7, [r4, #3044]
	mov	r6, #16
	str	r7, [r4, #3036]
	str	r7, [r4, #3032]
	str	r7, [r4, #3052]
	str	r7, [r4, #3056]
	blx	r3
	ldr	r3, .L4057
	add	r0, r4, #13376
	mov	r2, #280
	str	r7, [r10, #864]
	mov	r1, r7
	ldr	r3, [r3, #48]
	add	r0, r0, #52
	str	r6, [r10, #860]
	blx	r3
	add	r2, r4, #2848
	add	r3, r4, #2912
	add	r2, r2, #4
	add	r3, r3, #8
	mov	r0, r7
	str	r6, [r10, #1140]
	str	r7, [r10, #1144]
.L3989:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3989
	add	r2, r4, #2976
	add	r0, r4, #4096
	add	r2, r2, #12
	mov	ip, r1
	str	r1, [r0, #764]
.L3990:
	str	ip, [r3, #4]!
	cmp	r3, r2
	mov	r1, #0
	bne	.L3990
	cmp	r9, r1
	str	r1, [r0, #768]
	bne	.L3991
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	beq	.L3991
.L3992:
	ldr	r1, [r4, #184]
	cmp	r1, #0
	addne	r2, r4, #2144
	movne	r3, #0
	addne	r2, r2, #8
	movne	r0, r3
	beq	.L4009
.L4008:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L4008
.L4009:
	ldr	r3, [r4, #168]
	cmp	r3, #0
	movne	r5, #0
	movne	r6, r5
	beq	.L4007
.L4011:
	ldr	r3, [r4, #2836]
	mov	r7, r5, asl #2
	ldr	r3, [r3, r5, asl #2]
	add	r5, r5, #1
	cmp	r3, #0
	mov	r1, r3
	beq	.L4010
	ldr	r2, [r4, #2816]
	cmp	r3, r2
	beq	.L4010
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r4, #2836]
	str	r6, [r3, r7]
.L4010:
	ldr	r3, [r4, #168]
	cmp	r3, r5
	bhi	.L4011
.L4007:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3991:
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	mov	r3, #20
	str	r3, [r4, #180]
	cmp	r2, #1
	str	r3, [r4, #184]
	beq	.L4050
.L3993:
	mov	r0, r4
	bl	HEVC_ArrangeMem
.L4015:
	cmp	r0, #0
	beq	.L4001
	cmp	r0, #2
	beq	.L4051
.L4002:
	ldr	r2, .L4057+4
	mov	r0, #0
	ldr	r1, .L4057+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4049:
	mov	r6, #17
	ldr	r2, .L4057+4
	str	r6, [sp]
	mov	r3, r6
	ldr	r1, .L4057+12
	mov	r0, #1
	bl	dprint_vfmw
	str	r6, [r4, #3024]
	b	.L3988
.L4048:
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L3985
	ldr	r2, [r4, #2380]
	cmp	r2, #0
	beq	.L3985
	ldr	r3, [r4, #2828]
	ldr	r3, [r3, #184]
	mul	r3, r3, r2
	add	r3, r3, #1
	str	r3, [r4, #3024]
	b	.L3987
.L4001:
	ldr	r0, [r4, #276]
	bl	FSP_GetTotalValidFsNum
	cmp	r0, #20
	movgt	r0, #20
	ble	.L4052
.L4004:
	str	r0, [r4, #180]
	b	.L3992
.L4050:
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L3993
	ldr	r3, [r4, #2380]
	ldr	r10, [r4, #2828]
	cmp	r3, #0
	str	r3, [fp, #-88]
	beq	.L4053
	ldr	r2, [r10, #140]
	mov	r6, #0
	ldr	r3, [r10, #144]
	mov	r7, r6
	rsb	r1, r2, #0
	str	r1, [fp, #-76]
	ldr	r1, [r4, #3024]
	sub	r2, r2, #1
	ldr	r9, [r0, #728]
	movw	r0, #8160
	str	r2, [fp, #-80]
	rsb	r2, r3, #0
	str	r1, [fp, #-92]
	sub	r3, r3, #1
	str	r2, [fp, #-72]
	str	r3, [fp, #-84]
	mov	r3, r6
	b	.L3998
.L3996:
	cmp	r7, r1
	movcc	r7, r1
	cmp	r6, r2
	sub	r1, r7, #32
	movcc	r6, r2
	sub	r2, r6, #32
	cmp	r1, r0
	cmpls	r2, r0
	movhi	r1, #1
	movls	r1, #0
	bhi	.L4054
	ldr	r2, [fp, #-88]
	uxtb	r3, ip
	cmp	r2, r3
	mov	r5, r3
	bls	.L4055
.L3998:
	add	r2, r4, r3, lsl #2
	ldr	lr, [fp, #-80]
	cmp	r9, r5
	add	ip, r3, #1
	ldr	r1, [r2, #2388]
	ldr	r2, [r2, #2396]
	add	r1, lr, r1
	ldr	lr, [fp, #-84]
	add	r2, lr, r2
	ldr	lr, [fp, #-76]
	and	r1, r1, lr
	ldr	lr, [fp, #-72]
	and	r2, r2, lr
	bne	.L3996
	ldr	r5, [r10, #188]
	ldr	lr, [r10, #128]
	ldr	r8, [r10, #192]
	mov	r5, r5, asl lr
	cmp	r1, r5
	mov	lr, r8, asl lr
	movcc	r1, r5
	cmp	r2, lr
	movcc	r2, lr
	b	.L3996
.L4054:
	str	r6, [sp, #4]
	mov	r0, #0
	str	r7, [sp]
	ldr	r2, .L4057+16
	ldr	r1, .L4057+20
	bl	dprint_vfmw
	b	.L4002
.L4051:
	add	r0, r4, #6144
	add	r0, r0, #24
	bl	ResetVoQueue
	mvn	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4055:
	ldr	r3, .L4057
	mov	r2, #20
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2844]
	str	r7, [fp, #-60]
	str	r6, [fp, #-56]
	ldr	r3, [r3, #28]
	str	r7, [fp, #-52]
	cmp	r3, #24
	str	r6, [fp, #-48]
	beq	.L3999
	ldrb	r3, [fp, #-92]	@ zero_extendqisi2
	strb	r3, [fp, #-63]
.L4016:
	sub	r1, fp, #64
	ldr	r0, [r4, #276]
	strb	r3, [fp, #-61]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L4056
	ldr	r1, [r4, #2844]
	sub	r3, fp, #68
	ldr	r0, [r4, #276]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	b	.L4015
.L4052:
	ldr	r0, [r4, #276]
	bl	FSP_GetTotalValidFsNum
	b	.L4004
.L3999:
	mov	r3, #1
	strb	r3, [fp, #-63]
	b	.L4016
.L4053:
	ldr	r3, [fp, #-88]
	ldr	r2, .L4057+16
	ldr	r1, .L4057+24
	mov	r0, r3
	bl	dprint_vfmw
	b	.L4002
.L4056:
	ldr	r2, .L4057+16
	mov	r0, #1
	ldr	r1, .L4057+28
	bl	dprint_vfmw
	b	.L4002
.L4058:
	.align	2
.L4057:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+680
	.word	.LC491
	.word	.LC158
	.word	.LANCHOR0+696
	.word	.LC490
	.word	.LC489
	.word	.LC95
	UNWIND(.fnend)
	.size	HEVC_InitDPB, .-HEVC_InitDPB
	.align	2
	.global	HEVC_ClearAllNal
	.type	HEVC_ClearAllNal, %function
HEVC_ClearAllNal:
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
	ldr	r3, [r0, #168]
	mov	r6, r0
	cmn	r3, #1
	beq	.L4063
	mov	r4, #0
	mov	r5, r4
	b	.L4062
.L4061:
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r5
	bls	.L4063
.L4062:
	ldr	r1, [r6, #2840]
	add	r5, r5, #1
	add	r1, r1, r4
	add	r4, r4, #96
	ldr	r3, [r1, #32]
	cmp	r3, #1
	bne	.L4061
	ldr	r0, [r6, #276]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L4062
.L4063:
	mov	r0, #0
	strb	r0, [r6, #9]
	str	r0, [r6, #148]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllNal, .-HEVC_ClearAllNal
	.align	2
	.global	HEVC_InitDecPara
	.type	HEVC_InitDecPara, %function
HEVC_InitDecPara:
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
	ldr	r1, .L4082
	mov	r7, r0
	mov	r0, #22
	mov	r8, #0
	bl	dprint_vfmw
	mov	r3, #-2147483647
	mov	r1, #1
	mvn	r2, #-2147483648
	strb	r8, [r7, #4]
	mov	r0, r7
	strb	r8, [r7, #12]
	add	r4, r7, #13760
	strb	r8, [r7, #5]
	mov	r6, r8
	strb	r8, [r7, #13]
	mov	r5, r8
	str	r3, [r7, #212]
	add	r4, r4, #32
	str	r3, [r7, #252]
	mov	r9, #20
	str	r3, [r7, #216]
	str	r3, [r7, #256]
	strb	r1, [r7, #6]
	strb	r1, [r7, #7]
	str	r2, [r7, #244]
	str	r2, [r7, #248]
	bl	HEVC_ClearAllNal
	add	r0, r7, #6144
	add	r0, r0, #24
	ldr	r8, .L4082+4
	bl	ResetVoQueue
.L4067:
	strb	r5, [r4, #-80]
	mov	r3, #16
	str	r5, [r4, #-32]
	mov	r0, r4
	strb	r5, [r4, #-79]
	mov	r2, #632
	str	r5, [r4, #-72]
	mov	r1, #0
	strb	r5, [r4, #-78]
	str	r9, [r4, #-60]
	str	r3, [r4, #-56]
	ldr	r3, [r8, #48]
	blx	r3
	str	r6, [r4, #148]
	add	r6, r6, #1
	sub	r3, r4, #80
	cmp	r6, #20
	str	r5, [r4, #-24]
	str	r3, [r4, #-4]
	add	r4, r4, #712
	bne	.L4067
	add	r3, r7, #2144
	add	r2, r7, #2224
	add	r3, r3, #8
	add	r2, r2, #8
	mov	r1, #0
.L4068:
	str	r1, [r3, #4]!
	cmp	r3, r2
	bne	.L4068
	ldr	r3, [r7, #168]
	cmp	r3, #0
	beq	.L4069
	mov	r3, #0
	mov	r1, r3
.L4070:
	ldr	r2, [r7, #2836]
	str	r1, [r2, r3, asl #2]
	add	r3, r3, #1
	ldr	r2, [r7, #168]
	cmp	r2, r3
	bhi	.L4070
.L4069:
	add	r0, r7, #13120
	ldr	r3, [r8, #48]
	mov	r2, #280
	mov	r1, #0
	add	r4, r7, #12288
	add	r0, r0, #28
	blx	r3
	add	r0, r7, #13376
	mov	r5, #16
	mov	r2, #280
	ldr	r3, [r8, #48]
	mov	r1, #0
	add	r0, r0, #52
	str	r5, [r4, #860]
	blx	r3
	add	ip, r7, #3392
	add	r0, r7, #3248
	add	r1, r7, #3184
	add	ip, ip, #4
	add	r0, r0, #12
	add	r1, r1, #8
	add	lr, r7, #3328
	mov	r2, #17
	mov	r3, #0
	str	r5, [r4, #1140]
.L4071:
	subs	r2, r2, #1
	str	r3, [ip, #4]!
	str	r3, [lr, #4]!
	str	r3, [r0, #4]!
	str	r3, [r1, #4]!
	bne	.L4071
	add	r3, r7, #2912
	add	r0, r7, #2848
	add	r1, r7, #2976
	add	r3, r3, #8
	add	r0, r0, #4
	add	r1, r1, #12
	mov	ip, r2
	mov	lr, #17
	str	r2, [r7, #3028]
	str	r2, [r7, #3032]
	str	r2, [r7, #3036]
	str	r2, [r7, #3040]
	str	r2, [r7, #3044]
	str	lr, [r7, #3024]
.L4072:
	str	ip, [r3, #4]!
	cmp	r3, r1
	str	ip, [r0, #4]!
	mov	r4, #0
	bne	.L4072
	add	r0, r7, #4736
	mov	r5, #2
	mov	r1, r4
	ldr	r3, [r8, #48]
	str	r4, [r7, #2816]
	mov	r2, #1376
	str	r4, [r7, #204]
	add	r0, r0, #56
	str	r4, [r7, #268]
	add	r6, r7, #2992
	str	r4, [r7, #260]
	mov	r9, #16
	str	r5, [r7, #176]
	blx	r3
	add	r2, r7, #4096
	mov	r3, #1
	mov	ip, #8
	str	r5, [r2, #716]
	mov	r1, r4
	str	r3, [r2, #848]
	mov	lr, #64
	mov	r2, #20
	strb	r3, [r7, #3]
	strb	r4, [r7, #8]
	mov	r3, #6
	str	r5, [r7, #2248]
	mov	r0, r6
	ldr	r5, [r8, #48]
	mov	r8, #256
	str	r4, [r7, #172]
	movw	r4, #1025
	str	r2, [r7, #180]
	str	r2, [r7, #184]
	mov	r2, #32
	str	ip, [r7, #196]
	str	ip, [r7, #200]
	str	r9, [r7, #348]
	str	lr, [r7, #352]
	str	r8, [r7, #356]
	str	r4, [r7, #360]
	str	r3, [r7, #2236]
	str	r3, [r7, #2240]
	str	r3, [r7, #2244]
	blx	r5
	str	r6, [r7, #2796]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4083:
	.align	2
.L4082:
	.word	.LC492
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_InitDecPara, .-HEVC_InitDecPara
	.align	2
	.global	HEVC_ClearCurrPic
	.type	HEVC_ClearCurrPic, %function
HEVC_ClearCurrPic:
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
	add	r4, r0, #4096
	mov	r5, r0
	bl	HEVC_ClearAllSlice
	ldr	r3, [r4, #60]
	cmp	r3, #0
	beq	.L4085
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r5, #276]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #60]
	mov	r3, #0
	str	r3, [r2, #48]
	str	r3, [r4, #60]
.L4085:
	mov	r0, #0
	strb	r0, [r4, #1]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearCurrPic, .-HEVC_ClearCurrPic
	.align	2
	.global	HEVC_ClearAll
	.type	HEVC_ClearAll, %function
HEVC_ClearAll:
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
	mov	r4, r0
	mov	r5, r1
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	cmp	r5, #0
	bne	.L4092
	add	r0, r4, #6144
	add	r0, r0, #24
	bl	ResetVoQueue
	ldr	r0, [r4, #276]
	bl	FSP_EmptyInstance
.L4091:
	mov	r0, r4
	bl	HEVC_InitDecPara
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4092:
	add	r1, r4, #6144
	ldr	r0, [r4, #276]
	add	r1, r1, #24
	bl	FSP_ClearNotInVoQueue
	b	.L4091
	UNWIND(.fnend)
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.align	2
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldr	r1, [r0, #292]
	ldr	r3, [r0, #288]
	add	r2, r0, #4096
	mov	r6, r0
	mov	r9, r1
	str	r1, [fp, #-80]
	ldr	r1, [r0, #296]
	str	r3, [fp, #-72]
	ldr	r3, [r2, #732]
	str	r1, [fp, #-76]
	ldr	r1, [r0, #300]
	cmp	r3, #0
	mov	r10, r1
	str	r1, [fp, #-84]
	blt	.L4122
	ldr	r1, [r0, #164]
	cmp	r3, r1
	bge	.L4122
	ldr	r0, [r0, #2808]
	movw	r5, #5036
	movw	r1, #12668
	ldr	r2, [r2, #728]
	ldr	r8, [r6, #2804]
	movw	ip, #24912
	mla	r5, r5, r3, r0
	add	r2, r6, r2, lsl #2
	ldr	r0, [r6, #2800]
	ldr	r7, [r5, #32]
	mul	r7, r1, r7
	add	r1, r8, r7
	str	r1, [fp, #-64]
	mov	lr, r1
	ldr	r1, [r1, #48]
	str	r3, [r2, #236]
	ldr	r3, [r5, #32]
	mla	r1, ip, r1, r0
	str	r3, [r2, #228]
	ldr	r3, [lr, #48]
	str	r3, [r2, #220]
	ldr	r4, [lr, #128]
	ldr	r2, [r6, #172]
	ldr	r3, [lr, #64]
	subs	r4, r10, r4
	clz	r2, r2
	movne	r4, #1
	cmp	r9, r3
	mov	r0, r2
	mov	r3, r0, lsr #5
	str	r3, [fp, #-68]
	movne	r3, #1
	strne	r3, [fp, #-88]
	beq	.L4145
.L4095:
	ldr	r3, [r6, #2824]
	ldr	r2, [fp, #-68]
	ldr	r0, [fp, #-88]
	orr	r4, r4, r2
	ldr	r3, [r3, #4]
	ldr	r2, [r1, #4]
	orr	r4, r0, r4
	cmp	r3, r2
	movne	r3, #1
	beq	.L4146
.L4096:
	ldr	r2, [fp, #-68]
	orrs	r3, r3, r2
	beq	.L4097
	mov	r0, r6
	bl	HEVC_UpdatePicVPS
.L4097:
	ldr	r3, [r6, #2828]
	ldr	r2, [fp, #-64]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #56]
	cmp	r1, r2
	movne	r2, #1
	beq	.L4147
.L4098:
	orrs	r2, r2, r4
	streq	r2, [fp, #-92]
	beq	.L4099
	ldr	r2, [fp, #-64]
	mov	r0, r6
	ldr	r3, [r3, #184]
	mov	r1, r2
	ldr	r2, [r2, #184]
	subs	r3, r2, r3
	movne	r3, #1
	str	r3, [fp, #-92]
	bl	HEVC_UpdatePicSPS
.L4099:
	ldr	r2, [r6, #2832]
	ldr	r3, [r5, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	movne	r3, #1
	beq	.L4148
.L4100:
	orrs	r3, r3, r4
	beq	.L4101
	mov	r2, r5
	ldr	r1, [fp, #-64]
	mov	r0, r6
	bl	HEVC_UpdatePicPPS
.L4101:
	ldr	r2, [r6, #2828]
	ldr	r1, [r6, #2844]
	ldr	r3, [r2, #96]
	ldr	r2, [r2, #88]
	cmp	r3, r2
	movcc	r3, r2
	str	r3, [r1, #900]
	ldr	r3, [r6, #2824]
	str	r3, [fp, #-60]
	add	r3, r3, #16384
	ldr	ip, [r3, #160]
	cmp	ip, #0
	beq	.L4115
	add	r10, ip, #1
	add	r3, r6, #2384
	cmp	r10, #2
	str	r3, [fp, #-52]
	mov	r9, #0
	ldr	r3, [fp, #-60]
	movcs	r10, #2
	cmp	r9, r10
	add	r3, r3, #24832
	str	r10, [r6, #2380]
	str	r3, [fp, #-48]
	bcs	.L4115
.L4114:
	add	r3, r9, #1
	ldr	r4, [r6, #2824]
	cmp	r3, r10
	str	r3, [fp, #-56]
	bcs	.L4112
	mov	r2, r9, asl #5
	add	r8, r4, #12288
	add	r2, r2, r9, lsl #3
	ldr	r3, [fp, #-60]
	add	r8, r8, r2
	ldr	r2, [fp, #-48]
	rsb	r3, r3, #40
	add	r7, r8, #12480
	add	r3, r3, r2
	add	r8, r8, #12544
	add	r7, r7, #60
	add	r8, r8, #4
	add	r4, r4, r3
	ldr	r5, [fp, #-56]
	b	.L4111
.L4109:
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4110
	mov	r3, #1
	strb	r3, [r6, #2]
	ldr	ip, [r4, #4]
	ldr	r3, [r7, #4]
	str	ip, [sp, #12]
	ldr	ip, [r4]
	stmib	sp, {r5, ip}
	ldr	ip, [r8]
	str	ip, [sp]
	bl	dprint_vfmw
.L4110:
	add	r5, r5, #1
	add	r4, r4, #40
	cmp	r5, r10
	bcs	.L4112
.L4111:
	ldr	ip, [r7, #4]
	mov	r2, r9
	ldr	r3, [r4]
	mov	r0, #32
	ldr	r1, .L4150
	cmp	ip, r3
	bne	.L4109
	ldr	ip, [r8]
	ldr	r3, [r4, #4]
	cmp	ip, r3
	bne	.L4109
	add	r5, r5, #1
	add	r4, r4, #40
	cmp	r5, r10
	bcc	.L4111
.L4112:
	ldr	r1, [fp, #-52]
	ldr	r3, [fp, #-48]
	ldr	r2, [r1, #4]!
	ldr	r3, [r3]
	cmp	r2, r3
	str	r1, [fp, #-52]
	bne	.L4107
	ldr	r2, [fp, #-52]
	ldr	r1, [r2, #8]
	ldr	r2, [fp, #-48]
	ldr	r2, [r2, #4]
	cmp	r1, r2
	beq	.L4113
.L4107:
	ldr	lr, [fp, #-52]
	mov	r0, #32
	ldr	r2, [fp, #-48]
	ldr	r1, .L4150+4
	str	r3, [lr]
	ldr	ip, [r2, #4]
	mov	r2, r9
	str	ip, [lr, #8]
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r6, #2384]
.L4113:
	ldr	r10, [r6, #2380]
	ldr	r9, [fp, #-56]
	ldr	r3, [fp, #-48]
	cmp	r9, r10
	add	r3, r3, #40
	str	r3, [fp, #-48]
	bcc	.L4114
.L4115:
	ldr	r3, [r6, #2356]
	cmp	r3, #0
	bne	.L4104
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-72]
	ldr	r3, [r3, #56]
	cmp	r2, r3
	beq	.L4149
.L4116:
	ldr	r3, [fp, #-92]
	mov	r0, r6
	ldr	r2, [fp, #-76]
	ldr	r1, [fp, #-80]
	str	r3, [sp]
	ldr	r3, [fp, #-84]
	bl	HEVC_GetReRangeFlag
	cmp	r0, #0
	bne	.L4118
	ldr	r3, [r6, #2844]
	ldr	r2, [r3, #888]
	cmp	r2, #1
	beq	.L4118
.L4119:
	mov	r2, #0
	str	r2, [r3, #904]
.L4117:
	mov	r0, r6
	bl	HEVC_AllocFrameStore
	subs	r4, r0, #0
	beq	.L4104
	ldr	r1, .L4150+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	b	.L4094
.L4122:
	mov	r0, #0
.L4094:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4104:
	mov	r0, r6
	bl	HEVC_InitPicInfo
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4118:
	mov	r1, #1
	mov	r0, r6
	bl	HEVC_InitDPB
	cmn	r0, #2
	beq	.L4094
	cmp	r0, #0
	bne	.L4120
	ldr	r3, [r6, #2844]
	b	.L4119
.L4148:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	adds	r3, r3, #0
	movne	r3, #1
	b	.L4100
.L4147:
	ldrb	r2, [r8, r7]	@ zero_extendqisi2
	adds	r2, r2, #0
	movne	r2, #1
	b	.L4098
.L4146:
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	adds	r3, r3, #0
	movne	r3, #1
	b	.L4096
.L4145:
	ldr	r3, [lr, #68]
	ldr	r2, [fp, #-76]
	subs	r3, r2, r3
	movne	r3, #1
	str	r3, [fp, #-88]
	b	.L4095
.L4149:
	ldr	r2, [fp, #-68]
	ldr	r3, [fp, #-88]
	orr	r3, r3, r2
	ldr	r2, [fp, #-92]
	orrs	r3, r3, r2
	bne	.L4116
	ldr	r3, [r6, #2844]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L4117
	b	.L4116
.L4120:
	mov	r2, r0
	ldr	r1, .L4150+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L4094
.L4151:
	.align	2
.L4150:
	.word	.LC493
	.word	.LC494
	.word	.LC496
	.word	.LC495
	UNWIND(.fnend)
	.size	HEVC_InitPic, .-HEVC_InitPic
	.align	2
	.global	HEVC_OutputCurrPic
	.type	HEVC_OutputCurrPic, %function
HEVC_OutputCurrPic:
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
	add	r6, r0, #4096
	add	r1, r0, #4160
	mov	r4, r0
	mov	r2, #632
	ldr	r5, [r6, #60]
	ldr	r3, [r6, #40]
	add	r0, r5, #80
	str	r3, [r5, #16]
	bl	memcpy
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_GetImagePara
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4159
.L4153:
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_OutputFrame
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r2, .L4160
	mov	r0, #0
	ldr	r1, .L4160+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4159:
	mov	r2, #1
	ldr	r1, [r5, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetRef
	b	.L4153
.L4161:
	.align	2
.L4160:
	.word	.LANCHOR0+716
	.word	.LC497
	UNWIND(.fnend)
	.size	HEVC_OutputCurrPic, .-HEVC_OutputCurrPic
	.align	2
	.global	HEVC_FirstFrameFastOut
	.type	HEVC_FirstFrameFastOut, %function
HEVC_FirstFrameFastOut:
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
	mov	r4, r0
	bl	HEVC_OutputCurrPic
	subs	r5, r0, #0
	bne	.L4165
	add	r3, r4, #4096
	add	r1, r4, #8192
	mov	r2, #1
	mov	ip, #2
	ldr	r0, [r3, #60]
	str	ip, [r0, #52]
	str	r2, [r1, #3576]
	ldr	r0, [r3, #8]
	ldr	r1, [r3, #12]
	add	r4, r4, r0, lsl #2
	mov	r0, r5
	str	r1, [r4, #212]
	ldr	r3, [r3, #60]
	strb	r2, [r3, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4165:
	ldr	r2, .L4166
	mov	r0, #1
	ldr	r1, .L4166+4
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4167:
	.align	2
.L4166:
	.word	.LANCHOR0+736
	.word	.LC498
	UNWIND(.fnend)
	.size	HEVC_FirstFrameFastOut, .-HEVC_FirstFrameFastOut
	.align	2
	.global	HEVC_OutputFrmToVO
	.type	HEVC_OutputFrmToVO, %function
HEVC_OutputFrmToVO:
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
	mov	r4, r0
	mov	r5, r1
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r6, r0, #0
	beq	.L4176
	cmn	r6, #3
	bne	.L4177
.L4172:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4176:
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_OutputFrame
	cmp	r0, #0
	beq	.L4172
	ldr	r2, .L4178
	mov	r0, r6
	ldr	r1, .L4178+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4177:
	mov	r3, r6
	movw	r2, #11772
	ldr	r1, .L4178+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #228]
	mov	r0, r4
	bl	HEVC_DECRecycleImage
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4179:
	.align	2
.L4178:
	.word	.LANCHOR0+760
	.word	.LC497
	.word	.LC499
	UNWIND(.fnend)
	.size	HEVC_OutputFrmToVO, .-HEVC_OutputFrmToVO
	.align	2
	.global	HEVC_DirectOutput
	.type	HEVC_DirectOutput, %function
HEVC_DirectOutput:
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
	add	r6, r0, #4096
	mov	ip, #2
	mov	r5, #0
	mov	r3, #1
	ldr	r4, [r6, #60]
	mov	r7, r0
	add	r1, r0, #4160
	mov	r2, #632
	add	r0, r4, #80
	str	ip, [r4, #48]
	strb	r3, [r4, #2]
	strb	r5, [r4, #1]
	ldr	r3, [r6, #16]
	str	r3, [r4, #12]
	ldr	r3, [r6, #40]
	str	r3, [r4, #16]
	bl	memcpy
	mov	r2, r5
	str	r5, [r4, #56]
	ldr	r1, [r4, #28]
	ldr	r0, [r7, #276]
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r7
	bl	HEVC_OutputFrmToVO
	ldr	r3, .L4181
	str	r5, [r4, #48]
	mov	r1, r5
	mov	r2, #696
	ldr	r3, [r3, #48]
	mov	r7, r0
	mov	r0, r6
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4182:
	.align	2
.L4181:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	HEVC_DirectOutput, .-HEVC_DirectOutput
	.align	2
	.global	HEVC_IModeProcess
	.type	HEVC_IModeProcess, %function
HEVC_IModeProcess:
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
	mov	r4, r0
	bl	HEVC_DirectOutput
	add	r2, r4, #4096
	ldr	r1, [r4, #184]
	ldr	r3, [r2, #36]
	cmp	r3, r1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r3, r3, #536
	mov	ip, #0
	add	r3, r3, #2
	add	r3, r4, r3, lsl #2
	str	ip, [r3, #4]
	str	r1, [r2, #36]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IModeProcess, .-HEVC_IModeProcess
	.align	2
	.global	HEVC_OutputFrmFromDPB
	.type	HEVC_OutputFrmFromDPB, %function
HEVC_OutputFrmFromDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	ldr	ip, [r0, #3028]
	add	r9, r0, #4096
	mov	r6, r0
	cmp	ip, #0
	ldr	r7, [r9, #8]
	beq	.L4200
	add	lr, r7, #52
	add	r1, r0, #3184
	mov	r3, #0
	add	r1, r1, #8
	str	r3, [fp, #-48]
	add	lr, r0, lr, lsl #2
	b	.L4188
.L4187:
	cmp	r3, ip
	beq	.L4186
.L4188:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L4187
	ldr	r0, [r2, #32]
	cmp	r0, r7
	bne	.L4187
	ldr	r0, [r2, #8]
	ldr	r2, [lr, #4]
	cmp	r0, r2
	ldrgt	r2, [fp, #-48]
	addgt	r2, r2, #1
	strgt	r2, [fp, #-48]
	cmp	r3, ip
	bne	.L4188
.L4186:
	ldr	r3, [r6, #2364]
	cmp	r3, #1
	beq	.L4212
	ldr	r3, [r9, #720]
	ldr	r2, [r6, #2828]
	add	r3, r3, #90
	ldr	r10, [r2, r3, asl #2]
.L4190:
	cmp	ip, #0
	beq	.L4201
	add	r8, r7, #52
	add	r5, r6, #3184
	mov	r4, #0
	add	r5, r5, #8
	add	r8, r6, r8, lsl #2
	str	r4, [fp, #-52]
	b	.L4198
.L4192:
	ldr	r3, [r8, #4]
.L4194:
	cmp	r3, #0
	bne	.L4196
	ldr	r2, [r1, #8]
	cmp	r2, #0
	bge	.L4196
	cmp	r0, #0
	beq	.L4213
.L4197:
	str	r2, [sp]
	mov	r0, #31
	ldr	r2, .L4214
	ldr	r1, .L4214+4
	bl	dprint_vfmw
.L4196:
	ldr	r3, [r6, #3028]
	add	r4, r4, #1
	cmp	r3, r4
	bls	.L4211
.L4198:
	ldr	r1, [r5, #4]!
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L4192
	ldr	r3, [r1, #32]
	cmp	r3, r7
	bne	.L4192
	add	r2, r6, r7, lsl #2
	ldr	ip, [r1, #8]
	ldr	r3, [r2, #212]
	str	ip, [fp, #-56]
	cmp	ip, r3
	ble	.L4194
	ldr	lr, [fp, #-48]
	ldr	ip, [r9, #720]
	cmp	lr, r10
	movhi	lr, #1
	movls	lr, #0
	cmp	ip, #7
	movhi	lr, #0
	cmp	lr, #0
	beq	.L4194
	ldr	lr, [r9, #708]
	ldr	ip, [fp, #-56]
	cmp	ip, lr
	blt	.L4195
	add	ip, r6, r7
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L4194
.L4195:
	mov	r3, #1
	strb	r3, [r1, #2]
	ldr	r3, [fp, #-48]
	mov	r0, r6
	ldr	r1, [r5]
	add	r4, r4, #1
	sub	r3, r3, #1
	str	r2, [fp, #-56]
	str	r3, [fp, #-48]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r5]
	ldr	r2, [fp, #-56]
	ldr	r3, [r3, #8]
	str	r3, [r2, #212]
	ldr	r3, [r6, #3028]
	cmp	r3, r4
	str	r0, [fp, #-52]
	bhi	.L4198
.L4211:
	ldr	r0, [fp, #-52]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4213:
	mov	r2, r3
	ldr	r1, [r1, #28]
	ldr	r0, [r6, #276]
	bl	FSP_SetDisplay
	ldr	r2, [r5]
	ldr	r3, [r8, #4]
	ldr	r2, [r2, #8]
	b	.L4197
.L4212:
	ldr	r1, [r6, #2828]
	mov	r10, #0
	add	r3, r1, #356
	add	r1, r1, #388
.L4189:
	ldr	r2, [r3, #4]!
	cmp	r10, r2
	movcc	r10, r2
	cmp	r3, r1
	bne	.L4189
	b	.L4190
.L4200:
	str	ip, [fp, #-48]
	b	.L4186
.L4201:
	str	ip, [fp, #-52]
	b	.L4211
.L4215:
	.align	2
.L4214:
	.word	.LANCHOR0+780
	.word	.LC500
	UNWIND(.fnend)
	.size	HEVC_OutputFrmFromDPB, .-HEVC_OutputFrmFromDPB
	.align	2
	.global	HEVC_OutputOneFrmFromDPB
	.type	HEVC_OutputOneFrmFromDPB, %function
HEVC_OutputOneFrmFromDPB:
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
	add	r4, r0, r1, lsl #2
	mov	r2, #1
	mov	r6, r1
	mov	r5, r0
	ldr	r3, [r4, #3196]
	strb	r2, [r3, #2]
	ldr	r1, [r4, #3196]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r4, #3196]
	ldr	r2, [r3, #32]
	ldr	r1, [r3, #8]
	add	r2, r5, r2, lsl #2
	str	r1, [r2, #212]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L4217
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
.L4217:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_OutputOneFrmFromDPB, .-HEVC_OutputOneFrmFromDPB
	.align	2
	.global	HEVC_OutputUnRefPicWithMinPoc
	.type	HEVC_OutputUnRefPicWithMinPoc, %function
HEVC_OutputUnRefPicWithMinPoc:
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
	sub	r1, fp, #24
	mov	r4, r0
	bl	HEVC_GetUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L4222
	mov	r0, r4
	ldr	r1, [fp, #-24]
	bl	HEVC_OutputOneFrmFromDPB
	cmp	r0, #0
	bne	.L4223
.L4220:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4222:
	ldr	r2, .L4224
	mov	r0, #1
	ldr	r1, .L4224+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4220
.L4223:
	ldr	r2, .L4224
	mov	r0, #1
	ldr	r1, .L4224+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4220
.L4225:
	.align	2
.L4224:
	.word	.LANCHOR0+804
	.word	.LC501
	.word	.LC502
	UNWIND(.fnend)
	.size	HEVC_OutputUnRefPicWithMinPoc, .-HEVC_OutputUnRefPicWithMinPoc
	.align	2
	.global	HEVC_FlushOutputFrmFromDPB
	.type	HEVC_FlushOutputFrmFromDPB, %function
HEVC_FlushOutputFrmFromDPB:
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
	subs	r4, r0, #0
	beq	.L4235
	ldr	r3, [r4, #3028]
	cmp	r3, #0
	addne	r5, r4, #3184
	movne	r6, #0
	addne	r5, r5, #8
	movne	r8, #1
	bne	.L4233
	b	.L4234
.L4241:
	strb	r8, [r3, #2]
	ldr	r1, [r5]
	bl	HEVC_OutputFrmToVO
	cmn	r0, #1
	mov	r9, r0
	beq	.L4240
.L4231:
	ldr	r3, [r4, #3028]
	cmp	r3, r6
	bls	.L4234
.L4233:
	ldr	r3, [r5, #4]!
	mov	r2, #0
	ldr	r0, [r4, #276]
	add	r6, r6, #1
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r3, [r5]
	mov	r0, r4
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L4241
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #276]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L4231
	ldr	r3, [r5]
	ldr	r0, [r4, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #3028]
	cmp	r3, r6
	bhi	.L4233
.L4234:
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	mov	r9, #0
	str	r3, [r4, #216]
	bl	HEVC_InitDecBuffers
.L4227:
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4240:
	mov	r0, r7
	ldr	r2, .L4242
	ldr	r1, .L4242+4
	bl	dprint_vfmw
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4235:
	mvn	r9, #0
	b	.L4227
.L4243:
	.align	2
.L4242:
	.word	.LANCHOR0+836
	.word	.LC503
	UNWIND(.fnend)
	.size	HEVC_FlushOutputFrmFromDPB, .-HEVC_FlushOutputFrmFromDPB
	.align	2
	.global	HEVC_ReceivePacket
	.type	HEVC_ReceivePacket, %function
HEVC_ReceivePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r6, [r0, #2816]
	mov	r3, #0
	mov	r4, r0
	cmp	r6, r3
	str	r3, [r0, #344]
	beq	.L4274
	ldrb	r3, [r1]	@ zero_extendqisi2
	str	r3, [r6, #36]
	ldr	r3, [r0, #2844]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L4275
.L4251:
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L4252
	ldr	r3, [r4, #2816]
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bls	.L4253
	ldr	r0, [r3, #36]
	cmp	r0, #1
	beq	.L4252
.L4253:
	ldr	r0, [r1, #16]
	cmp	r0, #0
	ble	.L4254
	ldr	r0, [r1, #4]
	cmp	r0, #0
	beq	.L4254
	ldr	ip, [r1, #8]
	cmp	ip, #0
	bne	.L4276
.L4254:
	mov	r2, #1
	str	r2, [r3, #36]
	ldr	r1, [r1, #20]
	ldr	r0, [r4, #276]
	bl	SM_ReleaseStreamSeg
.L4250:
	ldr	r3, [r4, #2816]
	ldr	r0, [r3, #36]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
.L4248:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4276:
	mov	lr, r2, asl #5
	mov	ip, #0
	sub	r2, lr, r2, asl #2
	add	r3, r3, r2
	str	r0, [r3, #40]
	ldr	r3, [r4, #2816]
	ldr	lr, [r1, #16]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #44]
	ldr	r3, [r4, #2816]
	ldr	lr, [r1, #8]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #48]
	ldr	r3, [r4, #2816]
	ldr	lr, [r1, #20]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #64]
	ldr	r3, [r4, #2816]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	ip, [r3, #56]
	ldr	r2, [r4, #2816]
	ldr	r3, [r2, #8]
	add	r3, r3, #1
	str	r3, [r2, #8]
	ldr	r3, [r4, #2844]
	ldrb	r3, [r3, #912]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4255
	add	r3, r4, #4096
	ldr	r0, [r1, #16]
	ldr	r2, [r3, #52]
	ldr	ip, [r3, #56]
	add	r0, r0, r2
	str	r0, [r3, #52]
	ldr	r2, [r1, #16]
	add	r2, r2, ip
	str	r2, [r3, #56]
.L4255:
	mov	r0, r4
	bl	HEVC_CombinePacket
	mov	r3, #1
	str	r3, [r4, #344]
	b	.L4250
.L4275:
	ldr	r3, [r3, #888]
	cmp	r3, #0
	bne	.L4250
	b	.L4251
.L4274:
	ldr	r3, [r1, #16]
	cmp	r3, #0
	ble	.L4246
	ldr	r3, [r1, #4]
	cmp	r3, #0
	beq	.L4246
	ldr	r3, [r1, #8]
	str	r1, [fp, #-32]
	cmp	r3, #0
	beq	.L4246
	bl	HEVC_FindNaluArraySlot
	ldr	r1, [fp, #-32]
	cmn	r0, #1
	mov	r5, r0
	beq	.L4277
	ldr	r3, [r4, #2840]
	mov	r0, r0, asl #7
	sub	r0, r0, r5, asl #5
	mov	r2, #1
	add	r0, r3, r0
	str	r0, [r4, #2816]
	ldr	r3, [r1, #4]
	str	r3, [r0, #40]
	ldr	r3, [r4, #2816]
	ldr	r0, [r1, #16]
	str	r0, [r3, #44]
	ldr	r3, [r4, #2816]
	ldr	r0, [r1, #20]
	str	r0, [r3, #64]
	ldr	r3, [r4, #2816]
	ldr	r0, [r1, #8]
	str	r0, [r3, #48]
	ldr	r3, [r4, #2816]
	str	r6, [r3, #56]
	ldr	r3, [r4, #2816]
	str	r2, [r3, #8]
	ldr	r3, [r4, #2816]
	strb	r6, [r3]
	ldr	r3, [r4, #2816]
	ldrb	r2, [r1]	@ zero_extendqisi2
	str	r2, [r3, #36]
	ldr	r3, [r4, #2844]
	ldrb	r3, [r3, #912]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4249
	add	r3, r4, #4096
	ldr	r0, [r1, #16]
	ldr	r2, [r3, #52]
	ldr	ip, [r3, #56]
	add	r0, r0, r2
	str	r0, [r3, #52]
	ldr	r2, [r1, #16]
	add	r2, r2, ip
	str	r2, [r3, #56]
.L4249:
	ldr	r3, [r1, #12]
	str	r3, [r4, #2352]
	b	.L4250
.L4252:
	ldr	r1, .L4278
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4248
.L4246:
	ldr	r1, .L4278+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4248
.L4277:
	ldr	r1, .L4278+8
	mov	r0, r6
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	mov	r0, r5
	b	.L4248
.L4279:
	.align	2
.L4278:
	.word	.LC506
	.word	.LC505
	.word	.LC504
	UNWIND(.fnend)
	.size	HEVC_ReceivePacket, .-HEVC_ReceivePacket
	.align	2
	.global	HEVC_FlushDPB
	.type	HEVC_FlushDPB, %function
HEVC_FlushDPB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r3, [r0, #3028]
	mov	r4, r0
	cmp	r3, #0
	beq	.L4282
	add	r6, r0, #3184
	mov	r5, #0
	add	r6, r6, #8
	mov	r7, r5
	b	.L4284
.L4283:
	ldr	r3, [r4, #3028]
	cmp	r3, r5
	bls	.L4282
.L4284:
	ldr	r3, [r6, #4]!
	add	r5, r5, #1
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L4283
	strb	r7, [r3, #1]
	mov	r2, #0
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #276]
	bl	FSP_SetRef
	ldr	r3, [r4, #3028]
	cmp	r3, r5
	bhi	.L4284
.L4282:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L4286
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L4282
	b	.L4286
.L4288:
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	beq	.L4287
.L4286:
	ldr	r3, [r4, #3028]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L4288
	mov	r0, r3
.L4287:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_FlushDPB, .-HEVC_FlushDPB
	.align	2
	.global	HEVC_ClearDPB
	.type	HEVC_ClearDPB, %function
HEVC_ClearDPB:
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
	mov	r4, r0
	bl	HEVC_FlushDPB
	subs	r3, r0, #0
	beq	.L4297
	ldr	r2, .L4301
	mov	r0, #0
	ldr	r1, .L4301+4
	bl	dprint_vfmw
.L4297:
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4302:
	.align	2
.L4301:
	.word	.LANCHOR0+864
	.word	.LC507
	UNWIND(.fnend)
	.size	HEVC_ClearDPB, .-HEVC_ClearDPB
	.align	2
	.global	HEVC_RecoverDPBProcess
	.type	HEVC_RecoverDPBProcess, %function
HEVC_RecoverDPBProcess:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r4, r0
	b	.L4304
.L4306:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L4312
.L4304:
	ldr	ip, [r4, #3028]
	mov	r0, #13
	ldr	lr, [r4, #3024]
	ldr	r2, .L4313
	cmp	ip, lr
	ldr	r1, .L4313+4
	mov	r3, ip
	bcs	.L4306
	b	.L4308
.L4309:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_OutputUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L4307
	ldr	ip, [r4, #3028]
	ldr	lr, [r4, #3024]
.L4308:
	cmp	ip, lr
	mov	r3, ip
	ldr	r2, .L4313
	mov	r0, #1
	ldr	r1, .L4313+8
	bcs	.L4309
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4312:
	ldr	r2, .L4313
	mov	r0, #1
	ldr	r1, .L4313+12
	bl	dprint_vfmw
	ldr	ip, [r4, #3028]
	ldr	lr, [r4, #3024]
	b	.L4308
.L4307:
	ldr	r2, .L4313
	mov	r0, #1
	ldr	r1, .L4313+16
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	HEVC_ClearDPB
.L4314:
	.align	2
.L4313:
	.word	.LANCHOR0+880
	.word	.LC508
	.word	.LC510
	.word	.LC509
	.word	.LC502
	UNWIND(.fnend)
	.size	HEVC_RecoverDPBProcess, .-HEVC_RecoverDPBProcess
	.align	2
	.global	HEVC_InsertFrmInDPB
	.type	HEVC_InsertFrmInDPB, %function
HEVC_InsertFrmInDPB:
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
	cmp	r1, #16
	mov	r7, r1
	mov	r6, r0
	mov	r4, r2
	bhi	.L4319
	ldr	r3, [r2, #60]
	add	r5, r0, r1, lsl #2
	mov	r1, #1
	mov	r8, #0
	mov	r2, r1
	str	r3, [r5, #3196]
	str	r1, [r3, #48]
	ldr	r3, [r5, #3196]
	ldr	r0, [r0, #276]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r0, [r5, #3196]
	mov	r2, #632
	subs	r3, r3, r8
	add	r1, r4, #64
	movne	r3, #1
	strb	r3, [r0, #1]
	ldr	r3, [r5, #3196]
	ldr	r0, [r4, #36]
	str	r0, [r3, #20]
	ldr	r0, [r5, #3196]
	add	r0, r0, #80
	bl	memcpy
	ldr	ip, [r5, #3196]
	ldr	lr, [r4, #40]
	add	r0, r6, #3184
	add	r1, r7, #1
	add	r0, r0, #12
	ldr	r3, .L4321
	mov	r2, #4
	str	lr, [ip, #16]
	ldr	ip, [r5, #3196]
	ldr	lr, [r4, #60]
	str	lr, [ip, #76]
	ldr	ip, [r5, #3196]
	ldr	lr, [r4, #16]
	str	lr, [ip, #12]
	ldr	ip, [r5, #3196]
	ldr	lr, [r4, #12]
	str	lr, [ip, #8]
	ldr	ip, [r5, #3196]
	ldr	lr, [r4, #8]
	str	lr, [ip, #32]
	ldr	ip, [r5, #3196]
	str	r8, [ip, #72]
	bl	qsort
	ldr	r3, [r6, #3028]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r6, #3028]
	ldr	r1, [r4, #60]
	bl	HEVC_GetAPC
	subs	r3, r0, #0
	bne	.L4320
	mov	r0, r3
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4319:
	mov	r3, r1
	ldr	r2, .L4321+4
	ldr	r1, .L4321+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4320:
	ldr	r2, .L4321+4
	mov	r0, r8
	ldr	r1, .L4321+12
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_PrintDPBState
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4322:
	.align	2
.L4321:
	.word	HEVC_ComparePicByPocAsc
	.word	.LANCHOR0+904
	.word	.LC511
	.word	.LC512
	UNWIND(.fnend)
	.size	HEVC_InsertFrmInDPB, .-HEVC_InsertFrmInDPB
	.align	2
	.global	HEVC_SimpleDPBProcess
	.type	HEVC_SimpleDPBProcess, %function
HEVC_SimpleDPBProcess:
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
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r4, r0, #4096
	mov	r5, r0
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4336
	ldr	r3, [r4, #60]
	mov	r2, #2
	str	r2, [r3, #48]
.L4325:
	ldr	r3, [r4, #60]
	mov	r2, #1
	mov	r0, r5
	strb	r2, [r3, #2]
	ldr	r1, [r4, #60]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r4, r0
	beq	.L4337
	cmn	r0, #3
	beq	.L4329
	mov	r0, r5
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L4338
.L4329:
	mov	r0, #0
.L4326:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4336:
	bl	HEVC_SimpleSlideDPB
	mov	r2, r4
	ldr	r1, [r5, #3028]
	mov	r0, r5
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	beq	.L4325
	str	r0, [sp]
	movw	r3, #10933
	ldr	r2, .L4339
	mov	r0, #0
	ldr	r1, .L4339+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4326
.L4338:
	ldr	r2, .L4339
	mov	r0, #0
	ldr	r1, .L4339+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4326
.L4337:
	ldr	r2, .L4339
	mov	r0, #0
	ldr	r1, .L4339+12
	bl	dprint_vfmw
	mov	r0, r4
	b	.L4326
.L4340:
	.align	2
.L4339:
	.word	.LANCHOR0+924
	.word	.LC513
	.word	.LC498
	.word	.LC514
	UNWIND(.fnend)
	.size	HEVC_SimpleDPBProcess, .-HEVC_SimpleDPBProcess
	.align	2
	.global	HEVC_DecOrderProcess
	.type	HEVC_DecOrderProcess, %function
HEVC_DecOrderProcess:
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
	ldr	r1, [r0, #3028]
	mov	r4, r0
	ldr	r3, [r0, #3024]
	cmp	r1, r3
	bcs	.L4353
.L4342:
	add	r5, r4, #4096
	mov	r0, r4
	mov	r2, r5
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L4354
	ldr	r1, [r5, #60]
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L4355
	cmn	r0, #3
	beq	.L4348
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L4356
.L4348:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4353:
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L4352
	ldr	r2, .L4357
	mov	r0, #0
	ldr	r1, .L4357+4
	bl	dprint_vfmw
.L4352:
	ldr	r1, [r4, #3028]
	b	.L4342
.L4354:
	ldr	r2, .L4357
	mov	r0, #0
	ldr	r1, .L4357+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4356:
	mov	r0, r6
	ldr	r2, .L4357
	ldr	r1, .L4357+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4355:
	mov	r0, r6
	ldr	r2, .L4357
	ldr	r1, .L4357+16
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4358:
	.align	2
.L4357:
	.word	.LANCHOR0+948
	.word	.LC515
	.word	.LC516
	.word	.LC498
	.word	.LC514
	UNWIND(.fnend)
	.size	HEVC_DecOrderProcess, .-HEVC_DecOrderProcess
	.align	2
	.global	HEVC_DispOrderProcess
	.type	HEVC_DispOrderProcess, %function
HEVC_DispOrderProcess:
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
	add	r3, r0, #8192
	mov	r4, r0
	ldr	r3, [r3, #3576]
	cmp	r3, #1
	beq	.L4360
	bl	HEVC_FirstFrameFastOut
	cmp	r0, #0
	bne	.L4377
.L4360:
	ldr	r1, [r4, #3028]
	ldr	r3, [r4, #3024]
	cmp	r1, r3
	bcs	.L4378
.L4362:
	add	r2, r4, #4096
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L4379
	ldr	r3, [r4, #3028]
	cmp	r3, #0
	bne	.L4365
.L4366:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4365:
	mov	r0, r4
	bl	HEVC_OutputFrmFromDPB
	cmp	r0, #0
	beq	.L4366
	ldr	r2, .L4380
	mov	r0, #1
	ldr	r1, .L4380+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4378:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L4376
	ldr	r1, .L4380+8
	mov	r0, #0
	bl	dprint_vfmw
.L4376:
	ldr	r1, [r4, #3028]
	b	.L4362
.L4379:
	mov	r2, r0
	ldr	r1, .L4380+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4377:
	ldr	r2, .L4380
	mov	r0, #0
	ldr	r1, .L4380+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4381:
	.align	2
.L4380:
	.word	.LANCHOR0+972
	.word	.LC520
	.word	.LC518
	.word	.LC519
	.word	.LC517
	UNWIND(.fnend)
	.size	HEVC_DispOrderProcess, .-HEVC_DispOrderProcess
	.align	2
	.global	HEVC_StorePicInDPB
	.type	HEVC_StorePicInDPB, %function
HEVC_StorePicInDPB:
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
	ldr	r3, .L4446
	mov	r4, r0
	ldr	r2, [r0, #276]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L4435
.L4383:
	mov	r0, r4
	add	r6, r4, #4096
	bl	HEVC_RemoveDummyFrame
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4436
.L4384:
	ldrb	r5, [r6, #1]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L4437
	ldr	r2, [r6, #40]
	cmp	r2, #0
	beq	.L4389
	ldr	r5, [r6, #16]
	cmp	r5, #0
	beq	.L4438
.L4390:
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bcc	.L4439
.L4389:
	ldr	r3, [r4, #2852]
	ldr	r2, [r6, #60]
	add	r3, r3, #4096
	ldr	r3, [r3, #1088]
	str	r3, [r2, #40]
	ldr	r3, [r4, #2852]
	ldr	r2, [r6, #60]
	add	r3, r3, #4096
	ldr	r3, [r3, #1092]
	str	r3, [r2, #44]
	ldr	r3, [r4, #280]
	cmp	r3, #2
	beq	.L4440
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	beq	.L4441
	cmp	r3, #1
	beq	.L4442
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bls	.L4400
.L4402:
	mov	r0, r4
	mvn	r5, #0
	bl	HEVC_ClearCurrPic
	ldr	r2, .L4446+4
	ldr	r1, .L4446+8
	mov	r0, #1
	bl	dprint_vfmw
.L4401:
	mov	r3, #0
	mov	r0, r5
	strb	r3, [r6, #1]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4436:
	ldr	lr, [r6, #8]
	cmp	lr, #0
	beq	.L4384
	mov	r3, #280
	mul	r3, r3, lr
	add	r2, r4, r3
	add	r2, r2, #13120
	ldr	ip, [r2, #28]
	cmp	ip, #0
	beq	.L4384
	add	r1, r3, #13120
	add	r3, r3, #13376
	add	r1, r1, #32
	add	r3, r3, #36
	add	r1, r4, r1
	add	r3, r4, r3
	mov	r2, #0
	b	.L4386
.L4385:
	add	r2, r2, #1
	add	r3, r3, #1
	cmp	r2, ip
	beq	.L4384
.L4386:
	ldr	r0, [r1, #4]!
	cmp	r0, #0
	beq	.L4385
	ldrsb	r0, [r3]
	cmp	r0, #0
	beq	.L4385
	mov	r3, #70
	mov	r0, #280
	mla	r3, r3, lr, r2
	mov	r1, #0
	mla	lr, r0, lr, r4
	add	r3, r4, r3, lsl #2
	add	r0, lr, #13120
	add	r3, r3, #12288
	add	r2, lr, r2
	add	r2, r2, #13376
	str	r1, [r3, #868]
	str	r1, [r3, #932]
	str	r1, [r3, #996]
	ldr	ip, [r0, #32]
	sub	ip, ip, #1
	str	ip, [r0, #32]
	strb	r1, [r2, #36]
	str	r1, [r3, #1060]
	b	.L4384
.L4435:
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L4383
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L4383
	add	r3, r0, #8192
	ldrb	r3, [r3, #3520]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L4383
	bl	HEVC_Sei_Get_Frame_Pts
	b	.L4383
.L4437:
	ldr	r2, .L4446+4
	mov	r0, #1
	ldr	r1, .L4446+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4439:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #2844]
	ldr	r2, [r6, #40]
	mov	r0, #1
	ldr	r1, .L4446+16
	ldr	r3, [r3, #4]
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4441:
	mov	r0, r4
	bl	HEVC_SimpleDPBProcess
	subs	r5, r0, #0
	bne	.L4443
.L4397:
	movw	r3, #11210
	mov	r2, r5
	ldr	r1, .L4446+20
	mov	r0, #14
	bl	dprint_vfmw
.L4395:
	cmn	r5, #1
	bne	.L4401
	b	.L4402
.L4442:
	mov	r0, r4
	bl	HEVC_DecOrderProcess
	subs	r5, r0, #0
	beq	.L4444
	ldr	r2, .L4446+4
	mov	r0, #0
	ldr	r1, .L4446+24
	bl	dprint_vfmw
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L4395
.L4400:
	mov	r0, r4
	bl	HEVC_DispOrderProcess
	subs	r5, r0, #0
	beq	.L4401
	ldr	r2, .L4446+4
	mov	r0, #0
	ldr	r1, .L4446+28
	bl	dprint_vfmw
	b	.L4395
.L4438:
	ldr	r2, .L4446+4
	mov	r0, #1
	ldr	r1, .L4446+32
	bl	dprint_vfmw
	ldr	r3, .L4446+36
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4434
	mov	r3, r5
	mov	r2, r5
	mov	r1, #111
	ldr	r0, [r4, #276]
	blx	ip
.L4434:
	ldr	r2, [r6, #40]
	b	.L4390
.L4440:
	mov	r0, r4
	bl	HEVC_DirectOutput
	ldr	r3, [r6, #36]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	mov	r5, r0
	beq	.L4393
	add	r3, r3, #536
	mov	r1, #0
	add	r3, r3, #2
	add	r3, r4, r3, lsl #2
	str	r1, [r3, #4]
	str	r2, [r6, #36]
.L4393:
	cmp	r5, #0
	bne	.L4445
.L4394:
	movw	r3, #11195
	mov	r2, r5
	ldr	r1, .L4446+20
	mov	r0, #14
	bl	dprint_vfmw
	b	.L4395
.L4444:
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bls	.L4400
	b	.L4401
.L4445:
	ldr	r2, .L4446+4
	mov	r0, #0
	ldr	r1, .L4446+40
	bl	dprint_vfmw
	b	.L4394
.L4443:
	ldr	r2, .L4446+4
	mov	r0, #0
	ldr	r1, .L4446+44
	bl	dprint_vfmw
	b	.L4397
.L4447:
	.align	2
.L4446:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+996
	.word	.LC529
	.word	.LC521
	.word	.LC523
	.word	.LC525
	.word	.LC527
	.word	.LC528
	.word	.LC522
	.word	g_event_report
	.word	.LC524
	.word	.LC526
	UNWIND(.fnend)
	.size	HEVC_StorePicInDPB, .-HEVC_StorePicInDPB
	.align	2
	.global	HEVC_CreateLostPicture
	.type	HEVC_CreateLostPicture, %function
HEVC_CreateLostPicture:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 696
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #696)
	sub	sp, sp, #696
	ldr	r3, .L4493
	mov	r5, r0
	mov	r6, r1
	sub	r0, fp, #732
	mov	r2, #696
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	add	r4, r5, #13696
	add	r4, r4, #16
	mov	r7, #0
.L4453:
	ldr	r2, [r4, #48]
	cmp	r2, #0
	bne	.L4449
	cmp	r4, #0
	beq	.L4450
	ldr	r3, [r5, #3028]
	cmp	r3, #0
	beq	.L4450
	ldr	r1, [r5, #3196]
	cmp	r4, r1
	beq	.L4449
	add	ip, r5, #3184
	add	ip, ip, #12
	b	.L4451
.L4452:
	ldr	lr, [ip, #4]!
	cmp	r4, lr
	beq	.L4449
.L4451:
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L4452
.L4450:
	mov	r8, #712
	mov	r2, #632
	mla	r8, r8, r7, r5
	sub	r0, fp, #668
	mov	r9, #1
	mov	r3, #101
	str	r6, [fp, #-720]
	add	r1, r8, #13760
	str	r3, [fp, #-692]
	add	r1, r1, #32
	strb	r9, [fp, #-731]
	strb	r9, [fp, #-732]
	bl	memcpy
	add	r3, r8, #13696
	cmp	r7, #19
	add	r1, r8, #13760
	movw	r2, #13712
	mov	r7, #0
	strb	r9, [r3, #18]
	str	r4, [fp, #-672]
	str	r7, [r1, #4]
	str	r7, [fp, #-516]
	strb	r9, [r8, r2]
	bgt	.L4454
	ldr	r0, [r5, #3028]
	cmp	r0, #0
	beq	.L4456
	add	r1, r5, #3184
	mov	ip, r7
	add	r1, r1, #8
	mvn	r2, #-2147483648
	mov	r8, r1
.L4459:
	ldr	lr, [r8, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #8]
	rsb	r3, r6, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bge	.L4458
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	cmp	lr, #0
	movne	r2, r3
	movne	r7, #1
.L4458:
	cmp	ip, r0
	bne	.L4459
	cmp	r7, #0
	beq	.L4456
	mov	r4, #0
	b	.L4460
.L4461:
	add	r4, r4, #1
	cmp	r4, r0
	beq	.L4462
.L4460:
	ldr	ip, [r1, #4]!
	ldr	r3, [ip, #8]
	rsb	r3, r6, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bne	.L4461
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4461
	ldr	r1, [ip, #28]
	add	r4, r5, r4, lsl #2
	ldr	r0, [r5, #276]
	ldr	r9, [ip, #32]
	bl	FSP_GetLogicFs
	ldr	r2, [r4, #3196]
	mov	r3, r6
	ldr	r1, .L4493+4
	ldr	r2, [r2, #8]
	mov	r8, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r8, #0
	beq	.L4462
	ldr	r0, [r8, #28]
	cmp	r0, #0
	beq	.L4491
	mov	r1, #0
	ldr	r0, [r5, #276]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r5, #276]
	bl	FSP_GetLogicFs
	mvn	r2, r7
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r3, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L4465
	ldr	r1, [fp, #-672]
	sub	r2, fp, #732
	mov	r0, r5
	str	r7, [r1, #28]
	ldr	r1, [r8, #28]
	str	r1, [r3, #28]
	ldr	r1, [r8, #32]
	str	r1, [r3, #32]
	ldrsb	r3, [r8, #4]
	ldr	r1, [r5, #3028]
	str	r9, [fp, #-724]
	str	r3, [fp, #-696]
	bl	HEVC_InsertFrmInDPB
	subs	r4, r0, #0
	bne	.L4492
	ldr	r0, [r5, #276]
	mov	r1, r7
	mov	r2, r4
	bl	FSP_SetDisplay
	add	r3, r5, #4096
	mov	r0, r4
	ldr	r3, [r3, #728]
	add	r5, r5, r3, lsl #2
	ldr	r3, [r5, #244]
	cmn	r3, #-2147483647
	streq	r6, [r5, #244]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4449:
	add	r7, r7, #1
	add	r4, r4, #712
	cmp	r7, #20
	bne	.L4453
.L4454:
	ldr	r1, .L4493+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L4486:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4462:
	ldr	r1, .L4493+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4465:
	ldr	r3, [fp, #-672]
	mov	r0, r2
	ldr	r1, .L4493+16
	strb	r2, [r3]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4486
.L4492:
	ldr	r3, [fp, #-672]
	mov	r1, r7
	mov	r4, #0
	mov	r2, #1
	strb	r4, [r3]
	ldr	r0, [r5, #276]
	bl	FSP_ClearLogicFs
	mov	r0, r4
	ldr	r1, .L4493+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4486
.L4456:
	mov	r0, #0
	ldr	r1, .L4493+24
	strb	r0, [r4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4486
.L4491:
	ldr	r1, .L4493+28
	bl	dprint_vfmw
	mov	r0, r5
	bl	HEVC_ClearDPB
	mvn	r0, #0
	b	.L4486
.L4494:
	.align	2
.L4493:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC533
	.word	.LC530
	.word	.LC531
	.word	.LC535
	.word	.LC536
	.word	.LC532
	.word	.LC534
	UNWIND(.fnend)
	.size	HEVC_CreateLostPicture, .-HEVC_CreateLostPicture
	.align	2
	.global	HEVC_RefPicProcess
	.type	HEVC_RefPicProcess, %function
HEVC_RefPicProcess:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r0
	bl	HEVC_RemoveDummyFrame
	ldrb	r0, [r4, #1]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L4496
.L4500:
	mov	r0, r4
	add	r5, r4, #4096
	bl	HEVC_ApplyReferencePictureSet
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	b	.L4497
.L4506:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.15
	ldr	r1, .L4518
	cmp	r0, #0
	mov	r0, #1
	bne	.L4510
	ldr	r2, [fp, #-24]
	bl	dprint_vfmw
	ldr	r3, [r4, #2844]
	mov	r0, r4
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L4504
	ldr	r1, [fp, #-24]
	bl	HEVC_CreateLostPicture
	cmp	r0, #0
	bne	.L4516
.L4497:
	ldr	r3, [r5, #724]
	sub	r1, fp, #24
	mov	r0, r4
	sub	r3, r3, #19
	cmp	r3, #2
	bhi	.L4506
.L4510:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4517
.L4508:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	mov	r0, r4
	bl	HEVC_RecoverDPBProcess
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4504:
	ldr	ip, [fp, #-24]
	mov	r0, #1
	ldr	r3, [r5, #708]
	ldr	r1, .L4518+4
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4516:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4496:
	ldr	r3, [r4, #3052]
	cmp	r3, #0
	addne	r2, r4, #3056
	movne	r3, #0
	movne	ip, r3
	beq	.L4502
.L4501:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	str	ip, [r1, #60]
	ldr	r1, [r2]
	str	r0, [r1, #64]
	ldr	r1, [r4, #3052]
	cmp	r3, r1
	bcc	.L4501
.L4502:
	ldr	r3, [r4, #3056]
	cmp	r3, #0
	beq	.L4500
	add	r3, r4, #3120
	mov	r2, #0
	add	r3, r3, #4
	mov	ip, r2
	mov	r0, #1
.L4503:
	ldr	r1, [r3, #4]!
	add	r2, r2, #1
	str	ip, [r1, #60]
	ldr	r1, [r3]
	str	r0, [r1, #64]
	ldr	r1, [r4, #3056]
	cmp	r2, r1
	bcc	.L4503
	b	.L4500
.L4517:
	mov	r0, r4
	bl	HEVC_UpdateInterLayerReflist
	b	.L4508
.L4519:
	.align	2
.L4518:
	.word	.LC537
	.word	.LC538
	UNWIND(.fnend)
	.size	HEVC_RefPicProcess, .-HEVC_RefPicProcess
	.align	2
	.global	HEVC_DecVDM
	.type	HEVC_DecVDM, %function
HEVC_DecVDM:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	ldr	r3, [r0, #176]
	mov	r4, r0
	cmp	r3, #2
	bls	.L4579
	ldr	r3, [r0, #312]
	add	r5, r0, #4096
	ldr	r2, [r0, #316]
	mov	r0, #1
	ldr	r1, [r4, #2844]
	add	r3, r3, r0
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #312]
	rsb	r3, r2, r3
	str	r3, [r1, #576]
	strb	r0, [r5]
	ldr	r6, [r4, #272]
	ldr	r2, [r4, #280]
	ubfx	r6, r6, #16, #3
	cmp	r2, r6
	beq	.L4525
	subs	r3, r6, #2
	sub	r1, r2, #2
	movne	r3, #1
	cmp	r1, r0
	movhi	r3, #0
	cmp	r3, #0
	beq	.L4525
	cmp	r6, #4
	cmpne	r6, r0
	bls	.L4580
.L4525:
	cmp	r6, #2
	str	r6, [r4, #280]
	beq	.L4527
	cmp	r6, #3
	bne	.L4575
.L4576:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
.L4574:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4575:
	ldr	r3, [r4, #260]
	cmp	r3, #0
	beq	.L4544
	cmp	r6, #4
	ldr	r3, [r5, #16]
	beq	.L4581
.L4533:
	cmp	r3, #2
	bne	.L4535
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L4582
.L4546:
	ldr	r2, [r4, #264]
	mov	r0, #2
	ldr	r1, .L4584
	sub	r2, r2, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L4583
	ldr	r1, [r5, #28]
	add	r0, r4, #8192
	ldr	ip, [r5, #32]
	clz	r2, r1
	str	ip, [r5, #3756]
	mov	r2, r2, lsr #5
	str	r2, [r5, #3764]
	str	r3, [r0, #816]
	ldr	r3, [r4, #2844]
	ldr	r2, [r3, #592]
	strb	r2, [r5, #2424]
	ldr	r2, [r3, #596]
	strb	r2, [r5, #2425]
	ldr	r2, [r3, #600]
	strb	r2, [r5, #2427]
	ldr	r2, [r3, #604]
	strb	r2, [r5, #2428]
	ldr	r3, [r3, #644]
	str	r3, [r5, #3752]
	ldr	r3, [r4, #264]
	cmp	r3, #0
	beq	.L4540
	add	r2, r4, #6464
	add	r3, r5, #4096
	add	r2, r2, #56
	str	r2, [r4, #2852]
	ldr	ip, [r5, #44]
	add	r1, r1, #1
	mov	r2, #0
	str	ip, [r3, #3512]
	ldr	ip, [r5, #48]
	str	ip, [r3, #3516]
	str	r1, [r5, #28]
	str	r2, [r3, #3508]
	ldr	r1, [r5, #16]
	cmp	r1, r2
	bne	.L4540
	ldr	r2, [r0, #820]
	cmp	r2, #0
	beq	.L4549
.L4543:
	ldr	r3, [r2]
	ldr	r0, [r2, #4]
	ldr	r2, [r2, #1504]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L4543
.L4542:
	ldr	r3, .L4584+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4540
	sub	r2, fp, #28
	ldr	r0, [r4, #276]
	mov	r3, #4
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	ip
.L4540:
	ldr	ip, [r5, #56]
	mov	r0, #0
	ldr	r1, [r5, #60]
	ldr	r3, [r5, #52]
	str	ip, [r5, #52]
	ldr	r2, [r1, #320]
	rsb	r3, ip, r3
	add	r2, r2, r3
	str	r2, [r1, #320]
	ldr	r2, [r5, #304]
	add	r3, r3, r2
	str	r3, [r5, #304]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L4535:
	cmp	r3, #1
	streqb	r3, [r4, #8]
	b	.L4546
.L4527:
	ldr	r3, [r5, #16]
	cmp	r3, #0
	bne	.L4531
	ldr	r3, [r4, #260]
	cmp	r3, #0
	bne	.L4546
.L4544:
	ldr	r3, .L4584+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4531
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
.L4531:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L4574
.L4581:
	cmp	r3, #0
	moveq	r3, #2
	streqb	r3, [r4, #8]
	beq	.L4546
	b	.L4533
.L4582:
	ldr	r3, .L4584+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4546
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L4546
	mov	r3, #1
	ldr	r2, [r5, #12]
	mov	r0, r3
	ldr	r1, .L4584+12
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, .L4584+4
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L4574
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #127
	blx	ip
	mvn	r0, #0
	b	.L4574
.L4580:
	mov	r3, r6
	ldr	r1, .L4584+16
	bl	dprint_vfmw
	str	r6, [r4, #280]
	b	.L4576
.L4583:
	ldr	r2, .L4584+4
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L4538
	mov	r2, r3
	mov	r1, #127
	ldr	r0, [r4, #276]
	blx	ip
.L4538:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r2, .L4584+20
	ldr	r1, .L4584+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4574
.L4579:
	bl	HEVC_ClearCurrPic
	ldr	r3, .L4584+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4522
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
.L4522:
	ldr	r3, [r4, #268]
	cmp	r3, #524288
	bls	.L4523
	ldr	r1, .L4584+28
	mov	r0, #0
	bl	dprint_vfmw
.L4523:
	ldr	r1, .L4584+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4574
.L4549:
	mov	r1, r2
	b	.L4542
.L4585:
	.align	2
.L4584:
	.word	.LC543
	.word	g_event_report
	.word	g_allow_B_before_P
	.word	.LC542
	.word	.LC541
	.word	.LANCHOR0+1016
	.word	.LC544
	.word	.LC539
	.word	.LC540
	UNWIND(.fnend)
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	2
	.global	HEVC_VES_Splitter
	.type	HEVC_VES_Splitter, %function
HEVC_VES_Splitter:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #2796]
	mov	r1, #16
	mov	r9, r2
	str	r3, [fp, #-56]
	mov	r7, #0
	str	r7, [fp, #-48]
	bl	BsGet
	mov	r1, #8
	add	r6, r4, #4096
	mov	r10, r0
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #24
	and	r8, r0, #31
	ldr	r0, [r4, #2796]
	bl	BsBack
	ldr	r2, [r6, #496]
	cmp	r5, r7
	str	r7, [r6, #484]
	str	r2, [fp, #-48]
	beq	.L4588
	cmp	r5, #1
	beq	.L4589
	mov	r2, r5
	ldr	r1, .L4743
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
.L4596:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4589:
	cmp	r9, #0
	bne	.L4609
	ldr	r3, [fp, #-56]
	movw	r2, #31745
	cmp	r10, r2
	cmpeq	r3, #1
	moveq	r0, #1
	movne	r0, #0
	cmp	r8, #25
	movne	r8, #0
	andeq	r8, r0, #1
	cmp	r8, #0
	bne	.L4735
	movw	r1, #32257
	cmp	r10, r1
	beq	.L4736
	cmp	r10, r2
	bne	.L4737
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4608
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2816]
	mov	r0, r8
	b	.L4596
.L4588:
	cmp	r9, #0
	bne	.L4590
	movw	r1, #31745
	cmp	r8, #25
	cmpeq	r10, r1
	moveq	r5, #1
	movne	r5, #0
	bne	.L4591
	ldr	r8, .L4743+4
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L4592
	mov	r3, r9
	mov	r2, r9
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	ip
.L4592:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2816]
	subs	r5, r0, #0
	bne	.L4738
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r6, #484]
	bls	.L4597
	ldr	r1, .L4743+8
	movw	r3, #2348
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4598
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2816]
.L4598:
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L4724
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L4724:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4590:
	bic	r3, r10, #512
	movw	r2, #31745
	cmp	r3, r2
	beq	.L4739
.L4631:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4609:
	movw	r1, #31745
	cmp	r8, #25
	cmpeq	r10, r1
	moveq	r8, #1
	movne	r8, #0
	bne	.L4617
	ldr	r8, .L4743+4
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L4618
	mov	r3, r7
	mov	r2, r7
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	ip
.L4618:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2816]
	subs	r5, r0, #0
	bne	.L4732
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r6, #484]
	bls	.L4621
	ldr	r1, .L4743+8
	movw	r3, #2513
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4622
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2816]
.L4622:
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L4724
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L4596
.L4735:
	ldr	r8, .L4743+4
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L4611
	mov	r3, r9
	mov	r2, r9
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	ip
.L4611:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2816]
	subs	r5, r0, #0
	beq	.L4727
.L4732:
	cmp	r1, #0
	beq	.L4622
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
	b	.L4622
.L4591:
	movw	r2, #32257
	cmp	r10, r2
	bne	.L4631
.L4606:
	ldr	r1, [r4, #2816]
.L4727:
	cmp	r1, #0
	beq	.L4608
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2816]
	mov	r0, r5
	b	.L4596
.L4617:
	movw	r2, #32257
	cmp	r10, r2
	movne	r0, r5
	bne	.L4596
	ldr	r1, .L4743+12
	movw	r3, #2579
	ldr	r2, .L4743+16
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4724
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2816]
	mvn	r0, #0
	b	.L4596
.L4739:
	ldr	r1, .L4743+20
	movw	r3, #2434
	ldr	r2, .L4743+16
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4724
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2816]
	mvn	r0, #0
	b	.L4596
.L4608:
	mov	r0, #0
	b	.L4596
.L4738:
	cmp	r1, #0
	beq	.L4598
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
	b	.L4598
.L4737:
	mov	r1, #8
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	ldr	r0, [r4, #2796]
	ubfx	r5, r5, #1, #6
	bl	BsSkip
	cmp	r5, #49
	beq	.L4740
.L4616:
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4608
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2816]
	b	.L4596
.L4621:
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r6, #488]
	add	r3, r3, r0
	ldr	r0, [r4, #276]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r7, r0, #0
	bne	.L4741
	ldr	r5, .L4743+24
	mov	r2, #5
	ldr	r1, .L4743+28
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2816]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r6, #484]
	add	r1, r1, #6
	blx	r3
	ldr	r0, [r6, #484]
	add	r3, r0, #5
	str	r3, [r6, #484]
	ldr	r1, [r4, #2816]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L4624
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L4625
	add	r2, r0, #10
	ldr	r1, .L4743+8
	movw	r3, #2537
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4626
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r7, [r4, #2816]
.L4626:
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L4627
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
.L4627:
	ldr	r0, [r4, #276]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movne	r3, #2544
	beq	.L4724
.L4723:
	ldr	r2, .L4743+16
	mov	r0, #0
	ldr	r1, .L4743+32
	bl	dprint_vfmw
	b	.L4724
.L4597:
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r6, #488]
	add	r3, r3, r0
	ldr	r0, [r4, #276]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r7, r0, #0
	bne	.L4742
	ldr	r5, .L4743+24
	mov	r2, #5
	ldr	r1, .L4743+28
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2816]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r6, #484]
	add	r1, r1, #6
	blx	r3
	ldr	r0, [r6, #484]
	add	r3, r0, #5
	str	r3, [r6, #484]
	ldr	r1, [r4, #2816]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L4601
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L4602
	add	r2, r0, #10
	ldr	r1, .L4743+8
	movw	r3, #2372
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4603
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r7, [r4, #2816]
.L4603:
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L4604
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
.L4604:
	ldr	r0, [r4, #276]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2379
	beq	.L4724
	b	.L4723
.L4602:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r4, #2816]
	ldr	r2, [r6, #484]
	ldr	r3, [r3, #72]
	add	r3, r3, r2
	str	r3, [r6, #484]
.L4601:
	ldr	r0, [r4, #276]
	ldr	r7, .L4743+36
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L4605
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #276]
	ldr	r1, [r6, #484]
	ldr	r3, [r5, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #276]
.L4605:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	beq	.L4606
	movw	r3, #2407
	b	.L4723
.L4625:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r4, #2816]
	ldr	r2, [r6, #484]
	ldr	r3, [r3, #72]
	add	r3, r3, r2
	str	r3, [r6, #484]
.L4624:
	ldr	r0, [r4, #276]
	ldr	r7, .L4743+36
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L4628
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #276]
	ldr	r1, [r6, #484]
	ldr	r3, [r5, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #276]
.L4628:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	movwne	r3, #2567
	beq	.L4606
	b	.L4723
.L4736:
	ldr	r0, [r4, #2796]
	mov	r1, #16
	bl	BsSkip
	mov	r0, r5
	b	.L4596
.L4740:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	bne	.L4616
	ldr	r3, [r4, #2816]
	ldr	r0, [r4, #2796]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	ldr	r0, [r4, #2796]
	mov	r1, #24
	bl	BsSkip
	mov	r0, #2
	b	.L4596
.L4741:
	mov	r0, r5
	movw	r3, #2525
	ldr	r2, .L4743+16
	ldr	r1, .L4743+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4596
.L4742:
	mov	r0, r5
	movw	r3, #2360
	ldr	r2, .L4743+16
	ldr	r1, .L4743+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4596
.L4744:
	.align	2
.L4743:
	.word	.LC550
	.word	g_event_report
	.word	.LC545
	.word	.LC549
	.word	.LANCHOR0+1028
	.word	.LC548
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR4+208
	.word	.LC547
	.word	vfmw_save_metadata_file
	.word	.LC546
	UNWIND(.fnend)
	.size	HEVC_VES_Splitter, .-HEVC_VES_Splitter
	.align	2
	.global	HEVC_CRAOutputFrame
	.type	HEVC_CRAOutputFrame, %function
HEVC_CRAOutputFrame:
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
	mov	r4, r0
	ldr	r0, [r0, #3028]
	cmp	r0, #0
	beq	.L4757
	add	r2, r4, #3184
	mov	r5, #0
	add	r2, r2, #8
	mov	r3, r5
.L4748:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, #0
	addeq	r5, r5, #1
	cmp	r3, r0
	bne	.L4748
.L4749:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L4749
	cmp	r5, #0
	ble	.L4751
.L4755:
	ldr	r1, [r4, #3028]
	cmp	r1, #0
	beq	.L4752
	ldr	r3, [r4, #3196]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4759
	add	r2, r4, #3184
	mov	r3, #0
	add	r2, r2, #12
	b	.L4756
.L4753:
	ldr	ip, [r2, #4]!
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L4759
.L4756:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L4753
.L4752:
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	subs	r5, r5, #1
	bne	.L4755
.L4751:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4759:
	mov	r1, r3
	b	.L4752
.L4757:
	mov	r5, r0
	b	.L4749
	UNWIND(.fnend)
	.size	HEVC_CRAOutputFrame, .-HEVC_CRAOutputFrame
	.align	2
	.global	HEVC_DecSlice
	.type	HEVC_DecSlice, %function
HEVC_DecSlice:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r3, [r0, #2816]
	add	r5, r0, #4096
	ldr	r2, .L4849
	mov	ip, #0
	mov	r4, r0
	ldr	r1, [r3, #16]
	str	r1, [r5, #724]
	ldr	r1, [r3, #28]
	str	r1, [r5, #720]
	ldr	r6, [r3, #24]
	str	r6, [r5, #728]
	ldr	r1, [r0, #276]
	strb	ip, [r0, #3]
	ldr	r2, [r2, r1, asl #2]
	ldrsb	r1, [r2, #44]
	cmp	r1, #1
	beq	.L4835
.L4770:
	ldr	r3, [r5, #848]
	cmp	r3, #1
	beq	.L4836
.L4771:
	ldr	r2, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r2, r3
	bcs	.L4837
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4838
	mov	r0, r4
	bl	HEVC_PicTypeStatistic
	mov	r0, r4
	bl	HEVC_CalcStreamBits
	ldr	r3, [r5, #848]
	cmp	r3, #2
	beq	.L4789
	ldr	r3, [r4, #2356]
	cmp	r3, #0
	bne	.L4790
	ldrb	r3, [r5, #697]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4839
.L4790:
	mov	r0, r4
	bl	HEVC_WriteSliceMsg
	cmp	r0, #0
	bne	.L4840
.L4793:
	ldr	r3, [r4, #2356]
	cmp	r3, #0
	beq	.L4841
.L4795:
	ldr	r3, [r4, #3480]
	mov	r0, #0
	str	r3, [r5, #44]
	ldr	r3, [r4, #3484]
	str	r3, [r5, #48]
.L4776:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4841:
	ldr	r3, [r5, #732]
	mov	r2, #1
	str	r3, [r4, #320]
	ldr	r3, [r5, #708]
	str	r2, [r4, #172]
	str	r3, [r4, #284]
	b	.L4795
.L4836:
	ldr	r3, [r4, #2356]
	cmp	r3, #0
	bne	.L4773
	ldr	r3, [r5, #724]
	clz	r7, r6
	sub	r3, r3, #16
	mov	r7, r7, lsr #5
	cmp	r3, #4
	cmpls	r6, #0
	bne	.L4842
.L4774:
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L4843
.L4775:
	add	r3, r4, r6
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	andeq	r3, r7, #1
	cmp	r3, #0
	beq	.L4777
	ldr	r3, [r4, #3028]
	cmp	r3, #0
	bne	.L4844
.L4777:
	ldr	r0, [r4, #2844]
	ldr	r1, [r0, #12]
	cmp	r1, #0
	bne	.L4778
	ldr	r3, [r4, #2364]
	cmp	r3, #1
	beq	.L4845
	ldr	r3, [r5, #720]
	ldr	r2, [r4, #2828]
	add	r3, r3, #90
	ldr	r1, [r2, r3, asl #2]
.L4781:
	cmp	r7, #0
	beq	.L4778
	add	r6, r4, r6, lsl #2
	ldr	r3, [r6, #212]
	cmp	r3, #-2147483647
	beq	.L4778
	ldr	r2, [r5, #708]
	add	r1, r1, r3
	cmp	r2, r1
	bcs	.L4778
	ldr	r1, [r5, #724]
	cmp	r1, #21
	bne	.L4778
	ldr	r1, .L4849+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_CRAOutputFrame
	mov	r3, #-2147483647
	str	r3, [r6, #212]
	ldr	r0, [r4, #2844]
.L4778:
	ldr	r3, [r0, #8]
	cmp	r3, #2
	beq	.L4773
	ldr	r3, [r0, #24]
	cmp	r3, #2
	bne	.L4783
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4846
.L4784:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
.L4773:
	mov	r0, r4
	bl	HEVC_InitPic
	cmn	r0, #2
	beq	.L4776
	cmp	r0, #0
	bne	.L4847
	ldr	r3, [r4, #264]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #264]
	bl	HEVC_SetScalingList
	mov	r0, r4
	bl	HEVC_WritePicMsg
	cmp	r0, #0
	beq	.L4771
	ldr	r1, .L4849+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4835:
	ldr	r1, [r2, #156]
	cmp	r1, ip
	bne	.L4770
	ldr	r2, [r2, #160]
	cmp	r2, #1
	bne	.L4770
	ldr	r1, [r3, #16]
	bl	HEVC_Get_Last_IDR_Frame_Info
	b	.L4770
.L4789:
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4793
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
	b	.L4793
.L4839:
	mov	r0, r4
	bl	HEVC_DecList
	cmp	r0, #0
	bne	.L4848
	mov	r0, r4
	bl	HEVC_IsRefListWrong
	cmp	r0, #0
	beq	.L4790
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r1, .L4849+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4842:
	mov	r0, r4
	bl	HEVC_IsPVRFlushPic
	cmp	r0, #0
	beq	.L4775
	b	.L4774
.L4783:
	mov	r0, r4
	bl	HEVC_RefPicProcess
	cmp	r0, #0
	beq	.L4773
	mvn	r0, #0
	b	.L4776
.L4844:
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L4777
	ldr	r2, .L4849+16
	mov	r0, #1
	ldr	r1, .L4849+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4838:
	ldr	r1, .L4849+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4845:
	ldr	ip, [r4, #2828]
	add	r3, ip, #356
	add	ip, ip, #388
.L4780:
	ldr	r2, [r3, #4]!
	cmp	r1, r2
	movcc	r1, r2
	cmp	r3, ip
	bne	.L4780
	b	.L4781
.L4837:
	ldr	r1, .L4849+28
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	cmp	r3, r2
	bcc	.L4787
	ldr	r1, .L4849+32
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L4787
	str	r3, [fp, #-36]
	mov	r1, #108
	str	r2, [fp, #-32]
	mov	r3, #8
	sub	r2, fp, #36
	ldr	r0, [r4, #276]
	blx	ip
.L4787:
	ldr	r1, .L4849+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L4776
.L4840:
	ldr	r1, .L4849+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4847:
	ldr	r1, .L4849+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4846:
	mov	r0, r4
	bl	HEVC_UpdateInterLayerReflist
	b	.L4784
.L4848:
	mov	r2, r0
	ldr	r1, .L4849+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4843:
	ldr	r2, .L4849+16
	mov	r0, #1
	ldr	r1, .L4849+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4776
.L4850:
	.align	2
.L4849:
	.word	s_pstVfmwChan
	.word	.LC553
	.word	.LC555
	.word	.LC560
	.word	.LANCHOR0+1048
	.word	.LC552
	.word	.LC558
	.word	.LC556
	.word	g_event_report
	.word	.LC557
	.word	.LC561
	.word	.LC554
	.word	.LC559
	.word	.LC551
	UNWIND(.fnend)
	.size	HEVC_DecSlice, .-HEVC_DecSlice
	.align	2
	.global	HEVC_DecOneNal
	.type	HEVC_DecOneNal, %function
HEVC_DecOneNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	mov	r4, r0
	ldr	r0, [r0, #2816]
	ldr	r3, [r0, #8]
	cmp	r3, #0
	ldrne	r1, [r4, #268]
	movne	r2, r0
	movne	r3, #0
	beq	.L4856
.L4855:
	ldr	ip, [r2, #44]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, ip
	str	r1, [r4, #268]
	ldr	ip, [r0, #8]
	cmp	ip, r3
	bhi	.L4855
.L4856:
	mov	r3, #0
	strb	r3, [r0]
	ldr	r3, [r4, #2816]
	ldr	r2, [r3, #16]
	sub	r2, r2, #36
	cmp	r2, #1
	bls	.L4995
.L4854:
	ldr	r2, [r3, #4]
	add	r2, r2, #16
	str	r2, [r3, #4]
	ldr	r1, [r4, #2816]
	ldr	r2, [r1, #16]
	cmp	r2, #49
	ldrls	pc, [pc, r2, asl #2]
	b	.L4857
.L4859:
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4858
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4860
	.word	.L4861
	.word	.L4862
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4863
	.word	.L4863
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4857
	.word	.L4864
	.word	.L4865
.L4995:
	mov	r2, #1
	strb	r2, [r4, #3]
	b	.L4854
.L4865:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	beq	.L4996
.L4881:
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4984
.L4986:
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2816]
.L4983:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4858:
	mov	r0, r4
	bl	HEVC_DecSlice
	cmn	r0, #2
	beq	.L4983
	cmp	r0, #0
	beq	.L4984
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4993
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L4993:
	ldr	r3, .L4998
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4985
.L4987:
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L4985:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4860:
	mov	r0, r4
	bl	HEVC_DecVPS
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4866
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L4866:
	cmp	r5, #0
	bne	.L4997
.L4984:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4861:
	mov	r0, r4
	bl	HEVC_DecSPS
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4871
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L4871:
	cmp	r5, #0
	beq	.L4984
	ldr	r6, .L4998
	mov	r0, #1
	ldr	r1, .L4998+4
	bl	dprint_vfmw
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L4989
	b	.L4985
.L4862:
	mov	r0, r4
	bl	HEVC_DecPPS
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4873
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L4873:
	cmp	r5, #0
	beq	.L4984
	ldr	r6, .L4998
	mov	r0, #1
	ldr	r1, .L4998+8
	bl	dprint_vfmw
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L4985
.L4989:
	sub	r2, fp, #28
	mvn	r5, #0
	mov	r3, #4
	mov	r1, #100
	str	r5, [r2, #-4]!
	ldr	r0, [r4, #276]
	blx	ip
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L4987
	b	.L4985
.L4863:
	mov	r0, r4
	bl	HEVC_DecSEI
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4874
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L4874:
	cmp	r5, #0
	beq	.L4984
	ldr	r1, .L4998+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4993
.L4864:
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4879
	cmp	r1, #0
	beq	.L4878
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L4878:
	add	r3, r4, #4096
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4984
.L4879:
	add	r5, r4, #2992
	mov	r1, #32
	mov	r6, #0
	strb	r6, [r4, #10]
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r7, r0
	mov	r0, r5
	bl	BsGet
	movw	r1, #20036
	movw	r2, #20553
	movt	r1, 17221
	movt	r2, 18515
	cmp	r0, r1
	cmpeq	r7, r2
	bne	.L4984
	ldr	r5, .L4998
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4880
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #276]
	blx	ip
.L4880:
	add	r3, r4, #4096
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4984
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L4984
.L4883:
	ldr	ip, [r5]
	cmp	ip, #0
	bne	.L4987
	b	.L4985
.L4857:
	ldr	r1, .L4998+16
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	ldr	r3, [r1, #16]
	cmp	r3, #63
	bhi	.L4884
	cmp	r1, #0
	bne	.L4986
	b	.L4984
.L4884:
	ldr	r5, .L4998
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4885
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4886
.L4887:
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L4886:
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4984
	mov	r3, #0
	ldr	r0, [r4, #276]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	b	.L4984
.L4885:
	cmp	r1, #0
	bne	.L4887
	b	.L4984
.L4997:
	ldr	r6, .L4998
	mov	r0, #1
	ldr	r1, .L4998+20
	bl	dprint_vfmw
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L4989
	b	.L4985
.L4996:
	ldr	r5, .L4998
	strb	r0, [r4, #11]
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4882
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
.L4882:
	add	r3, r4, #4096
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4881
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L4881
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L4883
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
	b	.L4883
.L4999:
	.align	2
.L4998:
	.word	g_event_report
	.word	.LC563
	.word	.LC564
	.word	.LC565
	.word	.LC566
	.word	.LC562
	UNWIND(.fnend)
	.size	HEVC_DecOneNal, .-HEVC_DecOneNal
	.align	2
	.global	HEVC_UnMarkFrameStoreRef
	.type	HEVC_UnMarkFrameStoreRef, %function
HEVC_UnMarkFrameStoreRef:
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
	mov	r3, #0
	strb	r3, [r1, #1]
	mov	r2, r3
	ldr	r1, [r1, #28]
	ldr	r0, [r0, #276]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
	UNWIND(.fnend)
	.size	HEVC_UnMarkFrameStoreRef, .-HEVC_UnMarkFrameStoreRef
	.align	2
	.global	HEVC_InquireSliceProperty
	.type	HEVC_InquireSliceProperty, %function
HEVC_InquireSliceProperty:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	ip, .L5026
	mov	r4, r0
	mov	r3, #0
	mov	r8, r1
	add	r0, r0, #4736
	str	r3, [r2]
	mov	r1, r3
	str	r3, [r8]
	mov	r7, r2
	ldr	r3, [ip, #48]
	mov	r2, #1376
	add	r0, r0, #56
	add	r5, r4, #4096
	blx	r3
	ldr	r3, [r4, #2816]
	mov	r0, r4
	ldr	r2, [r3, #16]
	str	r2, [r5, #724]
	ldr	r2, [r3, #28]
	str	r2, [r5, #720]
	ldr	r3, [r3, #24]
	str	r3, [r5, #728]
	bl	HEVC_DecSliceSegmentHeader
	cmp	r0, #0
	bne	.L5021
	ldr	r2, [r5, #732]
	movw	r0, #5036
	ldr	r3, [r4, #2808]
	movw	r6, #12668
	ldr	r9, [r4, #2356]
	ldr	r1, [r4, #2804]
	mla	r3, r0, r2, r3
	cmp	r9, #1
	ldr	r3, [r3, #32]
	mla	r6, r6, r3, r1
	beq	.L5022
	ldr	r3, [r5, #848]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r8]
	ldr	r2, [r4, #2828]
	ldr	ip, [r4, #2844]
	ldr	r1, [r6, #184]
	ldr	r3, [r2, #184]
	ldr	lr, [ip, #840]
	subs	r0, r1, r3
	ldr	r1, [r2, #64]
	ldr	r3, [r6, #64]
	movne	r0, #1
	cmp	lr, #1
	ldr	r2, [r2, #68]
	ldr	lr, [r6, #68]
	beq	.L5023
.L5007:
	cmp	r3, r1
	moveq	r1, r0
	orrne	r1, r0, #1
	cmp	lr, r2
	moveq	r3, r1
	orrne	r3, r1, #1
	cmp	r3, #0
	beq	.L5010
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L5024
.L5011:
	mov	r0, #0
	mov	r3, #1
	str	r3, [r7]
.L5020:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L5022:
	ldr	r0, [r4, #2796]
	bl	BsResidBits
	ldr	r3, [r6, #188]
	ldr	r1, [r4, #204]
	add	r1, r1, #1
	mov	r5, r0
	ldr	r0, [r6, #192]
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	cmp	r5, r0
	movge	r3, #0
	movlt	r3, #1
	orrs	r3, r3, r5, lsr #31
	bne	.L5005
.L5010:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L5021:
	ldr	r1, .L5026+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L5026+8
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L5020
	sub	r2, fp, #36
	ldr	r0, [r4, #276]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	ip
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L5023:
	ldr	r5, [r6, #96]
	ldr	r6, [r6, #88]
	cmp	r5, r6
	movcc	r5, r6
	str	r5, [ip, #900]
	ldr	r5, [r4, #2828]
	ldr	r6, [r4, #2844]
	ldr	ip, [r5, #96]
	ldr	r5, [r5, #88]
	ldr	r8, [r6, #900]
	cmp	ip, r5
	movcc	ip, r5
	cmp	ip, #8
	movls	r5, #0
	movhi	r5, #1
	cmp	r8, #8
	movne	r5, #0
	cmp	r5, #0
	beq	.L5025
.L5008:
	mov	ip, #1
	str	ip, [r6, #904]
	str	ip, [r7]
	b	.L5007
.L5024:
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	bics	r3, r3, #4
	beq	.L5011
	ldr	r3, [r4, #2384]
	mov	r0, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r7]
	b	.L5020
.L5025:
	sub	ip, ip, #8
	cmp	r8, #8
	clz	ip, ip
	mov	ip, ip, lsr #5
	movle	ip, #0
	cmp	ip, #0
	beq	.L5007
	b	.L5008
.L5005:
	mov	r3, r0
	mov	r2, r5
	mov	r0, r9
	ldr	r1, .L5026+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L5020
.L5027:
	.align	2
.L5026:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC567
	.word	g_event_report
	.word	.LC568
	UNWIND(.fnend)
	.size	HEVC_InquireSliceProperty, .-HEVC_InquireSliceProperty
	.align	2
	.global	HEVC_HaveSliceToDec
	.type	HEVC_HaveSliceToDec, %function
HEVC_HaveSliceToDec:
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
	mov	r4, r0
	ldr	r0, [r0, #204]
	cmp	r0, #0
	bne	.L5030
	add	r3, r4, #4096
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L5032
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5030:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5032:
	ldr	r2, .L5033
	ldr	r1, .L5033+4
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5034:
	.align	2
.L5033:
	.word	.LANCHOR0+1064
	.word	.LC569
	UNWIND(.fnend)
	.size	HEVC_HaveSliceToDec, .-HEVC_HaveSliceToDec
	.align	2
	.global	HEVC_GetPicStreamSize
	.type	HEVC_GetPicStreamSize, %function
HEVC_GetPicStreamSize:
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
	add	r0, r0, #8192
	ldr	r2, [r0, #820]
	cmp	r2, #0
	beq	.L5038
	mov	r0, #0
.L5037:
	ldr	r3, [r2]
	ldr	r1, [r2, #4]
	ldr	r2, [r2, #1504]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L5037
	ldmfd	sp, {fp, sp, pc}
.L5038:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_GetPicStreamSize, .-HEVC_GetPicStreamSize
	.align	2
	.global	HEVC_IsFrameEndNal
	.type	HEVC_IsFrameEndNal, %function
HEVC_IsFrameEndNal:
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
	sub	r3, r0, #48
	sub	r0, r0, #32
	cmp	r0, #2
	cmphi	r3, #1
	movls	r0, #1
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_IsFrameEndNal, .-HEVC_IsFrameEndNal
	.align	2
	.global	HEVCDEC_CheckSedOnly
	.type	HEVCDEC_CheckSedOnly, %function
HEVCDEC_CheckSedOnly:
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
	ldr	r3, [r0, #2352]
	mov	r5, #0
	mov	r4, r0
	str	r5, [r0, #2356]
	cmp	r3, #2
	str	r5, [r0, #2364]
	beq	.L5069
	cmp	r3, #1
	beq	.L5070
.L5054:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5070:
	ldr	r3, [r0, #2360]
	cmp	r3, #1
	bne	.L5054
	str	r5, [r0, #2360]
.L5068:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5069:
	ldr	r3, [r0, #2348]
	cmp	r3, r5
	beq	.L5068
	ldr	r3, [r0, #2360]
	cmp	r3, #1
	beq	.L5054
	ldr	r0, [r0, #276]
	bl	VCTRL_CheckFreshSeg
	cmp	r0, #0
	beq	.L5068
	ldr	r0, [r4, #276]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L5068
	ldr	r3, [r4, #2816]
	ldr	r0, [r4, #2796]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2796]
	bl	BsSkip
	ldr	r0, [r4, #2796]
	bl	BsResidBits
	cmp	r0, #15
	ble	.L5068
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsSkip
	mov	r1, #6
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #9
	mov	r6, r0
	ldr	r0, [r4, #2796]
	bl	BsSkip
	mov	r0, r6
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r7, r0
	beq	.L5071
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L5068
	sub	r3, r6, #48
	sub	r6, r6, #32
	cmp	r6, #2
	cmphi	r3, #1
	bhi	.L5068
.L5050:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	bne	.L5068
	add	r2, r4, #4096
	mov	r3, #1
	mvn	r0, #0
	str	r3, [r4, #2364]
	strb	r3, [r2]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5071:
	ldr	r0, [r4, #2796]
	bl	BsResidBits
	cmp	r0, #0
	movle	r0, r5
	ble	.L5047
	mov	r1, r7
	ldr	r0, [r4, #2796]
	bl	BsGet
.L5047:
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L5048
	sub	r3, r6, #48
	sub	r6, r6, #32
	cmp	r6, #2
	cmphi	r3, #1
	movls	r3, #1
	movhi	r3, #0
	cmp	r0, #0
	moveq	r5, r3
	orrne	r5, r3, #1
	cmp	r5, #0
	bne	.L5050
.L5048:
	add	r3, r4, #4096
	mov	r5, #0
	mov	r2, #1
	str	r5, [r4, #2360]
	str	r2, [r4, #2356]
	mov	r0, r5
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	str	r3, [r4, #2368]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_CheckSedOnly, .-HEVCDEC_CheckSedOnly
	.align	2
	.global	HEVCDEC_IsNeedSedOnly
	.type	HEVCDEC_IsNeedSedOnly, %function
HEVCDEC_IsNeedSedOnly:
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
	ldr	r3, [r0, #204]
	mov	r4, r0
	cmp	r3, #0
	beq	.L5075
	ldr	r2, [r0, #2852]
	cmp	r2, #0
	beq	.L5080
.L5075:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5080:
	add	r2, r0, #4096
	ldr	r2, [r2, #2448]
	cmp	r2, #1
	bls	.L5075
	ldr	r2, [r0, #2372]
	cmp	r3, r2
	beq	.L5075
	ldr	r3, [r0, #2356]
	cmp	r3, #1
	beq	.L5081
	cmp	r3, #0
	bne	.L5075
	ldr	r0, [r0, #276]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L5075
	ldr	r0, [r4, #276]
	bl	VCTRL_CheckFreshSeg
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L5081:
	ldr	r0, [r0, #2816]
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_IsNeedSedOnly, .-HEVCDEC_IsNeedSedOnly
	.align	2
	.global	HEVCDEC_SetDecParam
	.type	HEVCDEC_SetDecParam, %function
HEVCDEC_SetDecParam:
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
	ldr	r5, [r0, #2360]
	mov	r4, r0
	cmp	r5, #1
	beq	.L5095
.L5083:
	mov	r0, r4
	bl	HEVCDEC_IsNeedSedOnly
	cmp	r0, #1
	beq	.L5096
	ldr	r3, [r4, #2356]
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	ip, [r4, #2368]
	add	r3, r4, #4096
	ldr	r0, [r4, #204]
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #260]
	sub	r0, r0, #1
	sub	r1, r1, #1
	str	r0, [r4, #204]
	str	r1, [r4, #176]
	sub	r2, r2, #1
	str	r2, [r4, #260]
	strb	ip, [r3, #1]
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5095:
	ldr	r3, [r0, #204]
	cmp	r3, #0
	beq	.L5083
	ldr	r6, [r0, #2852]
	cmp	r6, #0
	bne	.L5083
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L5097
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2816]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5096:
	add	r2, r4, #8192
	add	lr, r4, #4096
	add	r3, r4, #6464
	mov	ip, #0
	str	r0, [r2, #3508]
	add	r3, r3, #56
	ldr	r1, [r4, #204]
	str	r1, [r4, #2372]
	str	r1, [r2, #816]
	ldr	r2, [r4, #2844]
	ldr	r2, [r2, #644]
	str	r2, [lr, #3752]
	str	r3, [r4, #2852]
	str	ip, [r4, #2360]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5097:
	add	r3, r4, #4096
	str	r5, [r4, #2364]
	strb	r5, [r3]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_SetDecParam, .-HEVCDEC_SetDecParam
	.align	2
	.global	HEVCDEC_VDMProcSedOnly
	.type	HEVCDEC_VDMProcSedOnly, %function
HEVCDEC_VDMProcSedOnly:
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
	ldr	r6, .L5110
	mov	r3, #180
	ldr	r2, [r0, #2852]
	mov	r4, r0
	ldr	lr, [r0, #276]
	mov	r0, #22
	mla	r1, r3, r1, r6
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #20]
	ldr	ip, .L5110+4
	add	r6, r1, #16
	ldr	r1, .L5110+8
	mla	r5, r2, r3, r3
	ldr	r3, [r6, #4]
	ldr	r7, [ip, lr, asl #2]
	add	r5, r5, r2
	mov	r2, r5
	bl	dprint_vfmw
	ldr	r3, [r6, #4]
	cmp	r3, r5
	ldr	r3, [r4, #2356]
	beq	.L5108
	cmp	r3, #1
	beq	.L5109
.L5103:
	mov	r3, #0
	str	r3, [r4, #2852]
.L5101:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5108:
	cmp	r3, #1
	beq	.L5100
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	addeq	r2, r4, #4096
	moveq	r3, #1
	streq	r3, [r4, #2364]
	streqb	r3, [r2]
	b	.L5101
.L5109:
	ldr	ip, [r4, #2368]
	add	r3, r4, #4096
	ldr	r0, [r4, #204]
	mov	r5, #0
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #260]
	sub	r0, r0, #1
	sub	r1, r1, #1
	str	r0, [r4, #204]
	str	r1, [r4, #176]
	sub	r2, r2, #1
	str	r5, [r4, #2360]
	str	r2, [r4, #260]
	strb	ip, [r3, #1]
	ldr	r1, [r4, #2816]
	cmp	r1, r5
	beq	.L5103
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2816]
	b	.L5103
.L5100:
	ldr	r5, [r4, #2368]
	add	lr, r4, #4096
	ldr	r0, [r4, #204]
	mov	ip, #0
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #260]
	sub	r0, r0, #1
	str	r3, [r4, #2360]
	sub	r1, r1, #1
	str	r0, [r4, #204]
	sub	r2, r2, #1
	str	r1, [r4, #176]
	mov	r0, #0
	str	r2, [r4, #260]
	strb	r5, [lr, #1]
	strb	r3, [r7, #681]
	strb	r3, [r4, #9]
	str	ip, [r4, #2852]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5111:
	.align	2
.L5110:
	.word	g_BackUp
	.word	s_pstVfmwChan
	.word	.LC570
	UNWIND(.fnend)
	.size	HEVCDEC_VDMProcSedOnly, .-HEVCDEC_VDMProcSedOnly
	.align	2
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
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
	add	r7, r0, #4096
	ldr	r6, .L5126
	mov	r4, r0
	ldr	r8, [r7, #2416]
	mov	r5, r1
	movw	r2, #27952
	mov	r1, #0
	ldr	r3, [r6, #48]
	blx	r3
	str	r8, [r7, #2416]
	mov	r3, #0
	str	r5, [r4, #2844]
	str	r3, [r4, #2852]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	beq	.L5122
	mov	r3, #17
	mov	r1, #65
	str	r3, [r4, #156]
	mov	r2, #200
	str	r3, [r4, #160]
	mov	r3, #210
	str	r1, [r4, #164]
	str	r2, [r4, #152]
	str	r3, [r4, #168]
.L5114:
	ldr	r0, [r5, #584]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L5123
	ldr	r3, [r4, #156]
	movw	r9, #24912
	ldr	r0, [r4, #160]
	movw	r8, #12668
	ldr	r1, [r4, #168]
	movw	r7, #5036
	mul	r9, r9, r3
	ldr	r3, [r4, #2844]
	ldr	r2, [r4, #152]
	ldr	lr, [r3, #580]
	add	r10, ip, lr
	add	lr, r9, lr
	add	r3, ip, lr
	str	r3, [r4, #2804]
	mla	lr, r8, r0, lr
	add	r0, r1, #1
	movw	r1, #1508
	str	r10, [r4, #2800]
	mul	r2, r1, r2
	add	r1, ip, lr
	str	r1, [r4, #2808]
	mov	r3, r0, asl #7
	ldr	r1, [r4, #164]
	sub	r3, r3, r0, asl #5
	mla	r0, r7, r1, lr
	add	r1, r0, r2
	add	r0, ip, r0
	add	r3, r1, r3
	add	r1, ip, r1
	str	r1, [r4, #2840]
	add	ip, ip, r3
	ldr	r1, [r4, #168]
	str	r0, [r4, #2848]
	str	ip, [r4, #2836]
	add	r3, r3, r1, lsl #2
	ldr	r1, [r4, #2844]
	ldr	r1, [r1, #588]
	cmp	r3, r1
	bhi	.L5124
	ldr	r5, [r5, #616]
	cmp	r5, #0
	beq	.L5125
.L5118:
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #168]
	ldr	ip, [r6, #48]
	mov	r1, #0
	add	r3, r3, #1
	ldr	r0, [r4, #2840]
	mov	r2, r3, asl #7
	sub	r2, r2, r3, asl #5
	blx	ip
	ldr	r2, [r4, #168]
	ldr	r3, [r6, #48]
	mov	r1, #0
	ldr	r0, [r4, #2836]
	mov	r2, r2, asl #2
	blx	r3
	ldr	ip, [r4, #156]
	ldr	r0, [r4, #164]
	movw	r1, #24912
	ldr	lr, [r4, #160]
	movw	r2, #5036
	mul	r1, r1, ip
	movw	r3, #12668
	mul	r2, r2, r0
	ldr	r0, [r4, #2800]
	mul	r3, r3, lr
	sub	r1, r1, #24832
	sub	r1, r1, #80
	ldr	lr, [r4, #2808]
	add	r1, r0, r1
	sub	r2, r2, #4992
	ldr	r0, [r4, #2804]
	sub	r3, r3, #12608
	sub	r2, r2, #44
	sub	r3, r3, #60
	str	r1, [r4, #2824]
	add	r2, lr, r2
	add	r3, r0, r3
	str	r2, [r4, #2832]
	str	r3, [r4, #2828]
	mov	r0, r4
	str	ip, [r1, #4]
	ldr	r3, [r4, #2832]
	ldr	r2, [r4, #160]
	str	r2, [r3, #28]
	ldr	r3, [r4, #2828]
	ldr	r2, [r4, #164]
	str	r2, [r3, #56]
	bl	HEVC_InitScalingOrderTable
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #276]
	beq	.L5119
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	str	r3, [r4, #216]
	bl	HEVC_InitDecPara
	add	r3, r4, #8192
	mov	r2, #0
	movw	r0, #9999
	str	r2, [r3, #3576]
	mov	r2, #1
	ldr	r1, [r4, #164]
	ldr	r3, [r4, #2844]
	str	r0, [r4, #284]
	str	r1, [r4, #320]
	strb	r2, [r4]
	ldr	r2, [r3, #12]
	cmp	r2, #0
	bne	.L5120
.L5121:
	mov	r0, #0
	str	r0, [r4, #2376]
	ldr	r3, [r3, #632]
	str	r3, [r4, #2348]
.L5116:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5120:
	mov	r2, #6
	str	r2, [r3, #24]
	ldr	r3, [r4, #2844]
	b	.L5121
.L5125:
	mov	r2, r9
	ldr	r3, [r6, #48]
	mov	r1, r5
	mov	r0, r10
	blx	r3
	ldr	r2, [r4, #160]
	ldr	r3, [r6, #48]
	mov	r1, r5
	ldr	r0, [r4, #2804]
	mul	r2, r8, r2
	blx	r3
	ldr	r2, [r4, #164]
	ldr	r3, [r6, #48]
	mov	r1, r5
	ldr	r0, [r4, #2808]
	mul	r2, r7, r2
	blx	r3
	ldr	r2, [r4, #152]
	movw	r3, #1508
	ldr	r0, [r4, #2848]
	mul	r2, r3, r2
	b	.L5118
.L5122:
	ldr	r3, [r5, #696]
	str	r3, [r4, #156]
	ldr	r3, [r5, #700]
	str	r3, [r4, #160]
	ldr	r3, [r5, #704]
	str	r3, [r4, #164]
	ldr	r3, [r5, #692]
	add	r2, r3, #5
	str	r2, [r4, #168]
	str	r3, [r4, #152]
	b	.L5114
.L5124:
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L5126+4
	ldr	r1, .L5126+8
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L5116
.L5119:
	ldr	r2, .L5126+4
	mov	r0, #0
	ldr	r1, .L5126+12
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L5116
.L5123:
	ldr	r2, .L5126+4
	ldr	r1, .L5126+16
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L5116
.L5127:
	.align	2
.L5126:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1084
	.word	.LC572
	.word	.LC573
	.word	.LC571
	UNWIND(.fnend)
	.size	HEVCDEC_Init, .-HEVCDEC_Init
	.align	2
	.global	HEVCDEC_GetImageBuffer
	.type	HEVCDEC_GetImageBuffer, %function
HEVCDEC_GetImageBuffer:
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
	UNWIND(.pad #20)
	sub	sp, sp, #20
	ldr	r3, [r0, #180]
	mov	r4, r0
	cmp	r3, #0
	beq	.L5131
	add	r3, r0, #4096
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L5131
	add	r1, r0, #13696
	add	r0, r0, #27904
	add	r1, r1, #16
	add	r0, r0, #48
.L5137:
	ldr	r3, [r1, #48]
	cmp	r3, #0
	bne	.L5132
	cmp	r1, #0
	beq	.L5133
	ldr	lr, [r4, #3028]
	cmp	lr, #0
	beq	.L5133
	ldr	r2, [r4, #3196]
	cmp	r2, r1
	beq	.L5132
	add	r2, r4, #3184
	add	r2, r2, #12
	b	.L5134
.L5135:
	ldr	ip, [r2, #4]!
	cmp	ip, r1
	beq	.L5132
.L5134:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L5135
.L5133:
	ldr	r0, [r4, #276]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L5131
	cmn	r0, #1
	beq	.L5156
.L5155:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L5131:
	mov	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L5132:
	add	r1, r1, #712
	cmp	r1, r0
	bne	.L5137
	add	r0, r4, #6144
	sub	r2, fp, #24
	sub	r1, fp, #28
	add	r0, r0, #24
	bl	GetQueueImgNum
	mov	r0, r4
	bl	HEVC_PrintFrameStoreState
	ldr	r1, .L5157
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r2, [r4, #180]
	ldr	r0, [r4, #3028]
	ldr	r3, [fp, #-28]
	sub	r2, r2, #2
	ldr	r1, [fp, #-24]
	rsb	r2, r0, r2
	add	r0, r3, r1
	cmp	r0, r2
	bge	.L5155
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L5157+4
	ldr	r1, .L5157+8
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L5156:
	ldr	r1, .L5157+12
	mov	r0, #1
	bl	dprint_vfmw
	add	r1, r4, #6144
	add	r1, r1, #24
	ldr	r0, [r4, #276]
	bl	FSP_ClearNotInVoQueue
	b	.L5155
.L5158:
	.align	2
.L5157:
	.word	.LC575
	.word	.LANCHOR0+1100
	.word	.LC576
	.word	.LC574
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageBuffer, .-HEVCDEC_GetImageBuffer
	.align	2
	.global	HEVCDEC_DecodePacket
	.type	HEVCDEC_DecodePacket, %function
HEVCDEC_DecodePacket:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	cmp	r1, #0
	mov	r4, r0
	mov	r0, #0
	str	r0, [fp, #-64]
	str	r0, [fp, #-60]
	str	r0, [fp, #-56]
	beq	.L5239
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L5240
	ldr	ip, [r4, #2844]
	ldrb	lr, [r4, #9]	@ zero_extendqisi2
	ldr	r3, [ip, #8]
	cmp	lr, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r4, #272]
	beq	.L5163
	ldr	r3, [ip, #840]
	cmp	r3, #1
	beq	.L5241
.L5164:
	mov	r0, r4
	bl	HEVC_ReceivePacket
	ldr	r3, [r4, #2816]
	str	r3, [r4, #2820]
	mov	r6, r0
.L5165:
	cmp	r6, #0
	mov	r3, #0
	strb	r3, [r4, #9]
	beq	.L5166
.L5192:
	mov	r5, #0
.L5236:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5241:
	ldr	r3, [ip, #888]
	cmp	r3, #1
	bne	.L5164
	ldr	r3, [r4, #344]
	cmp	r3, #1
	bne	.L5164
	ldr	r3, [r4, #2820]
	mov	r5, r0
	str	r0, [r4, #344]
	strb	r0, [r4, #9]
	str	r3, [r4, #2816]
	b	.L5236
.L5166:
	mov	r0, r4
	bl	HEVCDEC_CheckSedOnly
	subs	r5, r0, #0
	beq	.L5167
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L5237
	ldr	r0, [r4, #276]
	mvn	r5, #0
	bl	HEVC_ReleaseNAL
	mov	r0, r5
	str	r6, [r4, #2816]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5163:
	ldr	r3, [r4, #2816]
	cmp	r3, #0
	movne	r6, #0
	mvneq	r6, #0
	cmp	r3, #0
	bne	.L5165
	ldr	r1, .L5249
	mov	r5, r6
	bl	dprint_vfmw
	b	.L5236
.L5245:
	ldr	r1, .L5249+4
	mov	r0, #22
	bl	dprint_vfmw
.L5237:
	mvn	r5, #0
	b	.L5236
.L5167:
	ldr	r3, [r4, #2816]
	ldr	r8, .L5249+8
	str	r6, [r3, #4]
	ldr	r3, [r4, #2816]
	ldr	r0, [r4, #2796]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2796]
	bl	BsSkip
	ldr	r3, [r4, #276]
	ldr	r3, [r8, r3, asl #2]
	ldrsb	r10, [r3, #44]
	cmp	r10, #1
	movne	r7, #2
	movne	r9, r7
	beq	.L5242
.L5169:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2796]
	ldr	r10, [r4, #2816]
	bl	BsGet
	mov	r1, #6
	str	r0, [r10, #16]
	ldr	r0, [r4, #2796]
	ldr	r10, [r4, #2816]
	bl	BsGet
	str	r0, [r10, #24]
	ldr	r10, [r4, #2816]
	ldr	r2, [r10, #24]
	cmp	r2, #1
	bls	.L5170
	mov	r3, #1
	ldr	r1, .L5249+12
	mov	r0, r3
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L5237
.L5238:
	ldr	r0, [r4, #276]
	mvn	r5, #0
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
	b	.L5236
.L5170:
	ldr	r3, [r4, #2844]
	ldr	r3, [r3, #24]
	bics	r1, r3, #4
	moveq	r1, #1
	movne	r1, #0
	cmp	r2, #0
	moveq	r1, #0
	andne	r1, r1, #1
	cmp	r1, #0
	bne	.L5243
	mov	r1, #3
	ldr	r0, [r4, #2796]
	bl	BsGet
	str	r0, [r10, #28]
	ldr	r10, [r4, #2816]
	ldr	r3, [r10, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r10, #28]
	ldrne	r10, [r4, #2816]
	ldr	r0, [r10, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	beq	.L5244
	mov	r3, #0
	str	r3, [r10, #4]
	ldr	r3, [r4, #2816]
	add	r0, r4, #2992
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2796]
	bl	BsSkip
	cmp	r7, #0
	cmpeq	r9, #1
	moveq	r7, #1
	movne	r7, #0
	cmp	r6, #1
	moveq	r6, #0
	andne	r6, r7, #1
	cmp	r6, #0
	beq	.L5190
	mov	r1, #16
	ldr	r0, [r4, #2796]
	bl	BsSkip
.L5190:
	mov	r1, #1
	ldr	r0, [r4, #2796]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2796]
	ldr	r6, [r4, #2816]
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #16]
	ldr	r0, [r4, #2796]
	ldr	r6, [r4, #2816]
	bl	BsGet
	mov	r1, #3
	str	r0, [r6, #24]
	ldr	r0, [r4, #2796]
	ldr	r6, [r4, #2816]
	bl	BsGet
	str	r0, [r6, #28]
	ldr	r2, [r4, #2816]
	ldr	r3, [r2, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r2, #28]
.L5180:
	mov	r0, r4
	bl	HEVC_DecOneNal
	cmn	r0, #2
	beq	.L5196
	cmp	r0, #0
	bne	.L5245
	add	r3, r4, #4096
	str	r0, [r3, #56]
	ldr	r3, [r4, #2348]
	cmp	r3, #1
	bne	.L5192
	mov	r0, r4
	bl	HEVCDEC_SetDecParam
	b	.L5236
.L5240:
	ldr	r1, .L5249+16
	mvn	r5, #0
	bl	dprint_vfmw
	b	.L5236
.L5242:
	ldr	r9, [r3, #152]
	mov	r0, r4
	ldr	r7, [r3, #156]
	ldr	r3, [r3, #160]
	mov	r1, r9
	mov	r2, r7
	bl	HEVC_VES_Splitter
	cmp	r0, #2
	beq	.L5194
	cmp	r0, #1
	beq	.L5169
.L5196:
	mov	r5, r0
	b	.L5236
.L5244:
	str	r0, [fp, #-72]
	sub	r2, fp, #48
	sub	r1, fp, #52
	mov	r0, r4
	bl	HEVC_InquireSliceProperty
	ldr	r3, [fp, #-72]
	subs	ip, r0, #0
	bne	.L5175
	ldr	r6, [fp, #-52]
	cmp	r6, #1
	beq	.L5246
.L5176:
	ldr	r6, [fp, #-48]
	cmp	r6, #1
	bne	.L5180
	ldr	r3, [r4, #2816]
	mov	r0, r4
	ldr	r3, [r3, #24]
	add	r3, r4, r3
	ldrb	r7, [r3, #4]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L5247
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L5248
.L5183:
	ldr	r0, [r4, #276]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L5180
	sub	r3, fp, #56
	ldr	r0, [r4, #276]
	sub	r2, fp, #60
	sub	r1, fp, #64
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #2844]
	ldr	r0, [r3, #724]
	cmp	r0, #1
	bne	.L5180
	ldr	r6, [fp, #-56]
	cmp	r6, #0
	bgt	.L5186
	ldr	r3, [fp, #-60]
	cmp	r3, #32
	bgt	.L5186
	ldr	r3, [r4, #2852]
	cmp	r3, #0
	bne	.L5186
	ldr	r2, [fp, #-48]
	cmp	r2, #0
	beq	.L5180
	ldr	r3, [r4, #264]
	cmp	r3, #0
	beq	.L5180
	ldr	r3, [r4, #2828]
	ldr	r1, [r4, #336]
	ldr	lr, [r3, #68]
	cmp	lr, r1
	beq	.L5180
	ldr	ip, [r3, #64]
	ldr	r3, [r4, #340]
	subs	r7, ip, r3
	movne	r7, #1
	cmp	r6, #0
	movne	r7, #0
	cmp	r7, #0
	beq	.L5180
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L5249+20
	bl	dprint_vfmw
	ldr	r3, [r4, #2828]
	ldr	r1, .L5249+24
	ldr	r2, [r3, #68]
	ldr	ip, [r1]
	str	r2, [r4, #336]
	cmp	ip, #0
	ldr	r3, [r3, #64]
	str	r3, [r4, #340]
	beq	.L5180
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
	b	.L5180
.L5243:
	ldr	r1, .L5249+28
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	bne	.L5238
	b	.L5237
.L5194:
	mov	r6, r10
	b	.L5169
.L5239:
	mov	r0, r1
	ldr	r1, .L5249+32
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L5236
.L5175:
	ldr	r1, .L5249+36
	mov	r0, r3
	bl	dprint_vfmw
	ldr	r1, [r4, #2816]
	cmp	r1, #0
	beq	.L5188
	ldr	r0, [r4, #276]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2816]
.L5188:
	ldr	r3, .L5249+24
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L5189
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #276]
	blx	ip
.L5189:
	ldr	r3, [r4, #276]
	ldr	r3, [r8, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	bne	.L5237
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L5237
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L5237
	add	r3, r4, #8192
	ldrb	r6, [r3, #3520]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L5237
	ldr	r3, .L5249+40
	mov	r1, r6
	mov	r2, #56
	add	r0, r4, #11712
	mvn	r5, #0
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r4, #3488
	mov	r0, #0
	mov	r1, #0
	strd	r0, [r3, #32]
	strd	r0, [r3, #8]
	strd	r0, [r3, #16]
	strd	r0, [r3, #24]
	str	r6, [r4, #3476]
	b	.L5236
.L5246:
	ldr	r3, [r4, #204]
	cmp	r3, #0
	bne	.L5177
	add	r3, r4, #4096
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L5176
	ldr	r2, .L5249+44
	ldr	r1, .L5249+48
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	b	.L5176
.L5177:
	ldr	r3, [r4, #2816]
	mov	r2, #13
	ldr	r1, .L5249+52
	add	r0, r4, #2992
	mvn	r5, #1
	str	ip, [r3, #4]
	bl	BsInit
	mov	r1, #40
	ldr	r0, [r4, #2796]
	bl	BsSkip
	ldr	r3, [r4, #2816]
	mov	r2, #48
	mov	r0, r4
	str	r2, [r3, #16]
	strb	r6, [r4, #10]
	bl	HEVC_DecOneNal
	ldr	r3, [r4, #304]
	strb	r6, [r4, #9]
	add	r3, r3, #1
	str	r3, [r4, #304]
	b	.L5236
.L5247:
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L5183
	mov	r0, r7
	ldr	r2, .L5249+56
	ldr	r1, .L5249+60
	bl	dprint_vfmw
	b	.L5183
.L5248:
	mov	r0, r6
	ldr	r2, .L5249+56
	ldr	r1, .L5249+64
	bl	dprint_vfmw
	b	.L5183
.L5186:
	mov	r3, #1
	mvn	r5, #1
	strb	r3, [r4, #9]
	b	.L5236
.L5250:
	.align	2
.L5249:
	.word	.LC579
	.word	.LC584
	.word	s_pstVfmwChan
	.word	.LC580
	.word	.LC578
	.word	.LC582
	.word	g_event_report
	.word	.LC581
	.word	.LC577
	.word	.LC583
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+1064
	.word	.LC569
	.word	.LANCHOR0+1148
	.word	.LANCHOR0+1124
	.word	.LC552
	.word	.LC551
	UNWIND(.fnend)
	.size	HEVCDEC_DecodePacket, .-HEVCDEC_DecodePacket
	.align	2
	.global	HEVCDEC_VDMPostProc
	.type	HEVCDEC_VDMPostProc, %function
HEVCDEC_VDMPostProc:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	mov	r4, r0
	ldr	r0, [r0, #2844]
	mov	r7, r3
	ldr	ip, [r5, #60]
	ldr	r3, [fp, #4]
	cmp	ip, #0
	ldr	r6, [r0, #636]
	str	r1, [r5, #40]
	ldrneb	r1, [r5, #2429]	@ zero_extendqisi2
	ldr	r2, [fp, #8]
	strneb	r1, [ip, #3]
	ldrneb	r1, [r5, #2424]	@ zero_extendqisi2
	strneb	r1, [ip, #4]
	ldr	ip, [r4, #2376]
	ldrne	r0, [r4, #2844]
	cmp	ip, #1
	bls	.L5253
.L5256:
	ldr	r1, [r5, #20]
	cmp	r1, #1920
	bhi	.L5286
.L5254:
	ldr	r1, [r0, #632]
	cmp	r3, #0
	str	r1, [r4, #2348]
	beq	.L5259
.L5290:
	ldr	r3, .L5291
	mov	r0, r2, asl #6
	sub	r2, r0, r2, asl #3
	add	r2, r2, r3
	ldr	r3, [r2, #4]
	cmp	r3, #3
	beq	.L5287
	cmp	r3, #1
	beq	.L5259
.L5262:
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_StorePicInDPB
	subs	r8, r0, #0
	bne	.L5288
	cmp	r6, #1
	beq	.L5289
.L5264:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #172]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5286:
	ldr	r1, [r0, #8]
	cmp	r1, #2
	movne	r1, #0
	strne	r1, [r4, #2348]
	beq	.L5254
	cmp	r3, #0
	bne	.L5290
.L5259:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	b	.L5262
.L5288:
	mov	r2, r8
	ldr	r1, .L5291+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5253:
	add	ip, ip, #1
	str	ip, [r4, #2376]
	cmp	ip, #1
	bls	.L5254
	b	.L5256
.L5289:
	ldr	r7, [r4, #2852]
	ldr	r3, [r7, #1292]
	add	r3, r7, r3, lsl #2
	ldr	r10, [r3, #1476]
	mov	r0, r10
	bl	MEM_Phy2Vir
	ldr	r2, [r7, #76]
	ldr	r3, [r7, #192]
	mov	r1, r10
	ldr	r7, [r7, #196]
	mov	r6, r6, asl r2
	sub	r3, r3, #1
	ldr	lr, .L5291+8
	sub	ip, r7, #1
	add	r3, r3, r6
	add	r7, ip, r6
	mov	r3, r3, lsr r2
	ldr	ip, [lr, #140]
	mov	r7, r7, lsr r2
	mul	r7, r7, r3
	mov	r2, r7, asl #4
	mov	r9, r0
	blx	ip
	cmp	r7, #0
	beq	.L5275
	mov	r2, r8
	mov	lr, r8
	mov	r6, r8
	mov	r1, r8
	mov	r0, r9
	mvn	r8, #-2147483648
.L5272:
	ldrh	ip, [r0, #4]
	ubfx	r3, ip, #0, #15
	sxth	ip, ip
	rsb	r9, ip, #0
	tst	ip, #32768
	ldrh	ip, [r0, #6]
	ubfxne	r3, r9, #0, #15
	ubfx	r9, ip, #0, #15
	sxth	ip, ip
	tst	ip, #32768
	rsb	r10, ip, #0
	ubfxne	r9, r10, #0, #15
	add	r3, r3, r9
	cmp	r6, r3
	movlt	r6, r3
	cmp	r3, #0
	addeq	lr, lr, #1
	beq	.L5271
	cmp	r8, r3
	movge	r8, r3
.L5271:
	add	r1, r1, #1
	add	r2, r2, r3
	cmp	r1, r7
	add	r0, r0, #16
	bne	.L5272
	mov	r9, #100
	mov	r0, r2
	mul	r9, r9, lr
.L5265:
	mov	r1, r7
	bl	__aeabi_uidiv
	mov	r1, r7
	mov	r10, r0
	mov	r0, r9
	bl	__aeabi_uidiv
	mov	r3, r0
	ldr	r0, [r5, #60]
	cmp	r3, #100
	moveq	r8, #0
	cmp	r0, #0
	beq	.L5274
	str	r6, [r0, #324]
	ldr	r2, [r5, #60]
	str	r8, [r2, #328]
	ldr	r2, [r5, #60]
	str	r10, [r2, #332]
	ldr	r2, [r5, #60]
	str	r3, [r2, #336]
	str	r6, [r5, #308]
	str	r8, [r5, #312]
	str	r10, [r5, #316]
	str	r3, [r5, #320]
	b	.L5264
.L5287:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L5275:
	mov	r9, r7
	mov	r0, r7
	mvn	r8, #-2147483648
	mov	r6, r7
	b	.L5265
.L5274:
	ldr	r1, .L5291+12
	bl	dprint_vfmw
	b	.L5264
.L5292:
	.align	2
.L5291:
	.word	g_VdmDrvParam+40
	.word	.LC585
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC586
	UNWIND(.fnend)
	.size	HEVCDEC_VDMPostProc, .-HEVCDEC_VDMPostProc
	.align	2
	.global	HEVCDEC_GetImageWidth
	.type	HEVCDEC_GetImageWidth, %function
HEVCDEC_GetImageWidth:
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
	ldr	r2, [r0, #2828]
	ldr	r3, [r2, #132]
	ldr	r2, [r2, #64]
	rsb	r0, r3, #0
	add	r3, r3, r2
	sub	r3, r3, #1
	and	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageWidth, .-HEVCDEC_GetImageWidth
	.align	2
	.global	HEVCDEC_GetImageHeight
	.type	HEVCDEC_GetImageHeight, %function
HEVCDEC_GetImageHeight:
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
	ldr	r2, [r0, #2828]
	ldr	r3, [r2, #132]
	ldr	r2, [r2, #68]
	rsb	r0, r3, #0
	add	r3, r3, r2
	sub	r3, r3, #1
	and	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCDEC_GetImageHeight, .-HEVCDEC_GetImageHeight
	.align	2
	.global	HEVCDEC_GetRemainImg
	.type	HEVCDEC_GetRemainImg, %function
HEVCDEC_GetRemainImg:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	ldr	r3, [r0, #3028]
	mov	r4, r0
	cmp	r3, #0
	bne	.L5296
	b	.L5300
.L5310:
	ldr	r3, [fp, #-36]
.L5297:
	mov	r1, r3
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r3, [r4, #3028]
	cmp	r3, #0
	beq	.L5300
.L5296:
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	mov	r6, #1
	bl	HEVC_GetMinPOC
	ldr	r3, [fp, #-36]
	mov	r0, r4
	add	r2, r4, r3, lsl #2
	ldr	r5, [r2, #3196]
	cmp	r5, #0
	mov	r1, r5
	beq	.L5297
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	cmp	r2, r6
	beq	.L5297
	strb	r6, [r5, #2]
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r7, r0, #0
	bne	.L5310
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_OutputFrame
	cmp	r0, #0
	beq	.L5310
	mov	r0, r7
	ldr	r2, .L5311
	ldr	r1, .L5311+4
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	b	.L5310
.L5300:
	add	r0, r4, #6144
	add	r0, r0, #24
	bl	GetVoLastImageID
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L5312:
	.align	2
.L5311:
	.word	.LANCHOR0+1164
	.word	.LC497
	UNWIND(.fnend)
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.global	g_IsDeced
	.global	g_TsToRsMap
	.global	s_TmpParam
	.global	g_RpuStartCode
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.16709, %object
	.size	__func__.16709, 17
__func__.16709:
	.ascii	"HEVC_OutputFrame\000"
	.space	3
	.type	__func__.15175, %object
	.size	__func__.15175, 26
__func__.15175:
	.ascii	"HEVC_OutputImgToViewQueue\000"
	.space	2
	.type	__func__.14599, %object
	.size	__func__.14599, 24
__func__.14599:
	.ascii	"HEVC_CheckVpsExtOverlap\000"
	.type	__func__.14604, %object
	.size	__func__.14604, 24
__func__.14604:
	.ascii	"HEVC_CheckPpsExtOverlap\000"
	.type	__func__.14609, %object
	.size	__func__.14609, 26
__func__.14609:
	.ascii	"HEVC_CheckSliceExtOverlap\000"
	.space	2
	.type	SarTable.15370, %object
	.size	SarTable.15370, 136
SarTable.15370:
	.word	1
	.word	1
	.word	1
	.word	1
	.word	12
	.word	11
	.word	10
	.word	11
	.word	16
	.word	11
	.word	40
	.word	33
	.word	24
	.word	11
	.word	20
	.word	11
	.word	32
	.word	11
	.word	80
	.word	33
	.word	18
	.word	11
	.word	15
	.word	11
	.word	64
	.word	33
	.word	160
	.word	99
	.word	4
	.word	3
	.word	3
	.word	2
	.word	2
	.word	1
	.type	__func__.15528, %object
	.size	__func__.15528, 18
__func__.15528:
	.ascii	"HEVC_CalcTileInfo\000"
	.space	2
	.type	__func__.15996, %object
	.size	__func__.15996, 27
__func__.15996:
	.ascii	"HEVC_GetUnRefPicWithMinPoc\000"
	.space	1
	.type	__func__.16005, %object
	.size	__func__.16005, 21
__func__.16005:
	.ascii	"HEVC_IncreaseDPBSize\000"
	.space	3
	.type	__func__.16257, %object
	.size	__func__.16257, 17
__func__.16257:
	.ascii	"HEVC_WritePicMsg\000"
	.space	3
	.type	__func__.16286, %object
	.size	__func__.16286, 16
__func__.16286:
	.ascii	"HEVC_CheckListX\000"
	.type	__func__.16450, %object
	.size	__func__.16450, 16
__func__.16450:
	.ascii	"HEVC_RepairList\000"
	.type	__func__.16537, %object
	.size	__func__.16537, 16
__func__.16537:
	.ascii	"HEVC_ArrangeMem\000"
	.type	__func__.16610, %object
	.size	__func__.16610, 20
__func__.16610:
	.ascii	"HEVC_RemoveApcStore\000"
	.type	__func__.16879, %object
	.size	__func__.16879, 21
__func__.16879:
	.ascii	"HEVC_CheckFrameStore\000"
	.space	3
	.type	__func__.16947, %object
	.size	__func__.16947, 19
__func__.16947:
	.ascii	"HEVC_GetSLHDR1Info\000"
	.space	1
	.type	__func__.17074, %object
	.size	__func__.17074, 14
__func__.17074:
	.ascii	"HEVC_IsNewPic\000"
	.space	2
	.type	g_Quant8InterDefault, %object
	.size	g_Quant8InterDefault, 64
g_Quant8InterDefault:
	.word	269488144
	.word	403968529
	.word	286265360
	.word	421008402
	.word	303108112
	.word	471406612
	.word	336728336
	.word	555489560
	.word	403968529
	.word	690035737
	.word	421008402
	.word	908665116
	.word	471406612
	.word	1194731809
	.word	555489560
	.word	1531393577
	.type	g_QuantTsDefault, %object
	.size	g_QuantTsDefault, 16
g_QuantTsDefault:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	__func__.17389, %object
	.size	__func__.17389, 16
__func__.17389:
	.ascii	"HEVC_ReleaseNAL\000"
	.type	__func__.16569, %object
	.size	__func__.16569, 20
__func__.16569:
	.ascii	"HEVC_InitDecBuffers\000"
	.type	__func__.15023, %object
	.size	__func__.15023, 23
__func__.15023:
	.ascii	"HEVC_ParseVPSExtension\000"
	.space	1
	.type	g_CropUnitX, %object
	.size	g_CropUnitX, 16
g_CropUnitX:
	.word	1
	.word	2
	.word	2
	.word	1
	.type	g_CropUnitY, %object
	.size	g_CropUnitY, 16
g_CropUnitY:
	.word	1
	.word	2
	.word	1
	.word	1
	.type	__func__.16110, %object
	.size	__func__.16110, 27
__func__.16110:
	.ascii	"HEVC_DecSliceSegmentHeader\000"
	.space	1
	.type	__func__.16548, %object
	.size	__func__.16548, 13
__func__.16548:
	.ascii	"HEVC_InitDPB\000"
	.space	3
	.type	__func__.15232, %object
	.size	__func__.15232, 20
__func__.15232:
	.ascii	"HEVC_ArrangeShvcMem\000"
	.type	__func__.16716, %object
	.size	__func__.16716, 19
__func__.16716:
	.ascii	"HEVC_OutputCurrPic\000"
	.space	1
	.type	__func__.16721, %object
	.size	__func__.16721, 23
__func__.16721:
	.ascii	"HEVC_FirstFrameFastOut\000"
	.space	1
	.type	__func__.16871, %object
	.size	__func__.16871, 19
__func__.16871:
	.ascii	"HEVC_OutputFrmToVO\000"
	.space	1
	.type	__func__.16833, %object
	.size	__func__.16833, 22
__func__.16833:
	.ascii	"HEVC_OutputFrmFromDPB\000"
	.space	2
	.type	__func__.16011, %object
	.size	__func__.16011, 30
__func__.16011:
	.ascii	"HEVC_OutputUnRefPicWithMinPoc\000"
	.space	2
	.type	__func__.16846, %object
	.size	__func__.16846, 27
__func__.16846:
	.ascii	"HEVC_FlushOutputFrmFromDPB\000"
	.space	1
	.type	__func__.17452, %object
	.size	__func__.17452, 14
__func__.17452:
	.ascii	"HEVC_ClearDPB\000"
	.space	2
	.type	__func__.16016, %object
	.size	__func__.16016, 23
__func__.16016:
	.ascii	"HEVC_RecoverDPBProcess\000"
	.space	1
	.type	__func__.16807, %object
	.size	__func__.16807, 20
__func__.16807:
	.ascii	"HEVC_InsertFrmInDPB\000"
	.type	__func__.16726, %object
	.size	__func__.16726, 22
__func__.16726:
	.ascii	"HEVC_SimpleDPBProcess\000"
	.space	2
	.type	__func__.16731, %object
	.size	__func__.16731, 21
__func__.16731:
	.ascii	"HEVC_DecOrderProcess\000"
	.space	3
	.type	__func__.16736, %object
	.size	__func__.16736, 22
__func__.16736:
	.ascii	"HEVC_DispOrderProcess\000"
	.space	2
	.type	__func__.16750, %object
	.size	__func__.16750, 19
__func__.16750:
	.ascii	"HEVC_StorePicInDPB\000"
	.space	1
	.type	__func__.16372, %object
	.size	__func__.16372, 12
__func__.16372:
	.ascii	"HEVC_DecVDM\000"
	.type	__func__.15258, %object
	.size	__func__.15258, 18
__func__.15258:
	.ascii	"HEVC_VES_Splitter\000"
	.space	2
	.type	__func__.16047, %object
	.size	__func__.16047, 14
__func__.16047:
	.ascii	"HEVC_DecSlice\000"
	.space	2
	.type	__func__.17534, %object
	.size	__func__.17534, 20
__func__.17534:
	.ascii	"HEVC_HaveSliceToDec\000"
	.type	__func__.17580, %object
	.size	__func__.17580, 13
__func__.17580:
	.ascii	"HEVCDEC_Init\000"
	.space	3
	.type	__func__.17594, %object
	.size	__func__.17594, 23
__func__.17594:
	.ascii	"HEVCDEC_GetImageBuffer\000"
	.space	1
	.type	__func__.17609, %object
	.size	__func__.17609, 21
__func__.17609:
	.ascii	"HEVCDEC_DecodePacket\000"
	.space	3
	.type	g_HevcNalTypeEOP, %object
	.size	g_HevcNalTypeEOP, 13
g_HevcNalTypeEOP:
	.byte	0
	.byte	0
	.byte	1
	.byte	96
	.byte	0
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.space	3
	.type	__func__.17658, %object
	.size	__func__.17658, 21
__func__.17658:
	.ascii	"HEVCDEC_GetRemainImg\000"
	.data
	.align	2
.LANCHOR4 = . + 0
	.type	g_Quant8IntraDefault, %object
	.size	g_Quant8IntraDefault, 64
g_Quant8IntraDefault:
	.word	269488144
	.word	404034065
	.word	269488144
	.word	420877073
	.word	303108112
	.word	488183316
	.word	353505296
	.word	606018328
	.word	403968273
	.word	791225118
	.word	454431506
	.word	1094069283
	.word	521737749
	.word	1480996393
	.word	605886744
	.word	1935163695
	.type	g_QuantTSDefault4x4, %object
	.size	g_QuantTSDefault4x4, 16
g_QuantTSDefault4x4:
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
	.type	g_QuantInterDefault8x8, %object
	.size	g_QuantInterDefault8x8, 64
g_QuantInterDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	17
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	18
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	20
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	24
	.byte	25
	.byte	28
	.byte	33
	.byte	41
	.byte	54
	.byte	71
	.byte	91
	.type	g_QuantIntraDefault8x8, %object
	.size	g_QuantIntraDefault8x8, 64
g_QuantIntraDefault8x8:
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	21
	.byte	24
	.byte	16
	.byte	16
	.byte	16
	.byte	16
	.byte	17
	.byte	19
	.byte	22
	.byte	25
	.byte	16
	.byte	16
	.byte	17
	.byte	18
	.byte	20
	.byte	22
	.byte	25
	.byte	29
	.byte	16
	.byte	16
	.byte	18
	.byte	21
	.byte	24
	.byte	27
	.byte	31
	.byte	36
	.byte	17
	.byte	17
	.byte	20
	.byte	24
	.byte	30
	.byte	35
	.byte	41
	.byte	47
	.byte	18
	.byte	19
	.byte	22
	.byte	27
	.byte	35
	.byte	44
	.byte	54
	.byte	65
	.byte	21
	.byte	22
	.byte	25
	.byte	31
	.byte	41
	.byte	54
	.byte	70
	.byte	88
	.byte	24
	.byte	25
	.byte	29
	.byte	36
	.byte	47
	.byte	65
	.byte	88
	.byte	115
	.type	g_RpuStartCode, %object
	.size	g_RpuStartCode, 5
g_RpuStartCode:
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	25
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC2:
	ASCII(.ascii	"../../core/syntax/hevc.c\000" )
	.space	3
.LC3:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC4:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%" )
	ASCII(.ascii	"d, logic_fs=%p, dec_fs=%p)\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"%s: pImg is NULL!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"View %d image queue is full, discard head image %d." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"%s: view0 frame poc(%d) > view1 frame poc(%d)\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"%s: view1 frame poc(%d) > view0 frame poc(%d)\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"%s: Image(view=0, poc=%d) output failed!\012\000" )
	.space	2
.LC10:
	ASCII(.ascii	"%s: Image(view=1, poc=%d) output failed!\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"%s: InsertImgToVoQueue failed!\012\000" )
.LC12:
	ASCII(.ascii	"%s pVPSExt = NULL\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"%s pPPSExt = NULL\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"%s pSlcExt = NULL\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"dar=%d\012\000" )
.LC16:
	ASCII(.ascii	"--------------- PrintNaluArraySlot START ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC18:
	ASCII(.ascii	"--------------- PrintNaluArraySlot END ------------" )
	ASCII(.ascii	"---\012\000" )
.LC19:
	ASCII(.ascii	"NalArray[%d]=%p,is_valid=%d   \000" )
	.space	1
.LC20:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX START ---------" )
	ASCII(.ascii	"------\012\000" )
	.space	1
.LC21:
	ASCII(.ascii	"List0, size: %d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"List1, size: %d\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"pListX[0][%d]:%p \000" )
	.space	2
.LC24:
	ASCII(.ascii	"pFrameStore:%p \000" )
.LC25:
	ASCII(.ascii	"pLogicFs:%p \000" )
	.space	3
.LC26:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX END -----------" )
	ASCII(.ascii	"----\012\000" )
	.space	3
.LC27:
	ASCII(.ascii	"pListX[1][%d]: %p\000" )
	.space	2
.LC28:
	ASCII(.ascii	"--------------- PrintFrameStoreState START --------" )
	ASCII(.ascii	"-------\012\000" )
.LC29:
	ASCII(.ascii	"--------------- PrintFrameStoreState END ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC30:
	ASCII(.ascii	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displa" )
	ASCII(.ascii	"yed=%d \000" )
	.space	1
.LC31:
	ASCII(.ascii	"p_usrdat[%d]=%p \000" )
	.space	3
.LC32:
	ASCII(.ascii	"--------------- PrintAPCState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"Layer %d: APC.used_size:%d, APC.size:%d\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"%d: is_used=%d, idc=%d, poc=%d\012\000" )
.LC35:
	ASCII(.ascii	"--------------- PrintAPCState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC36:
	ASCII(.ascii	"--------------- PrintDPBState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC37:
	ASCII(.ascii	"DPB: size:%d, used_size:%d, negative:%d, positive:%" )
	ASCII(.ascii	"d, longterm:%d\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"fs[%d]:%p view %d non_existing:%d state:%d is_ref:%" )
	ASCII(.ascii	"d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_" )
	ASCII(.ascii	"ref:%d fsp_disp:%d logic_id:%d img_id:%d\012\000" )
.LC39:
	ASCII(.ascii	"--------------- PrintDPBState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC40:
	ASCII(.ascii	"fs[%d]\011\000" )
.LC41:
	ASCII(.ascii	"LogicFs:%p\011\000" )
.LC42:
	ASCII(.ascii	"LogicTick:%d\011\000" )
	.space	2
.LC43:
	ASCII(.ascii	"IsRef:%d\011\000" )
	.space	2
.LC44:
	ASCII(.ascii	"DispState:%d\011\000" )
	.space	2
.LC45:
	ASCII(.ascii	"LogicFs:Null\011\000" )
	.space	2
.LC46:
	ASCII(.ascii	"DecFs:%p\011\000" )
	.space	2
.LC47:
	ASCII(.ascii	"DecTick:%d\011\000" )
.LC48:
	ASCII(.ascii	"DecFs:Null\011\000" )
.LC49:
	ASCII(.ascii	"DispFs:%p\011\000" )
	.space	1
.LC50:
	ASCII(.ascii	"DispTick:%d\011\000" )
	.space	3
.LC51:
	ASCII(.ascii	"DispFs:Null\011\000" )
	.space	3
.LC52:
	ASCII(.ascii	"%s num_tile_columns(%d) out of range(0, %d].\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"%s num_tile_rows(%d) out of range(0, %d].\012\000" )
	.space	1
.LC54:
	ASCII(.ascii	"%s 0 idx(%d) out of range(0, 512).\012\000" )
.LC55:
	ASCII(.ascii	"%s 1 idx(%d) out of range(0, 512).\012\000" )
.LC56:
	ASCII(.ascii	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC57:
	ASCII(.ascii	"pListX[0][%d] = NULL, listXsize[0] = %d\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) inval" )
	ASCII(.ascii	"id\012\000" )
	.space	1
.LC60:
	ASCII(.ascii	"pListX[1][%d] = NULL, listXsize[1] = %d\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC62:
	ASCII(.ascii	"pListX[i][%d] pstLogicFs(%p) invalid\012\000" )
	.space	2
.LC63:
	ASCII(.ascii	"%s DPB.used_size(%d) >= 17.\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"%s can't find such pic.\012\000" )
	.space	3
.LC65:
	ASCII(.ascii	"%s find pos=%d, poc=%d.\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"%s DPB.size(%d) already reached max(%d).\012\000" )
	.space	2
.LC67:
	ASCII(.ascii	"%s increase DPB size to %d\012\000" )
.LC68:
	ASCII(.ascii	"%s no enough fs(total_fs_num=%d) to increase DPB si" )
	ASCII(.ascii	"ze.\012\000" )
.LC69:
	ASCII(.ascii	"TileWidthInCtb is 0\012\000" )
	.space	3
.LC70:
	ASCII(.ascii	"image_id=%d, pmv_idc=%d\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC72:
	ASCII(.ascii	"%s call HEVC_CalcTileInfo failed.\012\000" )
	.space	1
.LC73:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC74:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"%s ERROR: bHaveIndependentSlice = 0\012\012\000" )
	.space	2
.LC76:
	ASCII(.ascii	"ListX ERROR: list0size >= %d\012\000" )
	.space	2
.LC77:
	ASCII(.ascii	"ListX ERROR: list1size >= %d\012\000" )
	.space	2
.LC78:
	ASCII(.ascii	"pListX[0][%d] = NULL\012\000" )
	.space	2
.LC79:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL\012\000" )
	.space	1
.LC80:
	ASCII(.ascii	"pListX[1][%d] = NULL\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL\012\000" )
	.space	1
.LC82:
	ASCII(.ascii	"NumSlicePara(%d) >= MaxSliceNum(%d)\012\000" )
	.space	3
.LC83:
	ASCII(.ascii	"width is larger than 3! (%d, %d)\012\000" )
	.space	2
.LC84:
	ASCII(.ascii	"height is larger than 3! (%d, %d)\012\000" )
	.space	1
.LC85:
	ASCII(.ascii	"line:%d pic_parameter_set_id(%d) out of range(0,%d)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC86:
	ASCII(.ascii	"line:%d seq_parameter_set_id(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC87:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d) num_of_pics %d\012\000" )
	.space	3
.LC88:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d)(neg%d + pos%d)\012\000" )
	.space	3
.LC89:
	ASCII(.ascii	"%s unkown slice type(%d).\012\000" )
	.space	1
.LC90:
	ASCII(.ascii	"%s pListX[%d] no available pic to repair.\012\000" )
	.space	1
.LC91:
	ASCII(.ascii	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\012" )
	ASCII(.ascii	"\000" )
.LC92:
	ASCII(.ascii	"HEVC_InitListX error.\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"HEVC_RepairList error.\012\000" )
.LC94:
	ASCII(.ascii	"%s image size abnormal(%dx%d)\012\000" )
	.space	1
.LC95:
	ASCII(.ascii	"%s HEVC FSP_ConfigInstance failed!\012\000" )
.LC96:
	ASCII(.ascii	"%s fs[%d]->view_id = %d invalid.\012\000" )
	.space	2
.LC97:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC98:
	ASCII(.ascii	"Cant find free apc slot.\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"%s frame logic_fs_id=%d, state=%d\012\000" )
	.space	1
.LC100:
	ASCII(.ascii	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null," )
	ASCII(.ascii	" logic_fs_id = %d\012\000" )
	.space	2
.LC101:
	ASCII(.ascii	"%s frame poc=%d, is already output\012\000" )
.LC102:
	ASCII(.ascii	"%s frame(%p) invalid, state:%d, non_existing:%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC103:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC104:
	ASCII(.ascii	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STA" )
	ASCII(.ascii	"TE_NOT_USED\012\000" )
.LC105:
	ASCII(.ascii	"%-5d   specVersion\012\000" )
.LC106:
	ASCII(.ascii	"%-5d   payloadMode\012\000" )
.LC107:
	ASCII(.ascii	"%-5d   hdrPicColourSpace\012\000" )
	.space	2
.LC108:
	ASCII(.ascii	"%-5d   hdrMasterDisplayColourSpace\012\000" )
.LC109:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMaxLuminance\012\000" )
	.space	3
.LC110:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMinLuminance\012\000" )
	.space	3
.LC111:
	ASCII(.ascii	"%-5d   sdrPicColourSpace\012\000" )
	.space	2
.LC112:
	ASCII(.ascii	"%-5d   sdrMasterDisplayColourSpace\012\000" )
.LC113:
	ASCII(.ascii	"%-5d   tmInputSignalBlackLevelOffset\012\000" )
	.space	2
.LC114:
	ASCII(.ascii	"%-5d   tmInputSignalWhiteLevelOffset\012\000" )
	.space	2
.LC115:
	ASCII(.ascii	"%-5d   shadowGain\012\000" )
	.space	1
.LC116:
	ASCII(.ascii	"%-5d   highlightGain\012\000" )
	.space	2
.LC117:
	ASCII(.ascii	"%-5d   midToneWidthAdjFactor\012\000" )
	.space	2
.LC118:
	ASCII(.ascii	"%-5d   tmOutputFineTuningNumVal\012\000" )
	.space	3
.LC119:
	ASCII(.ascii	"%-5d   saturationGainNumVal\012\000" )
	.space	3
.LC120:
	ASCII(.ascii	"%-5d   tmOutputFineTuningX[%d]\012\000" )
.LC121:
	ASCII(.ascii	"%-5d   tmOutputFineTuningY[%d]\012\000" )
.LC122:
	ASCII(.ascii	"%-5d   saturationGainX[%d]\012\000" )
.LC123:
	ASCII(.ascii	"%-5d   saturationGainY[%d]\012\000" )
.LC124:
	ASCII(.ascii	"%-5d   luminanceMappingNumVal\012\000" )
	.space	1
.LC125:
	ASCII(.ascii	"%-5d   colourCorrectionNumVal\012\000" )
	.space	1
.LC126:
	ASCII(.ascii	"%-5d   luminanceMappingX[%d]\012\000" )
	.space	2
.LC127:
	ASCII(.ascii	"%-5d   luminanceMappingY[%d]\012\000" )
	.space	2
.LC128:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuA\012\000" )
	.space	3
.LC129:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuB\012\000" )
	.space	3
.LC130:
	ASCII(.ascii	"%-5d   colourCorrectionX[%d]\012\000" )
	.space	2
.LC131:
	ASCII(.ascii	"%-5d   colourCorrectionY[%d]\012\000" )
	.space	2
.LC132:
	ASCII(.ascii	"======SL_HDR1_METADATA= %d=======\012\000" )
	.space	1
.LC133:
	ASCII(.ascii	"%s, [%d %d %d %d %d]\012\000" )
	.space	2
.LC134:
	ASCII(.ascii	"%s HDR_Metadata_phy_addr is invalid!!\012\000" )
	.space	1
.LC135:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC136:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC137:
	ASCII(.ascii	"FSP_GetFspType -1\012\000" )
	.space	1
.LC138:
	ASCII(.ascii	"FSP_GetLogicFs return NULL\012\000" )
.LC139:
	ASCII(.ascii	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), err" )
	ASCII(.ascii	"or resilence.\012\000" )
	.space	2
.LC140:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC141:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC142:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC143:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC144:
	ASCII(.ascii	"sps with this seq_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC145:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of r" )
	ASCII(.ascii	"ange\012\000" )
	.space	3
.LC146:
	ASCII(.ascii	"vps with this video_parameter_set_id = %d havn't be" )
	ASCII(.ascii	" decoded\012\000" )
	.space	3
.LC147:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, n" )
	ASCII(.ascii	"al_unit_type = %d, should skip this frame\012\000" )
	.space	2
.LC148:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d," )
	ASCII(.ascii	" nal_unit_type = %d, should skip this frame\012\000" )
.LC149:
	ASCII(.ascii	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocC" )
	ASCII(.ascii	"RA = %d, nal_unit_type = %d, should skip this frame" )
	ASCII(.ascii	"\012\000" )
.LC150:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code should not be zero.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC151:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code:%d\012\000" )
	.space	3
.LC152:
	ASCII(.ascii	"reserved_zero_2bits not equal 0.\012\000" )
	.space	2
.LC153:
	ASCII(.ascii	"HEVC_GetScalingListDefaultAddress NULL.\012\000" )
	.space	3
.LC154:
	ASCII(.ascii	"Error, BsLen: 0x%x, TotalPos: 0x%x\012\000" )
.LC155:
	ASCII(.ascii	"Panic: All zero data sequence in RBSP \012\000" )
.LC156:
	ASCII(.ascii	"nal_trail_zero_bit_num err\012\000" )
.LC157:
	ASCII(.ascii	"%s release streambuff=%p, bitstream_length=%d\012\000" )
	.space	1
.LC158:
	ASCII(.ascii	"%s DPB size exceed %d, force to %d\012\000" )
.LC159:
	ASCII(.ascii	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\012\000" )
	.space	2
.LC160:
	ASCII(.ascii	"END of the bit buffer, copy the first packet!\012\000" )
	.space	1
.LC161:
	ASCII(.ascii	"tone_map_id\000" )
.LC162:
	ASCII(.ascii	"Unsupport: target_bit_depth(%d) > 8\012\000" )
	.space	3
.LC163:
	ASCII(.ascii	"pTon->num_pivots > 256\012\000" )
.LC164:
	ASCII(.ascii	"frame_packing_arrangement_id\000" )
	.space	3
.LC165:
	ASCII(.ascii	"frame_packing_arrangement_type(%d) out of range\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC166:
	ASCII(.ascii	"decoding_unit_idx\000" )
	.space	2
.LC167:
	ASCII(.ascii	"num_sps_ids_minus1\000" )
	.space	1
.LC168:
	ASCII(.ascii	"pAct->num_sps_ids_minus1 > 15\012\000" )
	.space	1
.LC169:
	ASCII(.ascii	"active_seq_parameter_set_id\000" )
.LC170:
	ASCII(.ascii	"bp_seq_parameter_set_id\000" )
.LC171:
	ASCII(.ascii	"Wrong bp_seq_parameter_set_id = %d, should be 0 to " )
	ASCII(.ascii	"15!\012\000" )
.LC172:
	ASCII(.ascii	"num_decoding_units_minus1\000" )
	.space	2
.LC173:
	ASCII(.ascii	"pPic->num_decoding_units_minus1 > 255\012\000" )
	.space	1
.LC174:
	ASCII(.ascii	"num_nalus_in_du_minus1\000" )
	.space	1
.LC175:
	ASCII(.ascii	"cv_rec_id\000" )
	.space	2
.LC176:
	ASCII(.ascii	"HEVC_Sei_User_Data_Registered_Itu_T_T35 payloadSize" )
	ASCII(.ascii	" < 4!!\012\000" )
	.space	1
.LC177:
	ASCII(.ascii	"delta_idx_minus1\000" )
	.space	3
.LC178:
	ASCII(.ascii	"delta_idx(%d) > idx(%d).\012\000" )
	.space	2
.LC179:
	ASCII(.ascii	"rIdx(%d) > (idx-1)(%d) or < 0).\012\000" )
	.space	3
.LC180:
	ASCII(.ascii	"abs_delta_rps_minus1\000" )
	.space	3
.LC181:
	ASCII(.ascii	"pTempRPset->num_of_pics(%d) out of range(0,15).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC182:
	ASCII(.ascii	"num_of_pics out of range(0,15).\012\000" )
	.space	3
.LC183:
	ASCII(.ascii	"num_negative_pics\000" )
	.space	2
.LC184:
	ASCII(.ascii	"pTempRPset->num_negative_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC185:
	ASCII(.ascii	"num_positive_pics\000" )
	.space	2
.LC186:
	ASCII(.ascii	"pTempRPset->num_positive_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC187:
	ASCII(.ascii	"pShortTermRpset->num_of_pics(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC188:
	ASCII(.ascii	"delta_poc_s0_minus1\000" )
.LC189:
	ASCII(.ascii	"delta_poc_s0_minus1(%d) out of range.\012\000" )
	.space	1
.LC190:
	ASCII(.ascii	"delta_poc_s1_minus1\000" )
.LC191:
	ASCII(.ascii	"elemental_duration_in_tc_minus1\000" )
.LC192:
	ASCII(.ascii	"cpb_cnt_minus1\000" )
	.space	1
.LC193:
	ASCII(.ascii	"cpb_cnt_minus1(%d) out of range(0,31).\012\000" )
.LC194:
	ASCII(.ascii	"bit_rate_value_minus1\000" )
	.space	2
.LC195:
	ASCII(.ascii	"cpb_size_value_minus1\000" )
	.space	2
.LC196:
	ASCII(.ascii	"cpb_size_du_value_minus1\000" )
	.space	3
.LC197:
	ASCII(.ascii	"bit_rate_du_value_minus1\000" )
	.space	3
.LC198:
	ASCII(.ascii	"%s: vps_max_layers_minus1 %d out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC199:
	ASCII(.ascii	"num_add_layer_sets\000" )
	.space	1
.LC200:
	ASCII(.ascii	"%s %d: num_add_layer_sets %d >= HEVC_MAX_VPS_OP_SET" )
	ASCII(.ascii	"S_PLUS1 %d\012\000" )
	.space	1
.LC201:
	ASCII(.ascii	"vps_num_profile_tier_level_minus1\000" )
	.space	2
.LC202:
	ASCII(.ascii	"num_add_olss\000" )
	.space	3
.LC203:
	ASCII(.ascii	"%s %d: num_output_layer_sets %d >= HEVC_MAX_VPS_OP_" )
	ASCII(.ascii	"SETS_PLUS1 %d, num_add_olss %d, num_layer_sets %d\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC204:
	ASCII(.ascii	"vps_num_rep_formats_minus1 > 255.\012\000" )
	.space	1
.LC205:
	ASCII(.ascii	"conf_win_vps_left_offset\000" )
	.space	3
.LC206:
	ASCII(.ascii	"conf_win_vps_right_offset\000" )
	.space	2
.LC207:
	ASCII(.ascii	"conf_win_vps_top_offset\000" )
.LC208:
	ASCII(.ascii	"conf_win_vps_bottom_offset\000" )
	.space	1
.LC209:
	ASCII(.ascii	"bit_depth_vps_luma_minus8(%d) or bit_depth_vps_chro" )
	ASCII(.ascii	"ma_minus8(%d) out of range [0,8]\012\000" )
	.space	3
.LC210:
	ASCII(.ascii	"direct_dep_type_len_minus2\000" )
	.space	1
.LC211:
	ASCII(.ascii	"max_vps_num_reorder_pics\000" )
	.space	3
.LC212:
	ASCII(.ascii	"max_vps_latency_increase_plus1\000" )
	.space	1
.LC213:
	ASCII(.ascii	"max_vps_dec_pic_buffering_minus1\000" )
	.space	3
.LC214:
	ASCII(.ascii	"vps_non_vui_extension_length\000" )
	.space	3
.LC215:
	ASCII(.ascii	"min_spatial_segment_offset_plus1\000" )
	.space	3
.LC216:
	ASCII(.ascii	"min_horizontal_ctu_offset_plus1\000" )
.LC217:
	ASCII(.ascii	"vps_num_add_hrd_params\000" )
	.space	1
.LC218:
	ASCII(.ascii	"vps_num_hrd_params %d out of range [0,%d]\012\000" )
	.space	1
.LC219:
	ASCII(.ascii	"num_sub_layer_hrd_minus1\000" )
	.space	3
.LC220:
	ASCII(.ascii	"hrd %d num_sub_layer_hrd_minus1 %d out of range [0," )
	ASCII(.ascii	"%d]\012\000" )
.LC221:
	ASCII(.ascii	"num_signalled_partitioning_schemes\000" )
	.space	1
.LC222:
	ASCII(.ascii	"OPL %d num_signalled_partitioning_schemes %d out of" )
	ASCII(.ascii	" range [0,%d]\012\000" )
	.space	2
.LC223:
	ASCII(.ascii	"num_partitions_in_scheme_minus1\000" )
.LC224:
	ASCII(.ascii	"num_bsp_schedules_minus1\000" )
	.space	3
.LC225:
	ASCII(.ascii	"OPL %d Partition %d Tid %dnum_bsp_schedules_minus1 " )
	ASCII(.ascii	"%d out of range [0,31]\012\000" )
	.space	1
.LC226:
	ASCII(.ascii	"bsp_sched_idx\000" )
	.space	2
.LC227:
	ASCII(.ascii	"vps_num_rep_formats_minus1\000" )
	.space	1
.LC228:
	ASCII(.ascii	"HEVCC_ParseBspPartitonParameters failed.\012\000" )
	.space	2
.LC229:
	ASCII(.ascii	"vps_base_layer_available_flag(%d) not equal 0x1.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC230:
	ASCII(.ascii	"vps_max_layers_minus1 %d out of range[0,63].\012\000" )
	.space	2
.LC231:
	ASCII(.ascii	"vps_max_sub_layers_minus1=%d\012\000" )
	.space	2
.LC232:
	ASCII(.ascii	"vps_reserved_0xffff_16bits not equal 0xffff.\012\000" )
	.space	2
.LC233:
	ASCII(.ascii	"VPS HEVC_DecPTL error.\012\000" )
.LC234:
	ASCII(.ascii	"vps_max_dec_pic_buffering_minus1[i]\000" )
.LC235:
	ASCII(.ascii	"vps_num_reorder_pics[i]\000" )
.LC236:
	ASCII(.ascii	"vps_max_latency_increase_plus1[i]\000" )
	.space	2
.LC237:
	ASCII(.ascii	"vps_max_layer_id out of range[0,%d].\012\000" )
	.space	2
.LC238:
	ASCII(.ascii	"This is MV_HEVC!\012\000" )
	.space	2
.LC239:
	ASCII(.ascii	"vps_num_layer_sets_minus1\000" )
	.space	2
.LC240:
	ASCII(.ascii	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC241:
	ASCII(.ascii	"vps_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC242:
	ASCII(.ascii	"vps_num_hrd_parameters\000" )
	.space	1
.LC243:
	ASCII(.ascii	"vps_num_hrd_parameters(%d) out of range[0,%d].\012\000" )
.LC244:
	ASCII(.ascii	"hrd_layer_set_idx\000" )
	.space	2
.LC245:
	ASCII(.ascii	"VPS HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC246:
	ASCII(.ascii	"HEVC VPSExtension error.\012\000" )
	.space	2
.LC247:
	ASCII(.ascii	"pVPS->vps_video_parameter_set_id out of range(0,15)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC248:
	ASCII(.ascii	"VPS[%d] decode error0.\012\000" )
.LC249:
	ASCII(.ascii	"VPS[%d] decode error1.\012\000" )
.LC250:
	ASCII(.ascii	"chroma_sample_loc_type_top_field\000" )
	.space	3
.LC251:
	ASCII(.ascii	"chroma_sample_loc_type_bottom_field\000" )
.LC252:
	ASCII(.ascii	"def_disp_win_left_offset\000" )
	.space	3
.LC253:
	ASCII(.ascii	"VUI pSps->chroma_format_idc out of range(0,3).\012\000" )
.LC254:
	ASCII(.ascii	"def_disp_win_right_offset\000" )
	.space	2
.LC255:
	ASCII(.ascii	"def_disp_win_top_offset\000" )
.LC256:
	ASCII(.ascii	"def_disp_win_bottom_offset\000" )
	.space	1
.LC257:
	ASCII(.ascii	"vui_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC258:
	ASCII(.ascii	"VUI HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC259:
	ASCII(.ascii	"min_spatial_segmentation_idc\000" )
	.space	3
.LC260:
	ASCII(.ascii	"VUI min_spatial_segmentation_idc out of range(0,409" )
	ASCII(.ascii	"5).\012\000" )
.LC261:
	ASCII(.ascii	"max_bytes_per_pic_denom\000" )
.LC262:
	ASCII(.ascii	"max_bits_per_min_cu_denom\000" )
	.space	2
.LC263:
	ASCII(.ascii	"log2_max_mv_length_horizontal\000" )
	.space	2
.LC264:
	ASCII(.ascii	"log2_max_mv_length_vertical\000" )
.LC265:
	ASCII(.ascii	"sop_seq_parameter_set_id\000" )
	.space	3
.LC266:
	ASCII(.ascii	"num_entries_in_sop_minus1\000" )
	.space	2
.LC267:
	ASCII(.ascii	"num_entries_in_sop_minus1 out of range(0,1024)\012\000" )
.LC268:
	ASCII(.ascii	"sop_short_term_rps_idx\000" )
	.space	1
.LC269:
	ASCII(.ascii	"sop_poc_delta\000" )
	.space	2
.LC270:
	ASCII(.ascii	"recovery_poc_cnt\000" )
	.space	3
.LC271:
	ASCII(.ascii	"colour_remap_id\000" )
.LC272:
	ASCII(.ascii	"colour_remap_coeffs\000" )
.LC273:
	ASCII(.ascii	"reserved_payload_extension_data\000" )
.LC274:
	ASCII(.ascii	"line:%d Cosume TotalPos(%d > %d)!!!\012\000" )
	.space	3
.LC275:
	ASCII(.ascii	"HEVC_SeiMessage HEVC_Sei_Payload error.\012\000" )
	.space	3
.LC276:
	ASCII(.ascii	"SEI pSEISPS = NULL.\012\000" )
	.space	3
.LC277:
	ASCII(.ascii	"SEI HEVC_SeiMessage error.\012\000" )
.LC278:
	ASCII(.ascii	"SEI BsIsByteAligned error.\012\000" )
.LC279:
	ASCII(.ascii	"SEI rbsp_trailing_bits(%d) not equal 0x80.\012\000" )
.LC280:
	ASCII(.ascii	"nesting_num_ops_minus1\000" )
	.space	1
.LC281:
	ASCII(.ascii	"nesting_num_ops_minus1 out of range(0,%d)\012\000" )
	.space	1
.LC282:
	ASCII(.ascii	"nesting_op_idx\000" )
	.space	1
.LC283:
	ASCII(.ascii	"nesting_num_layers_minus1\000" )
	.space	2
.LC284:
	ASCII(.ascii	"nesting_num_layers_minus1 out of range(0,63)\012\000" )
	.space	2
.LC285:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta\000" )
	.space	2
.LC286:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta out of range(0,ma" )
	ASCII(.ascii	"trixId).\012\000" )
	.space	3
.LC287:
	ASCII(.ascii	"HEVC_DecScalingListData pMatrixAddress NULL.\012\000" )
	.space	2
.LC288:
	ASCII(.ascii	"scaling_list_dc_coef_minus8\000" )
.LC289:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-7,247).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC290:
	ASCII(.ascii	"scaling_list_delta_coef\000" )
.LC291:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-128,127)." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC292:
	ASCII(.ascii	"sps_rep_format_idx %d > HEVC_MAX_NUM_LAYERS %d\012\000" )
.LC293:
	ASCII(.ascii	"HEVC_DeriveSPSRepFormat failed.\012\000" )
	.space	3
.LC294:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range(0,3).\012\000" )
.LC295:
	ASCII(.ascii	"pSPS->chroma_format_idc not equal(%d) 1.\012\000" )
	.space	2
.LC296:
	ASCII(.ascii	"pic_width_in_luma_samples\000" )
	.space	2
.LC297:
	ASCII(.ascii	"pic_width_in_luma_samples out of range(0,8192).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC298:
	ASCII(.ascii	"pic_height_in_luma_samples\000" )
	.space	1
.LC299:
	ASCII(.ascii	"pic_height_in_luma_samples out of range(0,4096).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC300:
	ASCII(.ascii	"ERROR Unkown level: %d\012\000" )
.LC301:
	ASCII(.ascii	"conf_win_left_offset\000" )
	.space	3
.LC302:
	ASCII(.ascii	"conf_win_right_offset\000" )
	.space	2
.LC303:
	ASCII(.ascii	"conf_win_left_offset+conf_win_right_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC304:
	ASCII(.ascii	"conf_win_top_offset\000" )
.LC305:
	ASCII(.ascii	"conf_win_bottom_offset\000" )
	.space	1
.LC306:
	ASCII(.ascii	"conf_win_top_offset+conf_win_bottom_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC307:
	ASCII(.ascii	"bit_depth_luma_minus8\000" )
	.space	2
.LC308:
	ASCII(.ascii	"bit_depth_luma(%d) out of range(8,10).\012\000" )
.LC309:
	ASCII(.ascii	"bit_depth_chroma_minus8\000" )
.LC310:
	ASCII(.ascii	"bit_depth_chroma(%d) out of range[8,14].\012\000" )
	.space	2
.LC311:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	2
.LC312:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12" )
	ASCII(.ascii	"].\012\000" )
	.space	1
.LC313:
	ASCII(.ascii	"sps_max_dec_pic_buffering_minus1\000" )
	.space	3
.LC314:
	ASCII(.ascii	"sps_num_reorder_pics\000" )
	.space	3
.LC315:
	ASCII(.ascii	"sps_max_latency_increase_plus1\000" )
	.space	1
.LC316:
	ASCII(.ascii	"log2_min_coding_block_size_minus3\000" )
	.space	2
.LC317:
	ASCII(.ascii	"log2_min_luma_coding_block_size_minus3 out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC318:
	ASCII(.ascii	"log2_diff_max_min_coding_block_size\000" )
.LC319:
	ASCII(.ascii	"log2_diff_max_min_luma_coding_block_size out of ran" )
	ASCII(.ascii	"ge(0,3).\012\000" )
	.space	3
.LC320:
	ASCII(.ascii	"log2_ctb_sizeY out of range(4,6).\012\000" )
	.space	1
.LC321:
	ASCII(.ascii	"log2_min_transform_block_size_minus2\000" )
	.space	3
.LC322:
	ASCII(.ascii	"log2_min_transform_block_size_minus2 out of range(0" )
	ASCII(.ascii	",3).\012\000" )
	.space	3
.LC323:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size\000" )
	.space	1
.LC324:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC325:
	ASCII(.ascii	"quadtree_tu_log2_min_size not less than log2_min_cb" )
	ASCII(.ascii	"_sizeY.\012\000" )
.LC326:
	ASCII(.ascii	"quadtree_tu_log2_max_size greater than Min( CtbLog2" )
	ASCII(.ascii	"SizeY, 5 ).\012\000" )
.LC327:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter\000" )
.LC328:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC329:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra\000" )
.LC330:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC331:
	ASCII(.ascii	"SPS HEVC_DecScalingListData error.\012\000" )
.LC332:
	ASCII(.ascii	"SPS sao is off and pic height(%d) is too small.(Log" )
	ASCII(.ascii	"ic Unsupported).\012\000" )
	.space	3
.LC333:
	ASCII(.ascii	"log2_min_pcm_luma_coding_block_size_minus3\000" )
	.space	1
.LC334:
	ASCII(.ascii	"log2_min_pcm_coding_block_size_minus3(%d) out of ra" )
	ASCII(.ascii	"nge[0,2].\012\000" )
	.space	2
.LC335:
	ASCII(.ascii	"log2_diff_max_min_pcm_luma_coding_block_size\000" )
	.space	3
.LC336:
	ASCII(.ascii	"log2_diff_max_min_pcm_coding_block_size(%d) out of " )
	ASCII(.ascii	"range[0,2].\012\000" )
.LC337:
	ASCII(.ascii	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5" )
	ASCII(.ascii	" ).\012\000" )
.LC338:
	ASCII(.ascii	"num_short_term_ref_pic_sets\000" )
.LC339:
	ASCII(.ascii	"num_short_term_ref_pic_sets out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC340:
	ASCII(.ascii	"SPS HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	1
.LC341:
	ASCII(.ascii	"num_long_term_ref_pic_sps\000" )
	.space	2
.LC342:
	ASCII(.ascii	"num_long_term_ref_pic_sps out of range[0,32].\012\000" )
	.space	1
.LC343:
	ASCII(.ascii	"SPS HEVC_DecVuiParam error.\012\000" )
	.space	3
.LC344:
	ASCII(.ascii	"chroma_format_idc\000" )
	.space	2
.LC345:
	ASCII(.ascii	"sps_video_parameter_set_id out of range(0,%d).\012\000" )
.LC346:
	ASCII(.ascii	"sps_max_sub_layers_minus1 out of range(0,%d).\012\000" )
	.space	1
.LC347:
	ASCII(.ascii	"SPS HEVC_DecPTL error.\012\000" )
.LC348:
	ASCII(.ascii	"sps_seq_parameter_set_id\000" )
	.space	3
.LC349:
	ASCII(.ascii	"sps_seq_parameter_set_id out of range(0,%d).\012\000" )
	.space	2
.LC350:
	ASCII(.ascii	"SPS[%d] decode error0.\012\000" )
.LC351:
	ASCII(.ascii	"SPS[%d] decode error.\012\000" )
	.space	1
.LC352:
	ASCII(.ascii	"pps_seq_parameter_set_id\000" )
	.space	3
.LC353:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range[0,15].\012\000" )
	.space	2
.LC354:
	ASCII(.ascii	"SPS(%d) haven't decode.\012\000" )
	.space	3
.LC355:
	ASCII(.ascii	"num_ref_idx_l0_default_active_minus1\000" )
	.space	3
.LC356:
	ASCII(.ascii	"num_ref_idx_l0_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC357:
	ASCII(.ascii	"num_ref_idx_l1_default_active_minus1\000" )
	.space	3
.LC358:
	ASCII(.ascii	"num_ref_idx_l1_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC359:
	ASCII(.ascii	"init_qp_minus26\000" )
.LC360:
	ASCII(.ascii	"pic_init_qp(%d) out of range[-%d,51].\012\000" )
	.space	1
.LC361:
	ASCII(.ascii	"diff_cu_qp_delta_depth\000" )
	.space	1
.LC362:
	ASCII(.ascii	"diff_cu_qp_delta_depth out of range[0,3].\012\000" )
	.space	1
.LC363:
	ASCII(.ascii	"pps_cb_qp_offset\000" )
	.space	3
.LC364:
	ASCII(.ascii	"pic_cb_qp_offset out of range[-12,12].\012\000" )
.LC365:
	ASCII(.ascii	"pps_cr_qp_offset\000" )
	.space	3
.LC366:
	ASCII(.ascii	"pic_cr_qp_offset out of range[-12,12].\012\000" )
.LC367:
	ASCII(.ascii	"num_tile_columns_minus1\000" )
.LC368:
	ASCII(.ascii	"num_tile_columns(%d) out of range(0,%d).\012\000" )
	.space	2
.LC369:
	ASCII(.ascii	"num_tile_rows_minus1\000" )
	.space	3
.LC370:
	ASCII(.ascii	"num_tile_rows out(%d) of range(0,%d).\012\000" )
	.space	1
.LC371:
	ASCII(.ascii	"Logic limit(%d), num_tile_columns(%d) exceed.\012\000" )
	.space	1
.LC372:
	ASCII(.ascii	"Logic limit(%d), num_tile_rows(%d) exceed.\012\000" )
.LC373:
	ASCII(.ascii	"column_width_minus1\000" )
.LC374:
	ASCII(.ascii	"column_width[%d](%d) out of range (0 %d)\012\000" )
	.space	2
.LC375:
	ASCII(.ascii	"row_height_minus1\000" )
	.space	2
.LC376:
	ASCII(.ascii	"row_height[%d](%d) out of range (0 %d)\012\000" )
.LC377:
	ASCII(.ascii	"column_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	2
.LC378:
	ASCII(.ascii	"row_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	1
.LC379:
	ASCII(.ascii	"PPS tile width(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC380:
	ASCII(.ascii	"PPS tile height(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
.LC381:
	ASCII(.ascii	"pps_beta_offset_div2\000" )
	.space	3
.LC382:
	ASCII(.ascii	"pps_beta_offset_div2(%d) out of range(-6,6).\012\000" )
	.space	2
.LC383:
	ASCII(.ascii	"pps_tc_offset_div2\000" )
	.space	1
.LC384:
	ASCII(.ascii	"pps_tc_offset_div2(%d) out of range(-6,6).\012\000" )
.LC385:
	ASCII(.ascii	"PPS HEVC_DecScalingListData error.\012\000" )
.LC386:
	ASCII(.ascii	"log2_parallel_merge_level_minus2\000" )
	.space	3
.LC387:
	ASCII(.ascii	"log2_parallel_merge_level(%d) out of range(2,log2_c" )
	ASCII(.ascii	"tb_sizeY).\012\000" )
	.space	1
.LC388:
	ASCII(.ascii	"log2_max_transform_skip_block_size_minus2\000" )
	.space	2
.LC389:
	ASCII(.ascii	"log2_sao_offset_scale_luma\000" )
	.space	1
.LC390:
	ASCII(.ascii	"log2_sao_offset_scale_chroma\000" )
	.space	3
.LC391:
	ASCII(.ascii	"diff_cu_chroma_qp_offset_depth\000" )
	.space	1
.LC392:
	ASCII(.ascii	"chroma_qp_offset_list_len_minus1\000" )
	.space	3
.LC393:
	ASCII(.ascii	"chroma_qp_offset_list_len_minus1 %d > 5\012\000" )
	.space	3
.LC394:
	ASCII(.ascii	"cb_qp_offset_list\000" )
	.space	2
.LC395:
	ASCII(.ascii	"cr_qp_offset_list\000" )
	.space	2
.LC396:
	ASCII(.ascii	"pps_scaling_list_ref_layer_id %d > HEVC_MAX_NUM_LAY" )
	ASCII(.ascii	"ERS %d\012\000" )
	.space	1
.LC397:
	ASCII(.ascii	"num_ref_loc_offsets\000" )
.LC398:
	ASCII(.ascii	"num_ref_loc_offsets %d > HEVC_EXT_MAX_REF_LOC_OFFSE" )
	ASCII(.ascii	"T %d\012\000" )
	.space	3
.LC399:
	ASCII(.ascii	"ref_loc_offset_layer_id %d > HEVC_EXT_MAX_REF_LOC_O" )
	ASCII(.ascii	"FFSET %d\012\000" )
	.space	3
.LC400:
	ASCII(.ascii	"scaled_ref_layer_left_offset\000" )
	.space	3
.LC401:
	ASCII(.ascii	"scaled_ref_layer_top_offset\000" )
.LC402:
	ASCII(.ascii	"scaled_ref_layer_right_offset\000" )
	.space	2
.LC403:
	ASCII(.ascii	"scaled_ref_layer_bottom_offset\000" )
	.space	1
.LC404:
	ASCII(.ascii	"ref_region_left_offset\000" )
	.space	1
.LC405:
	ASCII(.ascii	"ref_region_top_offset\000" )
	.space	2
.LC406:
	ASCII(.ascii	"ref_region_right_offset\000" )
.LC407:
	ASCII(.ascii	"ref_region_bottom_offset\000" )
	.space	3
.LC408:
	ASCII(.ascii	"phase_hor_luma\000" )
	.space	1
.LC409:
	ASCII(.ascii	"phase_ver_luma\000" )
	.space	1
.LC410:
	ASCII(.ascii	"phase_hor_chroma_plus8\000" )
	.space	1
.LC411:
	ASCII(.ascii	"phase_ver_chroma_plus8\000" )
	.space	1
.LC412:
	ASCII(.ascii	"HEVC_ParsePPSExtension failed.\012\000" )
.LC413:
	ASCII(.ascii	"pps_pic_parameter_set_id\000" )
	.space	3
.LC414:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range(0,%d).\012\000" )
	.space	2
.LC415:
	ASCII(.ascii	"PPS[%d] decode error.\012\000" )
	.space	1
.LC416:
	ASCII(.ascii	"luma_log2_weight_denom\000" )
	.space	1
.LC417:
	ASCII(.ascii	"luma_log2_weight_denom out of range(0,7).\012\000" )
	.space	1
.LC418:
	ASCII(.ascii	"delta_chroma_log2_weight_denom\000" )
	.space	1
.LC419:
	ASCII(.ascii	"delta_chroma_log2_weight_denom out of range(-7,7).\012" )
	ASCII(.ascii	"\000" )
.LC420:
	ASCII(.ascii	"chroma_log2_weight_denom out of range(0,7).\012\000" )
	.space	3
.LC421:
	ASCII(.ascii	"delta_luma_weight_l0\000" )
	.space	3
.LC422:
	ASCII(.ascii	"delta_luma_weight_l0(%d) out of range(-128,127).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC423:
	ASCII(.ascii	"luma_offset_l0\000" )
	.space	1
.LC424:
	ASCII(.ascii	"luma_offset_l0(%d) out of range(-128,127).\012\000" )
.LC425:
	ASCII(.ascii	"delta_chroma_weight_l0\000" )
	.space	1
.LC426:
	ASCII(.ascii	"delta_chroma_weight_l0 out of range(-128,127).\012\000" )
.LC427:
	ASCII(.ascii	"delta_chroma_offset_l0\000" )
	.space	1
.LC428:
	ASCII(.ascii	"delta_chroma_offset_l0 out of range(-512,511).\012\000" )
.LC429:
	ASCII(.ascii	"delta_luma_weight_l1\000" )
	.space	3
.LC430:
	ASCII(.ascii	"delta_luma_weight_l1 out of range(-128,127).\012\000" )
	.space	2
.LC431:
	ASCII(.ascii	"luma_offset_l1\000" )
	.space	1
.LC432:
	ASCII(.ascii	"luma_offset_l1 out of range(-128,127).\012\000" )
.LC433:
	ASCII(.ascii	"delta_chroma_weight_l1\000" )
	.space	1
.LC434:
	ASCII(.ascii	"delta_chroma_weight_l1 out of range(-128,127).\012\000" )
.LC435:
	ASCII(.ascii	"delta_chroma_offset_l1\000" )
	.space	1
.LC436:
	ASCII(.ascii	"delta_chroma_offset_l1 out of range(-512,511).\012\000" )
.LC437:
	ASCII(.ascii	"slice_pic_parameter_set_id\000" )
	.space	1
.LC438:
	ASCII(.ascii	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC439:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\012\000" )
.LC440:
	ASCII(.ascii	"max_cu_width(%d)/max_cu_height(%d) = 0\012\000" )
.LC441:
	ASCII(.ascii	"slice_segment_address(%d) out of range(0,%d).\012\000" )
	.space	1
.LC442:
	ASCII(.ascii	"slice_type\000" )
	.space	1
.LC443:
	ASCII(.ascii	"slice_type(%d) out of range(0,2].\012\000" )
	.space	1
.LC444:
	ASCII(.ascii	"HEVC_ClearDPB,LastDisplayPoc:%d poc:%d \012\000" )
	.space	3
.LC445:
	ASCII(.ascii	"SH HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	2
.LC446:
	ASCII(.ascii	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
.LC447:
	ASCII(.ascii	"num_long_term_sps\000" )
	.space	2
.LC448:
	ASCII(.ascii	"num_long_term_sps(%d) out of range[0,%d].\012\000" )
	.space	1
.LC449:
	ASCII(.ascii	"num_long_term_pics\000" )
	.space	1
.LC450:
	ASCII(.ascii	"SH ERROR: (num_negative_pics(%d) + num_positive_pic" )
	ASCII(.ascii	"s(%d) + num_of_longterm_pics(%d)) > %d\012\000" )
	.space	1
.LC451:
	ASCII(.ascii	"lt_idx_sps[%d] = %d, but out of range[0,%d].\012\000" )
	.space	2
.LC452:
	ASCII(.ascii	"delta_poc_msb_cycle_lt\000" )
	.space	1
.LC453:
	ASCII(.ascii	"ERROR: pRPS->num_of_pics(%d) > %d.\012\000" )
.LC454:
	ASCII(.ascii	"Error0: Parse num_active_ref_layer_pics %d > HEVC_M" )
	ASCII(.ascii	"AX_NUM_LAYERS %d, not support\012\000" )
	.space	2
.LC455:
	ASCII(.ascii	"Error1: Parse num_active_ref_layer_pics %d > HEVC_M" )
	ASCII(.ascii	"AX_NUM_LAYERS %d, not support\012\000" )
	.space	2
.LC456:
	ASCII(.ascii	"Parse inter_layer_pred_layer_idc[%d] %d > HEVC_MAX_" )
	ASCII(.ascii	"NUM_LAYERS %d, not support\000" )
	.space	2
.LC457:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC458:
	ASCII(.ascii	"num_ref_idx_l0_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC459:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC460:
	ASCII(.ascii	"num_ref_idx_l1_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC461:
	ASCII(.ascii	"pRPS is null.\012\000" )
	.space	1
.LC462:
	ASCII(.ascii	"pRPS->num_of_pics out(%d) of range(0,%d).\012\000" )
	.space	1
.LC463:
	ASCII(.ascii	"SH HEVC_DecRefPicListsModification error.\012\000" )
	.space	1
.LC464:
	ASCII(.ascii	"collocated_ref_idx\000" )
	.space	1
.LC465:
	ASCII(.ascii	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) " )
	ASCII(.ascii	"out of range(0,%d).\012\000" )
.LC466:
	ASCII(.ascii	"SH HEVC_DecPredWeightTable error.\012\000" )
	.space	1
.LC467:
	ASCII(.ascii	"five_minus_max_num_merge_cand\000" )
	.space	2
.LC468:
	ASCII(.ascii	"SH max_num_merge_cand(%d) out of range(1,5).\012\000" )
	.space	2
.LC469:
	ASCII(.ascii	"slice_qp_delta\000" )
	.space	1
.LC470:
	ASCII(.ascii	"SH slice_qp(%d) out of range [-%d,51].\012\000" )
.LC471:
	ASCII(.ascii	"slice_cb_qp_offset\000" )
	.space	1
.LC472:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC473:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out " )
	ASCII(.ascii	"of range[-12,12].\012\000" )
	.space	2
.LC474:
	ASCII(.ascii	"slice_cr_qp_offset\000" )
	.space	1
.LC475:
	ASCII(.ascii	"SH slice_cr_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC476:
	ASCII(.ascii	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) ou" )
	ASCII(.ascii	"t of range[-12,12].\012\000" )
.LC477:
	ASCII(.ascii	"slice_beta_offset_div2\000" )
	.space	1
.LC478:
	ASCII(.ascii	"SH slice_beta_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC479:
	ASCII(.ascii	"slice_tc_offset_div2\000" )
	.space	3
.LC480:
	ASCII(.ascii	"SH slice_tc_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC481:
	ASCII(.ascii	"num_entry_point_offsets\000" )
.LC482:
	ASCII(.ascii	"CurrSlice.num_entry_point_offsets(%d) out of range[" )
	ASCII(.ascii	"0,%d].\012\000" )
	.space	1
.LC483:
	ASCII(.ascii	"offset_len_minus1\000" )
	.space	2
.LC484:
	ASCII(.ascii	"CurrSlice.offset_len(%d) out of range[1,32].\012\000" )
	.space	2
.LC485:
	ASCII(.ascii	"slice_segment_header_extension_length\000" )
	.space	2
.LC486:
	ASCII(.ascii	"slice_segment_header_extension_length(%d) out of ra" )
	ASCII(.ascii	"nge [0,256]\012\000" )
.LC487:
	ASCII(.ascii	"bitsLeft(%d) < slice_segment_header_extension_lengt" )
	ASCII(.ascii	"h(%d)\012\000" )
	.space	2
.LC488:
	ASCII(.ascii	"HEVC_ParseSliceExtension failed\012\000" )
	.space	3
.LC489:
	ASCII(.ascii	"%s layer num %d invalid!\012\000" )
	.space	2
.LC490:
	ASCII(.ascii	"%s layer %d image size abnormal(%dx%d)\012\000" )
.LC491:
	ASCII(.ascii	"%s arrange mem failed.\012\000" )
.LC492:
	ASCII(.ascii	"Init dec para\012\000" )
	.space	1
.LC493:
	ASCII(.ascii	"Is SHVC: layer%d %dx%d, layer%d %dx%d.\012\000" )
.LC494:
	ASCII(.ascii	"Layer %d: %d x %d\012\000" )
	.space	1
.LC495:
	ASCII(.ascii	"HEVC_InitDPB error, return %d\012\000" )
	.space	1
.LC496:
	ASCII(.ascii	"HEVC_AllocFrameStore error\012\000" )
.LC497:
	ASCII(.ascii	"%s: HEVC_OutputFrame failed!\012\000" )
	.space	2
.LC498:
	ASCII(.ascii	"%s output current picture failed\012\000" )
	.space	2
.LC499:
	ASCII(.ascii	"HEVC.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC500:
	ASCII(.ascii	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\012\000" )
.LC501:
	ASCII(.ascii	"%s call HEVC_GetUnRefPicWithMinPoc failed\012\000" )
	.space	1
.LC502:
	ASCII(.ascii	"%s call HEVC_OutputOneFrmFromDPB failed\012\000" )
	.space	3
.LC503:
	ASCII(.ascii	"%s: HEVC_OutputFrmToVO err!\012\000" )
	.space	3
.LC504:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC505:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC506:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC507:
	ASCII(.ascii	"%s: flush dpb failed, return %d\012\000" )
	.space	3
.LC508:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), need to incr" )
	ASCII(.ascii	"ease DPB size.\012\000" )
	.space	1
.LC509:
	ASCII(.ascii	"%s call HEVC_IncreaseDPBSize failed\012\000" )
	.space	3
.LC510:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpo" )
	ASCII(.ascii	"c frame.\012\000" )
	.space	3
.LC511:
	ASCII(.ascii	"%s with invalid pos(%d)\012\000" )
	.space	3
.LC512:
	ASCII(.ascii	"%s get APC error, ret %d\012\000" )
	.space	2
.LC513:
	ASCII(.ascii	"%s %d: InsertFrmInDPB failed, return %d\012\000" )
	.space	3
.LC514:
	ASCII(.ascii	"%s call HEVC_CheckFrameStore failed!\012\000" )
	.space	2
.LC515:
	ASCII(.ascii	"%s call HEVC_RemoveUnUsedFrameStore Failed.\012\000" )
	.space	3
.LC516:
	ASCII(.ascii	"%s call HEVC_InsertFrmInDPB Failed.\012\000" )
	.space	3
.LC517:
	ASCII(.ascii	"%s call HEVC_FirstFrameFastOut Failed\012\000" )
	.space	1
.LC518:
	ASCII(.ascii	"DPB.used_size may bigger than DPB.size\012\000" )
.LC519:
	ASCII(.ascii	"HEVC_InsertFrmInDPB Failed, ret = %d\012\000" )
	.space	2
.LC520:
	ASCII(.ascii	"%s call HEVC_OutputFrmFromDPB failed\012\000" )
	.space	2
.LC521:
	ASCII(.ascii	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_" )
	ASCII(.ascii	"NORMAL\012\000" )
	.space	1
.LC522:
	ASCII(.ascii	"%s, REPORT_IFRAME_ERR\012\000" )
	.space	1
.LC523:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC524:
	ASCII(.ascii	"%s call HEVC_IModeProcess Failed\012\000" )
	.space	2
.LC525:
	ASCII(.ascii	"HEVC_StorePicInDpb return(%d) from L%d\012\000" )
.LC526:
	ASCII(.ascii	"%s call HEVC_SimpleDPBProcess Failed\012\000" )
	.space	2
.LC527:
	ASCII(.ascii	"%s call HEVC_DecOrderProcess Failed\012\000" )
	.space	3
.LC528:
	ASCII(.ascii	"%s call HEVC_DispOrderProcess Failed\012\000" )
	.space	2
.LC529:
	ASCII(.ascii	"%s return HEVC_DEC_ERR\012\000" )
.LC530:
	ASCII(.ascii	"No frame store for lost pic.\012\000" )
	.space	2
.LC531:
	ASCII(.ascii	"DPB ERROR: Can not get ref_fs!\012\000" )
.LC532:
	ASCII(.ascii	"DPB no suited fs for lost pic.\012\000" )
.LC533:
	ASCII(.ascii	"Take poc(%d) to creat lost poc(%d).\012\000" )
	.space	3
.LC534:
	ASCII(.ascii	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\012\000" )
	.space	1
.LC535:
	ASCII(.ascii	"ERROR: Can not new logic fs!\012\000" )
	.space	2
.LC536:
	ASCII(.ascii	"Lost pic insert in DPB Failed!\012\000" )
.LC537:
	ASCII(.ascii	"Ref frame(poc %d) lost.\012\000" )
	.space	3
.LC538:
	ASCII(.ascii	"s32OutErrThr = %d,drop poc %d because lost ref fram" )
	ASCII(.ascii	"e(pod %d)\012\000" )
	.space	2
.LC539:
	ASCII(.ascii	"DecVDM MaxBytesReceived exceed threshold!\012\000" )
	.space	1
.LC540:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM\012\000" )
	.space	1
.LC541:
	ASCII(.ascii	"IPBDecMode Changed (%d -> %d)\012\000" )
	.space	1
.LC542:
	ASCII(.ascii	"Discard this B(poc=%d) before P, is_ref_idc=%d.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC543:
	ASCII(.ascii	"VDM start, TotalPicNum=%d.\012\000" )
.LC544:
	ASCII(.ascii	"%s no correct slice in the pic\012\000" )
.LC545:
	ASCII(.ascii	"metadatasize is too large:%d at line:%d\012\000" )
	.space	3
.LC546:
	ASCII(.ascii	"%s:%d Metadata map failed\012\000" )
	.space	1
.LC547:
	ASCII(.ascii	"%s:%d Metadata unmap failed\012\000" )
	.space	3
.LC548:
	ASCII(.ascii	"*****[%s][%d],BL Codec can only dec BL stream!!****" )
	ASCII(.ascii	"*\012\000" )
	.space	2
.LC549:
	ASCII(.ascii	"*****[%s][%d],EL Codec can only dec EL stream in DV" )
	ASCII(.ascii	"_DUAL_VES_IMP stream!!*****\012\000" )
.LC550:
	ASCII(.ascii	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC551:
	ASCII(.ascii	"%s call HEVC_FlushOutputFrmFromDPB failed\012\000" )
	.space	1
.LC552:
	ASCII(.ascii	"%s call HEVC_EmptyFrmFromDPB failed\012\000" )
	.space	3
.LC553:
	ASCII(.ascii	"Meet CRA frame, force output remain frame, CurPoc %" )
	ASCII(.ascii	"d, LastPoc %d\012\000" )
	.space	2
.LC554:
	ASCII(.ascii	"Init pic err, exit\012\000" )
.LC555:
	ASCII(.ascii	"HEVC_WritePicMsg failed!\012\000" )
	.space	2
.LC556:
	ASCII(.ascii	"Start Reason: SliceParaNum= %d\012\000" )
.LC557:
	ASCII(.ascii	"Too many slice , err!\012\000" )
	.space	1
.LC558:
	ASCII(.ascii	"Cur pic not init yet, discard this slice!\012\000" )
	.space	1
.LC559:
	ASCII(.ascii	"Dec List error, ret=%d\012\000" )
.LC560:
	ASCII(.ascii	"Ref List is Wrong!\012\000" )
.LC561:
	ASCII(.ascii	"HEVC_WriteSliceMsg err.\012\000" )
	.space	3
.LC562:
	ASCII(.ascii	"VPS decode error.\012\000" )
	.space	1
.LC563:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC564:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC565:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC566:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC567:
	ASCII(.ascii	"HEVC_DecSliceSegmentHeader dec err\012\000" )
.LC568:
	ASCII(.ascii	"CurBitsLen = %d, MinBitsLen = %d\012\000" )
	.space	2
.LC569:
	ASCII(.ascii	"%s last frame fs unrelease, fix it!\012\000" )
	.space	3
.LC570:
	ASCII(.ascii	"CtbNumOneFrame=%d, SedEnd0=%d\012\000" )
	.space	1
.LC571:
	ASCII(.ascii	"%s: Get context addr failed!\012\000" )
	.space	2
.LC572:
	ASCII(.ascii	"%s FATAL: MemOffset %d > ContextMemSize %d.\012\000" )
	.space	3
.LC573:
	ASCII(.ascii	"%s: VCTRL_GetChanIDByCtx() return -1!\012\000" )
	.space	1
.LC574:
	ASCII(.ascii	"Fs leak, clear dpb fs not in vo queue.\012\000" )
.LC575:
	ASCII(.ascii	"No frame store available!\012\000" )
	.space	1
.LC576:
	ASCII(.ascii	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak" )
	ASCII(.ascii	", ClearAll!\012\000" )
.LC577:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pPacket!\012\000" )
	.space	1
.LC578:
	ASCII(.ascii	"HevcCtx not init!\012\000" )
	.space	1
.LC579:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC580:
	ASCII(.ascii	"nal_layer_id out %d of range[0,1].\012\000" )
.LC581:
	ASCII(.ascii	"Not need nal of layer %d in output order %d.\012\000" )
	.space	2
.LC582:
	ASCII(.ascii	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\012" )
	ASCII(.ascii	"\000" )
.LC583:
	ASCII(.ascii	"HEVC_InquireSliceProperty error.\012\000" )
	.space	2
.LC584:
	ASCII(.ascii	"HEVC_DecOneNal ERR\012\000" )
.LC585:
	ASCII(.ascii	"HEVC_StorePicInDPB failed, ret = %d\012\000" )
	.space	3
.LC586:
	ASCII(.ascii	"pHevcCtx->CurrPic.frame_store is null pointer\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
.LANCHOR2 = . + 458304
.LANCHOR3 = . + 605616
.LANCHOR5 = . + 646536
	.type	g_SigLastScan, %object
	.size	g_SigLastScan, 458752
g_SigLastScan:
	.space	458752
	.type	g_TsToRsMap, %object
	.size	g_TsToRsMap, 147456
g_TsToRsMap:
	.space	147456
	.type	g_IsDeced, %object
	.size	g_IsDeced, 36864
g_IsDeced:
	.space	36864
	.type	s_TmpParam, %object
	.size	s_TmpParam, 24912
s_TmpParam:
	.space	24912
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
