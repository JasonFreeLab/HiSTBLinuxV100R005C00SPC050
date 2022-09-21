#include "hi_asm_define.h"
	.arch armv8-a+fp+simd
	.file	"vdm_hal.c"
	.global	_mcount
	.text
	.align	2
	.p2align 3,,7
	.type	VDMHAL_UpateDecParam.constprop.10, %function
VDMHAL_UpateDecParam.constprop.10:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, 17
	bhi	.L1
	ldr	x0, .LC0
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx4
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx4:
	.section	.rodata
	.align	0
	.align	2
.L4:
	.byte	(.L14 - .Lrtx4) / 4
	.byte	(.L5 - .Lrtx4) / 4
	.byte	(.L6 - .Lrtx4) / 4
	.byte	(.L7 - .Lrtx4) / 4
	.byte	(.L1 - .Lrtx4) / 4
	.byte	(.L8 - .Lrtx4) / 4
	.byte	(.L9 - .Lrtx4) / 4
	.byte	(.L1 - .Lrtx4) / 4
	.byte	(.L10 - .Lrtx4) / 4
	.byte	(.L11 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L12 - .Lrtx4) / 4
	.byte	(.L13 - .Lrtx4) / 4
	.byte	(.L1 - .Lrtx4) / 4
	.byte	(.L14 - .Lrtx4) / 4
	.byte	(.L15 - .Lrtx4) / 4
	.byte	(.L16 - .Lrtx4) / 4
	.text
	.p2align 3
.L14:
	mov	w0, 1
	strb	wzr, [x19, 4]
	strb	w0, [x19, 17]
.L1:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L15:
	mov	w0, 1
	strb	wzr, [x19]
	strb	w0, [x19, 5]
	b	.L1
	.p2align 3
.L16:
	add	x19, x19, 270336
	mov	w0, 1
	str	wzr, [x19, 2468]
	strb	w0, [x19, 2081]
	b	.L1
	.p2align 3
.L5:
	mov	w0, 1
	str	wzr, [x19, 14600]
	strb	w0, [x19, 75]
	b	.L1
	.p2align 3
.L6:
	mov	w0, 1
	str	wzr, [x19, 14672]
	strb	w0, [x19, 167]
	b	.L1
	.p2align 3
.L7:
	add	x1, x19, 45056
	mov	w0, 1
	str	wzr, [x1, 240]
	strb	w0, [x19, 144]
	b	.L1
	.p2align 3
.L8:
	mov	w0, 1
	str	wzr, [x19, 160]
	strb	w0, [x19]
	b	.L1
	.p2align 3
.L9:
	mov	w0, 1
	str	wzr, [x19, 14904]
	strb	w0, [x19, 48]
	b	.L1
	.p2align 3
.L10:
	mov	w0, 1
	str	wzr, [x19, 76]
	strb	w0, [x19]
	b	.L1
	.p2align 3
.L11:
	mov	w0, 1
	str	wzr, [x19, 72]
	strb	w0, [x19, 1]
	b	.L1
	.p2align 3
.L12:
	mov	w0, 1
	str	wzr, [x19, 264]
	strb	w0, [x19, 104]
	b	.L1
	.p2align 3
.L13:
	mov	w0, 1
	str	wzr, [x19, 3144]
	strb	w0, [x19, 2778]
	b	.L1
	.size	VDMHAL_UpateDecParam.constprop.10, .-VDMHAL_UpateDecParam.constprop.10
	.align	3
.LC0:
	.xword	.L4
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetHalMemSize
	.type	VDMHAL_V5R2C1_GetHalMemSize, %function
VDMHAL_V5R2C1_GetHalMemSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 6291456
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_GetHalMemSize, .-VDMHAL_V5R2C1_GetHalMemSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_OpenHAL
	.type	VDMHAL_V5R2C1_OpenHAL, %function
VDMHAL_V5R2C1_OpenHAL:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	str	x25, [sp, 64]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L31
	ldp	w23, w22, [x19]
	ldr	w19, [x19, 8]
	cbz	w23, .L32
	mov	w0, 6291455
	cmp	w22, w0
	ble	.L33
	cmp	w19, wzr
	bgt	.L34
	sxtw	x20, w19
	ldr	x25, .LC15
	ldr	x21, .LC16
	mov	x2, 268
	add	x0, x20, x20, lsl 4
	mov	w1, 0
	lsl	x0, x0, 2
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	add	x0, x21, x0, lsl 2
	blr	x3
	ldr	x24, .LC1
	lsl	x0, x20, 6
	ldr	x3, [x25, 96]
	sub	x0, x0, x20
	mov	w1, 4
	lsl	x0, x0, 2
	str	w1, [x21]
	sub	x25, x0, x20
	mov	x2, 1256
	mov	w1, 0
	add	x25, x0, x25, lsl 2
	add	x21, x24, x25
	mov	x0, x21
	blr	x3
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC18
	str	x0, [x24, x25]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 53248
	movk	w0, 0xf8c3, lsl 16
	bl	MEM_Phy2Vir
	mov	x2, x0
	ldr	x1, .LC20
	str	x0, [x21, 16]
	mov	w0, 22
	bl	dprint_vfmw
	mov	w0, 1256
	add	w4, w23, 1023
	and	w4, w4, -1024
	add	w1, w23, w22
	smull	x19, w19, w0
	sub	w1, w1, w4
	mov	w2, 1024
	add	x0, x19, 56
	add	x19, x19, 896
	stp	w4, w1, [x21, 32]
	str	w2, [x21, 40]
	add	x0, x24, x0
	add	x2, x24, x19
	mov	w1, w4
	.p2align 2
.L25:
	str	w1, [x0], 4
	add	w1, w1, 1280
	cmp	x0, x2
	bne	.L25
	lsl	x0, x20, 6
	add	w2, w4, 266240
	sub	x0, x0, x20
	add	w2, w2, 3072
	lsl	x0, x0, 2
	add	w3, w2, 4096
	sub	x20, x0, x20
	mov	w7, 210
	add	w3, w3, 1024
	add	x0, x0, x20, lsl 2
	add	w1, w3, 32768
	add	x0, x24, x0
	add	w1, w1, 1023
	and	w1, w1, -32768
	add	w4, w1, 4427776
	add	w5, w1, 4370432
	str	w7, [x0, 1080]
	add	x7, x0, 1024
	add	w4, w4, 1024
	add	w5, w5, 2048
	add	w6, w1, 589824
	add	w8, w1, 45056
	stp	w2, w1, [x7, 80]
	stp	w1, w1, [x7, 88]
	str	w3, [x0, 1124]
	add	w3, w1, 1773568
	add	w3, w3, 1152
	add	w7, w1, 1093632
	add	w2, w1, 4390912
	cmp	w4, w3
	add	w2, w2, 1024
	str	w7, [x0, 1164]
	add	w7, w1, 4423680
	str	w5, [x0, 1192]
	str	w3, [x0, 1152]
	add	w5, w1, 4374528
	str	w2, [x0, 1204]
	add	w5, w5, 1024
	str	w2, [x0, 1220]
	csel	w2, w4, w3, cs
	add	w3, w7, 1024
	str	w3, [x0, 1200]
	add	w3, w1, 1769472
	add	w4, w6, 2048
	add	w3, w3, 2048
	str	w5, [x0, 1196]
	sub	w2, w2, w23
	add	w5, w1, 1179648
	add	w5, w5, 2048
	str	w1, [x0, 1172]
	str	w4, [x0, 1132]
	cmp	w22, w2
	add	w4, w1, 2142208
	str	w3, [x0, 1144]
	str	w3, [x0, 1148]
	add	w3, w1, 3190784
	str	w6, [x0, 1120]
	add	w1, w1, 4239360
	str	w6, [x0, 1128]
	str	wzr, [x0, 1156]
	str	w8, [x0, 1160]
	str	wzr, [x0, 1184]
	str	w5, [x0, 1136]
	str	w5, [x0, 1140]
	str	w4, [x0, 1168]
	str	w3, [x0, 1176]
	str	w1, [x0, 1208]
	bcc	.L26
	mov	x0, x21
	bl	H264HAL_V5R2C1_InitHal
	cmp	w0, wzr
	mov	x0, x21
	csetm	w19, ne
	bl	HEVCHAL_V5R2C1_InitHal
	cmp	w0, wzr
	csinv	w19, w19, wzr, eq
.L21:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L34:
	ldr	x1, .LC14
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	ldr	x25, [sp, 64]
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L26:
	ldr	x1, .LC22
	mov	w3, w22
	mov	w0, 0
	mov	w19, -1
	bl	dprint_vfmw
	b	.L21
.L32:
	ldr	x3, .LC10
.L30:
	ldr	x2, .LC6
	mov	w0, 0
	ldr	x1, .LC8
	mov	w19, -1
	bl	dprint_vfmw
	b	.L21
.L33:
	ldr	x3, .LC12
	b	.L30
.L31:
	ldr	x3, .LC5
	b	.L30
	.size	VDMHAL_V5R2C1_OpenHAL, .-VDMHAL_V5R2C1_OpenHAL
	.align	3
.LC1:
	.xword	g_HwMem
	.align	3
.LC5:
	.xword	.LC4
	.align	3
.LC6:
	.xword	.LANCHOR0
	.align	3
.LC8:
	.xword	.LC7
	.align	3
.LC10:
	.xword	.LC9
	.align	3
.LC12:
	.xword	.LC11
	.align	3
.LC14:
	.xword	.LC13
	.align	3
.LC15:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC16:
	.xword	g_VdmExtParam
	.align	3
.LC18:
	.xword	.LC17
	.align	3
.LC20:
	.xword	.LC19
	.align	3
.LC22:
	.xword	.LC21
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CloseHAL
	.type	VDMHAL_V5R2C1_CloseHAL, %function
VDMHAL_V5R2C1_CloseHAL:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_CloseHAL, .-VDMHAL_V5R2C1_CloseHAL
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CalcFsSize
	.type	VDMHAL_V5R2C1_CalcFsSize, %function
VDMHAL_V5R2C1_CalcFsSize:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w25, w0
	mov	x0, x30
	mov	w27, w1
	mov	w20, w2
	mov	w23, w3
	mov	w24, w4
	mov	x22, x5
	bl	_mcount
	sub	w1, w27, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L37
	sub	w1, w20, #32
	mov	w6, w20
	cmp	w1, w0
	bhi	.L37
	ldr	x1, .LC27
	add	w0, w27, 15
	asr	w0, w0, 4
	add	w3, w20, 15
	asr	w3, w3, 4
	cmp	w0, 45
	ldrb	w2, [x1]
	mov	w1, 36
	ccmp	w3, w1, 0, le
	mov	w19, 32
	cset	w4, le
	mov	w1, 64
	cmp	w4, wzr
	lsl	w21, w0, 4
	csel	w19, w19, w1, eq
	cmp	w2, 1
	csel	w19, w19, w1, ne
	cmp	w24, 16
	beq	.L42
	cmp	w24, 17
	beq	.L69
	mul	w19, w0, w19
	ldr	x26, .LC29
	add	w21, w21, 255
	add	w6, w20, 31
	and	w21, w21, -256
	mul	w19, w19, w3
	ldr	x5, [x26, w25, sxtw 3]
	and	w6, w6, -32
	add	w19, w19, 143
	mov	w28, 0
	and	w19, w19, -128
	mov	w7, 0
.L45:
	ldr	w0, [x5, 1240]
	cmp	w0, 1
	beq	.L70
.L67:
	asr	w4, w19, 1
	mov	w9, 0
	mov	w8, 0
	mov	w27, 0
.L48:
	cmp	w23, 1
	mul	w23, w6, w21
	beq	.L71
	mul	w2, w28, w7
	lsl	w1, w27, 2
	lsl	w0, w2, 2
	sub	w1, w1, w27
	sub	w2, w0, w2
	lsl	w0, w23, 2
	sub	w0, w0, w23
	lsr	w0, w0, 1
	add	w0, w0, w2, lsr 1
	add	w20, w0, w1, lsr 1
.L51:
	add	x2, x5, 503808
	ldr	w0, [x2, 1288]
	cbz	w0, .L72
	add	x0, x5, 507904
	cmp	w24, 17
	lsl	w21, w21, 4
	str	w20, [x0, 760]
	str	w8, [x2, 3636]
	str	w9, [x2, 3640]
	str	w4, [x2, 3676]
	beq	.L53
.L73:
	ldr	w0, [x2, 1296]
	mov	w1, 32
	sub	w24, w24, #16
	str	w21, [x2, 3628]
	cmp	w0, 32
	lsr	w21, w21, 1
	csel	w0, w0, w1, le
	str	w21, [x2, 3632]
	str	w0, [x2, 3680]
	cmp	w24, 1
	add	w0, w23, w27
	str	w0, [x2, 3660]
	bls	.L54
.L55:
	ldr	x0, [x26, w25, sxtw 3]
	mov	w4, 1024
	add	w1, w20, 1056
	add	x3, x0, 507904
	add	w2, w1, w19
	add	w5, w2, w4
	str	w19, [x3, 764]
	str	w4, [x3, 772]
	ldrsb	w0, [x0, 44]
	cmp	w0, 1
	csel	w2, w5, w2, eq
	cbz	x22, .L63
	str	w1, [x22, 4]
	mov	w0, 0
	ldr	x3, [x26, w25, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 1296]
	stp	w3, w19, [x22, 8]
	ldr	x3, [x26, w25, sxtw 3]
	add	x3, x3, 503808
	ldr	w3, [x3, 3680]
	stp	w3, w4, [x22, 16]
	str	w2, [x22]
	ldr	x2, [x26, w25, sxtw 3]
	add	x2, x2, 507904
	str	w1, [x2, 768]
.L65:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.p2align 3
.L72:
	ldr	x1, .LC28
	add	x0, x2, 3624
	mov	x2, 1248
	lsl	w21, w21, 4
	stp	w4, w7, [x29, 96]
	ldr	x3, [x1, 96]
	mov	w1, 0
	stp	w8, w9, [x29, 104]
	blr	x3
	ldr	x5, [x26, w25, sxtw 3]
	cmp	w24, 17
	ldp	w8, w9, [x29, 104]
	add	x0, x5, 507904
	add	x2, x5, 503808
	ldp	w4, w7, [x29, 96]
	str	w20, [x0, 760]
	str	w8, [x2, 3636]
	str	w9, [x2, 3640]
	str	w4, [x2, 3676]
	bne	.L73
.L53:
	mov	w0, 1
	str	w21, [x2, 3628]
	str	w0, [x2, 3680]
	lsr	w21, w21, 1
	add	w0, w23, w27
	str	w21, [x2, 3632]
	str	w0, [x2, 3660]
.L54:
	ldr	w0, [x5, 1548]
	cmp	w0, 8
	ble	.L55
	lsl	w6, w23, 2
	ldr	x1, .LC31
	sub	w6, w6, w23
	lsl	w23, w27, 2
	sub	w27, w23, w27
	mov	w0, 31
	mul	w28, w28, w7
	lsr	w23, w27, 1
	lsl	w7, w7, 4
	add	w6, w23, w6, lsr 1
	str	w7, [x2, 3644]
	str	w6, [x2, 3652]
	str	w28, [x2, 3656]
	bl	dprint_vfmw
	b	.L55
	.p2align 3
.L71:
	lsl	w1, w3, 6
	sub	w1, w1, w3, lsl 4
	mul	w20, w1, w21
	b	.L51
	.p2align 3
.L42:
	ldr	x26, .LC29
	mul	w19, w3, w21
	add	w21, w27, 255
	ldr	x5, [x26, w25, sxtw 3]
	add	w19, w19, 143
	and	w21, w21, -256
	and	w19, w19, -128
	ldr	w0, [x5, 1548]
	cmp	w0, 8
	ble	.L74
	ldr	w0, [x5, 1240]
	add	w28, w20, 31
	and	w28, w28, -32
	lsr	w7, w21, 2
	cmp	w0, 1
	bne	.L67
	.p2align 2
.L70:
	cmp	w24, 17
	mov	w0, 1920
	ccmp	w27, w0, 0, ne
	ble	.L67
	add	w2, w20, 63
	asr	w4, w19, 1
.L60:
	adds	w8, w27, 2047
	add	w27, w27, 4094
	csel	w27, w27, w8, mi
	and	w27, w27, -2048
	cmp	w27, wzr
	add	w8, w27, 127
	csel	w8, w8, w27, lt
	add	w27, w2, 63
	cmp	w2, wzr
	asr	w8, w8, 7
	csel	w2, w27, w2, lt
	lsl	w27, w8, 5
	asr	w2, w2, 6
	mul	w27, w2, w27
	mov	w9, w27
	b	.L48
	.p2align 3
.L69:
	ldr	x26, .LC29
	add	w21, w27, 255
	add	w2, w20, 63
	and	w21, w21, -256
	and	w6, w2, -64
	ldr	x5, [x26, w25, sxtw 3]
	ldr	w0, [x5, 1548]
	cmp	w0, 8
	bgt	.L58
	mov	w28, 0
	mov	w7, 0
.L46:
	ldr	w0, [x5, 1240]
	mov	w4, 64
	movk	w4, 0x12, lsl 16
	cmp	w0, 1
	beq	.L64
	mov	w19, 128
	mov	w9, 0
	mov	w8, 0
	movk	w19, 0x24, lsl 16
	mov	w27, 0
	b	.L48
	.p2align 3
.L74:
	mov	w28, 0
	mov	w7, 0
	b	.L45
	.p2align 3
.L63:
	mov	w0, 0
	b	.L65
	.p2align 3
.L58:
	add	w28, w6, 63
	lsr	w7, w21, 2
	and	w28, w28, -64
	b	.L46
	.p2align 3
.L37:
	ldr	x2, .LC25
	mov	w0, 0
	ldr	x3, .LC24
	ldr	x1, .LC26
	add	x2, x2, 24
	bl	dprint_vfmw
	mov	w0, -1
	b	.L65
	.p2align 3
.L64:
	mov	w19, 128
	movk	w19, 0x24, lsl 16
	b	.L60
	.size	VDMHAL_V5R2C1_CalcFsSize, .-VDMHAL_V5R2C1_CalcFsSize
	.align	3
.LC24:
	.xword	.LC23
	.align	3
.LC25:
	.xword	.LANCHOR0
	.align	3
.LC26:
	.xword	.LC7
	.align	3
.LC27:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC28:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC29:
	.xword	s_pstVfmwChan
	.align	3
.LC31:
	.xword	.LC30
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetRpuSize
	.type	VDMHAL_V5R2C1_GetRpuSize, %function
VDMHAL_V5R2C1_GetRpuSize:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, 1024
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_GetRpuSize, .-VDMHAL_V5R2C1_GetRpuSize
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CalcFsNum
	.type	VDMHAL_V5R2C1_CalcFsNum, %function
VDMHAL_V5R2C1_CalcFsNum:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w20, w0
	mov	x19, x3
	mov	x0, x30
	mov	w21, w1
	bl	_mcount
	cbz	x19, .L81
	cmp	w21, 17
	ldr	x2, .LC35
	beq	.L82
	ldr	x3, [x2, w20, sxtw 3]
	mov	w4, 32
	add	x1, x3, 503808
	ldr	w0, [x1, 1296]
	cmp	w0, w4
	csel	w0, w0, w4, le
	str	w0, [x1, 3680]
	ldr	w0, [x3, 632]
	cmp	w0, 2
	beq	.L83
.L80:
	ldr	x1, [x2, w20, sxtw 3]
	mov	w0, 0
	add	x1, x1, 503808
	ldr	w1, [x1, 1296]
	str	w1, [x19, 8]
	ldr	x1, [x2, w20, sxtw 3]
	add	x1, x1, 503808
	ldr	w1, [x1, 3680]
	str	w1, [x19, 16]
