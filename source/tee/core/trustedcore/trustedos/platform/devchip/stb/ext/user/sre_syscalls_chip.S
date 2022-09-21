#include "sre_syscalls_id_chip.h"
#include "sre_syscalls_id.h"



.global __tee_hisilicon_ioctl
    .align 5

__tee_hisilicon_ioctl:
        push {fp, lr}
        add fp, sp, #4
        swi SW_SYSCALL_TEE_HISILICON_IOCTL
        sub sp, fp, #4
        pop {fp, lr}
        bx lr


