#include <asm_macros.S>

.global c51_cpu_suspend

#define REG_GEN9	0xf80000a4
#define REG_GEN13	0xf80000b4
#define REG_GEN30	0xf80000f8

#define MCU_START_CTRL  0xf840f000 /* mcu start control */

func c51_cpu_suspend

	/* set scu boot entry point */
	ldr	w0,	=resume_entry_start_32
	ldr	x1,	=REG_GEN9
	str	w0,	[x1]

	/* set 64bit entry point */
	ldr	w0,	=psci_entrypoint
	ldr	x1,	=REG_GEN30
	str	w0,	[x1]

enable_mcu:
	/* start mcu */
	ldr	x0,	=MCU_START_CTRL
	ldr	w1,	[x0]
	orr	w1, 	w1, #0x1
	str	w1,	[x0]

	ret

