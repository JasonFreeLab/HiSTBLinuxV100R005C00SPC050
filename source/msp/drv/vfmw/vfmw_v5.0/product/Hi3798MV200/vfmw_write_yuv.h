/*******************************************************************************
*
* Copyright (c) 2006  - All Rights Reserved
*
* Date: $2016/12/16$
* Revision: $v1.0$
* Purpose: interface header file of crc module
*
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
* 2016/12/16                Original
*
*
* Dependencies:
*
*******************************************************************************/
#ifndef __DBG_VFMW_WRITE_YUV_HEADER__
#define __DBG_VFMW_WRITE_YUV_HEADER__

#include "vfmw.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_DUMP_WIDTH               (4096)
#define MAX_DUMP_HEIGHT              (2304)

#define MAX_DUMP_FRAME_SIZE          (MAX_DUMP_WIDTH*MAX_DUMP_HEIGHT*3/2)
#define MAX_DUMP_PIXEL_ARRAY_SIZE    (MAX_DUMP_WIDTH*MAX_DUMP_HEIGHT*2)

/*----------------------------EXTERNAL FUNCTION-------------------------------*/
SINT32 YUV_DumpImage(SINT32 ChanID, IMAGE *pImage);

#ifdef __cplusplus
}
#endif

#endif






