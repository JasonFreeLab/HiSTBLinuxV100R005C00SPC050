
/***********************************************************************
*
* Copyright (c) 2006  - All Rights Reserved
*
* Date: $2016/09/27$
* Revision: $v1.0$
* Purpose: interface header file of PTS module
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2016/11/21               Original
*
*
* Dependencies:
*
************************************************************************/

#ifndef __PTS_INFO_H__
#define __PTS_INFO_H__

#include "vfmw.h"

#ifdef __cplusplus
extern "C" {
#endif


/*----------------------------EXTERNAL FUNCTION-------------------------------*/
SINT32 PTS_Info_Init(VOID);
SINT32 PTS_Info_Exit(VOID);
SINT32 PTS_Info_Alloc(SINT32 ChanID);
SINT32 PTS_Info_Free (SINT32 ChanID);
SINT32 PTS_Info_Reset(SINT32 ChanID);
SINT32 PTS_Info_SetFrmRate(SINT32 ChanID, PTS_FRMRATE_S *pstFrmRate);
SINT32 PTS_Info_GetFrmRate(SINT32 ChanID, PTS_FRMRATE_S *pstFrmRate);
SINT32 PTS_Info_Convert(SINT32 ChanID, IMAGE *pstImage);
SINT32 PTS_Info_EnableSampleFRD (SINT32 ChanID);
SINT32 PTS_Info_DisableSampleFRD(SINT32 ChanID);


#ifdef __cplusplus
}
#endif

#endif