.L78:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L82:
	ldr	x0, [x2, w20, sxtw 3]
	mov	w1, 1
	add	x0, x0, 503808
	str	w1, [x0, 3680]
	b	.L80
	.p2align 3
.L83:
	ldr	w0, [x1, 1300]
	str	w0, [x1, 3680]
	b	.L80
.L81:
	ldr	x2, .LC32
	mov	w0, 1
	ldr	x1, .LC34
	add	x2, x2, 56
	bl	dprint_vfmw
	mov	w0, -1
	b	.L78
	.size	VDMHAL_V5R2C1_CalcFsNum, .-VDMHAL_V5R2C1_CalcFsNum
	.align	3
.LC32:
	.xword	.LANCHOR0
	.align	3
.LC34:
	.xword	.LC33
	.align	3
.LC35:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_DynamicAllocFrame
	.type	VDMHAL_V5R2C1_DynamicAllocFrame, %function
VDMHAL_V5R2C1_DynamicAllocFrame:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w19, w0
	mov	x0, x30
	mov	w23, w1
	mov	w22, w2
	mov	x20, x3
	bl	_mcount
	ldr	x21, .LC36
	mov	w0, w19
	ldr	x1, [x21, w19, sxtw 3]
	add	x1, x1, 503808
	add	x1, x1, 1320
	bl	DelAllFrameMemRecord
	cbnz	w0, .L104
.L85:
	ldr	x1, [x21, w19, sxtw 3]
	mov	w2, 255
	add	x1, x1, 503808
	add	x0, x1, 1320
	add	x1, x1, 3624
	.p2align 2
.L86:
	str	w2, [x0], 72
	cmp	x1, x0
	bne	.L86
	mov	w0, 1088
	cmp	w23, 1920
	ccmp	w22, w0, 0, le
	ble	.L87
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x20, 8]
.L88:
	add	x2, x0, 503808
	ldr	w3, [x0, 1496]
	mov	w0, w19
	add	w1, w3, w1
	str	w1, [x2, 1300]
	bl	VCTRL_GetVidStd
	ldr	x1, [x21, w19, sxtw 3]
	ldr	w2, [x1, 632]
	cmp	w2, 2
	ccmp	w0, 17, 4, eq
	beq	.L91
	add	x1, x1, 503808
	ldr	w0, [x1, 1300]
	str	w0, [x20, 16]
	ldr	x1, [x21, w19, sxtw 3]
.L91:
	add	x0, x1, 507904
	add	x1, x1, 475136
	mov	w4, 1
	mov	w3, w22
	mov	w2, w23
	str	wzr, [x0, 800]
	str	w4, [x1, 2200]
	str	w4, [x0, 1340]
	mov	w0, 31
	ldr	x1, .LC40
	ldr	w4, [x20, 8]
	ldr	w5, [x20, 16]
	bl	dprint_vfmw
	ldr	x0, .LC41
	ldr	x4, [x0]
	cbz	x4, .L92
	ldp	w1, w2, [x20, 12]
	ldp	w3, w5, [x20, 4]
	ldr	w0, [x20, 20]
	stp	w2, w1, [x29, 72]
	stp	w5, w3, [x29, 64]
	stp	w0, w23, [x29, 80]
	str	w22, [x29, 88]
	mov	w3, 28
	add	x2, x29, 64
	mov	w1, 121
	mov	w0, w19
	blr	x4
.L92:
	ldr	x3, .LC42
	mov	x2, 528
	ldr	x0, [x21, w19, sxtw 3]
	mov	w1, 0
	ldr	x3, [x3, 96]
	add	x0, x0, 507904
	add	x0, x0, 808
	blr	x3
	ldr	x1, [x21, w19, sxtw 3]
	mov	w0, w19
	add	x1, x1, 507904
	str	wzr, [x1, 1336]
	bl	FSP_ClearContextAll
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L87:
	ldr	x0, [x21, w19, sxtw 3]
	ldr	w1, [x0, 36]
	cmp	w1, 24
	beq	.L103
	add	x1, x0, 507904
	ldr	w1, [x1, 1396]
	cbnz	w1, .L103
	ldr	w1, [x20, 8]
	add	w1, w1, 4
	str	w1, [x20, 8]
	ldr	x0, [x21, w19, sxtw 3]
	b	.L88
.L103:
	ldr	w1, [x20, 8]
	b	.L88
.L104:
	ldr	x1, .LC38
	mov	w0, 0
	bl	dprint_vfmw
	b	.L85
	.size	VDMHAL_V5R2C1_DynamicAllocFrame, .-VDMHAL_V5R2C1_DynamicAllocFrame
	.align	3
.LC36:
	.xword	s_pstVfmwChan
	.align	3
.LC38:
	.xword	.LC37
	.align	3
.LC40:
	.xword	.LC39
	.align	3
.LC41:
	.xword	g_event_report
	.align	3
.LC42:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.type	VDMHAL_V5R2C1_DynamicAllocFrame_Only, %function
VDMHAL_V5R2C1_DynamicAllocFrame_Only:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x3
	mov	w22, w1
	mov	w21, w2
	bl	_mcount
	ldr	x4, .LC43
	mov	w3, w21
	ldr	w5, [x19, 8]
	mov	w2, w22
	ldr	x1, .LC45
	mov	w0, 31
	ldr	x4, [x4, w20, sxtw 3]
	add	x4, x4, 503808
	str	w5, [x4, 1300]
	ldr	w4, [x19, 8]
	ldr	w5, [x19, 16]
	bl	dprint_vfmw
	ldr	x0, .LC46
	ldr	x4, [x0]
	cbz	x4, .L105
	ldp	w1, w2, [x19, 12]
	ldp	w3, w5, [x19, 4]
	ldr	w0, [x19, 20]
	stp	w2, w1, [x29, 56]
	stp	w5, w3, [x29, 48]
	stp	w0, w22, [x29, 64]
	str	w21, [x29, 72]
	mov	w3, 28
	add	x2, x29, 48
	mov	w1, 122
	mov	w0, w20
	blr	x4
.L105:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
	.size	VDMHAL_V5R2C1_DynamicAllocFrame_Only, .-VDMHAL_V5R2C1_DynamicAllocFrame_Only
	.align	3
.LC43:
	.xword	s_pstVfmwChan
	.align	3
.LC45:
	.xword	.LC44
	.align	3
.LC46:
	.xword	g_event_report
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ArrangeMem_Normal
	.type	VDMHAL_V5R2C1_ArrangeMem_Normal, %function
VDMHAL_V5R2C1_ArrangeMem_Normal:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w19, w0
	mov	x0, x30
	mov	w22, w1
	mov	w23, w2
	mov	w24, w3
	mov	w25, w4
	mov	w27, w5
	mov	x21, x6
	bl	_mcount
	str	xzr, [x29, 120]
	add	x0, x29, 104
	cmp	w22, 20
	stp	xzr, xzr, [x0]
	bhi	.L147
	ldr	x20, .LC51
	ldr	x0, [x20, w19, sxtw 3]
	add	x1, x0, 503808
	ldr	w26, [x1, 1292]
	ldr	w1, [x0, 100]
	cmp	w1, 2
	beq	.L148
	and	w1, w22, -17
	cmp	w1, wzr
	ccmp	w22, 18, 4, ne
	beq	.L149
	cmp	w22, 17
	beq	.L132
.L152:
	ldr	w2, [x0, 1240]
.L116:
	ldr	w3, [x0, 1244]
	ldr	w4, [x0, 1248]
	ldr	w5, [x0, 1252]
	ldr	x1, .LC53
	str	w2, [x0, 1240]
	mov	w0, 1
	bl	dprint_vfmw
.L114:
	mov	w2, w25
	add	x3, x29, 104
	mov	w1, w22
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CalcFsNum
	mov	w25, w0
	add	x5, x29, 104
	mov	w4, w22
	mov	w3, w27
	mov	w2, w24
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CalcFsSize
	orr	w0, w25, w0
	cbnz	w0, .L150
	ldr	x27, [x20, w19, sxtw 3]
	ldr	w22, [x29, 104]
	cmp	w26, w22
	add	x26, x27, 503808
	ldr	w25, [x26, 1296]
	ldr	w5, [x26, 1312]
	beq	.L151
.L119:
	ldr	x2, .LC49
	mov	w3, w22
	ldr	x1, .LC57
	mov	w4, w25
	add	x2, x2, 112
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	add	x3, x29, 104
	mov	w2, w24
	add	x0, x0, 503808
	ldr	w1, [x0, 1288]
	str	w22, [x0, 1292]
	cbnz	w1, .L121
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R2C1_DynamicAllocFrame
.L122:
	ldr	x4, [x20, w19, sxtw 3]
	mov	w3, w25
	ldr	x1, .LC59
	mov	w2, w22
	add	x4, x4, 503808
	mov	w0, 31
	ldr	w4, [x4, 1312]
	bl	dprint_vfmw
	ldr	x19, [x20, w19, sxtw 3]
	ldr	x0, .LC60
	add	x19, x19, 507904
	ldr	x0, [x0]
	blr	x0
	str	w0, [x19, 776]
	mov	w1, 2
.L112:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	mov	w0, w1
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L149:
	mov	w1, 2159
	cmp	w23, 3839
	ccmp	w24, w1, 0, le
	mov	w2, 1
	cset	w1, gt
	cbnz	w1, .L116
	cmp	w22, 17
	bne	.L152
.L132:
	mov	w2, 1
	b	.L116
	.p2align 3
.L121:
	mov	w1, w23
	mov	w0, w19
	bl	VDMHAL_V5R2C1_DynamicAllocFrame_Only
	b	.L122
	.p2align 3
.L151:
	cmp	w5, 1
	beq	.L119
	ldr	w0, [x26, 1288]
	cmp	w0, 1
	beq	.L119
	cbz	x21, .L153
	add	x1, x27, 507904
	add	x22, x26, 3624
	mov	x0, x27
	ldr	w23, [x1, 760]
	cbz	w25, .L154
.L124:
	add	x0, x0, 503808
	ldr	w2, [x0, 1300]
	cmp	w2, 30
	bgt	.L155
.L125:
	ldr	x24, .LC60
	add	x26, x26, 3624
	mov	w0, 8
	str	w2, [x26, 48]
	ldr	x1, [x24, 24]
	blr	x1
	ldr	x7, [x20, w19, sxtw 3]
	add	x9, x7, 507904
	ldr	w0, [x9, 800]
	cbz	w0, .L130
	ldp	w10, w6, [x26, 56]
	mov	x1, x26
	mov	w5, 0
	mov	w8, 1
	.p2align 2
.L129:
	uxtw	x0, w5
	add	w5, w5, 1
	lsl	x2, x0, 6
	add	x2, x2, x0, lsl 3
	add	x2, x7, x2
	add	x11, x2, 503808
	uxtw	x2, w6
	lsl	x3, x2, 2
	add	x4, x2, 20
	sub	x3, x3, x2
	add	w6, w6, 1
	ldr	w2, [x11, 1352]
	add	x3, x1, x3, lsl 2
	ldr	w12, [x11, 1332]
	add	w2, w2, 1023
	and	w2, w2, -1024
	strb	w8, [x3, 472]
	str	w2, [x3, 464]
	add	w2, w23, w2
	str	w12, [x3, 468]
	str	w2, [x1, x4, lsl 2]
	str	w6, [x1, 60]
	ldr	w2, [x11, 1324]
	cmp	w2, 255
	beq	.L127
	ldr	w2, [x1, 68]
	ldr	w4, [x11, 1368]
	add	w3, w2, 1
	uxtw	x2, w2
	lsl	x0, x2, 2
	sub	x0, x0, x2
	add	x0, x1, x0, lsl 2
	str	w4, [x0, 848]
	str	w3, [x1, 68]
.L127:
	ldr	w0, [x1, 64]
	cmp	w0, w10
	bcs	.L128
	ldr	w3, [x11, 1328]
	add	x2, x27, x0, uxtw 3
	add	x2, x2, 503808
	add	w0, w0, 1
	cmp	w3, 255
	beq	.L128
	ldr	w3, [x11, 1384]
	str	w3, [x2, 3832]
	strb	w8, [x2, 3836]
	str	w0, [x1, 64]
.L128:
	ldr	w0, [x9, 800]
	cmp	w5, w0
	bcc	.L129
.L130:
	ldr	x3, [x24, 104]
	mov	x2, 1232
	mov	x1, x22
	mov	x0, x21
	blr	x3
	ldr	x1, [x20, w19, sxtw 3]
	mov	w3, 1
	ldr	x2, [x24, 32]
	mov	w0, 8
	add	x1, x1, 507904
	str	w3, [x1, 804]
	blr	x2
	mov	w1, 0
	b	.L112
	.p2align 3
.L148:
	add	x2, x0, 1024
	mov	w1, -1
	stp	wzr, wzr, [x2, 216]
	stp	w1, w1, [x2, 224]
	b	.L114
	.p2align 3
.L155:
	ldr	x1, .LC66
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	mov	w1, 30
	mov	w2, w1
	add	x0, x0, 503808
	str	w1, [x0, 1300]
	b	.L125
	.p2align 3
.L154:
	ldr	x1, .LC64
	mov	w0, 31
	bl	dprint_vfmw
	ldr	x0, [x20, w19, sxtw 3]
	b	.L124
	.p2align 3
.L147:
	ldr	x2, .LC49
	mov	w0, 0
	ldr	x1, .LC50
	ldr	x3, .LC48
	add	x2, x2, 80
	bl	dprint_vfmw
	mov	w1, -1
	b	.L112
	.p2align 3
.L150:
	ldr	x1, .LC55
	mov	w0, 31
	bl	dprint_vfmw
	mov	w1, -1
	b	.L112
.L153:
	ldr	x2, .LC49
	mov	w0, 0
	ldr	x1, .LC50
	ldr	x3, .LC62
	add	x2, x2, 144
	bl	dprint_vfmw
	mov	w1, -1
	b	.L112
	.size	VDMHAL_V5R2C1_ArrangeMem_Normal, .-VDMHAL_V5R2C1_ArrangeMem_Normal
	.align	3
.LC48:
	.xword	.LC47
	.align	3
.LC49:
	.xword	.LANCHOR0
	.align	3
.LC50:
	.xword	.LC7
	.align	3
.LC51:
	.xword	s_pstVfmwChan
	.align	3
.LC53:
	.xword	.LC52
	.align	3
.LC55:
	.xword	.LC54
	.align	3
.LC57:
	.xword	.LC56
	.align	3
.LC59:
	.xword	.LC58
	.align	3
.LC60:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC62:
	.xword	.LC61
	.align	3
.LC64:
	.xword	.LC63
	.align	3
.LC66:
	.xword	.LC65
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ArrangeMem_Specific
	.type	VDMHAL_V5R2C1_ArrangeMem_Specific, %function
VDMHAL_V5R2C1_ArrangeMem_Specific:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	w25, w0
	mov	w22, w2
	mov	x0, x30
	mov	w24, w1
	mov	w19, w3
	mov	w21, w4
	mov	w28, w5
	mov	w20, w6
	mov	w26, w7
	ldr	x23, [x29, 144]
	bl	_mcount
	cbz	w22, .L232
	sub	w1, w21, #32
	mov	w0, 8160
	cmp	w1, w0
	bhi	.L159
	sub	w1, w28, #32
	cmp	w1, w0
	bhi	.L159
	cbz	x23, .L233
	ldr	x0, .LC74
	cmp	w20, 20
	mov	x2, 1232
	mov	w1, 0
	mov	w6, 20
	ldr	x3, [x0, 96]
	mov	x0, x23
	csel	w27, w20, w6, le
	mov	w20, 32
	blr	x3
	ldr	x1, .LC75
	add	w0, w21, 15
	asr	w0, w0, 4
	add	w4, w28, 15
	cmp	w0, 45
	asr	w4, w4, 4
	ldrb	w2, [x1]
	mov	w1, 36
	ccmp	w4, w1, 0, le
	mov	w1, 64
	cset	w3, le
	cmp	w3, wzr
	csel	w20, w20, w1, eq
	cmp	w2, 1
	csel	w20, w20, w1, ne
	cmp	w24, 16
	lsl	w1, w0, 4
	beq	.L234
	cmp	w24, 17
	beq	.L167
	mul	w20, w0, w20
	mul	w20, w20, w4
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w2, w27, w20
	cmp	w19, w2
	ble	.L165
	add	w1, w1, 255
	sub	w2, w19, w2
	and	w1, w1, -256
	add	w19, w22, 1023
	lsl	w0, w1, 4
	str	w0, [x23, 4]
	asr	w0, w0, 1
	and	w19, w19, -1024
	str	w27, [x23, 56]
	sub	w6, w19, w22
	str	w0, [x23, 8]
	asr	w0, w20, 1
	str	w0, [x23, 52]
	add	w3, w28, 31
	sub	w2, w2, w6
	and	w27, w3, -32
	tbnz	w25, #31, .L229
	ldr	x9, .LC78
	mov	w5, 0
	mov	w7, 0
	ldr	x0, [x9, w25, sxtw 3]
	ldr	w0, [x0, 1240]
	cmp	w0, 1
	beq	.L235
.L206:
	mov	w9, 0
	mov	w0, 0
	mov	w28, 0
.L170:
	stp	w0, w9, [x23, 12]
	ldr	w0, [x29, 128]
	cmp	w0, 1
	beq	.L236
	mul	w4, w27, w1
	mul	w9, w7, w5
	lsl	w0, w4, 2
	lsl	w21, w28, 2
	sub	w4, w0, w4
	lsl	w0, w9, 2
	sub	w0, w0, w9
	sub	w21, w21, w28
	asr	w0, w0, 1
	add	w0, w0, w4, asr 1
	add	w21, w0, w21, lsr 1
.L172:
	ldr	w0, [x29, 136]
	tbnz	w0, #31, .L173
	stp	w2, w6, [x29, 104]
	stp	w1, w5, [x29, 112]
	str	w7, [x29, 120]
	bl	VCTRL_GetChanWidth
	mov	w25, w0
	ldr	w0, [x29, 136]
	bl	VCTRL_GetChanHeight
	cmn	w25, #1
	ldr	w7, [x29, 120]
	ccmn	w0, #1, 4, ne
	ldp	w2, w6, [x29, 104]
	ldp	w1, w5, [x29, 112]
	beq	.L237
	ldr	w3, [x29, 128]
	add	w4, w25, 15
	and	w8, w4, -16
	add	w0, w0, 15
	cmp	w3, 1
	add	w4, w8, 255
	and	w0, w0, -16
	and	w10, w4, -256
	beq	.L238
	ldr	x4, .LC78
	ldr	w3, [x29, 136]
	ldr	x4, [x4, w3, sxtw 3]
	ldr	w4, [x4, 1240]
	cmp	w4, 1
	beq	.L177
	add	w4, w0, 126
	adds	w0, w0, 63
	csel	w4, w4, w0, mi
	mov	w9, 0
	asr	w4, w4, 6
.L178:
	mul	w4, w10, w4
	mul	w10, w7, w5
	lsl	w8, w4, 2
	sub	w4, w8, w4
	lsl	w0, w10, 2
	lsl	w4, w4, 6
	sub	w0, w0, w10
	asr	w0, w0, 1
	add	w0, w0, w4, asr 1
	add	w0, w0, w9
.L176:
	cmp	w21, w0
	ldr	w25, [x29, 136]
	bgt	.L239
.L173:
	mul	w1, w27, w1
	sub	w0, w24, #16
	cmp	w0, 1
	add	w0, w1, w28
	str	w0, [x23, 36]
	bls	.L240
	cbz	w26, .L182
	cmp	w24, wzr
	ccmp	w24, 3, 4, ne
	beq	.L180
	sdiv	w2, w2, w21
	cmp	w26, 32
	mov	w0, 32
	csel	w26, w26, w0, le
	cmp	w2, w26
	csel	w4, w2, w26, le
	str	w4, [x23, 48]
