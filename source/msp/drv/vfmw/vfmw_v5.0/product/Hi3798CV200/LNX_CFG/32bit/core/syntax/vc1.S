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
	.file	"vc1.c"
	.text
	.align	2
	.type	VC1_Vfmw_GenerateIntensityMap, %function
VC1_Vfmw_GenerateIntensityMap:
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
	cmp	r2, #31
	subgt	r2, r2, #64
	cmp	r1, #0
	addne	ip, r1, #32
	moveq	r2, r2, asl #7
	mvneq	ip, #63
	rsbeq	r2, r2, #16320
	movne	r2, r2, asl #6
	cmp	r3, #0
	bne	.L13
	add	r3, r2, #32
	sub	r2, r0, #1
	add	r0, r0, #255
.L5:
	usat	r1, #8, r3, asr #6
	strb	r1, [r2, #1]!
	cmp	r2, r0
	add	r3, r3, ip
	bne	.L5
	ldmfd	sp, {fp, sp, pc}
.L13:
	mov	r3, ip, asl #7
	sub	r2, r0, #1
	rsb	r3, r3, #8192
	add	r0, r0, #255
	add	r3, r3, #32
.L6:
	usat	r1, #8, r3, asr #6
	strb	r1, [r2, #1]!
	cmp	r2, r0
	add	r3, r3, ip
	bne	.L6
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_GenerateIntensityMap, .-VC1_Vfmw_GenerateIntensityMap
	.align	2
	.type	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5, %function
VC1_Vfmw_UpdataLastPicRNDCTRL.part.5:
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
	add	r2, r0, #8192
	ldrb	r3, [r2, #2415]	@ zero_extendqisi2
	tst	r3, #251
	moveq	r3, #1
	moveq	r1, r3
	beq	.L15
	cmp	r3, #1
	ldreqsb	r3, [r0, #10]
	ldrneb	r1, [r0, #10]	@ zero_extendqisi2
	clzeq	r3, r3
	moveq	r3, r3, lsr #5
	uxtbne	r3, r1
	uxtbeq	r1, r3
.L15:
	strb	r1, [r0, #10]
	strb	r3, [r2, #2434]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5, .-VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
	.align	2
	.global	emp_print
	.type	emp_print, %function
emp_print:
	UNWIND(.fnstart)
	@ args = 4, pretend = 12, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 1
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r1, r2, r3}
	UNWIND(.save {r1, r2, r3})
	stmfd	sp!, {fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {fp, ip, lr})
	UNWIND(.setfp fp, ip, #-16)
	sub	fp, ip, #16
	mov	r0, #0
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	emp_print, .-emp_print
	.align	2
	.global	AbandonBitsLenthNoUse
	.type	AbandonBitsLenthNoUse, %function
AbandonBitsLenthNoUse:
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
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r2, r3
	bne	.L31
.L23:
	ldrb	r3, [r0, #-1]!	@ zero_extendqisi2
	add	r2, r2, #8
	cmp	r3, #0
	beq	.L23
	add	r0, r2, #1
.L24:
	tst	r3, #1
	bne	.L32
.L25:
	mov	r3, r3, lsr #1
	add	r2, r2, #1
	tst	r3, #1
	beq	.L25
	add	r0, r2, #1
	ldmfd	sp, {fp, sp, pc}
.L31:
	mov	r0, #1
	mov	r2, #0
	b	.L24
.L32:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AbandonBitsLenthNoUse, .-AbandonBitsLenthNoUse
	.align	2
	.global	VC1DEC_Init
	.type	VC1DEC_Init, %function
VC1DEC_Init:
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
	add	r4, r0, #49152
	ldr	r3, .L37
	mov	r8, r1
	movw	r2, #49632
	ldr	r9, [r4, #464]
	mov	r1, #0
	ldr	r3, [r3, #48]
	mov	r6, r1
	mov	r7, r0
	blx	r3
	add	r0, r4, #120
	str	r9, [r4, #464]
	bl	ResetVoQueue
	add	r2, r7, #12288
	ldr	r3, [r8, #32]
	mov	r5, #1
	str	r8, [r7]
	mov	r0, r7
	strb	r5, [r2, #457]
	add	r3, r3, #255
	ldr	r1, [r8, #8]
	bic	r3, r3, #255
	add	ip, r3, #2048
	str	r3, [r4, #48]
	str	ip, [r4, #52]
	add	ip, r3, #4096
	str	r1, [r4, #76]
	add	r1, r3, #6144
	str	ip, [r4, #56]
	add	ip, r3, #8192
	str	r1, [r4, #60]
	add	r1, r3, #10240
	str	ip, [r4, #64]
	add	r3, r3, #12288
	str	r1, [r4, #68]
	str	r3, [r4, #72]
	strb	r5, [r2, #458]
	str	r6, [r4, #8]
	str	r6, [r4, #12]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #472]
	beq	.L36
	ldr	r1, .L37+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L36:
	mov	r0, r6
	ldr	r1, .L37+8
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L38:
	.align	2
.L37:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC14
	.word	.LC13
	UNWIND(.fnend)
	.size	VC1DEC_Init, .-VC1DEC_Init
	.align	2
	.global	Vc1SMPSeqHdr
	.type	Vc1SMPSeqHdr, %function
Vc1SMPSeqHdr:
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
	mov	r4, r2
	mov	r2, r1, asl #3
	mov	r1, r0
	sub	r0, fp, #52
	bl	BsInit
	mov	r1, #8
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #8
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #16
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #24
	sub	r0, fp, #52
	str	r5, [r4, #8]
	bl	BsGet
	mov	r1, #8
	mov	r5, r0
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #8
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #8
	add	r5, r5, r0, lsl #16
	sub	r0, fp, #52
	bl	BsGet
	ldr	r3, [r4, #8]
	cmp	r3, #8192
	add	r0, r5, r0, lsl #24
	str	r0, [r4, #12]
	bgt	.L43
	cmp	r0, #8192
	bgt	.L44
	cmp	r3, #31
	ble	.L43
	cmp	r0, #31
	ble	.L44
	mov	r1, #2
	sub	r0, fp, #52
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #16]
	cmp	r0, #1
	bhi	.L46
	mov	r1, #2
	sub	r0, fp, #52
	bl	BsGet
	cmp	r0, #0
	bne	.L46
	mov	r1, #3
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #5
	strb	r0, [r4, #17]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #18]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #19]
	sub	r0, fp, #52
	bl	BsGet
	cmp	r0, #0
	bne	.L46
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #20]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #21]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #22]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #23]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #24]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #25]
	sub	r0, fp, #52
	bl	BsGet
	subs	r5, r0, #0
	bne	.L46
	mov	r1, #1
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #26]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #27]
	sub	r0, fp, #52
	bl	BsGet
	ldrb	r3, [r4, #16]	@ zero_extendqisi2
	mov	r1, #3
	cmp	r3, #0
	strb	r0, [r4, #28]
	sub	r0, fp, #52
	streqb	r5, [r4, #28]
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #29]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #30]
	sub	r0, fp, #52
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #31]
	sub	r0, fp, #52
	bl	BsGet
	sub	r0, fp, #52
	mov	r1, #32
	bl	BsGet
	cmp	r0, #0
	bne	.L52
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L52:
	ldr	r1, .L53
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L46:
	ldr	r3, .L53+4
.L51:
	ldr	r2, .L53+8
	mov	r0, #0
	ldr	r1, .L53+12
	mvn	r5, #0
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L44:
	ldr	r3, .L53+16
	b	.L51
.L43:
	ldr	r3, .L53+20
	b	.L51
.L54:
	.align	2
.L53:
	.word	.LC19
	.word	.LC18
	.word	.LANCHOR0
	.word	.LC16
	.word	.LC17
	.word	.LC15
	UNWIND(.fnend)
	.size	Vc1SMPSeqHdr, .-Vc1SMPSeqHdr
	.align	2
	.global	VC1_SetImgFormat
	.type	VC1_SetImgFormat, %function
VC1_SetImgFormat:
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
	add	r5, r0, #32768
	add	r8, r0, #49152
	mov	r6, r0
	add	r7, r0, #12288
	ldr	r1, [r5, #4044]
	ldr	r0, [r8, #472]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r9, #1
	str	r9, [r4, #296]
	ldrb	r3, [r7, #451]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L64
	ldr	ip, .L65
	mov	r3, #0
	mov	r1, r3
	strb	r3, [r4, #284]
	mov	r2, #4
	add	r0, r4, #64
	ldr	r3, [ip, #48]
	blx	r3
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	orr	r3, r3, #12
	bfi	r3, r9, #4, #2
	strb	r3, [r4, #65]
.L59:
	ldrb	r2, [r8, #81]	@ zero_extendqisi2
	mov	r1, #0
	ldrb	r3, [r4, #66]	@ zero_extendqisi2
	mov	r0, r4
	bfi	r3, r2, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r8, #84]
	str	r3, [r4, #120]
	ldr	r3, [r5, #3988]
	str	r3, [r4, #72]
	ldr	r3, [r5, #3984]
	str	r3, [r4, #68]
	bl	SetAspectRatio
	ldr	r8, [r7, #244]
	ldr	r1, [r4, #36]
	add	lr, r4, #512
	ldr	r3, [r4, #112]
	mov	r2, #8
	add	r0, r1, r8
	str	r0, [r4, #40]
	ldrd	r6, [lr, #-8]
	add	r9, r0, r3
	add	r3, r1, r3
	mov	ip, #1
	adds	r6, r6, r8
	adc	r7, r7, #0
	strd	r6, [lr]
	ldr	lr, [r4, #68]
	str	r0, [r4, #24]
	str	r3, [r4, #28]
	add	r0, lr, #508
	str	r9, [r4, #32]
	add	r0, r0, #3
	str	r1, [r4, #20]
	bic	r3, r0, #508
	ldr	r1, [r5, #3988]
	bic	r3, r3, #3
	mov	r3, r3, lsr #5
	str	r1, [r4, #80]
	ldr	r1, [r5, #3984]
	str	r3, [r4, #136]
	strb	ip, [r4, #291]
	str	r1, [r4, #76]
	strb	ip, [r4, #289]
	str	r2, [r4, #300]
	str	r2, [r4, #308]
	str	r2, [r4, #304]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L64:
	mov	r3, #4
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	strb	r3, [r4, #284]
	mov	r1, #1
	ldrb	r3, [r6, #16]	@ zero_extendqisi2
	ubfx	r2, r2, #2, #2
	add	r3, r3, r9
	orr	r3, r3, r2
	cmp	r3, #3
	andls	r2, r3, #3
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	movhi	r2, #0
	bfi	r3, r2, #2, #2
	bfi	r3, r1, #0, #2
	bfi	r3, r1, #4, #2
	strb	r3, [r4, #65]
	b	.L59
.L66:
	.align	2
.L65:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_SetImgFormat, .-VC1_SetImgFormat
	.align	2
	.global	VC1DEC_Destroy
	.type	VC1DEC_Destroy, %function
VC1DEC_Destroy:
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
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1DEC_Destroy, .-VC1DEC_Destroy
	.align	2
	.global	VC1DEC_RecycleImage
	.type	VC1DEC_RecycleImage, %function
VC1DEC_RecycleImage:
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
	cmp	r0, #0
	mov	r5, r1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r4, r0, #49152
	mov	r2, #0
	ldr	r0, [r4, #472]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #472]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L71
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #472]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #472]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L71:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1DEC_RecycleImage, .-VC1DEC_RecycleImage
	.align	2
	.global	VC1DEC_GetRemainImg
	.type	VC1DEC_GetRemainImg, %function
VC1DEC_GetRemainImg:
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
	add	r5, r0, #32768
	mov	r4, r0
	add	r9, r0, #12288
	ldr	r3, [r5, #3956]
	cmp	r3, #0
	beq	.L79
	ldr	r3, [r0]
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L90
	add	r6, r0, #49152
	ldr	r1, [r5, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	moveq	r5, r6
	addeq	r5, r5, #120
	beq	.L78
	ldr	r1, [r5, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L88
.L90:
	add	r5, r4, #49152
	add	r5, r5, #120
.L78:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	GetVoLastImageID
.L88:
	add	r10, r8, #544
	add	r7, r8, #560
	mov	r0, r4
	bl	VC1_SetImgFormat
	mov	r2, #1
	mov	r0, #0
	str	r2, [r8, #180]
	mov	r1, #0
	strd	r0, [r10]
	strd	r0, [r7, #-8]
	ldr	r1, [r8, #148]
	ldr	r0, [r6, #472]
	bl	FSP_SetDisplay
	ldr	r3, [r5, #3956]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L91
.L75:
	add	r5, r4, #49152
	ldr	r0, [r6, #472]
	add	r5, r5, #120
	str	r8, [sp]
	mov	r2, r4
	mov	r1, #1
	mov	r3, r5
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L76
	ldr	r1, [r8, #148]
	mov	r0, r4
	bl	VC1DEC_RecycleImage
	ldr	r1, [r8, #544]
	ldr	r0, [r6, #472]
	mov	r8, #0
	bl	FreeUsdByDec
	mov	r9, #0
	strd	r8, [r10]
	ldr	r0, [r6, #472]
	ldr	r1, [r7, #-8]
	bl	FreeUsdByDec
	strd	r8, [r7, #-8]
	b	.L78
.L76:
	ldr	r3, [r8, #152]
	cmp	r3, #100
	bhi	.L78
	ldr	r3, [r8, #68]
	cmp	r3, #31
	bls	.L78
	ldr	r3, [r8, #72]
	cmp	r3, #31
	movhi	r0, #0
	bls	.L78
.L89:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L91:
	strb	r2, [r3, #1]
	mov	r1, #0
	ldr	r2, [r5, #3956]
	mov	r3, #3
	strb	r1, [r2]
	strb	r3, [r9, #449]
	b	.L75
.L79:
	mvn	r0, #0
	b	.L89
	UNWIND(.fnend)
	.size	VC1DEC_GetRemainImg, .-VC1DEC_GetRemainImg
	.align	2
	.global	VC1_ArrangeVahbMem
	.type	VC1_ArrangeVahbMem, %function
VC1_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #32)
	sub	sp, sp, #32
	mov	r5, r1
	sub	r1, r1, #32
	movw	r3, #8160
	cmp	r1, r3
	mov	r7, r0
	mov	r6, r2
	bhi	.L93
	sub	r2, r2, #32
	cmp	r2, r3
	bhi	.L93
	add	ip, r0, #28160
	mov	lr, #0
	add	ip, ip, #200
	mov	r4, lr
.L96:
	str	lr, [ip, #-484]
	add	lr, lr, #1
	cmp	lr, #5
	strb	r4, [ip, #-1671]
	strb	r4, [ip, #-1672]
	add	ip, ip, #1664
	add	ip, ip, #8
	bne	.L96
	ldr	r3, [r7]
	ldr	r4, [r3, #724]
	ldr	r2, [r3, #28]
	cmp	r4, #0
	bne	.L97
	cmp	r2, #25
	beq	.L121
.L117:
	mov	r4, lr
	mov	r8, #3
	mov	r9, #2
.L98:
	ldr	r3, .L124
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #56
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r7]
	str	r5, [fp, #-52]
	str	r6, [fp, #-48]
	ldr	r3, [r3, #28]
	str	r5, [fp, #-44]
	cmp	r3, #24
	str	r6, [fp, #-40]
	beq	.L108
	uxtb	r3, r9
	strb	r8, [fp, #-55]
	strb	r4, [fp, #-54]
.L113:
	add	r5, r7, #49152
	sub	r1, fp, #56
	strb	r3, [fp, #-53]
	ldr	r0, [r5, #472]
	bl	FSP_ConfigInstance
	subs	r4, r0, #0
	bne	.L109
	ldr	r1, [r7]
	sub	r3, fp, #60
	ldr	r0, [r5, #472]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L122
	cmp	r0, #0
	bne	.L111
.L115:
	mov	r4, #1
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L93:
	mov	r3, r6
	mov	r2, r5
	ldr	r1, .L124+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r4, #0
.L120:
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L97:
	cmp	r2, #25
	bne	.L117
	ldr	r2, [r3, #684]
	ldr	r1, [r3, #688]
	cmp	r5, r2
	bhi	.L105
	cmp	r6, r1
	bhi	.L105
	ldr	r1, [r3, #712]
	ldr	r2, [r3, #708]
	cmp	r1, #0
	add	r8, r2, #2
	moveq	r9, #1
	bne	.L123
.L107:
	ldrb	r4, [r3, #732]	@ zero_extendqisi2
	b	.L98
.L109:
	ldr	r1, .L124+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r4, #0
	mov	r0, r4
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L121:
	ldr	r2, [r3, #684]
	cmp	r5, r2
	ldrhi	r0, [r3, #688]
	bhi	.L100
	ldr	r1, [r3, #688]
	cmp	r6, r1
	mov	r0, r1
	bhi	.L100
	add	r0, r7, #12288
	ldrb	r0, [r0, #448]	@ zero_extendqisi2
	tst	r0, #8
	bne	.L115
	ldr	ip, [r3, #712]
	ldr	r0, [r3, #708]
	cmp	ip, #0
	add	r8, r0, #2
	moveq	r9, #1
	beq	.L103
	add	r9, r0, #1
	cmp	r9, #17
	movcs	r9, #17
.L103:
	ldrb	r4, [r3, #732]	@ zero_extendqisi2
	mov	r6, r1
	mov	r5, r2
	b	.L98
.L108:
	mov	r3, #1
	strb	r4, [fp, #-54]
	strb	r3, [fp, #-55]
	b	.L113
.L105:
	str	r1, [sp, #4]
	mov	r3, r6
	str	r2, [sp]
	mov	r0, #0
	mov	r2, r5
	ldr	r1, .L124+12
	bl	dprint_vfmw
	mov	r4, #0
	b	.L120
.L122:
	add	r0, r5, #120
	bl	ResetVoQueue
.L111:
	ldr	r1, .L124+16
	mov	r0, #0
	bl	dprint_vfmw
	b	.L120
.L123:
	add	r9, r2, #1
	cmp	r9, #17
	movcs	r9, #17
	b	.L107
.L100:
	str	r0, [sp, #4]
	mov	r3, r6
	str	r2, [sp]
	mov	r0, #0
	mov	r2, r5
	ldr	r1, .L124+12
	bl	dprint_vfmw
	b	.L120
.L125:
	.align	2
.L124:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	.LC23
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	VC1_ArrangeVahbMem, .-VC1_ArrangeVahbMem
	.align	2
	.global	VC1_WritePicMsg
	.type	VC1_WritePicMsg, %function
VC1_WritePicMsg:
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
	add	r7, r0, #32768
	add	r5, r0, #49152
	mov	r6, r0
	mov	r4, r1
	add	r8, r0, #12288
	ldr	r1, [r7, #4044]
	ldr	r0, [r5, #472]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L149
	movw	r3, #3544
	ldrsb	r2, [r8, r3]
	add	r3, r6, #20480
	cmp	r2, #0
	bne	.L150
	strb	r2, [r4, #5]
	ldrb	r1, [r3, #2612]	@ zero_extendqisi2
	strb	r1, [r4, #4]
	ldrb	r1, [r3, #2863]	@ zero_extendqisi2
	cmp	r1, #4
	moveq	r1, #3
	strb	r1, [r4, #3]
	ldr	r1, [r5, #28]
	sub	r1, r1, #1
	strh	r1, [r4, #80]	@ movhi
	ldr	r1, [r5, #24]
	strb	r2, [r4, #8]
	sub	r1, r1, #1
	strh	r1, [r4, #78]	@ movhi
	ldrb	r1, [r3, #2615]	@ zero_extendqisi2
	strb	r2, [r4, #9]
	strb	r1, [r4, #6]
	ldrb	r1, [r8, #456]	@ zero_extendqisi2
	strb	r2, [r4, #10]
	strb	r2, [r4, #11]
	strb	r1, [r4, #7]
	ldrb	r1, [r3, #2618]	@ zero_extendqisi2
	strb	r1, [r4, #13]
	ldrb	r1, [r3, #2622]	@ zero_extendqisi2
	strb	r1, [r4, #14]
	ldrb	r1, [r3, #2882]	@ zero_extendqisi2
	strb	r1, [r4, #12]
	ldrb	r1, [r3, #2892]	@ zero_extendqisi2
	strb	r1, [r4, #18]
	ldrb	r1, [r3, #2867]	@ zero_extendqisi2
	strb	r1, [r4, #19]
	ldrb	r1, [r3, #2866]	@ zero_extendqisi2
	strb	r1, [r4, #17]
	ldr	r1, [r3, #2952]
	strb	r1, [r4, #16]
	ldrb	r1, [r3, #2626]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L141
	ldrb	r2, [r3, #2866]	@ zero_extendqisi2
	cmp	r2, #8
	movhi	r2, #0
	movls	r2, #1
	strb	r2, [r4, #20]
.L142:
	ldrb	r1, [r3, #2886]	@ zero_extendqisi2
	add	r2, r4, #12288
	strb	r1, [r4, #24]
	ldrb	r1, [r3, #2885]	@ zero_extendqisi2
	strb	r1, [r4, #23]
	ldrb	r1, [r3, #2620]	@ zero_extendqisi2
	strb	r1, [r4, #22]
	ldrb	r1, [r3, #2884]	@ zero_extendqisi2
	strb	r1, [r4, #25]
	ldr	r1, [r3, #2896]
	strb	r1, [r4, #26]
	ldrb	r1, [r3, #2887]	@ zero_extendqisi2
	strb	r1, [r4, #21]
	ldrb	r1, [r3, #2871]	@ zero_extendqisi2
	strb	r1, [r4, #27]
	ldrb	r1, [r3, #2872]	@ zero_extendqisi2
	strb	r1, [r4, #28]
	ldr	r1, [r7, #3956]
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #30]
	ldr	r1, [r7, #3952]
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #29]
	ldrb	r1, [r3, #2869]	@ zero_extendqisi2
	strb	r1, [r4, #31]
	ldrb	r1, [r3, #2991]	@ zero_extendqisi2
	strb	r1, [r4, #32]
	ldrb	r1, [r3, #2881]	@ zero_extendqisi2
	strb	r1, [r4, #35]
	ldrb	r1, [r3, #2621]	@ zero_extendqisi2
	strb	r1, [r4, #36]
	ldrb	r1, [r3, #2877]	@ zero_extendqisi2
	strb	r1, [r4, #37]
	ldrb	r1, [r3, #2879]	@ zero_extendqisi2
	strb	r1, [r4, #38]
	ldrb	r1, [r3, #2880]	@ zero_extendqisi2
	strb	r1, [r4, #39]
	ldrb	r1, [r3, #2878]	@ zero_extendqisi2
	strb	r1, [r4, #40]
	ldr	r1, [r3, #2944]
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #42]
	ldr	r1, [r3, #2940]
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #43]
	ldr	r1, [r3, #2948]
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #45]
	ldrb	r1, [r3, #2864]	@ zero_extendqisi2
	strb	r1, [r4, #50]
	ldrb	r1, [r3, #2876]	@ zero_extendqisi2
	strb	r1, [r4, #49]
	ldrb	r1, [r3, #2875]	@ zero_extendqisi2
	strb	r1, [r4, #48]
	ldr	r1, [r3, #2956]
	str	r1, [r2, #84]
	ldrb	r1, [r3, #2624]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L151
	mov	r1, #0
	mov	ip, r1
	mov	r9, r1
	mov	lr, r1
.L145:
	strb	lr, [r4, #59]
	strb	r9, [r4, #60]
	strb	ip, [r4, #61]
	str	r1, [r0, #352]
	ldrb	r3, [r3, #2612]	@ zero_extendqisi2
	strb	r3, [r0, #330]
.L139:
	ldr	r3, [r7, #4052]
	add	r6, r6, #12736
	ldr	r1, .L155
	add	r6, r6, #13
	strh	r3, [r4, #72]	@ movhi
	ldr	r3, [r7, #3984]
	strh	r3, [r4, #74]	@ movhi
	ldr	r3, [r7, #3988]
	strh	r3, [r4, #76]	@ movhi
	ldrb	r3, [r8, #459]	@ zero_extendqisi2
	strb	r3, [r4, #63]
	ldrb	r3, [r8, #460]	@ zero_extendqisi2
	strb	r3, [r4, #62]
	ldr	r0, [r7, #3968]
	adds	r3, r0, #127
	addmi	r3, r0, #254
	mov	r3, r3, asr #7
	mov	r3, r3, asl #4
	str	r3, [r2, #116]
	ldr	r3, [r5, #48]
	str	r3, [r2, #120]
	ldr	r3, [r5, #52]
	str	r3, [r2, #124]
	ldr	r3, [r5, #56]
	str	r3, [r2, #128]
	ldr	r3, [r5, #60]
	str	r3, [r2, #132]
	ldr	r3, [r5, #64]
	str	r3, [r2, #136]
	ldr	r3, [r5, #68]
	str	r3, [r2, #140]
	ldr	r3, [r5, #72]
	str	r3, [r2, #144]
	str	r6, [r4, #64]
	ldr	r2, [r5, #472]
	ldrh	r3, [r4, #78]
	ldr	r2, [r1, r2, asl #2]
	add	r3, r3, #1
	str	r3, [r2, #1436]
	ldr	r3, [r5, #472]
	ldr	r2, [r1, r3, asl #2]
	ldrh	r3, [r4, #80]
	add	r3, r3, #1
	str	r3, [r2, #1440]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L150:
	ldr	r2, [r3, #3004]
	movw	ip, #1672
	strb	r2, [r4, #5]
	ldrb	r2, [r3, #2628]	@ zero_extendqisi2
	strb	r2, [r4, #4]
	ldrb	r2, [r3, #2961]	@ zero_extendqisi2
	cmp	r2, #4
	moveq	r2, #3
	strb	r2, [r4, #3]
	ldr	r2, [r3, #3004]
	cmp	r2, #3
	ldr	r2, [r5, #28]
	addeq	r2, r2, #1
	addeq	r2, r2, r2, lsr #31
	moveq	r2, r2, asr #1
	sub	r2, r2, #1
	strh	r2, [r4, #80]	@ movhi
	ldr	r1, [r5, #24]
	sub	r1, r1, #1
	strh	r1, [r4, #78]	@ movhi
	ldrb	r2, [r3, #3001]	@ zero_extendqisi2
	strb	r2, [r4, #8]
	ldrb	r2, [r3, #2804]	@ zero_extendqisi2
	strb	r2, [r4, #6]
	ldrb	r2, [r3, #2992]	@ zero_extendqisi2
	strb	r2, [r4, #9]
	ldrb	r2, [r8, #456]	@ zero_extendqisi2
	strb	r2, [r4, #7]
	ldr	r1, [r7, #4008]
	mla	r1, ip, r1, r8
	add	r1, r1, #15424
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	strb	r2, [r4, #10]
	ldr	r2, [r7, #4024]
	mla	r2, ip, r2, r8
	add	r2, r2, #15424
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	strb	r2, [r4, #11]
	ldrb	r2, [r3, #2990]	@ zero_extendqisi2
	strb	r2, [r4, #15]
	ldrb	r2, [r3, #2805]	@ zero_extendqisi2
	strb	r2, [r4, #13]
	ldrb	r2, [r3, #2809]	@ zero_extendqisi2
	strb	r2, [r4, #14]
	ldrb	r2, [r3, #2960]	@ zero_extendqisi2
	strb	r2, [r4, #12]
	ldrb	r2, [r3, #3128]	@ zero_extendqisi2
	strb	r2, [r4, #18]
	ldrb	r2, [r3, #2963]	@ zero_extendqisi2
	strb	r2, [r4, #19]
	ldrb	r2, [r3, #2970]	@ zero_extendqisi2
	strb	r2, [r4, #17]
	ldr	r2, [r3, #3076]
	strb	r2, [r4, #16]
	ldrb	r2, [r3, #2810]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L132
	ldrb	r2, [r3, #2970]	@ zero_extendqisi2
	cmp	r2, #8
	movhi	r2, #0
	movls	r2, #1
	strb	r2, [r4, #20]
.L133:
	ldrb	r1, [r3, #3122]	@ zero_extendqisi2
	add	r2, r4, #12288
	strb	r1, [r4, #24]
	ldrb	r1, [r3, #3121]	@ zero_extendqisi2
	strb	r1, [r4, #23]
	ldrb	r1, [r3, #2807]	@ zero_extendqisi2
	strb	r1, [r4, #22]
	ldrb	r1, [r3, #3120]	@ zero_extendqisi2
	strb	r1, [r4, #25]
	ldr	r1, [r3, #3132]
	strb	r1, [r4, #26]
	ldrb	r1, [r3, #3123]	@ zero_extendqisi2
	strb	r1, [r4, #21]
	ldrb	r1, [r3, #2974]	@ zero_extendqisi2
	strb	r1, [r4, #27]
	ldrb	r1, [r3, #2975]	@ zero_extendqisi2
	strb	r1, [r4, #28]
	ldrb	r1, [r3, #2993]	@ zero_extendqisi2
	strb	r1, [r4, #34]
	ldrb	r1, [r3, #2985]	@ zero_extendqisi2
	strb	r1, [r4, #33]
	ldrb	ip, [r3, #3001]	@ zero_extendqisi2
	ldr	r1, [r7, #3956]
	add	r1, r1, ip
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #30]
	ldr	r1, [r7, #3952]
	ldrb	ip, [r3, #3001]	@ zero_extendqisi2
	add	r1, r1, ip
	ldrb	r1, [r1, #1029]	@ zero_extendqisi2
	strb	r1, [r4, #29]
	ldrb	r1, [r3, #2973]	@ zero_extendqisi2
	strb	r1, [r4, #31]
	ldrb	r1, [r3, #2991]	@ zero_extendqisi2
	strb	r1, [r4, #32]
	ldrb	r1, [r3, #2984]	@ zero_extendqisi2
	strb	r1, [r4, #35]
	ldrb	r1, [r3, #2808]	@ zero_extendqisi2
	strb	r1, [r4, #36]
	ldrb	r1, [r3, #2980]	@ zero_extendqisi2
	strb	r1, [r4, #37]
	ldrb	r1, [r3, #2982]	@ zero_extendqisi2
	strb	r1, [r4, #38]
	ldrb	r1, [r3, #2983]	@ zero_extendqisi2
	strb	r1, [r4, #39]
	ldrb	r1, [r3, #2981]	@ zero_extendqisi2
	strb	r1, [r4, #40]
	ldrb	r1, [r3, #2997]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #46]
	ldrb	r1, [r3, #2995]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #42]
	ldrb	r1, [r3, #2999]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #44]
	ldrb	r1, [r3, #3000]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #41]
	ldrb	r1, [r3, #2994]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #43]
	ldrb	r1, [r3, #2998]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #47]
	ldrb	r1, [r3, #2996]	@ zero_extendqisi2
	clz	r1, r1
	mov	r1, r1, lsr #5
	strb	r1, [r4, #45]
	ldrb	r1, [r3, #2962]	@ zero_extendqisi2
	strb	r1, [r4, #50]
	ldrb	r1, [r3, #2979]	@ zero_extendqisi2
	strb	r1, [r4, #49]
	ldrb	r1, [r3, #2978]	@ zero_extendqisi2
	strb	r1, [r4, #48]
	ldrb	r1, [r3, #2989]	@ zero_extendqisi2
	strb	r1, [r4, #53]
	ldrb	r1, [r3, #2986]	@ zero_extendqisi2
	strb	r1, [r4, #54]
	ldrb	r1, [r3, #2987]	@ zero_extendqisi2
	strb	r1, [r4, #51]
	ldrb	r1, [r3, #2988]	@ zero_extendqisi2
	strb	r1, [r4, #52]
	ldr	r1, [r3, #3108]
	str	r1, [r2, #84]
	ldr	r1, [r5]
	str	r1, [r2, #88]
	ldr	r1, [r5, #4]
	str	r1, [r2, #92]
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r4, #55]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r4, #56]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r4, #57]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r4, #58]
	ldr	r1, [r3, #3004]
	cmp	r1, #3
	beq	.L152
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r0, #325]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r0, #326]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r0, #327]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r0, #328]
.L138:
	ldrb	r3, [r3, #2628]	@ zero_extendqisi2
	strb	r3, [r0, #330]
	ldrb	r3, [r8, #459]	@ zero_extendqisi2
	strb	r3, [r4, #63]
	b	.L139
.L141:
	cmp	r1, #1
	beq	.L153
	cmp	r1, #2
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L142
.L132:
	cmp	r2, #1
	beq	.L154
	cmp	r2, #2
	moveq	r2, #0
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L133
.L154:
	ldrb	r2, [r3, #2971]	@ zero_extendqisi2
	adds	r2, r2, #0
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L133
.L153:
	ldrb	r2, [r3, #2868]	@ zero_extendqisi2
	adds	r2, r2, #0
	movne	r2, #1
	strb	r2, [r4, #20]
	b	.L142
.L152:
	ldrb	r1, [r3, #3001]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L137
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r0, #325]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r0, #326]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r0, #327]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r0, #328]
	ldrb	r1, [r3, #3001]	@ zero_extendqisi2
.L137:
	cmp	r1, #1
	bne	.L138
	ldrb	r1, [r3, #2813]	@ zero_extendqisi2
	strb	r1, [r0, #320]
	ldrb	r1, [r3, #2814]	@ zero_extendqisi2
	strb	r1, [r0, #321]
	ldrb	r1, [r3, #2815]	@ zero_extendqisi2
	strb	r1, [r0, #322]
	ldrb	r1, [r3, #2816]	@ zero_extendqisi2
	strb	r1, [r0, #323]
	b	.L138
.L151:
	ldr	ip, [r7, #4008]
	movw	r9, #1672
	ldr	r1, [r7, #4024]
	ldrb	lr, [r3, #2863]	@ zero_extendqisi2
	mla	ip, r9, ip, r8
	sub	lr, lr, #2
	mla	r1, r9, r1, r8
	tst	lr, #253
	add	ip, ip, #14400
	ldrneb	lr, [r3, #2862]	@ zero_extendqisi2
	add	r1, r1, #14400
	ldrb	r9, [ip, #2]	@ zero_extendqisi2
	ldrb	ip, [r1, #2]	@ zero_extendqisi2
	movne	r1, lr
	moveq	r1, ip
	moveq	lr, ip
	b	.L145
.L149:
	movw	r2, #1032
	ldr	r1, .L155+4
	mov	r0, #22
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L156:
	.align	2
.L155:
	.word	s_pstVfmwChan
	.word	.LC24
	UNWIND(.fnend)
	.size	VC1_WritePicMsg, .-VC1_WritePicMsg
	.align	2
	.global	VC1_WriteSliceMsg
	.type	VC1_WriteSliceMsg, %function
VC1_WriteSliceMsg:
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
	add	r3, r0, #20480
	mov	r2, r1
	ldr	ip, .L158
	add	r1, r0, #24064
	ldr	lr, [r3, #3604]
	add	r0, r2, #84
	add	r1, r1, #24
	ldr	ip, [ip, #52]
	strb	lr, [r2, #70]
	ldr	r3, [r3, #3604]
	mov	r2, r3, asl #6
	sub	r2, r2, r3, asl #4
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L159:
	.align	2
.L158:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_WriteSliceMsg, .-VC1_WriteSliceMsg
	.align	2
	.global	VC1_CfgVDH
	.type	VC1_CfgVDH, %function
VC1_CfgVDH:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L161
	add	r3, r0, #8192
	ldr	r3, [r3, #2556]
	cmp	r3, #3
	beq	.L166
.L161:
	add	r3, r0, #32768
	add	r6, r1, #12288
	ldr	r3, [r3, #3680]
	sub	r3, r3, #1
	str	r3, [r6, #164]
.L162:
	add	r5, r0, #20480
	ldr	r3, [r6, #260]
	mov	ip, #0
	movw	r4, #1672
	ldr	r2, [r5, #3544]
	and	lr, r3, #1
	cmp	r2, ip
	add	r3, r2, #63
	movlt	r2, r3
	mov	r2, r2, asr #6
	mov	r2, r2, asl #4
	add	r3, r2, #536870913
	add	r3, r3, #81920
	orr	r3, r3, lr, asl #30
	str	r3, [r6, #168]
	ldr	lr, [r5, #3576]
	ldr	r3, [r5, #3560]
	ldr	r2, [r5, #3504]
	mla	lr, r4, lr, r0
	mla	r0, r4, r3, r0
	ldr	r2, [r2, #1092]
	add	r3, lr, #15040
	and	r2, r2, #3
	ldr	r3, [r3, #4]
	add	r0, r0, #15040
	mov	r2, r2, asl #4
	ldr	r0, [r0, #4]
	and	r3, r3, #3
	strb	ip, [r1, #69]
	orr	r3, r2, r3, asl #2
	and	r2, r0, #3
	orr	r3, r3, r2
	strb	r3, [r1, #68]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L166:
	add	r2, r0, #32768
	add	r6, r1, #12288
	ldr	r3, [r2, #3676]
	ldr	r2, [r2, #3672]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	mul	r3, r2, r3
	sub	r3, r3, #1
	str	r3, [r6, #164]
	b	.L162
	UNWIND(.fnend)
	.size	VC1_CfgVDH, .-VC1_CfgVDH
	.align	2
	.global	VC1_Vfmw_GenerateDecPara
	.type	VC1_Vfmw_GenerateDecPara, %function
VC1_Vfmw_GenerateDecPara:
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
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_GenerateDecPara, .-VC1_Vfmw_GenerateDecPara
	.align	2
	.global	VC1DEC_GetImageBuffer
	.type	VC1DEC_GetImageBuffer, %function
VC1DEC_GetImageBuffer:
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
	ldrb	r2, [r3, #451]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L179
.L169:
	add	r5, r4, #49152
	ldr	r0, [r5, #472]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L171
	ldr	r0, [r5, #472]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L180
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L179:
	ldrb	r3, [r3, #457]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L169
.L171:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L180:
	ldr	r0, [r5, #472]
	add	r1, r5, #120
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1DEC_GetImageBuffer, .-VC1DEC_GetImageBuffer
	.align	2
	.global	VC1_Vfmw_GetImageBuffer
	.type	VC1_Vfmw_GetImageBuffer, %function
VC1_Vfmw_GetImageBuffer:
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
	add	r6, r0, #49152
	add	r4, r0, #32768
	mov	r5, r0
	mov	r1, #1
	ldr	r0, [r6, #472]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #4044]
	blt	.L201
	add	r3, r5, #26624
	add	r3, r3, #64
	mov	r2, r3
	ldrh	r3, [r3]
	cmp	r3, #0
	beq	.L185
	add	r3, r5, #28160
	add	lr, r5, #34816
	add	r3, r3, #200
	add	lr, lr, #232
.L188:
	ldrh	ip, [r3]
	mov	r2, r3
	add	r3, r3, #1664
	cmp	ip, #0
	add	r3, r3, #8
	beq	.L185
	cmp	r3, lr
	bne	.L188
	mov	r1, r0
	mov	r2, #1
	ldr	r0, [r6, #472]
	bl	FSP_ClearLogicFs
	ldr	r1, .L202
	mov	r0, #1
	bl	dprint_vfmw
	add	r3, r5, #26624
	add	r5, r5, #34816
	add	r3, r3, #65
	add	r5, r5, #233
	mov	r2, #0
.L190:
	strb	r2, [r3]
	add	r3, r3, #1664
	strb	r2, [r3, #-1665]
	add	r3, r3, #8
	cmp	r3, r5
	bne	.L190
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L185:
	mov	r3, #0
	str	r2, [r4, #3952]
	mov	r1, #1
	strb	r1, [r2, #1]
.L187:
	ldr	r1, [r4, #3952]
	uxtb	r2, r3
	add	r1, r1, r3
	strb	r2, [r1, #3]
	ldr	r1, [r4, #3952]
	add	r1, r1, r3
	strb	r2, [r1, #259]
	ldr	r1, [r4, #3952]
	add	r1, r1, r3
	strb	r2, [r1, #515]
	ldr	r1, [r4, #3952]
	add	r1, r1, r3
	add	r3, r3, #1
	cmp	r3, #256
	strb	r2, [r1, #771]
	bne	.L187
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L201:
	ldr	r1, .L202+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L183
	ldr	r1, [r7, #544]
	add	r9, r7, #560
	ldr	r0, [r6, #472]
	add	r8, r7, #576
	bl	FreeUsdByDec
	ldr	r1, [r7, #552]
	ldr	r0, [r6, #472]
	add	r10, r7, #544
	bl	FreeUsdByDec
	ldr	r1, [r7, #560]
	ldr	r0, [r6, #472]
	bl	FreeUsdByDec
	ldr	r1, [r7, #568]
	ldr	r0, [r6, #472]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r10]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4036]
	ldr	r0, [r6, #472]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	str	r3, [r4, #4036]
	str	r3, [r4, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #4040]
	str	r0, [r4, #4036]
.L183:
	add	r1, r5, #49152
	mov	r5, #0
	add	r1, r1, #120
	str	r5, [r4, #4032]
	ldr	r0, [r6, #472]
	bl	FSP_ClearNotInVoQueue
	ldr	r1, .L202+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L203:
	.align	2
.L202:
	.word	.LC27
	.word	.LC25
	.word	.LC26
	UNWIND(.fnend)
	.size	VC1_Vfmw_GetImageBuffer, .-VC1_Vfmw_GetImageBuffer
	.align	2
	.global	VC1_Vfmw_MemMove
	.type	VC1_Vfmw_MemMove, %function
VC1_Vfmw_MemMove:
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
	add	r0, r0, #20480
	ldr	ip, .L205
	ldr	r3, [r0, #3524]
	ldr	r2, [r0, #3544]
	add	r3, r3, #1
	ldr	r1, [r0, #3508]
	ldr	r0, [r0, #3504]
	add	r3, r3, r3, lsr #31
	ldr	ip, [ip, #52]
	ldr	r1, [r1, #1544]
	mov	r3, r3, asr #1
	ldr	r0, [r0, #1544]
	mov	r3, r3, asl #5
	mul	r3, r2, r3
	add	r2, r3, r3, lsl #1
	mov	r2, r2, asr #1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L206:
	.align	2
.L205:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_MemMove, .-VC1_Vfmw_MemMove
	.align	2
	.global	VC1_Vfmw_BuildRefList
	.type	VC1_Vfmw_BuildRefList, %function
VC1_Vfmw_BuildRefList:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 536
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #540)
	sub	sp, sp, #540
	ldr	r6, .L282
	mov	r7, r0
	mov	r10, r1
	mov	r4, r2
	mov	r1, #0
	mov	r2, #256
	sub	r0, fp, #556
	mov	r5, r3
	bl	memset
	mov	r2, #256
	mov	r1, #0
	sub	r0, fp, #300
	bl	memset
	add	r0, r7, #23808
	ldr	r3, [r6, #48]
	mov	r2, #16
	mov	r1, #0
	add	r0, r0, #224
	blx	r3
	add	r0, r7, #23808
	ldr	r3, [r6, #48]
	add	r0, r0, #240
	mov	r2, #16
	mov	r1, #0
	blx	r3
	ldrsb	r3, [r7, #4]
	bics	r3, r3, #2
	bne	.L208
	cmp	r10, #1
	beq	.L269
	cmp	r10, #2
	addne	ip, r7, #20480
	beq	.L270
.L217:
	mov	r0, #1
	mov	r3, #0
	str	r3, [ip, #3572]
	str	r3, [ip, #3556]
.L251:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L208:
	add	r6, r7, #8192
	ldrb	r3, [r6, #2516]	@ zero_extendqisi2
	cmp	r3, #1
	ldrb	r3, [r6, #2553]	@ zero_extendqisi2
	beq	.L271
	cmp	r3, #0
	beq	.L272
.L227:
	add	ip, r7, #20480
	ldr	r3, [ip, #3512]
	ldr	r9, [r3, #1188]
	mov	r8, r9
.L226:
	cmp	r10, #1
	beq	.L273
.L228:
	cmp	r10, #2
	bne	.L217
	cmp	r4, #0
	mov	r2, #0
	mov	r3, #1
	str	r10, [ip, #3572]
	str	r10, [ip, #3556]
	strb	r2, [ip, #3552]
	strb	r3, [ip, #3553]
	beq	.L240
	cmp	r5, r2
	beq	.L274
.L240:
	ldr	r3, [ip, #3512]
	ldr	lr, [ip, #3504]
	ldr	r2, [r3, #1188]
.L267:
	ldr	r0, [ip, #3508]
	mov	r1, #1
	str	r2, [ip, #3560]
	mov	r3, #0
	strb	r1, [ip, #3569]
	strb	r3, [ip, #3568]
	ldr	r1, [r0, #1188]
	str	r1, [ip, #3576]
	ldr	r0, [r0, #1188]
	str	r0, [ip, #3580]
	ldr	r0, [r6, #2640]
	ldr	r8, [lr, #1188]
	cmp	r0, #1
	bls	.L275
	bics	r0, r0, #2
	beq	.L246
.L245:
	movw	ip, #1672
	mov	r3, r7
	mul	r8, ip, r8
	mul	r0, ip, r2
	mov	r2, #0
	mul	r1, ip, r1
	str	r2, [fp, #-572]
	add	r2, r8, #13952
	str	r2, [fp, #-568]
	add	r2, r8, #14208
	str	r2, [fp, #-560]
	ldr	r2, [fp, #-568]
	add	r10, r0, #13952
	add	r9, r0, #14208
	add	r5, r1, #13952
	add	r2, r2, #2
	str	r2, [fp, #-568]
	ldr	r2, [fp, #-560]
	add	r4, r1, #14208
	add	lr, r1, #14464
	add	ip, r1, #14720
	add	r1, r8, #14464
	add	r9, r9, #2
	add	r2, r2, #2
	add	r1, r1, #2
	add	r10, r10, #2
	str	r1, [fp, #-576]
	add	ip, ip, #2
	add	r7, r7, r10
	add	r8, r8, #14720
	str	r7, [fp, #-560]
	add	r7, r3, r9
	add	r9, r3, r2
	ldr	r2, [fp, #-576]
	add	r6, r0, #14464
	add	r8, r8, #2
	add	r1, r3, ip
	str	r8, [fp, #-580]
	add	r0, r0, #14720
	ldr	ip, [fp, #-568]
	add	r6, r6, #2
	add	r0, r0, #2
	add	r5, r5, #2
	add	r4, r4, #2
	add	lr, lr, #2
	add	r8, r3, r2
	ldr	r2, [fp, #-580]
	add	r6, r3, r6
	add	r0, r3, r0
	add	r5, r3, r5
	add	r4, r3, r4
	add	lr, r3, lr
	add	ip, r3, ip
	str	r7, [fp, #-564]
	add	r7, r3, r2
	mov	r2, #0
	str	r1, [fp, #-568]
.L247:
	ldr	r1, [fp, #-560]
	add	r2, r2, #1
	cmp	r2, #256
	add	r3, r3, #1
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-560]
	ldr	r1, [fp, #-564]
	strb	r10, [r3, #12]
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #268]
	ldrb	r10, [r6, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-564]
	ldr	r1, [fp, #-568]
	strb	r10, [r3, #524]
	ldrb	r10, [r0, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #780]
	ldrb	r10, [r5, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1036]
	ldrb	r10, [r4, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1292]
	ldrb	r10, [lr, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1548]
	ldrb	r10, [r1, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #1804]
	ldrb	r10, [ip, #1]!	@ zero_extendqisi2
	str	r1, [fp, #-568]
	strb	r10, [r3, #2060]
	ldrb	r10, [r9, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #2316]
	ldrb	r10, [r8, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #2572]
	ldrb	r10, [r7, #1]!	@ zero_extendqisi2
	strb	r10, [r3, #2828]
	bne	.L247
	mov	r0, #1
.L279:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L272:
	add	ip, r7, #20480
	cmp	r10, #1
	ldr	r2, [ip, #3512]
	ldr	r3, [ip, #3508]
	ldr	r9, [r2, #1188]
	ldr	r8, [r3, #1188]
	bne	.L228
.L273:
	ldrb	r3, [r6, #2544]	@ zero_extendqisi2
	cmp	r4, #0
	mov	r2, #0
	strb	r10, [ip, #3553]
	add	r3, r3, #1
	str	r2, [ip, #3572]
	str	r3, [ip, #3556]
	strb	r2, [ip, #3552]
	beq	.L229
	cmp	r5, r2
	beq	.L276
.L229:
	ldr	r3, [ip, #3512]
	ldr	r2, [ip, #3504]
	ldr	r5, [r3, #1188]
.L266:
	str	r5, [ip, #3560]
	ldr	r3, [r3, #1188]
	str	r3, [ip, #3564]
	ldr	r3, [r6, #2640]
	ldr	r4, [r2, #1188]
	cmp	r3, #1
	bls	.L277
.L233:
	bics	r2, r3, #2
	bne	.L234
	ldrb	r2, [r6, #2526]	@ zero_extendqisi2
	cmp	r2, #4
	beq	.L278
.L234:
	movw	r1, #1672
	mov	r3, r7
	mul	r0, r1, r5
	mov	r2, #0
	mul	r1, r1, r4
	add	r8, r0, #13952
	add	r6, r0, #14208
	add	r5, r0, #14464
	add	r0, r0, #14720
	add	r4, r1, #13952
	add	lr, r1, #14208
	add	ip, r1, #14464
	add	r1, r1, #14720
	add	r8, r8, #2
	add	r6, r6, #2
	add	r5, r5, #2
	add	r0, r0, #2
	add	r4, r4, #2
	add	lr, lr, #2
	add	ip, ip, #2
	add	r1, r1, #2
	add	r7, r7, r8
	add	r6, r3, r6
	add	r5, r3, r5
	add	r0, r3, r0
	add	r4, r3, r4
	add	lr, r3, lr
	add	ip, r3, ip
	add	r1, r3, r1
.L239:
	ldrb	r8, [r7, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r2, #256
	add	r3, r3, #1
	strb	r8, [r3, #12]
	ldrb	r8, [r6, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #268]
	ldrb	r8, [r5, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #524]
	ldrb	r8, [r0, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #780]
	ldrb	r8, [r4, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2060]
	ldrb	r8, [lr, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2316]
	ldrb	r8, [ip, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2572]
	ldrb	r8, [r1, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #2828]
	bne	.L239
	mov	r0, #1
	b	.L279
.L269:
	add	r2, r7, #20480
	ldr	r1, [r2, #3512]
	str	r10, [r2, #3556]
	str	r3, [r2, #3572]
	strb	r3, [r2, #3552]
	ldr	r4, [r1, #1188]
	str	r4, [r2, #3560]
	ldrb	r3, [r7, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r7, #8192
	beq	.L210
	ldr	r2, [r3, #2556]
	ldrb	r5, [r3, #2528]	@ zero_extendqisi2
	cmp	r2, #2
	ldrb	r6, [r3, #2529]	@ zero_extendqisi2
	ldrb	r0, [r3, #2526]	@ zero_extendqisi2
	beq	.L280
.L211:
	cmp	r0, #4
	beq	.L212
.L213:
	movw	r3, #1672
	add	r6, r7, #12
	mul	r2, r3, r4
	add	r5, r7, #268
	add	r4, r7, #524
	add	lr, r7, #780
	mov	r3, #0
	add	ip, r2, #13952
	add	r0, r2, #14208
	add	r1, r2, #14464
	add	r2, r2, #14720
	add	ip, ip, #2
	add	r0, r0, #2
	add	r1, r1, #2
	add	r2, r2, #2
	add	ip, r7, ip
	add	r0, r7, r0
	add	r1, r7, r1
	add	r7, r7, r2
.L215:
	ldrb	r2, [ip, #1]!	@ zero_extendqisi2
	add	r3, r3, #1
	cmp	r3, #256
	strb	r2, [r6, #1]!
	ldrb	r2, [r0, #1]!	@ zero_extendqisi2
	strb	r2, [r5, #1]!
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	strb	r2, [r4, #1]!
	ldrb	r2, [r7, #1]!	@ zero_extendqisi2
	strb	r2, [lr, #1]!
	bne	.L215
	mov	r0, #1
	b	.L279
.L271:
	cmp	r3, #0
	beq	.L227
	add	ip, r7, #20480
	ldr	r2, [ip, #3508]
	ldr	r3, [ip, #3512]
	ldr	r9, [r2, #1188]
	ldr	r8, [r3, #1188]
	b	.L226
.L270:
	add	r2, r7, #20480
	mov	r1, #1
	ldr	r0, [r2, #3512]
	str	r1, [r2, #3572]
	str	r1, [r2, #3556]
	strb	r3, [r2, #3552]
	ldr	r1, [r2, #3508]
	ldr	r5, [r0, #1188]
	strb	r3, [r2, #3568]
	str	r5, [r2, #3560]
	ldr	r4, [r1, #1188]
	str	r4, [r2, #3576]
	ldrb	r3, [r7, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r7, #8192
	ldrneb	r6, [r3, #2528]	@ zero_extendqisi2
	ldrneb	r8, [r3, #2529]	@ zero_extendqisi2
	ldreqb	r6, [r3, #2425]	@ zero_extendqisi2
	ldreqb	r8, [r3, #2426]	@ zero_extendqisi2
	ldrneb	r3, [r3, #2526]	@ zero_extendqisi2
	ldreqb	r3, [r3, #2423]	@ zero_extendqisi2
	cmp	r3, #4
	beq	.L281
.L220:
	movw	r0, #1672
	mov	r3, r7
	mul	r1, r0, r5
	mov	r2, #0
	mul	r0, r0, r4
	add	r8, r1, #13952
	add	r6, r1, #14208
	add	r5, r1, #14464
	add	r1, r1, #14720
	add	r4, r0, #13952
	add	lr, r0, #14208
	add	ip, r0, #14464
	add	r0, r0, #14720
	add	r8, r8, #2
	add	r6, r6, #2
	add	r5, r5, #2
	add	r1, r1, #2
	add	r4, r4, #2
	add	lr, lr, #2
	add	ip, ip, #2
	add	r0, r0, #2
	add	r7, r7, r8
	add	r6, r3, r6
	add	r5, r3, r5
	add	r1, r3, r1
	add	r4, r3, r4
	add	lr, r3, lr
	add	ip, r3, ip
	add	r0, r3, r0
.L222:
	ldrb	r8, [r7, #1]!	@ zero_extendqisi2
	add	r2, r2, #1
	cmp	r2, #256
	add	r3, r3, #1
	strb	r8, [r3, #12]
	ldrb	r8, [r6, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #268]
	ldrb	r8, [r5, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #524]
	ldrb	r8, [r1, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #780]
	ldrb	r8, [r4, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1036]
	ldrb	r8, [lr, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1292]
	ldrb	r8, [ip, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1548]
	ldrb	r8, [r0, #1]!	@ zero_extendqisi2
	strb	r8, [r3, #1804]
	bne	.L222
	mov	r0, #1
	b	.L279
.L210:
	ldrb	r5, [r3, #2425]	@ zero_extendqisi2
	ldrb	r6, [r3, #2426]	@ zero_extendqisi2
	ldrb	r0, [r3, #2423]	@ zero_extendqisi2
	b	.L211
.L246:
	ldrb	r3, [r6, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L245
	b	.L251
.L276:
	ldr	r2, [ip, #3504]
	ldr	r3, [ip, #3512]
	ldr	r5, [r2, #1188]
	b	.L266
.L274:
	ldr	lr, [ip, #3504]
	ldr	r2, [lr, #1188]
	b	.L267
.L277:
	ldrb	r3, [r6, #2526]	@ zero_extendqisi2
	cmp	r3, #4
	bne	.L234
	ldrb	ip, [r6, #2529]	@ zero_extendqisi2
	mov	r3, #0
	ldrb	r10, [r6, #2528]	@ zero_extendqisi2
	sub	r0, fp, #556
	mov	r2, ip
	str	ip, [fp, #-560]
	mov	r1, r10
	bl	VC1_Vfmw_GenerateIntensityMap
	ldr	ip, [fp, #-560]
	mov	r1, r10
	sub	r0, fp, #300
	mov	r3, #1
	mov	r2, ip
	bl	VC1_Vfmw_GenerateIntensityMap
	movw	r2, #1672
	mul	r2, r2, r9
	mov	r0, #0
	add	r1, r2, #13952
	add	r2, r2, #14208
	add	r1, r1, #3
	add	r2, r2, #3
	add	r1, r7, r1
	add	r2, r7, r2
.L235:
	ldrb	r3, [r1]	@ zero_extendqisi2
	sub	ip, fp, #44
	add	r0, r0, #1
	add	r3, ip, r3
	cmp	r0, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r1], #1
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, ip, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L235
	ldr	r3, [r6, #2640]
	b	.L233
.L275:
	ldrb	r0, [r6, #2526]	@ zero_extendqisi2
	cmp	r0, #4
	bne	.L245
	mov	r0, r3
	b	.L251
.L278:
	cmp	r3, #0
	sub	r0, fp, #556
	mov	r3, #0
	ldreqb	r9, [r6, #2644]	@ zero_extendqisi2
	ldrneb	r9, [r6, #2528]	@ zero_extendqisi2
	ldreqb	r6, [r6, #2648]	@ zero_extendqisi2
	ldrneb	r6, [r6, #2529]	@ zero_extendqisi2
	mov	r1, r9
	mov	r2, r6
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	r2, r6
	mov	r1, r9
	sub	r0, fp, #300
	mov	r3, #1
	bl	VC1_Vfmw_GenerateIntensityMap
	movw	r3, #1672
	mul	r2, r3, r8
	mov	r0, #0
	add	r1, r2, #14464
	add	r2, r2, #14720
	add	r1, r1, #3
	add	r2, r2, #3
	add	r1, r7, r1
	add	r2, r7, r2
.L238:
	ldrb	r3, [r1]	@ zero_extendqisi2
	sub	ip, fp, #44
	add	r0, r0, #1
	add	r3, ip, r3
	cmp	r0, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r1], #1
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, ip, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L238
	b	.L234
.L280:
	ldr	r3, [r3, #2632]
	cmp	r3, #1
	bne	.L211
.L212:
	sub	r0, fp, #556
	mov	r3, #0
	mov	r2, r6
	mov	r1, r5
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	r2, r6
	mov	r1, r5
	sub	r0, fp, #300
	mov	r3, #1
	bl	VC1_Vfmw_GenerateIntensityMap
	movw	r3, #1672
	mul	r3, r3, r4
	mov	lr, #0
	add	ip, r3, #13952
	add	r0, r3, #14208
	add	r1, r3, #14464
	add	r3, r3, #14720
	add	ip, ip, #3
	add	r0, r0, #3
	add	r1, r1, #3
	add	r3, r3, #3
	add	ip, r7, ip
	add	r0, r7, r0
	add	r1, r7, r1
	add	r2, r7, r3
.L214:
	ldrb	r3, [ip]	@ zero_extendqisi2
	sub	r5, fp, #44
	add	lr, lr, #1
	add	r3, r5, r3
	cmp	lr, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [ip], #1
	ldrb	r3, [r0]	@ zero_extendqisi2
	add	r3, r5, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r0], #1
	ldrb	r3, [r1]	@ zero_extendqisi2
	add	r3, r5, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r1], #1
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, r5, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L214
	b	.L213
.L281:
	mov	r2, r8
	mov	r1, r6
	sub	r0, fp, #556
	mov	r3, #0
	bl	VC1_Vfmw_GenerateIntensityMap
	mov	r2, r8
	mov	r1, r6
	sub	r0, fp, #300
	mov	r3, #1
	mov	r10, #0
	bl	VC1_Vfmw_GenerateIntensityMap
	movw	r2, #1672
	mul	r1, r2, r5
	str	r4, [fp, #-560]
	mul	r2, r2, r4
	add	r9, r1, #13952
	add	r8, r1, #14208
	add	r6, r1, #14464
	add	r1, r1, #14720
	add	lr, r2, #13952
	add	ip, r2, #14208
	add	r0, r2, #14464
	add	r2, r2, #14720
	add	r9, r9, #3
	add	r8, r8, #3
	add	r6, r6, #3
	add	r1, r1, #3
	add	lr, lr, #3
	add	ip, ip, #3
	add	r0, r0, #3
	add	r2, r2, #3
	add	r9, r7, r9
	add	r8, r7, r8
	add	r6, r7, r6
	add	r1, r7, r1
	add	lr, r7, lr
	add	ip, r7, ip
	add	r0, r7, r0
	add	r2, r7, r2
.L221:
	ldrb	r3, [r9]	@ zero_extendqisi2
	sub	r4, fp, #44
	add	r10, r10, #1
	add	r3, r4, r3
	cmp	r10, #256
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r9], #1
	ldrb	r3, [r8]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r8], #1
	ldrb	r3, [r6]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r6], #1
	ldrb	r3, [r1]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r1], #1
	ldrb	r3, [lr]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [lr], #1
	ldrb	r3, [ip]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [ip], #1
	ldrb	r3, [r0]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-512]	@ zero_extendqisi2
	strb	r3, [r0], #1
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r3, r4, r3
	ldrb	r3, [r3, #-256]	@ zero_extendqisi2
	strb	r3, [r2], #1
	bne	.L221
	ldr	r4, [fp, #-560]
	b	.L220
.L283:
	.align	2
.L282:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_BuildRefList, .-VC1_Vfmw_BuildRefList
	.align	2
	.global	VC1_Vfmw_GetStreamInfo
	.type	VC1_Vfmw_GetStreamInfo, %function
VC1_Vfmw_GetStreamInfo:
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
	UNWIND(.pad #36)
	sub	sp, sp, #36
	add	r8, r0, #12288
	add	r4, r0, #32768
	mov	r5, r0
	ldrb	r3, [r8, #3544]	@ zero_extendqisi2
	ldr	r9, [r4, #3968]
	cmp	r3, #0
	beq	.L285
	add	r3, r0, #20480
	movw	r2, #3338
	movw	r1, #3336
	ldr	r3, [r3, #3004]
	cmp	r3, #3
	ldr	r3, [r4, #3972]
	addeq	r3, r3, #1
	addeq	r3, r3, r3, lsr #31
	moveq	r3, r3, asr #1
	mul	r3, r3, r9
	str	r3, [fp, #-48]
	add	r3, r0, #12736
	ldrh	r2, [r3, r2]
	ldrh	r3, [r3, r1]
	adds	r1, r2, #15
	addmi	r1, r2, #30
	adds	r0, r3, #15
	addmi	r0, r3, #30
	mov	r1, r1, asr #4
	mov	r0, r0, asr #4
.L337:
	mov	r2, r0, asl #4
	movw	ip, #8160
	sub	r3, r2, #32
	cmp	r3, ip
	mov	r3, r1, asl #4
	bhi	.L288
	sub	lr, r3, #32
	cmp	lr, ip
	bhi	.L288
	ldr	r3, [r4, #3980]
	cmp	r3, r1
	beq	.L369
.L291:
	ldr	r2, [r4, #3972]
	mov	r3, r9, asl #4
	add	r3, r3, #63
	str	r9, [r4, #3976]
	bic	r3, r3, #63
	str	r3, [r4, #3992]
	str	r2, [r4, #3980]
	ldrb	r3, [r8, #456]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L299
	mov	r3, #1
.L293:
	ldrb	r2, [r8, #451]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L370
.L296:
	ldrb	r2, [r8, #448]	@ zero_extendqisi2
	eor	r2, r2, #8
	ubfx	r2, r2, #3, #1
	orrs	r3, r3, r2
	bne	.L299
.L303:
	mov	r0, r5
	bl	VC1_Vfmw_GetImageBuffer
	subs	r6, r0, #0
	beq	.L371
	add	r10, r5, #49152
	ldr	r1, [r4, #4044]
	ldr	r0, [r10, #472]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L305
	ldr	r0, [r5]
	add	r2, r3, #592
	add	ip, r3, #608
	ldr	r1, .L379
	ldrd	r6, [r0, #56]
	mov	r0, #29
	strd	r6, [r2, #-8]
	ldr	lr, [r5]
	ldrd	r6, [lr, #72]
	strd	r6, [r2]
	ldr	lr, [r5]
	ldrd	r6, [lr, #88]
	strd	r6, [ip, #-8]
	mvn	r6, #0
	ldr	ip, [r5]
	mvn	r7, #0
	ldr	ip, [ip, #104]
	str	ip, [r3]
	ldr	ip, [r5]
	ldr	ip, [ip, #108]
	str	ip, [r3, #4]
	ldr	ip, [r5]
	ldr	ip, [ip, #112]
	str	ip, [r3, #8]
	ldr	ip, [r5]
	ldr	ip, [ip, #128]
	str	ip, [r3, #12]
	ldr	r3, [r5]
	strd	r6, [r3, #56]
	ldrd	r6, [r2]
	ldrd	r2, [r2, #-8]
	strd	r6, [sp]
	bl	dprint_vfmw
.L305:
	ldrb	r3, [r8, #3544]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L306
	add	r3, r5, #20480
	ldr	r3, [r3, #3004]
	cmp	r3, #3
	beq	.L372
.L306:
	ldr	r3, [r4, #3952]
	mov	r2, #0
	str	r2, [r3, #1092]
.L307:
	ldr	r3, [r4, #3952]
	mov	r2, #0
	strb	r2, [r3, #2]
	ldrb	r3, [r8, #3544]	@ zero_extendqisi2
	cmp	r3, r2
	bne	.L308
	add	r3, r5, #20480
	ldrb	r2, [r3, #2624]	@ zero_extendqisi2
	cmp	r2, #1
	ldreqb	r2, [r3, #2862]	@ zero_extendqisi2
	ldreq	r3, [r4, #3952]
	streqb	r2, [r3, #2]
.L308:
	ldrb	r3, [r8, #450]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #1
	ldr	r3, [r4, #4032]
	movls	r7, #1
	movhi	r7, #0
	bhi	.L309
	cmp	r3, #0
	ldr	r2, [r4, #4036]
	ldr	r3, [r4, #4040]
	movne	r1, #2
	moveq	r1, #1
	cmp	r2, r3
	str	r1, [r4, #4032]
	beq	.L311
	ldr	r1, .L379+4
	mov	r0, #13
	bl	dprint_vfmw
	mov	r2, #0
	ldr	r1, [r4, #4036]
	ldr	r0, [r10, #472]
	bl	FSP_SetRef
	ldr	r3, [r4, #4040]
.L311:
	ldr	r1, [r4, #4044]
	mov	r2, #1
	str	r3, [r4, #4036]
	str	r1, [r4, #4040]
	ldr	r0, [r10, #472]
	bl	FSP_SetRef
	ldr	r1, [r4, #4036]
	ldr	r0, [r10, #472]
	bl	FSP_RemovePmv
	ldrb	r3, [r8, #450]	@ zero_extendqisi2
	cmp	r3, #5
	cmpne	r3, #1
	bhi	.L313
	ldr	r3, [r4, #3960]
	mov	r1, #0
	mov	r2, #1
	strb	r1, [r3]
	ldr	r3, [r4, #3952]
	strb	r2, [r3]
	ldr	r2, [r4, #3956]
	ldr	r3, [r4, #3952]
	str	r2, [r4, #3960]
	str	r3, [r4, #3956]
.L313:
	ldr	r1, [r4, #4044]
	ldr	r0, [r10, #472]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #4036]
	mov	r6, r0
	ldr	r0, [r10, #472]
	bl	FSP_GetLogicFs
	ldr	r1, [r4, #4040]
	mov	r7, r0
	ldr	r0, [r10, #472]
	bl	FSP_GetLogicFs
	cmp	r6, #0
	cmpne	r7, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	ip, r0
	cmp	r3, #0
	bne	.L373
	ldrb	r3, [r8, #3544]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L374
.L319:
	mov	r3, #0
.L364:
	str	r3, [r6, #92]
	ldrb	r3, [r8, #450]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L375
.L321:
	ldr	r2, [r6, #28]
	cmp	r2, #0
	beq	.L322
	ldr	r3, [r6, #32]
	cmp	r3, #0
	beq	.L322
	ldr	r3, [ip, #28]
	cmp	r3, #0
	ldreq	r3, [r2, #8]
	ldrne	r3, [r3, #8]
	str	r3, [r8, #112]
	ldr	r3, [r7, #28]
	mov	r7, #0
	cmp	r3, #0
	ldreq	r3, [r6, #28]
	ldr	r3, [r3, #8]
	str	r3, [r8, #108]
	ldr	r3, [r6, #28]
	ldr	r3, [r3, #8]
	str	r3, [r8, #236]
	ldr	r3, [r6, #8]
	str	r3, [r8, #116]
	ldr	r3, [ip, #8]
	str	r3, [r8, #120]
	ldr	r3, [r6, #32]
	ldr	r3, [r3, #8]
	str	r3, [r8, #104]
	ldr	r3, [r6, #32]
	ldr	r3, [r3, #24]
	str	r3, [r8, #184]
	ldr	r3, [r6, #32]
	ldr	r3, [r3, #28]
	str	r3, [r8, #188]
	ldr	r3, [r6, #32]
	ldr	r3, [r3, #60]
	str	r3, [r8, #192]
	ldr	r3, [r6, #32]
	ldr	r3, [r3, #44]
	str	r3, [r8, #196]
	ldr	r3, [r6, #32]
	ldr	r3, [r3, #48]
	str	r3, [r8, #200]
	ldr	r3, [r6, #28]
	ldr	r6, [r4, #3952]
	ldr	r0, [r3, #8]
	bl	MEM_Phy2Vir
	str	r7, [r6, #1548]
	str	r0, [r6, #1544]
	ldr	r0, [r8, #108]
	ldr	r6, [r4, #3960]
	bl	MEM_Phy2Vir
	str	r7, [r6, #1548]
	str	r0, [r6, #1544]
	ldr	r0, [r8, #112]
	ldr	r6, [r4, #3956]
	bl	MEM_Phy2Vir
	str	r7, [r6, #1548]
	str	r0, [r6, #1544]
.L298:
	movw	r3, #3544
	ldrsb	r3, [r8, r3]
	cmp	r3, #0
	beq	.L376
	add	ip, r5, #20480
	ldr	r3, [r4, #3952]
	ldr	r2, [ip, #3004]
	strb	r2, [r3, #1027]
	ldr	r3, [r4, #3952]
	ldrb	r2, [ip, #2961]	@ zero_extendqisi2
	strb	r2, [r3, #1028]
	ldrb	r2, [ip, #2974]	@ zero_extendqisi2
	ldr	r3, [r4, #3952]
	sub	r0, r2, #2
	ldrb	r1, [ip, #3001]	@ zero_extendqisi2
	cmp	r0, #1
	movls	r2, #1
	bls	.L331
	cmp	r2, #4
	movne	r2, #0
	beq	.L377
.L331:
	add	r3, r3, r1
	strb	r2, [r3, #1029]
	ldr	r0, [r4, #4052]
	cmp	r0, #0
	beq	.L332
	sub	r0, r0, #1
	cmp	r0, #0
	mov	lr, r0
	moveq	r1, r0
	beq	.L334
	add	r2, r5, #36608
	mov	r1, #0
	add	r2, r2, #224
.L335:
	ldr	r3, [r2, #64]
	add	r2, r2, #48
	strb	r1, [r2, #-48]
	add	r1, r1, #1
	cmp	r1, lr
	mul	r3, r3, r9
	sub	r3, r3, #1
	str	r3, [r2, #-32]
	bne	.L335
	uxtb	r1, r1
.L334:
	mov	r3, r0, asl #6
	movw	r2, #24560
	sub	r0, r3, r0, asl #4
	ldr	r3, [fp, #-48]
	add	r0, r8, r0
	movw	lr, #24544
	sub	r3, r3, #1
	strb	r1, [r0, lr]
	str	r3, [r0, r2]
	ldrb	r1, [r8, #450]	@ zero_extendqisi2
	cmp	r1, #2
	bne	.L330
	ldrb	r3, [ip, #2991]	@ zero_extendqisi2
	add	r0, r5, #49152
	ldr	r2, [ip, #3108]
	mul	r2, r2, r3
	mov	r2, r2, asr #8
	str	r2, [r0]
	rsb	r3, r2, r3
	subs	r3, r3, #1
	movmi	r3, #0
	str	r3, [r0, #4]
	b	.L330
.L288:
	ldr	r1, .L379+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r6, #0
.L361:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L285:
	ldr	r1, [r4, #3972]
	mov	r0, r9
	mul	r3, r1, r9
	str	r3, [fp, #-48]
	b	.L337
.L299:
	add	r10, r5, #49152
	add	r3, r5, #34816
	add	r3, r3, #232
	ldr	r1, [r4, #4040]
	str	r3, [r4, #3952]
	str	r3, [r4, #3964]
	str	r3, [r4, #3960]
	str	r3, [r4, #3956]
	ldr	r0, [r10, #472]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L295
	ldr	r1, [r6, #544]
	add	r3, r6, #576
	ldr	r0, [r10, #472]
	add	r7, r6, #560
	str	r3, [fp, #-52]
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	add	r3, r6, #544
	ldr	r0, [r10, #472]
	str	r3, [fp, #-56]
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r10, #472]
	bl	FreeUsdByDec
	ldr	r6, [fp, #-52]
	ldr	r0, [r10, #472]
	ldr	r1, [r6, #-8]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-56]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r3]
	strd	r0, [r7, #-8]
	strd	r0, [r7]
	strd	r0, [r6, #-8]
	ldr	r1, [r4, #4040]
	ldr	r0, [r10, #472]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #4036]
	ldr	r0, [r10, #472]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	str	r3, [r4, #4036]
	str	r3, [r4, #4040]
	ldr	r0, [r10, #472]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #4040]
	str	r0, [r4, #4036]
.L295:
	add	r3, r5, #26624
	add	r1, r5, #34816
	add	r3, r3, #65
	add	r1, r1, #233
	mov	r2, #0
	str	r2, [r4, #4032]
.L301:
	strb	r2, [r3]
	add	r3, r3, #1664
	strb	r2, [r3, #-1665]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L301
	add	r7, r5, #49152
	ldr	r0, [r10, #472]
	add	r7, r7, #120
	mov	r1, r7
	bl	FSP_ClearNotInVoQueue
	ldrb	r6, [r8, #448]	@ zero_extendqisi2
	and	r6, r6, #8
	ands	r6, r6, #255
	bne	.L303
	mov	r0, r7
	bl	ResetVoQueue
	ldr	r1, [r5]
	mov	r3, #2
	mov	r0, r5
	ldr	r2, [r1, #684]
	ldr	ip, [r1, #688]
	adds	r1, r2, #15
	addmi	r1, r2, #30
	adds	r2, ip, #15
	addmi	r2, ip, #30
	mov	r1, r1, asr #4
	str	r1, [r8, #276]
	mov	r2, r2, asr #4
	str	r2, [r8, #280]
	add	r2, r2, #1
	mov	r1, r1, asl #4
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
	mov	r2, r2, asl #5
	bl	VC1_ArrangeVahbMem
	cmp	r0, #1
	bne	.L302
	ldrb	r3, [r8, #448]	@ zero_extendqisi2
	orr	r3, r3, #8
	strb	r3, [r8, #448]
	b	.L303
.L371:
	ldr	r1, .L379+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L361
.L369:
	ldr	r3, [r4, #3976]
	cmp	r3, r0
	bne	.L291
	mov	r3, r9, asl #4
	add	r3, r3, #63
	bic	r3, r3, #63
	str	r3, [r4, #3992]
	ldrb	r3, [r8, #456]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #0
	bne	.L293
	b	.L296
.L309:
	cmp	r3, #1
	bhi	.L313
	ldr	r0, [r10, #472]
	mov	r2, #1
	ldr	r1, [r4, #4044]
	mov	r6, r7
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #3952]
	ldr	r1, .L379+16
	mov	r0, #1
	strb	r7, [r3]
	ldr	r3, [r4, #3952]
	strb	r7, [r3, #1]
	bl	dprint_vfmw
	b	.L361
.L373:
	ldr	r1, [r4, #4044]
	mov	r2, #1
	str	r0, [fp, #-48]
	ldr	r0, [r10, #472]
	bl	FSP_ClearLogicFs
	ldr	r1, [r4, #3952]
	mov	lr, #0
	ldr	ip, [fp, #-48]
	mov	r3, r6
	mov	r0, lr
	strb	lr, [r1]
	movw	r2, #2291
	ldr	r4, [r4, #3952]
	ldr	r1, .L379+20
	strb	lr, [r4, #1]
	stmia	sp, {r7, ip}
	bl	dprint_vfmw
	ldrb	r3, [r8, #450]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L368
.L317:
	ldr	r1, .L379+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
	b	.L361
.L376:
	ldr	r1, [r4, #3952]
	add	r2, r5, #20480
	strb	r3, [r1, #1027]
	ldr	r1, [r4, #3952]
	ldrb	r0, [r2, #2863]	@ zero_extendqisi2
	strb	r0, [r1, #1028]
	ldrb	r0, [r2, #2871]	@ zero_extendqisi2
	ldr	r1, [r4, #3952]
	sub	ip, r0, #2
	cmp	ip, #1
	movls	r3, #1
	bls	.L329
	cmp	r0, #4
	beq	.L378
.L329:
	add	r6, r5, #45056
	strb	r3, [r1, #1030]
	strb	r3, [r1, #1029]
	mov	r2, #1
	mov	r3, #0
	str	r2, [r4, #4052]
	strb	r3, [r4, #4064]
	ldr	r0, [r8, #3576]
	ldr	r7, [r6, #4060]
	bl	BsPos
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	add	r0, r7, r0, asr #3
	str	r0, [r4, #4056]
	ldr	r0, [r8, #3576]
	ldr	r7, [r6, #4072]
	bl	BsPos
	add	r3, r0, #7
	cmp	r0, #0
	movlt	r0, r3
	add	r0, r7, r0, asr #3
	str	r0, [r4, #4068]
	ldr	r0, [r8, #3576]
	bl	BsPos
	and	r0, r0, #7
	str	r0, [r4, #4072]
	ldr	r0, [r8, #3576]
	ldr	r6, [r6, #4080]
	bl	BsPos
	add	r2, r5, #49152
	mov	r6, r6, asl #3
	rsb	r0, r0, r6
	str	r0, [r4, #4076]
	ldr	r1, [r2, #24]
	ldr	r3, [r2, #28]
	mul	r3, r3, r1
	sub	r3, r3, #1
	str	r3, [r4, #4080]
	ldrb	r1, [r8, #450]	@ zero_extendqisi2
.L330:
	mov	r3, #1
	mov	r2, #0
	add	r0, r5, #12736
	bl	VC1_Vfmw_BuildRefList
	subs	r6, r0, #0
	movne	r6, #1
	bne	.L361
	add	r5, r5, #49152
	ldr	r1, [r4, #4044]
	mov	r2, #1
	ldr	r0, [r5, #472]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #3952]
	ldr	r1, .L379+28
	mov	r0, #1
	strb	r6, [r3]
	ldr	r3, [r4, #3952]
	strb	r6, [r3, #1]
	bl	dprint_vfmw
	b	.L361
.L374:
	add	r3, r5, #20480
	ldr	r3, [r3, #3004]
	cmp	r3, #3
	bne	.L319
	ldr	r3, .L379+32
	ldr	r3, [r3]
	cmp	r3, #1
	bne	.L319
	b	.L364
.L322:
	mov	r2, #1
	ldr	r1, [r4, #4044]
	ldr	r0, [r10, #472]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3952]
	mov	r3, #0
	ldr	r1, .L379+36
	mov	r0, r3
	strb	r3, [r2]
	ldr	r2, [r4, #3952]
	strb	r3, [r2, #1]
	ldr	ip, [r6, #32]
	ldr	r3, [r4, #4044]
	ldr	r2, [r4, #4036]
	str	ip, [sp, #8]
	ldr	lr, [r4, #4040]
	ldr	ip, [r6, #28]
	str	lr, [sp]
	str	ip, [sp, #4]
	bl	dprint_vfmw
	ldrb	r3, [r8, #450]	@ zero_extendqisi2
	cmp	r3, #5
	bne	.L317
.L368:
	ldr	r3, [r10, #44]
	cmp	r3, #0
	subgt	r3, r3, #1
	strgt	r3, [r10, #44]
	b	.L317
.L370:
	ldrb	r2, [r8, #457]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L298
	b	.L296
.L332:
	mov	r3, #1
	mov	r1, r0
	str	r3, [r4, #4052]
	b	.L334
.L375:
	ldr	r3, [r7, #92]
	str	r3, [r6, #92]
	ldr	r2, [r4, #3960]
	ldr	r3, [r4, #3952]
	ldr	r2, [r2, #1092]
	str	r2, [r3, #1092]
	ldr	r3, [r10, #44]
	add	r3, r3, #1
	str	r3, [r10, #44]
	b	.L321
.L372:
	ldr	r3, .L379+32
	ldr	r3, [r3]
	cmp	r3, #1
	ldreq	r2, [r4, #3952]
	streq	r3, [r2, #1092]
	bne	.L306
	b	.L307
.L302:
	ldr	r1, .L379+40
	mov	r0, #1
	bl	dprint_vfmw
	ldrb	r3, [r8, #448]	@ zero_extendqisi2
	bic	r3, r3, #8
	strb	r3, [r8, #448]
	b	.L361
.L377:
	ldrb	r2, [ip, #2975]	@ zero_extendqisi2
	sub	r2, r2, #2
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	b	.L331
.L378:
	ldrb	r3, [r2, #2872]	@ zero_extendqisi2
	sub	r3, r3, #2
	cmp	r3, #1
	movhi	r3, #0
	movls	r3, #1
	b	.L329
.L380:
	.align	2
.L379:
	.word	.LC30
	.word	.LC31
	.word	.LC20
	.word	.LC29
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC36
	.word	USE_FF_APT_EN
	.word	.LC35
	.word	.LC28
	UNWIND(.fnend)
	.size	VC1_Vfmw_GetStreamInfo, .-VC1_Vfmw_GetStreamInfo
	.align	2
	.global	VC1_Vfmw_PrepareDecode
	.type	VC1_Vfmw_PrepareDecode, %function
VC1_Vfmw_PrepareDecode:
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
	bl	VC1_Vfmw_GetStreamInfo
	subs	r4, r0, #0
	movne	r4, #1
	bne	.L382
	ldr	r1, .L384
	bl	dprint_vfmw
.L382:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L385:
	.align	2
.L384:
	.word	.LC37
	UNWIND(.fnend)
	.size	VC1_Vfmw_PrepareDecode, .-VC1_Vfmw_PrepareDecode
	.align	2
	.global	VC1_DecMvrange
	.type	VC1_DecMvrange, %function
VC1_DecMvrange:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	ldr	lr, .L387
	mov	r4, r0
	sub	ip, fp, #84
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #3
	bl	BsShow
	sub	r3, fp, #20
	add	r3, r3, r0, lsl #3
	mov	r0, r4
	ldr	r1, [r3, #-60]
	ldr	r4, [r3, #-64]
	bl	BsSkip
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L388:
	.align	2
.L387:
	.word	.LANCHOR0+16
	UNWIND(.fnend)
	.size	VC1_DecMvrange, .-VC1_DecMvrange
	.align	2
	.global	VC1_DecTransacfrm
	.type	VC1_DecTransacfrm, %function
VC1_DecTransacfrm:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #68)
	sub	sp, sp, #68
	mov	r2, #64
	mov	r4, r0
	mov	r1, #0
	sub	r0, fp, #84
	bl	memset
	mov	r3, #2
	mov	r1, r3
	mov	r0, r4
	mov	r2, #1
	str	r3, [fp, #-64]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	str	r2, [fp, #-80]
	str	r2, [fp, #-72]
	str	r2, [fp, #-68]
	bl	BsShow
	sub	r3, fp, #20
	add	r3, r3, r0, lsl #3
	mov	r0, r4
	ldr	r1, [r3, #-60]
	ldr	r4, [r3, #-64]
	bl	BsSkip
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_DecTransacfrm, .-VC1_DecTransacfrm
	.align	2
	.global	VC1_SetCurPicResolutionInfo
	.type	VC1_SetCurPicResolutionInfo, %function
VC1_SetCurPicResolutionInfo:
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
	add	r3, r0, #20480
	cmp	r1, #1
	add	r0, r0, #32768
	ldr	r2, [r3, #3520]
	beq	.L392
	cmp	r1, #2
	beq	.L398
	cmp	r1, #0
	beq	.L397
	add	r2, r2, #1
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
.L398:
	str	r2, [r0, #3672]
	ldr	r3, [r3, #3524]
	add	r3, r3, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	str	r3, [r0, #3676]
	b	.L395
.L392:
	add	r2, r2, #1
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
.L397:
	str	r2, [r0, #3672]
	ldr	r3, [r3, #3524]
	str	r3, [r0, #3676]
.L395:
	mul	r1, r3, r2
	mov	r2, r2, asl #4
	mov	r3, r3, asl #4
	str	r2, [r0, #3664]
	str	r3, [r0, #3668]
	str	r1, [r0, #3680]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_SetCurPicResolutionInfo, .-VC1_SetCurPicResolutionInfo
	.align	2
	.global	VC1_DecMvmodeProgrP
	.type	VC1_DecMvmodeProgrP, %function
VC1_DecMvmodeProgrP:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #44)
	sub	sp, sp, #44
	mov	r6, r1
	mov	r1, #4
	mov	r7, r0
	bl	BsShow
	ldr	ip, .L410
	sub	r4, fp, #76
	sub	lr, fp, #56
	mov	r5, r0
	cmp	r0, #1
	ldmia	ip!, {r0, r1, r2, r3}
	ldr	r8, [ip], #4
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	str	r8, [r4]
	ldr	ip, [ip]
	stmia	lr!, {r0, r1, r2, r3}
	str	ip, [lr]
	ble	.L408
	cmp	r5, #3
	movle	r1, #3
	movle	r4, #2
	bgt	.L409
.L401:
	mov	r0, r7
	bl	BsSkip
	sub	r3, fp, #36
	add	r4, r3, r4, lsl #2
	cmp	r6, #12
	ldrhi	r0, [r4, #-40]
	ldrls	r0, [r4, #-20]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L409:
	cmp	r5, #8
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
	b	.L401
.L408:
	cmp	r5, #0
	mov	r1, #4
	moveq	r4, #3
	movne	r4, r1
	b	.L401
.L411:
	.align	2
.L410:
	.word	.LANCHOR0+80
	UNWIND(.fnend)
	.size	VC1_DecMvmodeProgrP, .-VC1_DecMvmodeProgrP
	.align	2
	.global	VC1_DecMvmodeProgrB
	.type	VC1_DecMvmodeProgrB, %function
VC1_DecMvmodeProgrB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
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
	mov	r1, #1
	bl	BsSkip
	ldr	r2, .L413
	sub	r3, fp, #12
	add	r3, r3, r0, lsl #2
	ldmia	r2, {r0, r1}
	sub	r2, fp, #12
	stmdb	r2, {r0, r1}
	ldr	r0, [r3, #-8]
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L414:
	.align	2
.L413:
	.word	.LANCHOR0+120
	UNWIND(.fnend)
	.size	VC1_DecMvmodeProgrB, .-VC1_DecMvmodeProgrB
	.align	2
	.global	VC1_DecMvmodeInterB
	.type	VC1_DecMvmodeInterB, %function
VC1_DecMvmodeInterB:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #40)
	sub	sp, sp, #40
	mov	r5, r1
	mov	r1, #3
	mov	r6, r0
	bl	BsShow
	ldr	r3, .L423
	sub	lr, fp, #72
	mov	r8, #0
	mov	r9, #1
	mov	ip, #2
	mov	r4, #3
	str	r8, [fp, #-52]
	str	r8, [fp, #-40]
	str	r9, [fp, #-56]
	str	ip, [fp, #-48]
	str	r4, [fp, #-44]
	mov	r7, r0
	cmp	r0, #1
	ldmia	r3, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ble	.L422
	cmp	r7, #4
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
.L417:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #36
	add	ip, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [ip, #-36]
	ldrls	r0, [ip, #-20]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L422:
	cmp	r7, r8
	mov	r1, r4
	movne	r4, ip
	b	.L417
.L424:
	.align	2
.L423:
	.word	.LANCHOR0+128
	UNWIND(.fnend)
	.size	VC1_DecMvmodeInterB, .-VC1_DecMvmodeInterB
	.align	2
	.global	VC1_DecMvmode2
	.type	VC1_DecMvmode2, %function
VC1_DecMvmode2:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
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
	mov	r5, r1
	mov	r1, #3
	mov	r6, r0
	bl	BsShow
	ldr	r3, .L434
	sub	lr, fp, #60
	add	ip, r3, #16
	mov	r4, r0
	cmp	r0, #1
	ldmia	r3, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	sub	ip, fp, #28
	stmdb	ip, {r0, r1, r2, r3}
	ble	.L433
	cmp	r4, #4
	movlt	r1, #2
	movge	r1, #1
	movlt	r4, #1
	movge	r4, #0
.L427:
	mov	r0, r6
	bl	BsSkip
	sub	r3, fp, #28
	add	r4, r3, r4, lsl #2
	cmp	r5, #12
	ldrhi	r0, [r4, #-32]
	ldrls	r0, [r4, #-16]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L433:
	cmp	r4, #0
	mov	r1, #3
	moveq	r4, r1
	movne	r4, #2
	b	.L427
.L435:
	.align	2
.L434:
	.word	.LANCHOR0+128
	UNWIND(.fnend)
	.size	VC1_DecMvmode2, .-VC1_DecMvmode2
	.align	2
	.global	VC1_DecBfractionSMP
	.type	VC1_DecBfractionSMP, %function
VC1_DecBfractionSMP:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 216
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
	ldr	ip, .L442
	str	r0, [fp, #-248]
	sub	r10, fp, #244
	str	r1, [fp, #-252]
	sub	r8, fp, #216
	str	r2, [fp, #-256]
	sub	r5, fp, #156
	ldmia	ip!, {r0, r1, r2, r3}
	sub	lr, fp, #100
	sub	r7, fp, #188
	add	r9, ip, #12
	add	r6, ip, #40
	stmia	r10!, {r0, r1, r2, r3}
	add	r4, ip, #96
	ldmia	ip, {r0, r1, r2}
	add	ip, ip, #152
	stmia	r10, {r0, r1, r2}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	r8!, {r0, r1, r2, r3}
	ldmia	r9, {r0, r1, r2}
	stmia	r8, {r0, r1, r2}
	ldmia	r6!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	ldmia	r6!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	ldmia	r6!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	ldmia	r6, {r0, r1}
	stmia	r5, {r0, r1}
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r4!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r4, {r0, r1}
	stmia	lr, {r0, r1}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	r7!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2, r3}
	stmia	r7, {r0, r1, r2, r3}
	mov	r1, #3
	ldr	r0, [fp, #-248]
	bl	BsShow
	mov	r4, r0
	cmp	r4, #6
	ldr	r0, [fp, #-248]
	bgt	.L437
	mov	r1, #3
	bl	BsSkip
	sub	r3, fp, #44
	add	r3, r3, r4, lsl #2
	ldr	r1, [r3, #-200]
	ldr	r2, [r3, #-172]
.L438:
	sub	r3, fp, #44
	mov	r0, r4
	add	r2, r3, r2, lsl #2
	ldr	r3, [r2, #-148]
	ldr	r2, [fp, #-252]
	mul	r3, r3, r1
	str	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L437:
	mov	r1, #7
	bl	BsGet
	and	r4, r0, #15
	cmp	r4, #15
	beq	.L441
	sub	r0, r0, #112
	sub	r3, fp, #44
	add	r4, r4, #7
	add	r0, r3, r0, lsl #2
	ldr	r1, [r0, #-112]
	ldr	r2, [r0, #-56]
	b	.L438
.L441:
	ldr	r2, [fp, #-256]
	mov	r3, #4
	mov	r0, #22
	strb	r3, [r2]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L443:
	.align	2
.L442:
	.word	.LANCHOR0+160
	UNWIND(.fnend)
	.size	VC1_DecBfractionSMP, .-VC1_DecBfractionSMP
	.align	2
	.global	VC1_DecBfraction
	.type	VC1_DecBfraction, %function
VC1_DecBfraction:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 216
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #228)
	sub	sp, sp, #228
	ldr	r6, .L452
	str	r0, [fp, #-248]
	sub	r10, fp, #244
	str	r1, [fp, #-256]
	sub	r8, fp, #216
	ldmia	r6!, {r0, r1, r2, r3}
	sub	lr, fp, #188
	str	lr, [fp, #-252]
	sub	r4, fp, #156
	sub	ip, fp, #100
	add	r9, r6, #12
	add	r5, r6, #40
	stmia	r10!, {r0, r1, r2, r3}
	add	lr, r6, #96
	ldmia	r6, {r0, r1, r2}
	add	r7, r6, #152
	stmia	r10, {r0, r1, r2}
	ldmia	r9!, {r0, r1, r2, r3}
	stmia	r8!, {r0, r1, r2, r3}
	ldmia	r9, {r0, r1, r2}
	stmia	r8, {r0, r1, r2}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	r5!, {r0, r1, r2, r3}
	stmia	r4!, {r0, r1, r2, r3}
	ldmia	r5, {r0, r1}
	stmia	r4, {r0, r1}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1}
	ldr	lr, [fp, #-252]
	stmia	ip, {r0, r1}
	ldmia	r7!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	r7, {r0, r1, r2, r3}
	stmia	lr, {r0, r1, r2, r3}
	mov	r1, #3
	ldr	r0, [fp, #-248]
	bl	BsShow
	mov	r4, r0
	cmp	r4, #6
	ldr	r0, [fp, #-248]
	bgt	.L445
	mov	r1, #3
	bl	BsSkip
	sub	r3, fp, #44
	add	r2, r3, r4, lsl #2
	ldr	r1, [r2, #-200]
	ldr	r2, [r2, #-172]
	sub	r3, r2, #1
	cmp	r3, #7
	bhi	.L449
.L451:
	sub	r2, fp, #44
	add	r3, r2, r3, lsl #2
	ldr	r3, [r3, #-144]
	mul	r3, r3, r1
.L450:
	ldr	r2, [fp, #-256]
	str	r3, [r2]
.L447:
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L445:
	mov	r1, #7
	bl	BsGet
	and	r4, r0, #15
	sub	r3, r4, #14
	add	r4, r4, #7
	cmp	r3, #1
	bls	.L447
	sub	r3, r0, #112
	cmp	r3, #13
	bhi	.L448
	sub	r2, fp, #44
	add	r2, r2, r3, lsl #2
	ldr	r1, [r2, #-112]
	ldr	r2, [r2, #-56]
	sub	r3, r2, #1
	cmp	r3, #7
	bls	.L451
.L449:
	str	r2, [sp]
	movw	r3, #3466
	ldr	r2, .L452+4
	mov	r0, #1
	ldr	r1, .L452+8
	bl	dprint_vfmw
	mov	r3, #0
	b	.L450
.L448:
	str	r0, [sp]
	add	r2, r6, #184
	mov	r3, #3456
	ldr	r1, .L452+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, #0
	b	.L449
.L453:
	.align	2
.L452:
	.word	.LANCHOR0+160
	.word	.LANCHOR0+360
	.word	.LC39
	.word	.LC38
	UNWIND(.fnend)
	.size	VC1_DecBfraction, .-VC1_DecBfraction
	.align	2
	.global	VC1_VopDQuant
	.type	VC1_VopDQuant, %function
VC1_VopDQuant:
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
	cmp	r1, #2
	mov	r6, r2
	mov	r4, r3
	mov	r7, r0
	beq	.L472
	mov	r1, #1
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4]
	cmp	r5, #1
	beq	.L473
.L458:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L472:
	mov	r3, #1
	mov	r1, #3
	strb	r3, [r4, #3]
	strb	r3, [r4]
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #7
	addne	r6, r6, #1
	addne	r3, r0, r6
	strneb	r3, [r4, #8]
	beq	.L474
.L457:
	mov	r3, #1
	mov	r0, #1
	str	r3, [r4, #12]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L473:
	mov	r1, #2
	mov	r0, r7
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #1]
	cmp	r1, #0
	streq	r5, [r4, #12]
	beq	.L461
	cmp	r1, #2
	beq	.L475
	cmp	r1, #1
	beq	.L476
	cmp	r1, #3
	movne	r3, #0
	strne	r3, [r4, #12]
	beq	.L477
.L461:
	ldr	r3, [r4]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #768
	beq	.L458
	mov	r3, #1
	mov	r1, #3
	strb	r3, [r4, #3]
	mov	r0, r7
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #7
	addne	r6, r6, #1
	addne	r6, r0, r6
	strneb	r6, [r4, #8]
	bne	.L458
	mov	r0, r7
	mov	r1, #5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	strb	r0, [r4, #8]
	b	.L458
.L477:
	mov	r1, r5
	mov	r0, r7
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #2]
	cmp	r0, #0
	movne	r3, #10
	moveq	r3, #11
	str	r3, [r4, #12]
	b	.L461
.L474:
	mov	r0, r7
	mov	r1, #5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #5]
	strb	r0, [r4, #8]
	b	.L457
.L475:
	mov	r0, r7
	bl	BsGet
	uxtb	r3, r0
	strb	r0, [r4, #6]
	add	r3, r3, #6
	str	r3, [r4, #12]
	b	.L461
.L476:
	mov	r1, #2
	mov	r0, r7
	bl	BsGet
	uxtb	r3, r0
	strb	r0, [r4, #7]
	add	r3, r3, #2
	str	r3, [r4, #12]
	b	.L461
	UNWIND(.fnend)
	.size	VC1_VopDQuant, .-VC1_VopDQuant
	.align	2
	.global	VC1_DecNormDiff6Tile
	.type	VC1_DecNormDiff6Tile, %function
VC1_DecNormDiff6Tile:
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
	ldr	r9, [r1]
	mov	r8, r1
	mov	r5, r0
	mov	r6, #0
.L479:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	subs	r7, r0, #0
	mov	r0, r5
	bne	.L488
	bl	BsGet
	mov	r4, r0
	cmp	r4, #1
	mov	r1, r0
	mov	r0, r5
	bgt	.L498
	bne	.L482
	bl	BsGet
	cmp	r0, #0
	beq	.L483
	cmp	r6, #0
	mov	r6, r4
	beq	.L479
.L496:
	str	r9, [r8]
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L488:
	mov	r0, #0
.L480:
	cmp	r6, #0
	mov	r7, #1
	eorne	r0, r0, #63
.L497:
	str	r0, [r8]
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L498:
	sub	r4, r4, #2
	mov	r0, #1
	mov	r0, r0, asl r4
	b	.L480
.L482:
	mov	r0, r5
	mov	r1, #4
	bl	BsGet
	cmp	r0, #255
	beq	.L496
	ldr	r3, .L499
	add	r3, r3, r0, lsl #2
	ldr	r0, [r3, #508]
	b	.L480
.L483:
	mov	r0, r5
	mov	r1, #5
	bl	BsGet
	ldr	r3, .L499
	add	r3, r3, r0, lsl #2
	ldr	r3, [r3, #380]
	cmp	r3, #2
	orreq	r0, r0, #32
	beq	.L480
	cmp	r3, #3
	bne	.L497
	b	.L480
.L500:
	.align	2
.L499:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VC1_DecNormDiff6Tile, .-VC1_DecNormDiff6Tile
	.align	2
	.global	VC1_Vfmw_ParseSMPIPicHdr
	.type	VC1_Vfmw_ParseSMPIPicHdr, %function
VC1_Vfmw_ParseSMPIPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #7
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	mov	r1, #5
	strb	r0, [r4, #253]
	mov	r0, r6
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #254]
	cmp	r5, #0
	beq	.L502
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L517
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #340]
	movhi	r3, #0
	strhib	r3, [r4, #255]
	bls	.L514
.L505:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L515
.L507:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L516
.L509:
	ldrb	r3, [r4, #251]	@ zero_extendqisi2
	sub	r3, r3, #2
	tst	r3, #253
	bne	.L510
.L512:
	ldrb	r1, [r4, #258]	@ zero_extendqisi2
.L511:
	mov	r0, r8
	mov	r5, #1
	bl	VC1_SetCurPicResolutionInfo
	mov	r0, r6
	bl	VC1_DecTransacfrm
	strb	r0, [r4, #267]
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #268]
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #269]
.L502:
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L510:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L512
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #258]
	b	.L511
.L514:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L505
.L515:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L507
.L516:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L509
.L518:
	.align	2
.L517:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseSMPIPicHdr, .-VC1_Vfmw_ParseSMPIPicHdr
	.align	2
	.global	VC1_Vfmw_ParseSMPPPicHdr
	.type	VC1_Vfmw_ParseSMPPPicHdr, %function
VC1_Vfmw_ParseSMPPPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r7, r1
	mov	r1, #5
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #254]
	cmp	r6, #0
	beq	.L532
	ldrb	r8, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L549
	sub	r0, fp, #164
	bl	memcpy
	cmp	r8, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #340]
	movhi	r3, #0
	strhib	r3, [r4, #255]
	bls	.L543
.L524:
	cmp	r8, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L544
.L526:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L545
.L528:
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L529
	ldrb	r1, [r4, #258]	@ zero_extendqisi2
.L530:
	mov	r0, r7
	bl	VC1_SetCurPicResolutionInfo
	mov	r0, r5
	bl	BsPos
	ldr	r1, .L549+4
	mov	r2, r0
	mov	r0, #18
	bl	dprint_vfmw
	ldrb	r1, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #259]
	cmp	r0, #4
	beq	.L546
.L531:
	mov	r1, r7
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L532
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #263]
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #264]
	bne	.L547
.L533:
	mov	r0, r5
	bl	BsPos
	ldr	r1, .L549+8
	mov	r2, r0
	mov	r0, #18
	bl	dprint_vfmw
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L548
.L535:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #267]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #269]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L532:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L543:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L524
.L547:
	add	r3, r4, #272
	ldrb	r2, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L533
.L545:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L528
.L529:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #258]
	b	.L530
.L544:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L526
.L546:
	ldrb	r1, [r4, #340]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmode2
	mov	r1, #6
	strb	r0, [r4, #260]
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #261]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #262]
	b	.L531
.L548:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #265]
	cmp	r0, #1
	bne	.L535
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #266]
	b	.L535
.L550:
	.align	2
.L549:
	.word	.LANCHOR0+568
	.word	.LC40
	.word	.LC41
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseSMPPPicHdr, .-VC1_Vfmw_ParseSMPPPicHdr
	.align	2
	.global	VC1_Vfmw_ParseMPBPicHdr
	.type	VC1_Vfmw_ParseMPBPicHdr, %function
VC1_Vfmw_ParseMPBPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #5
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #254]
	cmp	r5, #0
	beq	.L562
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L579
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #340]
	movhi	r3, #0
	strhib	r3, [r4, #255]
	bls	.L574
.L556:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #256]
	beq	.L575
.L558:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #257]
	beq	.L576
.L560:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r3, #0
	mov	r1, r8
	mov	r2, r4
	cmp	r0, r3
	mov	r0, r6
	moveq	ip, #3
	movne	ip, #1
	strb	ip, [r4, #259]
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L562
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #263]
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #264]
	bne	.L577
.L563:
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L578
.L565:
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #267]
	mov	r0, r6
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #269]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L562:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L574:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	strb	r0, [r4, #255]
	b	.L556
.L577:
	add	r3, r4, #272
	ldrb	r2, [r4, #340]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_VopDQuant
	b	.L563
.L575:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #256]
	b	.L558
.L576:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #257]
	b	.L560
.L578:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #265]
	cmp	r0, #1
	bne	.L565
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #266]
	b	.L565
.L580:
	.align	2
.L579:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseMPBPicHdr, .-VC1_Vfmw_ParseMPBPicHdr
	.align	2
	.global	VC1_Vfmw_ParseSMPPicHdr
	.type	VC1_Vfmw_ParseSMPPicHdr, %function
VC1_Vfmw_ParseSMPPicHdr:
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
	ldrb	r7, [r2, #258]	@ zero_extendqisi2
	mov	r5, r0
	mov	r6, r1
	mov	r0, r1
	mov	r4, r2
	mov	r1, r7
	bl	VC1_SetCurPicResolutionInfo
	ldr	r3, [r5, #16]
	cmp	r3, #1
	ble	.L619
	ldr	r9, .L624
	mov	r2, #100
	mov	r1, #0
	add	r0, r4, #248
	add	r8, r6, #32768
	ldr	r3, [r9, #48]
	blx	r3
	add	r0, r6, #24064
	ldr	r3, [r9, #48]
	mov	r2, #12288
	mov	r1, #0
	add	r0, r0, #24
	strb	r7, [r4, #258]
	blx	r3
	ldr	r2, [r8, #3608]
	ldr	r1, .L624+4
	mov	r0, #18
	bl	dprint_vfmw
	mov	r0, r5
	bl	BsPos
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r4, #324]
	bne	.L584
	ldrb	r2, [r4, #248]	@ zero_extendqisi2
.L585:
	ldr	r1, .L624+8
	mov	r0, #18
	bl	dprint_vfmw
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #12]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #249]
	bne	.L620
.L586:
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	mov	r1, #1
	mov	r0, r5
	cmp	r3, #0
	bne	.L587
	bl	BsGet
	adds	r0, r0, #0
	movne	r0, #1
	strb	r0, [r4, #251]
.L588:
	mov	r3, #0
	strb	r0, [r6, #2]
	strb	r3, [r6, #4]
	ldrb	r3, [r4, #251]	@ zero_extendqisi2
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L600
.L593:
	.word	.L592
	.word	.L594
	.word	.L595
	.word	.L600
	.word	.L596
.L596:
	ldrb	r7, [r6, #3112]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L621
.L600:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L619:
	mov	r3, #5
	mov	r0, #1
	strb	r3, [r4, #251]
	strb	r3, [r6, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L587:
	bl	BsGet
	cmp	r0, #1
	beq	.L617
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	beq	.L622
	mov	r2, r4
	mov	r3, #2
	add	r1, r4, #344
	strb	r3, [r2, #251]!
	mov	r0, r5
	bl	VC1_DecBfractionSMP
	uxtb	r0, r0
	strb	r0, [r4, #252]
	cmp	r0, #21
	ldrneb	r0, [r4, #251]	@ zero_extendqisi2
	bne	.L588
	b	.L600
.L584:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r2, r0
	strb	r2, [r4, #248]
	b	.L585
.L622:
	mov	r0, #0
.L617:
	strb	r0, [r4, #251]
	b	.L588
.L595:
	ldrb	r7, [r6, #3112]	@ zero_extendqisi2
	cmp	r7, #1
	bne	.L600
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseMPBPicHdr
	cmp	r0, #1
	mov	r6, r0
	beq	.L597
	mov	r0, r7
	ldr	r1, .L624+12
	bl	dprint_vfmw
	b	.L597
.L594:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPPPicHdr
	mov	r6, r0
.L597:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #324]
	rsb	r0, r3, r0
	str	r0, [r4, #324]
	mov	r0, r5
	ldr	r4, [r8, #3632]
	bl	BsPos
	mov	r4, r4, asl #3
	rsb	r0, r0, r4
	cmp	r0, #0
	ble	.L623
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L592:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPIPicHdr
	mov	r6, r0
	b	.L597
.L620:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #250]
	b	.L586
.L623:
	ldr	r1, .L624+16
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L621:
	mov	r1, r6
	mov	r2, r4
	mov	r0, r5
	bl	VC1_Vfmw_ParseSMPIPicHdr
	cmp	r0, #1
	mov	r6, r0
	beq	.L597
	mov	r0, r7
	ldr	r1, .L624+20
	bl	dprint_vfmw
	b	.L597
.L625:
	.align	2
.L624:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC42
	.word	.LC43
	.word	.LC44
	.word	.LC46
	.word	.LC45
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseSMPPicHdr, .-VC1_Vfmw_ParseSMPPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvSeqHdr
	.type	VC1_Vfmw_ParseAdvSeqHdr, %function
VC1_Vfmw_ParseAdvSeqHdr:
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
	ldr	r3, .L643
	mov	r5, r0
	mov	r4, r2
	mov	r1, #0
	add	r0, r2, #16
	mov	r2, #172
	ldr	r3, [r3, #48]
	mov	r6, #2
	blx	r3
	mov	r0, r5
	bl	BsPos
	mov	r1, r6
	str	r0, [r4, #184]
	mov	r0, r5
	bl	BsGet
	strb	r6, [r4, #16]
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	strb	r0, [r4, #17]
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #18]
	mov	r0, r5
	bl	BsGet
	mov	r1, #5
	strb	r0, [r4, #19]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #20]
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	strb	r0, [r4, #21]
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	uxth	r3, r0
	mov	r0, r5
	add	r3, r3, #1
	mov	r3, r3, asl #1
	strh	r3, [r4, #172]	@ movhi
	bl	BsGet
	mov	r1, #1
	uxth	r3, r0
	mov	r0, r5
	add	r3, r3, r1
	mov	r3, r3, asl r1
	strh	r3, [r4, #174]	@ movhi
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #22]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #23]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #24]
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	strb	r0, [r4, #25]
	mov	r0, r5
	bl	BsSkip
	mov	r0, r5
	mov	r1, #1
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #26]
	cmp	r6, #1
	beq	.L640
	ldrh	r2, [r4, #172]
	ldrh	r3, [r4, #174]
	strh	r2, [r4, #176]	@ movhi
	strh	r3, [r4, #178]	@ movhi
.L633:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #39]
	cmp	r0, #1
	beq	.L634
.L636:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #184]
	mov	r2, #1
	rsb	r0, r3, r0
	str	r0, [r4, #184]
.L635:
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L634:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #40]
	cmp	r0, #31
	movhi	r2, #0
	bhi	.L635
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	mov	r1, #4
	strb	r0, [r4, #41]
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #42]
	ble	.L636
	add	r7, r4, #42
	mov	r6, #0
.L637:
	mov	r1, #16
	mov	r0, r5
	bl	BsGet
	mov	r1, #16
	add	r6, r6, #1
	strh	r0, [r7, #2]!	@ movhi
	mov	r0, r5
	bl	BsGet
	strh	r0, [r7, #64]	@ movhi
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, r6
	bgt	.L637
	b	.L636
.L640:
	mov	r1, #14
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	add	r3, r0, #1
	mov	r0, r5
	strh	r3, [r4, #176]	@ movhi
	bl	BsGet
	mov	r1, r6
	add	r3, r0, #1
	mov	r0, r5
	strh	r3, [r4, #178]	@ movhi
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #27]
	cmp	r0, #1
	beq	.L641
.L629:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r1, r0
	strb	r1, [r4, #31]
	cmp	r1, #1
	beq	.L642
.L631:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #35]
	cmp	r0, #1
	bne	.L633
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #36]
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #37]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #38]
	b	.L633
.L642:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #32]
	cmp	r0, #0
	bne	.L632
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #4
	strb	r0, [r4, #33]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #34]
	b	.L631
.L641:
	mov	r1, #4
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #28]
	cmp	r0, #15
	bne	.L629
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	mov	r1, #8
	strb	r0, [r4, #29]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #30]
	b	.L629
.L632:
	mov	r1, #16
	mov	r0, r5
	bl	BsGet
	strh	r0, [r4, #180]	@ movhi
	b	.L631
.L644:
	.align	2
.L643:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvSeqHdr, .-VC1_Vfmw_ParseAdvSeqHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvEntptHdr
	.type	VC1_Vfmw_ParseAdvEntptHdr, %function
VC1_Vfmw_ParseAdvEntptHdr:
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
	ldr	r3, .L670
	mov	r4, r2
	mov	r5, r0
	mov	r1, #0
	add	r0, r2, #188
	mov	r2, #60
	ldr	r3, [r3, #48]
	blx	r3
	mov	r0, r5
	bl	BsPos
	mov	r1, #1
	str	r0, [r4, #244]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #188]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #189]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #190]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #191]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #192]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #193]
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #194]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #195]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #196]
	mov	r0, r5
	bl	BsGet
	mov	r1, #2
	strb	r0, [r4, #197]
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #39]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #198]
	beq	.L646
.L649:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #199]
	cmp	r0, #1
	ldrneh	r2, [r4, #240]
	beq	.L666
.L651:
	ldrh	r1, [r4, #238]
	ldrh	r0, [r4, #172]
	cmp	r1, #15
	movhi	r3, #0
	movls	r3, #1
	cmp	r1, r0
	orrhi	r3, r3, #1
	ldrb	r1, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #0
	ldrh	r3, [r4, #174]
	strneh	r0, [r4, #238]	@ movhi
	cmp	r3, r2
	cmpcs	r2, #15
	strlsh	r3, [r4, #240]	@ movhi
	cmp	r1, #1
	beq	.L667
.L654:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #201]
	cmp	r0, #1
	beq	.L668
.L655:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #203]
	cmp	r0, #1
	beq	.L669
.L656:
	mov	r0, r5
	bl	BsPos
	ldr	r3, [r4, #244]
	rsb	r3, r3, r0
	mov	r0, #1
	str	r3, [r4, #244]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L646:
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, #0
	ble	.L649
	add	r7, r4, #204
	mov	r6, #0
.L650:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	add	r6, r6, #1
	strb	r0, [r7, #1]!
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	cmp	r3, r6
	bgt	.L650
	b	.L649
.L669:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #204]
	b	.L656
.L666:
	mov	r1, #12
	mov	r0, r5
	bl	BsGet
	mov	r1, #12
	add	r3, r0, #1
	mov	r0, r5
	mov	r3, r3, asl #1
	strh	r3, [r4, #238]	@ movhi
	bl	BsGet
	add	r0, r0, #1
	mov	r2, r0, asl #1
	uxth	r2, r2
	strh	r2, [r4, #240]	@ movhi
	b	.L651
.L667:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #200]
	b	.L654
.L668:
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #202]
	b	.L655
.L671:
	.align	2
.L670:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvEntptHdr, .-VC1_Vfmw_ParseAdvEntptHdr
	.align	2
	.global	VC1_DecFcm
	.type	VC1_DecFcm, %function
VC1_DecFcm:
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
	mov	r1, #2
	mov	r5, r0
	bl	BsShow
	mov	r4, r0
	cmp	r4, #1
	mov	r0, r5
	ble	.L675
	mov	r1, #2
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L675:
	mov	r1, #1
	mov	r4, #0
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_DecFcm, .-VC1_DecFcm
	.align	2
	.global	VC1_DecAdvPtype
	.type	VC1_DecAdvPtype, %function
VC1_DecAdvPtype:
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
	mov	r1, #4
	mov	r4, r0
	bl	BsShow
	cmp	r0, #7
	movle	r1, #1
	movle	r5, r1
	ble	.L677
	cmp	r0, #11
	movle	r1, #2
	movle	r5, r1
	bgt	.L682
.L677:
	mov	r0, r4
	bl	BsSkip
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L682:
	cmp	r0, #13
	movle	r1, #3
	movle	r5, #0
	ble	.L677
	cmp	r0, #14
	mov	r1, #4
	movne	r5, #5
	moveq	r5, r1
	b	.L677
	UNWIND(.fnend)
	.size	VC1_DecAdvPtype, .-VC1_DecAdvPtype
	.align	2
	.global	VC1_Vfmw_ParseAdvIPicHdr
	.type	VC1_Vfmw_ParseAdvIPicHdr, %function
VC1_Vfmw_ParseAdvIPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #1
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	ldrb	r1, [r4, #23]	@ zero_extendqisi2
	cmp	r1, #1
	strb	r0, [r4, #348]
	beq	.L699
.L684:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	bne	.L685
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L700
.L685:
	mov	r1, #5
	mov	r0, r6
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #358]
	cmp	r5, #0
	beq	.L694
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L704
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L701
.L690:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L702
.L692:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L703
.L693:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r6
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L694
	mov	r0, r6
	bl	VC1_DecTransacfrm
	strb	r0, [r4, #370]
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #371]
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #372]
	moveq	r0, #1
	beq	.L687
	mov	r0, r6
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	bl	VC1_VopDQuant
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L694:
	mov	r0, #0
.L687:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L701:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L690
.L700:
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #357]
	b	.L685
.L699:
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #356]
	b	.L684
.L702:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L692
.L703:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L693
.L705:
	.align	2
.L704:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvIPicHdr, .-VC1_Vfmw_ParseAdvIPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvPPicHdr
	.type	VC1_Vfmw_ParseAdvPPicHdr, %function
VC1_Vfmw_ParseAdvPPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #1
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #348]
	beq	.L707
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L707
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L744
.L709:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L724
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L757
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L745
.L714:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L746
.L716:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L747
.L717:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L748
.L718:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	beq	.L749
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strneb	r3, [r4, #373]
	beq	.L750
.L722:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #374]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r4, #468]
	beq	.L751
.L723:
	mov	r3, #0
	strb	r3, [r4, #382]
.L720:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L724
	ldr	r1, [r4, #392]
	cmp	r1, #2
	beq	.L752
.L725:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #392]
	cmp	r3, #0
	moveq	r1, #2
	movne	r1, #3
	strb	r0, [r4, #366]
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #392]
	cmp	r6, #2
	uxtb	r0, r0
	strb	r0, [r4, #367]
	beq	.L753
.L728:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L754
.L730:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L755
.L732:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #372]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L724:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L707:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	strb	r0, [r4, #356]
	bne	.L709
.L744:
	ldr	r2, [r4, #392]
	cmp	r2, #0
	bne	.L709
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #357]
	b	.L709
.L749:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #362]
	cmp	r0, #4
	bne	.L720
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmode2
	mov	r1, #6
	strb	r0, [r4, #363]
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #364]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #365]
	b	.L720
.L745:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L714
.L754:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L730
.L748:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L718
.L746:
	mov	r1, r7
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L716
.L747:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L717
.L755:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L732
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L732
.L753:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #374]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #376]
	movne	r0, #0
	beq	.L756
.L729:
	strb	r0, [r4, #377]
	b	.L728
.L752:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #375]
	b	.L725
.L750:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L722
.L751:
	mov	r1, #6
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #364]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #365]
	b	.L723
.L756:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	b	.L729
.L758:
	.align	2
.L757:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvPPicHdr, .-VC1_Vfmw_ParseAdvPPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvBPicHdr
	.type	VC1_Vfmw_ParseAdvBPicHdr, %function
VC1_Vfmw_ParseAdvBPicHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r7, r1
	mov	r1, #1
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #348]
	beq	.L760
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L760
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L802
.L762:
	cmp	r3, #0
	bne	.L766
	add	r1, r4, #496
	mov	r0, r5
	bl	VC1_DecBfraction
	uxtb	r0, r0
	strb	r0, [r4, #350]
	cmp	r0, #21
	beq	.L764
.L766:
	mov	r1, #5
	mov	r0, r5
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L764
	ldrb	r8, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L814
	sub	r0, fp, #164
	bl	memcpy
	cmp	r8, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L803
	cmp	r8, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L804
.L772:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L805
.L773:
	ldr	r3, [r4, #392]
	cmp	r3, #2
	beq	.L806
.L774:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L807
.L775:
	ldr	r3, [r4, #392]
	cmp	r3, #0
	beq	.L808
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L809
.L779:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #468]
.L778:
	mov	r1, r7
	mov	r3, #0
	mov	r2, r4
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L764
	ldr	r1, [r4, #392]
	cmp	r1, #2
	beq	.L810
.L780:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #392]
	cmp	r3, #0
	moveq	r1, #2
	movne	r1, #3
	strb	r0, [r4, #366]
	mov	r0, r5
	bl	BsGet
	ldr	r6, [r4, #392]
	cmp	r6, #2
	uxtb	r0, r0
	strb	r0, [r4, #367]
	beq	.L811
.L783:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L812
.L784:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L813
.L786:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #372]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L764:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L760:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r1, [r4, #25]	@ zero_extendqisi2
	ldr	r3, [r4, #392]
	cmp	r1, #1
	strb	r0, [r4, #356]
	bne	.L762
.L802:
	cmp	r3, #0
	bne	.L766
	mov	r0, r5
	bl	BsGet
	ldr	r3, [r4, #392]
	strb	r0, [r4, #357]
	b	.L762
.L808:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	moveq	r3, #3
	movne	r3, #1
	strb	r3, [r4, #362]
	b	.L778
.L803:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r8, [r4, #198]	@ zero_extendqisi2
	cmp	r8, #1
	movne	r3, #0
	strb	r0, [r4, #351]
	strneb	r3, [r4, #359]
	bne	.L772
.L804:
	mov	r1, r8
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L772
.L806:
	add	r1, r4, #496
	mov	r0, r5
	bl	VC1_DecBfraction
	strb	r0, [r4, #350]
	b	.L774
.L807:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L775
.L805:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L773
.L812:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L784
.L813:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L786
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L786
.L811:
	mov	r1, r6
	mov	r0, r5
	bl	BsGet
	mov	r1, r6
	strb	r0, [r4, #376]
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #377]
	b	.L783
.L810:
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #375]
	b	.L780
.L809:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L779
.L815:
	.align	2
.L814:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvBPicHdr, .-VC1_Vfmw_ParseAdvBPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvFramePicHdr
	.type	VC1_Vfmw_ParseAdvFramePicHdr, %function
VC1_Vfmw_ParseAdvFramePicHdr:
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
	mov	r6, r1
	mov	r1, #4
	mov	r4, r2
	mov	r5, r0
	bl	BsShow
	cmp	r0, #7
	movle	r7, #1
	movle	r1, r7
	ble	.L817
	cmp	r0, #11
	movle	r7, #2
	movle	r1, r7
	bgt	.L848
.L817:
	mov	r0, r5
	bl	BsSkip
	strb	r7, [r4, #349]
	ldrb	r3, [r6, #3513]	@ zero_extendqisi2
	strb	r3, [r6, #2]
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L849
.L818:
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	beq	.L819
	cmp	r3, #0
	beq	.L850
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #352]
	mov	r0, r5
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #353]
	beq	.L851
.L823:
	cmp	r3, #1
	bne	.L825
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	ldrb	r3, [r4, #354]	@ zero_extendqisi2
	cmp	r1, #1
	add	r3, r3, #1
	str	r3, [r4, #492]
	bne	.L834
.L826:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #355]
	cmp	r0, #1
	bne	.L834
	ldr	r3, [r4, #492]
	cmp	r3, #0
	ble	.L834
	mov	r7, r4
	mov	r8, #0
.L835:
	mov	r1, #18
	mov	r0, r5
	bl	BsGet
	mov	r1, #18
	add	r8, r8, #1
	add	r7, r7, #4
	str	r0, [r7, #396]
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #412]
	mov	r0, r5
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #428]
	mov	r0, r5
	bl	BsGet
	str	r0, [r7, #444]
	ldr	r3, [r4, #492]
	cmp	r3, r8
	bgt	.L835
	b	.L834
.L819:
	mov	r2, #1
	cmp	r3, r2
	strb	r2, [r4, #352]
	beq	.L822
.L825:
	mov	r3, #1
	str	r3, [r4, #492]
.L824:
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L826
.L834:
	ldrb	r3, [r4, #349]	@ zero_extendqisi2
	cmp	r3, #5
	ldrls	pc, [pc, r3, asl #2]
	b	.L827
.L829:
	.word	.L832
	.word	.L830
	.word	.L831
	.word	.L827
	.word	.L832
	.word	.L840
.L832:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvIPicHdr
.L850:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #354]
	bne	.L823
.L851:
	cmp	r3, #1
	beq	.L852
.L822:
	mov	r3, #2
	str	r3, [r4, #492]
	b	.L824
.L848:
	cmp	r0, #13
	movle	r7, #0
	movle	r1, #3
	ble	.L817
	cmp	r0, #14
	moveq	r7, #4
	movne	r7, #5
	movne	r1, #4
	moveq	r1, r7
	b	.L817
.L849:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	str	r0, [r4, #396]
	b	.L818
.L840:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L830:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvPPicHdr
.L831:
	mov	r2, r4
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvBPicHdr
.L827:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L852:
	ldrb	r3, [r4, #353]	@ zero_extendqisi2
	add	r3, r3, #2
	str	r3, [r4, #492]
	b	.L824
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvFramePicHdr, .-VC1_Vfmw_ParseAdvFramePicHdr
	.align	2
	.global	VC1_DecRefdist
	.type	VC1_DecRefdist, %function
VC1_DecRefdist:
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
	mov	r1, #5
	mov	r5, r0
	bl	BsShow
	cmp	r0, #23
	bgt	.L854
	mov	r4, r0, asr #3
	mov	r1, #2
	mov	r0, r5
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L854:
	cmp	r0, #27
	movle	r4, #3
	bgt	.L860
.L856:
	mov	r0, r5
	mov	r1, r4
	bl	BsSkip
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L860:
	cmp	r0, #29
	movgt	r4, #5
	movle	r4, #4
	b	.L856
	UNWIND(.fnend)
	.size	VC1_DecRefdist, .-VC1_DecRefdist
	.align	2
	.global	VC1_DecIntCompField
	.type	VC1_DecIntCompField, %function
VC1_DecIntCompField:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	ldr	lr, .L862
	mov	r4, r0
	sub	ip, fp, #52
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	mov	r0, r4
	mov	r1, #2
	bl	BsShow
	sub	r3, fp, #20
	add	r3, r3, r0, lsl #3
	mov	r0, r4
	ldr	r1, [r3, #-28]
	ldr	r4, [r3, #-32]
	bl	BsSkip
	mov	r0, r4
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L863:
	.align	2
.L862:
	.word	.LANCHOR0+696
	UNWIND(.fnend)
	.size	VC1_DecIntCompField, .-VC1_DecIntCompField
	.align	2
	.global	VC1_Vfmw_ParseAdvIFieldHdr
	.type	VC1_Vfmw_ParseAdvIFieldHdr, %function
VC1_Vfmw_ParseAdvIFieldHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r8, r1
	mov	r1, #5
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #358]
	cmp	r5, #0
	beq	.L873
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L881
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #36
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L878
.L869:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L879
.L871:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L880
.L872:
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	mov	r0, r6
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L873
	mov	r0, r6
	bl	VC1_DecTransacfrm
	strb	r0, [r4, #370]
	mov	r0, r6
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #371]
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #372]
	moveq	r0, #1
	beq	.L866
	mov	r0, r6
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	bl	VC1_VopDQuant
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L873:
	mov	r0, #0
.L866:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L878:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L869
.L879:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L871
.L880:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L872
.L882:
	.align	2
.L881:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvIFieldHdr, .-VC1_Vfmw_ParseAdvIFieldHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvPFieldHdr
	.type	VC1_Vfmw_ParseAdvPFieldHdr, %function
VC1_Vfmw_ParseAdvPFieldHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #128)
	sub	sp, sp, #128
	mov	r1, #5
	mov	r4, r2
	mov	r6, r0
	bl	BsGet
	uxtb	r5, r0
	strb	r5, [r4, #358]
	cmp	r5, #0
	beq	.L884
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L921
	sub	r0, fp, #156
	bl	memcpy
	cmp	r7, #0
	mov	r3, r5
	subeq	r3, fp, #28
	addeq	r3, r3, r5, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r5, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L912
.L887:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L913
.L889:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L914
.L890:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #380]
	cmp	r0, #0
	beq	.L915
.L891:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L916
.L892:
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L917
.L893:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_DecMvmodeProgrP
	uxtb	r0, r0
	strb	r0, [r4, #362]
	cmp	r0, #4
	beq	.L918
.L895:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #380]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r1, #2
	movne	r1, #3
	strb	r0, [r4, #375]
	mov	r0, r6
	bl	BsGet
	mov	r1, #3
	uxtb	r0, r0
	strb	r0, [r4, #366]
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #362]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #367]
	beq	.L899
	movw	r3, #362
	ldrh	r3, [r4, r3]
	cmp	r3, #4
	beq	.L899
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L919
.L901:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L920
.L903:
	mov	r0, r6
	mov	r5, #1
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #372]
.L884:
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L899:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	strb	r0, [r4, #377]
	beq	.L901
.L919:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_VopDQuant
	b	.L901
.L915:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	clz	r0, r0
	mov	r0, r0, lsr #5
	strb	r0, [r4, #381]
	b	.L891
.L912:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L887
.L916:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L892
.L917:
	mov	r0, r6
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L893
.L913:
	mov	r1, r7
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L889
.L920:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L903
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L903
.L914:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L890
.L918:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r6
	bl	VC1_DecMvmode2
	strb	r0, [r4, #363]
	mov	r0, r6
	bl	VC1_DecIntCompField
	mov	r1, #6
	str	r0, [r4, #476]
	mov	r0, r6
	bl	BsGet
	mov	r1, #6
	strb	r0, [r4, #364]
	mov	r0, r6
	bl	BsGet
	ldr	r3, [r4, #476]
	cmp	r3, #0
	strb	r0, [r4, #365]
	bne	.L895
	mov	r1, #6
	mov	r0, r6
	bl	BsGet
	mov	r1, #6
	str	r0, [r4, #480]
	mov	r0, r6
	bl	BsGet
	str	r0, [r4, #484]
	b	.L895
.L922:
	.align	2
.L921:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvPFieldHdr, .-VC1_Vfmw_ParseAdvPFieldHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvBFieldHdr
	.type	VC1_Vfmw_ParseAdvBFieldHdr, %function
VC1_Vfmw_ParseAdvBFieldHdr:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r3, #1
	mov	r8, r1
	strb	r3, [r2, #380]
	mov	r1, #5
	mov	r4, r2
	mov	r5, r0
	bl	BsGet
	uxtb	r6, r0
	strb	r6, [r4, #358]
	cmp	r6, #0
	beq	.L934
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	mov	r2, #128
	ldr	r1, .L954
	sub	r0, fp, #164
	bl	memcpy
	cmp	r7, #0
	mov	r3, r6
	subeq	r3, fp, #36
	addeq	r3, r3, r6, lsl #2
	ldreq	r3, [r3, #-128]
	cmp	r6, #8
	str	r3, [r4, #464]
	movhi	r3, #0
	strhib	r3, [r4, #351]
	bls	.L946
.L928:
	cmp	r7, #1
	movne	r3, #0
	strneb	r3, [r4, #359]
	beq	.L947
.L930:
	ldrb	r3, [r4, #21]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L948
.L931:
	ldrb	r3, [r4, #194]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L949
.L932:
	ldrb	r3, [r4, #200]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L950
.L933:
	ldrb	r1, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_DecMvmodeInterB
	mov	r1, r8
	mov	r3, #0
	mov	r2, r4
	strb	r0, [r4, #362]
	mov	r0, r5
	bl	BPD_Drv
	cmp	r0, #1
	beq	.L934
	mov	r1, #3
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #375]
	mov	r0, r5
	bl	BsGet
	mov	r1, #3
	strb	r0, [r4, #366]
	mov	r0, r5
	bl	BsGet
	ldrb	r3, [r4, #362]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #367]
	beq	.L951
.L935:
	ldrb	r1, [r4, #195]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L952
.L936:
	ldrb	r1, [r4, #196]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L953
.L938:
	mov	r0, r5
	bl	VC1_DecTransacfrm
	mov	r1, #1
	strb	r0, [r4, #370]
	mov	r0, r5
	bl	BsGet
	mov	r3, #1
	strb	r0, [r4, #372]
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L934:
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L946:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	ldrb	r7, [r4, #198]	@ zero_extendqisi2
	strb	r0, [r4, #351]
	b	.L928
.L952:
	add	r3, r4, #508
	ldrb	r2, [r4, #464]	@ zero_extendqisi2
	mov	r0, r5
	bl	VC1_VopDQuant
	b	.L936
.L951:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #377]
	b	.L935
.L948:
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #360]
	b	.L931
.L949:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #361]
	b	.L932
.L947:
	mov	r1, r7
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #359]
	b	.L930
.L950:
	mov	r0, r5
	bl	VC1_DecMvrange
	strb	r0, [r4, #373]
	b	.L933
.L953:
	mov	r0, r5
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #368]
	cmp	r0, #1
	bne	.L938
	mov	r1, #2
	mov	r0, r5
	bl	BsGet
	strb	r0, [r4, #369]
	b	.L938
.L955:
	.align	2
.L954:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvBFieldHdr, .-VC1_Vfmw_ParseAdvBFieldHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvFieldPicHdr
	.type	VC1_Vfmw_ParseAdvFieldPicHdr, %function
VC1_Vfmw_ParseAdvFieldPicHdr:
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
	ldrb	r3, [r1, #8]	@ zero_extendqisi2
	mov	r5, r1
	mov	r6, r0
	mov	r4, r2
	cmp	r3, #0
	beq	.L957
	add	r3, r1, #20480
	ldr	r3, [r3, #3604]
	cmp	r3, #0
	bne	.L957
	ldr	r3, [r2, #504]
	strb	r3, [r2, #349]
	ldrb	r3, [r1, #3513]	@ zero_extendqisi2
	strb	r3, [r1, #2]
.L975:
	ldrb	r3, [r4, #349]	@ zero_extendqisi2
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L984
.L979:
	.word	.L978
	.word	.L980
	.word	.L981
	.word	.L984
	.word	.L978
.L957:
	mov	r1, #3
	mov	r0, r6
	bl	BsGet
	ldr	r3, .L1003
	str	r0, [r4, #472]
	add	r0, r3, r0, lsl #3
	ldr	r3, [r0, #732]
	ldr	r2, [r0, #728]
	str	r3, [r4, #504]
	str	r2, [r4, #500]
	ldrb	r1, [r5, #8]	@ zero_extendqisi2
	cmp	r1, #0
	uxtbeq	r3, r2
	uxtbne	r3, r3
	strb	r3, [r4, #349]
	ldrb	r3, [r5, #3513]	@ zero_extendqisi2
	strb	r3, [r5, #2]
	ldrb	r3, [r4, #24]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L996
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	bne	.L997
.L962:
	mov	r2, #1
	cmp	r3, r2
	strb	r2, [r4, #352]
	beq	.L965
.L968:
	mov	r3, #1
	str	r3, [r4, #492]
.L967:
	ldrb	r1, [r4, #190]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L969
.L972:
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #348]
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #191]	@ zero_extendqisi2
	cmp	r3, #1
	strb	r0, [r4, #356]
	beq	.L998
.L971:
	ldr	r3, [r4, #472]
	cmp	r3, #3
	ble	.L975
.L976:
	add	r1, r4, #496
	mov	r0, r6
	bl	VC1_DecBfraction
	strb	r0, [r4, #350]
	b	.L975
.L997:
	cmp	r3, #0
	beq	.L999
	mov	r1, #1
	mov	r0, r6
	bl	BsGet
	mov	r1, #1
	strb	r0, [r4, #352]
	mov	r0, r6
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #353]
	beq	.L1000
.L966:
	cmp	r3, #1
	bne	.L968
	ldrb	r3, [r4, #354]	@ zero_extendqisi2
	add	r3, r3, #1
	str	r3, [r4, #492]
	b	.L967
.L981:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvBFieldHdr
.L977:
	ldrb	r3, [r4, #352]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	bne	.L1001
.L982:
	subs	r3, r3, #1
	movne	r3, #1
	strb	r3, [r4, #389]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L980:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvPFieldHdr
	ldrb	r3, [r4, #352]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r5, #8]	@ zero_extendqisi2
	beq	.L982
.L1001:
	adds	r3, r3, #0
	movne	r3, #1
	strb	r3, [r4, #389]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L978:
	mov	r0, r6
	mov	r2, r4
	mov	r1, r5
	bl	VC1_Vfmw_ParseAdvIFieldHdr
	b	.L977
.L996:
	mov	r1, #8
	mov	r0, r6
	bl	BsGet
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	ldrb	r3, [r4, #23]	@ zero_extendqisi2
	str	r0, [r4, #396]
	beq	.L962
	b	.L997
.L999:
	mov	r1, #2
	mov	r0, r6
	bl	BsGet
	ldrb	r2, [r4, #23]	@ zero_extendqisi2
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r2, #1
	strb	r0, [r4, #354]
	bne	.L966
.L1000:
	cmp	r3, #1
	beq	.L1002
.L965:
	mov	r3, #2
	str	r3, [r4, #492]
	b	.L967
.L984:
	mov	r0, #0
	b	.L977
.L998:
	ldr	r3, [r4, #472]
	cmp	r3, #3
	bgt	.L976
	mov	r0, r6
	bl	VC1_DecRefdist
	strb	r0, [r4, #379]
	b	.L971
.L969:
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #355]
	cmp	r0, #1
	bne	.L972
	ldr	r3, [r4, #492]
	cmp	r3, #0
	ble	.L972
	mov	r7, r4
	mov	r8, #0
.L973:
	mov	r1, #18
	mov	r0, r6
	bl	BsGet
	mov	r1, #18
	add	r8, r8, #1
	add	r7, r7, #4
	str	r0, [r7, #396]
	mov	r0, r6
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #412]
	mov	r0, r6
	bl	BsGet
	mov	r1, #14
	str	r0, [r7, #428]
	mov	r0, r6
	bl	BsGet
	str	r0, [r7, #444]
	ldr	r3, [r4, #492]
	cmp	r3, r8
	bgt	.L973
	b	.L972
.L1002:
	ldrb	r3, [r4, #353]	@ zero_extendqisi2
	add	r3, r3, #2
	str	r3, [r4, #492]
	b	.L967
.L1004:
	.align	2
.L1003:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvFieldPicHdr, .-VC1_Vfmw_ParseAdvFieldPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvPicHdr
	.type	VC1_Vfmw_ParseAdvPicHdr, %function
VC1_Vfmw_ParseAdvPicHdr:
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
	mov	r4, r1
	mov	r6, r0
	mov	r1, #0
	mov	r0, r4
	mov	r5, r2
	bl	VC1_SetCurPicResolutionInfo
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1006
	add	r3, r4, #20480
	ldr	r3, [r3, #3604]
	cmp	r3, #0
	beq	.L1015
.L1006:
	ldrb	r8, [r5, #23]	@ zero_extendqisi2
	cmp	r8, #1
	movne	r3, #0
	movne	r0, r3
	beq	.L1016
.L1008:
	str	r0, [r5, #392]
.L1007:
	cmp	r3, #0
	mov	r2, r5
	mov	r1, r4
	mov	r0, r6
	beq	.L1017
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvFieldPicHdr
.L1015:
	ldr	r3, [r5, #392]
	bic	r3, r3, #2
	b	.L1007
.L1017:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvFramePicHdr
.L1016:
	mov	r1, #2
	mov	r0, r6
	bl	BsShow
	cmp	r0, #1
	mov	r7, r0
	ble	.L1018
	mov	r1, #2
	mov	r0, r6
	bl	BsSkip
	bic	r3, r7, #2
	mov	r0, r7
	b	.L1008
.L1018:
	mov	r1, r8
	mov	r0, r6
	bl	BsSkip
	mov	r3, #0
	mov	r0, r3
	b	.L1008
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvPicHdr, .-VC1_Vfmw_ParseAdvPicHdr
	.align	2
	.global	VC1_Vfmw_ParseAdvSlcHdr
	.type	VC1_Vfmw_ParseAdvSlcHdr, %function
VC1_Vfmw_ParseAdvSlcHdr:
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
	add	r3, r1, #20480
	mov	r7, r1
	mov	r1, #9
	mov	r5, r2
	ldr	r4, [r3, #3604]
	mov	r6, r0
	bl	BsGet
	mov	r1, #1
	mov	r3, r4, asl #4
	sub	r4, r3, r4, asl #2
	add	r4, r5, r4
	add	r4, r4, #520
	str	r0, [r4, #8]
	mov	r0, r6
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r4, #4]
	cmp	r0, #1
	beq	.L1021
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1021:
	add	lr, r5, #188
	add	ip, r7, #6912
	add	ip, ip, #36
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	add	r0, r7, #6720
	add	r1, r5, #16
	mov	r2, #172
	add	r0, r0, #56
	bl	memcpy
	add	r0, r7, #7104
	add	r1, r5, #348
	mov	r2, #176
	add	r0, r0, #4
	bl	memcpy
	add	r2, r7, #6720
	mov	r0, r6
	add	r2, r2, #40
	mov	r1, r7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvPicHdr
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvSlcHdr, .-VC1_Vfmw_ParseAdvSlcHdr
	.align	2
	.global	VC1_Vfmw_next_start_code
	.type	VC1_Vfmw_next_start_code, %function
VC1_Vfmw_next_start_code:
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
	cmp	r6, #3
	subgt	r6, r6, #3
	movgt	r4, #0
	bgt	.L1025
	b	.L1026
.L1031:
	bl	BsSkip
	cmp	r4, r6
	beq	.L1026
.L1025:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L1031
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1026:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_next_start_code, .-VC1_Vfmw_next_start_code
	.align	2
	.global	VC1_Vfmw_UserData
	.type	VC1_Vfmw_UserData, %function
VC1_Vfmw_UserData:
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
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_UserData, .-VC1_Vfmw_UserData
	.align	2
	.global	VC1_RecordSlcStream
	.type	VC1_RecordSlcStream, %function
VC1_RecordSlcStream:
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
	add	r9, r0, #20480
	ldr	r3, [r0, #3128]
	mov	r5, r0
	ldr	r6, [r9, #3604]
	movw	ip, #24096
	str	r1, [fp, #-48]
	movw	r0, #24088
	movw	lr, #24104
	mov	r8, r6, asl #4
	mov	r7, r6, asl #6
	rsb	r4, r8, r7
	add	r4, r5, r4
	add	r1, r4, #24064
	strb	r6, [r4, ip]
	add	ip, r1, #24
	str	ip, [fp, #-52]
	mov	r10, r1
	str	ip, [fp, #-56]
	ldr	ip, [r3, #24]
	add	r2, r2, ip, lsr #3
	str	r2, [r4, r0]
	ldr	r2, [r3, #24]
	and	r2, r2, #7
	str	r2, [r4, lr]
	ldr	r2, [r3, #16]
	ldr	r3, [r3, #24]
	rsb	r3, r3, r2, lsl #3
	str	r3, [r1, #44]
	ldr	r0, [r4, r0]
	bl	MEM_Vir2Phy
	add	r3, r5, #32768
	movw	r1, #24128
	add	r2, r10, #64
	str	r0, [r10, #36]
	ldr	r0, [r3, #3640]
	str	r0, [r4, r1]
	ldr	r1, [r3, #3616]
	cmp	r1, #0
	beq	.L1034
	ldr	r0, [r3, #3628]
	ldr	ip, [fp, #-52]
	cmp	r0, #0
	bne	.L1053
.L1034:
	rsb	r3, r8, r7
	movw	ip, #24120
	add	r3, r5, r3
	mov	r2, #0
	add	r4, r3, #24064
	add	lr, r4, #56
	str	r2, [r4, #28]
	str	r2, [r3, ip]
	str	r2, [r4, #60]
	str	r2, [r4, #52]
	str	r2, [r4, #68]
.L1035:
	ldr	r0, [r9, #3524]
	sub	r6, r8, r6, asl #2
	ldr	ip, [r9, #3520]
	ldrb	r4, [r5, #8]	@ zero_extendqisi2
	mul	ip, ip, r0
	cmp	r4, #0
	sub	r10, ip, #1
	beq	.L1036
	ldr	r2, [fp, #-48]
	add	r3, r0, #1
	rsb	r1, r8, r7
	movw	lr, #24112
	add	r6, r2, r6
	add	r3, r3, r3, lsr #31
	add	r1, r5, r1
	add	r6, r6, #520
	ldr	r2, [r6, #8]
	sub	r3, r2, r3, asr #1
	str	r3, [r1, lr]
	cmp	r10, r3
	movcs	ip, #0
	movcc	ip, #1
	cmp	r3, #0
	movle	ip, #0
	cmp	ip, #0
	bne	.L1054
.L1037:
	rsb	r7, r8, r7
	add	r5, r5, r7
	add	r3, r5, #24064
	add	r3, r3, #40
	ldr	r3, [r3, #4]
	cmp	r3, #0
	ble	.L1039
	add	r3, r5, #24064
	add	r3, r3, #24
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1040
	add	r5, r5, #24064
	ldr	r3, [r5, #60]
	cmp	r3, #0
	ble	.L1039
.L1040:
	ldr	r3, [r9, #3604]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r9, #3604]
.L1038:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1036:
	ldr	r3, [fp, #-48]
	rsb	r2, r8, r7
	add	r2, r5, r2
	movw	r1, #24112
	add	r6, r3, r6
	add	r6, r6, #520
	ldr	r3, [r6, #8]
	cmp	r10, r3
	str	r3, [r2, r1]
	bcs	.L1037
	ldr	r2, [r6, #8]
	mov	r0, #1
	str	r10, [sp]
	ldr	r1, .L1055
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1053:
	movw	lr, #24120
	str	r1, [ip, #4]
	mov	ip, #0
	str	ip, [r4, lr]
	ldr	ip, [r3, #3636]
	add	r1, r4, #24064
	str	r0, [r1, #52]
	mov	ip, ip, asl #3
	str	ip, [r1, #60]
	ldr	r3, [r3, #3644]
	str	r3, [r2, #4]
	b	.L1035
.L1054:
	ldr	r2, [r6, #8]
	ldr	r1, .L1055+4
	str	r0, [sp]
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1038
.L1039:
	ldr	r1, .L1055+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1056:
	.align	2
.L1055:
	.word	.LC48
	.word	.LC47
	.word	.LC49
	UNWIND(.fnend)
	.size	VC1_RecordSlcStream, .-VC1_RecordSlcStream
	.align	2
	.global	VC1_Vfmw_UpdateAdvSPS
	.type	VC1_Vfmw_UpdateAdvSPS, %function
VC1_Vfmw_UpdateAdvSPS:
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
	add	r5, r0, #8192
	movw	r3, #2402
	ldrh	r2, [r1, #238]
	mov	r4, r1
	ldrh	r3, [r5, r3]
	cmp	r3, r2
	beq	.L1058
	adds	r3, r2, #15
	add	r0, r0, #20480
	addmi	r3, r2, #30
	movw	r1, #2404
	mov	r3, r3, asr #4
	str	r3, [r0, #3520]
	ldrh	r3, [r4, #238]
	str	r3, [r0, #3536]
	ldrh	r2, [r4, #240]
	ldrh	r3, [r5, r1]
	cmp	r3, r2
	beq	.L1059
.L1060:
	adds	r3, r2, #15
	addmi	r3, r2, #30
	mov	r3, r3, asr #4
	str	r3, [r0, #3524]
	ldrh	r3, [r4, #240]
	str	r3, [r0, #3540]
.L1059:
	add	r0, r5, #2176
	add	r1, r4, #16
	mov	r2, #172
	add	r0, r0, #4
	bl	memcpy
	add	lr, r4, #188
	add	ip, r5, #2352
	mov	r4, #1
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr!, {r0, r1, r2, r3}
	stmia	ip!, {r0, r1, r2, r3}
	ldmia	lr, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
.L1063:
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1058:
	movw	r3, #2404
	ldrh	r2, [r1, #240]
	ldrh	r3, [r5, r3]
	cmp	r3, r2
	addne	r0, r0, #20480
	bne	.L1060
	mov	r4, #0
	b	.L1063
	UNWIND(.fnend)
	.size	VC1_Vfmw_UpdateAdvSPS, .-VC1_Vfmw_UpdateAdvSPS
	.align	2
	.global	VC1_Vfmw_UpdataLastPicRNDCTRL
	.type	VC1_Vfmw_UpdataLastPicRNDCTRL, %function
VC1_Vfmw_UpdataLastPicRNDCTRL:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1066
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
.L1066:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_Vfmw_UpdataLastPicRNDCTRL, .-VC1_Vfmw_UpdataLastPicRNDCTRL
	.align	2
	.global	VC1_Vfmw_DecPQUANT
	.type	VC1_Vfmw_DecPQUANT, %function
VC1_Vfmw_DecPQUANT:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #128)
	sub	sp, sp, #128
	mov	r2, #128
	mov	r4, r1
	mov	r5, r0
	ldr	r1, .L1070
	sub	r0, fp, #148
	bl	memcpy
	cmp	r5, #0
	subeq	r3, fp, #20
	movne	r0, r4
	addeq	r4, r3, r4, lsl #2
	ldreq	r0, [r4, #-128]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1071:
	.align	2
.L1070:
	.word	.LANCHOR0+568
	UNWIND(.fnend)
	.size	VC1_Vfmw_DecPQUANT, .-VC1_Vfmw_DecPQUANT
	.align	2
	.global	VC1_ClearCurPacket
	.type	VC1_ClearCurPacket, %function
VC1_ClearCurPacket:
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
	mov	r4, r1
	ldr	r1, [r1, #28]
	mov	r5, r0
	bl	SM_ReleaseStreamSeg
	ldrsb	r3, [r4, #8]
	cmp	r3, #1
	beq	.L1073
	mov	r0, r5
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
.L1073:
	ldr	r3, .L1077
	mov	r0, r4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L1078:
	.align	2
.L1077:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_ClearCurPacket, .-VC1_ClearCurPacket
	.align	2
	.global	VC1_ClearCurPic
	.type	VC1_ClearCurPic, %function
VC1_ClearCurPic:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	mov	r6, r1
	cmp	r3, #0
	beq	.L1080
	add	r7, r0, #20480
	ldr	r3, [r7, #3604]
	cmp	r3, #0
	beq	.L1094
	add	r4, r0, #24064
	mov	r5, #0
	add	r4, r4, #64
	b	.L1084
.L1083:
	ldr	r3, [r7, #3604]
	add	r4, r4, #48
	cmp	r5, r3
	bcs	.L1095
.L1084:
	ldr	r1, [r4]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #-36]
	add	r5, r5, #1
	cmp	r3, #0
	beq	.L1083
	ldr	r3, [r4, #-12]
	cmp	r3, #0
	beq	.L1083
	ldr	r1, [r4, #4]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r7, #3604]
	add	r4, r4, #48
	cmp	r5, r3
	bcc	.L1084
.L1095:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1080:
	add	r1, r0, #36352
	mov	r0, r6
	add	r1, r1, #28
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VC1_ClearCurPacket
.L1094:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_ClearCurPic, .-VC1_ClearCurPic
	.align	2
	.global	VC1DEC_VDMPostProc
	.type	VC1DEC_VDMPostProc, %function
VC1DEC_VDMPostProc:
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
	ldr	r3, [r0, #4]
	add	r4, r0, #49152
	add	r5, r0, #32768
	add	r2, r3, #12288
	mov	r7, r0
	ldrb	r3, [r3, #71]	@ zero_extendqisi2
	add	r0, r0, #12736
	mov	r6, r1
	ldr	r1, [r4, #472]
	strb	r3, [r4, #81]
	ldr	r3, [r2, #260]
	str	r3, [r4, #84]
	bl	VC1_ClearCurPic
	ldr	r1, [r5, #4044]
	ldr	r0, [r4, #472]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r5, #4040]
	mov	r8, r0
	ldr	r0, [r4, #472]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r5, #4036]
	mov	r9, r0
	ldr	r0, [r4, #472]
	bl	FSP_GetFsImagePtr
	cmp	r8, #0
	beq	.L1129
	cmp	r6, #0
	movlt	r3, #0
	blt	.L1099
	cmp	r6, #100
	movlt	r3, r6
	movge	r3, #100
.L1099:
	add	r6, r7, #12288
	str	r3, [r8, #152]
	mov	r0, r7
	bl	VC1_SetImgFormat
	ldrb	r3, [r6, #451]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L1130
.L1100:
	add	r3, r8, #560
	add	r2, r8, #544
	mov	r0, #0
	mov	r1, #0
	strd	r0, [r2]
	strd	r0, [r3, #-8]
	ldr	r3, [r7]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L1131
	ldr	r1, [r5, #4044]
	mov	r10, #0
	str	r1, [r5, #4048]
.L1104:
	add	r2, r7, #45056
	cmn	r1, #1
	ldr	r3, [r2, #4056]
	add	r3, r3, #1
	str	r3, [r2, #4056]
	beq	.L1105
	ldr	r0, [r4, #472]
	bl	FSP_GetFsImagePtr
	subs	r9, r0, #0
	beq	.L1132
	ldr	r2, [r9, #152]
	cmp	r2, #0
	beq	.L1107
	ldr	r3, [r7]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L1108
.L1107:
	ldr	r8, [r5, #4048]
	ldr	r0, [r4, #472]
	mov	r1, r8
	bl	FSP_GetRef
	mov	r2, r8
	ldr	r1, .L1136
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r5, #4048]
	ldr	r0, [r4, #472]
	bl	FSP_SetDisplay
	cmp	r10, #1
	ldreq	r3, [r5, #3960]
	movne	r1, #1
	ldrne	r2, [r5, #3952]
	movne	r3, #2
	strneb	r1, [r2, #1]
	mov	r2, r7
	streqb	r10, [r3, #1]
	mov	r1, #1
	strneb	r3, [r6, #449]
	add	r3, r7, #49152
	streqb	r10, [r6, #449]
	add	r3, r3, #120
	ldr	r0, [r4, #472]
	str	r9, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L1111
	ldr	r1, [r9, #544]
	add	r3, r9, #544
	ldr	r0, [r4, #472]
	add	r8, r9, #560
	str	r3, [fp, #-48]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-48]
	mov	r6, #0
	mov	r7, #0
	strd	r6, [r3]
	ldr	r1, [r9, #552]
	ldr	r0, [r4, #472]
	bl	FreeUsdByDec
	mov	r2, #0
	strd	r6, [r8, #-8]
	ldr	r0, [r4, #472]
	ldr	r1, [r5, #4048]
	bl	FSP_SetDisplay
	cmp	r10, #1
	mov	r3, #0
	ldreq	r2, [r5, #3960]
	mov	r0, r3
	ldrne	r2, [r5, #3952]
	strb	r3, [r2, #1]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1131:
	ldrb	r10, [r6, #450]	@ zero_extendqisi2
	sub	r10, r10, #2
	ands	r10, r10, #253
	bne	.L1133
	ldr	r1, [r5, #4044]
	cmp	r9, #0
	moveq	r10, r9
	str	r1, [r5, #4048]
	beq	.L1104
	add	ip, r9, #592
	add	r0, r8, #592
	ldrd	r2, [ip, #-8]
	ldrd	r8, [r0, #-8]
	cmp	r2, r8
	sbcs	lr, r3, r9
	strltd	r2, [r0, #-8]
	strltd	r8, [ip, #-8]
	ldrlt	r1, [r5, #4048]
	b	.L1104
.L1134:
	ldr	r2, [r5, #3956]
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r6, #449]
.L1105:
	mov	r0, #1
.L1098:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1130:
	ldrb	r3, [r6, #457]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1105
	b	.L1100
.L1133:
	ldr	r9, [r5, #4032]
	cmp	r9, #1
	ldrhi	r1, [r5, #4036]
	mvnls	r1, #0
	cmp	r9, #1
	str	r1, [r5, #4048]
	movls	r10, #0
	movhi	r10, #1
	b	.L1104
.L1111:
	ldrb	r3, [r6, #449]	@ zero_extendqisi2
	sxtb	r3, r3
	cmp	r3, #3
	beq	.L1134
	cmp	r3, #1
	beq	.L1135
	cmp	r3, #2
	bne	.L1105
	ldr	r2, [r5, #3952]
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r6, #449]
	b	.L1098
.L1108:
	ldr	r1, .L1136+4
	mov	r0, #1
	add	ip, r9, #544
	str	ip, [fp, #-48]
	bl	dprint_vfmw
	ldr	r1, [r9, #544]
	ldr	r0, [r4, #472]
	add	r8, r9, #560
	bl	FreeUsdByDec
	ldr	ip, [fp, #-48]
	mov	r6, #0
	mov	r7, #0
	strd	r6, [ip]
	ldr	r1, [r9, #552]
	ldr	r0, [r4, #472]
	bl	FreeUsdByDec
	strd	r6, [r8, #-8]
	mov	r2, #0
	ldr	r0, [r4, #472]
	ldr	r1, [r5, #4048]
	bl	FSP_SetDisplay
	cmp	r10, #1
	mov	r2, #0
	ldreq	r3, [r5, #3960]
	moveq	r0, r10
	ldrne	r3, [r5, #3952]
	movne	r0, #1
	strb	r2, [r3, #1]
	b	.L1098
.L1135:
	ldr	r2, [r5, #3960]
	mov	r0, r3
	mov	r3, #0
	strb	r3, [r2, #1]
	strb	r3, [r6, #449]
	b	.L1098
.L1129:
	str	r0, [sp]
	mov	r3, r9
	mov	r2, r8
	ldr	r1, .L1136+8
	mov	r0, r8
	bl	dprint_vfmw
	mov	r0, r8
	b	.L1098
.L1132:
	mov	r2, #644
	ldr	r1, .L1136+12
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r9
	b	.L1098
.L1137:
	.align	2
.L1136:
	.word	.LC52
	.word	.LC53
	.word	.LC50
	.word	.LC51
	UNWIND(.fnend)
	.size	VC1DEC_VDMPostProc, .-VC1DEC_VDMPostProc
	.align	2
	.global	VC1_Vfmw_DecodeArbiter
	.type	VC1_Vfmw_DecodeArbiter, %function
VC1_Vfmw_DecodeArbiter:
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
	add	r5, r0, #12288
	mov	r4, r0
	ldrb	r3, [r5, #448]	@ zero_extendqisi2
	tst	r3, #16
	beq	.L1191
	add	r6, r0, #49152
	bic	r3, r3, #20
	strb	r3, [r5, #448]
	ldr	r3, [r6, #76]
	sub	r3, r3, #2
	cmp	r3, #1
	bls	.L1141
.L1143:
	ldr	r3, [r4]
	add	r7, r4, #32768
	ldr	r1, [r7, #4032]
	ldr	r2, [r3, #8]
.L1142:
	sub	r3, r2, #1
	str	r2, [r6, #76]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L1172
.L1153:
	.word	.L1147
	.word	.L1149
	.word	.L1171
	.word	.L1151
.L1170:
	mov	r1, #0
.L1151:
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	cmp	r3, #0
	streq	r3, [r6, #8]
	moveq	r3, #1
	beq	.L1154
	cmp	r3, #2
	bne	.L1156
	ldr	r3, [r6, #8]
	adds	r3, r3, #0
	movne	r3, #1
	cmp	r1, #0
	bne	.L1158
.L1157:
	ldr	r1, .L1193
	mov	r0, #1
	bl	dprint_vfmw
.L1165:
	add	r0, r4, #12736
	ldr	r1, [r6, #472]
	bl	VC1_ClearCurPic
	ldr	r3, .L1193+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1191
	mov	r3, #0
	ldr	r0, [r6, #472]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L1191:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1141:
	ldr	r3, [r0]
	ldr	r2, [r3, #8]
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L1143
	add	r7, r0, #32768
	ldr	r1, .L1193+8
	mov	r0, #2
	bl	dprint_vfmw
	ldr	r1, [r7, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L1144
	ldr	r1, [r8, #544]
	add	r9, r8, #560
	ldr	r0, [r6, #472]
	add	r10, r8, #576
	bl	FreeUsdByDec
	ldr	r1, [r8, #552]
	ldr	r0, [r6, #472]
	add	r3, r8, #544
	str	r3, [fp, #-48]
	bl	FreeUsdByDec
	ldr	r1, [r8, #560]
	ldr	r0, [r6, #472]
	bl	FreeUsdByDec
	ldr	r1, [r8, #568]
	ldr	r0, [r6, #472]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-48]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r10, #-8]
	ldr	r1, [r7, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r7, #4036]
	ldr	r0, [r6, #472]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	str	r3, [r7, #4036]
	str	r3, [r7, #4040]
	ldr	r0, [r6, #472]
	bl	FSP_GetNullLogicFs
	str	r0, [r7, #4040]
	str	r0, [r7, #4036]
.L1144:
	ldr	r2, [r7, #3956]
	mov	r3, #0
	str	r3, [r7, #4032]
	cmp	r2, r3
	beq	.L1152
	ldr	r1, [r7, #3960]
	cmp	r1, #0
	beq	.L1152
	strb	r3, [r2, #1]
	ldr	r2, [r7, #3960]
	strb	r3, [r2, #1]
	ldr	r2, [r7, #3956]
	strb	r3, [r2]
	ldr	r2, [r7, #3960]
	strb	r3, [r2]
	ldr	r3, [r4]
	ldr	r1, [r7, #4032]
	ldr	r2, [r3, #8]
	b	.L1142
.L1171:
	mov	r3, #0
.L1154:
	cmp	r1, #0
	beq	.L1150
.L1158:
	cmp	r1, #1
	bls	.L1192
.L1161:
	cmp	r3, #0
	beq	.L1165
	ldrb	r3, [r5, #3544]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1164
	add	r3, r5, #3600
	add	ip, r4, #23040
	add	r3, r3, #12
	add	ip, ip, #52
	ldmia	r3, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	add	r1, r5, #3856
	add	r0, r4, #23296
	add	r1, r1, #4
	mov	r2, #100
	add	r0, r0, #44
	bl	memcpy
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1167:
	mov	r1, #0
.L1147:
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	sub	r3, r3, #2
	tst	r3, #253
	movne	r3, #1
	moveq	r3, #0
	cmp	r1, #0
	bne	.L1158
.L1150:
	ldrb	r2, [r5, #450]	@ zero_extendqisi2
	sub	r0, r2, #4
	sub	r1, r2, #1
	cmp	r1, #1
	cmphi	r0, #1
	bls	.L1157
.L1159:
	sub	r2, r2, #2
	tst	r2, #253
	bne	.L1161
	ldr	r1, .L1193+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1165
.L1168:
	mov	r1, #0
.L1149:
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	b	.L1154
.L1164:
	add	r1, r5, #3616
	add	r0, r4, #23040
	add	r1, r1, #12
	mov	r2, #172
	add	r0, r0, #68
	add	r6, r4, #20480
	bl	memcpy
	add	ip, r5, #3792
	add	ip, ip, #8
	add	lr, r6, #2800
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip!, {r0, r1, r2, r3}
	stmia	lr!, {r0, r1, r2, r3}
	ldmia	ip, {r0, r1, r2}
	stmia	lr, {r0, r1, r2}
	add	r1, r5, #3952
	add	r0, r6, #2960
	add	r1, r1, #8
	mov	r2, #176
	bl	memcpy
	ldr	r3, [r5, #4004]
	ldr	r2, .L1193+16
	add	r1, r4, #16384
	add	r0, r4, #23552
	add	r1, r1, #40
	strb	r3, [r5, #452]
	add	r0, r0, #64
	ldr	r3, [r7, #4052]
	ldr	ip, [r2, #52]
	mov	r2, r3, asl #4
	sub	r2, r2, r3, asl #2
	blx	ip
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1166:
	mov	r1, #0
.L1172:
	mov	r3, #1
	b	.L1154
.L1156:
	and	r3, r3, #251
	cmp	r3, #1
	bne	.L1172
	str	r3, [r6, #8]
	b	.L1154
.L1152:
	ldr	r3, [r4]
	ldr	r2, [r3, #8]
	sub	r3, r2, #1
	str	r2, [r6, #76]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L1166
.L1148:
	.word	.L1167
	.word	.L1168
	.word	.L1169
	.word	.L1170
.L1169:
	mov	r3, #0
	b	.L1150
.L1192:
	ldrb	r2, [r5, #450]	@ zero_extendqisi2
	b	.L1159
.L1194:
	.align	2
.L1193:
	.word	.LC55
	.word	g_event_report
	.word	.LC54
	.word	.LC56
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_DecodeArbiter, .-VC1_Vfmw_DecodeArbiter
	.align	2
	.global	VC1_Vfmw_StartDecode
	.type	VC1_Vfmw_StartDecode, %function
VC1_Vfmw_StartDecode:
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
	ldr	r3, [r0]
	add	r5, r0, #12288
	mov	r4, r0
	add	r6, r0, #12736
	ldrb	r1, [r5, #3544]	@ zero_extendqisi2
	add	r8, r0, #8
	ldr	r2, [r3, #592]
	cmp	r1, #0
	str	r2, [r5, #268]
	ldr	r3, [r3, #644]
	str	r3, [r5, #272]
	beq	.L1210
.L1196:
	add	r7, r4, #32768
	mov	r1, r8
	mov	r0, r4
	bl	VC1_WritePicMsg
	ldr	r3, [r7, #4052]
	ldr	ip, .L1215
	add	r1, r6, #24064
	add	r1, r1, #24
	add	r0, r4, #92
	mov	r2, r3, asl #6
	strb	r3, [r4, #78]
	sub	r2, r2, r3, asl #4
	ldr	r3, [ip, #52]
	blx	r3
	mov	r1, r8
	mov	r0, r6
	bl	VC1_CfgVDH
	ldrb	r3, [r5, #450]	@ zero_extendqisi2
	cmp	r3, #1
	ldrlsb	r2, [r5, #452]	@ zero_extendqisi2
	strlsb	r2, [r5, #453]
	cmp	r3, #5
	beq	.L1211
	mov	r3, #0
	strb	r3, [r4, #9]
	ldrb	r3, [r5, #452]	@ zero_extendqisi2
	ldrb	r2, [r5, #456]	@ zero_extendqisi2
.L1199:
	strb	r3, [r4, #8]
	strb	r3, [r5, #451]
	strb	r2, [r5, #457]
	ldrb	r3, [r4, #11]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1212
	and	r2, r3, #251
	cmp	r2, #1
	addeq	r1, r4, #49152
	streq	r2, [r1, #8]
.L1201:
	ldr	r2, [r4]
	str	r8, [r4, #4]
	ldr	r0, [r2, #880]
	cmp	r0, #1
	beq	.L1213
	cmp	r0, #2
	beq	.L1214
.L1206:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1214:
	ldr	r2, [r2, #884]
	cmp	r8, #0
	cmpne	r2, #0
	ble	.L1206
	sub	r3, r3, #2
	ands	r5, r3, #253
	bne	.L1206
	ldr	r3, [r7, #3952]
	add	r1, r4, #49152
	mov	r0, r6
	strb	r5, [r3, #1]
	ldr	r2, [r4]
	ldr	r3, [r2, #884]
	sub	r3, r3, #1
	str	r3, [r2, #884]
	ldr	r1, [r1, #472]
	bl	VC1_ClearCurPic
	str	r5, [r4, #4]
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1212:
	add	r9, r4, #49152
	ldr	r5, [r9, #8]
	cmp	r5, #0
	bne	.L1201
	mov	r0, r6
	ldr	r1, [r9, #472]
	bl	VC1_ClearCurPic
	ldr	r3, [r7, #3952]
	mov	r0, r5
	strb	r5, [r3]
	ldr	r3, [r9, #12]
	add	r3, r3, #1
	str	r3, [r9, #12]
	str	r5, [r4, #4]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1211:
	mov	r2, #1
	strb	r2, [r4, #9]
	ldrb	r3, [r5, #453]	@ zero_extendqisi2
	add	r1, r4, #49152
	strb	r2, [r5, #456]
	strb	r3, [r5, #452]
	ldr	r1, [r1, #32]
	sub	r1, r1, #1
	str	r1, [r5, #172]
	b	.L1199
.L1213:
	cmp	r8, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	sub	r3, r3, #2
	ands	r5, r3, #253
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r2, [r7, #3952]
	add	r3, r4, #49152
	mov	r0, r6
	strb	r5, [r2, #1]
	ldr	r1, [r3, #472]
	bl	VC1_ClearCurPic
	str	r5, [r4, #4]
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1210:
	mov	r0, r6
	bl	VC1_Vfmw_UpdataLastPicRNDCTRL.part.5
	b	.L1196
.L1216:
	.align	2
.L1215:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	VC1_Vfmw_StartDecode, .-VC1_Vfmw_StartDecode
	.align	2
	.global	VC1_Vfmw_ParseAdvHdr
	.type	VC1_Vfmw_ParseAdvHdr, %function
VC1_Vfmw_ParseAdvHdr:
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
	ldr	r5, [r0, #3128]
	add	r8, r0, #32768
	mov	r4, r0
	str	r1, [fp, #-52]
	mov	r10, #0
	mov	r1, #32
	strb	r10, [r0, #6]
	mov	r0, r5
	str	r2, [fp, #-48]
	bl	BsGet
	ldr	r3, [r5, #24]
	ldr	r6, [r8, #3612]
	add	r7, r4, #36352
	ldr	r2, [r8, #3632]
	add	r7, r7, #28
	mov	r3, r3, lsr #3
	add	r6, r6, r3
	rsb	r2, r3, r2
	mov	r1, r6
	uxtb	r9, r0
	mov	r0, r5
	bl	BsInit
	sub	r2, r9, #10
	cmp	r2, #5
	bhi	.L1218
	cmp	r9, #11
	ldrb	r3, [r4]	@ zero_extendqisi2
	beq	.L1287
	and	r1, r3, #7
	cmp	r1, #7
	beq	.L1288
	add	r9, r4, #20480
	strb	r10, [r4, #8]
	str	r10, [r9, #3604]
	cmp	r2, #5
	ldrls	pc, [pc, r2, asl #2]
	b	.L1250
.L1234:
	.word	.L1233
	.word	.L1250
	.word	.L1235
	.word	.L1251
	.word	.L1237
	.word	.L1238
.L1218:
	sub	r2, r9, #27
	cmp	r2, #4
	bls	.L1289
	cmp	r9, #254
	beq	.L1290
.L1250:
	ldr	r0, [fp, #-48]
	mov	r1, r7
	bl	VC1_ClearCurPacket
	mov	r0, #0
.L1223:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1289:
	ldr	r0, [fp, #-48]
	mov	r1, r7
	bl	VC1_ClearCurPacket
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1287:
	and	r3, r3, #7
	cmp	r3, #7
	beq	.L1291
.L1248:
	ldr	r0, [fp, #-48]
	mov	r1, r7
	bl	VC1_ClearCurPacket
	mov	r0, r10
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1251:
	ldr	r10, .L1294
.L1280:
	ldr	r0, [fp, #-52]
	mov	r2, #176
	ldr	ip, [r10, #48]
	mov	r1, #0
	add	r0, r0, #348
	ldrb	r3, [r0, #31]	@ zero_extendqisi2
	str	r3, [fp, #-56]
	blx	ip
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-56]
	strb	r3, [r2, #379]
.L1239:
	add	r0, r4, #24064
	ldr	r3, [r10, #48]
	mov	r2, #12288
	mov	r1, #0
	add	r0, r0, #24
	blx	r3
	mov	r0, r5
	bl	BsPos
	ldr	r3, [fp, #-52]
	mov	r1, r4
	mov	r2, r3
	str	r0, [r3, #488]
	mov	r0, r5
	bl	VC1_Vfmw_ParseAdvPicHdr
	cmp	r0, #1
	mov	r10, r0
	beq	.L1292
	mov	r1, r7
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	movw	r2, #6001
	ldr	r1, .L1294+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1223
.L1290:
	mov	r1, #32
	mov	r0, r5
	bl	BsGet
	mov	r1, #32
	mov	r6, r0
	mov	r0, r5
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r6, r3
	bne	.L1250
	add	r3, r4, #20480
	mov	r2, #1
	strb	r2, [r4, #7]
	ldr	r3, [r3, #3604]
	cmp	r3, #0
	moveq	r0, r2
	beq	.L1223
	ldrb	r3, [r4]	@ zero_extendqisi2
	mov	r0, r2
	strb	r2, [r4, #6]
	orr	r3, r3, #16
	strb	r3, [r4]
	b	.L1223
.L1288:
	mov	r10, #1
	orr	r3, r3, #16
	strb	r10, [r4, #6]
	mov	r0, r10
	strb	r3, [r4]
	b	.L1223
.L1235:
	ldr	r10, .L1294
	mov	r3, #1
	strb	r3, [r4, #8]
	mov	r2, #16
	ldr	r3, [fp, #-52]
	mov	r1, #0
	add	r0, r3, #508
	ldr	r3, [r10, #48]
	blx	r3
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1239
	b	.L1280
.L1238:
	ldr	r2, [fp, #-52]
	mov	r0, r5
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvSeqHdr
	cmp	r0, #1
	mov	r10, r0
	ldreqb	r3, [r4]	@ zero_extendqisi2
	orreq	r3, r3, #1
	streqb	r3, [r4]
	b	.L1248
.L1237:
	mov	r0, r5
	ldr	r2, [fp, #-52]
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvEntptHdr
	cmp	r0, #1
	mov	r10, r0
	bne	.L1248
	ldr	r1, [fp, #-52]
	mov	r0, r4
	bl	VC1_Vfmw_UpdateAdvSPS
	ldrb	r3, [r4]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r4]
	b	.L1248
.L1233:
	orr	r3, r3, #32
	ldr	r0, [fp, #-48]
	mov	r1, r7
	strb	r3, [r4]
	bl	VC1_ClearCurPacket
	mov	r0, #1
	b	.L1223
.L1291:
	mov	r0, r5
	ldr	r2, [fp, #-52]
	mov	r1, r4
	bl	VC1_Vfmw_ParseAdvSlcHdr
	cmp	r0, #1
	mov	r5, r0
	bne	.L1221
	add	r9, r4, #20480
	ldr	r7, [r9, #3604]
	cmp	r7, #255
	bhi	.L1293
	mov	r3, r7, asl #4
	mov	r2, r7, asl #6
	rsb	r5, r3, r2
	str	r3, [fp, #-48]
	ldr	r3, [r4, #3128]
	add	r5, r4, r5
	str	r2, [fp, #-56]
	movw	r2, #24096
	strb	r7, [r5, r2]
	movw	ip, #24088
	ldr	r1, [r3, #24]
	movw	r0, #24104
	add	r2, r5, #24064
	add	r1, r6, r1, lsr #3
	str	r1, [r5, ip]
	ldr	r1, [r3, #24]
	mov	r6, r2
	and	r1, r1, #7
	str	r1, [r5, r0]
	ldr	r1, [r3, #16]
	ldr	r0, [r3, #24]
	add	r3, r2, #24
	str	r3, [fp, #-60]
	rsb	r1, r0, r1, lsl #3
	str	r1, [r2, #44]
	ldr	r0, [r5, ip]
	str	r3, [fp, #-64]
	bl	MEM_Vir2Phy
	movw	r1, #24128
	add	r2, r6, #64
	str	r0, [r6, #36]
	ldr	r0, [r8, #3640]
	str	r0, [r5, r1]
	ldr	r1, [r8, #3616]
	cmp	r1, #0
	beq	.L1224
	ldr	r0, [r8, #3628]
	ldr	r3, [fp, #-60]
	cmp	r0, #0
	beq	.L1224
	movw	ip, #24120
	str	r1, [r3, #4]
	str	r10, [r5, ip]
	add	r3, r5, #24064
	ldr	r1, [r8, #3636]
	str	r0, [r3, #52]
	mov	r1, r1, asl #3
	str	r1, [r3, #60]
	ldr	r3, [r8, #3644]
	str	r3, [r2, #4]
.L1225:
	ldr	r0, [r9, #3524]
	ldr	r1, [r9, #3520]
	ldrb	r10, [r4, #8]	@ zero_extendqisi2
	mul	r1, r1, r0
	cmp	r10, #0
	sub	r1, r1, #1
	beq	.L1226
	ldr	r2, [fp, #-48]
	add	r3, r0, #1
	ldr	lr, [fp, #-52]
	movw	r5, #24112
	sub	ip, r2, r7, asl #2
	add	r3, r3, r3, lsr #31
	add	ip, lr, ip
	ldr	lr, [fp, #-56]
	add	ip, ip, #520
	rsb	lr, r2, lr
	ldr	r2, [ip, #8]
	add	lr, r4, lr
	sub	r3, r2, r3, asr #1
	cmp	r1, r3
	str	r3, [lr, r5]
	movcs	r1, #0
	movcc	r1, #1
	cmp	r3, #0
	movle	r1, #0
	cmp	r1, #0
	bne	.L1281
.L1227:
	ldr	r3, [fp, #-56]
	ldr	r2, [fp, #-48]
	rsb	r3, r2, r3
	add	r4, r4, r3
.L1286:
	add	r3, r4, #24064
	add	r3, r3, #40
	ldr	r3, [r3, #4]
	cmp	r3, #0
	ble	.L1230
	add	r3, r4, #24064
	add	r3, r3, #24
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L1246
	add	r4, r4, #24064
	ldr	r3, [r4, #60]
	cmp	r3, #0
	ble	.L1230
.L1246:
	ldr	r3, [r9, #3604]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r9, #3604]
	b	.L1223
.L1292:
	mov	r0, r5
	bl	BsPos
	ldr	r2, [fp, #-52]
	ldr	r3, [r2, #488]
	rsb	r0, r3, r0
	str	r0, [r2, #488]
	ldrb	r3, [r4]	@ zero_extendqisi2
	mov	r0, r5
	orr	r3, r3, #4
	strb	r3, [r4]
	bl	BsPos
	ldr	r3, [r8, #3632]
	add	r0, r0, #32
	cmp	r0, r3, asl #3
	bge	.L1241
	ldr	r7, [r9, #3604]
	movw	r3, #24096
	ldr	r2, [r4, #3128]
	movw	ip, #24104
	mov	r1, r7, asl #6
	mov	r10, r7, asl #4
	rsb	r5, r10, r1
	str	r1, [fp, #-48]
	add	r5, r4, r5
	add	r0, r5, #24064
	strb	r7, [r5, r3]
	add	r3, r0, #32
	ldr	r1, [r2, #24]
	str	r3, [fp, #-56]
	str	r3, [fp, #-60]
	movw	r3, #24088
	add	r1, r6, r1, lsr #3
	str	r1, [r5, r3]
	ldr	r1, [r2, #24]
	add	r6, r0, #24
	and	r1, r1, #7
	str	r1, [r5, ip]
	ldr	r1, [r2, #16]
	ldr	r2, [r2, #24]
	rsb	r2, r2, r1, lsl #3
	str	r2, [r0, #44]
	ldr	r0, [r5, r3]
	bl	MEM_Vir2Phy
	ldr	r3, [fp, #-56]
	movw	r1, #24128
	add	r2, r5, #24064
	add	r2, r2, #64
	str	r0, [r3, #4]
	ldr	r3, [r8, #3640]
	str	r3, [r5, r1]
	ldr	r3, [r8, #3616]
	cmp	r3, #0
	beq	.L1242
	ldr	r1, [r8, #3628]
	cmp	r1, #0
	beq	.L1242
	movw	r0, #24120
	str	r3, [r6, #4]
	mov	ip, #0
	str	ip, [r5, r0]
	ldr	r0, [r8, #3636]
	add	r3, r5, #24064
	str	r1, [r3, #52]
	mov	r0, r0, asl #3
	str	r0, [r3, #60]
	ldr	r3, [r8, #3644]
	str	r3, [r2, #4]
.L1243:
	ldr	r0, [r9, #3524]
	ldr	r1, [r9, #3520]
	ldrb	r5, [r4, #8]	@ zero_extendqisi2
	mul	r1, r1, r0
	cmp	r5, #0
	sub	r1, r1, #1
	beq	.L1244
	ldr	r2, [fp, #-52]
	sub	ip, r10, r7, asl #2
	add	r3, r0, #1
	movw	r5, #24112
	add	ip, r2, ip
	ldr	r2, [fp, #-48]
	add	r3, r3, r3, lsr #31
	add	ip, ip, #520
	rsb	lr, r10, r2
	ldr	r2, [ip, #8]
	add	lr, r4, lr
	sub	r3, r2, r3, asr #1
	cmp	r1, r3
	str	r3, [lr, r5]
	movcs	r1, #0
	movcc	r1, #1
	cmp	r3, #0
	movle	r1, #0
	cmp	r1, #0
	bne	.L1281
.L1245:
	ldr	r3, [fp, #-48]
	rsb	r7, r10, r3
	add	r4, r4, r7
	b	.L1286
.L1221:
	mov	r1, r7
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	movw	r2, #5912
	ldr	r1, .L1294+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	b	.L1223
.L1241:
	mov	r1, r7
	ldr	r0, [fp, #-48]
	bl	VC1_ClearCurPacket
	movw	r2, #5995
	ldr	r1, .L1294+4
	mov	r0, r10
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1223
.L1242:
	ldr	r3, [fp, #-48]
	movw	ip, #24120
	mov	r2, #0
	rsb	r3, r10, r3
	add	r3, r4, r3
	add	r5, r3, #24064
	add	lr, r5, #56
	str	r2, [r5, #28]
	str	r2, [r3, ip]
	str	r2, [r5, #60]
	str	r2, [r5, #52]
	str	r2, [r5, #68]
	b	.L1243
.L1293:
	ldr	r1, [fp, #-48]
	mov	r0, r4
	bl	VC1_ClearCurPic
	ldr	r2, [r9, #3604]
	mov	r0, r5
	ldr	r1, .L1294+12
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1223
.L1224:
	ldr	r2, [fp, #-48]
	movw	ip, #24120
	ldr	r3, [fp, #-56]
	rsb	r3, r2, r3
	mov	r2, #0
	add	r3, r4, r3
	add	r5, r3, #24064
	add	lr, r5, #56
	str	r2, [r5, #28]
	str	r2, [r3, ip]
	str	r2, [r5, #60]
	str	r2, [r5, #52]
	str	r2, [r5, #68]
	b	.L1225
.L1244:
	ldr	r3, [fp, #-48]
	sub	r2, r10, r7, asl #2
	movw	ip, #24112
	rsb	r0, r10, r3
	ldr	r3, [fp, #-52]
	add	r0, r4, r0
	add	r2, r3, r2
	add	r2, r2, #520
	ldr	r3, [r2, #8]
	cmp	r1, r3
	str	r3, [r0, ip]
	bcs	.L1245
	ldr	r2, [r2, #8]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, .L1294+16
	bl	dprint_vfmw
	mov	r0, r5
	b	.L1223
.L1226:
	ldr	r3, [fp, #-48]
	movw	ip, #24112
	ldr	r0, [fp, #-56]
	sub	r2, r3, r7, asl #2
	rsb	r0, r3, r0
	ldr	r3, [fp, #-52]
	add	r0, r4, r0
	add	r2, r3, r2
	add	r2, r2, #520
	ldr	r3, [r2, #8]
	cmp	r1, r3
	str	r3, [r0, ip]
	bcs	.L1227
	ldr	r2, [r2, #8]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, .L1294+16
	bl	dprint_vfmw
	mov	r0, r10
	b	.L1223
.L1230:
	ldr	r1, .L1294+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1223
.L1281:
	ldr	r2, [ip, #8]
	ldr	r1, .L1294+24
	str	r0, [sp]
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	b	.L1223
.L1295:
	.align	2
.L1294:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC59
	.word	.LC58
	.word	.LC57
	.word	.LC48
	.word	.LC49
	.word	.LC47
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseAdvHdr, .-VC1_Vfmw_ParseAdvHdr
	.align	2
	.global	VC1_Vfmw_ParseHeader
	.type	VC1_Vfmw_ParseHeader, %function
VC1_Vfmw_ParseHeader:
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
	ldrb	r3, [r0, #3096]	@ zero_extendqisi2
	mov	r4, r0
	cmp	r3, #0
	bne	.L1297
	ldrb	r3, [r0]	@ zero_extendqisi2
	mov	r2, r1
	mov	r1, r0
	ldr	r0, [r0, #3128]
	orr	r3, r3, #3
	strb	r3, [r4]
	bl	VC1_Vfmw_ParseSMPPicHdr
	cmp	r0, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r3, [r4]	@ zero_extendqisi2
	orr	r3, r3, #20
	strb	r3, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1297:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	VC1_Vfmw_ParseAdvHdr
	UNWIND(.fnend)
	.size	VC1_Vfmw_ParseHeader, .-VC1_Vfmw_ParseHeader
	.align	2
	.global	VC1_SetCodeInfo
	.type	VC1_SetCodeInfo, %function
VC1_SetCodeInfo:
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
	add	r4, r0, #12288
	mov	r5, r0
	add	r0, r0, #15808
	ldrb	r3, [r4, #3546]	@ zero_extendqisi2
	add	r0, r0, #60
	str	r0, [r4, #3576]
	cmp	r3, #8
	strneb	r3, [r4, #459]
	moveq	r3, #6
	movne	r3, #0
	streqb	r3, [r4, #459]
	moveq	r2, #1
	strneb	r3, [r4, #460]
	ldrb	r3, [r4, #3544]	@ zero_extendqisi2
	streqb	r2, [r4, #460]
	cmp	r3, #0
	ldr	r2, [r1, #20]
	ldr	r1, [r1]
	beq	.L1305
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	BsInit
.L1305:
	bl	BsInit
	ldr	r0, [r4, #3552]
	add	r5, r5, #32768
	add	r3, r4, #3552
	adds	r2, r0, #15
	add	r3, r3, #8
	addmi	r2, r0, #30
	add	ip, r4, #3600
	add	ip, ip, #12
	mov	r2, r2, asr #4
	str	r2, [r5, #3968]
	ldr	r1, [r4, #3556]
	str	r0, [r5, #3984]
	adds	r2, r1, #15
	addmi	r2, r1, #30
	str	r1, [r5, #3988]
	mov	r2, r2, asr #4
	str	r2, [r5, #3972]
	ldmia	r3, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_SetCodeInfo, .-VC1_SetCodeInfo
	.align	2
	.global	VC1_ReceivePacket
	.type	VC1_ReceivePacket, %function
VC1_ReceivePacket:
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
	subs	r4, r1, #0
	add	r1, r0, #48896
	add	r1, r1, #220
	beq	.L1314
	ldr	r2, [r4, #8]
	add	r3, r0, #45056
	str	r2, [r3, #4072]
	ldr	r2, [r4]
	str	r2, [r3, #4060]
	ldr	r2, [r4, #12]
	str	r2, [r3, #4080]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #4068]
	ldr	r2, [r4, #16]
	str	r2, [r3, #4088]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1309
	ldr	r2, [r4, #88]
	str	r2, [r3, #4076]
	ldr	r2, [r4, #80]
	str	r2, [r3, #4064]
	ldr	r2, [r4, #92]
	str	r2, [r3, #4084]
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	strb	r2, [r3, #4069]
	ldr	r2, [r4, #96]
	str	r2, [r3, #4092]
	ldrb	r3, [r4, #85]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1315
.L1310:
	bl	VC1_SetCodeInfo
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1315:
	add	r0, r0, #49152
	ldr	r0, [r0, #472]
	bl	VC1_ClearCurPacket
	ldrb	r2, [r4, #85]	@ zero_extendqisi2
	ldr	r1, .L1316
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1309:
	mov	r2, #0
	str	r2, [r3, #4076]
	str	r2, [r3, #4064]
	str	r2, [r3, #4084]
	strb	r2, [r3, #4069]
	str	r2, [r3, #4092]
	b	.L1310
.L1314:
	ldr	r1, .L1316+4
	mov	r0, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1317:
	.align	2
.L1316:
	.word	.LC61
	.word	.LC60
	UNWIND(.fnend)
	.size	VC1_ReceivePacket, .-VC1_ReceivePacket
	.align	2
	.global	VC1DEC_Decode
	.type	VC1DEC_Decode, %function
VC1DEC_Decode:
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
	ldr	r3, .L1347
	add	r5, r0, #12544
	add	r5, r5, #32
	mov	r4, r0
	mov	r2, #160
	ldr	r3, [r3, #52]
	mov	r0, r5
	blx	r3
	mov	r1, r5
	mov	r0, r4
	bl	VC1_ReceivePacket
	subs	r6, r0, #0
	beq	.L1342
	ldr	r3, [r4]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L1343
.L1321:
	add	r3, r4, #12288
	add	r5, r4, #49152
	ldrb	r3, [r3, #448]	@ zero_extendqisi2
	strb	r3, [r5, #80]
.L1322:
	add	r7, r4, #12736
	add	r1, r4, #15872
	add	r1, r1, #28
	ldr	r2, [r5, #472]
	mov	r0, r7
	bl	VC1_Vfmw_ParseHeader
	subs	r8, r0, #0
	beq	.L1344
	mov	r0, r4
	bl	VC1_Vfmw_DecodeArbiter
	cmp	r0, #0
	bne	.L1345
.L1325:
	mov	r6, #0
.L1320:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1344:
	add	r1, r4, #48896
	ldr	r0, [r5, #472]
	add	r1, r1, #220
	bl	VC1_ClearCurPacket
	ldr	r3, .L1347+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1325
	ldr	r0, [r5, #472]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	mov	r6, r8
	blx	ip
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1343:
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L1321
	add	r5, r4, #49152
	add	r3, r4, #12288
	ldrb	r2, [r5, #80]	@ zero_extendqisi2
	strb	r2, [r3, #448]
	b	.L1322
.L1342:
	add	r4, r4, #45056
	ldr	r1, .L1347+8
	ldr	r2, [r4, #4056]
	bl	dprint_vfmw
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1345:
	mov	r0, r4
	bl	VC1_Vfmw_PrepareDecode
	subs	r6, r0, #0
	bne	.L1326
	ldr	r3, [r4]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L1346
.L1327:
	mov	r0, r7
	ldr	r1, [r5, #472]
	bl	VC1_ClearCurPic
.L1328:
	ldr	r3, .L1347+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1325
	mov	r3, #0
	ldr	r0, [r5, #472]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	b	.L1320
.L1346:
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L1327
	b	.L1328
.L1326:
	mov	r0, r4
	bl	VC1_Vfmw_StartDecode
	subs	r6, r0, #0
	movne	r6, r8
	bne	.L1320
	add	r4, r4, #32768
	mov	r2, #1
	ldr	r0, [r5, #472]
	ldr	r1, [r4, #4044]
	bl	FSP_ClearLogicFs
	ldr	r2, [r4, #3952]
	ldr	r3, .L1347+4
	strb	r6, [r2]
	ldr	r2, [r4, #3952]
	strb	r6, [r2, #1]
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1325
	ldr	r0, [r5, #472]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	ip
	b	.L1320
.L1348:
	.align	2
.L1347:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC62
	UNWIND(.fnend)
	.size	VC1DEC_Decode, .-VC1DEC_Decode
	.align	2
	.global	VC1_GetPacketState
	.type	VC1_GetPacketState, %function
VC1_GetPacketState:
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
	add	r0, r0, #12736
	ldrsb	r3, [r0, #6]
	cmp	r3, #1
	moveq	r0, #2
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	VC1_GetPacketState, .-VC1_GetPacketState
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14158, %object
	.size	__func__.14158, 13
__func__.14158:
	.ascii	"Vc1SMPSeqHdr\000"
	.space	3
.LC0:
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	3
	.word	3
.LC1:
	.word	3
	.word	1
	.word	2
	.word	0
	.word	4
.LC2:
	.word	1
	.word	0
	.word	2
	.word	3
	.word	4
.LC3:
	.word	3
	.word	1
.LC4:
	.word	3
	.word	1
	.word	2
	.word	0
.LC5:
	.word	1
	.word	0
	.word	2
	.word	3
.LC6:
	.word	1
	.word	1
	.word	2
	.word	1
	.word	3
	.word	1
	.word	2
.LC7:
	.word	2
	.word	3
	.word	3
	.word	4
	.word	4
	.word	5
	.word	5
.LC8:
	.word	3
	.word	4
	.word	1
	.word	5
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	1
	.word	3
	.word	5
	.word	7
.LC9:
	.word	5
	.word	5
	.word	6
	.word	6
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	7
	.word	8
	.word	8
	.word	8
	.word	8
.LC10:
	.word	256
	.word	128
	.word	85
	.word	64
	.word	51
	.word	43
	.word	37
	.word	32
	.type	__func__.14469, %object
	.size	__func__.14469, 17
__func__.14469:
	.ascii	"VC1_DecBfraction\000"
	.space	3
	.type	aCount, %object
	.size	aCount, 128
aCount:
	.word	0
	.word	1
	.word	1
	.word	2
	.word	1
	.word	2
	.word	2
	.word	3
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	1
	.word	2
	.word	2
	.word	3
	.word	2
	.word	3
	.word	3
	.word	4
	.word	2
	.word	3
	.word	3
	.word	4
	.word	3
	.word	4
	.word	4
	.word	5
	.type	a2On4Off, %object
	.size	a2On4Off, 60
a2On4Off:
	.word	3
	.word	5
	.word	6
	.word	9
	.word	10
	.word	12
	.word	17
	.word	18
	.word	20
	.word	24
	.word	33
	.word	34
	.word	36
	.word	40
	.word	48
.LC12:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	6
	.word	7
	.word	8
	.word	9
	.word	10
	.word	11
	.word	12
	.word	13
	.word	14
	.word	15
	.word	16
	.word	17
	.word	18
	.word	19
	.word	20
	.word	21
	.word	22
	.word	23
	.word	24
	.word	25
	.word	27
	.word	29
	.word	31
.LC11:
	.word	1
	.word	2
	.word	2
	.word	2
	.word	0
	.word	1
	.word	0
	.word	1
	.type	FldPTypeTab, %object
	.size	FldPTypeTab, 64
FldPTypeTab:
	.word	0
	.word	0
	.word	0
	.word	1
	.word	1
	.word	0
	.word	1
	.word	1
	.word	2
	.word	2
	.word	2
	.word	4
	.word	4
	.word	2
	.word	4
	.word	4
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC13:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC14:
	ASCII(.ascii	"VC1 INIT!!!\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"picture width out of range\000" )
	.space	1
.LC16:
	ASCII(.ascii	"%s: %s\012\000" )
.LC17:
	ASCII(.ascii	"picture height out of range\000" )
.LC18:
	ASCII(.ascii	"Vc1SMPSeqHdr Err, BS is wrong\000" )
	.space	2
.LC19:
	ASCII(.ascii	"Vc1SMPSeqHdr Err, BS is wrong\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC21:
	ASCII(.ascii	"vc1 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC22:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC24:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"VC1_Vfmw_GetImageBuffer get imgbuf err, clear all r" )
	ASCII(.ascii	"ef!\012\000" )
.LC27:
	ASCII(.ascii	"VC1_Vfmw_GetImageBuffer get_flag!=1, FSP_ClearLogic" )
	ASCII(.ascii	"Fs.\012\000" )
.LC28:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_ArrangeVahbMem err!\012\000" )
.LC29:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_GetImageBuffer err!" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo B pic pCodecInf->RefNum < 2 " )
	ASCII(.ascii	"err!\012\000" )
	.space	3
.LC33:
	ASCII(.ascii	"line: %d (pCur,pFwd,pBwd)(%p,%p,%p)\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo imgbuf = NULL err!\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p)\012\000" )
	.space	2
.LC36:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo VC1_Vfmw_BuildRefList err!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC37:
	ASCII(.ascii	"VC1_Vfmw_GetStreamInfo error! Release all packets!\012" )
	ASCII(.ascii	"\000" )
.LC38:
	ASCII(.ascii	"%s:%d Code(%d) is invalid\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"%s:%d Denominator(%d) is invalid\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"Check Pos 2: %d\012\000" )
	.space	3
.LC41:
	ASCII(.ascii	"Check Pos 3: %d\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"\012======PicNum  :%6d=========\012\000" )
	.space	2
.LC43:
	ASCII(.ascii	"INTERPFRM  :%#x\012\000" )
	.space	3
.LC44:
	ASCII(.ascii	"VC1_Vfmw_ParseMPBPicHdr err!\012\000" )
	.space	2
.LC45:
	ASCII(.ascii	"VC1_Vfmw_ParseSMPIPicHdr err!\012\000" )
	.space	1
.LC46:
	ASCII(.ascii	"After VC1_Vfmw_ParseSMPPicHdr BS Len <= 0 err!\012\000" )
.LC47:
	ASCII(.ascii	"SLICE_ADDR = %d,SlcEndMbn = %d, MbHeight = %d\012\000" )
	.space	1
.LC48:
	ASCII(.ascii	"SLICE_ADDR = %d,SlcEndMbn = %d, totalMbMin1 = %d\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC49:
	ASCII(.ascii	"VC1_RecordSlcStream stream len <= 0\012\000" )
	.space	3
.LC50:
	ASCII(.ascii	"pImg is null, pCurImg %p pBwdImg %p pFwdImg %p\012\000" )
.LC51:
	ASCII(.ascii	"line: %d, pToQueImg is Null!\012\000" )
	.space	2
.LC52:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC54:
	ASCII(.ascii	"----------------- VC1 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC55:
	ASCII(.ascii	"NOTE: Drop non-I\012\000" )
	.space	2
.LC56:
	ASCII(.ascii	"NOTE: Drop B\012\000" )
	.space	2
.LC57:
	ASCII(.ascii	" pCodecInf->SlcNum = %d >= 256 \012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"line %d, Code = VC1_SCSLC failed!\012\000" )
	.space	1
.LC59:
	ASCII(.ascii	"line %d, Code = VC1_SCFRM failed!\012\000" )
	.space	1
.LC60:
	ASCII(.ascii	"bitsream para error -----\012\000" )
	.space	1
.LC61:
	ASCII(.ascii	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\012\000" )
.LC62:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
