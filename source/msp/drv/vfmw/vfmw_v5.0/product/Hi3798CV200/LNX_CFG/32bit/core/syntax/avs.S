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
	.file	"avs.c"
	.text
	.align	2
	.global	avs_u_v
	.type	avs_u_v, %function
avs_u_v:
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
	mov	r6, r1
	mov	r5, r2
	bl	BsGet
	str	r6, [sp]
	mov	r2, r5
	ldr	r1, .L2
	mov	r4, r0
	mov	r3, r0
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_u_v, .-avs_u_v
	.align	2
	.global	avs_f_v
	.type	avs_f_v, %function
avs_f_v:
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
	mov	r6, r1
	mov	r5, r2
	bl	BsGet
	str	r6, [sp]
	mov	r2, r5
	ldr	r1, .L5
	mov	r4, r0
	mov	r3, r0
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r4
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L6:
	.align	2
.L5:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_f_v, .-avs_f_v
	.align	2
	.global	avs_ue_v
	.type	avs_ue_v, %function
avs_ue_v:
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
	mov	r6, r1
	mov	r1, #32
	mov	r7, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	mov	r4, r0
	mvnhi	r5, #0
	movhi	r4, #32
	bls	.L11
.L8:
	str	r4, [sp]
	mov	r2, r6
	mov	r3, r5
	ldr	r1, .L12
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L11:
	add	r5, r4, #1
	mov	r1, r4
	mov	r0, r7
	mov	r4, r4, asl #1
	bl	BsSkip
	mov	r1, r5
	mov	r0, r7
	add	r4, r4, #1
	bl	BsShow
	mov	r1, r5
	sub	r5, r0, #1
	mov	r0, r7
	bl	BsSkip
	b	.L8
.L13:
	.align	2
.L12:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_ue_v, .-avs_ue_v
	.align	2
	.global	avs_se_v
	.type	avs_se_v, %function
avs_se_v:
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
	mov	r6, r1
	mov	r1, #32
	mov	r7, r0
	bl	BsShow
	bl	ZerosMS_32
	cmp	r0, #31
	mov	r4, r0
	mvnhi	r5, #-2147483648
	movhi	r4, #32
	bls	.L19
.L15:
	str	r4, [sp]
	mov	r2, r6
	mov	r3, r5
	ldr	r1, .L20
	mov	r0, #7
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L19:
	add	r8, r4, #1
	mov	r1, r4
	mov	r0, r7
	mov	r4, r4, asl #1
	bl	BsSkip
	mov	r1, r8
	mov	r0, r7
	add	r4, r4, #1
	bl	BsShow
	mov	r1, r8
	sub	r0, r0, #1
	tst	r0, #1
	mov	r5, r0, asr #1
	mov	r0, r7
	addne	r5, r5, #1
	rsbeq	r5, r5, #0
	bl	BsSkip
	b	.L15
.L21:
	.align	2
.L20:
	.word	.LC0
	UNWIND(.fnend)
	.size	avs_se_v, .-avs_se_v
	.align	2
	.global	AVS_next_start_code
	.type	AVS_next_start_code, %function
AVS_next_start_code:
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
	bgt	.L25
	b	.L26
.L31:
	bl	BsSkip
	cmp	r4, r6
	beq	.L26
.L25:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	bne	.L31
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L26:
	mov	r3, #0
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_next_start_code, .-AVS_next_start_code
	.align	2
	.global	AVS_sequence_header
	.type	AVS_sequence_header, %function