.L183:
	cbz	w4, .L181
	sub	w5, w4, #1
	mov	x2, 476
	mov	w1, 12
	ldr	w3, [x23, 60]
	add	x0, x23, 464
	umaddl	x1, w5, w1, x2
	uxtw	x2, w5
	add	x1, x23, x1
	.p2align 2
.L186:
	str	w19, [x0], 12
	add	w19, w19, w21
	cmp	x0, x1
	bne	.L186
	madd	w21, w21, w4, w6
	add	x2, x2, 21
	add	w3, w4, w3
	add	w1, w21, w22
	add	x0, x23, 80
	add	x2, x23, x2, lsl 2
	str	w3, [x23, 60]
	.p2align 2
.L188:
	str	w1, [x0], 4
	add	w1, w1, 32
	cmp	x2, x0
	bne	.L188
	ldr	w3, [x23, 56]
	add	w21, w21, w4, lsl 5
	add	w22, w21, w22
	cbz	w3, .L193
	sub	w2, w3, #1
	ldr	w6, [x23, 64]
	add	x2, x2, 27
	add	x1, x23, 208
	mov	w0, w22
	add	x2, x23, x2, lsl 3
	.p2align 2
.L192:
	str	w0, [x1], 8
	add	w0, w0, w20
	cmp	x1, x2
	bne	.L192
	add	w0, w3, w6
	str	w0, [x23, 64]
.L193:
	madd	w20, w3, w20, w21
	str	w20, [x23]
	tbnz	w25, #31, .L191
	ldr	x0, .LC78
	ldr	x0, [x0, w25, sxtw 3]
	cbz	x0, .L191
	add	w0, w20, w22
	cbz	w4, .L191
	mov	w3, 12
	mov	x2, 860
	add	x1, x23, 848
	umaddl	x2, w5, w3, x2
	add	x2, x23, x2
	.p2align 2
.L194:
	str	w0, [x1], 12
	add	w0, w0, 1024
	cmp	x2, x1
	bne	.L194
.L191:
	add	w20, w20, w4, lsl 10
	mov	w0, 0
	str	w20, [x23]
.L225:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L240:
	lsl	w0, w1, 2
	sub	w1, w0, w1
	lsl	w0, w28, 2
	sub	w0, w0, w28
	lsr	w28, w28, 1
	lsr	w0, w0, 1
	madd	w7, w7, w5, w28
	add	w0, w0, w1, asr 1
	lsl	w5, w5, 4
	stp	w0, w7, [x23, 28]
	str	w5, [x23, 20]
	cbnz	w26, .L180
.L182:
	str	wzr, [x23, 48]
.L181:
	ldr	x2, .LC69
	ldr	x3, .LC84
.L230:
	ldr	x1, .LC70
	add	x2, x2, 184
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.p2align 3
.L180:
	cmp	w26, 32
	mov	w0, 32
	sdiv	w2, w2, w21
	csel	w26, w26, w0, le
	cmp	w26, w2
	csel	w4, w26, w2, le
	str	w4, [x23, 48]
	b	.L183
	.p2align 3
.L234:
	mul	w20, w4, w1
	add	w20, w20, 143
	and	w20, w20, -128
	mul	w2, w27, w20
	cmp	w19, w2
	ble	.L165
	sub	w2, w19, w2
	add	w19, w22, 1023
	and	w19, w19, -1024
	asr	w0, w20, 1
	stp	w0, w27, [x23, 52]
	sub	w6, w19, w22
	add	w1, w21, 255
	sub	w2, w2, w6
	and	w1, w1, -256
	mov	w27, w28
	tbnz	w25, #31, .L198
	ldr	x9, .LC78
	stp	w2, w6, [x29, 104]
	stp	w1, w4, [x29, 112]
	ldr	x0, [x9, w25, sxtw 3]
	str	x9, [x29, 120]
	add	x0, x0, 507904
	add	x0, x0, 1408
	bl	IsMain10Profile
	ldp	w2, w6, [x29, 104]
	ldp	w1, w4, [x29, 112]
	ldr	x9, [x29, 120]
	cbz	w0, .L203
	cmp	w1, wzr
	add	w5, w1, 3
	csel	w5, w5, w1, lt
	add	w7, w28, 31
	asr	w5, w5, 2
	and	w7, w7, -32
	mov	w27, w28
	b	.L169
	.p2align 3
.L236:
	lsl	w0, w4, 4
	mul	w0, w0, w1
	lsl	w21, w0, 2
	sub	w21, w21, w0
	b	.L172
.L241:
	mov	w20, 128
	movk	w20, 0x24, lsl 16
.L198:
	lsl	w0, w1, 4
	str	w0, [x23, 4]
	asr	w0, w0, 1
	str	w0, [x23, 8]
.L229:
	mov	w9, 0
	mov	w0, 0
	mov	w5, 0
	mov	w7, 0
	mov	w28, 0
	b	.L170
	.p2align 3
.L167:
	lsl	w0, w27, 14
	add	w0, w0, w27, lsl 11
	add	w0, w0, w27
	lsl	w0, w0, 7
	cmp	w19, w0
	ble	.L165
	sub	w0, w19, w0
	mov	w1, 64
	add	w19, w22, 1023
	movk	w1, 0x12, lsl 16
	and	w19, w19, -1024
	add	w3, w28, 63
	stp	w1, w27, [x23, 52]
	sub	w6, w19, w22
	add	w1, w21, 255
	sub	w2, w0, w6
	and	w1, w1, -256
	and	w27, w3, -64
	tbnz	w25, #31, .L241
	ldr	x9, .LC78
	ldr	x0, [x9, w25, sxtw 3]
	ldr	w0, [x0, 1548]
	cmp	w0, 8
	ble	.L204
	cmp	w1, wzr
	add	w5, w1, 3
	csel	w5, w5, w1, lt
	add	w7, w27, 63
	mov	w20, 128
	asr	w5, w5, 2
	and	w7, w7, -64
	movk	w20, 0x24, lsl 16
.L169:
	lsl	w0, w1, 4
	str	w0, [x23, 4]
	asr	w0, w0, 1
	str	w0, [x23, 8]
	ldr	x0, [x9, w25, sxtw 3]
	ldr	w0, [x0, 1240]
	cmp	w0, 1
	bne	.L206
.L235:
	cmp	w24, 17
	mov	w0, 1920
	ccmp	w21, w0, 0, ne
	ble	.L206
	adds	w0, w21, 2047
	add	w21, w21, 4094
	csel	w0, w21, w0, mi
	and	w9, w0, -2048
	cmp	w9, wzr
	add	w0, w9, 127
	csel	w0, w0, w9, lt
	add	w9, w28, 126
	adds	w28, w28, 63
	asr	w0, w0, 7
	csel	w28, w9, w28, mi
	asr	w28, w28, 6
	lsl	w28, w28, 5
	mul	w28, w28, w0
	mov	w9, w28
	b	.L170
	.p2align 3
.L238:
	mul	w0, w0, w10
	lsl	w4, w0, 2
	sub	w0, w4, w0
	b	.L176
	.p2align 3
.L177:
	adds	w9, w0, 63
	add	w4, w0, 126
	csel	w4, w4, w9, mi
	adds	w0, w8, 2047
	add	w8, w8, 4094
	asr	w4, w4, 6
	csel	w8, w8, w0, mi
	and	w8, w8, -2048
	add	w9, w8, 127
	cmp	w8, wzr
	csel	w8, w9, w8, lt
	lsl	w9, w4, 2
	sub	w9, w9, w4
	asr	w8, w8, 7
	lsl	w9, w9, 5
	mul	w9, w8, w9
	lsr	w9, w9, 1
	b	.L178
.L203:
	mov	w27, w28
	mov	w7, 0
	mov	w5, 0
	b	.L169
.L204:
	mov	w20, 128
	mov	w7, 0
	movk	w20, 0x24, lsl 16
	mov	w5, 0
	b	.L169
.L159:
	ldr	x2, .LC69
	ldr	x3, .LC71
	b	.L230
.L165:
	ldr	x2, .LC69
	ldr	x3, .LC77
	b	.L230
.L232:
	ldr	x2, .LC69
	ldr	x3, .LC68
	b	.L230
.L237:
	ldr	x1, .LC80
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L225
.L239:
	ldr	x2, .LC69
	ldr	x3, .LC82
	b	.L230
.L233:
	ldr	x2, .LC69
	ldr	x3, .LC73
	b	.L230
	.size	VDMHAL_V5R2C1_ArrangeMem_Specific, .-VDMHAL_V5R2C1_ArrangeMem_Specific
	.align	3
.LC68:
	.xword	.LC67
	.align	3
.LC69:
	.xword	.LANCHOR0
	.align	3
.LC70:
	.xword	.LC7
	.align	3
.LC71:
	.xword	.LC23
	.align	3
.LC73:
	.xword	.LC72
	.align	3
.LC74:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC75:
	.xword	g_not_direct_8x8_inference_flag
	.align	3
.LC77:
	.xword	.LC76
	.align	3
.LC78:
	.xword	s_pstVfmwChan
	.align	3
.LC80:
	.xword	.LC79
	.align	3
.LC82:
	.xword	.LC81
	.align	3
.LC84:
	.xword	.LC83
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ArrangeMem
	.type	VDMHAL_V5R2C1_ArrangeMem, %function
VDMHAL_V5R2C1_ArrangeMem:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	stp	x19, x20, [sp, 48]
	stp	x21, x22, [sp, 64]
	stp	x23, x24, [sp, 80]
	stp	x25, x26, [sp, 96]
	mov	w24, w0
	mov	x0, x30
	mov	w19, w7
	mov	w25, w1
	mov	w20, w2
	mov	w21, w3
	mov	w22, w4
	mov	w26, w5
	mov	w23, w6
	bl	_mcount
	cmn	w19, #2
	beq	.L246
	tbnz	w19, #31, .L247
	mov	w0, w19
	bl	VCTRL_GetVidStd
	mov	w1, w0
	ldr	x0, .LC85
	ldr	x0, [x0, w19, sxtw 3]
	ldr	w0, [x0, 1488]
	cmp	w0, 1
	beq	.L249
.L244:
	ldr	x0, [x29, 80]
	mov	w7, w26
	str	x0, [sp, 16]
	mov	w6, w22
	mov	w5, w21
	mov	w4, w20
	mov	w3, w25
	mov	w2, w24
	str	w23, [sp]
	mov	w0, w19
	str	w19, [sp, 8]
	bl	VDMHAL_V5R2C1_ArrangeMem_Specific
.L248:
	add	sp, x29, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L247:
	mov	w1, 21
	b	.L244
	.p2align 3
.L246:
	mov	w1, 16
	b	.L244
	.p2align 3
.L249:
	ldr	x6, [x29, 80]
	mov	w5, w23
	mov	w4, w22
	mov	w3, w21
	mov	w2, w20
	mov	w0, w19
	bl	VDMHAL_V5R2C1_ArrangeMem_Normal
	b	.L248
	.size	VDMHAL_V5R2C1_ArrangeMem, .-VDMHAL_V5R2C1_ArrangeMem
	.align	3
.LC85:
	.xword	s_pstVfmwChan
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ResetVdm
	.type	VDMHAL_V5R2C1_ResetVdm, %function
VDMHAL_V5R2C1_ResetVdm:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w21, w0
	mov	x0, x30
	bl	_mcount
	cmp	w21, wzr
	ble	.L251
	ldr	x2, .LC86
	mov	w4, 0
	ldr	x1, .LC88
	mov	w3, w21
	add	x2, x2, 224
	mov	w0, 0
	bl	dprint_vfmw
.L250:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L251:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L263
	sxtw	x22, w21
	ldr	x24, .LC91
	lsl	x0, x22, 6
	ldr	x20, .LC92
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	ldr	x2, [x20]
	add	x0, x0, x1, lsl 2
	ldr	x0, [x24, x0]
	ldr	w25, [x0, 36]
	ldr	w23, [x2, 120]
	tbz	x23, 0, .L250
	ldr	x26, .LC93
	mov	w0, 2
	bfi	w23, w0, 8, 2
	str	w23, [x2, 120]
	mov	w19, 0
	orr	w23, w23, 64
	ldr	x0, [x26, 224]
	blr	x0
	ldr	x0, [x20]
	str	w23, [x0, 120]
	b	.L255
	.p2align 3
.L264:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L256
.L255:
	ldr	x1, [x26, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 2, .L264
	cmp	w19, 999
	bgt	.L256
	ldr	x2, .LC86
	mov	w3, w21
	ldr	x1, .LC97
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
.L258:
	ldr	x0, [x20]
	and	w23, w23, -65
	str	w23, [x0, 120]
	and	w23, w23, -769
	ldr	x0, [x26, 224]
	blr	x0
	lsl	x0, x22, 6
	ldr	x1, [x20]
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x22, x0, x22
	str	w23, [x1, 120]
	add	x22, x0, x22, lsl 2
	ldr	x0, [x24, x22]
	str	w25, [x0, 36]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L256:
	ldr	x2, .LC86
	mov	w3, w21
	ldr	x1, .LC95
	mov	w0, 0
	add	x2, x2, 224
	bl	dprint_vfmw
	b	.L258
.L263:
	ldr	x1, .LC90
	mov	x2, 0
	bl	dprint_vfmw
	b	.L250
	.size	VDMHAL_V5R2C1_ResetVdm, .-VDMHAL_V5R2C1_ResetVdm
	.align	3
.LC86:
	.xword	.LANCHOR0
	.align	3
.LC88:
	.xword	.LC87
	.align	3
.LC90:
	.xword	.LC89
	.align	3
.LC91:
	.xword	g_HwMem
	.align	3
.LC92:
	.xword	g_pstRegCrg
	.align	3
.LC93:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC95:
	.xword	.LC94
	.align	3
.LC97:
	.xword	.LC96
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.type	VDMHAL_V5R2C1_SetSmmuPageTableAddr, %function
VDMHAL_V5R2C1_SetSmmuPageTableAddr:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC98
	ldr	x3, [x0, 376]
	cbz	x3, .L265
	add	x2, x29, 60
	add	x1, x29, 56
	add	x0, x29, 52
	blr	x3
	cbnz	w19, .L267
	ldr	x0, .LC99
	ldp	w3, w2, [x29, 52]
	ldr	w1, [x29, 60]
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w3, [x0, 524]
	str	w2, [x0, 772]
	str	w1, [x0, 776]
.L265:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L267:
	ldr	x20, .LC100
	mov	w3, w19
	ldr	x21, .LC102
	mov	w4, 1
	add	x20, x20, 248
	mov	w0, 32
	mov	x1, x21
	mov	x2, x20
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x20
	mov	x1, x21
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w19
	mov	x2, x20
	mov	x1, x21
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
	.size	VDMHAL_V5R2C1_SetSmmuPageTableAddr, .-VDMHAL_V5R2C1_SetSmmuPageTableAddr
	.align	3
.LC98:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC99:
	.xword	g_HwMem
	.align	3
.LC100:
	.xword	.LANCHOR0
	.align	3
.LC102:
	.xword	.LC101
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_EnableSmmu
	.type	VDMHAL_V5R2C1_EnableSmmu, %function
VDMHAL_V5R2C1_EnableSmmu:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x0, .LC104
	mov	w1, 8
	movk	w1, 0x3, lsl 16
	ldr	x0, [x0]
	add	x0, x0, 61440
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_EnableSmmu, .-VDMHAL_V5R2C1_EnableSmmu
	.align	3
.LC104:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GlbResetX
	.type	VDMHAL_V5R2C1_GlbResetX, %function
VDMHAL_V5R2C1_GlbResetX:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	w23, w0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L284
	ldr	x20, .LC108
	ldr	x0, [x20]
	ldr	w22, [x0, 120]
	tbnz	x22, 0, .L285
.L272:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L285:
	ldr	x21, .LC109
	mov	w1, 2
	bfi	w22, w1, 8, 2
	str	w22, [x0, 120]
	mov	w19, 0
	orr	w22, w22, 16
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	str	w22, [x0, 120]
	b	.L276
	.p2align 3
.L286:
	add	w19, w19, 1
	cmp	w19, 1000
	beq	.L277
.L276:
	ldr	x1, [x21, 232]
	mov	x0, 30
	blr	x1
	ldr	x0, [x20]
	ldr	w0, [x0, 372]
	tbz	x0, 0, .L286
	cmp	w19, 999
	bgt	.L277
	ldr	x2, .LC105
	mov	w3, w23
	ldr	x1, .LC113
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
.L279:
	ldr	x0, [x20]
	and	w22, w22, -17
	str	w22, [x0, 120]
	and	w22, w22, -769
	ldr	x0, [x21, 224]
	blr	x0
	ldr	x0, [x20]
	str	w22, [x0, 120]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L277:
	ldr	x2, .LC105
	mov	w3, w23
	ldr	x1, .LC111
	mov	w0, 0
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L279
.L284:
	ldr	x2, .LC105
	mov	w3, -121438208
	ldr	x1, .LC107
	add	x2, x2, 288
	bl	dprint_vfmw
	b	.L272
	.size	VDMHAL_V5R2C1_GlbResetX, .-VDMHAL_V5R2C1_GlbResetX
	.align	3
.LC105:
	.xword	.LANCHOR0
	.align	3
.LC107:
	.xword	.LC106
	.align	3
.LC108:
	.xword	g_pstRegCrg
	.align	3
.LC109:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC111:
	.xword	.LC110
	.align	3
.LC113:
	.xword	.LC112
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GlbReset
	.type	VDMHAL_V5R2C1_GlbReset, %function
VDMHAL_V5R2C1_GlbReset:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L290
	mov	w0, 0
	bl	VDMHAL_V5R2C1_GlbResetX
.L287:
	ldp	x29, x30, [sp], 16
	ret
.L290:
	ldr	x2, .LC114
	mov	w3, -121438208
	ldr	x1, .LC115
	add	x2, x2, 312
	bl	dprint_vfmw
	b	.L287
	.size	VDMHAL_V5R2C1_GlbReset, .-VDMHAL_V5R2C1_GlbReset
	.align	3
.LC114:
	.xword	.LANCHOR0
	.align	3
.LC115:
	.xword	.LC106
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ClearIntState
	.type	VDMHAL_V5R2C1_ClearIntState, %function
VDMHAL_V5R2C1_ClearIntState:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x19, w0
	mov	x0, x30
	mov	x20, x19
	bl	_mcount
	ldr	x21, .LC117
	ldr	x0, .LC116
	add	x1, x21, x19, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x0, [x0, x1, lsl 3]
	cbz	x0, .L301
	ldr	w22, [x0, 1272]
.L292:
	cmp	w20, wzr
	bgt	.L303
	lsl	x0, x19, 6
	ldr	x23, .LC120
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x23, x20]
	cbz	x0, .L304
.L295:
	cmp	w22, 1
	bne	.L302
	add	x19, x21, x19, lsl 6
	ldr	w1, [x19, 44]
	cmp	w1, 1
	beq	.L302
	ldr	w2, [x0, 28]
	cmp	w1, 2
	beq	.L305
	cmp	w1, 3
	bne	.L291
	mov	w1, -15
	str	w1, [x0, 32]
	b	.L291
	.p2align 3
.L303:
	ldr	x2, .LC118
	mov	w4, 0
	ldr	x1, .LC119
	mov	w3, w20
	add	x2, x2, 336
	mov	w0, 0
	bl	dprint_vfmw
.L291:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L302:
	mov	w1, -1
	str	w1, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L301:
	mov	w22, 0
	b	.L292
	.p2align 3
