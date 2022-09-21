#include "hi_type.h"

#ifndef __TEE_DRV_NETFLIX_IOCTL_H__
#define __TEE_DRV_NETFLIX_IOCTL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

enum NETFLIX_IOCTL_CMD{
	CMD_NETFLIX_CPYFROM_TA_TO_DRV,
	CMD_NETFLIX_CPYFROM_DRV_TO_TA,
};

typedef  struct {
	HI_U32 PhyAddr;
	HI_U8 *VirAddr;
	HI_U32 Offset;
	HI_U32 Size;
}NETFLIX_IOCTL_PARA_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif
