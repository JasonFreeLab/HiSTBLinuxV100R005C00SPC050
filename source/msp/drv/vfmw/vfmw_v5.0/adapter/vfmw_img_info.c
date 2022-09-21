
/***********************************************************************
*
* Copyright (c) 2006  - All Rights Reserved
*
* Date: $2016/10/08$
* Revision: $v1.0$
* Purpose: convert some info(such as HDR/PTS/ info) for postprocess
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2016/10/08                 Original
*
*
* Dependencies:
*
************************************************************************/

#include "public.h"
#include "hdr_info.h"
#include "pts_info.h"

/*----------------------------EXTERNAL FUNCTION-------------------------------*/
VOID IMG_Info_Convert(SINT32 ChanID, IMAGE *pstImage)
{
    SINT32 Ret;

    Ret = HDR_Info_Convert(ChanID, pstImage);
    if (Ret != VDEC_OK)
    {
        dprint(PRN_ERROR, "%s convert hdr info failed!\n", __func__);
    }

    Ret = PTS_Info_Convert(ChanID, pstImage);
    if (Ret != VDEC_OK)
    {
        dprint(PRN_ERROR, "%s convert pts info failed!\n", __func__);
    }

    return;
}

VOID IMG_Info_Init(VOID)
{
    HDR_Info_Init();
    PTS_Info_Init();

    return;
}

VOID IMG_Info_Exit(VOID)
{
    HDR_Info_Exit();
    PTS_Info_Exit();

    return;
}