AVS_sequence_header:
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
	add	r6, r0, #12288
	mov	r4, r1
	ldr	r2, .L42
	ldr	r5, [r6, #3176]
	mov	r1, #32
	ldr	r3, [r6, #2784]
	mov	r7, r0
	bic	r3, r3, #65536
	mov	r0, r5
	str	r3, [r6, #2784]
	bl	avs_f_v
	ldr	r2, .L42+4
	mov	r1, #8
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+8
	mov	r1, #8
	str	r0, [r4, #16]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+12
	mov	r1, #1
	str	r0, [r4, #20]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+16
	mov	r1, #14
	strb	r0, [r4, #15]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+20
	mov	r1, #14
	str	r0, [r4, #24]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+24
	mov	r1, #2
	str	r0, [r4, #28]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+28
	mov	r1, #3
	strb	r0, [r4, #11]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+32
	mov	r1, #4
	strb	r0, [r4, #12]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+36
	mov	r1, #4
	strb	r0, [r4, #13]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+40
	mov	r1, #18
	strb	r0, [r4, #14]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+44
	mov	r1, #1
	str	r0, [r4, #32]
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L42+48
	mov	r1, #12
	strb	r0, [r4, #10]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+52
	mov	r1, #1
	str	r0, [r4, #36]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+44
	mov	r1, #1
	strb	r0, [r4, #9]
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L42+56
	mov	r1, #18
	strb	r0, [r4, #10]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L42+60
	mov	r1, #3
	str	r0, [r4, #40]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #14]	@ zero_extendqisi2
	cmp	r3, #15
	ldrls	r2, .L42+64
	mvnhi	r3, #0
	ldrls	r3, [r2, r3, asl #2]
	strb	r0, [r4, #8]
	str	r3, [r4, #44]
	ldr	r3, [r4, #24]
	ldr	r0, [r6, #2824]
	cmp	r3, r0
	beq	.L41
.L35:
	ldr	r3, .L42+68
	mov	r2, #1
	str	r2, [r6, #2796]
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L36
	ldr	r8, [r6, #2828]
	mov	r3, #8
	ldr	r5, [r4, #24]
	sub	r2, fp, #44
	ldr	lr, [r4, #28]
	mov	r1, #2
	strh	r0, [fp, #-44]	@ movhi
	strh	r8, [fp, #-42]	@ movhi
	ldr	r0, [r7, #4]
	strh	r5, [fp, #-40]	@ movhi
	strh	lr, [fp, #-38]	@ movhi
	blx	ip
.L36:
	mov	r1, r4
	mov	r2, #376
	add	r0, r6, #2800
	bl	memcpy
	ldr	r2, [r6, #2792]
	ldr	r3, [r6, #2784]
	mov	r0, #1
	add	r2, r2, r0
	str	r0, [r6, #2788]
	orr	r3, r3, #65536
	str	r2, [r6, #2792]
	str	r3, [r6, #2784]
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L41:
	ldr	r2, [r4, #28]
	ldr	r3, [r6, #2828]
	cmp	r2, r3
	bne	.L35
	b	.L36
.L43:
	.align	2
.L42:
	.word	.LC1
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	.LC13
	.word	.LC14
	.word	.LC15
	.word	.LC16
	.word	.LANCHOR0
	.word	g_event_report
	UNWIND(.fnend)
	.size	AVS_sequence_header, .-AVS_sequence_header
	.align	2
	.global	AVS_i_picture_header
	.type	AVS_i_picture_header, %function
AVS_i_picture_header:
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
	ldr	r3, .L83
	mov	r6, r0
	ldr	r5, [r0, #544]
	mov	r4, r1
	add	r0, r1, #80
	mov	r2, #272
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r6, #152]
	ldr	r2, .L83+4
	mov	r1, #32
	bic	r3, r3, #262144
	mov	r0, r5
	str	r3, [r6, #152]
	bl	avs_f_v
	mov	r0, r5
	ldr	r2, .L83+8
	mov	r1, #16
	bl	avs_u_v
	ldr	r3, [r4, #16]
	cmp	r3, #72
	str	r0, [r4, #96]
	beq	.L75
.L45:
	ldr	r2, .L83+12
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #90]
	cmp	r0, #1
	beq	.L76
.L46:
	ldr	r2, .L83+16
	mov	r1, #1
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L83+20
	mov	r1, #8
	str	r0, [r4, #108]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	cmp	r3, #1
	str	r0, [r4, #112]
	beq	.L77
.L47:
	ldr	r2, .L83+24
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #15]	@ zero_extendqisi2
	cmp	r3, #1
	uxtb	r0, r0
	strb	r0, [r4, #80]
	streqb	r3, [r4, #80]
	beq	.L49
	cmp	r0, #0
	beq	.L78
.L49:
	mov	r3, #1
	strb	r3, [r4, #81]
.L50:
	ldr	r2, .L83+28
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+32
	mov	r1, #1
	strb	r0, [r4, #82]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+36
	mov	r1, #1
	strb	r0, [r4, #83]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+40
	mov	r1, #6
	strb	r0, [r4, #84]
	mov	r0, r5
	bl	avs_u_v
	ldrh	r3, [r4, #80]
	cmp	r3, #0
	strb	r0, [r4, #85]
	beq	.L79
.L51:
	ldr	r2, .L83+44
	mov	r1, #4
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+48
	mov	r1, #1
	strb	r0, [r4, #87]
	mov	r0, r5
	bl	avs_u_v
	mov	r3, #0
	str	r3, [r4, #120]
	str	r3, [r4, #124]
	uxtb	r0, r0
	strb	r0, [r4, #88]
	cmp	r0, r3
	beq	.L80
.L53:
	ldr	r3, [r4, #16]
	cmp	r3, #72
	beq	.L81
.L55:
	mov	r0, #1
	mov	r3, #0
	strb	r0, [r4, #93]
	str	r3, [r4, #348]
	ldr	r3, [r6, #152]
	orr	r3, r3, #262144
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L78:
	ldr	r2, .L83+52
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #81]
	b	.L50
.L80:
	ldr	r2, .L83+56
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #89]
	cmp	r0, #0
	beq	.L53
	ldr	r1, .L83+60
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L83+64
	str	r0, [r4, #120]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #124]
	b	.L53
.L79:
	ldr	r2, .L83+68
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #86]
	b	.L51
.L81:
	ldr	r2, .L83+72
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #0
	str	r0, [r4, #128]
	bne	.L56
.L65:
	mov	r0, r5
	ldr	r2, .L83+76
	mov	r1, #1
	bl	avs_u_v
	str	r0, [r4, #332]
	b	.L55
.L75:
	ldr	r2, .L83+16
	mov	r1, #1
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L83+80
	mov	r1, #7
	str	r0, [r4, #108]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #96]
	mov	r2, #1
	strb	r2, [r4]
	str	r0, [r4, #100]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #96]
	b	.L45
.L76:
	ldr	r2, .L83+84
	mov	r1, #24
	mov	r0, r5
	bl	avs_u_v
	str	r0, [r4, #104]
	b	.L46
.L77:
	ldr	r1, .L83+88
	mov	r0, r5
	bl	avs_ue_v
	str	r0, [r4, #116]
	b	.L47
.L56:
	ldr	r2, .L83+92
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+96
	mov	r1, #1
	str	r0, [r4, #132]
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #0
	str	r0, [r4, #136]
	beq	.L82
.L57:
	ldr	r2, .L83+100
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L83+104
	mov	r1, #2
	str	r0, [r4, #148]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #148]
	cmp	r3, #1
	str	r0, [r4, #152]
	beq	.L60
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	beq	.L60
	cmp	r3, #2
	addeq	r7, r4, #176
	bne	.L65
.L64:
	add	r8, r4, #200
.L63:
	ldr	r1, .L83+108
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r7, #4]!
	cmp	r7, r8
	bne	.L63
	b	.L65
.L82:
	ldr	r1, .L83+112
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L83+116
	str	r0, [r4, #140]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #144]
	b	.L57
.L60:
	add	r8, r4, #152
	add	r7, r4, #176
.L59:
	ldr	r1, .L83+120
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r8, #4]!
	cmp	r8, r7
	bne	.L59
	ldr	r3, [r4, #148]
	cmp	r3, #2
	beq	.L64
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	bne	.L65
	b	.L64
.L84:
	.align	2
.L83:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC17
	.word	.LC18
	.word	.LC20
	.word	.LC12
	.word	.LC22
	.word	.LC24
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC16
	.word	.LC31
	.word	.LC25
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC30
	.word	.LC35
	.word	.LC36
	.word	.LC19
	.word	.LC21
	.word	.LC23
	.word	.LC37
	.word	.LC38
	.word	.LC41
	.word	.LC42
	.word	.LC44
	.word	.LC39
	.word	.LC40
	.word	.LC43
	UNWIND(.fnend)
	.size	AVS_i_picture_header, .-AVS_i_picture_header
	.align	2
	.global	AVS_pb_picture_header
	.type	AVS_pb_picture_header, %function
AVS_pb_picture_header:
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
	ldr	r3, .L137
	mov	r6, r0
	ldr	r5, [r0, #544]
	mov	r4, r1
	add	r0, r1, #80
	mov	r2, #272
	ldr	r3, [r3, #48]
	mov	r1, #0
	blx	r3
	ldr	r3, [r6, #152]
	ldr	r2, .L137+4
	mov	r1, #32
	bic	r3, r3, #262144
	mov	r0, r5
	str	r3, [r6, #152]
	bl	avs_f_v
	mov	r0, r5
	ldr	r2, .L137+8
	mov	r1, #16
	bl	avs_u_v
	ldr	r3, [r4, #16]
	cmp	r3, #72
	str	r0, [r4, #96]
	beq	.L129
.L86:
	ldr	r2, .L137+12
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+16
	mov	r1, #8
	strb	r0, [r4, #91]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	cmp	r3, #1
	str	r0, [r4, #112]
	beq	.L130
.L87:
	ldr	r2, .L137+20
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #80]
	cmp	r0, #0
	movne	r3, #1
	strneb	r3, [r4, #81]
	beq	.L131
.L89:
	ldr	r2, .L137+24
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+28
	mov	r1, #1
	strb	r0, [r4, #82]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+32
	mov	r1, #1
	strb	r0, [r4, #83]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+36
	mov	r1, #6
	strb	r0, [r4, #84]
	mov	r0, r5
	bl	avs_u_v
	ldrb	r3, [r4, #91]	@ zero_extendqisi2
	cmp	r3, #2
	strb	r0, [r4, #85]
	beq	.L132
.L90:
	ldr	r2, .L137+40
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #93]
.L92:
	ldr	r2, .L137+44
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	ldrb	r2, [r4, #91]	@ zero_extendqisi2
	mov	r3, #0
	str	r3, [r4, #340]
	cmp	r2, #2
	str	r3, [r4, #344]
	strb	r0, [r4, #94]
	beq	.L133
	ldr	r2, .L137+48
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	str	r0, [r4, #340]
.L94:
	ldrb	r3, [r4, #81]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L95
	ldr	r3, [r4, #16]
	cmp	r3, #72
	beq	.L96
.L95:
	mov	r3, #0
	str	r3, [r4, #340]
	str	r3, [r4, #344]
.L96:
	ldr	r2, .L137+52
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+56
	mov	r1, #1
	strb	r0, [r4, #87]
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+60
	mov	r1, #1
	strb	r0, [r4, #86]
	mov	r0, r5
	bl	avs_u_v
	mov	r3, #0
	str	r3, [r4, #120]
	str	r3, [r4, #124]
	uxtb	r0, r0
	strb	r0, [r4, #88]
	cmp	r0, r3
	beq	.L134
.L98:
	ldr	r3, [r4, #16]
	cmp	r3, #72
	beq	.L135
.L100:
	ldrb	r3, [r4, #91]	@ zero_extendqisi2
	mov	r0, #1
	cmp	r3, #1
	movne	r3, #2
	str	r3, [r4, #348]
	ldr	r3, [r6, #152]
	orr	r3, r3, #262144
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L132:
	ldrb	r3, [r4, #81]	@ zero_extendqisi2
	cmp	r3, #1
	streqb	r3, [r4, #93]
	bne	.L90
	b	.L92
.L131:
	ldr	r2, .L137+64
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #81]
	cmp	r0, #0
	bne	.L89
	ldr	r2, .L137+68
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	strb	r0, [r4, #92]
	b	.L89
.L134:
	ldr	r2, .L137+72
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r4, #89]
	cmp	r0, #0
	beq	.L98
	ldr	r1, .L137+76
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L137+80
	str	r0, [r4, #120]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #124]
	b	.L98
.L133:
	ldr	r2, .L137+84
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	str	r0, [r4, #344]
	b	.L94
.L135:
	ldr	r2, .L137+88
	mov	r1, #1
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #1
	mov	r7, r0
	str	r0, [r4, #128]
	beq	.L101
.L110:
	mov	r0, r5
	ldr	r2, .L137+92
	mov	r1, #1
	bl	avs_u_v
	str	r0, [r4, #332]
	b	.L100
.L129:
	ldr	r2, .L137+96
	mov	r1, #1
	mov	r0, r5
	bl	avs_f_v
	ldr	r2, .L137+100
	mov	r1, #7
	str	r0, [r4, #108]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #96]
	mov	r2, #1
	strb	r2, [r4]
	str	r0, [r4, #100]
	orr	r0, r0, r3, asl #7
	str	r0, [r4, #96]
	b	.L86
.L130:
	ldr	r1, .L137+104
	mov	r0, r5
	bl	avs_ue_v
	str	r0, [r4, #116]
	b	.L87
.L101:
	mov	r1, r0
	ldr	r2, .L137+108
	mov	r0, r5
	bl	avs_u_v
	mov	r1, r7
	ldr	r2, .L137+112
	str	r0, [r4, #132]
	mov	r0, r5
	bl	avs_u_v
	cmp	r0, #0
	str	r0, [r4, #136]
	beq	.L136
.L102:
	ldr	r2, .L137+116
	mov	r1, #2
	mov	r0, r5
	bl	avs_u_v
	ldr	r2, .L137+120
	mov	r1, #2
	str	r0, [r4, #148]
	mov	r0, r5
	bl	avs_u_v
	ldr	r3, [r4, #148]
	cmp	r3, #1
	str	r0, [r4, #152]
	beq	.L105
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	beq	.L105
	cmp	r3, #2
	addeq	r7, r4, #176
	bne	.L110
.L109:
	add	r8, r4, #200
.L108:
	ldr	r1, .L137+124
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r7, #4]!
	cmp	r7, r8
	bne	.L108
	b	.L110
.L105:
	add	r8, r4, #152
	add	r7, r4, #176
.L104:
	ldr	r1, .L137+128
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r8, #4]!
	cmp	r8, r7
	bne	.L104
	ldr	r3, [r4, #148]
	cmp	r3, #2
	beq	.L109
	ldr	r2, [r4, #132]
	cmp	r2, #0
	cmpeq	r3, #3
	bne	.L110
	b	.L109
.L136:
	ldr	r1, .L137+132
	mov	r0, r5
	bl	avs_se_v
	ldr	r1, .L137+136
	str	r0, [r4, #140]
	mov	r0, r5
	bl	avs_se_v
	str	r0, [r4, #144]
	b	.L102
.L138:
	.align	2
.L137:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC45
	.word	.LC18
	.word	.LC46
	.word	.LC22
	.word	.LC24
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.word	.LC29
	.word	.LC48
	.word	.LC49
	.word	.LC51
	.word	.LC16
	.word	.LC30
	.word	.LC31
	.word	.LC25
	.word	.LC47
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC50
	.word	.LC35
	.word	.LC36
	.word	.LC12
	.word	.LC19
	.word	.LC23
	.word	.LC37
	.word	.LC38
	.word	.LC41
	.word	.LC42
	.word	.LC44
	.word	.LC43
	.word	.LC39
	.word	.LC40
	UNWIND(.fnend)
	.size	AVS_pb_picture_header, .-AVS_pb_picture_header
	.align	2
	.global	AVS_user_data
	.type	AVS_user_data, %function
AVS_user_data:
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
	add	r4, r0, #12288
	mov	r6, r1
	mov	r5, r0
	ldr	r2, .L172
	ldr	r0, [r4, #3176]
	mov	r1, #32
	bl	avs_f_v
	ldr	r3, [r4, #2784]
	cmp	r6, #0
	orr	r3, r3, #1048576
	str	r3, [r4, #2784]
	bne	.L140
	ldr	r1, [r4, #3468]
	cmp	r1, #0
	beq	.L141
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	str	r6, [r4, #3468]
.L141:
	ldr	r0, [r5, #4]
	bl	GetUsd
	cmp	r0, #0
	str	r0, [r4, #3468]
	beq	.L151
	ldr	r3, [r5, #12]
	add	r0, r0, #1056
	mov	r1, #10
	add	r6, r5, #16384
	ldr	r7, .L172+4
	ldrd	r2, [r3, #56]
	strd	r2, [r0]
	ldr	r3, [r4, #3468]
	str	r1, [r3, #1040]
	ldr	r3, [r4, #3468]
	ldr	r2, [r4, #2792]
	str	r2, [r3, #1044]
	ldr	r2, [r4, #3468]
	ldr	r3, [r6, #180]
	sub	r3, r3, #4
	str	r3, [r2, #1052]
	ldr	r0, [r4, #3468]
	ldr	r2, [r0, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r0, #1052]
	ldrgt	r0, [r4, #3468]
	ldr	r1, [r6, #168]
	ldr	r3, [r7, #52]
	ldrgt	r2, [r0, #1052]
	add	r1, r1, #4
	blx	r3
	ldrb	r3, [r6, #173]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L146
	ldr	r2, [r4, #3468]
	ldr	r1, [r6, #260]
	ldr	r3, [r2, #1052]
	add	r3, r3, r1
	str	r3, [r2, #1052]
	ldr	r1, [r4, #3468]
	ldr	r2, [r1, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r1, #1052]
	ldrgt	r1, [r4, #3468]
	ldr	r0, [r6, #180]
	ldrgt	r2, [r1, #1052]
	rsb	r3, r0, #4
	add	r2, r3, r2
	cmp	r2, #0
	ble	.L146
	sub	r0, r0, #4
	ldr	r3, [r7, #52]
	add	r0, r1, r0
	ldr	r1, [r6, #248]
	blx	r3
.L146:
	ldr	r3, .L172+8
	ldr	ip, [r3]
	cmp	ip, #0
	ldrne	r2, [r4, #3468]
	bne	.L171
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L140:
	ldr	r1, [r4, #3472]
	cmp	r1, #0
	beq	.L150
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r3, #0
	str	r3, [r4, #3472]
.L150:
	ldr	r0, [r5, #4]
	bl	GetUsd
	cmp	r0, #0
	str	r0, [r4, #3472]
	beq	.L151
	ldr	r3, [r5, #12]
	add	r0, r0, #1056
	mov	r1, #11
	add	r6, r5, #16384
	ldr	r7, .L172+4
	ldrd	r2, [r3, #56]
	strd	r2, [r0]
	ldr	r3, [r4, #3472]
	str	r1, [r3, #1040]
	ldr	r3, [r4, #3472]
	ldr	r2, [r4, #2792]
	str	r2, [r3, #1044]
	ldr	r2, [r4, #3472]
	ldr	r3, [r6, #180]
	sub	r3, r3, #4
	str	r3, [r2, #1052]
	ldr	r0, [r4, #3472]
	ldr	r2, [r0, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r0, #1052]
	ldrgt	r0, [r4, #3472]
	ldr	r1, [r6, #168]
	ldr	r3, [r7, #52]
	ldrgt	r2, [r0, #1052]
	add	r1, r1, #4
	blx	r3
	ldrb	r3, [r6, #173]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L154
	ldr	r2, [r4, #3472]
	ldr	r1, [r6, #260]
	ldr	r3, [r2, #1052]
	add	r3, r3, r1
	str	r3, [r2, #1052]
	ldr	r1, [r4, #3472]
	ldr	r2, [r1, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r1, #1052]
	ldrgt	r1, [r4, #3472]
	ldr	r0, [r6, #180]
	ldrgt	r2, [r1, #1052]
	rsb	r3, r0, #4
	add	r2, r3, r2
	cmp	r2, #0
	ble	.L154
	sub	r0, r0, #4
	ldr	r3, [r7, #52]
	add	r0, r1, r0
	ldr	r1, [r6, #248]
	blx	r3
.L154:
	ldr	r3, .L172+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L170
	ldr	r2, [r4, #3472]
.L171:
	movw	r3, #1064
	ldr	r0, [r5, #4]
	mov	r1, #6
	blx	ip
.L170:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L151:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L173:
	.align	2
.L172:
	.word	.LC52
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	UNWIND(.fnend)
	.size	AVS_user_data, .-AVS_user_data
	.align	2
	.global	AVS_sequence_display_extension
	.type	AVS_sequence_display_extension, %function
AVS_sequence_display_extension:
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
	ldr	r4, [r0, #544]
	mov	r5, r1
	ldr	r2, .L177
	mov	r1, #4
	mov	r6, r0
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+4
	mov	r1, #3
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+8
	mov	r1, #1
	strb	r0, [r5, #50]
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+12
	mov	r1, #1
	strb	r0, [r5, #51]
	mov	r0, r4
	bl	avs_u_v
	uxtb	r0, r0
	strb	r0, [r5, #52]
	cmp	r0, #1
	beq	.L176
.L175:
	ldr	r2, .L177+16
	mov	r1, #14
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+20
	mov	r1, #1
	str	r0, [r5, #68]
	mov	r0, r4
	bl	avs_f_v
	ldr	r2, .L177+24
	mov	r1, #14
	strb	r0, [r5, #49]
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+28
	mov	r1, #2
	str	r0, [r5, #72]
	mov	r0, r4
	bl	avs_u_v
	strb	r0, [r5, #48]
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r6, #152]
	mov	r0, #1
	orr	r3, r3, #131072
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L176:
	ldr	r2, .L177+32
	mov	r1, #8
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+36
	mov	r1, #8
	str	r0, [r5, #56]
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L177+40
	mov	r1, #8
	str	r0, [r5, #60]
	mov	r0, r4
	bl	avs_u_v
	str	r0, [r5, #64]
	b	.L175
.L178:
	.align	2
.L177:
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC60
	.word	.LC12
	.word	.LC61
	.word	.LC16
	.word	.LC57
	.word	.LC58
	.word	.LC59
	UNWIND(.fnend)
	.size	AVS_sequence_display_extension, .-AVS_sequence_display_extension
	.align	2
	.global	AVS_copyright_extension
	.type	AVS_copyright_extension, %function
AVS_copyright_extension:
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
	ldr	r4, [r0, #544]
	mov	r5, r0
	ldr	r2, .L180
	mov	r1, #4
	ldr	r6, .L180+4
	mov	r0, r4
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+8
	mov	r1, #1
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+12
	mov	r1, #8
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+16
	mov	r1, #1
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L180+20
	mov	r1, #7
	bl	avs_u_v
	mov	r2, r6
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L180+24
	mov	r1, #20
	bl	avs_u_v
	mov	r2, r6
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L180+28
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r6
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	ldr	r2, .L180+32
	mov	r1, #22
	mov	r0, r4
	bl	avs_u_v
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r5, #152]
	mov	r0, #1
	orr	r3, r3, #2097152
	str	r3, [r5, #152]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L181:
	.align	2
.L180:
	.word	.LC53
	.word	.LC12
	.word	.LC62
	.word	.LC63
	.word	.LC64
	.word	.LC16
	.word	.LC65
	.word	.LC66
	.word	.LC67
	UNWIND(.fnend)
	.size	AVS_copyright_extension, .-AVS_copyright_extension
	.align	2
	.global	AVS_camera_parameters_extension
	.type	AVS_camera_parameters_extension, %function
AVS_camera_parameters_extension:
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
	ldr	r4, [r0, #544]
	mov	r6, r0
	ldr	r7, .L183
	mov	r1, #4
	ldr	r5, .L183+4
	ldr	r2, .L183+8
	mov	r0, r4
	bl	avs_u_v
	mov	r2, r7
	mov	r0, r4
	mov	r1, #1
	bl	avs_u_v
	mov	r0, r4
	ldr	r2, .L183+12
	mov	r1, #7
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+16
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+20
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+24
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+28
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+32
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+36
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+40
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+44
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+48
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+52
	mov	r1, #16
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+56
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+60
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+64
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+68
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+72
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r0, r4
	ldr	r2, .L183+76
	mov	r1, #22
	bl	avs_u_v
	mov	r2, r5
	mov	r0, r4
	mov	r1, #1
	bl	avs_f_v
	mov	r2, r7
	mov	r1, #32
	mov	r0, r4
	bl	avs_u_v
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r6, #152]
	mov	r0, #1
	orr	r3, r3, #4194304
	str	r3, [r6, #152]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L184:
	.align	2
.L183:
	.word	.LC16
	.word	.LC12
	.word	.LC53
	.word	.LC68
	.word	.LC69
	.word	.LC70
	.word	.LC71
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC77
	.word	.LC78
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC83
	.word	.LC84
	UNWIND(.fnend)
	.size	AVS_camera_parameters_extension, .-AVS_camera_parameters_extension
	.align	2
	.global	AVS_picture_display_extension
	.type	AVS_picture_display_extension, %function
AVS_picture_display_extension:
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
	ldr	r4, [r0, #544]
	mov	r7, r1
	mov	r8, r0
	mov	r1, #4
	ldr	r2, .L204
	mov	r0, r4
	bl	avs_u_v
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L202
	ldrb	r3, [r7, #81]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L203
.L187:
	mov	r3, #1
	str	r3, [r7, #4]
.L189:
	add	r6, r7, #348
	mov	r5, #0
.L191:
	ldr	r2, .L204+4
	mov	r1, #16
	mov	r0, r4
	add	r5, r5, #1
	bl	avs_u_v
	ldr	r2, .L204+8
	mov	r1, #1
	str	r0, [r6, #4]!
	mov	r0, r4
	bl	avs_f_v
	ldr	r2, .L204+12
	mov	r1, #16
	mov	r0, r4
	bl	avs_u_v
	ldr	r2, .L204+8
	mov	r1, #1
	str	r0, [r6, #12]
	mov	r0, r4
	bl	avs_f_v
	ldr	r3, [r7, #4]
	cmp	r3, r5
	bgt	.L191
	mov	r0, r4
	bl	AVS_next_start_code
	ldr	r3, [r8, #152]
	mov	r0, #1
	orr	r3, r3, #524288
	str	r3, [r8, #152]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L203:
	ldrb	r3, [r7, #83]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L190
.L188:
	mov	r3, #2
	str	r3, [r7, #4]
	b	.L189
.L202:
	ldrb	r3, [r7, #83]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L187
	ldrb	r3, [r7, #82]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L188
.L190:
	mov	r3, #3
	str	r3, [r7, #4]
	b	.L189
.L205:
	.align	2
.L204:
	.word	.LC53
	.word	.LC85
	.word	.LC12
	.word	.LC86
	UNWIND(.fnend)
	.size	AVS_picture_display_extension, .-AVS_picture_display_extension
	.align	2
	.global	AVS_extension
	.type	AVS_extension, %function
AVS_extension:
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
	ldr	r4, [r0, #544]
	mov	r5, r0
	ldr	r2, .L213
	mov	r6, r1
	mov	r1, #32
	mov	r0, r4
	bl	avs_f_v
	mov	r0, r4
	mov	r1, #4
	bl	BsShow
	sub	r0, r0, #2
	cmp	r0, #9
	ldrls	pc, [pc, r0, asl #2]
	b	.L207
.L209:
	.word	.L208
	.word	.L207
	.word	.L210
	.word	.L207
	.word	.L207
	.word	.L211
	.word	.L207
	.word	.L207
	.word	.L207
	.word	.L212
.L212:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_camera_parameters_extension
.L211:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_picture_display_extension
.L210:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_copyright_extension
.L208:
	mov	r1, r6
	mov	r0, r5
	sub	sp, fp, #28
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, lr}
	b	AVS_sequence_display_extension
.L207:
	mov	r0, r4
	mov	r1, #4
	bl	BsSkip
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L214:
	.align	2
.L213:
	.word	.LC87
	UNWIND(.fnend)
	.size	AVS_extension, .-AVS_extension
	.align	2
	.global	AVS_extension_and_userdata
	.type	AVS_extension_and_userdata, %function
AVS_extension_and_userdata:
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
	add	r3, r0, #12288
	add	r6, r0, #14912
	add	r5, r0, #15808
	mov	r7, r0
	mov	r8, r1
	ldr	r4, [r3, #3176]
	add	r6, r6, #8
	add	r5, r5, #4
	b	.L219
.L218:
	mov	r1, #32
	mov	r0, r4
	bl	BsShow
	uxtb	r0, r0
	cmp	r0, #178
	beq	.L223
.L219:
	mov	r0, r4
	bl	BsResidBits
	cmp	r0, #40
	mov	r0, r4
	ble	.L224
	bl	AVS_next_start_code
	mov	r1, #32
	mov	r0, r4
	bl	BsShow
	uxtb	r0, r0
	cmp	r0, #178
	cmpne	r0, #181
	bne	.L221
	cmp	r0, #181
	bne	.L218
	mov	r1, r5
	mov	r0, r6
	bl	AVS_extension
	b	.L218
.L224:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L221:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L223:
	mov	r1, r8
	mov	r0, r7
	bl	AVS_user_data
	b	.L219
	UNWIND(.fnend)
	.size	AVS_extension_and_userdata, .-AVS_extension_and_userdata
	.align	2
	.global	AVS_AllocateVHB
	.type	AVS_AllocateVHB, %function
AVS_AllocateVHB:
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
	UNWIND(.pad #44)
	sub	sp, sp, #44
	add	r3, r0, #12288
	movw	r2, #8160
	mov	r5, r0
	ldr	r4, [r3, #2824]
	ldr	r3, [r3, #2828]
	sub	r1, r4, #32
	cmp	r1, r2
	bhi	.L226
	sub	r1, r3, #32
	cmp	r1, r2
	bhi	.L226
	ldr	r1, [r0, #12]
	ldr	r6, [r1, #724]
	ldr	r2, [r1, #28]
	cmp	r6, #0
	bne	.L229
	cmp	r2, #25
	beq	.L258
.L248:
	mov	r6, #4
	mov	r7, #5
	mov	r8, r6
.L230:
	ldr	ip, .L260
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #56
	str	r3, [fp, #-64]
	ldr	ip, [ip, #48]
	blx	ip
	ldr	r2, [r5, #12]
	ldr	r3, [fp, #-64]
	str	r4, [fp, #-52]
	ldr	r2, [r2, #28]
	str	r3, [fp, #-48]
	cmp	r2, #24
	str	r4, [fp, #-44]
	str	r3, [fp, #-40]
	beq	.L239
	uxtb	r6, r6
	strb	r8, [fp, #-55]
	strb	r7, [fp, #-54]
.L243:
	sub	r1, fp, #56
	ldr	r0, [r5, #4]
	strb	r6, [fp, #-53]
	bl	FSP_ConfigInstance
	subs	r6, r0, #0
	bne	.L240
	ldr	r1, [r5, #12]
	sub	r3, fp, #60
	ldr	r0, [r5, #4]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L259
	cmp	r0, #0
	moveq	r6, #1
	streq	r6, [r5, #8]
	beq	.L251
	ldr	r1, .L260+4
	mov	r0, r6
	bl	dprint_vfmw
	b	.L251
.L226:
	mov	r2, r4
	ldr	r1, .L260+8
	mov	r0, #0
	mov	r6, #0
	bl	dprint_vfmw
.L251:
	mov	r0, r6
	sub	sp, fp, #32
	ldmfd	sp, {r4, r5, r6, r7, r8, fp, sp, pc}
.L229:
	cmp	r2, #25
	bne	.L248
	ldr	r2, [r1, #684]
	ldr	r0, [r1, #688]
	cmp	r2, r4
	bcc	.L236
	cmp	r0, r3
	bcc	.L236
.L237:
	ldr	r0, [r1, #712]
	ldr	r2, [r1, #708]
	cmp	r0, #0
	add	r8, r2, #2
	moveq	r6, #1
	beq	.L238
	add	r6, r2, #1
	cmp	r6, #17
	movge	r6, #17
.L238:
	ldrb	r7, [r1, #732]	@ zero_extendqisi2
	b	.L230
.L240:
	ldr	r1, .L260+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r6, #0
	b	.L251
.L239:
	mov	r6, #1
	strb	r7, [fp, #-54]
	strb	r6, [fp, #-55]
	b	.L243
.L258:
	ldr	r2, [r1, #684]
	ldr	r0, [r1, #688]
	cmp	r2, r4
	bcc	.L232
	cmp	r0, r3
	bcc	.L232
	ldr	r6, [r5, #8]
	cmp	r6, #1
	bne	.L237
	b	.L251
.L236:
	str	r0, [sp, #4]
	mov	r0, #0
	str	r2, [sp]
	mov	r2, r4
	ldr	r1, .L260+16
	mov	r6, #0
	bl	dprint_vfmw
	b	.L251
.L232:
	str	r0, [sp, #4]
	mov	r0, #0
	str	r2, [sp]
	mov	r2, r4
	ldr	r1, .L260+16
	bl	dprint_vfmw
	b	.L251
.L259:
	add	r0, r5, #16192
	mov	r6, #3
	bl	ResetVoQueue
	b	.L251
.L261:
	.align	2
.L260:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC90
	.word	.LC88
	.word	.LC91
	.word	.LC89
	UNWIND(.fnend)
	.size	AVS_AllocateVHB, .-AVS_AllocateVHB
	.align	2
	.global	AVS_StartDecode
	.type	AVS_StartDecode, %function
AVS_StartDecode:
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
	add	r4, r0, #16384
	add	r6, r0, #12288
	mov	r5, r0
	ldr	r3, [r4, #328]
	strb	r3, [r0, #20]
	ldr	r3, [r4, #332]
	strb	r3, [r0, #21]
	ldr	r3, [r4, #336]
	strb	r3, [r0, #22]
	ldr	r3, [r4, #340]
	strb	r3, [r0, #23]
	ldr	r3, [r4, #344]
	strb	r3, [r0, #24]
	ldr	r3, [r4, #356]
	str	r3, [r0, #28]
	ldr	r3, [r4, #360]
	str	r3, [r0, #84]
	ldr	r3, [r4, #380]
	str	r3, [r0, #32]
	ldr	r3, [r4, #508]
	str	r3, [r0, #96]
	ldr	r3, [r4, #520]
	str	r3, [r0, #100]
	ldr	r3, [r4, #512]
	str	r3, [r0, #104]
	ldr	r3, [r4, #524]
	str	r3, [r0, #108]
	ldr	r3, [r4, #516]
	str	r3, [r0, #112]
	ldr	r3, [r4, #528]
	str	r3, [r0, #116]
	ldr	r3, [r4, #388]
	strh	r3, [r0, #80]	@ movhi
	ldr	r3, [r4, #384]
	strh	r3, [r0, #82]	@ movhi
	ldr	r3, [r4, #392]
	strb	r3, [r0, #59]
	ldr	r3, [r4, #396]
	strb	r3, [r0, #60]
	ldr	r3, [r4, #432]
	strb	r3, [r0, #36]
	ldr	r3, [r4, #436]
	strb	r3, [r0, #37]
	ldr	r3, [r4, #400]
	strb	r3, [r0, #38]
	ldr	r3, [r4, #404]
	strb	r3, [r0, #39]
	ldr	r3, [r4, #412]
	strb	r3, [r0, #40]
	ldr	r3, [r4, #416]
	strb	r3, [r0, #41]
	ldr	r3, [r4, #420]
	strb	r3, [r0, #42]
	ldr	r3, [r4, #424]
	strb	r3, [r0, #43]
	ldr	r3, [r4, #428]
	strb	r3, [r0, #44]
	ldr	r3, [r4, #440]
	strb	r3, [r0, #45]
	ldr	r3, [r4, #444]
	strb	r3, [r0, #46]
	ldr	r3, [r4, #448]
	strb	r3, [r0, #47]
	ldr	r3, [r4, #452]
	strb	r3, [r0, #48]
	ldr	r3, [r4, #456]
	strb	r3, [r0, #49]
	ldr	r3, [r4, #500]
	strb	r3, [r0, #50]
	ldr	r3, [r4, #408]
	strb	r3, [r0, #51]
	ldr	r3, [r4, #464]
	strb	r3, [r0, #52]
	ldr	r3, [r4, #460]
	strb	r3, [r0, #53]
	ldr	r3, [r4, #480]
	strb	r3, [r0, #54]
	ldr	r3, [r4, #476]
	strb	r3, [r0, #55]
	ldr	r3, [r4, #472]
	strb	r3, [r0, #56]
	ldr	r3, [r4, #468]
	strb	r3, [r0, #57]
	ldr	r3, [r4, #504]
	strb	r3, [r0, #58]
	ldr	r2, [r4, #484]
	ldr	r3, [r6, #2756]
	str	r2, [r6, #2172]
	ldr	r2, [r4, #488]
	str	r2, [r6, #2176]
	ldr	r2, [r4, #492]
	str	r2, [r6, #2180]
	ldr	r2, [r4, #560]
	str	r2, [r6, #2188]
	ldr	r2, [r4, #572]
	str	r2, [r6, #2192]
	ldr	r1, [r3, #12]
	ldr	r0, [r0, #4]
	bl	FSP_GetLogicFs
	subs	r7, r0, #0
	beq	.L277
	ldr	r2, [r7, #32]
	add	r0, r5, #14592
	add	r0, r0, #24
	add	r3, r5, #16896
	add	ip, r5, #17152
	add	r3, r3, #194
	ldr	r1, [r2, #24]
	add	ip, ip, #66
	mov	r2, r0
	str	r1, [r6, #2588]
	ldr	r1, [r7, #32]
	ldr	r1, [r1, #60]
	str	r1, [r6, #2596]
	ldr	r1, [r7, #32]
	ldr	r1, [r1, #44]
	str	r1, [r6, #2600]
	ldr	r1, [r7, #32]
	ldr	r1, [r1, #48]
	str	r1, [r6, #2604]
	ldr	r1, [r4, #380]
	str	r1, [r6, #2184]
	ldr	r1, [r4, #496]
	str	r1, [r6, #2196]
	ldr	r1, [r4, #704]
	str	r1, [r6, #2200]
	ldr	r1, [r4, #532]
	strb	r1, [r5, #61]
	ldr	r1, [r4, #536]
	strb	r1, [r5, #62]
	ldr	r1, [r4, #544]
	strb	r1, [r5, #63]
	ldr	r1, [r4, #540]
	strb	r1, [r5, #64]
	ldr	r1, [r4, #548]
	strb	r1, [r5, #65]
	ldr	r1, [r4, #552]
	strb	r1, [r5, #66]
	ldr	r1, [r4, #556]
	strb	r1, [r5, #67]
.L265:
	ldrsh	r1, [r3, #2]!
	cmp	r3, ip
	str	r1, [r2, #4]!
	bne	.L265
	ldr	r1, [r4, #364]
	add	r2, r5, #16896
	add	r3, r5, #14464
	add	r2, r2, #60
	add	r3, r3, #24
	str	r1, [r6, #2608]
	ldr	r1, [r4, #368]
	str	r1, [r6, #2612]
	ldr	r1, [r4, #372]
	str	r1, [r6, #2616]
	ldr	r1, [r4, #376]
	str	r1, [r6, #2620]
.L266:
	ldr	r1, [r2, #4]!
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L266
	ldr	r3, [r6, #3464]
	add	r1, r5, #20
	add	r3, r3, #1
	str	r3, [r6, #3464]
	ldr	r3, [r5, #12]
	str	r1, [r5, #16]
	ldr	r2, [r3, #880]
	cmp	r2, #1
	beq	.L278
	cmp	r2, #2
	beq	.L279
.L268:
	ldr	r2, [r3, #592]
	mov	r0, #1
	str	r2, [r6, #2624]
	ldr	r3, [r3, #644]
	str	r3, [r6, #2628]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L278:
	cmp	r1, #0
	beq	.L268
	ldr	r1, [r6, #2756]
	ldrb	r2, [r1, #9]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L268
	mov	r7, #0
	ldr	r0, [r5, #4]
	str	r7, [r5, #16]
	mov	r2, r7
	ldr	r1, [r1, #12]
	bl	FSP_SetDisplay
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L279:
	ldr	r2, [r3, #884]
	cmp	r1, #0
	cmpne	r2, #0
	ble	.L268
	ldr	r1, [r6, #2756]
	ldrb	r2, [r1, #9]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L268
	mov	r7, #0
	ldr	r0, [r5, #4]
	str	r7, [r5, #16]
	mov	r2, r7
	ldr	r1, [r1, #12]
	bl	FSP_SetDisplay
	ldr	r2, [r5, #12]
	mov	r0, r7
	ldr	r3, [r2, #884]
	sub	r3, r3, #1
	str	r3, [r2, #884]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L277:
	mov	r2, #2208
	ldr	r1, .L280
	bl	dprint_vfmw
	mov	r0, r7
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L281:
	.align	2
.L280:
	.word	.LC92
	UNWIND(.fnend)
	.size	AVS_StartDecode, .-AVS_StartDecode
	.align	2
	.global	AVS_SetImgFormat
	.type	AVS_SetImgFormat, %function
AVS_SetImgFormat:
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
	mov	r6, r0
	ldrb	r3, [r5, #2815]	@ zero_extendqisi2
	ldr	r10, [r5, #3148]
	cmp	r3, #1
	ldrb	r8, [r5, #2850]	@ zero_extendqisi2
	moveq	r9, #0
	beq	.L283
	ldrb	r9, [r5, #2880]	@ zero_extendqisi2
	subs	r9, r9, #1
	movne	r9, #1
.L283:
	ldrb	r3, [r5, #2813]	@ zero_extendqisi2
	ldrb	r2, [r5, #2882]	@ zero_extendqisi2
	sub	r3, r3, #1
	ldr	r0, [r6, #4]
	uxtb	r3, r3
	str	r2, [fp, #-48]
	cmp	r3, #3
	ldrls	r2, .L293
	movhi	r7, #0
	addls	r3, r2, r3, lsl #2
	ldrls	r7, [r3, #64]
	ldr	r3, [r5, #2756]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L291
	ldrb	r3, [r4, #65]	@ zero_extendqisi2
	mov	r1, r7
	ldrb	ip, [r4, #64]	@ zero_extendqisi2
	bfi	r3, r9, #0, #2
	ldr	r2, [fp, #-48]
	bfi	ip, r10, #0, #2
	uxtb	r3, r3
	and	ip, ip, #227
	orr	r3, r3, #12
	bfi	ip, r8, #5, #3
	bfi	r3, r2, #4, #2
	strb	ip, [r4, #64]
	strb	r3, [r4, #65]
	ldr	r3, [r4, #64]
	bfi	r3, r7, #14, #3
	str	r3, [r4, #64]
	ldr	r2, [r5, #2756]
	ldrb	r3, [r4, #66]	@ zero_extendqisi2
	ldrb	r2, [r2]	@ zero_extendqisi2
	bfi	r3, r2, #1, #1
	strb	r3, [r4, #66]
	ldr	r3, [r5, #2756]
	ldr	r3, [r3, #4]
	str	r3, [r4, #120]
	ldr	r3, [r5, #3456]
	str	r10, [r4, #56]
	str	r10, [r4, #60]
	str	r3, [r4, #152]
	bl	SetAspectRatio
	ldr	r3, [r5, #2824]
	str	r3, [r4, #68]
	ldr	r3, [r5, #2828]
	str	r3, [r4, #72]
	ldr	r2, [r5, #2844]
	str	r2, [r4, #108]
	ldr	r2, [r6, #12]
	ldr	r2, [r2, #28]
	cmp	r2, #25
	beq	.L292
.L286:
	mov	r3, #6
	str	r3, [r4, #296]
	ldrb	r1, [r5, #2881]	@ zero_extendqisi2
	mov	r2, #1
	mov	r3, #8
	strb	r2, [r4, #291]
	cmp	r1, r2
	strb	r2, [r4, #289]
	str	r3, [r4, #300]
	moveq	r2, #0
	movne	r2, #4
	str	r3, [r4, #308]
	strb	r2, [r4, #284]
	str	r3, [r4, #304]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L292:
	ldr	r0, [r4, #112]
	add	r3, r3, #15
	ldr	ip, [r4, #36]
	add	lr, r4, #512
	mov	r3, r3, lsr #4
	mov	r1, r0, asl #4
	add	r6, ip, r0
	mul	r1, r3, r1
	add	r7, r1, ip
	str	r7, [r4, #40]
	ldrd	r2, [lr, #-8]
	add	r0, r7, r0
	adds	r2, r2, r1
	adc	r3, r3, r1, asr #31
	strd	r2, [lr]
	str	r7, [r4, #24]
	str	r0, [r4, #32]
	str	r6, [r4, #28]
	str	ip, [r4, #20]
	b	.L286
.L291:
	movw	r2, #2332
	ldr	r1, .L293+4
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L294:
	.align	2
.L293:
	.word	.LANCHOR0
	.word	.LC93
	UNWIND(.fnend)
	.size	AVS_SetImgFormat, .-AVS_SetImgFormat
	.align	2
	.global	AVS_GetImageBuffer
	.type	AVS_GetImageBuffer, %function
AVS_GetImageBuffer:
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
	add	r4, r0, #12288
	mov	r5, r0
	ldr	r3, [r4, #3872]
	cmp	r3, #2
	beq	.L296
	ldr	r6, [r4, #3188]
	add	r7, r0, #14912
	add	r7, r7, #8
	add	r2, r6, #1
	mov	r3, r6, asl #4
	mov	r1, r2, asr #31
	add	r6, r3, r6, lsl #2
	add	r6, r6, #24
	mov	r3, r1, lsr #30
	add	r6, r7, r6
	add	r2, r2, r3
	str	r6, [r4, #2756]
	and	r2, r2, #3
	rsb	r2, r3, r2
	str	r2, [r4, #3188]
.L297:
	mov	r1, #1
	ldr	r0, [r5, #4]
	bl	FSP_NewLogicFs
	str	r0, [r6, #12]
	ldr	r3, [r4, #2756]
	ldr	r1, [r3, #12]
	cmp	r1, #0
	blt	.L312
	ldr	r0, [r5, #4]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L313
	ldr	r3, [r4, #2756]
	mov	r0, #18
	ldr	r1, .L314
	ldr	r2, [r3, #12]
	bl	dprint_vfmw
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L302
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L302
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L314+4
	bl	dprint_vfmw
.L302:
	mov	r3, #0
	mov	r0, #1
	str	r3, [r5, #192]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L296:
	add	r7, r0, #14912
	add	r6, r7, #112
	add	r7, r7, #8
	str	r6, [r4, #2756]
	b	.L297
.L312:
	ldr	r1, .L314+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r10, r0, #0
	beq	.L299
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r8, r10, #560
	add	r6, r10, #576
	add	r9, r10, #544
	ldr	r1, [r3, #12]
	add	r7, r7, #4
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2760]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2764]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2768]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r1, [r10, #544]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r10, #552]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r10, #560]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r10, #568]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r9]
	strd	r2, [r8, #-8]
	strd	r2, [r8]
	strd	r2, [r6, #-8]
	str	r7, [r4, #2756]
	str	r7, [r4, #2768]
	str	r7, [r4, #2764]
	str	r7, [r4, #2760]
	ldr	r0, [r5, #4]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2648]
.L299:
	mov	r6, #0
	add	r1, r5, #16192
	str	r6, [r4, #3452]
	ldr	r0, [r5, #4]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r6
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L313:
	movw	r2, #2437
	ldr	r1, .L314+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L315:
	.align	2
.L314:
	.word	.LC95
	.word	.LC96
	.word	.LC94
	.word	.LC92
	UNWIND(.fnend)
	.size	AVS_GetImageBuffer, .-AVS_GetImageBuffer
	.align	2
	.global	AVS_OutputOneFrame
	.type	AVS_OutputOneFrame, %function
AVS_OutputOneFrame:
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
	mov	r6, r0
	mov	r4, r1
	ldr	r0, [r1, #4]
	ldr	r1, [r6, #12]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L322
	mov	r2, #1
	ldr	r1, [r6, #12]
	ldr	r0, [r4, #4]
	bl	FSP_SetDisplay
	ldr	r0, [r4, #4]
	add	r3, r4, #16192
	str	r5, [sp]
	mov	r2, r4
	mov	r1, #6
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L318
	ldr	r0, [r4, #4]
	mov	r2, #0
	ldr	r1, [r6, #12]
	bl	FSP_SetDisplay
	ldr	r2, [r6, #12]
	ldr	r1, .L323
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
.L318:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L322:
	movw	r2, #2478
	ldr	r1, .L323+4
	bl	dprint_vfmw
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L324:
	.align	2
.L323:
	.word	.LC98
	.word	.LC97
	UNWIND(.fnend)
	.size	AVS_OutputOneFrame, .-AVS_OutputOneFrame
	.align	2
	.global	AVS_UpdateTableIdx2Dist
	.type	AVS_UpdateTableIdx2Dist, %function
AVS_UpdateTableIdx2Dist:
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
	ldrb	r3, [r0, #249]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r0, #516]
	beq	.L339
	cmp	r3, #0
	beq	.L340
	cmp	r3, #1
	bne	.L334
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	ldr	r1, [r0, #124]
	cmp	r3, r2
	ldrne	r2, [r3, #16]
	ldr	r3, [r0, #128]
	ldreq	r2, [r0, #588]
	movne	r2, r2, asl #1
	strne	r2, [r0, #588]
	add	r2, r2, #1
	str	r2, [r0, #584]
	ldr	r3, [r3, #16]
	str	r2, [r0, #604]
	mov	r3, r3, asl #1
	str	r3, [r0, #580]
	str	r3, [r0, #600]
	add	r3, r3, #1
	str	r3, [r0, #576]
	str	r3, [r0, #596]
	ldr	r3, [r1, #16]
	mov	r3, r3, asl #1
	str	r3, [r0, #592]
.L330:
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L340:
	ldr	r3, [r0, #128]
	ldr	r3, [r3, #16]
	mov	r3, r3, asl #1
	str	r3, [r0, #592]
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L339:
	cmp	r3, #1
	beq	.L341
	cmp	r3, #2
	bne	.L330
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	cmp	r3, r2
	ldrne	r3, [r3, #16]
	movne	r3, r3, asl #1
	strne	r3, [r0, #576]
	ldr	r3, [r0, #128]
	ldr	r3, [r3, #16]
	mov	r3, r3, asl #1
	str	r3, [r0, #584]
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L334:
	cmp	r3, #2
	bne	.L330
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	cmp	r3, r2
	ldrne	r2, [r3, #16]
	ldr	r3, [r0, #128]
	ldreq	r2, [r0, #580]
	movne	r2, r2, asl #1
	strne	r2, [r0, #580]
	add	r1, r2, #1
	str	r1, [r0, #576]
	ldr	r3, [r3, #16]
	str	r1, [r0, #592]
	str	r2, [r0, #596]
	mov	r3, r3, asl #1
	str	r3, [r0, #584]
	str	r3, [r0, #600]
	add	r3, r3, #1
	str	r3, [r0, #588]
	str	r3, [r0, #604]
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L341:
	ldr	r3, [r0, #128]
	add	r2, r0, #4
	ldr	r1, [r0, #132]
	ldr	r3, [r3, #16]
	cmp	r1, r2
	mov	r3, r3, asl #1
	str	r3, [r0, #576]
	ldrne	r3, [r1, #16]
	movne	r3, r3, asl #1
	strne	r3, [r0, #580]
	b	.L330
	UNWIND(.fnend)
	.size	AVS_UpdateTableIdx2Dist, .-AVS_UpdateTableIdx2Dist
	.global	__aeabi_idiv
	.align	2
	.global	AVS_UpdateTableMvEScale
	.type	AVS_UpdateTableMvEScale, %function
AVS_UpdateTableMvEScale:
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
	mov	r6, r0
	ldrb	r0, [r0, #249]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L393
	ldr	r3, [r6, #516]
	cmp	r3, #0
	moveq	r3, #512
	streq	r3, [r6, #672]
	beq	.L379
	cmp	r3, #1
	bne	.L369
	ldr	r3, [r6, #124]
	add	r10, r6, #588
	str	r3, [fp, #-60]
	add	r3, r6, #572
	str	r3, [fp, #-48]
	add	r3, r6, #604
	str	r3, [fp, #-52]
	mov	r3, #0
	str	r3, [fp, #-56]
.L358:
	ldr	r3, [fp, #-60]
	mov	r8, r10
	ldr	r7, [fp, #-52]
	ldr	r6, [fp, #-48]
	ldr	r2, [r3, #16]
	ldr	r3, [fp, #-56]
	add	r9, r3, r2, lsl #1
	mov	r10, r9
.L354:
	ldr	r5, [r6, #4]!
	mov	r9, r7
	ldr	r4, [fp, #-48]
	rsb	r5, r5, r10
	ubfx	r5, r5, #0, #9
.L356:
	ldr	r1, [r4, #4]!
	mov	r0, #512
	mov	r3, #1
	rsb	r1, r1, r10
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L355
	bl	__aeabi_idiv
	mov	r3, r0
.L355:
	mul	r3, r3, r5
	cmp	r8, r4
	str	r3, [r9, #4]!
	bne	.L356
	cmp	r8, r6
	add	r7, r7, #16
	bne	.L354
	ldr	r3, [fp, #-56]
	add	r10, r8, #16
	add	r3, r3, #1
	str	r3, [fp, #-56]
	cmp	r3, #2
	ldr	r3, [fp, #-48]
	add	r3, r3, #16
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-52]
	add	r3, r3, #64
	str	r3, [fp, #-52]
	bne	.L358
.L379:
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L393:
	ldr	r2, [r6, #124]
	ldr	r3, [r6, #516]
	ldr	r5, [r2, #16]
	cmp	r3, #1
	addeq	r9, r6, #572
	addeq	r7, r6, #32
	moveq	r8, r6
	mov	r5, r5, asl #1
	beq	.L345
	cmp	r3, #2
	bne	.L379
	ldr	r3, [r6, #576]
	rsb	r3, r3, r5
	ubfx	r4, r3, #0, #9
	cmp	r4, #0
	beq	.L351
	mov	r1, r4
	mov	r0, #512
	bl	__aeabi_idiv
.L351:
	mul	r3, r0, r4
	ldr	r4, [r6, #584]
	rsb	r4, r5, r4
	ubfx	r4, r4, #0, #9
	cmp	r4, #0
	str	r3, [r6, #608]
	moveq	r0, #1
	beq	.L352
	mov	r1, r4
	mov	r0, #512
	bl	__aeabi_idiv
.L352:
	mul	r4, r0, r4
	mov	r0, #1
	str	r4, [r6, #624]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L345:
	ldr	r1, [r6, #576]
	mov	r0, #512
	ldr	r4, [r9, #4]!
	mov	r3, #1
	rsb	r1, r1, r5
	ubfx	r1, r1, #0, #9
	rsb	r4, r4, r5
	cmp	r1, #0
	ubfx	r4, r4, #0, #9
	beq	.L347
	bl	__aeabi_idiv
	mov	r3, r0
.L347:
	mul	r3, r3, r4
	mov	r0, #1
	str	r3, [r8, #608]
	ldr	r1, [r6, #580]
	rsb	r1, r1, r5
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L348
	mov	r0, #512
	bl	__aeabi_idiv
.L348:
	mul	r0, r0, r4
	add	r8, r8, #16
	str	r0, [r8, #596]
	cmp	r8, r7
	bne	.L345
	b	.L379
.L369:
	cmp	r3, #2
	bne	.L379
	ldr	r3, [r6, #124]
	mov	r7, r6
	add	r6, r6, #16
	add	r10, r7, #572
	mov	r8, #0
	str	r3, [fp, #-52]
.L368:
	ldr	r3, [fp, #-52]
	mov	r9, r10
	ldr	r4, [r3, #16]
	mov	r3, r7
	add	r4, r8, r4, lsl #1
.L359:
	ldr	r1, [r10, #4]
	mov	r0, #512
	ldr	r5, [r9, #4]!
	mov	ip, #1
	rsb	r1, r1, r4
	ubfx	r1, r1, #0, #9
	rsb	r5, r5, r4
	cmp	r1, #0
	ubfx	r5, r5, #0, #9
	beq	.L361
	str	r3, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
	mov	ip, r0
.L361:
	mul	ip, ip, r5
	mov	r0, #1
	str	ip, [r3, #608]
	ldr	r1, [r10, #8]
	rsb	r1, r1, r4
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L362
	mov	r0, #512
	str	r3, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r3, [fp, #-48]
.L362:
	mul	r0, r0, r5
	add	r3, r3, #8
	str	r0, [r3, #604]
	cmp	r3, r6
	bne	.L359
	add	r2, r10, #8
	mov	r9, r7
.L360:
	ldr	r1, [r10, #12]
	mov	r0, #512
	ldr	r5, [r2, #4]!
	mov	ip, #1
	rsb	r1, r4, r1
	ubfx	r1, r1, #0, #9
	rsb	r5, r4, r5
	cmp	r1, #0
	ubfx	r5, r5, #0, #9
	beq	.L365
	str	r2, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-48]
	mov	ip, r0
.L365:
	mul	ip, ip, r5
	mov	r0, #1
	str	ip, [r9, #624]
	ldr	r1, [r10, #16]
	rsb	r1, r4, r1
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	beq	.L366
	mov	r0, #512
	str	r2, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-48]
.L366:
	mul	r0, r0, r5
	add	r9, r9, #8
	str	r0, [r9, #620]
	cmp	r6, r9
	bne	.L360
	add	r8, r8, #1
	add	r6, r6, #32
	cmp	r8, #2
	add	r7, r7, #32
	add	r10, r10, #16
	bne	.L368
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTableMvEScale, .-AVS_UpdateTableMvEScale
	.align	2
	.global	AVS_UpdateTableDirectScale
	.type	AVS_UpdateTableDirectScale, %function
AVS_UpdateTableDirectScale:
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
	ldrb	r3, [r0, #249]	@ zero_extendqisi2
	mov	r6, r0
	cmp	r3, #1
	beq	.L417
	ldr	r8, [r0, #128]
	mov	r5, #1
	add	r9, r0, #4
	add	r7, r0, #736
	mov	r4, #0
	ldr	r10, [r8, #16]
	mov	r10, r10, asl r5
.L401:
	sub	r3, r5, #1
	mov	r0, #16384
	and	r1, r5, #1
	add	r3, r3, r3, lsr #31
	mov	r3, r3, asr #1
	add	r3, r3, #33
	ldr	r3, [r6, r3, asl #2]
	cmp	r9, r3
	beq	.L399
	ldr	r4, [r3, #16]
	add	r4, r1, r4, lsl #1
	rsb	r1, r4, r10
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	moveq	r3, #32
	streq	r3, [r7]
	beq	.L399
	bl	__aeabi_idiv
	str	r0, [r7]
.L399:
	add	r5, r5, #1
	add	r7, r7, #4
	cmp	r5, #5
	bne	.L401
	ldr	r2, [r8, #16]
	add	r10, r6, #752
	ldr	ip, [r6, #852]
	mov	r5, #1
	mov	r7, #0
	cmp	ip, #0
	moveq	r2, r2, asl #1
	movne	r8, r2, asl #1
	addeq	r8, r2, #1
.L411:
	cmp	ip, #0
	beq	.L404
	add	r3, r7, r7, lsr #31
	mov	r3, r3, asr #1
	add	r3, r3, #33
	ldr	r3, [r6, r3, asl #2]
	cmp	r9, r3
	beq	.L405
	ldr	r4, [r3, #16]
	and	r3, r5, #1
	add	r4, r3, r4, lsl #1
	rsb	r0, r4, r8
	add	r0, r0, #512
	mov	r1, r0, asr #31
	mov	r1, r1, lsr #23
	add	r0, r0, r1
	ubfx	r3, r0, #0, #9
	subs	r1, r3, r1
	moveq	r3, #32
	streq	r3, [r10, #-16]
	beq	.L407
	mov	r0, #16384
	str	ip, [fp, #-48]
	bl	__aeabi_idiv
	ldr	ip, [fp, #-48]
	str	r0, [r10, #-16]
.L408:
	str	r0, [r10]
.L410:
	add	r5, r5, #1
	add	r7, r7, #1
	cmp	r5, #5
	add	r10, r10, #4
	bne	.L411
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L404:
	add	r3, r5, r5, lsr #31
	mov	r3, r3, asr #1
	add	r3, r3, #32
	ldr	r3, [r6, r3, asl #2]
	cmp	r9, r3
	ldrne	r4, [r3, #16]
	andne	r3, r7, #1
	addne	r4, r3, r4, lsl #1
.L405:
	rsb	r0, r4, r8
	add	r0, r0, #512
	mov	r1, r0, asr #31
	mov	r1, r1, lsr #23
	add	r0, r0, r1
	ubfx	r3, r0, #0, #9
	subs	r1, r3, r1
	beq	.L407
	mov	r0, #16384
	str	ip, [fp, #-48]
	bl	__aeabi_idiv
	ldr	ip, [fp, #-48]
	b	.L408
.L407:
	mov	r3, #32
	str	r3, [r10]
	b	.L410
.L417:
	ldr	r3, [r0, #128]
	add	r7, r0, #4
	add	r4, r0, #128
	add	r6, r0, #136
	mov	r8, #32
	ldr	r5, [r3, #16]
	mov	r5, r5, asl #1
.L398:
	ldr	r3, [r4, #4]!
	mov	r0, #16384
	cmp	r3, r7
	beq	.L396
	ldr	r1, [r3, #16]
	sub	r1, r5, r1, asl #1
	ubfx	r1, r1, #0, #9
	cmp	r1, #0
	streq	r8, [r4, #604]
	beq	.L396
	bl	__aeabi_idiv
	str	r0, [r4, #604]
.L396:
	cmp	r4, r6
	bne	.L398
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTableDirectScale, .-AVS_UpdateTableDirectScale
	.align	2
	.global	AVS_UpdateTableSymScale
	.type	AVS_UpdateTableSymScale, %function
AVS_UpdateTableSymScale:
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
	ldr	r3, [r0, #132]
	add	r2, r0, #4
	mov	r5, r0
	cmp	r3, r2
	beq	.L425
	ldrb	r0, [r0, #249]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L420
	ldr	ip, [r5, #124]
	add	r2, r5, #572
	add	r5, r5, #764
	mov	r3, #0
.L423:
	ldr	r6, [ip, #16]
	add	r10, r2, #20
	mov	r9, r5
	mov	r8, r2
	mov	r7, #2
	add	r6, r3, r6, lsl #1
.L422:
	ldr	r1, [r8, #4]!
	mov	r0, #512
	ldr	r4, [r10, #-4]!
	mov	lr, #1
	rsb	r1, r1, r6
	ubfx	r1, r1, #0, #9
	rsb	r4, r6, r4
	cmp	r1, #0
	ubfx	r4, r4, #0, #9
	beq	.L421
	str	ip, [fp, #-56]
	str	r3, [fp, #-52]
	str	r2, [fp, #-48]
	bl	__aeabi_idiv
	ldr	r2, [fp, #-48]
	ldr	r3, [fp, #-52]
	ldr	ip, [fp, #-56]
	mov	lr, r0
.L421:
	mul	r4, lr, r4
	subs	r7, r7, #1
	str	r4, [r9, #4]!
	bne	.L422
	add	r3, r3, #1
	add	r2, r2, #16
	cmp	r3, #2
	add	r5, r5, #8
	bne	.L423
	mov	r0, #1
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L420:
	ldr	r2, [r5, #124]
	ldr	r1, [r3, #16]
	ldr	r3, [r5, #128]
	ldr	r2, [r2, #16]
	ldr	r4, [r3, #16]
	mov	r3, r2, asl #1
	sub	r1, r3, r1, asl #1
	ubfx	r1, r1, #0, #9
	rsb	r3, r3, r4, lsl #1
	cmp	r1, #0
	ubfx	r4, r3, #0, #9
	bne	.L430
.L424:
	mul	r3, r0, r4
	mov	r0, #1
	str	r3, [r5, #768]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L430:
	mov	r0, #512
	bl	__aeabi_idiv
	b	.L424
.L425:
	mov	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTableSymScale, .-AVS_UpdateTableSymScale
	.align	2
	.global	AVS_UpdateTabBBlkDist
	.type	AVS_UpdateTabBBlkDist, %function
AVS_UpdateTabBBlkDist:
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
	ldr	r2, [r0, #132]
	add	r1, r0, #4
	mov	r3, r0
	cmp	r2, r1
	beq	.L434
	ldrb	r0, [r0, #249]	@ zero_extendqisi2
	cmp	r0, #1
	beq	.L435
	ldr	r5, [r3, #124]
	mov	r0, #1
	ldr	r1, [r3, #588]
	ldr	r6, [r3, #576]
	ldr	r2, [r5, #16]
	ldr	lr, [r3, #584]
	ldr	ip, [r3, #580]
	mov	r2, r2, asl r0
	ldr	r4, [r3, #592]
	rsb	r6, r6, r2
	rsb	ip, ip, r2
	rsb	lr, r2, lr
	rsb	r2, r2, r1
	ubfx	lr, lr, #0, #9
	ubfx	r1, r6, #0, #9
	str	lr, [r3, #792]
	ubfx	r2, r2, #0, #9
	str	r1, [r3, #784]
	ubfx	r1, ip, #0, #9
	str	r2, [r3, #796]
	str	r1, [r3, #788]
	ldr	r2, [r5, #16]
	ldr	r1, [r3, #604]
	ldr	lr, [r3, #600]
	ldr	ip, [r3, #596]
	mov	r2, r2, asl r0
	add	r2, r2, r0
	rsb	r4, r4, r2
	rsb	ip, ip, r2
	rsb	lr, r2, lr
	rsb	r2, r2, r1
	ubfx	lr, lr, #0, #9
	ubfx	r1, r4, #0, #9
	ubfx	r2, r2, #0, #9
	str	r1, [r3, #800]
	str	lr, [r3, #808]
	ubfx	r1, ip, #0, #9
	str	r2, [r3, #812]
	str	r1, [r3, #804]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L435:
	ldr	r1, [r3, #124]
	ldr	lr, [r3, #128]
	ldr	ip, [r2, #16]
	ldr	r1, [r1, #16]
	ldr	lr, [lr, #16]
	mov	r2, r1, asl #1
	sub	r1, r2, ip, asl #1
	rsb	r2, r2, lr, lsl #1
	ubfx	r1, r1, #0, #9
	ubfx	r2, r2, #0, #9
	str	r1, [r3, #784]
	str	r2, [r3, #792]
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L434:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdateTabBBlkDist, .-AVS_UpdateTabBBlkDist
	.align	2
	.global	AVS_UpdatePmvTable
	.type	AVS_UpdatePmvTable, %function
AVS_UpdatePmvTable:
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
	ldr	r4, [r0, #516]
	mov	r5, r0
	cmp	r4, #1
	beq	.L445
	bcc	.L439
	cmp	r4, #2
	bne	.L447
	bl	AVS_UpdateTableIdx2Dist
	mov	r0, r5
	bl	AVS_UpdateTableMvEScale
	mov	r0, r5
	bl	AVS_UpdateTableDirectScale
	mov	r0, r5
	bl	AVS_UpdateTabBBlkDist
	mov	r0, r5
	bl	AVS_UpdateTableSymScale
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L447:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L439:
	ldrb	r4, [r0, #249]	@ zero_extendqisi2
	cmp	r4, #1
	beq	.L444
.L445:
	bl	AVS_UpdateTableIdx2Dist
	mov	r0, r5
	bl	AVS_UpdateTableMvEScale
.L444:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_UpdatePmvTable, .-AVS_UpdatePmvTable
	.align	2
	.global	AVS_GetStreamInf
	.type	AVS_GetStreamInf, %function
AVS_GetStreamInf:
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
	add	r4, r0, #12288
	mov	r5, r0
	ldr	r2, [r4, #2796]
	ldrb	r3, [r4, #2812]	@ zero_extendqisi2
	cmp	r2, #1
	str	r3, [r4, #3480]
	beq	.L449
	ldr	r3, [r0, #8]
	cmp	r3, #1
	beq	.L450
.L449:
	ldr	r1, .L557
	mov	r0, #22
	bl	dprint_vfmw
	sub	r3, fp, #44
	mov	ip, #0
	sub	r2, fp, #52
	str	ip, [r3, #-4]!
	sub	r1, fp, #56
	ldr	r0, [r5, #4]
	str	ip, [fp, #-56]
	str	ip, [fp, #-52]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r5, #12]
	ldr	r2, [r3, #724]
	cmp	r2, #1
	beq	.L542
.L452:
	ldrb	r3, [r4, #2815]	@ zero_extendqisi2
	ldr	r2, [r4, #2824]
	cmp	r3, #1
	ldr	r3, [r4, #2828]
	add	r2, r2, #15
	addne	r3, r3, #31
	addeq	r3, r3, #15
	mov	r2, r2, lsr #4
	str	r2, [r4, #2776]
	movne	r3, r3, lsr #5
	moveq	r3, r3, lsr #4
	movne	r3, r3, asl #1
	cmp	r2, #512
	str	r3, [r4, #2780]
	bgt	.L459
	cmp	r3, #512
	ble	.L460
.L459:
	ldr	r1, .L557+4
	mov	r0, #18
	bl	dprint_vfmw
	mov	r7, #0
.L455:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L460:
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	addeq	r6, r5, #14912
	addeq	r6, r6, #12
	beq	.L462
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r9, r7, #560
	add	r8, r7, #576
	add	r10, r7, #544
	ldr	r1, [r3, #12]
	add	r6, r5, #14912
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2760]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r6, r6, #12
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2764]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2768]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r1, [r7, #544]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r7, #552]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r7, #560]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r7, #568]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r10]
	strd	r2, [r9, #-8]
	strd	r2, [r9]
	strd	r2, [r8, #-8]
	str	r6, [r4, #2756]
	str	r6, [r4, #2768]
	str	r6, [r4, #2764]
	str	r6, [r4, #2760]
	ldr	r0, [r5, #4]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2648]
.L462:
	add	r7, r5, #16192
	mov	r3, #0
	str	r3, [r4, #3452]
	mov	r1, r7
	ldr	r0, [r5, #4]
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r5, #12]
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L463
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L543
.L463:
	ldr	r0, [r5, #4]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L539
.L465:
	mov	r7, #0
	str	r6, [r4, #2756]
	str	r7, [r4, #2796]
	mov	r0, r5
	str	r6, [r4, #2768]
	str	r6, [r4, #2764]
	str	r6, [r4, #2760]
	bl	AVS_AllocateVHB
	cmp	r0, #3
	mov	ip, r0
	moveq	r7, r0
	beq	.L455
	cmp	r0, r7
	strne	r7, [r4, #2796]
	beq	.L544
.L450:
	ldrb	r1, [r4, #2811]	@ zero_extendqisi2
	mov	r0, r5
	ldr	r3, [r4, #2756]
	ldrb	r2, [r4, #2881]	@ zero_extendqisi2
	str	r1, [r4, #3476]
	strb	r2, [r3, #8]
	bl	AVS_GetImageBuffer
	subs	r7, r0, #0
	beq	.L545
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L546
	ldr	r3, [r5, #12]
	add	lr, ip, #592
	add	r8, ip, #608
	mvn	r6, #0
	mvn	r7, #0
	ldr	r1, .L557+8
	ldrd	r2, [r3, #56]
	mov	r0, #29
	strd	r2, [lr, #-8]
	ldr	r3, [r5, #12]
	ldrd	r2, [r3, #72]
	strd	r2, [lr]
	ldr	r3, [r5, #12]
	ldrd	r2, [r3, #88]
	strd	r2, [r8, #-8]
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #104]
	str	r3, [ip]
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #108]
	str	r3, [ip, #4]
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #112]
	str	r3, [ip, #8]
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #128]
	str	r3, [ip, #12]
	ldrb	r3, [r4, #2881]	@ zero_extendqisi2
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [ip, #52]
	ldr	r3, [r5, #12]
	strd	r6, [r3, #56]
	ldrd	r6, [lr]
	ldrd	r2, [lr, #-8]
	strd	r6, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #2756]
	ldr	r2, [r4, #2912]
	str	r2, [r3, #16]
	ldr	r3, [r4, #2756]
	ldrb	r2, [r4, #2881]	@ zero_extendqisi2
	strb	r2, [r3, #8]
	ldr	r3, [r4, #2756]
	ldr	r2, [r4, #3148]
	strb	r2, [r3, #9]
	ldrb	r2, [r4, #2881]	@ zero_extendqisi2
	ldr	r3, [r4, #2756]
	cmp	r2, #0
	ldrneb	r2, [r4, #2882]	@ zero_extendqisi2
	moveq	r2, #1
	strb	r2, [r3, #10]
	ldrb	r3, [r4, #2881]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L540
	ldr	r7, [r4, #3148]
	cmp	r7, #0
	beq	.L537
.L540:
	add	r6, r5, #14912
	add	r6, r6, #8
.L471:
	ldr	r3, [r4, #3144]
	mov	r0, r6
	add	r6, r5, #16384
	mov	r7, #6
	str	r3, [r4, #3484]
	bl	AVS_UpdatePmvTable
	ldr	lr, [r4, #2776]
	ldr	ip, [r4, #2780]
	mov	r2, #0
	mov	r3, #1
	str	r2, [r6, #332]
	str	r3, [r6, #336]
	add	r2, r5, #16896
	mul	r1, ip, lr
	add	r3, r5, #15232
	add	r0, r5, #15360
	add	r3, r3, #58
	add	r2, r2, #194
	add	r0, r0, #58
	sub	r1, r1, #1
	str	r1, [r6, #328]
	ldr	r1, [r4, #3200]
	str	lr, [r6, #388]
	cmp	r1, #0
	add	lr, r1, #63
	str	ip, [r6, #384]
	movlt	r1, lr
	str	r7, [r6, #344]
	mov	r1, r1, asr r7
	str	r1, [r6, #340]
	ldr	r1, [r4, #3480]
	str	r1, [r6, #392]
	ldr	r1, [r4, #3476]
	str	r1, [r6, #396]
	ldrb	r1, [r4, #2894]	@ zero_extendqisi2
	str	r1, [r6, #400]
	ldrb	r1, [r4, #2893]	@ zero_extendqisi2
	str	r1, [r6, #404]
	ldrb	r1, [r4, #2892]	@ zero_extendqisi2
	str	r1, [r6, #408]
	ldrb	r1, [r4, #2886]	@ zero_extendqisi2
	str	r1, [r6, #412]
	ldrb	r1, [r4, #2885]	@ zero_extendqisi2
	str	r1, [r6, #416]
	ldrb	r1, [r4, #2884]	@ zero_extendqisi2
	str	r1, [r6, #420]
	ldrb	r1, [r4, #2883]	@ zero_extendqisi2
	str	r1, [r6, #424]
	ldrb	r1, [r4, #2882]	@ zero_extendqisi2
	str	r1, [r6, #428]
	ldr	r1, [r4, #3148]
	str	r1, [r6, #432]
	ldrb	r1, [r4, #2881]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r1, #1
	movne	r1, #3
	str	r1, [r6, #436]
	ldrb	r1, [r4, #2880]	@ zero_extendqisi2
	str	r1, [r6, #440]
	ldr	r1, [r4, #2924]
	str	r1, [r6, #444]
	ldr	r1, [r4, #2920]
	str	r1, [r6, #448]
	ldrb	r1, [r4, #2889]	@ zero_extendqisi2
	str	r1, [r6, #452]
	ldrb	r1, [r4, #2888]	@ zero_extendqisi2
	str	r1, [r6, #456]
	ldr	r1, [r4, #2928]
	str	r1, [r6, #532]
	ldr	r1, [r4, #2936]
	str	r1, [r6, #536]
	ldr	r1, [r4, #2940]
	str	r1, [r6, #544]
	ldr	r1, [r4, #2944]
	str	r1, [r6, #540]
.L474:
	ldrh	r1, [r3, #2]!
	cmp	r3, r0
	strh	r1, [r2, #2]!	@ movhi
	bne	.L474
	ldr	r3, [r4, #3132]
	str	r3, [r6, #548]
	ldr	r3, [r4, #3144]
	str	r3, [r6, #556]
	ldr	r3, [r4, #3140]
	str	r3, [r6, #552]
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	cmp	r3, #2
	ldr	r3, [r4, #2760]
	ldr	r1, [r3, #12]
	beq	.L547
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L548
	ldr	r3, [r4, #2760]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #460]
	ldrsb	r2, [r3, #10]
	str	r2, [r6, #464]
	ldr	r2, [ip, #36]
	str	r2, [r6, #484]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #476]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #480]
	ldr	r3, [ip, #36]
	str	r3, [r6, #488]
	ldr	r3, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	ldrne	r3, [r4, #2764]
	beq	.L549
.L541:
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #468]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #472]
	ldr	r3, [ip, #36]
	str	r3, [r6, #492]
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L550
	ldr	r3, [ip, #52]
	str	r3, [r6, #364]
	ldr	r3, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L551
	ldr	r3, [ip, #52]
	str	r3, [r6, #368]
	ldr	r3, [r4, #2768]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L552
	ldr	r3, [ip, #52]
	str	r3, [r6, #372]
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L553
	ldr	r3, [ip, #52]
	str	r3, [r6, #376]
	ldr	r3, [ip, #36]
	str	r3, [r6, #380]
	ldr	r3, [ip, #20]
	str	r3, [r6, #496]
	ldr	r3, [r4, #2760]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #500]
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	adds	r3, r3, #0
	movne	r3, #1
	str	r3, [r6, #504]
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetPmvAddr
	str	r0, [r6, #560]
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetPmvAddr
	add	ip, r5, #15488
	add	ip, ip, #36
	mov	r2, #0
	str	r0, [r6, #572]
	add	r0, r5, #16896
	ldr	r3, [r4, #3148]
	add	r0, r0, #60
	cmp	r3, #2
	movne	r1, #0
	moveq	r1, #4
	moveq	lr, #8
	moveq	r7, #16
	movne	r7, #32
	movne	lr, r1
.L495:
	add	r2, r2, #1
	ldr	r3, [ip, #4]!
	cmp	r2, r7
	ubfx	r3, r3, #0, #18
	str	r3, [r0, #4]!
	blt	.L495
	cmp	lr, #0
	ble	.L500
	add	ip, r5, #15616
	add	r0, r5, #16896
	add	ip, ip, #36
	add	r0, r0, #124
	mov	r2, #0
.L499:
	add	r2, r2, #1
	ldr	r3, [ip, #4]!
	cmp	r2, lr
	ubfx	r3, r3, #0, #15
	str	r3, [r0, #4]!
	bne	.L499
.L500:
	cmp	r1, #0
	ble	.L498
	add	r0, r5, #15680
	add	lr, r5, #16896
	add	r0, r0, #24
	add	lr, lr, #156
	mov	ip, #0
.L501:
	ldr	r2, [r0, #4]
	add	ip, ip, #1
	ldr	r3, [r0], #8
	cmp	ip, r1
	ubfx	r2, r2, #0, #9
	ubfx	r3, r3, #0, #9
	orr	r3, r3, r2, asl #9
	str	r3, [lr, #4]!
	bne	.L501
	add	r0, r5, #15680
	add	r5, r5, #16896
	add	r0, r0, #4
	add	r5, r5, #172
	mov	r2, #0
.L502:
	add	r2, r2, #1
	ldr	r3, [r0, #4]!
	cmp	r2, r1
	ubfx	r3, r3, #0, #18
	str	r3, [r5, #4]!
	bne	.L502
.L498:
	ldr	r3, [r4, #3196]
	mov	r7, #1
	mov	r0, r7
	str	r3, [r6, #704]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L542:
	ldr	r3, [fp, #-48]
	cmp	r3, #0
	ble	.L554
.L453:
	mov	r7, #3
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L545:
	ldr	r1, .L557+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L543:
	ldr	r3, [r5, #8]
	cmp	r3, #0
	bne	.L465
.L539:
	mov	r0, r7
	bl	ResetVoQueue
	b	.L465
.L554:
	ldr	r3, [fp, #-52]
	cmp	r3, #32
	bgt	.L453
	ldr	r7, [r5, #16]
	cmp	r7, #0
	bne	.L453
	ldr	r3, [r4, #2792]
	cmp	r3, #0
	beq	.L452
	ldr	r1, [r4, #3548]
	cmp	r1, #0
	beq	.L452
	add	r6, r5, #16384
	ldr	r0, [r6, #836]
	cmp	r1, r0
	beq	.L452
	ldr	lr, [r4, #3552]
	ldr	ip, [r6, #840]
	cmp	lr, ip
	beq	.L452
	str	r1, [sp, #12]
	stmib	sp, {r0, lr}
	mov	r0, r2
	str	ip, [sp]
	ldr	r1, .L557+16
	bl	dprint_vfmw
	ldr	r2, .L557+20
	ldr	r3, [r4, #3548]
	ldr	ip, [r2]
	str	r3, [r6, #836]
	ldr	r3, [r4, #3552]
	cmp	ip, #0
	str	r3, [r6, #840]
	beq	.L452
	mov	r3, r7
	mov	r2, r7
	mov	r1, #120
	ldr	r0, [r5, #4]
	blx	ip
	b	.L452
.L544:
	ldr	r1, .L557+24
	mov	r0, #1
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L547:
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L555
	ldr	r3, [r4, #2760]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #460]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #464]
	ldr	r3, [ip, #36]
	str	r3, [r6, #484]
	ldr	r3, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L556
	ldr	r3, [r4, #2764]
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	cmp	r2, #1
	moveq	r2, #3
	movne	r2, #1
	str	r2, [r6, #476]
	ldrsb	r3, [r3, #10]
	str	r3, [r6, #480]
	ldr	r3, [ip, #36]
	str	r3, [r6, #488]
	ldr	r3, [r4, #2768]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	ldrne	r3, [r4, #2768]
	bne	.L541
	movw	r2, #1989
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L537:
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r6, r5, #14912
	add	r6, r6, #8
	ldr	r1, [r3, #12]
	bl	FSP_SetRef
	ldr	r3, [r4, #2768]
	add	r2, r6, #4
	cmp	r3, r2
	beq	.L472
	mov	r2, r7
	ldr	r1, [r3, #12]
	ldr	r0, [r5, #4]
	bl	FSP_SetRef
.L472:
	ldr	r1, [r4, #2764]
	ldr	r2, [r4, #2760]
	ldr	r3, [r4, #2756]
	str	r1, [r4, #2768]
	str	r2, [r4, #2764]
	str	r3, [r4, #2760]
	b	.L471
.L546:
	movw	r2, #1886
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L550:
	movw	r2, #2013
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L551:
	movw	r2, #2017
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L552:
	movw	r2, #2021
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L549:
	movw	r2, #2006
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L548:
	movw	r2, #1997
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L553:
	movw	r2, #2025
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L556:
	movw	r2, #1983
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L555:
	movw	r2, #1977
	ldr	r1, .L557+28
	mov	r7, ip
	bl	dprint_vfmw
	b	.L455
.L558:
	.align	2
.L557:
	.word	.LC99
	.word	.LC101
	.word	.LC104
	.word	.LC103
	.word	.LC100
	.word	g_event_report
	.word	.LC102
	.word	.LC97
	UNWIND(.fnend)
	.size	AVS_GetStreamInf, .-AVS_GetStreamInf
	.align	2
	.global	AVS_PrepareDecode
	.type	AVS_PrepareDecode, %function
AVS_PrepareDecode:
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
	bl	AVS_GetStreamInf
	cmp	r0, #3
	ldmeqfd	sp, {fp, sp, pc}
	adds	r0, r0, #0
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_PrepareDecode, .-AVS_PrepareDecode
	.align	2
	.global	AVS_VerifyMemPara
	.type	AVS_VerifyMemPara, %function
AVS_VerifyMemPara:
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
	.size	AVS_VerifyMemPara, .-AVS_VerifyMemPara
	.align	2
	.global	AVSDEC_Init
	.type	AVSDEC_Init, %function
AVSDEC_Init:
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
	add	r6, r0, #16384
	ldr	r8, .L567
	add	r7, r0, #16192
	movw	r2, #17232
	ldr	r10, [r6, #152]
	mov	r9, r1
	ldr	r3, [r8, #48]
	mov	r1, #0
	mov	r4, r0
	add	r5, r0, #14912
	blx	r3
	str	r10, [r6, #152]
	mov	r0, r7
	add	r6, r4, #15744
	bl	ResetVoQueue
	str	r9, [r4, #12]
	mov	r0, r4
	add	r5, r5, #8
	bl	VCTRL_GetChanIDByCtx
	add	r6, r6, #36
	cmn	r0, #1
	str	r0, [r4, #4]
	beq	.L566
	ldr	r3, [r8, #48]
	mov	r2, #860
	mov	r1, #0
	mov	r0, r5
	blx	r3
	add	r3, r4, #12288
	add	r5, r5, #4
	mov	r1, #1024
	str	r5, [r3, #2756]
	mov	r2, #0
	str	r6, [r3, #3176]
	mov	r0, #1
	str	r5, [r3, #2768]
	str	r5, [r3, #2764]
	str	r5, [r3, #2760]
	str	r7, [r3, #3204]
	str	r1, [r3, #3200]
	ldr	r3, [r4, #12]
	str	r2, [r3, #888]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L566:
	ldr	r1, .L567+4
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #19
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L568:
	.align	2
.L567:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC105
	UNWIND(.fnend)
	.size	AVSDEC_Init, .-AVSDEC_Init
	.align	2
	.global	AVSDEC_Destroy
	.type	AVSDEC_Destroy, %function
AVSDEC_Destroy:
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
	.size	AVSDEC_Destroy, .-AVSDEC_Destroy
	.align	2
	.global	AVSDEC_RecycleImage
	.type	AVSDEC_RecycleImage, %function
AVSDEC_RecycleImage:
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
	mov	r5, r1
	beq	.L572
	mov	r2, #0
	ldr	r0, [r4, #4]
	bl	FSP_SetDisplay
	mov	r1, r5
	ldr	r0, [r4, #4]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	beq	.L573
	add	r5, r0, #560
	add	r8, r0, #544
	ldr	r1, [r0, #544]
	mov	r6, #0
	ldr	r0, [r4, #4]
	mov	r7, #0
	bl	FreeUsdByDec
	strd	r6, [r8]
	ldr	r0, [r4, #4]
	ldr	r1, [r5, #-8]
	bl	FreeUsdByDec
	strd	r6, [r5, #-8]
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L572:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L573:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVSDEC_RecycleImage, .-AVSDEC_RecycleImage
	.align	2
	.global	AVSDEC_GetRemainImg
	.type	AVSDEC_GetRemainImg, %function
AVSDEC_GetRemainImg:
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
	ldr	r3, [r0, #12]
	mov	r4, r0
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L580
	add	r10, r0, #15040
	mov	r8, #0
	add	r10, r10, #20
	mov	r9, #0
	mov	r5, #3
	mvn	r6, #0
.L579:
	ldr	r3, [r10, #-4]!
	ldr	r0, [r4, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L576
	ldr	r3, [r10]
	ldr	r0, [r4, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetDisplay
	cmp	r0, #2
	movne	r6, #1
	beq	.L588
.L576:
	subs	r5, r5, #1
	bne	.L579
	cmp	r6, #0
	bne	.L580
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L580:
	add	r0, r4, #16192
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	GetVoLastImageID
.L588:
	mov	r0, r4
	bl	AVS_SetImgFormat
	cmp	r5, #1
	streq	r5, [r7, #180]
	mov	r2, #1
	ldr	r3, [r10]
	ldr	r0, [r4, #4]
	ldr	r1, [r3, #12]
	bl	FSP_SetDisplay
	ldr	r0, [r4, #4]
	add	r3, r4, #16192
	str	r7, [sp]
	mov	r2, r4
	mov	r1, #6
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L578
	ldr	r1, [r7, #148]
	mov	r0, r4
	add	r3, r7, #544
	str	r3, [fp, #-52]
	add	r3, r7, #560
	str	r3, [fp, #-48]
	bl	AVSDEC_RecycleImage
	ldr	r1, [r7, #544]
	ldr	r0, [r4, #4]
	mvn	r6, #0
	bl	FreeUsdByDec
	ldr	r7, [fp, #-48]
	ldr	r3, [fp, #-52]
	strd	r8, [r3]
	ldr	r1, [r7, #-8]
	ldr	r0, [r4, #4]
	bl	FreeUsdByDec
	strd	r8, [r7, #-8]
	b	.L576
.L578:
	ldr	r3, [r7, #152]
	cmp	r3, #100
	bhi	.L583
	ldr	r3, [r7, #68]
	cmp	r3, #31
	bhi	.L589
.L583:
	mvn	r6, #0
	b	.L576
.L589:
	ldr	r6, [r7, #72]
	cmp	r6, #31
	movhi	r6, #0
	mvnls	r6, #0
	b	.L576
	UNWIND(.fnend)
	.size	AVSDEC_GetRemainImg, .-AVSDEC_GetRemainImg
	.align	2
	.global	AVSDEC_GetImageBuffer
	.type	AVSDEC_GetImageBuffer, %function
AVSDEC_GetImageBuffer:
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
	ldr	r0, [r0, #4]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, fp, sp, pc}
	ldr	r0, [r4, #4]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L596
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L596:
	add	r1, r4, #16192
	ldr	r0, [r4, #4]
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVSDEC_GetImageBuffer, .-AVSDEC_GetImageBuffer
	.align	2
	.global	ClearSlice
	.type	ClearSlice, %function
ClearSlice:
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
	add	r4, r1, #4
	add	r8, r1, #12
	mov	r7, r1
	mov	r9, r0
	mov	r6, r1
	mov	r5, #0
.L599:
	ldr	r3, [r4, #4]!
	cmp	r3, #0
	ble	.L598
	ldr	r3, [r6]
	cmp	r3, #0
	bne	.L604
.L598:
	cmp	r4, r8
	str	r5, [r4]
	str	r5, [r6], #4
	str	r5, [r7, #16]
	bne	.L599
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L604:
	ldr	r1, [r4, #12]
	mov	r0, r9
	bl	SM_ReleaseStreamSeg
	b	.L598
	UNWIND(.fnend)
	.size	ClearSlice, .-ClearSlice
	.align	2
	.global	AVS_ClearCurPic
	.type	AVS_ClearCurPic, %function
AVS_ClearCurPic:
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
	add	r6, r0, #12288
	mov	r7, r0
	ldr	r3, [r6, #2168]
	cmp	r3, #0
	ble	.L608
	add	r5, r0, #120
	mov	r4, #0
.L607:
	mov	r1, r5
	ldr	r0, [r7, #4]
	bl	ClearSlice
	ldr	r3, [r6, #2168]
	add	r4, r4, #1
	add	r5, r5, #28
	cmp	r3, r4
	bgt	.L607
.L608:
	mov	r3, #0
	mov	r0, #1
	str	r3, [r6, #2168]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_ClearCurPic, .-AVS_ClearCurPic
	.align	2
	.type	AVS_DecodeArbiter.part.4, %function
AVS_DecodeArbiter.part.4:
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
	ldr	r3, [r0, #12]
	mov	r6, r0
	add	r4, r0, #12288
	ldr	r3, [r3, #8]
	cmp	r3, #4
	ldrls	pc, [pc, r3, asl #2]
	b	.L626
.L614:
	.word	.L613
	.word	.L615
	.word	.L616
	.word	.L626
	.word	.L613
.L616:
	ldr	r5, [r4, #3872]
	clz	r5, r5
	mov	r5, r5, lsr #5
.L612:
	cmp	r5, #0
	str	r3, [r4, #3448]
	beq	.L632
.L619:
	ldr	r3, [r4, #3872]
	cmp	r3, #1
	beq	.L633
.L622:
	cmp	r3, #2
	bne	.L624
	ldr	r3, [r4, #3452]
	cmp	r3, #1
	ble	.L623
.L624:
	add	r1, r4, #3520
	mov	r2, #376
	add	r1, r1, #4
	add	r0, r4, #2800
	bl	memcpy
	ldrb	ip, [r4, #2881]	@ zero_extendqisi2
	ldr	r3, [r4, #3148]
	mov	r0, #18
	ldr	r2, [r4, #3464]
	ldr	r1, .L634
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r4, #2784]
	mov	r0, #1
	bic	r3, r3, #311296
	str	r3, [r4, #2784]
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L615:
	ldr	r2, [r4, #3448]
	ldr	r5, [r4, #3872]
	cmp	r2, #2
	str	r3, [r4, #3448]
	moveq	r2, #0
	streq	r2, [r4, #3452]
	subs	r5, r5, #2
	movne	r5, #1
	cmp	r5, #0
	bne	.L619
.L632:
	mov	r0, r6
	bl	AVS_ClearCurPic
	ldr	r2, .L634+4
	ldr	r3, [r4, #2784]
	ldr	ip, [r2]
	bic	r3, r3, #311296
	str	r3, [r4, #2784]
	cmp	ip, #0
	beq	.L631
	ldr	r0, [r6, #4]
	mov	r3, r5
	mov	r2, r5
	mov	r1, #113
	blx	ip
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L613:
	ldr	r2, [r4, #3448]
	str	r3, [r4, #3448]
	cmp	r2, #2
	ldr	r3, [r4, #3872]
	moveq	r2, #0
	streq	r2, [r4, #3452]
	cmp	r3, #1
	bne	.L622
.L633:
	ldr	r3, [r4, #3452]
	cmp	r3, #0
	bgt	.L624
.L623:
	mov	r0, r6
	bl	AVS_ClearCurPic
	ldr	r2, .L634+4
	ldr	r3, [r4, #2784]
	ldr	ip, [r2]
	bic	r3, r3, #311296
	str	r3, [r4, #2784]
	cmp	ip, #0
	beq	.L631
	mov	r3, #0
	ldr	r0, [r6, #4]
	mov	r2, r3
	mov	r1, #113
	blx	ip
.L631:
	mov	r0, #0
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L626:
	mov	r5, #1
	b	.L612
.L635:
	.align	2
.L634:
	.word	.LC106
	.word	g_event_report
	UNWIND(.fnend)
	.size	AVS_DecodeArbiter.part.4, .-AVS_DecodeArbiter.part.4
	.align	2
	.global	AVS_DecodeArbiter
	.type	AVS_DecodeArbiter, %function
AVS_DecodeArbiter:
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
	add	r3, r0, #12288
	ldr	r3, [r3, #2784]
	and	r3, r3, #376832
	cmp	r3, #376832
	beq	.L638
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L638:
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	AVS_DecodeArbiter.part.4
	UNWIND(.fnend)
	.size	AVS_DecodeArbiter, .-AVS_DecodeArbiter
	.align	2
	.global	AVSDEC_VDMPostProc
	.type	AVSDEC_VDMPostProc, %function
AVSDEC_VDMPostProc:
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
	ldr	r2, [r0, #16]
	add	r4, r0, #12288
	mov	r6, r1
	mov	r5, r0
	ldr	r3, [r4, #2756]
	add	r1, r2, #12288
	ldrb	r2, [r2, #48]	@ zero_extendqisi2
	strb	r2, [r3]
	ldr	r2, [r1, #2604]
	str	r2, [r3, #4]
	bl	AVS_ClearCurPic
	ldr	r3, .L698
	add	r0, r5, #20
	movw	r2, #14900
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4, #3148]
	cmp	r3, #0
	bne	.L640
	str	r6, [r4, #3456]
	ldr	r3, [r5, #12]
	ldr	r2, [r4, #3456]
	ldr	r3, [r3]
	cmp	r3, r2
	blt	.L689
.L645:
	mov	r0, r5
	bl	AVS_SetImgFormat
	ldr	r3, [r4, #2756]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L690
	ldr	r1, [r4, #3468]
	mov	r2, #0
	cmp	r1, #0
	strne	r1, [r3, #544]
	movne	r1, #0
	strne	r1, [r3, #548]
	ldr	r1, [r4, #3472]
	str	r2, [r4, #3468]
	cmp	r1, r2
	strne	r2, [r3, #556]
	strne	r1, [r3, #552]
	mov	r2, #0
	ldr	r3, [r4, #3148]
	str	r2, [r4, #3472]
	cmp	r3, #1
	bls	.L691
.L650:
	ldr	r7, [r4, #2756]
.L655:
	ldr	r1, [r7, #12]
	ldr	r0, [r5, #4]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L692
	add	r3, r5, #14912
	add	r3, r3, #12
	cmp	r7, r3
	beq	.L660
	ldr	r3, [r5, #12]
	ldr	r2, [r4, #3456]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	bge	.L658
	ldr	r1, .L698+4
	mov	r0, #1
	add	r4, r6, #544
	bl	dprint_vfmw
	ldr	r1, [r7, #12]
	mov	r2, #0
	ldr	r0, [r5, #4]
	bl	FSP_SetDisplay
	ldrd	r2, [r4]
	orrs	r1, r2, r3
	bne	.L693
.L659:
	add	r6, r6, #560
	ldrd	r2, [r6, #-8]
	orrs	r1, r2, r3
	bne	.L694
.L660:
	mov	r4, #1
.L643:
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L658:
	mov	r0, r7
	mov	r1, r5
	bl	AVS_OutputOneFrame
	subs	r4, r0, #0
	bne	.L660
	add	r7, r6, #544
	ldrd	r2, [r7]
	orrs	r1, r2, r3
	bne	.L695
.L661:
	add	r6, r6, #560
	ldrd	r2, [r6, #-8]
	orrs	r1, r2, r3
	beq	.L643
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r6, #-8]
	b	.L643
.L640:
	ldr	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r3, r0, #0
	beq	.L696
	ldr	r2, [r4, #2764]
	ldr	r0, [r5, #4]
	ldr	r7, [r3, #152]
	ldr	r1, [r2, #12]
	bl	FSP_GetFsImagePtr
	subs	ip, r0, #0
	beq	.L697
	ldr	r3, [ip, #152]
	ldr	r2, [r4, #3148]
	add	r3, r7, r3
	add	r6, r6, r3
	cmp	r6, #100
	movge	r6, #100
	str	r6, [r4, #3456]
	ldr	r3, [r5, #12]
	cmp	r2, #2
	ldr	r3, [r3]
	beq	.L645
	ldr	r2, [r4, #3456]
	cmp	r3, r2
	bge	.L645
.L689:
	ldr	r1, .L698+8
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, [r4, #2760]
	mov	r2, #0
	str	r2, [r4, #3452]
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L646
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	add	r8, r6, #560
	add	r7, r6, #576
	add	r9, r6, #544
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2760]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2764]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r3, [r4, #2768]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_ClearLogicFs
	ldr	r1, [r6, #544]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	ldr	r1, [r6, #568]
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	add	r3, r5, #14912
	mov	r0, #0
	mov	r1, #0
	add	r3, r3, #12
	strd	r0, [r9]
	strd	r0, [r8, #-8]
	strd	r0, [r8]
	strd	r0, [r7, #-8]
	str	r3, [r4, #2756]
	str	r3, [r4, #2768]
	str	r3, [r4, #2764]
	str	r3, [r4, #2760]
	ldr	r0, [r5, #4]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #2648]
.L646:
	mov	r3, #0
	str	r3, [r4, #3452]
	mov	r4, r3
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L691:
	ldr	r2, [r4, #3452]
	ldrb	r1, [r4, #2881]	@ zero_extendqisi2
	cmp	r2, #1
	addle	r2, r2, #1
	adds	r3, r3, #0
	str	r2, [r4, #3452]
	movne	r3, #1
	cmp	r1, #1
	orreq	r3, r3, #1
	cmp	r3, #0
	beq	.L652
	ldr	r3, [r4, #2756]
	mov	r2, #1
	ldr	r0, [r5, #4]
	ldr	r1, [r3, #12]
	bl	FSP_SetRef
	add	r3, r5, #14912
	ldr	r2, [r4, #2768]
	add	r3, r3, #12
	cmp	r2, r3
	beq	.L653
	ldr	r1, [r2, #12]
	mov	r2, #0
	ldr	r0, [r5, #4]
	bl	FSP_SetRef
.L653:
	ldr	r1, [r4, #2764]
	ldr	r2, [r4, #2760]
	ldr	r3, [r4, #2756]
	str	r1, [r4, #2768]
	str	r2, [r4, #2764]
	str	r3, [r4, #2760]
.L652:
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	ldreq	r7, [r4, #2764]
	beq	.L655
	b	.L650
.L694:
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r4, #1
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r6, #-8]
	b	.L643
.L693:
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r4]
	b	.L659
.L695:
	mov	r1, r2
	ldr	r0, [r5, #4]
	bl	FreeUsdByDec
	mov	r2, #0
	mov	r3, #0
	strd	r2, [r7]
	b	.L661
.L690:
	movw	r2, #3297
	ldr	r1, .L698+12
	mov	r4, r3
	bl	dprint_vfmw
	b	.L643
.L692:
	movw	r2, #3337
	ldr	r1, .L698+12
	mov	r4, r6
	bl	dprint_vfmw
	b	.L643
.L696:
	movw	r2, #3272
	ldr	r1, .L698+12
	mov	r4, r3
	bl	dprint_vfmw
	b	.L643
.L697:
	movw	r2, #3276
	ldr	r1, .L698+12
	mov	r4, ip
	bl	dprint_vfmw
	b	.L643
.L699:
	.align	2
.L698:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC108
	.word	.LC107
	.word	.LC97
	UNWIND(.fnend)
	.size	AVSDEC_VDMPostProc, .-AVSDEC_VDMPostProc
	.align	2
	.global	ClearPacket
	.type	ClearPacket, %function
ClearPacket:
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
	add	r4, r0, #16384
	mov	r5, r0
	ldr	r0, [r0, #4]
	ldr	r1, [r4, #184]
	bl	SM_ReleaseStreamSeg
	ldrb	r3, [r4, #173]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L701
	ldrb	r3, [r4, #253]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L705
.L701:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L705:
	ldr	r3, [r4, #256]
	cmp	r3, #0
	beq	.L701
	ldr	r1, [r4, #264]
	ldr	r0, [r5, #4]
	bl	SM_ReleaseStreamSeg
	b	.L701
	UNWIND(.fnend)
	.size	ClearPacket, .-ClearPacket
	.align	2
	.global	WriteAvsSliceMsg
	.type	WriteAvsSliceMsg, %function
WriteAvsSliceMsg:
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
	add	ip, r0, #12288
	mov	r4, r0
	ldr	r2, [ip, #2168]
	cmp	r2, #512
	bge	.L717
	cmp	r2, #0
	add	r1, r0, #16384
	ble	.L709
	sub	r3, r2, #1
	ldr	r0, [ip, #3548]
	ldr	r5, [r1, #168]
	mov	lr, r3, asl #5
	add	r0, r0, #15
	sub	r3, lr, r3, asl #2
	ldrb	lr, [r5, #3]	@ zero_extendqisi2
	mov	r0, r0, lsr #4
	add	r3, r4, r3
	mul	r0, lr, r0
	ldr	r3, [r3, #136]
	cmp	r0, r3
	bls	.L718
.L709:
	mov	lr, r2, asl #2
	mov	r5, r2, asl #5
	ldr	r6, [r1, #176]
	rsb	r3, lr, r5
	add	r3, r4, r3
	cmp	r2, #0
	add	r0, r3, #132
	str	r6, [r3, #120]
	ldr	r6, [r1, #184]
	str	r6, [r0, #8]
	ldr	r6, [r1, #180]
	str	r6, [r3, #128]
	streq	r2, [r4, #136]
	bne	.L719
.L711:
	ldrb	r3, [r1, #173]	@ zero_extendqisi2
	rsb	lr, lr, r5
	cmp	r3, #1
	beq	.L720
	ldr	r3, [r1, #256]
	add	r4, r4, lr
	str	r3, [r4, #124]
	ldr	r3, [r1, #264]
	str	r3, [r4, #144]
	ldr	r3, [r1, #260]
	str	r3, [r4, #132]
.L713:
	add	r2, r2, #1
	mov	r0, #1
	str	r2, [ip, #2168]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L719:
	ldr	r6, [r1, #168]
	ldr	r3, [ip, #3548]
	add	r3, r3, #15
	ldrb	r7, [r6, #3]	@ zero_extendqisi2
	mov	r3, r3, lsr #4
	mul	r7, r7, r3
	str	r7, [r0, #4]
	ldr	r3, [ip, #2824]
	ldr	r6, [ip, #2828]
	add	r0, r3, #15
	add	r6, r6, #15
	mov	r3, r0, lsr #4
	mov	r6, r6, lsr #4
	mul	r3, r3, r6
	sub	r3, r3, #1
	cmp	r7, r3
	bls	.L711
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L717:
	mov	r3, #512
	ldr	r1, .L721
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L718:
	mov	r2, r0
	ldr	r1, .L721+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L720:
	add	r4, r4, lr
	mov	r3, #0
	add	r4, r4, #128
	str	r3, [r4, #-4]
	str	r3, [r4, #16]
	str	r3, [r4, #4]
	b	.L713
.L722:
	.align	2
.L721:
	.word	.LC109
	.word	.LC110
	UNWIND(.fnend)
	.size	WriteAvsSliceMsg, .-WriteAvsSliceMsg
	.align	2
	.global	AVS_GetPacketState
	.type	AVS_GetPacketState, %function
AVS_GetPacketState:
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
	ldr	r0, [r0, #160]
	subs	r0, r0, #1
	movne	r0, #1
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_GetPacketState, .-AVS_GetPacketState
	.align	2
	.global	Avs_Vfmw_WQMatrix
	.type	Avs_Vfmw_WQMatrix, %function
Avs_Vfmw_WQMatrix:
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
	UNWIND(.pad #308)
	sub	sp, sp, #308
	ldr	r8, [r0, #148]
	mov	r3, #0
	ldr	lr, [r0, #132]
	cmp	r8, #1
	str	r3, [fp, #-348]
	str	r3, [fp, #-344]
	str	r3, [fp, #-340]
	str	r3, [fp, #-336]
	str	r3, [fp, #-332]
	str	r3, [fp, #-328]
	beq	.L727
	clz	r3, lr
	cmp	r8, #3
	cmpeq	lr, #0
	mov	r3, r3, lsr #5
	beq	.L727
	cmp	r8, #2
	addeq	r3, r0, #176
	beq	.L729
	cmp	r3, #0
	bne	.L761
.L762:
	sub	r4, fp, #324
	cmp	r8, #0
	mov	r3, #128
	strh	r3, [r4]	@ movhi
	strh	r3, [r4, #2]	@ movhi
	strh	r3, [r4, #4]	@ movhi
	strh	r3, [r4, #6]	@ movhi
	strh	r3, [r4, #8]	@ movhi
	strh	r3, [r4, #10]	@ movhi
	strh	r3, [r4, #12]	@ movhi
	strh	r3, [r4, #14]	@ movhi
	strh	r3, [r4, #16]	@ movhi
	strh	r3, [r4, #18]	@ movhi
	strh	r3, [r4, #20]	@ movhi
	strh	r3, [r4, #22]	@ movhi
	bne	.L811
	ldr	r3, .L817
	add	r2, r4, #10
	add	ip, r3, #12
.L743:
	ldrh	r1, [r3, #2]!
	cmp	r3, ip
	strh	r1, [r2, #2]!	@ movhi
	bne	.L743
.L736:
	add	ip, r0, #202
	add	lr, r0, #328
	add	lr, lr, #2
	mov	r2, #128
	mov	r3, ip
.L747:
	strh	r2, [r3, #2]!	@ movhi
	cmp	r3, lr
	bne	.L747
	ldr	r3, [r0, #128]
	cmp	r3, #0
	beq	.L764
	ldr	r10, [r0, #152]
	mov	r9, #0
	ldr	r3, .L817+4
	mov	r10, r10, asl #6
	add	r7, r10, #64
	add	r10, r3, r10
	add	r7, r3, r7
.L765:
	sub	r3, fp, #300
	mov	r5, r9, asl #3
	add	r6, r3, r9, lsl #7
	sub	r5, r5, r9, asl #1
	sub	r6, r6, #2
	mov	r2, r10
.L755:
	add	r0, r2, #8
	mov	r1, r6
.L753:
	ldrb	r3, [r2], #1	@ zero_extendqisi2
	add	r3, r5, r3
	cmp	r0, r2
	mov	r3, r3, asl #1
	ldrh	r3, [r4, r3]
	strh	r3, [r1, #2]!	@ movhi
	bne	.L753
	cmp	r0, r7
	add	r6, r6, #16
	mov	r2, r0
	bne	.L755
	add	r9, r9, #1
	cmp	r9, #2
	bne	.L765
.L751:
	cmp	r8, #0
	subeq	r3, fp, #174
	subeq	r1, fp, #46
	beq	.L756
	cmp	r8, #1
	beq	.L812
	cmp	r8, #2
	beq	.L813
.L724:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L727:
	ldr	r4, .L817+8
	add	r1, r0, #152
	sub	ip, fp, #348
	add	r3, r0, #176
.L726:
	ldr	r5, [r1, #4]!
	ldrh	r2, [r4], #2
	cmp	r1, r3
	add	r2, r2, r5
	strh	r2, [ip], #2	@ movhi
	bne	.L726
	cmp	r8, #2
	beq	.L729
	cmp	lr, #0
	cmpeq	r8, #3
	bne	.L730
.L729:
	ldr	ip, .L817
	sub	r1, fp, #336
	add	r5, r0, #200
.L731:
	ldr	r4, [r3, #4]!
	ldrh	r2, [ip, #2]!
	cmp	r3, r5
	add	r2, r2, r4
	strh	r2, [r1], #2	@ movhi
	bne	.L731
.L730:
	cmp	lr, #0
	bne	.L762
.L761:
	ldr	r3, .L817+8
	sub	r4, fp, #324
	add	ip, r3, #12
	mov	r5, r4
	mov	r2, r4
.L734:
	ldrh	r1, [r3], #2
	cmp	r3, ip
	strh	r1, [r2], #2	@ movhi
	bne	.L734
	ldr	r3, .L817
	add	lr, r4, #10
	add	ip, r3, #12
	mov	r2, lr
.L735:
	ldrh	r1, [r3, #2]!
	cmp	r3, ip
	strh	r1, [r2, #2]!	@ movhi
	bne	.L735
	cmp	r8, #0
	beq	.L736
	cmp	r8, #1
	beq	.L814
	cmp	r8, #2
	beq	.L815
	cmp	r8, #3
	bne	.L736
	sub	r3, fp, #348
	sub	r1, fp, #336
.L741:
	ldrh	r2, [r3], #2
	cmp	r3, r1
	strh	r2, [r5], #2	@ movhi
	bne	.L741
	add	r1, r4, #22
.L742:
	ldrh	r2, [r3], #2
	strh	r2, [lr, #2]!	@ movhi
	cmp	lr, r1
	bne	.L742
	b	.L736
.L756:
	ldrh	r2, [r3, #2]!
	cmp	r3, r1
	strh	r2, [ip, #2]!	@ movhi
	beq	.L724
	ldrh	r2, [r3, #2]!
	cmp	r3, r1
	strh	r2, [ip, #2]!	@ movhi
	bne	.L756
	b	.L724
.L764:
	sub	r0, fp, #174
	add	r4, fp, #82
	mov	r1, #128
.L766:
	sub	r3, r0, #128
.L752:
	add	r2, r3, #16
.L749:
	strh	r1, [r3, #2]!	@ movhi
	cmp	r2, r3
	bne	.L749
	cmp	r2, r0
	mov	r3, r2
	bne	.L752
	add	r0, r0, #128
	cmp	r0, r4
	bne	.L766
	b	.L751
.L811:
	cmp	r8, #1
	beq	.L816
	cmp	r8, #2
	bne	.L736
	sub	r2, fp, #336
	add	r3, r4, #10
	add	ip, r4, #22
.L746:
	ldrh	r1, [r2], #2
	strh	r1, [r3, #2]!	@ movhi
	cmp	r3, ip
	bne	.L746
	b	.L736
.L816:
	sub	r3, fp, #348
	sub	ip, fp, #336
	mov	r2, r4
.L745:
	ldrh	r1, [r3], #2
	cmp	r3, ip
	strh	r1, [r2], #2	@ movhi
	bne	.L745
	b	.L736
.L814:
	sub	r3, fp, #348
	sub	r1, fp, #336
.L738:
	ldrh	r2, [r3], #2
	cmp	r3, r1
	strh	r2, [r5], #2	@ movhi
	bne	.L738
	b	.L736
.L813:
	sub	r3, fp, #174
	sub	r1, fp, #46
.L760:
	ldrh	r2, [r3, #2]!
	cmp	r3, r1
	strh	r2, [ip, #2]!	@ movhi
	bne	.L760
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L812:
	sub	r3, fp, #300
	sub	r3, r3, #2
.L758:
	ldrh	r2, [r3, #2]!
	strh	r2, [ip, #2]!	@ movhi
	cmp	lr, ip
	bne	.L758
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L815:
	sub	r3, fp, #336
	add	r1, r4, #22
.L740:
	ldrh	r2, [r3], #2
	strh	r2, [lr, #2]!	@ movhi
	cmp	lr, r1
	bne	.L740
	b	.L736
.L818:
	.align	2
.L817:
	.word	.LANCHOR1+10
	.word	.LANCHOR0+80
	.word	.LANCHOR1
	UNWIND(.fnend)
	.size	Avs_Vfmw_WQMatrix, .-Avs_Vfmw_WQMatrix
	.align	2
	.global	AVS_ParseHeader
	.type	AVS_ParseHeader, %function
AVS_ParseHeader:
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
	add	r7, r0, #12288
	add	r8, r0, #16384
	mov	r3, #0
	add	r9, r0, #14912
	ldr	r6, [r7, #3176]
	add	r5, r0, #15808
	str	r3, [r8, #160]
	mov	r4, r0
	mov	r1, #32
	add	r9, r9, #8
	mov	r0, r6
	add	r5, r5, #4
	bl	BsShow
	uxtb	r0, r0
	sub	r3, r0, #176
	cmp	r3, #78
	ldrls	pc, [pc, r3, asl #2]
	b	.L820
.L822:
	.word	.L821
	.word	.L823
	.word	.L824
	.word	.L825
	.word	.L826
	.word	.L827
	.word	.L828
	.word	.L829
	.word	.L826
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L820
	.word	.L830
.L820:
	cmp	r0, #175
	bhi	.L826
	ldr	r3, [r7, #2784]
	and	r2, r3, #327680
	cmp	r2, #327680
	beq	.L867
.L826:
	mov	r0, r4
	bl	ClearPacket
.L863:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L825:
	ldr	r3, [r7, #2784]
	ands	r6, r3, #32768
	bne	.L861
	tst	r3, #262144
	beq	.L835
	bic	r3, r3, #311296
	mov	r0, r9
	str	r3, [r7, #2784]
	mov	r1, r5
	bl	AVS_i_picture_header
	b	.L865
.L827:
	ldr	r3, [r7, #2784]
	tst	r3, #327680
	beq	.L839
	mov	r1, r5
	mov	r0, r9
	bl	AVS_extension
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L828:
	ldr	r3, [r7, #2784]
	ands	r6, r3, #32768
	bne	.L861
	tst	r3, #262144
	beq	.L837
	bic	r3, r3, #311296
	mov	r0, r9
	str	r3, [r7, #2784]
	mov	r1, r5
	bl	AVS_pb_picture_header
.L865:
	mov	r0, r5
	bl	Avs_Vfmw_WQMatrix
	mov	r0, r4
	bl	ClearPacket
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L829:
	ldr	r3, [r7, #2784]
	ands	r5, r3, #32768
	bne	.L860
	tst	r3, #327680
	beq	.L863
.L866:
	bic	r3, r3, #311296
	mov	r0, r4
	str	r3, [r7, #2784]
	bl	ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L830:
	mov	r1, #32
	mov	r0, r6
	bl	BsSkip
	mov	r1, #32
	mov	r0, r6
	bl	BsGet
	mov	r1, #32
	mov	r5, r0
	mov	r0, r6
	bl	BsGet
	movw	r2, #20036
	movw	r3, #20553
	movt	r2, 17221
	movt	r3, 18515
	cmp	r0, r2
	cmpeq	r5, r3
	bne	.L839
	mov	r5, #1
	strb	r5, [r4]
	str	r5, [r8, #160]
	mov	r0, r4
	ldr	r3, [r7, #2784]
	orr	r3, r3, #16384
	str	r3, [r7, #2784]
	bl	ClearPacket
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L823:
	ldr	r3, [r7, #2784]
	ands	r5, r3, #32768
	bne	.L860
	tst	r3, #327680
	beq	.L826
	b	.L866
.L824:
	ldr	r3, [r7, #2784]
	ands	r1, r3, #262144
	movne	r1, #1
	bne	.L862
	tst	r3, #65536
	beq	.L839
.L862:
	mov	r0, r4
	bl	AVS_user_data
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L821:
	ldr	r3, [r7, #2784]
	ands	r6, r3, #32768
	bne	.L860
	tst	r3, #65536
	beq	.L833
	bic	r3, r3, #311296
	mov	r1, r5
	str	r3, [r7, #2784]
	mov	r0, r4
	bl	AVS_sequence_header
	mov	r0, r4
	bl	ClearPacket
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L867:
	orr	r3, r3, #32768
	mov	r0, r4
	str	r3, [r7, #2784]
	bl	WriteAvsSliceMsg
	cmp	r0, #0
	bne	.L863
.L839:
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L860:
	mov	r0, #1
	orr	r3, r3, #16384
	str	r0, [r8, #160]
	str	r3, [r7, #2784]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L837:
	mov	r0, r9
	mov	r1, r5
	bl	AVS_pb_picture_header
.L864:
	mov	r0, r5
	bl	Avs_Vfmw_WQMatrix
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L835:
	mov	r0, r9
	mov	r1, r5
	bl	AVS_i_picture_header
	b	.L864
.L833:
	mov	r1, r5
	mov	r0, r4
	bl	AVS_sequence_header
	mov	r0, r4
	bl	ClearPacket
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L861:
	orr	r3, r3, #16384
	mov	r0, r5
	mov	r4, #1
	str	r4, [r8, #160]
	str	r3, [r7, #2784]
	bl	Avs_Vfmw_WQMatrix
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	AVS_ParseHeader, .-AVS_ParseHeader
	.align	2
	.global	AVSDEC_Decode
	.type	AVSDEC_Decode, %function
AVSDEC_Decode:
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
	add	r0, r0, #15744
	mov	r5, r1
	ldr	r2, [r1, #12]
	add	r0, r0, #36
	ldr	r1, [r1]
	bl	BsInit
	ldr	r3, .L883
	add	r6, r4, #12288
	add	r0, r4, #16384
	mov	r1, r5
	mov	r2, #160
	ldr	r3, [r3, #52]
	add	r0, r0, #168
	blx	r3
	ldr	r3, [r6, #2784]
	mov	r0, r4
	str	r3, [r6, #3488]
	bl	AVS_ParseHeader
	subs	r5, r0, #0
	beq	.L881
	ldr	r3, [r6, #2784]
	and	r3, r3, #376832
	cmp	r3, #376832
	beq	.L871
.L872:
	mov	r5, #0
.L870:
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L881:
	ldr	r1, .L883+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	AVS_ClearCurPic
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L871:
	mov	r0, r4
	bl	AVS_DecodeArbiter.part.4
	cmp	r0, #0
	beq	.L872
	mov	r0, r4
	bl	AVS_GetStreamInf
	cmp	r0, #3
	beq	.L873
	adds	r5, r0, #0
	movne	r5, #1
	cmp	r5, #0
	beq	.L882
	mov	r0, r4
	bl	AVS_StartDecode
	subs	r6, r0, #0
	bne	.L870
	ldr	r1, .L883+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	AVS_ClearCurPic
	mov	r5, r6
	b	.L870
.L882:
	ldr	r1, .L883+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	bl	AVS_ClearCurPic
	b	.L870
.L873:
	ldr	r3, [r6, #3488]
	mov	r5, r0
	str	r3, [r6, #2784]
	b	.L870
.L884:
	.align	2
.L883:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC111
	.word	.LC113
	.word	.LC112
	UNWIND(.fnend)
	.size	AVSDEC_Decode, .-AVSDEC_Decode
	.global	g_tmp
	.global	wq_param_default
	.global	g_AvsCfg
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	24551
	.word	24576
	.word	25600
	.word	30689
	.word	30720
	.word	51200
	.word	61378
	.word	61440
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.type	CSWTCH.56, %object
	.size	CSWTCH.56, 16
CSWTCH.56:
	.word	5
	.word	1
	.word	2
	.word	3
	.type	WeightQuantModel, %object
	.size	WeightQuantModel, 256
WeightQuantModel:
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	4
	.byte	5
	.byte	5
	.byte	0
	.byte	3
	.byte	2
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	5
	.byte	5
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	0
	.byte	0
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	0
	.byte	4
	.byte	4
	.byte	3
	.byte	2
	.byte	1
	.byte	5
	.byte	5
	.byte	3
	.byte	3
	.byte	3
	.byte	3
	.byte	2
	.byte	5
	.byte	5
	.byte	5
	.byte	2
	.byte	2
	.byte	2
	.byte	2
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	1
	.byte	1
	.byte	1
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.byte	5
	.data
	.align	2
.LANCHOR1 = . + 0
	.type	wq_param_default, %object
	.size	wq_param_default, 24
wq_param_default:
	.short	135
	.short	143
	.short	143
	.short	160
	.short	160
	.short	213
	.short	128
	.short	98
	.short	106
	.short	116
	.short	116
	.short	128
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"%-40s     %#-8x(%db)\012\000" )
	.space	2
.LC1:
	ASCII(.ascii	"video_sequence_start_code\000" )
	.space	2
.LC2:
	ASCII(.ascii	"profile_id\000" )
	.space	1
.LC3:
	ASCII(.ascii	"level_id\000" )
	.space	3
.LC4:
	ASCII(.ascii	"progressive_sequence\000" )
	.space	3
.LC5:
	ASCII(.ascii	"horizontal_size\000" )
.LC6:
	ASCII(.ascii	"vertical_size\000" )
	.space	2
.LC7:
	ASCII(.ascii	"chroma_format\000" )
	.space	2
.LC8:
	ASCII(.ascii	"sample_precision\000" )
	.space	3
.LC9:
	ASCII(.ascii	"aspect_ratio\000" )
	.space	3
.LC10:
	ASCII(.ascii	"frame_rate_code\000" )
.LC11:
	ASCII(.ascii	"bit_rate_lower\000" )
	.space	1
.LC12:
	ASCII(.ascii	"marker_bit\000" )
	.space	1
.LC13:
	ASCII(.ascii	"bit_rate_upper\000" )
	.space	1
.LC14:
	ASCII(.ascii	"low_delay\000" )
	.space	2
.LC15:
	ASCII(.ascii	"bbv_buffer_size\000" )
.LC16:
	ASCII(.ascii	"reserved_bits\000" )
	.space	2
.LC17:
	ASCII(.ascii	"i_picture_start_code\000" )
	.space	3
.LC18:
	ASCII(.ascii	"bbv_delay\000" )
	.space	2
.LC19:
	ASCII(.ascii	"bbv_delay_extension\000" )
.LC20:
	ASCII(.ascii	"time_code_flag\000" )
	.space	1
.LC21:
	ASCII(.ascii	"time_code\000" )
	.space	2
.LC22:
	ASCII(.ascii	"picture_distance\000" )
	.space	3
.LC23:
	ASCII(.ascii	"bbv_check_times\000" )
.LC24:
	ASCII(.ascii	"progressive_frame\000" )
	.space	2
.LC25:
	ASCII(.ascii	"picture_structure\000" )
	.space	2
.LC26:
	ASCII(.ascii	"top_field_first\000" )
.LC27:
	ASCII(.ascii	"repeat_first_field\000" )
	.space	1
.LC28:
	ASCII(.ascii	"fixed_picture_qp\000" )
	.space	3
.LC29:
	ASCII(.ascii	"picture_qp\000" )
	.space	1
.LC30:
	ASCII(.ascii	"skip_mode_flag\000" )
	.space	1
.LC31:
	ASCII(.ascii	"loop_filter_disable\000" )
.LC32:
	ASCII(.ascii	"loop_filter_parameter_flag\000" )
	.space	1
.LC33:
	ASCII(.ascii	"alpha_c_offset\000" )
	.space	1
.LC34:
	ASCII(.ascii	"beta_offset\000" )
.LC35:
	ASCII(.ascii	"weighting_quant_flag\000" )
	.space	3
.LC36:
	ASCII(.ascii	"aec_enable\000" )
	.space	1
.LC37:
	ASCII(.ascii	"mb_adapt_weighting_quant_disable\000" )
	.space	3
.LC38:
	ASCII(.ascii	"chroma_quant_param_disable\000" )
	.space	1
.LC39:
	ASCII(.ascii	"chroma_quant_param_delta_u\000" )
	.space	1
.LC40:
	ASCII(.ascii	"chroma_quant_param_delta_v\000" )
	.space	1
.LC41:
	ASCII(.ascii	"weighting_quant_param_index\000" )
.LC42:
	ASCII(.ascii	"weighting_quant_model\000" )
	.space	2
.LC43:
	ASCII(.ascii	"weighting_quant_param_deltal1\000" )
	.space	2
.LC44:
	ASCII(.ascii	"weighting_quant_param_deltal2\000" )
	.space	2
.LC45:
	ASCII(.ascii	"pb_picture_start_code\000" )
	.space	2
.LC46:
	ASCII(.ascii	"picture_coding_type\000" )
.LC47:
	ASCII(.ascii	"advanced_pred_mode_disable\000" )
	.space	1
.LC48:
	ASCII(.ascii	"picture_reference_flag\000" )
	.space	1
.LC49:
	ASCII(.ascii	"no_forward_reference_flag\000" )
	.space	2
.LC50:
	ASCII(.ascii	"b_filed_enhanced_flag\000" )
	.space	2
.LC51:
	ASCII(.ascii	"p_filed_enhanced_flag\000" )
	.space	2
.LC52:
	ASCII(.ascii	"user_data_start_code\000" )
	.space	3
.LC53:
	ASCII(.ascii	"extension_ID\000" )
	.space	3
.LC54:
	ASCII(.ascii	"video_format\000" )
	.space	3
.LC55:
	ASCII(.ascii	"sample_range\000" )
	.space	3
.LC56:
	ASCII(.ascii	"colour_description\000" )
	.space	1
.LC57:
	ASCII(.ascii	"colour_primaries\000" )
	.space	3
.LC58:
	ASCII(.ascii	"transfer_characteristics\000" )
	.space	3
.LC59:
	ASCII(.ascii	"matrix_coefficients\000" )
.LC60:
	ASCII(.ascii	"display_horizontal_size\000" )
.LC61:
	ASCII(.ascii	"display_vertical_size\000" )
	.space	2
.LC62:
	ASCII(.ascii	"copyright_flag\000" )
	.space	1
.LC63:
	ASCII(.ascii	"copyright_id\000" )
	.space	3
.LC64:
	ASCII(.ascii	"original_or_copy\000" )
	.space	3
.LC65:
	ASCII(.ascii	"copyright_number_1\000" )
	.space	1
.LC66:
	ASCII(.ascii	"copyright_number_2\000" )
	.space	1
.LC67:
	ASCII(.ascii	"copyright_number_3\000" )
	.space	1
.LC68:
	ASCII(.ascii	"camera_id\000" )
	.space	2
.LC69:
	ASCII(.ascii	"height_of_image_device\000" )
	.space	1
.LC70:
	ASCII(.ascii	"focal_length\000" )
	.space	3
.LC71:
	ASCII(.ascii	"f_number\000" )
	.space	3
.LC72:
	ASCII(.ascii	"vertical_angle_of_view\000" )
	.space	1
.LC73:
	ASCII(.ascii	"camera_position_x_upper\000" )
.LC74:
	ASCII(.ascii	"camera_position_x_lower\000" )
.LC75:
	ASCII(.ascii	"camera_position_y_upper\000" )
.LC76:
	ASCII(.ascii	"camera_position_y_lower\000" )
.LC77:
	ASCII(.ascii	"camera_position_z_upper\000" )
.LC78:
	ASCII(.ascii	"camera_position_z_lower\000" )
.LC79:
	ASCII(.ascii	"camera_direction_x\000" )
	.space	1
.LC80:
	ASCII(.ascii	"camera_direction_y\000" )
	.space	1
.LC81:
	ASCII(.ascii	"camera_direction_z\000" )
	.space	1
.LC82:
	ASCII(.ascii	"image_plane_vertical_x\000" )
	.space	1
.LC83:
	ASCII(.ascii	"image_plane_vertical_y\000" )
	.space	1
.LC84:
	ASCII(.ascii	"image_plane_vertical_z\000" )
	.space	1
.LC85:
	ASCII(.ascii	"frame_centre_horizontal_offset\000" )
	.space	1
.LC86:
	ASCII(.ascii	"frame_centre_vertical_offset\000" )
	.space	3
.LC87:
	ASCII(.ascii	"extension_start_code\000" )
	.space	3
.LC88:
	ASCII(.ascii	"ERROR: image size abnormal(%dx%d)\012\000" )
	.space	1
.LC89:
	ASCII(.ascii	"avs actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC90:
	ASCII(.ascii	"ERROR: partition fs memory fail!\012\000" )
	.space	2
.LC91:
	ASCII(.ascii	"ERROR: FSP_ConfigInstance fail!\012\000" )
	.space	3
.LC92:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC93:
	ASCII(.ascii	"line: %d pImage is null\012\000" )
	.space	3
.LC94:
	ASCII(.ascii	"ERROR: get frame store fail!\012\000" )
	.space	2
.LC95:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC96:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC97:
	ASCII(.ascii	"line: %d\012\000" )
	.space	2
.LC98:
	ASCII(.ascii	"ERROR: AVS_OutputOneFrame is err(%d)\012\000" )
	.space	2
.LC99:
	ASCII(.ascii	"size change\012\000" )
	.space	3
.LC100:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC101:
	ASCII(.ascii	"MbWidth = %d, MbHeight = %d, don't support!\012\000" )
	.space	3
.LC102:
	ASCII(.ascii	"ERROR: allocate vhb\012\000" )
	.space	3
.LC103:
	ASCII(.ascii	"ERROR: get img buf err\012\000" )
.LC104:
	ASCII(.ascii	"dec_pts: %lld Usertag = %lld\012\000" )
	.space	2
.LC105:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC106:
	ASCII(.ascii	"-----Pic %5d, type %d, struct %d-----\012\000" )
	.space	1
.LC107:
	ASCII(.ascii	"ERROR: err_level(%d) over ref_thr(%d)\012\000" )
	.space	1
.LC108:
	ASCII(.ascii	"ERROR: err_level(%d) over out_thr(%d)\012\000" )
	.space	1
.LC109:
	ASCII(.ascii	"SlcNum %d > %d Write slice msg failed\012\000" )
	.space	1
.LC110:
	ASCII(.ascii	"This slice's start mbn %d <= LastSliceFirstMb %d, W" )
	ASCII(.ascii	"rite slice msg failed\012\000" )
	.space	2
.LC111:
	ASCII(.ascii	"ERROR: paseHeader err\012\000" )
	.space	1
.LC112:
	ASCII(.ascii	"ERROR: AVS_PrepareDecode err\012\000" )
	.space	2
.LC113:
	ASCII(.ascii	"ERROR: AVS_StartDecode err\012\000" )
	.bss
	.align	2
	.type	g_tmp, %object
	.size	g_tmp, 1024
g_tmp:
	.space	1024
	.type	g_AvsCfg, %object
	.size	g_AvsCfg, 508
g_AvsCfg:
	.space	508
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
