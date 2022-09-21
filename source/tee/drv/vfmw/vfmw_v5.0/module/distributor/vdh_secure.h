#ifndef __VDH_SECURE_H__
#define __VDH_SECURE_H__

#include "vdh_common.h"


#ifdef __cplusplus
extern "C" {
#endif

/******************************************
 Initialize VDH hardware abstract layer 
******************************************/
SINT32 VDH_Secure_Init(VDH_SHARE_DATA_S *pShareData);

/******************************************
 Map Exchange Context in Secure OS
******************************************/
SINT32 VDH_Map_ShareData(VDH_SHARE_DATA_S *pShareData);
    
/******************************************
 UnMap Exchange Context in Secure OS
******************************************/
SINT32 VDH_UnMap_ShareData(VOID);


#ifdef __cplusplus
}
#endif

#endif
