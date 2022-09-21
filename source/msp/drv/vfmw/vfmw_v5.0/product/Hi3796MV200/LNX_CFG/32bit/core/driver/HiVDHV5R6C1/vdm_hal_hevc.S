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
	.file	"vdm_hal_hevc.c"
	.text
	.align	2
	.global	HEVCWriteCabacTab
	.type	HEVCWriteCabacTab, %function
HEVCWriteCabacTab:
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
	ldr	r6, .L19
	mov	r9, #0
	ldr	r10, .L19+4
	mov	r1, r9
	mov	r8, r9
	mov	r7, r9
	mov	r5, #16
.L2:
	add	lr, r5, r9
	mov	r4, r1, asl #1
	rsb	r5, r1, r5
	add	ip, r6, r4
	add	lr, r10, lr, lsl #2
.L6:
	ldr	r3, [lr], #4
	add	r1, r1, #1
	add	ip, ip, #2
	cmn	r3, #1
	and	r2, r3, #15
	mov	r3, r3, asr #4
	streqb	r7, [r6, r4]
	mov	r2, r2, asl #3
	streqb	r7, [ip, #-1]
	addne	r3, r3, r3, lsl #2
	subne	r2, r2, #16
	subne	r3, r3, #45
	strneb	r3, [r6, r4]
	add	r3, r5, r1
	strneb	r2, [ip, #-1]
	cmp	r3, #159
	mov	r4, r1, asl #1
	ble	.L6
	add	r8, r8, #1
	cmp	r8, #3
	beq	.L17
	cmp	r8, #0
	add	r9, r9, #160
	moveq	r5, #16
	movne	r5, #0
	b	.L2
.L17:
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	addne	r3, r3, #2
	ldrne	r2, .L19+8
	addne	r0, r2, #928
	beq	.L18
.L10:
	ldrb	r1, [r2, #-1]	@ zero_extendqisi2
	add	r3, r3, #2
	strb	r1, [r3, #-3]
	ldrb	r1, [r2], #2	@ zero_extendqisi2
	cmp	r2, r0
	strb	r1, [r3, #-4]
	bne	.L10
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L18:
	ldr	r3, .L19+12
	ldr	r2, .L19+16
	ldr	r1, .L19+20
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L20:
	.align	2
.L19:
	.word	.LANCHOR0
	.word	.LANCHOR1+20
	.word	.LANCHOR0+1
	.word	.LC0
	.word	.LANCHOR1
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCWriteCabacTab, .-HEVCWriteCabacTab
	.align	2
	.global	HEVCHAL_V5R6C1_InitHal
	.type	HEVCHAL_V5R6C1_InitHal, %function
HEVCHAL_V5R6C1_InitHal:
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
	ldr	r0, [r0, #1108]
	bl	HEVCWriteCabacTab
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	ldr	r1, .L26
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L27:
	.align	2
.L26:
	.word	.LC2
	UNWIND(.fnend)
	.size	HEVCHAL_V5R6C1_InitHal, .-HEVCHAL_V5R6C1_InitHal
	.align	2
	.global	HEVCGet_V5R6C1_VirAddr
	.type	HEVCGet_V5R6C1_VirAddr, %function
HEVCGet_V5R6C1_VirAddr:
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
	.size	HEVCGet_V5R6C1_VirAddr, .-HEVCGet_V5R6C1_VirAddr
	.align	2
	.global	HEVCGet_V5R6C1_PhyAddr
	.type	HEVCGet_V5R6C1_PhyAddr, %function
HEVCGet_V5R6C1_PhyAddr:
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
	.size	HEVCGet_V5R6C1_PhyAddr, .-HEVCGet_V5R6C1_PhyAddr
	.align	2
	.global	HEVCHAL_V5R6C1_CutSliceChain
	.type	HEVCHAL_V5R6C1_CutSliceChain, %function
HEVCHAL_V5R6C1_CutSliceChain:
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
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	beq	.L33
	mov	r0, #0
	str	r0, [r3, #252]
	ldmfd	sp, {fp, sp, pc}
.L33:
	ldr	r3, .L34
	ldr	r2, .L34+4
	ldr	r1, .L34+8
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L35:
	.align	2
.L34:
	.word	.LC3
	.word	.LANCHOR1+1940
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R6C1_CutSliceChain, .-HEVCHAL_V5R6C1_CutSliceChain
	.align	2
	.global	HEVC_WriteQmatrix
	.type	HEVC_WriteQmatrix, %function
HEVC_WriteQmatrix:
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
	ldmeqfd	sp, {fp, sp, pc}
	sub	r0, r0, #4
	sub	r3, r3, #4
	mov	r2, #0
.L38:
	add	r2, r2, #1
	ldr	ip, [r0, #4]!
	cmp	r2, r1
	str	ip, [r3, #4]!
	bne	.L38
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix, .-HEVC_WriteQmatrix
	.align	2
	.global	HEVC_WriteTileInfo
	.type	HEVC_WriteTileInfo, %function
HEVC_WriteTileInfo:
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
	mov	r8, r0
	ldr	r0, [r1, #1112]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-48]
	beq	.L42
	add	r0, r3, #1024
	add	r9, r3, #4
	add	r0, r0, #4
	mov	r7, r8
	mov	r10, r8
	mov	r6, #0
.L43:
	mov	lr, r10
	mov	r4, r9
	mov	ip, #0
.L47:
	cmp	ip, #252
	add	ip, ip, #4
	strgt	r6, [r4, #-4]
	add	lr, lr, #4
	ldrleb	r3, [lr, #1738]	@ zero_extendqisi2
	add	r4, r4, #4
	ldrleb	r5, [lr, #1739]	@ zero_extendqisi2
	ldrleb	r2, [lr, #1736]	@ zero_extendqisi2
	movle	r3, r3, asl #16
	ldrleb	r1, [lr, #1737]	@ zero_extendqisi2
	orrle	r3, r3, r5, asl #24
	orrle	r3, r3, r2
	orrle	r3, r3, r1, asl #8
	strle	r3, [r4, #-8]
	cmp	ip, #512
	bne	.L47
	add	r9, r9, #512
	add	r10, r10, #256
	cmp	r9, r0
	bne	.L43
	mov	r3, #0
	mov	ip, r3
.L48:
	cmp	r3, #9
	add	r3, r3, #1
	strgt	ip, [r0, #-4]
	add	r8, r8, #8
	ldrle	r1, [r8, #2248]
	add	r0, r0, #4
	ldrle	r2, [r8, #2244]
	orrle	r2, r2, r1, asl #16
	strle	r2, [r0, #-8]
	cmp	r3, #20
	bne	.L48
	ldr	r3, [fp, #-48]
	add	r2, r3, #1104
	mov	r3, #0
	add	r2, r2, #4
	mov	ip, r3
.L54:
	cmp	r3, #10
	add	r3, r3, #1
	strgt	ip, [r2, #-4]
	add	r7, r7, #8
	ldrle	r0, [r7, #2328]
	add	r2, r2, #4
	ldrle	r1, [r7, #2324]
	orrle	r1, r1, r0, asl #16
	strle	r1, [r2, #-8]
	cmp	r3, #22
	bne	.L54
	mov	r0, #0
.L59:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L42:
	ldr	r3, .L62
	ldr	r2, .L62+4
	ldr	r1, .L62+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L59
.L63:
	.align	2
.L62:
	.word	.LC4
	.word	.LANCHOR1+1972
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVC_WriteTileInfo, .-HEVC_WriteTileInfo
	.align	2
	.global	HEVCHAL_V5R6C1_SetPicMsg
	.type	HEVCHAL_V5R6C1_SetPicMsg, %function
HEVCHAL_V5R6C1_SetPicMsg:
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
	mov	r0, r2
	str	r2, [fp, #-48]
	mov	r8, r1
	str	r3, [fp, #-52]
	bl	MEM_Phy2Vir
	subs	r7, r0, #0
	beq	.L82
	ldr	r3, .L84
	mov	r2, #1280
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, .L84+4
	mov	r0, #4
	bl	dprint_vfmw
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	ldr	lr, [r4, #20]
	mov	r0, #4
	ldrb	r1, [r4, #7]	@ zero_extendqisi2
	ldrb	ip, [r4, #8]	@ zero_extendqisi2
	mov	r2, r3, asl #25
	ldr	r5, [r4, #12]
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	orr	r1, r2, r1, asl #24
	mov	r2, lr, asl #9
	orr	r1, r1, ip, asl #23
	ldrb	lr, [r4, #10]	@ zero_extendqisi2
	orr	r5, r2, r5, asl #19
	ldr	ip, [r4, #24]
	orr	r3, r1, r3, asl #22
	ldrb	r2, [r4, #16]	@ zero_extendqisi2
	orr	ip, r5, ip
	orr	r3, r3, lr, asl #21
	ldr	r1, .L84+8
	orr	r2, ip, r2, asl #18
	orr	r2, r2, r3
	str	r2, [r7]
	bl	dprint_vfmw
	ldr	r2, [r4, #28]
	ldr	r1, .L84+12
	mov	r0, #4
	str	r2, [r7, #4]
	bl	dprint_vfmw
	ldr	r2, [r4, #44]
	ldr	ip, [r4, #36]
	mov	r0, #4
	ldr	r1, [r4, #76]
	ldr	r3, [r4, #48]
	mov	r2, r2, asl #24
	ldr	lr, [r4, #52]
	orr	ip, r2, ip, asl #29
	orr	r1, ip, r1
	ldr	r2, [r4, #56]
	ldr	ip, [r4, #60]
	orr	r3, r1, r3, asl #21
	orr	r3, r3, lr, asl #18
	ldr	r1, [r4, #64]
	ldr	lr, [r4, #68]
	orr	r2, r3, r2, asl #15
	orr	r2, r2, ip, asl #12
	ldr	r3, [r4, #72]
	ldrb	ip, [r4, #40]	@ zero_extendqisi2
	orr	r1, r2, r1, asl #9
	orr	r1, r1, lr, asl #6
	ldrb	r2, [r4, #41]	@ zero_extendqisi2
	orr	r3, r1, r3, asl #3
	ldr	r1, .L84+16
	orr	r3, r3, ip, asl #28
	orr	r2, r3, r2, asl #27
	str	r2, [r7, #8]
	bl	dprint_vfmw
	ldr	r2, [r4, #84]
	ldr	ip, [r4, #80]
	mov	r0, #4
	ldr	r1, [r4, #100]
	ldr	r3, [r4, #88]
	mov	r2, r2, asl #16
	orr	ip, r2, ip, asl #22
	ldr	lr, [r4, #92]
	orr	r1, ip, r1
	ldr	r2, [r4, #96]
	orr	r3, r1, r3, asl #12
	ldr	r1, .L84+20
	orr	r3, r3, lr, asl #8
	orr	r2, r3, r2, asl r0
	str	r2, [r7, #12]
	bl	dprint_vfmw
	ldr	r2, [r8, #1092]
	ldr	r1, .L84+24
	mov	r0, #4
	str	r2, [r7, #16]
	bl	dprint_vfmw
	ldr	r2, [r8, #1096]
	ldr	r1, .L84+28
	mov	r0, #4
	str	r2, [r7, #20]
	bl	dprint_vfmw
	ldr	r3, [r4, #1292]
	ldr	r1, .L84+32
	mov	r0, #4
	add	r3, r4, r3, lsl #2
	ldr	r2, [r3, #1476]
	str	r2, [r7, #24]
	bl	dprint_vfmw
	ldr	r2, [r8, #1104]
	ldr	r1, .L84+36
	mov	r0, #4
	str	r2, [r7, #28]
	bl	dprint_vfmw
	ldr	r5, [r4, #2484]
	cmp	r5, #0
	beq	.L67
	add	r9, r4, #2416
	add	r10, r7, #32
	mov	r6, #0
.L68:
	ldr	r3, [r9, #4]!
	add	r2, r6, #8
	ldr	r1, .L84+40
	mov	r0, #4
	add	r3, r3, #336
	add	r6, r6, #1
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r10], #4
	bl	dprint_vfmw
	ldr	r5, [r4, #2484]
	cmp	r5, r6
	bhi	.L68
	cmp	r5, #15
	bhi	.L71
.L67:
	add	r2, r5, #8
	add	r6, r7, r2, lsl #2
.L70:
	ldr	r3, [r4, #2420]
	add	r5, r5, #1
	ldr	r1, .L84+40
	mov	r0, #4
	add	r3, r3, #336
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r6], #4
	bl	dprint_vfmw
	cmp	r5, #15
	add	r2, r5, #8
	bls	.L70
.L71:
	ldr	r2, [r8, #1108]
	mov	r0, #4
	ldr	r1, .L84+44
	add	r9, r4, #124
	add	r6, r7, #104
	add	r10, r4, #188
	str	r2, [r7, #100]
	mov	r5, #26
	bl	dprint_vfmw
.L69:
	ldr	r3, [r9, #4]!
	mov	r2, r5
	ldr	r1, .L84+40
	mov	r0, #4
	add	r5, r5, #1
	str	r3, [r6], #4
	bl	dprint_vfmw
	cmp	r9, r10
	bne	.L69
	ldr	r2, [r8, #1100]
	mov	r0, #4
	ldr	r1, .L84+48
	str	r2, [r7, #172]
	bl	dprint_vfmw
	ldr	r2, [r4, #192]
	ldr	r3, [r4, #196]
	mov	r0, #4
	ldr	r1, .L84+52
	orr	r2, r3, r2, asl #16
	str	r2, [r7, #216]
	bl	dprint_vfmw
	mov	r1, r8
	mov	r0, r4
	bl	HEVC_WriteTileInfo
	subs	r5, r0, #0
	bne	.L83
	ldr	r2, [r8, #1112]
	mov	r0, #4
	ldr	r1, .L84+56
	str	r2, [r7, #220]
	bl	dprint_vfmw
	ldr	r2, [r8, #1124]
	ldr	r1, .L84+60
	mov	r0, #4
	str	r2, [r7, #224]
	bl	dprint_vfmw
	ldr	r2, [r8, #1116]
	ldr	r1, .L84+64
	mov	r0, #4
	str	r2, [r7, #228]
	bl	dprint_vfmw
	ldr	r2, [r8, #1128]
	ldr	r1, .L84+68
	mov	r0, #4
	str	r2, [r7, #232]
	bl	dprint_vfmw
	ldr	r2, [r8, #1120]
	ldr	r1, .L84+72
	mov	r0, #4
	str	r2, [r7, #236]
	bl	dprint_vfmw
	ldr	r3, [r4, #228]
	ldr	r1, [r4, #232]
	mov	r0, #4
	ldr	r2, [r4, #244]
	ldrb	ip, [r4, #220]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r1, r3, r1, asl #13
	and	r2, r2, #31
	ldrb	r3, [r4, #221]	@ zero_extendqisi2
	orr	r1, r1, r2
	ldrb	lr, [r4, #222]	@ zero_extendqisi2
	orr	r1, r1, ip, asl #24
	ldrb	r2, [r4, #223]	@ zero_extendqisi2
	ldrb	ip, [r4, #224]	@ zero_extendqisi2
	orr	r3, r1, r3, asl #23
	orr	r3, r3, lr, asl #22
	ldrb	r1, [r4, #225]	@ zero_extendqisi2
	ldrb	lr, [r4, #236]	@ zero_extendqisi2
	orr	r2, r3, r2, asl #21
	orr	r2, r2, ip, asl #20
	ldrb	r3, [r4, #237]	@ zero_extendqisi2
	ldr	ip, [r4, #240]
	orr	r1, r2, r1, asl #19
	ldrb	r2, [r4, #238]	@ zero_extendqisi2
	orr	r1, r1, lr, asl #12
	and	ip, ip, #31
	orr	r3, r1, r3, asl #11
	ldr	r1, .L84+76
	orr	r3, r3, r2, asl #10
	orr	r2, r3, ip, asl #5
	str	r2, [r7, #240]
	bl	dprint_vfmw
	ldr	r2, [r4, #248]
	ldr	r3, [r4, #252]
	mov	r0, #4
	ldr	r1, .L84+80
	orr	r2, r3, r2, asl #16
	str	r2, [r7, #244]
	bl	dprint_vfmw
	ldr	r3, [fp, #-52]
	ldr	r1, .L84+84
	mov	r0, #4
	mov	r2, r3
	str	r3, [r7, #252]
	bl	dprint_vfmw
	mov	r1, r7
	mov	r0, #64
	bl	HEVC_GetVirAddr
	ldr	r1, [fp, #-48]
	mov	r6, r0
	mov	r0, #64
	bl	HEVC_GetPhyAddr
	add	r3, r4, #256
	sub	r2, r6, #4
	add	r4, r4, #1280
.L73:
	ldr	r1, [r3, #4]!
	cmp	r3, r4
	str	r1, [r2, #4]!
	bne	.L73
.L66:
	mov	r0, r5
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L83:
	ldr	r1, .L84+88
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r5, #0
	b	.L66
.L82:
	ldr	r3, .L84+92
	mvn	r5, #0
	ldr	r2, .L84+96
	ldr	r1, .L84+100
	bl	dprint_vfmw
	b	.L66
.L85:
	.align	2
.L84:
	.word	vfmw_Osal_Func_Ptr_S
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
	.word	.LC17
	.word	.LC18
	.word	.LC20
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC19
	.word	.LC5
	.word	.LANCHOR1+1992
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R6C1_SetPicMsg, .-HEVCHAL_V5R6C1_SetPicMsg
	.align	2
	.global	HEVCHAL_SetSliceMsgStreamAddrInfo
	.type	HEVCHAL_SetSliceMsgStreamAddrInfo, %function
HEVCHAL_SetSliceMsgStreamAddrInfo:
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
	mov	r5, #0
	mov	r4, r2
	add	r7, r1, #16
	add	r10, r4, #8
	mov	r6, r3
	mov	r8, r5
	str	r1, [fp, #-52]
	str	r0, [fp, #-48]
.L92:
	cmp	r8, #0
	mov	r3, r6
	mov	r2, r5
	ldr	r1, .L95
	mov	r0, #4
	beq	.L94
	ldr	r9, [r7, #-16]
	cmp	r9, #0
	beq	.L90
.L88:
	ldr	r2, [fp, #-48]
	mov	r3, r6
	ldr	lr, [r7]
	mov	r0, #4
	ldr	r1, .L95
	ldr	ip, [r2, #1332]
	bic	lr, lr, #15
	mov	r2, r5
	bic	ip, ip, #15
	rsb	ip, ip, lr
	str	ip, [r4]
	ldr	ip, [r10, #-8]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r7]
	ldr	r0, [r7, #-8]
	add	r3, r6, #4
	add	r2, r5, #1
	ldr	r1, .L95
	add	ip, r0, ip, lsl #3
	mov	r0, #4
	and	ip, ip, #127
	str	ip, [r4, #4]
	ldr	ip, [r4, #4]
	str	ip, [sp]
	bl	dprint_vfmw
	ldr	ip, [r7, #-16]
	add	r3, r6, #8
	add	r2, r5, #2
	ldr	r1, .L95
	mov	r0, #4
	str	ip, [r10]
	ldr	ip, [r4, #8]
	str	ip, [sp]
	bl	dprint_vfmw
.L91:
	add	r8, r8, #1
	add	r7, r7, #4
	cmp	r8, #2
	add	r4, r4, #12
	add	r5, r5, #3
	add	r6, r6, #12
	add	r10, r10, #12
	bne	.L92
	mov	r0, #0
.L89:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L90:
	str	r9, [r4]
	ldr	lr, [r10, #-8]
	str	lr, [sp]
	bl	dprint_vfmw
	str	r9, [r4, #4]
	ldr	lr, [r4, #4]
	add	r3, r6, #4
	add	r2, r5, #1
	ldr	r1, .L95
	mov	r0, #4
	str	lr, [sp]
	bl	dprint_vfmw
	str	r9, [r10]
	ldr	ip, [r4, #8]
	add	r3, r6, #8
	add	r2, r5, #2
	ldr	r1, .L95
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L91
.L94:
	ldr	r3, [fp, #-52]
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L88
	mov	r0, r8
	ldr	r2, .L95+4
	ldr	r1, .L95+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L89
.L96:
	.align	2
.L95:
	.word	.LC29
	.word	.LANCHOR1+2020
	.word	.LC28
	UNWIND(.fnend)
	.size	HEVCHAL_SetSliceMsgStreamAddrInfo, .-HEVCHAL_SetSliceMsgStreamAddrInfo
	.align	2
	.global	HEVCHAL_SetSliceMsgAPCIndex
	.type	HEVCHAL_SetSliceMsgAPCIndex, %function
HEVCHAL_SetSliceMsgAPCIndex:
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
	ldr	r2, [r0, #68]
	cmp	r2, #0
	addne	r4, r0, #368
	movne	lr, #0
	movne	r6, #15
	movne	ip, lr
	beq	.L104
.L103:
	and	r3, ip, #7
	ldr	r5, [r4, #4]!
	cmp	r3, #7
	sub	r2, r2, #1
	mov	r3, r3, asl #2
	orr	lr, lr, r5, asl r3
	streq	lr, [r1, r6, asl #2]
	addeq	r6, r6, #1
	moveq	lr, #0
	beq	.L102
	cmp	r2, ip
	streq	lr, [r1, r6, asl #2]
.L102:
	ldr	r2, [r0, #68]
	add	ip, ip, #1
	cmp	r2, ip
	bhi	.L103
.L104:
	ldr	r2, [r0, #72]
	cmp	r2, #0
	beq	.L111
	mov	lr, #0
	add	r4, r0, #432
	mov	ip, lr
	mov	r6, #17
.L107:
	and	r3, ip, #7
	ldr	r5, [r4, #4]!
	cmp	r3, #7
	sub	r2, r2, #1
	mov	r3, r3, asl #2
	orr	lr, lr, r5, asl r3
	streq	lr, [r1, r6, asl #2]
	addeq	r6, r6, #1
	moveq	lr, #0
	beq	.L106
	cmp	r2, ip
	streq	lr, [r1, r6, asl #2]
.L106:
	ldr	r2, [r0, #72]
	add	ip, ip, #1
	cmp	r2, ip
	bhi	.L107
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L111:
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCHAL_SetSliceMsgAPCIndex, .-HEVCHAL_SetSliceMsgAPCIndex
	.align	2
	.global	HEVCHAL_SetSliceMsgWPInfo
	.type	HEVCHAL_SetSliceMsgWPInfo, %function
HEVCHAL_SetSliceMsgWPInfo:
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
	mov	r7, r0
	mov	r4, r1
	mov	r0, #64
	mov	r1, r2
	mov	r6, r2
	bl	HEVC_GetVirAddr
	mov	r1, r6
	mov	r5, r0
	mov	r0, #128
	bl	HEVC_GetVirAddr
	ldrb	r3, [r7, #41]	@ zero_extendqisi2
	cmp	r3, #0
	mov	lr, r0
	beq	.L113
	ldr	r3, [r4, #76]
	cmp	r3, #1
	beq	.L114
.L113:
	ldrb	r3, [r7, #40]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, [r4, #76]
	cmp	r3, #0
	bne	.L134
	ldr	r3, [r4, #68]
	cmp	r3, #0
	beq	.L121
.L120:
	mov	r1, #0
	add	r7, r4, #712
	add	r6, r4, #584
	mov	r0, r1
	mov	r3, r4
.L118:
	ldr	r8, [r7, #4]!
	add	ip, r1, #128
	ldr	r10, [r6, #4]!
	add	r0, r0, #1
	ldr	r9, [r4, #580]
	add	r3, r3, #8
	uxtb	r8, r8
	ubfx	r10, r10, #0, #9
	and	r9, r9, #7
	mov	r8, r8, asl #12
	orr	r2, r8, r10, asl #3
	orr	r2, r2, r9
	str	r2, [r5, r1]
	ldr	r9, [r3, #836]
	ldrb	r2, [r3, #1092]	@ zero_extendqisi2
	ldr	r8, [r4, #584]
	ubfx	r9, r9, #0, #9
	mov	r2, r2, asl #12
	and	r8, r8, #7
	orr	r2, r2, r9, asl #3
	orr	r2, r2, r8
	str	r2, [lr, r1]
	ldr	r2, [r3, #840]
	add	r1, r1, #4
	ldrb	r8, [r3, #1096]	@ zero_extendqisi2
	ubfx	r2, r2, #0, #9
	orr	r2, r2, r8, asl #9
	str	r2, [lr, ip]
	ldr	r2, [r4, #68]
	cmp	r2, r0
	bhi	.L118
	ldr	r3, [r4, #76]
	cmp	r3, #0
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L121:
	ldr	r3, [r4, #72]
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r1, #0
	add	r7, r4, #776
	add	r6, r4, #648
	mov	ip, r1
	mov	r2, r4
.L119:
	ldr	r8, [r7, #4]!
	add	r10, r1, #64
	ldr	r3, [r6, #4]!
	add	r0, r1, #192
	ldr	r9, [r4, #580]
	add	ip, ip, #1
	uxtb	r8, r8
	ubfx	r3, r3, #0, #9
	and	r9, r9, #7
	add	r2, r2, #8
	mov	r8, r8, asl #12
	add	r1, r1, #4
	orr	r3, r8, r3, asl #3
	orr	r3, r3, r9
	str	r3, [r5, r10]
	ldr	r3, [r2, #964]
	ldrb	r9, [r2, #1220]	@ zero_extendqisi2
	ldr	r8, [r4, #584]
	ubfx	r3, r3, #0, #9
	mov	r9, r9, asl #12
	and	r8, r8, #7
	orr	r3, r9, r3, asl #3
	orr	r3, r3, r8
	str	r3, [lr, r10]
	ldr	r3, [r2, #968]
	ldrb	r8, [r2, #1224]	@ zero_extendqisi2
	ubfx	r3, r3, #0, #9
	orr	r3, r3, r8, asl #9
	str	r3, [lr, r0]
	ldr	r3, [r4, #72]
	cmp	r3, ip
	bhi	.L119
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L114:
	ldr	r3, [r4, #68]
	cmp	r3, #0
	bne	.L120
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L134:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCHAL_SetSliceMsgWPInfo, .-HEVCHAL_SetSliceMsgWPInfo
	.global	__aeabi_uidivmod
	.global	__aeabi_uidiv
	.align	2
	.global	HEVCHAL_V5R6C1_SetSliceMsg
	.type	HEVCHAL_V5R6C1_SetSliceMsg, %function
HEVCHAL_V5R6C1_SetSliceMsg:
	UNWIND(.fnstart)
	@ args = 24, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r3, r4, r5, r6, r7, r8, r9, r10, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	mov	r0, r3
	mov	r7, r3
	mov	r8, r2
	ldr	r6, [fp, #12]
	ldr	r10, [fp, #16]
	bl	MEM_Phy2Vir
	subs	r4, r0, #0
	beq	.L147
	ldr	r3, .L148
	mov	r2, #1280
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, .L148+4
	mov	r0, #4
	bl	dprint_vfmw
	mov	r3, r7
	mov	r2, r4
	mov	r1, r8
	mov	r0, r5
	bl	HEVCHAL_SetSliceMsgStreamAddrInfo
	cmn	r0, #1
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldrb	r7, [r8, #24]	@ zero_extendqisi2
	mov	r0, #4
	ldrb	r3, [r8, #25]	@ zero_extendqisi2
	ldr	r1, [r8, #28]
	ldrb	r2, [r8, #32]	@ zero_extendqisi2
	mov	r7, r7, asl #27
	and	r1, r1, #127
	orr	r3, r7, r3, asl #26
	ldr	r7, [r8, #36]
	orr	lr, r3, r1, asl #19
	ldr	r1, .L148+8
	orr	r3, lr, r2, asl #18
	orr	r2, r3, r7
	str	r2, [r4, #24]
	bl	dprint_vfmw
	ldr	r3, [r8, #44]
	ldr	lr, [r8, #56]
	mov	r0, #4
	ldr	r7, [r8, #60]
	ldr	ip, [r8, #72]
	mov	r3, r3, asl #24
	ldr	r1, [r8, #76]
	orr	r3, r3, lr, asl #20
	ldr	r2, .L148+12
	orr	r3, r3, r7, asl #16
	orr	r7, r3, ip, asl #8
	ldr	r3, [r8, #68]
	add	r2, r2, r1, lsl #2
	ldrb	r1, [r8, #64]	@ zero_extendqisi2
	ldr	lr, [r2, #2084]
	orr	r3, r7, r3, asl #2
	ldrb	r2, [r8, #65]	@ zero_extendqisi2
	orr	r3, r3, lr
	ldrb	r7, [r8, #52]	@ zero_extendqisi2
	orr	r3, r3, r1, asl #15
	ldr	r1, [r8, #40]
	orr	r3, r3, r2, asl #14
	mov	lr, r1, asl #28
	ldr	r1, .L148+16
	orr	r2, lr, r7, asl #27
	orr	r2, r3, r2
	str	r2, [r4, #28]
	bl	dprint_vfmw
	mov	r2, r6
	str	r6, [r4, #32]
	mov	r0, #4
	ldr	r1, .L148+20
	bl	dprint_vfmw
	ldr	r3, [r5, #24]
	mov	r0, r6
	add	r9, r3, #1
	mov	r1, r9
	bl	__aeabi_uidivmod
	mov	r0, r6
	mov	r7, r1
	mov	r1, r9
	bl	__aeabi_uidiv
	ldr	r1, .L148+24
	orr	r2, r7, r0, asl #16
	mov	r0, #4
	str	r2, [r4, #36]
	bl	dprint_vfmw
	mov	r2, r10
	ldr	r1, .L148+28
	mov	r0, #4
	str	r10, [r4, #40]
	bl	dprint_vfmw
	ldr	r2, [r8, #96]
	ldr	r3, [r8, #100]
	mov	r0, #4
	and	r2, r2, #31
	ldr	r1, .L148+32
	and	r3, r3, #31
	orr	r2, r3, r2, asl #8
	str	r2, [r4, #44]
	bl	dprint_vfmw
	ldr	r3, [r8, #108]
	ldr	lr, [r8, #104]
	mov	r0, #4
	and	r3, r3, #15
	ldrb	r1, [r8, #115]	@ zero_extendqisi2
	and	lr, lr, #15
	ldrb	r7, [r8, #113]	@ zero_extendqisi2
	mov	r3, r3, asl #8
	ldrb	r2, [r8, #112]	@ zero_extendqisi2
	orr	r3, r3, lr, asl #16
	ldrb	r6, [r8, #114]	@ zero_extendqisi2
	orr	lr, r3, r1
	ldr	r1, .L148+36
	orr	r3, lr, r7, asl #3
	orr	r3, r3, r2, asl #2
	orr	r2, r3, r6, asl #1
	str	r2, [r4, #48]
	bl	dprint_vfmw
	ldr	lr, [r8, #68]
	cmp	lr, #0
	beq	.L143
	mov	r2, #0
	add	r1, r8, #112
	mov	r3, r2
.L139:
	ldr	r0, [r1, #4]!
	orr	r2, r2, r0, asl r3
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L139
	mov	lr, r2
.L138:
	str	lr, [r4, #52]
	mov	r0, #4
	ldr	r1, .L148+40
	bl	dprint_vfmw
	ldr	lr, [r8, #72]
	cmp	lr, #0
	beq	.L144
	mov	r2, #0
	add	r1, r8, #176
	mov	r3, r2
.L141:
	ldr	r0, [r1, #4]!
	orr	r2, r2, r0, asl r3
	add	r3, r3, #1
	cmp	r3, lr
	bne	.L141
	mov	lr, r2
.L140:
	str	lr, [r4, #56]
	mov	r0, #4
	ldr	r1, .L148+44
	bl	dprint_vfmw
	mov	r1, r4
	mov	r0, r8
	bl	HEVCHAL_SetSliceMsgAPCIndex
	ldr	r2, [r8, #564]
	ldr	r1, .L148+48
	mov	r0, #4
	str	r2, [r4, #92]
	bl	dprint_vfmw
	ldr	r2, [r5, #84]
	ldr	r1, .L148+52
	mov	r0, #4
	mov	r2, r2, lsr #1
	mov	r2, r2, asl #8
	orr	r2, r2, #16384
	orr	r2, r2, #10
	str	r2, [r4, #96]
	bl	dprint_vfmw
	ldr	r6, [r5, #2492]
	ldrb	r2, [r8, #1357]	@ zero_extendqisi2
	mov	r0, #4
	ldr	r1, .L148+56
	ldr	r3, [r6, #1360]
	and	r7, r2, #1
	ldr	r10, [r6, #1368]
	ldr	lr, [r6, #1364]
	mov	r3, r3, asl #14
	ubfx	r10, r10, #0, #14
	ubfx	lr, lr, #0, #14
	uxth	r3, r3
	orr	r3, r3, r10, asl #16
	orr	r3, r3, lr
	orr	r2, r3, r7, asl #30
	str	r2, [r4, #100]
	bl	dprint_vfmw
	ldr	r2, [r6, #1384]
	ldr	r1, .L148+60
	mov	r0, #4
	ubfx	r2, r2, #0, #17
	str	r2, [r4, #104]
	bl	dprint_vfmw
	ldr	r2, [r6, #1444]
	ldr	r1, .L148+64
	mov	r0, #4
	str	r2, [r4, #108]
	bl	dprint_vfmw
	ldr	r2, [r6, #1448]
	ldr	r1, .L148+68
	mov	r0, #4
	str	r2, [r4, #112]
	bl	dprint_vfmw
	ldr	r3, [r6, #1400]
	ldr	r2, [r6, #1396]
	mov	r0, #4
	ldr	r1, .L148+72
	uxth	r3, r3
	orr	r2, r3, r2, asl #16
	str	r2, [r4, #116]
	bl	dprint_vfmw
	ldr	r3, [r6, #1416]
	ldr	r2, [r6, #1412]
	mov	r0, #4
	ldr	r1, .L148+76
	uxth	r3, r3
	orr	r2, r3, r2, asl #16
	str	r2, [r4, #120]
	bl	dprint_vfmw
	ldr	r2, [r6, #1392]
	ldr	r1, .L148+80
	mov	r0, #4
	ubfx	r2, r2, #0, #17
	str	r2, [r4, #124]
	bl	dprint_vfmw
	ldr	r2, [r6, #1452]
	ldr	r1, .L148+84
	mov	r0, #4
	str	r2, [r4, #128]
	bl	dprint_vfmw
	ldr	r2, [r6, #1456]
	ldr	r1, .L148+88
	mov	r0, #4
	str	r2, [r4, #132]
	bl	dprint_vfmw
	ldr	r3, [r6, #1408]
	ldr	r2, [r6, #1404]
	mov	r0, #4
	ldr	r1, .L148+92
	uxth	r3, r3
	orr	r2, r3, r2, asl #16
	str	r2, [r4, #136]
	bl	dprint_vfmw
	ldr	r3, [r6, #1424]
	ldr	r2, [r6, #1420]
	mov	r0, #4
	ldr	r1, .L148+96
	uxth	r3, r3
	orr	r2, r3, r2, asl #16
	str	r2, [r4, #140]
	bl	dprint_vfmw
	ldr	r1, [r6, #1432]
	ldr	r3, [r6, #1436]
	mov	r0, #4
	and	r1, r1, #31
	ldr	lr, [r6, #1440]
	ldr	r2, [r6, #1428]
	and	r7, r3, #31
	mov	r1, r1, asl #16
	and	lr, lr, #31
	orr	r3, r1, r7, asl #8
	and	r2, r2, #31
	orr	r3, r3, lr
	ldr	r1, .L148+100
	orr	r2, r3, r2, asl #24
	str	r2, [r4, #144]
	bl	dprint_vfmw
	ldr	r1, [r6, #1472]
	ldr	lr, [r6, #1376]
	mov	r0, #4
	ldr	r7, [r6, #1372]
	add	lr, lr, #15
	ldr	r2, [r6, #1468]
	ldrb	r10, [r6, #1356]	@ zero_extendqisi2
	mov	r1, r1, asl r0
	add	r7, r7, #15
	mov	lr, lr, asr r0
	and	r2, r2, #15
	and	r10, r10, #1
	mov	r7, r7, asr r0
	uxtb	r1, r1
	sub	lr, lr, #1
	orr	r1, r1, r2
	ubfx	lr, lr, #0, #9
	sub	r7, r7, #1
	orr	r3, r1, r10, asl #26
	ubfx	r7, r7, #0, #9
	orr	r3, r3, lr, asl #8
	ldr	r1, .L148+104
	orr	r2, r3, r7, asl #17
	str	r2, [r4, #148]
	bl	dprint_vfmw
	ldr	r3, [r6, #1464]
	ldr	r2, [r6, #1460]
	mov	r0, #4
	ubfx	r3, r3, #0, #13
	ldr	r1, .L148+108
	orr	r2, r3, r2, asl #16
	str	r2, [r4, #152]
	bl	dprint_vfmw
	ldr	r2, [r6, #1476]
	ldr	r1, .L148+112
	mov	r0, #4
	ubfx	r2, r2, #0, #20
	str	r2, [r4, #156]
	bl	dprint_vfmw
	ldr	r2, [r6, #1480]
	ldr	r1, .L148+116
	mov	r0, #4
	str	r2, [r4, #160]
	bl	dprint_vfmw
	ldr	r2, [r6, #1484]
	ldr	r1, .L148+120
	mov	r0, #4
	str	r2, [r4, #164]
	bl	dprint_vfmw
	ldr	r2, [r8, #1500]
	ldr	r1, .L148+124
	mov	r0, #4
	uxth	r2, r2
	str	r2, [r4, #168]
	bl	dprint_vfmw
	ldr	r3, [fp, #20]
	ldr	r1, .L148+128
	mov	r0, #4
	str	r3, [r4, #172]
	mov	r2, r3
	bl	dprint_vfmw
	ldr	r3, [fp, #24]
	ldr	r1, .L148+132
	mov	r0, #4
	str	r3, [r4, #176]
	mov	r2, r3
	bl	dprint_vfmw
	ldr	r2, [r6, #1488]
	ldr	r1, .L148+136
	mov	r0, #4
	add	r2, r2, r2, lsr #31
	ubfx	r2, r2, #1, #20
	str	r2, [r4, #180]
	bl	dprint_vfmw
	ldr	r2, [r6, #1492]
	ldr	r1, .L148+140
	mov	r0, #4
	str	r2, [r4, #184]
	bl	dprint_vfmw
	ldr	r2, [r6, #1496]
	ldr	r1, .L148+144
	mov	r0, #4
	str	r2, [r4, #188]
	bl	dprint_vfmw
	ldr	r2, [r6, #1380]
	ldr	r1, .L148+148
	mov	r0, #4
	ubfx	r2, r2, #0, #17
	str	r2, [r4, #192]
	bl	dprint_vfmw
	ldr	r2, [r6, #1388]
	ldr	r1, .L148+152
	mov	r0, #4
	ubfx	r2, r2, #0, #17
	str	r2, [r4, #196]
	bl	dprint_vfmw
	ldr	r3, [fp, #8]
	ldr	r1, .L148+156
	mov	r0, #4
	mov	r2, r3
	str	r3, [r4, #252]
	bl	dprint_vfmw
	mov	r0, r5
	mov	r2, r4
	mov	r1, r8
	bl	HEVCHAL_SetSliceMsgWPInfo
	mov	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L143:
	mov	r2, lr
	b	.L138
.L144:
	mov	r2, lr
	b	.L140
.L147:
	ldr	r3, .L148+160
	ldr	r2, .L148+164
	ldr	r1, .L148+168
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L149:
	.align	2
.L148:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC31
	.word	.LC13
	.word	.LANCHOR1
	.word	.LC14
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LC35
	.word	.LC36
	.word	.LC37
	.word	.LC38
	.word	.LC39
	.word	.LC40
	.word	.LC16
	.word	.LC41
	.word	.LC42
	.word	.LC43
	.word	.LC44
	.word	.LC45
	.word	.LC46
	.word	.LC47
	.word	.LC48
	.word	.LC49
	.word	.LC50
	.word	.LC51
	.word	.LC52
	.word	.LC53
	.word	.LC54
	.word	.LC55
	.word	.LC56
	.word	.LC57
	.word	.LC17
	.word	.LC58
	.word	.LC59
	.word	.LC60
	.word	.LC61
	.word	.LC62
	.word	.LC63
	.word	.LC27
	.word	.LC30
	.word	.LANCHOR1+2056
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R6C1_SetSliceMsg, .-HEVCHAL_V5R6C1_SetSliceMsg
	.align	2
	.global	HEVCHAL_CheckParaValid
	.type	HEVCHAL_CheckParaValid, %function
HEVCHAL_CheckParaValid:
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
	cmp	r1, #0
	bgt	.L155
	cmp	r0, #0
	beq	.L156
	ldr	r3, [r0, #2484]
	cmp	r3, #16
	movls	r0, #0
	bhi	.L157
.L152:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L155:
	mov	r3, r1
	ldr	r2, .L158
	mov	r1, #1
	mov	r0, #0
	str	r1, [sp]
	ldr	r1, .L158+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L152
.L157:
	ldr	r3, .L158+8
	mov	r0, #0
	ldr	r2, .L158
	ldr	r1, .L158+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L152
.L156:
	ldr	r3, .L158+16
	ldr	r2, .L158
	ldr	r1, .L158+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L152
.L159:
	.align	2
.L158:
	.word	.LANCHOR1+2096
	.word	.LC64
	.word	.LC66
	.word	.LC1
	.word	.LC65
	UNWIND(.fnend)
	.size	HEVCHAL_CheckParaValid, .-HEVCHAL_CheckParaValid
	.align	2
	.global	HEVCHAL_GetVdmRegVirAddr
	.type	HEVCHAL_GetVdmRegVirAddr, %function
HEVCHAL_GetVdmRegVirAddr:
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
	mov	r4, r0
	bgt	.L165
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L163
.L164:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L163:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4]
	bne	.L164
	ldr	r2, .L166
	ldr	r1, .L166+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L165:
	ldr	r1, .L166+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L167:
	.align	2
.L166:
	.word	.LANCHOR1+2120
	.word	.LC68
	.word	.LC67
	UNWIND(.fnend)
	.size	HEVCHAL_GetVdmRegVirAddr, .-HEVCHAL_GetVdmRegVirAddr
	.align	2
	.global	HEVCHAL_CheckSlicePara
	.type	HEVCHAL_CheckSlicePara, %function
HEVCHAL_CheckSlicePara:
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
	cmp	r0, #0
	beq	.L172
	cmp	r1, #0
	ldr	r1, [r0, #92]
	movgt	r0, #1
	movle	r0, #0
	cmp	r1, r2
	movcs	r0, #0
	andcc	r0, r0, #1
	cmp	r0, #0
	ldmeqfd	sp, {fp, sp, pc}
	mov	r3, r2
	mov	r0, #1
	mov	r2, r1
	ldr	r1, .L173
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L172:
	mov	r3, r1
	ldr	r2, .L173+4
	ldr	r1, .L173+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L174:
	.align	2
.L173:
	.word	.LC70
	.word	.LANCHOR1+2148
	.word	.LC69
	UNWIND(.fnend)
	.size	HEVCHAL_CheckSlicePara, .-HEVCHAL_CheckSlicePara
	.align	2
	.global	HEVCHAL_FindNextSlicePara
	.type	HEVCHAL_FindNextSlicePara, %function
HEVCHAL_FindNextSlicePara:
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
	cmp	r2, r1
	ldr	lr, [r0, #92]
	str	r2, [r3]
	ldmgefd	sp, {fp, sp, pc}
	ldr	r0, [r0, #1504]
	cmp	r0, #0
	beq	.L179
	ldr	ip, [r0, #92]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
	add	r2, r2, #1
	b	.L178
.L180:
	ldr	r0, [r0, #1504]
	cmp	r0, #0
	beq	.L179
	ldr	ip, [r0, #92]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
.L178:
	cmp	r2, r1
	str	r2, [r3]
	add	r2, r2, #1
	bne	.L180
	ldmfd	sp, {fp, sp, pc}
.L179:
	mov	r0, #0
	ldmfd	sp, {fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCHAL_FindNextSlicePara, .-HEVCHAL_FindNextSlicePara
	.align	2
	.global	HEVCHAL_CheckSliceAddrValid
	.type	HEVCHAL_CheckSliceAddrValid, %function
HEVCHAL_CheckSliceAddrValid:
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
	cmp	r1, r2
	ldr	r3, [r0, #572]
	bgt	.L186
	cmp	r2, r3
	blt	.L186
	ldr	r2, [r0, #92]
	cmp	r2, r3
	movls	r0, #0
	bhi	.L190
.L188:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L186:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r1
	ldr	r1, .L191
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L188
.L190:
	ldr	r1, .L191+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L188
.L192:
	.align	2
.L191:
	.word	.LC71
	.word	.LC72
	UNWIND(.fnend)
	.size	HEVCHAL_CheckSliceAddrValid, .-HEVCHAL_CheckSliceAddrValid
	.align	2
	.global	HEVCHAL_V5R6C1_CfgVdmReg
	.type	HEVCHAL_V5R6C1_CfgVdmReg, %function
HEVCHAL_V5R6C1_CfgVdmReg:
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
	ldr	r6, .L207
	mov	lr, r2, asl #6
	mov	r5, r2
	sub	lr, lr, r2, asl #3
	ldr	ip, .L207+4
	ldrb	r2, [r6]	@ zero_extendqisi2
	mov	r4, r0
	str	r1, [fp, #-56]
	add	r0, ip, lr
	subs	r2, r2, #1
	mov	r6, r3
	ldr	r0, [r0, #8]
	movne	r2, #1
	cmp	r3, #0
	movne	r1, #0
	andeq	r1, r2, #1
	cmp	r1, #0
	bne	.L205
	ldr	r3, .L207+8
	mov	r8, #0
	str	r8, [fp, #-48]
	mov	r9, #3
	ldr	r10, [r3, r0, asl #2]
	mov	r0, #0
	bfi	r0, r8, #7, #1
	strb	r0, [fp, #-46]
	cmp	r10, #0
	mov	r0, #8
	ldrne	ip, [r10, #1168]
	moveq	ip, r10
	moveq	r3, r10
	uxtbne	r3, ip
	str	ip, [fp, #-60]
	andne	r10, r3, #1
	cmp	r2, #0
	strneb	r3, [r6, #1]
	add	r3, r4, #4096
	ldr	r2, [r4, #20]
	ldr	r3, [r3, #1084]
	ldr	r1, [r4, #24]
	cmp	r3, #1
	ldrb	lr, [r4, #7]	@ zero_extendqisi2
	moveq	r3, #13
	movne	r3, #1
	mla	r1, r2, r1, r1
	bfi	r3, lr, #6, #1
	and	r3, r3, #111
	bfi	r3, r8, #5, #1
	strb	r3, [fp, #-45]
	ldr	r7, [fp, #-48]
	add	r1, r1, r2
	mov	r3, r6
	mov	r2, r5
	bfi	r7, r1, #0, #20
	str	r7, [r4, #2504]
	str	r7, [fp, #-48]
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	ldr	r1, .L207+12
	mov	r0, r9
	bl	dprint_vfmw
	str	r8, [fp, #-48]
	mov	r3, #0
	bfi	r3, r8, #5, #1
	strb	r3, [fp, #-45]
	mov	r2, #0
	ldrh	r1, [fp, #-46]
	mov	r0, #13
	ldr	lr, [r4, #1328]
	mov	r3, r6
	ldr	r7, [r4, #1340]
	bfi	r1, r9, #0, #12
	bfi	r2, lr, #4, #1
	ldrb	lr, [r4]	@ zero_extendqisi2
	strh	r1, [fp, #-46]	@ movhi
	bfi	r2, r7, #6, #1
	mov	r1, r1, lsr #8
	strb	r0, [fp, #-48]
	bfi	r1, lr, #6, #1
	mvn	r0, r2, asl #25
	and	r1, r1, #127
	mvn	r0, r0, lsr #25
	bfi	r1, r10, #4, #1
	strb	r0, [fp, #-47]
	strb	r1, [fp, #-45]
	mov	r2, r5
	ldr	r10, [fp, #-48]
	mov	r0, #12
	strb	r8, [r4, #5]
	movw	r7, #3075
	movt	r7, 48
	mov	r1, r10
	str	r10, [r4, #2508]
	bl	MFDE_ConfigReg
	mov	r2, r10
	ldr	r1, .L207+16
	mov	r0, r9
	bl	dprint_vfmw
	ldr	r10, [fp, #-56]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #16
	ldr	r8, [r10, #56]
	bic	r8, r8, #15
	str	r8, [r4, #2512]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L207+20
	mov	r0, r9
	bl	dprint_vfmw
	ldr	r1, [r10, #40]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #20
	str	r1, [r4, #2516]
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1332]
	mov	r3, r6
	mov	r2, r5
	bic	r1, r1, #15
	mov	r0, #24
	str	r1, [r4, #2520]
	bl	MFDE_ConfigReg
	mov	r1, r7
	mov	r3, r6
	mov	r2, r5
	mov	r0, #60
	str	r7, [r4, #2528]
	str	r7, [r4, #2532]
	str	r7, [r4, #2536]
	str	r7, [r4, #2540]
	str	r7, [r4, #2544]
	str	r7, [r4, #2548]
	str	r7, [r4, #2552]
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #64
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #68
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #72
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #76
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #80
	bl	MFDE_ConfigReg
	mov	r3, r6
	mov	r2, r5
	mov	r1, r7
	mov	r0, #84
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1288]
	mov	r3, r6
	mov	r2, r5
	add	r1, r1, #336
	mov	r0, #96
	ldr	r1, [r4, r1, asl #2]
	bic	r1, r1, #255
	str	r1, [r4, #2556]
	str	r1, [fp, #-48]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-60]
	cmp	ip, #1
	beq	.L206
.L198:
	ldr	r8, [r4, #1296]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #100
	mov	r7, #0
	str	r8, [r4, #2560]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L207+24
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r8, [r4, #1304]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #104
	str	r8, [r4, #2564]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L207+28
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r4, #1312]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #108
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1316]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #116
	str	r1, [r4, #2580]
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1320]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #120
	str	r1, [r4, #2584]
	bl	MFDE_ConfigReg
	ldr	r1, [r4, #1324]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #124
	str	r1, [r4, #2588]
	bl	MFDE_ConfigReg
	str	r7, [r4, #2604]
	mov	r1, r7
	mov	r3, r6
	mov	r2, r5
	mov	r0, #128
	str	r7, [fp, #-48]
	bl	MFDE_ConfigReg
	strh	r7, [fp, #-48]	@ movhi
	mov	r3, r6
	ldr	r1, [fp, #-48]
	mov	r2, r5
	mov	r0, #132
	str	r1, [r4, #2608]
	bl	MFDE_ConfigReg
	ldr	r3, [r4, #196]
	mov	r2, r5
	mov	r0, #4
	cmp	r3, #4096
	mov	r3, r6
	movhi	r1, r7
	movls	r1, #1
	mov	r4, r1
	bl	SCD_ConfigReg
	mov	r2, r4
	ldr	r1, .L207+32
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r6
	mov	r2, r5
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L207+36
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, #32
	mov	r3, r6
	mov	r2, r5
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, #0
.L195:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L206:
	mov	r3, r6
	mov	r2, r5
	mov	r1, #60
	mov	r0, #92
	bl	MFDE_ConfigReg
	mov	r2, #60
	ldr	r1, .L207+40
	mov	r0, r9
	bl	dprint_vfmw
	ldr	r1, [r4, #1288]
	mov	r2, r5
	mov	r3, r6
	mov	r0, #112
	add	r1, r4, r1, lsl #2
	ldr	r7, [r1, #1612]
	mov	r1, r7
	bl	MFDE_ConfigReg
	mov	r2, r7
	mov	r0, r9
	ldr	r1, .L207+44
	bl	dprint_vfmw
	b	.L198
.L205:
	ldr	r2, .L207+48
	mov	r0, #0
	ldr	r1, .L207+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L195
.L208:
	.align	2
.L207:
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC74
	.word	.LC75
	.word	.LC76
	.word	.LC79
	.word	.LC80
	.word	.LC81
	.word	.LC82
	.word	.LC77
	.word	.LC78
	.word	.LANCHOR1+2172
	.word	.LC73
	UNWIND(.fnend)
	.size	HEVCHAL_V5R6C1_CfgVdmReg, .-HEVCHAL_V5R6C1_CfgVdmReg
	.align	2
	.global	HEVCHAL_V5R6C1_SetSliceMsgSedOnly
	.type	HEVCHAL_V5R6C1_SetSliceMsgSedOnly, %function
HEVCHAL_V5R6C1_SetSliceMsgSedOnly:
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
	UNWIND(.pad #28)
	sub	sp, sp, #28
	mov	r6, r0
	ldr	r0, [r0, #2488]
	mov	r10, r1
	ldr	r2, [r6, #2492]
	cmp	r0, #0
	ble	.L210
	mov	r3, #0
	mov	r8, r3
	mov	r4, r3
.L212:
	ldrb	r1, [r2, #25]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r8, r3
	add	r3, r3, #1
	moveq	r4, r2
	cmp	r3, r0
	ldr	r2, [r2, #1504]
	bne	.L212
	cmp	r4, #0
	beq	.L210
	rsb	r3, r8, r3
	cmp	r3, #0
	addgt	r7, r10, #60
	movgt	r5, #0
	movgt	ip, r3
	bgt	.L220
	b	.L221
.L226:
	ldr	r2, [r4, #1504]
	mov	ip, r9
	ldrb	lr, [r6, #225]	@ zero_extendqisi2
	cmp	lr, #0
	ldr	lr, [r2, #92]
	sub	lr, lr, #1
	beq	.L224
	ldr	r2, [r2, #568]
	mov	ip, r9
.L218:
	str	r2, [sp, #16]
	mov	r2, r4
	str	r1, [sp, #12]
	mov	r1, r10
	str	r0, [sp, #8]
	mov	r0, r6
	str	ip, [sp, #4]
	mov	ip, #0
	str	lr, [sp, #20]
	add	r5, r5, #1
	str	ip, [sp]
	bl	HEVCHAL_V5R6C1_SetSliceMsg
	cmp	r0, #0
	bne	.L225
	ldr	ip, [r6, #2488]
	ldr	r4, [r4, #1504]
	rsb	ip, r8, ip
	cmp	ip, r5
	ble	.L221
.L220:
	sub	ip, ip, #1
	ldr	r3, [r7]
	cmp	r5, #205
	cmple	r5, ip
	ldr	r9, [r7, #4]!
	ldr	r0, [r4, #80]
	movlt	ip, #1
	movge	ip, #0
	ldr	r1, [r4, #92]
	blt	.L226
	ldr	lr, [r6, #24]
	ldr	r2, [r6, #20]
	mla	r2, lr, r2, r2
	add	lr, r2, lr
.L224:
	mov	r2, lr
	b	.L218
.L221:
	mov	r0, #0
.L214:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L225:
	ldr	r2, .L227
	mov	r0, #1
	ldr	r1, .L227+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L210:
	ldr	r2, .L227
	mov	r0, #1
	ldr	r1, .L227+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L214
.L228:
	.align	2
.L227:
	.word	.LANCHOR1+2200
	.word	.LC84
	.word	.LC83
	UNWIND(.fnend)
	.size	HEVCHAL_V5R6C1_SetSliceMsgSedOnly, .-HEVCHAL_V5R6C1_SetSliceMsgSedOnly
	.align	2
	.global	HEVCHAL_V5R6C1_StartDec
	.type	HEVCHAL_V5R6C1_StartDec, %function
HEVCHAL_V5R6C1_StartDec:
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
	UNWIND(.pad #76)
	sub	sp, sp, #76
	mov	r4, r2
	ldr	r2, .L294
	movw	ip, #1228
	str	r1, [fp, #-88]
	mov	r9, r0
	mla	r3, ip, r1, r2
	str	r3, [fp, #-80]
	bl	HEVCHAL_CheckParaValid
	cmn	r0, #1
	beq	.L284
	ldr	r6, [fp, #-88]
	ldr	r5, [fp, #-80]
	mov	r1, r6
	mov	r0, r5
	bl	HEVCHAL_GetVdmRegVirAddr
	cmn	r0, #1
	beq	.L284
	mov	r3, r4
	mov	r2, r6
	mov	r1, r5
	mov	r0, r9
	bl	HEVCHAL_V5R6C1_CfgVdmReg
	ldr	r3, [r5, #60]
	mov	r1, r5
	ldr	r2, [r5, #56]
	mov	r0, r9
	bl	HEVCHAL_V5R6C1_SetPicMsg
	ldr	r4, [r9, #2492]
	cmp	r4, #0
	beq	.L286
	add	r3, r9, #4096
	ldr	r3, [r3, #1084]
	cmp	r3, #1
	beq	.L287
	ldr	r5, [r4, #92]
	cmp	r5, #0
	bne	.L288
	mov	r10, r4
	str	r5, [fp, #-92]
.L235:
	ldr	r2, [r9, #24]
	ldr	r3, [r9, #20]
	ldr	r1, [r9, #2488]
	mla	r3, r2, r3, r3
	cmp	r1, #0
	add	r3, r3, r2
	str	r3, [fp, #-76]
	ble	.L238
	ldr	r0, [fp, #-88]
	movw	r2, #307
	ldr	r1, [fp, #-92]
	mul	r2, r2, r0
	add	r3, r1, #4
	add	r1, r1, #5
	str	r1, [fp, #-68]
	mov	r0, r2
	str	r2, [fp, #-72]
	mov	r2, #0
	add	r3, r0, r3
	mov	r5, r2
	str	r2, [fp, #-48]
	str	r3, [fp, #-84]
.L251:
	ldr	r3, [fp, #-68]
	mov	r0, r10
	ldr	r1, [fp, #-72]
	add	r7, r3, r5
	ldr	r3, [fp, #-84]
	ldr	lr, .L294
	add	ip, r1, r7
	add	r3, r3, r5
	add	ip, ip, #10
	add	r3, r3, #10
	mov	r1, r5
	ldr	ip, [lr, ip, asl #2]
	ldr	r3, [lr, r3, asl #2]
	str	ip, [fp, #-56]
	str	r3, [fp, #-52]
	bl	HEVCHAL_CheckSlicePara
	cmn	r0, #1
	beq	.L284
	ldr	r2, [r9, #2488]
	add	r5, r5, #1
	ldr	r6, [r10, #92]
	cmp	r2, r5
	ldr	ip, [r10, #80]
	ble	.L239
	ldr	r4, [r10, #1504]
	cmp	r4, #0
	bne	.L283
	b	.L240
.L290:
	add	r5, r5, #1
	cmp	r5, r2
	beq	.L289
	ldr	r4, [r4, #1504]
	cmp	r4, #0
	beq	.L240
.L283:
	ldr	r3, [r4, #92]
	cmp	r6, r3
	bcs	.L290
.L246:
	cmp	r7, #209
	cmpne	r2, r5
	beq	.L252
	ldrb	r2, [r9, #225]	@ zero_extendqisi2
	ldr	r3, [r4, #92]
	cmp	r2, #0
	ldr	r2, [fp, #-68]
	sub	r7, r3, #1
	ldr	r3, [fp, #-72]
	ldrne	r8, [r4, #568]
	add	r2, r3, r2
	ldr	r3, .L294
	add	r2, r2, r5
	moveq	r8, r7
	add	r2, r2, #10
	ldr	r3, [r3, r2, asl #2]
	str	r3, [fp, #-60]
.L248:
	str	r7, [r10, #572]
	mov	r1, r8
	ldr	r2, [fp, #-76]
	mov	r0, r10
	str	ip, [fp, #-64]
	bl	HEVCHAL_CheckSliceAddrValid
	cmn	r0, #1
	beq	.L284
	ldr	ip, [fp, #-64]
	mov	r2, r10
	str	r7, [sp, #20]
	mov	r0, r9
	ldr	r3, [fp, #-56]
	str	ip, [sp, #8]
	ldr	ip, [fp, #-60]
	str	r8, [sp, #16]
	str	r6, [sp, #12]
	str	ip, [sp, #4]
	ldr	ip, [fp, #-52]
	ldr	r1, [fp, #-80]
	str	ip, [sp]
	bl	HEVCHAL_V5R6C1_SetSliceMsg
	cmp	r0, #0
	bne	.L291
	ldr	r3, [r9, #2488]
	ldr	r2, [fp, #-48]
	cmp	r5, r3
	add	r2, r2, #1
	str	r2, [fp, #-48]
	ldr	r2, [r10, #572]
	bge	.L292
	mov	r10, r4
	b	.L251
.L288:
	ldrb	r3, [r9, #225]	@ zero_extendqisi2
	movw	r0, #1228
	ldr	r2, .L294
	mov	r6, #1
	cmp	r3, #0
	ldr	r3, [r4]
	ldr	r10, [r4, #4]
	sub	ip, r5, #1
	str	r6, [r4]
	str	r3, [fp, #-48]
	moveq	lr, ip
	ldr	r3, [fp, #-88]
	ldrne	lr, [r4, #568]
	ldr	r7, [r4, #16]
	mla	r0, r0, r3, r2
	ldr	r3, [r4, #8]
	mov	r2, r4
	ldr	r1, [fp, #-80]
	str	r3, [fp, #-52]
	ldr	r3, [r4, #12]
	str	r3, [fp, #-56]
	mov	r3, #0
	str	r3, [r4, #4]
	str	r3, [r4, #8]
	str	r3, [r4, #12]
	ldr	r8, [r9, #1332]
	str	r8, [r4, #16]
	ldr	r8, [r4, #20]
	str	r3, [r4, #20]
	str	r3, [sp, #12]
	str	r3, [sp, #8]
	ldr	r3, [r0, #60]
	str	ip, [sp, #20]
	ldr	ip, [r0, #64]
	ldr	r0, [r0, #56]
	str	lr, [sp, #16]
	str	ip, [sp, #4]
	str	r0, [sp]
	mov	r0, r9
	bl	HEVCHAL_V5R6C1_SetSliceMsg
	cmp	r0, #0
	bne	.L293
	ldr	r3, [fp, #-48]
	str	r5, [r4, #92]
	str	r7, [r4, #16]
	stmia	r4, {r3, r10}
	ldr	r3, [fp, #-52]
	str	r8, [r4, #20]
	str	r6, [fp, #-92]
	str	r3, [r4, #8]
	ldr	r3, [fp, #-56]
	str	r3, [r4, #12]
	ldr	r10, [r9, #2492]
	b	.L235
.L289:
	cmp	r4, #0
	beq	.L240
.L252:
	ldr	r3, [fp, #-76]
	mov	r7, #0
	str	r7, [r10, #1504]
	str	r7, [fp, #-60]
	mov	r8, r3
	ldr	r5, [r9, #2488]
	mov	r7, r3
	b	.L248
.L239:
	cmp	r10, #0
	beq	.L240
	mov	r4, r10
	b	.L246
.L238:
	ldr	r1, .L294+4
	mov	r0, #1
	bl	dprint_vfmw
.L284:
	mvn	r7, #0
.L279:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L240:
	ldr	r2, .L294+8
	mov	r0, #1
	ldr	r1, .L294+12
	mvn	r7, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L291:
	ldr	r2, .L294+8
	mov	r0, #1
	ldr	r1, .L294+16
	mvn	r7, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L292:
	cmp	r3, #0
	ldr	r1, [fp, #-48]
	mov	r7, r0
	movgt	r2, #1
	movle	r2, #0
	cmp	r1, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r2, #0
	beq	.L238
	ldr	r2, [fp, #-88]
	movw	r5, #307
	ldr	r1, [fp, #-92]
	mla	r5, r5, r2, r1
	ldr	r2, .L294
	add	r3, r5, r3
	add	r3, r3, #14
	ldr	r0, [r2, r3, asl #2]
	bl	HEVCHAL_V5R6C1_CutSliceChain
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L287:
	ldr	r1, [fp, #-80]
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	HEVCHAL_V5R6C1_SetSliceMsgSedOnly
.L293:
	mov	r0, r6
	ldr	r2, .L294+8
	ldr	r1, .L294+20
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L279
.L286:
	mov	r0, r4
	ldr	r2, .L294+8
	ldr	r1, .L294+24
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L279
.L295:
	.align	2
.L294:
	.word	g_HwMem
	.word	.LC88
	.word	.LANCHOR1+2236
	.word	.LC86
	.word	.LC87
	.word	.LC84
	.word	.LC85
	UNWIND(.fnend)
	.size	HEVCHAL_V5R6C1_StartDec, .-HEVCHAL_V5R6C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.14985, %object
	.size	__func__.14985, 18
__func__.14985:
	.ascii	"HEVCWriteCabacTab\000"
	.space	2
	.type	s_InitValue, %object
	.size	s_InitValue, 1920
s_InitValue:
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	200
	.word	139
	.word	141
	.word	157
	.word	154
	.word	-1
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	-1
	.word	-1
	.word	-1
	.word	184
	.word	63
	.word	94
	.word	138
	.word	182
	.word	154
	.word	111
	.word	141
	.word	154
	.word	154
	.word	139
	.word	139
	.word	138
	.word	153
	.word	136
	.word	167
	.word	152
	.word	152
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	110
	.word	110
	.word	124
	.word	125
	.word	140
	.word	153
	.word	125
	.word	127
	.word	140
	.word	109
	.word	111
	.word	143
	.word	127
	.word	111
	.word	79
	.word	108
	.word	123
	.word	63
	.word	91
	.word	171
	.word	134
	.word	141
	.word	140
	.word	92
	.word	137
	.word	138
	.word	140
	.word	152
	.word	138
	.word	139
	.word	153
	.word	74
	.word	149
	.word	92
	.word	139
	.word	107
	.word	122
	.word	152
	.word	140
	.word	179
	.word	166
	.word	182
	.word	140
	.word	227
	.word	122
	.word	197
	.word	111
	.word	111
	.word	125
	.word	110
	.word	110
	.word	94
	.word	124
	.word	108
	.word	124
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	107
	.word	125
	.word	141
	.word	179
	.word	153
	.word	125
	.word	140
	.word	139
	.word	182
	.word	182
	.word	152
	.word	136
	.word	152
	.word	136
	.word	153
	.word	136
	.word	139
	.word	111
	.word	136
	.word	139
	.word	111
	.word	-1
	.word	153
	.word	138
	.word	138
	.word	-1
	.word	-1
	.word	79
	.word	110
	.word	122
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	140
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	185
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	149
	.word	154
	.word	139
	.word	154
	.word	154
	.word	154
	.word	152
	.word	149
	.word	107
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	122
	.word	107
	.word	167
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	125
	.word	110
	.word	94
	.word	110
	.word	95
	.word	79
	.word	125
	.word	111
	.word	110
	.word	78
	.word	110
	.word	111
	.word	111
	.word	95
	.word	94
	.word	108
	.word	123
	.word	108
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	196
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	137
	.word	169
	.word	194
	.word	166
	.word	167
	.word	154
	.word	167
	.word	137
	.word	182
	.word	155
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	153
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	123
	.word	123
	.word	107
	.word	121
	.word	107
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	124
	.word	138
	.word	94
	.word	-1
	.word	-1
	.word	79
	.word	154
	.word	137
	.word	95
	.word	79
	.word	63
	.word	31
	.word	31
	.word	153
	.word	153
	.word	168
	.word	169
	.word	198
	.word	-1
	.word	-1
	.word	-1
	.word	153
	.word	160
	.word	107
	.word	139
	.word	126
	.word	154
	.word	197
	.word	185
	.word	201
	.word	134
	.word	154
	.word	139
	.word	154
	.word	154
	.word	183
	.word	152
	.word	149
	.word	92
	.word	167
	.word	154
	.word	153
	.word	111
	.word	154
	.word	154
	.word	139
	.word	139
	.word	107
	.word	167
	.word	91
	.word	107
	.word	107
	.word	167
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	125
	.word	110
	.word	124
	.word	110
	.word	95
	.word	94
	.word	125
	.word	111
	.word	111
	.word	79
	.word	125
	.word	126
	.word	111
	.word	111
	.word	79
	.word	108
	.word	123
	.word	93
	.word	121
	.word	140
	.word	61
	.word	154
	.word	154
	.word	196
	.word	167
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	182
	.word	134
	.word	149
	.word	136
	.word	153
	.word	121
	.word	136
	.word	122
	.word	169
	.word	208
	.word	166
	.word	167
	.word	154
	.word	152
	.word	167
	.word	182
	.word	170
	.word	154
	.word	139
	.word	153
	.word	139
	.word	123
	.word	123
	.word	63
	.word	124
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	166
	.word	183
	.word	140
	.word	136
	.word	153
	.word	154
	.word	170
	.word	153
	.word	138
	.word	138
	.word	122
	.word	121
	.word	122
	.word	121
	.word	167
	.word	151
	.word	183
	.word	140
	.word	151
	.word	183
	.word	140
	.word	-1
	.word	224
	.word	167
	.word	122
	.word	-1
	.word	-1
	.type	__func__.15006, %object
	.size	__func__.15006, 29
__func__.15006:
	.ascii	"HEVCHAL_V5R6C1_CutSliceChain\000"
	.space	3
	.type	__func__.15025, %object
	.size	__func__.15025, 19
__func__.15025:
	.ascii	"HEVC_WriteTileInfo\000"
	.space	1
	.type	__func__.15051, %object
	.size	__func__.15051, 25
__func__.15051:
	.ascii	"HEVCHAL_V5R6C1_SetPicMsg\000"
	.space	3
	.type	__func__.15071, %object
	.size	__func__.15071, 34
__func__.15071:
	.ascii	"HEVCHAL_SetSliceMsgStreamAddrInfo\000"
	.space	2
	.type	__func__.15127, %object
	.size	__func__.15127, 27
__func__.15127:
	.ascii	"HEVCHAL_V5R6C1_SetSliceMsg\000"
	.space	1
	.type	s_SliceTypeForPMV, %object
	.size	s_SliceTypeForPMV, 12
s_SliceTypeForPMV:
	.word	2
	.word	1
	.word	0
	.type	__func__.15138, %object
	.size	__func__.15138, 23
__func__.15138:
	.ascii	"HEVCHAL_CheckParaValid\000"
	.space	1
	.type	__func__.15144, %object
	.size	__func__.15144, 25
__func__.15144:
	.ascii	"HEVCHAL_GetVdmRegVirAddr\000"
	.space	3
	.type	__func__.15150, %object
	.size	__func__.15150, 23
__func__.15150:
	.ascii	"HEVCHAL_CheckSlicePara\000"
	.space	1
	.type	__func__.15177, %object
	.size	__func__.15177, 25
__func__.15177:
	.ascii	"HEVCHAL_V5R6C1_CfgVdmReg\000"
	.space	3
	.type	__func__.15197, %object
	.size	__func__.15197, 34
__func__.15197:
	.ascii	"HEVCHAL_V5R6C1_SetSliceMsgSedOnly\000"
	.space	2
	.type	__func__.15227, %object
	.size	__func__.15227, 24
__func__.15227:
	.ascii	"HEVCHAL_V5R6C1_StartDec\000"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	ASCII(.ascii	"can not map mn virtual address!\012\000" )
	.space	3
.LC1:
	ASCII(.ascii	"%s: %s\012\000" )
.LC2:
	ASCII(.ascii	"HEVCWriteCabacTab return error.\012\000" )
	.space	3
.LC3:
	ASCII(.ascii	"can not map slice msg virtual address!\012\000" )
.LC4:
	ASCII(.ascii	"can not map slice segment info virtual address!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC5:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC6:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC7:
	ASCII(.ascii	"D0 = 0x%x\012\000" )
	.space	1
.LC8:
	ASCII(.ascii	"D1 = 0x%x\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"D2 = 0x%x\012\000" )
	.space	1
.LC10:
	ASCII(.ascii	"D3 = 0x%x\012\000" )
	.space	1
.LC11:
	ASCII(.ascii	"D4 = 0x%x\012\000" )
	.space	1
.LC12:
	ASCII(.ascii	"D5 = 0x%x\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"D6 = 0x%x\012\000" )
	.space	1
.LC14:
	ASCII(.ascii	"D7 = 0x%x\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"D%d = 0x%x\012\000" )
.LC16:
	ASCII(.ascii	"D25 = 0x%x\012\000" )
.LC17:
	ASCII(.ascii	"D43 = 0x%x\012\000" )
.LC18:
	ASCII(.ascii	"D54 = 0x%x\012\000" )
.LC19:
	ASCII(.ascii	"HEVC_WriteTileInfo return error.\012\000" )
	.space	2
.LC20:
	ASCII(.ascii	"D55 = 0x%x\012\000" )
.LC21:
	ASCII(.ascii	"D56 = 0x%x\012\000" )
.LC22:
	ASCII(.ascii	"D57 = 0x%x\012\000" )
.LC23:
	ASCII(.ascii	"D58 = 0x%x\012\000" )
.LC24:
	ASCII(.ascii	"D59 = 0x%x\012\000" )
.LC25:
	ASCII(.ascii	"D60 = 0x%x\012\000" )
.LC26:
	ASCII(.ascii	"D61 = 0x%x\012\000" )
.LC27:
	ASCII(.ascii	"D63 = 0x%x\012\000" )
.LC28:
	ASCII(.ascii	"%s FATAL: i=0, valid_bitlen=0\012\000" )
	.space	1
.LC29:
	ASCII(.ascii	"slicemsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"HEVCHAL_SetSliceMsg can not map slice msg virtual a" )
	ASCII(.ascii	"ddress!\012\000" )
.LC31:
	ASCII(.ascii	"slice msg info:\012\000" )
	.space	3
.LC32:
	ASCII(.ascii	"D8 = 0x%x\012\000" )
	.space	1
.LC33:
	ASCII(.ascii	"D9 = 0x%x\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"D10 = 0x%x\012\000" )
.LC35:
	ASCII(.ascii	"D11 = 0x%x\012\000" )
.LC36:
	ASCII(.ascii	"D12 = 0x%x\012\000" )
.LC37:
	ASCII(.ascii	"D13 = 0x%x\012\000" )
.LC38:
	ASCII(.ascii	"D14 = 0x%x\012\000" )
.LC39:
	ASCII(.ascii	"D23 = 0x%x\012\000" )
.LC40:
	ASCII(.ascii	"D24 = 0x%x\012\000" )
.LC41:
	ASCII(.ascii	"D26 = 0x%x\012\000" )
.LC42:
	ASCII(.ascii	"D27 = 0x%x\012\000" )
.LC43:
	ASCII(.ascii	"D28 = 0x%x\012\000" )
.LC44:
	ASCII(.ascii	"D29 = 0x%x\012\000" )
.LC45:
	ASCII(.ascii	"D30 = 0x%x\012\000" )
.LC46:
	ASCII(.ascii	"D31 = 0x%x\012\000" )
.LC47:
	ASCII(.ascii	"D32 = 0x%x\012\000" )
.LC48:
	ASCII(.ascii	"D33 = 0x%x\012\000" )
.LC49:
	ASCII(.ascii	"D34 = 0x%x\012\000" )
.LC50:
	ASCII(.ascii	"D35 = 0x%x\012\000" )
.LC51:
	ASCII(.ascii	"D36 = 0x%x\012\000" )
.LC52:
	ASCII(.ascii	"D37 = 0x%x\012\000" )
.LC53:
	ASCII(.ascii	"D38 = 0x%x\012\000" )
.LC54:
	ASCII(.ascii	"D39 = 0x%x\012\000" )
.LC55:
	ASCII(.ascii	"D40 = 0x%x\012\000" )
.LC56:
	ASCII(.ascii	"D41 = 0x%x\012\000" )
.LC57:
	ASCII(.ascii	"D42 = 0x%x\012\000" )
.LC58:
	ASCII(.ascii	"D44 = 0x%x\012\000" )
.LC59:
	ASCII(.ascii	"D45 = 0x%x\012\000" )
.LC60:
	ASCII(.ascii	"D46 = 0x%x\012\000" )
.LC61:
	ASCII(.ascii	"D47 = 0x%x\012\000" )
.LC62:
	ASCII(.ascii	"D48 = 0x%x\012\000" )
.LC63:
	ASCII(.ascii	"D49 = 0x%x\012\000" )
.LC64:
	ASCII(.ascii	"%s VdhId %d >= %d\012\000" )
	.space	1
.LC65:
	ASCII(.ascii	"pParam is null\012\000" )
.LC66:
	ASCII(.ascii	"FATAL: ApcSize > 16\012\000" )
	.space	3
.LC67:
	ASCII(.ascii	"VdhId is wrong! HEVC4HAL_V200R003_StartDec\012\000" )
.LC68:
	ASCII(.ascii	"%s vdm register virtual address not mapped, reset f" )
	ASCII(.ascii	"ailed!\012\000" )
	.space	1
.LC69:
	ASCII(.ascii	"%s: i = %d, pSlicePara = NULL!\012\000" )
.LC70:
	ASCII(.ascii	"SliceSegmentTileAddress %d < prevEndCtbInSliceTile " )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC71:
	ASCII(.ascii	"end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%" )
	ASCII(.ascii	"d) > pic_max_ctb(%d)\012\000" )
	.space	3
.LC72:
	ASCII(.ascii	"SliceSegmentTileAddress %d > end_ctb_in_slice_tile " )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC73:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC74:
	ASCII(.ascii	"HEVC_BASIC_CFG0 = 0x%x\012\000" )
.LC75:
	ASCII(.ascii	"HEVC_BASIC_CFG1 = 0x%x\012\000" )
.LC76:
	ASCII(.ascii	"AVM_ADDR = 0x%x\012\000" )
	.space	3
.LC77:
	ASCII(.ascii	"VREG_V200R003_PART_DEC_OVER_INT_LEVEL=0x%x\012\000" )
.LC78:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC79:
	ASCII(.ascii	"HEVC_VFMW_YSTADDR_1D = 0x%x\012\000" )
	.space	3
.LC80:
	ASCII(.ascii	"HEVC_VFMW_UVOFFSET_1D = 0x%x\012\000" )
	.space	2
.LC81:
	ASCII(.ascii	"SCD REG_EMAR_ID = 0x%x\012\000" )
.LC82:
	ASCII(.ascii	"VREG_FF_APT_EN = 0x%x\012\000" )
	.space	1
.LC83:
	ASCII(.ascii	"%s : pTargetSlicePara == NULL\012\000" )
	.space	1
.LC84:
	ASCII(.ascii	"%s 0: set slice msg failed!\012\000" )
	.space	3
.LC85:
	ASCII(.ascii	"%s pFirstSlice = NULL!\012\000" )
.LC86:
	ASCII(.ascii	"%s pTargetSlicePara is NULL!\012\000" )
	.space	2
.LC87:
	ASCII(.ascii	"%s 1: set slice msg failed!\012\000" )
	.space	3
.LC88:
	ASCII(.ascii	"No slice to dec, add up msg report.\012\000" )
	.bss
	.align	2
.LANCHOR0 = . + 0
	.type	s_CabacMN, %object
	.size	s_CabacMN, 928
s_CabacMN:
	.space	928
	.ident	"GCC: (gcc-linaro-4.9-2014.09 + glibc-2.24 (Build by czyong) Wed Dec 21 10:39:16 CST 2016) 4.9.2 20140904 (prerelease)"
	.section	.note.GNU-stack,"",%progbits
