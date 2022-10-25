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
	.global	HEVCHAL_V5R2C1_InitHal
	.type	HEVCHAL_V5R2C1_InitHal, %function
HEVCHAL_V5R2C1_InitHal:
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
	.size	HEVCHAL_V5R2C1_InitHal, .-HEVCHAL_V5R2C1_InitHal
	.align	2
	.global	HEVCGet_V5R2C1_VirAddr
	.type	HEVCGet_V5R2C1_VirAddr, %function
HEVCGet_V5R2C1_VirAddr:
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
	.size	HEVCGet_V5R2C1_VirAddr, .-HEVCGet_V5R2C1_VirAddr
	.align	2
	.global	HEVCGet_V5R2C1_PhyAddr
	.type	HEVCGet_V5R2C1_PhyAddr, %function
HEVCGet_V5R2C1_PhyAddr:
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
	.size	HEVCGet_V5R2C1_PhyAddr, .-HEVCGet_V5R2C1_PhyAddr
	.align	2
	.global	HEVCHAL_V5R2C1_CutSliceChain
	.type	HEVCHAL_V5R2C1_CutSliceChain, %function
HEVCHAL_V5R2C1_CutSliceChain:
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
	.size	HEVCHAL_V5R2C1_CutSliceChain, .-HEVCHAL_V5R2C1_CutSliceChain
	.align	2
	.global	HEVC_WriteQmatrix
	.type	HEVC_WriteQmatrix, %function
HEVC_WriteQmatrix:
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
	subs	r9, r1, #0
	mov	r8, r0
	mov	r10, r2
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	sub	r6, r3, #4
	sub	r7, r0, #4
	mov	r4, #0
