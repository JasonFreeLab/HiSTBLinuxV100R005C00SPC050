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
	.word	.L35
	.word	.L19
	.word	.L36
.L36:
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
.L35:
	ldr	r1, [r2, #148]
	mov	r0, r3
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2DEC_RecycleImage
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
	beq	.L38
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
	beq	.L48
	cmp	r2, #1
	mvnhi	r6, #0
	mvnhi	r7, #0
	bls	.L40
.L38:
	mov	r0, r6
	mov	r1, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L48:
	cmp	r2, #1
	bhi	.L38
	ldrb	r2, [r3, #64]	@ zero_extendqisi2
	and	r2, r2, #3
	cmp	r2, #2
	bne	.L38
.L40:
	mvn	r1, #0
	str	r1, [r3, #576]
	mov	r6, r1
	mov	r7, r1
	str	r1, [r3, #580]
	b	.L38
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
	ldr	ip, .L50
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
	ldr	r1, .L50+4
	ldrd	r2, [r5]
	strd	r6, [sp]
	strd	r8, [sp, #8]
	bl	dprint_vfmw
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L51:
	.align	2
.L50:
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
	beq	.L53
	ldr	r3, [r4, #80]
	cmp	r3, #0
	bne	.L78
.L53:
	ldr	r2, [r4, #68]
	ldr	r3, [r4, #72]
	mov	r1, r2, lsr #1
	str	r2, [r4, #76]
	str	r3, [r4, #80]
	mov	r3, r3, lsr #1
	str	r1, [r4, #84]
	str	r3, [r4, #88]
.L54:
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
	beq	.L56
	ldr	r1, .L80
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L57
	strb	r3, [fp, #-52]
	mov	r1, #7
	strb	r2, [fp, #-51]
	mov	r3, #2
	sub	r2, fp, #52
	mov	r0, r8
	blx	ip
.L57:
	str	r10, [r5, #272]
.L56:
	ldr	r3, [r5, #276]
	cmp	r3, r9
	beq	.L58
	ldr	r3, .L80
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L59
	sub	r2, fp, #44
	mov	r3, #1
	mov	r1, #4
	mov	r0, r8
	strb	r7, [r2, #-8]!
	blx	ip
.L59:
	str	r9, [r5, #276]
.L58:
	ldr	r3, [r5, #288]
	cmp	r3, r6
	beq	.L79
.L60:
	ldr	r3, .L80
	ldr	r2, [fp, #-56]
	str	r6, [r5, #288]
	ldr	ip, [r3]
	str	r2, [r5, #292]
	cmp	ip, #0
	beq	.L61
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
.L61:
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
.L78:
	sub	r3, r1, #15
	cmp	r1, #0
	cmpne	r3, #1
	ldrls	r2, [r4, #68]
	bhi	.L53
	b	.L54
.L79:
	ldr	r3, [r5, #292]
	ldr	r2, [fp, #-56]
	cmp	r3, r2
	bne	.L60
	b	.L61
.L81:
	.align	2
.L80:
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
	ldr	r3, .L84
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {fp, sp, pc}
	mov	r2, r1
	mov	r3, #632
	mov	r1, #5
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	bx	ip
.L85:
	.align	2
.L84:
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
	beq	.L114
	ldr	r6, .L117
	mov	r0, #2
	ldr	r1, .L117+4
	bl	dprint_vfmw
	mov	r0, #2
	ldr	r3, [r6, #12]
	blx	r3
	ldrh	r4, [r5, #4]
	ldrh	r3, [r5, #8]
	and	r4, r4, #63
	cmp	r3, r4
	bne	.L94
	b	.L93
.L92:
	add	r4, r4, #1
	ldrh	r3, [r5, #8]
	and	r4, r4, #63
	cmp	r3, r4
	beq	.L93
.L94:
	add	ip, r5, r4, lsl #2
	ldr	r3, [r10, #148]
	ldr	r2, [ip, #12]
	ldr	r2, [r2, #148]
	cmp	r2, r3
	bne	.L92
	ldr	r1, .L117+8
	mov	r0, #0
	bl	dprint_vfmw
	mov	r3, #1000
	str	r3, [r10, #152]
	b	.L92
.L93:
	ldr	r2, [r10, #152]
	cmp	r2, #100
	bhi	.L90
	ldr	r3, [r10, #68]
	cmp	r3, #31
	bhi	.L115
.L90:
	ldr	r3, [r10, #68]
	ldr	r1, [r10, #72]
.L95:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L117+12
	bl	dprint_vfmw
	ldr	r3, [r10, #152]
	cmp	r3, #1000
	beq	.L97
	mov	r2, r10
	mov	r1, r9
	mov	r0, r8
	bl	ReturnImageToSyntax
.L97:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, #1
.L88:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L115:
	ldr	r1, [r10, #72]
	cmp	r1, #31
	bls	.L95
	add	r1, r10, #416
	mov	r0, r7
	str	r8, [r10, #216]
	bl	VCTRL_GetHDRConfigInfo
	mov	r3, r10
	mov	r2, r5
	mov	r1, r8
	mov	r0, r7
	ldr	r4, .L117+16
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
	ldr	r1, .L117+20
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	ldrh	r3, [r5, #8]
	ldr	r0, .L117+24
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
	ldr	r1, .L117+28
	ldr	r3, [r10, #160]
	mov	r0, #2
	ldr	r2, [r6, #16]
	add	r3, r3, #1
	str	r3, [r1, r7, asl #2]
	blx	r2
	ldr	r3, .L117+32
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L98
	mov	r2, r10
	mov	r3, #632
	mov	r1, #5
	mov	r0, r7
	blx	ip
.L98:
	mov	r0, #8
	bl	CHECK_REC_POS_ENABLE
	cmp	r0, #0
	bne	.L116
.L100:
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
	bcc	.L88
	ldr	r3, [r6, #4]
	cmp	r3, #0
	beq	.L102
	movw	r0, #10000
	mul	r0, r0, r3
	bl	__aeabi_uidiv
	str	r0, [r6, #8]
.L102:
	mov	r3, #300
	mov	r2, #0
	mul	r7, r3, r7
	mov	r0, #1
	add	r3, r4, r7
	str	r8, [r4, r7]
	str	r2, [r3, #4]
	b	.L88
.L116:
	ldr	r3, [r6]
	blx	r3
	ldr	ip, .L117+36
	ldr	r2, .L117+40
	ldr	r3, [ip, r7, asl #2]
	ldr	r2, [r2]
	rsb	r3, r3, r0
	mov	lr, r0
	cmp	r3, r2
	bls	.L100
	mov	r2, r7, asl #24
	movw	r1, #517
	add	r2, r2, #524288
	ldr	r0, .L117+44
	str	lr, [ip, r7, asl #2]
	bl	DBG_AddTrace
	b	.L100
.L114:
	mov	r0, r10
	ldr	r1, .L117+48
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L88
.L118:
	.align	2
.L117:
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
	b	.L143
.L128:
	.word	.L142
	.word	.L129
	.word	.L130
	.word	.L131
	.word	.L143
	.word	.L132
	.word	.L133
	.word	.L143
	.word	.L134
	.word	.L135
	.word	.L136
	.word	.L136
	.word	.L136
	.word	.L137
	.word	.L143
	.word	.L138
	.word	.L139
	.word	.L140
	.word	.L141
	.word	.L143
	.word	.L142
.L142:
	add	r0, r0, #16
	ldmfd	sp, {fp, sp, pc}
.L129:
	add	r0, r0, #49152
	add	r0, r0, #128
	ldmfd	sp, {fp, sp, pc}
.L130:
	add	r0, r0, #22528
	add	r0, r0, #104
	ldmfd	sp, {fp, sp, pc}
.L131:
	add	r0, r0, #88064
	add	r0, r0, #136
	ldmfd	sp, {fp, sp, pc}
.L132:
	add	r0, r0, #41984
	add	r0, r0, #40
	ldmfd	sp, {fp, sp, pc}
.L133:
	add	r0, r0, #16192
	add	r0, r0, #8
	ldmfd	sp, {fp, sp, pc}
.L134:
	add	r0, r0, #54272
	add	r0, r0, #80
	ldmfd	sp, {fp, sp, pc}
.L135:
	add	r0, r0, #54272
	add	r0, r0, #72
	ldmfd	sp, {fp, sp, pc}
.L136:
	add	r0, r0, #12672
	add	r0, r0, #24
	ldmfd	sp, {fp, sp, pc}
.L137:
	add	r0, r0, #8192
	add	r0, r0, #24
	ldmfd	sp, {fp, sp, pc}
.L138:
	add	r0, r0, #592
	ldmfd	sp, {fp, sp, pc}
.L139:
	add	r0, r0, #6144
	add	r0, r0, #32
	ldmfd	sp, {fp, sp, pc}
.L140:
	add	r0, r0, #274432
	add	r0, r0, #4032
	ldmfd	sp, {fp, sp, pc}
.L141:
	add	r0, r0, #17920
	add	r0, r0, #152
	ldmfd	sp, {fp, sp, pc}
.L143:
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
	beq	.L148
	bl	SYNTAX_GetVoQue
	subs	r4, r0, #0
	beq	.L150
	ldr	r7, .L151
	mov	r0, #2
	ldr	r3, [r7, #12]
	blx	r3
	ldrh	r3, [r4, #6]
	ldrh	r2, [r4, #8]
	cmp	r2, r3
	mvneq	r5, #2
	beq	.L147
	add	r10, r6, #496
	add	r3, r4, r3, lsl #2
	ldr	ip, [r7, #52]
	mov	r2, #632
	ldrd	r8, [r10]
	mov	r0, r6
	ldr	r1, [r3, #12]
	mov	r5, #1
	blx	ip
	ldr	r1, .L151+4
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
.L147:
	ldr	r3, [r7, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r5
.L145:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L148:
	mvn	r0, #1
	b	.L145
.L150:
	ldr	r2, .L151+8
	mov	r0, #1
	ldr	r1, .L151+12
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L145
.L152:
	.align	2
.L151:
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
	b	.L154
.L156:
	.word	.L159
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L154
	.word	.L159
	.word	.L159
	.word	.L159
.L159:
	cmp	r1, #0
	mvnne	r0, #19
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L154:
	cmn	r1, #2
	beq	.L165
	cmp	r1, #1
	mvnne	r0, #19
	moveq	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L165:
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
	b	.L185
.L170:
	.word	.L169
	.word	.L171
	.word	.L172
	.word	.L173
	.word	.L185
	.word	.L174
	.word	.L175
	.word	.L185
	.word	.L176
	.word	.L177
	.word	.L178
	.word	.L178
	.word	.L178
	.word	.L179
	.word	.L185
	.word	.L180
	.word	.L181
	.word	.L182
	.word	.L183
	.word	.L185
	.word	.L184
.L184:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	USERDEC_RecycleImage
	mov	r1, r0
.L168:
	mov	r0, r4
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	SYNTAX_ReleaseImage_RecycleImage_CheckRet
.L169:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	H264DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L171:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VC1DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L172:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	MPEG4DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L173:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	MPEG2DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L174:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	DIVX3DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L175:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	AVSDEC_RecycleImage
	mov	r1, r0
	b	.L168
.L176:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	REAL8DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L177:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	REAL9DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L178:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VP6DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L179:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VP8DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L180:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	MVC_DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L181:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	HEVC_DECRecycleImage
	mov	r1, r0
	b	.L168
.L182:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	VP9DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L183:
	ldr	r1, [r1, #148]
	add	r0, r0, #8
	bl	AVS2DEC_RecycleImage
	mov	r1, r0
	b	.L168
.L185:
	mvn	r1, #1
	b	.L168
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
	beq	.L202
	bl	SYNTAX_GetVoQue
	subs	r5, r0, #0
	beq	.L203
	ldr	r6, .L204
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
	bne	.L198
	b	.L197
.L194:
	add	r4, r4, #1
	ldrh	r3, [r5, #6]
	and	r4, r4, #63
	cmp	r3, r4
	beq	.L197
.L198:
	add	r10, r4, #2
	add	r3, r5, r10, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, #0
	beq	.L192
	ldr	r0, [r3, #148]
	rsb	r0, r0, r9
	clz	r0, r0
	mov	r0, r0, lsr #5
	cmp	r0, #0
	beq	.L194
.L193:
	ldrh	r1, [r5, #4]
	b	.L196
.L200:
	mov	r4, ip
.L196:
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
	bne	.L200
	ldr	r3, [r8, #148]
	cmp	r0, #1
	ldr	r2, [r5, #344]
	rsb	r3, r2, r3
	str	r3, [r8, #148]
	ldrh	r2, [r5, #4]
	add	r2, r2, #1
	and	r2, r2, #63
	strh	r2, [r5, #4]	@ movhi
	bne	.L194
	ldr	ip, [r8, #148]
	mov	r0, #12
	ldrh	r3, [r5, #6]
	ldr	r1, .L204+4
	str	ip, [sp, #4]
	ldrh	ip, [r5, #8]
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r1, r8
	mov	r0, r7
	bl	SYNTAX_ReleaseImage_RecycleImage
	mov	r4, r0
	b	.L191
.L192:
	mov	r2, r4
	ldr	r1, .L204+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #2
	b	.L193
.L197:
	mov	r2, r9
	ldr	r1, .L204+12
	mov	r0, #1
	mvn	r4, #1
	bl	dprint_vfmw
.L191:
	ldr	r3, [r6, #16]
	mov	r0, #2
	blx	r3
	mov	r0, r4
.L188:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L202:
	ldr	r1, .L204+16
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L188
.L203:
	ldr	r2, .L204+20
	mov	r0, #1
	ldr	r1, .L204+24
	bl	dprint_vfmw
	mvn	r0, #1
	b	.L188
.L205:
	.align	2
.L204:
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
	b	.L225
.L209:
	.word	.L223
	.word	.L210
	.word	.L211
	.word	.L212
	.word	.L225
	.word	.L213
	.word	.L214
	.word	.L225
	.word	.L215
	.word	.L216
	.word	.L217
	.word	.L217
	.word	.L217
	.word	.L218
	.word	.L225
	.word	.L219
	.word	.L220
	.word	.L221
	.word	.L222
	.word	.L225
	.word	.L223
.L223:
	add	r4, r0, #16
.L224:
	ldr	r5, .L226
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
.L210:
	add	r4, r0, #49152
	add	r4, r4, #128
	b	.L224
.L211:
	add	r4, r0, #22528
	add	r4, r4, #104
	b	.L224
.L212:
	add	r4, r0, #88064
	add	r4, r4, #136
	b	.L224
.L213:
	add	r4, r0, #41984
	add	r4, r4, #40
	b	.L224
.L214:
	add	r4, r0, #16192
	add	r4, r4, #8
	b	.L224
.L215:
	add	r4, r0, #54272
	add	r4, r4, #80
	b	.L224
.L216:
	add	r4, r0, #54272
	add	r4, r4, #72
	b	.L224
.L217:
	add	r4, r0, #12672
	add	r4, r4, #24
	b	.L224
.L218:
	add	r4, r0, #8192
	add	r4, r4, #24
	b	.L224
.L219:
	add	r4, r0, #592
	b	.L224
.L220:
	add	r4, r0, #6144
	add	r4, r4, #32
	b	.L224
.L221:
	add	r4, r0, #274432
	add	r4, r4, #4032
	b	.L224
.L222:
	add	r4, r0, #17920
	add	r4, r4, #152
	b	.L224
.L225:
	mvn	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L227:
	.align	2
.L226:
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
	ldr	r1, .L234
	cmn	r0, #2
	moveq	r3, #1
	movne	r3, #0
	strb	r3, [r4, #1]
	ldr	r0, [r2, #2352]
	ldr	r1, [r1, r0, asl #2]
	strb	r3, [r1, #1456]
	ldr	r4, [r5, #360]
	cmp	r4, #0
	beq	.L233
.L228:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L233:
	add	r5, r5, #12288
	ldrb	r3, [r5, #1272]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L228
	ldr	r0, [r2, #2352]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1272]
	b	.L228
.L235:
	.align	2
.L234:
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
	beq	.L237
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L238
.L237:
	mov	r3, #1
	ldr	r2, .L245
	strb	r3, [r4, #1]
	ldr	r1, [r5, #276]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1456]
	ldr	r4, [r5, #2852]
	cmp	r4, #0
	beq	.L244
.L236:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L238:
	strb	r3, [r4, #1]
	ldr	r2, .L245
	ldr	r1, [r5, #276]
	ldr	r2, [r2, r1, asl #2]
	strb	r3, [r2, #1456]
	ldr	r4, [r5, #2852]
	cmp	r4, #0
	bne	.L236
.L244:
	ldrb	r3, [r5, #11]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L236
	ldr	r0, [r5, #276]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #11]
	b	.L236
.L246:
	.align	2
.L245:
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
	beq	.L262
	ldr	r8, .L264
	add	r7, r0, #88
	add	r1, r0, #8
	mov	r2, #80
	mov	r0, r7
	add	r6, r5, #311296
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
	ldr	r3, [r6, #2768]
	cmp	r3, #0
	bne	.L263
.L249:
	ldr	r3, [r6, #2764]
	cmp	r3, #0
	bne	.L250
.L261:
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
	ldr	r0, [r6, #2860]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L264+4
	ldr	ip, [r3]
	cmp	ip, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r0, [r6, #2860]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	bx	ip
.L263:
	ldr	r2, [r6, #2808]
	ldr	r3, [r6, #2804]
	cmp	r2, r3
	beq	.L249
.L250:
	mov	r3, #1
	b	.L261
.L262:
	add	r5, r1, #311296
	ldr	r0, [r5, #2860]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #2860]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L265:
	.align	2
.L264:
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
	beq	.L270
.L266:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L270:
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L266
	ldr	r0, [r5, #120]
	bl	VCTRL_OutputLastFrame
	strb	r4, [r5, #1]
	b	.L266
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
	beq	.L284
	ldr	r6, .L287
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
	bls	.L285
	add	r2, r5, #15808
	mov	r1, #16
	add	r2, r2, #24
	ldr	r0, [r4, #88]
	bl	Vc1SMPSeqHdr
	subs	r8, r0, #0
	beq	.L286
	ldr	r1, .L287+4
	add	r5, r5, #49152
.L283:
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #108]
	ldr	r0, [r5, #472]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L287+8
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
.L285:
	add	r5, r5, #49152
	ldr	r1, .L287+12
	b	.L283
.L284:
	add	r5, r1, #49152
	ldr	r0, [r5, #472]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #472]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L286:
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
.L288:
	.align	2
.L287:
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
	beq	.L299
	ldr	r7, .L300
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
	ldr	r3, .L300+4
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
.L299:
	add	r5, r1, #53248
	ldr	r0, [r5, #1448]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1448]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L301:
	.align	2
.L300:
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
	beq	.L312
	ldr	r7, .L313
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
	ldr	r3, .L313+4
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
.L312:
	add	r5, r1, #53248
	ldr	r0, [r5, #1440]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1440]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L314:
	.align	2
.L313:
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
	beq	.L325
	ldr	r7, .L326
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
	ldr	r3, .L326+4
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
.L325:
	add	r5, r1, #40960
	ldr	r0, [r5, #1408]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #1408]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L327:
	.align	2
.L326:
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
	beq	.L338
	ldr	r7, .L339
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
	ldr	r3, .L339+4
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
.L338:
	add	r5, r1, #8192
	ldr	r0, [r5, #368]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #368]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L340:
	.align	2
.L339:
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
	beq	.L351
	ldr	r7, .L352
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
	ldr	r3, .L352+4
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
.L351:
	add	r5, r1, #12288
	ldr	r0, [r5, #752]
	bl	VCTRL_OutputLastFrame
	ldr	r0, [r5, #752]
	ldr	r1, [r4, #28]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	SM_ReleaseStreamSeg
.L353:
	.align	2
.L352:
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
	beq	.L355
	ldr	r0, [r4, #8]
	cmp	r0, #0
	beq	.L355
	ldr	r3, .L379
	ldr	r3, [r3, r6, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L375
.L358:
	ldrb	r5, [r4, #14]	@ zero_extendqisi2
	mov	r7, #0
	strb	r7, [r4, #408]
	cmp	r5, #1
	beq	.L376
	cmp	r5, #0
	beq	.L377
.L363:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L377:
	ldr	r9, .L379+4
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
	bls	.L363
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
	ldr	r1, .L379+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L379+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L362
	mov	r0, r6
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	ip
.L362:
	mov	r3, #0
	mvn	r0, #0
	strb	r3, [r4, #2]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L375:
	ldr	r3, [r3, #1432]
	cmp	r3, #1
	bne	.L358
	ldrb	r3, [r4, #408]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L358
	mov	r2, #160
	add	r1, r4, #248
	add	r0, r4, #88
	bl	memcpy
	mov	r3, #0
	mov	r0, r3
	strb	r3, [r4, #408]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L376:
	ldrb	r5, [r4, #2]	@ zero_extendqisi2
	cmp	r5, r7
	beq	.L378
	cmp	r5, #1
	bne	.L363
	ldr	r2, [r4, #104]
	cmp	r2, #1024
	bcs	.L364
	ldr	r8, .L379+4
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
.L365:
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
.L378:
	ldr	r6, .L379+4
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
.L364:
	ldr	r3, .L379+4
	mov	r2, #80
	add	r1, r4, #8
	add	r0, r4, #168
	ldr	r3, [r3, #52]
	blx	r3
	b	.L365
.L355:
	ldr	r1, .L379+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L380:
	.align	2
.L379:
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
	beq	.L386
.L382:
	mov	r1, r5
	ldr	r0, [r6, #472]
	bl	SegMan
	subs	r7, r0, #0
	beq	.L387
.L384:
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
.L387:
	add	r5, r5, #88
	mov	r0, r4
	mov	r1, r5
	bl	VC1DEC_Decode
	ldr	r3, .L389
	mov	r0, r5
	mov	r1, r7
	mov	r2, #160
	ldr	r3, [r3, #48]
	blx	r3
	b	.L384
.L386:
	ldr	r3, .L389+4
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L388
.L383:
	add	r1, r4, #12544
	mov	r0, r4
	add	r1, r1, #32
	bl	VC1DEC_Decode
	b	.L382
.L388:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L382
	b	.L383
.L390:
	.align	2
.L389:
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
	ldr	r1, .L398
	bl	dprint_vfmw
	ldr	r2, [r4, #20]
	ldr	r1, .L398+4
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r4, #24]
	ldr	r1, .L398+8
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r5]
	ldr	r3, [r2, #556]
	cmp	r3, #1
	ldrhi	r1, .L398+12
	bhi	.L395
	ldr	r1, [r2, #560]
	cmp	r1, #8
	bgt	.L396
	add	r1, r5, #12288
	uxtb	r3, r3
	cmp	r3, #1
	mov	r0, r4
	strb	r3, [r1, #3544]
	ldr	r3, [r2, #560]
	strb	r3, [r1, #3546]
	mov	r1, r5
	beq	.L397
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DecodeStream_VC1_Smp
.L396:
	ldr	r1, .L398+16
.L395:
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L397:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	DecodeStream_VC1_Adv
.L399:
	.align	2
.L398:
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
	beq	.L406
.L401:
	mov	r1, r6
	ldr	r0, [r5, #2528]
	bl	SegMan
	cmp	r0, #0
	beq	.L407
.L403:
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
.L407:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG2DEC_Decode
	ldrb	r3, [r5, #2545]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r3, #0
	strb	r3, [r6, #1]
	b	.L403
.L406:
	ldr	r3, .L409
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L408
.L402:
	add	r1, r4, #87040
	mov	r0, r4
	add	r1, r1, #592
	bl	MPEG2DEC_Decode
	b	.L401
.L408:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L401
	b	.L402
.L410:
	.align	2
.L409:
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
	beq	.L416
.L412:
	mov	r1, r6
	ldr	r0, [r5, #2496]
	bl	SegMan
	cmp	r0, #0
	beq	.L417
.L414:
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
.L417:
	add	r1, r6, #88
	mov	r0, r4
	bl	MPEG4DEC_Decode
	b	.L414
.L416:
	ldr	r3, .L419
	ldr	r3, [r3, r7, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L418
.L413:
	add	r1, r4, #15680
	mov	r0, r4
	add	r1, r1, #32
	bl	MPEG4DEC_Decode
	b	.L412
.L418:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L412
	b	.L413
.L420:
	.align	2
.L419:
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
	bne	.L422
	ldr	r3, .L428
	ldr	r3, [r3, r6, asl #2]
	ldr	r2, [r3, #1384]
	cmp	r2, #1
	beq	.L426
	add	r1, r4, #16384
	mov	r0, r4
	add	r1, r1, #168
	bl	AVSDEC_Decode
.L422:
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	SegMan
	cmp	r0, #0
	beq	.L427
.L424:
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
.L426:
	ldr	r3, [r3, #1432]
	cmp	r3, #0
	bne	.L422
	add	r1, r4, #16384
	mov	r0, r4
	add	r1, r1, #168
	bl	AVSDEC_Decode
	b	.L422
.L427:
	add	r1, r5, #88
	mov	r0, r4
	bl	AVSDEC_Decode
	b	.L424
.L429:
	.align	2
.L428:
	.word	s_pstVfmwChan
	UNWIND(.fnend)
	.size	DecodeStream_AVS, .-DecodeStream_AVS
	.align	2
	.global	DecodeStream_AVS2
	.type	DecodeStream_AVS2, %function
DecodeStream_AVS2:
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
	mov	r4, r1
	ldr	r0, [r1, #4]
	mov	r1, r5
	bl	SegMan
	cmp	r0, #0
	beq	.L436
.L431:
	ldr	r3, [r4, #8]
	cmp	r3, #1
	movne	r3, #0
	strb	r3, [r5, #1]
	ldr	r5, [r4, #40]
	cmp	r5, #0
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	VCTRL_OutputLastFrame
	strb	r5, [r4]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L436:
	add	r1, r5, #88
	mov	r0, r4
	bl	AVS2DEC_Decode
	b	.L431
	UNWIND(.fnend)
	.size	DecodeStream_AVS2, .-DecodeStream_AVS2
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
	cmp	r4, #18
	ldrls	pc, [pc, r4, asl #2]
	b	.L438
.L440:
	.word	.L439
	.word	.L441
	.word	.L442
	.word	.L443
	.word	.L438
	.word	.L444
	.word	.L445
	.word	.L438
	.word	.L446
	.word	.L447
	.word	.L448
	.word	.L448
	.word	.L448
	.word	.L449
	.word	.L438
	.word	.L450
	.word	.L451
	.word	.L452
	.word	.L453
.L453:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_AVS2
.L454:
	mov	r0, #7
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	VCTRL_RecordPosTime
.L439:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_H264
	b	.L454
.L441:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VC1
	b	.L454
.L442:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG4
	b	.L454
.L443:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MPEG2
	b	.L454
.L444:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_DIVX3
	b	.L454
.L445:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_AVS
	b	.L454
.L446:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL8
	b	.L454
.L447:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_REAL9
	b	.L454
.L448:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP6x
	b	.L454
.L449:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP8
	b	.L454
.L450:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_MVC
	b	.L454
.L451:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_HEVC
	b	.L454
.L452:
	mov	r1, r6
	mov	r0, r5
	bl	DecodeStream_VP9
	b	.L454
.L438:
	movw	r3, #1782
	ldr	r2, .L455
	ldr	r1, .L455+4
	mov	r0, #32
	bl	dprint_vfmw
	b	.L454
.L456:
	.align	2
.L455:
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
	b	.L458
.L460:
	.word	.L459
	.word	.L458
	.word	.L458
	.word	.L461
	.word	.L462
	.word	.L463
	.word	.L463
	.word	.L463
	.word	.L464
	.word	.L458
	.word	.L458
	.word	.L458
	.word	.L465
.L465:
	ldr	r4, [r1]
	add	r1, r1, #311296
	ldr	r0, [r1, #2860]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L471
	ldr	r1, .L481
	mov	r0, #1
	bl	dprint_vfmw
.L471:
	ldr	r3, .L481+4
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L459:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L471
	add	r3, r1, #40960
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1408]
	bl	SM_ReleaseStreamSeg
	b	.L471
.L461:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L471
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1448]
	bl	SM_ReleaseStreamSeg
	b	.L471
.L462:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L471
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1440]
	bl	SM_ReleaseStreamSeg
	b	.L471
.L463:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L471
	ldr	r1, .L481+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L471
.L464:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L471
	ldr	r1, .L481+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L471
.L458:
	mov	r2, r0
	ldr	r1, .L481+16
	mov	r0, #0
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L482:
	.align	2
.L481:
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
	b	.L483
.L486:
	.word	.L485
	.word	.L485
	.word	.L485
	.word	.L487
	.word	.L483
	.word	.L483
	.word	.L483
	.word	.L488
.L488:
	ldr	r4, [r1]
	add	r1, r1, #311296
	ldr	r0, [r1, #2860]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L491
	ldr	r1, .L501
	mov	r0, #1
	bl	dprint_vfmw
.L491:
	ldr	r3, .L501+4
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L487:
	ldr	r4, [r1]
	add	r1, r1, #8192
	ldr	r0, [r1, #368]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L491
	ldr	r1, .L501+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L491
.L485:
	ldr	r4, [r1]
	add	r1, r1, #12288
	ldr	r0, [r1, #752]
	ldr	r1, [r4, #244]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L491
	ldr	r1, .L501+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L491
.L483:
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L502:
	.align	2
.L501:
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
	beq	.L505
	cmp	r0, #9
	ldmnefd	sp, {r4, r5, fp, sp, pc}
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L511
.L508:
	ldr	r3, .L512
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L505:
	ldr	r4, [r1]
	ldrb	r3, [r4, #230]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L508
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1448]
	bl	SM_ReleaseStreamSeg
	b	.L508
.L511:
	add	r3, r1, #53248
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1440]
	bl	SM_ReleaseStreamSeg
	b	.L508
.L513:
	.align	2
.L512:
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
	beq	.L516
.L515:
	ldr	r3, .L517
	add	r0, r4, #224
	mov	r2, #160
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L516:
	add	r3, r1, #40960
	ldr	r1, [r4, #244]
	ldr	r0, [r3, #1408]
	bl	SM_ReleaseStreamSeg
	b	.L515
.L518:
	.align	2
.L517:
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
	cmp	r0, #18
	ldrls	pc, [pc, r0, asl #2]
	b	.L520
.L522:
	.word	.L521
	.word	.L523
	.word	.L524
	.word	.L525
	.word	.L520
	.word	.L526
	.word	.L527
	.word	.L520
	.word	.L528
	.word	.L529
	.word	.L530
	.word	.L530
	.word	.L530
	.word	.L531
	.word	.L520
	.word	.L532
	.word	.L533
	.word	.L534
	.word	.L535
.L535:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS2DEC_ClearCurPic
.L521:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264_ClearCurrPic
.L523:
	add	r3, r1, #49152
	add	r0, r1, #12736
	ldr	r1, [r3, #472]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	VC1_ClearCurPic
.L524:
	mov	r0, r1
	str	r1, [fp, #-16]
	bl	MP4_ClearCurPic
	ldr	r1, [fp, #-16]
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP4_Clean_HeadPacket
.L525:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP2_ClearCurPic
.L526:
	mov	r0, #5
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_DIVX3
.L527:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS_ClearCurPic
.L528:
	mov	r0, #8
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L529:
	mov	r0, #9
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_Realx
.L530:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L531:
	mov	r0, #13
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L532:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_ClearCurrPic
.L533:
	mov	r0, r1
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_ClearCurrPic
.L534:
	mov	r0, #17
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	ReleaseCurPic_VPx
.L520:
	mov	r2, r0
	ldr	r1, .L536
	mov	r0, #0
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L537:
	.align	2
.L536:
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
	beq	.L542
	ldr	r2, [r0]
	cmp	r2, #0
	bne	.L542
	mov	r3, #1
	str	r3, [r0]
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
.L539:
	cmp	r3, #0
	streq	r3, [r0]
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L542:
	mvn	r2, #0
	b	.L539
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
	bne	.L555
.L544:
	cmp	r2, #1
	bne	.L548
.L545:
	mov	r2, #1
	str	r2, [r0]
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	mov	r3, #0
.L546:
	cmp	lr, #182
	moveq	r2, #0
	streq	r2, [r0]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L555:
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L545
	b	.L544
.L548:
	mvn	r3, #0
	b	.L546
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
	beq	.L560
	ldr	ip, [r0]
	cmp	ip, #0
	bne	.L560
	mov	r3, #1
	str	r3, [r0]
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	sub	r2, r3, #179
	clz	r2, r2
	mov	r2, r2, lsr #5
.L557:
	cmp	r3, #182
	movne	r3, r2
	orreq	r3, r2, #1
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0]
	mov	r0, ip
	ldmfd	sp, {fp, sp, pc}
.L560:
	mvn	ip, #0
	b	.L557
	UNWIND(.fnend)
	.size	CheckNewPicSegAVS, .-CheckNewPicSegAVS
	.align	2
	.global	CheckNewPicSegAVS2
	.type	CheckNewPicSegAVS2, %function
CheckNewPicSegAVS2:
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
	add	ip, r3, #80
	add	r2, r3, #74
	sub	lr, r3, #179
	uxtb	r2, r2
	clz	lr, lr
	uxtb	ip, ip
	cmp	r2, #1
	cmphi	ip, #1
	mov	lr, lr, lsr #5
	movls	r2, #1
	movhi	r2, #0
	orrs	r2, lr, r2
	beq	.L568
	ldr	r2, [r0]
	cmp	r2, #0
	bne	.L568
	mov	r3, #1
	str	r3, [r0]
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	sub	lr, r3, #179
	clz	lr, lr
	mov	lr, lr, lsr #5
.L565:
	cmp	r3, #182
	movne	r3, lr
	orreq	r3, lr, #1
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0]
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
.L568:
	mvn	r2, #0
	b	.L565
	UNWIND(.fnend)
	.size	CheckNewPicSegAVS2, .-CheckNewPicSegAVS2
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
	bhi	.L576
	ldr	r3, [r0]
	cmp	r3, #0
	bne	.L576
	mov	r2, #1
	str	r2, [r0]
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
.L573:
	cmp	r2, #13
	moveq	r2, #0
	streq	r2, [r0]
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L576:
	mvn	r3, #0
	b	.L573
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
	cmp	r1, #18
	ldrls	pc, [pc, r1, asl #2]
	b	.L578
.L580:
	.word	.L579
	.word	.L581
	.word	.L582
	.word	.L583
	.word	.L578
	.word	.L578
	.word	.L584
	.word	.L578
	.word	.L578
	.word	.L578
	.word	.L578
	.word	.L578
	.word	.L578
	.word	.L578
	.word	.L578
	.word	.L585
	.word	.L586
	.word	.L578
	.word	.L587
.L587:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegAVS2
.L579:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	H264_IsNewPicNal
.L581:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegVC1
.L582:
	mov	r2, r3
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegMpeg4
.L583:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegMpeg2
.L584:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CheckNewPicSegAVS
.L585:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MVC_IsNewPicNal
.L586:
	mov	r1, ip
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	HEVC_IsNewPicNal
.L578:
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
	beq	.L604
.L589:
	ldrb	lr, [ip]	@ zero_extendqisi2
	ldrb	r4, [ip, #1]	@ zero_extendqisi2
	cmp	lr, #0
	ldrb	ip, [ip, #2]	@ zero_extendqisi2
	bne	.L592
	cmp	r4, #0
	bne	.L592
	cmp	ip, #1
	bne	.L592
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	CheckNewPicSegByVidStd
.L604:
	ldrb	r3, [r2, #72]	@ zero_extendqisi2
	ands	r3, r3, #1
	beq	.L589
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	CheckNewPicSegByVidStd
.L592:
	str	ip, [sp]
	mov	r3, r4
	mov	r2, lr
	ldr	r1, .L605
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L606:
	.align	2
.L605:
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
	ldr	r4, .L614
	add	r4, r4, r0, lsl #2
	ldr	ip, [r4, #128]
	cmp	ip, #0
	beq	.L613
.L608:
	add	r1, ip, #203776
	mov	r0, #0
	add	r1, r1, #512
	mov	r3, ip
	mov	r2, r0
	str	r0, [ip]
.L610:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L610
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L613:
	ldr	r3, .L614+4
	movw	r0, #7688
	movt	r0, 3
	ldr	r3, [r3, #208]
	blx	r3
	cmp	r0, #0
	str	r0, [r4, #128]
	movne	ip, r0
	bne	.L608
.L611:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L615:
	.align	2
.L614:
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
	ldr	r4, .L621
	add	r4, r4, r0, lsl #2
	ldr	r0, [r4, #128]
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r3, .L621+4
	ldr	r3, [r3, #212]
	blx	r3
	mov	r3, #0
	str	r3, [r4, #128]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L622:
	.align	2
.L621:
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
	ldr	r3, .L630
	add	r0, r3, r0, lsl #2
	ldr	ip, [r0, #128]
	cmp	ip, #0
	beq	.L629
.L624:
	add	r1, ip, #203776
	mov	r0, #0
	add	r1, r1, #512
	mov	r3, ip
	mov	r2, r0
	str	r0, [ip]
.L626:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L626
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L629:
	cmp	r1, #0
	str	r1, [r0, #128]
	movne	ip, r1
	bne	.L624
.L627:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L631:
	.align	2
.L630:
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
	ldr	r3, .L637
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #128]
	cmp	r3, #0
	movne	r3, #0
	strne	r3, [r0, #128]
	ldmfd	sp, {fp, sp, pc}
.L638:
	.align	2
.L637:
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
	ldr	r3, .L644
	add	r0, r3, r0, lsl #2
	ldr	r0, [r0, #128]
	cmp	r0, #0
	beq	.L642
	add	r1, r0, #203776
	mov	ip, #0
	add	r1, r1, #512
	mov	r3, r0
	mov	r2, ip
	str	ip, [r0]
.L641:
	str	r2, [r3, #1048]
	add	r3, r3, #1056
	str	r2, [r3, #-12]
	add	r3, r3, #8
	cmp	r3, r1
	bne	.L641
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L642:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L645:
	.align	2
.L644:
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
	ldr	r3, .L653
	add	r0, r3, r0, lsl #2
	ldr	ip, [r0, #128]
	cmp	ip, #0
	beq	.L650
	mov	r3, ip
	mov	r2, #0
	b	.L649
.L648:
	add	r2, r2, #1
	add	r3, r3, #1056
	cmp	r2, #192
	add	r3, r3, #8
	beq	.L652
.L649:
	ldr	r1, [r3, #1048]
	cmp	r1, #0
	bne	.L648
	ldr	r1, [r3, #1044]
	cmp	r1, #0
	bne	.L648
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
.L652:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L650:
	mov	r0, ip
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L654:
	.align	2
.L653:
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
	beq	.L681
	ldrh	r3, [r0, #4]
	ldrh	lr, [r0, #8]
	and	r3, r3, #63
	cmp	lr, r3
	beq	.L675
.L674:
	add	r2, r0, r3, lsl #2
	add	r3, r3, #1
	and	r3, r3, #63
	ldr	r2, [r2, #12]
	cmp	r2, #0
	beq	.L673
	ldr	ip, [r2, #148]
	ldr	r2, [r1, #148]
	cmp	ip, r2
	beq	.L676
.L673:
	cmp	r3, lr
	bne	.L674
.L675:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L676:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L681:
	mov	r0, r1
	ldr	r1, .L682
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L683:
	.align	2
.L682:
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
	beq	.L688
	ldrh	r0, [r4, #8]
	ldrh	r3, [r4, #6]
	cmp	r0, r3
	ldreqh	r3, [r4, #4]
	rsbeq	r0, r0, r3
	clzeq	r0, r0
	moveq	r0, r0, lsr #5
	movne	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L688:
	ldr	r2, .L689
	ldr	r1, .L689+4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L690:
	.align	2
.L689:
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
	b	.L692
.L694:
	.word	.L693
	.word	.L695
	.word	.L696
	.word	.L697
	.word	.L698
	.word	.L699
.L699:
	mov	r1, #0
	mov	r2, #2
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L693:
	mov	r1, #0
	mov	r2, #1
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L695:
	mov	r1, #4
	mov	r2, #3
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L696:
	mov	r1, #16
	mov	r2, #9
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L697:
	mov	r1, #221
	mov	r2, #100
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L698:
	mov	r1, #235
	mov	r2, #100
	str	r1, [r0, #100]
	str	r2, [r0, #104]
	ldmfd	sp, {fp, sp, pc}
.L692:
	mov	r0, #1
	mov	r2, r1
	mov	ip, #0
	str	r0, [r3, #104]
	ldr	r1, .L701
	str	ip, [r3, #100]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	dprint_vfmw
.L702:
	.align	2
.L701:
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
	ldr	r3, [r0, #324]
	cmp	r3, #1
	beq	.L710
	ldr	r2, [r0, #328]
	cmp	r2, #1
	beq	.L710
	cmp	r3, #2
	moveq	r3, #1
	ldrne	r3, [r0, #332]
	subne	r3, r3, #1
	clzne	r3, r3
	movne	r3, r3, lsr #5
.L708:
	ldr	r0, [r0, #332]
	cmp	r0, #1
	movne	r0, r3
	orreq	r0, r3, #1
	ldmfd	sp, {fp, sp, pc}
.L710:
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
	ldr	r1, .L717
	ldrd	r4, [fp, #4]
	ldr	r1, [r1, r0, asl #2]
	subs	r2, r2, r4
	sbc	r3, r3, r5
	ldr	r1, [r1, #128]
	cmp	r1, #0
	bne	.L716
	cmp	r3, #0
	cmpeq	r2, #1000
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L716:
	mov	r1, #0
	movw	r0, #16960
	cmp	r3, r1
	movt	r0, 15
	cmpeq	r2, r0
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L718:
	.align	2
.L717:
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
	.type	__FUNCTION__.15732, %object
	.size	__FUNCTION__.15732, 19
__FUNCTION__.15732:
	.ascii	"InsertImgToVoQueue\000"
	.space	1
	.type	__func__.15769, %object
	.size	__func__.15769, 20
__func__.15769:
	.ascii	"SYNTAX_ReceiveImage\000"
	.type	__func__.15816, %object
	.size	__func__.15816, 20
__func__.15816:
	.ascii	"SYNTAX_ReleaseImage\000"
	.type	__func__.15953, %object
	.size	__func__.15953, 13
__func__.15953:
	.ascii	"DecodeStream\000"
	.space	3
	.type	__func__.16134, %object
	.size	__func__.16134, 15
__func__.16134:
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
	.type	last_rec_pos_time.15729, %object
	.size	last_rec_pos_time.15729, 128
last_rec_pos_time.15729:
	.space	128
	.type	pstVdecUsdPool, %object
	.size	pstVdecUsdPool, 128
pstVdecUsdPool:
	.space	128
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
