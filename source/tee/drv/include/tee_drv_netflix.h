#include "hi_type.h"
#include "tee_os_hal.h"

#ifndef __TEE_DRV_NETFLIX_H__
#define __TEE_DRV_NETFLIX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern void *asm_memmove(void *dest, const void *src, unsigned int n);

#define TEE_NETFLIX_MEMCPY  asm_memmove

typedef struct
{
    HI_VOID *VirAddr;
    HI_U32   PhyAddr;
    HI_U32   Size;
}NETFLIX_BUFFER_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
