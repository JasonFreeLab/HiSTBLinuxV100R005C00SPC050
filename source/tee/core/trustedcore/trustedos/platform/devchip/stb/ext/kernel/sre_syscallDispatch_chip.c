#include <stddef.h>

#include "sre_task.h"
#include "sre_base.h"
#include "sre_typedef.h"
#include "sre_syscalls_id_chip.h"
#include "sre_typedef.h"
#include "sre_taskmem.h"
#include "sre_securemmu.h"
#include "sre_access_control.h"
#include "sre_log.h"


#ifdef CFG_HI_TEE_PLCIPHER_SUPPORT
#include "hi_tee_drv_plcipher.h"
#include "tee_drv_plcipher_ioctl.h"
#endif


extern int tee_hisilicon_ioctl(const unsigned int module,
	const unsigned int cmd, void *args, const size_t size);

int swi_handler_chip(int swi_id, TSK_REGS_S *regs, UINT64 permissions)
{

    UINT32 uwRet = 0;
    /* According to ARM AAPCS arguments from 5-> in a function call
     * are stored on the stack, which in this case is pointer by
     * user sp. Our own TrustedCore also push FP and LR on the stack
     * just before SWI, so skip them */
    UINT32  *args = (UINT32 *)(regs->usr_sp + 8);

    HANDLE_SYSCALL(swi_id)
    {
        SYSCALL_PERMISSION(SW_SYSCALL_TEE_HISILICON_IOCTL, permissions, GENERAL_GROUP_PERMISSION)
            uwRet = tee_hisilicon_ioctl(regs->r0, regs->r1, (void *)regs->r2, regs->r3);
            regs->r0 = uwRet;
        SYSCALL_END;



            default:
                return -1;
    }

	(void)args;
    return 0;

}