.L38:
	ldr	r3, [r7, #4]!
	mov	r2, r4
	ldr	r1, .L41
	mov	r0, #4
	add	r4, r4, #1
	mov	r5, r7
	str	r3, [r6, #4]!
	ldr	r3, [r5], r10
	bl	dprint_vfmw
	ldr	r3, [r6]
	rsb	r2, r8, r5
	ldr	r1, .L41+4
	mov	r0, #4
	bl	dprint_vfmw
	cmp	r4, r9
	bne	.L38
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L42:
	.align	2
.L41:
	.word	.LC4
	.word	.LC5
	UNWIND(.fnend)
	.size	HEVC_WriteQmatrix, .-HEVC_WriteQmatrix
	.align	2
	.global	HEVC_WriteTileInfo
	.type	HEVC_WriteTileInfo, %function
HEVC_WriteTileInfo:
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
	str	r0, [fp, #-52]
	mov	r4, r0
	ldr	r0, [r1, #1112]
	bl	MEM_Phy2Vir
	subs	r3, r0, #0
	str	r3, [fp, #-48]
	beq	.L44
	add	r7, r3, #1024
	add	r8, r3, #4
	add	r7, r7, #4
	mov	r5, #0
	mov	r9, r4
	str	r4, [fp, #-56]
.L45:
	mov	r10, r9
	mov	r6, r8
	mov	r4, #0
	b	.L49
.L65:
	ldrb	r3, [r10, #1742]	@ zero_extendqisi2
	ldrb	ip, [r10, #1743]	@ zero_extendqisi2
	ldrb	r1, [r10, #1740]	@ zero_extendqisi2
	ldrb	r2, [r10, #1741]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	orr	r3, r3, ip, asl #24
	orr	r3, r3, r1
	ldr	r1, .L66
	orr	r2, r3, r2, asl #8
	str	r2, [r6, #-4]
	bl	dprint_vfmw
.L48:
	add	r4, r4, #4
	add	r6, r6, #4
	cmp	r4, #512
	add	r10, r10, #4
	beq	.L64
.L49:
	cmp	r4, #252
	mov	r2, #0
	ldr	r1, .L66
	mov	r0, #4
	ble	.L65
	str	r5, [r6, #-4]
	bl	dprint_vfmw
	b	.L48
.L64:
	add	r8, r8, #512
	add	r9, r9, #256
	cmp	r8, r7
	bne	.L45
	ldr	r6, [fp, #-56]
	mov	r3, #0
	ldr	r2, [fp, #-52]
	mov	ip, r3
.L50:
	cmp	r3, #9
	add	r3, r3, #1
	strgt	ip, [r7, #-4]
	add	r2, r2, #8
	ldrle	r0, [r2, #2248]
	add	r7, r7, #4
	ldrle	r1, [r2, #2244]
	orrle	r1, r1, r0, asl #16
	strle	r1, [r7, #-8]
	cmp	r3, #20
	bne	.L50
	ldr	r3, [fp, #-48]
	add	r2, r3, #1104
	mov	r3, #0
	add	r2, r2, #4
	mov	ip, r3
.L56:
	cmp	r3, #10
	add	r3, r3, #1
	strgt	ip, [r2, #-4]
	add	r6, r6, #8
	ldrle	r0, [r6, #2328]
	add	r2, r2, #4
	ldrle	r1, [r6, #2324]
	orrle	r1, r1, r0, asl #16
	strle	r1, [r2, #-8]
	cmp	r3, #22
	bne	.L56
	mov	r0, #0
.L61:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L44:
	ldr	r3, .L66+4
	ldr	r2, .L66+8
	ldr	r1, .L66+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L61
.L67:
	.align	2
.L66:
	.word	.LC7
	.word	.LC6
	.word	.LANCHOR1+1972
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVC_WriteTileInfo, .-HEVC_WriteTileInfo
	.align	2
	.global	HEVCHAL_V5R2C1_SetPicMsg
	.type	HEVCHAL_V5R2C1_SetPicMsg, %function
HEVCHAL_V5R2C1_SetPicMsg:
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
	mov	r4, r0
	mov	r0, r2
	mov	r6, r2
	mov	r8, r1
	mov	r7, r3
	bl	MEM_Phy2Vir
	subs	r5, r0, #0
	beq	.L83
	ldr	r3, .L85
	mov	r2, #1280
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	ldr	r1, .L85+4
	mov	r0, #4
	bl	dprint_vfmw
	ldrb	r1, [r4, #6]	@ zero_extendqisi2
	ldrb	ip, [r4, #7]	@ zero_extendqisi2
	mov	r2, r6
	ldr	r3, [r4, #20]
	mov	r0, #4
	ldrb	r10, [r4, #8]	@ zero_extendqisi2
	mov	r1, r1, asl #25
	ldr	r9, [r4, #12]
	orr	r1, r1, ip, asl #24
	ldrb	lr, [r4, #9]	@ zero_extendqisi2
	mov	r3, r3, asl #9
	ldrb	ip, [r4, #10]	@ zero_extendqisi2
	orr	r1, r1, r10, asl #23
	orr	r3, r3, r9, asl #19
	ldr	r10, [r4, #24]
	ldrb	r9, [r4, #16]	@ zero_extendqisi2
	orr	r1, r1, lr, asl #22
	orr	lr, r3, r10
	orr	ip, r1, ip, asl #21
	ldr	r1, .L85+8
	orr	r3, lr, r9, asl #18
	orr	r3, r3, ip
	str	r3, [r5]
	ldr	r3, [r5]
	bl	dprint_vfmw
	ldr	r3, [r4, #28]
	str	r3, [r5, #4]
	ldr	r2, [r4, #44]
	ldr	r1, [r4, #36]
	ldr	ip, [r4, #76]
	ldr	r3, [r4, #48]
	mov	r2, r2, asl #24
	ldr	r0, [r4, #52]
	orr	r2, r2, r1, asl #29
	ldr	lr, [r4, #56]
	orr	r2, r2, ip
	ldr	r1, [r4, #60]
	orr	r3, r2, r3, asl #21
	ldr	ip, [r4, #64]
	orr	r3, r3, r0, asl #18
	ldr	r2, [r4, #68]
	orr	r0, r3, lr, asl #15
	orr	r1, r0, r1, asl #12
	ldr	r0, [r4, #72]
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	orr	r1, r1, ip, asl #9
	orr	r2, r1, r2, asl #6
	ldrb	r1, [r4, #41]	@ zero_extendqisi2
	orr	r2, r2, r0, asl #3
	orr	r3, r2, r3, asl #28
	orr	r3, r3, r1, asl #27
	str	r3, [r5, #8]
	ldr	r0, [r4, #84]
	ldr	r2, [r4, #80]
	ldr	r1, [r4, #100]
	ldr	ip, [r4, #88]
	mov	r0, r0, asl #16
	ldr	r3, [r4, #92]
	orr	r2, r0, r2, asl #22
	orr	r2, r2, r1
	ldr	r1, [r4, #96]
	orr	r2, r2, ip, asl #12
	orr	r3, r2, r3, asl #8
	orr	r3, r3, r1, asl #4
	str	r3, [r5, #12]
	ldr	r3, [r8, #1092]
	str	r3, [r5, #16]
	ldr	r3, [r8, #1096]
	str	r3, [r5, #20]
	ldr	r3, [r4, #1292]
	add	r3, r4, r3, lsl #2
	ldr	r3, [r3, #1476]
	str	r3, [r5, #24]
	ldr	r3, [r8, #1104]
	str	r3, [r5, #28]
	ldr	ip, [r4, #2484]
	cmp	ip, #0
	beq	.L71
	add	r0, r4, #2416
	add	r1, r5, #32
	mov	r2, #0
.L72:
	ldr	r3, [r0, #4]!
	add	r2, r2, #1
	add	r3, r3, #336
	ldr	r3, [r4, r3, asl #2]
	str	r3, [r1], #4
	ldr	ip, [r4, #2484]
	cmp	ip, r2
	bhi	.L72
	cmp	ip, #15
	bhi	.L75
.L71:
	add	r3, ip, #8
	add	r3, r5, r3, lsl #2
.L74:
	ldr	lr, [r4, #2420]
	add	ip, ip, #1
	cmp	ip, #15
	add	lr, lr, #336
	ldr	r2, [r4, lr, asl #2]
	str	r2, [r3], #4
	bls	.L74
.L75:
	ldr	r2, [r8, #1108]
	add	ip, r4, #124
	add	r3, r5, #104
	add	r1, r4, #188
	str	r2, [r5, #100]
.L73:
	ldr	r2, [ip, #4]!
	cmp	ip, r1
	str	r2, [r3], #4
	bne	.L73
	ldr	r3, [r8, #1100]
	mov	r1, r8
	mov	r0, r4
	str	r3, [r5, #172]
	ldr	r2, [r4, #192]
	ldr	r3, [r4, #196]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #216]
	bl	HEVC_WriteTileInfo
	subs	r9, r0, #0
	bne	.L84
	ldr	r3, [r8, #1112]
	mov	r1, r5
	mov	r0, #64
	str	r3, [r5, #220]
	ldr	r3, [r8, #1124]
	str	r3, [r5, #224]
	ldr	r3, [r8, #1116]
	str	r3, [r5, #228]
	ldr	r3, [r8, #1128]
	str	r3, [r5, #232]
	ldr	r3, [r8, #1120]
	str	r3, [r5, #236]
	ldr	r3, [r4, #228]
	ldr	r2, [r4, #232]
	ldr	ip, [r4, #244]
	ldrb	lr, [r4, #220]	@ zero_extendqisi2
	mov	r3, r3, asl #16
	ldrb	r10, [r4, #221]	@ zero_extendqisi2
	orr	r2, r3, r2, asl #13
	and	ip, ip, #31
	ldrb	r3, [r4, #222]	@ zero_extendqisi2
	orr	r2, r2, ip
	ldrb	r8, [r4, #223]	@ zero_extendqisi2
	orr	r2, r2, lr, asl #24
	ldrb	ip, [r4, #224]	@ zero_extendqisi2
	orr	lr, r2, r10, asl #23
	ldrb	r2, [r4, #225]	@ zero_extendqisi2
	orr	r3, lr, r3, asl #22
	ldrb	r10, [r4, #236]	@ zero_extendqisi2
	orr	r3, r3, r8, asl #21
	ldr	lr, [r4, #240]
	orr	ip, r3, ip, asl #20
	ldrb	r3, [r4, #237]	@ zero_extendqisi2
	ldrb	r8, [r4, #238]	@ zero_extendqisi2
	orr	ip, ip, r2, asl #19
	orr	r2, ip, r10, asl #12
	and	lr, lr, #31
	orr	r2, r2, r3, asl #11
	orr	r3, r2, r8, asl #10
	orr	r3, r3, lr, asl #5
	str	r3, [r5, #240]
	ldr	r2, [r4, #248]
	ldr	r3, [r4, #252]
	orr	r3, r3, r2, asl #16
	str	r3, [r5, #244]
	str	r7, [r5, #252]
	bl	HEVC_GetVirAddr
	mov	r1, r6
	mov	r5, r0
	mov	r0, #64
	bl	HEVC_GetPhyAddr
	mov	r3, r5
	mov	r1, #256
	mov	r2, r0
	add	r0, r4, #260
	bl	HEVC_WriteQmatrix
.L70:
	mov	r0, r9
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L84:
	ldr	r1, .L85+12
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r9, #0
	b	.L70
.L83:
	ldr	r3, .L85+16
	mvn	r9, #0
	ldr	r2, .L85+20
	ldr	r1, .L85+24
	bl	dprint_vfmw
	b	.L70
.L86:
	.align	2
.L85:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC8
	.word	.LANCHOR1+1992
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_SetPicMsg, .-HEVCHAL_V5R2C1_SetPicMsg
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
.L93:
	cmp	r8, #0
	mov	r3, r6
	mov	r2, r5
	ldr	r1, .L96
	mov	r0, #4
	beq	.L95
	ldr	r9, [r7, #-16]
	cmp	r9, #0
	beq	.L91
.L89:
	ldr	r2, [fp, #-48]
	mov	r3, r6
	ldr	lr, [r7]
	mov	r0, #4
	ldr	r1, .L96
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
	ldr	r1, .L96
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
	ldr	r1, .L96
	mov	r0, #4
	str	ip, [r10]
	ldr	ip, [r4, #8]
	str	ip, [sp]
	bl	dprint_vfmw
.L92:
	add	r8, r8, #1
	add	r7, r7, #4
	cmp	r8, #2
	add	r4, r4, #12
	add	r5, r5, #3
	add	r6, r6, #12
	add	r10, r10, #12
	bne	.L93
	mov	r0, #0
.L90:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L91:
	str	r9, [r4]
	ldr	lr, [r10, #-8]
	str	lr, [sp]
	bl	dprint_vfmw
	str	r9, [r4, #4]
	ldr	lr, [r4, #4]
	add	r3, r6, #4
	add	r2, r5, #1
	ldr	r1, .L96
	mov	r0, #4
	str	lr, [sp]
	bl	dprint_vfmw
	str	r9, [r10]
	ldr	ip, [r4, #8]
	add	r3, r6, #8
	add	r2, r5, #2
	ldr	r1, .L96
	mov	r0, #4
	str	ip, [sp]
	bl	dprint_vfmw
	b	.L92
.L95:
	ldr	r3, [fp, #-52]
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L89
	mov	r0, r8
	ldr	r2, .L96+4
	ldr	r1, .L96+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L90
.L97:
	.align	2
.L96:
	.word	.LC13
	.word	.LANCHOR1+2020
	.word	.LC12
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
	beq	.L105
.L104:
	and	r3, ip, #7
	ldr	r5, [r4, #4]!
	cmp	r3, #7
	sub	r2, r2, #1
	mov	r3, r3, asl #2
	orr	lr, lr, r5, asl r3
	streq	lr, [r1, r6, asl #2]
	addeq	r6, r6, #1
	moveq	lr, #0
	beq	.L103
	cmp	r2, ip
	streq	lr, [r1, r6, asl #2]
.L103:
	ldr	r2, [r0, #68]
	add	ip, ip, #1
	cmp	r2, ip
	bhi	.L104
.L105:
	ldr	r2, [r0, #72]
	cmp	r2, #0
	beq	.L112
	mov	lr, #0
	add	r4, r0, #432
	mov	ip, lr
	mov	r6, #17
.L108:
	and	r3, ip, #7
	ldr	r5, [r4, #4]!
	cmp	r3, #7
	sub	r2, r2, #1
	mov	r3, r3, asl #2
	orr	lr, lr, r5, asl r3
	streq	lr, [r1, r6, asl #2]
	addeq	r6, r6, #1
	moveq	lr, #0
	beq	.L107
	cmp	r2, ip
	streq	lr, [r1, r6, asl #2]
.L107:
	ldr	r2, [r0, #72]
	add	ip, ip, #1
	cmp	r2, ip
	bhi	.L108
	ldmfd	sp, {r4, r5, r6, fp, sp, pc}
.L112:
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
	beq	.L114
	ldr	r3, [r4, #76]
	cmp	r3, #1
	beq	.L115
.L114:
	ldrb	r3, [r7, #40]	@ zero_extendqisi2
	cmp	r3, #1
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	ldr	r3, [r4, #76]
	cmp	r3, #0
	bne	.L135
	ldr	r3, [r4, #68]
	cmp	r3, #0
	beq	.L122
.L121:
	mov	r1, #0
	add	r7, r4, #712
	add	r6, r4, #584
	mov	r0, r1
	mov	r3, r4
.L119:
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
	bhi	.L119
	ldr	r3, [r4, #76]
	cmp	r3, #0
	ldmnefd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L122:
	ldr	r3, [r4, #72]
	cmp	r3, #0
	ldmeqfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	mov	r1, #0
	add	r7, r4, #776
	add	r6, r4, #648
	mov	ip, r1
	mov	r2, r4
.L120:
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
	bhi	.L120
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L115:
	ldr	r3, [r4, #68]
	cmp	r3, #0
	bne	.L121
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L135:
	ldmfd	sp, {r3, r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
	UNWIND(.fnend)
	.size	HEVCHAL_SetSliceMsgWPInfo, .-HEVCHAL_SetSliceMsgWPInfo
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.align	2
	.global	HEVCHAL_V5R2C1_SetSliceMsg
	.type	HEVCHAL_V5R2C1_SetSliceMsg, %function
HEVCHAL_V5R2C1_SetSliceMsg:
	UNWIND(.fnstart)
	@ args = 24, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	UNWIND(.movsp ip)
	mov	ip, sp
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, fp, ip, lr, pc}
	UNWIND(.pad #4)
	UNWIND(.save {r4, r5, r6, r7, r8, r9, fp, ip, lr})
	UNWIND(.setfp fp, ip, #-4)
	sub	fp, ip, #4
	mov	r5, r0
	mov	r0, r3
	mov	r8, r3
	mov	r4, r2
	ldr	r7, [fp, #12]
	bl	MEM_Phy2Vir
	subs	r6, r0, #0
	beq	.L148
	ldr	r3, .L149
	mov	r2, #1280
	mov	r1, #0
	ldr	r3, [r3, #48]
	blx	r3
	mov	r3, r8
	mov	r2, r6
	mov	r1, r4
	mov	r0, r5
	bl	HEVCHAL_SetSliceMsgStreamAddrInfo
	cmn	r0, #1
	ldmeqfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
	ldr	r1, [r4, #28]
	mov	r0, r7
	ldrb	ip, [r4, #32]	@ zero_extendqisi2
	ldrb	r2, [r4, #24]	@ zero_extendqisi2
	and	r1, r1, #127
	ldrb	r3, [r4, #25]	@ zero_extendqisi2
	ldr	lr, [r4, #36]
	mov	ip, ip, asl #18
	orr	r1, ip, r1, asl #19
	mov	r2, r2, asl #27
	orr	r1, r1, lr
	orr	r3, r2, r3, asl #26
	orr	r3, r1, r3
	str	r3, [r6, #24]
	ldr	r1, [r4, #44]
	ldr	r3, [r4, #56]
	ldr	lr, [r4, #76]
	ldr	r2, [r4, #60]
	mov	r1, r1, asl #24
	ldr	ip, .L149+4
	orr	r1, r1, r3, asl #20
	ldr	r3, [r4, #72]
	ldr	r9, [r4, #68]
	add	lr, ip, lr, lsl #2
	orr	r2, r1, r2, asl #16
	ldrb	r8, [r4, #64]	@ zero_extendqisi2
	orr	r2, r2, r3, asl #8
	ldr	ip, [lr, #2084]
	ldr	r1, [r4, #40]
	orr	r3, r2, r9, asl #2
	ldrb	lr, [r4, #65]	@ zero_extendqisi2
	orr	ip, r3, ip
	ldrb	r3, [r4, #52]	@ zero_extendqisi2
	orr	ip, ip, r8, asl #15
	mov	r2, r1, asl #28
	orr	r1, ip, lr, asl #14
	orr	r2, r2, r3, asl #27
	orr	r3, r1, r2
	str	r3, [r6, #28]
	str	r7, [r6, #32]
	ldr	r8, [r5, #24]
	add	r8, r8, #1
	mov	r1, r8
	bl	__aeabi_uidiv
	mov	r1, r8
	mov	r8, r0, asl #16
	mov	r0, r7
	bl	__aeabi_uidivmod
	ldr	r3, [fp, #16]
	orr	r1, r8, r1
	str	r1, [r6, #36]
	str	r3, [r6, #40]
	ldr	r2, [r4, #96]
	ldr	r3, [r4, #100]
	and	r2, r2, #31
	and	r3, r3, #31
	orr	r3, r3, r2, asl #8
	str	r3, [r6, #44]
	ldr	r0, [r4, #108]
	ldr	r2, [r4, #104]
	and	r0, r0, #15
	ldrb	r1, [r4, #115]	@ zero_extendqisi2
	and	r2, r2, #15
	ldrb	ip, [r4, #113]	@ zero_extendqisi2
	mov	r0, r0, asl #8
	ldrb	r3, [r4, #112]	@ zero_extendqisi2
	orr	r2, r0, r2, asl #16
	ldrb	r0, [r4, #114]	@ zero_extendqisi2
	orr	r2, r2, r1
	orr	r2, r2, ip, asl #3
	orr	r3, r2, r3, asl #2
	orr	r3, r3, r0, asl #1
	str	r3, [r6, #48]
	ldr	r0, [r4, #68]
	cmp	r0, #0
	beq	.L144
	mov	ip, #0
	add	r2, r4, #112
	mov	r3, ip
.L140:
	ldr	r1, [r2, #4]!
	orr	ip, ip, r1, asl r3
	add	r3, r3, #1
	cmp	r3, r0
	bne	.L140
.L139:
	str	ip, [r6, #52]
	ldr	r0, [r4, #72]
	cmp	r0, #0
	beq	.L145
	mov	ip, #0
	add	r2, r4, #176
	mov	r3, ip
.L142:
	ldr	r1, [r2, #4]!
	orr	ip, ip, r1, asl r3
	add	r3, r3, #1
	cmp	r3, r0
	bne	.L142
.L141:
	str	ip, [r6, #56]
	mov	r1, r6
	mov	r0, r4
	bl	HEVCHAL_SetSliceMsgAPCIndex
	ldr	r3, [r4, #564]
	mov	r0, r5
	mov	r1, r4
	mov	r2, r6
	str	r3, [r6, #92]
	ldr	r3, [r5, #84]
	mov	r3, r3, lsr #1
	mov	r3, r3, asl #8
	orr	r3, r3, #16384
	orr	r3, r3, #10
	str	r3, [r6, #96]
	ldr	r3, [fp, #20]
	str	r3, [r6, #172]
	ldr	r3, [fp, #24]
	str	r3, [r6, #176]
	ldr	r3, [fp, #8]
	str	r3, [r6, #252]
	bl	HEVCHAL_SetSliceMsgWPInfo
	mov	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L144:
	mov	ip, r0
	b	.L139
.L145:
	mov	ip, r0
	b	.L141
.L148:
	ldr	r3, .L149+8
	ldr	r2, .L149+12
	ldr	r1, .L149+16
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, fp, sp, pc}
.L150:
	.align	2
.L149:
	.word	vfmw_Osal_Func_Ptr_S
	.word	.LANCHOR1
	.word	.LC14
	.word	.LANCHOR1+2056
	.word	.LC1
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_SetSliceMsg, .-HEVCHAL_V5R2C1_SetSliceMsg
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
	bgt	.L156
	cmp	r0, #0
	beq	.L157
	ldr	r3, [r0, #2484]
	cmp	r3, #16
	movls	r0, #0
	bhi	.L158
.L153:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L156:
	mov	r3, r1
	ldr	r2, .L159
	mov	r1, #1
	mov	r0, #0
	str	r1, [sp]
	ldr	r1, .L159+4
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L153
.L158:
	ldr	r3, .L159+8
	mov	r0, #0
	ldr	r2, .L159
	ldr	r1, .L159+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L153
.L157:
	ldr	r3, .L159+16
	ldr	r2, .L159
	ldr	r1, .L159+12
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L153
.L160:
	.align	2
.L159:
	.word	.LANCHOR1+2096
	.word	.LC15
	.word	.LC17
	.word	.LC1
	.word	.LC16
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
	bgt	.L166
	ldr	r3, [r0]
	cmp	r3, #0
	beq	.L164
.L165:
	mov	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L164:
	mov	r0, #0
	movt	r0, 63683
	bl	MEM_Phy2Vir
	cmp	r0, #0
	str	r0, [r4]
	bne	.L165
	ldr	r2, .L167
	ldr	r1, .L167+4
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L166:
	ldr	r1, .L167+8
	mov	r0, #0
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L168:
	.align	2
.L167:
	.word	.LANCHOR1+2120
	.word	.LC19
	.word	.LC18
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
	beq	.L173
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
	ldr	r1, .L174
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L173:
	mov	r3, r1
	ldr	r2, .L174+4
	ldr	r1, .L174+8
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	ldmfd	sp, {fp, sp, pc}
.L175:
	.align	2
.L174:
	.word	.LC21
	.word	.LANCHOR1+2148
	.word	.LC20
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
	ldr	r0, [r0, #1356]
	cmp	r0, #0
	beq	.L180
	ldr	ip, [r0, #92]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
	add	r2, r2, #1
	b	.L179
.L181:
	ldr	r0, [r0, #1356]
	cmp	r0, #0
	beq	.L180
	ldr	ip, [r0, #92]
	cmp	lr, ip
	ldmccfd	sp, {fp, sp, pc}
.L179:
	cmp	r2, r1
	str	r2, [r3]
	add	r2, r2, #1
	bne	.L181
	ldmfd	sp, {fp, sp, pc}
.L180:
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
	bgt	.L187
	cmp	r2, r3
	blt	.L187
	ldr	r2, [r0, #92]
	cmp	r2, r3
	movls	r0, #0
	bhi	.L191
.L189:
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, pc}
.L187:
	str	r2, [sp]
	mov	r0, #1
	mov	r2, r1
	ldr	r1, .L192
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L189
.L191:
	ldr	r1, .L192+4
	mov	r0, #1
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L189
.L193:
	.align	2
.L192:
	.word	.LC22
	.word	.LC23
	UNWIND(.fnend)
	.size	HEVCHAL_CheckSliceAddrValid, .-HEVCHAL_CheckSliceAddrValid
	.align	2
	.global	HEVCHAL_V5R2C1_CfgVdmReg
	.type	HEVCHAL_V5R2C1_CfgVdmReg, %function
HEVCHAL_V5R2C1_CfgVdmReg:
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
	ldr	r6, .L210
	mov	lr, r2, asl #6
	mov	r5, r2
	sub	lr, lr, r2, asl #3
	ldr	ip, .L210+4
	ldrb	r2, [r6]	@ zero_extendqisi2
	mov	r9, r1
	add	ip, ip, lr
	mov	r4, r0
	subs	r2, r2, #1
	mov	r6, r3
	ldr	r0, [ip, #8]
	movne	r2, #1
	cmp	r3, #0
	movne	r1, #0
	andeq	r1, r2, #1
	cmp	r1, #0
	bne	.L208
	ldr	r3, .L210+8
	mov	r7, #0
	str	r7, [fp, #-48]
	ldr	ip, [r3, r0, asl #2]
	mov	r0, #0
	bfi	r0, r7, #7, #1
	strb	r0, [fp, #-46]
	cmp	ip, #0
	mov	r0, #8
	ldrne	r10, [ip, #1168]
	moveq	r3, ip
	moveq	r10, ip
	uxtbne	r3, r10
	andne	ip, r3, #1
	cmp	r2, #0
	strneb	r3, [r6, #1]
	add	r3, r4, #4096
	ldr	r2, [r4, #20]
	ldr	r3, [r3, #1084]
	ldr	r1, [r4, #24]
	ldrb	lr, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #1
	str	ip, [fp, #-56]
	moveq	r3, #13
	movne	r3, #1
	mla	r1, r2, r1, r1
	bfi	r3, lr, #6, #1
	and	r3, r3, #111
	bfi	r3, r7, #5, #1
	strb	r3, [fp, #-45]
	ldr	r8, [fp, #-48]
	add	r1, r1, r2
	mov	r3, r6
	mov	r2, r5
	bfi	r8, r1, #0, #20
	str	r8, [r4, #2504]
	str	r8, [fp, #-48]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L210+12
	mov	r0, #3
	bl	dprint_vfmw
	ldr	r1, [r4, #196]
	ldr	r2, [r4, #1328]
	mov	r3, #0
	cmp	r1, #1920
	ldr	r0, [r4, #1340]
	bfi	r3, r2, #4, #1
	strlsb	r7, [r4]
	strhib	r7, [r4, #5]
	movls	r1, #1
	str	r7, [fp, #-48]
	bfi	r3, r0, #6, #1
	strlsb	r1, [r4, #5]
	movhi	r1, r7
	ldrb	r0, [fp, #-45]	@ zero_extendqisi2
	mov	r8, #3
	ldrhib	lr, [r4]	@ zero_extendqisi2
	movls	lr, r7
	bfi	r0, r1, #5, #1
	strb	r0, [fp, #-45]
	ldrh	r1, [fp, #-46]
	mvn	r3, r3, asl #25
	ldr	ip, [fp, #-56]
	mov	r2, #13
	bfi	r1, r8, #0, #12
	strh	r1, [fp, #-46]	@ movhi
	strb	r2, [fp, #-48]
	mvn	r3, r3, lsr #25
	mov	r1, r1, lsr #8
	strb	r3, [fp, #-47]
	mov	r2, r5
	mov	r3, r6
	mov	r0, #12
	movw	r7, #3075
	movt	r7, 48
	andhi	lr, lr, #1
	bfi	r1, lr, #6, #1
	and	r1, r1, #127
	bfi	r1, ip, #4, #1
	strb	r1, [fp, #-45]
	ldr	ip, [fp, #-48]
	mov	r1, ip
	str	ip, [r4, #2508]
	str	ip, [fp, #-56]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	mov	r0, r8
	ldr	r1, .L210+16
	mov	r2, ip
	bl	dprint_vfmw
	ldr	ip, [r9, #56]
	mov	r3, r6
	mov	r2, r5
	bic	ip, ip, #15
	mov	r0, #16
	str	ip, [r4, #2512]
	mov	r1, ip
	str	ip, [fp, #-56]
	bl	MFDE_ConfigReg
	ldr	ip, [fp, #-56]
	ldr	r1, .L210+20
	mov	r0, r8
	mov	r2, ip
	bl	dprint_vfmw
	ldr	r1, [r9, #40]
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
	cmp	r10, #1
	beq	.L209
.L201:
	ldr	r8, [r4, #1296]
	mov	r3, r6
	mov	r2, r5
	mov	r0, #100
	mov	r7, #0
	str	r8, [r4, #2560]
	mov	r1, r8
	bl	MFDE_ConfigReg
	mov	r2, r8
	ldr	r1, .L210+24
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
	ldr	r1, .L210+28
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
	ldr	r1, .L210+32
	mov	r0, #3
	bl	dprint_vfmw
	mov	r3, r6
	mov	r2, r5
	mov	r1, #0
	mov	r0, #152
	bl	MFDE_ConfigReg
	mov	r2, #0
	ldr	r1, .L210+36
	mov	r0, #3
	bl	dprint_vfmw
	mov	r0, #32
	mov	r3, r6
	mov	r2, r5
	mvn	r1, #0
	bl	MFDE_ConfigReg
	mov	r0, #0
.L196:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L209:
	mov	r3, r6
	mov	r2, r5
	mov	r1, #60
	mov	r0, #92
	bl	MFDE_ConfigReg
	mov	r2, #60
	ldr	r1, .L210+40
	mov	r0, r8
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
	mov	r0, r8
	ldr	r1, .L210+44
	bl	dprint_vfmw
	b	.L201
.L208:
	ldr	r2, .L210+48
	mov	r0, #0
	ldr	r1, .L210+52
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L196
.L211:
	.align	2
.L210:
	.word	g_HalDisable
	.word	g_VdmDrvParam
	.word	s_pstVfmwChan
	.word	.LC25
	.word	.LC26
	.word	.LC27
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC28
	.word	.LC29
	.word	.LANCHOR1+2172
	.word	.LC24
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_CfgVdmReg, .-HEVCHAL_V5R2C1_CfgVdmReg
	.align	2
	.global	HEVCHAL_V5R2C1_SetSliceMsgSedOnly
	.type	HEVCHAL_V5R2C1_SetSliceMsgSedOnly, %function
HEVCHAL_V5R2C1_SetSliceMsgSedOnly:
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
	ble	.L213
	mov	r3, #0
	mov	r8, r3
	mov	r4, r3
.L215:
	ldrb	r1, [r2, #25]	@ zero_extendqisi2
	cmp	r1, #0
	moveq	r8, r3
	add	r3, r3, #1
	moveq	r4, r2
	cmp	r3, r0
	ldr	r2, [r2, #1356]
	bne	.L215
	cmp	r4, #0
	beq	.L213
	rsb	r3, r8, r3
	cmp	r3, #0
	addgt	r7, r10, #60
	movgt	r5, #0
	movgt	ip, r3
	bgt	.L223
	b	.L224
.L229:
	ldr	r2, [r4, #1356]
	mov	ip, r9
	ldrb	lr, [r6, #225]	@ zero_extendqisi2
	cmp	lr, #0
	ldr	lr, [r2, #92]
	sub	lr, lr, #1
	beq	.L227
	ldr	r2, [r2, #568]
	mov	ip, r9
.L221:
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
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	bne	.L228
	ldr	ip, [r6, #2488]
	ldr	r4, [r4, #1356]
	rsb	ip, r8, ip
	cmp	ip, r5
	ble	.L224
.L223:
	sub	ip, ip, #1
	ldr	r3, [r7]
	cmp	r5, #205
	cmple	r5, ip
	ldr	r9, [r7, #4]!
	ldr	r0, [r4, #80]
	movlt	ip, #1
	movge	ip, #0
	ldr	r1, [r4, #92]
	blt	.L229
	ldr	lr, [r6, #24]
	ldr	r2, [r6, #20]
	mla	r2, lr, r2, r2
	add	lr, r2, lr
.L227:
	mov	r2, lr
	b	.L221
.L224:
	mov	r0, #0
.L217:
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L228:
	ldr	r2, .L230
	mov	r0, #1
	ldr	r1, .L230+4
	bl	dprint_vfmw
	mvn	r0, #0
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L213:
	ldr	r2, .L230
	mov	r0, #1
	ldr	r1, .L230+8
	bl	dprint_vfmw
	mvn	r0, #0
	b	.L217
.L231:
	.align	2
.L230:
	.word	.LANCHOR1+2200
	.word	.LC35
	.word	.LC34
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_SetSliceMsgSedOnly, .-HEVCHAL_V5R2C1_SetSliceMsgSedOnly
	.align	2
	.global	HEVCHAL_V5R2C1_StartDec
	.type	HEVCHAL_V5R2C1_StartDec, %function
HEVCHAL_V5R2C1_StartDec:
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
	ldr	r2, .L297
	movw	ip, #1228
	str	r1, [fp, #-88]
	mov	r9, r0
	mla	r3, ip, r1, r2
	str	r3, [fp, #-80]
	bl	HEVCHAL_CheckParaValid
	cmn	r0, #1
	beq	.L287
	ldr	r6, [fp, #-88]
	ldr	r5, [fp, #-80]
	mov	r1, r6
	mov	r0, r5
	bl	HEVCHAL_GetVdmRegVirAddr
	cmn	r0, #1
	beq	.L287
	mov	r3, r4
	mov	r2, r6
	mov	r1, r5
	mov	r0, r9
	bl	HEVCHAL_V5R2C1_CfgVdmReg
	ldr	r3, [r5, #60]
	mov	r1, r5
	ldr	r2, [r5, #56]
	mov	r0, r9
	bl	HEVCHAL_V5R2C1_SetPicMsg
	ldr	r4, [r9, #2492]
	cmp	r4, #0
	beq	.L289
	add	r3, r9, #4096
	ldr	r3, [r3, #1084]
	cmp	r3, #1
	beq	.L290
	ldr	r5, [r4, #92]
	cmp	r5, #0
	bne	.L291
	mov	r10, r4
	str	r5, [fp, #-92]
.L238:
	ldr	r2, [r9, #24]
	ldr	r3, [r9, #20]
	ldr	r1, [r9, #2488]
	mla	r3, r2, r3, r3
	cmp	r1, #0
	add	r3, r3, r2
	str	r3, [fp, #-76]
	ble	.L241
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
.L254:
	ldr	r3, [fp, #-68]
	mov	r0, r10
	ldr	r1, [fp, #-72]
	add	r7, r3, r5
	ldr	r3, [fp, #-84]
	ldr	lr, .L297
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
	beq	.L287
	ldr	r2, [r9, #2488]
	add	r5, r5, #1
	ldr	r6, [r10, #92]
	cmp	r2, r5
	ldr	ip, [r10, #80]
	ble	.L242
	ldr	r4, [r10, #1356]
	cmp	r4, #0
	bne	.L286
	b	.L243
.L293:
	add	r5, r5, #1
	cmp	r5, r2
	beq	.L292
	ldr	r4, [r4, #1356]
	cmp	r4, #0
	beq	.L243
.L286:
	ldr	r3, [r4, #92]
	cmp	r6, r3
	bcs	.L293
.L249:
	cmp	r7, #209
	cmpne	r2, r5
	beq	.L255
	ldrb	r2, [r9, #225]	@ zero_extendqisi2
	ldr	r3, [r4, #92]
	cmp	r2, #0
	ldr	r2, [fp, #-68]
	sub	r7, r3, #1
	ldr	r3, [fp, #-72]
	ldrne	r8, [r4, #568]
	add	r2, r3, r2
	ldr	r3, .L297
	add	r2, r2, r5
	moveq	r8, r7
	add	r2, r2, #10
	ldr	r3, [r3, r2, asl #2]
	str	r3, [fp, #-60]
.L251:
	str	r7, [r10, #572]
	mov	r1, r8
	ldr	r2, [fp, #-76]
	mov	r0, r10
	str	ip, [fp, #-64]
	bl	HEVCHAL_CheckSliceAddrValid
	cmn	r0, #1
	beq	.L287
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
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	bne	.L294
	ldr	r3, [r9, #2488]
	ldr	r2, [fp, #-48]
	cmp	r5, r3
	add	r2, r2, #1
	str	r2, [fp, #-48]
	ldr	r2, [r10, #572]
	bge	.L295
	mov	r10, r4
	b	.L254
.L291:
	ldrb	r3, [r9, #225]	@ zero_extendqisi2
	movw	r0, #1228
	ldr	r2, .L297
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
	bl	HEVCHAL_V5R2C1_SetSliceMsg
	cmp	r0, #0
	bne	.L296
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
	b	.L238
.L292:
	cmp	r4, #0
	beq	.L243
.L255:
	ldr	r3, [fp, #-76]
	mov	r7, #0
	str	r7, [r10, #1356]
	str	r7, [fp, #-60]
	mov	r8, r3
	ldr	r5, [r9, #2488]
	mov	r7, r3
	b	.L251
.L242:
	cmp	r10, #0
	beq	.L243
	mov	r4, r10
	b	.L249
.L241:
	ldr	r1, .L297+4
	mov	r0, #1
	bl	dprint_vfmw
.L287:
	mvn	r7, #0
.L282:
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L243:
	ldr	r2, .L297+8
	mov	r0, #1
	ldr	r1, .L297+12
	mvn	r7, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L294:
	ldr	r2, .L297+8
	mov	r0, #1
	ldr	r1, .L297+16
	mvn	r7, #0
	bl	dprint_vfmw
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L295:
	cmp	r3, #0
	ldr	r1, [fp, #-48]
	mov	r7, r0
	movgt	r2, #1
	movle	r2, #0
	cmp	r1, #0
	andgt	r2, r2, #1
	movle	r2, #0
	cmp	r2, #0
	beq	.L241
	ldr	r2, [fp, #-88]
	movw	r5, #307
	ldr	r1, [fp, #-92]
	mla	r5, r5, r2, r1
	ldr	r2, .L297
	add	r3, r5, r3
	add	r3, r3, #14
	ldr	r0, [r2, r3, asl #2]
	bl	HEVCHAL_V5R2C1_CutSliceChain
	mov	r0, r7
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, pc}
.L290:
	ldr	r1, [fp, #-80]
	mov	r0, r9
	sub	sp, fp, #40
	ldmfd	sp, {r4, r5, r6, r7, r8, r9, r10, fp, sp, lr}
	b	HEVCHAL_V5R2C1_SetSliceMsgSedOnly
.L296:
	mov	r0, r6
	ldr	r2, .L297+8
	ldr	r1, .L297+20
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L282
.L289:
	mov	r0, r4
	ldr	r2, .L297+8
	ldr	r1, .L297+24
	mvn	r7, #0
	bl	dprint_vfmw
	b	.L282
.L298:
	.align	2
.L297:
	.word	g_HwMem
	.word	.LC39
	.word	.LANCHOR1+2236
	.word	.LC37
	.word	.LC38
	.word	.LC35
	.word	.LC36
	UNWIND(.fnend)
	.size	HEVCHAL_V5R2C1_StartDec, .-HEVCHAL_V5R2C1_StartDec
	.section	.rodata
	.align	2
.LANCHOR1 = . + 0
	.type	__func__.14461, %object
	.size	__func__.14461, 18
__func__.14461:
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
	.type	__func__.14482, %object
	.size	__func__.14482, 29
__func__.14482:
	.ascii	"HEVCHAL_V5R2C1_CutSliceChain\000"
	.space	3
	.type	__func__.14501, %object
	.size	__func__.14501, 19
__func__.14501:
	.ascii	"HEVC_WriteTileInfo\000"
	.space	1
	.type	__func__.14527, %object
	.size	__func__.14527, 25
__func__.14527:
	.ascii	"HEVCHAL_V5R2C1_SetPicMsg\000"
	.space	3
	.type	__func__.14547, %object
	.size	__func__.14547, 34
__func__.14547:
	.ascii	"HEVCHAL_SetSliceMsgStreamAddrInfo\000"
	.space	2
	.type	__func__.14601, %object
	.size	__func__.14601, 27
__func__.14601:
	.ascii	"HEVCHAL_V5R2C1_SetSliceMsg\000"
	.space	1
	.type	s_SliceTypeForPMV, %object
	.size	s_SliceTypeForPMV, 12
s_SliceTypeForPMV:
	.word	2
	.word	1
	.word	0
	.type	__func__.14612, %object
	.size	__func__.14612, 23
__func__.14612:
	.ascii	"HEVCHAL_CheckParaValid\000"
	.space	1
	.type	__func__.14618, %object
	.size	__func__.14618, 25
__func__.14618:
	.ascii	"HEVCHAL_GetVdmRegVirAddr\000"
	.space	3
	.type	__func__.14624, %object
	.size	__func__.14624, 23
__func__.14624:
	.ascii	"HEVCHAL_CheckSlicePara\000"
	.space	1
	.type	__func__.14651, %object
	.size	__func__.14651, 25
__func__.14651:
	.ascii	"HEVCHAL_V5R2C1_CfgVdmReg\000"
	.space	3
	.type	__func__.14671, %object
	.size	__func__.14671, 34
__func__.14671:
	.ascii	"HEVCHAL_V5R2C1_SetSliceMsgSedOnly\000"
	.space	2
	.type	__func__.14701, %object
	.size	__func__.14701, 24
__func__.14701:
	.ascii	"HEVCHAL_V5R2C1_StartDec\000"
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
	ASCII(.ascii	"qmatrix[%d] = 0x%x\012\000" )
.LC5:
	ASCII(.ascii	"picmsg Dxx addr 0x%x = 0x%x\012\000" )
	.space	3
.LC6:
	ASCII(.ascii	"can not map slice segment info virtual address!\012" )
	ASCII(.ascii	"\000" )
	.space	3
.LC7:
	ASCII(.ascii	"TileId: 0x%x\012\000" )
	.space	2
.LC8:
	ASCII(.ascii	"can not map down msg virtual address!\012\000" )
	.space	1
.LC9:
	ASCII(.ascii	"pic msg burst0:\012\000" )
	.space	3
.LC10:
	ASCII(.ascii	"picmsg D[0] addr 0x%x = 0x%x\012\000" )
	.space	2
.LC11:
	ASCII(.ascii	"HEVC_WriteTileInfo return error.\012\000" )
	.space	2
.LC12:
	ASCII(.ascii	"%s FATAL: i=0, valid_bitlen=0\012\000" )
	.space	1
.LC13:
	ASCII(.ascii	"slicemsg D[%d] addr 0x%x = 0x%x\012\000" )
	.space	3
.LC14:
	ASCII(.ascii	"HEVCHAL_V5R2C1_SetSliceMsg can not map slice msg vi" )
	ASCII(.ascii	"rtual address!\012\000" )
	.space	1
.LC15:
	ASCII(.ascii	"%s VdhId %d >= %d\012\000" )
	.space	1
.LC16:
	ASCII(.ascii	"pParam is null\012\000" )
.LC17:
	ASCII(.ascii	"FATAL: ApcSize > 16\012\000" )
	.space	3
.LC18:
	ASCII(.ascii	"VdhId is wrong! HEVC4HAL_V200R003_StartDec\012\000" )
.LC19:
	ASCII(.ascii	"%s vdm register virtual address not mapped, reset f" )
	ASCII(.ascii	"ailed!\012\000" )
	.space	1
.LC20:
	ASCII(.ascii	"%s: i = %d, pSlicePara = NULL!\012\000" )
.LC21:
	ASCII(.ascii	"SliceSegmentTileAddress %d < prevEndCtbInSliceTile " )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC22:
	ASCII(.ascii	"end_ctb_in_slice_raster(%d)/end_ctb_in_slice_tile(%" )
	ASCII(.ascii	"d) > pic_max_ctb(%d)\012\000" )
	.space	3
.LC23:
	ASCII(.ascii	"SliceSegmentTileAddress %d > end_ctb_in_slice_tile " )
	ASCII(.ascii	"%d\012\000" )
	.space	1
.LC24:
	ASCII(.ascii	"%s: pMfdeTask(%p) = NULL\012\000" )
	.space	2
.LC25:
	ASCII(.ascii	"HEVC_BASIC_CFG0 = 0x%x\012\000" )
.LC26:
	ASCII(.ascii	"HEVC_BASIC_CFG1 = 0x%x\012\000" )
.LC27:
	ASCII(.ascii	"AVM_ADDR = 0x%x\012\000" )
	.space	3
.LC28:
	ASCII(.ascii	"VREG_V200R003_PART_DEC_OVER_INT_LEVEL=0x%x\012\000" )
.LC29:
	ASCII(.ascii	"VREG_LINE_NUM_STADDR = 0x%x\012\000" )
	.space	3
.LC30:
	ASCII(.ascii	"HEVC_VFMW_YSTADDR_1D = 0x%x\012\000" )
	.space	3
.LC31:
	ASCII(.ascii	"HEVC_VFMW_UVOFFSET_1D = 0x%x\012\000" )
	.space	2
.LC32:
	ASCII(.ascii	"SCD REG_EMAR_ID = 0x%x\012\000" )
.LC33:
	ASCII(.ascii	"VREG_FF_APT_EN = 0x%x\012\000" )
	.space	1
.LC34:
	ASCII(.ascii	"%s : pTargetSlicePara == NULL\012\000" )
	.space	1
.LC35:
	ASCII(.ascii	"%s 0: set slice msg failed!\012\000" )
	.space	3
.LC36:
	ASCII(.ascii	"%s pFirstSlice = NULL!\012\000" )
.LC37:
	ASCII(.ascii	"%s pTargetSlicePara is NULL!\012\000" )
	.space	2
.LC38:
	ASCII(.ascii	"%s 1: set slice msg failed!\012\000" )
	.space	3
.LC39:
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
