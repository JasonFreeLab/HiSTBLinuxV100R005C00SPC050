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
	.file	"h264.c"
	.text
	.align	2
	.global	IsSTRefFlg
	.type	IsSTRefFlg, %function
IsSTRefFlg:
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
	ldr	r0, [r0]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsSTRefFlg, .-IsSTRefFlg
	.align	2
	.global	IsLTRefFlg
	.type	IsLTRefFlg, %function
IsLTRefFlg:
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
	ldr	r0, [r0]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsLTRefFlg, .-IsLTRefFlg
	.align	2
	.global	compare_pic_by_pic_num_desc
	.type	compare_pic_by_pic_num_desc, %function
compare_pic_by_pic_num_desc:
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
	blt	.L5
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L5:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_pic_num_desc, .-compare_pic_by_pic_num_desc
	.align	2
	.global	compare_pic_by_lt_pic_num_asc
	.type	compare_pic_by_lt_pic_num_asc, %function
compare_pic_by_lt_pic_num_asc:
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
	ldr	r2, [r2, #4]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	blt	.L9
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L9:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_lt_pic_num_asc, .-compare_pic_by_lt_pic_num_asc
	.align	2
	.global	compare_fs_by_frame_num_desc
	.type	compare_fs_by_frame_num_desc, %function
compare_fs_by_frame_num_desc:
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
	ldr	r2, [r2, #656]
	ldr	r3, [r3, #656]
	cmp	r2, r3
	blt	.L12
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L12:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_frame_num_desc, .-compare_fs_by_frame_num_desc
	.align	2
	.global	compare_fs_by_lt_pic_idx_asc
	.type	compare_fs_by_lt_pic_idx_asc, %function
compare_fs_by_lt_pic_idx_asc:
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
	ldr	r2, [r2, #660]
	ldr	r3, [r3, #660]
	cmp	r2, r3
	bcc	.L15
	movhi	r0, #1
	movls	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L15:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_lt_pic_idx_asc, .-compare_fs_by_lt_pic_idx_asc
	.align	2
	.global	compare_pic_by_poc_asc
	.type	compare_pic_by_poc_asc, %function
compare_pic_by_poc_asc:
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
	ldr	r2, [r2, #12]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	blt	.L18
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L18:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_poc_asc, .-compare_pic_by_poc_asc
	.align	2
	.global	compare_pic_by_poc_desc
	.type	compare_pic_by_poc_desc, %function
compare_pic_by_poc_desc:
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
	ldr	r2, [r2, #12]
	ldr	r3, [r3, #12]
	cmp	r2, r3
	blt	.L21
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L21:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_pic_by_poc_desc, .-compare_pic_by_poc_desc
	.align	2
	.global	compare_fs_by_poc_asc
	.type	compare_fs_by_poc_asc, %function
compare_fs_by_poc_asc:
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
	ldr	r2, [r2, #664]
	ldr	r3, [r3, #664]
	cmp	r2, r3
	blt	.L24
	movgt	r0, #1
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L24:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_poc_asc, .-compare_fs_by_poc_asc
	.align	2
	.global	compare_fs_by_poc_desc
	.type	compare_fs_by_poc_desc, %function
compare_fs_by_poc_desc:
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
	ldr	r2, [r2, #664]
	ldr	r3, [r3, #664]
	cmp	r2, r3
	blt	.L27
	mvngt	r0, #0
	movle	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	compare_fs_by_poc_desc, .-compare_fs_by_poc_desc
	.align	2
	.type	SetFrmRepeatCount.part.3, %function
SetFrmRepeatCount.part.3:
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
	add	ip, r0, #61440
	add	r0, r0, #24576
	ldr	lr, [ip, #2364]
	ldr	r2, [r0, #2136]
	ldr	r3, [ip, #2360]
	add	r2, r2, lr, lsr #1
	add	r0, r2, #1
	mov	r3, r3, lsr #1
	cmp	r3, r0
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
	ldrhi	r3, [ip, #2364]
	ldrls	r3, [ip, #2364]
	addhi	r3, r3, #4
	addls	r3, r3, #2
	str	r3, [ip, #2364]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	SetFrmRepeatCount.part.3, .-SetFrmRepeatCount.part.3
	.align	2
	.type	DumpList.part.7, %function
DumpList.part.7:
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
	add	r8, r0, #26880
	add	r8, r8, #240
	add	r10, r0, #20480
	add	r10, r10, #244
	mov	r7, r0
	mov	r6, #0
	mov	r9, r8
.L33:
	ldr	r3, [r10, #4]!
	cmp	r3, #0
	movne	r5, r9
	movne	r4, #0
	beq	.L36
.L34:
	ldr	ip, [r5, #4]!
	mov	r3, r4
	mov	r2, r6
	ldr	r1, .L64
	mov	r0, #13
	add	r4, r4, #1
	ldr	ip, [ip, #36]
	ldr	lr, [ip, #664]
	str	lr, [sp, #4]
	ldr	ip, [ip, #652]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r10]
	cmp	r4, r3
	bcc	.L34
.L36:
	add	r6, r6, #1
	add	r9, r9, #132
	cmp	r6, #2
	bne	.L33
	add	r5, r7, #20480
	ldr	r3, [r5, #248]
	cmp	r3, #0
	bne	.L60
.L37:
	ldr	r3, [r5, #252]
	cmp	r3, #0
	bne	.L61
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L61:
	ldr	r1, .L64+4
	mov	r0, #13
	bl	dprint_vfmw
	ldr	r3, [r5, #252]
	cmp	r3, #0
	addne	r7, r7, #27136
	movne	r4, #0
	addne	r7, r7, #116
	bne	.L50
	b	.L51
.L62:
	bcc	.L48
	cmp	r2, #2
	ldr	r1, .L64+8
	mov	r0, #13
	bne	.L46
	ldr	r3, [r3, #36]
	ldr	r2, [r3, #664]
	bl	dprint_vfmw
.L46:
	ldr	r3, [r5, #252]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L51
.L50:
	ldr	r3, [r7, #4]!
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L62
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+12
	add	r4, r4, #1
	ldr	r2, [r3, #664]
	bl	dprint_vfmw
	ldr	r3, [r5, #252]
	cmp	r4, r3
	bcc	.L50
.L51:
	ldr	r1, .L64+16
	mov	r0, #13
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L48:
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+20
	ldr	r2, [r3, #664]
	bl	dprint_vfmw
	b	.L46
.L60:
	ldr	r1, .L64+24
	mov	r0, #13
	bl	dprint_vfmw
	ldr	r3, [r5, #248]
	cmp	r3, #0
	movne	r4, #0
	bne	.L38
	b	.L43
.L63:
	bcc	.L41
	cmp	r2, #2
	ldr	r1, .L64+8
	mov	r0, #13
	bne	.L39
	ldr	r3, [r3, #36]
	ldr	r2, [r3, #664]
	bl	dprint_vfmw
.L39:
	ldr	r3, [r5, #248]
	add	r4, r4, #1
	cmp	r4, r3
	bcs	.L43
.L38:
	ldr	r3, [r8, #4]!
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L63
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+12
	add	r4, r4, #1
	ldr	r2, [r3, #664]
	bl	dprint_vfmw
	ldr	r3, [r5, #248]
	cmp	r4, r3
	bcc	.L38
.L43:
	ldr	r1, .L64+16
	mov	r0, #13
	bl	dprint_vfmw
	b	.L37
.L41:
	ldr	r3, [r3, #36]
	mov	r0, #13
	ldr	r1, .L64+20
	ldr	r2, [r3, #664]
	bl	dprint_vfmw
	b	.L39
.L65:
	.align	2
.L64:
	.word	.LC0
	.word	.LC6
	.word	.LC5
	.word	.LC4
	.word	.LC2
	.word	.LC3
	.word	.LC1
	UNWIND(.fnend)
	.size	DumpList.part.7, .-DumpList.part.7
	.align	2
	.type	CombinePacket.part.13, %function
CombinePacket.part.13:
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
	ldr	r1, .L67
	mov	r4, r0
	mov	r0, #7
	bl	dprint_vfmw
	ldr	ip, [r4, #368]
	ldr	r1, .L67+4
	mov	r0, #7
	mov	r5, #0
	ldr	lr, [ip, #40]
	ldr	r3, [ip, #44]
	ldr	r2, [ip, #16]
	str	lr, [sp, #4]
	ldr	ip, [ip, #12]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #368]
	ldr	ip, .L67+8
	ldr	r2, [r3, #12]
	ldr	r0, [r3, #36]
	ldr	r1, [r3, #8]
	rsb	r0, r2, r0
	ldr	r3, [ip, #52]
	blx	r3
	ldr	r3, [r4, #368]
	mov	ip, #1
	ldr	r1, .L67+12
	mov	r0, #7
	ldr	r2, [r3, #60]
	ldr	r6, [r3, #32]
	str	r2, [r3, #32]
	ldr	r3, [r4, #368]
	str	r5, [r3, #24]
	ldr	r3, [r4, #368]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #36]
	rsb	r2, lr, r2
	str	r2, [r3, #8]
	ldr	r3, [r4, #368]
	ldr	lr, [r3, #12]
	ldr	r2, [r3, #44]
	rsb	r2, lr, r2
	str	r2, [r3, #16]
	ldr	r3, [r4, #368]
	ldr	lr, [r3, #40]
	ldr	r2, [r3, #12]
	add	r2, r2, lr
	str	r2, [r3, #12]
	ldr	r3, [r4, #368]
	str	ip, [r3, #68]
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #12]
	ldr	r2, [r2, #16]
	bl	dprint_vfmw
	add	r3, r4, #61440
	mov	r1, r6
	ldr	r0, [r3, #2344]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #368]
	str	r5, [r3, #36]
	ldr	r3, [r4, #368]
	str	r5, [r3, #52]
	ldr	r3, [r4, #368]
	str	r5, [r3, #40]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L68:
	.align	2
.L67:
	.word	.LC7
	.word	.LC8
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	UNWIND(.fnend)
	.size	CombinePacket.part.13, .-CombinePacket.part.13
	.align	2
	.global	ue_v
	.type	ue_v, %function
ue_v:
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
	add	r7, r0, #13504
	mov	r8, r0
	add	r7, r7, #24
	mov	r6, r1
	mov	r1, #32
	mov	r0, r7
	bl	BsShow
	mov	r5, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r4, r0
	bls	.L73
	cmp	r0, #31
	bls	.L74
	add	r3, r8, #61440
	mvn	r5, #0
	mov	r7, #32
	mov	r2, #1
	str	r2, [r3, #2284]
.L71:
	ldr	ip, [r8, #368]
	mov	r2, r6
	mov	r3, r5
	ldr	r1, .L75
	mov	r0, #21
	ldr	lr, [ip, #64]
	add	r4, lr, r7
	str	r4, [ip, #64]
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L73:
	mov	r4, r0, asl #1
	mov	r0, r7
	add	r7, r4, #1
	rsb	r4, r4, #31
	mov	r4, r5, lsr r4
	mov	r1, r7
	sub	r5, r4, #1
	bl	BsSkip
	b	.L71
.L74:
	add	r5, r0, #1
	mov	r1, r0
	mov	r0, r7
	bl	BsSkip
	mov	r1, r5
	mov	r0, r7
	bl	BsShow
	mov	r1, r5
	sub	r5, r0, #1
	mov	r0, r7
	bl	BsSkip
	mov	ip, r4, asl #1
	add	r7, ip, #1
	b	.L71
.L76:
	.align	2
.L75:
	.word	.LC10
	UNWIND(.fnend)
	.size	ue_v, .-ue_v
	.align	2
	.global	se_v
	.type	se_v, %function
se_v:
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
	add	r6, r0, #13504
	mov	r8, r0
	add	r6, r6, #24
	mov	r7, r1
	mov	r1, #32
	mov	r0, r6
	bl	BsShow
	mov	r4, r0
	bl	ZerosMS_32
	cmp	r0, #15
	mov	r5, r0
	bhi	.L78
	mov	r5, r0, asl #1
	mov	r0, r6
	rsb	r3, r5, #31
	add	r5, r5, #1
	mov	r3, r4, lsr r3
	and	r2, r3, #1
	mov	r1, r5
	rsb	r4, r2, #0
	eor	r4, r4, r3, lsr #1
	add	r4, r4, r2
	bl	BsSkip
.L79:
	ldr	lr, [r8, #368]
	mov	r2, r7
	mov	r3, r4
	ldr	r1, .L82
	mov	r0, #21
	ldr	ip, [lr, #64]
	add	r5, ip, r5
	str	r5, [lr, #64]
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L78:
	cmp	r0, #31
	bls	.L81
	add	r3, r8, #61440
	mov	r2, #1
	mvn	r4, #-2147483648
	mov	r5, #32
	str	r2, [r3, #2284]
	b	.L79
.L81:
	mov	r1, r0
	mov	r0, r6
	bl	BsSkip
	mov	r1, r5
	mov	r0, r6
	mov	r5, r5, asl #1
	bl	BsGet
	mov	r1, #1
	add	r5, r5, #1
	mov	r9, r0
	mov	r0, r6
	bl	BsGet
	and	r0, r0, #1
	rsb	r4, r0, #0
	eor	r9, r9, r4
	add	r4, r9, r0
	b	.L79
.L83:
	.align	2
.L82:
	.word	.LC10
	UNWIND(.fnend)
	.size	se_v, .-se_v
	.align	2
	.global	u_v
	.type	u_v, %function
u_v:
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
	add	r0, r0, #13504
	add	r0, r0, #24
	mov	r6, r1
	mov	r7, r2
	bl	BsGet
	ldr	lr, [r5, #368]
	mov	r2, r7
	ldr	r1, .L85
	ldr	ip, [lr, #64]
	add	ip, ip, r6
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r0, #21
	mov	r3, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L86:
	.align	2
.L85:
	.word	.LC10
	UNWIND(.fnend)
	.size	u_v, .-u_v
	.align	2
	.global	u_1
	.type	u_1, %function
u_1:
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
	add	r0, r0, #13504
	mov	r6, r1
	add	r0, r0, #24
	mov	r1, #1
	bl	BsGet
	ldr	lr, [r5, #368]
	mov	r2, r6
	ldr	r1, .L88
	ldr	ip, [lr, #64]
	add	ip, ip, #1
	str	ip, [lr, #64]
	mov	r4, r0
	mov	r3, r0
	mov	r0, #21
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L89:
	.align	2
.L88:
	.word	.LC10
	UNWIND(.fnend)
	.size	u_1, .-u_1
	.align	2
	.global	H264_IsEosNal
	.type	H264_IsEosNal, %function
H264_IsEosNal:
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
	add	r4, r0, #13504
	mov	r1, #32
	add	r4, r4, #24
	mov	r0, r4
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r4
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
	.size	H264_IsEosNal, .-H264_IsEosNal
	.align	2
	.global	GetMinPOC
	.type	GetMinPOC, %function
GetMinPOC:
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
	add	r5, r0, #24576
	mov	ip, #0
	mvn	r3, #-2147483648
	str	ip, [r2]
	str	r3, [r1]
	ldr	r3, [r5, #2140]
	ldr	ip, [r5, #2136]
	cmp	r3, ip
	strhi	ip, [r5, #2140]
	movhi	r3, ip
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #148
.L95:
	ldr	ip, [r0, #4]!
	ldr	r4, [r1]
	ldr	lr, [ip, #664]
	cmp	r4, lr
	ble	.L94
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	strne	lr, [r1]
	strne	r3, [r2]
.L94:
	ldr	ip, [r5, #2140]
	add	r3, r3, #1
	cmp	ip, r3
	bhi	.L95
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetMinPOC, .-GetMinPOC
	.align	2
	.global	GetMinPOCInDPB
	.type	GetMinPOCInDPB, %function
GetMinPOCInDPB:
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
	add	r4, r0, #24576
	mov	ip, #0
	mvn	r3, #-2147483648
	str	ip, [r2]
	str	r3, [r1]
	ldr	r3, [r4, #2140]
	ldr	ip, [r4, #2136]
	cmp	r3, ip
	strhi	ip, [r4, #2140]
	movhi	r3, ip
	cmp	r3, #0
	ldmeqfd	sp, {r4, fp, sp, pc}
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #148
.L105:
	ldr	ip, [r0, #4]!
	ldr	lr, [r1]
	ldr	ip, [ip, #664]
	cmp	lr, ip
	strgt	ip, [r1]
	strgt	r3, [r2]
	add	r3, r3, #1
	ldr	ip, [r4, #2140]
	cmp	ip, r3
	bhi	.L105
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetMinPOCInDPB, .-GetMinPOCInDPB
	.align	2
	.global	GetMaxPOC
	.type	GetMaxPOC, %function
GetMaxPOC:
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
	add	r5, r0, #24576
	mov	r3, #0
	str	r3, [r2]
	str	r3, [r1]
	ldr	r3, [r5, #2140]
	ldr	ip, [r5, #2136]
	cmp	r3, ip
	strhi	ip, [r5, #2140]
	movhi	r3, ip
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #148
.L112:
	ldr	ip, [r0, #4]!
	ldr	r4, [r1]
	ldr	lr, [ip, #664]
	cmp	r4, lr
	bge	.L111
	ldrb	ip, [ip, #4]	@ zero_extendqisi2
	cmp	ip, #0
	strne	lr, [r1]
	strne	r3, [r2]
.L111:
	ldr	ip, [r5, #2140]
	add	r3, r3, #1
	cmp	ip, r3
	bhi	.L112
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetMaxPOC, .-GetMaxPOC
	.align	2
	.global	FrameStoreRefFlg
	.type	FrameStoreRefFlg, %function
FrameStoreRefFlg:
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
	ldrb	r0, [r0, #2]	@ zero_extendqisi2
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	FrameStoreRefFlg, .-FrameStoreRefFlg
	.align	2
	.global	ShortTermRefFlg
	.type	ShortTermRefFlg, %function
ShortTermRefFlg:
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
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L134
	tst	r3, #1
	bne	.L135
.L123:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L127
.L124:
	ldr	r0, [r0, #776]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #65536
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L127:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L135:
	ldr	r2, [r0, #736]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #65536
	bne	.L123
.L128:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L134:
	ldr	r3, [r0, #696]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L128
	ldr	r3, [r0, #736]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	bne	.L124
	b	.L128
	UNWIND(.fnend)
	.size	ShortTermRefFlg, .-ShortTermRefFlg
	.align	2
	.global	LongTermRefFlg
	.type	LongTermRefFlg, %function
LongTermRefFlg:
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
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L151
	tst	r3, #1
	bne	.L152
.L140:
	and	r3, r3, #2
	ands	r3, r3, #255
	beq	.L144
.L141:
	ldr	r0, [r0, #776]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	sub	r0, r0, #256
	clz	r0, r0
	mov	r0, r0, lsr #5
	ldmfd	sp, {fp, sp, pc}
.L144:
	mov	r0, r3
	ldmfd	sp, {fp, sp, pc}
.L152:
	ldr	r2, [r0, #736]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #256
	bne	.L140
.L145:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L151:
	ldr	r3, [r0, #696]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L145
	ldr	r3, [r0, #736]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	bne	.L141
	b	.L145
	UNWIND(.fnend)
	.size	LongTermRefFlg, .-LongTermRefFlg
	.align	2
	.global	UpdateLTReflist
	.type	UpdateLTReflist, %function
UpdateLTReflist:
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
	add	r9, r0, #24576
	mov	r6, r0
	ldr	r8, [r9, #2140]
	cmp	r8, #0
	beq	.L160
	add	r10, r0, #26368
	mov	r4, #0
	add	r10, r10, #148
	mov	r5, r4
.L156:
	ldr	r7, [r10, #4]!
	add	r5, r5, #1
	mov	r0, r7
	bl	LongTermRefFlg
	add	r3, r4, #6656
	add	r3, r3, #6
	cmp	r0, #0
	strne	r7, [r6, r3, asl #2]
	addne	r4, r4, #1
	cmp	r5, r8
	bne	.L156
.L154:
	ldr	r3, [r9, #2136]
	str	r4, [r9, #2148]
	cmp	r3, r4
	ldmlsfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r0, r4, #6656
	mov	r2, #0
	add	r0, r0, #5
	add	r0, r6, r0, lsl #2
.L158:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r3
	bne	.L158
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L160:
	mov	r4, r8
	b	.L154
	UNWIND(.fnend)
	.size	UpdateLTReflist, .-UpdateLTReflist
	.align	2
	.global	UpdateReflist
	.type	UpdateReflist, %function
UpdateReflist:
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
	add	r9, r0, #24576
	mov	r6, r0
	ldr	r8, [r9, #2140]
	cmp	r8, #0
	beq	.L173
	add	r10, r0, #26368
	mov	r4, #0
	add	r10, r10, #148
	mov	r5, r4
.L169:
	ldr	r7, [r10, #4]!
	add	r5, r5, #1
	mov	r0, r7
	bl	ShortTermRefFlg
	add	r3, r4, #6592
	add	r3, r3, #54
	cmp	r0, #0
	strne	r7, [r6, r3, asl #2]
	addne	r4, r4, #1
	cmp	r5, r8
	bne	.L169
.L167:
	ldr	r3, [r9, #2136]
	str	r4, [r9, #2144]
	cmp	r3, r4
	ldmlsfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	add	r0, r4, #6592
	mov	r2, #0
	add	r0, r0, #53
	add	r0, r6, r0, lsl #2
.L171:
	add	r4, r4, #1
	str	r2, [r0, #4]!
	cmp	r4, r3
	bne	.L171
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L173:
	mov	r4, r8
	b	.L167
	UNWIND(.fnend)
	.size	UpdateReflist, .-UpdateReflist
	.align	2
	.global	GetPicNumX
	.type	GetPicNumX, %function
GetPicNumX:
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
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r0, #656]
	mvn	r0, r1
	movne	r3, r3, asl #1
	addne	r3, r3, #1
	add	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	GetPicNumX, .-GetPicNumX
	.align	2
	.global	UnMarkFrameStoreRef
	.type	UnMarkFrameStoreRef, %function
UnMarkFrameStoreRef:
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
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L183
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r1, #737]
	and	r2, r2, #2
	strb	ip, [r1, #738]
	strb	r2, [r1, #2]
.L183:
	tst	r3, #2
	beq	.L184
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	mov	ip, #0
	strb	ip, [r1, #777]
	and	r2, r2, #1
	strb	ip, [r1, #778]
	strb	r2, [r1, #2]
.L184:
	cmp	r3, #3
	add	r0, r0, #61440
	moveq	r3, #0
	streqb	r3, [r1, #698]
	streqb	r3, [r1, #697]
	mov	r3, #0
	mov	r2, r3
	strb	r3, [r1, #2]
	ldr	r1, [r1, #648]
	ldr	r0, [r0, #2344]
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	FSP_SetRef
	UNWIND(.fnend)
	.size	UnMarkFrameStoreRef, .-UnMarkFrameStoreRef
	.align	2
	.type	SlidingWinMark.part.4, %function
SlidingWinMark.part.4:
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
	add	r3, r0, #24576
	mov	r8, r0
	ldr	r7, [r3, #2140]
	cmp	r7, #0
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r6, r0, #26368
	mov	r4, #0
	add	r6, r6, #148
.L195:
	ldr	r5, [r6, #4]!
	add	r4, r4, #1
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	mov	r0, r5
	cmp	r3, #0
	beq	.L194
	bl	ShortTermRefFlg
	cmp	r0, #0
	bne	.L206
.L194:
	cmp	r4, r7
	bne	.L195
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L206:
	mov	r0, r8
	mov	r1, r5
	bl	UnMarkFrameStoreRef
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	UpdateReflist
	UNWIND(.fnend)
	.size	SlidingWinMark.part.4, .-SlidingWinMark.part.4
	.align	2
	.global	UnMarkLTFrmByFrmIdx
	.type	UnMarkLTFrmByFrmIdx, %function
UnMarkLTFrmByFrmIdx:
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
	add	r3, r0, #24576
	ldr	r4, [r3, #2148]
	cmp	r4, #0
	ldmeqfd	sp, {r4, fp, sp, pc}
	ldr	ip, [r3, #2072]
	ldr	r3, [ip, #660]
	cmp	r3, r1
	addne	r2, r0, #26624
	movne	r3, #0
	addne	r2, r2, #24
	bne	.L211
	b	.L209
.L212:
	ldr	ip, [r2, #4]!
	ldr	lr, [ip, #660]
	cmp	lr, r1
	beq	.L209
.L211:
	add	r3, r3, #1
	cmp	r3, r4
	bne	.L212
	ldmfd	sp, {r4, fp, sp, pc}
.L209:
	mov	r1, ip
	sub	sp, fp, #16
	ldmia	sp, {r4, fp, sp, lr}
	b	UnMarkFrameStoreRef
	UNWIND(.fnend)
	.size	UnMarkLTFrmByFrmIdx, .-UnMarkLTFrmByFrmIdx
	.align	2
	.global	UnMarkLTFldByFrmIdx
	.type	UnMarkLTFldByFrmIdx, %function
UnMarkLTFldByFrmIdx:
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
	add	ip, r0, #24576
	ldr	r6, [ip, #2148]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, fp, sp, pc}
	add	r4, r0, #26624
	mov	ip, #0
	add	r4, r4, #20
	b	.L222
.L220:
	cmp	ip, r6
	beq	.L236
.L222:
	ldr	lr, [r4, #4]!
	add	ip, ip, #1
	ldr	r5, [lr, #660]
	cmp	r5, r3
	bne	.L220
	cmp	r2, #1
	ldreqb	r5, [lr, #777]	@ zero_extendqisi2
	beq	.L235
	cmp	r2, #2
	bne	.L220
	ldrb	r5, [lr, #737]	@ zero_extendqisi2
.L235:
	clz	r5, r5
	mov	r5, r5, lsr #5
	cmp	lr, r1
	orrne	r5, r5, #1
	cmp	r5, #0
	beq	.L220
	mov	r1, lr
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	UnMarkFrameStoreRef
.L236:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkLTFldByFrmIdx, .-UnMarkLTFldByFrmIdx
	.align	2
	.global	UnMarkSTRef
	.type	UnMarkSTRef, %function
UnMarkSTRef:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L238
	add	ip, r0, #24576
	ldr	r1, [r1, #656]
	ldr	r4, [ip, #2144]
	sub	r1, r1, #1
	rsb	r2, r2, r1
	cmp	r4, #0
	beq	.L267
	add	ip, r0, #26368
	add	ip, ip, #212
	b	.L244
.L243:
	cmp	r3, r4
	beq	.L268
.L244:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #704]
	cmp	lr, r2
	bne	.L243
	ldrb	lr, [r1, #2]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L243
	ldr	lr, [r1, #696]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L243
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	UnMarkFrameStoreRef
.L238:
	add	r3, r0, #24576
	ldr	r1, [r1, #656]
	ldr	r5, [r3, #2144]
	rsb	r2, r2, r1, lsl #1
	cmp	r5, #0
	beq	.L269
	add	r4, r0, #26368
	mov	ip, #0
	add	r4, r4, #212
	b	.L249
.L245:
	tst	r3, #2
	beq	.L247
	ldr	r3, [r1, #776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L270
.L247:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L271
.L249:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L245
	ldr	lr, [r1, #736]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L245
	ldr	lr, [r1, #744]
	cmp	lr, r2
	bne	.L245
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #24576
	strb	r3, [r1, #2]
	mov	r1, #0
	ldr	r3, [r2, #2008]
	strb	r1, [r3, #738]
	ldr	r3, [r2, #2008]
	ldrb	ip, [r3, #696]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #698]
	ldreq	r3, [r2, #2008]
	streqb	r1, [r3, #697]
	ldreq	r3, [r2, #2008]
	ldrb	r1, [r3, #2]	@ zero_extendqisi2
	cmp	r1, #0
	ldmnefd	sp, {r4, r5, r6, fp, sp, pc}
	ldr	ip, [r3, #684]
	mov	r2, r1
	add	lr, r0, #61440
	add	ip, ip, #15552
	add	ip, ip, #48
	str	r1, [r0, ip, asl #2]
	ldr	r1, [r3, #648]
.L264:
	ldr	r0, [lr, #2344]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	FSP_SetRef
.L270:
	ldr	r3, [r1, #784]
	cmp	r3, r2
	bne	.L247
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #2]
	add	r3, r3, #24576
	mov	r2, #0
	ldr	r1, [r3, #2008]
	strb	r2, [r1, #778]
	ldr	r1, [r3, #2008]
	ldrb	ip, [r1, #696]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r2
	streqb	r2, [r1, #698]
	ldreq	r1, [r3, #2008]
	streqb	r2, [r1, #697]
	ldreq	r1, [r3, #2008]
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #0
	ldmnefd	sp, {r4, r5, r6, fp, sp, pc}
	ldr	ip, [r1, #684]
	add	lr, r0, #61440
	mov	r2, r3
	add	ip, ip, #15552
	add	ip, ip, #48
	str	r3, [r0, ip, asl #2]
	ldr	r1, [r1, #648]
	b	.L264
.L271:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L268:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L267:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L269:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkSTRef, .-UnMarkSTRef
	.align	2
	.global	UnMarkLTRef
	.type	UnMarkLTRef, %function
UnMarkLTRef:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L273
	add	r3, r0, #24576
	ldr	r5, [r3, #2148]
	cmp	r5, #0
	beq	.L301
	add	r4, r0, #26624
	mov	ip, #0
	add	r4, r4, #20
	b	.L282
.L278:
	tst	r3, #2
	beq	.L280
	ldr	r3, [r1, #776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #256
	beq	.L302
.L280:
	add	ip, ip, #1
	cmp	ip, r5
	beq	.L303
.L282:
	ldr	r1, [r4, #4]!
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	ands	r6, r3, #1
	beq	.L278
	ldr	lr, [r1, #736]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L278
	ldr	lr, [r1, #740]
	cmp	r2, lr
	bne	.L278
	add	r2, r0, ip, lsl #2
	and	r3, r3, #2
	add	r2, r2, #24576
	strb	r3, [r1, #2]
	mov	r1, #0
	ldr	r3, [r2, #2072]
	strb	r1, [r3, #737]
	ldr	r3, [r2, #2072]
	ldrb	ip, [r3, #696]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r3, #698]
	ldreq	r3, [r2, #2072]
	streqb	r1, [r3, #697]
	ldreq	r3, [r2, #2072]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #0
	ldreq	r3, [r3, #684]
	addeq	r3, r3, #15552
	addeq	r3, r3, #48
	streq	r2, [r0, r3, asl #2]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L273:
	add	r1, r0, #24576
	ldr	r4, [r1, #2148]
	cmp	r4, #0
	beq	.L304
	add	ip, r0, #26624
	add	ip, ip, #20
	b	.L284
.L283:
	cmp	r3, r4
	beq	.L305
.L284:
	ldr	r1, [ip, #4]!
	add	r3, r3, #1
	ldr	lr, [r1, #700]
	cmp	lr, r2
	bne	.L283
	ldrb	lr, [r1, #2]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L283
	ldr	lr, [r1, #696]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	bne	.L283
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, lr}
	b	UnMarkFrameStoreRef
.L302:
	ldr	r3, [r1, #780]
	cmp	r2, r3
	bne	.L280
	add	r3, r0, ip, lsl #2
	strb	r6, [r1, #2]
	add	r3, r3, #24576
	mov	r1, #0
	ldr	r2, [r3, #2072]
	strb	r1, [r2, #777]
	ldr	r2, [r3, #2072]
	ldrb	ip, [r2, #696]	@ zero_extendqisi2
	cmp	ip, #3
	cmpne	ip, r1
	streqb	r1, [r2, #698]
	ldreq	r2, [r3, #2072]
	streqb	r1, [r2, #697]
	ldreq	r2, [r3, #2072]
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	cmp	r1, #0
	ldreq	r3, [r2, #684]
	addeq	r3, r3, #15552
	addeq	r3, r3, #48
	streq	r1, [r0, r3, asl #2]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L305:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L303:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L304:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L301:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkLTRef, .-UnMarkLTRef
	.align	2
	.global	MarkPicLTRef
	.type	MarkPicLTRef, %function
MarkPicLTRef:
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
	ldrb	r5, [r3, #3]	@ zero_extendqisi2
	add	r3, r0, #24576
	cmp	r5, #0
	beq	.L307
	ldr	r7, [r3, #2144]
	cmp	r7, #0
	beq	.L336
	add	r6, r0, #26368
	mov	ip, #0
	add	r6, r6, #212
	b	.L321
.L313:
	tst	r4, #2
	beq	.L316
	ldr	lr, [r3, #776]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	beq	.L337
.L316:
	add	ip, ip, #1
	cmp	ip, r7
	beq	.L338
.L321:
	ldr	r3, [r6, #4]!
	ldrb	r4, [r3, #2]	@ zero_extendqisi2
	tst	r4, #1
	beq	.L313
	ldr	lr, [r3, #736]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L313
	ldr	lr, [r3, #744]
	cmp	lr, r2
	bne	.L313
	ldrb	lr, [r3, #777]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L317
	ldr	lr, [r3, #660]
	cmp	lr, r1
	bne	.L316
.L317:
	str	r1, [r3, #660]
	sub	r3, r5, #1
	add	r2, r0, ip, lsl #2
	clz	r3, r3
	add	r2, r2, #24576
	mov	ip, #1
	mov	r3, r3, lsr #5
	mov	r0, #0
	add	r1, r3, r1, lsl #1
	ldr	r3, [r2, #2008]
	str	r1, [r3, #740]
	ldr	r3, [r2, #2008]
	strb	ip, [r3, #737]
	ldr	r3, [r2, #2008]
	strb	r0, [r3, #738]
	ldr	r3, [r2, #2008]
	ldrb	r1, [r3, #696]	@ zero_extendqisi2
	cmp	r1, #3
	cmpne	r1, r0
	bne	.L339
	ldrb	r1, [r3, #777]	@ zero_extendqisi2
	ldrb	r0, [r3, #737]	@ zero_extendqisi2
	cmp	r1, r0
	streqb	r1, [r3, #697]
	ldreq	r3, [r2, #2008]
	ldreqb	r2, [r3, #738]	@ zero_extendqisi2
	streqb	r2, [r3, #698]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L307:
	ldr	r6, [r3, #2144]
	cmp	r6, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	lr, r0, #26368
	mov	r3, r5
	add	lr, lr, #212
	b	.L312
.L311:
	add	r3, r3, #1
	cmp	r3, r6
	beq	.L340
.L312:
	ldr	ip, [lr, #4]!
	ldrb	r4, [ip, #2]	@ zero_extendqisi2
	cmp	r4, #3
	bne	.L311
	ldr	r4, [ip, #696]
	bic	r4, r4, #-16777216
	bic	r4, r4, #255
	cmp	r4, #65536
	bne	.L311
	ldr	r4, [ip, #704]
	cmp	r4, r2
	bne	.L311
	add	r3, r0, r3, lsl #2
	str	r1, [ip, #660]
	add	r3, r3, #24576
	mov	r0, #1
	mov	r2, #0
	ldr	ip, [r3, #2008]
	str	r1, [ip, #700]
	ldr	r1, [r3, #2008]
	strb	r0, [r1, #697]
	ldr	r1, [r3, #2008]
	strb	r0, [r1, #737]
	ldr	r1, [r3, #2008]
	strb	r0, [r1, #777]
	ldr	r1, [r3, #2008]
	strb	r2, [r1, #698]
	ldr	r1, [r3, #2008]
	strb	r2, [r1, #738]
	ldr	r3, [r3, #2008]
	strb	r2, [r3, #778]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L337:
	ldr	lr, [r3, #784]
	cmp	lr, r2
	bne	.L316
	ldrb	lr, [r3, #737]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L320
	ldr	lr, [r3, #660]
	cmp	lr, r1
	bne	.L316
.L320:
	str	r1, [r3, #660]
	sub	r3, r5, #2
	add	r0, r0, ip, lsl #2
	clz	r3, r3
	add	r0, r0, #24576
	mov	ip, #1
	mov	r3, r3, lsr #5
	mov	r2, #0
	add	r1, r3, r1, lsl #1
	ldr	r3, [r0, #2008]
	str	r1, [r3, #780]
	ldr	r3, [r0, #2008]
	strb	ip, [r3, #777]
	ldr	r3, [r0, #2008]
	strb	r2, [r3, #778]
	ldr	r3, [r0, #2008]
	ldrb	r2, [r3, #696]	@ zero_extendqisi2
	cmp	r2, #3
	cmpne	r2, #0
	bne	.L341
	ldrb	r2, [r3, #777]	@ zero_extendqisi2
	ldrb	r1, [r3, #737]	@ zero_extendqisi2
	cmp	r2, r1
	streqb	r2, [r3, #697]
	ldreq	r3, [r0, #2008]
	ldreqb	r2, [r3, #778]	@ zero_extendqisi2
	streqb	r2, [r3, #698]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L338:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L340:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L339:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L341:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L336:
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MarkPicLTRef, .-MarkPicLTRef
	.align	2
	.global	MarkSTToLTRef
	.type	MarkSTToLTRef, %function
MarkSTToLTRef:
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
	ldrb	r1, [r1, #3]	@ zero_extendqisi2
	mov	r8, r3
	mov	r7, r0
	cmp	r1, #0
	bne	.L343
	ldr	r5, [r6, #656]
	mov	r1, r3
	sub	r5, r5, #1
	rsb	r5, r2, r5
	bl	UnMarkLTFrmByFrmIdx
.L344:
	mov	r3, r6
	mov	r2, r5
	mov	r1, r8
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	MarkPicLTRef
.L343:
	add	r3, r0, #24576
	ldr	r5, [r6, #656]
	ldr	r1, [r3, #2144]
	rsb	r5, r2, r5, lsl #1
	cmp	r1, #0
	beq	.L344
	add	r2, r0, #26368
	mov	lr, #0
	add	r2, r2, #212
	b	.L347
.L345:
	tst	r3, #2
	beq	.L346
	ldr	r3, [ip, #776]
	bic	r3, r3, #-16777216
	bic	r3, r3, #255
	cmp	r3, #65536
	beq	.L358
.L346:
	cmp	lr, r1
	beq	.L344
.L347:
	ldr	ip, [r2, #4]!
	add	lr, lr, #1
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L345
	ldr	r4, [ip, #736]
	bic	r4, r4, #-16777216
	bic	r4, r4, #255
	cmp	r4, #65536
	bne	.L345
	ldr	r0, [ip, #744]
	cmp	r0, r5
	bne	.L345
	mov	r1, ip
	mov	r3, r8
	mov	r2, #1
	mov	r0, r7
	bl	UnMarkLTFldByFrmIdx
	b	.L344
.L358:
	ldr	r3, [ip, #784]
	cmp	r3, r5
	bne	.L346
	mov	r1, ip
	mov	r3, r8
	mov	r2, #2
	mov	r0, r7
	bl	UnMarkLTFldByFrmIdx
	b	.L344
	UNWIND(.fnend)
	.size	MarkSTToLTRef, .-MarkSTToLTRef
	.align	2
	.global	UpdateMaxLTFrmIdx
	.type	UpdateMaxLTFrmIdx, %function
UpdateMaxLTFrmIdx:
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
	add	r6, r0, #24576
	mov	r7, r0
	ldr	r3, [r6, #2148]
	str	r1, [r6, #2152]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #26624
	mov	r3, r1
	add	r5, r5, #20
	mov	r4, #0
	b	.L363
.L361:
	ldr	r3, [r6, #2148]
	cmp	r3, r4
	ldmlsfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r3, [r6, #2152]
.L363:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	ldr	r2, [r1, #660]
	cmp	r2, r3
	bcc	.L361
	mov	r0, r7
	bl	UnMarkFrameStoreRef
	b	.L361
	UNWIND(.fnend)
	.size	UpdateMaxLTFrmIdx, .-UpdateMaxLTFrmIdx
	.align	2
	.global	UnMarkAllSTRef
	.type	UnMarkAllSTRef, %function
UnMarkAllSTRef:
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
	add	r7, r0, #24576
	mov	r6, r0
	ldr	r3, [r7, #2144]
	cmp	r3, #0
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	add	r5, r0, #26368
	mov	r4, #0
	add	r5, r5, #212
.L366:
	ldr	r1, [r5, #4]!
	mov	r0, r6
	bl	UnMarkFrameStoreRef
	ldr	r3, [r7, #2144]
	add	r4, r4, #1
	cmp	r3, r4
	bhi	.L366
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	UnMarkAllSTRef, .-UnMarkAllSTRef
	.align	2
	.global	MarkCurrPicLT
	.type	MarkCurrPicLT, %function
MarkCurrPicLT:
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
	mov	r5, r2
	ldrb	r2, [r1, #3]	@ zero_extendqisi2
	mov	r4, r1
	cmp	r2, #0
	beq	.L372
	mov	r3, r5
	ldr	r1, [r1, #648]
	bl	UnMarkLTFldByFrmIdx
.L371:
	mov	r2, #1
	mov	r3, #0
	str	r5, [r4, #660]
	strb	r2, [r4, #4]
	strb	r3, [r4, #5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L372:
	mov	r1, r5
	bl	UnMarkLTFrmByFrmIdx
	b	.L371
	UNWIND(.fnend)
	.size	MarkCurrPicLT, .-MarkCurrPicLT
	.align	2
	.global	RemoveFrameStoreOutDPB
	.type	RemoveFrameStoreOutDPB, %function
RemoveFrameStoreOutDPB:
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
	add	r5, r0, r1, lsl #2
	mov	r4, r1
	add	r5, r5, #24576
	mov	r6, r0
	ldr	r2, [r5, #1944]
	cmp	r2, #0
	beq	.L393
	ldr	r3, [r2, #688]
	add	r7, r0, #24576
	mov	r1, #0
	add	r8, r0, #61440
	add	r3, r3, #6656
	add	r3, r3, #26
	add	r3, r0, r3, lsl #2
	str	r1, [r3, #4]
	ldr	r3, [r7, #2416]
	cmp	r3, r1
	subne	r3, r3, #1
	str	r3, [r7, #2416]
	ldr	r1, [r2, #648]
	ldr	r0, [r8, #2344]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L376
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	beq	.L377
	ldr	r3, [r5, #1944]
	mov	r2, #0
	ldr	r0, [r8, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetDisplay
.L377:
	ldr	r3, [r5, #1944]
	mov	r2, #0
	ldr	r0, [r8, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetRef
.L376:
	ldr	r1, [r5, #1944]
	mov	r3, #0
	mvn	r2, #0
	strb	r3, [r1, #1]
	ldr	r1, [r5, #1944]
	strb	r3, [r1, #4]
	ldr	r1, [r5, #1944]
	strb	r3, [r1, #2]
	ldr	r3, [r5, #1944]
	str	r2, [r3, #648]
	ldr	r1, [r7, #2140]
	add	r1, r1, r2
	cmp	r4, r1
	addcc	r2, r4, #6592
	addcc	r2, r2, #38
	addcc	r2, r6, r2, lsl #2
	bcs	.L381
.L380:
	add	r4, r4, #1
	ldr	r3, [r2, #4]!
	cmp	r4, r1
	str	r3, [r2, #-4]
	bne	.L380
.L381:
	add	r3, r1, #6592
	mov	r2, #0
	add	r3, r3, #38
	str	r2, [r6, r3, asl #2]
	str	r1, [r7, #2140]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L393:
	mov	r3, r1
	ldr	r2, .L394
	ldr	r1, .L394+4
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L395:
	.align	2
.L394:
	.word	.LANCHOR0
	.word	.LC11
	UNWIND(.fnend)
	.size	RemoveFrameStoreOutDPB, .-RemoveFrameStoreOutDPB
	.align	2
	.global	RemoveUnUsedFrameStore
	.type	RemoveUnUsedFrameStore, %function
RemoveUnUsedFrameStore:
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
	subs	r5, r0, #0
	beq	.L406
	add	r3, r5, #24576
	ldr	r6, [r3, #2140]
	cmp	r6, #0
	addne	r7, r5, #61440
	movne	r10, #0
	movne	r8, r10
	movne	r9, r10
	bne	.L404
	b	.L405
.L415:
	ldrb	r1, [r2, #4]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L402
	ldr	r0, [r2, #816]
	cmp	r0, #1
	beq	.L402
	strb	r1, [r2, #1]
	mov	r0, r5
	mov	r1, r10
	add	r8, r8, #1
	bl	RemoveFrameStoreOutDPB
	cmp	r8, r6
	beq	.L405
.L404:
	add	r4, r5, r10, lsl #2
	ldr	r0, [r7, #2344]
	add	r4, r4, #24576
	ldr	r2, [r4, #1944]
	ldr	r1, [r2, #648]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L399
	ldrsh	r2, [r0]
	cmp	r2, #0
	bne	.L400
	ldr	r1, [r4, #1944]
	ldrb	r2, [r1, #2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L401
	ldrsb	r0, [r0]
	cmp	r0, #0
	bne	.L414
.L401:
	mvn	r3, #0
	str	r3, [r1, #648]
	ldr	r2, [r4, #1944]
	strb	r9, [r2, #2]
.L399:
	ldr	r1, [r4, #1944]
	ldr	r2, [r1, #816]
	sub	r2, r2, #1
	clz	r2, r2
	mov	r2, r2, lsr #5
	strb	r2, [r1, #4]
.L400:
	ldr	r2, [r4, #1944]
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L415
.L402:
	add	r8, r8, #1
	add	r10, r10, #1
	cmp	r8, r6
	bne	.L404
.L405:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L414:
	ldr	r1, [r1, #648]
	ldr	r0, [r7, #2344]
	bl	FSP_SetRef
	ldr	r1, [r4, #1944]
	b	.L401
.L406:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	RemoveUnUsedFrameStore, .-RemoveUnUsedFrameStore
	.align	2
	.global	CheckFrameStore
	.type	CheckFrameStore, %function
CheckFrameStore:
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
	add	r3, r0, #61440
	mov	r5, r0
	mov	r4, r1
	ldr	r2, [r3, #1044]
	cmp	r2, #0
	bne	.L417
	ldr	r2, [r1, #816]
	cmp	r2, #1
	beq	.L418
	ldr	r2, [r3, #2272]
	cmp	r2, #0
	beq	.L442
.L418:
	mov	r2, #1
	str	r2, [r3, #1044]
.L417:
	ldr	r0, [r3, #2344]
	ldr	r1, [r4, #648]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L420
	ldrsb	r3, [r0, #1]
	cmp	r3, #3
	cmpne	r3, #0
	beq	.L443
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L428
	cmp	r3, #1
	beq	.L428
	ldr	r3, [r4]
	mov	r1, #768
	movt	r1, 768
	bic	r3, r3, #16711680
	bic	r3, r3, #255
	cmp	r3, r1
	beq	.L444
	cmp	r2, #1
	beq	.L445
	cmp	r2, #2
	beq	.L446
.L426:
	ldr	r3, [r5]
	ldr	r2, [r0, #192]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	movls	r0, #0
	bhi	.L447
.L441:
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L442:
	ldr	r2, [r0]
	ldr	r2, [r2, #24]
	cmp	r2, #0
	bne	.L418
	mvn	r0, #0
	b	.L441
.L443:
	ldr	r2, [r4, #648]
	mov	r0, #1
	ldr	r1, .L448
	bl	dprint_vfmw
.L422:
	ldr	r3, [r4, #816]
	cmp	r3, #1
	beq	.L429
	mvn	r0, #2
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L445:
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	tst	r3, #1
	beq	.L426
	mov	r0, r2
	ldr	r1, .L448+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L441
.L446:
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	tst	r3, #2
	beq	.L426
	ldr	r1, .L448+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L441
.L429:
	mov	r3, #2
	mvn	r0, #2
	str	r3, [r4, #816]
	b	.L441
.L420:
	ldr	ip, [r4, #648]
	mov	r2, r4
	ldr	r3, [r4, #816]
	mov	r0, #1
	ldr	r1, .L448+12
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L422
.L428:
	ldr	r1, .L448+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L441
.L447:
	ldr	r1, .L448+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L441
.L444:
	ldrb	r3, [r4, #3]	@ zero_extendqisi2
	mov	r0, #1
	ldr	r1, .L448+24
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L441
.L449:
	.align	2
.L448:
	.word	.LC12
	.word	.LC16
	.word	.LC17
	.word	.LC13
	.word	.LC14
	.word	.LC18
	.word	.LC15
	UNWIND(.fnend)
	.size	CheckFrameStore, .-CheckFrameStore
	.align	2
	.global	GetImagePara
	.type	GetImagePara, %function
GetImagePara:
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
	add	lr, r0, #12288
	mov	r7, r0
	add	r0, r0, #20480
	mov	r4, r1
	ldr	r3, [lr, #1304]
	ldr	r1, [r0, #216]
	mov	r2, #2208
	ldrb	ip, [r4, #81]	@ zero_extendqisi2
	add	r6, r7, #61440
	ldrb	r0, [r4, #80]	@ zero_extendqisi2
	mov	r5, #4000
	mla	r2, r2, r1, r3
	bfc	r0, #0, #2
	ldr	r3, [lr, #1300]
	bfc	ip, #0, #2
	ldr	lr, [r4, #8]
	ldrb	r1, [r4, #82]	@ zero_extendqisi2
	ldrb	r9, [r4, #5]	@ zero_extendqisi2
	ldr	r8, [r2, #28]
	strb	ip, [r4, #81]
	bfi	r1, r9, #1, #1
	strb	r0, [r4, #80]
	ldr	r0, [r6, #1052]
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	mla	r3, r5, r8, r3
	str	r0, [r4, #124]
	strb	r1, [r4, #82]
	str	lr, [r4, #136]
	cmp	r2, #3
	ldrls	pc, [pc, r2, asl #2]
	b	.L496
.L453:
	.word	.L452
	.word	.L454
	.word	.L455
	.word	.L452
.L455:
	ldrb	r2, [r4, #81]	@ zero_extendqisi2
	mov	ip, #3
	ldr	r8, [r4, #680]
	add	r5, r7, #24576
	ldr	lr, [r4, #796]
	and	r2, r2, #240
	ldr	r0, [r4, #812]
	orr	r2, r2, #11
	ldrb	r1, [r4, #80]	@ zero_extendqisi2
	ldr	r9, [r4, #676]
	strb	r2, [r4, #81]
	bfi	r1, r9, #0, #2
	str	r8, [r4, #168]
	strb	r1, [r4, #80]
	str	lr, [r4, #76]
	str	ip, [r4, #72]
	ldr	r2, [r0, #692]
	str	r2, [r4, #728]
.L451:
	ldrb	r2, [r3, #18]	@ zero_extendqisi2
	str	r2, [r4, #412]
	str	r2, [r4, #416]
	ldrb	r2, [r3, #22]	@ zero_extendqisi2
	cmp	r2, #0
	ldrne	r2, [r3, #3332]
	mov	r3, #1
	str	r3, [r4, #420]
	str	r2, [r4, #424]
	ldr	r3, [r7]
	ldr	r3, [r3, #596]
	str	r3, [r4, #140]
	ldr	r3, [r7]
	ldr	r3, [r3, #600]
	str	r3, [r4, #144]
	ldr	r3, [r7]
	ldr	r3, [r3, #604]
	str	r3, [r4, #148]
	ldr	r3, [r7]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L472
	ldrb	r3, [r4, #696]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L472
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	cmp	r2, #3
	ldreqb	r2, [r4, #81]	@ zero_extendqisi2
	bfieq	r2, r3, #0, #2
	streqb	r2, [r4, #81]
.L472:
	add	r3, r4, #608
	str	r3, [fp, #-68]
	mvn	r9, #0
	mvn	r8, #0
	ldrd	r2, [r3, #-8]
	cmp	r3, r9
	cmpeq	r2, r8
	beq	.L474
	ldr	r3, [r5, #2140]
	cmp	r3, #0
	beq	.L474
	add	r8, r7, #26368
	mov	r10, #0
	add	r8, r8, #148
	mvn	r3, #0
	mvn	r2, #1
	strd	r2, [fp, #-52]
	mvn	r3, #0
	str	r3, [fp, #-56]
.L477:
	ldr	r1, [r8, #4]!
	cmp	r1, #0
	beq	.L476
	ldr	r1, [r1, #648]
	ldr	r0, [r6, #2344]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L476
	ldrsb	r1, [r0, #1]
	cmp	r1, #3
	cmpne	r1, #0
	beq	.L476
	ldr	r1, [r8]
	ldrd	r2, [fp, #-52]
	add	r1, r1, #608
	ldrd	r0, [r1, #-8]
	cmp	r1, r3
	cmpeq	r0, r2
	strccd	r0, [fp, #-52]
	strcc	r10, [fp, #-56]
.L476:
	ldr	r1, [r5, #2140]
	add	r10, r10, #1
	cmp	r10, r1
	bcc	.L477
	ldr	r3, [fp, #-56]
	cmn	r3, #1
	beq	.L474
	ldr	r3, [fp, #-68]
	ldrd	r0, [fp, #-52]
	ldrd	r2, [r3, #-8]
	cmp	r3, r1
	cmpeq	r2, r0
	bhi	.L515
.L474:
	ldrb	r3, [r5, #1808]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L478
	ldr	r3, [r5, #1824]
	cmp	r3, #3
	moveq	r3, #1
	streq	r3, [r4, #292]
	beq	.L478
	cmp	r3, #4
	moveq	r3, #2
	streq	r3, [r4, #292]
	beq	.L478
	cmp	r3, #5
	moveq	r3, #3
	streq	r3, [r4, #292]
	beq	.L478
	mov	r0, #0
	ldr	r1, .L519
	str	r0, [r4, #292]
	ldr	r2, [r5, #1824]
	bl	dprint_vfmw
.L478:
	ldr	r0, [r6, #2344]
	ldr	r1, [r4, #648]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L450
	ldr	r3, .L519+4
	mov	r2, #632
	add	r1, r4, #16
	ldr	r3, [r3, #52]
	blx	r3
	mov	r3, #0
	str	r3, [r5, #296]
	mov	r2, #1
	ldrb	r3, [r4, #696]	@ zero_extendqisi2
	strb	r2, [r5, #291]
	cmp	r3, #0
	movne	r3, #4
	strb	r3, [r5, #284]
	ldr	r3, [r4, #720]
	strb	r2, [r5, #289]
	str	r3, [r5, #300]
	str	r3, [r5, #308]
	str	r3, [r5, #304]
	ldr	r3, [r4, #728]
	str	r3, [r5, #236]
.L450:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L454:
	ldrb	r2, [r4, #81]	@ zero_extendqisi2
	mov	ip, #3
	ldr	r8, [r4, #680]
	add	r5, r7, #24576
	ldr	lr, [r4, #756]
	and	r2, r2, #240
	ldr	r0, [r4, #772]
	orr	r2, r2, #7
	ldrb	r1, [r4, #80]	@ zero_extendqisi2
	ldr	r9, [r4, #676]
	strb	r2, [r4, #81]
	bfi	r1, r9, #0, #2
	str	r8, [r4, #168]
	strb	r1, [r4, #80]
	str	lr, [r4, #72]
	str	ip, [r4, #76]
	ldr	r2, [r0, #692]
	str	r2, [r4, #728]
	b	.L451
.L452:
	ldrb	r2, [r4, #696]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L456
	ldr	r1, [r4, #672]
	ldr	r2, [r4, #680]
	cmp	r1, #0
	ldr	r0, [r4, #676]
	ldreq	r8, [r4, #756]
	movne	ip, #3
	ldreq	lr, [r4, #796]
	moveq	ip, #2
	ldrne	r8, [r4, #756]
	moveq	r1, #3
	ldrne	lr, [r4, #796]
	movne	r1, ip
	str	r2, [r4, #168]
.L458:
	ldr	r5, [r4, #748]
	ldr	r2, [r4, #788]
	cmp	r5, r2
	beq	.L516
	movle	r10, #1
	movgt	r10, #0
.L469:
	add	r5, r7, #24576
	ldrb	r2, [r5, #1844]	@ zero_extendqisi2
	cmp	r2, #3
	moveq	r10, #1
	beq	.L470
	cmp	r2, #4
	moveq	r10, #0
.L470:
	ldrb	r2, [r4, #81]	@ zero_extendqisi2
	ldrb	r9, [r4, #80]	@ zero_extendqisi2
	bfi	r2, r10, #4, #2
	str	r8, [r4, #72]
	bfi	r2, r1, #2, #2
	bfi	r9, r0, #0, #2
	bfi	r2, ip, #0, #2
	str	lr, [r4, #76]
	strb	r9, [r4, #80]
	strb	r2, [r4, #81]
	b	.L451
.L515:
	ldrd	r8, [fp, #-52]
	ldr	r0, [r6, #2344]
	strd	r8, [sp]
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L474
	ldr	r8, [fp, #-68]
	mov	r0, #29
	ldr	r1, .L519+8
	ldrd	r2, [r8, #-8]
	strd	r2, [fp, #-68]
	ldrd	r2, [fp, #-52]
	strd	r2, [sp]
	ldrd	r2, [fp, #-68]
	bl	dprint_vfmw
	ldr	r3, [fp, #-56]
	add	r1, r3, #6592
	ldrd	r2, [r8, #-8]
	add	r1, r1, #38
	ldr	r1, [r7, r1, asl #2]
	add	r1, r1, #608
	strd	r2, [r1, #-8]
	ldrd	r2, [fp, #-52]
	strd	r2, [r8, #-8]
	b	.L474
.L456:
	ldr	ip, [r4, #752]
	ldr	r2, [r6, #2340]
	cmp	ip, r2
	bhi	.L517
	ldr	r1, [r4, #792]
	cmp	r2, r1
	bcc	.L462
.L460:
	ldr	r2, [r4, #680]
	mov	r1, #3
	ldr	r0, [r4, #676]
	ldr	r9, [r4, #756]
	ldr	r5, [r4, #796]
	str	r2, [r4, #168]
.L463:
	ldrb	r2, [r4, #3]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L518
	cmp	r2, #2
	streq	ip, [r4, #168]
	moveq	r0, r9
	moveq	r1, #1
.L465:
	ldr	r2, [r4, #768]
	mov	r8, r9
	ldr	r10, [r4, #808]
	mov	lr, r5
	mov	ip, #3
	str	r9, [r4, #72]
	add	r2, r2, r10
	str	r5, [r4, #76]
	add	r2, r2, r2, lsr #31
	mov	r2, r2, asr #1
	str	r2, [r4, #252]
	b	.L458
.L462:
	ldr	r0, [r4, #756]
	mov	r1, #1
	ldr	r5, [r4, #796]
	str	ip, [r4, #168]
	mov	r9, r0
	b	.L463
.L516:
	ldr	r2, [r4, #84]
	cmp	r2, #720
	movne	r10, #1
	bne	.L469
	ldr	r10, [r4, #88]
	subs	r10, r10, #480
	movne	r10, #1
	b	.L469
.L517:
	ldr	lr, [r4, #792]
	cmp	r2, lr
	bcc	.L460
	ldr	r0, [r4, #796]
	mov	r1, #2
	str	lr, [r4, #168]
	ldr	r9, [r4, #756]
	mov	r5, r0
	b	.L463
.L518:
	ldr	r2, [r4, #792]
	mov	r0, r5
	mov	r1, #2
	str	r2, [r4, #168]
	b	.L465
.L496:
	add	r5, r7, #24576
	b	.L451
.L520:
	.align	2
.L519:
	.word	.LC20
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC19
	UNWIND(.fnend)
	.size	GetImagePara, .-GetImagePara
	.align	2
	.global	SetFrmRepeatCount
	.type	SetFrmRepeatCount, %function
SetFrmRepeatCount:
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
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r1, #16]
	ldmccfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SetFrmRepeatCount.part.3
	UNWIND(.fnend)
	.size	SetFrmRepeatCount, .-SetFrmRepeatCount
	.align	2
	.global	SplitFrmToFlds
	.type	SplitFrmToFlds, %function
SplitFrmToFlds:
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
	ldrb	lr, [r0, #697]	@ zero_extendqisi2
	mov	r5, #1
	ldrb	ip, [r0, #698]	@ zero_extendqisi2
	mov	r4, #2
	ldr	r1, [r0, #712]
	ldr	r2, [r0, #716]
	ldr	r3, [r0, #732]
	strb	r5, [r0, #736]
	strb	r4, [r0, #776]
	strb	lr, [r0, #737]
	strb	lr, [r0, #777]
	strb	ip, [r0, #738]
	strb	ip, [r0, #778]
	str	r1, [r0, #752]
	str	r1, [r0, #792]
	str	r2, [r0, #756]
	str	r2, [r0, #796]
	str	r3, [r0, #772]
	str	r3, [r0, #812]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	SplitFrmToFlds, .-SplitFrmToFlds
	.align	2
	.global	CombineFldsToFrm
	.type	CombineFldsToFrm, %function
CombineFldsToFrm:
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
	ldr	r2, [r0, #788]
	mov	lr, #3
	ldr	r1, [r0, #748]
	ldr	r3, [r0, #792]
	cmp	r2, r1
	ldr	r5, [r0, #752]
	ldrb	r4, [r0, #777]	@ zero_extendqisi2
	ldr	ip, [r0, #772]
	movge	r2, r1
	add	r3, r3, r5
	cmp	r4, #0
	strb	lr, [r0, #696]
	mov	r3, r3, lsr #1
	str	ip, [r0, #732]
	str	r2, [r0, #708]
	str	r2, [r0, #664]
	str	r3, [r0, #712]
	beq	.L525
	ldrb	r2, [r0, #737]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L526
.L525:
	ldr	r2, [r0, #776]
	mov	r1, #0
	strb	r1, [r0, #697]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, r1
	beq	.L532
	ldr	r2, [r0, #736]
	bic	r2, r2, #-16777216
	bic	r2, r2, #255
	cmp	r2, #0
	movne	r1, #1
	beq	.L532
.L528:
	ldr	r2, [r0, #756]
	strb	r1, [r0, #698]
	cmp	r2, #0
	beq	.L530
	ldr	r1, [r0, #796]
	cmp	r1, #0
	moveq	r2, r1
	beq	.L530
	cmp	r2, r1
	movcc	r2, r1
.L530:
	str	r2, [r0, #716]
	str	r2, [r0, #676]
	str	r3, [r0, #680]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L526:
	mov	r1, #1
	strb	r1, [r0, #697]
.L532:
	mov	r1, #0
	b	.L528
	UNWIND(.fnend)
	.size	CombineFldsToFrm, .-CombineFldsToFrm
	.align	2
	.global	GetAPC
	.type	GetAPC, %function
GetAPC:
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
	subs	r7, r1, #0
	mov	r5, r0
	beq	.L566
	cmp	r2, #1
	beq	.L547
	cmp	r2, #2
	beq	.L548
	ldr	r8, [r7, #748]
	ldr	r9, [r7, #788]
.L549:
	add	r6, r5, #24576
	ldr	ip, [r6, #2412]
	cmp	ip, #0
	beq	.L558
	ldr	r4, [r6, #2156]
	cmp	r4, #0
	addne	r3, r5, #26624
	movne	r4, #0
	addne	r3, r3, #108
	bne	.L552
	b	.L550
.L556:
	ldr	r2, [r3, #4]!
	cmp	r2, #0
	beq	.L550
.L552:
	add	r4, r4, #1
	cmp	r4, ip
	bne	.L556
.L558:
	mvn	r0, #0
.L562:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L548:
	ldr	r8, [r7, #788]
	mov	r9, r8
	b	.L549
.L550:
	add	r3, r5, #61440
	ldr	r1, [r7, #648]
	ldr	r0, [r3, #2344]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L553
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L553
	add	r5, r5, r4, lsl #2
	mov	r3, #1
	add	r5, r5, #24576
	ldr	r1, .L567
	str	r3, [r5, #2156]
	ldr	r3, [r0, #28]
	mov	r0, #13
	ldr	r3, [r3, #4]
	str	r8, [r5, #2284]
	str	r9, [r5, #2348]
	str	r3, [r5, #2220]
	ldr	r3, [r6, #2416]
	cmp	r3, #15
	addls	r3, r3, #1
	movhi	r3, #16
	str	r3, [r6, #2416]
	mov	r3, r4
	ldr	r2, [r7, #164]
	bl	dprint_vfmw
	mov	r0, #0
	str	r4, [r7, #688]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L547:
	ldr	r8, [r7, #748]
	mov	r9, r8
	b	.L549
.L553:
	mov	r1, #0
	ldr	r2, [r7, #648]
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	stmia	sp, {r0, r1}
	mov	r0, r1
	ldr	r1, .L567+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L562
.L566:
	mov	r0, r7
	movw	r3, #2206
	ldr	r2, .L567+8
	ldr	r1, .L567+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L562
.L568:
	.align	2
.L567:
	.word	.LC23
	.word	.LC24
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	GetAPC, .-GetAPC
	.align	2
	.global	SlidingWinMark
	.type	SlidingWinMark, %function
SlidingWinMark:
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
	add	r2, r0, #24576
	add	r3, r0, #16384
	ldr	r1, [r2, #2148]
	ldr	r3, [r3, #456]
	ldr	r2, [r2, #2144]
	rsb	r3, r1, r3
	cmp	r2, r3
	ldmnefd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	SlidingWinMark.part.4
	UNWIND(.fnend)
	.size	SlidingWinMark, .-SlidingWinMark
	.align	2
	.global	DumpDPB
	.type	DumpDPB, %function
DumpDPB:
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
	ldr	r3, .L581
	mov	r5, r0
	ldr	r3, [r3]
	tst	r3, #16384
	beq	.L571
	add	r6, r0, #24576
	ldr	r3, [r6, #2140]
	cmp	r3, #0
	addne	r7, r0, #26368
	movne	r4, #0
	addne	r7, r7, #148
	beq	.L577
.L576:
	ldr	ip, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L581+4
	mov	r0, #14
	add	r4, r4, #1
	ldrb	lr, [ip, #2]	@ zero_extendqisi2
	ldr	r3, [ip, #652]
	str	lr, [sp, #4]
	ldr	ip, [ip, #664]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r6, #2140]
	cmp	r3, r4
	bhi	.L576
.L577:
	ldr	r1, .L581+8
	mov	r0, #14
	bl	dprint_vfmw
	ldr	r3, [r6, #2144]
	cmp	r3, #0
	addne	r5, r5, #26368
	movne	r4, #0
	addne	r5, r5, #212
	beq	.L575
.L578:
	ldr	ip, [r5, #4]!
	mov	r2, r4
	ldr	r1, .L581+12
	mov	r0, #14
	ldrb	lr, [ip, #2]	@ zero_extendqisi2
	ldr	r3, [ip, #652]
	str	lr, [sp, #4]
	ldr	ip, [ip, #664]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5]
	mov	r2, r4
	ldr	r1, .L581+16
	mov	r0, #14
	add	r4, r4, #1
	ldr	r3, [r3, #708]
	bl	dprint_vfmw
	ldr	r3, [r6, #2144]
	cmp	r3, r4
	bhi	.L578
.L575:
	ldr	r1, .L581+8
	mov	r0, #14
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L571:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L582:
	.align	2
.L581:
	.word	g_PrintEnable
	.word	.LC25
	.word	.LC2
	.word	.LC26
	.word	.LC27
	UNWIND(.fnend)
	.size	DumpDPB, .-DumpDPB
	.align	2
	.global	UpdateCurrFrameInfo
	.type	UpdateCurrFrameInfo, %function
UpdateCurrFrameInfo:
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
	add	r3, r0, #57344
	ldrb	r2, [r3, #3010]	@ zero_extendqisi2
	ldr	r4, [r3, #3656]
	strb	r2, [r4]
	ldrb	r2, [r3, #3012]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
	bne	.L584
	ldrb	r2, [r3, #3013]	@ zero_extendqisi2
	cmp	r2, #0
	movne	r2, #3
.L584:
	strb	r2, [r4, #2]
	ldr	r2, [r3, #3664]
	str	r2, [r4, #652]
	ldr	r2, [r3, #3700]
	str	r2, [r4, #680]
	ldr	r2, [r3, #3692]
	str	r2, [r4, #676]
	ldr	r2, [r3, #3676]
	str	r2, [r4, #664]
	ldr	r2, [r3, #3724]
	str	r2, [r4, #684]
	ldr	r2, [r3, #3668]
	str	r2, [r4, #660]
	ldrb	r2, [r3, #3017]	@ zero_extendqisi2
	str	r2, [r4, #672]
	ldrb	r2, [r3, #3015]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r1, #3
	movne	r1, #0
	strb	r1, [r4, #3]
	ldrb	r2, [r3, #3011]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L587
	bcc	.L588
	cmp	r2, #2
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	str	r4, [r4, #812]
	mov	r0, #1
	strb	r0, [r4, #776]
	mov	r0, #0
	ldrb	ip, [r3, #3012]	@ zero_extendqisi2
	strb	ip, [r4, #777]
	ldrb	ip, [r3, #3013]	@ zero_extendqisi2
	strb	ip, [r4, #778]
	ldr	ip, [r3, #3684]
	str	ip, [r4, #788]
	ldr	lr, [r3, #3692]
	str	lr, [r4, #796]
	ldr	ip, [r3, #3700]
	str	r0, [r4, #672]
	str	ip, [r4, #792]
	ldrb	r5, [r3, #3009]	@ zero_extendqisi2
	cmp	r5, r0
	beq	.L605
	ldr	r2, [r4, #752]
	mov	r5, #3
	strb	r5, [r4, #1]
	mvn	r7, #0
	add	ip, ip, r2
	str	ip, [r4, #680]
	str	ip, [r4, #712]
	mvn	r6, #0
	ldrb	r2, [r3, #3015]	@ zero_extendqisi2
	cmp	r2, #1
	add	r2, r3, #3616
	orreq	r0, r1, #2
	strb	r0, [r4, #3]
	ldrd	r8, [r2, #-8]
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L596
	add	r2, r4, #608
	ldrd	r0, [r2, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	beq	.L606
.L596:
	ldr	r2, [r4, #756]
.L603:
	cmp	r2, lr
	mov	r0, r4
	movcc	r2, lr
	str	r2, [r4, #676]
	ldr	r3, [r3, #3676]
	str	r3, [r4, #664]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	CombineFldsToFrm
.L588:
	str	r4, [r4, #732]
	mov	r1, #3
	mov	r2, #0
	strb	r1, [r4, #1]
	strb	r2, [r4, #696]
	add	r1, r3, #3024
	ldrb	r5, [r3, #3012]	@ zero_extendqisi2
	mov	r2, #632
	add	r0, r4, #16
	strb	r5, [r4, #697]
	ldrb	r6, [r3, #3013]	@ zero_extendqisi2
	strb	r6, [r4, #698]
	ldr	ip, [r3, #3680]
	str	ip, [r4, #708]
	ldr	r7, [r3, #3692]
	str	r7, [r4, #716]
	ldr	r8, [r3, #3700]
	str	r8, [r4, #712]
	ldr	ip, [r3, #3684]
	str	ip, [r4, #748]
	ldr	r3, [r3, #3688]
	str	r3, [r4, #788]
	bl	memcpy
	mov	r2, #1
	mov	r3, #2
	str	r8, [r4, #752]
	str	r8, [r4, #792]
	str	r7, [r4, #756]
	str	r7, [r4, #796]
	strb	r6, [r4, #738]
	strb	r6, [r4, #778]
	strb	r5, [r4, #737]
	strb	r5, [r4, #777]
	str	r4, [r4, #772]
	str	r4, [r4, #812]
	strb	r2, [r4, #736]
	strb	r3, [r4, #776]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L587:
	strb	r2, [r4, #736]
	mov	r0, #0
	str	r4, [r4, #772]
	ldrb	ip, [r3, #3012]	@ zero_extendqisi2
	strb	ip, [r4, #737]
	ldrb	ip, [r3, #3013]	@ zero_extendqisi2
	strb	ip, [r4, #738]
	ldr	ip, [r3, #3684]
	str	ip, [r4, #748]
	ldr	lr, [r3, #3692]
	str	lr, [r4, #756]
	ldr	ip, [r3, #3700]
	str	r0, [r4, #672]
	str	ip, [r4, #752]
	ldrb	r5, [r3, #3009]	@ zero_extendqisi2
	cmp	r5, r0
	beq	.L607
	ldr	r2, [r4, #792]
	mov	r5, #3
	strb	r5, [r4, #1]
	mvn	r7, #0
	add	ip, ip, r2
	str	ip, [r4, #680]
	str	ip, [r4, #712]
	mvn	r6, #0
	ldrb	r2, [r3, #3015]	@ zero_extendqisi2
	cmp	r2, #1
	add	r2, r3, #3616
	orreq	r0, r1, #1
	strb	r0, [r4, #3]
	ldrd	r8, [r2, #-8]
	cmp	r9, r7
	cmpeq	r8, r6
	beq	.L592
	add	r2, r4, #608
	ldrd	r0, [r2, #-8]
	cmp	r1, r7
	cmpeq	r0, r6
	streqd	r8, [r2, #-8]
.L592:
	ldr	r2, [r4, #796]
	b	.L603
.L605:
	strb	r2, [r4, #1]
	add	r1, r3, #3024
	str	ip, [r4, #680]
	add	r0, r4, #16
	str	ip, [r4, #712]
	mov	r2, #632
	ldrb	r3, [r3, #3015]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r5, #2
	strb	r5, [r4, #3]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L607:
	strb	r2, [r4, #1]
	add	r1, r3, #3024
	str	ip, [r4, #680]
	add	r0, r4, #16
	str	ip, [r4, #712]
	mov	r2, #632
	ldrb	r3, [r3, #3015]	@ zero_extendqisi2
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #3]
	bl	memcpy
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L606:
	strd	r8, [r2, #-8]
	b	.L596
	UNWIND(.fnend)
	.size	UpdateCurrFrameInfo, .-UpdateCurrFrameInfo
	.align	2
	.global	SimpleSlideDPB
	.type	SimpleSlideDPB, %function
SimpleSlideDPB:
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
	add	r3, r0, #24576
	mov	r4, r0
	ldr	r1, [r3, #2140]
	ldr	r2, [r3, #2136]
	cmp	r1, r2
	bcs	.L614
.L609:
	add	r0, r4, #57344
	mov	r2, #0
	ldr	r3, [r0, #3672]
	strb	r2, [r0, #3012]
	cmp	r3, r2
	movne	r3, #1
	strneb	r3, [r0, #3013]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L614:
	ldr	r1, [r3, #1944]
	bl	UnMarkFrameStoreRef
	mov	r1, #0
	mov	r0, r4
	bl	RemoveFrameStoreOutDPB
	b	.L609
	UNWIND(.fnend)
	.size	SimpleSlideDPB, .-SimpleSlideDPB
	.align	2
	.global	ReleaseNAL
	.type	ReleaseNAL, %function
ReleaseNAL:
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
	subs	r5, r1, #0
	mov	r6, r0
	beq	.L623
	add	r7, r5, #56
	mov	r4, r5
	mov	r3, #0
	strb	r3, [r5, #1]
	strb	r3, [r5, #4]
.L618:
	ldr	r3, [r4, #8]
	mov	r0, r6
	cmp	r3, #0
	beq	.L617
	ldr	r1, [r4, #32]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #8]
	mov	r0, #7
	ldr	r1, .L624
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r4, #8]
	str	r3, [r4, #24]
	str	r3, [r4, #12]
.L617:
	add	r4, r4, #28
	cmp	r4, r7
	bne	.L618
	mov	r3, #0
	strb	r3, [r5]
	str	r3, [r5, #68]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L623:
	mov	r0, r5
	movw	r3, #3961
	ldr	r2, .L624+4
	ldr	r1, .L624+8
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	dprint_vfmw
.L625:
	.align	2
.L624:
	.word	.LC28
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	ReleaseNAL, .-ReleaseNAL
	.align	2
	.global	ClearCurrNal
	.type	ClearCurrNal, %function
ClearCurrNal:
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
	ldr	r1, [r0, #368]
	mov	r4, r0
	cmp	r1, #0
	beq	.L627
	add	r3, r0, #61440
	ldr	r0, [r3, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #368]
.L627:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	ClearCurrNal, .-ClearCurrNal
	.align	2
	.global	ClearCurrSlice
	.type	ClearCurrSlice, %function
ClearCurrSlice:
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
	ldr	r1, .L636
	mov	r5, r0
	mov	r0, #1
	add	r4, r5, #61440
	bl	dprint_vfmw
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L632
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L632:
	ldr	r3, [r4, #2300]
	mov	r0, #0
	add	r3, r3, #1
	str	r3, [r4, #2300]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L637:
	.align	2
.L636:
	.word	.LC29
	UNWIND(.fnend)
	.size	ClearCurrSlice, .-ClearCurrSlice
	.align	2
	.global	ClearAllNal
	.type	ClearAllNal, %function
ClearAllNal:
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
	add	r5, r0, #13504
	add	r4, r0, #376
	add	r5, r5, #24
	add	r6, r0, #61440
	b	.L640
.L639:
	add	r4, r4, #96
	cmp	r4, r5
	beq	.L642
.L640:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L639
	mov	r1, r4
	ldr	r0, [r6, #2344]
	add	r4, r4, #96
	bl	ReleaseNAL
	cmp	r4, r5
	bne	.L640
.L642:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ClearAllNal, .-ClearAllNal
	.align	2
	.global	ClearAllSlice
	.type	ClearAllSlice, %function
ClearAllSlice:
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
	add	r4, r0, #61696
	add	r5, r0, #62208
	add	r4, r4, #156
	add	r5, r5, #188
	add	r6, r0, #61440
	mov	r7, #0
.L645:
	ldr	r1, [r4, #4]!
	cmp	r1, #0
	beq	.L644
	ldr	r0, [r6, #2344]
	bl	ReleaseNAL
	str	r7, [r4]
.L644:
	cmp	r4, r5
	bne	.L645
	mov	r0, #0
	str	r0, [r6, #2268]
	str	r0, [r6, #2328]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ClearAllSlice, .-ClearAllSlice
	.align	2
	.global	H264_ClearCurrPic
	.type	H264_ClearCurrPic, %function
H264_ClearCurrPic:
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
	bl	ClearAllSlice
	add	r0, r4, #12288
	add	r3, r4, #20480
	mov	r2, #0
	movw	r1, #23352
	ldr	r0, [r0, #1292]
	movt	r1, 1
	mov	ip, #2
	str	r1, [r3, #1864]
	strb	ip, [r3, #1849]
	mov	r1, #7
	str	r0, [r3, #1856]
	mov	r0, #32
	str	r1, [r3, #1860]
	mov	r1, #3
	strb	r0, [r3, #1850]
	mvn	r0, #0
	str	r1, [r3, #1872]
	mov	r1, #262144
	str	r0, [r3, #1876]
	mov	r0, r2
	str	r1, [r3, #1888]
	strb	r2, [r3, #1848]
	str	r2, [r3, #1880]
	str	r2, [r3, #1884]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	H264_ClearCurrPic, .-H264_ClearCurrPic
	.align	2
	.global	H264_ArrangeVahbMem
	.type	H264_ArrangeVahbMem, %function
H264_ArrangeVahbMem:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 24
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
	mov	r4, r1
	sub	r3, r2, #32
	sub	r1, r1, #32
	movw	ip, #8160
	cmp	r3, ip
	cmpls	r1, ip
	mov	r5, r2
	mov	r6, r0
	movhi	r1, #1
	movls	r1, #0
	bhi	.L663
	ldr	r3, .L667
	mov	r2, #20
	sub	r0, fp, #48
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r6]
	str	r4, [fp, #-44]
	str	r5, [fp, #-40]
	ldr	r3, [r3, #28]
	str	r4, [fp, #-36]
	cmp	r3, #24
	str	r5, [fp, #-32]
	beq	.L654
	add	r2, r6, #24576
	ldrb	r3, [fp, #4]	@ zero_extendqisi2
	mov	r1, #5
	strb	r1, [fp, #-46]
	ldr	r2, [r2, #2136]
	add	r2, r2, #1
	strb	r2, [fp, #-47]
.L660:
	cmp	r5, #63
	cmphi	r4, #63
	strb	r3, [fp, #-45]
	movls	r7, #1
	movhi	r7, #0
	bls	.L664
	add	r4, r6, #61440
	sub	r1, fp, #48
	ldr	r0, [r4, #2344]
	bl	FSP_ConfigInstance
	subs	r5, r0, #0
	bne	.L656
	ldr	r1, [r6]
	sub	r3, fp, #52
	ldr	r0, [r4, #2344]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L665
	cmp	r0, #0
	moveq	r0, #1
	bne	.L666
.L661:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L654:
	mov	r3, #1
	mov	r2, #5
	strb	r3, [fp, #-47]
	strb	r2, [fp, #-46]
	b	.L660
.L663:
	mov	r3, r2
	ldr	r1, .L667+4
	mov	r2, r4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L664:
	mov	r3, r5
	mov	r2, r4
	ldr	r1, .L667+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	b	.L661
.L656:
	mov	r0, r7
	ldr	r1, .L667+12
	bl	dprint_vfmw
.L662:
	mvn	r0, #19
	b	.L661
.L666:
	mov	r0, r5
	ldr	r1, .L667+16
	bl	dprint_vfmw
	b	.L662
.L665:
	add	r0, r6, #8
	bl	ResetVoQueue
	b	.L662
.L668:
	.align	2
.L667:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC30
	.word	.LC31
	.word	.LC33
	.word	.LC32
	UNWIND(.fnend)
	.size	H264_ArrangeVahbMem, .-H264_ArrangeVahbMem
	.align	2
	.global	RepairList
	.type	RepairList, %function
RepairList:
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
	add	r3, r0, #20480
	mov	r4, r0
	ldrb	r2, [r3, #208]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L671
	bcc	.L686
	cmp	r2, #2
	bne	.L695
.L687:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L695:
	ldr	r1, .L699
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L686:
	mov	r6, #1
.L672:
	add	r0, r4, #20480
	add	lr, r4, #26880
	add	r0, r0, #244
	mov	r5, #0
	add	lr, lr, #244
	add	r7, r4, #57344
	ldr	r3, [r0, #4]!
	mov	r2, r5
	mov	r8, #1
	cmp	r3, #0
	beq	.L674
.L697:
	ldr	r10, [lr]
	cmp	r10, #0
	bne	.L688
	mov	ip, lr
	mov	r1, r10
	b	.L676
.L677:
	ldr	r9, [ip, #4]!
	cmp	r9, #0
	bne	.L675
.L676:
	add	r1, r1, #1
	cmp	r1, r3
	bne	.L677
	ldr	r1, [r4]
	ldr	r1, [r1, #24]
	cmp	r1, #2
	bne	.L696
	ldr	r5, [r7, #3656]
	add	r5, r5, #696
.L679:
	mov	r9, r10
	mov	ip, lr
	mov	r1, #0
	b	.L685
.L681:
	ldr	r9, [ip, #4]!
.L685:
	add	r1, r1, #1
	cmp	r9, #0
	streq	r5, [ip]
	cmp	r1, r3
	bne	.L681
	add	r2, r2, #1
	add	lr, lr, #132
	cmp	r6, r2
	bls	.L687
.L694:
	ldr	r3, [r0, #4]!
	cmp	r3, #0
	bne	.L697
.L674:
	ldr	r1, [r4]
	ldr	r1, [r1, #24]
	cmp	r1, #2
	bne	.L698
	add	r2, r2, #1
	str	r8, [r0]
	cmp	r6, r2
	ldr	r3, [r7, #3656]
	add	lr, lr, #132
	add	r3, r3, #696
	str	r3, [lr, #-132]
	bhi	.L694
	b	.L687
.L688:
	mov	r9, r10
.L675:
	mov	r5, r9
	b	.L679
.L671:
	mov	r6, #2
	b	.L672
.L698:
	ldr	r1, .L699+4
.L692:
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L696:
	mov	r2, r5
	mov	r3, #0
	ldr	r1, .L699+8
	b	.L692
.L700:
	.align	2
.L699:
	.word	.LC34
	.word	.LC36
	.word	.LC35
	UNWIND(.fnend)
	.size	RepairList, .-RepairList
	.align	2
	.global	GetShortTermPicPoint
	.type	GetShortTermPicPoint, %function
GetShortTermPicPoint:
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
	add	r3, r0, #20480
	ldrb	r4, [r3, #209]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L702
	ldrb	r3, [r3, #210]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r4, #2
	moveq	r4, #1
.L702:
	add	r3, r0, #24576
	ldr	r5, [r3, #2144]
	cmp	r5, #0
	beq	.L710
	add	r3, r0, #26368
	mov	r2, #0
	add	r3, r3, #216
	b	.L707
.L720:
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L718
.L705:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L719
.L707:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L720
	ldrb	lr, [r0, #2]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L706
	ldr	ip, [r0, #736]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	beq	.L721
.L706:
	tst	lr, #2
	beq	.L705
	ldr	ip, [r0, #776]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L705
	ldr	ip, [r0, #784]
	cmp	ip, r1
	bne	.L705
	add	r0, r0, #776
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L718:
	ldr	ip, [r0, #696]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	bne	.L705
	ldr	ip, [r0, #704]
	cmp	ip, r1
	bne	.L705
	add	r0, r0, #696
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L721:
	ldr	ip, [r0, #744]
	cmp	ip, r1
	bne	.L706
	add	r0, r0, #736
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L719:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L710:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetShortTermPicPoint, .-GetShortTermPicPoint
	.align	2
	.global	GetLongTermPicPoint
	.type	GetLongTermPicPoint, %function
GetLongTermPicPoint:
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
	add	r3, r0, #20480
	ldrb	r4, [r3, #209]	@ zero_extendqisi2
	cmp	r4, #0
	beq	.L723
	ldrb	r3, [r3, #210]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r4, #2
	moveq	r4, #1
.L723:
	add	r3, r0, #24576
	ldr	r5, [r3, #2148]
	cmp	r5, #0
	beq	.L731
	add	r3, r0, #26624
	mov	r2, #0
	add	r3, r3, #24
	b	.L728
.L741:
	ldrb	ip, [r0, #2]	@ zero_extendqisi2
	cmp	ip, #3
	beq	.L739
.L726:
	add	r2, r2, #1
	add	r3, r3, #4
	cmp	r2, r5
	beq	.L740
.L728:
	cmp	r4, #0
	ldr	r0, [r3]
	beq	.L741
	ldrb	lr, [r0, #2]	@ zero_extendqisi2
	tst	lr, #1
	beq	.L727
	ldr	ip, [r0, #736]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	beq	.L742
.L727:
	tst	lr, #2
	beq	.L726
	ldr	ip, [r0, #776]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L726
	ldr	ip, [r0, #780]
	cmp	ip, r1
	bne	.L726
	add	r0, r0, #776
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L739:
	ldr	ip, [r0, #696]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L726
	ldr	ip, [r0, #700]
	cmp	ip, r1
	bne	.L726
	add	r0, r0, #696
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L742:
	ldr	ip, [r0, #740]
	cmp	ip, r1
	bne	.L727
	add	r0, r0, #736
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L740:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L731:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetLongTermPicPoint, .-GetLongTermPicPoint
	.align	2
	.global	ReorderSTList
	.type	ReorderSTList, %function
ReorderSTList:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r7, [fp, #4]
	mov	r5, r1
	mov	r1, r3
	mov	r8, r2
	mov	r6, r3
	bl	GetShortTermPicPoint
	ldr	r4, [r7]
	add	r2, r8, #1
	cmp	r2, r4
	ble	.L744
	add	lr, r5, r2, lsl #2
	mov	ip, r2
.L745:
	ldr	r3, [lr, #-4]!
	sub	ip, ip, #1
	str	r3, [lr, #4]
	ldr	r4, [r7]
	cmp	r4, ip
	blt	.L745
.L744:
	add	r3, r4, #1
	str	r3, [r7]
	str	r0, [r5, r4, asl #2]
	ldr	ip, [r7]
	cmp	r2, ip
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r2, r8, #2
	add	r4, r5, ip, lsl #2
	mov	lr, ip
.L749:
	ldr	r0, [r4], #4
	add	ip, ip, #1
	cmp	r0, #0
	beq	.L747
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L748
	ldr	r3, [r0, #8]
	cmp	r3, r6
	beq	.L747
.L748:
	str	r0, [r5, lr, asl #2]
	add	lr, lr, #1
.L747:
	cmp	ip, r2
	bne	.L749
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	ReorderSTList, .-ReorderSTList
	.align	2
	.global	ReorderLTList
	.type	ReorderLTList, %function
ReorderLTList:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	ldr	r7, [fp, #4]
	mov	r5, r1
	mov	r1, r3
	mov	r8, r2
	mov	r6, r3
	bl	GetLongTermPicPoint
	ldr	r4, [r7]
	add	r2, r8, #1
	cmp	r2, r4
	ble	.L757
	add	lr, r5, r2, lsl #2
	mov	ip, r2
.L758:
	ldr	r3, [lr, #-4]!
	sub	ip, ip, #1
	str	r3, [lr, #4]
	ldr	r4, [r7]
	cmp	r4, ip
	blt	.L758
.L757:
	add	r3, r4, #1
	str	r3, [r7]
	str	r0, [r5, r4, asl #2]
	ldr	ip, [r7]
	cmp	r2, ip
	ldmltfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r2, r8, #2
	add	r4, r5, ip, lsl #2
	mov	lr, ip
.L762:
	ldr	r0, [r4], #4
	add	ip, ip, #1
	cmp	r0, #0
	beq	.L760
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L761
	ldr	r3, [r0, #4]
	cmp	r3, r6
	beq	.L760
.L761:
	str	r0, [r5, lr, asl #2]
	add	lr, lr, #1
.L760:
	cmp	ip, r2
	bne	.L762
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	ReorderLTList, .-ReorderLTList
	.align	2
	.global	ReorderRefPiclist
	.type	ReorderRefPiclist, %function
ReorderRefPiclist:
	UNWIND(.fnstart)
	@ args = 12, pretend = 0, frame = 24
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
	add	r2, r0, #20480
	str	r1, [fp, #-56]
	mov	r8, r3
	ldrb	r1, [r2, #209]	@ zero_extendqisi2
	mov	r3, #0
	mov	r7, r0
	str	r3, [fp, #-48]
	cmp	r1, r3
	ldr	ip, [fp, #4]
	add	r3, r0, #12288
	beq	.L773
	ldr	lr, [r2, #216]
	mov	r4, #2208
	ldr	r5, [r3, #1304]
	mov	r0, #4000
	ldr	r6, [r2, #224]
	mov	r1, #2
	ldr	r3, [r3, #1300]
	mla	r2, r4, lr, r5
	mov	lr, r6, asl #1
	add	lr, lr, #1
	str	lr, [fp, #-64]
	ldr	r2, [r2, #28]
	mla	r3, r0, r2, r3
	ldr	r3, [r3, #2196]
	add	r3, r3, #4
	mov	r3, r1, asl r3
	str	r3, [fp, #-60]
.L783:
	adds	r9, r8, #2
	beq	.L772
	ldr	r3, [ip]
	cmp	r3, #3
	beq	.L772
	mov	r2, r8
	ldr	r6, [fp, #8]
	ldr	r5, [fp, #-64]
	mov	r4, #0
	mov	r8, ip
	mov	r10, r2
	b	.L776
.L777:
	ldr	r3, [fp, #12]
	sub	r1, fp, #48
	mov	r2, r10
	mov	r0, r7
	ldr	r3, [r3, r4, asl #2]
	add	r4, r4, #1
	str	r1, [sp]
	ldr	r1, [fp, #-56]
	bl	ReorderLTList
	cmp	r4, r9
	beq	.L772
.L782:
	ldr	r3, [r8, #4]!
	add	r6, r6, #4
	cmp	r3, #3
	beq	.L772
.L776:
	cmp	r3, #1
	bhi	.L777
	cmp	r3, #0
	ldr	r3, [r6]
	bne	.L778
	mvn	r3, r3
	adds	r5, r5, r3
	ldrmi	r3, [fp, #-60]
	addmi	r5, r5, r3
.L779:
	ldr	r3, [fp, #-64]
	sub	r2, fp, #48
	ldr	r1, [fp, #-56]
	mov	r0, r7
	cmp	r3, r5
	str	r2, [sp]
	add	r4, r4, #1
	mov	r2, r10
	ldrlt	r3, [fp, #-60]
	movge	r3, r5
	rsblt	r3, r3, r5
	bl	ReorderSTList
	cmp	r4, r9
	bne	.L782
.L772:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L778:
	add	r3, r3, #1
	add	r5, r5, r3
	ldr	r3, [fp, #-60]
	cmp	r3, r5
	rsble	r5, r3, r5
	b	.L779
.L773:
	ldr	r1, [r2, #216]
	mov	r4, #2208
	ldr	r5, [r3, #1304]
	mov	lr, #4000
	ldr	r2, [r2, #224]
	mov	r0, #1
	ldr	r3, [r3, #1300]
	mla	r1, r4, r1, r5
	str	r2, [fp, #-64]
	ldr	r2, [r1, #28]
	mla	r3, lr, r2, r3
	ldr	r3, [r3, #2196]
	add	r3, r3, #4
	mov	r3, r0, asl r3
	str	r3, [fp, #-60]
	b	.L783
	UNWIND(.fnend)
	.size	ReorderRefPiclist, .-ReorderRefPiclist
	.align	2
	.global	ReorderListX
	.type	ReorderListX, %function
ReorderListX:
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
	add	r4, r0, #20480
	mov	r5, r0
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L791
	add	r6, r0, #16384
	ldrb	r2, [r6, #3512]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L803
.L794:
	cmp	r3, #1
	ldr	r3, [r4, #260]
	add	r3, r3, #1
	str	r3, [r4, #248]
	bne	.L791
	ldrb	r3, [r6, #3513]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L804
.L796:
	ldr	r3, [r4, #264]
	add	r3, r3, #1
	str	r3, [r4, #252]
.L791:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L803:
	add	r7, r0, #20224
	add	lr, r0, #19968
	add	ip, r0, #19712
	add	r1, r0, #26880
	ldr	r3, [r4, #260]
	add	lr, lr, #196
	add	ip, ip, #188
	add	r7, r7, #204
	stmia	sp, {ip, lr}
	add	r2, r4, #248
	str	r7, [sp, #8]
	add	r1, r1, #244
	bl	ReorderRefPiclist
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	b	.L794
.L804:
	add	lr, r5, #20480
	add	ip, r5, #20224
	add	r0, r5, #19968
	add	r1, r5, #27136
	ldr	r3, [r4, #264]
	mov	r2, lr
	add	ip, ip, #72
	add	lr, lr, #76
	add	r0, r0, #64
	str	lr, [sp, #8]
	stmia	sp, {r0, ip}
	add	r2, r2, #252
	add	r1, r1, #120
	mov	r0, r5
	bl	ReorderRefPiclist
	b	.L796
	UNWIND(.fnend)
	.size	ReorderListX, .-ReorderListX
	.align	2
	.global	GenPiclistfromFrmlist
	.type	GenPiclistfromFrmlist, %function
GenPiclistfromFrmlist:
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
	cmp	r2, #31
	ldr	r6, [fp, #8]
	mov	r7, r1
	ldr	lr, .L868
	movcc	r4, r2
	ldr	ip, .L868+4
	movcs	r4, #31
	cmp	r6, #0
	str	r3, [fp, #-52]
	movne	r6, lr
	moveq	r6, ip
	cmp	r0, #1
	moveq	r5, #0
	moveq	r10, r5
	beq	.L808
	cmp	r0, #2
	moveq	r5, #0
	moveq	r10, r5
	bne	.L816
.L817:
	cmp	r10, r4
	movcs	r3, #0
	movcc	r3, #1
	cmp	r5, r4
	str	r3, [fp, #-48]
	movcs	r2, #0
	movcc	r2, #1
	orrs	r3, r2, r3
	beq	.L816
	cmp	r2, #0
	beq	.L822
	add	r8, r7, r5, lsl #2
	b	.L821
.L818:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L822
.L821:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	tst	ip, #2
	beq	.L818
	add	r0, r0, #776
	blx	r6
	cmp	r0, #0
	beq	.L818
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #776
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L822:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r10, lsl #2
	bne	.L824
	b	.L817
.L823:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L817
.L824:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	tst	r2, #1
	beq	.L823
	add	r0, r0, #736
	blx	r6
	cmp	r0, #0
	beq	.L823
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #736
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
	b	.L817
.L867:
	add	r0, r0, #736
	blx	r6
	cmp	r0, #0
	beq	.L809
	ldr	r3, [fp, #4]
	add	r10, r10, #1
	ldr	r2, [r8]
	ldr	r0, [r3]
	add	r2, r2, #736
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L813:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	addne	r8, r7, r5, lsl #2
	bne	.L815
	b	.L808
.L814:
	add	r5, r5, #1
	cmp	r4, r5
	bls	.L808
.L815:
	mov	r9, r8
	ldr	r0, [r8], #4
	ldrb	r2, [r0, #1]	@ zero_extendqisi2
	tst	r2, #2
	beq	.L814
	add	r0, r0, #776
	blx	r6
	cmp	r0, #0
	beq	.L814
	ldr	r3, [fp, #4]
	add	r5, r5, #1
	ldr	r2, [r9]
	ldr	r0, [r3]
	add	r2, r2, #776
	ldr	r3, [fp, #-52]
	str	r2, [r3, r0, asl #2]
	ldr	r3, [fp, #4]
	ldr	r2, [r3]
	add	r2, r2, #1
	str	r2, [r3]
.L808:
	cmp	r10, r4
	movcs	r2, #0
	movcc	r2, #1
	cmp	r5, r4
	movcs	r3, #0
	movcc	r3, #1
	str	r3, [fp, #-48]
	orrs	r3, r3, r2
	beq	.L816
	cmp	r2, #0
	beq	.L813
	add	r9, r7, r10, lsl #2
	b	.L812
.L809:
	add	r10, r10, #1
	cmp	r4, r10
	bls	.L813
.L812:
	mov	r8, r9
	ldr	r0, [r9], #4
	ldrb	ip, [r0, #1]	@ zero_extendqisi2
	tst	ip, #1
	beq	.L809
	b	.L867
.L816:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L869:
	.align	2
.L868:
	.word	IsLTRefFlg
	.word	IsSTRefFlg
	UNWIND(.fnend)
	.size	GenPiclistfromFrmlist, .-GenPiclistfromFrmlist
	.align	2
	.global	InitListX
	.type	InitListX, %function
InitListX:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 208
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
	add	r6, r0, #20480
	mov	r4, r0
	add	r8, r0, #57344
	ldrb	r3, [r6, #208]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L871
	ldrb	r7, [r8, #3011]	@ zero_extendqisi2
	cmp	r7, #0
	bne	.L995
	add	r3, r0, #24576
	str	r3, [fp, #-240]
	ldr	ip, [r3, #2144]
	cmp	ip, #0
	beq	.L938
	add	r1, r0, #26368
	mov	r3, r7
	add	r1, r1, #212
	b	.L877
.L876:
	cmp	r3, ip
	beq	.L875
.L877:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L876
	ldr	r0, [r2, #696]
	bic	r0, r0, #-16777216
	bic	r0, r0, #255
	cmp	r0, #65536
	bne	.L876
	add	r0, r7, #6720
	cmp	r3, ip
	add	r0, r0, #60
	add	r2, r2, #696
	add	r7, r7, #1
	add	r0, r4, r0, lsl #2
	str	r2, [r0, #4]
	bne	.L877
.L875:
	add	r0, r4, #26880
	ldr	r3, .L1003
	mov	r1, r7
	add	r0, r0, #244
	mov	r2, #4
	bl	qsort
	ldr	r3, [fp, #-240]
	str	r7, [r6, #248]
	ldr	r1, [r3, #2148]
	cmp	r1, #0
	beq	.L939
	add	r0, r4, #26624
	mov	r5, r7
	add	r0, r0, #20
	mov	r3, #0
	b	.L880
.L879:
	cmp	r3, r1
	beq	.L996
.L880:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L879
	ldr	ip, [r2, #696]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	bne	.L879
	add	ip, r5, #6720
	cmp	r3, r1
	add	ip, ip, #60
	add	r2, r2, #696
	add	r5, r5, #1
	add	ip, r4, ip, lsl #2
	str	r2, [ip, #4]
	bne	.L880
.L996:
	rsb	r1, r7, r5
.L878:
	add	r0, r4, r7, lsl #2
	ldr	r3, .L1003+4
	add	r0, r0, #26880
	mov	r2, #4
	add	r0, r0, #244
	bl	qsort
	mov	r2, r5
	cmp	r2, #0
	mov	r3, #0
	str	r5, [r6, #248]
	str	r3, [r6, #252]
	beq	.L997
.L886:
	ldr	r0, [r6, #260]
	ldr	r1, [r6, #264]
	add	r0, r0, #1
	cmp	r2, r0
	add	r1, r1, #1
	movcs	r2, r0
	cmp	r3, r1
	str	r2, [r6, #248]
	movcs	r3, r1
	cmp	r2, #32
	str	r3, [r6, #252]
	bhi	.L930
	add	r2, r2, #6720
	add	r1, r4, #27136
	add	r2, r2, #60
	add	r1, r1, #116
	mov	r0, #0
	add	r2, r4, r2, lsl #2
.L929:
	str	r0, [r2, #4]!
	cmp	r2, r1
	bne	.L929
.L930:
	cmp	r3, #32
	bhi	.L928
	add	r3, r3, #6784
	add	r2, r4, #27136
	add	r3, r3, #29
	add	r2, r2, #248
	mov	r1, #0
	add	r4, r4, r3, lsl #2
.L931:
	str	r1, [r4, #4]!
	cmp	r4, r2
	bne	.L931
.L928:
	mov	r0, #0
.L981:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L871:
	ldrb	r5, [r8, #3011]	@ zero_extendqisi2
	add	r3, r0, #24576
	str	r3, [fp, #-240]
	cmp	r5, #0
	beq	.L892
	ldr	ip, [r3, #2144]
	cmp	ip, #0
	beq	.L998
	add	r9, r0, #26368
	mov	r5, #0
	add	r9, r9, #212
	mov	r3, r5
	mov	r1, r9
.L911:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L910
	sub	r0, fp, #44
	ldr	lr, [r8, #3676]
	add	r7, r0, r5, lsl #2
	ldr	r0, [r2, #664]
	cmp	lr, r0
	strge	r2, [r7, #-192]
	addge	r5, r5, #1
.L910:
	cmp	r3, ip
	bne	.L911
	sub	r10, fp, #236
	ldr	r3, .L1003+8
	mov	r2, #4
	mov	r1, r5
	mov	r0, r10
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r7, [r3, #2144]
	cmp	r7, #0
	beq	.L992
.L936:
	mov	r3, r9
	mov	r2, #0
	mov	r9, r5
.L914:
	ldr	r1, [r3, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L913
	sub	r0, fp, #44
	ldr	ip, [r8, #3676]
	add	lr, r0, r9, lsl #2
	ldr	r0, [r1, #664]
	cmp	ip, r0
	strlt	r1, [lr, #-192]
	addlt	r9, r9, #1
.L913:
	cmp	r2, r7
	bne	.L914
	rsb	r7, r5, r9
	mov	r3, r5, asl #2
	add	r0, r10, r3
	str	r3, [fp, #-244]
	mov	r1, r7
	ldr	r3, .L1003+12
	mov	r2, #4
	bl	qsort
	cmp	r5, #0
	subeq	ip, fp, #172
	beq	.L915
.L933:
	sub	ip, fp, #172
	mov	r2, r10
	add	r7, ip, r7, lsl #2
	mov	r3, #0
.L916:
	add	r3, r3, #1
	ldr	r1, [r2], #4
	cmp	r3, r5
	str	r1, [r7], #4
	bcc	.L916
.L915:
	cmp	r9, r5
	bls	.L917
	ldr	r3, [fp, #-244]
	add	r2, r10, r3
	mov	r3, ip
.L918:
	add	r5, r5, #1
	ldr	r1, [r2], #4
	cmp	r5, r9
	str	r1, [r3], #4
	bne	.L918
.L917:
	add	r2, r4, #20480
	add	r3, r4, #26880
	add	r2, r2, #248
	mov	r5, #0
	add	r3, r3, #244
	str	r5, [r6, #248]
	str	r5, [r6, #252]
	mov	r1, r10
	ldrb	r0, [r8, #3011]	@ zero_extendqisi2
	add	r10, r4, #27136
	str	ip, [fp, #-252]
	mov	ip, r2
	str	r2, [fp, #-248]
	mov	r2, r9
	str	ip, [sp]
	add	r10, r10, #120
	str	r5, [sp, #4]
	str	r3, [fp, #-244]
	bl	GenPiclistfromFrmlist
	ldr	ip, [fp, #-252]
	add	r3, r4, #20480
	ldrb	r0, [r8, #3011]	@ zero_extendqisi2
	mov	r2, r9
	mov	lr, r3
	str	r5, [sp, #4]
	mov	r1, ip
	mov	r3, r10
	add	ip, lr, #252
	str	ip, [sp]
	str	ip, [fp, #-252]
	bl	GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	r7, [r3, #2148]
	cmp	r7, r5
	subeq	r9, fp, #108
	beq	.L919
	add	r3, r4, #26624
	sub	r9, fp, #108
	add	r3, r3, #20
	mov	r2, r9
.L920:
	add	r5, r5, #1
	ldr	r1, [r3, #4]!
	cmp	r5, r7
	str	r1, [r2], #4
	bne	.L920
.L919:
	ldr	r3, .L1003+16
	mov	r2, #4
	mov	r1, r7
	mov	r0, r9
	bl	qsort
	ldr	r3, [fp, #-248]
	ldrb	r0, [r8, #3011]	@ zero_extendqisi2
	mov	r5, #1
	mov	r2, r7
	mov	r1, r9
	str	r3, [sp]
	str	r5, [sp, #4]
	ldr	r3, [fp, #-244]
	bl	GenPiclistfromFrmlist
	ldr	r2, [fp, #-252]
	ldrb	r0, [r8, #3011]	@ zero_extendqisi2
	mov	r3, r10
	mov	r1, r9
	str	r5, [sp, #4]
	str	r2, [sp]
	mov	r2, r7
	bl	GenPiclistfromFrmlist
	ldr	r2, [r6, #248]
	ldr	r3, [r6, #252]
	rsb	r1, r3, r2
	clz	r1, r1
	mov	r1, r1, lsr #5
.L909:
	cmp	r2, #1
	movls	r1, #0
	andhi	r1, r1, #1
	cmp	r1, #0
	beq	.L921
	cmp	r2, #0
	ldr	r1, [fp, #-240]
	beq	.L922
	ldr	r7, [r1, #2548]
	ldr	r1, [r1, #2680]
	cmp	r7, r1
	bne	.L921
	add	r0, r4, #27136
	ldr	ip, [fp, #-244]
	add	r0, r0, #120
	mov	r1, #0
	b	.L923
.L924:
	ldr	r5, [ip, #4]!
	ldr	lr, [r0, #4]!
	cmp	r5, lr
	bne	.L921
.L923:
	add	r1, r1, #1
	cmp	r1, r2
	bne	.L924
.L925:
	ldr	r0, [fp, #-240]
	ldr	r1, [r0, #2684]
	str	r7, [r0, #2684]
	str	r1, [r0, #2680]
.L921:
	orrs	r1, r2, r3
	bne	.L886
	ldr	r1, .L1003+20
.L987:
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	b	.L981
.L892:
	ldr	r10, [r3, #2144]
	cmp	r10, #0
	beq	.L895
	add	r9, r0, #26368
	mov	r3, r5
	add	r9, r9, #212
	mov	r1, r9
	b	.L897
.L896:
	cmp	r3, r10
	beq	.L999
.L897:
	ldr	r2, [r1, #4]!
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L896
	add	r0, r5, #6720
	ldr	ip, [r2, #708]
	add	r0, r0, #60
	ldr	lr, [r8, #3680]
	add	r2, r2, #696
	add	r0, r4, r0, lsl #2
	cmp	lr, ip
	addge	r5, r5, #1
	strge	r2, [r0, #4]
	cmp	r3, r10
	bne	.L897
.L999:
	add	r3, r4, #26880
	mov	r1, r5
	mov	r2, r3
	add	r2, r2, #244
	ldr	r3, .L1003+24
	mov	r0, r2
	str	r2, [fp, #-244]
	mov	r2, #4
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r7, [r3, #2144]
	cmp	r7, #0
	beq	.L991
.L934:
	mov	r3, r9
	mov	r10, r5
	mov	r2, #0
	b	.L900
.L899:
	cmp	r2, r7
	beq	.L1000
.L900:
	ldr	r1, [r3, #4]!
	add	r2, r2, #1
	ldrb	r0, [r1, #2]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L899
	add	r0, r10, #6720
	ldr	ip, [r1, #708]
	add	r0, r0, #60
	ldr	lr, [r8, #3680]
	add	r1, r1, #696
	add	r0, r4, r0, lsl #2
	cmp	lr, ip
	addlt	r10, r10, #1
	strlt	r1, [r0, #4]
	cmp	r2, r7
	bne	.L900
.L1000:
	add	r8, r5, #6720
	rsb	r7, r5, r10
	add	r8, r8, #60
	mov	r2, #4
	ldr	r3, .L1003+28
	mov	r1, r7
	add	r0, r4, r8, lsl #2
	add	r9, r4, r10, lsl #2
	add	r0, r0, r2
	add	r9, r9, #26880
	bl	qsort
	cmp	r5, #0
	add	r9, r9, #244
	beq	.L902
.L932:
	add	r7, r7, #6784
	add	r2, r4, #26880
	add	r7, r7, #29
	add	r2, r2, #240
	mov	r3, #0
	add	r7, r4, r7, lsl #2
.L903:
	add	r3, r3, #1
	ldr	r1, [r2, #4]!
	cmp	r3, r5
	str	r1, [r7, #4]!
	bcc	.L903
.L902:
	cmp	r10, r5
	bls	.L904
	add	r3, r4, #27136
	add	r8, r4, r8, lsl #2
	add	r3, r3, #116
.L905:
	add	r5, r5, #1
	ldr	r2, [r8, #4]!
	cmp	r5, r10
	str	r2, [r3, #4]!
	bne	.L905
.L904:
	ldr	r3, [fp, #-240]
	str	r10, [r6, #252]
	str	r10, [r6, #248]
	ldr	r1, [r3, #2148]
	cmp	r1, #0
	beq	.L941
	add	r0, r4, #26624
	mov	r5, r10
	add	r0, r0, #20
	mov	r3, #0
	b	.L908
.L907:
	cmp	r3, r1
	beq	.L1001
.L908:
	ldr	r2, [r0, #4]!
	add	r3, r3, #1
	ldrb	ip, [r2, #1]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L907
	ldrb	ip, [r2, #697]	@ zero_extendqisi2
	cmp	ip, #1
	bne	.L907
	add	ip, r4, r5, lsl #2
	cmp	r3, r1
	add	ip, ip, #24576
	add	r2, r2, #696
	add	r5, r5, #1
	str	r2, [ip, #2548]
	str	r2, [ip, #2680]
	bne	.L908
.L1001:
	rsb	r1, r10, r5
.L906:
	mov	r0, r9
	ldr	r3, .L1003+4
	mov	r2, #4
	bl	qsort
	ldr	r0, [r6, #248]
	ldr	r3, .L1003+4
	mov	r2, #4
	rsb	r1, r0, r5
	add	r0, r4, r0, lsl #2
	add	r0, r0, #27136
	add	r0, r0, #120
	bl	qsort
	mov	r3, r5
	str	r5, [r6, #252]
	mov	r2, r5
	str	r5, [r6, #248]
	mov	r1, #1
	b	.L909
.L995:
	add	r2, r0, #24576
	str	r2, [fp, #-240]
	ldr	lr, [r2, #2144]
	cmp	lr, #0
	moveq	r7, lr
	beq	.L874
	add	r1, r0, #26368
	mov	r7, r3
	add	r1, r1, #212
.L883:
	ldr	r2, [r1, #4]!
	sub	r0, fp, #44
	add	ip, r0, r7, lsl #2
	add	r3, r3, #1
	ldrb	r0, [r2, #2]	@ zero_extendqisi2
	cmp	r0, #0
	strne	r2, [ip, #-192]
	addne	r7, r7, #1
	cmp	r3, lr
	bne	.L883
.L874:
	add	r10, r4, #26880
	mov	r1, r7
	ldr	r3, .L1003+32
	mov	r2, #4
	sub	r0, fp, #236
	add	r10, r10, #244
	bl	qsort
	add	ip, r4, #20480
	add	ip, ip, #248
	mov	r5, #0
	mov	r2, r7
	str	r5, [r6, #248]
	mov	r3, r10
	ldrb	r0, [r8, #3011]	@ zero_extendqisi2
	sub	r1, fp, #236
	str	ip, [sp]
	str	r5, [sp, #4]
	str	ip, [fp, #-244]
	bl	GenPiclistfromFrmlist
	ldr	r3, [fp, #-240]
	ldr	ip, [fp, #-244]
	ldr	r7, [r3, #2148]
	cmp	r7, r5
	subeq	r9, fp, #108
	beq	.L884
	add	r3, r4, #26624
	sub	r9, fp, #108
	add	r3, r3, #20
	mov	r2, r9
.L885:
	add	r5, r5, #1
	ldr	r1, [r3, #4]!
	cmp	r5, r7
	str	r1, [r2], #4
	bne	.L885
.L884:
	ldr	r3, .L1003+16
	mov	r2, #4
	mov	r1, r7
	mov	r0, r9
	str	ip, [fp, #-244]
	bl	qsort
	ldr	ip, [fp, #-244]
	mov	r3, r10
	ldrb	r0, [r8, #3011]	@ zero_extendqisi2
	mov	r2, r7
	mov	r1, r9
	str	ip, [sp]
	mov	ip, #1
	str	ip, [sp, #4]
	bl	GenPiclistfromFrmlist
	ldr	r2, [r6, #248]
	mov	r3, #0
	str	r3, [r6, #252]
	cmp	r2, #0
	bne	.L886
.L997:
	ldr	r3, [r4]
	ldr	r3, [r3, #24]
	cmp	r3, #2
	bne	.L887
	ldrb	r3, [r8, #3011]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1002
	cmp	r3, #1
	ldr	r2, [fp, #-240]
	ldr	r3, [r8, #3656]
	addeq	r3, r3, #736
	addne	r3, r3, #776
	str	r3, [r2, #2548]
.L889:
	mov	r3, #0
	mov	r2, #1
	b	.L886
.L1002:
	ldr	r2, [fp, #-240]
	ldr	r3, [r8, #3656]
	add	r3, r3, #696
	str	r3, [r2, #2548]
	b	.L889
.L922:
	ldr	r7, [r1, #2680]
	b	.L925
.L991:
	add	r8, r5, #6720
	mov	r2, #4
	add	r8, r8, #60
	ldr	r3, .L1003+28
	mov	r1, r7
	add	r9, r4, r8, lsl #2
	add	r9, r9, r2
	mov	r0, r9
	bl	qsort
	subs	r10, r5, #0
	bne	.L932
	b	.L904
.L992:
	mov	r3, r5, asl #2
	mov	r1, r7
	str	r3, [fp, #-244]
	mov	r2, r3
	ldr	r3, .L1003+12
	add	r0, r10, r2
	mov	r2, #4
	bl	qsort
	subs	r9, r5, #0
	bne	.L933
.L988:
	sub	ip, fp, #172
	b	.L917
.L938:
	mov	r7, ip
	b	.L875
.L998:
	sub	r10, fp, #236
	ldr	r3, .L1003+8
	mov	r1, ip
	mov	r2, #4
	mov	r0, r10
	str	ip, [fp, #-244]
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	ip, [fp, #-244]
	ldr	r7, [r3, #2144]
	cmp	r7, #0
	addne	r9, r4, #26368
	movne	r5, ip
	addne	r9, r9, #212
	bne	.L936
	ldr	r3, .L1003+12
	mov	r2, #4
	mov	r1, r7
	mov	r0, r10
	mov	r9, r7
	bl	qsort
	b	.L988
.L895:
	add	r3, r0, #26880
	mov	r1, r10
	mov	r2, r3
	add	r2, r2, #244
	ldr	r3, .L1003+24
	mov	r0, r2
	str	r2, [fp, #-244]
	mov	r2, #4
	bl	qsort
	ldr	r3, [fp, #-240]
	ldr	r7, [r3, #2144]
	cmp	r7, #0
	addne	r9, r4, #26368
	movne	r5, r10
	addne	r9, r9, #212
	bne	.L934
	ldr	r9, [fp, #-244]
	mov	r2, #4
	ldr	r3, .L1003+28
	mov	r1, r7
	mov	r10, r7
	mov	r0, r9
	bl	qsort
	b	.L904
.L939:
	mov	r5, r7
	b	.L878
.L941:
	mov	r5, r10
	b	.L906
.L887:
	ldr	r1, .L1003+36
	b	.L987
.L1004:
	.align	2
.L1003:
	.word	compare_pic_by_pic_num_desc
	.word	compare_pic_by_lt_pic_num_asc
	.word	compare_fs_by_poc_desc
	.word	compare_fs_by_poc_asc
	.word	compare_fs_by_lt_pic_idx_asc
	.word	.LC38
	.word	compare_pic_by_poc_desc
	.word	compare_pic_by_poc_asc
	.word	compare_fs_by_frame_num_desc
	.word	.LC37
	UNWIND(.fnend)
	.size	InitListX, .-InitListX
	.align	2
	.global	DumpList
	.type	DumpList, %function
DumpList:
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
	ldr	r3, .L1007
	ldr	r3, [r3]
	tst	r3, #8192
	ldmeqfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	DumpList.part.7
.L1008:
	.align	2
.L1007:
	.word	g_PrintEnable
	UNWIND(.fnend)
	.size	DumpList, .-DumpList
	.align	2
	.global	FindNearestPOCPicId
	.type	FindNearestPOCPicId, %function
FindNearestPOCPicId:
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
	add	r3, r0, #24576
	ldr	r4, [r3, #2140]
	cmp	r4, #0
	beq	.L1014
	ldr	r3, [r3, #1944]
	add	r2, r0, #57344
	ldr	r5, [r2, #3676]
	ldr	lr, [r3, #664]
	rsb	lr, lr, r5
	cmp	lr, #0
	rsblt	lr, lr, #0
	cmp	r4, #1
	bls	.L1015
	add	r1, r0, #26368
	mov	r2, #1
	add	r1, r1, #152
	mov	r0, #0
.L1013:
	ldr	ip, [r1, #4]!
	add	r2, r2, #1
	ldr	r3, [ip, #664]
	rsb	r3, r3, r5
	cmp	r3, #0
	rsblt	r3, r3, #0
	cmp	r3, lr
	ldrlt	r0, [ip, #164]
	movlt	lr, r3
	cmp	r2, r4
	bne	.L1013
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1015:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1014:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	FindNearestPOCPicId, .-FindNearestPOCPicId
	.align	2
	.global	FindMinRefIdx
	.type	FindMinRefIdx, %function
FindMinRefIdx:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r3, r0, #20480
	ldrb	r2, [r3, #208]	@ zero_extendqisi2
	cmp	r2, #2
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	add	r2, r0, #57344
	add	r5, r0, #26880
	ldrb	ip, [r2, #3011]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L1047
	ldr	lr, [r3, #248]
	mov	r4, r5
	mov	r6, r5
	mov	r7, ip
	cmp	lr, #0
	add	r5, r5, #116
	add	r4, r4, #120
	add	r6, r6, #240
	beq	.L1025
.L1049:
	mov	r2, r6
	mov	r0, #32
	mov	r3, #0
	b	.L1023
.L1022:
	add	r3, r3, #1
	cmp	r3, lr
	beq	.L1048
.L1023:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #688]
	cmp	r1, ip
	bne	.L1022
	cmp	r0, r3
	movcs	r0, r3
	add	r3, r3, #1
	cmp	r3, lr
	str	r0, [r4, #-4]
	str	r0, [r5, #4]
	bne	.L1023
.L1048:
	cmp	r0, #31
	bhi	.L1025
.L1024:
	add	ip, ip, #1
	add	r5, r5, #8
	cmp	ip, #16
	add	r4, r4, #8
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	lr, #0
	bne	.L1049
.L1025:
	str	r7, [r4, #-4]
	str	r7, [r5, #4]
	b	.L1024
.L1047:
	ldr	r4, [r3, #248]
	mov	ip, #0
	mov	r6, r5
	mov	r7, ip
	cmp	r4, #0
	add	r5, r5, #116
	add	r6, r6, #240
	beq	.L1029
.L1051:
	mov	r1, r6
	mov	lr, #32
	mov	r2, #0
	b	.L1027
.L1026:
	add	r2, r2, #1
	cmp	r2, r4
	beq	.L1050
.L1027:
	ldr	r3, [r1, #4]!
	ldr	r8, [r3, #36]
	ldrb	r0, [r3]	@ zero_extendqisi2
	ldr	r3, [r8, #688]
	mov	r3, r3, asl #1
	cmp	r0, #2
	orreq	r3, r3, #1
	cmp	r3, ip
	bne	.L1026
	cmp	lr, r2
	movcs	lr, r2
	add	r2, r2, #1
	cmp	r2, r4
	str	lr, [r5]
	bne	.L1027
.L1050:
	cmp	lr, #31
	bhi	.L1029
.L1028:
	add	ip, ip, #1
	add	r5, r5, #4
	cmp	ip, #32
	ldmeqfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	cmp	r4, #0
	bne	.L1051
.L1029:
	str	r7, [r5]
	b	.L1028
	UNWIND(.fnend)
	.size	FindMinRefIdx, .-FindMinRefIdx
	.align	2
	.global	DecList
	.type	DecList, %function
DecList:
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
	mov	r6, r0
	bl	FindNearestPOCPicId
	add	r5, r6, #20480
	mvn	r4, #0
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	str	r4, [r5, #1832]
	cmp	r3, #2
	str	r0, [r5, #1836]
	beq	.L1065
	mov	r0, r6
	bl	InitListX
	cmp	r0, #0
	bne	.L1066
	ldr	r4, .L1069
	mov	r0, #13
	ldr	r1, .L1069+4
	bl	dprint_vfmw
	ldr	r3, [r4]
	tst	r3, #8192
	bne	.L1067
.L1056:
	mov	r0, r6
	bl	ReorderListX
	mov	r0, r6
	bl	RepairList
	cmp	r0, #0
	bne	.L1058
	mov	r0, r6
	bl	FindMinRefIdx
	add	r3, r6, #24576
	mov	r0, #13
	ldr	r1, .L1069+8
	ldr	r3, [r3, #2548]
	cmp	r3, #0
	ldrne	r3, [r3, #36]
	mvneq	r3, #0
	ldrne	r3, [r3, #164]
	str	r3, [r5, #1832]
	bl	dprint_vfmw
	ldr	r4, [r4]
	ands	r4, r4, #8192
	bne	.L1068
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1068:
	mov	r0, r6
	bl	DumpList.part.7
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1065:
	mov	r0, #0
	str	r0, [r5, #248]
	str	r0, [r5, #252]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1067:
	mov	r0, r6
	bl	DumpList.part.7
	b	.L1056
.L1058:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1066:
	ldr	r1, .L1069+12
	mov	r0, #13
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1070:
	.align	2
.L1069:
	.word	g_PrintEnable
	.word	.LC40
	.word	.LC41
	.word	.LC39
	UNWIND(.fnend)
	.size	DecList, .-DecList
	.align	2
	.global	NoPicOut
	.type	NoPicOut, %function
NoPicOut:
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
	add	r4, r0, #61440
	ldr	ip, [r4, #1028]
	cmp	ip, #0
	addne	r3, r0, #27904
	movne	r2, #0
	addne	r3, r3, #156
	movne	lr, r2
	bne	.L1077
	b	.L1078
.L1086:
	ldrb	r1, [r3, #-664]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1075
	cmp	r2, ip
	add	r3, r3, #824
	beq	.L1078
.L1077:
	ldr	r1, [r3]
	add	r2, r2, #1
	cmp	r1, #1
	bne	.L1086
.L1075:
	cmp	r2, ip
	strb	lr, [r3, #-667]
	strb	lr, [r3, #-666]
	add	r3, r3, #824
	bne	.L1077
.L1078:
	ldr	r2, [r4, #1032]
	cmp	r2, #0
	beq	.L1087
	add	r0, r0, #62208
	mov	r3, #0
	add	r0, r0, #188
	mov	r1, r3
.L1079:
	add	r3, r3, #1
	str	r1, [r0, #4]!
	cmp	r3, r2
	bne	.L1079
	ldmfd	sp, {r4, fp, sp, pc}
.L1087:
	ldmfd	sp, {r4, fp, sp, pc}
	UNWIND(.fnend)
	.size	NoPicOut, .-NoPicOut
	.align	2
	.global	GetBackPicFromVOQueue
	.type	GetBackPicFromVOQueue, %function
GetBackPicFromVOQueue:
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
	add	r5, r0, #61440
	mov	r9, r0
	ldr	r0, [r5, #2344]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L1105
.L1089:
	ldr	r3, [r5, #1028]
	cmp	r3, #0
	beq	.L1096
	add	r10, r9, #27904
	mov	r6, #0
	add	r10, r10, #72
	mov	r7, #0
	mov	r8, #0
.L1095:
	sub	r4, r10, #32
	mov	r3, #0
	strb	r3, [r10, #-583]
	strb	r3, [r10, #-582]
.L1094:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L1093
	ldr	r0, [r5, #2344]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L1093:
	cmp	r4, r10
	bne	.L1094
	ldr	r3, [r5, #1028]
	add	r8, r8, #1
	add	r10, r10, #824
	cmp	r3, r8
	bhi	.L1095
.L1096:
	ldr	r2, [r5, #1032]
	cmp	r2, #0
	beq	.L1106
	add	r9, r9, #62208
	mov	r3, #0
	add	r9, r9, #188
	mov	r1, r3
.L1097:
	add	r3, r3, #1
	str	r1, [r9, #4]!
	cmp	r3, r2
	bne	.L1097
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1105:
	add	r0, r9, #8
	bl	ResetVoQueue
	b	.L1089
.L1106:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetBackPicFromVOQueue, .-GetBackPicFromVOQueue
	.align	2
	.global	wait_vo
	.type	wait_vo, %function
wait_vo:
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
	.size	wait_vo, .-wait_vo
	.align	2
	.global	GetReRangeFlag
	.type	GetReRangeFlag, %function
GetReRangeFlag:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r7, r0, #12288
	add	r3, r0, #20480
	mov	r5, r0
	ldr	r0, [r7, #1304]
	mov	ip, #2208
	ldr	r3, [r3, #216]
	mov	r4, #4000
	ldr	r2, [r7, #1300]
	mov	r6, r1
	ldr	lr, [r7, #1276]
	mla	r3, ip, r3, r0
	ldr	r0, [r7, #1280]
	ldr	r3, [r3, #28]
	mla	r4, r4, r3, r2
	ldrb	r3, [r4, #18]	@ zero_extendqisi2
	ldr	r1, [r4, #3252]
	rsb	r3, r3, #2
	ldr	r2, [r4, #3248]
	mla	r3, r1, r3, r3
	add	r2, r2, #1
	cmp	r2, lr
	cmpeq	r3, r0
	movne	r1, #1
	moveq	r1, #0
	bne	.L1109
	add	ip, r5, #24576
	ldr	r8, [r4, #3272]
	ldr	ip, [ip, #2136]
	add	ip, ip, #1
	cmp	r8, ip
	moveq	r3, r1
	beq	.L1110
.L1109:
	ldr	r1, .L1114
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L1113
	add	r1, r5, #61440
	mov	r0, r0, asl #4
	mov	r2, r2, asl #4
	mov	r3, r3, asl #4
	mov	lr, lr, asl #4
	strh	r0, [fp, #-42]	@ movhi
	strh	r2, [fp, #-40]	@ movhi
	sub	r2, fp, #44
	strh	r3, [fp, #-38]	@ movhi
	mov	r3, #8
	ldr	r0, [r1, #2344]
	mov	r1, #2
	strh	lr, [fp, #-44]	@ movhi
	blx	ip
.L1113:
	ldr	ip, [r4, #3272]
	mov	r3, #1
.L1110:
	add	r5, r5, #16384
	ldr	r2, [r4, #36]
	ldr	lr, [r7, #1344]
	mov	r0, r3
	ldr	r1, [r5, #484]
	cmp	lr, r2
	cmpeq	r1, ip
	movne	r2, #1
	moveq	r2, #0
	orr	r3, r2, r3
	str	r3, [r6]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1115:
	.align	2
.L1114:
	.word	g_event_report
	UNWIND(.fnend)
	.size	GetReRangeFlag, .-GetReRangeFlag
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	DecPOC
	.type	DecPOC, %function
DecPOC:
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
	add	r2, r0, #12288
	add	r6, r0, #20480
	mov	r4, #2208
	mov	r5, #4000
	ldr	r1, [r6, #216]
	mov	ip, #1
	ldr	r3, [r2, #1304]
	ldr	lr, [r2, #1300]
	ldrb	r2, [r6, #211]	@ zero_extendqisi2
	mla	r3, r4, r1, r3
	sub	r2, r2, #5
	clz	r2, r2
	mov	r2, r2, lsr #5
	ldr	r3, [r3, #28]
	mla	r5, r5, r3, lr
	ldr	r1, [r5, #2200]
	ldr	r3, [r5, #2196]
	cmp	r1, ip
	ldr	lr, [r5, #2204]
	add	r3, r3, #4
	mov	r3, ip, asl r3
	beq	.L1118
	bcc	.L1119
	cmp	r1, #2
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	cmp	r2, #0
	add	r4, r0, #16384
	bne	.L1174
	ldr	r1, [r4, #3444]
	cmp	r1, #0
	bne	.L1152
	ldr	r2, [r4, #3484]
	ldr	r0, [r4, #3480]
	ldr	r1, [r4, #3492]
	cmp	r2, r0
	addcc	r1, r1, r3
	strcc	r1, [r4, #3488]
	bcs	.L1154
.L1155:
	add	r3, r1, r2
	str	r3, [r4, #3476]
	ldr	r0, [r6, #236]
	mov	r3, r3, asl #1
	cmp	r0, #0
	subeq	r3, r3, #1
	str	r3, [r4, #3464]
	ldrb	r0, [r6, #209]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L1158
	str	r3, [r4, #3460]
	str	r3, [r4, #3456]
	str	r3, [r4, #3452]
.L1151:
	str	r2, [r4, #3480]
	str	r1, [r4, #3492]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1119:
	cmp	r2, #0
	add	lr, lr, #4
	add	r4, r0, #16384
	mov	ip, ip, asl lr
	bne	.L1125
	ldr	r3, [r4, #3444]
	cmp	r3, #0
	bne	.L1123
	ldr	lr, [r4, #3428]
	ldr	r1, [r4, #3432]
	mov	r2, lr
.L1124:
	ldr	r0, [r4, #3420]
	cmp	r0, r1
	bcs	.L1122
	rsb	r3, r0, r1
	cmp	r3, ip, lsr #1
	addcs	r2, r2, ip
	strcs	r2, [r4, #3436]
	bcc	.L1122
.L1126:
	ldrb	r3, [r6, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1128
.L1176:
	ldr	r3, [r4, #3424]
	add	r2, r2, r0
	str	r2, [r4, #3452]
	add	r3, r2, r3
	str	r3, [r4, #3456]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r4, #3464]
.L1129:
	ldr	r2, [r4, #3484]
	ldr	r1, [r4, #3480]
	str	r3, [r4, #3460]
	cmp	r2, r1
	strne	r2, [r4, #3480]
	ldr	r3, [r6, #236]
	cmp	r3, #0
	ldrne	r2, [r4, #3420]
	ldrne	r3, [r4, #3436]
	strne	r2, [r4, #3432]
	strne	r3, [r4, #3428]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1118:
	cmp	r2, #0
	add	r4, r0, #16384
	movne	r3, #0
	strne	r3, [r4, #3488]
	bne	.L1133
	ldr	r1, [r4, #3444]
	cmp	r1, #0
	beq	.L1134
	mov	r3, r2
	str	r2, [r4, #3492]
	str	r2, [r4, #3480]
.L1135:
	str	r3, [r4, #3488]
.L1133:
	ldr	r3, [r5, #2216]
	cmp	r3, #0
	beq	.L1137
	ldr	r3, [r4, #3484]
	ldr	r0, [r4, #3488]
	add	r0, r3, r0
	str	r0, [r4, #3476]
	ldr	r7, [r6, #236]
	cmp	r7, #0
	bne	.L1139
	cmp	r0, #0
	beq	.L1140
	sub	r0, r0, #1
	str	r0, [r4, #3476]
.L1139:
	mov	r3, #0
	str	r3, [r4, #3508]
	ldr	r1, [r5, #2216]
	cmp	r1, r3
	bgt	.L1160
	cmp	r0, #0
	beq	.L1143
.L1177:
	sub	r8, r0, #1
	mov	r0, r8
	bl	__aeabi_uidiv
	mov	r9, r0
	mov	r0, r8
	str	r9, [r4, #3500]
	ldr	r1, [r5, #2216]
	bl	__aeabi_uidivmod
	ldr	r0, [r4, #3508]
	mul	r0, r0, r9
	str	r0, [r4, #3504]
	cmp	r1, #0
	str	r1, [r4, #3496]
	blt	.L1144
	add	r2, r5, #2208
	add	r1, r1, #1
	add	r2, r2, #8
	mov	r3, #0
.L1145:
	add	r3, r3, #1
	ldr	ip, [r2, #4]!
	cmp	r3, r1
	add	r0, r0, ip
	str	r0, [r4, #3504]
	bne	.L1145
.L1144:
	cmp	r7, #0
	ldreq	r3, [r5, #2208]
	addeq	r0, r0, r3
	streq	r0, [r4, #3504]
	ldrb	r3, [r6, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1147
	ldr	r2, [r4, #3468]
	ldr	r1, [r4, #3472]
	add	r2, r0, r2
	str	r2, [r4, #3452]
	ldr	r3, [r5, #2212]
	add	r3, r2, r3
	add	r0, r3, r1
	str	r0, [r4, #3456]
	cmp	r0, r2
	movge	r0, r2
	str	r0, [r4, #3464]
.L1148:
	ldr	r2, [r4, #3484]
	ldr	r3, [r4, #3488]
	str	r0, [r4, #3460]
	str	r2, [r4, #3480]
	str	r3, [r4, #3492]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1123:
	ldr	lr, [r4, #3448]
	cmp	lr, #0
	beq	.L1175
.L1125:
	ldr	r0, [r4, #3420]
	mov	r3, #0
	mov	lr, r3
	mov	r2, r1
	str	r3, [r4, #3428]
	str	r3, [r4, #3432]
.L1122:
	cmp	r0, r1
	bls	.L1127
	rsb	r1, r1, r0
	cmp	r1, ip, lsr #1
	rsbhi	r2, ip, r2
	strhi	r2, [r4, #3436]
	bhi	.L1126
.L1127:
	str	lr, [r4, #3436]
	ldrb	r3, [r6, #209]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1176
.L1128:
	ldrb	r3, [r6, #210]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r2, r0
	streq	r3, [r4, #3452]
	strne	r3, [r4, #3456]
	str	r3, [r4, #3464]
	b	.L1129
.L1174:
	mov	r3, #0
	ldr	r2, [r4, #3484]
	mov	r1, r3
	str	r3, [r4, #3488]
	str	r3, [r4, #3456]
	str	r3, [r4, #3452]
	str	r3, [r4, #3460]
	str	r3, [r4, #3464]
	b	.L1151
.L1137:
	str	r3, [r4, #3476]
	ldr	r7, [r6, #236]
.L1140:
	mov	r0, #0
	str	r0, [r4, #3508]
	ldr	r3, [r5, #2216]
	cmp	r3, r0
	ble	.L1143
.L1160:
	add	ip, r5, #2208
	mov	r3, #0
	add	ip, ip, #8
	mov	r2, r3
.L1142:
	ldr	r1, [ip, #4]!
	add	r2, r2, #1
	add	r3, r3, r1
	str	r3, [r4, #3508]
	ldr	r1, [r5, #2216]
	cmp	r1, r2
	bgt	.L1142
	cmp	r0, #0
	bne	.L1177
.L1143:
	mov	r0, #0
	str	r0, [r4, #3504]
	b	.L1144
.L1147:
	ldrb	r3, [r6, #210]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r2, [r5, #2212]
	ldreq	r3, [r4, #3468]
	ldrne	r3, [r4, #3468]
	addne	r0, r0, r2
	addeq	r0, r0, r3
	streq	r0, [r4, #3452]
	addne	r0, r0, r3
	strne	r0, [r4, #3456]
	str	r0, [r4, #3464]
	b	.L1148
.L1134:
	ldr	r1, [r4, #3484]
	ldr	r2, [r4, #3480]
	cmp	r1, r2
	bcs	.L1136
	ldr	r2, [r4, #3492]
	add	r3, r3, r2
	str	r3, [r4, #3488]
	b	.L1133
.L1158:
	ldrb	r0, [r6, #210]	@ zero_extendqisi2
	str	r3, [r4, #3460]
	cmp	r0, #0
	streq	r3, [r4, #3452]
	strne	r3, [r4, #3456]
	b	.L1151
.L1152:
	str	r2, [r4, #3480]
	mov	r1, r2
	str	r2, [r4, #3492]
	ldr	r2, [r4, #3484]
.L1154:
	str	r1, [r4, #3488]
	b	.L1155
.L1175:
	ldr	r3, [r4, #3452]
	mov	r2, r1
	str	lr, [r4, #3428]
	mov	r1, r3
	str	r3, [r4, #3432]
	b	.L1124
.L1136:
	ldr	r3, [r4, #3492]
	b	.L1135
	UNWIND(.fnend)
	.size	DecPOC, .-DecPOC
	.align	2
	.global	CalcPicNum
	.type	CalcPicNum, %function
CalcPicNum:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #12288
	add	r3, r0, #20480
	mov	r4, #2208
	mov	lr, #4000
	ldr	ip, [r3, #216]
	add	r6, r0, #57344
	ldr	r1, [r2, #1304]
	mov	r7, #1
	ldr	r3, [r2, #1300]
	ldrb	r2, [r6, #3011]	@ zero_extendqisi2
	mla	r1, r4, ip, r1
	cmp	r2, #0
	ldr	r1, [r1, #28]
	mla	r3, lr, r1, r3
	ldr	r3, [r3, #2196]
	add	r3, r3, #4
	mov	r7, r7, asl r3
	add	r3, r0, #24576
	beq	.L1179
	sub	r5, r2, #1
	sub	r4, r2, #2
	ldr	r2, [r3, #2144]
	clz	r5, r5
	clz	r4, r4
	cmp	r2, #0
	mov	r5, r5, lsr #5
	addne	lr, r0, #26368
	mov	r4, r4, lsr #5
	movne	r1, #0
	addne	lr, lr, #212
	beq	.L1199
.L1198:
	ldr	ip, [lr, #4]!
	ldrb	r2, [ip, #2]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1193
	ldr	r2, [ip, #652]
	ldr	r8, [r6, #3664]
	cmp	r2, r8
	rsbhi	r2, r7, r2
	str	r2, [ip, #656]
	ldr	r2, [lr]
	ldrb	ip, [r2, #2]	@ zero_extendqisi2
	tst	ip, #1
	beq	.L1196
	ldr	r8, [r2, #736]
	bic	r8, r8, #-16777216
	bic	r8, r8, #255
	cmp	r8, #65536
	ldreq	ip, [r2, #656]
	addeq	ip, r5, ip, lsl #1
	streq	ip, [r2, #744]
	ldreq	r2, [lr]
	ldreqb	ip, [r2, #2]	@ zero_extendqisi2
.L1196:
	tst	ip, #2
	beq	.L1193
	ldr	ip, [r2, #776]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #65536
	ldreq	ip, [r2, #656]
	addeq	ip, r4, ip, lsl #1
	streq	ip, [r2, #784]
.L1193:
	ldr	r2, [r3, #2144]
	add	r1, r1, #1
	cmp	r2, r1
	bhi	.L1198
.L1199:
	ldr	r2, [r3, #2148]
	cmp	r2, #0
	beq	.L1223
	add	r0, r0, #26624
	mov	r2, #0
	add	r0, r0, #20
.L1204:
	ldr	ip, [r0, #4]!
	add	r2, r2, #1
	ldrb	r1, [ip, #2]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1201
	tst	r1, #1
	beq	.L1202
	ldr	lr, [ip, #736]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #256
	ldreq	r1, [ip, #660]
	addeq	r1, r5, r1, lsl #1
	streq	r1, [ip, #740]
	ldreq	ip, [r0]
	ldreqb	r1, [ip, #2]	@ zero_extendqisi2
.L1202:
	tst	r1, #2
	beq	.L1201
	ldr	r1, [ip, #776]
	bic	r1, r1, #-16777216
	bic	r1, r1, #255
	cmp	r1, #256
	ldreq	r1, [ip, #660]
	addeq	r1, r4, r1, lsl #1
	streq	r1, [ip, #780]
.L1201:
	ldr	r1, [r3, #2148]
	cmp	r1, r2
	bhi	.L1204
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1179:
	ldr	r1, [r3, #2144]
	cmp	r1, #0
	addne	ip, r0, #26368
	addne	ip, ip, #212
	bne	.L1188
.L1189:
	ldr	r2, [r3, #2148]
	cmp	r2, #0
	beq	.L1224
	add	r0, r0, #26624
	mov	r2, #0
	add	r0, r0, #20
	b	.L1191
.L1190:
	ldr	r1, [r3, #2148]
	cmp	r1, r2
	bls	.L1225
.L1191:
	ldr	r1, [r0, #4]!
	add	r2, r2, #1
	ldrb	ip, [r1, #2]	@ zero_extendqisi2
	cmp	ip, #3
	bne	.L1190
	ldr	ip, [r1, #696]
	bic	ip, ip, #-16777216
	bic	ip, ip, #255
	cmp	ip, #256
	ldreq	ip, [r1, #660]
	streq	ip, [r1, #700]
	ldr	r1, [r3, #2148]
	cmp	r1, r2
	bhi	.L1191
.L1225:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1226:
	ldr	lr, [r1, #696]
	bic	lr, lr, #-16777216
	bic	lr, lr, #255
	cmp	lr, #65536
	bne	.L1185
	ldr	lr, [r1, #652]
	ldr	r4, [r6, #3664]
	rsb	r5, r7, lr
	cmp	lr, r4
	strhi	r5, [r1, #656]
	strls	lr, [r1, #656]
	ldr	r1, [ip]
	ldr	lr, [r1, #656]
	str	lr, [r1, #704]
.L1185:
	ldr	r1, [r3, #2144]
	add	r2, r2, #1
	cmp	r1, r2
	bls	.L1189
.L1188:
	ldr	r1, [ip, #4]!
	ldrb	lr, [r1, #2]	@ zero_extendqisi2
	cmp	lr, #3
	bne	.L1185
	b	.L1226
.L1224:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1223:
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	CalcPicNum, .-CalcPicNum
	.align	2
	.global	IsOutDPB
	.type	IsOutDPB, %function
IsOutDPB:
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
	beq	.L1232
	add	r3, r0, #24576
	ldr	ip, [r3, #2140]
	cmp	ip, #0
	beq	.L1232
	ldr	r3, [r3, #1944]
	cmp	r3, r1
	beq	.L1234
	add	r0, r0, #26368
	mov	r3, #0
	add	r0, r0, #152
	b	.L1229
.L1230:
	ldr	r2, [r0, #4]!
	cmp	r2, r1
	beq	.L1234
.L1229:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1230
.L1232:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L1234:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	IsOutDPB, .-IsOutDPB
	.align	2
	.global	WriteCurrPicYUV
	.type	WriteCurrPicYUV, %function
WriteCurrPicYUV:
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
	add	r5, r0, #57344
	ldr	r1, .L1238
	mov	r0, #2
	ldrb	r4, [r5, #3011]	@ zero_extendqisi2
	ldr	r3, [r5, #3656]
	mov	r2, r4
	ldr	r3, [r3, #164]
	bl	dprint_vfmw
	ldr	ip, [r5, #3708]
	cmp	r4, #3
	cmpne	r4, #0
	ldr	r3, [r5, #3704]
	addne	r2, r4, #1
	ldr	r1, .L1238+4
	moveq	r2, #1
	str	ip, [sp]
	mov	r0, #22
	bl	dprint_vfmw
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1239:
	.align	2
.L1238:
	.word	.LC42
	.word	.LC43
	UNWIND(.fnend)
	.size	WriteCurrPicYUV, .-WriteCurrPicYUV
	.align	2
	.global	WritePicMsg
	.type	WritePicMsg, %function
WritePicMsg:
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
	add	r10, r0, #57344
	mov	r4, r0
	ldr	r1, .L1276
	ldr	lr, [r10, #3724]
	mov	r0, #2
	ldr	ip, [r10, #3172]
	add	r5, r4, #61440
	ldrb	r3, [r10, #3011]	@ zero_extendqisi2
	add	r9, r4, #12288
	ldr	r2, [r10, #3672]
	add	r8, r4, #16384
	stmia	sp, {ip, lr}
	bl	dprint_vfmw
	add	r3, r4, #60928
	mov	r2, #0
	str	r2, [r5, #2268]
	ldrd	r0, [r3, #24]
	movw	r2, #62544
	strd	r0, [r4, r2]
	ldr	r3, [r5, #2264]
	str	r3, [r5, #2024]
	ldr	r3, [r10, #3136]
	str	r3, [r5, #1800]
	ldr	r3, [r10, #3140]
	str	r3, [r5, #1804]
	ldr	r3, [r10, #3160]
	str	r3, [r5, #1808]
	ldr	r3, [r10, #3164]
	str	r3, [r5, #1812]
	ldr	r3, [r10, #3672]
	str	r3, [r5, #1112]
	ldrb	r3, [r10, #3011]	@ zero_extendqisi2
	strb	r3, [r5, #1080]
	ldrb	r3, [r9, #1327]	@ zero_extendqisi2
	str	r3, [r5, #1128]
	ldr	r3, [r10, #3708]
	str	r3, [r5, #1116]
	ldr	r3, [r10, #3712]
	str	r3, [r5, #1120]
	ldr	r3, [r8, #460]
	add	r3, r3, #1
	str	r3, [r5, #1124]
	ldrb	r3, [r9, #1326]	@ zero_extendqisi2
	strb	r3, [r5, #1083]
	ldr	r3, [r8, #1272]
	str	r3, [r5, #1132]
	ldrb	r3, [r8, #1212]	@ zero_extendqisi2
	str	r3, [r5, #1136]
	ldr	r3, [r9, #1348]
	strb	r3, [r5, #1081]
	ldrb	r3, [r8, #1216]	@ zero_extendqisi2
	ldr	r0, [r5, #2344]
	str	r3, [r5, #1140]
	ldr	r3, [r8, #3464]
	str	r3, [r5, #1144]
	ldr	r3, [r8, #3452]
	str	r3, [r5, #1148]
	ldr	r3, [r8, #3456]
	str	r3, [r5, #1152]
	ldr	r3, [r10, #3656]
	ldr	r1, [r3, #648]
	bl	FSP_GetLogicFs
	subs	r7, r0, #0
	beq	.L1274
	ldr	r2, [r7, #28]
	ldr	r3, [r7, #32]
	cmp	r2, #0
	beq	.L1244
	cmp	r3, #0
	beq	.L1244
	add	r3, r4, #62720
	add	r1, r4, #62976
	add	r1, r1, #124
	ldr	r0, [r5, #2344]
	mov	r2, r3
	add	r3, r3, #252
	add	r2, r2, #124
	add	r6, r4, #24576
	bl	FSP_GetDecFsAddrTab
	ldr	r3, [r7, #28]
	add	r2, r4, #62976
	add	r1, r4, #63232
	add	r2, r2, #128
	ldr	r0, [r5, #2344]
	ldr	r3, [r3, #4]
	str	r3, [r5, #1388]
	bl	FSP_GetPmvAddrTab
	ldr	r3, [r10, #3724]
	str	r3, [r5, #1396]
	ldr	r3, [r7, #12]
	str	r3, [r5, #1796]
	ldr	r3, [r7, #32]
	ldr	r3, [r3, #8]
	str	r3, [r5, #1392]
	ldr	r3, [r7, #32]
	ldr	r3, [r3, #60]
	str	r3, [r5, #1400]
	ldr	r3, [r6, #2412]
	cmp	r3, #0
	str	r3, [fp, #-48]
	str	r3, [r5, #2016]
	beq	.L1250
	add	lr, r4, #63232
	add	r10, r4, #26624
	add	r1, r4, #26880
	ldr	r7, [fp, #-48]
	mov	ip, r10
	mov	r0, lr
	mov	r2, lr
	add	r10, r10, #168
	add	lr, lr, #28
	add	ip, ip, #232
	add	r0, r0, #92
	add	r1, r1, #40
	add	r2, r2, #156
	mov	r3, #0
	str	r4, [fp, #-52]
.L1249:
	ldr	r4, [r10, #4]!
	add	r3, r3, #1
	cmp	r3, r7
	str	r4, [lr, #4]!
	ldr	r4, [ip, #4]!
	str	r4, [r0, #4]!
	ldr	r4, [r1, #4]!
	str	r4, [r2, #4]!
	bne	.L1249
	ldr	r4, [fp, #-52]
.L1250:
	ldrb	r3, [r9, #1333]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1275
	ldrb	r1, [r8, #1230]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L1251
	add	r0, r4, #62464
	ldr	r9, .L1276+4
	add	r0, r0, #128
.L1252:
	and	r3, r1, #3
	add	r1, r1, #1
	cmp	r1, #24
	ldr	r3, [r9, r3, asl #2]
	bic	r2, r3, #16711680
	ubfx	ip, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, ip, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [r0, #4]!
	bne	.L1252
	add	r8, r4, #62464
	mov	r7, #0
	add	r8, r8, #228
.L1253:
	add	r3, r7, #1
	and	r2, r7, #14
	and	r3, r3, #15
	add	r7, r7, #2
	add	r2, r9, r2, lsl #2
	cmp	r7, #32
	add	r3, r9, r3, lsl #2
	ldr	r2, [r2, #16]
	ldr	r1, [r3, #16]
	ubfx	r3, r2, #8, #8
	mov	r0, r2, lsr #24
	uxtb	r10, r2
	uxtb	lr, r1
	mov	ip, r1, lsr #16
	orr	r3, r3, r0, asl #8
	mov	r2, r2, lsr #8
	mov	lr, lr, asl #16
	and	r0, r1, #-16777216
	orr	ip, lr, ip, asl #24
	ubfx	r1, r1, #8, #8
	orr	ip, ip, r10
	and	r2, r2, #65280
	orr	r3, r3, r0
	orr	r2, ip, r2
	orr	r3, r3, r1, asl #16
	stmia	r8, {r2, r3}
	add	r8, r8, #8
	bne	.L1253
.L1258:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	beq	.L1255
	add	r9, r4, #63488
	add	r7, r4, #26624
	add	r7, r7, #172
	mov	r8, #0
	mov	r4, r9
	add	r9, r9, #80
	add	r4, r4, #144
.L1261:
	ldr	r2, [r7]
	mov	r1, #0
	ldr	r0, [r5, #2344]
	add	r8, r8, #1
	bl	FSP_GetStoreType
	adds	r0, r0, #0
	movne	r0, #1
	str	r0, [r9, #4]!
	ldr	r3, [r7], #4
	str	r3, [r4, #4]!
	ldr	r3, [r6, #2412]
	cmp	r3, r8
	bhi	.L1261
.L1255:
	mov	r0, #0
.L1271:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1275:
	ldrb	r1, [r8, #1230]	@ zero_extendqisi2
.L1251:
	cmp	r1, #1
	add	ip, r4, #62464
	mov	r0, #0
	add	ip, ip, #128
	beq	.L1256
.L1259:
	add	r3, r0, #3888
	add	r0, r0, #1
	add	r3, r3, #2
	cmp	r0, #24
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #8]
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1259
	add	r9, r4, #62464
	mov	r10, #1
	add	r9, r9, #228
	mov	r8, #0
.L1260:
	mov	r2, r8, lsr #3
	mov	r3, r8, asl #1
	and	r1, r10, #15
	and	r0, r3, #14
	mov	r3, r2, asl #4
	add	r8, r8, #1
	add	r2, r3, r1
	add	r3, r3, r0
	add	r2, r2, #3904
	add	r3, r3, #3904
	add	r2, r2, #10
	add	r3, r3, #10
	cmp	r8, #16
	add	r10, r10, #2
	add	r2, r4, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r1, [r2, #8]
	ldr	r3, [r3, #8]
	ubfx	r7, r1, #8, #8
	and	r0, r1, #-16777216
	mov	r2, r1, lsr #16
	uxtb	r1, r1
	mov	ip, r3, lsr #24
	uxtb	lr, r3
	mov	r2, r2, asl #24
	mov	ip, ip, asl #8
	orr	r2, r2, r1, asl #16
	orr	ip, ip, r7, asl #16
	mov	r1, r3, lsr #8
	orr	r2, r2, lr
	and	r1, r1, #65280
	ubfx	r3, r3, #8, #8
	orr	r0, ip, r0
	orr	r2, r2, r1
	orr	r3, r0, r3
	stmia	r9, {r2, r3}
	add	r9, r9, #8
	bne	.L1260
	b	.L1258
.L1256:
	add	r3, r0, #4864
	add	r0, r0, #1
	add	r3, r3, #30
	cmp	r0, #24
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	bic	r2, r3, #16711680
	ubfx	r1, r3, #8, #8
	bic	r2, r2, #65280
	mov	r3, r3, lsr #8
	orr	r2, r2, r1, asl #16
	and	r3, r3, #65280
	orr	r3, r2, r3
	str	r3, [ip, #4]!
	bne	.L1256
	add	r9, r4, #62464
	mov	r10, #1
	add	r9, r9, #228
	mov	r8, #0
.L1257:
	mov	r2, r8, lsr #3
	mov	r3, r8, asl #1
	and	r1, r10, #15
	and	r0, r3, #14
	mov	r3, r2, asl #4
	add	r8, r8, #1
	add	r2, r3, r1
	add	r3, r3, r0
	add	r2, r2, #4864
	add	r3, r3, #4864
	add	r2, r2, #54
	add	r3, r3, #54
	cmp	r8, #16
	add	r10, r10, #2
	add	r2, r4, r2, lsl #2
	add	r3, r4, r3, lsl #2
	ldr	r1, [r2, #4]
	ldr	r3, [r3, #4]
	ubfx	r7, r1, #8, #8
	and	r0, r1, #-16777216
	mov	r2, r1, lsr #16
	uxtb	r1, r1
	mov	ip, r3, lsr #24
	uxtb	lr, r3
	mov	r2, r2, asl #24
	mov	ip, ip, asl #8
	orr	r2, r2, r1, asl #16
	orr	ip, ip, r7, asl #16
	mov	r1, r3, lsr #8
	orr	r2, r2, lr
	and	r1, r1, #65280
	ubfx	r3, r3, #8, #8
	orr	r0, ip, r0
	orr	r2, r2, r1
	orr	r3, r0, r3
	stmia	r9, {r2, r3}
	add	r9, r9, #8
	bne	.L1257
	b	.L1258
.L1244:
	ldr	r1, .L1276+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1271
.L1274:
	ldr	r3, [r10, #3656]
	ldr	r1, .L1276+12
	ldr	r2, [r3, #648]
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1271
.L1277:
	.align	2
.L1276:
	.word	.LC44
	.word	.LANCHOR1
	.word	.LC46
	.word	.LC45
	UNWIND(.fnend)
	.size	WritePicMsg, .-WritePicMsg
	.align	2
	.global	UpdatePicQpInf
	.type	UpdatePicQpInf, %function
UpdatePicQpInf:
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
	ldr	r2, [r1, #24]
	ldr	r3, [r1, #28]
	cmp	r2, r0
	movlt	r2, r0
	cmp	r3, r0
	str	r2, [r1, #24]
	movge	r3, r0
	str	r3, [r1, #28]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	UpdatePicQpInf, .-UpdatePicQpInf
	.align	2
	.global	WriteSliceMsg
	.type	WriteSliceMsg, %function
WriteSliceMsg:
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
	add	r7, r0, #61440
	add	lr, r0, #12288
	movw	r1, #4060
	ldr	r3, [r7, #2268]
	mov	r4, r0
	ldr	ip, [r7, #2264]
	mov	r2, r3
	str	r3, [fp, #-48]
	mul	r1, r1, r2
	add	r3, r3, #1
	str	r3, [r7, #2268]
	ldr	r3, [lr, #1284]
	add	r6, ip, r1
	sub	r3, r3, #1
	cmp	r2, r3
	addcc	r3, r1, #4048
	addcc	r3, r3, #12
	movcs	r3, #0
	addcc	r3, ip, r3
	str	r3, [r6, #4056]
	ldr	r2, [r0, #368]
	ldrb	r0, [r2]	@ zero_extendqisi2
	ldr	r3, [r2, #68]
	cmp	r0, #1
	cmpls	r0, r3
	bcs	.L1282
	add	r5, r0, #3
	add	r5, r6, r5, lsl #2
.L1283:
	mov	r3, r0, asl #5
	sub	r3, r3, r0, asl #2
	add	r0, r0, #1
	add	r2, r2, r3
	ldr	r2, [r2, #24]
	str	r2, [r5, #4]!
	ldr	r2, [r4, #368]
	add	r2, r2, r3
	ldr	r2, [r2, #20]
	str	r2, [r5, #-8]
	ldr	r2, [r4, #368]
	add	r3, r2, r3
	ldr	r3, [r3, #28]
	str	r3, [r5, #8]
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #68]
	cmp	r3, r0
	movhi	r8, #1
	movls	r8, #0
	cmp	r0, #1
	movhi	r8, #0
	cmp	r8, #0
	bne	.L1283
.L1282:
	cmp	r3, #1
	bhi	.L1288
	add	r3, r3, #3
	add	r0, r6, #20
	mov	r2, #0
	add	r3, r6, r3, lsl #2
.L1287:
	str	r2, [r3, #4]!
	cmp	r3, r0
	str	r2, [r3, #-8]
	str	r2, [r3, #8]
	bne	.L1287
.L1288:
	add	r9, r4, #57344
	add	r8, r4, #16384
	add	r5, r4, #20480
	ldrb	r3, [r9, #3017]	@ zero_extendqisi2
	strb	r3, [r6, #1]
	ldr	r3, [r8, #1260]
	ldr	r0, [r5, #1816]
	add	r3, r3, #26
	add	r3, r3, r0
	str	r3, [r6, #32]
	ldr	r2, [r5, #1812]
	str	r2, [r6, #36]
	ldr	r2, [r5, #264]
	str	r2, [r6, #40]
	ldr	r2, [r5, #260]
	str	r2, [r6, #44]
	ldrb	r2, [r5, #208]	@ zero_extendqisi2
	strb	r2, [ip, r1]
	ldr	r2, [r5, #256]
	str	r2, [r6, #48]
	ldrb	r2, [r5, #214]	@ zero_extendqisi2
	strb	r2, [r6, #2]
	ldrb	r2, [lr, #1328]	@ zero_extendqisi2
	strb	r2, [r6, #3]
	ldr	r2, [r5, #248]
	str	r2, [r6, #52]
	ldr	r2, [r5, #252]
	str	r2, [r6, #56]
	ldrb	r2, [r5, #208]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L1387
	cmp	r2, #0
	ldreqb	r2, [r8, #1214]	@ zero_extendqisi2
	movne	r2, #0
	strb	r2, [r6, #4]
.L1289:
	ldr	r2, [r8, #1264]
	str	r2, [r6, #60]
	ldr	r2, [r8, #1268]
	str	r2, [r6, #64]
	ldr	r2, [r5, #1824]
	str	r2, [r6, #68]
	ldr	r2, [r5, #1828]
	str	r2, [r6, #72]
	ldr	r2, [r5, #1820]
	str	r2, [r6, #76]
	ldrb	r2, [r5, #209]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1291
	ldr	r10, [r9, #3656]
	ldr	r2, [fp, #-48]
	ldr	r1, [r7, #2268]
	ldr	r0, [r10, #692]
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	str	r0, [r10, #728]
.L1292:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ldr	r3, [r9, #3656]
	bne	.L1294
	ldr	r2, [r6, #32]
	str	r2, [r3, #720]
	ldr	r3, [r9, #3656]
	ldr	r2, [r6, #32]
	str	r2, [r3, #724]
.L1295:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1333
	ldr	ip, [r5, #248]
	cmp	ip, #0
	beq	.L1336
	add	r3, r4, #24576
	ldr	r3, [r3, #2548]
	ldr	r1, [r3, #36]
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r2, r4, #26880
	movne	r3, #0
	addne	r2, r2, #244
	bne	.L1301
	b	.L1299
.L1303:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #36]
	ldrb	r0, [r1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1299
.L1301:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1303
	mov	r3, #0
	str	r3, [fp, #-52]
.L1298:
	ldr	ip, [r5, #252]
	cmp	ip, #0
	beq	.L1337
	add	r3, r4, #24576
	ldr	r3, [r3, #2680]
	ldr	r1, [r3, #36]
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #0
	addne	r2, r4, #27136
	movne	r3, #0
	addne	r2, r2, #120
	bne	.L1307
	b	.L1305
.L1309:
	ldr	r1, [r2, #4]!
	ldr	r1, [r1, #36]
	ldrb	r0, [r1]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1305
.L1307:
	add	r3, r3, #1
	cmp	r3, ip
	bne	.L1309
	mov	r3, #0
	str	r3, [fp, #-56]
.L1304:
	ldrb	r2, [r9, #3011]	@ zero_extendqisi2
	ldr	r3, [r5, #248]
	cmp	r2, #0
	beq	.L1310
	cmp	r3, #0
	beq	.L1325
	add	r9, r4, #26880
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-60]
	str	r4, [fp, #-64]
	mov	r6, r5
	add	r9, r9, #244
	ldr	r4, [fp, #-52]
	mov	r5, r3
	b	.L1324
.L1322:
	strb	r1, [r10, #1630]
	ldr	r1, [r9]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1631]
	ldr	r1, [r9]
	ldr	r1, [r1, #12]
	str	r1, [r10, #1656]
.L1323:
	ldr	r1, [r6, #248]
	add	r5, r5, #1
	add	r9, r9, #4
	add	r10, r10, #36
	cmp	r1, r5
	bls	.L1388
.L1324:
	ldr	r1, [r9]
	ldr	r0, [r7, #2344]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #648]
	bl	FSP_GetLogicFs
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #684]
	str	r1, [r10, #1636]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1625]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1321
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1321:
	str	r0, [r10, #1640]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #688]
	str	r1, [r10, #1644]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #664]
	str	r1, [r10, #1632]
	ldr	r1, [r9]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #1624]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #696]	@ zero_extendqisi2
	strb	r1, [r10, #1626]
	ldr	r1, [r9]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1322
	strb	r1, [r10, #1628]
	ldr	r1, [r9]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1629]
	ldr	r1, [r9]
	ldr	r1, [r1, #12]
	str	r1, [r10, #1652]
	b	.L1323
.L1388:
	mov	r5, r6
	ldr	r4, [fp, #-64]
	ldr	r6, [fp, #-60]
.L1325:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1389
.L1313:
	add	r2, r4, #26880
	add	r3, r6, #3920
	add	r0, r6, #4048
	add	r2, r2, #112
	add	r3, r3, #4
	add	r0, r0, #4
.L1330:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L1330
	ldrb	r3, [r8, #1214]	@ zero_extendqisi2
	cmp	r3, #0
	str	r3, [r7, #1380]
	ldr	r3, [r8, #1256]
	str	r3, [r7, #1384]
	beq	.L1331
	ldrb	r2, [r5, #208]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1332
.L1331:
	cmp	r3, #1
	beq	.L1390
.L1333:
	ldr	r3, [fp, #-48]
	mov	r2, #0
	ldr	r1, [r4, #368]
	add	r3, r3, #15424
	add	r3, r3, #40
	str	r1, [r4, r3, asl #2]
	str	r2, [r4, #368]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1294:
	ldr	r1, [r6, #32]
	ldr	r0, [r3, #720]
	ldr	r2, [r3, #724]
	cmp	r0, r1
	movlt	r0, r1
	cmp	r2, r1
	str	r0, [r3, #720]
	movge	r2, r1
	str	r2, [r3, #724]
	b	.L1295
.L1291:
	ldr	r10, [r9, #3656]
	ldrb	r2, [r5, #210]	@ zero_extendqisi2
	ldr	r1, [r7, #2268]
	ldr	r0, [r10, #692]
	cmp	r2, #0
	ldr	r2, [fp, #-48]
	mla	r0, r0, r2, r3
	bne	.L1293
	bl	__aeabi_uidiv
	str	r0, [r10, #768]
	b	.L1292
.L1293:
	bl	__aeabi_uidiv
	str	r0, [r10, #808]
	b	.L1292
.L1299:
	ldr	r1, [r1, #648]
	ldr	r0, [r7, #2344]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	moveq	r2, #7104
	beq	.L1383
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-52]
	b	.L1298
.L1390:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1333
.L1332:
	ldr	r3, [r5, #268]
	add	r9, r4, #20736
	add	lr, r4, #21504
	add	r7, r4, #20992
	add	r0, r4, #21760
	mov	r8, r9
	str	r3, [r6, #80]
	mov	ip, lr
	ldr	r10, [r5, #272]
	add	r9, r9, #16
	add	r8, r8, #144
	add	r7, r7, #16
	add	lr, lr, #16
	add	ip, ip, #144
	add	r0, r0, #16
	mov	r1, r6
	mov	r3, r6
	mov	r2, #0
	str	r6, [fp, #-52]
	str	r10, [r1, #84]!
.L1334:
	ldr	r10, [r9, #4]!
	add	r2, r2, #1
	add	r3, r3, #4
	str	r10, [r1, #4]!
	ldr	r10, [r8, #4]!
	str	r10, [r3, #212]
	ldr	r10, [r7, #4]!
	str	r10, [r3, #340]
	ldr	r10, [lr, #4]!
	str	r10, [r3, #852]
	ldr	r10, [ip, #4]!
	str	r10, [r3, #980]
	ldr	r10, [r0, #4]!
	str	r10, [r3, #1108]
	ldr	r10, [r5, #260]
	cmp	r10, r2
	bcs	.L1334
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1333
	add	lr, r4, #21248
	add	r1, r4, #22016
	add	r7, r4, #20992
	add	r0, r4, #21760
	ldr	r8, [fp, #-52]
	mov	ip, lr
	mov	r2, r1
	add	r6, r6, #468
	add	r7, r7, #144
	add	lr, lr, #16
	add	ip, ip, #144
	add	r0, r0, #144
	add	r1, r1, #16
	add	r2, r2, #144
	mov	r3, #0
.L1335:
	ldr	r9, [r7, #4]!
	add	r3, r3, #1
	add	r8, r8, #4
	str	r9, [r6, #4]!
	ldr	r9, [lr, #4]!
	str	r9, [r8, #596]
	ldr	r9, [ip, #4]!
	str	r9, [r8, #724]
	ldr	r9, [r0, #4]!
	str	r9, [r8, #1236]
	ldr	r9, [r1, #4]!
	str	r9, [r8, #1364]
	ldr	r9, [r2, #4]!
	str	r9, [r8, #1492]
	ldr	r9, [r5, #264]
	cmp	r9, r3
	bcs	.L1335
	b	.L1333
.L1310:
	cmp	r3, #0
	beq	.L1318
	add	r3, r4, #26880
	str	r4, [fp, #-64]
	add	r3, r3, #244
	ldr	r4, [fp, #-52]
	mov	r10, r6
	str	r6, [fp, #-60]
	mov	r9, r3
	mov	r6, r5
	mov	r5, r2
.L1317:
	ldr	r1, [r9]
	ldr	r0, [r7, #2344]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #648]
	bl	FSP_GetLogicFs
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #684]
	str	r1, [r10, #1636]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1625]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1316
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1316:
	str	r0, [r10, #1640]
	mov	r3, #0
	ldr	r1, [r9]
	add	r5, r5, #1
	add	r10, r10, #36
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #688]
	str	r1, [r10, #1608]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #664]
	str	r1, [r10, #1596]
	ldr	r1, [r9]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #1591]
	ldr	r1, [r9]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #1590]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #708]
	str	r1, [r10, #1612]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #748]
	str	r1, [r10, #1616]
	ldr	r1, [r9], #4
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #788]
	strb	r3, [r10, #1588]
	str	r1, [r10, #1620]
	ldr	r1, [r6, #248]
	cmp	r1, r5
	bhi	.L1317
	mov	r5, r6
	ldr	r4, [fp, #-64]
	ldr	r6, [fp, #-60]
.L1318:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1313
	ldr	r3, [r5, #252]
	cmp	r3, #0
	beq	.L1313
	add	r3, r4, #27136
	str	r4, [fp, #-60]
	add	r3, r3, #120
	ldr	r4, [fp, #-56]
	mov	r9, #0
	mov	r10, r6
	str	r6, [fp, #-52]
	mov	r6, r5
	mov	r5, r9
	mov	r9, r3
.L1320:
	ldr	r1, [r9]
	ldr	r0, [r7, #2344]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #648]
	bl	FSP_GetLogicFs
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #684]
	str	r1, [r10, #2788]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2777]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1319
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1319:
	str	r0, [r10, #1640]
	mov	r3, #0
	ldr	r1, [r9]
	add	r5, r5, #1
	add	r10, r10, #36
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #688]
	str	r1, [r10, #2760]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #664]
	str	r1, [r10, #2748]
	ldr	r1, [r9]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2743]
	ldr	r1, [r9]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #2742]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #708]
	str	r1, [r10, #2764]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #748]
	str	r1, [r10, #2768]
	ldr	r1, [r9], #4
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #788]
	strb	r3, [r10, #2740]
	str	r1, [r10, #2772]
	ldr	r1, [r6, #252]
	cmp	r1, r5
	bhi	.L1320
.L1382:
	mov	r5, r6
	ldr	r4, [fp, #-60]
	ldr	r6, [fp, #-52]
	b	.L1313
.L1305:
	ldr	r1, [r1, #648]
	ldr	r0, [r7, #2344]
	bl	FSP_GetLogicFs
	subs	r3, r0, #0
	beq	.L1391
	ldr	r3, [r3, #28]
	ldr	r3, [r3, #4]
	str	r3, [fp, #-56]
	b	.L1304
.L1387:
	ldr	r2, [r8, #1256]
	strb	r2, [r6, #4]
	b	.L1289
.L1389:
	ldr	r3, [r5, #252]
	cmp	r3, #0
	beq	.L1313
	add	r9, r4, #27136
	mov	r3, #0
	mov	r10, r6
	str	r6, [fp, #-52]
	str	r4, [fp, #-60]
	mov	r6, r5
	add	r9, r9, #120
	ldr	r4, [fp, #-56]
	mov	r5, r3
	b	.L1329
.L1327:
	strb	r1, [r10, #2782]
	ldr	r1, [r9]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2783]
	ldr	r1, [r9]
	ldr	r1, [r1, #12]
	str	r1, [r10, #2808]
.L1328:
	ldr	r1, [r6, #252]
	add	r5, r5, #1
	add	r9, r9, #4
	add	r10, r10, #36
	cmp	r1, r5
	bls	.L1382
.L1329:
	ldr	r1, [r9]
	ldr	r0, [r7, #2344]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #648]
	bl	FSP_GetLogicFs
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #684]
	str	r1, [r10, #2788]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2777]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	moveq	r0, r4
	beq	.L1326
	cmp	r0, #0
	ldrne	r1, [r0, #28]
	ldrne	r0, [r1, #4]
.L1326:
	str	r0, [r10, #2792]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #688]
	str	r1, [r10, #2796]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldr	r1, [r1, #664]
	str	r1, [r10, #2784]
	ldr	r1, [r9]
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r1, [r10, #2776]
	ldr	r1, [r9]
	ldr	r1, [r1, #36]
	ldrb	r1, [r1, #696]	@ zero_extendqisi2
	strb	r1, [r10, #2778]
	ldr	r1, [r9]
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L1327
	strb	r1, [r10, #2780]
	ldr	r1, [r9]
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	strb	r1, [r10, #2781]
	ldr	r1, [r9]
	ldr	r1, [r1, #12]
	str	r1, [r10, #2804]
	b	.L1328
.L1391:
	movw	r2, #7125
.L1383:
	ldr	r1, .L1392
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L1336:
	str	ip, [fp, #-52]
	b	.L1298
.L1337:
	str	ip, [fp, #-56]
	b	.L1304
.L1393:
	.align	2
.L1392:
	.word	.LC47
	UNWIND(.fnend)
	.size	WriteSliceMsg, .-WriteSliceMsg
	.align	2
	.global	StopPicNum
	.type	StopPicNum, %function
StopPicNum:
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
	.size	StopPicNum, .-StopPicNum
	.align	2
	.global	H264_GetPicStreamSize
	.type	H264_GetPicStreamSize, %function
H264_GetPicStreamSize:
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
	add	r0, r0, #61440
	ldr	r2, [r0, #2024]
	cmp	r2, #0
	beq	.L1398
	mov	r0, #0
.L1397:
	ldr	r3, [r2, #8]
	ldr	r1, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r1
	add	r3, r3, #7
	cmp	r2, #0
	add	r0, r0, r3, lsr #3
	bne	.L1397
	ldmfd	sp, {fp, sp, pc}
.L1398:
	mov	r0, r2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	H264_GetPicStreamSize, .-H264_GetPicStreamSize
	.align	2
	.global	SliceCheck
	.type	SliceCheck, %function
SliceCheck:
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
	ldr	r1, .L1411
	add	r4, r0, #20480
	add	r6, r0, #61440
	mov	r5, r0
	bl	ue_v
	str	r0, [r4, #256]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L1409
	cmp	r0, #262144
	bcs	.L1410
	add	r2, r5, #12288
	ldr	r1, [r2, #1276]
	ldr	r3, [r2, #1280]
	mul	r3, r3, r1
	sub	r3, r3, #1
	cmp	r0, r3
	bhi	.L1409
	mov	r0, r5
	ldr	r1, .L1411+4
	bl	ue_v
	ldr	r1, .L1411+8
	mov	r2, r0
	mov	r5, r0
	mov	r0, #19
	bl	dprint_vfmw
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L1409
	cmp	r5, #9
	bhi	.L1405
	mov	r1, #1
	movw	r0, #297
	mov	r2, r1, asl r5
	and	r0, r0, r2
	cmp	r0, #0
	bne	.L1406
	ands	r3, r2, #660
	bne	.L1407
	tst	r2, #66
	beq	.L1405
	strb	r1, [r4, #208]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1406:
	strb	r3, [r4, #208]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1405:
	mov	r2, r5
	ldr	r1, .L1411+12
	mov	r0, #1
	bl	dprint_vfmw
.L1409:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1407:
	mov	r3, #2
	strb	r3, [r4, #208]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1410:
	ldr	r1, .L1411+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1412:
	.align	2
.L1411:
	.word	.LC48
	.word	.LC50
	.word	.LC51
	.word	.LC52
	.word	.LC49
	UNWIND(.fnend)
	.size	SliceCheck, .-SliceCheck
	.align	2
	.global	PPSSPSCheck
	.type	PPSSPSCheck, %function
PPSSPSCheck:
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
	add	r5, r0, #20480
	mov	r4, r0
	add	r4, r4, #12288
	ldr	r1, .L1419
	ldr	r2, [r5, #216]
	mov	r0, #19
	bl	dprint_vfmw
	ldr	r1, [r4, #1304]
	ldr	r2, [r5, #216]
	mov	r3, #2208
	mla	r3, r3, r2, r1
	ldrb	r1, [r3, #19]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L1417
	ldr	r2, [r3, #28]
	mov	r3, #4000
	ldr	r1, [r4, #1300]
	mla	r3, r3, r2, r1
	ldrb	r3, [r3, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1418
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1417:
	ldr	r1, .L1419+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1418:
	ldr	r1, .L1419+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1420:
	.align	2
.L1419:
	.word	.LC53
	.word	.LC54
	.word	.LC55
	UNWIND(.fnend)
	.size	PPSSPSCheck, .-PPSSPSCheck
	.align	2
	.global	PPSSPSCheckTmpId
	.type	PPSSPSCheckTmpId, %function
PPSSPSCheckTmpId:
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
	mov	r2, r1
	mov	r5, r1
	mov	r4, r0
	ldr	r1, .L1429
	mov	r0, #19
	bl	dprint_vfmw
	add	r0, r4, #12288
	mov	r3, #2208
	ldr	r2, [r0, #1304]
	mla	r3, r3, r5, r2
	ldrb	r2, [r3, #19]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L1426
	ldr	r1, [r0, #1288]
	ldr	r2, [r3, #28]
	sub	r3, r1, #1
	cmp	r2, r3
	bhi	.L1427
	ldr	r1, [r0, #1300]
	mov	r3, #4000
	mla	r3, r3, r2, r1
	ldrb	r3, [r3, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1428
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1426:
	mov	r2, r5
	ldr	r1, .L1429+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1427:
	ldr	r1, .L1429+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1428:
	ldr	r1, .L1429+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L1430:
	.align	2
.L1429:
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC59
	UNWIND(.fnend)
	.size	PPSSPSCheckTmpId, .-PPSSPSCheckTmpId
	.align	2
	.global	IsNewPic
	.type	IsNewPic, %function
IsNewPic:
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
	add	r3, r0, #20480
	add	lr, r0, #12288
	ldr	ip, [r3, #1852]
	ldr	r1, [lr, #1344]
	ldr	r2, [r3, #1856]
	ldr	r4, [r3, #216]
	ldr	r6, [r3, #1864]
	cmp	r2, r4
	cmpeq	ip, r1
	ldr	r5, [r3, #224]
	ldrb	r4, [r3, #1848]	@ zero_extendqisi2
	ldrb	ip, [r3, #209]	@ zero_extendqisi2
	movne	r1, #1
	moveq	r1, #0
	cmp	r6, r5
	moveq	r2, r1
	orrne	r2, r1, #1
	cmp	r4, ip
	orrne	r2, r2, #1
	cmp	r4, #0
	cmpne	ip, #0
	beq	.L1433
	ldrb	ip, [r3, #1849]	@ zero_extendqisi2
	ldrb	r1, [r3, #210]	@ zero_extendqisi2
	cmp	ip, r1
	orrne	r2, r2, #1
.L1433:
	ldr	r1, [r3, #1860]
	ldr	ip, [r3, #236]
	cmp	r1, ip
	moveq	r1, #0
	beq	.L1434
	cmp	ip, #0
	cmpne	r1, #0
	moveq	r1, #1
	movne	r1, #0
.L1434:
	ldrb	ip, [r3, #1850]	@ zero_extendqisi2
	ldrb	r4, [r3, #211]	@ zero_extendqisi2
	cmp	ip, r4
	orrne	r2, r2, #1
	cmp	r4, #5
	cmpeq	ip, #5
	orr	r2, r2, r1
	beq	.L1442
.L1435:
	ldr	r1, [lr, #3508]
	cmp	r1, #0
	bne	.L1436
	add	r0, r0, #16384
	ldr	r1, [r3, #1872]
	ldr	ip, [r3, #1876]
	ldr	lr, [r0, #3424]
	ldr	r0, [r0, #3420]
	cmp	r1, r0
	cmpeq	ip, lr
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
.L1437:
	ldr	r4, [r3, #256]
	mov	r0, #19
	ldr	r1, .L1443
	cmp	r4, #0
	movne	r4, r2
	orreq	r4, r2, #1
	mov	r2, r4
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L1436:
	cmp	r1, #1
	bne	.L1437
	add	r0, r0, #16384
	ldr	r1, [r3, #1880]
	ldr	ip, [r3, #1884]
	ldr	lr, [r0, #3472]
	ldr	r0, [r0, #3468]
	cmp	r1, r0
	cmpeq	ip, lr
	movne	r1, #1
	moveq	r1, #0
	orr	r2, r2, r1
	b	.L1437
.L1442:
	ldr	ip, [r3, #1868]
	ldr	r1, [r3, #244]
	cmp	ip, r1
	orrne	r2, r2, #1
	b	.L1435
.L1444:
	.align	2
.L1443:
	.word	.LC60
	UNWIND(.fnend)
	.size	IsNewPic, .-IsNewPic
	.align	2
	.global	ref_pic_list_reordering
	.type	ref_pic_list_reordering, %function
ref_pic_list_reordering:
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
	add	r5, r0, #20480
	add	r3, r0, #12288
	mov	lr, #2208
	mov	ip, #4000
	ldr	r2, [r3, #1304]
	add	r8, r0, #16384
	ldr	r1, [r5, #216]
	mov	r4, r0
	ldr	r3, [r3, #1300]
	mov	r0, #0
	mov	r7, #1
	mla	r2, lr, r1, r2
	ldr	r2, [r2, #28]
	strb	r0, [r8, #3512]
	strb	r0, [r8, #3513]
	mla	r3, ip, r2, r3
	ldrb	r1, [r5, #209]	@ zero_extendqisi2
	cmp	r1, r0
	ldr	r3, [r3, #2196]
	addne	r3, r3, #5
	addeq	r3, r3, #4
	mov	r7, r7, asl r3
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	cmp	r3, #1
	addhi	r6, r4, #61440
	bls	.L1499
.L1498:
	ldr	r3, [r6, #2284]
.L1464:
	adds	r3, r3, #0
	movne	r3, #1
	rsb	r0, r3, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1499:
	ldr	r1, .L1504
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r8, #3512]
	cmp	r0, #0
	beq	.L1497
	ldr	r3, [r5, #260]
	cmn	r3, #2
	beq	.L1478
	add	r10, r4, #19712
	add	r6, r4, #61440
	add	r10, r10, #184
	mov	r9, #0
	b	.L1461
.L1456:
	cmp	r0, #2
	beq	.L1500
.L1459:
	ldr	r3, [r5, #260]
	add	r3, r3, #2
	cmp	r3, r9
	bls	.L1501
.L1461:
	ldr	r1, .L1504+4
	mov	r0, r4
	bl	ue_v
	add	r9, r9, #1
	cmp	r0, #3
	str	r0, [r10, #4]!
	ldr	r3, [r6, #2284]
	bhi	.L1452
	cmp	r3, #0
	bne	.L1452
	cmp	r0, #3
	beq	.L1455
	cmp	r0, #1
	bhi	.L1456
	ldr	r1, .L1504+8
	mov	r0, r4
	bl	ue_v
	cmp	r7, r0
	str	r0, [r10, #264]
	ldr	r3, [r6, #2284]
	bls	.L1458
	cmp	r3, #0
	beq	.L1459
.L1458:
	mov	r2, r0
	ldr	r1, .L1504+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1500:
	ldr	r1, .L1504+16
	mov	r0, r4
	bl	ue_v
	str	r0, [r10, #528]
	b	.L1459
.L1497:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	add	r6, r4, #61440
.L1448:
	cmp	r3, #1
	bne	.L1498
	ldr	r1, .L1504+20
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r8, #3513]
	cmp	r0, #0
	beq	.L1498
	ldr	r3, [r5, #264]
	cmn	r3, #2
	beq	.L1498
	add	r9, r4, #19968
	mov	r8, #0
	add	r9, r9, #60
	b	.L1476
.L1475:
	add	r8, r8, #1
	cmp	r8, r3
	bcs	.L1498
.L1476:
	ldr	r1, .L1504+24
	mov	r0, r4
	bl	ue_v
	cmp	r0, #3
	str	r0, [r9, #4]!
	ldr	r3, [r6, #2284]
	bhi	.L1468
	cmp	r3, #0
	bne	.L1468
	cmp	r0, #3
	beq	.L1464
	cmp	r0, #1
	bls	.L1502
	cmp	r0, #2
	beq	.L1503
	ldr	r3, [r5, #264]
	add	r3, r3, #2
	cmp	r3, r8
	bne	.L1475
.L1477:
	ldr	r1, .L1504+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1502:
	ldr	r1, .L1504+32
	mov	r0, r4
	bl	ue_v
	cmp	r7, r0
	str	r0, [r9, #264]
	ldr	r3, [r6, #2284]
	bls	.L1472
	cmp	r3, #0
	bne	.L1472
.L1473:
	ldr	r2, [r5, #264]
	add	r3, r2, #2
	cmp	r3, r8
	bne	.L1475
	add	r2, r2, #4992
	add	r2, r2, #18
	ldr	r2, [r4, r2, asl #2]
	cmp	r2, #3
	beq	.L1475
	b	.L1477
.L1503:
	ldr	r1, .L1504+36
	mov	r0, r4
	bl	ue_v
	str	r0, [r9, #524]
	b	.L1473
.L1455:
	ldrb	r3, [r5, #208]	@ zero_extendqisi2
	b	.L1448
.L1452:
	mov	r2, r0
	ldr	r1, .L1504+40
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1468:
	mov	r2, r0
	ldr	r1, .L1504+44
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1501:
	cmp	r9, r3
	bne	.L1455
.L1450:
	add	r3, r3, #4928
	add	r3, r3, #46
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #4]
	cmp	r3, #3
	beq	.L1497
	ldr	r1, .L1504+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1472:
	mov	r2, r0
	ldr	r1, .L1504+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1478:
	mov	r3, #0
	b	.L1450
.L1505:
	.align	2
.L1504:
	.word	.LC61
	.word	.LC62
	.word	.LC64
	.word	.LC65
	.word	.LC66
	.word	.LC68
	.word	.LC69
	.word	.LC74
	.word	.LC71
	.word	.LC73
	.word	.LC63
	.word	.LC70
	.word	.LC67
	.word	.LC72
	UNWIND(.fnend)
	.size	ref_pic_list_reordering, .-ref_pic_list_reordering
	.align	2
	.global	pred_weight_table
	.type	pred_weight_table, %function
pred_weight_table:
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
	add	r3, r0, #12288
	add	r6, r0, #20480
	mov	r10, #2208
	ldr	r2, [r3, #1304]
	mov	r7, #4000
	ldr	ip, [r6, #216]
	mov	r5, r0
	ldr	r3, [r3, #1300]
	mov	r4, #1
	ldr	r1, .L1536
	mla	r2, r10, ip, r2
	str	r2, [fp, #-48]
	ldr	r2, [r2, #28]
	mla	r7, r7, r2, r3
	bl	ue_v
	str	r0, [r6, #268]
	mov	r8, r4, asl r0
	ldr	r9, [r7, #40]
	cmp	r9, #0
	bne	.L1530
.L1507:
	cmp	r0, #7
	bhi	.L1510
	ldr	r3, [r6, #272]
	cmp	r3, #7
	bhi	.L1510
	add	r3, r5, #61440
	str	r3, [fp, #-52]
	ldr	r2, [r3, #2284]
	cmp	r2, #0
	addeq	r10, r5, #20736
	moveq	r4, r2
	addeq	r10, r10, #148
	beq	.L1518
	b	.L1509
.L1514:
	ldr	r2, [r7, #40]
	cmp	r2, #0
	bne	.L1531
.L1515:
	str	r2, [r10]
	str	r2, [r10, #768]
	str	r2, [r10, #128]
	str	r2, [r10, #896]
.L1517:
	ldr	r2, [r6, #260]
	add	r4, r4, #1
	add	r10, r10, #4
	cmp	r2, r4
	bcc	.L1532
.L1518:
	ldr	r1, .L1536+4
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	streq	r8, [r10, #-128]
	streq	r0, [r10, #640]
	beq	.L1514
	ldr	r1, .L1536+8
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+12
	str	r0, [r10, #-128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #640]
	ldr	r2, [r7, #40]
	cmp	r2, #0
	beq	.L1515
.L1531:
	ldr	r1, .L1536+16
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L1533
	str	r9, [r10]
	str	r0, [r10, #768]
	str	r9, [r10, #128]
	str	r0, [r10, #896]
	b	.L1517
.L1532:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #44]
	cmp	r3, #1
	beq	.L1519
.L1520:
	ldr	r3, [fp, #-52]
	ldr	r0, [r3, #2284]
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
.L1512:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1533:
	ldr	r1, .L1536+20
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+24
	str	r0, [r10]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+20
	str	r0, [r10, #768]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+24
	str	r0, [r10, #128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #896]
	b	.L1517
.L1530:
	ldr	r1, .L1536+28
	mov	r0, r5
	bl	ue_v
	mov	r3, r0
	ldr	r0, [r6, #268]
	mov	r9, r4, asl r3
	str	r3, [r6, #272]
	b	.L1507
.L1519:
	ldrb	r3, [r6, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1520
	add	r10, r5, #21248
	mov	r4, #0
	add	r10, r10, #20
	b	.L1526
.L1522:
	ldr	r3, [r7, #40]
	cmp	r3, #0
	bne	.L1534
.L1523:
	str	r3, [r10]
	str	r3, [r10, #768]
	str	r3, [r10, #128]
	str	r3, [r10, #896]
.L1525:
	ldr	r3, [r6, #264]
	add	r4, r4, #1
	add	r10, r10, #4
	cmp	r3, r4
	bcc	.L1520
.L1526:
	ldr	r1, .L1536+32
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	streq	r8, [r10, #-128]
	streq	r0, [r10, #640]
	beq	.L1522
	ldr	r1, .L1536+36
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+40
	str	r0, [r10, #-128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #640]
	ldr	r3, [r7, #40]
	cmp	r3, #0
	beq	.L1523
.L1534:
	ldr	r1, .L1536+44
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L1535
	str	r9, [r10]
	str	r0, [r10, #768]
	str	r9, [r10, #128]
	str	r0, [r10, #896]
	b	.L1525
.L1510:
	add	r5, r5, #61440
	ldr	r2, [r5, #2284]
.L1509:
	ldr	r1, .L1536+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1512
.L1535:
	ldr	r1, .L1536+52
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+56
	str	r0, [r10]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+52
	str	r0, [r10, #768]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1536+56
	str	r0, [r10, #128]
	mov	r0, r5
	bl	se_v
	str	r0, [r10, #896]
	b	.L1525
.L1537:
	.align	2
.L1536:
	.word	.LC75
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC76
	.word	.LC84
	.word	.LC85
	.word	.LC86
	.word	.LC87
	.word	.LC77
	.word	.LC88
	.word	.LC89
	UNWIND(.fnend)
	.size	pred_weight_table, .-pred_weight_table
	.align	2
	.global	DecMMCO
	.type	DecMMCO, %function
DecMMCO:
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
	mov	r9, r0
	moveq	r6, #100
	beq	.L1550
	add	r8, r0, #24576
	mov	r10, #0
	b	.L1541
.L1572:
	ldr	r1, .L1578
	mov	r0, r9
	bl	ue_v
	cmp	r4, #2
	beq	.L1570
.L1552:
	cmp	r4, #6
	orreq	r5, r5, #1
	cmp	r5, #0
	bne	.L1555
	cmp	r4, #4
	beq	.L1571
.L1556:
	cmp	r4, #6
	bhi	.L1548
.L1553:
	add	r3, r9, #61440
	ldr	r3, [r3, #2284]
	cmp	r3, #0
	bne	.L1548
	cmp	r4, #0
	beq	.L1558
.L1557:
	subs	r6, r6, #1
	beq	.L1559
.L1550:
	ldr	r1, .L1578+4
	mov	r0, r9
	bl	ue_v
	bic	r3, r0, #2
	sub	r5, r0, #3
	clz	r5, r5
	cmp	r3, #1
	mov	r4, r0
	mov	r5, r5, lsr #5
	beq	.L1572
	cmp	r4, #2
	bne	.L1552
.L1570:
	ldr	r1, .L1578+8
	mov	r0, r9
	bl	ue_v
	cmp	r5, #0
	beq	.L1553
.L1555:
	ldr	r1, .L1578+12
	mov	r0, r9
	bl	ue_v
	cmp	r4, #4
	bne	.L1556
.L1571:
	ldr	r1, .L1578+16
	mov	r0, r9
	bl	ue_v
	add	r3, r9, #61440
	ldr	r3, [r3, #2284]
	cmp	r3, #0
	beq	.L1557
.L1548:
	ldr	r1, .L1578+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1577:
	ldr	r1, .L1578
	mov	r0, r9
	bl	ue_v
	ldr	r2, [r4, #8]
	cmp	r2, #2
	str	r0, [r4, #12]
	beq	.L1573
.L1544:
	cmp	r2, #3
	cmpne	r2, #6
	beq	.L1574
.L1545:
	cmp	r2, #4
	beq	.L1575
.L1546:
	cmp	r2, #6
	bhi	.L1548
	add	r3, r9, #61440
	ldr	r3, [r3, #2284]
	cmp	r3, #0
	bne	.L1548
	cmp	r2, #0
	add	r10, r10, #1
	beq	.L1558
	cmp	r10, #100
	beq	.L1576
.L1541:
	ldr	r1, .L1578+4
	mov	r0, r9
	ldr	r5, [r8, #1804]
	bl	ue_v
	mov	r6, r10, asl #2
	mov	r7, r10, asl #4
	add	r4, r6, r7
	movw	r3, #2004
	mla	r4, r3, r5, r4
	add	r4, r9, r4
	add	r4, r4, #22272
	add	r4, r4, #96
	bic	r1, r0, #2
	str	r0, [r4, #8]
	cmp	r1, #1
	mov	r2, r0
	beq	.L1577
	cmp	r2, #2
	bne	.L1544
.L1573:
	ldr	r1, .L1578+8
	mov	r0, r9
	bl	ue_v
	add	r3, r6, r7
	movw	r2, #2004
	mla	r3, r2, r5, r3
	add	r3, r9, r3
	add	r2, r3, #22272
	str	r0, [r2, #112]
	ldr	r2, [r2, #104]
	cmp	r2, #3
	cmpne	r2, #6
	bne	.L1545
.L1574:
	ldr	r1, .L1578+12
	mov	r0, r9
	bl	ue_v
	add	r3, r6, r7
	movw	r2, #2004
	mla	r3, r2, r5, r3
	add	r3, r9, r3
	add	r2, r3, #22272
	str	r0, [r2, #116]
	ldr	r2, [r2, #104]
	cmp	r2, #4
	bne	.L1546
.L1575:
	ldr	r1, .L1578+16
	mov	r0, r9
	bl	ue_v
	add	r6, r6, r7
	movw	r7, #2004
	mla	r5, r7, r5, r6
	add	r5, r9, r5
	add	r3, r5, #22272
	add	r5, r3, #96
	ldr	r2, [r3, #104]
	str	r0, [r3, #120]
	b	.L1546
.L1558:
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1576:
	ldr	r1, .L1578+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1559:
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1579:
	.align	2
.L1578:
	.word	.LC92
	.word	.LC91
	.word	.LC93
	.word	.LC94
	.word	.LC95
	.word	.LC96
	.word	.LC90
	UNWIND(.fnend)
	.size	DecMMCO, .-DecMMCO
	.align	2
	.global	dec_ref_pic_marking
	.type	dec_ref_pic_marking, %function
dec_ref_pic_marking:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #20480
	add	r6, r0, #24576
	mov	r5, r0
	ldrb	r8, [r3, #213]	@ zero_extendqisi2
	ldr	r7, [r6, #1804]
	cmp	r8, #0
	beq	.L1581
	clz	r4, r7
	mov	r4, r4, lsr #5
	str	r4, [r6, #1804]
	ldrb	r3, [r3, #211]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1599
.L1582:
	ldr	r1, .L1604
	mov	r0, r5
	bl	u_1
	movw	r1, #2004
	mla	r4, r1, r4, r5
	ldr	r1, .L1604+4
	add	r4, r4, #22272
	add	r4, r4, #96
	mov	r3, r0
	uxtb	r2, r0
	strb	r3, [r4, #7]
	mov	r0, #16
	bl	dprint_vfmw
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1584
.L1588:
	mov	r8, #0
.L1596:
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1581:
	movw	r4, #2004
	mla	r4, r4, r7, r0
	add	r4, r4, #22272
	add	r4, r4, #96
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1600
	ldrb	r3, [r3, #211]	@ zero_extendqisi2
	mov	r4, r7
	cmp	r3, #5
	bne	.L1582
.L1599:
	ldr	r1, .L1604+8
	mov	r0, r5
	bl	u_1
	movw	r3, #2004
	mla	r4, r3, r4, r5
	ldr	r1, .L1604+12
	mov	r8, #0
	add	r4, r4, #22272
	strb	r0, [r4, #101]
	mov	r0, r5
	bl	u_1
	ldrb	r2, [r4, #101]	@ zero_extendqisi2
	ldr	r1, .L1604+16
	strb	r0, [r4, #102]
	mov	r0, #16
	bl	dprint_vfmw
	mov	r0, r8
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1600:
	ldrb	r3, [r3, #211]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1601
	ldr	r1, .L1604
	ldrb	r6, [r4, #7]	@ zero_extendqisi2
	bl	u_1
	cmp	r6, r0
	bne	.L1602
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1588
	mov	r1, r8
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	DecMMCO
.L1584:
	mov	r0, r5
	mov	r1, #1
	bl	DecMMCO
	cmn	r0, #1
	mov	r8, r0
	movne	r3, #1
	movne	r8, #0
	strneb	r3, [r4, #4]
	bne	.L1596
	mov	r3, #0
	ldr	r1, .L1604+20
	strb	r3, [r4, #4]
	mov	r0, #1
	str	r7, [r6, #1804]
	bl	dprint_vfmw
	b	.L1596
.L1601:
	ldr	r1, .L1604+8
	ldrb	r6, [r4, #5]	@ zero_extendqisi2
	bl	u_1
	cmp	r6, r0
	bne	.L1603
	mov	r0, r5
	ldr	r1, .L1604+12
	ldrb	r4, [r4, #6]	@ zero_extendqisi2
	bl	u_1
	cmp	r4, r0
	beq	.L1588
	ldr	r1, .L1604+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1596
.L1602:
	add	r5, r5, #61440
	ldr	r1, .L1604+28
	mov	r0, #1
	mvn	r8, #0
	bl	dprint_vfmw
	ldr	ip, [r5, #2288]
	ldr	r3, [r5, #2324]
	mov	r0, #1
	ldr	r2, [r5, #2308]
	ldr	r1, .L1604+32
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L1596
.L1603:
	ldr	r1, .L1604+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1596
.L1605:
	.align	2
.L1604:
	.word	.LC100
	.word	.LC101
	.word	.LC97
	.word	.LC98
	.word	.LC99
	.word	.LC102
	.word	.LC104
	.word	.LC105
	.word	.LC106
	.word	.LC103
	UNWIND(.fnend)
	.size	dec_ref_pic_marking, .-dec_ref_pic_marking
	.align	2
	.global	ProcessSliceHeaderFirstPart
	.type	ProcessSliceHeaderFirstPart, %function
ProcessSliceHeaderFirstPart:
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
	ldr	r1, .L1680
	add	r5, r0, #12288
	mov	r6, r0
	bl	ue_v
	ldr	r3, [r5, #1292]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r10, r0
	bhi	.L1607
	add	r9, r6, #61440
	ldr	r3, [r9, #2284]
	cmp	r3, #0
	bne	.L1607
	mov	r1, r0
	mov	r0, r6
	bl	PPSSPSCheckTmpId
	subs	r8, r0, #0
	bne	.L1671
	add	r4, r6, #20480
	mov	r7, #2208
	mov	r1, #4000
	str	r10, [r4, #216]
	ldr	r2, [r5, #1304]
	ldrb	r0, [r4, #211]	@ zero_extendqisi2
	ldr	r3, [r5, #1300]
	mla	r7, r7, r10, r2
	cmp	r0, #5
	ldr	r2, [r7, #28]
	mla	r5, r1, r2, r3
	beq	.L1611
	ldr	r3, [r5, #3244]
	cmp	r3, #0
	beq	.L1611
.L1612:
	ldr	r1, [r5, #2196]
	mov	r0, r6
	ldr	r2, .L1680+4
	add	r1, r1, #4
	bl	u_v
	str	r0, [r4, #224]
	ldr	r3, [r9, #2284]
	cmp	r3, #0
	bne	.L1669
	ldrb	r3, [r4, #211]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1672
.L1615:
	mov	r3, #0
	strb	r3, [r4, #209]
	strb	r3, [r4, #210]
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1673
	ldr	r2, [r5, #3248]
	ldr	r1, [r5, #3252]
	add	r3, r2, #1
	mla	r3, r1, r3, r3
.L1639:
	ldrb	r2, [r5, #19]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1622
	strb	r2, [r4, #212]
.L1624:
	ldr	r2, [r4, #256]
	cmp	r2, r3
	bcs	.L1674
.L1625:
	ldrb	r3, [r4, #211]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L1675
.L1627:
	add	r10, r6, #16384
	mov	r3, #0
	str	r3, [r10, #3420]
	str	r3, [r10, #3424]
	ldr	r3, [r5, #2200]
	cmp	r3, #0
	beq	.L1676
.L1631:
	mov	r3, #0
	str	r3, [r10, #3468]
	str	r3, [r10, #3472]
	ldr	r3, [r5, #2200]
	cmp	r3, #1
	beq	.L1677
.L1634:
	ldr	r3, [r9, #2284]
	cmp	r3, #0
	bne	.L1669
	ldrb	r3, [r7, #17]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1637
	ldr	r1, .L1680+8
	mov	r0, r6
	bl	ue_v
	cmp	r0, #0
	bne	.L1638
	ldr	r3, [r9, #2284]
	cmp	r3, #0
	bne	.L1638
.L1637:
	mov	r0, r6
	bl	IsNewPic
	uxtb	r0, r0
	strb	r0, [r4, #213]
	cmp	r0, #0
	bne	.L1651
	ldr	r2, [r4, #256]
	ldr	r3, [r4, #1888]
	cmp	r2, r3
	bls	.L1678
.L1651:
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1611:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1612
	ldr	r1, .L1680+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1651
.L1622:
	mov	r2, #1
	strb	r2, [r4, #212]
.L1642:
	ldr	r2, [r4, #256]
	cmp	r2, r3, lsr #1
	bcc	.L1625
	ldr	r1, .L1680+16
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1651
.L1638:
	ldr	r1, .L1680+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L1680+24
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1669
	mov	r3, #0
	ldr	r0, [r9, #2344]
	mov	r2, r3
	mov	r1, #102
	blx	ip
.L1669:
	mvn	r8, #0
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1673:
	ldr	r1, .L1680+28
	mov	r0, r6
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #209]
	cmp	r0, #0
	bne	.L1679
	ldr	r2, [r5, #3248]
	ldrb	ip, [r5, #18]	@ zero_extendqisi2
	ldr	r1, [r5, #3252]
	add	r3, r2, #1
	cmp	ip, #0
	mla	r3, r1, r3, r3
	bne	.L1641
	mov	r3, r3, asl #1
	b	.L1639
.L1676:
	ldr	r1, [r5, #2204]
	mov	r0, r6
	ldr	r2, .L1680+32
	add	r1, r1, #4
	bl	u_v
	str	r0, [r10, #3420]
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1631
	ldrb	r3, [r4, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1631
	ldr	r1, .L1680+36
	mov	r0, r6
	bl	se_v
	str	r0, [r10, #3424]
	b	.L1631
.L1672:
	cmp	r0, #0
	str	r0, [r4, #220]
	beq	.L1615
	ldr	r1, .L1680+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1615
.L1677:
	ldrb	r3, [r5, #16]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1634
	ldr	r1, .L1680+44
	mov	r0, r6
	bl	se_v
	str	r0, [r10, #3468]
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1634
	ldrb	r3, [r4, #209]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1634
	ldr	r1, .L1680+48
	mov	r0, r6
	bl	se_v
	str	r0, [r10, #3472]
	b	.L1634
.L1679:
	ldr	r1, .L1680+52
	mov	r0, r6
	bl	u_1
	strb	r0, [r4, #210]
	ldr	r2, [r5, #3248]
	ldrb	r0, [r5, #18]	@ zero_extendqisi2
	ldr	r1, [r5, #3252]
	add	r3, r2, #1
	cmp	r0, #0
	ldrb	r0, [r4, #209]	@ zero_extendqisi2
	mla	r3, r1, r3, r3
	moveq	r2, #2
	beq	.L1620
.L1641:
	mov	r2, #1
.L1620:
	cmp	r0, #0
	mul	r3, r2, r3
	beq	.L1639
	cmp	r0, #1
	mov	r2, #0
	strb	r2, [r4, #212]
	bne	.L1624
	b	.L1642
.L1675:
	ldr	r1, .L1680+56
	mov	r0, r6
	bl	ue_v
	cmp	r0, #65536
	str	r0, [r4, #244]
	bcs	.L1628
	ldr	r3, [r9, #2284]
	cmp	r3, #0
	beq	.L1627
.L1628:
	ldr	r1, .L1680+60
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1627
.L1607:
	mov	r2, r10
	ldr	r1, .L1680+64
	mvn	r8, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r8
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1671:
	ldr	r1, .L1680+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1651
.L1674:
	ldr	r1, .L1680+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1651
.L1678:
	ldr	r1, .L1680+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r8, #0
	b	.L1651
.L1681:
	.align	2
.L1680:
	.word	.LC107
	.word	.LC111
	.word	.LC123
	.word	.LC110
	.word	.LC115
	.word	.LC124
	.word	g_event_report
	.word	.LC113
	.word	.LC119
	.word	.LC120
	.word	.LC112
	.word	.LC121
	.word	.LC122
	.word	.LC114
	.word	.LC117
	.word	.LC118
	.word	.LC108
	.word	.LC109
	.word	.LC116
	.word	.LC125
	UNWIND(.fnend)
	.size	ProcessSliceHeaderFirstPart, .-ProcessSliceHeaderFirstPart
	.align	2
	.global	ProcessSliceHeaderSecondPart
	.type	ProcessSliceHeaderSecondPart, %function
ProcessSliceHeaderSecondPart:
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
	add	r6, r0, #12288
	add	r4, r0, #20480
	mov	r5, r0
	ldr	r3, [r6, #1292]
	ldr	r2, [r4, #216]
	sub	r3, r3, #1
	cmp	r3, r2
	bcc	.L1683
	add	r8, r0, #61440
	ldr	r3, [r8, #2284]
	cmp	r3, #0
	bne	.L1683
	bl	PPSSPSCheck
	cmp	r0, #0
	bne	.L1765
	ldr	r2, [r4, #216]
	mov	r7, #2208
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	ldr	r9, [r6, #1304]
	mul	r7, r7, r2
	cmp	r3, #1
	add	r6, r9, r7
	beq	.L1766
.L1687:
	ldr	r2, [r6, #36]
	cmp	r3, #1
	str	r2, [r4, #260]
	ldr	r2, [r6, #40]
	str	r2, [r4, #264]
	bls	.L1767
	cmp	r3, #2
	beq	.L1714
.L1698:
	mov	r3, #32
	str	r3, [r4, #264]
.L1699:
	mov	r0, r5
	bl	ref_pic_list_reordering
	subs	r10, r0, #0
	bne	.L1768
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1701
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r2, #1
	moveq	r3, r2
	beq	.L1702
.L1701:
	ldr	r3, [r6, #44]
	cmp	r3, #1
	beq	.L1769
.L1718:
	mov	r2, #0
	mov	r3, r2
.L1702:
	strb	r3, [r4, #215]
	mov	r0, #19
	ldr	r1, .L1775
	bl	dprint_vfmw
	ldrb	r2, [r4, #215]	@ zero_extendqisi2
	mov	r3, #0
	str	r3, [r4, #268]
	cmp	r2, r3
	str	r3, [r4, #272]
	bne	.L1770
.L1703:
	ldr	r3, [r4, #236]
	cmp	r3, #0
	bne	.L1771
.L1704:
	mov	r3, #0
	str	r3, [r4, #1812]
	ldrb	r3, [r9, r7]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1705
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bls	.L1772
.L1705:
	ldr	r1, .L1775+4
	mov	r0, r5
	bl	se_v
	mov	r3, #0
	str	r3, [r4, #1820]
	str	r3, [r4, #1824]
	str	r3, [r4, #1828]
	str	r0, [r4, #1816]
	ldrb	r3, [r6, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1773
.L1734:
	mov	r0, r10
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1714:
	mov	r3, #32
	str	r3, [r4, #260]
	b	.L1698
.L1773:
	ldr	r1, .L1775+8
	mov	r0, r5
	bl	ue_v
	cmp	r0, #2
	str	r0, [r4, #1820]
	bhi	.L1708
	ldr	r3, [r8, #2284]
	cmp	r3, #0
	bne	.L1708
	cmp	r0, #1
	beq	.L1734
	ldr	r1, .L1775+12
	mov	r0, r5
	bl	se_v
	add	r3, r0, #6
	str	r0, [r4, #1824]
	cmp	r3, #12
	bhi	.L1711
	ldr	r3, [r8, #2284]
	cmp	r3, #0
	bne	.L1711
	mov	r0, r5
	ldr	r1, .L1775+16
	bl	se_v
	add	r3, r0, #6
	str	r0, [r4, #1828]
	cmp	r3, #12
	bhi	.L1713
	ldr	r3, [r8, #2284]
	cmp	r3, #0
	beq	.L1734
.L1713:
	ldr	r1, .L1775+20
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1770:
	mov	r0, r5
	bl	pred_weight_table
	cmp	r0, #0
	beq	.L1703
	ldr	r1, .L1775+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1771:
	mov	r0, r5
	bl	dec_ref_pic_marking
	cmp	r0, #0
	beq	.L1704
	ldr	r1, .L1775+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1769:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r2, r3
	bne	.L1718
	b	.L1702
.L1766:
	ldr	r1, .L1775+32
	mov	r0, r5
	bl	u_1
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	strb	r0, [r4, #214]
	b	.L1687
.L1767:
	ldr	r1, .L1775+36
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L1689
	ldr	r3, [r4, #260]
.L1690:
	ldrb	r2, [r4, #209]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1691
	cmp	r3, #15
	bhi	.L1692
	ldr	r3, [r4, #264]
	cmp	r3, #15
	bhi	.L1774
.L1693:
	ldr	r3, [r8, #2284]
	cmp	r3, #0
	bne	.L1692
.L1694:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1714
	cmp	r3, #1
	bne	.L1698
	b	.L1699
.L1683:
	ldr	r1, .L1775+40
	mvn	r10, #0
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r10
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1772:
	ldr	r1, .L1775+44
	mov	r0, r5
	bl	ue_v
	cmp	r0, #2
	str	r0, [r4, #1812]
	bhi	.L1706
	ldr	r3, [r8, #2284]
	cmp	r3, #0
	beq	.L1705
.L1706:
	ldr	r1, .L1775+48
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1691:
	cmp	r3, #31
	bhi	.L1695
	ldr	r3, [r4, #264]
	cmp	r3, #31
	bls	.L1696
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1696
.L1695:
	ldr	r1, .L1775+52
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1696:
	ldr	r3, [r8, #2284]
	cmp	r3, #0
	beq	.L1694
	b	.L1695
.L1774:
	ldrb	r3, [r4, #208]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1693
.L1692:
	ldr	r1, .L1775+56
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1689:
	ldr	r1, .L1775+60
	mov	r0, r5
	bl	ue_v
	ldrb	r2, [r4, #208]	@ zero_extendqisi2
	cmp	r2, #1
	mov	r3, r0
	str	r0, [r4, #260]
	bne	.L1690
	ldr	r1, .L1775+64
	mov	r0, r5
	bl	ue_v
	ldr	r3, [r4, #260]
	str	r0, [r4, #264]
	b	.L1690
.L1711:
	ldr	r1, .L1775+68
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1708:
	ldr	r1, .L1775+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1765:
	ldr	r1, .L1775+76
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1768:
	ldr	r1, .L1775+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r10, #0
	b	.L1734
.L1776:
	.align	2
.L1775:
	.word	.LC133
	.word	.LC138
	.word	.LC139
	.word	.LC141
	.word	.LC143
	.word	.LC144
	.word	.LC134
	.word	.LC135
	.word	.LC126
	.word	.LC127
	.word	.LC108
	.word	.LC136
	.word	.LC137
	.word	.LC131
	.word	.LC130
	.word	.LC128
	.word	.LC129
	.word	.LC142
	.word	.LC140
	.word	.LC109
	.word	.LC132
	UNWIND(.fnend)
	.size	ProcessSliceHeaderSecondPart, .-ProcessSliceHeaderSecondPart
	.align	2
	.global	ExitSlice
	.type	ExitSlice, %function
ExitSlice:
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
	add	r3, r0, #20480
	add	lr, r0, #12288
	mov	r1, #2208
	mov	r7, #4000
	ldr	r2, [lr, #1304]
	ldr	ip, [r3, #216]
	ldr	r5, [lr, #1300]
	ldrb	r6, [r3, #209]	@ zero_extendqisi2
	mla	r1, r1, ip, r2
	cmp	r6, #0
	ldr	r4, [r3, #256]
	ldr	lr, [r3, #224]
	ldr	r2, [r1, #28]
	str	ip, [r3, #1856]
	ldr	ip, [r3, #236]
	mla	r2, r7, r2, r5
	ldr	r1, [r2, #36]
	str	r4, [r3, #1888]
	str	lr, [r3, #1864]
	str	r1, [r3, #1852]
	ldrneb	r1, [r3, #210]	@ zero_extendqisi2
	strb	r6, [r3, #1848]
	str	ip, [r3, #1860]
	strneb	r1, [r3, #1849]
	ldrb	r1, [r3, #211]	@ zero_extendqisi2
	cmp	r1, #5
	strb	r1, [r3, #1850]
	ldreq	r1, [r3, #244]
	streq	r1, [r3, #1868]
	ldr	r1, [r2, #2200]
	cmp	r1, #0
	bne	.L1780
	add	r1, r0, #16384
	ldr	ip, [r1, #3420]
	str	ip, [r3, #1872]
	ldr	r1, [r1, #3424]
	str	r1, [r3, #1876]
	ldr	r1, [r2, #2200]
.L1780:
	cmp	r1, #1
	addeq	r2, r0, #16384
	add	r0, r0, #61440
	ldreq	r1, [r2, #3468]
	streq	r1, [r3, #1880]
	ldreq	r2, [r2, #3472]
	streq	r2, [r3, #1884]
	ldr	r3, [r0, #2300]
	add	r3, r3, #1
	str	r3, [r0, #2300]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	ExitSlice, .-ExitSlice
	.align	2
	.global	PicTypeStatistic
	.type	PicTypeStatistic, %function
PicTypeStatistic:
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
	add	r2, r0, #20480
	ldrb	r3, [r2, #208]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L1787
	bcc	.L1788
	cmp	r3, #2
	ldmnefd	sp, {fp, sp, pc}
	ldrb	r3, [r2, #211]	@ zero_extendqisi2
	add	r0, r0, #57344
	cmp	r3, #5
	beq	.L1797
.L1790:
	mov	r3, #0
	str	r3, [r0, #3696]
	ldmfd	sp, {fp, sp, pc}
.L1788:
	add	r0, r0, #57344
	ldr	r3, [r0, #3692]
	cmp	r3, #2
	movne	r3, #1
	strne	r3, [r0, #3692]
	b	.L1790
.L1787:
	add	r0, r0, #57344
	mov	r2, #2
	mov	r3, #0
	str	r2, [r0, #3692]
	str	r3, [r0, #3696]
	ldmfd	sp, {fp, sp, pc}
.L1797:
	mov	r3, #1
	str	r3, [r0, #3696]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	PicTypeStatistic, .-PicTypeStatistic
	.align	2
	.global	CalcStreamBits
	.type	CalcStreamBits, %function
CalcStreamBits:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	add	r3, r0, #16384
	mov	r4, r0
	ldrb	r3, [r3, #1212]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1799
	ldr	r2, [r0, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #7
	bic	r3, r3, #7
	str	r3, [r2, #64]
	ldr	r2, [r0, #368]
	ldr	r3, [r2, #72]
	sub	r3, r3, #1
	str	r3, [r2, #72]
.L1799:
	ldr	r3, [r4, #368]
	ldrb	r6, [r3]	@ zero_extendqisi2
	cmp	r6, #0
	beq	.L1810
	mov	r1, #0
	mov	r0, r3
	mov	r5, r1
.L1801:
	add	r1, r1, #1
	ldr	ip, [r0, #12]
	cmp	r1, r6
	add	r0, r0, #28
	add	r5, r5, ip
	bne	.L1801
.L1800:
	mov	r7, r6, asl #5
	ldr	r0, [r3, #72]
	sub	r7, r7, r6, asl #2
	ldr	r2, [r3, #64]
	add	r1, r3, r7
	mov	r3, r5
	str	r0, [sp, #4]
	mov	r0, #7
	ldr	ip, [r1, #12]
	ldr	r1, .L1821
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #368]
	mov	r2, r6
	mov	r0, #7
	ldr	r1, .L1821+4
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	ip, [r3, #64]
	mov	lr, r6, asl #5
	and	ip, ip, r0
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	str	ip, [r3, #24]
	ldr	r3, [r4, #368]
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldr	r8, [r3, #64]
	mov	lr, r6, asl #5
	sub	lr, lr, r6, asl #2
	add	r3, r3, lr
	ldr	ip, [r3, #16]
	add	ip, ip, r8, lsr #3
	rsb	ip, r5, ip
	str	ip, [r3, #28]
	ldr	ip, [r4, #368]
	ldrb	r6, [ip]	@ zero_extendqisi2
	ldr	lr, [ip, #64]
	mov	r3, r6, asl #5
	sub	r3, r3, r6, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #12]
	add	r3, r5, r3
	rsb	r3, lr, r3, lsl #3
	str	r3, [ip, #20]
	ldr	ip, [r4, #368]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	ldr	lr, [r3, #24]
	and	ip, ip, #3
	add	ip, lr, ip, lsl #3
	str	ip, [r3, #24]
	ldr	ip, [r4, #368]
	ldrb	lr, [ip]	@ zero_extendqisi2
	mov	r3, lr, asl #5
	sub	r3, r3, lr, asl #2
	add	r3, ip, r3
	ldr	ip, [r3, #28]
	bic	ip, ip, #3
	str	ip, [r3, #28]
	ldr	ip, [r4, #368]
	add	r7, ip, r7
	ldrb	r5, [ip]	@ zero_extendqisi2
	ldr	r3, [r7, #24]
	mov	lr, r5, asl #5
	sub	lr, lr, r5, asl #2
	add	ip, ip, lr
	ldr	ip, [ip, #28]
	str	ip, [sp, #4]
	ldr	ip, [r7, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r4, #368]
	ldr	r2, [ip, #68]
	sub	r3, r2, #1
	cmp	r3, #1
	bhi	.L1820
	ldrb	r6, [ip]	@ zero_extendqisi2
	add	r1, r6, #1
	cmp	r2, r1
	movhi	r2, #1
	movls	r2, #0
	cmp	r1, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L1803
	add	r6, r6, #2
	mov	r5, #0
.L1804:
	sub	r3, r6, #1
	ldr	r1, .L1821+8
	mov	r0, #7
	mov	lr, r3, asl #5
	mov	r2, r3
	sub	r3, lr, r3, asl #2
	add	ip, ip, r3
	str	r5, [ip, #24]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #16]
	str	lr, [ip, #28]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #12]
	mov	lr, lr, asl #3
	str	lr, [ip, #20]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	ldr	r7, [ip, #24]
	and	lr, lr, #3
	add	lr, r7, lr, lsl #3
	str	lr, [ip, #24]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	lr, [ip, #28]
	bic	lr, lr, #3
	str	lr, [ip, #28]
	ldr	ip, [r4, #368]
	add	ip, ip, r3
	ldr	r3, [ip, #24]
	ldr	ip, [ip, #20]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r4, #368]
	ldr	r3, [ip, #68]
	cmp	r6, #1
	cmpls	r6, r3
	add	r6, r6, #1
	movcc	r2, #1
	movcs	r2, #0
	cmp	r2, #0
	bne	.L1804
	sub	r3, r3, #1
.L1803:
	mov	r2, r3, asl #5
	ldr	r1, [ip, #72]
	sub	r3, r2, r3, asl #2
	add	ip, ip, r3
	ldr	r3, [ip, #20]
	rsb	r3, r1, r3
	str	r3, [ip, #20]
	ldr	ip, [r4, #368]
	ldrb	r1, [ip]	@ zero_extendqisi2
	ldr	r3, [ip, #68]
	cmp	r1, r3
	bcs	.L1798
	sxth	r3, r1
	add	r4, r4, #57344
	mov	r2, r3, asl #5
	sub	r3, r2, r3, asl #2
	add	r3, ip, r3
.L1808:
	ldr	r2, [r3, #28]
	add	r1, r1, #1
	ldr	r0, [r4, #3720]
	add	r3, r3, #28
	cmp	r2, r0
	strcc	r2, [r4, #3720]
	ldr	r2, [ip, #68]
	cmp	r2, r1
	bhi	.L1808
.L1798:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L1820:
	ldr	r1, .L1821+12
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, lr}
	b	dprint_vfmw
.L1810:
	mov	r5, r6
	b	.L1800
.L1822:
	.align	2
.L1821:
	.word	.LC145
	.word	.LC146
	.word	.LC148
	.word	.LC147
	UNWIND(.fnend)
	.size	CalcStreamBits, .-CalcStreamBits
	.align	2
	.global	Scaling_List
	.type	Scaling_List, %function
Scaling_List:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 8
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
	subs	r7, r3, #0
	str	r0, [fp, #-52]
	mov	r6, r2
	ble	.L1823
	mov	r0, #8
	mov	r4, #0
	mov	r2, r7
	mov	r9, r6
	ldr	r8, .L1834
	mov	r10, #255
	mov	r7, r1
	mov	r6, r0
	mov	r5, r4
	b	.L1828
.L1827:
	mov	lr, r4, lsr #2
	and	r3, r4, #3
	str	r6, [r7, r4, asl #2]
	uxtb	r1, r6
	mov	r4, r3, asl #3
	ldr	r3, [r9, lr, asl #2]
	cmp	r5, r2
	bic	r3, r3, r10, asl r4
	orr	r1, r3, r1, asl r4
	str	r1, [r9, lr, asl #2]
	beq	.L1823
.L1828:
	cmp	r2, #16
	ldreq	r3, .L1834+4
	ldrneb	r4, [r5, r8]	@ zero_extendqisi2
	ldreqb	r4, [r5, r3]	@ zero_extendqisi2
	cmp	r0, #0
	add	r5, r5, #1
	beq	.L1827
	ldr	r1, .L1834+8
	ldr	r0, [fp, #-52]
	str	r2, [fp, #-48]
	bl	se_v
	ldr	r2, [fp, #4]
	add	r0, r6, r0
	ands	r0, r0, #255
	moveq	r3, #1
	movne	r3, #0
	cmp	r3, #0
	moveq	r6, r0
	cmp	r4, #0
	movne	r3, #0
	andeq	r3, r3, #1
	str	r3, [r2]
	ldr	r2, [fp, #-48]
	b	.L1827
.L1823:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1835:
	.align	2
.L1834:
	.word	.LANCHOR0+40
	.word	.LANCHOR0+24
	.word	.LC149
	UNWIND(.fnend)
	.size	Scaling_List, .-Scaling_List
	.align	2
	.global	ProcessPPS
	.type	ProcessPPS, %function
ProcessPPS:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	mov	r4, r1
	ldr	r1, .L1894
	mov	r5, r0
	bl	u_1
	add	r6, r5, #61440
	strb	r0, [r4]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L1885
	ldr	r1, .L1894+4
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #1]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L1885
	ldr	r1, .L1894+8
	mov	r0, r5
	bl	ue_v
	cmp	r0, #0
	str	r0, [r4, #32]
	bne	.L1840
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	beq	.L1841
.L1840:
	ldr	r1, .L1894+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L1894+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L1885
	mov	r3, #0
	ldr	r0, [r6, #2344]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
.L1838:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1848:
	ldr	r1, .L1894+20
	mov	r0, r5
	bl	u_1
	ldr	r1, .L1894+24
	str	r0, [r4, #60]
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #18]
	cmp	r0, #1
	beq	.L1849
.L1867:
	mov	r0, r5
	ldr	r1, .L1894+28
	bl	se_v
	add	r3, r0, #12
	str	r0, [r4, #56]
	cmp	r3, #24
	bhi	.L1850
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	beq	.L1868
.L1850:
	ldr	r1, .L1894+32
	mov	r0, #1
	bl	dprint_vfmw
.L1885:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1841:
	ldr	r1, .L1894+36
	mov	r0, r5
	bl	ue_v
	cmp	r0, #31
	str	r0, [r4, #36]
	bhi	.L1842
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L1842
	ldr	r1, .L1894+40
	mov	r0, r5
	bl	ue_v
	cmp	r0, #31
	str	r0, [r4, #40]
	bhi	.L1844
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L1844
	ldr	r1, .L1894+44
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #2]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L1885
	ldr	r2, .L1894+48
	mov	r1, #2
	mov	r0, r5
	bl	u_v
	cmp	r0, #2
	str	r0, [r4, #44]
	bhi	.L1886
	ldr	r1, .L1894+52
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1894+56
	str	r0, [r4, #48]
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1894+60
	mov	r0, r5
	bl	se_v
	ldr	r1, .L1894+64
	str	r0, [r4, #52]
	mov	r0, r5
	bl	u_1
	ldr	r1, .L1894+68
	strb	r0, [r4, #3]
	mov	r0, r5
	bl	u_1
	ldr	r1, .L1894+72
	strb	r0, [r4, #4]
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #17]
	cmp	r0, #0
	bne	.L1887
.L1847:
	ldr	r3, [r4, #52]
	add	r0, r5, #13504
	mov	r7, #0
	add	r0, r0, #24
	str	r7, [r4, #60]
	str	r3, [r4, #56]
	strb	r7, [r4, #18]
	bl	BsResidBits
	ldr	r3, [r5, #368]
	ldr	r3, [r3, #72]
	add	r3, r3, #3
	cmp	r0, r3
	bcs	.L1848
.L1868:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1887:
	ldr	r1, .L1894+76
	mov	r0, #1
	bl	dprint_vfmw
	b	.L1847
.L1842:
	ldr	r1, .L1894+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1838
.L1844:
	ldr	r1, .L1894+84
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1838
.L1849:
	add	r3, r4, #4
	str	r6, [fp, #-80]
	sub	r9, fp, #72
	add	r8, r4, #1984
	add	r10, r4, #64
	mov	r6, r3
	b	.L1858
.L1891:
	ldr	lr, [lr, #1300]
	ldr	r3, [r4, #28]
	mla	r3, ip, r3, lr
	ldrb	ip, [r3, #25]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L1888
	ldr	r3, .L1894+88
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L1894+92
	ldr	r3, [r3, #52]
	blx	r3
.L1853:
	add	r7, r7, #1
	add	r8, r8, #16
	cmp	r7, #6
	add	r10, r10, #64
	beq	.L1889
.L1858:
	ldr	r1, .L1894+96
	mov	r0, r5
	bl	u_1
	clz	r1, r7
	add	lr, r5, #12288
	mov	ip, #4000
	mov	r2, #16
	mov	r1, r1, lsr #5
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r8
	str	r3, [r9, #4]!
	strb	r3, [r6, #1]!
	beq	.L1890
	cmp	r7, #0
	cmpne	r7, #3
	beq	.L1891
	ldr	r3, .L1894+92
	mov	r2, #16
	sub	r1, r8, #16
	mov	r0, r8
	ldr	r3, [r3, #52]
	blx	r3
	b	.L1853
.L1889:
	ldr	r6, [fp, #-80]
	add	ip, r4, #448
	add	r3, r5, #12288
	sub	r8, fp, #76
	add	r9, r4, #2080
	add	r10, r4, #11
	str	r5, [fp, #-80]
	mov	r7, #0
	str	r6, [fp, #-84]
	mov	r5, r3
	mov	r6, r4
	mov	r4, ip
.L1866:
	ldr	r2, [r6, #60]
	mov	r3, #0
	cmp	r2, #1
	strne	r3, [r8]
	strneb	r3, [r10]
	beq	.L1892
.L1861:
	ldr	r1, [r6, #28]
	mov	lr, #4000
	ldr	r3, [r5, #1300]
	mov	r0, r9
	mov	r2, #64
	mla	r3, lr, r1, r3
	ldrb	r1, [r3, #25]	@ zero_extendqisi2
	cmp	r1, #1
	beq	.L1893
	ldr	r1, .L1894+100
	cmp	r7, #0
	ldr	r3, .L1894+92
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L1862:
	add	r7, r7, #1
	add	r9, r9, #64
	cmp	r7, #2
	add	r4, r4, #256
	add	r8, r8, #4
	add	r10, r10, #1
	bne	.L1866
	mov	r4, r6
	ldr	r5, [fp, #-80]
	ldr	r6, [fp, #-84]
	b	.L1867
.L1890:
	mov	r3, r2
	str	r9, [sp]
	mov	r2, r8
	mov	r1, r10
	mov	r0, r5
	bl	Scaling_List
	ldr	r3, [r9]
	cmp	r3, #1
	bne	.L1853
	ldr	r1, .L1894+88
	mov	r2, #16
	ldr	r3, .L1894+92
	cmp	r7, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r8
	blx	r3
	b	.L1853
.L1888:
	add	r1, r3, r7, lsl #4
	ldr	r3, .L1894+92
	add	r1, r1, #1968
	mov	r2, #16
	add	r1, r1, #4
	mov	r0, r8
	ldr	r3, [r3, #52]
	blx	r3
	b	.L1853
.L1886:
	ldr	r1, .L1894+104
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1838
.L1892:
	ldr	r1, .L1894+108
	ldr	r0, [fp, #-80]
	bl	u_1
	mov	r2, r9
	mov	r1, r4
	mov	r3, #64
	mov	lr, r0
	cmp	lr, #1
	ldr	r0, [fp, #-80]
	str	lr, [r8]
	strb	lr, [r10]
	bne	.L1861
	str	r8, [sp]
	bl	Scaling_List
	ldr	r3, [r8]
	cmp	r3, #1
	bne	.L1862
	ldr	r1, .L1894+100
	mov	r2, #64
	ldr	r3, .L1894+92
	cmp	r7, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r9
	blx	r3
	b	.L1862
.L1893:
	add	r1, r3, r7, lsl #6
	ldr	r3, .L1894+92
	add	r1, r1, #2064
	add	r1, r1, #4
	ldr	r3, [r3, #52]
	blx	r3
	b	.L1862
.L1895:
	.align	2
.L1894:
	.word	.LC150
	.word	.LC151
	.word	.LC152
	.word	.LC153
	.word	g_event_report
	.word	.LC168
	.word	.LC169
	.word	.LC170
	.word	.LC173
	.word	.LC154
	.word	.LC156
	.word	.LC158
	.word	.LC159
	.word	.LC161
	.word	.LC162
	.word	.LC163
	.word	.LC164
	.word	.LC165
	.word	.LC166
	.word	.LC167
	.word	.LC155
	.word	.LC157
	.word	.LANCHOR1+80
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC171
	.word	.LANCHOR1+112
	.word	.LC160
	.word	.LC172
	UNWIND(.fnend)
	.size	ProcessPPS, .-ProcessPPS
	.align	2
	.global	PPSEqual
	.type	PPSEqual, %function
PPSEqual:
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
	subs	r6, r0, #0
	beq	.L1919
	cmp	r1, #0
	beq	.L1920
	ldr	r2, [r6, #24]
	ldr	ip, [r6, #28]
	ldr	r0, [r1, #28]
	ldr	r4, [r1, #24]
	ldrb	lr, [r6]	@ zero_extendqisi2
	cmp	ip, r0
	cmpeq	r2, r4
	ldrb	r3, [r1]	@ zero_extendqisi2
	ldrb	r4, [r6, #1]	@ zero_extendqisi2
	ldrb	ip, [r1, #1]	@ zero_extendqisi2
	moveq	r2, #1
	movne	r2, #0
	cmp	lr, r3
	movne	r0, #0
	andeq	r0, r2, #1
	ldr	lr, [r6, #36]
	cmp	r4, ip
	movne	r3, #0
	andeq	r3, r0, #1
	ldr	r2, [r1, #36]
	ldr	r4, [r6, #40]
	ldr	r0, [r1, #40]
	cmp	lr, r2
	movne	ip, #0
	andeq	ip, r3, #1
	ldrb	lr, [r6, #2]	@ zero_extendqisi2
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r4, r0
	movne	r2, #0
	andeq	r2, ip, #1
	ldr	r4, [r6, #44]
	ldr	ip, [r1, #44]
	cmp	lr, r3
	movne	r0, #0
	andeq	r0, r2, #1
	ldr	lr, [r6, #48]
	ldr	r2, [r1, #48]
	cmp	r4, ip
	movne	r3, #0
	andeq	r3, r0, #1
	ldr	r4, [r6, #52]
	ldr	r0, [r1, #52]
	cmp	lr, r2
	movne	ip, #0
	andeq	ip, r3, #1
	ldrb	r5, [r6, #3]	@ zero_extendqisi2
	ldrb	lr, [r1, #3]	@ zero_extendqisi2
	cmp	r4, r0
	movne	r2, #0
	andeq	r2, ip, #1
	ldrb	r3, [r6, #4]	@ zero_extendqisi2
	ldrb	r4, [r1, #4]	@ zero_extendqisi2
	cmp	r5, lr
	movne	r0, #0
	andeq	r0, r2, #1
	ldr	ip, [r6, #60]
	ldr	lr, [r1, #60]
	cmp	r3, r4
	movne	r3, #0
	andeq	r3, r0, #1
	ldrb	r2, [r1, #18]	@ zero_extendqisi2
	ldrb	r0, [r6, #18]	@ zero_extendqisi2
	cmp	ip, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r0
	movne	r2, #0
	andeq	r2, r3, #1
	cmp	r0, #0
	beq	.L1900
	mov	ip, ip, asl #1
	adds	r3, ip, #6
	str	r3, [fp, #-48]
	beq	.L1900
	add	r0, r1, #4
	sub	r8, r1, #1088
	add	r3, r6, #4
	sub	r8, r8, #4
	add	r9, r1, #64
	mov	r5, r0
	mov	r10, r6
	mov	r7, r6
	str	r6, [fp, #-52]
	mov	r0, #0
	mov	r6, r3
	str	r1, [fp, #-56]
.L1905:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	ldrsb	ip, [r5, #1]!
	sxtb	r1, r3
	cmp	ip, r1
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r3, #0
	beq	.L1918
	cmp	r0, #5
	bhi	.L1902
	add	r4, r10, #64
	add	r10, r10, #128
	mov	r1, r9
	mov	r3, r4
.L1903:
	ldr	lr, [r3], #4
	ldr	ip, [r1], #4
	cmp	lr, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r3, r10
	bne	.L1903
.L1901:
	ldr	r3, [fp, #-48]
	add	r0, r0, #1
	add	r7, r7, #256
	add	r8, r8, #256
	cmp	r0, r3
	mov	r10, r4
	add	r9, r9, #64
	bne	.L1905
	ldr	r6, [fp, #-52]
	ldr	r1, [fp, #-56]
.L1900:
	ldr	r0, [r6, #56]
	ldr	r3, [r1, #56]
	cmp	r0, r3
	movne	r0, #0
	andeq	r0, r2, #1
	eor	r0, r0, #1
	rsb	r0, r0, #0
.L1898:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L1902:
	sub	r3, r7, #1088
	sub	r4, r7, #836
	sub	r3, r3, #4
	mov	r1, r8
.L1904:
	ldr	lr, [r3, #4]!
	ldr	ip, [r1, #4]!
	cmp	lr, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r3, r4
	bne	.L1904
.L1918:
	add	r4, r10, #64
	b	.L1901
.L1920:
	mov	r0, r1
	movw	r3, #9299
	ldr	r2, .L1921
	ldr	r1, .L1921+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1898
.L1919:
	movw	r3, #9298
	ldr	r2, .L1921
	ldr	r1, .L1921+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1898
.L1922:
	.align	2
.L1921:
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	PPSEqual, .-PPSEqual
	.align	2
	.global	H264_DecPPS
	.type	H264_DecPPS, %function
H264_DecPPS:
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
	ldr	r1, .L1940
	add	r4, r0, #12288
	mov	r5, r0
	bl	ue_v
	ldr	r3, [r4, #1292]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	r6, r0
	bls	.L1924
	ldr	r1, .L1940+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #1292]
	sub	r2, r3, #1
	cmp	r6, r2
	bls	.L1932
	ldr	r2, .L1940+8
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L1932
	add	r5, r5, #61440
	str	r3, [fp, #-40]
	str	r6, [fp, #-44]
	mov	r3, #8
	ldr	r0, [r5, #2344]
	sub	r2, fp, #44
	mov	r1, #110
	blx	ip
	mvn	r0, #0
.L1925:
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1924:
	ldr	r1, .L1940+12
	mov	r0, r5
	bl	ue_v
	ldr	r3, [r4, #1288]
	sub	r3, r3, #1
	cmp	r0, r3
	mov	ip, r0
	bhi	.L1936
	ldr	r2, [r4, #1300]
	mov	r3, #4000
	mla	r3, r3, r0, r2
	ldrb	r3, [r3, #23]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1937
	mov	r9, #2208
	ldr	r3, [r4, #1304]
	mul	r7, r9, r6
	add	r3, r3, r7
	ldrb	r8, [r3, #19]	@ zero_extendqisi2
	cmp	r8, #0
	beq	.L1928
	ldr	r8, .L1940+16
	mov	r0, r5
	mov	r1, r8
	str	r6, [r8, #24]
	str	ip, [r8, #28]
	bl	ProcessPPS
	subs	r5, r0, #0
	bne	.L1938
	ldr	r1, [r4, #1304]
	mov	r0, r8
	add	r1, r1, r7
	bl	PPSEqual
	cmp	r0, #0
	beq	.L1925
	ldr	ip, .L1940+20
	mov	r3, #1
	ldr	r0, [r4, #1304]
	mov	r2, r9
	mov	r1, r8
	strb	r3, [r8, #20]
	add	r0, r0, r7
	ldr	ip, [ip, #56]
	strb	r3, [r8, #19]
	blx	ip
	mov	r0, r5
	b	.L1925
.L1928:
	str	r6, [r3, #24]
	mov	r0, r5
	ldr	r3, [r4, #1304]
	add	r3, r3, r7
	str	ip, [r3, #28]
	ldr	r1, [r4, #1304]
	add	r1, r1, r7
	bl	ProcessPPS
	cmp	r0, #0
	bne	.L1939
	ldr	r3, [r4, #1304]
	mov	r2, #1
	add	r3, r3, r7
	strb	r2, [r3, #20]
	ldr	r3, [r4, #1304]
	add	r7, r3, r7
	strb	r2, [r7, #19]
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1932:
	mvn	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1936:
	ldr	r1, .L1940+24
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1925
.L1938:
	ldr	r2, .L1940+28
	mov	r0, #1
	ldr	r1, .L1940+32
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1925
.L1937:
	ldr	r1, .L1940+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1925
.L1939:
	ldr	r2, .L1940+28
	mov	r0, #1
	ldr	r1, .L1940+40
	bl	dprint_vfmw
	ldr	r3, [r4, #1304]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r7
	strb	r2, [r3, #20]
	ldr	r3, [r4, #1304]
	add	r7, r3, r7
	strb	r8, [r7, #19]
	b	.L1925
.L1941:
	.align	2
.L1940:
	.word	.LC174
	.word	.LC175
	.word	g_event_report
	.word	.LC176
	.word	.LANCHOR2
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC177
	.word	.LANCHOR0+104
	.word	.LC179
	.word	.LC178
	.word	.LC180
	UNWIND(.fnend)
	.size	H264_DecPPS, .-H264_DecPPS
	.align	2
	.global	vui_parameters
	.type	vui_parameters, %function
vui_parameters:
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
	mov	r5, r1
	ldr	r1, .L1991
	mov	r4, r0
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5]
	cmp	r0, #0
	streqb	r0, [r5, #15]
	bne	.L1985
.L1944:
	ldr	r1, .L1991+4
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #1]
	cmp	r0, #0
	bne	.L1986
.L1945:
	ldr	r1, .L1991+8
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #3]
	cmp	r0, #0
	moveq	r3, #5
	streq	r3, [r5, #28]
	bne	.L1987
.L1947:
	ldr	r1, .L1991+12
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #6]
	cmp	r0, #0
	bne	.L1988
.L1948:
	ldr	r1, .L1991+16
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #8]
	cmp	r0, #0
	bne	.L1989
.L1950:
	ldr	r1, .L1991+20
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #7]
	cmp	r0, #0
	beq	.L1952
	ldr	r1, .L1991+24
	mov	r0, r4
	bl	ue_v
	ldr	r2, .L1991+28
	mov	r1, #4
	str	r0, [r5, #120]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+32
	mov	r1, #4
	strb	r0, [r5, #116]
	mov	r0, r4
	bl	u_v
	ldr	r3, [r5, #120]
	cmp	r3, #31
	strb	r0, [r5, #117]
	bhi	.L1955
	add	r9, r4, #61440
	ldr	r6, [r9, #2284]
	cmp	r6, #0
	bne	.L1955
	add	r7, r5, #120
	add	r8, r5, #83
.L1956:
	ldr	r1, .L1991+36
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #120]
	cmp	r3, r6
	bcs	.L1956
	ldr	r2, .L1991+48
	mov	r1, #5
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+52
	mov	r1, #5
	str	r0, [r5, #380]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+56
	mov	r1, #5
	str	r0, [r5, #384]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+60
	mov	r1, #5
	str	r0, [r5, #388]
	mov	r0, r4
	bl	u_v
	str	r0, [r5, #392]
.L1952:
	ldr	r1, .L1991+64
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #10]
	cmp	r0, #0
	bne	.L1990
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	add	r9, r4, #61440
	cmp	r3, #0
	bne	.L1961
.L1960:
	ldr	r1, .L1991+68
	mov	r0, r4
	bl	u_1
	ldr	r1, .L1991+72
	strb	r0, [r5, #11]
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #12]
	cmp	r0, #0
	bne	.L1962
	ldr	r0, [r9, #2284]
.L1963:
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1990:
	ldr	r1, .L1991+24
	mov	r0, r4
	bl	ue_v
	ldr	r2, .L1991+28
	mov	r1, #4
	str	r0, [r5, #432]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+32
	mov	r1, #4
	strb	r0, [r5, #428]
	mov	r0, r4
	bl	u_v
	ldr	r3, [r5, #432]
	cmp	r3, #31
	strb	r0, [r5, #429]
	bhi	.L1955
	add	r9, r4, #61440
	ldr	r6, [r9, #2284]
	cmp	r6, #0
	bne	.L1955
	add	r8, r5, #392
	add	r7, r5, #432
	add	r8, r8, #3
.L1958:
	ldr	r1, .L1991+36
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+40
	add	r6, r6, #1
	str	r0, [r7, #4]!
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+44
	str	r0, [r7, #128]
	mov	r0, r4
	bl	u_1
	strb	r0, [r8, #1]!
	ldr	r3, [r5, #432]
	cmp	r3, r6
	bcs	.L1958
	ldr	r2, .L1991+48
	mov	r1, #5
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+52
	mov	r1, #5
	str	r0, [r5, #692]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+56
	mov	r1, #5
	str	r0, [r5, #696]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+60
	mov	r1, #5
	str	r0, [r5, #700]
	mov	r0, r4
	bl	u_v
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	cmp	r3, #0
	str	r0, [r5, #704]
	bne	.L1961
	ldrb	r3, [r5, #10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1960
.L1961:
	ldr	r1, .L1991+76
	mov	r0, r4
	bl	u_1
	strb	r0, [r5, #14]
	b	.L1960
.L1989:
	ldr	r2, .L1991+80
	mov	r1, #32
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+84
	mov	r1, #32
	str	r0, [r5, #52]
	mov	r0, r4
	bl	u_v
	ldr	r1, .L1991+88
	str	r0, [r5, #56]
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #9]
	cmp	r0, #1
	bne	.L1950
	ldr	r2, [r5, #52]
	cmp	r2, #0
	beq	.L1950
	ldr	r0, [r5, #56]
	movw	r1, #10000
	ldr	r3, .L1991+92
	add	r9, r4, #61440
	umull	r0, r1, r0, r1
	ldr	r3, [r3, #236]
	movs	r1, r1, lsr #1
	mov	r0, r0, rrx
	blx	r3
	movw	r2, #52429
	movt	r2, 52428
	add	r0, r0, #5
	umull	r2, r3, r0, r2
	mov	r3, r3, lsr #3
	str	r3, [r9, #1052]
	b	.L1950
.L1988:
	ldr	r1, .L1991+96
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+100
	str	r0, [r5, #44]
	mov	r0, r4
	bl	ue_v
	str	r0, [r5, #48]
	b	.L1948
.L1987:
	ldr	r2, .L1991+104
	mov	r1, #3
	mov	r0, r4
	bl	u_v
	ldr	r1, .L1991+108
	str	r0, [r5, #28]
	mov	r0, r4
	bl	u_1
	ldr	r1, .L1991+112
	strb	r0, [r5, #4]
	mov	r0, r4
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r5, #5]
	cmp	r0, #0
	beq	.L1947
	ldr	r2, .L1991+116
	mov	r1, #8
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+120
	mov	r1, #8
	str	r0, [r5, #32]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+124
	mov	r1, #8
	str	r0, [r5, #36]
	mov	r0, r4
	bl	u_v
	str	r0, [r5, #40]
	b	.L1947
.L1986:
	ldr	r1, .L1991+128
	mov	r0, r4
	bl	u_1
	strb	r0, [r5, #2]
	b	.L1945
.L1985:
	ldr	r2, .L1991+132
	mov	r1, #8
	mov	r0, r4
	bl	u_v
	uxtb	r0, r0
	strb	r0, [r5, #15]
	cmp	r0, #255
	bne	.L1944
	ldr	r2, .L1991+136
	mov	r1, #16
	mov	r0, r4
	bl	u_v
	ldr	r2, .L1991+140
	mov	r1, #16
	str	r0, [r5, #16]
	mov	r0, r4
	bl	u_v
	str	r0, [r5, #20]
	b	.L1944
.L1962:
	ldr	r1, .L1991+144
	mov	r0, r4
	bl	u_1
	ldr	r1, .L1991+148
	strb	r0, [r5, #13]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+152
	str	r0, [r5, #60]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+156
	str	r0, [r5, #64]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+160
	str	r0, [r5, #72]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+164
	str	r0, [r5, #68]
	mov	r0, r4
	bl	ue_v
	ldr	r1, .L1991+168
	str	r0, [r5, #76]
	mov	r0, r4
	bl	ue_v
	str	r0, [r5, #80]
	ldr	r0, [r9, #2284]
	cmp	r0, #0
	beq	.L1963
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1955:
	ldr	r1, .L1991+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L1992:
	.align	2
.L1991:
	.word	.LC181
	.word	.LC185
	.word	.LC187
	.word	.LC194
	.word	.LC197
	.word	.LC201
	.word	.LC202
	.word	.LC203
	.word	.LC204
	.word	.LC206
	.word	.LC207
	.word	.LC208
	.word	.LC209
	.word	.LC210
	.word	.LC211
	.word	.LC212
	.word	.LC213
	.word	.LC215
	.word	.LC216
	.word	.LC214
	.word	.LC198
	.word	.LC199
	.word	.LC200
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC195
	.word	.LC196
	.word	.LC188
	.word	.LC189
	.word	.LC190
	.word	.LC191
	.word	.LC192
	.word	.LC193
	.word	.LC186
	.word	.LC182
	.word	.LC183
	.word	.LC184
	.word	.LC217
	.word	.LC218
	.word	.LC219
	.word	.LC220
	.word	.LC221
	.word	.LC222
	.word	.LC223
	.word	.LC205
	UNWIND(.fnend)
	.size	vui_parameters, .-vui_parameters
	.align	2
	.global	SPSEqual
	.type	SPSEqual, %function
SPSEqual:
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
	subs	r5, r0, #0
	beq	.L2025
	cmp	r1, #0
	beq	.L2026
	ldrb	lr, [r1]	@ zero_extendqisi2
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	ip, [r5, #28]
	ldr	r2, [r1, #28]
	ldrb	r0, [r5, #1]	@ zero_extendqisi2
	cmp	r3, lr
	cmpeq	ip, r2
	ldrb	r6, [r1, #1]	@ zero_extendqisi2
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	ldrb	r4, [r1, #2]	@ zero_extendqisi2
	moveq	lr, #1
	movne	lr, #0
	ldr	r3, [r5, #32]
	cmp	r0, r6
	movne	ip, #0
	andeq	ip, lr, #1
	ldr	r6, [r1, #32]
	cmp	r2, r4
	movne	r0, #0
	andeq	r0, ip, #1
	ldr	lr, [r1, #36]
	ldr	r4, [r5, #36]
	cmp	r3, r6
	movne	r2, #0
	andeq	r2, r0, #1
	ldrb	ip, [r1, #25]	@ zero_extendqisi2
	ldrb	r0, [r5, #25]	@ zero_extendqisi2
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r2, #1
	cmp	ip, r0
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r0, #0
	beq	.L1997
	add	r0, r1, #3
	add	r2, r5, #3
	sub	r9, r1, #1104
	add	r7, r1, #48
	mov	ip, r0
	mov	r8, r5
	mov	r6, r5
	str	r5, [fp, #-48]
	mov	r0, #0
	mov	r4, r2
	mov	r5, ip
	str	r1, [fp, #-52]
.L2002:
	ldrb	r2, [r4, #1]!	@ zero_extendqisi2
	ldrsb	ip, [r5, #1]!
	sxtb	r1, r2
	cmp	ip, r1
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, #0
	beq	.L1998
	cmp	r0, #5
	bhi	.L1999
	add	r2, r6, #48
	add	r10, r6, #112
	mov	r1, r7
.L2000:
	ldr	lr, [r2, #4]!
	ldr	ip, [r1, #4]!
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r10
	bne	.L2000
.L1998:
	add	r0, r0, #1
	add	r8, r8, #256
	cmp	r0, #8
	add	r9, r9, #256
	add	r6, r6, #64
	add	r7, r7, #64
	bne	.L2002
	ldr	r5, [fp, #-48]
	ldr	r1, [fp, #-52]
.L1997:
	ldr	r2, [r1, #2196]
	ldr	ip, [r5, #2200]
	ldr	r0, [r1, #2200]
	ldr	lr, [r5, #2196]
	cmp	ip, r0
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	beq	.L2004
	cmp	ip, #1
	bne	.L2003
	ldr	r0, [r1, #2208]
	ldr	ip, [r5, #2208]
	ldrb	r2, [r5, #16]	@ zero_extendqisi2
	ldrb	r6, [r1, #16]	@ zero_extendqisi2
	ldr	r4, [r5, #2212]
	cmp	ip, r0
	cmpeq	r2, r6
	ldr	lr, [r1, #2212]
	ldr	r6, [r5, #2216]
	ldr	ip, [r1, #2216]
	moveq	r0, #1
	movne	r0, #0
	cmp	r4, lr
	movne	r2, #0
	andeq	r2, r0, #1
	cmp	r6, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r6, #0
	and	r3, r3, r2
	beq	.L2003
	add	ip, r5, #2208
	add	r0, r1, #2208
	add	ip, ip, #8
	add	r0, r0, #8
	mov	r2, #0
.L2006:
	ldr	r4, [ip, #4]!
	add	r2, r2, #1
	ldr	lr, [r0, #4]!
	cmp	r4, lr
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r6
	bne	.L2006
.L2003:
	ldrb	ip, [r1, #17]	@ zero_extendqisi2
	ldrb	lr, [r5, #17]	@ zero_extendqisi2
	ldr	r0, [r5, #3244]
	ldr	r4, [r1, #3244]
	ldr	r2, [r5, #3248]
	cmp	lr, ip
	cmpeq	r0, r4
	ldr	r7, [r1, #3248]
	ldr	r6, [r5, #3252]
	ldr	r4, [r1, #3252]
	moveq	ip, #1
	movne	ip, #0
	ldrb	lr, [r1, #18]	@ zero_extendqisi2
	cmp	r2, r7
	movne	r0, #0
	andeq	r0, ip, #1
	ldrb	ip, [r5, #18]	@ zero_extendqisi2
	cmp	r6, r4
	movne	r2, #0
	andeq	r2, r0, #1
	cmp	lr, ip
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2007
	ldrb	r0, [r5, #19]	@ zero_extendqisi2
	ldrb	r2, [r1, #19]	@ zero_extendqisi2
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
.L2007:
	ldrb	r2, [r1, #20]	@ zero_extendqisi2
	ldrb	ip, [r5, #21]	@ zero_extendqisi2
	ldrb	r0, [r1, #21]	@ zero_extendqisi2
	ldrb	lr, [r5, #20]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	lr, r2
	moveq	r2, #1
	movne	r2, #0
	cmp	ip, #0
	and	r3, r3, r2
	bne	.L2027
.L2008:
	ldrb	r2, [r5, #22]	@ zero_extendqisi2
	ldr	r0, [r5, #3316]
	ldr	ip, [r1, #3316]
	ldrb	r1, [r1, #22]	@ zero_extendqisi2
	cmp	r0, ip
	cmpeq	r2, r1
	moveq	r2, #1
	movne	r2, #0
	tst	r3, r2
	mvneq	r0, #0
	movne	r0, #0
.L1995:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2027:
	ldr	ip, [r1, #3260]
	ldr	lr, [r5, #3260]
	ldr	r0, [r5, #3256]
	ldr	r4, [r1, #3256]
	ldr	r2, [r1, #3264]
	cmp	lr, ip
	cmpeq	r0, r4
	ldr	r6, [r5, #3264]
	ldr	r4, [r5, #3268]
	ldr	lr, [r1, #3268]
	moveq	ip, #1
	movne	ip, #0
	cmp	r6, r2
	movne	r0, #0
	andeq	r0, ip, #1
	cmp	r4, lr
	movne	r2, #0
	andeq	r2, r0, #1
	and	r3, r3, r2
	b	.L2008
.L1999:
	sub	r2, r8, #1104
	sub	r10, r8, #848
	mov	r1, r9
.L2001:
	ldr	lr, [r2, #4]!
	ldr	ip, [r1, #4]!
	cmp	lr, ip
	movne	r3, #0
	andeq	r3, r3, #1
	cmp	r2, r10
	bne	.L2001
	b	.L1998
.L2004:
	ldr	r0, [r5, #2204]
	ldr	r2, [r1, #2204]
	cmp	r0, r2
	movne	r3, #0
	andeq	r3, r3, #1
	b	.L2003
.L2026:
	mov	r0, r1
	mov	r3, #9536
	ldr	r2, .L2028
	ldr	r1, .L2028+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1995
.L2025:
	movw	r3, #9535
	ldr	r2, .L2028
	ldr	r1, .L2028+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L1995
.L2029:
	.align	2
.L2028:
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	SPSEqual, .-SPSEqual
	.global	__aeabi_idiv
	.align	2
	.global	H264GetDar
	.type	H264GetDar, %function
H264GetDar:
	UNWIND(.fnstart)
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	subs	r4, r0, #0
	mov	lr, r1
	mov	r5, r3
	beq	.L2056
	subs	r1, r4, #255
	movne	r1, #1
	cmp	r4, #16
	movle	r0, #0
	andgt	r0, r1, #1
	cmp	r0, #0
	bne	.L2043
	cmp	r2, #0
	cmpne	lr, #0
	moveq	ip, #1
	movne	ip, #0
	cmp	r4, #255
	movne	ip, #0
	andeq	ip, ip, #1
	cmp	ip, #0
	bne	.L2044
	cmp	r4, #1
	beq	.L2057
	cmp	r1, #0
	ldrne	r0, .L2059
	addne	r4, r0, r4, lsl #3
	ldrne	r2, [r4, #120]
	ldrne	lr, [r4, #116]
	mov	r1, r2
	mov	r0, lr, asl #10
	bl	__aeabi_idiv
	ldr	r1, [fp, #4]
	mov	r4, r0
	mov	r0, r5, asl #10
	bl	__aeabi_idiv
	movw	r3, #2405
	movw	r1, #2262
	mul	r0, r0, r4
	add	r2, r0, #1020
	cmp	r0, #0
	add	r2, r2, #3
	movlt	r0, r2
	mov	r2, r0, asr #10
	cmp	r2, r3
	rsble	r3, r2, #2400
	subgt	r3, r2, #2400
	addle	r3, r3, #6
	subgt	r3, r3, #6
	cmp	r2, r1
	ble	.L2058
	sub	r1, r2, #2256
	sub	r1, r1, #7
	cmp	r3, r1
	bge	.L2037
.L2049:
	mov	r4, #4
	b	.L2031
.L2043:
	mov	r4, #0
.L2056:
	mov	r2, r4
.L2031:
	mov	r3, r4
	ldr	r1, .L2059+4
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2058:
	rsb	r1, r2, #2256
	add	r1, r1, #7
	cmp	r3, r1
	blt	.L2049
.L2037:
	movw	r3, #1819
	cmp	r2, r3
	bgt	.L2038
	rsb	r3, r2, #1808
	add	r3, r3, #12
	cmp	r1, r3
	blt	.L2051
.L2039:
	movw	r1, #1364
	cmp	r2, r1
	rsble	r4, r2, #1360
	subgt	r4, r2, #1360
	addle	r4, r4, #5
	subgt	r4, r4, #5
	cmp	r3, r4
	movlt	r4, #2
	movge	r4, #1
	b	.L2031
.L2057:
	ldr	r3, [fp, #4]
	sub	r3, r3, #1072
	sub	r3, r3, #8
	bics	r3, r3, #8
	moveq	r2, #1
	movne	r2, #0
	cmp	r5, #1920
	movne	r2, #0
	andeq	r2, r2, #1
	cmp	r2, #0
	movne	r2, ip
	movne	r4, #2
	bne	.L2031
	ldr	r3, [fp, #4]
	cmp	r5, #1280
	cmpeq	r3, #720
	moveq	r1, #1
	movne	r1, #0
	moveq	r4, #2
	beq	.L2031
	cmp	r5, #640
	cmpeq	r3, #480
	mov	r2, r1
	moveq	r4, #1
	movne	r4, #5
	b	.L2031
.L2044:
	mov	r4, r0
	mov	r2, r0
	b	.L2031
.L2038:
	sub	r3, r2, #1808
	sub	r3, r3, #12
	cmp	r1, r3
	bge	.L2039
.L2051:
	mov	r4, #3
	b	.L2031
.L2060:
	.align	2
.L2059:
	.word	.LANCHOR0
	.word	.LC224
	UNWIND(.fnend)
	.size	H264GetDar, .-H264GetDar
	.align	2
	.global	ProcessSPS
	.type	ProcessSPS, %function
ProcessSPS:
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
	UNWIND(.pad #52)
	sub	sp, sp, #52
	subs	r4, r1, #0
	mov	r5, r0
	beq	.L2178
	ldr	r2, [r4, #28]
	cmp	r2, #100
	cmpne	r2, #110
	moveq	r3, #1
	movne	r3, #0
	cmp	r2, #122
	orreq	r3, r3, #1
	cmp	r2, #144
	orreq	r3, r3, #1
	cmp	r2, #83
	orreq	r3, r3, #1
	cmp	r2, #86
	orreq	r3, r3, #1
	cmp	r3, #0
	streqb	r3, [r4, #25]
	moveq	r3, #1
	streq	r3, [r4, #40]
	bne	.L2179
.L2078:
	ldr	r1, .L2195
	mov	r0, r5
	bl	ue_v
	cmp	r0, #12
	str	r0, [r4, #2196]
	bhi	.L2091
	add	r6, r5, #61440
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2091
	ldr	r1, .L2195+4
	mov	r0, r5
	bl	ue_v
	cmp	r0, #2
	str	r0, [r4, #2200]
	bhi	.L2093
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2093
	cmp	r0, #0
	beq	.L2180
	cmp	r0, #1
	beq	.L2181
.L2098:
	ldr	r1, .L2195+8
	mov	r0, r5
	bl	ue_v
	str	r0, [r4, #3244]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	ldr	r1, .L2195+12
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #17]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	ldr	r1, .L2195+16
	mov	r0, r5
	bl	ue_v
	movw	r8, #509
	sub	r3, r0, #1
	str	r0, [r4, #3248]
	cmp	r3, r8
	bhi	.L2102
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2102
	ldr	r1, .L2195+20
	mov	r0, r5
	bl	ue_v
	str	r0, [r4, #3252]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	ldr	r1, .L2195+24
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #18]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	cmp	r0, #0
	bne	.L2182
	ldr	r1, .L2195+28
	mov	r0, r5
	bl	u_1
	ldr	r7, [r4, #3252]
	add	r7, r7, #1
	cmp	r7, #255
	strb	r0, [r4, #19]
	bhi	.L2134
	ldr	r3, [r4, #3248]
	add	r3, r3, #1
	cmp	r7, #1
	cmphi	r3, #3
	movhi	r9, #2
	bls	.L2134
.L2106:
	mul	r7, r7, r9
	mov	r10, r3, asl #4
	mov	r7, r7, asl #4
	mul	r1, r10, r7
	add	r1, r1, r1, lsr #1
	cmp	r1, #100663296
	bhi	.L2183
	ldr	r2, [r4, #32]
	sub	r3, r2, #10
	cmp	r3, #31
	ldrls	pc, [pc, r3, asl #2]
	b	.L2108
.L2110:
	.word	.L2109
	.word	.L2111
	.word	.L2141
	.word	.L2141
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2141
	.word	.L2113
	.word	.L2115
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2115
	.word	.L2116
	.word	.L2117
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2108
	.word	.L2119
	.word	.L2119
.L2179:
	ldr	r1, .L2195+32
	bl	ue_v
	cmp	r0, #1
	str	r0, [r4, #40]
	bls	.L2184
.L2065:
	mov	r2, r0
	ldr	r1, .L2195+36
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, .L2195+40
	mov	r0, r5
	bl	ue_v
	uxth	r0, r0
	add	r2, r0, #8
	str	r2, [r4, #44]
	cmp	r2, #8
	beq	.L2185
.L2067:
	ldr	r1, .L2195+44
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2195+48
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2176
	ldr	r1, [r4, #44]
	add	r5, r5, #61440
	mov	lr, #0
	mov	r3, #8
	ldr	r0, [r5, #2344]
	sub	r2, fp, #68
	str	r1, [fp, #-64]
	mov	r1, #119
	str	lr, [fp, #-68]
	blx	ip
	mvn	r0, #0
.L2169:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2184:
	add	r6, r5, #61440
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2065
	ldr	r1, .L2195+40
	mov	r0, r5
	bl	ue_v
	uxth	r0, r0
	add	r2, r0, #8
	str	r2, [r4, #44]
	cmp	r2, #8
	bne	.L2069
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	beq	.L2070
.L2069:
	ldr	r1, .L2195+44
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2195+48
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2070
	ldr	r0, [r4, #44]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-68]
	mov	r1, #119
	sub	r2, fp, #68
	str	r0, [fp, #-64]
	ldr	r0, [r6, #2344]
	blx	ip
.L2070:
	ldr	r1, .L2195+52
	mov	r0, r5
	bl	ue_v
	uxth	r0, r0
	add	r2, r0, #8
	str	r2, [r4, #48]
	cmp	r2, #8
	bne	.L2072
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2072
.L2073:
	ldr	r1, .L2195+56
	mov	r0, r5
	bl	u_1
	cmp	r0, #0
	bne	.L2075
	ldr	r6, [r6, #2284]
	cmp	r6, #0
	bne	.L2075
	ldr	r1, .L2195+60
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #25]
	cmp	r0, #1
	bne	.L2078
	add	r10, r4, #1968
	sub	r7, fp, #72
	add	r10, r10, #4
	add	r9, r4, #3
	add	r8, r4, #52
	b	.L2084
.L2188:
	ldr	r3, .L2195+64
	cmp	r1, #0
	add	ip, r3, #16
	moveq	r3, ip
	mov	r1, r3
	ldr	r3, .L2195+68
	ldr	r3, [r3, #52]
	blx	r3
.L2080:
	add	r6, r6, #1
	add	r10, r10, #16
	cmp	r6, #6
	add	r8, r8, #64
	beq	.L2186
.L2084:
	ldr	r1, .L2195+72
	mov	r0, r5
	bl	u_1
	clz	r1, r6
	mov	r2, #16
	mov	r1, r1, lsr #5
	cmp	r0, #1
	mov	r3, r0
	mov	r0, r10
	str	r3, [r7, #4]!
	strb	r3, [r9, #1]!
	beq	.L2187
	cmp	r6, #0
	cmpne	r6, #3
	beq	.L2188
	ldr	r3, .L2195+68
	mov	r2, #16
	sub	r1, r10, #16
	mov	r0, r10
	ldr	r3, [r3, #52]
	blx	r3
	b	.L2080
.L2185:
	add	r3, r5, #61440
	ldr	r3, [r3, #2284]
	cmp	r3, #0
	bne	.L2067
.L2176:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2180:
	ldr	r1, .L2195+76
	mov	r0, r5
	bl	ue_v
	cmp	r0, #12
	str	r0, [r4, #2204]
	bhi	.L2096
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	beq	.L2098
.L2096:
	ldr	r1, .L2195+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2072:
	ldr	r1, .L2195+84
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L2195+48
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2073
	ldr	r0, [r4, #48]
	mov	r2, #0
	mov	r3, #8
	str	r2, [fp, #-68]
	mov	r1, #119
	sub	r2, fp, #68
	str	r0, [fp, #-64]
	ldr	r0, [r6, #2344]
	blx	ip
	b	.L2073
.L2182:
	ldr	r7, [r4, #3252]
	strb	r3, [r4, #19]
	sub	r3, r7, #1
	cmp	r3, r8
	bhi	.L2134
	ldr	r3, [r4, #3248]
	mov	r9, #1
	add	r7, r7, #1
	add	r3, r3, r9
	b	.L2106
.L2141:
	mov	r0, #60416
	movt	r0, 13
.L2112:
	bl	__aeabi_uidiv
	ldr	r1, .L2195+88
	cmp	r0, #16
	movcc	r8, r0
	movcs	r8, #16
	mov	r2, r8
	mov	r0, #21
	bl	dprint_vfmw
	ldr	r2, [r4, #3244]
	cmp	r2, r8
	bhi	.L2120
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	beq	.L2121
.L2120:
	mov	r3, r8
	ldr	r1, .L2195+92
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #3244]
	cmp	r3, #16
	bhi	.L2173
	cmp	r8, r3
	movcc	r8, r3
.L2173:
	str	r8, [r4, #3244]
.L2121:
	ldr	r1, .L2195+96
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #20]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	ldr	r1, .L2195+100
	mov	r0, r5
	bl	u_1
	uxtb	r0, r0
	strb	r0, [r4, #21]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	cmp	r0, #0
	bne	.L2189
.L2123:
	mov	r2, r10, lsr #1
	mov	r3, r7, lsr #1
	str	r10, [r4, #3276]
	str	r7, [r4, #3280]
	str	r2, [r4, #3284]
	str	r3, [r4, #3288]
.L2125:
	ldr	r1, .L2195+104
	mov	r0, r5
	bl	u_1
	uxtb	r3, r0
	strb	r3, [r4, #22]
	ldr	r2, [r6, #2284]
	cmp	r2, #0
	bne	.L2176
	cmp	r3, #0
	mov	r2, #2
	str	r2, [r4, #3332]
	bne	.L2190
	mov	r0, r3
	strb	r3, [r4, #3307]
	mov	r3, #5
	str	r3, [r4, #3320]
.L2128:
	ldr	r2, [r4, #3312]
	mov	r3, r10
	ldr	r1, [r4, #3308]
	str	r7, [sp]
	bl	H264GetDar
	ldr	r3, [r4, #3244]
	cmp	r3, #0
	str	r0, [r4, #3316]
	beq	.L2131
	ldr	r2, [r4, #3372]
	cmp	r3, r2
	bls	.L2131
	cmp	r8, r3
	movcs	r8, r3
.L2131:
	cmp	r8, #16
	add	r3, r5, #12288
	movcs	r8, #16
	str	r8, [r3, #1296]
	ldr	r3, [r5]
	ldr	r2, [r3, #28]
	cmp	r2, #25
	beq	.L2191
.L2132:
	add	r8, r8, #1
	mov	r0, #0
	str	r8, [r4, #3272]
	b	.L2169
.L2119:
	mov	r0, #12582912
	b	.L2112
.L2115:
	mov	r0, #30208
	movt	r0, 47
	b	.L2112
.L2111:
	mov	r0, #17920
	movt	r0, 5
	b	.L2112
.L2109:
	mov	r0, #20992
	movt	r0, 2
	b	.L2112
.L2117:
	mov	r0, #7864320
	b	.L2112
.L2116:
	mov	r0, #30720
	movt	r0, 105
	b	.L2112
.L2113:
	mov	r0, #55296
	movt	r0, 27
	b	.L2112
.L2108:
	ldr	r1, .L2195+108
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2091:
	ldr	r1, .L2195+112
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2134:
	ldr	r1, .L2195+116
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2189:
	ldr	r1, .L2195+120
	mov	r0, r5
	bl	ue_v
	ldr	r1, .L2195+124
	str	r0, [r4, #3256]
	mov	r0, r5
	bl	ue_v
	ldr	r1, .L2195+128
	str	r0, [r4, #3260]
	mov	r0, r5
	bl	ue_v
	ldr	r1, .L2195+132
	str	r0, [r4, #3264]
	mov	r0, r5
	bl	ue_v
	ldr	r2, [r4, #3264]
	ldr	r1, [r4, #3256]
	mov	ip, r9, asl #1
	ldr	r3, [r4, #3260]
	mov	r2, r2, asl #1
	mov	r1, r1, asl #1
	mul	r9, r9, r2
	rsb	r2, r1, r10
	sub	r3, r2, r3, asl #1
	rsb	r2, r9, r7
	str	r0, [r4, #3268]
	mls	r0, r0, ip, r2
	cmp	r3, #0
	cmpgt	r0, #0
	ble	.L2123
	add	r1, r1, r3, lsr #1
	add	r9, r9, r0, lsr #1
	str	r1, [r4, #3284]
	str	r9, [r4, #3288]
	str	r3, [r4, #3276]
	str	r0, [r4, #3280]
	b	.L2125
.L2190:
	add	r1, r4, #3280
	mov	r0, r5
	add	r1, r1, #12
	bl	vui_parameters
	cmp	r0, #0
	bne	.L2175
	ldrb	r3, [r4, #3304]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2175
	ldr	r2, [r4, #3372]
	clz	r3, r2
	mov	r3, r3, lsr #5
	cmp	r8, r2
	orrcc	r3, r3, #1
	cmp	r3, #0
	bne	.L2192
	ldr	r3, [r4, #3244]
	ldrb	r0, [r4, #3307]	@ zero_extendqisi2
	cmp	r2, r3
	movcs	r8, r2
	movcc	r8, r3
	b	.L2128
.L2191:
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L2132
	ldr	r2, [r3, #708]
	ldr	r1, [r3, #684]
	cmp	r8, r2
	ldr	r0, [r3, #688]
	bls	.L2133
	ldr	r3, .L2195+48
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2176
	str	r2, [fp, #-72]
	mov	r3, #8
	str	r8, [fp, #-76]
	sub	r2, fp, #76
	ldr	r0, [r6, #2344]
	mov	r1, #106
	blx	ip
	mvn	r0, #0
	b	.L2169
.L2192:
	mov	r3, r8
	ldr	r1, .L2195+136
	mov	r0, #1
	bl	dprint_vfmw
.L2175:
	ldrb	r0, [r4, #3307]	@ zero_extendqisi2
	b	.L2128
.L2186:
	add	r6, r4, #2064
	sub	r7, fp, #88
	add	r6, r6, #4
	add	r9, r4, #9
	add	r8, r4, #436
	mov	r10, #0
.L2089:
	ldr	r1, .L2195+72
	mov	r0, r5
	bl	u_1
	mov	r2, #64
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r6
	str	r3, [r7, #4]!
	strb	r3, [r9, #1]!
	beq	.L2193
	ldr	r1, .L2195+140
	cmp	r10, #0
	ldr	r3, .L2195+68
	add	ip, r1, #64
	ldr	r3, [r3, #52]
	movne	r1, ip
	blx	r3
.L2086:
	add	r10, r10, #1
	add	r6, r6, #64
	cmp	r10, #2
	add	r8, r8, #256
	bne	.L2089
	b	.L2078
.L2181:
	ldr	r1, .L2195+144
	mov	r0, r5
	bl	u_1
	strb	r0, [r4, #16]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	ldr	r1, .L2195+148
	mov	r0, r5
	bl	se_v
	str	r0, [r4, #2208]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	ldr	r1, .L2195+152
	mov	r0, r5
	bl	se_v
	str	r0, [r4, #2212]
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	bne	.L2176
	ldr	r1, .L2195+156
	mov	r0, r5
	bl	ue_v
	cmp	r0, #255
	str	r0, [r4, #2216]
	bhi	.L2099
	ldr	r7, [r6, #2284]
	cmp	r7, #0
	bne	.L2099
	cmp	r0, #0
	addne	r8, r4, #2208
	addne	r8, r8, #8
	bne	.L2101
	b	.L2098
.L2194:
	ldr	r3, [r4, #2216]
	cmp	r3, r7
	bls	.L2098
.L2101:
	ldr	r1, .L2195+160
	mov	r0, r5
	bl	se_v
	add	r7, r7, #1
	str	r0, [r8, #4]!
	ldr	r3, [r6, #2284]
	cmp	r3, #0
	beq	.L2194
	b	.L2176
.L2187:
	mov	r3, r2
	str	r7, [sp]
	mov	r2, r10
	mov	r1, r8
	mov	r0, r5
	bl	Scaling_List
	ldr	r3, [r7]
	cmp	r3, #1
	bne	.L2080
	ldr	r1, .L2195+64
	mov	r2, #16
	ldr	r3, .L2195+68
	cmp	r6, #2
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movhi	r1, r0
	mov	r0, r10
	blx	r3
	b	.L2080
.L2102:
	mov	r2, r0
	ldr	r1, .L2195+164
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2093:
	ldr	r1, .L2195+168
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2075:
	ldr	r1, .L2195+172
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2193:
	mov	r3, r2
	str	r7, [sp]
	mov	r2, r6
	mov	r1, r8
	mov	r0, r5
	bl	Scaling_List
	ldr	r3, [r7]
	cmp	r3, #1
	bne	.L2086
	ldr	r1, .L2195+140
	mov	r2, #64
	ldr	r3, .L2195+68
	cmp	r10, #0
	add	r0, r1, r2
	ldr	r3, [r3, #52]
	movne	r1, r0
	mov	r0, r6
	blx	r3
	b	.L2086
.L2133:
	cmp	r1, r10
	cmpcs	r0, r7
	bcs	.L2132
	ldr	r3, .L2195+48
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L2176
	strh	r1, [fp, #-72]	@ movhi
	mov	r3, #8
	strh	r0, [fp, #-70]	@ movhi
	sub	r2, fp, #76
	strh	r10, [fp, #-76]	@ movhi
	mov	r1, #107
	strh	r7, [fp, #-74]	@ movhi
	ldr	r0, [r6, #2344]
	blx	ip
	b	.L2176
.L2178:
	mov	r0, r4
	movw	r3, #9742
	ldr	r2, .L2195+176
	ldr	r1, .L2195+180
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2183:
	ldr	r1, .L2195+184
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2099:
	ldr	r1, .L2195+188
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2169
.L2196:
	.align	2
.L2195:
	.word	.LC234
	.word	.LC236
	.word	.LC239
	.word	.LC247
	.word	.LC248
	.word	.LC250
	.word	.LC251
	.word	.LC265
	.word	.LC225
	.word	.LC226
	.word	.LC227
	.word	.LC228
	.word	g_event_report
	.word	.LC229
	.word	.LC231
	.word	.LC233
	.word	.LANCHOR1+80
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC171
	.word	.LC238
	.word	.LC240
	.word	.LC230
	.word	.LC255
	.word	.LC256
	.word	.LC257
	.word	.LC258
	.word	.LC263
	.word	.LC254
	.word	.LC235
	.word	.LC252
	.word	.LC259
	.word	.LC260
	.word	.LC261
	.word	.LC262
	.word	.LC264
	.word	.LANCHOR1+112
	.word	.LC241
	.word	.LC242
	.word	.LC243
	.word	.LC244
	.word	.LC246
	.word	.LC249
	.word	.LC237
	.word	.LC232
	.word	.LC21
	.word	.LC22
	.word	.LC253
	.word	.LC245
	UNWIND(.fnend)
	.size	ProcessSPS, .-ProcessSPS
	.align	2
	.global	Sps_SvcExt
	.type	Sps_SvcExt, %function
Sps_SvcExt:
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
	add	r1, r0, #12288
	add	r2, r0, #20480
	mov	lr, #2208
	ldr	r3, [r1, #1304]
	mov	r4, r0
	ldr	r2, [r2, #216]
	add	r0, r0, #13504
	ldr	ip, [r1, #1300]
	mov	r5, #4000
	mov	r1, #32
	add	r0, r0, #24
	mla	r3, lr, r2, r3
	ldr	r3, [r3, #28]
	mla	r5, r5, r3, ip
	bl	BsGet
	ldr	r1, .L2211
	mov	r6, r0
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2211+4
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	mov	r0, r4
	ldr	r2, .L2211+8
	mov	r1, #2
	bl	u_v
	cmp	r0, #1
	beq	.L2207
	ldr	r2, [r5, #40]
	sub	r1, r2, #1
	cmp	r1, #1
	bls	.L2208
.L2200:
	cmp	r2, #1
	beq	.L2209
.L2201:
	ldr	r1, .L2211+12
	mov	r0, r4
	bl	u_1
	cmp	r0, #0
	bne	.L2210
.L2202:
	mov	r0, r4
	ldr	r1, .L2211+16
	bl	u_1
	cmp	r0, #1
	moveq	r0, #0
	beq	.L2199
	ldr	ip, [r5, #40]
	mov	r2, r0
	mov	r3, r6
	ldr	r1, .L2211+20
	mov	r0, #1
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r0, #0
.L2199:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2210:
	ldr	r1, .L2211+24
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2211+28
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	b	.L2202
.L2209:
	ldr	r2, .L2211+32
	mov	r1, #2
	mov	r0, r4
	bl	u_v
	ldr	r1, .L2211+36
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	b	.L2201
.L2208:
	ldr	r1, .L2211+40
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2211+44
	mov	r2, r0
	mov	r0, #17
	bl	dprint_vfmw
	ldr	r2, [r5, #40]
	b	.L2200
.L2207:
	ldr	r1, .L2211+48
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2199
.L2212:
	.align	2
.L2211:
	.word	.LC266
	.word	.LC267
	.word	.LC268
	.word	.LC274
	.word	.LC277
	.word	.LC278
	.word	.LC275
	.word	.LC276
	.word	.LC272
	.word	.LC273
	.word	.LC270
	.word	.LC271
	.word	.LC269
	UNWIND(.fnend)
	.size	Sps_SvcExt, .-Sps_SvcExt
	.align	2
	.global	H264_DecSPS
	.type	H264_DecSPS, %function
H264_DecSPS:
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
	ldr	r2, .L2248
	mov	r1, #8
	mov	r4, r0
	add	r7, r0, #61440
	bl	u_v
	ldr	r1, .L2248+4
	mov	r10, r0
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2248+8
	str	r0, [fp, #-56]
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2248+12
	str	r0, [fp, #-60]
	mov	r0, r4
	bl	u_1
	ldr	r1, .L2248+16
	str	r0, [fp, #-64]
	mov	r0, r4
	bl	u_1
	ldr	r2, .L2248+20
	mov	r1, #4
	str	r0, [fp, #-68]
	mov	r0, r4
	bl	u_v
	ldr	r2, .L2248+24
	mov	r1, #8
	mov	r0, r4
	bl	u_v
	ldr	r1, .L2248+28
	mov	r6, r0
	mov	r0, r4
	bl	ue_v
	ldr	r2, [r7, #2284]
	cmp	r2, #0
	mov	r9, r0
	bne	.L2242
	add	r5, r4, #12288
	ldr	r2, [r5, #1288]
	sub	r2, r2, #1
	cmp	r0, r2
	bhi	.L2243
	sub	r2, r10, #66
	mov	r8, r10
	cmp	r2, #78
	ldrls	pc, [pc, r2, asl #2]
	b	.L2218
.L2220:
	.word	.L2219
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2221
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2221
	.word	.L2218
	.word	.L2218
	.word	.L2221
	.word	.L2218
	.word	.L2222
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2221
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2223
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2223
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2218
	.word	.L2223
.L2219:
	ldr	r1, .L2248+32
	mov	r0, #1
	bl	dprint_vfmw
.L2221:
	cmp	r6, #9
	mov	r2, r6
	bls	.L2241
.L2247:
	cmp	r6, #41
	bhi	.L2241
.L2225:
	mov	r3, #4000
	ldr	r1, [r5, #1300]
	mul	r7, r3, r9
	add	r1, r1, r7
	ldrb	r6, [r1, #23]	@ zero_extendqisi2
	cmp	r6, #0
	beq	.L2226
	ldr	r6, .L2248+36
	mov	r0, r4
	str	r3, [fp, #-72]
	ldrb	r3, [fp, #-56]	@ zero_extendqisi2
	add	r1, r6, #2208
	str	r8, [r6, #2236]
	str	r2, [r6, #2240]
	strb	r3, [r6, #2208]
	ldrb	r3, [fp, #-60]	@ zero_extendqisi2
	str	r9, [r6, #2244]
	strb	r3, [r6, #2209]
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	strb	r3, [r6, #2210]
	ldrb	r3, [fp, #-68]	@ zero_extendqisi2
	strb	r3, [r6, #2211]
	bl	ProcessSPS
	ldr	r3, [fp, #-72]
	cmp	r0, #0
	bne	.L2244
	ldr	r1, [r5, #1300]
	add	r0, r6, #2208
	str	r3, [fp, #-56]
	add	r1, r1, r7
	bl	SPSEqual
	ldr	r3, [fp, #-56]
	cmp	r0, #0
	bne	.L2245
.L2228:
	cmp	r8, #83
	cmpne	r8, #86
	beq	.L2230
.L2231:
	mov	r0, #0
.L2215:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2241:
	mov	r3, #41
	ldr	r1, .L2248+40
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, #41
	b	.L2225
.L2226:
	str	r8, [r1, #28]
	mov	r0, r4
	ldr	r3, [r5, #1300]
	ldrb	r1, [fp, #-56]	@ zero_extendqisi2
	strb	r1, [r3, r7]
	ldr	r3, [r5, #1300]
	ldrb	r1, [fp, #-60]	@ zero_extendqisi2
	add	r3, r3, r7
	strb	r1, [r3, #1]
	ldr	r3, [r5, #1300]
	ldrb	r1, [fp, #-64]	@ zero_extendqisi2
	add	r3, r3, r7
	strb	r1, [r3, #2]
	ldr	r3, [r5, #1300]
	ldrb	r1, [fp, #-68]	@ zero_extendqisi2
	add	r3, r3, r7
	strb	r1, [r3, #3]
	ldr	r3, [r5, #1300]
	add	r3, r3, r7
	str	r2, [r3, #32]
	ldr	r3, [r5, #1300]
	add	r3, r3, r7
	str	r9, [r3, #36]
	ldr	r1, [r5, #1300]
	add	r1, r1, r7
	bl	ProcessSPS
	cmp	r0, #0
	bne	.L2246
	ldr	r3, [r5, #1300]
	mov	r2, #1
	cmp	r8, #83
	cmpne	r8, #86
	add	r3, r3, r7
	strb	r2, [r3, #24]
	ldr	r3, [r5, #1300]
	add	r7, r3, r7
	strb	r2, [r7, #23]
	bne	.L2231
.L2230:
	mov	r0, r4
	bl	Sps_SvcExt
	cmp	r0, #0
	beq	.L2231
	ldr	r1, .L2248+44
	mov	r0, #1
	bl	dprint_vfmw
.L2242:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2243:
	ldr	r1, .L2248+48
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #1288]
	sub	r3, r2, #1
	cmp	r9, r3
	bls	.L2242
	ldr	r3, .L2248+52
	ldr	r4, [r3]
	cmp	r4, #0
	beq	.L2242
	str	r2, [fp, #-48]
	mov	r3, #8
	str	r9, [fp, #-52]
	sub	r2, fp, #52
	ldr	r0, [r7, #2344]
	mov	r1, #109
	blx	r4
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2223:
	ldr	r1, .L2248+56
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r6, #9
	mov	r2, r6
	bhi	.L2247
	b	.L2241
.L2222:
	ldr	r1, .L2248+60
	mov	r0, #1
	bl	dprint_vfmw
	cmp	r6, #9
	mov	r2, r6
	bhi	.L2247
	b	.L2241
.L2218:
	mov	r2, r10
	ldr	r1, .L2248+64
	mov	r0, #1
	mov	r8, #100
	bl	dprint_vfmw
	cmp	r6, #9
	mov	r2, r6
	bhi	.L2247
	b	.L2241
.L2245:
	ldr	ip, .L2248+68
	mov	r2, r3
	ldr	r0, [r5, #1300]
	mov	r3, #1
	add	r1, r6, #2208
	strb	r3, [r6, #2232]
	add	r0, r0, r7
	ldr	ip, [ip, #56]
	strb	r3, [r6, #2231]
	blx	ip
	b	.L2228
.L2244:
	mov	r3, r9
	movw	r2, #10356
	ldr	r1, .L2248+72
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2215
.L2246:
	mov	r3, r9
	movw	r2, #10381
	ldr	r1, .L2248+72
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r5, #1300]
	mov	r2, #1
	mvn	r0, #0
	add	r3, r3, r7
	strb	r2, [r3, #24]
	ldr	r3, [r5, #1300]
	add	r7, r3, r7
	strb	r6, [r7, #23]
	b	.L2215
.L2249:
	.align	2
.L2248:
	.word	.LC279
	.word	.LC280
	.word	.LC281
	.word	.LC282
	.word	.LC283
	.word	.LC284
	.word	.LC285
	.word	.LC286
	.word	.LC287
	.word	.LANCHOR2
	.word	.LC291
	.word	.LC293
	.word	.LC177
	.word	g_event_report
	.word	.LC289
	.word	.LC288
	.word	.LC290
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC292
	UNWIND(.fnend)
	.size	H264_DecSPS, .-H264_DecSPS
	.align	2
	.global	PassBytes
	.type	PassBytes, %function
PassBytes:
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
	ldr	ip, [r0, #368]
	cmp	ip, #0
	cmpne	r1, #0
	beq	.L2259
	ldrb	r3, [ip]	@ zero_extendqisi2
	mov	r2, r3, asl #2
	mov	r5, r3, asl #5
	rsb	r4, r2, r5
	add	r4, ip, r4
	add	r6, r4, #8
	ldr	lr, [r4, #8]
	cmp	lr, #0
	beq	.L2259
	ldr	lr, [ip, #68]
	cmp	r3, #1
	cmpls	lr, #2
	bhi	.L2259
	cmp	lr, r3
	bls	.L2259
	ldr	lr, [r4, #12]
	mov	r6, r2
	ldr	r4, [r4, #24]
	mov	lr, lr, asl #3
	add	r1, r4, r1, lsl #3
	cmp	r1, lr
	bhi	.L2254
	b	.L2252
.L2255:
	ldr	r4, [r2, #24]
	ldr	r2, [r2, #12]
	rsb	lr, lr, r4
	add	r1, r1, lr
	mov	lr, r2, asl #3
	cmp	r1, lr
	bls	.L2252
.L2254:
	rsb	r2, r6, r5
	add	r3, r3, #1
	add	ip, ip, r2
	mov	r6, r3, asl #2
	mov	r5, r3, asl #5
	str	lr, [ip, #24]
	rsb	r2, r6, r5
	ldr	ip, [r0, #368]
	ldrb	r4, [ip]	@ zero_extendqisi2
	add	r4, r4, #1
	strb	r4, [ip]
	ldr	ip, [r0, #368]
	add	r2, ip, r2
	ldr	r4, [ip, #68]
	cmp	r4, r3
	bhi	.L2255
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2252:
	rsb	r2, r6, r5
	mov	r0, #1
	add	ip, ip, r2
	str	r1, [ip, #24]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L2259:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	PassBytes, .-PassBytes
	.align	2
	.global	GetBytes
	.type	GetBytes, %function
GetBytes:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	cmp	r1, #0
	beq	.L2274
	ldr	r3, [r0, #368]
	cmp	r3, #0
	cmpne	r2, #0
	ble	.L2274
	ldrb	r7, [r3]	@ zero_extendqisi2
	mov	ip, r7, asl #5
	sub	ip, ip, r7, asl #2
	add	ip, r3, ip
	ldr	ip, [ip, #8]
	cmp	ip, #0
	beq	.L2274
	ldr	ip, [r3, #68]
	cmp	r7, #1
	cmpls	ip, #2
	movhi	lr, #1
	movls	lr, #0
	bhi	.L2274
	cmp	ip, r7
	bls	.L2274
.L2269:
	mov	r5, r7, asl #5
	sub	r5, r5, r7, asl #2
	add	r3, r3, r5
	ldr	r4, [r3, #24]
	ldr	r8, [r3, #8]
	add	r4, r4, #7
	ldr	r6, [r3, #12]
	add	ip, r8, r4, lsr #3
	add	r6, r8, r6
	cmp	ip, r6
	bcs	.L2265
	ldrb	r3, [r8, r4, lsr #3]	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	lr, r2
	add	r4, r1, #1
	add	ip, ip, #1
	strb	r3, [r1]
	b	.L2276
.L2267:
	cmp	ip, r6
	mov	r1, r4
	beq	.L2265
	ldrb	r3, [ip], #1	@ zero_extendqisi2
	add	lr, lr, #1
	cmp	lr, r2
	strb	r3, [r4], #1
.L2276:
	ldr	r3, [r0, #368]
	add	r3, r3, r5
	ldr	r1, [r3, #24]
	add	r1, r1, #8
	str	r1, [r3, #24]
	bcc	.L2267
	mov	r0, r2
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2265:
	ldr	ip, [r0, #368]
	add	r7, r7, #1
	ldrb	r3, [ip]	@ zero_extendqisi2
	add	r3, r3, #1
	strb	r3, [ip]
	ldr	r3, [r0, #368]
	ldr	ip, [r3, #68]
	cmp	ip, r7
	bhi	.L2269
	mov	r0, lr
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2274:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
	UNWIND(.fnend)
	.size	GetBytes, .-GetBytes
	.align	2
	.global	H264_DecFramePackingSEI
	.type	H264_DecFramePackingSEI, %function
H264_DecFramePackingSEI:
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
	ldr	r1, .L2284
	mov	r5, r0
	bl	ue_v
	add	r4, r5, #24576
	ldr	r2, .L2284+4
	mov	r1, #1
	str	r0, [r4, #1832]
	mov	r0, r5
	bl	u_v
	uxtb	r0, r0
	strb	r0, [r4, #1809]
	cmp	r0, #0
	beq	.L2283
.L2278:
	mov	r0, r5
	ldr	r2, .L2284+8
	mov	r1, #1
	bl	u_v
	mov	r3, #1
	strb	r3, [r4, #1808]
	strb	r0, [r4, #1810]
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2283:
	ldr	r2, .L2284+12
	mov	r1, #7
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+16
	mov	r1, #1
	str	r0, [r4, #1824]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+20
	mov	r1, #6
	strb	r0, [r4, #1811]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+24
	mov	r1, #1
	str	r0, [r4, #1828]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+28
	mov	r1, #1
	strb	r0, [r4, #1812]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+32
	mov	r1, #1
	strb	r0, [r4, #1813]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+36
	mov	r1, #1
	strb	r0, [r4, #1814]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+40
	mov	r1, #1
	strb	r0, [r4, #1815]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+44
	mov	r1, #1
	strb	r0, [r4, #1816]
	mov	r0, r5
	bl	u_v
	ldrb	r3, [r4, #1811]	@ zero_extendqisi2
	cmp	r3, #0
	strb	r0, [r4, #1817]
	bne	.L2279
	ldr	r3, [r4, #1824]
	cmp	r3, #5
	beq	.L2279
	ldr	r2, .L2284+48
	mov	r1, #1
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+52
	mov	r1, #1
	strb	r0, [r4, #1818]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+56
	mov	r1, #1
	strb	r0, [r4, #1819]
	mov	r0, r5
	bl	u_v
	ldr	r2, .L2284+60
	mov	r1, #1
	strb	r0, [r4, #1820]
	mov	r0, r5
	bl	u_v
	strb	r0, [r4, #1821]
.L2279:
	ldr	r2, .L2284+64
	mov	r1, #8
	mov	r0, r5
	bl	u_v
	ldr	r1, .L2284+68
	str	r0, [r4, #1836]
	mov	r0, r5
	bl	ue_v
	str	r0, [r4, #1840]
	b	.L2278
.L2285:
	.align	2
.L2284:
	.word	.LC294
	.word	.LC295
	.word	.LC311
	.word	.LC296
	.word	.LC297
	.word	.LC298
	.word	.LC299
	.word	.LC300
	.word	.LC301
	.word	.LC302
	.word	.LC303
	.word	.LC304
	.word	.LC305
	.word	.LC306
	.word	.LC307
	.word	.LC308
	.word	.LC309
	.word	.LC310
	UNWIND(.fnend)
	.size	H264_DecFramePackingSEI, .-H264_DecFramePackingSEI
	.align	2
	.global	H264_Sei_Get_Dpb_Output_Time
	.type	H264_Sei_Get_Dpb_Output_Time, %function
H264_Sei_Get_Dpb_Output_Time:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	add	r2, r0, #12288
	add	r3, r0, #20480
	mov	r4, #2208
	add	r0, r0, #24576
	ldr	lr, [r2, #1304]
	mov	r1, #4000
	ldr	r3, [r3, #216]
	ldr	r6, [r2, #1300]
	ldr	ip, [r0, #1848]
	mla	r4, r4, r3, lr
	ldr	r3, [r0, #1860]
	ldr	lr, [r0, #1852]
	add	r3, r3, #1
	ldr	r2, [r0, #1864]
	subs	r5, r3, #1
	add	r2, r2, #1
	ldr	r4, [r4, #28]
	movne	r5, #1
	cmp	ip, #0
	str	ip, [r0, #1868]
	str	r2, [r0, #1864]
	mla	r1, r1, r4, r6
	movne	r5, #0
	cmp	r5, #0
	str	r3, [r0, #1860]
	str	lr, [r0, #1876]
	ldrne	ip, [r0, #1872]
	ldr	r2, [r1, #3344]
	addne	ip, ip, #2
	str	r2, [r0, #1912]
	ldr	r2, [r1, #3348]
	strne	ip, [r0, #1868]
	cmp	r3, #1
	str	r2, [r0, #1916]
	beq	.L2294
	ldrb	r3, [r0, #1936]	@ zero_extendqisi2
	add	r4, r0, #1856
	cmp	r3, #1
	ldrd	r2, [r4, #48]
	beq	.L2295
	adds	r2, r2, ip
	adc	r3, r3, #0
	strd	r2, [r4, #40]
.L2289:
	adds	r2, r2, lr
	mov	lr, #0
	adc	r3, r3, #0
	strb	lr, [r0, #1936]
	ldr	r4, [r1, #3368]
	movs	r3, r3, lsr #1
	mov	r2, r2, rrx
	ldr	r8, [r1, #3344]
	add	lr, r0, #1856
	subs	r6, r2, r4
	sbc	r7, r3, #0
	umull	r4, r5, r6, r8
	mla	r5, r8, r7, r5
	strd	r4, [lr, #24]
	ldr	r1, [r1, #3368]
	subs	r2, r2, r1
	sbc	r3, r3, #0
	strd	r2, [lr, #32]
	str	ip, [r0, #1872]
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2294:
	mov	r6, #0
	str	r6, [r0, #1896]
	mov	r2, r6
	mov	r3, r6
	str	r6, [r0, #1904]
	str	r6, [r0, #1900]
	str	r6, [r0, #1908]
	b	.L2289
.L2295:
	adds	r2, r2, ip
	adc	r3, r3, #0
	strd	r2, [r4, #40]
	strd	r2, [r4, #48]
	b	.L2289
	UNWIND(.fnend)
	.size	H264_Sei_Get_Dpb_Output_Time, .-H264_Sei_Get_Dpb_Output_Time
	.align	2
	.global	H264_Get_Last_IDR_Frame_Info
	.type	H264_Get_Last_IDR_Frame_Info, %function
H264_Get_Last_IDR_Frame_Info:
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
	cmp	r1, #5
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldr	r1, [r0]
	mvn	r3, #0
	mvn	r2, #0
	ldrd	r4, [r1, #56]
	cmp	r5, r3
	cmpeq	r4, r2
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	movw	r2, #26464
	add	r3, r0, #26368
	ldrd	r6, [r0, r2]
	movw	r2, #26496
	strd	r4, [r0, r2]
	strd	r6, [r3, #136]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	H264_Get_Last_IDR_Frame_Info, .-H264_Get_Last_IDR_Frame_Info
	.align	2
	.global	H264_Sei_Get_Frame_Pts
	.type	H264_Sei_Get_Frame_Pts, %function
H264_Sei_Get_Frame_Pts:
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
	add	r3, r0, #26368
	add	r2, r0, #24576
	add	r3, r3, #144
	mov	r4, r0
	movw	r0, #26496
	ldr	r5, [r2, #1912]
	movw	r1, #26464
	ldr	r10, [r2, #1916]
	ldrd	r2, [r3, #-8]
	cmp	r5, #0
	ldrd	r6, [r4, r1]
	strd	r2, [fp, #-60]
	ldrd	r2, [r4, r0]
	strd	r2, [fp, #-52]
	beq	.L2301
	mov	r9, r5
	mov	r0, r10
	b	.L2300
.L2302:
	mov	r9, r1
.L2300:
	mov	r1, r9
	bl	__aeabi_uidivmod
	mov	r0, r9
	cmp	r1, #0
	bne	.L2302
.L2299:
	ldrd	r2, [fp, #-60]
	mov	r1, r9
	mov	r0, r5
	mov	r8, #1000
	subs	r2, r6, r2
	add	r4, r4, #60928
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
	strd	r0, [r4, #24]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2301:
	mov	r9, r10
	b	.L2299
	UNWIND(.fnend)
	.size	H264_Sei_Get_Frame_Pts, .-H264_Sei_Get_Frame_Pts
	.align	2
	.global	H264_DecPicTimingSEI
	.type	H264_DecPicTimingSEI, %function
H264_DecPicTimingSEI:
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
	add	r2, r0, #12288
	mov	r4, #4000
	mov	r5, r0
	ldr	r1, [r2, #1344]
	ldr	r3, [r2, #1300]
	mla	r4, r4, r1, r3
	ldrb	r1, [r4, #23]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2304
	ldr	ip, [r2, #1288]
	cmp	ip, #0
	ble	.L2305
	ldrb	r2, [r3, #23]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #4000
	beq	.L2308
	b	.L2326
.L2309:
	ldrb	r1, [r3, #-3977]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2306
.L2308:
	add	r2, r2, #1
	mov	r4, r3
	cmp	r2, ip
	add	r3, r3, #4000
	bne	.L2309
.L2305:
	ldr	r1, .L2329
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r3, #0
.L2310:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2326:
	mov	r4, r3
.L2306:
	cmp	r4, #0
	beq	.L2305
.L2304:
	ldrb	r3, [r4, #22]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2312
	ldrb	r3, [r4, #3299]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2327
	ldr	r1, [r4, #3676]
	ldr	r7, [r4, #3680]
	add	r1, r1, #1
	add	r7, r7, #1
.L2316:
	ldr	r2, .L2329+4
	mov	r0, r5
	bl	u_v
	add	r6, r5, #24576
	ldr	r2, .L2329+8
	mov	r1, r7
	str	r0, [r6, #1848]
	mov	r0, r5
	bl	u_v
	add	r3, r5, #61440
	ldr	r2, .L2329+12
	str	r0, [r6, #1852]
	ldr	r3, [r3, #2344]
	ldr	r3, [r2, r3, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L2328
.L2312:
	ldrb	r0, [r4, #3303]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	r3, r0
	beq	.L2310
	ldr	r2, .L2329+16
	mov	r1, #4
	mov	r0, r5
	add	r5, r5, #24576
	bl	u_v
	mov	r3, #0
	strb	r0, [r5, #1844]
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2327:
	ldrb	r3, [r4, #3302]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2312
	ldr	r1, [r4, #3988]
	ldr	r7, [r4, #3992]
	add	r1, r1, #1
	add	r7, r7, #1
	b	.L2316
.L2328:
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L2312
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L2312
	mov	r0, r5
	bl	H264_Sei_Get_Dpb_Output_Time
	b	.L2312
.L2330:
	.align	2
.L2329:
	.word	.LC312
	.word	.LC313
	.word	.LC314
	.word	s_pstVfmwChan
	.word	.LC315
	UNWIND(.fnend)
	.size	H264_DecPicTimingSEI, .-H264_DecPicTimingSEI
	.align	2
	.global	H264_DecSEI
	.type	H264_DecSEI, %function
H264_DecSEI:
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
	add	r10, r0, #61440
	ldr	r3, .L2605
	mov	r1, #0
	ldr	r2, [r10, #2344]
	mov	r7, r0
	strb	r1, [fp, #-45]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L2570
.L2332:
	ldr	r3, [r7, #368]
	mov	r2, #32
	str	r2, [r3, #24]
.L2333:
	add	r6, r7, #13504
	add	r4, r7, #12288
	add	r6, r6, #24
	mov	r8, #0
	b	.L2336
.L2572:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2335
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2571
.L2336:
	mov	r2, #1
	sub	r1, fp, #45
	mov	r0, r7
	bl	GetBytes
	ldr	r3, [r4, #1264]
	ldr	ip, [r4, #1256]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	bls	.L2572
.L2335:
	ldr	r1, .L2605+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2338
.L2571:
	mov	r3, #0
	str	r3, [fp, #-60]
.L2516:
	mov	r5, #0
	b	.L2342
.L2574:
	bl	BsSkip
	cmp	r9, #0
	ble	.L2340
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2573
.L2342:
	mov	r2, #1
	sub	r1, fp, #45
	mov	r0, r7
	bl	GetBytes
	ldr	r3, [r4, #1264]
	ldr	ip, [r4, #1256]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r5, r5, r2
	mov	r9, r0
	mov	r0, r6
	bls	.L2574
.L2340:
	ldr	r1, .L2605+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
.L2338:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2573:
	cmp	r5, #409600
	bgt	.L2340
	ldr	r3, [r7, #368]
	ldr	r2, [r3, #68]
	cmp	r2, #2
	ldreq	r2, [r3, #52]
	ldreq	r3, [r3, #24]
	ldrne	r2, [r3, #24]
	addeq	r2, r2, r3
	moveq	r2, r2, lsr #3
	cmp	r8, #45
	ldrls	pc, [pc, r8, asl #2]
	b	.L2345
.L2347:
	.word	.L2346
	.word	.L2348
	.word	.L2349
	.word	.L2350
	.word	.L2351
	.word	.L2352
	.word	.L2353
	.word	.L2354
	.word	.L2355
	.word	.L2356
	.word	.L2357
	.word	.L2358
	.word	.L2359
	.word	.L2360
	.word	.L2361
	.word	.L2362
	.word	.L2363
	.word	.L2364
	.word	.L2365
	.word	.L2366
	.word	.L2367
	.word	.L2368
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2345
	.word	.L2369
.L2369:
	mov	r1, r5
	mov	r0, r7
	ldr	r8, [r4, #1264]
	bl	H264_DecFramePackingSEI
	ldr	r0, [r4, #1264]
	mov	r9, r5, asl #3
	rsb	r3, r8, r0
	cmp	r3, r9
	bge	.L2499
	rsb	r3, r3, r9
	str	r3, [fp, #-56]
	cmp	r3, #0
	add	r8, r3, #7
	movge	r8, r3
	ldr	r3, [r4, #1256]
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2501
	add	r2, r0, #8
	mov	r3, r3, asl #3
	cmp	r2, r3
	bhi	.L2501
	mov	r9, #0
	b	.L2502
.L2503:
	add	r2, r0, #8
	cmp	r2, r3
	bhi	.L2501
.L2502:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r9, r9, #1
	ldr	r3, [r4, #1256]
	cmp	r9, r8
	ldr	r0, [r4, #1264]
	mov	r3, r3, asl #3
	bne	.L2503
.L2501:
	ldr	r2, [fp, #-56]
	mov	r1, r2, asr #31
	mov	r1, r1, lsr #29
	add	r2, r2, r1
	and	r2, r2, #7
	rsb	r1, r1, r2
	add	r2, r0, r1
	cmp	r3, r2
	bcs	.L2575
.L2499:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2576
.L2565:
	ldr	r3, [r10, #1056]
.L2372:
	cmp	r3, #3
	bhi	.L2577
.L2511:
	mov	r8, #0
	b	.L2515
.L2513:
	bl	BsSkip
	cmp	r5, #0
	ble	.L2514
	ldrb	r3, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2578
.L2515:
	mov	r2, #1
	sub	r1, fp, #45
	mov	r0, r7
	bl	GetBytes
	ldr	r3, [r4, #1264]
	ldr	ip, [r4, #1256]
	mov	r1, #8
	add	r3, r3, r1
	ldrb	r2, [fp, #-45]	@ zero_extendqisi2
	cmp	r3, ip, asl #3
	add	r8, r8, r2
	mov	r5, r0
	mov	r0, r6
	bls	.L2513
.L2514:
	mov	r0, #0
.L2603:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2368:
	mov	r3, r5
	ldr	r1, .L2605+12
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2579
.L2493:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2496
.L2497:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2496:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2497
	b	.L2565
.L2367:
	mov	r3, r5
	ldr	r1, .L2605+16
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2580
.L2488:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2491
.L2492:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2491:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2492
	b	.L2565
.L2364:
	mov	r3, r5
	ldr	r1, .L2605+20
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2581
.L2473:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2476
.L2477:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2476:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2477
	b	.L2565
.L2363:
	mov	r3, r5
	ldr	r1, .L2605+24
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2582
.L2468:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2471
.L2472:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2471:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2472
	b	.L2565
.L2362:
	mov	r3, r5
	ldr	r1, .L2605+28
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2583
.L2463:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2466
.L2467:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2466:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2467
	b	.L2565
.L2361:
	mov	r3, r5
	ldr	r1, .L2605+32
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2584
.L2458:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2461
.L2462:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2461:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2462
	b	.L2565
.L2366:
	mov	r3, r5
	ldr	r1, .L2605+36
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2585
.L2483:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2486
.L2487:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2486:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2487
	b	.L2565
.L2365:
	mov	r3, r5
	ldr	r1, .L2605+40
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2586
.L2478:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2481
.L2482:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2481:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2482
	b	.L2565
.L2360:
	mov	r3, r5
	ldr	r1, .L2605+44
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2587
.L2453:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2456
.L2457:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2456:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2457
	b	.L2565
.L2359:
	mov	r3, r5
	ldr	r1, .L2605+48
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2588
.L2448:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2451
.L2452:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2451:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2452
	b	.L2565
.L2358:
	mov	r3, r5
	ldr	r1, .L2605+52
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2589
.L2443:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2446
.L2447:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2446:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2447
	b	.L2565
.L2357:
	mov	r3, r5
	ldr	r1, .L2605+56
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2590
.L2438:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2441
.L2442:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2441:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2442
	b	.L2565
.L2356:
	mov	r3, r5
	ldr	r1, .L2605+60
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2591
.L2433:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2436
.L2437:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2436:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2437
	b	.L2565
.L2355:
	mov	r3, r5
	ldr	r1, .L2605+64
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2592
.L2428:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2431
.L2432:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2431:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2432
	b	.L2565
.L2354:
	mov	r3, r5
	ldr	r1, .L2605+68
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2593
.L2423:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2426
.L2427:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2426:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2427
	b	.L2565
.L2353:
	mov	r3, r5
	ldr	r1, .L2605+72
	mov	r0, #20
	bl	dprint_vfmw
	cmp	r5, #0
	ble	.L2420
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2420
	mov	r8, #0
	b	.L2421
.L2422:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2420
.L2421:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2422
.L2420:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	bge	.L2565
	movw	r3, #11196
	b	.L2566
.L2352:
	ldr	r3, [fp, #-60]
	cmp	r3, #0
	bne	.L2351
	mov	r3, r5
	ldr	r1, .L2605+76
	mov	r0, #20
	bl	dprint_vfmw
	ldr	r8, [r10, #1056]
	cmp	r8, #3
	bhi	.L2594
.L2396:
	ldr	r0, [r10, #2344]
	bl	GetUsd
	add	r3, r8, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	str	r0, [r3, #4]
	ldr	r3, [r10, #1056]
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	ip, [r3, #4]
	cmp	ip, #0
	beq	.L2519
	ldr	r2, [r7, #368]
	cmp	r5, #1024
	movlt	r9, r5
	movge	r9, #1024
	ldrb	r0, [r2]	@ zero_extendqisi2
	ldr	lr, [r2, #68]
	cmp	r0, lr
	bcs	.L2520
	sxth	r3, r0
	mov	r8, #0
	mov	r1, r3, asl #5
	sub	r1, r1, r3, asl #2
	add	r1, r2, r1
.L2398:
	ldr	r3, [r1, #24]
	add	r0, r0, #1
	ldr	r2, [r1, #12]
	cmp	r0, lr
	add	r3, r3, #7
	add	r1, r1, #28
	sub	r3, r2, r3, lsr #3
	add	r8, r8, r3
	bne	.L2398
	mov	r3, r8
.L2397:
	cmp	r9, r3
	ldrsb	r2, [fp, #-60]
	movle	r8, r9
	cmp	r2, #1
	str	r2, [fp, #-64]
	movne	r3, #0
	strne	r3, [fp, #-56]
	beq	.L2595
.L2400:
	rsb	r2, r3, r8
	cmp	r2, #0
	ble	.L2596
	ldr	r3, [r10, #1056]
	mov	r0, r7
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	r1, [r3, #4]
	bl	GetBytes
	subs	r8, r0, #0
	ble	.L2597
	ldr	r3, [fp, #-56]
	rsb	r3, r3, r9
	cmp	r8, r3
	ldr	r3, [r10, #1056]
	bge	.L2406
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r8, [r3, #1052]
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2407
	mov	r5, #0
	b	.L2408
.L2410:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2407
.L2408:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2410
.L2407:
	ldr	r3, [r10, #1056]
	ldr	r1, [r7]
	add	r3, r3, #15616
	ldr	ip, .L2605+112
	add	r3, r3, #8
	ldr	r2, [fp, #-64]
	ldrd	r0, [r1, #56]
	add	r3, r7, r3, lsl #2
	cmp	r2, #1
	ldr	ip, [ip]
	ldr	r3, [r3, #4]
	moveq	r2, #8
	movne	r2, #9
	cmp	ip, #0
	add	r3, r3, #1056
	strd	r0, [r3]
	ldr	r3, [r10, #1056]
	add	r3, r3, #15616
	add	r3, r3, #8
.L2568:
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r2, [r3, #1040]
	ldr	r3, [r10, #1056]
	ldr	r2, [r10, #2304]
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r2, [r3, #1044]
	beq	.L2416
	ldr	r2, [r10, #1056]
	movw	r3, #1064
	mov	r1, #6
	ldr	r0, [r10, #2344]
	add	r2, r2, #15616
	add	r2, r2, #8
	add	r2, r7, r2, lsl #2
	ldr	r2, [r2, #4]
	blx	ip
.L2416:
	ldr	r3, [r10, #1056]
	ldr	r0, [r10, #2344]
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	r1, [r3, #4]
	bl	FreeUsdByDec
	ldr	r3, [r10, #1056]
	add	r3, r3, #1
	str	r3, [r10, #1056]
	cmp	r3, #3
	bls	.L2511
.L2577:
	ldr	r1, .L2605+80
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2338
.L2348:
	mov	r3, r5
	ldr	r1, .L2605+84
	mov	r0, #20
	mov	r9, r5, asl #3
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	ldr	r8, [r4, #1264]
	bl	H264_DecPicTimingSEI
	ldr	r2, [r4, #1264]
	rsb	r3, r8, r2
	cmp	r3, r9
	bge	.L2377
	rsb	r3, r3, r9
	str	r3, [fp, #-56]
	cmp	r3, #0
	add	r8, r3, #7
	movge	r8, r3
	ldr	r3, [r4, #1256]
	mov	r8, r8, asr #3
	cmp	r8, #0
	movle	r3, r3, asl #3
	ble	.L2379
	add	r1, r2, #8
	mov	r3, r3, asl #3
	cmp	r1, r3
	bhi	.L2379
	mov	r9, #0
	b	.L2380
.L2381:
	add	r1, r2, #8
	cmp	r1, r3
	bhi	.L2379
.L2380:
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	add	r9, r9, #1
	ldr	r3, [r4, #1256]
	cmp	r9, r8
	ldr	r2, [r4, #1264]
	mov	r3, r3, asl #3
	bne	.L2381
.L2379:
	ldr	ip, [fp, #-56]
	mov	r1, ip, asr #31
	mov	r0, r1, lsr #29
	add	r1, ip, r0
	and	r1, r1, #7
	rsb	r1, r0, r1
	add	r2, r2, r1
	cmp	r2, r3
	bls	.L2598
.L2377:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	bge	.L2565
	movw	r3, #10951
.L2566:
	ldr	r2, .L2605+116
	mov	r0, #20
	ldr	r1, .L2605+120
	bl	dprint_vfmw
	ldr	r3, [r10, #1056]
	b	.L2372
.L2346:
	add	r1, r7, #24576
	mov	lr, #1
	mov	r0, #0
	mov	r3, r5
	ldr	ip, [r1, #1856]
	str	r0, [r1, #1864]
	mov	r0, #20
	add	ip, ip, lr
	strb	lr, [r1, #1936]
	str	ip, [r1, #1856]
	ldr	r1, .L2605+88
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2599
.L2370:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2374
.L2375:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2374:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2375
	b	.L2565
.L2350:
	mov	r3, r5
	ldr	r1, .L2605+92
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2600
.L2389:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2392
.L2393:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2392:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2393
	b	.L2565
.L2349:
	mov	r3, r5
	ldr	r1, .L2605+96
	mov	r0, #20
	bl	dprint_vfmw
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2601
.L2384:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2387
.L2388:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2387:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2388
	b	.L2565
.L2606:
	.align	2
.L2605:
	.word	s_pstVfmwChan
	.word	.LC316
	.word	.LC317
	.word	.LC345
	.word	.LC344
	.word	.LC341
	.word	.LC340
	.word	.LC339
	.word	.LC338
	.word	.LC343
	.word	.LC342
	.word	.LC337
	.word	.LC336
	.word	.LC335
	.word	.LC334
	.word	.LC333
	.word	.LC332
	.word	.LC331
	.word	.LC330
	.word	.LC324
	.word	.LC346
	.word	.LC320
	.word	.LC318
	.word	.LC322
	.word	.LC321
	.word	.LC323
	.word	.LC325
	.word	.LC327
	.word	g_event_report
	.word	.LANCHOR0+252
	.word	.LC319
	.word	.LC326
	.word	.LC328
	.word	.LC329
.L2351:
	mov	r3, r5
	ldr	r1, .L2605+100
	mov	r0, #20
	bl	dprint_vfmw
	ldr	r8, [r10, #1056]
	mov	r3, #1
	str	r3, [fp, #-60]
	cmp	r8, #3
	bls	.L2396
.L2594:
	ldr	r1, [r10, #1060]
	ldr	r0, [r10, #2344]
	bl	FreeUsdByDec
	ldr	r1, [r10, #1064]
	ldr	r0, [r10, #2344]
	bl	FreeUsdByDec
	ldr	r1, [r10, #1068]
	ldr	r0, [r10, #2344]
	bl	FreeUsdByDec
	ldr	r1, [r10, #1072]
	ldr	r0, [r10, #2344]
	bl	FreeUsdByDec
	mov	r3, #0
	mov	r8, r3
	str	r3, [r10, #1060]
	str	r3, [r10, #1064]
	str	r3, [r10, #1068]
	str	r3, [r10, #1072]
	str	r3, [r10, #1056]
	b	.L2396
.L2345:
	mov	r1, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	blt	.L2602
.L2506:
	cmp	r5, #0
	ble	.L2565
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
	mov	r8, #0
	b	.L2509
.L2510:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2565
.L2509:
	add	r8, r8, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2510
	b	.L2565
.L2578:
	cmp	r3, #128
	bne	.L2516
	mov	r0, #0
	b	.L2603
.L2406:
	add	r3, r3, #15616
	ldr	r2, [fp, #-56]
	add	r3, r3, #8
	cmp	r9, r5
	rsb	r8, r2, r5
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r8, [r3, #1052]
	bcc	.L2604
.L2412:
	cmp	r8, #0
	ble	.L2407
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2407
	mov	r5, #0
	b	.L2414
.L2415:
	ldr	r3, [r4, #1264]
	ldr	r2, [r4, #1256]
	add	r3, r3, #8
	cmp	r3, r2, asl #3
	bhi	.L2407
.L2414:
	add	r5, r5, #1
	mov	r1, #8
	mov	r0, r6
	bl	BsSkip
	cmp	r5, r8
	bne	.L2415
	b	.L2407
.L2570:
	ldr	r2, [r3, #156]
	cmp	r2, r1
	bne	.L2332
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L2332
	ldr	r3, [r3, #152]
	cmp	r3, #1
	bne	.L2332
	ldr	r3, [r0, #368]
	mov	r2, #48
	str	r2, [r3, #24]
	b	.L2333
.L2598:
	mov	r0, r6
	bl	BsSkip
	b	.L2377
.L2576:
	movw	r3, #11624
	b	.L2566
.L2575:
	mov	r0, r6
	bl	BsSkip
	b	.L2499
.L2595:
	ldrb	r3, [fp, #-64]	@ zero_extendqisi2
	mov	r1, #8
	mov	r0, r7
	ldr	r2, .L2605+104
	strb	r3, [ip, #1026]
	ldr	r3, [r10, #1056]
	add	r3, r3, #15616
	add	r3, r3, r1
	add	r3, r7, r3, lsl #2
	ldr	r3, [r3, #4]
	str	r3, [fp, #-56]
	bl	u_v
	ldr	r3, [fp, #-56]
	strb	r0, [r3, #1027]
	ldr	r3, [r10, #1056]
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	ip, [r3, #4]
	ldrb	r3, [ip, #1027]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L2401
	mov	r3, #3
	mov	r2, #0
	str	r3, [fp, #-56]
	strb	r2, [ip, #1028]
.L2402:
	ldr	ip, [r10, #1056]
	mov	r1, #16
	ldr	r2, .L2605+108
	mov	r0, r7
	add	ip, ip, #15616
	str	r3, [fp, #-68]
	add	ip, ip, #8
	add	ip, r7, ip, lsl #2
	ldr	ip, [ip, #4]
	str	ip, [fp, #-72]
	bl	u_v
	ldr	ip, [fp, #-72]
	ldr	r3, [fp, #-68]
	add	ip, ip, #1024
	mov	r1, r3
	strh	r0, [ip, #6]	@ movhi
	mov	r0, r7
	bl	PassBytes
	ldr	r3, [fp, #-68]
	cmp	r8, r3
	bne	.L2400
	ldr	r3, [r10, #1056]
	mov	r2, #8
	ldr	r1, [r7]
	add	r3, r3, #15616
	ldr	ip, .L2605+112
	add	r3, r3, r2
	ldrd	r0, [r1, #56]
	add	r3, r7, r3, lsl #2
	ldr	ip, [ip]
	ldr	r3, [r3, #4]
	cmp	ip, #0
	add	r3, r3, #1056
	strd	r0, [r3]
	ldr	r3, [r10, #1056]
	add	r3, r3, #15616
	add	r3, r3, r2
	b	.L2568
.L2604:
	rsb	r1, r9, r5
	mov	r0, r7
	bl	PassBytes
	cmp	r0, #0
	bge	.L2412
	movw	r3, #11145
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2412
.L2520:
	mov	r3, #0
	mov	r8, r3
	b	.L2397
.L2602:
	movw	r3, #11636
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2506
.L2601:
	movw	r3, #10963
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2384
.L2600:
	movw	r3, #10989
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2389
.L2599:
	movw	r3, #10898
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2370
.L2593:
	movw	r3, #11208
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2423
.L2592:
	movw	r3, #11234
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2428
.L2591:
	movw	r3, #11260
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2433
.L2590:
	movw	r3, #11286
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2438
.L2589:
	movw	r3, #11312
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2443
.L2588:
	movw	r3, #11338
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2448
.L2587:
	movw	r3, #11364
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2453
.L2586:
	movw	r3, #11494
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2478
.L2585:
	mov	r3, #11520
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2483
.L2584:
	movw	r3, #11390
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2458
.L2583:
	movw	r3, #11416
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2463
.L2582:
	movw	r3, #11442
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2468
.L2581:
	movw	r3, #11468
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2473
.L2580:
	movw	r3, #11546
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2488
.L2579:
	movw	r3, #11572
	ldr	r2, .L2605+116
	ldr	r1, .L2605+120
	mov	r0, #20
	bl	dprint_vfmw
	b	.L2493
.L2519:
	mvn	r0, #0
	b	.L2338
.L2401:
	ldr	r2, .L2605+124
	mov	r1, #8
	mov	r0, r7
	mov	r3, #4
	str	ip, [fp, #-68]
	str	r3, [fp, #-56]
	bl	u_v
	ldr	ip, [fp, #-68]
	ldr	r3, [fp, #-56]
	strb	r0, [ip, #1028]
	b	.L2402
.L2596:
	ldr	r1, .L2605+128
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #1056]
	ldr	r0, [r10, #2344]
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	r1, [r3, #4]
	bl	FreeUsdByDec
	ldr	r3, [r10, #1056]
	mov	r2, #0
	mvn	r0, #0
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	str	r2, [r3, #4]
	b	.L2338
.L2597:
	ldr	r1, .L2605+132
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r10, #1056]
	ldr	r0, [r10, #2344]
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r3, r7, r3, lsl #2
	ldr	r1, [r3, #4]
	bl	FreeUsdByDec
	ldr	r3, [r10, #1056]
	mov	r2, #0
	mvn	r0, #0
	add	r3, r3, #15616
	add	r3, r3, #8
	add	r7, r7, r3, lsl #2
	str	r2, [r7, #4]
	b	.L2338
	UNWIND(.fnend)
	.size	H264_DecSEI, .-H264_DecSEI
	.align	2
	.global	InitOldSlice
	.type	InitOldSlice, %function
InitOldSlice:
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
	add	r2, r0, #12288
	add	r0, r0, #20480
	movw	r3, #23352
	ldr	r1, [r2, #1292]
	movt	r3, 1
	mov	r2, #2
	str	r3, [r0, #1864]
	strb	r2, [r0, #1849]
	mov	r3, #32
	mov	r2, #7
	strb	r3, [r0, #1850]
	str	r2, [r0, #1860]
	mvn	r3, #0
	mov	r2, #3
	str	r3, [r0, #1876]
	str	r2, [r0, #1872]
	mov	r3, #0
	mov	r2, #262144
	str	r1, [r0, #1856]
	str	r2, [r0, #1888]
	strb	r3, [r0, #1848]
	str	r3, [r0, #1880]
	str	r3, [r0, #1884]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	InitOldSlice, .-InitOldSlice
	.align	2
	.global	H264_IsNewPicNal
	.type	H264_IsNewPicNal, %function
H264_IsNewPicNal:
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
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	mov	r5, r0
	and	r3, r3, #31
	sub	r3, r3, #1
	cmp	r3, #7
	ldrls	pc, [pc, r3, asl #2]
	b	.L2616
.L2611:
	.word	.L2610
	.word	.L2616
	.word	.L2616
	.word	.L2616
	.word	.L2610
	.word	.L2616
	.word	.L2612
	.word	.L2612
.L2612:
	ldr	r3, [r0]
	mov	r2, #1
	str	r2, [r0]
	adds	r3, r3, #0
	movne	r3, #1
	rsb	r0, r3, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2610:
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L2613
.L2615:
	mvn	r0, #0
.L2614:
	mov	r2, #0
	str	r2, [r5]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2616:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2613:
	ldrb	ip, [r1, #5]	@ zero_extendqisi2
	ldrb	r3, [r1, #6]	@ zero_extendqisi2
	ldrb	r2, [r1, #7]	@ zero_extendqisi2
	mov	ip, ip, asl #16
	ldrb	r4, [r1, #4]	@ zero_extendqisi2
	orr	r3, ip, r3, asl #8
	orr	r3, r3, r2
	orr	r4, r3, r4, asl #24
	mov	r0, r4
	bl	ZerosMS_32
	cmp	r0, #15
	bhi	.L2615
	mov	r3, r0, asl #1
	rsb	r3, r3, #31
	mov	r3, r4, lsr r3
	subs	r0, r3, #1
	mvnne	r0, #0
	b	.L2614
	UNWIND(.fnend)
	.size	H264_IsNewPicNal, .-H264_IsNewPicNal
	.align	2
	.global	FindZeroBitsInSeg
	.type	FindZeroBitsInSeg, %function
FindZeroBitsInSeg:
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
	cmp	r0, #0
	cmpne	r1, #0
	mov	r9, r0
	str	r1, [fp, #-48]
	movle	r4, #1
	movgt	r4, #0
	ble	.L2643
	ldr	r3, [fp, #-48]
	subs	r7, r3, #0
	add	r8, r3, #63
	movge	r8, r3
	ands	r3, r3, #63
	movne	r3, #1
	add	r8, r3, r8, asr #6
	cmp	r8, #0
	ble	.L2631
	ldr	r5, .L2644
	ldr	r10, .L2644+4
.L2629:
	cmp	r7, #64
	ldr	r3, [r10, #52]
	ldr	r0, .L2644
	movcc	r6, r7
	movcs	r6, #64
	mov	r2, r6
	rsb	r1, r6, r7
	sub	r6, r6, #1
	add	r1, r9, r1
	blx	r3
	add	r3, r5, r6
	ldrb	r2, [r5, r6]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2621
	ldr	r2, .L2644
	add	r4, r4, #1
	cmp	r3, r2
	bne	.L2624
	b	.L2622
.L2625:
	cmp	r3, r5
	add	r4, r4, #1
	beq	.L2622
.L2624:
	ldrb	r2, [r3, #-1]!	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2625
.L2621:
	mov	r0, r4, asl #3
.L2620:
	ldr	r3, [fp, #-48]
	cmp	r4, r3
	bge	.L2633
	sub	r3, r3, #1
	rsb	r4, r4, r3
	ldrb	r2, [r9, r4]	@ zero_extendqisi2
	tst	r2, #1
	moveq	r2, r2, lsr #1
	moveq	r3, #1
	bne	.L2633
.L2628:
	tst	r2, #1
	mov	r2, r2, lsr #1
	bne	.L2626
	add	r3, r3, #1
	cmp	r3, #8
	bne	.L2628
	b	.L2626
.L2622:
	subs	r8, r8, #1
	sub	r7, r7, #64
	bne	.L2629
	b	.L2621
.L2633:
	mov	r3, #0
.L2626:
	add	r0, r3, r0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2643:
	mov	r2, r1
	mov	r0, #0
	ldr	r1, .L2644+8
	bl	dprint_vfmw
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2631:
	mov	r0, r4
	b	.L2620
.L2645:
	.align	2
.L2644:
	.word	.LANCHOR3-1976
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC347
	UNWIND(.fnend)
	.size	FindZeroBitsInSeg, .-FindZeroBitsInSeg
	.align	2
	.global	FindTrailZeros
	.type	FindTrailZeros, %function
FindTrailZeros:
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
	beq	.L2652
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2651
	ldr	r1, [r3, #40]
	ldr	r0, [r3, #36]
	bl	FindZeroBitsInSeg
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #40]
	cmp	r0, r2, asl #3
	bcs	.L2655
	cmn	r0, #1
	beq	.L2651
.L2650:
	add	r0, r0, #1
	str	r0, [r3, #72]
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #68]
	cmp	r2, #1
	bls	.L2654
	ldr	r1, [r3, #40]
	ldr	r2, [r3, #72]
	cmp	r2, r1, asl #3
	bcs	.L2656
.L2654:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2656:
	add	r2, r4, #61440
	ldr	r1, [r3, #60]
	ldr	r0, [r2, #2344]
	bl	SM_ReleaseStreamSeg
	ldr	r2, [r4, #368]
	mov	r3, #0
	mov	r1, #1
	mov	r0, r3
	str	r3, [r2, #36]
	ldr	r2, [r4, #368]
	str	r1, [r2, #68]
	ldr	r2, [r4, #368]
	str	r3, [r2, #72]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L2655:
	add	r2, r4, #61440
	ldr	r1, [r3, #60]
	ldr	r0, [r2, #2344]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #368]
	mov	r1, #0
	mov	r2, #1
	str	r1, [r3, #36]
	ldr	r3, [r4, #368]
	str	r2, [r3, #68]
	ldr	r3, [r4, #368]
.L2651:
	ldr	r1, [r3, #12]
	ldr	r0, [r3, #8]
	bl	FindZeroBitsInSeg
	ldr	r3, [r4, #368]
	b	.L2650
.L2652:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	FindTrailZeros, .-FindTrailZeros
	.align	2
	.global	CombinePacket
	.type	CombinePacket, %function
CombinePacket:
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
	ldr	r3, [r0, #368]
	ldr	r3, [r3, #12]
	cmp	r3, #4096
	ldmcsfd	sp, {fp, sp, pc}
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	CombinePacket.part.13
	UNWIND(.fnend)
	.size	CombinePacket, .-CombinePacket
	.align	2
	.global	FindNaluArraySlot
	.type	FindNaluArraySlot, %function
FindNaluArraySlot:
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
	mov	ip, r0
	ldrb	r0, [r0, #377]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2664
	mov	r2, ip
	mov	r3, #1
	b	.L2662
.L2661:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L2667
.L2662:
	ldrb	r1, [r2, #473]	@ zero_extendqisi2
	add	r2, r2, #96
	cmp	r1, #0
	bne	.L2661
	mov	r0, r3
.L2660:
	mov	r2, r3, asl #7
	mov	r1, #1
	sub	r3, r2, r3, asl #5
	add	ip, ip, r3
	strb	r1, [ip, #377]
	ldmfd	sp, {fp, sp, pc}
.L2667:
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L2664:
	mov	r3, r0
	b	.L2660
	UNWIND(.fnend)
	.size	FindNaluArraySlot, .-FindNaluArraySlot
	.align	2
	.global	InquireSliceExtProperty
	.type	InquireSliceExtProperty, %function
InquireSliceExtProperty:
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
	add	r0, r0, #13504
	add	r0, r0, #24
	mov	r1, #24
	bl	BsGet
	ldr	r3, [r4, #368]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #3]
	ldr	r2, [r4, #368]
	ldrb	r3, [r2, #3]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r4, #61440
	ldreqb	r0, [r3, #404]	@ zero_extendqisi2
	beq	.L2670
	ubfx	lr, r0, #16, #6
	ubfx	ip, r0, #15, #1
	ubfx	r1, r0, #12, #3
	strb	lr, [r3, #405]
	strb	ip, [r3, #406]
	ubfx	lr, r0, #8, #4
	ubfx	ip, r0, #5, #3
	strb	r1, [r3, #407]
	strb	lr, [r3, #408]
	ubfx	r1, r0, #4, #1
	ubfx	lr, r0, #3, #1
	strb	ip, [r3, #409]
	strb	r1, [r3, #410]
	ubfx	ip, r0, #2, #1
	and	r1, r0, #3
	strb	lr, [r3, #411]
	ubfx	r0, r0, #22, #1
	strb	ip, [r3, #412]
	strb	r1, [r3, #413]
	strb	r0, [r3, #404]
.L2670:
	cmp	r0, #1
	mov	r0, #0
	moveq	r3, #5
	streqb	r3, [r2, #2]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	InquireSliceExtProperty, .-InquireSliceExtProperty
	.align	2
	.global	InquireSliceProperty
	.type	InquireSliceProperty, %function
InquireSliceProperty:
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
	add	r3, r0, #61440
	mov	r5, r2
	mov	r4, r0
	mov	r8, r1
	ldr	r2, [r3, #2288]
	mov	r0, #22
	ldr	r1, .L2681
	add	r6, r4, #20480
	sub	r2, r2, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r5]
	mov	r0, r4
	str	r3, [r8]
	ldr	r3, [r4, #368]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	strb	r2, [r6, #211]
	ldr	r3, [r3, #76]
	str	r3, [r6, #236]
	bl	SliceCheck
	subs	r7, r0, #0
	bne	.L2676
	mov	r0, r4
	bl	ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L2680
	ldrb	r0, [r6, #213]	@ zero_extendqisi2
	add	r9, r4, #12288
	mov	r2, #2208
	mov	r3, #4000
	sub	r0, r0, #1
	add	r4, r4, #24576
	clz	r0, r0
	mov	r0, r0, lsr #5
	str	r0, [r8]
	ldr	r1, [r6, #216]
	ldr	r0, [r9, #1304]
	ldr	ip, [r9, #1300]
	ldr	lr, [r9, #1280]
	mla	r2, r2, r1, r0
	ldr	r0, [r9, #1276]
	ldr	r2, [r2, #28]
	mla	r3, r3, r2, ip
	ldrb	ip, [r3, #18]	@ zero_extendqisi2
	ldr	r6, [r3, #3252]
	rsb	r1, ip, #2
	ldr	r2, [r3, #3248]
	mla	r1, r6, r1, r1
	add	r2, r2, #1
	cmp	r0, r2
	cmpeq	lr, r1
	movne	r2, #1
	strne	r2, [r5]
	ldr	r2, [r3, #3272]
	ldr	r3, [r4, #2136]
	add	r3, r3, #1
	cmp	r2, r3
	movne	r3, #1
	strne	r3, [r5]
.L2673:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2676:
	mvn	r7, #0
	b	.L2673
.L2680:
	ldr	r1, .L2681+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r7, #0
	b	.L2673
.L2682:
	.align	2
.L2681:
	.word	.LC348
	.word	.LC349
	UNWIND(.fnend)
	.size	InquireSliceProperty, .-InquireSliceProperty
	.align	2
	.global	HaveSliceToDec
	.type	HaveSliceToDec, %function
HaveSliceToDec:
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
	add	r0, r0, #61440
	ldr	r0, [r0, #2268]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HaveSliceToDec, .-HaveSliceToDec
	.align	2
	.global	IsRefListWrong
	.type	IsRefListWrong, %function
IsRefListWrong:
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
	add	r6, r0, #20480
	mov	r7, r0
	ldr	r3, [r6, #248]
	cmp	r3, #0
	beq	.L2685
	add	r5, r0, #26880
	add	r8, r0, #61440
	add	r5, r5, #240
	mov	r4, #0
	b	.L2689
.L2686:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L2688
	ldr	r3, [r6, #248]
	cmp	r4, r3
	bcs	.L2711
.L2689:
	ldr	r3, [r5, #4]!
	add	r4, r4, #1
	ldr	r0, [r8, #2344]
	ldr	r3, [r3, #36]
	ldr	r1, [r3, #648]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L2686
.L2688:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2711:
	cmp	r3, #0
	beq	.L2685
	ldr	r3, [r6, #252]
	cmp	r3, #0
	addne	r7, r7, #27136
	movne	r4, #0
	addne	r7, r7, #116
	bne	.L2692
	b	.L2685
.L2712:
	ldr	r3, [r0, #28]
	cmp	r3, #0
	beq	.L2688
	ldr	r3, [r6, #252]
	cmp	r4, r3
	bcs	.L2685
.L2692:
	ldr	r3, [r7, #4]!
	add	r4, r4, #1
	ldr	r0, [r8, #2344]
	ldr	r3, [r3, #36]
	ldr	r1, [r3, #648]
	bl	FSP_GetLogicFs
	cmp	r0, #0
	bne	.L2712
	b	.L2688
.L2685:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	IsRefListWrong, .-IsRefListWrong
	.align	2
	.global	H264DEC_Destroy
	.type	H264DEC_Destroy, %function
H264DEC_Destroy:
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
	add	r8, r0, #61440
	mov	r9, r0
	bl	H264_ClearCurrPic
	mov	r0, r9
	bl	ClearAllNal
	ldr	r3, [r8, #2280]
	cmp	r3, #1
	moveq	r3, #0
	streq	r3, [r8, #2280]
	ldr	r3, [r8, #1056]
	cmp	r3, #0
	beq	.L2715
	add	r5, r9, #62464
	mov	r4, #0
	add	r5, r5, #32
	mov	r6, r4
.L2717:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L2716
	ldr	r0, [r8, #2344]
	bl	FreeUsdByDec
	str	r6, [r5]
.L2716:
	ldr	r3, [r8, #1056]
	cmp	r3, r4
	bhi	.L2717
.L2715:
	add	r5, r9, #27904
	add	r9, r9, #60928
	add	r5, r5, #72
	add	r9, r9, #8
	mov	r6, #0
	mov	r7, #0
.L2721:
	sub	r4, r5, #32
.L2719:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L2718
	ldr	r0, [r8, #2344]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L2718:
	cmp	r4, r5
	bne	.L2719
	add	r5, r4, #824
	cmp	r5, r9
	bne	.L2721
	ldr	r1, .L2733
	mov	r0, #2
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	dprint_vfmw
.L2734:
	.align	2
.L2733:
	.word	.LC350
	UNWIND(.fnend)
	.size	H264DEC_Destroy, .-H264DEC_Destroy
	.align	2
	.global	H264DEC_RecycleImage
	.type	H264DEC_RecycleImage, %function
H264DEC_RecycleImage:
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
	add	r5, r0, #61440
	mov	r8, r1
	mov	r0, #2
	ldr	r1, .L2746
	bl	dprint_vfmw
	ldr	r0, [r5, #2344]
	mov	r1, r8
	bl	FSP_GetLogicFs
	cmp	r0, #0
	beq	.L2740
	ldrsb	r3, [r0, #1]
	cmp	r3, #0
	beq	.L2740
	add	r4, r0, #576
	add	r9, r0, #608
	mov	r6, #0
	mov	r7, #0
.L2738:
	ldrd	r2, [r4, #8]!
	orrs	r1, r2, r3
	bne	.L2745
.L2737:
	cmp	r4, r9
	bne	.L2738
	ldr	r0, [r5, #2344]
	mov	r1, r8
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2745:
	mov	r1, r2
	ldr	r0, [r5, #2344]
	bl	FreeUsdByDec
	strd	r6, [r4]
	b	.L2737
.L2740:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L2747:
	.align	2
.L2746:
	.word	.LC351
	UNWIND(.fnend)
	.size	H264DEC_RecycleImage, .-H264DEC_RecycleImage
	.align	2
	.global	OutputFrmToVO
	.type	OutputFrmToVO, %function
OutputFrmToVO:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #12)
	sub	sp, sp, #12
	cmp	r1, #0
	cmpne	r0, #0
	mov	r7, r2
	mov	r4, r0
	moveq	r3, #1
	movne	r3, #0
	mov	r5, r1
	beq	.L2790
	ldr	r2, [r0]
	ldr	r2, [r2, #24]
	cmp	r2, #0
	beq	.L2751
	add	r1, r0, #61440
	ldr	r2, [r1, #2272]
	cmp	r2, #2
	beq	.L2751
	ldr	r2, [r1, #396]
	cmp	r2, #0
	strneb	r3, [r2, #1]
	movne	r0, #1
	strne	r3, [r1, #396]
	beq	.L2753
.L2750:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2751:
	mov	r1, r5
	mov	r0, r4
	bl	CheckFrameStore
	cmn	r0, #3
	beq	.L2753
	add	r6, r4, #61440
	ldr	r1, [r6, #396]
	cmp	r1, #0
	beq	.L2754
	mov	r0, r4
	bl	GetImagePara
	ldr	r1, [r6, #396]
	mov	r0, r4
	bl	CheckFrameStore
	subs	r3, r0, #0
	beq	.L2791
	cmn	r3, #3
	beq	.L2761
	ldr	r1, .L2799
	movw	r2, #2036
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r6, #396]
	mov	r0, r4
	ldr	r1, [r3, #164]
	bl	H264DEC_RecycleImage
.L2761:
	ldr	r3, [r6, #396]
	mov	r0, #0
	strb	r0, [r3, #1]
	ldr	r3, [r6, #396]
	str	r0, [r6, #396]
	cmp	r5, r3
	beq	.L2750
.L2754:
	mov	r1, r5
	mov	r0, r4
	bl	GetImagePara
	mov	r1, r5
	mov	r0, r4
	bl	CheckFrameStore
	subs	r3, r0, #0
	beq	.L2792
	cmn	r3, #3
	beq	.L2753
	movw	r2, #2093
	ldr	r1, .L2799
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #164]
	mov	r0, r4
	bl	H264DEC_RecycleImage
	mov	r0, #2
	b	.L2750
.L2790:
	mov	r3, r1
	mov	r2, r0
	ldr	r1, .L2799+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #2
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2753:
	mov	r0, #1
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L2792:
	mov	r2, #1
	ldr	r1, [r5, #648]
	ldr	r0, [r6, #2344]
	bl	FSP_SetDisplay
	ldr	r1, [r5, #648]
	ldr	r0, [r6, #2344]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L2793
	cmp	r7, #1
	add	r3, r4, #8
	streq	r7, [r8, #180]
	mov	r2, r4
	ldr	r0, [r6, #2344]
	mov	r1, #0
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L2794
	ldr	r3, [r4]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r8, #16]
	bcs	.L2795
.L2768:
	ldr	r2, [r6, #2372]
	mov	r0, #0
	ldr	r3, [r6, #2364]
	add	r2, r2, #1
	str	r2, [r6, #2372]
	add	r3, r3, #2
	str	r3, [r6, #2364]
	b	.L2750
.L2791:
	ldr	r3, [r6, #396]
	mov	r2, #1
	ldr	r0, [r6, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetDisplay
	ldr	r3, [r6, #396]
	ldr	r0, [r6, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L2796
	ldr	r3, [r6, #396]
	mov	r2, r4
	mov	r1, #0
	cmp	r5, r3
	cmpeq	r7, #1
	moveq	r3, #1
	streq	r3, [r8, #180]
	add	r3, r4, #8
	ldr	r0, [r6, #2344]
	str	r8, [sp]
	bl	InsertImgToVoQueue
	cmp	r0, #1
	bne	.L2797
	ldr	r3, [r4]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r8, #16]
	bcs	.L2798
.L2760:
	ldr	r2, [r6, #2372]
	ldr	r3, [r6, #2364]
	add	r2, r2, #1
	str	r2, [r6, #2372]
	add	r3, r3, #2
	str	r3, [r6, #2364]
	b	.L2761
.L2795:
	mov	r1, r8
	mov	r0, r4
	bl	SetFrmRepeatCount.part.3
	b	.L2768
.L2798:
	mov	r1, r8
	mov	r0, r4
	bl	SetFrmRepeatCount.part.3
	b	.L2760
.L2794:
	mov	r2, r0
	ldr	r1, .L2799+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r5, #648]
	ldr	r0, [r6, #2344]
	mov	r2, #0
	bl	FSP_SetDisplay
	mov	r0, r4
	mov	r1, #1
	bl	ClearAll
	mvn	r0, #0
	b	.L2750
.L2797:
	mov	r2, r0
	ldr	r1, .L2799+8
	mov	r0, #0
	mov	r5, r0
	bl	dprint_vfmw
	ldr	r3, [r6, #396]
	mov	r2, r5
	strb	r5, [r3, #1]
	ldr	r3, [r6, #396]
	ldr	r0, [r6, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetDisplay
	str	r5, [r6, #396]
	mov	r0, r4
	mov	r1, #1
	bl	ClearAll
	mvn	r0, #0
	b	.L2750
.L2793:
	movw	r2, #2063
	ldr	r1, .L2799+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2750
.L2796:
	movw	r2, #2007
	ldr	r1, .L2799+16
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L2750
.L2800:
	.align	2
.L2799:
	.word	.LC355
	.word	.LC352
	.word	.LC354
	.word	.LC356
	.word	.LC353
	UNWIND(.fnend)
	.size	OutputFrmToVO, .-OutputFrmToVO
	.align	2
	.global	OutputFrmFromDPB
	.type	OutputFrmFromDPB, %function
OutputFrmFromDPB:
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
	mov	r6, r1
	add	r4, r4, #24576
	mov	r3, #0
	mov	r2, r3
	mov	r5, r0
	ldr	r1, [r4, #1944]
	strb	r3, [r1, #4]
	ldr	r1, [r4, #1944]
	bl	OutputFrmToVO
	ldr	r3, [r4, #1944]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r7, r0
	bne	.L2802
	mov	r1, r6
	mov	r0, r5
	bl	RemoveFrameStoreOutDPB
.L2802:
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	OutputFrmFromDPB, .-OutputFrmFromDPB
	.align	2
	.global	FlushDPB
	.type	FlushDPB, %function
FlushDPB:
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
	add	r6, r0, #24576
	mov	r4, r0
	ldr	r3, [r6, #2140]
	cmp	r3, #0
	beq	.L2805
	add	r7, r0, #26368
	mov	r5, #0
	add	r7, r7, #148
	b	.L2807
.L2806:
	ldr	r3, [r6, #2140]
	cmp	r3, r5
	bls	.L2805
.L2807:
	ldr	r1, [r7, #4]!
	add	r5, r5, #1
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2806
	mov	r0, r4
	bl	UnMarkFrameStoreRef
	ldr	r3, [r6, #2140]
	cmp	r3, r5
	bhi	.L2807
.L2805:
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L2809
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L2805
	b	.L2809
.L2811:
	bl	GetMinPOC
	ldr	r1, [fp, #-36]
	mov	r0, r4
	bl	OutputFrmFromDPB
	cmn	r0, #1
	beq	.L2810
.L2809:
	ldr	r3, [r6, #2140]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	bne	.L2811
	mov	r0, r3
.L2810:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	FlushDPB, .-FlushDPB
	.align	2
	.global	AdaptiveMemMark
	.type	AdaptiveMemMark, %function
AdaptiveMemMark:
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
	add	r3, r0, #57344
	add	r7, r0, #60160
	add	r2, r0, #26368
	ldr	r4, [r3, #3660]
	add	r7, r7, #192
	mov	r5, r0
	str	r3, [fp, #-56]
	add	r6, r4, #2000
	add	r4, r4, #4
	add	r6, r6, #4
	add	r3, r2, #212
	str	r3, [fp, #-52]
	add	r3, r0, #16384
	str	r3, [fp, #-48]
.L2832:
	ldr	r3, [r4]
	cmp	r3, #6
	ldrls	pc, [pc, r3, asl #2]
	b	.L2820
.L2822:
	.word	.L2821
	.word	.L2823
	.word	.L2824
	.word	.L2825
	.word	.L2826
	.word	.L2827
	.word	.L2828
.L2828:
	ldr	r2, [r4, #12]
	mov	r1, r7
	mov	r0, r5
	bl	MarkCurrPicLT
.L2820:
	add	r4, r4, #20
	cmp	r4, r6
	bne	.L2832
.L2821:
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #3444]
	cmp	r3, #1
	movne	r0, #0
	beq	.L2841
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2827:
	add	r8, r5, #24576
	ldr	r3, [r8, #2144]
	cmp	r3, #0
	ldrne	r9, [fp, #-52]
	movne	r10, #0
	beq	.L2831
.L2830:
	ldr	r1, [r9, #4]!
	mov	r0, r5
	bl	UnMarkFrameStoreRef
	ldr	r1, [r8, #2144]
	add	r10, r10, #1
	cmp	r10, r1
	bcc	.L2830
.L2831:
	mov	r0, r5
	bl	UpdateReflist
	mov	r1, #0
	mov	r0, r5
	bl	UpdateMaxLTFrmIdx
	mov	r0, r5
	bl	UpdateLTReflist
	ldr	r2, [fp, #-48]
	mov	r3, #1
	str	r3, [r2, #3444]
	b	.L2820
.L2826:
	mov	r0, r5
	ldr	r1, [r4, #16]
	bl	UpdateMaxLTFrmIdx
	mov	r0, r5
	bl	UpdateLTReflist
	b	.L2820
.L2825:
	ldr	r3, [r4, #12]
	mov	r1, r7
	ldr	r2, [r4, #4]
	mov	r0, r5
	bl	MarkSTToLTRef
	mov	r0, r5
	bl	UpdateReflist
	mov	r0, r5
	bl	UpdateLTReflist
	b	.L2820
.L2824:
	mov	r0, r5
	ldr	r2, [r4, #8]
	mov	r1, r7
	bl	UnMarkLTRef
	mov	r0, r5
	bl	UpdateLTReflist
	b	.L2820
.L2823:
	mov	r0, r5
	ldr	r2, [r4, #4]
	mov	r1, r7
	bl	UnMarkSTRef
	mov	r0, r5
	bl	UpdateReflist
	b	.L2820
.L2841:
	ldr	r1, [fp, #-56]
	mov	r3, #0
	ldrb	r2, [r1, #3011]	@ zero_extendqisi2
	str	r3, [r1, #3664]
	cmp	r2, #1
	beq	.L2835
	bcc	.L2836
	cmp	r2, #2
	bne	.L2834
	ldr	r2, [fp, #-56]
	str	r3, [r2, #3688]
	str	r3, [r2, #3676]
	ldr	r2, [fp, #-48]
	str	r3, [r2, #3456]
	str	r3, [r2, #3464]
.L2834:
	mov	r0, r5
	bl	FlushDPB
	adds	r0, r0, #0
	movne	r0, #1
	rsb	r0, r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2836:
	ldr	r0, [fp, #-56]
	ldr	r1, [r0, #3676]
	ldr	r2, [r0, #3684]
	ldr	r3, [r0, #3688]
	rsb	r2, r1, r2
	str	r2, [r0, #3684]
	rsb	r3, r1, r3
	str	r3, [r0, #3688]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r0, #3680]
	str	r3, [r0, #3676]
	ldr	r0, [fp, #-48]
	ldr	r1, [r0, #3464]
	ldr	r2, [r0, #3452]
	ldr	r3, [r0, #3456]
	rsb	r2, r1, r2
	str	r2, [r0, #3452]
	rsb	r3, r1, r3
	str	r3, [r0, #3456]
	cmp	r3, r2
	movge	r3, r2
	str	r3, [r0, #3460]
	str	r3, [r0, #3464]
	b	.L2834
.L2835:
	ldr	r2, [fp, #-56]
	str	r3, [r2, #3684]
	str	r3, [r2, #3676]
	ldr	r2, [fp, #-48]
	str	r3, [r2, #3452]
	str	r3, [r2, #3464]
	b	.L2834
	UNWIND(.fnend)
	.size	AdaptiveMemMark, .-AdaptiveMemMark
	.align	2
	.global	IDRMemMarking
	.type	IDRMemMarking, %function
IDRMemMarking:
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
	add	r3, r0, #57344
	str	r3, [fp, #-52]
	ldr	r3, [r3, #3660]
	str	r0, [fp, #-48]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2843
	add	r9, r0, #24576
	ldr	r3, [r9, #2140]
	cmp	r3, #0
	beq	.L2863
	ldr	r3, [fp, #-48]
	mov	r10, #0
	mov	r4, r10
	add	r8, r3, #26368
	add	r6, r3, #26624
	add	r6, r6, #20
	add	r5, r3, #61440
	mov	r7, r8
	add	r8, r8, #152
	add	r7, r7, #212
.L2849:
	ldr	r3, [r8]
	mov	r2, #0
	add	r10, r10, #1
	ldr	r1, [r3, #816]
	cmp	r1, #1
	streq	r1, [r5, #1044]
	strb	r4, [r3, #698]
	strb	r4, [r3, #697]
	ldr	r3, [r8]
	strb	r4, [r3, #738]
	strb	r4, [r3, #737]
	ldr	r3, [r8]
	strb	r4, [r3, #778]
	strb	r4, [r3, #777]
	ldr	r3, [r8]
	strb	r4, [r3, #2]
	ldr	r3, [r8]
	ldr	r0, [r5, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetRef
	ldr	r3, [r8]
	mov	r2, #1
	ldr	r1, [fp, #-48]
	strb	r4, [r3, #1]
	ldr	r3, [r8]
	strb	r4, [r3, #4]
	ldr	r3, [r8]
	str	r2, [r3, #668]
	ldr	r2, [r8]
	ldr	r3, [r2, #688]
	add	r3, r3, #6656
	add	r3, r3, #26
	add	r3, r1, r3, lsl #2
	str	r4, [r3, #4]
	ldr	r1, [r2, #648]
	ldr	r0, [r5, #2344]
	bl	FSP_GetDisplay
	mov	r2, #0
	cmp	r0, #3
	beq	.L2848
	ldr	r3, [r8]
	ldr	r0, [r5, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetDisplay
.L2848:
	str	r4, [r8], #4
	str	r4, [r7, #4]!
	str	r4, [r6, #4]!
	ldr	r3, [r9, #2140]
	cmp	r3, r10
	bhi	.L2849
.L2850:
	mov	r3, #0
	str	r3, [r9, #2140]
	ldr	r1, [r5, #1032]
	cmp	r1, r3
	beq	.L2846
	ldr	r2, [fp, #-48]
	mov	r0, r3
	add	r2, r2, #62208
	add	r2, r2, #188
.L2853:
	add	r3, r3, #1
	str	r0, [r2, #4]!
	cmp	r3, r1
	bne	.L2853
.L2846:
	ldr	r4, [fp, #-48]
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	ldr	r3, [fp, #-52]
	ldr	r3, [r3, #3660]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2864
	ldr	r2, [fp, #-52]
	mov	r0, r3
	str	r3, [r9, #2152]
	strb	r3, [r2, #3012]
	mov	r3, #1
	strb	r3, [r2, #3013]
.L2854:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2864:
	ldr	r1, [fp, #-52]
	mov	r3, #0
	mov	r2, #1
	mov	r0, r3
	str	r2, [r9, #2152]
	strb	r2, [r1, #3012]
	str	r3, [r1, #3668]
	strb	r3, [r1, #3013]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2843:
	bl	FlushDPB
	cmp	r0, #0
	bne	.L2855
	ldr	r3, [fp, #-48]
	add	r9, r3, #24576
	b	.L2846
.L2863:
	add	r5, r0, #61440
	b	.L2850
.L2855:
	mvn	r0, #0
	b	.L2854
	UNWIND(.fnend)
	.size	IDRMemMarking, .-IDRMemMarking
	.align	2
	.global	Marking
	.type	Marking, %function
Marking:
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
	add	r6, r0, #16384
	add	r4, r0, #57344
	mov	r3, #0
	mov	r5, r0
	str	r3, [r6, #3444]
	ldrb	r3, [r4, #3011]	@ zero_extendqisi2
	sub	r3, r3, #2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r6, #3448]
	ldrb	r3, [r4, #3014]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L2866
	ldr	r3, [r4, #3692]
	cmp	r3, #0
	bne	.L2867
	ldr	r3, [r0]
	ldr	r2, [r3, #652]
	cmp	r2, #1
	beq	.L2891
.L2867:
	ldr	r3, [r4, #3660]
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, [r4, #3672]
	beq	.L2892
	cmp	r3, #0
	bne	.L2893
.L2874:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2892:
	cmp	r3, #0
	beq	.L2874
.L2873:
	ldrb	r2, [r4, #3009]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2878
	add	r2, r5, #24576
	ldr	r1, [r6, #456]
	ldr	ip, [r2, #2148]
	ldr	r0, [r2, #2144]
	rsb	r2, ip, r1
	cmp	r0, r2
	beq	.L2894
.L2879:
	mov	r2, #0
	strb	r2, [r4, #3012]
.L2876:
	cmp	r3, #0
	beq	.L2874
.L2878:
	ldrb	r3, [r4, #3012]	@ zero_extendqisi2
	mov	r0, #0
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r4, #3013]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2891:
	ldr	r2, [r3, #648]
	cmp	r2, #0
	bne	.L2867
	ldr	r2, [r3, #656]
	cmp	r2, #0
	bne	.L2867
	ldr	r3, [r3, #612]
	add	r3, r3, #1024
	cmp	r3, #2048
	bls	.L2867
.L2866:
	mov	r0, r5
	bl	IDRMemMarking
	cmp	r0, #0
	bne	.L2868
.L2875:
	ldrb	r3, [r4, #3014]	@ zero_extendqisi2
	cmp	r3, #5
	ldreq	r3, [r4, #3672]
	beq	.L2876
	ldr	r3, [r4, #3672]
	cmp	r3, #0
	beq	.L2874
	ldr	r2, [r4, #3660]
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2873
	b	.L2878
.L2893:
	mov	r0, r5
	bl	AdaptiveMemMark
	cmp	r0, #0
	beq	.L2875
.L2868:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L2894:
	mov	r0, r5
	bl	SlidingWinMark.part.4
	ldr	r3, [r4, #3672]
	b	.L2879
	UNWIND(.fnend)
	.size	Marking, .-Marking
	.align	2
	.global	DirectOutput
	.type	DirectOutput, %function
DirectOutput:
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
	add	r5, r0, #57344
	mov	r6, r0
	ldrb	r7, [r5, #3011]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L2897
	bcc	.L2898
	cmp	r7, #2
	beq	.L2899
	mov	r7, #0
.L2896:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2899:
	ldr	r3, [r5, #3656]
	mov	r2, #3
	add	r4, r0, #61440
	strb	r2, [r3, #696]
	ldrb	r2, [r5, #3009]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2918
	ldr	r1, [r4, #396]
	cmp	r1, #0
	beq	.L2919
	bl	OutputFrmToVO
	subs	r7, r0, #0
	bne	.L2986
.L2920:
	ldr	r3, [r5, #3656]
	str	r3, [r4, #396]
	str	r3, [r3, #812]
.L2921:
	ldr	r3, [r4, #396]
	mov	r9, #2
	ldrb	r0, [r5, #3010]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #632
	add	r1, r5, #3024
	strb	r0, [r3]
	ldr	r3, [r4, #396]
	strb	r9, [r3, #1]
	ldr	r3, [r4, #396]
	strb	r8, [r3, #4]
	ldr	r3, [r4, #396]
	str	r8, [r3, #668]
	ldr	r3, [r4, #396]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #396]
	ldr	r0, [r5, #3692]
	str	r0, [r3, #676]
	ldr	r3, [r4, #396]
	str	r8, [r3, #672]
	ldr	r0, [r4, #396]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r4, #396]
	ldr	r2, [r5, #3700]
	str	r2, [r3, #792]
	ldr	r3, [r4, #396]
	ldr	r2, [r3, #792]
	str	r2, [r3, #712]
	str	r2, [r3, #680]
	ldr	r3, [r4, #396]
	strb	r9, [r3, #776]
	ldrb	r2, [r5, #3015]	@ zero_extendqisi2
	ldr	r3, [r4, #396]
	cmp	r2, #1
	moveq	r2, r9
	movne	r2, r8
	strb	r2, [r3, #3]
	ldr	r9, [r4, #2276]
	cmp	r9, #1
	bne	.L2896
.L2981:
	ldr	r3, [r4, #396]
	mov	r2, r8
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetRef
	mov	r2, r8
	mov	r0, r6
	ldr	r1, [r4, #396]
	bl	OutputFrmToVO
	ldr	r3, [r4, #396]
	cmp	r3, r8
	mov	r7, r0
	beq	.L2931
	ldr	r3, [r5, #3656]
	mov	r2, r9
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_ClearLogicFs
	b	.L2931
.L2898:
	ldr	r3, [r5, #3656]
	add	r4, r0, #61440
	mov	r2, #0
	strb	r2, [r3, #696]
	ldr	r1, [r4, #396]
	cmp	r1, r2
	beq	.L2900
	bl	OutputFrmToVO
	cmp	r0, #0
	bne	.L2987
.L2901:
	ldr	r3, [r4, #396]
	cmp	r3, #0
	beq	.L2900
	ldr	r3, [r5, #3656]
	mov	r2, #1
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_ClearLogicFs
.L2900:
	ldr	r3, [r5, #3656]
	mov	r0, #3
	mov	r8, #0
	mov	r2, #632
	add	r1, r5, #3024
	str	r3, [r4, #396]
	str	r3, [r3, #732]
	ldr	r3, [r4, #396]
	ldr	ip, [r5, #3656]
	str	ip, [r3, #772]
	ldr	r3, [r4, #396]
	ldr	ip, [r5, #3656]
	str	ip, [r3, #812]
	ldrb	ip, [r5, #3010]	@ zero_extendqisi2
	ldr	r3, [r4, #396]
	strb	ip, [r3]
	ldr	r3, [r4, #396]
	strb	r0, [r3, #1]
	ldr	r3, [r4, #396]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #396]
	strb	r8, [r3, #4]
	ldr	r3, [r4, #396]
	str	r8, [r3, #668]
	ldr	r0, [r4, #396]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r4, #396]
	ldr	r1, [r5, #3700]
	mov	r2, r8
	str	r1, [r3, #712]
	str	r1, [r3, #680]
	ldr	r3, [r4, #396]
	strb	r8, [r3, #696]
	ldr	r3, [r4, #396]
	ldr	r1, [r5, #3692]
	str	r1, [r3, #676]
	ldr	r3, [r4, #396]
	ldrb	r1, [r5, #3017]	@ zero_extendqisi2
	str	r1, [r3, #672]
	ldrb	r1, [r5, #3015]	@ zero_extendqisi2
	ldr	r3, [r4, #396]
	cmp	r1, #1
	moveq	r7, #3
	strb	r7, [r3, #3]
	ldr	r3, [r4, #396]
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetRef
	mov	r2, r8
	mov	r0, r6
	ldr	r1, [r4, #396]
	bl	OutputFrmToVO
	ldr	r3, [r4, #396]
	cmp	r3, r8
	mov	r7, r0
	beq	.L2931
.L2979:
	ldr	r3, [r5, #3656]
	mov	r2, #1
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_ClearLogicFs
.L2931:
	mov	r3, #0
	mov	r0, r7
	str	r3, [r4, #396]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2897:
	ldr	r3, [r5, #3656]
	mov	r2, #3
	add	r4, r0, #61440
	strb	r2, [r3, #696]
	ldrb	r2, [r5, #3009]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L2905
	ldr	r1, [r4, #396]
	cmp	r1, #0
	beq	.L2906
	bl	OutputFrmToVO
	subs	r7, r0, #0
	bne	.L2988
.L2907:
	ldr	r3, [r5, #3656]
	str	r3, [r4, #396]
	str	r3, [r3, #772]
.L2908:
	ldr	r3, [r4, #396]
	mov	r9, #1
	ldrb	r0, [r5, #3010]	@ zero_extendqisi2
	mov	r8, #0
	mov	r2, #632
	add	r1, r5, #3024
	strb	r0, [r3]
	ldr	r3, [r4, #396]
	strb	r9, [r3, #1]
	ldr	r3, [r4, #396]
	strb	r8, [r3, #4]
	ldr	r3, [r4, #396]
	str	r8, [r3, #668]
	ldr	r3, [r4, #396]
	strb	r8, [r3, #2]
	ldr	r3, [r4, #396]
	ldr	r0, [r5, #3692]
	str	r0, [r3, #676]
	ldr	r3, [r4, #396]
	str	r8, [r3, #672]
	ldr	r0, [r4, #396]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r4, #396]
	ldr	r2, [r5, #3700]
	str	r2, [r3, #752]
	ldr	r3, [r4, #396]
	ldr	r2, [r3, #752]
	str	r2, [r3, #712]
	str	r2, [r3, #680]
	ldr	r3, [r4, #396]
	strb	r9, [r3, #736]
	ldrb	r3, [r5, #3015]	@ zero_extendqisi2
	ldr	r2, [r4, #396]
	rsb	r3, r9, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r2, #3]
	ldr	r9, [r4, #2276]
	cmp	r9, #1
	beq	.L2981
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L2918:
	ldr	lr, [r4, #396]
	mov	r2, #632
	add	r1, r5, #3024
	cmp	lr, #0
	ldreq	r3, [r5, #3656]
	streq	r3, [r4, #396]
	streq	r3, [r3, #812]
	ldreq	lr, [r4, #396]
	add	r7, lr, #608
	add	r10, lr, #624
	ldr	ip, [lr, #600]
	add	r0, lr, #16
	ldrd	r8, [r7]
	ldr	r3, [lr, #604]
	ldr	r7, [lr, #28]
	strd	r8, [fp, #-52]
	ldrd	r8, [r10, #-8]
	str	ip, [fp, #-68]
	ldr	r10, [lr, #16]
	strd	r8, [fp, #-60]
	str	r3, [fp, #-64]
	ldr	r9, [lr, #20]
	ldr	r8, [lr, #24]
	bl	memcpy
	add	r2, r6, #60928
	ldr	r3, [fp, #-64]
	add	r2, r2, #32
	ldr	ip, [fp, #-68]
	ldr	r0, [r2, #-8]
	ldr	r2, [r2, #-4]
	and	r1, ip, r3
	and	r0, r0, r2
	adds	r2, r1, #1
	movne	r2, #1
	cmn	r0, #1
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r4, #396]
	strne	ip, [r2, #600]
	strne	r3, [r2, #604]
	movw	r3, #60960
	ldr	r1, [r4, #396]
	ldrd	r2, [r3, r6]
	add	ip, r1, #608
	ldrd	r0, [fp, #-52]
	cmp	r3, r1
	cmpeq	r2, r0
	movhi	r2, r0
	movhi	r3, r1
	add	r0, r6, #60928
	strd	r2, [ip]
	ldr	r1, [r4, #396]
	ldrd	r2, [r0, #40]
	add	ip, r1, #624
	ldrd	r0, [fp, #-60]
	cmp	r3, r1
	cmpeq	r2, r0
	movhi	r2, r0
	movhi	r3, r1
	strd	r2, [ip, #-8]
	mov	ip, #2
	ldr	r3, [r5, #3024]
	mov	r0, #3
	ldr	r2, [r4, #396]
	cmp	r3, r10
	movcs	r3, r10
	str	r3, [r2, #16]
	ldr	r3, [r5, #3028]
	ldr	r2, [r4, #396]
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r2, #20]
	ldr	r3, [r5, #3032]
	ldr	r2, [r4, #396]
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r2, #24]
	ldr	r3, [r5, #3036]
	ldr	r2, [r4, #396]
	cmp	r3, r7
	movcs	r3, r7
	str	r3, [r2, #28]
	ldr	r2, [r4, #396]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #3010]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r2, [r4, #396]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #1]
	ldr	r2, [r4, #396]
	ldr	r1, [r5, #3692]
	ldr	r3, [r2, #676]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #676]
	ldr	r3, [r4, #396]
	strb	ip, [r3, #776]
	ldr	r3, [r4, #396]
	strb	r0, [r3, #696]
	ldr	r3, [r4, #396]
	ldr	r2, [r5, #3700]
	str	r2, [r3, #792]
	ldr	r2, [r4, #396]
	ldr	r3, [r2, #792]
	ldr	r1, [r2, #752]
	add	r3, r3, r1
	mov	r3, r3, lsr #1
	str	r3, [r2, #712]
	ldr	r3, [r4, #396]
	ldr	r2, [r3, #712]
	str	r2, [r3, #680]
	ldr	r3, [r4, #396]
	ldr	r2, [r3, #812]
	str	r2, [r3, #732]
	ldrb	r3, [r5, #3015]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #396]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	beq	.L2983
.L2930:
	strb	r2, [r3, #3]
	mov	r2, #0
	ldr	r3, [r4, #396]
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetRef
	mov	r0, r6
	mov	r2, #0
	ldr	r1, [r4, #396]
	bl	OutputFrmToVO
	ldr	r3, [r4, #396]
	cmp	r3, #0
	mov	r7, r0
	bne	.L2979
	b	.L2931
.L2905:
	ldr	lr, [r4, #396]
	mov	r2, #632
	add	r1, r5, #3024
	cmp	lr, #0
	ldreq	r3, [r5, #3656]
	streq	r3, [r4, #396]
	streq	r3, [r3, #772]
	ldreq	lr, [r4, #396]
	add	r7, lr, #608
	add	r10, lr, #624
	ldr	ip, [lr, #600]
	add	r0, lr, #16
	ldrd	r8, [r7]
	ldr	r3, [lr, #604]
	ldr	r7, [lr, #28]
	strd	r8, [fp, #-52]
	ldrd	r8, [r10, #-8]
	str	ip, [fp, #-68]
	ldr	r10, [lr, #16]
	strd	r8, [fp, #-60]
	str	r3, [fp, #-64]
	ldr	r9, [lr, #20]
	ldr	r8, [lr, #24]
	bl	memcpy
	add	r2, r6, #60928
	ldr	r3, [fp, #-64]
	add	r2, r2, #32
	ldr	ip, [fp, #-68]
	ldr	r0, [r2, #-8]
	ldr	r2, [r2, #-4]
	and	r1, ip, r3
	and	r0, r0, r2
	adds	r2, r1, #1
	movne	r2, #1
	cmn	r0, #1
	movne	r2, #0
	cmp	r2, #0
	ldrne	r2, [r4, #396]
	strne	ip, [r2, #600]
	strne	r3, [r2, #604]
	movw	r3, #60960
	ldr	r1, [r4, #396]
	ldrd	r2, [r3, r6]
	add	ip, r1, #608
	ldrd	r0, [fp, #-52]
	cmp	r3, r1
	cmpeq	r2, r0
	movhi	r2, r0
	movhi	r3, r1
	add	r0, r6, #60928
	strd	r2, [ip]
	ldr	r1, [r4, #396]
	ldrd	r2, [r0, #40]
	add	ip, r1, #624
	ldrd	r0, [fp, #-60]
	cmp	r3, r1
	cmpeq	r2, r0
	movhi	r2, r0
	movhi	r3, r1
	strd	r2, [ip, #-8]
	mov	ip, #1
	ldr	r3, [r5, #3024]
	mov	r0, #3
	ldr	r2, [r4, #396]
	cmp	r3, r10
	movcs	r3, r10
	str	r3, [r2, #16]
	ldr	r3, [r5, #3028]
	ldr	r2, [r4, #396]
	cmp	r3, r9
	movcs	r3, r9
	str	r3, [r2, #20]
	ldr	r3, [r5, #3032]
	ldr	r2, [r4, #396]
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r2, #24]
	ldr	r3, [r5, #3036]
	ldr	r2, [r4, #396]
	cmp	r3, r7
	movcs	r3, r7
	str	r3, [r2, #28]
	ldr	r2, [r4, #396]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r5, #3010]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r2, [r4, #396]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, ip
	strb	r3, [r2, #1]
	ldr	r2, [r4, #396]
	ldr	r1, [r5, #3692]
	ldr	r3, [r2, #676]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #676]
	ldr	r3, [r4, #396]
	strb	ip, [r3, #736]
	ldr	r3, [r4, #396]
	strb	r0, [r3, #696]
	ldr	r3, [r4, #396]
	ldr	r2, [r5, #3700]
	str	r2, [r3, #752]
	ldr	r2, [r4, #396]
	ldr	r3, [r2, #792]
	ldr	r1, [r2, #752]
	add	r3, r3, r1
	mov	r3, r3, lsr ip
	str	r3, [r2, #712]
	ldr	r3, [r4, #396]
	ldr	r2, [r3, #712]
	str	r2, [r3, #680]
	ldr	r3, [r4, #396]
	ldr	r2, [r3, #772]
	str	r2, [r3, #732]
	ldrb	r3, [r5, #3015]	@ zero_extendqisi2
	cmp	r3, ip
	ldr	r3, [r4, #396]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	bne	.L2930
.L2983:
	orr	r2, r2, ip
	b	.L2930
.L2987:
	str	r0, [sp]
	movw	r3, #2628
	ldr	r2, .L2989
	mov	r0, #22
	ldr	r1, .L2989+4
	bl	dprint_vfmw
	b	.L2901
.L2919:
	ldr	r3, [r5, #3656]
	mov	r7, r1
	str	r3, [r4, #396]
	str	r3, [r3, #812]
	b	.L2921
.L2906:
	ldr	r3, [r5, #3656]
	mov	r7, r1
	str	r3, [r4, #396]
	str	r3, [r3, #772]
	b	.L2908
.L2986:
	str	r7, [sp]
	movw	r3, #2796
	ldr	r2, .L2989
	mov	r0, #22
	ldr	r1, .L2989+4
	bl	dprint_vfmw
	b	.L2920
.L2988:
	str	r7, [sp]
	movw	r3, #2680
	ldr	r2, .L2989
	mov	r0, #22
	ldr	r1, .L2989+4
	bl	dprint_vfmw
	b	.L2907
.L2990:
	.align	2
.L2989:
	.word	.LANCHOR0+264
	.word	.LC357
	UNWIND(.fnend)
	.size	DirectOutput, .-DirectOutput
	.align	2
	.global	H264DEC_GetRemainImg
	.type	H264DEC_GetRemainImg, %function
H264DEC_GetRemainImg:
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
	add	r5, r0, #24576
	mov	r4, r0
	ldr	r3, [r5, #2140]
	cmp	r3, #0
	beq	.L2993
	add	r7, r0, #26368
	mov	r6, #0
	add	r7, r7, #148
	b	.L2995
.L2994:
	ldr	r3, [r5, #2140]
	cmp	r3, r6
	bls	.L2993
.L2995:
	ldr	r1, [r7, #4]!
	add	r6, r6, #1
	ldrb	r3, [r1, #2]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2994
	mov	r0, r4
	bl	UnMarkFrameStoreRef
	ldr	r3, [r5, #2140]
	cmp	r3, r6
	bhi	.L2995
.L2993:
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	bne	.L2993
	mvn	r6, #0
.L2997:
	ldr	r3, [r5, #2140]
	sub	r2, fp, #36
	sub	r1, fp, #32
	mov	r0, r4
	cmp	r3, #0
	beq	.L3009
	bl	GetMinPOC
	ldr	r3, [fp, #-36]
	mov	r1, #0
	mov	r0, r4
	add	r3, r4, r3, lsl #2
	add	r3, r3, #24576
	ldr	r2, [r3, #1944]
	strb	r1, [r2, #4]
	ldr	r1, [r3, #1944]
	ldr	r2, [r5, #2140]
	bl	OutputFrmToVO
	ldr	r1, [fp, #-36]
	add	r3, r1, #6592
	add	r3, r3, #38
	ldr	r3, [r4, r3, asl #2]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r6, r0
	bne	.L2997
	mov	r0, r4
	bl	RemoveFrameStoreOutDPB
	b	.L2997
.L3009:
	cmp	r6, #0
	beq	.L3000
	add	r0, r4, #8
	bl	GetVoLastImageID
	mov	r6, r0
.L3000:
	mov	r0, r6
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	H264DEC_GetRemainImg, .-H264DEC_GetRemainImg
	.align	2
	.global	InitDPB
	.type	InitDPB, %function
InitDPB:
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
	subs	r7, r0, #0
	beq	.L3025
	bl	ClearAllSlice
	add	r6, r7, #26368
	add	r5, r7, #26624
	mov	r8, #0
	mov	r4, r6
	add	r5, r5, #24
	add	r6, r6, #152
	add	r4, r4, #216
	add	r10, r7, #61440
	mov	r9, r8
.L3015:
	ldr	r3, [r6]
	mov	r2, #1
	add	r8, r8, r2
	cmp	r3, #0
	beq	.L3012
	ldr	r1, [r3, #648]
	ldr	r0, [r10, #2344]
	bl	FSP_ClearLogicFs
.L3012:
	ldr	r3, [r4]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3013
	ldr	r1, [r3, #648]
	ldr	r0, [r10, #2344]
	bl	FSP_ClearLogicFs
.L3013:
	ldr	r3, [r5]
	mov	r2, #1
	cmp	r3, #0
	beq	.L3014
	ldr	r1, [r3, #648]
	ldr	r0, [r10, #2344]
	bl	FSP_ClearLogicFs
.L3014:
	cmp	r8, #16
	str	r9, [r5], #4
	mov	r2, #0
	str	r9, [r4], #4
	str	r9, [r6], #4
	bne	.L3015
	add	r3, r7, #16384
	add	r4, r7, #24576
	ldr	r3, [r3, #484]
	str	r2, [r4, #2140]
	sub	r3, r3, #1
	str	r2, [r4, #2144]
	str	r3, [r4, #2136]
	str	r2, [r4, #2148]
	str	r2, [r4, #2152]
	ldr	r1, [r10, #396]
	cmp	r1, r2
	beq	.L3017
	ldr	r3, [r10, #2272]
	cmp	r3, #2
	beq	.L3048
.L3018:
	ldr	r1, [r1, #648]
	mov	r2, #1
	ldr	r0, [r10, #2344]
	bl	FSP_ClearLogicFs
	add	r3, r7, #57344
	ldr	r3, [r3, #3656]
	cmp	r3, #0
	beq	.L3021
	ldr	r2, [r10, #396]
	ldr	r1, [r3, #648]
	ldr	r3, [r2, #648]
	cmp	r3, r1
	beq	.L3021
	mov	r2, #1
	ldr	r0, [r10, #2344]
	bl	FSP_ClearLogicFs
.L3021:
	mov	r3, #0
	str	r3, [r10, #396]
.L3017:
	ldr	r3, .L3050
	add	r0, r7, #26624
	mov	r2, #392
	mov	r1, #0
	add	r0, r0, #108
	ldr	r3, [r3, #48]
	blx	r3
	ldr	ip, [r4, #2136]
	add	r3, r7, #62208
	mov	r0, #0
	add	r3, r3, #188
	add	r1, r7, #62464
	mov	r2, r0
	str	ip, [r4, #2412]
	str	r0, [r4, #2416]
.L3022:
	str	r2, [r3, #4]!
	cmp	r3, r1
	bne	.L3022
	add	r2, r7, #26880
	add	r3, r7, #27136
	add	r2, r2, #240
	add	r3, r3, #116
	mov	r0, #0
.L3023:
	str	r0, [r2, #4]!
	cmp	r2, r3
	mov	r1, #0
	bne	.L3023
	add	r2, r7, #27136
	add	r7, r7, #20480
	add	r2, r2, #248
	mov	ip, r1
	str	r1, [r7, #248]
.L3024:
	str	ip, [r3, #4]!
	cmp	r3, r2
	mov	r0, #0
	bne	.L3024
	str	r0, [r7, #252]
.L3011:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3048:
	mov	r0, r7
	bl	OutputFrmToVO
	cmp	r0, #0
	bne	.L3049
.L3019:
	ldr	r1, [r10, #396]
	cmp	r1, #0
	beq	.L3017
	b	.L3018
.L3049:
	str	r0, [sp]
	movw	r3, #5433
	ldr	r2, .L3050+4
	mov	r0, #22
	ldr	r1, .L3050+8
	bl	dprint_vfmw
	b	.L3019
.L3025:
	mvn	r0, #0
	b	.L3011
.L3051:
	.align	2
.L3050:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+280
	.word	.LC357
	UNWIND(.fnend)
	.size	InitDPB, .-InitDPB
	.align	2
	.global	ClearDPB
	.type	ClearDPB, %function
ClearDPB:
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
	bl	FlushDPB
	subs	r3, r0, #0
	beq	.L3053
	movw	r2, #494
	ldr	r1, .L3057
	mov	r0, #0
	bl	dprint_vfmw
.L3053:
	mov	r0, r4
	add	r4, r4, #61440
	bl	InitDPB
	mov	r3, #0
	mov	r0, r3
	str	r3, [r4, #1044]
	str	r3, [r4, #2348]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3058:
	.align	2
.L3057:
	.word	.LC358
	UNWIND(.fnend)
	.size	ClearDPB, .-ClearDPB
	.align	2
	.global	DecVDM
	.type	DecVDM, %function
DecVDM:
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
	add	r6, r0, #57344
	mov	r7, r0
	add	r4, r0, #61440
	ldrb	r3, [r6, #3011]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3060
	ldrb	r3, [r6, #3009]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3060
.L3061:
	ldr	r5, [r4, #2332]
	ldr	r3, [r4, #2272]
	ubfx	r5, r5, #16, #3
	cmp	r3, r5
	beq	.L3062
	subs	r2, r5, #2
	sub	r3, r3, #2
	movne	r2, #1
	cmp	r3, #1
	movhi	r2, #0
	cmp	r2, #0
	beq	.L3062
	cmp	r5, #4
	cmpne	r5, #1
	bls	.L3153
.L3062:
	cmp	r5, #2
	str	r5, [r4, #2272]
	beq	.L3065
	cmp	r5, #3
	beq	.L3066
	cmp	r5, #1
	beq	.L3154
	ldr	r3, [r4, #2268]
	cmp	r3, #0
	beq	.L3069
	cmp	r5, #4
	ldr	r3, [r6, #3692]
	beq	.L3155
.L3076:
	cmp	r3, #2
	beq	.L3093
.L3080:
	cmp	r3, #1
	streq	r3, [r4, #1048]
.L3082:
	ldr	r2, [r4, #2308]
	mov	r0, #2
	ldrb	r3, [r6, #3011]	@ zero_extendqisi2
	sub	r2, r2, #1
	ldr	r1, .L3160
	bl	dprint_vfmw
	ldr	r0, [r6, #3716]
	ldr	r1, [r4, #2308]
	mov	r3, #1
	ldr	r2, [r4, #2268]
	str	r0, [r4, #1820]
	cmp	r1, #0
	strb	r3, [r4, #1082]
	ldr	r3, [r6, #3720]
	str	r2, [r4, #2020]
	str	r3, [r4, #1816]
	beq	.L3084
	ldr	r1, [r6, #3692]
	cmp	r1, #0
	beq	.L3156
	add	r3, r7, #24576
	ldr	r3, [r3, #2140]
	cmp	r3, #0
	bne	.L3086
	ldr	r2, [r7]
	ldr	r1, [r2, #24]
	cmp	r1, #2
	bne	.L3157
.L3089:
	add	r3, r7, #62464
	add	r3, r3, #56
	str	r3, [r7, #360]
	ldr	r1, [r2, #880]
	cmp	r1, #1
	beq	.L3158
	cmp	r1, #2
	bne	.L3092
	ldr	r1, [r2, #884]
	cmp	r3, #0
	cmpne	r1, #0
	ble	.L3092
	ldr	r3, [r6, #3692]
	cmp	r3, #2
	bne	.L3092
	mov	r2, #0
	str	r2, [r7, #360]
	ldr	r3, [r6, #3656]
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetDisplay
	ldr	r2, [r7]
	mov	r0, r7
	ldr	r3, [r2, #884]
	sub	r3, r3, #1
	str	r3, [r2, #884]
	bl	H264_ClearCurrPic
	mvn	r0, #0
	b	.L3145
.L3060:
	ldr	r3, [r4, #2368]
	ldr	r2, [r4, #2372]
	add	r3, r3, #1
	cmp	r3, r2
	movlt	r3, r2
	str	r3, [r4, #2368]
	ldr	r1, [r7]
	rsb	r3, r2, r3
	str	r3, [r1, #576]
	b	.L3061
.L3153:
	mov	r2, r5
	ldr	r1, .L3160+4
	mov	r0, #2
	bl	dprint_vfmw
	str	r5, [r4, #2272]
.L3066:
	mov	r0, r7
	bl	H264_ClearCurrPic
	mov	r0, r7
	bl	ClearDPB
	mvn	r0, #0
.L3145:
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3084:
	ldr	r2, [r7]
.L3092:
	ldr	r3, [r2, #592]
	mov	r0, #0
	strb	r3, [r4, #1084]
	ldr	r3, [r2, #600]
	str	r3, [r4, #1088]
	ldr	r3, [r2, #604]
	str	r3, [r4, #1092]
	ldr	r3, [r2, #596]
	strb	r3, [r4, #1085]
	ldr	r3, [r2, #644]
	strb	r3, [r4, #1096]
	ldr	ip, [r6, #3732]
	ldr	r1, [r6, #3656]
	ldr	r3, [r6, #3728]
	str	ip, [r6, #3728]
	ldr	r2, [r1, #256]
	rsb	r3, ip, r3
	add	r2, r2, r3
	str	r2, [r1, #256]
	ldr	r2, [r6, #3264]
	add	r3, r3, r2
	str	r3, [r6, #3264]
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3065:
	ldr	r5, [r6, #3692]
	cmp	r5, #0
	bne	.L3072
	ldr	r3, [r4, #2268]
	cmp	r3, #0
	beq	.L3069
	ldr	r3, [r4, #2264]
	ldr	r3, [r3, #48]
	cmp	r3, #0
	beq	.L3082
	mov	r3, #1
	mov	r0, r7
	strb	r3, [r6, #3015]
	bl	H264_ClearCurrPic
	mov	r0, r5
	ldr	r1, .L3160+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3145
.L3154:
	ldr	r3, [r6, #3692]
	cmp	r3, #2
	beq	.L3159
	ldr	r2, [r4, #2268]
	cmp	r2, #0
	bne	.L3080
.L3069:
	mov	r0, r7
	bl	H264_ClearCurrPic
	ldr	r3, .L3160+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3149
	mov	r3, #0
	ldr	r0, [r4, #2344]
	mov	r2, r3
	mov	r1, #127
	blx	ip
	mvn	r0, #0
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L3156:
	ldr	r3, .L3160+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3086
	ldr	r2, [r4, #2024]
	cmp	r2, #0
	beq	.L3087
.L3088:
	ldr	r3, [r2, #8]
	ldr	r0, [r2, #12]
	ldr	r2, [r2, #4056]
	add	r3, r3, r0
	add	r3, r3, #7
	cmp	r2, #0
	add	r1, r1, r3, lsr #3
	bne	.L3088
.L3087:
	sub	r2, fp, #28
	mov	r3, #4
	ldr	r0, [r4, #2344]
	str	r1, [r2, #-4]!
	mov	r1, #20
	blx	ip
	ldr	r2, [r7]
	b	.L3089
.L3159:
	ldr	r3, [r6, #3672]
	cmp	r3, #0
	beq	.L3072
	ldr	r3, [r4, #2268]
	cmp	r3, #0
	beq	.L3069
.L3093:
	ldr	r3, [r4, #1048]
	cmp	r3, #2
	bne	.L3082
	ldr	r3, [r7]
	ldr	r5, [r3, #24]
	cmp	r5, #0
	bne	.L3082
	ldr	r3, .L3160+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3082
	ldr	r3, [r6, #3672]
	mov	r0, #1
	ldr	r2, [r6, #3676]
	ldr	r1, .L3160+20
	bl	dprint_vfmw
	mov	r0, r7
	bl	H264_ClearCurrPic
	ldr	r3, .L3160+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3083
	mov	r3, r5
	mov	r2, r5
	mov	r1, #127
	ldr	r0, [r4, #2344]
	blx	ip
.L3083:
	ldr	r3, [r6, #3656]
	mov	r2, #0
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetDisplay
	mvn	r0, #0
	b	.L3145
.L3158:
	cmp	r3, #0
	beq	.L3092
	ldr	r3, [r6, #3692]
	cmp	r3, #2
	bne	.L3092
	mov	r2, #0
	str	r2, [r7, #360]
	ldr	r3, [r6, #3656]
	ldr	r0, [r4, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_SetDisplay
.L3148:
	mov	r0, r7
	bl	H264_ClearCurrPic
.L3149:
	mvn	r0, #0
	b	.L3145
.L3155:
	cmp	r3, #0
	bne	.L3076
	ldr	r3, [r4, #1048]
	cmp	r3, #0
	moveq	r3, #2
	streq	r3, [r4, #1048]
	movne	r3, #1
	strne	r3, [r4, #1048]
	b	.L3082
.L3086:
	ldr	r2, [r7]
	b	.L3089
.L3157:
	ldr	r2, .L3160+12
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L3148
	ldr	r0, [r4, #2344]
	mov	r2, r3
	mov	r1, #127
	blx	ip
	b	.L3148
.L3072:
	mov	r3, #1
	mov	r0, r7
	strb	r3, [r6, #3015]
	bl	H264_ClearCurrPic
	mvn	r0, #0
	b	.L3145
.L3161:
	.align	2
.L3160:
	.word	.LC362
	.word	.LC359
	.word	.LC360
	.word	g_event_report
	.word	g_allow_B_before_P
	.word	.LC361
	UNWIND(.fnend)
	.size	DecVDM, .-DecVDM
	.align	2
	.global	H264_FlushDecoder
	.type	H264_FlushDecoder, %function
H264_FlushDecoder:
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
	add	r2, r0, #20480
	mov	r1, #0
	mov	r4, #1
	str	r1, [r2, #256]
	strb	r4, [r2, #213]
	str	r4, [r0, #364]
	bl	DecVDM
	cmp	r0, #0
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	mov	r0, r4
	ldr	r1, .L3164
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	b	dprint_vfmw
.L3165:
	.align	2
.L3164:
	.word	.LC363
	UNWIND(.fnend)
	.size	H264_FlushDecoder, .-H264_FlushDecoder
	.align	2
	.global	H264_VES_Splitter
	.type	H264_VES_Splitter, %function
H264_VES_Splitter:
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
	add	r4, r0, #13504
	add	r4, r4, #24
	add	r8, r0, #57344
	mov	r7, r1
	mov	r5, r0
	mov	r1, #24
	mov	r0, r4
	mov	r10, r3
	mov	r6, #0
	mov	r9, r2
	str	r6, [fp, #-48]
	bl	BsSkip
	ldr	r3, [r8, #3456]
	cmp	r7, r6
	str	r3, [fp, #-48]
	beq	.L3168
	cmp	r7, #1
	beq	.L3169
	mov	r2, r7
	ldr	r1, .L3282
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
.L3253:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3169:
	cmp	r9, #0
	mov	r1, #16
	mov	r0, r4
	bne	.L3182
	bl	BsGet
	mov	r1, #8
	mov	r6, r0
	mov	r0, r4
	bl	BsGet
	movw	r2, #31745
	cmp	r6, r2
	beq	.L3183
	mov	r1, #32
	mov	r0, r4
	bl	BsBack
	ldr	r3, [r5, #368]
	movw	r2, #32257
	cmp	r6, r2
	mov	r2, #16
	str	r2, [r3, #64]
	beq	.L3272
	mov	r1, #8
	mov	r0, r4
	bl	BsSkip
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	and	r0, r0, #31
	cmp	r0, #11
	beq	.L3273
.L3189:
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L3259
	add	r3, r5, #61440
	ldr	r0, [r3, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r5, #368]
	b	.L3253
.L3168:
	cmp	r9, #0
	bne	.L3170
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	movw	r7, #31745
	mov	r6, r0
	mov	r0, r4
	bl	BsGet
	cmp	r6, r7
	beq	.L3171
	mov	r1, #24
	mov	r0, r4
	bl	BsBack
	bic	r6, r6, #512
	mov	r0, r4
	mov	r1, #24
	bl	BsBack
	cmp	r6, r7
	beq	.L3189
	b	.L3188
.L3182:
	bl	BsGet
	mov	r1, #8
	mov	r7, r0
	mov	r0, r4
	bl	BsGet
	movw	r3, #31745
	cmp	r7, r3
	beq	.L3190
	mov	r1, #24
	mov	r0, r4
	bl	BsBack
	mov	r0, r4
	mov	r1, #24
	bl	BsBack
	movw	r3, #32257
	cmp	r7, r3
	beq	.L3274
.L3188:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3171:
	and	r0, r0, #31
	cmp	r0, #25
	bne	.L3189
	ldr	r4, .L3282+4
	ldr	ip, [r4]
	cmp	ip, #0
	beq	.L3174
	add	r0, r5, #61440
	mov	r3, r9
	mov	r2, r9
	mov	r1, #112
	ldr	r0, [r0, #2344]
	blx	ip
.L3174:
	mov	r0, r5
	bl	DecVDM
	subs	r7, r0, #0
	beq	.L3275
.L3265:
	ldr	ip, [r4]
	cmp	ip, #0
	beq	.L3259
	add	r5, r5, #61440
	mov	r3, #0
	mov	r2, r3
	mov	r1, #113
	ldr	r0, [r5, #2344]
	blx	ip
	mvn	r0, #0
	b	.L3253
.L3170:
	mov	r0, r4
	mov	r1, #24
	bl	BsBack
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3275:
	ldr	ip, [r5, #368]
	add	r6, r5, #61440
	sub	r2, fp, #48
	ldr	r1, [r8, #3448]
	ldr	r0, [r6, #2344]
	ldr	r3, [ip, #12]
	ldr	ip, [ip, #40]
	add	r3, r3, ip
	sub	r3, r3, #1
	bl	MetadataMapToSec
	cmp	r0, #0
	bne	.L3276
	ldr	r4, .L3282+8
	mov	r2, #5
	ldr	r1, .L3282+12
	ldr	r0, [fp, #-48]
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r5, #368]
	ldr	r0, [fp, #-48]
	ldr	ip, [r4, #52]
	ldr	r2, [r3, #12]
	add	r0, r0, #5
	sub	r2, r2, #6
	str	r2, [r8, #3444]
	ldr	r1, [r3, #8]
	add	r1, r1, #6
	blx	ip
	ldr	r3, [r8, #3444]
	add	r3, r3, #5
	str	r3, [r8, #3444]
	ldr	r1, [r5, #368]
	ldr	r2, [r1, #40]
	cmp	r2, #0
	bne	.L3277
.L3178:
	ldr	r0, [r6, #2344]
	ldr	r7, .L3282+16
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L3179
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r6, #2344]
	ldr	r1, [r8, #3444]
	ldr	r3, [r4, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r6, #2344]
.L3179:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r4, r0, #0
	movwne	r3, #12803
	beq	.L3197
.L3258:
	ldr	r2, .L3282+20
	mov	r0, #0
	ldr	r1, .L3282+24
	bl	dprint_vfmw
.L3259:
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3190:
	and	r0, r0, #31
	cmp	r0, #25
	bne	.L3188
	ldr	r4, .L3282+4
	ldr	ip, [r4]
	cmp	ip, #0
	beq	.L3192
	add	r0, r5, #61440
	mov	r3, r6
	mov	r2, r6
	mov	r1, #112
	ldr	r0, [r0, #2344]
	blx	ip
.L3192:
	mov	r0, r5
	bl	DecVDM
	subs	r7, r0, #0
	bne	.L3265
	ldr	ip, [r5, #368]
	add	r6, r5, #61440
	sub	r2, fp, #48
	ldr	r1, [r8, #3448]
	ldr	r0, [r6, #2344]
	ldr	r3, [ip, #12]
	ldr	ip, [ip, #40]
	add	r3, r3, ip
	sub	r3, r3, #1
	bl	MetadataMapToSec
	cmp	r0, #0
	bne	.L3278
	ldr	r4, .L3282+8
	mov	r2, #5
	ldr	r1, .L3282+12
	ldr	r0, [fp, #-48]
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r5, #368]
	ldr	r0, [fp, #-48]
	ldr	ip, [r4, #52]
	ldr	r2, [r3, #12]
	add	r0, r0, #5
	sub	r2, r2, #6
	str	r2, [r8, #3444]
	ldr	r1, [r3, #8]
	add	r1, r1, #6
	blx	ip
	ldr	r3, [r8, #3444]
	add	r3, r3, #5
	str	r3, [r8, #3444]
	ldr	r1, [r5, #368]
	ldr	r2, [r1, #40]
	cmp	r2, #0
	bne	.L3279
.L3195:
	ldr	r0, [r6, #2344]
	ldr	r7, .L3282+16
	ldr	r3, [r7, r0, asl #2]
	cmp	r3, #0
	beq	.L3196
	ldr	r3, [r4, #16]
	mov	r0, #0
	blx	r3
	ldr	r2, [r6, #2344]
	ldr	r1, [r8, #3444]
	ldr	r3, [r4, #44]
	ldr	r2, [r7, r2, asl #2]
	ldr	r0, [fp, #-48]
	blx	r3
	ldr	r3, [r4, #12]
	mov	r0, #0
	blx	r3
	ldr	r0, [r6, #2344]
.L3196:
	ldr	r1, [fp, #-48]
	bl	MetadataUnMapToSec
	subs	r4, r0, #0
	bne	.L3280
.L3197:
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L3259
	ldr	r0, [r6, #2344]
	bl	ReleaseNAL
	str	r4, [r5, #368]
	mvn	r0, #0
	b	.L3253
.L3183:
	and	r3, r0, #31
	cmp	r3, #25
	cmpeq	r10, #1
	moveq	r10, #1
	movne	r10, #0
	bne	.L3281
	ldr	r4, .L3282+4
	ldr	ip, [r4]
	cmp	ip, #0
	beq	.L3186
	add	r0, r5, #61440
	mov	r3, r9
	mov	r2, r9
	mov	r1, #112
	ldr	r0, [r0, #2344]
	blx	ip
.L3186:
	mov	r0, r5
	bl	DecVDM
	subs	r6, r0, #0
	bne	.L3265
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L3259
	add	r3, r5, #61440
	ldr	r0, [r3, #2344]
	bl	ReleaseNAL
	str	r6, [r5, #368]
	mvn	r0, #0
	b	.L3253
.L3281:
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L3259
	add	r3, r5, #61440
	ldr	r0, [r3, #2344]
	bl	ReleaseNAL
	str	r10, [r5, #368]
	mvn	r0, #0
	b	.L3253
.L3272:
	add	r7, r5, #61440
	ldr	r6, .L3282+28
	ldr	r3, [r7, #2344]
	ldr	r3, [r6, r3, asl #2]
	cmp	r3, #0
	beq	.L3188
	ldr	r4, .L3282+8
	mov	r0, r9
	ldr	r3, [r4, #16]
	blx	r3
	ldr	r3, [r5, #368]
	ldr	r2, [r7, #2344]
	ldr	ip, [r4, #44]
	ldr	r1, [r3, #12]
	ldr	r2, [r6, r2, asl #2]
	ldr	r0, [r3, #8]
	blx	ip
	ldr	r3, [r4, #12]
	mov	r0, r9
	blx	r3
	mov	r0, r9
	b	.L3253
.L3274:
	ldr	r1, .L3282+32
	movw	r3, #12974
	ldr	r2, .L3282+20
	mov	r0, r6
	bl	dprint_vfmw
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L3259
	add	r3, r5, #61440
	ldr	r0, [r3, #2344]
	bl	ReleaseNAL
	str	r6, [r5, #368]
	b	.L3259
.L3277:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #36]
	add	r0, r0, r3
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r5, #368]
	ldr	r2, [r8, #3444]
	ldr	r3, [r3, #40]
	add	r3, r3, r2
	str	r3, [r8, #3444]
	b	.L3178
.L3279:
	ldr	r0, [fp, #-48]
	ldr	r1, [r1, #36]
	add	r0, r0, r3
	ldr	r3, [r4, #52]
	blx	r3
	ldr	r3, [r5, #368]
	ldr	r2, [r8, #3444]
	ldr	r3, [r3, #40]
	add	r3, r3, r2
	str	r3, [r8, #3444]
	b	.L3195
.L3273:
	mov	r0, r5
	bl	H264_IsEosNal
	cmp	r0, #1
	bne	.L3189
	mov	r1, #32
	mov	r0, r4
	bl	BsBack
	mov	r1, #32
	mov	r0, r4
	bl	BsBack
	mov	r0, r4
	mov	r1, #32
	bl	BsBack
	mov	r0, #3
	b	.L3253
.L3276:
	mov	r0, r7
	movw	r3, #12769
	ldr	r2, .L3282+20
	ldr	r1, .L3282+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3253
.L3278:
	mov	r0, r7
	movw	r3, #12932
	ldr	r2, .L3282+20
	ldr	r1, .L3282+36
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3253
.L3280:
	movw	r3, #12962
	b	.L3258
.L3283:
	.align	2
.L3282:
	.word	.LC367
	.word	g_event_report
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_RpuStartCode
	.word	vfmw_save_metadata_file
	.word	.LANCHOR0+288
	.word	.LC365
	.word	vfmw_save_el_file
	.word	.LC366
	.word	.LC364
	UNWIND(.fnend)
	.size	H264_VES_Splitter, .-H264_VES_Splitter
	.align	2
	.global	ReceivePacket
	.type	ReceivePacket, %function
ReceivePacket:
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
	ldr	ip, [r1, #12]
	add	r6, r0, #61440
	ldr	r3, [r1, #8]
	ldr	r2, [r1, #4]
	mov	r4, r0
	mov	r5, r1
	mov	r0, #7
	ldr	r1, .L3352
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [r6, #2376]
	ldr	r3, [r4]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L3347
.L3285:
	ldr	r3, [r4, #368]
	cmp	r3, #0
	beq	.L3307
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, #1
	beq	.L3348
.L3288:
	ldr	r1, .L3352+4
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r4, #368]
	cmp	r1, #0
	beq	.L3307
	ldr	r0, [r6, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r4, #368]
.L3307:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3292
	ldr	r3, [r5, #4]
	cmp	r3, #0
	beq	.L3292
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3292
	ldrb	r3, [r4, #377]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3310
	mov	r2, r4
	mov	r3, #1
	b	.L3295
.L3294:
	add	r3, r3, #1
	cmp	r3, #137
	beq	.L3308
.L3295:
	ldrb	r1, [r2, #473]	@ zero_extendqisi2
	add	r2, r2, #96
	cmp	r1, #0
	bne	.L3294
	mov	r2, r3
.L3293:
	mov	r1, r3, asl #7
	cmn	r2, #1
	sub	r3, r1, r3, asl #5
	mov	r1, #1
	add	r3, r4, r3
	strb	r1, [r3, #377]
	beq	.L3308
	mov	r3, r2, asl #7
	mov	r0, #0
	sub	r3, r3, r2, asl #5
	add	r2, r3, #376
	add	r3, r4, r3
	add	r2, r4, r2
	str	r2, [r4, #368]
	ldr	r2, [r5, #4]
	str	r2, [r3, #384]
	ldr	r2, [r5, #12]
	str	r2, [r3, #388]
	ldr	r2, [r5, #8]
	str	r2, [r3, #392]
	ldr	r3, [r4, #368]
	str	r0, [r3, #24]
	ldr	r3, [r4, #368]
	ldr	r2, [r5, #16]
	str	r2, [r3, #32]
	ldrd	r2, [r5, #24]
	ldr	ip, [r4, #368]
	strd	r2, [ip, #88]
	ldr	r3, [r4, #368]
	str	r1, [r3, #68]
	ldr	r3, [r4, #368]
	strb	r0, [r3]
	ldr	r3, [r4, #368]
	ldrb	r2, [r5]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r3, [r4]
	ldrb	r3, [r3, #912]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3344
	add	r3, r4, #57344
	ldr	r1, [r5, #12]
	ldr	r2, [r3, #3728]
	ldr	r0, [r3, #3732]
	add	r1, r1, r2
	str	r1, [r3, #3728]
	ldr	r2, [r5, #12]
	add	r2, r2, r0
	str	r2, [r3, #3732]
	ldr	r3, [r4, #368]
	b	.L3299
.L3348:
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bhi	.L3288
	ldrb	r1, [r3, #4]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L3289
	b	.L3288
.L3347:
	ldr	r3, [r3, #888]
	cmp	r3, #0
	beq	.L3285
	ldr	r3, [r4, #368]
	cmp	r3, #0
	ldrneb	r2, [r5]	@ zero_extendqisi2
	beq	.L3307
.L3289:
	strb	r2, [r3, #4]
	ldr	r3, [r4]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L3349
.L3301:
	ldr	r3, [r5, #12]
	cmp	r3, #0
	ble	.L3302
	ldr	r2, [r5, #4]
	cmp	r2, #0
	beq	.L3302
	ldr	r3, [r5, #8]
	cmp	r3, #0
	beq	.L3302
	ldr	r3, [r4, #368]
	ldr	r1, [r3, #68]
	cmp	r1, #1
	bls	.L3350
.L3303:
	mov	r2, #1
	strb	r2, [r3, #4]
	ldr	r1, [r5, #16]
	ldr	r0, [r6, #2344]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3352+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3344
	mov	r3, #0
	ldr	r0, [r6, #2344]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L3344:
	ldr	r3, [r4, #368]
.L3299:
	ldrb	r0, [r3, #4]	@ zero_extendqisi2
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3292:
	ldr	r1, .L3352+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r5, #16]
	ldr	r0, [r6, #2344]
	bl	SM_ReleaseStreamSeg
	ldr	r3, .L3352+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3346
.L3345:
	mov	r3, #0
	ldr	r0, [r6, #2344]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L3346:
	mvn	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3302:
	ldr	r3, [r4, #368]
	b	.L3303
.L3349:
	ldr	r3, [r3, #888]
	cmp	r3, #0
	bne	.L3344
	b	.L3301
.L3350:
	mov	ip, r1, asl #5
	mov	r0, #0
	sub	r1, ip, r1, asl #2
	add	r3, r3, r1
	str	r2, [r3, #8]
	ldr	r3, [r4, #368]
	ldr	ip, [r5, #12]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #12]
	ldr	r3, [r4, #368]
	ldr	ip, [r5, #8]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	ip, [r3, #16]
	ldr	r3, [r4, #368]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #24]
	ldr	r3, [r4, #368]
	ldr	r0, [r5, #16]
	ldr	r1, [r3, #68]
	mov	r2, r1, asl #5
	sub	r2, r2, r1, asl #2
	add	r3, r3, r2
	str	r0, [r3, #32]
	ldr	r2, [r4, #368]
	ldr	r3, [r2, #68]
	add	r3, r3, #1
	str	r3, [r2, #68]
	ldr	r3, [r4]
	ldrb	r3, [r3, #912]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3304
	add	r3, r4, #57344
	ldr	r1, [r5, #12]
	ldr	r2, [r3, #3728]
	ldr	r0, [r3, #3732]
	add	r1, r1, r2
	str	r1, [r3, #3728]
	ldr	r2, [r5, #12]
	add	r2, r2, r0
	str	r2, [r3, #3732]
.L3304:
	ldr	r3, [r4, #368]
	ldr	r2, [r3, #12]
	cmp	r2, #4096
	bcc	.L3351
.L3305:
	mov	r2, #1
	str	r2, [r6, #2376]
	b	.L3299
.L3351:
	mov	r0, r4
	bl	CombinePacket.part.13
	ldr	r3, [r4, #368]
	b	.L3305
.L3308:
	ldr	r1, .L3352+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearAllNal
	mov	r0, r4
	bl	H264_ClearCurrPic
	mov	r0, r4
	bl	ClearDPB
	ldr	r3, .L3352+8
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L3345
	b	.L3346
.L3310:
	mov	r2, r3
	b	.L3293
.L3353:
	.align	2
.L3352:
	.word	.LC368
	.word	.LC369
	.word	g_event_report
	.word	.LC371
	.word	.LC370
	UNWIND(.fnend)
	.size	ReceivePacket, .-ReceivePacket
	.align	2
	.global	ClearAll
	.type	ClearAll, %function
ClearAll:
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
	mov	r5, r0
	str	r0, [fp, #-48]
	mov	r4, r1
	mov	r0, #22
	ldr	r1, .L3380
	bl	dprint_vfmw
	mov	r0, r5
	bl	H264_ClearCurrPic
	mov	r0, r5
	bl	ClearAllNal
	mov	r0, r5
	bl	InitDPB
	ldr	r3, [fp, #-48]
	cmp	r4, #0
	add	r9, r3, #61440
	beq	.L3355
	add	r1, r3, #8
	ldr	r0, [r9, #2344]
	bl	FSP_ClearNotInVoQueue
.L3356:
	ldr	r3, [fp, #-48]
	mov	r8, #0
	mov	r6, #0
	mov	r7, #0
	add	r4, r3, #27904
	add	r4, r4, #72
.L3359:
	sub	r5, r4, #32
	mov	r3, #0
	sub	r2, r4, #584
	mov	r1, #1
	mvn	r10, #0
	mov	lr, #17
	mov	ip, #16
	mov	r0, #2
	str	r8, [r4, #-420]
	strb	r3, [r4, #-584]
	strb	r3, [r4, #-583]
	strb	r3, [r4, #-582]
	str	r3, [r4, #76]
	str	r3, [r4, #68]
	str	r3, [r4, #80]
	strb	r3, [r4, #-580]
	strb	r3, [r4, #112]
	str	r10, [r4, #72]
	str	r1, [r4, #84]
	strb	r1, [r4, #152]
	str	lr, [r4, #100]
	str	ip, [r4, #104]
	str	r2, [r4, #228]
	str	r2, [r4, #188]
	str	r2, [r4, #148]
	strb	r0, [r4, #192]
.L3358:
	ldr	r1, [r5, #8]!
	cmp	r1, #0
	beq	.L3357
	ldr	r0, [r9, #2344]
	bl	FreeUsdByDec
	strd	r6, [r5]
.L3357:
	cmp	r5, r4
	bne	.L3358
	add	r8, r8, #1
	add	r4, r5, #824
	cmp	r8, #40
	bne	.L3359
	ldr	r3, [fp, #-48]
	mov	r6, #0
	mov	r7, #0
	add	r4, r3, #60672
	add	r5, r3, #60928
	add	r4, r4, #232
	add	r5, r5, #8
.L3361:
	ldr	r1, [r4, #8]!
	cmp	r1, #0
	beq	.L3360
	ldr	r0, [r9, #2344]
	bl	FreeUsdByDec
	strd	r6, [r4]
.L3360:
	cmp	r4, r5
	bne	.L3361
	ldr	r3, [r9, #1056]
	cmp	r3, #0
	beq	.L3365
	ldr	r3, [fp, #-48]
	mov	r4, #0
	mov	r6, r4
	add	r5, r3, #62464
	add	r5, r5, #32
.L3364:
	ldr	r1, [r5, #4]!
	add	r4, r4, #1
	cmp	r1, #0
	beq	.L3363
	ldr	r0, [r9, #2344]
	bl	FreeUsdByDec
	str	r6, [r5]
.L3363:
	ldr	r3, [r9, #1056]
	cmp	r3, r4
	bhi	.L3364
.L3365:
	ldr	r6, [fp, #-48]
	mov	r4, #0
	ldr	r3, .L3380+4
	mov	r1, r4
	add	r5, r6, #20480
	add	ip, r6, #24576
	str	r4, [r9, #1056]
	add	r0, r5, #208
	str	r4, [r9, #2320]
	movw	r2, #1640
	str	r4, [r9, #1036]
	str	r4, [r9, #2268]
	str	r4, [r9, #2328]
	str	r4, [r9, #2276]
	str	r4, [r9, #1044]
	str	r4, [r9, #2348]
	str	r4, [r9, #1048]
	ldr	r3, [r3, #48]
	str	r4, [r6, #368]
	str	r4, [ip, #1804]
	strb	r4, [r5, #3896]
	strb	r4, [r5, #1892]
	strb	r4, [r5, #3897]
	strb	r4, [r5, #1893]
	blx	r3
	add	r2, r6, #57344
	mov	r3, #2
	mov	r1, #1
	strb	r3, [r5, #208]
	mov	r0, r4
	strb	r1, [r5, #213]
	mov	r3, #256
	strb	r4, [r2, #3008]
	strb	r4, [r9, #368]
	str	r4, [r9, #372]
	str	r3, [r9, #376]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3355:
	add	r0, r3, #8
	bl	ResetVoQueue
	ldr	r0, [r9, #2344]
	bl	FSP_EmptyInstance
	b	.L3356
.L3381:
	.align	2
.L3380:
	.word	.LC372
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	ClearAll, .-ClearAll
	.align	2
	.global	InsertFrmInDPB
	.type	InsertFrmInDPB, %function
InsertFrmInDPB:
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
	cmp	r1, #15
	mov	r9, r1
	mov	r5, r0
	mov	r4, r2
	bhi	.L3481
	ldrb	r7, [r2, #3]	@ zero_extendqisi2
	cmp	r7, #1
	beq	.L3386
	bcc	.L3387
	cmp	r7, #2
	bne	.L3482
	ldr	r3, [r2, #648]
	mov	r2, #3
	strb	r2, [r3, #696]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3407
	add	r6, r0, r3
	add	r2, r6, #24576
	str	r2, [fp, #-48]
	ldr	r2, [r2, #1944]
	cmp	r2, #0
	beq	.L3407
	ldr	r0, [fp, #-48]
	strb	r7, [r2, #776]
	ldr	r2, [r4, #648]
	ldr	r3, [r0, #1944]
	str	r2, [r3, #812]
	ldr	r3, [r0, #1944]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #777]
	ldr	r3, [r0, #1944]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #778]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #680]
	str	r2, [r3, #788]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #684]
	str	r2, [r3, #796]
	ldr	r2, [r4, #648]
	ldr	r3, [r0, #1944]
	ldr	r2, [r2, #808]
	str	r2, [r3, #808]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #692]
	str	r2, [r3, #792]
	ldr	r3, [r0, #1944]
	ldr	r1, [r3, #752]
	ldr	r2, [r3, #792]
	add	r2, r2, r1
	str	r2, [r3, #712]
	str	r2, [r3, #680]
	ldr	r2, [r0, #1944]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r3, [fp, #-48]
	ldr	r1, [fp, #-48]
	ldr	r2, [r3, #1944]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #1]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #1944]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	orreq	r2, r2, #2
	strb	r2, [r3, #3]
	mov	r2, #632
	ldr	lr, [r1, #1944]
	add	r1, r4, #16
	add	r8, lr, #608
	add	ip, lr, #624
	ldr	r3, [lr, #600]
	add	r0, lr, #16
	ldrd	r6, [r8]
	ldr	r10, [lr, #16]
	str	r3, [fp, #-76]
	strd	r6, [fp, #-60]
	ldr	r3, [lr, #604]
	ldrd	r6, [ip, #-8]
	ldr	ip, [lr, #20]
	str	r3, [fp, #-52]
	strd	r6, [fp, #-68]
	str	ip, [fp, #-72]
	ldr	r8, [lr, #24]
	ldr	r7, [lr, #28]
	bl	memcpy
	ldr	r3, [fp, #-76]
	add	r2, r4, #608
	ldr	r6, [fp, #-52]
	ldmdb	r2, {r0, lr}
	and	ip, r3, r6
	adds	r1, ip, #1
	and	r0, r0, lr
	ldr	ip, [fp, #-72]
	movne	r1, #1
	cmn	r0, #1
	movne	r1, #0
	cmp	r1, #0
	ldrne	r1, [fp, #-48]
	ldrne	r1, [r1, #1944]
	strne	r3, [r1, #600]
	movne	r3, r6
	strne	r3, [r1, #604]
	ldr	r1, [fp, #-48]
	ldrd	r2, [r2]
	ldr	lr, [r1, #1944]
	ldrd	r0, [fp, #-60]
	cmp	r3, r1
	add	r1, lr, #608
	cmpeq	r2, r0
	ldrhid	r2, [fp, #-60]
.L3417:
	strd	r2, [r1]
	add	r0, r4, #624
	ldr	r3, [fp, #-48]
	ldr	r1, [r3, #1944]
	ldrd	r2, [r0, #-8]
	add	lr, r1, #624
	ldrd	r0, [fp, #-68]
	cmp	r3, r1
	cmpeq	r2, r0
	movhi	r3, r1
	ldr	r1, [fp, #-48]
	movhi	r2, r0
	strd	r2, [lr, #-8]
	ldr	r3, [r4, #16]
	ldr	r2, [r1, #1944]
	cmp	r3, r10
	movcs	r3, r10
	str	r3, [r2, #16]
	ldr	r3, [r4, #20]
	ldr	r2, [r1, #1944]
	cmp	r3, ip
	movcs	r3, ip
	str	r3, [r2, #20]
	ldr	r3, [r4, #24]
	ldr	r2, [r1, #1944]
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r2, #24]
	ldr	r3, [r4, #28]
	ldr	r2, [r1, #1944]
	cmp	r3, r7
	movcs	r3, r7
	str	r3, [r2, #28]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3419
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3419
.L3420:
	ldr	r0, [fp, #-48]
	ldr	r2, [r0, #1944]
	ldr	r3, [r2, #796]
	ldr	r1, [r2, #756]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #676]
	ldr	r2, [r4, #668]
	mov	r4, r0
	ldr	r3, [r0, #1944]
	str	r2, [r3, #664]
	ldr	r0, [r0, #1944]
	bl	CombineFldsToFrm
	ldr	r2, [r4, #1944]
	ldr	r3, [r2, #688]
	ldr	r2, [r2, #788]
	add	r3, r3, #6720
	add	r3, r3, #10
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3406
.L3387:
	ldr	r2, [r2, #648]
	add	r8, r0, r1, lsl #2
	add	r8, r8, #24576
	mov	r3, #3
	str	r2, [r8, #1944]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r2]
	ldr	r2, [r8, #1944]
	strb	r3, [r2, #1]
	ldr	r1, [r4, #648]
	ldr	r2, [r8, #1944]
	ldrb	r1, [r1, #4]	@ zero_extendqisi2
	strb	r1, [r2, #4]
	ldr	r1, [r4, #648]
	ldr	r2, [r8, #1944]
	ldr	r1, [r1, #668]
	str	r1, [r2, #668]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	ldr	r2, [r8, #1944]
	cmp	r1, #0
	beq	.L3483
.L3389:
	strb	r3, [r2, #2]
	add	r1, r4, #16
	ldr	r3, [r8, #1944]
	mov	r2, #632
	ldr	r0, [r4, #716]
	mov	r6, #0
	mov	r10, #1
	str	r0, [r3, #684]
	ldr	r0, [r8, #1944]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #692]
	mov	ip, #2
	mov	r2, r6
	mov	r0, r5
	str	r1, [r3, #712]
	str	r1, [r3, #680]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #648]
	str	r1, [r3, #812]
	str	r1, [r3, #772]
	str	r1, [r3, #732]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #660]
	str	r1, [r3, #660]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #656]
	str	r1, [r3, #652]
	ldr	r3, [r8, #1944]
	strb	r6, [r3, #696]
	ldr	r3, [r8, #1944]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	strb	r1, [r3, #697]
	ldr	r3, [r8, #1944]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #698]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #684]
	str	r1, [r3, #716]
	str	r1, [r3, #676]
	ldr	r3, [r8, #1944]
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	str	r1, [r3, #672]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #668]
	str	r1, [r3, #664]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #672]
	str	r1, [r3, #708]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #676]
	str	r1, [r3, #748]
	ldr	r3, [r8, #1944]
	ldr	r1, [r4, #680]
	str	r1, [r3, #788]
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldr	r3, [r8, #1944]
	cmp	r1, r10
	moveq	r7, #3
	strb	r7, [r3, #3]
	ldr	r1, [r4, #648]
	ldr	r3, [r8, #1944]
	ldr	r1, [r1, #728]
	str	r1, [r3, #728]
	ldr	r3, [r8, #1944]
	ldrb	r8, [r3, #697]	@ zero_extendqisi2
	ldrb	r7, [r3, #698]	@ zero_extendqisi2
	ldr	lr, [r3, #712]
	ldr	r1, [r3, #732]
	strb	ip, [r3, #776]
	ldr	ip, [r3, #716]
	str	r1, [r3, #772]
	strb	r10, [r3, #736]
	strb	r8, [r3, #737]
	strb	r8, [r3, #777]
	strb	r7, [r3, #738]
	strb	r7, [r3, #778]
	str	lr, [r3, #752]
	str	lr, [r3, #792]
	str	ip, [r3, #756]
	str	ip, [r3, #796]
	str	r1, [r3, #812]
	ldr	r1, [r4, #648]
	bl	GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2319
	movne	r0, r6
	bne	.L3479
.L3406:
	add	r3, r9, #6592
	add	r1, r5, #61440
	add	r3, r3, #38
	mov	r2, #1
	ldr	r0, [r1, #2344]
	ldr	r3, [r5, r3, asl #2]
	ldr	r1, [r3, #648]
	bl	FSP_SetRef
	mov	r0, #0
.L3384:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3482:
	mov	r2, r7
	ldr	r1, .L3484
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	mov	r1, #1
	bl	ClearAll
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3386:
	ldr	r3, [r2, #648]
	mov	r2, #3
	strb	r2, [r3, #696]
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #0
	mov	r3, r1, asl #2
	beq	.L3392
	add	r6, r0, r3
	add	r2, r6, #24576
	str	r2, [fp, #-48]
	ldr	r2, [r2, #1944]
	cmp	r2, #0
	beq	.L3392
	ldr	r0, [fp, #-48]
	strb	r7, [r2, #736]
	ldr	r2, [r4, #684]
	ldr	r3, [r0, #1944]
	str	r2, [r3, #756]
	ldr	r3, [r0, #1944]
	ldrb	r2, [r4, #4]	@ zero_extendqisi2
	strb	r2, [r3, #737]
	ldr	r3, [r0, #1944]
	ldrb	r2, [r4, #5]	@ zero_extendqisi2
	strb	r2, [r3, #738]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #676]
	str	r2, [r3, #748]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #684]
	str	r2, [r3, #756]
	ldr	r2, [r4, #648]
	ldr	r3, [r0, #1944]
	ldr	r2, [r2, #768]
	str	r2, [r3, #768]
	ldr	r3, [r0, #1944]
	ldr	r2, [r4, #692]
	str	r2, [r3, #752]
	ldr	r3, [r0, #1944]
	ldr	r1, [r3, #752]
	ldr	r2, [r3, #792]
	add	r2, r2, r1
	str	r2, [r3, #712]
	str	r2, [r3, #680]
	ldr	r2, [r0, #1944]
	ldrb	r3, [r2]	@ zero_extendqisi2
	cmp	r3, #0
	ldrneb	r3, [r4, #2]	@ zero_extendqisi2
	strb	r3, [r2]
	ldr	r3, [fp, #-48]
	ldr	r1, [fp, #-48]
	ldr	r2, [r3, #1944]
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #1]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [fp, #-48]
	ldr	r3, [r3, #1944]
	ldrb	r2, [r3, #3]	@ zero_extendqisi2
	orreq	r2, r2, #1
	strb	r2, [r3, #3]
	mov	r2, #632
	ldr	lr, [r1, #1944]
	add	r1, r4, #16
	add	r8, lr, #608
	add	ip, lr, #624
	ldr	r3, [lr, #600]
	add	r0, lr, #16
	ldrd	r6, [r8]
	ldr	r10, [lr, #16]
	str	r3, [fp, #-76]
	strd	r6, [fp, #-60]
	ldr	r3, [lr, #604]
	ldrd	r6, [ip, #-8]
	ldr	ip, [lr, #20]
	str	r3, [fp, #-52]
	strd	r6, [fp, #-68]
	str	ip, [fp, #-72]
	ldr	r8, [lr, #24]
	ldr	r7, [lr, #28]
	bl	memcpy
	ldr	r3, [fp, #-76]
	add	r2, r4, #608
	ldr	r6, [fp, #-52]
	ldmdb	r2, {r0, lr}
	and	ip, r3, r6
	adds	r1, ip, #1
	and	r0, r0, lr
	ldr	ip, [fp, #-72]
	movne	r1, #1
	cmn	r0, #1
	movne	r1, #0
	cmp	r1, #0
	ldrne	r1, [fp, #-48]
	ldrne	r1, [r1, #1944]
	strne	r3, [r1, #600]
	movne	r3, r6
	strne	r3, [r1, #604]
	ldr	r1, [fp, #-48]
	ldrd	r2, [r2]
	ldr	lr, [r1, #1944]
	ldrd	r0, [fp, #-60]
	cmp	r3, r1
	add	r1, lr, #608
	cmpeq	r2, r0
	ldrhid	r2, [fp, #-60]
.L3401:
	strd	r2, [r1]
	add	r0, r4, #624
	ldr	r3, [fp, #-48]
	ldr	r1, [r3, #1944]
	ldrd	r2, [r0, #-8]
	add	lr, r1, #624
	ldrd	r0, [fp, #-68]
	cmp	r3, r1
	cmpeq	r2, r0
	movhi	r3, r1
	ldr	r1, [fp, #-48]
	movhi	r2, r0
	strd	r2, [lr, #-8]
	ldr	r3, [r4, #16]
	ldr	r2, [r1, #1944]
	cmp	r3, r10
	movcs	r3, r10
	str	r3, [r2, #16]
	ldr	r3, [r4, #20]
	ldr	r2, [r1, #1944]
	cmp	r3, ip
	movcs	r3, ip
	str	r3, [r2, #20]
	ldr	r3, [r4, #24]
	ldr	r2, [r1, #1944]
	cmp	r3, r8
	movcs	r3, r8
	str	r3, [r2, #24]
	ldr	r3, [r4, #28]
	ldr	r2, [r1, #1944]
	cmp	r3, r7
	movcs	r3, r7
	str	r3, [r2, #28]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3403
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3403
.L3404:
	ldr	r0, [fp, #-48]
	ldr	r2, [r0, #1944]
	ldr	r3, [r2, #796]
	ldr	r1, [r2, #756]
	cmp	r3, r1
	movcc	r3, r1
	str	r3, [r2, #676]
	ldr	r2, [r4, #668]
	mov	r4, r0
	ldr	r3, [r0, #1944]
	str	r2, [r3, #664]
	ldr	r0, [r0, #1944]
	bl	CombineFldsToFrm
	ldr	r2, [r4, #1944]
	ldr	r3, [r2, #688]
	ldr	r2, [r2, #748]
	add	r3, r3, #6656
	add	r3, r3, #58
	add	r3, r5, r3, lsl #2
	str	r2, [r3, #4]
	b	.L3406
.L3392:
	add	r6, r5, r3
	ldr	r3, [r4, #648]
	add	r6, r6, #24576
	mov	r2, #1
	str	r3, [r6, #1944]
	strb	r2, [r3, #736]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #648]
	str	r1, [r3, #772]
	ldr	r3, [r6, #1944]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	strb	r1, [r3, #737]
	ldr	r3, [r6, #1944]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #738]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #676]
	str	r1, [r3, #748]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #684]
	str	r1, [r3, #756]
	ldr	r1, [r4, #648]
	ldr	r3, [r6, #1944]
	ldr	r1, [r1, #768]
	str	r1, [r3, #768]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #692]
	str	r1, [r3, #752]
	ldr	r3, [r6, #1944]
	ldr	r1, [r3, #752]
	str	r1, [r3, #712]
	str	r1, [r3, #680]
	ldr	r3, [r6, #1944]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r6, #1944]
	strb	r2, [r3, #1]
	ldr	r2, [r4, #648]
	ldr	r3, [r6, #1944]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r2, [r4, #648]
	ldr	r3, [r6, #1944]
	ldr	r2, [r2, #668]
	str	r2, [r3, #668]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3394
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3394
.L3395:
	ldr	r3, [r6, #1944]
	mov	r7, #0
	mov	r2, #632
	add	r1, r4, #16
	str	r7, [r3, #672]
	ldr	r0, [r6, #1944]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #716]
	mov	r2, #1
	mov	r0, r5
	str	r1, [r3, #684]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #656]
	str	r1, [r3, #652]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #668]
	str	r1, [r3, #664]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #684]
	str	r1, [r3, #676]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	ldr	r1, [r6, #1944]
	rsb	r3, r2, r3
	clz	r3, r3
	mov	r3, r3, lsr #5
	strb	r3, [r1, #3]
	ldr	r1, [r4, #648]
	bl	GetAPC
	cmp	r0, #0
	beq	.L3406
	mov	r3, r0
	movw	r2, #2374
	mov	r0, r7
.L3479:
	ldr	r1, .L3484+4
	bl	dprint_vfmw
	mov	r0, r5
	bl	ClearDPB
	mvn	r0, #0
	b	.L3384
.L3407:
	add	r6, r5, r3
	ldr	r3, [r4, #648]
	add	r6, r6, #24576
	mov	r2, #2
	str	r3, [r6, #1944]
	strb	r2, [r3, #776]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #648]
	str	r1, [r3, #812]
	ldr	r3, [r6, #1944]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	strb	r1, [r3, #777]
	ldr	r3, [r6, #1944]
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	strb	r1, [r3, #778]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #680]
	str	r1, [r3, #788]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #684]
	str	r1, [r3, #796]
	ldr	r1, [r4, #648]
	ldr	r3, [r6, #1944]
	ldr	r1, [r1, #808]
	str	r1, [r3, #808]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #692]
	str	r1, [r3, #792]
	ldr	r3, [r6, #1944]
	ldr	r1, [r3, #752]
	str	r1, [r3, #712]
	str	r1, [r3, #680]
	ldr	r3, [r6, #1944]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	strb	r1, [r3]
	ldr	r3, [r6, #1944]
	strb	r2, [r3, #1]
	ldr	r2, [r4, #648]
	ldr	r3, [r6, #1944]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r2, [r4, #648]
	ldr	r3, [r6, #1944]
	ldr	r2, [r2, #668]
	str	r2, [r3, #668]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3409
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3409
.L3410:
	ldr	r3, [r6, #1944]
	mov	r8, #0
	mov	r2, #632
	add	r1, r4, #16
	str	r8, [r3, #672]
	ldr	r0, [r6, #1944]
	add	r0, r0, #16
	bl	memcpy
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #716]
	mov	r2, #2
	mov	r0, r5
	str	r1, [r3, #684]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #656]
	str	r1, [r3, #652]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #668]
	str	r1, [r3, #664]
	ldr	r3, [r6, #1944]
	ldr	r1, [r4, #684]
	str	r1, [r3, #796]
	str	r1, [r3, #676]
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldr	r3, [r6, #1944]
	cmp	r1, #1
	moveq	r7, r2
	movne	r7, r8
	strb	r7, [r3, #3]
	ldr	r1, [r4, #648]
	bl	GetAPC
	cmp	r0, #0
	movne	r3, r0
	movwne	r2, #2497
	movne	r0, r8
	beq	.L3406
	b	.L3479
.L3483:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #3
	b	.L3389
.L3394:
	ldr	r3, [r6, #1944]
	mov	r2, #1
	strb	r2, [r3, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, r2
	ldreq	r3, [r6, #1944]
	ldreq	r2, [r4, #660]
	streq	r2, [r3, #660]
	b	.L3395
.L3409:
	ldr	r3, [r6, #1944]
	mov	r2, #2
	strb	r2, [r3, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	ldreq	r3, [r6, #1944]
	ldreq	r2, [r4, #660]
	streq	r2, [r3, #660]
	b	.L3410
.L3419:
	ldr	r1, [fp, #-48]
	ldr	r2, [r1, #1944]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r3, r1
	ldreq	r2, [r4, #660]
	ldreq	r3, [r3, #1944]
	streq	r2, [r3, #660]
	b	.L3420
.L3403:
	ldr	r1, [fp, #-48]
	ldr	r2, [r1, #1944]
	ldrb	r3, [r2, #2]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r2, #2]
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r3, r1
	ldreq	r2, [r4, #660]
	ldreq	r3, [r3, #1944]
	streq	r2, [r3, #660]
	b	.L3404
.L3481:
	mov	r3, r1
	movw	r2, #2280
	ldr	r1, .L3484+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3384
.L3485:
	.align	2
.L3484:
	.word	.LC375
	.word	.LC374
	.word	.LC373
	UNWIND(.fnend)
	.size	InsertFrmInDPB, .-InsertFrmInDPB
	.align	2
	.global	StorePicInDPB
	.type	StorePicInDPB, %function
StorePicInDPB:
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
	add	r2, r0, #16384
	add	r5, r0, #57344
	mov	r3, #0
	str	r3, [r2, #3444]
	mov	r4, r0
	ldrb	r3, [r5, #3011]	@ zero_extendqisi2
	sub	r3, r3, #2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r2, #3448]
	ldrb	r3, [r5, #3008]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3660
	add	r6, r0, #61440
	ldr	r3, .L3684
	ldr	r1, [r6, #2344]
	ldr	r2, [r6, #2356]
	ldr	r3, [r3, r1, asl #2]
	str	r2, [r6, #2352]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L3661
.L3489:
	ldr	r0, [r6, #2272]
	cmp	r0, #2
	beq	.L3662
	ldr	r7, [r4]
	ldr	r3, [r7, #24]
	cmp	r3, #0
	bne	.L3494
	ldr	r2, [r6, #2348]
	cmp	r2, #2
	beq	.L3496
	ldrb	r2, [r5, #3010]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3496
.L3574:
	ldrb	r1, [r5, #3011]	@ zero_extendqisi2
	ldr	r9, [r5, #3656]
	sub	r2, r1, #1
	cmp	r2, #1
	movhi	r2, #0
	movls	r2, #1
	cmp	r1, #0
	beq	.L3498
	ldrb	r0, [r9, #1]	@ zero_extendqisi2
	cmp	r0, #0
	moveq	ip, r2
	orrne	ip, r2, #1
	cmp	ip, #0
	beq	.L3497
	cmp	r2, #0
	beq	.L3663
.L3577:
	ldr	r2, [r6, #2348]
	cmp	r2, #0
	bne	.L3501
	add	r0, r5, #3728
	mov	r3, #1
	add	r0, r0, #8
	str	r3, [r6, #2348]
	mov	r2, #728
	add	r1, r5, #3008
	bl	memcpy
	ldr	r3, [r7, #24]
.L3497:
	cmp	r3, #2
	beq	.L3664
.L3496:
	ldr	r3, [r5, #3672]
	cmp	r3, #0
	beq	.L3533
	ldr	r3, [r6, #2336]
	ldr	r2, [r5, #3700]
	cmp	r3, r2
	bcs	.L3534
	ldrb	r1, [r5, #3010]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L3665
.L3534:
	mov	r0, r4
	bl	Marking
	subs	r2, r0, #0
	beq	.L3536
	ldr	r1, .L3684+4
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3759
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3494:
	ldrb	r2, [r5, #3010]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3497
	b	.L3574
.L3498:
	cmp	r2, #0
	bne	.L3577
.L3504:
	add	r7, r4, #60160
	add	r7, r7, #192
.L3507:
	cmp	r1, #0
	beq	.L3508
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3666
.L3508:
	ldr	r3, [r7, #692]
	str	r3, [r9, #680]
.L3509:
	mov	r1, r9
	mov	r0, r4
	bl	GetImagePara
	ldr	r1, [r9, #648]
	ldr	r0, [r6, #2344]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L3667
	ldrb	r3, [r7, #3]	@ zero_extendqisi2
	add	ip, r7, #608
	cmp	r3, #0
	beq	.L3511
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3668
.L3511:
	ldrd	r2, [ip, #-8]
	add	r1, r8, #592
.L3652:
	strd	r2, [r1, #-8]
.L3512:
	ldrd	r2, [ip]
	add	r10, r7, #624
	add	lr, r8, #608
	add	ip, r7, #448
	add	r0, r8, #432
	strd	r2, [r1]
	ldrd	r2, [r10, #-8]
	strd	r2, [lr, #-8]
	ldr	r3, [r7, #16]
	str	r3, [r8]
	ldr	r3, [r7, #20]
	str	r3, [r8, #4]
	ldr	r3, [r7, #24]
	str	r3, [r8, #8]
	ldr	r3, [r7, #28]
	str	r3, [r8, #12]
	ldr	r1, [r9, #680]
	cmp	r1, #0
	str	r1, [r8, #152]
	ldr	r3, [r7, #440]
	str	r3, [r8, #424]
	ldr	r3, [r7, #436]
	str	r3, [r8, #420]
	ldrd	r2, [ip]
	strd	r2, [r0]
	beq	.L3513
	ldrb	r3, [r8, #64]	@ zero_extendqisi2
	ands	r7, r3, #3
	beq	.L3669
.L3514:
	ldr	r3, [r4]
	ldr	r2, [r3, #4]
	cmp	r2, r1
	bcs	.L3513
	ldr	r3, .L3684+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3524
	str	r1, [fp, #-52]
	mov	r3, #8
	str	r2, [fp, #-48]
	mov	r1, #104
	sub	r2, fp, #52
	ldr	r0, [r6, #2344]
	blx	ip
.L3524:
	ldr	r1, [r9, #648]
	mov	r2, #0
	ldr	r0, [r6, #2344]
	bl	FSP_SetDisplay
	movw	r3, #3683
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3660:
	mov	r0, r3
	ldr	r1, .L3684+16
	bl	dprint_vfmw
	movw	r3, #3519
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	add	r6, r4, #61440
	bl	dprint_vfmw
.L3576:
	ldr	r3, [r5, #3656]
	mov	r2, #1
	ldr	r0, [r6, #2344]
	mvn	r7, #0
	ldr	r1, [r3, #648]
	bl	FSP_ClearLogicFs
	mov	r3, r7
	movw	r2, #3937
	ldr	r1, .L3684+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r2, [r5, #3656]
	mov	r3, #0
	strb	r3, [r2, #4]
	ldr	r2, [r5, #3656]
	strb	r3, [r2, #1]
.L3573:
	mov	r0, r7
	mov	r3, #0
	strb	r3, [r5, #3008]
.L3649:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3669:
	movw	r2, #3659
	ldr	r1, .L3684+24
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3684+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3653
	mov	r3, r7
	mov	r2, r7
	mov	r1, #111
	ldr	r0, [r6, #2344]
	blx	ip
.L3653:
	ldr	r1, [r8, #152]
	cmp	r1, #0
	bne	.L3514
.L3513:
	mov	r2, #1
	ldr	r1, [r9, #648]
	ldr	r0, [r6, #2344]
	bl	FSP_SetDisplay
	ldr	r0, [r6, #2344]
	add	r3, r4, #8
	str	r8, [sp]
	mov	r2, r4
	mov	r1, #0
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L3518
	mov	r2, #0
	ldr	r1, [r9, #648]
	ldr	r0, [r6, #2344]
	bl	FSP_SetDisplay
.L3519:
	ldr	r3, [r4]
	ldr	r3, [r3, #612]
	add	r3, r3, #2032
	add	r3, r3, #15
	cmp	r3, #4096
	movcc	r3, #0
	strcc	r3, [r8, #16]
	bcs	.L3670
.L3521:
	ldr	r2, [r6, #2348]
	ldr	r3, [r6, #2364]
	cmp	r2, #2
	add	r3, r3, #2
	str	r3, [r6, #2364]
	movne	r3, #1
	strne	r3, [r9, #816]
	mov	r3, #2
	str	r3, [r6, #2348]
	ldr	r3, [r4]
	ldr	r3, [r3, #24]
	b	.L3497
.L3663:
	cmp	r0, #0
	beq	.L3497
	b	.L3504
.L3661:
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L3489
	ldr	r3, [r3, #160]
	cmp	r3, #1
	bne	.L3489
	bl	H264_Sei_Get_Frame_Pts
	b	.L3489
.L3533:
	ldrb	r3, [r5, #3009]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3538
	add	r7, r4, #24576
	ldr	r3, [r7, #2136]
.L3550:
	mvn	r10, #0
	mov	r9, r10
	b	.L3564
.L3565:
	bl	GetMinPOC
	ldr	r3, [r5, #3672]
	cmp	r3, #0
	bne	.L3557
	ldr	r2, [r5, #3676]
	ldr	r3, [fp, #-56]
	cmp	r2, r3
	blt	.L3671
.L3557:
	ldr	r8, [r7, #2140]
	cmp	r8, r10
	ldrne	r9, [fp, #-52]
	bne	.L3562
	ldr	r3, [fp, #-52]
	cmp	r3, r9
	beq	.L3672
	mov	r9, r3
.L3562:
	mov	r1, r9
	mov	r0, r4
	bl	OutputFrmFromDPB
	mov	r10, r8
	cmn	r0, #1
	beq	.L3563
	ldr	r3, [r7, #2136]
.L3564:
	ldr	ip, [r7, #2140]
	sub	r2, fp, #52
	sub	r1, fp, #56
	mov	r0, r4
	cmp	ip, r3
	bcs	.L3565
	ldr	r3, [r5, #3672]
	cmp	r3, #0
	beq	.L3566
	ldrb	r3, [r5, #3012]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3566
	ldr	r2, [r7, #2144]
	cmp	r2, #0
	beq	.L3566
	add	r2, r4, #26368
	mov	lr, r3
	add	r2, r2, #212
	b	.L3571
.L3568:
	ldr	r1, [r7, #2144]
	cmp	r1, r3
	bls	.L3673
.L3571:
	ldr	r1, [r2, #4]!
	add	r3, r3, #1
	ldr	r0, [r5, #3664]
	ldr	ip, [r1, #652]
	cmp	ip, r0
	bne	.L3568
	strb	lr, [r1, #2]
	ldr	r1, [r2]
	ldrb	r0, [r1, #4]	@ zero_extendqisi2
	cmp	r0, #1
	streq	r0, [r1, #668]
	ldreq	r1, [r2]
	streqb	lr, [r1, #4]
	ldreq	r1, [r2]
	ldr	r8, [r6, #1032]
	ldr	ip, [r1, #684]
	add	r0, ip, #15552
	cmp	ip, r8
	add	r0, r0, #48
	strne	lr, [r4, r0, asl #2]
	strne	r8, [r1, #684]
	b	.L3568
.L3673:
	ldr	ip, [r7, #2140]
.L3566:
	add	r2, r4, #60160
	mov	r1, ip
	add	r2, r2, #192
	mov	r0, r4
	bl	InsertFrmInDPB
	ldr	r2, [r7, #2140]
	str	r2, [r6, #392]
	subs	r3, r0, #0
	bne	.L3674
	add	r2, r2, #1
	mov	r0, r4
	str	r2, [r7, #2140]
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
.L3532:
	mov	r7, #0
	b	.L3573
.L3664:
	ldr	r3, [r5, #3672]
	cmp	r3, #0
	beq	.L3526
	ldrb	r3, [r5, #3014]	@ zero_extendqisi2
	cmp	r3, #5
	beq	.L3527
.L3531:
	mov	r0, r4
	add	r7, r4, #24576
	bl	SimpleSlideDPB
	add	r2, r4, #60160
	ldr	r1, [r7, #2140]
	add	r2, r2, #192
	mov	r0, r4
	bl	InsertFrmInDPB
	subs	r8, r0, #0
	beq	.L3675
	mov	r3, r8
	movw	r2, #3726
	ldr	r1, .L3684+20
	mov	r0, #0
	bl	dprint_vfmw
	movw	r3, #3727
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3536:
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	mov	r0, r4
	bl	RemoveUnUsedFrameStore
	cmp	r0, #0
	beq	.L3526
	ldr	r1, .L3684+28
	mov	r0, #22
	bl	dprint_vfmw
.L3526:
	ldrb	r3, [r5, #3009]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3538
	add	r7, r4, #24576
.L3542:
	ldr	r3, [r5, #3672]
	cmp	r3, #0
	beq	.L3676
	ldr	r2, [r7, #2144]
	ldr	r1, [r7, #2148]
	ldr	r3, [r7, #2136]
	add	r0, r1, r2
	cmp	r3, r0
	bhi	.L3550
	ldr	r0, [r4]
	ldr	r0, [r0, #24]
	cmp	r0, #3
	beq	.L3551
	ldr	r0, .L3684+32
	ldrb	r0, [r0]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L3551
	str	r1, [sp, #4]
	mov	r0, #1
	str	r2, [sp]
	movw	r2, #3838
	ldr	r1, .L3684+36
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearDPB
	mov	r3, #3840
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3676:
	ldr	r3, [r7, #2136]
	b	.L3550
.L3538:
	ldr	r3, [r6, #396]
	ldr	r0, [r5, #3656]
	cmp	r3, #0
	rsb	r1, r3, r0
	clz	r1, r1
	mov	r1, r1, lsr #5
	moveq	r1, #0
	cmp	r1, #0
	beq	.L3677
	mov	r0, r4
	bl	DirectOutput
	cmn	r0, #1
	mov	r7, r0
	beq	.L3678
	cmp	r0, #1
	ldreq	r2, [r5, #3656]
	moveq	r3, #0
	streqb	r3, [r2, #4]
	ldreq	r2, [r5, #3656]
	streqb	r3, [r2, #1]
.L3546:
	movw	r3, #3795
	mov	r2, r7
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3493
.L3662:
	ldr	r1, .L3684+40
	bl	dprint_vfmw
	mov	r0, r4
	bl	DirectOutput
	ldr	r3, [r5, #3724]
	ldr	r2, [r6, #1032]
	cmp	r3, r2
	addne	r3, r3, #15552
	addne	r3, r3, #48
	movne	r1, #0
	strne	r1, [r4, r3, asl #2]
	mov	r7, r0
	strne	r2, [r5, #3724]
	cmp	r0, #1
	ldr	r1, .L3684+8
	ldreq	r2, [r5, #3656]
	moveq	r3, #0
	streqb	r3, [r2, #4]
	ldreq	r2, [r5, #3656]
	streqb	r3, [r2, #1]
	mov	r2, r0
	movw	r3, #3554
	mov	r0, #14
	bl	dprint_vfmw
.L3493:
	cmn	r7, #1
	bne	.L3573
	b	.L3576
.L3501:
	cmp	r2, #1
	beq	.L3679
	cmp	r1, #0
	beq	.L3504
	ldrb	r2, [r9, #1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3504
	b	.L3497
.L3563:
	mov	r3, r0
	str	r0, [fp, #-64]
	movw	r2, #3886
	ldr	r1, .L3684+20
	mov	r0, #1
	bl	dprint_vfmw
	ldr	ip, [fp, #-64]
	movw	r3, #3887
	ldr	r1, .L3684+8
	mov	r0, #14
	mov	r2, ip
	bl	dprint_vfmw
	b	.L3576
.L3677:
	add	r7, r4, #24576
	ldr	ip, [r7, #2140]
	cmp	ip, #0
	beq	.L3542
	ldr	r3, [r7, #1944]
	cmp	r0, r3
	addne	r3, r4, #26368
	addne	r3, r3, #152
	beq	.L3543
.L3547:
	add	r1, r1, #1
	cmp	r1, ip
	beq	.L3542
	ldr	r2, [r3, #4]!
	cmp	r0, r2
	bne	.L3547
.L3543:
	add	r2, r4, #60160
	mov	r0, r4
	add	r2, r2, #192
	bl	InsertFrmInDPB
	cmn	r0, #1
	mov	r7, r0
	beq	.L3680
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	movw	r3, #3815
	mov	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3532
.L3665:
	ldr	r1, .L3684+44
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3684+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3535
	ldr	r7, [r5, #3700]
	mov	r3, #8
	ldr	lr, [r6, #2336]
	sub	r2, fp, #52
	mov	r1, #104
	ldr	r0, [r6, #2344]
	str	r7, [fp, #-52]
	str	lr, [fp, #-48]
	blx	ip
.L3535:
	mov	r0, r4
	bl	H264_ClearCurrPic
	mov	r0, r4
	bl	ClearDPB
	movw	r3, #3751
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3674:
	movw	r2, #3923
	ldr	r1, .L3684+20
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3924
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3518:
	ldr	r3, [r6, #2372]
	add	r3, r3, #1
	str	r3, [r6, #2372]
	b	.L3519
.L3675:
	ldr	r3, [r7, #2140]
	mov	r0, r4
	add	r3, r3, #1
	str	r3, [r7, #2140]
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	mov	r2, r8
	movw	r3, #3735
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3532
.L3551:
	ldr	r8, [r7, #2140]
	mov	r1, #0
	mvn	r2, #-2147483648
	str	r1, [fp, #-52]
	cmp	r8, r3
	strhi	r3, [r7, #2140]
	str	r2, [fp, #-56]
	movhi	r8, r3
	cmp	r8, #0
	beq	.L3582
	add	ip, r4, #26368
	ldr	r2, [fp, #-56]
	ldr	r1, [fp, #-52]
	add	ip, ip, #148
	mvn	lr, #-2147483648
	mov	r3, #0
.L3556:
	ldr	r0, [ip, #4]!
	ldr	r0, [r0, #664]
	cmp	r0, lr
	movlt	r1, r3
	add	r3, r3, #1
	movlt	r2, r0
	cmp	r3, r8
	mov	lr, r2
	bne	.L3556
	str	r2, [fp, #-56]
	str	r1, [fp, #-52]
.L3554:
	mov	r0, r4
	bl	RemoveFrameStoreOutDPB
	mov	r0, r4
	bl	UpdateReflist
	mov	r0, r4
	bl	UpdateLTReflist
	ldr	r3, [r7, #2136]
	b	.L3550
.L3666:
	mov	r2, #3
	ldr	r3, [r9, #680]
	strb	r2, [r9, #1]
	ldr	r2, [r7, #692]
	add	r3, r3, r2
	str	r3, [r9, #680]
	b	.L3509
.L3668:
	ldrd	r0, [ip, #-8]
	mvn	r3, #0
	mvn	r2, #0
	cmp	r1, r3
	cmpeq	r0, r2
	addne	r1, r8, #592
	bne	.L3512
	movw	r3, #61680
	ldrd	r2, [r3, r4]
	cmp	r3, r1
	add	r1, r8, #592
	cmpeq	r2, r0
	bne	.L3652
	b	.L3512
.L3678:
	mov	r3, r0
	movw	r2, #3785
	ldr	r1, .L3684+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3546
.L3671:
	ldr	r3, [r6, #2272]
	cmp	r3, #2
	beq	.L3681
.L3558:
	mov	r0, r4
	bl	DirectOutput
	cmn	r0, #1
	mov	r7, r0
	beq	.L3682
	cmp	r0, #1
	ldreq	r2, [r5, #3656]
	moveq	r3, #0
	streqb	r3, [r2, #4]
	ldreq	r2, [r5, #3656]
	streqb	r3, [r2, #1]
.L3560:
	movw	r3, #3868
	mov	r2, r7
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3493
.L3672:
	mov	r3, r9
	ldr	r2, .L3684+48
	ldr	r1, .L3684+52
	mov	r0, #1
	bl	dprint_vfmw
	movw	r3, #3875
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3670:
	mov	r1, r8
	mov	r0, r4
	bl	SetFrmRepeatCount.part.3
	b	.L3521
.L3527:
	mov	r0, r4
	bl	IDRMemMarking
	cmp	r0, #0
	beq	.L3531
	mvn	r0, #0
	b	.L3649
.L3679:
	cmp	r1, #1
	add	r7, r4, #60160
	add	r7, r7, #192
	ldr	r9, [r6, #288]
	beq	.L3683
	cmp	r1, #2
	ldreq	r3, [r5, #3688]
	streq	r3, [r9, #788]
	ldreqb	r1, [r5, #3011]	@ zero_extendqisi2
	b	.L3507
.L3681:
	ldrb	r3, [r5, #3011]	@ zero_extendqisi2
	cmp	r3, #0
	ldrne	r3, [r5, #3656]
	strne	r3, [r6, #400]
	b	.L3558
.L3680:
	mov	r3, r0
	mov	r2, #3808
	ldr	r1, .L3684+20
	mov	r0, #1
	bl	dprint_vfmw
	mov	r2, r7
	movw	r3, #3809
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3667:
	movw	r2, #3627
	ldr	r1, .L3684+56
	bl	dprint_vfmw
	movw	r3, #3628
	mvn	r2, #0
	ldr	r1, .L3684+8
	mov	r0, #14
	bl	dprint_vfmw
	b	.L3576
.L3682:
	mov	r3, r0
	movw	r2, #3859
	ldr	r1, .L3684+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L3560
.L3683:
	ldr	r3, [r5, #3684]
	str	r3, [r9, #748]
	ldrb	r1, [r5, #3011]	@ zero_extendqisi2
	b	.L3507
.L3582:
	mov	r1, r8
	b	.L3554
.L3685:
	.align	2
.L3684:
	.word	s_pstVfmwChan
	.word	.LC383
	.word	.LC377
	.word	g_event_report
	.word	.LC376
	.word	.LC381
	.word	.LC380
	.word	.LC384
	.word	g_apple_airplay_mirrorinig_flag
	.word	.LC385
	.word	.LC378
	.word	.LC382
	.word	.LANCHOR0+308
	.word	.LC386
	.word	.LC379
	UNWIND(.fnend)
	.size	StorePicInDPB, .-StorePicInDPB
	.align	2
	.global	AllocFrameStore
	.type	AllocFrameStore, %function
AllocFrameStore:
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
	add	r8, r0, #20480
	mov	r7, r0
	str	r1, [fp, #-56]
	ldrb	r3, [r8, #209]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3687
	ldrb	r3, [r8, #210]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3751
	add	r6, r0, #61440
	ldr	r3, [r6, #2272]
	cmp	r3, #2
	beq	.L3746
	add	r5, r7, #57344
	mov	r3, #0
	strb	r3, [r5, #3009]
	ldrb	r3, [r6, #368]	@ zero_extendqisi2
	cmp	r3, #1
	mov	r3, #2
	str	r3, [fp, #-52]
	bne	.L3717
.L3713:
	ldr	r2, [r6, #376]
	ldr	r3, [r8, #224]
	cmp	r2, r3
	bne	.L3717
	ldr	r3, [r8, #236]
	cmp	r3, #0
	ldr	r3, [r6, #372]
	beq	.L3752
	cmp	r3, #0
	beq	.L3717
.L3693:
	ldr	r3, [r6, #2356]
	ldr	r2, [r6, #2352]
	rsb	r3, r2, r3
	cmp	r3, #2
	bhi	.L3717
	ldr	r1, [r5, #3656]
	mov	r3, #1
	strb	r3, [r5, #3009]
	cmp	r1, #0
	beq	.L3695
	ldr	r3, [fp, #-52]
	cmp	r3, #2
	beq	.L3753
	ldr	r3, [fp, #-52]
	cmp	r3, #1
	beq	.L3754
.L3720:
	mov	ip, #0
	b	.L3699
.L3687:
	add	r6, r0, #61440
	ldr	r2, [r6, #2272]
	cmp	r2, #2
	strne	r3, [fp, #-52]
	addne	r5, r0, #57344
	strneb	r3, [r5, #3009]
	beq	.L3746
.L3717:
	mov	lr, #0
	strb	lr, [r5, #3008]
	ldr	r4, [r6, #1028]
	cmp	r4, lr
	addne	r10, r7, #26368
	addne	ip, r7, #27392
	addne	r10, r10, #152
	addne	r9, r7, #24576
	beq	.L3707
.L3706:
	ldrb	r3, [ip, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3702
	cmp	ip, #0
	beq	.L3722
	ldr	r1, [r9, #2140]
	cmp	r1, #0
	beq	.L3722
	ldr	r2, [r9, #1944]
	cmp	r2, ip
	beq	.L3702
	mov	r2, r10
	b	.L3704
.L3705:
	ldr	r0, [r2, #4]!
	cmp	r0, ip
	beq	.L3702
.L3704:
	add	r3, r3, #1
	cmp	r3, r1
	bne	.L3705
.L3722:
	mov	r9, #824
	movw	r0, #28072
	mla	r9, r9, lr, r7
	mov	r10, #0
	mov	r3, #1
	mov	r4, ip
	str	ip, [r5, #3656]
	mov	r2, #632
	add	r1, r9, #27392
	strb	r3, [r5, #3008]
	mov	ip, #101
	add	r1, r1, #16
	str	r10, [r9, r0]
	add	r0, r5, #3024
	str	ip, [r5, #3700]
	str	r3, [fp, #-48]
	bl	memcpy
	add	lr, r9, #27392
	str	r10, [r5, #3176]
	ldr	r3, [fp, #-48]
	strb	r10, [lr, #3]
	str	r10, [r4, #668]
	ldr	r2, [r5, #3656]
	strb	r10, [r2, #2]
	ldr	r2, [r5, #3656]
	strb	r3, [r2, #4]
	ldr	r3, [r5, #3656]
	str	r10, [r3, #816]
	ldrb	r4, [r5, #3008]	@ zero_extendqisi2
	cmp	r4, #1
	bne	.L3707
	ldr	r3, [fp, #-56]
	ldr	r0, [r6, #2344]
	clz	r1, r3
	mov	r1, r1, lsr #5
	bl	FSP_NewLogicFs
	mov	r1, r0
	str	r0, [fp, #-48]
	ldr	r0, [r6, #2344]
	bl	FSP_GetLogicFs
	ldr	r3, [fp, #-48]
	mvn	r2, r3
	mov	r2, r2, lsr #31
	cmp	r0, #0
	mov	r9, r0
	moveq	r2, #0
	cmp	r2, #0
	beq	.L3708
	ldr	r2, [r7]
	ldr	r2, [r2, #28]
	cmp	r2, #25
	beq	.L3755
.L3709:
	ldr	r4, .L3758
	mov	r2, #632
	ldr	r0, [r5, #3656]
	add	r1, r9, #40
	str	r3, [fp, #-48]
	ldr	ip, [r4, #52]
	add	r0, r0, #16
	blx	ip
	ldr	r1, [r5, #3656]
	add	r0, r7, #60160
	ldr	ip, [r4, #52]
	add	r1, r1, #16
	mov	r2, #632
	add	r0, r0, #208
	blx	ip
	ldr	r3, [fp, #-48]
	ldr	r2, [r5, #3656]
	mov	ip, r3
	str	r3, [r2, #648]
	ldrsb	r3, [r9, #4]
	ldr	r1, [r5, #3656]
	str	r3, [r5, #3724]
.L3699:
	ldrb	r2, [fp, #-52]	@ zero_extendqisi2
	strb	r2, [r5, #3011]
	ldrb	r3, [r8, #209]	@ zero_extendqisi2
	cmp	r3, #0
	movne	r3, #3
	strb	r3, [r1, #696]
	ldrb	r3, [r5, #3009]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L3756
	ldr	r3, [fp, #-52]
	strb	r2, [r6, #368]
	cmp	r3, #0
	ldr	r3, [r8, #224]
	ldr	r2, [r6, #2356]
	ldreq	r0, [fp, #-52]
	movne	r0, #0
	str	r3, [r6, #376]
	ldr	r3, [r8, #236]
	str	ip, [r6, #388]
	str	r2, [r6, #384]
	str	r3, [r6, #372]
	movne	r3, #1
	moveq	r3, r0
	strb	r3, [r6, #369]
.L3742:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3702:
	add	lr, lr, #1
	add	ip, ip, #824
	cmp	lr, r4
	bne	.L3706
.L3707:
	ldr	r1, .L3758+4
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r7
	mov	r1, #1
	bl	ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3751:
	add	r6, r0, #61440
	ldr	r2, [r6, #2272]
	cmp	r2, #2
	beq	.L3757
	add	r5, r7, #57344
	strb	r3, [r5, #3009]
	ldrb	r3, [r6, #368]	@ zero_extendqisi2
	cmp	r3, #2
	mov	r3, #1
	str	r3, [fp, #-52]
	bne	.L3717
	b	.L3713
.L3757:
	mov	r3, #1
.L3746:
	add	r5, r7, #57344
	str	r3, [fp, #-52]
.L3748:
	mov	r3, #0
	strb	r3, [r5, #3009]
	b	.L3717
.L3755:
	add	r1, r7, #12288
	ldr	r4, [r0, #152]
	ldr	r0, [r0, #76]
	ldr	r2, [r1, #1280]
	ldr	r1, [r1, #1276]
	str	r10, [r9, #280]
	mov	r2, r2, asl #4
	str	r10, [r9, #284]
	mov	r1, r1, asl #4
	str	r2, [r9, #112]
	mul	r4, r4, r2
	str	r1, [r9, #108]
	str	r10, [r9, #288]
	str	r10, [r9, #292]
	add	r0, r4, r0
	str	r10, [r9, #296]
	str	r0, [r9, #80]
	bl	MEM_Phy2Vir
	ldr	r1, [r9, #60]
	ldr	r2, [r9, #156]
	add	r4, r4, r1
	str	r10, [r9, #556]
	str	r4, [r9, #64]
	add	r4, r4, r2
	ldr	r3, [fp, #-48]
	str	r4, [r9, #72]
	str	r0, [r9, #552]
	b	.L3709
.L3756:
	mov	r3, #0
	strb	r3, [r6, #368]
	ldr	r1, [r8, #224]
	mov	r0, r3
	ldr	r2, [r6, #2356]
	str	r1, [r6, #376]
	ldr	r1, [r8, #236]
	strb	r3, [r6, #369]
	str	ip, [r6, #388]
	str	r1, [r6, #372]
	str	r2, [r6, #384]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3752:
	cmp	r3, #0
	beq	.L3693
	b	.L3717
.L3708:
	ldr	r3, [r5, #3656]
	mov	r0, r2
	strb	r2, [r5, #3008]
	ldr	r1, .L3758+8
	strb	r2, [r3, #4]
	bl	dprint_vfmw
	mov	r1, r4
	mov	r0, r7
	bl	ClearAll
	mvn	r0, #0
	b	.L3742
.L3754:
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3748
.L3698:
	ldr	r1, [r5, #3656]
	cmp	r1, #0
	bne	.L3720
	b	.L3717
.L3753:
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L3748
	b	.L3698
.L3695:
	strb	r1, [r5, #3009]
	b	.L3717
.L3759:
	.align	2
.L3758:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC387
	.word	.LC388
	UNWIND(.fnend)
	.size	AllocFrameStore, .-AllocFrameStore
	.global	__aeabi_idivmod
	.align	2
	.global	DecGap
	.type	DecGap, %function
DecGap:
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
	add	r10, r0, #24576
	mov	r6, r0
	add	r2, r0, #12288
	ldr	r0, [r10, #1804]
	add	r1, r6, #20480
	movw	r3, #2004
	str	r1, [fp, #-76]
	mov	ip, r1
	ldrb	r1, [r2, #1325]	@ zero_extendqisi2
	mul	r3, r3, r0
	cmp	r1, #1
	mov	r5, #0
	mov	r1, ip
	moveq	r1, #2
	movne	r1, r5
	str	r1, [fp, #-68]
	add	r1, r6, r3
	add	r1, r1, #22272
	ldr	r0, [ip, #224]
	add	r8, r6, #16384
	add	r4, r6, #57344
	mov	r3, r1
	add	r1, r1, #96
	str	r2, [fp, #-72]
	add	r3, r3, #100
	ldrb	r1, [r1, #7]	@ zero_extendqisi2
	ldr	r2, [r2, #3504]
	str	r0, [fp, #-60]
	str	r1, [fp, #-92]
	ldr	r0, [ip, #220]
	ldr	r1, [r8, #3472]
	ldr	ip, [r8, #3468]
	str	r3, [r4, #3660]
	ldr	r7, [r10, #2140]
	str	ip, [fp, #-84]
	cmp	r7, r5
	str	r1, [fp, #-88]
	str	r5, [fp, #-52]
	str	r5, [fp, #-48]
	beq	.L3776
	add	r2, r2, #4
	mov	r7, #1
	mov	r3, r7, asl r2
	add	r0, r0, r7
	str	r3, [fp, #-80]
	mov	r1, r3
	bl	__aeabi_uidivmod
	str	r5, [r8, #3472]
	mov	r0, #2
	str	r5, [r8, #3468]
	mov	r9, r1
	ldr	r1, .L3779
	bl	dprint_vfmw
	mov	r3, r9
	ldr	r2, [fp, #-60]
	mov	r0, #2
	ldr	r1, .L3779+4
	bl	dprint_vfmw
	sub	r2, fp, #52
	sub	r1, fp, #48
	mov	r0, r6
	bl	GetMaxPOC
	ldr	r3, [fp, #-60]
	cmp	r3, r9
	beq	.L3768
	mov	r3, r10
	str	r5, [fp, #-64]
	mov	r10, r4
	mov	r5, r7
	mov	r4, r3
	b	.L3769
.L3766:
	mov	r1, r7
	mov	r0, r6
	strb	r7, [r10, #3012]
	bl	StorePicInDPB
	ldr	r1, [fp, #-80]
	subs	r3, r0, #0
	add	r0, r9, #1
	bne	.L3777
	ldr	r3, [fp, #-76]
	str	r9, [r3, #220]
	bl	__aeabi_idivmod
	ldr	r3, [fp, #-60]
	cmp	r3, r1
	mov	r9, r1
	beq	.L3775
	ldr	r3, [r4, #2140]
	ldr	r2, [fp, #-64]
	cmp	r2, r3
	bhi	.L3775
.L3769:
	mov	r1, #1
	mov	r0, r6
	bl	AllocFrameStore
	mov	r7, #0
	ldr	r1, .L3779+8
	subs	r3, r0, #0
	mov	r0, #2
	bne	.L3778
	str	r3, [fp, #-56]
	bl	dprint_vfmw
	ldr	r1, [r10, #3656]
	strb	r5, [r10, #3014]
	ldr	r3, [fp, #-68]
	str	r9, [r1, #652]
	ldr	r1, [r10, #3656]
	str	r9, [r10, #3664]
	str	r9, [r1, #704]
	str	r3, [r10, #3672]
	ldr	r1, [r10, #3656]
	ldr	r3, [fp, #-56]
	str	r3, [r1, #700]
	ldr	r1, [r10, #3656]
	str	r5, [r1, #668]
	ldr	r1, [r10, #3656]
	strb	r3, [r1, #4]
	ldr	r1, [r10, #3656]
	strb	r5, [r1]
	ldr	r1, [r10, #3660]
	strb	r5, [r10, #3010]
	strb	r3, [r1, #3]
	ldr	r3, [fp, #-72]
	ldr	r3, [r3, #3508]
	cmp	r3, #0
	beq	.L3766
	str	r9, [r8, #3484]
	mov	r0, r6
	bl	DecPOC
	ldr	r3, [r8, #3464]
	ldr	r1, [fp, #-48]
	str	r3, [r10, #3676]
	ldr	r3, [r8, #3460]
	str	r3, [r10, #3680]
	ldr	r3, [r8, #3452]
	cmp	r3, r1
	str	r3, [r10, #3684]
	ldr	r3, [r8, #3456]
	str	r3, [r10, #3688]
	bls	.L3766
	cmp	r1, r3
	ldrcc	r3, [fp, #-64]
	addcc	r3, r3, #1
	strcc	r3, [fp, #-64]
	b	.L3766
.L3776:
	ldr	r1, .L3779+12
	mov	r0, r7
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3775:
	mov	r4, r10
.L3768:
	ldr	r3, [fp, #-84]
	mov	r0, #0
	ldrb	r2, [fp, #-92]	@ zero_extendqisi2
	str	r3, [r8, #3468]
	ldr	r3, [fp, #-88]
	str	r3, [r8, #3472]
	ldr	r3, [r4, #3660]
	strb	r2, [r3, #3]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3778:
	ldr	r3, [fp, #-84]
	mov	r0, r7
	ldrb	r2, [fp, #-92]	@ zero_extendqisi2
	ldr	r1, .L3779+16
	str	r3, [r8, #3468]
	ldr	r3, [fp, #-88]
	str	r3, [r8, #3472]
	ldr	r3, [r10, #3660]
	strb	r2, [r3, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3777:
	ldr	r2, [fp, #-84]
	mov	r0, r7
	ldrb	lr, [fp, #-92]	@ zero_extendqisi2
	ldr	r1, .L3779+20
	str	r2, [r8, #3468]
	ldr	r2, [fp, #-88]
	str	r2, [r8, #3472]
	movw	r2, #6265
	ldr	ip, [r10, #3660]
	strb	lr, [ip, #3]
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3780:
	.align	2
.L3779:
	.word	.LC390
	.word	.LC391
	.word	.LC393
	.word	.LC389
	.word	.LC392
	.word	.LC394
	UNWIND(.fnend)
	.size	DecGap, .-DecGap
	.align	2
	.global	H264DEC_Init
	.type	H264DEC_Init, %function
H264DEC_Init:
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
	ldr	r8, .L3794
	mov	r5, r0
	ldr	r4, [r0, #352]
	mov	r7, r1
	movw	r2, #63832
	mov	r1, #0
	ldr	r3, [r8, #48]
	blx	r3
	str	r4, [r5, #352]
	add	r0, r5, #8
	bl	ResetVoQueue
	mov	r3, #0
	str	r7, [r5]
	str	r3, [r5, #360]
	str	r3, [r5, #364]
	ldr	r3, [r7, #28]
	cmp	r3, #25
	beq	.L3791
	add	r6, r5, #12288
	mov	r1, #32
	mov	r2, #256
	mov	r3, #136
	str	r1, [r6, #1288]
	str	r2, [r6, #1292]
	str	r3, [r6, #1284]
.L3783:
	ldr	r0, [r7, #584]
	add	r4, r5, #61440
	bl	MEM_Phy2Vir
	ldr	lr, [r6, #1288]
	ldr	r3, [r5]
	mov	r2, #4000
	ldr	r1, [r6, #1292]
	mul	r2, r2, lr
	ldr	r3, [r3, #580]
	add	r3, r0, r3
	mov	r0, #2208
	add	ip, r3, r2
	str	r3, [r6, #1300]
	cmp	r3, #0
	cmpne	ip, #0
	str	ip, [r6, #1304]
	mla	r0, r0, r1, ip
	moveq	r9, #1
	movne	r9, #0
	cmp	r0, #0
	orreq	r9, r9, #1
	cmp	r9, #0
	str	r0, [r4, #2264]
	bne	.L3792
	ldr	r7, [r7, #616]
	mov	r10, r7
	adds	r7, r3, #0
	movne	r7, #1
	cmp	r10, #0
	movne	r7, #0
	cmp	ip, #0
	moveq	ip, #0
	andne	ip, r7, #1
	cmp	ip, #0
	beq	.L3786
	mov	r0, r3
	mov	r1, r9
	ldr	r3, [r8, #48]
	blx	r3
	ldr	r2, [r6, #1292]
	mov	ip, #2208
	mov	r1, r9
	ldr	r3, [r8, #48]
	ldr	r0, [r6, #1304]
	mul	r2, ip, r2
	blx	r3
	ldr	r1, [r6, #1292]
	ldr	lr, [r6, #1288]
	ldr	r0, [r4, #2264]
.L3786:
	add	r3, r5, #16384
	movw	r2, #4060
	ldr	ip, [r8, #48]
	str	r1, [r3, #1236]
	mov	r1, #0
	ldr	r3, [r6, #1284]
	mov	r7, r1
	str	lr, [r6, #1344]
	mul	r2, r2, r3
	blx	ip
	mov	r2, #40
	mov	r3, #17
	str	r7, [r4, #2288]
	str	r7, [r4, #2292]
	mov	r0, r5
	str	r7, [r4, #2296]
	str	r7, [r4, #2300]
	str	r7, [r4, #2304]
	str	r7, [r4, #2308]
	str	r7, [r4, #2312]
	str	r7, [r4, #2316]
	str	r7, [r4, #2280]
	str	r7, [r4, #1056]
	str	r7, [r4, #1060]
	str	r7, [r4, #1064]
	str	r7, [r4, #1068]
	str	r7, [r4, #1072]
	str	r7, [r4, #1036]
	str	r7, [r4, #1044]
	str	r7, [r4, #2348]
	str	r7, [r4, #1048]
	str	r7, [r4, #1052]
	str	r2, [r4, #1028]
	str	r3, [r4, #1032]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #2344]
	beq	.L3793
	mov	r1, r7
	mov	r0, r5
	bl	ClearAll
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3791:
	ldr	r3, [r7, #700]
	add	r6, r5, #12288
	str	r3, [r6, #1288]
	ldr	r3, [r7, #704]
	str	r3, [r6, #1292]
	ldr	r3, [r7, #692]
	str	r3, [r6, #1284]
	b	.L3783
.L3792:
	movw	r3, #12616
	ldr	r2, .L3794+4
	ldr	r1, .L3794+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3793:
	mov	r0, r7
	ldr	r1, .L3794+12
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3795:
	.align	2
.L3794:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR0+324
	.word	.LC395
	.word	.LC396
	UNWIND(.fnend)
	.size	H264DEC_Init, .-H264DEC_Init
	.align	2
	.global	InitPic
	.type	InitPic, %function
InitPic:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r3, r0, #12288
	add	r8, r0, #20480
	mov	r5, r0
	ldr	r0, [r3, #1304]
	mov	r10, #2208
	ldr	ip, [r8, #216]
	add	r4, r5, #57344
	str	r3, [fp, #-56]
	mov	r1, #4000
	ldrb	r2, [r4, #3008]	@ zero_extendqisi2
	mla	r10, r10, ip, r0
	cmp	r2, #0
	ldr	r3, [r3, #1300]
	addeq	r7, r5, #61440
	ldr	r2, [r10, #28]
	mla	r3, r1, r2, r3
	str	r3, [fp, #-60]
	beq	.L3797
	ldr	r3, [r4, #3656]
	cmp	r3, #0
	beq	.L3798
	ldrb	r6, [r3, #1]	@ zero_extendqisi2
	add	r7, r5, #61440
	cmp	r6, #0
	beq	.L3906
.L3799:
	mov	r3, #0
	strb	r3, [r4, #3008]
.L3797:
	sub	r1, fp, #48
	mov	r0, r5
	bl	GetReRangeFlag
	ldr	r3, [fp, #-56]
	ldr	r2, [r3, #1344]
	ldr	r3, [fp, #-60]
	ldr	r3, [r3, #36]
	cmp	r2, r3
	mov	r6, r0
	beq	.L3907
.L3800:
	ldr	r3, .L3921
	add	r0, r5, #13568
	ldr	r1, [fp, #-60]
	mov	r2, #0
	add	r0, r0, #28
	strb	r2, [r1, #24]
	mov	r2, #4000
	ldr	r3, [r3, #56]
	blx	r3
.L3801:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	bne	.L3802
	ldr	r3, [r5]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	beq	.L3802
.L3901:
	add	r6, r5, #16384
.L3803:
	ldr	r2, [r6, #1236]
	ldr	r3, [r10, #24]
	cmp	r2, r3
	beq	.L3908
.L3812:
	ldr	r3, .L3921
	add	r0, r5, #17408
	mov	r2, #0
	mov	r1, r10
	strb	r2, [r10, #20]
	add	r0, r0, #188
	ldr	r3, [r3, #56]
	mov	r2, #2208
	blx	r3
.L3813:
	ldr	r3, [r6, #3444]
	ldr	r2, [fp, #-56]
	cmp	r3, #0
	ldr	ip, [r2, #3504]
	movne	r3, #0
	strne	r3, [r8, #220]
	strne	r3, [r7, #376]
	ldr	r3, [r7, #2272]
	cmp	r3, #2
	beq	.L3815
	ldr	r3, [r5]
	ldr	r2, [r3, #24]
	str	r3, [fp, #-64]
	sub	r2, r2, #2
	cmp	r2, #1
	bls	.L3815
	ldr	r2, [r8, #224]
	ldr	r10, [r8, #220]
	cmp	r2, r10
	str	r2, [fp, #-68]
	beq	.L3816
	mov	r1, #1
	add	ip, ip, #4
	mov	ip, r1, asl ip
	add	r0, r10, r1
	str	ip, [fp, #-72]
	mov	r1, ip
	bl	__aeabi_uidivmod
	ldr	r2, [fp, #-68]
	cmp	r2, r1
	beq	.L3852
	ldr	r3, [fp, #-64]
	ldr	r1, [r3, #608]
	cmp	r1, #0
	bne	.L3817
	ldr	r1, [r3, #652]
	ldr	ip, [fp, #-72]
	cmp	r1, #1
	beq	.L3909
.L3818:
	cmp	r2, r10
	bls	.L3819
	ldr	r3, [r6, #484]
	rsb	r10, r10, r2
	cmp	r3, r10
	bcs	.L3817
	ldrb	r3, [r8, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3820
.L3825:
	ldr	r3, [r7, #2340]
	cmp	r3, #0
	bne	.L3817
	mov	r0, r5
	bl	H264_ClearCurrPic
	ldr	r3, .L3921+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3910
.L3826:
	ldr	ip, [r6, #484]
	movw	r2, #6476
.L3902:
	ldr	r1, [r8, #224]
	mov	r0, #0
	ldr	r3, [r8, #220]
	str	ip, [sp]
	rsb	r3, r3, r1
	ldr	r1, .L3921+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3820:
	cmp	r2, #0
	mov	r0, r5
	subeq	r2, ip, #1
	subne	r2, r2, #1
	str	r2, [r8, #220]
	bl	FlushDPB
	subs	r3, r0, #0
	bne	.L3911
	ldrb	r3, [r8, #208]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L3825
.L3817:
	mov	r0, r5
	bl	DecGap
	cmp	r0, #0
	bne	.L3912
.L3815:
	ldr	r10, [r8, #224]
.L3816:
	ldr	r3, [r8, #236]
	mov	r0, r5
	cmp	r3, #0
	strne	r10, [r8, #220]
	str	r10, [r6, #3484]
	bl	DecPOC
	mov	r1, #0
	mov	r0, r5
	bl	AllocFrameStore
	cmp	r0, #0
	bne	.L3913
	strb	r0, [r4, #3015]
	mov	r1, #1
	strb	r1, [r4, #3008]
	mvn	r3, #0
	ldrb	r2, [r8, #211]	@ zero_extendqisi2
	strb	r2, [r4, #3014]
	ldr	ip, [r8, #224]
	str	ip, [r4, #3664]
	ldr	r2, [r8, #236]
	str	ip, [fp, #-64]
	str	r2, [r4, #3672]
	ldr	lr, [r6, #3464]
	str	r2, [fp, #-68]
	str	lr, [r4, #3676]
	ldr	lr, [r6, #3460]
	str	lr, [r4, #3680]
	ldr	lr, [r6, #3452]
	str	lr, [r4, #3684]
	ldr	lr, [r6, #3456]
	strb	r0, [r4, #3010]
	strb	r0, [r4, #3013]
	str	lr, [r4, #3688]
	strb	r0, [r4, #3012]
	str	r3, [r4, #3720]
	ldrb	r3, [r8, #209]	@ zero_extendqisi2
	cmp	r3, #0
	strneb	r1, [r8, #209]
	ldr	lr, [r6, #464]
	movne	r3, r1
	str	r3, [fp, #-72]
	ldr	r3, [fp, #-56]
	movne	r1, #2
	ldrb	r0, [r3, #1326]	@ zero_extendqisi2
	rsb	r10, r0, #2
	mla	r10, lr, r10, r10
	mov	r0, r10
	bl	__aeabi_uidiv
	str	r10, [r4, #3712]
	ldr	r3, [fp, #-72]
	ldr	ip, [fp, #-64]
	cmp	r3, #0
	ldr	r2, [fp, #-68]
	movne	r3, #0
	str	r0, [r4, #3708]
	ldr	lr, [r6, #460]
	add	r1, lr, #1
	str	r1, [r4, #3704]
	mul	r1, r1, r0
	str	r1, [r4, #3716]
	ldrb	r1, [r6, #1212]	@ zero_extendqisi2
	strb	r1, [r4, #3016]
	movne	r1, r3
	beq	.L3914
.L3838:
	strb	r1, [r4, #3017]
	add	r1, r5, #24576
	str	r3, [r7, #2260]
	cmp	r2, #0
	strne	ip, [r8, #220]
	movw	r3, #2004
	ldr	lr, [r1, #1804]
	add	r2, r5, #60928
	movw	r10, #60960
	ldr	r1, .L3921+12
	mov	ip, r2
	add	r2, r2, #32
	mla	r3, r3, lr, r5
	ldr	lr, [fp, #-60]
	mov	r0, #29
	add	r3, r3, #22272
	add	r3, r3, #100
	str	r3, [r4, #3660]
	ldr	r3, [r5]
	ldrd	r8, [r3, #56]
	strd	r8, [r2, #-8]
	ldrd	r8, [r3, #72]
	strd	r8, [r5, r10]
	ldrd	r8, [r3, #88]
	strd	r8, [ip, #40]
	mvn	r8, #0
	ldr	ip, [r3, #104]
	mvn	r9, #0
	str	ip, [r4, #3024]
	ldr	ip, [r3, #108]
	str	ip, [r4, #3028]
	ldr	ip, [r3, #112]
	str	ip, [r4, #3032]
	ldr	ip, [r3, #128]
	str	ip, [r4, #3036]
	ldr	ip, [lr, #44]
	str	ip, [r4, #3192]
	ldr	ip, [lr, #48]
	str	ip, [r4, #3196]
	strd	r8, [r3, #56]
	ldrd	r2, [r2, #-8]
	bl	dprint_vfmw
	ldrd	r2, [r5, r10]
	ldr	r1, .L3921+16
	mov	r0, #29
	bl	dprint_vfmw
	ldr	r3, [r6, #460]
	ldr	r9, [fp, #-56]
	mov	r2, #4
	add	r3, r3, #1
	ldr	r8, .L3921
	add	r0, r5, #60416
	mov	r1, #0
	mov	r3, r3, asl r2
	str	r3, [r4, #3092]
	ldrb	ip, [r9, #1326]	@ zero_extendqisi2
	add	r0, r0, #16
	ldr	lr, [r6, #464]
	rsb	r3, ip, #2
	ldr	ip, [r8, #48]
	mla	r3, lr, r3, r3
	mov	r3, r3, asl r2
	str	r3, [r4, #3096]
	ldr	r9, [r9, #1348]
	ldr	r8, [r6, #528]
	subs	r9, r9, #1
	and	r8, r8, #7
	movne	r9, #1
	blx	ip
	ldrb	r2, [r4, #3088]	@ zero_extendqisi2
	mov	ip, #2
	ldrb	r3, [r4, #3089]	@ zero_extendqisi2
	add	r0, r5, #60160
	and	r2, r2, #252
	mov	r1, r8
	bfi	r2, r9, #2, #3
	bfi	r3, ip, #0, #2
	strb	r2, [r4, #3088]
	and	r3, r3, #243
	ldr	lr, [r6, #532]
	uxtb	r2, r2
	bfi	r3, ip, #4, #2
	strb	r3, [r4, #3089]
	bfi	r2, lr, #5, #3
	strb	r2, [r4, #3088]
	ldr	r3, [r4, #3088]
	add	r0, r0, #208
	bfi	r3, r8, #14, #3
	str	r3, [r4, #3088]
	bl	SetAspectRatio
	ldrb	r3, [r4, #3011]	@ zero_extendqisi2
	ldr	r2, [r4, #3656]
	adds	r3, r3, #0
	ldr	r1, [r7, #2304]
	movne	r3, #1
	cmp	r2, #0
	str	r3, [r4, #3076]
	str	r1, [r4, #3180]
	beq	.L3915
	ldr	r3, [r4, #3088]
	ldr	r1, [fp, #-60]
	str	r3, [r2, #80]
	ldr	r3, [r4, #3656]
	ldr	r2, [r4, #3076]
	str	r2, [r3, #68]
	ldr	r3, [r4, #3656]
	ldr	r2, [r4, #3128]
	str	r2, [r3, #120]
	ldr	r3, [r4, #3656]
	ldr	r2, [r4, #3124]
	str	r2, [r3, #116]
	ldr	r3, [r4, #3656]
	ldr	r2, [r4, #3092]
	str	r2, [r3, #84]
	ldr	r3, [r4, #3656]
	ldr	r2, [r4, #3096]
	str	r2, [r3, #88]
	ldr	r3, [r1, #3284]
	ldr	r2, [r4, #3656]
	str	r3, [r2, #100]
	str	r3, [r4, #3108]
	ldr	r2, [r4, #3656]
	ldr	r3, [r1, #3288]
	str	r3, [r2, #104]
	str	r3, [r4, #3112]
	ldr	r2, [r4, #3656]
	ldr	r3, [r1, #3276]
	str	r3, [r2, #92]
	str	r3, [r4, #3100]
	ldr	r2, [r4, #3656]
	ldr	r3, [r1, #3280]
	str	r3, [r2, #96]
	str	r3, [r4, #3104]
	ldr	r3, [r4, #3656]
	ldr	r0, [r7, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_GetDispPhyFs
	cmp	r0, #0
	beq	.L3841
	ldr	r3, [r4, #3076]
	mov	r1, #0
	ldr	r2, [r0, #4]
	subs	r3, r3, r1
	ldr	r0, [r7, #2344]
	movne	r3, #1
	bl	FSP_SetStoreType
.L3841:
	add	r2, r5, #60672
	add	r0, r5, #60928
	add	lr, r5, #62464
	ldr	r8, [r7, #1056]
	add	r2, r2, #232
	add	r0, r0, #8
	add	lr, lr, #36
	mov	r6, #0
.L3845:
	ldr	r3, [r2, #8]!
	cmp	r3, #0
	beq	.L3916
.L3842:
	cmp	r2, r0
	bne	.L3845
	cmp	r8, #0
	beq	.L3847
	ble	.L3847
	add	r6, r8, #15616
	mov	r9, #0
	add	r6, r6, #9
	add	r6, r5, r6, lsl #2
.L3848:
	ldr	r1, [r6, #-4]!
	sub	r8, r8, #1
	ldr	r0, [r7, #2344]
	bl	FreeUsdByDec
	cmp	r8, #0
	str	r9, [r6]
	bne	.L3848
.L3847:
	mov	r0, r5
	mov	r5, #0
	str	r5, [r7, #1056]
	str	r5, [r4, #3692]
	bl	CalcPicNum
	mov	r0, r5
.L3897:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3802:
	ldr	r3, [r7, #2304]
	cmp	r6, #0
	add	r3, r3, #1
	str	r3, [r7, #2304]
	bne	.L3804
	ldr	r3, [r5]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	beq	.L3805
	mov	r0, r5
	bl	FlushDPB
	cmp	r0, #0
	bne	.L3917
.L3900:
	mov	r0, r5
	bl	InitDPB
	cmp	r0, #0
	bne	.L3849
	ldr	r3, [r5]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	bne	.L3901
.L3810:
	add	r6, r5, #16384
	ldr	r1, [fp, #-56]
	add	r3, r5, #62464
	mov	r0, r5
	ldr	ip, [r6, #484]
	add	r3, r3, #4
	str	ip, [r7, #1032]
	ldr	r2, [r6, #464]
	ldrb	r1, [r1, #1326]	@ zero_extendqisi2
	add	r2, r2, #1
	ldr	lr, [r6, #460]
	rsb	r1, r1, #2
	str	ip, [sp]
	mov	r2, r2, asl #4
	add	ip, lr, #1
	mul	r2, r1, r2
	mov	ip, ip, asl #4
	str	ip, [fp, #-64]
	mov	r1, ip
	mov	r9, r2
	bl	H264_ArrangeVahbMem
	ldr	ip, [fp, #-64]
	cmp	r0, #1
	beq	.L3918
	ldr	r3, [r5]
	ldr	r3, [r3, #888]
	cmp	r3, #1
	mvneq	r0, #1
	beq	.L3897
	ldr	r3, [fp, #-56]
	mov	r4, #0
	ldr	r1, .L3921+20
	mov	r0, r4
	str	r4, [r3, #1276]
	str	r4, [r3, #1280]
	bl	dprint_vfmw
	mov	r1, r4
	mov	r0, r5
	bl	ClearAll
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3914:
	ldr	r1, [fp, #-56]
	ldrb	r1, [r1, #1327]	@ zero_extendqisi2
	cmp	r1, #0
	movne	r3, #1
	movne	r1, r3
	b	.L3838
.L3908:
	ldrb	r3, [r10, #20]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3813
	b	.L3812
.L3907:
	ldr	r3, [fp, #-60]
	ldrb	r3, [r3, #24]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3801
	b	.L3800
.L3916:
	cmp	r8, #0
	beq	.L3842
	ldr	r1, [r7, #1060]
	subs	r8, r8, #1
	stmia	r2, {r1, r3}
	beq	.L3843
	mov	r1, lr
.L3844:
	add	r3, r3, #1
	ldr	ip, [r1, #4]!
	cmp	r3, r8
	str	ip, [r1, #-4]
	bne	.L3844
.L3843:
	add	r3, r8, #15616
	add	r3, r3, #8
	add	r3, r5, r3, lsl #2
	str	r6, [r3, #4]
	str	r8, [r7, #1056]
	b	.L3842
.L3805:
	ldr	r1, .L3921+24
	mov	r0, #22
	bl	dprint_vfmw
	b	.L3900
.L3804:
	ldr	r1, .L3921+24
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	bl	InitDPB
	cmp	r0, #0
	beq	.L3810
.L3849:
	mov	r3, r0
	movw	r2, #6380
	ldr	r1, .L3921+28
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3852:
	mov	r10, r2
	b	.L3816
.L3906:
	ldr	r1, [r3, #648]
	mov	r2, #1
	ldr	r0, [r7, #2344]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #3656]
	strb	r6, [r3, #1]
	ldr	r3, [r4, #3656]
	strb	r6, [r3, #4]
	b	.L3799
.L3918:
	ldr	r2, [fp, #-56]
	mov	ip, ip, lsr #4
	mov	r3, r9, lsr #4
	str	ip, [r2, #1276]
	str	r3, [r2, #1280]
	b	.L3803
.L3819:
	rsb	r3, r10, r2
	ldr	r1, [r6, #484]
	add	r3, r3, ip
	cmp	r1, r3
	bcs	.L3817
	ldrb	r3, [r8, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3827
.L3832:
	ldr	r3, [r7, #2340]
	cmp	r3, #0
	bne	.L3817
	mov	r0, r5
	bl	H264_ClearCurrPic
	ldr	r3, .L3921+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3919
.L3833:
	ldr	ip, [r6, #484]
	movw	r2, #6509
	b	.L3902
.L3798:
	movw	r3, #6343
	ldr	r2, .L3921+32
	ldr	r1, .L3921+36
	mov	r0, #22
	bl	dprint_vfmw
	add	r7, r5, #61440
	b	.L3799
.L3912:
	movw	r2, #6519
	ldr	r1, .L3921+40
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3909:
	ldr	r1, [r3, #648]
	cmp	r1, #0
	bne	.L3818
	ldr	r1, [r3, #656]
	cmp	r1, #0
	bne	.L3818
	ldr	r3, [r3, #612]
	add	r3, r3, #1024
	cmp	r3, #2048
	bhi	.L3817
	b	.L3818
.L3913:
	movw	r2, #6538
	ldr	r1, .L3921+44
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3827:
	cmp	r2, #0
	mov	r0, r5
	subeq	r2, ip, #1
	subne	r2, r2, #1
	str	r2, [r8, #220]
	bl	FlushDPB
	subs	r3, r0, #0
	bne	.L3920
	ldrb	r3, [r8, #208]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L3817
	b	.L3832
.L3915:
	movw	r3, #6615
	ldr	r2, .L3921+32
	ldr	r1, .L3921+48
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3917:
	mov	r3, r0
	movw	r2, #6372
	mov	r0, r6
	ldr	r1, .L3921+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3910:
	mov	r0, r5
	bl	ClearDPB
	b	.L3826
.L3920:
	movw	r2, #6493
	ldr	r1, .L3921+52
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3919:
	mov	r0, r5
	bl	ClearDPB
	b	.L3833
.L3911:
	movw	r2, #6460
	ldr	r1, .L3921+52
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3897
.L3922:
	.align	2
.L3921:
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_apple_airplay_mirrorinig_flag
	.word	.LC400
	.word	.LC403
	.word	.LC404
	.word	.LC399
	.word	.LC406
	.word	.LC398
	.word	.LANCHOR0+340
	.word	.LC397
	.word	.LC401
	.word	.LC402
	.word	.LC405
	.word	.LC358
	UNWIND(.fnend)
	.size	InitPic, .-InitPic
	.align	2
	.global	H264_DecSlice
	.type	H264_DecSlice, %function
H264_DecSlice:
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
	add	r5, r0, #61440
	mov	r4, r0
	ldr	r1, .L3982
	ldr	r2, [r5, #2288]
	mov	r0, #22
	add	r6, r4, #20480
	sub	r2, r2, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #368]
	ldr	r1, .L3982+4
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	strb	r2, [r6, #211]
	ldr	r3, [r3, #76]
	str	r3, [r6, #236]
	ldr	r3, [r5, #2344]
	ldr	r3, [r1, r3, asl #2]
	ldrsb	r1, [r3, #44]
	cmp	r1, #1
	beq	.L3975
.L3924:
	mov	r0, r4
	bl	ProcessSliceHeaderFirstPart
	cmp	r0, #0
	bne	.L3974
	mov	r0, r4
	bl	ProcessSliceHeaderSecondPart
	cmp	r0, #0
	bne	.L3974
	ldr	r2, [r5, #2268]
	cmp	r2, #0
	moveq	r3, r2
	beq	.L3931
	add	r9, r4, #61696
	mov	r3, r0
	add	r9, r9, #156
	mov	r1, r0
	mov	r8, r0
	b	.L3939
.L3976:
	cmp	r7, r1
	add	r3, ip, r3
	rsbhi	r0, r0, r10
	rsbhi	r1, r1, r7
	addhi	r0, r1, r0
	movls	r0, r10
	add	r3, r3, r0
.L3937:
	cmp	lr, #0
	add	r8, r8, #1
	moveq	r1, r7
	moveq	r0, r10
	movne	r1, lr
	movne	r0, ip
	cmp	r8, r2
	beq	.L3931
.L3939:
	ldr	ip, [r9, #4]!
	ldr	r7, [ip, #8]
	ldr	lr, [ip, #36]
	cmp	r7, #0
	ldrne	r10, [ip, #12]
	moveq	r10, r7
	cmp	lr, #0
	ldrne	ip, [ip, #40]
	moveq	ip, lr
	cmp	r1, #0
	bne	.L3976
	add	r3, r10, r3
	add	r3, r3, ip
	b	.L3937
.L3931:
	add	r7, r4, #57344
	str	r3, [r5, #2328]
	movw	r0, #1620
	ldr	ip, [r7, #3708]
	ldr	r1, [r7, #3704]
	mul	r1, r1, ip
	cmp	r1, r0
	movgt	r1, r1, asl #8
	ble	.L3977
.L3941:
	add	r8, r4, #12288
	ldr	r0, [r8, #1284]
	cmp	r0, r2
	bls	.L3942
	cmp	r1, r3
	bcc	.L3942
	ldrb	r3, [r6, #213]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3978
.L3945:
	mov	r0, r4
	bl	PicTypeStatistic
	mov	r0, r4
	bl	DecList
	cmp	r0, #0
	bne	.L3979
	mov	r0, r4
	bl	IsRefListWrong
	subs	r6, r0, #0
	bne	.L3980
	mov	r0, r4
	bl	ExitSlice
	mov	r0, r4
	bl	CalcStreamBits
	mov	r0, r4
	bl	WriteSliceMsg
	ldr	r3, [r5, #2324]
	mov	r0, r6
	mov	r2, #1
	add	r3, r3, r2
	str	r2, [r5, #1036]
	str	r3, [r5, #2324]
.L3928:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L3977:
	mov	r0, r1, asl #9
	sub	r1, r0, r1, asl #7
	cmp	r1, #16384
	movlt	r1, #16384
	b	.L3941
.L3978:
	ldr	r1, .L3982+8
	mov	r0, #2
	bl	dprint_vfmw
	ldrb	r3, [r6, #211]	@ zero_extendqisi2
	mov	r2, #0
	str	r2, [r5, #2324]
	cmp	r3, #5
	ldr	r3, [r5, #2308]
	mov	r0, r4
	streq	r3, [r5, #2320]
	add	r3, r3, #1
	str	r3, [r5, #2308]
	ldrb	r3, [r7, #3011]	@ zero_extendqisi2
	cmp	r3, r2
	ldreq	r3, [r5, #2312]
	ldrne	r3, [r5, #2316]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r5, #2312]
	strne	r3, [r5, #2316]
	bl	InitPic
	cmn	r0, #2
	beq	.L3928
	cmp	r0, #0
	bne	.L3981
	mov	r0, r4
	bl	WritePicMsg
	b	.L3945
.L3975:
	ldr	r1, [r3, #156]
	cmp	r1, #0
	bne	.L3924
	ldr	r3, [r3, #160]
	cmp	r3, #1
	cmpeq	r2, #5
	bne	.L3924
	ldr	r3, [r4]
	mvn	r1, #0
	mvn	r0, #0
	ldrd	r2, [r3, #56]
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L3924
	movw	r1, #26464
	add	ip, r4, #26368
	ldrd	r0, [r1, r4]
	movw	lr, #26496
	strd	r2, [r4, lr]
	strd	r0, [ip, #136]
	b	.L3924
.L3974:
	ldr	r1, .L3982+12
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L3982+16
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L3972
	sub	r2, fp, #44
	mvn	r1, #0
	ldr	r0, [r5, #2344]
	mov	r3, #4
	str	r1, [r2, #-8]!
	mov	r1, #100
	blx	ip
.L3972:
	mov	r0, r4
	bl	ClearCurrSlice
	mvn	r0, #0
	b	.L3928
.L3942:
	str	r1, [sp]
	mov	r0, #0
	ldr	r1, .L3982+20
	bl	dprint_vfmw
	ldr	r2, [r8, #1284]
	ldr	r3, [r5, #2268]
	cmp	r3, r2
	bcc	.L3944
	ldr	r1, .L3982+16
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L3944
	str	r3, [fp, #-52]
	mov	r1, #108
	str	r2, [fp, #-48]
	mov	r3, #8
	sub	r2, fp, #52
	ldr	r0, [r5, #2344]
	blx	ip
.L3944:
	ldr	r1, .L3982+24
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	H264_ClearCurrPic
	mvn	r0, #0
	b	.L3928
.L3979:
	mov	r2, r0
	ldr	r1, .L3982+28
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3928
.L3980:
	ldr	r2, [r7, #3676]
	mov	r0, #1
	ldr	r1, .L3982+32
	bl	dprint_vfmw
	b	.L3972
.L3981:
	ldr	r1, .L3982+36
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L3928
.L3983:
	.align	2
.L3982:
	.word	.LC348
	.word	s_pstVfmwChan
	.word	.LC409
	.word	.LC349
	.word	g_event_report
	.word	.LC407
	.word	.LC408
	.word	.LC411
	.word	.LC412
	.word	.LC410
	UNWIND(.fnend)
	.size	H264_DecSlice, .-H264_DecSlice
	.align	2
	.global	H264_DecOneNal
	.type	H264_DecOneNal, %function
H264_DecOneNal:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #20)
	sub	sp, sp, #20
	mov	r5, r1
	ldr	r1, [r0, #368]
	add	r4, r0, #61440
	mov	r6, r0
	ldr	r3, [r1, #68]
	cmp	r3, #0
	movne	ip, r1
	movne	r2, #0
	ldrne	r3, [r4, #2328]
	beq	.L3989
.L3988:
	ldr	lr, [ip, #12]
	add	r2, r2, #1
	add	ip, ip, #28
	add	r3, r3, lr
	str	r3, [r4, #2328]
	ldr	lr, [r1, #68]
	cmp	lr, r2
	bhi	.L3988
.L3989:
	mov	r2, #0
	ldr	r3, .L4140
	strb	r2, [r1]
	ldr	r2, [r4, #2344]
	ldr	r3, [r3, r2, asl #2]
	ldrsb	r2, [r3, #44]
	cmp	r2, #1
	beq	.L4132
.L3987:
	add	r8, r6, #13504
	mov	r1, #32
	add	r8, r8, #24
	mov	r0, r8
	bl	BsGet
	ldr	r2, [r6, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #32
	str	r3, [r2, #64]
	mov	r7, r0
.L3990:
	ldr	lr, [r6, #368]
	and	r0, r7, #31
	ubfx	r2, r7, #5, #2
	ubfx	r3, r7, #7, #1
	mov	ip, #0
	ldr	r1, .L4140+4
	strb	r0, [lr, #2]
	mov	r0, #22
	ldr	lr, [r6, #368]
	str	r2, [lr, #76]
	ldr	r2, [r6, #368]
	str	r3, [r2, #80]
	str	ip, [r4, #2284]
	ldr	r3, [r6, #368]
	ldr	r2, [r4, #2288]
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r1, [r4, #2288]
	movw	r3, #371
	cmp	r1, r3
	beq	.L4133
.L3991:
	add	r1, r1, #1
	str	r1, [r4, #2288]
	ldr	r3, [r6, #368]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	cmp	r2, #20
	beq	.L4134
.L3992:
	sub	r3, r2, #1
	cmp	r3, #29
	ldrls	pc, [pc, r3, asl #2]
	b	.L4000
.L4002:
	.word	.L4001
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4001
	.word	.L4003
	.word	.L4004
	.word	.L4005
	.word	.L4006
	.word	.L4007
	.word	.L4008
	.word	.L4009
	.word	.L4010
	.word	.L4000
	.word	.L4004
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4011
	.word	.L4001
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4000
	.word	.L4012
.L4132:
	ldr	r2, [r3, #156]
	cmp	r2, #0
	bne	.L3987
	ldr	r2, [r3, #160]
	cmp	r2, #1
	bne	.L3987
	ldr	r3, [r3, #152]
	cmp	r5, #0
	cmpeq	r3, #1
	bne	.L3987
	add	r8, r6, #13504
	mov	r1, #40
	add	r8, r8, #24
	mov	r0, r8
	bl	BsSkip
	mov	r0, r8
	mov	r1, #8
	bl	BsGet
	ldr	r2, [r6, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #48
	str	r3, [r2, #64]
	mov	r7, r0
	b	.L3990
.L4012:
	mov	r2, #30
	ldr	r1, .L4140+8
	mov	r0, #22
	bl	dprint_vfmw
	cmp	r5, #0
	bne	.L4025
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L4025
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	str	r5, [r6, #368]
.L4025:
	mov	r1, #32
	mov	r0, r8
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r8
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L4118
	ldr	r5, .L4140+12
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4026
	mov	r3, #0
	mov	r1, #112
	mov	r2, r3
	ldr	r0, [r4, #2344]
	blx	ip
.L4026:
	mov	r7, #0
	mov	r0, r6
	str	r7, [r6, #364]
	bl	DecVDM
	cmp	r0, r7
	beq	.L4118
	ldr	ip, [r5]
	cmp	ip, r7
	beq	.L4117
	ldr	r0, [r4, #2344]
	mov	r3, r7
	mov	r2, r7
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L3998
.L4001:
	ldr	r3, [r4, #2300]
	mov	r0, #22
	ldr	r1, .L4140+16
	bl	dprint_vfmw
	ldr	r2, [r6, #368]
	add	r3, r6, #20480
	mov	r0, r6
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	strb	r1, [r3, #211]
	ldr	r2, [r2, #76]
	str	r2, [r3, #236]
	bl	SliceCheck
	subs	r5, r0, #0
	bne	.L4135
	mov	r0, r6
	bl	H264_DecSlice
	cmn	r0, #2
	beq	.L3998
	cmp	r0, #0
	beq	.L4118
	ldr	r3, .L4140+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4117
	ldr	r0, [r4, #2344]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	ip
.L4117:
	mvn	r0, #0
	b	.L3998
.L4003:
	ldr	r1, .L4140+20
	mov	r2, #6
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	H264_DecSEI
	ldr	r1, [r6, #368]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4020
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r6, #368]
.L4020:
	cmp	r5, #0
	bne	.L4136
.L4118:
	mov	r0, #0
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4004:
	ldr	r1, .L4140+24
	mov	r0, #22
	ldr	r3, [r4, #2292]
	bl	dprint_vfmw
	mov	r0, r6
	bl	H264_DecSPS
	ldr	r1, [r6, #368]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4018
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r6, #368]
.L4018:
	cmp	r5, #0
	bne	.L4137
	ldr	r3, [r4, #2292]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #2292]
	b	.L3998
.L4008:
	mov	r2, #11
	ldr	r1, .L4140+28
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	H264_IsEosNal
	cmp	r0, #1
	beq	.L4138
.L4127:
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L4118
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	mov	r0, r3
	str	r3, [r6, #368]
.L3998:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4009:
	ldr	r1, .L4140+32
	mov	r2, #12
.L4125:
	mov	r0, #22
	bl	dprint_vfmw
	b	.L4127
.L4010:
	mov	r2, #13
	ldr	r1, .L4140+36
	b	.L4125
.L4011:
	mov	r2, #19
	ldr	r1, .L4140+40
	b	.L4125
.L4006:
	mov	r2, #9
	ldr	r1, .L4140+44
	b	.L4125
.L4007:
	mov	r2, #10
	ldr	r1, .L4140+48
	b	.L4125
.L4005:
	ldr	r1, .L4140+52
	mov	r2, #8
	ldr	r3, [r4, #2296]
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	H264_DecPPS
	ldr	r1, [r6, #368]
	cmp	r1, #0
	mov	r5, r0
	beq	.L4016
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r6, #368]
.L4016:
	cmp	r5, #0
	bne	.L4139
	ldr	r3, [r4, #2296]
	mov	r0, r5
	add	r3, r3, #1
	str	r3, [r4, #2296]
	b	.L3998
.L4000:
	mov	r3, r7
	ldr	r1, .L4140+56
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r3, [r6, #368]
	ldr	r1, .L4140+60
	mov	r0, #0
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bl	dprint_vfmw
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L4027
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r6, #368]
.L4027:
	ldr	r3, .L4140+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4118
.L4120:
	mov	r3, #0
	ldr	r0, [r4, #2344]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	b	.L4118
.L4133:
	ldr	r1, .L4140+64
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r1, [r4, #2288]
	b	.L3991
.L4134:
	mov	r1, #24
	mov	r0, r8
	bl	BsGet
	ldr	r3, [r6, #368]
	ubfx	r2, r0, #23, #1
	strb	r2, [r3, #3]
	ldr	r1, [r6, #368]
	mov	r7, r0
	ldrb	r3, [r1, #3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3993
	ldrb	r2, [r4, #408]	@ zero_extendqisi2
	ldrb	r3, [r4, #406]	@ zero_extendqisi2
.L3994:
	cmp	r2, #0
	bne	.L3995
	cmp	r3, #1
	beq	.L3996
.L3995:
	ldr	r1, .L4140+68
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r1, [r6, #368]
	cmp	r1, #0
	beq	.L4117
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	mvn	r0, #0
	str	r3, [r6, #368]
	b	.L3998
.L3993:
	ubfx	r3, r0, #22, #1
	ubfx	r2, r0, #16, #6
	ubfx	ip, r7, #4, #1
	strb	r3, [r4, #404]
	strb	r2, [r4, #405]
	ubfx	r3, r0, #15, #1
	ubfx	r2, r7, #8, #4
	ubfx	r0, r0, #12, #3
	strb	ip, [r4, #410]
	ubfx	ip, r7, #2, #1
	strb	r0, [r4, #407]
	ubfx	r0, r7, #5, #3
	strb	r3, [r4, #406]
	strb	r0, [r4, #409]
	ubfx	r0, r7, #3, #1
	strb	r2, [r4, #408]
	strb	r0, [r4, #411]
	and	r0, r7, #3
	strb	ip, [r4, #412]
	strb	r0, [r4, #413]
	b	.L3994
.L4135:
	ldr	r1, .L4140+72
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	ClearCurrSlice
	ldr	r3, .L4140+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4117
.L4121:
	mov	r3, #0
	ldr	r0, [r4, #2344]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L3998
.L4139:
	ldr	r5, .L4140+12
	mov	r0, #1
	ldr	r2, .L4140+76
	ldr	r1, .L4140+80
	bl	dprint_vfmw
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4117
.L4123:
	sub	r2, fp, #36
	mvn	r6, #0
	mov	r3, #4
	mov	r1, #100
	str	r6, [r2, #-4]!
	ldr	r0, [r4, #2344]
	blx	ip
	ldr	ip, [r5]
	cmp	ip, #0
	bne	.L4121
	b	.L4117
.L4137:
	ldr	r5, .L4140+12
	mov	r0, #1
	ldr	r1, .L4140+84
	bl	dprint_vfmw
	ldr	ip, [r5]
	cmp	ip, #0
	bne	.L4123
	b	.L4117
.L4136:
	ldr	r1, .L4140+88
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L4140+12
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L4120
	b	.L4118
.L3996:
	ldrb	r3, [r4, #404]	@ zero_extendqisi2
	mov	r0, #22
	cmp	r3, #1
	moveq	r3, #5
	streqb	r3, [r1, #2]
	ldrb	ip, [r4, #409]	@ zero_extendqisi2
	ldreqb	r2, [r4, #408]	@ zero_extendqisi2
	ldrb	r3, [r4, #407]	@ zero_extendqisi2
	ldr	r1, .L4140+92
	str	ip, [sp]
	bl	dprint_vfmw
	mov	r2, r7
	ldr	r1, .L4140+96
	mov	r0, #22
	bl	dprint_vfmw
	ldr	r2, [r6, #368]
	ldr	r3, [r2, #64]
	add	r3, r3, #24
	str	r3, [r2, #64]
	ldr	r3, [r6, #368]
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	b	.L3992
.L4138:
	ldr	r5, .L4140+12
	add	r3, r6, #12288
	strb	r0, [r3, #1272]
	ldr	ip, [r5]
	cmp	ip, #0
	beq	.L4023
	mov	r3, #0
	mov	r1, #117
	mov	r2, r3
	ldr	r0, [r4, #2344]
	blx	ip
.L4023:
	mov	r7, #0
	mov	r0, r6
	str	r7, [r6, #364]
	bl	DecVDM
	cmp	r0, r7
	beq	.L4127
	ldr	r1, [r6, #368]
	cmp	r1, r7
	beq	.L4024
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	str	r7, [r6, #368]
.L4024:
	ldr	ip, [r5]
	cmp	ip, #0
	bne	.L4121
	b	.L4117
.L4141:
	.align	2
.L4140:
	.word	s_pstVfmwChan
	.word	.LC413
	.word	.LC432
	.word	g_event_report
	.word	.LC418
	.word	.LC424
	.word	.LC422
	.word	.LC429
	.word	.LC428
	.word	.LC430
	.word	.LC431
	.word	.LC426
	.word	.LC427
	.word	.LC420
	.word	.LC433
	.word	.LC434
	.word	.LC414
	.word	.LC415
	.word	.LC419
	.word	.LANCHOR0+348
	.word	.LC421
	.word	.LC423
	.word	.LC425
	.word	.LC416
	.word	.LC417
	UNWIND(.fnend)
	.size	H264_DecOneNal, .-H264_DecOneNal
	.align	2
	.global	H264DEC_DecodePacket
	.type	H264DEC_DecodePacket, %function
H264DEC_DecodePacket:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #28)
	sub	sp, sp, #28
	cmp	r1, #0
	mov	ip, #0
	mov	r5, r0
	str	ip, [fp, #-48]
	str	ip, [fp, #-52]
	str	ip, [fp, #-56]
	beq	.L4199
	ldr	r2, [r0]
	add	r4, r0, #61440
	ldr	lr, [r4, #1040]
	ldr	r3, [r2, #8]
	cmp	lr, #1
	mov	r3, r3, asl #16
	and	r3, r3, #458752
	str	r3, [r4, #2332]
	ldr	r3, [r2]
	str	r3, [r4, #2336]
	ldr	r3, [r2, #4]
	str	ip, [r4, #2284]
	str	r3, [r4, #2340]
	beq	.L4145
	ldr	r3, [r2, #840]
	cmp	r3, #1
	beq	.L4200
.L4146:
	mov	r0, r5
	bl	ReceivePacket
	ldr	r3, [r5, #368]
	str	r3, [r4, #2380]
.L4148:
	cmp	r0, #0
	mov	r0, #0
	str	r0, [r4, #1040]
	beq	.L4201
.L4197:
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L4200:
	ldr	r3, [r2, #888]
	cmp	r3, #1
	bne	.L4146
	ldr	r3, [r4, #2376]
	cmp	r3, #1
	bne	.L4146
	ldr	r3, [r4, #2380]
	str	r3, [r0, #368]
	str	ip, [r4, #2376]
	str	ip, [r4, #1040]
	b	.L4147
.L4201:
	ldr	r3, [r5, #368]
.L4147:
	mov	r2, #0
	add	r6, r5, #13504
	str	r2, [r3, #64]
	add	r6, r6, #24
	ldr	r3, [r5, #368]
	mov	r0, r6
	ldr	r2, [r3, #12]
	ldr	r1, [r3, #8]
	bl	BsInit
	ldr	r3, .L4209
	ldr	r2, [r4, #2344]
	ldr	ip, [r3, r2, asl #2]
	ldrsb	r7, [ip, #44]
	cmp	r7, #1
	beq	.L4149
.L4151:
	mov	r7, #0
.L4150:
	mov	r1, #32
	mov	r0, r6
	bl	BsGet
	ldr	r2, [r5, #368]
	uxtb	r0, r0
	and	r3, r0, #31
	and	r1, r0, #27
	strb	r3, [r2, #2]
	sub	ip, r3, #20
	ldr	r2, [r5, #368]
	clz	ip, ip
	cmp	r3, #20
	cmpne	r1, #1
	ubfx	r0, r0, #5, #2
	mov	ip, ip, lsr #5
	str	r0, [r2, #76]
	beq	.L4202
.L4152:
	mov	r0, r5
	bl	FindTrailZeros
	subs	r3, r0, #0
	bne	.L4203
	ldr	r2, [r5, #368]
	mov	r0, r6
	str	r3, [r2, #64]
	ldr	r3, [r5, #368]
	ldr	r1, [r3, #8]
	ldr	r2, [r3, #12]
	bl	BsInit
	mov	r1, r7
	mov	r0, r5
	bl	H264_DecOneNal
	cmn	r0, #2
	mov	r3, r0
	beq	.L4197
	cmp	r3, #0
	addeq	r5, r5, #57344
	moveq	r0, r3
	streq	r3, [r5, #3732]
	beq	.L4197
	ldr	r1, .L4209+4
	mov	r0, #22
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4197
.L4145:
	ldr	r0, [r0, #368]
	clz	r0, r0
	mov	r0, r0, lsr #5
	rsb	r0, r0, #0
	b	.L4148
.L4202:
	cmp	ip, #0
	bne	.L4204
.L4153:
	sub	r2, fp, #40
	sub	r1, fp, #44
	mov	r0, r5
	bl	InquireSliceProperty
	cmp	r0, #0
	beq	.L4205
	ldr	r1, [r5, #368]
	cmp	r1, #0
	beq	.L4164
	ldr	r0, [r4, #2344]
	bl	ReleaseNAL
	mov	r3, #0
	str	r3, [r5, #368]
.L4164:
	ldr	r3, .L4209+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L4198
	mov	r3, #0
	ldr	r0, [r4, #2344]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	mvn	r0, #0
	b	.L4197
.L4205:
	ldr	r2, [fp, #-44]
	ldr	r1, [r4, #2356]
	sub	r3, r2, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	cmp	r3, #0
	add	r3, r3, r1
	str	r3, [r4, #2356]
	bne	.L4206
.L4155:
	ldr	r3, [fp, #-40]
	cmp	r3, #1
	bne	.L4152
	mov	r0, r5
	bl	FlushDPB
	subs	r3, r0, #0
	bne	.L4207
.L4162:
	ldr	r0, [r4, #2344]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L4152
	sub	r3, fp, #48
	sub	r2, fp, #52
	sub	r1, fp, #56
	ldr	r0, [r4, #2344]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r5]
	ldr	r3, [r3, #724]
	cmp	r3, #1
	bne	.L4152
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ble	.L4208
.L4159:
	mov	r3, #1
	mvn	r0, #1
	str	r3, [r4, #1040]
	b	.L4197
.L4149:
	ldr	r3, [ip, #160]
	mov	r0, r5
	ldr	r2, [ip, #156]
	ldr	r1, [ip, #152]
	bl	H264_VES_Splitter
	cmp	r0, #3
	beq	.L4150
	cmp	r0, #0
	bne	.L4197
	b	.L4151
.L4204:
	mov	r0, r5
	bl	InquireSliceExtProperty
	b	.L4153
.L4203:
	ldr	r1, .L4209+12
	mov	r0, #22
	bl	dprint_vfmw
.L4198:
	mvn	r0, #0
	b	.L4197
.L4206:
	add	r8, r5, #20480
	ldrb	r3, [r8, #209]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #2360]
	addeq	r3, r3, #1
	addne	r3, r3, #2
	str	r3, [r4, #2360]
	ldr	r3, [r4, #2268]
	cmp	r3, #0
	beq	.L4155
	ldr	r3, [r5, #368]
	mov	ip, #0
	mov	r0, r6
	mov	r2, #12
	ldr	r1, .L4209+16
	str	ip, [r3, #64]
	bl	BsInit
	mov	r0, r5
	mov	r1, #1
	bl	H264_DecOneNal
	ldrb	r3, [r8, #209]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #2360]
	subeq	r3, r3, #1
	subne	r3, r3, #2
	str	r3, [r4, #2360]
	b	.L4159
.L4207:
	movw	r2, #13318
	ldr	r1, .L4209+20
	mov	r0, #0
	bl	dprint_vfmw
	b	.L4162
.L4199:
	mov	r0, r1
	movw	r3, #13199
	ldr	r2, .L4209+24
	ldr	r1, .L4209+28
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L4197
.L4208:
	ldr	r3, [fp, #-52]
	cmp	r3, #32
	bgt	.L4159
	ldr	r3, [r5, #360]
	cmp	r3, #0
	bne	.L4159
	ldr	r3, [r4, #2308]
	cmp	r3, #0
	beq	.L4152
	add	r2, r5, #12288
	ldr	r3, [r2, #1276]
	cmp	r3, #0
	beq	.L4152
	ldr	r2, [r2, #1280]
	ldr	r1, [r4, #2384]
	cmp	r2, r1
	beq	.L4152
	ldr	r1, [r4, #2388]
	cmp	r3, r1
	beq	.L4152
	ldr	r1, .L4209+8
	str	r2, [r4, #2384]
	str	r3, [r4, #2388]
	ldr	ip, [r1]
	cmp	ip, #0
	beq	.L4152
	mov	r3, #0
	ldr	r0, [r4, #2344]
	mov	r2, r3
	mov	r1, #120
	blx	ip
	b	.L4152
.L4210:
	.align	2
.L4209:
	.word	s_pstVfmwChan
	.word	.LC436
	.word	g_event_report
	.word	.LC435
	.word	.LANCHOR1+432
	.word	.LC358
	.word	.LC21
	.word	.LC22
	UNWIND(.fnend)
	.size	H264DEC_DecodePacket, .-H264DEC_DecodePacket
	.align	2
	.global	H264DEC_VDMPostProc
	.type	H264DEC_VDMPostProc, %function
H264DEC_VDMPostProc:
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
	ldr	r2, [r0, #360]
	add	r5, r0, #57344
	ldr	lr, [r0]
	mov	r8, r3
	mov	r4, r0
	ldrb	r3, [r2, #17]	@ zero_extendqisi2
	ldr	ip, [r5, #3656]
	ldr	r7, [lr, #636]
	strb	r3, [ip, #5]
	ldrb	r3, [r2, #4]	@ zero_extendqisi2
	ldr	r2, [fp, #8]
	str	r3, [ip, #8]
	ldr	r6, [r0, #364]
	cmp	r6, #0
	bne	.L4212
	ldr	r3, [fp, #4]
	str	r1, [r5, #3700]
	cmp	r3, #0
	beq	.L4213
	ldr	r3, .L4246
	mov	ip, r2, asl #6
	sub	r2, ip, r2, asl #3
	add	r2, r2, r3
	ldr	r3, [r2, #4]
	cmp	r3, #3
	beq	.L4242
	cmp	r3, #1
	beq	.L4213
.L4216:
	mov	r1, r8
	mov	r0, r4
	bl	StorePicInDPB
	cmp	r0, #1
	mov	r8, r0
	bls	.L4217
	ldr	r3, [r5, #3656]
	add	r1, r4, #61440
	mov	r2, #1
	mvn	r6, #0
	ldr	r0, [r1, #2344]
	ldr	r1, [r3, #648]
	bl	FSP_ClearLogicFs
	mov	r2, r8
	ldr	r1, .L4246+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	H264_ClearCurrPic
	mov	r0, r4
	bl	ClearDPB
	mov	r3, #0
	str	r3, [r5, #3656]
.L4215:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4212:
	str	r1, [r5, #3700]
	bl	ClearAllSlice
	mov	r1, r8
	mov	r0, r4
	bl	StorePicInDPB
	subs	r2, r0, #0
	bne	.L4243
.L4229:
	mov	r0, r4
	bl	FlushDPB
	subs	r2, r0, #0
	bne	.L4244
.L4230:
	add	r1, r4, #61440
	add	r2, r4, #12288
	mov	r3, #0
	add	r4, r4, #20480
	str	r3, [r1, #1036]
	mov	r6, r3
	ldr	r1, [r2, #1292]
	movw	r2, #23352
	strb	r3, [r4, #1848]
	movt	r2, 1
	str	r3, [r4, #1880]
	mov	lr, #2
	str	r1, [r4, #1856]
	mov	ip, #7
	str	r3, [r4, #1884]
	mov	r0, #32
	str	r2, [r4, #1864]
	mov	r1, #3
	mvn	r2, #0
	mov	r3, #262144
	strb	r0, [r4, #1850]
	mov	r0, r6
	strb	lr, [r4, #1849]
	str	ip, [r4, #1860]
	str	r1, [r4, #1872]
	str	r2, [r4, #1876]
	str	r3, [r4, #1888]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4213:
	mov	r0, r4
	bl	ClearAllSlice
	b	.L4216
.L4217:
	cmp	r7, #1
	beq	.L4245
.L4218:
	add	r4, r4, #61440
	mov	r3, #1
	mov	r0, r6
	str	r3, [r4, #1036]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L4244:
	ldr	r1, .L4246+8
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4230
.L4243:
	ldr	r1, .L4246+12
	mov	r0, #1
	bl	dprint_vfmw
	b	.L4229
.L4242:
	bl	ClearAllSlice
	b	.L4215
.L4245:
	ldr	r7, [r4, #360]
	ldr	r3, [r7, #316]
	add	r3, r3, #146
	ldr	r9, [r7, r3, asl #2]
	mov	r0, r9
	bl	MEM_Phy2Vir
	ldr	r2, [r7, #36]
	ldr	r8, [r7, #44]
	mov	r1, r9
	ldr	r3, .L4246+16
	mul	r8, r8, r2
	ldr	r3, [r3, #140]
	mov	r2, r8, asl #2
	mov	r10, r0
	blx	r3
	cmp	r8, #0
	beq	.L4231
	mov	r0, #0
	sub	r1, r10, #4
	mov	ip, r0
	mov	r7, r0
	mov	r2, r0
	mvn	r9, #-2147483648
.L4226:
	ldr	r3, [r1, #4]!
	ubfx	lr, r3, #0, #14
	tst	r3, #8192
	rsb	r10, lr, #0
	ubfx	lr, r3, #0, #13
	mov	r3, r3, asr #14
	ubfxne	lr, r10, #0, #13
	ubfx	r10, r3, #0, #12
	tst	r3, #2048
	rsb	r10, r10, #0
	ubfx	r3, r3, #0, #11
	ubfxne	r3, r10, #0, #11
	add	r3, lr, r3
	cmp	r7, r3
	movlt	r7, r3
	cmp	r3, #0
	addeq	ip, ip, #1
	beq	.L4225
	cmp	r9, r3
	movge	r9, r3
.L4225:
	add	r2, r2, #1
	add	r0, r0, r3
	cmp	r2, r8
	bne	.L4226
	mov	r3, #100
	mul	ip, r3, ip
.L4219:
	mov	r1, r8
	str	ip, [fp, #-48]
	bl	__aeabi_uidiv
	ldr	ip, [fp, #-48]
	mov	r1, r8
	mov	r10, r0
	mov	r0, ip
	bl	__aeabi_uidiv
	ldr	r2, [r5, #3656]
	cmp	r0, #100
	moveq	r9, #0
	cmp	r2, #0
	beq	.L4228
	ldr	r3, [r2, #260]
	cmp	r3, r7
	movcc	r3, r7
	str	r3, [r2, #260]
	ldr	r2, [r5, #3656]
	ldr	r3, [r2, #264]
	cmp	r3, r9
	movcc	r3, r9
	str	r3, [r2, #264]
	ldr	r3, [r5, #3656]
	str	r10, [r3, #268]
	ldr	r3, [r5, #3656]
	str	r0, [r3, #272]
	ldr	r3, [r5, #3656]
	ldr	r2, [r3, #260]
	str	r2, [r5, #3268]
	ldr	r2, [r3, #264]
	str	r10, [r5, #3276]
	str	r2, [r5, #3272]
	ldr	r3, [r3, #272]
	str	r3, [r5, #3280]
	b	.L4218
.L4231:
	mov	ip, r8
	mov	r0, r8
	mvn	r9, #-2147483648
	mov	r7, r8
	b	.L4219
.L4228:
	mov	r0, r2
	ldr	r1, .L4246+20
	bl	dprint_vfmw
	b	.L4218
.L4247:
	.align	2
.L4246:
	.word	g_VdmDrvParam+40
	.word	.LC437
	.word	.LC440
	.word	.LC439
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC438
	UNWIND(.fnend)
	.size	H264DEC_VDMPostProc, .-H264DEC_VDMPostProc
	.align	2
	.global	H264DEC_GetImageBuffer
	.type	H264DEC_GetImageBuffer, %function
H264DEC_GetImageBuffer:
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
	add	r4, r0, #61440
	mov	r5, r0
	ldr	r7, [r4, #1028]
	cmp	r7, #0
	beq	.L4264
	add	r6, r0, #27392
	add	r9, r0, #26368
	add	r9, r9, #152
	add	r8, r0, #24576
	mov	r1, r6
	mov	lr, #0
.L4256:
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4251
	cmp	r1, #0
	beq	.L4252
	ldr	r0, [r8, #2140]
	cmp	r0, #0
	beq	.L4252
	ldr	r2, [r8, #1944]
	cmp	r2, r1
	beq	.L4251
	mov	r2, r9
	b	.L4253
.L4254:
	ldr	ip, [r2, #4]!
	cmp	ip, r1
	beq	.L4251
.L4253:
	add	r3, r3, #1
	cmp	r3, r0
	bne	.L4254
.L4252:
	ldr	r0, [r4, #2344]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L4264
	cmn	r0, #1
	bne	.L4284
	add	r1, r5, #8
	ldr	r0, [r4, #2344]
	bl	FSP_ClearNotInVoQueue
	b	.L4284
.L4251:
	add	lr, lr, #1
	add	r1, r1, #824
	cmp	lr, r7
	bne	.L4256
	sub	r2, fp, #40
	sub	r1, fp, #44
	add	r0, r5, #8
	bl	GetQueueImgNum
	ldr	r1, .L4288
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, .L4288+4
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #1028]
	cmp	r3, #0
	addne	r8, r5, #26368
	addne	r9, r5, #24576
	addne	r8, r8, #152
	movne	r7, #0
	beq	.L4286
.L4257:
	cmp	r6, #0
	ldrb	r3, [r6, #1]	@ zero_extendqisi2
	ldrb	lr, [r6, #4]	@ zero_extendqisi2
	beq	.L4268
	ldr	r0, [r9, #2140]
	cmp	r0, #0
	beq	.L4268
	ldr	r2, [r9, #1944]
	cmp	r6, r2
	beq	.L4270
	mov	r1, r8
	mov	ip, #0
	b	.L4261
.L4262:
	ldr	r2, [r1, #4]!
	cmp	r6, r2
	beq	.L4270
.L4261:
	add	ip, ip, #1
	cmp	ip, r0
	bne	.L4262
.L4268:
	mov	r2, #1
.L4260:
	str	r2, [sp, #4]
	mov	r0, #0
	mov	r2, r7
	str	lr, [sp]
	ldr	r1, .L4288+8
	add	r7, r7, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #1028]
	add	r6, r6, #824
	cmp	r3, r7
	bhi	.L4257
.L4263:
	ldr	r3, [fp, #-40]
	mov	r0, #0
	ldr	r2, [fp, #-44]
	ldr	r1, .L4288+12
	bl	dprint_vfmw
	ldr	r3, [r4, #1028]
	ldr	r0, [r9, #2140]
	ldr	r2, [fp, #-44]
	sub	r3, r3, #2
	ldr	r1, [fp, #-40]
	rsb	r3, r0, r3
	add	r2, r2, r1
	cmp	r2, r3
	blt	.L4287
.L4284:
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4264:
	mov	r0, #1
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4270:
	mov	r2, #0
	b	.L4260
.L4287:
	ldr	r1, .L4288+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, r5
	mov	r1, #1
	bl	ClearAll
	mov	r0, #0
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L4286:
	add	r9, r5, #24576
	b	.L4263
.L4289:
	.align	2
.L4288:
	.word	.LC441
	.word	.LC442
	.word	.LC444
	.word	.LC443
	.word	.LC445
	UNWIND(.fnend)
	.size	H264DEC_GetImageBuffer, .-H264DEC_GetImageBuffer
	.align	2
	.global	H264DEC_GetImageWidth
	.type	H264DEC_GetImageWidth, %function
H264DEC_GetImageWidth:
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
	add	r0, r0, #16384
	ldr	r0, [r0, #460]
	add	r0, r0, #1
	mov	r0, r0, asl #4
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	H264DEC_GetImageWidth, .-H264DEC_GetImageWidth
	.align	2
	.global	H264DEC_GetImageHeight
	.type	H264DEC_GetImageHeight, %function
H264DEC_GetImageHeight:
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
	add	r3, r0, #16384
	add	r0, r0, #12288
	ldr	r3, [r3, #464]
	ldrb	r0, [r0, #1326]	@ zero_extendqisi2
	add	r3, r3, #1
	rsb	r0, r0, #2
	mov	r3, r3, asl #4
	mul	r0, r0, r3
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	H264DEC_GetImageHeight, .-H264DEC_GetImageHeight
	.global	TmpBuf
	.global	g_CabacMN
	.global	quant8_org
	.global	quant_org
	.global	quant8_inter_default
	.global	quant8_intra_default
	.global	quant_inter_default
	.global	quant_intra_default
	.global	g_ZZ_SCAN8
	.global	g_ZZ_SCAN
	.global	CalcZeroNum
	.global	g_AspecRatioIdc
	.global	g_NalTypeEOPIC
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__func__.14295, %object
	.size	__func__.14295, 23
__func__.14295:
	.ascii	"RemoveFrameStoreOutDPB\000"
	.space	1
	.type	g_ZZ_SCAN, %object
	.size	g_ZZ_SCAN, 16
g_ZZ_SCAN:
	.byte	0
	.byte	1
	.byte	4
	.byte	8
	.byte	5
	.byte	2
	.byte	3
	.byte	6
	.byte	9
	.byte	12
	.byte	13
	.byte	10
	.byte	7
	.byte	11
	.byte	14
	.byte	15
	.type	g_ZZ_SCAN8, %object
	.size	g_ZZ_SCAN8, 64
g_ZZ_SCAN8:
	.byte	0
	.byte	1
	.byte	8
	.byte	16
	.byte	9
	.byte	2
	.byte	3
	.byte	10
	.byte	17
	.byte	24
	.byte	32
	.byte	25
	.byte	18
	.byte	11
	.byte	4
	.byte	5
	.byte	12
	.byte	19
	.byte	26
	.byte	33
	.byte	40
	.byte	48
	.byte	41
	.byte	34
	.byte	27
	.byte	20
	.byte	13
	.byte	6
	.byte	7
	.byte	14
	.byte	21
	.byte	28
	.byte	35
	.byte	42
	.byte	49
	.byte	56
	.byte	57
	.byte	50
	.byte	43
	.byte	36
	.byte	29
	.byte	22
	.byte	15
	.byte	23
	.byte	30
	.byte	37
	.byte	44
	.byte	51
	.byte	58
	.byte	59
	.byte	52
	.byte	45
	.byte	38
	.byte	31
	.byte	39
	.byte	46
	.byte	53
	.byte	60
	.byte	61
	.byte	54
	.byte	47
	.byte	55
	.byte	62
	.byte	63
	.type	__func__.15302, %object
	.size	__func__.15302, 12
__func__.15302:
	.ascii	"H264_DecPPS\000"
	.type	SarTable.15380, %object
	.size	SarTable.15380, 136
SarTable.15380:
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
	.type	__func__.15562, %object
	.size	__func__.15562, 12
__func__.15562:
	.ascii	"H264_DecSEI\000"
	.type	__func__.14413, %object
	.size	__func__.14413, 13
__func__.14413:
	.ascii	"DirectOutput\000"
	.space	3
	.type	__func__.14876, %object
	.size	__func__.14876, 8
__func__.14876:
	.ascii	"InitDPB\000"
	.type	__func__.15831, %object
	.size	__func__.15831, 18
__func__.15831:
	.ascii	"H264_VES_Splitter\000"
	.space	2
	.type	__func__.14540, %object
	.size	__func__.14540, 14
__func__.14540:
	.ascii	"StorePicInDPB\000"
	.space	2
	.type	__FUNCTION__.15800, %object
	.size	__FUNCTION__.15800, 13
__FUNCTION__.15800:
	.ascii	"H264DEC_Init\000"
	.space	3
	.type	__FUNCTION__.15013, %object
	.size	__FUNCTION__.15013, 8
__FUNCTION__.15013:
	.ascii	"InitPic\000"
	.type	__func__.15705, %object
	.size	__func__.15705, 15
__func__.15705:
	.ascii	"H264_DecOneNal\000"
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	quant_org, %object
	.size	quant_org, 16
quant_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	quant8_org, %object
	.size	quant8_org, 64
quant8_org:
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.word	269488144
	.type	quant_intra_default, %object
	.size	quant_intra_default, 16
quant_intra_default:
	.word	471076102
	.word	538711053
	.word	622861332
	.word	707076124
	.type	quant_inter_default, %object
	.size	quant_inter_default, 16
quant_inter_default:
	.word	403967498
	.word	454562830
	.word	505092116
	.word	572398360
	.type	quant8_intra_default, %object
	.size	quant8_intra_default, 64
quant8_intra_default:
	.word	269289990
	.word	454629138
	.word	303041290
	.word	488315159
	.word	387059725
	.word	522001177
	.word	420942352
	.word	555687195
	.word	454629138
	.word	606150429
	.word	488315159
	.word	639901983
	.word	522001177
	.word	673588257
	.word	555687195
	.word	707274276
	.type	quant8_inter_default, %object
	.size	quant8_inter_default, 256
quant8_inter_default:
	.word	286199049
	.word	404100371
	.word	319884557
	.word	421008917
	.word	353571087
	.word	454629398
	.word	370479889
	.word	471537944
	.word	404100371
	.word	505158425
	.word	421008917
	.word	538844187
	.word	454629398
	.word	555752988
	.word	471537944
	.word	589373470
	.space	192
	.type	g_NalTypeEOPIC, %object
	.size	g_NalTypeEOPIC, 12
g_NalTypeEOPIC:
	.byte	0
	.byte	0
	.byte	1
	.byte	30
	.byte	72
	.byte	83
	.byte	80
	.byte	73
	.byte	67
	.byte	69
	.byte	78
	.byte	68
	.type	g_CabacMN, %object
	.size	g_CabacMN, 5120
g_CabacMN:
	.word	388044546
	.word	352326208
	.word	153820416
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	721207
	.word	4522025
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	521477919
	.word	422707200
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	388044546
	.word	352326208
	.word	153820416
	.word	3013710
	.word	-44040151
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	203950899
	.word	238747648
	.word	0
	.word	0
	.word	87683918
	.word	-180289218
	.word	17367089
	.word	-613020375
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	21230414
	.word	-180289218
	.word	440602714
	.word	157864575
	.word	-328728576
	.word	0
	.word	0
	.word	0
	.word	204602441
	.word	288553558
	.word	-278922691
	.word	154007875
	.word	-78971830
	.word	-78579384
	.word	20578304
	.word	0
	.word	-45745583
	.word	-178256329
	.word	121895766
	.word	39321658
	.word	-45287842
	.word	87426117
	.word	-45023144
	.word	0
	.word	370745856
	.word	268442146
	.word	320219136
	.word	219088691
	.word	38797353
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	421532977
	.word	355860480
	.word	0
	.word	0
	.word	37878343
	.word	-212925132
	.word	-32963543
	.word	-478802647
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-62064057
	.word	-212925132
	.word	956442916
	.word	440783743
	.word	-245039104
	.word	0
	.word	0
	.word	0
	.word	154336582
	.word	171312709
	.word	-212205516
	.word	137101122
	.word	-11730618
	.word	-27854008
	.word	3997696
	.word	0
	.word	-28968110
	.word	-161480133
	.word	38534487
	.word	-43777736
	.word	-45417899
	.word	3931473
	.word	-111740065
	.word	0
	.word	487594240
	.word	234886184
	.word	336207104
	.word	119732056
	.word	-327221207
	.word	4128831
	.word	4128768
	.word	0
	.word	351339062
	.word	55239807
	.word	-378996171
	.word	-13236429
	.word	354489138
	.word	289210368
	.word	0
	.word	0
	.word	437320789
	.word	-395967175
	.word	-164364994
	.word	-446493399
	.word	54458195
	.word	72745057
	.word	-112721920
	.word	0
	.word	-28640171
	.word	-395967175
	.word	905979178
	.word	207741055
	.word	-361431040
	.word	0
	.word	0
	.word	0
	.word	104460105
	.word	238680669
	.word	-229049812
	.word	70714167
	.word	-61866421
	.word	-194905806
	.word	20709376
	.word	0
	.word	-178654873
	.word	-344714439
	.word	339346516
	.word	106955071
	.word	-78253206
	.word	88016459
	.word	-44368027
	.word	0
	.word	-276827290
	.word	5437770
	.word	-345250433
	.word	-511711105
	.word	-295705217
	.word	-344792449
	.word	0
	.word	0
	.word	-277089165
	.word	-260377229
	.word	-45614550
	.word	-80544458
	.word	-29491142
	.word	20971080
	.word	-11864229
	.word	0
	.word	-111282857
	.word	-45221049
	.word	-62915516
	.word	-195757762
	.word	-113178563
	.word	87621186
	.word	20971581
	.word	-28442624
	.word	402657033
	.word	135859474
	.word	252251411
	.word	170200082
	.word	102568993
	.word	253625389
	.word	20578366
	.word	121438208
	.word	-94504364
	.word	-129040318
	.word	-12124098
	.word	-29557189
	.word	-78906050
	.word	-63244478
	.word	-11599801
	.word	54788096
	.word	252053011
	.word	118492174
	.word	302845195
	.word	219090704
	.word	202837271
	.word	252972570
	.word	237769000
	.word	288292864
	.word	-197132732
	.word	-246090904
	.word	-79430885
	.word	-47710676
	.word	3076160
	.word	-129698226
	.word	-95553962
	.word	0
	.word	20055860
	.word	170065964
	.word	187040045
	.word	3015980
	.word	521208115
	.word	120724499
	.word	270601790
	.word	0
	.word	203819821
	.word	254217002
	.word	220991533
	.word	204016177
	.word	505549354
	.word	171381043
	.word	288227417
	.word	0
	.word	170719550
	.word	254021160
	.word	270208029
	.word	19665956
	.word	304088362
	.word	19925566
	.word	288229696
	.word	0
	.word	403772693
	.word	420880155
	.word	371004195
	.word	238160441
	.word	121634381
	.word	-61670050
	.word	155579501
	.word	0
	.word	-45680547
	.word	-161815937
	.word	-195235529
	.word	-163775938
	.word	-62786487
	.word	-129173168
	.word	-145166482
	.word	0
	.word	-210964124
	.word	-211422373
	.word	-195103144
	.word	-262867370
	.word	-111938729
	.word	-312606394
	.word	4782922
	.word	305856512
	.word	451745519
	.word	451878631
	.word	485237225
	.word	635773417
	.word	686040815
	.word	569714929
	.word	704259585
	.word	688979968
	.word	-194448031
	.word	-262080168
	.word	-128583339
	.word	-145362088
	.word	71499085
	.word	-45286836
	.word	171638604
	.word	-11337728
	.word	618472670
	.word	551953890
	.word	752886510
	.word	586230001
	.word	569975803
	.word	553657858
	.word	554506019
	.word	221904896
	.word	-11863455
	.word	-111416193
	.word	-178131884
	.word	-179307959
	.word	-62196906
	.word	-211749535
	.word	-311099392
	.word	0
	.word	-127471260
	.word	6225920
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	519707395
	.word	437649408
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-110890401
	.word	39780352
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	503126528
	.word	371064832
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-63374510
	.word	-112399747
	.word	-129041631
	.word	-63898059
	.word	-46206137
	.word	-162532266
	.word	-212143519
	.word	0
	.word	-62193080
	.word	-179569337
	.word	254735173
	.word	4063297
	.word	354808136
	.word	154734646
	.word	4066376
	.word	0
	.word	636494844
	.word	653797117
	.word	620963333
	.word	704652048
	.word	655756848
	.word	455415100
	.word	205783649
	.word	0
	.word	5045066
	.word	4650315
	.word	21233729
	.word	-230096066
	.word	71237444
	.word	-213185737
	.word	88083526
	.word	0
	.word	536421361
	.word	587014659
	.word	620700165
	.word	537600773
	.word	571221771
	.word	505225754
	.word	489100098
	.word	0
	.word	0
	.word	0
	.word	-45351145
	.word	19005739
	.word	3604023
	.word	3998016
	.word	4519772
	.word	0
	.word	-277287824
	.word	-294455979
	.word	-245566887
	.word	-431492783
	.word	-229638076
	.word	-230234056
	.word	-381360078
	.word	-179699712
	.word	401808115
	.word	686895602
	.word	738405638
	.word	740434230
	.word	324141056
	.word	0
	.word	0
	.word	0
	.word	-227871903
	.word	-245697446
	.word	-296159671
	.word	-145755562
	.word	-162924986
	.word	-163185854
	.word	-146736326
	.word	37421056
	.word	368449781
	.word	486022399
	.word	486743305
	.word	588520740
	.word	239271936
	.word	0
	.word	0
	.word	0
	.word	-444668830
	.word	-412751549
	.word	-464327586
	.word	-262935954
	.word	-346296730
	.word	-211950721
	.word	0
	.word	0
	.word	-111346855
	.word	-111086740
	.word	-95617492
	.word	2949172
	.word	-46072261
	.word	-62456757
	.word	-128782490
	.word	0
	.word	-27919794
	.word	-11798195
	.word	37094706
	.word	-45874894
	.word	103480401
	.word	20970566
	.word	4391481
	.word	-28573696
	.word	186384936
	.word	53215281
	.word	3015212
	.word	36896815
	.word	69665342
	.word	103678006
	.word	53871162
	.word	71237632
	.word	-211095446
	.word	-162010254
	.word	-294718878
	.word	-361829526
	.word	-295179413
	.word	-378739088
	.word	-161418145
	.word	-77922304
	.word	235604750
	.word	151720459
	.word	352917502
	.word	552673521
	.word	585836521
	.word	719268321
	.word	786704116
	.word	354222080
	.word	-47251647
	.word	-12978339
	.word	-145947880
	.word	2752560
	.word	3668539
	.word	-112724909
	.word	-178789769
	.word	0
	.word	186844224
	.word	20777763
	.word	303631384
	.word	220007716
	.word	-161613495
	.word	-28766930
	.word	154270052
	.word	0
	.word	104007225
	.word	120915508
	.word	104270637
	.word	237242421
	.word	-11401417
	.word	-45215954
	.word	371195732
	.word	0
	.word	-144840098
	.word	-78247613
	.word	-61802923
	.word	-12187844
	.word	154797373
	.word	204607282
	.word	305205558
	.word	0
	.word	770192851
	.word	820396501
	.word	736962550
	.word	503910938
	.word	337313849
	.word	-229442741
	.word	-312353411
	.word	0
	.word	-45418660
	.word	-128456322
	.word	20643101
	.word	-14417626
	.word	36436535
	.word	3801152
	.word	-45418918
	.word	0
	.word	154468917
	.word	87424573
	.word	3670072
	.word	-213910724
	.word	-12712903
	.word	-96140231
	.word	237438003
	.word	222560256
	.word	419897081
	.word	469965828
	.word	536879871
	.word	503717382
	.word	537468691
	.word	437983774
	.word	622074914
	.word	289800192
	.word	170460974
	.word	-13433039
	.word	137627945
	.word	103744055
	.word	220793388
	.word	103941429
	.word	221316159
	.word	104857600
	.word	452992000
	.word	536615686
	.word	570957322
	.word	404103443
	.word	371202591
	.word	355015212
	.word	388960321
	.word	239534080
	.word	87426620
	.word	104531525
	.word	4652061
	.word	85919530
	.word	20708922
	.word	-45548207
	.word	-178192384
	.word	0
	.word	54526269
	.word	155123712
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	21169467
	.word	155385856
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28967365
	.word	105250816
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	138151487
	.word	289472512
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-13631420
	.word	-62523304
	.word	3803141
	.word	168693266
	.word	219873832
	.word	3865926
	.word	-95422379
	.word	0
	.word	120721447
	.word	86770740
	.word	187759420
	.word	-12910533
	.word	371262764
	.word	237764430
	.word	3934533
	.word	0
	.word	270406176
	.word	304289309
	.word	404690726
	.word	304813097
	.word	188680507
	.word	155254622
	.word	-27658388
	.word	0
	.word	170658079
	.word	204145461
	.word	237111846
	.word	-46920408
	.word	287311660
	.word	119934258
	.word	171514411
	.word	0
	.word	353900308
	.word	437721888
	.word	471276568
	.word	388503584
	.word	471668522
	.word	322508341
	.word	373099350
	.word	0
	.word	0
	.word	0
	.word	-96274141
	.word	-114624467
	.word	-80677832
	.word	-96666818
	.word	-129828788
	.word	0
	.word	-61867705
	.word	-79300794
	.word	-129829308
	.word	-313920443
	.word	-263786173
	.word	-331420346
	.word	-264050111
	.word	-331415552
	.word	167647991
	.word	569845753
	.word	704523523
	.word	822684955
	.word	607846400
	.word	0
	.word	0
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	368255474
	.word	670641918
	.word	855784454
	.word	1024538402
	.word	708706304
	.word	0
	.word	0
	.word	0
	.word	-645927333
	.word	-278862255
	.word	-580720538
	.word	-379460233
	.word	-396104850
	.word	-295248769
	.word	0
	.word	0
	.word	5307225
	.word	-111215524
	.word	-378474169
	.word	-113442763
	.word	-79497907
	.word	-145688748
	.word	-162013569
	.word	0
	.word	-211291301
	.word	-145100196
	.word	-129174441
	.word	-378607511
	.word	-162599824
	.word	-278678913
	.word	-1166029185
	.word	-763428864
	.word	70060572
	.word	169812469
	.word	886379023
	.word	469771242
	.word	652681728
	.word	669917428
	.word	1721892864
	.word	955318272
	.word	-344004228
	.word	-328276354
	.word	-411242647
	.word	-444996235
	.word	-278469003
	.word	-445325446
	.word	-161484188
	.word	-127991808
	.word	335155962
	.word	234887924
	.word	535831015
	.word	568993252
	.word	669133538
	.word	802565596
	.word	836643311
	.word	537460736
	.word	2555969
	.word	-246096513
	.word	-345637593
	.word	-80348867
	.word	-179572403
	.word	-279189653
	.word	-412097414
	.word	0
	.word	-62719154
	.word	-62392248
	.word	37486391
	.word	-112788917
	.word	-128328073
	.word	-45408236
	.word	504812671
	.word	0
	.word	570170634
	.word	637219811
	.word	670512350
	.word	1170621377
	.word	754655239
	.word	937631745
	.word	6948
	.word	0
	.word	-277879694
	.word	-94765488
	.word	-61671595
	.word	-128843960
	.word	88080707
	.word	154665029
	.word	21301061
	.word	0
	.word	1169768385
	.word	1119899062
	.word	920204509
	.word	703996928
	.word	687808014
	.word	471471909
	.word	204933953
	.word	0
	.word	-28707736
	.word	-144973441
	.word	-179505620
	.word	-164301255
	.word	-147132344
	.word	-112853947
	.word	-78973098
	.word	0
	.word	3603261
	.word	3866428
	.word	-46270397
	.word	-413863350
	.word	-79624908
	.word	37290045
	.word	-146410170
	.word	305594368
	.word	568795874
	.word	618931940
	.word	652550894
	.word	602940146
	.word	553133562
	.word	587210250
	.word	470948377
	.word	489226240
	.word	-112854461
	.word	-263324096
	.word	37616195
	.word	-46136775
	.word	-46006974
	.word	4065587
	.word	-12386745
	.word	-28639232
	.word	635381724
	.word	685450978
	.word	786377442
	.word	686305763
	.word	653535478
	.word	654126843
	.word	521411870
	.word	422313984
	.word	53937976
	.word	121047101
	.word	37943074
	.word	18877215
	.word	87359031
	.word	-29163447
	.word	-128385024
	.word	0
	.word	-62455750
	.word	121438208
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	4915784
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-12126392
	.word	238813184
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	204475185
	.word	439156736
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-46858172
	.word	-112527528
	.word	53741316
	.word	168300808
	.word	269681445
	.word	-12715191
	.word	-12125106
	.word	0
	.word	153686553
	.word	153093419
	.word	154075180
	.word	3342894
	.word	321322050
	.word	254151722
	.word	153223257
	.word	0
	.word	237179423
	.word	287511838
	.word	288166954
	.word	304945946
	.word	271976258
	.word	272108361
	.word	172226164
	.word	0
	.word	270860335
	.word	304286501
	.word	204016169
	.word	36703273
	.word	220790843
	.word	53613352
	.word	54661682
	.word	0
	.word	370546454
	.word	454369556
	.word	438050328
	.word	455217706
	.word	421990962
	.word	205919542
	.word	239536979
	.word	0
	.word	0
	.word	0
	.word	-79233000
	.word	-14352854
	.word	-30083271
	.word	-96469951
	.word	-62654126
	.word	0
	.word	-78251439
	.word	-162662063
	.word	-279908791
	.word	-62196141
	.word	-146278589
	.word	-12715966
	.word	-230555589
	.word	37421056
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-44958388
	.word	-112657842
	.word	-196545980
	.word	-45680052
	.word	-79496386
	.word	3800125
	.word	-147062474
	.word	37355520
	.word	301342963
	.word	720843259
	.word	889208835
	.word	1141522971
	.word	792264704
	.word	0
	.word	0
	.word	0
	.word	-595595429
	.word	-228595884
	.word	-413731751
	.word	-279191169
	.word	-229839257
	.word	-212149377
	.word	0
	.word	0
	.word	189793612
	.word	39060814
	.word	-395056558
	.word	-146931659
	.word	3928661
	.word	-212208802
	.word	-178461825
	.word	0
	.word	-61410216
	.word	-78447288
	.word	-62654392
	.word	-262539451
	.word	-12909246
	.word	70908999
	.word	-28900806
	.word	-11927552
	.word	69664810
	.word	119671581
	.word	136250917
	.word	120193832
	.word	136383787
	.word	220464175
	.word	53936698
	.word	104595456
	.word	-360716417
	.word	-411507329
	.word	-311236235
	.word	-411638155
	.word	-395189130
	.word	-512173188
	.word	-161549978
	.word	-161284096
	.word	301142263
	.word	301210603
	.word	635578840
	.word	718745809
	.word	669003480
	.word	885862103
	.word	886647789
	.word	537591808
	.word	-97057731
	.word	-229385345
	.word	-345705927
	.word	-196872889
	.word	-162665643
	.word	-262608536
	.word	-245179521
	.word	0
	.word	-64159931
	.word	4127027
	.word	-63964630
	.word	-47580619
	.word	139261774
	.word	-179107532
	.word	4455258
	.word	0
	.word	137104172
	.word	237635376
	.word	70779956
	.word	220530993
	.word	322570800
	.word	204275781
	.word	337709119
	.word	0
	.word	-211104129
	.word	-77852359
	.word	-78187682
	.word	-195297715
	.word	4718409
	.word	71366993
	.word	88084281
	.word	0
	.word	1036597458
	.word	1053708733
	.word	770450430
	.word	470753793
	.word	654384657
	.word	338039341
	.word	255197263
	.word	0
	.word	-78645912
	.word	-178527617
	.word	-162334672
	.word	-130156478
	.word	-112790965
	.word	-162531501
	.word	-195236244
	.word	0
	.word	21229896
	.word	-78907312
	.word	-346821824
	.word	-216012992
	.word	-480376501
	.word	289405002
	.word	-81527269
	.word	224067584
	.word	602808807
	.word	486348810
	.word	452993778
	.word	886319080
	.word	319889177
	.word	605886497
	.word	571416084
	.word	373882880
	.word	21168196
	.word	-163380924
	.word	5046848
	.word	4520782
	.word	121046331
	.word	37817910
	.word	254543164
	.word	38141952
	.word	619718130
	.word	636428289
	.word	571415823
	.word	404300310
	.word	521151250
	.word	521937193
	.word	605821743
	.word	356384768
	.word	4324943
	.word	4783196
	.word	-61871547
	.word	-263455174
	.word	20640590
	.word	-145490863
	.word	-211615744
	.word	0
	.word	54655301
	.word	139264000
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	337777439
	.word	455868416
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-28512682
	.word	205914112
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	304026394
	.word	605552640
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	-96992444
	.word	-129502366
	.word	-212731354
	.word	-213976518
	.word	-29626295
	.word	-162729130
	.word	-145492393
	.word	0
	.word	-163445954
	.word	-45814703
	.word	1966343
	.word	-48764086
	.word	272820604
	.word	287649006
	.word	853469823
	.word	0
	.word	319819556
	.word	254022940
	.word	420814356
	.word	520887056
	.word	405405789
	.word	238554937
	.word	438757503
	.word	0
	.word	88142918
	.word	188155192
	.word	4522561
	.word	-95812298
	.word	121043532
	.word	-179110323
	.word	-28501718
	.word	0
	.word	404167440
	.word	404627229
	.word	371791402
	.word	272371508
	.word	238814030
	.word	-260369099
	.word	372775229
	.word	0
	.word	0
	.word	0
	.word	-146278107
	.word	-131271375
	.word	-164039621
	.word	-130025661
	.word	-96143793
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.word	-45156278
	.word	-146213304
	.word	-297012153
	.word	-180356282
	.word	-280235448
	.word	-263981003
	.word	-230951116
	.word	-180092928
	.word	167649014
	.word	536617471
	.word	554114828
	.word	622272294
	.word	339738624
	.word	0
	.word	0
	.word	0
	.type	CalcZeroNum, %object
	.size	CalcZeroNum, 256
CalcZeroNum:
	.byte	8
	.byte	7
	.byte	6
	.byte	6
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.type	g_AspecRatioIdc, %object
	.size	g_AspecRatioIdc, 112
g_AspecRatioIdc:
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"list[%d][%d]: frame_num=%d, poc=%d\012\000" )
.LC1:
	ASCII(.ascii	"L0: \000" )
	.space	3
.LC2:
	ASCII(.ascii	"\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"%d \000" )
.LC4:
	ASCII(.ascii	"%dt \000" )
	.space	3
.LC5:
	ASCII(.ascii	"%db \000" )
	.space	3
.LC6:
	ASCII(.ascii	"L1:\000" )
.LC7:
	ASCII(.ascii	"\012\012END of the bit buffer, copy the first packe" )
	ASCII(.ascii	"t!\012\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"0:phy:0x%x, 1:phy:0x%x; len0:%d len1:%d\012\000" )
	.space	3
.LC9:
	ASCII(.ascii	"0:phy:0x%x, len0:%d\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"%-50s%50d\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"%s DPB.fs[%d] = NULL\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"frame %d, state=%d, is already output\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"plfs(fs=%p, eFoState=%d) is null, logic_fs_id = %d\012" )
	ASCII(.ascii	"\000" )
.LC14:
	ASCII(.ascii	"not used frame: (%d,%d)\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"frame skip: is_used=%d,skip=%d\012\000" )
.LC16:
	ASCII(.ascii	"topfield skip: is_used=%d,skip=%d\012\000" )
	.space	1
.LC17:
	ASCII(.ascii	"bottom field skip: is_used=%d,skip=%d\012\000" )
	.space	1
.LC18:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC19:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC20:
	ASCII(.ascii	"stream frame packing type is %d! what can we do?\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC21:
	ASCII(.ascii	"../../core/syntax/h264.c\000" )
	.space	3
.LC22:
	ASCII(.ascii	"NULL pointer: %s, L%d\012\000" )
	.space	1
.LC23:
	ASCII(.ascii	"framestore %d allocate apc %d\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"find APC, but logic_fs_id %d abnormal(ref=%d,plfs=%" )
	ASCII(.ascii	"p, pdfs=%p)\012\000" )
.LC25:
	ASCII(.ascii	"pH264Ctx->DPB.fs[%d]: frame_num=%d poc=%d is_refere" )
	ASCII(.ascii	"nce=%d\012\000" )
	.space	1
.LC26:
	ASCII(.ascii	"pH264Ctx->DPB.fs_ref[%d]: frame_num=%d poc=%d is_re" )
	ASCII(.ascii	"ference=%d\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"pH264Ctx->DPB.fs_ref[%d]: frame.poc=%d \012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"\012 VFMW ** release streambuff=%p   bitstream_leng" )
	ASCII(.ascii	"th=%d\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"clear curr slice.\012\000" )
	.space	1
.LC30:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC31:
	ASCII(.ascii	"resolution error, ImageWidth=%d, ImageHeight=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC32:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC34:
	ASCII(.ascii	"slice_type %d invalid, clear current slice.\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"pRepairPic(%p)/found(%d) = 0, clear current slice.\012" )
	ASCII(.ascii	"\000" )
.LC36:
	ASCII(.ascii	"listXsize[%d] = %d, clear current slice.\012\000" )
	.space	2
.LC37:
	ASCII(.ascii	"for P slice size of list equal 0.\012\000" )
	.space	1
.LC38:
	ASCII(.ascii	"for B slice size of two list all equal 0.\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"init list error.\012\000" )
	.space	2
.LC40:
	ASCII(.ascii	"L0: list after init.\012\000" )
	.space	2
.LC41:
	ASCII(.ascii	"L0: list after reorder.\012\000" )
	.space	3
.LC42:
	ASCII(.ascii	"save pic yuv :  structure = %d;  idc = %d\012\000" )
	.space	1
.LC43:
	ASCII(.ascii	"structure = %d pH264Ctx->CurrPic.pic_width_in_mb = " )
	ASCII(.ascii	"%d pH264Ctx->CurrPic.pic_height_in_mb = %d\012\000" )
	.space	1
.LC44:
	ASCII(.ascii	"nal_ref_idc=%d, structure=%d, image_id=%d, pmv_idc=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"logic frame id(=%d): get LogicFs error!\012\000" )
	.space	3
.LC46:
	ASCII(.ascii	"phy fs is null: pstDecodeFs = %p, pstDispOutFs = %p" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"line: %d pstLogicFs is null\012\000" )
	.space	3
.LC48:
	ASCII(.ascii	"SH: first_mb_in_slice\000" )
	.space	2
.LC49:
	ASCII(.ascii	"slicecheck first_mb_in_slice >= MAX_MB_NUM_IN_PIC e" )
	ASCII(.ascii	"rror.\012\000" )
	.space	2
.LC50:
	ASCII(.ascii	"SH: slice_type\000" )
	.space	1
.LC51:
	ASCII(.ascii	"slice type = %d\012\000" )
	.space	3
.LC52:
	ASCII(.ascii	"slice type = %d, err\012\000" )
	.space	2
.LC53:
	ASCII(.ascii	"slice  pps id = %d\012\000" )
.LC54:
	ASCII(.ascii	"pps with this pic_parameter_set_id = %d havn't deco" )
	ASCII(.ascii	"de\012\000" )
	.space	1
.LC55:
	ASCII(.ascii	"sps with this pic_parameter_set_id = %d havn't deco" )
	ASCII(.ascii	"de\012\000" )
	.space	1
.LC56:
	ASCII(.ascii	"tmp slice  pps id = %d\012\000" )
.LC57:
	ASCII(.ascii	"PPSSPSCheckTmpId: pps with this pic_parameter_set_i" )
	ASCII(.ascii	"d = %d havn't decode\012\000" )
	.space	3
.LC58:
	ASCII(.ascii	"PPSSPSCheckTmpId: seq_parameter_set_id out of range" )
	ASCII(.ascii	".\012\000" )
	.space	2
.LC59:
	ASCII(.ascii	"PPSSPSCheckTmpId: sps with this pic_parameter_set_i" )
	ASCII(.ascii	"d = %d havn't decode\012\000" )
	.space	3
.LC60:
	ASCII(.ascii	"new pic flag = %d\012\000" )
	.space	1
.LC61:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l0\000" )
.LC62:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l0\000" )
	.space	2
.LC63:
	ASCII(.ascii	"reorder idc l0 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC64:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l0\000" )
	.space	1
.LC65:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l0 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC66:
	ASCII(.ascii	"SH: long_term_pic_idx_l0\000" )
	.space	3
.LC67:
	ASCII(.ascii	"num of idc l0 exceed\012\000" )
	.space	2
.LC68:
	ASCII(.ascii	"SH: ref_pic_list_reordering_flag_l1\000" )
.LC69:
	ASCII(.ascii	"SH: reordering_of_pic_nums_idc_l1\000" )
	.space	2
.LC70:
	ASCII(.ascii	"reorder idc l1 = %d, g_SeErrFlag=%d\012\000" )
	.space	3
.LC71:
	ASCII(.ascii	"SH: abs_diff_pic_num_minus1_l1\000" )
	.space	1
.LC72:
	ASCII(.ascii	"abs_diff_pic_num_minus1_l1 = %d, g_SeErrFlag=%d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC73:
	ASCII(.ascii	"SH: long_term_pic_idx_l1\000" )
	.space	3
.LC74:
	ASCII(.ascii	"num of idc l1 exceed\012\000" )
	.space	2
.LC75:
	ASCII(.ascii	"SH: luma_log2_weight_denom\000" )
	.space	1
.LC76:
	ASCII(.ascii	"SH: chroma_log2_weight_denom\000" )
	.space	3
.LC77:
	ASCII(.ascii	"WP log2 exceed  and err flag = %d\012\000" )
	.space	1
.LC78:
	ASCII(.ascii	"SH: luma_weight_flag_l0\000" )
.LC79:
	ASCII(.ascii	"SH: luma_weight_l0\000" )
	.space	1
.LC80:
	ASCII(.ascii	"SH: luma_offset_l0\000" )
	.space	1
.LC81:
	ASCII(.ascii	"SH: chroma_weight_flag_l0\000" )
	.space	2
.LC82:
	ASCII(.ascii	"SH: chroma_weight_l0\000" )
	.space	3
.LC83:
	ASCII(.ascii	"SH: chroma_offset_l0\000" )
	.space	3
.LC84:
	ASCII(.ascii	"SH: luma_weight_flag_l1\000" )
.LC85:
	ASCII(.ascii	"SH: luma_weight_l1\000" )
	.space	1
.LC86:
	ASCII(.ascii	"SH: luma_offset_l1\000" )
	.space	1
.LC87:
	ASCII(.ascii	"SH: chroma_weight_flag_l1\000" )
	.space	2
.LC88:
	ASCII(.ascii	"SH: chroma_weight_l1\000" )
	.space	3
.LC89:
	ASCII(.ascii	"SH: chroma_offset_l1\000" )
	.space	3
.LC90:
	ASCII(.ascii	"overflow MAX_MMCO_LEN\012\000" )
	.space	1
.LC91:
	ASCII(.ascii	"SH: memory_management_control_operation\000" )
.LC92:
	ASCII(.ascii	"SH: difference_of_pic_nums_minus1\000" )
	.space	2
.LC93:
	ASCII(.ascii	"SH: long_term_pic_num\000" )
	.space	2
.LC94:
	ASCII(.ascii	"SH: long_term_frame_idx\000" )
.LC95:
	ASCII(.ascii	"SH: max_long_term_frame_idx_plus1\000" )
	.space	2
.LC96:
	ASCII(.ascii	"mmco exceed 6\012\000" )
	.space	1
.LC97:
	ASCII(.ascii	"SH: no_output_of_prior_pics_flag\000" )
	.space	3
.LC98:
	ASCII(.ascii	"SH: long_term_reference_flag\000" )
	.space	3
.LC99:
	ASCII(.ascii	"IDR and no_output_of_prior_pics_flag = %d\012\000" )
	.space	1
.LC100:
	ASCII(.ascii	"SH: adaptive_ref_pic_marking_mode_flag\000" )
	.space	1
.LC101:
	ASCII(.ascii	"adaptive_ref_pic_marking_mode_flag = %d\012\000" )
	.space	3
.LC102:
	ASCII(.ascii	"MMCO para would save dec err\012\000" )
	.space	2
.LC103:
	ASCII(.ascii	"mulitislice diff no_out_of_prior_pics_flag, used fi" )
	ASCII(.ascii	"rst.\012\000" )
	.space	3
.LC104:
	ASCII(.ascii	"mulitislice diff long_term_reference_flag, used fir" )
	ASCII(.ascii	"st.\012\000" )
.LC105:
	ASCII(.ascii	"mulitislice diff adaptive_ref_pic_marking_mode_flag" )
	ASCII(.ascii	", used first.\012\000" )
	.space	2
.LC106:
	ASCII(.ascii	"TotalPicNum=%d, SliceNumInPic=%d, TotalNal=%d\012\000" )
	.space	1
.LC107:
	ASCII(.ascii	"SH: pic_parameter_set_id\000" )
	.space	3
.LC108:
	ASCII(.ascii	"pps id:%d in sliceheader err\012\000" )
	.space	2
.LC109:
	ASCII(.ascii	"PPS or SPS of this slice not valid\012\000" )
.LC110:
	ASCII(.ascii	"recover point but isn't I_SLICE.\012\000" )
	.space	2
.LC111:
	ASCII(.ascii	"SH: frame_num\000" )
	.space	2
.LC112:
	ASCII(.ascii	"IDR NAL but frame_num!=0.\012\000" )
	.space	1
.LC113:
	ASCII(.ascii	"SH: field_pic_flag\000" )
	.space	1
.LC114:
	ASCII(.ascii	"SH: bottom_field_flag\000" )
	.space	2
.LC115:
	ASCII(.ascii	"field first_mb_in_slice bigger than pic size\012\000" )
	.space	2
.LC116:
	ASCII(.ascii	"frame first_mb_in_slice bigger than pic size\012\000" )
	.space	2
.LC117:
	ASCII(.ascii	"SH: idr_pic_id\000" )
	.space	1
.LC118:
	ASCII(.ascii	"idr_pic_id bigger than 65535\012\000" )
	.space	2
.LC119:
	ASCII(.ascii	"SH: pic_order_cnt_lsb\000" )
	.space	2
.LC120:
	ASCII(.ascii	"SH: delta_pic_order_cnt_bottom\000" )
	.space	1
.LC121:
	ASCII(.ascii	"SH: delta_pic_order_cnt[0]\000" )
	.space	1
.LC122:
	ASCII(.ascii	"SH: delta_pic_order_cnt[1]\000" )
	.space	1
.LC123:
	ASCII(.ascii	"SH: redundant_pic_cnt\000" )
	.space	2
.LC124:
	ASCII(.ascii	"redundant pic not support.\012\000" )
.LC125:
	ASCII(.ascii	"first_mb_in_slice in currslice small than prevslice" )
	ASCII(.ascii	" in same pic\012\000" )
	.space	3
.LC126:
	ASCII(.ascii	"SH: direct_spatial_mv_pred_flag\000" )
.LC127:
	ASCII(.ascii	"SH: num_ref_idx_override_flag\000" )
	.space	2
.LC128:
	ASCII(.ascii	"SH: num_ref_idx_l0_active_minus1\000" )
	.space	3
.LC129:
	ASCII(.ascii	"SH: num_ref_idx_l1_active_minus1\000" )
	.space	3
.LC130:
	ASCII(.ascii	"frame num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC131:
	ASCII(.ascii	"field num_ref_idx_lx_active_minus1 exceed\012\000" )
	.space	1
.LC132:
	ASCII(.ascii	"reordering para dec err\012\000" )
	.space	3
.LC133:
	ASCII(.ascii	"apply_weights_flag=%d\012\000" )
	.space	1
.LC134:
	ASCII(.ascii	"wpt dec err\012\000" )
	.space	3
.LC135:
	ASCII(.ascii	"mark para dec err\012\000" )
	.space	1
.LC136:
	ASCII(.ascii	"SH: cabac_init_idc\000" )
	.space	1
.LC137:
	ASCII(.ascii	"cabac_init_idc bigger than 3\012\000" )
	.space	2
.LC138:
	ASCII(.ascii	"SH: slice_qp_delta\000" )
	.space	1
.LC139:
	ASCII(.ascii	"SH: disable_deblocking_filter_idc\000" )
	.space	2
.LC140:
	ASCII(.ascii	"disable_deblocking_filter_idc dec err\012\000" )
	.space	1
.LC141:
	ASCII(.ascii	"SH: slice_alpha_c0_offset_div2\000" )
	.space	1
.LC142:
	ASCII(.ascii	"slice_alpha_c0_offset_div2 dec err\012\000" )
.LC143:
	ASCII(.ascii	"SH: slice_beta_offset_div2\000" )
	.space	1
.LC144:
	ASCII(.ascii	"slice_beta_offset_div2 dec err\012\000" )
.LC145:
	ASCII(.ascii	"pH264Ctx->pCurrNal->nal_bitoffset = %d; code_len_by" )
	ASCII(.ascii	"te = %d; bitstream_length = %d; pH264Ctx->pCurrNal-" )
	ASCII(.ascii	">nal_trail_zero_bit_num = %d\012\000" )
.LC146:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d; byt" )
	ASCII(.ascii	"espos = %x\012\000" )
	.space	1
.LC147:
	ASCII(.ascii	"nal_segment = %d is not expected value\012\000" )
.LC148:
	ASCII(.ascii	"stream[%d]: bitsoffset = %d; valid_bitlen = %d\012\000" )
.LC149:
	ASCII(.ascii	"   : delta_sl   \000" )
	.space	3
.LC150:
	ASCII(.ascii	"PPS: entropy_coding_mode_flag\000" )
	.space	2
.LC151:
	ASCII(.ascii	"PPS: pic_order_present_flag\000" )
.LC152:
	ASCII(.ascii	"PPS: num_slice_groups_minus1\000" )
	.space	3
.LC153:
	ASCII(.ascii	"Baseline stream with FMO, not support.\012\000" )
.LC154:
	ASCII(.ascii	"PPS: num_ref_idx_l0_active_minus1\000" )
	.space	2
.LC155:
	ASCII(.ascii	"num_ref_idx_l0_active_minus1 out of range.\012\000" )
.LC156:
	ASCII(.ascii	"PPS: num_ref_idx_l1_active_minus1\000" )
	.space	2
.LC157:
	ASCII(.ascii	"num_ref_idx_l1_active_minus1 out of range.\012\000" )
.LC158:
	ASCII(.ascii	"PPS: weighted prediction flag\000" )
	.space	2
.LC159:
	ASCII(.ascii	"PPS: weighted_bipred_idc\000" )
	.space	3
.LC160:
	ASCII(.ascii	"weighted_bipred_idc out of range\012\000" )
	.space	2
.LC161:
	ASCII(.ascii	"PPS: pic_init_qp_minus26\000" )
	.space	3
.LC162:
	ASCII(.ascii	"PPS: pic_init_qs_minus26\000" )
	.space	3
.LC163:
	ASCII(.ascii	"PPS: chroma_qp_index_offset\000" )
.LC164:
	ASCII(.ascii	"PPS: deblocking_filter_control_present_flag\000" )
.LC165:
	ASCII(.ascii	"PPS: constrained_intra_pred_flag\000" )
	.space	3
.LC166:
	ASCII(.ascii	"PPS: redundant_pic_cnt_present_flag\000" )
.LC167:
	ASCII(.ascii	"redundant pic not support when find redundant slice" )
	ASCII(.ascii	" later, exit\012\000" )
	.space	3
.LC168:
	ASCII(.ascii	"PPS: transform_8x8_mode_flag\000" )
	.space	3
.LC169:
	ASCII(.ascii	"PPS: pic_scaling_matrix_present_flag\000" )
	.space	3
.LC170:
	ASCII(.ascii	"PPS: second_chroma_qp_index_offset\000" )
	.space	1
.LC171:
	ASCII(.ascii	"SPS: seq_scaling_list_present_flag\000" )
	.space	1
.LC172:
	ASCII(.ascii	"PPS: pic_scaling_list_present_flag\000" )
	.space	1
.LC173:
	ASCII(.ascii	"second_chroma_qp_index_offset out of range.\012\000" )
	.space	3
.LC174:
	ASCII(.ascii	"PPS: pic_parameter_set_id\000" )
	.space	2
.LC175:
	ASCII(.ascii	"pic_parameter_set_id out of range.\012\000" )
.LC176:
	ASCII(.ascii	"PPS: seq_parameter_set_id\000" )
	.space	2
.LC177:
	ASCII(.ascii	"seq_parameter_set_id out of range.\012\000" )
.LC178:
	ASCII(.ascii	"SPS haven't decode.\012\000" )
	.space	3
.LC179:
	ASCII(.ascii	"%s: PPS decode error 1.\012\000" )
	.space	3
.LC180:
	ASCII(.ascii	"%s: PPS decode error 2.\012\000" )
	.space	3
.LC181:
	ASCII(.ascii	"VUI: aspect_ratio_info_present_flag\000" )
.LC182:
	ASCII(.ascii	"VUI: aspect_ratio_idc\000" )
	.space	2
.LC183:
	ASCII(.ascii	"VUI: sar_width\000" )
	.space	1
.LC184:
	ASCII(.ascii	"VUI: sar_height\000" )
.LC185:
	ASCII(.ascii	"VUI: overscan_info_present_flag\000" )
.LC186:
	ASCII(.ascii	"VUI: overscan_appropriate_flag\000" )
	.space	1
.LC187:
	ASCII(.ascii	"VUI: video_signal_type_present_flag\000" )
.LC188:
	ASCII(.ascii	"VUI: video_format\000" )
	.space	2
.LC189:
	ASCII(.ascii	"VUI: video_full_range_flag\000" )
	.space	1
.LC190:
	ASCII(.ascii	"VUI: color_description_present_flag\000" )
.LC191:
	ASCII(.ascii	"VUI: colour_primaries\000" )
	.space	2
.LC192:
	ASCII(.ascii	"VUI: transfer_characteristics\000" )
	.space	2
.LC193:
	ASCII(.ascii	"VUI: matrix_coefficients\000" )
	.space	3
.LC194:
	ASCII(.ascii	"VUI: chroma_loc_info_present_flag\000" )
	.space	2
.LC195:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_top_field\000" )
	.space	2
.LC196:
	ASCII(.ascii	"VUI: chroma_sample_loc_type_bottom_field\000" )
	.space	3
.LC197:
	ASCII(.ascii	"VUI: timing_info_present_flag\000" )
	.space	2
.LC198:
	ASCII(.ascii	"VUI: num_units_in_tick\000" )
	.space	1
.LC199:
	ASCII(.ascii	"VUI: time_scale\000" )
.LC200:
	ASCII(.ascii	"VUI: fixed_frame_rate_flag\000" )
	.space	1
.LC201:
	ASCII(.ascii	"VUI: nal_hrd_parameters_present_flag\000" )
	.space	3
.LC202:
	ASCII(.ascii	"VUI: cpb_cnt_minus1\000" )
.LC203:
	ASCII(.ascii	"VUI: bit_rate_scale\000" )
.LC204:
	ASCII(.ascii	"VUI: cpb_size_scale\000" )
.LC205:
	ASCII(.ascii	"hrd->cpb_cnt_minus1 out of range\012\000" )
	.space	2
.LC206:
	ASCII(.ascii	"VUI: bit_rate_value_minus1\000" )
	.space	1
.LC207:
	ASCII(.ascii	"VUI: cpb_size_value_minus1\000" )
	.space	1
.LC208:
	ASCII(.ascii	"VUI: cbr_flag\000" )
	.space	2
.LC209:
	ASCII(.ascii	"VUI: initial_cpb_removal_delay_length_minus1\000" )
	.space	3
.LC210:
	ASCII(.ascii	"VUI: cpb_removal_delay_length_minus1\000" )
	.space	3
.LC211:
	ASCII(.ascii	"VUI: dpb_output_delay_length_minus1\000" )
.LC212:
	ASCII(.ascii	"VUI: time_offset_length\000" )
.LC213:
	ASCII(.ascii	"VUI: vcl_hrd_parameters_present_flag\000" )
	.space	3
.LC214:
	ASCII(.ascii	"VUI: low_delay_hrd_flag\000" )
.LC215:
	ASCII(.ascii	"VUI: pic_struct_present_flag\000" )
	.space	3
.LC216:
	ASCII(.ascii	"VUI: bitstream_restriction_flag\000" )
.LC217:
	ASCII(.ascii	"VUI: motion_vectors_over_pic_boundaries_flag\000" )
	.space	3
.LC218:
	ASCII(.ascii	"VUI: max_bytes_per_pic_denom\000" )
	.space	3
.LC219:
	ASCII(.ascii	"VUI: max_bits_per_mb_denom\000" )
	.space	1
.LC220:
	ASCII(.ascii	"VUI: log2_max_mv_length_horizontal\000" )
	.space	1
.LC221:
	ASCII(.ascii	"VUI: log2_max_mv_length_vertical\000" )
	.space	3
.LC222:
	ASCII(.ascii	"VUI: num_reorder_frames\000" )
.LC223:
	ASCII(.ascii	"VUI: max_dec_frame_buffering\000" )
	.space	3
.LC224:
	ASCII(.ascii	"dar=%d, final_dar=%d\012\000" )
	.space	2
.LC225:
	ASCII(.ascii	"SPS: chroma_format_idc\000" )
	.space	1
.LC226:
	ASCII(.ascii	"pSPS->chroma_format_idc = %d out of range.\012\000" )
.LC227:
	ASCII(.ascii	"SPS: bit_depth_luma_minus8\000" )
	.space	1
.LC228:
	ASCII(.ascii	"bit_depth_luma(%d) not equal 8.\012\000" )
	.space	3
.LC229:
	ASCII(.ascii	"SPS: bit_depth_chroma_minus8\000" )
	.space	3
.LC230:
	ASCII(.ascii	"bit_depth_chroma(%d) not equal 8.\012\000" )
	.space	1
.LC231:
	ASCII(.ascii	"SPS: qpprime_y_zero_trans_bypass_flag\000" )
	.space	2
.LC232:
	ASCII(.ascii	"qpprime_y_zero_trans_bypass_flag not equal 0.\012\000" )
	.space	1
.LC233:
	ASCII(.ascii	"SPS: seq_scaling_matrix_present_flag\000" )
	.space	3
.LC234:
	ASCII(.ascii	"SPS: log2_max_frame_num_minus4\000" )
	.space	1
.LC235:
	ASCII(.ascii	"pSPS->log2_max_frame_num_minus4 out of range.\012\000" )
	.space	1
.LC236:
	ASCII(.ascii	"SPS: pic_order_cnt_type\000" )
.LC237:
	ASCII(.ascii	"pSPS->pic_order_cnt_type out of range.\012\000" )
.LC238:
	ASCII(.ascii	"SPS: log2_max_pic_order_cnt_lsb_minus4\000" )
	.space	1
.LC239:
	ASCII(.ascii	"SPS: num_ref_frames\000" )
.LC240:
	ASCII(.ascii	"pSPS->log2_max_pic_order_cnt_lsb_minus4 out of rang" )
	ASCII(.ascii	"e.\012\000" )
	.space	1
.LC241:
	ASCII(.ascii	"SPS: delta_pic_order_always_zero_flag\000" )
	.space	2
.LC242:
	ASCII(.ascii	"SPS: offset_for_non_ref_pic\000" )
.LC243:
	ASCII(.ascii	"SPS: offset_for_top_to_bottom_field\000" )
.LC244:
	ASCII(.ascii	"SPS: num_ref_frames_in_pic_order_cnt_cycle\000" )
	.space	1
.LC245:
	ASCII(.ascii	"pSPS->num_ref_frames_in_pic_order_cnt_cycle out of " )
	ASCII(.ascii	"range.\012\000" )
	.space	1
.LC246:
	ASCII(.ascii	"SPS: offset_for_ref_frame[i]\000" )
	.space	3
.LC247:
	ASCII(.ascii	"SPS: gaps_in_frame_num_value_allowed_flag\000" )
	.space	2
.LC248:
	ASCII(.ascii	"SPS: pic_width_in_mbs_minus1\000" )
	.space	3
.LC249:
	ASCII(.ascii	"pSPS->pic_width_in_mbs_minus1 out of range(=%d).\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC250:
	ASCII(.ascii	"SPS: pic_height_in_map_units_minus1\000" )
.LC251:
	ASCII(.ascii	"SPS: frame_mbs_only_flag\000" )
	.space	3
.LC252:
	ASCII(.ascii	"pSPS->pic_height_in_map_units_minus1 out of range.\012" )
	ASCII(.ascii	"\000" )
.LC253:
	ASCII(.ascii	"pic size too large.\012\000" )
	.space	3
.LC254:
	ASCII(.ascii	"level_idc %d not support.\012\000" )
	.space	1
.LC255:
	ASCII(.ascii	"dpb size according level : %d\012\000" )
	.space	1
.LC256:
	ASCII(.ascii	"pSPS->num_ref_frames(%d) > DPB size(%d), try to sel" )
	ASCII(.ascii	"ect the reasonable one.\012\000" )
.LC257:
	ASCII(.ascii	"SPS: direct_8x8_inference_flag\000" )
	.space	1
.LC258:
	ASCII(.ascii	"SPS: frame_cropping_flag\000" )
	.space	3
.LC259:
	ASCII(.ascii	"SPS: frame_cropping_rect_left_offset\000" )
	.space	3
.LC260:
	ASCII(.ascii	"SPS: frame_cropping_rect_right_offset\000" )
	.space	2
.LC261:
	ASCII(.ascii	"SPS: frame_cropping_rect_top_offset\000" )
.LC262:
	ASCII(.ascii	"SPS: frame_cropping_rect_bottom_offset\000" )
	.space	1
.LC263:
	ASCII(.ascii	"SPS: vui_parameters_present_flag\000" )
	.space	3
.LC264:
	ASCII(.ascii	"max_dec_frame_buffering(%d) > MaxDpbSize(%d)\012\000" )
	.space	2
.LC265:
	ASCII(.ascii	"SPS: mb_adaptive_frame_field_flag\000" )
	.space	2
.LC266:
	ASCII(.ascii	"SPS_SVC_EXT: inter_layer_deblocking_filter_control_" )
	ASCII(.ascii	"present_flag\000" )
.LC267:
	ASCII(.ascii	"inter_layer_present_flag:%d!\012\000" )
	.space	2
.LC268:
	ASCII(.ascii	"SPS_SVC_EXT: extended_spatial_scalability_idc\000" )
	.space	2
.LC269:
	ASCII(.ascii	"spatial scalability not support!!\012\000" )
	.space	1
.LC270:
	ASCII(.ascii	"SPS_SVC_EXT: chroma_phase_x_plus1_flag\000" )
	.space	1
.LC271:
	ASCII(.ascii	"chroma_phase_x_plus1_flag:%d!!\012\000" )
.LC272:
	ASCII(.ascii	"SPS_SVC_EXT: chroma_phase_y_plus1\000" )
	.space	2
.LC273:
	ASCII(.ascii	"chroma_phase_y_plus1:%d!\012\000" )
	.space	2
.LC274:
	ASCII(.ascii	"SPS_SVC_EXT: seq_tcoeff_level_prediction_flag\000" )
	.space	2
.LC275:
	ASCII(.ascii	"SPS_SVC_EXT: adaptive_tcoeff_level_prediction_flag\000" )
	.space	1
.LC276:
	ASCII(.ascii	"adaptive_tcoeff_level_prediction_flag:%d!\012\000" )
	.space	1
.LC277:
	ASCII(.ascii	"SPS_SVC_EXT: slice_header_restriction_flag\000" )
	.space	1
.LC278:
	ASCII(.ascii	"slice_header_restriction_flag error:%d,%x,%d\012\000" )
	.space	2
.LC279:
	ASCII(.ascii	"SPS: profile_idc\000" )
	.space	3
.LC280:
	ASCII(.ascii	"SPS: constrained_set0_flag\000" )
	.space	1
.LC281:
	ASCII(.ascii	"SPS: constrained_set1_flag\000" )
	.space	1
.LC282:
	ASCII(.ascii	"SPS: constrained_set2_flag\000" )
	.space	1
.LC283:
	ASCII(.ascii	"SPS: constrained_set3_flag\000" )
	.space	1
.LC284:
	ASCII(.ascii	"SPS: reserved_zero_4bits\000" )
	.space	3
.LC285:
	ASCII(.ascii	"SPS: level_idc\000" )
	.space	1
.LC286:
	ASCII(.ascii	"SPS: seq_parameter_set_id\000" )
	.space	2
.LC287:
	ASCII(.ascii	"Baseline stream, try to decode, exit when FMO occur" )
	ASCII(.ascii	"red.\012\000" )
	.space	3
.LC288:
	ASCII(.ascii	"EXTENDED stream, try to decode, exit when dataparti" )
	ASCII(.ascii	"tion occurred.\012\000" )
	.space	1
.LC289:
	ASCII(.ascii	"others High profile stream, try to decode, exit whe" )
	ASCII(.ascii	"n high profile not support occurred.\012\000" )
	.space	3
.LC290:
	ASCII(.ascii	"profile_idc = %5d error, try to decode as main prof" )
	ASCII(.ascii	"ile.\012\000" )
	.space	3
.LC291:
	ASCII(.ascii	"level_idc = %5d error, try to decode as level_idc %" )
	ASCII(.ascii	"d.\012\000" )
	.space	1
.LC292:
	ASCII(.ascii	"Line %d: SPS[%d] decode error.\012\000" )
.LC293:
	ASCII(.ascii	"svc ext error:\012\000" )
.LC294:
	ASCII(.ascii	"SEI: frame_packing_arrangement_id\000" )
	.space	2
.LC295:
	ASCII(.ascii	"SEI: frame_packing_arrangement_cancel_flag\000" )
	.space	1
.LC296:
	ASCII(.ascii	"SEI: frame_packing_arrangement_type\000" )
.LC297:
	ASCII(.ascii	"SEI: quincunx_sampling_flag\000" )
.LC298:
	ASCII(.ascii	"SEI: content_interpretation_type\000" )
	.space	3
.LC299:
	ASCII(.ascii	"SEI: spatial_flipping_flag\000" )
	.space	1
.LC300:
	ASCII(.ascii	"SEI: frame0_flipped_flag\000" )
	.space	3
.LC301:
	ASCII(.ascii	"SEI: field_views_flag\000" )
	.space	2
.LC302:
	ASCII(.ascii	"SEI: current_frame_is_frame0_flag\000" )
	.space	2
.LC303:
	ASCII(.ascii	"SEI: frame0_self_contained_flag\000" )
.LC304:
	ASCII(.ascii	"SEI: frame1_self_contained_flag\000" )
.LC305:
	ASCII(.ascii	"SEI: frame0_grid_position_x\000" )
.LC306:
	ASCII(.ascii	"SEI: frame0_grid_position_y\000" )
.LC307:
	ASCII(.ascii	"SEI: frame1_grid_position_x\000" )
.LC308:
	ASCII(.ascii	"SEI: frame1_grid_position_y\000" )
.LC309:
	ASCII(.ascii	"SEI: frame_packing_arrangement_reserved_byte\000" )
	.space	3
.LC310:
	ASCII(.ascii	"SEI: frame_packing_arrangement_repetition_period\000" )
	.space	3
.LC311:
	ASCII(.ascii	"SEI: frame_packing_arrangement_extension_flag\000" )
	.space	2
.LC312:
	ASCII(.ascii	"DecPicTimingSEI but SPS is invalid.\012\000" )
	.space	3
.LC313:
	ASCII(.ascii	"SEI: cpb_removal_delay\000" )
	.space	1
.LC314:
	ASCII(.ascii	"SEI: dpb_output_delay\000" )
	.space	2
.LC315:
	ASCII(.ascii	"pic_struct\000" )
	.space	1
.LC316:
	ASCII(.ascii	"SEI nal dec payload type err\012\000" )
	.space	2
.LC317:
	ASCII(.ascii	"SEI nal dec payloadSize err\012\000" )
	.space	3
.LC318:
	ASCII(.ascii	"SEI_BUFFERING_PERIOD,offset = %d,payload_size = %d " )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC319:
	ASCII(.ascii	"PassBytes err [%s][%d]\012\000" )
.LC320:
	ASCII(.ascii	"SEI_PIC_TIMING,offset = %d,payload_size = %d \012\000" )
	.space	1
.LC321:
	ASCII(.ascii	"SEI_PAN_SCAN_RECT,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC322:
	ASCII(.ascii	"SEI_FILLER_PAYLOAD,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC323:
	ASCII(.ascii	"SEI_USER_DATA_REGISTERED_ITU_T_T35, offset = %d, pa" )
	ASCII(.ascii	"yload_size = %d \012\000" )
	.space	3
.LC324:
	ASCII(.ascii	"SEI_USER_DATA_UNREGISTERED, offset = %d, payload_si" )
	ASCII(.ascii	"ze = %d \012\000" )
	.space	3
.LC325:
	ASCII(.ascii	"SEI: itu_t_t35_country_code\000" )
.LC326:
	ASCII(.ascii	"SEI: itu_t_t35_country_code_extension_byte\000" )
	.space	1
.LC327:
	ASCII(.ascii	"SEI: itu_t_t35_provider_code\000" )
	.space	3
.LC328:
	ASCII(.ascii	"len_tmp = %d cann't dec usrdata\012\000" )
	.space	3
.LC329:
	ASCII(.ascii	"cann't dec usrdata\012\000" )
.LC330:
	ASCII(.ascii	"SEI_RECOVERY_POINT,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC331:
	ASCII(.ascii	"SEI_DEC_REF_PIC_MARKING_REPETITION,offset = %d,payl" )
	ASCII(.ascii	"oad_size = %d \012\000" )
	.space	1
.LC332:
	ASCII(.ascii	"SEI_SPARE_PIC,offset = %d,payload_size = %d \012\000" )
	.space	2
.LC333:
	ASCII(.ascii	"SEI_SCENE_INFO,offset = %d,payload_size = %d \012\000" )
	.space	1
.LC334:
	ASCII(.ascii	"SEI_SUB_SEQ_INFO,offset = %d,payload_size = %d \012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC335:
	ASCII(.ascii	"SEI_SUB_SEQ_LAYER_CHARACTERISTICS,offset = %d,paylo" )
	ASCII(.ascii	"ad_size = %d \012\000" )
	.space	2
.LC336:
	ASCII(.ascii	"SEI_SUB_SEQ_CHARACTERISTICS,offset = %d,payload_siz" )
	ASCII(.ascii	"e = %d \012\000" )
.LC337:
	ASCII(.ascii	"SEI_FULL_FRAME_FREEZE,offset = %d,payload_size = %d" )
	ASCII(.ascii	" \012\000" )
	.space	2
.LC338:
	ASCII(.ascii	"SEI_FULL_FRAME_FREEZE_RELEASE,offset = %d,payload_s" )
	ASCII(.ascii	"ize = %d \012\000" )
	.space	2
.LC339:
	ASCII(.ascii	"SEI_FULL_FRAME_SNAPSHOT,offset = %d,payload_size = " )
	ASCII(.ascii	"%d \012\000" )
.LC340:
	ASCII(.ascii	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_START,offset = %" )
	ASCII(.ascii	"d,payload_size = %d \012\000" )
	.space	3
.LC341:
	ASCII(.ascii	"SEI_PROGRESSIVE_REFINEMENT_SEGMENT_END,offset = %d," )
	ASCII(.ascii	"payload_size = %d \012\000" )
	.space	1
.LC342:
	ASCII(.ascii	"SEI_MOTION_CONSTRAINED_SLICE_GROUP_SET,offset = %d," )
	ASCII(.ascii	"payload_size = %d \012\000" )
	.space	1
.LC343:
	ASCII(.ascii	"SEI_FILM_GRAIN_CHARACTERISTICS,offset = %d,payload_" )
	ASCII(.ascii	"size = %d \012\000" )
	.space	1
.LC344:
	ASCII(.ascii	"SEI_DEBLOCKING_FILTER_DISPLAY_PREFERENCE,offset = %" )
	ASCII(.ascii	"d,payload_size = %d \012\000" )
	.space	3
.LC345:
	ASCII(.ascii	"SEI_STEREO_VIDEO_INFO,offset = %d,payload_size = %d" )
	ASCII(.ascii	" \012\000" )
	.space	2
.LC346:
	ASCII(.ascii	"too much usrdat, cann't dec SEI\012\000" )
	.space	3
.LC347:
	ASCII(.ascii	"\012the stream is error,len:%d\012\000" )
	.space	3
.LC348:
	ASCII(.ascii	"\012Slice nal or IDR nal = %d\012\000" )
.LC349:
	ASCII(.ascii	"sliceheader dec err\012\000" )
	.space	3
.LC350:
	ASCII(.ascii	"H264Dec destroy\012\000" )
	.space	3
.LC351:
	ASCII(.ascii	"H264 recycle image\012\000" )
.LC352:
	ASCII(.ascii	"pH264Ctx is %p, pFrameStore is %p\012\000" )
	.space	1
.LC353:
	ASCII(.ascii	"line; %d pstLogicFsImage is NULL!\012\000" )
	.space	1
.LC354:
	ASCII(.ascii	"InsertVO err:%d, ClearAll\012\000" )
	.space	1
.LC355:
	ASCII(.ascii	"H264.c line %d: frame para err(ret=%d), recycle ima" )
	ASCII(.ascii	"ge self\012\000" )
.LC356:
	ASCII(.ascii	"line: %d pstLogicFsImage is NULL!\012\000" )
	.space	1
.LC357:
	ASCII(.ascii	"[%s][%d] OutputFrmToVO return %d\012\000" )
	.space	2
.LC358:
	ASCII(.ascii	"line %d: flush dpb return %d\012\000" )
	.space	2
.LC359:
	ASCII(.ascii	"----------------- Imode -> %d ------------------\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC360:
	ASCII(.ascii	"I_MODE but first_mb_in_slice != 0\012\000" )
	.space	1
.LC361:
	ASCII(.ascii	"Discard this B(poc=%d) befor P, is_ref_idc=%d.\012\000" )
.LC362:
	ASCII(.ascii	"***** VDM start, TotalPicNum=%d, pH264Ctx->CurrPic." )
	ASCII(.ascii	"structure=%d.\012\000" )
	.space	2
.LC363:
	ASCII(.ascii	"DecVDM ERR\012\000" )
.LC364:
	ASCII(.ascii	"%s:%d Metadata map failed\012\000" )
	.space	1
.LC365:
	ASCII(.ascii	"%s:%d Metadata unmap failed\012\000" )
	.space	3
.LC366:
	ASCII(.ascii	"*****[%s][%d],EL Codec can only dec EL stream in DV" )
	ASCII(.ascii	"_DUAL_VES_IMP stream!!*****\012\000" )
.LC367:
	ASCII(.ascii	"***** VES Splitter: UNSUPPORT, HDR_capacity=%d*****" )
	ASCII(.ascii	"\012\000" )
	.space	3
.LC368:
	ASCII(.ascii	"\012 receive streambuff=%p; phy_addr=0x%x; bitstrea" )
	ASCII(.ascii	"m_length=%d\012\000" )
	.space	3
.LC369:
	ASCII(.ascii	"nal_release_err\012\000" )
	.space	3
.LC370:
	ASCII(.ascii	"cann't find slot for current nal\012\000" )
	.space	2
.LC371:
	ASCII(.ascii	"receive a zero packet\012\000" )
	.space	1
.LC372:
	ASCII(.ascii	"clear all dec para\012\000" )
.LC373:
	ASCII(.ascii	"[%s %d], pos is %d out of range\012\000" )
	.space	3
.LC374:
	ASCII(.ascii	"line %d, get APC error, ret %d\012\000" )
.LC375:
	ASCII(.ascii	"InserFrmInDPB: cur pic struct = %d!\012\000" )
	.space	3
.LC376:
	ASCII(.ascii	"CurrPic.state is 'EMPTY'\012\000" )
	.space	2
.LC377:
	ASCII(.ascii	"StorePicInDPB return(%d) from L%d\012\000" )
	.space	1
.LC378:
	ASCII(.ascii	"directoutput mode\012\000" )
	.space	1
.LC379:
	ASCII(.ascii	"line: %d pImg is NULL!\012\000" )
.LC380:
	ASCII(.ascii	"line %d, REPORT_IFRAME_ERR\012\000" )
.LC381:
	ASCII(.ascii	"line %d, return %d\012\000" )
.LC382:
	ASCII(.ascii	"err(%d) > ref_thr(%d)\012\000" )
	.space	1
.LC383:
	ASCII(.ascii	"marking return %d\012\000" )
	.space	1
.LC384:
	ASCII(.ascii	"return value is unexpeced!\012\000" )
.LC385:
	ASCII(.ascii	"line %d: pH264Ctx->DPB.size = %d, ref %d, ltref %d\012" )
	ASCII(.ascii	"\000" )
.LC386:
	ASCII(.ascii	"%s: pos(%d) = pre_pos, force return.\012\000" )
	.space	2
.LC387:
	ASCII(.ascii	"FS_ALLOC_ERR, ClearAll\012\000" )
.LC388:
	ASCII(.ascii	"Can not new logic fs! ClearAll\012\000" )
.LC389:
	ASCII(.ascii	"GAP found while DPB is empty!\012\000" )
	.space	1
.LC390:
	ASCII(.ascii	"frame num gap try to fill it \012\000" )
	.space	1
.LC391:
	ASCII(.ascii	"CurrFrameNum = %d  UnusedShortTermFrameNum = %d\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC392:
	ASCII(.ascii	"cann't allocate frame store when gap find\012\000" )
	.space	1
.LC393:
	ASCII(.ascii	"allocate frame store when gap find\012\000" )
.LC394:
	ASCII(.ascii	"line %d: store gap pic err, ret=%d\012\000" )
.LC395:
	ASCII(.ascii	"%s %d unknow error!!\012\000" )
	.space	2
.LC396:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC397:
	ASCII(.ascii	"%s %d frame_store is null!!\012\000" )
	.space	3
.LC398:
	ASCII(.ascii	"line %d: init dpb return %d\012\000" )
	.space	3
.LC399:
	ASCII(.ascii	"mem arrange err, ClearAll\012\000" )
	.space	1
.LC400:
	ASCII(.ascii	"line %d: frame gap(=%d) > dpb size(=%d)\012\000" )
	.space	3
.LC401:
	ASCII(.ascii	"line %d: dec gap failed\012\000" )
	.space	3
.LC402:
	ASCII(.ascii	"line %d: alloc framestore failed\012\000" )
	.space	2
.LC403:
	ASCII(.ascii	"dec_pts: %lld\012\000" )
	.space	1
.LC404:
	ASCII(.ascii	"dec_usertag: %lld\012\000" )
	.space	1
.LC405:
	ASCII(.ascii	"%s %d NULL == pH264Ctx->CurrPic.frame_store!!\012\000" )
	.space	1
.LC406:
	ASCII(.ascii	"get back frm\012\000" )
	.space	2
.LC407:
	ASCII(.ascii	"Start Reason: SliceParaNum, MaxBytesReceived = %d, " )
	ASCII(.ascii	"%d(thr=%d)\012\000" )
	.space	1
.LC408:
	ASCII(.ascii	"Too many slice or bitstream, err!\012\000" )
	.space	1
.LC409:
	ASCII(.ascii	"Start Reason: new_pic_flag\012\000" )
.LC410:
	ASCII(.ascii	"init pic err, find next recover point or next valid" )
	ASCII(.ascii	" sps, pps, or exit\012\000" )
	.space	1
.LC411:
	ASCII(.ascii	"DecList error, ret=%d\012\000" )
	.space	1
.LC412:
	ASCII(.ascii	"dec list err, cur pic poc %d.\012\000" )
	.space	1
.LC413:
	ASCII(.ascii	"pH264Ctx->TotalNal = %d, type:%d\012\000" )
	.space	2
.LC414:
	ASCII(.ascii	"stop i want\012\000" )
	.space	3
.LC415:
	ASCII(.ascii	"svc_extension_flag error:priority_id:%d, pred_flag%" )
	ASCII(.ascii	"d\012\000" )
	.space	2
.LC416:
	ASCII(.ascii	"%d,%d,%d\012\000" )
	.space	2
.LC417:
	ASCII(.ascii	"svc stream,nal_header:%x\012\000" )
	.space	2
.LC418:
	ASCII(.ascii	"***** NAL: IDR/Slice, nal_unit_type=%d, TotalSlice=" )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC419:
	ASCII(.ascii	"SliceCheck failed, clear current slice.\012\000" )
	.space	3
.LC420:
	ASCII(.ascii	"***** NAL: PPS, nal_unit_type=%d, TotalPPS=%d\012\000" )
	.space	1
.LC421:
	ASCII(.ascii	"%s: PPS decode error.\012\000" )
	.space	1
.LC422:
	ASCII(.ascii	"***** NAL: SPS, nal_unit_type=%d, TotalSPS=%d\012\000" )
	.space	1
.LC423:
	ASCII(.ascii	"SPS decode error.\012\000" )
	.space	1
.LC424:
	ASCII(.ascii	"***** NAL: SEI, nal_unit_type=%d\012\000" )
	.space	2
.LC425:
	ASCII(.ascii	"SEI decode error.\012\000" )
	.space	1
.LC426:
	ASCII(.ascii	"***** NAL: AUD, nal_unit_type=%d\012\000" )
	.space	2
.LC427:
	ASCII(.ascii	"***** NAL: EOSEQ, nal_unit_type=%d\012\000" )
.LC428:
	ASCII(.ascii	"***** NAL: FILL, nal_unit_type=%d\012\000" )
	.space	1
.LC429:
	ASCII(.ascii	"***** NAL: EOSTREAM, nal_unit_type=%d\012\000" )
	.space	1
.LC430:
	ASCII(.ascii	"***** NAL: SPSEXT, nal_unit_type=%d\012\000" )
	.space	3
.LC431:
	ASCII(.ascii	"***** NAL: AUX, nal_unit_type=%d\012\000" )
	.space	2
.LC432:
	ASCII(.ascii	"***** NAL: EOPIC, nal_unit_type=%d\012\000" )
.LC433:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d,nalu header:" )
	ASCII(.ascii	"%x\012\000" )
	.space	1
.LC434:
	ASCII(.ascii	"***** NAL: UNSUPPORT, nal_unit_type=%d\012\000" )
.LC435:
	ASCII(.ascii	"FindTrailZeros ERR\012\000" )
.LC436:
	ASCII(.ascii	"H264_DecOneNal ERR\012\000" )
.LC437:
	ASCII(.ascii	"store pic err, ret = %d\012\000" )
	.space	3
.LC438:
	ASCII(.ascii	"pH264Ctx->CurrPic.frame_store is null pointer\012\000" )
	.space	1
.LC439:
	ASCII(.ascii	"imode nal store pic err, ret = %d\012\000" )
	.space	1
.LC440:
	ASCII(.ascii	"imode nal flush dpb err, ret = %d\012\000" )
	.space	1
.LC441:
	ASCII(.ascii	"cann't find FrameStore\012\000" )
.LC442:
	ASCII(.ascii	"========== H264 FrameStore state(is_used, is_in_dpb" )
	ASCII(.ascii	", IsOutDPB) ========\012\000" )
	.space	3
.LC443:
	ASCII(.ascii	"ReadImgNum = %d, NewImgNum = %d\012\000" )
	.space	3
.LC444:
	ASCII(.ascii	"%02d: %d %d %d\012\000" )
.LC445:
	ASCII(.ascii	"FrameStore leak, ClearAll\012\000" )
	.bss
	.align	2
.LANCHOR2 = . + 0
.LANCHOR3 = . + 8184
	.type	pps_tmp.15298, %object
	.size	pps_tmp.15298, 2208
pps_tmp.15298:
	.space	2208
	.type	sps_tmp.15450, %object
	.size	sps_tmp.15450, 4000
sps_tmp.15450:
	.space	4000
	.type	TmpBuf, %object
	.size	TmpBuf, 68
TmpBuf:
	.space	68
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
