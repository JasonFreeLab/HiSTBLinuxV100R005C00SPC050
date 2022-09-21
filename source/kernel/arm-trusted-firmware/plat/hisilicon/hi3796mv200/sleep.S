#include <asm_macros.S>

.global c51_cpu_suspend

#define REG_GEN9	0xf80000a4
#define REG_GEN13	0xf80000b4
#define REG_GEN30	0xf80000f8

#define MCU_START_CTRL  0xf840f000 /* mcu start control */
#define SECURE_CPU_SUPPORT 0xf8ab00f4

#define REG_MAILBOX_ARG_0 0xf9a39040 //cep
#define REG_MAILBOX_ARG_1 0xf9a39044 //ree cep
#define REG_MAILBOX_ARG_2 0xf9a39048 //ddr_sha_alg
#define REG_MAILBOX_ARG_3 0xf9a3904c //aarch64
#define REG_MAILBOX_ARG_4 0xf9a39050 //ree cep flag 
#define REG_MAILBOX_ARG_5 0xf9a39054 //count
#define REG_MAILBOX_ARG_6 0xf9a39058 //addr
#define REG_MAILBOX_ARG_7 0xf9a3905c //length
#define REG_MAILBOX_CMD   0xf9a39020
#define SHA_3 0x66031013

.section .rodata.pm_debug_str, "aS"
	debug_msg: .asciz "INFO: enter CA\n"

func c51_cpu_suspend

	/* set scu boot entry point */
	ldr	w0,	=resume_entry_start_32
	ldr	x1,	=REG_MAILBOX_ARG_0
	str	w0,	[x1]

	/* set 64bit entry point */
	ldr	w0,	=psci_entrypoint
	ldr	x1,	=REG_GEN30
	str	w0,	[x1]

	/* set mailbox param */
	ldr	w0,	=0x0
	ldr	x1,	=REG_MAILBOX_ARG_1
	str	w0,	[x1]

	/* ddr_sha_alg */
	ldr	w0,	=0x0
	ldr	x1,	=REG_MAILBOX_ARG_2
	str	w0,	[x1]

	/* aarch64 */
	ldr	w0,	=0xf
	ldr	x1,	=REG_MAILBOX_ARG_3
	str	w0,	[x1]

	ldr	w0,	=0x0
	ldr	x1,	=REG_MAILBOX_ARG_4
	str	w0,	[x1]

	ldr	w0,	=0x1
	ldr	x1,	=REG_MAILBOX_ARG_5
	str	w0,	[x1]

	ldr	w0,	=resume_entry_start_32
	ldr	x1,	=REG_MAILBOX_ARG_6
	str	w0,	[x1]

	ldr	w0,	=0x220000
	ldr	x1,	=REG_MAILBOX_ARG_7
	str	w0,	[x1]

	ldr	w0,	=0x62211f01
	ldr	x1,	=REG_MAILBOX_CMD
	str	w0,	[x1]

	ldr	x1,	=SECURE_CPU_SUPPORT
	ldr	w0,	[x1]
	ldr	w1,	=0xff0000
	and	w0, w0, w1
	ldr	w1,	=0x420000
	cmp	w0,	w1
	beq	enable_mcu

secure_cpu:
	/* advance cpu should save 64bit address */
	ldr	w0,	=psci_entrypoint
	ldr	x1,	=REG_MAILBOX_ARG_0
	str	w0,	[x1]
	ldr	x1,	=REG_MAILBOX_ARG_6
	str	w0,	[x1]

enable_mcu:
	/* start mcu */
	ldr	x0,	=MCU_START_CTRL
	ldr	w1,	[x0]
	orr	w1, 	w1, #0x1
	str	w1,	[x0]

	ret

_panic_loop:
	b	_panic_loop