.L304:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L296
	str	x0, [x23, x20]
	b	.L295
	.p2align 3
.L305:
	mov	w1, -12
	str	w1, [x0, 32]
	b	.L291
.L296:
	ldr	x1, .LC122
	mov	w0, 0
	bl	dprint_vfmw
	b	.L291
	.size	VDMHAL_V5R2C1_ClearIntState, .-VDMHAL_V5R2C1_ClearIntState
	.align	3
.LC116:
	.xword	s_pstVfmwChan
	.align	3
.LC117:
	.xword	g_VdmDrvParam
	.align	3
.LC118:
	.xword	.LANCHOR0
	.align	3
.LC119:
	.xword	.LC87
	.align	3
.LC120:
	.xword	g_HwMem
	.align	3
.LC122:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ClearMMUIntState
	.type	VDMHAL_V5R2C1_ClearMMUIntState, %function
VDMHAL_V5R2C1_ClearMMUIntState:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L311
	lsl	x3, x19, 6
	ldr	x20, .LC125
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L312
.L309:
	add	x0, x0, 61440
	mov	w1, 7
	str	w1, [x0, 44]
.L306:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L311:
	ldr	x2, .LC123
	mov	w3, w19
	ldr	x1, .LC124
	mov	w4, 0
	add	x2, x2, 368
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L312:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L310
	str	x0, [x20, x19]
	b	.L309
.L310:
	ldr	x1, .LC126
	mov	w0, 0
	bl	dprint_vfmw
	b	.L306
	.size	VDMHAL_V5R2C1_ClearMMUIntState, .-VDMHAL_V5R2C1_ClearMMUIntState
	.align	3
.LC123:
	.xword	.LANCHOR0
	.align	3
.LC124:
	.xword	.LC87
	.align	3
.LC125:
	.xword	g_HwMem
	.align	3
.LC126:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_MaskInt
	.type	VDMHAL_V5R2C1_MaskInt, %function
VDMHAL_V5R2C1_MaskInt:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	bgt	.L318
	lsl	x3, x19, 6
	ldr	x20, .LC129
	sub	x3, x3, x19
	lsl	x3, x3, 2
	sub	x19, x3, x19
	add	x19, x3, x19, lsl 2
	ldr	x0, [x20, x19]
	cbz	x0, .L319
.L316:
	mov	w1, -1
	str	w1, [x0, 36]
.L313:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L318:
	ldr	x2, .LC127
	mov	w3, w19
	ldr	x1, .LC128
	mov	w4, 0
	add	x2, x2, 400
	mov	w0, 0
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L319:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L317
	str	x0, [x20, x19]
	b	.L316
.L317:
	ldr	x1, .LC130
	mov	w0, 0
	bl	dprint_vfmw
	b	.L313
	.size	VDMHAL_V5R2C1_MaskInt, .-VDMHAL_V5R2C1_MaskInt
	.align	3
.LC127:
	.xword	.LANCHOR0
	.align	3
.LC128:
	.xword	.LC87
	.align	3
.LC129:
	.xword	g_HwMem
	.align	3
.LC130:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetIntMaskCfg
	.type	VDMHAL_V5R2C1_GetIntMaskCfg, %function
VDMHAL_V5R2C1_GetIntMaskCfg:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, 1
	mov	w1, -6
	mov	w0, -2
	ldr	x19, [sp, 16]
	csel	w0, w1, w0, eq
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R2C1_GetIntMaskCfg, .-VDMHAL_V5R2C1_GetIntMaskCfg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_EnableInt
	.type	VDMHAL_V5R2C1_EnableInt, %function
VDMHAL_V5R2C1_EnableInt:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	ldr	x1, .LC132
	sxtw	x0, w19
	ldr	x2, .LC131
	add	x1, x1, x0, lsl 6
	ldrsw	x1, [x1, 8]
	ldr	x1, [x2, x1, lsl 3]
	cbz	x1, .L331
	ldr	w20, [x1, 1272]
.L324:
	cmp	w19, wzr
	bgt	.L332
	lsl	x19, x0, 6
	ldr	x21, .LC135
	sub	x19, x19, x0
	lsl	x19, x19, 2
	sub	x0, x19, x0
	add	x19, x19, x0, lsl 2
	ldr	x0, [x21, x19]
	cbz	x0, .L333
.L327:
	mov	w1, -6
	mov	w2, -2
	cmp	w20, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 36]
.L323:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L332:
	ldr	x2, .LC133
	mov	w3, w19
	ldr	x1, .LC134
	mov	w4, 0
	add	x2, x2, 424
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L331:
	mov	w20, 0
	b	.L324
	.p2align 3
.L333:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L328
	str	x0, [x21, x19]
	b	.L327
.L328:
	ldr	x1, .LC136
	mov	w0, 0
	bl	dprint_vfmw
	b	.L323
	.size	VDMHAL_V5R2C1_EnableInt, .-VDMHAL_V5R2C1_EnableInt
	.align	3
.LC131:
	.xword	s_pstVfmwChan
	.align	3
.LC132:
	.xword	g_VdmDrvParam
	.align	3
.LC133:
	.xword	.LANCHOR0
	.align	3
.LC134:
	.xword	.LC87
	.align	3
.LC135:
	.xword	g_HwMem
	.align	3
.LC136:
	.xword	.LC121
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CheckReg
	.type	VDMHAL_V5R2C1_CheckReg, %function
VDMHAL_V5R2C1_CheckReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	bgt	.L351
	lsl	x0, x19, 6
	ldr	x21, .LC140
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	ldr	x0, [x21, x20]
	cbz	x0, .L352
.L337:
	sub	w0, w22, #1
	cmp	w0, 6
	bls	.L353
	ldr	x2, .LC137
	mov	w3, w22
	ldr	x1, .LC144
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
.L350:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L353:
	ldr	x1, .LC145
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx344
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx344:
	.section	.rodata
	.align	0
	.align	2
.L344:
	.byte	(.L348 - .Lrtx344) / 4
	.byte	(.L345 - .Lrtx344) / 4
	.byte	(.L346 - .Lrtx344) / 4
	.byte	(.L347 - .Lrtx344) / 4
	.byte	(.L349 - .Lrtx344) / 4
	.byte	(.L339 - .Lrtx344) / 4
	.byte	(.L341 - .Lrtx344) / 4
	.text
	.p2align 3
.L349:
	mov	x1, 61480
.L343:
	lsl	x0, x19, 6
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x21, x19]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	w0, [x0, x1]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L348:
	mov	x1, 28
	b	.L343
	.p2align 3
.L347:
	mov	x1, 40
	b	.L343
	.p2align 3
.L346:
	mov	x1, 36
	b	.L343
	.p2align 3
.L345:
	mov	x1, 32
	b	.L343
	.p2align 3
.L341:
	mov	x1, 62272
	b	.L343
	.p2align 3
.L339:
	mov	x1, 62304
	b	.L343
	.p2align 3
.L352:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L338
	str	x0, [x21, x20]
	b	.L337
	.p2align 3
.L351:
	ldr	x2, .LC137
	mov	w3, w19
	ldr	x1, .LC139
	mov	w0, 0
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, -1
	b	.L350
.L338:
	ldr	x2, .LC137
	mov	w0, 0
	ldr	x1, .LC142
	add	x2, x2, 448
	bl	dprint_vfmw
	mov	w0, 0
	b	.L350
	.size	VDMHAL_V5R2C1_CheckReg, .-VDMHAL_V5R2C1_CheckReg
	.align	3
.LC137:
	.xword	.LANCHOR0
	.align	3
.LC139:
	.xword	.LC138
	.align	3
.LC140:
	.xword	g_HwMem
	.align	3
.LC142:
	.xword	.LC141
	.align	3
.LC144:
	.xword	.LC143
	.align	3
.LC145:
	.xword	.L344
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ReadMMUMask
	.type	VDMHAL_V5R2C1_ReadMMUMask, %function
VDMHAL_V5R2C1_ReadMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	sxtw	x19, w0
	mov	x0, x30
	bl	_mcount
	cmp	w19, wzr
	ble	.L357
	ldr	x2, .LC147
	mov	w3, w19
	ldr	x1, .LC149
	mov	w4, 1
	add	x2, x2, 472
	mov	w0, 32
	bl	dprint_vfmw
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L357:
	lsl	x0, x19, 6
	ldr	x1, .LC146
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	ldr	x19, [sp, 16]
	add	x0, x0, 61440
	ldp	x29, x30, [sp], 32
	ldr	w0, [x0, 32]
	ret
	.size	VDMHAL_V5R2C1_ReadMMUMask, .-VDMHAL_V5R2C1_ReadMMUMask
	.align	3
.LC146:
	.xword	g_HwMem
	.align	3
.LC147:
	.xword	.LANCHOR0
	.align	3
.LC149:
	.xword	.LC148
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_WriteMMUMask
	.type	VDMHAL_V5R2C1_WriteMMUMask, %function
VDMHAL_V5R2C1_WriteMMUMask:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	mov	x0, x30
	sxtw	x19, w1
	bl	_mcount
	cmp	w19, wzr
	ble	.L361
	ldr	x2, .LC151
	mov	w3, w19
	ldr	x1, .LC152
	mov	w4, 1
	add	x2, x2, 504
	mov	w0, 32
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L361:
	lsl	x0, x19, 6
	ldr	x1, .LC150
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	add	x0, x0, 61440
	str	w20, [x0, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R2C1_WriteMMUMask, .-VDMHAL_V5R2C1_WriteMMUMask
	.align	3
.LC150:
	.xword	g_HwMem
	.align	3
.LC151:
	.xword	.LANCHOR0
	.align	3
.LC152:
	.xword	.LC101
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_PrepareDec
	.type	VDMHAL_V5R2C1_PrepareDec, %function
VDMHAL_V5R2C1_PrepareDec:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	w20, w0
	mov	x22, x1
	mov	x0, x30
	mov	w21, w2
	mov	x19, x3
	bl	_mcount
	cbz	x22, .L381
	cmp	w21, wzr
	bgt	.L382
	cmp	w20, 6
	mov	w2, 0
	cset	w1, eq
	mov	w0, 0
	mov	x3, x19
	bl	SCD_ConfigReg
	mov	x3, x19
	mov	w2, 0
	mov	w1, 1
	mov	w0, 8
	bl	SCD_ConfigReg
	cmp	w20, 17
	bls	.L383
.L380:
	mov	w0, -1
	b	.L364
	.p2align 3
.L383:
	ldr	x0, .LC157
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx367
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx367:
	.section	.rodata
	.align	0
	.align	2
.L367:
	.byte	(.L377 - .Lrtx367) / 4
	.byte	(.L368 - .Lrtx367) / 4
	.byte	(.L369 - .Lrtx367) / 4
	.byte	(.L370 - .Lrtx367) / 4
	.byte	(.L380 - .Lrtx367) / 4
	.byte	(.L371 - .Lrtx367) / 4
	.byte	(.L372 - .Lrtx367) / 4
	.byte	(.L380 - .Lrtx367) / 4
	.byte	(.L373 - .Lrtx367) / 4
	.byte	(.L374 - .Lrtx367) / 4
	.byte	(.L375 - .Lrtx367) / 4
	.byte	(.L375 - .Lrtx367) / 4
	.byte	(.L375 - .Lrtx367) / 4
	.byte	(.L376 - .Lrtx367) / 4
	.byte	(.L380 - .Lrtx367) / 4
	.byte	(.L377 - .Lrtx367) / 4
	.byte	(.L378 - .Lrtx367) / 4
	.byte	(.L379 - .Lrtx367) / 4
	.text
	.p2align 3
.L377:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	H264HAL_V5R2C1_StartDec
.L364:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L378:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	HEVCHAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L376:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP8HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L375:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP6HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L374:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV9HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L373:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	RV8HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L372:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	AVSHAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L371:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	DIVX3HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L370:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP2HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L369:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	MP4HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L368:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VC1HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L379:
	mov	x2, x19
	mov	w1, w21
	mov	x0, x22
	bl	VP9HAL_V5R2C1_StartDec
	b	.L364
	.p2align 3
.L382:
	ldr	x2, .LC153
	mov	w3, w21
	ldr	x1, .LC156
	mov	w4, 0
	add	x2, x2, 536
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L381:
	ldr	x2, .LC153
	mov	x3, 0
	ldr	x1, .LC155
	mov	w0, 0
	add	x2, x2, 536
	bl	dprint_vfmw
	mov	w0, -1
	b	.L364
	.size	VDMHAL_V5R2C1_PrepareDec, .-VDMHAL_V5R2C1_PrepareDec
	.align	3
.LC153:
	.xword	.LANCHOR0
	.align	3
.LC155:
	.xword	.LC154
	.align	3
.LC156:
	.xword	.LC87
	.align	3
.LC157:
	.xword	.L367
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdmReady
	.type	VDMHAL_V5R2C1_IsVdmReady, %function
VDMHAL_V5R2C1_IsVdmReady:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC158
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L389
	cmp	w19, wzr
	ble	.L390
	ldr	x2, .LC161
	mov	w4, 1
	ldr	x1, .LC163
	mov	w3, w19
	add	x2, x2, 568
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 0
.L386:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L390:
	ldr	w0, [x0, 28]
	ldr	x19, [sp, 16]
	ubfx	x0, x0, 17, 1
	ldp	x29, x30, [sp], 32
	ret
.L389:
	ldr	x2, .LC161
	ldr	x3, .LC160
	ldr	x1, .LC162
	add	x2, x2, 568
	bl	dprint_vfmw
	mov	w0, -1
	b	.L386
	.size	VDMHAL_V5R2C1_IsVdmReady, .-VDMHAL_V5R2C1_IsVdmReady
	.align	3
.LC158:
	.xword	g_HwMem
	.align	3
.LC160:
	.xword	.LC159
	.align	3
.LC161:
	.xword	.LANCHOR0
	.align	3
.LC162:
	.xword	.LC7
	.align	3
.LC163:
	.xword	.LC148
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdmRun
	.type	VDMHAL_V5R2C1_IsVdmRun, %function
VDMHAL_V5R2C1_IsVdmRun:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	bl	_mcount
	sxtw	x0, w19
	ldr	x2, .LC164
	lsl	x1, x0, 6
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x2, x0]
	cbz	x0, .L396
	cmp	w19, wzr
	ble	.L397
	ldr	x2, .LC167
	mov	w4, 1
	ldr	x1, .LC168
	mov	w3, w19
	add	x2, x2, 600
	mov	w0, 32
	bl	dprint_vfmw
	mov	w0, 1
.L393:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L397:
	ldr	w0, [x0, 40]
	ldr	x19, [sp, 16]
	cmp	w0, 1
	cset	w0, ne
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L396:
	ldr	x1, .LC166
	bl	dprint_vfmw
	mov	w0, 0
	b	.L393
	.size	VDMHAL_V5R2C1_IsVdmRun, .-VDMHAL_V5R2C1_IsVdmRun
	.align	3
.LC164:
	.xword	g_HwMem
	.align	3
.LC166:
	.xword	.LC165
	.align	3
.LC167:
	.xword	.LANCHOR0
	.align	3
.LC168:
	.xword	.LC148
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdhDecOver
	.type	VDMHAL_V5R2C1_IsVdhDecOver, %function
VDMHAL_V5R2C1_IsVdhDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC169
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L406
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	w19, 2
	beq	.L403
	cmp	w19, 3
	beq	.L403
	cmp	w19, 1
	ubfx	x0, x0, 17, 1
	beq	.L400
	ldr	x2, .LC171
	mov	w3, w19
	ldr	x1, .LC173
	mov	w0, 0
	add	x2, x2, 624
	bl	dprint_vfmw
	mov	w0, 0
.L400:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L403:
	and	w0, w0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L406:
	ldr	x2, .LC171
	ldr	x3, .LC170
	ldr	x1, .LC172
	add	x2, x2, 624
	bl	dprint_vfmw
	mov	w0, -1
	b	.L400
	.size	VDMHAL_V5R2C1_IsVdhDecOver, .-VDMHAL_V5R2C1_IsVdhDecOver
	.align	3
.LC169:
	.xword	g_HwMem
	.align	3
.LC170:
	.xword	.LC159
	.align	3
.LC171:
	.xword	.LANCHOR0
	.align	3
.LC172:
	.xword	.LC7
	.align	3
.LC173:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_IsVdhPartDecOver
	.type	VDMHAL_V5R2C1_IsVdhPartDecOver, %function
VDMHAL_V5R2C1_IsVdhPartDecOver:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	sxtw	x0, w20
	ldr	x1, .LC174
	lsl	x2, x0, 6
	sub	x2, x2, x0
	lsl	x2, x2, 2
	sub	x0, x2, x0
	add	x0, x2, x0, lsl 2
	ldr	x0, [x1, x0]
	cbz	x0, .L415
	mov	w1, w20
	mov	w0, w19
	bl	VDMHAL_V5R2C1_CheckReg
	cmp	w19, 1
	beq	.L411
	cmp	w19, 2
	ubfx	x0, x0, 2, 1
	bne	.L416
.L409:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L416:
	ldr	x2, .LC176
	mov	w3, w19
	ldr	x1, .LC178
	mov	w0, 0
	add	x2, x2, 656
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L411:
	ubfx	x0, x0, 19, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L415:
	ldr	x2, .LC176
	ldr	x3, .LC175
	ldr	x1, .LC177
	add	x2, x2, 656
	bl	dprint_vfmw
	mov	w0, -1
	b	.L409
	.size	VDMHAL_V5R2C1_IsVdhPartDecOver, .-VDMHAL_V5R2C1_IsVdhPartDecOver
	.align	3
.LC174:
	.xword	g_HwMem
	.align	3
.LC175:
	.xword	.LC159
	.align	3
.LC176:
	.xword	.LANCHOR0
	.align	3
.LC177:
	.xword	.LC7
	.align	3
.LC178:
	.xword	.LC143
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_UpdateHardwareInfo
	.type	VDMHAL_V5R2C1_UpdateHardwareInfo, %function
VDMHAL_V5R2C1_UpdateHardwareInfo:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	w22, w0
	mov	x0, x30
	bl	_mcount
	cmp	w22, wzr
	bgt	.L418
	ldr	x4, .LC179
	add	x0, x4, 4
	add	x4, x4, 128
	ldr	w1, [x4, -128]
	cmp	w1, 1
	bne	.L422
	b	.L433
	.p2align 3
.L443:
	cmp	x0, x4
	beq	.L442
.L422:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L443
.L433:
	mov	w19, w1
.L419:
	sxtw	x20, w22
	ldr	x24, .LC184
	lsl	x0, x20, 6
	sub	x0, x0, x20
	lsl	x0, x0, 2
	sub	x21, x0, x20
	add	x21, x0, x21, lsl 2
	ldr	x1, [x24, x21]
	cbz	x1, .L444
.L423:
	lsl	x0, x20, 2
	ldr	x21, .LC186
	sub	x4, x0, x20
	ldr	x2, .LC190
	lsl	x0, x4, 4
	ldr	w3, [x1, 12]
	sub	x0, x0, x4
	lsl	x5, x20, 6
	lsl	x0, x0, 2
	add	x4, x21, x0
	str	w3, [x21, x0]
	add	x0, x2, x5
	ldr	w3, [x1, 28]
	ldr	w0, [x0, 56]
	str	w3, [x4, 4]
	cmp	w0, 1
	beq	.L445
	cmp	w19, 1
	beq	.L446
	ldr	w5, [x1, 4096]
	ldr	w3, [x1, 4108]
	ldr	w2, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w2, w0, [x4, 8]
	stp	w5, w3, [x4, 16]
	cbz	w19, .L447
