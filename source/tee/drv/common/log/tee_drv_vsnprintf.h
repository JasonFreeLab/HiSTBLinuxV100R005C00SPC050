/***********************************************************************************
*              Copyright 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  tee_drv_vsnprintf.h
* Description:  Define svnprintf interface.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1      20161215    NA                 NULL      Create this file.
***********************************************************************************/

#ifndef __TEE_DRV_VSNPRINTF_H__
#define __TEE_DRV_VSNPRINTF_H__

#include <stdarg.h>

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define _U  0x01    /* upper */
#define _L  0x02    /* lower */
#define _D  0x04    /* digit */
#define _C  0x08    /* cntrl */
#define _P  0x10    /* punct */
#define _S  0x20    /* white space (space/lf/tab) */
#define _X  0x40    /* hex digit */
#define _SP 0x80    /* hard space (0x20) */

struct tee_snprintf_arg {
	HI_CHAR	*str;
	HI_U32	remain;
};

extern HI_U8 _ctype[];

#define hex2ascii(hex) (hex2ascii_data[hex]) 
#define imax(_a, _b) ((_a) > (_b) ? (_a) : (_b))

#define __ismask(x) (_ctype[(int)(unsigned char)(x)])
#define islower(c)  ((__ismask(c)&(_L)) != 0)
#define isupper(c)  ((__ismask(c)&(_U)) != 0)

HI_S32 tee_vsnprintf(HI_CHAR *str, HI_U32 size, const HI_CHAR *format, va_list ap);

#ifdef __cplusplus
}
#endif

#endif  /* __TEE_HAL_DEMUX_H__ */