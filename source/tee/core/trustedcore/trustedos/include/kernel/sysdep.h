#ifndef __SYS_DEP_H__
#define __SYS_DEP_H__

#include "stdint.h"

#define PTR_GUARD
extern uint32_t g_pointer_chk_guard;

#define PTR_MANGLE(dst, var) \
    do \
    { \
        if (var != NULL) { \
            (dst) = (__typeof (dst)) ((uintptr_t) (var) ^ g_pointer_chk_guard); \
        } else { \
			(dst) = (var); \
		} \
    }while(0)
    
#define PTR_DEMANGLE(dst, var) PTR_MANGLE(dst, var)

#define PTR_MANGLE2(dst, var) \
        (dst) = (__typeof (dst)) ((uintptr_t) (var) ^ g_pointer_chk_guard);
    
#define PTR_DEMANGLE2(dst, var) PTR_MANGLE2(dst, var)

#endif /*__SYS_DEP_H__*/

