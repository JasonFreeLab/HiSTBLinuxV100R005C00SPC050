#include <common.h>
#include <asm/armv7.h>
#include <asm/utils.h>
#include <stdarg.h>


int exec_smc(u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
	register u32 r0 asm("r0");
	register u32 r1 asm("r1");
	register u32 r2 asm("r2");
	register u32 r3 asm("r3");

	printf("smc enter: 0x%X, 0x%X, 0x%X, 0x%X\n", arg0, arg1, arg2, arg3);

	r0 = arg0;
	r1 = arg1;
	r2 = arg2;
	r3 = arg3;

	asm volatile(
		__asmeq("%0", "r0")
		__asmeq("%1", "r0")
		__asmeq("%2", "r1")
		__asmeq("%3", "r2")
		__asmeq("%4", "r3")
		".arch_extension sec\n"
		"smc	#0\n"
		: "+r" (r0)
		: "r" (r0), "r" (r1), "r" (r2), "r" (r3)
		: "memory");

	printf("smc return:%d\n",r0);

	return r0;
}
