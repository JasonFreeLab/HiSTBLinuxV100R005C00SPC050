#ifndef __VDEC_PRODUCT_H__
#define __VDEC_PRODUCT_H__

#include "vfmw.h"
#include "vdm_hal.h"

#define PDT_OK   0
#define PDT_ERR  -1

typedef enum
{
    ATTR_VDEC_CAP,
    ATTR_VDEC_ISNVRCHIP,
    ATTR_OUT_FMT,
    ATTR_BUTT,
}ATTR_ID;

SINT32 PDT_GetAttribute(ATTR_ID eAttrID, VOID *pArgs);
SINT32 PDT_Init(VDMHAL_FUN_PTR_S *pFuncPtr);

#endif

