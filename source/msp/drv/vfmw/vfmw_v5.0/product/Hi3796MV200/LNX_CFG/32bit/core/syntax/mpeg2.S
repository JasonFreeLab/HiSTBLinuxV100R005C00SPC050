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
	.file	"mpeg2.c"
	.text
	.align	2
	.type	MP2_SearchStartCode.part.2, %function
MP2_SearchStartCode.part.2:
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
	add	r3, r0, #2
	add	ip, r0, r1
.L12:
	cmp	ip, r3
	bls	.L2
.L15:
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #1
	bls	.L14
.L8:
	add	r3, r3, #3
	cmp	ip, r3
	bhi	.L15
.L2:
	sub	r0, r1, #3
	ldmfd	sp, {fp, sp, pc}
.L14:
	cmp	r2, #0
	bne	.L5
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #1
	beq	.L12
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	cmp	r2, #0
	addeq	r3, r3, #2
	addne	r3, r3, #4
	b	.L12
.L5:
	cmp	r2, #1
	bne	.L12
	ldrb	r2, [r3, #-2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L8
	ldrb	r2, [r3, #-1]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L8
	rsb	r3, r0, r3
	sub	r0, r3, #2
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_SearchStartCode.part.2, .-MP2_SearchStartCode.part.2
	.align	2
	.global	MP2_VerifyMemPara
	.type	MP2_VerifyMemPara, %function
MP2_VerifyMemPara:
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
	.size	MP2_VerifyMemPara, .-MP2_VerifyMemPara
	.align	2
	.global	MP2_ArrangeVHBMem
	.type	MP2_ArrangeVHBMem, %function
MP2_ArrangeVHBMem:
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
	add	r5, r0, #86016
	mov	r4, r0
	ldr	r3, [r5, #2168]
	ldr	r2, [r3, #56]
	ldr	r3, [r3, #60]
	cmp	r2, #31
	bls	.L19
	sub	r0, r3, #32
	movw	r1, #8160
	cmp	r2, #8192
	cmpls	r0, r1
	bhi	.L19
	ldr	r0, [r4]
	ldr	r1, [r0, #28]
	cmp	r1, #25
	beq	.L44
	mov	r7, r2
	mov	r8, r3
	mov	r10, #5
	mov	r6, #2
	mov	r9, #3
.L28:
	ldr	r3, .L47
	mov	r2, #20
	mov	r1, #0
	sub	r0, fp, #64
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r3, [r4]
	str	r7, [fp, #-60]
	str	r8, [fp, #-56]
	ldr	r2, [r3, #28]
	str	r7, [fp, #-52]
	cmp	r2, #24
	str	r8, [fp, #-48]
	beq	.L33
	uxtb	r1, r6
	strb	r9, [fp, #-63]
	strb	r10, [fp, #-62]
.L39:
	ldr	r2, [r3, #684]
	ldr	r3, [r3, #688]
	mul	r0, r8, r7
	strb	r1, [fp, #-61]
	mul	ip, r3, r2
	cmp	r0, ip
	ble	.L34
	stmia	sp, {r7, r8}
	mov	r0, #0
	ldr	r1, .L47+4
	bl	dprint_vfmw
	ldr	r3, .L47+8
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r0, #0
	beq	.L43
	mov	r3, #0
	ldr	r0, [r5, #2528]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	mvn	r0, #0
	b	.L43
.L19:
	ldr	r1, .L47+12
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
.L43:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L34:
	sub	r1, fp, #64
	ldr	r0, [r5, #2528]
	bl	FSP_ConfigInstance
	cmp	r0, #0
	bne	.L35
	ldr	r1, [r4]
	sub	r3, fp, #68
	ldr	r0, [r5, #2528]
	ldr	r2, [r1, #20]
	ldr	r1, [r1, #16]
	bl	FSP_ConfigFrameBuf
	cmp	r0, #2
	beq	.L45
	cmp	r0, #0
	moveq	r0, #1
	beq	.L43
.L37:
	ldr	r1, .L47+16
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L43
.L44:
	ldr	r1, [r0, #724]
	cmp	r1, #0
	beq	.L46
	ldr	r1, [r0, #684]
	ldr	ip, [r0, #688]
	cmp	r2, r1
	bhi	.L30
	cmp	r3, ip
	bhi	.L30
	ldr	r1, [r0, #712]
	mov	r7, r2
	ldr	r2, [r0, #708]
	mov	r8, r3
	cmp	r1, #0
	add	r9, r2, #2
	beq	.L41
	add	r1, r2, #1
	cmp	r1, #17
	movlt	r6, r1
	movge	r6, #17
.L32:
	ldrb	r10, [r0, #732]	@ zero_extendqisi2
	b	.L28
.L35:
	ldr	r1, .L47+20
	mov	r0, #0
	bl	dprint_vfmw
	mov	r0, #0
	b	.L43
.L46:
	ldr	r7, [r0, #684]
	ldr	r8, [r0, #688]
	cmp	r2, r7
	bhi	.L25
	cmp	r3, r8
	bhi	.L25
	ldr	r2, [r0, #712]
	ldr	r3, [r0, #708]
	cmp	r2, #0
	add	r9, r3, #2
	beq	.L41
	add	r1, r3, #1
	cmp	r1, #17
	movlt	r6, r1
	movge	r6, #17
	b	.L32
.L33:
	mov	r1, #1
	strb	r10, [fp, #-62]
	strb	r1, [fp, #-63]
	b	.L39
.L30:
	stmia	sp, {r1, ip}
	mov	r0, #0
	ldr	r1, .L47+24
	bl	dprint_vfmw
	mov	r0, #0
	b	.L43
.L41:
	mov	r6, #1
	b	.L32
.L25:
	stmia	sp, {r7, r8}
	mov	r0, #0
	ldr	r1, .L47+24
	bl	dprint_vfmw
	mov	r0, #0
	b	.L43
.L45:
	add	r0, r4, #88064
	add	r0, r0, #128
	bl	ResetVoQueue
	b	.L37
.L48:
	.align	2
.L47:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC3
	.word	g_event_report
	.word	.LC1
	.word	.LC4
	.word	.LC5
	.word	.LC2
	UNWIND(.fnend)
	.size	MP2_ArrangeVHBMem, .-MP2_ArrangeVHBMem
	.align	2
	.global	MP2_DecodingDecide
	.type	MP2_DecodingDecide, %function
MP2_DecodingDecide:
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
	add	r4, r0, #86016
	mov	r5, r0
	ldr	r3, [r4, #828]
	ldr	r7, [r4, #2168]
	tst	r3, #8388608
	mvneq	r6, #0
	bne	.L126
.L50:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L126:
	ldrb	r2, [r7, #17]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L51
	ldr	r2, [r4, #840]
	cmp	r2, #1
	beq	.L51
	ands	r6, r3, #255
	beq	.L53
.L129:
	ldr	r2, .L145
	ldr	ip, [r2]
	cmp	ip, #0
	beq	.L54
	mov	r3, #0
	mov	r1, #103
	mov	r2, r3
	ldr	r0, [r4, #2528]
	blx	ip
	ldr	r3, [r4, #828]
.L54:
	ldr	r2, [r4, #836]
	mov	r0, #22
	ldr	r1, .L145+4
	mov	r6, #0
	bl	dprint_vfmw
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L53:
	ldr	r3, [r4, #876]
	cmp	r3, #0
	beq	.L127
	ldr	r3, [r4, #816]
	sub	r3, r3, #2
	cmp	r3, #1
	ldr	r3, [r5]
	ldr	r2, [r3, #8]
	bls	.L128
.L57:
	sub	r3, r2, #1
	str	r2, [r4, #816]
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L122
.L64:
	.word	.L63
	.word	.L65
	.word	.L66
	.word	.L67
.L51:
	ldr	r2, [r4, #2532]
	ands	r6, r3, #255
	add	r2, r2, #1
	str	r2, [r4, #2532]
	beq	.L53
	b	.L129
.L67:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	cmp	r10, #1
	beq	.L130
	cmp	r10, #3
	beq	.L131
.L73:
	cmp	r10, #2
	beq	.L77
.L122:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	mov	r3, #1
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	str	r3, [fp, #-52]
.L68:
	ldr	r2, [r4, #836]
	add	r0, r5, #87040
	ldr	r1, [r4, #776]
	add	r0, r0, #48
	ldr	r8, [r4, #880]
	str	r2, [fp, #-48]
	add	r8, r8, r1
	bl	BsPos
	mov	r3, r10
	str	r9, [sp]
	ldr	r2, [fp, #-48]
	ldr	r1, .L145+8
	add	r8, r8, r0, lsr #3
	mov	r0, #18
	str	r8, [sp, #4]
	bl	dprint_vfmw
	ldr	r3, [r4, #828]
	bic	r3, r3, #14155776
	str	r3, [r4, #828]
	ldr	r3, [r5]
	ldr	r0, [r3, #620]
	ldr	r3, [r4, #868]
	cmp	r0, #1
	beq	.L132
	cmp	r3, #0
	bne	.L81
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	sub	r1, r2, #2
	cmp	r1, #1
	bls	.L133
.L82:
	cmp	r2, #3
	beq	.L134
.L79:
	ldr	r1, [r4, #904]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #908]
	mov	r8, r0
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	clz	r3, r8
	mov	r3, r3, lsr #5
	clz	r1, r0
	mov	r1, r1, lsr #5
	orrs	r2, r1, r3
	bne	.L135
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	cmp	r2, #2
	beq	.L136
	cmp	r2, #3
	beq	.L137
.L87:
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	movne	r6, #1
	bne	.L50
	ldrb	r3, [r7, #17]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L93
	ldr	r3, [r4, #840]
	cmp	r3, #0
	bne	.L50
.L93:
	ldrb	r3, [r7, #35]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L138
	ldrb	r3, [r7, #26]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L139
	ldr	r3, [r4, #992]
	add	r3, r3, #1
	str	r3, [r4, #992]
	mov	r3, r3, asl #1
	str	r3, [r4, #988]
.L95:
	ldr	r2, [r4, #984]
	ldr	r3, [r4, #836]
	add	r2, r2, #1
	str	r2, [r4, #984]
	add	r3, r3, #1
	str	r3, [r4, #836]
	b	.L50
.L63:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	cmp	r10, #3
	beq	.L140
.L124:
	mov	r3, #1
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	str	r3, [fp, #-52]
	b	.L68
.L66:
	mov	r3, #0
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	str	r3, [fp, #-52]
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L65:
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	sub	r3, r10, #2
	cmp	r3, #1
	bhi	.L124
	cmp	r10, #2
	beq	.L141
.L71:
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	cmp	r9, #3
	beq	.L142
.L74:
	ldr	r3, [r4, #840]
	mov	r2, #0
	str	r2, [fp, #-52]
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #840]
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L81:
	cmp	r3, #1
	bhi	.L79
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	b	.L82
.L132:
	cmp	r3, #0
	bne	.L79
	ldrb	r2, [r7, #30]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L143
	cmp	r2, #2
	bne	.L79
	ldr	r1, .L145+12
	bl	dprint_vfmw
	b	.L79
.L128:
	cmp	r2, #4
	cmpne	r2, #1
	bhi	.L57
	ldr	r1, .L145+16
	mov	r0, #2
	bl	dprint_vfmw
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L121
	ldr	r3, [r4, #828]
	ldr	r1, [r4, #908]
	orr	r3, r3, #128
	ldr	r0, [r4, #2528]
	str	r3, [r4, #828]
	bl	FSP_GetFsImagePtr
	subs	r8, r0, #0
	beq	.L60
	add	r9, r8, #560
	ldr	r1, [r8, #544]
	ldr	r0, [r4, #2528]
	add	r10, r8, #576
	bl	FreeUsdByDec
	ldr	r1, [r9, #-8]
	ldr	r0, [r4, #2528]
	add	r3, r8, #544
	str	r3, [fp, #-48]
	bl	FreeUsdByDec
	ldr	r1, [r8, #560]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	ldr	r1, [r10, #-8]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-48]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r10, #-8]
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #904]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	str	r6, [r4, #904]
	str	r6, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L144
.L60:
	mov	r3, #0
	str	r3, [r4, #868]
.L121:
	ldr	r3, [r5]
	ldr	r2, [r3, #8]
	b	.L57
.L127:
	ldr	r2, [r4, #836]
	mov	r0, #1
	ldr	r1, .L145+20
	bl	dprint_vfmw
	b	.L50
.L136:
	cmp	r3, #0
	bne	.L85
	ldr	r3, [r5]
	ldr	r2, [r8, #152]
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L87
	ldr	r1, .L145+24
	mov	r0, #1
	bl	dprint_vfmw
	b	.L50
.L135:
	movw	r3, #879
	ldr	r2, .L145+28
	ldr	r1, .L145+32
	mov	r0, #1
	bl	dprint_vfmw
	b	.L50
.L137:
	cmp	r3, #0
	ldr	r3, [r5]
	ldr	r2, [r8, #152]
	ldr	r3, [r3]
	bne	.L89
	cmp	r2, r3
	bhi	.L89
	cmp	r1, #0
	ldr	r2, [r0, #152]
	bne	.L92
	cmp	r3, r2
	bcs	.L87
.L92:
	ldr	r1, .L145+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L50
.L138:
	ldrb	r2, [r7, #24]	@ zero_extendqisi2
	ldrb	r3, [r7, #18]	@ zero_extendqisi2
	ldr	r1, [r4, #992]
	add	r3, r2, r3
	add	r3, r3, #1
	add	r3, r3, r1
	str	r3, [r4, #992]
	mov	r3, r3, asl #1
	str	r3, [r4, #988]
	b	.L95
.L89:
	ldr	r1, .L145+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L50
.L131:
	ldr	r3, [r4, #2540]
	cmp	r3, #0
	bne	.L124
.L76:
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	cmp	r9, #3
	bne	.L74
	mov	r3, #0
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	str	r3, [fp, #-52]
	b	.L68
.L130:
	mov	r3, #0
	str	r3, [r4, #2540]
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	cmp	r10, #3
	bne	.L73
	b	.L76
.L140:
	ldrb	r10, [r7, #17]	@ zero_extendqisi2
	cmp	r10, #3
	bne	.L74
	mov	r3, #0
	mov	r9, r10
	str	r3, [fp, #-52]
	b	.L68
.L139:
	ldr	r2, [r4, #992]
	ldr	r3, [r4, #988]
	add	r2, r2, #1
	str	r2, [r4, #992]
	ldrb	r2, [r7, #24]	@ zero_extendqisi2
	add	r2, r2, #2
	add	r3, r3, r2
	str	r3, [r4, #988]
	b	.L95
.L77:
	mov	r9, #1
	str	r9, [r4, #2540]
	str	r9, [fp, #-52]
	ldrb	r10, [r7, #30]	@ zero_extendqisi2
	ldrb	r9, [r7, #17]	@ zero_extendqisi2
	b	.L68
.L133:
	ldr	r1, .L145+44
	mov	r0, #1
	str	r3, [fp, #-52]
	bl	dprint_vfmw
	b	.L79
.L134:
	ldr	r1, .L145+48
	mov	r0, #1
	bl	dprint_vfmw
	mov	r3, #0
	str	r3, [fp, #-52]
	b	.L79
.L85:
	movw	r3, #889
	ldr	r2, .L145+28
	ldr	r1, .L145+52
	mov	r0, #1
	bl	dprint_vfmw
	b	.L50
.L143:
	ldr	r1, .L145+56
	str	r3, [fp, #-52]
	bl	dprint_vfmw
	b	.L79
.L141:
	add	r3, r5, #45056
	ldrb	r2, [r3, #257]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L71
	ldrb	r9, [r3, #256]	@ zero_extendqisi2
	cmp	r9, #1
	streq	r9, [fp, #-52]
	ldreqb	r9, [r7, #17]	@ zero_extendqisi2
	bne	.L71
	b	.L68
.L142:
	mov	r3, #0
	str	r3, [fp, #-52]
	b	.L68
.L144:
	ldr	r0, [r4, #2528]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #904]
	str	r0, [r4, #908]
	b	.L60
.L146:
	.align	2
.L145:
	.word	g_event_report
	.word	.LC6
	.word	.LC9
	.word	.LC11
	.word	.LC8
	.word	.LC7
	.word	.LC16
	.word	.LANCHOR0
	.word	.LC14
	.word	.LC18
	.word	.LC17
	.word	.LC12
	.word	.LC13
	.word	.LC15
	.word	.LC10
	UNWIND(.fnend)
	.size	MP2_DecodingDecide, .-MP2_DecodingDecide
	.align	2
	.global	MP2_EstimatePicQp
	.type	MP2_EstimatePicQp, %function
MP2_EstimatePicQp:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 128
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #132)
	sub	sp, sp, #132
	mov	r2, #128
	mov	r4, r0
	ldr	r1, .L153
	sub	r0, fp, #148
	bl	memcpy
	add	r3, r4, #86016
	ldr	r0, [r4, #284]
	ldr	r2, [r3, #864]
	cmp	r2, #1
	beq	.L148
	ldr	r3, [r3, #2168]
	ldrb	r3, [r3, #21]	@ zero_extendqisi2
	cmp	r3, #0
	subne	r3, fp, #20
	moveq	r0, r0, asl #1
	addne	r0, r3, r0, lsl #2
	ldrne	r0, [r0, #-128]
.L148:
	sub	sp, fp, #16
	ldmfd	sp, {r4, fp, sp, pc}
.L154:
	.align	2
.L153:
	.word	.LANCHOR0+20
	UNWIND(.fnend)
	.size	MP2_EstimatePicQp, .-MP2_EstimatePicQp
	.align	2
	.global	MP2_GetSequenceInfo
	.type	MP2_GetSequenceInfo, %function
MP2_GetSequenceInfo:
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
	add	r4, r0, #86016
	mov	r3, #0
	mov	r6, r0
	ldr	r2, [r4, #864]
	str	r3, [fp, #-64]
	cmp	r2, #1
	ldr	r5, [r4, #2168]
	ldr	r7, [r4, #2172]
	str	r3, [fp, #-60]
	str	r3, [fp, #-56]
	beq	.L157
	cmp	r2, #2
	bne	.L223
	ldr	r3, [r4, #828]
	and	r3, r3, #1769472
	cmp	r3, #589824
	beq	.L160
.L159:
	ldr	r1, .L233
	mov	r0, #17
	bl	dprint_vfmw
	ldr	r3, [r4, #864]
	cmp	r3, #1
	beq	.L224
.L162:
	ldr	r3, [r5, #56]
	add	r3, r3, #15
	mov	r3, r3, lsr #4
	str	r3, [r5, #64]
	ldr	r2, [r4, #864]
	cmp	r2, #2
	beq	.L225
.L163:
	ldr	r2, [r5, #60]
	add	r2, r2, #15
	mov	r2, r2, lsr #4
.L164:
	mov	r1, #0
	str	r2, [r5, #68]
	str	r1, [r5, #72]
	ldr	r1, [r4, #864]
	cmp	r1, #2
	beq	.L226
.L165:
	ldr	r1, [r4, #876]
	cmp	r1, #0
	beq	.L166
	ldr	r0, [r7, #64]
	cmp	r3, r0
	beq	.L227
.L166:
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	subs	r10, r0, #0
	beq	.L169
	ldr	r1, [r10, #544]
	add	r9, r10, #560
	ldr	r0, [r4, #2528]
	add	r8, r10, #576
	bl	FreeUsdByDec
	ldr	r1, [r10, #552]
	ldr	r0, [r4, #2528]
	add	r3, r10, #544
	str	r3, [fp, #-72]
	bl	FreeUsdByDec
	ldr	r1, [r10, #560]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	ldr	r1, [r10, #568]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	ldr	r3, [fp, #-72]
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r3]
	strd	r0, [r9, #-8]
	strd	r0, [r9]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #904]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2528]
	str	r3, [r4, #904]
	str	r3, [r4, #908]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L228
.L169:
	add	r1, r6, #88064
	mov	r3, #0
	add	r1, r1, #128
	str	r3, [r4, #868]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearNotInVoQueue
	ldr	r3, [r6]
	ldr	r2, [r3, #724]
	cmp	r2, #0
	bne	.L171
	ldr	r3, [r3, #28]
	cmp	r3, #25
	beq	.L229
.L171:
	ldr	r3, [r4, #876]
	cmp	r3, #0
	beq	.L173
	ldr	r3, [r7, #64]
	cmp	r3, #0
	beq	.L173
	ldr	r3, [r7, #68]
	cmp	r3, #0
	bne	.L230
.L173:
	ldr	r0, [r4, #2528]
	bl	FSP_GetFspType
	cmp	r0, #0
	ldrne	r8, .L233+4
	bne	.L174
	sub	r3, fp, #56
	sub	r2, fp, #60
	sub	r1, fp, #64
	ldr	r0, [r4, #2528]
	bl	VCTRL_GetChanImgNum
	ldr	r3, [r6]
	ldr	r2, [r3, #724]
	cmp	r2, #1
	beq	.L231
.L220:
	ldr	r8, .L233+4
.L176:
	mov	r3, #0
	strb	r3, [r4, #2545]
.L174:
	mov	r3, #0
	mov	r0, r6
	mov	r1, r3
	str	r3, [r4, #876]
	str	r3, [r4, #892]
	bl	MP2_ArrangeVHBMem
	ldr	r1, .L233+8
	str	r0, [r4, #876]
	mov	r0, #1
	ldr	r3, [r5, #68]
	ldr	r2, [r5, #64]
	mov	r3, r3, asl #4
	mov	r2, r2, asl #4
	bl	dprint_vfmw
.L172:
	ldr	ip, [r8]
	cmp	ip, #0
	beq	.L221
	ldr	r0, [r5, #68]
	mov	r3, #8
	ldr	r8, [r7, #64]
	sub	r2, fp, #52
	ldr	r6, [r7, #68]
	mov	r1, #2
	ldr	lr, [r5, #64]
	strh	r0, [fp, #-46]	@ movhi
	strh	r8, [fp, #-52]	@ movhi
	strh	r6, [fp, #-50]	@ movhi
	strh	lr, [fp, #-48]	@ movhi
	ldr	r0, [r4, #2528]
	blx	ip
.L221:
	ldr	r1, [r4, #876]
.L167:
	str	r1, [r4, #824]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L223:
	ldr	r3, [r4, #828]
	tst	r3, #3538944
	beq	.L160
	tst	r3, #131072
	mov	r2, #2
	orreq	r3, r3, r2
	streq	r3, [r4, #828]
	tst	r3, #1048576
	str	r2, [r4, #864]
	orreq	r3, r3, #16
	streq	r3, [r4, #828]
	moveq	r2, #2
	movne	r2, #2
	b	.L159
.L160:
	mov	r2, #1
	str	r2, [r4, #864]
	b	.L159
.L157:
	ldr	r3, [r4, #828]
	mov	r1, #18
	bfi	r1, r1, #16, #16
	and	r3, r3, r1
	cmp	r3, #1179648
	moveq	r2, #2
	streq	r2, [r4, #864]
	b	.L159
.L226:
	ldrb	r1, [r5, #35]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L165
	ldr	r1, [r5, #60]
	add	r0, r1, #31
	add	r1, r1, #15
	mov	r0, r0, lsr #5
	mov	r1, r1, lsr #4
	rsb	r1, r1, r0, lsl #1
	str	r1, [r5, #72]
	b	.L165
.L225:
	ldrb	r2, [r5, #35]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L163
	ldr	r2, [r5, #60]
	add	r2, r2, #31
	mov	r2, r2, lsr #5
	mov	r2, r2, asl #1
	b	.L164
.L224:
	mov	r2, #0
	mov	r0, #3
	mov	r1, #5
	strb	r3, [r5, #35]
	strb	r3, [r5, #26]
	strb	r3, [r5, #19]
	strb	r3, [r5, #36]
	strb	r0, [r5, #17]
	str	r1, [r5, #152]
	strb	r2, [r5, #20]
	strb	r2, [r5, #21]
	strb	r2, [r5, #22]
	strb	r2, [r5, #23]
	strb	r2, [r5, #16]
	b	.L162
.L230:
	mov	r3, #0
	ldr	r1, .L233+12
	str	r3, [r4, #876]
	mov	r0, #1
	bl	dprint_vfmw
	b	.L173
.L227:
	ldr	r3, [r7, #68]
	cmp	r2, r3
	bne	.L166
	b	.L167
.L228:
	ldr	r0, [r4, #2528]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #904]
	str	r0, [r4, #908]
	b	.L169
.L229:
	ldr	r9, [r4, #876]
	cmp	r9, #0
	beq	.L213
	ldr	r8, .L233+4
	b	.L172
.L231:
	ldr	r3, [fp, #-56]
	cmp	r3, #0
	ble	.L232
.L177:
	mov	r3, #1
	strb	r3, [r4, #2545]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L232:
	ldr	r3, [fp, #-60]
	cmp	r3, #32
	bgt	.L177
	ldr	r3, [r6, #4]
	cmp	r3, #0
	bne	.L177
	ldr	r3, [r4, #2532]
	cmp	r3, #0
	beq	.L220
	ldr	r1, [r5, #64]
	cmp	r1, #0
	beq	.L220
	ldr	lr, [r5, #68]
	ldr	r0, [r4, #2552]
	cmp	lr, r0
	beq	.L220
	ldr	ip, [r4, #2548]
	cmp	r1, ip
	beq	.L220
	stmib	sp, {r0, r1, lr}
	mov	r0, r2
	str	ip, [sp]
	ldr	r1, .L233+16
	ldr	r8, .L233+4
	bl	dprint_vfmw
	ldr	r3, [r5, #68]
	ldr	ip, [r8]
	str	r3, [r4, #2552]
	ldr	r3, [r5, #64]
	cmp	ip, #0
	str	r3, [r4, #2548]
	beq	.L176
	mov	r3, #0
	mov	r1, #120
	mov	r2, r3
	ldr	r0, [r4, #2528]
	blx	ip
	b	.L176
.L213:
	mov	r0, r6
	mov	r1, r9
	bl	MP2_ArrangeVHBMem
	ldr	r8, .L233+4
	str	r9, [r4, #892]
	str	r0, [r4, #876]
	b	.L172
.L234:
	.align	2
.L233:
	.word	.LC19
	.word	g_event_report
	.word	.LC22
	.word	.LC20
	.word	.LC21
	UNWIND(.fnend)
	.size	MP2_GetSequenceInfo, .-MP2_GetSequenceInfo
	.global	__aeabi_idiv
	.align	2
	.global	MP2_CalcRealEncFrameRate
	.type	MP2_CalcRealEncFrameRate, %function
MP2_CalcRealEncFrameRate:
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
	add	r4, r0, #86016
	ldr	r3, [r4, #2168]
	ldr	r5, [r4, #968]
	ldr	lr, [r4, #980]
	ldrb	r2, [r3, #30]	@ zero_extendqisi2
	ldr	ip, [r3, #80]
	cmp	r2, #1
	ldr	r1, [r4, #976]
	ldr	r2, [r4, #964]
	ldr	r6, [r4, #960]
	ldr	r0, [r4, #972]
	ldmnefd	sp, {r4, r5, r6, r7, fp, sp, pc}
	cmp	ip, #0
	add	r0, r6, r0
	add	r1, r2, r1
	movgt	r2, #1
	movle	r2, #0
	cmp	r0, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r1, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r2, #0
	streq	r2, [r4, #996]
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	ldrb	r3, [r3, #35]	@ zero_extendqisi2
	cmp	r3, #1
	movne	r0, r0, asl #1
	addeq	r1, r5, lr
	mul	r0, ip, r0
	bl	__aeabi_idiv
	movw	r2, #26215
	movt	r2, 26214
	mov	r3, r0, asr #31
	smull	r0, r1, r0, r2
	rsb	r3, r3, r1, asr #2
	str	r3, [r4, #996]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_CalcRealEncFrameRate, .-MP2_CalcRealEncFrameRate
	.align	2
	.global	MP2_CalcDar
	.type	MP2_CalcDar, %function
MP2_CalcDar:
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
	add	r0, r0, #86016
	ldr	r3, [r0, #2168]
	ldr	r3, [r3, #92]
	sub	r3, r3, #1
	cmp	r3, #2
	ldrls	r2, .L243
	addls	r3, r2, r3, lsl #2
	ldrls	r0, [r3, #148]
	movhi	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L244:
	.align	2
.L243:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MP2_CalcDar, .-MP2_CalcDar
	.align	2
	.global	MP2_SetImgFormat
	.type	MP2_SetImgFormat, %function
MP2_SetImgFormat:
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
	add	r6, r0, #86016
	mov	r7, r0
	ldr	r1, [r6, #912]
	ldr	r0, [r6, #2528]
	ldr	r5, [r6, #2168]
	bl	FSP_GetFsImagePtr
	subs	r4, r0, #0
	beq	.L245
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	ldrb	r2, [r5, #35]	@ zero_extendqisi2
	cmp	r3, #4
	ldrb	lr, [r4, #65]	@ zero_extendqisi2
	subne	r3, r3, #1
	ldr	r9, [r5, #136]
	andne	r3, r3, #3
	moveq	r3, #0
	moveq	r10, r3
	ubfx	lr, lr, #2, #2
	uxtbne	r10, r3
	cmp	r2, #0
	ldrb	r2, [r5, #17]	@ zero_extendqisi2
	moveq	r0, #1
	movne	r0, #0
	orr	lr, r2, lr
	movne	r2, #1
	strne	r2, [fp, #-48]
	beq	.L263
.L248:
	ldr	r2, [r6, #2168]
	ldrb	ip, [r4, #64]	@ zero_extendqisi2
	ldr	r2, [r2, #92]
	bfi	ip, r10, #0, #2
	and	ip, ip, #227
	sub	r2, r2, #1
	bfi	ip, r9, #5, #3
	cmp	r2, #2
	strb	ip, [r4, #64]
	ldrls	r1, .L266
	movhi	r1, #0
	movhi	r8, r1
	addls	r2, r1, r2, lsl #2
	ldrls	r1, [r2, #148]
	ldrb	r2, [r4, #65]	@ zero_extendqisi2
	andls	r8, r1, #7
	bfi	r2, r0, #0, #2
	mov	r0, r4
	bfi	r2, lr, #2, #2
	ldr	lr, [fp, #-48]
	bfi	r2, lr, #4, #2
	strb	r2, [r4, #65]
	ldr	r2, [r4, #64]
	bfi	r2, r8, #14, #3
	str	r2, [r4, #64]
	ldrb	ip, [r5, #4]	@ zero_extendqisi2
	mov	r2, r2, lsr #16
	bfi	r2, ip, #1, #1
	strb	r2, [r4, #66]
	ldr	r2, [r5, #8]
	str	r3, [r4, #56]
	str	r3, [r4, #60]
	str	r2, [r4, #120]
	bl	SetAspectRatio
	mov	r3, #3
	str	r3, [r4, #296]
	mov	r2, #1
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	strb	r2, [r4, #291]
	cmp	r3, #3
	moveq	r3, #0
	movne	r3, #4
	strb	r3, [r4, #284]
	ldr	r3, [r7, #4]
	cmp	r3, #0
	streqb	r3, [r4, #291]
	ldrneb	r3, [r3, #145]	@ zero_extendqisi2
	moveq	r2, #32
	moveq	r3, r2
	streq	r2, [r4, #300]
	mov	r2, #1
	strb	r2, [r4, #289]
	strne	r3, [r4, #300]
	str	r3, [r4, #308]
	str	r3, [r4, #304]
	ldr	r3, [r5, #80]
	str	r3, [r4, #108]
	ldr	r2, [r5, #56]
	str	r2, [r4, #68]
	ldr	r3, [r5, #60]
	str	r3, [r4, #72]
	ldr	r1, [r7]
	ldr	r1, [r1, #28]
	cmp	r1, #25
	beq	.L264
.L255:
	mov	r0, r2, lsr #1
	mov	r1, r3, lsr #1
	str	r0, [r4, #84]
	mov	r0, r7
	str	r1, [r4, #88]
	ldr	r1, [r5, #156]
	str	r1, [r4, #92]
	ldr	r1, [r5, #160]
	str	r2, [r4, #76]
	str	r3, [r4, #80]
	str	r1, [r4, #96]
	ldrb	r3, [r5, #35]	@ zero_extendqisi2
	str	r3, [r4, #396]
	ldrb	r3, [r5, #26]	@ zero_extendqisi2
	str	r3, [r4, #400]
	ldr	r3, [r5, #152]
	str	r3, [r4, #408]
	bl	MP2_CalcRealEncFrameRate
	ldr	r3, [r6, #996]
	str	r3, [r4, #404]
.L245:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L263:
	cmp	r2, #3
	beq	.L265
	ldr	r1, [r6, #840]
	cmp	r1, #0
	bne	.L250
	sub	r2, r2, #1
	clz	r2, r2
	mov	r2, r2, lsr #5
	str	r2, [fp, #-48]
	b	.L248
.L264:
	ldr	lr, [r4, #112]
	add	ip, r3, #15
	ldr	r8, [r4, #36]
	add	r10, r4, #512
	mov	r1, ip, lsr #4
	mov	ip, lr, asl #4
	add	r0, r8, lr
	str	r0, [fp, #-48]
	mul	ip, r1, ip
	add	r9, ip, r8
	str	r9, [r4, #40]
	ldrd	r0, [r10, #-8]
	add	lr, r9, lr
	adds	r0, r0, ip
	adc	r1, r1, ip, asr #31
	strd	r0, [r10]
	ldr	r0, [fp, #-48]
	str	r9, [r4, #24]
	str	lr, [r4, #32]
	str	r0, [r4, #28]
	str	r8, [r4, #20]
	b	.L255
.L250:
	subs	r2, r2, #1
	movne	r2, #1
	str	r2, [fp, #-48]
	b	.L248
.L265:
	ldrb	r2, [r5, #18]	@ zero_extendqisi2
	and	r2, r2, #1
	str	r2, [fp, #-48]
	b	.L248
.L267:
	.align	2
.L266:
	.word	.LANCHOR0
	UNWIND(.fnend)
	.size	MP2_SetImgFormat, .-MP2_SetImgFormat
	.align	2
	.global	MP2_SearchStartCode
	.type	MP2_SearchStartCode, %function
MP2_SearchStartCode:
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
	cmp	r1, #4
	ble	.L269
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	MP2_SearchStartCode.part.2
.L269:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_SearchStartCode, .-MP2_SearchStartCode
	.align	2
	.global	MP2_ProtocolPPSCheck
	.type	MP2_ProtocolPPSCheck, %function
MP2_ProtocolPPSCheck:
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
	add	r4, r0, #86016
	ldr	r3, [r4, #864]
	ldr	r1, [r4, #2168]
	cmp	r3, #1
	beq	.L272
	cmp	r3, #2
	beq	.L273
	ldr	r3, [r4, #828]
	orr	r3, r3, #63
	str	r3, [r4, #828]
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
.L279:
	tst	r3, #24
	beq	.L281
.L297:
	cmp	r2, #3
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L282:
	orr	r3, r3, #64
	ldr	r1, [r4, #908]
	str	r3, [r4, #828]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L285
	ldr	r1, [r5, #544]
	add	r6, r5, #560
	ldr	r0, [r4, #2528]
	add	r7, r5, #576
	bl	FreeUsdByDec
	ldr	r1, [r5, #552]
	ldr	r0, [r4, #2528]
	add	r8, r5, #544
	bl	FreeUsdByDec
	ldr	r1, [r5, #560]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	ldr	r1, [r5, #568]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r8]
	strd	r0, [r6, #-8]
	strd	r0, [r6]
	strd	r0, [r7, #-8]
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #904]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2528]
	str	r3, [r4, #904]
	str	r3, [r4, #908]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L296
.L285:
	mov	r3, #0
	str	r3, [r4, #868]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L273:
	ldr	r3, [r4, #828]
	tst	r3, #1048576
	orreq	r3, r3, #16
	streq	r3, [r4, #828]
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
	sub	r0, r2, #1
	cmp	r0, #2
	bls	.L279
.L294:
	orr	r3, r3, #8
	str	r3, [r4, #828]
	tst	r3, #24
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
	bne	.L297
.L281:
	cmp	r2, #1
	biceq	r3, r3, #192
	streq	r3, [r4, #828]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L272:
	ldrb	r2, [r1, #30]	@ zero_extendqisi2
	sub	r3, r2, #1
	cmp	r3, #3
	ldr	r3, [r4, #828]
	orrhi	r3, r3, #8
	strhi	r3, [r4, #828]
	ldrhib	r2, [r1, #30]	@ zero_extendqisi2
	sub	r0, r2, #2
	cmp	r0, #1
	bls	.L298
.L276:
	cmp	r2, #3
	beq	.L299
	tst	r3, #24
	bne	.L282
	b	.L281
.L296:
	ldr	r0, [r4, #2528]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #904]
	str	r0, [r4, #908]
	b	.L285
.L299:
	ldrb	r2, [r1, #34]	@ zero_extendqisi2
	cmp	r2, #0
	ldmnefd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	b	.L294
.L298:
	ldrb	r0, [r1, #32]	@ zero_extendqisi2
	cmp	r0, #0
	orreq	r3, r3, #8
	streq	r3, [r4, #828]
	ldreqb	r2, [r1, #30]	@ zero_extendqisi2
	b	.L276
	UNWIND(.fnend)
	.size	MP2_ProtocolPPSCheck, .-MP2_ProtocolPPSCheck
	.align	2
	.global	MP2_GetImageBuffer
	.type	MP2_GetImageBuffer, %function
MP2_GetImageBuffer:
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
	add	r4, r0, #86016
	mov	r5, r0
	mov	r1, #1
	ldr	r0, [r4, #2528]
	bl	FSP_NewLogicFs
	cmp	r0, #0
	str	r0, [r4, #912]
	blt	.L312
	mov	r1, r0
	ldr	r0, [r4, #2528]
	bl	FSP_GetLogicFs
	subs	r5, r0, #0
	beq	.L313
	ldr	r2, [r4, #912]
	mov	r0, #18
	ldr	r1, .L315
	bl	dprint_vfmw
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L308
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L308
	ldr	r3, [r3, #8]
	mov	r0, #18
	ldr	r2, [r2, #8]
	ldr	r1, .L315+4
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L312:
	ldr	r1, .L315+8
	mov	r0, #0
	bl	dprint_vfmw
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	subs	r6, r0, #0
	beq	.L303
	ldr	r1, [r6, #544]
	add	r7, r6, #560
	ldr	r0, [r4, #2528]
	add	r8, r6, #576
	bl	FreeUsdByDec
	ldr	r1, [r6, #552]
	ldr	r0, [r4, #2528]
	add	r9, r6, #544
	bl	FreeUsdByDec
	ldr	r1, [r6, #560]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	ldr	r1, [r6, #568]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r9]
	strd	r0, [r7, #-8]
	strd	r0, [r7]
	strd	r0, [r8, #-8]
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #904]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2528]
	str	r3, [r4, #904]
	str	r3, [r4, #908]
	bl	FSP_GetFspType
	cmp	r0, #0
	bne	.L314
.L303:
	add	r1, r5, #88064
	ldr	r0, [r4, #2528]
	mov	r5, #0
	add	r1, r1, #128
	str	r5, [r4, #868]
	bl	FSP_ClearNotInVoQueue
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L308:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L314:
	ldr	r0, [r4, #2528]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #904]
	str	r0, [r4, #908]
	b	.L303
.L313:
	movw	r2, #1860
	ldr	r1, .L315+12
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L316:
	.align	2
.L315:
	.word	.LC25
	.word	.LC26
	.word	.LC23
	.word	.LC24
	UNWIND(.fnend)
	.size	MP2_GetImageBuffer, .-MP2_GetImageBuffer
	.align	2
	.global	MP2_GetPictureInfo
	.type	MP2_GetPictureInfo, %function
MP2_GetPictureInfo:
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
	add	r8, r0, #86016
	mov	r4, r0
	ldr	r3, [r8, #864]
	ldr	r5, [r8, #2168]
	cmp	r3, #1
	ldr	r7, [r8, #2172]
	beq	.L367
.L318:
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L319
	ldr	r2, [r8, #840]
	ldr	r1, [r8, #872]
	clz	r3, r2
	mov	r3, r3, lsr #5
	str	r3, [r8, #840]
	ldr	r2, [r5, #164]
	cmp	r2, r1
	moveq	r3, #0
	andne	r3, r3, #1
	cmp	r3, #0
	bne	.L368
.L365:
	add	r6, r4, #45056
.L321:
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	strb	r3, [r6, #257]
	ldr	r3, [r5, #164]
	str	r3, [r8, #872]
	ldr	r3, [r5, #64]
	strh	r3, [r4, #158]	@ movhi
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r3, #3
	ldr	r3, [r5, #68]
	ldreq	r2, [r5, #72]
	movne	r3, r3, lsr #1
	rsbeq	r3, r2, r3
	strh	r3, [r4, #154]	@ movhi
	ldr	r3, [r5, #68]
	strh	r3, [r4, #156]	@ movhi
	ldrb	r3, [r5, #19]	@ zero_extendqisi2
	strb	r3, [r4, #13]
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	strb	r3, [r4, #11]
	ldr	r2, [r8, #840]
	strb	r2, [r4, #12]
	ldrb	r3, [r5, #20]	@ zero_extendqisi2
	strb	r3, [r4, #15]
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	strb	r3, [r4, #8]
	ldr	r3, [r8, #864]
	sub	r3, r3, #1
	clz	r3, r3
	mov	r3, r3, lsr #5
	str	r3, [r4, #184]
	cmp	r3, #0
	ldrneb	r3, [r5, #33]	@ zero_extendqisi2
	strneb	r3, [r4, #9]
	ldrneb	r3, [r5, #31]	@ zero_extendqisi2
	strneb	r3, [r4, #10]
	ldrb	r3, [r5, #12]	@ zero_extendqisi2
	strb	r3, [r4, #20]
	ldrb	r3, [r5, #13]	@ zero_extendqisi2
	strb	r3, [r4, #21]
	ldrb	r3, [r5, #14]	@ zero_extendqisi2
	strb	r3, [r4, #22]
	ldrb	r3, [r5, #15]	@ zero_extendqisi2
	strb	r3, [r4, #23]
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	strb	r3, [r4, #14]
	ldrb	r3, [r5, #16]	@ zero_extendqisi2
	strb	r3, [r4, #19]
	ldrb	r3, [r5, #21]	@ zero_extendqisi2
	strb	r3, [r4, #18]
	ldrb	r3, [r5, #22]	@ zero_extendqisi2
	strb	r3, [r4, #17]
	ldrb	r3, [r5, #23]	@ zero_extendqisi2
	strb	r3, [r4, #16]
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r2, #0
	cmpne	r3, #3
	bne	.L330
	mov	r1, #0
	mov	r0, r4
	bl	MP2_GetImageBuffer
	subs	r7, r0, #0
	beq	.L369
	ldr	r1, [r8, #912]
	ldr	r0, [r8, #2528]
	bl	FSP_GetFsImagePtr
	subs	r9, r0, #0
	beq	.L333
	ldr	r6, [r4]
	add	ip, r9, #592
	add	lr, r9, #608
	mvn	r2, #0
	mvn	r3, #0
	ldr	r1, .L372
	ldrd	r6, [r6, #56]
	mov	r0, #29
	strd	r6, [ip, #-8]
	ldr	r6, [r4]
	ldrd	r6, [r6, #72]
	strd	r6, [ip]
	ldr	r6, [r4]
	ldrd	r6, [r6, #88]
	strd	r6, [lr, #-8]
	ldr	lr, [r4]
	ldr	lr, [lr, #104]
	str	lr, [r9]
	ldr	lr, [r4]
	ldr	lr, [lr, #108]
	str	lr, [r9, #4]
	ldr	lr, [r4]
	ldr	lr, [lr, #112]
	str	lr, [r9, #8]
	ldr	lr, [r4]
	ldr	lr, [lr, #128]
	str	lr, [r9, #12]
	ldr	lr, [r4]
	strd	r2, [lr, #56]
	ldrd	r6, [ip]
	ldrd	r2, [ip, #-8]
	strd	r6, [sp]
	bl	dprint_vfmw
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	subs	r3, r3, #3
	movne	r3, #1
	str	r3, [r9, #52]
.L333:
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L330
	ldr	r3, [r8, #868]
	ldr	r2, [r8, #904]
	cmp	r3, #0
	ldr	r3, [r8, #908]
	movne	r1, #2
	moveq	r1, #1
	cmp	r2, r3
	str	r1, [r8, #868]
	beq	.L336
	ldr	r1, .L372+4
	mov	r0, #13
	bl	dprint_vfmw
	mov	r2, #0
	ldr	r1, [r8, #904]
	ldr	r0, [r8, #2528]
	bl	FSP_SetRef
	ldr	r3, [r8, #908]
.L336:
	ldr	r1, [r8, #912]
	mov	r2, #1
	str	r3, [r8, #904]
	ldr	r0, [r8, #2528]
	str	r1, [r8, #908]
	bl	FSP_SetRef
	ldr	r1, [r8, #904]
	ldr	r0, [r8, #2528]
	bl	FSP_RemovePmv
	ldr	r2, [r8, #912]
	ldr	r1, .L372+8
	mov	r0, #13
	bl	dprint_vfmw
.L330:
	ldr	r1, [r8, #912]
	ldr	r0, [r8, #2528]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #904]
	mov	r5, r0
	ldr	r0, [r8, #2528]
	bl	FSP_GetLogicFs
	ldr	r1, [r8, #908]
	mov	r6, r0
	ldr	r0, [r8, #2528]
	bl	FSP_GetLogicFs
	cmp	r5, #0
	cmpne	r6, #0
	moveq	r3, #1
	movne	r3, #0
	cmp	r0, #0
	orreq	r3, r3, #1
	mov	r9, r0
	cmp	r3, #0
	bne	.L370
	ldr	r2, [r5, #28]
	cmp	r2, #0
	beq	.L338
	ldr	r3, [r5, #32]
	cmp	r3, #0
	beq	.L338
	ldr	r3, [r0, #28]
	mov	r0, #13
	ldr	r1, .L372+12
	cmp	r3, #0
	ldrne	lr, [r3, #8]
	ldreq	lr, [r2, #8]
	str	lr, [r4, #188]
	ldr	r3, [r6, #28]
	cmp	r3, #0
	ldreq	r3, [r5, #28]
	ldr	ip, [r3, #8]
	str	ip, [r4, #192]
	ldr	r3, [r5, #28]
	ldr	r2, [r3, #8]
	str	r2, [r4, #196]
	ldr	r7, [r5, #8]
	str	r7, [r4, #232]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #8]
	str	r3, [r4, #208]
	ldr	r8, [r9, #92]
	str	r8, [r4, #200]
	ldr	r6, [r6, #92]
	str	lr, [sp, #4]
	str	r7, [sp, #8]
	str	r6, [r4, #204]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	r3, [r5, #32]
	add	r1, r4, #87040
	add	lr, r4, #87
	add	r0, r1, #76
	add	ip, r4, #23
	ldr	r3, [r3, #24]
	add	r1, r1, #332
	mov	r2, #0
	str	r3, [r4, #216]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #60]
	str	r3, [r4, #220]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #44]
	str	r3, [r4, #224]
	ldr	r3, [r5, #32]
	ldr	r3, [r3, #48]
	str	r3, [r4, #228]
.L344:
	ldr	r3, [r0, #4]!
	add	r2, r2, #1
	cmp	r2, #64
	strb	r3, [lr, #1]!
	ldr	r3, [r1, #4]!
	strb	r3, [ip, #1]!
	bne	.L344
	mov	r0, r4
	mov	r7, #1
	bl	MP2_EstimatePicQp
	strb	r0, [r4, #153]
.L332:
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L369:
	ldr	r2, [r8, #836]
	ldr	r1, .L372+16
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L319:
	add	r6, r4, #45056
	ldrb	r1, [r6, #257]	@ zero_extendqisi2
	cmp	r1, #3
	beq	.L324
	ldr	r3, [r8, #840]
	cmp	r3, #0
	beq	.L371
.L324:
	mov	r3, #1
	str	r3, [r8, #840]
	b	.L321
.L367:
	ldrb	r2, [r5, #34]	@ zero_extendqisi2
	ldrb	r3, [r5, #32]	@ zero_extendqisi2
	strb	r2, [r5, #15]
	strb	r2, [r5, #14]
	strb	r3, [r5, #13]
	strb	r3, [r5, #12]
	b	.L318
.L370:
	ldr	r1, [r8, #912]
	mov	r7, #0
	ldr	r0, [r8, #2528]
	mov	r2, #1
	bl	FSP_ClearLogicFs
	stmia	sp, {r6, r9}
	mov	r3, r5
	movw	r2, #1180
	ldr	r1, .L372+20
	mov	r0, r7
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L371:
	ldr	r2, [r8, #836]
	mov	r0, #1
	str	r1, [sp]
	ldr	r1, .L372+24
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r8, #912]
	ldr	r0, [r8, #2528]
	bl	FSP_ClearLogicFs
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #3
	ldrne	r3, [r8, #828]
	orrne	r3, r3, #192
	strne	r3, [r8, #828]
	b	.L324
.L338:
	ldr	r1, [r8, #912]
	mov	r2, #1
	ldr	r0, [r8, #2528]
	mov	r7, #0
	bl	FSP_ClearLogicFs
	ldr	r1, [r5, #32]
	ldr	r3, [r8, #912]
	mov	r0, r7
	ldr	r2, [r8, #904]
	str	r1, [sp, #8]
	ldr	lr, [r8, #908]
	ldr	ip, [r5, #28]
	ldr	r1, .L372+28
	str	lr, [sp]
	str	ip, [sp, #4]
	bl	dprint_vfmw
	b	.L332
.L368:
	ldr	r2, [r8, #836]
	mov	r0, #1
	ldr	r1, .L372+32
	bl	dprint_vfmw
	mov	r3, #0
	mov	r2, #1
	str	r3, [r8, #840]
	ldr	r1, [r8, #912]
	ldr	r0, [r8, #2528]
	bl	FSP_ClearLogicFs
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L365
	ldr	r3, [r8, #828]
	add	r6, r4, #45056
	orr	r3, r3, #192
	str	r3, [r8, #828]
	b	.L321
.L373:
	.align	2
.L372:
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC35
	.word	.LC29
	.word	.LC33
	.word	.LC28
	.word	.LC34
	.word	.LC27
	UNWIND(.fnend)
	.size	MP2_GetPictureInfo, .-MP2_GetPictureInfo
	.align	2
	.global	MP2_SetVDMInf
	.type	MP2_SetVDMInf, %function
MP2_SetVDMInf:
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
	add	r5, r0, #86016
	mov	r4, r0
	add	r0, r0, #87040
	ldrb	r3, [r5, #780]	@ zero_extendqisi2
	add	r0, r0, #48
	ldr	r2, [r5, #784]
	cmp	r3, #1
	ldr	r3, [r5, #1096]
	beq	.L377
	ldr	ip, [r5, #776]
	mov	r1, r3, lsr #3
	add	r3, r3, r2, lsl #3
	add	r2, r1, r2
	ldr	r6, [r5, #788]
	and	r3, r3, #31
	bic	r2, r2, #3
	add	r1, r1, ip
	str	r1, [r5, #776]
	bic	r6, r6, #3
	str	r3, [r4, #168]
	str	r2, [r4, #160]
	bl	BsResidBits
	str	r6, [r4, #164]
	str	r0, [r4, #176]
	ldr	r3, [r5, #788]
	and	r3, r3, #3
	mov	r3, r3, asl #3
	str	r3, [r4, #172]
	ldr	r3, [r5, #796]
	mov	r3, r3, asl #3
	str	r3, [r4, #180]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L377:
	ldr	r1, [r5, #776]
	mov	ip, r3, lsr #3
	add	r3, r3, r2, lsl #3
	add	r2, ip, r2
	and	r3, r3, #31
	bic	r2, r2, #3
	add	r1, r1, ip
	str	r1, [r5, #776]
	str	r3, [r4, #168]
	str	r2, [r4, #160]
	bl	BsResidBits
	mov	r3, #0
	str	r3, [r4, #164]
	str	r3, [r4, #172]
	str	r3, [r4, #180]
	str	r0, [r4, #176]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_SetVDMInf, .-MP2_SetVDMInf
	.align	2
	.global	MP2_DecNewPic
	.type	MP2_DecNewPic, %function
MP2_DecNewPic:
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
	mov	r4, r0
	bl	MP2_SetVDMInf
	ldr	r3, [r4]
	add	r2, r4, #45056
	add	r1, r4, #86016
	ldr	r0, [r3, #592]
	str	r0, [r2, #248]
	ldr	r0, [r3, #644]
	str	r0, [r2, #252]
	ldr	r2, [r1, #2168]
	ldrb	r0, [r2, #30]	@ zero_extendqisi2
	cmp	r0, #3
	beq	.L396
	cmp	r0, #2
	moveq	r0, #1
	streq	r0, [r1, #2540]
.L380:
	add	ip, r4, #8
	str	ip, [r4, #4]
	ldr	r0, [r3, #880]
	cmp	r0, #1
	beq	.L397
	cmp	r0, #2
	beq	.L398
.L383:
	ldr	r3, [r1, #828]
	bic	r3, r3, #16252928
	str	r3, [r1, #828]
	ldrb	r5, [r2, #30]	@ zero_extendqisi2
	cmp	r5, #1
	movne	r0, #1
	beq	.L399
.L381:
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L399:
	ldr	r3, .L400
	ldr	r6, [r3]
	cmp	r6, #0
	moveq	r0, r5
	beq	.L381
	ldr	lr, [r4, #180]
	sub	r2, fp, #28
	ldr	ip, [r4, #176]
	mov	r3, #4
	ldr	r0, [r1, #2528]
	mov	r1, #20
	add	ip, ip, lr
	add	lr, ip, #7
	cmp	ip, #0
	movlt	ip, lr
	mov	ip, ip, asr #3
	str	ip, [r2, #-4]!
	blx	r6
	mov	r0, r5
	sub	sp, fp, #24
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L396:
	ldr	r0, [r1, #2540]
	cmp	r0, #0
	bne	.L380
	ldr	ip, [r1, #868]
	cmp	ip, #2
	beq	.L380
	ldrb	r3, [r2, #17]	@ zero_extendqisi2
	cmp	r3, #3
	ldrne	r3, [r1, #840]
	clzne	r3, r3
	movne	r3, r3, lsr #5
	strne	r3, [r1, #840]
	b	.L381
.L397:
	cmp	ip, #0
	beq	.L383
	ldrb	r3, [r2, #30]	@ zero_extendqisi2
	cmp	r3, #3
	moveq	r0, #0
	streq	r0, [r4, #4]
	bne	.L383
	b	.L381
.L398:
	ldr	r0, [r3, #884]
	cmp	ip, #0
	cmpne	r0, #0
	ble	.L383
	ldrb	r0, [r2, #30]	@ zero_extendqisi2
	cmp	r0, #3
	bne	.L383
	mov	r0, #0
	str	r0, [r4, #4]
	ldr	r2, [r3, #884]
	sub	r2, r2, #1
	str	r2, [r3, #884]
	b	.L381
.L401:
	.align	2
.L400:
	.word	g_event_report
	UNWIND(.fnend)
	.size	MP2_DecNewPic, .-MP2_DecNewPic
	.align	2
	.global	MP2_RecordVFMWState
	.type	MP2_RecordVFMWState, %function
MP2_RecordVFMWState:
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
	add	r2, r0, #86016
	ldr	r1, [r0]
	ldr	r3, [r2, #2168]
	ldr	ip, [r3, #48]
	str	ip, [r1, #568]
	ldr	r1, [r3, #52]
	ldr	r3, [r0]
	str	r1, [r3, #572]
	ldr	r3, [r2, #2532]
	ldr	r2, [r2, #2536]
	ldr	r1, [r0]
	cmp	r3, r2
	rsbge	r3, r2, r3
	movlt	r3, #0
	str	r3, [r1, #576]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_RecordVFMWState, .-MP2_RecordVFMWState
	.align	2
	.global	MP2_GetUsrData
	.type	MP2_GetUsrData, %function
MP2_GetUsrData:
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
	add	r4, r0, #87040
	mov	r8, r0
	add	r4, r4, #48
	mov	r0, r4
	bl	BsToNextByte
	mov	r0, r4
	bl	BsResidBits
	add	r7, r0, #7
	cmp	r0, #0
	movlt	r0, r7
	mov	r7, r0, asr #3
	cmp	r7, #0
	ble	.L425
	mov	r6, #0
	ldr	r9, .L443
	mov	r5, r6
	b	.L410
.L441:
	bl	BsGet
	add	r5, r5, #1
	cmp	r5, r7
	strb	r0, [r9, r6]
	add	r6, r6, #1
	beq	.L406
.L410:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	bic	r3, r0, #-16777216
	mov	r0, r4
	cmp	r3, #1
	beq	.L407
	cmp	r6, #1024
	blt	.L441
	mov	r1, #8
	mov	r0, r4
	add	r5, r5, #1
	bl	BsGet
	cmp	r5, r7
	bne	.L410
.L406:
	add	r7, r8, #86016
	add	r3, r7, #780
	ldrsb	r9, [r3]
	cmp	r9, #0
	beq	.L422
.L440:
	mov	r5, #0
.L411:
	ldr	r4, [r7, #860]
	cmp	r4, #3
	ble	.L424
.L423:
	add	r4, r7, #840
	add	r10, r7, #856
	mov	r9, #0
.L415:
	ldr	r1, [r4, #4]!
	ldr	r0, [r7, #2528]
	bl	FreeUsdByDec
	cmp	r4, r10
	str	r9, [r4]
	mov	r3, #0
	bne	.L415
	mov	r4, r3
	str	r3, [r7, #860]
.L424:
	ldr	r0, [r7, #2528]
	add	r4, r8, r4, lsl #2
	bl	GetUsd
	add	r4, r4, #86016
	str	r0, [r4, #844]
	ldr	r2, [r7, #860]
	add	r3, r8, r2, lsl #2
	add	r3, r3, #86016
	add	r3, r3, #584
	ldr	r3, [r3, #260]
	cmp	r3, #0
	beq	.L416
	ldr	r3, [r8]
	add	r0, r0, #1056
	ldr	r1, .L443
	ldrd	r2, [r3, #56]
	strd	r2, [r0]
	ldr	r3, [r4, #844]
	ldr	r2, [r7, #832]
	str	r2, [r3, #1044]
	ldr	r3, [r4, #844]
	str	r6, [r3, #1052]
	ldr	r2, [r7, #2168]
	ldr	r3, [r4, #844]
	ldrb	r2, [r2, #30]	@ zero_extendqisi2
	strb	r2, [r3, #1024]
	ldr	r3, [r4, #844]
	ldr	r2, [r7, #2532]
	str	r2, [r3, #1032]
	ldr	r2, [r7, #2168]
	ldr	r3, [r4, #844]
	ldrb	r2, [r2, #18]	@ zero_extendqisi2
	strb	r2, [r3, #1025]
	ldr	r3, [r7, #828]
	tst	r3, #524288
	ldr	r3, [r4, #844]
	movne	r2, #3
	moveq	r2, #1
	str	r2, [r3, #1040]
	ldr	r0, [r4, #844]
	ldr	r2, [r0, #1052]
	cmp	r2, #1024
	movgt	r3, #1024
	strgt	r3, [r0, #1052]
	ldr	r3, .L443+4
	ldrgt	r0, [r4, #844]
	ldr	r3, [r3, #52]
	ldrgt	r2, [r0, #1052]
	blx	r3
	ldr	r3, .L443+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L420
	ldr	r2, [r4, #844]
	movw	r3, #1064
	mov	r1, #6
	ldr	r0, [r7, #2528]
	blx	ip
.L420:
	ldr	r3, [r7, #860]
	add	r3, r3, #1
	str	r3, [r7, #860]
.L439:
	mov	r0, r5
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L422:
	movw	r3, #781
	ldrsb	r3, [r7, r3]
	cmp	r3, #0
	beq	.L428
	ldr	r5, [r7, #796]
	cmp	r5, #0
	beq	.L411
	ldr	r1, .L443+12
	mov	r0, r9
	bl	dprint_vfmw
	ldr	ip, .L443+4
	ldr	r3, [r7, #792]
	mov	r2, #3
	ldr	r1, [r7, #808]
	mov	r5, #1
	ldr	r0, [r7, #812]
	sub	r3, r3, #3
	add	r1, r1, r3
	ldr	r3, [ip, #52]
	sub	r0, r0, #3
	blx	r3
	ldr	r3, [r7, #812]
	ldr	ip, [r7, #788]
	mov	r0, r4
	ldr	r2, [r7, #796]
	sub	r3, r3, #3
	strb	r9, [r7, #781]
	add	r2, r2, #3
	mov	r1, r3
	str	r2, [r7, #792]
	str	r3, [r7, #808]
	sub	r3, ip, #3
	str	r9, [r7, #796]
	str	r3, [r7, #784]
	str	r9, [r7, #812]
	str	r9, [r7, #788]
	strb	r5, [r7, #780]
	bl	BsInit
	strb	r5, [r7, #781]
	strb	r9, [r7, #780]
	mov	r0, r4
	bl	BsToNextByte
	mov	r0, r4
	bl	BsResidBits
	add	r10, r0, #7
	cmp	r0, #0
	movlt	r0, r10
	mov	r10, r0, asr #3
	cmp	r10, #3
	ble	.L427
	ldr	r5, .L443
	sub	r10, r10, #3
	b	.L414
.L442:
	bl	BsGet
	strb	r0, [r5, r6]
	add	r6, r6, #1
.L413:
	add	r9, r9, #1
	cmp	r9, r10
	beq	.L440
.L414:
	mov	r1, #24
	mov	r0, r4
	bl	BsShow
	mov	r1, #8
	bic	r3, r0, #-16777216
	mov	r0, r4
	cmp	r3, #1
	beq	.L428
	cmp	r6, #1024
	blt	.L442
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	b	.L413
.L407:
	add	r7, r8, #86016
	mov	r5, r3
	ldr	r4, [r7, #860]
	cmp	r4, #3
	bgt	.L423
	b	.L424
.L428:
	mov	r5, r3
	b	.L411
.L416:
	mov	r0, r3
	ldr	r1, .L443+16
	bl	dprint_vfmw
	b	.L439
.L425:
	mov	r6, #0
	b	.L406
.L427:
	mov	r5, r9
	b	.L411
.L444:
	.align	2
.L443:
	.word	.LANCHOR1
	.word	vfmw_Osal_Func_Ptr_S
	.word	g_event_report
	.word	.LC36
	.word	.LC37
	UNWIND(.fnend)
	.size	MP2_GetUsrData, .-MP2_GetUsrData
	.align	2
	.global	next_start_code
	.type	next_start_code, %function
next_start_code:
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
	add	r5, r0, #87040
	mov	r7, r0
	add	r5, r5, #48
	mov	r0, r5
	bl	BsToNextByte
	mov	r0, r5
	bl	BsGetNextBytePtr
	mov	r4, r0
	mov	r0, r5
	bl	BsResidBits
	cmp	r0, #0
	add	r3, r0, #7
	movge	r1, r0
	movlt	r1, r3
	mov	r1, r1, asr #3
	cmp	r1, #4
	movle	r1, #0
	bgt	.L470
.L446:
	mov	r0, r5
	bl	BsLongSkip
	mov	r0, r5
	bl	BsResidBits
	mov	r6, r0
	add	r0, r0, #7
	cmp	r6, #0
	movlt	r6, r0
	mov	r6, r6, asr #3
	cmp	r6, #3
	subgt	r6, r6, #3
	movgt	r4, #0
	bgt	.L452
	b	.L453
.L450:
	bl	BsSkip
	cmp	r4, r6
	beq	.L453
.L452:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r5
	bne	.L450
.L455:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L453:
	add	r7, r7, #86016
	add	r3, r7, #780
	ldrsb	r4, [r3]
	cmp	r4, #0
	bne	.L449
	ldrb	r3, [r7, #781]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L449
	ldr	r3, [r7, #796]
	cmp	r3, #0
	beq	.L449
	ldr	r1, .L473
	mov	r0, #7
	bl	dprint_vfmw
	ldr	ip, .L473+4
	ldr	r3, [r7, #792]
	mov	r2, #3
	ldr	r1, [r7, #808]
	mov	r6, #1
	ldr	r0, [r7, #812]
	sub	r3, r3, #3
	add	r1, r1, r3
	ldr	r3, [ip, #52]
	sub	r0, r0, #3
	blx	r3
	ldr	r3, [r7, #812]
	ldr	ip, [r7, #788]
	mov	r0, r5
	ldr	r2, [r7, #796]
	sub	r3, r3, #3
	strb	r6, [r7, #780]
	mov	r1, r3
	add	r2, r2, #3
	str	r3, [r7, #808]
	sub	r3, ip, #3
	str	r2, [r7, #792]
	str	r3, [r7, #784]
	strb	r4, [r7, #781]
	str	r4, [r7, #796]
	str	r4, [r7, #812]
	str	r4, [r7, #788]
	bl	BsInit
	strb	r6, [r7, #781]
	strb	r4, [r7, #780]
	mov	r0, r5
	bl	BsToNextByte
	mov	r0, r5
	bl	BsGetNextBytePtr
	mov	r6, r0
	mov	r0, r5
	bl	BsResidBits
	cmp	r0, #0
	add	r1, r0, #7
	movge	r3, r0
	movlt	r3, r1
	mov	r1, r3, asr #3
	cmp	r1, #4
	movle	r1, r4
	bgt	.L471
.L454:
	mov	r0, r5
	bl	BsLongSkip
	mov	r0, r5
	bl	BsResidBits
	add	r6, r0, #7
	cmp	r0, #0
	movlt	r0, r6
	mov	r6, r0, asr #3
	cmp	r6, #3
	ble	.L449
	sub	r6, r6, #3
	mov	r4, #0
	b	.L456
.L472:
	bl	BsSkip
	cmp	r4, r6
	beq	.L449
.L456:
	mov	r1, #24
	mov	r0, r5
	bl	BsShow
	add	r4, r4, #1
	mov	r1, #8
	cmp	r0, #1
	mov	r0, r5
	bne	.L472
	b	.L455
.L449:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L470:
	mov	r0, r4
	bl	MP2_SearchStartCode.part.2
	mov	r1, r0, asl #3
	b	.L446
.L471:
	mov	r0, r6
	bl	MP2_SearchStartCode.part.2
	mov	r1, r0, asl #3
	b	.L454
.L474:
	.align	2
.L473:
	.word	.LC36
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	next_start_code, .-next_start_code
	.align	2
	.global	GetSliceHdr
	.type	GetSliceHdr, %function
GetSliceHdr:
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
	add	r5, r0, #87040
	mov	r6, r0
	add	r5, r5, #48
	add	r7, r0, #86016
	b	.L476
.L483:
	bl	BsShow
	mov	r4, r0
	mov	r0, r5
	bl	BsPos
	sub	r3, r4, #256
	sub	r3, r3, #1
	mov	r1, #32
	cmp	r3, #174
	str	r0, [r7, #888]
	mov	r0, r5
	bls	.L489
	bl	BsSkip
.L476:
	mov	r0, r6
	bl	next_start_code
	mov	r1, #32
	mov	r3, r0
	cmp	r3, #1
	mov	r0, r5
	beq	.L483
	cmn	r3, #1
	beq	.L478
.L484:
	mov	r0, r3
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L478:
	ldr	r3, .L490
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L485
	add	r6, r6, #86016
	mov	r3, #0
	mov	r2, r3
	mov	r1, #113
	ldr	r0, [r6, #2528]
	blx	ip
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L489:
	bl	BsResidBits
	cmp	r0, #40
	ble	.L478
	ldr	r3, [r7, #824]
	mov	r2, #0
	str	r2, [r7, #884]
	cmp	r3, r2
	bne	.L482
	mov	r0, r6
	bl	MP2_GetSequenceInfo
	ldr	r3, [r7, #876]
	cmp	r3, #0
	beq	.L484
.L482:
	mov	r0, r6
	bl	MP2_ProtocolPPSCheck
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L485:
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L491:
	.align	2
.L490:
	.word	g_event_report
	UNWIND(.fnend)
	.size	GetSliceHdr, .-GetSliceHdr
	.align	2
	.global	sequence_header
	.type	sequence_header, %function
sequence_header:
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
	add	r7, r0, #87040
	add	r4, r0, #86016
	add	r5, r7, #48
	mov	r2, #65536
	mov	r3, #0
	str	r2, [r4, #828]
	str	r3, [r4, #824]
	mov	r1, #12
	mov	r6, r0
	mov	r0, r5
	ldr	r8, [r4, #2168]
	bl	BsGet
	mov	r1, #12
	str	r0, [r8, #56]
	mov	r0, r5
	bl	BsGet
	mov	r1, #4
	str	r0, [r8, #60]
	mov	r0, r5
	bl	BsGet
	mov	r1, #4
	str	r0, [r8, #92]
	mov	r0, r5
	bl	BsGet
	mov	r1, #18
	str	r0, [r8, #96]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #100]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	ldreq	r3, [r4, #828]
	orreq	r3, r3, #1
	streq	r3, [r4, #828]
.L493:
	mov	r1, #10
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r8, #104]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	strb	r0, [r8, #1]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r8, #84]
	beq	.L500
	ldr	r2, .L507
	add	r3, r7, #76
	add	r0, r7, #332
.L496:
	ldrb	r1, [r2, #1]!	@ zero_extendqisi2
	str	r1, [r3, #4]!
	cmp	r3, r0
	bne	.L496
.L495:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r8, #88]
	beq	.L501
	add	r3, r7, #332
	add	r7, r7, #588
	mov	r2, #16
.L498:
	str	r2, [r3, #4]!
	cmp	r3, r7
	bne	.L498
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L500:
	ldr	r10, .L507+4
	add	r9, r10, #64
.L494:
	mov	r1, #8
	mov	r0, r5
	ldrb	r4, [r10, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #21760
	cmp	r10, r9
	add	r3, r3, #20
	str	r0, [r6, r3, asl #2]
	bne	.L494
	b	.L495
.L501:
	ldr	r7, .L507+4
	add	r8, r7, #64
.L497:
	mov	r1, #8
	mov	r0, r5
	ldrb	r4, [r7, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #21760
	cmp	r7, r8
	add	r3, r3, #84
	str	r0, [r6, r3, asl #2]
	bne	.L497
	mov	r0, #1
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L508:
	.align	2
.L507:
	.word	.LANCHOR2-1
	.word	.LANCHOR2+63
	UNWIND(.fnend)
	.size	sequence_header, .-sequence_header
	.align	2
	.global	group_of_pictures_header
	.type	group_of_pictures_header, %function
group_of_pictures_header:
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
	add	r5, r0, #87040
	add	r4, r0, #86016
	add	r5, r5, #48
	mov	r1, #1
	ldr	r6, [r4, #2168]
	add	r7, r4, #948
	mov	r0, r5
	bl	BsGet
	mov	r1, #5
	strb	r0, [r6, #2]
	mov	r0, r5
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #108]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #112]
	mov	r0, r5
	bl	BsSkip
	mov	r0, r5
	mov	r1, #6
	bl	BsGet
	mov	r1, #6
	str	r0, [r6, #116]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #120]
	mov	r0, r5
	bl	BsGet
	mov	r1, #1
	str	r0, [r6, #124]
	mov	r0, r5
	bl	BsGet
	add	ip, r4, #960
	add	r3, r4, #972
	add	r5, r4, #984
	mov	lr, #0
	str	r0, [r6, #128]
	ldmia	ip, {r0, r1, r2}
	stmia	r7, {r0, r1, r2}
	ldmia	r3, {r0, r1, r2}
	stmia	ip, {r0, r1, r2}
	ldmia	r5, {r0, r1, r2}
	stmia	r3, {r0, r1, r2}
	str	lr, [r4, #984]
	str	lr, [r4, #992]
	str	lr, [r4, #988]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	group_of_pictures_header, .-group_of_pictures_header
	.align	2
	.global	sequence_extension
	.type	sequence_extension, %function
sequence_extension:
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
	add	r6, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #48
	mov	r2, #0
	ldr	r3, [r6, #828]
	mov	r1, #8
	str	r2, [r6, #824]
	mov	r0, r4
	orr	r3, r3, #131072
	str	r3, [r6, #828]
	ldr	r5, [r6, #2168]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #132]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r5, #35]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r5, #36]
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	mov	r10, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #12
	mov	r8, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	mov	r7, r0
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	bne	.L511
	ldr	r3, [r6, #828]
	orr	r3, r3, #2
	str	r3, [r6, #828]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L511:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	mov	r9, r0
	mov	r0, r4
	bl	BsGet
	mov	r1, #2
	strb	r0, [r5, #37]
	mov	r0, r4
	bl	BsGet
	mov	r1, #5
	strb	r0, [r5, #38]
	mov	r0, r4
	bl	BsGet
	ldrb	r3, [r5, #38]	@ zero_extendqisi2
	uxtb	r1, r0
	strb	r0, [r5, #39]
	add	r1, r1, #1
	add	r0, r3, #1
	bl	__aeabi_idiv
	ldr	r1, [r5, #96]
	ldr	r2, .L535
	ldr	r3, [r5, #132]
	add	r2, r2, r1, lsl #2
	tst	r3, #128
	ldr	r2, [r2, #160]
	mul	r0, r2, r0
	str	r0, [r5, #80]
	bne	.L534
	ubfx	r2, r3, #4, #3
	and	r3, r3, #15
	str	r2, [r5, #48]
	str	r3, [r5, #52]
.L514:
	ldr	r3, [r5, #56]
	ldr	r2, [r5, #60]
	ubfx	r3, r3, #0, #12
	ubfx	r2, r2, #0, #12
	orr	r3, r3, r10, asl #12
	orr	r8, r2, r8, asl #12
	str	r3, [r5, #56]
	cmp	r8, #0
	cmpne	r3, #0
	str	r8, [r5, #60]
	ldreq	r3, [r6, #828]
	orreq	r3, r3, #1
	streq	r3, [r6, #828]
	ldreq	r3, [r5, #56]
	cmp	r3, #8192
	bhi	.L516
	ldr	r3, [r5, #60]
	cmp	r3, #8192
	bls	.L517
.L516:
	ldr	r2, .L535+4
	ldr	r3, [r6, #828]
	ldr	ip, [r2]
	orr	r3, r3, #1
	str	r3, [r6, #828]
	cmp	ip, #0
	beq	.L517
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r6, #2528]
	blx	ip
.L517:
	ldr	r3, [r5, #100]
	mov	r1, #400
	ldr	r2, [r5, #48]
	add	r7, r3, r7, lsl #18
	str	r7, [r5, #100]
	sub	r0, r2, #4
	ldr	r3, [r5, #104]
	mul	r7, r1, r7
	cmp	r0, #1
	add	r9, r3, r9, lsl #10
	str	r9, [r5, #104]
	str	r7, [r5, #76]
	bls	.L519
	ldr	r3, .L535+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L520
	mov	r3, #0
	mov	r1, #102
	mov	r2, r3
	ldr	r0, [r6, #2528]
	blx	ip
	ldr	r2, [r5, #48]
.L520:
	ldr	r1, .L535+8
	mov	r0, #1
	bl	dprint_vfmw
.L519:
	ldr	r2, [r5, #52]
	sub	r3, r2, #4
	cmp	r3, #6
	ldmlsfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, .L535+4
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L521
	mov	r3, #0
	ldr	r0, [r6, #2528]
	mov	r2, r3
	mov	r1, #102
	blx	ip
	ldr	r2, [r5, #52]
.L521:
	ldr	r1, .L535+12
	mov	r0, #1
	sub	sp, fp, #44
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	dprint_vfmw
.L534:
	and	r3, r3, #15
	cmp	r3, #5
	moveq	r2, #133
	moveq	r3, #8
	streq	r2, [r5, #48]
	streq	r3, [r5, #52]
	b	.L514
.L536:
	.align	2
.L535:
	.word	.LANCHOR0
	.word	g_event_report
	.word	.LC38
	.word	.LC39
	UNWIND(.fnend)
	.size	sequence_extension, .-sequence_extension
	.align	2
	.global	sequence_display_extension
	.type	sequence_display_extension, %function
sequence_display_extension:
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
	add	r6, r0, #86016
	add	r4, r0, #87040
	mov	r3, #0
	add	r4, r4, #48
	ldr	r5, [r6, #2168]
	mov	r1, #3
	mov	r0, r4
	str	r3, [r5, #156]
	str	r3, [r5, #160]
	ldr	r3, [r6, #828]
	orr	r3, r3, #262144
	str	r3, [r6, #828]
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #136]
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	str	r0, [r5, #140]
	bne	.L544
.L538:
	mov	r1, #14
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #156]
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	bne	.L539
	ldr	r3, [r6, #828]
	orr	r3, r3, #4
	str	r3, [r6, #828]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L539:
	mov	r0, r4
	mov	r1, #14
	bl	BsGet
	str	r0, [r5, #160]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L544:
	mov	r1, #8
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #144]
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	str	r0, [r5, #148]
	mov	r0, r4
	bl	BsGet
	str	r0, [r5, #152]
	b	.L538
	UNWIND(.fnend)
	.size	sequence_display_extension, .-sequence_display_extension
	.align	2
	.global	quant_matrix_extension
	.type	quant_matrix_extension, %function
quant_matrix_extension:
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
	add	r5, r0, #87040
	add	r3, r0, #86016
	add	r5, r5, #48
	mov	r7, r0
	mov	r1, #1
	ldr	r9, [r3, #2168]
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r9, #84]
	beq	.L570
.L546:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #1
	str	r0, [r9, #88]
	ldreq	r6, .L572
	addeq	r8, r6, #64
	beq	.L548
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	beq	.L550
.L556:
	mov	r4, #64
.L551:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	subs	r4, r4, #1
	bne	.L551
.L550:
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	beq	.L571
.L552:
	mov	r4, #64
.L553:
	mov	r1, #8
	mov	r0, r5
	bl	BsGet
	subs	r4, r4, #1
	bne	.L553
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L548:
	mov	r1, #8
	mov	r0, r5
	ldrb	r4, [r6, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #21760
	cmp	r6, r8
	add	r3, r3, #84
	str	r0, [r7, r3, asl #2]
	bne	.L548
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L556
	mov	r1, #1
	mov	r0, r5
	bl	BsGet
	cmp	r0, #0
	bne	.L552
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L571:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L570:
	ldr	r6, .L572
	add	r8, r6, #64
.L547:
	mov	r1, #8
	mov	r0, r5
	ldrb	r4, [r6, #1]!	@ zero_extendqisi2
	bl	BsGet
	add	r3, r4, #21760
	cmp	r6, r8
	add	r3, r3, #20
	str	r0, [r7, r3, asl #2]
	bne	.L547
	b	.L546
.L573:
	.align	2
.L572:
	.word	.LANCHOR2+63
	UNWIND(.fnend)
	.size	quant_matrix_extension, .-quant_matrix_extension
	.align	2
	.global	sequence_scalable_extension
	.type	sequence_scalable_extension, %function
sequence_scalable_extension:
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
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #48
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	sequence_scalable_extension, .-sequence_scalable_extension
	.align	2
	.global	picture_display_extension
	.type	picture_display_extension, %function
picture_display_extension:
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
	add	r8, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #48
	ldr	r5, [r8, #2168]
	ldr	r3, [r8, #828]
	orr	r3, r3, #2097152
	str	r3, [r8, #828]
	ldrb	r3, [r5, #35]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L576
	ldrb	r3, [r5, #24]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L588
.L584:
	mov	r7, #1
.L577:
	add	r5, r5, #168
	mov	r6, #0
	b	.L581
.L590:
	bl	BsGet
	mov	r1, #1
	str	r0, [r5, #12]
	mov	r0, r4
	bl	BsGet
	cmp	r0, #0
	beq	.L587
	cmp	r6, r7
	bge	.L589
.L581:
	mov	r1, #16
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	add	r6, r6, r1
	str	r0, [r5, #4]!
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	cmp	r0, #0
	mov	r0, r4
	bne	.L590
.L587:
	ldr	r3, [r8, #828]
	orr	r3, r3, #32
	str	r3, [r8, #828]
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L576:
	ldrb	r3, [r5, #17]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L584
	ldrb	r3, [r5, #24]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r7, #2
	movne	r7, #3
	b	.L577
.L588:
	ldrb	r3, [r5, #18]	@ zero_extendqisi2
	cmp	r3, #0
	moveq	r7, #2
	movne	r7, #3
	b	.L577
.L589:
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	picture_display_extension, .-picture_display_extension
	.align	2
	.global	picture_coding_extension
	.type	picture_coding_extension, %function
picture_coding_extension:
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
	add	r8, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #48
	ldr	r7, [r8, #2168]
	ldr	r3, [r8, #828]
	add	r10, r7, #12
	add	r9, r7, #16
	orr	r3, r3, #1048576
	str	r3, [r8, #828]
.L592:
	mov	r6, r10
	mov	r5, #0
.L594:
	mov	r1, #4
	mov	r0, r4
	bl	BsGet
	add	r5, r5, #1
	uxtb	r0, r0
	strb	r0, [r6], #1
	sub	r3, r0, #10
	cmp	r0, #0
	cmpne	r3, #4
	ldrls	r3, [r8, #828]
	orrls	r3, r3, #16
	strls	r3, [r8, #828]
	cmp	r5, #2
	bne	.L594
	add	r10, r10, #2
	cmp	r10, r9
	bne	.L592
	mov	r1, r5
	mov	r0, r4
	bl	BsGet
	mov	r1, r5
	strb	r0, [r7, #16]
	mov	r0, r4
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #17]
	cmp	r0, #0
	bne	.L596
	ldr	r3, [r8, #828]
	orr	r3, r3, #16
	str	r3, [r8, #828]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L596:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #18]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #19]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #20]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #21]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #22]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #23]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #24]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #25]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #26]
	mov	r0, r4
	bl	BsGet
	uxtb	r0, r0
	strb	r0, [r7, #3]
	cmp	r0, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #3
	strb	r0, [r7, #27]
	mov	r0, r4
	bl	BsGet
	mov	r1, #1
	strb	r0, [r7, #28]
	mov	r0, r4
	bl	BsGet
	mov	r1, #7
	strb	r0, [r7, #29]
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	str	r0, [r7, #40]
	mov	r0, r4
	bl	BsGet
	str	r0, [r7, #44]
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	picture_coding_extension, .-picture_coding_extension
	.align	2
	.global	picture_spatial_scalable_extension
	.type	picture_spatial_scalable_extension, %function
picture_spatial_scalable_extension:
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
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #48
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	picture_spatial_scalable_extension, .-picture_spatial_scalable_extension
	.align	2
	.global	picture_temporal_scalable_extension
	.type	picture_temporal_scalable_extension, %function
picture_temporal_scalable_extension:
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
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #48
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	picture_temporal_scalable_extension, .-picture_temporal_scalable_extension
	.align	2
	.global	extra_bit_information
	.type	extra_bit_information, %function
extra_bit_information:
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
	add	r4, r0, #87040
	mov	r5, #0
	add	r4, r4, #48
	b	.L608
.L610:
	bl	BsSkip
	mov	r0, r4
	bl	BsResidBits
	add	r5, r5, #1
	cmp	r0, #8
	ble	.L609
.L608:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #8
	cmp	r0, #0
	mov	r0, r4
	bne	.L610
.L609:
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	extra_bit_information, .-extra_bit_information
	.align	2
	.global	picture_header
	.type	picture_header, %function
picture_header:
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
	add	r2, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #48
	mov	r1, #10
	ldr	r3, [r2, #828]
	mov	r6, r0
	mov	r0, r4
	ldr	r5, [r2, #2168]
	bic	r3, r3, #3145728
	bic	r3, r3, #56
	orr	r3, r3, #524288
	str	r3, [r2, #828]
	bl	BsGet
	mov	r1, #3
	str	r0, [r5, #164]
	mov	r0, r4
	bl	BsGet
	mov	r1, #16
	strb	r0, [r5, #30]
	mov	r0, r4
	bl	BsGet
	ldrb	r7, [r5, #30]	@ zero_extendqisi2
	sub	r3, r7, #2
	cmp	r3, #1
	str	r0, [r5, #168]
	bls	.L614
.L612:
	cmp	r7, #3
	beq	.L615
.L613:
	mov	r0, r6
	bl	extra_bit_information
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L615:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, r7
	strb	r0, [r5, #33]
	mov	r0, r4
	bl	BsGet
	strb	r0, [r5, #34]
	b	.L613
.L614:
	mov	r1, #1
	mov	r0, r4
	bl	BsGet
	mov	r1, #3
	strb	r0, [r5, #31]
	mov	r0, r4
	bl	BsGet
	ldrb	r7, [r5, #30]	@ zero_extendqisi2
	strb	r0, [r5, #32]
	b	.L612
	UNWIND(.fnend)
	.size	picture_header, .-picture_header
	.align	2
	.global	copyright_extension
	.type	copyright_extension, %function
copyright_extension:
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
	add	r0, r0, #87040
	mov	r1, #32
	add	r0, r0, #48
	sub	sp, fp, #12
	ldmia	sp, {fp, sp, lr}
	b	BsSkip
	UNWIND(.fnend)
	.size	copyright_extension, .-copyright_extension
	.align	2
	.global	extension
	.type	extension, %function
extension:
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
	add	r3, r0, #86016
	add	r4, r0, #87040
	add	r4, r4, #48
	mov	r2, #0
	ldr	r3, [r3, #2168]
	mov	r5, r0
	mov	r1, #4
	mov	r0, r4
	str	r2, [r3, #136]
	str	r2, [r3, #140]
	str	r2, [r3, #144]
	str	r2, [r3, #148]
	str	r2, [r3, #152]
	bl	BsGet
	sub	r0, r0, #1
	cmp	r0, #9
	ldrls	pc, [pc, r0, asl #2]
	b	.L618
.L620:
	.word	.L619
	.word	.L621
	.word	.L622
	.word	.L623
	.word	.L623
	.word	.L618
	.word	.L625
	.word	.L626
	.word	.L623
	.word	.L623
.L625:
	mov	r0, r5
	bl	picture_display_extension
.L618:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L623:
	mov	r0, r4
	mov	r1, #32
	bl	BsSkip
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L622:
	mov	r0, r5
	bl	quant_matrix_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L626:
	mov	r0, r5
	bl	picture_coding_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L619:
	mov	r0, r5
	bl	sequence_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L621:
	mov	r0, r5
	bl	sequence_display_extension
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	extension, .-extension
	.align	2
	.global	MPEG2DEC_Init
	.type	MPEG2DEC_Init, %function
MPEG2DEC_Init:
	UNWIND(.fnstart)
	@ args = 0, pretend = 0, frame = 912
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	UNWIND(.pad #916)
	sub	sp, sp, #916
	ldr	r3, [r1, #616]
	mov	r6, r1
	mov	r5, r0
	cmp	r3, #1
	ldr	r7, .L638
	beq	.L635
	add	r4, r0, #86016
	add	r8, r0, #87040
	mov	r10, #0
	str	r10, [fp, #-956]
	str	r10, [fp, #-952]
.L630:
	ldr	r9, [r4, #2520]
	mov	r2, #23040
	movt	r2, 1
	mov	r1, #0
	ldr	r7, [r7, #48]
	mov	r0, r5
	blx	r7
	add	r0, r5, #88064
	str	r9, [r4, #2520]
	add	r0, r0, #128
	bl	ResetVoQueue
	add	r1, r5, #45056
	str	r6, [r5]
	mov	r7, #0
	add	r0, r8, #752
	str	r7, [r4, #2540]
	str	r0, [r4, #2172]
	add	r2, r8, #948
	mov	r0, #3
	str	r2, [r4, #2168]
	mov	r9, #1
	str	r9, [r4, #840]
	strb	r0, [r1, #257]
	mov	r0, r5
	str	r7, [r4, #884]
	ldr	r1, [r6, #8]
	str	r7, [r4, #876]
	ldr	r5, .L638
	str	r1, [r4, #816]
	bl	VCTRL_GetChanIDByCtx
	cmn	r0, #1
	str	r0, [r4, #2528]
	beq	.L636
	ldr	r6, [r6, #616]
	cmp	r6, #1
	movne	r6, r9
	beq	.L637
.L632:
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L637:
	ldr	r3, [fp, #-952]
	sub	r1, fp, #556
	ldr	ip, [r4, #828]
	mov	r2, #256
	str	r10, [r4, #824]
	add	r0, r8, #80
	str	r3, [r4, #864]
	orr	ip, ip, #65536
	ldr	r3, [fp, #-956]
	str	ip, [r4, #828]
	str	r3, [r4, #876]
	ldr	r3, [r5, #52]
	blx	r3
	ldr	r3, [r5, #52]
	sub	r1, fp, #300
	add	r0, r8, #336
	mov	r2, #256
	blx	r3
	ldr	r3, [r5, #52]
	sub	r1, fp, #948
	mov	r2, #196
	ldr	r0, [r4, #2168]
	blx	r3
	ldr	r3, [r5, #52]
	ldr	r0, [r4, #2172]
	mov	r2, #196
	sub	r1, fp, #752
	blx	r3
	mov	r0, r6
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L635:
	add	r4, r0, #86016
	add	r8, r0, #87040
	add	r1, r8, #80
	ldr	ip, [r7, #52]
	ldr	r3, [r4, #864]
	mov	r2, #256
	sub	r0, fp, #556
	ldr	r10, [r4, #824]
	str	r3, [fp, #-952]
	ldr	r3, [r4, #876]
	str	r3, [fp, #-956]
	blx	ip
	ldr	ip, [r7, #52]
	add	r1, r8, #336
	mov	r2, #256
	sub	r0, fp, #300
	blx	ip
	ldr	ip, [r7, #52]
	ldr	r1, [r4, #2168]
	mov	r2, #196
	sub	r0, fp, #948
	blx	ip
	ldr	ip, [r7, #52]
	ldr	r1, [r4, #2172]
	mov	r2, #196
	sub	r0, fp, #752
	blx	ip
	b	.L630
.L636:
	mov	r0, r7
	ldr	r1, .L638+4
	bl	dprint_vfmw
	mvn	r6, #19
	b	.L632
.L639:
	.align	2
.L638:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC40
	UNWIND(.fnend)
	.size	MPEG2DEC_Init, .-MPEG2DEC_Init
	.align	2
	.global	MPEG2DEC_Destroy
	.type	MPEG2DEC_Destroy, %function
MPEG2DEC_Destroy:
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
	add	r3, r0, #86016
	ldr	r1, .L641
	mov	r0, #2
	ldr	r2, [r3, #836]
	bl	dprint_vfmw
	mov	r0, #1
	ldmfd	sp, {fp, sp, pc}
.L642:
	.align	2
.L641:
	.word	.LC41
	UNWIND(.fnend)
	.size	MPEG2DEC_Destroy, .-MPEG2DEC_Destroy
	.align	2
	.global	MPEG2DEC_RecycleImage
	.type	MPEG2DEC_RecycleImage, %function
MPEG2DEC_RecycleImage:
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
	mov	r4, r1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	add	r5, r0, #86016
	mov	r2, #0
	ldr	r0, [r5, #2528]
	bl	FSP_SetDisplay
	mov	r1, r4
	ldr	r0, [r5, #2528]
	bl	FSP_GetFsImagePtr
	cmp	r0, #0
	addne	r4, r0, #536
	addne	r6, r0, #568
	movne	r8, #0
	movne	r9, #0
	beq	.L647
.L646:
	ldr	r1, [r4, #8]!
	ldr	r0, [r5, #2528]
	bl	FreeUsdByDec
	cmp	r4, r6
	strd	r8, [r4]
	bne	.L646
.L647:
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG2DEC_RecycleImage, .-MPEG2DEC_RecycleImage
	.align	2
	.global	MPEG2DEC_GetRemainImg
	.type	MPEG2DEC_GetRemainImg, %function
MPEG2DEC_GetRemainImg:
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
	ldr	r3, [r0]
	mov	r4, r0
	ldr	r3, [r3, #24]
	cmp	r3, #1
	beq	.L672
	add	r5, r0, #86016
	ldr	r1, [r5, #908]
	ldr	r0, [r5, #2528]
	bl	FSP_GetFsImagePtr
	subs	r9, r0, #0
	beq	.L672
	ldr	r1, [r5, #908]
	ldr	r0, [r5, #2528]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L670
.L672:
	add	r6, r4, #88064
.L651:
	add	r7, r6, #128
.L657:
	mov	r0, r7
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, lr}
	b	GetVoLastImageID
.L670:
	mov	r0, r4
	bl	MP2_SetImgFormat
	add	r3, r5, #840
	add	r2, r9, #544
	add	ip, r5, #856
	mov	r0, #0
.L653:
	ldr	r1, [r3, #4]!
	mov	r8, #0
	add	r2, r2, #8
	cmp	r1, r8
	strne	r0, [r2, #-4]
	strne	r1, [r2, #-8]
	cmp	r3, ip
	str	r0, [r3]
	bne	.L653
	add	r6, r4, #88064
	mov	r3, #1
	add	r7, r6, #128
	str	r8, [r5, #860]
	mov	r2, r3
	str	r3, [r9, #180]
	ldr	r1, [r9, #148]
	ldr	r0, [r5, #2528]
	bl	FSP_SetDisplay
	ldr	r0, [r5, #2528]
	mov	r3, r7
	str	r9, [sp]
	mov	r2, r4
	mov	r1, #3
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L654
	ldr	r1, [r9, #148]
	mov	r0, r4
	bl	MPEG2DEC_RecycleImage
	b	.L657
.L654:
	ldr	r3, [r9, #152]
	cmp	r3, #100
	bhi	.L651
	ldr	r3, [r9, #68]
	cmp	r3, #31
	bls	.L651
	ldr	r3, [r9, #72]
	cmp	r3, #31
	bls	.L657
	mov	r0, r8
	sub	sp, fp, #36
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG2DEC_GetRemainImg, .-MPEG2DEC_GetRemainImg
	.align	2
	.global	MPEG2DEC_GetImageBuffer
	.type	MPEG2DEC_GetImageBuffer, %function
MPEG2DEC_GetImageBuffer:
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
	add	r3, r0, #45056
	mov	r4, r0
	add	r5, r0, #86016
	ldrb	r3, [r3, #257]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L674
	ldr	r3, [r5, #840]
	cmp	r3, #0
	beq	.L676
.L674:
	ldr	r0, [r5, #2528]
	bl	FSP_IsNewFsAvalible
	cmp	r0, #1
	beq	.L676
	ldr	r0, [r5, #2528]
	bl	FSP_IsNewFsAvalible
	cmn	r0, #1
	beq	.L684
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L676:
	mov	r0, #1
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L684:
	add	r1, r4, #88064
	ldr	r0, [r5, #2528]
	add	r1, r1, #128
	bl	FSP_ClearNotInVoQueue
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MPEG2DEC_GetImageBuffer, .-MPEG2DEC_GetImageBuffer
	.align	2
	.global	MP2_ClearCurPacket
	.type	MP2_ClearCurPacket, %function
MP2_ClearCurPacket:
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
	ldr	r1, [r1, #20]
	mov	r5, r0
	bl	SM_ReleaseStreamSeg
	ldrsb	r3, [r4]
	cmp	r3, #1
	beq	.L686
	mov	r0, r5
	ldr	r1, [r4, #24]
	bl	SM_ReleaseStreamSeg
.L686:
	ldr	r3, .L690
	mov	r0, r4
	mov	r2, #36
	mov	r1, #0
	ldr	r3, [r3, #48]
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, lr}
	bx	r3
.L691:
	.align	2
.L690:
	.word	vfmw_Osal_Func_Ptr_S
	UNWIND(.fnend)
	.size	MP2_ClearCurPacket, .-MP2_ClearCurPacket
	.align	2
	.global	MP2_ReceivePacket
	.type	MP2_ReceivePacket, %function
MP2_ReceivePacket:
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
	add	r3, r0, #40960
	beq	.L697
	mov	r5, #0
	str	r5, [r3, #520]
	ldr	r1, [r4, #16]
	str	r1, [r3, #564]
	ldr	r1, [r4, #12]
	str	r1, [r3, #528]
	ldr	r1, [r4]
	str	r1, [r3, #552]
	ldr	r1, [r4, #16]
	str	r1, [r3, #536]
	ldrb	r1, [r4, #6]	@ zero_extendqisi2
	strb	r1, [r3, #524]
	ldr	r1, [r4, #20]
	str	r1, [r3, #544]
	ldrb	ip, [r4, #6]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L695
	ldr	r1, [r4, #92]
	str	r1, [r3, #532]
	ldr	r1, [r4, #80]
	str	r1, [r3, #556]
	ldr	r1, [r4, #96]
	str	r1, [r3, #540]
	ldrb	r1, [r4, #86]	@ zero_extendqisi2
	strb	r1, [r3, #525]
	ldr	r1, [r4, #100]
	str	r1, [r3, #548]
	ldrb	ip, [r4, #86]	@ zero_extendqisi2
	cmp	ip, #1
	beq	.L696
	add	r1, r0, #41472
	mov	r0, r2
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	ldrb	r2, [r4, #86]	@ zero_extendqisi2
	ldr	r1, .L698
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r5
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L696:
	mov	r0, ip
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L695:
	str	r5, [r3, #532]
	mov	r0, ip
	str	r5, [r3, #556]
	str	r5, [r3, #540]
	strb	r5, [r3, #525]
	str	r5, [r3, #548]
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L697:
	ldr	r1, .L698+4
	mov	r0, #1
	ldr	r2, [r3, #580]
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L699:
	.align	2
.L698:
	.word	.LC43
	.word	.LC42
	UNWIND(.fnend)
	.size	MP2_ReceivePacket, .-MP2_ReceivePacket
	.align	2
	.global	MP2_ClearCurPic
	.type	MP2_ClearCurPic, %function
MP2_ClearCurPic:
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
	add	r6, r0, #45056
	ldr	r3, [r6, #244]
	cmp	r3, #0
	movne	r4, r0
	movne	r5, #0
	addne	r7, r4, #86016
	bne	.L703
	b	.L704
.L702:
	ldr	r3, [r6, #244]
	add	r4, r4, #44
	cmp	r5, r3
	bcs	.L704
.L703:
	ldr	r1, [r4, #268]
	add	r5, r5, #1
	ldr	r0, [r7, #2528]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r4, #248]
	cmp	r3, #0
	beq	.L702
	ldr	r3, [r4, #256]
	cmp	r3, #0
	beq	.L702
	ldr	r1, [r4, #272]
	add	r4, r4, #44
	ldr	r0, [r7, #2528]
	bl	SM_ReleaseStreamSeg
	ldr	r3, [r6, #244]
	cmp	r5, r3
	bcc	.L703
.L704:
	mov	r3, #0
	str	r3, [r6, #244]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_ClearCurPic, .-MP2_ClearCurPic
	.align	2
	.global	MPEG2DEC_VDMPostProc
	.type	MPEG2DEC_VDMPostProc, %function
MPEG2DEC_VDMPostProc:
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
	ldrb	r3, [r0, #153]	@ zero_extendqisi2
	add	r4, r0, #86016
	mov	r5, r0
	mov	r2, r1
	mov	r8, r1
	strb	r3, [r4, #1008]
	mov	r0, #22
	ldr	r1, .L787
	add	r7, r5, #8
	ldr	r6, [r4, #2168]
	bl	dprint_vfmw
	ldr	r2, [r5, #4]
	mov	r0, r5
	ldr	r3, [r4, #2168]
	add	r9, r5, #45056
	add	r1, r2, #45056
	ldrb	r2, [r2, #144]	@ zero_extendqisi2
	strb	r2, [r3, #4]
	ldr	r2, [r1, #240]
	str	r2, [r3, #8]
	ldr	r3, [r4, #2168]
	ldr	r2, [r5]
	ldr	r1, [r3, #48]
	str	r1, [r2, #568]
	ldr	r2, [r3, #52]
	ldr	r3, [r5]
	str	r2, [r3, #572]
	ldr	r3, [r4, #2532]
	ldr	r2, [r4, #2536]
	ldr	r1, [r5]
	cmp	r3, r2
	rsbge	r3, r2, r3
	movlt	r3, #0
	str	r3, [r1, #576]
	bl	MP2_ClearCurPic
	ldr	r3, .L787+4
	movw	r2, #45304
	mov	r0, r7
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, [r4, #912]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #908]
	mov	r7, r0
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #904]
	mov	r10, r0
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	cmp	r7, #0
	beq	.L781
	ldrb	r3, [r6, #30]	@ zero_extendqisi2
	cmp	r8, #0
	strb	r3, [r9, #256]
	str	r8, [r7, #152]
	blt	.L717
	cmp	r8, #100
	movlt	r1, r8
	movge	r1, #100
	str	r1, [r7, #152]
	ldrb	r3, [r6, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L718
	ldr	r3, [r5]
	ldr	r3, [r3]
	cmp	r1, r3
	bhi	.L782
.L718:
	ldr	r1, .L787+8
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r5
	bl	MP2_SetImgFormat
	ldrb	r3, [r6, #17]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L724
	ldr	r3, [r4, #840]
	cmp	r3, #1
	movne	r0, #1
	beq	.L724
.L777:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L724:
	add	r0, r7, #544
	add	r3, r4, #840
	add	lr, r4, #856
	mov	r1, #0
.L723:
	ldr	r2, [r3, #4]!
	mov	ip, #0
	add	r0, r0, #8
	cmp	r2, ip
	strne	r1, [r0, #-4]
	strne	r2, [r0, #-8]
	cmp	r3, lr
	str	r1, [r3]
	bne	.L723
	str	ip, [r4, #860]
	ldr	r3, [r5]
	ldr	r3, [r3, #24]
	cmp	r3, #0
	beq	.L783
.L726:
	ldr	r1, [r4, #912]
	str	r1, [r4, #916]
.L727:
	cmn	r1, #1
	beq	.L729
	ldr	r0, [r4, #2528]
	bl	FSP_GetDisplay
	cmp	r0, #1
	beq	.L733
	ldr	r1, [r4, #916]
	ldr	r0, [r4, #2528]
	bl	FSP_GetDisplay
	cmp	r0, #2
	beq	.L733
.L729:
	ldrb	r3, [r6, #35]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L784
	ldrb	r3, [r6, #26]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r4, #992]
	addeq	r3, r3, #1
	addne	r3, r3, #1
	streq	r3, [r4, #992]
	ldreqb	r3, [r6, #24]	@ zero_extendqisi2
	ldreq	r2, [r4, #988]
	addeq	r3, r3, #2
	strne	r3, [r4, #992]
	addeq	r3, r2, r3
	movne	r3, r3, asl #1
	str	r3, [r4, #988]
.L746:
	ldr	r2, [r4, #984]
	mov	r0, #1
	ldr	r3, [r4, #836]
	add	r2, r2, r0
	str	r2, [r4, #984]
	add	r3, r3, r0
	str	r3, [r4, #836]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L717:
	mov	r3, #0
	str	r3, [r7, #152]
	b	.L718
.L782:
	mov	r2, #1
	ldr	r1, [r4, #912]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	subs	r5, r0, #0
	beq	.L720
	ldr	r1, [r5, #544]
	add	r6, r5, #560
	ldr	r0, [r4, #2528]
	add	r7, r5, #576
	bl	FreeUsdByDec
	ldr	r1, [r5, #552]
	ldr	r0, [r4, #2528]
	add	r8, r5, #544
	bl	FreeUsdByDec
	ldr	r1, [r5, #560]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	ldr	r1, [r5, #568]
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	mov	r0, #0
	mov	r1, #0
	mov	r2, #1
	strd	r0, [r8]
	strd	r0, [r6, #-8]
	strd	r0, [r6]
	strd	r0, [r7, #-8]
	ldr	r1, [r4, #908]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r2, #1
	ldr	r1, [r4, #904]
	ldr	r0, [r4, #2528]
	bl	FSP_ClearLogicFs
	mov	r3, #0
	ldr	r0, [r4, #2528]
	str	r3, [r4, #904]
	str	r3, [r4, #908]
	bl	FSP_GetFspType
	cmp	r0, #0
	beq	.L720
	ldr	r0, [r4, #2528]
	bl	FSP_GetNullLogicFs
	str	r0, [r4, #904]
	str	r0, [r4, #908]
.L720:
	mov	r3, #0
	mov	r0, #1
	str	r3, [r4, #868]
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L783:
	ldrb	r3, [r6, #30]	@ zero_extendqisi2
	cmp	r3, #3
	beq	.L726
	ldr	r1, [r4, #904]
	str	r1, [r4, #916]
	b	.L727
.L733:
	ldr	r1, [r4, #916]
	ldr	r0, [r4, #2528]
	bl	FSP_GetFsImagePtr
	subs	r7, r0, #0
	beq	.L785
	ldr	r2, [r7, #152]
	cmp	r2, #0
	beq	.L735
	ldr	r3, [r5]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	bhi	.L736
.L735:
	ldr	r8, [r4, #916]
	ldr	r0, [r4, #2528]
	mov	r1, r8
	bl	FSP_GetRef
	mov	r2, r8
	ldr	r1, .L787+12
	mov	r3, r0
	mov	r0, #12
	bl	dprint_vfmw
	mov	r2, #1
	ldr	r1, [r4, #916]
	ldr	r0, [r4, #2528]
	bl	FSP_SetDisplay
	ldr	r8, [r4, #2528]
	ldr	r1, [r4, #908]
	mov	r0, r8
	bl	FSP_GetFsImagePtr
	ldr	r1, [r4, #916]
	mov	r10, r0
	mov	r0, r8
	bl	FSP_GetFsImagePtr
	cmp	r10, #0
	cmpne	r0, #0
	beq	.L786
	add	r9, r0, #592
	mvn	r1, #0
	mvn	r0, #0
	ldrd	r2, [r9, #-8]
	cmp	r3, r1
	cmpeq	r2, r0
	beq	.L738
	ldr	r1, [r4, #908]
	mov	r0, r8
	bl	FSP_GetDisplay
	cmp	r0, #1
	beq	.L742
	ldr	r1, [r4, #908]
	mov	r0, r8
	bl	FSP_GetDisplay
	cmp	r0, #2
	bne	.L738
.L742:
	add	r10, r10, #592
	ldrd	r2, [r9, #-8]
	ldrd	r0, [r10, #-8]
	cmp	r3, r1
	cmpeq	r2, r0
	bls	.L738
	strd	r0, [sp]
	mov	r0, r8
	bl	IsPtsRewind
	cmp	r0, #0
	bne	.L738
	ldrd	r2, [r9, #-8]
	mov	r0, #29
	ldr	r1, .L787+16
	strd	r2, [fp, #-52]
	ldrd	r2, [r10, #-8]
	strd	r2, [sp]
	ldrd	r2, [fp, #-52]
	bl	dprint_vfmw
	ldrd	r2, [r9, #-8]
	ldrd	r0, [r10, #-8]
	strd	r0, [r9, #-8]
	strd	r2, [r10, #-8]
.L738:
	add	r3, r5, #88064
	ldr	r0, [r4, #2528]
	add	r3, r3, #128
	str	r7, [sp]
	mov	r2, r5
	mov	r1, #3
	bl	InsertImgToVoQueue
	cmp	r0, #1
	beq	.L748
	add	r5, r7, #536
	add	r7, r7, #568
	mov	r8, #0
	mov	r9, #0
.L743:
	ldr	r1, [r5, #8]!
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	cmp	r5, r7
	strd	r8, [r5]
	bne	.L743
	ldr	r0, [r4, #2528]
	mov	r2, #0
	ldr	r1, [r4, #916]
	bl	FSP_SetDisplay
	mov	r0, #0
	b	.L777
.L784:
	ldrb	r2, [r6, #24]	@ zero_extendqisi2
	ldrb	r3, [r6, #18]	@ zero_extendqisi2
	ldr	r1, [r4, #992]
	add	r3, r2, r3
	add	r3, r3, #1
	add	r3, r3, r1
	str	r3, [r4, #992]
	mov	r3, r3, asl #1
	str	r3, [r4, #988]
	b	.L746
.L736:
	ldr	r1, .L787+20
	mov	r0, #1
	bl	dprint_vfmw
	add	r5, r7, #536
	add	r7, r7, #568
	mov	r8, #0
	mov	r9, #0
.L744:
	ldr	r1, [r5, #8]!
	ldr	r0, [r4, #2528]
	bl	FreeUsdByDec
	cmp	r5, r7
	strd	r8, [r5]
	bne	.L744
	mov	r2, #0
	ldr	r1, [r4, #916]
	ldr	r0, [r4, #2528]
	bl	FSP_SetDisplay
	b	.L729
.L781:
	str	r0, [sp]
	mov	r3, r10
	mov	r2, r7
	ldr	r1, .L787+24
	mov	r0, r7
	bl	dprint_vfmw
	mov	r0, r7
	b	.L777
.L748:
	ldr	r3, [r4, #2536]
	add	r3, r3, #1
	str	r3, [r4, #2536]
	b	.L729
.L786:
	ldr	r1, .L787+28
	mov	r0, #0
	bl	dprint_vfmw
	b	.L738
.L785:
	movw	r2, #3535
	ldr	r1, .L787+32
	bl	dprint_vfmw
	mov	r0, r7
	b	.L777
.L788:
	.align	2
.L787:
	.word	.LC44
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC46
	.word	.LC47
	.word	.LC49
	.word	.LC50
	.word	.LC45
	.word	.LC48
	.word	.LC24
	UNWIND(.fnend)
	.size	MPEG2DEC_VDMPostProc, .-MPEG2DEC_VDMPostProc
	.align	2
	.global	MP2_u_v
	.type	MP2_u_v, %function
MP2_u_v:
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
	mov	r5, r2
	mov	r6, r0
	mov	r7, r1
	bl	BsShow
	mov	r1, r7
	mov	r4, r0
	mov	r0, r6
	bl	BsSkip
	mov	r3, r4
	mov	r2, r5
	ldr	r1, .L790
	mov	r0, #2
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L791:
	.align	2
.L790:
	.word	.LC51
	UNWIND(.fnend)
	.size	MP2_u_v, .-MP2_u_v
	.align	2
	.global	MP2_DecSliceHeader
	.type	MP2_DecSliceHeader, %function
MP2_DecSliceHeader:
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
	ldr	r2, [r0, #4]
	mov	r1, #1
	mov	r3, #0
	mov	r5, r0
	cmp	r2, #175
	str	r1, [r0, #16]
	ldr	r4, [r0, #52]
	str	r3, [r0, #24]
	bls	.L793
	ldr	r2, [r0]
	cmp	r2, r3
	beq	.L805
.L793:
	ldr	r2, [r5, #20]
	mov	r0, r4
	ldr	r1, [r5, #8]
	sub	r2, r2, #1
	add	r3, r2, r3
	ldr	r2, .L808
	mul	r3, r1, r3
	mov	r1, #5
	cmp	r3, #0
	subne	r3, r3, #1
	str	r3, [r5, #28]
	bl	MP2_u_v
	mov	r3, #0
	mov	r1, #1
	str	r3, [r5, #32]
	str	r0, [r5, #44]
	mov	r0, r4
	bl	BsShow
	cmp	r0, #0
	bne	.L806
.L797:
	mov	r0, r4
	ldr	r2, .L808+4
	mov	r1, #1
	bl	MP2_u_v
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L806:
	ldr	r2, .L808+8
	mov	r1, #1
	mov	r0, r4
	bl	MP2_u_v
	ldr	r2, .L808+12
	mov	r1, #1
	mov	r0, r4
	bl	MP2_u_v
	ldr	r2, .L808+16
	mov	r1, #7
	str	r0, [r5, #32]
	mov	r0, r4
	bl	MP2_u_v
	b	.L796
.L807:
	bl	BsShow
	ldr	r2, .L808+4
	mov	r1, #1
	cmp	r0, #0
	mov	r0, r4
	beq	.L797
	bl	MP2_u_v
	ldr	r2, .L808+20
	mov	r1, #8
	mov	r0, r4
	bl	MP2_u_v
.L796:
	mov	r0, r4
	bl	BsResidBits
	mov	r1, #1
	cmp	r0, #0
	mov	r0, r4
	bgt	.L807
	b	.L797
.L805:
	ldr	r2, .L808+24
	mov	r1, #3
	mov	r0, r4
	bl	MP2_u_v
	mov	r3, r0, asl #7
	str	r0, [r5, #24]
	b	.L793
.L809:
	.align	2
.L808:
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC57
	.word	.LC58
	.word	.LC52
	UNWIND(.fnend)
	.size	MP2_DecSliceHeader, .-MP2_DecSliceHeader
	.align	2
	.global	MP2_ExitMb
	.type	MP2_ExitMb, %function
MP2_ExitMb:
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
	str	r3, [r0, #16]
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_ExitMb, .-MP2_ExitMb
	.align	2
	.global	MP2_WriteSliceInfo
	.type	MP2_WriteSliceInfo, %function
MP2_WriteSliceInfo:
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
	add	r7, r0, #45056
	mov	r4, #44
	add	r5, r0, #86016
	mov	r6, r0
	ldr	r2, [r7, #244]
	ldr	r1, [r5, #1048]
	cmp	r2, #1024
	mla	r4, r4, r2, r0
	str	r1, [r4, #280]
	ldr	r1, [r5, #1060]
	str	r1, [r4, #284]
	ldr	r1, [r5, #1056]
	str	r1, [r4, #276]
	bcs	.L817
	ldr	r2, [r5, #1096]
	add	r0, r0, #87040
	ldr	r3, [r5, #784]
	add	r0, r0, #48
	and	r1, r2, #7
	str	r1, [r4, #260]
	add	r3, r3, r2, lsr #3
	str	r3, [r4, #244]
	ldr	r3, [r5, #800]
	str	r3, [r4, #268]
	bl	BsResidBits
	add	r2, r5, #780
	str	r0, [r4, #252]
	ldrsh	r3, [r2]
	cmp	r3, #1
	beq	.L818
	cmp	r3, #256
	bne	.L816
	ldr	r1, [r5, #788]
	mov	r2, #0
	str	r2, [r4, #264]
	str	r1, [r4, #248]
	ldr	r3, [r5, #804]
	str	r3, [r4, #272]
	ldr	r3, [r5, #796]
	mov	r3, r3, asl #3
	str	r3, [r4, #256]
.L815:
	ldr	r3, [r7, #244]
	mov	r0, #1
	add	r3, r3, r0
	str	r3, [r7, #244]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L817:
	mov	r3, #1024
	ldr	r1, .L819
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP2_ClearCurPic
	ldr	r3, [r5, #828]
	mov	r0, #0
	str	r0, [r5, #884]
	bic	r3, r3, #5767168
	str	r3, [r5, #828]
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L818:
	mov	r3, #0
	add	r4, r4, #252
	str	r3, [r4, #-4]
	str	r3, [r4, #12]
	str	r3, [r4, #20]
	str	r3, [r4, #4]
	b	.L815
.L816:
	movw	r3, #781
	ldrsb	r2, [r2]
	ldrsb	r3, [r5, r3]
	mov	r0, #1
	ldr	r1, .L819+4
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L820:
	.align	2
.L819:
	.word	.LC59
	.word	.LC60
	UNWIND(.fnend)
	.size	MP2_WriteSliceInfo, .-MP2_WriteSliceInfo
	.align	2
	.global	MP2_MbAddrInc
	.type	MP2_MbAddrInc, %function
MP2_MbAddrInc:
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
	mov	r6, r0
	bl	BsShow
	ldr	r5, .L827
	add	r0, r5, r0, lsl #3
	ldr	r4, [r0, #224]
	ldr	r1, [r0, #228]
	cmp	r4, #6
	bls	.L825
	cmp	r4, #9
	beq	.L826
	mov	r1, #11
	mov	r0, r6
	bl	BsShow
	ldr	r2, .L827+4
	and	r3, r0, #127
	mov	r0, r6
	sub	r3, r3, #24
	add	r5, r5, r3, lsl #3
	ldr	r4, [r5, #352]
	ldr	r1, [r5, #356]
	bl	MP2_u_v
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L825:
	mov	r0, r6
	ldr	r2, .L827+4
	bl	MP2_u_v
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L826:
	mov	r0, r6
	ldr	r2, .L827+4
	bl	MP2_u_v
	rsb	r0, r0, #9
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L828:
	.align	2
.L827:
	.word	.LANCHOR0
	.word	.LC61
	UNWIND(.fnend)
	.size	MP2_MbAddrInc, .-MP2_MbAddrInc
	.align	2
	.global	MP2_InitMb
	.type	MP2_InitMb, %function
MP2_InitMb:
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
	mov	r5, #0
	mov	r6, r0
	ldr	r4, [r0, #52]
	b	.L830
.L834:
	cmp	r0, #15
	beq	.L831
	cmp	r0, #8
	add	r5, r5, #33
	bne	.L842
.L831:
	ldr	r2, .L844
	mov	r1, #11
	mov	r0, r4
	bl	MP2_u_v
.L830:
	mov	r1, #11
	mov	r0, r4
	bl	BsShow
	cmp	r0, #23
	bls	.L834
	mov	r0, r4
	bl	MP2_MbAddrInc
	ldr	r4, [r6, #16]
	cmp	r4, #0
	beq	.L835
	ldr	r3, [r6, #28]
	add	r5, r5, r0
	cmp	r3, #0
	addne	r2, r5, r3
	ldr	r3, [r6, #12]
	subeq	r2, r5, #1
	str	r2, [r6, #40]
	sub	r3, r3, #1
	cmp	r2, r3
	bhi	.L843
	mov	r0, #1
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L842:
	ldr	r1, .L844+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L835:
	mov	r2, r4
	ldr	r1, .L844+8
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, r4
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L843:
	ldr	r1, .L844+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L845:
	.align	2
.L844:
	.word	.LC63
	.word	.LC62
	.word	.LC65
	.word	.LC64
	UNWIND(.fnend)
	.size	MP2_InitMb, .-MP2_InitMb
	.align	2
	.global	MP2_GetFirstMbInSlice
	.type	MP2_GetFirstMbInSlice, %function
MP2_GetFirstMbInSlice:
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
	bl	MP2_DecSliceHeader
	mov	r0, r4
	bl	MP2_InitMb
	mov	r3, #0
	str	r3, [r4, #16]
	ldmfd	sp, {r4, r5, fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_GetFirstMbInSlice, .-MP2_GetFirstMbInSlice
	.align	2
	.global	MP2_DecSlice
	.type	MP2_DecSlice, %function
MP2_DecSlice:
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
	add	r4, r0, #86016
	mov	r5, r0
	add	r6, r4, #1016
	uxtb	r1, r1
	ldr	r3, [r4, #864]
	ldr	r2, [r4, #2168]
	ldr	ip, [r4, #808]
	sub	r3, r3, #1
	ldr	r0, [r4, #792]
	clz	r3, r3
	str	ip, [r4, #1064]
	mov	r3, r3, lsr #5
	str	r0, [r4, #1052]
	mov	r0, r6
	str	r3, [r4, #1016]
	ldr	r3, [r2, #68]
	str	r3, [r4, #1020]
	ldr	r3, [r2, #64]
	str	r3, [r4, #1024]
	ldr	ip, [r2, #60]
	ldr	r3, [r2, #56]
	add	ip, ip, #15
	add	r3, r3, #15
	mov	ip, ip, lsr #4
	mov	r3, r3, lsr #4
	mul	r3, r3, ip
	str	r3, [r4, #1028]
	ldrb	r2, [r2, #17]	@ zero_extendqisi2
	str	r1, [r4, #1036]
	cmp	r2, #3
	movne	r3, r3, lsr #1
	strne	r3, [r4, #1028]
	add	r3, r5, #87040
	add	r3, r3, #48
	str	r3, [r4, #1068]
	bl	MP2_DecSliceHeader
	mov	r0, r6
	bl	MP2_InitMb
	mov	r6, #0
	str	r6, [r4, #1032]
	cmp	r0, #1
	mov	r7, r0
	beq	.L849
	ldr	r1, .L863
	mov	r0, #1
	bl	dprint_vfmw
	ldr	r3, .L863+4
	ldr	ip, [r3]
	cmp	ip, r6
	beq	.L852
.L862:
	ldr	r0, [r4, #2528]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #127
	blx	ip
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L849:
	mov	r0, r5
	bl	MP2_WriteSliceInfo
	cmp	r0, #1
	ldmeqfd	sp, {r4, r5, r6, r7, fp, sp, pc}
	mov	r0, r7
	ldr	r1, .L863+8
	bl	dprint_vfmw
	ldr	r3, .L863+4
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L862
.L852:
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, fp, sp, pc}
.L864:
	.align	2
.L863:
	.word	.LC66
	.word	g_event_report
	.word	.LC67
	UNWIND(.fnend)
	.size	MP2_DecSlice, .-MP2_DecSlice
	.align	2
	.global	MP2_GetHDR
	.type	MP2_GetHDR, %function
MP2_GetHDR:
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
	add	r5, r0, #87040
	add	r4, r0, #86016
	add	r5, r5, #48
	mov	r1, #32
	mov	r6, r0
	mov	r7, #0
	mov	r0, r5
	strb	r7, [r4, #2544]
	ldr	r8, [r4, #2168]
	ldr	r9, [r4, #2172]
	bl	BsShow
	ldr	r3, [r4, #828]
	str	r3, [fp, #-80]
	mov	r10, r0
	mov	r0, r5
	bl	BsPos
	mov	r1, #32
	str	r0, [r4, #888]
	mov	r0, r5
	bl	BsSkip
	movw	r3, #439
	cmp	r10, r3
	beq	.L933
	movw	r3, #435
	cmp	r10, r3
	cmpne	r10, #440
	bne	.L872
.L868:
	ldr	r3, [r4, #884]
	cmp	r3, #1
	beq	.L934
.L869:
	movw	r3, #435
	cmp	r10, r3
	beq	.L874
.L937:
	cmp	r10, #436
	bcc	.L935
	movw	r3, #437
	cmp	r10, r3
	beq	.L878
	cmp	r10, #436
	bls	.L929
	movw	r3, #439
	cmp	r10, r3
	beq	.L929
	cmp	r10, #440
	bne	.L873
	ldr	r3, [r4, #880]
	mov	r0, r5
	ldr	r7, [r4, #776]
	add	r7, r3, r7
	bl	BsPos
	ldr	r1, .L941
	add	r2, r7, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	group_of_pictures_header
	mov	r0, r5
	bl	BsResidBits
	cmp	r0, #0
	blt	.L936
.L929:
	mov	r5, #0
.L871:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L872:
	cmp	r10, #256
	beq	.L868
	movw	r3, #435
	cmp	r10, r3
	bne	.L937
.L874:
	ldr	r3, [r4, #880]
	mov	r0, r5
	ldr	r7, [r4, #776]
	add	r7, r3, r7
	bl	BsPos
	ldr	r1, .L941+4
	add	r2, r7, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	sequence_header
	mov	r0, r5
	bl	BsResidBits
	cmp	r0, #0
	blt	.L938
	ldr	r5, [r4, #828]
	ands	r5, r5, #7
	bne	.L883
	mov	r3, #1
	mov	r0, r9
	strb	r3, [r8]
	mov	r1, r8
	mov	r2, #196
	bl	memcpy
	ldr	r3, [r4, #832]
	add	r3, r3, #1
	str	r3, [r4, #832]
	b	.L871
.L935:
	cmp	r10, #256
	beq	.L876
	bcc	.L873
	cmp	r10, #432
	bls	.L873
	ldr	r3, [r4, #880]
	mov	r0, r5
	ldr	r5, [r4, #776]
	add	r5, r3, r5
	bl	BsPos
	ldr	r1, .L941+8
	add	r2, r5, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	MP2_GetUsrData
	subs	r5, r0, #0
	bne	.L889
	add	r1, r6, #86016
	ldr	r0, [r4, #2528]
	add	r1, r1, #780
	bl	MP2_ClearCurPacket
	ldr	r3, .L941+12
	ldr	ip, [r3]
	cmp	ip, #0
	mvneq	r5, #0
	beq	.L871
	mov	r3, r5
	mov	r2, r5
	ldr	r0, [r4, #2528]
	mov	r1, #113
	blx	ip
	mvn	r5, #0
	b	.L871
.L876:
	ldr	r3, [r4, #880]
	mov	r0, r5
	ldr	r7, [r4, #776]
	add	r7, r3, r7
	bl	BsPos
	ldr	r1, .L941+16
	add	r2, r7, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	picture_header
	mov	r0, r5
	bl	BsResidBits
	cmp	r0, #0
	bge	.L929
	ldr	r3, .L941+12
	ldr	r2, [fp, #-80]
	ldr	ip, [r3]
	str	r2, [r4, #828]
	cmp	ip, #0
	beq	.L888
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #2528]
	blx	ip
.L888:
	add	r1, r6, #86016
	ldr	r0, [r4, #2528]
	add	r1, r1, #780
	mvn	r5, #0
	bl	MP2_ClearCurPacket
	mov	r2, #256
	ldr	r1, .L941+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L871
.L934:
	ldr	r2, [r4, #828]
	tst	r2, #4194304
	beq	.L869
	orr	r2, r2, #8388608
	strb	r3, [r4, #2544]
	str	r2, [r4, #828]
	mov	r0, r6
	mov	r2, #0
	str	r2, [r4, #884]
	mov	r5, r3
	bl	MP2_ProtocolPPSCheck
	b	.L871
.L933:
	ldr	r3, .L941+24
	mov	r2, #32
	mov	r1, r5
	sub	r0, fp, #76
	ldr	r3, [r3, #52]
	blx	r3
	mov	r1, #32
	sub	r0, fp, #76
	bl	BsGet
	mov	r1, #32
	str	r0, [fp, #-84]
	sub	r0, fp, #76
	bl	BsGet
	ldr	r2, [fp, #-84]
	movw	r1, #20036
	movw	r3, #20553
	movt	r1, 17221
	movt	r3, 18515
	cmp	r0, r1
	cmpeq	r2, r3
	bne	.L868
	ldr	r5, [r4, #884]
	cmp	r5, #1
	beq	.L939
.L870:
	mov	r3, #1
	mov	r5, #0
	strb	r3, [r4, #2546]
	b	.L871
.L873:
	sub	r3, r10, #256
	sub	r3, r3, #1
	cmp	r3, #174
	bhi	.L891
	ldr	r7, [r4, #824]
	cmp	r7, #0
	beq	.L892
.L894:
	ldr	r3, [r4, #828]
	tst	r3, #589824
	beq	.L929
	orr	r3, r3, #4194304
	mov	r0, r6
	str	r3, [r4, #828]
	mov	r6, #1
	mov	r1, r10
	str	r6, [r4, #884]
	bl	MP2_DecSlice
	cmp	r0, r6
	mov	r5, r0
	beq	.L871
	mov	r2, r10
	mov	r0, r6
	ldr	r1, .L941+28
	mov	r5, #0
	bl	dprint_vfmw
	b	.L871
.L878:
	ldr	r3, [r4, #880]
	mov	r0, r5
	ldr	r7, [r4, #776]
	add	r7, r3, r7
	bl	BsPos
	ldr	r1, .L941+32
	add	r2, r7, r0, lsr #3
	mov	r0, #22
	bl	dprint_vfmw
	mov	r0, r6
	bl	extension
	mov	r0, r5
	bl	BsResidBits
	cmp	r0, #0
	bge	.L929
	ldr	r3, .L941+12
	ldr	r2, [fp, #-80]
	ldr	ip, [r3]
	str	r2, [r4, #828]
	cmp	ip, #0
	beq	.L890
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #2528]
	blx	ip
.L890:
	add	r1, r6, #86016
	ldr	r0, [r4, #2528]
	add	r1, r1, #780
	mvn	r5, #0
	bl	MP2_ClearCurPacket
	b	.L871
.L883:
	ldrb	r3, [r9]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L940
.L891:
	ldr	r3, .L941+12
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L929
.L928:
	mov	r3, #0
	ldr	r0, [r4, #2528]
	mov	r2, r3
	mov	r1, #113
	blx	ip
	b	.L929
.L889:
	ldr	r1, .L941+36
	mov	r0, #1
	bl	dprint_vfmw
	b	.L871
.L939:
	ldr	r3, [r4, #828]
	tst	r3, #4194304
	beq	.L870
	orr	r3, r3, #8388608
	strb	r5, [r4, #2546]
	str	r3, [r4, #828]
	mov	r0, r6
	strb	r5, [r4, #2544]
	str	r7, [r4, #884]
	bl	MP2_ProtocolPPSCheck
	b	.L871
.L892:
	mov	r0, r6
	bl	MP2_GetSequenceInfo
	ldr	r5, [r4, #876]
	cmp	r5, #0
	beq	.L871
	ldrb	r3, [r4, #2545]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r5, r7
	beq	.L871
	ldr	r5, [r4, #824]
	cmp	r5, #0
	bne	.L894
	b	.L871
.L940:
	mov	r2, #196
	mov	r1, r9
	mov	r0, r8
	bl	memcpy
	ldr	r2, .L941+12
	ldr	r3, [r4, #828]
	ldr	ip, [r2]
	bic	r3, r3, #7
	str	r3, [r4, #828]
	cmp	ip, #0
	bne	.L928
	b	.L929
.L936:
	ldr	r3, .L941+12
	ldr	r2, [fp, #-80]
	ldr	ip, [r3]
	str	r2, [r4, #828]
	cmp	ip, #0
	beq	.L887
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #2528]
	blx	ip
.L887:
	add	r1, r6, #86016
	ldr	r0, [r4, #2528]
	add	r1, r1, #780
	mvn	r5, #0
	bl	MP2_ClearCurPacket
	mov	r2, #440
	ldr	r1, .L941+40
	mov	r0, #1
	bl	dprint_vfmw
	b	.L871
.L938:
	ldr	r3, .L941+12
	ldr	r2, [fp, #-80]
	ldr	ip, [r3]
	str	r2, [r4, #828]
	cmp	ip, #0
	beq	.L882
	mov	r3, #0
	mov	r1, #113
	mov	r2, r3
	ldr	r0, [r4, #2528]
	blx	ip
.L882:
	add	r1, r6, #86016
	ldr	r0, [r4, #2528]
	add	r1, r1, #780
	mvn	r5, #0
	bl	MP2_ClearCurPacket
	movw	r2, #435
	ldr	r1, .L941+44
	mov	r0, #1
	bl	dprint_vfmw
	b	.L871
.L942:
	.align	2
.L941:
	.word	.LC70
	.word	.LC68
	.word	.LC74
	.word	g_event_report
	.word	.LC72
	.word	.LC73
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC77
	.word	.LC76
	.word	.LC75
	.word	.LC71
	.word	.LC69
	UNWIND(.fnend)
	.size	MP2_GetHDR, .-MP2_GetHDR
	.align	2
	.global	MPEG2DEC_Decode
	.type	MPEG2DEC_Decode, %function
MPEG2DEC_Decode:
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
	ldr	r3, .L981
	add	r7, r0, #87040
	add	r6, r7, #592
	add	r5, r0, #86016
	add	r8, r0, #45312
	mov	r2, #160
	ldr	r3, [r3, #52]
	mov	r4, r0
	mov	r0, r6
	blx	r3
	mov	r1, r6
	ldr	r2, [r5, #2528]
	mov	r0, r8
	bl	MP2_ReceivePacket
	cmp	r0, #1
	beq	.L944
	ldr	r1, .L981+4
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
.L945:
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L944:
	ldr	r2, [r5, #792]
	add	r0, r7, #48
	ldr	r1, [r5, #808]
	bl	BsInit
	ldr	r3, [r4]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L976
.L946:
	ldr	r3, [r5, #828]
	str	r3, [r5, #1012]
.L947:
	mov	r0, r4
	bl	MP2_GetHDR
	add	r0, r0, #1
	cmp	r0, #1
	bls	.L977
	mov	r0, r4
	bl	MP2_DecodingDecide
	subs	r6, r0, #0
	beq	.L978
	cmn	r6, #1
	beq	.L975
	mov	r0, r4
	bl	MP2_GetPictureInfo
	subs	r6, r0, #0
	bne	.L953
	add	r1, r8, #41472
	ldr	r0, [r5, #2528]
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L981+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L954
	ldr	r0, [r5, #2528]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	ip
.L954:
	ldr	r1, .L981+12
	mov	r0, #1
	bl	dprint_vfmw
	mov	r6, #0
	b	.L945
.L977:
	ldr	r3, [r4]
	ldr	r2, [r3, #840]
	cmp	r2, #1
	beq	.L979
.L949:
	ldrb	r3, [r5, #2545]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L975
	add	r1, r8, #41472
	ldr	r0, [r5, #2528]
	add	r1, r1, #12
	mov	r6, #0
	bl	MP2_ClearCurPacket
	b	.L945
.L978:
	add	r1, r8, #41472
	ldr	r0, [r5, #2528]
	add	r1, r1, #12
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L981+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L952
	ldr	r0, [r5, #2528]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	ip
.L952:
	ldr	r1, .L981+16
	mov	r0, #22
	bl	dprint_vfmw
.L975:
	mov	r6, #0
	mov	r0, r6
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L976:
	ldr	r3, [r3, #888]
	cmp	r3, #1
	ldreq	r3, [r5, #1012]
	streq	r3, [r5, #828]
	bne	.L946
	b	.L947
.L979:
	ldr	r3, [r3, #888]
	cmp	r3, #0
	beq	.L949
	b	.L975
.L953:
	mov	r0, r4
	bl	MP2_DecNewPic
	subs	r6, r0, #0
	beq	.L980
	ldr	r6, [r5, #776]
	ldr	r3, [r5, #880]
	ldr	r2, [r5, #792]
	mov	r6, r6, asl #3
	add	r3, r3, r2
	str	r3, [r5, #880]
	b	.L945
.L980:
	mov	r2, #1
	ldr	r1, [r5, #912]
	ldr	r0, [r5, #2528]
	bl	FSP_ClearLogicFs
	add	r1, r8, #41472
	add	r1, r1, #12
	ldr	r0, [r5, #2528]
	bl	MP2_ClearCurPacket
	mov	r0, r4
	bl	MP2_ClearCurPic
	ldr	r3, .L981+8
	ldr	ip, [r3]
	cmp	ip, #0
	beq	.L956
	ldr	r0, [r5, #2528]
	mov	r3, r6
	mov	r2, r6
	mov	r1, #113
	blx	ip
.L956:
	ldr	r1, .L981+20
	mov	r0, #1
	bl	dprint_vfmw
	b	.L945
.L982:
	.align	2
.L981:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC78
	.word	g_event_report
	.word	.LC80
	.word	.LC79
	.word	.LC81
	UNWIND(.fnend)
	.size	MPEG2DEC_Decode, .-MPEG2DEC_Decode
	.align	2
	.global	MP2_GetPacketState
	.type	MP2_GetPacketState, %function
MP2_GetPacketState:
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
	add	r0, r0, #86016
	ldrb	r3, [r0, #2544]	@ zero_extendqisi2
	cmp	r3, #1
	moveq	r0, #2
	movne	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	MP2_GetPacketState, .-MP2_GetPacketState
	.global	g_tmpusd
	.global	zigzag
	.global	default_intra_quantizer_matrix
	.section	.rodata
	.align	2
.LANCHOR0 = . + 0
	.type	__FUNCTION__.14740, %object
	.size	__FUNCTION__.14740, 19
__FUNCTION__.14740:
	.ascii	"MP2_DecodingDecide\000"
	.space	1
.LC0:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	10
	.word	12
	.word	14
	.word	16
	.word	18
	.word	20
	.word	22
	.word	24
	.word	28
	.word	32
	.word	36
	.word	40
	.word	44
	.word	48
	.word	52
	.word	56
	.word	64
	.word	72
	.word	80
	.word	88
	.word	96
	.word	104
	.word	112
	.type	CSWTCH.51, %object
	.size	CSWTCH.51, 12
CSWTCH.51:
	.word	5
	.word	1
	.word	2
	.type	frame_rate_Table, %object
	.size	frame_rate_Table, 64
frame_rate_Table:
	.word	0
	.word	23976
	.word	24000
	.word	25000
	.word	29970
	.word	30000
	.word	50000
	.word	59940
	.word	60000
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.type	tab_for_first_4bit, %object
	.size	tab_for_first_4bit, 128
tab_for_first_4bit:
	.word	8
	.word	4
	.word	9
	.word	5
	.word	5
	.word	4
	.word	4
	.word	4
	.word	3
	.word	3
	.word	3
	.word	3
	.word	2
	.word	3
	.word	2
	.word	3
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.word	1
	.type	tab_for_last_7bit, %object
	.size	tab_for_last_7bit, 832
tab_for_last_7bit:
	.word	33
	.word	11
	.word	32
	.word	11
	.word	31
	.word	11
	.word	30
	.word	11
	.word	29
	.word	11
	.word	28
	.word	11
	.word	27
	.word	11
	.word	26
	.word	11
	.word	25
	.word	11
	.word	24
	.word	11
	.word	23
	.word	11
	.word	22
	.word	11
	.word	21
	.word	10
	.word	21
	.word	10
	.word	20
	.word	10
	.word	20
	.word	10
	.word	19
	.word	10
	.word	19
	.word	10
	.word	18
	.word	10
	.word	18
	.word	10
	.word	17
	.word	10
	.word	17
	.word	10
	.word	16
	.word	10
	.word	16
	.word	10
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	15
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	14
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	13
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	12
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	11
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	10
	.word	8
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	9
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.word	8
	.word	7
	.data
	.align	2
.LANCHOR2 = . + 0
	.type	default_intra_quantizer_matrix, %object
	.size	default_intra_quantizer_matrix, 64
default_intra_quantizer_matrix:
	.byte	8
	.byte	16
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	16
	.byte	16
	.byte	22
	.byte	24
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	19
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	34
	.byte	38
	.byte	22
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	37
	.byte	40
	.byte	22
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	26
	.byte	27
	.byte	29
	.byte	32
	.byte	35
	.byte	40
	.byte	48
	.byte	58
	.byte	26
	.byte	27
	.byte	29
	.byte	34
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	27
	.byte	29
	.byte	35
	.byte	38
	.byte	46
	.byte	56
	.byte	69
	.byte	83
	.type	zigzag, %object
	.size	zigzag, 64
zigzag:
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
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC1:
	ASCII(.ascii	"image size abnormal(%dx%d)\012\000" )
.LC2:
	ASCII(.ascii	"mp2 actual frame size(%dx%d) exeed max config(%dx%d" )
	ASCII(.ascii	")\012\000" )
	.space	2
.LC3:
	ASCII(.ascii	"user set decode channel max resolution is (w=%d,h=%" )
	ASCII(.ascii	"d), this stream (w=%d,h=%d) can NOT be decoded!\012" )
	ASCII(.ascii	"\000" )
.LC4:
	ASCII(.ascii	"partition fs memory fail!\012\000" )
	.space	1
.LC5:
	ASCII(.ascii	"FSP_ConfigInstance fail!\012\000" )
	.space	2
.LC6:
	ASCII(.ascii	"ERROR: frm %d, integrality: %#x\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"ERROR: frm %d, No Img buffer is allocated\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"----------------- mp2 Imode -> %d -----------------" )
	ASCII(.ascii	"-\012\000" )
	.space	2
.LC9:
	ASCII(.ascii	"frm %d pic type %d struct is %d total pos %#x\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"NOTE: Drop non-I, cur is B\012\000" )
.LC11:
	ASCII(.ascii	"NOTE: Drop non-I, cur is P\012\000" )
.LC12:
	ASCII(.ascii	"NOTE: Drop non-I\012\000" )
	.space	2
.LC13:
	ASCII(.ascii	"NOTE: Drop B\012\000" )
	.space	2
.LC14:
	ASCII(.ascii	"%s %d pFwdImg = NULL,  pBwdImg = NULL!!\012\000" )
	.space	3
.LC15:
	ASCII(.ascii	"fuction return value is null,%s %d !!\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"dec P frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC17:
	ASCII(.ascii	"dec B frame, bwd ref err(%d) > ref_thr(%d)\012\000" )
.LC18:
	ASCII(.ascii	"dec B frame, fwd ref err(%d) > ref_thr(%d)\012\000" )
.LC19:
	ASCII(.ascii	"Protocol %d\012\000" )
	.space	3
.LC20:
	ASCII(.ascii	"seq size change, call vpss to release all frames.\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC21:
	ASCII(.ascii	"IsSizeChanged = %d,TotalPicNum = %d,old w/h = %d/%d" )
	ASCII(.ascii	",new w/h = %d/%d\012\000" )
	.space	3
.LC22:
	ASCII(.ascii	"new seq size %dx%d\012\000" )
.LC23:
	ASCII(.ascii	"get frame store fail!\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"line: %d, pImage is NULL!\012\000" )
	.space	1
.LC25:
	ASCII(.ascii	"get image buffer ok: LogicFsID = %d\012\000" )
	.space	3
.LC26:
	ASCII(.ascii	"decode %p, disp %p, tf %p\012\000" )
	.space	1
.LC27:
	ASCII(.ascii	"ERROR: frm %d, lost one field\012\000" )
	.space	1
.LC28:
	ASCII(.ascii	"ERROR: frm %d, lost one field flg = %d, last_struct" )
	ASCII(.ascii	" = %d\012\000" )
	.space	2
.LC29:
	ASCII(.ascii	"Fatal Error: frm%d, get image buffer failed\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"dec_pts: %lld Usertag: %lld\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"---------- unref %d\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"++++++++++ ref %d\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"line: %d(pCur, pFwd, pBwd)(%p, %p, %p)\012\000" )
.LC34:
	ASCII(.ascii	"CurFsID(fwd%d,%d,bwd%d) abnormal!(%p,%p,%p)\012\000" )
	.space	3
.LC35:
	ASCII(.ascii	"dec addr: cur,cur2d,fwd,bwd,pmv = %p,%p,%p,%p,%p\012" )
	ASCII(.ascii	"\000" )
	.space	2
.LC36:
	ASCII(.ascii	"\012mpeg2 copy last 3 bytes of the first packet!\012" )
	ASCII(.ascii	"\012\000" )
.LC37:
	ASCII(.ascii	"pMp2CodecInfo->pUsrDatArray[%d] is null\012\000" )
	.space	3
.LC38:
	ASCII(.ascii	"ERROR: unsupported profile %d\012\000" )
	.space	1
.LC39:
	ASCII(.ascii	"ERROR: unsupported level %d\012\000" )
	.space	3
.LC40:
	ASCII(.ascii	"-1 == VCTRL_GetChanIDByCtx() Err! \012\000" )
.LC41:
	ASCII(.ascii	"Decoding quits at frm %d\012\000" )
	.space	2
.LC42:
	ASCII(.ascii	"ERROR: frm %d, Invalid packet pointer!\012\000" )
.LC43:
	ASCII(.ascii	"line %d, pPacket->StreamPack[1].IsLastSeg = %d\012\000" )
.LC44:
	ASCII(.ascii	"ErrRatio = %d\012\000" )
	.space	1
.LC45:
	ASCII(.ascii	"pImg is null, pCurImg %#x pBwdImg %#x pFwdImg %#x\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC46:
	ASCII(.ascii	"DEBUG: DEC over\012\000" )
	.space	3
.LC47:
	ASCII(.ascii	"insert buf %d ref %d\012\000" )
	.space	2
.LC48:
	ASCII(.ascii	"ERROR,pBwdImg == NULL || pToQueImg == NULL\012\000" )
.LC49:
	ASCII(.ascii	"exg_pts: %lld <-> %lld\012\000" )
.LC50:
	ASCII(.ascii	"err(%d) > out_thr(%d)\012\000" )
	.space	1
.LC51:
	ASCII(.ascii	"%-40s%20d\012\000" )
	.space	1
.LC52:
	ASCII(.ascii	"slice_vertical_position\000" )
.LC53:
	ASCII(.ascii	"quantiser_scale_code\000" )
	.space	3
.LC54:
	ASCII(.ascii	"extra_bit_slice\000" )
.LC55:
	ASCII(.ascii	"intra_slice_flag\000" )
	.space	3
.LC56:
	ASCII(.ascii	"intra_slice\000" )
.LC57:
	ASCII(.ascii	"reserved_bits\000" )
	.space	2
.LC58:
	ASCII(.ascii	"extra_infrmation_slice\000" )
	.space	1
.LC59:
	ASCII(.ascii	"Slice num = %d >= %d\012\000" )
	.space	2
.LC60:
	ASCII(.ascii	"seg info is wrong! IsLastSeg[0] = %d, IsLastSeg[1] " )
	ASCII(.ascii	"= %d\012\000" )
	.space	3
.LC61:
	ASCII(.ascii	"macroblock_address_increment\000" )
	.space	3
.LC62:
	ASCII(.ascii	"macroblock_escape ERROR\012\000" )
	.space	3
.LC63:
	ASCII(.ascii	"macroblock_escape\000" )
	.space	2
.LC64:
	ASCII(.ascii	"SlcStartMbNum = %d > PicEndMum = %d\012\000" )
	.space	3
.LC65:
	ASCII(.ascii	"FirstMbInSliceFlag = %d\012\000" )
	.space	3
.LC66:
	ASCII(.ascii	"MP2_GetFirstMbInSlice Failed!\012\000" )
	.space	1
.LC67:
	ASCII(.ascii	"MP2_WriteSliceInfo Failed!\012\000" )
.LC68:
	ASCII(.ascii	"found sh %#x\012\000" )
	.space	2
.LC69:
	ASCII(.ascii	"SEQUENCE_HEADER_CODE Bitstream is not enough!\012\000" )
	.space	1
.LC70:
	ASCII(.ascii	"found gh %#x\012\000" )
	.space	2
.LC71:
	ASCII(.ascii	"GROUP_START_CODE Bitstream is not enough!\012\000" )
	.space	1
.LC72:
	ASCII(.ascii	"found ph %#x\012\000" )
	.space	2
.LC73:
	ASCII(.ascii	"PICTURE_START_CODE Bitstream is not enough!\012\000" )
	.space	3
.LC74:
	ASCII(.ascii	"found ud %#x\012\000" )
	.space	2
.LC75:
	ASCII(.ascii	"cann't get ud pointer\012\000" )
	.space	1
.LC76:
	ASCII(.ascii	"found ext %#x\012\000" )
	.space	1
.LC77:
	ASCII(.ascii	"MP2_DecSlice is wrong!\012\000" )
.LC78:
	ASCII(.ascii	"line %d, MP2_ReceivePacket receive packet failed!\012" )
	ASCII(.ascii	"\000" )
	.space	1
.LC79:
	ASCII(.ascii	"MP2 Decode Decide is wrong!\012\000" )
	.space	3
.LC80:
	ASCII(.ascii	"MP2 get picture info is wrong!\012\000" )
.LC81:
	ASCII(.ascii	"MP2 dec new pic failed!\012\000" )
	.bss
	.align	2
.LANCHOR1 = . + 0
	.type	g_tmpusd, %object
	.size	g_tmpusd, 1024
g_tmpusd:
	.space	1024
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