.L428:
	mov	w0, 180
	add	x4, x1, 32768
	add	x1, x4, 256
	smull	x2, w22, w0
	add	x0, x2, 52
	add	x2, x2, 180
	add	x0, x21, x0
	add	x3, x21, x2
	.p2align 2
.L429:
	ldr	w2, [x1], 4
	str	w2, [x0], 4
	cmp	x3, x0
	bne	.L429
	mov	w0, 0
	cbnz	w19, .L436
	lsl	x1, x20, 2
	ldr	w3, [x4, 384]
	sub	x20, x1, x20
	ldr	w2, [x4, 388]
	lsl	x1, x20, 4
	sub	x1, x1, x20
	add	x21, x21, x1, lsl 2
	stp	w2, w3, [x21, 44]
.L436:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L447:
	ldr	w5, [x1, 176]
	ldr	w0, [x1, 180]
	stp	w5, w0, [x4, 24]
	ldr	w3, [x1, 184]
	ldr	w2, [x1, 188]
	ldr	w0, [x1, 192]
	stp	w3, w2, [x4, 32]
	str	w0, [x4, 40]
	b	.L428
	.p2align 3
.L442:
	mov	w19, 0
	b	.L419
.L445:
	ldr	w2, [x1, 4108]
	mov	w0, 0
	str	w2, [x4, 20]
	and	w2, w2, 1048575
	ldr	w1, [x1, 176]
	stp	w2, w1, [x4, 20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L446:
	sub	x0, x5, x20
	and	w23, w3, 131071
	lsl	x0, x0, 2
	sub	x1, x0, x20
	add	x0, x0, x1, lsl 2
	add	x0, x24, x0
	ldr	w0, [x0, 56]
	bl	MEM_Phy2Vir
	cbz	x0, .L448
	sub	w1, w23, #1
	cmp	w1, 199
	bhi	.L434
	lsl	w1, w23, 2
	sub	w1, w1, #4
	lsl	x1, x1, 2
	add	x3, x1, 8
.L427:
	lsl	x2, x20, 2
	ldr	w4, [x0, x1]
	sub	x2, x2, x20
	lsl	x1, x2, 4
	sub	x2, x1, x2
	lsl	x1, x20, 6
	sub	x1, x1, x20
	add	x2, x21, x2, lsl 2
	lsl	x1, x1, 2
	str	w4, [x2, 16]
	ldr	w3, [x0, x3]
	sub	x0, x1, x20
	str	w3, [x2, 20]
	add	x1, x1, x0, lsl 2
	ldr	x1, [x24, x1]
	ldr	w3, [x1, 208]
	ldr	w0, [x1, 212]
	stp	w3, w0, [x2, 8]
	b	.L428
.L444:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L424
	str	x0, [x24, x21]
	mov	x1, x0
	b	.L423
.L434:
	mov	x3, 8
	mov	x1, 0
	b	.L427
.L418:
	ldr	x2, .LC180
	mov	w4, 0
	ldr	x1, .LC181
	mov	w3, w22
	add	x2, x2, 688
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L436
.L448:
	ldr	x2, .LC180
	ldr	x3, .LC188
	ldr	x1, .LC189
	add	x2, x2, 688
	bl	dprint_vfmw
	mov	w0, -1
	b	.L436
.L424:
	ldr	x1, .LC185
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L436
	.size	VDMHAL_V5R2C1_UpdateHardwareInfo, .-VDMHAL_V5R2C1_UpdateHardwareInfo
	.align	3
.LC179:
	.xword	g_DSPState
	.align	3
.LC180:
	.xword	.LANCHOR0
	.align	3
.LC181:
	.xword	.LC87
	.align	3
.LC184:
	.xword	g_HwMem
	.align	3
.LC185:
	.xword	.LC121
	.align	3
.LC186:
	.xword	g_BackUp
	.align	3
.LC188:
	.xword	.LC187
	.align	3
.LC189:
	.xword	.LC7
	.align	3
.LC190:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_ReadMsgSlot
	.type	VDMHAL_V5R2C1_ReadMsgSlot, %function
VDMHAL_V5R2C1_ReadMsgSlot:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x20, x0
	mov	x0, x30
	mov	x21, x1
	mov	w19, w2
	bl	_mcount
	cmp	x20, xzr
	ccmp	x21, xzr, 4, ne
	beq	.L453
	cmp	w19, 800
	bhi	.L454
	ldr	x3, .LC195
	ubfiz	x2, x19, 2, 30
	mov	x1, x21
	mov	x0, x20
	ldr	x3, [x3, 104]
	blr	x3
	mov	w0, 0
.L451:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L454:
	ldr	x1, .LC194
	mov	w2, w19
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L451
	.p2align 3
.L453:
	ldr	x1, .LC192
	mov	x3, x21
	mov	x2, x20
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L451
	.size	VDMHAL_V5R2C1_ReadMsgSlot, .-VDMHAL_V5R2C1_ReadMsgSlot
	.align	3
.LC192:
	.xword	.LC191
	.align	3
.LC194:
	.xword	.LC193
	.align	3
.LC195:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_WriteMsgSlot
	.type	VDMHAL_V5R2C1_WriteMsgSlot, %function
VDMHAL_V5R2C1_WriteMsgSlot:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	x19, x0
	mov	x0, x30
	mov	x20, x1
	mov	w21, w2
	bl	_mcount
	cmp	x19, xzr
	ccmp	x20, xzr, 4, ne
	beq	.L456
	sub	w0, w21, #1
	cmp	w0, 255
	bhi	.L456
	ldr	x3, .LC198
	ubfiz	x2, x21, 2, 30
	mov	x1, x20
	mov	x0, x19
	ldr	x3, [x3, 104]
	blr	x3
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L456:
	ldr	x1, .LC197
	mov	w0, 0
	bl	dprint_vfmw
	ldr	x21, [sp, 32]
	mov	w0, -1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	VDMHAL_V5R2C1_WriteMsgSlot, .-VDMHAL_V5R2C1_WriteMsgSlot
	.align	3
.LC197:
	.xword	.LC196
	.align	3
.LC198:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CfgRpMsg
	.type	VDMHAL_V5R2C1_CfgRpMsg, %function
VDMHAL_V5R2C1_CfgRpMsg:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	mov	x20, x1
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	ldr	w0, [x20, 64]
	bl	MEM_Phy2Vir
	mov	x20, x0
	cbz	x0, .L501
	ldr	w2, [x19, 44]
	sub	w0, w2, #1
	cmp	w0, 199
	bhi	.L502
	ldr	w3, [x19, 64]
	mov	w4, 0
	ldp	w2, w0, [x19, 28]
	ldrb	w5, [x19]
	lsl	w2, w2, w3
	lsl	w0, w0, w3
	add	w1, w2, 255
	cmp	w5, 1
	and	w1, w1, -256
	lsl	w3, w1, 4
	beq	.L503
	ldr	w2, [x19, 4]
	cmp	w2, 16
	beq	.L464
.L512:
	add	w0, w0, 31
	mov	w23, 8
	and	w0, w0, -32
	madd	w0, w0, w1, w4
.L487:
	ldr	w2, [x19, 20]
	mov	w1, w3
	str	w2, [x20]
	ldr	w2, [x19, 20]
	add	w2, w0, w2
	str	w2, [x20, 4]
	ldr	w2, [x19, 8]
	str	w2, [x20, 8]
	ldr	w2, [x19, 8]
	add	w0, w0, w2
	str	w0, [x20, 12]
	ldrb	w0, [x19, 1]
	cbnz	w0, .L504
.L466:
	str	w1, [x20, 16]
	mov	w3, 0
	str	w4, [x20, 20]
	mov	w2, 0
	ldp	w1, w0, [x19, 28]
	sub	w0, w0, #1
	sub	w1, w1, #1
	bfi	w2, w0, 0, 9
	bfi	w3, w1, 0, 9
	strh	w2, [x29, 74]
	strh	w3, [x29, 72]
	ldr	w0, [x29, 72]
	str	w0, [x20, 24]
	ldr	w0, [x19, 52]
	ldp	w21, w22, [x19, 28]
	sub	w0, w0, #1
	cmp	w0, 1
	bls	.L505
.L468:
	ldr	w0, [x19, 56]
	mov	w11, 0
	cbz	w0, .L506
.L469:
	cmp	w0, 1
	beq	.L485
.L511:
	sub	w11, w11, #1
	uxth	w11, w11
.L486:
	ldr	w3, [x19, 64]
	ldrb	w4, [x19]
	ldr	w2, [x19, 52]
	sub	w3, w3, #4
	ldrb	w1, [x29, 74]
	ldrb	w0, [x29, 75]
	and	w2, w2, 3
	bfi	w1, w4, 0, 1
	strh	w11, [x29, 72]
	bfi	w0, w3, 0, 2
	ldrb	w3, [x19, 1]
	bfi	w1, w2, 4, 2
	bfi	w0, w23, 2, 4
	bfi	w1, w2, 6, 2
	bfi	w0, w3, 6, 1
	strb	w1, [x29, 74]
	strb	w0, [x29, 75]
	mov	w0, 0
	ldr	w1, [x29, 72]
	str	w1, [x20, 28]
.L499:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L504:
	add	w0, w3, 15
	cmp	w3, wzr
	csel	w1, w0, w3, lt
	asr	w1, w1, 4
	b	.L466
	.p2align 3
.L506:
	ldr	w0, [x19, 64]
	cmp	w0, 6
	beq	.L490
	cmp	w0, 5
	beq	.L491
	cmp	w0, 4
	mov	w2, 8
	beq	.L470
	ldr	x1, .LC206
	mov	w0, 1
	bl	dprint_vfmw
	mov	w2, 1
.L470:
	ldr	w8, [x19, 44]
	cmp	w8, wzr
	ble	.L500
	mul	w12, w22, w21
	mov	w4, 0
	mov	w6, 0
	sub	w13, w12, #1
	mov	w11, 0
	sub	w9, w2, #1
	b	.L473
	.p2align 3
.L509:
	ldrsh	w6, [x10, 70]
	sub	w6, w6, #1
	add	w6, w6, w2
	udiv	w6, w6, w2
	mul	w6, w6, w2
	cmp	w0, w6
	bgt	.L476
.L475:
	add	w4, w4, 1
	cmp	w4, w8
	bge	.L507
.L484:
	cmp	w4, 199
	bgt	.L508
.L473:
	add	x10, x19, x4, sxtw 2
	cmp	w4, wzr
	ldrsh	w1, [x10, 74]
	sub	w0, w1, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	bgt	.L509
	ccmp	w0, w6, 0, ne
	ble	.L475
.L478:
	ldrsh	w1, [x10, 72]
	cmp	w12, w0
	csel	w0, w0, w13, hi
	add	w5, w11, 1
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w1, w0
	csel	w1, w1, wzr, le
	cmp	w5, 252
	bgt	.L510
	udiv	w7, w1, w21
	sxtw	x3, w11
	mov	w11, w5
	mov	w8, 0
	add	x3, x3, 6
	add	w4, w4, 1
	lsl	x3, x3, 3
	udiv	w5, w0, w21
	msub	w1, w7, w21, w1
	bfi	w8, w1, 0, 9
	mov	w1, 0
	bfi	w1, w7, 0, 9
	strh	w8, [x29, 76]
	strh	w1, [x29, 78]
	mov	w1, 0
	msub	w0, w5, w21, w0
	bfi	w1, w0, 0, 9
	mov	w0, 0
	bfi	w0, w5, 0, 9
	ldr	w5, [x29, 76]
	str	w5, [x20, x3]
	add	x3, x3, 4
	strh	w1, [x29, 76]
	strh	w0, [x29, 78]
	ldr	w0, [x29, 76]
	str	w0, [x20, x3]
	ldr	w8, [x19, 44]
	cmp	w4, w8
	blt	.L484
.L507:
	ldr	w0, [x19, 56]
	cmp	w0, 1
	bne	.L511
	.p2align 2
.L485:
	strh	wzr, [x29, 72]
	sub	w21, w21, #1
	strh	wzr, [x29, 74]
	mov	w2, 0
	sub	w22, w22, #1
	mov	w1, 0
	ldr	w3, [x29, 72]
	bfi	w2, w21, 0, 9
	bfi	w1, w22, 0, 9
	strh	w2, [x29, 72]
	strh	w1, [x29, 74]
	mov	w11, 0
	str	w0, [x19, 44]
	str	w3, [x20, 48]
	ldr	w0, [x29, 72]
	str	w0, [x20, 52]
	b	.L486
	.p2align 3
.L503:
	adds	w4, w2, 2047
	add	w2, w2, 4094
	csel	w2, w2, w4, mi
	add	w5, w0, 126
	and	w2, w2, -2048
	cmp	w2, wzr
	add	w4, w2, 127
	csel	w2, w4, w2, lt
	adds	w6, w0, 63
	csel	w4, w5, w6, mi
	asr	w2, w2, 7
	asr	w4, w4, 6
	lsl	w4, w4, 5
	mul	w4, w2, w4
	ldr	w2, [x19, 4]
	cmp	w2, 16
	bne	.L512
.L464:
	madd	w0, w0, w1, w4
	mov	w23, 10
	b	.L487
	.p2align 3
.L505:
	add	w22, w22, w22, lsr 31
	asr	w22, w22, 1
	b	.L468
	.p2align 3
.L479:
	udiv	w0, w0, w2
	ldrsh	w1, [x5, 76]
	udiv	w1, w1, w2
	mul	w0, w0, w2
	mul	w1, w1, w2
	cmp	w0, w1
	add	w14, w1, 1
	bhi	.L480
	sub	w1, w4, #1
	cmp	w0, w14
	add	x1, x19, x1, sxtw 2
	beq	.L480
	ldrsh	w1, [x1, 74]
	sub	w1, w1, #1
	add	w1, w1, w2
	udiv	w1, w1, w2
	mul	w1, w1, w2
	cmp	w0, w1
	bhi	.L478
.L480:
	cmp	w7, 199
	mov	w4, w3
	bgt	.L513
	ldrsh	w1, [x5, 78]
.L476:
	add	w3, w4, 1
	add	x5, x19, x4, sxtw 2
	cmp	w8, w3
	add	w0, w9, w1
	add	w7, w3, 1
	bgt	.L479
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L478
.L491:
	mov	w2, 4
	b	.L470
	.p2align 3
.L513:
	add	x0, x19, x3, sxtw 2
	ldrsh	w0, [x0, 74]
	sub	w0, w0, #1
	add	w0, w0, w2
	udiv	w0, w0, w2
	mul	w0, w0, w2
	b	.L478
.L508:
	ldr	x2, .LC201
	mov	w3, 2196
	ldr	x1, .LC208
	mov	w0, 0
	add	x2, x2, 752
	bl	dprint_vfmw
.L500:
	mov	w11, 0
	ldr	w0, [x19, 56]
	b	.L469
.L490:
	mov	w2, 2
	b	.L470
.L510:
	mov	w0, 1
	str	w0, [x19, 56]
	b	.L485
.L502:
	ldr	x1, .LC204
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L499
.L501:
	ldr	x2, .LC201
	mov	w0, 0
	ldr	x3, .LC200
	ldr	x1, .LC202
	add	x2, x2, 728
	bl	dprint_vfmw
	mov	w0, -1
	b	.L499
	.size	VDMHAL_V5R2C1_CfgRpMsg, .-VDMHAL_V5R2C1_CfgRpMsg
	.align	3
.LC200:
	.xword	.LC199
	.align	3
.LC201:
	.xword	.LANCHOR0
	.align	3
.LC202:
	.xword	.LC7
	.align	3
.LC204:
	.xword	.LC203
	.align	3
.LC206:
	.xword	.LC205
	.align	3
.LC208:
	.xword	.LC207
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CfgRpReg
	.type	VDMHAL_V5R2C1_CfgRpReg, %function
VDMHAL_V5R2C1_CfgRpReg:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	mov	x0, x30
	mov	w21, w3
	mov	x22, x1
	mov	x20, x4
	bl	_mcount
	str	wzr, [x29, 60]
	cmp	w21, wzr
	bgt	.L540
	ldr	x0, [x22]
	cbz	x0, .L541
.L517:
	ldr	x19, .LC212
	ldr	w3, [x22, 64]
	ldrb	w0, [x19]
	and	w3, w3, -16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L542
	mov	x0, x20
	mov	w2, 16
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	mov	w3, 53763
	movk	w3, 0x2000, lsl 16
	str	w3, [x29, 60]
	cmp	w0, 1
	beq	.L543
	mov	x0, x20
	mov	w2, 12
	mov	w1, 2
	mov	w22, 3075
	movk	w22, 0x30, lsl 16
	bl	VDH_Record_RegData
	str	w22, [x29, 60]
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L544
	mov	x0, x20
	mov	w3, w22
	mov	w2, 60
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L545
	mov	x0, x20
	mov	w3, w22
	mov	w2, 64
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L546
	mov	x0, x20
	mov	w3, w22
	mov	w2, 68
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L547
	mov	x0, x20
	mov	w3, w22
	mov	w2, 72
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L548
	mov	x0, x20
	mov	w3, w22
	mov	w2, 76
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L549
	mov	x0, x20
	mov	w3, w22
	mov	w2, 80
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x19]
	cmp	w0, 1
	beq	.L550
	mov	x0, x20
	mov	w3, w22
	mov	w2, 84
	mov	w1, 2
	bl	VDH_Record_RegData
	mov	w0, 0
.L537:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L542:
	sxtw	x1, w21
	ldr	x2, .LC213
	lsl	x0, x1, 6
	sub	x0, x0, x1
	lsl	x0, x0, 2
	sub	x4, x0, x1
	add	x0, x0, x4, lsl 2
	ldr	x0, [x2, x0]
	str	w3, [x0, 16]
.L520:
	lsl	x0, x1, 6
	mov	w4, 53763
	sub	x0, x0, x1
	movk	w4, 0x2000, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 12]
.L522:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 60]
.L524:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 64]
.L526:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 68]
.L528:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 72]
.L530:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 76]
.L532:
	lsl	x0, x1, 6
	mov	w4, 3075
	sub	x0, x0, x1
	movk	w4, 0x30, lsl 16
	lsl	x0, x0, 2
	sub	x3, x0, x1
	add	x0, x0, x3, lsl 2
	ldr	x0, [x2, x0]
	str	w4, [x0, 80]
.L534:
	lsl	x3, x1, 6
	mov	w4, 3075
	sub	x3, x3, x1
	movk	w4, 0x30, lsl 16
	lsl	x3, x3, 2
	mov	w0, 0
	sub	x1, x3, x1
	add	x1, x3, x1, lsl 2
	ldr	x1, [x2, x1]
	str	w4, [x1, 84]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L541:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L518
	str	x0, [x22]
	b	.L517
	.p2align 3
.L540:
	ldr	x2, .LC209
	mov	w4, 0
	ldr	x1, .LC210
	mov	w3, w21
	add	x2, x2, 776
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L537
.L518:
	ldr	x1, .LC211
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L537
.L547:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L528
.L546:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L526
.L545:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L524
.L544:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L522
.L549:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L532
.L548:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L530
.L550:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L534
.L543:
	ldr	x2, .LC213
	sxtw	x1, w21
	b	.L520
	.size	VDMHAL_V5R2C1_CfgRpReg, .-VDMHAL_V5R2C1_CfgRpReg
	.align	3
.LC209:
	.xword	.LANCHOR0
	.align	3
.LC210:
	.xword	.LC87
	.align	3
.LC211:
	.xword	.LC121
	.align	3
.LC212:
	.xword	g_HalDisable
	.align	3
.LC213:
	.xword	g_HwMem
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_MakeDecReport
	.type	VDMHAL_V5R2C1_MakeDecReport, %function
