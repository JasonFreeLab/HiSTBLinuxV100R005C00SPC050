#ifndef __TEST_CRC_HEADER__
#define __TEST_CRC_HEADER__

#include "vfmw.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------EXTERNAL FUNCTION-------------------------------*/
VOID   CRC_Init(VOID);
VOID   CRC_Exit(VOID);
SINT32 CRC_CreateInst(SINT32 InstID);
SINT32 CRC_DestroyInst(SINT32 InstID);
SINT32 CRC_SetConfig(SINT32 InstID, VDEC_CHAN_CFG_S *pstCfg);
SINT32 CRC_PutImage(SINT32 InstID, IMAGE *pImage);

#ifdef __cplusplus
}
#endif

#endif


