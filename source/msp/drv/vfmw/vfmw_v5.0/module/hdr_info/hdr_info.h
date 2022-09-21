
/***********************************************************************
*
* Copyright (c) 2006  - All Rights Reserved
*
* File: $hdr.h$
* Date: $2016/09/27$
* Revision: $v1.0$
* Purpose: interface header file of HDR module
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2016/09/27                Original
*
*
* Dependencies:
*
************************************************************************/

#ifndef __HDR_INFO_H__
#define __HDR_INFO_H__
#if defined(VFMW_EXTRA_TYPE_DEFINE)
#include "hi_type.h"
#endif

#include "vfmw.h"


#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------EXTERNAL FUNCTION-------------------------------*/

VOID HDR_Info_Init(VOID);
VOID HDR_Info_Exit(VOID);
SINT32 HDR_Info_Convert(SINT32 ChanID, IMAGE *pstImage);

#ifdef __cplusplus
}
#endif

#endif