VDMHAL_V5R2C1_MakeDecReport:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	mov	x0, x30
	bl	_mcount
	cbz	x19, .L581
	ldr	x23, [x19, 8]
	ldr	w21, [x19]
	ldr	w22, [x19, 16]
	cbz	x23, .L582
	sxtw	x22, w22
	ldr	x20, .LC222
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	ldr	x0, [x20, x0]
	cbz	x0, .L555
	ldr	x2, .LC223
	add	x0, x2, 4
	add	x2, x2, 128
	ldr	w1, [x2, -128]
	cmp	w1, 1
	bne	.L558
	b	.L570
	.p2align 3
.L584:
	cmp	x0, x2
	beq	.L583
.L558:
	ldr	w1, [x0]
	add	x0, x0, 4
	cmp	w1, 1
	bne	.L584
.L570:
	mov	w19, w1
.L556:
	ldr	x3, .LC227
	mov	x2, 820
	mov	w1, 0
	mov	x0, x23
	ldr	x3, [x3, 96]
	blr	x3
	lsl	x0, x22, 6
	lsl	x1, x22, 2
	sub	x0, x0, x22
	sub	x1, x1, x22
	lsl	x0, x0, 2
	lsl	x2, x1, 4
	sub	x3, x0, x22
	sub	x1, x2, x1
	ldr	x4, .LC228
	add	x2, x0, x3, lsl 2
	add	x2, x20, x2
	add	x1, x4, x1, lsl 2
	ldr	w0, [x2, 40]
	str	w0, [x23, 4]
	ldr	w1, [x1, 4]
	ubfx	x0, x1, 17, 2
	cmp	w0, 1
	beq	.L571
	and	w1, w1, 131072
	cmp	w1, wzr
	ccmp	w21, 3, 0, ne
	cset	w1, ne
.L559:
	lsl	x0, x22, 2
	str	w1, [x23]
	sub	x0, x0, x22
	cmp	w21, wzr
	lsl	x1, x0, 4
	ccmp	w21, 15, 4, ne
	sub	x0, x1, x0
	add	x0, x4, x0, lsl 2
	ldr	w2, [x0, 4]
	and	w2, w2, 131071
	str	w2, [x23, 12]
	beq	.L585
.L560:
	cmp	w2, 200
	bhi	.L586
.L562:
	lsl	x0, x22, 6
	sub	x0, x0, x22
	lsl	x0, x0, 2
	sub	x1, x0, x22
	add	x0, x0, x1, lsl 2
	add	x20, x20, x0
	ldr	w21, [x20, 56]
	mov	w0, w21
	bl	MEM_Phy2Vir
	cbz	x0, .L587
	lsl	x3, x22, 2
	ldr	x19, .LC233
	sub	x3, x3, x22
	ldr	w2, [x23, 12]
	mov	x1, x0
	add	x20, x22, x3, lsl 3
	lsl	w2, w2, 2
	add	x0, x19, x20, lsl 7
	bl	VDMHAL_V5R2C1_ReadMsgSlot
	ldr	w0, [x23, 12]
	cbz	w0, .L567
	sub	w2, w0, #1
	mov	x5, 22
	add	x1, x23, 18
	mov	w0, 2
	add	x5, x5, x2, uxtw 2
	lsl	x3, x20, 5
	add	x5, x23, x5
	.p2align 2
.L566:
	sub	w2, w0, #1
	add	x4, x3, x0, uxtw
	add	x2, x3, x2
	add	w0, w0, 4
	ldr	w2, [x19, x2, lsl 2]
	strh	w2, [x1, -2]
	ldr	w2, [x19, x4, lsl 2]
	strh	w2, [x1], 4
	cmp	x5, x1
	bne	.L566
.L567:
	mov	w0, 6
	bl	IsDprintTypeEnable
	cbnz	w0, .L588
.L553:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L585:
	cmp	w19, 1
	beq	.L589
	ldr	x1, .LC229
	ldrb	w1, [x1]
	cbnz	w1, .L560
	ldrb	w0, [x0, 19]
	and	w0, w0, 3
	cmp	w0, 2
	bne	.L560
	mov	w0, 1
	strh	wzr, [x23, 16]
	str	w0, [x23, 12]
	mov	w0, 0
	strh	wzr, [x23, 18]
	b	.L553
	.p2align 3
.L583:
	mov	w19, 0
	b	.L556
	.p2align 3
.L588:
	ldr	x1, .LC235
	mov	w0, 6
	ldr	w2, [x23, 12]
	mov	w20, 0
	bl	dprint_vfmw
	mov	w2, w21
	ldr	x1, .LC237
	lsl	x21, x22, 2
	mov	w0, 6
	sub	x21, x21, x22
	bl	dprint_vfmw
	ldr	x24, .LC239
	add	x21, x22, x21, lsl 3
	lsl	x21, x21, 5
	.p2align 2
.L568:
	add	w1, w20, 3
	add	w3, w20, 2
	add	w0, w20, 1
	add	x7, x21, x20, uxtw
	add	x1, x21, x1
	add	x3, x21, x3
	add	x0, x21, x0
	mov	w2, w20
	add	w20, w20, 4
	ldr	w6, [x19, x1, lsl 2]
	mov	x1, x24
	ldr	w5, [x19, x3, lsl 2]
	ldr	w4, [x19, x0, lsl 2]
	mov	w0, 6
	ldr	w3, [x19, x7, lsl 2]
	bl	dprint_vfmw
	ldr	w0, [x23, 12]
	lsl	w0, w0, 2
	sub	w0, w0, #3
	cmp	w0, w20
	bhi	.L568
	ldr	x1, .LC241
	mov	w0, 6
	bl	dprint_vfmw
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L571:
	mov	w1, 0
	b	.L559
	.p2align 3
.L586:
	ldr	x1, .LC231
	mov	w3, 200
	mov	w0, 1
	bl	dprint_vfmw
	str	wzr, [x23, 12]
	b	.L562
	.p2align 3
.L589:
	ldr	w0, [x0, 16]
	ubfx	x0, x0, 21, 2
	cmp	w0, 2
	bne	.L560
	strh	wzr, [x23, 16]
	mov	w0, 0
	strh	wzr, [x23, 18]
	str	w19, [x23, 12]
	b	.L553
.L587:
	ldr	x2, .LC218
	ldr	x3, .LC232
	ldr	x1, .LC219
	add	x2, x2, 800
	bl	dprint_vfmw
	mov	w0, -1
	b	.L553
.L555:
	ldr	x2, .LC218
	ldr	x3, .LC224
.L579:
	ldr	x1, .LC219
	mov	w0, 0
	add	x2, x2, 800
	bl	dprint_vfmw
	mov	w0, -1
	b	.L553
.L582:
	ldr	x2, .LC218
	ldr	x3, .LC221
	b	.L579
.L581:
	ldr	x2, .LC218
	ldr	x3, .LC217
	b	.L579
	.size	VDMHAL_V5R2C1_MakeDecReport, .-VDMHAL_V5R2C1_MakeDecReport
	.align	3
.LC217:
	.xword	.LC216
	.align	3
.LC218:
	.xword	.LANCHOR0
	.align	3
.LC219:
	.xword	.LC7
	.align	3
.LC221:
	.xword	.LC220
	.align	3
.LC222:
	.xword	g_HwMem
	.align	3
.LC223:
	.xword	g_DSPState
	.align	3
.LC224:
	.xword	.LC159
	.align	3
.LC227:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC228:
	.xword	g_BackUp
	.align	3
.LC229:
	.xword	g_not_allow_H264FullPictureRepair_flag
	.align	3
.LC231:
	.xword	.LC230
	.align	3
.LC232:
	.xword	.LC187
	.align	3
.LC233:
	.xword	g_UpMsg
	.align	3
.LC235:
	.xword	.LC234
	.align	3
.LC237:
	.xword	.LC236
	.align	3
.LC239:
	.xword	.LC238
	.align	3
.LC241:
	.xword	.LC240
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_PrepareRepair
	.type	VDMHAL_V5R2C1_PrepareRepair, %function
VDMHAL_V5R2C1_PrepareRepair:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w22, w0
	mov	x0, x30
	sxtw	x19, w3
	mov	x23, x1
	mov	w27, w2
	mov	x24, x4
	bl	_mcount
	ldr	x25, .LC242
	lsl	x0, x19, 6
	cmp	w19, wzr
	sub	x0, x0, x19
	mov	x21, x19
	lsl	x0, x0, 2
	sub	x20, x0, x19
	add	x20, x0, x20, lsl 2
	add	x26, x20, x25
	bgt	.L609
	ldr	x0, [x20, x25]
	cbz	x0, .L610
	cbz	w27, .L611
.L595:
	cmp	w27, 1
	mov	w0, 0
	beq	.L612
.L592:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L610:
	mov	w0, -121438208
	bl	MEM_Phy2Vir
	cbz	x0, .L594
	str	x0, [x20, x25]
	cbnz	w27, .L595
	.p2align 2
.L611:
	lsl	x0, x19, 3
	ldr	x20, .LC247
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	ldr	w1, [x0, 44]
	cmp	w1, wzr
	ble	.L596
	cmp	w22, 6
	beq	.L613
.L597:
	lsl	x2, x19, 3
	sub	x2, x2, x19
	lsl	x2, x2, 3
	sub	x2, x2, x19
	lsl	x2, x2, 1
	sub	x2, x2, x19
	lsl	x2, x2, 4
	add	x1, x20, x2
	ldr	w0, [x1, 28]
	ldr	w3, [x1, 64]
	lsl	w0, w0, w3
	cmp	w0, 1920
	bgt	.L599
	ldr	w0, [x1, 4]
	cmp	w0, 17
	beq	.L599
	mov	w0, 1
	strb	wzr, [x20, x2]
	strb	w0, [x1, 1]
	mov	x1, x23
	mov	w0, w22
	bl	VDMHAL_UpateDecParam.constprop.10
.L599:
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	mov	x1, x26
	mov	w0, w22
	bl	VDMHAL_V5R2C1_CfgRpReg
	lsl	x0, x19, 3
	mov	w2, w21
	sub	x0, x0, x19
	mov	x1, x26
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x0, x0, x19
	add	x0, x20, x0, lsl 4
	bl	VDMHAL_V5R2C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L612:
	cmp	w22, 6
	bne	.L600
	ldrb	w0, [x23, 17]
	cmp	w0, 1
	bne	.L600
	lsl	x0, x19, 3
	ldr	x2, .LC247
	sub	x0, x0, x19
	lsl	x0, x0, 3
	sub	x0, x0, x19
	lsl	x0, x0, 1
	sub	x19, x0, x19
	lsl	x19, x19, 4
	add	x1, x2, x19
	ldr	w0, [x1, 916]
	cmp	w0, wzr
	ble	.L600
	ldr	w0, [x1, 28]
	add	x20, x19, 872
	ldr	w3, [x1, 64]
	add	x20, x20, x2
	lsl	w0, w0, w3
	cmp	w0, 1920
	mov	w0, 2
	str	w0, [x1, 924]
	bgt	.L601
	ldr	w0, [x1, 4]
	cmp	w0, 17
	beq	.L601
	strb	w27, [x1, 1]
	mov	w0, w22
	mov	x1, x23
	strb	wzr, [x2, x19]
	bl	VDMHAL_UpateDecParam.constprop.10
.L601:
	mov	x4, x24
	mov	w3, w21
	mov	x2, x23
	mov	x1, x26
	mov	w0, 6
	bl	VDMHAL_V5R2C1_CfgRpReg
	mov	w2, w21
	mov	x1, x26
	mov	x0, x20
	bl	VDMHAL_V5R2C1_CfgRpMsg
	ldr	x27, [sp, 80]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L613:
	ldrb	w1, [x23, 17]
	mov	w2, 0
	cmp	w1, 1
	csel	w1, w1, w2, eq
	str	w1, [x0, 924]
	b	.L597
	.p2align 3
.L609:
	ldr	x2, .LC243
	mov	w4, 0
	ldr	x1, .LC244
	mov	w3, w19
	add	x2, x2, 832
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L592
	.p2align 3
.L600:
	ldr	x1, .LC251
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L592
.L596:
	ldr	x1, .LC249
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, 0
	b	.L592
.L594:
	ldr	x1, .LC246
	mov	w0, 0
	bl	dprint_vfmw
	mov	w0, -1
	b	.L592
	.size	VDMHAL_V5R2C1_PrepareRepair, .-VDMHAL_V5R2C1_PrepareRepair
	.align	3
.LC242:
	.xword	g_HwMem
	.align	3
.LC243:
	.xword	.LANCHOR0
	.align	3
.LC244:
	.xword	.LC87
	.align	3
.LC246:
	.xword	.LC245
	.align	3
.LC247:
	.xword	g_RepairParam
	.align	3
.LC249:
	.xword	.LC248
	.align	3
.LC251:
	.xword	.LC250
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_StartHwRepair
	.type	VDMHAL_V5R2C1_StartHwRepair, %function
VDMHAL_V5R2C1_StartHwRepair:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	sxtw	x20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	ldr	x21, .LC252
	ldrb	w4, [x21]
	cmp	w4, 1
	bne	.L638
	cmp	w20, wzr
	ble	.L639
	ldr	x22, .LC254
	mov	w3, w20
	ldr	x23, .LC255
	mov	w0, 32
	add	x2, x22, 864
	mov	x1, x23
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L622
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L635
.L617:
	cbz	x19, .L640
.L631:
	ldr	x1, .LC258
	sbfiz	x0, x20, 6, 32
	mov	w2, 1
	str	w2, [x19, 4]
	add	x1, x1, x0
	mov	x0, x19
	ldr	w1, [x1, 8]
	str	w1, [x19, 8]
	strb	w20, [x19]
	strb	w2, [x19, 2]
	bl	VDH_PostTask
.L614:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L639:
	sxtw	x0, w20
	ldr	x3, .LC253
	lsl	x1, x0, 6
	mov	w4, 67108864
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x2, x1, x0
	add	x1, x1, x2, lsl 2
	ldr	x1, [x3, x1]
	str	w4, [x1, 8]
.L620:
	lsl	x1, x0, 6
	mov	w2, -2
	sub	x1, x1, x0
	lsl	x1, x1, 2
	sub	x0, x1, x0
	add	x0, x1, x0, lsl 2
	ldr	x0, [x3, x0]
	str	w2, [x0, 36]
.L618:
	ldr	x0, .LC259
	ldr	x0, [x0, 224]
	blr	x0
	cmp	w20, wzr
	ble	.L634
	ldr	x22, .LC254
	ldr	x23, .LC255
.L627:
	add	x22, x22, 880
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w4, 1
	mov	w0, 32
	bl	dprint_vfmw
	mov	w4, 1
	mov	w3, w20
	mov	x2, x22
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	b	.L614
	.p2align 3
.L616:
	cmp	w20, wzr
	ble	.L632
	ldr	x22, .LC254
	ldr	x23, .LC255
.L622:
	mov	w4, 1
	mov	w3, w20
	add	x2, x22, 864
	mov	x1, x23
	mov	w0, 32
	bl	dprint_vfmw
	ldrb	w0, [x21]
	cmp	w0, 1
	bne	.L617
.L635:
	ldr	x0, .LC259
	ldr	x0, [x0, 224]
	blr	x0
	b	.L627
	.p2align 3
.L638:
	mov	x0, x19
	mov	w3, 67108864
	mov	w2, 8
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L616
	mov	x0, x19
	mov	w3, -2
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x21]
	cmp	w0, 1
	beq	.L618
	cbnz	x19, .L631
.L640:
	ldr	x2, .LC254
	mov	x3, 0
	ldr	x1, .LC257
	mov	w0, 0
	add	x2, x2, 880
	bl	dprint_vfmw
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.p2align 3
.L634:
	lsl	x0, x20, 6
	ldr	x1, .LC253
	sub	x0, x0, x20
	mov	w3, 1
	lsl	x0, x0, 2
	sub	x20, x0, x20
	add	x0, x0, x20, lsl 2
	ldr	x2, [x1, x0]
	str	wzr, [x2]
	ldr	x2, [x1, x0]
	str	w3, [x2]
	ldr	x0, [x1, x0]
	str	wzr, [x0]
	b	.L614
.L632:
	ldr	x3, .LC253
	sxtw	x0, w20
	b	.L620
	.size	VDMHAL_V5R2C1_StartHwRepair, .-VDMHAL_V5R2C1_StartHwRepair
	.align	3
.LC252:
	.xword	g_HalDisable
	.align	3
.LC253:
	.xword	g_HwMem
	.align	3
.LC254:
	.xword	.LANCHOR0
	.align	3
.LC255:
	.xword	.LC101
	.align	3
.LC257:
	.xword	.LC256
	.align	3
.LC258:
	.xword	g_VdmDrvParam
	.align	3
.LC259:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_CalVdhClkSkip
	.type	VDMHAL_V5R2C1_CalVdhClkSkip, %function
VDMHAL_V5R2C1_CalVdhClkSkip:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	mov	x0, x30
	bl	_mcount
	ldr	x24, .LC261
	ldr	w28, [x24, 128]
	tbnz	w28, #31, .L673
	ldr	x25, .LC264
	add	x20, x24, 132
	ldr	x27, .LC267
	add	x24, x24, 256
	ldr	x26, .LC266
	mov	w23, 30
	mov	w22, 0
	mov	w21, 0
	add	x25, x25, 912
	mov	w19, 0
	b	.L644
	.p2align 3
.L676:
	mov	w3, w28
	mov	x2, x25
	mov	x1, x26
	mov	w0, 1
	bl	dprint_vfmw
.L646:
	cmp	x24, x20
	beq	.L674
.L663:
	ldr	w28, [x20], 4
	tbnz	w28, #31, .L675
.L644:
	mov	w0, w28
	bl	VCTRL_IsChanActive
	cbnz	w0, .L676
	mov	w0, w28
	bl	FSP_GetInst
	cbz	x0, .L647
	ldp	w1, w0, [x0, 40]
	adds	w19, w1, 15
	add	w1, w1, 30
	add	w21, w0, 30
	csel	w19, w1, w19, mi
	adds	w0, w0, 15
	asr	w19, w19, 4
	csel	w0, w21, w0, mi
	asr	w21, w0, 4
.L647:
	ldr	x1, [x27, w28, sxtw 3]
	mov	w0, w28
	ldr	w1, [x1, 1568]
	cmp	w1, 31
	csel	w23, w23, w1, lt
	bl	VCTRL_GetVidStd
	cmp	w0, 17
	bls	.L677
.L666:
	cmp	x24, x20
	mov	w22, 0
	bne	.L663
.L674:
	lsl	w0, w22, 2
	mov	w3, 23813
	sub	w22, w0, w22
	movk	w3, 0xdb4f, lsl 16
	lsl	w1, w22, 6
	mov	w0, 32
	mov	w2, 25
	umull	x1, w1, w3
	ldp	x19, x20, [sp, 16]
	lsr	x1, x1, 53
	sub	w0, w0, w1
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L677:
	ldr	x1, .LC268
	ldrb	w0, [x1,w0,uxtw]
	adr	x1, .Lrtx650
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx650:
	.section	.rodata
	.align	0
	.align	2
