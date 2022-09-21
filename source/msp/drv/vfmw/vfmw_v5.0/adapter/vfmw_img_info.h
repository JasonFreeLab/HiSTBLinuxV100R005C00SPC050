
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

#ifndef __IMG_INFO_H__
#define __IMG_INFO_H__

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------EXTERNAL FUNCTION-------------------------------*/

VOID IMG_Info_Init(VOID);
VOID IMG_Info_Exit(VOID);
VOID IMG_Info_Convert(SINT32 ChanID, IMAGE *pstImage);


#ifdef __cplusplus
}
#endif

#endif
