
#ifndef __CTRL_CASE_H__
#define __CTRL_CASE_H__

#include "vfmw.h"


typedef SINT32 (*FN_VDEC_CID_HANDLER)(SINT32 ChanID, VOID *pArgs);
typedef struct
{
    VDEC_CID_E eCmdID;
    FN_VDEC_CID_HANDLER pHandler;
    UINT32 Length;
}VDEC_CID_NODE;

SINT32 CASE_HandleEntry(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs);

#endif

