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
	.file	"syntax.c"
	.text
	.align	2
	.global	InitVoQueue
	.type	InitVoQueue, %function
InitVoQueue:
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
	ldr	r1, .L2
	mov	r4, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #0
	mov	r3, #64
	strh	r2, [r4, #2]	@ movhi
	strh	r3, [r4]	@ movhi
	mov	r0, #1
	mvn	r3, #0
	strh	r2, [r4, #4]	@ movhi
	strh	r2, [r4, #6]	@ movhi
	strh	r2, [r4, #8]	@ movhi
	str	r2, [r4, #344]
	str	r2, [r4, #316]
	str	r3, [r4, #272]
	str	r3, [r4, #292]
	str	r3, [r4, #288]
	str	r3, [r4, #284]
	str	r3, [r4, #276]
	str	r3, [r4, #280]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	UNWIND(.fnend)
	.size	InitVoQueue, .-InitVoQueue
	.align	2
	.global	PrintVoQueue
	.type	PrintVoQueue, %function
PrintVoQueue:
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
	mov	r5, r0
	ldrh	ip, [r5, #8]
	ldrh	r3, [r0, #4]
	mov	r0, #1
	ldrh	r2, [r5, #6]
	ldr	r1, .L10
	str	ip, [sp]
	bl	dprint_vfmw
	ldrh	r3, [r5, #4]
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	bne	.L8
	b	.L7
.L6:
	add	r3, r5, r4, lsl #2
	ldr	r1, .L10+4
	mov	r0, #1
	ldr	r3, [r3, #12]
	ldr	r2, [r3, #148]
	bl	dprint_vfmw
	add	r3, r4, #1
	ldrh	r2, [r5, #8]
	and	r4, r3, #63
	cmp	r2, r4
	beq	.L7
.L8:
	tst	r3, #7
	bne	.L6
	ldr	r1, .L10+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L6
.L7:
	ldr	r1, .L10+8
	mov	r0, #1
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L11:
	.align	2
.L10:
	.word	.LC1
	.word	.LC3
	.word	.LC2
	UNWIND(.fnend)
	.size	PrintVoQueue, .-PrintVoQueue
	.align	2
	.global	ResetVoQueue
	.type	ResetVoQueue, %function
ResetVoQueue:
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
	ldr	r5, .L17
	mov	r4, r0
	mov	r0, #2
	ldr	r3, [r5, #12]
	blx	r3
	ldrh	r2, [r4, #6]
	ldrh	r3, [r4, #4]
	ldrh	r1, [r4, #8]
	cmp	r2, r3
	beq	.L16
.L14:
	str	r1, [sp]
	mov	r0, #1
	ldr	r1, .L17+4
	bl	dprint_vfmw
.L15:
	ldr	r2, [r4, #344]
	add	r1, r4, #336
	mov	r3, #0
	mov	r0, #64
	strh	r3, [r4, #2]	@ movhi
	add	r2, r2, #100
	strh	r0, [r4]	@ movhi
	mvn	r8, #0
	str	r2, [r4, #344]
	mvn	r9, #0
	mvn	r2, #0
	strh	r3, [r4, #4]	@ movhi
	strh	r3, [r4, #6]	@ movhi
	mov	r6, #0
	strh	r3, [r4, #8]	@ movhi
	mov	r7, #0
	str	r3, [r4, #316]
	mov	r0, #2
	str	r2, [r4, #272]
	str	r2, [r4, #292]
	str	r2, [r4, #288]
	str	r2, [r4, #284]
	str	r2, [r4, #276]
	str	r2, [r4, #280]
	ldr	ip, [r5, #16]
	strd	r8, [r1, #-8]
	str	r3, [r4, #324]
	strd	r6, [r1]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L16:
	cmp	r2, r1
	bne	.L14
	b	.L15
.L18:
	.align	2
.L17:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC4
	UNWIND(.fnend)
	.size	ResetVoQueue, .-ResetVoQueue
	.align	2
	.global	ReturnImageToSyntax
	.type	ReturnImageToSyntax, %function
ReturnImageToSyntax:
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
	mov	r3, r1
	cmp	r0, #20
	ldrls	pc, [pc, r0, asl #2]
	b	.L19
.L22:
	.word	.L21
	.word	.L23
	.word	.L24
	.word	.L25
	.word	.L19
	.word	.L26
	.word	.L27
	.word	.L19
	.word	.L28
	.word	.L29
	.word	.L30
	.word	.L30
	.word	.L30
	.word	.L31
	.word	.L19
	.word	.L32
	.word	.L33
	.word	.L34
	.word	.L19
	.word	.L19
	.word	.L35
.L35:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	USERDEC_RecycleImage
.L21:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264DEC_RecycleImage
.L23:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1DEC_RecycleImage
.L24:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG4DEC_RecycleImage
.L25:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MPEG2DEC_RecycleImage
.L26:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DIVX3DEC_RecycleImage
.L27:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVSDEC_RecycleImage
.L28:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL8DEC_RecycleImage
.L29:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	REAL9DEC_RecycleImage
.L30:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP6DEC_RecycleImage
.L31:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP8DEC_RecycleImage
.L32:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_DEC_RecycleImage
.L33:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_DECRecycleImage
.L34:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VP9DEC_RecycleImage
.L19:
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	ReturnImageToSyntax, .-ReturnImageToSyntax
	.align	2
	.global	ProduceTimeStamp
	.type	ProduceTimeStamp, %function
ProduceTimeStamp:
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
	mov	r3, r1
	cmp	r2, #20
	add	r1, r1, #592
	ldrd	r6, [r1, #-8]
	beq	.L37
	add	r0, r0, #272
	sub	r2, r2, #8
	ldrd	r4, [r0, #56]
	subs	r0, r6, r4
	and	r4, r4, r5
	sbc	r1, r7, r5
	cmp	r1, #0
	cmpeq	r0, #5
	movls	r1, #1
	movhi	r1, #0
	adds	r4, r4, #1
	movne	r4, #1
	tst	r1, r4
	beq	.L47
	cmp	r2, #1
	mvnhi	r6, #0
	mvnhi	r7, #0
	bls	.L39
.L37:
	mov	r0, r6
	mov	r1, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L47:
	cmp	r2, #1
	bhi	.L37
	ldrb	r2, [r3, #64]	@ zero_extendqisi2
	and	r2, r2, #3
	cmp	r2, #2
	bne	.L37
.L39:
	mvn	r1, #0
	str	r1, [r3, #576]
	mov	r6, r1
	mov	r7, r1
	str	r1, [r3, #580]
	b	.L37
	UNWIND(.fnend)
	.size	ProduceTimeStamp, .-ProduceTimeStamp
	.align	2
	.global	InsertImgToVoQueue_PtsProcess
	.type	InsertImgToVoQueue_PtsProcess, %function
InsertImgToVoQueue_PtsProcess:
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
	UNWIND(.pad #16)
	sub	sp, sp, #16
	ldr	ip, .L49
	add	r4, r3, #592
	ldrb	lr, [r3, #66]	@ zero_extendqisi2
	mov	r6, r2
	add	r5, r3, #576
	ldr	ip, [ip, r0, asl #2]
	mov	r0, r6
	mov	r2, r1
	mov	r1, r3
	ldr	ip, [ip, #128]
	sub	ip, ip, #1
	clz	ip, ip
	mov	ip, ip, lsr #5
	bfi	lr, ip, #2, #1
	strb	lr, [r3, #66]
	ldrd	r6, [r4, #-8]
	strd	r6, [r5]
	bl	ProduceTimeStamp
	ldrd	r8, [r4]
	mov	r6, r0
	mov	r7, r1
	mov	r0, #29
	strd	r6, [r4, #-8]
	ldr	r1, .L49+4
	ldrd	r2, [r5]
	strd	r6, [sp]
	strd	r8, [sp, #8]
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L50:
	.align	2
.L49:
	.word	s_pstVfmwChan
	.word	.LC5
	UNWIND(.fnend)
	.size	InsertImgToVoQueue_PtsProcess, .-InsertImgToVoQueue_PtsProcess
	.align	2
	.global	InsertImgToVoQueue_FillImageInfo
	.type	InsertImgToVoQueue_FillImageInfo, %function
InsertImgToVoQueue_FillImageInfo:
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
	mov	r4, r3
	ldr	r3, [r3, #76]
	mov	r8, r0
	mov	r5, r2
	cmp	r3, #0
	beq	.L52
	ldr	r3, [r4, #80]
	cmp	r3, #0
	bne	.L77
.L52:
	ldr	r2, [r4, #68]
	ldr	r3, [r4, #72]
	mov	r1, r2, lsr #1
	str	r2, [r4, #76]
	str	r3, [r4, #80]
	mov	r3, r3, lsr #1
	str	r1, [r4, #84]
	str	r3, [r4, #88]
.L53:
	str	r2, [r5, #300]
	ldr	r3, [r4, #72]
	ldr	r1, [r5, #280]
	str	r3, [r5, #304]
	ldrb	r3, [r4, #64]	@ zero_extendqisi2
	mov	r3, r3, lsr #5
	str	r3, [r5, #308]
	ldr	r3, [r4, #64]
	str	r3, [r5, #312]
	ldr	r3, [r4, #148]
	add	r3, r3, #2
	str	r3, [r5, #296]
	ldr	r3, [r4, #156]
	ldr	r2, [r4, #64]
	cmp	r3, r1
	ldrb	r7, [r4, #65]	@ zero_extendqisi2
	ldr	r6, [r4, #80]
	ubfx	r2, r2, #14, #3
	ldr	r0, [r4, #84]
	ubfx	r7, r7, #0, #2
	ldrh	ip, [r4, #76]
	uxtb	r10, r2
	ldrh	r1, [r4, #88]
	uxtb	r9, r7
	strne	r3, [r5, #320]
	orr	r6, ip, r6, asl #16
	ldr	r3, [r5, #316]
	orr	r1, r1, r0, asl #16
	str	r1, [fp, #-56]
	add	r1, r3, #1
	str	r1, [r5, #316]
	str	r3, [r4, #160]
	ldr	r3, [r5, #272]
	cmp	r3, r10
	beq	.L55
	ldr	r1, .L79
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L56
	strb	r3, [fp, #-52]
	mov	r1, #7
	strb	r2, [fp, #-51]
	mov	r3, #2
	sub	r2, fp, #52
	mov	r0, r8
	blx	ip
.L56:
	str	r10, [r5, #272]
.L55:
	ldr	r3, [r5, #276]
	cmp	r3, r9
	beq	.L57
	ldr	r3, .L79
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L58
	sub	r2, fp, #44
	mov	r3, #1
	mov	r1, #4
	mov	r0, r8
	strb	r7, [r2, #-8]!
	blx	ip
.L58:
	str	r9, [r5, #276]
.L57:
	ldr	r3, [r5, #288]
	cmp	r3, r6
	beq	.L78
.L59:
	ldr	r3, .L79
	ldr	r2, [fp, #-56]
	str	r6, [r5, #288]
	ldr	ip, [r3]
	str	r2, [r5, #292]
	cmp	ip, #0
	beq	.L60
	ldr	r7, [r4, #76]
	mov	r0, r8
	ldr	r6, [r4, #80]
	mov	r3, #8
	ldr	r5, [r4, #84]
	sub	r2, fp, #52
	ldr	lr, [r4, #88]
	mov	r1, #1
	strh	r7, [fp, #-52]	@ movhi
	strh	r6, [fp, #-50]	@ movhi
	strh	r5, [fp, #-48]	@ movhi
	strh	lr, [fp, #-46]	@ movhi
	blx	ip
.L60:
	ldr	r0, [r4, #36]
	ldr	r1, [r4, #40]
	ldr	r2, [r4, #112]
	ldr	r3, [r4, #116]
	add	r2, r2, r0
	str	r0, [r4, #20]
	add	r3, r3, r1
	str	r1, [r4, #24]
	str	r2, [r4, #28]
	str	r3, [r4, #32]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L77:
	sub	r3, r1, #15
	cmp	r1, #0
	cmpne	r3, #1
	ldrls	r2, [r4, #68]
	bhi	.L52
	b	.L53
.L78:
	ldr	r3, [r5, #292]
	ldr	r2, [fp, #-56]
	cmp	r3, r2
	bne	.L59
	b	.L60
.L80:
	.align	2
.L79:
	.word	g_event_report
	UNWIND(.fnend)
	.size	InsertImgToVoQueue_FillImageInfo, .-InsertImgToVoQueue_FillImageInfo
	.align	2
	.global	InsertImgToVoQueue_ReportIMG
	.type	InsertImgToVoQueue_ReportIMG, %function
InsertImgToVoQueue_ReportIMG:
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
	ldr	r3, .L83
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {fp, sp, pc}
	mov	r2, r1
	mov	r3, #632
	mov	r1, #5
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L84:
	.align	2
.L83:
	.word	g_event_report
	UNWIND(.fnend)
	.size	InsertImgToVoQueue_ReportIMG, .-InsertImgToVoQueue_ReportIMG
	.global	__aeabi_uidiv
	.align	2
	.global	InsertImgToVoQueue
	.type	InsertImgToVoQueue, %function
InsertImgToVoQueue:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
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
	ldr	r10, [fp, #4]
	mov	r7, r0
	mov	r8, r1
	cmp	r10, #0
	mov	r9, r2
	mov	r5, r3
	beq	.L113
	ldr	r6, .L116
	mov	r0, #2
	ldr	r1, .L116+4
	bl	dprint_vfmw
	mov	r0, #2
	ldr	r3, [r6, #12]
	blx	r3
	ldrh	r4, [r5, #4]
	ldrh	r3, [r5, #8]
	and	r4, r4, #63
	cmp	r3, r4
	bne	.L93
	b	.L92
.L91:
	add	r4, r4, #1
	ldrh	r3, [r5, #8]
	and	r4, r4, #63
	cmp	r3, r4
	beq	.L92
.L93:
	add	ip, r5, r4, lsl #2
	ldr	r3, [r10, #148]
	ldr	r2, [ip, #12]
	ldr	r2, [r2, #148]
	cmp	r2, r3
	bne	.L91
	ldr	r1, .L116+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1000
	str	r3, [r10, #152]
	b	.L91
.L92:
	ldr	r2, [r10, #152]
	cmp	r2, #100
	bhi	.L89
	ldr	r3, [r10, #68]
	cmp	r3, #31
	bhi	.L114
.L89:
	ldr	r3, [r10, #68]
	ldr	r1, [r10, #72]
.L94:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L116+12
	bl	dprint_vfmw
	ldr	r3, [r10, #152]
	cmp	r3, #1000
	beq	.L96
	mov	r2, r10
	mov	r1, r9
	mov	r0, r8
	bl	ReturnImageToSyntax
.L96:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, #1
.L87:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L114:
	ldr	r1, [r10, #72]
	cmp	r1, #31
	bls	.L94
	add	r1, r10, #416
	mov	r0, r7
	str	r8, [r10, #216]
	bl	VCTRL_GetHDRConfigInfo
	mov	r3, r10
	mov	r2, r5
	mov	r1, r8
	mov	r0, r7
	ldr	r4, .L116+16
	bl	InsertImgToVoQueue_PtsProcess
	mov	r3, r10
	mov	r2, r5
	mov	r1, r8
	mov	r0, r7
	bl	InsertImgToVoQueue_FillImageInfo
	ldr	lr, [r10, #148]
	ldrh	ip, [r5, #8]
	mov	r0, #12
	ldrh	r3, [r5, #6]
	ldrh	r2, [r5, #4]
	ldr	r1, .L116+20
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldrh	r3, [r5, #8]
	ldr	r0, .L116+24
	mov	r2, #300
	add	r1, r3, #1
	mov	ip, #0
	add	r3, r5, r3, lsl #2
	and	r1, r1, #63
	mla	r2, r2, r7, r4
	str	r10, [r3, #12]
	strh	r1, [r5, #8]	@ movhi
	mov	r1, #5
	ldr	r3, [r0, r7, asl #2]
	mov	r0, r7
	add	r3, r3, #475136
	ldr	lr, [r3, #992]
	add	lr, lr, #1
	str	lr, [r3, #992]
	ldr	r3, [r10, #52]
	str	ip, [r10, #264]
	str	r3, [r2, #20]
	ldr	r2, [r10, #160]
	bl	VDEC_Lowdelay_Event_Time
	ldr	r1, .L116+28
	ldr	r3, [r10, #160]
	mov	r0, #2
	ldr	r2, [r6, #16]
	add	r3, r3, #1
	str	r3, [r1, r7, asl #2]
	blx	r2
	ldr	r3, .L116+32
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L97
	mov	r2, r10
	mov	r3, #632
	mov	r1, #5
	mov	r0, r7
	blx	ip
.L97:
	mov	r0, #8
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L115
.L99:
	mov	r5, #300
	ldr	r2, [r6]
	mul	r5, r5, r7
	add	r6, r4, r5
	ldr	r3, [r6, #4]
	add	r3, r3, #1
	str	r3, [r6, #4]
	blx	r2
	ldr	r1, [r4, r5]
	rsb	r1, r1, r0
	mov	r8, r0
	cmp	r1, #300
	movcc	r0, #1
	bcc	.L87
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L101
	movw	r0, #10000
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	str	r0, [r6, #8]
.L101:
	mov	r3, #300
	mov	r2, #0
	mul	r7, r3, r7
	mov	r0, #1
	add	r3, r4, r7
	str	r8, [r4, r7]
	str	r2, [r3, #4]
	b	.L87
.L115:
	ldr	r3, [r6]
	blx	r3
	ldr	ip, .L116+36
	ldr	r2, .L116+40
	ldr	r3, [ip, r7, asl #2]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	mov	lr, r0
	cmp	r3, r2
	bls	.L99
	mov	r2, r7, asl #24
	movw	r1, #517
	add	r2, r2, #524288
	ldr	r0, .L116+44
	str	lr, [ip, r7, asl #2]
	bl	DBG_AddTrace
	b	.L99
.L113:
	mov	r0, r10
	ldr	r1, .L116+48
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L87
.L117:
	.align	2
.L116:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	g_VfmwChanStat
	.word	.LC10
	.word	s_pstVfmwChan
	.word	g_LowDelaySeqIndex
	.word	g_event_report
	.word	.LANCHOR0
	.word	g_TraceFramePeriod
	.word	.LANCHOR1
	.word	.LC6
	UNWIND(.fnend)
	.size	InsertImgToVoQueue, .-InsertImgToVoQueue
	.align	2
	.global	GetQueueImgNum
	.type	GetQueueImgNum, %function
GetQueueImgNum:
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
	ldrh	r3, [r0, #6]
	ldrh	ip, [r0, #4]
	ldrh	r0, [r0, #8]
	cmp	r3, ip
	addcc	lr, r3, #64
	rsbcs	ip, ip, r3
	rsbcc	ip, ip, lr
	cmp	r3, r0
	addhi	r0, r0, #64
	str	ip, [r1]
	rsb	r3, r3, r0
	str	r3, [r2]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetQueueImgNum, .-GetQueueImgNum
	.align	2
	.global	SYNTAX_GetVoQue
	.type	SYNTAX_GetVoQue, %function
SYNTAX_GetVoQue:
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
	ldr	r3, [r0]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L141
.L127:
	.word	.L140
	.word	.L128
	.word	.L129
	.word	.L130
	.word	.L141
	.word	.L131
	.word	.L132
	.word	.L141
	.word	.L133
	.word	.L134
	.word	.L135
	.word	.L135
	.word	.L135
	.word	.L136
	.word	.L141
	.word	.L137
	.word	.L138
	.word	.L139
	.word	.L141
	.word	.L141
	.word	.L140
.L140:
	add	r0, r0, #16
	ldmfd	sp, {fp, sp, pc}
.L128:
	add	r0, r0, #49152
	add	r0, r0, #128
	ldmfd	sp, {fp, sp, pc}
.L129:
	add	r0, r0, #22528
	add	r0, r0, #104
	ldmfd	sp, {fp, sp, pc}
.L130:
	add	r0, r0, #88064
	add	r0, r0, #136
	ldmfd	sp, {fp, sp, pc}
.L131:
	add	r0, r0, #41984
	add	r0, r0, #40
	ldmfd	sp, {fp, sp, pc}
.L132:
	add	r0, r0, #16192
	add	r0, r0, #8
	ldmfd	sp, {fp, sp, pc}
.L133:
	add	r0, r0, #54272
	add	r0, r0, #80
	ldmfd	sp, {fp, sp, pc}
.L134:
	add	r0, r0, #54272
	add	r0, r0, #72
	ldmfd	sp, {fp, sp, pc}
.L135:
	add	r0, r0, #12672
	add	r0, r0, #24
	ldmfd	sp, {fp, sp, pc}
.L136:
	add	r0, r0, #8192
	add	r0, r0, #24
	ldmfd	sp, {fp, sp, pc}
.L137:
	add	r0, r0, #592
	ldmfd	sp, {fp, sp, pc}
.L138:
	add	r0, r0, #5568
	ldmfd	sp, {fp, sp, pc}
.L139:
	add	r0, r0, #274432
	add	r0, r0, #1408
	ldmfd	sp, {fp, sp, pc}
.L141:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SYNTAX_GetVoQue, .-SYNTAX_GetVoQue
	.align	2
	.global	SYNTAX_ReceiveImage
	.type	SYNTAX_ReceiveImage, %function
SYNTAX_ReceiveImage:
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
	cmp	r0, #0
	cmpne	r1, #0
	mov	r6, r1
	beq	.L146
	bl	SYNTAX_GetVoQue
	subs	r4, r0, #0
	beq	.L148
	ldr	r7, .L149
	mov	r0, #2
	ldr	r3, [r7, #12]
	blx	r3
	ldrh	r3, [r4, #6]
	ldrh	r2, [r4, #8]
	cmp	r2, r3
	mvneq	r5, #2
	beq	.L145
	add	r10, r6, #496
	add	r3, r4, r3, lsl #2
	ldr	ip, [r7, #52]
	mov	r2, #632
	ldrd	r8, [r10]
	mov	r0, r6
	ldr	r1, [r3, #12]
	mov	r5, #1
	blx	ip
	ldr	r1, .L149+4
	strd	r8, [r10]
	mov	r0, #12
	ldr	ip, [r6, #148]
	ldrh	r3, [r4, #6]
	ldrh	r2, [r4, #4]
	str	ip, [sp, #4]
	ldrh	ip, [r4, #8]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6, #148]
	ldr	r2, [r4, #344]
	add	r3, r3, r2
	str	r3, [r6, #148]
	ldrh	r3, [r4, #6]
	add	r3, r3, r5
	and	r3, r3, #63
	strh	r3, [r4, #6]	@ movhi
.L145:
	ldr	r3, [r7, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r5
.L143:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L146:
	mvn	r0, #1
	b	.L143
.L148:
	ldr	r2, .L149+8
	mov	r0, #1
	ldr	r1, .L149+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L143
.L150:
	.align	2
.L149:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC12
	.word	.LANCHOR1+20
	.word	.LC11
	UNWIND(.fnend)
	.size	SYNTAX_ReceiveImage, .-SYNTAX_ReceiveImage
	.align	2
	.global	SYNTAX_ReleaseImage_RecycleImage_CheckRet
	.type	SYNTAX_ReleaseImage_RecycleImage_CheckRet, %function
SYNTAX_ReleaseImage_RecycleImage_CheckRet:
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
	ldr	r3, [r0]
	cmp	r3, #17
	ldrls	pc, [pc, r3, asl #2]
	b	.L152
.L154:
	.word	.L157
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L152
	.word	.L157
	.word	.L157
	.word	.L157
.L157:
	cmp	r1, #0
	mvnne	r0, #19
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L152:
	cmn	r1, #2
	beq	.L163
	cmp	r1, #1
	mvnne	r0, #19
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L163:
	mov	r0, r1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SYNTAX_ReleaseImage_RecycleImage_CheckRet, .-SYNTAX_ReleaseImage_RecycleImage_CheckRet
	.align	2
	.global	SYNTAX_ReleaseImage_RecycleImage
	.type	SYNTAX_ReleaseImage_RecycleImage, %function
SYNTAX_ReleaseImage_RecycleImage:
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
	ldr	r3, [r0]
	mov	r4, r0
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L182
.L168:
	.word	.L167
	.word	.L169
	.word	.L170
	.word	.L171
	.word	.L182
	.word	.L172
	.word	.L173
	.word	.L182
	.word	.L174
	.word	.L175
	.word	.L176
	.word	.L176
	.word	.L176
	.word	.L177
	.word	.L182
	.word	.L178
	.word	.L179
	.word	.L180
	.word	.L182
	.word	.L182
	.word	.L181
.L181:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	USERDEC_RecycleImage
	mov	r1, r0
.L166:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SYNTAX_ReleaseImage_RecycleImage_CheckRet
.L167:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	H264DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L169:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VC1DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L170:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	MPEG4DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L171:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	MPEG2DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L172:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	DIVX3DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L173:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	AVSDEC_RecycleImage
	mov	r1, r0
	b	.L166
.L174:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	REAL8DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L175:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	REAL9DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L176:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VP6DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L177:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VP8DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L178:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	MVC_DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L179:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	HEVC_DECRecycleImage
	mov	r1, r0
	b	.L166
.L180:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VP9DEC_RecycleImage
	mov	r1, r0
	b	.L166
.L182:
	mvn	r1, #1
	b	.L166
	UNWIND(.fnend)
	.size	SYNTAX_ReleaseImage_RecycleImage, .-SYNTAX_ReleaseImage_RecycleImage
	.align	2
	.global	SYNTAX_ReleaseImage
	.type	SYNTAX_ReleaseImage, %function
SYNTAX_ReleaseImage:
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
	cmp	r0, #0
	cmpne	r1, #0
	mov	r8, r1
	mov	r7, r0
	beq	.L199
	bl	SYNTAX_GetVoQue
	subs	r5, r0, #0
	beq	.L200
	ldr	r6, .L201
	mov	r0, #2
	ldr	r3, [r6, #12]
	blx	r3
	ldrh	r4, [r5, #4]
	ldrh	r3, [r5, #6]
	and	r4, r4, #63
	ldr	r9, [r8, #148]
	cmp	r3, r4
	ldr	r3, [r5, #344]
	rsb	r9, r3, r9
	bne	.L195
	b	.L194
.L191:
	add	r4, r4, #1
	ldrh	r3, [r5, #6]
	and	r4, r4, #63
	cmp	r3, r4
	beq	.L194
.L195:
	add	r10, r4, #2
	add	r3, r5, r10, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L189
	ldr	r0, [r3, #148]
	rsb	r0, r0, r9
	clz	r0, r0
	mov	r0, r0, lsr #5
	cmp	r0, #0
	beq	.L191
.L190:
	ldrh	r1, [r5, #4]
	b	.L193
.L197:
	mov	r4, ip
.L193:
	cmp	r4, #0
	mov	ip, #63
	subne	ip, r4, #1
	add	r2, r5, r10, lsl #2
	add	r3, ip, #2
	cmp	r4, r1
	add	lr, r5, r3, lsl #2
	mov	r10, r3
	ldr	r3, [lr, #4]
	str	r3, [r2, #4]
	bne	.L197
	ldr	r3, [r8, #148]
	cmp	r0, #1
	ldr	r2, [r5, #344]
	rsb	r3, r2, r3
	str	r3, [r8, #148]
	ldrh	r2, [r5, #4]
	add	r2, r2, #1
	and	r2, r2, #63
	strh	r2, [r5, #4]	@ movhi
	bne	.L191
	ldr	ip, [r8, #148]
	mov	r0, #12
	ldrh	r3, [r5, #6]
	ldr	r1, .L201+4
	str	ip, [sp, #4]
	ldrh	ip, [r5, #8]
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r1, r8
	mov	r0, r7
	bl	SYNTAX_ReleaseImage_RecycleImage
	mov	r4, r0
	b	.L188
.L189:
	mov	r2, r4
	ldr	r1, .L201+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #2
	b	.L190
.L194:
	mov	r2, r9
	ldr	r1, .L201+12
	mov	r0, #1
	mvn	r4, #1
	bl	dprint_vfmw
.L188:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r4
.L185:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L199:
	ldr	r1, .L201+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L185
.L200:
	ldr	r2, .L201+20
	mov	r0, #1
	ldr	r1, .L201+24
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L185
.L202:
	.align	2
.L201:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC16
	.word	.LC15
	.word	.LC14
	.word	.LC13
	.word	.LANCHOR1+40
	.word	.LC11
	UNWIND(.fnend)
	.size	SYNTAX_ReleaseImage, .-SYNTAX_ReleaseImage
	.align	2
	.global	SYNTAX_ReturnImage
	.type	SYNTAX_ReturnImage, %function
SYNTAX_ReturnImage:
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
	ldr	r3, [r0]
	cmp	r3, #20
	ldrls	pc, [pc, r3, asl #2]
	b	.L221
.L206:
	.word	.L219
	.word	.L207
	.word	.L208
	.word	.L209
	.word	.L221
	.word	.L210
	.word	.L211
	.word	.L221
	.word	.L212
	.word	.L213
	.word	.L214
	.word	.L214
	.word	.L214
	.word	.L215
	.word	.L221
	.word	.L216
	.word	.L217
	.word	.L218
	.word	.L221
	.word	.L221
	.word	.L219
.L219:
	add	r4, r0, #16
.L220:
	ldr	r5, .L222
	mov	r0, #2
	ldr	r3, [r5, #12]
	blx	r3
	ldrh	r3, [r4, #6]
	mov	r0, #2
	sub	r3, r3, #1
	and	r3, r3, #63
	strh	r3, [r4, #6]	@ movhi
	ldr	r3, [r5, #16]
	blx	r3
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L207:
	add	r4, r0, #49152
	add	r4, r4, #128
	b	.L220
.L208:
	add	r4, r0, #22528
	add	r4, r4, #104
	b	.L220
.L209:
	add	r4, r0, #88064
	add	r4, r4, #136
	b	.L220
.L210:
	add	r4, r0, #41984
	add	r4, r4, #40
	b	.L220
.L211:
	add	r4, r0, #16192
	add	r4, r4, #8
	b	.L220
.L212:
	add	r4, r0, #54272
	add	r4, r4, #80
	b	.L220
.L213:
	add	r4, r0, #54272
	add	r4, r4, #72
	b	.L220
.L214:
	add	r4, r0, #12672
	add	r4, r4, #24
	b	.L220
.L215:
	add	r4, r0, #8192
	add	r4, r4, #24
	b	.L220
.L216:
	add	r4, r0, #592
	b	.L220
.L217:
	add	r4, r0, #5568
	b	.L220
.L218:
	add	r4, r0, #274432
	add	r4, r4, #1408
	b	.L220
.L221:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L223:
	.align	2
.L222:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	SYNTAX_ReturnImage, .-SYNTAX_ReturnImage
	.align	2
	.global	DecodeStream_H264
	.type	DecodeStream_H264, %function
DecodeStream_H264:
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
	mov	r4, r0
	ldrd	r2, [r0, #32]
	mov	r5, r1
	ldr	r10, [r4, #8]
	mov	r0, r1
	ldr	r9, [r4, #20]
	sub	r1, fp, #76
	ldr	r8, [r4, #24]
	ldrb	r7, [r4, #14]	@ zero_extendqisi2
	ldr	r6, [r4, #28]
	ldrb	lr, [r4, #16]	@ zero_extendqisi2
	ldrsb	ip, [r4, #13]
	strd	r2, [fp, #-52]
	str	r10, [fp, #-72]
	str	r9, [fp, #-68]
	str	r8, [fp, #-64]
	strb	r7, [fp, #-76]
	str	r6, [fp, #-60]
	strb	lr, [fp, #-75]
	str	ip, [fp, #-56]
	bl	H264DEC_DecodePacket
	add	r2, r5, #61440
	ldr	r1, .L230
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r0, [r2, #2352]
	ldr	r1, [r1, r0, asl #2]
	strb	r3, [r1, #1456]
	ldr	r4, [r5, #360]
	cmp	r4, #0
	beq	.L229
.L224:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L229:
	add	r5, r5, #12288
	ldrb	r3, [r5, #1272]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L224
	ldr	r0, [r2, #2352]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1272]
	b	.L224
.L231:
	.align	2
.L230:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_H264, .-DecodeStream_H264
	.align	2
	.global	DecodeStream_HEVC
	.type	DecodeStream_HEVC, %function
DecodeStream_HEVC:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
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
	mov	r4, r0
	ldr	r7, [r0, #8]
	mov	r5, r1
	ldr	r6, [r4, #20]
	mov	r0, r1
	ldr	lr, [r4, #24]
	sub	r1, fp, #52
	ldrb	ip, [r4, #14]	@ zero_extendqisi2
	ldr	r2, [r4, #28]
	ldrsb	r3, [r4, #13]
	str	r7, [fp, #-48]
	str	r6, [fp, #-44]
	str	lr, [fp, #-36]
	strb	ip, [fp, #-52]
	str	r2, [fp, #-32]
	str	r3, [fp, #-40]
	bl	HEVCDEC_DecodePacket
	cmn	r0, #2
	beq	.L233
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L234
.L233:
	mov	r3, #1
	ldr	r2, .L241
	strb	r3, [r4, #1]
	ldr	r1, [r5, #252]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1456]
	ldr	r4, [r5, #2412]
	cmp	r4, #0
	beq	.L240
.L232:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L234:
	strb	r3, [r4, #1]
	ldr	r2, .L241
	ldr	r1, [r5, #252]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1456]
	ldr	r4, [r5, #2412]
	cmp	r4, #0
	bne	.L232
.L240:
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L232
	ldr	r0, [r5, #252]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #9]
	b	.L232
.L242:
	.align	2
.L241:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_HEVC, .-DecodeStream_HEVC
	.align	2
	.global	DecodeStream_VP9
	.type	DecodeStream_VP9, %function
DecodeStream_VP9:
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
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #1
	beq	.L258
	ldr	r8, .L260
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	add	r6, r5, #294912
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r3, [r8, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r7
	mov	r0, r5
	bl	VP9DEC_DecodePacket
	ldr	r3, [r6, #3424]
	cmp	r3, #0
	bne	.L259
.L245:
	ldr	r3, [r6, #3420]
	cmp	r3, #0
	bne	.L246
.L257:
	strb	r3, [r4, #1]
	ldr	r3, [r5, #4]
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #262144
	ldrb	r5, [r5, #1036]	@ zero_extendqisi2
	cmp	r5, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r3, [r8, #48]
	mov	r2, #160
	mov	r1, r5
	mov	r0, r7
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r6, #3516]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L260+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r6, #3516]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L259:
	ldr	r2, [r6, #3464]
	ldr	r3, [r6, #3460]
	cmp	r2, r3
	beq	.L245
.L246:
	mov	r3, #1
	b	.L257
.L258:
	add	r5, r1, #294912
	ldr	r0, [r5, #3516]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #3516]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L261:
	.align	2
.L260:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	DecodeStream_VP9, .-DecodeStream_VP9
	.align	2
	.global	DecodeStream_MVC
	.type	DecodeStream_MVC, %function
DecodeStream_MVC:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #36)
	sub	sp, sp, #36
	mov	r4, r0
	ldrd	r2, [r0, #32]
	mov	r5, r1
	ldr	r8, [r4, #8]
	mov	r0, r1
	ldr	r7, [r4, #20]
	sub	r1, fp, #68
	ldr	r6, [r4, #24]
	ldrb	lr, [r4, #14]	@ zero_extendqisi2
	ldr	ip, [r4, #28]
	strd	r2, [fp, #-44]
	str	r8, [fp, #-64]
	str	r7, [fp, #-60]
	str	r6, [fp, #-56]
	strb	lr, [fp, #-68]
	str	ip, [fp, #-52]
	bl	MVC_DEC_DecodePacket
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r4, [r5, #228]
	cmp	r4, #0
	beq	.L266
.L262:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L266:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L262
	ldr	r0, [r5, #120]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1]
	b	.L262
	UNWIND(.fnend)
	.size	DecodeStream_MVC, .-DecodeStream_MVC
	.align	2
	.global	DecodeStream_VC1_Smp
	.type	DecodeStream_VC1_Smp, %function
DecodeStream_VC1_Smp:
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
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #1
	beq	.L280
	ldr	r6, .L283
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	ldr	r3, [r6, #52]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	ldr	r3, [r4, #104]
	cmp	r3, #15
	bls	.L281
	add	r2, r5, #15808
	mov	r1, #16
	add	r2, r2, #24
	ldr	r0, [r4, #88]
	bl	Vc1SMPSeqHdr
	subs	r8, r0, #0
	beq	.L282
	ldr	r1, .L283+4
	add	r5, r5, #49152
.L279:
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #108]
	ldr	r0, [r5, #472]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L283+8
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	mov	r3, #0
	ldr	r0, [r5, #472]
	mov	r2, r3
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L281:
	add	r5, r5, #49152
	ldr	r1, .L283+12
	b	.L279
.L280:
	add	r5, r1, #49152
	ldr	r0, [r5, #472]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #472]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L282:
	ldr	ip, [r4, #104]
	mov	r1, r7
	ldr	r2, [r4, #88]
	mov	r0, r5
	ldr	r3, [r4, #100]
	sub	ip, ip, #16
	add	r2, r2, #16
	str	ip, [r4, #104]
	str	r2, [r4, #88]
	add	r3, r3, #16
	str	r3, [r4, #100]
	bl	VC1DEC_Decode
	ldr	r3, [r6, #48]
	mov	r1, r8
	mov	r0, r7
	mov	r2, #160
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	r3
.L284:
	.align	2
.L283:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC18
	.word	g_event_report
	.word	.LC17
	UNWIND(.fnend)
	.size	DecodeStream_VC1_Smp, .-DecodeStream_VC1_Smp
	.align	2
	.global	DecodeStream_REAL8
	.type	DecodeStream_REAL8, %function
DecodeStream_REAL8:
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
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #1
	beq	.L295
	ldr	r7, .L296
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	REAL8DEC_Decode
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r8, [r5, #4]
	cmp	r8, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #53248
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #1448]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L296+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #1448]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L295:
	add	r5, r1, #53248
	ldr	r0, [r5, #1448]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1448]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L297:
	.align	2
.L296:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	DecodeStream_REAL8, .-DecodeStream_REAL8
	.align	2
	.global	DecodeStream_REAL9
	.type	DecodeStream_REAL9, %function
DecodeStream_REAL9:
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
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #1
	beq	.L308
	ldr	r7, .L309
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	REAL9DEC_Decode
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r8, [r5, #4]
	cmp	r8, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #53248
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #1440]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L309+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #1440]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L308:
	add	r5, r1, #53248
	ldr	r0, [r5, #1440]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1440]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L310:
	.align	2
.L309:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	DecodeStream_REAL9, .-DecodeStream_REAL9
	.align	2
	.global	DecodeStream_DIVX3
	.type	DecodeStream_DIVX3, %function
DecodeStream_DIVX3:
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
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #1
	beq	.L321
	ldr	r7, .L322
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	DIVX3DEC_Decode
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r8, [r5, #4]
	cmp	r8, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #40960
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #1408]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L322+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #1408]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L321:
	add	r5, r1, #40960
	ldr	r0, [r5, #1408]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1408]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L323:
	.align	2
.L322:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	DecodeStream_DIVX3, .-DecodeStream_DIVX3
	.align	2
	.global	DecodeStream_VP8
	.type	DecodeStream_VP8, %function
DecodeStream_VP8:
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
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #1
	beq	.L334
	ldr	r7, .L335
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	VP8DEC_Decode
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r8, [r5, #4]
	cmp	r8, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #8192
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #368]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L335+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #368]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L334:
	add	r5, r1, #8192
	ldr	r0, [r5, #368]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #368]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L336:
	.align	2
.L335:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	DecodeStream_VP8, .-DecodeStream_VP8
	.align	2
	.global	DecodeStream_VP6x
	.type	DecodeStream_VP6x, %function
DecodeStream_VP6x:
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
	ldrb	r3, [r0, #15]	@ zero_extendqisi2
	mov	r4, r0
	mov	r5, r1
	cmp	r3, #1
	beq	.L347
	ldr	r7, .L348
	add	r6, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r6
	ldr	r3, [r7, #52]
	blx	r3
	ldr	r3, [r7, #48]
	mov	r2, #80
	mov	r1, #0
	add	r0, r4, #168
	blx	r3
	mov	r1, r6
	mov	r0, r5
	bl	VP6DEC_Decode
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r8, [r5, #4]
	cmp	r8, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r5, #12288
	ldr	r3, [r7, #48]
	mov	r2, #160
	mov	r1, r8
	mov	r0, r6
	blx	r3
	ldr	r1, [r4, #28]
	ldr	r0, [r5, #752]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L348+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r5, #752]
	mov	r3, r8
	mov	r2, r8
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L347:
	add	r5, r1, #12288
	ldr	r0, [r5, #752]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #752]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L349:
	.align	2
.L348:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	DecodeStream_VP6x, .-DecodeStream_VP6x
	.align	2
	.global	SegMan
	.type	SegMan, %function
SegMan:
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
	subs	r4, r1, #0
	mov	r6, r0
	beq	.L351
	ldr	r0, [r4, #8]
	cmp	r0, #0
	beq	.L351
	ldr	r3, .L375
	ldr	r3, [r3, r6, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L371
.L354:
	ldrb	r5, [r4, #14]	@ zero_extendqisi2
	mov	r7, #0
	strb	r7, [r4, #408]
	cmp	r5, #1
	beq	.L372
	cmp	r5, #0
	beq	.L373
.L359:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L373:
	ldr	r9, .L375+4
	add	r8, r4, #88
	add	r7, r4, #168
	mov	r2, #80
	add	r1, r4, #8
	mov	r0, r8
	ldr	r3, [r9, #52]
	blx	r3
	ldr	r3, [r9, #48]
	mov	r0, r7
	mov	r2, #80
	mov	r1, r5
	blx	r3
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	add	r3, r3, #1
	uxtb	r3, r3
	strb	r3, [r4, #2]
	cmp	r3, #1
	bls	.L359
	ldr	r1, [r4, #108]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	ldr	r1, [r4, #188]
	mov	r0, r6
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r9, #48]
	mov	r2, #80
	mov	r1, r5
	mov	r0, r8
	blx	r3
	ldr	r3, [r9, #48]
	mov	r2, #80
	mov	r1, r5
	mov	r0, r7
	blx	r3
	ldr	r1, .L375+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L375+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L358
	mov	r0, r6
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	ip
.L358:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L371:
	ldr	r3, [r3, #1432]
	cmp	r3, #1
	bne	.L354
	ldrb	r3, [r4, #408]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L354
	mov	r2, #160
	add	r1, r4, #248
	add	r0, r4, #88
	bl	memcpy
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r4, #408]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L372:
	ldrb	r5, [r4, #2]	@ zero_extendqisi2
	cmp	r5, r7
	beq	.L374
	cmp	r5, #1
	bne	.L359
	ldr	r2, [r4, #104]
	cmp	r2, #1024
	bcs	.L360
	ldr	r8, .L375+4
	rsb	r0, r2, r0
	ldr	r1, [r4, #88]
	ldr	r3, [r8, #52]
	blx	r3
	ldr	r1, [r4, #104]
	ldr	ip, [r4, #8]
	mov	r0, r6
	ldr	r2, [r4, #20]
	ldr	r3, [r4, #24]
	rsb	ip, r1, ip
	rsb	r2, r1, r2
	str	ip, [r4, #88]
	add	r3, r3, r1
	str	r2, [r4, #100]
	str	r3, [r4, #104]
	ldr	r1, [r4, #108]
	strb	r5, [r4, #94]
	bl	SM_ReleaseStreamSeg
	ldr	ip, [r4, #28]
	ldr	r3, [r8, #48]
	mov	r1, r7
	mov	r2, #80
	add	r0, r4, #168
	str	ip, [r4, #108]
	blx	r3
.L361:
	mov	r5, #0
	mov	r3, #1
	strb	r5, [r4, #2]
	mov	r2, #160
	strb	r3, [r4, #408]
	add	r1, r4, #88
	add	r0, r4, #248
	bl	memcpy
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L374:
	ldr	r6, .L375+4
	add	r1, r4, #8
	mov	r2, #80
	add	r0, r4, #88
	ldr	r3, [r6, #52]
	blx	r3
	ldr	r3, [r6, #48]
	mov	r2, #80
	mov	r1, r5
	add	r0, r4, #168
	blx	r3
	strb	r5, [r4, #2]
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L360:
	ldr	r3, .L375+4
	mov	r2, #80
	add	r1, r4, #8
	add	r0, r4, #168
	ldr	r3, [r3, #52]
	blx	r3
	b	.L361
.L351:
	ldr	r1, .L375+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L376:
	.align	2
.L375:
	.word	s_pstVfmwChan
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC20
	.word	g_event_report
	.word	.LC19
	UNWIND(.fnend)
	.size	SegMan, .-SegMan
	.align	2
	.global	DecodeStream_VC1_Adv
	.type	DecodeStream_VC1_Adv, %function
DecodeStream_VC1_Adv:
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
	add	r6, r1, #49152
	mov	r5, r0
	mov	r0, r1
	mov	r4, r1
	ldr	r7, [r6, #472]
	bl	VC1_GetPacketState
	cmp	r0, #2
	beq	.L382
.L378:
	mov	r1, r5
	ldr	r0, [r6, #472]
	bl	SegMan
	subs	r7, r0, #0
	beq	.L383
.L380:
	ldr	r5, [r4, #4]
	cmp	r5, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r4, r4, #12288
	ldrb	r3, [r4, #455]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r6, #472]
	bl	VCTRL_OutputLastFrame
	strb	r5, [r4, #455]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L383:
	add	r5, r5, #88
	mov	r0, r4
	mov	r1, r5
	bl	VC1DEC_Decode
	ldr	r3, .L385
	mov	r0, r5
	mov	r1, r7
	mov	r2, #160
	ldr	r3, [r3, #48]
	blx	r3
	b	.L380
.L382:
	ldr	r3, .L385+4
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L384
.L379:
	add	r1, r4, #12544
	mov	r0, r4
	add	r1, r1, #32
	bl	VC1DEC_Decode
	b	.L378
.L384:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L378
	b	.L379
.L386:
	.align	2
.L385:
	.word	vfmw_Osal_Func_Ptr_S
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_VC1_Adv, .-DecodeStream_VC1_Adv
	.align	2
	.global	DecodeStream_VC1
	.type	DecodeStream_VC1, %function
DecodeStream_VC1:
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
	ldrb	r2, [r0, #14]	@ zero_extendqisi2
	mov	r5, r1
	mov	r0, #22
	ldr	r1, .L394
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L394+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r4, #24]
	ldr	r1, .L394+8
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r5]
	ldr	r3, [r2, #556]
	cmp	r3, #1
	ldrhi	r1, .L394+12
	bhi	.L391
	ldr	r1, [r2, #560]
	cmp	r1, #8
	bgt	.L392
	add	r1, r5, #12288
	uxtb	r3, r3
	cmp	r3, #1
	mov	r0, r4
	strb	r3, [r1, #3544]
	ldr	r3, [r2, #560]
	strb	r3, [r1, #3546]
	mov	r1, r5
	beq	.L393
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DecodeStream_VC1_Smp
.L392:
	ldr	r1, .L394+16
.L391:
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L393:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DecodeStream_VC1_Adv
.L395:
	.align	2
.L394:
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC25
	UNWIND(.fnend)
	.size	DecodeStream_VC1, .-DecodeStream_VC1
	.align	2
	.global	DecodeStream_MPEG2
	.type	DecodeStream_MPEG2, %function
DecodeStream_MPEG2:
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
	add	r5, r1, #86016
	mov	r6, r0
	mov	r0, r1
	mov	r4, r1
	ldr	r7, [r5, #2528]
	bl	MP2_GetPacketState
	cmp	r0, #2
	beq	.L402
.L397:
	mov	r1, r6
	ldr	r0, [r5, #2528]
	bl	SegMan
	cmp	r0, #0
	beq	.L403
.L399:
	ldr	r4, [r4, #4]
	cmp	r4, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r5, #2546]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r5, #2528]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #2546]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L403:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG2DEC_Decode
	ldrb	r3, [r5, #2545]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strb	r3, [r6, #1]
	b	.L399
.L402:
	ldr	r3, .L405
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L404
.L398:
	add	r1, r4, #87040
	mov	r0, r4
	add	r1, r1, #592
	bl	MPEG2DEC_Decode
	b	.L397
.L404:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L397
	b	.L398
.L406:
	.align	2
.L405:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_MPEG2, .-DecodeStream_MPEG2
	.align	2
	.global	DecodeStream_MPEG4
	.type	DecodeStream_MPEG4, %function
DecodeStream_MPEG4:
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
	add	r5, r1, #20480
	mov	r6, r0
	mov	r0, r1
	mov	r4, r1
	ldr	r7, [r5, #2496]
	bl	MP4_GetPacketState
	cmp	r0, #3
	beq	.L412
.L408:
	mov	r1, r6
	ldr	r0, [r5, #2496]
	bl	SegMan
	cmp	r0, #0
	beq	.L413
.L410:
	ldr	r4, [r4, #1036]
	cmp	r4, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r5, #2532]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r5, #2496]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #2532]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L413:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG4DEC_Decode
	b	.L410
.L412:
	ldr	r3, .L415
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L414
.L409:
	add	r1, r4, #15680
	mov	r0, r4
	add	r1, r1, #32
	bl	MPEG4DEC_Decode
	b	.L408
.L414:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L408
	b	.L409
.L416:
	.align	2
.L415:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_MPEG4, .-DecodeStream_MPEG4
	.align	2
	.global	DecodeStream_AVS
	.type	DecodeStream_AVS, %function
DecodeStream_AVS:
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
	mov	r0, r1
	mov	r4, r1
	ldr	r6, [r1, #4]
	bl	AVS_GetPacketState
	cmp	r0, #0
	bne	.L418
	ldr	r3, .L424
	ldr	r3, [r3, r6, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L422
	add	r1, r4, #16384
	mov	r0, r4
	add	r1, r1, #168
	bl	AVSDEC_Decode
.L418:
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	SegMan
	cmp	r0, #0
	beq	.L423
.L420:
	ldr	r5, [r4, #16]
	cmp	r5, #0
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	VCTRL_OutputLastFrame
	strb	r5, [r4]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L422:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L418
	add	r1, r4, #16384
	mov	r0, r4
	add	r1, r1, #168
	bl	AVSDEC_Decode
	b	.L418
.L423:
	add	r1, r5, #88
	mov	r0, r4
	bl	AVSDEC_Decode
	b	.L420
.L425:
	.align	2
.L424:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_AVS, .-DecodeStream_AVS
	.align	2
	.global	DecodeStream
	.type	DecodeStream, %function
DecodeStream:
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
	mov	r0, #6
	mov	r4, r1
	mov	r6, r2
	bl	VCTRL_RecordPosTime
	cmp	r4, #17
	ldrls	pc, [pc, r4, asl #2]
	b	.L427
.L429:
	.word	.L428
	.word	.L430
	.word	.L431
	.word	.L432
	.word	.L427
	.word	.L433
	.word	.L434
	.word	.L427
	.word	.L435
	.word	.L436
	.word	.L437
	.word	.L437
	.word	.L437
	.word	.L438
	.word	.L427
	.word	.L439
	.word	.L440
	.word	.L441
.L441:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP9
.L442:
	mov	r0, #7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_RecordPosTime
.L428:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_H264
	b	.L442
.L430:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VC1
	b	.L442
.L431:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG4
	b	.L442
.L432:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG2
	b	.L442
.L433:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_DIVX3
	b	.L442
.L434:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_AVS
	b	.L442
.L435:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL8
	b	.L442
.L436:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL9
	b	.L442
.L437:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP6x
	b	.L442
.L438:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP8
	b	.L442
.L439:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MVC
	b	.L442
.L440:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_HEVC
	b	.L442
.L427:
	movw	r3, #1782
	ldr	r2, .L443
	ldr	r1, .L443+4
	mov	r0, #32
	bl	dprint_vfmw
	b	.L442
.L444:
	.align	2
.L443:
	.word	.LANCHOR1+60
	.word	.LC26
	UNWIND(.fnend)
	.size	DecodeStream, .-DecodeStream
	.align	2
	.global	ReleasePacket
	.type	ReleasePacket, %function
ReleasePacket:
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
	sub	r3, r0, #5
	cmp	r3, #12
	ldrls	pc, [pc, r3, asl #2]
	b	.L446
.L448:
	.word	.L447
	.word	.L446
	.word	.L446
	.word	.L449
	.word	.L450
	.word	.L451
	.word	.L451
	.word	.L451
	.word	.L452
	.word	.L446
	.word	.L446
	.word	.L446
	.word	.L453
.L453:
	ldr	r4, [r1]
	add	r1, r1, #294912
	ldr	r0, [r1, #3516]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L459
	ldr	r1, .L469
	mov	r0, #1
	bl	dprint_vfmw
.L459:
	ldr	r3, .L469+4
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L447:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L459
	add	r3, r1, #40960
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1408]
	bl	SM_ReleaseStreamSeg
	b	.L459
.L449:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L459
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1448]
	bl	SM_ReleaseStreamSeg
	b	.L459
.L450:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L459
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1440]
	bl	SM_ReleaseStreamSeg
	b	.L459
.L451:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L459
	ldr	r1, .L469+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L459
.L452:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L459
	ldr	r1, .L469+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L459
.L446:
	mov	r2, r0
	ldr	r1, .L469+16
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L470:
	.align	2
.L469:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC28
	.word	.LC27
	.word	.LC30
	UNWIND(.fnend)
	.size	ReleasePacket, .-ReleasePacket
	.align	2
	.global	ReleaseCurPic_VPx
	.type	ReleaseCurPic_VPx, %function
ReleaseCurPic_VPx:
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
	sub	r0, r0, #10
	cmp	r0, #7
	ldrls	pc, [pc, r0, asl #2]
	b	.L471
.L474:
	.word	.L473
	.word	.L473
	.word	.L473
	.word	.L475
	.word	.L471
	.word	.L471
	.word	.L471
	.word	.L476
.L476:
	ldr	r4, [r1]
	add	r1, r1, #294912
	ldr	r0, [r1, #3516]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L479
	ldr	r1, .L489
	mov	r0, #1
	bl	dprint_vfmw
.L479:
	ldr	r3, .L489+4
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L475:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L479
	ldr	r1, .L489+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L479
.L473:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L479
	ldr	r1, .L489+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L479
.L471:
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L490:
	.align	2
.L489:
	.word	.LC29
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC27
	.word	.LC28
	UNWIND(.fnend)
	.size	ReleaseCurPic_VPx, .-ReleaseCurPic_VPx
	.align	2
	.global	ReleaseCurPic_Realx
	.type	ReleaseCurPic_Realx, %function
ReleaseCurPic_Realx:
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
	cmp	r0, #8
	beq	.L493
	cmp	r0, #9
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L499
.L496:
	ldr	r3, .L500
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L493:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L496
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1448]
	bl	SM_ReleaseStreamSeg
	b	.L496
.L499:
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1440]
	bl	SM_ReleaseStreamSeg
	b	.L496
.L501:
	.align	2
.L500:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ReleaseCurPic_Realx, .-ReleaseCurPic_Realx
	.align	2
	.global	ReleaseCurPic_DIVX3
	.type	ReleaseCurPic_DIVX3, %function
ReleaseCurPic_DIVX3:
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
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L504
.L503:
	ldr	r3, .L505
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L504:
	add	r3, r1, #40960
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1408]
	bl	SM_ReleaseStreamSeg
	b	.L503
.L506:
	.align	2
.L505:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ReleaseCurPic_DIVX3, .-ReleaseCurPic_DIVX3
	.align	2
	.global	ReleaseCurPic
	.type	ReleaseCurPic, %function
ReleaseCurPic:
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
	cmp	r0, #17
	ldrls	pc, [pc, r0, asl #2]
	b	.L508
.L510:
	.word	.L509
	.word	.L511
	.word	.L512
	.word	.L513
	.word	.L508
	.word	.L514
	.word	.L515
	.word	.L508
	.word	.L516
	.word	.L517
	.word	.L518
	.word	.L518
	.word	.L518
	.word	.L519
	.word	.L508
	.word	.L520
	.word	.L521
	.word	.L522
.L522:
	mov	r0, #17
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L509:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264_ClearCurrPic
.L511:
	add	r3, r1, #49152
	add	r0, r1, #12736
	ldr	r1, [r3, #472]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1_ClearCurPic
.L512:
	mov	r0, r1
	str	r1, [fp, #-16]
	bl	MP4_ClearCurPic
	ldr	r1, [fp, #-16]
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP4_Clean_HeadPacket
.L513:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP2_ClearCurPic
.L514:
	mov	r0, #5
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_DIVX3
.L515:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS_ClearCurPic
.L516:
	mov	r0, #8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L517:
	mov	r0, #9
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L518:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L519:
	mov	r0, #13
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L520:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_ClearCurrPic
.L521:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_ClearCurrPic
.L508:
	mov	r2, r0
	ldr	r1, .L523
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L524:
	.align	2
.L523:
	.word	.LC30
	UNWIND(.fnend)
	.size	ReleaseCurPic, .-ReleaseCurPic
	.align	2
	.global	CheckNewPicSegMpeg2
	.type	CheckNewPicSegMpeg2, %function
CheckNewPicSegMpeg2:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	add	r2, r3, #73
	cmp	r3, #0
	cmpne	r3, #179
	uxtb	r2, r2
	moveq	ip, #1
	movne	ip, #0
	cmp	r2, #1
	movhi	r2, ip
	orrls	r2, ip, #1
	cmp	r2, #0
	beq	.L529
	ldr	r2, [r0]
	cmp	r2, #0
	bne	.L529
	mov	r3, #1
	str	r3, [r0]
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
.L526:
	cmp	r3, #0
	streq	r3, [r0]
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L529:
	mvn	r2, #0
	b	.L526
	UNWIND(.fnend)
	.size	CheckNewPicSegMpeg2, .-CheckNewPicSegMpeg2
	.align	2
	.global	CheckNewPicSegMpeg4
	.type	CheckNewPicSegMpeg4, %function
CheckNewPicSegMpeg4:
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
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	lr, #179
	cmpne	lr, #176
	add	r3, lr, #75
	moveq	ip, #1
	movne	ip, #0
	cmp	lr, #254
	orreq	ip, ip, #1
	uxtb	r3, r3
	cmp	lr, #47
	orrls	ip, ip, #1
	cmp	r3, #1
	movhi	r3, ip
	orrls	r3, ip, #1
	cmp	r3, #0
	bne	.L542
.L531:
	cmp	r2, #1
	bne	.L535
.L532:
	mov	r2, #1
	str	r2, [r0]
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	mov	r3, #0
.L533:
	cmp	lr, #182
	moveq	r2, #0
	streq	r2, [r0]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L542:
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L532
	b	.L531
.L535:
	mvn	r3, #0
	b	.L533
	UNWIND(.fnend)
	.size	CheckNewPicSegMpeg4, .-CheckNewPicSegMpeg4
	.align	2
	.global	CheckNewPicSegAVS
	.type	CheckNewPicSegAVS, %function
CheckNewPicSegAVS:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	sub	r2, r3, #179
	add	ip, r3, #74
	clz	r2, r2
	uxtb	ip, ip
	mov	r2, r2, lsr #5
	cmp	r3, #176
	movne	lr, r2
	orreq	lr, r2, #1
	cmp	ip, #1
	movhi	ip, lr
	orrls	ip, lr, #1
	cmp	ip, #0
	beq	.L547
	ldr	ip, [r0]
	cmp	ip, #0
	bne	.L547
	mov	r3, #1
	str	r3, [r0]
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	sub	r2, r3, #179
	clz	r2, r2
	mov	r2, r2, lsr #5
.L544:
	cmp	r3, #182
	movne	r3, r2
	orreq	r3, r2, #1
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0]
	mov	r0, ip
	ldmfd	sp, {fp, sp, pc}
.L547:
	mvn	ip, #0
	b	.L544
	UNWIND(.fnend)
	.size	CheckNewPicSegAVS, .-CheckNewPicSegAVS
	.align	2
	.global	CheckNewPicSegVC1
	.type	CheckNewPicSegVC1, %function
CheckNewPicSegVC1:
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
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	sub	r3, r2, #12
	cmp	r2, #10
	cmpne	r3, #3
	bhi	.L555
	ldr	r3, [r0]
	cmp	r3, #0
	bne	.L555
	mov	r2, #1
	str	r2, [r0]
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
.L552:
	cmp	r2, #13
	moveq	r2, #0
	streq	r2, [r0]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L555:
	mvn	r3, #0
	b	.L552
	UNWIND(.fnend)
	.size	CheckNewPicSegVC1, .-CheckNewPicSegVC1
	.align	2
	.global	CheckNewPicSegByVidStd
	.type	CheckNewPicSegByVidStd, %function
CheckNewPicSegByVidStd:
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
	ldr	ip, [r2]
	cmp	r1, #16
	ldrls	pc, [pc, r1, asl #2]
	b	.L557
.L559:
	.word	.L558
	.word	.L560
	.word	.L561
	.word	.L562
	.word	.L557
	.word	.L557
	.word	.L563
	.word	.L557
	.word	.L557
	.word	.L557
	.word	.L557
	.word	.L557
	.word	.L557
	.word	.L557
	.word	.L557
	.word	.L564
	.word	.L565
.L565:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_IsNewPicNal
.L558:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264_IsNewPicNal
.L560:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegVC1
.L561:
	mov	r2, r3
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegMpeg4
.L562:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegMpeg2
.L563:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegAVS
.L564:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_IsNewPicNal
.L557:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	CheckNewPicSegByVidStd, .-CheckNewPicSegByVidStd
	.align	2
	.global	IsNewpicSeg
	.type	IsNewpicSeg, %function
IsNewpicSeg:
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
	cmp	r1, #2
	ldr	ip, [r2]
	movne	r3, #0
	beq	.L582
.L567:
	ldrb	lr, [ip]	@ zero_extendqisi2
	ldrb	r4, [ip, #1]	@ zero_extendqisi2
	cmp	lr, #0
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	bne	.L570
	cmp	r4, #0
	bne	.L570
	cmp	ip, #1
	bne	.L570
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	CheckNewPicSegByVidStd
.L582:
	ldrb	r3, [r2, #72]	@ zero_extendqisi2
	ands	r3, r3, #1
	beq	.L567
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	CheckNewPicSegByVidStd
.L570:
	str	ip, [sp]
	mov	r3, r4
	mov	r2, lr
	ldr	r1, .L583
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L584:
	.align	2
.L583:
	.word	.LC31
	UNWIND(.fnend)
	.size	IsNewpicSeg, .-IsNewpicSeg
	.align	2
	.global	OpenUsdPool
	.type	OpenUsdPool, %function
OpenUsdPool:
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
	ldr	r4, .L592
	add	r4, r4, r0, lsl #2
	ldr	ip, [r4, #128]
	cmp	ip, #0
	beq	.L591
.L586:
	add	r1, ip, #203776
	mov	r0, #0
	add	r1, r1, #512
	mov	r3, ip
	mov	r2, r0
	str	r0, [ip]
.L588:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L588
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L591:
	ldr	r3, .L592+4
	movw	r0, #7688
	movt	r0, 3
	ldr	r3, [r3, #208]
	blx	r3
	cmp	r0, #0
	str	r0, [r4, #128]
	movne	ip, r0
	bne	.L586
.L589:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L593:
	.align	2
.L592:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	OpenUsdPool, .-OpenUsdPool
	.align	2
	.global	CloseUsdPool
	.type	CloseUsdPool, %function
CloseUsdPool:
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
	ldr	r4, .L599
	add	r4, r4, r0, lsl #2
	ldr	r0, [r4, #128]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L599+4
	ldr	r3, [r3, #212]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #128]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L600:
	.align	2
.L599:
	.word	.LANCHOR0
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	CloseUsdPool, .-CloseUsdPool
	.align	2
	.global	OpenUsdPool_WithMem
	.type	OpenUsdPool_WithMem, %function
OpenUsdPool_WithMem:
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
	ldr	r3, .L608
	add	r0, r3, r0, lsl #2
	ldr	ip, [r0, #128]
	cmp	ip, #0
	beq	.L607
.L602:
	add	r1, ip, #203776
	mov	r0, #0
	add	r1, r1, #512
	mov	r3, ip
	mov	r2, r0
	str	r0, [ip]
.L604:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L604
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L607:
	cmp	r1, #0
	str	r1, [r0, #128]
	movne	ip, r1
	bne	.L602
.L605:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L609:
	.align	2
.L608:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	OpenUsdPool_WithMem, .-OpenUsdPool_WithMem
	.align	2
	.global	CloseUsdPool_WithMem
	.type	CloseUsdPool_WithMem, %function
CloseUsdPool_WithMem:
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
	ldr	r3, .L615
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #128]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0, #128]
	ldmfd	sp, {fp, sp, pc}
.L616:
	.align	2
.L615:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	CloseUsdPool_WithMem, .-CloseUsdPool_WithMem
	.align	2
	.global	InitUsdPool
	.type	InitUsdPool, %function
InitUsdPool:
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
	ldr	r3, .L622
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #128]
	cmp	r0, #0
	beq	.L620
	add	r1, r0, #203776
	mov	ip, #0
	add	r1, r1, #512
	mov	r3, r0
	mov	r2, ip
	str	ip, [r0]
.L619:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L619
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L620:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L623:
	.align	2
.L622:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	InitUsdPool, .-InitUsdPool
	.align	2
	.global	GetUsd
	.type	GetUsd, %function
GetUsd:
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
	ldr	r3, .L631
	add	r0, r3, r0, lsl #2
	ldr	ip, [r0, #128]
	cmp	ip, #0
	beq	.L628
	mov	r3, ip
	mov	r2, #0
	b	.L627
.L626:
	add	r2, r2, #1
	add	r3, r3, #1056
	cmp	r2, #192
	add	r3, r3, #8
	beq	.L630
.L627:
	ldr	r1, [r3, #1048]
	cmp	r1, #0
	bne	.L626
	ldr	r1, [r3, #1044]
	cmp	r1, #0
	bne	.L626
	movw	r0, #1064
	mov	r4, #0
	mul	r3, r0, r2
	mov	r5, #0
	mla	r2, r2, r0, r0
	add	r6, ip, r3
	add	r3, r3, #8
	add	lr, r6, #1024
	add	r0, ip, r3
	str	r1, [r6, #1044]
	add	lr, lr, #8
	strd	r4, [ip, r2]
	str	r1, [r6, #1060]
	str	r1, [r6, #1056]
	str	r1, [r6, #1052]
	strb	r1, [r6, #1034]
	strb	r1, [r6, #1035]
	strb	r1, [r6, #1036]
	strh	r1, [lr, #6]	@ movhi
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L630:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L628:
	mov	r0, ip
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L632:
	.align	2
.L631:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	GetUsd, .-GetUsd
	.align	2
	.global	FreeUsdByDec
	.type	FreeUsdByDec, %function
FreeUsdByDec:
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
	movne	r3, #0
	strne	r3, [r1, #1040]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FreeUsdByDec, .-FreeUsdByDec
	.align	2
	.global	MarkUsdByDnr
	.type	MarkUsdByDnr, %function
MarkUsdByDnr:
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
	movne	r3, #1
	strne	r3, [r1, #1036]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MarkUsdByDnr, .-MarkUsdByDnr
	.align	2
	.global	UnMarkUsdByDnr
	.type	UnMarkUsdByDnr, %function
UnMarkUsdByDnr:
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
	movne	r3, #0
	strne	r3, [r1, #1036]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkUsdByDnr, .-UnMarkUsdByDnr
	.align	2
	.global	IsImageInVoQueue
	.type	IsImageInVoQueue, %function
IsImageInVoQueue:
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
	beq	.L659
	ldrh	r3, [r0, #4]
	ldrh	lr, [r0, #8]
	and	r3, r3, #63
	cmp	lr, r3
	beq	.L653
.L652:
	add	r2, r0, r3, lsl #2
	add	r3, r3, #1
	and	r3, r3, #63
	ldr	r2, [r2, #12]
	cmp	r2, #0
	beq	.L651
	ldr	ip, [r2, #148]
	ldr	r2, [r1, #148]
	cmp	ip, r2
	beq	.L654
.L651:
	cmp	r3, lr
	bne	.L652
.L653:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L654:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L659:
	mov	r0, r1
	ldr	r1, .L660
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L661:
	.align	2
.L660:
	.word	.LC6
	UNWIND(.fnend)
	.size	IsImageInVoQueue, .-IsImageInVoQueue
	.align	2
	.global	IsVoQueueEmpty
	.type	IsVoQueueEmpty, %function
IsVoQueueEmpty:
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
	beq	.L666
	ldrh	r0, [r4, #8]
	ldrh	r3, [r4, #6]
	cmp	r0, r3
	ldreqh	r3, [r4, #4]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L666:
	ldr	r2, .L667
	ldr	r1, .L667+4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L668:
	.align	2
.L667:
	.word	.LANCHOR1+76
	.word	.LC32
	UNWIND(.fnend)
	.size	IsVoQueueEmpty, .-IsVoQueueEmpty
	.align	2
	.global	SetAspectRatio
	.type	SetAspectRatio, %function
SetAspectRatio:
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
	mov	r3, r0
	cmp	r1, #5
	ldrls	pc, [pc, r1, asl #2]
	b	.L670
.L672:
	.word	.L671
	.word	.L673
	.word	.L674
	.word	.L675
	.word	.L676
	.word	.L677
.L677:
	mov	r1, #0
	mov	r2, #2
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L671:
	mov	r1, #0
	mov	r2, #1
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L673:
	mov	r1, #4
	mov	r2, #3
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L674:
	mov	r1, #16
	mov	r2, #9
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L675:
	mov	r1, #221
	mov	r2, #100
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L676:
	mov	r1, #235
	mov	r2, #100
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L670:
	mov	r0, #1
	mov	r2, r1
	mov	ip, #0
	str	r0, [r3, #104]
	ldr	r1, .L679
	str	ip, [r3, #100]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L680:
	.align	2
.L679:
	.word	.LC33
	UNWIND(.fnend)
	.size	SetAspectRatio, .-SetAspectRatio
	.align	2
	.global	GetVoLastImageID
	.type	GetVoLastImageID, %function
GetVoLastImageID:
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
	ldr	r0, [r0, #296]
	cmp	r0, #1
	mvnls	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetVoLastImageID, .-GetVoLastImageID
	.align	2
	.global	IsMain10Profile
	.type	IsMain10Profile, %function
IsMain10Profile:
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
	ldr	r3, [r0, #300]
	cmp	r3, #1
	beq	.L688
	ldr	r2, [r0, #304]
	cmp	r2, #1
	beq	.L688
	cmp	r3, #2
	moveq	r3, #1
	ldrne	r3, [r0, #308]
	subne	r3, r3, #1
	clzne	r3, r3
	movne	r3, r3, lsr #5
.L686:
	ldr	r0, [r0, #308]
	cmp	r0, #1
	movne	r0, r3
	orreq	r0, r3, #1
	ldmfd	sp, {fp, sp, pc}
.L688:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsMain10Profile, .-IsMain10Profile
	.align	2
	.global	IsPtsRewind
	.type	IsPtsRewind, %function
IsPtsRewind:
	UNWIND(.fnstart)
	@ args = 8, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r1, .L695
	ldrd	r4, [fp, #4]
	ldr	r1, [r1, r0, asl #2]
	subs	r2, r2, r4
	sbc	r3, r3, r5
	ldr	r1, [r1, #128]
	cmp	r1, #0
	bne	.L694
	cmp	r3, #0
	cmpeq	r2, #1000
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L694:
	mov	r1, #0
	movw	r0, #16960
	cmp	r3, r1
	movt	r0, 15
	cmpeq	r2, r0
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L696:
	.align	2
.L695:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	IsPtsRewind, .-IsPtsRewind
	.align	2
	.global	MetadataMapToSec
	.type	MetadataMapToSec, %function
MetadataMapToSec:
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
	.size	MetadataMapToSec, .-MetadataMapToSec
	.align	2
	.global	MetadataUnMapToSec
	.type	MetadataUnMapToSec, %function
MetadataUnMapToSec:
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
	.size	MetadataUnMapToSec, .-MetadataUnMapToSec
	.global	pstVdecUsdPool
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__FUNCTION__.15223, %object
	.size	__FUNCTION__.15223, 19
__FUNCTION__.15223:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__func__.15259, %object
	.size	__func__.15259, 20
__func__.15259:
	.ascii	"SYNTAX_ReceiveImage\000"
	.type	__func__.15305, %object
	.size	__func__.15305, 20
__func__.15305:
	.ascii	"SYNTAX_ReleaseImage\000"
	.type	__func__.15434, %object
	.size	__func__.15434, 13
__func__.15434:
	.ascii	"DecodeStream\000"
	.space	3
	.type	__func__.15607, %object
	.size	__func__.15607, 15
__func__.15607:
	.ascii	"IsVoQueueEmpty\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"Initializing VO queue\012\000" )
	.space	1
.LC1:
	ASCII(.ascii	"VoQueue state: head(%d) history(%d) tail(%d)\000" )
	.space	3
.LC2:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"%d \000" )
.LC4:
	ASCII(.ascii	"ResetVoQueue but queue not empty: head(%d) history(" )
	ASCII(.ascii	"%d) tail(%d)\012\000" )
	.space	3
.LC5:
	ASCII(.ascii	"out_pts: %lld -> %lld Usertag %lld\012\000" )
.LC6:
	ASCII(.ascii	"image point NULL\012\000" )
	.space	2
.LC7:
	ASCII(.ascii	"call InsertVOQueue\012\000" )
.LC8:
	ASCII(.ascii	"FATAL: p_image(id=%d) has already in the VoQueue!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC9:
	ASCII(.ascii	"error=%d,W=%d,H=%d,not acceptable!\012\000" )
.LC10:
	ASCII(.ascii	"Queue=(%02d,%02d,%02d) + F%d\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"%s, pstVoQue is NULL!!!\012\000" )
	.space	3
.LC12:
	ASCII(.ascii	"Queue=(%02d,%02d,%02d) - F%d\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"SYNTAX_ReleaseImage p_image is null\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"Image %d not found in vo queue.\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"image[%d] null\012\000" )
.LC16:
	ASCII(.ascii	"Queue=(%02d,%02d,%02d) x F%d\012\000" )
	.space	2
.LC17:
	ASCII(.ascii	"LENTH ERROR: VC1 S/MP BS is wrong!\012\000" )
.LC18:
	ASCII(.ascii	"SYNTAX ERROR: VC1 S/MP BS is wrong!\012\000" )
	.space	3
.LC19:
	ASCII(.ascii	"pSegMan error!\012\000" )
.LC20:
	ASCII(.ascii	"More than two packet!!!ERROR!!!\012\000" )
	.space	3
.LC21:
	ASCII(.ascii	"pSegMan->CurrSeg.IsLastSeg=%d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"pSegMan->CurrSeg.PhyAddr=%#x\012\000" )
	.space	2
.LC23:
	ASCII(.ascii	"pSegMan->CurrSeg.LenInByte=%#x\012\000" )
.LC24:
	ASCII(.ascii	"ERROR: Wrong PreParseInfo about Vc1 IsAdvProfile!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC25:
	ASCII(.ascii	"ERROR: Wrong PreParseInfo about Vc1 CodecVersion!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC26:
	ASCII(.ascii	"Func: %s, Line: %d\012\000" )
.LC27:
	ASCII(.ascii	"ERROR: VFMW_VP8 one packet stream, but IsLastSeg ==" )
	ASCII(.ascii	" 0\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"ERROR: VFMW_VP6 one packet stream, but IsLastSeg ==" )
	ASCII(.ascii	" 0\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"ERROR: VFMW_VP9 one packet stream, but IsLastSeg ==" )
	ASCII(.ascii	" 0\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"VidStd=%d Error!\012\000" )
	.space	2
.LC31:
	ASCII(.ascii	"pu8[0] = %x,pu8[1] = %x, pu8[2] = %x\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"%s pstVoQue NULL\012\000" )
	.space	2
.LC33:
	ASCII(.ascii	"WARNNING: aspect ration (%d) is not expected!\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	last_rec_pos_time.15220, %object
	.size	last_rec_pos_time.15220, 128
last_rec_pos_time.15220:
	.space	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 128
pstVdecUsdPool:
	.space	128
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