.L650:
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L666 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L666 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L666 - .Lrtx650) / 4
	.byte	(.L660 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.byte	(.L659 - .Lrtx650) / 4
	.text
	.p2align 3
.L659:
	mul	w22, w19, w21
	mul	w22, w22, w23
	b	.L646
	.p2align 3
.L675:
	lsl	w1, w22, 2
	mov	w0, 23813
	sub	w22, w1, w22
	movk	w0, 0xdb4f, lsl 16
	lsl	w22, w22, 6
	mov	w1, 32
	mov	w2, 25
	umull	x0, w22, w0
	lsr	x0, x0, 53
	sub	w0, w1, w0
	cmp	w0, w2
	csel	w0, w0, w2, le
	cmp	w0, wzr
	csel	w0, w0, wzr, ge
.L642:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.p2align 3
.L660:
	mul	w22, w19, w21
	mul	w22, w22, w23
	lsl	w22, w22, 1
	b	.L646
.L673:
	mov	w0, 25
	b	.L642
	.size	VDMHAL_V5R2C1_CalVdhClkSkip, .-VDMHAL_V5R2C1_CalVdhClkSkip
	.align	3
.LC261:
	.xword	g_ChanCtx
	.align	3
.LC264:
	.xword	.LANCHOR0
	.align	3
.LC266:
	.xword	.LC265
	.align	3
.LC267:
	.xword	s_pstVfmwChan
	.align	3
.LC268:
	.xword	.L650
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetVdmClk
	.type	VDMHAL_V5R2C1_GetVdmClk, %function
VDMHAL_V5R2C1_GetVdmClk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	bl	_mcount
	cmp	w20, 3
	bls	.L686
.L679:
	ldr	x0, .LC271
	sbfiz	x19, x19, 6, 32
	mov	w1, 500
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L686:
	ldr	x0, .LC270
	ldrb	w0, [x0,w20,uxtw]
	adr	x1, .Lrtx681
	add	x0, x1, w0, sxtb #2
	br	x0
.Lrtx681:
	.section	.rodata
	.align	0
	.align	2
.L681:
	.byte	(.L679 - .Lrtx681) / 4
	.byte	(.L682 - .Lrtx681) / 4
	.byte	(.L683 - .Lrtx681) / 4
	.byte	(.L684 - .Lrtx681) / 4
	.text
	.p2align 3
.L683:
	ldr	x0, .LC271
	sbfiz	x19, x19, 6, 32
	mov	w1, 100
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L682:
	ldr	x0, .LC271
	sbfiz	x19, x19, 6, 32
	mov	w1, 540
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.p2align 3
.L684:
	ldr	x0, .LC271
	sbfiz	x19, x19, 6, 32
	mov	w1, 600
	add	x19, x0, x19
	mov	w0, w1
	str	w1, [x19, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	VDMHAL_V5R2C1_GetVdmClk, .-VDMHAL_V5R2C1_GetVdmClk
	.align	3
.LC270:
	.xword	.L681
	.align	3
.LC271:
	.xword	g_VdmDrvParam
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_StartHwDecode
	.type	VDMHAL_V5R2C1_StartHwDecode, %function
VDMHAL_V5R2C1_StartHwDecode:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w20, w0
	mov	x0, x30
	mov	x19, x1
	bl	_mcount
	cmp	w20, wzr
	bgt	.L736
	ldr	x25, .LC274
	sxtw	x21, w20
	ldr	x24, .LC275
	mov	w26, 0
	add	x0, x25, x21, lsl 6
	ldr	w23, [x0, 8]
	ldr	x0, [x24, w23, sxtw 3]
	ldr	w1, [x0, 1564]
	cmp	w1, 1
	beq	.L737
.L690:
	ldr	x22, .LC279
	ldrb	w0, [x22]
	cmp	w0, 1
	bne	.L738
	ldr	x1, .LC280
	ldr	x2, [x1]
	ldr	w1, [x2, 120]
	ubfx	x3, x1, 8, 2
	cmp	w26, w3
	beq	.L729
	bfi	w1, w26, 8, 2
	str	w1, [x2, 120]
.L729:
	ldr	x1, .LC281
	ldrh	w1, [x1,w26,uxtw #1]
	adr	x2, .Lrtx698
	add	x1, x2, w1, sxth #2
	br	x1
.Lrtx698:
	.section	.rodata
	.align	0
	.align	2
.L698:
	.2byte	(.L697 - .Lrtx698) / 4
	.2byte	(.L699 - .Lrtx698) / 4
	.2byte	(.L700 - .Lrtx698) / 4
	.2byte	(.L701 - .Lrtx698) / 4
	.text
	.p2align 3
.L738:
	mov	x0, x19
	mov	w3, w26
	mov	w2, 0
	mov	w1, 0
	bl	VDH_Record_RegData
	ldrb	w0, [x22]
	b	.L729
	.p2align 3
.L736:
	ldr	x2, .LC272
	mov	w4, 0
	ldr	x1, .LC273
	mov	w3, w20
	add	x2, x2, 944
	mov	w0, 0
	bl	dprint_vfmw
.L687:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L737:
	ldr	w0, [x0, 600]
	cmp	w0, 17
	bne	.L690
	ldr	x0, .LC276
	ldr	x0, [x0, w23, sxtw 3]
	ldr	w1, [x0, 40]
	cmp	w1, 3839
	bgt	.L691
	ldr	w0, [x0, 44]
	cmp	w0, 2159
	ble	.L690
.L691:
	ldr	x1, .LC277
	mov	w0, 12320
	movk	w0, 0xf8a2, lsl 16
	ldr	x1, [x1, 304]
	blr	x1
	ldr	x1, .LC278
	ldr	x1, [x1]
	ldr	w1, [x1, 196]
	lsr	w1, w1, 24
	cmp	w1, 3
	beq	.L722
	cmp	w1, 2
	beq	.L723
	mov	w2, 221
	mov	w3, 221
	movk	w2, 0x71, lsl 16
	movk	w3, 0x89, lsl 16
	cmp	w1, 1
	csel	w1, w2, w3, ne
.L692:
	mov	w26, 2
	str	w1, [x0]
	b	.L690
	.p2align 3
.L700:
	add	x1, x25, x21, lsl 6
	mov	w2, 100
	str	w2, [x1, 16]
.L702:
	ldr	x1, [x24, w23, sxtw 3]
	cmp	w0, 1
	ldr	w24, [x1, 1272]
	bne	.L739
.L703:
	ldr	x0, .LC280
	mov	x3, x19
	mov	w2, w20
	ldr	x0, [x0]
	ldr	w1, [x0, 120]
	and	w1, w1, -258049
	str	w1, [x0, 120]
	ldr	w1, [x0, 120]
	orr	w1, w1, 131072
	str	w1, [x0, 120]
	mov	w0, 12
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L740
.L715:
	mov	w1, 2
	mov	x0, x19
	mov	w3, -1431655766
	mov	w2, 156
	bl	VDH_Record_RegData
	ldr	x1, .LC282
	ldrb	w0, [x22]
	ldr	w1, [x1]
	cmp	w1, 1
	beq	.L741
.L706:
	mov	w3, 0
.L705:
	cmp	w0, 1
	beq	.L742
	mov	x0, x19
	mov	w2, 61472
	mov	w1, 2
	bl	VDH_Record_RegData
	cmp	w24, 1
	ldrb	w0, [x22]
	beq	.L743
.L709:
	mov	w3, -2
.L708:
	cmp	w0, 1
	beq	.L744
	mov	x0, x19
	mov	w2, 36
	mov	w1, 2
	bl	VDH_Record_RegData
	ldrb	w0, [x22]
	cmp	w0, 1
	beq	.L745
	cbz	x19, .L746
	mov	w0, 1
	strb	w20, [x19]
	stp	w0, w23, [x19, 4]
	mov	x0, x19
	bl	VDH_PostTask
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.p2align 3
.L743:
	mov	w3, -6
	b	.L708
	.p2align 3
.L741:
	mov	w3, 15
	b	.L705
	.p2align 3
.L699:
	add	x1, x25, x21, lsl 6
	mov	w2, 540
	cmp	w0, 1
	str	w2, [x1, 16]
	ldr	x1, [x24, w23, sxtw 3]
	ldr	w24, [x1, 1272]
	beq	.L703
.L739:
	mov	w3, 0
	mov	w2, 1
	mov	w1, 0
	mov	x0, x19
	bl	VDH_Record_RegData
	mov	w0, 12
	mov	x3, x19
	mov	w2, w20
	mov	w1, 3
	bl	SCD_ConfigReg
	ldrb	w0, [x22]
	cmp	w0, 1
	bne	.L715
.L740:
	ldr	x2, .LC282
	lsl	x1, x21, 6
	sub	x1, x1, x21
	ldr	x26, .LC283
	lsl	x1, x1, 2
	ldr	w2, [x2]
	cmp	w2, 1
	sub	x2, x1, x21
	add	x1, x1, x2, lsl 2
	mov	w2, -1431655766
	ldr	x1, [x26, x1]
	str	w2, [x1, 156]
	bne	.L706
	mov	w3, 15
	b	.L707
	.p2align 3
.L697:
	add	x1, x25, x21, lsl 6
	mov	w2, 500
	str	w2, [x1, 16]
	b	.L702
	.p2align 3
.L701:
	add	x1, x25, x21, lsl 6
	mov	w2, 600
	str	w2, [x1, 16]
	b	.L702
	.p2align 3
.L742:
	ldr	x26, .LC283
.L707:
	lsl	x0, x21, 6
	cmp	w24, 1
	sub	x0, x0, x21
	lsl	x0, x0, 2
	sub	x1, x0, x21
	add	x0, x0, x1, lsl 2
	ldr	x0, [x26, x0]
	add	x0, x0, 61440
	str	w3, [x0, 32]
	beq	.L728
	mov	w0, 1
	b	.L709
	.p2align 3
.L744:
	ldr	x26, .LC283
.L710:
	lsl	x1, x21, 6
	ldr	x19, .LC277
	sub	x1, x1, x21
	mov	x0, 30
	lsl	x1, x1, 2
	sub	x2, x1, x21
	add	x1, x1, x2, lsl 2
	ldr	x1, [x26, x1]
	str	w3, [x1, 36]
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
.L713:
	lsl	x0, x21, 6
	mov	w2, 1
	sub	x1, x0, x21
	add	x25, x25, x0
	lsl	x0, x1, 2
	ldr	x3, .LC285
	sub	x21, x0, x21
	mov	w1, 4
	add	x21, x0, x21, lsl 2
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	x0, [x26, x21]
	str	w2, [x0]
	ldr	x0, [x26, x21]
	str	wzr, [x0]
	ldr	w2, [x25, 8]
	mov	w0, w2
	ldr	w2, [x3, w2, sxtw 2]
	bl	VDEC_Lowdelay_Event_Time
	b	.L687
	.p2align 3
.L746:
	ldr	x2, .LC272
	mov	x3, 0
	ldr	x1, .LC284
	mov	w0, 0
	add	x2, x2, 944
	bl	dprint_vfmw
	b	.L687
	.p2align 3
.L728:
	mov	w3, -6
	b	.L710
.L722:
	mov	w1, 221
	movk	w1, 0x71, lsl 16
	b	.L692
.L723:
	mov	w1, 221
	movk	w1, 0x7d, lsl 16
	b	.L692
.L745:
	ldr	x19, .LC277
	mov	x0, 30
	ldr	x1, [x19, 232]
	blr	x1
	ldr	x0, [x19, 224]
	blr	x0
	ldr	x26, .LC283
	b	.L713
	.size	VDMHAL_V5R2C1_StartHwDecode, .-VDMHAL_V5R2C1_StartHwDecode
	.align	3
.LC272:
	.xword	.LANCHOR0
	.align	3
.LC273:
	.xword	.LC87
	.align	3
.LC274:
	.xword	g_VdmDrvParam
	.align	3
.LC275:
	.xword	s_pstVfmwChan
	.align	3
.LC276:
	.xword	s_pFspInst
	.align	3
.LC277:
	.xword	vfmw_Osal_Func_Ptr_S
	.align	3
.LC278:
	.xword	g_pstRegSysCtrl
	.align	3
.LC279:
	.xword	g_HalDisable
	.align	3
.LC280:
	.xword	g_pstRegCrg
	.align	3
.LC281:
	.xword	.L698
	.align	3
.LC282:
	.xword	mask_mmu_err_int
	.align	3
.LC283:
	.xword	g_HwMem
	.align	3
.LC284:
	.xword	.LC256
	.align	3
.LC285:
	.xword	g_LowDelaySeqIndex
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_GetCharacter
	.type	VDMHAL_V5R2C1_GetCharacter, %function
VDMHAL_V5R2C1_GetCharacter:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	mov	x0, x30
	bl	_mcount
	ldr	x2, .LC286
	mov	w3, 15
	ldr	x0, .LC287
	mov	w1, 4
	str	w3, [x2]
	str	w1, [x0]
	ldp	x29, x30, [sp], 16
	ret
	.size	VDMHAL_V5R2C1_GetCharacter, .-VDMHAL_V5R2C1_GetCharacter
	.align	3
.LC286:
	.xword	g_VdmCharacter
	.align	3
.LC287:
	.xword	g_eVdmVersion
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.type	VDMHAL_V5R2C1_WriteBigTitle1DYuv, %function
VDMHAL_V5R2C1_WriteBigTitle1DYuv:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 112]
	mov	x0, x30
	mov	w21, w3
	mov	x22, x1
	mov	w19, w2
	str	w4, [x29, 108]
	bl	_mcount
	ubfx	x0, x21, 29, 2
	stp	xzr, xzr, [x29, 144]
	stp	xzr, xzr, [x29, 160]
	stp	xzr, xzr, [x29, 176]
	stp	xzr, xzr, [x29, 192]
	cmp	w0, 1
	beq	.L792
	mov	w20, 2
	cmp	w0, w20
	csinc	w20, w20, wzr, ne
.L749:
	ldr	x0, [x29, 112]
	cbz	x0, .L748
	ldr	x0, .LC289
	mov	w4, 0
	add	x3, x29, 144
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L752
	ldr	x0, .LC293
	mov	w4, 0
	add	x3, x29, 176
	mov	w2, 4194304
	mov	w1, 0
	bl	MEM_AllocMemBlock
	cbnz	w0, .L752
	add	w19, w19, 15
	add	w21, w21, 15
	and	w19, w19, -16
	and	w0, w21, -16
	add	w1, w19, 255
	mov	w3, w0
	and	w1, w1, -256
	add	w0, w0, 62
	lsl	w1, w1, 4
	ldr	x25, [x29, 184]
	mov	w2, w1
	adds	w1, w3, 31
	csel	w0, w0, w1, mi
	add	w21, w2, 15
	cmp	w2, wzr
	asr	w0, w0, 5
	csel	w21, w21, w2, lt
	cmp	w20, wzr
	asr	w21, w21, 4
	ccmp	w20, 3, 4, ne
	stp	w2, w3, [x29, 124]
	mul	w21, w0, w21
	add	x21, x22, x21, sxtw
	bne	.L753
	lsr	w1, w3, 1
	lsr	w0, w19, 1
	str	w1, [x29, 120]
	add	x1, x25, 2097152
	str	w0, [x29, 104]
	str	x1, [x29, 136]
	ldr	x28, .LC294
	ldr	x20, [x29, 152]
	cbz	w3, .L755
	mov	w27, 0
	str	wzr, [x29, 132]
	.p2align 2
.L754:
	cbz	w19, .L757
	ldr	w0, [x29, 124]
	lsr	w23, w27, 4
	ldr	w24, [x29, 132]
	mov	w26, 0
	mul	w0, w23, w0
	ubfiz	x23, x27, 8, 4
	add	x23, x0, x23
	.p2align 2
.L756:
	lsr	w1, w26, 8
	add	x0, x24, x26, uxtw
	ubfiz	x1, x1, 12, 20
	ldr	x5, [x28, 104]
	add	x1, x1, x23
	mov	x2, 256
	add	x1, x22, x1
	add	x0, x20, x0
	add	w26, w26, 256
	blr	x5
	cmp	w19, w26
	bhi	.L756
.L757:
	ldr	w0, [x29, 132]
	add	w27, w27, 1
	add	w0, w0, w19
	str	w0, [x29, 132]
	ldr	w0, [x29, 128]
	cmp	w0, w27
	bne	.L754
.L755:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	blr	x3
	ldr	w0, [x29, 120]
	cbz	w0, .L847
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 132]
	.p2align 2
.L761:
	cbz	w19, .L763
	ldr	w0, [x29, 132]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L760:
	lsr	w1, w27, 8
	add	x0, x23, x27, uxtw
	ubfiz	x1, x1, 11, 21
	ldr	x5, [x28, 104]
	add	x1, x1, x22
	mov	x2, 256
	add	x1, x21, x1
	add	x0, x20, x0
	add	w27, w27, 256
	blr	x5
	cmp	w19, w27
	bhi	.L760
.L763:
	ldr	w0, [x29, 120]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L761
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L848
.L789:
	ldr	w0, [x29, 108]
	cbnz	w0, .L766
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	ldr	x0, [x29, 136]
	mov	w1, 128
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	mov	w1, 128
	mov	x0, x25
	blr	x3
.L766:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 120]
.L842:
	mul	w19, w0, w1
	ldr	x20, [x29, 112]
	mov	x0, x25
	ldr	x3, [x28, 88]
	mov	w1, w19
	mov	x2, x20
	blr	x3
	ldr	x3, [x28, 88]
	mov	x2, x20
	ldr	x0, [x29, 136]
	mov	w1, w19
	blr	x3
	ldr	w0, [x29, 160]
	ldr	x1, [x29, 152]
	bl	MEM_ReleaseMemBlock
	ldr	x3, [x28, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 144
	blr	x3
	ldr	w0, [x29, 192]
	ldr	x1, [x29, 184]
	bl	MEM_ReleaseMemBlock
	ldr	x3, [x28, 96]
	mov	x2, 32
	mov	w1, 0
	add	x0, x29, 176
	blr	x3
.L748:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L752:
	ldr	x1, .LC291
	mov	w0, 1
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
	.p2align 3
.L792:
	mov	w20, 0
	b	.L749
.L753:
	cmp	w20, 1
	ldr	w1, [x29, 128]
	cset	w0, ne
	str	w0, [x29, 120]
	cmp	w1, w0
	lsr	w0, w19, 1
	str	w0, [x29, 104]
	lsr	w0, w1, 1
	str	w0, [x29, 132]
	add	x0, x25, 2097152
	str	x0, [x29, 136]
	ldr	x28, .LC294
	ldr	x20, [x29, 152]
	bls	.L771
	ldr	w27, [x29, 120]
	.p2align 2
.L773:
	cbz	w19, .L774
	ldr	w0, [x29, 124]
	lsr	w24, w27, 4
	lsr	w23, w27, 1
	mov	w26, 0
	mul	w0, w24, w0
	mul	w23, w23, w19
	ubfiz	x24, x27, 8, 4
	add	x24, x0, x24
	.p2align 2
.L772:
	lsr	w1, w26, 8
	add	x0, x23, x26, uxtw
	ubfiz	x1, x1, 12, 20
	ldr	x5, [x28, 104]
	add	x1, x1, x24
	mov	x2, 256
	add	x1, x22, x1
	add	x0, x20, x0
	add	w26, w26, 256
	blr	x5
	cmp	w19, w26
	bhi	.L772
.L774:
	ldr	w0, [x29, 128]
	add	w27, w27, 2
	cmp	w0, w27
	bhi	.L773
.L771:
	ldr	w0, [x29, 128]
	ldr	x3, [x28, 88]
	ldr	x2, [x29, 112]
	mul	w1, w19, w0
	mov	x0, x20
	lsr	w1, w1, 1
	blr	x3
	ldr	w0, [x29, 132]
	cbz	w0, .L849
	ldr	w1, [x29, 124]
	mov	w26, 0
	mov	w24, 0
	asr	w0, w1, 1
	str	w0, [x29, 128]
	.p2align 2
.L778:
	cbz	w19, .L780
	ldr	w0, [x29, 128]
	lsr	w22, w24, 3
	uxtw	x23, w26
	mov	w27, 0
	mul	w0, w22, w0
	ubfiz	x22, x24, 8, 3
	add	x22, x0, x22
	.p2align 2
.L777:
	lsr	w1, w27, 8
	add	x0, x23, x27, uxtw
	ubfiz	x1, x1, 11, 21
	ldr	x5, [x28, 104]
	add	x1, x1, x22
	mov	x2, 256
	add	x1, x21, x1
	add	x0, x20, x0
	add	w27, w27, 256
	blr	x5
	cmp	w19, w27
	bhi	.L777
.L780:
	ldr	w0, [x29, 132]
	add	w24, w24, 1
	add	w26, w26, w19
	cmp	w0, w24
	bne	.L778
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L850
	ldr	w0, [x29, 108]
	cbnz	w0, .L783
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 132]
	cmp	w0, w1
	bls	.L786
	.p2align 2
