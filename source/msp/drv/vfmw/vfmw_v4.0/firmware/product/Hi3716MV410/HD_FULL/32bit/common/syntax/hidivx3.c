#include    "syntax.h"
#include "divx3.h"
#include    "public.h"
#include    "bitstream.h"
#include    "vfmw.h"

#include    "vdm_hal.h"
#include    "postprocess.h"
#include    "vfmw_ctrl.h"
#include    "fsp.h"


#ifdef DIVX3_ENABLE



SINT32 DIVX3DEC_Init(DIVX3_CTX_S *pCtx, SYNTAX_EXTRA_DATA_S *pstExtraData)
{

    return 0;
}


VOID DIVX3DEC_Destroy(DIVX3_CTX_S *pCtx)
{
    return;
}


SINT32 DIVX3DEC_Decode(DIVX3_CTX_S *pCtx, DEC_STREAM_PACKET_S *pPacket)
{
    return RV8_VFMW_FALSE;
}


SINT32 DIVX3DEC_RecycleImage(DIVX3_CTX_S *pCtx, UINT32 ImgID)
{
    return RV8_VFMW_FALSE;
}


SINT32 DIVX3DEC_GetRemainImg(DIVX3_CTX_S *pCtx)
{
    return -1;
}


UINT32 DIVX3DEC_VDMPostProc(DIVX3_CTX_S *pCtx, SINT32 ErrRatio, UINT32 SwitchRounding)
{
    return RV8_VFMW_FALSE;
}


SINT32 DIVX3DEC_GetImageBuffer( DIVX3_CTX_S *pCtx )
{
    return 0;
}



#endif //REAL8_VFMW_ENABLE
