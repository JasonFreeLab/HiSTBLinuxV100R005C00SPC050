
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_com.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_DISP_COM_H__
#define __DRV_DISP_COM_H__

#include "hi_type.h"
#include "hi_drv_video.h"
#include "hi_drv_disp.h"
#include "drv_disp_version.h"
#include "drv_disp_osal.h"
#include "hi_reg_common.h"


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */


/*CVBS  Video Buff Type */
#define  VIDEO_BUFF_CVBS_NONE            0
#define  VIDEO_BUFF_CVBS_FMS6141            1
#define  VIDEO_BUFF_CVBS_FMS6143a           2
#define  VIDEO_BUFF_CVBS_TT_FILTER           3

/*YPbPr  ideo Buff Type */
#define  VIDEO_BUFF_YPBPR_NONE          0
#define  VIDEO_BUFF_YPBPR_FMS6363    1
#define  VIDEO_BUFF_YPBPR_DIO2176       2
#define  VIDEO_BUFF_YPBPR_TT_FILTER       3

/*DAC Type
    Only HISI_VOLTAGE   Support  DAC Detect
    Only SYNOPSYS   Need   Revise LumaNoLine By Gamma
*/

#if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) )

/* Video Buff Type !*/
#define  VIDEO_BUFF_CVBS     VIDEO_BUFF_CVBS_TT_FILTER
#define  VIDEO_BUFF_YPBPR    VIDEO_BUFF_YPBPR_TT_FILTER

#else
/* Video Buff Type!*/
#define  VIDEO_BUFF_CVBS     VIDEO_BUFF_CVBS_FMS6141
#define  VIDEO_BUFF_YPBPR  VIDEO_BUFF_YPBPR_FMS6363

#endif


/*the mode of isogeny output*/
typedef enum tagISOGENY_MODE
{    
	/*cv200/98m/98c, under which hd and sd 's video layer is  symmetrical.*/
	ISOGENY_SYMMETRICAL_MODE = 0,
	/*mv410,98cv200, the sd channel has a wbc input from hd channel.*/
	ISOGENY_WBC_MODE,
    ISOGENY_BUTT
}ISOGENY_MODE_E;



#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /*  __DRV_DISP_COMMON_H__  */