.L787:
	ldr	w0, [x29, 120]
	ldr	w1, [x29, 132]
	add	w0, w0, 2
	str	w0, [x29, 120]
	cmp	w1, w0
	bhi	.L787
.L786:
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	ldr	x0, [x29, 136]
	mov	w1, 128
	blr	x3
	ldr	x3, [x28, 96]
	mov	x2, 1048576
	mov	w1, 128
	mov	x0, x25
	blr	x3
.L783:
	ldr	w0, [x29, 104]
	ldr	w1, [x29, 132]
	b	.L842
.L848:
	mov	w0, 0
	mov	w6, 0
	.p2align 2
.L765:
	ldr	w1, [x29, 104]
	mov	w5, w0
	cbz	w1, .L767
	ldr	w1, [x29, 104]
	add	w5, w1, w0
	mov	w1, 1
	.p2align 2
.L764:
	sub	w3, w1, #1
	uxtw	x2, w0
	ldr	x4, [x29, 136]
	add	w0, w0, 1
	cmp	w0, w5
	ldrb	w3, [x20, x3]
	strb	w3, [x4, x2]
	ldrb	w3, [x20, w1, uxtw]
	add	w1, w1, 2
	strb	w3, [x25, x2]
	bne	.L764
.L767:
	ldr	w0, [x29, 120]
	add	w6, w6, 1
	add	x20, x20, x19
	cmp	w0, w6
	mov	w0, w5
	bne	.L765
	b	.L766
.L850:
	ldr	w0, [x29, 120]
	mov	w7, 0
	mul	w1, w19, w0
	lsl	w0, w19, 1
	add	x20, x20, x1
	.p2align 2
.L782:
	ldr	w3, [x29, 104]
	cbz	w3, .L784
	lsr	w1, w7, 1
	mov	w2, 1
	mul	w1, w1, w3
	add	w6, w3, w1
	.p2align 2
.L781:
	sub	w5, w2, #1
	uxtw	x3, w1
	ldr	x4, [x29, 136]
	add	w1, w1, 1
	cmp	w6, w1
	ldrb	w5, [x20, x5]
	strb	w5, [x4, x3]
	ldrb	w5, [x20, w2, uxtw]
	add	w2, w2, 2
	strb	w5, [x25, x3]
	bne	.L781
.L784:
	ldr	w1, [x29, 132]
	add	w7, w7, 2
	add	x20, x20, x0
	cmp	w1, w7
	bhi	.L782
	b	.L783
.L849:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	beq	.L783
	ldr	w0, [x29, 108]
	cbz	w0, .L786
	b	.L783
.L847:
	ldr	w0, [x29, 108]
	cmp	w0, 1
	bne	.L789
	b	.L766
	.size	VDMHAL_V5R2C1_WriteBigTitle1DYuv, .-VDMHAL_V5R2C1_WriteBigTitle1DYuv
	.align	3
.LC289:
	.xword	.LC288
	.align	3
.LC291:
	.xword	.LC290
	.align	3
.LC293:
	.xword	.LC292
	.align	3
.LC294:
	.xword	vfmw_Osal_Func_Ptr_S
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	CRG_ConfigReg
	.type	CRG_ConfigReg, %function
CRG_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	mov	w19, w0
	mov	x0, x30
	mov	w20, w1
	mov	x21, x2
	bl	_mcount
	ldr	x0, .LC295
	ldrb	w0, [x0]
	cmp	w0, 1
	bne	.L858
	cbnz	w19, .L854
	ldr	x0, .LC296
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	ubfx	x2, x0, 8, 2
	cmp	w20, w2
	beq	.L851
	bfi	w0, w20, 8, 2
	str	w0, [x1, 120]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L854:
	cmp	w19, 1
	beq	.L859
.L851:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L858:
	mov	w3, w20
	mov	w2, w19
	mov	x0, x21
	mov	w1, 0
	bl	VDH_Record_RegData
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L859:
	ldr	x0, .LC296
	ldr	x1, [x0]
	ldr	w0, [x1, 120]
	bfi	w0, w20, 12, 5
	and	w0, w0, -131073
	str	w0, [x1, 120]
	ldr	w0, [x1, 120]
	orr	w0, w0, 131072
	str	w0, [x1, 120]
	b	.L851
	.size	CRG_ConfigReg, .-CRG_ConfigReg
	.align	3
.LC295:
	.xword	g_HalDisable
	.align	3
.LC296:
	.xword	g_pstRegCrg
	.global	_mcount
	.align	2
	.p2align 3,,7
	.global	MFDE_ConfigReg
	.type	MFDE_ConfigReg, %function
MFDE_ConfigReg:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	uxtw	x20, w0
	mov	x0, x30
	mov	w21, w1
	sxtw	x19, w2
	mov	x22, x3
	bl	_mcount
	ldr	x0, .LC297
	ldrb	w4, [x0]
	cmp	w4, 1
	bne	.L864
	cmp	w19, wzr
	ble	.L865
	ldr	x2, .LC299
	mov	w3, w19
	ldr	x1, .LC300
	mov	w0, 32
	add	x2, x2, 864
	bl	dprint_vfmw
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L865:
	lsl	x0, x19, 6
	ldr	x1, .LC298
	sub	x0, x0, x19
	lsl	x0, x0, 2
	sub	x19, x0, x19
	add	x19, x0, x19, lsl 2
	ldr	x0, [x1, x19]
	str	w21, [x0, x20]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.p2align 3
.L864:
	mov	w3, w21
	mov	w2, w20
	mov	x0, x22
	mov	w1, 2
	bl	VDH_Record_RegData
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	MFDE_ConfigReg, .-MFDE_ConfigReg
	.align	3
.LC297:
	.xword	g_HalDisable
	.align	3
.LC298:
	.xword	g_HwMem
	.align	3
.LC299:
	.xword	.LANCHOR0
	.align	3
.LC300:
	.xword	.LC101
	.section	.rodata
	.align	3
.LANCHOR0 = . + 0
	.type	__func__.52836, %object
	.size	__func__.52836, 22
__func__.52836:
	.string	"VDMHAL_V5R2C1_OpenHAL"
	.zero	2
	.type	__func__.52910, %object
	.size	__func__.52910, 25
__func__.52910:
	.string	"VDMHAL_V5R2C1_CalcFsSize"
	.zero	7
	.type	__func__.52936, %object
	.size	__func__.52936, 24
__func__.52936:
	.string	"VDMHAL_V5R2C1_CalcFsNum"
	.type	__func__.52979, %object
	.size	__func__.52979, 32
__func__.52979:
	.string	"VDMHAL_V5R2C1_ArrangeMem_Normal"
	.type	__FUNCTION__.52980, %object
	.size	__FUNCTION__.52980, 32
__FUNCTION__.52980:
	.string	"VDMHAL_V5R2C1_ArrangeMem_Normal"
	.type	__func__.52922, %object
	.size	__func__.52922, 33
__func__.52922:
	.string	"VDMHAL_V5R2C1_FillMemArrangeInfo"
	.zero	7
	.type	__func__.53062, %object
	.size	__func__.53062, 34
__func__.53062:
	.string	"VDMHAL_V5R2C1_ArrangeMem_Specific"
	.zero	6
	.type	__func__.53085, %object
	.size	__func__.53085, 23
__func__.53085:
	.string	"VDMHAL_V5R2C1_ResetVdm"
	.zero	1
	.type	__func__.53095, %object
	.size	__func__.53095, 35
__func__.53095:
	.string	"VDMHAL_V5R2C1_SetSmmuPageTableAddr"
	.zero	5
	.type	__func__.53116, %object
	.size	__func__.53116, 24
__func__.53116:
	.string	"VDMHAL_V5R2C1_GlbResetX"
	.type	__func__.53105, %object
	.size	__func__.53105, 23
__func__.53105:
	.string	"VDMHAL_V5R2C1_GlbReset"
	.zero	1
	.type	__func__.53128, %object
	.size	__func__.53128, 28
__func__.53128:
	.string	"VDMHAL_V5R2C1_ClearIntState"
	.zero	4
	.type	__func__.53134, %object
	.size	__func__.53134, 31
__func__.53134:
	.string	"VDMHAL_V5R2C1_ClearMMUIntState"
	.zero	1
	.type	__func__.53140, %object
	.size	__func__.53140, 22
__func__.53140:
	.string	"VDMHAL_V5R2C1_MaskInt"
	.zero	2
	.type	__func__.53153, %object
	.size	__func__.53153, 24
__func__.53153:
	.string	"VDMHAL_V5R2C1_EnableInt"
	.type	__func__.53162, %object
	.size	__func__.53162, 23
__func__.53162:
	.string	"VDMHAL_V5R2C1_CheckReg"
	.zero	1
	.type	__func__.53176, %object
	.size	__func__.53176, 26
__func__.53176:
	.string	"VDMHAL_V5R2C1_ReadMMUMask"
	.zero	6
	.type	__func__.53181, %object
	.size	__func__.53181, 27
__func__.53181:
	.string	"VDMHAL_V5R2C1_WriteMMUMask"
	.zero	5
	.type	__func__.53212, %object
	.size	__func__.53212, 25
__func__.53212:
	.string	"VDMHAL_V5R2C1_PrepareDec"
	.zero	7
	.type	__func__.53217, %object
	.size	__func__.53217, 25
__func__.53217:
	.string	"VDMHAL_V5R2C1_IsVdmReady"
	.zero	7
	.type	__func__.53222, %object
	.size	__func__.53222, 23
__func__.53222:
	.string	"VDMHAL_V5R2C1_IsVdmRun"
	.zero	1
	.type	__func__.53228, %object
	.size	__func__.53228, 27
__func__.53228:
	.string	"VDMHAL_V5R2C1_IsVdhDecOver"
	.zero	5
	.type	__func__.53238, %object
	.size	__func__.53238, 31
__func__.53238:
	.string	"VDMHAL_V5R2C1_IsVdhPartDecOver"
	.zero	1
	.type	__func__.53253, %object
	.size	__func__.53253, 33
__func__.53253:
	.string	"VDMHAL_V5R2C1_UpdateHardwareInfo"
	.zero	7
	.type	__func__.53326, %object
	.size	__func__.53326, 23
__func__.53326:
	.string	"VDMHAL_V5R2C1_CfgRpMsg"
	.zero	1
	.type	__func__.53303, %object
	.size	__func__.53303, 24
__func__.53303:
	.string	"VDMHAL_CfgNotFullRepair"
	.type	__func__.53337, %object
	.size	__func__.53337, 23
__func__.53337:
	.string	"VDMHAL_V5R2C1_CfgRpReg"
	.zero	1
	.type	__func__.53350, %object
	.size	__func__.53350, 28
__func__.53350:
	.string	"VDMHAL_V5R2C1_MakeDecReport"
	.zero	4
	.type	__func__.53419, %object
	.size	__func__.53419, 28
__func__.53419:
	.string	"VDMHAL_V5R2C1_PrepareRepair"
	.zero	4
	.type	__func__.53609, %object
	.size	__func__.53609, 15
__func__.53609:
	.string	"MFDE_ConfigReg"
	.zero	1
	.type	__func__.53426, %object
	.size	__func__.53426, 28
__func__.53426:
	.string	"VDMHAL_V5R2C1_StartHwRepair"
	.zero	4
	.type	__func__.53465, %object
	.size	__func__.53465, 28
__func__.53465:
	.string	"VDMHAL_V5R2C1_CalVdhClkSkip"
	.zero	4
	.type	__func__.53491, %object
	.size	__func__.53491, 28
__func__.53491:
	.string	"VDMHAL_V5R2C1_StartHwDecode"
	.section	.rodata.str1.8,"aMS",%progbits,1
	.align	3
.LC4:
	ASCII(.string	"pOpenParam = NULL error!" )
	.zero	7
.LC7:
	ASCII(.string	"%s: %s\n" )
.LC9:
	ASCII(.string	"MemBaseAddr = 0 error!" )
	.zero	1
.LC11:
	ASCII(.string	"VDMHAL_V5R2C1_OpenHAL: Size error!" )
	.zero	5
.LC13:
	ASCII(.string	"VdhId is wrong!!!\n" )
	.zero	5
.LC17:
	ASCII(.string	"g_VdmRegVirAddr, g_VdmResetVirAddr = %p\n" )
	.zero	7
.LC19:
	ASCII(.string	"BPDRegVirAddr %p\n" )
	.zero	6
.LC21:
	ASCII(.string	"!!!!!! HAL memory not enouph! need %d, have %d\n" )
.LC23:
	ASCII(.string	"image size out of range" )
.LC30:
	ASCII(.string	"VDMHAL ArrangeMem HEVC/VP9 10 bit\n" )
	.zero	5
.LC33:
	ASCII(.string	"%s pstVfmwFrameSizeInfo = NULL\n" )
.LC37:
	ASCII(.string	"DelAllFrameMemRecord err in VDMHAL_V5R2C1_ArrangeMem!\n" )
	.zero	1
.LC39:
	ASCII(.string	"Report arrange frame buffer: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	3
.LC44:
	ASCII(.string	"Report arrange frame buffer only: wxh %dx%d, FsNum %d, PmvNum %d\n" )
	.zero	6
.LC47:
	ASCII(.string	"VidStd Invalid" )
	.zero	1
.LC52:
	ASCII(.string	"Set CompressEn %d, LossCompressEn %d, YCompRatio %d, UVCompRatio %d\n" )
	.zero	3
.LC54:
	ASCII(.string	"VDMHAL_V5R2C1_CalcFsSize err!\n" )
	.zero	1
.LC56:
	ASCII(.string	"%s, need arrange, Size: %#x, Num: %#x, RefChanged: %#x\n" )
.LC58:
	ASCII(.string	"DFS, report event. Size: 0x%x, Num: %d, RefChanged: %d\n" )
.LC61:
	ASCII(.string	"pVdmMemArrange is NULL" )
	.zero	1
.LC63:
	ASCII(.string	"DFS, no ref frame!\n" )
	.zero	4
.LC65:
	ASCII(.string	"DFS, Frame number = %d > 30, Then, Frame num = 30, \n" )
	.zero	3
.LC67:
	ASCII(.string	"VDMHAL_V5R2C1_ArrangeMem Mem addr is NULL" )
	.zero	6
.LC72:
	ASCII(.string	"'pVdmMemArrange' is NULL" )
	.zero	7
.LC76:
	ASCII(.string	"MemSize not enough for pmv slot" )
.LC79:
	ASCII(.string	"VDMHAL_V200R003_ArrangeMem get ChanWidth/ChanHeight failed!\n" )
	.zero	3
.LC81:
	ASCII(.string	"ImgSlotLen > ChanSlotLen" )
	.zero	7
.LC83:
	ASCII(.string	"cann't allocate img slot" )
	.zero	7
.LC87:
	ASCII(.string	"%s: VdhId(%d) > %d\n" )
	.zero	4
.LC89:
	ASCII(.string	"VDMHAL_V5R2C1_ResetVdm: map vdm register fail, vir(reg) = (%p)\n" )
.LC94:
	ASCII(.string	"%s module id %d failed!\n" )
	.zero	7
.LC96:
	ASCII(.string	"%s module id %d success!\n" )
	.zero	6
.LC101:
	ASCII(.string	"%s: WR_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC106:
	ASCII(.string	"%s: map vdm register 0x%x failed!\n" )
	.zero	5
.LC110:
	ASCII(.string	"%s VdhId %d failed!\n" )
	.zero	3
.LC112:
	ASCII(.string	"%s VdhId %d success!\n" )
	.zero	2
.LC121:
	ASCII(.string	"vdm register virtual address not mapped, reset failed!\n" )
.LC138:
	ASCII(.string	"%s: VdhId(%d) Invalid!\n" )
.LC141:
	ASCII(.string	"%s: vdm register virtual address not mapped, reset failed!\n" )
	.zero	4
.LC143:
	ASCII(.string	"%s: unkown reg_id = %d\n" )
.LC148:
	ASCII(.string	"%s: RD_VREG but VdhId(%d) > MAX_VDH_NUM(%d)\n" )
	.zero	3
.LC154:
	ASCII(.string	"%s: pDecParam(%p) = NULL\n" )
	.zero	6
.LC159:
	ASCII(.string	"VDM register not mapped yet!" )
	.zero	3
.LC165:
	ASCII(.string	"VDM register not mapped yet!\n" )
	.zero	2
.LC187:
	ASCII(.string	"can NOT map vir addr for up-msg" )
.LC191:
	ASCII(.string	"ReadUpMsgSlot error! pDst=%p, pSrc=%p\n" )
	.zero	1
.LC193:
	ASCII(.string	"ReadUpMsgSlot error! upmsg_size(%d) > 512\n" )
	.zero	5
.LC196:
	ASCII(.string	"WriteMsgSlot error!\n" )
	.zero	3
.LC199:
	ASCII(.string	"can not map repair msg virtual address!" )
.LC203:
	ASCII(.string	"ValidGroupNum=%d out of range!\n" )
.LC205:
	ASCII(.string	"align_mb error\n" )
.LC207:
	ASCII(.string	"[%s][%d]sclie_num is wrong! %d \n" )
	.zero	7
.LC216:
	ASCII(.string	"'pMakeDecReport' is NULL" )
	.zero	7
.LC220:
	ASCII(.string	"'pDecReport' is NULL" )
	.zero	3
.LC230:
	ASCII(.string	"pDecReport->DecSliceNum(%d) > %d, set to 0 for full repair.\n" )
	.zero	3
.LC234:
	ASCII(.string	"\n***** UpMsg DecSliceNum=%d\n" )
	.zero	3
.LC236:
	ASCII(.string	"\n***** Up Msg (phy addr: %#8x) *****\n" )
	.zero	2
.LC238:
	ASCII(.string	"\n0x%02x 0x%08x 0x%08x 0x%08x 0x%08x\n" )
	.zero	3
.LC240:
	ASCII(.string	"\n***** Up Msg print finished *****\n" )
	.zero	4
.LC245:
	ASCII(.string	"vdm register virtual address not mapped, VDMHAL_V200R003_PrepareRepair failed!\n" )
.LC248:
	ASCII(.string	"FIRST_REPAIR Parameter Error!\n" )
	.zero	1
.LC250:
	ASCII(.string	"SECOND_REPAIR Parameter Error!\n" )
.LC256:
	ASCII(.string	"%s: pMfdeTask(%p) = NULL\n" )
	.zero	6
.LC265:
	ASCII(.string	"%s The channel %d is not active\n" )
	.zero	7
.LC288:
	ASCII(.string	"BigTile1d_y" )
	.zero	4
.LC290:
	ASCII(.string	"failed mem_allocMemBlock BigTile_yuv save!\n" )
	.zero	4
.LC292:
	ASCII(.string	"BigTile1d_uv" )
	.ident	"GCC: (gcc-linaro-5.1-2015.08 + glibc-2.22 (Build by czyong Wed Mar  9 18:57:48 CST 2016)) 5.1.1 20150608"
	.section	.note.GNU-stack,"",%progbits
