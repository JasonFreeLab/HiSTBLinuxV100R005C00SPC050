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
	.global	__aeabi_idivmod
	.align	2
	.type	HEVC_CheckThatAllRefPicsAreAvailable.part.8, %function
HEVC_CheckThatAllRefPicsAreAvailable.part.8:
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
	ldr	ip, [r0, #2368]
	mov	r6, #1888
	ldr	r2, [r3, #140]
	movw	r4, #12660
	ldr	r5, [r3, #1040]
	mov	r7, r0
	str	r1, [fp, #-84]
	mla	ip, r6, r2, ip
	ldr	r1, [r3, #1036]
	ldr	lr, [r0, #2364]
	add	r1, r5, r1
	ldr	r2, [r3, #1044]
	str	r1, [fp, #-80]
	mov	r5, r1
	cmp	r1, r2
	ldr	ip, [ip, #32]
	str	r0, [fp, #-60]
	mov	r0, #1
	mla	r1, r4, ip, lr
	ldr	r10, [r1, #116]
	mov	r10, r0, asl r10
	bcs	.L6
	add	r9, r5, #1296
	ldr	r6, [r7, #2588]
	add	r9, r9, #12
	mov	r0, #0
	add	r2, r2, #5120
	add	r1, r5, #5120
	add	r9, r7, r9, lsl #2
	mov	ip, r0
	add	r2, r2, #24
	add	r1, r1, #24
	str	r0, [fp, #-64]
	mov	r0, r7
	add	r2, r7, r2
	str	ip, [fp, #-72]
	str	r2, [fp, #-68]
	add	r2, r7, r1
	str	r3, [fp, #-76]
	str	r2, [fp, #-56]
.L7:
	cmp	r6, #0
	beq	.L13
	ldr	r3, [fp, #-60]
	mov	r2, #0
	ldr	r8, [r9, #-944]
	mov	r5, r2
	add	r4, r3, #2608
	str	r2, [fp, #-52]
	b	.L10
.L50:
	ldr	r3, [r4]
	ldr	r1, [r3, #60]
	cmp	r1, #0
	beq	.L9
	ldr	r0, [r3, #8]
	ldr	r1, [r9]
	cmp	r0, r1
	ldreqb	r3, [r3, #1]	@ zero_extendqisi2
	beq	.L48
.L9:
	add	r5, r5, #1
	add	r4, r4, #4
	cmp	r5, r6
	beq	.L49
.L10:
	cmp	r8, #0
	bne	.L50
	ldr	r7, [r4]
	mov	r1, r10
	ldr	r3, [r7, #60]
	cmp	r3, #0
	beq	.L9
	ldr	r0, [r7, #8]
	bl	__aeabi_idivmod
	ldr	r0, [r9]
	str	r1, [fp, #-48]
	mov	r1, r10
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-48]
	cmp	r3, r1
	bne	.L9
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
.L48:
	cmp	r3, #0
	add	r5, r5, #1
	ldr	r3, [fp, #-52]
	add	r4, r4, #4
	movne	r3, #1
	cmp	r5, r6
	str	r3, [fp, #-52]
	bne	.L10
.L49:
	ldr	r2, [fp, #-52]
	cmp	r2, #0
	beq	.L13
.L11:
	ldr	r3, [fp, #-56]
	add	r9, r9, #4
	ldr	r2, [fp, #-68]
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r3, r2
	bne	.L7
	ldr	r2, [fp, #-80]
	ldr	r3, [fp, #-76]
	cmp	r2, #0
	beq	.L15
.L14:
	ldr	r2, [fp, #-60]
	mov	r7, #0
	ldr	r10, [fp, #-80]
	add	r4, r2, #5120
	ldr	r0, [fp, #-72]
	mov	r9, r2
	mov	r8, r4
	add	r4, r4, #44
	add	r8, r8, #24
.L19:
	cmp	r6, #0
	beq	.L20
	add	lr, r9, #2592
	mov	r5, #0
	add	lr, lr, #12
	mov	r2, r5
	str	r0, [fp, #-48]
	b	.L17
.L16:
	cmp	r2, r6
	beq	.L51
.L17:
	ldr	r1, [lr, #4]!
	add	r2, r2, #1
	ldr	ip, [r1, #60]
	cmp	ip, #0
	bne	.L16
	ldr	r0, [r4]
	ldr	ip, [r3, #116]
	add	ip, ip, r0
	ldr	r0, [r1, #8]
	cmp	r0, ip
	bne	.L16
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	cmp	r1, #0
	movne	r5, #1
	cmp	r2, r6
	bne	.L17
.L51:
	cmp	r5, #0
	ldr	r0, [fp, #-48]
	beq	.L20
.L18:
	add	r7, r7, #1
	add	r4, r4, #4
	cmp	r10, r7
	add	r8, r8, #1
	bhi	.L19
	str	r0, [fp, #-72]
.L15:
	ldr	r3, [fp, #-72]
	cmp	r3, #0
	ldrne	r3, [fp, #-84]
	movne	r0, #0
	ldrne	r2, [fp, #-64]
	moveq	r0, #1
	strne	r2, [r3]
.L47:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	ldr	r1, [r3, #136]
	ldr	r2, [r3, #116]
	ldr	ip, [r4]
	add	r1, r9, r1, lsl #2
	add	r2, r2, ip
	ldr	r1, [r1, #228]
	cmp	r2, r1
	blt	.L18
	ldrb	r1, [r8]	@ zero_extendqisi2
	cmp	r1, #0
	ldr	r1, [fp, #-64]
	movne	r0, #1
	movne	r1, r2
	str	r1, [fp, #-64]
	b	.L18
.L13:
	ldr	r3, [fp, #-76]
	ldr	r0, [r9, #-68]
	ldr	r1, [r3, #136]
	ldr	r2, [r3, #116]
	ldr	r3, [fp, #-60]
	add	r2, r2, r0
	add	r1, r3, r1, lsl #2
	ldr	r1, [r1, #228]
	cmp	r2, r1
	blt	.L11
	ldr	r3, [fp, #-56]
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldr	r3, [fp, #-64]
	cmp	r1, #0
	movne	r3, r2
	str	r3, [fp, #-64]
	ldr	r3, [fp, #-72]
	movne	r3, #1
	str	r3, [fp, #-72]
	b	.L11
.L6:
	ldr	r2, [fp, #-80]
	cmp	r2, #0
	beq	.L47
	ldr	r1, [fp, #-60]
	mov	r2, #0
	str	r2, [fp, #-64]
	str	r2, [fp, #-72]
	ldr	r6, [r1, #2588]
	b	.L14
	UNWIND(.fnend)
	.size	HEVC_CheckThatAllRefPicsAreAvailable.part.8, .-HEVC_CheckThatAllRefPicsAreAvailable.part.8
	.align	2
	.type	HEVC_SetFrmRepeatCount.part.9, %function
HEVC_SetFrmRepeatCount.part.9:
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
	ldr	ip, [r0, #284]
	ldr	r2, [r0, #2584]
	ldr	r3, [r0, #280]
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
	ldrhi	r3, [r0, #284]
	ldrls	r3, [r0, #284]
	addhi	r3, r3, #2
	addls	r3, r3, #1
	str	r3, [r0, #284]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_SetFrmRepeatCount.part.9, .-HEVC_SetFrmRepeatCount.part.9
	.align	2
	.type	HEVC_OutputFrame.isra.10, %function
HEVC_OutputFrame.isra.10:
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
	UNWIND(.pad #12)
	sub	sp, sp, #12
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #252]
	ldr	r1, [r1]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L62
	mov	r2, #1
	ldr	r1, [r5]
	ldr	r0, [r4, #252]
	bl	FSP_SetDisplay
	add	r3, r4, #5504
	ldr	r0, [r4, #252]
	add	r3, r3, #56
	str	r6, [sp]
	mov	r2, r4
	mov	r1, #16
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L63
	ldr	r3, [r4, #2404]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r6, #16]
	bcs	.L64
.L61:
	ldr	r2, [r4, #292]
	mov	r0, #0
	ldr	r3, [r4, #284]
	add	r2, r2, #1
	str	r2, [r4, #292]
	add	r3, r3, #1
	str	r3, [r4, #284]
.L58:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L64:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SetFrmRepeatCount.part.9
	b	.L61
.L63:
	ldr	r2, .L65
	mov	r0, #1
	ldr	r1, .L65+4
	bl	dprint_vfmw
	ldr	r0, [r4, #252]
	ldr	r1, [r5]
	mov	r2, #0
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L58
.L62:
	ldr	r2, .L65
	ldr	r1, .L65+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L58
.L66:
	.align	2
.L65:
	.word	.LANCHOR0
	.word	.LC3
	.word	.LC2
	UNWIND(.fnend)
	.size	HEVC_OutputFrame.isra.10, .-HEVC_OutputFrame.isra.10
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
	ldr	r3, .L68
	mov	r6, r0
	add	r0, r0, #11072
	mov	r2, #56
	add	r0, r0, #32
	mov	r1, #0
	ldr	r3, [r3, #48]
	mov	r4, #0
	blx	r3
	add	r3, r6, #2896
	mov	r5, #0
	mov	r2, #0
	strd	r4, [r3, #32]
	strd	r4, [r3, #8]
	strd	r4, [r3, #16]
	strd	r4, [r3, #24]
	str	r2, [r6, #2884]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L69:
	.align	2
.L68:
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
	ldr	r5, [r0, #2368]
	mov	r6, #1888
	ldr	r1, [r0, #2364]
	ldr	ip, [r3, #140]
	movw	r4, #12660
	ldr	lr, [r2, #36]
	add	r3, r0, #8192
	mla	ip, r6, ip, r5
	ldr	r5, [r3, #2916]
	cmp	r5, #1
	ldr	ip, [ip, #32]
	str	lr, [r3, #2924]
	ldr	lr, [r2, #40]
	mla	r1, r4, ip, r1
	str	lr, [r3, #2928]
	ldr	ip, [r1, #52]
	add	ip, ip, #90
	ldrb	ip, [r1, ip, asl #2]	@ zero_extendqisi2
	beq	.L78
	ldrb	r1, [r3, #2913]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L79
	add	r1, r0, #2896
	ldr	lr, [r0, #2896]
	ldrd	r4, [r1, #8]
	adds	r4, r4, lr
	adc	r5, r5, #0
	strd	r4, [r1, #32]
.L72:
	add	lr, r3, #2912
	strd	r4, [r1, #24]
	mov	r1, #0
	strb	r1, [r3, #2913]
	ldrd	r6, [lr, #32]
	strd	r6, [lr, #48]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	cmp	r3, r1
	ldr	r3, [r0, #2900]
	bne	.L80
	adds	r4, r4, r3
	adc	r5, r5, #0
	subs	r4, r4, ip
	sbc	r5, r5, #0
	strd	r4, [lr, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L79:
	ldrb	r1, [r0, #2880]	@ zero_extendqisi2
	cmp	r1, #0
	add	r1, r0, #2896
	bne	.L81
	ldrd	r4, [r1, #8]
	ldrd	r8, [r1, #16]
.L75:
	ldr	r6, [r0, #2896]
	mov	r7, #0
	adds	r4, r4, r6
	adc	r5, r5, r7
	cmp	r4, r8
	sbcs	lr, r5, r9
	strd	r4, [r1, #32]
	strd	r4, [r1, #8]
	bge	.L72
	adds	r4, r6, r8
	adc	r5, r7, r9
	strd	r4, [r1, #32]
	strd	r4, [r1, #8]
	b	.L72
.L80:
	adds	r4, r4, r3
	adc	r5, r5, #0
	movs	r5, r5, asr #1
	mov	r4, r4, rrx
	subs	r4, r4, ip
	sbc	r5, r5, #0
	strd	r4, [lr, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L78:
	ldr	r4, [r0, #2884]
	add	r1, r0, #2896
	mov	r5, r4, asr #31
	strd	r4, [r1, #32]
	strd	r4, [r1, #8]
	b	.L72
.L81:
	ldrd	r4, [r1, #16]
	mov	r8, r4
	mov	r9, r5
	b	.L75
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	sub	r3, r1, #19
	cmp	r3, #1
	bls	.L86
.L83:
	sub	r1, r1, #6
	cmp	r1, #3
	addhi	r0, r0, #2896
	ldrhid	r2, [r0, #32]
	strhid	r2, [r0, #16]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L86:
	ldr	ip, [r0, #2404]
	mvn	r3, #0
	mvn	r2, #0
	ldrd	r4, [ip, #56]
	cmp	r5, r3
	cmpeq	r4, r2
	addne	r3, r0, #11136
	ldrned	r6, [r3]
	strned	r4, [r3, #-8]
	strned	r6, [r3, #8]
.L84:
	add	r3, r0, #8192
	mov	r2, #1
	strb	r2, [r3, #2912]
	b	.L83
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
	add	r1, r0, #8192
	add	r3, r0, #11136
	mov	r4, r0
	ldr	r5, [r1, #2924]
	ldr	r10, [r1, #2928]
	mov	r2, r3
	ldrd	r0, [r3, #8]
	cmp	r5, #0
	ldrd	r6, [r2]
	strd	r0, [fp, #-60]
	ldrd	r0, [r2, #-8]
	strd	r0, [fp, #-52]
	beq	.L90
	mov	r9, r5
	mov	r0, r10
	b	.L89
.L91:
	mov	r9, r1
.L89:
	mov	r1, r9
	bl	__aeabi_uidivmod
	mov	r0, r9
	cmp	r1, #0
	bne	.L91
.L88:
	ldrd	r2, [fp, #-60]
	mov	r1, r9
	mov	r0, r5
	mov	r8, #1000
	subs	r2, r6, r2
	add	r4, r4, #4160
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
	strd	r0, [r4, #-8]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L90:
	mov	r9, r10
	b	.L88
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
	bgt	.L93
	cmp	r4, #8
	mul	r9, r4, r4
	beq	.L126
	cmp	r9, #0
	movne	r10, r6
	beq	.L93
.L95:
	mov	r5, #0
	rsb	r7, r4, #1
	mov	r8, r5
.L101:
	cmp	r4, r8
	bgt	.L113
	rsb	lr, r4, r8
	sub	r2, r4, #1
	add	lr, lr, #1
.L102:
	cmp	r2, #0
	cmpge	r4, lr
	ble	.L99
	mla	r0, r2, r4, lr
	add	ip, r10, r5, lsl #2
	mov	r1, r5
.L100:
	add	r1, r1, #1
	sub	r2, r2, #1
	rsb	r3, r5, r1
	str	r0, [ip], #4
	add	r3, r3, lr
	add	r0, r0, r7
	cmp	r2, #0
	cmpge	r4, r3
	bgt	.L100
	mov	r5, r1
.L99:
	cmp	r9, r5
	add	r8, r8, #1
	bhi	.L101
.L93:
	cmp	r4, #4
	ble	.L92
	mov	r3, r4, asr #2
	ldr	r1, [fp, #-48]
	str	r3, [fp, #-64]
	mov	r2, r3
	add	r3, r1, r3
	mul	r2, r2, r2
	mov	r0, r2
	str	r2, [fp, #-60]
	cmp	r0, #0
	ldrsb	r2, [r3, #12]
	add	r2, r2, #1
	beq	.L92
	add	r3, r1, #340
.L97:
	ldr	r1, .L127
	rsb	r7, r4, #1
	str	r3, [fp, #-52]
	mov	r3, #0
	add	r2, r1, r2, lsl #16
	str	r3, [fp, #-48]
	sub	r3, r2, #4
	str	r3, [fp, #-56]
.L111:
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
.L105:
	cmp	lr, #3
	mvn	r1, r2
	mov	r1, r1, lsr #31
	movgt	r1, #0
	cmp	r1, #0
	beq	.L106
	mla	r1, r2, r4, lr
	add	r0, r3, r10
	rsb	lr, r3, lr
	add	r0, r6, r0, lsl #2
	add	r1, r1, r9
.L107:
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
	bne	.L107
.L106:
	cmp	r3, #15
	add	r8, r8, #1
	bhi	.L108
	cmp	r8, #3
	movle	r2, r8
	movle	lr, #0
	subgt	lr, r8, #3
	movgt	r2, #3
	b	.L105
.L108:
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	add	r2, r2, #4
	str	r2, [fp, #-52]
	ldr	r2, [fp, #-60]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, r2
	bne	.L111
.L92:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L113:
	mov	r2, r8
	mov	lr, #0
	b	.L102
.L126:
	add	r3, r0, #340
	cmp	r9, #0
	mov	r10, r3
	bne	.L95
	ldr	r2, [fp, #-48]
	mov	r1, #2
	str	r1, [fp, #-64]
	mov	r1, #4
	str	r1, [fp, #-60]
	ldrsb	r2, [r2, #14]
	add	r2, r2, #1
	b	.L97
.L128:
	.align	2
.L127:
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
	add	r3, r0, #11
	add	r1, r0, #140
	mov	r7, r0
	mvn	r2, #0
.L130:
	strb	r2, [r3, #1]!
	cmp	r3, r1
	bne	.L130
	ldr	r6, .L134
	mov	r2, #0
	mov	r3, #2
	mov	r5, r2
	mov	r4, r3
	strb	r2, [r7, #16]
	strb	r3, [r7, #28]
	mov	r2, #1
	mov	r3, #3
	strb	r2, [r7, #20]
	strb	r3, [r7, #44]
	mov	r3, #4
	strb	r3, [r7, #76]
.L131:
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
	bne	.L131
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L135:
	.align	2
.L134:
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
	beq	.L137
	subs	lr, r0, #255
	movne	lr, #1
	cmp	r0, #16
	movle	r4, #0
	andgt	r4, lr, #1
	cmp	r4, #0
	movne	r4, #0
	bne	.L137
	cmp	r2, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
	cmp	r0, #255
	movne	r1, #0
	andeq	r1, r1, #1
	cmp	r1, #0
	bne	.L137
	cmp	r0, #1
	moveq	r4, #5
	beq	.L137
	cmp	lr, #0
	str	r3, [fp, #-24]
	ldrne	r2, .L159
	addne	r0, r2, r0, lsl #3
	ldrne	r2, [r0, #24]
	ldrne	ip, [r0, #20]
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
	bgt	.L141
	rsb	r2, r0, #2256
	add	r2, r2, #7
	cmp	r3, r2
	bge	.L142
.L152:
	mov	r4, #4
.L137:
	mov	r2, r4
	ldr	r1, .L159+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L141:
	sub	r2, r0, #2256
	sub	r2, r2, #7
	cmp	r3, r2
	blt	.L152
.L142:
	movw	r3, #1819
	cmp	r0, r3
	bgt	.L143
	rsb	r3, r0, #1808
	add	r3, r3, #12
	cmp	r2, r3
	blt	.L154
.L144:
	movw	r2, #1364
	cmp	r0, r2
	rsble	r0, r0, #1360
	subgt	r0, r0, #1360
	addle	r0, r0, #5
	subgt	r0, r0, #5
	cmp	r3, r0
	movlt	r4, #2
	movge	r4, #1
	b	.L137
.L143:
	sub	r3, r0, #1808
	sub	r3, r3, #12
	cmp	r2, r3
	bge	.L144
.L154:
	mov	r4, #3
	b	.L137
.L160:
	.align	2
.L159:
	.word	.LANCHOR0
	.word	.LC4
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
	ldr	r1, .L167
	mov	r7, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #168]
	cmn	r3, #1
	movne	r5, #0
	movwne	r6, #52429
	movne	r4, r5
	movtne	r6, 52428
	bne	.L164
	b	.L165
.L163:
	ldr	r3, [r7, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bls	.L165
.L164:
	ldr	r3, [r7, #2400]
	mov	r2, r4
	ldr	r1, .L167+4
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
	bne	.L163
	ldr	r1, .L167+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #168]
	add	r3, r3, #1
	cmp	r3, r4
	bhi	.L164
.L165:
	ldr	r1, .L167+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, .L167+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L168:
	.align	2
.L167:
	.word	.LC5
	.word	.LC8
	.word	.LC6
	.word	.LC7
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
	ldr	r1, .L190
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #172]
	ldr	r1, .L190+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #172]
	cmp	r3, #0
	addne	r5, r7, #2400
	movne	r4, #0
	addne	r5, r5, #12
	beq	.L177
.L176:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L190+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L190+12
	cmp	r3, #0
	beq	.L174
	ldr	r2, [r3, #16]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L174
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #252]
	bl	FSP_GetLogicFs
	ldr	r1, .L190+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L174:
	ldr	r1, .L190+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #172]
	cmp	r3, r4
	bhi	.L176
.L177:
	ldr	r2, [r6, #176]
	mov	r0, #1
	ldr	r1, .L190+24
	bl	dprint_vfmw
	ldr	r3, [r6, #176]
	cmp	r3, #0
	addne	r5, r7, #2480
	movne	r4, #0
	beq	.L172
.L181:
	ldr	r3, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L190+28
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
	ldr	r3, [r5]
	add	r4, r4, r0
	ldr	r1, .L190+12
	cmp	r3, #0
	beq	.L179
	ldr	r2, [r3, #16]
	bl	dprint_vfmw
	ldr	r3, [r5]
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L179
	ldr	r1, [r3, #28]
	ldr	r0, [r7, #252]
	bl	FSP_GetLogicFs
	ldr	r1, .L190+16
	mov	r2, r0
	mov	r0, #1
	bl	dprint_vfmw
.L179:
	ldr	r1, .L190+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #176]
	cmp	r3, r4
	bhi	.L181
.L172:
	ldr	r1, .L190+32
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L191:
	.align	2
.L190:
	.word	.LC9
	.word	.LC10
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC6
	.word	.LC11
	.word	.LC16
	.word	.LC15
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
	ldr	r1, .L199
	mov	r10, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	cmp	r3, #0
	addne	r8, r10, #12672
	movne	r9, #0
	addne	r8, r8, #48
	beq	.L196
.L195:
	ldrb	ip, [r8, #2]	@ zero_extendqisi2
	mov	r3, r8
	mov	r2, r9
	ldr	r1, .L199+4
	mov	r0, #1
	add	r5, r8, #616
	str	ip, [sp, #8]
	mov	r4, #0
	ldrb	ip, [r8, #1]	@ zero_extendqisi2
	str	ip, [sp, #4]
	ldr	ip, [r8, #48]
	str	ip, [sp]
	bl	dprint_vfmw
.L194:
	ldrd	r6, [r5, #8]!
	mov	r2, r4
	ldr	r1, .L199+8
	add	r4, r4, #1
	mov	r0, #1
	strd	r6, [sp]
	bl	dprint_vfmw
	cmp	r4, #4
	bne	.L194
	ldr	r1, .L199+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #180]
	add	r9, r9, #1
	add	r8, r8, #712
	cmp	r3, r9
	bhi	.L195
.L196:
	ldr	r1, .L199+16
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L200:
	.align	2
.L199:
	.word	.LC17
	.word	.LC19
	.word	.LC20
	.word	.LC6
	.word	.LC18
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
	ldr	r1, .L204
	mov	r5, r0
	mov	r0, #1
	bl	dprint_vfmw
	add	ip, r5, #12288
	mov	r2, #0
	ldr	r1, .L204+4
	ldr	r3, [ip, #236]
	mov	r0, #1
	ldr	ip, [ip, #232]
	add	r6, r5, #12480
	add	r7, r5, #12544
	add	r5, r5, #12608
	add	r6, r6, #44
	add	r7, r7, #44
	str	ip, [sp]
	add	r5, r5, #44
	bl	dprint_vfmw
	mov	r4, #0
.L202:
	ldr	lr, [r5, #4]!
	mov	r2, r4
	ldr	ip, [r7, #4]!
	add	r4, r4, #1
	ldr	r3, [r6, #4]!
	mov	r0, #1
	ldr	r1, .L204+8
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	cmp	r4, #16
	bne	.L202
	ldr	r1, .L204+12
	mov	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L205:
	.align	2
.L204:
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC24
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
	ldr	r1, .L222
	mov	r9, r0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r9, #2600]
	ldr	lr, [r9, #2596]
	mov	r0, #1
	ldr	ip, [r9, #2604]
	ldr	r3, [r9, #2588]
	ldr	r2, [r9, #2584]
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L222+4
	bl	dprint_vfmw
	ldr	r3, [r9, #2588]
	cmp	r3, #0
	addne	r4, r9, #2592
	movne	r5, #0
	addne	r4, r4, #12
	beq	.L211
.L210:
	ldr	r3, [r4, #4]!
	ldr	r0, [r9, #252]
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
	ldr	r0, [r9, #252]
	bl	FSP_GetRef
	ldr	r3, [r4]
	ldr	r1, [r3, #28]
	mov	r7, r0
	ldr	r0, [r9, #252]
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
	ldr	r1, .L222+8
	str	r0, [sp, #36]
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #2588]
	cmp	r3, r5
	bhi	.L210
.L211:
	ldr	r1, .L222+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #2588]
	cmp	r3, #0
	addne	r5, r9, #2592
	movne	r6, #0
	addne	r5, r5, #12
	bne	.L218
	b	.L209
.L221:
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L222+16
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4]
	ldr	r1, .L222+20
	mov	r0, #1
	bl	dprint_vfmw
	ldrsb	r2, [r4, #1]
	ldr	r1, .L222+24
	mov	r0, #1
	bl	dprint_vfmw
.L213:
	cmp	r8, #0
	mov	r2, r8
	ldr	r1, .L222+28
	mov	r0, #1
	beq	.L214
	bl	dprint_vfmw
	ldr	r2, [r8, #72]
	ldr	r1, .L222+32
	mov	r0, #1
	bl	dprint_vfmw
.L215:
	cmp	r7, #0
	mov	r2, r7
	ldr	r1, .L222+36
	mov	r0, #1
	beq	.L216
	bl	dprint_vfmw
	ldr	r2, [r7, #72]
	ldr	r1, .L222+40
	mov	r0, #1
	bl	dprint_vfmw
.L217:
	ldr	r1, .L222+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r9, #2588]
	add	r6, r6, #1
	cmp	r3, r6
	bls	.L209
.L218:
	ldr	r3, [r5, #4]!
	ldr	r0, [r9, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r4, r0
	ldr	r0, [r9, #252]
	bl	FSP_GetDecPhyFs
	ldr	r3, [r5]
	ldr	r1, [r3, #28]
	mov	r8, r0
	ldr	r0, [r9, #252]
	bl	FSP_GetDispPhyFs
	mov	r2, r6
	ldr	r1, .L222+44
	mov	r7, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r4, #0
	mov	r2, r4
	ldr	r1, .L222+48
	mov	r0, #1
	bne	.L221
	ldr	r1, .L222+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L213
.L216:
	ldr	r1, .L222+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L217
.L214:
	ldr	r1, .L222+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L215
.L209:
	ldr	r1, .L222+64
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L223:
	.align	2
.L222:
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC6
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC35
	.word	.LC36
	.word	.LC38
	.word	.LC39
	.word	.LC29
	.word	.LC30
	.word	.LC34
	.word	.LC40
	.word	.LC37
	.word	.LC28
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
	bls	.L226
	sub	r0, r0, #16
	cmp	r0, #5
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L226:
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
	ldr	r3, [r0, #3520]
	cmp	r3, #0
	bne	.L234
	ldr	r2, [r0, #2404]
	ldr	r1, [r2, #652]
	cmp	r1, #1
	beq	.L238
.L236:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L234:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L238:
	ldr	r0, [r2, #648]
	cmp	r0, #0
	bne	.L236
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
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	ldr	r0, [r4, #2356]
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
	ldr	r1, [r0, #2392]
	mov	r6, r2
	ldr	r2, [r0, #2388]
	mov	r5, r0
	str	r3, [fp, #-48]
	ldr	r7, [r1, #68]
	ldr	r2, [r2, #128]
	sub	r3, r7, #1
	ldr	r9, [r1, #72]
	cmp	r3, #9
	str	r2, [fp, #-52]
	bhi	.L268
	sub	r3, r9, #1
	cmp	r3, #10
	bhi	.L269
	ldr	r4, .L270
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
	ble	.L249
	ldr	r3, [fp, #-52]
	mov	r2, #0
	mov	r1, r2
	mov	r0, r6
	sub	r10, r3, #4
.L248:
	str	r2, [r6, r1, asl #3]
	mov	r3, r2, asl r10
	ldr	ip, [r5, #2392]
	add	ip, ip, r1, lsl #1
	ldrsh	ip, [ip, #172]
	add	r2, ip, r2
	sub	ip, r2, #1
	str	ip, [r0, #4]
	mov	lr, r2, asl r10
	cmp	r3, lr
	bge	.L254
	cmp	r3, #255
	bhi	.L250
	uxtb	r4, r1
	add	ip, r8, r3
	b	.L252
.L253:
	cmp	r3, #256
	beq	.L250
.L252:
	add	r3, r3, #1
	strb	r4, [ip], #1
	cmp	r3, lr
	bne	.L253
.L254:
	add	r1, r1, #1
	add	r0, r0, #8
	cmp	r1, r7
	bne	.L248
.L249:
	cmp	r9, #0
	ble	.L246
	ldr	r3, [fp, #-52]
	mov	ip, #0
	ldr	r7, [fp, #-48]
	mov	lr, ip
	sub	r4, r3, #4
	mov	r6, r7
.L256:
	str	ip, [r7, lr, asl #3]
	mov	r3, ip, asl r4
	ldr	r2, [r5, #2392]
	add	r2, r2, lr, lsl #1
	ldrsh	r2, [r2, #212]
	add	ip, r2, ip
	sub	r2, ip, #1
	str	r2, [r6, #4]
	mov	r1, ip, asl r4
	cmp	r3, r1
	bge	.L261
	cmp	r3, #255
	bhi	.L257
	add	r2, r3, #255
	uxtb	r0, lr
	add	r2, r8, r2
	b	.L259
.L260:
	cmp	r3, #256
	beq	.L257
.L259:
	add	r3, r3, #1
	strb	r0, [r2, #1]!
	cmp	r3, r1
	bne	.L260
.L261:
	add	lr, lr, #1
	add	r6, r6, #8
	cmp	lr, r9
	bne	.L256
.L246:
	mov	r0, #0
	b	.L242
.L250:
	ldr	r2, .L270+4
	mov	r0, #1
	ldr	r1, .L270+8
	bl	dprint_vfmw
	mvn	r0, #0
.L242:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L257:
	ldr	r2, .L270+4
	mov	r0, #1
	ldr	r1, .L270+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L242
.L269:
	mov	r1, #11
	mov	r3, r9
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L270+4
	ldr	r1, .L270+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L242
.L268:
	mov	r1, #10
	mov	r3, r7
	str	r1, [sp]
	mov	r0, #1
	ldr	r2, .L270+4
	ldr	r1, .L270+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L242
.L271:
	.align	2
.L270:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+156
	.word	.LC43
	.word	.LC44
	.word	.LC42
	.word	.LC41
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
	ldr	r2, [r0, #2356]
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
	ldr	r3, .L280
	mov	r5, r1
	mov	r2, #32
	ldr	r1, [r0, #2356]
	sub	r0, fp, #52
	ldr	r3, [r3, #52]
	mov	r5, r5, asl #3
	blx	r3
	ldr	r3, [fp, #-28]
	ldr	r2, [fp, #-24]
	rsb	r3, r2, r3
	cmp	r3, r5
	movcs	r0, #0
	bcc	.L279
.L274:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L279:
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsShow
	cmp	r0, #0
	moveq	r0, #1
	beq	.L274
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
	b	.L275
.L276:
	bl	BsSkip
	ldr	r3, [fp, #-28]
	ldr	r4, [fp, #-24]
	rsb	r4, r4, r3
.L275:
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
	bne	.L276
	mov	r0, r3
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L281:
	.align	2
.L280:
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
	beq	.L290
	mov	r1, #8
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r6, #3
	mov	r7, r0
.L289:
	cmp	r7, #0
	bne	.L284
	mov	r4, #16
.L285:
	mov	r1, #8
	ldr	r0, [r5, #2356]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L285
.L286:
	subs	r6, r6, #1
	bne	.L289
.L294:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L284:
	cmp	r7, #1
	beq	.L293
	cmp	r7, #2
	bne	.L286
	mov	r1, #32
	ldr	r0, [r5, #2356]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L289
	b	.L294
.L293:
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	subs	r6, r6, #1
	bne	.L289
	b	.L294
.L290:
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
	beq	.L297
	mov	r1, #1
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L297:
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
	beq	.L301
	add	r7, r1, #12
	mov	r4, r1
	mov	r3, #1
	strb	r3, [r1]
.L300:
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	str	r0, [r4, #4]!
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r4, r7
	str	r0, [r4, #12]
	bne	.L300
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	str	r0, [r6, #28]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #32]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #32
	str	r0, [r6, #36]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r3, #0
	str	r0, [r6, #40]
.L299:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L301:
	mvn	r3, #0
	b	.L299
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
	beq	.L305
	mov	r3, #1
	mov	r1, #16
	strb	r3, [r5]
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #16
	strh	r0, [r5, #2]	@ movhi
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r3, r4
	strh	r0, [r5, #4]	@ movhi
.L304:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L305:
	mvn	r3, #0
	b	.L304
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
	beq	.L308
	ldr	r0, [r0, #2356]
	mov	r1, #8
	bl	BsGet
	mov	r3, r4
	strb	r0, [r5]
.L307:
	mov	r0, r3
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L308:
	mvn	r3, #0
	b	.L307
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
	beq	.L311
	mov	r1, #1
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	r0, [r5, #2356]
	bl	BsToNextByte
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L311:
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
	beq	.L315
	mov	r1, #1
	ldr	r0, [r0, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L316
.L314:
	ldr	r0, [r4, #2356]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L316:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L314
.L315:
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
	beq	.L319
	mov	r1, #4
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #1]
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r3, r4
	mov	r2, #1
	strb	r2, [r5]
	strb	r0, [r5, #2]
.L318:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L319:
	mvn	r3, #0
	b	.L318
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
	bls	.L329
.L323:
	mov	r1, #8
	ldr	r0, [r5, #2356]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L323
	subs	r6, r6, #16
	beq	.L325
.L324:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r6, r4
	bne	.L324
.L325:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L329:
	ldr	r1, .L330
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L331:
	.align	2
.L330:
	.word	.LC45
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
	ldr	r3, [r7, #172]
	cmp	r3, #0
	beq	.L333
	ldr	r4, [r0, #2416]
	cmp	r4, #0
	beq	.L334
	ldr	r2, [r4, #16]
	cmp	r2, #0
	addne	r6, r0, #2416
	movne	r4, #0
	bne	.L339
	b	.L377
.L340:
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L341
	ldr	r3, [r7, #172]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L378
	ldr	r2, [r6, #4]!
	cmp	r2, #0
	beq	.L334
	ldr	r2, [r2, #16]
	cmp	r2, #0
	beq	.L335
.L339:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	bne	.L340
.L341:
	add	r3, r4, #604
	mov	r2, r4
	ldr	r1, .L382
	mov	r0, #1
	ldr	r3, [r5, r3, asl #2]
	ldr	r3, [r3, #16]
	str	ip, [sp]
	bl	dprint_vfmw
.L338:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L378:
	cmp	r3, #0
	beq	.L333
	ldr	r2, [r7, #176]
	cmp	r2, #0
	beq	.L333
	ldr	r4, [r5, #2484]
	cmp	r4, #0
	beq	.L346
	ldr	r2, [r4, #16]
	cmp	r2, #0
	addne	r6, r5, #2480
	movne	r4, #0
	addne	r6, r6, #4
	bne	.L350
	b	.L379
.L351:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L352
	ldr	r3, [r7, #176]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L333
	ldr	r3, [r6, #4]!
	cmp	r3, #0
	beq	.L380
	ldr	r2, [r3, #16]
	cmp	r2, #0
	beq	.L381
.L350:
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L351
.L352:
	mov	r3, r0
	mov	r2, r4
	ldr	r1, .L382+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L372
.L333:
	mov	r0, #0
.L372:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L334:
	mov	r2, r4
	ldr	r1, .L382+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L338
.L377:
	mov	r4, r2
.L335:
	mov	r2, r4
	ldr	r1, .L382+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L338
.L380:
	ldr	r3, [r7, #172]
.L346:
	mov	r2, r4
	ldr	r1, .L382+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L372
.L381:
	ldr	r3, [r7, #172]
.L347:
	mov	r2, r4
	ldr	r1, .L382+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L372
.L379:
	mov	r4, r2
	b	.L347
.L383:
	.align	2
.L382:
	.word	.LC48
	.word	.LC51
	.word	.LC46
	.word	.LC47
	.word	.LC49
	.word	.LC50
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
	ldr	r3, [r0, #2588]
	cmp	r3, #16
	bhi	.L385
	cmp	r3, #0
	addne	ip, r0, #2592
	mvnne	r4, #-2147483648
	addne	ip, ip, #12
	movne	r3, #0
	beq	.L387
.L390:
	ldr	r2, [ip, #4]!
	ldr	lr, [r2, #8]
	cmp	lr, r4
	bge	.L389
	ldr	r2, [r2]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	streq	r3, [r1]
	moveq	r4, lr
.L389:
	ldr	r2, [r0, #2588]
	add	r3, r3, #1
	cmp	r2, r3
	bhi	.L390
	ldr	r3, [r1]
	cmn	r3, #1
	beq	.L387
	str	r4, [sp]
	mov	r0, #1
	ldr	r2, .L393
	ldr	r1, .L393+4
	bl	dprint_vfmw
	mov	r0, #0
.L388:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L385:
	ldr	r2, .L393
	mov	r0, #1
	ldr	r1, .L393+8
	bl	dprint_vfmw
	mov	r0, r4
	b	.L388
.L387:
	ldr	r2, .L393
	mov	r0, #1
	ldr	r1, .L393+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L388
.L394:
	.align	2
.L393:
	.word	.LANCHOR0+176
	.word	.LC54
	.word	.LC52
	.word	.LC53
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
	ldr	r3, [r0, #2584]
	mov	r4, r0
	cmp	r3, #16
	bhi	.L399
	ldr	r0, [r0, #252]
	bl	FSP_GetTotalValidFsNum
	ldr	r2, [r4, #252]
	ldr	r1, [r4, #3528]
	mov	r5, r0
	ldr	r0, [r4, #3524]
	bl	FSP_GetOccupiedNum
	rsb	r0, r0, r5
	bic	r0, r0, r0, asr #31
	cmp	r0, #0
	ble	.L398
	ldr	r3, [r4, #2584]
	add	r3, r3, #1
	cmp	r0, r3
	bcc	.L398
	str	r3, [r4, #2584]
	mov	r0, #13
	ldr	r2, .L400
	ldr	r1, .L400+4
	bl	dprint_vfmw
	mov	r0, #0
.L397:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L398:
	mov	r3, r0
	ldr	r2, .L400
	ldr	r1, .L400+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L397
.L399:
	mov	r5, #17
	ldr	r2, .L400
	mov	r0, #1
	str	r5, [sp]
	ldr	r1, .L400+12
	bl	dprint_vfmw
	str	r5, [r4, #2584]
	mvn	r0, #0
	b	.L397
.L401:
	.align	2
.L400:
	.word	.LANCHOR0+204
	.word	.LC56
	.word	.LC57
	.word	.LC55
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
	add	r3, r0, #4096
	ldr	r2, [r3, #132]
	sub	r1, r2, #16
	cmp	r1, #5
	bls	.L403
	ldr	r2, [r0, #3508]
	sub	r2, r2, #16
	cmp	r2, #5
	bls	.L414
	ldr	r3, [r3, #124]
	cmp	r3, #1
	beq	.L406
	cmp	r3, #2
	beq	.L407
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r0, #3520]
	ldmfd	sp, {fp, sp, pc}
.L403:
	mov	r3, #0
	str	r2, [r0, #3508]
	str	r3, [r0, #3520]
	ldmfd	sp, {fp, sp, pc}
.L406:
	ldr	r2, [r0, #3520]
	cmp	r2, #2
	beq	.L415
	str	r3, [r0, #3520]
	ldmfd	sp, {fp, sp, pc}
.L407:
	ldr	r3, [r0, #3520]
	sub	r3, r3, #1
	cmp	r3, #1
	movhi	r3, #0
	strhi	r3, [r0, #3520]
	ldmfd	sp, {fp, sp, pc}
.L415:
	ldmfd	sp, {fp, sp, pc}
.L414:
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
	ldr	r0, [r0, #132]
	cmp	r0, #15
	bhi	.L417
	tst	r0, #1
	bne	.L419
.L417:
	sub	r0, r0, #16
	cmp	r0, #7
	movhi	r0, #0
	movls	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L419:
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
	ldr	r0, [r1, #604]
	ldr	r3, [r1, #608]
	ldrb	ip, [r1, #596]	@ zero_extendqisi2
	ldrb	lr, [r1, #600]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r0, r0
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r0
	str	r3, [r2]
	ldr	r0, [r1, #604]
	ldrb	lr, [r1, #597]	@ zero_extendqisi2
	ldrb	r3, [r1, #609]	@ zero_extendqisi2
	and	r0, r0, #65280
	ldrb	ip, [r1, #601]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #4]
	ldr	r0, [r1, #600]
	ldrb	lr, [r1, #598]	@ zero_extendqisi2
	ldrb	r3, [r1, #610]	@ zero_extendqisi2
	and	r0, r0, #16711680
	ldrb	ip, [r1, #606]	@ zero_extendqisi2
	orr	r0, lr, r0
	orr	r3, r0, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #8]
	ldr	r0, [r1, #608]
	ldrb	r3, [r1, #603]	@ zero_extendqisi2
	ldrb	lr, [r1, #599]	@ zero_extendqisi2
	and	r0, r0, #-16777216
	ldrb	ip, [r1, #607]	@ zero_extendqisi2
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
	ldr	r1, [r0, #1756]
	ldr	r3, [r0, #1772]
	ldrb	ip, [lr, #596]	@ zero_extendqisi2
	ldrb	r4, [r0, #1764]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1788]
	ldr	r3, [r0, #1804]
	ldrb	ip, [r0, #1780]	@ zero_extendqisi2
	ldrb	r4, [r0, #1796]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1756]
	ldrb	r4, [lr, #597]	@ zero_extendqisi2
	ldrb	r3, [r0, #1773]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1765]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1788]
	ldrb	r4, [r0, #1781]	@ zero_extendqisi2
	ldrb	r3, [r0, #1805]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1797]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1764]
	ldrb	r4, [lr, #598]	@ zero_extendqisi2
	ldrb	r3, [r0, #1774]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1758]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1796]
	ldrb	r4, [r0, #1782]	@ zero_extendqisi2
	ldrb	r3, [r0, #1806]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1790]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1772]
	ldrb	lr, [lr, #599]	@ zero_extendqisi2
	ldrb	r3, [r0, #1767]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1759]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1804]
	ldrb	lr, [r0, #1783]	@ zero_extendqisi2
	ldrb	r3, [r0, #1799]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1791]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1760]
	ldr	r3, [r0, #1776]
	ldrb	ip, [r0, #1752]	@ zero_extendqisi2
	ldrb	lr, [r0, #1768]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1792]
	ldr	r3, [r0, #1808]
	ldrb	ip, [r0, #1784]	@ zero_extendqisi2
	ldrb	lr, [r0, #1800]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1760]
	ldrb	lr, [r0, #1753]	@ zero_extendqisi2
	ldrb	r3, [r0, #1777]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1769]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1792]
	ldrb	lr, [r0, #1785]	@ zero_extendqisi2
	ldrb	r3, [r0, #1809]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1801]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1768]
	ldrb	lr, [r0, #1754]	@ zero_extendqisi2
	ldrb	r3, [r0, #1778]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1762]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #1786]	@ zero_extendqisi2
	ldr	r1, [r0, #1800]
	ldrb	r3, [r0, #1810]	@ zero_extendqisi2
	ldrb	ip, [r0, #1794]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1776]
	ldrb	lr, [r0, #1755]	@ zero_extendqisi2
	ldrb	r3, [r0, #1771]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1763]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1808]
	ldrb	ip, [r0, #1787]	@ zero_extendqisi2
	ldrb	r3, [r0, #1803]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1795]	@ zero_extendqisi2
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
	ldr	r1, [r0, #996]
	ldr	r3, [r0, #1028]
	ldrb	ip, [lr, #596]	@ zero_extendqisi2
	ldrb	r4, [r0, #1012]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1004]
	ldr	r3, [r0, #1036]
	ldrb	ip, [r0, #988]	@ zero_extendqisi2
	ldrb	r4, [r0, #1020]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #996]
	ldrb	r4, [lr, #597]	@ zero_extendqisi2
	ldrb	r3, [r0, #1029]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1013]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1004]
	ldrb	r4, [r0, #989]	@ zero_extendqisi2
	ldrb	r3, [r0, #1037]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1021]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1012]
	ldrb	r4, [lr, #598]	@ zero_extendqisi2
	ldrb	r3, [r0, #1030]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #998]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1020]
	ldrb	r4, [r0, #990]	@ zero_extendqisi2
	ldrb	r3, [r0, #1038]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1006]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1028]
	ldrb	lr, [lr, #599]	@ zero_extendqisi2
	ldrb	r3, [r0, #1015]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #999]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1036]
	ldrb	lr, [r0, #991]	@ zero_extendqisi2
	ldrb	r3, [r0, #1023]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1007]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1000]
	ldr	r3, [r0, #1032]
	ldrb	ip, [r0, #984]	@ zero_extendqisi2
	ldrb	lr, [r0, #1016]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1008]
	ldr	r3, [r0, #1040]
	ldrb	ip, [r0, #992]	@ zero_extendqisi2
	ldrb	lr, [r0, #1024]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1000]
	ldrb	lr, [r0, #985]	@ zero_extendqisi2
	ldrb	r3, [r0, #1033]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1017]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1008]
	ldrb	lr, [r0, #993]	@ zero_extendqisi2
	ldrb	r3, [r0, #1041]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1025]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1016]
	ldrb	lr, [r0, #986]	@ zero_extendqisi2
	ldrb	r3, [r0, #1034]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1002]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #994]	@ zero_extendqisi2
	ldr	r1, [r0, #1024]
	ldrb	r3, [r0, #1042]	@ zero_extendqisi2
	ldrb	ip, [r0, #1010]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1032]
	ldrb	lr, [r0, #987]	@ zero_extendqisi2
	ldrb	r3, [r0, #1019]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1003]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1040]
	ldrb	ip, [r0, #995]	@ zero_extendqisi2
	ldrb	r3, [r0, #1027]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1011]	@ zero_extendqisi2
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
	ldr	r1, [r0, #1372]
	ldr	r3, [r0, #1388]
	ldrb	ip, [lr, #596]	@ zero_extendqisi2
	ldrb	r4, [r0, #1380]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2]
	ldr	r1, [r0, #1404]
	ldr	r3, [r0, #1420]
	ldrb	ip, [r0, #1396]	@ zero_extendqisi2
	ldrb	r4, [r0, #1412]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, r4, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #4]
	ldr	r1, [r0, #1372]
	ldrb	r4, [lr, #597]	@ zero_extendqisi2
	ldrb	r3, [r0, #1389]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1381]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #8]
	ldr	r1, [r0, #1404]
	ldrb	r4, [r0, #1397]	@ zero_extendqisi2
	ldrb	r3, [r0, #1421]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1413]	@ zero_extendqisi2
	orr	r1, r4, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #12]
	ldr	ip, [r0, #1380]
	ldrb	r4, [lr, #598]	@ zero_extendqisi2
	ldrb	r3, [r0, #1390]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1374]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #16]
	ldr	ip, [r0, #1412]
	ldrb	r4, [r0, #1398]	@ zero_extendqisi2
	ldrb	r3, [r0, #1422]	@ zero_extendqisi2
	and	ip, ip, #16711680
	ldrb	r1, [r0, #1406]	@ zero_extendqisi2
	orr	ip, r4, ip
	orr	r3, ip, r3, asl #24
	orr	r3, r3, r1, asl #8
	str	r3, [r2, #20]
	ldr	r1, [r0, #1388]
	ldrb	lr, [lr, #599]	@ zero_extendqisi2
	ldrb	r3, [r0, #1383]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1375]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #24]
	ldr	r1, [r0, #1420]
	ldrb	lr, [r0, #1399]	@ zero_extendqisi2
	ldrb	r3, [r0, #1415]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1407]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #28]
	ldr	r1, [r0, #1376]
	ldr	r3, [r0, #1392]
	ldrb	ip, [r0, #1368]	@ zero_extendqisi2
	ldrb	lr, [r0, #1384]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #32]
	ldr	r1, [r0, #1408]
	ldr	r3, [r0, #1424]
	ldrb	ip, [r0, #1400]	@ zero_extendqisi2
	ldrb	lr, [r0, #1416]	@ zero_extendqisi2
	mov	r1, r1, asl #8
	orr	r3, ip, r3, asl #24
	uxth	r1, r1
	orr	r3, r3, lr, asl #16
	orr	r3, r3, r1
	str	r3, [r2, #36]
	ldr	r1, [r0, #1376]
	ldrb	lr, [r0, #1369]	@ zero_extendqisi2
	ldrb	r3, [r0, #1393]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1385]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #40]
	ldr	r1, [r0, #1408]
	ldrb	lr, [r0, #1401]	@ zero_extendqisi2
	ldrb	r3, [r0, #1425]	@ zero_extendqisi2
	and	r1, r1, #65280
	ldrb	ip, [r0, #1417]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #16
	str	r3, [r2, #44]
	ldr	r1, [r0, #1384]
	ldrb	lr, [r0, #1370]	@ zero_extendqisi2
	ldrb	r3, [r0, #1394]	@ zero_extendqisi2
	and	r1, r1, #16711680
	ldrb	ip, [r0, #1378]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #48]
	ldrb	lr, [r0, #1402]	@ zero_extendqisi2
	ldr	r1, [r0, #1416]
	ldrb	r3, [r0, #1426]	@ zero_extendqisi2
	ldrb	ip, [r0, #1410]	@ zero_extendqisi2
	and	r1, r1, #16711680
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #24
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #52]
	ldr	r1, [r0, #1392]
	ldrb	lr, [r0, #1371]	@ zero_extendqisi2
	ldrb	r3, [r0, #1387]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	ip, [r0, #1379]	@ zero_extendqisi2
	orr	r1, lr, r1
	orr	r3, r1, r3, asl #16
	orr	r3, r3, ip, asl #8
	str	r3, [r2, #56]
	ldr	r1, [r0, #1424]
	ldrb	ip, [r0, #1403]	@ zero_extendqisi2
	ldrb	r3, [r0, #1419]	@ zero_extendqisi2
	and	r1, r1, #-16777216
	ldrb	r0, [r0, #1411]	@ zero_extendqisi2
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
	ldr	ip, [r0, #2392]
	mov	r6, r1
	ldrb	r3, [ip, #13]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L459
	ldr	r3, [ip, #72]
	ldr	r7, [ip, #68]
	ldrb	r4, [ip, #15]	@ zero_extendqisi2
	mov	r2, r3
	str	r3, [fp, #-236]
	ldr	r3, [r0, #2388]
	cmp	r2, #0
	sub	r8, r2, #1
	sub	r2, r7, #1
	str	r2, [fp, #-240]
	ldr	r5, [r3, #64]
	ldr	r1, [r3, #128]
	ble	.L430
	ldr	r3, [fp, #-236]
	add	r2, ip, #210
	sub	r0, fp, #216
	add	lr, r3, #105
	add	lr, ip, lr, lsl #1
.L429:
	ldrsh	r3, [r2, #2]!
	cmp	r2, lr
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L429
.L430:
	cmp	r7, #0
	ble	.L428
	add	r3, r7, #85
	add	r2, ip, #170
	sub	r0, fp, #128
	add	ip, ip, r3, lsl #1
.L433:
	ldrsh	r3, [r2, #2]!
	cmp	r2, ip
	sub	r3, r3, #1
	str	r3, [r0, #4]!
	bne	.L433
.L428:
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
	beq	.L471
	cmp	r8, #0
	mov	r3, #0
	blt	.L450
	sub	r10, fp, #212
	mov	r4, r3
	mov	r6, r3
	mov	r8, r3
	str	r3, [fp, #-232]
	str	r3, [fp, #-244]
.L436:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L453
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	r1, r2
	add	r8, r8, #1
	sub	lr, fp, #128
	mov	r6, r4
	add	r9, r3, r8
	b	.L439
.L451:
	mov	r6, r4
.L439:
	ldr	r3, [lr, #4]!
	add	r1, r1, #1
	add	r3, r3, #1
	add	ip, r2, r3
	cmp	r5, ip
	mla	r4, r8, r3, r4
	bge	.L437
	cmp	r0, r9
	blt	.L469
.L437:
	cmp	r1, r7
	mov	r2, ip
	bne	.L451
.L442:
	add	r2, ip, r3
	cmp	r5, r2
	bge	.L452
	cmp	r0, r9
	blt	.L472
.L452:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	r1, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, r1
	str	r2, [fp, #-244]
	bne	.L436
	rsb	r0, r9, r0
	mov	r2, ip
	rsb	r2, r2, r5
	mul	r3, r0, r3
	add	r3, r2, r3
	add	r6, r3, r6
.L459:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L471:
	cmp	r8, #0
	mov	r3, r4
	blt	.L450
	sub	r10, fp, #212
	mov	lr, r4
	mov	r6, r4
	mov	r8, r4
	str	r4, [fp, #-232]
	str	r4, [fp, #-244]
.L435:
	ldr	r2, [fp, #-240]
	cmp	r2, #0
	blt	.L456
	ldr	r8, [r10]
	mov	r2, #0
	ldr	r3, [fp, #-232]
	mov	ip, r2
	add	r8, r8, #1
	sub	r4, fp, #128
	mov	r6, lr
	add	r9, r3, r8
	b	.L445
.L454:
	mov	r6, lr
.L445:
	ldr	r3, [r4, #4]!
	add	ip, ip, #1
	add	r3, r3, #1
	add	r1, r2, r3
	cmp	r5, r1
	mla	lr, r8, r3, lr
	bge	.L443
	cmp	r0, r9
	blt	.L444
.L443:
	cmp	ip, r7
	mov	r2, r1
	bne	.L454
.L448:
	add	r2, r1, r3
	cmp	r5, r2
	bge	.L468
	cmp	r0, r9
	blt	.L473
.L468:
	ldr	r2, [fp, #-244]
	add	r10, r10, #4
	ldr	ip, [fp, #-236]
	add	r2, r2, #1
	str	r9, [fp, #-232]
	cmp	r2, ip
	str	r2, [fp, #-244]
	bne	.L435
	rsb	r0, r9, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L434
.L469:
	ldr	r1, [fp, #-232]
	rsb	r0, r1, r0
	mul	r3, r0, r3
.L434:
	rsb	r2, r2, r5
	add	r3, r2, r3
	add	r6, r3, r6
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L444:
	cmp	r1, r5
	bgt	.L469
	mov	r1, r2
	b	.L468
.L453:
	ldr	r2, [fp, #-232]
	mov	ip, #0
	add	r9, r2, r8
	b	.L442
.L456:
	ldr	r2, [fp, #-232]
	mov	r1, #0
	add	r9, r2, r8
	b	.L448
.L472:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, ip
	mul	r3, r0, r3
	b	.L434
.L473:
	ldr	r2, [fp, #-232]
	rsb	r0, r2, r0
	mov	r2, r1
	mul	r3, r0, r3
	b	.L434
.L450:
	mov	r2, r3
	mov	r6, r3
	b	.L434
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
	ldr	lr, [r0, #2392]
	mov	r7, r1
	ldrb	r3, [lr, #13]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r0, r1
	beq	.L498
	ldr	r3, [lr, #72]
	ldr	r8, [lr, #68]
	mov	r2, r3
	str	r3, [fp, #-232]
	ldr	r3, [r0, #2388]
	cmp	r2, #0
	ldr	r4, [r3, #64]
	ldr	ip, [r3, #128]
	ble	.L480
	ldr	r3, [fp, #-232]
	add	r2, lr, #210
	sub	r1, fp, #216
	add	r0, r3, #105
	add	r0, lr, r0, lsl #1
.L479:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L479
.L480:
	cmp	r8, #0
	ble	.L478
	add	r0, r8, #85
	add	r2, lr, #170
	sub	r1, fp, #128
	add	r0, lr, r0, lsl #1
.L483:
	ldrsh	r3, [r2, #2]!
	cmp	r2, r0
	sub	r3, r3, #1
	str	r3, [r1, #4]!
	bne	.L483
.L478:
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
	ble	.L482
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
.L484:
	cmp	r8, #0
	ble	.L494
	ldr	r6, [r0]
	ldr	r4, [fp, #-236]
	add	r6, r6, #1
	mla	ip, r6, r4, r3
	cmp	r7, ip
	blt	.L495
	mov	r5, #0
	mov	r1, r3
	mov	r2, r5
	mov	r3, ip
	sub	lr, fp, #124
	b	.L489
.L486:
	ldr	r4, [lr, #4]!
	mov	r1, r3
	add	r4, r4, #1
	mla	ip, r6, r4, r3
	cmp	ip, r7
	bgt	.L487
	mov	r3, ip
.L489:
	add	r2, r2, #1
	add	r5, r5, r4
	cmp	r2, r8
	bne	.L486
.L488:
	cmp	r3, r7
	bgt	.L493
	ldr	r2, [fp, #-232]
	add	r10, r10, #1
	add	r9, r9, r6
	add	r0, r0, #4
	cmp	r10, r2
	bne	.L484
.L493:
	mov	r3, r1
.L487:
	cmp	r4, #0
	beq	.L482
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
.L498:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L494:
	mov	r5, #0
	b	.L488
.L495:
	ldr	r4, [fp, #-236]
	mov	r5, #0
	b	.L487
.L482:
	ldr	r1, .L500
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L498
.L501:
	.align	2
.L500:
	.word	.LC58
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
	ldr	r4, .L525
	mov	r10, r0
	mov	r2, #147456
	mov	r1, #0
	ldr	r0, .L525+4
	ldr	r3, [r4, #48]
	blx	r3
	ldr	r3, [r4, #48]
	mov	r2, #36864
	mov	r1, #0
	ldr	r0, .L525+8
	blx	r3
	add	r0, r10, #8576
	ldr	r3, [r4, #48]
	mov	r2, #880
	mov	r1, #0
	add	r0, r0, #36
	blx	r3
	add	r3, r10, #8192
	str	r3, [fp, #-56]
	mov	r2, r3
	mov	r3, #0
	str	r3, [r2, #416]
	ldr	r9, [r10, #2392]
	ldr	r1, [r10, #2388]
	ldr	r2, [r9, #72]
	ldr	r8, [r1, #188]
	cmp	r2, r3
	strne	r3, [fp, #-68]
	strne	r3, [fp, #-72]
	beq	.L502
.L510:
	ldr	r2, [r9, #68]
	cmp	r2, #0
	ldr	r2, [fp, #-68]
	add	r2, r2, #104
	streq	r2, [fp, #-76]
	beq	.L511
	mov	r1, r2
	str	r2, [fp, #-76]
	mov	r7, r1, asl #1
	ldr	r1, [fp, #-72]
	mov	r2, #0
	str	r2, [fp, #-48]
	str	r2, [fp, #-52]
	mul	r1, r8, r1
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #416]
	str	r1, [fp, #-64]
.L509:
	add	r1, r2, #1072
	add	r0, r9, r7
	add	r1, r1, #4
	add	r1, r10, r1, lsl #3
	str	r3, [r1, #4]
	ldrsh	r1, [r0, #4]
	cmp	r1, #0
	ldreq	r1, [fp, #-48]
	addeq	r1, r1, #84
	streq	r1, [fp, #-60]
	beq	.L505
	ldr	r2, [fp, #-48]
	mov	r5, #0
	ldr	r1, [fp, #-52]
	add	r2, r2, #84
	ldr	r0, [fp, #-64]
	str	r2, [fp, #-60]
	add	r6, r1, r0
	mov	ip, r2, asl #1
.L506:
	add	r2, r9, ip
	ldrsh	r2, [r2, #4]
	cmp	r2, #0
	beq	.L508
	ldr	r2, .L525+4
	rsb	lr, r3, r6
	mov	r4, r3
	add	r2, r2, r3, lsl #2
.L507:
	add	r1, lr, r3
	str	r1, [r2], #4
	ldr	r9, [r10, #2392]
	add	r3, r3, #1
	rsb	r1, r4, r3
	add	r0, r9, ip
	ldrsh	r0, [r0, #4]
	cmp	r0, r1
	bhi	.L507
.L508:
	add	r2, r9, r7
	add	r5, r5, #1
	add	r6, r6, r8
	ldrsh	r2, [r2, #4]
	cmp	r2, r5
	bhi	.L506
	ldr	r2, [fp, #-56]
	ldr	r2, [r2, #416]
.L505:
	add	r1, r10, r2, lsl #3
	sub	ip, r3, #1
	add	r1, r1, #8576
	ldr	r0, [fp, #-60]
	ldr	lr, [fp, #-48]
	add	r2, r2, #1
	str	ip, [r1, #40]
	ldr	r1, [fp, #-56]
	add	r0, r9, r0, lsl #1
	add	lr, lr, #1
	str	lr, [fp, #-48]
	str	r2, [r1, #416]
	ldr	ip, [r9, #68]
	ldrsh	r1, [r0, #4]
	cmp	ip, lr
	ldr	r0, [fp, #-52]
	add	r1, r0, r1
	str	r1, [fp, #-52]
	bhi	.L509
.L511:
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
	bhi	.L510
.L502:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L526:
	.align	2
.L525:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r4, r0
	ldr	r3, [r0, #3540]
	ldr	r2, [r4, #3716]
	mov	r0, #2
	ldr	r1, .L550
	add	r5, r4, #4096
	bl	dprint_vfmw
	ldr	r1, .L550+4
	mov	r0, #4
	mov	r7, #200
	bl	dprint_vfmw
	ldr	r3, [r4, #3512]
	add	r8, r4, #8192
	mov	ip, #0
	ldr	r6, .L550+8
	add	r0, r4, #6016
	str	r3, [r5, #1848]
	mov	r2, #64
	ldr	r1, [r4, #3680]
	add	r0, r0, #24
	mul	r7, r7, r3
	str	r1, [r5, #3112]
	ldr	r3, [r4, #3684]
	add	r1, r7, #12608
	add	r1, r1, #48
	str	r3, [r5, #3116]
	add	r1, r4, r1
	ldr	r3, [r4, #3604]
	ldr	lr, [r4, #3608]
	rsb	lr, r3, lr
	str	lr, [r5, #3120]
	ldr	lr, [r4, #3716]
	str	lr, [r5, #3104]
	ldr	lr, [r4, #3540]
	str	lr, [r5, #3108]
	ldr	lr, [r4, #3704]
	str	lr, [r5, #3124]
	ldr	lr, [r4, #3708]
	str	lr, [r5, #3128]
	ldr	lr, [r4, #3712]
	str	lr, [r5, #3132]
	ldr	lr, [r4, #3612]
	rsb	r3, r3, lr
	str	r3, [r5, #3136]
	ldr	r3, [r4, #3616]
	rsb	r3, lr, r3
	str	r3, [r5, #3140]
	ldr	r3, [r4, #2408]
	str	ip, [r4, #204]
	str	r3, [r8, #212]
	ldr	r3, [r4, #2388]
	ldrb	ip, [r3, #10]	@ zero_extendqisi2
	strb	ip, [r5, #1822]
	ldrb	ip, [r3, #3]	@ zero_extendqisi2
	strb	ip, [r5, #1823]
	ldrb	ip, [r3, #7]	@ zero_extendqisi2
	strb	ip, [r5, #1824]
	ldrb	ip, [r3, #6]	@ zero_extendqisi2
	strb	ip, [r5, #1825]
	ldrb	ip, [r3, #5]	@ zero_extendqisi2
	strb	ip, [r5, #1826]
	ldr	ip, [r3, #60]
	str	ip, [r5, #1828]
	ldr	ip, [r3, #104]
	strb	ip, [r5, #1832]
	ldr	ip, [r3, #192]
	sub	ip, ip, #1
	str	ip, [r5, #1836]
	ldr	ip, [r3, #188]
	sub	ip, ip, #1
	str	ip, [r5, #1840]
	ldr	ip, [r4, #3516]
	str	ip, [r5, #1844]
	ldr	ip, [r4, #2392]
	ldr	lr, [ip, #84]
	sub	lr, lr, #2
	str	lr, [r5, #1852]
	ldrb	lr, [ip, #11]	@ zero_extendqisi2
	strb	lr, [r5, #1856]
	ldrb	ip, [ip, #10]	@ zero_extendqisi2
	strb	ip, [r5, #1857]
	ldr	ip, [r3, #164]
	str	ip, [r5, #1860]
	ldr	ip, [r3, #168]
	str	ip, [r5, #1864]
	ldr	ip, [r3, #156]
	str	ip, [r5, #1868]
	ldr	ip, [r3, #160]
	str	ip, [r5, #1872]
	ldr	ip, [r3, #148]
	str	ip, [r5, #1876]
	ldr	ip, [r3, #152]
	str	ip, [r5, #1880]
	ldr	lr, [r3, #172]
	ldr	ip, [r6, #52]
	str	lr, [r5, #1884]
	ldr	lr, [r3, #124]
	str	lr, [r5, #1888]
	ldr	lr, [r3, #128]
	str	lr, [r5, #1892]
	ldr	lr, [r3, #100]
	str	lr, [r5, #1896]
	ldr	lr, [r3, #92]
	str	lr, [r5, #1900]
	ldr	lr, [r3, #112]
	str	lr, [r5, #1904]
	ldr	lr, [r3, #108]
	str	lr, [r5, #1908]
	ldr	lr, [r3, #96]
	str	lr, [r5, #1912]
	ldr	r3, [r3, #88]
	str	r3, [r5, #1916]
	blx	ip
	ldr	ip, [r4, #2388]
	add	r2, r4, #8128
	add	r1, r4, #7616
	add	r3, r8, #52
	add	r2, r2, #36
	ldr	lr, [ip, #68]
	add	r1, r1, #36
	mov	r0, r4
	str	lr, [r5, #2008]
	ldr	ip, [ip, #64]
	str	ip, [r5, #2012]
	bl	HEVC_CalcTileInfo
	subs	r6, r0, #0
	bne	.L548
	ldr	r3, [r4, #2392]
	ldrb	r2, [r3, #16]	@ zero_extendqisi2
	strb	r2, [r5, #2036]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	strb	r2, [r5, #2037]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	strb	r2, [r5, #2038]
	ldrb	r2, [r3, #14]	@ zero_extendqisi2
	strb	r2, [r5, #2039]
	ldrb	r2, [r3, #15]	@ zero_extendqisi2
	strb	r2, [r5, #2040]
	ldrb	r2, [r3, #13]	@ zero_extendqisi2
	strb	r2, [r5, #2041]
	ldr	r2, [r4, #2388]
	ldr	r1, [r3, #56]
	ldr	r2, [r2, #128]
	rsb	r2, r1, r2
	str	r2, [r5, #2044]
	ldr	r2, [r3, #52]
	str	r2, [r5, #2048]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	strb	r2, [r5, #2052]
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	strb	r2, [r5, #2053]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	strb	r2, [r5, #2054]
	ldr	r2, [r3, #60]
	str	r2, [r5, #2056]
	ldr	r2, [r3, #64]
	str	r2, [r5, #2060]
	ldr	r2, [r3, #72]
	sub	r2, r2, #1
	str	r2, [r5, #2064]
	ldr	r2, [r3, #68]
	sub	r2, r2, #1
	str	r2, [r5, #2068]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	strb	r2, [r5, #1857]
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	strb	r3, [r5, #1856]
	ldr	r3, [r4, #2332]
	str	r6, [r4, #2348]
	cmp	r3, #1
	beq	.L539
	ldr	r3, [r4, #3564]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	subs	r9, r0, #0
	beq	.L549
	ldr	r2, [r9, #28]
	ldr	r3, [r9, #32]
	cmp	r2, #0
	beq	.L532
	cmp	r3, #0
	beq	.L532
	add	r3, r4, #7488
	add	r2, r4, #7232
	add	r1, r4, #7360
	add	r3, r3, #36
	add	r2, r2, #24
	add	r1, r1, #24
	ldr	r0, [r4, #252]
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r9, #28]
	add	r2, r4, #7360
	add	r1, r4, #7488
	add	r2, r2, #28
	add	r1, r1, #28
	ldr	r3, [r3, #4]
	str	r3, [r5, #3104]
	ldr	r0, [r4, #252]
	bl	FSP_GetPmvAddrTab
	ldr	r1, [r4, #3540]
	add	r2, r4, r7
	movw	r3, #12520
	str	r1, [r5, #3108]
	ldr	r1, [r9, #12]
	str	r1, [r5, #3424]
	ldr	r1, [r9, #32]
	ldr	r1, [r1, #8]
	str	r1, [r8, #408]
	ldr	r1, [r9, #32]
	ldr	r1, [r1, #60]
	str	r1, [r8, #412]
	ldr	ip, [r2, r3]
	cmp	ip, #0
	str	ip, [r8, #204]
	beq	.L534
	add	r3, r7, #12544
	add	r2, r4, #8320
	add	r3, r3, #44
	add	r2, r2, #8
	add	r3, r4, r3
	mov	r0, r6
.L535:
	add	r0, r0, #1
	ldr	r1, [r3, #4]!
	cmp	r0, ip
	str	r1, [r2, #4]!
	bne	.L535
.L534:
	add	r7, r4, #6144
	mov	r6, #0
	add	r7, r7, #28
.L536:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r4
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_8x8
	cmp	r6, #4
	add	r7, r7, #64
	bne	.L536
	add	r2, r4, #6400
	mov	r0, r6
	add	r2, r2, #28
	mov	r1, r4
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r4, #6464
	add	r2, r2, #28
	mov	r1, r4
	mov	r0, #5
	add	r7, r4, #6656
	bl	HEVC_WriteQmatrix_8x8
	add	r2, r4, #6528
	add	r2, r2, #28
	mov	r1, r4
	mov	r0, #0
	add	r7, r7, #28
	bl	HEVC_WriteQmatrix_16x16
	add	r2, r4, #6592
	add	r2, r2, #28
	mov	r1, r4
	mov	r0, #1
	mov	r6, #2
	bl	HEVC_WriteQmatrix_16x16
.L537:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r4
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_16x16
	cmp	r6, #6
	add	r7, r7, #64
	bne	.L537
	add	r2, r4, #6912
	mov	r1, r4
	add	r2, r2, #28
	mov	r0, #0
	bl	HEVC_WriteQmatrix_32x32
	add	r2, r4, #6976
	add	r2, r2, #28
	mov	r1, r4
	mov	r0, #1
	add	r7, r4, #7040
	bl	HEVC_WriteQmatrix_32x32
	add	r7, r7, #28
	mov	r6, #0
.L538:
	mov	r2, r7
	mov	r0, r6
	mov	r1, r4
	add	r6, r6, #1
	bl	HEVC_WriteQmatrix_4x4
	cmp	r6, #6
	add	r7, r7, #16
	bne	.L538
	ldr	r1, [r4, #2284]
	mov	r0, #0
	ldr	r3, [r4, #2288]
	ldr	r2, [r4, #2276]
	ldr	ip, [r4, #2280]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r5, #3068]
	ldr	r1, [r4, #2300]
	ldr	r3, [r4, #2304]
	ldr	r2, [r4, #2292]
	ldr	ip, [r4, #2296]
	mov	r1, r1, asl #16
	orr	r3, r1, r3, asl #24
	orr	r3, r3, r2
	orr	r3, r3, ip, asl #8
	str	r3, [r5, #3072]
	ldr	r3, [r4, #3540]
	str	r3, [r5, #3100]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L539:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L548:
	ldr	r2, .L550+12
	mov	r0, #1
	ldr	r1, .L550+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L532:
	ldr	r1, .L550+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L549:
	ldr	r3, [r4, #3564]
	mov	r0, #1
	ldr	r1, .L550+24
	ldr	r2, [r3, #28]
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L551:
	.align	2
.L550:
	.word	.LC59
	.word	.LC60
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+228
	.word	.LC61
	.word	.LC63
	.word	.LC62
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
	ldrb	r3, [r3, #105]	@ zero_extendqisi2
	cmp	r3, #0
	addeq	r3, r0, #4160
	addeq	r3, r3, #40
	beq	.L554
	ldrsb	r3, [r0, #11]
	cmp	r3, #0
	addne	r3, r0, #11136
	addne	r3, r3, #28
	beq	.L587
.L554:
	ldr	ip, [r3, #68]
	ldr	lr, [r3, #72]
	cmp	ip, #16
	bhi	.L588
	cmp	lr, #16
	bhi	.L558
	cmp	ip, #0
	beq	.L559
	ldr	r3, [r0, #2416]
	cmp	r3, #0
	beq	.L572
	ldr	r3, [r3, #16]
	cmp	r3, #0
	addne	r1, r0, #2416
	movne	r2, #0
	bne	.L564
	b	.L589
.L565:
	ldr	r3, [r1, #4]!
	cmp	r3, #0
	beq	.L560
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L561
.L564:
	add	r2, r2, #1
	cmp	r2, ip
	bne	.L565
.L559:
	cmp	lr, #0
	beq	.L584
	ldr	r3, [r0, #2484]
	cmp	r3, #0
	beq	.L575
	ldr	r3, [r3, #16]
	cmp	r3, #0
	addne	r0, r0, #2480
	movne	r2, #0
	addne	r0, r0, #4
	bne	.L570
	b	.L590
.L571:
	ldr	r3, [r0, #4]!
	cmp	r3, #0
	beq	.L566
	ldr	r3, [r3, #16]
	cmp	r3, #0
	beq	.L567
.L570:
	add	r2, r2, #1
	cmp	r2, lr
	bne	.L571
.L584:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L572:
	mov	r2, r3
.L560:
	ldr	r1, .L591
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L589:
	mov	r2, r3
.L561:
	ldr	r1, .L591+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L575:
	mov	r2, r3
.L566:
	ldr	r1, .L591+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L590:
	mov	r2, r3
.L567:
	ldr	r1, .L591+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L587:
	mov	r0, r3
	ldr	r2, .L591+16
	ldr	r1, .L591+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L558:
	mov	r2, lr
	mov	r3, #17
	ldr	r1, .L591+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L588:
	mov	r2, ip
	mov	r3, #17
	ldr	r1, .L591+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L592:
	.align	2
.L591:
	.word	.LC67
	.word	.LC68
	.word	.LC69
	.word	.LC70
	.word	.LANCHOR0+248
	.word	.LC64
	.word	.LC66
	.word	.LC65
	UNWIND(.fnend)
	.size	HEVC_CheckListX, .-HEVC_CheckListX
	.align	2
	.global	HEVC_WriteSliceMsg
	.type	HEVC_WriteSliceMsg, %function
HEVC_WriteSliceMsg:
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
	ldr	r3, [r0, #3512]
	mov	r4, r0
	str	r3, [fp, #-116]
	bl	HEVC_CheckListX
	subs	r3, r0, #0
	str	r3, [fp, #-112]
	bne	.L634
	ldr	r0, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r0, r3
	bcs	.L667
	ldr	r6, [r4, #2408]
	mov	r5, #1360
	ldr	r7, [fp, #-112]
	mov	r2, r5
	ldr	r8, .L671
	mla	r6, r5, r0, r6
	mov	r1, r7
	ldr	r3, [r8, #48]
	mov	r0, r6
	blx	r3
	mov	r1, r7
	ldr	r3, [r8, #48]
	mov	r2, #64
	sub	r0, fp, #108
	add	r7, r4, #4096
	blx	r3
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	add	r3, r3, #1
	str	r3, [r4, #204]
	cmp	r3, r2
	ldrcc	r2, [r4, #2408]
	ldrcs	r3, [fp, #-112]
	mlacc	r3, r5, r3, r2
	str	r3, [r6, #1356]
	ldr	r1, [r7, #140]
	ldr	r2, [r4, #2376]
	ldr	r0, [r4, #176]
	ldr	r3, [r4, #236]
	add	r0, r0, #1
	str	r1, [r4, #208]
	str	r0, [r4, #176]
	add	r3, r3, #1
	str	r3, [r4, #236]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #8]
	str	r0, [fp, #-120]
	cmp	r1, #1
	cmpls	r1, r3
	bcs	.L598
	add	r0, r6, r1, lsl #2
.L599:
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r1, r1, #1
	add	r2, r2, r3
	ldr	r2, [r2, #56]
	str	r2, [r0, #8]
	ldr	r2, [r4, #2376]
	add	r2, r2, r3
	ldr	r2, [r2, #52]
	str	r2, [r0], #4
	ldr	r2, [r4, #2376]
	add	r3, r2, r3
	ldr	r3, [r3, #60]
	str	r3, [r0, #12]
	ldr	r2, [r4, #2376]
	ldr	r3, [r2, #8]
	cmp	r3, r1
	movhi	ip, #1
	movls	ip, #0
	cmp	r1, #1
	movhi	ip, #0
	cmp	ip, #0
	bne	.L599
.L598:
	cmp	r3, #1
	addls	r3, r6, r3, lsl #2
	addls	r1, r6, #8
	movls	r2, #0
	bhi	.L604
.L603:
	str	r2, [r3, #8]
	str	r2, [r3], #4
	cmp	r3, r1
	str	r2, [r3, #12]
	bne	.L603
.L604:
	ldrb	r3, [r7, #105]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L668
.L602:
	add	r5, r4, #8192
	ldr	r3, [r5, #3040]
	cmp	r3, #0
	beq	.L605
	add	r0, r4, #2416
	add	r9, r6, #112
	add	lr, r6, #368
	mov	r1, #0
.L606:
	ldr	r3, [r0]
	sub	r10, fp, #44
	add	r1, r1, #1
	ldr	r3, [r3, #4]
	str	r3, [r9, #4]!
	ldr	r2, [r0], #4
	ldr	ip, [r2, #16]
	ldr	r3, [ip, #20]
	ldr	ip, [ip, #24]
	add	r3, r3, #1840
	add	r3, r3, #6
	add	ip, r10, ip, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [ip, #-64]
	ldr	r3, [r2, #16]
	ldr	r3, [r3, #24]
	str	r3, [lr, #4]!
	ldr	r2, [r5, #3040]
	cmp	r2, r1
	bhi	.L606
	ldr	r0, [r5, #3044]
	cmp	r0, #0
	beq	.L607
.L633:
	add	r1, r4, #2480
	add	r10, r6, #176
	add	r1, r1, #4
	add	r9, r6, #432
	mov	lr, #0
.L608:
	ldr	r3, [r1]
	sub	ip, fp, #44
	add	lr, lr, #1
	ldr	r3, [r3, #4]
	str	r3, [r10, #4]!
	ldr	r2, [r1], #4
	ldr	r0, [r2, #16]
	ldr	r3, [r0, #20]
	ldr	r0, [r0, #24]
	add	r3, r3, #1840
	add	r3, r3, #6
	add	r0, ip, r0, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [r0, #-64]
	ldr	r3, [r2, #16]
	ldr	r3, [r3, #24]
	str	r3, [r9, #4]!
	ldr	r0, [r5, #3044]
	cmp	r0, lr
	bhi	.L608
	ldr	r2, [r5, #3040]
.L607:
	cmp	r2, #0
	beq	.L609
	ldr	r1, [fp, #-116]
	mov	r9, #50
	ldr	r3, [r6, #372]
	ldr	r10, [r4, #3516]
	mul	r9, r9, r1
	add	r3, r9, r3
	add	r3, r3, #3152
	add	r3, r3, #12
	ldr	r3, [r4, r3, asl #2]
	cmp	r10, r3
	blt	.L640
	add	lr, r6, #372
	mov	r1, #0
	b	.L611
.L612:
	ldr	r3, [lr, #4]!
	add	r3, r9, r3
	add	r3, r3, #3152
	add	r3, r3, #12
	ldr	r3, [r4, r3, asl #2]
	cmp	r3, r10
	bgt	.L640
.L611:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L612
.L609:
	ldr	r2, [r5, #2992]
	cmp	r2, #0
	bne	.L665
	cmp	r0, #0
	beq	.L665
	ldr	r1, [fp, #-116]
	mov	lr, #50
	ldr	r3, [r6, #436]
	ldr	r9, [r4, #3516]
	mul	lr, lr, r1
	add	r3, lr, r3
	add	r3, r3, #3152
	add	r3, r3, #12
	ldr	r3, [r4, r3, asl #2]
	cmp	r9, r3
	blt	.L610
	add	r1, r6, #436
	b	.L613
.L614:
	ldr	r3, [r1, #4]!
	add	r3, lr, r3
	add	r3, r3, #3152
	add	r3, r3, #12
	ldr	r3, [r4, r3, asl #2]
	cmp	r3, r9
	bgt	.L640
.L613:
	add	r2, r2, #1
	cmp	r2, r0
	bne	.L614
.L665:
	mov	r2, #1
.L610:
	strb	r2, [r6, #24]
	ldrb	r3, [r7, #105]	@ zero_extendqisi2
	strb	r3, [r6, #25]
	ldr	r3, [r5, #2988]
	str	r3, [r6, #28]
	ldrb	r2, [r5, #2979]	@ zero_extendqisi2
	strb	r2, [r6, #32]
	ldr	r2, [r5, #3012]
	str	r2, [r6, #36]
	ldr	r2, [r4, #2332]
	cmp	r2, #0
	bne	.L615
	ldr	r9, [r4, #3564]
	ldr	r1, [r4, #204]
	ldr	r0, [r9, #316]
	sub	r2, r1, #1
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	str	r0, [r9, #68]
.L615:
	ldr	r3, [r5, #2992]
	cmp	r3, #0
	bne	.L616
	ldrb	r3, [r5, #2980]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L617
	ldr	r3, [r5, #3016]
	add	r3, r6, r3, lsl #2
	ldr	r9, [r3, #436]
.L618:
	str	r9, [r6, #40]
	ldr	r3, [r5, #3016]
	str	r3, [r6, #48]
	ldrb	r3, [r5, #2980]	@ zero_extendqisi2
	strb	r3, [r6, #52]
	ldr	r3, [r5, #3020]
	str	r3, [r6, #44]
	ldr	r3, [r5, #3048]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #60]
	ldr	r3, [r5, #3052]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #56]
	ldrb	r3, [r5, #2976]	@ zero_extendqisi2
	strb	r3, [r6, #64]
	ldrb	r3, [r5, #2978]	@ zero_extendqisi2
	strb	r3, [r6, #65]
	ldr	r3, [r5, #3040]
	str	r3, [r6, #68]
	ldr	r3, [r5, #3044]
	str	r3, [r6, #72]
	ldr	r3, [r5, #2992]
	str	r3, [r6, #76]
	ldr	r3, [r7, #144]
	str	r3, [r6, #80]
	ldr	r3, [r4, #2388]
	ldr	r0, [r7, #144]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidivmod
	str	r1, [r6, #84]
	ldr	r3, [r4, #2388]
	ldr	r0, [r7, #144]
	ldr	r1, [r3, #188]
	bl	__aeabi_uidiv
	str	r0, [r6, #88]
	mov	r0, r4
	ldr	r1, [r7, #144]
	bl	HEVC_CtbRsAddrToTsAddr
	str	r0, [r6, #92]
	ldr	r3, [r5, #3024]
	str	r3, [r6, #96]
	ldr	r3, [r5, #3028]
	str	r3, [r6, #100]
	ldr	r3, [r5, #3036]
	str	r3, [r6, #104]
	ldr	r3, [r5, #3032]
	str	r3, [r6, #108]
	ldrb	r3, [r5, #2975]	@ zero_extendqisi2
	strb	r3, [r6, #112]
	ldrb	r3, [r5, #2974]	@ zero_extendqisi2
	strb	r3, [r6, #113]
	ldrb	r3, [r5, #2981]	@ zero_extendqisi2
	strb	r3, [r6, #114]
	ldrb	r3, [r5, #2982]	@ zero_extendqisi2
	strb	r3, [r6, #115]
	ldr	r3, [r4, #2392]
	ldrb	r2, [r3, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L623
	ldr	r2, [r5, #2992]
	cmp	r2, #1
	beq	.L624
.L623:
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L669
.L626:
	ldrb	r3, [r5, #2976]	@ zero_extendqisi2
	cmp	r3, #0
	subne	r3, fp, #44
	addne	r9, r3, r9, lsl #2
	ldreq	r3, [r7, #3292]
	ldrne	r3, [r9, #-64]
	str	r3, [r6, #564]
	ldr	r3, [r4, #2332]
	cmp	r3, #0
	ldreq	r1, [r4, #2376]
	ldreq	r2, [r4, #2396]
	ldreq	r0, [fp, #-120]
	streq	r1, [r2, r0, asl #2]
	streq	r3, [r4, #2376]
	ldrb	r3, [r7, #2041]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L648
	ldr	r3, [r4, #236]
	cmp	r3, #1
	beq	.L670
	add	r1, r4, r3, lsl #3
	ldr	r0, [r6, #92]
	add	r1, r1, #9472
	add	r2, r3, #1184
	add	r2, r2, #1
	sub	r0, r0, #1
	str	r0, [r1, #8]
	sub	r3, r3, #1
	ldr	r1, [r6, #92]
	add	r2, r4, r2, lsl #3
	str	r1, [r2, #4]
.L632:
	ldr	r1, [r7, #1840]
	add	r3, r4, r3, lsl #3
	ldr	r2, [r7, #1836]
	add	r3, r3, #9472
	mla	r2, r1, r2, r2
	add	r2, r2, r1
	str	r2, [r3, #24]
	ldr	r1, [r6, #92]
	sub	r1, r1, #1
	cmp	r1, #36864
	bcs	.L648
	mov	r0, r4
	bl	HEVC_CtbTsAddrToRsAddr
	str	r0, [r6, #568]
.L648:
	ldr	r0, [fp, #-112]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L640:
	mov	r2, #0
	b	.L610
.L616:
	cmp	r3, #1
	movne	r9, #0
	bne	.L618
.L617:
	ldr	r3, [r5, #3016]
	add	r3, r6, r3, lsl #2
	ldr	r9, [r3, #372]
	b	.L618
.L668:
	add	r1, r4, #4160
	add	r0, r4, #11136
	ldr	r3, [r8, #52]
	add	r1, r1, #40
	add	r0, r0, #28
	movw	r2, #1356
	blx	r3
	mov	r3, #1
	strb	r3, [r4, #11]
	b	.L602
.L669:
	ldr	r3, [r5, #2992]
	cmp	r3, #0
	bne	.L626
.L624:
	ldr	lr, [r5, #3128]
	mov	r2, #64
	ldr	r3, [r8, #52]
	add	r1, r4, #11456
	add	r0, r6, #588
	ldr	r10, .L671
	str	lr, [r6, #580]
	ldr	lr, [r5, #3260]
	str	lr, [r6, #584]
	blx	r3
	add	r1, r4, #11264
	add	r1, r1, #60
	ldr	r3, [r8, #52]
	mov	r2, #64
	add	r0, r6, #716
	blx	r3
	ldr	r3, [r8, #52]
	mov	r2, #128
	add	r1, r4, #11520
	add	r0, r6, #844
	blx	r3
	add	r0, r6, #1088
	ldr	r3, [r8, #52]
	add	r0, r0, #12
	mov	r2, #128
	add	r1, r4, #11648
	blx	r3
	ldr	r3, [r5, #2992]
	cmp	r3, #0
	bne	.L626
	ldr	r3, [r10, #52]
	add	r1, r4, #11776
	mov	r2, #64
	add	r0, r6, #652
	blx	r3
	add	r1, r4, #11328
	ldr	r3, [r10, #52]
	add	r1, r1, #60
	mov	r2, #64
	add	r0, r6, #780
	blx	r3
	ldr	r3, [r10, #52]
	add	r1, r4, #11840
	mov	r2, #128
	add	r0, r6, #972
	blx	r3
	add	r0, r6, #1216
	ldr	r3, [r10, #52]
	mov	r2, #128
	add	r1, r4, #11968
	add	r0, r0, #12
	blx	r3
	b	.L626
.L670:
	ldr	r2, [r6, #92]
	mov	r3, #0
	str	r2, [r5, #1300]
	b	.L632
.L605:
	ldr	r3, [r5, #3044]
	cmp	r3, #0
	bne	.L633
	b	.L665
.L634:
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L648
.L667:
	mov	r2, r0
	ldr	r1, .L671+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
	str	r3, [fp, #-112]
	b	.L648
.L672:
	.align	2
.L671:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC71
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
	ldr	r2, [r0, #3532]
	add	r1, r0, #4096
	mov	r3, r0
	add	ip, r0, #8192
	clz	r2, r2
	mov	r0, #0
	mov	r2, r2, lsr #5
	str	r2, [r1, #3156]
	ldr	r2, [r3, #3536]
	str	r2, [r1, #3148]
	ldr	r3, [r3, #204]
	str	r3, [ip, #208]
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
	add	ip, r0, #4096
	mov	r6, r0
	ldr	r2, [r0, #164]
	ldr	r3, [ip, #140]
	cmp	r3, #0
	blt	.L678
	cmp	r3, r2
	bge	.L678
	ldr	r2, [r0, #2368]
	mov	r1, #1888
	mla	r3, r1, r3, r2
	ldr	r2, [r0, #160]
	ldr	r3, [r3, #32]
	cmp	r3, #0
	blt	.L682
	cmp	r3, r2
	bge	.L682
	ldr	r2, [r0, #2364]
	movw	r1, #12660
	ldr	r0, [ip, #1036]
	mov	r10, #1
	ldr	lr, [ip, #1040]
	mla	r1, r1, r3, r2
	ldr	r3, [ip, #1044]
	add	r2, lr, r0
	str	r0, [fp, #-56]
	cmp	r2, r3
	str	lr, [fp, #-60]
	mov	r4, r2
	ldr	r1, [r1, #116]
	mov	r10, r10, asl r1
	bcs	.L693
	cmp	r2, #15
	bgt	.L685
	ldr	r9, [r6, #3516]
	add	r5, r2, #1296
	add	r5, r5, #11
	str	r6, [fp, #-48]
	str	r2, [fp, #-64]
	add	r5, r6, r5, lsl #2
	mov	r8, r9
	mov	r6, r3
	str	ip, [fp, #-52]
	b	.L687
.L705:
	cmp	r6, r4
	bls	.L703
	cmp	r4, #16
	beq	.L704
.L687:
	ldr	r7, [r5, #4]!
	mov	r1, r10
	mov	r0, r8
	mov	r9, r8
	ldr	lr, [r5, #-944]
	cmp	lr, #0
	bne	.L688
	bl	__aeabi_idivmod
	mov	r0, r7
	mov	r9, r1
	mov	r1, r10
	bl	__aeabi_idivmod
	mov	r7, r1
.L688:
	cmp	r9, r7
	add	r4, r4, #1
	bne	.L705
	ldr	r2, [fp, #-64]
	mov	r4, #1
	ldr	r6, [fp, #-48]
	ldr	ip, [fp, #-52]
.L684:
	cmp	r2, #0
	beq	.L680
	ldr	lr, [ip, #116]
	ldr	r3, [ip, #1068]
	ldr	r0, [r6, #3516]
	add	r3, lr, r3
	cmp	r0, r3
	beq	.L697
	add	r6, r6, #5120
	mov	r1, #0
	add	r6, r6, #44
	b	.L690
.L691:
	ldr	r3, [r6, #4]!
	add	r3, lr, r3
	cmp	r3, r0
	beq	.L697
.L690:
	add	r1, r1, #1
	cmp	r1, r2
	beq	.L680
	cmp	r1, #17
	bne	.L691
	ldr	r3, [fp, #-60]
	mov	r0, #0
	ldr	r2, [fp, #-56]
	str	r1, [sp]
	str	r3, [sp, #8]
	mov	r3, r1
	str	r2, [sp, #4]
	movw	r2, #8976
	ldr	r1, .L706
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L682:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8927
	ldr	r1, .L706+4
	mov	r4, r0
	bl	dprint_vfmw
.L680:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L678:
	str	r2, [sp]
	mov	r0, #0
	movw	r2, #8915
	ldr	r1, .L706+8
	mov	r4, r0
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L704:
	mov	r3, r6
	ldr	ip, [fp, #-52]
	ldr	r6, [fp, #-48]
.L685:
	str	r3, [sp, #4]
	mov	r1, #16
	mov	r3, r4
	movw	r2, #8947
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L706+12
	mov	r4, r0
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	ip, [fp, #-48]
	ldr	r3, [ip, #1036]
	ldr	r2, [ip, #1040]
	str	r3, [fp, #-56]
	str	r2, [fp, #-60]
	add	r2, r2, r3
	b	.L684
.L703:
	ldr	r2, [fp, #-64]
	mov	r4, #0
	ldr	r6, [fp, #-48]
	ldr	ip, [fp, #-52]
	b	.L684
.L697:
	mov	r4, #1
	b	.L680
.L693:
	mov	r4, #0
	b	.L684
.L707:
	.align	2
.L706:
	.word	.LC75
	.word	.LC73
	.word	.LC72
	.word	.LC74
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
	ldr	r2, [r0, #2384]
	ldr	r3, [r1, #4]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	beq	.L711
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L711:
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
	ldr	ip, [r0, #156]
	mov	r4, r0
	ldr	lr, .L713
	mov	r2, #132
	ldr	r0, [r0, #2360]
	mov	r3, ip, asl #7
	add	r3, r3, ip, lsl #2
	ldr	ip, [lr, #52]
	sub	r3, r3, #132
	add	r0, r0, r3
	blx	ip
	ldr	r3, [r4, #156]
	ldr	r1, [r4, #2360]
	mov	r2, r3, asl #7
	add	r3, r2, r3, lsl #2
	sub	r3, r3, #132
	add	r3, r1, r3
	str	r3, [r4, #2384]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L714:
	.align	2
.L713:
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
	ldr	r2, [r0, #2388]
	ldr	r3, [r1, #56]
	ldr	r2, [r2, #56]
	cmp	r2, r3
	beq	.L718
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L718:
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
	movw	r5, #12660
	ldr	ip, .L720
	mov	r4, r0
	ldr	r0, [r0, #2364]
	mov	r2, r5
	mul	r3, r5, r3
	ldr	ip, [ip, #52]
	sub	r3, r3, #12608
	sub	r3, r3, #52
	add	r0, r0, r3
	blx	ip
	ldr	r2, [r4, #160]
	ldr	r3, [r4, #2364]
	mul	r5, r5, r2
	sub	r5, r5, #12608
	sub	r5, r5, #52
	add	r5, r3, r5
	str	r5, [r4, #2388]
	ldr	r3, [r5, #56]
	str	r3, [r4, #264]
	ldr	r3, [r5, #64]
	str	r3, [r4, #268]
	ldr	r3, [r5, #68]
	str	r3, [r4, #272]
	ldr	r3, [r5, #128]
	str	r3, [r4, #276]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L721:
	.align	2
.L720:
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
	ldr	r2, [r0, #2392]
	ldr	r3, [r1, #28]
	ldr	r2, [r2, #28]
	cmp	r2, r3
	beq	.L725
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L725:
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
	beq	.L727
	ldrb	r3, [r2, #15]	@ zero_extendqisi2
	cmp	r3, r4
	bne	.L745
	ldr	lr, [r2, #68]
	ldr	r3, [r1, #188]
	cmp	lr, #1
	add	r0, r2, lr, lsl #1
	strh	r3, [r0, #170]	@ movhi
	ble	.L739
	add	lr, lr, #42
	add	r2, r2, #86
	add	ip, r5, #170
	add	lr, r5, lr, lsl #1
.L738:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #170]
	rsb	r3, r1, r3
	strh	r3, [r0, #170]	@ movhi
	bne	.L738
.L739:
	ldr	lr, [r5, #72]
	ldr	r3, [r7, #192]
	cmp	lr, #1
	add	r0, r5, lr, lsl #1
	strh	r3, [r0, #210]	@ movhi
	ble	.L734
	add	lr, lr, #62
	add	r2, r5, #126
	add	ip, r5, #210
	add	lr, r5, lr, lsl #1
.L740:
	ldrh	r1, [r2, #2]!
	cmp	r2, lr
	strh	r1, [ip, #2]!	@ movhi
	ldrh	r3, [r0, #210]
	rsb	r3, r1, r3
	strh	r3, [r0, #210]	@ movhi
	bne	.L740
	b	.L734
.L727:
	ldr	r3, [r1, #188]
	strh	r3, [r2, #172]	@ movhi
	ldr	r3, [r1, #192]
	strh	r3, [r2, #212]	@ movhi
.L734:
	ldr	r3, [r6, #164]
	mov	r4, #1888
	ldr	ip, .L746
	mov	r2, r4
	ldr	r0, [r6, #2368]
	mov	r1, r5
	mul	r3, r4, r3
	ldr	ip, [ip, #52]
	sub	r3, r3, #1888
	add	r0, r0, r3
	blx	ip
	ldr	r2, [r6, #164]
	ldr	r3, [r6, #2368]
	mul	r4, r4, r2
	sub	r4, r4, #1888
	add	r4, r3, r4
	str	r4, [r6, #2392]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L745:
	ldr	r9, [r2, #68]
	cmp	r9, r4
	addgt	r3, r2, #170
	ble	.L733
.L732:
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
	bne	.L732
.L733:
	ldr	r9, [r5, #72]
	cmp	r9, #0
	addgt	r3, r5, #210
	movgt	r4, #0
	ble	.L734
.L735:
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
	bne	.L735
	b	.L734
.L747:
	.align	2
.L746:
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r5, r0, #4096
	mov	r3, #1
	strb	r3, [r0, #3505]
	mov	r4, r0
	ldr	r3, [r5, #132]
	mvn	r2, #0
	ldr	ip, [r0, #2388]
	mov	r1, #0
	ldr	r0, [r0, #252]
	str	r3, [r4, #3508]
	ldr	lr, [r5, #116]
	ldr	r3, .L762
	str	r2, [r4, #3536]
	str	lr, [r4, #3516]
	ldr	r2, [ip, #64]
	ldr	r3, [r3, r0, asl #2]
	str	r2, [r4, #3524]
	ldr	r2, [ip, #68]
	str	r1, [r4, #3532]
	str	r2, [r4, #3528]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L761
.L749:
	ldr	r3, [r4, #2332]
	cmp	r3, #0
	bne	.L752
	ldr	ip, [r4, #2404]
	add	lr, r4, #4160
	mvn	r2, #0
	mvn	r3, #0
	ldrd	r0, [ip, #56]
	strd	r0, [lr, #-8]
	ldrd	r0, [ip, #72]
	strd	r0, [lr]
	ldrd	r0, [ip, #88]
	strd	r0, [lr, #8]
	ldr	r1, [ip, #104]
	str	r1, [r4, #3568]
	ldr	r1, [ip, #108]
	str	r1, [r4, #3572]
	ldr	r1, [ip, #112]
	str	r1, [r4, #3576]
	ldr	r1, [ip, #128]
	str	r1, [r4, #3580]
	strd	r2, [ip, #56]
	ldr	ip, [r4, #2388]
.L752:
	ldr	r2, [ip, #64]
	mov	r6, #0
	ldrb	r3, [r4, #3632]	@ zero_extendqisi2
	add	r0, r4, #3568
	str	r2, [r4, #3636]
	ldr	r2, [ip, #68]
	str	r6, [r4, #3620]
	str	r2, [r4, #3640]
	ldr	r2, [ip, #60]
	ldr	r1, [ip, #2084]
	subs	r2, r2, #1
	bfi	r3, r1, #5, #3
	movne	r2, #1
	bfi	r3, r2, #2, #3
	strb	r3, [r4, #3632]
	ldr	r1, [ip, #2068]
	and	r1, r1, #7
	bl	SetAspectRatio
	ldr	r3, [r4, #2332]
	cmp	r3, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r2, [r5, #116]
	ldr	r3, [r4, #3564]
	str	r2, [r3, #8]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3632]
	str	r2, [r3, #144]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3620]
	str	r2, [r3, #132]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3672]
	str	r2, [r3, #184]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3668]
	str	r2, [r3, #180]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3636]
	str	r2, [r3, #148]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3640]
	str	r2, [r3, #152]
	ldr	r3, [r4, #3564]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L754
	ldr	r3, [r4, #3620]
	mov	r1, r6
	ldr	r2, [r0, #4]
	subs	r3, r3, r6
	ldr	r0, [r4, #252]
	movne	r3, #1
	bl	FSP_SetStoreType
.L754:
	ldr	r3, [r4, #2388]
	mov	r6, #0
	ldr	ip, [r4, #3564]
	ldr	r2, [r3, #72]
	str	r2, [r4, #3788]
	ldr	r5, [r3, #76]
	str	r5, [r4, #3792]
	ldr	r1, [r3, #80]
	str	r1, [r4, #3796]
	ldr	lr, [r3, #84]
	str	lr, [r4, #3800]
	ldr	r0, [r3, #64]
	rsb	r2, r2, r0
	rsb	r2, r5, r2
	str	r2, [r4, #3644]
	ldr	r0, [r3, #68]
	rsb	r1, r1, r0
	rsb	r1, lr, r1
	str	r1, [r4, #3648]
	ldr	r1, [r3, #60]
	str	r1, [r4, #3732]
	ldr	r1, [r3, #88]
	str	r1, [r4, #3736]
	ldr	r3, [r3, #96]
	str	r3, [r4, #3740]
	ldr	r3, [ip, #164]
	str	r3, [r4, #3652]
	ldr	r3, [ip, #168]
	str	r3, [r4, #3656]
	str	r2, [ip, #156]
	ldr	r2, [r4, #3648]
	ldr	r3, [r4, #3564]
	str	r2, [r3, #160]
	ldr	r2, [r4, #3652]
	ldr	r3, [r4, #3564]
	str	r2, [r3, #164]
	ldr	r2, [r4, #3656]
	ldr	r3, [r4, #3564]
	str	r2, [r3, #168]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3736]
	str	r2, [r3, #248]
	ldr	r3, [r4, #3564]
	ldr	r2, [r4, #3740]
	str	r2, [r3, #252]
	str	r6, [r4, #3520]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L761:
	ldr	r2, [r3, #156]
	cmp	r2, r1
	bne	.L749
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L749
	add	r3, r4, #8192
	ldrb	r3, [r3, #2912]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L749
	add	r8, r4, #11136
	movw	r3, #11152
	ldrd	r2, [r3, r4]
	ldrd	r0, [r8]
	cmp	r1, r3
	cmpeq	r0, r2
	bls	.L750
	subs	r6, r0, r2
	sbc	r7, r1, r3
	cmp	r7, #0
	cmpeq	r6, #16
	bls	.L750
.L751:
	ldr	r1, [r4, #260]
	rsb	lr, r1, lr
	adds	r2, r2, lr
	adc	r3, r3, lr, asr #31
	strd	r2, [r8]
	b	.L749
.L750:
	cmp	r1, r3
	cmpeq	r0, r2
	bcs	.L749
	subs	r0, r2, r0
	sbc	r1, r3, r1
	cmp	r1, #0
	cmpeq	r0, #16
	bls	.L749
	b	.L751
.L763:
	.align	2
.L762:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	HEVC_InitPicInfo, .-HEVC_InitPicInfo
	.align	2
	.global	HEVC_RepairList
	.type	HEVC_RepairList, %function
HEVC_RepairList:
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
	add	r3, r0, #4096
	mov	ip, r0
	ldr	r3, [r3, #124]
	cmp	r3, #1
	beq	.L781
	cmp	r3, #2
	beq	.L782
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [fp, #-48]
	beq	.L766
	ldr	r2, .L791
	mov	r0, #1
	ldr	r1, .L791+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L781:
	str	r3, [fp, #-48]
.L766:
	add	r8, ip, #4224
	add	r9, ip, #2416
	add	r8, r8, #40
	mov	r10, #0
.L779:
	ldr	r1, [r8, #4]!
	cmp	r1, #0
	beq	.L769
	ldr	r3, [r9]
	cmp	r3, #0
	bne	.L783
	mov	r2, r9
	mov	r4, r3
	b	.L771
.L773:
	ldr	r6, [r2, #4]!
	cmp	r6, #0
	bne	.L789
.L771:
	add	r4, r4, #1
	cmp	r4, r1
	bne	.L773
	mov	r4, #255
.L772:
	ldr	r2, [ip, #2404]
	ldr	r2, [r2, #24]
	cmp	r2, #2
	bne	.L774
	ldr	r6, [ip, #3564]
	add	r6, r6, #56
.L770:
	mov	r7, r9
	mov	r5, #0
	b	.L780
.L776:
	ldr	r3, [r7, #4]!
.L780:
	cmp	r3, #0
	beq	.L790
.L775:
	ldr	r3, [r8]
	add	r5, r5, #1
	cmp	r3, r5
	bhi	.L776
.L777:
	ldr	r3, [fp, #-48]
	add	r10, r10, #1
	add	r9, r9, #68
	cmp	r10, r3
	bcc	.L779
.L782:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L769:
	ldr	r3, [ip, #2404]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	moveq	r3, #1
	streq	r3, [r8]
	ldreq	r3, [ip, #3564]
	addeq	r3, r3, #56
	streq	r3, [r9]
	b	.L777
.L790:
	sxtb	r2, r4
	str	r5, [sp]
	str	r2, [sp, #4]
	mov	r3, r10
	ldr	r2, .L791
	mov	r0, #1
	ldr	r1, .L791+8
	str	ip, [fp, #-52]
	bl	dprint_vfmw
	str	r6, [r7]
	ldr	ip, [fp, #-52]
	b	.L775
.L789:
	uxtb	r4, r4
	cmp	r4, #255
	bne	.L770
	b	.L772
.L783:
	mov	r6, r3
	mov	r4, #0
	b	.L770
.L774:
	mov	r3, r10
	ldr	r2, .L791
	ldr	r1, .L791+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L792:
	.align	2
.L791:
	.word	.LANCHOR0+264
	.word	.LC76
	.word	.LC78
	.word	.LC77
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
	subs	r8, r0, #0
	beq	.L829
	ldr	r3, .L861
	mov	r2, #136
	mov	r1, #0
	sub	r0, fp, #180
	ldr	r3, [r3, #48]
	blx	r3
	ldr	lr, [r8, #2600]
	cmp	lr, #0
	beq	.L830
	mov	r1, #0
	add	r0, r8, #2672
	mov	r3, r1
	b	.L797
.L796:
	cmp	r3, lr
	beq	.L795
.L797:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L796
	ldr	ip, [r2, #60]
	cmp	ip, #0
	bne	.L796
	ldr	ip, [r2, #64]
	cmp	ip, #1
	subeq	ip, fp, #44
	addeq	r2, r2, #56
	addeq	ip, ip, r1, lsl #2
	addeq	r1, r1, #1
	streq	r2, [ip, #-136]
	cmp	r3, lr
	bne	.L797
.L795:
	ldr	r4, [r8, #2604]
	cmp	r4, #0
	beq	.L831
	add	ip, r8, #2736
	mov	r0, r1
	add	ip, ip, #4
	mov	r3, #0
	b	.L800
.L799:
	cmp	r3, r4
	beq	.L857
.L800:
	ldr	r2, [ip, #4]!
	add	r3, r3, #1
	ldrb	lr, [r2, #1]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L799
	ldr	lr, [r2, #60]
	cmp	lr, #0
	bne	.L799
	ldr	lr, [r2, #64]
	cmp	lr, #1
	subeq	lr, fp, #44
	addeq	r2, r2, #56
	addeq	lr, lr, r0, lsl #2
	addeq	r0, r0, #1
	streq	r2, [lr, #-136]
	cmp	r3, r4
	bne	.L800
.L857:
	rsb	r4, r1, r0
.L798:
	ldr	r5, [r8, #2596]
	cmp	r5, #0
	beq	.L832
	add	lr, r8, #2800
	mov	r10, r0
	add	lr, lr, #8
	mov	r3, #0
	b	.L803
.L802:
	cmp	r3, r5
	beq	.L858
.L803:
	ldr	r2, [lr, #4]!
	add	r3, r3, #1
	ldrb	r6, [r2, #1]	@ zero_extendqisi2
	cmp	r6, #1
	bne	.L802
	ldr	r6, [r2, #60]
	cmp	r6, #1
	bne	.L802
	ldr	r6, [r2, #64]
	sub	ip, fp, #44
	add	r9, ip, r10, lsl #2
	add	r2, r2, #56
	cmp	r6, #0
	addeq	r10, r10, #1
	streq	r2, [r9, #-136]
	cmp	r3, r5
	bne	.L803
.L858:
	rsb	r5, r1, r10
	rsb	r5, r4, r5
.L801:
	cmp	r10, #0
	beq	.L859
	add	r3, r8, #4096
	str	r3, [fp, #-184]
	ldr	r3, [r3, #124]
	cmp	r3, #0
	str	r3, [fp, #-188]
	beq	.L860
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #180]
	ldr	r5, [r3, #184]
	cmp	r4, #0
	str	r4, [r3, #172]
	str	r5, [r3, #176]
	beq	.L822
.L828:
	ldr	r3, [fp, #-184]
	add	r7, r8, #2400
	add	r7, r7, #12
	mov	r6, #0
	ldrb	r9, [r3, #1200]	@ zero_extendqisi2
.L815:
	cmp	r9, #0
	mov	r1, r10
	mov	r0, r6
	ldrne	r1, [r7, #2888]
	bne	.L814
	bl	__aeabi_uidivmod
.L814:
	sub	r3, fp, #44
	add	r6, r6, #1
	add	r1, r3, r1, lsl #2
	cmp	r4, r6
	ldr	r1, [r1, #-136]
	str	r1, [r7, #4]!
	bhi	.L815
	ldr	r3, [fp, #-188]
	cmp	r3, #0
	bne	.L856
.L816:
	cmp	r5, #0
	beq	.L818
	ldr	r3, [fp, #-184]
	add	r6, r8, #2480
	mov	r4, #0
	ldrb	r7, [r3, #1201]	@ zero_extendqisi2
.L821:
	cmp	r7, #0
	mov	r1, r10
	mov	r0, r4
	ldrne	r1, [r6, #2948]
	bne	.L820
	bl	__aeabi_uidivmod
.L820:
	sub	r3, fp, #44
	add	r4, r4, #1
	add	r1, r3, r1, lsl #2
	cmp	r4, r5
	ldr	r3, [r1, #-68]
	str	r3, [r6, #4]!
	bne	.L821
.L856:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #172]
	ldr	r5, [r3, #176]
.L817:
	cmp	r4, #16
	bhi	.L826
.L822:
	add	r4, r4, #600
	add	r2, r8, #2480
	add	r4, r4, #3
	add	r4, r8, r4, lsl #2
.L825:
	ldr	r3, [r8, #2416]
	str	r3, [r4, #4]!
	cmp	r4, r2
	bne	.L825
.L826:
	cmp	r5, #16
	bhi	.L824
	add	r5, r5, #620
	add	r2, r8, #2544
	add	r2, r2, #4
	add	r5, r8, r5, lsl #2
.L827:
	ldr	r3, [r8, #2484]
	str	r3, [r5, #4]!
	cmp	r5, r2
	bne	.L827
.L824:
	mov	r0, #0
.L855:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L860:
	cmp	r4, #0
	beq	.L807
	sub	r3, fp, #180
	sub	r2, fp, #116
	add	lr, r3, r1, lsl #2
	ldr	r3, [fp, #-188]
.L808:
	add	r3, r3, #1
	ldr	r6, [lr], #4
	cmp	r3, r4
	str	r6, [r2, #4]!
	bne	.L808
.L807:
	cmp	r1, #0
	beq	.L809
	add	r2, r4, #16
	sub	lr, fp, #180
	mov	r3, #0
	add	r2, lr, r2, lsl #2
.L810:
	add	r3, r3, #1
	ldr	r6, [lr], #4
	cmp	r3, r1
	str	r6, [r2, #4]!
	bne	.L810
	add	r4, r4, r3
.L809:
	cmp	r5, #0
	beq	.L811
	add	r4, r4, #16
	sub	r2, fp, #180
	sub	r3, fp, #180
	add	r4, r2, r4, lsl #2
	add	r0, r3, r0, lsl #2
	mov	r3, #0
.L812:
	add	r3, r3, #1
	ldr	r2, [r0], #4
	cmp	r3, r5
	str	r2, [r4, #4]!
	bne	.L812
.L811:
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #180]
	ldr	r5, [r3, #184]
	cmp	r4, #0
	str	r4, [r3, #172]
	str	r5, [r3, #176]
	bne	.L828
	b	.L816
.L859:
	ldr	r3, .L861
	add	r4, r8, #4096
	mov	r2, #136
	mov	r1, r10
	str	r10, [r4, #172]
	add	r0, r8, #2416
	ldr	r3, [r3, #48]
	str	r10, [r4, #176]
	blx	r3
	ldr	r3, [r8, #2404]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L824
	mov	r3, #1
	str	r3, [r4, #172]
	ldr	r3, [r8, #3564]
	mov	r0, r10
	add	r3, r3, #56
	str	r3, [r8, #2416]
	b	.L855
.L830:
	mov	r1, lr
	b	.L795
.L831:
	mov	r0, r1
	b	.L798
.L832:
	mov	r10, r0
	b	.L801
.L818:
	ldr	r3, .L861
	add	r0, r8, #2480
	add	r0, r0, #4
	mov	r2, #68
	add	r1, r8, #2416
	ldr	r3, [r3, #52]
	blx	r3
	ldr	r3, [fp, #-184]
	ldr	r4, [r3, #172]
	str	r4, [r3, #176]
	mov	r5, r4
	b	.L817
.L829:
	mvn	r0, #0
	b	.L855
.L862:
	.align	2
.L861:
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
	ldr	r2, [r3, #124]
	cmp	r2, #2
	beq	.L868
	bl	HEVC_InitListX
	cmp	r0, #0
	bne	.L869
	mov	r0, r4
	bl	HEVC_RepairList
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L870
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L868:
	mov	r0, #0
	str	r0, [r3, #172]
	str	r0, [r3, #176]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L869:
	ldr	r1, .L870+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L871:
	.align	2
.L870:
	.word	.LC80
	.word	.LC79
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
	ldr	r2, [r0, #2388]
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
	bhi	.L879
	ldr	r3, .L881
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #2404]
	str	r6, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r6, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L875
	ldrb	r3, [r4, #2584]	@ zero_extendqisi2
	strb	r3, [fp, #-47]
.L877:
	sub	r1, fp, #48
	ldr	r0, [r4, #252]
	strb	r3, [fp, #-45]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L880
	ldr	r1, [r4, #2404]
	sub	r3, fp, #52
	ldr	r0, [r4, #252]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
.L878:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L875:
	mov	r3, #1
	strb	r3, [fp, #-47]
	b	.L877
.L879:
	str	r5, [sp]
	mov	r3, r6
	ldr	r2, .L881+4
	mov	r0, #0
	ldr	r1, .L881+8
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L880:
	ldr	r2, .L881+4
	mov	r0, #1
	ldr	r1, .L881+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L878
.L882:
	.align	2
.L881:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+280
	.word	.LC81
	.word	.LC82
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
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	add	r3, r1, #652
	ldr	ip, [r0, r3, asl #2]
	ldr	r2, [ip, #32]
	cmp	r2, #0
	bne	.L886
	ldr	r3, [ip, #24]
	cmp	r3, #15
	bhi	.L883
	add	r3, r0, r3, lsl #2
	add	r1, r0, #12288
	add	r3, r3, #12288
	mov	lr, #16
	str	r2, [r3, #240]
	str	r2, [r3, #304]
	str	r2, [r3, #368]
	ldr	r3, [ip, #20]
	add	r0, r0, r3, lsl #2
	str	r2, [r0, #2132]
	str	lr, [ip, #24]
	ldr	r3, [r1, #236]
	sub	r3, r3, #1
	str	r3, [r1, #236]
.L883:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L886:
	str	r2, [sp]
	mov	r3, r1
	ldr	r2, .L887
	mov	r0, #1
	ldr	r1, .L887+4
	bl	dprint_vfmw
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L888:
	.align	2
.L887:
	.word	.LANCHOR0+296
	.word	.LC83
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
	ldr	r3, [r0, #2588]
	mov	r6, r0
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #2592
	mov	r4, #0
	add	r5, r5, #12
	b	.L892
.L891:
	ldr	r3, [r6, #2588]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L895
.L892:
	ldr	r3, [r5, #4]!
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L891
	mov	r1, r4
	mov	r0, r6
	bl	HEVC_RemoveApcStore
	ldr	r3, [r6, #2588]
	add	r4, r4, #1
	cmp	r4, r3
	bcc	.L892
.L895:
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
	ldr	r2, [r0, #2368]
	mov	r6, #1888
	ldr	r1, [r5, #140]
	movw	lr, #12660
	ldr	r3, [r0, #2364]
	mov	ip, r0
	ldr	r4, [ip, #2588]
	mov	r0, #1
	mla	r2, r6, r1, r2
	cmp	r4, #0
	ldr	r2, [r2, #32]
	mla	r3, lr, r2, r3
	ldr	r3, [r3, #116]
	mov	r3, r0, asl r3
	str	r3, [fp, #-48]
	beq	.L896
	add	r3, ip, #2592
	add	r2, ip, #5120
	add	r3, r3, #12
	add	r2, r2, #44
	mov	r10, #0
	str	r2, [fp, #-64]
	mov	r2, r3
	mov	r3, r10
	mov	r10, r2
	b	.L913
.L899:
	ldr	r2, [ip, #2588]
	add	r3, r3, #1
	cmp	r3, r2
	bcs	.L896
.L913:
	ldr	r7, [r10, #4]!
	ldr	r2, [r5, #136]
	ldr	r1, [r7, #32]
	cmp	r1, r2
	bne	.L899
	ldr	r0, [r5, #1036]
	ldr	r2, [r5, #1040]
	ldr	r1, [r5, #1044]
	add	r2, r2, r0
	cmp	r2, r1
	mov	r8, r2
	ldrcs	r0, [r7, #8]
	movcs	r4, #0
	bcs	.L901
	add	r6, r2, #1296
	ldr	r9, [r7, #8]
	add	r6, r6, #12
	str	r3, [fp, #-60]
	mov	r3, r5
	mov	r4, #0
	add	r6, ip, r6, lsl #2
	mov	r5, r10
	mov	r10, r3
	str	ip, [fp, #-56]
.L907:
	ldr	r2, [r6, #-944]
	cmp	r2, #0
	ldr	r2, [r7, #60]
	beq	.L902
	cmp	r2, #0
	beq	.L903
	ldr	r2, [r6]
	cmp	r2, r9
	beq	.L934
.L903:
	cmp	r4, #0
	bne	.L918
	ldr	r1, [r6]
	mov	r4, r9
	b	.L915
.L902:
	cmp	r2, #0
	beq	.L905
	ldr	r1, [fp, #-48]
	mov	r0, r9
	bl	__aeabi_idivmod
	ldr	r0, [r6]
	str	r1, [fp, #-52]
	ldr	r1, [fp, #-48]
	bl	__aeabi_idivmod
	ldr	r2, [fp, #-52]
	cmp	r2, r1
	beq	.L934
.L905:
	cmp	r4, #0
	bne	.L918
	ldr	r2, [r6]
	mov	r0, r9
	ldr	r1, [fp, #-48]
	str	r2, [fp, #-52]
	bl	__aeabi_idivmod
	ldr	r2, [fp, #-52]
	mov	r0, r2
	mov	r4, r1
	ldr	r1, [fp, #-48]
	bl	__aeabi_idivmod
.L915:
	ldrb	r2, [r7, #1]	@ zero_extendqisi2
	rsb	r4, r1, r4
	clz	r4, r4
	cmp	r2, #0
	mov	r4, r4, lsr #5
	moveq	r4, #0
	cmp	r4, #0
	bne	.L935
.L918:
	mov	r0, r9
.L906:
	ldr	r2, [r10, #1044]
	add	r8, r8, #1
	add	r6, r6, #4
	mov	r9, r0
	cmp	r8, r2
	bcc	.L907
	mov	r2, r10
	mov	r10, r5
	mov	r5, r2
	ldr	r2, [r2, #1040]
	ldr	r1, [r5, #1036]
	ldr	r3, [fp, #-60]
	ldr	ip, [fp, #-56]
	add	r2, r2, r1
.L901:
	cmp	r2, #0
	ldr	lr, [r5, #116]
	beq	.L909
	ldr	r8, [fp, #-64]
	mov	r1, r7
	mov	r6, #0
	mov	r9, #1
	mov	r7, ip
.L911:
	ldr	r2, [r1, #60]
	add	r6, r6, #1
	cmp	r2, #0
	bne	.L910
	ldr	r2, [r8]
	add	r2, lr, r2
	cmp	r2, r0
	beq	.L936
.L910:
	ldr	r2, [r5, #1040]
	add	r8, r8, #4
	ldr	ip, [r5, #1036]
	add	r2, r2, ip
	cmp	r6, r2
	bcc	.L911
	mov	ip, r7
	mov	r7, r1
.L909:
	eor	r4, r4, #1
	cmp	r0, lr
	moveq	r0, #0
	andne	r0, r4, #1
	cmp	r0, #0
	beq	.L899
	mov	r2, #0
	strb	r2, [r7, #1]
	ldr	r2, [r10]
	mov	r1, #0
	str	r1, [r2, #60]
	ldr	r2, [r10]
	ldr	r1, [r2, #52]
	cmp	r1, #1
	beq	.L899
	ldr	r1, [r2, #28]
	mov	r2, #0
	ldr	r0, [ip, #252]
	str	r3, [fp, #-56]
	str	ip, [fp, #-52]
	bl	FSP_SetRef
	ldr	ip, [fp, #-52]
	ldr	r3, [fp, #-56]
	ldr	r2, [ip, #2588]
	add	r3, r3, #1
	cmp	r3, r2
	bcc	.L913
.L896:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L935:
	mov	r3, #1
	strb	r3, [r7, #1]
	ldr	r1, [r5]
	mov	r2, r3
	mov	r4, r3
	str	r3, [r1, #60]
	ldr	r1, [r5]
	str	r3, [r1, #48]
	ldr	r3, [fp, #-56]
	ldr	r1, [r5]
	ldr	r0, [r3, #252]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r7, [r5]
	ldr	r0, [r7, #8]
	b	.L906
.L936:
	strb	r9, [r1, #1]
	mov	r2, #1
	ldr	r1, [r10]
	mov	r4, r2
	str	r3, [fp, #-52]
	str	r9, [r1, #48]
	ldr	r1, [r10]
	ldr	r0, [r7, #252]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r1, [r10]
	ldr	lr, [r5, #116]
	ldr	r3, [fp, #-52]
	ldr	r0, [r1, #8]
	b	.L910
.L934:
	mov	r3, #1
	strb	r3, [r7, #1]
	ldr	r1, [r5]
	mov	r2, r3
	mov	r4, #1
	str	r3, [r1, #48]
	ldr	r3, [fp, #-56]
	ldr	r1, [r5]
	ldr	r0, [r3, #252]
	ldr	r1, [r1, #28]
	bl	FSP_SetRef
	ldr	r7, [r5]
	ldr	r0, [r7, #8]
	b	.L906
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
	ldr	r3, [r3, #132]
	sub	r3, r3, #19
	cmp	r3, #2
	bls	.L938
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_CheckThatAllRefPicsAreAvailable.part.8
.L938:
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
	ldr	r3, [r0, #2404]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_SetFrmRepeatCount.part.9
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
	add	r2, r0, #12672
	add	r4, r0, #26880
	add	r2, r2, #48
	add	r4, r4, #80
	mov	r5, #0
.L946:
	ldr	r3, [r2, #48]
	cmp	r3, #0
	bne	.L942
	cmp	r2, #0
	beq	.L943
	ldr	lr, [r0, #2588]
	cmp	lr, #0
	beq	.L943
	ldr	r1, [r0, #2608]
	cmp	r1, r2
	beq	.L942
	add	r1, r0, #2608
	b	.L944
.L945:
	ldr	ip, [r1, #4]!
	cmp	ip, r2
	beq	.L942
.L944:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L945
.L943:
	add	r5, r5, #1
.L942:
	add	r2, r2, #712
	cmp	r2, r4
	bne	.L946
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
	ldr	r1, [r4, #1036]
	cmp	r1, #0
	beq	.L976
	add	r9, r0, #5120
	mov	r7, #0
	mov	r5, r7
	mov	r8, r9
	add	r9, r9, #23
	add	r8, r8, #44
.L962:
	ldrb	r3, [r9, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L958
	ldr	lr, [r6, #2588]
	ldr	ip, [r4, #116]
	ldr	r3, [r8]
	cmp	lr, #0
	add	ip, ip, r3
	beq	.L958
	add	r1, r6, #2592
	mov	r3, #0
	add	r1, r1, #12
	b	.L961
.L959:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L958
.L961:
	ldr	r2, [r1, #4]!
	ldr	r0, [r2, #8]
	cmp	r0, ip
	bne	.L959
	ldr	r10, [r4, #136]
	ldr	r0, [r2, #32]
	cmp	r10, r0
	bne	.L959
	add	r10, r6, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r10, #2608]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1002
.L960:
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r10, #2608]
	mov	r1, #0
	add	r3, r6, r7, lsl #2
	add	r7, r7, #1
	str	r1, [r2, #60]
	ldr	r2, [r10, #2608]
	str	r2, [r3, #2676]
.L958:
	ldr	r1, [r4, #1036]
	add	r5, r5, #1
	add	r8, r8, #4
	cmp	r1, r5
	bhi	.L962
.L957:
	ldr	r2, [r6, #2584]
	str	r7, [r6, #2600]
	cmp	r2, r7
	addhi	r3, r7, #668
	movhi	r0, #0
	addhi	r3, r6, r3, lsl #2
	bls	.L967
.L966:
	add	r7, r7, #1
	str	r0, [r3, #4]!
	cmp	r7, r2
	bne	.L966
.L967:
	ldr	r3, [r4, #1040]
	add	r10, r1, r3
	cmp	r10, r5
	movls	r7, #0
	bls	.L965
	add	r8, r5, #1280
	add	r9, r5, #5120
	add	r8, r8, #11
	add	r9, r9, #23
	add	r9, r6, r9
	mov	r7, #0
	add	r8, r6, r8, lsl #2
	str	r7, [fp, #-48]
.L972:
	ldrb	r3, [r9, #1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L968
	ldr	ip, [r6, #2588]
	ldr	r0, [r4, #116]
	ldr	r3, [r8]
	cmp	ip, #0
	add	r0, r0, r3
	beq	.L968
	add	r1, r6, #2592
	mov	r3, #0
	add	r1, r1, #12
	b	.L971
.L969:
	add	r3, r3, #1
	cmp	r3, ip
	beq	.L968
.L971:
	ldr	r2, [r1, #4]!
	ldr	lr, [r2, #8]
	cmp	lr, r0
	bne	.L969
	ldr	r7, [r4, #136]
	ldr	lr, [r2, #32]
	cmp	r7, lr
	bne	.L969
	add	r7, r6, r3, lsl #2
	mov	r3, #1
	strb	r3, [r2, #1]
	ldr	r3, [r7, #2608]
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1003
.L970:
	mov	r2, #1
	str	r2, [r3, #64]
	ldr	r2, [r7, #2608]
	ldr	r1, [fp, #-48]
	add	r3, r1, #684
	add	r1, r1, #1
	str	r1, [fp, #-48]
	mov	r1, #0
	str	r1, [r2, #60]
	add	r3, r3, #2
	ldr	r2, [r7, #2608]
	str	r2, [r6, r3, asl #2]
.L968:
	add	r5, r5, #1
	add	r8, r8, #4
	cmp	r10, r5
	bhi	.L972
	ldr	r7, [fp, #-48]
	ldr	r2, [r6, #2584]
.L965:
	cmp	r2, r7
	str	r7, [r6, #2604]
	bls	.L956
	add	r1, r7, #684
	mov	r3, #0
	add	r1, r1, #1
	add	r6, r6, r1, lsl #2
.L974:
	add	r7, r7, #1
	str	r3, [r6, #4]!
	cmp	r7, r2
	bne	.L974
.L956:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1002:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r6, #252]
	bl	FSP_SetRef
	ldr	r3, [r10, #2608]
	b	.L960
.L1003:
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r6, #252]
	bl	FSP_SetRef
	ldr	r3, [r7, #2608]
	b	.L970
.L976:
	mov	r7, r1
	mov	r5, r1
	b	.L957
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
	ldr	r0, [r0, #2368]
	ldr	r3, [r5, #140]
	mov	r4, #1888
	ldr	r2, [r5, #1036]
	movw	lr, #12660
	ldr	ip, [r7, #2364]
	mov	r1, #1
	mla	r0, r4, r3, r0
	ldr	r4, [r5, #1040]
	ldr	r3, [r5, #1044]
	add	r2, r2, r4
	sub	r2, r2, #1
	sub	r10, r3, #1
	cmp	r10, r2
	ldr	r0, [r0, #32]
	mla	r2, lr, r0, ip
	ldr	r2, [r2, #116]
	mov	r2, r1, asl r2
	ble	.L1015
	add	r9, r3, #1296
	add	r3, r3, #5120
	add	r9, r9, #11
	add	r3, r3, #24
	add	r3, r7, r3
	sub	r4, r2, #1
	add	r9, r7, r9, lsl #2
	mov	r8, #0
	str	r8, [fp, #-52]
	mov	r8, r3
	str	r1, [fp, #-56]
.L1011:
	ldrb	r3, [r8, #-1]!	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1006
	ldrb	r0, [r9, #-944]	@ zero_extendqisi2
	ldr	ip, [r9]
	ldr	lr, [r7, #2588]
	cmp	r0, #0
	andeq	ip, ip, r4
	cmp	lr, #0
	ble	.L1006
	add	r1, r7, #2592
	mov	r3, #0
	add	r1, r1, #12
	str	r7, [fp, #-48]
	b	.L1010
.L1009:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1022
.L1010:
	ldr	r2, [r1, #4]!
	cmp	r0, #0
	ldr	r6, [r2, #8]
	andeq	r6, r6, r4
	cmp	ip, r6
	bne	.L1009
	ldr	r6, [r5, #136]
	ldr	r7, [r2, #32]
	cmp	r7, r6
	bne	.L1009
	ldr	r7, [fp, #-48]
	mov	ip, #0
	ldr	r1, [fp, #-52]
	ldr	r0, [fp, #-56]
	add	r3, r7, r3, lsl #2
	strb	r0, [r2, #1]
	add	r2, r7, r1, lsl #2
	add	r1, r1, #1
	str	r1, [fp, #-52]
	ldr	r1, [r3, #2608]
	str	ip, [r1, #64]
	ldr	r1, [r3, #2608]
	str	r0, [r1, #60]
	ldr	r3, [r3, #2608]
	str	r3, [r2, #2812]
.L1006:
	ldr	r3, [r5, #1036]
	sub	r10, r10, #1
	ldr	r2, [r5, #1040]
	sub	r9, r9, #4
	add	r3, r3, r2
	sub	r3, r3, #1
	cmp	r3, r10
	blt	.L1011
	ldr	r8, [fp, #-52]
	mov	r3, r8
.L1005:
	ldr	r2, [r7, #2584]
	str	r3, [r7, #2596]
	cmp	r2, r8
	ble	.L1004
	add	r3, r8, #700
	mov	r1, #0
	add	r3, r3, #2
	add	r3, r7, r3, lsl #2
.L1013:
	add	r8, r8, #1
	str	r1, [r3, #4]!
	cmp	r8, r2
	bne	.L1013
.L1004:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1022:
	ldr	r7, [fp, #-48]
	b	.L1006
.L1015:
	mov	r3, #0
	mov	r8, r3
	b	.L1005
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
	beq	.L1041
	ldr	r7, [r0, #3512]
	mov	r3, #200
	movw	r1, #12520
	mul	r3, r3, r7
	add	r2, r0, r3
	ldr	ip, [r2, r1]
	cmp	ip, #0
	beq	.L1026
	movw	r1, #12528
	ldr	r4, [r2, r1]
	cmp	r4, #0
	addne	r3, r3, #12480
	addne	r3, r3, #48
	movne	r4, #0
	addne	r3, r0, r3
	bne	.L1029
	b	.L1027
.L1032:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L1027
.L1029:
	add	r4, r4, #1
	cmp	r4, ip
	bne	.L1032
.L1026:
	ldr	r1, .L1042
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L1039:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1027:
	ldr	r1, [r5, #28]
	ldr	r0, [r6, #252]
	bl	FSP_GetLogicFs
	subs	ip, r0, #0
	beq	.L1030
	ldr	r3, [ip, #28]
	cmp	r3, #0
	beq	.L1030
	mov	r2, #50
	mov	r3, #200
	mla	r2, r2, r7, r4
	mov	lr, #1
	mla	r7, r3, r7, r6
	ldr	r1, .L1042+4
	mov	r3, r4
	mov	r0, #13
	add	r6, r6, r2, lsl #2
	add	r7, r7, #12480
	add	r6, r6, #12288
	str	lr, [r6, #240]
	ldr	r2, [ip, #28]
	ldr	r2, [r2, #4]
	str	r2, [r6, #304]
	ldr	r2, [r5, #8]
	str	r2, [r6, #368]
	ldr	r2, [r7, #44]
	add	r2, r2, lr
	str	r2, [r7, #44]
	ldr	r2, [r5, #228]
	bl	dprint_vfmw
	mov	r0, #0
	str	r4, [r5, #24]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1030:
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	mov	r0, #0
	ldr	r2, [r5, #28]
	ldr	r3, [r5, #8]
	stmia	sp, {r1, ip}
	str	r0, [sp, #8]
	ldr	r1, .L1042+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1039
.L1041:
	mov	r0, r5
	movw	r3, #11486
	ldr	r2, .L1042+12
	ldr	r1, .L1042+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1039
.L1043:
	.align	2
.L1042:
	.word	.LC88
	.word	.LC86
	.word	.LC87
	.word	.LC84
	.word	.LC85
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
	ldr	r0, [r0, #252]
	ldr	r1, [r1, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1045
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	moveq	r0, #1
	movne	r0, #0
	beq	.L1064
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1051
	ldr	r2, [r4, #48]
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1050
	cmp	r3, #1
	beq	.L1050
.L1061:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L1064:
	ldr	r3, [r4, #28]
	mov	r0, #13
	str	r2, [sp]
	ldr	r1, .L1065
	ldr	r2, .L1065+4
	bl	dprint_vfmw
.L1047:
	ldr	r3, [r4, #52]
	cmp	r3, #1
	beq	.L1051
	ldr	r3, [r4, #8]
	mov	r0, #1
	ldr	r2, .L1065+4
	ldr	r1, .L1065+8
	bl	dprint_vfmw
	mvn	r0, #2
	b	.L1061
.L1045:
	ldr	lr, [r4, #28]
	mov	r2, r4
	ldr	ip, [r4, #52]
	mov	r0, #1
	ldr	r3, [r4, #8]
	ldr	r1, .L1065+12
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	b	.L1047
.L1050:
	str	r3, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	mov	r3, r4
	ldr	r2, .L1065+4
	ldr	r1, .L1065+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1061
.L1051:
	mov	r2, #1
	mov	r3, #2
	strb	r2, [r4, #2]
	mvn	r0, #2
	str	r3, [r4, #52]
	b	.L1061
.L1066:
	.align	2
.L1065:
	.word	.LC89
	.word	.LANCHOR0+316
	.word	.LC91
	.word	.LC90
	.word	.LC92
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
	beq	.L1069
	ldr	r3, [r0, #2588]
	cmp	r3, #0
	beq	.L1069
	add	r10, r0, #2592
	mvn	r6, #1
	add	r10, r10, #12
	mvn	r7, #0
	mov	r9, #0
	mvn	r3, #0
	str	r3, [fp, #-48]
.L1072:
	ldr	r2, [r10, #4]!
	cmp	r2, #0
	beq	.L1071
	ldr	r1, [r2, #28]
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1071
	ldrsb	r2, [r0, #1]
	cmp	r2, #3
	cmpne	r2, #0
	beq	.L1071
	ldr	r2, [r10]
	add	r2, r2, #672
	ldrd	r0, [r2, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	strcc	r9, [fp, #-48]
	movcc	r6, r0
	movcc	r7, r1
.L1071:
	ldr	r2, [r5, #2588]
	add	r9, r9, #1
	cmp	r9, r2
	bcc	.L1072
	ldr	r3, [fp, #-48]
	cmn	r3, #1
	beq	.L1069
	ldrd	r2, [r8, #-8]
	cmp	r3, r7
	cmpeq	r2, r6
	bhi	.L1104
.L1069:
	ldrb	r3, [r4, #145]	@ zero_extendqisi2
	ldrb	r2, [r4, #144]	@ zero_extendqisi2
	and	r3, r3, #195
	bfc	r3, #0, #2
	bfc	r2, #0, #2
	strb	r3, [r4, #145]
	strb	r2, [r4, #144]
	ldr	r3, [r5, #144]
	str	r3, [r4, #188]
	ldr	r3, [r5, #2384]
	ldrh	r3, [r3, #124]
	cmp	r3, #1
	moveq	r2, #0
	beq	.L1073
	movw	r2, #257
	cmp	r3, r2
	movne	r2, #1
	bne	.L1073
	ldr	r2, [r5, #2892]
	subs	r2, r2, #1
	movne	r2, #1
.L1073:
	ldr	r3, [r5, #2388]
	ldrb	r3, [r3, #2066]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	ip, #3
	beq	.L1074
	ldr	r3, [r4, #40]
	cmp	r3, #1
	cmpne	r3, #11
	moveq	ip, #1
	bne	.L1105
.L1075:
	ldr	r2, [r4, #44]
	clz	r2, r2
	mov	r2, r2, lsr #5
.L1074:
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
	ldr	r3, [r5, #2404]
	ldr	r1, [r4, #28]
	ldr	r3, [r3, #596]
	str	r3, [r4, #204]
	ldr	r3, [r5, #2404]
	ldr	r3, [r3, #600]
	str	r3, [r4, #208]
	ldr	r3, [r5, #2404]
	ldr	r3, [r3, #604]
	str	r3, [r4, #212]
	ldr	r0, [r5, #252]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L1067
	ldr	r3, .L1106
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
.L1067:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1105:
	bic	r3, r3, #8
	cmp	r3, #2
	moveq	ip, #2
	movne	ip, #3
	b	.L1075
.L1104:
	ldr	r0, [r5, #252]
	strd	r6, [sp]
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L1069
	ldrd	r2, [r8, #-8]
	mov	r0, #29
	ldr	r1, .L1106+4
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [fp, #-48]
	add	r10, r3, #652
	ldrd	r2, [r8, #-8]
	ldr	r1, [r5, r10, asl #2]
	add	r1, r1, #672
	strd	r2, [r1, #-8]
	strd	r6, [r8, #-8]
	b	.L1069
.L1107:
	.align	2
.L1106:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC93
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
	bhi	.L1110
	mov	r3, #712
	mla	r1, r3, r1, r0
	add	r1, r1, #12672
	ldrb	r0, [r1, #49]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1110:
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
	ldr	r0, [r0, #252]
	mov	r9, r1
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1116
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	addne	r4, r0, #576
	addne	r5, r0, #608
	movne	r6, #0
	movne	r7, #0
	beq	.L1121
.L1115:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1114
	ldr	r0, [r8, #252]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1114:
	cmp	r4, r5
	bne	.L1115
	ldr	r0, [r8, #252]
	mov	r1, r9
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1121:
	ldr	r1, .L1122
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1116:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1123:
	.align	2
.L1122:
	.word	.LC94
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
	bhi	.L1128
	sub	r2, r3, #8448
	movw	ip, #4749
	sub	r2, r2, #52
	cmp	r2, ip
	movls	r3, #1
	strlsb	r3, [r0, #3]
	bls	.L1126
	sub	r3, r3, #13248
	movw	r2, #1749
	sub	r3, r3, #2
	cmp	r3, r2
	bhi	.L1128
	mov	r3, #2
	strb	r3, [r0, #3]
.L1126:
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
.L1128:
	mov	r3, #0
	strb	r3, [r0, #3]
	b	.L1126
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
	ldr	r1, .L1150
	mov	r4, r0
	ldrb	r2, [r0]	@ zero_extendqisi2
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	ldr	r1, .L1150+4
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	ldr	r1, .L1150+8
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	ldr	r1, .L1150+12
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #4]
	ldr	r1, .L1150+16
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r2, [r4, #6]
	ldr	r1, .L1150+20
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ldr	r1, .L1150+24
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #9]	@ zero_extendqisi2
	ldr	r1, .L1150+28
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	mov	r0, #32
	cmp	r5, #0
	bne	.L1132
	ldr	r1, .L1150+32
	bl	dprint_vfmw
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	ldr	r1, .L1150+36
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	ldr	r1, .L1150+40
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	ldr	r1, .L1150+44
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #14]	@ zero_extendqisi2
	ldr	r1, .L1150+48
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r2, [r4, #15]	@ zero_extendqisi2
	ldr	r1, .L1150+52
	mov	r0, #32
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #15
	addne	r6, r4, #26
	beq	.L1137
.L1136:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1150+56
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1150+60
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1136
.L1137:
	ldrb	r2, [r4, #38]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1150+64
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #38
	addne	r6, r4, #45
	movne	r5, #0
	beq	.L1138
.L1139:
	mov	r3, r5
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	ldr	r1, .L1150+68
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrb	r2, [r6, #1]!	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1150+72
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #38]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1139
.L1138:
	movw	r2, #290
	ldr	r1, .L1150+76
	mov	r0, #32
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1132:
	ldr	r1, .L1150+80
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #10
	addne	r6, r4, #78
	movne	r5, #0
	beq	.L1144
.L1143:
	mov	r2, r5
	ldrh	r3, [r7, #2]!
	ldr	r1, .L1150+84
	mov	r0, #32
	bl	dprint_vfmw
	ldrh	r3, [r6, #2]!
	mov	r2, r5
	ldr	r1, .L1150+88
	mov	r0, #32
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #10]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1143
.L1144:
	ldrb	r2, [r4, #148]	@ zero_extendqisi2
	mov	r0, #32
	ldr	r1, .L1150+92
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r7, r4, #148
	addne	r6, r4, #216
	movne	r5, #0
	beq	.L1142
.L1145:
	mov	r3, r5
	ldrh	r2, [r7, #2]!
	ldr	r1, .L1150+96
	mov	r0, #32
	bl	dprint_vfmw
	mov	r3, r5
	ldrh	r2, [r6, #2]!
	mov	r0, #32
	ldr	r1, .L1150+100
	add	r5, r5, #1
	bl	dprint_vfmw
	ldrb	r3, [r4, #148]	@ zero_extendqisi2
	cmp	r3, r5
	bhi	.L1145
.L1142:
	movw	r3, #286
	ldr	r1, .L1150+104
	ldrh	r2, [r4, r3]
	add	r4, r4, #288
	mov	r0, #32
	bl	dprint_vfmw
	ldr	r1, .L1150+108
	ldrh	r2, [r4]
	mov	r0, #32
	bl	dprint_vfmw
	b	.L1138
.L1151:
	.align	2
.L1150:
	.word	.LC95
	.word	.LC96
	.word	.LC97
	.word	.LC98
	.word	.LC99
	.word	.LC100
	.word	.LC101
	.word	.LC102
	.word	.LC103
	.word	.LC104
	.word	.LC105
	.word	.LC106
	.word	.LC107
	.word	.LC108
	.word	.LC110
	.word	.LC111
	.word	.LC109
	.word	.LC112
	.word	.LC113
	.word	.LC122
	.word	.LC114
	.word	.LC116
	.word	.LC117
	.word	.LC115
	.word	.LC120
	.word	.LC121
	.word	.LC118
	.word	.LC119
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
	beq	.L1155
	ldrb	r2, [r4, #56]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1198
.L1155:
	ldrb	r2, [r4, #56]	@ zero_extendqisi2
	ldrb	ip, [r4, #568]	@ zero_extendqisi2
	ldrb	r0, [r4, #59]	@ zero_extendqisi2
	ldrb	r1, [r4, #128]	@ zero_extendqisi2
.L1154:
	str	r1, [sp, #12]
	str	r0, [sp, #8]
	mov	r0, #22
	stmia	sp, {r2, ip}
	ldr	r1, .L1201
	ldr	r2, .L1201+4
	bl	dprint_vfmw
	mov	r3, #0
	strb	r3, [r5, #458]
.L1152:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1198:
	ldrb	ip, [r4, #568]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1155
	ldrb	r1, [r4, #59]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1156
	ldrb	r1, [r4, #128]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1199
.L1156:
	mov	r3, #1
	strb	r3, [r5, #458]
	ldr	r0, [r6, #24]
	ldrb	r1, [r4, #57]	@ zero_extendqisi2
	ldrb	r2, [r4, #58]	@ zero_extendqisi2
	cmp	r0, #9
	strb	r1, [fp, #-320]
	strb	r2, [fp, #-319]
	bne	.L1158
	ldr	r2, [r6, #32]
	cmp	r2, #9
	streqb	r3, [fp, #-312]
.L1158:
	ldrb	r3, [r4, #60]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1159
	ldrb	r2, [r4, #129]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1159
	cmp	r2, #9
	cmpne	r3, #9
	ldrneb	r3, [fp, #-312]	@ zero_extendqisi2
	moveq	r3, #1
	strb	r3, [fp, #-318]
.L1159:
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
	bne	.L1163
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
	beq	.L1168
	sub	r2, fp, #320
	add	ip, r4, #66
	add	r0, r2, #15
	add	r1, r4, #81
	add	r2, r2, #26
.L1167:
	add	r3, r3, #1
	ldrb	r6, [ip, #1]!	@ zero_extendqisi2
	ldrb	lr, [r1, #1]!	@ zero_extendqisi2
	cmp	r3, r7
	strb	r6, [r0, #1]!
	strb	lr, [r2, #1]!
	bne	.L1167
.L1168:
	ldrb	r6, [r4, #97]	@ zero_extendqisi2
	cmp	r6, #0
	strb	r6, [fp, #-282]
	beq	.L1166
	sub	r1, fp, #280
	sub	r2, fp, #272
	add	r0, r4, #97
	sub	r1, r1, #2
	add	r4, r4, #112
	sub	r2, r2, #3
	mov	r3, #0
.L1171:
	add	r3, r3, #1
	ldrb	lr, [r0, #1]!	@ zero_extendqisi2
	ldrb	ip, [r4, #1]!	@ zero_extendqisi2
	cmp	r3, r6
	strb	lr, [r1, #1]!
	strb	ip, [r2, #1]!
	bne	.L1171
.L1166:
	ldr	r3, [r5, #464]
	cmp	r3, #0
	bne	.L1200
	ldr	r2, .L1201+4
	mov	r0, #1
	ldr	r1, .L1201+8
	bl	dprint_vfmw
	b	.L1152
.L1163:
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
	beq	.L1175
.L1174:
	add	r2, r2, #1
	ldrh	lr, [r0, #2]!
	ldrh	ip, [r1, #2]!
	cmp	r2, r6
	add	r3, r3, #2
	strh	lr, [r3, #10]	@ movhi
	strh	ip, [r3, #78]	@ movhi
	bcc	.L1174
.L1175:
	ldrb	lr, [r4, #169]	@ zero_extendqisi2
	add	lr, lr, #1
	uxtb	lr, lr
	strb	lr, [fp, #-172]
	cmp	lr, #0
	beq	.L1166
	add	r1, r4, #432
	sub	r3, fp, #320
	add	r4, r4, #236
	add	r1, r1, #2
	mov	r2, #0
.L1176:
	add	r2, r2, #1
	ldrh	ip, [r4, #2]!
	ldrh	r0, [r1, #2]!
	cmp	r2, lr
	add	r3, r3, #2
	strh	ip, [r3, #148]	@ movhi
	strh	r0, [r3, #216]	@ movhi
	bcc	.L1176
	b	.L1166
.L1200:
	ldr	r3, .L1201+12
	sub	r1, fp, #320
	movw	r2, #290
	ldr	r0, [r5, #472]
	ldr	r3, [r3, #52]
	blx	r3
	movw	r3, #290
	str	r3, [r5, #460]
	b	.L1152
.L1199:
	mov	r0, r1
	b	.L1154
.L1202:
	.align	2
.L1201:
	.word	.LC123
	.word	.LANCHOR0+340
	.word	.LC124
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
.L1204:
	ldr	r5, [r0, #572]
	add	r2, r2, #1
	cmp	r2, #3
	add	r0, r0, #4
	strh	r5, [lr, #2]!	@ movhi
	ldr	r5, [r0, #580]
	strh	r5, [r4, #2]!	@ movhi
	bne	.L1204
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #4096
	ldr	r3, [r0, #2368]
	mov	ip, #1888
	mov	r6, r0
	ldr	r2, [r2, #140]
	movw	r5, #12660
	ldr	r0, [r0, #2364]
	add	lr, r6, #12672
	mov	r1, #0
	add	lr, lr, #48
	mla	r3, ip, r2, r3
	mov	r7, r1
	ldr	r3, [r3, #32]
	strb	r1, [r6, #3505]
	mla	r5, r5, r3, r0
.L1211:
	ldr	r3, [lr, #48]
	cmp	r3, #0
	bne	.L1207
	cmp	lr, #0
	beq	.L1218
	ldr	r1, [r6, #2588]
	cmp	r1, #0
	beq	.L1218
	ldr	r2, [r6, #2608]
	cmp	r2, lr
	beq	.L1207
	add	r2, r6, #2608
	b	.L1209
.L1210:
	ldr	ip, [r2, #4]!
	cmp	ip, lr
	beq	.L1207
.L1209:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L1210
.L1218:
	mov	r3, #712
	add	r8, r6, #3568
	mla	r7, r3, r7, r6
	mov	r2, #101
	mov	r3, #1
	str	r2, [r6, #3544]
	strb	r3, [r6, #3505]
	mov	r0, r8
	add	r1, r7, #12800
	mov	r2, #632
	mov	r4, lr
	bl	memcpy
	add	r3, r7, #12672
	add	r7, r7, #12736
	str	r4, [r6, #3564]
	mov	r9, #0
	str	r9, [r6, #3720]
	str	r9, [r7]
	strb	r9, [r3, #50]
	strb	r9, [r4]
	ldr	r3, [r6, #3564]
	str	r9, [r3, #60]
	ldr	r3, [r6, #3564]
	str	r9, [r3, #64]
	ldr	r3, [r6, #3564]
	str	r9, [r3, #52]
	ldrb	r1, [r6, #3505]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1215
	ldr	r0, [r6, #252]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r6, #252]
	bl	FSP_GetLogicFs
	mvn	r3, r7
	mov	r3, r3, lsr #31
	cmp	r0, #0
	mov	r4, r0
	moveq	r3, #0
	cmp	r3, #0
	beq	.L1213
	add	r1, r5, #2064
	add	r2, r6, #2880
	bl	HEVC_ConvertHDRInfo
	ldr	r3, [r6, #2404]
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L1222
.L1214:
	ldr	r5, .L1223
	add	r1, r4, #40
	ldr	r0, [r6, #3564]
	mov	r2, #632
	ldr	r3, [r5, #52]
	add	r0, r0, #80
	blx	r3
	ldr	r1, [r6, #3564]
	ldr	r3, [r5, #52]
	mov	r0, r8
	add	r1, r1, #80
	mov	r2, #632
	blx	r3
	ldr	r3, [r6, #3564]
	mov	r0, #0
	str	r7, [r3, #28]
	ldrsb	r3, [r4, #4]
	str	r3, [r6, #3540]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1207:
	add	r7, r7, #1
	add	lr, lr, #712
	cmp	r7, #20
	bne	.L1211
.L1215:
	ldr	r1, .L1223+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1222:
	ldr	r1, [r6, #2388]
	ldr	r5, [r4, #152]
	ldr	r3, [r4, #76]
	ldr	r2, [r1, #68]
	ldr	r1, [r1, #64]
	str	r9, [r4, #280]
	mul	r5, r5, r2
	str	r2, [r4, #112]
	str	r1, [r4, #108]
	str	r9, [r4, #284]
	add	r3, r5, r3
	str	r9, [r4, #288]
	str	r3, [r4, #80]
	mov	r0, r3
	str	r9, [r4, #292]
	str	r9, [r4, #296]
	bl	MEM_Phy2Vir
	ldr	r2, [r4, #60]
	ldr	r3, [r4, #156]
	add	r5, r5, r2
	str	r9, [r4, #556]
	str	r5, [r4, #64]
	add	r5, r5, r3
	str	r5, [r4, #72]
	str	r0, [r4, #552]
	b	.L1214
.L1213:
	strb	r3, [r6, #3505]
	mov	r0, r3
	ldr	r1, .L1223+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1224:
	.align	2
.L1223:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC125
	.word	.LC126
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
	ldr	r0, [r0, #252]
	bl	FSP_GetFspType
	cmn	r0, #1
	mov	r4, r0
	movne	r4, #0
	bne	.L1229
	b	.L1232
.L1228:
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1230
	cmp	r4, #32
	beq	.L1233
.L1229:
	mov	r1, r4
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	add	r4, r4, #1
	cmp	r0, #0
	bne	.L1228
	ldr	r1, .L1234
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1232:
	ldr	r1, .L1234+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1230:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1233:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1235:
	.align	2
.L1234:
	.word	.LC128
	.word	.LC127
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
	add	r0, r0, #5504
	add	r0, r0, #56
	add	r5, r8, #13312
	bl	ResetVoQueue
	add	r9, r8, #27392
	add	r5, r5, #56
	add	r9, r9, #216
	mov	r6, #0
	mov	r7, #0
.L1239:
	sub	r4, r5, #32
	mov	r3, #0
	strb	r3, [r5, #-647]
	str	r3, [r5, #-600]
.L1238:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1237
	ldr	r0, [r8, #252]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1237:
	cmp	r4, r5
	bne	.L1238
	add	r5, r4, #712
	cmp	r5, r9
	bne	.L1239
	ldr	r2, [r8, #184]
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r3, #0
	add	r8, r8, #2128
	mov	r1, r3
.L1241:
	add	r3, r3, #1
	str	r1, [r8, #4]!
	cmp	r3, r2
	bne	.L1241
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
	ldr	r3, [r6, #2608]
	str	r7, [r3, #48]
	ldr	r3, [r6, #2608]
	ldr	r0, [r0, #252]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1250
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L1251
	ldr	r3, [r6, #2608]
	mov	r2, r7
	ldr	r0, [r5, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
.L1251:
	ldr	r3, [r6, #2608]
	mov	r2, #0
	ldr	r0, [r5, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
.L1250:
	ldr	r1, [r5, #2588]
	sub	r1, r1, #1
	cmp	r4, r1
	addls	r3, r4, #652
	addls	r3, r5, r3, lsl #2
	bhi	.L1254
.L1253:
	add	r4, r4, #1
	ldr	r2, [r3, #4]!
	cmp	r4, r1
	str	r2, [r3, #-4]
	bls	.L1253
.L1254:
	add	r3, r1, #652
	mov	r2, #0
	str	r2, [r5, r3, asl #2]
	str	r1, [r5, #2588]
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
	ldr	r3, [r0, #2588]
	mov	r5, r0
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r7, #0
	mov	r4, r7
	mov	r6, r7
	b	.L1266
.L1265:
	ldr	r3, [r5, #2588]
	add	r4, r4, #1
	cmp	r4, r3
	mov	r7, r4
	bcs	.L1272
.L1266:
	add	r3, r4, #652
	ldr	r3, [r5, r3, asl #2]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1265
	mov	r1, r7
	mov	r0, r5
	strb	r6, [r3]
	sub	r4, r4, #1
	bl	HEVC_RemoveApcStore
	mov	r1, r7
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
	b	.L1265
.L1272:
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
	ldr	r5, [r0, #2588]
	mov	r7, r0
	cmp	r5, #0
	beq	.L1282
	mov	r6, #0
	mvn	r8, #0
	mov	r10, r6
	mov	r9, r6
	b	.L1281
.L1292:
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	cmpne	r3, #3
	ldr	r3, [r4, #2608]
	bne	.L1277
	ldr	r0, [r3, #52]
	cmp	r0, #1
	beq	.L1277
	str	r8, [r3, #28]
	mov	r2, #1
	ldr	r3, [r4, #2608]
	strb	r1, [r3, #1]
	ldr	r3, [r4, #2608]
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2608]
.L1277:
	ldr	r3, [r3]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	addne	r10, r10, #1
	beq	.L1291
	add	r9, r9, #1
	cmp	r9, r5
	beq	.L1274
.L1281:
	add	r4, r7, r10, lsl #2
	ldr	r0, [r7, #252]
	ldr	r3, [r4, #2608]
	ldr	r1, [r3, #28]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L1275
	ldrsb	r1, [r0]
	cmp	r1, #0
	beq	.L1292
	ldr	r3, [r4, #2608]
	b	.L1277
.L1275:
	ldr	r3, [r4, #2608]
	ldr	r1, [r3, #52]
	cmp	r1, #1
	beq	.L1277
	str	r8, [r3, #28]
	mov	r2, #1
	ldr	r3, [r4, #2608]
	strb	r0, [r3, #1]
	ldr	r3, [r4, #2608]
	strb	r2, [r3, #2]
	ldr	r3, [r4, #2608]
	b	.L1277
.L1291:
	mov	r1, r10
	mov	r0, r7
	add	r9, r9, #1
	bl	HEVC_RemoveFrameStoreOutDPB
	cmp	r9, r5
	mov	r6, #1
	bne	.L1281
.L1274:
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1282:
	mov	r6, r5
	b	.L1274
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
	ldr	r2, [r3, #236]
	ldr	r3, [r3, #232]
	cmp	r2, r3
	bcs	.L1297
	ldr	r3, [r0, #2584]
	ldr	r2, [r0, #2588]
	cmp	r2, r3
	ldmccfd	sp, {r4, r5, fp, sp, pc}
	cmp	r3, #15
	bls	.L1299
.L1297:
	ldr	r3, [r4, #2608]
	mov	r5, #0
	mov	r2, r5
	strb	r5, [r3, #1]
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	mov	r1, r5
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	HEVC_RemoveFrameStoreOutDPB
.L1299:
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L1297
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
	ldr	r2, [r0, #2588]
	mov	r6, r0
	ldr	r3, [r0, #2584]
	cmp	r2, r3
	bhi	.L1307
	cmp	r2, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1308:
	add	lr, r6, #2592
	mov	r3, #0
	add	lr, lr, #12
.L1304:
	ldr	r2, [lr, #4]!
	ldr	r4, [r5]
	ldr	ip, [r2, #8]
	cmp	r4, ip
	strgt	ip, [r5]
	strgt	r3, [r7]
	add	r3, r3, #1
	ldr	ip, [r6, #2588]
	cmp	ip, r3
	bhi	.L1304
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1307:
	ldr	r1, .L1309
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r6, #2584]
	cmp	r2, #0
	str	r2, [r6, #2588]
	bne	.L1308
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1310:
	.align	2
.L1309:
	.word	.LC129
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
	ldr	r5, [r0, #2368]
	mov	r6, #1888
	movw	r4, #12660
	ldr	ip, [r3, #140]
	ldr	r3, [r0, #2364]
	ldr	lr, [fp, #4]
	mla	ip, r6, ip, r5
	ldr	ip, [ip, #32]
	mla	r3, r4, ip, r3
	ldr	ip, [r3, #64]
	ldr	r3, [r3, #68]
	cmp	r1, ip
	cmpeq	lr, #0
	bne	.L1315
	cmp	r2, r3
	beq	.L1316
.L1315:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L1316:
	ldr	r3, [r0, #172]
	cmp	r3, #0
	beq	.L1315
	ldr	r3, [r0, #2404]
	ldr	r0, [r3, #904]
	adds	r0, r0, #0
	movne	r0, #1
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
	ldr	r4, [r0, #2376]
	ldrb	ip, [r4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L1328
	mov	r3, #0
	mov	r2, r4
	mov	lr, r3
.L1319:
	add	r3, r3, #1
	ldr	r1, [r2, #44]
	cmp	r3, ip
	add	r2, r2, #28
	add	lr, lr, r1
	bne	.L1319
.L1318:
	ldr	r2, [r0, #2356]
	mov	r3, ip, asl #5
	sub	ip, r3, ip, asl #2
	add	r4, r4, ip
	ldr	r3, [r2, #24]
	and	r3, r3, #7
	str	r3, [r4, #56]
	ldr	r2, [r0, #2376]
	ldr	r3, [r0, #2356]
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #48]
	add	r2, r2, ip, lsr #3
	rsb	r2, lr, r2
	str	r2, [r3, #60]
	ldr	r1, [r0, #2376]
	ldr	r3, [r0, #2356]
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldr	ip, [r3, #24]
	mov	r3, r2, asl #5
	sub	r2, r3, r2, asl #2
	add	r2, r1, r2
	ldr	r3, [r2, #44]
	add	r3, lr, r3
	rsb	r3, ip, r3, lsl #3
	str	r3, [r2, #52]
	ldr	r2, [r0, #2376]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	ldr	r1, [r3, #56]
	and	r2, r2, #3
	add	r2, r1, r2, lsl #3
	str	r2, [r3, #56]
	ldr	r2, [r0, #2376]
	ldrb	r1, [r2]	@ zero_extendqisi2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #3
	str	r2, [r3, #60]
	ldr	r1, [r0, #2376]
	ldr	r2, [r1, #8]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L1335
	ldrb	ip, [r1]	@ zero_extendqisi2
	add	lr, ip, #1
	cmp	r2, lr
	movhi	r2, #1
	movls	r2, #0
	cmp	lr, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1321
	add	ip, ip, #2
	mov	lr, #0
.L1322:
	sub	r3, ip, #1
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	str	lr, [r1, #56]
	ldr	r2, [r0, #2376]
	add	r2, r2, r3
	ldr	r1, [r2, #48]
	str	r1, [r2, #60]
	ldr	r2, [r0, #2376]
	add	r2, r2, r3
	ldr	r1, [r2, #44]
	mov	r1, r1, asl #3
	str	r1, [r2, #52]
	ldr	r2, [r0, #2376]
	add	r2, r2, r3
	ldr	r1, [r2, #60]
	ldr	r4, [r2, #56]
	and	r1, r1, #15
	add	r1, r4, r1, lsl #3
	str	r1, [r2, #56]
	ldr	r2, [r0, #2376]
	add	r3, r2, r3
	ldr	r2, [r3, #60]
	bic	r2, r2, #15
	str	r2, [r3, #60]
	ldr	r1, [r0, #2376]
	ldr	r3, [r1, #8]
	cmp	ip, #1
	cmpls	ip, r3
	add	ip, ip, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L1322
	sub	r3, r3, #1
.L1321:
	mov	r2, r3, asl #5
	ldr	ip, [r1, #12]
	sub	r3, r2, r3, asl #2
	add	r1, r1, r3
	ldr	r3, [r1, #52]
	rsb	r3, ip, r3
	str	r3, [r1, #52]
	ldr	lr, [r0, #2376]
	ldrb	r2, [lr]	@ zero_extendqisi2
	ldr	r3, [lr, #8]
	cmp	r2, r3
	ldmcsfd	sp, {r4, fp, sp, pc}
	sxth	r1, r2
	mov	r3, r1, asl #5
	sub	r3, r3, r1, asl #2
	add	r3, lr, r3
.L1326:
	ldr	r1, [r3, #60]
	add	r2, r2, #1
	ldr	ip, [r0, #3536]
	add	r3, r3, #28
	cmp	r1, ip
	strcc	r1, [r0, #3536]
	ldr	r1, [lr, #8]
	cmp	r1, r2
	bhi	.L1326
	ldmfd	sp, {r4, fp, sp, pc}
.L1335:
	ldr	r1, .L1336
	mov	r0, #0
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	dprint_vfmw
.L1328:
	mov	lr, ip
	b	.L1318
.L1337:
	.align	2
.L1336:
	.word	.LC130
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
	ldr	r2, [r2, #140]
	cmp	r2, r3
	bge	.L1346
	mov	r3, #1888
	ldr	r1, [r0, #2368]
	mul	r3, r3, r2
	add	ip, r1, r3
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1347
	ldr	r2, [ip, #32]
	ldr	r3, [r0, #160]
	cmp	r2, r3
	bge	.L1348
	ldr	r1, [r0, #2364]
	movw	r3, #12660
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #1]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1349
	ldr	r2, [r3, #48]
	ldr	r3, [r0, #156]
	cmp	r2, r3
	bcs	.L1350
	ldr	r1, [r0, #2360]
	mov	r3, r2, asl #7
	add	r3, r3, r2, lsl #2
	ldrb	r3, [r1, r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1351
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1346:
	ldr	r1, .L1352
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1347:
	ldr	r1, .L1352+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1348:
	ldr	r1, .L1352+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1349:
	ldr	r1, .L1352+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1350:
	ldr	r1, .L1352+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1351:
	ldr	r1, .L1352+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1353:
	.align	2
.L1352:
	.word	.LC131
	.word	.LC132
	.word	.LC133
	.word	.LC134
	.word	.LC135
	.word	.LC136
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
	ldr	ip, [r0, #2376]
	ldr	r2, [r1, #136]
	ldr	r3, [ip, #16]
	add	r4, r0, r2, lsl #2
	sub	r5, r3, #16
	ldr	lr, [r4, #228]
	cmn	lr, #-2147483647
	beq	.L1388
	cmp	r3, #21
	cmpne	r5, #2
	bls	.L1384
.L1368:
	sub	r3, r3, #19
	cmp	r3, #1
	movls	lr, #-2147483647
	strls	lr, [r4, #228]
.L1384:
	ldr	r5, [r1, #116]
	cmp	r5, lr
	bge	.L1358
	ldr	r3, [ip, #16]
	sub	r6, r3, #8
	cmp	r6, #1
	addhi	r2, r0, r2
	bls	.L1389
.L1361:
	ldrb	lr, [r2, #10]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L1362
	ldr	r6, [r4, #232]
	cmp	r5, r6
	blt	.L1390
.L1362:
	ldrb	r3, [r1, #105]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1363
	ldr	ip, [ip, #16]
	sub	lr, ip, #19
	cmp	lr, #1
	bls	.L1385
	cmp	ip, #21
	beq	.L1385
	sub	ip, ip, #16
	cmp	ip, #2
	strls	r5, [r4, #232]
	movls	r3, #1
	strlsb	r3, [r2, #10]
.L1363:
	ldr	r2, [r0, #236]
	ldrb	r3, [r1, #104]	@ zero_extendqisi2
	cmp	r2, #0
	ldr	r2, [r1, #140]
	beq	.L1367
	ldr	r1, [r0, #208]
	cmp	r2, r1
	movne	r3, #1
.L1367:
	ldr	r1, [r0, #296]
	cmp	r1, r2
	movne	r0, #1
	beq	.L1391
.L1382:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1388:
	cmp	r5, #5
	bhi	.L1386
	cmp	r3, #21
	cmpne	r5, #2
	bhi	.L1368
	ldr	r5, [r1, #116]
	str	r5, [r4, #228]
.L1358:
	add	r2, r0, r2
	ldrb	lr, [r2, #5]	@ zero_extendqisi2
	cmp	lr, #0
	beq	.L1361
	ldr	r3, [ip, #16]
	sub	r6, r3, #8
	cmp	r6, #1
	bhi	.L1361
	str	r3, [sp, #8]
	mov	r0, #1
	movw	r3, #12854
	str	lr, [sp, #4]
	str	r5, [sp]
	ldr	r2, .L1392
	ldr	r1, .L1392+4
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1382
.L1390:
	ldr	r3, [ip, #16]
	sub	r7, r3, #8
	cmp	r7, #1
	bhi	.L1362
	str	r3, [sp, #12]
	mov	r0, #1
	movw	r3, #12863
	str	r6, [sp, #8]
	str	r5, [sp, #4]
	str	lr, [sp]
	ldr	r2, .L1392
	ldr	r1, .L1392+8
	bl	dprint_vfmw
.L1386:
	mov	r0, #2
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1385:
	str	r5, [r4, #232]
	strb	r3, [r2, #10]
	b	.L1363
.L1391:
	ldr	r0, [r0, #260]
	cmp	r5, r0
	moveq	r0, r3
	movne	r0, #1
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1389:
	str	r3, [sp, #8]
	mov	r0, #1
	movw	r3, #12847
	str	lr, [sp, #4]
	str	r5, [sp]
	ldr	r2, .L1392
	ldr	r1, .L1392+12
	bl	dprint_vfmw
	mov	r0, #2
	b	.L1382
.L1393:
	.align	2
.L1392:
	.word	.LANCHOR0+360
	.word	.LC138
	.word	.LC139
	.word	.LC137
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
	ldr	r0, [r0, #2356]
	bl	BsGet
	cmp	r0, #0
	beq	.L1399
	ldr	r0, [r4, #2356]
	bl	BsBitsToNextByte
	subs	r1, r0, #0
	beq	.L1398
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r1, .L1400
	mov	r2, r0
	mov	r0, #19
	bl	dprint_vfmw
.L1398:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1399:
	ldr	r1, .L1400+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1401:
	.align	2
.L1400:
	.word	.LC141
	.word	.LC140
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
	ldr	r0, [r0, #132]
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
	ldr	r0, [r0, #132]
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
	bne	.L1441
.L1439:
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r6, #0
	str	r0, [r9, #4]
	ble	.L1410
	sub	r3, fp, #84
	sub	r7, fp, #92
	add	r10, r3, r6
	mov	r4, r3
	mov	r9, r7
.L1411:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4], #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r4, r10
	strb	r0, [r9], #1
	bne	.L1411
	cmp	r6, #7
	movle	r4, r6
	ble	.L1415
	b	.L1421
.L1414:
	cmp	r4, #8
	beq	.L1421
.L1415:
	mov	r1, #2
	ldr	r0, [r5, #2356]
	bl	BsGet
	add	r4, r4, #1
	cmp	r0, #0
	beq	.L1414
	ldr	r1, .L1443
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1410:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1421:
	mov	r10, #0
	b	.L1419
.L1418:
	add	r10, r10, #1
	cmp	r6, r10
	ble	.L1410
.L1419:
	cmp	r8, #0
	beq	.L1416
	sub	r3, fp, #84
	ldrb	r3, [r3, r10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1442
.L1416:
	ldrb	r3, [r7, r10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1418
	mov	r1, #8
	ldr	r0, [r5, #2356]
	bl	BsGet
	b	.L1418
.L1442:
	mov	r1, #2
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	mov	r4, #32
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2356]
	bl	BsGet
.L1417:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	subs	r4, r4, #1
	bne	.L1417
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #12
	ldr	r0, [r5, #2356]
	bl	BsGet
	b	.L1416
.L1441:
	mov	r1, #2
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	sub	r4, fp, #77
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r5, #2356]
	sub	r7, fp, #45
	bl	BsGet
	mov	r10, r0
.L1406:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	strb	r0, [r4, #1]!
	cmp	r4, r7
	bne	.L1406
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9, #1]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	sub	r3, r10, #4
	cmp	r3, #3
	bls	.L1407
	ldrb	r3, [fp, #-72]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1407
	ldrb	r3, [fp, #-71]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1407
	ldrb	r3, [fp, #-70]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1407
	ldrb	r3, [fp, #-69]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1407
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #11
	ldr	r0, [r5, #2356]
	bl	BsGet
	b	.L1409
.L1407:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #2
	ldr	r0, [r5, #2356]
	bl	BsGet
.L1409:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldrb	r2, [fp, #-75]	@ zero_extendqisi2
	ldrb	r3, [fp, #-74]	@ zero_extendqisi2
	mov	r1, #8
	str	r10, [r5, #300]
	str	r2, [r5, #304]
	str	r3, [r5, #308]
	b	.L1439
.L1444:
	.align	2
.L1443:
	.word	.LC142
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
	ldr	r9, .L1463
	add	r10, r0, #2208
	mov	r6, #0
	add	r3, r0, #2224
	str	r0, [fp, #-52]
	str	r3, [fp, #-48]
.L1446:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	beq	.L1454
	ldr	r3, [fp, #-52]
	mov	r8, r6, asl #9
	ldr	r7, [fp, #-48]
	sub	r8, r8, r6, asl #7
	add	r5, r3, #596
	mov	r4, #0
.L1452:
	cmp	r6, #0
	add	r0, r5, r8
	mov	r2, #64
	ldr	r3, [r9, #52]
	beq	.L1461
	cmp	r6, #3
	beq	.L1462
	ldr	ip, .L1463+4
	cmp	r4, #2
	ldr	r1, .L1463+8
	movhi	r1, ip
	blx	r3
.L1448:
	mov	r3, #16
	str	r3, [r7, #4]!
	ldr	r3, [r10]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1452
.L1454:
	add	r6, r6, #1
	ldr	r3, [fp, #-48]
	cmp	r6, #4
	add	r3, r3, #24
	str	r3, [fp, #-48]
	bne	.L1446
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1461:
	mov	r2, #16
	ldr	r1, .L1463+12
	mov	r0, r5
	blx	r3
	b	.L1448
.L1462:
	ldr	r0, .L1463+4
	cmp	r4, #0
	ldr	r1, .L1463+8
	mov	r2, #64
	movne	r1, r0
	add	r0, r5, #1152
	blx	r3
	b	.L1448
.L1464:
	.align	2
.L1463:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+376
	.word	.LANCHOR4
	.word	.LANCHOR0+440
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
	ldr	r7, [lr, #324]
	add	r3, r3, r2
	cmp	r7, #64
	mov	r6, r3, asl #4
	movcs	r7, #64
	mov	r8, r7, lsr #2
.L1466:
	cmp	r5, r8
	ldmcsfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r7, #0
	beq	.L1466
	add	r3, r5, r6
	ldrb	ip, [r1]	@ zero_extendqisi2
	mov	r4, r1
	mov	r2, #0
	add	r3, r0, r3, lsl #2
	ldr	lr, [r3, #596]
	orr	ip, lr, ip
	str	ip, [r3, #596]
.L1472:
	add	r2, r2, #1
	add	r3, r5, r6
	and	lr, r2, #3
	cmp	r2, r7
	add	r3, r0, r3, lsl #2
	mov	ip, lr, asl #3
	beq	.L1466
	ldrb	r9, [r4, #1]!	@ zero_extendqisi2
	cmp	lr, #3
	ldr	lr, [r3, #596]
	addeq	r5, r5, #1
	orr	ip, lr, r9, asl ip
	str	ip, [r3, #596]
	b	.L1472
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
	ldr	r3, [r0, #2388]
	mov	r7, r0
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1474
	ldr	r9, [r0, #2392]
	ldrb	r2, [r9, #21]	@ zero_extendqisi2
	cmp	r2, #0
	addne	r3, r9, #256
	strne	r3, [fp, #-48]
	beq	.L1491
.L1476:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1477
	ldr	r10, .L1492
	mov	r1, #0
	mov	r2, #1536
	add	r0, r7, #596
	add	r9, r7, #2208
	ldr	r8, [fp, #-48]
	ldr	r3, [r10, #48]
	mov	r6, r1
	blx	r3
.L1479:
	ldr	r3, [r9, #4]!
	cmp	r3, #0
	movne	r5, r8
	movne	r4, #0
	beq	.L1482
.L1480:
	mov	r3, r4
	mov	r1, r5
	mov	r2, r6
	mov	r0, r7
	bl	HEVC_CalScalingList
	ldr	r3, [r9]
	add	r4, r4, #1
	add	r5, r5, #64
	cmp	r3, r4
	bhi	.L1480
.L1482:
	add	r6, r6, #1
	add	r8, r8, #384
	cmp	r6, #4
	bne	.L1479
	ldr	r2, [fp, #-48]
	add	r0, r7, #2224
	ldr	r3, [r10, #52]
	add	r0, r0, #4
	add	r1, r2, #1536
	mov	r2, #96
	blx	r3
.L1474:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1491:
	ldrb	r2, [r3, #4]	@ zero_extendqisi2
	cmp	r2, #0
	addne	r3, r3, #432
	strne	r3, [fp, #-48]
	bne	.L1476
.L1477:
	mov	r0, r7
	bl	HEVC_SetDefaultScalingList
	b	.L1474
.L1493:
	.align	2
.L1492:
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
	b	.L1495
.L1497:
	.word	.L1501
	.word	.L1499
	.word	.L1499
	.word	.L1500
.L1499:
	ldr	r3, .L1505
	cmp	r1, #2
	add	r0, r3, #64
	movhi	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1501:
	ldr	r0, .L1505+4
	ldmfd	sp, {fp, sp, pc}
.L1500:
	ldr	r3, .L1505
	cmp	r1, #0
	add	r0, r3, #64
	movne	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L1495:
	ldr	r1, .L1505+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1506:
	.align	2
.L1505:
	.word	.LANCHOR4+80
	.word	.LANCHOR4+64
	.word	.LC143
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
	bne	.L1517
	sub	ip, r3, #1
	mov	r4, #1
	movs	ip, ip, asr #1
	beq	.L1509
.L1510:
	movs	ip, ip, asr #1
	add	r4, r4, #1
	bne	.L1510
.L1509:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	cmp	r5, #1
	movls	r10, #0
	movhi	r10, #1
	uxtb	r0, r0
	strb	r0, [r8]
	cmp	r0, #0
	cmpne	r5, #1
	bls	.L1514
	ldr	r3, [r7, #76]
	cmp	r3, #0
	beq	.L1514
	mov	r9, r8
	mov	r5, #0
.L1515:
	mov	r1, r4
	ldr	r0, [r6, #2356]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7, #76]
	cmp	r3, r5
	bhi	.L1515
.L1514:
	ldr	r5, [r7, #20]
	cmp	r5, #0
	beq	.L1532
.L1513:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1532:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r8, #1]
	cmp	r0, #0
	moveq	r10, #0
	andne	r10, r10, #1
	cmp	r10, #0
	beq	.L1513
	ldr	r3, [r7, #80]
	cmp	r3, #0
	beq	.L1513
	add	r8, r8, #128
.L1516:
	mov	r1, r4
	ldr	r0, [r6, #2356]
	bl	BsGet
	add	r5, r5, #1
	str	r0, [r8, #4]!
	ldr	r3, [r7, #80]
	cmp	r3, r5
	bhi	.L1516
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1517:
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
	ldr	r0, [r0, #2356]
	bl	BsResidBits
	subs	r3, r0, #0
	ble	.L1535
	ldr	r2, [r4, #2376]
	ldr	r0, [r2, #12]
	add	r0, r0, #3
	cmp	r3, r0
	movls	r0, #0
	movhi	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1535:
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
	ldr	r0, [r0, #2356]
	ldr	r2, [r0, #16]
	ldr	r3, [r0, #24]
	mov	r2, r2, asl #3
	cmp	r2, r3
	bls	.L1539
	mov	r1, #8
	bl	BsShow
	subs	r0, r0, #128
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1539:
	ldr	r1, .L1540
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L1541:
	.align	2
.L1540:
	.word	.LC144
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
.L1554:
	ldr	r3, [r6, #2376]
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
.L1543:
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r5, r0, ip
	cmp	r4, #0
	bne	.L1555
	ldr	r2, [r6, #2376]
	add	r1, r1, #1
	add	lr, r2, r5
	ldr	r2, [r2, #40]
	cmp	r2, r3
	beq	.L1556
	ldr	r2, [lr, #40]
	cmp	r2, r3
	sub	r3, r3, #1
	bne	.L1543
	ldr	r1, [lr, #64]
	ldr	r0, [r6, #252]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #2376]
	mov	r1, r4
	add	r5, r3, r5
	str	r4, [r5, #40]
	ldr	r2, [r6, #2376]
	ldr	r3, [r2, #8]
	sub	r3, r3, #1
	str	r3, [r2, #8]
	b	.L1554
.L1555:
	tst	r4, #1
	mov	r3, #1
	moveq	r2, r3
	bne	.L1550
.L1551:
	ands	r0, r4, r2, asl r3
	add	r3, r3, #1
	bne	.L1550
	cmp	r3, #8
	bne	.L1551
	ldr	r1, .L1557
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1556:
	ldr	r1, .L1557+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1550:
	ldr	ip, [r6, #2376]
	mov	r2, #0
	add	r1, r3, r1, lsl #3
	mov	r0, r2
	str	r2, [ip, #4]
	ldr	r3, [r6, #2376]
	str	r1, [r3, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1558:
	.align	2
.L1557:
	.word	.LC146
	.word	.LC145
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
	blt	.L1560
	add	r6, r5, #1
	mov	r0, r3
	mov	r1, r6
	bl	__aeabi_uidivmod
	ldr	r7, [r8, #2400]
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1561
	mov	r4, #0
	b	.L1563
.L1564:
	bl	__aeabi_uidivmod
	mov	r3, r1
	mov	r1, r1, asl #5
	mov	ip, r3, asl #7
	rsb	r2, r1, ip
	add	r2, r7, r2
	ldr	r2, [r2, #32]
	cmp	r2, #0
	beq	.L1561
.L1563:
	add	r4, r4, #1
	mov	r1, r6
	cmp	r4, r5
	add	r0, r3, r4
	ble	.L1564
.L1560:
	mvn	r0, #0
	str	r3, [r8, #148]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1561:
	cmp	r3, r6
	mov	r0, r3
	str	r3, [r8, #148]
	bcs	.L1574
	rsb	r1, r1, ip
	mov	r3, #1
	add	r7, r7, r1
	str	r3, [r7, #32]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1574:
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
	beq	.L1583
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	str	r3, [r5, #32]
	str	r3, [r5, #36]
.L1578:
	ldr	r3, [r4, #40]
	mov	r0, r6
	cmp	r3, #0
	beq	.L1577
	ldr	r1, [r4, #64]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #44]
	ldr	r3, [r4, #40]
	mov	r0, #7
	ldr	r2, .L1584
	ldr	r1, .L1584+4
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #40]
	str	r3, [r4, #56]
	str	r3, [r4, #44]
.L1577:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L1578
	ldr	r3, .L1584+8
	mov	r0, r5
	mov	r2, #96
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	bx	r3
.L1583:
	mov	r0, r5
	movw	r3, #14174
	ldr	r2, .L1584+12
	ldr	r1, .L1584+16
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L1585:
	.align	2
.L1584:
	.word	.LANCHOR0+456
	.word	.LC147
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC84
	.word	.LC85
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, [r0, #2388]
	mov	r6, r0
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r0, #2584]
	cmp	r3, #17
	bhi	.L1621
.L1587:
	add	r0, r6, #2800
	add	r1, r6, #2736
	add	r2, r6, #2592
	mov	lr, #0
	add	r0, r0, #8
	add	r1, r1, #4
	add	r2, r2, #12
	add	ip, r6, #2672
	mov	r3, lr
	mov	r7, #17
	str	lr, [r6, #2588]
	str	lr, [r6, #2600]
	str	lr, [r6, #2604]
	str	lr, [r6, #2596]
	str	lr, [r6, #2592]
.L1588:
	subs	r7, r7, #1
	str	r3, [r0, #4]!
	str	r3, [ip, #4]!
	str	r3, [r1, #4]!
	str	r3, [r2, #4]!
	bne	.L1588
	ldr	r9, .L1622
	add	r4, r6, #12800
.L1589:
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
	str	r3, [r4, #-8]
	mov	r8, #16
	str	r5, [r4, #-32]
	add	r4, r4, #712
	strb	r5, [r4, #-791]
	str	r5, [r4, #-784]
	strb	r5, [r4, #-790]
	str	r5, [r4, #-736]
	str	r2, [r4, #-772]
	str	r8, [r4, #-768]
	ldr	r3, .L1622
	bne	.L1589
	add	r0, r6, #12480
	ldr	r3, [r3, #48]
	mov	r2, #200
	mov	r1, r5
	add	r0, r0, #40
	blx	r3
	add	r2, r6, #12288
	add	r3, r6, #2400
	mov	r1, r5
	str	r8, [r2, #232]
	add	r3, r3, #12
	str	r5, [r2, #236]
	add	r2, r6, #2480
.L1591:
	str	r1, [r3, #4]!
	cmp	r3, r2
	mov	r0, #0
	bne	.L1591
	add	r1, r6, #2544
	add	lr, r6, #4096
	add	r1, r1, #4
	mov	ip, r0
	str	r0, [lr, #172]
.L1592:
	str	ip, [r2, #4]!
	cmp	r2, r1
	mov	r3, #0
	bne	.L1592
	str	r3, [lr, #176]
	ldr	r1, [r6, #184]
	cmp	r1, r3
	addne	r2, r6, #2128
	movne	r0, r3
	beq	.L1597
.L1596:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L1596
.L1597:
	ldr	r3, [r6, #168]
	cmp	r3, #0
	movne	r4, #0
	movne	r5, r4
	beq	.L1586
.L1602:
	ldr	r3, [r6, #2396]
	mov	r7, r4, asl #2
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L1598
	ldr	r3, [r6, #2376]
	cmp	r1, r3
	beq	.L1598
	ldr	r0, [r6, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r6, #2396]
	str	r5, [r3, r7]
	ldr	r3, [r6, #204]
	ldr	r2, [r6, #236]
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r6, #204]
	ldr	r3, [r6, #176]
	cmp	r2, #0
	subne	r2, r2, #1
	str	r2, [r6, #236]
	cmp	r3, #2
	subhi	r3, r3, #1
	movls	r3, #2
	str	r3, [r6, #176]
.L1598:
	ldr	r3, [r6, #168]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L1602
.L1586:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1621:
	mov	r4, #17
	ldr	r2, .L1622+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L1622+8
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r6, #2584]
	b	.L1587
.L1623:
	.align	2
.L1622:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+472
	.word	.LC148
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
	beq	.L1634
	ldr	r3, [r6, #2588]
	add	r8, r6, #2592
	cmp	r3, #0
	addeq	r8, r8, #12
	beq	.L1626
	add	r8, r8, #12
	mov	r3, #0
	mov	ip, #1
	mov	r1, r8
.L1628:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	streqb	ip, [r2, #2]
	ldr	r2, [r6, #2588]
	cmp	r2, r3
	bhi	.L1628
.L1626:
	mov	r4, r6
	mov	r7, #17
	mov	r5, #0
	mov	r3, #-2147483647
	str	r3, [r6, #212]
.L1633:
	ldr	r3, [r8, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L1629
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1629:
	ldr	r3, [r4, #2676]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1630
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1630:
	ldr	r3, [r4, #2744]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1631
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1631:
	ldr	r3, [r4, #2812]
	mov	r2, #1
	cmp	r3, #0
	beq	.L1632
	ldr	r1, [r3, #28]
	ldr	r0, [r6, #252]
	bl	FSP_ClearLogicFs
.L1632:
	subs	r7, r7, #1
	str	r5, [r4, #2812]
	str	r5, [r4, #2744]
	add	r4, r4, #4
	str	r5, [r4, #2672]
	str	r5, [r4, #2604]
	bne	.L1633
	mov	r0, r6
	bl	HEVC_InitDecBuffers
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1634:
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
	ldr	r0, [r0, #2376]
	cmp	r0, #0
	beq	.L1656
	ldr	r3, [r0, #44]
	cmp	r3, #4096
	ldmcsfd	sp, {r4, r5, fp, sp, pc}
	ldr	r1, .L1657
	mov	r0, #7
	bl	dprint_vfmw
	ldr	r3, [r4, #2376]
	ldr	ip, .L1657+4
	mov	r5, #0
	ldr	r2, [r3, #44]
	ldr	r0, [r3, #68]
	ldr	r1, [r3, #40]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #2376]
	mov	r0, #1
	ldr	r2, [r3, #92]
	ldr	r1, [r3, #64]
	str	r2, [r3, #64]
	ldr	r3, [r4, #2376]
	str	r5, [r3, #56]
	ldr	r3, [r4, #2376]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #68]
	rsb	r2, ip, r2
	str	r2, [r3, #40]
	ldr	r3, [r4, #2376]
	ldr	ip, [r3, #44]
	ldr	r2, [r3, #76]
	rsb	r2, ip, r2
	str	r2, [r3, #48]
	ldr	r3, [r4, #2376]
	ldr	r2, [r3, #44]
	ldr	ip, [r3, #72]
	add	r2, r2, ip
	str	r2, [r3, #44]
	ldr	r3, [r4, #2376]
	str	r0, [r3, #8]
	ldr	r0, [r4, #252]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #2376]
	str	r5, [r3, #68]
	ldr	r3, [r4, #2376]
	str	r5, [r3, #84]
	ldr	r3, [r4, #2376]
	str	r5, [r3, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1656:
	ldr	r1, .L1657+8
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L1658:
	.align	2
.L1657:
	.word	.LC150
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC149
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
	beq	.L1664
	ldr	ip, [r0, #2588]
	cmp	ip, #0
	beq	.L1664
	ldr	r3, [r0, #2608]
	cmp	r3, r1
	beq	.L1666
	add	r0, r0, #2608
	mov	r3, #0
	b	.L1661
.L1662:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1666
.L1661:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1662
.L1664:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1666:
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
	bls	.L1673
	movw	r0, #61166
	movt	r0, 65535
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1673:
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
	ldr	r1, .L1696
	mov	r4, r0
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2356]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	beq	.L1693
.L1679:
	mov	r1, #32
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r0, [r4, #2356]
	mov	r1, #32
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1693:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	mov	r6, r0
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r0, #8
	mov	r7, r0
	bhi	.L1694
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r0, #4
	ldrls	pc, [pc, r0, asl #2]
	b	.L1690
.L1678:
	.word	.L1679
	.word	.L1679
	.word	.L1680
	.word	.L1681
	.word	.L1682
.L1681:
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r0, #256
	mov	r8, r0
	bhi	.L1686
	cmp	r0, #0
	beq	.L1690
	add	r6, r6, #7
	add	r7, r7, #7
	bic	r6, r6, #7
	bic	r7, r7, #7
	mov	r5, #0
.L1688:
	mov	r1, r6
	ldr	r0, [r4, #2356]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, r7
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r5, r8
	bne	.L1688
.L1690:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1680:
	mov	r2, #1
	movs	r7, r2, asl r7
	addne	r6, r6, #7
	movne	r5, #0
	bicne	r6, r6, #7
	beq	.L1690
.L1684:
	add	r5, r5, #1
	mov	r1, r6
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r7, r5
	bne	.L1684
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1682:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r0, #255
	beq	.L1695
.L1689:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r0, [r4, #2356]
	mov	r1, #16
	bl	BsGet
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1695:
	mov	r1, #32
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L1689
.L1694:
	mov	r2, r0
	ldr	r1, .L1696+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1686:
	ldr	r1, .L1696+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1697:
	.align	2
.L1696:
	.word	.LC151
	.word	.LC152
	.word	.LC153
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
	ldr	r1, .L1708
	mov	r4, r0
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2356]
	mov	r1, #1
	bl	BsGet
	tst	r0, #255
	bne	.L1699
	mov	r1, #7
	ldr	r0, [r4, #2356]
	bl	BsGet
	sub	r3, r0, #3
	mov	r6, r0
	cmp	r3, #2
	bhi	.L1706
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #6
	mov	r5, r0
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	uxtb	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	clz	r5, r5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	mov	r5, r5, lsr #5
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r6, #5
	moveq	r5, #0
	cmp	r5, #0
	bne	.L1707
.L1702:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
.L1699:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r0, [r4, #2356]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1707:
	mov	r1, #4
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L1702
.L1706:
	mov	r2, r0
	ldr	r1, .L1708+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1709:
	.align	2
.L1708:
	.word	.LC154
	.word	.LC155
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
	bne	.L1714
	ldr	r1, .L1723
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1721
.L1712:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L1722
.L1713:
	ldr	r0, [r4, #2356]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1721:
	ldr	r1, [r5, #4]
	ldr	r0, [r4, #2356]
	add	r1, r1, #1
	bl	BsGet
	b	.L1712
.L1722:
	ldr	r1, [r5, #8]
	ldr	r0, [r4, #2356]
	add	r1, r1, #1
	bl	BsGet
	b	.L1713
.L1714:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1724:
	.align	2
.L1723:
	.word	.LC156
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
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	r0, [r5, #2356]
	ldr	r1, .L1732
	bl	HEVC_ue_v
	cmp	r0, #15
	bgt	.L1726
	cmp	r0, #0
	addge	r6, r0, #1
	movge	r4, #0
	blt	.L1730
.L1729:
	add	r4, r4, #1
	ldr	r1, .L1732+4
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r4, r6
	bne	.L1729
.L1730:
	ldr	r0, [r5, #2356]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1726:
	ldr	r1, .L1732+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1733:
	.align	2
.L1732:
	.word	.LC157
	.word	.LC159
	.word	.LC158
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
	ldr	r1, .L1763
	mov	r7, r2
	str	r6, [r4, #2920]
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	cmp	r0, #15
	bhi	.L1759
	mov	r1, #1
	strb	r1, [r4, #2913]
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r8, r6
	beq	.L1760
.L1737:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r4, #1
	strb	r0, [r9]
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2356]
	add	r1, r1, r4
	bl	BsGet
	subs	r3, r4, #1
	beq	.L1761
.L1739:
	cmp	r3, #1
	beq	.L1762
.L1743:
	cmp	r4, #1
	bhi	.L1742
.L1741:
	add	r4, r4, #1
	subs	r3, r4, #1
	bne	.L1739
.L1761:
	ldrb	r2, [r7]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1743
	ldr	r2, [r7, #24]
	cmn	r2, #1
	beq	.L1741
.L1750:
	mov	r6, #0
	b	.L1746
.L1745:
	ldr	r3, [r7, #24]
	add	r3, r3, #1
	cmp	r3, r6
	bls	.L1743
.L1746:
	ldr	r1, [r7, #12]
	add	r6, r6, #1
	ldr	r0, [r5, #2356]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2356]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	orrs	r3, r8, r3
	beq	.L1745
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2356]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #2356]
	add	r1, r1, #1
	bl	BsGet
	b	.L1745
.L1762:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1742
	ldr	r3, [r7, #24]
	cmn	r3, #1
	bne	.L1750
.L1742:
	ldr	r0, [r5, #2356]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1760:
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r8, r0
	cmp	r8, #0
	beq	.L1737
	ldr	r1, [r7, #16]
	ldr	r0, [r5, #2356]
	add	r1, r1, #1
	bl	BsGet
	ldr	r1, [r7, #20]
	ldr	r0, [r5, #2356]
	add	r1, r1, #1
	bl	BsGet
	b	.L1737
.L1759:
	mov	r2, r0
	ldr	r1, .L1763+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1764:
	.align	2
.L1763:
	.word	.LC160
	.word	.LC161
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
	ldr	r0, [r3, #2916]
	ldr	r2, [r3, #2920]
	add	r0, r0, #1
	str	r0, [r3, #2916]
	add	r2, r2, #1
	str	r2, [r3, #2920]
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1793
.L1766:
	ldrh	r3, [r5, #44]
	cmp	r3, #0
	beq	.L1768
	ldr	r1, [r5, #60]
	ldr	r0, [r4, #2356]
	add	r1, r1, #1
	bl	BsGet
	add	r0, r0, #1
	str	r0, [r6, #8]
	ldr	r1, [r5, #64]
	ldr	r0, [r4, #2356]
	add	r1, r1, #1
	bl	BsGet
	str	r0, [r6, #12]
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1769
.L1772:
	ldr	r2, [r4, #252]
	ldr	r3, .L1796
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L1794
.L1768:
	ldr	r0, [r4, #2356]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1793:
	mov	r1, #4
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #2
	str	r0, [r6]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #4]
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L1766
.L1794:
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L1768
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L1768
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_Get_Dpb_Output_Time
	b	.L1768
.L1769:
	ldr	r1, [r5, #52]
	ldr	r0, [r4, #2356]
	add	r1, r1, #1
	bl	BsGet
	ldrb	r3, [r5, #46]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1772
	ldrb	r3, [r5, #47]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1772
	ldr	r1, .L1796+4
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	mov	r1, #1
	mov	r8, r0
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r9, r0
	cmp	r9, #0
	bne	.L1795
.L1773:
	cmp	r8, #255
	bhi	.L1777
	add	r8, r8, #1
	mov	r7, #0
	b	.L1776
.L1775:
	cmp	r7, r8
	beq	.L1772
.L1776:
	ldr	r1, .L1796+8
	add	r7, r7, #1
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r9, #0
	bne	.L1775
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2356]
	add	r1, r1, #1
	bl	BsGet
	b	.L1775
.L1795:
	ldr	r1, [r5, #48]
	ldr	r0, [r4, #2356]
	add	r1, r1, #1
	bl	BsGet
	b	.L1773
.L1777:
	ldr	r1, .L1796+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1797:
	.align	2
.L1796:
	.word	s_pstVfmwChan
	.word	.LC162
	.word	.LC164
	.word	.LC163
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
	beq	.L1808
	ldr	r1, .L1812
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L1800
.L1804:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r5]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1800:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L1811
.L1801:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #3]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #4]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #5]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #4
	strb	r0, [r5, #6]
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #7]
	addne	r7, r5, #7
	movne	r6, #0
	beq	.L1806
.L1805:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L1805
.L1806:
	mov	r1, #4
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	strb	r0, [r5, #38]
	addne	r7, r5, #38
	movne	r6, #0
	beq	.L1804
.L1807:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r7, #15]
	ldrb	r3, [r5, #38]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L1807
	b	.L1804
.L1808:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1811:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r5, #1]
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L1801
.L1813:
	.align	2
.L1812:
	.word	.LC165
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
	beq	.L1821
	cmp	r2, #3
	bls	.L1824
	mov	r1, #8
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #16
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #2
	beq	.L1825
	cmp	r0, #4
	beq	.L1826
	subs	r6, r6, #4
	beq	.L1820
.L1819:
	add	r4, r4, #1
	mov	r1, #8
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r6, r4
	bne	.L1819
.L1820:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1825:
	add	r1, r5, #2928
	mov	r0, r5
	add	r1, r1, #8
	bl	HEVC_Sei_TSI
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1826:
	add	r1, r5, #2928
	mov	r0, r5
	add	r1, r1, #11
	bl	HEVC_Sei_Color_Volume_Reconstruction_Info
	cmn	r0, #1
	movne	r0, #0
	moveq	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1821:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1824:
	ldr	r1, .L1827
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1828:
	.align	2
.L1827:
	.word	.LC166
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
	bne	.L1874
.L1830:
	ldr	r1, .L1883
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4]
	bhi	.L1875
	ldr	r1, .L1883+4
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #16
	str	r0, [r4, #4]
	bhi	.L1876
	ldr	r6, [r4]
	add	r2, r0, r6
	str	r2, [r4, #8]
	cmp	r2, #16
	bhi	.L1853
	cmp	r6, #0
	addne	r10, r4, #28
	addne	r9, r4, #11
	movne	r7, #0
	movne	r8, r7
	bne	.L1857
	b	.L1855
.L1856:
	str	r8, [r10, #4]!
	ldr	r0, [r5, #2356]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r6, [r4]
	cmp	r6, r7
	bls	.L1877
.L1857:
	ldr	r1, .L1883+8
	add	r7, r7, #1
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	mov	r1, #1
	cmp	r0, #32768
	mvn	r3, r0
	add	r8, r8, r3
	bcc	.L1856
	mov	r2, r0
	ldr	r1, .L1883+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1874:
	mov	r1, #1
	ldr	r0, [r0, #2356]
	bl	BsGet
	cmp	r0, #0
	beq	.L1830
	ldr	r7, [r9, #176]
	cmp	r7, r6
	movne	r0, #0
	beq	.L1878
.L1831:
	sub	r3, r6, #1
	rsb	r8, r0, r3
	cmp	r8, r3
	bhi	.L1879
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	r1, .L1883+16
	mov	r6, r0
	ldr	r0, [r5, #2356]
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
	bhi	.L1880
	add	r6, r8, #2192
	mov	r10, #0
	add	r6, r6, #4
	str	r10, [fp, #-48]
	add	r6, r9, r6
	str	r10, [fp, #-52]
	mov	r7, r10
	b	.L1840
.L1835:
	sub	r3, r0, #1
	cmp	r3, #1
	bls	.L1881
.L1836:
	add	r3, r9, r8
	add	r10, r10, #1
	add	r6, r6, #4
	ldr	r3, [r3, #2172]
	cmp	r3, r10
	bcc	.L1882
.L1840:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r0, #0
	bne	.L1835
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r0, r0, asl #1
	sub	r3, r0, #1
	cmp	r3, #1
	bhi	.L1836
.L1881:
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
	b	.L1836
.L1882:
	ldr	r3, [fp, #-52]
	cmp	r7, #16
	ldr	r2, [fp, #-48]
	str	r7, [r4, #8]
	str	r3, [r4]
	str	r2, [r4, #4]
	bhi	.L1841
	cmp	r3, #16
	bhi	.L1841
	cmp	r2, #16
	bhi	.L1841
	cmp	r7, #1
	subhi	r7, r7, #1
	addhi	r8, r4, #32
	addhi	r6, r4, #12
	movhi	r5, #0
	bls	.L1847
.L1846:
	ldr	ip, [r8, #4]!
	cmp	r5, #0
	ldrb	lr, [r6, #1]!	@ zero_extendqisi2
	mov	r2, r5
	movge	r1, r8
	movge	r3, r6
	blt	.L1849
.L1845:
	ldr	r0, [r1, #-4]!
	sub	r3, r3, #1
	cmp	ip, r0
	strlt	r0, [r1, #4]
	ldrltb	r0, [r3]	@ zero_extendqisi2
	strltb	r0, [r3, #1]
	strlt	ip, [r1]
	strltb	lr, [r3]
	subs	r2, r2, #1
	bpl	.L1845
.L1849:
	add	r5, r5, #1
	cmp	r5, r7
	bne	.L1846
.L1847:
	ldr	r3, [fp, #-52]
	movs	r6, r3, lsr #1
	beq	.L1844
	ldr	r3, [fp, #-52]
	add	r0, r4, #32
	mov	r1, #0
	add	r2, r3, #7
	add	r3, r3, #11
	add	r3, r4, r3
	add	r2, r4, r2, lsl #2
	add	r4, r4, #12
.L1850:
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
	bne	.L1850
.L1844:
	mov	r0, #0
.L1832:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1877:
	ldr	r2, [r4, #8]
.L1855:
	cmp	r2, r6
	bls	.L1844
	add	r8, r6, #7
	add	r9, r6, #11
	add	r9, r4, r9
	mov	r7, #0
	add	r8, r4, r8, lsl #2
.L1858:
	ldr	r1, .L1883+20
	add	r6, r6, #1
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	mov	r1, #1
	add	r0, r0, r1
	add	r7, r7, r0
	str	r7, [r8, #4]!
	ldr	r0, [r5, #2356]
	bl	BsGet
	strb	r0, [r9, #1]!
	ldr	r3, [r4, #8]
	cmp	r3, r6
	bhi	.L1858
	b	.L1844
.L1878:
	ldr	r1, .L1883+24
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	add	r2, r0, #1
	cmp	r7, r2
	bcs	.L1831
	mov	r3, r7
	ldr	r1, .L1883+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1832
.L1841:
	ldr	r1, .L1883+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1832
.L1876:
	ldr	r2, [r4]
	mov	r0, #1
	ldr	r1, .L1883+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1832
.L1879:
	mov	r2, r8
	ldr	r1, .L1883+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1832
.L1880:
	ldr	r1, .L1883+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1832
.L1875:
	mov	r2, r0
	ldr	r1, .L1883+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1832
.L1853:
	mov	r3, #16
	ldr	r1, .L1883+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1832
.L1884:
	.align	2
.L1883:
	.word	.LC173
	.word	.LC175
	.word	.LC178
	.word	.LC179
	.word	.LC170
	.word	.LC180
	.word	.LC167
	.word	.LC168
	.word	.LC172
	.word	.LC176
	.word	.LC169
	.word	.LC171
	.word	.LC174
	.word	.LC177
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
	beq	.L1907
	cmp	r2, #0
	bne	.L1934
.L1890:
	add	r5, r9, #24
	mov	r7, #0
.L1902:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	uxtb	r4, r0
	cmp	r4, #0
	movne	r3, #0
	strne	r3, [r5]
	beq	.L1935
.L1905:
	ldr	r1, .L1940
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
.L1893:
	ldr	r1, .L1940+4
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	mov	r2, r0
	str	r0, [r5]
.L1894:
	cmp	r2, #31
	bhi	.L1936
.L1895:
	mov	r4, #0
.L1906:
	cmp	r4, #0
	beq	.L1937
	cmp	r4, #1
	beq	.L1932
.L1901:
	add	r4, r4, #1
	cmp	r4, #2
	bne	.L1906
.L1900:
	add	r7, r7, #1
	add	r5, r5, #4
	cmp	r8, r7
	bcs	.L1902
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1936:
	ldr	r1, .L1940+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5]
	b	.L1895
.L1935:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	str	r4, [r5]
	tst	r0, #255
	bne	.L1905
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L1893
	ldr	r2, [r5]
	b	.L1894
.L1934:
	mov	r1, #1
	ldr	r0, [r0, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r9]
	ldr	r0, [r6, #2356]
	bl	BsGet
	strb	r0, [r9, #1]
	ldrh	r3, [r9]
	cmp	r3, #0
	beq	.L1890
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r9, #2]
	cmp	r0, #0
	bne	.L1938
.L1888:
	mov	r1, #4
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r1, #4
	ldr	r0, [r6, #2356]
	bl	BsGet
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1939
.L1889:
	mov	r1, #5
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #12]
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r1, #5
	str	r0, [r9, #16]
	ldr	r0, [r6, #2356]
	bl	BsGet
	str	r0, [r9, #20]
	b	.L1890
.L1907:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1939:
	mov	r1, #4
	ldr	r0, [r6, #2356]
	bl	BsGet
	b	.L1889
.L1938:
	mov	r1, #8
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r1, #5
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r1, #1
	str	r0, [r9, #4]
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r1, #5
	strb	r0, [r9, #3]
	ldr	r0, [r6, #2356]
	bl	BsGet
	str	r0, [r9, #20]
	b	.L1888
.L1937:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1909
	mov	r4, #1
.L1932:
	ldrb	r3, [r9, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1900
.L1909:
	mov	r10, #0
	b	.L1904
.L1903:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	ldr	r3, [r5]
	cmp	r3, r10
	bcc	.L1901
.L1904:
	ldr	r1, .L1940+12
	add	r10, r10, #1
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L1940+16
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	ldrb	r3, [r9, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1903
	ldr	r1, .L1940+20
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L1940+24
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	b	.L1903
.L1941:
	.align	2
.L1940:
	.word	.LC181
	.word	.LC182
	.word	.LC183
	.word	.LC184
	.word	.LC185
	.word	.LC186
	.word	.LC187
	UNWIND(.fnend)
	.size	HEVC_DecHrdParam, .-HEVC_DecHrdParam
	.align	2
	.global	HEVC_ProcessVPS
	.type	HEVC_ProcessVPS, %function
HEVC_ProcessVPS:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 56
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
	mov	r5, r0
	mov	r6, r1
	ldr	r0, [r0, #2356]
	mov	r1, #1
	bl	BsGet
	mov	r1, #1
	strb	r0, [r6, #3]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r2, r0
	cmp	r2, #1
	beq	.L1943
	ldr	r1, .L1994
	mov	r0, #1
	bl	dprint_vfmw
.L1943:
	mov	r1, #6
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r0, #63
	str	r0, [r6, #8]
	bhi	.L1987
	mov	r1, #3
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r0, #7
	mov	r7, r0
	bhi	.L1988
	str	r0, [r6, #12]
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #16
	strb	r0, [r6, #1]
	ldr	r0, [r5, #2356]
	bl	BsGet
	movw	r3, #65535
	cmp	r0, r3
	bne	.L1989
	mov	r3, r7
	mov	r2, #1
	add	r1, r6, #124
	mov	r0, r5
	bl	HEVC_DecPTL
	subs	r4, r0, #0
	bne	.L1990
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r7, #0
	addge	r8, r6, #24
	addge	r9, r7, #1
	uxtb	r10, r0
	bge	.L1955
	b	.L1953
.L1952:
	add	r4, r4, #1
	cmp	r4, r9
	beq	.L1953
.L1955:
	ldr	r1, .L1994+4
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L1994+8
	add	r0, r0, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L1994+12
	str	r0, [r8, #32]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r10, #0
	str	r0, [r8, #64]
	bne	.L1952
	add	r3, r4, #1
	cmp	r7, r3
	blt	.L1953
	add	r1, r4, #7
	add	r1, r6, r1, lsl #2
.L1954:
	ldr	r2, [r6, #28]
	add	r3, r3, #1
	cmp	r9, r3
	str	r2, [r1, #4]!
	ldr	r2, [r6, #60]
	str	r2, [r1, #32]
	ldr	r2, [r6, #92]
	str	r2, [r1, #64]
	bne	.L1954
.L1953:
	mov	r1, #6
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	r1, .L1994+16
	str	r0, [r6, #16]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #20]
	bcs	.L1991
	cmp	r0, #0
	movgt	r8, #1
	ble	.L1957
.L1959:
	mov	r4, #0
.L1958:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	ip, [r6, #16]
	add	r4, r4, #1
	cmp	r4, ip
	bls	.L1958
	ldr	r3, [r6, #20]
	add	r8, r8, #1
	cmp	r3, r8
	bge	.L1959
.L1957:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L1966
	mov	r1, #32
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #32
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L1992
.L1963:
	ldr	r1, .L1994+20
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #1024
	str	r0, [r6, #24]
	bhi	.L1964
	cmp	r0, #0
	ble	.L1966
	ldr	r1, .L1994+24
	mov	r4, #0
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	mov	r0, #1
.L1971:
	uxtb	r2, r0
	sub	r1, fp, #100
	mov	r3, r7
	mov	r0, r5
	bl	HEVC_DecHrdParam
	add	r4, r4, #1
	ldr	r1, .L1994+24
	cmp	r0, #0
	bne	.L1993
	ldr	r3, [r6, #24]
	cmp	r3, r4
	ble	.L1966
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r4, #0
	mov	r0, #1
	beq	.L1971
	mov	r1, r0
	ldr	r0, [r5, #2356]
	bl	BsGet
	b	.L1971
.L1966:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L1983
.L1962:
	mov	r0, #0
.L1984:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1970:
	ldr	r0, [r5, #2356]
	bl	BsGet
.L1983:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L1970
	b	.L1962
.L1993:
	ldr	r1, .L1994+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1992:
	ldr	r1, .L1994+32
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	b	.L1963
.L1989:
	ldr	r1, .L1994+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1984
.L1987:
	mov	r2, r0
	ldr	r1, .L1994+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1984
.L1990:
	ldr	r1, .L1994+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1984
.L1988:
	mov	r2, r0
	ldr	r1, .L1994+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1984
.L1991:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L1994+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1984
.L1964:
	mov	r2, r0
	mov	r3, #1024
	ldr	r1, .L1994+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1984
.L1995:
	.align	2
.L1994:
	.word	.LC188
	.word	.LC194
	.word	.LC195
	.word	.LC196
	.word	.LC193
	.word	.LC199
	.word	.LC201
	.word	.LC202
	.word	.LC198
	.word	.LC191
	.word	.LC189
	.word	.LC192
	.word	.LC190
	.word	.LC197
	.word	.LC200
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r1, #4
	mov	r5, r0
	ldr	r0, [r0, #2356]
	bl	BsGet
	cmp	r0, #15
	mov	r6, r0
	bhi	.L2002
	ldr	r3, [r5, #2360]
	mov	r4, r0, asl #7
	add	r4, r4, r0, lsl #2
	add	r2, r3, r4
	ldrb	r8, [r3, r4]	@ zero_extendqisi2
	cmp	r8, #0
	bne	.L2003
	str	r0, [r2, #4]
	mov	r0, r5
	ldr	r1, [r5, #2360]
	add	r1, r1, r4
	bl	HEVC_ProcessVPS
	subs	r7, r0, #0
	bne	.L2004
	ldr	r3, [r5, #2360]
	mov	r2, #1
	add	r3, r3, r4
	strb	r2, [r3, #2]
	ldr	r3, [r5, #2360]
	strb	r2, [r3, r4]
.L1998:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2003:
	ldr	r9, .L2006
	mov	r2, #132
	ldr	r8, .L2006+4
	mov	r1, #0
	ldr	r0, .L2006+8
	ldr	r3, [r9, #48]
	blx	r3
	ldr	r1, .L2006+8
	mov	r0, r5
	str	r6, [r8, #-3460]
	bl	HEVC_ProcessVPS
	subs	r7, r0, #0
	bne	.L2005
	ldr	r0, [r5, #2360]
	mov	r3, #1
	ldr	ip, [r9, #56]
	mov	r2, #132
	add	r0, r0, r4
	strb	r3, [r8, #-3462]
	strb	r3, [r8, #-3464]
	ldr	r1, .L2006+8
	blx	ip
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2005:
	mov	r2, r6
	ldr	r1, .L2006+12
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L1998
.L2002:
	ldr	r1, .L2006+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L1998
.L2004:
	mov	r2, r6
	ldr	r1, .L2006+20
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	ldr	r3, [r5, #2360]
	mov	r2, #1
	add	r3, r3, r4
	strb	r2, [r3, #2]
	ldr	r3, [r5, #2360]
	strb	r8, [r3, r4]
	b	.L1998
.L2007:
	.align	2
.L2006:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR5
	.word	.LANCHOR5-3464
	.word	.LC204
	.word	.LC203
	.word	.LC205
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
	ldr	r0, [r0, #2356]
	mov	r1, #1
	mov	r6, r2
	bl	BsGet
	tst	r0, #255
	bne	.L2052
.L2010:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L2053
.L2012:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L2054
.L2014:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L2055
.L2016:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #2]
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L2017
	ldr	r1, .L2061
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r6, #60]
	cmp	r3, #3
	bhi	.L2056
	ldr	r1, .L2061+4
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L2061+8
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L2061+12
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
.L2017:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L2020
	mov	r1, #32
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #32
	str	r0, [r5, #36]
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r2, [r5, #36]
	cmp	r2, #0
	str	r0, [r5, #40]
	bne	.L2057
.L2021:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L2058
.L2022:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	bne	.L2059
.L2020:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r1, .L2061+16
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r0, #4096
	bcs	.L2060
.L2023:
	ldr	r1, .L2061+20
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L2061+24
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L2061+28
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r0, [r4, #2356]
	ldr	r1, .L2061+32
	bl	HEVC_ue_v
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2052:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r0, #255
	str	r0, [r5, #8]
	bne	.L2010
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	str	r0, [r5, #12]
	ldr	r0, [r4, #2356]
	bl	BsGet
	str	r0, [r5, #16]
	b	.L2010
.L2055:
	ldr	r1, .L2061+36
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L2061+40
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	b	.L2016
.L2054:
	mov	r1, #3
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #20]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5]
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	beq	.L2014
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #24]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #28]
	ldr	r0, [r4, #2356]
	bl	BsGet
	str	r0, [r5, #32]
	b	.L2014
.L2053:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L2012
.L2059:
	ldr	r3, [r6, #52]
	add	r1, r5, #44
	mov	r2, #1
	mov	r0, r4
	bl	HEVC_DecHrdParam
	cmp	r0, #0
	beq	.L2020
	ldr	r1, .L2061+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2058:
	ldr	r1, .L2061+48
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	b	.L2022
.L2057:
	ldr	r3, .L2061+52
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
	b	.L2021
.L2060:
	ldr	r1, .L2061+56
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2023
.L2056:
	ldr	r1, .L2061+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2062:
	.align	2
.L2061:
	.word	.LC208
	.word	.LC210
	.word	.LC211
	.word	.LC212
	.word	.LC215
	.word	.LC217
	.word	.LC218
	.word	.LC219
	.word	.LC220
	.word	.LC206
	.word	.LC207
	.word	.LC214
	.word	.LC213
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC216
	.word	.LC209
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
	bls	.L2068
	mvn	r0, #-2147483648
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2068:
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
	ldr	r1, .L2081
	mov	r6, r0
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	ldr	r0, [r6, #2356]
	ldr	r1, .L2081+4
	bl	HEVC_ue_v
	cmp	r0, #1024
	mov	r7, r0
	bhi	.L2070
	cmp	r0, #0
	movne	r4, #0
	beq	.L2076
.L2075:
	mov	r1, #6
	ldr	r0, [r6, #2356]
	bl	BsGet
	mov	r1, #3
	mov	r5, r0
	ldr	r0, [r6, #2356]
	sub	r5, r5, #19
	bl	BsGet
	cmp	r5, #1
	ldr	r1, .L2081+8
	bls	.L2073
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
.L2073:
	cmp	r4, #0
	ldr	r1, .L2081+12
	add	r4, r4, #1
	beq	.L2074
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
.L2074:
	cmp	r4, r7
	bne	.L2075
.L2076:
	ldr	r0, [r6, #2356]
	bl	BsToNextByte
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2070:
	ldr	r1, .L2081+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2082:
	.align	2
.L2081:
	.word	.LC221
	.word	.LC222
	.word	.LC224
	.word	.LC225
	.word	.LC223
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
	beq	.L2085
	ldr	r1, .L2086
	ldr	r0, [r0, #2356]
	bl	HEVC_se_v
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r0, [r4, #2356]
	bl	BsToNextByte
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2085:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2087:
	.align	2
.L2086:
	.word	.LC226
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
	beq	.L2104
	ldr	r1, .L2116
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L2090
.L2102:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r8]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2090:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r1, r0
	cmp	r1, #1
	beq	.L2114
.L2091:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2356]
	mov	r7, #3
	bl	BsGet
.L2093:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	beq	.L2096
	add	r6, r0, #1
	mov	r5, #0
.L2095:
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	add	r5, r5, #1
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r5, r6
	bne	.L2095
.L2096:
	subs	r7, r7, #1
	bne	.L2093
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #1
	beq	.L2115
.L2097:
	add	r10, r8, #42
	add	r7, r8, #39
	mov	r9, r10
.L2101:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #1]!
	cmp	r0, #0
	beq	.L2103
	mov	r6, r9
	mov	r5, #0
.L2100:
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #16
	add	r5, r5, #1
	strh	r0, [r6, #2]!	@ movhi
	ldr	r0, [r4, #2356]
	bl	BsGet
	strh	r0, [r6, #198]	@ movhi
	ldrb	r3, [r7]	@ zero_extendqisi2
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L2100
.L2103:
	cmp	r7, r10
	add	r9, r9, #66
	bne	.L2101
	b	.L2102
.L2104:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2115:
	mov	r1, #4
	ldr	r0, [r4, #2356]
	bl	BsGet
	add	r7, r8, #36
	mov	r5, r8
.L2098:
	add	r6, r5, #12
.L2099:
	ldr	r1, .L2116+4
	ldr	r0, [r4, #2356]
	bl	HEVC_se_v
	str	r0, [r5, #4]!
	cmp	r5, r6
	bne	.L2099
	cmp	r7, r5
	bne	.L2098
	b	.L2097
.L2114:
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	strb	r0, [r8, #1]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L2091
.L2117:
	.align	2
.L2116:
	.word	.LC227
	.word	.LC228
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
	ldr	ip, [r0, #2376]
	mov	r4, r0
	ldr	r6, [fp, #4]
	ldr	ip, [ip, #16]
	cmp	ip, #39
	beq	.L2164
	cmp	r3, #5
	beq	.L2147
	cmp	r3, #132
	beq	.L2148
	cmp	r6, #0
	movne	r5, #0
	beq	.L2141
.L2150:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r5, r6
	bne	.L2150
	b	.L2141
.L2147:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	bne	.L2144
.L2141:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_More_Data_In_Payload
	cmp	r0, #0
	bne	.L2151
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2151:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_Sei_Payload_Extension_Present
	cmp	r0, #0
	bne	.L2165
.L2152:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L2153
.L2154:
	ldr	r0, [r4, #2356]
	bl	BsGet
.L2153:
	ldr	r0, [r4, #2356]
	bl	BsIsByteAligned
	mov	r1, #1
	cmp	r0, #0
	beq	.L2154
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2164:
	cmp	r3, #147
	ldrls	pc, [pc, r3, asl #2]
	b	.L2120
.L2122:
	.word	.L2121
	.word	.L2123
	.word	.L2120
	.word	.L2120
	.word	.L2124
	.word	.L2125
	.word	.L2126
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2127
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2128
	.word	.L2120
	.word	.L2129
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2130
	.word	.L2131
	.word	.L2132
	.word	.L2133
	.word	.L2120
	.word	.L2134
	.word	.L2135
	.word	.L2120
	.word	.L2120
	.word	.L2136
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2120
	.word	.L2137
	.word	.L2120
	.word	.L2138
	.word	.L2120
	.word	.L2120
	.word	.L2139
.L2148:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Decoded_Picture_Hash
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2165:
	ldr	r1, .L2166
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	b	.L2152
.L2139:
	add	r1, r1, #616
	add	r1, r1, #2
	bl	HEVC_Sei_HLGHDR_Comapitibility_Info
	cmp	r0, #0
	beq	.L2141
.L2144:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2121:
	add	r2, r2, #2096
	add	r2, r2, #12
	bl	HEVC_Sei_Buf_Period
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2123:
	add	r2, r2, #2064
	add	r1, r1, #8
	bl	HEVC_Sei_Pic_Timming
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2124:
	add	r1, r1, #56
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Registered_Itu_T_T35
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2125:
	add	r1, r1, #568
	mov	r2, r6
	bl	HEVC_Sei_User_Data_Unregistered
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2126:
	add	r1, r1, #568
	bl	HEVC_Sei_Recovery_Point
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2127:
	add	r1, r1, #616
	add	r1, r1, #3
	bl	HEVC_Sei_Tone_Mapping_Info
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2128:
	add	r1, r1, #568
	bl	HEVC_Sei_Frame_Packing_Arrangement
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2129:
	add	r1, r1, #568
	bl	HEVC_Sei_Display_Orientation
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2130:
	add	r1, r1, #616
	mov	r2, r6
	add	r1, r1, #3
	bl	HEVC_Sei_Structure_Of_Pictures_Info
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2131:
	add	r1, r1, #568
	bl	HEVC_Sei_Active_Param_sets
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2132:
	add	r2, r2, #2096
	add	r1, r1, #568
	add	r2, r2, #12
	bl	HEVC_Sei_Dec_Unit_Info
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2133:
	add	r1, r1, #568
	bl	HEVC_Sei_Temporal_Sub_Layer_Zero_Index
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2134:
	mov	r3, r6
	bl	HEVC_Sei_Scalable_Nesting
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2135:
	cmn	r1, #568
	cmpne	r0, #0
	beq	.L2144
	mov	r1, #1
	ldr	r0, [r0, #2356]
	bl	BsGet
	b	.L2141
.L2136:
	add	r1, r1, #568
	bl	HEVC_Sei_Mastering_Display_Colour_Volume
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2137:
	add	r1, r1, #128
	bl	HEVC_Sei_Color_Remapping_Info
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2138:
	add	r1, r1, #612
	bl	HEVC_Sei_Content_Light_Level_Information
	cmp	r0, #0
	beq	.L2141
	b	.L2144
.L2120:
	cmp	r6, #0
	movne	r5, #0
	beq	.L2141
.L2145:
	add	r5, r5, #1
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r5, r6
	bne	.L2145
	b	.L2141
.L2167:
	.align	2
.L2166:
	.word	.LC229
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
	ldr	r0, [r0, #2356]
	b	.L2169
.L2171:
	bl	BsSkip
	ldr	r0, [r4, #2356]
	add	r5, r5, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2
	bhi	.L2177
.L2169:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2356]
	beq	.L2171
	bl	BsGet
	mov	r8, #0
	mov	r9, r0
	ldr	r0, [r4, #2356]
	b	.L2172
.L2173:
	bl	BsSkip
	ldr	r0, [r4, #2356]
	add	r8, r8, #255
	ldr	r3, [r0, #24]
	ldr	r2, [r0, #16]
	add	r1, r3, #8
	cmp	r1, r2
	bhi	.L2178
.L2172:
	mov	r1, #8
	bl	BsShow
	mov	r1, #8
	cmp	r0, #255
	ldr	r0, [r4, #2356]
	beq	.L2173
	bl	BsGet
	add	r3, r9, r5
	mov	r2, r7
	mov	r1, r6
	add	r8, r0, r8
	mov	r0, r4
	str	r8, [sp]
	bl	HEVC_Sei_Payload
	cmp	r0, #0
	bne	.L2179
.L2170:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2177:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5022
	ldr	r1, .L2180
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2178:
	str	r2, [sp]
	mov	r0, #1
	movw	r2, #5043
	ldr	r1, .L2180
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2179:
	ldr	r1, .L2180+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2170
.L2181:
	.align	2
.L2180:
	.word	.LC230
	.word	.LC231
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
	beq	.L2188
	ldr	r5, [r0, #2372]
	add	r6, r0, #2880
	cmp	r5, #0
	bne	.L2191
	b	.L2194
.L2186:
	ldr	r0, [r4, #2356]
	bl	BsIsByteAligned
	cmp	r0, #0
	mov	r0, r4
	beq	.L2195
	bl	HEVC_More_Rbsp_Data
	cmp	r0, #0
	beq	.L2196
.L2191:
	mov	r2, r5
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	beq	.L2186
	ldr	r1, .L2198
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2196:
	ldr	r0, [r4, #2356]
	mov	r1, #8
	bl	BsGet
	cmp	r0, #128
	bne	.L2197
.L2188:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2195:
	ldr	r1, .L2198+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2197:
	mov	r2, r0
	ldr	r1, .L2198+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2194:
	ldr	r1, .L2198+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2199:
	.align	2
.L2198:
	.word	.LC233
	.word	.LC234
	.word	.LC235
	.word	.LC232
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
	ldr	r0, [r0, #2356]
	mov	r1, #1
	mov	r7, r2
	bl	BsGet
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	tst	r0, #255
	ldr	r0, [r4, #2356]
	beq	.L2201
	bl	BsGet
	ldr	r1, .L2217
	mov	r5, r0
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r0, #63
	mov	r8, r0
	bhi	.L2214
	uxtb	r5, r5
	cmp	r0, r5
	bcc	.L2207
.L2206:
	mov	r1, #3
	ldr	r0, [r4, #2356]
	bl	BsGet
	add	r5, r5, #1
	ldr	r1, .L2217+4
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r8, r5
	bcs	.L2206
.L2207:
	ldr	r0, [r4, #2356]
	bl	BsToNextByte
	b	.L2205
.L2210:
	bl	HEVC_MoreRbspData
	cmp	r0, #0
	beq	.L2215
.L2205:
	mov	r2, r7
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_SeiMessage
	cmp	r0, #0
	mov	r0, r4
	beq	.L2210
	ldr	r1, .L2217+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2201:
	bl	BsGet
	uxtb	r5, r0
	cmp	r5, #0
	bne	.L2207
	mov	r1, #3
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r1, .L2217+12
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r0, #63
	addls	r8, r0, #1
	bhi	.L2216
.L2209:
	add	r5, r5, #1
	mov	r1, #6
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r5, r8
	bne	.L2209
	b	.L2207
.L2215:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2214:
	mov	r2, #64
	ldr	r1, .L2217+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2216:
	ldr	r1, .L2217+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2218:
	.align	2
.L2217:
	.word	.LC236
	.word	.LC238
	.word	.LC233
	.word	.LC239
	.word	.LC237
	.word	.LC240
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
	ldr	r3, .L2257
	mov	r6, r0
	add	r9, r6, #2208
	mov	r4, r1
	str	r1, [fp, #-68]
	ldr	r3, [r3, #52]
	mov	r2, #64
	add	r1, r1, #1216
	add	r0, r4, #1344
	blx	r3
	add	r3, r4, #1536
	str	r4, [fp, #-60]
	str	r3, [fp, #-64]
	mov	r3, #0
	str	r3, [fp, #-52]
.L2220:
	ldr	r3, [r9, #4]!
	cmp	r3, #0
	beq	.L2240
	ldr	r3, [fp, #-64]
	ldr	r7, [fp, #-60]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [fp, #-48]
.L2239:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	ldr	r5, [r9, #-1888]
	ldr	r3, [fp, #-52]
	cmp	r5, #64
	movge	r5, #64
	cmp	r3, #0
	uxtb	r0, r0
	beq	.L2221
	cmp	r0, #0
	add	r4, r6, #340
	beq	.L2253
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	bls	.L2246
	ldr	r1, .L2257+4
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #254
	bhi	.L2254
	ldr	r3, [fp, #-56]
	add	r10, r0, #8
	str	r10, [r3]
.L2232:
	cmp	r5, #0
	ble	.L2231
	sub	r4, r4, #4
	mov	r8, #0
	b	.L2236
.L2235:
	mov	r10, r10, lsr #24
	ldr	r2, [r4, #4]!
	add	r3, r3, r10
	cmp	r8, r5
	uxtb	r3, r3
	rsb	r10, r10, r3
	strb	r10, [r7, r2]
	beq	.L2231
.L2236:
	ldr	r1, .L2257+8
	add	r8, r8, #1
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r3, r10, r0
	add	r0, r0, #128
	add	r3, r3, #256
	cmp	r0, #255
	mov	r10, r3, asr #31
	bls	.L2235
	ldr	r1, .L2257+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2251:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2241:
	ldr	r1, .L2257+16
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	cmp	r0, r3
	bhi	.L2243
	ldr	r3, [fp, #-48]
	rsb	r3, r0, r3
	uxtb	r3, r3
.L2226:
	ldr	r2, [fp, #-48]
	cmp	r3, r2
	beq	.L2255
.L2228:
	ldr	r2, [fp, #-52]
	mov	r1, r2, asl #3
	sub	r1, r1, r2, asl #1
	ldr	r2, [fp, #-68]
	add	r3, r1, r3
	add	r1, r2, r3, lsl #6
.L2229:
	cmp	r1, #0
	beq	.L2256
	ldr	r3, .L2257
	mov	r2, r5
	mov	r0, r7
	ldr	r3, [r3, #52]
	blx	r3
.L2231:
	ldr	r3, [fp, #-48]
	add	r3, r3, #1
	str	r3, [fp, #-48]
	cmp	r3, #6
	beq	.L2240
	ldr	r2, [fp, #-56]
	add	r7, r7, #64
	ldr	r3, [r9]
	add	r2, r2, #4
	str	r2, [fp, #-56]
	ldr	r2, [fp, #-48]
	cmp	r3, r2
	bhi	.L2239
.L2240:
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
	bne	.L2220
	mov	r0, #0
	b	.L2251
.L2246:
	mov	r10, #8
	b	.L2232
.L2253:
	ldr	r1, .L2257+16
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	cmp	r0, r3
	bhi	.L2243
	ldr	r1, [fp, #-48]
	ldr	r2, [fp, #-52]
	rsb	r3, r0, r1
	cmp	r2, #1
	uxtb	r3, r3
	bls	.L2226
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
	bne	.L2228
.L2255:
	mov	r1, r2
	ldr	r0, [fp, #-52]
	bl	HEVC_GetScalingListDefaultAddress
	mov	r1, r0
	b	.L2229
.L2254:
	ldr	r1, .L2257+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2251
.L2256:
	ldr	r1, .L2257+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2251
.L2243:
	ldr	r1, .L2257+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2251
.L2221:
	cmp	r0, #0
	beq	.L2241
	ldr	r4, .L2257+32
	mov	r10, #8
	b	.L2232
.L2258:
	.align	2
.L2257:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC244
	.word	.LC246
	.word	.LC247
	.word	.LC241
	.word	.LC245
	.word	.LC243
	.word	.LC242
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
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #16)
	sub	sp, sp, #16
	mov	r4, r1
	mov	r5, r0
	ldr	r1, .L2425
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	cmp	r0, #1
	mov	r6, r0
	str	r0, [r4, #60]
	beq	.L2260
	cmp	r0, #3
	bhi	.L2403
	mov	r2, r0
	ldr	r1, .L2425+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2262:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2403:
	ldr	r1, .L2425+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2260:
	ldr	r1, .L2425+12
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #8192
	str	r0, [r4, #64]
	bhi	.L2404
	ldr	r1, .L2425+16
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #4096
	str	r0, [r4, #68]
	bhi	.L2405
	ldr	r2, [r4, #428]
	ldr	r3, [r4, #64]
	cmp	r2, #120
	mul	r0, r3, r0
	beq	.L2268
	bgt	.L2269
	cmp	r2, #60
	beq	.L2270
	ble	.L2406
	cmp	r2, #90
	beq	.L2273
	cmp	r2, #93
	beq	.L2274
	cmp	r2, #63
	beq	.L2407
.L2267:
	ldr	r1, .L2425+20
	mov	r0, #1
	bl	dprint_vfmw
.L2398:
	mvn	r0, #0
	b	.L2262
.L2404:
	ldr	r1, .L2425+24
	mov	r0, r6
.L2400:
	bl	dprint_vfmw
	ldr	r3, .L2425+28
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2398
	mov	r3, #0
	ldr	r0, [r5, #252]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2270:
	mov	r2, #30720
	mov	r3, #122880
.L2275:
	cmp	r0, r2
	movls	r3, #16
	strls	r3, [r4, #184]
	bls	.L2280
	cmp	r0, r3, lsr #1
	movls	r3, #12
	strls	r3, [r4, #184]
	bls	.L2280
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, lsr #2
	movls	r3, #8
	movhi	r3, #6
	str	r3, [r4, #184]
.L2280:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r0, #0
	beq	.L2283
	ldr	r1, .L2425+32
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r6, .L2425+36
	ldr	r1, .L2425+40
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #492]
	mul	r0, r3, r0
	str	r0, [r4, #72]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r2, [r4, #60]
	ldr	r3, [r4, #64]
	ldr	r1, [r4, #72]
	add	r2, r6, r2, lsl #2
	rsb	r3, r1, r3
	ldr	r2, [r2, #492]
	mul	r0, r2, r0
	rsb	r3, r0, r3
	cmp	r3, #0
	str	r0, [r4, #76]
	blt	.L2408
	ldr	r1, .L2425+44
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r4, #60]
	ldr	r1, .L2425+48
	add	r3, r6, r3, lsl #2
	ldr	r3, [r3, #508]
	mul	r0, r3, r0
	str	r0, [r4, #80]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r1, [r4, #60]
	ldr	r2, [r4, #80]
	ldr	r3, [r4, #68]
	add	r6, r6, r1, lsl #2
	rsb	r3, r2, r3
	ldr	r2, [r6, #508]
	mul	r0, r2, r0
	rsb	r3, r0, r3
	cmp	r3, #0
	str	r0, [r4, #84]
	blt	.L2409
.L2283:
	ldr	r1, .L2425+52
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #2
	add	r2, r0, #8
	str	r2, [r4, #88]
	bhi	.L2410
	ldr	r1, .L2425+56
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #6
	add	r2, r0, #8
	str	r2, [r4, #96]
	bhi	.L2411
	ldr	r3, [r4, #88]
	ldr	r1, .L2425+60
	str	r3, [r5, #196]
	ldr	r3, [r4, #96]
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
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #12
	bhi	.L2412
	add	r0, r0, #4
	mov	r1, #1
	str	r0, [r4, #116]
	mov	r8, #0
	str	r0, [r4, #120]
	mov	r7, r8
	ldr	r0, [r5, #2356]
	mov	r6, r4
	bl	BsGet
	mov	r9, r0
	b	.L2294
.L2288:
	ldr	r3, [r4, #52]
	add	r7, r7, #1
	add	r6, r6, #4
	cmp	r7, r3
	bhi	.L2293
.L2294:
	ldr	r1, .L2425+64
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L2425+68
	add	r0, r0, #1
	str	r0, [r6, #328]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r1, .L2425+72
	str	r0, [r6, #360]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r6, #328]
	cmp	r8, r3
	movcc	r8, r3
	cmp	r9, #0
	str	r0, [r6, #392]
	bne	.L2288
	ldr	r1, [r4, #52]
	add	r3, r7, #1
	cmp	r3, r1
	addls	r7, r7, #82
	addls	r7, r4, r7, lsl #2
	bhi	.L2293
.L2292:
	ldr	r2, [r4, #328]
	add	r3, r3, #1
	cmp	r3, r1
	str	r2, [r7, #4]!
	ldr	r2, [r4, #360]
	str	r2, [r7, #32]
	ldr	r2, [r4, #392]
	str	r2, [r7, #64]
	bls	.L2292
.L2293:
	ldr	r3, [r4, #184]
	ldr	r1, .L2425+76
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r4, #184]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L2413
	ldr	r1, .L2425+80
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r7, r0
	bhi	.L2414
	add	r3, r6, #3
	str	r3, [r4, #124]
	add	r6, r0, r3
	str	r6, [r4, #128]
	sub	r2, r6, #4
	cmp	r2, #2
	bhi	.L2415
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
	beq	.L2297
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2298:
	ldr	r8, [r4, #68]
	mov	r1, r6
	str	r0, [r4, #188]
	mov	r0, r8
	bl	__aeabi_uidivmod
	mov	r0, r8
	cmp	r1, #0
	mov	r1, r6
	beq	.L2299
	bl	__aeabi_uidiv
	add	r0, r0, #1
.L2300:
	str	r0, [r4, #192]
	ldr	r1, .L2425+84
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #3
	mov	r6, r0
	bhi	.L2416
	ldr	r1, .L2425+88
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #3
	bhi	.L2417
	ldr	r2, [r4, #124]
	add	r3, r6, #2
	str	r3, [r4, #148]
	cmp	r3, r2
	bcs	.L2418
	add	r3, r0, r3
	str	r3, [r4, #152]
	cmp	r3, #5
	bhi	.L2304
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L2304
	ldr	r1, .L2425+92
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r4, #128]
	ldr	r2, [r4, #148]
	rsb	r3, r2, r3
	cmp	r0, r3
	str	r0, [r4, #164]
	bhi	.L2419
	ldr	r1, .L2425+96
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	ldr	ip, [r4, #148]
	ldr	r3, [r4, #128]
	rsb	r3, ip, r3
	cmp	r0, r3
	str	r0, [r4, #168]
	bhi	.L2307
	ldr	r1, [r4, #140]
	mov	r0, #1
	mov	r3, #0
	mov	r1, r1, lsr r7
	cmp	r1, r0, asl ip
	bls	.L2309
.L2310:
	add	r3, r3, #1
	add	r2, r3, ip
	cmp	r1, r0, asl r2
	bhi	.L2310
.L2309:
	add	r3, r3, r7
	mov	r1, #1
	str	r3, [r4, #172]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #3]
	cmp	r0, #0
	beq	.L2311
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #0
	bne	.L2420
.L2311:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #6]
	cmp	r6, #0
	bne	.L2312
	ldr	r2, [r4, #68]
	cmp	r2, #64
	bls	.L2421
.L2312:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	cmp	r0, #0
	str	r0, [r4, #104]
	beq	.L2313
	mov	r1, #4
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #4
	add	r0, r0, #1
	str	r0, [r4, #108]
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	r1, .L2425+100
	add	r0, r0, #1
	str	r0, [r4, #112]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r7, r0
	bhi	.L2422
.L2314:
	ldr	r1, .L2425+104
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #2
	mov	r6, r0
	bhi	.L2423
.L2315:
	add	r3, r7, #3
	str	r3, [r4, #156]
	add	r3, r6, r3
	str	r3, [r4, #160]
	cmp	r3, #5
	bhi	.L2316
	ldr	r2, [r4, #128]
	cmp	r3, r2
	bhi	.L2316
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	strb	r0, [r4, #7]
.L2313:
	ldr	r1, .L2425+108
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #64
	str	r0, [r4, #176]
	bhi	.L2318
	cmp	r0, #0
	addne	r7, r4, #2160
	movne	r6, #0
	addne	r7, r7, #4
	bne	.L2323
	b	.L2324
.L2322:
	ldr	r3, [r4, #176]
	cmp	r6, r3
	bcs	.L2324
.L2323:
	mov	r3, r6
	mov	r2, r7
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_DecShortTermRefPicSet
	add	r6, r6, #1
	add	r7, r7, #164
	cmp	r0, #0
	beq	.L2322
	ldr	r1, .L2425+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2405:
	mov	r0, r6
	ldr	r1, .L2425+116
	b	.L2400
.L2269:
	cmp	r2, #156
	beq	.L2276
	bgt	.L2277
	cmp	r2, #150
	beq	.L2276
	cmp	r2, #153
	beq	.L2276
	cmp	r2, #123
	bne	.L2267
.L2268:
	mov	r2, #557056
	mov	r3, #2228224
	b	.L2275
.L2299:
	bl	__aeabi_uidiv
	b	.L2300
.L2297:
	bl	__aeabi_uidiv
	b	.L2298
.L2410:
	ldr	r1, .L2425+120
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2425+28
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2398
	ldr	r1, [r4, #88]
	mov	r2, #0
	ldr	r0, [r5, #252]
	mov	r3, #8
	str	r2, [fp, #-44]
	sub	r2, fp, #44
	str	r1, [fp, #-40]
	mov	r1, #119
	blx	ip
	mvn	r0, #0
	b	.L2262
.L2324:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	beq	.L2321
	ldr	r1, .L2425+124
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #32
	str	r0, [r4, #180]
	bhi	.L2327
	cmp	r0, #0
	addne	r8, r4, #192
	addne	r7, r4, #12
	movne	r6, #0
	beq	.L2321
.L2329:
	ldr	r1, [r4, #116]
	add	r6, r6, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #4]!
	ldr	r0, [r5, #2356]
	bl	BsGet
	strb	r0, [r7, #1]!
	ldr	r3, [r4, #180]
	cmp	r6, r3
	bcc	.L2329
.L2321:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #11]
	cmp	r0, #0
	beq	.L2326
	mov	r2, r4
	add	r1, r4, #2064
	mov	r0, r5
	bl	HEVC_DecVuiParam
	cmp	r0, #0
	bne	.L2424
.L2326:
	ldr	ip, [r4, #68]
	ldr	r3, [r4, #64]
	ldr	r2, [r4, #2080]
	ldr	r1, [r4, #2076]
	ldr	r0, [r4, #2072]
	str	ip, [sp]
	bl	HEVC_GetDar
	mov	r1, #1
	str	r0, [r4, #2068]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #12]
	cmp	r0, #0
	bne	.L2396
.L2332:
	mov	r3, #1
	mov	r0, #0
	strb	r3, [r4]
	b	.L2262
.L2331:
	ldr	r0, [r5, #2356]
	bl	BsGet
.L2396:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2331
	b	.L2332
.L2277:
	cmp	r2, #183
	beq	.L2278
	cmp	r2, #186
	beq	.L2278
	cmp	r2, #180
	bne	.L2267
.L2278:
	mov	r2, #8912896
	mov	r3, #35651584
	b	.L2275
.L2406:
	cmp	r2, #0
	beq	.L2272
	cmp	r2, #30
	bne	.L2267
.L2272:
	mov	r2, #9216
	mov	r3, #36864
	b	.L2275
.L2273:
	mov	r2, #138240
	mov	r3, #552960
	b	.L2275
.L2407:
	mov	r2, #61440
	mov	r3, #245760
	b	.L2275
.L2274:
	mov	r2, #245760
	mov	r3, #983040
	b	.L2275
.L2276:
	mov	r2, #2228224
	mov	r3, #8912896
	b	.L2275
.L2421:
	ldr	r1, .L2425+128
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2425+28
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2398
	ldr	r0, [r5, #252]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #102
	blx	ip
	mvn	r0, #0
	b	.L2262
.L2420:
	add	r1, r4, #432
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	beq	.L2311
	ldr	r1, .L2425+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2304:
	ldr	r1, .L2425+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2423:
	mov	r2, r0
	ldr	r1, .L2425+140
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2315
.L2422:
	mov	r2, r0
	ldr	r1, .L2425+144
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2314
.L2412:
	ldr	r1, .L2425+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2413:
	ldr	r1, .L2425+152
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2416:
	ldr	r1, .L2425+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2316:
	ldr	r1, .L2425+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2419:
	ldr	r1, .L2425+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2414:
	ldr	r1, .L2425+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2415:
	ldr	r1, .L2425+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2411:
	ldr	r1, .L2425+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2418:
	ldr	r1, .L2425+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2417:
	ldr	r1, .L2425+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2307:
	ldr	r1, .L2425+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2408:
	ldr	r1, .L2425+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2318:
	mov	r2, #64
	ldr	r1, .L2425+196
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2409:
	ldr	r1, .L2425+200
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2327:
	ldr	r1, .L2425+204
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2424:
	ldr	r1, .L2425+208
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2262
.L2426:
	.align	2
.L2425:
	.word	.LC248
	.word	.LC250
	.word	.LC249
	.word	.LC251
	.word	.LC253
	.word	.LC255
	.word	.LC252
	.word	g_event_report
	.word	.LC256
	.word	.LANCHOR0
	.word	.LC257
	.word	.LC259
	.word	.LC260
	.word	.LC262
	.word	.LC264
	.word	.LC266
	.word	.LC268
	.word	.LC269
	.word	.LC270
	.word	.LC271
	.word	.LC273
	.word	.LC276
	.word	.LC278
	.word	.LC282
	.word	.LC284
	.word	.LC288
	.word	.LC290
	.word	.LC293
	.word	.LC295
	.word	.LC254
	.word	.LC263
	.word	.LC296
	.word	.LC287
	.word	.LC286
	.word	.LC281
	.word	.LC291
	.word	.LC289
	.word	.LC267
	.word	.LC272
	.word	.LC277
	.word	.LC292
	.word	.LC283
	.word	.LC274
	.word	.LC275
	.word	.LC265
	.word	.LC280
	.word	.LC279
	.word	.LC285
	.word	.LC258
	.word	.LC294
	.word	.LC261
	.word	.LC297
	.word	.LC298
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
	ldr	r7, .L2446
	mov	r4, r0
	mov	r2, #8
	mov	r1, #0
	sub	r0, fp, #60
	ldr	r3, [r7, #48]
	blx	r3
	ldr	r0, [r4, #2356]
	mov	r1, #4
	bl	BsGet
	ldr	r2, [r4, #156]
	cmp	r2, r0
	mov	r9, r0
	bls	.L2440
	ldr	r3, [r4, #2376]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L2441
	mov	r5, #0
	mov	r10, r5
.L2430:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r3, r5
	mov	r2, #1
	sub	r1, fp, #60
	mov	r8, r0
	mov	r0, r4
	bl	HEVC_DecPTL
	subs	r3, r0, #0
	str	r3, [fp, #-64]
	bne	.L2442
	ldr	r1, .L2446+4
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r2, [r4, #160]
	cmp	r0, r2
	mov	r6, r0
	bcs	.L2443
	movw	r3, #12660
	ldr	r2, [r4, #2364]
	mul	r5, r3, r0
	uxtb	r1, r8
	str	r1, [fp, #-68]
	add	r2, r2, r5
	ldrb	r8, [r2, #1]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L2434
	mov	r2, r3
	ldr	ip, [r7, #48]
	ldr	r1, [fp, #-64]
	ldr	r0, .L2446+8
	ldr	r8, .L2446+12
	str	r3, [fp, #-72]
	blx	ip
	ldrb	r3, [fp, #-68]	@ zero_extendqisi2
	sub	r1, fp, #60
	ldr	ip, [r7, #52]
	mov	r2, #8
	str	r9, [r8, #-3416]
	sub	r0, r8, #3040
	strb	r3, [r8, #-3462]
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	str	r10, [r8, #-3412]
	strb	r3, [r8, #-3418]
	blx	ip
	ldr	r1, .L2446+8
	mov	r0, r4
	str	r6, [r8, #-3408]
	bl	HEVC_ProcessSPS
	ldr	r1, .L2446
	ldr	r3, [fp, #-72]
	subs	r7, r0, #0
	bne	.L2444
	ldr	r0, [r4, #2364]
	mov	r2, r3
	ldr	ip, [r1, #56]
	mov	r3, #1
	add	r0, r0, r5
	strb	r3, [r8, #-3464]
	strb	r3, [r8, #-3463]
	ldr	r1, .L2446+8
	blx	ip
	ldr	r3, [r4, #2364]
	add	r5, r3, r5
	str	r5, [r4, #2372]
.L2429:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2441:
	mov	r1, #3
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r0, #8
	mov	r5, r0
	mov	r10, r0
	bls	.L2430
	mov	r2, #8
	ldr	r1, .L2446+16
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L2429
.L2434:
	str	r9, [r2, #48]
	sub	r1, fp, #60
	ldr	r3, [r4, #2364]
	mov	r2, #8
	ldrb	r0, [fp, #-68]	@ zero_extendqisi2
	add	r3, r3, r5
	str	r10, [r3, #52]
	ldr	r3, [r4, #2364]
	add	r3, r3, r5
	strb	r0, [r3, #2]
	ldr	r3, [r4, #2364]
	add	r3, r3, r5
	strb	r8, [r3, #46]
	ldr	r0, [r4, #2364]
	ldr	r3, [r7, #52]
	add	r0, r0, r5
	add	r0, r0, #424
	blx	r3
	ldr	r3, [r4, #2364]
	mov	r0, r4
	add	r3, r3, r5
	str	r6, [r3, #56]
	ldr	r1, [r4, #2364]
	add	r1, r1, r5
	bl	HEVC_ProcessSPS
	subs	r7, r0, #0
	bne	.L2445
	ldr	r3, [r4, #2364]
	mov	r2, #1
	mov	r0, r7
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2364]
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2364]
	add	r5, r3, r5
	str	r5, [r4, #2372]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2443:
	ldr	r1, .L2446+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r4, #160]
	cmp	r6, r2
	bcc	.L2439
	ldr	r3, .L2446+24
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2439
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r6, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r4, #252]
	mov	r1, #109
	blx	ip
	mvn	r7, #0
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2439:
	mvn	r7, #0
	b	.L2429
.L2442:
	ldr	r1, .L2446+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2429
.L2440:
	ldr	r1, .L2446+32
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L2429
.L2444:
	ldr	r3, [r4, #2364]
	mov	r2, r6
	ldr	r1, .L2446+36
	mov	r0, #1
	add	r5, r3, r5
	str	r5, [r4, #2372]
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2429
.L2445:
	mov	r2, r6
	ldr	r1, .L2446+40
	mov	r0, #1
	mvn	r7, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2364]
	mov	r2, #1
	strb	r2, [r3, r5]
	ldr	r3, [r4, #2364]
	add	r5, r3, r5
	strb	r8, [r5, #1]
	b	.L2429
.L2447:
	.align	2
.L2446:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC302
	.word	.LANCHOR5-3464
	.word	.LANCHOR5
	.word	.LC300
	.word	.LC303
	.word	g_event_report
	.word	.LC301
	.word	.LC299
	.word	.LC304
	.word	.LC305
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
	ldr	r1, .L2576
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	blt	.L2449
	ldr	r3, [r5, #160]
	cmp	r0, r3
	bge	.L2449
	ldr	r3, [r5, #2364]
	movw	r6, #12660
	mla	r6, r6, r0, r3
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2556
	mov	r1, r7
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #2]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #4]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, r7
	str	r0, [r4, #36]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #3]
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	r1, .L2576+4
	strb	r0, [r4, #5]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #40]
	cmp	r0, #15
	bhi	.L2557
	ldr	r1, .L2576+8
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	add	r0, r0, #1
	str	r0, [r4, #44]
	cmp	r0, #15
	bhi	.L2558
	ldr	r1, .L2576+12
	ldr	r0, [r5, #2356]
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
	bne	.L2559
	mov	r1, r7
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #6]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, r7
	strb	r0, [r4, #7]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #8]
	cmp	r0, #0
	streq	r0, [r4, #52]
	bne	.L2560
.L2458:
	str	r0, [r4, #56]
	ldr	r1, .L2576+16
	ldr	r0, [r5, #2356]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #60]
	cmp	r3, #24
	bhi	.L2561
	ldr	r1, .L2576+20
	ldr	r0, [r5, #2356]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r4, #64]
	cmp	r3, #24
	bhi	.L2562
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #9]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #10]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #11]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #12]
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #13]
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #14]
	bne	.L2563
	ldr	r3, [r6, #188]
	strh	r3, [r4, #172]	@ movhi
	ldr	r3, [r6, #192]
	strh	r3, [r4, #212]	@ movhi
.L2497:
	ldr	r0, [r4, #68]
	cmp	r0, #0
	ble	.L2502
.L2496:
	ldr	ip, [r6, #140]
	add	r1, r4, #170
	mov	r3, #0
.L2501:
	ldrsh	r2, [r1, #2]!
	add	r3, r3, #1
	mul	r2, ip, r2
	cmp	r2, #64
	bhi	.L2500
	ldr	lr, [r6, #64]
	cmp	lr, #64
	bhi	.L2564
.L2500:
	cmp	r3, r0
	blt	.L2501
.L2502:
	ldr	r1, [r4, #72]
	cmp	r1, #0
	ble	.L2499
	ldr	r0, [r6, #140]
	ldrsh	r2, [r4, #212]
	mul	r2, r0, r2
	cmp	r2, #63
	addhi	r1, r1, #105
	addhi	r3, r4, #212
	addhi	r1, r4, r1, lsl #1
	bhi	.L2505
	b	.L2503
.L2506:
	ldrsh	r2, [r3, #2]!
	mul	r2, r0, r2
	cmp	r2, #63
	bls	.L2503
.L2505:
	cmp	r3, r1
	bne	.L2506
.L2499:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #17]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #0
	bne	.L2565
.L2508:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #21]
	cmp	r0, #0
	beq	.L2511
	add	r1, r4, #256
	mov	r0, r5
	bl	HEVC_DecScalingListData
	cmp	r0, #0
	bne	.L2566
.L2511:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	ldr	r1, .L2576+24
	strb	r0, [r4, #22]
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	add	r2, r0, #2
	str	r2, [r4, #84]
	cmp	r2, #1
	ble	.L2512
	ldr	r3, [r6, #128]
	cmp	r2, r3
	bhi	.L2512
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #24]
	cmp	r0, #0
	bne	.L2543
	b	.L2516
.L2515:
	ldr	r0, [r5, #2356]
	bl	BsGet
	strb	r0, [r4, #25]
.L2543:
	mov	r0, r5
	bl	HEVC_MoreRbspData
	mov	r1, #1
	cmp	r0, #0
	bne	.L2515
.L2516:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2560:
	ldr	r1, .L2576+28
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #3
	str	r0, [r4, #52]
	bls	.L2458
	mov	r0, r7
	ldr	r1, .L2576+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2563:
	ldr	r1, .L2576+36
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #19
	add	r2, r0, #1
	str	r2, [r4, #68]
	bhi	.L2567
	ldr	r1, .L2576+40
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	cmp	r0, #21
	add	r3, r0, #1
	str	r3, [r4, #72]
	bhi	.L2568
	ldr	r2, [r4, #68]
	cmp	r2, #10
	bgt	.L2569
	cmp	r3, #11
	ble	.L2466
	ldr	r1, .L2576+44
	mov	r2, #11
.L2553:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2576+48
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2548
.L2550:
	mov	r3, #0
	ldr	r0, [r5, #252]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
.L2544:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2503:
	ldr	r1, .L2576+52
.L2552:
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2576+48
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L2550
.L2548:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2564:
	ldr	r1, .L2576+56
	b	.L2552
.L2559:
	mov	r0, r7
	ldr	r1, .L2576+60
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2466:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #15]
	cmp	r0, #0
	bne	.L2480
	ldr	r3, [r4, #68]
	cmp	r3, #1
	addgt	r8, r4, #86
	movgt	r7, r0
	bgt	.L2478
	b	.L2570
.L2572:
	cmp	r3, r2
	bhi	.L2476
	ldr	r3, [r4, #68]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L2571
.L2478:
	ldr	r1, .L2576+64
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #188]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2572
.L2476:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r7
	ldr	r1, .L2576+68
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2569:
	mov	r3, r2
	ldr	r1, .L2576+72
	mov	r2, #10
	b	.L2553
.L2565:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	ldr	r0, [r5, #2356]
	bl	BsGet
	uxtb	r7, r0
	strb	r7, [r4, #20]
	cmp	r7, #0
	bne	.L2508
	ldr	r1, .L2576+76
	ldr	r0, [r5, #2356]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #76]
	bhi	.L2573
.L2510:
	ldr	r1, .L2576+80
	ldr	r0, [r5, #2356]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r4, #80]
	bls	.L2508
	ldr	r1, .L2576+84
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #80]
	b	.L2508
.L2480:
	ldr	r7, [r4, #68]
	cmp	r7, #0
	addgt	r3, r4, #170
	movgt	r8, #0
	ble	.L2470
.L2488:
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
	bne	.L2488
.L2470:
	ldr	r10, [r4, #72]
	cmp	r10, #0
	addgt	r2, r4, #210
	movgt	r8, #0
	ble	.L2487
.L2489:
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
	bne	.L2489
.L2487:
	cmp	r7, #1
	bne	.L2495
	ldr	r0, [r4, #72]
	cmp	r0, #1
	beq	.L2496
.L2495:
	mov	r1, #1
	ldr	r0, [r5, #2356]
	bl	BsGet
	strb	r0, [r4, #16]
	b	.L2497
.L2449:
	mov	r2, r0
	ldr	r1, .L2576+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2556:
	mov	r2, r0
	ldr	r1, .L2576+92
	mov	r0, r7
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2557:
	mov	r0, r7
	ldr	r1, .L2576+96
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2558:
	mov	r0, r7
	ldr	r1, .L2576+100
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2561:
	ldr	r1, .L2576+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2562:
	ldr	r1, .L2576+108
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2512:
	ldr	r1, .L2576+112
	mov	r0, #1
	bl	dprint_vfmw
	b	.L2548
.L2571:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	ble	.L2474
.L2473:
	add	r8, r4, #126
	mov	r7, #0
	b	.L2485
.L2574:
	cmp	r3, r2
	bhi	.L2483
	ldr	r3, [r4, #72]
	add	r7, r7, #1
	sub	r3, r3, #1
	cmp	r3, r7
	ble	.L2474
.L2485:
	ldr	r1, .L2576+116
	ldr	r0, [r5, #2356]
	bl	HEVC_ue_v
	add	r0, r0, #1
	uxth	r3, r0
	strh	r3, [r8, #2]!	@ movhi
	ldr	r2, [r6, #192]
	sxth	r3, r3
	cmp	r3, #0
	bge	.L2574
.L2483:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r7
	ldr	r1, .L2576+120
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2567:
	mov	r3, #20
	ldr	r1, .L2576+124
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2573:
	ldr	r1, .L2576+128
	mov	r0, #1
	bl	dprint_vfmw
	str	r7, [r4, #76]
	b	.L2510
.L2474:
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2480
.L2481:
	ldr	r7, [r4, #68]
	ldrh	r3, [r6, #188]
	sub	r2, r7, #1
	add	ip, r4, r7, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #170]	@ movhi
	ble	.L2490
	add	r8, r7, #42
	add	r1, r4, #86
	add	lr, r4, #170
	add	r8, r4, r8, lsl #1
.L2491:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #170]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #170]	@ movhi
	bne	.L2491
.L2490:
	sxth	r3, r3
	cmp	r3, #0
	ble	.L2575
	ldr	r1, [r4, #72]
	ldrh	r3, [r6, #192]
	sub	r2, r1, #1
	add	ip, r4, r1, lsl #1
	cmp	r2, #0
	strh	r3, [ip, #210]	@ movhi
	ble	.L2493
	add	r8, r1, #62
	add	lr, r4, #210
	add	r1, r4, #126
	add	r8, r4, r8, lsl #1
.L2494:
	ldrh	r0, [r1, #2]!
	cmp	r1, r8
	strh	r0, [lr, #2]!	@ movhi
	ldrh	r3, [ip, #210]
	rsb	r3, r0, r3
	uxth	r3, r3
	strh	r3, [ip, #210]	@ movhi
	bne	.L2494
.L2493:
	sxth	r3, r3
	cmp	r3, #0
	bgt	.L2487
	ldr	r1, .L2576+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2568:
	mov	r2, r3
	ldr	r1, .L2576+136
	mov	r3, #22
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2566:
	ldr	r1, .L2576+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2570:
	ldr	r3, [r4, #72]
	cmp	r3, #1
	bgt	.L2473
	b	.L2481
.L2575:
	ldr	r1, .L2576+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2544
.L2577:
	.align	2
.L2576:
	.word	.LC306
	.word	.LC309
	.word	.LC311
	.word	.LC313
	.word	.LC317
	.word	.LC319
	.word	.LC340
	.word	.LC315
	.word	.LC316
	.word	.LC321
	.word	.LC323
	.word	.LC326
	.word	g_event_report
	.word	.LC334
	.word	.LC333
	.word	.LC314
	.word	.LC327
	.word	.LC328
	.word	.LC325
	.word	.LC335
	.word	.LC337
	.word	.LC338
	.word	.LC307
	.word	.LC308
	.word	.LC310
	.word	.LC312
	.word	.LC318
	.word	.LC320
	.word	.LC341
	.word	.LC329
	.word	.LC330
	.word	.LC322
	.word	.LC336
	.word	.LC332
	.word	.LC324
	.word	.LC339
	.word	.LC331
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
	ldr	r1, .L2588
	mov	r4, r0
	ldr	r0, [r0, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r4, #164]
	cmp	r0, r3
	mov	r6, r0
	bcs	.L2584
	mov	r7, #1888
	ldr	r3, [r4, #2368]
	mul	r5, r7, r0
	add	r2, r3, r5
	ldrb	r9, [r3, r5]	@ zero_extendqisi2
	cmp	r9, #0
	bne	.L2585
	str	r0, [r2, #28]
	mov	r0, r4
	ldr	r1, [r4, #2368]
	add	r1, r1, r5
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L2586
	ldr	r3, [r4, #2368]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2368]
	strb	r2, [r3, r5]
.L2580:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2585:
	ldr	r10, .L2588+4
	mov	r2, r7
	ldr	r9, .L2588+8
	mov	r1, #0
	ldr	r0, .L2588+12
	ldr	r3, [r10, #48]
	blx	r3
	ldr	r1, .L2588+12
	mov	r0, r4
	str	r6, [r9, #-3436]
	bl	HEVC_ProcessPPS
	subs	r8, r0, #0
	bne	.L2587
	ldr	r0, [r4, #2368]
	mov	r3, #1
	mov	r2, r7
	ldr	ip, [r10, #56]
	add	r0, r0, r5
	strb	r3, [r9, #-3463]
	strb	r3, [r9, #-3464]
	ldr	r1, .L2588+12
	blx	ip
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2587:
	mov	r2, r6
	ldr	r1, .L2588+16
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L2580
.L2584:
	mov	r2, r0
	ldr	r1, .L2588+20
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	b	.L2580
.L2586:
	mov	r2, r6
	ldr	r1, .L2588+16
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2368]
	mov	r2, #1
	add	r3, r3, r5
	strb	r2, [r3, #1]
	ldr	r3, [r4, #2368]
	strb	r9, [r3, r5]
	b	.L2580
.L2589:
	.align	2
.L2588:
	.word	.LC342
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR5
	.word	.LANCHOR5-3464
	.word	.LC344
	.word	.LC343
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
	ldr	r3, [r0, #2368]
	mov	r6, r0
	ldr	r2, [r4, #140]
	mov	r0, #1888
	ldr	r1, [r4, #124]
	ldr	r5, [r6, #2364]
	mla	r3, r0, r2, r3
	cmp	r1, #1
	ldr	r7, [r3, #32]
	beq	.L2656
	cmp	r1, #0
	bne	.L2594
	ldrb	r3, [r3, #11]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2594
.L2592:
	ldr	r1, .L2667
	ldr	r0, [r6, #2356]
	bl	HEVC_ue_v
	cmp	r0, #7
	str	r0, [r4, #260]
	bhi	.L2657
	movw	r8, #12660
	mla	r8, r8, r7, r5
	ldr	r3, [r8, #60]
	cmp	r3, #0
	streq	r0, [r4, #392]
	bne	.L2658
.L2634:
	ldr	r3, [r4, #180]
	cmp	r3, #0
	subne	r3, fp, #172
	strne	r3, [fp, #-176]
	movne	r5, #0
	movne	r7, r3
	beq	.L2600
.L2601:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	ldr	r3, [r4, #180]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L2601
	ldr	r2, [r8, #60]
	cmp	r2, #0
	beq	.L2602
	cmp	r3, #0
	subne	r7, fp, #108
	movne	r5, #0
	beq	.L2600
.L2606:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	ldr	r3, [r4, #180]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L2606
.L2602:
	cmp	r3, #0
	beq	.L2600
	add	r9, r6, #4480
	add	r10, r6, #4544
	add	r9, r9, #12
	add	r10, r10, #20
	mov	r5, #0
	b	.L2617
.L2607:
	ldr	r2, [r4, #260]
	mov	r3, #1
	str	r1, [r9, #-132]
	mov	r2, r3, asl r2
	str	r2, [r9]
.L2609:
	ldr	r2, [r8, #60]
	cmp	r2, #0
	beq	.L2611
	sub	r2, fp, #108
	ldr	r2, [r2, r5, asl #2]
	cmp	r2, #0
	bne	.L2612
	ldr	r1, [r4, #392]
	mov	r3, #1
	str	r2, [r10, #120]
	mov	r1, r3, asl r1
	str	r2, [r10, #124]
	str	r1, [r10, #-8]
	str	r1, [r10, #-4]
.L2611:
	ldr	r2, [r4, #180]
	add	r5, r5, #1
	add	r9, r9, #4
	add	r10, r10, #8
	cmp	r2, r5
	bls	.L2600
.L2617:
	ldr	r3, [fp, #-176]
	ldr	r1, [r3, r5, asl #2]
	cmp	r1, #0
	beq	.L2607
	ldr	r1, .L2667+4
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r2, r0, #128
	cmp	r2, #255
	bhi	.L2659
	ldr	r2, [r4, #260]
	mov	r3, #1
	ldr	r1, .L2667+8
	add	r0, r0, r3, asl r2
	str	r0, [r9]
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r2, r0, #128
	str	r0, [r9, #-132]
	cmp	r2, #255
	bls	.L2609
	mov	r2, r0
	ldr	r1, .L2667+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2656:
	ldrb	r3, [r3, #10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2592
.L2594:
	mov	r0, #0
.L2655:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2612:
	sub	r7, r10, #8
.L2615:
	ldr	r1, .L2667+16
	ldr	r0, [r6, #2356]
	str	r7, [fp, #-180]
	bl	HEVC_se_v
	ldr	r1, .L2667+20
	add	lr, r0, #128
	cmp	lr, #255
	bhi	.L2660
	ldr	lr, [r4, #392]
	mov	r3, #1
	add	r7, r7, #4
	add	r0, r0, r3, asl lr
	str	r0, [r7, #-4]
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r1, r0, #512
	cmp	r1, #1024
	bcs	.L2661
	ldr	r3, [fp, #-180]
	cmp	r10, r7
	ldr	lr, [r4, #392]
	ldr	r1, [r3]
	mov	r1, r1, asl #7
	mov	r1, r1, asr lr
	rsb	r1, r1, #128
	add	r0, r0, r1
	ssat	r0, #8, r0
	str	r0, [r7, #124]
	bne	.L2615
	b	.L2611
.L2600:
	ldr	r5, [r4, #124]
	cmp	r5, #0
	bne	.L2594
	ldr	r3, [r4, #184]
	cmp	r3, #0
	beq	.L2594
	sub	r3, fp, #172
	str	r3, [fp, #-176]
	mov	r7, r3
.L2618:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	ldr	r3, [r4, #184]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L2618
	ldr	r2, [r8, #60]
	cmp	r2, #0
	bne	.L2662
.L2619:
	cmp	r3, #0
	beq	.L2594
	add	r7, r6, #4800
	add	r10, r6, #4864
	add	r7, r7, #12
	add	r10, r10, #20
	mov	r5, #0
	b	.L2633
.L2623:
	ldr	r1, [r4, #260]
	mov	r3, #1
	str	r0, [r7, #-388]
	mov	r1, r3, asl r1
	str	r1, [r7]
.L2625:
	ldr	r1, [r8, #60]
	cmp	r1, #0
	beq	.L2627
	sub	r1, fp, #108
	ldr	r1, [r1, r5, asl #2]
	cmp	r1, #0
	bne	.L2628
	ldr	r0, [r4, #392]
	mov	r3, #1
	str	r1, [r10, #120]
	mov	r0, r3, asl r0
	str	r1, [r10, #124]
	str	r0, [r10, #-8]
	str	r0, [r10, #-4]
.L2627:
	ldr	r1, [r4, #184]
	add	r5, r5, #1
	add	r7, r7, #4
	add	r10, r10, #8
	cmp	r1, r5
	bls	.L2594
.L2633:
	ldr	r3, [fp, #-176]
	ldr	r0, [r3, r5, asl #2]
	cmp	r0, #0
	beq	.L2623
	ldr	r1, .L2667+24
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r1, r0, #128
	cmp	r1, #255
	bhi	.L2663
	ldr	ip, [r4, #260]
	mov	r3, #1
	ldr	r1, .L2667+28
	add	r0, r0, r3, asl ip
	str	r0, [r7]
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r1, r0, #128
	str	r0, [r7, #-388]
	cmp	r1, #255
	bls	.L2625
	ldr	r1, .L2667+32
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2628:
	sub	r9, r10, #8
.L2631:
	ldr	r1, .L2667+36
	ldr	r0, [r6, #2356]
	str	r9, [fp, #-180]
	bl	HEVC_se_v
	ldr	r1, .L2667+40
	add	lr, r0, #128
	cmp	lr, #255
	bhi	.L2664
	ldr	lr, [r4, #392]
	mov	r3, #1
	add	r9, r9, #4
	add	r0, r0, r3, asl lr
	str	r0, [r9, #-4]
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r1, r0, #512
	cmp	r1, #1024
	bcs	.L2665
	ldr	r3, [fp, #-180]
	cmp	r10, r9
	ldr	lr, [r4, #392]
	ldr	r1, [r3]
	mov	r1, r1, asl #7
	mov	r1, r1, asr lr
	rsb	r1, r1, #128
	add	r1, r0, r1
	ssat	r1, #8, r1
	str	r1, [r9, #124]
	bne	.L2631
	b	.L2627
.L2658:
	ldr	r1, .L2667+44
	ldr	r0, [r6, #2356]
	bl	HEVC_se_v
	add	r3, r0, #7
	cmp	r3, #14
	bhi	.L2666
	ldr	r3, [r4, #260]
	add	r0, r0, r3
	str	r0, [r4, #392]
	cmp	r0, #7
	bls	.L2634
	ldr	r1, .L2667+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2660:
	ldr	r1, .L2667+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2661:
	ldr	r1, .L2667+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2662:
	cmp	r3, #0
	subne	r7, fp, #108
	movne	r5, #0
	beq	.L2594
.L2622:
	mov	r1, #1
	ldr	r0, [r6, #2356]
	bl	BsGet
	ldr	r3, [r4, #184]
	add	r5, r5, #1
	cmp	r3, r5
	str	r0, [r7], #4
	bhi	.L2622
	b	.L2619
.L2659:
	mov	r2, r0
	ldr	r1, .L2667+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2664:
	ldr	r1, .L2667+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2665:
	ldr	r1, .L2667+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2663:
	ldr	r1, .L2667+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2657:
	ldr	r1, .L2667+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2666:
	ldr	r1, .L2667+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2655
.L2668:
	.align	2
.L2667:
	.word	.LC345
	.word	.LC350
	.word	.LC352
	.word	.LC353
	.word	.LC354
	.word	.LC356
	.word	.LC358
	.word	.LC360
	.word	.LC361
	.word	.LC362
	.word	.LC364
	.word	.LC347
	.word	.LC349
	.word	.LC355
	.word	.LC357
	.word	.LC351
	.word	.LC363
	.word	.LC365
	.word	.LC359
	.word	.LC346
	.word	.LC348
	UNWIND(.fnend)
	.size	HEVC_DecPredWeightTable, .-HEVC_DecPredWeightTable
	.align	2
	.global	HEVC_DecSliceSegmentHeader
	.type	HEVC_DecSliceSegmentHeader, %function
HEVC_DecSliceSegmentHeader:
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
	ldr	r3, [r0, #2376]
	add	r5, r0, #4096
	mov	r4, r0
	mov	r1, #1
	ldr	r0, [r0, #2356]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-48]
	bl	BsGet
	ldr	r6, [r5, #132]
	sub	r3, r6, #16
	cmp	r3, #5
	movhi	r3, #0
	movls	r3, #1
	cmp	r3, #0
	str	r3, [fp, #-64]
	strb	r0, [r5, #104]
	bne	.L2921
.L2670:
	ldr	r1, .L2965
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r0, #0
	str	r0, [r5, #140]
	ldr	r3, [r4, #164]
	blt	.L2672
	cmp	r0, r3
	bge	.L2672
	mov	r0, r4
	bl	HEVC_VpsSpsPpsCheck
	subs	r3, r0, #0
	str	r3, [fp, #-72]
	bne	.L2922
	ldr	r1, [r5, #140]
	mov	r7, #1888
	ldr	r2, [r4, #2368]
	movw	r8, #12660
	ldr	r3, [r4, #2364]
	mla	r7, r7, r1, r2
	ldrb	r1, [r7, #2]	@ zero_extendqisi2
	ldr	r2, [r7, #32]
	cmp	r1, #0
	mla	r8, r8, r2, r3
	bne	.L2923
.L2678:
	mov	r3, #0
	strb	r3, [r5, #105]
.L2679:
	ldr	r10, [r8, #140]
	ldr	r3, [r8, #144]
	cmp	r10, #0
	beq	.L2681
	cmp	r3, #0
	beq	.L2681
	ldr	r0, [r8, #68]
	mov	r1, r3
	add	r0, r3, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	mov	r1, r10
	mov	r9, r0
	ldr	r0, [r8, #64]
	add	r0, r10, r0
	sub	r0, r0, #1
	bl	__aeabi_uidiv
	ldr	r10, [r8, #172]
	mov	r1, #1
	mov	r10, r10, asl r1
	mov	r10, r1, asl r10
	mul	r0, r0, r9
	cmp	r0, r1
	ble	.L2812
	mov	r3, r1
	mov	r1, #0
.L2684:
	add	r1, r1, #1
	cmp	r0, r3, asl r1
	bgt	.L2684
.L2683:
	ldrb	r3, [r5, #104]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [fp, #-68]
	beq	.L2924
.L2685:
	ldrb	r10, [r5, #105]	@ zero_extendqisi2
	ldr	r3, [r4, #192]
	cmp	r10, #0
	str	r3, [r5, #116]
	beq	.L2925
.L2688:
	ldr	r3, [r7, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #0
	bne	.L2780
.L2787:
	ldrb	r3, [r7, #23]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2926
.L2782:
	ldr	r3, [fp, #-68]
	cmp	r3, #0
	bne	.L2927
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [fp, #-64]
	beq	.L2798
	cmp	r3, #0
	beq	.L2799
	ldr	r3, [r5, #136]
	mov	r2, #1
	add	r3, r4, r3
	strb	r2, [r3, #5]
.L2796:
	ldr	r2, [r5, #116]
	ldr	r1, [fp, #-64]
	cmp	r2, #0
	moveq	r1, #0
	andne	r1, r1, #1
	cmp	r1, #0
	bne	.L2928
.L2797:
	mov	r2, #0
	strb	r2, [r3, #4]
.L2801:
	mov	r0, r4
	bl	HEVC_IsNewPic
	str	r0, [r5, #256]
	mov	r0, r4
	bl	HEVC_ReadByteAlignment
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L2906:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2923:
	ldrb	r3, [r5, #104]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2678
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r5, #105]
	b	.L2679
.L2925:
	ldr	r3, [r7, #36]
	cmp	r3, #0
	beq	.L2693
.L2692:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r3, [r7, #36]
	add	r10, r10, #1
	cmp	r3, r10
	bhi	.L2692
.L2693:
	ldr	r1, .L2965+4
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r0, #2
	str	r0, [r5, #124]
	bhi	.L2929
	ldrb	r3, [r7, #4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2930
.L2694:
	sub	r6, r6, #19
	cmp	r6, #1
	bhi	.L2931
	mov	r3, #0
	str	r3, [r5, #116]
	ldr	r3, [r4, #2332]
	cmp	r3, #0
	streq	r3, [r4, #192]
	ldr	r3, [r5, #128]
	cmp	r3, #0
	streq	r3, [r4, #188]
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2914
.L2804:
	mov	r3, #0
	strb	r3, [r5, #108]
	str	r3, [fp, #-84]
.L2806:
	ldr	r3, [r5, #124]
	cmp	r3, #2
	bne	.L2932
.L2734:
	ldrb	r3, [r5, #108]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2756
	mov	r3, #2
	mov	r2, #1
	strb	r2, [r5, #112]
.L2759:
	ldrb	r2, [r7, #10]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2763
	cmp	r3, #1
	beq	.L2766
.L2763:
	ldrb	r2, [r7, #11]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2754
	cmp	r3, #0
	bne	.L2754
.L2766:
	mov	r0, r4
	bl	HEVC_DecPredWeightTable
	cmp	r0, #0
	ldreq	r3, [r5, #124]
	bne	.L2933
.L2754:
	cmp	r3, #2
	beq	.L2767
	ldr	r1, .L2965+8
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	rsb	r3, r0, #4
	rsb	r2, r0, #5
	cmp	r3, #4
	str	r2, [r5, #152]
	bhi	.L2934
.L2767:
	ldr	r1, .L2965+12
	ldr	r0, [r4, #2356]
	bl	HEVC_se_v
	ldr	r2, [r7, #48]
	add	r2, r0, r2
	str	r2, [r5, #120]
	ldr	r3, [r8, #92]
	cmp	r2, #51
	rsb	r0, r3, #0
	movle	r1, #0
	movgt	r1, #1
	cmp	r2, r0
	orrlt	r1, r1, #1
	cmp	r1, #0
	bne	.L2935
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2936
.L2769:
	ldrb	r3, [r7, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2911
	ldrb	r3, [r7, #19]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2937
.L2775:
	ldrb	r0, [r7, #20]	@ zero_extendqisi2
	strb	r0, [r5, #113]
	ldr	r3, [r7, #76]
	str	r3, [r5, #164]
	ldr	r3, [r7, #80]
	str	r3, [r5, #168]
.L2774:
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2778
	ldrh	r2, [r5, #106]
	adds	r3, r2, #0
	movne	r3, #1
.L2778:
	ldrb	r2, [r7, #17]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2779
	cmp	r0, #0
	orreq	r3, r3, #1
	cmp	r3, #0
	bne	.L2938
.L2779:
	strb	r2, [r5, #114]
	b	.L2688
.L2927:
	ldr	r3, [r5, #136]
	add	r3, r4, r3
	ldrb	r2, [r3, #5]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2797
	b	.L2796
.L2921:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L2670
.L2924:
	ldr	r0, [r4, #2356]
	bl	BsGet
	str	r0, [r5, #144]
	cmp	r0, #0
	ldr	r2, [r8, #192]
	ldr	r3, [r8, #188]
	mul	r3, r3, r2
	blt	.L2687
	cmp	r3, r0
	bls	.L2687
	mul	r3, r10, r0
	str	r3, [fp, #-68]
	b	.L2685
.L2780:
	ldr	r1, .L2965+16
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r7, #12]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	ldreq	r3, [r8, #192]
	subeq	r3, r3, #1
	mov	r6, r0
	beq	.L2784
	cmp	r3, #256
	ldreq	r2, [r7, #68]
	ldreq	r3, [r7, #72]
	ldrne	r3, [r8, #192]
	ldrne	r2, [r7, #68]
	mul	r3, r3, r2
	sub	r3, r3, #1
.L2784:
	cmp	r3, #255
	movcs	r3, #255
	cmp	r6, r3
	bhi	.L2939
	cmp	r6, #0
	beq	.L2787
	ldr	r1, .L2965+20
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r0, #31
	add	r8, r0, #1
	movls	r9, #0
	bhi	.L2940
.L2789:
	add	r9, r9, #1
	mov	r1, r8
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r9, r6
	bne	.L2789
	ldrb	r3, [r7, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2782
.L2926:
	ldr	r1, .L2965+24
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	cmp	r0, #256
	mov	r7, r0
	bhi	.L2941
	ldr	r0, [r4, #2356]
	bl	BsResidBits
	cmp	r7, r0
	bhi	.L2793
	cmp	r7, #0
	movne	r6, #0
	beq	.L2782
.L2795:
	add	r6, r6, #1
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	cmp	r6, r7
	bne	.L2795
	b	.L2782
.L2931:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2942
	ldr	r3, [r8, #116]
	mov	r2, #1
	ldr	r6, [r4, #188]
	mov	r3, r2, asl r3
	str	r3, [fp, #-80]
	mov	r1, r3
	mov	r0, r6
	bl	__aeabi_uidivmod
	cmp	r1, #0
	rsb	r3, r1, r6
	streq	r1, [fp, #-76]
	beq	.L2698
	ldr	r2, [fp, #-80]
	cmp	r1, r2, lsr #1
	mov	r2, #0
	str	r2, [fp, #-76]
	bcs	.L2811
.L2698:
	ldr	r2, [r5, #132]
	ldr	r1, [fp, #-48]
	sub	r2, r2, #16
	cmp	r2, #2
	ldr	r2, [fp, #-76]
	add	r9, r4, r1, lsl #2
	movls	r3, #0
	add	r3, r3, r2
	str	r3, [r5, #116]
	ldr	r2, [r9, #212]
	cmp	r3, r2
	bge	.L2700
	ldrb	r0, [r5, #104]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L2943
.L2700:
	ldr	r3, [r4, #2332]
	cmp	r3, #0
	ldreq	r3, [r5, #116]
	streq	r3, [r4, #192]
	ldr	r3, [r5, #128]
	cmp	r3, #0
	bne	.L2702
	ldr	r3, [r5, #132]
	cmp	r3, #15
	bhi	.L2703
	tst	r3, #1
	movne	r2, #1
	beq	.L2703
.L2704:
	sub	r3, r3, #7
	bics	r3, r3, #2
	andne	r3, r2, #1
	moveq	r3, #0
	cmp	r3, #0
	ldrne	r3, [r5, #116]
	strne	r3, [r4, #188]
.L2702:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L2705
	ldr	r3, [r8, #176]
	mov	r1, #0
	cmp	r3, #1
	movhi	r2, #1
	bls	.L2707
.L2709:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L2709
	cmp	r1, #0
	bne	.L2944
.L2710:
	mov	r2, #164
	add	r0, r5, #1024
	mla	r1, r2, r1, r8
	add	r3, r4, #5120
	add	r0, r0, #12
	add	r3, r3, #12
	str	r3, [fp, #-84]
	add	r1, r1, #2160
	add	r1, r1, #4
	bl	memcpy
.L2708:
	ldrb	r3, [r8, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2712
	ldr	r3, [r8, #180]
	ldr	r6, [r5, #1040]
	cmp	r3, #0
	ldr	r2, [r5, #1036]
	streq	r3, [fp, #-48]
	add	r6, r6, r2
	streq	r3, [fp, #-56]
	bne	.L2945
.L2713:
	ldr	r1, .L2965+28
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r2, [r5, #1036]
	ldr	r3, [r5, #1040]
	ldr	ip, [fp, #-48]
	add	r1, r3, r2
	add	r0, r0, ip
	str	r0, [fp, #-60]
	add	r1, r1, r0
	cmp	r1, #16
	bhi	.L2946
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	add	r3, r6, r3
	str	r3, [fp, #-88]
	beq	.L2729
	ldr	r3, [fp, #-88]
	str	r7, [fp, #-92]
	add	r9, r3, #5120
	add	ip, r3, #1056
	add	r9, r9, #23
	add	ip, ip, #15
	add	r3, r4, r9
	add	r10, r4, ip, lsl #2
	mov	r2, r3
	mov	r3, #0
	mov	r9, r3
	str	r3, [fp, #-52]
	mov	r7, r2
	b	.L2728
.L2950:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ldreq	r0, [fp, #-56]
	bne	.L2947
.L2720:
	add	r3, r8, r0
	add	r0, r8, r0, lsl #2
	ldrb	r3, [r3, #13]	@ zero_extendqisi2
	ldr	r6, [r0, #196]
	strb	r3, [r7]
.L2723:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	cmp	r0, #0
	bne	.L2948
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-52]
	cmp	r9, r3
	cmpne	r9, #0
	str	r6, [r10, #944]
	str	r0, [r10]
	ldr	r3, [r5, #116]
	moveq	r2, #0
	str	r2, [fp, #-52]
	rsb	r6, r3, r6
	str	r6, [r10, #876]
.L2726:
	ldr	r3, [fp, #-60]
	add	r9, r9, #1
	sub	r10, r10, #4
	sub	r7, r7, #1
	cmp	r9, r3
	beq	.L2949
.L2728:
	ldr	r3, [fp, #-48]
	cmp	r3, r9
	bhi	.L2950
	ldr	r1, [r8, #120]
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	mov	r6, r0
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r7]
	b	.L2723
.L2798:
	cmp	r3, #0
	beq	.L2799
	ldr	r3, [r5, #136]
	ldrb	r2, [fp, #-68]	@ zero_extendqisi2
	add	r3, r4, r3
	strb	r2, [r3, #5]
	b	.L2797
.L2928:
	ldr	r2, [r5, #132]
	cmp	r2, #21
	moveq	r2, #1
	streqb	r2, [r3, #4]
	bne	.L2797
	b	.L2801
.L2942:
	ldr	r1, [r8, #120]
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r3, [r8, #116]
	mov	r2, #1
	ldr	r6, [r4, #188]
	mov	r3, r2, asl r3
	str	r3, [fp, #-80]
	mov	r1, r3
	mov	r9, r0
	str	r0, [fp, #-76]
	mov	r0, r6
	bl	__aeabi_uidivmod
	cmp	r9, r1
	rsb	r3, r1, r6
	bcs	.L2697
	ldr	r2, [fp, #-76]
	ldr	r0, [fp, #-80]
	rsb	r2, r2, r1
	cmp	r2, r0, lsr #1
	bcc	.L2697
.L2811:
	ldr	r2, [fp, #-80]
	add	r3, r3, r2
	b	.L2698
.L2703:
	sub	r2, r3, #16
	cmp	r2, #7
	movhi	r2, #0
	movls	r2, #1
	b	.L2704
.L2948:
	ldr	r1, .L2965+32
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r3, [fp, #-48]
	ldr	r2, [fp, #-76]
	cmp	r9, #0
	cmpne	r9, r3
	ldrne	r3, [fp, #-52]
	addne	r0, r0, r3
	mov	r3, #1
	str	r3, [r10]
	ldr	r3, [r5, #116]
	str	r0, [fp, #-52]
	rsb	r1, r2, r3
	ldr	r2, [fp, #-80]
	add	r6, r1, r6
	mls	r0, r2, r0, r6
	rsb	r3, r3, r0
	str	r3, [r10, #876]
	str	r0, [r10, #944]
	b	.L2726
.L2947:
	ldr	r1, [fp, #-72]
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r3, [r8, #180]
	sub	r3, r3, #1
	cmp	r0, #0
	blt	.L2722
	cmp	r3, r0
	bcs	.L2720
.L2722:
	str	r3, [sp]
	mov	r2, r9
	mov	r3, r0
	ldr	r1, .L2965+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2932:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #109]
	cmp	r0, #0
	bne	.L2951
	ldr	r3, [r5, #124]
	ldr	r2, [r7, #40]
	cmp	r3, #0
	str	r2, [r5, #180]
	bne	.L2740
	ldr	r2, [r7, #44]
	mov	r6, r3
	mov	r9, r3
	str	r2, [r5, #184]
.L2741:
	ldr	r3, [fp, #-84]
	cmp	r3, #0
	beq	.L2952
	ldr	r3, [fp, #-84]
	ldr	r2, [r3, #8]
	cmp	r2, #16
	bhi	.L2744
	cmp	r2, #0
	moveq	r3, r2
	beq	.L2746
	ldr	r3, [fp, #-84]
	add	r2, r2, #11
	add	r1, r3, #11
	add	r2, r3, r2
	mov	r3, #0
.L2748:
	ldrb	r0, [r1, #1]!	@ zero_extendqisi2
	cmp	r0, #0
	addne	r3, r3, #1
	cmp	r1, r2
	bne	.L2748
	cmp	r3, #1
	movle	r2, #0
	movgt	r2, #1
.L2746:
	ldrb	r1, [r7, #22]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r2, #0
	andne	r2, r2, #1
	cmp	r2, #0
	beq	.L2953
	add	r2, r4, #5248
	add	r1, r4, #4160
	add	r2, r2, #48
	add	r1, r1, #40
	mov	r0, r4
	bl	HEVC_DecRefPicListsModification
	cmp	r0, #0
	bne	.L2954
.L2742:
	ldr	r3, [r5, #124]
	cmp	r3, #0
	beq	.L2808
.L2749:
	cmp	r3, #2
	beq	.L2734
.L2809:
	ldrb	r3, [r7, #5]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2955
.L2750:
	ldrb	r3, [r5, #108]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r5, #124]
	beq	.L2759
	cmp	r3, #0
	beq	.L2956
	cmp	r3, #2
	mov	r3, #1
	strb	r3, [r5, #112]
	beq	.L2756
.L2755:
	ldr	r3, [r5, #180]
	cmp	r3, #1
	bls	.L2910
.L2758:
	ldr	r1, .L2965+40
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldrb	r2, [r5, #112]	@ zero_extendqisi2
	cmp	r2, #0
	subne	r6, r9, #1
	subeq	r6, r6, #1
	cmp	r6, r0
	str	r0, [r5, #148]
	movcs	r3, #0
	movcc	r3, #1
	orrs	r3, r3, r0, lsr #31
	bne	.L2762
.L2910:
	ldr	r3, [r5, #124]
	b	.L2759
.L2799:
	ldr	r3, [r5, #136]
	add	r3, r4, r3
	b	.L2797
.L2911:
	ldrb	r0, [r5, #113]	@ zero_extendqisi2
	b	.L2774
.L2949:
	ldr	r7, [fp, #-92]
.L2729:
	ldr	r3, [fp, #-88]
	cmp	r3, #16
	str	r3, [r5, #1044]
	bhi	.L2957
.L2712:
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	cmp	r3, #0
	streqb	r3, [r5, #108]
	bne	.L2958
.L2731:
	ldrb	r3, [r8, #6]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2806
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #106]
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r5, #107]
	b	.L2806
.L2953:
	ldr	r3, [r5, #124]
	cmp	r3, #0
	bne	.L2809
.L2808:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r3, [r5, #124]
	strb	r0, [r5, #110]
	b	.L2749
.L2930:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	b	.L2694
.L2672:
	str	r3, [sp]
	mov	r3, r0
	ldr	r2, .L2965+44
	mov	r0, #1
	ldr	r1, .L2965+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2936:
	ldr	r1, .L2965+52
	ldr	r0, [r4, #2356]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #156]
	cmp	r3, #24
	bhi	.L2959
	ldr	r3, [r7, #60]
	add	r2, r0, r3
	add	r2, r2, #12
	cmp	r2, #24
	bhi	.L2960
	ldr	r1, .L2965+56
	ldr	r0, [r4, #2356]
	bl	HEVC_se_v
	add	r3, r0, #12
	str	r0, [r5, #160]
	cmp	r3, #24
	bhi	.L2961
	ldr	r2, [r7, #64]
	add	r2, r0, r2
	add	r3, r2, #12
	cmp	r3, #24
	bls	.L2769
	ldr	r1, .L2965+60
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2955:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r5, #111]
	b	.L2750
.L2812:
	mov	r1, #0
	b	.L2683
.L2740:
	mov	r6, r0
	mov	r9, r0
	str	r0, [r5, #184]
.L2739:
	cmp	r3, #2
	bne	.L2741
	b	.L2742
.L2697:
	ldr	r2, [fp, #-76]
	cmp	r2, r1
	bls	.L2698
	rsb	r1, r1, r2
	ldr	r2, [fp, #-80]
	cmp	r1, r2, lsr #1
	rsbhi	r3, r2, r3
	b	.L2698
.L2914:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #1
	strb	r0, [r5, #106]
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r5, #107]
	b	.L2804
.L2705:
	add	r6, r4, #5120
	ldr	r3, [r8, #176]
	add	r6, r6, #12
	mov	r1, r8
	mov	r0, r4
	mov	r2, r6
	bl	HEVC_DecShortTermRefPicSet
	cmp	r0, #0
	streq	r6, [fp, #-84]
	beq	.L2708
	ldr	r1, .L2965+64
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2951:
	ldr	r1, .L2965+68
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	add	r9, r0, #1
	cmp	r9, #16
	bhi	.L2962
	ldr	r3, [r5, #124]
	str	r9, [r5, #180]
	cmp	r3, #0
	movne	r6, #0
	strne	r6, [r5, #184]
	bne	.L2739
	ldr	r1, .L2965+72
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	add	r6, r0, #1
	cmp	r6, #16
	strls	r6, [r5, #184]
	ldrls	r3, [r5, #124]
	bls	.L2739
	mov	r2, r6
	mov	r3, #16
	ldr	r1, .L2965+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2944:
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r3, [r8, #176]
	subs	r1, r0, #0
	sublt	r3, r3, #1
	blt	.L2711
.L2707:
	sub	r3, r3, #1
	cmp	r3, r1
	bcs	.L2710
.L2711:
	mov	r2, r1
	mov	r0, #1
	ldr	r1, .L2965+80
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2956:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	ldr	r3, [r5, #124]
	cmp	r3, #2
	uxtb	r0, r0
	strb	r0, [r5, #112]
	beq	.L2767
	cmp	r0, #0
	bne	.L2755
	ldr	r2, [r5, #184]
	cmp	r2, #1
	bhi	.L2758
	b	.L2759
.L2756:
	mov	r3, #2
	b	.L2763
.L2941:
	mov	r2, r0
	ldr	r1, .L2965+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2957:
	ldr	r2, [fp, #-88]
	mov	r3, #16
	ldr	r1, .L2965+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2681:
	mov	r2, r10
	ldr	r1, .L2965+92
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2958:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r5, #108]
	b	.L2731
.L2938:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	strb	r0, [r5, #114]
	b	.L2688
.L2937:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	tst	r0, #255
	beq	.L2775
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r5, #113]
	cmp	r0, #0
	bne	.L2774
	ldr	r1, .L2965+96
	ldr	r0, [r4, #2356]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #164]
	bhi	.L2963
.L2776:
	ldr	r1, .L2965+100
	ldr	r0, [r4, #2356]
	bl	HEVC_se_v
	add	r3, r0, #6
	mov	r2, r0
	cmp	r3, #12
	str	r0, [r5, #168]
	bls	.L2911
	ldr	r1, .L2965+104
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #80]
	ldrb	r0, [r5, #113]	@ zero_extendqisi2
	str	r3, [r5, #168]
	b	.L2774
.L2922:
	ldr	r3, [r4, #236]
	mov	r0, r4
	cmp	r3, #0
	ldrne	r3, [r4, #192]
	str	r3, [r5, #116]
	bl	HEVC_IsNewPic
	ldr	r1, .L2965+108
	str	r0, [r5, #256]
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2945:
	ldr	r1, .L2965+112
	ldr	r0, [r4, #2356]
	bl	HEVC_ue_v
	ldr	r3, [r8, #180]
	cmp	r0, r3
	mov	r2, r0
	str	r0, [fp, #-48]
	bhi	.L2964
	cmp	r3, #1
	movls	r3, #0
	strls	r3, [fp, #-56]
	bls	.L2713
	mov	r2, #0
	mov	r1, r2
	mov	r2, #1
.L2715:
	add	r1, r1, #1
	cmp	r3, r2, asl r1
	bhi	.L2715
	str	r1, [fp, #-72]
	str	r1, [fp, #-56]
	b	.L2713
.L2935:
	ldr	r1, .L2965+116
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2943:
	ldr	r1, .L2965+120
	bl	dprint_vfmw
	b	.L2700
.L2687:
	mov	r2, r0
	ldr	r1, .L2965+124
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2929:
	mov	r2, r0
	ldr	r1, .L2965+128
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2744:
	mov	r3, #16
	ldr	r1, .L2965+132
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2934:
	ldr	r1, .L2965+136
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2762:
	mov	r3, r0
	str	r6, [sp]
	ldr	r1, .L2965+140
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2939:
	mov	r2, r6
	ldr	r1, .L2965+144
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2793:
	mov	r2, r0
	mov	r3, r7
	ldr	r1, .L2965+148
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2963:
	ldr	r1, .L2965+152
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r7, #76]
	str	r3, [r5, #164]
	b	.L2776
.L2960:
	mov	r2, r0
	ldr	r1, .L2965+156
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2959:
	mov	r2, r0
	ldr	r1, .L2965+160
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2961:
	mov	r2, r0
	ldr	r1, .L2965+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2946:
	str	r0, [sp]
	mov	ip, #16
	ldr	r1, .L2965+168
	mov	r0, #1
	str	ip, [sp, #4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2933:
	ldr	r1, .L2965+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2964:
	ldr	r1, .L2965+176
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2966:
	.align	2
.L2965:
	.word	.LC366
	.word	.LC371
	.word	.LC393
	.word	.LC395
	.word	.LC407
	.word	.LC409
	.word	.LC411
	.word	.LC378
	.word	.LC381
	.word	.LC380
	.word	.LC390
	.word	.LANCHOR0+524
	.word	.LC367
	.word	.LC397
	.word	.LC400
	.word	.LC402
	.word	.LC374
	.word	.LC383
	.word	.LC385
	.word	.LC386
	.word	.LC375
	.word	.LC412
	.word	.LC382
	.word	.LC369
	.word	.LC403
	.word	.LC405
	.word	.LC406
	.word	.LC368
	.word	.LC376
	.word	.LC396
	.word	.LC373
	.word	.LC370
	.word	.LC372
	.word	.LC388
	.word	.LC394
	.word	.LC391
	.word	.LC408
	.word	.LC413
	.word	.LC404
	.word	.LC399
	.word	.LC398
	.word	.LC401
	.word	.LC379
	.word	.LC392
	.word	.LC377
	.word	.LC384
	.word	.LC387
	.word	.LC389
	.word	.LC410
.L2962:
	mov	r2, r9
	mov	r3, #16
	ldr	r1, .L2965+180
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2952:
	ldr	r1, .L2965+184
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2954:
	ldr	r1, .L2965+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
.L2940:
	mov	r2, r8
	ldr	r1, .L2965+192
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2906
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
	ldr	r1, [r0, #2376]
	mov	r4, r0
	cmp	r1, #0
	beq	.L2968
	ldr	r0, [r0, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L2968:
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
	ldr	r1, [r0, #2376]
	mov	r4, r0
	cmp	r1, #0
	beq	.L2974
	ldr	r0, [r0, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L2974:
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
	beq	.L2982
	mov	r4, #0
	mov	r6, r4
.L2981:
	ldr	r3, [r5, #2396]
	ldr	r1, [r3, r4, asl #2]
	cmp	r1, #0
	beq	.L2980
	ldr	r0, [r5, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2396]
	str	r6, [r3, r4, asl #2]
.L2980:
	ldr	r3, [r5, #168]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L2981
.L2982:
	mov	r0, #0
	mov	r3, #2
	str	r0, [r5, #204]
	str	r0, [r5, #244]
	str	r0, [r5, #236]
	strb	r0, [r5, #11]
	str	r3, [r5, #176]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_ClearAllSlice, .-HEVC_ClearAllSlice
	.align	2
	.global	HEVC_InitDPB
	.type	HEVC_InitDPB, %function
HEVC_InitDPB:
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
	mov	r5, r0
	mov	r8, r1
	bl	HEVC_ClearAllSlice
	add	r9, r5, #2592
	mov	r4, r5
	add	r9, r9, #12
	mov	r7, #17
	mov	r6, #0
.L2993:
	ldr	r3, [r9, #4]!
	mov	r2, #1
	cmp	r3, #0
	beq	.L2989
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L2989:
	ldr	r3, [r4, #2676]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2990
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L2990:
	ldr	r3, [r4, #2744]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2991
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L2991:
	ldr	r3, [r4, #2812]
	mov	r2, #1
	cmp	r3, #0
	beq	.L2992
	ldr	r1, [r3, #28]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
.L2992:
	subs	r7, r7, #1
	str	r6, [r4, #2812]
	str	r6, [r4, #2744]
	add	r4, r4, #4
	str	r6, [r4, #2672]
	str	r6, [r4, #2604]
	bne	.L2993
	ldr	r3, [r5, #2388]
	ldr	r3, [r3, #184]
	add	r3, r3, #1
	str	r3, [r5, #2584]
	cmp	r3, #17
	bhi	.L3031
.L2994:
	ldr	r3, .L3034
	mov	r4, #0
	add	r0, r5, #12480
	mov	r1, r4
	mov	r2, #200
	str	r4, [r5, #2588]
	ldr	r3, [r3, #48]
	add	r0, r0, #40
	str	r4, [r5, #2600]
	str	r4, [r5, #2604]
	str	r4, [r5, #2596]
	str	r4, [r5, #2592]
	blx	r3
	add	r2, r5, #2400
	add	r1, r5, #12288
	add	r2, r2, #12
	add	r3, r5, #2480
	mov	r0, r4
	mov	ip, #16
	str	r4, [r1, #236]
	str	ip, [r1, #232]
.L2995:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L2995
	add	r2, r5, #2544
	add	ip, r5, #4096
	add	r2, r2, #4
	mov	r0, r1
	str	r1, [ip, #172]
.L2996:
	str	r0, [r3, #4]!
	cmp	r3, r2
	mov	r1, #0
	bne	.L2996
	cmp	r8, r1
	str	r1, [ip, #176]
	bne	.L2997
	ldr	r3, [r5, #2404]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	beq	.L2997
.L2998:
	ldr	r1, [r5, #184]
	cmp	r1, #0
	addne	r2, r5, #2128
	movne	r3, #0
	movne	r0, r3
	beq	.L3007
.L3006:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L3006
.L3007:
	ldr	r3, [r5, #168]
	cmp	r3, #0
	movne	r4, #0
	movne	r6, r4
	beq	.L3005
.L3009:
	ldr	r3, [r5, #2396]
	mov	r7, r4, asl #2
	ldr	r3, [r3, r4, asl #2]
	add	r4, r4, #1
	cmp	r3, #0
	mov	r1, r3
	beq	.L3008
	ldr	r2, [r5, #2376]
	cmp	r3, r2
	beq	.L3008
	ldr	r0, [r5, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r5, #2396]
	str	r6, [r3, r7]
.L3008:
	ldr	r3, [r5, #168]
	cmp	r3, r4
	bhi	.L3009
.L3005:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2997:
	mov	r4, #20
	mov	r0, r5
	str	r4, [r5, #180]
	str	r4, [r5, #184]
	bl	HEVC_ArrangeMem
	cmp	r0, #0
	beq	.L2999
	cmp	r0, #2
	beq	.L3032
	ldr	r2, .L3034+4
	mov	r0, #0
	ldr	r1, .L3034+8
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3031:
	mov	r4, #17
	ldr	r2, .L3034+4
	str	r4, [sp]
	mov	r3, r4
	ldr	r1, .L3034+12
	mov	r0, #1
	bl	dprint_vfmw
	str	r4, [r5, #2584]
	b	.L2994
.L2999:
	ldr	r0, [r5, #252]
	bl	FSP_GetTotalValidFsNum
	cmp	r0, #20
	movgt	r0, r4
	ble	.L3033
.L3002:
	str	r0, [r5, #180]
	b	.L2998
.L3032:
	add	r0, r5, #5504
	add	r0, r0, #56
	bl	ResetVoQueue
	mvn	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3033:
	ldr	r0, [r5, #252]
	bl	FSP_GetTotalValidFsNum
	b	.L3002
.L3035:
	.align	2
.L3034:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+552
	.word	.LC414
	.word	.LC148
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
	beq	.L3040
	mov	r4, #0
	mov	r5, r4
	b	.L3039
.L3038:
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r5
	bls	.L3040
.L3039:
	ldr	r1, [r6, #2400]
	add	r5, r5, #1
	add	r1, r1, r4
	add	r4, r4, #96
	ldr	r3, [r1, #32]
	cmp	r3, #1
	bne	.L3038
	ldr	r0, [r6, #252]
	bl	HEVC_ReleaseNAL
	ldr	r3, [r6, #168]
	add	r3, r3, #1
	cmp	r3, r5
	bhi	.L3039
.L3040:
	mov	r0, #0
	strb	r0, [r6, #7]
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
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L3059
	mov	r7, r0
	mov	r0, #22
	mov	r5, #0
	bl	dprint_vfmw
	mov	r2, #1
	mvn	r3, #-2147483648
	strb	r2, [r7, #5]
	str	r3, [r7, #228]
	mov	r0, r7
	mov	r3, #-2147483647
	strb	r5, [r7, #4]
	str	r3, [r7, #212]
	add	r4, r7, #12800
	str	r3, [r7, #232]
	mov	r6, r5
	strb	r5, [r7, #10]
	mov	r9, #20
	bl	HEVC_ClearAllNal
	add	r0, r7, #5504
	add	r0, r0, #56
	ldr	r8, .L3059+4
	bl	ResetVoQueue
.L3044:
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
	str	r3, [r4, #-8]
	add	r4, r4, #712
	bne	.L3044
	add	r3, r7, #2128
	add	r1, r7, #2208
	mov	r2, #0
.L3045:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L3045
	ldr	r3, [r7, #168]
	cmp	r3, #0
	beq	.L3046
	mov	r3, #0
	mov	r1, r3
.L3047:
	ldr	r2, [r7, #2396]
	str	r1, [r2, r3, asl #2]
	add	r3, r3, #1
	ldr	r2, [r7, #168]
	cmp	r2, r3
	bhi	.L3047
.L3046:
	add	r0, r7, #12480
	ldr	r3, [r8, #48]
	mov	r2, #200
	mov	r1, #0
	add	r0, r0, #40
	blx	r3
	add	r3, r7, #12288
	add	ip, r7, #2800
	add	r0, r7, #2736
	add	r1, r7, #2592
	add	ip, ip, #8
	add	r0, r0, #4
	add	r1, r1, #12
	add	lr, r7, #2672
	mov	r2, #16
	str	r2, [r3, #232]
	mov	r2, #17
	mov	r3, #0
.L3048:
	subs	r2, r2, #1
	str	r3, [ip, #4]!
	str	r3, [r0, #4]!
	str	r3, [lr, #4]!
	str	r3, [r1, #4]!
	bne	.L3048
	add	r0, r7, #2400
	add	r1, r7, #2544
	add	r0, r0, #12
	add	r1, r1, #4
	add	r3, r7, #2480
	mov	ip, r2
	mov	lr, #17
	str	r2, [r7, #2588]
	str	r2, [r7, #2592]
	str	r2, [r7, #2596]
	str	r2, [r7, #2600]
	str	r2, [r7, #2604]
	str	lr, [r7, #2584]
.L3049:
	str	ip, [r3, #4]!
	cmp	r3, r1
	str	ip, [r0, #4]!
	mov	r4, #0
	bne	.L3049
	add	r0, r7, #4160
	mov	r6, #2
	mov	r1, r4
	ldr	r3, [r8, #48]
	str	r4, [r7, #2376]
	movw	r2, #1356
	str	r4, [r7, #204]
	add	r0, r0, #40
	str	r4, [r7, #244]
	add	r5, r7, #2544
	str	r4, [r7, #236]
	add	r5, r5, #8
	str	r6, [r7, #176]
	mov	r10, #16
	blx	r3
	add	r3, r7, #4096
	mov	r2, #1
	mov	ip, #20
	str	r6, [r3, #124]
	mov	r1, r4
	str	r2, [r3, #256]
	mov	lr, #256
	mov	r3, #8
	strb	r2, [r7, #3]
	strb	r4, [r7, #6]
	mov	r0, r5
	str	r6, [r7, #2224]
	mov	r9, #64
	ldr	r6, [r8, #48]
	mov	r2, #32
	str	r4, [r7, #172]
	movw	r8, #1025
	mov	r4, #6
	str	ip, [r7, #180]
	str	ip, [r7, #184]
	str	r3, [r7, #196]
	str	r3, [r7, #200]
	str	r10, [r7, #324]
	str	r9, [r7, #328]
	str	lr, [r7, #332]
	str	r8, [r7, #336]
	str	r4, [r7, #2212]
	str	r4, [r7, #2216]
	str	r4, [r7, #2220]
	blx	r6
	str	r5, [r7, #2356]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3060:
	.align	2
.L3059:
	.word	.LC415
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
	mov	r4, r0
	bl	HEVC_ClearAllSlice
	ldr	r3, [r4, #3564]
	cmp	r3, #0
	beq	.L3062
	ldr	r1, [r3, #28]
	mov	r2, #1
	ldr	r0, [r4, #252]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3564]
	mov	r3, #0
	str	r3, [r2, #48]
	str	r3, [r4, #3564]
.L3062:
	mov	r0, #0
	strb	r0, [r4, #3505]
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
	bne	.L3069
	add	r0, r4, #5504
	add	r0, r0, #56
	bl	ResetVoQueue
	ldr	r0, [r4, #252]
	bl	FSP_EmptyInstance
.L3068:
	mov	r0, r4
	bl	HEVC_InitDecPara
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3069:
	add	r1, r4, #5504
	ldr	r0, [r4, #252]
	add	r1, r1, #56
	bl	FSP_ClearNotInVoQueue
	b	.L3068
	UNWIND(.fnend)
	.size	HEVC_ClearAll, .-HEVC_ClearAll
	.align	2
	.global	HEVC_InitPic
	.type	HEVC_InitPic, %function
HEVC_InitPic:
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
	ldr	r2, [r0, #264]
	add	r3, r0, #4096
	mov	r4, r0
	ldr	r7, [r0, #268]
	ldr	r1, [r3, #140]
	str	r2, [fp, #-52]
	ldr	r2, [r0, #272]
	cmp	r1, #0
	ldr	r8, [r0, #276]
	str	r2, [fp, #-48]
	blt	.L3086
	ldr	r2, [r0, #164]
	cmp	r1, r2
	bge	.L3086
	ldr	r2, [r0, #2368]
	mov	lr, #1888
	ldr	ip, [r3, #136]
	movw	r0, #12660
	ldr	r6, [r4, #2364]
	mla	r2, lr, r1, r2
	add	ip, r4, ip, lsl #2
	ldr	r5, [r4, #2360]
	ldr	r3, [r2, #32]
	mul	r3, r0, r3
	add	r9, r6, r3
	ldr	lr, [r9, #48]
	str	r1, [ip, #224]
	ldr	r1, [r2, #32]
	mov	r0, lr, asl #7
	add	r0, r0, lr, lsl #2
	str	r1, [ip, #220]
	add	r1, r5, r0
	ldr	r0, [r9, #48]
	str	r0, [ip, #216]
	ldr	r5, [r9, #128]
	ldr	r0, [r9, #64]
	subs	r5, r8, r5
	ldr	ip, [r4, #172]
	movne	r5, #1
	clz	r10, ip
	cmp	r7, r0
	mov	r10, r10, lsr #5
	movne	r0, #1
	strne	r0, [fp, #-56]
	beq	.L3105
.L3072:
	ldr	r0, [r4, #2384]
	orr	r5, r5, r10
	ldr	lr, [r1, #4]
	ldr	ip, [fp, #-56]
	ldr	r0, [r0, #4]
	orr	r5, ip, r5
	cmp	r0, lr
	movne	r0, #1
	beq	.L3106
.L3073:
	orrs	r0, r0, r10
	beq	.L3074
	mov	r0, r4
	str	r3, [fp, #-64]
	str	r2, [fp, #-60]
	bl	HEVC_UpdatePicVPS
	ldr	r3, [fp, #-64]
	ldr	r2, [fp, #-60]
.L3074:
	ldr	r1, [r4, #2388]
	ldr	r0, [r9, #56]
	ldr	lr, [r1, #56]
	cmp	lr, r0
	movne	r6, #1
	beq	.L3107
.L3075:
	orrs	r6, r6, r5
	beq	.L3076
	ldr	lr, [r1, #184]
	mov	r0, r4
	ldr	r6, [r9, #184]
	mov	r1, r9
	str	r2, [fp, #-60]
	subs	r6, r6, lr
	movne	r6, #1
	bl	HEVC_UpdatePicSPS
	ldr	r2, [fp, #-60]
.L3076:
	ldr	r0, [r4, #2392]
	ldr	r1, [r2, #28]
	ldr	r0, [r0, #28]
	cmp	r0, r1
	movne	r1, #1
	beq	.L3108
.L3077:
	orrs	r3, r1, r5
	beq	.L3078
	mov	r1, r9
	mov	r0, r4
	bl	HEVC_UpdatePicPPS
.L3078:
	ldr	r1, [r4, #2388]
	ldr	r0, [r4, #2404]
	ldr	r2, [r1, #96]
	ldr	r1, [r1, #88]
	cmp	r2, r1
	movcc	r2, r1
	str	r2, [r0, #900]
	ldr	r2, [r4, #2332]
	cmp	r2, #0
	bne	.L3079
	ldr	r3, [r9, #56]
	ldr	r2, [fp, #-52]
	cmp	r2, r3
	beq	.L3109
.L3080:
	str	r6, [sp]
	mov	r3, r8
	ldr	r2, [fp, #-48]
	mov	r1, r7
	mov	r0, r4
	bl	HEVC_GetReRangeFlag
	cmp	r0, #0
	bne	.L3081
	ldr	r3, [r4, #2404]
	ldr	r2, [r3, #888]
	cmp	r2, #1
	beq	.L3081
.L3083:
	mov	r2, #0
	str	r2, [r3, #904]
.L3082:
	mov	r0, r4
	bl	HEVC_AllocFrameStore
	subs	r5, r0, #0
	beq	.L3079
	ldr	r1, .L3110
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L3071
.L3086:
	mov	r0, #0
.L3071:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3079:
	mov	r0, r4
	bl	HEVC_InitPicInfo
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3109:
	ldr	r3, [fp, #-56]
	orr	ip, r3, r10
	orrs	r3, ip, r6
	bne	.L3080
	ldr	r3, [r4, #2404]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L3082
.L3081:
	mov	r1, #1
	mov	r0, r4
	bl	HEVC_InitDPB
	cmn	r0, #2
	beq	.L3071
	cmp	r0, #0
	bne	.L3084
	ldr	r3, [r4, #2404]
	b	.L3083
.L3108:
	ldrb	r1, [r2, #1]	@ zero_extendqisi2
	adds	r1, r1, #0
	movne	r1, #1
	b	.L3077
.L3107:
	ldrb	r6, [r6, r3]	@ zero_extendqisi2
	adds	r6, r6, #0
	movne	r6, #1
	b	.L3075
.L3106:
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	b	.L3073
.L3105:
	ldr	r0, [r9, #68]
	ldr	ip, [fp, #-48]
	subs	r0, ip, r0
	movne	r0, #1
	str	r0, [fp, #-56]
	b	.L3072
.L3084:
	mov	r2, r0
	ldr	r1, .L3110+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_ClearAll
	mvn	r0, #0
	b	.L3071
.L3111:
	.align	2
.L3110:
	.word	.LC417
	.word	.LC416
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, [r0, #3544]
	mov	r4, r0
	ldr	r5, [r0, #3564]
	add	r1, r0, #3568
	mov	r2, #632
	add	r0, r5, #80
	str	r3, [r5, #16]
	bl	memcpy
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_GetImagePara
	ldrb	r3, [r4, #3504]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3119
.L3113:
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r2, .L3120
	mov	r0, #0
	ldr	r1, .L3120+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3119:
	mov	r2, #1
	ldr	r1, [r5, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	b	.L3113
.L3121:
	.align	2
.L3120:
	.word	.LANCHOR0+568
	.word	.LC418
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
	bne	.L3125
	ldr	r1, [r4, #3564]
	add	r3, r4, #8192
	mov	r2, #1
	mov	r0, #2
	str	r0, [r1, #52]
	mov	r0, r5
	str	r2, [r3, #2968]
	ldr	r3, [r4, #3512]
	ldr	r1, [r4, #3516]
	add	r3, r4, r3, lsl #2
	str	r1, [r3, #212]
	ldr	r3, [r4, #3564]
	strb	r2, [r3, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3125:
	ldr	r2, .L3126
	mov	r0, #1
	ldr	r1, .L3126+4
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3127:
	.align	2
.L3126:
	.word	.LANCHOR0+588
	.word	.LC419
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
	beq	.L3136
	cmn	r6, #3
	bne	.L3137
.L3132:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3136:
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	beq	.L3132
	ldr	r2, .L3138
	mov	r0, r6
	ldr	r1, .L3138+4
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3137:
	mov	r3, r6
	movw	r2, #11772
	ldr	r1, .L3138+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #228]
	mov	r0, r4
	bl	HEVC_DECRecycleImage
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3139:
	.align	2
.L3138:
	.word	.LANCHOR0+612
	.word	.LC418
	.word	.LC420
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
	ldr	r4, [r0, #3564]
	mov	r5, r0
	mov	ip, #2
	mov	r6, #0
	mov	r3, #1
	add	r1, r0, #3568
	str	ip, [r4, #48]
	add	r0, r4, #80
	strb	r3, [r4, #2]
	mov	r2, #632
	strb	r6, [r4, #1]
	ldr	r3, [r5, #3520]
	str	r3, [r4, #12]
	ldr	r3, [r5, #3544]
	str	r3, [r4, #16]
	bl	memcpy
	mov	r2, r6
	str	r6, [r4, #56]
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #252]
	bl	FSP_SetRef
	mov	r1, r4
	mov	r0, r5
	bl	HEVC_OutputFrmToVO
	ldr	r3, .L3141
	str	r6, [r4, #48]
	mov	r1, r6
	mov	r2, #696
	ldr	r3, [r3, #48]
	mov	r7, r0
	add	r0, r5, #3504
	blx	r3
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3142:
	.align	2
.L3141:
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
	ldr	r3, [r4, #3540]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	addne	r3, r3, #532
	movne	r1, #0
	addne	r3, r4, r3, lsl #2
	strne	r1, [r3, #4]
	strne	r2, [r4, #3540]
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
	ldr	ip, [r0, #2588]
	mov	r6, r0
	ldr	r7, [r0, #3512]
	cmp	ip, #0
	beq	.L3160
	add	lr, r7, #52
	add	r1, r0, #2592
	mov	r10, #0
	add	r1, r1, #12
	add	lr, r0, lr, lsl #2
	mov	r3, r10
	b	.L3148
.L3147:
	cmp	r3, ip
	beq	.L3146
.L3148:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L3147
	ldr	r0, [r2, #32]
	cmp	r0, r7
	bne	.L3147
	ldr	r0, [r2, #8]
	ldr	r2, [lr, #4]
	cmp	r0, r2
	addgt	r10, r10, #1
	cmp	r3, ip
	bne	.L3148
.L3146:
	ldr	r3, [r6, #2340]
	cmp	r3, #1
	beq	.L3172
	add	r3, r6, #4096
	ldr	r2, [r6, #2388]
	ldr	r3, [r3, #128]
	add	r3, r3, #90
	ldr	r9, [r2, r3, asl #2]
.L3150:
	cmp	ip, #0
	beq	.L3161
	add	r8, r7, #52
	add	r5, r6, #2592
	mov	r4, #0
	add	r5, r5, #12
	add	r8, r6, r8, lsl #2
	str	r4, [fp, #-48]
	b	.L3158
.L3152:
	ldr	r3, [r8, #4]
.L3154:
	cmp	r3, #0
	bne	.L3156
	ldr	r2, [r1, #8]
	cmp	r2, #0
	bge	.L3156
	cmp	r0, #0
	beq	.L3173
.L3157:
	str	r2, [sp]
	mov	r0, #31
	ldr	r2, .L3174
	ldr	r1, .L3174+4
	bl	dprint_vfmw
.L3156:
	ldr	r3, [r6, #2588]
	add	r4, r4, #1
	cmp	r3, r4
	bls	.L3171
.L3158:
	ldr	r1, [r5, #4]!
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L3152
	ldr	r3, [r1, #32]
	cmp	r3, r7
	bne	.L3152
	add	r2, r6, r7, lsl #2
	ldr	ip, [r1, #8]
	ldr	r3, [r2, #212]
	str	ip, [fp, #-52]
	cmp	ip, r3
	ble	.L3154
	add	ip, r6, #4096
	cmp	r10, r9
	str	ip, [fp, #-56]
	ldr	ip, [ip, #128]
	movhi	lr, #1
	movls	lr, #0
	cmp	ip, #7
	movhi	lr, #0
	cmp	lr, #0
	beq	.L3154
	ldr	ip, [fp, #-56]
	ldr	lr, [ip, #116]
	ldr	ip, [fp, #-52]
	cmp	ip, lr
	blt	.L3155
	add	ip, r6, r7
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L3154
.L3155:
	mov	r3, #1
	mov	r0, r6
	strb	r3, [r1, #2]
	add	r4, r4, #1
	ldr	r1, [r5]
	sub	r10, r10, #1
	str	r2, [fp, #-52]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r5]
	ldr	r2, [fp, #-52]
	ldr	r3, [r3, #8]
	str	r3, [r2, #212]
	ldr	r3, [r6, #2588]
	cmp	r3, r4
	str	r0, [fp, #-48]
	bhi	.L3158
.L3171:
	ldr	r0, [fp, #-48]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3173:
	mov	r2, r3
	ldr	r1, [r1, #28]
	ldr	r0, [r6, #252]
	bl	FSP_SetDisplay
	ldr	r2, [r5]
	ldr	r3, [r8, #4]
	ldr	r2, [r2, #8]
	b	.L3157
.L3172:
	ldr	r1, [r6, #2388]
	mov	r9, #0
	add	r3, r1, #356
	add	r1, r1, #388
.L3149:
	ldr	r2, [r3, #4]!
	cmp	r9, r2
	movcc	r9, r2
	cmp	r3, r1
	bne	.L3149
	b	.L3150
.L3160:
	mov	r10, ip
	b	.L3146
.L3161:
	str	ip, [fp, #-48]
	b	.L3171
.L3175:
	.align	2
.L3174:
	.word	.LANCHOR0+632
	.word	.LC421
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
	ldr	r3, [r4, #2608]
	strb	r2, [r3, #2]
	ldr	r1, [r4, #2608]
	bl	HEVC_OutputFrmToVO
	ldr	r3, [r4, #2608]
	ldr	r2, [r3, #32]
	ldr	r1, [r3, #8]
	add	r2, r5, r2, lsl #2
	str	r1, [r2, #212]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L3177
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveApcStore
	mov	r1, r6
	mov	r0, r5
	bl	HEVC_RemoveFrameStoreOutDPB
.L3177:
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
	bne	.L3182
	mov	r0, r4
	ldr	r1, [fp, #-24]
	bl	HEVC_OutputOneFrmFromDPB
	cmp	r0, #0
	bne	.L3183
.L3180:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L3182:
	ldr	r2, .L3184
	mov	r0, #1
	ldr	r1, .L3184+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3180
.L3183:
	ldr	r2, .L3184
	mov	r0, #1
	ldr	r1, .L3184+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3180
.L3185:
	.align	2
.L3184:
	.word	.LANCHOR0+656
	.word	.LC422
	.word	.LC423
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
	beq	.L3194
	ldr	r3, [r4, #2588]
	cmp	r3, #0
	beq	.L3188
	add	r5, r4, #2592
	mov	r6, #0
	add	r5, r5, #12
	mov	r8, #1
	b	.L3193
.L3204:
	strb	r8, [r3, #2]
	ldr	r1, [r5]
	bl	HEVC_OutputFrmToVO
	cmn	r0, #1
	mov	r9, r0
	beq	.L3203
.L3191:
	ldr	r3, [r4, #2588]
	cmp	r3, r6
	bls	.L3188
.L3193:
	ldr	r3, [r5, #4]!
	mov	r2, #0
	ldr	r0, [r4, #252]
	add	r6, r6, #1
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldr	r3, [r5]
	mov	r0, r4
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	cmp	r7, #0
	beq	.L3204
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L3191
	ldr	r3, [r5]
	ldr	r0, [r4, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetDisplay
	ldr	r3, [r4, #2588]
	cmp	r3, r6
	bhi	.L3193
.L3188:
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	mov	r9, #0
	bl	HEVC_InitDecBuffers
.L3202:
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3203:
	mov	r0, r7
	ldr	r2, .L3205
	ldr	r1, .L3205+4
	bl	dprint_vfmw
	mov	r0, r9
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3194:
	mvn	r9, #0
	b	.L3202
.L3206:
	.align	2
.L3205:
	.word	.LANCHOR0+688
	.word	.LC424
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
	ldr	r6, [r0, #2376]
	mov	r3, #0
	mov	r4, r0
	cmp	r6, r3
	str	r3, [r0, #320]
	beq	.L3237
	ldrb	r3, [r1]	@ zero_extendqisi2
	str	r3, [r6, #36]
	ldr	r3, [r0, #2404]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L3238
.L3214:
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3215
	ldr	r3, [r4, #2376]
	ldr	r2, [r3, #8]
	cmp	r2, #1
	bls	.L3216
	ldr	r0, [r3, #36]
	cmp	r0, #1
	beq	.L3215
.L3216:
	ldr	r0, [r1, #16]
	cmp	r0, #0
	ble	.L3217
	ldr	r0, [r1, #4]
	cmp	r0, #0
	beq	.L3217
	ldr	ip, [r1, #8]
	cmp	ip, #0
	bne	.L3239
.L3217:
	mov	r2, #1
	str	r2, [r3, #36]
	ldr	r1, [r1, #20]
	ldr	r0, [r4, #252]
	bl	SM_ReleaseStreamSeg
.L3213:
	ldr	r3, [r4, #2376]
	ldr	r0, [r3, #36]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
.L3211:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3239:
	mov	lr, r2, asl #5
	mov	ip, #0
	sub	r2, lr, r2, asl #2
	add	r3, r3, r2
	str	r0, [r3, #40]
	ldr	r3, [r4, #2376]
	ldr	lr, [r1, #16]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #44]
	ldr	r3, [r4, #2376]
	ldr	lr, [r1, #8]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #48]
	ldr	r3, [r4, #2376]
	ldr	lr, [r1, #20]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	lr, [r3, #64]
	ldr	r3, [r4, #2376]
	ldr	r0, [r3, #8]
	mov	r2, r0, asl #5
	sub	r2, r2, r0, asl #2
	add	r3, r3, r2
	str	ip, [r3, #56]
	ldr	r2, [r4, #2376]
	ldr	r3, [r2, #8]
	add	r3, r3, #1
	str	r3, [r2, #8]
	ldr	r3, [r4, #2404]
	ldrb	r3, [r3, #912]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3218
	ldr	r0, [r1, #16]
	ldr	r2, [r4, #3556]
	ldr	r3, [r4, #3560]
	add	r2, r2, r0
	str	r2, [r4, #3556]
	ldr	r2, [r1, #16]
	add	r3, r3, r2
	str	r3, [r4, #3560]
.L3218:
	mov	r0, r4
	bl	HEVC_CombinePacket
	mov	r3, #1
	str	r3, [r4, #320]
	b	.L3213
.L3238:
	ldr	r3, [r3, #888]
	cmp	r3, #0
	bne	.L3213
	b	.L3214
.L3237:
	ldr	r3, [r1, #16]
	cmp	r3, #0
	ble	.L3209
	ldr	r3, [r1, #4]
	cmp	r3, #0
	beq	.L3209
	ldr	r3, [r1, #8]
	str	r1, [fp, #-32]
	cmp	r3, #0
	beq	.L3209
	bl	HEVC_FindNaluArraySlot
	ldr	r1, [fp, #-32]
	cmn	r0, #1
	mov	r5, r0
	beq	.L3240
	ldr	r3, [r4, #2400]
	mov	r0, r0, asl #7
	sub	r0, r0, r5, asl #5
	mov	r2, #1
	add	r0, r3, r0
	str	r0, [r4, #2376]
	ldr	r3, [r1, #4]
	str	r3, [r0, #40]
	ldr	r3, [r4, #2376]
	ldr	r0, [r1, #16]
	str	r0, [r3, #44]
	ldr	r3, [r4, #2376]
	ldr	r0, [r1, #20]
	str	r0, [r3, #64]
	ldr	r3, [r4, #2376]
	ldr	r0, [r1, #8]
	str	r0, [r3, #48]
	ldr	r3, [r4, #2376]
	str	r6, [r3, #56]
	ldr	r3, [r4, #2376]
	str	r2, [r3, #8]
	ldr	r3, [r4, #2376]
	strb	r6, [r3]
	ldr	r3, [r4, #2376]
	ldrb	r2, [r1]	@ zero_extendqisi2
	str	r2, [r3, #36]
	ldr	r3, [r4, #2404]
	ldrb	r3, [r3, #912]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3212
	ldr	r0, [r1, #16]
	ldr	r2, [r4, #3556]
	ldr	r3, [r4, #3560]
	add	r2, r2, r0
	str	r2, [r4, #3556]
	ldr	r2, [r1, #16]
	add	r3, r3, r2
	str	r3, [r4, #3560]
.L3212:
	ldr	r3, [r1, #12]
	str	r3, [r4, #2328]
	b	.L3213
.L3215:
	ldr	r1, .L3241
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3211
.L3209:
	ldr	r1, .L3241+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3211
.L3240:
	ldr	r1, .L3241+8
	mov	r0, r6
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	mov	r0, r5
	b	.L3211
.L3242:
	.align	2
.L3241:
	.word	.LC427
	.word	.LC426
	.word	.LC425
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
	ldr	r3, [r0, #2588]
	mov	r4, r0
	cmp	r3, #0
	beq	.L3245
	add	r6, r0, #2592
	mov	r5, #0
	add	r6, r6, #12
	mov	r7, r5
	b	.L3247
.L3246:
	ldr	r3, [r4, #2588]
	cmp	r3, r5
	bls	.L3245
.L3247:
	ldr	r3, [r6, #4]!
	add	r5, r5, #1
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3246
	strb	r7, [r3, #1]
	mov	r2, #0
	ldr	r1, [r3, #28]
	ldr	r0, [r4, #252]
	bl	FSP_SetRef
	ldr	r3, [r4, #2588]
	cmp	r3, r5
	bhi	.L3247
.L3245:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L3249
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3245
	b	.L3249
.L3251:
	bl	HEVC_GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	beq	.L3250
.L3249:
	ldr	r3, [r4, #2588]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L3251
	mov	r0, r3
.L3250:
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
	beq	.L3260
	ldr	r2, .L3264
	mov	r0, #0
	ldr	r1, .L3264+4
	bl	dprint_vfmw
.L3260:
	mov	r0, r4
	mov	r1, #0
	bl	HEVC_InitDPB
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3265:
	.align	2
.L3264:
	.word	.LANCHOR0+716
	.word	.LC428
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
	b	.L3267
.L3269:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_IncreaseDPBSize
	cmp	r0, #0
	bne	.L3275
.L3267:
	ldr	ip, [r4, #2588]
	mov	r0, #13
	ldr	lr, [r4, #2584]
	ldr	r2, .L3276
	cmp	ip, lr
	ldr	r1, .L3276+4
	mov	r3, ip
	bcs	.L3269
	b	.L3271
.L3272:
	str	lr, [sp]
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_OutputUnRefPicWithMinPoc
	cmp	r0, #0
	bne	.L3270
	ldr	ip, [r4, #2588]
	ldr	lr, [r4, #2584]
.L3271:
	cmp	ip, lr
	mov	r3, ip
	ldr	r2, .L3276
	mov	r0, #1
	ldr	r1, .L3276+8
	bcs	.L3272
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L3275:
	ldr	r2, .L3276
	mov	r0, #1
	ldr	r1, .L3276+12
	bl	dprint_vfmw
	ldr	ip, [r4, #2588]
	ldr	lr, [r4, #2584]
	b	.L3271
.L3270:
	ldr	r2, .L3276
	mov	r0, #1
	ldr	r1, .L3276+16
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	mov	r0, r4
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	HEVC_ClearDPB
.L3277:
	.align	2
.L3276:
	.word	.LANCHOR0+732
	.word	.LC429
	.word	.LC431
	.word	.LC430
	.word	.LC423
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
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #16
	mov	r7, r1
	mov	r6, r0
	mov	r4, r2
	bhi	.L3282
	ldr	r3, [r2, #60]
	add	r5, r0, r1, lsl #2
	mov	r1, #1
	mov	r2, r1
	str	r3, [r5, #2608]
	str	r1, [r3, #48]
	ldr	r3, [r5, #2608]
	ldr	r0, [r0, #252]
	ldr	r1, [r3, #28]
	bl	FSP_SetRef
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r0, [r5, #2608]
	mov	r2, #632
	adds	r3, r3, #0
	add	r1, r4, #64
	movne	r3, #1
	strb	r3, [r0, #1]
	ldr	r3, [r5, #2608]
	ldr	r0, [r4, #36]
	str	r0, [r3, #20]
	ldr	r0, [r5, #2608]
	add	r0, r0, #80
	bl	memcpy
	ldr	ip, [r5, #2608]
	ldr	lr, [r4, #40]
	add	r1, r7, #1
	ldr	r3, .L3284
	mov	r2, #4
	add	r0, r6, #2608
	str	lr, [ip, #16]
	ldr	ip, [r5, #2608]
	ldr	lr, [r4, #60]
	str	lr, [ip, #72]
	ldr	ip, [r5, #2608]
	ldr	lr, [r4, #16]
	str	lr, [ip, #12]
	ldr	ip, [r5, #2608]
	ldr	lr, [r4, #12]
	str	lr, [ip, #8]
	ldr	ip, [r5, #2608]
	ldr	lr, [r4, #8]
	str	lr, [ip, #32]
	bl	qsort
	ldr	r3, [r6, #2588]
	mov	r0, r6
	add	r3, r3, #1
	str	r3, [r6, #2588]
	ldr	r1, [r4, #60]
	bl	HEVC_GetAPC
	subs	r3, r0, #0
	bne	.L3283
	mov	r0, r3
	strb	r3, [r4, #1]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3282:
	mov	r3, r1
	ldr	r2, .L3284+4
	ldr	r1, .L3284+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3283:
	ldr	r2, .L3284+4
	mov	r0, #0
	ldr	r1, .L3284+12
	bl	dprint_vfmw
	mov	r0, r6
	bl	HEVC_PrintDPBState
	mov	r0, r6
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3285:
	.align	2
.L3284:
	.word	HEVC_ComparePicByPocAsc
	.word	.LANCHOR0+756
	.word	.LC432
	.word	.LC433
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
	ldrb	r3, [r0, #3504]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #0
	bne	.L3299
	ldr	r3, [r0, #3564]
	mov	r2, #2
	str	r2, [r3, #48]
.L3288:
	ldr	r3, [r4, #3564]
	mov	r2, #1
	mov	r0, r4
	strb	r2, [r3, #2]
	ldr	r1, [r4, #3564]
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L3300
	cmn	r0, #3
	beq	.L3292
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3301
.L3292:
	mov	r0, #0
.L3289:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3299:
	bl	HEVC_SimpleSlideDPB
	add	r2, r4, #3504
	ldr	r1, [r4, #2588]
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	beq	.L3288
	str	r0, [sp]
	movw	r3, #10933
	ldr	r2, .L3302
	mov	r0, #0
	ldr	r1, .L3302+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3289
.L3301:
	ldr	r2, .L3302
	mov	r0, #0
	ldr	r1, .L3302+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3289
.L3300:
	ldr	r2, .L3302
	mov	r0, #0
	ldr	r1, .L3302+12
	bl	dprint_vfmw
	mov	r0, r5
	b	.L3289
.L3303:
	.align	2
.L3302:
	.word	.LANCHOR0+776
	.word	.LC434
	.word	.LC419
	.word	.LC435
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
	ldr	r1, [r0, #2588]
	mov	r4, r0
	ldr	r3, [r0, #2584]
	cmp	r1, r3
	bcs	.L3316
.L3305:
	add	r2, r4, #3504
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	subs	r6, r0, #0
	bne	.L3317
	ldr	r1, [r4, #3564]
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	cmn	r0, #1
	mov	r5, r0
	beq	.L3318
	cmn	r0, #3
	beq	.L3311
	mov	r0, r4
	bl	HEVC_OutputCurrPic
	cmp	r0, #0
	bne	.L3319
.L3311:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3316:
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3315
	ldr	r2, .L3320
	mov	r0, #0
	ldr	r1, .L3320+4
	bl	dprint_vfmw
.L3315:
	ldr	r1, [r4, #2588]
	b	.L3305
.L3317:
	ldr	r2, .L3320
	mov	r0, #0
	ldr	r1, .L3320+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3319:
	mov	r0, r6
	ldr	r2, .L3320
	ldr	r1, .L3320+12
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3318:
	mov	r0, r6
	ldr	r2, .L3320
	ldr	r1, .L3320+16
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3321:
	.align	2
.L3320:
	.word	.LANCHOR0+800
	.word	.LC436
	.word	.LC437
	.word	.LC419
	.word	.LC435
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
	ldr	r3, [r3, #2968]
	cmp	r3, #1
	beq	.L3323
	bl	HEVC_FirstFrameFastOut
	cmp	r0, #0
	bne	.L3340
.L3323:
	ldr	r1, [r4, #2588]
	ldr	r3, [r4, #2584]
	cmp	r1, r3
	bcs	.L3341
.L3325:
	add	r2, r4, #3504
	mov	r0, r4
	bl	HEVC_InsertFrmInDPB
	cmp	r0, #0
	bne	.L3342
	ldr	r3, [r4, #2588]
	cmp	r3, #0
	bne	.L3328
.L3329:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3328:
	mov	r0, r4
	bl	HEVC_OutputFrmFromDPB
	cmp	r0, #0
	beq	.L3329
	ldr	r2, .L3343
	mov	r0, #1
	ldr	r1, .L3343+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3341:
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #1
	beq	.L3339
	ldr	r1, .L3343+8
	mov	r0, #0
	bl	dprint_vfmw
.L3339:
	ldr	r1, [r4, #2588]
	b	.L3325
.L3342:
	mov	r2, r0
	ldr	r1, .L3343+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3340:
	ldr	r2, .L3343
	mov	r0, #0
	ldr	r1, .L3343+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3344:
	.align	2
.L3343:
	.word	.LANCHOR0+824
	.word	.LC441
	.word	.LC439
	.word	.LC440
	.word	.LC438
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r3, .L3390
	mov	r4, r0
	ldr	r2, [r0, #252]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L3380
.L3346:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	ldrb	r5, [r4, #3505]	@ zero_extendqisi2
	cmp	r5, #0
	beq	.L3381
	ldr	r2, [r4, #3544]
	cmp	r2, #0
	beq	.L3349
	ldr	r5, [r4, #3520]
	cmp	r5, #0
	beq	.L3382
.L3350:
	ldr	r3, [r4, #2404]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bcc	.L3383
.L3349:
	ldr	r3, [r4, #2412]
	ldr	r2, [r4, #3564]
	add	r3, r3, #4096
	ldr	r3, [r3, #1088]
	str	r3, [r2, #40]
	ldr	r3, [r4, #2412]
	ldr	r2, [r4, #3564]
	add	r3, r3, #4096
	ldr	r3, [r3, #1092]
	str	r3, [r2, #44]
	ldr	r3, [r4, #256]
	cmp	r3, #2
	beq	.L3384
	ldr	r3, [r4, #2404]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	beq	.L3385
	cmp	r3, #1
	beq	.L3386
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bls	.L3360
.L3362:
	mov	r0, r4
	mvn	r5, #0
	bl	HEVC_ClearCurrPic
	ldr	r2, .L3390+4
	ldr	r1, .L3390+8
	mov	r0, #1
	bl	dprint_vfmw
.L3361:
	mov	r3, #0
	mov	r0, r5
	strb	r3, [r4, #3505]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3380:
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L3346
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L3346
	add	r3, r0, #8192
	ldrb	r3, [r3, #2912]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3346
	bl	HEVC_Sei_Get_Frame_Pts
	b	.L3346
.L3381:
	ldr	r2, .L3390+4
	mov	r0, #1
	ldr	r1, .L3390+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3383:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, [r4, #2404]
	ldr	r2, [r4, #3544]
	mov	r0, #1
	ldr	r1, .L3390+16
	ldr	r3, [r3, #4]
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3385:
	mov	r0, r4
	bl	HEVC_SimpleDPBProcess
	subs	r5, r0, #0
	bne	.L3387
.L3357:
	movw	r3, #11210
	mov	r2, r5
	ldr	r1, .L3390+20
	mov	r0, #14
	bl	dprint_vfmw
.L3355:
	cmn	r5, #1
	bne	.L3361
	b	.L3362
.L3386:
	mov	r0, r4
	bl	HEVC_DecOrderProcess
	subs	r5, r0, #0
	beq	.L3388
	ldr	r2, .L3390+4
	mov	r0, #0
	ldr	r1, .L3390+24
	bl	dprint_vfmw
	ldr	r3, [r4, #2404]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3355
.L3360:
	mov	r0, r4
	bl	HEVC_DispOrderProcess
	subs	r5, r0, #0
	beq	.L3361
	ldr	r2, .L3390+4
	mov	r0, #0
	ldr	r1, .L3390+28
	bl	dprint_vfmw
	b	.L3355
.L3382:
	ldr	r2, .L3390+4
	mov	r0, #1
	ldr	r1, .L3390+32
	bl	dprint_vfmw
	ldr	r3, .L3390+36
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3379
	mov	r3, r5
	mov	r2, r5
	mov	r1, #111
	ldr	r0, [r4, #252]
	blx	ip
.L3379:
	ldr	r2, [r4, #3544]
	b	.L3350
.L3384:
	mov	r0, r4
	bl	HEVC_DirectOutput
	ldr	r3, [r4, #3540]
	ldr	r2, [r4, #184]
	cmp	r3, r2
	addne	r3, r3, #532
	movne	r1, #0
	addne	r3, r4, r3, lsl #2
	strne	r1, [r3, #4]
	mov	r5, r0
	strne	r2, [r4, #3540]
	cmp	r0, #0
	bne	.L3389
.L3354:
	movw	r3, #11195
	mov	r2, r5
	ldr	r1, .L3390+20
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3355
.L3388:
	ldr	r3, [r4, #2404]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bls	.L3360
	b	.L3361
.L3389:
	ldr	r2, .L3390+4
	mov	r0, #0
	ldr	r1, .L3390+40
	bl	dprint_vfmw
	b	.L3354
.L3387:
	ldr	r2, .L3390+4
	mov	r0, #0
	ldr	r1, .L3390+44
	bl	dprint_vfmw
	b	.L3357
.L3391:
	.align	2
.L3390:
	.word	s_pstVfmwChan
	.word	.LANCHOR0+848
	.word	.LC450
	.word	.LC442
	.word	.LC444
	.word	.LC446
	.word	.LC448
	.word	.LC449
	.word	.LC443
	.word	g_event_report
	.word	.LC445
	.word	.LC447
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
	ldr	r3, .L3437
	mov	r5, r0
	mov	r6, r1
	sub	r0, fp, #732
	mov	r2, #696
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	add	r4, r5, #12672
	add	r4, r4, #48
	mov	r7, #0
.L3397:
	ldr	r2, [r4, #48]
	cmp	r2, #0
	bne	.L3393
	cmp	r4, #0
	beq	.L3394
	ldr	r3, [r5, #2588]
	cmp	r3, #0
	beq	.L3394
	ldr	r1, [r5, #2608]
	cmp	r4, r1
	beq	.L3393
	add	ip, r5, #2608
	b	.L3395
.L3396:
	ldr	lr, [ip, #4]!
	cmp	r4, lr
	beq	.L3393
.L3395:
	add	r2, r2, #1
	cmp	r2, r3
	bne	.L3396
.L3394:
	mov	r8, #712
	mov	r2, #632
	mla	r8, r8, r7, r5
	sub	r0, fp, #668
	mov	r9, #1
	mov	r3, #101
	str	r6, [fp, #-720]
	add	r1, r8, #12800
	str	r3, [fp, #-692]
	strb	r9, [fp, #-731]
	strb	r9, [fp, #-732]
	bl	memcpy
	add	r2, r8, #12672
	add	r3, r8, #12736
	cmp	r7, #19
	movw	r1, #12720
	mov	r7, #0
	strb	r9, [r2, #50]
	str	r4, [fp, #-672]
	str	r7, [r3, #36]
	str	r7, [fp, #-516]
	strb	r9, [r8, r1]
	bgt	.L3398
	ldr	r0, [r5, #2588]
	cmp	r0, #0
	beq	.L3400
	add	r1, r5, #2592
	mov	ip, r7
	add	r1, r1, #12
	mvn	r2, #-2147483648
	mov	r8, r1
.L3403:
	ldr	lr, [r8, #4]!
	add	ip, ip, #1
	ldr	r3, [lr, #8]
	rsb	r3, r6, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bge	.L3402
	ldrb	lr, [lr, #1]	@ zero_extendqisi2
	cmp	lr, #0
	movne	r2, r3
	movne	r7, #1
.L3402:
	cmp	ip, r0
	bne	.L3403
	cmp	r7, #0
	beq	.L3400
	mov	r4, #0
	b	.L3404
.L3405:
	add	r4, r4, #1
	cmp	r4, r0
	beq	.L3406
.L3404:
	ldr	ip, [r1, #4]!
	ldr	r3, [ip, #8]
	rsb	r3, r6, r3
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, r2
	bne	.L3405
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3405
	ldr	r1, [ip, #28]
	add	r4, r4, #652
	ldr	r0, [r5, #252]
	ldr	r9, [ip, #32]
	bl	FSP_GetLogicFs
	ldr	r2, [r5, r4, asl #2]
	mov	r3, r6
	ldr	r1, .L3437+4
	ldr	r2, [r2, #8]
	mov	r8, r0
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r8, #0
	beq	.L3406
	ldr	r0, [r8, #28]
	cmp	r0, #0
	beq	.L3435
	mov	r1, #0
	ldr	r0, [r5, #252]
	bl	FSP_NewLogicFs
	mov	r7, r0
	mov	r1, r0
	ldr	r0, [r5, #252]
	bl	FSP_GetLogicFs
	mvn	r2, r7
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r3, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L3409
	ldr	r1, [fp, #-672]
	sub	r2, fp, #732
	mov	r0, r5
	str	r7, [r1, #28]
	ldr	r1, [r8, #28]
	str	r1, [r3, #28]
	ldr	r1, [r8, #32]
	str	r1, [r3, #32]
	ldrsb	r3, [r8, #4]
	ldr	r1, [r5, #2588]
	str	r9, [fp, #-724]
	str	r3, [fp, #-696]
	bl	HEVC_InsertFrmInDPB
	subs	r4, r0, #0
	bne	.L3436
	ldr	r0, [r5, #252]
	mov	r1, r7
	mov	r2, r4
	bl	FSP_SetDisplay
	add	r3, r5, #4096
	mov	r0, r4
	ldr	r3, [r3, #136]
	add	r5, r5, r3, lsl #2
	ldr	r3, [r5, #228]
	cmn	r3, #-2147483647
	streq	r6, [r5, #228]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3393:
	add	r7, r7, #1
	add	r4, r4, #712
	cmp	r7, #20
	bne	.L3397
.L3398:
	ldr	r1, .L3437+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
.L3430:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3406:
	ldr	r1, .L3437+12
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3409:
	ldr	r3, [fp, #-672]
	mov	r0, r2
	ldr	r1, .L3437+16
	strb	r2, [r3]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3430
.L3436:
	ldr	r3, [fp, #-672]
	mov	r1, r7
	mov	r4, #0
	mov	r2, #1
	strb	r4, [r3]
	ldr	r0, [r5, #252]
	bl	FSP_ClearLogicFs
	mov	r0, r4
	ldr	r1, .L3437+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3430
.L3400:
	mov	r0, #0
	ldr	r1, .L3437+24
	strb	r0, [r4]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3430
.L3435:
	ldr	r1, .L3437+28
	bl	dprint_vfmw
	mov	r0, r5
	bl	HEVC_ClearDPB
	mvn	r0, #0
	b	.L3430
.L3438:
	.align	2
.L3437:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC454
	.word	.LC451
	.word	.LC452
	.word	.LC456
	.word	.LC457
	.word	.LC453
	.word	.LC455
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
	mov	r0, r4
	bl	HEVC_ApplyReferencePictureSet
	mov	r0, r4
	bl	HEVC_RemoveUnusedApcStore
	mov	r0, r4
	add	r5, r4, #4096
	bl	HEVC_RemoveUnUsedFrameStore
	b	.L3440
.L3443:
	bl	HEVC_CheckThatAllRefPicsAreAvailable.part.8
	ldr	r1, .L3449
	cmp	r0, #0
	mov	r0, #1
	bne	.L3445
	ldr	r2, [fp, #-24]
	bl	dprint_vfmw
	ldr	r3, [r4, #2404]
	mov	r0, r4
	ldr	r2, [r3, #4]
	cmp	r2, #0
	beq	.L3441
	ldr	r1, [fp, #-24]
	bl	HEVC_CreateLostPicture
	cmp	r0, #0
	bne	.L3448
.L3440:
	ldr	r3, [r5, #132]
	sub	r1, fp, #24
	mov	r0, r4
	sub	r3, r3, #19
	cmp	r3, #2
	bhi	.L3443
.L3445:
	mov	r0, r4
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	mov	r0, r4
	bl	HEVC_RecoverDPBProcess
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3441:
	ldr	ip, [fp, #-24]
	mov	r0, #1
	ldr	r3, [r5, #116]
	ldr	r1, .L3449+4
	str	ip, [sp]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3448:
	mov	r0, r4
	bl	HEVC_RemoveDummyFrame
	mvn	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3450:
	.align	2
.L3449:
	.word	.LC458
	.word	.LC459
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
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #8)
	sub	sp, sp, #8
	ldr	r3, [r0, #176]
	mov	r4, r0
	cmp	r3, #2
	bls	.L3510
	ldr	r3, [r0, #288]
	mov	r0, #1
	ldr	r2, [r4, #292]
	add	r3, r3, r0
	ldr	r1, [r4, #2404]
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #288]
	rsb	r3, r2, r3
	str	r3, [r1, #576]
	ldr	r5, [r4, #248]
	ldr	r2, [r4, #256]
	ubfx	r5, r5, #16, #3
	strb	r0, [r4, #3504]
	cmp	r2, r5
	beq	.L3456
	subs	r3, r5, #2
	sub	r1, r2, #2
	movne	r3, #1
	cmp	r1, r0
	movhi	r3, #0
	cmp	r3, #0
	beq	.L3456
	cmp	r5, #4
	cmpne	r5, r0
	bls	.L3511
.L3456:
	cmp	r5, #2
	str	r5, [r4, #256]
	beq	.L3458
	cmp	r5, #3
	bne	.L3506
.L3507:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
.L3505:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3506:
	ldr	r3, [r4, #236]
	cmp	r3, #0
	beq	.L3475
	cmp	r5, #4
	ldr	r3, [r4, #3520]
	beq	.L3512
.L3464:
	cmp	r3, #2
	bne	.L3466
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3513
.L3477:
	ldr	r2, [r4, #240]
	mov	r0, #2
	ldr	r1, .L3515
	sub	r2, r2, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L3514
	ldr	r0, [r4, #3532]
	add	r2, r4, #4096
	add	ip, r4, #8192
	clz	r1, r0
	mov	r1, r1, lsr #5
	str	r1, [r2, #3156]
	ldr	r1, [r4, #3536]
	str	r1, [r2, #3148]
	str	r3, [ip, #208]
	ldr	r3, [r4, #2404]
	ldr	r1, [r3, #592]
	strb	r1, [r2, #1816]
	ldr	r1, [r3, #596]
	strb	r1, [r2, #1817]
	ldr	r1, [r3, #600]
	strb	r1, [r2, #1819]
	ldr	r1, [r3, #604]
	strb	r1, [r2, #1820]
	ldr	r3, [r3, #644]
	str	r3, [r2, #3144]
	ldr	r3, [r4, #240]
	cmp	r3, #0
	beq	.L3471
	ldr	r1, [r4, #3548]
	add	r3, r4, #5888
	add	r3, r3, #24
	str	r3, [r4, #2412]
	add	r0, r0, #1
	mov	r3, #0
	str	r1, [ip, #2904]
	ldr	r1, [r4, #3552]
	str	r1, [ip, #2908]
	str	r0, [r4, #3532]
	str	r3, [ip, #2900]
	ldr	r1, [r4, #3520]
	cmp	r1, r3
	bne	.L3471
	ldr	r2, [ip, #212]
	cmp	r2, r3
	beq	.L3480
.L3474:
	ldr	r3, [r2]
	ldr	r0, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3474
.L3473:
	ldr	r3, .L3515+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3471
	sub	r2, fp, #20
	mov	r3, #4
	ldr	r0, [r4, #252]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	ip
.L3471:
	ldr	ip, [r4, #3560]
	mov	r0, #0
	ldr	r1, [r4, #3564]
	ldr	r3, [r4, #3556]
	str	ip, [r4, #3556]
	ldr	r2, [r1, #320]
	rsb	r3, ip, r3
	add	r2, r2, r3
	str	r2, [r1, #320]
	ldr	r2, [r4, #3808]
	add	r3, r2, r3
	str	r3, [r4, #3808]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3466:
	cmp	r3, #1
	streqb	r3, [r4, #6]
	b	.L3477
.L3458:
	ldr	r3, [r4, #3520]
	cmp	r3, #0
	bne	.L3462
	ldr	r3, [r4, #236]
	cmp	r3, #0
	bne	.L3477
.L3475:
	ldr	r3, .L3515+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3462
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
.L3462:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3505
.L3512:
	cmp	r3, #0
	moveq	r3, #2
	streqb	r3, [r4, #6]
	beq	.L3477
	b	.L3464
.L3513:
	ldr	r3, .L3515+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3477
	ldr	r3, [r4, #2404]
	ldr	r3, [r3, #24]
	sub	r2, r3, #4
	cmp	r3, #0
	cmpne	r2, #2
	bhi	.L3477
	mov	r3, #1
	ldr	r2, [r4, #3516]
	mov	r0, r3
	ldr	r1, .L3515+12
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r3, .L3515+4
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L3505
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #127
	blx	ip
	mvn	r0, #0
	b	.L3505
.L3511:
	mov	r3, r5
	ldr	r1, .L3515+16
	bl	dprint_vfmw
	str	r5, [r4, #256]
	b	.L3507
.L3514:
	ldr	r2, .L3515+4
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L3469
	mov	r2, r3
	mov	r1, #127
	ldr	r0, [r4, #252]
	blx	ip
.L3469:
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	ldr	r2, .L3515+20
	ldr	r1, .L3515+24
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3505
.L3510:
	bl	HEVC_ClearCurrPic
	ldr	r3, .L3515+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3453
	mov	r3, #0
	mov	r1, #127
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
.L3453:
	ldr	r3, [r4, #244]
	cmp	r3, #524288
	bls	.L3454
	ldr	r1, .L3515+28
	mov	r0, #0
	bl	dprint_vfmw
.L3454:
	ldr	r1, .L3515+32
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3505
.L3480:
	mov	r1, r2
	b	.L3473
.L3516:
	.align	2
.L3515:
	.word	.LC464
	.word	g_event_report
	.word	g_allow_B_before_P
	.word	.LC463
	.word	.LC462
	.word	.LANCHOR0+868
	.word	.LC465
	.word	.LC460
	.word	.LC461
	UNWIND(.fnend)
	.size	HEVC_DecVDM, .-HEVC_DecVDM
	.align	2
	.global	HEVC_VES_Splitter
	.type	HEVC_VES_Splitter, %function
HEVC_VES_Splitter:
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
	mov	r4, r0
	mov	r5, r1
	ldr	r0, [r0, #2356]
	mov	r1, #16
	mov	r10, r3
	mov	r9, r2
	mov	r6, #0
	str	r6, [fp, #-48]
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #24
	and	r8, r0, #31
	ldr	r0, [r4, #2356]
	bl	BsBack
	ldr	r3, [r4, #4000]
	cmp	r5, r6
	str	r6, [r4, #3988]
	str	r3, [fp, #-48]
	beq	.L3519
	cmp	r5, #1
	beq	.L3520
	mov	r2, r5
	ldr	r1, .L3674
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #1
.L3527:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3520:
	cmp	r9, #0
	bne	.L3540
	movw	r3, #31745
	cmp	r7, r3
	cmpeq	r10, #1
	moveq	r0, #1
	movne	r0, #0
	cmp	r8, #25
	movne	r8, #0
	andeq	r8, r0, #1
	cmp	r8, #0
	bne	.L3666
	movw	r2, #32257
	cmp	r7, r2
	beq	.L3667
	cmp	r7, r3
	bne	.L3668
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3539
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2376]
	mov	r0, r8
	b	.L3527
.L3519:
	cmp	r9, #0
	bne	.L3521
	movw	r1, #31745
	cmp	r8, #25
	cmpeq	r7, r1
	moveq	r5, #1
	movne	r5, #0
	bne	.L3522
	ldr	r7, .L3674+4
	ldr	ip, [r7]
	cmp	ip, #0
	beq	.L3523
	mov	r3, r9
	mov	r2, r9
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	ip
.L3523:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2376]
	subs	r5, r0, #0
	bne	.L3669
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r4, #3988]
	bls	.L3528
	ldr	r1, .L3674+8
	movw	r3, #2348
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3529
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2376]
.L3529:
	ldr	ip, [r7]
	cmp	ip, #0
	beq	.L3655
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L3655:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3521:
	bic	r7, r7, #512
	movw	r3, #31745
	cmp	r7, r3
	beq	.L3670
.L3562:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3540:
	movw	r1, #31745
	cmp	r8, #25
	cmpeq	r7, r1
	moveq	r8, #1
	movne	r8, #0
	bne	.L3548
	ldr	r7, .L3674+4
	ldr	ip, [r7]
	cmp	ip, #0
	beq	.L3549
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	ip
.L3549:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2376]
	subs	r5, r0, #0
	bne	.L3663
	ldr	r3, [r1, #44]
	sub	r2, r3, #1
	sub	r3, r3, #6
	cmp	r2, #1024
	str	r3, [r4, #3988]
	bls	.L3552
	ldr	r1, .L3674+8
	movw	r3, #2513
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3553
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2376]
.L3553:
	ldr	ip, [r7]
	cmp	ip, #0
	beq	.L3655
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L3527
.L3666:
	ldr	r7, .L3674+4
	ldr	ip, [r7]
	cmp	ip, #0
	beq	.L3542
	mov	r3, r9
	mov	r2, r9
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	ip
.L3542:
	mov	r0, r4
	bl	HEVC_DecVDM
	ldr	r1, [r4, #2376]
	subs	r5, r0, #0
	beq	.L3658
.L3663:
	cmp	r1, #0
	beq	.L3553
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
	b	.L3553
.L3522:
	movw	r3, #32257
	cmp	r7, r3
	bne	.L3562
.L3537:
	ldr	r1, [r4, #2376]
.L3658:
	cmp	r1, #0
	beq	.L3539
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2376]
	mov	r0, r5
	b	.L3527
.L3548:
	movw	r3, #32257
	cmp	r7, r3
	movne	r0, r5
	bne	.L3527
	ldr	r1, .L3674+12
	movw	r3, #2579
	ldr	r2, .L3674+16
	mov	r0, r8
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3655
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r8, [r4, #2376]
	mvn	r0, #0
	b	.L3527
.L3670:
	ldr	r1, .L3674+20
	movw	r3, #2434
	ldr	r2, .L3674+16
	mov	r0, r5
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3655
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2376]
	mvn	r0, #0
	b	.L3527
.L3539:
	mov	r0, #0
	b	.L3527
.L3669:
	cmp	r1, #0
	beq	.L3529
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
	b	.L3529
.L3668:
	mov	r1, #8
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	ldr	r0, [r4, #2356]
	ubfx	r5, r5, #1, #6
	bl	BsSkip
	cmp	r5, #49
	beq	.L3671
.L3547:
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3539
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2376]
	b	.L3527
.L3552:
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r4, #3992]
	add	r3, r3, r0
	ldr	r0, [r4, #252]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r6, r0, #0
	bne	.L3672
	ldr	r5, .L3674+24
	mov	r2, #5
	ldr	r1, .L3674+28
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2376]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r4, #3988]
	add	r1, r1, #6
	blx	r3
	ldr	r1, [r4, #2376]
	ldr	r0, [r4, #3988]
	add	r3, r0, #5
	str	r3, [r4, #3988]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L3555
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L3556
	add	r2, r0, #10
	ldr	r1, .L3674+8
	movw	r3, #2537
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3557
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2376]
.L3557:
	ldr	ip, [r7]
	cmp	ip, #0
	beq	.L3558
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
.L3558:
	ldr	r0, [r4, #252]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movne	r3, #2544
	beq	.L3655
.L3654:
	ldr	r2, .L3674+16
	mov	r0, #0
	ldr	r1, .L3674+32
	bl	dprint_vfmw
	b	.L3655
.L3528:
	ldr	r0, [r1, #72]
	sub	r2, fp, #48
	ldr	r3, [r1, #44]
	ldr	r1, [r4, #3992]
	add	r3, r3, r0
	ldr	r0, [r4, #252]
	sub	r3, r3, #1
	bl	MetadataMapToSec
	subs	r6, r0, #0
	bne	.L3673
	ldr	r5, .L3674+24
	mov	r2, #5
	ldr	r1, .L3674+28
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2376]
	ldr	r0, [fp, #-48]
	ldr	r3, [r5, #52]
	ldr	r1, [r2, #40]
	add	r0, r0, #5
	ldr	r2, [r4, #3988]
	add	r1, r1, #6
	blx	r3
	ldr	r1, [r4, #2376]
	ldr	r0, [r4, #3988]
	add	r3, r0, #5
	str	r3, [r4, #3988]
	ldr	r2, [r1, #72]
	cmp	r2, #0
	beq	.L3532
	add	ip, r3, r2
	cmp	ip, #1024
	bls	.L3533
	add	r2, r0, #10
	ldr	r1, .L3674+8
	movw	r3, #2372
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3534
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2376]
.L3534:
	ldr	ip, [r7]
	cmp	ip, #0
	beq	.L3535
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
.L3535:
	ldr	r0, [r4, #252]
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	cmp	r0, #0
	movwne	r3, #2379
	beq	.L3655
	b	.L3654
.L3533:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2376]
	ldr	r3, [r4, #3988]
	ldr	r2, [r2, #72]
	add	r3, r3, r2
	str	r3, [r4, #3988]
.L3532:
	ldr	r0, [r4, #252]
	ldr	r6, .L3674+36
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L3536
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #252]
	ldr	r3, [r5, #44]
	ldr	r1, [r4, #3988]
	ldr	r2, [r6, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #252]
.L3536:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	beq	.L3537
	movw	r3, #2407
	b	.L3654
.L3556:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #68]
	add	r0, r0, r3
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r2, [r4, #2376]
	ldr	r3, [r4, #3988]
	ldr	r2, [r2, #72]
	add	r3, r3, r2
	str	r3, [r4, #3988]
.L3555:
	ldr	r0, [r4, #252]
	ldr	r6, .L3674+36
	ldr	r3, [r6, r0, asl #2]
	cmp	r3, #0
	beq	.L3559
	ldr	r3, [r5, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r4, #252]
	ldr	r3, [r5, #44]
	ldr	r1, [r4, #3988]
	ldr	r2, [r6, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r5, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r4, #252]
.L3559:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r5, r0, #0
	movwne	r3, #2567
	beq	.L3537
	b	.L3654
.L3667:
	ldr	r0, [r4, #2356]
	mov	r1, #16
	bl	BsSkip
	mov	r0, r5
	b	.L3527
.L3671:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	bne	.L3547
	ldr	r3, [r4, #2376]
	ldr	r0, [r4, #2356]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	ldr	r0, [r4, #2356]
	mov	r1, #24
	bl	BsSkip
	mov	r0, #2
	b	.L3527
.L3672:
	mov	r0, r5
	movw	r3, #2525
	ldr	r2, .L3674+16
	ldr	r1, .L3674+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3527
.L3673:
	mov	r0, r5
	movw	r3, #2360
	ldr	r2, .L3674+16
	ldr	r1, .L3674+40
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3527
.L3675:
	.align	2
.L3674:
	.word	.LC471
	.word	g_event_report
	.word	.LC466
	.word	.LC470
	.word	.LANCHOR0+880
	.word	.LC469
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR4+208
	.word	.LC468
	.word	vfmw_save_metadata_file
	.word	.LC467
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
	ldr	r0, [r0, #2588]
	cmp	r0, #0
	beq	.L3688
	add	r2, r4, #2592
	mov	r5, #0
	add	r2, r2, #12
	mov	r3, r5
.L3679:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	cmp	r1, #0
	addeq	r5, r5, #1
	cmp	r3, r0
	bne	.L3679
.L3680:
	mov	r0, r4
	bl	HEVC_RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L3680
	cmp	r5, #0
	ble	.L3682
.L3686:
	ldr	r1, [r4, #2588]
	cmp	r1, #0
	beq	.L3683
	ldr	r3, [r4, #2608]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3690
	add	r2, r4, #2608
	mov	r3, #0
	b	.L3687
.L3684:
	ldr	ip, [r2, #4]!
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	cmp	ip, #0
	beq	.L3690
.L3687:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3684
.L3683:
	mov	r0, r4
	bl	HEVC_OutputOneFrmFromDPB
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	subs	r5, r5, #1
	bne	.L3686
.L3682:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3690:
	mov	r1, r3
	b	.L3683
.L3688:
	mov	r5, r0
	b	.L3680
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
	ldr	r3, [r0, #2376]
	add	r5, r0, #4096
	ldr	r2, .L3779
	mov	ip, #0
	mov	r4, r0
	ldr	r1, [r3, #16]
	str	r1, [r5, #132]
	ldr	r1, [r3, #28]
	str	r1, [r5, #128]
	ldr	r6, [r3, #24]
	str	r6, [r5, #136]
	ldr	r1, [r0, #252]
	strb	ip, [r0, #3]
	ldr	r2, [r2, r1, asl #2]
	ldrsb	r1, [r2, #44]
	cmp	r1, #1
	beq	.L3765
.L3701:
	ldr	r3, [r5, #256]
	cmp	r3, #1
	beq	.L3766
.L3702:
	ldr	r2, [r4, #204]
	ldr	r3, [r4, #152]
	cmp	r2, r3
	bcs	.L3767
	ldrb	r3, [r4, #3505]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3768
	mov	r0, r4
	bl	HEVC_PicTypeStatistic
	mov	r0, r4
	bl	HEVC_CalcStreamBits
	ldr	r3, [r5, #256]
	cmp	r3, #2
	beq	.L3719
	ldr	r3, [r4, #2332]
	cmp	r3, #0
	bne	.L3720
	ldrb	r3, [r5, #105]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3769
.L3720:
	mov	r0, r4
	bl	HEVC_WriteSliceMsg
	cmp	r0, #0
	bne	.L3770
.L3723:
	ldr	r3, [r4, #2332]
	cmp	r3, #0
	beq	.L3771
.L3725:
	ldr	r2, [r4, #2888]
	mov	r0, #0
	ldr	r3, [r4, #2892]
	str	r2, [r4, #3548]
	str	r3, [r4, #3552]
.L3707:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3771:
	ldr	r3, [r5, #140]
	mov	r2, #1
	str	r3, [r4, #296]
	ldr	r3, [r5, #116]
	str	r2, [r4, #172]
	str	r3, [r4, #260]
	b	.L3725
.L3766:
	ldr	r3, [r4, #2332]
	cmp	r3, #0
	bne	.L3704
	ldr	r3, [r5, #132]
	clz	r7, r6
	sub	r3, r3, #16
	mov	r7, r7, lsr #5
	cmp	r3, #4
	cmpls	r6, #0
	bne	.L3772
.L3705:
	mov	r0, r4
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L3773
.L3706:
	add	r3, r4, r6
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	andeq	r3, r7, #1
	cmp	r3, #0
	beq	.L3708
	ldr	r3, [r4, #2588]
	cmp	r3, #0
	bne	.L3774
.L3708:
	ldr	r0, [r4, #2404]
	ldr	r1, [r0, #12]
	cmp	r1, #0
	bne	.L3709
	ldr	r3, [r4, #2340]
	cmp	r3, #1
	beq	.L3775
	ldr	r3, [r5, #128]
	ldr	r2, [r4, #2388]
	add	r3, r3, #90
	ldr	r1, [r2, r3, asl #2]
.L3712:
	cmp	r7, #0
	beq	.L3709
	add	r6, r4, r6, lsl #2
	ldr	r3, [r6, #212]
	cmp	r3, #-2147483647
	beq	.L3709
	ldr	r2, [r5, #116]
	add	r1, r1, r3
	cmp	r2, r1
	bcs	.L3709
	ldr	r1, [r5, #132]
	cmp	r1, #21
	bne	.L3709
	ldr	r1, .L3779+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_CRAOutputFrame
	mov	r3, #-2147483647
	str	r3, [r6, #212]
	ldr	r0, [r4, #2404]
.L3709:
	ldr	r3, [r0, #8]
	cmp	r3, #2
	beq	.L3704
	ldr	r3, [r0, #24]
	mov	r0, r4
	cmp	r3, #2
	beq	.L3776
	bl	HEVC_RefPicProcess
	cmp	r0, #0
	bne	.L3726
.L3704:
	mov	r0, r4
	bl	HEVC_InitPic
	cmn	r0, #2
	beq	.L3707
	cmp	r0, #0
	bne	.L3777
	ldr	r3, [r4, #240]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r4, #240]
	bl	HEVC_SetScalingList
	mov	r0, r4
	bl	HEVC_WritePicMsg
	cmp	r0, #0
	beq	.L3702
	ldr	r1, .L3779+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3765:
	ldr	r1, [r2, #156]
	cmp	r1, ip
	bne	.L3701
	ldr	r2, [r2, #160]
	cmp	r2, #1
	bne	.L3701
	ldr	r1, [r3, #16]
	bl	HEVC_Get_Last_IDR_Frame_Info
	b	.L3701
.L3719:
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3723
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
	b	.L3723
.L3769:
	mov	r0, r4
	bl	HEVC_DecList
	cmp	r0, #0
	bne	.L3778
	mov	r0, r4
	bl	HEVC_IsRefListWrong
	cmp	r0, #0
	beq	.L3720
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r1, .L3779+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3772:
	mov	r0, r4
	bl	HEVC_IsPVRFlushPic
	cmp	r0, #0
	beq	.L3706
	b	.L3705
.L3774:
	mov	r0, r4
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L3708
	ldr	r2, .L3779+16
	mov	r0, #1
	ldr	r1, .L3779+20
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3726:
	mvn	r0, #0
	b	.L3707
.L3776:
	bl	HEVC_UpdateReflist
	mov	r0, r4
	bl	HEVC_UpdateLTReflist
	b	.L3704
.L3768:
	ldr	r1, .L3779+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3775:
	ldr	ip, [r4, #2388]
	add	r3, ip, #356
	add	ip, ip, #388
.L3711:
	ldr	r2, [r3, #4]!
	cmp	r1, r2
	movcc	r1, r2
	cmp	r3, ip
	bne	.L3711
	b	.L3712
.L3767:
	ldr	r1, .L3779+28
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #204]
	ldr	r2, [r4, #152]
	cmp	r3, r2
	bcc	.L3717
	ldr	r1, .L3779+32
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L3717
	str	r3, [fp, #-36]
	mov	r1, #108
	str	r2, [fp, #-32]
	mov	r3, #8
	sub	r2, fp, #36
	ldr	r0, [r4, #252]
	blx	ip
.L3717:
	ldr	r1, .L3779+36
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	b	.L3707
.L3770:
	ldr	r1, .L3779+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3777:
	ldr	r1, .L3779+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3778:
	mov	r2, r0
	ldr	r1, .L3779+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3773:
	ldr	r2, .L3779+16
	mov	r0, #1
	ldr	r1, .L3779+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3707
.L3780:
	.align	2
.L3779:
	.word	s_pstVfmwChan
	.word	.LC474
	.word	.LC476
	.word	.LC481
	.word	.LANCHOR0+900
	.word	.LC473
	.word	.LC479
	.word	.LC477
	.word	g_event_report
	.word	.LC478
	.word	.LC482
	.word	.LC475
	.word	.LC480
	.word	.LC472
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
	ldr	r0, [r0, #2376]
	ldr	r3, [r0, #8]
	cmp	r3, #0
	ldrne	r1, [r4, #244]
	movne	r2, r0
	movne	r3, #0
	beq	.L3786
.L3785:
	ldr	ip, [r2, #44]
	add	r3, r3, #1
	add	r2, r2, #28
	add	r1, r1, ip
	str	r1, [r4, #244]
	ldr	ip, [r0, #8]
	cmp	ip, r3
	bhi	.L3785
.L3786:
	mov	r3, #0
	strb	r3, [r0]
	ldr	r3, [r4, #2376]
	ldr	r2, [r3, #16]
	sub	r2, r2, #36
	cmp	r2, #1
	bls	.L3925
.L3784:
	ldr	r2, [r3, #4]
	add	r2, r2, #16
	str	r2, [r3, #4]
	ldr	r1, [r4, #2376]
	ldr	r2, [r1, #16]
	cmp	r2, #49
	ldrls	pc, [pc, r2, asl #2]
	b	.L3787
.L3789:
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3788
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3790
	.word	.L3791
	.word	.L3792
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3793
	.word	.L3793
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3787
	.word	.L3794
	.word	.L3795
.L3925:
	mov	r2, #1
	strb	r2, [r4, #3]
	b	.L3784
.L3795:
	mov	r0, r4
	bl	HEVC_IsEosNal
	cmp	r0, #1
	beq	.L3926
.L3811:
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3914
.L3916:
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2376]
.L3913:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3788:
	mov	r0, r4
	bl	HEVC_DecSlice
	cmn	r0, #2
	beq	.L3913
	cmp	r0, #0
	beq	.L3914
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3923
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L3923:
	ldr	r3, .L3928
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3915
.L3917:
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L3915:
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3790:
	mov	r0, r4
	bl	HEVC_DecVPS
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3796
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L3796:
	cmp	r5, #0
	bne	.L3927
.L3914:
	mov	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3791:
	mov	r0, r4
	bl	HEVC_DecSPS
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3801
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L3801:
	cmp	r5, #0
	beq	.L3914
	ldr	r6, .L3928
	mov	r0, #1
	ldr	r1, .L3928+4
	bl	dprint_vfmw
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L3919
	b	.L3915
.L3792:
	mov	r0, r4
	bl	HEVC_DecPPS
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3803
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L3803:
	cmp	r5, #0
	beq	.L3914
	ldr	r6, .L3928
	mov	r0, #1
	ldr	r1, .L3928+8
	bl	dprint_vfmw
	ldr	ip, [r6]
	cmp	ip, #0
	beq	.L3915
.L3919:
	sub	r2, fp, #28
	mvn	r5, #0
	mov	r3, #4
	mov	r1, #100
	str	r5, [r2, #-4]!
	ldr	r0, [r4, #252]
	blx	ip
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L3917
	b	.L3915
.L3793:
	mov	r0, r4
	bl	HEVC_DecSEI
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	mov	r5, r0
	beq	.L3804
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L3804:
	cmp	r5, #0
	beq	.L3914
	ldr	r1, .L3928+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3923
.L3794:
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3809
	cmp	r1, #0
	beq	.L3808
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L3808:
	ldrb	r3, [r4, #3505]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3914
.L3809:
	add	r5, r4, #2544
	mov	r1, #32
	add	r5, r5, #8
	mov	r6, #0
	strb	r6, [r4, #8]
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
	bne	.L3914
	ldr	r5, .L3928
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L3810
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r4, #252]
	blx	ip
.L3810:
	ldrb	r3, [r4, #3505]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3914
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L3914
.L3813:
	ldr	ip, [r5]
	cmp	ip, #0
	bne	.L3917
	b	.L3915
.L3787:
	ldr	r1, .L3928+16
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	ldr	r3, [r1, #16]
	cmp	r3, #63
	bhi	.L3814
	cmp	r1, #0
	bne	.L3916
	b	.L3914
.L3814:
	ldr	r5, .L3928
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L3815
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3816
.L3817:
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L3816:
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L3914
	mov	r3, #0
	ldr	r0, [r4, #252]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	b	.L3914
.L3815:
	cmp	r1, #0
	bne	.L3817
	b	.L3914
.L3927:
	ldr	r6, .L3928
	mov	r0, #1
	ldr	r1, .L3928+20
	bl	dprint_vfmw
	ldr	ip, [r6]
	cmp	ip, #0
	bne	.L3919
	b	.L3915
.L3926:
	ldr	r5, .L3928
	strb	r0, [r4, #9]
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L3812
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
.L3812:
	ldrb	r3, [r4, #3505]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3811
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	beq	.L3811
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L3813
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
	b	.L3813
.L3929:
	.align	2
.L3928:
	.word	g_event_report
	.word	.LC484
	.word	.LC485
	.word	.LC486
	.word	.LC487
	.word	.LC483
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
	ldr	r0, [r0, #252]
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
	ldr	ip, .L3952
	mov	r4, r0
	mov	r3, #0
	mov	r8, r1
	add	r0, r0, #4160
	str	r3, [r2]
	mov	r1, r3
	str	r3, [r8]
	mov	r7, r2
	ldr	r3, [ip, #48]
	movw	r2, #1356
	add	r0, r0, #40
	add	r5, r4, #4096
	blx	r3
	ldr	r3, [r4, #2376]
	mov	r0, r4
	ldr	r2, [r3, #16]
	str	r2, [r5, #132]
	ldr	r2, [r3, #28]
	str	r2, [r5, #128]
	ldr	r3, [r3, #24]
	str	r3, [r5, #136]
	bl	HEVC_DecSliceSegmentHeader
	cmp	r0, #0
	bne	.L3948
	ldr	r2, [r5, #140]
	mov	r0, #1888
	ldr	r3, [r4, #2368]
	movw	r6, #12660
	ldr	r9, [r4, #2332]
	ldr	r1, [r4, #2364]
	mla	r3, r0, r2, r3
	cmp	r9, #1
	ldr	r3, [r3, #32]
	mla	r6, r6, r3, r1
	beq	.L3949
	ldr	r3, [r5, #256]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r8]
	ldr	r2, [r4, #2388]
	ldr	ip, [r4, #2404]
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
	beq	.L3950
.L3937:
	cmp	r3, r1
	moveq	r1, r0
	orrne	r1, r0, #1
	cmp	lr, r2
	moveq	r3, r1
	orrne	r3, r1, #1
	cmp	r3, #0
	beq	.L3940
	mov	r0, #0
	mov	r3, #1
	str	r3, [r7]
.L3933:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3949:
	ldr	r0, [r4, #2356]
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
	bne	.L3935
.L3940:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3948:
	ldr	r1, .L3952+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3952+8
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L3933
	sub	r2, fp, #36
	ldr	r0, [r4, #252]
	mov	r3, #4
	mvn	r4, #0
	mov	r1, #100
	str	r4, [r2, #-4]!
	blx	ip
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L3950:
	ldr	r5, [r6, #96]
	ldr	r6, [r6, #88]
	cmp	r5, r6
	movcc	r5, r6
	str	r5, [ip, #900]
	ldr	r5, [r4, #2388]
	ldr	r6, [r4, #2404]
	ldr	ip, [r5, #96]
	ldr	r4, [r5, #88]
	ldr	r5, [r6, #900]
	cmp	ip, r4
	movcc	ip, r4
	cmp	ip, #8
	movls	r4, #0
	movhi	r4, #1
	cmp	r5, #8
	movne	r4, #0
	cmp	r4, #0
	beq	.L3951
.L3938:
	mov	ip, #1
	str	ip, [r6, #904]
	str	ip, [r7]
	b	.L3937
.L3951:
	sub	ip, ip, #8
	cmp	r5, #8
	clz	ip, ip
	mov	ip, ip, lsr #5
	movle	ip, #0
	cmp	ip, #0
	beq	.L3937
	b	.L3938
.L3935:
	mov	r3, r0
	mov	r2, r5
	mov	r0, r9
	ldr	r1, .L3952+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3933
.L3953:
	.align	2
.L3952:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC488
	.word	g_event_report
	.word	.LC489
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
	bne	.L3956
	ldrb	r3, [r4, #3505]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3958
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3956:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3958:
	ldr	r2, .L3959
	ldr	r1, .L3959+4
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3960:
	.align	2
.L3959:
	.word	.LANCHOR0+916
	.word	.LC490
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
	ldr	r2, [r0, #212]
	cmp	r2, #0
	beq	.L3964
	mov	r0, #0
.L3963:
	ldr	r3, [r2]
	ldr	r1, [r2, #4]
	ldr	r2, [r2, #1356]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L3963
	ldmfd	sp, {fp, sp, pc}
.L3964:
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
	ldr	r3, [r0, #2328]
	mov	r5, #0
	mov	r4, r0
	str	r5, [r0, #2332]
	cmp	r3, #2
	str	r5, [r0, #2340]
	beq	.L3995
	cmp	r3, #1
	beq	.L3996
.L3980:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3996:
	ldr	r3, [r0, #2336]
	cmp	r3, #1
	bne	.L3980
	str	r5, [r0, #2336]
.L3994:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3995:
	ldr	r3, [r0, #2324]
	cmp	r3, r5
	beq	.L3994
	ldr	r3, [r0, #2336]
	cmp	r3, #1
	beq	.L3980
	ldr	r0, [r0, #252]
	bl	VCTRL_CheckFreshSeg
	cmp	r0, #0
	beq	.L3994
	ldr	r0, [r4, #252]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L3994
	ldr	r3, [r4, #2376]
	ldr	r0, [r4, #2356]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2356]
	bl	BsSkip
	ldr	r0, [r4, #2356]
	bl	BsResidBits
	cmp	r0, #15
	ble	.L3994
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsSkip
	mov	r1, #6
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #9
	mov	r6, r0
	ldr	r0, [r4, #2356]
	bl	BsSkip
	mov	r0, r6
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	mov	r7, r0
	beq	.L3997
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L3994
	sub	r3, r6, #48
	sub	r6, r6, #32
	cmp	r6, #2
	cmphi	r3, #1
	bhi	.L3994
.L3976:
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	bne	.L3994
	mov	r3, #1
	mvn	r0, #0
	str	r3, [r4, #2340]
	strb	r3, [r4, #3504]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3997:
	ldr	r0, [r4, #2356]
	bl	BsResidBits
	cmp	r0, #0
	movle	r0, r5
	ble	.L3973
	mov	r1, r7
	ldr	r0, [r4, #2356]
	bl	BsGet
.L3973:
	ldr	r3, [r4, #204]
	cmp	r3, #0
	beq	.L3974
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
	bne	.L3976
.L3974:
	ldrb	r2, [r4, #3505]	@ zero_extendqisi2
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #2336]
	mov	r3, #1
	str	r3, [r4, #2332]
	str	r2, [r4, #2344]
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
	beq	.L4001
	ldr	r2, [r0, #2412]
	cmp	r2, #0
	beq	.L4006
.L4001:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4006:
	add	r2, r0, #4096
	ldr	r2, [r2, #1840]
	cmp	r2, #1
	bls	.L4001
	ldr	r2, [r0, #2348]
	cmp	r3, r2
	beq	.L4001
	ldr	r3, [r0, #2332]
	cmp	r3, #1
	beq	.L4007
	cmp	r3, #0
	bne	.L4001
	ldr	r0, [r0, #252]
	bl	VCTRL_CheckFreshRaw
	cmp	r0, #0
	beq	.L4001
	ldr	r0, [r4, #252]
	bl	VCTRL_CheckFreshSeg
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L4007:
	ldr	r0, [r0, #2376]
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
	ldr	r5, [r0, #2336]
	mov	r4, r0
	cmp	r5, #1
	beq	.L4021
.L4009:
	mov	r0, r4
	bl	HEVCDEC_IsNeedSedOnly
	cmp	r0, #1
	beq	.L4022
	ldr	r3, [r4, #2332]
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r4, #2376]
	ldr	ip, [r4, #2344]
	ldr	r0, [r4, #204]
	cmp	r1, #0
	ldr	r2, [r4, #176]
	ldr	r3, [r4, #236]
	sub	r0, r0, #1
	sub	r2, r2, #1
	str	r0, [r4, #204]
	sub	r3, r3, #1
	str	r2, [r4, #176]
	strb	ip, [r4, #3505]
	str	r3, [r4, #236]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4021:
	ldr	r3, [r0, #204]
	cmp	r3, #0
	beq	.L4009
	ldr	r6, [r0, #2412]
	cmp	r6, #0
	bne	.L4009
	bl	HEVC_DecVDM
	cmp	r0, #0
	streq	r5, [r4, #2340]
	streqb	r5, [r4, #3504]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r6, [r4, #2376]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4022:
	add	r2, r4, #8192
	add	lr, r4, #4096
	add	r3, r4, #5888
	mov	ip, #0
	str	r0, [r2, #2900]
	add	r3, r3, #24
	ldr	r1, [r4, #204]
	str	r1, [r4, #2348]
	str	r1, [r2, #208]
	ldr	r2, [r4, #2404]
	ldr	r2, [r2, #644]
	str	r2, [lr, #3144]
	str	r3, [r4, #2412]
	str	ip, [r4, #2336]
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
	ldr	r6, .L4035
	mov	r3, #180
	ldr	r2, [r0, #2412]
	mov	r4, r0
	ldr	lr, [r0, #252]
	mov	r0, #22
	mla	r1, r3, r1, r6
	ldr	r3, [r2, #24]
	ldr	r2, [r2, #20]
	ldr	ip, .L4035+4
	add	r6, r1, #16
	ldr	r1, .L4035+8
	mla	r5, r2, r3, r3
	ldr	r3, [r6, #4]
	ldr	r7, [ip, lr, asl #2]
	add	r5, r5, r2
	mov	r2, r5
	bl	dprint_vfmw
	ldr	r3, [r6, #4]
	cmp	r3, r5
	ldr	r3, [r4, #2332]
	beq	.L4033
	cmp	r3, #1
	beq	.L4034
.L4028:
	mov	r3, #0
	str	r3, [r4, #2412]
.L4026:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4033:
	cmp	r3, #1
	beq	.L4025
	mov	r0, r4
	bl	HEVC_DecVDM
	cmp	r0, #0
	moveq	r3, #1
	streq	r3, [r4, #2340]
	streqb	r3, [r4, #3504]
	b	.L4026
.L4034:
	ldr	r1, [r4, #2376]
	mov	r5, #0
	ldr	ip, [r4, #2344]
	ldr	r0, [r4, #204]
	cmp	r1, r5
	ldr	r2, [r4, #176]
	ldr	r3, [r4, #236]
	sub	r0, r0, #1
	sub	r2, r2, #1
	str	r0, [r4, #204]
	sub	r3, r3, #1
	str	r2, [r4, #176]
	strb	ip, [r4, #3505]
	str	r3, [r4, #236]
	str	r5, [r4, #2336]
	beq	.L4028
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	str	r5, [r4, #2376]
	b	.L4028
.L4025:
	ldr	lr, [r4, #2344]
	mov	ip, #0
	ldr	r0, [r4, #204]
	ldr	r1, [r4, #176]
	ldr	r2, [r4, #236]
	sub	r0, r0, #1
	str	r3, [r4, #2336]
	sub	r1, r1, #1
	str	r0, [r4, #204]
	sub	r2, r2, #1
	str	r1, [r4, #176]
	mov	r0, #0
	str	r2, [r4, #236]
	strb	lr, [r4, #3505]
	strb	r3, [r7, #681]
	strb	r3, [r4, #7]
	str	ip, [r4, #2412]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4036:
	.align	2
.L4035:
	.word	g_BackUp
	.word	s_pstVfmwChan
	.word	.LC491
	UNWIND(.fnend)
	.size	HEVCDEC_VDMProcSedOnly, .-HEVCDEC_VDMProcSedOnly
	.align	2
	.global	HEVCDEC_Init
	.type	HEVCDEC_Init, %function
HEVCDEC_Init:
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
	add	r7, r0, #4096
	ldr	r6, .L4051
	mov	r4, r0
	ldr	r8, [r7, #1808]
	mov	r5, r1
	movw	r2, #26960
	mov	r1, #0
	ldr	r3, [r6, #48]
	blx	r3
	str	r8, [r7, #1808]
	mov	r3, #0
	str	r5, [r4, #2404]
	str	r3, [r4, #2412]
	ldr	r3, [r5, #28]
	cmp	r3, #25
	beq	.L4046
	mov	r3, #17
	mov	r1, #65
	str	r3, [r4, #156]
	mov	r2, #200
	str	r3, [r4, #160]
	mov	r3, #210
	str	r1, [r4, #164]
	str	r2, [r4, #152]
	str	r3, [r4, #168]
.L4039:
	ldr	r0, [r5, #584]
	bl	MEM_Phy2Vir
	subs	ip, r0, #0
	beq	.L4047
	ldr	r2, [r4, #156]
	movw	r9, #12660
	ldr	r1, [r4, #2404]
	mov	r8, #1888
	ldr	r3, [r4, #160]
	mov	r7, #1360
	mov	r10, r2, asl #7
	ldr	lr, [r1, #580]
	add	r10, r10, r2, lsl #2
	ldr	r2, [r4, #152]
	add	r0, r10, lr
	add	lr, ip, lr
	add	r1, ip, r0
	str	r1, [r4, #2364]
	mla	r0, r9, r3, r0
	ldr	r3, [r4, #168]
	mul	r2, r7, r2
	add	r3, r3, #1
	str	lr, [r4, #2360]
	mov	r1, r3, asl #7
	sub	r3, r1, r3, asl #5
	add	r1, ip, r0
	str	r1, [fp, #-48]
	ldr	r1, [r4, #164]
	mla	r0, r8, r1, r0
	ldr	r1, [fp, #-48]
	str	r1, [r4, #2368]
	add	r1, r0, r2
	add	r3, r1, r3
	add	r1, ip, r1
	str	r1, [r4, #2400]
	add	r0, ip, r0
	ldr	r1, [r4, #168]
	add	ip, ip, r3
	str	r0, [r4, #2408]
	str	ip, [r4, #2396]
	add	r3, r3, r1, lsl #2
	ldr	r1, [r4, #2404]
	ldr	r1, [r1, #588]
	cmp	r3, r1
	bhi	.L4048
	ldr	r5, [r5, #616]
	cmp	r5, #0
	beq	.L4049
.L4043:
	ldr	r3, [r6, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r4, #168]
	ldr	ip, [r6, #48]
	mov	r1, #0
	add	r3, r3, #1
	ldr	r0, [r4, #2400]
	mov	r2, r3, asl #7
	sub	r2, r2, r3, asl #5
	blx	ip
	ldr	r2, [r4, #168]
	ldr	r3, [r6, #48]
	mov	r1, #0
	ldr	r0, [r4, #2396]
	mov	r2, r2, asl #2
	blx	r3
	ldr	r1, [r4, #160]
	ldr	ip, [r4, #156]
	movw	r3, #12660
	ldr	r0, [r4, #164]
	mov	r2, #1888
	mul	r3, r3, r1
	mov	r1, ip, asl #7
	mul	r2, r2, r0
	add	r1, r1, ip, lsl #2
	ldr	r0, [r4, #2360]
	sub	r1, r1, #132
	ldr	lr, [r4, #2364]
	sub	r3, r3, #12608
	add	r1, r0, r1
	ldr	r0, [r4, #2368]
	sub	r3, r3, #52
	sub	r2, r2, #1888
	str	r1, [r4, #2384]
	add	r3, lr, r3
	add	r2, r0, r2
	str	r3, [r4, #2388]
	str	r2, [r4, #2392]
	mov	r0, r4
	str	ip, [r1, #4]
	ldr	r3, [r4, #2392]
	ldr	r2, [r4, #160]
	str	r2, [r3, #28]
	ldr	r3, [r4, #2388]
	ldr	r2, [r4, #164]
	str	r2, [r3, #56]
	bl	HEVC_InitScalingOrderTable
	mov	r0, r4
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #252]
	beq	.L4050
	mov	r3, #-2147483647
	mov	r0, r4
	str	r3, [r4, #212]
	bl	HEVC_InitDecPara
	add	r2, r4, #8192
	mov	r3, #0
	movw	ip, #9999
	str	r3, [r2, #2968]
	mov	r1, #1
	ldr	lr, [r4, #164]
	mov	r0, r3
	ldr	r2, [r4, #2404]
	str	r3, [r4, #2352]
	str	lr, [r4, #296]
	str	ip, [r4, #260]
	strb	r1, [r4]
	ldr	r3, [r2, #632]
	str	r3, [r4, #2324]
.L4045:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4049:
	mov	r0, lr
	mov	r2, r10
	ldr	r3, [r6, #48]
	mov	r1, r5
	blx	r3
	ldr	r2, [r4, #160]
	ldr	r3, [r6, #48]
	mov	r1, r5
	ldr	r0, [r4, #2364]
	mul	r2, r9, r2
	blx	r3
	ldr	r2, [r4, #164]
	mov	r1, r5
	ldr	r3, [r6, #48]
	ldr	r0, [r4, #2368]
	mul	r2, r8, r2
	blx	r3
	ldr	r2, [r4, #152]
	ldr	r0, [r4, #2408]
	mul	r2, r7, r2
	b	.L4043
.L4046:
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
	b	.L4039
.L4048:
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L4051+4
	ldr	r1, .L4051+8
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4045
.L4050:
	ldr	r2, .L4051+4
	mov	r0, #0
	ldr	r1, .L4051+12
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4045
.L4047:
	ldr	r2, .L4051+4
	ldr	r1, .L4051+16
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L4045
.L4052:
	.align	2
.L4051:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+936
	.word	.LC493
	.word	.LC494
	.word	.LC492
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
	beq	.L4056
	ldrb	r3, [r0, #3505]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L4056
	add	r2, r0, #12672
	add	r0, r0, #26880
	add	r2, r2, #48
	add	r0, r0, #80
.L4062:
	ldr	r3, [r2, #48]
	cmp	r3, #0
	bne	.L4057
	cmp	r2, #0
	beq	.L4058
	ldr	lr, [r4, #2588]
	cmp	lr, #0
	beq	.L4058
	ldr	r1, [r4, #2608]
	cmp	r1, r2
	beq	.L4057
	add	r1, r4, #2608
	b	.L4059
.L4060:
	ldr	ip, [r1, #4]!
	cmp	ip, r2
	beq	.L4057
.L4059:
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L4060
.L4058:
	ldr	r0, [r4, #252]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4056
	cmn	r0, #1
	beq	.L4081
.L4080:
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4056:
	mov	r0, #1
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4057:
	add	r2, r2, #712
	cmp	r2, r0
	bne	.L4062
	add	r0, r4, #5504
	sub	r2, fp, #24
	sub	r1, fp, #28
	add	r0, r0, #56
	bl	GetQueueImgNum
	mov	r0, r4
	bl	HEVC_PrintFrameStoreState
	ldr	r1, .L4082
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_PrintDPBState
	ldr	r2, [r4, #180]
	ldr	r0, [r4, #2588]
	ldr	r3, [fp, #-28]
	sub	r2, r2, #2
	ldr	r1, [fp, #-24]
	rsb	r2, r0, r2
	add	r0, r3, r1
	cmp	r0, r2
	bge	.L4080
	str	r1, [sp]
	mov	r0, #0
	ldr	r2, .L4082+4
	ldr	r1, .L4082+8
	bl	dprint_vfmw
	mov	r0, r4
	mov	r1, #1
	bl	HEVC_ClearAll
	mov	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L4081:
	ldr	r1, .L4082+12
	mov	r0, #1
	bl	dprint_vfmw
	add	r1, r4, #5504
	add	r1, r1, #56
	ldr	r0, [r4, #252]
	bl	FSP_ClearNotInVoQueue
	b	.L4080
.L4083:
	.align	2
.L4082:
	.word	.LC496
	.word	.LANCHOR0+952
	.word	.LC497
	.word	.LC495
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
	beq	.L4159
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L4160
	ldr	ip, [r4, #2404]
	ldrb	lr, [r4, #7]	@ zero_extendqisi2
	ldr	r3, [ip, #8]
	cmp	lr, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r4, #248]
	beq	.L4088
	ldr	r3, [ip, #840]
	cmp	r3, #1
	beq	.L4161
.L4089:
	mov	r0, r4
	bl	HEVC_ReceivePacket
	ldr	r3, [r4, #2376]
	str	r3, [r4, #2380]
	mov	r6, r0
.L4090:
	cmp	r6, #0
	mov	r3, #0
	strb	r3, [r4, #7]
	beq	.L4091
.L4116:
	mov	r5, #0
.L4157:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4161:
	ldr	r3, [ip, #888]
	cmp	r3, #1
	bne	.L4089
	ldr	r3, [r4, #320]
	cmp	r3, #1
	bne	.L4089
	ldr	r3, [r4, #2380]
	mov	r5, r0
	str	r0, [r4, #320]
	strb	r0, [r4, #7]
	str	r3, [r4, #2376]
	b	.L4157
.L4091:
	mov	r0, r4
	bl	HEVCDEC_CheckSedOnly
	subs	r5, r0, #0
	beq	.L4092
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L4158
	ldr	r0, [r4, #252]
	mvn	r5, #0
	bl	HEVC_ReleaseNAL
	mov	r0, r5
	str	r6, [r4, #2376]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4088:
	ldr	r3, [r4, #2376]
	cmp	r3, #0
	movne	r6, #0
	mvneq	r6, #0
	cmp	r3, #0
	bne	.L4090
	ldr	r1, .L4169
	mov	r5, r6
	bl	dprint_vfmw
	b	.L4157
.L4165:
	ldr	r1, .L4169+4
	mov	r0, #22
	bl	dprint_vfmw
.L4158:
	mvn	r5, #0
	b	.L4157
.L4092:
	ldr	r3, [r4, #2376]
	ldr	r8, .L4169+8
	str	r6, [r3, #4]
	ldr	r3, [r4, #2376]
	ldr	r0, [r4, #2356]
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2356]
	bl	BsSkip
	ldr	r3, [r4, #252]
	ldr	r3, [r8, r3, asl #2]
	ldrsb	r10, [r3, #44]
	cmp	r10, #1
	movne	r7, #2
	movne	r9, r7
	beq	.L4162
.L4094:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2356]
	ldr	r10, [r4, #2376]
	bl	BsGet
	mov	r1, #6
	str	r0, [r10, #16]
	ldr	r0, [r4, #2356]
	ldr	r10, [r4, #2376]
	bl	BsGet
	str	r0, [r10, #24]
	ldr	r10, [r4, #2376]
	ldr	r2, [r10, #24]
	cmp	r2, #0
	bne	.L4163
	mov	r1, #3
	ldr	r0, [r4, #2356]
	bl	BsGet
	str	r0, [r10, #28]
	ldr	r10, [r4, #2376]
	ldr	r3, [r10, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r10, #28]
	ldrne	r10, [r4, #2376]
	ldr	r0, [r10, #16]
	bl	HEVC_IsSliceUnit
	cmp	r0, #1
	beq	.L4164
	mov	r3, #0
	str	r3, [r10, #4]
	ldr	r3, [r4, #2376]
	add	r0, r4, #2544
	add	r0, r0, #8
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #44]
	bl	BsInit
	mov	r1, #24
	ldr	r0, [r4, #2356]
	bl	BsSkip
	cmp	r7, #0
	cmpeq	r9, #1
	moveq	r7, #1
	movne	r7, #0
	cmp	r6, #1
	moveq	r6, #0
	andne	r6, r7, #1
	cmp	r6, #0
	beq	.L4114
	mov	r1, #16
	ldr	r0, [r4, #2356]
	bl	BsSkip
.L4114:
	mov	r1, #1
	ldr	r0, [r4, #2356]
	bl	BsGet
	mov	r1, #6
	ldr	r0, [r4, #2356]
	ldr	r6, [r4, #2376]
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #16]
	ldr	r0, [r4, #2356]
	ldr	r6, [r4, #2376]
	bl	BsGet
	mov	r1, #3
	str	r0, [r6, #24]
	ldr	r0, [r4, #2356]
	ldr	r6, [r4, #2376]
	bl	BsGet
	str	r0, [r6, #28]
	ldr	r2, [r4, #2376]
	ldr	r3, [r2, #28]
	cmp	r3, #0
	subne	r3, r3, #1
	strne	r3, [r2, #28]
.L4104:
	mov	r0, r4
	bl	HEVC_DecOneNal
	cmn	r0, #2
	beq	.L4120
	cmp	r0, #0
	bne	.L4165
	ldr	r3, [r4, #2324]
	str	r0, [r4, #3560]
	cmp	r3, #1
	bne	.L4116
	mov	r0, r4
	bl	HEVCDEC_SetDecParam
	b	.L4157
.L4164:
	str	r0, [fp, #-72]
	sub	r2, fp, #48
	sub	r1, fp, #52
	mov	r0, r4
	bl	HEVC_InquireSliceProperty
	ldr	r3, [fp, #-72]
	subs	ip, r0, #0
	bne	.L4099
	ldr	r6, [fp, #-52]
	cmp	r6, #1
	beq	.L4166
.L4100:
	ldr	r6, [fp, #-48]
	cmp	r6, #1
	bne	.L4104
	ldr	r3, [r4, #2376]
	mov	r0, r4
	ldr	r3, [r3, #24]
	add	r3, r4, r3
	ldrb	r7, [r3, #4]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L4167
	bl	HEVC_FlushOutputFrmFromDPB
	cmp	r0, #0
	bne	.L4168
.L4107:
	ldr	r0, [r4, #252]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4104
	sub	r3, fp, #56
	ldr	r0, [r4, #252]
	sub	r2, fp, #60
	sub	r1, fp, #64
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r4, #2404]
	ldr	r0, [r3, #724]
	cmp	r0, #1
	bne	.L4104
	ldr	r6, [fp, #-56]
	cmp	r6, #0
	bgt	.L4110
	ldr	r3, [fp, #-60]
	cmp	r3, #32
	bgt	.L4110
	ldr	r3, [r4, #2412]
	cmp	r3, #0
	bne	.L4110
	ldr	r2, [fp, #-48]
	cmp	r2, #0
	beq	.L4104
	ldr	r3, [r4, #240]
	cmp	r3, #0
	beq	.L4104
	ldr	r3, [r4, #2388]
	ldr	r1, [r4, #312]
	ldr	lr, [r3, #68]
	cmp	lr, r1
	beq	.L4104
	ldr	ip, [r3, #64]
	ldr	r3, [r4, #316]
	subs	r7, ip, r3
	movne	r7, #1
	cmp	r6, #0
	movne	r7, #0
	cmp	r7, #0
	beq	.L4104
	stmia	sp, {r1, ip, lr}
	ldr	r1, .L4169+12
	bl	dprint_vfmw
	ldr	r3, [r4, #2388]
	ldr	r1, .L4169+16
	ldr	r2, [r3, #68]
	ldr	ip, [r1]
	str	r2, [r4, #312]
	cmp	ip, #0
	ldr	r3, [r3, #64]
	str	r3, [r4, #316]
	beq	.L4104
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
	b	.L4104
.L4160:
	ldr	r1, .L4169+20
	mvn	r5, #0
	bl	dprint_vfmw
	b	.L4157
.L4162:
	ldr	r9, [r3, #152]
	mov	r0, r4
	ldr	r7, [r3, #156]
	ldr	r3, [r3, #160]
	mov	r1, r9
	mov	r2, r7
	bl	HEVC_VES_Splitter
	cmp	r0, #2
	beq	.L4118
	cmp	r0, #1
	beq	.L4094
.L4120:
	mov	r5, r0
	b	.L4157
.L4163:
	ldr	r1, .L4169+24
	mov	r3, #0
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L4158
	ldr	r0, [r4, #252]
	mvn	r5, #0
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
	b	.L4157
.L4118:
	mov	r6, r10
	b	.L4094
.L4099:
	ldr	r1, .L4169+28
	mov	r0, r3
	bl	dprint_vfmw
	ldr	r1, [r4, #2376]
	cmp	r1, #0
	beq	.L4112
	ldr	r0, [r4, #252]
	bl	HEVC_ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #2376]
.L4112:
	ldr	r3, .L4169+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4113
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #252]
	blx	ip
.L4113:
	ldr	r3, [r4, #252]
	ldr	r3, [r8, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	bne	.L4158
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L4158
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L4158
	add	r3, r4, #8192
	ldrb	r6, [r3, #2912]	@ zero_extendqisi2
	cmp	r6, #0
	bne	.L4158
	ldr	r3, .L4169+32
	add	r0, r4, #11072
	mov	r1, r6
	add	r0, r0, #32
	mov	r2, #56
	mvn	r5, #0
	ldr	r3, [r3, #48]
	blx	r3
	add	r3, r4, #2896
	mov	r0, #0
	mov	r1, #0
	strd	r0, [r3, #32]
	strd	r0, [r3, #8]
	strd	r0, [r3, #16]
	strd	r0, [r3, #24]
	str	r6, [r4, #2884]
	b	.L4157
.L4159:
	mov	r0, r1
	ldr	r1, .L4169+36
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L4157
.L4166:
	ldr	r3, [r4, #204]
	cmp	r3, #0
	bne	.L4101
	ldrb	r3, [r4, #3505]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4100
	ldr	r2, .L4169+40
	ldr	r1, .L4169+44
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	b	.L4100
.L4101:
	ldr	r3, [r4, #2376]
	add	r0, r4, #2544
	mov	r2, #13
	add	r0, r0, #8
	ldr	r1, .L4169+48
	mvn	r5, #1
	str	ip, [r3, #4]
	bl	BsInit
	mov	r1, #40
	ldr	r0, [r4, #2356]
	bl	BsSkip
	ldr	r3, [r4, #2376]
	mov	r2, #48
	mov	r0, r4
	str	r2, [r3, #16]
	strb	r6, [r4, #8]
	bl	HEVC_DecOneNal
	ldr	r3, [r4, #280]
	strb	r6, [r4, #7]
	add	r3, r3, #1
	str	r3, [r4, #280]
	b	.L4157
.L4167:
	bl	HEVC_EmptyFrmFromDPB
	cmp	r0, #0
	beq	.L4107
	mov	r0, r7
	ldr	r2, .L4169+52
	ldr	r1, .L4169+56
	bl	dprint_vfmw
	b	.L4107
.L4168:
	mov	r0, r6
	ldr	r2, .L4169+52
	ldr	r1, .L4169+60
	bl	dprint_vfmw
	b	.L4107
.L4110:
	mov	r3, #1
	mvn	r5, #1
	strb	r3, [r4, #7]
	b	.L4157
.L4170:
	.align	2
.L4169:
	.word	.LC500
	.word	.LC504
	.word	s_pstVfmwChan
	.word	.LC502
	.word	g_event_report
	.word	.LC499
	.word	.LC501
	.word	.LC503
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC498
	.word	.LANCHOR0+916
	.word	.LC490
	.word	.LANCHOR0+1000
	.word	.LANCHOR0+976
	.word	.LC473
	.word	.LC472
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
	ldr	ip, [r0, #3564]
	mov	r4, r0
	ldr	r0, [r0, #2404]
	mov	r6, r3
	cmp	ip, #0
	ldr	lr, [fp, #4]
	ldr	r2, [fp, #8]
	ldr	r5, [r0, #636]
	str	r1, [r4, #3544]
	beq	.L4172
	add	r3, r4, #4096
	ldrb	r1, [r3, #1821]	@ zero_extendqisi2
	strb	r1, [ip, #3]
	ldrb	r3, [r3, #1816]	@ zero_extendqisi2
	strb	r3, [ip, #4]
	ldr	r0, [r4, #2404]
.L4172:
	ldr	ip, [r4, #2352]
	cmp	ip, #1
	bls	.L4173
.L4176:
	ldr	r3, [r4, #3524]
	cmp	r3, #1920
	bhi	.L4206
.L4174:
	ldr	r3, [r0, #632]
	cmp	lr, #0
	str	r3, [r4, #2324]
	beq	.L4179
.L4210:
	ldr	r3, .L4211
	mov	r0, r2, asl #6
	sub	r2, r0, r2, asl #3
	add	r2, r2, r3
	ldr	r3, [r2, #4]
	cmp	r3, #3
	beq	.L4207
	cmp	r3, #1
	beq	.L4179
.L4182:
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_StorePicInDPB
	subs	r7, r0, #0
	bne	.L4208
	cmp	r5, #1
	beq	.L4209
.L4184:
	mov	r3, #1
	mov	r0, #0
	str	r3, [r4, #172]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4206:
	ldr	r3, [r0, #8]
	cmp	r3, #2
	movne	r3, #0
	strne	r3, [r4, #2324]
	beq	.L4174
	cmp	lr, #0
	bne	.L4210
.L4179:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	b	.L4182
.L4208:
	mov	r2, r7
	ldr	r1, .L4211+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	HEVC_ClearCurrPic
	mov	r0, r4
	bl	HEVC_ClearDPB
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4173:
	add	ip, ip, #1
	str	ip, [r4, #2352]
	cmp	ip, #1
	bls	.L4174
	b	.L4176
.L4209:
	ldr	r9, [r4, #2412]
	ldr	r3, [r9, #1292]
	add	r3, r9, r3, lsl #2
	ldr	r10, [r3, #1476]
	mov	r0, r10
	bl	MEM_Phy2Vir
	ldr	r6, [r9, #76]
	ldr	r3, [r9, #192]
	mov	r1, r10
	ldr	r2, [r9, #196]
	mov	r5, r5, asl r6
	sub	r3, r3, #1
	ldr	ip, .L4211+8
	sub	r2, r2, #1
	add	r3, r3, r5
	add	r5, r2, r5
	mov	r3, r3, lsr r6
	ldr	ip, [ip, #140]
	mov	r6, r5, lsr r6
	mul	r6, r6, r3
	mov	r2, r6, asl #4
	mov	r8, r0
	blx	ip
	cmp	r6, #0
	beq	.L4195
	mov	r2, r7
	mov	lr, r7
	mov	r5, r7
	mov	r1, r7
	mov	r0, r8
	mvn	r7, #-2147483648
.L4192:
	ldrh	ip, [r0, #4]
	ubfx	r3, ip, #0, #15
	sxth	ip, ip
	rsb	r8, ip, #0
	tst	ip, #32768
	ldrh	ip, [r0, #6]
	ubfxne	r3, r8, #0, #15
	ubfx	r8, ip, #0, #15
	sxth	ip, ip
	tst	ip, #32768
	rsb	r9, ip, #0
	ubfxne	r8, r9, #0, #15
	add	r3, r3, r8
	cmp	r5, r3
	movlt	r5, r3
	cmp	r3, #0
	addeq	lr, lr, #1
	beq	.L4191
	cmp	r7, r3
	movge	r7, r3
.L4191:
	add	r1, r1, #1
	add	r2, r2, r3
	cmp	r1, r6
	add	r0, r0, #16
	bne	.L4192
	mov	r8, #100
	mov	r0, r2
	mul	r8, r8, lr
.L4185:
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r9, r0
	mov	r0, r8
	bl	__aeabi_uidiv
	mov	r3, r0
	ldr	r0, [r4, #3564]
	cmp	r3, #100
	moveq	r7, #0
	cmp	r0, #0
	beq	.L4194
	str	r5, [r0, #324]
	ldr	r2, [r4, #3564]
	str	r7, [r2, #328]
	ldr	r2, [r4, #3564]
	str	r9, [r2, #332]
	ldr	r2, [r4, #3564]
	str	r3, [r2, #336]
	str	r5, [r4, #3812]
	str	r7, [r4, #3816]
	str	r9, [r4, #3820]
	str	r3, [r4, #3824]
	b	.L4184
.L4207:
	mov	r0, r4
	bl	HEVC_ClearAllSlice
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4195:
	mov	r8, r6
	mov	r0, r6
	mvn	r7, #-2147483648
	mov	r5, r6
	b	.L4185
.L4194:
	ldr	r1, .L4211+12
	bl	dprint_vfmw
	b	.L4184
.L4212:
	.align	2
.L4211:
	.word	g_VdmDrvParam+40
	.word	.LC505
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC506
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
	ldr	r2, [r0, #2388]
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
	ldr	r2, [r0, #2388]
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
	ldr	r3, [r0, #2588]
	mov	r4, r0
	cmp	r3, #0
	bne	.L4216
	b	.L4220
.L4230:
	ldr	r3, [fp, #-36]
.L4217:
	mov	r1, r3
	mov	r0, r4
	bl	HEVC_RemoveApcStore
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	HEVC_RemoveFrameStoreOutDPB
	ldr	r3, [r4, #2588]
	cmp	r3, #0
	beq	.L4220
.L4216:
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	mov	r6, #1
	bl	HEVC_GetMinPOC
	ldr	r3, [fp, #-36]
	mov	r0, r4
	add	r2, r3, #652
	ldr	r5, [r4, r2, asl #2]
	cmp	r5, #0
	mov	r1, r5
	beq	.L4217
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	cmp	r2, r6
	beq	.L4217
	strb	r6, [r5, #2]
	bl	HEVC_GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	HEVC_CheckFrameStore
	subs	r7, r0, #0
	bne	.L4230
	add	r1, r5, #28
	mov	r0, r4
	bl	HEVC_OutputFrame.isra.10
	cmp	r0, #0
	beq	.L4230
	mov	r0, r7
	ldr	r2, .L4231
	ldr	r1, .L4231+4
	bl	dprint_vfmw
	mov	r1, r6
	mov	r0, r4
	bl	HEVC_ClearAll
	b	.L4230
.L4220:
	add	r0, r4, #5504
	add	r0, r0, #56
	bl	GetVoLastImageID
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L4232:
	.align	2
.L4231:
	.word	.LANCHOR0+1016
	.word	.LC418
	UNWIND(.fnend)
	.size	HEVCDEC_GetRemainImg, .-HEVCDEC_GetRemainImg
	.global	g_IsDeced
	.global	g_TsToRsMap
	.global	s_TmpParam
	.global	g_RpuStartCode
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.15537, %object
	.size	__func__.15537, 17
__func__.15537:
	.ascii	"HEVC_OutputFrame\000"
	.space	3
	.type	SarTable.14206, %object
	.size	SarTable.14206, 136
SarTable.14206:
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
	.type	__func__.14364, %object
	.size	__func__.14364, 18
__func__.14364:
	.ascii	"HEVC_CalcTileInfo\000"
	.space	2
	.type	__func__.14844, %object
	.size	__func__.14844, 27
__func__.14844:
	.ascii	"HEVC_GetUnRefPicWithMinPoc\000"
	.space	1
	.type	__func__.14853, %object
	.size	__func__.14853, 21
__func__.14853:
	.ascii	"HEVC_IncreaseDPBSize\000"
	.space	3
	.type	__func__.15105, %object
	.size	__func__.15105, 17
__func__.15105:
	.ascii	"HEVC_WritePicMsg\000"
	.space	3
	.type	__func__.15134, %object
	.size	__func__.15134, 16
__func__.15134:
	.ascii	"HEVC_CheckListX\000"
	.type	__func__.15298, %object
	.size	__func__.15298, 16
__func__.15298:
	.ascii	"HEVC_RepairList\000"
	.type	__func__.15365, %object
	.size	__func__.15365, 16
__func__.15365:
	.ascii	"HEVC_ArrangeMem\000"
	.type	__func__.15438, %object
	.size	__func__.15438, 20
__func__.15438:
	.ascii	"HEVC_RemoveApcStore\000"
	.type	__func__.15707, %object
	.size	__func__.15707, 21
__func__.15707:
	.ascii	"HEVC_CheckFrameStore\000"
	.space	3
	.type	__func__.15775, %object
	.size	__func__.15775, 19
__func__.15775:
	.ascii	"HEVC_GetSLHDR1Info\000"
	.space	1
	.type	__func__.15902, %object
	.size	__func__.15902, 14
__func__.15902:
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
	.type	__func__.16217, %object
	.size	__func__.16217, 16
__func__.16217:
	.ascii	"HEVC_ReleaseNAL\000"
	.type	__func__.15397, %object
	.size	__func__.15397, 20
__func__.15397:
	.ascii	"HEVC_InitDecBuffers\000"
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
	.type	__func__.14958, %object
	.size	__func__.14958, 27
__func__.14958:
	.ascii	"HEVC_DecSliceSegmentHeader\000"
	.space	1
	.type	__func__.15376, %object
	.size	__func__.15376, 13
__func__.15376:
	.ascii	"HEVC_InitDPB\000"
	.space	3
	.type	__func__.15544, %object
	.size	__func__.15544, 19
__func__.15544:
	.ascii	"HEVC_OutputCurrPic\000"
	.space	1
	.type	__func__.15549, %object
	.size	__func__.15549, 23
__func__.15549:
	.ascii	"HEVC_FirstFrameFastOut\000"
	.space	1
	.type	__func__.15699, %object
	.size	__func__.15699, 19
__func__.15699:
	.ascii	"HEVC_OutputFrmToVO\000"
	.space	1
	.type	__func__.15661, %object
	.size	__func__.15661, 22
__func__.15661:
	.ascii	"HEVC_OutputFrmFromDPB\000"
	.space	2
	.type	__func__.14859, %object
	.size	__func__.14859, 30
__func__.14859:
	.ascii	"HEVC_OutputUnRefPicWithMinPoc\000"
	.space	2
	.type	__func__.15674, %object
	.size	__func__.15674, 27
__func__.15674:
	.ascii	"HEVC_FlushOutputFrmFromDPB\000"
	.space	1
	.type	__func__.16280, %object
	.size	__func__.16280, 14
__func__.16280:
	.ascii	"HEVC_ClearDPB\000"
	.space	2
	.type	__func__.14864, %object
	.size	__func__.14864, 23
__func__.14864:
	.ascii	"HEVC_RecoverDPBProcess\000"
	.space	1
	.type	__func__.15635, %object
	.size	__func__.15635, 20
__func__.15635:
	.ascii	"HEVC_InsertFrmInDPB\000"
	.type	__func__.15554, %object
	.size	__func__.15554, 22
__func__.15554:
	.ascii	"HEVC_SimpleDPBProcess\000"
	.space	2
	.type	__func__.15559, %object
	.size	__func__.15559, 21
__func__.15559:
	.ascii	"HEVC_DecOrderProcess\000"
	.space	3
	.type	__func__.15564, %object
	.size	__func__.15564, 22
__func__.15564:
	.ascii	"HEVC_DispOrderProcess\000"
	.space	2
	.type	__func__.15578, %object
	.size	__func__.15578, 19
__func__.15578:
	.ascii	"HEVC_StorePicInDPB\000"
	.space	1
	.type	__func__.15220, %object
	.size	__func__.15220, 12
__func__.15220:
	.ascii	"HEVC_DecVDM\000"
	.type	__func__.14094, %object
	.size	__func__.14094, 18
__func__.14094:
	.ascii	"HEVC_VES_Splitter\000"
	.space	2
	.type	__func__.14895, %object
	.size	__func__.14895, 14
__func__.14895:
	.ascii	"HEVC_DecSlice\000"
	.space	2
	.type	__func__.16362, %object
	.size	__func__.16362, 20
__func__.16362:
	.ascii	"HEVC_HaveSliceToDec\000"
	.type	__func__.16408, %object
	.size	__func__.16408, 13
__func__.16408:
	.ascii	"HEVCDEC_Init\000"
	.space	3
	.type	__func__.16422, %object
	.size	__func__.16422, 23
__func__.16422:
	.ascii	"HEVCDEC_GetImageBuffer\000"
	.space	1
	.type	__func__.16437, %object
	.size	__func__.16437, 21
__func__.16437:
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
	.type	__func__.16486, %object
	.size	__func__.16486, 21
__func__.16486:
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
	ASCII(.ascii	"%s: pImg is NULL!\012\000" )
	.space	1
.LC3:
	ASCII(.ascii	"%s: InsertImgToVoQueue failed!\012\000" )
.LC4:
	ASCII(.ascii	"dar=%d\012\000" )
.LC5:
	ASCII(.ascii	"--------------- PrintNaluArraySlot START ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"--------------- PrintNaluArraySlot END ------------" )
	ASCII(.ascii	"---\012\000" )
.LC8:
	ASCII(.ascii	"NalArray[%d]=%p,is_valid=%d   \000" )
	.space	1
.LC9:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX START ---------" )
	ASCII(.ascii	"------\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"List0, size: %d\012\000" )
	.space	3
.LC11:
	ASCII(.ascii	"List1, size: %d\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"pListX[0][%d]:%p \000" )
	.space	2
.LC13:
	ASCII(.ascii	"pFrameStore:%p \000" )
.LC14:
	ASCII(.ascii	"pLogicFs:%p \000" )
	.space	3
.LC15:
	ASCII(.ascii	"--------------- PrintCurrSlicelistX END -----------" )
	ASCII(.ascii	"----\012\000" )
	.space	3
.LC16:
	ASCII(.ascii	"pListX[1][%d]: %p\000" )
	.space	2
.LC17:
	ASCII(.ascii	"--------------- PrintFrameStoreState START --------" )
	ASCII(.ascii	"-------\012\000" )
.LC18:
	ASCII(.ascii	"--------------- PrintFrameStoreState END ----------" )
	ASCII(.ascii	"-----\012\000" )
	.space	2
.LC19:
	ASCII(.ascii	"Fs=%d, pFs=%p, state=%d, is_reference=%d, is_displa" )
	ASCII(.ascii	"yed=%d \000" )
	.space	1
.LC20:
	ASCII(.ascii	"p_usrdat[%d]=%p \000" )
	.space	3
.LC21:
	ASCII(.ascii	"--------------- PrintAPCState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"Layer %d: APC.used_size:%d, APC.size:%d\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"%d: is_used=%d, idc=%d, poc=%d\012\000" )
.LC24:
	ASCII(.ascii	"--------------- PrintAPCState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC25:
	ASCII(.ascii	"--------------- PrintDPBState START ---------------" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"DPB: size:%d, used_size:%d, negative:%d, positive:%" )
	ASCII(.ascii	"d, longterm:%d\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"fs[%d]:%p view %d non_existing:%d state:%d is_ref:%" )
	ASCII(.ascii	"d displayed:%d poc:%d long_term:%d LogicFs:%p, fsp_" )
	ASCII(.ascii	"ref:%d fsp_disp:%d logic_id:%d img_id:%d\012\000" )
.LC28:
	ASCII(.ascii	"--------------- PrintDPBState END ---------------\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC29:
	ASCII(.ascii	"fs[%d]\011\000" )
.LC30:
	ASCII(.ascii	"LogicFs:%p\011\000" )
.LC31:
	ASCII(.ascii	"LogicTick:%d\011\000" )
	.space	2
.LC32:
	ASCII(.ascii	"IsRef:%d\011\000" )
	.space	2
.LC33:
	ASCII(.ascii	"DispState:%d\011\000" )
	.space	2
.LC34:
	ASCII(.ascii	"LogicFs:Null\011\000" )
	.space	2
.LC35:
	ASCII(.ascii	"DecFs:%p\011\000" )
	.space	2
.LC36:
	ASCII(.ascii	"DecTick:%d\011\000" )
.LC37:
	ASCII(.ascii	"DecFs:Null\011\000" )
.LC38:
	ASCII(.ascii	"DispFs:%p\011\000" )
	.space	1
.LC39:
	ASCII(.ascii	"DispTick:%d\011\000" )
	.space	3
.LC40:
	ASCII(.ascii	"DispFs:Null\011\000" )
	.space	3
.LC41:
	ASCII(.ascii	"%s num_tile_columns(%d) out of range(0, %d].\012\000" )
	.space	2
.LC42:
	ASCII(.ascii	"%s num_tile_rows(%d) out of range(0, %d].\012\000" )
	.space	1
.LC43:
	ASCII(.ascii	"%s 0 idx(%d) out of range(0, 512).\012\000" )
.LC44:
	ASCII(.ascii	"%s 1 idx(%d) out of range(0, 512).\012\000" )
.LC45:
	ASCII(.ascii	"HEVC_Sei_User_Data_Unregistered payloadSize < 16\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC46:
	ASCII(.ascii	"pListX[0][%d] = NULL, listXsize[0] = %d\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL, listXsize[0] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC48:
	ASCII(.ascii	"pListX[0][%d] frame_store(%p), pstLogicFs(%p) inval" )
	ASCII(.ascii	"id\012\000" )
	.space	1
.LC49:
	ASCII(.ascii	"pListX[1][%d] = NULL, listXsize[1] = %d\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL, listXsize[1] = %" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC51:
	ASCII(.ascii	"pListX[i][%d] pstLogicFs(%p) invalid\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"%s DPB.used_size(%d) >= 17.\012\000" )
	.space	3
.LC53:
	ASCII(.ascii	"%s can't find such pic.\012\000" )
	.space	3
.LC54:
	ASCII(.ascii	"%s find pos=%d, poc=%d.\012\000" )
	.space	3
.LC55:
	ASCII(.ascii	"%s DPB.size(%d) already reached max(%d).\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"%s increase DPB size to %d\012\000" )
.LC57:
	ASCII(.ascii	"%s no enough fs(total_fs_num=%d) to increase DPB si" )
	ASCII(.ascii	"ze.\012\000" )
.LC58:
	ASCII(.ascii	"TileWidthInCtb is 0\012\000" )
	.space	3
.LC59:
	ASCII(.ascii	"image_id=%d, pmv_idc=%d\012\000" )
	.space	3
.LC60:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"%s call HEVC_CalcTileInfo failed.\012\000" )
	.space	1
.LC62:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"%s ERROR: bHaveIndependentSlice = 0\012\012\000" )
	.space	2
.LC65:
	ASCII(.ascii	"ListX ERROR: list0size >= %d\012\000" )
	.space	2
.LC66:
	ASCII(.ascii	"ListX ERROR: list1size >= %d\012\000" )
	.space	2
.LC67:
	ASCII(.ascii	"pListX[0][%d] = NULL\012\000" )
	.space	2
.LC68:
	ASCII(.ascii	"pListX[0][%d]->frame_store = NULL\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"pListX[1][%d] = NULL\012\000" )
	.space	2
.LC70:
	ASCII(.ascii	"pListX[1][%d]->frame_store = NULL\012\000" )
	.space	1
.LC71:
	ASCII(.ascii	"NumSlicePara(%d) >= MaxSliceNum(%d)\012\000" )
	.space	3
.LC72:
	ASCII(.ascii	"line:%d pic_parameter_set_id(%d) out of range(0,%d)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC73:
	ASCII(.ascii	"line:%d seq_parameter_set_id(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC74:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d) num_of_pics %d\012\000" )
	.space	3
.LC75:
	ASCII(.ascii	"line:%d, i(%d) > Max(%d)(neg%d + pos%d)\012\000" )
	.space	3
.LC76:
	ASCII(.ascii	"%s unkown slice type(%d).\012\000" )
	.space	1
.LC77:
	ASCII(.ascii	"%s pListX[%d] no available pic to repair.\012\000" )
	.space	1
.LC78:
	ASCII(.ascii	"%s: pListX[%d][%d] = NULL, repair it with pos(%d).\012" )
	ASCII(.ascii	"\000" )
.LC79:
	ASCII(.ascii	"HEVC_InitListX error.\012\000" )
	.space	1
.LC80:
	ASCII(.ascii	"HEVC_RepairList error.\012\000" )
.LC81:
	ASCII(.ascii	"%s image size abnormal(%dx%d)\012\000" )
	.space	1
.LC82:
	ASCII(.ascii	"%s HEVC FSP_ConfigInstance failed!\012\000" )
.LC83:
	ASCII(.ascii	"%s fs[%d]->view_id = %d invalid.\012\000" )
	.space	2
.LC84:
	ASCII(.ascii	"../../core/syntax/hevc.c\000" )
	.space	3
.LC85:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC86:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC87:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(poc=%d, ref=%" )
	ASCII(.ascii	"d, logic_fs=%p, dec_fs=%p)\012\000" )
	.space	1
.LC88:
	ASCII(.ascii	"Cant find free apc slot.\012\000" )
	.space	2
.LC89:
	ASCII(.ascii	"%s frame logic_fs_id=%d, state=%d\012\000" )
	.space	1
.LC90:
	ASCII(.ascii	"LogicFs(fs=%p, poc=%d, FirstFrameState=%d) is null," )
	ASCII(.ascii	" logic_fs_id = %d\012\000" )
	.space	2
.LC91:
	ASCII(.ascii	"%s frame poc=%d, is already output\012\000" )
.LC92:
	ASCII(.ascii	"%s frame(%p) invalid, state:%d, non_existing:%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC93:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC94:
	ASCII(.ascii	"HEVC_DECRecycleImage ERROR, DispState = FS_DISP_STA" )
	ASCII(.ascii	"TE_NOT_USED\012\000" )
.LC95:
	ASCII(.ascii	"%-5d   specVersion\012\000" )
.LC96:
	ASCII(.ascii	"%-5d   payloadMode\012\000" )
.LC97:
	ASCII(.ascii	"%-5d   hdrPicColourSpace\012\000" )
	.space	2
.LC98:
	ASCII(.ascii	"%-5d   hdrMasterDisplayColourSpace\012\000" )
.LC99:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMaxLuminance\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"%-5d   hdrMasterDisplayMinLuminance\012\000" )
	.space	3
.LC101:
	ASCII(.ascii	"%-5d   sdrPicColourSpace\012\000" )
	.space	2
.LC102:
	ASCII(.ascii	"%-5d   sdrMasterDisplayColourSpace\012\000" )
.LC103:
	ASCII(.ascii	"%-5d   tmInputSignalBlackLevelOffset\012\000" )
	.space	2
.LC104:
	ASCII(.ascii	"%-5d   tmInputSignalWhiteLevelOffset\012\000" )
	.space	2
.LC105:
	ASCII(.ascii	"%-5d   shadowGain\012\000" )
	.space	1
.LC106:
	ASCII(.ascii	"%-5d   highlightGain\012\000" )
	.space	2
.LC107:
	ASCII(.ascii	"%-5d   midToneWidthAdjFactor\012\000" )
	.space	2
.LC108:
	ASCII(.ascii	"%-5d   tmOutputFineTuningNumVal\012\000" )
	.space	3
.LC109:
	ASCII(.ascii	"%-5d   saturationGainNumVal\012\000" )
	.space	3
.LC110:
	ASCII(.ascii	"%-5d   tmOutputFineTuningX[%d]\012\000" )
.LC111:
	ASCII(.ascii	"%-5d   tmOutputFineTuningY[%d]\012\000" )
.LC112:
	ASCII(.ascii	"%-5d   saturationGainX[%d]\012\000" )
.LC113:
	ASCII(.ascii	"%-5d   saturationGainY[%d]\012\000" )
.LC114:
	ASCII(.ascii	"%-5d   luminanceMappingNumVal\012\000" )
	.space	1
.LC115:
	ASCII(.ascii	"%-5d   colourCorrectionNumVal\012\000" )
	.space	1
.LC116:
	ASCII(.ascii	"%-5d   luminanceMappingX[%d]\012\000" )
	.space	2
.LC117:
	ASCII(.ascii	"%-5d   luminanceMappingY[%d]\012\000" )
	.space	2
.LC118:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuA\012\000" )
	.space	3
.LC119:
	ASCII(.ascii	"%-5d   chromaToLumaInjectionMuB\012\000" )
	.space	3
.LC120:
	ASCII(.ascii	"%-5d   colourCorrectionX[%d]\012\000" )
	.space	2
.LC121:
	ASCII(.ascii	"%-5d   colourCorrectionY[%d]\012\000" )
	.space	2
.LC122:
	ASCII(.ascii	"======SL_HDR1_METADATA= %d=======\012\000" )
	.space	1
.LC123:
	ASCII(.ascii	"%s, [%d %d %d %d %d]\012\000" )
	.space	2
.LC124:
	ASCII(.ascii	"%s HDR_Metadata_phy_addr is invalid!!\012\000" )
	.space	1
.LC125:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC126:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC127:
	ASCII(.ascii	"FSP_GetFspType -1\012\000" )
	.space	1
.LC128:
	ASCII(.ascii	"FSP_GetLogicFs return NULL\012\000" )
.LC129:
	ASCII(.ascii	"%s: pHevcCtx->DPB.used_size(%d) > DPB.size(%d), err" )
	ASCII(.ascii	"or resilence.\012\000" )
	.space	2
.LC130:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC131:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck pic_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC132:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC133:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck seq_parameter_set_id(%d) out of" )
	ASCII(.ascii	" range\012\000" )
	.space	1
.LC134:
	ASCII(.ascii	"sps with this seq_parameter_set_id = %d havn't be d" )
	ASCII(.ascii	"ecoded\012\000" )
	.space	1
.LC135:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck video_parameter_set_id out of r" )
	ASCII(.ascii	"ange\012\000" )
	.space	3
.LC136:
	ASCII(.ascii	"vps with this video_parameter_set_id = %d havn't be" )
	ASCII(.ascii	" decoded\012\000" )
	.space	3
.LC137:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, PocRandomAccess = %d, n" )
	ASCII(.ascii	"al_unit_type = %d, should skip this frame\012\000" )
	.space	2
.LC138:
	ASCII(.ascii	"%s, %d, CurrSlice.poc = %d, bNoRaslOutputFlag = %d," )
	ASCII(.ascii	" nal_unit_type = %d, should skip this frame\012\000" )
.LC139:
	ASCII(.ascii	"%s, %d, PrevRAPIsBLA = %d, CurrSlice.poc = %d, PocC" )
	ASCII(.ascii	"RA = %d, nal_unit_type = %d, should skip this frame" )
	ASCII(.ascii	"\012\000" )
.LC140:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code should not be zero.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC141:
	ASCII(.ascii	"HEVC_ReadByteAlignment: code:%d\012\000" )
	.space	3
.LC142:
	ASCII(.ascii	"reserved_zero_2bits not equal 0.\012\000" )
	.space	2
.LC143:
	ASCII(.ascii	"HEVC_GetScalingListDefaultAddress NULL.\012\000" )
	.space	3
.LC144:
	ASCII(.ascii	"Error, BsLen: 0x%x, TotalPos: 0x%x\012\000" )
.LC145:
	ASCII(.ascii	"Panic: All zero data sequence in RBSP \012\000" )
.LC146:
	ASCII(.ascii	"nal_trail_zero_bit_num err\012\000" )
.LC147:
	ASCII(.ascii	"%s release streambuff=%p, bitstream_length=%d\012\000" )
	.space	1
.LC148:
	ASCII(.ascii	"%s DPB size exceed %d, force to %d\012\000" )
.LC149:
	ASCII(.ascii	"HEVC_CombinePacket FATAL: pCurrNal=NULL!\012\000" )
	.space	2
.LC150:
	ASCII(.ascii	"END of the bit buffer, copy the first packet!\012\000" )
	.space	1
.LC151:
	ASCII(.ascii	"tone_map_id\000" )
.LC152:
	ASCII(.ascii	"Unsupport: target_bit_depth(%d) > 8\012\000" )
	.space	3
.LC153:
	ASCII(.ascii	"pTon->num_pivots > 256\012\000" )
.LC154:
	ASCII(.ascii	"frame_packing_arrangement_id\000" )
	.space	3
.LC155:
	ASCII(.ascii	"frame_packing_arrangement_type(%d) out of range\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC156:
	ASCII(.ascii	"decoding_unit_idx\000" )
	.space	2
.LC157:
	ASCII(.ascii	"num_sps_ids_minus1\000" )
	.space	1
.LC158:
	ASCII(.ascii	"pAct->num_sps_ids_minus1 > 15\012\000" )
	.space	1
.LC159:
	ASCII(.ascii	"active_seq_parameter_set_id\000" )
.LC160:
	ASCII(.ascii	"bp_seq_parameter_set_id\000" )
.LC161:
	ASCII(.ascii	"Wrong bp_seq_parameter_set_id = %d, should be 0 to " )
	ASCII(.ascii	"15!\012\000" )
.LC162:
	ASCII(.ascii	"num_decoding_units_minus1\000" )
	.space	2
.LC163:
	ASCII(.ascii	"pPic->num_decoding_units_minus1 > 255\012\000" )
	.space	1
.LC164:
	ASCII(.ascii	"num_nalus_in_du_minus1\000" )
	.space	1
.LC165:
	ASCII(.ascii	"cv_rec_id\000" )
	.space	2
.LC166:
	ASCII(.ascii	"HEVC_Sei_User_Data_Registered_Itu_T_T35 payloadSize" )
	ASCII(.ascii	" < 4!!\012\000" )
	.space	1
.LC167:
	ASCII(.ascii	"delta_idx_minus1\000" )
	.space	3
.LC168:
	ASCII(.ascii	"delta_idx(%d) > idx(%d).\012\000" )
	.space	2
.LC169:
	ASCII(.ascii	"rIdx(%d) > (idx-1)(%d) or < 0).\012\000" )
	.space	3
.LC170:
	ASCII(.ascii	"abs_delta_rps_minus1\000" )
	.space	3
.LC171:
	ASCII(.ascii	"pTempRPset->num_of_pics(%d) out of range(0,15).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC172:
	ASCII(.ascii	"num_of_pics out of range(0,15).\012\000" )
	.space	3
.LC173:
	ASCII(.ascii	"num_negative_pics\000" )
	.space	2
.LC174:
	ASCII(.ascii	"pTempRPset->num_negative_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC175:
	ASCII(.ascii	"num_positive_pics\000" )
	.space	2
.LC176:
	ASCII(.ascii	"pTempRPset->num_positive_pics(%d) out of range(0,15" )
	ASCII(.ascii	").\012\000" )
	.space	1
.LC177:
	ASCII(.ascii	"pShortTermRpset->num_of_pics(%d) out of range[0,%d]" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC178:
	ASCII(.ascii	"delta_poc_s0_minus1\000" )
.LC179:
	ASCII(.ascii	"delta_poc_s0_minus1(%d) out of range.\012\000" )
	.space	1
.LC180:
	ASCII(.ascii	"delta_poc_s1_minus1\000" )
.LC181:
	ASCII(.ascii	"elemental_duration_in_tc_minus1\000" )
.LC182:
	ASCII(.ascii	"cpb_cnt_minus1\000" )
	.space	1
.LC183:
	ASCII(.ascii	"cpb_cnt_minus1(%d) out of range(0,31).\012\000" )
.LC184:
	ASCII(.ascii	"bit_rate_value_minus1\000" )
	.space	2
.LC185:
	ASCII(.ascii	"cpb_size_value_minus1\000" )
	.space	2
.LC186:
	ASCII(.ascii	"cpb_size_du_value_minus1\000" )
	.space	3
.LC187:
	ASCII(.ascii	"bit_rate_du_value_minus1\000" )
	.space	3
.LC188:
	ASCII(.ascii	"vps_base_layer_available_flag(%d) not equal 0x1.\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC189:
	ASCII(.ascii	"vps_max_layers_minus1 %d out of range[0,63].\012\000" )
	.space	2
.LC190:
	ASCII(.ascii	"vps_max_sub_layers_minus1=%d\012\000" )
	.space	2
.LC191:
	ASCII(.ascii	"vps_reserved_0xffff_16bits not equal 0xffff.\012\000" )
	.space	2
.LC192:
	ASCII(.ascii	"VPS HEVC_DecPTL error.\012\000" )
.LC193:
	ASCII(.ascii	"vps_num_layer_sets_minus1\000" )
	.space	2
.LC194:
	ASCII(.ascii	"vps_max_dec_pic_buffering_minus1[i]\000" )
.LC195:
	ASCII(.ascii	"vps_num_reorder_pics[i]\000" )
.LC196:
	ASCII(.ascii	"vps_max_latency_increase_plus1[i]\000" )
	.space	2
.LC197:
	ASCII(.ascii	"vps_num_layer_sets_minus1(%d) out of range(0,%d).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC198:
	ASCII(.ascii	"vps_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC199:
	ASCII(.ascii	"vps_num_hrd_parameters\000" )
	.space	1
.LC200:
	ASCII(.ascii	"vps_num_hrd_parameters(%d) out of range[0,%d].\012\000" )
.LC201:
	ASCII(.ascii	"hrd_layer_set_idx\000" )
	.space	2
.LC202:
	ASCII(.ascii	"VPS HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC203:
	ASCII(.ascii	"pVPS->vps_video_parameter_set_id out of range(0,15)" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC204:
	ASCII(.ascii	"VPS[%d] decode error0.\012\000" )
.LC205:
	ASCII(.ascii	"VPS[%d] decode error1.\012\000" )
.LC206:
	ASCII(.ascii	"chroma_sample_loc_type_top_field\000" )
	.space	3
.LC207:
	ASCII(.ascii	"chroma_sample_loc_type_bottom_field\000" )
.LC208:
	ASCII(.ascii	"def_disp_win_left_offset\000" )
	.space	3
.LC209:
	ASCII(.ascii	"VUI pSps->chroma_format_idc out of range(0,3).\012\000" )
.LC210:
	ASCII(.ascii	"def_disp_win_right_offset\000" )
	.space	2
.LC211:
	ASCII(.ascii	"def_disp_win_top_offset\000" )
.LC212:
	ASCII(.ascii	"def_disp_win_bottom_offset\000" )
	.space	1
.LC213:
	ASCII(.ascii	"vui_num_ticks_poc_diff_one_minus1\000" )
	.space	2
.LC214:
	ASCII(.ascii	"VUI HEVC_DecHrdParam error.\012\000" )
	.space	3
.LC215:
	ASCII(.ascii	"min_spatial_segmentation_idc\000" )
	.space	3
.LC216:
	ASCII(.ascii	"VUI min_spatial_segmentation_idc out of range(0,409" )
	ASCII(.ascii	"5).\012\000" )
.LC217:
	ASCII(.ascii	"max_bytes_per_pic_denom\000" )
.LC218:
	ASCII(.ascii	"max_bits_per_min_cu_denom\000" )
	.space	2
.LC219:
	ASCII(.ascii	"log2_max_mv_length_horizontal\000" )
	.space	2
.LC220:
	ASCII(.ascii	"log2_max_mv_length_vertical\000" )
.LC221:
	ASCII(.ascii	"sop_seq_parameter_set_id\000" )
	.space	3
.LC222:
	ASCII(.ascii	"num_entries_in_sop_minus1\000" )
	.space	2
.LC223:
	ASCII(.ascii	"num_entries_in_sop_minus1 out of range(0,1024)\012\000" )
.LC224:
	ASCII(.ascii	"sop_short_term_rps_idx\000" )
	.space	1
.LC225:
	ASCII(.ascii	"sop_poc_delta\000" )
	.space	2
.LC226:
	ASCII(.ascii	"recovery_poc_cnt\000" )
	.space	3
.LC227:
	ASCII(.ascii	"colour_remap_id\000" )
.LC228:
	ASCII(.ascii	"colour_remap_coeffs\000" )
.LC229:
	ASCII(.ascii	"reserved_payload_extension_data\000" )
.LC230:
	ASCII(.ascii	"line:%d Cosume TotalPos(%d > %d)!!!\012\000" )
	.space	3
.LC231:
	ASCII(.ascii	"HEVC_SeiMessage HEVC_Sei_Payload error.\012\000" )
	.space	3
.LC232:
	ASCII(.ascii	"SEI pSEISPS = NULL.\012\000" )
	.space	3
.LC233:
	ASCII(.ascii	"SEI HEVC_SeiMessage error.\012\000" )
.LC234:
	ASCII(.ascii	"SEI BsIsByteAligned error.\012\000" )
.LC235:
	ASCII(.ascii	"SEI rbsp_trailing_bits(%d) not equal 0x80.\012\000" )
.LC236:
	ASCII(.ascii	"nesting_num_ops_minus1\000" )
	.space	1
.LC237:
	ASCII(.ascii	"nesting_num_ops_minus1 out of range(0,%d)\012\000" )
	.space	1
.LC238:
	ASCII(.ascii	"nesting_op_idx\000" )
	.space	1
.LC239:
	ASCII(.ascii	"nesting_num_layers_minus1\000" )
	.space	2
.LC240:
	ASCII(.ascii	"nesting_num_layers_minus1 out of range(0,63)\012\000" )
	.space	2
.LC241:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta\000" )
	.space	2
.LC242:
	ASCII(.ascii	"scaling_list_pred_matrix_id_delta out of range(0,ma" )
	ASCII(.ascii	"trixId).\012\000" )
	.space	3
.LC243:
	ASCII(.ascii	"HEVC_DecScalingListData pMatrixAddress NULL.\012\000" )
	.space	2
.LC244:
	ASCII(.ascii	"scaling_list_dc_coef_minus8\000" )
.LC245:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-7,247).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC246:
	ASCII(.ascii	"scaling_list_delta_coef\000" )
.LC247:
	ASCII(.ascii	"scaling_list_dc_coef_minus8 out of range(-128,127)." )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC248:
	ASCII(.ascii	"chroma_format_idc\000" )
	.space	2
.LC249:
	ASCII(.ascii	"pSPS->chroma_format_idc out of range(0,3).\012\000" )
.LC250:
	ASCII(.ascii	"pSPS->chroma_format_idc not equal(%d) 1.\012\000" )
	.space	2
.LC251:
	ASCII(.ascii	"pic_width_in_luma_samples\000" )
	.space	2
.LC252:
	ASCII(.ascii	"pic_width_in_luma_samples out of range(0,8192).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC253:
	ASCII(.ascii	"pic_height_in_luma_samples\000" )
	.space	1
.LC254:
	ASCII(.ascii	"pic_height_in_luma_samples out of range(0,4096).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC255:
	ASCII(.ascii	"ERROR Unkown level: %d\012\000" )
.LC256:
	ASCII(.ascii	"conf_win_left_offset\000" )
	.space	3
.LC257:
	ASCII(.ascii	"conf_win_right_offset\000" )
	.space	2
.LC258:
	ASCII(.ascii	"conf_win_left_offset+conf_win_right_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC259:
	ASCII(.ascii	"conf_win_top_offset\000" )
.LC260:
	ASCII(.ascii	"conf_win_bottom_offset\000" )
	.space	1
.LC261:
	ASCII(.ascii	"conf_win_top_offset+conf_win_bottom_offset out of r" )
	ASCII(.ascii	"ange.\012\000" )
	.space	2
.LC262:
	ASCII(.ascii	"bit_depth_luma_minus8\000" )
	.space	2
.LC263:
	ASCII(.ascii	"bit_depth_luma(%d) out of range(8,10).\012\000" )
.LC264:
	ASCII(.ascii	"bit_depth_chroma_minus8\000" )
.LC265:
	ASCII(.ascii	"bit_depth_chroma(%d) out of range[8,14].\012\000" )
	.space	2
.LC266:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	2
.LC267:
	ASCII(.ascii	"log2_max_pic_order_cnt_lsb_minus4 out of range[0,12" )
	ASCII(.ascii	"].\012\000" )
	.space	1
.LC268:
	ASCII(.ascii	"sps_max_dec_pic_buffering_minus1\000" )
	.space	3
.LC269:
	ASCII(.ascii	"sps_num_reorder_pics\000" )
	.space	3
.LC270:
	ASCII(.ascii	"sps_max_latency_increase_plus1\000" )
	.space	1
.LC271:
	ASCII(.ascii	"log2_min_coding_block_size_minus3\000" )
	.space	2
.LC272:
	ASCII(.ascii	"log2_min_luma_coding_block_size_minus3 out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC273:
	ASCII(.ascii	"log2_diff_max_min_coding_block_size\000" )
.LC274:
	ASCII(.ascii	"log2_diff_max_min_luma_coding_block_size out of ran" )
	ASCII(.ascii	"ge(0,3).\012\000" )
	.space	3
.LC275:
	ASCII(.ascii	"log2_ctb_sizeY out of range(4,6).\012\000" )
	.space	1
.LC276:
	ASCII(.ascii	"log2_min_transform_block_size_minus2\000" )
	.space	3
.LC277:
	ASCII(.ascii	"log2_min_transform_block_size_minus2 out of range(0" )
	ASCII(.ascii	",3).\012\000" )
	.space	3
.LC278:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size\000" )
	.space	1
.LC279:
	ASCII(.ascii	"log2_diff_max_min_transform_block_size out of range" )
	ASCII(.ascii	"(0,3).\012\000" )
	.space	1
.LC280:
	ASCII(.ascii	"quadtree_tu_log2_min_size not less than log2_min_cb" )
	ASCII(.ascii	"_sizeY.\012\000" )
.LC281:
	ASCII(.ascii	"quadtree_tu_log2_max_size greater than Min( CtbLog2" )
	ASCII(.ascii	"SizeY, 5 ).\012\000" )
.LC282:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter\000" )
.LC283:
	ASCII(.ascii	"max_transform_hierarchy_depth_inter out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC284:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra\000" )
.LC285:
	ASCII(.ascii	"max_transform_hierarchy_depth_intra out of range(0," )
	ASCII(.ascii	"CtbLog2SizeY-Log2MinTrafoSize).\012\000" )
.LC286:
	ASCII(.ascii	"SPS HEVC_DecScalingListData error.\012\000" )
.LC287:
	ASCII(.ascii	"SPS sao is off and pic height(%d) is too small.(Log" )
	ASCII(.ascii	"ic Unsupported).\012\000" )
	.space	3
.LC288:
	ASCII(.ascii	"log2_min_pcm_luma_coding_block_size_minus3\000" )
	.space	1
.LC289:
	ASCII(.ascii	"log2_min_pcm_coding_block_size_minus3(%d) out of ra" )
	ASCII(.ascii	"nge[0,2].\012\000" )
	.space	2
.LC290:
	ASCII(.ascii	"log2_diff_max_min_pcm_luma_coding_block_size\000" )
	.space	3
.LC291:
	ASCII(.ascii	"log2_diff_max_min_pcm_coding_block_size(%d) out of " )
	ASCII(.ascii	"range[0,2].\012\000" )
.LC292:
	ASCII(.ascii	"pcm_log2_max_size greater than Min( CtbLog2SizeY, 5" )
	ASCII(.ascii	" ).\012\000" )
.LC293:
	ASCII(.ascii	"num_short_term_ref_pic_sets\000" )
.LC294:
	ASCII(.ascii	"num_short_term_ref_pic_sets out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC295:
	ASCII(.ascii	"SPS HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	1
.LC296:
	ASCII(.ascii	"num_long_term_ref_pic_sps\000" )
	.space	2
.LC297:
	ASCII(.ascii	"num_long_term_ref_pic_sps out of range[0,32].\012\000" )
	.space	1
.LC298:
	ASCII(.ascii	"SPS HEVC_DecVuiParam error.\012\000" )
	.space	3
.LC299:
	ASCII(.ascii	"sps_video_parameter_set_id out of range(0,%d).\012\000" )
.LC300:
	ASCII(.ascii	"sps_max_sub_layers_minus1 out of range(0,%d).\012\000" )
	.space	1
.LC301:
	ASCII(.ascii	"SPS HEVC_DecPTL error.\012\000" )
.LC302:
	ASCII(.ascii	"sps_seq_parameter_set_id\000" )
	.space	3
.LC303:
	ASCII(.ascii	"sps_seq_parameter_set_id out of range(0,%d).\012\000" )
	.space	2
.LC304:
	ASCII(.ascii	"SPS[%d] decode error0.\012\000" )
.LC305:
	ASCII(.ascii	"SPS[%d] decode error.\012\000" )
	.space	1
.LC306:
	ASCII(.ascii	"pps_seq_parameter_set_id\000" )
	.space	3
.LC307:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range[0,15].\012\000" )
	.space	2
.LC308:
	ASCII(.ascii	"SPS(%d) haven't decode.\012\000" )
	.space	3
.LC309:
	ASCII(.ascii	"num_ref_idx_l0_default_active_minus1\000" )
	.space	3
.LC310:
	ASCII(.ascii	"num_ref_idx_l0_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC311:
	ASCII(.ascii	"num_ref_idx_l1_default_active_minus1\000" )
	.space	3
.LC312:
	ASCII(.ascii	"num_ref_idx_l1_default_active out of range[0,15].\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC313:
	ASCII(.ascii	"init_qp_minus26\000" )
.LC314:
	ASCII(.ascii	"pic_init_qp(%d) out of range[-%d,51].\012\000" )
	.space	1
.LC315:
	ASCII(.ascii	"diff_cu_qp_delta_depth\000" )
	.space	1
.LC316:
	ASCII(.ascii	"diff_cu_qp_delta_depth out of range[0,3].\012\000" )
	.space	1
.LC317:
	ASCII(.ascii	"pps_cb_qp_offset\000" )
	.space	3
.LC318:
	ASCII(.ascii	"pic_cb_qp_offset out of range[-12,12].\012\000" )
.LC319:
	ASCII(.ascii	"pps_cr_qp_offset\000" )
	.space	3
.LC320:
	ASCII(.ascii	"pic_cr_qp_offset out of range[-12,12].\012\000" )
.LC321:
	ASCII(.ascii	"num_tile_columns_minus1\000" )
.LC322:
	ASCII(.ascii	"num_tile_columns(%d) out of range(0,%d).\012\000" )
	.space	2
.LC323:
	ASCII(.ascii	"num_tile_rows_minus1\000" )
	.space	3
.LC324:
	ASCII(.ascii	"num_tile_rows out(%d) of range(0,%d).\012\000" )
	.space	1
.LC325:
	ASCII(.ascii	"Logic limit(%d), num_tile_columns(%d) exceed.\012\000" )
	.space	1
.LC326:
	ASCII(.ascii	"Logic limit(%d), num_tile_rows(%d) exceed.\012\000" )
.LC327:
	ASCII(.ascii	"column_width_minus1\000" )
.LC328:
	ASCII(.ascii	"column_width[%d](%d) out of range (0 %d)\012\000" )
	.space	2
.LC329:
	ASCII(.ascii	"row_height_minus1\000" )
	.space	2
.LC330:
	ASCII(.ascii	"row_height[%d](%d) out of range (0 %d)\012\000" )
.LC331:
	ASCII(.ascii	"column_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	2
.LC332:
	ASCII(.ascii	"row_bd[%d](%d) <= 0, invalid!\012\000" )
	.space	1
.LC333:
	ASCII(.ascii	"PPS tile width(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC334:
	ASCII(.ascii	"PPS tile height(%d) is too small.(Logic Unsupport)\012" )
	ASCII(.ascii	"\000" )
.LC335:
	ASCII(.ascii	"pps_beta_offset_div2\000" )
	.space	3
.LC336:
	ASCII(.ascii	"pps_beta_offset_div2(%d) out of range(-6,6).\012\000" )
	.space	2
.LC337:
	ASCII(.ascii	"pps_tc_offset_div2\000" )
	.space	1
.LC338:
	ASCII(.ascii	"pps_tc_offset_div2(%d) out of range(-6,6).\012\000" )
.LC339:
	ASCII(.ascii	"PPS HEVC_DecScalingListData error.\012\000" )
.LC340:
	ASCII(.ascii	"log2_parallel_merge_level_minus2\000" )
	.space	3
.LC341:
	ASCII(.ascii	"log2_parallel_merge_level(%d) out of range(2,log2_c" )
	ASCII(.ascii	"tb_sizeY).\012\000" )
	.space	1
.LC342:
	ASCII(.ascii	"pps_pic_parameter_set_id\000" )
	.space	3
.LC343:
	ASCII(.ascii	"pic_parameter_set_id(%d) out of range(0,%d).\012\000" )
	.space	2
.LC344:
	ASCII(.ascii	"PPS[%d] decode error.\012\000" )
	.space	1
.LC345:
	ASCII(.ascii	"luma_log2_weight_denom\000" )
	.space	1
.LC346:
	ASCII(.ascii	"luma_log2_weight_denom out of range(0,7).\012\000" )
	.space	1
.LC347:
	ASCII(.ascii	"delta_chroma_log2_weight_denom\000" )
	.space	1
.LC348:
	ASCII(.ascii	"delta_chroma_log2_weight_denom out of range(-7,7).\012" )
	ASCII(.ascii	"\000" )
.LC349:
	ASCII(.ascii	"chroma_log2_weight_denom out of range(0,7).\012\000" )
	.space	3
.LC350:
	ASCII(.ascii	"delta_luma_weight_l0\000" )
	.space	3
.LC351:
	ASCII(.ascii	"delta_luma_weight_l0(%d) out of range(-128,127).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC352:
	ASCII(.ascii	"luma_offset_l0\000" )
	.space	1
.LC353:
	ASCII(.ascii	"luma_offset_l0(%d) out of range(-128,127).\012\000" )
.LC354:
	ASCII(.ascii	"delta_chroma_weight_l0\000" )
	.space	1
.LC355:
	ASCII(.ascii	"delta_chroma_weight_l0 out of range(-128,127).\012\000" )
.LC356:
	ASCII(.ascii	"delta_chroma_offset_l0\000" )
	.space	1
.LC357:
	ASCII(.ascii	"delta_chroma_offset_l0 out of range(-512,511).\012\000" )
.LC358:
	ASCII(.ascii	"delta_luma_weight_l1\000" )
	.space	3
.LC359:
	ASCII(.ascii	"delta_luma_weight_l1 out of range(-128,127).\012\000" )
	.space	2
.LC360:
	ASCII(.ascii	"luma_offset_l1\000" )
	.space	1
.LC361:
	ASCII(.ascii	"luma_offset_l1 out of range(-128,127).\012\000" )
.LC362:
	ASCII(.ascii	"delta_chroma_weight_l1\000" )
	.space	1
.LC363:
	ASCII(.ascii	"delta_chroma_weight_l1 out of range(-128,127).\012\000" )
.LC364:
	ASCII(.ascii	"delta_chroma_offset_l1\000" )
	.space	1
.LC365:
	ASCII(.ascii	"delta_chroma_offset_l1 out of range(-512,511).\012\000" )
.LC366:
	ASCII(.ascii	"slice_pic_parameter_set_id\000" )
	.space	1
.LC367:
	ASCII(.ascii	"%s: pic_parameter_set_id(%d) out of range(0 %d)!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC368:
	ASCII(.ascii	"HEVC_VpsSpsPpsCheck != HEVC_DEC_NORMAL\012\000" )
.LC369:
	ASCII(.ascii	"max_cu_width(%d)/max_cu_height(%d) = 0\012\000" )
.LC370:
	ASCII(.ascii	"slice_segment_address(%d) out of range(0,%d).\012\000" )
	.space	1
.LC371:
	ASCII(.ascii	"slice_type\000" )
	.space	1
.LC372:
	ASCII(.ascii	"slice_type(%d) out of range(0,2].\012\000" )
	.space	1
.LC373:
	ASCII(.ascii	"HEVC_ClearDPB,LastDisplayPoc:%d poc:%d \012\000" )
	.space	3
.LC374:
	ASCII(.ascii	"SH HEVC_DecShortTermRefPicSet error.\012\000" )
	.space	2
.LC375:
	ASCII(.ascii	"short_term_ref_pic_set_idx(%d) out of range[0,%d].\012" )
	ASCII(.ascii	"\000" )
.LC376:
	ASCII(.ascii	"num_long_term_sps\000" )
	.space	2
.LC377:
	ASCII(.ascii	"num_long_term_sps(%d) out of range[0,%d].\012\000" )
	.space	1
.LC378:
	ASCII(.ascii	"num_long_term_pics\000" )
	.space	1
.LC379:
	ASCII(.ascii	"SH ERROR: (num_negative_pics(%d) + num_positive_pic" )
	ASCII(.ascii	"s(%d) + num_of_longterm_pics(%d)) > %d\012\000" )
	.space	1
.LC380:
	ASCII(.ascii	"lt_idx_sps[%d] = %d, but out of range[0,%d].\012\000" )
	.space	2
.LC381:
	ASCII(.ascii	"delta_poc_msb_cycle_lt\000" )
	.space	1
.LC382:
	ASCII(.ascii	"ERROR: pRPS->num_of_pics(%d) > %d.\012\000" )
.LC383:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC384:
	ASCII(.ascii	"num_ref_idx_l0_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC385:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC386:
	ASCII(.ascii	"num_ref_idx_l1_active(%d) out of range(0,%d).\012\000" )
	.space	1
.LC387:
	ASCII(.ascii	"pRPS is null.\012\000" )
	.space	1
.LC388:
	ASCII(.ascii	"pRPS->num_of_pics out(%d) of range(0,%d).\012\000" )
	.space	1
.LC389:
	ASCII(.ascii	"SH HEVC_DecRefPicListsModification error.\012\000" )
	.space	1
.LC390:
	ASCII(.ascii	"collocated_ref_idx\000" )
	.space	1
.LC391:
	ASCII(.ascii	"collocated_from_l0_flag=%d, collocated_ref_idx(%d) " )
	ASCII(.ascii	"out of range(0,%d).\012\000" )
.LC392:
	ASCII(.ascii	"SH HEVC_DecPredWeightTable error.\012\000" )
	.space	1
.LC393:
	ASCII(.ascii	"five_minus_max_num_merge_cand\000" )
	.space	2
.LC394:
	ASCII(.ascii	"SH max_num_merge_cand(%d) out of range(1,5).\012\000" )
	.space	2
.LC395:
	ASCII(.ascii	"slice_qp_delta\000" )
	.space	1
.LC396:
	ASCII(.ascii	"SH slice_qp(%d) out of range [-%d,51].\012\000" )
.LC397:
	ASCII(.ascii	"slice_cb_qp_offset\000" )
	.space	1
.LC398:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC399:
	ASCII(.ascii	"SH slice_cb_qp_offset(%d)+pic_cb_qp_offset(%d) out " )
	ASCII(.ascii	"of range[-12,12].\012\000" )
	.space	2
.LC400:
	ASCII(.ascii	"slice_cr_qp_offset\000" )
	.space	1
.LC401:
	ASCII(.ascii	"SH slice_cr_qp_offset(%d) out of range[-12,12].\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC402:
	ASCII(.ascii	"SH slice_cr_qp_offset+pPPS->pic_cr_qp_offset(%d) ou" )
	ASCII(.ascii	"t of range[-12,12].\012\000" )
.LC403:
	ASCII(.ascii	"slice_beta_offset_div2\000" )
	.space	1
.LC404:
	ASCII(.ascii	"SH slice_beta_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC405:
	ASCII(.ascii	"slice_tc_offset_div2\000" )
	.space	3
.LC406:
	ASCII(.ascii	"SH slice_tc_offset_div2(%d) out of range(-6,6).\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC407:
	ASCII(.ascii	"num_entry_point_offsets\000" )
.LC408:
	ASCII(.ascii	"CurrSlice.num_entry_point_offsets(%d) out of range[" )
	ASCII(.ascii	"0,%d].\012\000" )
	.space	1
.LC409:
	ASCII(.ascii	"offset_len_minus1\000" )
	.space	2
.LC410:
	ASCII(.ascii	"CurrSlice.offset_len(%d) out of range[1,32].\012\000" )
	.space	2
.LC411:
	ASCII(.ascii	"slice_segment_header_extension_length\000" )
	.space	2
.LC412:
	ASCII(.ascii	"slice_segment_header_extension_length(%d) out of ra" )
	ASCII(.ascii	"nge [0,256]\012\000" )
.LC413:
	ASCII(.ascii	"bitsLeft(%d) < slice_segment_header_extension_lengt" )
	ASCII(.ascii	"h(%d)\012\000" )
	.space	2
.LC414:
	ASCII(.ascii	"%s arrange mem failed.\012\000" )
.LC415:
	ASCII(.ascii	"Init dec para\012\000" )
	.space	1
.LC416:
	ASCII(.ascii	"HEVC_InitDPB error, return %d\012\000" )
	.space	1
.LC417:
	ASCII(.ascii	"HEVC_AllocFrameStore error\012\000" )
.LC418:
	ASCII(.ascii	"%s: HEVC_OutputFrame failed!\012\000" )
	.space	2
.LC419:
	ASCII(.ascii	"%s output current picture failed\012\000" )
	.space	2
.LC420:
	ASCII(.ascii	"HEVC.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC421:
	ASCII(.ascii	"%s: FirstFrameFastOut LastPoc: %d, CurPos: %d!\012\000" )
.LC422:
	ASCII(.ascii	"%s call HEVC_GetUnRefPicWithMinPoc failed\012\000" )
	.space	1
.LC423:
	ASCII(.ascii	"%s call HEVC_OutputOneFrmFromDPB failed\012\000" )
	.space	3
.LC424:
	ASCII(.ascii	"%s: HEVC_OutputFrmToVO err!\012\000" )
	.space	3
.LC425:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC426:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC427:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC428:
	ASCII(.ascii	"%s: flush dpb failed, return %d\012\000" )
	.space	3
.LC429:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), need to incr" )
	ASCII(.ascii	"ease DPB size.\012\000" )
	.space	1
.LC430:
	ASCII(.ascii	"%s call HEVC_IncreaseDPBSize failed\012\000" )
	.space	3
.LC431:
	ASCII(.ascii	"%s: DPB.used_size(%d) >= DPB.size(%d), output minpo" )
	ASCII(.ascii	"c frame.\012\000" )
	.space	3
.LC432:
	ASCII(.ascii	"%s with invalid pos(%d)\012\000" )
	.space	3
.LC433:
	ASCII(.ascii	"%s get APC error, ret %d\012\000" )
	.space	2
.LC434:
	ASCII(.ascii	"%s %d: InsertFrmInDPB failed, return %d\012\000" )
	.space	3
.LC435:
	ASCII(.ascii	"%s call HEVC_CheckFrameStore failed!\012\000" )
	.space	2
.LC436:
	ASCII(.ascii	"%s call HEVC_RemoveUnUsedFrameStore Failed.\012\000" )
	.space	3
.LC437:
	ASCII(.ascii	"%s call HEVC_InsertFrmInDPB Failed.\012\000" )
	.space	3
.LC438:
	ASCII(.ascii	"%s call HEVC_FirstFrameFastOut Failed\012\000" )
	.space	1
.LC439:
	ASCII(.ascii	"DPB.used_size may bigger than DPB.size\012\000" )
.LC440:
	ASCII(.ascii	"HEVC_InsertFrmInDPB Failed, ret = %d\012\000" )
	.space	2
.LC441:
	ASCII(.ascii	"%s call HEVC_OutputFrmFromDPB failed\012\000" )
	.space	2
.LC442:
	ASCII(.ascii	"%s CurrPic.state = HEVC_PIC_EMPTY, return HEVC_DEC_" )
	ASCII(.ascii	"NORMAL\012\000" )
	.space	1
.LC443:
	ASCII(.ascii	"%s, REPORT_IFRAME_ERR\012\000" )
	.space	1
.LC444:
	ASCII(.ascii	"Discard cur pic, ErrLevel(%d) > OutErrThr(%d)\012\000" )
	.space	1
.LC445:
	ASCII(.ascii	"%s call HEVC_IModeProcess Failed\012\000" )
	.space	2
.LC446:
	ASCII(.ascii	"HEVC_StorePicInDpb return(%d) from L%d\012\000" )
.LC447:
	ASCII(.ascii	"%s call HEVC_SimpleDPBProcess Failed\012\000" )
	.space	2
.LC448:
	ASCII(.ascii	"%s call HEVC_DecOrderProcess Failed\012\000" )
	.space	3
.LC449:
	ASCII(.ascii	"%s call HEVC_DispOrderProcess Failed\012\000" )
	.space	2
.LC450:
	ASCII(.ascii	"%s return HEVC_DEC_ERR\012\000" )
.LC451:
	ASCII(.ascii	"No frame store for lost pic.\012\000" )
	.space	2
.LC452:
	ASCII(.ascii	"DPB ERROR: Can not get ref_fs!\012\000" )
.LC453:
	ASCII(.ascii	"DPB no suited fs for lost pic.\012\000" )
.LC454:
	ASCII(.ascii	"Take poc(%d) to creat lost poc(%d).\012\000" )
	.space	3
.LC455:
	ASCII(.ascii	"DPB ERROR: Ref DecodeFs = NULL, ClearDPB!\012\000" )
	.space	1
.LC456:
	ASCII(.ascii	"ERROR: Can not new logic fs!\012\000" )
	.space	2
.LC457:
	ASCII(.ascii	"Lost pic insert in DPB Failed!\012\000" )
.LC458:
	ASCII(.ascii	"Ref frame(poc %d) lost.\012\000" )
	.space	3
.LC459:
	ASCII(.ascii	"s32OutErrThr = %d,drop poc %d because lost ref fram" )
	ASCII(.ascii	"e(pod %d)\012\000" )
	.space	2
.LC460:
	ASCII(.ascii	"DecVDM MaxBytesReceived exceed threshold!\012\000" )
	.space	1
.LC461:
	ASCII(.ascii	"DecVDM no slice and needn't start VDM\012\000" )
	.space	1
.LC462:
	ASCII(.ascii	"IPBDecMode Changed (%d -> %d)\012\000" )
	.space	1
.LC463:
	ASCII(.ascii	"Discard this B(poc=%d) before P, is_ref_idc=%d.\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC464:
	ASCII(.ascii	"VDM start, TotalPicNum=%d.\012\000" )
.LC465:
	ASCII(.ascii	"%s no correct slice in the pic\012\000" )
.LC466:
	ASCII(.ascii	"metadatasize is too large:%d at line:%d\012\000" )
	.space	3
.LC467:
	ASCII(.ascii	"%s:%d Metadata map failed\012\000" )
	.space	1
.LC468:
	ASCII(.ascii	"%s:%d Metadata unmap failed\012\000" )
	.space	3
.LC469:
	ASCII(.ascii	"*****[%s][%d],BL Codec can only dec BL stream!!****" )
	ASCII(.ascii	"*\012\000" )
	.space	2
.LC470:
	ASCII(.ascii	"*****[%s][%d],EL Codec can only dec EL stream in DV" )
	ASCII(.ascii	"_DUAL_VES_IMP stream!!*****\012\000" )
.LC471:
	ASCII(.ascii	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC472:
	ASCII(.ascii	"%s call HEVC_FlushOutputFrmFromDPB failed\012\000" )
	.space	1
.LC473:
	ASCII(.ascii	"%s call HEVC_EmptyFrmFromDPB failed\012\000" )
	.space	3
.LC474:
	ASCII(.ascii	"Meet CRA frame, force output remain frame, CurPoc %" )
	ASCII(.ascii	"d, LastPoc %d\012\000" )
	.space	2
.LC475:
	ASCII(.ascii	"Init pic err, exit\012\000" )
.LC476:
	ASCII(.ascii	"HEVC_WritePicMsg failed!\012\000" )
	.space	2
.LC477:
	ASCII(.ascii	"Start Reason: SliceParaNum= %d\012\000" )
.LC478:
	ASCII(.ascii	"Too many slice , err!\012\000" )
	.space	1
.LC479:
	ASCII(.ascii	"Cur pic not init yet, discard this slice!\012\000" )
	.space	1
.LC480:
	ASCII(.ascii	"Dec List error, ret=%d\012\000" )
.LC481:
	ASCII(.ascii	"Ref List is Wrong!\012\000" )
.LC482:
	ASCII(.ascii	"HEVC_WriteSliceMsg err.\012\000" )
	.space	3
.LC483:
	ASCII(.ascii	"VPS decode error.\012\000" )
	.space	1
.LC484:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC485:
	ASCII(.ascii	"PPS decode error.\012\000" )
	.space	1
.LC486:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC487:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC488:
	ASCII(.ascii	"HEVC_DecSliceSegmentHeader dec err\012\000" )
.LC489:
	ASCII(.ascii	"CurBitsLen = %d, MinBitsLen = %d\012\000" )
	.space	2
.LC490:
	ASCII(.ascii	"%s last frame fs unrelease, fix it!\012\000" )
	.space	3
.LC491:
	ASCII(.ascii	"CtbNumOneFrame=%d, SedEnd0=%d\012\000" )
	.space	1
.LC492:
	ASCII(.ascii	"%s: Get context addr failed!\012\000" )
	.space	2
.LC493:
	ASCII(.ascii	"%s FATAL: MemOffset %d > ContextMemSize %d.\012\000" )
	.space	3
.LC494:
	ASCII(.ascii	"%s: VCTRL_GetChanIDByCtx() return -1!\012\000" )
	.space	1
.LC495:
	ASCII(.ascii	"Fs leak, clear dpb fs not in vo queue.\012\000" )
.LC496:
	ASCII(.ascii	"No frame store available!\012\000" )
	.space	1
.LC497:
	ASCII(.ascii	"%s ReadImgNum = %d, NewImgNum = %d, FrameStore leak" )
	ASCII(.ascii	", ClearAll!\012\000" )
.LC498:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pPacket!\012\000" )
	.space	1
.LC499:
	ASCII(.ascii	"HevcCtx not init!\012\000" )
	.space	1
.LC500:
	ASCII(.ascii	"HEVCDEC_DecodePacket NULL == pHevcCtx->pCurrNal!\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC501:
	ASCII(.ascii	"nal_layer_id out %d of range[0,1].\012\000" )
.LC502:
	ASCII(.ascii	"IsSizeChanged = %d,old w/h = %d/%d,new w/h = %d/%d\012" )
	ASCII(.ascii	"\000" )
.LC503:
	ASCII(.ascii	"HEVC_InquireSliceProperty error.\012\000" )
	.space	2
.LC504:
	ASCII(.ascii	"HEVC_DecOneNal ERR\012\000" )
.LC505:
	ASCII(.ascii	"HEVC_StorePicInDPB failed, ret = %d\012\000" )
	.space	3
.LC506:
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
	.size	s_TmpParam, 12660
s_TmpParam:
	.space	12660
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
